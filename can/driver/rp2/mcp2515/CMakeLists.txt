register_component_library(mcp2515 C CXX ASM) # pico projects must include all 3 languages

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
set(LINK_LIBS Boost::preprocessor Boost::conversion pico_stdlib can::driver::base ${CAN_NAMESPACE_PREFIX}::mcp2515_lib)
 #libcan::core libcan::rp2040::mcp2515::lib::mcp2515)

if (IS_TEST_ENV STREQUAL "true")
    message("${PROJECT}: Adding test-only dependencies...")
    set(LINK_LIBS ${LINK_LIBS} can::driver::rp2::mcp2515::test_stubs)
    message("${PROJECT}: Setting test env define...")
    target_compile_definitions(${PROJECT} PRIVATE IS_TEST_ENV=1)
else()
    message("${PROJECT}: No production-only dependencies.")
endif()

target_link_libraries(${PROJECT} PUBLIC ${LINK_LIBS})




set(CMAKE_FOLDER_BAK ${CMAKE_FOLDER})

set(CMAKE_FOLDER "can/drivers/lib")
include(pico-mcp2515.cmake)

set(CMAKE_FOLDER "can/drivers/test")
add_subdirectory(test)


set(CMAKE_FOLDER ${CMAKE_FOLDER_BAK})