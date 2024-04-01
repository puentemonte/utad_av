#include "CollisionComponent.h"
#include "../../common/sys.h"
#include "LogicManager.h"
#include "Entity.h"
#include "MovementComponent.h"
#include "EntCollisionMsg.h"
#include "LimitWorldCollisionMsg.h"
#include "NewPosMsg.h"

void CollisionComponent::Slot(double _TickRate)
{
	LogicManager* logicManager = LogicManager::Get();

	// Collision detection.
	bool collision = false;
	int colliding_ball = -1;
	CollisionComponent* collidingBallCollisionComp = nullptr;

	for (int j = 0; j < logicManager->GetBallsNum(); ++j) {
		if (logicManager->GetBall(j) != m_Owner) {
			collidingBallCollisionComp = logicManager->GetBall(j)->FindComponent<CollisionComponent>();
			
			float limit2 = (m_fRadius + collidingBallCollisionComp->GetRadius()) * (m_fRadius + collidingBallCollisionComp->GetRadius());
			
			if (vlen2(m_vNewPos - collidingBallCollisionComp->GetPos()) <= limit2) {
				collision = true;
				colliding_ball = j;
				break;
			}
		}
	}

	if (!collision)
	{
		m_vPos = m_vNewPos;
	}
	else
	{
		// Rebound!
		m_Owner->SendMessage(new EntCollisionMsg(m_vPos));
		logicManager->GetBall(colliding_ball)->SendMessage(new EntCollisionMsg(collidingBallCollisionComp->GetPos()));
	}

	// Rebound on margins.
	if ((m_vPos.x > SCR_WIDTH) || (m_vPos.x < 0)) {
		m_Owner->SendMessage(new LimitWorldCollisionMsg(m_vPos, vec2(-1, 1)));
	}
	if ((m_vPos.y > SCR_HEIGHT) || (m_vPos.y < 0)) {
		m_Owner->SendMessage(new LimitWorldCollisionMsg(m_vPos, vec2(1, -1)));
	}
}

void CollisionComponent::ReceiveMessage(Message* _msg)
{
	EntCollisionMsg* entCollisionMsg = dynamic_cast<EntCollisionMsg*>(_msg);
	if (entCollisionMsg)
	{
		m_vVel *= -1;
		m_vPos = entCollisionMsg->vNewPos;
		return;
	}

	LimitWorldCollisionMsg* limitWorldCollisionMsg = dynamic_cast<LimitWorldCollisionMsg*>(_msg);
	if (limitWorldCollisionMsg)
	{
		m_vVel = m_vVel * limitWorldCollisionMsg->vNewDirection;
		m_vPos = limitWorldCollisionMsg->vNewPos;
		return;
	}

	NewPosMsg* newPosMsg = dynamic_cast<NewPosMsg*>(_msg);
	if (newPosMsg)
	{
		m_vNewPos = newPosMsg->vNewPos;
		return;
	}
}

void CollisionComponent::Init(Entity* _Owner, vec2 _vPos, vec2 _vVel, float _fRadius)
{
	m_Owner = _Owner;
	m_vPos = _vPos;
	m_vVel = _vVel;
	m_fRadius = _fRadius;
}

vec2 CollisionComponent::GetVel()
{
	return m_vVel;
}

void CollisionComponent::SetVel(vec2 _vVel)
{
	m_vVel = _vVel;
}

float CollisionComponent::GetRadius()
{
	return m_fRadius;
}

vec2 CollisionComponent::GetPos()
{
	return m_vPos;
}
