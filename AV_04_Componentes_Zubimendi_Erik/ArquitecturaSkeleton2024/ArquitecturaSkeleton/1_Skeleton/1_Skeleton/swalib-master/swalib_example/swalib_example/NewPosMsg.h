#pragma once
#include "Message.h"
#include "../../common/vector2d.h"

class NewPosMsg : public Message
{
public:
    NewPosMsg(vec2 _vNewPos);

    vec2 vNewPos;
};