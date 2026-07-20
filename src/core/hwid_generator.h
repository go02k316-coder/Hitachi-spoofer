#pragma once

#include <string>
#include <windows.h>

namespace UchihaSpoofer {
namespace Core {

/**
 * @brief HWID Generator - Generates hardware identifiers
 */
class HWIDGenerator {
public:
    // Generate random MAC address
    static std::string GenerateMAC();
    
    // Generate random GUID
    static std::string GenerateGUID();
    
    // Generate random serial number
    static std::string GenerateSerialNumber();
    
    // Generate random Product ID
    static std::string GenerateProductID();
    
private:
    static std::string BytesToHex(const unsigned char* data, size_t size);
};

} // namespace Core
} // namespace UchihaSpoofer
