register_component_library(classic CXX)


target_sources(${PROJECT}
    PRIVATE
          ${CMAKE_CURRENT_LIST_DIR}/src/frame/dlc.cpp
          ${CMAKE_CURRENT_LIST_DIR}/src/frame/frame.cpp
          ${CMAKE_CURRENT_LIST_DIR}/src/frame/util.cpp
)

target_include_directories(${PROJECT}
     PRIVATE
          # internal headers
          ${CMAKE_CURRENT_SOURCE_DIR}/src
     PUBLIC
          # exported headers
          ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# as the "main" subproject, set once here and have it propagate to dependents.
# set PLOG to local, so instances will not be shared across modules
# However make this definition an interface to add to dependent's compile defs(?)
target_compile_definitions(${PROJECT} INTERFACE PLOG_LOCAL)

add_subdirectory(test)