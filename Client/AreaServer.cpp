#include "StdAfx.h"
#include "smwsock.h"

#include "character.h"
#include "srcsound\\dxwav.h"
#include "particle.h"
#include "fileread.h"
#include "playmain.h"
#include "drawsub.h"
#include "netplay.h"

#include "effectsnd.h"
#include "playsub.h"
#include "skillsub.h"

#include "AreaServer.h"

TRANS_SEVER_MAP	TransAreaServer;

HANDLE	hAreaServerContol_Thread = 0;
DWORD	dwAreaServerContol_ID = 0;

CRITICAL_SECTION	cSection_Main;


DWORD	dwDebugAreaIP[4];
DWORD	dwDebugAreaCount = 0;
DWORD	dwDebugAreaConnCount = 0;
DWORD	dwDebugAreaStep = 0;