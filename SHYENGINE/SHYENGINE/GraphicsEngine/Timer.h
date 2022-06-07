#pragma once
#include <chrono>
#include <Windows.h>
namespace CommonUtilities
{
	class Timer
	{
	public:
		Timer();
		Timer(const Timer& aTimer) = delete;
		Timer& operator=(const Timer& aTimer) = delete;
		void Update();
		float GetDeltaTime() const;
		double GetTotalTime() const;

	public:
		std::chrono::high_resolution_clock::time_point myTimeSinceLastUpdate;
		std::chrono::high_resolution_clock::time_point myStartTime;
		std::chrono::duration<float> myDeltaTime;
		std::chrono::duration<double> myTotalTime;
	};
}

