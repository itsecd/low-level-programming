#include "memory"
#include "scoped_timer.h"
#include <iostream>
// There is 'inline' keyword in C/C++, but there is no 'noinline'.
// Each compiler has its own way to mark a function noinline.
// A macros can be used to simplify things.
#ifdef _MSC_VER  //MSVC
#define noinline __declspec(noinline)
#else            // GCC/Clang
#define noinline __attribute__((noinline))
#endif


noinline void fill(volatile int* arr, size_t size, int value = 0){
    ScopedTimer s{};

    for(size_t i = 0; i < size; ++i)
        arr[i] = value;
}

constexpr size_t SIZE = 1024*1024*64; //256 MB, bigger than most CPU caches
int main(){
    auto array = new int[SIZE];
    fill(array, SIZE); //slower because of soft page faults
    fill(array, SIZE);
    fill(array, SIZE);
}