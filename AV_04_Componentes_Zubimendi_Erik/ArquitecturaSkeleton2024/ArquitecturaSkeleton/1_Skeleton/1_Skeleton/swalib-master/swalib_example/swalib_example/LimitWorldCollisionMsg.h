#pragma once
#include "CollisionMsg.h"

class LimitWorldCollisionMsg : public CollisionMsg
{
public:
	LimitWorldCollisionMsg(vec2 _vNewPos, vec2 _vNewDirection);
	vec2 vNewDirection;
};