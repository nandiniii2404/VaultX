cmake_minimum_required(VERSION 3.14)
project(VaultX VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCES
    src/main.cpp
    src/FileManager.cpp
    src/EncryptionEngine.cpp
    src/OutputHandler.cpp
    src/VaultX.cpp
)

# Include directories
include_directories(include)

# Executable
add_executable(vaultx ${SOURCES})

# Link filesystem library (required for some compilers)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.0)
    target_link_libraries(vaultx stdc++fs)
endif()

# Compiler warnings
if(MSVC)
    target_compile_options(vaultx PRIVATE /W4)
else()
    target_compile_options(vaultx PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Build type defaults
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()
