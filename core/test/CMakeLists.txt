# GoogleTest section following
if (IS_TEST_ENV STREQUAL "true")

    set(PROJECT can_core_test)

    project(
        ${PROJECT}
        VERSION ${CMAKE_PROJECT_VERSION}
        LANGUAGES C CXX ASM # pico projects must include all 3
    )

    enable_testing()

    add_executable(${PROJECT}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/protocol_frame_test.cpp
    )

    target_include_directories(${PROJECT}
        PRIVATE
            # internal headers
            ${CMAKE_CURRENT_SOURCE_DIR}/src/
    )

    target_link_libraries(${PROJECT} libcan::core gmock-global::gmock-global GTest::gtest_main GTest::gmock_main)

    set_target_properties(${PROJECT} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test-bin)
    include(GoogleTest)
    gtest_discover_tests(${PROJECT})

    setup_target_for_coverage_gcovr_xml(
        NAME ${PROJECT}_coverage
        EXECUTABLE ${PROJECT}
        BASE_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endif()

add_subdirectory(fuzz)