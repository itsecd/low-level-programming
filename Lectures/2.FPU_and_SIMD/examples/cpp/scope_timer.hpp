//
// Created by Alexey on 16.09.2024.
//

#ifndef REPO_SCOPE_TIMER_HPP
#define REPO_SCOPE_TIMER_HPP

#include <chrono>
#include <string_view>

struct scope_timer {
    using duration_t = std::chrono::duration<float,std::milli>;
    using clock = std::chrono::high_resolution_clock;

    const std::string scope_name;
    const clock::time_point start_time;

    explicit scope_timer(std::string_view scope_name = "");
    ~scope_timer();
};


#endif //REPO_SCOPE_TIMER_HPP
