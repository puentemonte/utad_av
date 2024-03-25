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
	LogicManager* logicManager = LogicManager::Get();

	// New Pos.
	vec2 newpos = m_vPos + m_vVel * _TickRate;

	// Collision detection.
	bool collision = false;
	int colliding_ball = -1;
	for (int j = 0; j < logicManager->GetBallsSize(); j++) {
		if (logicManager->GetBall(j) != this) {
			float limit2 = (m_fRadius + logicManager->GetBall(j)->GetRadius()) * (m_fRadius + logicManager->GetBall(j)->GetRadius());
			if (vlen2(newpos - logicManager->GetBall(j)->GetPos()) <= limit2) {
				collision = true;
				colliding_ball = j;
				break;
			}
		}
	}

	if (!collision) {
		m_vPos = newpos;
	}
	else {
		// Rebound!
		m_vVel = m_vVel * -1.f;
		logicManager->GetBall(colliding_ball)->SetVel(logicManager->GetBall(colliding_ball)->GetVel() * -1.f);
	}

	// Rebound on margins.
	if ((m_vPos.x > SCR_WIDTH) || (m_vPos.x < 0)) {
		m_vVel.x = m_vVel.x * -1.f;
	}
	if ((m_vPos.y > SCR_HEIGHT) || (m_vPos.y < 0)) {
		m_vVel.y = m_vVel.y * -1.f;
	}
}