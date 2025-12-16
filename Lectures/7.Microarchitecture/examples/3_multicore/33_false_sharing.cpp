#include <scope_timer.hpp>
#include <thread>

struct Shared{
    int x, y;
};

struct NonShared{
    alignas(std::hardware_destructive_interference_size) int x;
    alignas(std::hardware_destructive_interference_size) int y;
};

void process(volatile int& x){
    for(int i= 0;i < 100000000; ++i)
        ++x;
}

int main(){
    Shared s{};
    NonShared ns{};

    {
        scope_timer _{"With false-sharing"};
        std::jthread t{process, std::ref(s.x)};
        process(s.y);
    }

    {
        scope_timer _{"Without false-sharing"};
        std::jthread t{process, std::ref(ns.x)};
        process(ns.y);
    }
    std::cout <<"Results equal? " << std::boolalpha<< ((s.x==ns.x)&&(s.y == ns.y));
}