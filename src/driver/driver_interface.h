#pragma once

#include <string>
#include <windows.h>

namespace UchihaSpoofer {
namespace Driver {

/**
 * @brief Driver Interface - Communication with kernel driver
 */
class DriverInterface {
public:
    bool Initialize();
    void Shutdown();
    
    bool ExecuteCommand(const std::string& command);
    bool LoadDriver();
    bool UnloadDriver();
    
    bool IsLoaded() const { return m_loaded; }
    
private:
    bool m_loaded = false;
    HANDLE m_deviceHandle = INVALID_HANDLE_VALUE;
};

} // namespace Driver
} // namespace UchihaSpoofer
