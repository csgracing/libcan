register_component_library(base CXX)


target_sources(${PROJECT}
    PRIVATE
          ${CMAKE_CURRENT_LIST_DIR}/src/base.cpp
)

target_include_directories(${PROJECT}
     PRIVATE
          # internal headers
          ${CMAKE_CURRENT_SOURCE_DIR}/src
     PUBLIC
          # exported headers
          ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT} PUBLIC can::protocol::classic can::util::log concurrentqueue)