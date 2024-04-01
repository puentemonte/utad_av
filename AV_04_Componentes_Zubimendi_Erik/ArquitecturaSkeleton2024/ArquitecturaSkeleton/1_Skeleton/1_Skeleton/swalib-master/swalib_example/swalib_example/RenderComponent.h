#pragma once
#include "Component.h"
#include "../../common/stdafx.h"
#include "../../common/vector2d.h"

class RenderComponent : public Component
{
private:
	GLuint m_Texture;
	vec2   m_vPos;
	float  m_fSize;

public:
	virtual void Slot(double _TickRate = 1.f / 60.f) override;

	virtual void ReceiveMessage(Message* _msg) override;

	void Init(Entity* _Owner, vec2 _vPos, float _fSize);
	void LoadTexture(GLuint _Texture);
};

