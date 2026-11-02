#pragma once
// Conversion between SDK domain types and the protobuf wire messages.

#include <memory>
#include <string>
#include <vector>

#include "omnicept/abi/DomainTypes.h"
#include "omnicept/abi/SessionLicense.h"
#include "omnicept/abi/Subscription.h"

namespace HP { namespace Omnicept { namespace detail {

// One message as it travels on the wire: a PackageDeclaration header plus the
// serialized body it describes.
struct Envelope {
    Abi::MessageType type = Abi::MessageType::null;
    uint32_t version = 0;
    std::string sender;
    std::string destination;
    Abi::SensorInfo sensorInfo;
    std::string body;
};

std::string encodeHeader(const Envelope& env);
// Throws Abi::SerializationError on malformed input. Fills everything but `body`.
Envelope decodeHeader(const std::string& bytes);

// Decode a body into a domain object. Returns nullptr for message types the
// SDK does not expose to callers. Throws Abi::SerializationError if the body
// does not parse.
std::shared_ptr<Abi::GenericMessage> decodeDomain(const Envelope& env);

std::string encodeSubscriptionList(const Abi::SubscriptionList& list);
std::vector<Abi::SubscriptionResult> decodeSubscriptionResults(const std::string& body);
std::string encodeDataVaultAction(bool start);
std::string encodeModuleControlSignal(Abi::ModuleControlSignalType signal);
Abi::ModuleControlSignalType decodeModuleControlSignal(const std::string& body);

// Encoders used by the mock runtime in tests.
std::string encodeHeartRate(const Abi::HeartRate& hr);
std::string encodeEyeTracking(const Abi::EyeTracking& et);
std::string encodeIMUFrame(const Abi::IMUFrame& frame);
std::string encodeDataVaultResult(const Abi::DataVaultResult& r);
std::string encodeSubscriptionResults(const std::vector<Abi::SubscriptionResult>& results);
Abi::SubscriptionList decodeSubscriptionList(const std::string& body);
bool decodeDataVaultActionIsStart(const std::string& body);

}}}  // namespace HP::Omnicept::detail
