#pragma once
#include "../../common/vector2d.h"
#include "Component.h"

class MovementComponent : public Component
{
private:
	vec2   m_vPos;
	vec2   m_vVel;

public:
	virtual void Slot(double _TickRate = 1.f / 60.f) override;

	virtual void ReceiveMessage(Message* _msg) override;

	void Init(Entity* _Owner, vec2 _vPos, vec2 _vVel);

	vec2 GetPos();
};