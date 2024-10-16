#ifdef _MSC_VER
#define EXTERN __declspec(dllimport)
#else
#define EXTERN extern
#endif

extern "C" {
     EXTERN void function();
     EXTERN void function2();
}

int main(){
    function();
    function2();
}