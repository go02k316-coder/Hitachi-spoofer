#include "core/hwid_generator.h"
#include <random>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace UchihaSpoofer::Core;

std::string HWIDGenerator::GenerateMAC() {
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    
    for (int i = 0; i < 6; ++i) {
        if (i > 0) ss << ":";
        ss << std::setw(2) << static_cast<int>(RandomByte());
    }
    
    return ss.str();
}

std::string HWIDGenerator::GenerateGUID() {
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    
    // GUID format: {XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX}
    ss << "{";
    
    // First segment (8 hex digits)
    ss << std::setw(8) << RandomDword();
    ss << "-";
    
    // Second segment (4 hex digits)
    ss << std::setw(4) << (RandomDword() & 0xFFFF);
    ss << "-";
    
    // Third segment (4 hex digits)
    ss << std::setw(4) << (RandomDword() & 0xFFFF);
    ss << "-";
    
    // Fourth segment (4 hex digits)
    ss << std::setw(4) << (RandomDword() & 0xFFFF);
    ss << "-";
    
    // Fifth segment (12 hex digits)
    ss << std::setw(8) << RandomDword();
    ss << std::setw(4) << (RandomDword() & 0xFFFF);
    
    ss << "}";
    
    return ss.str();
}

std::string HWIDGenerator::GenerateSerialNumber() {
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    
    // Generate 8 random bytes as serial number
    for (int i = 0; i < 8; ++i) {
        ss << std::setw(2) << static_cast<int>(RandomByte());
    }
    
    return ss.str();
}

std::string HWIDGenerator::GenerateProductID() {
    // Windows Product ID format: XXXXX-XXXXX-XXXXX-XXXXX
    std::stringstream ss;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(10000, 99999);
    
    for (int i = 0; i < 4; ++i) {
        if (i > 0) ss << "-";
        ss << dis(gen);
    }
    
    return ss.str();
}

std::string HWIDGenerator::GenerateCPUSerial() {
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    
    // Generate CPU serial (typically 12 hex digits)
    for (int i = 0; i < 6; ++i) {
        ss << std::setw(2) << static_cast<int>(RandomByte());
    }
    
    return ss.str();
}

std::string HWIDGenerator::GenerateBIOSSerial() {
    // Generate BIOS serial (typically alphanumeric)
    std::stringstream ss;
    const char* chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 35);
    
    for (int i = 0; i < 12; ++i) {
        ss << chars[dis(gen)];
    }
    
    return ss.str();
}

std::string HWIDGenerator::GenerateVolumeSerial() {
    // Volume serial format: XXXX-XXXX
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    
    ss << std::setw(4) << (RandomDword() & 0xFFFF);
    ss << "-";
    ss << std::setw(4) << (RandomDword() & 0xFFFF);
    
    return ss.str();
}

HWIDData HWIDGenerator::GenerateComplete() {
    HWIDData data;
    data.macAddress = GenerateMAC();
    data.guid = GenerateGUID();
    data.serialNumber = GenerateSerialNumber();
    data.productId = GenerateProductID();
    data.cpuSerial = GenerateCPUSerial();
    data.biosSerial = GenerateBIOSSerial();
    data.volumeSerialC = GenerateVolumeSerial();
    data.volumeSerialD = GenerateVolumeSerial();
    return data;
}

unsigned char HWIDGenerator::RandomByte() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 255);
    return static_cast<unsigned char>(dis(gen));
}

uint32_t HWIDGenerator::RandomDword() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<uint32_t> dis(0, 0xFFFFFFFF);
    return dis(gen);
}

std::string HWIDGenerator::BytesToHex(const unsigned char* data, size_t size) {
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    
    for (size_t i = 0; i < size; ++i) {
        ss << std::setw(2) << static_cast<int>(data[i]);
    }
    
    return ss.str();
}
