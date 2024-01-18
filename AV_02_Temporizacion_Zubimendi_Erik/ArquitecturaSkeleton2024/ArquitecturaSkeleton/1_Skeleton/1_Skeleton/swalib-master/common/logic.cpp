#include "logic.h"
#include "render.h"
#include "core.h"
#include "sys.h"

Ball balls[NUM_BALLS]; // Array of balls.

extern GLuint texbkg;
extern GLuint texsmallball;

LARGE_INTEGER previousTime, currentTime, freq;
double totalTime = 0, logicTime = 0, elapsedTime = 0, accumulatedElapsedTime = 0, currentFrames, currentLogicTime = 0;

void InitGame()
{
	// Init game state.
	for (int i = 0; i < NUM_BALLS; i++) {
		balls[i].pos = vec2(CORE_FRand(0.0, SCR_WIDTH), CORE_FRand(0.0, SCR_HEIGHT));
		balls[i].vel = vec2(CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED) * TICK_RATE, CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED) * TICK_RATE);
		balls[i].radius = 16.f;
		balls[i].gfx = texsmallball;
	}
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&previousTime);
}

void GameLogic()
{
	// Run balls
	for (int i = 0; i < NUM_BALLS; i++) {
		// New Pos.
		vec2 newpos = balls[i].pos + balls[i].vel;

		// Collision detection.
		bool collision = false;
		int colliding_ball = -1;
		for (int j = 0; j < NUM_BALLS; j++) {
			if (i != j) {
				float limit2 = (balls[i].radius + balls[j].radius) * (balls[i].radius + balls[j].radius);
				if (vlen2(newpos - balls[j].pos) <= limit2) {
					collision = true;
					colliding_ball = j;
					break;
				}
			}
		}

		if (!collision) {
			balls[i].pos = newpos;
		}
		else {
			// Rebound!
			balls[i].vel = balls[i].vel * -1.f;
			balls[colliding_ball].vel = balls[colliding_ball].vel * -1.f;
		}

		// Rebound on margins.
		if ((balls[i].pos.x > SCR_WIDTH) || (balls[i].pos.x < 0)) {
			balls[i].vel.x *= -1.0;
		}
		if ((balls[i].pos.y > SCR_HEIGHT) || (balls[i].pos.y < 0)) {
			balls[i].vel.y *= -1.0;
		}
	}
}

void Run()
{
	QueryPerformanceCounter(&currentTime);
	elapsedTime = (static_cast<double>(currentTime.QuadPart) - static_cast<double>(previousTime.QuadPart)) / static_cast<double>(freq.QuadPart);
	previousTime = currentTime;
	accumulatedElapsedTime += elapsedTime;
	totalTime += elapsedTime;

	if (accumulatedElapsedTime > (1.f / 15.f))
	{
		accumulatedElapsedTime = 1.f / 15.f;
	}
	
	while (accumulatedElapsedTime >= TICK_RATE)
	{
		GameLogic();
		currentFrames = accumulatedElapsedTime;
		currentLogicTime += TICK_RATE;
		accumulatedElapsedTime -= TICK_RATE;
	}
	//SYS_Sleep(17);
}