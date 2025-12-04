cmake_minimum_required(VERSION 3.20)
project(exploits C)

include(CheckPIESupported)
check_pie_supported()

if(MSVC)
    message(FATAL_ERROR "Build with gcc. Use MinGW if on Windows")
endif()

set(CMAKE_C_STANDARD 99) # c99 is the last C standard with gets() included
set(CMAKE_POSITION_INDEPENDENT_CODE FALSE)

#for Linux and MinGW
if(MINGW)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-stack-protector -fcf-protection=none -U_FORTIFY_SOURCE -D__USE_MINGW_ANSI_STDIO -D_FORTIFY_SOURCE=0") # add -m32 flag to build x86-32 executables
    add_link_options(/DYNAMICBASE:NO)
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-stack-protector -fcf-protection=none -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=0 -z execstack") #  execstack is supported on Linux, but not on Windows
endif()

add_executable(stack0 stack0.c)
add_executable(stack1 stack1.c)
add_executable(stack3 stack3.c)
add_executable(format0 format0.c)
add_executable(format1 format1.c)
add_executable(format3 format3.c)
add_executable(print_addresses_PIE print_addresses.c)
add_executable(print_addresses_noPIE print_addresses.c)

set_target_properties(print_addresses_PIE PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
if(MINGW)
    target_link_options(print_addresses_PIE PRIVATE /DYNAMICBASE)
endif ()

