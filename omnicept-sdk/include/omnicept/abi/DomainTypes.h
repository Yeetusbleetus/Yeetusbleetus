#pragma once

#include <cstdint>
#include <map>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "omnicept/abi/MessageType.h"
#include "omnicept/abi/Sensor.h"

namespace HP { namespace Omnicept { namespace Abi {

enum class CognitiveLoadTargetModel { UNKNOWN = 0, EYE_TRACKING = 1, EYE_TRACKING_PPG = 2 };

enum class DataVaultResultType {
    UNKNOWN = 0,
    RECORDING_STARTED = 1,
    RECORDING_START_REJECTED = 2,
    RECORDING_STOPPED = 3,
    RECORDING_STOP_REJECTED = 4,
    RECORDING_ERROR = 5,
};

enum class DataVaultResultErrorType {
    UNKNOWN_ERROR = 0,
    SUCCESS_NO_ERROR = 1,
    INVALID_LICENSE_ERROR = 2,
    CONNECTION_FAILED_ERROR = 3,
    CONNECTION_NEGOTIATING_ERROR = 4,
    RECORDING_HAS_ALREADY_STARTED_ERROR = 5,
    RECORDING_HAS_NOT_STARTED_ERROR = 6,
    RECORDING_STOP_NO_PERMISSON_ERROR = 7,
};

enum class WhichEye { unknown = 0, left = 1, right = 2, both = 3 };

enum class ModuleControlSignalType {
    MODULE_SIGNAL_UNKNOWN = 0,
    MODULE_SIGNAL_READY = 10,
    MODULE_SIGNAL_STOP = 20,
    MODULE_SIGNAL_WAKE = 30,
    MODULE_SIGNAL_SLEEP = 40,
};

// ---------------------------------------------------------------------------
// Base classes
// ---------------------------------------------------------------------------

class GenericMessage {
public:
    GenericMessage() = delete;
    explicit GenericMessage(MessageType msgType) : m_type(msgType) {}
    virtual ~GenericMessage() = default;

    MessageType getMessageType() const { return m_type; }
    bool operator==(const GenericMessage& other) const { return m_type == other.m_type; }

private:
    MessageType m_type;
};

// Timestamped data from a specific sensor.
class DomainData : public GenericMessage {
public:
    SensorInfo sensorInfo;
    Timestamp timestamp;

    DomainData() = delete;
    explicit DomainData(MessageType type) : GenericMessage(type) {}
    virtual ~DomainData() = default;

    bool operator==(const DomainData& other) const {
        return GenericMessage::operator==(other) && sensorInfo == other.sensorInfo && timestamp == other.timestamp;
    }
    virtual bool dataEquals(const DomainData& other) const { return getMessageType() == other.getMessageType(); }
    virtual std::string toString() const;
};

// A batch of samples collected over a period of time; `timestamp` belongs to
// the newest sample.
template <typename T>
class DataFrame : public DomainData {
public:
    std::vector<T> data;

    explicit DataFrame(MessageType value) : DomainData(value) {}
    virtual ~DataFrame() = default;

    bool operator==(const DataFrame<T>& other) const { return DomainData::operator==(other) && dataEquals(other); }
    bool dataEquals(const DomainData& other) const override {
        auto* o = dynamic_cast<const DataFrame<T>*>(&other);
        return o != nullptr && dataEquals(*o);
    }
    bool dataEquals(const DataFrame<T>& other) const {
        if (data.size() != other.data.size()) return false;
        for (size_t i = 0; i < data.size(); ++i)
            if (!data[i].dataEquals(other.data[i])) return false;
        return true;
    }
    std::string toString() const override {
        std::ostringstream ss;
        ss << MessageTypeUtils::toString(getMessageType()) << "[" << data.size() << " samples]";
        return ss.str();
    }
};

// ---------------------------------------------------------------------------
// Value structs
// ---------------------------------------------------------------------------

struct EyeGaze {
    float x = 0, y = 0, z = 0;
    EyeGaze() = default;
    EyeGaze(float x, float y, float z) : x(x), y(y), z(z) {}
    bool operator==(const EyeGaze& o) const { return x == o.x && y == o.y && z == o.z; }
    std::string toString() const;
};

// Normalised to [0, 1] in both axes.
struct PupilPosition {
    float x = 0, y = 0;
    PupilPosition() = default;
    PupilPosition(float x, float y) : x(x), y(y) {}
    bool operator==(const PupilPosition& o) const { return x == o.x && y == o.y; }
    std::string toString() const;
};

// RGB plus luminance (y).
struct Color {
    float r = 0, g = 0, b = 0, y = 0;
    Color() = default;
    Color(float r, float g, float b, float y) : r(r), g(g), b(b), y(y) {}
    virtual ~Color() = default;
    bool operator==(const Color& o) const { return r == o.r && g == o.g && b == o.b && y == o.y; }
    std::string toString() const;
};

class IMU3AxisValues {
public:
    float x = 0, y = 0, z = 0;
    IMU3AxisValues() = default;
    IMU3AxisValues(float x, float y, float z) : x(x), y(y), z(z) {}
    virtual ~IMU3AxisValues() = default;
    bool operator==(const IMU3AxisValues& o) const { return x == o.x && y == o.y && z == o.z; }
    std::string toString() const;
};

class NDimArrayFloat {
public:
    std::vector<uint32_t> shape;
    std::vector<float> valuesFlat;
    NDimArrayFloat() = default;
    virtual ~NDimArrayFloat() = default;
    bool operator==(const NDimArrayFloat& o) const { return shape == o.shape && valuesFlat == o.valuesFlat; }
    std::string toString() const;
};

class EyePupilDiameter {
public:
    float size = 0;
    float confidence = 0;
    EyePupilDiameter() = default;
    EyePupilDiameter(float size, float confidence) : size(size), confidence(confidence) {}
    virtual ~EyePupilDiameter() = default;
    bool operator==(const EyePupilDiameter& o) const { return size == o.size && confidence == o.confidence; }
    std::string toString() const;
};

class EyeSceneColors {
public:
    Color ambientColor;
    Color fovealColor;
    EyeSceneColors() = default;
    EyeSceneColors(const Color& ambient, const Color& foveal) : ambientColor(ambient), fovealColor(foveal) {}
    virtual ~EyeSceneColors() = default;
    bool operator==(const EyeSceneColors& o) const {
        return ambientColor == o.ambientColor && fovealColor == o.fovealColor;
    }
    std::string toString() const;
};

class BackpackColorZone {
public:
    uint32_t r = 0, g = 0, b = 0;
    BackpackColorZone() = default;
    BackpackColorZone(uint32_t r, uint32_t g, uint32_t b) : r(r), g(g), b(b) {}
    virtual ~BackpackColorZone() = default;
    bool operator==(const BackpackColorZone& o) const { return r == o.r && g == o.g && b == o.b; }
};

// ---------------------------------------------------------------------------
// Domain types
// ---------------------------------------------------------------------------

#define OMNICEPT_DOMAIN_TYPE(Name, TypeId)                                     \
    static constexpr MessageType kMessageType = MessageType::TypeId;           \
    bool dataEquals(const DomainData& other) const override {                  \
        auto* o = dynamic_cast<const Name*>(&other);                           \
        return o != nullptr && fieldsEqual(*o);                                \
    }                                                                          \
    bool operator==(const Name& other) const {                                 \
        return DomainData::operator==(other) && fieldsEqual(other);            \
    }                                                                          \
    std::string toString() const override;

class HeartRate : public DomainData {
public:
    uint32_t rate = 0;  // beats per minute

    HeartRate() : DomainData(kMessageType) {}
    virtual ~HeartRate() = default;
    OMNICEPT_DOMAIN_TYPE(HeartRate, heartRate)

private:
    bool fieldsEqual(const HeartRate& o) const { return rate == o.rate; }
};

class HeartRateFrame : public DataFrame<HeartRate> {
public:
    static constexpr MessageType kMessageType = MessageType::heartRateFrame;
    HeartRateFrame() : DataFrame<HeartRate>(kMessageType) {}
    virtual ~HeartRateFrame() = default;
};

class HeartRateVariability : public DomainData {
public:
    float sdnn = 0;   // milliseconds
    float rmssd = 0;  // milliseconds

    HeartRateVariability() : DomainData(kMessageType) {}
    virtual ~HeartRateVariability() = default;
    OMNICEPT_DOMAIN_TYPE(HeartRateVariability, heartRateVariability)

private:
    bool fieldsEqual(const HeartRateVariability& o) const { return sdnn == o.sdnn && rmssd == o.rmssd; }
};

class EyeTracking : public DomainData {
public:
    EyeGaze leftGaze;
    float leftGazeConfidence = 0;
    EyeGaze rightGaze;
    float rightGazeConfidence = 0;
    EyeGaze combinedGaze;
    float combinedGazeConfidence = 0;
    float leftPupilDilation = 0;
    float leftPupilDilationConfidence = 0;
    float rightPupilDilation = 0;
    float rightPupilDilationConfidence = 0;
    PupilPosition leftPupilPosition;
    float leftPupilPositionConfidence = 0;
    PupilPosition rightPupilPosition;
    float rightPupilPositionConfidence = 0;
    float leftEyeOpenness = 0;
    float leftEyeOpennessConfidence = 0;
    float rightEyeOpenness = 0;
    float rightEyeOpennessConfidence = 0;

    EyeTracking() : DomainData(kMessageType) {}
    virtual ~EyeTracking() = default;
    OMNICEPT_DOMAIN_TYPE(EyeTracking, eyeTracking)

private:
    bool fieldsEqual(const EyeTracking& o) const;
};

class EyeTrackingFrame : public DataFrame<EyeTracking> {
public:
    static constexpr MessageType kMessageType = MessageType::eyeTrackingFrame;
    EyeTrackingFrame() : DataFrame<EyeTracking>(kMessageType) {}
    virtual ~EyeTrackingFrame() = default;
};

// No wire schema for this type was found in the runtime, so the SDK cannot
// decode it yet. The type exists for API compatibility.
class EyePupillometry : public DomainData {
public:
    EyePupilDiameter rightPupilDiameter;
    EyePupilDiameter leftPupilDiameter;

    EyePupillometry() : DomainData(kMessageType) {}
    EyePupillometry(EyePupilDiameter left, EyePupilDiameter right)
        : DomainData(kMessageType), rightPupilDiameter(right), leftPupilDiameter(left) {}
    virtual ~EyePupillometry() = default;
    OMNICEPT_DOMAIN_TYPE(EyePupillometry, eyePupillometry)

private:
    bool fieldsEqual(const EyePupillometry& o) const {
        return rightPupilDiameter == o.rightPupilDiameter && leftPupilDiameter == o.leftPupilDiameter;
    }
};

class CognitiveLoad : public DomainData {
public:
    float cognitiveLoad = 0;      // 0..1
    float standardDeviation = 0;  // uncertainty of the estimate
    std::string dataState;
    Timestamp startDataCollectTime;
    Timestamp endDataCollectTime;

    CognitiveLoad() : DomainData(kMessageType) {}
    virtual ~CognitiveLoad() = default;
    OMNICEPT_DOMAIN_TYPE(CognitiveLoad, cognitiveLoad)

private:
    bool fieldsEqual(const CognitiveLoad& o) const {
        return cognitiveLoad == o.cognitiveLoad && standardDeviation == o.standardDeviation &&
               dataState == o.dataState;
    }
};

class CognitiveLoadInputFeature : public DomainData {
public:
    std::string dataState;
    Timestamp startDataCollectTime;
    Timestamp endDataCollectTime;
    NDimArrayFloat features;
    CognitiveLoadTargetModel targetModel = CognitiveLoadTargetModel::UNKNOWN;

    CognitiveLoadInputFeature() : DomainData(kMessageType) {}
    virtual ~CognitiveLoadInputFeature() = default;
    OMNICEPT_DOMAIN_TYPE(CognitiveLoadInputFeature, cognitiveLoadInputFeature)

private:
    bool fieldsEqual(const CognitiveLoadInputFeature& o) const {
        return dataState == o.dataState && features == o.features && targetModel == o.targetModel;
    }
};

class PPG : public DomainData {
public:
    std::vector<uint32_t> ledValues;

    PPG() : DomainData(kMessageType) {}
    explicit PPG(const std::vector<uint32_t>& values) : DomainData(kMessageType), ledValues(values) {}
    virtual ~PPG() = default;
    OMNICEPT_DOMAIN_TYPE(PPG, ppg)

private:
    bool fieldsEqual(const PPG& o) const { return ledValues == o.ledValues; }
};

class PPGFrame : public DataFrame<PPG> {
public:
    static constexpr MessageType kMessageType = MessageType::ppgFrame;
    std::vector<uint32_t> ledCurrents;

    PPGFrame() : DataFrame<PPG>(kMessageType) {}
    explicit PPGFrame(std::vector<uint32_t>& ledCurrents) : DataFrame<PPG>(kMessageType), ledCurrents(ledCurrents) {}
    virtual ~PPGFrame() = default;
};

class IMU : public DomainData {
public:
    IMU3AxisValues acc;
    IMU3AxisValues gyro;

    IMU() : DomainData(kMessageType) {}
    IMU(IMU3AxisValues accValues, IMU3AxisValues gyroValues)
        : DomainData(kMessageType), acc(accValues), gyro(gyroValues) {}
    virtual ~IMU() = default;
    OMNICEPT_DOMAIN_TYPE(IMU, imu)

private:
    bool fieldsEqual(const IMU& o) const { return acc == o.acc && gyro == o.gyro; }
};

class IMUFrame : public DataFrame<IMU> {
public:
    static constexpr MessageType kMessageType = MessageType::imuFrame;
    IMUFrame() : DataFrame<IMU>(kMessageType) {}
    virtual ~IMUFrame() = default;
};

class SceneColor : public DomainData {
public:
    EyeSceneColors leftEyeSceneColors;
    EyeSceneColors rightEyeSceneColors;

    SceneColor() : DomainData(kMessageType) {}
    SceneColor(const EyeSceneColors& left, const EyeSceneColors& right)
        : DomainData(kMessageType), leftEyeSceneColors(left), rightEyeSceneColors(right) {}
    virtual ~SceneColor() = default;
    OMNICEPT_DOMAIN_TYPE(SceneColor, sceneColor)

private:
    bool fieldsEqual(const SceneColor& o) const {
        return leftEyeSceneColors == o.leftEyeSceneColors && rightEyeSceneColors == o.rightEyeSceneColors;
    }
};

class SceneColorFrame : public DataFrame<SceneColor> {
public:
    static constexpr MessageType kMessageType = MessageType::sceneColorFrame;
    SceneColorFrame() : DataFrame<SceneColor>(kMessageType) {}
    virtual ~SceneColorFrame() = default;
};

class CameraImage : public DomainData {
public:
    enum class ImageFormat { UNKNOWN = 0, RGB888 = 1, YUY2 = 2, UYVY = 3, YVYU = 4, YUYV = 5,
                             AYUV = 6, YV12 = 7, NV12 = 8, L8 = 9, CUSTOM = 100 };

    std::vector<unsigned char> imageData;
    ImageFormat format = ImageFormat::UNKNOWN;
    uint32_t width = 0;
    uint32_t height = 0;
    uint64_t frameNumber = 0;
    float framesPerSecond = 0;

    CameraImage() : DomainData(kMessageType) {}
    virtual ~CameraImage() = default;
    OMNICEPT_DOMAIN_TYPE(CameraImage, cameraImage)

private:
    bool fieldsEqual(const CameraImage& o) const {
        return imageData == o.imageData && format == o.format && width == o.width && height == o.height &&
               frameNumber == o.frameNumber && framesPerSecond == o.framesPerSecond;
    }
};

class VSync : public DomainData {
public:
    VSync() : DomainData(kMessageType) {}
    virtual ~VSync() = default;
    OMNICEPT_DOMAIN_TYPE(VSync, vsync)

private:
    bool fieldsEqual(const VSync&) const { return true; }
};

#undef OMNICEPT_DOMAIN_TYPE

// ---------------------------------------------------------------------------
// Non-sensor messages
// ---------------------------------------------------------------------------

class ByteMessage : public GenericMessage {
public:
    static constexpr MessageType kMessageType = MessageType::byteMessage;
    std::string id;
    std::string message;

    ByteMessage() : GenericMessage(kMessageType) {}
    ByteMessage(std::string id, std::string msg) : GenericMessage(kMessageType), id(std::move(id)), message(std::move(msg)) {}
    virtual ~ByteMessage() = default;
    bool operator==(const ByteMessage& o) const { return id == o.id && message == o.message; }
};

class DataVaultResult : public GenericMessage {
public:
    static constexpr MessageType kMessageType = MessageType::dataVaultResult;
    DataVaultResultType m_result = DataVaultResultType::UNKNOWN;
    DataVaultResultErrorType m_error = DataVaultResultErrorType::UNKNOWN_ERROR;
    std::string m_sessionId;

    DataVaultResult() : GenericMessage(kMessageType) {}
    DataVaultResult(DataVaultResultType result, DataVaultResultErrorType error, std::string sessionId)
        : GenericMessage(kMessageType), m_result(result), m_error(error), m_sessionId(std::move(sessionId)) {}
    std::string toString() const;
    bool operator==(const DataVaultResult& rhs) const {
        return m_result == rhs.m_result && m_error == rhs.m_error && m_sessionId == rhs.m_sessionId;
    }
};

class ModuleControlSignal : public GenericMessage {
public:
    static constexpr MessageType kMessageType = MessageType::moduleControlSignal;

    ModuleControlSignal() : GenericMessage(kMessageType) {}
    explicit ModuleControlSignal(ModuleControlSignalType signal) : GenericMessage(kMessageType), m_signal(signal) {}
    ~ModuleControlSignal() = default;

    void SetSignal(ModuleControlSignalType signal) { m_signal = signal; }
    ModuleControlSignalType GetSignal() const { return m_signal; }
    bool operator==(const ModuleControlSignal& o) const { return m_signal == o.m_signal; }

private:
    ModuleControlSignalType m_signal = ModuleControlSignalType::MODULE_SIGNAL_UNKNOWN;
};

std::ostream& operator<<(std::ostream& out, const DomainData& d);
std::ostream& operator<<(std::ostream& out, const DataVaultResult& r);
std::ostream& operator<<(std::ostream& out, const EyeGaze& v);
std::ostream& operator<<(std::ostream& out, const PupilPosition& v);
std::ostream& operator<<(std::ostream& out, const IMU3AxisValues& v);

}}}  // namespace HP::Omnicept::Abi
