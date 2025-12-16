project(L7.uarch)

find_package(TBB)


add_executable(21_superscalar 21_superscalar.cpp)
add_executable(22_false_dependency 22_false_dependency.cpp)
add_executable(23_speculative_execution 23_speculative_execution.cpp)
add_executable(23_speculative_execution_nospec 23_speculative_execution.cpp)
target_compile_definitions(23_speculative_execution_nospec PUBLIC  NOSPEC=1)

if(TBB_FOUND)
    target_link_libraries(23_speculative_execution_nospec tbb)
    target_link_libraries(23_speculative_execution tbb)
endif ()