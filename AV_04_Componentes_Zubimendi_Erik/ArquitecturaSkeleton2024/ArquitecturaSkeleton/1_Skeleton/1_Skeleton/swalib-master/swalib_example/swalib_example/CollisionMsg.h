#pragma once
#include "Message.h"
#include "../../common/vector2d.h"

class CollisionMsg : public Message
{
public:
	vec2 vNewPos;
};