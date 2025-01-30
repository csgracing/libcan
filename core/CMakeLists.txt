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
          ${CMAKE_CURRENT_LIST_DIR}/src/isotp/tl/parse.cpp
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