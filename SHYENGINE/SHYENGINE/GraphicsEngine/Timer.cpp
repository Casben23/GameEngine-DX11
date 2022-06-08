#include "GraphicsEngine.pch.h"
#include "Timer.h"
std::chrono::high_resolution_clock::time_point Timer::myTimeSinceLastUpdate;
std::chrono::high_resolution_clock::time_point Timer::myStartTime;
std::chrono::duration<double> Timer::myTotalTime;
std::chrono::duration<float> Timer::myDeltaTime;
Timer::Timer()
{
	myStartTime = std::chrono::high_resolution_clock::now();
	myDeltaTime = std::chrono::seconds(0);
	myTotalTime = std::chrono::seconds(0);
	myTimeSinceLastUpdate = std::chrono::high_resolution_clock::now();
}

void Timer::Update()
{
	std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
	myTotalTime = currentTime - myStartTime;
	myDeltaTime = currentTime - myTimeSinceLastUpdate;
	myTimeSinceLastUpdate = currentTime;
}

float Timer::GetDeltaTime()
{
	return myDeltaTime.count();
}

double Timer::GetTotalTime()
{
	return myTotalTime.count();
}
