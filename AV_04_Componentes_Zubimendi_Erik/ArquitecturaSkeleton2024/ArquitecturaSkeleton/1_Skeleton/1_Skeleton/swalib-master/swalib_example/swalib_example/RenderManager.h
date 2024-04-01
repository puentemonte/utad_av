#pragma once
#include "../../common/stdafx.h"

class RenderManager
{
public:
	static RenderManager* Get();
	void InitRender();
	void RenderSlot();
	void ShutdownRender();

	/* Textures for different Game Elements */
	GLuint m_BackgroundTexture, m_BallTexture;

private:
	static RenderManager* m_pRenderManager;


	RenderManager();
	void RenderInfoText();
};

