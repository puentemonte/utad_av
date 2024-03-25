#include "sys.h"
#include "../swalib_example/swalib_example/LogicManager.h"
#include "../swalib_example/swalib_example/RenderManager.h"

//-----------------------------------------------------------------------------
int Main(void)
{
	LogicManager* logicManager = LogicManager::Get();
	RenderManager* renderManager = RenderManager::Get();

	renderManager->InitRender();
	logicManager->InitGame();

	while (!SYS_GottaQuit()) {	// Controlling a request to terminate an application.

		logicManager->LogicSlot();

		renderManager->RenderSlot();

		SYS_Pump();	// Process Windows messages.
	}
	logicManager->ShutdownGame();
	renderManager->ShutdownRender();

	return 0;
}
