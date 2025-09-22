#include <cstddef>
namespace NAMESPACE {
    float vec_mul(const float* a, const float* b, size_t size) {
        float result = 0;
        for (size_t i = 0; i < size; ++i)
            result += a[i] * b[i];
        return result;
    }
}
