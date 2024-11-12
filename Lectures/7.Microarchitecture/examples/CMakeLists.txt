project(L7 CXX)

if(MSVC)
    message(FATAL_ERROR "Build with gcc. Use MinGW if on Windows")
endif()


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -masm=intel")
add_subdirectory(common)
link_libraries(common)
add_subdirectory(1_caching)
add_subdirectory(2_uarch)
add_subdirectory(3_multicore)