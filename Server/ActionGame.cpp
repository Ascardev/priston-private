#include "StdAfx.h"

#include "character.h"
#include "playmain.h"
#include "fileread.h"
#include "netplay.h"

#include "effectsnd.h"

#include "record.h"
#include "playsub.h"
#include "resource.h"
#include "skillsub.h"

#include "srcserver\\onserver.h"

#include "actiongame.h"


int ActionKeyAngle;
int	ActionKeyFlag = 0;
int ActionKeySpace = 0;
int ActionKeyControl = 0;

int		ActionKeyDash = 0;
DWORD	dwActionKeyTime = 0;
int		ActionDashMode = 0;
int		ActionKeyOld = 0;
short	ActionMouseClick[2] = { 0 , 0 };
