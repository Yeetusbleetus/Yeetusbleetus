#pragma once

#include <cstdint>
#include <string>

namespace HP { namespace Omnicept { namespace Abi {

// Numeric ids carried in PackageDeclaration.messageType. The names follow the
// documented MessageType enum; the numeric values were recovered from the
// runtime's id table (ids 7 and 8 are unused there).
enum class MessageType : uint32_t {
    null = 0,
    declaration = 1,
    testPackage = 2,
    heartRate = 3,
    heartRateFrame = 4,
    sessionControlSignal = 5,
    moduleControlSignal = 6,
    eyeTracking = 9,
    eyeTrackingFrame = 10,
    backpackColors = 11,
    battery = 12,
    sync = 13,
    eyePupillometry = 14,
    eyePupillometryFrame = 15,
    byteMessage = 16,
    ppg = 17,
    ppgFrame = 18,
    expression = 19,
    expressionFrame = 20,
    cognitiveLoad = 21,
    cognitiveLoadInputFeature = 22,
    timestamp = 23,
    subscriptionList = 24,
    connectionParameter = 25,
    facialEmg = 26,
    facialEmgFrame = 27,
    vsync = 28,
    sceneColor = 29,
    sceneColorFrame = 30,
    dataVaultAction = 31,
    dataVaultResult = 32,
    connectionStatusSignal = 33,
    connectionInfo = 34,
    connectionInfoQuery = 35,
    heartRateVariability = 36,
    cameraImage = 37,
    imu = 38,
    imuFrame = 39,
    audio = 40,
    audioFrame = 41,
    subscriptionResultList = 42,
    subscriptionAuth = 43,
};

class MessageTypeUtils {
public:
    MessageTypeUtils() = delete;
    static std::string toString(MessageType type);
    static uint32_t toUint(MessageType type) { return static_cast<uint32_t>(type); }
};

}}}  // namespace HP::Omnicept::Abi
