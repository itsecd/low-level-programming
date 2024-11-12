#include <iostream>
#include <thread>

/*
 *  Программа всегда будет выводить 0 (нет ошибок) на х86,
 *  но может вывести не-0 на ARM из-за менее строгой модели памяти.
 *
 * */

const size_t VALUES_COUNT = 100000000;

size_t errors_count = 0;

using value_t = volatile long long;
using flag_t = volatile bool;


alignas(std::hardware_destructive_interference_size)
flag_t ready;

alignas(std::hardware_destructive_interference_size)
value_t value;

void consumer_fn(){
    size_t count = 0;
    long long old_value = 0;
    while (count < VALUES_COUNT){
        if(ready){
            auto new_value = value;
            ready = false;
            if(new_value != old_value +1)
                ++errors_count;
            old_value = new_value;
            ++count;
        }
    }
}

void producer_fn(){
    size_t count = 0;
    while (count < VALUES_COUNT){
        if(!ready){
            ++value;
            ready = true;
            ++count;
        }
    }
}

int main(){
    {
        std::jthread t(consumer_fn);
        producer_fn();
    }
    std::cout << errors_count << std::endl;
}

