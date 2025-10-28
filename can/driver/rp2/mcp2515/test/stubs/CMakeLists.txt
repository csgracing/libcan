if (IS_TEST_ENV STREQUAL "true")

    set(PROJECT can_driver_rp2_mcp2515_test_stubs)

    project(
        ${PROJECT}
        VERSION ${CMAKE_PROJECT_VERSION}
        LANGUAGES C CXX ASM # pico projects must include all 3
    )

    add_library(${PROJECT} ${CMAKE_CURRENT_SOURCE_DIR}/null.c)

    add_library(can::driver::rp2::mcp2515::test_stubs ALIAS ${PROJECT})

    target_include_directories(${PROJECT} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

    target_link_libraries(${PROJECT} PUBLIC pico_stdlib)

endif()