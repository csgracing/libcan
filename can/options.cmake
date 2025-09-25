
include(CMakeDependentOption)


function(can_driver_path_to_option_key path)
    string(REPLACE "/" "_" driver_name ${path}) # replace eg. "linux/socketcan with linux_socketcan"
    string(TOUPPER "CAN_DRIVER_${driver_name}" driver_option_key)
    return(PROPAGATE driver_name driver_option_key)
endfunction()

function(can_active_driver_list)
    # iterate over list
    foreach(entry IN LISTS driver_list)
        # check if entry is enabled
        can_driver_path_to_option_key(${entry})
        if(${driver_option_key})
            list(APPEND active_driver_list ${entry})
        endif()
    endforeach()
    return(PROPAGATE active_driver_list)
    #list(FILTER)
endfunction()

macro(can_add_driver_option path)
    can_driver_path_to_option_key(${path})
    message(TRACE "libcan: registering driver ${driver_name}")
    cmake_dependent_option(${driver_option_key} "Enable the ${driver_name} driver" ON "${ARGV1}" OFF)
    list(APPEND driver_list "${driver_name}")
endmacro()



# Options
option(CAN_USE_DRIVER "Use a driver to enable sending of CAN frames." OFF)
can_add_driver_option(rp2 "CAN_USE_DRIVER; NOT CAN_DRIVER_LINUX_SOCKETCAN")
can_add_driver_option(linux/socketcan "CAN_USE_DRIVER;NOT CAN_DRIVER_RP2")

# Informational logging
message(STATUS "libcan: version ${CAN_VERSION}")
message(STATUS "libcan: driver support: ${CAN_USE_DRIVER}")
message(STATUS "libcan: registered drivers: ${driver_list}")
can_active_driver_list()
message(STATUS "libcan: active drivers: ${active_driver_list}")