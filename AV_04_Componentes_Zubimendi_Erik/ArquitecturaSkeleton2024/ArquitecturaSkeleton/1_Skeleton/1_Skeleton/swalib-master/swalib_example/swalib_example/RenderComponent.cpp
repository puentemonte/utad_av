#include "RenderComponent.h"
#include "../../common/core.h"
#include "Entity.h"
#include "CollisionComponent.h"
#include "CollisionMsg.h"
#include "NewPosMsg.h"

void RenderComponent::Slot(double _TickRate)
{
	CollisionComponent* collisionComponent = m_Owner->FindComponent<CollisionComponent>();
	if (collisionComponent)
	{
		m_vPos = collisionComponent->GetPos();
	}
	CORE_RenderCenteredSprite(m_vPos, vec2(m_fSize, m_fSize), m_Texture);
}

void RenderComponent::ReceiveMessage(Message* _msg)
{
	CollisionMsg* collisionMsg = dynamic_cast<CollisionMsg*>(_msg);
	if (collisionMsg)
	{
		m_vPos = collisionMsg->vNewPos;
	}

	NewPosMsg* newPosMsg = dynamic_cast<NewPosMsg*>(_msg);
	if (newPosMsg)
	{
		m_vPos = newPosMsg->vNewPos;
	}
}

void RenderComponent::Init(Entity* _Owner, vec2 _vPos, float _fSize)
{
	m_Owner = _Owner;
	m_vPos = _vPos;
	m_fSize = _fSize;
}

void RenderComponent::LoadTexture(GLuint _Texture)
{
	m_Texture = _Texture;
}
