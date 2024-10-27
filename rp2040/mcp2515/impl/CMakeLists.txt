set(PROJECT can_rp2040_mcp2515_impl)

project(
    ${PROJECT}
    VERSION ${CMAKE_PROJECT_VERSION}
    LANGUAGES C CXX ASM # pico projects must include all 3
)

add_library(${PROJECT})

add_library(libcan::rp2040::mcp2515 ALIAS ${PROJECT})

target_sources(${PROJECT}
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/src/provider.cpp
)


target_include_directories(${PROJECT}
     PRIVATE
          # internal headers
          ${CMAKE_CURRENT_SOURCE_DIR}/src
     PUBLIC
          # exported headers
          ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# pico_stdlib for "hardware/gpio.h"
target_link_libraries(${PROJECT} PUBLIC Boost::preprocessor pico_stdlib libcan::core libcan::rp2040::mcp2515::lib::mcp2515)

include(pico-mcp2515.cmake)