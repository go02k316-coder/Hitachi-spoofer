#pragma once

// Application configuration constants

namespace UchihaSpoofer {
namespace Config {

// Window
const int WINDOW_WIDTH = 1050;
const int WINDOW_HEIGHT = 650;
const char* WINDOW_TITLE = "UCHIHA-HITACHI SPOOFER ULTIMATE v4.0 (Optimized)";

// Paths
const char* CONFIG_DIR = "./config";
const char* BACKUP_DIR = "./backups";
const char* PROFILES_DIR = "./profiles";
const char* LOG_FILE = "uchiha_session.log";

// Timing
const float TAB_FADE_SPEED = 4.5f;
const float SHARINGAN_SPEED = 1.8f;
const float SHARINGAN_SPEED_ACTIVE = 6.0f;

// UI
const int SIDEBAR_WIDTH = 240;
const int CONSOLE_HEIGHT = 150;
const int CONSOLE_WIDTH = 750;

} // namespace Config
} // namespace UchihaSpoofer
