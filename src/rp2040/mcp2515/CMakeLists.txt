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
set(LINK_LIBS Boost::preprocessor Boost::conversion pico_stdlib libcan::core libcan::rp2040::mcp2515::lib::mcp2515)

if (IS_TEST_ENV STREQUAL "true")
    message("${PROJECT}: Adding test-only dependencies...")
    set(LINK_LIBS ${LINK_LIBS} libcan::rp2040::stubs)
    message("${PROJECT}: Setting test env define...")
    target_compile_definitions(${PROJECT} PRIVATE IS_TEST_ENV=1)
else()
    message("${PROJECT}: No production-only dependencies.")
endif()

target_link_libraries(${PROJECT} PUBLIC ${LINK_LIBS})


include(pico-mcp2515.cmake)