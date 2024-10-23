set(PROJECT can_rp2040_mcp2515_lib_mcp2515)

set(MCP2515_LIB_DIR ${CMAKE_CURRENT_LIST_DIR}/../lib/pico-mcp2515)

project(
    ${PROJECT}
    LANGUAGES C CXX ASM # pico projects must include all 3
)

add_library(${PROJECT})

add_library(libcan::rp2040::mcp2515::lib::mcp2515 ALIAS ${PROJECT})

target_sources(${PROJECT}
    PRIVATE
    ${MCP2515_LIB_DIR}/include/mcp2515/mcp2515.cpp
)

target_include_directories(${PROJECT}
    PUBLIC
    ${MCP2515_LIB_DIR}/include
)

target_link_libraries(${PROJECT} pico_stdlib hardware_spi)