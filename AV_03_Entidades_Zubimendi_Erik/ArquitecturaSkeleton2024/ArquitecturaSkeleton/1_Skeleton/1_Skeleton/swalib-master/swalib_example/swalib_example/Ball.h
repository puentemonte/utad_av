#pragma once

#include "../../common/vector2d.h"

class Ball
{
private:
	vec2   m_vPos;
	vec2   m_vVel;
	float  m_fRadius;
public:
	Ball(vec2 _vPos, vec2 _vVel, float _fRadius);
	vec2 GetPos();
	vec2 GetVel();
	void SetVel(vec2 _vVel);
	float GetRadius();
	void Slot(double _TickRate);
};