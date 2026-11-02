#pragma once

#include <chrono>
#include <cstdint>
#include <string>
#include <vector>

namespace HP { namespace Omnicept {

// Everything about the wire protocol that is NOT confirmed by HP's public
// documentation lives here, so it can be adjusted without touching the SDK.
//
// Confidence of each default (see README "Protocol assumptions"):
//   [recovered] read directly from data embedded in the runtime (schemas, ids)
//   [inferred]  strong indirect evidence, not observed on the wire
//   [guess]     no evidence; first thing to change if the handshake fails
struct ProtocolConfig {
    // [inferred] Endpoint the runtime listens on for new connections.
    std::string host = "localhost";
    uint16_t port = 13352;

    enum class SocketType { PAIR = 0, REQ = 3, DEALER = 5 };
    // [guess] ZeroMQ socket type used for the initial handshake.
    SocketType handshakeSocketType = SocketType::DEALER;

    // [inferred] After ACCEPT, data flows over ZeroMQ PAIR sockets connected to
    // the URIs the runtime returns. [guess] which URI the client sends to.
    bool sendOnEndpointInUri = true;

    // [guess] Handshake versions offered in the CONNECT signal.
    std::vector<uint32_t> handshakeVersions = {1};
    // [guess] ABI version string offered in the CONNECT signal.
    std::string endpointAbiVersion;
    // [guess] Value for PackageDeclaration.messageVersion on outgoing messages.
    uint32_t messageVersion = 0;

    // [guess] Each message is sent as a 2-frame ZeroMQ multipart:
    //   frame 0 = serialized PackageDeclaration (header), frame 1 = body.
    // When false, a single frame of header || body is used, and the header's
    // length is not self-describing, so this mode only works for receiving if
    // the runtime prefixes nothing else.
    bool multipartFraming = true;

    // Name this client reports to the runtime.
    std::string connectionName = "omnicept-sdk";

    std::chrono::milliseconds handshakeTimeout{5000};
    std::chrono::milliseconds pollInterval{50};

    std::string handshakeUri() const { return "tcp://" + host + ":" + std::to_string(port); }
};

}}  // namespace HP::Omnicept
