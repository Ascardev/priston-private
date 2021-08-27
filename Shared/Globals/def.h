#pragma once

#define GAME_NAME				"PT Online"

#define GAME_VERSION			3101

#define MAX_UNITS				1024

#define WINDOW_WIDTH			300
#define WINDOW_HEIGHT			120

#define PLAYERS_MAX				1024
#define UNITS_MAX				2048
#define EVENT_BELLATRA_DIVSCORE	15

class CApplication;

extern CApplication *pcApplication;

class CGame;

extern CGame *g_lpGame;

#define GAME				g_lpGame

#define RELEASE(p)			{ if(p != NULL) p->Release(); p = NULL;}
#define INIT(p)				{ if(p != NULL) p->Init();}
#define INITP(p, ptr)		{ if(p != NULL && ptr != NULL) p->Init(ptr);}
#define DELET(p)			{ if(p != NULL) delete p; p = NULL;}
#define DELETA(p)			{ if(p != NULL) delete[] p; p = NULL;}
#define SHUTDOWN(p)			{ if(p != NULL) p->Shutdown();}
#define ADDREF(p)			{ if(p != NULL) p->AddRef();}
#define CLEARPTR(p)			{ if(p != NULL) p->Clear(); p = NULL;}
#define RESETPTR(p)			{ if(p != NULL) p.reset(); p = NULL;}

#define WM_UPDATE			WM_USER +   1
#define WM_WINDOWREADY		WM_USER +  51
#define WM_SOCKETACCEPT		WM_USER + 101
#define WM_SOCKETPACKET		WM_USER + 102
#define WM_SOCKETCLOSE		WM_USER + 103

#define TICKCOUNT			GetTickCount()

#define MAX_ROLLDICEDROP_TIME 15

#define WS_SERVER			(WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX)
#define WS_EX_SERVER		0 //(WS_EX_TOPMOST)

#define WS_WINDOWED			(WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)
#define WS_EX_WINDOWED		0 //(WS_EX_TOPMOST)

#define WS_FULLSCREEN		(WS_POPUP)
#define WS_EX_FULLSCREEN	0 //(WS_EX_TOPMOST)
