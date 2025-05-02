set(namespace "can")
set(PROJECT can_core)

project(
    ${PROJECT}
    VERSION ${CMAKE_PROJECT_VERSION}
    LANGUAGES CXX
)

add_library(${PROJECT})

add_library(libcan::core ALIAS ${PROJECT})


target_sources(${PROJECT}
     PRIVATE
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
)

target_include_directories(${PROJECT}
     PRIVATE
          # internal headers
          ${CMAKE_CURRENT_SOURCE_DIR}/src
     PUBLIC
          # exported headers
          ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_include_directories(${PROJECT} PUBLIC
     ${CMAKE_CURRENT_LIST_DIR}/include/
)

target_link_libraries(${PROJECT} PUBLIC concurrentqueue)
