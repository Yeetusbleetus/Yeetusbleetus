#include "Connection.h"

#include <random>
#include <sstream>
#include <stdexcept>
#include <iomanip>

#include "omnicept/abi/Errors.h"

#include "SessionControlSignal.pb.h"

namespace pb = HP::Omnicept::Abi;

namespace HP { namespace Omnicept { namespace detail {

using Abi::MessageType;

void sendEnvelope(zmq::socket_t& socket, const Envelope& env, bool multipart) {
    std::string header = encodeHeader(env);
    try {
        if (multipart) {
            socket.send(zmq::buffer(header), zmq::send_flags::sndmore);
            socket.send(zmq::buffer(env.body), zmq::send_flags::none);
        } else {
            socket.send(zmq::buffer(header + env.body), zmq::send_flags::none);
        }
    } catch (const zmq::error_t& e) {
        throw Abi::TransportError(std::string("send failed: ") + e.what());
    }
}

bool receiveEnvelope(zmq::socket_t& socket, Envelope& out, bool multipart, std::chrono::milliseconds timeout) {
    zmq::pollitem_t item{static_cast<void*>(socket), 0, ZMQ_POLLIN, 0};
    try {
        if (zmq::poll(&item, 1, timeout) <= 0 || !(item.revents & ZMQ_POLLIN)) return false;

        std::vector<zmq::message_t> frames;
        do {
            zmq::message_t frame;
            if (!socket.recv(frame, zmq::recv_flags::none)) return false;
            frames.push_back(std::move(frame));
        } while (frames.back().more());

        // Drop any routing/delimiter frames in front of the header+body pair.
        if (multipart) {
            if (frames.size() < 2) throw Abi::ProtocolError("expected header and body frames");
            const auto& h = frames[frames.size() - 2];
            const auto& b = frames.back();
            out = decodeHeader(h.to_string());
            out.body = b.to_string();
        } else {
            // A serialized PackageDeclaration is not self-delimiting, so a
            // concatenated header+body cannot be split without knowing more
            // about the runtime's framing.
            throw Abi::ProtocolError("receiving with multipartFraming=false is not supported");
        }
    } catch (const zmq::error_t& e) {
        throw Abi::TransportError(std::string("receive failed: ") + e.what());
    }
    return true;
}

std::string makeUuid() {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> dist;
    uint64_t hi = dist(gen), lo = dist(gen);
    hi = (hi & 0xFFFFFFFFFFFF0FFFULL) | 0x0000000000004000ULL;  // version 4
    lo = (lo & 0x3FFFFFFFFFFFFFFFULL) | 0x8000000000000000ULL;  // RFC 4122 variant
    std::ostringstream ss;
    ss << std::hex << std::setfill('0') << std::setw(8) << (hi >> 32) << '-' << std::setw(4)
       << ((hi >> 16) & 0xFFFF) << '-' << std::setw(4) << (hi & 0xFFFF) << '-' << std::setw(4) << (lo >> 48)
       << '-' << std::setw(12) << (lo & 0xFFFFFFFFFFFFULL);
    return ss.str();
}

namespace {

pb::proto_SessionControlSignal_LicensingModel toProto(Abi::LicensingModel m) {
    return static_cast<pb::proto_SessionControlSignal_LicensingModel>(static_cast<int>(m));
}

Envelope controlEnvelope(const pb::proto_SessionControlSignal& sig, const std::string& sender, uint32_t version) {
    Envelope env;
    env.type = MessageType::sessionControlSignal;
    env.version = version;
    env.sender = sender;
    if (!sig.SerializeToString(&env.body)) throw Abi::SerializationError("could not serialize SessionControlSignal");
    return env;
}

}  // namespace

std::unique_ptr<Connection> Connection::open(const ProtocolConfig& config, const std::string& clientName,
                                             const Abi::SessionLicense& license) {
    if (clientName.empty()) throw std::invalid_argument("clientName must not be empty");
    if (license.getRequestedLicense() == Abi::LicensingModel::UNKNOWN)
        throw std::invalid_argument("requested license model must not be UNKNOWN");
    if (license.getRequestedLicense() != Abi::LicensingModel::CORE &&
        (license.getClientId().empty() || license.getAccessKey().empty()))
        throw std::invalid_argument("only CORE licenses can be used without a clientId and accessKey");

    std::unique_ptr<Connection> conn(new Connection(config));
    const std::string uuid = makeUuid();
    // [guess] format of the connection identifier: "<name>_<uuid>".
    conn->m_connectionId = clientName + "_" + uuid;

    zmq::socket_t hs(conn->m_context, static_cast<int>(config.handshakeSocketType));
    hs.set(zmq::sockopt::linger, 0);
    try {
        hs.connect(config.handshakeUri());
    } catch (const zmq::error_t& e) {
        throw Abi::TransportError("cannot connect to " + config.handshakeUri() + ": " + e.what());
    }

    pb::proto_SessionControlSignal connect;
    connect.set_signal(pb::proto_SessionControlSignal::CONNECT);
    connect.set_connectionname(clientName);
    connect.set_connectionid(conn->m_connectionId);
    connect.set_endpointuuid(uuid);
    connect.set_endpointabiversion(config.endpointAbiVersion);
    for (auto v : config.handshakeVersions) connect.add_handshakeversions(v);
    auto* lic = connect.mutable_sessionlicense();
    lic->set_clientid(license.getClientId());
    lic->set_accesskey(license.getAccessKey());
    lic->set_requestedlicense(toProto(license.getRequestedLicense()));
    lic->set_isrunningineditor(license.getIsRunningInEditor());
    sendEnvelope(hs, controlEnvelope(connect, conn->m_connectionId, config.messageVersion), config.multipartFraming);

    const auto deadline = std::chrono::steady_clock::now() + config.handshakeTimeout;
    bool heardFromRuntime = false;
    bool accepted = false;

    while (true) {
        auto remaining = std::chrono::duration_cast<std::chrono::milliseconds>(deadline - std::chrono::steady_clock::now());
        if (remaining.count() <= 0) {
            if (!heardFromRuntime)
                throw Abi::TransportError("no response from the Omnicept runtime at " + config.handshakeUri() +
                                          " (is it running? see ProtocolConfig if it is)");
            throw Abi::HandshakeError("handshake timed out after the runtime responded");
        }

        Envelope env;
        if (!receiveEnvelope(hs, env, config.multipartFraming, remaining)) continue;
        heardFromRuntime = true;
        if (env.type != MessageType::sessionControlSignal)
            throw Abi::ProtocolError("unexpected message type " + Abi::MessageTypeUtils::toString(env.type) +
                                     " during handshake");

        pb::proto_SessionControlSignal sig;
        if (!sig.ParseFromString(env.body)) throw Abi::SerializationError("could not parse SessionControlSignal");

        switch (sig.signal()) {
            case pb::proto_SessionControlSignal::ACCEPT: {
                const std::string& sendUri = config.sendOnEndpointInUri ? sig.endpointinuri() : sig.endpointouturi();
                const std::string& recvUri = config.sendOnEndpointInUri ? sig.endpointouturi() : sig.endpointinuri();
                if (sendUri.empty() || recvUri.empty())
                    throw Abi::ProtocolError("ACCEPT did not include data endpoints");
                try {
                    conn->m_sendSocket = std::make_unique<zmq::socket_t>(conn->m_context, zmq::socket_type::pair);
                    conn->m_recvSocket = std::make_unique<zmq::socket_t>(conn->m_context, zmq::socket_type::pair);
                    conn->m_sendSocket->set(zmq::sockopt::linger, 0);
                    conn->m_recvSocket->set(zmq::sockopt::linger, 0);
                    conn->m_sendSocket->connect(sendUri);
                    conn->m_recvSocket->connect(recvUri);
                } catch (const zmq::error_t& e) {
                    throw Abi::TransportError(std::string("cannot connect data endpoints: ") + e.what());
                }
                accepted = true;
                pb::proto_SessionControlSignal ready;
                ready.set_signal(pb::proto_SessionControlSignal::CLIENT_READY);
                ready.set_connectionid(conn->m_connectionId);
                sendEnvelope(hs, controlEnvelope(ready, conn->m_connectionId, config.messageVersion),
                             config.multipartFraming);
                break;
            }
            case pb::proto_SessionControlSignal::LICENSE_REQUEST_VALIDATION: {
                // [guess] the runtime asks for the license again; answer with it.
                pb::proto_SessionControlSignal reply;
                reply.set_signal(pb::proto_SessionControlSignal::LICENSE_REQUEST_VALIDATION);
                reply.set_connectionid(conn->m_connectionId);
                *reply.mutable_sessionlicense() = connect.sessionlicense();
                sendEnvelope(hs, controlEnvelope(reply, conn->m_connectionId, config.messageVersion),
                             config.multipartFraming);
                break;
            }
            case pb::proto_SessionControlSignal::LICENSE_ACCEPT_VALIDATION:
                break;
            case pb::proto_SessionControlSignal::REJECT:
                throw Abi::HandshakeError("runtime rejected the connection: " +
                                          (sig.reasonforrejection().empty() ? std::string("(no reason given)")
                                                                            : sig.reasonforrejection()));
            case pb::proto_SessionControlSignal::FINALIZE:
                if (!accepted) throw Abi::ProtocolError("FINALIZE received before ACCEPT");
                return conn;
            default:
                throw Abi::ProtocolError("unexpected session signal " + std::to_string(sig.signal()));
        }
    }
}

Connection::~Connection() { close(); }

void Connection::send(MessageType type, const std::string& body) {
    std::lock_guard<std::mutex> lock(m_sendMutex);
    if (!m_sendSocket) throw Abi::ConnectionError("connection is closed");
    Envelope env;
    env.type = type;
    env.version = m_config.messageVersion;
    env.sender = m_connectionId;
    env.body = body;
    sendEnvelope(*m_sendSocket, env, m_config.multipartFraming);
}

bool Connection::receive(Envelope& out, std::chrono::milliseconds timeout) {
    // Only the client's worker thread calls this, so the receive socket has a
    // single owner (ZeroMQ sockets are not thread-safe).
    if (!m_recvSocket) return false;
    return receiveEnvelope(*m_recvSocket, out, m_config.multipartFraming, timeout);
}

void Connection::closeSend() {
    std::lock_guard<std::mutex> lock(m_sendMutex);
    m_sendSocket.reset();
}

void Connection::closeReceive() { m_recvSocket.reset(); }

void Connection::close() {
    closeSend();
    closeReceive();
}

}}}  // namespace HP::Omnicept::detail
