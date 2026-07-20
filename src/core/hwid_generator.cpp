#include "hwid_generator.h"
#include <random>
#include <sstream>
#include <iomanip>

using namespace UchihaSpoofer::Core;

std::string HWIDGenerator::GenerateMAC() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 255);
    
    std::stringstream ss;
    for (int i = 0; i < 6; ++i) {
        if (i > 0) ss << ":";
        ss << std::hex << std::setw(2) << std::setfill('0') << dis(gen);
    }
    
    return ss.str();
}

std::string HWIDGenerator::GenerateGUID() {
    // Implementation to generate GUID
    return "";
}

std::string HWIDGenerator::GenerateSerialNumber() {
    // Implementation to generate serial number
    return "";
}

std::string HWIDGenerator::GenerateProductID() {
    // Implementation to generate product ID
    return "";
}

std::string HWIDGenerator::BytesToHex(const unsigned char* data, size_t size) {
    std::stringstream ss;
    for (size_t i = 0; i < size; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)data[i];
    }
    return ss.str();
}
