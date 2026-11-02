#include "omnicept/abi/DomainTypes.h"

#include "omnicept/abi/Subscription.h"

namespace HP { namespace Omnicept { namespace Abi {

std::string MessageTypeUtils::toString(MessageType type) {
    switch (type) {
#define CASE(n) case MessageType::n: return #n;
        CASE(null) CASE(declaration) CASE(testPackage) CASE(heartRate) CASE(heartRateFrame)
        CASE(sessionControlSignal) CASE(moduleControlSignal) CASE(eyeTracking) CASE(eyeTrackingFrame)
        CASE(backpackColors) CASE(battery) CASE(sync) CASE(eyePupillometry) CASE(eyePupillometryFrame)
        CASE(byteMessage) CASE(ppg) CASE(ppgFrame) CASE(expression) CASE(expressionFrame) CASE(cognitiveLoad)
        CASE(cognitiveLoadInputFeature) CASE(timestamp) CASE(subscriptionList) CASE(connectionParameter)
        CASE(facialEmg) CASE(facialEmgFrame) CASE(vsync) CASE(sceneColor) CASE(sceneColorFrame)
        CASE(dataVaultAction) CASE(dataVaultResult) CASE(connectionStatusSignal) CASE(connectionInfo)
        CASE(connectionInfoQuery) CASE(heartRateVariability) CASE(cameraImage) CASE(imu) CASE(imuFrame)
        CASE(audio) CASE(audioFrame) CASE(subscriptionResultList) CASE(subscriptionAuth)
#undef CASE
    }
    return "unknown(" + std::to_string(static_cast<uint32_t>(type)) + ")";
}

SubscriptionList SubscriptionList::ForTypes(const std::vector<MessageType>& types) {
    SubscriptionList list;
    for (auto t : types) list.m_subscriptions.emplace_back(t);
    return list;
}

SubscriptionList SubscriptionList::GetSubscriptionListToAll() {
    return ForTypes({MessageType::heartRate, MessageType::heartRateFrame, MessageType::heartRateVariability,
                     MessageType::eyeTracking, MessageType::eyeTrackingFrame, MessageType::cognitiveLoad,
                     MessageType::cognitiveLoadInputFeature, MessageType::ppg, MessageType::ppgFrame,
                     MessageType::imu, MessageType::imuFrame, MessageType::sceneColor, MessageType::sceneColorFrame,
                     MessageType::cameraImage, MessageType::vsync, MessageType::byteMessage,
                     MessageType::dataVaultResult});
}

namespace {
std::string ts(const Timestamp& t) {
    return "t_omnicept=" + std::to_string(t.omniceptTimeMicroSeconds) + "us";
}
}  // namespace

std::string DomainData::toString() const {
    return MessageTypeUtils::toString(getMessageType()) + " " + ts(timestamp);
}

std::string EyeGaze::toString() const {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
}
std::string PupilPosition::toString() const { return "(" + std::to_string(x) + ", " + std::to_string(y) + ")"; }
std::string Color::toString() const {
    return "rgb(" + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) +
           ") y=" + std::to_string(y);
}
std::string IMU3AxisValues::toString() const {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
}
std::string NDimArrayFloat::toString() const {
    std::string s = "shape[";
    for (size_t i = 0; i < shape.size(); ++i) s += (i ? "x" : "") + std::to_string(shape[i]);
    return s + "] " + std::to_string(valuesFlat.size()) + " values";
}
std::string EyePupilDiameter::toString() const {
    return std::to_string(size) + "mm (conf " + std::to_string(confidence) + ")";
}
std::string EyeSceneColors::toString() const {
    return "ambient " + ambientColor.toString() + ", foveal " + fovealColor.toString();
}

bool EyeTracking::fieldsEqual(const EyeTracking& o) const {
    return leftGaze == o.leftGaze && leftGazeConfidence == o.leftGazeConfidence && rightGaze == o.rightGaze &&
           rightGazeConfidence == o.rightGazeConfidence && combinedGaze == o.combinedGaze &&
           combinedGazeConfidence == o.combinedGazeConfidence && leftPupilDilation == o.leftPupilDilation &&
           leftPupilDilationConfidence == o.leftPupilDilationConfidence &&
           rightPupilDilation == o.rightPupilDilation &&
           rightPupilDilationConfidence == o.rightPupilDilationConfidence &&
           leftPupilPosition == o.leftPupilPosition && leftPupilPositionConfidence == o.leftPupilPositionConfidence &&
           rightPupilPosition == o.rightPupilPosition &&
           rightPupilPositionConfidence == o.rightPupilPositionConfidence && leftEyeOpenness == o.leftEyeOpenness &&
           leftEyeOpennessConfidence == o.leftEyeOpennessConfidence && rightEyeOpenness == o.rightEyeOpenness &&
           rightEyeOpennessConfidence == o.rightEyeOpennessConfidence;
}

std::string HeartRate::toString() const { return "HeartRate " + std::to_string(rate) + " bpm " + ts(timestamp); }
std::string HeartRateVariability::toString() const {
    return "HRV sdnn=" + std::to_string(sdnn) + " rmssd=" + std::to_string(rmssd) + " " + ts(timestamp);
}
std::string EyeTracking::toString() const {
    return "EyeTracking gaze=" + combinedGaze.toString() + " pupils L=" + std::to_string(leftPupilDilation) +
           " R=" + std::to_string(rightPupilDilation) + " " + ts(timestamp);
}
std::string EyePupillometry::toString() const {
    return "EyePupillometry L=" + leftPupilDiameter.toString() + " R=" + rightPupilDiameter.toString();
}
std::string CognitiveLoad::toString() const {
    return "CognitiveLoad " + std::to_string(cognitiveLoad) + " +/- " + std::to_string(standardDeviation) + " " +
           ts(timestamp);
}
std::string CognitiveLoadInputFeature::toString() const {
    return "CognitiveLoadInputFeature " + features.toString();
}
std::string PPG::toString() const { return "PPG " + std::to_string(ledValues.size()) + " LEDs " + ts(timestamp); }
std::string IMU::toString() const { return "IMU acc=" + acc.toString() + " gyro=" + gyro.toString(); }
std::string SceneColor::toString() const {
    return "SceneColor L[" + leftEyeSceneColors.toString() + "] R[" + rightEyeSceneColors.toString() + "]";
}
std::string CameraImage::toString() const {
    return "CameraImage " + std::to_string(width) + "x" + std::to_string(height) + " #" +
           std::to_string(frameNumber);
}
std::string VSync::toString() const { return "VSync " + ts(timestamp); }

std::string DataVaultResult::toString() const {
    return "DataVaultResult result=" + std::to_string(static_cast<int>(m_result)) +
           " error=" + std::to_string(static_cast<int>(m_error)) + " session=" + m_sessionId;
}

std::ostream& operator<<(std::ostream& out, const DomainData& d) { return out << d.toString(); }
std::ostream& operator<<(std::ostream& out, const DataVaultResult& r) { return out << r.toString(); }
std::ostream& operator<<(std::ostream& out, const EyeGaze& v) { return out << v.toString(); }
std::ostream& operator<<(std::ostream& out, const PupilPosition& v) { return out << v.toString(); }
std::ostream& operator<<(std::ostream& out, const IMU3AxisValues& v) { return out << v.toString(); }

}}}  // namespace HP::Omnicept::Abi
