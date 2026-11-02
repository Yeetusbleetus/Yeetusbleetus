// Connects to the Omnicept runtime and prints heart rate, eye tracking and
// cognitive load until Enter is pressed.
//
//   heart_rate_monitor --clientId <id> --accessKey <key> --license revshare
//   heart_rate_monitor                     (Core license, no credentials)

#include <iostream>
#include <string>

#include "omnicept/Glia.h"

using namespace HP::Omnicept;

int main(int argc, char** argv) {
    auto license = SessionLicenseHelper::fromArgs(argc, argv);

    auto subscriptions = Abi::SubscriptionList::ForTypes(
        {Abi::MessageType::heartRate, Abi::MessageType::eyeTracking, Abi::MessageType::cognitiveLoad});

    auto builder = Glia::StartBuildClient_Async(
        "heart_rate_monitor", std::move(license), subscriptions, [](Client::State state) {
            const char* names[] = {"PAUSED", "RUNNING", "DISCONNECTED"};
            std::cout << "[state] " << names[static_cast<int>(state)] << std::endl;
        });

    std::cout << "Connecting to the HP Omnicept runtime..." << std::endl;
    auto build = ClientBuildHelpers::finishBuild(builder);
    if (!build.client) {
        std::cerr << "Could not connect: " << build.errorMsg << std::endl;
        return 1;
    }
    auto& client = build.client;

    client->setSubscriptionResultCallback([](const std::vector<Abi::SubscriptionResult>& results) {
        for (const auto& r : results)
            std::cout << "[subscription] " << Abi::MessageTypeUtils::toString(r.subscription.getType())
                      << " result=" << static_cast<int>(r.result) << " error=" << static_cast<int>(r.error)
                      << std::endl;
    });
    client->registerCallback<Abi::HeartRate>([](std::shared_ptr<Abi::HeartRate> hr) {
        std::cout << hr->toString() << std::endl;
    });
    client->registerCallback<Abi::EyeTracking>([](std::shared_ptr<Abi::EyeTracking> et) {
        std::cout << et->toString() << std::endl;
    });
    client->registerCallback<Abi::CognitiveLoad>([](std::shared_ptr<Abi::CognitiveLoad> cl) {
        std::cout << cl->toString() << std::endl;
    });

    client->startClient();
    std::cout << "Receiving data. Press Enter to quit." << std::endl;
    std::string line;
    std::getline(std::cin, line);
    client->disconnectClient();
    return 0;
}
