#include "RenderManager.h"
#include "../../common/stdafx.h"
#include "../../common/sys.h"
#include "../../common/core.h"
#include "../../common/font.h"
#include "../../common/vector2d.h"
#include "LogicManager.h"
#include "Ball.h"
#include "Timer.h"
//#include "TextureManager.h"
//#include "Sprite.h"

RenderManager* RenderManager::m_pRenderManager = nullptr;

RenderManager::RenderManager() {}

RenderManager* RenderManager::Get()
{
	if (m_pRenderManager == nullptr)
	{
		m_pRenderManager = new RenderManager();
	}
	return m_pRenderManager;
}

void RenderManager::InitRender()
{
	FONT_Init(); // Characters and symbols inicialization to draw on screen.

	// Set up rendering.
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT); // Sets up clipping.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// Specifies clear values for the color buffers.
	glMatrixMode(GL_PROJECTION);	// Specifies projection matrix is the current matrix.
	glLoadIdentity();	// Replaces the current matrix with the identity matrix.
	glOrtho(0.0, SCR_WIDTH, 0.0, SCR_HEIGHT, 0.0, 1.0);	// Multiplies the current matrix by an orthographic matrix.
	glEnable(GL_TEXTURE_2D);	// Enabling two-dimensional texturing.
	// NOTA: Mirar diferencias comentando las 2 siguientes funciones.
	glEnable(GL_BLEND);	// Blend the incoming RGBA color values with the values in the color buffers.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// Blend func. for alpha color.

	//TextureManager::Get()->LoadTexture("data/circle-bkg-128.png", true);
	//TextureManager::Get()->LoadTexture("data/tyrian_ball.png", false);

	m_BackgroundTexture = CORE_LoadPNG("data/circle-bkg-128.png", true);
	m_BallTexture = CORE_LoadPNG("data/tyrian_ball.png", false);

}

void RenderManager::RenderSlot()
{
	LogicManager* logicManager = LogicManager::Get();

	// Render
	glClear(GL_COLOR_BUFFER_BIT);	// Clear color buffer to preset values.

	// TODO: Remove. Call TextureManager.
	// Render background
	for (int i = 0; i <= SCR_WIDTH / 128; i++) {
		for (int j = 0; j <= SCR_HEIGHT / 128; j++) {
			CORE_RenderCenteredSprite(vec2(i * 128.f + 64.f, j * 128.f + 64.f), vec2(128.f, 128.f), m_BackgroundTexture);
		}
	}

	// Render balls
	for (int i = 0; i < logicManager->GetBallsSize(); i++) {
		CORE_RenderCenteredSprite(logicManager->GetBall(i)->GetPos(), vec2(32.f, 32.f), m_BallTexture);
	}

	RenderInfoText();

	// Exchanges the front and back buffers
	SYS_Show();
}

void RenderManager::ShutdownRender()
{
	FONT_End();

	//// TODO: Remove. Call TextureManager.
	CORE_UnloadPNG(m_BackgroundTexture);
	CORE_UnloadPNG(m_BallTexture);
}

void RenderManager::RenderInfoText()
{
	LogicManager* logicManager = LogicManager::Get();

	// Con el texto no tengo ni idea de lo que hacer xd
	// Text
	char sFrames[100];
	snprintf(sFrames, 100, "FPS:%f", 1.0f / logicManager->GetTimer()->GetFrames());
	FONT_DrawString(vec2(0, SCR_HEIGHT - 16), sFrames);

	char sTotalTime[100];
	snprintf(sTotalTime, 100, "TOTAL TIME:%f", logicManager->GetTimer()->GetTotalTime());
	FONT_DrawString(vec2(0, SCR_HEIGHT - 32), sTotalTime);

	char sTotalLogicTime[100];
	snprintf(sTotalLogicTime, 100, "LOGIC TIME:%f", logicManager->GetTimer()->GetTotalLogicTime());
	FONT_DrawString(vec2(0, SCR_HEIGHT - 48), sTotalLogicTime);
}