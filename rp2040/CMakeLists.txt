set(namespace "can::rp2040")

include(subdir_exclude_plat.cmake)

if (TARGET hardware_spi)
    add_subdirectory_exclude_platforms(mcp2515)
else()
    message("Skipping rp2040::mcp2515 provider as hardware_spi is unavailable on this platform")
endif()