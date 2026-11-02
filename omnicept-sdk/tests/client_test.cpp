// End-to-end tests of the SDK against MockRuntime.

#include <chrono>
#include <condition_variable>
#include <cstdio>
#include <functional>
#include <mutex>
#include <string>
#include <thread>

#include "MockRuntime.h"
#include "omnicept/Glia.h"

using namespace HP::Omnicept;
using namespace std::chrono_literals;

static int g_failures = 0;
#define CHECK(cond)                                                                 \
    do {                                                                            \
        if (!(cond)) {                                                              \
            std::fprintf(stderr, "  CHECK failed: %s (%s:%d)\n", #cond, __FILE__, __LINE__); \
            ++g_failures;                                                           \
        }                                                                           \
    } while (0)

// Poll until `pred` is true or the timeout expires.
static bool waitFor(const std::function<bool()>& pred, std::chrono::milliseconds timeout = 3000ms) {
    auto deadline = std::chrono::steady_clock::now() + timeout;
    while (std::chrono::steady_clock::now() < deadline) {
        if (pred()) return true;
        std::this_thread::sleep_for(5ms);
    }
    return pred();
}

static ProtocolConfig configFor(const MockRuntime& rt) {
    ProtocolConfig c;
    c.host = "127.0.0.1";
    c.port = rt.port();
    c.handshakeTimeout = 2000ms;
    return c;
}

static std::unique_ptr<Abi::SessionLicense> devLicense(const std::string& clientId = "my-client") {
    return std::make_unique<Abi::SessionLicense>(clientId, "my-key", Abi::LicensingModel::REV_SHARE, false);
}

static void test_connect_subscribe_and_receive() {
    MockRuntime rt({});
    std::mutex m;
    std::vector<Client::State> states;
    auto client = Glia::BuildClient(
        "test-app", devLicense(),
        Abi::SubscriptionList::ForTypes({Abi::MessageType::heartRate, Abi::MessageType::eyeTracking,
                                         Abi::MessageType::imuFrame}),
        [&](Client::State s) { std::lock_guard<std::mutex> l(m); states.push_back(s); }, configFor(rt));

    CHECK(client != nullptr);
    CHECK(client->getClientState() == Client::State::PAUSED);
    CHECK(rt.lastClientName() == "test-app");
    CHECK(rt.lastClientId() == "my-client");
    CHECK(waitFor([&] { return rt.subscribedTypes().size() == 3; }));

    std::atomic<uint32_t> lastRate{0};
    std::atomic<int> eyeCount{0};
    std::atomic<size_t> imuSamples{0};
    CHECK(client->registerCallback<Abi::HeartRate>([&](std::shared_ptr<Abi::HeartRate> hr) {
        lastRate = hr->rate;
    }) == Client::Result::SUCCESS);
    CHECK(client->registerCallback<Abi::EyeTracking>([&](std::shared_ptr<Abi::EyeTracking> et) {
        if (et->combinedGaze.x == 0.5f && et->leftPupilDilation == 3.5f) ++eyeCount;
    }) == Client::Result::SUCCESS);
    CHECK(client->registerCallback<Abi::IMUFrame>([&](std::shared_ptr<Abi::IMUFrame> f) {
        imuSamples = f->data.size();
    }) == Client::Result::SUCCESS);
    CHECK(client->isCallbackRegisteredForType<Abi::HeartRate>());
    CHECK(!client->isCallbackRegisteredForType<Abi::CognitiveLoad>());

    // Paused: nothing is delivered or cached.
    rt.sendHeartRate(60);
    std::this_thread::sleep_for(200ms);
    CHECK(lastRate == 0);
    CHECK(!client->getLastData<Abi::HeartRate>().valid);

    CHECK(client->startClient() == Client::Result::SUCCESS);
    CHECK(client->startClient() == Client::Result::NO_OP_CLIENT_RUNNING);
    rt.sendHeartRate(72);
    rt.sendEyeTracking(0.5f);
    rt.sendIMUFrame(4);
    CHECK(waitFor([&] { return lastRate == 72 && eyeCount == 1 && imuSamples == 4; }));

    auto lvc = client->getLastData<Abi::HeartRate>();
    CHECK(lvc.valid);
    CHECK(lvc.data.rate == 72);
    CHECK(lvc.data.timestamp.omniceptTimeMicroSeconds == 1234567);
    CHECK(lvc.data.sensorInfo.deviceId.id == "mock-sensor");

    CHECK(client->pauseClient() == Client::Result::SUCCESS);
    CHECK(client->pauseClient() == Client::Result::NO_OP_CLIENT_PAUSED);

    CHECK(client->disconnectClient() == Client::Result::SUCCESS);
    CHECK(client->getClientState() == Client::State::DISCONNECTED);
    CHECK(client->disconnectClient() == Client::Result::ERROR_CLIENT_DISCONNECTED);
    CHECK(client->startClient() == Client::Result::ERROR_CLIENT_DISCONNECTED);
    CHECK(waitFor([&] { return rt.clientSentStop(); }));

    std::lock_guard<std::mutex> l(m);
    CHECK(states.size() == 3);  // RUNNING, PAUSED, DISCONNECTED
    if (states.size() == 3) {
        CHECK(states[0] == Client::State::RUNNING);
        CHECK(states[1] == Client::State::PAUSED);
        CHECK(states[2] == Client::State::DISCONNECTED);
    }
}

static void test_unsubscribed_types_are_not_delivered() {
    MockRuntime rt({});
    auto client = Glia::BuildClient("test-app", devLicense(),
                                    Abi::SubscriptionList::ForTypes({Abi::MessageType::eyeTracking}), nullptr,
                                    configFor(rt));
    CHECK(waitFor([&] { return rt.subscribedTypes().size() == 1; }));
    std::atomic<int> hrCount{0};
    client->registerCallback<Abi::HeartRate>([&](std::shared_ptr<Abi::HeartRate>) { ++hrCount; });
    client->startClient();
    rt.sendHeartRate(80);
    std::this_thread::sleep_for(200ms);
    CHECK(hrCount == 0);

    // Changing subscriptions at runtime.
    std::atomic<int> approved{0};
    client->setSubscriptionResultCallback([&](const std::vector<Abi::SubscriptionResult>& results) {
        for (const auto& r : results)
            if (r.result == Abi::SubscriptionResult::Result::APPROVED) ++approved;
    });
    CHECK(client->setSubscriptions(Abi::SubscriptionList::ForTypes({Abi::MessageType::heartRate})) ==
          Client::Result::SUCCESS);
    CHECK(waitFor([&] { return approved == 1; }));
    rt.sendHeartRate(81);
    CHECK(waitFor([&] { return hrCount == 1; }));
}

static void test_data_vault() {
    MockRuntime rt({});
    auto client = Glia::BuildClient("test-app", devLicense(), Abi::SubscriptionList::GetSubscriptionListToNone(),
                                    nullptr, configFor(rt));
    std::atomic<int> started{0}, stopped{0};
    auto cb = [&](std::shared_ptr<Abi::DataVaultResult> r) {
        if (r->m_result == Abi::DataVaultResultType::RECORDING_STARTED) ++started;
        if (r->m_result == Abi::DataVaultResultType::RECORDING_STOPPED) ++stopped;
    };
    CHECK(client->startDataRecord(cb) == Client::Result::NO_OP_CLIENT_PAUSED);
    client->startClient();
    CHECK(client->startDataRecord(nullptr) == Client::Result::UNSPECIFIED_ERROR);
    CHECK(client->startDataRecord(cb) == Client::Result::SUCCESS);
    CHECK(waitFor([&] { return started == 1; }));
    CHECK(client->stopDataRecord() == Client::Result::SUCCESS);
    CHECK(waitFor([&] { return stopped == 1; }));
}

static void test_runtime_initiated_disconnect() {
    MockRuntime rt({});
    std::atomic<bool> sawDisconnect{false};
    auto client = Glia::BuildClient(
        "test-app", devLicense(), Abi::SubscriptionList::GetSubscriptionListToNone(),
        [&](Client::State s) { if (s == Client::State::DISCONNECTED) sawDisconnect = true; }, configFor(rt));
    client->startClient();
    rt.sendStop();
    CHECK(waitFor([&] { return client->getClientState() == Client::State::DISCONNECTED; }));
    CHECK(sawDisconnect);
    CHECK(client->registerCallback<Abi::HeartRate>([](std::shared_ptr<Abi::HeartRate>) {}) ==
          Client::Result::ERROR_CLIENT_DISCONNECTED);
}

static void test_rejected_license() {
    MockRuntime::Options opt;
    opt.rejectClientId = "bad-client";
    MockRuntime rt(opt);
    auto builder = Glia::StartBuildClient_Async("test-app", devLicense("bad-client"),
                                                Abi::SubscriptionList::GetSubscriptionListToNone(), nullptr,
                                                configFor(rt));
    CHECK(builder.isValid());
    auto result = ClientBuildHelpers::finishBuild(builder);
    CHECK(result.client == nullptr);
    CHECK(result.errorMsg.find("invalid license") != std::string::npos);
    CHECK(!builder.isValid());
    bool threw = false;
    try {
        builder.getBuildClientResultOrThrow();
    } catch (const std::logic_error&) {
        threw = true;
    }
    CHECK(threw);
}

static void test_no_runtime() {
    ProtocolConfig c;
    c.host = "127.0.0.1";
    c.port = 1;  // nothing listens here
    c.handshakeTimeout = 300ms;
    bool transportError = false;
    try {
        Glia::BuildClient("test-app", devLicense(), Abi::SubscriptionList::GetSubscriptionListToNone(), nullptr, c);
    } catch (const Abi::TransportError&) {
        transportError = true;
    }
    CHECK(transportError);
}

static void test_license_validation() {
    bool invalid = false;
    try {
        // Non-core licenses need credentials; this is checked before connecting.
        Glia::BuildClient("test-app",
                          std::make_unique<Abi::SessionLicense>("", "", Abi::LicensingModel::ENTERPRISE, false),
                          Abi::SubscriptionList::GetSubscriptionListToNone(), nullptr, ProtocolConfig{});
    } catch (const std::invalid_argument&) {
        invalid = true;
    }
    CHECK(invalid);
}

int main() {
    struct { const char* name; void (*fn)(); } tests[] = {
        {"connect, subscribe and receive", test_connect_subscribe_and_receive},
        {"unsubscribed types are not delivered", test_unsubscribed_types_are_not_delivered},
        {"data vault", test_data_vault},
        {"runtime-initiated disconnect", test_runtime_initiated_disconnect},
        {"rejected license", test_rejected_license},
        {"no runtime", test_no_runtime},
        {"license validation", test_license_validation},
    };
    for (auto& t : tests) {
        int before = g_failures;
        t.fn();
        std::printf("%s %s\n", g_failures == before ? "PASS" : "FAIL", t.name);
    }
    std::printf("%d failure(s)\n", g_failures);
    return g_failures == 0 ? 0 : 1;
}
