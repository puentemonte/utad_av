#pragma once

#include <vector>
class Ball;
class Timer;

// Fixed tick.
const double g_TickRate = 1.f / 60.f;

class LogicManager
{
public:
	static LogicManager* Get();
	void InitGame();
	void LogicSlot();
	void ShutdownGame();
	int GetBallsSize();
	Ball* GetBall(int _idx);
	Timer* GetTimer();

private:
	static LogicManager* m_pLogicManager;
	std::vector<Ball*> m_Balls;
	Timer* m_Timer;

	LogicManager();
	void LogicWorldSlot();
};