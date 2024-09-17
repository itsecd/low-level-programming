#include <span>
#include <vector>
#include <iostream>
#include <cmath>
#include "scope_timer.hpp"

#ifdef DISABLE_DENORMALS
#ifdef _MSC_VER
#include <xmmintrin.h>
#endif
void enable_ftz_daz(){
#ifdef _MSC_VER
    auto mxcsr = _mm_getcsr();        /*read the old MXCSR setting  */    \
    mxcsr |= 0x8040;  /* set DAZ and FZ bits        */    \
    _mm_setcsr( mxcsr );             /* write the new MXCSR setting to the MXCSR */
#else
    asm volatile (
            ".intel_syntax noprefix;\n"
            "sub rsp, 8;\n"
            "stmxcsr [rsp];\n"
            "or word ptr[rsp],0x8040;\n"
            "ldmxcsr [rsp];\n"
            "add rsp, 8;\n"
            ".att_syntax;\n"
            :
            :
            : "memory"
            );
#endif
}
#endif




void fill(std::span<float> f, float start_value, float a){
    float result = start_value;
    for(auto& x: f)
        x = result*=a;
}

// volatile is used to prevent optimizations
volatile size_t VECTOR_SIZE = 32*1024*1024;
volatile float MULTIPLIER1 = 1.00001;
volatile float MULTIPLIER2 = 0.99999;


int main(){
    auto v = std::vector<float>(VECTOR_SIZE, 0);

    {
        scope_timer _{"Without denormals"};
        fill(v, 1.0f, MULTIPLIER1);
    }
    std::cout << "Last element of v:" << v.back()<< std::endl<< std::endl;

#ifdef DISABLE_DENORMALS
    enable_ftz_daz();
#endif

    {
        scope_timer _{"With denormals"};
        fill(v, 1.0f, MULTIPLIER2);
    }
    std::cout << "Last element of v:" << v.back()<< std::endl;

    if (v.back() != 0)
    {
        size_t i = 0;
        for(auto x: v){
            if(std::fpclassify(x) == FP_SUBNORMAL)
                break;
            ++i;
        }
        std::cout << "Last normalized number index:" << i;
    }

}