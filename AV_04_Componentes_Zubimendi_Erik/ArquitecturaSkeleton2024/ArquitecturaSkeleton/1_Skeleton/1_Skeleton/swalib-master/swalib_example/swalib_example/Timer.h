#pragma once
#include "windows.h"

class Timer
{
public:
	Timer();
	void InitTimer();
	bool InitSlotsToProcess();
	bool ProcessSlots(double _TickRate);
	double GetFrames();
	double GetTotalTime();
	double GetTotalLogicTime();
	void UpdateTimer(double _TickRate);

private:
	LARGE_INTEGER previousTime, currentTime, freq;
	double logicTime = 0, elapsedTime = 0, accumulatedElapsedTime = 0;
	//---------------------------------------------------
	// Needed for Render
	double frames = 0, totalTime = 0, totalLogicTime = 0;
};