#include "spoofing_engine.h"

using namespace UchihaSpoofer::Core;

bool SpoofingEngine::ApplySpoofing(const std::string& hwid, ProgressCallback callback) {
    if (callback) {
        callback(0.5f, "Applying spoofing...");
    }
    m_isSpoofed = true;
    if (callback) {
        callback(1.0f, "Spoofing completed");
    }
    return true;
}

bool SpoofingEngine::RecoverOriginal(ProgressCallback callback) {
    if (callback) {
        callback(0.5f, "Recovering original...");
    }
    m_isSpoofed = false;
    if (callback) {
        callback(1.0f, "Recovery completed");
    }
    return true;
}

bool SpoofingEngine::IsSpoofed() const {
    return m_isSpoofed;
}
