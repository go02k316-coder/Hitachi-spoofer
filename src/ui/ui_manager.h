#pragma once

#include <windows.h>
#include <d3d11.h>

namespace UchihaSpoofer {
namespace UI {

/**
 * @brief UI Manager - Manages ImGui and rendering
 */
class UIManager {
public:
    static UIManager& GetInstance();
    
    bool Initialize(HWND hwnd);
    void Shutdown();
    
    void BeginFrame();
    void EndFrame();
    
    bool IsInitialized() const { return m_initialized; }
    
private:
    UIManager() = default;
    ~UIManager() = default;
    
    bool m_initialized = false;
    ID3D11Device* m_device = nullptr;
    ID3D11DeviceContext* m_context = nullptr;
};

} // namespace UI
} // namespace UchihaSpoofer
