register_component_library(can CXX)


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

add_subdirectory(test)