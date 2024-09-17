#include <immintrin.h>


namespace intrinsics {
    float vec_mul(const float* a, const float* b, size_t size) {
        auto remainder = size % 8;

        __m256 r;
        r = _mm256_xor_ps(r, r); // set to 0

        for (size_t i = 0; i < size; i += 8) {
            __m256 tmp = _mm256_loadu_ps((const float *) (&a[i]));
            tmp = _mm256_mul_ps(tmp, *(__m256 *) (&b[i]));
            r = _mm256_add_ps(r, tmp);
        }

        r = _mm256_hadd_ps(r, r);
        r = _mm256_hadd_ps(r, r);
        __m128 lo = _mm256_extractf128_ps(r, 0);
        __m128 hi = _mm256_extractf128_ps(r, 1);
        hi = _mm_add_ps(hi, lo);

        auto tmp = _mm_extract_ps(hi, 0);

        float result = *(float *) &tmp;

        for (int i = 0; i < remainder; ++i)
            result += a[i];

        return result;
    }
}