project(gtest-tap-listener VERSION 0.7 LANGUAGES CXX)

add_library(gtest-tap-listener INTERFACE)

target_include_directories(gtest-tap-listener INTERFACE lib/google/gtest-tap-listener/src)
