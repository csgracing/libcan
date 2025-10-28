set(CAN_NAMESPACE_PREFIX "can::driver::os")
set(CAN_PROJECT_PREFIX "can_driver_os")

if (CAN_DRIVER_OS_SOCKETCAN)
    add_subdirectory(socketcan)
endif()