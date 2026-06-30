#include "Performance.h"

PerformanceTimer::PerformanceTimer() : is_running(false) {}

void PerformanceTimer::start() {
    start_time = std::chrono::high_resolution_clock::now();
    is_running = true;
}

void PerformanceTimer::stop() {
    if (is_running) {
        end_time = std::chrono::high_resolution_clock::now();
        is_running = false;
    }
}

double PerformanceTimer::getElapsedTimeMs() const {
    auto end = is_running ? std::chrono::high_resolution_clock::now() : end_time;
    std::chrono::duration<double, std::milli> elapsed = end - start_time;
    return elapsed.count();
}

double PerformanceTimer::getElapsedTimeSec() const {
    return getElapsedTimeMs() / 1000.0;
}
