cmake_minimum_required(VERSION 3.20)
project(exploits C)

if(MSVC)
    message(FATAL_ERROR "Build with gcc. Use MinGW if on Windows")
endif()

set(CMAKE_C_STANDARD 99) # c99 is the last C standard with gets() included

#for Linux and MinGW
if(MINGW)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-stack-protector -fcf-protection=none -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=0") # add -m32 flag to build x86-32 executables
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-stack-protector -fcf-protection=none -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=0 -D__USE_MINGW_ANSI_STDIO -z execstack") #  execstack is supported on Linux, but not on Windows
endif()

add_executable(stack0 stack0.c)
add_executable(stack1 stack1.c)
add_executable(stack3 stack3.c)
add_executable(format0 format0.c)
add_executable(format1 format1.c)
add_executable(format3 format3.c)