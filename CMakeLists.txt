cmake_minimum_required(VERSION 3.16)

project(HitachiSpoofer
    VERSION 4.0.0
    LANGUAGES CXX C
    DESCRIPTION "Professional HWID Spoofing Tool"
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler flags
if(MSVC)
    add_compile_options(/W4 /utf-8)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# Source files
set(SOURCES
    src/main.cpp
    src/core/hwid_generator.cpp
    src/core/spoofing_engine.cpp
    src/driver/driver_interface.cpp
    src/ui/ui_manager.cpp
    src/ui/imgui_backend/imgui.cpp
    src/ui/imgui_backend/imgui_draw.cpp
    src/ui/imgui_backend/imgui_tables.cpp
    src/ui/imgui_backend/imgui_widgets.cpp
    src/ui/imgui_backend/imgui_impl_win32.cpp
    src/ui/imgui_backend/imgui_impl_dx11.cpp
)

# Create executable
add_executable(HitachiSpoofer WIN32 ${SOURCES})

# Include directories
target_include_directories(HitachiSpoofer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link libraries (Windows)
target_link_libraries(HitachiSpoofer PRIVATE
    user32
    d3d11
    d3dcompiler
    dxgi
    advapi32
    shell32
)

# Output directory
set_target_properties(HitachiSpoofer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
