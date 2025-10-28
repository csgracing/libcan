register_component_library(mcp2515_lib C CXX ASM) # pico projects must include all 3 languages


set(MCP2515_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../../lib/rp2040/pico-mcp2515)

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
    set(LINK_LIBS ${LINK_LIBS} can::driver::rp2::mcp2515::test_stubs)
else()
    message("${PROJECT}: Adding production-only dependencies...")
    set(LINK_LIBS ${LINK_LIBS} hardware_spi)
endif()

target_link_libraries(${PROJECT} ${LINK_LIBS})
