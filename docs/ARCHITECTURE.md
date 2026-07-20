# Architecture Documentation

## Project Structure

### Core Module (`src/core/`)
Responsible for the main spoofing logic.

- **hwid_generator.cpp/h** - Generate fake HWID values
- **spoofing_engine.cpp/h** - Apply spoofing operations

### Driver Module (`src/driver/`)
Handles communication with kernel driver.

- **driver_interface.cpp/h** - Driver API wrapper
- **driver.h** - Driver binary data and definitions

### UI Module (`src/ui/`)
User interface implementation.

- **ui_manager.cpp/h** - Main UI manager
- **imgui_backend/** - ImGui library and implementations
  - ImGui core library files
  - DirectX 11 backend
  - Win32 window backend

### Utils Module (`src/utils/`)
Utility functions and helpers.

- **logger.h** - Logging system
- **security_utils.h** - Security/validation functions
- **version.h** - Version information

## Data Flow

```
User Input (UI)
     ↓
UI Manager
     ↓
Spoofer Engine
     ↓
Driver Interface
     ↓
Kernel Driver
     ↓
Registry/System Changes
```

## Key Classes

### Spoofer
Main spoofing engine. Coordinates all spoofing operations.

### IdentityManager
Manages original and fake HWID values.

### UIManager
Manages ImGui rendering and window events.

### ConfigManager
Handles profile save/load functionality.

### BackupManager
Manages system state backups for recovery.

## Threading Model

Async operations use std::thread for long-running tasks:
- Spoofing operations
- Cleanup processes
- File I/O

## Error Handling

Custom exception hierarchy:
- `UchihaException` - Base exception
- `DriverException` - Driver-related errors
- `RegistryException` - Registry operation errors
