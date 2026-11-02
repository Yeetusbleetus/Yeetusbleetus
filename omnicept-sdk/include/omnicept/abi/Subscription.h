#pragma once

#include <string>
#include <vector>

#include "omnicept/abi/MessageType.h"
#include "omnicept/abi/Sensor.h"

namespace HP { namespace Omnicept { namespace Abi {

// Filter for incoming messages. Every field that is set must match (logical
// AND); fields left empty match anything.
class Subscription {
public:
    Subscription() = default;
    Subscription(MessageType messageType, const SensorInfo& sensorInfo = {}, const std::string& sender = {})
        : m_type(messageType), m_sensorInfo(sensorInfo), m_sender(sender) {}
    Subscription(uint32_t messageType, const SensorInfo& sensorInfo, const std::string& sender)
        : Subscription(static_cast<MessageType>(messageType), sensorInfo, sender) {}
    virtual ~Subscription() = default;

    const MessageType& getType() const { return m_type; }
    const SensorInfo& getSensorInfo() const { return m_sensorInfo; }
    const std::string& getSender() const { return m_sender; }
    // Version filter sent as `versionSemantic`. Its accepted syntax is not
    // known; empty means "no version constraint".
    const std::string& getVersionSemantic() const { return m_versionSemantic; }

    void setType(const MessageType& type) { m_type = type; }
    void setSensorInfo(const SensorInfo& sensorInfo) { m_sensorInfo = sensorInfo; }
    void setSender(const std::string& sender) { m_sender = sender; }
    void setVersionSemantic(const std::string& v) { m_versionSemantic = v; }

    bool operator==(const Subscription& o) const {
        return m_type == o.m_type && m_sensorInfo == o.m_sensorInfo && m_sender == o.m_sender &&
               m_versionSemantic == o.m_versionSemantic;
    }

private:
    MessageType m_type = MessageType::null;
    SensorInfo m_sensorInfo;
    std::string m_sender;
    std::string m_versionSemantic;
};

// A message is delivered if it matches at least one subscription in the list.
class SubscriptionList {
public:
    SubscriptionList() = default;
    virtual ~SubscriptionList() = default;

    // An explicitly empty list: receive nothing. This is the client's default.
    static SubscriptionList GetSubscriptionListToNone() { return SubscriptionList(); }
    // One subscription per message type, with no sensor or sender filter.
    static SubscriptionList ForTypes(const std::vector<MessageType>& types);
    // Every message type the client knows how to decode.
    static SubscriptionList GetSubscriptionListToAll();

    const std::vector<Subscription>& getSubscriptions() const { return m_subscriptions; }
    std::vector<Subscription>& getSubscriptions() { return m_subscriptions; }
    void setSubscriptions(const std::vector<Subscription>& subscriptions) { m_subscriptions = subscriptions; }
    bool operator==(const SubscriptionList& o) const { return m_subscriptions == o.m_subscriptions; }

private:
    std::vector<Subscription> m_subscriptions;
};

// The runtime's answer for one requested subscription.
struct SubscriptionResult {
    enum class Result { UNKNOWN = 0, REJECTED = 1, PENDING = 2, APPROVED = 3 };
    enum class Error {
        UNKNOWN_ERROR = 0,
        SUCCESS_NO_ERROR = 1,
        NOT_LICENSED_ERROR = 2,
        REJECTED_BY_USER_ERROR = 3,
        SPECIFIED_VERSION_NOT_AVAILABLE_ERROR = 4,
        MESSAGE_NOT_SUPPORTED = 5,
        LEGACY_SUBSCRIPTION_NOT_CHECKED = 6,
    };

    Result result = Result::UNKNOWN;
    Error error = Error::UNKNOWN_ERROR;
    Subscription subscription;
};

}}}  // namespace HP::Omnicept::Abi
