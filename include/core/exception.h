#pragma once

#include <exception>
#include <string>
#include <sstream>

namespace UchihaSpoofer {
namespace Core {

/**
 * @brief Error codes for exception handling
 */
enum class ErrorCode {
    Success = 0,
    DriverInitializationFailed = 1001,
    DriverNotLoaded = 1002,
    RegistryAccessDenied = 1003,
    RegistryModificationFailed = 1004,
    WindowCreationFailed = 2001,
    ImGuiInitializationFailed = 2002,
    DirectXInitializationFailed = 2003,
    InvalidConfigFile = 3001,
    ConfigSaveFailed = 3002,
    BackupCreationFailed = 4001,
    BackupRestoreFailed = 4002,
    InvalidParameters = 5001,
    UnknownError = 9999
};

/**
 * @brief Exception class for Uchiha Spoofer
 */
class UchihaException : public std::exception {
private:
    ErrorCode m_errorCode;
    std::string m_message;
    std::string m_fullMessage;
    
    void BuildFullMessage() {
        std::ostringstream oss;
        oss << "[ErrorCode: " << static_cast<int>(m_errorCode) << "] " << m_message;
        m_fullMessage = oss.str();
    }
    
public:
    /**
     * @brief Constructor with error code and message
     */
    UchihaException(ErrorCode code, const std::string& message)
        : m_errorCode(code), m_message(message) {
        BuildFullMessage();
    }
    
    /**
     * @brief Constructor with message only
     */
    explicit UchihaException(const std::string& message)
        : m_errorCode(ErrorCode::UnknownError), m_message(message) {
        BuildFullMessage();
    }
    
    /**
     * @brief Get error code
     */
    ErrorCode GetErrorCode() const noexcept { return m_errorCode; }
    
    /**
     * @brief Get error message
     */
    const std::string& GetMessage() const noexcept { return m_message; }
    
    /**
     * @brief Get C-string representation
     */
    const char* what() const noexcept override {
        return m_fullMessage.c_str();
    }
};

/**
 * @brief Driver-specific exception
 */
class DriverException : public UchihaException {
public:
    explicit DriverException(const std::string& message)
        : UchihaException(ErrorCode::DriverInitializationFailed, message) {}
};

/**
 * @brief Registry operation exception
 */
class RegistryException : public UchihaException {
public:
    explicit RegistryException(const std::string& message)
        : UchihaException(ErrorCode::RegistryAccessDenied, message) {}
};

} // namespace Core
} // namespace UchihaSpoofer
