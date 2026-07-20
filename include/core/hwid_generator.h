#pragma once

#include <string>
#include <vector>
#include <windows.h>

namespace UchihaSpoofer {
namespace Core {

/**
 * @brief Structure to hold HWID information
 */
struct HWIDData {
    std::string macAddress;
    std::string guid;
    std::string serialNumber;
    std::string productId;
    std::string cpuSerial;
    std::string biosSerial;
    std::string volumeSerialC;
    std::string volumeSerialD;
};

/**
 * @brief HWID Generator - Generates and manages hardware identifiers
 */
class HWIDGenerator {
public:
    /**
     * @brief Generate random MAC address (format: XX:XX:XX:XX:XX:XX)
     */
    static std::string GenerateMAC();
    
    /**
     * @brief Generate random GUID (format: {XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX})
     */
    static std::string GenerateGUID();
    
    /**
     * @brief Generate random serial number
     */
    static std::string GenerateSerialNumber();
    
    /**
     * @brief Generate random Product ID (Windows)
     */
    static std::string GenerateProductID();
    
    /**
     * @brief Generate random CPU serial number
     */
    static std::string GenerateCPUSerial();
    
    /**
     * @brief Generate random BIOS serial number
     */
    static std::string GenerateBIOSSerial();
    
    /**
     * @brief Generate random Volume Serial Number
     */
    static std::string GenerateVolumeSerial();
    
    /**
     * @brief Generate complete HWID data
     */
    static HWIDData GenerateComplete();
    
private:
    static std::string BytesToHex(const unsigned char* data, size_t size);
    static unsigned char RandomByte();
    static uint32_t RandomDword();
};

} // namespace Core
} // namespace UchihaSpoofer
