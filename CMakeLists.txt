cmake_minimum_required(VERSION 3.20)

project(math-tools
    VERSION 0.1.0
    LANGUAGES CXX
)

# Defaults
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # for clangd / IDE tooling

# Default to release
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Reusable warnings
add_library(project_warnings INTERFACE)
target_compile_options(project_warnings INTERFACE
    -Wall -Wextra -Wpedantic -Wshadow -Wconversion
)

add_executable(math-tools
    src/main.cpp
    src/app.cpp
)

target_include_directories(math-tools PRIVATE include)
target_link_libraries(math-tools PRIVATE project_warnings)

# Testing
option(BUILD_TESTING "Build tests" OFF)
if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()