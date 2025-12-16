//
// Created by Alexey on 11.11.2023.
//

#include <array>
#include <random>
#include <algorithm>
#include <execution>
#include <iostream>
#include <scope_timer.hpp>


constexpr size_t SIZE = 1024*1024*16; //16 MB
#ifdef NOSPEC
constexpr bool DISABLE_SPECULATION = true;
#else
constexpr bool DISABLE_SPECULATION = false;
#endif

// this array resides in the BSS section
// no memory reallocation is performed at the runtime
std::array<char, SIZE> values;


__attribute__((noinline)) void fill_random(double p){
    std::minstd_rand0 e;
    std::bernoulli_distribution d{p}; // p is the probability of True, (1-p) is the probability of False
    auto gen = [&](){return d(e);};
    std::generate_n(std::execution::par_unseq, values.begin(), values.size(), gen);
}


__attribute__((noinline)) void fill_alternating(){ //1010101010...
    auto tmp = false;
    for(auto& b: values)
    {
        b = tmp;
        tmp = !tmp;
    }
}


__attribute__((noinline)) void fill_square(size_t template_len){ // for size = 6 -> 000111000111000111...
    auto half = template_len / 2;
    size_t tmp = 0;
    for(auto & b: values){
        b = tmp++ >= half;
        tmp %= template_len;
    }
}

__attribute__((noinline)) void fill_repetitive(){ // produces complex repetitive pattern
    // LCG with m=17 (the last template parameter) generates the sequence with max period = 17
    //
    auto engine = std::linear_congruential_engine<size_t, 8, 11, 17>(0);

    for(auto & b: values){
        b = engine() & 1;
    }
}

constexpr double DELTA = 0.001;

__attribute__((noinline)) double process(){
    scope_timer _{"Process"};
    double result = 0;
    for(auto b: values){
        if(b)
            result += DELTA;
        else
            result -= DELTA;

        if constexpr  (DISABLE_SPECULATION)
            asm("lfence\n\t"); // LFENCE waits for all previous operations to be retired and disables reordering around itself
    }
    return result;
}

int main(){
    double result;

    std::cout << "P{1}=0.5 fill"<<std::endl;
    fill_random(0.5);
    result = process();
    std::cout << "Result:" <<result << std::endl<< std::endl;


    std::cout << "P{1}=0.75 fill"<<std::endl;
    fill_random(0.75);
    result = process();
    std::cout << "Result:" <<result << std::endl<< std::endl;


    std::cout << "P{1}=0.9 fill"<<std::endl;
    fill_random(0.9);
    result = process();
    std::cout << "Result:" <<result << std::endl<< std::endl;


    std::cout << "Alternating fill"<<std::endl;
    fill_alternating();
    result = process();
    std::cout << "Result:" <<result << std::endl<< std::endl;

    std::cout << "00110011 fill"<<std::endl;
    fill_square(4);
    result = process();
    std::cout << "Result:" <<result << std::endl<< std::endl;

    std::cout << "00001111 fill"<<std::endl;
    fill_square(8);
    result = process();
    std::cout << "Result:" <<result << std::endl;


    std::cout << std::endl<< "Repetitive template fill"<<std::endl;
    fill_repetitive();
    result = process();
    std::cout << "Result:" <<result << std::endl;

}