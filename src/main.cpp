#pragma execution_character_set("utf-8")

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>
#include <ctime>
#include <thread>

// Core modules
#include "core/exception.h"
#include "core/types.h"

// Utils modules
#include "utils/logger.h"
#include "utils/system_utils.h"
#include "utils/string_utils.h"
#include "utils/file_utils.h"
#include "utils/cache_manager.h"
#include "utils/async_worker.h"

// Driver module
#include "driver/driver_manager.h"

// Spoofing modules
#include "core/identity_manager.h"
#include "core/spoofer.h"
#include "core/deep_cleaner.h"
#include "core/config_manager.h"
#include "core/hwid_presets.h"
#include "core/backup_manager.h"

// UI modules
#include "ui/ui_manager.h"
#include "ui/ui_styles.h"
#include "ui/components.h"

using namespace UchihaSpoofer;

// Forward declarations
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Global state
struct AppState {
    int activeTab = 0;
    int previousTab = 0;
    float tabAlpha = 1.0f;
    bool isSpoofed = false;
    Core::SpoofConfig spoofConfig;
    Core::OperationProgress spoofProgress;
    Core::OperationProgress recoveryProgress;
    Core::OperationProgress cleanProgress;
    
    // Profile management
    std::vector<std::string> profileList;
    int selectedProfileIdx = 0;
    char customHWIDInput[256] = {0};
    int selectedPresetIdx = 0;
    int selectedBackupIdx = 0;
};

static AppState g_appState;
static HWND g_hwnd = nullptr;
static bool g_done = false;

// Window procedure
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg) {
    case WM_SIZE:
        if (msg == WM_SIZE && wParam != SIZE_MINIMIZED) {
            auto& ui = UI::UIManager::GetInstance();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU)
            return 0;
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        g_done = true;
        return 0;
    }
    return DefWindowProcA(hWnd, msg, wParam, lParam);
}

// Render main interface
void RenderMainUI() {
    // Implementation from original HWID Spoofer.cpp
    // UI rendering code here...
}

int main(int, char**) {
    try {
        srand(static_cast<unsigned int>(time(0)));

        // Initialize Logger
        auto& logger = Utils::Logger::GetInstance();
        logger.Info("[MAIN] Uchiha Spoofer v4.0.0 - Optimized Edition");
        logger.Info("[MAIN] Starting application...");

        // Initialize Identity Manager and load original identity
        auto& idManager = Spoofing::IdentityManager::GetInstance();
        idManager.LoadOriginalIdentity();
        idManager.GenerateFakeIdentity();
        g_appState.spoofConfig = Core::SpoofConfig();

        // Initialize Config Manager
        auto& configMgr = Spoofing::ConfigManager::GetInstance();
        configMgr.LoadAllProfiles();

        // Initialize Driver Manager
        auto& driverMgr = Driver::DriverManager::GetInstance();
        if (!driverMgr.Initialize()) {
            logger.Warning("[MAIN] Driver could not be initialized (non-critical)");
        }

        // Create window
        WNDCLASSEXA wc = {sizeof(WNDCLASSEXA), CS_CLASSDC, WndProc, 0L, 0L,
                         GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
                         "UCHIHA_CLASS", NULL};
        RegisterClassExA(&wc);

        g_hwnd = CreateWindowA(wc.lpszClassName,
                              "UCHIHA-HITACHI SPOOFER ULTIMATE v4.0 (Optimized)",
                              WS_OVERLAPPEDWINDOW, 100, 100, 1050, 670,
                              NULL, NULL, wc.hInstance, NULL);

        if (!g_hwnd) {
            throw Core::UchihaException(Core::ErrorCode::WindowCreationFailed,
                "Cannot create window");
        }

        // Initialize UI Manager
        auto& uiManager = UI::UIManager::GetInstance();
        if (!uiManager.Initialize(g_hwnd)) {
            throw Core::UchihaException(Core::ErrorCode::ImGuiInitializationFailed,
                "Cannot initialize ImGui");
        }

        ShowWindow(g_hwnd, SW_SHOWDEFAULT);
        UpdateWindow(g_hwnd);

        logger.Info("[MAIN] UI initialized successfully!");
        logger.Info("[MAIN] Welcome to Uchiha Spoofer v4.0!");

        // Main game loop
        while (!g_done) {
            MSG msg;
            while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
                if (msg.message == WM_QUIT)
                    g_done = true;
            }
            if (g_done) break;

            // Render frame
            uiManager.BeginFrame();
            RenderMainUI();
            uiManager.EndFrame();
        }

        // Cleanup
        logger.Info("[MAIN] Shutting down...");
        uiManager.Shutdown();
        driverMgr.Shutdown();
        DestroyWindow(g_hwnd);
        UnregisterClassA(wc.lpszClassName, wc.hInstance);

        logger.Info("[MAIN] Uchiha Spoofer shutdown complete!");
        logger.SaveToFile("uchiha_session.log");

        return 0;
    }
    catch (const Core::UchihaException& e) {
        Utils::Logger::GetInstance().Critical(std::string("[MAIN] Exception: ") + e.what());
        MessageBoxA(NULL, e.what(), "Uchiha Spoofer - Fatal Error", MB_ICONERROR);
        return 1;
    }
    catch (const std::exception& e) {
        std::string msg = std::string("[MAIN] Std Exception: ") + e.what();
        Utils::Logger::GetInstance().Critical(msg);
        MessageBoxA(NULL, msg.c_str(), "Uchiha Spoofer - Fatal Error", MB_ICONERROR);
        return 1;
    }
    catch (...) {
        Utils::Logger::GetInstance().Critical("[MAIN] Unknown exception!");
        MessageBoxA(NULL, "Unknown exception occurred!", "Uchiha Spoofer - Fatal Error", MB_ICONERROR);
        return 1;
    }
}
