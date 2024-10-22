# Project name
set(PROJECT libembeddedcan)

# Min CMake version
cmake_minimum_required(VERSION 3.19)

# Project definitions
# Src: https://github.com/raspberrypi/pico-examples/blob/f800a7e3031e278062639e070c5764adb4a8a0fc/CMakeLists.txt#L6
project(${PROJECT} C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)


add_executable(${PROJECT} src/main.cpp)

# These sources should be PUBLIC so dependents linking against this library inherit these.
target_sources(${PROJECT} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/src/message.h
    ${CMAKE_CURRENT_LIST_DIR}/src/providers/base.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/providers/bitrate.h
    ${CMAKE_CURRENT_LIST_DIR}/src/providers/rp2040/mcp2515.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/providers/rp2040/mcp2515/bitrate.h
)

