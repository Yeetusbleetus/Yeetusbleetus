#include "MockRuntime.h"

#include "SessionControlSignal.pb.h"

namespace pb = HP::Omnicept::Abi;
using HP::Omnicept::Abi::MessageType;
using HP::Omnicept::detail::Envelope;

namespace {

uint16_t portOf(const std::string& endpoint) {
    return static_cast<uint16_t>(std::stoi(endpoint.substr(endpoint.rfind(':') + 1)));
}

}  // namespace

MockRuntime::MockRuntime(Options options) : m_options(std::move(options)) {
    for (auto* s : {&m_router, &m_in, &m_out}) s->set(zmq::sockopt::linger, 0);
    m_router.bind("tcp://127.0.0.1:" + (m_options.port ? std::to_string(m_options.port) : std::string("*")));
    m_port = portOf(m_router.get(zmq::sockopt::last_endpoint));
    m_in.bind("tcp://127.0.0.1:*");
    m_out.bind("tcp://127.0.0.1:*");
    m_inUri = m_in.get(zmq::sockopt::last_endpoint);
    m_outUri = m_out.get(zmq::sockopt::last_endpoint);
    m_thread = std::thread([this] { loop(); });
}

MockRuntime::~MockRuntime() {
    m_running = false;
    if (m_thread.joinable()) m_thread.join();
}

void MockRuntime::loop() {
    while (m_running) {
        zmq::pollitem_t items[] = {{static_cast<void*>(m_router), 0, ZMQ_POLLIN, 0},
                                   {static_cast<void*>(m_in), 0, ZMQ_POLLIN, 0}};
        zmq::poll(items, 2, std::chrono::milliseconds(10));

        if (items[0].revents & ZMQ_POLLIN) {
            // ROUTER delivers [identity, header, body].
            std::vector<zmq::message_t> frames;
            do {
                zmq::message_t f;
                (void)m_router.recv(f);
                frames.push_back(std::move(f));
            } while (frames.back().more());
            if (frames.size() >= 3) {
                Envelope env = HP::Omnicept::detail::decodeHeader(frames[frames.size() - 2].to_string());
                env.body = frames.back().to_string();
                handleHandshake(frames.front().to_string(), env);
            }
        }

        if (items[1].revents & ZMQ_POLLIN) {
            Envelope env;
            if (HP::Omnicept::detail::receiveEnvelope(m_in, env, true, std::chrono::milliseconds(0)))
                handleData(env);
        }

        std::vector<std::pair<MessageType, std::string>> outbox;
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            outbox.swap(m_outbox);
        }
        for (auto& m : outbox) sendData(m.first, m.second);
    }
}

void MockRuntime::sendControl(const std::string& identity, int signal, const std::string& reason) {
    pb::proto_SessionControlSignal sig;
    sig.set_signal(static_cast<pb::proto_SessionControlSignal_SessionSignal>(signal));
    if (signal == pb::proto_SessionControlSignal::ACCEPT) {
        sig.set_endpointinuri(m_inUri);
        sig.set_endpointouturi(m_outUri);
    }
    sig.set_reasonforrejection(reason);
    Envelope env;
    env.type = MessageType::sessionControlSignal;
    env.sender = "mock-runtime";
    sig.SerializeToString(&env.body);
    m_router.send(zmq::buffer(identity), zmq::send_flags::sndmore);
    HP::Omnicept::detail::sendEnvelope(m_router, env, true);
}

void MockRuntime::handleHandshake(const std::string& identity, const Envelope& env) {
    if (env.type != MessageType::sessionControlSignal) return;
    pb::proto_SessionControlSignal sig;
    if (!sig.ParseFromString(env.body)) return;

    switch (sig.signal()) {
        case pb::proto_SessionControlSignal::CONNECT: {
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                m_clientName = sig.connectionname();
                m_clientId = sig.sessionlicense().clientid();
            }
            if (!m_options.rejectClientId.empty() && sig.sessionlicense().clientid() == m_options.rejectClientId) {
                sendControl(identity, pb::proto_SessionControlSignal::REJECT, "invalid license");
                return;
            }
            if (m_options.sendLicenseValidation)
                sendControl(identity, pb::proto_SessionControlSignal::LICENSE_ACCEPT_VALIDATION);
            sendControl(identity, pb::proto_SessionControlSignal::ACCEPT);
            break;
        }
        case pb::proto_SessionControlSignal::CLIENT_READY:
            m_clientReady = true;
            sendControl(identity, pb::proto_SessionControlSignal::FINALIZE);
            break;
        default:
            break;
    }
}

void MockRuntime::handleData(const Envelope& env) {
    using namespace HP::Omnicept;
    switch (env.type) {
        case MessageType::subscriptionList: {
            auto list = detail::decodeSubscriptionList(env.body);
            std::vector<Abi::SubscriptionResult> results;
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                m_subscribed.clear();
                for (const auto& s : list.getSubscriptions()) {
                    m_subscribed.push_back(s.getType());
                    Abi::SubscriptionResult r;
                    r.result = Abi::SubscriptionResult::Result::APPROVED;
                    r.error = Abi::SubscriptionResult::Error::SUCCESS_NO_ERROR;
                    r.subscription = s;
                    results.push_back(r);
                }
            }
            sendData(MessageType::subscriptionResultList, detail::encodeSubscriptionResults(results));
            break;
        }
        case MessageType::dataVaultAction: {
            bool start = detail::decodeDataVaultActionIsStart(env.body);
            Abi::DataVaultResult r(start ? Abi::DataVaultResultType::RECORDING_STARTED
                                         : Abi::DataVaultResultType::RECORDING_STOPPED,
                                   Abi::DataVaultResultErrorType::SUCCESS_NO_ERROR, "session-1");
            sendData(MessageType::dataVaultResult, detail::encodeDataVaultResult(r));
            break;
        }
        case MessageType::moduleControlSignal:
            if (detail::decodeModuleControlSignal(env.body) == Abi::ModuleControlSignalType::MODULE_SIGNAL_STOP)
                m_clientSentStop = true;
            break;
        default:
            break;
    }
}

void MockRuntime::sendData(MessageType type, const std::string& body) {
    // Like the real runtime, only forward sensor data the client subscribed to.
    bool control = type == MessageType::subscriptionResultList || type == MessageType::dataVaultResult ||
                   type == MessageType::moduleControlSignal;
    if (!control) {
        std::lock_guard<std::mutex> lock(m_mutex);
        bool wanted = false;
        for (auto t : m_subscribed) wanted |= (t == type);
        if (!wanted) return;
    }
    Envelope env;
    env.type = type;
    env.sender = "mock-runtime";
    env.sensorInfo = HP::Omnicept::Abi::SensorInfo("mock-sensor", "0", "head");
    env.body = body;
    HP::Omnicept::detail::sendEnvelope(m_out, env, true);
}

void MockRuntime::sendHeartRate(uint32_t bpm) {
    HP::Omnicept::Abi::HeartRate hr;
    hr.rate = bpm;
    hr.timestamp.omniceptTimeMicroSeconds = 1234567;
    std::lock_guard<std::mutex> lock(m_mutex);
    m_outbox.emplace_back(MessageType::heartRate, HP::Omnicept::detail::encodeHeartRate(hr));
}

void MockRuntime::sendEyeTracking(float combinedX) {
    HP::Omnicept::Abi::EyeTracking et;
    et.combinedGaze = HP::Omnicept::Abi::EyeGaze(combinedX, 0.25f, 1.0f);
    et.leftPupilDilation = 3.5f;
    std::lock_guard<std::mutex> lock(m_mutex);
    m_outbox.emplace_back(MessageType::eyeTracking, HP::Omnicept::detail::encodeEyeTracking(et));
}

void MockRuntime::sendIMUFrame(size_t samples) {
    HP::Omnicept::Abi::IMUFrame frame;
    for (size_t i = 0; i < samples; ++i)
        frame.data.emplace_back(HP::Omnicept::Abi::IMU3AxisValues(float(i), 0, 9.81f),
                                HP::Omnicept::Abi::IMU3AxisValues(0, 0, 0));
    std::lock_guard<std::mutex> lock(m_mutex);
    m_outbox.emplace_back(MessageType::imuFrame, HP::Omnicept::detail::encodeIMUFrame(frame));
}

void MockRuntime::sendStop() {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_outbox.emplace_back(MessageType::moduleControlSignal,
                          HP::Omnicept::detail::encodeModuleControlSignal(
                              HP::Omnicept::Abi::ModuleControlSignalType::MODULE_SIGNAL_STOP));
}

std::string MockRuntime::lastClientName() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_clientName;
}

std::string MockRuntime::lastClientId() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_clientId;
}

std::vector<MessageType> MockRuntime::subscribedTypes() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_subscribed;
}
