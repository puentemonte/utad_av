#include "logic.h"
#include "render.h"
#include "core.h"
#include "sys.h"

Ball balls[NUM_BALLS]; // Array of balls.

extern GLuint texbkg;
extern GLuint texsmallball;

void InitGame()
{
	// Init game state.
	for (int i = 0; i < NUM_BALLS; i++) {
		balls[i].pos = vec2(CORE_FRand(0.0, SCR_WIDTH), CORE_FRand(0.0, SCR_HEIGHT));
		balls[i].vel = vec2(CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED), CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED));
		balls[i].radius = 16.f;
		balls[i].gfx = texsmallball;
	}
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