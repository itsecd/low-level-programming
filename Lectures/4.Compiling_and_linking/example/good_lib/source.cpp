#include<cstdio>

#ifdef _MSC_VER
#define WIN_EXTERN __declspec(dllexport)
#else
#define WIN_EXTERN
#endif

extern "C" {
    WIN_EXTERN void function() {
        puts("doing something good");
    }

    WIN_EXTERN void function2() {
        puts("doing something good again");
    }
}