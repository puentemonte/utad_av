#pragma once
#include "Component.h"
#include "../../common/vector2d.h"

class CollisionComponent : public Component
{
private:
	vec2   m_vPos;
	vec2 m_vNewPos;
	vec2   m_vVel;
	float  m_fRadius;

public:
	virtual void Slot(double _TickRate = 1.f / 60.f) override;

	virtual void ReceiveMessage(Message* _msg) override;

	void Init(Entity* _Owner, vec2 _vPos, vec2 _vVel, float _fRadius);

	vec2 GetVel();

	void SetVel(vec2 _vVel);

	float GetRadius();

	vec2 GetPos();
};

