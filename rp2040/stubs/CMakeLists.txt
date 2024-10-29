set(PROJECT can_rp2040_stubs)

project(
    ${PROJECT}
    VERSION ${CMAKE_PROJECT_VERSION}
    LANGUAGES C CXX ASM # pico projects must include all 3
)

add_library(${PROJECT} ${CMAKE_CURRENT_SOURCE_DIR}/null.c)

add_library(libcan::rp2040::stubs ALIAS ${PROJECT})

target_include_directories(${PROJECT} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT} PUBLIC
    pico_stdlib
    hardware_claim # common
    hardware_irq # host
    # stubbed | pico_platform # host, platform_defs.h
)