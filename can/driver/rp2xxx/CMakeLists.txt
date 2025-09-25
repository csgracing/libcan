set(CAN_NAMESPACE_PREFIX "can::driver::rp2xxx")
set(CAN_PROJECT_PREFIX "can_driver_rp2xxx")

if (CAN_DRIVER_RP2)

    include(subdir_exclude_plat.cmake)

    if (TARGET hardware_spi OR IS_TEST_ENV STREQUAL "true")
        add_subdirectory_exclude_platforms(mcp2515)
    else()
        message("Skipping rp2040::mcp2515 provider as hardware_spi is unavailable on this platform")
    endif()
endif()