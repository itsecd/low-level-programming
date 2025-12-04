#include <stdio.h>

int global_var_in_data = 1;
int global_var_in_bss;

void foo() {
    printf("Address of foo: %p\n", foo);
}

int main() {
    volatile int local_var_on_stack = 0;

    printf("Address of global_var_in_data: %p\n", &global_var_in_data);
    printf("Address of global_var_in_bss: %p\n", &global_var_in_bss);
    printf("Address of local_var_on_stack: %p\n", &local_var_on_stack);
    foo();
    printf("Address of printf: %p\n", printf);
}