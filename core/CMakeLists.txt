set(SUBPROJECT core)

add_library(${SUBPROJECT} 
     ${CMAKE_CURRENT_LIST_DIR}/src/providers/base.cpp
)
target_include_directories(${SUBPROJECT} PUBLIC
     ${CMAKE_CURRENT_LIST_DIR}/include/
)