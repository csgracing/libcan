add_subdirectory(assert) # dependency of boost/conversion
add_subdirectory(config) # dependency of boost/conversion
add_subdirectory(conversion)
add_subdirectory(core) # dependency of boost/smart_ptr
add_subdirectory(preprocessor)
add_subdirectory(smart_ptr) # dependency of boost/conversion
add_subdirectory(static_assert) # dependency of boost/core
add_subdirectory(throw_exception) # dependency of boost/conversion

add_subdirectory(system)
add_subdirectory(variant2) # dependency of boost/system
add_subdirectory(mp11) # dependency of boost/variant2
add_subdirectory(winapi) # dependency of boost/system
add_subdirectory(predef) # dependency of boost/winapi