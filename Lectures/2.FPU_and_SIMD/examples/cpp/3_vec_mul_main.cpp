#include <vector>
#include <iostream>
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

std::vector<float> get_vector(size_t size){
    std::vector<float> result;
    result.reserve(size);
    for(size_t i = 0; i < size; ++i)
        result.push_back(rand()%16);
    return result;
}

constexpr size_t N = 1'000'000;
int main(){
    srand(0);

    auto a= get_vector(N);
    auto b = get_vector(N);

    decltype(scalar::vec_mul)* functions[] = {
            scalar::vec_mul,
            sse::vec_mul,
            avx::vec_mul,
            intrinsics::vec_mul
    };

    const char* scope_names[] = {
            "scalar", "sse", "avx", "intrinsics"
    };


    for(int i  = 0; i < 4; ++i){
        float result;
        {
            scope_timer _{scope_names[i]};
            result = functions[i](a.data(), b.data(), a.size());
        }
        std::cout << "result:"<<result<<std::endl<<std::endl;
    }


}