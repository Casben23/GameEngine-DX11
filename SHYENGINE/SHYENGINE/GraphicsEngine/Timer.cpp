#include "GraphicsEngine.pch.h"
#include "Timer.h"
CommonUtilities::Timer::Timer()
{
	myStartTime = std::chrono::high_resolution_clock::now();
	myDeltaTime = std::chrono::seconds(0);
	myTotalTime = std::chrono::seconds(0);
	myTimeSinceLastUpdate = std::chrono::high_resolution_clock::now();
}

void CommonUtilities::Timer::Update()
{
	std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
	myTotalTime = currentTime - myStartTime;
	myDeltaTime = currentTime - myTimeSinceLastUpdate;
	myTimeSinceLastUpdate = currentTime;
}

float CommonUtilities::Timer::GetDeltaTime() const
{
	return myDeltaTime.count();
}

double CommonUtilities::Timer::GetTotalTime() const
{
	return myTotalTime.count();
}
