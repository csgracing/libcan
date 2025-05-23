set(namespace "can")
set(PROJECT can_core)

project(
    ${PROJECT}
    VERSION ${CMAKE_PROJECT_VERSION}
    LANGUAGES CXX
)

add_library(${PROJECT})

add_library(libcan::core ALIAS ${PROJECT})

# <https://www.kdab.com/setting-defines-with-cmake/>
configure_file(config.h.in include/core/configure/config.h)

target_sources(${PROJECT}
     PRIVATE
          ${CMAKE_CURRENT_LIST_DIR}/src/isotp/error/code/code.cpp
          ${CMAKE_CURRENT_LIST_DIR}/src/isotp/error/code/category/isotp_code.cpp
          ${CMAKE_CURRENT_LIST_DIR}/src/isotp/error/common/category/isotp.cpp
          ${CMAKE_CURRENT_LIST_DIR}/src/isotp/error/common/category/libcan.cpp
          ${CMAKE_CURRENT_LIST_DIR}/src/isotp/error/condition/category/isotp_condition.cpp
          ${CMAKE_CURRENT_LIST_DIR}/src/isotp/link/directional_link.cpp
          ${CMAKE_CURRENT_LIST_DIR}/src/isotp/link/link.cpp
          ${CMAKE_CURRENT_LIST_DIR}/src/isotp/link/manager.cpp
          ${CMAKE_CURRENT_LIST_DIR}/src/isotp/tl/handler/consecutive_frame.cpp
          ${CMAKE_CURRENT_LIST_DIR}/src/isotp/tl/handler/first_frame.cpp
          ${CMAKE_CURRENT_LIST_DIR}/src/isotp/tl/handler/manager.cpp
          ${CMAKE_CURRENT_LIST_DIR}/src/isotp/tl/handler/single_frame.cpp
          ${CMAKE_CURRENT_LIST_DIR}/src/isotp/tl/pdu/base.cpp
          ${CMAKE_CURRENT_LIST_DIR}/src/isotp/tl/pdu/flow_control.cpp
          ${CMAKE_CURRENT_LIST_DIR}/src/protocol/frame/dlc.cpp
          ${CMAKE_CURRENT_LIST_DIR}/src/protocol/frame/frame.cpp
          ${CMAKE_CURRENT_LIST_DIR}/src/protocol/frame/util.cpp
          ${CMAKE_CURRENT_LIST_DIR}/src/providers/base.cpp
          ${CMAKE_CURRENT_LIST_DIR}/src/logger.cpp
)

target_include_directories(${PROJECT}
     PRIVATE
          # internal headers
          ${CMAKE_CURRENT_SOURCE_DIR}/src
     PUBLIC
          # exported headers
          ${CMAKE_CURRENT_SOURCE_DIR}/include
          ${CMAKE_CURRENT_BINARY_DIR}/include # config.h.in output location
)

target_include_directories(${PROJECT} PUBLIC
     ${CMAKE_CURRENT_LIST_DIR}/include/
)

target_link_libraries(${PROJECT} PUBLIC concurrentqueue Boost::system fmt::fmt plog)

# set PLOG to local, so instances will not be shared across modules
# However make this definition an interface to add to dependent's compile defs(?)
target_compile_definitions(${PROJECT} INTERFACE PLOG_LOCAL)