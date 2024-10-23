# Min CMake version
cmake_minimum_required(VERSION 3.19)

if (CAN_TARGET STREQUAL "pico")
    # Pull in pico sdk (must be before project() call)
    include(rp2040/pico-sdk.cmake)
endif()

project(
    libcan
    VERSION 0.0.1
    DESCRIPTION "can library"
    LANGUAGES CXX
)


if (CAN_TARGET STREQUAL "pico")
    pico_sdk_init()
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(core)




if (CAN_TARGET STREQUAL "pico")
    add_subdirectory(rp2040)
endif()