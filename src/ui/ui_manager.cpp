#include "ui_manager.h"
#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>

using namespace UchihaSpoofer::UI;

UIManager& UIManager::GetInstance() {
    static UIManager instance;
    return instance;
}

bool UIManager::Initialize(HWND hwnd) {
    if (m_initialized) return true;
    
    // Initialize ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    
    // Setup ImGui style
    ImGui::StyleColorsDark();
    
    // Initialize Win32 backend
    if (!ImGui_ImplWin32_Init(hwnd)) {
        return false;
    }
    
    // Initialize DirectX 11 backend
    if (!ImGui_ImplDX11_Init(m_device, m_context)) {
        ImGui_ImplWin32_Shutdown();
        return false;
    }
    
    m_initialized = true;
    return true;
}

void UIManager::Shutdown() {
    if (!m_initialized) return;
    
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    
    m_initialized = false;
}

void UIManager::BeginFrame() {
    if (!m_initialized) return;
    
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}

void UIManager::EndFrame() {
    if (!m_initialized) return;
    
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
