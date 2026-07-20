# HWID Spoofer - Hitachi Edition

A professional HWID (Hardware Identifier) spoofing tool with ImGui-based user interface.

## Features

- 🎯 HWID Spoofing (MAC Address, Machine GUID, HW Profile, Product ID, Volume Serial)
- 🎨 ImGui-based modern UI with Real-time feedback
- 💾 Profile Management (Save/Load/Delete spoof configurations)
- 🧹 Deep Clean Engine (Clear logs, cache, traces)
- 📦 Backup & Recovery System
- 🔐 Admin privilege validation
- 🔄 Async operation support

## Project Structure

```
hwid-spoofer/
├── src/
│   ├── core/              # Core spoofing logic
│   ├── driver/            # Driver communication
│   ├── ui/                # User Interface
│   ├── utils/             # Utilities
│   └── main.cpp           # Application entry point
├── include/               # Public headers
├── docs/                  # Documentation
├── build/                 # Build output
└── CMakeLists.txt         # CMake configuration
```

## Build

### Windows (Visual Studio)

```bash
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
```

### Requirements

- Windows 10 or later
- Visual Studio 2019+
- CMake 3.16+
- Admin privileges for running

## Usage

1. Run with Administrator privileges
2. Navigate through tabs using the sidebar
3. Select options and click "Start Spoof" to begin
4. Use Deep Clean to remove traces
5. Restore original HWID with "Recover Original"

## Safety & Disclaimer

This tool modifies system identifiers. Always create backups before use.

## License

MIT License
