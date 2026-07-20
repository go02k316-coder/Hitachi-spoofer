#pragma execution_character_set("utf-8")

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <ctime>
#include <thread>
#include <memory>
#include <string>
#include <iostream>

// Core modules
#include "core/exception.h"
#include "utils/logger.h"
#include "core/hwid_generator.h"

using namespace UchihaSpoofer;

/**
 * @brief Application state structure
 */
struct AppState {
    int activeTab = 0;
    int previousTab = 0;
    float tabAlpha = 1.0f;
    bool isSpoofed = false;
    
    // Progress tracking
    struct OperationProgress {
        bool isRunning = false;
        float progress = 0.0f;
        std::string currentTask;
    };
    
    OperationProgress spoofProgress;
    OperationProgress recoveryProgress;
    OperationProgress cleanProgress;
};

// Global variables (minimized)
static AppState g_appState;
static HWND g_hwnd = nullptr;
static bool g_done = false;

/**
 * @brief Window procedure
 */
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_SIZE:
        if (msg == WM_SIZE && wParam != SIZE_MINIMIZED) {
            // Handle window resize
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

/**
 * @brief Initialize the application
 */
bool InitializeApplication() {
    try {
        // Initialize logger
        auto& logger = Utils::Logger::GetInstance();
        logger.SetMinLogLevel(Utils::LogLevel::Info);
        logger.InitializeFileLogging("uchiha_spoofer.log");
        
        logger.Info("========================================");
        logger.Info("Uchiha Spoofer v4.0.0 - Optimized Edition");
        logger.Info("========================================");
        logger.Info("Application initialization started...");
        
        // Test HWID generation
        logger.Debug("Testing HWID Generator...");
        auto hwid = Core::HWIDGenerator::GenerateComplete();
        logger.Info("Generated MAC Address: " + hwid.macAddress);
        logger.Info("Generated GUID: " + hwid.guid);
        logger.Info("Generated Product ID: " + hwid.productId);
        logger.Info("Generated Volume Serial C: " + hwid.volumeSerialC);
        
        logger.Info("Application initialized successfully!");
        return true;
    }
    catch (const Core::UchihaException& e) {
        Utils::Logger::GetInstance().Critical(std::string("Exception: ") + e.what());
        MessageBoxA(NULL, e.what(), "Uchiha Spoofer - Error", MB_ICONERROR);
        return false;
    }
    catch (const std::exception& e) {
        Utils::Logger::GetInstance().Critical(std::string("Std Exception: ") + e.what());
        MessageBoxA(NULL, e.what(), "Uchiha Spoofer - Error", MB_ICONERROR);
        return false;
    }
}

/**
 * @brief Create and show the main window
 */
bool CreateMainWindow() {
    try {
        auto& logger = Utils::Logger::GetInstance();
        logger.Info("Creating main window...");
        
        WNDCLASSEXA wc = {};
        wc.cbSize = sizeof(WNDCLASSEXA);
        wc.style = CS_CLASSDC;
        wc.lpfnWndProc = WndProc;
        wc.hInstance = GetModuleHandle(NULL);
        wc.lpszClassName = "UCHIHA_CLASS";
        
        if (!RegisterClassExA(&wc)) {
            throw Core::UchihaException(Core::ErrorCode::WindowCreationFailed,
                "Failed to register window class");
        }
        
        g_hwnd = CreateWindowA(
            wc.lpszClassName,
            "UCHIHA-HITACHI SPOOFER ULTIMATE v4.0 (Optimized)",
            WS_OVERLAPPEDWINDOW,
            100, 100, 1050, 670,
            NULL, NULL, wc.hInstance, NULL
        );
        
        if (!g_hwnd) {
            throw Core::UchihaException(Core::ErrorCode::WindowCreationFailed,
                "Cannot create window");
        }
        
        ShowWindow(g_hwnd, SW_SHOWDEFAULT);
        UpdateWindow(g_hwnd);
        
        logger.Info("Main window created successfully");
        return true;
    }
    catch (const Core::UchihaException& e) {
        Utils::Logger::GetInstance().Critical(std::string("Window Error: ") + e.what());
        return false;
    }
}

/**
 * @brief Main application loop
 */
int MainLoop() {
    auto& logger = Utils::Logger::GetInstance();
    logger.Info("Entering main loop...");
    
    int frameCount = 0;
    
    while (!g_done) {
        MSG msg = {};
        
        while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            
            if (msg.message == WM_QUIT) {
                g_done = true;
            }
        }
        
        if (g_done) break;
        
        // Frame update
        frameCount++;
        if (frameCount % 1000 == 0) {
            logger.Debug(std::string("Frame: ") + std::to_string(frameCount));
        }
        
        // Render frame
        // TODO: Implement rendering (ImGui to be integrated)
        
        // Sleep to prevent busy-wait
        Sleep(16);  // ~60 FPS
    }
    
    logger.Info("Main loop exited");
    return 0;
}

/**
 * @brief Shutdown the application
 */
void ShutdownApplication() {
    auto& logger = Utils::Logger::GetInstance();
    logger.Info("Shutting down application...");
    
    if (g_hwnd) {
        DestroyWindow(g_hwnd);
        g_hwnd = nullptr;
    }
    
    logger.Info("Saving logs...");
    logger.SaveToFile("uchiha_spoofer_session.log");
    logger.Info("Application shutdown complete");
}

/**
 * @brief Main entry point
 */
int main(int argc, char* argv[]) {
    try {
        srand(static_cast<unsigned int>(time(0)));
        
        // Initialize application
        if (!InitializeApplication()) {
            return 1;
        }
        
        // Create main window
        if (!CreateMainWindow()) {
            return 1;
        }
        
        // Run main loop
        int result = MainLoop();
        
        // Cleanup
        ShutdownApplication();
        
        return result;
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
