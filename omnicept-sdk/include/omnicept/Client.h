#pragma once

#include <atomic>
#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <thread>
#include <type_traits>
#include <vector>

#include "omnicept/abi/DomainTypes.h"
#include "omnicept/abi/Errors.h"
#include "omnicept/abi/Subscription.h"

namespace HP { namespace Omnicept {

namespace Utils {

// Owns one worker thread that runs `run()` until asked to stop.
class ThreadOwner {
public:
    virtual ~ThreadOwner();

    virtual void start();
    virtual void requestStop() { m_continue = false; }
    virtual bool join();
    virtual bool shouldContinue() const { return m_continue; }
    std::thread::id getThreadId() const { return m_thread.get_id(); }

protected:
    virtual void run() = 0;

private:
    std::thread m_thread;
    std::atomic<bool> m_continue{false};
};

}  // namespace Utils

namespace detail { class Connection; }
class Glia;

// A live connection to the Omnicept runtime. Incoming messages are decoded on
// an internal thread, cached as the latest value for their type, and passed to
// the callback registered for that type. Create one with
// Glia::StartBuildClient_Async; a new Client starts PAUSED and subscribed to
// nothing.
class Client : public Utils::ThreadOwner {
public:
    enum class State { PAUSED, RUNNING, DISCONNECTED };

    enum class Result {
        SUCCESS,
        ERROR_CLIENT_DISCONNECTED,
        NO_OP_CLIENT_RUNNING,
        NO_OP_CLIENT_PAUSED,
        UNSPECIFIED_ERROR,
    };

    using StateCallback_T = std::function<void(const State)>;
    using SubscriptionResultCallback_T = std::function<void(const std::vector<Abi::SubscriptionResult>&)>;

    template <typename DomainType>
    struct LastValueCached {
        DomainType data;
        bool valid = false;
    };

    virtual ~Client();
    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;

    // PAUSED -> RUNNING. Unrelated to ThreadOwner::start(), which the SDK calls itself.
    Result startClient();
    // RUNNING -> PAUSED. While paused, callbacks are not called and cached values are not updated.
    Result pauseClient();
    // Any state -> DISCONNECTED (terminal). Tells the runtime and fires the state callback.
    Result disconnectClient();

    template <typename DomainType>
    Result registerCallback(std::function<void(std::shared_ptr<DomainType>)> callback) {
        static_assert(std::is_base_of<Abi::GenericMessage, DomainType>::value, "not an Omnicept message type");
        if (!callback) return isDisconnected() ? Result::ERROR_CLIENT_DISCONNECTED : Result::UNSPECIFIED_ERROR;
        return setCallback(DomainType::kMessageType, [callback](const std::shared_ptr<Abi::GenericMessage>& msg) {
            callback(std::static_pointer_cast<DomainType>(msg));
        });
    }

    template <typename DomainType>
    Result unregisterCallback() {
        return setCallback(DomainType::kMessageType, nullptr);
    }

    template <typename DomainType>
    bool isCallbackRegisteredForType() {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_callbacks.count(DomainType::kMessageType) != 0;
    }

    void clearAllCallbacks();

    template <typename DomainType>
    LastValueCached<DomainType> getLastData() {
        LastValueCached<DomainType> out;
        std::lock_guard<std::mutex> lock(m_mutex);
        auto it = m_lastValues.find(DomainType::kMessageType);
        if (it != m_lastValues.end()) {
            auto typed = std::dynamic_pointer_cast<DomainType>(it->second);
            if (!typed) throw Abi::SerializationError("cached message has an unexpected type");
            out.data = *typed;
            out.valid = true;
        }
        return out;
    }

    // Ask the runtime to start/stop recording session data. The callback gets
    // every DataVaultResult the runtime sends back.
    Result startDataRecord(std::function<void(std::shared_ptr<Abi::DataVaultResult>)> dvrCallback);
    Result stopDataRecord();

    State getClientState() const { return m_state.load(); }

    // Replace the set of messages the runtime should send. Takes effect
    // asynchronously; messages the license doesn't cover are simply not sent.
    Result setSubscriptions(const Abi::SubscriptionList& subList);

    // Extension: per-subscription answers from the runtime (approved, not
    // licensed, rejected by the user, ...).
    void setSubscriptionResultCallback(SubscriptionResultCallback_T callback);

    // Extension: identifier the runtime knows this connection by.
    const std::string& getConnectionId() const;

protected:
    void run() override;

private:
    friend class Glia;
    using AnyCallback = std::function<void(const std::shared_ptr<Abi::GenericMessage>&)>;

    Client(std::unique_ptr<detail::Connection> connection, StateCallback_T stateCallback);

    Result setCallback(Abi::MessageType type, AnyCallback callback);
    bool isDisconnected() const { return m_state.load() == State::DISCONNECTED; }
    void changeState(State newState);
    void handleDisconnect(bool notifyRuntime);
    void disconnectFromWorker();

    std::unique_ptr<detail::Connection> m_connection;
    StateCallback_T m_stateCallback;
    std::atomic<State> m_state{State::PAUSED};

    mutable std::mutex m_mutex;
    std::map<Abi::MessageType, AnyCallback> m_callbacks;
    std::map<Abi::MessageType, std::shared_ptr<Abi::GenericMessage>> m_lastValues;
    SubscriptionResultCallback_T m_subscriptionResultCallback;
    std::function<void(std::shared_ptr<Abi::DataVaultResult>)> m_dataVaultCallback;
    std::mutex m_disconnectMutex;
};

}}  // namespace HP::Omnicept
