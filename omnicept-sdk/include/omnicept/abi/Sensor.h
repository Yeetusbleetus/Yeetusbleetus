#pragma once

#include <cstdint>
#include <string>
#include <tuple>

namespace HP { namespace Omnicept { namespace Abi {

class SensorDeviceId {
public:
    std::string id;
    std::string subId;

    SensorDeviceId() = default;
    SensorDeviceId(const std::string& id, const std::string& subId) : id(id), subId(subId) {}
    virtual ~SensorDeviceId() = default;

    bool operator==(const SensorDeviceId& other) const { return id == other.id && subId == other.subId; }
    bool operator<(const SensorDeviceId& rhs) const { return std::tie(id, subId) < std::tie(rhs.id, rhs.subId); }
};

class SensorInfo {
public:
    SensorDeviceId deviceId;
    std::string location;

    SensorInfo() = default;
    SensorInfo(const SensorDeviceId& deviceId, const std::string& location) : deviceId(deviceId), location(location) {}
    SensorInfo(const std::string& id, const std::string& subid, const std::string& location)
        : deviceId(id, subid), location(location) {}
    virtual ~SensorInfo() = default;

    bool operator==(const SensorInfo& other) const { return deviceId == other.deviceId && location == other.location; }
    bool operator<(const SensorInfo& rhs) const {
        return std::tie(deviceId, location) < std::tie(rhs.deviceId, rhs.location);
    }
    bool empty() const { return deviceId.id.empty() && deviceId.subId.empty() && location.empty(); }
};

// All three clocks, in microseconds.
class Timestamp {
public:
    int64_t systemTimeMicroSeconds = 0;
    int64_t hardwareTimeMicroSeconds = 0;
    int64_t omniceptTimeMicroSeconds = 0;

    Timestamp() = default;
    virtual ~Timestamp() = default;

    bool operator==(const Timestamp& other) const {
        return systemTimeMicroSeconds == other.systemTimeMicroSeconds &&
               hardwareTimeMicroSeconds == other.hardwareTimeMicroSeconds &&
               omniceptTimeMicroSeconds == other.omniceptTimeMicroSeconds;
    }
};

}}}  // namespace HP::Omnicept::Abi
