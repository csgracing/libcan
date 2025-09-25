include(components.cmake)

set_property(DIRECTORY PROPERTY LABELS "can") # label all tests in can/ (this dir) so we can run only those

add_subdirectory(driver)
add_subdirectory(protocol)
add_subdirectory(util)