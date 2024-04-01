#include "MovementComponent.h"
#include "Entity.h"
#include "CollisionComponent.h"
#include "EntCollisionMsg.h"
#include "LimitWorldCollisionMsg.h"
#include "NewPosMsg.h"

void MovementComponent::Slot(double _TickRate)
{
	m_vPos += m_vVel * _TickRate;
	m_Owner->SendMessage(new NewPosMsg(m_vPos));
}

void MovementComponent::ReceiveMessage(Message* _msg)
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
		m_vPos = newPosMsg->vNewPos;
		return;
	}
}

void MovementComponent::Init(Entity* _Owner, vec2 _vPos, vec2 _vVel)
{
	m_Owner = _Owner;
	m_vPos = _vPos;
	m_vVel = _vVel;
}

vec2 MovementComponent::GetPos()
{
	return m_vPos;
}