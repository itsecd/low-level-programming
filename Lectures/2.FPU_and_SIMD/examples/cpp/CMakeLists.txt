project(L2 CXX)

set(CMAKE_CXX_STANDARD 20)



add_executable(1_denormals 1_denormals.cpp scope_timer.cpp)
add_executable(1_denormals_disabled 1_denormals.cpp scope_timer.cpp)
target_compile_definitions(1_denormals_disabled PRIVATE DISABLE_DENORMALS)

add_executable(2_fpu_exceptions 2_fpu_exceptions.cpp)


add_library(3_vec_mul_scalar 3_vec_mul.cpp)
add_library(3_vec_mul_sse 3_vec_mul.cpp)
add_library(3_vec_mul_avx 3_vec_mul.cpp)
add_library(3_vec_mul_intrinsics 3_vec_mul_intrinsics.cpp)

if(MSVC)
    set(FAST_MATH_FLAG /fp:fast)
    set(AVX_FLAG /arch:AVX2)
else()
    set(FAST_MATH_FLAG -ffast-math)
    set(AVX_FLAG -mavx2)
endif()

target_compile_options(3_vec_mul_sse PRIVATE ${FAST_MATH_FLAG} )
target_compile_options(3_vec_mul_avx PRIVATE ${FAST_MATH_FLAG} ${AVX_FLAG})
target_compile_options(3_vec_mul_intrinsics PRIVATE ${AVX_FLAG} )

target_compile_definitions(3_vec_mul_scalar PRIVATE NAMESPACE=scalar)
target_compile_definitions(3_vec_mul_sse PRIVATE NAMESPACE=sse)
target_compile_definitions(3_vec_mul_avx PRIVATE NAMESPACE=avx)

add_executable(3_vec_mul 3_vec_mul_main.cpp scope_timer.cpp)
target_link_libraries(3_vec_mul PRIVATE
        3_vec_mul_scalar 3_vec_mul_sse 3_vec_mul_avx 3_vec_mul_intrinsics )
