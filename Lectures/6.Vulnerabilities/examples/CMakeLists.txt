cmake_minimum_required(VERSION 3.20)
project(exploits C)

if(MSVC)
    message(FATAL_ERROR "Build with gcc. Use MinGW if on Windows")
endif()

set(CMAKE_C_STANDARD 99) # c99 is the last C standard where gets() is included in the standard library

#for Linux and MinGW
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-stack-protector -fcf-protection=none -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=0 -z execstack") # add -m32 flag to build x86-32 executables

add_executable(stack0 stack0.c)
add_executable(stack1 stack1.c)
add_executable(stack3 stack3.c)
add_executable(format0 format0.c)
add_executable(format1 format1.c)
add_executable(format3 format3.c)