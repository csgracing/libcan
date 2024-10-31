# GoogleTest section following
if (IS_TEST_ENV STREQUAL "true")

    set(PROJECT can_rp2040_mcp2515_test)

    project(
        ${PROJECT}
        VERSION ${CMAKE_PROJECT_VERSION}
        LANGUAGES C CXX ASM # pico projects must include all 3
    )

    enable_testing()

    add_executable(${PROJECT}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/provider_test.cpp
    )

    target_include_directories(${PROJECT}
        PRIVATE
            # internal headers
            ${CMAKE_CURRENT_SOURCE_DIR}/src/
    )

    target_link_libraries(${PROJECT} libcan::rp2040::mcp2515 gtest-tap-listener gmock-global::gmock-global GTest::gtest_main GTest::gmock_main)

    set_target_properties(${PROJECT} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test-bin)
    include(GoogleTest)
    gtest_discover_tests(${PROJECT})
endif()