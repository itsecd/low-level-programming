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
constexpr bool USE_NONSPECULATIVE = 0;

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


const double delta = 0.001;
double process1(){           // 'values' is a static array, the execution time depends only on the True/False distribution
    double result = 0;
    for(auto b: values){
        if(b)
            result += delta;
        else
            result -= delta;
    }
    return result;
}

double process2(){
    double result = 0;
    for (auto b: values) {
        result += b * delta - (!b) * delta; // True=1, false = 0; no Jump instructions are generated -> no speculative execution
    }
    return result;
}


__attribute__((noinline)) double process(){
    scope_timer _{"Process time"};
    return USE_NONSPECULATIVE ? process2() : process1(); //USE_NONSPECULATIVE is constexpr, check will be optimized at the compile time
}

int main(){
    double result;

    std::cout << "P-0.5 fill"<<std::endl;
    fill_random(0.5);
    result = process();
    std::cout << "Result:" <<result << std::endl<< std::endl;


    std::cout << "P-0.75 fill"<<std::endl;
    fill_random(0.75);
    result = process();
    std::cout << "Result:" <<result << std::endl<< std::endl;


    std::cout << "P-0.9 fill"<<std::endl;
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