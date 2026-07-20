# Build Guide

## Prerequisites

- Windows 10 or later (x64)
- Visual Studio 2019 or 2022
- CMake 3.16 or higher
- Git

## Build Steps

### 1. Clone Repository

```bash
git clone https://github.com/go02k316-coder/Hitachi-spoofer.git
cd Hitachi-spoofer
```

### 2. Create Build Directory

```bash
mkdir build
cd build
```

### 3. Generate Project Files

```bash
cmake .. -G "Visual Studio 17 2022" -A x64
```

For Visual Studio 2019:
```bash
cmake .. -G "Visual Studio 16 2019" -A x64
```

### 4. Build

**Option A: Command Line**
```bash
cmake --build . --config Release
```

**Option B: Visual Studio IDE**
```
Open HitachiSpoofer.sln and build in Visual Studio
```

### 5. Output

Executable will be at: `build/bin/HitachiSpoofer.exe`

## Build Configuration

### Release Build
```bash
cmake --build . --config Release
```

### Debug Build
```bash
cmake --build . --config Debug
```

## Troubleshooting

### CMake not found
- Install CMake from https://cmake.org/download/
- Add to PATH environment variable

### Visual Studio not found
- Install Visual Studio 2019+ with C++ development tools
- Ensure workload "Desktop development with C++" is selected

### Build errors
- Clean build: `cmake --build . --config Release --clean-first`
- Check Windows SDK version matches Visual Studio installation

## Development Build

For faster compilation during development:

```bash
cmake -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Debug -- /p:Configuration=Debug
```
