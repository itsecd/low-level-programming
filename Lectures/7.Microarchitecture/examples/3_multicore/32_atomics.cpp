#include <scope_timer.hpp>
#include <atomic>
#include <thread>

volatile int x;
volatile int y;
std::atomic_int z;

void process_x(){
    for(int i = 0; i < 10000000;++i)
        ++x;
}

void process_y(){
    for(int i = 0; i < 10000000;++i)
        asm volatile(
           "lock add %0, 1":"+m"(y)::"memory"
        );
}

void process_z(){
    for(int i = 0; i < 10000000;++i)
        ++z;
}

void run(auto fn){
    std::jthread t{fn};
    fn();
}

int main(){
    {
        scope_timer _{"default"};
        run(process_x);
    }

    {
        scope_timer _{"LOCKed"};
        run(process_y);
    }

    {
        scope_timer _{"C++ atomic"};
        run(process_z);
    }

    std::cout << x << " " << y << " " << z;
}