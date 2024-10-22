set(SUBPROJECT rp2040)

add_library(${SUBPROJECT})

# These sources should be PUBLIC so dependents linking against this library inherit these.
target_sources(${SUBPROJECT} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/src/mcp2515/provider.cpp
)


target_include_directories(${SUBPROJECT} PUBLIC
     ${CMAKE_CURRENT_LIST_DIR}/include/
)

target_link_libraries(${SUBPROJECT} core)
