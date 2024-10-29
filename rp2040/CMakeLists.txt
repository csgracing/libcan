set(namespace "can::rp2040")

include(subdir_exclude_plat.cmake)

if (IS_TEST_ENV STREQUAL "true")
    add_subdirectory(stubs)
endif()

if (TARGET hardware_spi OR IS_TEST_ENV STREQUAL "true")
    add_subdirectory_exclude_platforms(mcp2515)
else()
    message("Skipping rp2040::mcp2515 provider as hardware_spi is unavailable on this platform")
endif()