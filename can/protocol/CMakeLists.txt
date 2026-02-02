set(CAN_NAMESPACE_PREFIX "can::protocol")
set(CAN_PROJECT_PREFIX "can_protocol")


set(CMAKE_FOLDER "can/protocol")

add_subdirectory(classic)
add_subdirectory(isotp)

unset(CMAKE_FOLDER)