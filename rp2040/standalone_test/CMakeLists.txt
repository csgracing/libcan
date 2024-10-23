set(PROJECT can_rp2040_standalone)

project(
    ${PROJECT}
    VERSION ${CMAKE_PROJECT_VERSION}
    LANGUAGES C CXX ASM # pico projects must include all 3
)

add_executable(${PROJECT})

add_executable(libcan::rp2040::standalone ALIAS ${PROJECT})

target_sources(${PROJECT}
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
)


target_include_directories(${PROJECT}
     PRIVATE
          # internal headers
          ${CMAKE_CURRENT_SOURCE_DIR}/src
     PUBLIC
          # exported headers
          ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT} PRIVATE libcan::core libcan::rp2040::core libcan::rp2040::mcp2515)

# Create extra files, such as .uf2
pico_add_extra_outputs(${PROJECT})