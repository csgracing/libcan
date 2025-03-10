# Min CMake version
cmake_minimum_required(VERSION 3.19)

if (CAN_TARGET STREQUAL "pico")
    # Pull in pico sdk (must be before project() call)
    include(rp2040/pico-sdk.cmake)
endif()


if (IS_TEST_FUZZ_ENV STREQUAL "true")
    set(CMAKE_C_COMPILER "clang")
    set(CMAKE_CXX_COMPILER "clang++")
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
set(CMAKE_CXX_STANDARD 17)

# Tools


add_subdirectory(lib/common/boost)

if (IS_TEST_ENV STREQUAL "true" OR IS_TEST_FUZZ_ENV STREQUAL "true")

    # coverage setup
    set(CMAKE_BUILD_TYPE "Debug")
    
    include(lib/cmake/modules/CodeCoverage.cmake)

    if (IS_TEST_FUZZ_ENV STREQUAL "true")
        add_subdirectory(lib/google/fuzztest)
    else()
        add_subdirectory(lib/google/test)
        append_coverage_compiler_flags()

        list(APPEND COVERAGE_EXCLUDES
            ${CMAKE_SOURCE_DIR}/lib
            ${CMAKE_SOURCE_DIR}/out 
            ${CMAKE_SOURCE_DIR}/build
        
            ${CMAKE_SOURCE_DIR}/core/test
        
            ${CMAKE_SOURCE_DIR}/rp2040/lib
            ${CMAKE_SOURCE_DIR}/rp2040/mcp2515/lib
            ${CMAKE_SOURCE_DIR}/rp2040/mcp2515/test
        )
    endif()
    
    add_subdirectory(lib/google/gmock-global)

endif()

# Subprojects

add_subdirectory(core)

if (CAN_TARGET STREQUAL "pico")
    add_subdirectory(rp2040)
endif()

if (CAN_TARGET STREQUAL "linux")
    add_subdirectory(lib/linux/socketcan/libsockcanpp)
    add_subdirectory(linux/socketcan)
endif()

include(docs/docs.cmake)