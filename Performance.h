#pragma once
#include <chrono>

class PerformanceTimer {
private:
    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point end_time;
    bool is_running;

public:
    PerformanceTimer();
    void start();
    void stop();
    double getElapsedTimeMs() const;
    double getElapsedTimeSec() const;
};
