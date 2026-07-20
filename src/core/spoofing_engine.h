#pragma once

#include <string>
#include <functional>

namespace UchihaSpoofer {
namespace Core {

/**
 * @brief Spoofing Engine - Applies HWID spoofing operations
 */
class SpoofingEngine {
public:
    using ProgressCallback = std::function<void(float, const std::string&)>;
    
    // Apply HWID spoofing
    bool ApplySpoofing(const std::string& hwid, ProgressCallback callback);
    
    // Recover original HWID
    bool RecoverOriginal(ProgressCallback callback);
    
    // Get spoofing status
    bool IsSpoofed() const;
    
private:
    bool m_isSpoofed = false;
};

} // namespace Core
} // namespace UchihaSpoofer
