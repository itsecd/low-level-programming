#include <vector>
#include <iostream>
#include <iomanip>
#include "scope_timer.hpp"

namespace scalar {
    extern float vec_mul(const float* a, const float* b, size_t size);
}

namespace sse {
    extern float vec_mul(const float* a, const float* b, size_t size);
}

namespace avx {
    extern float vec_mul(const float* a, const float* b, size_t size);
}

namespace intrinsics {
    extern float vec_mul(const float* a, const float* b, size_t size);
}

std::vector<float> make_vector(size_t size){
    std::vector<float> result;
    result.reserve(size);
    for(size_t i = 0; i < size; ++i)
        result.push_back(rand()%16);
    return result;
}



using vec_mul_function_ptr = decltype(scalar::vec_mul)*;
// same as
// using vec_mul_function_ptr = float(*)(const float* a, const float* b, size_t size);

constexpr size_t N = 1'000'000;
int main(){
    srand(0);

    auto a= make_vector(N);
    auto b = make_vector(N);

    vec_mul_function_ptr functions[] = {
            scalar::vec_mul,
            sse::vec_mul,
            avx::vec_mul,
            intrinsics::vec_mul
    };

    const char* scope_names[] = {
            "scalar", "sse", "avx", "intrinsics"
    };

    for(int i  = 0; i < 4; ++i){
        std::cout <<std::setprecision(3); // to print the execution time with 4 numbers after .
        float result;
        {
            scope_timer _{scope_names[i]};
            result = functions[i](a.data(), b.data(), a.size());
        }
        std::cout <<std::setprecision(8); // to print the result with 8 numbers after .
        std::cout << "result:"<< std::setprecision(8)<<result<<std::endl<<std::endl;
    }


}