#include "Time.h"

#include <ctime>

std::chrono::time_point<std::chrono::steady_clock> Time::previousTime = std::chrono::steady_clock::now();
std::chrono::time_point<std::chrono::steady_clock> Time::currentTime = std::chrono::steady_clock::now();

double Time::DeltaTime()
{
    previousTime = currentTime;
    currentTime = std::chrono::steady_clock::now();

    std::chrono::duration<double> elapsed_seconds = currentTime - previousTime;

    return elapsed_seconds.count();
}