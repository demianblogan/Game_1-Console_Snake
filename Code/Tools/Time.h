#pragma once
#include <chrono>

// class Time exists for calculating time between two frames (delta time).
// I call its method "DeltaTime" only once, in "main" function (file main.cpp).
class Time
{
public:
	static double DeltaTime();

private:
    static std::chrono::time_point<std::chrono::steady_clock> previousTime;
    static std::chrono::time_point<std::chrono::steady_clock> currentTime;
};