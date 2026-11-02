#pragma once

#include <stdexcept>
#include <string>

namespace HP { namespace Omnicept { namespace Abi {

enum class ConfigurationErrorCode_t {
    UNKNOWN_ERROR,
    FILE_NOT_FOUND,
    FILE_PATH_OVERFLOW,
    FILE_ACCESS_DENIED,
    FILE_CLOSE_FAILED,
    FILE_CORRUPTED,
    ATTRIBUTE_NOT_FOUND,
    ATTRIBUTE_WRITE_FAILED,
    ATTRIBUTE_NAME_INVALID,
    ATTRIBUTE_DELETE_FAILED,
    ATTRIBUTE_VALUE_OVERFLOW,
    ATTRIBUTE_VALUE_CORRUPTED,
};

// Thrown when the runtime rejects the connection handshake (or it times out).
class HandshakeError : public std::exception {
public:
    explicit HandshakeError(const std::string& what_arg) : m_what(what_arg) {}
    explicit HandshakeError(const char* what_arg) : m_what(what_arg) {}
    const char* what() const noexcept override { return m_what.c_str(); }
    virtual ~HandshakeError() = default;

private:
    std::string m_what;
};

// An unexpected message, or a message in the wrong order.
class ProtocolError : public std::logic_error {
public:
    using std::logic_error::logic_error;
    virtual ~ProtocolError() = default;
};

// The socket layer could not send or receive bytes.
class TransportError : public std::logic_error {
public:
    using std::logic_error::logic_error;
    virtual ~TransportError() = default;
};

// The underlying connection mechanism failed.
class ConnectionError : public std::logic_error {
public:
    using std::logic_error::logic_error;
    virtual ~ConnectionError() = default;
};

// A message could not be (de)serialized.
class SerializationError : public std::logic_error {
public:
    using std::logic_error::logic_error;
    virtual ~SerializationError() = default;
};

class ConfigurationError : public std::logic_error {
public:
    explicit ConfigurationError(const std::string& what_arg, ConfigurationErrorCode_t errorCode)
        : std::logic_error(what_arg), m_errorCode(errorCode) {}
    explicit ConfigurationError(const char* what_arg, ConfigurationErrorCode_t errorCode)
        : std::logic_error(what_arg), m_errorCode(errorCode) {}
    virtual ~ConfigurationError() = default;

    ConfigurationErrorCode_t m_errorCode;
};

}}}  // namespace HP::Omnicept::Abi
