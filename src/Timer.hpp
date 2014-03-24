#pragma once
#include <chrono>

using namespace std::chrono;

struct Timer
{
	time_point<system_clock> mStartTime;

	Timer() : mStartTime(system_clock::duration::zero()) {};
	void startTime();
	float getTime();

};

