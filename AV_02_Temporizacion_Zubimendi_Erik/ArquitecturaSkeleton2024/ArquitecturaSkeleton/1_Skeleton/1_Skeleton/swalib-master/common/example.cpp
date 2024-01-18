#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "font.h"
#include "vector2d.h"
#include "render.h"
#include "logic.h"

//-----------------------------------------------------------------------------
int Main(void)
{
	InitRender();
	InitGame();
  
	while (!SYS_GottaQuit()) {	// Controlling a request to terminate an application.

		Run();

		RenderScene();
		
		SYS_Pump();	// Process Windows messages.
		//SYS_Sleep(17);	// To force 60 fps
	}

	Shutdown();

	return 0;
}
