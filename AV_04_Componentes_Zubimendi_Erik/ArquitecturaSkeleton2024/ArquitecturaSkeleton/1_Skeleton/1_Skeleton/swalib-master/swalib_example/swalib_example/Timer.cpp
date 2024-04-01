#include "Timer.h"
#include <iostream>


Timer::Timer()
{}

void Timer::InitTimer()
{
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&previousTime);
}

bool Timer::InitSlotsToProcess()
{
	QueryPerformanceCounter(&currentTime);
	elapsedTime = (static_cast<double>(currentTime.QuadPart - previousTime.QuadPart)) / static_cast<double>(freq.QuadPart);

	previousTime = currentTime;

	if (elapsedTime <= 0)
	{
		return false;
	}

	accumulatedElapsedTime += elapsedTime;
	totalTime += elapsedTime;

	if (accumulatedElapsedTime > (1.0 / 15.0))
	{
		accumulatedElapsedTime = 1.0 / 15.0;
	}
	return true;
}

bool Timer::ProcessSlots(double _TickRate)
{
	return accumulatedElapsedTime >= _TickRate;
}

double Timer::GetFrames()
{
	return frames;
}

double Timer::GetTotalTime()
{
	return totalTime;
}

double Timer::GetTotalLogicTime()
{
	return totalLogicTime;
}

void Timer::UpdateTimer(double _TickRate)
{
	totalLogicTime += _TickRate;
	frames = accumulatedElapsedTime;
	accumulatedElapsedTime -= _TickRate;
}