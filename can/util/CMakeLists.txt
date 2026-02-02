set(CAN_NAMESPACE_PREFIX "can::util")
set(CAN_PROJECT_PREFIX "can_util")


set(CMAKE_FOLDER "can/util")

add_subdirectory(config)
add_subdirectory(log)

unset(CMAKE_FOLDER)