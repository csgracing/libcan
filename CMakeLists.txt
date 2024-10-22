# Project name
set(PROJECT libembeddedcan)

# Min CMake version
cmake_minimum_required(VERSION 3.19)

# Project definitions
# Src: https://github.com/raspberrypi/pico-examples/blob/f800a7e3031e278062639e070c5764adb4a8a0fc/CMakeLists.txt#L6
project(${PROJECT} C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(core)
add_subdirectory(rp2040)