register_component_library(isotp CXX)


target_sources(${PROJECT}
    PRIVATE
          ${CMAKE_CURRENT_LIST_DIR}/src/error/code/code.cpp
          ${CMAKE_CURRENT_LIST_DIR}/src/error/code/category/isotp_code.cpp
          ${CMAKE_CURRENT_LIST_DIR}/src/error/common/category/isotp.cpp
          ${CMAKE_CURRENT_LIST_DIR}/src/error/common/category/libcan.cpp
          ${CMAKE_CURRENT_LIST_DIR}/src/error/condition/category/isotp_condition.cpp
          ${CMAKE_CURRENT_LIST_DIR}/src/link/directional_link.cpp
          ${CMAKE_CURRENT_LIST_DIR}/src/link/link.cpp
          ${CMAKE_CURRENT_LIST_DIR}/src/link/manager.cpp
          ${CMAKE_CURRENT_LIST_DIR}/src/tl/handler/consecutive_frame.cpp
          ${CMAKE_CURRENT_LIST_DIR}/src/tl/handler/first_frame.cpp
          ${CMAKE_CURRENT_LIST_DIR}/src/tl/handler/manager.cpp
          ${CMAKE_CURRENT_LIST_DIR}/src/tl/handler/single_frame.cpp
          ${CMAKE_CURRENT_LIST_DIR}/src/tl/pdu/base.cpp
          ${CMAKE_CURRENT_LIST_DIR}/src/tl/pdu/flow_control.cpp
)

target_include_directories(${PROJECT}
     PRIVATE
          # internal headers
          ${CMAKE_CURRENT_SOURCE_DIR}/src
     PUBLIC
          # exported headers
          ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT} PUBLIC can::protocol::can can::driver::base Boost::system fmt::fmt)

add_subdirectory(test)