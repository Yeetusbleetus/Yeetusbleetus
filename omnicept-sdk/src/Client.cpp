#include "omnicept/Client.h"

#include "Codec.h"
#include "Connection.h"

namespace HP { namespace Omnicept {

using Abi::MessageType;

// ThreadOwner ------------------------------------------------------------------

namespace Utils {

ThreadOwner::~ThreadOwner() {
    requestStop();
    join();
}

void ThreadOwner::start() {
    if (m_thread.joinable()) return;
    m_continue = true;
    m_thread = std::thread([this] { run(); });
}

bool ThreadOwner::join() {
    if (!m_thread.joinable()) return false;
    if (m_thread.get_id() == std::this_thread::get_id()) {
        m_thread.detach();  // called from inside run(); can't join ourselves
        return false;
    }
    m_thread.join();
    return true;
}

}  // namespace Utils

// Client -----------------------------------------------------------------------

Client::Client(std::unique_ptr<detail::Connection> connection, StateCallback_T stateCallback)
    : m_connection(std::move(connection)), m_stateCallback(std::move(stateCallback)) {}

Client::~Client() {
    disconnectClient();
    requestStop();
    join();
}

const std::string& Client::getConnectionId() const { return m_connection->connectionId(); }

void Client::changeState(State newState) {
    State old = m_state.exchange(newState);
    if (old != newState && m_stateCallback) m_stateCallback(newState);
}

Client::Result Client::startClient() {
    State expected = State::PAUSED;
    if (m_state.compare_exchange_strong(expected, State::RUNNING)) {
        if (m_stateCallback) m_stateCallback(State::RUNNING);
        return Result::SUCCESS;
    }
    return expected == State::RUNNING ? Result::NO_OP_CLIENT_RUNNING : Result::ERROR_CLIENT_DISCONNECTED;
}

Client::Result Client::pauseClient() {
    State expected = State::RUNNING;
    if (m_state.compare_exchange_strong(expected, State::PAUSED)) {
        if (m_stateCallback) m_stateCallback(State::PAUSED);
        return Result::SUCCESS;
    }
    return expected == State::PAUSED ? Result::NO_OP_CLIENT_PAUSED : Result::ERROR_CLIENT_DISCONNECTED;
}

Client::Result Client::disconnectClient() {
    if (isDisconnected()) return Result::ERROR_CLIENT_DISCONNECTED;
    handleDisconnect(true);
    return Result::SUCCESS;
}

// User-initiated: tell the runtime, stop the worker, close everything.
void Client::handleDisconnect(bool notifyRuntime) {
    std::lock_guard<std::mutex> lock(m_disconnectMutex);
    if (isDisconnected()) return;
    requestStop();
    if (notifyRuntime) {
        try {
            m_connection->send(MessageType::moduleControlSignal,
                               detail::encodeModuleControlSignal(Abi::ModuleControlSignalType::MODULE_SIGNAL_STOP));
        } catch (const std::exception&) {
            // Best effort: the runtime may already be gone.
        }
    }
    join();
    m_connection->close();
    changeState(State::DISCONNECTED);
}

// Runtime-initiated (STOP signal or transport failure), called on the worker
// thread. Never joins. If a user-initiated disconnect already holds the lock,
// it is waiting for this thread to exit and will finish the job.
void Client::disconnectFromWorker() {
    std::unique_lock<std::mutex> lock(m_disconnectMutex, std::try_to_lock);
    if (!lock.owns_lock() || isDisconnected()) return;
    requestStop();
    m_connection->closeSend();
    m_connection->closeReceive();
    changeState(State::DISCONNECTED);
}

Client::Result Client::setCallback(MessageType type, AnyCallback callback) {
    if (isDisconnected()) return Result::ERROR_CLIENT_DISCONNECTED;
    std::lock_guard<std::mutex> lock(m_mutex);
    if (callback)
        m_callbacks[type] = std::move(callback);
    else
        m_callbacks.erase(type);
    return Result::SUCCESS;
}

void Client::clearAllCallbacks() {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_callbacks.clear();
}

Client::Result Client::setSubscriptions(const Abi::SubscriptionList& subList) {
    if (isDisconnected()) return Result::ERROR_CLIENT_DISCONNECTED;
    try {
        m_connection->send(MessageType::subscriptionList, detail::encodeSubscriptionList(subList));
    } catch (const std::exception&) {
        return Result::UNSPECIFIED_ERROR;
    }
    return Result::SUCCESS;
}

void Client::setSubscriptionResultCallback(SubscriptionResultCallback_T callback) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_subscriptionResultCallback = std::move(callback);
}

Client::Result Client::startDataRecord(std::function<void(std::shared_ptr<Abi::DataVaultResult>)> dvrCallback) {
    if (isDisconnected()) return Result::ERROR_CLIENT_DISCONNECTED;
    if (getClientState() == State::PAUSED) return Result::NO_OP_CLIENT_PAUSED;
    if (!dvrCallback) return Result::UNSPECIFIED_ERROR;
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_dataVaultCallback = std::move(dvrCallback);
    }
    try {
        m_connection->send(MessageType::dataVaultAction, detail::encodeDataVaultAction(true));
    } catch (const std::exception&) {
        return Result::UNSPECIFIED_ERROR;
    }
    return Result::SUCCESS;
}

Client::Result Client::stopDataRecord() {
    if (isDisconnected()) return Result::ERROR_CLIENT_DISCONNECTED;
    if (getClientState() == State::PAUSED) return Result::NO_OP_CLIENT_PAUSED;
    try {
        m_connection->send(MessageType::dataVaultAction, detail::encodeDataVaultAction(false));
    } catch (const std::exception&) {
        return Result::UNSPECIFIED_ERROR;
    }
    return Result::SUCCESS;
}

void Client::run() {
    const auto interval = m_connection->config().pollInterval;
    while (shouldContinue()) {
        detail::Envelope env;
        try {
            if (!m_connection->receive(env, interval)) continue;
        } catch (const std::exception&) {
            disconnectFromWorker();  // transport failure: the runtime went away
            return;
        }

        switch (env.type) {
            case MessageType::moduleControlSignal:
                try {
                    if (detail::decodeModuleControlSignal(env.body) ==
                        Abi::ModuleControlSignalType::MODULE_SIGNAL_STOP) {
                        disconnectFromWorker();
                        return;
                    }
                } catch (const Abi::SerializationError&) {
                }
                continue;
            case MessageType::subscriptionResultList: {
                SubscriptionResultCallback_T cb;
                {
                    std::lock_guard<std::mutex> lock(m_mutex);
                    cb = m_subscriptionResultCallback;
                }
                try {
                    if (cb) cb(detail::decodeSubscriptionResults(env.body));
                } catch (const Abi::SerializationError&) {
                }
                continue;
            }
            default:
                break;
        }

        // DataVault results are delivered even while paused: they answer an
        // explicit request.
        if (getClientState() != State::RUNNING && env.type != MessageType::dataVaultResult) continue;

        std::shared_ptr<Abi::GenericMessage> msg;
        try {
            msg = detail::decodeDomain(env);
        } catch (const Abi::SerializationError&) {
            continue;  // drop malformed messages
        }
        if (!msg) continue;

        AnyCallback cb;
        std::function<void(std::shared_ptr<Abi::DataVaultResult>)> dvCb;
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_lastValues[env.type] = msg;
            auto it = m_callbacks.find(env.type);
            if (it != m_callbacks.end()) cb = it->second;
            if (env.type == MessageType::dataVaultResult) dvCb = m_dataVaultCallback;
        }
        if (cb) cb(msg);
        if (dvCb) dvCb(std::static_pointer_cast<Abi::DataVaultResult>(msg));
    }
}

}}  // namespace HP::Omnicept
