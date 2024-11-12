#ifndef REPO_SCOPE_TIMER_HPP
#define REPO_SCOPE_TIMER_HPP

#include <chrono>
#include <string_view>
#include <string>
#include <iostream>

template<typename resolution = std::milli>
struct scope_timer {
    using duration_t = std::chrono::duration<float,resolution>;
    using clock = std::chrono::high_resolution_clock;

    const std::string scope_name;
    const clock::time_point start_time;

    explicit scope_timer(std::string_view scope_name = ""): start_time(clock::now()), scope_name(scope_name) {};
    ~scope_timer(){
        duration_t time = clock::now() - start_time;
        if(scope_name.empty())
            std::cout << "Time: "<<time.count() << "ms"<<std::endl;
        else
            std::cout << scope_name << " time: "<<time<<std::endl;
    }

};


#endif //REPO_SCOPE_TIMER_HPP
