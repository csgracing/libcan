# GoogleTest section following
if (IS_TEST_ENV STREQUAL "true")

    register_component_test_executable(test_unit
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/provider_test.cpp
    )

    target_link_libraries(${PROJECT} can::driver::rp2::mcp2515 gmock-global::gmock-global GTest::gtest_main GTest::gmock_main)

    set_target_properties(${PROJECT} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test-bin)
    include(GoogleTest)
    gtest_discover_tests(${PROJECT})

    setup_target_for_coverage_gcovr_xml(
        NAME ${PROJECT}_coverage
        EXECUTABLE ${PROJECT}
        BASE_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endif()