#pragma once
#include <chrono>
#include <Windows.h>

class Timer
{
public:
	Timer();
	Timer(const Timer& aTimer) = delete;
	Timer& operator=(const Timer& aTimer) = delete;
	static void Update();
	static float GetDeltaTime();
	static double GetTotalTime();

public:
	static std::chrono::high_resolution_clock::time_point myTimeSinceLastUpdate;
	static std::chrono::high_resolution_clock::time_point myStartTime;
	static std::chrono::duration<double> myTotalTime;
	static std::chrono::duration<float> myDeltaTime;
};


