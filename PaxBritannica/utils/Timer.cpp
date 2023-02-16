//
//  Timer.cpp
//  PaxBritannica
//
//  Created by Laurine Xu on 2023/2/16.
//

#include "Timer.hpp"

void Timer::update() {
    std::chrono::duration<double> elapsed_time = std::chrono::steady_clock::now() - start_time;
    if (elapsed_time.count() >= 1.0) {
        // TODO
        start_time = std::chrono::steady_clock::now();
    }
}
