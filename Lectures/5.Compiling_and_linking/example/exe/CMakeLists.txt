add_executable(exe main.cpp)
set(CMAKE_SKIP_RPATH TRUE)
target_link_libraries(exe PRIVATE good_lib)