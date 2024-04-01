#pragma once
#include "../../common/stdafx.h"
//#include "../../common/sys.h"
//#include "../../common/core.h"

//class TextureManager;

class RenderManager
{
public:
	static RenderManager* Get();
	void InitRender();
	void RenderSlot();
	void ShutdownRender();

private:
	static RenderManager* m_pRenderManager;
	GLuint m_BackgroundTexture, m_BallTexture;

	RenderManager();
	void RenderInfoText();
};

