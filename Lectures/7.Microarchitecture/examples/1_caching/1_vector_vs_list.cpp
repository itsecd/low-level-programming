#include <scope_timer.hpp>
#include <random>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

const size_t COLLECTIONS_COUNT = 5;
const size_t TOTAL_ITEMS = 1024*1024*16;

template<typename TCollection>
std::vector<TCollection> make_random(){
    std::vector<TCollection> result(COLLECTIONS_COUNT);
    for(size_t i = 0; i < TOTAL_ITEMS; ++i)
    {
        auto idx = rand() % result.size();
        result[idx].push_back(rand() % 10);
    }
    return result;
}

double sum(const auto collections){
    double result{};
    for(auto& collection: collections)
        for(auto value: collection)
            result += value;
    return result;
}

int main(){
    std::vector<std::vector<int>> vectors;
    std::vector<std::list<int>> lists;
    srand(1);
    {
        scope_timer _{"Vector fill"};
        vectors = make_random<std::vector<int>>();
    }

    srand(1);
    {
        scope_timer _{"List fill"};
        lists = make_random<std::list<int>>();
    }
    double r1, r2;
    {
        scope_timer _{"Vector sum"};
        r1 =sum(vectors);
    }

    {
        scope_timer _{"Lists sum"};
        r2 =sum(lists);
    }

    std::cout <<std::boolalpha << (r1 == r2);
}

