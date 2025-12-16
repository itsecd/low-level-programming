project(L10 CXX C)
if(MSVC)
    message(FATAL_ERROR "Build with MinGW")
endif ()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -masm=intel -fno-inline -fcf-protection=none")
add_executable(software_breakpoint software_breakpoint.cpp)


if(NOT MINGW)
    add_executable(sigtrap sigtrap.cpp)
endif ()
add_executable(trap_flag trap_flag.cpp)