#include <stdio.h>
#include <signal.h>

#ifdef __MINGW32__
#include "memoryapi.h"
#else
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>

#endif


void enable_writing(void* address){
    void* page_address = (void*)((unsigned long long )address & ((-1ll)<<12));
#ifdef __MINGW32__
    DWORD tmp;
    if(!VirtualProtect(page_address, 4096, PAGE_EXECUTE_READWRITE,&tmp))
    {
        perror("VirtualProtect failed");
        exit(-1);
    }
#else
    if(mprotect(page_address, 4096, PROT_WRITE|PROT_EXEC))
    {
        perror("mprotect failed");
        exit(-1);
    }
#endif
}

void disable_writing(void* address){
    void* page_address = (void*)((unsigned long long )address & ((-1ll)<<12));
#ifdef __MINGW32__
    DWORD tmp;
    if(!VirtualProtect(page_address, 4096, PAGE_EXECUTE_READ,&tmp))
    {
        perror("VirtualProtect failed");
        exit(-1);
    }
#else
    if(mprotect(page_address, 1, PROT_EXEC))
    {
        perror("mprotect failed");
        exit(-1);
    }
#endif
}

char old_value;
void set_breakpoint(void* address){
    enable_writing(address);
    old_value  = *(char*)address;
    *(char*)address = 0xcc;
    disable_writing(address);
}

void clear_breakpoint(void* address){
    enable_writing(address);
    *(char*)address = old_value;
    disable_writing(address);
}

extern "C" void print_message(){
    puts("Target function called");
    fflush(stdout);
}

__attribute__((naked))
void target_function(){
    asm volatile ("nop; \n\t"  // <-- will be replaced with INT3
                  "jmp print_message;\n\t");
}


int main(){
    target_function();
    set_breakpoint((void*)&target_function);
    target_function();
    clear_breakpoint((void*)&target_function);
    target_function();

}

