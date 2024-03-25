#include "LogicManager.h"
#include "../../common/stdafx.h"
#include "../../common/core.h"
#include "../../common/sys.h"
#include "Ball.h"
#include "Timer.h"

LogicManager* LogicManager::m_pLogicManager = nullptr;

const float MAX_BALL_SPEED = 8.f * 60.f;
const int NUM_BALLS = 10;

LogicManager::LogicManager() {}

LogicManager* LogicManager::Get()
{
	if (m_pLogicManager == nullptr)
	{
		m_pLogicManager = new LogicManager();
	}
	return m_pLogicManager;
}

void LogicManager::InitGame()
{
	
	for (int i = 0; i < NUM_BALLS; ++i)
	{
		m_Balls.push_back(new Ball(vec2(CORE_FRand(0.0, SCR_WIDTH), CORE_FRand(0.0, SCR_HEIGHT)),
			vec2(CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED), CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED)),
			16.f));
	}
	m_Timer = new Timer();
	m_Timer->InitTimer();
}

void LogicManager::LogicSlot()
{
	bool bHasToProcess = m_Timer->InitSlotsToProcess();
	while (bHasToProcess && m_Timer->ProcessSlots(g_TickRate))
	{
		LogicWorldSlot();
		m_Timer->UpdateTimer(g_TickRate);
	}
}

void LogicManager::LogicWorldSlot()
{
	for (Ball* ball : m_Balls)
	{
		ball->Slot(g_TickRate);
	}
}

void LogicManager::ShutdownGame()
{
	delete m_Timer;
	m_Timer = nullptr;
	for (Ball* ball : m_Balls)
	{
		delete ball;
		ball = nullptr;
	}
}

int LogicManager::GetBallsSize()
{
	return m_Balls.size();
}

Ball* LogicManager::GetBall(int _idx)
{
	return m_Balls[_idx];
}

Timer* LogicManager::GetTimer()
{
	return m_Timer;
}