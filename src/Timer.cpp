#include "Timer.hpp"

void Timer::startTime()
{
	mStartTime = system_clock::now();
}


float Timer::getTime()
{
	duration<float> elapsed_seconds = system_clock::now() - mStartTime;

	return elapsed_seconds.count();
}
