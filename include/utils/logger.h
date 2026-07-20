#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <mutex>
#include <ctime>
#include <sstream>
#include <memory>
#include "singleton.h"

namespace UchihaSpoofer {
namespace Utils {

/**
 * @brief Log levels
 */
enum class LogLevel {
    Trace,
    Debug,
    Info,
    Warning,
    Error,
    Critical
};

/**
 * @brief Thread-safe logger with file and memory support
 */
class Logger : public Singleton<Logger> {
friend class Singleton<Logger>;

private:
    std::vector<std::string> m_logsMemory;
    std::ofstream m_logFile;
    mutable std::mutex m_logMutex;
    bool m_fileLoggingEnabled = false;
    LogLevel m_minLogLevel = LogLevel::Info;
    
    Logger() = default;
    ~Logger();
    
    std::string GetTimestamp() const;
    std::string GetLevelString(LogLevel level) const;
    
public:
    /**
     * @brief Initialize file logging
     */
    bool InitializeFileLogging(const std::string& filename);
    
    /**
     * @brief Set minimum log level
     */
    void SetMinLogLevel(LogLevel level) noexcept { m_minLogLevel = level; }
    
    /**
     * @brief Add log with specific level
     */
    void Log(LogLevel level, const std::string& message);
    
    // Convenience methods
    void Trace(const std::string& message) { Log(LogLevel::Trace, message); }
    void Debug(const std::string& message) { Log(LogLevel::Debug, message); }
    void Info(const std::string& message) { Log(LogLevel::Info, message); }
    void Warning(const std::string& message) { Log(LogLevel::Warning, message); }
    void Error(const std::string& message) { Log(LogLevel::Error, message); }
    void Critical(const std::string& message) { Log(LogLevel::Critical, message); }
    
    /**
     * @brief Get all logs
     */
    std::vector<std::string> GetLogs() const;
    
    /**
     * @brief Get recent N logs
     */
    std::vector<std::string> GetRecentLogs(size_t count) const;
    
    /**
     * @brief Clear memory logs
     */
    void ClearLogs();
    
    /**
     * @brief Get log count
     */
    size_t GetLogCount() const noexcept;
    
    /**
     * @brief Get last log
     */
    std::string GetLastLog() const;
    
    /**
     * @brief Save all logs to file
     */
    bool SaveToFile(const std::string& filename);
    
    /**
     * @brief Check if file logging is enabled
     */
    bool IsFileLoggingEnabled() const noexcept { return m_fileLoggingEnabled; }
};

} // namespace Utils
} // namespace UchihaSpoofer
