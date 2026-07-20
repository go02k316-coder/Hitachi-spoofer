#include "utils/logger.h"
#include <iostream>
#include <iomanip>

using namespace UchihaSpoofer::Utils;

Logger::~Logger() {
    if (m_logFile.is_open()) {
        m_logFile.close();
    }
}

std::string Logger::GetTimestamp() const {
    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now);
    
    std::ostringstream oss;
    oss << std::put_time(&ltm, "%H:%M:%S");
    return oss.str();
}

std::string Logger::GetLevelString(LogLevel level) const {
    switch (level) {
        case LogLevel::Trace:    return "TRACE";
        case LogLevel::Debug:    return "DEBUG";
        case LogLevel::Info:     return "INFO";
        case LogLevel::Warning:  return "WARN";
        case LogLevel::Error:    return "ERROR";
        case LogLevel::Critical: return "CRIT";
        default:                 return "UNKNOWN";
    }
}

bool Logger::InitializeFileLogging(const std::string& filename) {
    std::lock_guard<std::mutex> lock(m_logMutex);
    
    m_logFile.open(filename, std::ios::app);
    if (!m_logFile.is_open()) {
        return false;
    }
    
    m_fileLoggingEnabled = true;
    m_logFile << "\n====================================\n";
    m_logFile << "LOG SESSION STARTED - " << GetTimestamp() << "\n";
    m_logFile << "====================================\n\n";
    m_logFile.flush();
    
    return true;
}

void Logger::Log(LogLevel level, const std::string& message) {
    if (level < m_minLogLevel) return;
    
    std::lock_guard<std::mutex> lock(m_logMutex);
    
    std::string levelStr = GetLevelString(level);
    std::string timestamp = GetTimestamp();
    std::string formattedMsg = "[" + timestamp + "] [" + levelStr + "] " + message;
    
    m_logsMemory.push_back(formattedMsg);
    
    // Keep only last 1000 logs in memory
    if (m_logsMemory.size() > 1000) {
        m_logsMemory.erase(m_logsMemory.begin());
    }
    
    // Write to file if enabled
    if (m_fileLoggingEnabled && m_logFile.is_open()) {
        m_logFile << formattedMsg << "\n";
        m_logFile.flush();
    }
    
    // Also output to console in debug mode
    #ifdef _DEBUG
    std::cout << formattedMsg << std::endl;
    #endif
}

std::vector<std::string> Logger::GetLogs() const {
    std::lock_guard<std::mutex> lock(m_logMutex);
    return m_logsMemory;
}

std::vector<std::string> Logger::GetRecentLogs(size_t count) const {
    std::lock_guard<std::mutex> lock(m_logMutex);
    std::vector<std::string> recent;
    
    size_t start = m_logsMemory.size() > count ? m_logsMemory.size() - count : 0;
    recent.insert(recent.begin(), m_logsMemory.begin() + start, m_logsMemory.end());
    
    return recent;
}

void Logger::ClearLogs() {
    std::lock_guard<std::mutex> lock(m_logMutex);
    m_logsMemory.clear();
}

size_t Logger::GetLogCount() const noexcept {
    std::lock_guard<std::mutex> lock(m_logMutex);
    return m_logsMemory.size();
}

std::string Logger::GetLastLog() const {
    std::lock_guard<std::mutex> lock(m_logMutex);
    if (m_logsMemory.empty()) return "";
    return m_logsMemory.back();
}

bool Logger::SaveToFile(const std::string& filename) {
    std::lock_guard<std::mutex> lock(m_logMutex);
    std::ofstream file(filename);
    
    if (!file.is_open()) {
        return false;
    }
    
    for (const auto& log : m_logsMemory) {
        file << log << "\n";
    }
    
    file.close();
    return true;
}
