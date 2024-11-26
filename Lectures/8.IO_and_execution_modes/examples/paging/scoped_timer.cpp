//
// Created by Alexey on 11.11.2023.
//

#include "scoped_timer.h"
#include <iostream>
ScopedTimer::ScopedTimer(): start_time(clock::now()) {}

ScopedTimer::~ScopedTimer() {
    auto end_time = clock::now();
    duration_t time = end_time - start_time;
    std::cout << "Time: " << time.count() << " ms"<<std::endl;
}
