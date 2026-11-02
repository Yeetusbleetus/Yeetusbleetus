#pragma once

#include <string>

namespace HP { namespace Omnicept { namespace Abi {

enum class LicensingModel {
    UNKNOWN = 0,
    CORE = 1,
    TRIAL = 2,
    ENTERPRISE = 3,
    REV_SHARE = 4,  // developer / academic licenses
};

// Credentials from your HP Omnicept developer account. They are passed to the
// runtime unchanged; the runtime decides what the license allows.
class SessionLicense {
public:
    SessionLicense(std::string clientId, std::string accessKey, LicensingModel requestedLicense,
                   bool isRunningInEditor)
        : m_clientId(std::move(clientId)),
          m_accessKey(std::move(accessKey)),
          m_requestedLicense(requestedLicense),
          m_isRunningInEditor(isRunningInEditor) {}

    // A Core license is the only kind that may be requested without credentials.
    static SessionLicense Core() { return SessionLicense("", "", LicensingModel::CORE, false); }

    bool operator==(const SessionLicense& other) const {
        return m_clientId == other.m_clientId && m_accessKey == other.m_accessKey &&
               m_requestedLicense == other.m_requestedLicense && m_isRunningInEditor == other.m_isRunningInEditor;
    }

    const std::string& getClientId() const { return m_clientId; }
    const std::string& getAccessKey() const { return m_accessKey; }
    LicensingModel getRequestedLicense() const { return m_requestedLicense; }
    bool getIsRunningInEditor() const { return m_isRunningInEditor; }

private:
    std::string m_clientId;
    std::string m_accessKey;
    LicensingModel m_requestedLicense;
    bool m_isRunningInEditor;
};

}}}  // namespace HP::Omnicept::Abi
