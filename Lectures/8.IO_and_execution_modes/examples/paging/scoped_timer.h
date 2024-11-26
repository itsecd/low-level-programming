//
// Created by Alexey on 11.11.2023.
//

#ifndef C_SCOPED_TIMER_H
#define C_SCOPED_TIMER_H
#include <chrono>

struct ScopedTimer {
    using duration_t  = std::chrono::duration<double, std::milli>;
    using clock = std::chrono::high_resolution_clock;

    const clock::time_point start_time;
    ScopedTimer();
    ~ScopedTimer();
};


#endif //C_SCOPED_TIMER_H
