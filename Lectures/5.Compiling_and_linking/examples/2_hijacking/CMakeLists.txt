cmake_minimum_required(VERSION 3.14)
project(hijacking CXX)

set (CMAKE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/all")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIRECTORY})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIRECTORY})

add_subdirectory(good)
add_subdirectory(bad)
add_subdirectory(exe)