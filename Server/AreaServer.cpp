#include "StdAfx.h"
#include "character.h"
#include "fileread.h"
#include "playmain.h"
#include "netplay.h"

#include "effectsnd.h"
#include "playsub.h"
#include "skillsub.h"

#include "AreaServer.h"

TRANS_SEVER_MAP	TransAreaServer;

HANDLE	hAreaServerContol_Thread = 0;
DWORD	dwAreaServerContol_ID = 0;

DWORD	dwDebugAreaIP[4];
DWORD	dwDebugAreaCount = 0;
DWORD	dwDebugAreaConnCount = 0;
DWORD	dwDebugAreaStep = 0;