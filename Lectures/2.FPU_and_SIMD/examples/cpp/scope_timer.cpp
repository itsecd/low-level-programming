#include "scope_timer.hpp"
#include <iostream>

scope_timer::scope_timer(std::string_view scope_name): start_time(clock::now()), scope_name(scope_name) {}

scope_timer::~scope_timer() {
    duration_t time = clock::now() - start_time;
    if(scope_name.empty())
        std::cout << "Time: "<<time.count() << "ms"<<std::endl;
    else
        std::cout << scope_name << " time: "<<time.count() << "ms"<<std::endl;
}


