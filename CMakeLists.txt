# Min CMake version
cmake_minimum_required(VERSION 3.19)

project(
    libcan
    VERSION 0.0.1
    DESCRIPTION "can library"
    LANGUAGES CXX
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(core)
add_subdirectory(rp2040)