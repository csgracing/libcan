
macro(register_component_project name)
    set(PROJECT ${CAN_PROJECT_PREFIX}_${name})
    set(NAMESPACE ${CAN_NAMESPACE_PREFIX}::${name})

    
    # remove ${name} from argv
    set(languages ${ARGV})
    list(REMOVE_AT languages 0)

    project(
        ${PROJECT}
        VERSION ${CMAKE_PROJECT_VERSION}
        LANGUAGES ${languages}
    )
endmacro()

macro(register_component_library name)
    register_component_project(${ARGV})
    
    add_library(${PROJECT})
    
    add_library(${NAMESPACE} ALIAS ${PROJECT})
endmacro()

macro(register_component_library_interface name)
    register_component_project(${ARGV})
    
    add_library(${PROJECT} INTERFACE)
    
    add_library(${NAMESPACE} ALIAS ${PROJECT})
endmacro()


macro(register_component_test_executable name)
    register_component_project(${ARGV0} CXX)

    
    enable_testing()

    # remove ${name} from argv
    set(sources ${ARGV})
    list(REMOVE_AT sources 0)

    add_executable(${PROJECT} ${sources})
    add_executable(${NAMESPACE} ALIAS ${PROJECT})

    target_include_directories(${PROJECT}
        PRIVATE
            # internal headers
            ${CMAKE_CURRENT_SOURCE_DIR}/src/
    )

endmacro()