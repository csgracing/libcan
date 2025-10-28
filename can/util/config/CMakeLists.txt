register_component_library_interface(config CXX)

# <https://www.kdab.com/setting-defines-with-cmake/>
configure_file(config.h.in include/can/util/config/config.h)


target_include_directories(${PROJECT}
     INTERFACE
          # exported headers
          ${CMAKE_CURRENT_BINARY_DIR}/include # config.h.in output location
)