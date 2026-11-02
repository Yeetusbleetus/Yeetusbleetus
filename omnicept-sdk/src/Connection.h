#pragma once
// Socket handling and the connection handshake.

#include <chrono>
#include <memory>
#include <mutex>
#include <string>

#include <zmq.hpp>

#include "Codec.h"
#include "omnicept/ProtocolConfig.h"
#include "omnicept/abi/SessionLicense.h"

namespace HP { namespace Omnicept { namespace detail {

// Send/receive one Envelope on a socket using the configured framing.
void sendEnvelope(zmq::socket_t& socket, const Envelope& env, bool multipart);
// Returns false if nothing arrived within `timeout`.
bool receiveEnvelope(zmq::socket_t& socket, Envelope& out, bool multipart, std::chrono::milliseconds timeout);

std::string makeUuid();

class Connection {
public:
    // Performs the handshake. Throws Abi::TransportError if the runtime cannot
    // be reached, Abi::HandshakeError if it rejects us, Abi::ProtocolError on
    // unexpected messages, std::invalid_argument for bad parameters.
    static std::unique_ptr<Connection> open(const ProtocolConfig& config, const std::string& clientName,
                                            const Abi::SessionLicense& license);

    ~Connection();

    // Thread-safe.
    void send(Abi::MessageType type, const std::string& body);
    // Must only be called from one thread (the client's worker).
    bool receive(Envelope& out, std::chrono::milliseconds timeout);
    void closeSend();     // thread-safe
    void closeReceive();  // call only from the receiving thread, or after it has stopped
    void close();

    const std::string& connectionId() const { return m_connectionId; }
    const ProtocolConfig& config() const { return m_config; }

private:
    Connection(const ProtocolConfig& config) : m_config(config) {}

    ProtocolConfig m_config;
    zmq::context_t m_context{1};
    std::mutex m_sendMutex;
    std::unique_ptr<zmq::socket_t> m_sendSocket;
    std::unique_ptr<zmq::socket_t> m_recvSocket;
    std::string m_connectionId;
};

}}}  // namespace HP::Omnicept::detail
