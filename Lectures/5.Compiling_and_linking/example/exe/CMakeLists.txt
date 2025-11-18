


add_executable(exe main.cpp
        call_external_functions.cpp)

target_link_libraries(exe PRIVATE good)
set_target_properties(exe PROPERTIES BUILD_RPATH_USE_ORIGIN TRUE)