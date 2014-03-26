#include "Timer.hpp"

void Timer::startTime()
{
	mStartTime = steady_clock::now();
}


float Timer::getDeltaTime()
{
	duration<float> elapsed_seconds = steady_clock::now() - mStartTime;
	mStartTime = steady_clock::now();

	
	return (elapsed_seconds.count());
}

void Timer::reset()
{
	mStartTime = steady_clock::now();
}
