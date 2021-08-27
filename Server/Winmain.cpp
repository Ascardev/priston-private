#include "StdAfx.h"
#define _SINBARAM
#include "character.h"
#include "playmain.h"
#include "effectsnd.h"
#include "fileread.h"
#include "netplay.h"

#include "playsub.h"
#include "cracker.h"
#include "SkillSub.h"

#include "resource.h"
#include "AreaServer.h"

#include "actiongame.h"


char *szAppName = "PT Online";

HWND hwnd;

int quit = 0;
int QuitSave = 0;


DWORD	dwLastMouseMoveTime;
DWORD	dwLastCharMoveTime;

HINSTANCE hinst;

CApplication *pcApplication = nullptr;

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPreInst, LPSTR lpCmdLine, INT nCmdShow)
{
	initSinCos();

	pcApplication = new CApplication(new CServerWindow());

	if (pcApplication->Init(hInst))
	{
		pcApplication->Run();

		pcApplication->Shutdown();
	}

	DELET(pcApplication);

	return 0;
}