cmake_minimum_required(VERSION 3.16)

project(HitachiSpoofer
    VERSION 4.0.0
    LANGUAGES CXX C
    DESCRIPTION "Professional HWID Spoofing Tool"
)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Use folders in IDE
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Compiler flags for warnings and standards
if(MSVC)
    # MSVC specific flags
    add_compile_options(
        /W4                    # Warning level 4
        /utf-8                 # UTF-8 source
        /std:c++17            # C++17 standard
        /permissive-           # Standards conformance
        /WX                    # Warnings as errors in Release
    )
    
    # Disable specific warnings
    add_compile_options(
        /wd4100                # Unreferenced formal parameter
        /wd4201                # Nonstandard extension used
    )
    
    # Visual Studio specific
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-D_WIN32_WINNT=0x0601)  # Windows 7+
    
    # Optimization
    if(CMAKE_BUILD_TYPE MATCHES Release)
        add_compile_options(/O2 /Oi)
    endif()
else()
    # GCC/Clang flags
    add_compile_options(
        -Wall -Wextra -pedantic
        -fvisibility=hidden
        -fvisibility-inlines-hidden
    )
endif()

# Include paths
set(INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Source files
set(CORE_SOURCES
    src/core/hwid_generator.cpp
    src/core/spoofing_engine.cpp
)

set(DRIVER_SOURCES
    src/driver/driver_interface.cpp
)

set(UI_SOURCES
    src/ui/ui_manager.cpp
)

set(UTILS_SOURCES
    src/utils/logger.cpp
)

set(ALL_SOURCES
    src/main.cpp
    ${CORE_SOURCES}
    ${DRIVER_SOURCES}
    ${UI_SOURCES}
    ${UTILS_SOURCES}
)

# Create executable
add_executable(HitachiSpoofer WIN32 ${ALL_SOURCES})

# Set target properties
set_target_properties(HitachiSpoofer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    VS_STARTUP_PROJECT "HitachiSpoofer"
)

# Include directories
target_include_directories(HitachiSpoofer PRIVATE ${INCLUDE_DIRS})

# Precompiled headers (MSVC only)
if(MSVC)
    # Create a precompiled header
endif()

# Link libraries (Windows)
target_link_libraries(HitachiSpoofer PRIVATE
    # System libraries
    user32                 # Window management
    d3d11                  # DirectX 11
    d3dcompiler            # DirectX compiler
    dxgi                   # DXGI
    advapi32               # Registry & Security
    shell32                # Shell utilities
    oleaut32               # OLE automation
    winmm                  # Multimedia
)

# Debug specific
if(CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(HitachiSpoofer PRIVATE _DEBUG)
    if(MSVC)
        target_compile_options(HitachiSpoofer PRIVATE /Zi /Od /RTC1)
    endif()
else()
    target_compile_definitions(HitachiSpoofer PRIVATE NDEBUG)
    if(MSVC)
        target_compile_options(HitachiSpoofer PRIVATE /Zi)
        target_link_options(HitachiSpoofer PRIVATE /DEBUG:FULL)
    endif()
endif()

# Folder organization in IDE
set_target_properties(
    HitachiSpoofer PROPERTIES
    FOLDER "Applications"
)

if(MSVC)
    # Group source files in IDE
    source_group("Core" FILES ${CORE_SOURCES})
    source_group("Driver" FILES ${DRIVER_SOURCES})
    source_group("UI" FILES ${UI_SOURCES})
    source_group("Utils" FILES ${UTILS_SOURCES})
endif()

# Installation
install(
    TARGETS HitachiSpoofer
    RUNTIME DESTINATION bin
)

install(
    DIRECTORY include/
    DESTINATION include
)
