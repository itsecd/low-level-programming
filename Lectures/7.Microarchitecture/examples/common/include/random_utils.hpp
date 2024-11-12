#ifndef L7_RANDOM_UTILS_HPP
#define L7_RANDOM_UTILS_HPP
#include <random>
#include <algorithm>

template<typename Iter>
void fill_random(Iter begin, Iter end, int seed = 0, int min_value = -127, int max_value=127){
    auto e = std::default_random_engine(seed);
    auto gen = std::uniform_int_distribution<long>(min_value, max_value);
    auto gen_fn = [&e, &gen](){return gen(e);};
    std::generate(begin, end, gen_fn);
}



#endif //L7_RANDOM_UTILS_HPP
