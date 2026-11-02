#include "Codec.h"

#include "omnicept/abi/Errors.h"

#include "CameraImage.pb.h"
#include "CognitiveLoad.pb.h"
#include "CognitiveLoadInputFeature.pb.h"
#include "DataVaultAction.pb.h"
#include "DataVaultResult.pb.h"
#include "EyeTracking.pb.h"
#include "HeartRate.pb.h"
#include "HeartRateVariability.pb.h"
#include "IMU.pb.h"
#include "ModuleControlSignal.pb.h"
#include "PPG.pb.h"
#include "PackageDeclaration.pb.h"
#include "SceneColor.pb.h"
#include "Subscription.pb.h"
#include "SubscriptionResult.pb.h"
#include "ByteMessage.pb.h"
#include "VSync.pb.h"

namespace pb = HP::Omnicept::Abi;  // generated protobuf classes live in the same namespace

namespace HP { namespace Omnicept { namespace detail {

using namespace Abi;

namespace {

int64_t toMicros(const google::protobuf::Timestamp& t) {
    return t.seconds() * 1000000LL + t.nanos() / 1000;
}

void fromMicros(int64_t us, google::protobuf::Timestamp* t) {
    int64_t sec = us / 1000000LL;
    int64_t rem = us % 1000000LL;
    if (rem < 0) { rem += 1000000LL; --sec; }
    t->set_seconds(sec);
    t->set_nanos(static_cast<int32_t>(rem * 1000));
}

Timestamp toTimestamp(const pb::proto_Timestamp& p) {
    Timestamp t;
    t.systemTimeMicroSeconds = toMicros(p.systemtime());
    t.hardwareTimeMicroSeconds = toMicros(p.hardwaretime());
    t.omniceptTimeMicroSeconds = toMicros(p.omnicepttime());
    return t;
}

void fromTimestamp(const Timestamp& t, pb::proto_Timestamp* p) {
    fromMicros(t.systemTimeMicroSeconds, p->mutable_systemtime());
    fromMicros(t.hardwareTimeMicroSeconds, p->mutable_hardwaretime());
    fromMicros(t.omniceptTimeMicroSeconds, p->mutable_omnicepttime());
}

SensorInfo toSensorInfo(const pb::proto_SensorInfo& p) {
    return SensorInfo(p.deviceid().id(), p.deviceid().subid(), p.location());
}

void fromSensorInfo(const SensorInfo& s, pb::proto_SensorInfo* p) {
    p->mutable_deviceid()->set_id(s.deviceId.id);
    p->mutable_deviceid()->set_subid(s.deviceId.subId);
    p->set_location(s.location);
}

template <typename P>
P parse(const std::string& bytes, const char* what) {
    P p;
    if (!p.ParseFromString(bytes)) throw SerializationError(std::string("could not parse ") + what);
    return p;
}

template <typename P>
std::string serialize(const P& p) {
    std::string out;
    if (!p.SerializeToString(&out)) throw SerializationError("could not serialize message");
    return out;
}

// Per-type field mapping ----------------------------------------------------

void fill(HeartRate& d, const pb::proto_HeartRate& p) {
    d.rate = p.rate();
    d.timestamp = toTimestamp(p.timestamp());
}

void fill(EyeTracking& d, const pb::proto_EyeTracking& p) {
    auto gaze = [](const pb::proto_EyeGaze& g) { return EyeGaze(g.x(), g.y(), g.z()); };
    auto pos = [](const pb::proto_PupilPosition& g) { return PupilPosition(g.x(), g.y()); };
    d.leftGaze = gaze(p.leftgaze());
    d.leftGazeConfidence = p.leftgazeconfidence();
    d.rightGaze = gaze(p.rightgaze());
    d.rightGazeConfidence = p.rightgazeconfidence();
    d.combinedGaze = gaze(p.combinedgaze());
    d.combinedGazeConfidence = p.combinedgazeconfidence();
    d.leftPupilDilation = p.leftpupildilation();
    d.leftPupilDilationConfidence = p.leftpupildilationconfidence();
    d.rightPupilDilation = p.rightpupildilation();
    d.rightPupilDilationConfidence = p.rightpupildilationconfidence();
    d.leftPupilPosition = pos(p.leftpupilposition());
    d.leftPupilPositionConfidence = p.leftpupilpositionconfidence();
    d.rightPupilPosition = pos(p.rightpupilposition());
    d.rightPupilPositionConfidence = p.rightpupilpositionconfidence();
    d.leftEyeOpenness = p.lefteyeopenness();
    d.leftEyeOpennessConfidence = p.lefteyeopennessconfidence();
    d.rightEyeOpenness = p.righteyeopenness();
    d.rightEyeOpennessConfidence = p.righteyeopennessconfidence();
    d.timestamp = toTimestamp(p.timestamp());
}

void fill(IMU& d, const pb::proto_IMU& p) {
    d.acc = IMU3AxisValues(p.acc().x(), p.acc().y(), p.acc().z());
    d.gyro = IMU3AxisValues(p.gyro().x(), p.gyro().y(), p.gyro().z());
    d.timestamp = toTimestamp(p.timestamp());
}

void fill(PPG& d, const pb::proto_PPG& p) {
    d.ledValues.assign(p.values().begin(), p.values().end());
    d.timestamp = toTimestamp(p.timestamp());
}

void fill(SceneColor& d, const pb::proto_SceneColor& p) {
    auto color = [](const pb::proto_Color& c) { return Color(c.r(), c.g(), c.b(), c.y()); };
    auto eye = [&](const pb::proto_EyeSceneColors& e) {
        return EyeSceneColors(color(e.ambient()), color(e.foveal()));
    };
    d.leftEyeSceneColors = eye(p.left());
    d.rightEyeSceneColors = eye(p.right());
    d.timestamp = toTimestamp(p.timestamp());
}

template <typename Frame, typename Sample, typename PFrame>
std::shared_ptr<Frame> decodeFrame(const PFrame& p, const SensorInfo& sensor) {
    auto frame = std::make_shared<Frame>();
    frame->sensorInfo = sensor;
    frame->timestamp = toTimestamp(p.timestamp());
    for (const auto& s : p.data()) {
        Sample sample;
        fill(sample, s);
        sample.sensorInfo = sensor;
        frame->data.push_back(sample);
    }
    return frame;
}

}  // namespace

// Header ---------------------------------------------------------------------

std::string encodeHeader(const Envelope& env) {
    pb::proto_PackageDeclaration h;
    h.set_messagetype(static_cast<uint32_t>(env.type));
    h.set_messageversion(env.version);
    h.set_messagelength(env.body.size());
    h.set_sender(env.sender);
    h.set_destination(env.destination);
    if (!env.sensorInfo.empty()) fromSensorInfo(env.sensorInfo, h.mutable_sensorinfo());
    return serialize(h);
}

Envelope decodeHeader(const std::string& bytes) {
    auto h = parse<pb::proto_PackageDeclaration>(bytes, "PackageDeclaration");
    Envelope env;
    env.type = static_cast<MessageType>(h.messagetype());
    env.version = h.messageversion();
    env.sender = h.sender();
    env.destination = h.destination();
    env.sensorInfo = toSensorInfo(h.sensorinfo());
    return env;
}

// Domain decoding ------------------------------------------------------------

std::shared_ptr<GenericMessage> decodeDomain(const Envelope& env) {
    const auto& b = env.body;
    switch (env.type) {
        case MessageType::heartRate: {
            auto d = std::make_shared<HeartRate>();
            fill(*d, parse<pb::proto_HeartRate>(b, "HeartRate"));
            d->sensorInfo = env.sensorInfo;
            return d;
        }
        case MessageType::heartRateFrame:
            return decodeFrame<HeartRateFrame, HeartRate>(parse<pb::proto_HeartRateFrame>(b, "HeartRateFrame"),
                                                          env.sensorInfo);
        case MessageType::heartRateVariability: {
            auto p = parse<pb::proto_HeartRateVariability>(b, "HeartRateVariability");
            auto d = std::make_shared<HeartRateVariability>();
            d->sdnn = p.sdnn();
            d->rmssd = p.rmssd();
            d->timestamp = toTimestamp(p.timestamp());
            d->sensorInfo = env.sensorInfo;
            return d;
        }
        case MessageType::eyeTracking: {
            auto d = std::make_shared<EyeTracking>();
            fill(*d, parse<pb::proto_EyeTracking>(b, "EyeTracking"));
            d->sensorInfo = env.sensorInfo;
            return d;
        }
        case MessageType::eyeTrackingFrame:
            return decodeFrame<EyeTrackingFrame, EyeTracking>(
                parse<pb::proto_EyeTrackingFrame>(b, "EyeTrackingFrame"), env.sensorInfo);
        case MessageType::cognitiveLoad: {
            auto p = parse<pb::proto_CognitiveLoad>(b, "CognitiveLoad");
            auto d = std::make_shared<CognitiveLoad>();
            d->cognitiveLoad = p.cognitiveload();
            d->standardDeviation = p.standarddeviation();
            d->dataState = p.datastate();
            d->startDataCollectTime = toTimestamp(p.startdatacollecttime());
            d->endDataCollectTime = toTimestamp(p.enddatacollecttime());
            d->timestamp = toTimestamp(p.timestamp());
            d->sensorInfo = env.sensorInfo;
            return d;
        }
        case MessageType::cognitiveLoadInputFeature: {
            auto p = parse<pb::proto_CognitiveLoadInputFeature>(b, "CognitiveLoadInputFeature");
            auto d = std::make_shared<CognitiveLoadInputFeature>();
            d->dataState = p.datastate();
            d->startDataCollectTime = toTimestamp(p.startdatacollecttime());
            d->endDataCollectTime = toTimestamp(p.enddatacollecttime());
            for (auto s : p.features().shape()) d->features.shape.push_back(static_cast<uint32_t>(s));
            d->features.valuesFlat.assign(p.features().valuesflat().begin(), p.features().valuesflat().end());
            d->targetModel = static_cast<CognitiveLoadTargetModel>(p.targetmodel());
            d->timestamp = toTimestamp(p.timestamp());
            d->sensorInfo = env.sensorInfo;
            return d;
        }
        case MessageType::ppg: {
            auto d = std::make_shared<PPG>();
            fill(*d, parse<pb::proto_PPG>(b, "PPG"));
            d->sensorInfo = env.sensorInfo;
            return d;
        }
        case MessageType::ppgFrame: {
            auto p = parse<pb::proto_PPGFrame>(b, "PPGFrame");
            auto d = decodeFrame<PPGFrame, PPG>(p, env.sensorInfo);
            d->ledCurrents.assign(p.ledcurrents().begin(), p.ledcurrents().end());
            return d;
        }
        case MessageType::imu: {
            auto d = std::make_shared<IMU>();
            fill(*d, parse<pb::proto_IMU>(b, "IMU"));
            d->sensorInfo = env.sensorInfo;
            return d;
        }
        case MessageType::imuFrame:
            return decodeFrame<IMUFrame, IMU>(parse<pb::proto_IMUFrame>(b, "IMUFrame"), env.sensorInfo);
        case MessageType::sceneColor: {
            auto d = std::make_shared<SceneColor>();
            fill(*d, parse<pb::proto_SceneColor>(b, "SceneColor"));
            d->sensorInfo = env.sensorInfo;
            return d;
        }
        case MessageType::sceneColorFrame:
            return decodeFrame<SceneColorFrame, SceneColor>(
                parse<pb::proto_SceneColorFrame>(b, "SceneColorFrame"), env.sensorInfo);
        case MessageType::cameraImage: {
            auto p = parse<pb::proto_CameraImage>(b, "CameraImage");
            auto d = std::make_shared<CameraImage>();
            d->format = static_cast<CameraImage::ImageFormat>(p.format());
            d->imageData.assign(p.imagedata().begin(), p.imagedata().end());
            d->width = p.width();
            d->height = p.height();
            d->frameNumber = p.framenumber();
            d->framesPerSecond = p.fps();
            d->timestamp = toTimestamp(p.timestamp());
            d->sensorInfo = env.sensorInfo;
            return d;
        }
        case MessageType::vsync: {
            auto p = parse<pb::proto_VSync>(b, "VSync");
            auto d = std::make_shared<VSync>();
            d->timestamp = toTimestamp(p.timestamp());
            d->sensorInfo = env.sensorInfo;
            return d;
        }
        case MessageType::byteMessage: {
            auto p = parse<pb::proto_ByteMessage>(b, "ByteMessage");
            return std::make_shared<ByteMessage>(p.id(), p.message());
        }
        case MessageType::dataVaultResult: {
            auto p = parse<pb::proto_DataVaultResult>(b, "DataVaultResult");
            return std::make_shared<DataVaultResult>(static_cast<DataVaultResultType>(p.result()),
                                                     static_cast<DataVaultResultErrorType>(p.error()),
                                                     p.sessionid());
        }
        default:
            return nullptr;
    }
}

// Control messages -----------------------------------------------------------

std::string encodeSubscriptionList(const SubscriptionList& list) {
    pb::proto_SubscriptionList p;
    for (const auto& s : list.getSubscriptions()) {
        auto* ps = p.add_subscriptions();
        ps->set_messagetype(static_cast<uint32_t>(s.getType()));
        if (!s.getSensorInfo().empty()) fromSensorInfo(s.getSensorInfo(), ps->mutable_sensorinfo());
        ps->set_sender(s.getSender());
        ps->set_versionsemantic(s.getVersionSemantic());
    }
    return serialize(p);
}

SubscriptionList decodeSubscriptionList(const std::string& body) {
    auto p = parse<pb::proto_SubscriptionList>(body, "SubscriptionList");
    SubscriptionList list;
    for (const auto& ps : p.subscriptions()) {
        Subscription s(static_cast<MessageType>(ps.messagetype()), toSensorInfo(ps.sensorinfo()), ps.sender());
        s.setVersionSemantic(ps.versionsemantic());
        list.getSubscriptions().push_back(s);
    }
    return list;
}

std::vector<SubscriptionResult> decodeSubscriptionResults(const std::string& body) {
    auto p = parse<pb::proto_SubscriptionResultList>(body, "SubscriptionResultList");
    std::vector<SubscriptionResult> out;
    for (const auto& r : p.subscriptionresults()) {
        SubscriptionResult res;
        res.result = static_cast<SubscriptionResult::Result>(r.result());
        res.error = static_cast<SubscriptionResult::Error>(r.error());
        res.subscription = Subscription(static_cast<MessageType>(r.subscription().messagetype()),
                                        toSensorInfo(r.subscription().sensorinfo()), r.subscription().sender());
        out.push_back(res);
    }
    return out;
}

std::string encodeSubscriptionResults(const std::vector<SubscriptionResult>& results) {
    pb::proto_SubscriptionResultList p;
    for (const auto& r : results) {
        auto* pr = p.add_subscriptionresults();
        pr->set_result(static_cast<pb::proto_SubscriptionResult_SubscriptionResultType>(r.result));
        pr->set_error(static_cast<pb::proto_SubscriptionResult_SubscriptionResultErrorType>(r.error));
        pr->mutable_subscription()->set_messagetype(static_cast<uint32_t>(r.subscription.getType()));
    }
    return serialize(p);
}

std::string encodeDataVaultAction(bool start) {
    pb::proto_DataVaultAction p;
    p.set_action(start ? pb::proto_DataVaultAction::START_RECORDING : pb::proto_DataVaultAction::STOP_RECORDING);
    return serialize(p);
}

bool decodeDataVaultActionIsStart(const std::string& body) {
    return parse<pb::proto_DataVaultAction>(body, "DataVaultAction").action() ==
           pb::proto_DataVaultAction::START_RECORDING;
}

std::string encodeDataVaultResult(const DataVaultResult& r) {
    pb::proto_DataVaultResult p;
    p.set_result(static_cast<pb::proto_DataVaultResult_DataVaultResultType>(r.m_result));
    p.set_error(static_cast<pb::proto_DataVaultResult_DataVaultResultErrorType>(r.m_error));
    p.set_sessionid(r.m_sessionId);
    return serialize(p);
}

std::string encodeModuleControlSignal(ModuleControlSignalType signal) {
    pb::proto_ModuleControlSignal p;
    p.set_signal(static_cast<pb::proto_ModuleControlSignal_ModuleSignal>(signal));
    return serialize(p);
}

ModuleControlSignalType decodeModuleControlSignal(const std::string& body) {
    return static_cast<ModuleControlSignalType>(
        parse<pb::proto_ModuleControlSignal>(body, "ModuleControlSignal").signal());
}

// Test encoders ---------------------------------------------------------------

std::string encodeHeartRate(const HeartRate& hr) {
    pb::proto_HeartRate p;
    p.set_rate(hr.rate);
    fromTimestamp(hr.timestamp, p.mutable_timestamp());
    return serialize(p);
}

std::string encodeEyeTracking(const EyeTracking& et) {
    pb::proto_EyeTracking p;
    auto gaze = [](const EyeGaze& g, pb::proto_EyeGaze* o) { o->set_x(g.x); o->set_y(g.y); o->set_z(g.z); };
    gaze(et.leftGaze, p.mutable_leftgaze());
    gaze(et.rightGaze, p.mutable_rightgaze());
    gaze(et.combinedGaze, p.mutable_combinedgaze());
    p.set_combinedgazeconfidence(et.combinedGazeConfidence);
    p.set_leftpupildilation(et.leftPupilDilation);
    p.set_rightpupildilation(et.rightPupilDilation);
    p.mutable_leftpupilposition()->set_x(et.leftPupilPosition.x);
    p.mutable_leftpupilposition()->set_y(et.leftPupilPosition.y);
    p.set_lefteyeopenness(et.leftEyeOpenness);
    p.set_righteyeopenness(et.rightEyeOpenness);
    fromTimestamp(et.timestamp, p.mutable_timestamp());
    return serialize(p);
}

std::string encodeIMUFrame(const IMUFrame& frame) {
    pb::proto_IMUFrame p;
    for (const auto& s : frame.data) {
        auto* ps = p.add_data();
        ps->mutable_acc()->set_x(s.acc.x);
        ps->mutable_acc()->set_y(s.acc.y);
        ps->mutable_acc()->set_z(s.acc.z);
        ps->mutable_gyro()->set_x(s.gyro.x);
        ps->mutable_gyro()->set_y(s.gyro.y);
        ps->mutable_gyro()->set_z(s.gyro.z);
        fromTimestamp(s.timestamp, ps->mutable_timestamp());
    }
    fromTimestamp(frame.timestamp, p.mutable_timestamp());
    return serialize(p);
}

}}}  // namespace HP::Omnicept::detail
