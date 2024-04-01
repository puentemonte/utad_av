#include "LogicManager.h"
#include "../../common/stdafx.h"
#include "../../common/core.h"
#include "../../common/sys.h"
#include "Entity.h"
#include "Component.h"
#include "MovementComponent.h"
#include "CollisionComponent.h"
#include "RenderComponent.h"
#include "Timer.h"
#include "RenderManager.h"

LogicManager* LogicManager::m_pLogicManager = nullptr;

const float MAX_BALL_SPEED = 8.f * 60.f;
const int NUM_BALLS = 10;
const float BALL_RADIUS = 16.f;

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
	RenderManager* renderManager = RenderManager::Get();

	// Create the ball entities
	for (int i = 0; i < NUM_BALLS; ++i)
	{
		Entity* newBallEntity = new Entity();

		vec2 vPos = vec2(CORE_FRand(0.0, SCR_WIDTH), CORE_FRand(0.0, SCR_HEIGHT));
		vec2 vVel = vec2(CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED), CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED));

		MovementComponent* movementComponent = new MovementComponent();
		movementComponent->Init(newBallEntity, vPos, vVel);

		RenderComponent* renderComponent = new RenderComponent();
		renderComponent->Init(newBallEntity, vPos, BALL_RADIUS * 2);
		renderComponent->LoadTexture(renderManager->m_BallTexture);

		CollisionComponent* collisionComponent = new CollisionComponent();
		collisionComponent->Init(newBallEntity, vPos, vVel, BALL_RADIUS);

		newBallEntity->AddComponent(movementComponent);
		newBallEntity->AddComponent(renderComponent);
		newBallEntity->AddComponent(collisionComponent);

		m_Balls.push_back(newBallEntity);
	}

	for (int i = 0; i <= SCR_WIDTH / 128; i++)
	{
		std::vector<Entity*> aux;

		for (int j = 0; j <= SCR_HEIGHT / 128; j++)
		{
			Entity* newTile = new Entity();

			vec2 vPos = vec2(i * 128.f + 64.f, j * 128.f + 64.f);

			RenderComponent* renderComponet = new RenderComponent();
			renderComponet->Init(newTile, vPos, 128.f);
			renderComponet->LoadTexture(renderManager->m_BackgroundTexture);

			newTile->AddComponent(renderComponet);

			aux.push_back(newTile);
		}
		m_Background.push_back(aux);
	}

	m_Timer = new Timer();
	m_Timer->InitTimer();
}

void LogicManager::LogicSlot()
{
	m_Timer->InitSlotsToProcess();
	while (m_Timer->ProcessSlots(g_TickRate))
	{
		LogicWorldSlot();
		m_Timer->UpdateTimer(g_TickRate);
	}
}

void LogicManager::LogicWorldSlot()
{
	for (Entity* ball : m_Balls)
	{
		ball->Slot(g_TickRate);
	}
}

void LogicManager::ShutdownGame()
{
	delete m_Timer;
	m_Timer = nullptr;

	for (Entity* ball : m_Balls)
	{
		delete ball;
		ball = nullptr;
	}

	for (std::vector<Entity*>& tileRow : m_Background)
	{
		for (Entity* tile : tileRow)
		{
			delete tile;
			tile = nullptr;
		}
	}
}

int LogicManager::GetBallsNum()
{
	return m_Balls.size();
}

Entity* LogicManager::GetBall(int _idx)
{
	return m_Balls[_idx];
}

Entity* LogicManager::GetBackgroundTile(int _idx, int _jdx)
{
	return m_Background[_idx][_jdx];
}

Timer* LogicManager::GetTimer()
{
	return m_Timer;
}