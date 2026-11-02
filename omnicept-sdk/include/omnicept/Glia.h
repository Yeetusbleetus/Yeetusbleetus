#pragma once

#include <future>
#include <memory>
#include <string>

#include "omnicept/Client.h"
#include "omnicept/ProtocolConfig.h"
#include "omnicept/abi/SessionLicense.h"
#include "omnicept/abi/Subscription.h"

namespace HP { namespace Omnicept {

// Entry point: connects to the runtime and hands back a Client.
class Glia {
public:
    Glia() = delete;

    // Single-use handle for a Client that is being built on a background thread.
    class AsyncClientBuilder {
    public:
        // True once the background build has finished (successfully or not).
        bool isClientBuildFinished() const;
        // True until getBuildClientResultOrThrow() has been called.
        bool isValid() const { return m_valid; }
        // Block until the background build finishes. Throws std::logic_error if invalid.
        void waitForConnection();
        // Block until finished, then return the Client or rethrow the build error
        // (Abi::HandshakeError, Abi::TransportError, Abi::ProtocolError,
        // std::invalid_argument). Invalidates the builder.
        std::unique_ptr<Client> getBuildClientResultOrThrow();

        // Does not wait for the background thread.
        ~AsyncClientBuilder() = default;
        AsyncClientBuilder(const AsyncClientBuilder&) = delete;
        AsyncClientBuilder& operator=(const AsyncClientBuilder&) = delete;
        AsyncClientBuilder(AsyncClientBuilder&&) = default;
        AsyncClientBuilder& operator=(AsyncClientBuilder&&) = default;

    private:
        friend class Glia;
        explicit AsyncClientBuilder(std::future<std::unique_ptr<Client>> future)
            : m_future(std::move(future)) {}

        std::future<std::unique_ptr<Client>> m_future;
        bool m_valid = true;
    };

    // Start connecting to the runtime in the background.
    //   clientName     - shown to the user/runtime; also used as the connection name
    //   license        - your HP credentials (or SessionLicense::Core())
    //   subscriptions  - initial subscriptions, sent once connected
    //   stateCallback  - called on the client's thread whenever its State changes
    //   config         - wire-protocol settings (see ProtocolConfig.h)
    static AsyncClientBuilder StartBuildClient_Async(const std::string& clientName,
                                                     std::unique_ptr<Abi::SessionLicense> license,
                                                     const Abi::SubscriptionList& subscriptions,
                                                     Client::StateCallback_T stateCallback,
                                                     ProtocolConfig config = {});

    // Synchronous convenience wrapper around StartBuildClient_Async.
    static std::unique_ptr<Client> BuildClient(const std::string& clientName,
                                               std::unique_ptr<Abi::SessionLicense> license,
                                               const Abi::SubscriptionList& subscriptions,
                                               Client::StateCallback_T stateCallback,
                                               ProtocolConfig config = {});
};

}}  // namespace HP::Omnicept

// Builds a Client and turns any exception into an error message.
class ClientBuildHelpers {
public:
    struct BuildResult {
        std::unique_ptr<HP::Omnicept::Client> client;  // nullptr on failure
        std::string errorMsg;                          // empty on success
    };

    static BuildResult finishBuild(HP::Omnicept::Glia::AsyncClientBuilder& builder);
};

// Reads license settings from command-line arguments:
//   --clientId <id> --accessKey <key> --license core|trial|enterprise|revshare [--editor]
// Falls back to a Core license when nothing is given.
class SessionLicenseHelper {
public:
    static std::unique_ptr<HP::Omnicept::Abi::SessionLicense> fromArgs(int argc, const char* const* argv);
};
