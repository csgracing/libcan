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



set(LINK_LIBS pico_stdlib)

if (IS_TEST_ENV STREQUAL "true")
    message("${PROJECT}: Adding test-only dependencies...")
    set(LINK_LIBS ${LINK_LIBS} libcan::rp2040::stubs)
else()
    message("${PROJECT}: Adding production-only dependencies...")
    set(LINK_LIBS ${LINK_LIBS} hardware_spi)
endif()

target_link_libraries(${PROJECT} ${LINK_LIBS})
