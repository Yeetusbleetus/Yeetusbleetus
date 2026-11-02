#include "omnicept/Glia.h"

#include <cstring>
#include <thread>

#include "Connection.h"

namespace HP { namespace Omnicept {

bool Glia::AsyncClientBuilder::isClientBuildFinished() const {
    return m_valid && m_future.valid() &&
           m_future.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
}

void Glia::AsyncClientBuilder::waitForConnection() {
    if (!m_valid) throw std::logic_error("AsyncClientBuilder is no longer valid");
    m_future.wait();
}

std::unique_ptr<Client> Glia::AsyncClientBuilder::getBuildClientResultOrThrow() {
    if (!m_valid) throw std::logic_error("AsyncClientBuilder is no longer valid");
    m_valid = false;
    return m_future.get();
}

Glia::AsyncClientBuilder Glia::StartBuildClient_Async(const std::string& clientName,
                                                      std::unique_ptr<Abi::SessionLicense> license,
                                                      const Abi::SubscriptionList& subscriptions,
                                                      Client::StateCallback_T stateCallback, ProtocolConfig config) {
    // A promise + detached thread (rather than std::async) so that destroying
    // the builder never blocks on an unfinished connection attempt.
    auto promise = std::make_shared<std::promise<std::unique_ptr<Client>>>();
    std::future<std::unique_ptr<Client>> future = promise->get_future();

    std::shared_ptr<Abi::SessionLicense> lic(std::move(license));
    std::thread([promise, clientName, lic, subscriptions, stateCallback, config]() mutable {
        try {
            if (!lic) throw std::invalid_argument("license must not be null");
            if (config.connectionName.empty() || config.connectionName == ProtocolConfig().connectionName)
                config.connectionName = clientName;
            auto connection = detail::Connection::open(config, config.connectionName, *lic);
            std::unique_ptr<Client> client(new Client(std::move(connection), std::move(stateCallback)));
            client->start();  // worker thread; the client itself stays PAUSED
            client->setSubscriptions(subscriptions);
            promise->set_value(std::move(client));
        } catch (...) {
            promise->set_exception(std::current_exception());
        }
    }).detach();

    return AsyncClientBuilder(std::move(future));
}

std::unique_ptr<Client> Glia::BuildClient(const std::string& clientName, std::unique_ptr<Abi::SessionLicense> license,
                                          const Abi::SubscriptionList& subscriptions,
                                          Client::StateCallback_T stateCallback, ProtocolConfig config) {
    auto builder = StartBuildClient_Async(clientName, std::move(license), subscriptions, std::move(stateCallback),
                                          std::move(config));
    return builder.getBuildClientResultOrThrow();
}

}}  // namespace HP::Omnicept

ClientBuildHelpers::BuildResult ClientBuildHelpers::finishBuild(HP::Omnicept::Glia::AsyncClientBuilder& builder) {
    BuildResult result;
    try {
        result.client = builder.getBuildClientResultOrThrow();
    } catch (const HP::Omnicept::Abi::HandshakeError& e) {
        result.errorMsg = std::string("handshake failed: ") + e.what();
    } catch (const HP::Omnicept::Abi::TransportError& e) {
        result.errorMsg = std::string("could not reach the runtime: ") + e.what();
    } catch (const HP::Omnicept::Abi::ProtocolError& e) {
        result.errorMsg = std::string("protocol error: ") + e.what();
    } catch (const std::exception& e) {
        result.errorMsg = e.what();
    }
    return result;
}

std::unique_ptr<HP::Omnicept::Abi::SessionLicense> SessionLicenseHelper::fromArgs(int argc,
                                                                                    const char* const* argv) {
    using HP::Omnicept::Abi::LicensingModel;
    std::string clientId, accessKey, model = "core";
    bool editor = false;
    for (int i = 1; i < argc; ++i) {
        auto next = [&](std::string& dst) { if (i + 1 < argc) dst = argv[++i]; };
        if (!std::strcmp(argv[i], "--clientId")) next(clientId);
        else if (!std::strcmp(argv[i], "--accessKey")) next(accessKey);
        else if (!std::strcmp(argv[i], "--license")) next(model);
        else if (!std::strcmp(argv[i], "--editor")) editor = true;
    }
    LicensingModel m = LicensingModel::CORE;
    if (model == "trial") m = LicensingModel::TRIAL;
    else if (model == "enterprise") m = LicensingModel::ENTERPRISE;
    else if (model == "revshare" || model == "developer" || model == "academic") m = LicensingModel::REV_SHARE;
    return std::make_unique<HP::Omnicept::Abi::SessionLicense>(clientId, accessKey, m, editor);
}
