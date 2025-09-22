#include <iostream>

#ifdef _MSC_VER
#include <xmmintrin.h>
#else
#define _GNU_SOURCE
#include <fenv.h>
#endif



void enable_exception(){

#ifdef _MSC_VER
    auto mxcsr = _mm_getcsr();
    mxcsr &= ~(1<<12); //сброс бита 12
    _mm_setcsr( mxcsr );
#else
    int e = FE_INEXACT;
    feenableexcept(e);
#endif


}

volatile float x = 2;
volatile float y = 3;

int main(){
    std::cout << x/y << std::endl;
    enable_exception();
    std::cout << x/y << std::endl; // дробь 2/3 не может быть точно представлена, возникает аппаратное исключение
}