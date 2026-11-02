#pragma once
// A stand-in for the Omnicept runtime that speaks the SDK's assumed protocol
// (see ProtocolConfig.h). It exists to test the SDK end to end; agreeing with
// this mock says nothing about agreeing with HP's real runtime.

#include <atomic>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include <zmq.hpp>

#include "Codec.h"
#include "Connection.h"

class MockRuntime {
public:
    struct Options {
        uint16_t port = 0;  // 0 = pick a free port
        std::string rejectClientId;  // reject CONNECTs carrying this clientId
        bool sendLicenseValidation = true;
    };

    explicit MockRuntime(Options options);
    ~MockRuntime();

    uint16_t port() const { return m_port; }

    // Data pushed to the client once it is connected and subscribed.
    void sendHeartRate(uint32_t bpm);
    void sendEyeTracking(float combinedX);
    void sendIMUFrame(size_t samples);
    void sendStop();

    // Observations.
    std::string lastClientName() const;
    std::string lastClientId() const;
    std::vector<HP::Omnicept::Abi::MessageType> subscribedTypes() const;
    bool clientSentStop() const { return m_clientSentStop; }
    bool clientConnected() const { return m_clientReady; }

private:
    void loop();
    void handleHandshake(const std::string& identity, const HP::Omnicept::detail::Envelope& env);
    void handleData(const HP::Omnicept::detail::Envelope& env);
    void sendData(HP::Omnicept::Abi::MessageType type, const std::string& body);
    void sendControl(const std::string& identity, int signal, const std::string& reason = {});

    Options m_options;
    zmq::context_t m_ctx{1};
    zmq::socket_t m_router{m_ctx, zmq::socket_type::router};
    zmq::socket_t m_in{m_ctx, zmq::socket_type::pair};   // client -> runtime
    zmq::socket_t m_out{m_ctx, zmq::socket_type::pair};  // runtime -> client
    std::string m_inUri, m_outUri;
    uint16_t m_port = 0;

    std::thread m_thread;
    std::atomic<bool> m_running{true};
    std::atomic<bool> m_clientReady{false};
    std::atomic<bool> m_clientSentStop{false};

    mutable std::mutex m_mutex;  // guards the fields below and m_out sends
    std::string m_clientName, m_clientId;
    std::vector<HP::Omnicept::Abi::MessageType> m_subscribed;
    std::vector<std::pair<HP::Omnicept::Abi::MessageType, std::string>> m_outbox;
};
