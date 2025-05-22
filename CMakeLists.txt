# Min CMake version
cmake_minimum_required(VERSION 3.19)

if (CAN_TARGET STREQUAL "pico")
    # Pull in pico sdk (must be before project() call)
    include(src/rp2040/pico-sdk.cmake)
    
    add_compile_definitions(BOOST_SYSTEM_DISABLE_THREADS)

elseif (IS_TEST_FUZZ_ENV STREQUAL "true")
    set(CMAKE_C_COMPILER "clang" CACHE STRING "C compiler to use")
    set(CMAKE_CXX_COMPILER "clang++" CACHE STRING "C++ compiler to use")
else()
# if cache not set vsc no happy
# https://github.com/microsoft/vscode-cmake-tools/issues/2121#issuecomment-919324503
    set(CMAKE_C_COMPILER "gcc" CACHE STRING "C compiler to use")
    set(CMAKE_CXX_COMPILER "g++" CACHE STRING "C++ compiler to use")
endif()

project(
    libcan
    VERSION 0.0.1
    DESCRIPTION "Provider-agnostic CAN library"
    LANGUAGES CXX
)


if (CAN_TARGET STREQUAL "pico")
    pico_sdk_init()
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20) # "using enum" in core

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if (IS_TEST_ENV STREQUAL "true" OR IS_TEST_FUZZ_ENV STREQUAL "true")

    # for config
    set(LIBCAN_DEBUG TRUE)

    # coverage setup
    set(CMAKE_BUILD_TYPE "Debug")
    
    include(lib/cmake/modules/CodeCoverage.cmake)

    if (IS_TEST_FUZZ_ENV STREQUAL "true")
        add_subdirectory(lib/test/google/fuzztest)
    else()
        add_subdirectory(lib/test/google/test)
        append_coverage_compiler_flags()

        list(APPEND COVERAGE_EXCLUDES
            ${CMAKE_SOURCE_DIR}/lib
            ${CMAKE_SOURCE_DIR}/out 
            ${CMAKE_SOURCE_DIR}/build
            ${CMAKE_SOURCE_DIR}/test
        )
    endif()
    
    add_subdirectory(lib/test/google/gmock-global)

endif()

# Dependencies

add_subdirectory(lib/common/boost)
add_subdirectory(lib/common/moodycamel/concurrentqueue)
add_subdirectory(lib/common/fmt)
add_subdirectory(lib/common/plog)

# Subprojects

add_subdirectory(src/core)
add_subdirectory(test/core)

if (CAN_TARGET STREQUAL "pico")
    add_subdirectory(src/rp2040)
    add_subdirectory(test/rp2040)
    
endif()

if (CAN_TARGET STREQUAL "linux")
    add_subdirectory(lib/linux/socketcan/libsockcanpp)
    add_subdirectory(src/linux/socketcan)
    add_subdirectory(standalone/linux/socketcan)
endif()

include(docs/docs.cmake)

# Tools

include(ExternalProject)

ExternalProject_Add(
    bloaty
    PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/build/tools/bloaty/src
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/tools/google/bloaty
    BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build/tools/bloaty/bin
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_SOURCE_DIR}/build/tools/_share/
    UPDATE_COMMAND "" # dont rebuild every time! <https://stackoverflow.com/a/64994225>
)