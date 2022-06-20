//
// Created by martin on 18.06.22 г..
//

#pragma once

#include<chrono>
#include<cstdint>

inline uint_fast64_t CurrentNanoTime(){
    return std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
}
