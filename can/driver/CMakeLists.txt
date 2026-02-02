set(CAN_NAMESPACE_PREFIX "can::driver")
set(CAN_PROJECT_PREFIX "can_driver")

set(CMAKE_FOLDER "can/drivers")

add_subdirectory(base)
add_subdirectory(os)
add_subdirectory(rp2)

unset(CMAKE_FOLDER)