#ifdef _MSC_VER
#define EXTERN __declspec(dllimport)
#else
#define EXTERN extern
#endif


extern "C" {
    EXTERN void function();
    EXTERN void function2();
}

void call_external_functions()
{
    function();
    function2();
}

