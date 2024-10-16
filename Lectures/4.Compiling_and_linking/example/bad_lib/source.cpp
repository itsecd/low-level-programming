#include<cstdio>

#ifdef _MSC_VER
#include <windows.h>
#include <libloaderapi.h>
#define WIN_EXTERN __declspec(dllexport)
#else
#include <dlfcn.h>
#define WIN_EXTERN
#endif

typedef void(*function_ptr)();


static function_ptr get_function(const char* lib_path, const char* function_name){
#ifdef _MSC_VER
    auto lib = LoadLibraryA(lib_path);
    if(!lib) return nullptr;
    void* ptr = GetProcAddress(lib, function_name);
    return (function_ptr)ptr;
    #define GOOD_LIB_PATH "./good_lib_copy.dll"
#else
    void* module_ptr = dlopen(lib_path, RTLD_NOW);
    if(!module_ptr) return nullptr;
    void* ptr = dlsym(module_ptr, function_name);
    return (function_ptr)ptr;
#define GOOD_LIB_PATH "./good_lib_copy.so"
#endif
}

extern "C" {
    WIN_EXTERN void function() {
        puts("doing something bad >:> ");
    }

    WIN_EXTERN void function2(){
        puts("doing something bad again >:> ");
        auto ptr = get_function(GOOD_LIB_PATH, "function2");
        if(ptr)
            ptr();
    }
}