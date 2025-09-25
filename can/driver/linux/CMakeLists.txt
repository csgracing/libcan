set(CAN_NAMESPACE_PREFIX "can::driver::linux")
set(CAN_PROJECT_PREFIX "can_driver_linux")

if (CAN_DRIVER_LINUX_SOCKETCAN)
    add_subdirectory(socketcan)
endif()