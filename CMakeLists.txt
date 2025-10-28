# Min CMake version
cmake_minimum_required(VERSION 3.25)

set(CAN_VERSION 0.0.1 CACHE STRING "libcan version string")

include(can/options.cmake)

if (CAN_DRIVER_RP2)
    # Pull in pico sdk (must be before project() call)
    include(can/driver/rp2/pico-sdk.cmake)
    
    set(PICO_CXX_ENABLE_RTTI True)
    
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
    can
    VERSION 0.0.1
    DESCRIPTION "Provider-agnostic CAN library"
    LANGUAGES CXX
)

if (CAN_DRIVER_RP2)
    pico_sdk_init()
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20) # "using enum" in core

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if (IS_TEST_ENV_QEMU STREQUAL "true")
    set(BUILD_SHARED_LIBS OFF)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

if (IS_TEST_ENV STREQUAL "true" OR IS_TEST_FUZZ_ENV STREQUAL "true")

    set(CMAKE_CTEST_ARGUMENTS "-L" "can")
    include(CTest)
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

# External libraries
add_subdirectory(lib/common/boost)
add_subdirectory(lib/common/moodycamel/concurrentqueue)
add_subdirectory(lib/common/fmt)
add_subdirectory(lib/common/plog)

if (CAN_DRIVER_OS_SOCKETCAN)
    add_subdirectory(lib/linux/socketcan/libsockcanpp)
endif()

add_subdirectory(can)


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
    EXCLUDE_FROM_ALL
)