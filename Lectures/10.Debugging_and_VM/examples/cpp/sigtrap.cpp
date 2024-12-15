#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>





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

__attribute__((__noinline__))
void target_function(){
    puts("Target function called"); // <- INT3 will go somewhere there, breaking some instruction
    fflush(stdout);
}


void signal_handler(int signal, siginfo_t *si, void *context)
{
    puts("\t SIGTRAP caught");

    clear_breakpoint((void*)&target_function);
    puts("\t Original instruction restored");

    ((ucontext_t*)context)->uc_mcontext.gregs[REG_RIP] -= 1; // comment this line to break the program
    puts("\t RIP fixed to re-run original instruction");
}

void set_sigtrap_handler();

int main(){
    set_sigtrap_handler();

    target_function();
    set_breakpoint((void*)&target_function);
    target_function();
    target_function();
}

void set_sigtrap_handler(){
    struct sigaction sa{};
    sa.sa_sigaction = signal_handler,
            sa.sa_flags = SA_SIGINFO;
    if(sigaction(SIGTRAP, &sa, nullptr))
    {
        perror("sigaction() failed");
        exit(-1);
    }
}


