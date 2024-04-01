#include "Ball.h"
#include "LogicManager.h"
#include "../../common/sys.h"

Ball::Ball(vec2 _vPos, vec2 _vVel, float _fRadius)
{
	m_vPos = _vPos;
	m_vVel = _vVel;
	m_fRadius = _fRadius;
}

vec2 Ball::GetPos()
{
	return m_vPos;
}

vec2 Ball::GetVel()
{
	return m_vVel;
}

void Ball::SetVel(vec2 _vVel)
{
	m_vVel.x = _vVel.x;
	m_vVel.y = _vVel.y;
}

float Ball::GetRadius()
{
	return m_fRadius;
}

void Ball::Slot(double _TickRate)
{

}