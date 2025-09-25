# GoogleTest section following
if (IS_TEST_FUZZ_ENV STREQUAL "true")

    register_component_test_executable(test_fuzz
        ${CMAKE_CURRENT_SOURCE_DIR}/src/protocol_frame_fuzz_test.cpp
    )

    target_link_libraries(${PROJECT} can::protocol::can fuzztest::fuzztest fuzztest::fuzztest_gtest_main)

    set_target_properties(${PROJECT} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test-bin)


    include(GoogleTest)
    gtest_discover_tests(${PROJECT})
endif()