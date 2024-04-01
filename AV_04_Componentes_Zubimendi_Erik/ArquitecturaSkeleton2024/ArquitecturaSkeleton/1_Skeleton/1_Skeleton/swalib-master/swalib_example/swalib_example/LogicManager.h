#pragma once

#include <vector>

class Entity;
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
	int GetBallsNum();
	Entity* GetBall(int _idx);
	Entity* GetBackgroundTile(int _idx, int _jdx);
	Timer* GetTimer();

private:
	static LogicManager* m_pLogicManager;

	/* Entities */
	std::vector<Entity*> m_Balls;
	std::vector<std::vector<Entity*>> m_Background;

	Timer* m_Timer;

	LogicManager();
	void LogicWorldSlot();
};