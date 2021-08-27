#include "StdAfx.h"
#include "character.h"
#include "fileread.h"
#include "playmain.h"
#include "netplay.h"

#include "effectsnd.h"
#include "playsub.h"
#include "skillsub.h"

#include "srcserver\\svr_Damage.h"
#include "srcserver\\onserver.h"

//Ãß°¡ È¸ÇÇ µ¥¹ÌÁö Ãâ·Â ¿É¼Ç
#define DISP_DAMAGE

#ifdef	DISP_DAMAGE
int rsDisplayDamgeToClient(User *lpPlayInfo, char *szDmgMsg);
#endif

#define		SUCCUBUS_CURSE_TIME		10

//PK½Ã 40% Èí¼ö·Â Àû¿ë
#define		PKMODE_ABSORB			30

static smTEXLINK smTexLinkMotionBlur[128];		//ÅØ½ºÃÄ ÁÂÇ¥
static smVERTEX MbVertex[64];
static smFACE MbFace[64];

static smTEXLINK smTexLinkMotionBlur2[64];		//ÅØ½ºÃÄ ÁÂÇ¥
static smVERTEX MbVertex2[32];
static smFACE MbFace2[32];

#define	AGING_SUB_LEVEL	10

int	SkillChargingFlag = 0;			//½ºÅ³ Â÷Â¡ ÇÃ·¢
int	SkillEventDamageCount;			//½ºÅ³ µ¥¹ÌÁö Ä«¿îÅÍ

TRANS_SKIL_ATTACKDATA	Trans_SplashCharList;		//ÆÃ°Ü¼­ ¸Â´Â °ø°Ý µ¥ÀÌÅ¸ ÀÓ½ÃÀúÀå

//Å©¸®Æ¼ÄÃ ¼½¼Ç
CRITICAL_SECTION	cLoadSection;

int rsCheckHardCoreEventArea(int x, int y, int z);
extern int	rsHardCoreEventInterLineZ;
extern int	rsHardCoreEventInterLineZ2;
extern int	rsHardCoreEventPosY;
extern int	rsHardCoreEventOutLineZ;
extern rsSERVER_CONFIG		rsServerConfig;

//Æ¯Á¤À§Ä¡¿¡ º¸Á¶¸ó½ºÅÍ °­Á¦ ÃâÇö ½ÃÅ´
Unit *rsOpenSubMonster(Unit *lpMainChar, DWORD iMonsterEffectID, int x, int y, int z, int MaxFlag);
//ÇØ´ç ¸ó½ºÅÍ Ãâ½Å ±ê¹ß ÀÇ È°¼ºÈ­ ¸ó½ºÅÍ ¼ö
int rsGetMonCountFlag(Unit *lpChar);


//»ó´ë Ä³¸¯ÅÍ¿¡ ±â¼ú °ø°Ý °¡ÇÔ 
int rsSendTransSkillAttack(Unit *lpChar, User *lpPlayInfo);
//¼­¹ö - È¦¸® ¸®ÇÃ·º¼Ç °ø°Ý Ã³¸®
int rsProcessAttack_SkillHolyReflection(User *lpPlayInfo, Unit *lpChar);
//ÁÖº¯ ¸ó½ºÅÍ¸¦ Ã£´Â´Ù
Unit *rsFindAroundMonster(Unit *lpChar, int RoundDist);
//ÁÖº¯ ¸ó½ºÅÍ¸¦ Ã£¾Æ µ¥¹ÌÁö °ø°Ý
Unit *rsSkillDamage_AroundMonster(Unit *lpChar);
//ÁÖº¯ ¸ó½ºÅÍ¸¦ Ã£¾Æ ½ºÅ³ ( ¶óÅõ ÁÖº¯ ¸ó½ºÅÍ ½ºÅÏÁ¦°Å )
Unit *rsSkillMonster_AroundMonster(Unit *lpChar, int RoundDist);

//////////////////////////////////////////////////////////////////////

int GetProjPosi(int &x3d, int &y3d, int &z3d, POINT3D *CameraPosi, POINT3D *CameraAngle);
//»ó´ë Ä³¸¯ÅÍ¿¡ ±â¼ú °ø°Ý °¡ÇÔ 
int rsSendTransSkillAttack(Unit *lpChar, User *lpPlayInfo);

//½¦µµ¿ì ¸¶½ºÅ¸ ¿¬Å¸ Å¸°Ý Á¡
int	SkillShadowMasterEvent[9][7] = {
	{ 0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0 },

	{ 1,3,5,0,0,0,0 },		//3 ¹ø ¶§¸²
	{ 1,3,5,6,0,0,0 },
	{ 1,2,3,4,6,0,0 },
	{ 1,2,3,4,6,7,0 },
	{ 1,2,3,4,5,6,7 },		//7 ¹ø ¶§¸²

	{ 1,2,3,4,5,6,7 }
};

// ×£¸£µØÍ¼PK½çÏÞ
int CastleBattleZone_LineZ = -24043 * fONE;
int	CastleBattleZone_DoorLineZ = -25545 * fONE;
int	CastleBattleZone_DoorLineX[2] = { 34407 * fONE , 34695 * fONE };
int	CastleBattleZone_BridgeZ = -25258 * fONE;
int CastleSoulFountain_Area[4] = { 37040 * fONE , 37158 * fONE , -30286 * fONE, -30102 * fONE };

int GetDistanceDbl(int x1, int z1, int x2, int z2)
{
	int ax, az;

	ax = (x1 - x2) >> FLOATNS;
	az = (z1 - z2) >> FLOATNS;
	ax *= ax;
	az *= az;
	return ax + az;
}

//À§Ä¡¸¦ °Ë»çÇÏ¿© ÀÏÁ¤Å©±â ¹Ú½ºÅ©±â·Î È®ÀÎ
int CheckLocateBox(int x1, int y1, int z1, int x2, int y2, int z2, int size)
{
	if (abs(x1 - x2) < size && abs(y1 - y2) < size && abs(z1 - z2) < size)
		return TRUE;

	return FALSE;
}


char *szBipName_RightHand = "Bip weapon01";
char *szBipName_LeftHand = "Bip01 L Hand";
char *szBipName_Shield = "Bip01 L Forearm";
char *szBipName_Shield2 = "Bip-shield";
char *szBipName_BackSpine = "Bip in01";
char *szBipName_BackSpineCross = "Bip in-bow";
char *szBipName_BackSpineBow = "Bip in-cro";
char *szBipName_RFoot = "Bip01 R Foot";
char *szBipName_LFoot = "Bip01 L Foot";
char *szBipName_Head = "Bip01 Head";
char *szBipName_AssaWeapon = "Bip weapon05";
char *szBipName_BackSpineRightDagger = "Bip in07";
char *szBipName_BackSpineLeftDagger = "Bip in08";
char *szBipName_ShamanWeapon = "Bip01 TargetBone";

smPATTERN::smPATTERN(void)
{
	Init();
}


smPATTERN::~smPATTERN(void)
{
	Close();
}


//ÃÊ±âÈ­
void smPATTERN::Init()
{
	int cnt;

	for (cnt = 0; cnt < DPAT_MAX; cnt++)
		ZeroMemory(&DinaPat[cnt], sizeof(smDPAT));

	BipPattern = 0;
}

//¸»±âÈ­
int smPATTERN::Close()
{
	int cnt;

	for (cnt = 0; cnt < DPAT_MAX; cnt++)
	{
		if (DinaPat[cnt].Pat)
		{
			delete DinaPat[cnt].Pat;
			DinaPat[cnt].Pat = NULL;
			if (DinaPat[cnt].lpModelInfo)
			{
				delete DinaPat[cnt].lpModelInfo;
				DinaPat[cnt].lpModelInfo = NULL;
			}
		}
	}

	return TRUE;
}
int smPATTERN::FindFromName(char *szName)
{
	int cnt;

	for (cnt = 0; cnt < DPAT_MAX; cnt++)
	{
		if (DinaPat[cnt].Pat)
		{
			if (lstrcmpi(szName, DinaPat[cnt].szPatName) == 0)
				return cnt;
		}
	}

	return -1;
}
int smPATTERN::FindFromCode(DWORD dwCode)
{
	int cnt;

	for (cnt = 0; cnt < DPAT_MAX; cnt++)
	{
		if (DinaPat[cnt].Pat && dwCode == DinaPat[cnt].dwSpeedFindSum)
			return cnt;
	}

	return -1;
}
int smPATTERN::GetNew()
{
	int cnt;

	for (cnt = 0; cnt < DPAT_MAX; cnt++)
	{
		if (DinaPat[cnt].Pat == 0)
			return cnt;
	}

	return -1;
}
smDPAT *smPATTERN::LoadBipPattern(char *szFileName)
{
	int Num;
	DWORD dwCode;

	dwCode = GetCodebyName(szFileName);
	Num = FindFromCode(dwCode);

	if (Num < 0)
	{
		Num = GetNew();
		if (Num >= 0)
		{
			DinaPat[Num].Pat = smASE_ReadBone(szFileName);
			if (DinaPat[Num].Pat)
			{
				DinaPat[Num].smDinaLink = 0;
				lstrcpy(DinaPat[Num].szPatName, szFileName);
				DinaPat[Num].dwSpeedFindSum = dwCode;
				DinaPat[Num].UseCount = 1;
				return &DinaPat[Num];
			}
		}
		else
			return NULL;
	}

	DinaPat[Num].UseCount++;

	return &DinaPat[Num];
}

//¼ÓÔØÄ£ÐÍ
smDPAT *smPATTERN::LoadCharactor(char *szFileName)
{
	int Num, sframe;
	DWORD cnt;
	smDPAT *dMotionPat;
	smPAT3D	*AnimPat;
	DWORD	dwCode;

	smMODELINFO	modelInfo;

	dwCode = GetCodebyName(szFileName);
	Num = FindFromCode(dwCode);

	if (Num < 0)
	{
		if (smModelDecode(szFileName, &modelInfo) == NULL)
			return NULL;

		smASE_SetPhysique(0);

		Num = GetNew();

		if (Num < 0)
			return NULL;

		if (BipPattern && modelInfo.szMotionFile[0])
		{
			dMotionPat = BipPattern->LoadBipPattern(modelInfo.szMotionFile);
			if (dMotionPat)
			{
				smASE_SetPhysique(dMotionPat->Pat);
				DinaPat[Num].smDinaLink = dMotionPat;
			}
			else
				return NULL;
		}
		else
			DinaPat[Num].smDinaLink = 0;

		if (BipPattern && modelInfo.szTalkMotionFile[0])
		{
			smDPAT *lpTalkLink = BipPattern->LoadBipPattern(modelInfo.szTalkMotionFile);

			if (lpTalkLink)
				DinaPat[Num].lpTalkLink = lpTalkLink;
			else
				return NULL;
		}
		else
			DinaPat[Num].lpTalkLink = NULL;

		DinaPat[Num].Pat = smASE_Read(modelInfo.szModelFile);
		if (!DinaPat[Num].Pat)
		{
			
			return NULL;
		}

		if (DinaPat[Num].smDinaLink)
			AnimPat = DinaPat[Num].smDinaLink->Pat;
		else
			AnimPat = DinaPat[Num].Pat;

		if (AnimPat && AnimPat->TmFrameCnt > 0)
		{
			for (cnt = 0; cnt < modelInfo.MotionCount; cnt++)
			{
				sframe = AnimPat->TmFrame[modelInfo.MotionInfo[cnt].MotionFrame - 1].StartFrame / 160;
				modelInfo.MotionInfo[cnt].StartFrame += sframe;
				modelInfo.MotionInfo[cnt].EndFrame += sframe;
			}
		}

		DinaPat[Num].lpModelInfo = new smMODELINFO;
		memcpy(DinaPat[Num].lpModelInfo, &modelInfo, sizeof(smMODELINFO));
		lstrcpy(DinaPat[Num].szPatName, szFileName);
		DinaPat[Num].dwSpeedFindSum = dwCode;
		DinaPat[Num].UseCount = 1;
		return &DinaPat[Num];
	}

	DinaPat[Num].UseCount++;
	return &DinaPat[Num];
}


extern smPAT3D *PatKnife;
char *szDefaultCharName = "char\\woman.ini";


int InitLoader();
int CreateLoaderThread();
DWORD WINAPI smLoaderThreadProc(void *pInfo);

struct smDATALOADER {
	smSTAGE3D	*lpStage;
	Unit		*lpChar;
	scITEM		*lpItem;


	char		szLoadName[64];
	char		szLoadName2[64];

	int			Result;
	int			Cancel;
};

#define DATALOADER_MAX		64
#define DATALOADER_MASK		63

smDATALOADER	smLoader[DATALOADER_MAX];
int	smLoaderCnt;
int smLoaderEnd;
int	ThreadLoaderStats;

smPATTERN smBipPattern;
smPATTERN smPattern;

int AddLoaderStage(smSTAGE3D *lpStage, char *szName)
{
	int cnt;

	cnt = smLoaderEnd & DATALOADER_MASK;

	smLoaderEnd++;

	smLoader[cnt].lpStage = lpStage;
	smLoader[cnt].lpChar = 0;
	smLoader[cnt].lpItem = 0;
	smLoader[cnt].Cancel = 0;
	smLoader[cnt].Result = 0;
	lstrcpy(smLoader[cnt].szLoadName, szName);

	CreateLoaderThread();

	return smLoaderEnd;
}

int	AddLoaderPattern(Unit *lpChar, char *szName, char *szName2)
{
	int cnt;

	cnt = smLoaderEnd & DATALOADER_MASK;

	smLoaderEnd++;

	smLoader[cnt].lpStage = 0;
	smLoader[cnt].lpChar = lpChar;
	smLoader[cnt].lpItem = 0;
	smLoader[cnt].Cancel = 0;
	smLoader[cnt].Result = 0;
	lstrcpy(smLoader[cnt].szLoadName, szName);

	if (szName2)
		lstrcpy(smLoader[cnt].szLoadName2, szName2);
	else
		smLoader[cnt].szLoadName2[0] = 0;

	smLoader[cnt].lpChar->bLoading = TRUE;

	CreateLoaderThread();

	return TRUE;
}


int	AddLoaderItem(scITEM *lpItem, char *szName)
{
	int cnt;

	cnt = smLoaderEnd & DATALOADER_MASK;

	smLoaderEnd++;

	smLoader[cnt].lpStage = 0;
	smLoader[cnt].lpChar = 0;
	smLoader[cnt].lpItem = lpItem;
	smLoader[cnt].Cancel = 0;
	smLoader[cnt].Result = 0;
	lstrcpy(smLoader[cnt].szLoadName, szName);

	smLoader[cnt].lpItem->PatLoading = TRUE;

	CreateLoaderThread();

	return TRUE;
}


DWORD WINAPI smLoaderThreadProc(void *pInfo)
{
	int	cnt;
	smDPAT	*smDPat;
	smDPAT  *smDPat2;

	smDPAT *lpPatOld;
	smDPAT *lpPatOld2;

	EnterCriticalSection(&cLoadSection);

	cnt = smLoaderCnt & DATALOADER_MASK;

	if (smLoader[cnt].lpStage)
	{

		if (smSTAGE3D_ReadASE(smLoader[cnt].szLoadName, smLoader[cnt].lpStage))
		{
			smLoader[cnt].Result = TRUE;
			smLoader[cnt].lpStage->Head = TRUE;
		}
	}
	if (smLoader[cnt].lpChar)
	{
		smDPat = 0;
		smDPat2 = 0;

		smLoader[cnt].lpChar->bLoading = TRUE;

		lpPatOld = smLoader[cnt].lpChar->lpDinaPattern;
		lpPatOld2 = smLoader[cnt].lpChar->lpDinaPattern2;

		smDPat = smPattern.LoadCharactor(smLoader[cnt].szLoadName);

		if (smDPat)
		{
			smLoader[cnt].lpChar->DisplayFlag = 0;
			smLoader[cnt].lpChar->SetDinaPattern(smDPat);
			smLoader[cnt].lpChar->SetMotionFromCode(ANIMATIONTYPE_Idle);
			smLoader[cnt].lpChar->bActive = TRUE;
			lstrcpy(smLoader[cnt].lpChar->sCharacterData.Player.szBodyModel, smDPat->szPatName);

			smLoader[cnt].lpChar->sCharacterData.Player.szHeadModel[0] = 0;

			if (smDPat->lpModelInfo->szSubModelFile[0])
				smDPat2 = smPattern.LoadCharactor(smDPat->lpModelInfo->szSubModelFile);

			else
			{
				if (smLoader[cnt].szLoadName2[0])
				{
					smDPat2 = smPattern.LoadCharactor(smLoader[cnt].szLoadName2);
					lstrcpy(smLoader[cnt].lpChar->sCharacterData.Player.szHeadModel, smDPat2->szPatName);
				}
			}

			smLoader[cnt].lpChar->SetDinaPattern2(smDPat2);

			smLoader[cnt].lpChar->DisplayFlag = TRUE;

		}

		smLoader[cnt].Result = TRUE;

		if (lpPatOld)
			smDPAT_Delete(lpPatOld);

		if (lpPatOld2)
			smDPAT_Delete(lpPatOld2);

		smLoader[cnt].lpChar->bLoading = FALSE;
	}
	smLoaderCnt++;

	LeaveCriticalSection(&cLoadSection);

	ThreadLoaderStats = FALSE;


	return TRUE;
}

int CreateLoaderThread()
{
	smLoaderThreadProc(0);

	return FALSE;
}
int InitLoader()
{
	smLoaderCnt = 0;
	smLoaderEnd = 0;

	return TRUE;
}
int InitPatterns()
{
	smBipPattern.Init();
	smPattern.Init();

	smPattern.BipPattern = &smBipPattern;

	InitLoader();

	InitializeCriticalSection(&cLoadSection);

	return TRUE;
}

//ÆÐÅÏ¹öÆÛ¸¦ ¸»±âÈ­
int ClosePatterns()
{
	smBipPattern.Close();
	smPattern.Close();

	return TRUE;
}

//Á¦°Å
int smDPAT_Delete(smDPAT *dPat)
{
	if (dPat->UseCount > 0)
	{
		dPat->UseCount--;

		if (dPat->lpTalkLink && dPat->UseCount == 0)
			smDPAT_Delete(dPat->lpTalkLink);

		if (dPat->smDinaLink && dPat->UseCount == 0)
			smDPAT_Delete(dPat->smDinaLink);

		if (dPat->UseCount <= 0)
		{
			delete dPat->Pat;
			dPat->Pat = 0;
			if (dPat->lpModelInfo)
			{
				delete dPat->lpModelInfo;
				dPat->lpModelInfo = 0;
			}
		}
	}
	return NULL;
}


//Ä³¸¯ÅÍ¿¡ ÆÐÅÏÀ» ¼³Á¤
int SetLoadPattern(Unit *smChar, char *szName, char *szName2, POINT3D *Posi, POINT3D *Angle)
{
	smDPAT	*smDPat;
	smDPAT	*smDPat2;

	smDPat = 0;
	smDPat2 = 0;

	smDPat = smPattern.LoadCharactor(szName);

	if (smDPat)
	{
		smChar->Init();
		if (Posi && Angle)
			smChar->SetPosi(Posi->x, Posi->y, Posi->z, Angle->x, Angle->y, Angle->z);

		smChar->SetDinaPattern(smDPat);
		smChar->ChangeMotion(0);
		smChar->DisplayFlag = TRUE;
		lstrcpy(smChar->sCharacterData.Player.szBodyModel, smDPat->szPatName);

		smChar->sCharacterData.Player.szHeadModel[0] = 0;

		if (smDPat->lpModelInfo->szSubModelFile[0])
			smDPat2 = smPattern.LoadCharactor(smDPat->lpModelInfo->szSubModelFile);
		else
		{
			if (szName2 && szName2[0])
			{
				smDPat2 = smPattern.LoadCharactor(szName2);
				lstrcpy(smChar->sCharacterData.Player.szHeadModel, smDPat2->szPatName);
			}
		}

		smChar->SetDinaPattern2(smDPat2);

		return TRUE;
	}

	return FALSE;
}

//Ä³¸¯ÅÍ¿¡ ÆÐÅÏÀ» ¼³Á¤
int SetLoadPattern(Unit *smChar, char *szName, POINT3D *Posi, POINT3D *Angle)
{
	return SetLoadPattern(smChar, szName, 0, Posi, Angle);
}




////////////////////////// smCHAR ÇÔ¼ö /////////////////////////////
Unit::Unit()
{
	Pattern = 0;
	Pattern2 = 0;

	Init();
}

Unit::~Unit()
{

}

void Unit::Init()
{
	TalkPattern = NULL;
	TalkFrame = 0;
	TalkSoundSum = 0;
	lpTalkModelParent = NULL;
	lpTalkMotionInfo = NULL;

	ZeroMemory(&FrameInfo, sizeof(SMotionStEndInfo));

	iFrame = 0;
	action = 0;
	bActive = FALSE;
	pX = 0;
	pY = 0;
	pZ = 0;

	ZeroMemory(&Angle, sizeof(POINT3D));

	MoveFlag = FALSE;
	FrameCnt = 0;
	Counter = 0;

	ZeroMemory(sPlayBuff, sizeof(PlayBuffer) * PLAYBUFF_SIZE);

	iPlayBuffCount = 0;
	PlayBuffPosi_End = 0;

	lpDinaPattern = 0;
	lpDinaPattern2 = 0;
	bLoading = 0;

	lpDinaLeftPattern = 0;
	lpDinaRightPattern = 0;

	HvLeftHand.PatTool = 0;
	HvRightHand.PatTool = 0;
	HvLeftHand.dwItemCode = 0;
	HvRightHand.dwItemCode = 0;

	HvLeftHand.ColorBlink = 0;
	HvRightHand.ColorBlink = 0;

	wStickItems[0] = -1;
	wStickItems[1] = -1;
	wStickItems[2] = -1;
	wStickItems[3] = -1;

	DisplayFlag = 0;
	AnimDispMode = 0;
	PatDispMode = DISP_MODE_PATMAIN;
	MotionSelectFrame = 0;

	smMotionInfo = 0;

	smMotionInfo2 = 0;

	DisplayTools = TRUE;

	dwTarget = FALSE;

	if (smStage)
		lpStage = smStage;

	ptNextTarget.x = 0;
	ptNextTarget.y = 0;
	ptNextTarget.z = 0;

	pcFocusTarget = 0;
	pcAttackTarget = 0;

	pcOwner = nullptr;

	sCharacterData.sHP.sMin = 100;
	sCharacterData.sHP.sMax = 100;
	sCharacterData.iType = CHARACTERTYPE_None;

	dwLastActiveTime = TICKCOUNT;

	iFrameTimer = 0;

	PatWidth = 0;
	PatHeight = 0;
	PatSizeLevel = 0;

	FrameStep = 80;
	MoveSpeed = 250;
	AttackSpeed = fONE;

	pcMap = nullptr;
	pcKillerData = nullptr;
	pcBellatraKiller = nullptr;
	pcMapSpawn = nullptr;

	dwMessageEndTime = TICKCOUNT;
	uUnitInfoSize = 0;
	dwActionItemCode = 0;

	ShootingMode = FALSE;
	ShootingFlag = FALSE;
	chrAttackTarget = 0;

	AttackToolRange = 0;
	AttackAnger = 0;
	AttackIce = 0;

	OnStageFieldState = 0;
	OldMotionState = 0;

	OverLapPosi = 0;
	OverLapPosi2 = 0;
	lpCharOverLap = 0;

	TargetMoveCount = 0;

	AttackObjBip = 0;

	iAliveCounter = 256;
	AttackCritcal = 0;

	AutoMoveStep = 0;

	LevelLog = 0;

	dwNextMotionCode = 0;
	PosBeginCount = 0;

	EnableStateBar = 0;
	DisplayAlpha = 0;
	RendAlpha = 0;
	AttackSkil = 0;
	AttackEffect = 0;

	dwDispAppSkill = 0;
	dwDispAppSkillMask = 0;

	iPetID = 0;
	dwExclusiveNum = 0;
	dwAttackPlayTime = 0;

	CaravanSerial = 0; //³èÎï±àÂë
	CaravanTime = 0; //³èÎïÊ±¼ä
	CaravanMode = 0; //³èÎïÄ£Ê½

	Damge = 0; //ÉËº¦ÏÔÊ¾
	dwDamgeTimer = 0;
	DmgBlendValue = 0;
	DmgType[0] = 0;
	DmgType[1] = 0;

	PlaySlowCount = 0;
	PlaySlowSpeed = 0;
	iStunTimeLeft = 0;
	PlayStopCount = 0;
	ServerCode = 0;

	PlayHolyMind[1] = 0;
	PlayHolyPower[1] = 0;
	PlayPoison[1] = 0;	//¶¾
	DispPoison = 0;
	PlayFire[0] = 0;
	PlayFire[1] = 0;	//»ð
	DispFire = 0;
	PlayHolyIncantation[1] = 0;
	PlayVanish = 0;
	PlayCurseQuest = 0;
	PlayVague = 0;
	iDistortion = 0;
	PlayWeb = 0; //Ö©ÖëÍø
	PlayInvincible = 0;
	PlayDarkBoss = 0; //ÊÇ·ñ½øÈëBOSSµØÍ¼

	dwConcentrationTime = 0;	// »áÐÄÒ»»÷
	dwSwiftAxeTime = 0;	// ´ÌÉ±Ö®¸«
	dwBetserkerTime = 0;	// ·è¿ñÅ­ºð
	dwB_Berserker_Time = 0;	// ÖÚÉñÖ®Å­
	dwE_Shield_UseTime = 0;	// ¼«¹â»¤¶Ü
	dwP_Absorb_UseTime = 0;	// Áé¹â»¤Ìå
	dwAutomation_Time = 0;	// Áé¹â·ÉÑï // ¸ÄÁ¼×¨¼Ò
	dwMetal_Armor_Time = 0;	// ½ðÊôÖØ¼×
	dwSpark_Shield_Time = 0;	// ·ÀÓùµç²¨
	dwMagnetic_Sphere_Time = 0;	// ´ÅÐÔÇòÌå
	dwH_Sonic_Time = 0;	// ¿ìËÙ´ò»÷
	dwP_Enhence_Time = 0;	// Õ½Éñ×£¸£
	dwFalcon_Time = 0;	// Áé»êÖ®Ó¥
	dwGolden_Falcon_Time = 0;	// »Æ½ðÁÔÓ¥
	dwForceOfNatureTime = 0;	// ×ÔÈ»Ö®¹â
	dwAmplified_Time = 0;	// Ç±ÄÜ¼¤·¢
	dwWindy_Time = 0;	// ×·Ãü¾¢·ç
	dwT_Of_Valhalla_Time = 0;	// Õ½ÀõÅØÏø
	dwHallOfValhallaTime = 0;	// Íß¶û¹þÀ­
	dwFrost_Javelin_Time = 0;	// ±ùËª±êÇ¹
	dwTalaria_Time = 0;	// ÇáÎè·ÉÑï
	dwHolyBody_Time = 0;	// Ê¥¹â»¤Ìå
	dwHoly_Valor_Time = 0;	// ÉñÁ¦ÖØ»÷
	dwDrastic_Spirit_Time = 0;	// ÌìÓÓÉñîø
	dwD_Inhalation_Time = 0;	// Ê¥ÁéÖ®Îü
	dwGodly_Shield_Time = 0;	// ¾´ÉñÖ®¶Ü
	dwGod_Bless_Time = 0;	// ÉÏµÛ×£¸£
	dwH_Benedic_Time = 0;	// ÍöÁéÖ®Öä
	dwZenith_Time = 0;	// ¼¯ºÏÖ®Êõ
	dwEnergy_Shield_Time = 0;	// Ä§·¨ÊØ»¤
	dwSpirit_Elemental_Time = 0;	// Áé»êÕÙ»½
	dwDancing_Sword_Time = 0;	// ÔªËØÖ®½£
	dwDancing_Sword_Param = -1;	//
	dwT_Anima_Time = 0;	// Ê¥¹â·¨Õó
	dwHoly_Reflection_Time = 0;	// ÉñÊ¥·´Éä
	dwVirtual_Life_Time = 0;	// ÉñÊ¥Ö®¹â
	dwSummon_Muspell_Time = 0;	// ÉñÊ¥ÌìÊ¹
	dwB_Krishna_Time = 0;	// ÌìÅ®É¢»¨
	dwAlasTime = 0;	// Ãô½ÝÖ®Á¦
	dwInpesTime = 0;	// Ãô½Ý´óÊ¦
	dwAdvent_Migal_Time = 0;	// Âõ¿Ë¶û
	dwRainmaker_Time = 0;	// ÆíÓêÊ¦
	dwAdvent_Midranda_Time = 0;	// Ã×µÂÀ¼´ï
	dwCreed_Time = 0;	// ÖäÊõÐÅÑö
	dwWingEffectCode = 0;	// ³á°òÐ§¹û

	iAreaDamageArea = 0;

	RecvExp = 0;

	sAddColorEffect[0] = 0;
	sAddColorEffect[1] = 0;
	sAddColorEffect[2] = 0;
	sAddColorEffect[3] = 0;

	sCharacterData.sGlow = 0;
	sCharacterData.sSize = 0;

	RenderLatter = FALSE;
	dwLastUpdateTime = 0;

	dwTradeMsgCode = 0;
	EventAttackCount = 0;

	iBellatraCrown = 0;
	dwVipBit = 0;

	psaDamageUsersData = nullptr;
	psaSiegeWarDataList = 0;

	dwForceOrbCode = 0;
	dwForceOrbTime = 0;

	dwLifeBoosterCode = 0;
	dwLifeBoosterTime = 0;

	dwManaBoosterCode = 0;
	dwManaBoosterTime = 0;

	dwStaminaBoosterCode = 0;
	dwStaminaBoosterTime = 0;

	dwSkillDelayCode = 0;
	dwSkillDelayTime = 0;

	lExclusiveTargetID = 0;
	lpLinkPlayInfo = 0;
	pcExclusiveUnitTarget = 0;

	iCharacterType = CHARACTERTYPE_None;
	iClanID = 0;
	iHPBlocks = 0;

	sBlessCastle_Param[0] = 0;
	sBlessCastle_Param[1] = 0;
#ifndef _W_SERVER
	WeaponEffect = 0;
	dwWeaponEffectTime = 0;

	ClanInfoNum = -1;
	Clan_CastleMasterFlag = 0;
	dwClanInfoTime = 0;
	TryAttackCount = 0;

	sBlessCastle_Damage[0] = 0;
	sBlessCastle_Damage[1] = 0;
#else
	dwIgnoreOthersTime = 0;

	pcHookedTarget = 0;
	dwHookedTargetEndTime = 0;

	dwAssassinEyeTime = 0;
	AssassinEyeParam = 0;

	sMoveStepCount[0] = 0;
	sMoveStepCount[1] = 0;

	iSpecialType = 0;

	bBlessCastleCrown = 0;
#endif
}


int Unit::Close()
{
	bActive = FALSE;

	if (lpDinaPattern2)
	{
		AddRemoveDynPattern(lpDinaPattern2);
		lpDinaPattern2 = 0;
	}

	if (lpDinaPattern)
	{
		AddRemoveDynPattern(lpDinaPattern);
		lpDinaPattern = 0;
	}

	if (lpDinaLeftPattern)
	{
		AddRemoveDynPattern(lpDinaLeftPattern);
		lpDinaLeftPattern = 0;
	}

	if (lpDinaRightPattern)
	{
		AddRemoveDynPattern(lpDinaRightPattern);
		lpDinaRightPattern = 0;
	}


	Pattern = 0;
	Pattern2 = 0;

	HvLeftHand.PatTool = 0;
	HvRightHand.PatTool = 0;

	smMotionInfo = 0;
	smMotionInfo2 = 0;

	dwDispAppSkill = 0;

	DELETA(psaDamageUsersData);

	return TRUE;
}
// ×°±¸´©ÉÏ
int Unit::SetPattern(smPAT3D *pat)
{
	smPAT3D *AnimPat;

	Pattern = pat;

	if (pat->TmParent)
		AnimPat = pat->TmParent;
	else
		AnimPat = pat;

	if ((HvRightHand.dwItemCode& sinITEM_MASK2) == sinWN1)
		HvRightHand.ObjBip = AnimPat->GetObjectFromName(szBipName_BackSpine);
	else
		HvRightHand.ObjBip = AnimPat->GetObjectFromName(szBipName_RightHand);

	if ((HvLeftHand.dwItemCode&sinITEM_MASK2) == sinDS1)
		HvLeftHand.ObjBip = AnimPat->GetObjectFromName(szBipName_Shield);
	else
		HvLeftHand.ObjBip = AnimPat->GetObjectFromName(szBipName_LeftHand);

	BackObjBip[0] = AnimPat->GetObjectFromName(szBipName_BackSpine);
	BackObjBip[1] = AnimPat->GetObjectFromName(szBipName_BackSpineBow);
	BackObjBip[2] = AnimPat->GetObjectFromName(szBipName_BackSpineCross);
	BackObjBip[3] = AnimPat->GetObjectFromName(szBipName_BackSpineRightDagger);
	BackObjBip[4] = AnimPat->GetObjectFromName(szBipName_BackSpineLeftDagger);

	ShieldObjBip = AnimPat->GetObjectFromName(szBipName_Shield2);
	DaggerObjBip = AnimPat->GetObjectFromName(szBipName_AssaWeapon);

	AttackObjBip = 0;

	/*if (sCharacterData.iClass == CHARACTERCLASS_Archer || sCharacterData.iClass == CHARACTERCLASS_Atalanta)
		AttackObjBip = AnimPat->GetObjectFromName(szBipName_LFoot);

	if (sCharacterData.iClass == CHARACTERCLASS_Priestess)
		AttackObjBip = AnimPat->GetObjectFromName(szBipName_Head);*/

	switch (sCharacterData.iClass)
	{
	case CHARACTERCLASS_Archer:
	case CHARACTERCLASS_Atalanta:
		AttackObjBip = AnimPat->GetObjectFromName(szBipName_LFoot);
		break;
	case CHARACTERCLASS_Priestess:
		AttackObjBip = AnimPat->GetObjectFromName(szBipName_Head);
		break;
	}

	AnimPattern = AnimPat;

	PatHeight = pat->SizeHeight;
	PatWidth = (pat->SizeWidth * 160) >> FLOATNS;

	return TRUE;
}
int Unit::SetPattern2(smPAT3D *pat)
{
	Pattern2 = pat;

	return TRUE;
}

DWORD dwItemCodeFromVillage[] =
{
	(sinWC1 | sin01),(sinWC1 | sin02),(sinWC1 | sin03),(sinWC1 | sin04),(sinWC1 | sin05),
	(sinWC1 | sin06),(sinWC1 | sin07),(sinWC1 | sin08),(sinWC1 | sin09),(sinWC1 | sin10),
	(sinWC1 | sin11),(sinWC1 | sin12),(sinWC1 | sin13),(sinWC1 | sin14),(sinWC1 | sin15),
	(sinWC1 | sin16),(sinWC1 | sin17),(sinWC1 | sin18),(sinWC1 | sin19),(sinWC1 | sin20),
	(sinWC1 | sin21),(sinWC1 | sin22),(sinWC1 | sin23),(sinWC1 | sin25),(sinWC1 | sin24),
	(sinWC1 | sin26),(sinWC1 | sin27),(sinWC1 | sin28),(sinWC1 | sin29),(sinWC1 | sin61),
	(sinWC1 | sin63),(sinWC1 | sin64),(sinWC1 | sin65),(sinWC1 | sin66),

	(sinWM1 | sin01),(sinWM1 | sin02),(sinWM1 | sin03),(sinWM1 | sin06),
	(sinWS2 | sin01),(sinWS2 | sin02),(sinWS2 | sin03),

	(sinWS1 | sin02),(sinWS1 | sin03),
	(sinWS1 | sin09),(sinWS1 | sin65),(sinWS1 | sin67),

	(sinTW1 | sin01),(sinTW1 | sin02),(sinTW1 | sin04),(sinTW1 | sin05),(sinTW1 | sin07),
	0
};

DWORD dwItemCodeFromVillage_Bow[] =
{
	(sinWS1 | sin04),(sinWS1 | sin08),(sinWS1 | sin10),(sinWS1 | sin13),(sinWS1 | sin17),(sinWS1 | sin61),
	0
};

DWORD dwItemCodeFromVillage_Cross[] =
{
	(sinWS1 | sin01),(sinWS1 | sin05),(sinWS1 | sin06),(sinWS1 | sin07),
	(sinWS1 | sin11),(sinWS1 | sin12),(sinWS1 | sin14),(sinWS1 | sin15),
	(sinWS1 | sin16),(sinWS1 | sin26),(sinWS1 | sin27),(sinWS1 | sin28),
	(sinWS1 | sin29),(sinWS1 | sin30),(sinWS1 | sin31),(sinWS1 | sin62),
	(sinWS1 | sin63),(sinWS1 | sin64),(sinWS1 | sin66),
	0
};


int Unit::SetPosi(int x, int y, int z, int angX, int angY, int angZ)
{
	pX = x;
	pZ = z;
	pY = y;

	if (y == 0 && lpStage)
		pY = lpStage->GetHeight(pX, pZ);

	pY -= 2 * fONE;

	PHeight = pY;

	Angle.x = angX;
	Angle.y = angY;
	Angle.z = angZ;

	return TRUE;
}

int Unit::SetTargetPosi(int x, int z)
{

	tx = x << FLOATNS;
	tz = z << FLOATNS;
	MoveFlag = TRUE;

	Angle.y = GetRadian2D(pX, pZ, tx, tz);

	if (ActionPattern == 0)
	{
		if (MoveMode)
			SetMotionFromCode(ANIMATIONTYPE_Running);
		else
			SetMotionFromCode(ANIMATIONTYPE_Walking);
	}

	return Angle.y;
}

int Unit::SetTargetPosi2(int x, int z)
{

	tx = x << FLOATNS;
	tz = z << FLOATNS;

	Angle.y = GetRadian2D(pX, pZ, tx, tz);

	return Angle.y;
}

int Unit::SetNextTarget(int x, int y, int z)
{
	ptNextTarget.x = x;
	ptNextTarget.y = y;
	ptNextTarget.z = z;

	return TRUE;
}

int Unit::SetAction(int nAction)
{
	if (nAction == 0)
		MoveFlag = FALSE;

	return TRUE;

}

//µØÍ¼ÒÆ¶¯
int Unit::MoveAngle2(int step)
{
	int x, z, y;
	int he;
	POINT3D MovePosi;

	WaterHeight = CLIP_OUT;

	if (iSpecialType)
		return FALSE;

	POINT3D Posi;

	he = 0;

	Posi.x = x = pX;
	Posi.y = y = pY;
	Posi.z = z = pZ;

	if (step == 0 || PHeight < y)
	{
		if (lpStage)
		{
			he = lpStage->GetFloorHeight(x, y, z, Pattern->SizeHeight);
		}

		if (he != CLIP_OUT)
			y = he;
		else
			y = -80 * fONE;

		if ((pY - y) > 8 * fONE)
		{
			if (psModelAnimation && psModelAnimation->iType != ANIMATIONTYPE_Falling && (pY - y) > 32 * fONE)
			{
				FallHeight = pY - y;
				SetMotionFromCode(ANIMATIONTYPE_Falling);
			}
			PHeight = y;
			pY -= 8 * fONE;
		}
		else
		{
			pY = y;
			PHeight = y;

			if (psModelAnimation && psModelAnimation->iType == ANIMATIONTYPE_Falling)
			{
				if (FallHeight > 200 * fONE)
					SetMotionFromCode(ANIMATIONTYPE_FallHigh);
				else
					SetMotionFromCode(ANIMATIONTYPE_FallLow);
			}
		}
		return TRUE;
	}
	else
	{
		if (lpStage && lpStage->CheckNextMove(&Posi, &Angle, &MovePosi, step, Pattern->SizeWidth, Pattern->SizeHeight, OverLapPosi2) > 0)
		{
			x = MovePosi.x;
			y = MovePosi.y;
			z = MovePosi.z;
		}
	}

	pX = x;
	pZ = z;

	if ((pY - y) > 8 * fONE)
	{
		if (psModelAnimation && psModelAnimation->iType != ANIMATIONTYPE_Falling && (pY - y) > 32 * fONE)
		{
			FallHeight = pY - y;
			SetMotionFromCode(ANIMATIONTYPE_Falling);
		}

		PHeight = y;
		pY -= 8 * fONE;
	}
	else
	{
		pY = y;
		PHeight = y;

		if (psModelAnimation && psModelAnimation->iType == ANIMATIONTYPE_Falling)
		{
			if (FallHeight > 200 * fONE)
				SetMotionFromCode(ANIMATIONTYPE_FallHigh);
			else
				SetMotionFromCode(ANIMATIONTYPE_FallLow);
		}
	}

	return TRUE;
}
int Unit::MoveAngle(int step)
{
	return	MoveAngle2(step*fONE);
}

int Unit::SetDinaPattern(smDPAT *lpDPat)
{
	TalkPattern = NULL;
	TalkFrame = TalkSoundSum = 0;
	lpTalkModelParent = NULL;
	lpTalkMotionInfo = NULL;

	lpDinaPattern = lpDPat;

	if (lpDPat)
	{
		smMotionInfo = lpDinaPattern->lpModelInfo;
		SetPattern(lpDPat->Pat);
	}

	SetMotionFromCode(ANIMATIONTYPE_Idle);

	return TRUE;
}

int Unit::SetDinaPattern2(smDPAT	*lpDPat)
{
	lpDinaPattern2 = lpDPat;

	if (lpDinaPattern2)
	{
		smMotionInfo2 = lpDinaPattern2->lpModelInfo;
		SetPattern2(lpDPat->Pat);

		if (Pattern->TmParent == Pattern2->TmParent)
		{
			AnimDispMode = 0;
			PatDispMode = DISP_MODE_PATMAIN | DISP_MODE_PATSUB;
		}
		else
		{
			AnimDispMode = 1;
			PatDispMode = DISP_MODE_PATMAIN;
		}
	}
	else
	{
		AnimDispMode = 0;
		PatDispMode = DISP_MODE_PATMAIN;
		SetPattern2(0);
	}

	if (lpDinaPattern->lpTalkLink)
	{
		PatDispMode |= DISP_MODE_PATTALK;
		TalkPattern = lpDinaPattern->lpTalkLink->Pat;
	}
	else if (lpDinaPattern2 && lpDinaPattern2->lpTalkLink)
	{
		PatDispMode |= DISP_MODE_PATTALK;
		TalkPattern = lpDinaPattern2->lpTalkLink->Pat;
	}

	if (TalkPattern && (PatDispMode & DISP_MODE_PATTALK))
	{
		if (smMotionInfo && smMotionInfo->szTalkLinkFile[0])
			lpTalkModelParent = smMotionInfo;
		else if (smMotionInfo2 && smMotionInfo2->szTalkLinkFile[0])
			lpTalkModelParent = smMotionInfo2;
		else
		{
			PatDispMode &= (~DISP_MODE_PATTALK);
			TalkPattern = NULL;
		}
	}

	return TRUE;
}

//¿òÁ÷ÀÓ µ¿ÀÛ ¼³Á¤
int Unit::ChangeMotion(int Motion, int DpMode)
{

	if (DpMode)
	{
		if (MotionSelectFrame)
		{
			psModelAnimation = &smMotionInfo2->MotionInfo[Motion];
			PatDispMode = DISP_MODE_PATSUB;
		}
		else
		{
			psModelAnimation = &smMotionInfo->MotionInfo[Motion];
			PatDispMode = DISP_MODE_PATMAIN;
		}
	}
	else
	{
		if (AnimDispMode)
			PatDispMode = DISP_MODE_PATMAIN;

		psModelAnimation = &smMotionInfo->MotionInfo[Motion];
		MotionSelectFrame = 0;
	}

	iFrame = psModelAnimation->StartFrame * 160;
	action = Motion;
	iFrameTimer = 0;

	AttackSkil = 0;
	HideWeapon = 0;
	MotionLoop = 0;

	dwEventFrameExt[0] = 0;
	dwEventFrameExt[1] = 0;
	dwEventFrameExt[2] = 0;
	dwEventFrameExt[3] = 0;

	FrameInfo.StartFrame = iFrame;
	FrameInfo.EndFrame = psModelAnimation->EndFrame * 160;

	return TRUE;
}

int Unit::AutoChangeTalkMotion(int TalkModeType)
{
	if (TalkPattern == NULL)
		return FALSE;

	int TalkCnt = 0;
	if (lpTalkModelParent->TalkMotionRate[CHRMOTION_EXT])
	{
		TalkCnt = rand() % 100;
		TalkCnt = lpTalkModelParent->TalkMotionRateCnt[TalkModeType][TalkCnt];
	}
	else
		TalkCnt = rand() % lpTalkModelParent->TalkMotionCount;

	lpTalkMotionInfo = &lpTalkModelParent->TalkMotionInfo[TalkCnt];
	TalkFrame = lpTalkMotionInfo->StartFrame * 160;

	return TRUE;
}

int Unit::FindMotionCountFromCode(DWORD MotionCode)
{
	int cnt;
	int FindCnt = 0;

	if (smMotionInfo)
	{
		for (cnt = 0; cnt < (int)smMotionInfo->MotionCount; cnt++)
		{
			if (smMotionInfo->MotionInfo[cnt].iType == MotionCode)
				FindCnt++;
		}
	}

	return FindCnt;
}

#define WAONEMOTIONSTYLE (sinWA1|sin01)
#define WATWOMOTIONSTYLE (sinWA1|sin05)
#define WCONEMOTIONSTYLE (sinWC1|sin01)
#define WHONEMOTIONSTYLE (sinWH1|sin01)
#define WHTOWMOTIONSTYLE (sinWH1|sin06)
#define WMONEMOTIONSTYLE (sinWM1|sin01)
#define WMTWOMOTIONSTYLE (sinWM1|sin04)
#define WPONEMOTIONSTYLE (sinWP1|sin01)
#define WPTWOMOTIONSTYLE (sinWP1|sin04)
#define WBONEMOTIONSTYLE (sinWS1|sin02)
#define WBTWOMOTIONSTYLE (sinWS1|sin01)
#define WBTHRMOTIONSTYLE (sinWS1|sin04)
#define WSONEMOTIONSTYLE (sinWS2|sin01)
#define WSTWOMOTIONSTYLE (sinWS2|sin05)
#define WTONEMOTIONSTYLE (sinWT1|sin01)
#define WNONEMOTIONSTYLE (sinWN1|sin01)
#define WDONEMOTIONSTYLE (sinWD1|sin01)

DWORD ItemMotionCode[][2] =
{
	{(sinWA1 | sin25),WATWOMOTIONSTYLE},{(sinWA1 | sin28),WATWOMOTIONSTYLE},{(sinWA1 | sin29),WATWOMOTIONSTYLE},{(sinWA1 | sin30),WATWOMOTIONSTYLE},

	{(sinWA1 | sin61),WAONEMOTIONSTYLE},{(sinWA1 | sin62),WATWOMOTIONSTYLE},{(sinWA1 | sin63),WAONEMOTIONSTYLE},{(sinWA1 | sin64),WATWOMOTIONSTYLE},
	{(sinWA1 | sin65),WATWOMOTIONSTYLE},{(sinWA1 | sin66),WAONEMOTIONSTYLE},{(sinWA1 | sin67),WAONEMOTIONSTYLE},

	{(sinWC1 | sin25),WCONEMOTIONSTYLE},

	{(sinWC1 | sin27),WCONEMOTIONSTYLE},{(sinWC1 | sin28),WCONEMOTIONSTYLE},{(sinWC1 | sin29),WCONEMOTIONSTYLE},

	{(sinWC1 | sin61),WCONEMOTIONSTYLE},{(sinWC1 | sin63),WCONEMOTIONSTYLE},{(sinWC1 | sin64),WCONEMOTIONSTYLE},{(sinWC1 | sin65),WCONEMOTIONSTYLE},
	{(sinWC1 | sin66),WCONEMOTIONSTYLE},

	{(sinWH1 | sin26),WHTOWMOTIONSTYLE},

	{(sinWH1 | sin29),WHTOWMOTIONSTYLE},{(sinWH1 | sin30),WHTOWMOTIONSTYLE},{(sinWH1 | sin31),WHTOWMOTIONSTYLE},

	{(sinWH1 | sin63),WHTOWMOTIONSTYLE},{(sinWH1 | sin64),WHTOWMOTIONSTYLE},{(sinWH1 | sin65),WHTOWMOTIONSTYLE},{(sinWH1 | sin66),WHTOWMOTIONSTYLE},

	{(sinWM1 | sin26),WMTWOMOTIONSTYLE},

	{(sinWM1 | sin29),WMTWOMOTIONSTYLE},{(sinWM1 | sin30),WMTWOMOTIONSTYLE},{(sinWM1 | sin31),WMTWOMOTIONSTYLE},

	{(sinWM1 | sin61),WMTWOMOTIONSTYLE},{(sinWM1 | sin63),WMTWOMOTIONSTYLE},{(sinWM1 | sin64),WMTWOMOTIONSTYLE},{(sinWM1 | sin65),WMONEMOTIONSTYLE},
	{(sinWM1 | sin66),WMTWOMOTIONSTYLE},{(sinWM1 | sin67),WMONEMOTIONSTYLE},

	{(sinWP1 | sin26),WPTWOMOTIONSTYLE},

	{(sinWP1 | sin28),WPTWOMOTIONSTYLE},{(sinWP1 | sin29),WPTWOMOTIONSTYLE},{(sinWP1 | sin30),WPTWOMOTIONSTYLE},

	{(sinWP1 | sin61),WPTWOMOTIONSTYLE},{(sinWP1 | sin62),WPTWOMOTIONSTYLE},{(sinWP1 | sin63),WPTWOMOTIONSTYLE},{(sinWP1 | sin64),WPTWOMOTIONSTYLE},
	{(sinWP1 | sin65),WPONEMOTIONSTYLE},{(sinWP1 | sin66),WPTWOMOTIONSTYLE},{(sinWP1 | sin67),WPONEMOTIONSTYLE},

	{(sinWS1 | sin27),WBTWOMOTIONSTYLE},

	{(sinWS1 | sin29),WBTWOMOTIONSTYLE},{(sinWS1 | sin30),WBTWOMOTIONSTYLE},{(sinWS1 | sin31),WBTWOMOTIONSTYLE},

	{(sinWS1 | sin61),WBTHRMOTIONSTYLE},{(sinWS1 | sin62),WBTWOMOTIONSTYLE},{(sinWS1 | sin63),WBTWOMOTIONSTYLE},{(sinWS1 | sin64),WBTWOMOTIONSTYLE},
	{(sinWS1 | sin65),WBONEMOTIONSTYLE},{(sinWS1 | sin66),WBTWOMOTIONSTYLE},{(sinWS1 | sin67),WBONEMOTIONSTYLE},

	{(sinWS2 | sin28),WSTWOMOTIONSTYLE},

	{(sinWS2 | sin31),WSTWOMOTIONSTYLE},{(sinWS2 | sin32),WSTWOMOTIONSTYLE},{(sinWS2 | sin33),WSTWOMOTIONSTYLE},

	{(sinWS2 | sin61),WSONEMOTIONSTYLE},{(sinWS2 | sin62),WSONEMOTIONSTYLE},{(sinWS2 | sin63),WSONEMOTIONSTYLE},{(sinWS2 | sin64),WSTWOMOTIONSTYLE},
	{(sinWS2 | sin65),WSONEMOTIONSTYLE},{(sinWS2 | sin66),WSTWOMOTIONSTYLE},{(sinWS2 | sin67),WSONEMOTIONSTYLE},{(sinWS2 | sin68),WSONEMOTIONSTYLE},

	{(sinWT1 | sin26),WTONEMOTIONSTYLE},

	{(sinWT1 | sin28),WTONEMOTIONSTYLE},{(sinWT1 | sin29),WTONEMOTIONSTYLE},{(sinWT1 | sin30),WTONEMOTIONSTYLE},

	{(sinWT1 | sin61),WTONEMOTIONSTYLE},{(sinWT1 | sin63),WTONEMOTIONSTYLE},{(sinWT1 | sin64),WTONEMOTIONSTYLE},{(sinWT1 | sin65),WTONEMOTIONSTYLE},
	{(sinWT1 | sin66),WTONEMOTIONSTYLE},

	{(sinWN1 | sin27),WNONEMOTIONSTYLE},{(sinWN1 | sin28),WNONEMOTIONSTYLE},{(sinWN1 | sin29),WNONEMOTIONSTYLE},{(sinWN1 | sin30),WNONEMOTIONSTYLE},

	{(sinWD1 | sin27),WDONEMOTIONSTYLE},{(sinWD1 | sin28),WDONEMOTIONSTYLE},{(sinWD1 | sin29),WDONEMOTIONSTYLE},{(sinWD1 | sin30),WDONEMOTIONSTYLE},

	{(sinTW1 | sin01),WCONEMOTIONSTYLE},{(sinTW1 | sin02),WSONEMOTIONSTYLE},{(sinTW1 | sin03),WHONEMOTIONSTYLE},{(sinTW1 | sin04),WAONEMOTIONSTYLE},
	{(sinTW1 | sin05),WMONEMOTIONSTYLE},{(sinTW1 | sin06),WPONEMOTIONSTYLE},{(sinTW1 | sin07),WBONEMOTIONSTYLE},{(sinTW1 | sin08),WATWOMOTIONSTYLE},
	{(sinTW1 | sin09),WPTWOMOTIONSTYLE},{(sinTW1 | sin10),WPTWOMOTIONSTYLE},{(sinTW1 | sin11),WATWOMOTIONSTYLE},
	{0,0}
};
int CheckMotionItem(DWORD FindCode, DWORD ActionCode)
{
	return FALSE;
}

int Unit::SetMotionFromCode(DWORD MotionCode)
{
	int cnt, cnt2, itcnt;
	int FoundNum[64];
	int FindCnt;

	int FoundNum2[64];
	int FindCnt2;
	int StageVillage;
	int	dwActItemCode;
	int	atSkill = 0;
	int	skillCode;
	BYTE	bSkill;

	DWORD	dwJobCodeMask;

	WORD dwFindCode;

	smMODELINFO	*lpMotionInfo;

	if (sCharacterData.iClass && sCharacterData.iClass <= 10)
		dwJobCodeMask = BitMaskJobNames[sCharacterData.iClass - 1].dwBitMask;
	else
		dwJobCodeMask = 0;

	FindCnt = 0;
	FindCnt2 = 0;
	MotionSelectFrame = 0;
	dwActItemCode = dwActionItemCode;

	StageVillage = 3;

	lpMotionInfo = smMotionInfo;

	if (MotionCode == ANIMATIONTYPE_Skill && AttackSkil)
		atSkill = AttackSkil;

	if (smMotionInfo)
	{
		for (cnt = 0; cnt < (int)smMotionInfo->MotionCount; cnt++)
		{
			if (smMotionInfo->MotionInfo[cnt].iType == MotionCode && (!smMotionInfo->MotionInfo[cnt].MapPosition || (smMotionInfo->MotionInfo[cnt].MapPosition&StageVillage)) && (!smMotionInfo->MotionInfo[cnt].dwJobCodeBit || !dwJobCodeMask || (smMotionInfo->MotionInfo[cnt].dwJobCodeBit&dwJobCodeMask)))
			{
				if (atSkill)
				{
					cnt2 = 0;
					skillCode = atSkill & 0xFF;

					while (1)
					{
						bSkill = smMotionInfo->MotionInfo[cnt].SkillCodeList[cnt2];
						if (bSkill == 0)
							break;
						if (SkillDataCode[bSkill].dwPlaySkillCode == skillCode)
						{
							break;
						}
						cnt2++;
					}
					if (bSkill)
					{
						FoundNum[FindCnt++] = cnt;
						if (FindCnt >= 32)
							break;
					}
				}
				else
				{

					if ((dwActItemCode & sinITEM_MASK2) == sinWN1 || dwActItemCode == 0)
						StageVillage = 1;
					FoundNum[FindCnt++] = cnt;
					if (FindCnt >= 32)
						break;
				}
			}
		}
	}
	if (FindCnt == 0 && AnimDispMode && lpDinaPattern2 && smMotionInfo2)
	{
		for (cnt = 0; cnt < (int)smMotionInfo2->MotionCount; cnt++)
		{
			if (smMotionInfo2->MotionInfo[cnt].iType == MotionCode && (!smMotionInfo2->MotionInfo[cnt].MapPosition || (smMotionInfo2->MotionInfo[cnt].MapPosition&StageVillage)))
			{
				FoundNum[FindCnt++] = cnt;
				if (FindCnt >= 32)
					break;
			}
		}
		if (FindCnt)
		{
			MotionSelectFrame = 1;
			lpMotionInfo = smMotionInfo2;
		}
	}
	for (cnt = 0; cnt < FindCnt; cnt++)
	{
		itcnt = lpMotionInfo->MotionInfo[FoundNum[cnt]].ItemCodeCount;
		if (itcnt == 0)
			FoundNum2[FindCnt2++] = FoundNum[cnt];
		else
		{
			if (dwActItemCode)
			{
				for (cnt2 = 0; cnt2 < itcnt; cnt2++)
				{
					dwFindCode = lpMotionInfo->MotionInfo[FoundNum[cnt]].ItemCodeList[cnt2];
					/*if (dwActItemCode==(int)sItem[dwFindCode].CODE)
					{
						FoundNum2[FindCnt2++] = FoundNum[cnt];
						break;
					}*/
					if (CheckMotionItem(dwFindCode, dwActItemCode))
					{
						FoundNum2[FindCnt2++] = FoundNum[cnt];
						break;
					}
				}
			}
			else
			{
				for (cnt2 = 0; cnt2 < itcnt; cnt2++)
				{
					dwFindCode = lpMotionInfo->MotionInfo[FoundNum[cnt]].ItemCodeList[cnt2];
					if (dwFindCode == 0xFFFF)
					{
						FoundNum2[FindCnt2++] = FoundNum[cnt];
						break;
					}
				}
			}
		}
	}
	if (FindCnt2 == 0)
	{
		if (FindCnt == 1)
			ChangeMotion(FoundNum[0], AnimDispMode);
		else
			if (FindCnt)
				ChangeMotion(FoundNum[(rand() % FindCnt)], AnimDispMode);

		if (atSkill)
			AttackSkil = atSkill;

		return NULL;
	}
	if (FindCnt2 == 1)
		ChangeMotion(FoundNum2[0], AnimDispMode);
	else
	{
		if (FindCnt2)
			ChangeMotion(FoundNum2[(rand() % FindCnt2)], AnimDispMode);
	}
	if (atSkill)
		AttackSkil = atSkill;

	return FindCnt;
}

int Unit::FindActionFromFrame(int sframe)
{
	DWORD cnt;
	DWORD compFrame;

	compFrame = sframe / 160;

	if (smMotionInfo)
	{
		for (cnt = 0; cnt < smMotionInfo->MotionCount; cnt++)
		{
			if (smMotionInfo->MotionInfo[cnt].StartFrame<compFrame && smMotionInfo->MotionInfo[cnt].EndFrame>compFrame)
				return cnt;
		}
	}

	return -1;
}

int Unit::SavePlayBuff()
{
	iPlayBuffCount = (iPlayBuffCount + 1)&PLAYBUFF_MASK;

	sPlayBuff[iPlayBuffCount].saAngle[0] = Angle.x;
	sPlayBuff[iPlayBuffCount].saAngle[1] = Angle.y;
	sPlayBuff[iPlayBuffCount].saAngle[2] = Angle.z;
	sPlayBuff[iPlayBuffCount].saAngle[3] = action;

	sPlayBuff[iPlayBuffCount].iX = pX;
	sPlayBuff[iPlayBuffCount].iY = pY;
	sPlayBuff[iPlayBuffCount].iZ = pZ;

	sPlayBuff[iPlayBuffCount].dwFrame = (MotionSelectFrame << CHAR_FRAME_SELSHIFT) | iFrame;

	if (chrAttackTarget)
		sPlayBuff[iPlayBuffCount].dwTargetSerial = chrAttackTarget->iID;
	else
		sPlayBuff[iPlayBuffCount].dwTargetSerial = NULL;

	memcpy(sPlayBuff[iPlayBuffCount].sStickItems, wStickItems, sizeof(short) * 4);

	return iPlayBuffCount;
}
int Unit::SavePlayBuff2()
{
	iPlayBuffCount = (iPlayBuffCount + 1) & PLAYBUFF_MASK;

	sPlayBuff[iPlayBuffCount].saAngle[0] = Angle.x;
	sPlayBuff[iPlayBuffCount].saAngle[1] = Angle.y;
	sPlayBuff[iPlayBuffCount].saAngle[2] = Angle.z;
	sPlayBuff[iPlayBuffCount].saAngle[3] = action;

	sPlayBuff[iPlayBuffCount].iX = pX;
	sPlayBuff[iPlayBuffCount].iY = pY;
	sPlayBuff[iPlayBuffCount].iZ = pZ;

	sPlayBuff[iPlayBuffCount].dwFrame = (MotionSelectFrame << CHAR_FRAME_SELSHIFT) | iFrame;

	sPlayBuff[iPlayBuffCount].dwTargetSerial = NULL;

	if (pcAttackTarget)
		sPlayBuff[iPlayBuffCount].dwTargetSerial = pcAttackTarget->iID;

	if (pcFocusTarget)
		sPlayBuff[iPlayBuffCount].dwTargetSerial = pcFocusTarget->iID;

	memcpy(sPlayBuff[iPlayBuffCount].sStickItems, wStickItems, sizeof(short) * 4);

	return iPlayBuffCount;
}

int Unit::ChangeMoveMode()
{
	if (MoveMode == 0)
		MoveMode = 1;
	else
		MoveMode = 0;

	if (MoveFlag)
	{
		if (MoveMode)
			SetMotionFromCode(ANIMATIONTYPE_Running);
		else
			SetMotionFromCode(ANIMATIONTYPE_Walking);
	}

	return MoveMode;
}
int Unit::CheckShootingTest(Unit *lpChrTarget)
{
	int x, y, z;
	int he;
	int cnt;

	int	SucessCnt;

	if (lpChrTarget->sCharacterData.iMonsterEffectID == snCHAR_SOUND_CASTLE_TOWER_B)
		return TRUE;

	auto sPosition = GetRadian3D(pX, pY, pZ, lpChrTarget->pX, lpChrTarget->pY, lpChrTarget->pZ);

	ShootingPosi.x = pX;
	ShootingPosi.y = pY + 34 * fONE;
	ShootingPosi.z = pZ;

	ShootingAngle.x = sPosition.iX;
	ShootingAngle.y = sPosition.iY;
	ShootingAngle.z = sPosition.iZ;

	SucessCnt = 0;

	sPosition = GetMoveLocation(0, 0, 16 * fONE, sPosition.iX, sPosition.iY, sPosition.iZ);

	for (cnt = 0; cnt < 40; cnt++)
	{
		ShootingPosi.x += sPosition.iX;
		ShootingPosi.y += sPosition.iY;
		ShootingPosi.z += sPosition.iZ;

		he = TRUE;

		if (lpStage)
			he = lpStage->CheckVecImpact(&ShootingPosi, &ShootingAngle, 16 * fONE);

		if (chrAttackTarget)
		{
			x = abs(ShootingPosi.x - lpChrTarget->pX);
			z = abs(ShootingPosi.z - lpChrTarget->pZ);
			y = abs(ShootingPosi.y - lpChrTarget->pY);

			if (x < 48 * fONE && z < 48 * fONE && y < 64 * fONE && !SucessCnt)
				SucessCnt = cnt + 2;
		}

		if (SucessCnt && SucessCnt < cnt)
			return TRUE;


		if (he == FALSE)
			return FALSE;
	}

	return TRUE;
}


extern int MatLight[2];

#define SERVER_CHAR_FRAME_STEP			320
#define SERVER_CHAR_SKIP				4

int Unit::Main()
{
	int x, z, y;
	int cnt;
	DWORD compFrame;
	int dist;
	POINT3D OldPos;
	int	frameStep, moveStep;
	smTRANS_COMMAND	smTransCommand;
	Unit *lpChar;
	int EvtFrame;
	int dm1, dm2;
	int UserSlowSpeed = 128;

	if (!Pattern || bLoading || !psModelAnimation)
		return FALSE;

	if (lpDinaPattern->UseCount <= 0)
	{
		Close();
		return FALSE;
	}

	switch (ActionPattern)
	{
	case 0:
		break;

	case 1:
		break;
	case 5:

		if (PlaySlowCount)
		{
			if (PlaySlowSpeed)
			{
				moveStep = (SERVER_CHAR_SKIP*PlaySlowSpeed) >> 8;
				frameStep = (SERVER_CHAR_FRAME_STEP*PlaySlowSpeed) >> 8;
			}
			else
			{
				moveStep = SERVER_CHAR_SKIP >> 1;
				frameStep = SERVER_CHAR_FRAME_STEP >> 1;
			}
		}
		else
		{
			moveStep = SERVER_CHAR_SKIP;
			frameStep = SERVER_CHAR_FRAME_STEP;
		}

		if (psModelAnimation->iType == ANIMATIONTYPE_Special)
		{
			iFrame += frameStep;

			if (iFrame > psModelAnimation->EndFrame * 160)
			{
				Close();
				return TRUE;
			}
			SavePlayBuff2();
			iFrameTimer += 3;
			break;
		}

		if (iSpecialType)
			moveStep = 0;

		if (sCharacterData.iMonsterEffectID == snCHAR_SOUND_BABEL)
		{
			if (sCharacterData.sHP.sMin > 0)
				SERVERMAP->dwBabelEndTime = SERVER_GAMETIME + 5000;
		}
		if (psModelAnimation->iType && psModelAnimation->iType < 0x100 && moveStep)
		{
			if (psModelAnimation->iType == ANIMATIONTYPE_Walking || psModelAnimation->iType == ANIMATIONTYPE_Running)
			{
				OldPos.x = pX;
				OldPos.y = pY;
				OldPos.z = pZ;

				if (sMoveStepCount[0])
				{
					if (sMoveStepCount[1])
						moveStep *= sMoveStepCount[1];

					for (cnt = 0; cnt < sMoveStepCount[0]; cnt++)
					{
						MoveAngle(moveStep);
						if (psModelAnimation->iType == ANIMATIONTYPE_Running)
							MoveAngle(moveStep);
					}
				}
				else
				{
					if (sCharacterData.sGlow == MONSTER_CLASS_BOSS && sCharacterData.iMonsterEffectID == snCHAR_SOUND_DARKKNIGHT)
						MoveAngle(moveStep * 2);
					else
						MoveAngle(moveStep);

					if (psModelAnimation->iType == ANIMATIONTYPE_Running)
					{
						if (sCharacterData.iMonsterEffectID == snCHAR_SOUND_GREVEN)
						{
							if (pcFocusTarget && TragetTraceMode)
								SetTargetPosi2(pcFocusTarget->sPosition.iX >> FLOATNS, pcFocusTarget->sPosition.iZ >> FLOATNS);
							MoveAngle(moveStep * 2);
							MoveAngle(moveStep * 2);
						}
						else
						{
							if (sCharacterData.iMonsterEffectID == snCHAR_SOUND_WOLVERLIN)
							{
								if (pcFocusTarget && TragetTraceMode)
									SetTargetPosi2(pcFocusTarget->sPosition.iX >> FLOATNS, pcFocusTarget->sPosition.iZ >> FLOATNS);
								MoveAngle(moveStep * 2);
							}
							else
								MoveAngle(moveStep);
						}
					}
				}

				if (psModelAnimation->iType != ANIMATIONTYPE_Walking && psModelAnimation->iType != ANIMATIONTYPE_Running)
					SetMotionFromCode(ANIMATIONTYPE_Walking);

				if (OverLapPosi || pX != OldPos.x || pZ != OldPos.z)
				{
					lpCharOverLap = CheckOtherPlayPosi(pX, pY, pZ);

					if (lpCharOverLap)
					{
						if (!OverLapPosi)
						{
							pX = OldPos.x;
							pZ = OldPos.z;
							lpCharOverLap = CheckOtherPlayPosi(pX, pY, pZ);
						}

						if (lpCharOverLap)
						{
							OverLapPosi = TRUE;
							OverLapPosi2 = FALSE;
						}
						else
						{
							OverLapPosi = FALSE;
							OverLapPosi2 = TRUE;
						}

					}
					else
					{
						OverLapPosi = FALSE;
						OverLapPosi2 = FALSE;
					}
				}
				if (!OverLapPosi)
					lpCharOverLap = 0;
			}
			else
			{
				if (psModelAnimation->iType != ANIMATIONTYPE_Idle)
					SetMotionFromCode(ANIMATIONTYPE_Idle);
			}
		}

		iFrame += frameStep;

		if (iFrame > psModelAnimation->EndFrame * 160)
		{
			if (psModelAnimation->iType == ANIMATIONTYPE_Die)
				iFrame = psModelAnimation->EndFrame * 160;
			else
			{
				if (psModelAnimation->iType == ANIMATIONTYPE_Potion && PotionLog == 1)
				{
					sCharacterData.sHP.sMin += (sCharacterData.sHP.sMax >> 1);
					if (sCharacterData.sHP.sMin > sCharacterData.sHP.sMax)
						sCharacterData.sHP.sMin = sCharacterData.sHP.sMax;
				}

				if (sUnitInfo.SkillCurse && sCharacterData.iMonsterType != MONSTERTYPE_Friendly)
				{
					if (psModelAnimation->iType == ANIMATIONTYPE_Attack)
						pcFocusTarget = 0;

					if (pcAttackTarget && psModelAnimation->iType == ANIMATIONTYPE_Skill)
					{
						pcAttackTarget->PlayHolyPower[0] = GetRandomPos(10, 20);
						pcAttackTarget->PlayHolyPower[1] = 16 * 20;
						pcAttackTarget = 0;
					}
				}

				if ((pcFocusTarget || TargetMoveCount) && psModelAnimation->iType < 0x100)
					PosBeginCount++;

				if (psModelAnimation->Repeat == TRUE)
					iFrame = (psModelAnimation->StartFrame * 160) + (iFrame - psModelAnimation->EndFrame * 160);
				else
				{
					if (psModelAnimation->iType == ANIMATIONTYPE_Flinch && !iStunTimeLeft && !PlayStopCount && SetMotionFromCode(ANIMATIONTYPE_Walking))
						TargetMoveCount = 2;
					else
						SetMotionFromCode(ANIMATIONTYPE_Idle);
					AutoMoveStep = 1;
				}
				if (PosBeginCount > 4)
				{
					x = (pX - PosBeginMove.x) >> FLOATNS;
					z = (pZ - PosBeginMove.z) >> FLOATNS;
					dist = x * x + z * z;

					PosBeginMove.x = pX;
					PosBeginMove.z = pZ;
					PosBeginCount = 0;

					if (dist < (32 * 32))
					{
						SetTargetPosi(sSpawnPosition.iX >> FLOATNS, sSpawnPosition.iZ >> FLOATNS);
						TragetTraceMode = 0;

						y = (rand() % ANGLE_90) - ANGLE_45;
						Angle.y = (Angle.y + y)&ANGCLIP;

						TargetMoveCount = 10;
						OverLapPosi2 = FALSE;

						ptNextTarget.x = 0;
						ptNextTarget.y = 0;
						ptNextTarget.z = 0;

						if (!SetMotionFromCode(ANIMATIONTYPE_Running))
							SetMotionFromCode(ANIMATIONTYPE_Walking);

						goto Skip_5;
					}
				}

				if (TargetMoveCount > 0)
				{
					TargetMoveCount--;
					if (TargetMoveCount <= 0)
						SetMotionFromCode(ANIMATIONTYPE_Idle);
				}

				if (iLureDistance && (psModelAnimation->iType == ANIMATIONTYPE_Walking || psModelAnimation->iType == ANIMATIONTYPE_Running))
				{
					x = (pX - sSpawnPosition.iX) >> FLOATNS;
					z = (pZ - sSpawnPosition.iZ) >> FLOATNS;
					dist = x * x + z * z;
					if (dist > iLureDistance)
					{
						SetTargetPosi(sSpawnPosition.iX >> FLOATNS, sSpawnPosition.iZ >> FLOATNS);
						ptNextTarget.x = ptNextTarget.z = 0;
						TargetMoveCount = 6;
						TragetTraceMode = 0;
					}
				}

				if (!TargetMoveCount && ptNextTarget.x && ptNextTarget.z)
				{
					SetTargetPosi(ptNextTarget.x >> FLOATNS, ptNextTarget.z >> FLOATNS);
					TragetTraceMode = TRUE;

					if (OverLapPosi && lpCharOverLap)
					{
						Angle.y = GetRadian2D(lpCharOverLap->pX >> FLOATNS, lpCharOverLap->pZ >> FLOATNS, pX >> FLOATNS, pZ >> FLOATNS);

						SetMotionFromCode(ANIMATIONTYPE_Walking);
						OverLapPosi2 = FALSE;
						AutoMoveStep = 0;
					}
					else
					{
						if (AutoMoveStep <= 0)
						{
							if (psModelAnimation->iType == ANIMATIONTYPE_Idle)
							{
								AutoMoveStep = sUnitInfo.IQ - 5;
								if (AutoMoveStep < 0) AutoMoveStep = 0;

								x = (pX - ptNextTarget.x) >> FLOATNS;
								z = (pZ - ptNextTarget.z) >> FLOATNS;
								dist = x * x + z * z;

								if (sUnitInfo.IQ >= 6 && dist < (64 * 8 * 64 * 8))
								{
									if (SetMotionFromCode(ANIMATIONTYPE_Running))
										AutoMoveStep <<= 2;
									else
										SetMotionFromCode(ANIMATIONTYPE_Walking);
								}
								else
									SetMotionFromCode(ANIMATIONTYPE_Walking);
							}
							else
								SetMotionFromCode(ANIMATIONTYPE_Idle);
						}
						else
						{
							SetTargetPosi2(ptNextTarget.x >> FLOATNS, ptNextTarget.z >> FLOATNS);
							AutoMoveStep--;
						}
					}

					ptNextTarget.x = 0;
					ptNextTarget.y = 0;
					ptNextTarget.z = 0;
				}

				if (sUnitInfo.iMaxPotions)
				{
					cnt = (sCharacterData.sHP.sMin * 100) / sCharacterData.sHP.sMax;
					if (cnt < 30)
					{
						if (sCharacterData.iMonsterEffectID == snCHAR_SOUND_NPC_MAGICMASTER)
						{
							smTransCommand.code = smTRANSCODE_PROCESS_SKILL2;
							smTransCommand.size = sizeof(smTRANS_COMMAND);
							smTransCommand.WParam = SKILL_PLAY_HEALING;
							smTransCommand.LParam = iID;
							smTransCommand.SParam = 0;
							smTransCommand.EParam = CHARACTERCLASS_Priestess;

							SENDPACKET(lpLinkPlayInfo, &smTransCommand);

							sCharacterData.sHP.sMin += (sCharacterData.sHP.sMax >> 2);
							if (sCharacterData.sHP.sMin > sCharacterData.sHP.sMax)
								sCharacterData.sHP.sMin = sCharacterData.sHP.sMax;
						}
						else
						{
							SetMotionFromCode(ANIMATIONTYPE_Potion);
							PotionLog = 1;
						}

						sUnitInfo.iMaxPotions--;
					}
				}

				if (dwNextMotionCode)
				{
					if (SetMotionFromCode(dwNextMotionCode) == FALSE)
						SetMotionFromCode(ANIMATIONTYPE_Idle);
					dwNextMotionCode = 0;
				}
				if (sCharacterData.iMonsterEffectID == snCHAR_SOUND_HUNGKY)
				{
					cnt = (sCharacterData.sHP.sMin * 100) / sCharacterData.sHP.sMax;
					if (cnt < 30 || AttackAnger>80)
					{
						SetMotionFromCode(ANIMATIONTYPE_Special);
						pcFocusTarget = 0;
					}
				}
				if (sCharacterData.iMonsterEffectID == snCHAR_SOUND_BEBECHICK)
				{
					cnt = (sCharacterData.sHP.sMin * 100) / sCharacterData.sHP.sMax;
					if (cnt < 30 || AttackAnger>80)
					{
						SetMotionFromCode(ANIMATIONTYPE_Special);
						pcFocusTarget = 0;
					}
				}

				if (sCharacterData.iMonsterEffectID == snCHAR_SOUND_DEADHOPT)
				{
					cnt = (sCharacterData.sHP.sMin * 100) / sCharacterData.sHP.sMax;
					if (cnt < 20 || AttackAnger > 80)
					{
						SetMotionFromCode(ANIMATIONTYPE_Special);
						pcFocusTarget = 0;
					}
				}

			}
		}
	Skip_5:
		if (iSpecialType == 2)
		{
			Angle.x = 0;
			Angle.y = 0;
			Angle.z = 0;
		}
		SavePlayBuff2();

		// ¹ÖÎï¸úËæ

		if (pcOwner && iPetID && sCharacterData.sHP.sMin > 0)
		{
			if (rsGetlpLinkChar(pcOwner, this) == FALSE)
			{
				sCharacterData.sHP.sMin = 0;
				SetMotionFromCode(ANIMATIONTYPE_Die);
			}
			else
			{
				x = (pcOwner->sPosition.iX - pX) >> FLOATNS;
				z = (pcOwner->sPosition.iZ - pZ) >> FLOATNS;
				dist = x * x + z * z;

				Map	*lpStgArea;

				lpStgArea = SERVERMAP->GetMapByXZ(pcOwner->sPosition.iX, pcOwner->sPosition.iZ);

				if (lpStgArea)
				{
					if (dist >= (500 * 500) || lpStgArea->pcStage != lpStage)
					{
						pcMap->iNumAliveUnitData--;

						SERVERMAP->DelMonsterSpawn(pcMap, this);

						lpStage = lpStgArea->pcStage;
						pcMap = lpStgArea;

						SERVERMAP->AddMonsterSpawn(pcMap, this);

						if (lpStage)
						{
							y = lpStage->GetHeight(pcOwner->sPosition.iX, pcOwner->sPosition.iZ);
							if (y < 0)
							{
								sCharacterData.sHP.sMin = 0;
								SetMotionFromCode(ANIMATIONTYPE_Die);
							}
						}

						if (lpStgArea == SERVERMAP->GetMap(MAPID_BlessCastle) || (lpStgArea->pcBaseMap && lpStgArea->pcBaseMap->iMapType == MAPTYPE_Town))
						{
							if (psModelAnimation && psModelAnimation->iType != ANIMATIONTYPE_Die)
							{
								sCharacterData.sHP.sMin = 0;
								SetMotionFromCode(ANIMATIONTYPE_Die);
							}
						}
						if (sCharacterData.sHP.sMin > 0)
						{
							pX = pcOwner->sPosition.iX;
							pY = pcOwner->sPosition.iY;
							pZ = pcOwner->sPosition.iZ;

							ptNextTarget.x = ptNextTarget.z = 0;
							TargetMoveCount = 0;
							TragetTraceMode = 0;

							pcAttackTarget = 0;
						}
					}
					else if (dist >= (300 * 300) || (!pcAttackTarget && dist >= (150 * 150)))
					{
						SetTargetPosi(pcOwner->sPosition.iX >> FLOATNS, pcOwner->sPosition.iZ >> FLOATNS);
						TargetMoveCount = 2;
						TragetTraceMode = 0;
						pcAttackTarget = 0;
						if (psModelAnimation->iType != ANIMATIONTYPE_Die && (psModelAnimation->iType >= 0x100 ||
							psModelAnimation->iType == ANIMATIONTYPE_Idle))
						{
							if (!SetMotionFromCode(ANIMATIONTYPE_Running))
								SetMotionFromCode(ANIMATIONTYPE_Walking);
						}
					}
				}
			}
		}
		if (pcOwner && CaravanSerial && CaravanMode == TRUE)
		{
			x = (pcOwner->sPosition.iX - pX) >> FLOATNS;
			z = (pcOwner->sPosition.iZ - pZ) >> FLOATNS;
			dist = x * x + z * z;

			Map	*lpStgArea;

			lpStgArea = SERVERMAP->GetMapByXZ(pcOwner->sPosition.iX, pcOwner->sPosition.iZ);

			if (lpStgArea)
			{
				if (dist >= (500 * 500) || lpStgArea->pcStage != lpStage)
				{
					EMapID iMapID = lpStgArea->pcBaseMap->iMapID;

					if (iMapID != MAPID_BlessCastle &&
						iMapID != MAPID_Bellatra &&
						iMapID != MAPID_QuestArena)
					{
						lpStage = lpStgArea->pcStage;
						pcMap = lpStgArea;

						pX = pcOwner->sPosition.iX;
						pY = pcOwner->sPosition.iY;
						pZ = pcOwner->sPosition.iZ;

						ptNextTarget.x = 0;
						ptNextTarget.z = 0;
						TargetMoveCount = 0;
						TragetTraceMode = 0;

						pcAttackTarget = 0;
					}
				}
				else if (dist >= (300 * 300) || dist >= (150 * 150))
				{
					SetTargetPosi(pcOwner->sPosition.iX >> FLOATNS, pcOwner->sPosition.iZ >> FLOATNS);
					TargetMoveCount = 2;
					TragetTraceMode = 0;
					pcAttackTarget = 0;
					if (psModelAnimation->iType >= 0x100 || psModelAnimation->iType == ANIMATIONTYPE_Idle)
					{
						if (!SetMotionFromCode(ANIMATIONTYPE_Running))
							SetMotionFromCode(ANIMATIONTYPE_Walking);
					}
				}
			}
		}

		if (lExclusiveTargetID)
		{
			switch (sCharacterData.iMonsterEffectID)
			{
			case snCHAR_SOUND_NPC_SKILLMASTER:
			case snCHAR_SOUND_NPC_MAGICMASTER:
				if (sCharacterData.sHP.sMin <= (sCharacterData.sHP.sMax >> 4))
				{
					sCharacterData.sHP.sMin = (sCharacterData.sHP.sMax >> 4);
					pcFocusTarget = 0;
					pcAttackTarget = 0;
					SetMotionFromCode(ANIMATIONTYPE_Idle);
					ActionPattern = 12;
					sSpawnPosition.iX = pX;
					sSpawnPosition.iY = pY;
					sSpawnPosition.iZ = pZ;
					iLureDistance = 256 * 256;
					if (lpLinkPlayInfo && lpLinkPlayInfo->iID == lExclusiveTargetID)
						rsProcessQuest(lpLinkPlayInfo, this, SIN_QUEST_CODE_CHANGEJOB4, iID);
					lpChar = SERVERUNIT->GetPetUnit(this);
					if (lpChar)
					{
						lpChar->SetMotionFromCode(ANIMATIONTYPE_Die);
						lpChar->sCharacterData.sHP.sMin = 0;
					}
				}
				else
				{
					if (sCharacterData.iMonsterEffectID == snCHAR_SOUND_NPC_MAGICMASTER)
					{
						if ((rand() % 100) < 3 && psModelAnimation->iType != ANIMATIONTYPE_Skill && psModelAnimation->iType != ANIMATIONTYPE_Potion)
						{
							if (lpLinkPlayInfo)
							{
								x = (pX - lpLinkPlayInfo->sPosition.iX) >> FLOATNS;
								z = (pZ - lpLinkPlayInfo->sPosition.iZ) >> FLOATNS;
								dist = x * x + z * z;
								if (dist < (300 * 300))
								{
									pX = QUEST_ARENA_NPC_POS_X + ((rand() % 600) - 300)*fONE;
									pZ = QUEST_ARENA_NPC_POS_Z + ((rand() % 600) - 300)*fONE;
								}
							}
						}
					}
				}
				break;

			case snCHAR_SOUND_FURY:
				if (sCharacterData.sHP.sMin <= 0 && !sUnitInfo.iMaxPotions && sCharacterData.sHP.sMax > 1)
				{
					if (lpLinkPlayInfo && lpLinkPlayInfo->iID == lExclusiveTargetID)
					{
						rsProcessQuest(lpLinkPlayInfo, this, HAQUEST_CODE_FURYOFPHANTOM, iID);
						sCharacterData.sHP.sMax = 1;
					}
				}
				break;
			}
		}

		if (pcAttackTarget)
		{
			if (sUnitInfo.SkillCurse && sCharacterData.iMonsterType != MONSTERTYPE_Friendly &&
				pcAttackTarget->sCharacterData.iMonsterType != MONSTERTYPE_Friendly)
			{
				if (psModelAnimation->iType < 0x100)
				{
					TargetMoveCount = 1;
					AutoMoveStep = 1;
					pcAttackTarget = 0;
				}
			}
			else if (pcAttackTarget->bActive && !iStunTimeLeft && !PlayStopCount)
			{
				dist = sCharacterData.iAttackRange + 32;
				if (dist < 80)
					dist = 80;

				if (psModelAnimation->iType != ANIMATIONTYPE_Flinch && psModelAnimation->iType != ANIMATIONTYPE_Die && psModelAnimation->iType != ANIMATIONTYPE_Potion)
				{
					if (psModelAnimation->iType != ANIMATIONTYPE_Attack && psModelAnimation->iType != ANIMATIONTYPE_Skill && psModelAnimation->iType != ANIMATIONTYPE_Die)
					{
						cnt = GetDistanceDbl(pX, pZ, pcAttackTarget->pX, pcAttackTarget->pZ);

						dist = dist >> FLOATNS;
						dist *= dist;

						if (cnt < dist && abs(pY - pcAttackTarget->pY) < 64 * fONE)
						{
							PosBeginMove.x = 0;
							PosBeginMove.z = 0;
							PosBeginCount = 0;

							dwLastActiveTime = SERVER_GAMETIME;

							SetMotionFromCode(ANIMATIONTYPE_Attack);

							if (sUnitInfo.SkillRating > 0 && psModelAnimation->iType == ANIMATIONTYPE_Attack)
							{
								if ((rand() % 100) < sUnitInfo.SkillRating)
									SetMotionFromCode(ANIMATIONTYPE_Skill);
							}

							Angle.y = GetRadian2D(pX, pZ, pcAttackTarget->pX, pcAttackTarget->pZ);
							AttackX = pcAttackTarget->pX;
							AttackY = pcAttackTarget->pY;
							AttackZ = pcAttackTarget->pZ;

						}
						else
						{
							if (cnt > DIST_TRANSLEVEL_LOW)
								pcAttackTarget = 0;
						}
					}
				}

				if (sCharacterData.iMonsterType != MONSTERTYPE_Friendly)
				{
					if (iFrameTimer == 80 && sCharacterData.iMonsterEffectID == snCHAR_SOUND_BABEL)
					{
						iAreaDamageArea = sUnitInfo.SkillRange*sUnitInfo.SkillRange;

						sCharacterData.sHP.sMin += rsGetMonsterLifeRegen(this);

						if (sCharacterData.sHP.sMin > sCharacterData.sHP.sMax || sCharacterData.sHP.sMin < 0)
							sCharacterData.sHP.sMin = sCharacterData.sHP.sMax;
					}
				}

				if (iFrameTimer == 40 && pcAttackTarget)
				{
					if (psModelAnimation->iType == ANIMATIONTYPE_Attack || psModelAnimation->iType == ANIMATIONTYPE_Skill)
					{
						AttackUserFlag = TRUE;
						AttackAnger++;
						cnt = sinGetPVPAccuracy(sCharacterData.iLevel,
							sCharacterData.iAttackRating,
							pcAttackTarget->sCharacterData.iLevel,
							pcAttackTarget->sCharacterData.iDefenseRating);
						if ((rand() % 100) < cnt && pcAttackTarget->sCharacterData.sHP.sMin > 0)
						{
							if (!pcAttackTarget->pcFocusTarget)
								pcAttackTarget->pcAttackTarget = this;
							else
							{
								dist = GetDistanceDbl(pX, pZ, pcAttackTarget->pX, pcAttackTarget->pZ);
								if (GetDistanceDbl(pX, pZ, pcAttackTarget->pcFocusTarget->sPosition.iX, pcAttackTarget->pcFocusTarget->sPosition.iZ) > dist)
								{
									pcAttackTarget->pcAttackTarget = this;
									pcAttackTarget->pcFocusTarget = 0;
								}
							}

							if (psModelAnimation->iType == ANIMATIONTYPE_Skill && sCharacterData.iMinDamage)
							{
								cnt = GetRandomPos(sUnitInfo.SkillDamage[0], sUnitInfo.SkillDamage[1]);

								switch (sCharacterData.iMonsterEffectID)
								{
								case snCHAR_SOUND_GUARDIAN_SAINT:
									rsSkillDamage_AroundMonster(this);
									cnt = 0;
									break;
								}
							}
							else
								cnt = GetRandomPos(sCharacterData.iMinDamage, sCharacterData.iMaxDamage);

							if (sCharacterData.iMonsterEffectID == snCHAR_SOUND_BABEL || sCharacterData.iMonsterEffectID == snCHAR_SOUND_CHAOSCARA || sCharacterData.iMonsterEffectID == snCHAR_SOUND_DEATHKNIGHT || sCharacterData.iMonsterEffectID == snCHAR_SOUND_MOKOVA || sCharacterData.iMonsterEffectID == snCHAR_SOUND_KELVEZU || sCharacterData.iMonsterEffectID == snCHAR_SOUND_MOKOVA || sCharacterData.iMonsterEffectID == snCHAR_SOUND_DEVILSHY || sCharacterData.iMonsterEffectID == smCHAR_SOUND_TULLA)
							{
								cnt *= 8;
								if (sCharacterData.iMonsterEffectID == snCHAR_SOUND_KELVEZU)
								{
									pcAttackTarget->sCharacterData.sHP.sMin = 0;
									cnt = 1;
								}
							}

							if (pcAttackTarget)
								cnt -= (cnt * pcAttackTarget->sCharacterData.iAbsorbRating) / 100;
							else
								cnt = 0;

							if (cnt > 0)
							{
								pcAttackTarget->sCharacterData.sHP.sMin -= cnt;

								if (sCharacterData.iMonsterEffectID == snCHAR_SOUND_WEB)
								{
									if (pcAttackTarget->sCharacterData.iMonsterEffectID != snCHAR_SOUND_KELVEZU)
										pcAttackTarget->PlaySlowCount = -36;
								}

								if (pcAttackTarget->sCharacterData.sHP.sMin <= 0)
								{
									pcAttackTarget->sCharacterData.sHP.sMin = 0;
									pcAttackTarget->SetMotionFromCode(ANIMATIONTYPE_Die);
									if (pcOwner && pcOwner->iID && pcOwner->iID == sCharacterData.iOwnerID)
									{
										pcAttackTarget->pcKillerData = pcOwner;
										pcAttackTarget->pcBellatraKiller = this;
									}
									else
									{
										if (pcOwner)
										{
											sCharacterData.sHP.sMin = 0;
											SetMotionFromCode(ANIMATIONTYPE_Die);
										}
										else
											pcAttackTarget = 0;
									}
								}
								else
								{
									if (pcAttackTarget->psModelAnimation->iType < 0x100)
										pcAttackTarget->SetMotionFromCode(ANIMATIONTYPE_Flinch);
								}
							}
						}
					}
				}
			}
			else
				SetNextTarget(0, 0, 0);

			if (pcAttackTarget && (!pcAttackTarget->bActive || pcAttackTarget->sCharacterData.sHP.sMin <= 0))
			{
				pcAttackTarget = 0;
				if (psModelAnimation->iType < 0x100)
				{
					TargetMoveCount = 1;
					AutoMoveStep = 1;
				}
			}

			if (sCharacterData.iMonsterEffectID == snCHAR_SOUND_DEATHKNIGHT && pcAttackTarget)
			{
				if (GetDistanceDbl(pX, pZ, pcAttackTarget->pX, pcAttackTarget->pZ) > 120 * 120)
				{
					pcAttackTarget = 0;
					SetNextTarget(0, 0, 0);
				}
			}
		}

		cnt = TRUE;

		switch (sCharacterData.iMonsterEffectID)
		{
		case MONSTEREFFECTID_VAMPRICMACHINE:
			if (rsGetMonCountFlag(this) > 3)
				cnt = FALSE;
			break;

		case snCHAR_SOUND_MYSTIC:
		case smCHAR_SOUND_SEALCRASHER:
			if (psModelAnimation->iType == ANIMATIONTYPE_Die && iFrameTimer < 16)
			{
				iAreaDamageArea = sUnitInfo.SkillRange*sUnitInfo.SkillRange;
				AttackUserFlag = TRUE;
				iFrameTimer = 16;
			}
			if (psModelAnimation->iType != ANIMATIONTYPE_Die)
			{
				if (Counter > 16 * 60 * 2)
				{
					sCharacterData.sHP.sMin = 0;
					SetMotionFromCode(ANIMATIONTYPE_Die);
					iAreaDamageArea = sUnitInfo.SkillRange*sUnitInfo.SkillRange;
					AttackUserFlag = TRUE;
					iFrameTimer = 16;
				}
			}
			if (pcAttackTarget && psModelAnimation->iType == ANIMATIONTYPE_Die)
			{
				if (iFrameTimer == 16 && pcAttackTarget->psModelAnimation->iType != ANIMATIONTYPE_Die && pcAttackTarget->sCharacterData.sHP.sMin > 0)
				{
					pcAttackTarget->sCharacterData.sHP.sMin -= GetRandomPos(sUnitInfo.SkillDamage[0], sUnitInfo.SkillDamage[1]) * 2;
					if (pcAttackTarget->sCharacterData.sHP.sMin <= 0)
					{
						pcAttackTarget->sCharacterData.sHP.sMin = 0;
						pcAttackTarget->SetMotionFromCode(ANIMATIONTYPE_Die);
					}
				}
				pcAttackTarget = 0;
			}
			break;

		case snCHAR_SOUND_CHAOSCARA:
		case snCHAR_SOUND_DEVILSHY:
			if (psModelAnimation->iType == ANIMATIONTYPE_Skill && psModelAnimation->KeyCode != 'J')
			{
				sUnitInfo.SkillRangeRect.left = 0;
				sUnitInfo.SkillRangeRect.right = 0;
				sUnitInfo.SkillRangeRect.top = 0;
				sUnitInfo.SkillRangeRect.bottom = 0;
			}
			break;
		}

		if (!pcAttackTarget && pcFocusTarget && cnt)
		{
			if (!iStunTimeLeft && !PlayStopCount)
			{
				dist = sCharacterData.iAttackRange;

				if (psModelAnimation->iType != ANIMATIONTYPE_Flinch &&
					psModelAnimation->iType != ANIMATIONTYPE_Die &&
					psModelAnimation->iType != ANIMATIONTYPE_Potion && dist >= 0)
				{
					if (PlayAttackFromPosi(pcFocusTarget->sPosition.iX, pcFocusTarget->sPosition.iY, pcFocusTarget->sPosition.iZ, dist) == TRUE)
					{
						PosBeginMove.x = 0;
						PosBeginMove.z = 0;
						PosBeginCount = 0;

						dwLastActiveTime = SERVER_GAMETIME;

						if (sUnitInfo.SkillRating > 0 && psModelAnimation->iType == ANIMATIONTYPE_Attack)
						{
							if ((rand() % 100) < sUnitInfo.SkillRating)
							{
								if (sCharacterData.iMonsterEffectID == snCHAR_SOUND_NPC_MAGICMASTER && (rand() % 100) < 20)
								{
									SetMotionFromCode(ANIMATIONTYPE_Potion);
									PotionLog = 2;
								}
								else if (SetMotionFromCode(ANIMATIONTYPE_Skill) > 0)
								{
									if (sUnitInfo.SkillCurse)
									{
										switch (sUnitInfo.SkillCurse)
										{
										case 102:
											lpChar = rsFindAroundMonster(this, 200);
											if (lpChar)
											{
												pcAttackTarget = lpChar;
												pcFocusTarget = 0;
												Angle.y = GetRadian2D(pX, pZ, pcAttackTarget->pX, pcAttackTarget->pZ);
											}
											else
											{
												if (SetMotionFromCode(ANIMATIONTYPE_Attack) == FALSE)
													SetMotionFromCode(ANIMATIONTYPE_Idle);
											}
											break;

										case 103:
											pcFocusTarget->dwCurse_Attack_Time = SERVER_GAMETIME + SUCCUBUS_CURSE_TIME * 1000;
											pcFocusTarget->dwCurse_Attack_Param = GetRandomPos(10, 15);
											break;

										case 101:
											pcFocusTarget->dwCurse_Defence_Time = SERVER_GAMETIME + SUCCUBUS_CURSE_TIME * 1000;
											pcFocusTarget->dwCurse_Defence_Param = GetRandomPos(2, 6);

											if (sCharacterData.iMonsterEffectID == snCHAR_SOUND_MYSTIC || sCharacterData.iMonsterEffectID == smCHAR_SOUND_SEALCRASHER)
												pcFocusTarget->dwCurse_Defence_Param = GetRandomPos(10, 16);

											break;

										}
									}

									if (sUnitInfo.SkillRange > 0)
									{
										iAreaDamageArea = 0;

										if (sUnitInfo.SkillDistance)
										{
											auto sPosition = GetMoveLocation(0, 0, sUnitInfo.SkillDistance*fONE, 0, Angle.y, 0);
											x = pX + sPosition.iX;
											z = pZ + sPosition.iZ;

											dist = sUnitInfo.SkillRange << FLOATNS;

											sUnitInfo.SkillRangeRect.left = x - dist;
											sUnitInfo.SkillRangeRect.right = x + dist;
											sUnitInfo.SkillRangeRect.top = z - dist;
											sUnitInfo.SkillRangeRect.bottom = z + dist;
										}
									}

									switch (sCharacterData.iMonsterEffectID)
									{
									case snCHAR_SOUND_RATOO:
										rsSkillMonster_AroundMonster(this, 200);
										break;
									case snCHAR_SOUND_NPC_SKILLMASTER:
										cnt = rand() % 100;
										if (cnt < 3 && !SERVERUNIT->GetPetUnit(this) && lpLinkPlayInfo)
										{
											if ((cnt & 1) == 0)
											{
												lpChar = SERVERMAP->CreateUnitByID(SKILLPLAYID_T44, pX, pY, pZ, lpLinkPlayInfo, this);
												if (lpChar)
												{
													lpChar->sCharacterData.sSize = fONE + 5 * 15;
													lpChar->sMoveStepCount[0] = 1;
													lpChar->sMoveStepCount[1] = 2;
												}
											}
											else
											{
												lpChar = SERVERMAP->CreateUnitByID(SKILLPLAYID_T41, pX, pY, pZ, lpLinkPlayInfo, this);

												if (lpChar)
												{
													lpChar->sCharacterData.sSize = (fONE / 2) + 5 * 12;
													lpChar->sMoveStepCount[0] = 1;
													lpChar->sMoveStepCount[1] = 2;
												}
											}
										}
										break;
									case snCHAR_SOUND_NPC_MAGICMASTER:
										cnt = rand() % 100;
										if (cnt < 3 && !SERVERUNIT->GetPetUnit(this) && lpLinkPlayInfo)
										{
											lpChar = SERVERMAP->CreateUnitByID(SKILLPLAYID_T41, pX, pY, pZ, lpLinkPlayInfo, this);
											if (lpChar)
											{
												lpChar->sMoveStepCount[0] = 1;
												lpChar->sMoveStepCount[1] = 2;
											}
										}
										break;
									}
								}
							}
						}
					}
				}

				EvtFrame = 0;
				if (sCharacterData.iMonsterEffectID == snCHAR_SOUND_BABEL)
				{
					if (iFrameTimer == 40 || iFrameTimer == 80)
						EvtFrame = 1;
				}


				if ((!EvtFrame && iFrameTimer == 40) || EvtFrame)
				{
					if (psModelAnimation->iType == ANIMATIONTYPE_Attack && rsProcessAttack_SkillHolyReflection(pcFocusTarget, this) == TRUE)
					{
						if (sCharacterData.iMonsterEffectID == MONSTEREFFECTID_VAMPRICMACHINE)
						{
							cnt = 0;
							rsOpenSubMonster(this, snCHAR_SOUND_VAMPRICBEE, pX, pY, pZ, 4);
						}
						else
						{
							if (sCharacterData.iMonsterEffectID == snCHAR_SOUND_BABEL && (rand() % 100) < 60)
							{
								rsSendRangeDamage(this, pcFocusTarget, 100, fONE / 2);

								x = (pcFocusTarget->sPosition.iX - pX) >> FLOATNS;
								z = (pcFocusTarget->sPosition.iZ - pZ) >> FLOATNS;
								dist = x * x + z * z;
								if (dist > (200 * 200))
								{
									dm1 = sCharacterData.iMinDamage;
									dm2 = sCharacterData.iMaxDamage;

									sCharacterData.iMinDamage = (sCharacterData.iMinDamage * 70) / 100;
									sCharacterData.iMaxDamage = (sCharacterData.iMaxDamage * 70) / 100;
									cnt = SendTransAttack(0, pcFocusTarget, 0);

									sCharacterData.iMinDamage = dm1;
									sCharacterData.iMaxDamage = dm2;
								}
								else
									cnt = SendTransAttack(0, pcFocusTarget, 0);

							}
							else
								cnt = SendTransAttack(0, pcFocusTarget, 0);
						}

						if (cnt)
						{
							pcFocusTarget->Send_AttackCount++;
							pcFocusTarget->Send_AttackDamage += cnt;

							if (sCharacterData.sGlow == MONSTER_CLASS_HAMMER && pcFocusTarget->cdwTime_BigHead == NULL)
							{
								if (dwEventAttackParam != pcFocusTarget->iID)
								{
									EventAttackCount = 0;
									dwEventAttackParam = pcFocusTarget->iID;
								}

								EventAttackCount++;

								if (EventAttackCount >= 10)
								{
									rsSendBigHeadToClient(pcFocusTarget, 60 * 10, (rand() % 6) + 1);

									if (sUnitInfo.UseEventModel && sCharacterData.Player.szHeadModel[1])
									{
										Close();

										lstrcpy(sCharacterData.Player.szBodyModel, sCharacterData.Player.szHeadModel + 1);
										SetLoadPattern(sCharacterData.Player.szBodyModel);
										sCharacterData.bUpdateInfo[0]++;
										SetMotionFromCode(ANIMATIONTYPE_Idle);
									}

									sCharacterData.sGlow = MONSTER_CLASS_NORMAL;
									sUnitInfo.UseEventModel = 0;
								}

								TRANS_CHATMESSAGE	TransChatMessage;
								wsprintf(TransChatMessage.szMessage, "%s: %d ", sCharacterData.szName, EventAttackCount);
								TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
								TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
								TransChatMessage.dwIP = 0;
								TransChatMessage.dwObjectSerial = iID;

								rsSendCommandUser2(pcFocusTarget, (smTRANS_COMMAND *)&TransChatMessage);
							}
						}

						AttackUserFlag = TRUE;
						AttackAnger++;

						if (pcFocusTarget->BadPlayer == 4)
						{
							if ((sCharacterData.iLevel + 6) > pcFocusTarget->sCharacterData.iLevel && (rand() % 100) > 92)
							{
								smTransCommand.code = smTRANSCODE_DEAD_PLAYER;
								smTransCommand.size = sizeof(smTRANS_COMMAND);
								smTransCommand.WParam = 0;
								smTransCommand.LParam = 0;
								smTransCommand.SParam = 0;
								smTransCommand.EParam = 0;

								SENDPACKET(pcFocusTarget, &smTransCommand);

								pcFocusTarget->BadPlayer = 2;
							}
						}
					}
				}

				EvtFrame = 32;

				if (sCharacterData.iMonsterEffectID == snCHAR_SOUND_BABEL || sCharacterData.iMonsterEffectID == snCHAR_SOUND_DEATHKNIGHT)
				{
					EvtFrame = 120;
					if (iFrameTimer == EvtFrame)
					{
						sCharacterData.sHP.sMin += rsGetMonsterLifeRegen(this);

						if (sCharacterData.sHP.sMin > sCharacterData.sHP.sMax || sCharacterData.sHP.sMin < 0)
							sCharacterData.sHP.sMin = sCharacterData.sHP.sMax;

					}
				}

				if (iFrameTimer == EvtFrame)
				{
					if (psModelAnimation->iType == ANIMATIONTYPE_Skill)
					{
						if (sCharacterData.iMonsterEffectID != snCHAR_SOUND_MYSTIC && sCharacterData.iMonsterEffectID != smCHAR_SOUND_SEALCRASHER)
						{
							iAreaDamageArea = sUnitInfo.SkillRange*sUnitInfo.SkillRange;
							if (!iAreaDamageArea && pcFocusTarget)
								rsSendTransSkillAttack(this, pcFocusTarget);
							AttackUserFlag = TRUE;
						}
					}
				}
			}
			else
				SetNextTarget(0, 0, 0);
		}

		if (PlaySlowCount > 0)
			PlaySlowCount--;

		if (PlaySlowCount < 0)
			PlaySlowCount++;

		if (iStunTimeLeft > 0)
			iStunTimeLeft--;

		if (PlayStopCount > 0)
			PlayStopCount--;

		if (PlayHolyMind[1] > 0)
			PlayHolyMind[1]--;

		if (PlayHolyPower[1] > 0)
			PlayHolyPower[1]--;

		if (PlayPoison[1] > 0)
		{
			PlayPoison[1]--;
			if ((Counter & 0xF) == 0)
			{
				if (sCharacterData.sHP.sMin > 0 && psModelAnimation->iType != ANIMATIONTYPE_Die)
				{
					sCharacterData.sHP.sMin -= PlayPoison[0];

					if (sCharacterData.sHP.sMin < 1)
					{
						sCharacterData.sHP.sMin = 1;
						PlayPoison[1] = 0;
					}
				}
			}
		}
		if (PlayFire[1] > 0)
		{
			PlayFire[1] --;
			if ((Counter & 0xF) == 0)
			{
				if (sCharacterData.sHP.sMin > 0 && psModelAnimation->iType != ANIMATIONTYPE_Die)
				{
					sCharacterData.sHP.sMin -= PlayFire[0];

					if (sCharacterData.sHP.sMin < 1)
					{
						sCharacterData.sHP.sMin = 0;
						PlayFire[1] = 0;
						SetMotionFromCode(ANIMATIONTYPE_Die);
					}
				}
			}
		}

		if (PlayHolyIncantation[1] > 0)
		{
			PlayHolyIncantation[1]--;
			if (PlayHolyIncantation[1] == 0 && sCharacterData.iMonsterType == MONSTERTYPE_Friendly)
			{
				sCharacterData.iMonsterType = (EMonsterType)PlayHolyIncantation[0];
				sCharacterData.bUpdateInfo[0]++;
				pcOwner = nullptr;
			}
		}

		if (iHPBlocks)
		{
			if (sHPBlocks.sMin > 0)
			{
				cnt = (sCharacterData.sHP.sMin * 100) / sCharacterData.sHP.sMax;
				if (cnt <= 10)
				{
					sHPBlocks.sMin--;
					sCharacterData.sHP.sMin = sCharacterData.sHP.sMax;

					if (sCharacterData.iMonsterEffectID == snCHAR_SOUND_KELVEZU && (sHPBlocks.sMin & 0x1) == 0)
					{
						rsOpenSubMonster(this, snCHAR_SOUND_CHAOSCARA, pX + ((rand() % (200 * fONE)) - 100 * fONE), 0, pZ + ((rand() % (200 * fONE)) - 100 * fONE), 8);
						rsOpenSubMonster(this, snCHAR_SOUND_CHAOSCARA, pX + ((rand() % (200 * fONE)) - 100 * fONE), 0, pZ + ((rand() % (200 * fONE)) - 100 * fONE), 8);
					}
					else if (sCharacterData.iMonsterEffectID == snCHAR_SOUND_MOKOVA && (sHPBlocks.sMin & 0x1) == 0)
					{
						rsOpenSubMonster(this, snCHAR_SOUND_DARKGUARD, pX + ((rand() % (200 * fONE)) - 100 * fONE), 0, pZ + ((rand() % (200 * fONE)) - 100 * fONE), 8);
						rsOpenSubMonster(this, snCHAR_SOUND_DARKGUARD, pX + ((rand() % (200 * fONE)) - 100 * fONE), 0, pZ + ((rand() % (200 * fONE)) - 100 * fONE), 8);
					}

				}
			}

			cnt = (sCharacterData.sHP.sMin * 100) / sCharacterData.sHP.sMax;
			sVirtualHP.sMin = sHPBlocks.sMin * 100;
			sVirtualHP.sMin += cnt;
			sVirtualHP.sMax = (sHPBlocks.sMax + 1) * 100;

			if (sVirtualHP.sMin <= 0 && sCharacterData.sHP.sMin > 0)
				sVirtualHP.sMin = 1;

			if (sVirtualHP.sMin > sVirtualHP.sMax)
				sVirtualHP.sMin = sVirtualHP.sMax;

		}

		iFrameTimer += 3;
		break;

	case 10:
	case 11:	//NPC
		if (psModelAnimation->iType && psModelAnimation->iType < 0x100)
		{
			if (psModelAnimation->iType == ANIMATIONTYPE_Walking)
			{
				MoveAngle(SERVER_CHAR_SKIP);
				if (psModelAnimation->iType != ANIMATIONTYPE_Walking)
					SetMotionFromCode(ANIMATIONTYPE_Walking);
			}
			else
			{
				if (psModelAnimation->iType != ANIMATIONTYPE_Idle)
					SetMotionFromCode(ANIMATIONTYPE_Idle);
			}

		}

		iFrame += SERVER_CHAR_FRAME_STEP;

		if (iFrame > psModelAnimation->EndFrame * 160)
		{
			if (psModelAnimation->iType == ANIMATIONTYPE_Die)
				iFrame = psModelAnimation->EndFrame * 160;
			else
			{
				if (psModelAnimation->Repeat == TRUE)
					iFrame = (psModelAnimation->StartFrame * 160) + (iFrame - psModelAnimation->EndFrame * 160);
				else
					SetMotionFromCode(ANIMATIONTYPE_Idle);

				if (psModelAnimation->iType == ANIMATIONTYPE_Idle)
				{
					cnt = rand() % ANGCLIP;
					if (((cnt >> 2) & 3) == 0)
					{
						if (ActionPattern == 10)
						{
							if (!SetMotionFromCode(CHRMOTION_STATE_SOMETIME))
							{
								Angle.y = cnt & ANGCLIP;
								SetMotionFromCode(ANIMATIONTYPE_Walking);
							}
						}
						else
						{
							if (!SetMotionFromCode(TRUE))
							{
								Angle.y = cnt & ANGCLIP;
								SetMotionFromCode(ANIMATIONTYPE_Walking);
							}
						}
					}
					else
					{
						Angle.y = cnt & ANGCLIP;
						SetMotionFromCode(ANIMATIONTYPE_Walking);
					}

					if (psModelAnimation->iType == ANIMATIONTYPE_Walking)
					{
						x = (pX - sSpawnPosition.iX) >> FLOATNS;
						z = (pZ - sSpawnPosition.iZ) >> FLOATNS;
						dist = x * x + z * z;
						if (dist > iLureDistance)
							SetTargetPosi(sSpawnPosition.iX >> FLOATNS, sSpawnPosition.iZ >> FLOATNS);
					}
				}
				else SetMotionFromCode(ANIMATIONTYPE_Idle);

				if (OverLapPosi && lpCharOverLap)
				{
					Angle.y = GetRadian2D(lpCharOverLap->pX >> FLOATNS, lpCharOverLap->pZ >> FLOATNS, pX >> FLOATNS, pZ >> FLOATNS);

					SetMotionFromCode(ANIMATIONTYPE_Walking);
					OverLapPosi2 = FALSE;
				}
			}
		}
		SavePlayBuff();
		iFrameTimer += 3;
		break;

	case 12:	//NPC
		if (smMotionInfo && smMotionInfo->NpcMotionRate[CHRMOTION_EXT])
		{
			if (psModelAnimation->iType == ANIMATIONTYPE_Special)
			{
				iFrame += SERVER_CHAR_FRAME_STEP;
				if (iFrame > psModelAnimation->EndFrame * 160)
				{
					Close();
					return TRUE;
				}
				SavePlayBuff();
				iFrameTimer += 3;
				break;
			}

			int TalkCnt = 0;
			if (psModelAnimation->iType == ANIMATIONTYPE_Walking)
			{
				x = pX; z = pZ;
				MoveAngle(SERVER_CHAR_SKIP);

				if (x == pX && z == pZ)
				{
					TalkCnt = rand() % 100;
					TalkCnt = smMotionInfo->NpcMotionRateCnt[TalkCnt];

					if (TalkCnt == action && smMotionInfo->MotionInfo[TalkCnt].iType == ANIMATIONTYPE_Walking)
					{
						x = (pX - sSpawnPosition.iX) >> FLOATNS;
						z = (pZ - sSpawnPosition.iZ) >> FLOATNS;
						dist = x * x + z * z;

						if (dist > iLureDistance)
							SetTargetPosi(sSpawnPosition.iX >> FLOATNS, sSpawnPosition.iZ >> FLOATNS);
					}
					else
					{
						iFrame = psModelAnimation->EndFrame * 160;
						psModelAnimation->iType = ANIMATIONTYPE_Idle;
					}
				}
			}

			iFrame += SERVER_CHAR_FRAME_STEP;

			if (iFrame > psModelAnimation->EndFrame * 160)
			{
				if (psModelAnimation->iType == ANIMATIONTYPE_Walking)
					iFrame = (psModelAnimation->StartFrame * 160) + (iFrame - psModelAnimation->EndFrame * 160);
				else if (sCharacterData.iMonsterEffectID != snCHAR_SOUND_FURY)
				{
					if (TalkCnt == 0)
						TalkCnt = rand() % 100;

					ChangeMotion(smMotionInfo->NpcMotionRateCnt[TalkCnt]);
					if (psModelAnimation->iType == ANIMATIONTYPE_Walking)
					{
						x = (pX - sSpawnPosition.iX) >> FLOATNS;
						z = (pZ - sSpawnPosition.iZ) >> FLOATNS;
						dist = x * x + z * z;

						if (dist > iLureDistance)
							SetTargetPosi(sSpawnPosition.iX >> FLOATNS, sSpawnPosition.iZ >> FLOATNS);
					}
					else
						Angle.y = rand() % ANGCLIP;
				}
				else
					SetMotionFromCode(ANIMATIONTYPE_Idle);
			}
		}
		else
		{
			if (psModelAnimation->iType == ANIMATIONTYPE_Special)
			{
				iFrame += SERVER_CHAR_FRAME_STEP;

				if (iFrame > psModelAnimation->EndFrame * 160)
				{
					Close();
					return TRUE;
				}
				SavePlayBuff();
				iFrameTimer += 3;
				break;
			}


			if (psModelAnimation->iType && psModelAnimation->iType < 0x100)
			{
				if (psModelAnimation->iType == ANIMATIONTYPE_Walking)
				{
					x = pX; z = pZ;

					MoveAngle(SERVER_CHAR_SKIP);

					if (x == pX && z == pZ)
						Angle.y = rand() % ANGCLIP;

					if (psModelAnimation->iType != ANIMATIONTYPE_Walking)
						SetMotionFromCode(ANIMATIONTYPE_Walking);
				}
				else
				{
					if (psModelAnimation->iType != ANIMATIONTYPE_Idle)
						SetMotionFromCode(ANIMATIONTYPE_Idle);
				}
			}

			iFrame += SERVER_CHAR_FRAME_STEP;

			if (iFrame > psModelAnimation->EndFrame * 160)
			{
				if (psModelAnimation->iType == ANIMATIONTYPE_Die)
					iFrame = psModelAnimation->EndFrame * 160;
				else
				{

					if (psModelAnimation->Repeat == TRUE)
						iFrame = (psModelAnimation->StartFrame * 160) + (iFrame - psModelAnimation->EndFrame * 160);
					else
						SetMotionFromCode(ANIMATIONTYPE_Idle);

					if (psModelAnimation->iType == ANIMATIONTYPE_Idle && sCharacterData.iMonsterEffectID != snCHAR_SOUND_FURY)
					{
						cnt = rand() % ANGCLIP;
						if (((cnt >> 2) & 3) == 0)
						{
							if (!SetMotionFromCode(TRUE))
							{
								if (MoveSpeed) Angle.y = cnt & ANGCLIP;

								if (iLureDistance)
									SetMotionFromCode(ANIMATIONTYPE_Walking);
								else
									SetMotionFromCode(ANIMATIONTYPE_Idle);
							}
						}
						else
							SetMotionFromCode(ANIMATIONTYPE_Idle);

						if (psModelAnimation->iType == ANIMATIONTYPE_Walking)
						{
							x = (pX - sSpawnPosition.iX) >> FLOATNS;
							z = (pZ - sSpawnPosition.iZ) >> FLOATNS;
							dist = x * x + z * z;

							if (dist > iLureDistance)
								SetTargetPosi(sSpawnPosition.iX >> FLOATNS, sSpawnPosition.iZ >> FLOATNS);
						}
					}
					else SetMotionFromCode(ANIMATIONTYPE_Idle);
				}
			}
		}

		SavePlayBuff();
		iFrameTimer += 3;
		break;

	case 99:

		break;

	case 101:

		iFrame += 80;
		compFrame = iFrame / 160;

		if (compFrame >= psModelAnimation->EndFrame)
			SetMotionFromCode(ANIMATIONTYPE_Idle);

		if (TalkFrame)
		{
			if (TalkFrame >= lpTalkMotionInfo->EndFrame * 160)
				TalkFrame = 0;
			else
				TalkFrame += 80;
		}
		break;

	}

	if (DisplayAlpha < 0)
	{
		DisplayAlpha += 4;
		if (DisplayAlpha > 0) DisplayAlpha = 0;
	}
	if (DisplayAlpha > 0)
	{
		DisplayAlpha -= 4;
		if (DisplayAlpha < 0) DisplayAlpha = 0;
	}

	Counter++;
	iFrameTimer++;

	return TRUE;
}

#define VIEW_HIGH_DIST	36864
#define VIEW_MID_DIST	102400

#define STATE_BAR_WIDTH		100
#define STATE_BAR_HEIGHT	16
#define STATE_BAR_SIZE		92


int Unit::SetLoadPattern(char *szName)
{
	Pattern = 0;
	bActive = TRUE;
	return AddLoaderPattern((Unit *)&Head, szName);
}

void Unit::HandleUnitDataBuffer(char * pBuffer, int iDelayTime, int iSleep)
{
	auto psPacket = (PacketPlayData *)pBuffer;
	auto psPlayBuffData = (PlayBufferData *)(pBuffer + sizeof(PacketPlayData));

	psPacket->iHeader = PKTHDR_PlayDataChar;
	psPacket->dwObjectID = iID;
	psPacket->dwTarget = 0;
	psPacket->iStartPosition = iPlayBuffCount - iDelayTime;
	psPacket->sHp[0] = sCharacterData.sHP.sMin;
	psPacket->sHp[1] = sCharacterData.sHP.sMax;

	int iPercent = iHPBlocks != 0 ? sHPBlocks.sMin : 0;
	int iTotal = iHPBlocks;

	psPacket->sHPLong.iMin = ((int)sCharacterData.sHP.sMax * iPercent) + sCharacterData.sHP.sMin;
	psPacket->sHPLong.iMax = ((int)sCharacterData.sHP.sMax * iTotal) + sCharacterData.sHP.sMax;

	sHPLong = psPacket->sHPLong;

	psPacket->dwAutoCharCode = sCharacterData.iType == CHARACTERTYPE_Monster ? sUnitInfo.dwHashCharacterName : 0;

	sCharacterData.bUpdateInfo[1] = sinSkill.SkillPoint;

	psPacket->bUpdateInfo[0] = sCharacterData.bUpdateInfo[0];
	psPacket->bUpdateInfo[1] = sCharacterData.bUpdateInfo[1];
	psPacket->bUpdateInfo[2] = 0;
	psPacket->bUpdateInfo[3] = 0;
	psPacket->sMapID = -1;
	psPacket->iLevel = sCharacterData.iLevel;
	psPacket->bEventInfo[TRANS_PLAYDATA_EVENT_LEVEL] = sCharacterData.iLevel;
	psPacket->bEventInfo[TRANS_PLAYDATA_EVENT_POTION] = (PotionLog & 0x0F) | ((AttackCritcal & 0xF) << 4);
	psPacket->bEventInfo[TRANS_PLAYDATA_EVENT_EXT] = 0;
	psPacket->bEventInfo[TRANS_PLAYDATA_EVENT_SKIL] = (BYTE)dwDispAppSkill;

	int iStartPosition = psPacket->iStartPosition & PLAYBUFF_MASK;
	int iLastPosition = iStartPosition;

	PlayBuffer *psPlayBuffer = sPlayBuff + iStartPosition;

	int iPlayCount = 0;
	int iAction = psPlayBuffer->saAngle[3];
	DWORD dwFrame = psPlayBuffer->dwFrame;
	memcpy(&psPlayBuffData->sPlayBuff, psPlayBuffer, sizeof(PlayBuffer));
	psPlayBuffData->iCount = 0;
	psPlayBuffData++;
	iPlayCount++;

	DWORD dwFrameSelect = psPlayBuffer->dwFrame >> CHAR_FRAME_SELSHIFT;

	BOOL bAction = TRUE;

	for (int i = 1; i < iDelayTime - 1; i++)
	{
		int iBufferPosition = (iStartPosition + i) & PLAYBUFF_MASK;

		psPlayBuffer = sPlayBuff + iBufferPosition;

		if (psPlayBuffer->saAngle[3] != iAction)
			bAction = FALSE;

		if (psPlayBuffer->dwFrame < dwFrame || psPlayBuffer->saAngle[3] != iAction || dwFrameSelect != (psPlayBuffer->dwFrame >> CHAR_FRAME_SELSHIFT))
		{
			psPlayBuffer = sPlayBuff + iLastPosition;

			iAction = psPlayBuffer->saAngle[3];
			memcpy(&psPlayBuffData->sPlayBuff, psPlayBuffer, sizeof(PlayBuffer));

			psPlayBuffData->iCount = (i * iSleep) - 1;
			psPlayBuffData++;
			iPlayCount++;

			psPlayBuffer = sPlayBuff + iBufferPosition;

			iAction = psPlayBuffer->saAngle[3];
			dwFrame = psPlayBuffer->dwFrame;
			memcpy(&psPlayBuffData->sPlayBuff, psPlayBuffer, sizeof(PlayBuffer));
			psPlayBuffData->iCount = i * iSleep;
			psPlayBuffData++;
			iPlayCount++;

			dwFrameSelect = psPlayBuffer->dwFrame >> CHAR_FRAME_SELSHIFT;
		}

		iLastPosition = iBufferPosition;
	}

	int iBufferPosition = (iStartPosition + iDelayTime - 1) & PLAYBUFF_MASK;

	psPlayBuffer = sPlayBuff + iBufferPosition;

	iAction = psPlayBuffer->saAngle[3];
	memcpy(&psPlayBuffData->sPlayBuff, psPlayBuffer, sizeof(PlayBuffer));
	psPlayBuffData->iCount = (iDelayTime * iSleep) - 1;
	psPlayBuffData++;
	iPlayCount++;

	psPacket->iStartPosition = (psPacket->iStartPosition * iSleep) & PLAYBUFF_MASK;

	if (bAction && sCharacterData.iType == CHARACTERTYPE_Player && psModelAnimation->iType == ANIMATIONTYPE_Idle)
		iPlayCount = 1;

	psPacket->iPlayBuffCount = iPlayCount;

	psPacket->iLength = sizeof(PacketPlayData) + (sizeof(PlayBufferData) * iPlayCount);

	MotionRecordCount++;

	PacketBuffData * psPacketBuff = (PacketBuffData *)(psPlayBuffData + psPacket->iLength);

	if ((AttackIce || iDistortion || PlayWeb) && PlaySlowCount)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->iHeader = PKTHDR_IceDistortionBuff;

		psPacketBuff->dwItemID = PlaySlowCount;
		psPacketBuff->iTime = iDistortion;
		psPacketBuff->iClass = PlayWeb;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	if (PlayPoison[1])
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->iHeader = PKTHDR_PoisionDistortionBuff;
		psPacketBuff->dwItemID = PlayPoison[0];

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	if (PlayFire[1])
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->iHeader = PKTHDR_FireDistortionBuff;
		psPacketBuff->dwItemID = PlayFire[0];

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}

	uUnitInfoSize = psPacket->iLength;
}

int Unit::ClearSkillToPlay(DWORD SkillCode)
{
	switch (SkillCode)
	{
		// ¼«¹â»¤¶Ü
	case SKILL_EXTREME_SHIELD:
		if (dwE_Shield_UseTime)
			dwE_Shield_UseTime = 0;
		break;
		// Áé¹â»¤Ìå
	case SKILL_PHYSICAL_ABSORB:
		if (dwP_Absorb_UseTime)
			dwP_Absorb_UseTime = 0;
		break;
		// Áé¹â·ÉÑï 
	case SKILL_AUTOMATION:
		if (dwAutomation_Time)
			dwAutomation_Time = 0;
		break;
		// ½ðÊôÖØ¼×
	case SKILL_METAL_ARMOR:
		if (dwMetal_Armor_Time)
			dwMetal_Armor_Time = 0;
		break;
		// ·ÀÓùµç²¨
	case SKILL_SPARK_SHIELD:
		if (dwSpark_Shield_Time)
			dwSpark_Shield_Time = 0;
		break;
		// ´ÅÐÔµãÇò
	case SKILL_MAGNETIC_SPHERE:
		if (dwMagnetic_Sphere_Time)
			dwMagnetic_Sphere_Time = 0;
		break;
		// ¿ìËÙ´ò»÷
	case SKILL_H_SONIC:
		if (dwH_Sonic_Time)
			dwH_Sonic_Time = 0;
		break;
		// Õ½Éñ×£¸£
	case SKILL_P_ENHENCE:
		if (dwP_Enhence_Time)
			dwP_Enhence_Time = 0;
		break;
		// »áÐÄÒ»»÷
	case SKILL_CONCENTRATION:
		if (dwConcentrationTime)
			dwConcentrationTime = 0;
		break;
		// ´ÌÉ±Ö®¸«
	case SKILL_SWIFT_AXE:
		if (dwSwiftAxeTime)
			dwSwiftAxeTime = 0;
		break;
		// ·è¿ñÅ­ºð
	case SKILL_BERSERKER:
		if (dwBetserkerTime)
			dwBetserkerTime = 0;
		break;
		// ÖÚÉñÖ®Å­
	case SKILL_B_BERSERKER:
		if (dwB_Berserker_Time)
			dwB_Berserker_Time = 0;
		// Áé»êÖ®Ó¥
	case SKILL_FALCON:
		if (dwFalcon_Time)
			dwFalcon_Time = 0;
		break;
	case SKILL_GOLDEN_FALCON:
		if (dwGolden_Falcon_Time)
			dwGolden_Falcon_Time = 0;
		break;
		// ×ÔÈ»Ö®¹â
	case SKILL_FORCE_OF_NATURE:
		if (dwForceOfNatureTime)
			dwForceOfNatureTime = 0;
		break;
		// Ç±ÄÜ¼¤·¢
	case SKILL_AMPLIFIED:
		if (dwAmplified_Time)
			dwAmplified_Time = 0;
		break;
		//×·Ãü¾¢·ç
	case SKILL_WINDY:
		if (dwWindy_Time)
			dwWindy_Time = 0;
		break;
		// Õ½ÀõÅØÏø
	case SKILL_TRIUMPH_OF_VALHALLA:
		if (dwT_Of_Valhalla_Time)
			dwT_Of_Valhalla_Time = 0;
		break;
		// Íß¶û¹þÀ­Ö®¹â
	case SKILL_HALL_OF_VALHALLA:
		if (dwHallOfValhallaTime)
			dwHallOfValhallaTime = 0;
		break;
		// ±ùËª±êÇ¹
	case SKILL_FROST_JAVELIN:
		if (dwFrost_Javelin_Time)
			dwFrost_Javelin_Time = 0;
		break;
		// ÇáÎè·ÉÑï
	case SKILL_TALARIA:
		if (dwTalaria_Time)
			dwTalaria_Time = 0;
		break;
		// Ê¥¹â»¤Ìå
	case SKILL_HOLY_BODY:
		if (dwHolyBody_Time)
			dwHolyBody_Time = 0;
		break;
		// ÉñÁ¦ÖØ»÷
	case SKILL_HOLY_VALOR:
		if (dwHoly_Valor_Time)
			dwHoly_Valor_Time = 0;
		break;
		// ÌìÓÓÉñîø
	case SKILL_DRASTIC_SPIRIT:
		if (dwDrastic_Spirit_Time)
			dwDrastic_Spirit_Time = 0;
		break;
		// Ê¥ÁéÖ®Îü
	case SKILL_DIVINE_INHALATION:
		if (dwD_Inhalation_Time)
			dwD_Inhalation_Time = 0;
		break;
		// ¾´ÉñÖ®¶Ü
	case SKILL_GODLY_SHIELD:
		if (dwGodly_Shield_Time)
			dwGodly_Shield_Time = 0;
		break;
		// ÉÏµÛ×£¸£
	case SKILL_GOD_BLESS:
		if (dwGod_Bless_Time)
			dwGod_Bless_Time = 0;
		break;
		// ÍöÁéÖ®Öä
	case SKILL_H_BENEDIC:
		if (dwH_Benedic_Time)
			dwH_Benedic_Time = 0;
		break;
		// ÉñÊ¥·´Éä
	case SKILL_HOLY_REFLECTION:
		if (dwHoly_Reflection_Time)
			dwHoly_Reflection_Time = 0;
		break;
		// ¼¯ºÏÖ®Êõ
	case SKILL_ZENITH:
		if (dwZenith_Time)
			dwZenith_Time = 0;
		break;
	case SKILL_ENCHANT_WEAPON:
		if (dwWeaponEffectTime)
		{
			dwWeaponEffectTime = 0;
			WeaponEffect = 0;
		}
		break;
		// Ä§·¨ÊØ»¤
	case SKILL_ENERGY_SHIELD:
		if (dwEnergy_Shield_Time)
			dwEnergy_Shield_Time = 0;
		break;
		// Áé»êÕÙ»½
	case SKILL_SPIRIT_ELEMENTAL:
		if (dwSpirit_Elemental_Time)
			dwSpirit_Elemental_Time = 0;
		break;
		// ÔªËØÖ®½£
	case SKILL_DANCING_SWORD:
		if (dwDancing_Sword_Time)
		{
			dwDancing_Sword_Time = 0;
			dwDancing_Sword_Param = -1;
		}
		break;
		// Ê¥¹â·¨Õó
	case SKILL_T_ANIMA:
		if (dwT_Anima_Time)
			dwT_Anima_Time = 0;
		break;
		// ÉñÊ¥Ö®¹â
	case SKILL_VIRTUAL_LIFE:
		if (dwVirtual_Life_Time)
			dwVirtual_Life_Time = 0;
		break;
		// ÉñÊ¥ÌìÊ¹
	case SKILL_SUMMON_MUSPELL:
		if (dwSummon_Muspell_Time)
			dwSummon_Muspell_Time = 0;
		break;
		// ÌìÅ®É¢»¨
	case SKILL_B_KRISHNA:
		if (dwB_Krishna_Time)
			dwB_Krishna_Time = 0;
		break;
		// Ãô½ÝÖ®Á¦
	case SKILL_ALAS:
		if (dwAlasTime)
			dwAlasTime = 0;
		break;
		// Ãô½Ý´óÊ¦
	case SKILL_INPES:
		if (dwInpesTime)
			dwInpesTime = 0;
		break;
		// Âõ¿Ë¶û
	case SKILL_ADVENT_MIGAL:
		if (dwAdvent_Migal_Time)
			dwAdvent_Migal_Time = 0;
		break;
		// ÆíÓêÊ¦
	case SKILL_RAIN_MAKER:
		if (dwRainmaker_Time)
			dwRainmaker_Time = 0;
		break;
		// Ã×µÂÀ¼´ï
	case SKILL_ADVENT_MIDRANDA:
		if (dwAdvent_Midranda_Time)
			dwAdvent_Midranda_Time = 0;
		break;
		// ÖäÊõÐÅÑö
	case SKILL_CREED:
		if (dwCreed_Time)
			dwCreed_Time = 0;
		break;
	}
	return TRUE;
}


int Unit::SendTransAttack(Unit *lpChar, User *pcUser, int AttackCode, int Add_Damage, int Resistance)
{
	TRANS_ATTACKDATA	TransAttackData;
	smTRANS_COMMAND	smTransCommand;

	int	pow;

	int temp;
	int	accuracy;

	if (!pcUser)
		return 0;


	TransAttackData.code = smTRANSCODE_ATTACKDATA;
	TransAttackData.size = sizeof(TRANS_ATTACKDATA);

	TransAttackData.x = pX;
	TransAttackData.y = pY;
	TransAttackData.z = pZ;

	TransAttackData.AttackState = 1;
	TransAttackData.AttackSize = 48 * fONE;
	TransAttackData.Power = GetRandomPos(sCharacterData.iMinDamage, sCharacterData.iMaxDamage);

	TransAttackData.sRating[0] = sCharacterData.iLevel;
	TransAttackData.sRating[1] = sCharacterData.iAttackRating;

	if (PlayHolyMind[1] > 0)
		TransAttackData.Power -= ((TransAttackData.Power*PlayHolyMind[0]) / 100);

	if (pcUser->dwSiegeItem_Scroll_Time && pcUser->dwSiegeItem_Scroll_Time < SERVER_GAMETIME)
	{
		pcUser->dwSiegeItem_Scroll_Code = 0;
		pcUser->dwSiegeItem_Scroll_Time = 0;
	}
	if (pcUser->dwSiegeItem_Stone1_Time && pcUser->dwSiegeItem_Stone1_Time < SERVER_GAMETIME)
	{
		pcUser->dwSiegeItem_Stone1_Code = 0;
		pcUser->dwSiegeItem_Stone1_Time = 0;
	}

	if (sCharacterData.iMonsterEffectID == snCHAR_SOUND_CASTLE_CRYSTAL_B)
	{
		TransAttackData.sRating[0] = -SKILL_PLAY_ICE_CRYSTAL;
		TransAttackData.sRating[1] = 3;
	}
	else if (sCharacterData.iMonsterEffectID == snCHAR_SOUND_CASTLE_CRYSTAL_G)
	{
		TransAttackData.sRating[0] = -SKILL_PLAY_LIGHTNING_CRYSTAL;
		TransAttackData.sRating[1] = 2;
	}
	else if (sCharacterData.iMonsterEffectID == snCHAR_SOUND_CASTLE_CRYSTAL_R)
	{
		TransAttackData.sRating[0] = -SKILL_PLAY_FIRE_CRYSTAL;
		TransAttackData.sRating[1] = 1;
	}

	if (pcUser->dwSiegeItem_Stone1_Code && pcUser->dwSiegeItem_Stone1_Code == sCharacterData.iMonsterEffectID)
	{
		TransAttackData.Power /= 2;
		TransAttackData.sRating[0] = sCharacterData.iLevel;
		TransAttackData.sRating[1] = sCharacterData.iAttackRating;
	}

	if (pcUser->dwSiegeItem_Scroll_Code == (sinBC1 | sin01))
	{
		if (pcUser->iMapID == MAPID_BlessCastle)
			return FALSE;
	}
	if (pcUser->dwSiegeItem_Scroll_Code == (sinBI1 | sin05))
		return FALSE;


	if (pcUser->dwSiegeItem_Scroll_Code == (sinBC1 | sin03))
	{
		if (pcUser->iMapID == MAPID_BlessCastle)
		{
			if ((rand() % 100) < (int)pcUser->dwSiegeItem_Scroll_Param)
			{
				smTransCommand.code = smTRANSCODE_SUCCESS_EVATION;
				smTransCommand.size = sizeof(smTRANS_COMMAND);
				smTransCommand.WParam = 0;
				smTransCommand.LParam = pcUser->dwSiegeItem_Scroll_Code;
				smTransCommand.SParam = iID;
				smTransCommand.EParam = 0;

				SENDPACKET(pcUser, &smTransCommand);
				return FALSE;
			}
		}
	}

	if (pcUser->dwSiegeItem_Scroll_Code == (sinBI1 | sin07))
	{
		if ((rand() % 100) < (int)pcUser->dwSiegeItem_Scroll_Param)
		{
			smTransCommand.code = smTRANSCODE_SUCCESS_EVATION;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.WParam = 0;
			smTransCommand.LParam = pcUser->dwSiegeItem_Scroll_Code;
			smTransCommand.SParam = iID;
			smTransCommand.EParam = 0;
			SENDPACKET(pcUser, &smTransCommand);
			return FALSE;
		}
	}

	if (pcUser->dwSkill_PhysicalAbsorb_Time)
	{
		if (pcUser->dwSkill_PhysicalAbsorb_Time > SERVER_GAMETIME)
		{
			TransAttackData.Power -= pcUser->dwSkill_PhysicalAbsorb_Param;
			if (TransAttackData.Power < 0)
				return FALSE;
		}
		else
		{
			pcUser->dwSkill_PhysicalAbsorb_Time = 0;
			pcUser->dwSkill_PhysicalAbsorb_Param = 0;
		}
	}

	if (pcUser->dwSkill_MetalArmor_Time)
	{
		if (pcUser->dwSkill_MetalArmor_Time > SERVER_GAMETIME)
		{
			TransAttackData.Power -= pcUser->dwSkill_MetalArmor_Param;
			if (TransAttackData.Power < 0)
				return FALSE;
		}
		else
		{
			pcUser->dwSkill_MetalArmor_Time = 0;
			pcUser->dwSkill_MetalArmor_Param = 0;
		}
	}


	if (pcUser->dwSkill_HolyBody_Time)
	{
		if (pcUser->dwSkill_HolyBody_Time > SERVER_GAMETIME)
		{
			if (sCharacterData.iMonsterType == MONSTERTYPE_Undead)
			{
				TransAttackData.Power -= (TransAttackData.Power * pcUser->dwSkill_HolyBody_Param) / 100;
				if (TransAttackData.Power < 0)
					return FALSE;
			}
		}
		else
		{
			pcUser->dwSkill_HolyBody_Time = 0;
			pcUser->dwSkill_HolyBody_Param = 0;
		}
	}

	if (pcUser->dwSkill_ExtreamShield_Time)
	{
		if (pcUser->dwSkill_ExtreamShield_Time > SERVER_GAMETIME)
		{
			TransAttackData.AttackState |= (pcUser->dwSkill_ExtreamShield_Param << 16);
			if (TransAttackData.Power < 0)
				return FALSE;
		}
		else
		{
			pcUser->dwSkill_ExtreamShield_Time = 0;
			pcUser->dwSkill_ExtreamShield_Param = 0;
		}
	}


	if (pcUser->dwSkill_DivineInhalation_Time && sCharacterData.iMonsterType == MONSTERTYPE_Undead)
	{
		if (pcUser->dwSkill_DivineInhalation_Time > SERVER_GAMETIME)
		{
			temp = sCharacterData.sElementalDef[sITEMINFO_BIONIC];
			if (temp)
			{
				if (temp >= 100)
					temp = 100;
				if (temp <= -100)
					temp = -100;

				temp = (D_Inhalation_Life[pcUser->dwSkill_DivineInhalation_Param] * temp) / 100;
				temp &= 0xFF;
				temp |= D_Inhalation_Block[pcUser->dwSkill_DivineInhalation_Param] << 8;
				if (temp)
					TransAttackData.AttackState |= (temp << 16);
			}
			if (TransAttackData.Power < 0)
				return FALSE;
		}
		else
		{
			pcUser->dwSkill_DivineInhalation_Time = 0;
			pcUser->dwSkill_DivineInhalation_Param = 0;
		}
	}

	if (pcUser->dwSkill_VirtualLife_Time)
	{
		if (pcUser->dwSkill_VirtualLife_Time > SERVER_GAMETIME)
		{
			TransAttackData.Power -= (TransAttackData.Power * pcUser->dwSkill_VirtualLife_Param) / 100;
			if (TransAttackData.Power < 0)
				return FALSE;
		}
		else
		{
			pcUser->dwSkill_VirtualLife_Time = 0;
			pcUser->dwSkill_VirtualLife_Param = 0;
		}
	}

	if (pcUser->dwSkill_EnergyShield_Time)
	{
		if (pcUser->dwSkill_EnergyShield_Time > SERVER_GAMETIME)
		{
			temp = (TransAttackData.Power * pcUser->dwSkill_EnergyShield_Param) / 100;
			TransAttackData.Power -= temp;
			TransAttackData.AttackState |= (temp << 16);
			if (TransAttackData.Power < 0)
				return FALSE;
		}
		else
		{
			pcUser->dwSkill_EnergyShield_Time = 0;
			pcUser->dwSkill_EnergyShield_Param = 0;
		}
	}

	if (pcUser->dwSkill_Compulsion_Time)
	{
		if (pcUser->dwSkill_Compulsion_Time > SERVER_GAMETIME)
		{
			TransAttackData.Power -= pcUser->dwSkill_Compulsion_Param;
			if (TransAttackData.Power < 0)
				return FALSE;
		}
		else
		{
			pcUser->dwSkill_Compulsion_Time = 0;
			pcUser->dwSkill_Compulsion_Param = 0;
		}
	}
	//·è¿ñÅ­ºð
	if (pcUser->dwSkill_Berserker_Time)
	{
		if (pcUser->dwSkill_Berserker_Time > SERVER_GAMETIME)
		{
			TransAttackData.Power -= Berserker_SubAbsorb[pcUser->dwSkill_Berserker_Param];
			if (TransAttackData.Power < 0)
				return FALSE;
		}
		else
		{
			pcUser->dwSkill_Berserker_Time = 0;
			pcUser->dwSkill_Berserker_Param = 0;
		}
	}

	if (pcUser->dwSkill_Vague_Time)
	{
		if (pcUser->dwSkill_Vague_Time > SERVER_GAMETIME)
		{
			if ((rand() % 100) < Vague_EvasionPercent[pcUser->dwSkill_Vague_Param])
			{
				smTransCommand.code = smTRANSCODE_SUCCESS_EVATION;
				smTransCommand.size = sizeof(smTRANS_COMMAND);
				smTransCommand.WParam = 0;
				smTransCommand.LParam = SKILL_PLAY_VAGUE;
				smTransCommand.SParam = iID;
				smTransCommand.EParam = CHARACTERCLASS_Pikeman;

				SENDPACKET(pcUser, &smTransCommand);

				return FALSE;
			}
		}
		else
		{
			pcUser->dwSkill_Vague_Time = 0;
			pcUser->dwSkill_Vague_Param = 0;
		}
	}
	//Ç±ÄÜ¼¤·¢
	if (pcUser->dwSkill_Amplified_Time)
	{
		if (pcUser->dwSkill_Amplified_Time > SERVER_GAMETIME)
		{
			TransAttackData.Power -= Amplified_SubAbs[pcUser->dwSkill_Amplified_Param];
			if (TransAttackData.Power < 0)
				return FALSE;
		}
		else
		{
			pcUser->dwSkill_Amplified_Time = 0;
			pcUser->dwSkill_Amplified_Param = 0;
		}
	}
	if (pcUser->dwSkill_GodlyShied_Time)
	{
		if (pcUser->dwSkill_GodlyShied_Time > SERVER_GAMETIME)
		{
			TransAttackData.Power -= (TransAttackData.Power*Godly_Shield_AbsorbPercent[pcUser->dwSkill_GodlyShied_Param]) / 100;
			if (TransAttackData.Power < 0)
				return FALSE;
		}
		else
		{
			pcUser->dwSkill_GodlyShied_Time = 0;
			pcUser->dwSkill_GodlyShied_Param = 0;
		}
	}

	if (pcUser->dwSkill_HallOfValhalla_Time)
	{
		if (pcUser->dwSkill_HallOfValhalla_Time > SERVER_GAMETIME)
		{
			if ((rand() % 100) < (int)pcUser->wSkill_HallOfValhalla_Param[0])
			{
				smTransCommand.code = smTRANSCODE_SUCCESS_EVATION;
				smTransCommand.size = sizeof(smTRANS_COMMAND);
				smTransCommand.WParam = 0;
				smTransCommand.LParam = SKILL_PLAY_HALL_OF_VALHALLA;
				smTransCommand.SParam = iID;
				smTransCommand.EParam = CHARACTERCLASS_Atalanta;

				SENDPACKET(pcUser, &smTransCommand);

				return FALSE;
			}
		}
		else
			pcUser->dwSkill_HallOfValhalla_Time = 0;
	}

	if (pcUser->dwSkill_SummonMuspell_Time)
	{
		if (pcUser->dwSkill_SummonMuspell_Time > SERVER_GAMETIME)
		{
			if ((rand() % 100) < Summon_Muspell_BlockPercent[pcUser->dwSkill_SummonMuspell_Param])
			{
				smTransCommand.code = smTRANSCODE_SUCCESS_EVATION;
				smTransCommand.size = sizeof(smTRANS_COMMAND);
				smTransCommand.WParam = 0;
				smTransCommand.LParam = SKILL_PLAY_SUMMON_MUSPELL;
				smTransCommand.SParam = iID;
				smTransCommand.EParam = CHARACTERCLASS_Priestess;

				SENDPACKET(pcUser, &smTransCommand);

				return FALSE;
			}
			if (sCharacterData.iMonsterType == MONSTERTYPE_Undead)
			{
				temp = (TransAttackData.Power*Summon_Muspell_UndeadAbsorbPercent[pcUser->dwSkill_SummonMuspell_Param]) / 100;
				TransAttackData.AttackState |= (temp << 16);
				if (TransAttackData.Power < 0)
					return FALSE;
			}
		}
		else
		{
			pcUser->dwSkill_SummonMuspell_Time = 0;
			pcUser->dwSkill_SummonMuspell_Param = 0;
		}
	}
	// ÌìÅ®É¢»¨
	if (pcUser->dwSkill_Krishna_Time)
	{
		if (pcUser->dwSkill_Krishna_Time > SERVER_GAMETIME)
		{
			if (rand() % 100 < B_Krishna_Evasion[pcUser->dwSkill_Krishna_Param])
			{
				smTransCommand.code = smTRANSCODE_SUCCESS_EVATION;
				smTransCommand.size = sizeof(smTRANS_COMMAND);
				smTransCommand.WParam = 0;
				smTransCommand.LParam = SKILL_PLAY_B_KRISHNA;
				smTransCommand.SParam = iID;
				smTransCommand.EParam = CHARACTERCLASS_Priestess;

				SENDPACKET(pcUser, &smTransCommand);
				return FALSE;
			}

			TransAttackData.Power -= B_Krishna_Abs[pcUser->dwSkill_Krishna_Param];
			if (TransAttackData.Power < 0)
				return FALSE;
		}
		else
		{
			pcUser->dwSkill_Krishna_Time = 0;
			pcUser->dwSkill_Krishna_Param = 0;
		}
	}
	// ÆíÓêÊ¦ÎüÊÕÐ§¹û
	if (pcUser->dwSkill_Rainmaker_Time)
	{
		if (pcUser->dwSkill_Rainmaker_Time > SERVER_GAMETIME)
		{
			TransAttackData.Power -= pcUser->dwSkill_Rainmaker_Param;
			if (TransAttackData.Power < 0)
				return TRUE;
		}
		else
		{
			pcUser->dwSkill_Rainmaker_Param = 0;
			pcUser->dwSkill_Rainmaker_Time = 0;
		}
	}

	if (pcUser->dwBlessSkill_Code)
	{
		if (pcUser->dwBlessSkill_Code == SKILL_PLAY_BLESS_ABSORB)
		{
			if (pcUser->dwBlessSkill_Time > SERVER_GAMETIME)
			{
				TransAttackData.Power -= pcUser->dwBlessSkill_Param;
				if (TransAttackData.Power < 0) return FALSE;
			}
			else {
				pcUser->dwBlessSkill_Code = 0;
				pcUser->dwBlessSkill_Time = 0;
			}
		}
		else if (pcUser->dwBlessSkill_Code == SKILL_PLAY_BLESS_EVADE)
		{
			if (pcUser->dwBlessSkill_Time > SERVER_GAMETIME)
			{
				if ((rand() % 100) < (int)pcUser->dwBlessSkill_Param)
				{
					smTransCommand.code = smTRANSCODE_SUCCESS_EVATION;
					smTransCommand.size = sizeof(smTRANS_COMMAND);
					smTransCommand.WParam = 0;
					smTransCommand.LParam = SKILL_PLAY_BLESS_EVADE;
					smTransCommand.SParam = iID;
					smTransCommand.EParam = 0;

					SENDPACKET(pcUser, &smTransCommand);

					return FALSE;
				}
			}
			else
			{
				pcUser->dwBlessSkill_Code = 0;
				pcUser->dwBlessSkill_Time = 0;
			}
		}
	}

	if (pcUser->dwCurse_Defence_Time)
	{
		if (pcUser->dwCurse_Defence_Time > SERVER_GAMETIME)
			TransAttackData.Power += pcUser->dwCurse_Defence_Param;
		else
			pcUser->dwCurse_Defence_Time = 0;
	}
	if (PlayHolyPower[1])
		TransAttackData.Power += (TransAttackData.Power*PlayHolyPower[0]) / 100;

	if (Add_Damage)
		TransAttackData.Power += (TransAttackData.Power*Add_Damage) / 100;

	if (AttackCritcal)
	{
		TransAttackData.Power = (TransAttackData.Power * 170) / 100;
		TransAttackData.AttackState = 2;
	}
	if (AttackEffect)
		TransAttackData.AttackState = 2;

	if (TransAttackData.Power < 1) TransAttackData.Power = 1;

	if (lpChar)
	{
		switch (lpChar->sCharacterData.iType)
		{
		case CHARACTERTYPE_Monster:
			dwBattleTime = TICKCOUNT;
			temp = sCharacterData.iAttackRating;

			if (iPetID)
			{
				switch (iPetID)
				{
				case SKILL_SCOUT_HAWK:
					pow = GetSkillPower(this, lpChar, 0, 0, 0);
					if (pow)
						sCharacterData.iAttackRating += (sCharacterData.iAttackRating*pow) / 100;
					break;
				}
			}
			accuracy = sinGetAccuracy(lpChar->sCharacterData.iLevel, lpChar->sCharacterData.iDefenseRating);
			sCharacterData.iAttackRating = temp;
			if ((rand() % 100) > accuracy)
				return FALSE;
			break;

		case CHARACTERTYPE_NPC:
			TransAttackData.AttackState = Resistance;
			Resistance = 0;
			break;
		}
	}

	if (Resistance)
	{
		TransAttackData.AttackState |= (Resistance << 16);
		pow = Resistance >> 4;
		if (pow > 0 && pow < 512)
			TransAttackData.Power += pow;
	}

	TransAttackData.dwDestObjectSerial = iID;
	TransAttackData.dwTarObjectSerial = 0;
	TransAttackData.dwChkSum = TransAttackData.Power * 2002 + (TransAttackData.x * TransAttackData.y * TransAttackData.z);


	if (lpChar)
	{
		TransAttackData.dwTarObjectSerial = lpChar->iID;

		if (lpChar->sCharacterData.iType == CHARACTERTYPE_Monster && lpChar->sCharacterData.sHP.sMax && lpChar->sCharacterData.sHP.sMin == lpChar->sCharacterData.sHP.sMax)
			lpChar->EnableStateBar = TRUE;
	}

	pow = TransAttackData.Power;

	TransAttackData.dwDamageChkSum = dm_GetDamgeChkSum_S2V(&TransAttackData);

	SENDPACKET(pcUser, &TransAttackData);

	return pow;
}

int Unit::PlayAttackFromPosi(int ex, int ey, int ez, int Dist, int attack)
{
	int AtDist;
	int	dDist;
	int ay;

	ay = abs(pY - ey);

	if (ay > 64 * fONE)
		return NULL;

	AtDist = GetDistanceDbl(pX, pZ, ex, ez);
	dDist = (Dist >> FLOATNS);
	dDist *= dDist;

	if (AtDist < dDist)
	{
		if (psModelAnimation->iType != ANIMATIONTYPE_Attack && psModelAnimation->iType != ANIMATIONTYPE_Skill && psModelAnimation->iType != ANIMATIONTYPE_Die)
		{
			if (attack)
			{
				if (sCharacterData.iType != CHARACTERTYPE_Player)
				{
					SetMotionFromCode(ANIMATIONTYPE_Attack);
					Angle.y = GetRadian2D(pX, pZ, ex, ez);
					AttackX = ex;
					AttackY = ey;
					AttackZ = ez;
				}
			}

			return TRUE;
		}
	}

	return NULL;
}

EMapID Unit::GetMap()
{
	return pcMap ? (EMapID)pcMap->pcBaseMap->iMapID : MAPID_Invalid;
}




int GetProjPosi(int &x3d, int &y3d, int &z3d, POINT3D *CameraPosi, POINT3D *CameraAngle)
{

	int x2d, y2d;
	smMATRIX	trans, rX, rY, rZ, rm;

	int sx, sy, sz;
	int cx, cy, cz;

	cx = x3d - CameraPosi->x;
	cy = y3d - CameraPosi->y;
	cz = z3d - CameraPosi->z;

	smIdentityMatrix(rX);
	smIdentityMatrix(rY);
	smIdentityMatrix(rZ);
	smIdentityMatrix(trans);
	smZeroMatrix(rm);

	smRotateXMatrix(rX, (-CameraAngle->x)&ANGCLIP);
	smRotateYMatrix(rY, (-CameraAngle->y)&ANGCLIP);
	smRotateZMatrix(rZ, (-CameraAngle->z)&ANGCLIP);
	smTranslateMatrix(trans, cx, cy, cz);

	smMatrixMult(rm, trans, rY);
	smMatrixMult(rm, rm, rX);
	smMatrixMult(rm, rm, rZ);


	sx = x3d * rm._11 + y3d * rm._21 + z3d * rm._31;
	sy = x3d * rm._12 + y3d * rm._22 + z3d * rm._32;
	sz = x3d * rm._13 + y3d * rm._23 + z3d * rm._33;

	x3d = (sx >> FLOATNS) + rm._41;
	y3d = (sy >> FLOATNS) + rm._42;
	z3d = (sz >> FLOATNS) + rm._43;


	if (z3d > 0)
	{
		x3d = MidX + ((x3d * viewdistZ) / z3d);
		y3d = MidY - ((y3d * viewdistZ) / z3d);
		z3d >>= FLOATNS;
		return TRUE;

	}
	else
	{
		x2d = CLIP_OUT;
		y2d = CLIP_OUT;
		return FALSE;
	}

}