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

#include "tjboy\\clanmenu\\tjclanDEF.h"
#include "tjboy\\clanmenu\\tjclan.h"
#include "tjboy\\clanmenu\\cE_CViewClanInfo.h"

#include "damage.h"
#include "FontImage.h"
#include "FullZoomMap.h"		// pluto Á×¾úÀ»¶§ Áöµµ ¸ø ¿­°Ô ÇÏ·Á°í

//Ãß°¡ È¸ÇÇ µ¥¹ÌÁö Ãâ·Â ¿É¼Ç
#define DISP_DAMAGE

#define		SUCCUBUS_CURSE_TIME		10

//PK½Ã 40% Èí¼ö·Â Àû¿ë
#define		PKMODE_ABSORB			30

extern BYTE VRKeyBuff[256];
extern int MouseButton[3];

static int MatMBlur;							//¸ÞÆ®¸®¾ó ¹øÈ£

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

int DrawMotionBlur();

/////////////////////// ¼­¹öÃø ÇÔ¼ö ºÒ·¯´Ù ¾´´Ù //////////////////////
//ÀÌº¥Æ® Áö¿ªÀÎÁö Ã½Å©
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


Unit *rsFindAroundMonster(Unit *lpChar, int RoundDist);
Unit *rsSkillDamage_AroundMonster(Unit *lpChar);
Unit *rsSkillMonster_AroundMonster(Unit *lpChar, int RoundDist);

//////////////////////////////////////////////////////////////////////

int GetProjPosi(int &x3d, int &y3d, int &z3d, POINT3D *CameraPosi, POINT3D *CameraAngle);

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

DWORD GetClanCode(int ClassClanCode)
{
	DWORD	dwCode, dwCode1, dwCode2;

	dwCode = ClassClanCode % 1000000;
	dwCode1 = ClassClanCode / 100000000;
	dwCode2 = dwCode1 * 100000000;

	return dwCode + dwCode2;
}

//ÀúÇ× ¼Ó¼º °è»ê
int GetResistancePower(int power, int ResCode)
{
	int rs, result;

	rs = lpCurPlayer->sCharacterData.sElementalDef[ResCode];

	if (rs < 0)
		rs = 0;
	if (rs >= 100)
		rs = 100;
	rs = 100 - rs;

	result = (power*rs) / 100;

	if (result <= 0)
		result = 4;

	return result;
}

int			Debug_TalkZoomMode;
int			Debug_TalkRepeatMode;
int			Debug_TalkRepeatModeType;

//µµ±¸ À§Ä¡ Æ÷ÀÎÆ® ±¸ÇÏ±â
int Unit::GetToolBipPoint(smCHARTOOL *ChrTool, int *nX, int *nY, int *nZ)
{

	smMATRIX *mWorld;
	POINT3D angle;
	int tx, ty, tz;
	smOBJ3D	*lpObj;
	int pframe;
	int rx, ry, rz;

	if (!DisplayFlag)
		return FALSE;

	tx = 0;
	ty = 0;
	tz = 0;

	memcpy(&angle, &Angle, sizeof(POINT3D));
	angle.y = (-angle.y + ANGLE_180)&ANGCLIP;
	lpObj = ChrTool->ObjBip;

	if (lpObj)
	{
		mWorld = &lpObj->mWorld;
		pframe = iFrame;

		AnimObjectTree(lpObj, pframe, angle.x, angle.y, angle.z);

		rx = tx * mWorld->_11 + ty * mWorld->_21 + tz * mWorld->_31;
		ry = tx * mWorld->_12 + ty * mWorld->_22 + tz * mWorld->_32;
		rz = tx * mWorld->_13 + ty * mWorld->_23 + tz * mWorld->_33;

		*nX = pX + (rx >> FLOATNS) + mWorld->_41;
		*nZ = pZ + (ry >> FLOATNS) + mWorld->_42;
		*nY = pY + (rz >> FLOATNS) + mWorld->_43;

		return TRUE;
	}

	return FALSE;
}


int Unit::GetAttackPoint(int *nX, int *nY, int *nZ)
{
	smMATRIX *mWorld;
	POINT3D angle;
	int tx, ty, tz;
	smCHARTOOL *ChrTool = 0;
	smOBJ3D	*lpObj;
	int pframe;
	int rx, ry, rz;

	ChrTool = &HvRightHand;

	if (!DisplayFlag)
		return FALSE;

	tx = 0;
	ty = 0;

	if (ChrTool->PatTool)
		tz = ChrTool->SizeMax / 2;
	else
		tz = 0;

	memcpy(&angle, &Angle, sizeof(POINT3D));
	angle.y = (-angle.y + ANGLE_180)&ANGCLIP;

	if (AttackObjBip && !tz && !ShootingMode)
		lpObj = AttackObjBip;
	else
		lpObj = ChrTool->ObjBip;

	if (lpObj)
	{
		mWorld = &lpObj->mWorld;
		pframe = iFrame;

		AnimObjectTree(lpObj, pframe, angle.x, angle.y, angle.z);

		rx = tx * mWorld->_11 + ty * mWorld->_21 + tz * mWorld->_31;
		ry = tx * mWorld->_12 + ty * mWorld->_22 + tz * mWorld->_32;
		rz = tx * mWorld->_13 + ty * mWorld->_23 + tz * mWorld->_33;

		*nX = pX + (rx >> FLOATNS) + mWorld->_41;
		*nZ = pZ + (ry >> FLOATNS) + mWorld->_42;
		*nY = pY + (rz >> FLOATNS) + mWorld->_43;

		return TRUE;
	}

	return FALSE;
}
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


//Æ¯Á¤ ¿ÀºêÁ§Æ®ÀÇ Æ®¸®¸¦ ÃßÀûÇÏ¿© ¾Ö´Ï¸ÞÀÌ¼Ç ½ÃÅ´
int AnimObjectTree(smOBJ3D *tObj, int frame, int ax, int ay, int az)
{
	smOBJ3D *ObjList[32];
	smOBJ3D *obj;
	int ObjCnt;
	int cnt;

	ObjCnt = 0;
	obj = tObj;

	while (1) {
		ObjList[ObjCnt++] = obj;
		if (!obj->pParent) break;
		obj = obj->pParent;
	}

	for (cnt = ObjCnt - 1; cnt >= 0; cnt--) {
		ObjList[cnt]->TmAnimation(frame, ax, ay, az);
	}

	return TRUE;
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


int smCHAR_CameraX;
int smCHAR_CameraY;
int smCHAR_CameraZ;

int smCHAR_CameraAngX;
int smCHAR_CameraAngY;
int smCHAR_CameraAngZ;


// Ä³¸¯ÅÍ¿¡ »ç¿ëÇÒ Ä«¸Þ¶ó À§Ä¡¸¦ ¼³Á¤ÇÑ´Ù
int smCHAR_SetCameraPosi(int x, int y, int z, int angX, int angY, int angZ)
{
	smCHAR_CameraX = x;
	smCHAR_CameraY = y;
	smCHAR_CameraZ = z;

	smCHAR_CameraAngX = angX;
	smCHAR_CameraAngY = angY;
	smCHAR_CameraAngZ = angZ;

	return TRUE;
}

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
			if (SETTINGHANDLE->Get().bDebugMode)
			{
				CHATGAMEHANDLE->AddChatBoxTextEx(CHATCOLOR_Error, "Loading Error , ( %s )", modelInfo.szModelFile);
			}
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
		OpenDispLoading();

		if (smSTAGE3D_ReadASE(smLoader[cnt].szLoadName, smLoader[cnt].lpStage))
		{
			smLoader[cnt].lpStage->smMaterialGroup->ReadTextures(TRUE);

			smLoader[cnt].Result = TRUE;
			smLoader[cnt].lpStage->Head = TRUE;
		}
		CloseDispLoading();
	}

	if (smLoader[cnt].lpItem)
	{
		smLoader[cnt].lpItem->PatLoading = TRUE;

		lpPatOld = smLoader[cnt].lpItem->lpDinaPattern;
		smDPat = smPattern.LoadCharactor(smLoader[cnt].szLoadName);

		if (smDPat)
		{
			if (smDPat->UseCount == 1)
			{
				if (smDPat && smDPat->Pat)
					smDPat->Pat->smMaterialGroup->ReadTextures();
			}

			smLoader[cnt].lpItem->DisplayFlag = 0;

			smLoader[cnt].lpItem->SetPattern(smDPat->Pat);
			smLoader[cnt].lpItem->lpDinaPattern = smDPat;
			lstrcpy(smLoader[cnt].lpItem->szModelName, smDPat->szPatName);
			smLoader[cnt].lpItem->DisplayFlag = TRUE;

		}
		smLoader[cnt].Result = TRUE;

		if (smDPat && lpPatOld)
			smDPAT_Delete(lpPatOld);

		smLoader[cnt].lpItem->PatLoading = FALSE;
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

			if ((smDPat->UseCount == 1 || (smDPat2 && smDPat2->UseCount == 1)))
			{
				if (smDPat && smDPat->Pat)
					smDPat->Pat->smMaterialGroup->ReadTextures();
				if (smDPat2 && smDPat2->Pat)
					smDPat2->Pat->smMaterialGroup->ReadTextures();
			}

			smLoader[cnt].lpChar->DisplayFlag = TRUE;

		}
		else
		{
			CHATGAMEHANDLE->AddChatBoxTextEx(CHATCOLOR_Error, "> Load Model Error %s", smLoader[cnt].szLoadName);
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

	lpTargetChar = 0;

	sCharacterData.sHP.sMin = 100;
	sCharacterData.sHP.sMax = 100;
	sCharacterData.iType = CHARACTERTYPE_None;

	dwLastTransTime = dwPlayTime;

	iFrameTimer = 0;

	PatWidth = 0;
	PatHeight = 0;
	PatSizeLevel = 0;

	FrameStep = 80;
	MoveSpeed = 250;
	AttackSpeed = fONE;

	lpExt1 = 0;
	lpExt2 = 0;
	lpExt3 = 0;
	lpExt4 = 0;

	dwMessageEndTime = dwPlayTime;
	uUnitInfoSize = 0;
	dwActionItemCode = 0;

	ShootingMode = FALSE;
	ShootingFlag = FALSE;
	chrAttackTarget = 0;

	AttackToolRange = 0;
	AttackAnger = 0;
	AttackIce = 0;
	iLoadedMapIndex = -1;
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

	HoSkillCode = 0;
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

	AttackSkillRange = 0;

	RecvExp = 0;

	sAddColorEffect[0] = 0;
	sAddColorEffect[1] = 0;
	sAddColorEffect[2] = 0;
	sAddColorEffect[3] = 0;

	sCharacterData.sGlow = 0;
	sCharacterData.sSize = 0;

	RenderLatter = FALSE;
	dwUpdateCharInfoTime = 0;

	dwTradeMsgCode = 0;
	EventAttackCount = 0;

	dwClanManageBit = 0;
	dwVipBit = 0;

	psaDamageUsersData = nullptr;
	psaSiegeWarDataList = nullptr;

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

	lpLinkChar = 0;

	iCharacterType = CHARACTERTYPE_None;
	dwClanCode = 0;
	iHPBlocks = 0;

	sBlessCastle_Param[0] = 0;
	sBlessCastle_Param[1] = 0;
#ifndef _W_SERVER
	WeaponEffect = 0;
	dwWeaponEffectTime = 0;

	iClanInfoIndex = -1;
	Clan_CastleMasterFlag = 0;
	dwClanInfoTime = 0;
	TryAttackCount = 0;

	sBlessCastle_Damage[0] = 0;
	sBlessCastle_Damage[1] = 0;
#else
	dwTargetLockTime = 0;

	lpCompulsionPlayInfo = 0;
	dwCompulsionTime = 0;

	dwAssassinEyeTime = 0;
	AssassinEyeParam = 0;

	sMoveStepCount[0] = 0;
	sMoveStepCount[1] = 0;

	DontMoveFlag = 0;

	Clan_CastleMasterFlag = 0;
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



int Unit::SetTool(DWORD dwItemCode, int hvPosi)
{
	char szToolMeshName[64];
	int cnt, szX, szN;

	szX = szN = 0;

	if (sCharacterData.iType != CHARACTERTYPE_Player && iCharacterType != CHARACTERTYPE_Player)
		return FALSE;

	if (dwItemCode)
		sinGetItemInfo(dwItemCode, szToolMeshName);

	switch (hvPosi)
	{
	case hvPOSI_RHAND:
		if (HvRightHand.ObjBip)
		{
			if (lpDinaRightPattern)
			{
				AddRemoveDynPattern(lpDinaRightPattern);
				lpDinaRightPattern = 0;
			}
			if (dwItemCode)
			{
				lpDinaRightPattern = smPattern.LoadCharactor(szToolMeshName);
				if (lpDinaRightPattern)
				{
					HvRightHand.PatTool = lpDinaRightPattern->Pat;
					for (cnt = 0; cnt < lpDinaRightPattern->Pat->nObj3d; cnt++)
					{
						if (szX < lpDinaRightPattern->Pat->obj3d[cnt]->maxY)
							szX = lpDinaRightPattern->Pat->obj3d[cnt]->maxY;
						if (szN < lpDinaRightPattern->Pat->obj3d[cnt]->minY)
							szN = lpDinaRightPattern->Pat->obj3d[cnt]->minY;
					}
					HvRightHand.SizeMax = szX;
					HvRightHand.SizeMin = szN;
					HvRightHand.dwItemCode = dwItemCode;
					dwActionItemCode = dwItemCode;

					if ((dwItemCode & sinITEM_MASK2) == sinWN1)
						HvRightHand.ObjBip = AnimPattern->GetObjectFromName(szBipName_BackSpine);
					else
						HvRightHand.ObjBip = AnimPattern->GetObjectFromName(szBipName_RightHand);
					wStickItems[smPLAYBUFF_ITEM_RIGHT] = ITEMHANDLE->GetItemNumberFromID(dwItemCode);
				}
				else
				{
					HvRightHand.PatTool = NULL;
					HvRightHand.dwItemCode = NULL;
					HvRightHand.ElementEffect = NULL;
					wStickItems[smPLAYBUFF_ITEM_RIGHT] = -1;
				}
			}
			else
			{
				HvRightHand.PatTool = NULL;
				HvRightHand.dwItemCode = NULL;
				HvRightHand.ElementEffect = NULL;
				wStickItems[smPLAYBUFF_ITEM_RIGHT] = -1;
			}
		}
		else
			return FALSE;
		break;

	case hvPOSI_LHAND:
		if (HvLeftHand.ObjBip)
		{
			if (lpDinaLeftPattern)
			{
				AddRemoveDynPattern(lpDinaLeftPattern);
				lpDinaLeftPattern = 0;
			}
			if (dwItemCode)
			{
				lpDinaLeftPattern = smPattern.LoadCharactor(szToolMeshName);

				if (lpDinaLeftPattern)
				{
					HvLeftHand.PatTool = lpDinaLeftPattern->Pat;
					for (cnt = 0; cnt < lpDinaLeftPattern->Pat->nObj3d; cnt++)
					{
						if (szX < lpDinaLeftPattern->Pat->obj3d[cnt]->maxY)
							szX = lpDinaLeftPattern->Pat->obj3d[cnt]->maxY;
						if (szN < lpDinaLeftPattern->Pat->obj3d[cnt]->minY)
							szN = lpDinaLeftPattern->Pat->obj3d[cnt]->minY;
					}
					HvLeftHand.SizeMax = szX;
					HvLeftHand.SizeMin = szN;
					HvLeftHand.dwItemCode = dwItemCode;
					wStickItems[smPLAYBUFF_ITEM_LEFT] = ITEMHANDLE->GetItemNumberFromID(dwItemCode);

					if ((dwItemCode&sinITEM_MASK2) == sinDS1 || (dwItemCode&sinITEM_MASK2) == sinOM1)
					{
						if ((dwItemCode&sinITEM_MASK2) == sinDS1)
							HvLeftHand.ObjBip = AnimPattern->GetObjectFromName(szBipName_Shield);
						else
						{
							HvLeftHand.PatTool = NULL;
							HvLeftHand.dwItemCode = NULL;
							HvLeftHand.ElementEffect = NULL;
							wStickItems[smPLAYBUFF_ITEM_LEFT] = -1;
						}
					}
					else
					{
						HvLeftHand.ObjBip = AnimPattern->GetObjectFromName(szBipName_LeftHand);
						if (dwActionItemCode == NULL)
							dwActionItemCode = dwItemCode;
					}
				}
				else
				{
					HvLeftHand.PatTool = 0;
					HvLeftHand.dwItemCode = 0;
					HvLeftHand.ElementEffect = 0;
					wStickItems[smPLAYBUFF_ITEM_LEFT] = -1;
				}
			}
			else
			{
				HvLeftHand.PatTool = 0;
				HvLeftHand.dwItemCode = 0;
				HvLeftHand.ElementEffect = 0;
				wStickItems[smPLAYBUFF_ITEM_LEFT] = -1;
			}

		}
		else
			return FALSE;
		break;
	}

	if (dwActionItemCode)
	{
		if (dwActionItemCode != HvLeftHand.dwItemCode && dwActionItemCode != HvRightHand.dwItemCode)
			dwActionItemCode = 0;

		if (dwActionItemCode == HvLeftHand.dwItemCode)

			AttackToolRange = (HvLeftHand.SizeMax * 200) >> 8;

		if (dwActionItemCode == HvRightHand.dwItemCode)

			AttackToolRange = (HvRightHand.SizeMax * 200) >> 8;

		cnt = 0;
		dwItemSetting = 1;

		while (dwItemCodeFromVillage[cnt] != 0)
		{
			if (dwItemCodeFromVillage[cnt] == dwActionItemCode)
			{
				dwItemSetting = 0;
				break;
			}
			cnt++;
		}

		cnt = 0;

		while (dwItemCodeFromVillage_Bow[cnt] != 0)
		{
			if (dwItemCodeFromVillage_Bow[cnt] == dwActionItemCode)
			{
				dwItemSetting = 2;
				break;
			}
			cnt++;
		}

		cnt = 0;

		while (dwItemCodeFromVillage_Cross[cnt] != 0)
		{
			if (dwItemCodeFromVillage_Cross[cnt] == dwActionItemCode)
			{
				dwItemSetting = 3;
				break;
			}
			cnt++;
		}
		if ((dwActionItemCode & sinITEM_MASK2) == sinWD1)
		{
			if (sinChar->iClass == CHARACTERCLASS_Assassin)
				dwItemSetting = 4;
			else
				dwItemSetting = 1;
		}

		if (HvRightHand.dwItemCode == NULL && (HvLeftHand.dwItemCode & sinITEM_MASK2) == sinWD1)
		{
			dwItemSetting = 5;
			dwItemCode = HvLeftHand.dwItemCode;
			dwActionItemCode = HvLeftHand.dwItemCode;
		}
	}
	else
		AttackToolRange = 0;

	// ÆÕÍ¨¹¥»÷ÊÇ·ñ»ðÇò

	if ((dwActionItemCode&sinITEM_MASK2) == sinWS1 || (dwActionItemCode&sinITEM_MASK2) == sinWT1 || ((dwActionItemCode&sinITEM_MASK2) == sinWM1 && (sCharacterData.iClass == CHARACTERCLASS_Magician || sCharacterData.iClass == CHARACTERCLASS_Priestess)) || ((dwActionItemCode & sinITEM_MASK2) == sinWN1 && sCharacterData.iClass == CHARACTERCLASS_Shaman) || (dwActionItemCode == (sinTW1 | sin05)) || (dwActionItemCode == (sinTW1 | sin07)))
		ShootingMode = TRUE;
	else
		ShootingMode = FALSE;

	if ((sCharacterData.iType == CHARACTERTYPE_Player || iCharacterType == CHARACTERTYPE_Player) && dwItemCode == dwActionItemCode)
	{
		if (psModelAnimation->iType != ANIMATIONTYPE_Die && psModelAnimation->iType != ANIMATIONTYPE_Flinch && psModelAnimation->iType != ANIMATIONTYPE_Revive)
		{
			SetMotionFromCode(psModelAnimation->iType);
			AttackCritcal = -1;
		}

		if (dwItemCode)
		{
			ItemData * pItem = ITEMHANDLE->GetItemDataByID(dwItemCode);

			if (pItem)
			{
				if (pItem->iItemSlotFlag == ITEMSLOTFLAG_LeftRightHand && !ShootingMode && pItem->sBaseItemID.ToItemType() != sinWD1)
					dwActionItemTwoHand = TRUE;
				else
					dwActionItemTwoHand = FALSE;
			}
		}
	}

	DisplayTools = TRUE;
	return TRUE;
}

int Unit::SetPosi(int x, int y, int z, int angX, int angY, int angZ)
{
	int sy;

	pX = x;
	pZ = z;
	pY = y;

	if (y == 0 && lpStage)
		pY = lpStage->GetHeight(pX, pZ);

	if (pY == 0)
	{
		if (smGameStage[0])
			pY = smGameStage[0]->GetHeight(pX, pZ);

		if (smGameStage[1])
		{
			sy = smGameStage[1]->GetHeight(pX, pZ);
			if (pY < sy)
				pY = sy;
		}
	}

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

//¸ÕÁö »ý¼º
int	Unit::SetSmoking(int level)
{
	Point3D sPosition;

	sPosition = GetMoveLocation(4 * fONE, 0, 0, 0, Angle.y, 0);
	StartEffect(pX + sPosition.iX, pY + 8 * fONE, pZ + sPosition.iZ, 20, 20, EFFECT_DUST1);

	sPosition = GetMoveLocation(-4 * fONE, 0, 0, 0, Angle.y, 0);
	StartEffect(pX + sPosition.iX, pY + 8 * fONE, pZ + sPosition.iZ, 20, 20, EFFECT_DUST1);

	return TRUE;


}

//µØÍ¼ÒÆ¶¯
int Unit::MoveAngle2(int step)
{
	int x, z, y;
	int he, hy;
	int OldStageField;
	POINT3D MovePosi;
	int MovLevel[2];

	WaterHeight = CLIP_OUT;

	if (SETTINGHANDLE->Get().bDebugMode && VRKeyBuff['N'])
	{
		x = pX + (((GetSin[Angle.y&ANGCLIP] >> FLOATNS) * step) >> FLOATNS);
		z = pZ + (((GetCos[Angle.y&ANGCLIP] >> FLOATNS) * step) >> FLOATNS);
		y = pY;

		pY = y;
		pX = x;
		pZ = z;

		return TRUE;
	}

	POINT3D Posi;

	he = 0;

	Posi.x = x = pX;
	Posi.y = y = pY;
	Posi.z = z = pZ;

	OldStageField = iLoadedMapIndex;
	iLoadedMapIndex = -1;

	if (step == 0 || PHeight < y)
	{
		if (lpStage)
		{
			he = lpStage->GetFloorHeight(x, y, z, Pattern->SizeHeight);
		}
		else
		{
			if (smGameStage[0])
			{
				he = smGameStage[0]->GetFloorHeight(x, y, z, Pattern->SizeHeight);
				iLoadedMapIndex = 0;
			}

			if (smGameStage[1])
			{
				hy = smGameStage[1]->GetFloorHeight(x, y, z, Pattern->SizeHeight);
				if (he < hy)
				{
					he = hy;
					iLoadedMapIndex = 1;
				}
			}
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

				SetSmoking(0);
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
		else
		{
			MovLevel[0] = 0;
			MovLevel[1] = 0;

			if (smGameStage[0] && (MovLevel[0] = smGameStage[0]->CheckNextMove(&Posi, &Angle, &MovePosi, step, Pattern->SizeWidth, Pattern->SizeHeight, OverLapPosi2)) > 0)
			{
				if (smStage_WaterChk != CLIP_OUT)
					WaterHeight = smStage_WaterChk;

				if (STAGE_MAP[0]->iLevel <= sCharacterData.iLevel || SETTINGHANDLE->Get().bDebugMode == TRUE)
				{
					iLoadedMapIndex = 0;

					he = MovePosi.y;
					x = MovePosi.x;
					y = MovePosi.y;
					z = MovePosi.z;
				}

			}
			if (smGameStage[1] && (MovLevel[1] = smGameStage[1]->CheckNextMove(&Posi, &Angle, &MovePosi, step, Pattern->SizeWidth, Pattern->SizeHeight, OverLapPosi2) > 0))
			{
				if (smStage_WaterChk != CLIP_OUT)
					WaterHeight = smStage_WaterChk;

				if (STAGE_MAP[1]->iLevel <= sCharacterData.iLevel || SETTINGHANDLE->Get().bDebugMode)
				{
					if (MovLevel[0] && abs(he - MovePosi.y) < fONE * 8)
					{
						if (MovLevel[0] > MovLevel[1])
						{
							x = MovePosi.x;
							y = MovePosi.y;
							z = MovePosi.z;
							iLoadedMapIndex = 1;
						}
					}
					else
					{
						if (he < MovePosi.y)
						{
							x = MovePosi.x;
							y = MovePosi.y;
							z = MovePosi.z;
							iLoadedMapIndex = 1;
						}
					}
				}
			}
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

			SetSmoking(0);

		}
	}

	if (iLoadedMapIndex >= 0 && OldStageField != iLoadedMapIndex)
	{
		OnStageFieldState = STAGE_MAP[iLoadedMapIndex]->iMapType;
		if (psModelAnimation && (OldStageField < 0 || OnStageFieldState != STAGE_MAP[OldStageField]->iMapType))
			SetMotionFromCode(psModelAnimation->iType);
	}
	if (iLoadedMapIndex < 0)
		iLoadedMapIndex = OldStageField;

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
	if ((ActionCode & sinITEM_MASK2) == sinWD1)
	{
		if (sinChar->iClass != CHARACTERCLASS_Assassin)
		{
			return ITEMHANDLE->IsItemDataByID(FindCode, sinWS2 | sin01);
		}
	}
	int i = 0;
	while (ItemMotionCode[i][0] != 0)
	{
		if (ActionCode == ItemMotionCode[i][0])
		{
			return ITEMHANDLE->IsItemDataByID(FindCode, ItemMotionCode[i][1]);
		}
		i++;
	}

	return ITEMHANDLE->IsItemDataByID(FindCode, ActionCode);
}

// ¼ì²â¼¼ÄÜµÄ±àºÅ
int CheckSkillNum(BOOL bSkill)
{
	int JobCode = lpCurPlayer->sCharacterData.iClass;
	switch (JobCode)
	{
	case CHARACTERCLASS_Fighter:
		if (bSkill > 20 && bSkill <= 40)
			return TRUE;
		break;
	case CHARACTERCLASS_Mechanician:
		if (bSkill > 0 && bSkill <= 20)
			return TRUE;
		break;
	case CHARACTERCLASS_Archer:
		if (bSkill > 60 && bSkill <= 80)
			return TRUE;
		break;
	case CHARACTERCLASS_Pikeman:
		if (bSkill > 40 && bSkill <= 60)
			return TRUE;
		break;
	case CHARACTERCLASS_Atalanta:
		if (bSkill > 102 && bSkill <= 122)
			return TRUE;
		break;
	case CHARACTERCLASS_Knight:
		if (bSkill > 80 && bSkill <= 102)
			return TRUE;
		break;
	case CHARACTERCLASS_Magician:
		if (bSkill > 142 && bSkill <= 162)
			return TRUE;
		break;
	case CHARACTERCLASS_Priestess:
		if (bSkill > 122 && bSkill <= 142)
			return TRUE;
		break;
	case CHARACTERCLASS_Assassin:
		if (bSkill > 162 && bSkill <= 182)
			return TRUE;
		break;
	case CHARACTERCLASS_Shaman:
		if (bSkill > 182 && bSkill <= 202)
			return TRUE;
		break;
	}
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

	if (iLoadedMapIndex >= 0)
	{
		if (STAGE_MAP[iLoadedMapIndex]->iMapType == MAPTYPE_Town)
		{
			StageVillage = 1;
			dwActItemCode = 0;
		}
		else
			StageVillage = 2;
	}
	else
	{
		if (GAMESCREEN->GetActiveScreenType() != SCREEN_World)
			StageVillage = 1;
		else
			StageVillage = 3;
	}
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
							if (CheckSkillNum(bSkill))
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

	iPlayBuffCount = (iPlayBuffCount + 1)&PLAYBUFF_MASK;

	sPlayBuff[iPlayBuffCount].saAngle[0] = Angle.x;
	sPlayBuff[iPlayBuffCount].saAngle[1] = Angle.y;
	sPlayBuff[iPlayBuffCount].saAngle[2] = Angle.z;
	sPlayBuff[iPlayBuffCount].saAngle[3] = action;

	sPlayBuff[iPlayBuffCount].iX = pX;
	sPlayBuff[iPlayBuffCount].iY = pY;
	sPlayBuff[iPlayBuffCount].iZ = pZ;

	sPlayBuff[iPlayBuffCount].dwFrame = (MotionSelectFrame << CHAR_FRAME_SELSHIFT) | iFrame;

	sPlayBuff[iPlayBuffCount].dwTargetSerial = NULL;

	if (lpTargetChar)
		sPlayBuff[iPlayBuffCount].dwTargetSerial = lpTargetChar->iID;

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
int Unit::CheckShootingTest_LastAttackTime(Unit *lpChar)
{
	if (dwLastRecvAttackTime<dwPlayTime && (dwLastRecvAttackTime + 2000)>dwPlayTime)
		return TRUE;

	return CheckShootingTest(lpChar);
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
		else
		{
			if (smGameStage[0])
				he = smGameStage[0]->CheckVecImpact(&ShootingPosi, &ShootingAngle, 16 * fONE);

			if (he == TRUE && smGameStage[1])
				he = smGameStage[1]->CheckVecImpact(&ShootingPosi, &ShootingAngle, 16 * fONE);
		}

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

int Unit::ShootingMain()
{
	POINT3D Posi, pos;
	int x, y, z;
	int he;//,hy;
	int ShootSize;
	int r, g, b;
	int EffectFlag;

	he = CLIP_OUT;
	EffectFlag = 0;

	ShootSize = 512;

	auto sPosition = (dwActionItemCode&sinITEM_MASK2) == sinWS1 || (dwActionItemCode == (sinTW1 | sin07)) ?
		GetMoveLocation(0, 0, 8 * fONE, ShootingAngle.x, ShootingAngle.y, ShootingAngle.z) :
		GetMoveLocation(0, 0, 6 * fONE, ShootingAngle.x, ShootingAngle.y, ShootingAngle.z);

	Posi.x = x = ShootingPosi.x;
	Posi.y = y = ShootingPosi.y;
	Posi.z = z = ShootingPosi.z;

	ShootingPosi.x += sPosition.iX;
	ShootingPosi.y += sPosition.iY;
	ShootingPosi.z += sPosition.iZ;

	if (sCharacterData.iType == CHARACTERTYPE_Player)
	{
		if (dwActionItemCode == HvRightHand.dwItemCode)
		{
			if (HvRightHand.PatTool && HvRightHand.ColorBlink && !HvRightHand.EffectKind)
			{
				r = (HvRightHand.sColors[SMC_R] >> 1) + 128;
				g = (HvRightHand.sColors[SMC_G] >> 1) + 128;
				b = (HvRightHand.sColors[SMC_B] >> 1) + 128;

				StartEffect(ShootingPosi.x, ShootingPosi.y, ShootingPosi.z, r, g, b, 255, EFFECT_PARTICLE_BOW1);

				EffectFlag++;
			}
		}
		if (dwActionItemCode == HvLeftHand.dwItemCode)
		{
			if (HvLeftHand.PatTool && HvLeftHand.ColorBlink && !HvLeftHand.EffectKind)
			{

				r = (HvLeftHand.sColors[SMC_R] >> 1) + 128;
				g = (HvLeftHand.sColors[SMC_G] >> 1) + 128;
				b = (HvLeftHand.sColors[SMC_B] >> 1) + 128;

				StartEffect(ShootingPosi.x, ShootingPosi.y, ShootingPosi.z, r, g, b, 255, EFFECT_PARTICLE_BOW1);

				EffectFlag++;
			}
		}
		if (sCharacterData.iClass == CHARACTERCLASS_Atalanta && ShootingKind == SKILL_PLAY_FARINA)
			sinEffect_Farina_Particle(&ShootingPosi);
	}
	if (ShootingCount > 60 * 2)
		ShootingFlag = FALSE;

	ShootingCount++;

	if (ShootingFlag > 1 && chrAttackTarget)
	{
		ShootingFlag++;
		if (ShootingFlag > 8)
			ShootingFlag = FALSE;

		if (EffectFlag)
			StartEffect(chrAttackTarget->pX, ShootingPosi.y, chrAttackTarget->pZ, r, g, b, 255, EFFECT_PARTICLE_BOW1);

		return TRUE;
	}

	if (ShootingFlag == 1 && chrAttackTarget && AttackCritcal >= 0)
	{
		x = abs(ShootingPosi.x - chrAttackTarget->pX);
		z = abs(ShootingPosi.z - chrAttackTarget->pZ);
		y = abs(ShootingPosi.y - chrAttackTarget->pY);

		if (x < 64 * fONE && z < 64 * fONE && y < 80 * fONE)
		{
			ShootingFlag++;

			if (sCharacterData.iClass == CHARACTERCLASS_Atalanta && ShootingKind == SKILL_PLAY_FARINA)
			{
				Posi.x = chrAttackTarget->pX;
				Posi.y = chrAttackTarget->pY + 22 * fONE;
				Posi.z = chrAttackTarget->pZ;
				sinEffect_SkillHit(SKILL_FARINA, &Posi);
				SetDynLight(chrAttackTarget->pX, chrAttackTarget->pY + 22 * fONE, chrAttackTarget->pZ, 100, 0, 0, 0, 400);
				PlayWaponSoundDirect(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 16);
			}
			else
			{
				if (WeaponEffect)
				{
					pos.x = chrAttackTarget->pX;
					pos.y = chrAttackTarget->pY + 22 * fONE;
					pos.z = chrAttackTarget->pZ;

					switch (WeaponEffect)
					{
					case (sITEMINFO_LIGHTING + 1):
						AssaParticle_LightHit1(&pos);
						SetDynLight(x, y, z, 0, 0, 100, 0, 400);
						if ((rand() % 2) == 0)
							SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_LIGHTNING1, pX, pY, pZ);
						else
							SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_LIGHTNING2, pX, pY, pZ);
						break;
					case (sITEMINFO_FIRE + 1):
						AssaParticle_FireHit1(&pos);
						SetDynLight(x, y, z, 100, 0, 0, 0, 400);
						if ((rand() % 2) == 0)
							SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_FIRE1, pX, pY, pZ);
						else
							SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_FIRE2, pX, pY, pZ);
						break;
					case (sITEMINFO_ICE + 1):
						AssaParticle_IceHit1(&pos);
						SetDynLight(x, y, z, 0, 0, 100, 0, 400);
						if ((rand() % 2) == 0)
							SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_ICE1, pX, pY, pZ);
						else
							SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_ICE2, pX, pY, pZ);
						break;
					}
				}
				else
				{
					if (AttackCritcal)
					{
						StartEffect(chrAttackTarget->pX, chrAttackTarget->pY + 22 * fONE, chrAttackTarget->pZ, EFFECT_CRITICAL_HIT1);
						SetDynLight(chrAttackTarget->pX, chrAttackTarget->pY + 22 * fONE, chrAttackTarget->pZ, 100, 0, 0, 0, 400);
						PlayWaponSoundDirect(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 16);
					}
					else
					{
						StartEffect(chrAttackTarget->pX, chrAttackTarget->pY + 22 * fONE, chrAttackTarget->pZ, EFFECT_NORMAL_HIT1);
						SetDynLight(chrAttackTarget->pX, chrAttackTarget->pY + 22 * fONE, chrAttackTarget->pZ, 40, 0, 0, 0, 400);
					}

					if (dwForceOrbTime > dwPlayTime)
					{
						pos.x = chrAttackTarget->pX;
						pos.y = chrAttackTarget->pY + 22 * fONE;
						pos.z = chrAttackTarget->pZ;

						AssaParticle_ShelltomWeaponHit(&pos);
					}

				}
				if (HvLeftHand.ElementEffect || HvRightHand.ElementEffect)
				{
					pos.x = x;
					pos.y = y;
					pos.z = z;

					if (HvLeftHand.ElementEffect)
						AssaParticle_ElementHit(this, HvLeftHand.ElementEffect, &pos);
					if (HvRightHand.ElementEffect)
						AssaParticle_ElementHit(this, HvRightHand.ElementEffect, &pos);
				}
			}
			PlayWaponSoundDirect(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 14);

			if (this == lpCurPlayer && AttackExp > 0)
				AttackExp = 0;
		}
	}

	return TRUE;
}

//ÐîÁ¦¼¼ÄÜ
int Unit::ChargingSkill()
{
	DWORD dwFrame;

	if (this != lpCurPlayer)
		return FALSE;

	dwFrame = iFrame - psModelAnimation->StartFrame * 160;

	if (SkillChargingFlag && MouseButton[1] == 0)
		SkillChargingFlag = 0;

	if ((sCharacterData.iClass == CHARACTERCLASS_Archer && (AttackSkil & 0xFF) == SKILL_PLAY_PHOENIX_SHOT) || (sCharacterData.iClass == CHARACTERCLASS_Pikeman && (AttackSkil & 0xFF) == SKILL_PLAY_CHARGING_STRIKE))
	{
		if (dwFrame >= psModelAnimation->EventFrame[0] && dwFrame < psModelAnimation->EventFrame[1])
		{
			if (SkillChargingFlag == 0)
			{
				iFrame = psModelAnimation->StartFrame * 160 + psModelAnimation->EventFrame[1];
				ChargingFlag = 1;
			}
		}
	}

	return TRUE;
}

//°ø°Ý ÀÌº¥Æ®
int Unit::EventAttack(int Flag)
{

	int shootFlag;
	DWORD compFrame;
	int x, y, z;
	int wp;
	DWORD NearFrame;
	POINT3D	pos, pos2;

	int	cnt, ChrCnt;
	Unit *lpCharList[32];

	ChargingSkill();

	if (AttackSkil > 0 || (sCharacterData.iType == CHARACTERTYPE_Monster && psModelAnimation->iType == ANIMATIONTYPE_Skill))
	{
		if (Flag || ((psModelAnimation->iType == ANIMATIONTYPE_Attack || psModelAnimation->iType == ANIMATIONTYPE_Skill) && psModelAnimation->EventFrame[0]))
		{
			compFrame = iFrame - (psModelAnimation->StartFrame * 160);
			if ((psModelAnimation->EventFrame[0] > (compFrame - FrameStep) && psModelAnimation->EventFrame[0] <= compFrame) ||
				(psModelAnimation->EventFrame[1] && psModelAnimation->EventFrame[1] > (compFrame - FrameStep) && psModelAnimation->EventFrame[1] <= compFrame) ||
				(psModelAnimation->EventFrame[2] && psModelAnimation->EventFrame[2] > (compFrame - FrameStep) && psModelAnimation->EventFrame[2] <= compFrame) ||
				(psModelAnimation->EventFrame[3] && psModelAnimation->EventFrame[3] > (compFrame - FrameStep) && psModelAnimation->EventFrame[3] <= compFrame) ||

				(dwEventFrameExt[0] && dwEventFrameExt[0] > (iFrame - FrameStep) && dwEventFrameExt[0] <= iFrame) ||
				(dwEventFrameExt[1] && dwEventFrameExt[1] > (iFrame - FrameStep) && dwEventFrameExt[1] <= iFrame) ||
				(dwEventFrameExt[2] && dwEventFrameExt[2] > (iFrame - FrameStep) && dwEventFrameExt[2] <= iFrame) ||
				(dwEventFrameExt[3] && dwEventFrameExt[3] > (iFrame - FrameStep) && dwEventFrameExt[3] <= iFrame) ||

				(MotionEvent == 0 && psModelAnimation->EventFrame[0] <= compFrame)) {

				//½ºÅ³ÀÌº¥Æ®
				MotionEvent++;

				//°æÇèÄ¡ ÀÏºÎ »ó½Â ( ÁÖÀÎ°ø ¸¸ )
				if (this == lpCurPlayer) {//&& AttackExp>0 ) { 
					//AddExp( AttackExp );
					//SetTotalAddExp( AttackExp );			//°æÇèÄ¡ Áõ°¡ ±â·Ï
					AttackExp = 0;

					if (chrAttackTarget && abs(chrAttackTarget->sCharacterData.iLevel - sCharacterData.iLevel) <= AGING_SUB_LEVEL) {
						//·¹º§ 7Â÷ÀÌ ÀÌÇÏ´Â ¿¡ÀÌÂ¡ Àû¿ë
						if (AttackCritcal == TRUE)
							sinCheckAgingLevel(SIN_AGING_CRITICAL, false);
						else
							sinCheckAgingLevel(SIN_AGING_ATTACK, false);
					}
				}

				if (EventSkill() == TRUE)
					return TRUE;
			}
		}
	}


	if (psModelAnimation->iType != ANIMATIONTYPE_Attack && psModelAnimation->iType != ANIMATIONTYPE_Skill) return FALSE;

	if (ActionPattern)
		shootFlag = 0;
	else {
		shootFlag = ShootingFlag;
	}

	if (psModelAnimation->EventFrame[0])
	{
		compFrame = iFrame - (psModelAnimation->StartFrame * 160);
		NearFrame = compFrame - FrameStep;

		if (Flag || (psModelAnimation->EventFrame[0] > NearFrame && psModelAnimation->EventFrame[0] <= compFrame) || (psModelAnimation->EventFrame[1] && psModelAnimation->EventFrame[1] > NearFrame && psModelAnimation->EventFrame[1] <= compFrame))
		{
			MotionEvent++;

			if (sCharacterData.iType == CHARACTERTYPE_Monster)
				CharPlaySound(this);
			else
			{
				WeaponPlaySound(this);
				if (AttackCritcal < 0)
					return FALSE;
			}

			if (this == lpCurPlayer && AttackExp > 0)
			{

				//AttackExp = 500000;

				//AddExp( AttackExp );
				//SetTotalAddExp( AttackExp );			//°æÇèÄ¡ Áõ°¡ ±â·Ï
				AttackExp = 0;

				//SaveGameData();					

				if (chrAttackTarget && abs(chrAttackTarget->sCharacterData.iLevel - sCharacterData.iLevel) <= AGING_SUB_LEVEL)
				{
					if (AttackCritcal == TRUE)
						sinCheckAgingLevel(SIN_AGING_CRITICAL, false);
					else
						sinCheckAgingLevel(SIN_AGING_ATTACK, false);
				}

			}
			if (chrAttackTarget == lpCurPlayer)
				AttackMotionCountUp();

			switch (sCharacterData.iMonsterEffectID)
			{
			case snCHAR_SOUND_MUSHROOM:
				StartEffect(pX, pY + (24 * fONE), pZ, EFFECT_GAS1);
				break;
			case snCHAR_SOUND_IMP:
				if (chrAttackTarget)
				{
					if (CheckShootingTest_LastAttackTime(chrAttackTarget) || CheckLocateBox(pX, pY, pZ, chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 80 * fONE))
					{
						auto sPosition = GetMoveLocation(0, 0, 10 * fONE, 0, Angle.y, 0);
						x = pX + sPosition.iX;
						y = pY + 8 * fONE;
						z = pZ + sPosition.iZ;

						if (sCharacterData.iLevel < 15)
							StartEffectMonsterDest(x, y, z, chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ, MONSTER_IMP_SHOT1);
						else
							StartEffectMonsterDest(x, y, z, chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ, MONSTER_MEPHIT_SHOT1);
					}
					else
						ResetAttackTrans();
				}
				break;
			case snCHAR_SOUND_SHADOW:
				if (chrAttackTarget)
				{
					if (CheckShootingTest_LastAttackTime(chrAttackTarget) || CheckLocateBox(pX, pY, pZ, chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 80 * fONE))
						StartEffectMonsterDest(pX, pY + 32 * fONE, pZ, chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ, MONSTER_IMP_SHOT3);
					else
						ResetAttackTrans();
				}
				break;
			case snCHAR_SOUND_FIGON:
				if (chrAttackTarget)
				{
					if (CheckShootingTest_LastAttackTime(chrAttackTarget) || CheckLocateBox(pX, pY, pZ, chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 80 * fONE))
						StartEffectMonsterDest(pX, pY + 32 * fONE, pZ, chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ, MONSTER_PIGON_SHOT1);
					else
						ResetAttackTrans();
				}
				break;
				//´óÍ·Ö©Öë
			case snCHAR_SOUND_WEB:
				if (chrAttackTarget)
				{
					if (CheckShootingTest_LastAttackTime(chrAttackTarget) || CheckLocateBox(pX, pY, pZ, chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 80 * fONE))
					{
						auto sPosition = GetMoveLocation(0, 0, 32 * fONE, 0, Angle.y, 0);
						StartEffectMonsterDest(pX + sPosition.iX, pY + 12 * fONE, pZ + sPosition.iZ, chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ, MONSTER_WEB_SHOT1);
					}
					else
						ResetAttackTrans();
				}
				break;

			case snCHAR_SOUND_SKELETONRANGE:
				if (chrAttackTarget)
				{
					if (CheckShootingTest_LastAttackTime(chrAttackTarget))
					{
						ShootingPosi.x = pX;
						ShootingPosi.y = pY + 28 * fONE;
						ShootingPosi.z = pZ;
						auto sPosition = GetRadian3D(pX, pY + 28 * fONE, pZ, chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ);
						ShootingAngle.x = sPosition.iX;
						ShootingAngle.y = sPosition.iY;
						ShootingAngle.z = Angle.z;
						ShootingFlag = TRUE;
						ShootingCount = 0;
						dwActionItemCode = sinWS1;
					}
					else
						ResetAttackTrans();
				}
				break;

			case snCHAR_SOUND_WOLVERLIN:
				if (chrAttackTarget)
				{
					auto sPosition = GetMoveLocation(0, 0, 50 * fONE, 0, Angle.y, 0);
					x = pX + sPosition.iX;
					z = pZ + sPosition.iZ;
					y = pY + 18 * fONE;
					StartEffectMonster(x, y, z, MONSTER_PIGON_PARTICLE1);
					StartEffectMonster(x, y, z, MONSTER_PIGON_PARTICLE1);
					StartEffectMonster(x, y, z, MONSTER_PIGON_PARTICLE1);
					StartEffectMonster(x, y, z, MONSTER_PIGON_PARTICLE1);
				}
				break;

			case snCHAR_SOUND_EGAN:
				if (chrAttackTarget)
				{
					if (CheckShootingTest_LastAttackTime(chrAttackTarget))
					{
						auto sPosition = GetMoveLocation(0, 0, 10 * fONE, 0, Angle.y, 0);
						x = pX + sPosition.iX;
						y = pY + 8 * fONE;
						z = pZ + sPosition.iZ;

						StartEffectMonsterDest(x, y, z,
							chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ,
							MONSTER_IMP_SHOT1);
					}
					else
						ResetAttackTrans();
				}
				break;

			case snCHAR_SOUND_MUTANTTREE:
				if (chrAttackTarget)
				{
					if (CheckShootingTest_LastAttackTime(chrAttackTarget))
					{
						auto sPosition = GetMoveLocation(0, 0, 24 * fONE, 0, Angle.y, 0);
						x = pX + sPosition.iX;
						y = pY + 8 * fONE;
						z = pZ + sPosition.iZ;

						sinEffect_MutentTree_Attack(this, chrAttackTarget);
					}
					else
						ResetAttackTrans();
				}
				break;
				//Ð¡ÂÌÈË
			case snCHAR_SOUND_HULK:
				if (chrAttackTarget)
				{
					auto sPosition = GetMoveLocation(0, 0, 54 * fONE, 0, Angle.y, 0);
					StartEffectMonster(pX + sPosition.iX, pY + 48 * fONE, pZ + sPosition.iZ, MONSTER_HULK_HIT1);
				}
				break;
			case snCHAR_SOUND_DMACHINE:
				if (chrAttackTarget)
				{
					auto sPosition = GetMoveLocation(0, 30 * fONE, 10 * fONE, 0, Angle.y, 0);
					StartEffectMonsterDest(pX + sPosition.iX, pY + sPosition.iY, pZ + sPosition.iZ, chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ, MONSTER_DMACHINE_MISSILE1);
				}
				break;
			case snCHAR_SOUND_TURTLE_CANNON:
				if (chrAttackTarget)
					ParkAssaParticle_MonsterTurtleCanonNormal(this, chrAttackTarget);
				break;
			case snCHAR_SOUND_SUCCUBUS:
				if (chrAttackTarget)
				{
					if (sCharacterData.iLevel <= 75)
						wp = MONSTER_SERQBUS_SHOT1;
					else if (sCharacterData.iLevel < 80)
						wp = MONSTER_SERQBUS_SHOT2;
					else
						wp = MONSTER_SERQBUS_SHOT3;

					auto sPosition = GetMoveLocation(0, 20 * fONE, 20 * fONE, 0, Angle.y, 0);
					StartEffectMonsterDest(pX + sPosition.iX, pY + sPosition.iY, pZ + sPosition.iZ, chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ, wp);
				}
				break;

			case snCHAR_SOUND_STYGIANLORD:
				if (chrAttackTarget)
					StartEffectMonsterDest(pX, pY, pZ, chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ, 0, Angle.y, 0, MONSTER_STYGIANLORD_SHOT1);
				break;

			case snCHAR_SOUND_MOKOVA:
			case snCHAR_SOUND_OMICRON:
				if (chrAttackTarget)
				{
					auto sPosition = GetMoveLocation(0, 0, 68 * fONE, 0, Angle.y, 0);
					StartEffectMonster(pX + sPosition.iX, pY + 22 * fONE, pZ + sPosition.iZ, MONSTER_HULK_HIT1);
				}
				break;
			case snCHAR_SOUND_GUARDIAN_SAINT:
				AssaParticleClanMonsterHit2(this);
				break;
			case snCHAR_SOUND_HYPERMACHINE:
				if (chrAttackTarget)
				{
					pos.x = chrAttackTarget->pX;
					pos.y = chrAttackTarget->pY + 20 * fONE;
					pos.z = chrAttackTarget->pZ;
					AssaParticle_MonsterIronHyperHit1(this, &pos);
				}
				break;
			case snCHAR_SOUND_MOUNTAIN:
				AssaParticle_MonsterIronMountainHit1(this);
				break;
			case snCHAR_SOUND_TOWERGOLEM:
				AssaParticle_MonsterIronTowerGolemHit1(this);
				break;
			case snCHAR_SOUND_OMU:
				AssaParticle_MonsterIronOmuHit1(this);
				break;
			case snCHAR_SOUND_CHAINGOLEM:
			case snCHAR_SOUND_DEADZONE:
			case snCHAR_SOUND_IRONFIST:
			case snCHAR_SOUND_MORGON:
			case snCHAR_SOUND_RAMPAGE:
			case snCHAR_SOUND_VAMPRICBEE:
			case snCHAR_SOUND_IRONGUARD:
			case snCHAR_SOUND_GORGON:
			case snCHAR_SOUND_HOBOGOLEM:
			{
				auto sPosition = GetMoveLocation(0, 0, 54 * fONE, 0, Angle.y, 0);
				pos.x = pX + sPosition.iX;
				pos.y = pY + sPosition.iY + 32 * fONE;
				pos.z = pZ + sPosition.iZ;
				AssaParticle_MonsterIronHit1(&pos);
			}
				
				break;
			case snCHAR_SOUND_GOBLINSHAMAN:
				if (chrAttackTarget)
					ParkAssaParticle_MummyShot(this, chrAttackTarget);
				break;
			case snCHAR_SOUND_GROTESQUE:
			{
				auto sPosition = GetMoveLocation(0, 0, 75 * fONE, 0, Angle.y, 0);
				pos.x = pX + sPosition.iX;
				pos.y = pY + sPosition.iY + 32 * fONE;
				pos.z = pZ + sPosition.iZ;
				AssaParticle_MonsterIronHit1(&pos);
			}
				
				break;


			case snCHAR_SOUND_AVELIN_ARCHER:
				if (chrAttackTarget) {
					AssaParticle_MonsterAvelArcher(this, chrAttackTarget); //¾Æº§¸®½ºÅ© ¾ÆÃ³
				}
				break;

			case snCHAR_SOUND_AVELIN_QUEEN:
				if (chrAttackTarget) {
					AssaParticle_MonsterAvelQueen(this, chrAttackTarget); //¾Æº§¸®½ºÅ© ¾ÆÃ³
				}
				break;

			case snCHAR_SOUND_RUNICGUARDIAN:
				if (chrAttackTarget) {
					AssaParticle_MonsterRunicGuardianShot(this, chrAttackTarget);	//·ç´Ð°¡µð¾È
				}
				break;
				//°Í±ðËþ
			case snCHAR_SOUND_BABEL:
				if (chrAttackTarget)
				{
					if (Trans_SplashCharList.code == smTRANSCODE_ATTACK_SLASH_LIST && Trans_SplashCharList.TargetCount > 1)
					{
						ChrCnt = 0;
						for (cnt = 0; cnt < Trans_SplashCharList.TargetCount; cnt++)
						{
							if (cnt >= 32)
								break;
							lpCharList[ChrCnt] = FindChrPlayer(Trans_SplashCharList.dwTarObjectSerial[cnt]);
							if (lpCharList[ChrCnt])
								ChrCnt++;
						}
						AssaParticle_MonsterRunicGuardianBossHit(this, chrAttackTarget, lpCharList, ChrCnt);
						Trans_SplashCharList.code = 0;
					}
					else
						AssaParticle_MonsterRunicGuardianBossHit(this, chrAttackTarget);
				}
				break;

			case snCHAR_SOUND_SADNESS:
				if (chrAttackTarget)
					AssaParticle_MonsterIronSadNessHit1(this);
				break;
			case snCHAR_SOUND_COLDEYE:
				if (chrAttackTarget)
				{
					auto sPosition = GetMoveLocation(0, 0, 24 * fONE, 0, Angle.y, 0);
					pos.x = pX + sPosition.iX;
					pos.y = pY + 64 * fONE;
					pos.z = pZ + sPosition.iZ;
					pos2.x = chrAttackTarget->pX;
					pos2.y = chrAttackTarget->pY + 64 * fONE;
					pos2.z = chrAttackTarget->pZ;
					ParkAssaParticle_ColdEye(&pos, &pos2);
				}
				break;
			case snCHAR_SOUND_FROZEN:
				if (chrAttackTarget)
					ParkAssaParticle_MistIceBolt(this, chrAttackTarget);
				break;
			case snCHAR_SOUND_FROST:
				if (chrAttackTarget && psModelAnimation->KeyCode == 'U')
					ParksinSkillEffect_AcientPiercing(this);
				break;
			case snCHAR_SOUND_CHAOSCARA:
				if (chrAttackTarget)
					ParkAssaParticle_ChaosKara1(chrAttackTarget);
				break;
			case snCHAR_SOUND_DEATHKNIGHT:
				if (psModelAnimation->KeyCode == 'P')
				{
					if (MotionEvent == 1)
						ParkAssaParticle_Valento1(this);
					else
						ParkAssaParticle_Valento3_1(this);
				}
				else if (psModelAnimation->KeyCode == 'L')
				{
					if (MotionEvent == 1)
						ParkAssaParticle_Valento2_1(this);
					else
						ParkAssaParticle_Valento2_2(this);
				}
				break;
			case snCHAR_SOUND_GREATE_GREVEN:
			case snCHAR_SOUND_LIZARDFOLK:
			case snCHAR_SOUND_SPIDER:
			case snCHAR_SOUND_STRIDER:
				if (chrAttackTarget)
				{
					auto sPosition = GetMoveLocation(0, 0, 68 * fONE, 0, Angle.y, 0);
					StartEffectMonster(pX + sPosition.iX, pY + 22 * fONE, pZ + sPosition.iZ, MONSTER_HULK_HIT1);
				}
				break;
			case snCHAR_SOUND_M_LORD:
				if (chrAttackTarget)
					ParkAssaParticle_MummyShot(this, chrAttackTarget);
				break;
			case snCHAR_SOUND_IGOLATION:
				if (chrAttackTarget && psModelAnimation->KeyCode == 'H')
				{
					auto sPosition = GetMoveLocation(0, 0, 68 * fONE, 0, Angle.y, 0);
					StartEffectMonster(pX + sPosition.iX, pY + 22 * fONE, pZ + sPosition.iZ, MONSTER_HULK_HIT1);
				}
				break;
			case snCHAR_SOUND_NIKEN:
				if (chrAttackTarget)
				{
					pos.x = chrAttackTarget->pX;
					pos.y = chrAttackTarget->pY;
					pos.z = chrAttackTarget->pZ;

					AssaParticle_SnailShot(this, &pos);
				}
				break;
			case snCHAR_SOUND_XETAN:
				if (chrAttackTarget && psModelAnimation->KeyCode == 'G')
				{
					auto sPosition = GetMoveLocation(0, 40 * fONE, 20 * fONE, 0, Angle.y, 0);
					StartEffectMonsterDest(pX + sPosition.iX, pY + sPosition.iY, pZ + sPosition.iZ,
						chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ,
						MONSTER_SERQBUS_SHOT2);
				}
				break;
			case snCHAR_SOUND_SPRIN:
				if (chrAttackTarget && (psModelAnimation->KeyCode == 'G' || psModelAnimation->KeyCode == 'H'))
				{
					if (CheckShootingTest_LastAttackTime(chrAttackTarget) || CheckLocateBox(pX, pY, pZ, chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 80 * fONE))
					{
						auto sPosition = GetMoveLocation(0, 0, 32 * fONE, 0, Angle.y, 0);
						StartEffectMonsterDest(pX + sPosition.iX, pY + 12 * fONE, pZ + sPosition.iZ, chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ, MONSTER_WEB_SHOT1);
					}
					else
						ResetAttackTrans();
				}
				break;
			case snCHAR_SOUND_BEBECHICK:
				if (chrAttackTarget && (psModelAnimation->KeyCode == 'H' || psModelAnimation->KeyCode == 'J'))
				{
					//  ÀÌÆåÆ® Á¤ÀÇ ¾ÈÇÔ.(¸ð¼Ç¸¸ ¼³Á¤)
				}
				break;
			case snCHAR_SOUND_PAPACHICK:	// ¾Æºü ²¿²¿
				if (chrAttackTarget && psModelAnimation->KeyCode == 'H')
				{
					//  ÀÌÆåÆ® Á¤ÀÇ ¾ÈÇÔ.(¸ð¼Ç¸¸ ¼³Á¤)
				}
				break;
			case snCHAR_SOUND_KELVEZU:
				if (chrAttackTarget)
				{
					if (psModelAnimation->KeyCode != 'P')
					{
						ParkKelvezuNormal2(this);
						ParkKelvezuHit(chrAttackTarget);
					}
					else
						ParkKelvezuNormal1(chrAttackTarget);
				}
				break;
			case snCHAR_SOUND_DARKPHALANX:
				if (chrAttackTarget)
				{
					auto sPosition = GetMoveLocation(0, 0, 70 * fONE, 0, Angle.y, 0);
					StartEffectMonster(pX + sPosition.iX, pY + 42 * fONE, pZ + sPosition.iZ, MONSTER_HULK_HIT1);
				}
				break;
			case snCHAR_SOUND_BLOODYKNIGHT:
				if (chrAttackTarget)
				{
					auto sPosition = GetMoveLocation(0, 0, 70 * fONE, 0, Angle.y, 0);
					StartEffectMonster(pX + sPosition.iX, pY + 42 * fONE, pZ + sPosition.iZ, MONSTER_HULK_HIT1);
				}
				break;
			case snCHAR_SOUND_CHIMERA:
				if (chrAttackTarget)
				{
					auto sPosition = GetMoveLocation(0, 0, 70 * fONE, 0, Angle.y, 0);
					StartEffectMonster(pX + sPosition.iX, pY + 42 * fONE, pZ + sPosition.iZ, MONSTER_HULK_HIT1);
				}
				break;
				// »ðÁÒÊ÷
			case snCHAR_SOUND_FIREWORM:
				if (chrAttackTarget)
					ParkAssaParticle_FireWorm(chrAttackTarget, 0);
				break;
			case snCHAR_SOUND_HELLHOUND:
				if (chrAttackTarget)
				{
					ParkAssaParticle_HellHoundNormal(chrAttackTarget);

					auto sPosition = GetMoveLocation(0, 0, 70 * fONE, 0, Angle.y, 0);
					StartEffectMonster(pX + sPosition.iX, pY + 42 * fONE, pZ + sPosition.iZ, MONSTER_HULK_HIT1);
				}
				break;
			case snCHAR_SOUND_DARKMAGE:
				if (chrAttackTarget)
					ParkAssaParticle_DarkMageNormal(this, chrAttackTarget);
				break;
			case snCHAR_SOUND_DARKGUARD:
				if (chrAttackTarget)
				{
					if (CheckShootingTest_LastAttackTime(chrAttackTarget))
					{
						ShootingPosi.x = pX;
						ShootingPosi.y = pY + 38 * fONE;
						ShootingPosi.z = pZ;
						auto sPosition = GetRadian3D(pX, pY + 38 * fONE, pZ, chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ);
						ShootingAngle.x = sPosition.iX;
						ShootingAngle.y = sPosition.iY;
						ShootingAngle.z = Angle.z;
						ShootingFlag = TRUE;
						ShootingCount = 0;
						dwActionItemCode = sinWS1;
					}
					else
						ResetAttackTrans();
				}
				break;
			case snCHAR_SOUND_TEMPLEGUARD:
				if (psModelAnimation->KeyCode != 'I')
					AssaParticle_MonsterIronMorgonHit(this);
				else
				{
					auto sPosition = GetMoveLocation(0, 0, 54 * fONE, 0, Angle.y, 0);
					pos.x = pX + sPosition.iX;
					pos.y = pY + sPosition.iY + 32 * fONE;
					pos.z = pZ + sPosition.iZ;
					AssaParticle_MonsterIronHit1(&pos);
				}
				break;
			case snCHAR_SOUND_SETO:
				if (chrAttackTarget)
				{
					auto sPosition = GetMoveLocation(0, 24 * fONE, 24 * fONE, 0, Angle.y, 0);
					StartEffectMonsterDest(pX + sPosition.iX, pY + sPosition.iY, pZ + sPosition.iZ, chrAttackTarget->pX, chrAttackTarget->pY + 20 * fONE, chrAttackTarget->pZ, MONSTER_PIGON_SHOT1);

					if (((dwPlayTime >> 4) & 1) == 0)
						SkillPlaySound(SKILL_SOUND_SKILL_FIREBALL1, pX, pY, pZ);
					else
						SkillPlaySound(SKILL_SOUND_SKILL_FIREBALL2, pX, pY, pZ);
				}
				break;
			case snCHAR_SOUND_KINGSPIDER:
				if (chrAttackTarget)
				{
					auto sPosition = GetMoveLocation(0, 0, 70 * fONE, 0, Angle.y, 0);
					StartEffectMonster(pX + sPosition.iX, pY + 42 * fONE, pZ + sPosition.iZ, MONSTER_HULK_HIT1);
				}
				break;
			case snCHAR_SOUND_WATERMELON:
				if (chrAttackTarget && psModelAnimation)
				{
					if (psModelAnimation->KeyCode == 'H' || psModelAnimation->KeyCode == 'J')
					{
						auto sPosition = GetMoveLocation(0, 0, 54 * fONE, 0, Angle.y, 0);
						pos.x = pX + sPosition.iX;
						pos.y = pY + sPosition.iY + 32 * fONE;
						pos.z = pZ + sPosition.iZ;
						AssaParticle_MonsterIronHit1(&pos);
					}
				}
				break;
			case snCHAR_SOUND_PUMPKINGHOST:
				if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'H')
				{
					auto sPosition = GetMoveLocation(0, 0, 54 * fONE, 0, Angle.y, 0);
					pos.x = pX + sPosition.iX;
					pos.y = pY + sPosition.iY + 32 * fONE;
					pos.z = pZ + sPosition.iZ;
					AssaParticle_ShelltomWeaponHit(&pos);
				}
				break;
				// Ë«×Ó¶ñÄ§
			case snCHAR_SOUND_DEVILSHY:
				if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'H')
				{
					auto sPosition = GetMoveLocation(0, 0, 64 * fONE, 0, Angle.y, 0);
					pos.x = pX + sPosition.iX;
					pos.y = pY + sPosition.iY + 32 * fONE;
					pos.z = pZ + sPosition.iZ;
					AssaParticle_MonsterIronHit1(&pos);
				}
				break;
			case snCHAR_SOUND_COMA:
				if (chrAttackTarget)
				{
					auto sPosition = GetMoveLocation(0, 0, 68 * fONE, 0, Angle.y, 0);
					StartEffectMonster(pX + sPosition.iX, pY + 22 * fONE, pZ + sPosition.iZ, MONSTER_HULK_HIT1);
				}
				break;
			case smCHAR_SOUND_ICESERPENT:
				AssaParticle_IceserpentHit(this);
				break;
				// º®±ùÊ÷
			case smCHAR_SOUND_ICEWORM:
				if (chrAttackTarget)
					ParkAssaParticle_IceWorm(chrAttackTarget, FALSE);
				// º®±ù¶ñÄ§
			case smCHAR_SOUND_MINEBAT:
				if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'H')
					ParkDevilBirdAttackNormal(chrAttackTarget);
				break;
				// ¿óÉ½»úÐµ
			case smCHAR_SOUND_MINEGOLEM:
				if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'H')
				{
					auto sPosition = GetMoveLocation(0, 0, 75 * fONE, 0, Angle.y, 0);
					StartEffectMonster(pX + sPosition.iX, pY + 48 * fONE, pZ + sPosition.iZ, MONSTER_MINEGOLEM_HIT1);
				}
				break;
				// ±ù¼×¶¾Öë
			case smCHAR_SOUND_TARANTULIKA:
				if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'H')
				{
					auto sPosition = GetMoveLocation(0, 0, 48 * fONE, 0, Angle.y, 0);
					StartEffectMonster(pX + sPosition.iX, pY + 42 * fONE, pZ + sPosition.iZ, MONSTER_MINEGOLEM_HIT1);
				}
				break;
				//¶ñÄ§²®¾ô
			case smCHAR_SOUND_TULLA:
				if (sCharacterData.iMonsterType != MONSTERTYPE_Friendly)
				{
					if (chrAttackTarget)
					{
						auto sPosition = GetMoveLocation(0, 0, 70 * fONE, 0, Angle.y, 0);
						StartEffectMonster(pX + sPosition.iX, pY + 42 * fONE, pZ + sPosition.iZ, MONSTER_HULK_HIT1);
					}
				}
				else
				{
					if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'H')
						ParksinSkillEffect_TullaPiercing(this);
				}
				//¿óÉ½¹ÜÀíÕß
			case smChAR_SOUND_UNDEADMANAGER:
			case smCHAR_SOUND_UNDEADMINER:
				if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'H')
					AssParticle_UnDeadManger(this, 1);
				break;
				//¸±±¾¹ÖÎï
			case smCHAR_SOUND_BILLY:
			case smCHAR_SOUND_HOUND:
			case smCHAR_SOUND_LENA:
			case smCHAR_SOUND_MARIONETTE:
			case smCHAR_SOUND_UNDEADSTALKER:
				if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'H')
				{
					auto sPosition = GetMoveLocation(0, 0, 54 * fONE, 0, Angle.y, 0);
					pos.x = pX + sPosition.iX;
					pos.y = pY + sPosition.iY + 32 * fONE;
					pos.z = pZ + sPosition.iZ;
					AssaParticle_MonsterIronHit1(&pos);
				}
				break;
				// ÑÐ¾¿Ëù±¬ÆÆ±ø
			case smCHAR_SOUND_IBOMBER:
				if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'H')
					StartSkillDest(pX, pY + 30 * fONE, pZ, chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, SKILL_MECHANIC_BOMB);
				break;
				// ÑÐ¾¿Ëù¾¯ÎÀ±ø
			case smCHAR_SOUND_LGUARDIAN:
				if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'H')
					AssaParticle_Effect("Skill3Hit4", chrAttackTarget, 0);
				break;
				// ¸ß¼¶ÇÖÂÔÕß
			case smCHAR_SOUND_IELITE:
				if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'H')
					AssaParticle_Effect("IeliteSkill", chrAttackTarget, 0);
				break;
				// °£¿ËË¹
			case MONSTEREFFECTID_Draxos:
				if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'H')
					AssaParticle_Effect("DraxosHit", chrAttackTarget, 0);
				break;
				//Ë¾Áî¹Ù
			case smCHAR_SOUND_LIZADR_COMMANDER:
				if (chrAttackTarget)
					AssaParticle_Effect("LizardCommanderHit", chrAttackTarget, 0);
				break;
				//ÒÁ´ï
			case smCHAR_SOUND_LIZADR_ELDER:
				if (chrAttackTarget)
					AssaParticle_Effect("LizardElderHit", chrAttackTarget, 0);
				break;
			case smCHAR_SOUND_NIHIL:
				if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'H')
					AssaParticle_Effect("NihilHit", chrAttackTarget, 0);
				break;
			case smCHAR_SOUND_ACERO:
				if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'H')
					AssaParticle_Effect("SoreSword", chrAttackTarget, 0);
				break;
			case smCHAR_SOUND_CHALYBS:
				if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'H')
					AssaParticle_Effect("ChalybsHit", chrAttackTarget, 0);
				break;
			case smCHAR_SOUND_GREEDY:
				if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'H')
					AssaParticle_Effect("GreedyHit1", chrAttackTarget, 0);
				else if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'J')
					AssaParticle_Effect("GreedyHit2", chrAttackTarget, 0);
				break;
			case smCHAR_SOUND_INFERNO:
				if (chrAttackTarget && psModelAnimation)
				{
					if (CheckShootingTest_LastAttackTime(chrAttackTarget) || CheckLocateBox(pX, pY, pZ, chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 80 * fONE))
						StartEffectMonsterDest(pX, pY + 32 * fONE, pZ, chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ, MONSTER_PIGON_INFERNO);
					else
						ResetAttackTrans();
				}
				break;
			case smCHAR_SOUND_RGUARD:
				if (chrAttackTarget)
					AssaParticle_Effect("RGuardHit", chrAttackTarget, 0);
				break;
			case smCHAR_SOUND_DMYSTERY:
				if (chrAttackTarget)
				{
					if (CheckShootingTest_LastAttackTime(chrAttackTarget) || CheckLocateBox(pX, pY, pZ, chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 80 * fONE))
						StartEffectMonsterDest(pX, pY + 32 * fONE, pZ, chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ, MONSTER_PIGON_DMYSTERY);
					else
						ResetAttackTrans();
				}
				break;
			case smCHAR_SOUND_IGNIS:
				if (chrAttackTarget)
					AssaParticle_Effect("MonsterIgnisHit", chrAttackTarget, 0);
				break;
			case smCHAR_SOUND_NAJAN:
				if (chrAttackTarget)
					AssaDarkWaveEffect(this, chrAttackTarget, MONSTER_PIGON_NAJAN);
				break;
			case smCHAR_SOUND_CRIOS:
				if (chrAttackTarget)
					AssaParticle_Effect("CriosHit", chrAttackTarget, 0);
				break;
			case smCHAR_SOUND_WLORD:
				if (chrAttackTarget)
				{
					if (CheckShootingTest_LastAttackTime(chrAttackTarget) || CheckLocateBox(pX, pY, pZ, chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 80 * fONE))
						StartEffectMonsterDest(pX, pY + 32 * fONE, pZ, chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ, MONSTER_PIGON_WLORD);
					else
						ResetAttackTrans();
				}
				break;
			case smCHAR_SOUND_MIDRANDA:
				if (chrAttackTarget)
				{
					if (rand() % 2)
						AssaParticle_Effect("MonsterMidrandaHit2", chrAttackTarget, 0);
					else
						AssaParticle_Effect("MonsterMidrandaHit1", chrAttackTarget, 0);
				}
				break;
			case smCHAR_SOUND_DEY:
				if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'H')
					AssaParticle_Effect("DeyHit", chrAttackTarget, 0);
				break;
			case smCHAR_SOUND_GURKOB:
				if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'H')
					AssaParticle_Effect("GurkobHit", chrAttackTarget, 0);
				break;
			case smCHAR_SOUND_SHOGOTH:
				if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'H')
				{
					StartEffect(chrAttackTarget->pX, chrAttackTarget->pY + 10 * fONE, chrAttackTarget->pZ, EFFECT_NORMAL_HIT1);
					SetDynLight(chrAttackTarget->pX, chrAttackTarget->pY + 10 * fONE, chrAttackTarget->pZ, 40, 0, 0, 0, 400, 10);
				}
				break;
			case smCHAR_SOUND_ARHDYRA:
				if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'H')
					AssaParticle_Effect("ArhdyraHit", chrAttackTarget, 0);
				break;
			case smCHAR_SOUND_SATHLA:
				if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'H')
					AssaParticle_Effect("ShathlaHit", chrAttackTarget, 0);
				break;
			case smCHAR_SOUND_FAUGN:
				if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'H')
					AssaParticle_Effect("FaugnHit", chrAttackTarget, 0);
				break;
			case smCHAR_SOUND_KOON:
				if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'H')
					AssaParticle_Effect("KoonHit", chrAttackTarget, 0);
				break;
			case smCHAR_SOUND_YAGDITHA:
				if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'H')
					AssaParticle_Effect("YagdithaHit1", chrAttackTarget, 0);
				else if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'K')
					AssaParticle_Effect("YagdithaHit2", chrAttackTarget, 0);
				break;
			case smCHAR_SOUND_BLUEMOUNTAIN:
				AssaParticle_BlueMountainHit(this);
				break;
			case smCHAR_SOUND_REDEYE:
				if (chrAttackTarget)
				{
					auto sPosition = GetMoveLocation(0, 0, 24 * fONE, 0, Angle.y, 0);
					pos.x = pX + sPosition.iX;
					pos.y = pY + 64 * fONE;
					pos.z = pZ + sPosition.iZ;
					pos2.x = chrAttackTarget->pX;
					pos2.y = chrAttackTarget->pY + 64 * fONE;
					pos2.z = chrAttackTarget->pZ;
					ParkAssaParticle_RedEye(&pos, &pos2);
				}
				break;
			case smCHAR_SOUND_TURTLEDRAGON:
				ParkAssaParticle_TurtleDragonHit(this, chrAttackTarget);
				break;
			case smCHAR_SOUND_MORGONIA:
				AssaParticle_MorgoniaHit(this);
				break;
			case smCHAR_SOUND_BONEHOUND:
				if (chrAttackTarget)
				{
					AssaParticle_BoneHoundSkill(chrAttackTarget);
					auto sPosition = GetMoveLocation(0, 0, 70 * fONE, 0, Angle.y, 0);
					StartEffectMonster(pX + sPosition.iX, pY + 42 * fONE, pZ + sPosition.iZ, MONSTER_BONEHOUND_HIT);
				}
				break;
			case snCHAR_SOUND_NPC_MORIF:
				if (chrAttackTarget)
				{
					auto sPosition = GetMoveLocation(0, 0, 25 * fONE, 0, Angle.y, 0);
					pos.x = pX + sPosition.iX;
					pos.y = pY + sPosition.iY + 32 * fONE;
					pos.z = pZ + sPosition.iZ;

					pos2.x = chrAttackTarget->pX;
					pos2.y = chrAttackTarget->pY + 12 * fONE;
					pos2.z = chrAttackTarget->pZ;

					AssaParticle_ShelltomShot(&pos, &pos2, rand() % 3);
				}
				break;
			case snCHAR_SOUND_NPC_MOLLYWOLF:
				if (chrAttackTarget)
				{
					auto sPosition = GetMoveLocation(0, 0, 25 * fONE, 0, Angle.y, 0);
					pos.x = pX + sPosition.iX;
					pos.y = pY + sPosition.iY + 32 * fONE;
					pos.z = pZ + sPosition.iZ;

					pos2.x = chrAttackTarget->pX;
					pos2.y = chrAttackTarget->pY + 12 * fONE;
					pos2.z = chrAttackTarget->pZ;

					AssaParticle_BamShot(&pos, &pos2);
				}
				break;

			case snCHAR_SOUND_WORLDCUP:
				if (chrAttackTarget)
					ParkAssaParticle_WorldCupMonsterAttack(this, chrAttackTarget);
				break;

			case snCHAR_SOUND_S_F_ELEMENTAL:
				if (chrAttackTarget)
				{
					auto sPosition = GetMoveLocation(0, 0, 25 * fONE, 0, Angle.y, 0);
					pos.x = pX + sPosition.iX;
					pos.y = pY + sPosition.iY + 32 * fONE;
					pos.z = pZ + sPosition.iZ;

					pos2.x = chrAttackTarget->pX;
					pos2.y = chrAttackTarget->pY + 12 * fONE;
					pos2.z = chrAttackTarget->pZ;

					SkillArchMageFireElementalShot(&pos, &pos2);
				}
				break;
			case snCHAR_SOUND_S_METALGOLEM:
				if (chrAttackTarget)
				{
					auto sPosition = !sCharacterData.sSize ?
						GetMoveLocation(0, 0, 54 * fONE, 0, Angle.y, 0) : 
						GetMoveLocation(0, 0, 54 * sCharacterData.sSize, 0, Angle.y, 0);

					StartEffectMonster(pX + sPosition.iX, pY + 48 * fONE, pZ + sPosition.iZ, MONSTER_HULK_HIT1);
				}
				break;
			case snCHAR_SOUND_S_WOLVERLIN:
				if (chrAttackTarget)
				{
					auto sPosition = !sCharacterData.sSize ?
						GetMoveLocation(0, 0, 50 * fONE, 0, Angle.y, 0) :
						GetMoveLocation(0, 0, 50 * sCharacterData.sSize, 0, Angle.y, 0);

					x = pX + sPosition.iX;
					z = pZ + sPosition.iZ;
					y = pY + 18 * fONE;
					StartEffectMonster(x, y, z, MONSTER_PIGON_PARTICLE1);
					StartEffectMonster(x, y, z, MONSTER_PIGON_PARTICLE1);
					StartEffectMonster(x, y, z, MONSTER_PIGON_PARTICLE1);
					StartEffectMonster(x, y, z, MONSTER_PIGON_PARTICLE1);
				}
				break;
			case snCHAR_SOUND_S_ARCUDA:
				if (chrAttackTarget)
				{
					auto sPosition = !sCharacterData.sSize ?
						GetMoveLocation(0, 0, 54 * fONE, 0, Angle.y, 0) :
						GetMoveLocation(0, 0, 54 * sCharacterData.sSize, 0, Angle.y, 0);

					StartEffectMonster(pX + sPosition.iX, pY + 48 * fONE, pZ + sPosition.iZ, MONSTER_HULK_HIT1);
				}
				break;
			case snCHAR_SOUND_NPC_SKILLMASTER:
				if (chrAttackTarget && GetAttackPoint(&x, &y, &z) == TRUE)
				{
					StartEffect(x, y, z, EFFECT_CRITICAL_HIT1);
					SetDynLight(x, y, z, 40, 0, 0, 0, 400);
				}
				break;
			case snCHAR_SOUND_NPC_MAGICMASTER:
				if (chrAttackTarget)
				{
					auto sPosition = GetMoveLocation(0, 0, 25 * fONE, 0, Angle.y, 0);
					StartEffectMonsterDest(pX + sPosition.iX, pY + 32 * fONE, pZ + sPosition.iZ, chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ, MONSTER_IMP_SHOT1);
				}
				break;
			case snCHAR_SOUND_CASTLE_CRYSTAL_R:
				if (chrAttackTarget) {
					y = GetRadian2D(pX, pZ, chrAttackTarget->pX, chrAttackTarget->pZ);
					auto sPosition = GetMoveLocation(0, 0, 16 * fONE, 0, y, 0);
					pos.x = pX + sPosition.iX;
					pos.y = pY + sPosition.iY + 136 * fONE;
					pos.z = pZ + sPosition.iZ;
					pos2.x = chrAttackTarget->pX;
					pos2.y = chrAttackTarget->pY + 12 * fONE;
					pos2.z = chrAttackTarget->pZ;
					AssaParticle_FireShot(&pos, &pos2);

					if ((rand() % 2) == 0)
						SkillPlaySound(SKILL_SOUND_SKILL_FIREBOLT1, pos.x, pos.y, pos.z);
					else
						SkillPlaySound(SKILL_SOUND_SKILL_FIREBOLT2, pos.x, pos.y, pos.z);
				}
				break;
			case snCHAR_SOUND_CASTLE_CRYSTAL_G:
				if (chrAttackTarget) {
					y = GetRadian2D(pX, pZ, chrAttackTarget->pX, chrAttackTarget->pZ);
					auto sPosition = GetMoveLocation(0, 0, 16 * fONE, 0, y, 0);
					pos.x = pX + sPosition.iX;
					pos.y = pY + sPosition.iY + 136 * fONE;
					pos.z = pZ + sPosition.iZ;
					pos2.x = chrAttackTarget->pX;
					pos2.y = chrAttackTarget->pY + 12 * fONE;
					pos2.z = chrAttackTarget->pZ;
					AssaParticle_LightShot(&pos, &pos2);

					if ((rand() % 2) == 0)
						SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_MAGIC_LIGHTNING1, pos.x, pos.y, pos.z);
					else
						SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_MAGIC_LIGHTNING2, pos.x, pos.y, pos.z);
				}
				break;
			case snCHAR_SOUND_CASTLE_CRYSTAL_B:
				if (chrAttackTarget)
				{
					y = GetRadian2D(pX, pZ, chrAttackTarget->pX, chrAttackTarget->pZ);
					auto sPosition = GetMoveLocation(0, 0, 16 * fONE, 0, y, 0);
					pos.x = pX + sPosition.iX;
					pos.y = pY + sPosition.iY + 136 * fONE;
					pos.z = pZ + sPosition.iZ;
					pos2.x = chrAttackTarget->pX;
					pos2.y = chrAttackTarget->pY + 12 * fONE;
					pos2.z = chrAttackTarget->pZ;
					AssaParticle_IceShot(&pos, &pos2);

					if ((rand() % 2) == 0)
						SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_MAGIC_ICE1, pos.x, pos.y, pos.z);
					else
						SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_MAGIC_ICE2, pos.x, pos.y, pos.z);
				}
				break;
			case snCHAR_SOUND_CASTLE_SOLDER_A:
			case snCHAR_SOUND_CASTLE_SOLDER_B:
			case snCHAR_SOUND_CASTLE_SOLDER_C:
				if (chrAttackTarget && GetAttackPoint(&x, &y, &z) == TRUE)
				{
					StartEffect(x, y, z, EFFECT_CRITICAL_HIT1);
					SetDynLight(x, y, z, 40, 0, 0, 0, 400);
				}
				break;
			case snCHAR_SOUND_REVIVED_ARCHER:
				if (chrAttackTarget)
				{
					if (CheckShootingTest_LastAttackTime(chrAttackTarget))
					{
						ShootingPosi.x = pX;
						ShootingPosi.y = pY + 38 * fONE;
						ShootingPosi.z = pZ;
						auto sPosition = GetRadian3D(pX, pY + 38 * fONE, pZ, chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ);
						ShootingAngle.x = sPosition.iX;
						ShootingAngle.y = sPosition.iY;
						ShootingAngle.z = Angle.z;
						ShootingFlag = TRUE;
						ShootingCount = 0;
						dwActionItemCode = sinWS1;
					}
					else
						ResetAttackTrans();
				}
				break;

			}
			if (this != lpCurPlayer)
				PlayAttack();

			if (sCharacterData.iType != CHARACTERTYPE_Player && iCharacterType != CHARACTERTYPE_Player)
				return TRUE;

			if (!ShootingMode)
			{
				if (GetAttackPoint(&x, &y, &z) == TRUE)
				{
					if (WeaponEffect)
					{
						pos.x = x;
						pos.y = y;
						pos.z = z;

						switch (WeaponEffect)
						{
						case (sITEMINFO_LIGHTING + 1):
							AssaParticle_LightHit1(&pos);
							SetDynLight(x, y, z, 0, 0, 100, 0, 200);
							if ((rand() % 2) == 0)
								SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_LIGHTNING1, pX, pY, pZ);
							else
								SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_LIGHTNING2, pX, pY, pZ);

							break;
						case (sITEMINFO_FIRE + 1):
							AssaParticle_FireHit1(&pos);
							SetDynLight(x, y, z, 100, 0, 0, 0, 200);
							if ((rand() % 2) == 0)
								SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_FIRE1, pX, pY, pZ);
							else
								SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_FIRE2, pX, pY, pZ);
							break;
						case (sITEMINFO_ICE + 1):
							AssaParticle_IceHit1(&pos);
							SetDynLight(x, y, z, 0, 0, 100, 0, 200);
							if ((rand() % 2) == 0)
								SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_ICE1, pX, pY, pZ);
							else
								SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_ICE2, pX, pY, pZ);
							break;
						}
					}
					else
					{
						if (dwActionItemCode)
						{
							if (AttackCritcal == TRUE || AttackEffect)
							{
								StartEffect(x, y, z, EFFECT_CRITICAL_HIT1);
								SetDynLight(x, y, z, 100, 0, 0, 0, 400);
							}
							else
							{
								StartEffect(x, y, z, EFFECT_NORMAL_HIT1);
								SetDynLight(x, y, z, 40, 0, 0, 0, 400);
							}
						}
						else
							StartEffect(x, y, z, EFFECT_NORMAL_HIT1);

						if (dwForceOrbTime > dwPlayTime)
						{
							pos.x = x;
							pos.y = y;
							pos.z = z;

							AssaParticle_ShelltomWeaponHit(&pos);
						}
					}
					if (HvLeftHand.ElementEffect || HvRightHand.ElementEffect)
					{
						pos.x = x;
						pos.y = y;
						pos.z = z;

						if (HvLeftHand.ElementEffect)
							AssaParticle_ElementHit(this, HvLeftHand.ElementEffect, &pos);
						if (HvRightHand.ElementEffect)
							AssaParticle_ElementHit(this, HvRightHand.ElementEffect, &pos);
					}
				}
			}
			else
			{
				wp = (dwActionItemCode&sinITEM_MASK2);
				if (!shootFlag && chrAttackTarget)
				{
					GetAttackPoint(&x, &y, &z);

					if (wp == sinWS1 || wp == sinWT1 || wp == sinWD1 || (dwActionItemCode == (sinTW1 | sin07)))
					{
						if (sCharacterData.iClass == CHARACTERCLASS_Atalanta && (dwDispAppSkill&SKILL_APPMASK_GODLY_SHIELD) && wp == sinWT1)
						{
							pos.x = x;
							pos.y = y;
							pos.z = z;
							pos2.x = chrAttackTarget->pX;
							pos2.y = chrAttackTarget->pY + 24 * fONE;
							pos2.z = chrAttackTarget->pZ;
							SkillFrostJavelin(&pos, &pos2);

							if ((rand() % 2) == 0)
								SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_ICE1, pX, pY, pZ);
							else
								SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_ICE2, pX, pY, pZ);

							return TRUE;
						}

						ShootingPosi.x = x;
						ShootingPosi.y = y;
						ShootingPosi.z = z;

						if (chrAttackTarget)
						{
							auto sPosition = GetRadian3D(x, y, z, chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ);
							ShootingAngle.x = sPosition.iX;
							ShootingAngle.y = sPosition.iY;
							ShootingAngle.z = Angle.z;
						}
						else
						{
							ShootingAngle.x = Angle.x;
							ShootingAngle.y = Angle.y;
							ShootingAngle.z = Angle.z;
						}

						ShootingCount = 0;
						ShootingFlag = TRUE;

						if (AttackSkil)
							ShootingKind = AttackSkil & 0xFF;
						else
							ShootingKind = TRUE;
					}

					if (wp == sinWM1 || wp == sinWN1 || (dwActionItemCode == (sinTW1 | sin05)))
					{
						if (WeaponEffect)
						{
							switch (WeaponEffect)
							{
							case (sITEMINFO_LIGHTING + 1):
								pos.x = x;
								pos.y = y;
								pos.z = z;
								pos2.x = chrAttackTarget->pX;
								pos2.y = chrAttackTarget->pY + 24 * fONE;
								pos2.z = chrAttackTarget->pZ;
								AssaParticle_LightShot(&pos, &pos2);
								if ((rand() % 2) == 0)
									SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_MAGIC_LIGHTNING1, pX, pY, pZ);
								else
									SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_MAGIC_LIGHTNING2, pX, pY, pZ);
								break;
							case (sITEMINFO_FIRE + 1):
								pos.x = x;
								pos.y = y;
								pos.z = z;
								pos2.x = chrAttackTarget->pX;
								pos2.y = chrAttackTarget->pY + 24 * fONE;
								pos2.z = chrAttackTarget->pZ;
								AssaParticle_FireShot(&pos, &pos2);
								if ((rand() % 2) == 0)
									SkillPlaySound(SKILL_SOUND_SKILL_FIREBOLT1, pX, pY, pZ);
								else
									SkillPlaySound(SKILL_SOUND_SKILL_FIREBOLT2, pX, pY, pZ);
								break;
							case (sITEMINFO_ICE + 1):
								pos.x = x;
								pos.y = y;
								pos.z = z;
								pos2.x = chrAttackTarget->pX;
								pos2.y = chrAttackTarget->pY + 24 * fONE;
								pos2.z = chrAttackTarget->pZ;
								AssaParticle_IceShot(&pos, &pos2);
								if ((rand() % 2) == 0)
									SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_MAGIC_ICE1, pX, pY, pZ);
								else
									SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_MAGIC_ICE2, pX, pY, pZ);
								break;
							}
						}
						else
							StartEffectMonsterDest(x, y, z, chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ, MONSTER_IMP_SHOT1);
					}

				}
			}
		}
	}


	return TRUE;

}

extern int MatLight[2];

//¼Õ¿¡ È¿°ú ÁÖ±â ( ÆÄÀÌ°ï ¿ë )
int Unit::StartHandEffect(int Mode)
{
	POINT3D angle;
	POINT3D posi;
	smMATRIX *mWorld;
	int x, y, z;

	if (sCharacterData.iMonsterEffectID == snCHAR_SOUND_FIGON)
	{
		memcpy(&angle, &Angle, sizeof(POINT3D));
		angle.y = (-angle.y + ANGLE_180)&ANGCLIP;

		AnimObjectTree(HvLeftHand.ObjBip, iFrame, angle.x, angle.y, angle.z);
		mWorld = &HvLeftHand.ObjBip->mWorld;
		x = pX + mWorld->_41;
		z = pZ + mWorld->_42;
		y = pY + mWorld->_43;
		StartEffectMonster(x, y, z, MONSTER_PIGON_POWER1);

		AnimObjectTree(HvRightHand.ObjBip, iFrame, angle.x, angle.y, angle.z);
		mWorld = &HvRightHand.ObjBip->mWorld;
		x = pX + mWorld->_41;
		z = pZ + mWorld->_42;
		y = pY + mWorld->_43;
		StartEffectMonster(x, y, z, MONSTER_PIGON_POWER1);
	}
	if (sCharacterData.iMonsterEffectID == smCHAR_SOUND_INFERNO)
	{
		memcpy(&angle, &Angle, sizeof(POINT3D));
		angle.y = (-angle.y + ANGLE_180)&ANGCLIP;

		AnimObjectTree(HvLeftHand.ObjBip, iFrame, angle.x, angle.y, angle.z);
		mWorld = &HvLeftHand.ObjBip->mWorld;
		x = pX + mWorld->_41;
		z = pZ + mWorld->_42;
		y = pY + mWorld->_43;
		StartEffectMonster(x, y, z, MONSTER_PIGON_POWER4);

		AnimObjectTree(HvRightHand.ObjBip, iFrame, angle.x, angle.y, angle.z);
		mWorld = &HvRightHand.ObjBip->mWorld;
		x = pX + mWorld->_41;
		z = pZ + mWorld->_42;
		y = pY + mWorld->_43;
		StartEffectMonster(x, y, z, MONSTER_PIGON_POWER4);
	}
	if (sCharacterData.iMonsterEffectID == snCHAR_SOUND_SEN)
	{
		if (psModelAnimation->iType != ANIMATIONTYPE_Die)
		{
			memcpy(&angle, &Angle, sizeof(POINT3D));
			angle.y = (-angle.y + ANGLE_180)&ANGCLIP;

			AnimObjectTree(HvLeftHand.ObjBip, iFrame, angle.x, angle.y, angle.z);
			mWorld = &HvLeftHand.ObjBip->mWorld;
			x = pX + mWorld->_41;
			z = pZ + mWorld->_42;
			y = pY + mWorld->_43;

			posi.x = x;
			posi.y = y;
			posi.z = z;
			sinEffect_Sen(&posi);
		}
	}
	if (sCharacterData.iMonsterEffectID == snCHAR_SOUND_MUTANTTREE) {
		if (psModelAnimation->iType != ANIMATIONTYPE_Die) {
			memcpy(&angle, &Angle, sizeof(POINT3D));
			angle.y = (-angle.y + ANGLE_180)&ANGCLIP;

			AnimObjectTree(HvLeftHand.ObjBip, iFrame, angle.x, angle.y, angle.z);
			mWorld = &HvLeftHand.ObjBip->mWorld;
			x = pX + mWorld->_41;
			z = pZ + mWorld->_42;
			y = pY + mWorld->_43;

			posi.x = x;
			posi.y = y + 5 * fONE;
			posi.z = z;
			sinEffect_MutentTree_Smoke(&posi);
		}
	}

	if (sCharacterData.iMonsterEffectID == snCHAR_SOUND_RATOO) {
		if (psModelAnimation->iType != ANIMATIONTYPE_Die) {
			sinEffect_Ratoo_Aura2(this);
		}
	}

	return TRUE;

}

#define SERVER_CHAR_FRAME_STEP			320
#define SERVER_CHAR_SKIP				4

int Unit::Main()
{
	int x, z, y;
	int cnt;
	DWORD compFrame;
	int OldAction;
	int dist;
	POINT3D OldPos;
	Unit *lpChar;
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
		if (psModelAnimation->iType && psModelAnimation->iType < 0x100)
		{
			if (sinChangeSetFlag)
			{
				cInvenTory.ChangeABItem(sinChangeSetFlag);
				sinChangeSetFlag = 0;
			}

			if (sinGetLife() == 0)
			{
				sinSetLife(sCharacterData.sHP.sMax / 2);
				ResetEnergyGraph(0);
			}

			if (PlaySlowCount)
			{
				if (PlaySlowSpeed)
					UserSlowSpeed = PlaySlowSpeed;
				else
					UserSlowSpeed = 128;

				if (PlaySlowSpeed > 200 || PlaySlowSpeed < 0)
					UserSlowSpeed = 128;
			}

			if (MoveFlag == TRUE)
			{
				cnt = sCharacterData.iMovementSpeed - 1;
				if (cnt < 0)
					cnt = 0;
				if (cnt > 8)
					cnt = 8;
				if (cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItem.sItemID.ToInt() == (sinDB1 | sin30) ||
					cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItem.sItemID.ToInt() == (sinDB1 | sin31) ||
					cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItem.sItemID.ToInt() == (sinDB1 | sin32) ||
					cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItem.sItemID.ToInt() == (sinDB1 | sin33) ||
					cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItem.sItemID.ToInt() == (sinDB1 | sin34))
				{
					if (DeleteEventItem_TimeOut(&cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItem) == TRUE)
						cnt = 1;
					else
						cnt = sCharacterData.iMovementSpeed;
				}
				MoveSpeed = 250 + 10 * cnt;

				if (PlaySlowCount)
					MoveSpeed = (MoveSpeed*UserSlowSpeed) >> 8;

				if (MoveCnt > 0)
				{
					MoveCnt--;
					if (MoveCnt <= 0)
						MoveFlag = FALSE;
				}

				OldPos.x = pX;
				OldPos.y = pY;
				OldPos.z = pZ;

				if (!ShootingFlag)
					chrAttackTarget = 0;

				if (!SETTINGHANDLE->Get().bDebugMode && !Pattern2)
					MoveMode = 0;
				if (sCharacterData.sWeight.sMin > sCharacterData.sWeight.sMax)
					MoveMode = 0;

				if (MoveMode == 0 || ShootingFlag || sCharacterData.sSP.sMin == 0)
				{
					if (psModelAnimation->iType != ANIMATIONTYPE_Falling && psModelAnimation->iType != ANIMATIONTYPE_Walking)
						SetMotionFromCode(ANIMATIONTYPE_Walking);

					if (OnStageFieldState != MAPTYPE_Town)
						MoveAngle2((MoveSpeed * 180) >> 8);
					else
						MoveAngle2(MoveSpeed);

					dwLastCharMoveTime = dwPlayTime;
				}
				else
				{
					if (psModelAnimation->iType != ANIMATIONTYPE_Falling && psModelAnimation->iType != ANIMATIONTYPE_Running)
						SetMotionFromCode(ANIMATIONTYPE_Running);

					if (SETTINGHANDLE->Get().bDebugMode && VRKeyBuff[VK_SHIFT])
						MoveAngle2(3000);
					else
						MoveAngle2((MoveSpeed * 460) >> 8);

					dwLastCharMoveTime = dwPlayTime;

					if ((Counter & 0x7) == 0 && WeatherMode < 2)
					{
						if (iLoadedMapIndex >= 0 && STAGE_MAP[iLoadedMapIndex]->iMapID != rsSOD_FIELD &&
							(STAGE_MAP[iLoadedMapIndex]->iMapType == MAPTYPE_Wasteland ||
								STAGE_MAP[iLoadedMapIndex]->iMapType == MAPTYPE_Desert))
						{
							auto sPosition = (Counter & 8) == 0 ? 
								GetMoveLocation(+4 * fONE, 0, 0, 0, Angle.y, 0) : 
								GetMoveLocation(-4 * fONE, 0, 0, 0, Angle.y, 0);

							cnt = 10 + ((dwPlayTime >> 2) & 0xF);
							StartEffect(pX + sPosition.iX, pY + 12 * fONE, pZ + sPosition.iZ, cnt, cnt, EFFECT_DUST1);
						}
					}
				}

				if (OverLapPosi || pX != OldPos.x || pZ != OldPos.z)
				{
					lpChar = CheckOtherPlayPosi(pX, pY, pZ);
					if (lpChar)
					{
						if (!OverLapPosi)
						{
							pX = OldPos.x;
							pZ = OldPos.z;
							if (ActionGameMode)
							{
								if (lpChar->sCharacterData.iType == CHARACTERTYPE_Player)
								{
									if (chrEachMaster != lpChar)
									{
										if (chrEachMaster)
											CloseEachPlayer();
										OpenEachPlayer(lpChar);
									}
									if (chrEachMaster)
										EachTradeButton = TRUE;
								}
							}
						}

						if (CheckOtherPlayPosi(pX, pY, pZ))
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

				if (iLoadedMapIndex >= 0 && STAGE_MAP[iLoadedMapIndex]->iMapID == MAPID_BlessCastle)
				{
					if (pZ<CastleBattleZone_DoorLineZ + 16 * fONE && pZ>CastleBattleZone_DoorLineZ - 48 * fONE && pX > CastleBattleZone_DoorLineX[0] && pX < CastleBattleZone_DoorLineX[1])
					{
						if (rsBlessCastle.CastleMode && rsBlessCastle.DefenceLevel == 0)
						{
							pX = OldPos.x;
							pY = OldPos.y;
							pZ = OldPos.z;
						}
					}
					else
					{
						if (!SETTINGHANDLE->Get().bDebugMode && pZ < CastleBattleZone_BridgeZ && !rsBlessCastle.CastleMode)
						{
							if (!sCharacterData.iClanID || GetClanCode(sCharacterData.iClanID) != rsBlessCastle.dwMasterClan)
							{
								pX = OldPos.x;
								pY = OldPos.y;
								pZ = OldPos.z;
							}
						}
					}
				}

				if (pX == OldPos.x && pY == OldPos.y && pZ == OldPos.z)
				{
					if (TraceMode_DblClick)
					{
						MoveFlag = 0;
						TraceMode_DblClick = 0;
					}
				}

				int limit_FrameStep = 0;

				if (MoveSpeed > 350)
				{
					limit_FrameStep = 350;
					FrameStep = (80 * limit_FrameStep) / 300;
				}
				else
					FrameStep = (80 * MoveSpeed) / 300;
			}
			else
			{
				if (psModelAnimation->iType != ANIMATIONTYPE_Falling && psModelAnimation->iType != ANIMATIONTYPE_Idle)
					SetMotionFromCode(ANIMATIONTYPE_Idle);
				if (PHeight < pY)
					MoveAngle2(0);

				FrameStep = 80;

				if (iFrameTimer == 0)
				{
					if (CheckOtherPlayPosi(pX, pY, pZ))
					{
						OverLapPosi = TRUE;
						OverLapPosi2 = FALSE;
					}
				}
			}
		}

		if (psModelAnimation->iType == ANIMATIONTYPE_Attack || psModelAnimation->iType == ANIMATIONTYPE_Skill)
		{
			if (!MotionLoop)
			{
				FrameStep = (80 * AttackSpeed) >> FLOATNS;

				if (sCharacterData.iClass == CHARACTERCLASS_Priestess && psModelAnimation->ItemCodeCount &&
					ITEMHANDLE->IsItemDataByID(psModelAnimation->ItemCodeList[0], sinWM1 | sin04))
					FrameStep -= 16;
			}
			else
				FrameStep = MotionLoopSpeed;

			if (PlaySlowCount)
				FrameStep = (FrameStep*UserSlowSpeed) >> 8;
		}
		else
		{
			if (psModelAnimation->iType == ANIMATIONTYPE_Flinch || psModelAnimation->iType == ANIMATIONTYPE_Potion)
			{
				FrameStep = 92;

				if (PlaySlowCount)
					FrameStep = (FrameStep*UserSlowSpeed) >> 8;
			}
		}

		if (PlaySlowCount > 0)
		{
			PlaySlowCount--;
			if (PlaySlowCount == 0 && AttackIce != 0)
				AttackIce = -AttackIce;
		}
		if (iDistortion > 0)
			iDistortion--;

		if (PlayWeb > 0)
			PlayWeb--;

		if (PlayVanish > 0)
		{
			PlayVanish--;
			if (PlayVanish <= 0 && dwM_BlurTime)
				dwM_BlurTime = dwPlayTime;
			if ((psModelAnimation->iType == ANIMATIONTYPE_Die) || (iLoadedMapIndex >= 0 && STAGE_MAP[iLoadedMapIndex]->iMapType == MAPTYPE_Town))
				PlayVanish = 0;
		}
		if (iStunTimeLeft > 0)
			iStunTimeLeft--;

		if (AttackIce != 0)
		{
			if (AttackIce > 0 && AttackIce < 160)
				AttackIce++;
			if (AttackIce < 0)
				AttackIce++;
			if ((psModelAnimation->iType == ANIMATIONTYPE_Die) || (iLoadedMapIndex >= 0 && STAGE_MAP[iLoadedMapIndex]->iMapType == MAPTYPE_Town))
				AttackIce = 0;
		}

		if (PlayInvincible > 0)
			PlayInvincible--;

		if (PlayPoison[1] > 0)
		{
			if (DispPoison <= 0)
				DispPoison = 1;
			PlayPoison[1]--;

			if (PlayPoison[0] && (PlayPoison[1] & 1) == 0 && psModelAnimation && psModelAnimation->iType != ANIMATIONTYPE_Die)
			{
				sinSetLife(sinGetLife() - PlayPoison[0]);
				if (sinGetLife() <= 0)
					sinSetLife(1);
			}
		}
		else
		{
			if (DispPoison > 0)
				DispPoison = -DispPoison;
		}
		if (DispPoison != 0)
		{
			if (DispPoison > 0 && DispPoison < 100)
				DispPoison++;
			if (DispPoison < 0)
				DispPoison++;
			if ((psModelAnimation->iType == ANIMATIONTYPE_Die) || (iLoadedMapIndex >= 0 && STAGE_MAP[iLoadedMapIndex]->iMapType == MAPTYPE_Town))
				DispPoison = 0;
		}
		if (PlayFire[1] > 0)
		{
			if (DispFire <= 0)
				DispFire = 1;
			PlayFire[1] --;

			if (PlayFire[0] && (PlayFire[1] & 1) == 0 && psModelAnimation && psModelAnimation->iType != ANIMATIONTYPE_Die)
			{
				sinSetLife(sinGetLife() - PlayFire[0]);
				if (sinGetLife() <= 0)
				{
					sinSetLife(0);
					ZeroMemory(PlayFire, sizeof(PlayFire));
					SetMotionFromCode(ANIMATIONTYPE_Die);
				}
			}
		}
		if (DispFire != 0)
		{
			if (DispFire > 0 && DispFire < 100)
				DispFire++;
			if (DispFire < 0)
				DispFire++;
			if ((psModelAnimation->iType == ANIMATIONTYPE_Die) || (iLoadedMapIndex >= 0 && STAGE_MAP[iLoadedMapIndex]->iMapType == MAPTYPE_Town))
				DispFire = 0;
		}
		if (TalkFrame)
		{
			if (TalkFrame >= lpTalkMotionInfo->EndFrame * 160)
				TalkFrame = 0;
			else
				TalkFrame += 80;
		}
		if (iLoadedMapIndex >= 0)
		{
			if (STAGE_MAP[iLoadedMapIndex]->iMapID == MAPID_T5QuestArena)
			{
				if (psModelAnimation && psModelAnimation->iType != ANIMATIONTYPE_Die)
				{
					if (!PlayFire[1])
					{
						PlayFire[0] = 1;
						PlayFire[1] = 100 * 100;
						PlayDarkBoss = TRUE;
					}
				}
			}
			else
			{
				if (PlayDarkBoss)
				{
					ZeroMemory(PlayFire, sizeof(PlayFire));
					PlayDarkBoss = FALSE;
				}
			}
		}
		if (iLoadedMapIndex >= 0 && psModelAnimation && psModelAnimation->iType != ANIMATIONTYPE_Die)
		{
			if (sCharacterData.iLevel == UNIT_LEVEL_MAX)
				AssParticle_AdvEffect(this);
		}

		if (SETTINGHANDLE->Get().bDebugMode)
		{
			if (Debug_TalkRepeatMode == TRUE && TalkFrame == 0)
			{
				int TalkCnt = 0;
				if (lpTalkModelParent->TalkMotionRate[CHRMOTION_EXT])
				{
					TalkCnt = rand() % 100;
					TalkCnt = lpTalkModelParent->TalkMotionRateCnt[Debug_TalkRepeatModeType][TalkCnt];
				}
				else
					TalkCnt = rand() % lpTalkModelParent->TalkMotionCount;

				lpTalkMotionInfo = &lpTalkModelParent->TalkMotionInfo[TalkCnt];
				TalkFrame = lpTalkMotionInfo->StartFrame * 160;
			}
		}

		iFrame += FrameStep;

		EventAttack();

		if (MoveFlag == TRUE)
		{
			int IsStateIce = 0;

			if (iLoadedMapIndex >= 0)
			{
				if (STAGE_MAP[iLoadedMapIndex]->iMapID != MAPID_AcasiaForest && STAGE_MAP[iLoadedMapIndex]->iMapID != MAPID_BambooForest &&
					STAGE_MAP[iLoadedMapIndex]->iMapID != MAPID_ValleyOfTranquility && STAGE_MAP[iLoadedMapIndex]->iMapID != MAPID_LandOfDusk &&
					STAGE_MAP[iLoadedMapIndex]->iMapID != MAPID_MushroomCave && STAGE_MAP[iLoadedMapIndex]->iMapID != MAPID_DarkSanctuary &&
					STAGE_MAP[iLoadedMapIndex]->iMapID != MAPID_Bellatra && STAGE_MAP[iLoadedMapIndex]->iMapID != MAPID_BlessCastle &&
					STAGE_MAP[iLoadedMapIndex]->iMapID != MAPID_GreedyLake)

					WaterHeight = CLIP_OUT;

				if (lpCurPlayer == this && STAGE_MAP[iLoadedMapIndex]->iMapType == MAPTYPE_Ice)
					IsStateIce = 1;
			}

			if (psModelAnimation->EventFrame[0])
			{
				compFrame = iFrame - (psModelAnimation->StartFrame * 160);
				if (psModelAnimation->EventFrame[0] > (compFrame - FrameStep) && psModelAnimation->EventFrame[0] <= compFrame)
				{
					PlayFootStep(this);

					if (WaterHeight != CLIP_OUT && WaterHeight > pY && WaterHeight < (pY + 32 * fONE) && iLoadedMapIndex >= 0)
					{
						auto sPosition = GetMoveLocation(0, 0, 8 * fONE, 0, Angle.y, 0);
						StartTerrainEffect(pX + sPosition.iX, WaterHeight + 128, pZ + sPosition.iZ, EFFECT_TERRAIN_WAVE);
					}

					else if (IsStateIce)
					{
						auto sPosition = GetMoveLocation(3 * fONE, 0, 5 * fONE, 0, Angle.y, 0);
						SetIceFoot(0, dwPlayTime, sPosition.iX, sPosition.iZ);
					}
				}
			}

			if (psModelAnimation->EventFrame[1])
			{
				compFrame = iFrame - (psModelAnimation->StartFrame * 160);
				if (psModelAnimation->EventFrame[1] > (compFrame - FrameStep) && psModelAnimation->EventFrame[1] <= compFrame)
				{
					PlayFootStep(this);

					if (WaterHeight != CLIP_OUT && WaterHeight > pY && WaterHeight < (pY + 32 * fONE) && iLoadedMapIndex >= 0)
					{
						auto sPosition = GetMoveLocation(0, 0, 8 * fONE, 0, Angle.y, 0);
						StartTerrainEffect(pX + sPosition.iX, WaterHeight + 128, pZ + sPosition.iZ, EFFECT_TERRAIN_WAVE);
					}

					else if (IsStateIce)
					{
						auto sPosition = GetMoveLocation(-3 * fONE, 0, 5 * fONE, 0, Angle.y, 0);
						SetIceFoot(1, dwPlayTime, sPosition.iX, sPosition.iZ);
					}
				}
			}
		}

		if (psModelAnimation->iType == ANIMATIONTYPE_Potion)
		{
			if (psModelAnimation->EventFrame[0])
			{
				compFrame = iFrame - (psModelAnimation->StartFrame * 160);
				if (psModelAnimation->EventFrame[0] > (compFrame - FrameStep) && psModelAnimation->EventFrame[0] <= compFrame)
				{
					if (UseEtherCoreCode)
						PotionLog = POTION_ETHERCORE;
					else
					{
						if (pUsePotion && pUsePotion->sItem.sItemID.ToInt())
							SendUseItemCodeToServer(&pUsePotion->sItem);

						switch (sinUsePotion())
						{
						case 1:
							StartEffect(pX, pY + 48 * fONE, pZ, EFFECT_POTION1);
							PotionLog = 1;
							ResetEnergyGraph(0);
							break;
						case 2:
							StartEffect(pX, pY + 48 * fONE, pZ, EFFECT_POTION2);
							PotionLog = 2;
							ResetEnergyGraph(1);
							break;
						case 3:
							StartEffect(pX, pY + 48 * fONE, pZ, EFFECT_POTION3);
							PotionLog = 3;
							ResetEnergyGraph(2);
							break;
						case 4:
							StartEffect(pX, pY + 48 * fONE, pZ, EFFECT_POTION3);
							StartEffect(pX, pY + 48 * fONE, pZ, EFFECT_POTION2);
							StartEffect(pX, pY + 48 * fONE, pZ, EFFECT_POTION1);
							PotionLog = 4;
							ResetEnergyGraph(3);

							for (cnt = 0; cnt < MAX_UNITS; cnt++)
							{
								if (chrOtherPlayer[cnt].bActive && chrOtherPlayer[cnt].iID && chrOtherPlayer[cnt].dwExclusiveNum && chrOtherPlayer[cnt].psModelAnimation->iType != ANIMATIONTYPE_Die && chrOtherPlayer[cnt].RendSucess)
								{
									x = chrOtherPlayer[cnt].pX;
									y = chrOtherPlayer[cnt].pY + 48 * fONE;
									z = chrOtherPlayer[cnt].pZ;

									StartEffect(x, y, z, EFFECT_POTION1);
									StartEffect(x, y, z, EFFECT_POTION2);
									StartEffect(x, y, z, EFFECT_POTION3);
								}
							}
							break;
						case 5:
							SetMotionFromCode(ANIMATIONTYPE_Flinch);
							CharPlaySound(lpCurPlayer);
							break;
						case 6:
							break;
						case 7:
							SetMotionFromCode(ANIMATIONTYPE_Yahoo);
							break;
						}
					}
					SetDynLight(pX, pY + 48 * fONE, pZ, 50, 100, 70, 0, 250, 1);
				}
			}
		}

		if (iFrame >= psModelAnimation->EndFrame * 160)
		{
			if (psModelAnimation->iType == ANIMATIONTYPE_Die)
			{
				if (g_IsDxProjectZoomIn)
					SetFullZoomMap(0);

				Point3D sPosition;

				if (ReStartOptionIndex)
				{
					if (iLoadedMapIndex >= 0 && ReStartOptionIndex == RESTART_FEILD)
					{
						EMapID iID = STAGE_MAP[iLoadedMapIndex]->iMapID;

						sPosition = GAMEMAP->WarpMap(iID == MAPID_Bellatra ? MAPID_NaviskoTown : iID, pX, pZ);

						if (!PlayUsed_Resurrection)
							ContGameExp(this);
						PlayUsed_Resurrection = 0;
						RestartPlayCount = 700;
					}

					if (ReStartOptionIndex == RESTART_TOWN)
					{
						if (iLoadedMapIndex >= 0 && STAGE_MAP[iLoadedMapIndex]->iMapType == MAPTYPE_BlessCastle &&
							sCharacterData.iClanID && GetClanCode(sCharacterData.iClanID) == rsBlessCastle.dwMasterClan)
							sPosition = GAMEMAP->WarpCastle();
						else
							sPosition = GAMEMAP->WarpMap();

						RestartPlayCount = 700;		//10Ãë
						PlayUsed_Resurrection = 0;
					}

					if (ReStartOptionIndex == RESTART_EXIT)
					{
						CheckCharForm();
						sinSetLife(0);
						ResetEnergyGraph(0);

						quit = TRUE;
						SaveGameData();
						QuitSave = TRUE;
						PlayUsed_Resurrection = 0;
					}
					else
					{
						SetPosi(sPosition.iX, 0, sPosition.iZ, 0, 0, 0);
						TraceCameraPosi.x = pX;
						TraceCameraPosi.y = pY;
						TraceCameraPosi.z = pZ;
						TraceTargetPosi.x = pX;
						TraceTargetPosi.y = pY;
						TraceTargetPosi.z = pZ;

						if (sCharacterData.iType == CHARACTERTYPE_Monster)
							SetMotionFromCode(ANIMATIONTYPE_Idle);
						else
						{
							SetMotionFromCode(ANIMATIONTYPE_Revive);
							StartEffect(pX, pY, pZ, EFFECT_GAME_START1);
							SetDynLight(pX, pY, pZ, 100, 100, 100, 0, 200);
							CharPlaySound(this);
						}
						dwBattleTime = 0;
						dwBattleQuitTime = 0;

						iLoadedMapIndex = -1;
						if (smGameStage[0])
						{
							cnt = smGameStage[0]->GetFloorHeight(pX, pY, pZ, Pattern->SizeHeight);
							lpCurPlayer->iLoadedMapIndex = 0;
						}
						if (cnt == CLIP_OUT && smGameStage[1])
							lpCurPlayer->iLoadedMapIndex = 1;
					}

					CheckCharForm();
					sinSetLife(sCharacterData.sHP.sMax / 2);
					ResetEnergyGraph(0);
					ReformCharForm();
					MoveFlag = FALSE;

					ReStartOptionIndex = 0;
					ReStartFlag = 0;
				}
				else
					iFrame = psModelAnimation->EndFrame * 160 - 80;

				if (cTrade.OpenFlag && !dwTradeMaskTime)
				{
					SendRequestTrade(cTrade.TradeCharCode, 3);
					cTrade.CancelTradeItem();
				}

				if (iFrameTimer >= 70 * 10 && lpCurPlayer->iLoadedMapIndex >= 0)
				{
					Item *lpItemInfo = 0;

					if (STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapType == MAPTYPE_BlessCastle)
						lpItemInfo = FindItemFromCode(sinBC1 | sin05);

					if (lpItemInfo || PlayUsed_Resurrection)
					{
						if (lpItemInfo)
						{
							SendUseItemCodeToServer(lpItemInfo);
							cInvenTory.DeleteInvenItemToServer(lpItemInfo->sItemID.ToInt(), lpItemInfo->iChk1, lpItemInfo->iChk2);
						}

						lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Revive);
						StartEffect(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, EFFECT_GAME_START1);
						SetDynLight(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 100, 100, 100, 0, 200);
						CharPlaySound(lpCurPlayer);

						sinSetLife(lpCurPlayer->sCharacterData.sHP.sMax / 2);
						ResetEnergyGraph(4);
						lpCurPlayer->MoveFlag = FALSE;
						RestartPlayCount = 350;
						ReStartFlag = 0;
						PlayUsed_Resurrection = 0;
					}
				}
			}
			else
			{
				if (MotionLoop)
					MotionLoop--;

				if (psModelAnimation->iType == ANIMATIONTYPE_Yahoo)
					SendClanYahooMotion();

				if (psModelAnimation->iType == ANIMATIONTYPE_Potion)
				{
					if (UseEtherCoreCode)
					{
						if (iLoadedMapIndex < 0 || (STAGE_MAP[iLoadedMapIndex]->iMapID != MAPID_Bellatra && STAGE_MAP[iLoadedMapIndex]->iMapType != MAPID_QuestArena))
						{
							Point3D sPosition;
							switch (UseEtherCoreCode)
							{
							case sinEC1 | sin01:
								SaveGameData();
								sPosition = GAMEMAP->WarpMap(MAPID_RicartenTown, TRUE);
								break;
							case sinEC1 | sin02:
								SaveGameData();
								sPosition = GAMEMAP->WarpMap(MAPID_NaviskoTown, TRUE);
								break;
							case sinEC1 | sin04:
								SaveGameData();
								sPosition = GAMEMAP->WarpMap(MAPID_PhillaiTown, TRUE);
								break;
							}

							SetPosi(sPosition.iX, 0, sPosition.iZ, 0, 0, 0);
							TraceCameraPosi.x = pX;
							TraceCameraPosi.y = pY;
							TraceCameraPosi.z = pZ;
							TraceTargetPosi.x = pX;
							TraceTargetPosi.y = pY;
							TraceTargetPosi.z = pZ;

							StartEffect(pX, pY + 48 * fONE, pZ, EFFECT_RETURN1);
							SkillPlaySound(SKILL_SOUND_LEARN, pX, pY, pZ);
							RestartPlayCount = 700;
						}
						MoveFlag = 0;
						MouseButton[0] = 0;
						dwNextMotionCode = 0;
						UseEtherCoreCode = 0;
					}
					else
						ComparePotion();
				}

				if (lpTransVirtualPotion)
				{
					x = (sCharacterData.sHP.sMax * 40) / 100;
					if (lpTransVirtualPotion->WParam < x)
						x = lpTransVirtualPotion->WParam;
					sinSetLife(sinGetLife() + x);

					sinSetMana(sinGetMana() + lpTransVirtualPotion->LParam);
					sinSetStamina(sinGetStamina() + lpTransVirtualPotion->SParam);
					ResetEnergyGraph(3);

					ZeroMemory(lpTransVirtualPotion, sizeof(smTRANS_COMMAND));
					delete lpTransVirtualPotion;
					lpTransVirtualPotion = 0;
				}

				if (sinChangeSetFlag && !MotionLoop)
				{
					cInvenTory.ChangeABItem(sinChangeSetFlag);
					sinChangeSetFlag = 0;
				}

				if (dwNextMotionCode && !MotionLoop)
				{
					if (SetMotionFromCode(dwNextMotionCode) == FALSE)
						SetMotionFromCode(ANIMATIONTYPE_Idle);
					else
					{
						if (UseEtherCoreCode && dwNextMotionCode == ANIMATIONTYPE_Potion)
						{
							StartEffect(pX, pY + 48 * fONE, pZ, EFFECT_RETURN1);
							SkillPlaySound(SKILL_SOUND_LEARN, pX, pY, pZ);
						}
					}
					dwNextMotionCode = 0;
				}
				else
				{
					if (psModelAnimation->iType == ANIMATIONTYPE_Attack || psModelAnimation->iType == ANIMATIONTYPE_Skill)
					{
						if (psModelAnimation->iType == ANIMATIONTYPE_Skill && AttackSkil)
							EndSkill();

						if (AttackSkil && MotionLoop)
						{
							iFrame = psModelAnimation->StartFrame * 160;
							PlaySkillLoop(AttackSkil, this);
						}
						else
						{
							if (!AttAutoCont && MouseButton[0] == 0 && MouseButton[1] == 0 && lpCharMsTrace && lpCharMsTrace == chrAttackTarget)
							{
								if (CancelAttack() == TRUE)
									MoveFlag = FALSE;
							}
							if (MoveFlag && !MsTraceMode)
								Angle.y = GetPlayMouseAngle();
						}
					}
					else
					{
						if (psModelAnimation->iType == ANIMATIONTYPE_Potion)
						{
							if (!AttAutoCont && MouseButton[0] == 0 && MouseButton[1] == 0 && lpCharMsTrace && lpCharMsTrace == chrAttackTarget)
							{
								if (CancelAttack() == TRUE)
									MoveFlag = FALSE;
							}
						}
					}
					if (psModelAnimation->Repeat == TRUE)
						iFrame = (psModelAnimation->StartFrame * 160) + (iFrame - psModelAnimation->EndFrame * 160);
					else
					{
						if (MotionLoop == NULL)
						{
							if (dwNextMotionCode)
							{
								if (SetMotionFromCode(dwNextMotionCode) == FALSE)
									SetMotionFromCode(ANIMATIONTYPE_Idle);
								dwNextMotionCode = 0;
							}
							else
								SetMotionFromCode(ANIMATIONTYPE_Idle);
						}
					}
				}
			}

			AttackSpeed = GetAttackSpeedMainFrame(sCharacterData.iAttackSpeed);

			if (dwActionItemTwoHand)
				AttackSpeed += 16;

			for (cnt = 0; cnt < SIN_MAX_SKILL_LIST; cnt++)
			{
				if (ContinueSkill[cnt].Flag)
				{
					switch (ContinueSkill[cnt].CODE)
					{
						//´ÌÉ±Ö®¸«
					case SKILL_SWIFT_AXE:
						if ((dwActionItemCode&sinITEM_MASK2) == sinWA1)
						{
							x = ContinueSkill[cnt].Point - 1;
							if (x >= 0 && x < 10)
								AttackSpeed += (AttackSpeed * Swift_Axe_Speed[x]) / 100;
						}
						break;
						// ¿ìËÙ´ò»÷
					case SKILL_H_SONIC:
						if (dwActionItemCode)
						{
							x = ContinueSkill[cnt].Point - 1;
							if (x >= 0 && x < 10)
								AttackSpeed += (AttackSpeed * H_Sonic_Speed[x]) / 100;
						}
						break;
						//Ãô½Ý´óÊ¦
					case SKILL_INPES:
						if ((dwActionItemCode&sinITEM_MASK2) == sinWD1)
						{
							x = ContinueSkill[cnt].Point - 1;
							if (x >= 0 && x < 10)
								AttackSpeed += (AttackSpeed * Inpes_Atk_Speed[x]) / 100;
						}
						break;
						//Ã×µÂÀ¼´ï
					case SKILL_ADVENT_MIDRANDA:
						if (dwActionItemCode)
						{
							x = ContinueSkill[cnt].Point - 1;
							if (x >= 0 && x < 10)
								AttackSpeed += (AttackSpeed * Advent_Midranda_Speed[x]) / 100;
						}
						break;
					}
				}
			}

			if (MotionLoop == NULL)
				AttackEffect = 0;

			MotionEvent = 0;
		}

		if (AttackAnger > 0)
			AttackAnger--;

		if (dwWeaponEffectTime)
		{
			if (dwWeaponEffectTime < dwPlayTime)
			{
				dwWeaponEffectTime = 0;
				WeaponEffect = 0;
			}
		}

		wStickItems[smPLAYBUFF_ITEM_SKIL] = AttackSkil;

		if (WaterHeight != CLIP_OUT && WaterHeight > pY && WaterHeight < (pY + 32 * fONE) && iLoadedMapIndex >= 0)
		{
			dist = 0;
			cnt = 0x3F;
			switch (psModelAnimation->iType)
			{
			case ANIMATIONTYPE_Walking:
				cnt = 0x1F;
				dist = 8;
				break;
			case ANIMATIONTYPE_Running:
				dist = 14;
			case ANIMATIONTYPE_Attack:
			case ANIMATIONTYPE_Skill:
				cnt = 0xF;
				break;
			}

			if ((Counter&cnt) == 0)
			{
				auto sPosition = GetMoveLocation(0, 0, dist << FLOATNS, 0, Angle.y, 0);
				StartTerrainEffect(pX + sPosition.iX, WaterHeight + 128, pZ + sPosition.iZ, EFFECT_TERRAIN_WAVE);
			}
		}

		SavePlayBuff();
		break;

	case 1:
		break;
	case 5:
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
						x = (pX - PosiAround.x) >> FLOATNS;
						z = (pZ - PosiAround.z) >> FLOATNS;
						dist = x * x + z * z;
						if (dist > DistAroundDbl)
							SetTargetPosi(PosiAround.x >> FLOATNS, PosiAround.z >> FLOATNS);
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
						x = (pX - PosiAround.x) >> FLOATNS;
						z = (pZ - PosiAround.z) >> FLOATNS;
						dist = x * x + z * z;

						if (dist > DistAroundDbl)
							SetTargetPosi(PosiAround.x >> FLOATNS, PosiAround.z >> FLOATNS);
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
						x = (pX - PosiAround.x) >> FLOATNS;
						z = (pZ - PosiAround.z) >> FLOATNS;
						dist = x * x + z * z;

						if (dist > DistAroundDbl)
							SetTargetPosi(PosiAround.x >> FLOATNS, PosiAround.z >> FLOATNS);
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

								if (DistAroundDbl)
									SetMotionFromCode(ANIMATIONTYPE_Walking);
								else
									SetMotionFromCode(ANIMATIONTYPE_Idle);
							}
						}
						else
							SetMotionFromCode(ANIMATIONTYPE_Idle);

						if (psModelAnimation->iType == ANIMATIONTYPE_Walking)
						{
							x = (pX - PosiAround.x) >> FLOATNS;
							z = (pZ - PosiAround.z) >> FLOATNS;
							dist = x * x + z * z;

							if (dist > DistAroundDbl)
								SetTargetPosi(PosiAround.x >> FLOATNS, PosiAround.z >> FLOATNS);
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

		if (iPlayBuffCount == PlayBuffPosi_End)
		{
			if (psModelAnimation->iType != ANIMATIONTYPE_Idle &&
				psModelAnimation->iType != ANIMATIONTYPE_Die &&
				psModelAnimation->iType != ANIMATIONTYPE_Special &&
				psModelAnimation->iType != ANIMATIONTYPE_Attack &&
				psModelAnimation->iType != ANIMATIONTYPE_Skill)
				SetMotionFromCode(ANIMATIONTYPE_Idle);

			iFrame += 80;
			compFrame = iFrame / 160;

			if (compFrame >= psModelAnimation->EndFrame)
			{
				if (psModelAnimation->Repeat)
					ChangeMotion(action, AnimDispMode);
				else
					iFrame = (psModelAnimation->EndFrame) * 160;

				if (psModelAnimation->iType == ANIMATIONTYPE_Attack || psModelAnimation->iType == ANIMATIONTYPE_Skill)
					SetMotionFromCode(ANIMATIONTYPE_Idle);

			}
		}
		else
		{
			auto psPlayBuff = &sPlayBuff[iPlayBuffCount & PLAYBUFF_MASK];
			OldAction = action;

			Angle.x = psPlayBuff->saAngle[0];
			Angle.y = psPlayBuff->saAngle[1];
			Angle.z = psPlayBuff->saAngle[2];
			action = psPlayBuff->saAngle[3];

			if (!action)
			{
				action = OldAction;

				x = abs(pX - psPlayBuff->iX);
				y = abs(pY - psPlayBuff->iY);
				z = abs(pZ - psPlayBuff->iZ);

				cnt = x + y + z;

				if (cnt > 32)
				{
					if (psModelAnimation->iType != ANIMATIONTYPE_Walking && psModelAnimation->iType != ANIMATIONTYPE_Running)
					{
						if (cnt < 512)
							SetMotionFromCode(ANIMATIONTYPE_Walking);
						else
						{
							if (!SetMotionFromCode(ANIMATIONTYPE_Running))
								SetMotionFromCode(ANIMATIONTYPE_Walking);
						}
					}
				}
				else
				{
					if (psModelAnimation->iType != ANIMATIONTYPE_Idle)
						SetMotionFromCode(ANIMATIONTYPE_Idle);
				}
			}

			pX = psPlayBuff->iX;
			pY = psPlayBuff->iY;
			pZ = psPlayBuff->iZ;

			PHeight = pY;

			if (!psPlayBuff->dwTargetSerial)
				chrAttackTarget = 0;
			else
			{
				if (chrAttackTarget && chrAttackTarget->iID == psPlayBuff->dwTargetSerial)
				{

				}
				else
					chrAttackTarget = FindChrPlayer(psPlayBuff->dwTargetSerial);
			}

			if (psPlayBuff->dwFrame < smPLAYBUFF_FRAME_NONE)
			{
				iFrame = psPlayBuff->dwFrame & CHAR_FRAME_MASK;
				MotionSelectFrame = psPlayBuff->dwFrame >> CHAR_FRAME_SELSHIFT;

				if (AnimDispMode)
				{
					if (MotionSelectFrame)
						PatDispMode = DISP_MODE_PATSUB;
					else
						PatDispMode = DISP_MODE_PATMAIN;
				}

				if (action)
				{
					if (PatDispMode == DISP_MODE_PATSUB)
						psModelAnimation = &smMotionInfo2->MotionInfo[action];
					else
						psModelAnimation = &smMotionInfo->MotionInfo[action];

					FrameInfo.StartFrame = psModelAnimation->StartFrame * 160;
					FrameInfo.EndFrame = psModelAnimation->EndFrame * 160;
				}

				if (OldMotionState != psModelAnimation->iType)
				{
					if (psModelAnimation->iType >= 0x100 && psModelAnimation->iType != ANIMATIONTYPE_Attack && psModelAnimation->iType != ANIMATIONTYPE_Skill)
						CharPlaySound(this);
					else
					{
						if (sCharacterData.iType == CHARACTERTYPE_Monster && psModelAnimation->iType == ANIMATIONTYPE_Idle && (rand() % 4) == 0)
							CharPlaySound(this);
					}

					if (!MotionEvent && (OldMotionState == ANIMATIONTYPE_Attack || OldMotionState == ANIMATIONTYPE_Skill))
					{
						if (psModelAnimation->EventFrame[0])
						{
							EventAttack();
							dwAttackPlayTime = 0;
							ResetAttackTrans();
						}
						PlayAttack();
					}
					MotionEvent = 0;

					if (psPlayBuff->sStickItems[smPLAYBUFF_ITEM_SKIL] >= 0)
						BeginSkill(psPlayBuff->sStickItems[smPLAYBUFF_ITEM_SKIL], 0, chrAttackTarget, 0, 0, 0);

					if (sCharacterData.iType == CHARACTERTYPE_Monster)
					{
						if (psModelAnimation->iType == ANIMATIONTYPE_Skill)
							BeginSkill(0, 0, chrAttackTarget, 0, 0, 0);

						if (psModelAnimation->iType == ANIMATIONTYPE_Attack)
							BeginAttack_Monster();

						if (OldMotionState == ANIMATIONTYPE_Skill)
							PlayAttack();
					}

					switch (psModelAnimation->iType)
					{
					case ANIMATIONTYPE_Revive:
						StartEffect(pX, pY, pZ, EFFECT_GAME_START1);
						SetDynLight(pX, pY, pZ, 100, 100, 100, 0, 200);
						CharPlaySound(this);
						break;
					case ANIMATIONTYPE_Special:
						if (sCharacterData.iMonsterEffectID == snCHAR_SOUND_WOLVERLIN)
						{
							StartEffect(pX, pY + 48 * fONE, pZ, EFFECT_RETURN1);
							SkillPlaySound(SKILL_SOUND_LEARN, pX, pY, pZ);
							SetDynLight(pX, pY, pZ, 50, 100, 70, 0, 300, 1);
							CharPlaySound(this);
						}
						break;

					case ANIMATIONTYPE_Die:
						iFrameTimer = 0;
						switch (sCharacterData.iMonsterEffectID)
						{
						case snCHAR_SOUND_DEADZONE:
							AssaParticle_MonsterDeadZoneDead(this);
							break;
						case snCHAR_SOUND_HYPERMACHINE:
							AssaParticle_MonsterHyperDead(this);
							break;
						case snCHAR_SOUND_MYSTIC:
							ParkAssaParticle_MisticSpinel(this);
							break;
						case snCHAR_SOUND_DARKMAGE:
							ParkAssaParticle_DarkMageDead(this);
							break;
						case smCHAR_SOUND_SEALCRASHER:
							ParkAssaParticle_SealCrasherl(this);
							break;
						}
						break;
					}
				}
			}
			else
			iFrame += psPlayBuff->dwFrame & 0xFFFF;

			AttackSkil = psPlayBuff->sStickItems[smPLAYBUFF_ITEM_SKIL];
			EventAttack();

			if (sCharacterData.iType != CHARACTERTYPE_Player && (psModelAnimation->iType == ANIMATIONTYPE_Walking || psModelAnimation->iType == ANIMATIONTYPE_Running))
			{
				if (psModelAnimation->EventFrame[0])
				{
					compFrame = iFrame - (psModelAnimation->StartFrame * 160);
					if (psModelAnimation->EventFrame[0] > (compFrame - 80) && psModelAnimation->EventFrame[0] <= compFrame)
						CharPlaySound(this);
				}

				if (psModelAnimation->EventFrame[1])
				{
					compFrame = iFrame - (psModelAnimation->StartFrame * 160);
					if (psModelAnimation->EventFrame[1] > (compFrame - 80) && psModelAnimation->EventFrame[1] <= compFrame)
						CharPlaySound(this);
				}
			}

			FrameStep = 80;

			if (psModelAnimation->iType == ANIMATIONTYPE_Potion)
			{
				if (psModelAnimation->EventFrame[0])
				{
					compFrame = iFrame - (psModelAnimation->StartFrame * 160);

					if (psModelAnimation->EventFrame[0] > (compFrame - FrameStep) && psModelAnimation->EventFrame[0] <= compFrame)
					{
						if (sCharacterData.iType == CHARACTERTYPE_Player)
							cnt = pY + 48 * fONE;
						else
							cnt = pY + PatHeight;

						switch (PotionLog)
						{
						case 1:
							StartEffect(pX, cnt, pZ, EFFECT_POTION1);
							sinPlaySound(SIN_SOUND_EAT_POTION, GetDistVolume(pX, cnt, pZ));
							break;
						case 2:
							StartEffect(pX, cnt, pZ, EFFECT_POTION2);
							sinPlaySound(SIN_SOUND_EAT_POTION, GetDistVolume(pX, cnt, pZ));
							break;
						case 3:
							StartEffect(pX, cnt, pZ, EFFECT_POTION3);
							sinPlaySound(SIN_SOUND_EAT_POTION, GetDistVolume(pX, cnt, pZ));
							break;
						case 4:
							StartEffect(pX, cnt, pZ, EFFECT_POTION3);
							StartEffect(pX, cnt, pZ, EFFECT_POTION2);
							StartEffect(pX, cnt, pZ, EFFECT_POTION1);
							sinPlaySound(SIN_SOUND_EAT_POTION, GetDistVolume(pX, cnt, pZ));
							break;
						case POTION_ETHERCORE:
							StartEffect(pX, pY + 48 * fONE, pZ, EFFECT_RETURN1);
							SkillPlaySound(SKILL_SOUND_LEARN, pX, cnt, pZ);
						}
						SetDynLight(pX, cnt, pZ, 50, 100, 70, 0, 250, 1);
					}
				}
			}

			compFrame = iFrame / 160;

			if (compFrame < psModelAnimation->StartFrame)
				iFrame = psModelAnimation->StartFrame * 160;

			if (compFrame >= psModelAnimation->EndFrame)
			{
				if (psModelAnimation->Repeat)
					ChangeMotion(action, AnimDispMode);
				else
					iFrame = (psModelAnimation->EndFrame) * 160;

				AttackEffect = 0;
			}

			if ((sCharacterData.iType == CHARACTERTYPE_Player || iCharacterType == CHARACTERTYPE_Player) && DisplayFlag)
			{
				if (psPlayBuff->sStickItems[smPLAYBUFF_ITEM_LEFT] != wStickItems[smPLAYBUFF_ITEM_LEFT])
				{
					if (psPlayBuff->sStickItems[smPLAYBUFF_ITEM_LEFT] >= 0)
					{
						ItemData * pItem = ITEMHANDLE->GetItemDataByNumber(psPlayBuff->sStickItems[smPLAYBUFF_ITEM_LEFT]);

						if (pItem)
						{
							SetTool(pItem->sBaseItemID.ToInt(), hvPOSI_LHAND);
							HvLeftHand.ColorBlink = 0;
							HvLeftHand.ColorEffect = 0;
							HvLeftHand.ElementEffect = 0;
						}
					}
					else
						SetTool(0, hvPOSI_LHAND);
				}
				if (psPlayBuff->sStickItems[smPLAYBUFF_ITEM_RIGHT] != wStickItems[smPLAYBUFF_ITEM_RIGHT])
				{
					if (psPlayBuff->sStickItems[smPLAYBUFF_ITEM_RIGHT] >= 0)
					{
						ItemData * pItem = ITEMHANDLE->GetItemDataByNumber(psPlayBuff->sStickItems[smPLAYBUFF_ITEM_RIGHT]);

						if (pItem)
						{
							SetTool(pItem->sBaseItemID.ToInt(), hvPOSI_RHAND);
							HvRightHand.ColorBlink = 0;
							HvRightHand.ColorEffect = 0;
							HvRightHand.ElementEffect = 0;
						}
					}
					else
						SetTool(0, hvPOSI_RHAND);
				}
				if (psPlayBuff->sStickItems[smPLAYBUFF_ITEM_BODY] != wStickItems[smPLAYBUFF_ITEM_BODY])
				{
					SetChrArmor(this, psPlayBuff->sStickItems[smPLAYBUFF_ITEM_BODY]);
					wStickItems[smPLAYBUFF_ITEM_BODY] = psPlayBuff->sStickItems[smPLAYBUFF_ITEM_BODY];
				}
			}

			iPlayBuffCount++;
			MoveCnt = 0;

			if (((psModelAnimation->iType == ANIMATIONTYPE_Attack || psModelAnimation->iType == ANIMATIONTYPE_Flinch) && sCharacterData.iMonsterEffectID == snCHAR_SOUND_MINIG))
			{
				AttackAnger += 2;
				if (AttackAnger > 100) AttackAnger = 100;
			}
			else
			{
				AttackAnger -= 1;
				if (AttackAnger <= 0) AttackAnger = 0;
			}

			if (AttackIce != 0)
			{
				if (AttackIce > 0 && AttackIce < 160)
					AttackIce++;
				if (AttackIce < 0)
					AttackIce++;
				if (psModelAnimation->iType == ANIMATIONTYPE_Die)
					AttackIce = 0;
			}

			if (DispPoison != 0)
			{
				if (DispPoison > 0 && DispPoison < 100)
					DispPoison++;
				if (DispPoison < 0)
					DispPoison++;
				if (psModelAnimation->iType == ANIMATIONTYPE_Die)
					DispPoison = 0;
			}
			if (DispFire != 0)
			{
				if (DispFire > 0 && DispFire < 100)
					DispFire++;
				if (DispFire < 0)
					DispFire++;
				if (psModelAnimation->iType == ANIMATIONTYPE_Die)
					DispFire = 0;
			}
			if (iDistortion > 0)
				iDistortion--;

			if (PlayWeb > 0)
				PlayWeb--;

			if ((iPlayBuffCount & 0x3F) == 0 && sCharacterData.iType != CHARACTERTYPE_Monster)
			{
				iLoadedMapIndex = -1;
				if (smGameStage[0])
				{
					cnt = smGameStage[0]->GetFloorHeight(pX, pY, pZ, Pattern->SizeHeight);
					iLoadedMapIndex = 0;
				}
				if (cnt == CLIP_OUT && smGameStage[1])
					iLoadedMapIndex = 1;
			}

			if (dwAttackPlayTime && dwAttackPlayTime < dwPlayTime)
			{
				PlayAttack(TRUE);
				dwAttackPlayTime = 0;
			}


			OldMotionState = psModelAnimation->iType;

			DisplayFlag = TRUE;
		}

		if (sCharacterData.iMonsterEffectID == snCHAR_SOUND_WOLVERLIN && sCharacterData.iType == CHARACTERTYPE_Monster)
		{
			if ((Counter & 0x1) == 0 && psModelAnimation->iType != ANIMATIONTYPE_Die && psModelAnimation->iType == ANIMATIONTYPE_Running)
			{
				auto sPosition = GetMoveLocation(0, 0, ((rand() % 48) - 24)*fONE, 0, Angle.y, 0);
				sinSetEffect(SIN_PARTICLE_SPOUT, pX + sPosition.iX, pY + 30 * fONE, pZ + sPosition.iZ, 1000, SIN_PARTICLE_COLOR_GOLD);
			}
			if (psModelAnimation->iType == ANIMATIONTYPE_Die)
			{
				if (sAddColorEffect[SMC_R] > 0)
					sAddColorEffect[SMC_R]--;
				if (sAddColorEffect[SMC_G] > 0)
					sAddColorEffect[SMC_G]--;
				if (sAddColorEffect[SMC_B] > 0)
					sAddColorEffect[SMC_B]--;
			}
		}

		if (sCharacterData.sGlow == MONSTER_CLASS_BOSS)
		{
			if (psModelAnimation->iType == ANIMATIONTYPE_Die)
			{
				if (sAddColorEffect[SMC_R] > 0)
					sAddColorEffect[SMC_R]--;
				if (sAddColorEffect[SMC_G] > 0)
					sAddColorEffect[SMC_G]--;
				if (sAddColorEffect[SMC_B] > 0)
					sAddColorEffect[SMC_B]--;
			}
		}

		if (sCharacterData.sSize)
		{
			if (sCharacterData.iMonsterEffectID == snCHAR_SOUND_HOBGOBLIN && sCharacterData.iLevel == 60)
			{
				cnt = ((sCharacterData.sHP.sMax - sCharacterData.sHP.sMin) * 460) / sCharacterData.sHP.sMax;
				cnt += 120;
				sCharacterData.sSize = cnt;
			}
		}

		if (sCharacterData.iMonsterEffectID == snCHAR_SOUND_NPC_MORIF && sCharacterData.iLevel == 60)
		{
			cnt = ((sCharacterData.sHP.sMax - sCharacterData.sHP.sMin) * 700) / sCharacterData.sHP.sMax;
			cnt += 300;
			sCharacterData.sSize = cnt;
		}

		if (sCharacterData.sHP.sMin != DispLifeBar)
		{
			if (DispLifeBar < sCharacterData.sHP.sMin)
				DispLifeBar++;
			else
				DispLifeBar--;
		}

		if (psModelAnimation->iType == ANIMATIONTYPE_Special)
		{
			if (iFrameTimer > 10 && sCharacterData.iMonsterEffectID == snCHAR_SOUND_WOLVERLIN)
			{
				if (sAddColorEffect[SMC_A] > -256)
					sAddColorEffect[SMC_A] -= 8;
				if (sAddColorEffect[SMC_R] > 0)
					sAddColorEffect[SMC_R] -= 8;
				if (sAddColorEffect[SMC_G] > 0)
					sAddColorEffect[SMC_G] -= 8;
				if (sAddColorEffect[SMC_B] > 0)
					sAddColorEffect[SMC_B] -= 8;
				DisplayAlpha = -16;
			}
		}

		if (dwWeaponEffectTime)
		{
			if (dwWeaponEffectTime < dwPlayTime)
			{
				dwWeaponEffectTime = 0;
				WeaponEffect = 0;
			}
		}

		if (PlayVanish > 0)
			PlayVanish--;
		if (PlayInvincible > 0)
			PlayInvincible--;

		if (sCharacterData.iClanID && iClanInfoIndex < 0 &&
			dwClanInfoTime && (dwClanInfoTime + 60 * 1000) < dwPlayTime)
		{
			iClanInfoIndex = ReadClanInfo(sCharacterData.iClanID);
			dwClanInfoTime = dwPlayTime;
		}
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

	if (ShootingFlag)
		ShootingMain();

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


int bb_r, bb_g, bb_b, bb_a;

int SetRenderBlinkColor(smCHARTOOL *smCharTool)
{
	int BlinkMsk;
	int BlinkTime;
	int bTime;
	int Blink, r, g, b, a;

	bb_r = smRender.Color_R;
	bb_g = smRender.Color_G;
	bb_b = smRender.Color_B;
	bb_a = smRender.Color_A;

	if (!smCharTool || smCharTool->ColorBlink == 0)
		return NULL;

	Blink = smCharTool->ColorBlink;

	r = smCharTool->sColors[SMC_R];
	g = smCharTool->sColors[SMC_G];
	b = smCharTool->sColors[SMC_B];
	a = smCharTool->sColors[SMC_A];

	if (Blink < 0)
	{
		smRender.Color_R += r;
		smRender.Color_G += g;
		smRender.Color_B += b;
		smRender.Color_A += a;

		return NULL;
	}

	BlinkTime = (1 << Blink);
	BlinkMsk = BlinkTime - 1;

	bTime = dwPlayTime & BlinkMsk;

	if (dwPlayTime&BlinkTime)
	{
		smRender.Color_R += (bTime*r) >> Blink;
		smRender.Color_G += (bTime*g) >> Blink;
		smRender.Color_B += (bTime*b) >> Blink;
		if (a < 0)
			smRender.Color_A += (bTime*a) >> Blink;
	}
	else
	{
		bTime = BlinkMsk - bTime;
		smRender.Color_R += (bTime*r) >> Blink;
		smRender.Color_G += (bTime*g) >> Blink;
		smRender.Color_B += (bTime*b) >> Blink;

		if (a < 0)
			smRender.Color_A += (bTime*a) >> Blink;
	}

	if (a > 0)
		smRender.Color_A -= a;

	bTime = (bTime*fONE) >> Blink;

	if (!bTime)
		bTime = 1;

	if (smCharTool->TexMixCode >= 0)
		SetItem2PassTexture(smCharTool->TexMixCode, smCharTool->TexScroll);

	return  bTime;
}

int RestoreRenderBlinkColor()
{
	smRender.Color_R = bb_r;
	smRender.Color_G = bb_g;
	smRender.Color_B = bb_b;
	smRender.Color_A = bb_a;

	SetItem2PassTexture(-1);

	return TRUE;
}
int Unit::VirtualDraw()
{
	POINT	sPos;
	POINT3D CameraPosi, CameraAngle;
	int		He;

	if (!DisplayFlag || !psModelAnimation)
		return FALSE;

	if (ActionPattern == 99)
	{
		if (LastPlayDataType)
		{
			if ((dwLastTransTime + DISPLAY_TRANS_TIME_OVER_FAR) < dwPlayTime)
			{
				dwDispAppSkill = 0;
				return TRUE;
			}
		}
		else
		{
			if ((dwLastTransTime + DISPLAY_TRANS_TIME_OVER) < dwPlayTime)
			{
				dwDispAppSkill = 0;
				return TRUE;
			}
		}
	}
	CameraPosi.x = smCHAR_CameraX;
	CameraPosi.y = smCHAR_CameraY;
	CameraPosi.z = smCHAR_CameraZ;

	CameraAngle.x = smCHAR_CameraAngX;
	CameraAngle.y = smCHAR_CameraAngY;
	CameraAngle.z = smCHAR_CameraAngZ;

	He = PatHeight;
	if (He < 44 * fONE)
		He = 44 * fONE;

	smRender.SetCameraPosi(CameraPosi.x, CameraPosi.y, CameraPosi.z, CameraAngle.x, CameraAngle.y, CameraAngle.z);

	RendPoint.z = smRender.GetRect2D(pX, pY + (He >> 1), pZ, 44 * fONE, He, &RendRect2D, &sPos);
	RendPoint.x = sPos.x;
	RendPoint.y = sPos.y;

	if (RendPoint.z > 0 && sPos.x > 0 && sPos.x < (int)RESOLUTION_WIDTH && sPos.y>0 && sPos.y < (int)RESOLUTION_HEIGHT)
	{
		RendSucess = TRUE;
		return TRUE;
	}

	return FALSE;
}

int Unit::Draw()
{
	POINT3D CameraPosi, CameraAngle;
	POINT3D angle;
	smPAT3D *pat;
	POINT	sPos;
	POINT3D	sPos3;
	int		He;

	int dx, dy, dz, dDist;
	_MODELGROUP	*lpModelGroup;

	int	BlinkFlag = 0;
	smMATRIX	Mat;
	int	BlinkLevel;
	int	BlinkScale;

	RendSucess = 0;
	FlagShow = 0;

	if (!DisplayFlag || !psModelAnimation)
		return FALSE;

	if (lpDinaPattern->UseCount <= 0)
	{
		Close();
		return FALSE;
	}
	if (ActionPattern == 99)
	{
		if (LastPlayDataType)
		{
			if ((dwLastTransTime + DISPLAY_TRANS_TIME_OVER_FAR) < dwPlayTime)
			{
				dwDispAppSkill = 0;
				return TRUE;
			}
		}
		else
		{
			if ((dwLastTransTime + DISPLAY_TRANS_TIME_OVER) < dwPlayTime)
			{
				dwDispAppSkill = 0;
				return TRUE;
			}
		}
	}

	FlagShow = TRUE;

	dx = (smCHAR_CameraX - pX) >> FLOATNS;
	dy = (smCHAR_CameraY - pY) >> FLOATNS;
	dz = (smCHAR_CameraZ - pZ) >> FLOATNS;

	dDist = dx * dx + dy * dy + dz * dz;

	CameraPosi.x = smCHAR_CameraX;
	CameraPosi.y = smCHAR_CameraY;
	CameraPosi.z = smCHAR_CameraZ;

	CameraAngle.x = smCHAR_CameraAngX;
	CameraAngle.y = smCHAR_CameraAngY;
	CameraAngle.z = smCHAR_CameraAngZ;

	memcpy(&angle, &Angle, sizeof(POINT3D));
	angle.y = (-angle.y + ANGLE_180)&ANGCLIP;

	if (ActionGameMode)
	{
		if (angle.y > ANGLE_180)
			angle.y = ANGLE_270;
		else
			angle.y = ANGLE_90;
	}

	Posi.x = pX;
	Posi.y = pY;
	Posi.z = pZ;


	Pattern->SetPosi(&Posi, &angle);

	if (Pattern->TmParent && Pattern->TmParent->MaxFrame > (int)iFrame)
		Pattern->Frame = iFrame;
	else
		Pattern->Frame = 80;

	char *ModelNameList[4];

	int	cr, cg, cb, ca, cnt, sR, sG, sB, sA;
	int nl = 0;

	cr = smRender.Color_R;
	cg = smRender.Color_G;
	cb = smRender.Color_B;
	ca = smRender.Color_A;

	if (sCharacterData.iType == CHARACTERTYPE_Monster) //¹ÖÎïµÄHPÐ¡ÓÚ20%µÄÊ±ºò ÑÕÉ«±äºì
	{
		if ((sCharacterData.sHP.sMin * 100 / sCharacterData.sHP.sMax) <= 20 && psModelAnimation->iType != ANIMATIONTYPE_Die)
		{
			sAddColorEffect[SMC_R] = 220;
			sAddColorEffect[SMC_G] = 50;
			sAddColorEffect[SMC_B] = 50;
			sAddColorEffect[SMC_A] = 190;
		}
		else if (psModelAnimation->iType == ANIMATIONTYPE_Die)
		{
			sAddColorEffect[SMC_R] = 50;
			sAddColorEffect[SMC_G] = 50;
			sAddColorEffect[SMC_B] = 50;
			sAddColorEffect[SMC_A] = 190;
		}
	}

	sR = sAddColorEffect[SMC_R];
	sG = sAddColorEffect[SMC_G];
	sB = sAddColorEffect[SMC_B];
	sA = sAddColorEffect[SMC_A];

	if (sCharacterData.sGlow == MONSTER_CLASS_BOSS)
	{
		cnt = Counter & 0x1F;
		if ((Counter & 0x20) == 0)
			cnt = 0x1F - cnt;

		sR = (sR*cnt) >> 5;
		sG = (sG*cnt) >> 5;
		sB = (sB*cnt) >> 5;
	}

	smRender.Color_R = cr + AttackAnger + sR + abs(DispFire);
	smRender.Color_G = cg - (AttackAnger >> 1) + sG + abs(DispPoison);
	smRender.Color_B = cb + abs(AttackIce) + sB;
	smRender.Color_A = ca + DisplayAlpha - (abs(AttackIce) >> 1) + sA;

	if (PlayCurseQuest)
	{
		smRender.Color_R += 100;
		smRender.Color_B += 100;
	}
	if (iDistortion && psModelAnimation->iType != ANIMATIONTYPE_Die)
	{
		smRender.DistortionMesh = TRUE;
		smRender.Color_R += 80;
		smRender.Color_G += 80;
	}
	if (PlayWeb && psModelAnimation->iType != ANIMATIONTYPE_Die)
	{
		smRender.Color_R = 120;
		smRender.Color_G = 120;
		smRender.Color_B = 120;
	}
	if (sCharacterData.sSize)
		smRender.ObjectVertexScale = sCharacterData.sSize;

	if (DarkLevel > 0 && iLoadedMapIndex >= 0 && STAGE_MAP[iLoadedMapIndex]->iMapType == MAPTYPE_Town)
	{
		nl = DarkLevel >> 1;
		smRender.Color_R += nl;
		smRender.Color_G += nl;
		smRender.Color_B += nl;

		if (smRender.nRendLight > 0 && smRender.smRendLight[0].Range == DarkLightRange)
		{
			smRender.smRendLight[0].Range = 0;
			nl = 1;
		}
		else
			nl = 0;
	}

	if (psModelAnimation->iType == ANIMATIONTYPE_Die)
	{
		if (iFrameTimer > 400)
		{
			cnt = 100;
			smRender.Color_R -= cnt;
			smRender.Color_G -= cnt;
			smRender.Color_B -= cnt;
		}
		else
		{
			if (iFrameTimer > 200)
			{
				cnt = (iFrameTimer - 200) >> 1;
				smRender.Color_R -= cnt;
				smRender.Color_G -= cnt;
				smRender.Color_B -= cnt;
			}
		}

		if (sCharacterData.iMonsterEffectID == snCHAR_SOUND_FIGON || sCharacterData.iMonsterEffectID == snCHAR_SOUND_STYGIANLORD || sCharacterData.iMonsterEffectID == snCHAR_SOUND_GUARDIAN_SAINT || sCharacterData.iMonsterEffectID == snCHAR_SOUND_S_F_ELEMENTAL || sCharacterData.iMonsterEffectID == snCHAR_SOUND_CHAOSCARA || sCharacterData.iMonsterEffectID == snCHAR_SOUND_DEVILSHY)
		{
			smRender.Color_A = ca - (iFrameTimer << 1);

			if (smRender.Color_A < -400)
				goto rendSkip;
			DisplayAlpha = 100;
		}
	}

	lpModelGroup = &smMotionInfo->DefaultModel;

	if (dDist < VIEW_HIGH_DIST && smMotionInfo->HighModel.ModelNameCnt)
		lpModelGroup = &smMotionInfo->HighModel;

	if (dDist > VIEW_MID_DIST && smMotionInfo->LowModel.ModelNameCnt)
		lpModelGroup = &smMotionInfo->LowModel;

	if (TalkFrame)
	{
		if (TalkPattern->MaxFrame > (int)TalkFrame)
			TalkPattern->Frame = TalkFrame;
		else
			TalkFrame = 0;
	}
	// äÖÈ¾ÒÂ·þÄ£ÐÍ
	if (PatDispMode&DISP_MODE_PATMAIN)
	{
		if (Pattern->TmParent)
			Pattern->TmParent->TmLastFrame = -1;
		else
			Pattern->TmLastFrame = -1;

		if (lpModelGroup->ModelNameCnt)
		{
			ModelNameList[0] = lpModelGroup->szModelName[0];
			ModelNameList[1] = lpModelGroup->szModelName[1];
			ModelNameList[2] = lpModelGroup->szModelName[2];
			ModelNameList[3] = lpModelGroup->szModelName[3];

			if (TalkFrame && lpTalkMotionInfo->iType)
				RendSucess += Pattern->ChoiseRenderD3D(&CameraPosi, &CameraAngle, ModelNameList, lpModelGroup->ModelNameCnt, TalkPattern, &FrameInfo);
			else
				RendSucess += Pattern->ChoiseRenderD3D(&CameraPosi, &CameraAngle, ModelNameList, lpModelGroup->ModelNameCnt, &FrameInfo);
		}
		else
		{
			if (TalkFrame && lpTalkMotionInfo->iType)
				RendSucess += Pattern->RenderD3D(&CameraPosi, &CameraAngle, TalkPattern, &FrameInfo);
			else
				RendSucess += Pattern->RenderD3D(&CameraPosi, &CameraAngle, &FrameInfo);
		}
	}
	// äÖÈ¾Í·Ä£ÐÍ
	if (lpDinaPattern2 && lpDinaPattern2->lpModelInfo && Pattern2 && (PatDispMode&DISP_MODE_PATSUB))
	{
		lpModelGroup = &lpDinaPattern2->lpModelInfo->DefaultModel;

		if (dDist < VIEW_HIGH_DIST && lpDinaPattern2->lpModelInfo->HighModel.ModelNameCnt)
			lpModelGroup = &lpDinaPattern2->lpModelInfo->HighModel;

		if (dDist > VIEW_MID_DIST && lpDinaPattern2->lpModelInfo->LowModel.ModelNameCnt)
			lpModelGroup = &lpDinaPattern2->lpModelInfo->LowModel;

		Pattern2->SetPosi(&Posi, &angle);

		if (Pattern2->TmParent && Pattern2->TmParent->MaxFrame > (int)iFrame)
			Pattern2->Frame = iFrame;

		if (Pattern2->TmParent)
			Pattern2->TmParent->TmLastFrame = -1;
		else
			Pattern2->TmLastFrame = -1;

		if (lpModelGroup->ModelNameCnt)
		{
			ModelNameList[0] = lpModelGroup->szModelName[0];
			ModelNameList[1] = lpModelGroup->szModelName[1];
			ModelNameList[2] = lpModelGroup->szModelName[2];
			ModelNameList[3] = lpModelGroup->szModelName[3];

			if (TalkFrame && lpTalkMotionInfo->iType)
				RendSucess += Pattern2->ChoiseRenderD3D(&CameraPosi, &CameraAngle, ModelNameList, lpModelGroup->ModelNameCnt, TalkPattern, &FrameInfo);
			else
				RendSucess += Pattern2->ChoiseRenderD3D(&CameraPosi, &CameraAngle, ModelNameList, lpModelGroup->ModelNameCnt, &FrameInfo);
		}
		else
		{
			if (TalkFrame && lpTalkMotionInfo->iType)
				RendSucess += Pattern2->RenderD3D(&CameraPosi, &CameraAngle, TalkPattern, &FrameInfo);
			else
				RendSucess += Pattern2->RenderD3D(&CameraPosi, &CameraAngle, &FrameInfo);
		}
	}

	smRender.ObjectVertexScale = 0;

	if (RendSucess)
	{
		int We = 44 * fONE;
		He = PatHeight;

		if (sCharacterData.sSize)
			He = (He*sCharacterData.sSize) >> FLOATNS;

		if (sCharacterData.iMonsterEffectID == snCHAR_SOUND_KELVEZU)
			We = He * 2;

		if (He < 44 * fONE)
			He = 44 * fONE;

		smRender.SetCameraPosi(CameraPosi.x, CameraPosi.y, CameraPosi.z, CameraAngle.x, CameraAngle.y, CameraAngle.z);

		RendPoint.z = smRender.GetRect2D(pX, pY + (He >> 1), pZ, We, He, &RendRect2D, &sPos);
		RendPoint.x = sPos.x;
		RendPoint.y = sPos.y;
	}

	if (!Pattern->TmParent || !DisplayTools)
	{
		smRender.Color_R = cr;
		smRender.Color_G = cg;
		smRender.Color_B = cb;
		if (nl)
			smRender.smRendLight[0].Range = DarkLightRange;
		return TRUE;
	}

	if (psModelAnimation->iType == ANIMATIONTYPE_Attack && dwPlayTime & 0x20)
		BlinkFlag = TRUE;

	if (BlinkFlag && !ShootingMode)
	{
		smRender.Color_R += 80;
		smRender.Color_G += 80;
		smRender.Color_B += 80;
	}

	Rend_HvLeftHand = TRUE;
	Rend_HvRightHand = TRUE;

	if (sCharacterData.iType == CHARACTERTYPE_Player || iCharacterType == CHARACTERTYPE_Player)
	{
		if (dwItemSetting == 0 || (iLoadedMapIndex >= 0 && STAGE_MAP[iLoadedMapIndex]->iMapType != MAPTYPE_Town && psModelAnimation->iType != ANIMATIONTYPE_Yahoo))
		{
			if (HvLeftHand.PatTool)
			{
				pat = HvLeftHand.PatTool;

				if ((HvLeftHand.dwItemCode&sinITEM_MASK2) == sinDS1)
				{
					if ((dwDispAppSkill&SKILL_APPMASK_SPARK_SHIELD) && PatSparkShield && sCharacterData.iClass == CHARACTERCLASS_Mechanician)
					{
						if (psModelAnimation->iType == ANIMATIONTYPE_Skill && (AttackSkil & 0xFF) == SKILL_PLAY_SPARK_SHIELD && MotionEvent == 0)
							pat = HvLeftHand.PatTool;
						else
							pat = PatSparkShield;
					}
					if ((dwDispAppSkill&SKILL_APPMASK_SPARK_SHIELD) && PatDivineShield && sCharacterData.iClass == CHARACTERCLASS_Knight)
					{
						if (psModelAnimation->iType == ANIMATIONTYPE_Skill && (AttackSkil & 0xFF) == SKILL_PLAY_DIVINE_INHALATION && MotionEvent == 0)
							pat = HvLeftHand.PatTool;
						else
							pat = PatDivineShield;
					}
					if ((dwDispAppSkill&SKILL_APPMASK_GODLY_SHIELD) && PatGodlyShield && sCharacterData.iClass == CHARACTERCLASS_Knight)
					{
						if (psModelAnimation->iType == ANIMATIONTYPE_Skill && (AttackSkil & 0xFF) == SKILL_PLAY_GODLY_SHIELD && MotionEvent == 0)
							pat = HvLeftHand.PatTool;
						else
							pat = PatGodlyShield;
					}
				}
				if (psModelAnimation->iType == ANIMATIONTYPE_Skill && (sCharacterData.iClass == CHARACTERCLASS_Atalanta && ((AttackSkil & 0xFF) == SKILL_PLAY_SHIELD_STRIKE || (AttackSkil & 0xFF) == SKILL_PLAY_SOUL_SUCKER)) && ShieldObjBip)
				{
					pat->LinkParentObject(AnimPattern, ShieldObjBip);

					cr = smRender.Color_R;
					cg = smRender.Color_G;
					cb = smRender.Color_B;

					smRender.Color_R += 100;
					smRender.Color_G += 100;
					smRender.Color_B += 80;
				}
				else
					pat->LinkParentObject(AnimPattern, HvLeftHand.ObjBip);

				pat->SetPosi(&Posi, &angle);
				pat->Frame = iFrame;

				if ((HvLeftHand.dwItemCode & sinITEM_MASK2) == sinWD1)
				{
					if (DaggerObjBip)
					{
						HvLeftHand.ObjBip->mWorld._41 = DaggerObjBip->mWorld._41;
						HvLeftHand.ObjBip->mWorld._42 = DaggerObjBip->mWorld._42;
						HvLeftHand.ObjBip->mWorld._43 = DaggerObjBip->mWorld._43;
					}
				}
				memcpy(&HvLeftHand_Matrix, &HvLeftHand.ObjBip->mWorld, sizeof(smMATRIX));

				if (!HvLeftHand.ColorBlink || !HvLeftHand.sColors[SMC_A])
				{
					BlinkLevel = SetRenderBlinkColor(&HvLeftHand);

					if (HvLeftHand.BlinkScale && BlinkLevel)
					{
						smIdentityMatrix(Mat);
						if (HvLeftHand.BlinkScale < 0)
							BlinkScale = -HvLeftHand.BlinkScale;
						else
							BlinkScale = (BlinkLevel*HvLeftHand.BlinkScale) >> FLOATNS;
						Mat._11 = BlinkScale;
						Mat._22 = BlinkScale;
						Mat._33 = BlinkScale;
						pat->Frame = -1;
						memcpy(&pat->obj3d[0]->mWorld, &HvLeftHand.ObjBip->mWorld, sizeof(smMATRIX));
						smMatrixMult(pat->obj3d[0]->mWorld, Mat, pat->obj3d[0]->mWorld);
					}

					pat->RenderD3D(&CameraPosi, &CameraAngle);
					RestoreRenderBlinkColor();

					if (psModelAnimation->iType == ANIMATIONTYPE_Skill && sCharacterData.iClass == CHARACTERCLASS_Atalanta && (AttackSkil & 0xFF) == SKILL_PLAY_SHIELD_STRIKE && ShieldObjBip)
					{
						smRender.Color_R = cr;
						smRender.Color_G = cg;
						smRender.Color_B = cb;

						sPos3.x = pat->obj3d[0]->mWorld._41 + pX;
						sPos3.z = pat->obj3d[0]->mWorld._42 + pZ;
						sPos3.y = pat->obj3d[0]->mWorld._43 + pY;
						sinEffect_Shield_Strike(&sPos3);
					}
				}
				else
					Rend_HvLeftHand = FALSE;

				pat->LinkParentObject(0, 0);
				pat->TmLastFrame = -1;
			}

			if (HvRightHand.PatTool && !HideWeapon)
			{
				if ((dwActionItemCode&sinITEM_MASK2) == sinWT1 && ShootingFlag)
				{

				}
				else
				{
					if ((HvRightHand.dwItemCode & sinITEM_MASK2) == sinWN1)
					{
						smMATRIX mMatix;

						smIdentityMatrix(mMatix);
						smRotateYMatrix(mMatix, 2250);
						smTranslateMatrix(mMatix, 0, 0, 10);
						smMatrixMult(HvRightHand.ObjBip->mWorld, mMatix, HvRightHand.ObjBip->mWorld);
						Posi.y += 1000;
					}
					pat = HvRightHand.PatTool;
					pat->LinkParentObject(AnimPattern, HvRightHand.ObjBip);

					pat->SetPosi(&Posi, &angle);
					pat->Frame = iFrame;

					memcpy(&HvRightHand_Matrix, &HvRightHand.ObjBip->mWorld, sizeof(smMATRIX));

					if (!HvRightHand.ColorBlink || !HvRightHand.sColors[SMC_A])
					{
						BlinkLevel = SetRenderBlinkColor(&HvRightHand);

						if (HvRightHand.BlinkScale && BlinkLevel)
						{
							smIdentityMatrix(Mat);
							if (HvRightHand.BlinkScale < 0)
								BlinkScale = -HvRightHand.BlinkScale;
							else
								BlinkScale = (BlinkLevel*HvRightHand.BlinkScale) >> FLOATNS;

							Mat._11 = BlinkScale;
							Mat._22 = BlinkScale;
							Mat._33 = BlinkScale;
							pat->Frame = -1;
							memcpy(&pat->obj3d[0]->mWorld, &HvRightHand.ObjBip->mWorld, sizeof(smMATRIX));
							smMatrixMult(pat->obj3d[0]->mWorld, Mat, pat->obj3d[0]->mWorld);
						}

						pat->RenderD3D(&CameraPosi, &CameraAngle);
						RestoreRenderBlinkColor();
					}
					else
						Rend_HvRightHand = FALSE;

					pat->LinkParentObject(0, 0);
					pat->TmLastFrame = -1;
				}
			}
		}
		else
		{
			if (dwActionItemCode)
			{
				BlinkScale = 0;

				if (HvLeftHand.dwItemCode == dwActionItemCode)
				{
					pat = HvLeftHand.PatTool;
					if (!HvLeftHand.ColorBlink || !HvLeftHand.sColors[SMC_A])
					{
						BlinkLevel = SetRenderBlinkColor(&HvLeftHand);

						if (HvLeftHand.BlinkScale && BlinkLevel)
						{
							if (HvLeftHand.BlinkScale < 0)
								BlinkScale = -HvLeftHand.BlinkScale;
							else
								BlinkScale = (BlinkLevel*HvLeftHand.BlinkScale) >> FLOATNS;
							memcpy(&pat->obj3d[0]->mWorld, &HvLeftHand.ObjBip->mWorld, sizeof(smMATRIX));
						}
					}
					else
						Rend_HvLeftHand = FALSE;
				}

				if ((HvRightHand.dwItemCode & sinITEM_MASK2) == sinWN1)
				{
					smMATRIX mMatix;

					smIdentityMatrix(mMatix);
					smRotateYMatrix(mMatix, 2250);
					smTranslateMatrix(mMatix, 0, 0, 10);
					smMatrixMult(HvRightHand.ObjBip->mWorld, mMatix, HvRightHand.ObjBip->mWorld);
					Posi.y += 1000;
				}

				if (HvRightHand.dwItemCode == dwActionItemCode)
				{
					pat = HvRightHand.PatTool;
					if (!HvRightHand.ColorBlink || !HvRightHand.sColors[SMC_A])
					{
						BlinkLevel = SetRenderBlinkColor(&HvRightHand);

						if (HvRightHand.BlinkScale && BlinkLevel)
						{
							if (HvRightHand.BlinkScale < 0)
								BlinkScale = -HvRightHand.BlinkScale;
							else
								BlinkScale = (BlinkLevel*HvRightHand.BlinkScale) >> FLOATNS;

							memcpy(&pat->obj3d[0]->mWorld, &HvRightHand.ObjBip->mWorld, sizeof(smMATRIX));
						}
					}
					else
						Rend_HvRightHand = FALSE;
				}

				pat->LinkParentObject(AnimPattern, BackObjBip[dwItemSetting - 1]);
				pat->SetPosi(&Posi, &angle);
				pat->Frame = iFrame;

				if (BlinkScale)
				{
					smIdentityMatrix(Mat);
					Mat._11 = BlinkScale;
					Mat._22 = BlinkScale;
					Mat._33 = BlinkScale;
					pat->Frame = -1;
					smMatrixMult(pat->obj3d[0]->mWorld, Mat, pat->obj3d[0]->mWorld);
				}

				if ((HvLeftHand.dwItemCode == dwActionItemCode && (HvLeftHand.dwItemCode & sinITEM_MASK2) != sinWD1) || !HvRightHand.PatTool)
				{
					if (BackObjBip[dwItemSetting - 1])
						memcpy(&HvLeftHand_Matrix, &BackObjBip[dwItemSetting - 1]->mWorld, sizeof(smMATRIX));
					if (Rend_HvLeftHand)
					{
						pat->RenderD3D(&CameraPosi, &CameraAngle);
						RestoreRenderBlinkColor();
					}
				}
				else
				{
					if (BackObjBip[dwItemSetting - 1])
						memcpy(&HvRightHand_Matrix, &BackObjBip[dwItemSetting - 1]->mWorld, sizeof(smMATRIX));
					if (Rend_HvRightHand)
					{
						pat->RenderD3D(&CameraPosi, &CameraAngle);
						RestoreRenderBlinkColor();
					}
				}

				pat->LinkParentObject(0, 0);
				pat->TmLastFrame = -1;
			}

			if (HvLeftHand.PatTool && (HvLeftHand.dwItemCode != dwActionItemCode || (HvRightHand.dwItemCode & sinITEM_MASK2) == sinWD1))
			{
				pat = HvLeftHand.PatTool;

				if ((HvLeftHand.dwItemCode & sinITEM_MASK2) == sinWD1)
				{
					pat->LinkParentObject(AnimPattern, BackObjBip[4]);
					pat->SetPosi(&Posi, &angle);
					pat->Frame = iFrame;

					memcpy(&HvLeftHand_Matrix, &BackObjBip[4]->mWorld, sizeof(smMATRIX));
				}
				else
				{
					pat->LinkParentObject(AnimPattern, HvLeftHand.ObjBip);
					pat->SetPosi(&Posi, &angle);
					pat->Frame = iFrame;

					memcpy(&HvLeftHand_Matrix, &HvLeftHand.ObjBip->mWorld, sizeof(smMATRIX));
				}

				if (!HvLeftHand.ColorBlink || !HvLeftHand.sColors[SMC_A])
				{
					BlinkLevel = SetRenderBlinkColor(&HvLeftHand);

					if (HvLeftHand.BlinkScale && BlinkLevel)
					{
						smIdentityMatrix(Mat);
						if (HvLeftHand.BlinkScale < 0)
							BlinkScale = -HvLeftHand.BlinkScale;
						else
							BlinkScale = (BlinkLevel*HvLeftHand.BlinkScale) >> FLOATNS;

						Mat._11 = BlinkScale;
						Mat._22 = BlinkScale;
						Mat._33 = BlinkScale;
						pat->Frame = -1;
						memcpy(&pat->obj3d[0]->mWorld, &HvLeftHand.ObjBip->mWorld, sizeof(smMATRIX));
						smMatrixMult(pat->obj3d[0]->mWorld, Mat, pat->obj3d[0]->mWorld);
					}
					pat->RenderD3D(&CameraPosi, &CameraAngle);
					RestoreRenderBlinkColor();
				}
				else
					Rend_HvLeftHand = FALSE;

				pat->LinkParentObject(0, 0);
				pat->TmLastFrame = -1;
			}
		}

		if ((psModelAnimation->iType == ANIMATIONTYPE_Attack || psModelAnimation->iType == ANIMATIONTYPE_Skill) && (dwActionItemCode&sinITEM_MASK2) == sinWS1 && !HvRightHand.PatTool && !ShootingFlag && !HideWeapon)
		{
			pat = PatArrow;
			pat->LinkParentObject(AnimPattern, HvRightHand.ObjBip);
			pat->SetPosi(&Posi, &angle);
			pat->Frame = iFrame;
			pat->RenderD3D(&CameraPosi, &CameraAngle);
			pat->LinkParentObject(0, 0);
			pat->TmLastFrame = -1;
		}
	}

	if (ShootingFlag)
	{
		memcpy(&angle, &ShootingAngle, sizeof(POINT3D));
		angle.y = (-angle.y + ANGLE_180)&ANGCLIP;

		if ((dwActionItemCode&sinITEM_MASK2) == sinWS1 || (dwActionItemCode == (sinTW1 | sin07)))
			pat = PatArrow;
		else
		{
			pat = HvRightHand.PatTool;

			if (pat == NULL)
				pat = HvLeftHand.PatTool;
			angle.x = (angle.x - ANGLE_90)&ANGCLIP;

			if ((dwActionItemCode&sinITEM_MASK2) == sinWD1)
			{
				angle.y = (angle.y - ANGLE_180)&ANGCLIP;

				if (HvRightHand.PatTool && HvLeftHand.PatTool)
				{
					switch (MotionEvent)
					{
					case 1:
						pat = HvRightHand.PatTool;
						break;
					case 2:
						pat = HvLeftHand.PatTool;
						break;
					}
				}
			}

		}
		if (pat)
		{
			pat->SetPosi(&ShootingPosi, &angle);
			pat->Frame = 0;
			pat->RenderD3D(&CameraPosi, &CameraAngle);
		}
	}

rendSkip:

	smRender.Color_R = cr;
	smRender.Color_G = cg;
	smRender.Color_B = cb;
	smRender.Color_A = ca;

	if (nl)
		smRender.smRendLight[0].Range = DarkLightRange;
	smRender.DistortionMesh = FALSE;

	return TRUE;
}
int Unit::DrawShadow()
{
	int a;
	POINT3D	pos;
	POINT3D angle;
	POINT3D CameraPosi, CameraAngle;

	if (PatSizeLevel < 0 || !psModelAnimation)
		return FALSE;

	CameraPosi.x = smCHAR_CameraX;
	CameraPosi.y = smCHAR_CameraY;
	CameraPosi.z = smCHAR_CameraZ;

	CameraAngle.x = smCHAR_CameraAngX;
	CameraAngle.y = smCHAR_CameraAngY;
	CameraAngle.z = smCHAR_CameraAngZ;

	if (Pattern && PatShadow[PatSizeLevel] && psModelAnimation->iType != ANIMATIONTYPE_Revive && RendSucess && RendPoint.z < 12 * 64 * fONE && PlayVanish <= 0)
	{
		pos.x = pX;
		pos.y = PHeight + (1 * fONE);
		pos.z = pZ;

		angle.x = Angle.x;
		angle.y = (-Angle.y + ANGLE_180)&ANGCLIP;
		angle.z = Angle.z;

		a = smRender.Color_A;

		if (psModelAnimation->iType == ANIMATIONTYPE_Die)
			smRender.Color_A = a - (iFrameTimer << 1);

		smRender.Color_A -= 160;

		if (smRender.Color_A > -240)
		{
			GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
			smRender.SetMaterialGroup(smMaterialGroup);
			PatShadow[PatSizeLevel]->SetPosi(&pos, &angle);
			PatShadow[PatSizeLevel]->RenderD3D(&CameraPosi, &CameraAngle);
			GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		}

		smRender.Color_A = a;

	}

	smPAT3D *pat;
	smMATRIX Mat;
	int BlinkLevel, BlinkScale;

	if (RendSucess && !HideWeapon)
	{
		if (!Rend_HvRightHand)
		{
			if (HvRightHand.ColorBlink)
			{
				pat = HvRightHand.PatTool;
				pat->SetPosi(&Posi, &angle);
				pat->Frame = -1;

				BlinkLevel = SetRenderBlinkColor(&HvRightHand);
				memcpy(&pat->obj3d[0]->mWorld, &HvRightHand_Matrix, sizeof(smMATRIX));

				if (HvRightHand.BlinkScale && BlinkLevel)
				{
					smIdentityMatrix(Mat);

					if (HvRightHand.BlinkScale < 0)
						BlinkScale = -HvRightHand.BlinkScale;
					else
						BlinkScale = (BlinkLevel*HvRightHand.BlinkScale) >> FLOATNS;

					Mat._11 = BlinkScale;
					Mat._22 = BlinkScale;
					Mat._33 = BlinkScale;
					smMatrixMult(pat->obj3d[0]->mWorld, Mat, pat->obj3d[0]->mWorld);
				}

				pat->RenderD3D(&CameraPosi, &CameraAngle);
				RestoreRenderBlinkColor();
			}
		}
		if (!Rend_HvLeftHand)
		{
			if (HvLeftHand.ColorBlink)
			{
				pat = HvLeftHand.PatTool;
				pat->SetPosi(&Posi, &angle);
				pat->Frame = -1;

				BlinkLevel = SetRenderBlinkColor(&HvLeftHand);
				memcpy(&pat->obj3d[0]->mWorld, &HvLeftHand_Matrix, sizeof(smMATRIX));

				if (HvLeftHand.BlinkScale && BlinkLevel)
				{
					smIdentityMatrix(Mat);

					if (HvLeftHand.BlinkScale < 0)
						BlinkScale = -HvLeftHand.BlinkScale;
					else
						BlinkScale = (BlinkLevel*HvLeftHand.BlinkScale) >> FLOATNS;

					Mat._11 = BlinkScale;
					Mat._22 = BlinkScale;
					Mat._33 = BlinkScale;
					smMatrixMult(pat->obj3d[0]->mWorld, Mat, pat->obj3d[0]->mWorld);
				}
				pat->RenderD3D(&CameraPosi, &CameraAngle);
				RestoreRenderBlinkColor();
			}
		}
	}

	int r, g, b, c, d;
	int cnt;

	pat = 0;

	if ((dwDispAppSkill&SKILL_APPMASK_EXTREME_SHIELD) && (psModelAnimation->iType != ANIMATIONTYPE_Skill || (sCharacterData.iClass == CHARACTERCLASS_Mechanician && (AttackSkil & 0xFF) != SKILL_PLAY_EXTREME_SHIELD)))
		pat = PatEffectShield;

	if (pat)
	{
		if (RendSucess && HvLeftHand.PatTool && (HvLeftHand.dwItemCode&sinITEM_MASK2) == sinDS1)
		{
			memcpy(&angle, &Angle, sizeof(POINT3D));
			angle.y = (-angle.y + ANGLE_180)&ANGCLIP;

			Posi.x = pX;
			Posi.y = pY;
			Posi.z = pZ;
			a = smRender.Color_A;
			r = smRender.Color_R;
			g = smRender.Color_G;
			b = smRender.Color_B;
			smRender.Color_B = +128;

			pat->SetPosi(&Posi, &angle);

			d = dwPlayTime >> 4;
			c = d & 0x3F;
			if ((d & 0x40))
				c = 0x40 - c;

			c += (int)(fONE*0.9f) + c;

			smIdentityMatrix(Mat);
			if (PatEffectShield == pat)
			{
				Mat._11 = c;
				Mat._22 = c;
				Mat._33 = c;
			}

			for (cnt = 0; cnt < pat->nObj3d; cnt++)
			{
				memcpy(&pat->obj3d[cnt]->mWorld, &HvLeftHand_Matrix, sizeof(smMATRIX));
				smMatrixMult(pat->obj3d[cnt]->mWorld, Mat, pat->obj3d[cnt]->mWorld);
			}

			smRender.Color_R = 0;
			smRender.Color_G = 0;
			smRender.Color_B = 0;
			smRender.Color_A = 0;

			pat->Frame = -1;
			pat->RenderD3D(&CameraPosi, &CameraAngle);

			smRender.Color_A = a;
			smRender.Color_R = r;
			smRender.Color_G = g;
			smRender.Color_B = b;
		}
	}


	int s, sz, maxSize;

	if ((sCharacterData.iClass == CHARACTERCLASS_Pikeman && (AttackSkil & 0xFF) == SKILL_PLAY_EXPANSION) && RendSucess && HvRightHand.PatTool && psModelAnimation->iType == ANIMATIONTYPE_Attack)
	{
		sz = Expansion_Size[(AttackSkil >> 8) - 1];

		memcpy(&angle, &Angle, sizeof(POINT3D));
		angle.y = (-angle.y + ANGLE_180)&ANGCLIP;

		Posi.x = pX;
		Posi.y = pY;
		Posi.z = pZ;
		a = smRender.Color_A;
		r = smRender.Color_R;
		smRender.Color_A = -96 - (iFrameTimer << 1);
		smRender.Color_R = +128;
		if (smRender.Color_A < -192) smRender.Color_A = -192;

		pat = HvRightHand.PatTool;
		pat->SetPosi(&Posi, &angle);
		pat->Frame = -1;

		smIdentityMatrix(Mat);
		s = iFrameTimer << 3;
		maxSize = (sz*fONE) / 100;
		if (s > maxSize) s = maxSize;
		s += (fONE / 4);

		Mat._11 = fONE + s;
		Mat._22 = fONE + s;
		Mat._33 = fONE + s;

		memcpy(&pat->obj3d[0]->mWorld, &HvRightHand_Matrix, sizeof(smMATRIX));
		smMatrixMult(pat->obj3d[0]->mWorld, Mat, pat->obj3d[0]->mWorld);
		pat->RenderD3D(&CameraPosi, &CameraAngle);

		smRender.Color_A = a;
		smRender.Color_R = r;
	}

	if (Clan_CastleMasterFlag && sCharacterData.iClanID &&
		PatCrown && RendSucess && RendPoint.z < 12 * 64 * fONE && PlayVanish <= 0)
	{
		auto sPosition = GetMoveLocation(0, 0, 0 * fONE, 0, Angle.y, 0);

		pos.x = pX + sPosition.iX;
		pos.y = pY + PatHeight + 10 * fONE;
		pos.z = pZ + sPosition.iZ;

		cnt = (dwPlayTime >> 2) & 0xFF;
		if ((cnt & 0x80))
			pos.y += (cnt & 0x7F);
		else
			pos.y += 0x80 - (cnt & 0x7F);

		angle.x = 0;
		angle.y = (dwPlayTime >> 2)&ANGCLIP;
		angle.z = 0;

		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		smRender.SetMaterialGroup(smMaterialGroup);
		PatCrown->SetPosi(&pos, &angle);
		PatCrown->RenderD3D(&CameraPosi, &CameraAngle);
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	}

	return TRUE;

}
void Unit::SetIceFoot(int TypeNum, DWORD dwPlayTime, int x, int z)
{
	int loop = 0;

	if (smGameStage[iLoadedMapIndex] == NULL)
		return;

	for (loop = 0; loop < ICE_FOOT_COUNT_MAX; loop++)
	{
		if (m_IceFootInfo[loop].Life == 0)
			break;
	}

	if (loop >= ICE_FOOT_COUNT_MAX)
		return;

	POINT3D FootPos;
	FootPos.x = pX + x;
	FootPos.y = pY + (10 * fONE);
	FootPos.z = pZ + z;

	POINT3D FaceAngle;
	if (smGameStage[iLoadedMapIndex]->CheckFaceIceFoot(&FootPos, &FaceAngle, 32 * fONE) == 0)
		return;

	m_IceFootInfo[loop].Life = 1;
	m_IceFootInfo[loop].dwPlayTime = dwPlayTime;
	m_IceFootInfo[loop].TypeNum = TypeNum;
	m_IceFootInfo[loop].FootPos.x = FootPos.x;
	m_IceFootInfo[loop].FootPos.y = FootPos.y;
	m_IceFootInfo[loop].FootPos.z = FootPos.z;
	m_IceFootInfo[loop].FootAngle.x = -(FaceAngle.x - ANGLE_180) & ANGCLIP;
	m_IceFootInfo[loop].FootAngle.y = (-Angle.y) & ANGCLIP;
	m_IceFootInfo[loop].FootAngle.z = (FaceAngle.z - ANGLE_180) & ANGCLIP;
}
int Unit::DrawIceFoot(void)
{
	if (psModelAnimation == NULL || Pattern == NULL || psModelAnimation->iType == ANIMATIONTYPE_Revive || RendSucess == 0)
		return FALSE;

	POINT3D CameraPosi, CameraAngle;

	CameraPosi.x = smCHAR_CameraX;
	CameraPosi.y = smCHAR_CameraY;
	CameraPosi.z = smCHAR_CameraZ;

	CameraAngle.x = smCHAR_CameraAngX;
	CameraAngle.y = smCHAR_CameraAngY;
	CameraAngle.z = smCHAR_CameraAngZ;

	int b_r, b_g, b_b, b_a;
	b_r = smRender.Color_R;
	b_g = smRender.Color_G;
	b_b = smRender.Color_B;
	b_a = smRender.Color_A;

	smRender.Color_R = 0;
	smRender.Color_G = 0;
	smRender.Color_B = 0;
	smRender.Color_A = 0;

	smRender.m_dwRenderType = smRENDER_TYPE_ICE;

	smRender.SetMaterialGroup(smMaterialGroup);
	GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	for (int loop = 0; loop < ICE_FOOT_COUNT_MAX; loop++)
	{
		if (m_IceFootInfo[loop].Life)
		{
			float Alpha = float(dwPlayTime - m_IceFootInfo[loop].dwPlayTime) * ICE_FOOT_ALPHA_STEP;
			if (Alpha >= 200)
				m_IceFootInfo[loop].Life = 0;
			else
			{
				smRender.Color_A = -int(Alpha);
				PatIceFoot[m_IceFootInfo[loop].TypeNum]->SetPosi(&m_IceFootInfo[loop].FootPos, &m_IceFootInfo[loop].FootAngle);
				PatIceFoot[m_IceFootInfo[loop].TypeNum]->RenderD3D(&CameraPosi, &CameraAngle);
			}
		}
	}
	GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	smRender.Color_R = b_r;
	smRender.Color_G = b_g;
	smRender.Color_B = b_b;
	smRender.Color_A = b_a;

	smRender.m_dwRenderType = 0;
	return TRUE;
}

#define STATE_BAR_WIDTH		100
#define STATE_BAR_HEIGHT	16
#define STATE_BAR_SIZE		92


// ÉúÃüÌõÏÔÊ¾
int Unit::DrawStateBar(int x, int y)
{
	int Percent;

	if (!EnableStateBar && sCharacterData.iType == CHARACTERTYPE_Monster)
	{
		if (sCharacterData.sGlow == MONSTER_CLASS_BOSS)
			EnableStateBar = TRUE;
		else if (sCharacterData.iMonsterEffectID == MONSTEREFFECTID_CASTLE_DOOR || sCharacterData.iMonsterEffectID == snCHAR_SOUND_CASTLE_TOWER_B || sCharacterData.iMonsterEffectID == snCHAR_SOUND_CASTLE_CRYSTAL_R || sCharacterData.iMonsterEffectID == snCHAR_SOUND_CASTLE_CRYSTAL_G || sCharacterData.iMonsterEffectID == snCHAR_SOUND_CASTLE_CRYSTAL_B || sCharacterData.iMonsterEffectID == snCHAR_SOUND_CASTLE_CRYSTAL_N)
			EnableStateBar = TRUE;
	}

	if (sCharacterData.sHP.sMax == 0 || (!DisplayDebug && !EnableStateBar))
		return NULL;
	if (x < 0 || (x + STATE_BAR_WIDTH) >= (int)RESOLUTION_WIDTH)
		return NULL;
	if (y < 0 || (y + STATE_BAR_HEIGHT) >= (int)RESOLUTION_HEIGHT)
		return NULL;

	psSetRenderState(1);
	GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	float fSize;

	fSize = 1;

	Percent = (sCharacterData.sHP.sMin * STATE_BAR_SIZE_NEW) / sCharacterData.sHP.sMax;

	dsDrawTexImageFloat(MatEnergyBoxNew[0], (float)x, (float)y, STATE_BAR_WIDTH_NEW*fSize, STATE_BAR_HEIGHT_NEW*fSize, 426, 31, 0, 0, STATE_BAR_WIDTH_NEW, 30, 255);
	if (sCharacterData.sHP.sMin > 0)
		dsDrawTexImageFloat(MatEnergyBoxNew[1], (float)x + 62.0f*fSize, (float)y, (float)(Percent + 3)*fSize, STATE_BAR_HEIGHT_NEW*fSize, 300, 31, 0, 0, (float)Percent + 3, 30, 255);

	return TRUE;
}
int Unit::DrawStateBar2(int x, int y)
{
	int Percent;
	int	Percent2;
	int	Percent3;

	DWORD dwColor;

	if (sCharacterData.sHP.sMax == 0)
		return NULL;
	if (x < 0 || (x + (STATE_BAR_WIDTH / 2)) >= (int)RESOLUTION_WIDTH)
		return NULL;
	if (y < 0 || (y + (STATE_BAR_HEIGHT / 2)) >= (int)RESOLUTION_HEIGHT)
		return NULL;

	psSetRenderState(1);
	GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	Percent = (sCharacterData.sHP.sMin * STATE_BAR_SIZE) / sCharacterData.sHP.sMax;
	Percent2 = (sCharacterData.sHP.sMin * 511) / sCharacterData.sHP.sMax;
	Percent2 = (Percent2*Percent2) / 512;
	Percent3 = Percent2 & 0xFF;

	if (Percent2 < 256)
		dwColor = D3DCOLOR_RGBA(255, Percent3, 0, 255);
	else
		dwColor = D3DCOLOR_RGBA(255 - Percent3, 255, 0, 255);

	dsDrawTexImageFloat(MatEnergyBox[0], (float)x, (float)y, STATE_BAR_WIDTH*0.6f, STATE_BAR_HEIGHT*0.7f, 128, 16, 0, 0, STATE_BAR_WIDTH, 15, 255);
	dsDrawTexImageFloatColor(MatEnergyBox[1], (float)x, (float)y, ((float)Percent + 3)*0.6f, STATE_BAR_HEIGHT*0.7f, 128, 16, 0, 0, (float)Percent + 3, 15, dwColor);

	return TRUE;
}
int Unit::DrawChargingBar(int x, int y, int Charging, int ChargingMax)
{
	int	Percent;

	DWORD dwColor;

	if (sCharacterData.sHP.sMax == 0)
		return NULL;
	if (x < 0 || (x + (STATE_BAR_WIDTH / 2)) >= (int)RESOLUTION_WIDTH)
		return NULL;
	if (y < 0 || (y + (STATE_BAR_HEIGHT / 2)) >= (int)RESOLUTION_HEIGHT)
		return NULL;

	psSetRenderState(1);
	GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	Percent = (Charging*STATE_BAR_SIZE) / ChargingMax;
	dwColor = D3DCOLOR_RGBA(160, 160, 255, 255);

	dsDrawTexImageFloat(MatEnergyBox[0], (float)x, (float)y, STATE_BAR_WIDTH*0.6f, STATE_BAR_HEIGHT*0.7f, 128, 16, 0, 0, STATE_BAR_WIDTH, 15, 255);
	dsDrawTexImageFloatColor(MatEnergyBox[1], (float)x, (float)y, ((float)Percent + 3)*0.6f, STATE_BAR_HEIGHT*0.7f, 128, 16, 0, 0, (float)Percent + 3, 15, dwColor);

	return TRUE;
}
int Unit::DrawMotionBlur()
{
	if (HideWeapon || !DisplayFlag || !RendSucess || !smMotionInfo)
		return FALSE;

	if (RendPoint.z < 24 * 64 * fONE)
		StartHandEffect(0);

	if ((sCharacterData.iType != CHARACTERTYPE_Player && iCharacterType != CHARACTERTYPE_Player) || RendPoint.z > 10 * 64 * fONE)
		return FALSE;

	if (ShootingMode || (smMotionInfo->MotionInfo[action].iType != ANIMATIONTYPE_Attack && smMotionInfo->MotionInfo[action].iType != ANIMATIONTYPE_Skill))
		return FALSE;

	if (HvLeftHand.PatTool)
		DrawMotionBlurTool(&HvLeftHand);

	if (HvRightHand.PatTool)
		DrawMotionBlurTool(&HvRightHand);

	return TRUE;
}

int Unit::DrawMotionBlurTool(smCHARTOOL *ChrTool)
{
	DWORD ClipStates;
	smVERTEX *vp1, *vp2;
	smVERTEX *vp3, *vp4;

	int cnt, vcnt;
	int	sin, cos;
	DWORD pframe;
	int rx, ry, rz;
	smMATRIX *mWorld;
	POINT3D angle;
	POINT3D pTop, pBot;
	int szLevel;
	int mLevel;
	int mFrames;
	int mLevel2;
	smVERTEX	*lpVertex;
	smFACE		*lpFace;

	int r, g, b;

	if (!DisplayFlag || !dwActionItemCode || (dwActionItemCode&sinITEM_MASK2) == sinDS1)
		return FALSE;

	if (ActionPattern == 0)
	{
		mLevel = 32;
		mFrames = 40;
		mLevel2 = mLevel << 1;
		lpVertex = MbVertex;
		lpFace = MbFace;
	}
	else
	{
		mLevel = 16;
		mFrames = 80;
		mLevel2 = mLevel << 1;
		lpVertex = MbVertex2;
		lpFace = MbFace2;
	}

	pTop.x = 0;
	pTop.y = 0;
	pTop.z = 0;

	pBot.x = 0;
	pBot.y = 0;
	pBot.z = ChrTool->SizeMax;

	szLevel = pBot.z / (mLevel << 1);

	if (dwActionItemTwoHand)
	{
		cnt = (-ANGLE_45 / 5)&ANGCLIP;
		sin = GetSin[cnt] >> 8;
		cos = GetCos[cnt] >> 8;

		pTop.y = -(pTop.z*sin) >> 8;
		pTop.z = (pTop.z*cos) >> 8;

		pBot.y = -(pBot.z*sin) >> 8;
		pBot.z = (pBot.z*cos) >> 8;
	}

	memcpy(&angle, &Angle, sizeof(POINT3D));

	angle.y = (-angle.y + ANGLE_180)&ANGCLIP;

	if (ActionGameMode)
	{
		if (angle.y > ANGLE_180)
			angle.y = ANGLE_270;
		else
			angle.y = ANGLE_90;
	}

	mWorld = &ChrTool->ObjBip->mWorld;

	if (ChrTool->PatTool && ChrTool->ObjBip)
	{
		for (cnt = 0; cnt < mLevel; cnt++)
		{
			pframe = iFrame - (cnt*mFrames);
			if (pframe < psModelAnimation->StartFrame)
				pframe = psModelAnimation->StartFrame;

			AnimObjectTree(ChrTool->ObjBip, pframe, angle.x, angle.y, angle.z);

			vcnt = cnt << 1;

			rx = pTop.x * mWorld->_11 + pTop.y * mWorld->_21 + pTop.z * mWorld->_31;
			ry = pTop.x * mWorld->_12 + pTop.y * mWorld->_22 + pTop.z * mWorld->_32;
			rz = pTop.x * mWorld->_13 + pTop.y * mWorld->_23 + pTop.z * mWorld->_33;

			lpVertex[vcnt].x = pX + (rx >> FLOATNS) + mWorld->_41;
			lpVertex[vcnt].z = pZ + (ry >> FLOATNS) + mWorld->_42;
			lpVertex[vcnt].y = pY + (rz >> FLOATNS) + mWorld->_43;

			vcnt++;

			rx = pBot.x * mWorld->_11 + pBot.y * mWorld->_21 + pBot.z * mWorld->_31;
			ry = pBot.x * mWorld->_12 + pBot.y * mWorld->_22 + pBot.z * mWorld->_32;
			rz = pBot.x * mWorld->_13 + pBot.y * mWorld->_23 + pBot.z * mWorld->_33;

			lpVertex[vcnt].x = pX + (rx >> FLOATNS) + mWorld->_41;
			lpVertex[vcnt].z = pZ + (ry >> FLOATNS) + mWorld->_42;
			lpVertex[vcnt].y = pY + (rz >> FLOATNS) + mWorld->_43;

			pTop.z += szLevel;
			pBot.z -= szLevel;
		}
	}

	ClipStates = (SMCLIP_NEARZ | SMCLIP_FARZ | SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM);

	smRender.Init();
	smRender.SetCameraPosi(smCHAR_CameraX, smCHAR_CameraY, smCHAR_CameraZ, smCHAR_CameraAngX, smCHAR_CameraAngY, smCHAR_CameraAngZ);

	for (cnt = 0; cnt < mLevel2; cnt++)
		smRender.AddObjectVertex(&lpVertex[cnt]);

	for (cnt = 0; cnt < (mLevel2 - 2); cnt += 2)
	{
		vp1 = &lpVertex[cnt];
		vp2 = &lpVertex[cnt + 1];
		vp3 = &lpVertex[cnt + 2];
		vp4 = &lpVertex[cnt + 3];

		if (vp1->x != vp3->x || vp1->y != vp3->y || vp1->z != vp3->z || vp2->x != vp4->x || vp2->y != vp4->y || vp2->z != vp4->z)
		{
			smRender.AddObjectFace(&lpFace[cnt]);
			smRender.AddObjectFace(&lpFace[cnt + 1]);
		}
	}

	r = smRender.Color_R;
	g = smRender.Color_G;
	b = smRender.Color_B;

	if (AttackSkil)
		cnt = SetSkillMotionBlurColor(AttackSkil, this);


	if (!cnt && ChrTool->ColorBlink)
	{
		smRender.Color_R += ChrTool->sColors[SMC_R] >> 1;
		smRender.Color_G += ChrTool->sColors[SMC_G] >> 1;
		smRender.Color_B += ChrTool->sColors[SMC_B] >> 1;
	}
	if (smRender.nRendFace)
	{
		smRender.SetClipStates(ClipStates);
		smRender.ClipRendFace();
		smRender.GeomVertex2D(FALSE);
		smRender.RenderD3D();
	}

	smRender.Color_R = r;
	smRender.Color_G = g;
	smRender.Color_B = b;

	return TRUE;
}
// ÏÔÊ¾ÉËº¦
int Unit::ShowDamage(int Height)
{
	char buffTemp1[64] = { 0 };
	char buffTemp2[64] = { 0 };

	int sx;
	int sy;
	int Alpha;
	DWORD Color;

	if (psModelAnimation && psModelAnimation->iType != ANIMATIONTYPE_Die && SETTINGHANDLE->Get().bDebugDamage)
	{
		if (DmgBlendValue > 0)
		{
			Color = D3DCOLOR_XRGB(255, 255, 255);

			if (Damge == 0)
			{
				lstrcpy(buffTemp2, "Miss");
				Color = D3DCOLOR_XRGB(210, 0, 255);
			}
			else
			{
				_itoa_s(Damge, buffTemp1, 10);

				switch (DmgType[1])
				{
					// ±©»÷
				case 1:
					wsprintf(buffTemp2, "Critical -%s", buffTemp1);
					Color = D3DCOLOR_XRGB(255, 150, 0);
					break;
				default:
					wsprintf(buffTemp2, "-%s", buffTemp1);
					Color = D3DCOLOR_XRGB(200, 0, 0);
					break;
				}
				switch (DmgType[0])
				{
				case sITEMINFO_FIRE:
					Color = D3DCOLOR_XRGB(255, 70, 0);
					break;
				case sITEMINFO_ICE:
					Color = D3DCOLOR_XRGB(0, 150, 255);
					break;
				case sITEMINFO_POISON:
					Color = D3DCOLOR_XRGB(0, 255, 50);
					break;
				}
			}

			DmgBlendValue -= 2;

			if (DmgBlendValue < 0)
				DmgBlendValue = 0;

			sx = RendPoint.x;
			sy = RendRect2D.top + Height - 60 - (int)((255 - DmgBlendValue) * 0.2f);
			Alpha = DmgBlendValue;

			Color |= (Alpha & 0xFF) << 24;

			DrawFontImage(buffTemp2, sx, sy, Color, 1.0f);

			return TRUE;
		}
	}

	return FALSE;
}


int Unit::SetLoadPattern(char *szName)
{
	Pattern = 0;
	bActive = TRUE;
	return AddLoaderPattern((Unit *)&Head, szName);

}

//¹ÞÀº µ¥¹ÌÁö ¾ÏÈ­È­ ÄÚµå
DWORD Unit::GetAttackTrans_XorCode()
{
	return iID ^ lpCurPlayer->sCharacterData.dwObjectSerial ^ (((DWORD)this) >> 8);
}

//¹ÞÀºµ¥¹ÌÁö ¼öÄ¡ ÃÊ±âÈ­
int Unit::ResetAttackTrans()
{
	AttackTrans.code = GetAttackTrans_XorCode();
	return TRUE;
}

//¹ÞÀºµ¥¹ÌÁö ¼öÄ¡ ¾ÏÈ£È­ ¹ÝÀü
int Unit::XorAttackTrans()
{
	int cnt, len;
	DWORD dwCode;

	len = (sizeof(TRANS_ATTACKDATA) / sizeof(DWORD));//+2;
	DWORD *lpdwBuff = (DWORD *)&AttackTrans;

	dwCode = GetAttackTrans_XorCode();

	lpdwBuff[0] ^= dwCode;
	lpdwBuff[1] ^= dwCode;

	for (cnt = 2; cnt < len; cnt++) {
		lpdwBuff[cnt] ^= dwCode;
		dwCode += dwCode;
	}

	return TRUE;
}
int Unit::PlayAttack(int EventFlag)
{
	int cnt, len, act;
	int block, ChanceBlock;
	Unit *lpChar;
	int	HolyBody_Undead = 0;
	int x, y, z;
	POINT3D	Pos1;
	int temp;
	int Param1, Param2;
	int	bStunCount;

	TRANS_ATTACKDATA	*lpTransAttackData;

	lpTransAttackData = &AttackTrans;

	XorAttackTrans();

	if (!lpTransAttackData->code || (RestartPlayCount > 0 && RestartPlayCount < 1000) || (UseEtherCoreCode && lpCurPlayer->psModelAnimation->iType == ANIMATIONTYPE_Potion))
	{
		AttackTrans.code = GetAttackTrans_XorCode();
		if (RestartPlayCount)
			Ptect_IncAttackCount(0);
		return FALSE;
	}

	if (lpTransAttackData->dwDamageChkSum != dm_GetDamgeChkSum_S2V(lpTransAttackData))
	{
		ResetAttackTrans();
		SendSetHackUser3(8580, lpTransAttackData->Power, 0);
		return FALSE;
	}

	Ptect_IncAttackCount(-1);

	if (lpCurPlayer->psModelAnimation->iType != ANIMATIONTYPE_Die && DisplayFlag)
	{
		len = GetDistanceDbl(lpCurPlayer->pX, lpCurPlayer->pZ, pX, pZ);
		cnt = GetDistanceDbl(lpCurPlayer->pX, lpCurPlayer->pZ, lpTransAttackData->x, lpTransAttackData->z);

		if (sCharacterData.iType == CHARACTERTYPE_Player || iCharacterType == CHARACTERTYPE_Player)
		{
			len = 0;
			cnt = 0;
		}

		//ÅÐ¶Ï¹ÖÎï¼¼ÄÜÊÇ·ñÎª·¶Î§¹¥»÷
		if (sCharacterData.iMonsterEffectID == snCHAR_SOUND_FIGON ||
			sCharacterData.iMonsterEffectID == snCHAR_SOUND_WEB ||
			sCharacterData.iMonsterEffectID == snCHAR_SOUND_SKELETONRANGE ||
			sCharacterData.iMonsterEffectID == snCHAR_SOUND_IMP ||
			sCharacterData.iMonsterEffectID == snCHAR_SOUND_SCORPION ||
			sCharacterData.iMonsterEffectID == snCHAR_SOUND_NAZ ||
			sCharacterData.iMonsterEffectID == snCHAR_SOUND_NAZSENIOR ||
			sCharacterData.iMonsterEffectID == snCHAR_SOUND_SHADOW ||
			sCharacterData.iMonsterEffectID == snCHAR_SOUND_BEEDOG ||
			sCharacterData.iMonsterEffectID == snCHAR_SOUND_MUTANTTREE ||
			sCharacterData.iMonsterEffectID == snCHAR_SOUND_SUCCUBUS ||
			sCharacterData.iMonsterEffectID == snCHAR_SOUND_BERSERKER ||
			sCharacterData.iMonsterEffectID == snCHAR_SOUND_STYGIANLORD ||
			sCharacterData.iMonsterEffectID == snCHAR_SOUND_AVELIN_ARCHER ||
			sCharacterData.iMonsterEffectID == snCHAR_SOUND_AVELIN_QUEEN ||
			sCharacterData.iMonsterEffectID == snCHAR_SOUND_DMACHINE ||
			sCharacterData.iMonsterEffectID == snCHAR_SOUND_SADNESS ||
			sCharacterData.iMonsterEffectID == snCHAR_SOUND_RUNICGUARDIAN ||
			sCharacterData.iMonsterEffectID == snCHAR_SOUND_BABEL ||
			sCharacterData.iMonsterEffectID == snCHAR_SOUND_HYPERMACHINE ||
			sCharacterData.iMonsterEffectID == snCHAR_SOUND_TURTLE_CANNON ||
			sCharacterData.iMonsterEffectID == snCHAR_SOUND_FROZEN ||
			sCharacterData.iMonsterEffectID == snCHAR_SOUND_CHAOSCARA ||
			sCharacterData.iMonsterEffectID == snCHAR_SOUND_COLDEYE ||
			sCharacterData.iMonsterEffectID == snCHAR_SOUND_M_LORD ||
			sCharacterData.iMonsterEffectID == snCHAR_SOUND_KELVEZU ||
			sCharacterData.iMonsterEffectID == snCHAR_SOUND_DARKGUARD ||
			sCharacterData.iMonsterEffectID == snCHAR_SOUND_DARKMAGE ||
			sCharacterData.iMonsterEffectID == snCHAR_SOUND_FIREWORM ||
			sCharacterData.iMonsterEffectID == snCHAR_SOUND_SETO ||
			sCharacterData.iMonsterEffectID == snCHAR_SOUND_NPC_MAGICMASTER ||
			sCharacterData.iMonsterEffectID == snCHAR_SOUND_NPC_SKILLMASTER ||
			sCharacterData.iMonsterEffectID == snCHAR_SOUND_GOBLINSHAMAN ||
			sCharacterData.iMonsterEffectID == smCHAR_SOUND_ICEWORM ||
			sCharacterData.iMonsterEffectID == snCHAR_SOUND_DEVILSHY ||
			sCharacterData.iMonsterEffectID == MONSTEREFFECTID_Draxos ||
			sCharacterData.iMonsterEffectID == smCHAR_SOUND_GREEDY ||
			sCharacterData.iMonsterEffectID == snCHAR_SOUND_CASTLE_CRYSTAL_R ||
			sCharacterData.iMonsterEffectID == snCHAR_SOUND_CASTLE_CRYSTAL_G ||
			sCharacterData.iMonsterEffectID == snCHAR_SOUND_CASTLE_CRYSTAL_B ||
			lpTransAttackData->AttackState == 0x80)
		{
			if (len < (460 * 460))
				len = 0;

			cnt = 0;

			if (sCharacterData.iMonsterEffectID == snCHAR_SOUND_WEB)
			{
				lpCurPlayer->PlaySlowCount = 70 * 2;
				lpCurPlayer->PlaySlowSpeed = 180;
			}
			if (!EventFlag)
			{
				dwAttackPlayTime = dwPlayTime + 1100;
				XorAttackTrans();
				return TRUE;
			}
		}

		if (lpTransAttackData->sRating[0] < 0)
		{
			Param1 = -lpTransAttackData->sRating[0];
			Param2 = lpTransAttackData->sRating[1];
			lpTransAttackData->sRating[0] = 0;
			lpTransAttackData->sRating[1] = 0;
		}
		else
		{
			Param1 = 0;
			Param2 = 0;
		}

		if (lpCurPlayer->sCharacterData.iType == CHARACTERTYPE_Monster)
			act = 1;
		else
			act = 0;

		if (lpTransAttackData->AttackState == 0x80)
		{
			x = (lpTransAttackData->x - lpCurPlayer->pX) >> FLOATNS;
			y = (lpTransAttackData->y - lpCurPlayer->pY) >> FLOATNS;
			z = (lpTransAttackData->z - lpCurPlayer->pZ) >> FLOATNS;
			if ((x*x + y * y + z * z) > (140 * 140))
				cnt = lpTransAttackData->AttackSize;
			act = 1;
		}

		Record_RecvDamageCount++;

		if (cnt < lpTransAttackData->AttackSize && sinGetLife()>0 && (len < (330 * 330) || act) && DisplayAlpha == 0)
		{
			lpChar = this;

			block = FALSE;

			if (lpChar)
			{
				if (lpCurPlayer->sCharacterData.iClass == CHARACTERCLASS_Archer)
				{
					cnt = cSkill.GetSkillPoint(SKILL_EVASION_MASTERY);
					if (cnt > 0 && cnt <= 10)
					{
						cnt = Evasion_Mastery_AddPercent[cnt - 1];
						if ((rand() % 100) <= cnt)
						{
							cInterFace.SetStringEffect(HA_EVASION);
							block = 100;
							Record_BlockCount++;
						}
					}
				}
				if (lpCurPlayer->sCharacterData.iClass == CHARACTERCLASS_Assassin)
				{
					cnt = cSkill.GetSkillPoint(SKILL_ATTACK_MASTERY);
					if (cnt > 0 && cnt <= 10)
					{
						cnt = Blade_Mastery_Evasion[cnt - 1];
						if (rand() % 100 <= cnt)
						{
							cInterFace.SetStringEffect(HA_EVASION);
							block = 100;
							Record_BlockCount++;
						}
					}
				}

				if (lpCurPlayer->sCharacterData.iBlockRating)
				{
					ChanceBlock = sinGetBlockRating(lpChar->sCharacterData.iLevel);

					if ((lpCurPlayer->HvLeftHand.dwItemCode&sinITEM_MASK2) == sinDS1)
					{
						if (lpCurPlayer->sCharacterData.iClass == CHARACTERCLASS_Mechanician && (lpCurPlayer->dwDispAppSkill&SKILL_APPMASK_EXTREME_SHIELD) != 0)
							ChanceBlock += (lpTransAttackData->AttackState >> 16);
						if (lpCurPlayer->sCharacterData.iClass == CHARACTERCLASS_Knight && (lpCurPlayer->dwDispAppSkill&SKILL_APPMASK_SPARK_SHIELD) != 0)
							ChanceBlock += (lpTransAttackData->AttackState >> (16 + 8));
						if (lpCurPlayer->sCharacterData.iClass == CHARACTERCLASS_Knight && (lpCurPlayer->dwDispAppSkill&SKILL_APPMASK_GODLY_SHIELD) != 0)
						{
							cnt = cSkill.GetSkillPoint(SKILL_DIVINE_INHALATION);
							if (cnt > 0 && D_Inhalation_Block[cnt - 1] <= 10)
								ChanceBlock += D_Inhalation_Block[cnt - 1];
						}
						if (ChanceBlock > 50)
							ChanceBlock = 50;
					}
				}
				else
					ChanceBlock = 0;

				if ((rand() % 100) < ChanceBlock)
				{
					cInterFace.SetStringEffect(HA_BLOCK);
					block = TRUE;
					Record_BlockCount++;

					if (abs(lpChar->sCharacterData.iLevel - lpCurPlayer->sCharacterData.iLevel) <= AGING_SUB_LEVEL)
						sinCheckAgingLevel(SIN_AGING_BLOCK, false);

					if ((lpCurPlayer->dwDispAppSkill&SKILL_APPMASK_SPARK_SHIELD) && lpChar)
					{
						if (lpCurPlayer->sCharacterData.iClass == CHARACTERCLASS_Mechanician)
							dm_SendTransDamage(lpChar, 0, 0, 0, 0, SKILL_PLAY_SPARK_SHIELD | 0x100, FALSE);
						if (lpCurPlayer->sCharacterData.iClass == CHARACTERCLASS_Knight)
						{
							cnt = (lpTransAttackData->AttackState >> 16) & 0xFF;
							if (cnt > 0)
							{
								sinSetLife((sinGetLife() + cnt));
								ResetEnergyGraph(0);

								if (lpCurPlayer->HvLeftHand.PatTool)
								{
									if (lpCurPlayer->GetToolBipPoint(&lpCurPlayer->HvLeftHand, &x, &y, &z))
									{
										Pos1.x = x;
										Pos1.y = y;
										Pos1.z = z;

										AssaParticle_DivineInhalationDefence(&Pos1);
									}
								}
							}
						}
					}
				}
			}

			if (lpChar && (!block || act))
			{
				if (sizeof(TRANS_ATTACKDATA) == lpTransAttackData->size)
					cnt = sinGetMonsterAccuracy(lpTransAttackData->sRating[0], lpTransAttackData->sRating[1]);
				else
					cnt = sinGetMonsterAccuracy(sCharacterData.iLevel, sCharacterData.iAttackRange);

				if (dmAttackCount < 2)
					cnt <<= 2;

				if ((rand() % 100) <= cnt || act)
				{
					cnt = lpTransAttackData->Power;

					if ((lpCurPlayer->dwDispAppSkill&SKILL_APPMASK_HOLY_BODY))
					{
						if (sCharacterData.iMonsterType == MONSTERTYPE_Undead)
							HolyBody_Undead = TRUE;
					}

					if (lpCurPlayer->sCharacterData.iClass == CHARACTERCLASS_Magician)
					{
						temp = lpTransAttackData->AttackState >> 16;
						if (temp > 0)
						{
							AssaParticle_EnergyShieldDefence(lpCurPlayer);
							temp = sinGetMana() - temp;
							if (temp < 0)
								temp = 0;
							sinSetMana(temp);
							ResetEnergyGraph(1);
						}
					}

					if (lpCurPlayer->sCharacterData.iClass == CHARACTERCLASS_Priestess)
					{
						if (lpChar->sCharacterData.iMonsterType == MONSTERTYPE_Undead && (lpCurPlayer->dwDispAppSkill&SKILL_APPMASK_GODLY_SHIELD) != 0)
						{
							temp = lpTransAttackData->AttackState >> 16;
							if (temp > 0)
							{
								temp = sinGetLife() + temp;
								sinSetLife(temp);
								ResetEnergyGraph(0);
							}
						}
					}

					bStunCount = lpCurPlayer->iStunTimeLeft;
					lpCurPlayer->iStunTimeLeft = 0;
					lpCurPlayer->DmgType[0] = 0;

					//Ñ£ÔÎÐ§¹û
					if (sCharacterData.iClass == CHARACTERCLASS_Fighter && Param1 == SKILL_PLAY_ROAR)
					{
						if (!bStunCount)
						{
							lpCurPlayer->iStunTimeLeft = GetResistancePower(Param2 * 70, sITEMINFO_BIONIC);
							AssaParticle_Stune(lpCurPlayer, Param2 + 1);
						}
					}
					//º®±ùÖ®¼ý
					else if (sCharacterData.iClass == CHARACTERCLASS_Archer && Param1 == SKILL_PLAY_C_TRAP)
					{
						lpCurPlayer->PlaySlowCount = GetResistancePower(Param2 * 70, sITEMINFO_ICE);
						lpCurPlayer->PlaySlowSpeed = 120;
						lpCurPlayer->AttackIce = 1;
						lpCurPlayer->DmgType[0] = sITEMINFO_ICE;
					}
					else if (sCharacterData.iClass == CHARACTERCLASS_Pikeman && Param1 == SKILL_PLAY_GROUND_PIKE)
					{
						lpCurPlayer->PlaySlowCount = GetResistancePower(Param2 * 70, sITEMINFO_ICE);
						lpCurPlayer->PlaySlowSpeed = 180;
						lpCurPlayer->AttackIce = 1;
						lpCurPlayer->DmgType[0] = sITEMINFO_ICE;
					}
					else if (sCharacterData.iClass == CHARACTERCLASS_Pikeman && Param1 == SKILL_PLAY_VENOM_SPEAR)
					{
						lpCurPlayer->PlayPoison[0] = 1;
						lpCurPlayer->PlayPoison[1] = GetResistancePower(70 * Param2, sITEMINFO_POISON);
						lpCurPlayer->DmgType[0] = sITEMINFO_POISON;
					}
					//µØÏ®ÆæÇ¹
					else if (sCharacterData.iClass == CHARACTERCLASS_Pikeman && Param1 == SKILL_PLAY_F_SPEAR)
					{
						lpCurPlayer->PlaySlowCount = GetResistancePower(Param2 * 70, sITEMINFO_ICE);
						lpCurPlayer->PlaySlowSpeed = 100;
						lpCurPlayer->AttackIce = 1;
						lpCurPlayer->DmgType[0] = sITEMINFO_ICE;
					}
					else if (sCharacterData.iClass == CHARACTERCLASS_Atalanta && Param1 == SKILL_PLAY_SHIELD_STRIKE)
					{
						if (!bStunCount)
						{
							lpCurPlayer->iStunTimeLeft = GetResistancePower(Param2 * 70, sITEMINFO_BIONIC);
							AssaParticle_Stune(lpCurPlayer, Param2 + 1);
						}
					}
					else if (sCharacterData.iClass == CHARACTERCLASS_Atalanta && Param1 == SKILL_PLAY_FROST_JAVELIN)
					{
						lpCurPlayer->PlaySlowCount = GetResistancePower(210, sITEMINFO_ICE);
						lpCurPlayer->PlaySlowSpeed = Param2 * 70;
						lpCurPlayer->AttackIce = 1;
						lpCurPlayer->DmgType[0] = sITEMINFO_ICE;
					}
					// Å¤Çú
					else if (sCharacterData.iClass == CHARACTERCLASS_Magician && Param1 == SKILL_PLAY_DISTORTION)
					{
						lpCurPlayer->PlaySlowCount = Param2 * 70;
						lpCurPlayer->PlaySlowSpeed = 210;
						lpCurPlayer->iDistortion = lpCurPlayer->PlaySlowCount;
						lpCurPlayer->AttackIce = 0;
					}
					else if (sCharacterData.iClass == CHARACTERCLASS_Magician && Param1 == SKILL_PLAY_ENCHANT_WEAPON)
					{
						lpCurPlayer->PlaySlowCount = GetResistancePower(100, sITEMINFO_ICE);
						lpCurPlayer->PlaySlowSpeed = Param2 * 70;
						lpCurPlayer->AttackIce = 1;
						lpCurPlayer->DmgType[0] = sITEMINFO_ICE;
					}
					else if (sCharacterData.iClass == CHARACTERCLASS_Magician && Param1 == SKILL_PLAY_DANCING_SWORD)
					{
						lpCurPlayer->PlaySlowCount = GetResistancePower(140, sITEMINFO_ICE);
						lpCurPlayer->PlaySlowSpeed = Param2 * 70;
						lpCurPlayer->AttackIce = 1;
						lpCurPlayer->DmgType[0] = sITEMINFO_ICE;
					}
					//ÖëÍøÖ®Êõ
					else if (sCharacterData.iClass == CHARACTERCLASS_Magician && Param1 == SKILL_PLAY_V_TENUS)
					{
						lpCurPlayer->PlaySlowCount = Param2 * 70;
						lpCurPlayer->PlaySlowSpeed = 210;
						lpCurPlayer->PlayWeb = lpCurPlayer->PlaySlowCount;
						lpCurPlayer->AttackIce = 0;
					}
					//±ùËª
					else if (sCharacterData.iClass == CHARACTERCLASS_Priestess && Param1 == SKILL_PLAY_GLACIAL_SPIKE)
					{
						lpCurPlayer->PlaySlowCount = GetResistancePower(Param2 * 70, sITEMINFO_ICE);
						lpCurPlayer->PlaySlowSpeed = 200;
						lpCurPlayer->AttackIce = 1;
						lpCurPlayer->DmgType[0] = sITEMINFO_ICE;
					}
					//±ùÈÐ
					else if (sCharacterData.iClass == CHARACTERCLASS_Priestess && Param1 == SKILL_PLAY_P_ICE)
					{
						lpCurPlayer->PlaySlowCount = GetResistancePower(Param2 * 70, sITEMINFO_ICE);
						lpCurPlayer->PlaySlowSpeed = 0;
						lpCurPlayer->AttackIce = 1;
						lpCurPlayer->DmgType[0] = sITEMINFO_ICE;
					}
					//´ó±©·çÑ©
					else if (sCharacterData.iClass == CHARACTERCLASS_Priestess && Param1 == SKILL_PLAY_S_PRMIEL)
					{
						lpCurPlayer->PlaySlowCount = GetResistancePower(Param2 * 70, sITEMINFO_ICE);
						lpCurPlayer->PlaySlowSpeed = 120;
						lpCurPlayer->AttackIce = 1;
						lpCurPlayer->DmgType[0] = sITEMINFO_ICE;
					}
					else if (sCharacterData.iClass == CHARACTERCLASS_Assassin && Param1 == SKILL_PLAY_STRINGER)
					{
						lpCurPlayer->PlayPoison[0] = 1;
						lpCurPlayer->PlayPoison[1] = GetResistancePower(70 * Param2, sITEMINFO_POISON);
						lpCurPlayer->DmgType[0] = sITEMINFO_POISON;
					}
					else if (sCharacterData.iClass == CHARACTERCLASS_Assassin && Param1 == SKILL_PLAY_WISP)
					{
						lpCurPlayer->PlaySlowCount = Param2 * 70;
						lpCurPlayer->PlaySlowSpeed = 210;
						lpCurPlayer->iDistortion = lpCurPlayer->PlaySlowCount;
						lpCurPlayer->AttackIce = 0;
					}
					else if (sCharacterData.iClass == CHARACTERCLASS_Assassin && Param1 == SKILL_PLAY_VENOM_THORN)
					{
						lpCurPlayer->PlayPoison[0] = 1;
						lpCurPlayer->PlayPoison[1] = GetResistancePower(70 * Param2, sITEMINFO_POISON);
						lpCurPlayer->DmgType[0] = sITEMINFO_POISON;
					}
					else if (sCharacterData.iClass == CHARACTERCLASS_Assassin && Param1 == SKILL_PLAY_SOUL_SHOCK)
					{
						if (!bStunCount)
						{
							lpCurPlayer->iStunTimeLeft = GetResistancePower(Param2 * 70, sITEMINFO_BIONIC);
							AssaParticle_Stune(lpCurPlayer, Param2 + 1);
						}
					}
					else if (sCharacterData.iClass == CHARACTERCLASS_Assassin && Param1 == SKILL_PLAY_POLLUTE)
					{
						lpCurPlayer->PlayPoison[0] = 1;
						lpCurPlayer->PlayPoison[1] = GetResistancePower(70 * Param2, sITEMINFO_POISON);
						lpCurPlayer->DmgType[0] = sITEMINFO_POISON;
					}
					else if (sCharacterData.iClass == CHARACTERCLASS_Assassin && Param1 == SKILL_PLAY_SHADOW_BOMB)
					{
						lpCurPlayer->PlayFire[0] = 1;
						lpCurPlayer->PlayFire[1] = GetResistancePower(70 * Param2, sITEMINFO_FIRE);
						lpCurPlayer->DmgType[0] = sITEMINFO_FIRE;
					}
					else if (sCharacterData.iClass == CHARACTERCLASS_Shaman && Param1 == SKILL_PLAY_SPIRITUAL_MANACLE)
					{
						if (!bStunCount)
						{
							lpCurPlayer->iStunTimeLeft = GetResistancePower(Param2 * 70, sITEMINFO_BIONIC);
							AssaParticle_Stune(lpCurPlayer, Param2 + 1);
						}
					}
					else if (sCharacterData.iClass == CHARACTERCLASS_Shaman && Param1 == SKILL_PLAY_INERTIA)
					{
						lpCurPlayer->PlaySlowCount = Param2 * 70;
						lpCurPlayer->PlaySlowSpeed = 210;
						lpCurPlayer->iDistortion = lpCurPlayer->PlaySlowCount;
						lpCurPlayer->AttackIce = 0;
					}
					else if (Param1 == SKILL_PLAY_ICE_CRYSTAL)
					{
						lpCurPlayer->PlaySlowCount = GetResistancePower(Param2 * 70, sITEMINFO_ICE);
						lpCurPlayer->PlaySlowSpeed = 200;
						lpCurPlayer->AttackIce = 1;
						lpCurPlayer->DmgType[0] = sITEMINFO_ICE;
					}
					else if (Param1 == SKILL_PLAY_FIRE_CRYSTAL)
						cnt = GetResistancePower(cnt, sITEMINFO_FIRE);

					else if (Param1 == SKILL_PLAY_LIGHTNING_CRYSTAL)
					{
						if (!bStunCount)
						{
							lpCurPlayer->iStunTimeLeft = GetResistancePower(Param2 * 70, sITEMINFO_LIGHTING);
							AssaParticle_Stune(lpCurPlayer, Param2 + 1);
							lpCurPlayer->DmgType[0] = sITEMINFO_LIGHTING;
						}
					}
					switch (sCharacterData.iMonsterEffectID)
					{
					case snCHAR_SOUND_COLDEYE:
					case snCHAR_SOUND_FROZEN:
						if ((lpTransAttackData->AttackState & 0xFF) == 0x80)
						{
							lpCurPlayer->PlaySlowCount = GetResistancePower(70 * 4, sITEMINFO_ICE);
							lpCurPlayer->PlaySlowSpeed = 200;
							lpCurPlayer->AttackIce = 1;
							lpCurPlayer->DmgType[0] = sITEMINFO_ICE;
						}
						break;
					case snCHAR_SOUND_FROST:
					case snCHAR_SOUND_DEATHKNIGHT:
						if ((lpTransAttackData->AttackState & 0xFF) == 0x80)
						{
							lpCurPlayer->PlaySlowCount = GetResistancePower(70 * 6, sITEMINFO_ICE);
							lpCurPlayer->PlaySlowSpeed = 200;
							lpCurPlayer->AttackIce = 1;
							lpCurPlayer->DmgType[0] = sITEMINFO_ICE;
						}
						break;
					case snCHAR_SOUND_CHAOSCARA:
					case snCHAR_SOUND_DEVILSHY:
					case smCHAR_SOUND_WLORD:
						if (Param1 == SKILL_PLAY_CHAOSCARA_VAMP && LastSkillParam)
							sinSetMana(sinGetMana() - cnt);
						break;
					case snCHAR_SOUND_STINGRAY:
						if (chrAttackTarget && (lpTransAttackData->AttackState & 0xFF) == 0x80)
						{
							ParkAssaParticle_Posion(chrAttackTarget, STINGRAY_POSION_TIME);
							if (chrAttackTarget == lpCurPlayer)
							{
								len = GetResistancePower(70 * STINGRAY_POSION_TIME, sITEMINFO_POISON);
								lpCurPlayer->PlayPoison[0] = 1;
								lpCurPlayer->PlayPoison[1] = len;
								lpCurPlayer->DmgType[0] = sITEMINFO_POISON;
							}
						}
						break;
					case snCHAR_SOUND_KINGBAT:
						ParkAssaParticle_Posion(chrAttackTarget, STINGRAY_POSION_TIME);
						if (chrAttackTarget == lpCurPlayer)
						{
							len = GetResistancePower(70 * STINGRAY_POSION_TIME, sITEMINFO_POISON);
							lpCurPlayer->PlayPoison[0] = 1;
							lpCurPlayer->PlayPoison[1] = len;
							lpCurPlayer->DmgType[0] = sITEMINFO_POISON;
						}
						break;
					case snCHAR_SOUND_DEVIL_BIRD:
						if (chrAttackTarget)
							ParkDevilBirdAttackNormal(chrAttackTarget);
						break;
					case snCHAR_SOUND_BLOODYKNIGHT:
						if (chrAttackTarget && (lpTransAttackData->AttackState & 0xFF) == 0x80)
						{
							ParkAssaParticle_BloodySkillStun(chrAttackTarget);
							lpCurPlayer->iStunTimeLeft = 70 * 3;
						}
						break;
					case snCHAR_SOUND_HELLHOUND:
						if (chrAttackTarget && (lpTransAttackData->AttackState & 0xFF) == 0x80)
							ParkAssaParticle_HellHoundSkillTaget(chrAttackTarget);
						break;
					case snCHAR_SOUND_CHIMERA:
						if (chrAttackTarget && (lpTransAttackData->AttackState & 0xFF) == 0x80)
							lpCurPlayer->iStunTimeLeft = 70 * 3;
						break;
					case snCHAR_SOUND_BOITATA:
						if ((lpTransAttackData->AttackState & 0xFF) == 0x80)
						{
							lpCurPlayer->PlaySlowCount = GetResistancePower(70 * 6, sITEMINFO_BIONIC);
							lpCurPlayer->PlaySlowSpeed = 30;
						}
						break;
						// º®±ùÊ÷¼õËÙ
					case smCHAR_SOUND_ICEWORM:
						if ((lpTransAttackData->AttackState & 0xFF) == 0x80)
						{
							lpCurPlayer->PlaySlowCount = GetResistancePower(70 * 6, sITEMINFO_ICE);
							lpCurPlayer->PlaySlowSpeed = 200;
							lpCurPlayer->AttackIce = 1;
							lpCurPlayer->DmgType[0] = sITEMINFO_ICE;
						}
						break;
						// º®±ù¶ñÄ§
					case smCHAR_SOUND_MINEBAT:
						if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'H')
							ParkDevilBirdAttackNormal(chrAttackTarget);
						break;
						// ¿óÉ½»úÐµ
					case smCHAR_SOUND_MINEGOLEM:
						if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'H')
						{
							auto sPosition = GetMoveLocation(0, 0, 75 * fONE, 0, Angle.y, 0);
							POINT3D pos;
							pos.x = pX + sPosition.iX;
							pos.y = pY + 48 * fONE;
							pos.z = pZ + sPosition.iZ;

							StartEffectMonster(pX + sPosition.iX, pY + 48 * fONE, pZ + sPosition.iZ, MONSTER_MINEGOLEM_HIT1);
						}
						break;
						// ±ù¼×¶¾Öë
					case smCHAR_SOUND_TARANTULIKA:
						if (psModelAnimation && psModelAnimation->KeyCode == 'J')
						{
							ParkAssaParticle_Posion(chrAttackTarget, STINGRAY_POSION_TIME);
							if (chrAttackTarget == lpCurPlayer)
							{
								len = GetResistancePower(70 * STINGRAY_POSION_TIME, sITEMINFO_POISON);
								lpCurPlayer->PlayPoison[0] = 1;
								lpCurPlayer->PlayPoison[1] = len;
								lpCurPlayer->DmgType[0] = sITEMINFO_POISON;
							}
						}
						break;
						//¶ñÄ§²®¾ô
					case smCHAR_SOUND_TULLA:
						if (sCharacterData.iMonsterType != MONSTERTYPE_Friendly)
						{
							if (chrAttackTarget)
							{
								auto sPosition = GetMoveLocation(0, 0, 70 * fONE, 0, Angle.y, 0);
								StartEffectMonster(pX + sPosition.iX, pY + 42 * fONE, pZ + sPosition.iZ, MONSTER_HULK_HIT1);
							}
						}
						else
						{
							if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'H')
								ParksinSkillEffect_TullaPiercing(this);
						}
						break;
						//¿óÉ½¹ÜÀíÕß
					case smChAR_SOUND_UNDEADMANAGER:
					case smCHAR_SOUND_UNDEADMINER:
						if (psModelAnimation && psModelAnimation->KeyCode == 'H')
							AssParticle_UnDeadManger(this, 1);
						break;
					case smCHAR_SOUND_BONEHOUND:
						if (chrAttackTarget)
						{
							if ((lpTransAttackData->AttackState & 0xFF) == 0x80)
								AssaParticle_BoneHoundSkillHit(chrAttackTarget);
						}
						break;
					}

					if (iCharacterType == CHARACTERTYPE_Player)
						cnt = (cnt - ((lpCurPlayer->sCharacterData.iAbsorbRating*PKMODE_ABSORB) / 100));
					else
						cnt = (cnt - lpCurPlayer->sCharacterData.iAbsorbRating);

					if (cnt <= 0)
						cnt = 1;

					if (abs(lpChar->sCharacterData.iLevel - lpCurPlayer->sCharacterData.iLevel) <= AGING_SUB_LEVEL)
					{
						sinCheckAgingLevel(SIN_AGING_DEFENSE_ARMOR, false);
						sinCheckAgingLevel(SIN_AGING_DEFENSE_ORB, false);
						sinCheckAgingLevel(SIN_AGING_DEFENSE_BOOTS, false);
						sinCheckAgingLevel(SIN_AGING_DEFENSE_GLOVES, false);
						sinCheckAgingLevel(SIN_AGING_DEFENSE_ARMLETS, false);
					}

					CheckCharForm();

					sinSetLife(sinGetLife() - cnt);

					if (sCharacterData.iMonsterEffectID == snCHAR_SOUND_SUCCUBUS)
					{
						if (lpTransAttackData->sRating[0] > 75)
						{
							if (lpTransAttackData->sRating[0] < 80)
								sinSetStamina(sinGetStamina() - ((lpCurPlayer->sCharacterData.sSP.sMax * 6) / 100));
							else
								sinSetMana(sinGetMana() - ((lpCurPlayer->sCharacterData.sMP.sMax * 6) / 100));
						}
					}

					StartEffect(lpCurPlayer->pX, lpCurPlayer->pY + 16 * fONE, lpCurPlayer->pZ, EFFECT_DAMAGE1);
					SetDynLight(lpCurPlayer->pX, lpCurPlayer->pY + 16 * fONE, lpCurPlayer->pZ, 160, 0, 0, 0, 180);

					if (((lpCurPlayer->dwDispAppSkill&SKILL_APPMASK_PHYSICAL_ABSORB) && (lpCurPlayer->dwDispAppSkill&SKILL_APPMASK_HOLY_BODY) == 0) || HolyBody_Undead)
						StartEffect(lpCurPlayer->pX, lpCurPlayer->pY + 24 * fONE, lpCurPlayer->pZ, EFFECT_PHYSICAL_ABSORB_DAMAGE);

					lpCurPlayer->DmgType[1] = FALSE;

					if (lpCurPlayer->psModelAnimation &&
						lpCurPlayer->psModelAnimation->iType != ANIMATIONTYPE_Flinch &&
						lpCurPlayer->psModelAnimation->iType != ANIMATIONTYPE_Potion &&
						lpCurPlayer->psModelAnimation->iType != ANIMATIONTYPE_Attack &&
						lpCurPlayer->psModelAnimation->iType != ANIMATIONTYPE_Skill && cnt > 1)
					{
						lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Flinch);
						CharPlaySound(lpCurPlayer);
						lpCurPlayer->DmgType[1] = TRUE;
					}

					lpCurPlayer->dwDamgeTimer = dwPlayTime + 1000 * 2;
					lpCurPlayer->Damge = cnt;
					lpCurPlayer->DmgBlendValue = 255;

					SendDisplayDamgeToServer(lpCurPlayer->Damge, lpCurPlayer->iID, lpCurPlayer->DmgType[1], lpCurPlayer->DmgType[0]);

					if (sinGetLife() <= 0)
					{
						if (sinQuest_ChangeJob4.CODE == SIN_QUEST_CODE_CHANGEJOB4 && lpCurPlayer->iLoadedMapIndex >= 0 && STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == QUEST_ARENA_FIELD)
						{
							OpenEachPlayer(this);
							sinBattleNpcResult(0);
							sinSetLife(0);
							lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Die);
							CharPlaySound(lpCurPlayer);
							ResetAttackTrans();
							return TRUE;
						}
						lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Die);
						sinSetLife(0);
						CharPlaySound(lpCurPlayer);

						PacketDeadCharacter sPacket;

						sPacket.dwObjectID = iID;
						sPacket.iHeader = PKTHDR_KillCharacter;

						SENDPACKETALL(&sPacket);

						if (sCharacterData.iType != CHARACTERTYPE_Player && iCharacterType != CHARACTERTYPE_Player)
							DeadPlayerExp(lpCurPlayer);

						sinCheckQuest85Die();

						SaveGameData();

						if (sCharacterData.iType == CHARACTERTYPE_Player || iCharacterType == CHARACTERTYPE_Player)
							PlayerKilling(iID);

						ResetAttackTrans();
						SetFullZoomMap(0);
						return TRUE;
					}
					ReformCharForm();
				}
				else
				{
					cInterFace.SetStringEffect(HA_DEFANCE);
					Record_DefenceCount++;
				}
			}
			dwBattleTime = dwPlayTime;
		}
	}

	ResetAttackTrans();

	return TRUE;
}


//À§Ä¡¸¦ ¹Þ¾Æ ¿¹Ãøµ¥ÀÌÅ¸¸¦ ¸¸µé¾î ³Ö´Â´Ù
int Unit::MakePlayBuffFromPosi(int px, int py, int pz, int anX, int anY, int anZ, int act)
{
	int len;
	int sx, sy, sz;
	int x, y, z;
	int mx, my, mz;
	int PlayBuffPosi;
	int cnt;
	int aY;
	int dist;

	if (!smMotionInfo)
		return FALSE;

	len = 0x40;


	if (PlayBuffPosi_End <= 0)
	{
		sx = px;
		sy = py;
		sz = pz;
	}
	else
	{
		PlayBuffPosi = (PlayBuffPosi_End - 1) & PLAYBUFF_MASK;
		sx = sPlayBuff[PlayBuffPosi].iX;
		sy = sPlayBuff[PlayBuffPosi].iY;
		sz = sPlayBuff[PlayBuffPosi].iZ;
	}

	if (sx == px && sy == py && sz == pz)
		aY = anY;
	else
		aY = GetRadian2D(sx, sz, px, pz);

	x = (px - sx) >> FLOATNS;
	z = (py - sy) >> FLOATNS;

	dist = x * x + z * z;
	if (dist > (110 * 110))
	{
		PlayBuffPosi = PlayBuffPosi_End & PLAYBUFF_MASK;

		sPlayBuff[PlayBuffPosi].iX = px;
		sPlayBuff[PlayBuffPosi].iY = py;
		sPlayBuff[PlayBuffPosi].iZ = pz;

		sPlayBuff[PlayBuffPosi].saAngle[0] = 0;
		sPlayBuff[PlayBuffPosi].saAngle[1] = aY;
		sPlayBuff[PlayBuffPosi].saAngle[2] = 0;
		sPlayBuff[PlayBuffPosi].saAngle[3] = 0;

		sPlayBuff[PlayBuffPosi].dwFrame = smPLAYBUFF_FRAME_NONE | 80;
		sPlayBuff[PlayBuffPosi].dwTargetSerial = 0;

		memcpy(sPlayBuff[PlayBuffPosi].sStickItems, wStickItems, sizeof(short) * 4);

		PlayBuffPosi_End++;
		return TRUE;
	}

	mx = ((px - sx) << 8) / len;
	my = ((py - sy) << 8) / len;
	mz = ((pz - sz) << 8) / len;

	x = 0;	y = 0;	z = 0;

	for (cnt = 0; cnt < len; cnt++)
	{
		PlayBuffPosi = (PlayBuffPosi_End + cnt) & PLAYBUFF_MASK;

		sPlayBuff[PlayBuffPosi].iX = sx + (x >> 8);
		sPlayBuff[PlayBuffPosi].iY = sy + (y >> 8);
		sPlayBuff[PlayBuffPosi].iZ = sz + (z >> 8);

		sPlayBuff[PlayBuffPosi].saAngle[0] = 0;
		sPlayBuff[PlayBuffPosi].saAngle[1] = aY;
		sPlayBuff[PlayBuffPosi].saAngle[2] = 0;
		sPlayBuff[PlayBuffPosi].saAngle[3] = 0;

		sPlayBuff[PlayBuffPosi].dwFrame = smPLAYBUFF_FRAME_NONE | 80;
		sPlayBuff[PlayBuffPosi].dwTargetSerial = 0;

		memcpy(sPlayBuff[PlayBuffPosi].sStickItems, wStickItems, sizeof(short) * 4);

		x += mx;
		y += my;
		z += mz;
	}
	PlayBuffPosi_End = PlayBuffPosi_End + len;

	return TRUE;
}

int Unit::MakePlayBuffFromRecvData(PlayBuffer *StartBuff, PlayBuffer *EndBuff, int len)
{
	int cnt;
	int x, y, z;
	int px, py, pz;
	int mx, my, mz;
	int PlayBuffPosi;
	int aX, aY, aZ;
	int saX, saY, saZ;
	int taX, taY, taZ;
	int frameState;
	int frameStep;

	if (!smMotionInfo || len <= 1)
		return FALSE;

	if (!EndBuff)
	{
		PlayBuffPosi = PlayBuffPosi_End & PLAYBUFF_MASK;

		sPlayBuff[PlayBuffPosi].iX = StartBuff->iX;
		sPlayBuff[PlayBuffPosi].iY = StartBuff->iY;
		sPlayBuff[PlayBuffPosi].iZ = StartBuff->iZ;

		sPlayBuff[PlayBuffPosi].saAngle[0] = StartBuff->saAngle[0] & ANGCLIP;
		sPlayBuff[PlayBuffPosi].saAngle[1] = StartBuff->saAngle[1] & ANGCLIP;
		sPlayBuff[PlayBuffPosi].saAngle[2] = StartBuff->saAngle[2] & ANGCLIP;
		sPlayBuff[PlayBuffPosi].saAngle[3] = StartBuff->saAngle[3];

		sPlayBuff[PlayBuffPosi].dwFrame = StartBuff->dwFrame;
		sPlayBuff[PlayBuffPosi].dwTargetSerial = StartBuff->dwTargetSerial;

		memcpy(sPlayBuff[PlayBuffPosi].sStickItems, StartBuff->sStickItems, sizeof(short) * 4);
		PlayBuffPosi_End++;
		return TRUE;
	}

	px = StartBuff->iX;
	py = StartBuff->iY;
	pz = StartBuff->iZ;

	mx = ((EndBuff->iX - px) << 8) / len;
	my = ((EndBuff->iY - py) << 8) / len;
	mz = ((EndBuff->iZ - pz) << 8) / len;

	aX = StartBuff->saAngle[0];
	aY = StartBuff->saAngle[1];
	aZ = StartBuff->saAngle[2];

	taX = ANGLE_180 - EndBuff->saAngle[0];
	taY = ANGLE_180 - EndBuff->saAngle[1];
	taZ = ANGLE_180 - EndBuff->saAngle[2];

	saX = (aX + taX) & ANGCLIP;
	saY = (aY + taY) & ANGCLIP;
	saZ = (aZ + taZ) & ANGCLIP;

	saX = ((saX - ANGLE_180) << 8) / len;
	saY = ((saY - ANGLE_180) << 8) / len;
	saZ = ((saZ - ANGLE_180) << 8) / len;

	if (StartBuff->dwFrame < CHAR_FRAME_MASK)
	{
		frameState = smMotionInfo->MotionInfo[StartBuff->saAngle[3]].iType;

		if (frameState == ANIMATIONTYPE_Walking || frameState == ANIMATIONTYPE_Running)
		{
			aY = GetRadian2D(px, pz, EndBuff->iX, EndBuff->iZ);
			saY = 0;
		}
	}

	x = 0;
	y = 0;
	z = 0;

	taX = 0;
	taY = 0;
	taZ = 0;

	cnt = len - 1;

	if (cnt <= 0)
		frameStep = 80;
	else
		frameStep = (EndBuff->dwFrame - StartBuff->dwFrame) / cnt;

	if (frameStep >= 4096 || frameStep < 20)
		frameStep = 80;

	for (cnt = 0; cnt < len; cnt++)
	{
		PlayBuffPosi = (PlayBuffPosi_End + cnt) & PLAYBUFF_MASK;

		sPlayBuff[PlayBuffPosi].iX = px + (x >> 8);
		sPlayBuff[PlayBuffPosi].iY = py + (y >> 8);
		sPlayBuff[PlayBuffPosi].iZ = pz + (z >> 8);

		sPlayBuff[PlayBuffPosi].saAngle[0] = aX & ANGCLIP;
		sPlayBuff[PlayBuffPosi].saAngle[1] = aY & ANGCLIP;
		sPlayBuff[PlayBuffPosi].saAngle[2] = aZ & ANGCLIP;
		sPlayBuff[PlayBuffPosi].saAngle[3] = StartBuff->saAngle[3];

		sPlayBuff[PlayBuffPosi].dwFrame = smPLAYBUFF_FRAME_NONE | frameStep;

		sPlayBuff[PlayBuffPosi].dwTargetSerial = StartBuff->dwTargetSerial;

		memcpy(sPlayBuff[PlayBuffPosi].sStickItems, StartBuff->sStickItems, sizeof(short) * 4);

		x += mx;
		y += my;
		z += mz;

		taX += saX;
		taY += saY;
		taZ += saZ;
	}

	sPlayBuff[PlayBuffPosi_End&PLAYBUFF_MASK].dwFrame = StartBuff->dwFrame;
	sPlayBuff[(PlayBuffPosi_End + len - 1)&PLAYBUFF_MASK].dwFrame = EndBuff->dwFrame;

	PlayBuffPosi_End = PlayBuffPosi_End + len;

	return TRUE;
}

//»ó´ë ÇÃ·¹ÀÌ¾îÀÇ µ¥ÀÌÅ¸ ÃÊ±â ¼³Á¤
int Unit::FormSetPlayerInfo()
{
	int cnt = 0;

	if (!Pattern)
	{
		char szBuff[128];

		wsprintf(szBuff, "Mesh Pattern Error [ %s ] ( %s %s )", sCharacterData.szName, sCharacterData.Player.szBodyModel, sCharacterData.Player.szHeadModel);
		Record_ClinetLogFile(szBuff);
	}

	PHeight = pY;

	sCharacterData.bUpdateInfo[1] = 0xFF;

	if (this != lpCurPlayer && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType == ANIMATIONTYPE_Idle && abs(lpCurPlayer->pX - pX) < 32 * fONE && abs(lpCurPlayer->pZ - pZ) < 32 * fONE)
	{
		GAMEMAP->SetStartPoint();
	}

	if (sCharacterData.iType != CHARACTERTYPE_Monster)
	{
		iLoadedMapIndex = -1;
		if (smGameStage[0] && Pattern)
		{
			cnt = smGameStage[0]->GetFloorHeight(pX, pY, pZ, Pattern->SizeHeight);
			iLoadedMapIndex = 0;
		}
		if (cnt == CLIP_OUT && smGameStage[1])
			iLoadedMapIndex = 1;
	}

	PatSizeLevel = 1;

	PlayBuffPosi_End = 0;
	iPlayBuffCount = 0;

	DisplayAlpha = -256;
	DispLifeBar = 0;

	switch (sCharacterData.iMonsterEffectID)
	{
	case snCHAR_SOUND_FIGON:
	case smCHAR_SOUND_INFERNO:
		if (Pattern && Pattern->TmParent)
		{
			HvLeftHand.ObjBip = Pattern->TmParent->GetObjectFromName("Bip01 L Finger1");
			HvRightHand.ObjBip = Pattern->TmParent->GetObjectFromName("Bip01 R Finger1");
		}
		else
		{
			HvLeftHand.ObjBip = 0;
			HvRightHand.ObjBip = 0;
		}
		break;

	case snCHAR_SOUND_ILLUSIONKNIGHT:
		RendAlpha = -180;
		break;

	case snCHAR_SOUND_MUDY:
		RenderLatter = TRUE;
		break;
	case snCHAR_SOUND_WOLVERLIN:
		if (sCharacterData.iType == CHARACTERTYPE_Monster)
		{
			sAddColorEffect[SMC_R] = 100;
			sAddColorEffect[SMC_G] = 100;
		}
		break;
	case snCHAR_SOUND_SEN:
		if (Pattern && Pattern->TmParent) {
			HvLeftHand.ObjBip = Pattern->TmParent->GetObjectFromName("Bip01");
		}
		else {
			HvLeftHand.ObjBip = 0;
			HvRightHand.ObjBip = 0;
		}
		break;

	case snCHAR_SOUND_MUTANTTREE:
		if (Pattern && Pattern->TmParent) {
			HvLeftHand.ObjBip = Pattern->TmParent->GetObjectFromName("Bip05");
		}
		else {
			HvLeftHand.ObjBip = 0;
			HvRightHand.ObjBip = 0;
		}
		break;

	case snCHAR_SOUND_SHADOW:
	case smCHAR_SOUND_DMYSTERY:
		if (Pattern && Pattern->TmParent)
		{
			HvLeftHand.ObjBip = Pattern->TmParent->GetObjectFromName("Bip01 L UpperArm");
			HvRightHand.ObjBip = Pattern->TmParent->GetObjectFromName("Bip01 R UpperArm");
		}
		else
		{
			HvLeftHand.ObjBip = 0;
			HvRightHand.ObjBip = 0;
		}
		break;

	case snCHAR_SOUND_MRGHOST:
		RendAlpha = -80;
		break;

	case snCHAR_SOUND_FURY:
		AssaParticle_Fury_Eye(this);

		switch (sCharacterData.iLevel)
		{
		case 118:
			sAddColorEffect[SMC_R] = 100;
			sAddColorEffect[SMC_G] = 100;
			RendAlpha = -80;
			break;
		case 119:
			sAddColorEffect[SMC_R] = 100;
			RendAlpha = -80;
			break;
		case 120:
			sAddColorEffect[SMC_B] = 100;
			RendAlpha = -80;
			break;
		}
		break;

	case snCHAR_SOUND_BEEVIL:
		RenderLatter = TRUE;
		break;
		// ÊØ»¤Ê¥Í½
	case snCHAR_SOUND_GUARDIAN_SAINT:

		if (sCharacterData.iLevel == 120)
		{
			sAddColorEffect[SMC_R] = 240;
			sAddColorEffect[SMC_G] = 10;
			sAddColorEffect[SMC_B] = 0;
		}
		else
		{
			sAddColorEffect[SMC_R] = 80;
			sAddColorEffect[SMC_G] = 80;
			sAddColorEffect[SMC_B] = 20;
		}

		AssaParticleClanMonster(this);
		break;
	case  snCHAR_SOUND_CHAINGOLEM:
		AssaParticle_MonsterIronChainGolem(this);
		break;
	case snCHAR_SOUND_RUNICGUARDIAN:
		AssaParticle_MonsterRunicGuardianHand(this);
		break;
	case snCHAR_SOUND_BABEL:
		AssaParticle_MonsterRunicGuardianBossWeapon(this);
		break;
	case snCHAR_SOUND_CHAOSCARA:
		ParkAssaParticle_MonsterIceChaosKara(this);
		break;
	case snCHAR_SOUND_DEATHKNIGHT:
		ParkAssaParticle_MonsterIceValentoBody(this);
		break;
	case snCHAR_SOUND_S_F_ELEMENTAL:
		SkillArchMageFireElementalHand(this);
		break;
	case snCHAR_SOUND_NPC_SKILLMASTER:
		if (Pattern && Pattern->TmParent)
			AttackObjBip = Pattern->TmParent->GetObjectFromName("bip01 weapon");
		break;
	case snCHAR_SOUND_NPC_MAGICMASTER:
		if (Pattern && Pattern->TmParent)
			AttackObjBip = Pattern->TmParent->GetObjectFromName("Bip01 staff02");
		break;
	case snCHAR_SOUND_CASTLE_SOLDER_A:
	case snCHAR_SOUND_CASTLE_SOLDER_B:
	case snCHAR_SOUND_CASTLE_SOLDER_C:
		if (Pattern && Pattern->TmParent)
			AttackObjBip = Pattern->TmParent->GetObjectFromName("Bip01 Effect");
		break;
	case snCHAR_SOUND_KELVEZU:
		ParkKelvezuJin(this);
		break;
	case snCHAR_SOUND_REVIVED_KNIGHT:
		if (Pattern && Pattern->TmParent)
			HvRightHand.ObjBip = Pattern->TmParent->GetObjectFromName("Bip01 R Hand");
		break;
	case snCHAR_SOUND_REVIVED_PIKEMAN:
		if (Pattern && Pattern->TmParent)
			AttackObjBip = Pattern->TmParent->GetObjectFromName("bip01 wea");
		break;
	case snCHAR_SOUND_REVIVED_ARCHER:
		if (Pattern && Pattern->TmParent)
			HvRightHand.ObjBip = Pattern->TmParent->GetObjectFromName("Bip01 R Hand");
		break;
	case smCHAR_SOUND_TULLA:
		if (sCharacterData.iMonsterType != MONSTERTYPE_Friendly)
			AssaParticleTulla(this);
		break;
	case MONSTEREFFECTID_Draxos:
		AssaParticle_Draxos(this);
		break;
	case smCHAR_SOUND_GREEDY:
		AssParticle_Greedy(this);
		break;
	case smCHAR_SOUND_MIDRANDA:
		AssParticle_Midranda(this);
		break;
	case smCHAR_SOUND_ARHDYRA:
		AssParticle_Midranda(this);
		break;
	case smCHAR_SOUND_FAUGN:
		AssParticle_Faugn(this);
		break;
	case smCHAR_SOUND_YAGDITHA:
		AssParticle_Yagditha(this);
		break;
	}

	if (sCharacterData.sGlow == MONSTER_CLASS_BOSS)
	{
		if (sCharacterData.iType == CHARACTERTYPE_Monster)
		{
			sAddColorEffect[SMC_R] = 130;
			sAddColorEffect[SMC_G] = 50;
			sAddColorEffect[SMC_B] = 70;
		}
	}

	return TRUE;
}
int Unit::SetTransPlayerInfo(smTRNAS_PLAYERINFO *lpTransPlayerInfo)
{
	memcpy(&sCharacterData, &lpTransPlayerInfo->sCharacterData, sizeof(CharacterData));
	ResetAttackTrans();

	if (!bLoading)
		AddLoaderPattern((Unit *)&Head, sCharacterData.Player.szBodyModel, sCharacterData.Player.szHeadModel);

	pX = lpTransPlayerInfo->x;
	pY = lpTransPlayerInfo->y;
	pZ = lpTransPlayerInfo->z;

	FormSetPlayerInfo();

	if (sCharacterData.iClanID)
	{
		iClanInfoIndex = ReadClanInfo(sCharacterData.iClanID);
		dwClanInfoTime = dwPlayTime;

		if (GetClanCode(sCharacterData.iClanID) == rsBlessCastle.dwMasterClan)
			Clan_CastleMasterFlag = TRUE;
	}

	iCharacterType = CHARACTERTYPE_None;

	return TRUE;
}
int Unit::SetTransPlayerInfoQuick(smTRNAS_PLAYERINFO_QUICK *lpTransPlayerInfo)
{
	int len;

	len = sizeof(smTRNAS_PLAYERINFO_QUICK) - lpTransPlayerInfo->size;

	ZeroMemory(&sCharacterData, sizeof(CharacterData));
	sCharacterData.sHP.sMin = 10;
	sCharacterData.sHP.sMax = 50;

	memcpy(&sCharacterData, &lpTransPlayerInfo->sCharacterData, sizeof(CharacterData) - len);
	ResetAttackTrans();

	if (!bLoading)
		AddLoaderPattern((Unit *)&Head, sCharacterData.Player.szBodyModel, sCharacterData.Player.szHeadModel);

	pX = lpTransPlayerInfo->x;
	pY = lpTransPlayerInfo->y;
	pZ = lpTransPlayerInfo->z;

	FormSetPlayerInfo();

	if (sCharacterData.iClanID)
	{
		iClanInfoIndex = ReadClanInfo(sCharacterData.iClanID);
		dwClanInfoTime = dwPlayTime;

		if (GetClanCode(sCharacterData.iClanID) == rsBlessCastle.dwMasterClan)
			Clan_CastleMasterFlag = TRUE;
	}

	iCharacterType = CHARACTERTYPE_None;

	return TRUE;
}
int Unit::RecvPlayData2(char *lpData)
{
	PacketPlayDataMinor *lpPlayData;
	int RecvCode;
	int cnt;
	int len;
	int LastBuffPosi_End;
	int act;
	char *lpBuff;
	int	Code, Size;
	Unit	*lpChar;

	RecvCode = ((int *)lpData)[1];

	switch (RecvCode)
	{
	case smTRANSCODE_PLAYDATA1:
		lpPlayData = (PacketPlayDataMinor *)lpData;

		act = lpPlayData->saAngle[3];
		MakePlayBuffFromPosi(lpPlayData->iX, lpPlayData->iY, lpPlayData->iZ, lpPlayData->saAngle[0], lpPlayData->saAngle[1], lpPlayData->saAngle[2], act);
		MoveCnt = 0;

		LastPlayDataType = 1;
		sCharacterData.bUpdateInfo[1] = 0xFF;
		break;

	case smTRANSCODE_TRANSPLAYDATA:
		PacketPlayData	*lpTransPlayData;
		PlayBufferData	*lpTransPlayBuff;
		PlayBufferData	*lpTransPlayBuff2;

		LastPlayDataType = 0;

		lpTransPlayData = (PacketPlayData *)lpData;
		lpTransPlayBuff = (PlayBufferData *)(lpData + sizeof(PacketPlayData));

		LastBuffPosi_End = PlayBuffPosi_End;

		sCharacterData.sHP.sMin = lpTransPlayData->sHp[0];
		sCharacterData.sHP.sMax = lpTransPlayData->sHp[1];

		sHPLong.iMin = lpTransPlayData->sHPLong.iMin;
		sHPLong.iMax = lpTransPlayData->sHPLong.iMax;

		if (LevelLog)
		{
			if (sCharacterData.iType == CHARACTERTYPE_Player && lpTransPlayData->bEventInfo[TRANS_PLAYDATA_EVENT_LEVEL] > LevelLog)
			{
				StartEffect(pX, pY + 32 * fONE, pZ, EFFECT_LEVELUP1);
				esPlaySound(7, GetDistVolume(pX, pY, pZ));
			}
		}

		LevelLog = lpTransPlayData->bEventInfo[TRANS_PLAYDATA_EVENT_LEVEL];
		PotionLog = lpTransPlayData->bEventInfo[TRANS_PLAYDATA_EVENT_POTION] & 0x0F;
		CriticalLog = lpTransPlayData->bEventInfo[TRANS_PLAYDATA_EVENT_POTION] >> 4;
		dwDispAppSkill = lpTransPlayData->bEventInfo[TRANS_PLAYDATA_EVENT_SKIL];

		if (CriticalLog >= 8) CriticalLog = -1;
		AttackCritcal = CriticalLog;

		if (lpTransPlayData->iPlayBuffCount > 1)
		{
			for (cnt = 0; cnt < lpTransPlayData->iPlayBuffCount - 1; cnt++)
			{
				lpTransPlayBuff2 = lpTransPlayBuff + 1;

				len = lpTransPlayBuff2->iCount - lpTransPlayBuff->iCount;
				MakePlayBuffFromRecvData(&lpTransPlayBuff->sPlayBuff, &lpTransPlayBuff2->sPlayBuff, len);

				lpTransPlayBuff++;
			}

			dwTarget = lpTransPlayData->dwTarget;

			if (sCharacterData.bUpdateInfo[1] == 0xFF)
				sCharacterData.bUpdateInfo[1] = lpTransPlayData->bUpdateInfo[1];
			else
			{
				if (lpTransPlayData->bUpdateInfo[1] != sCharacterData.bUpdateInfo[1])
				{
					if (lpTransPlayData->bUpdateInfo[1] < sCharacterData.bUpdateInfo[1])
						LearnSkillEffect(this);

					sCharacterData.bUpdateInfo[1] = lpTransPlayData->bUpdateInfo[1];
				}
			}

			lpTransPlayBuff++;
		}
		else
		{
			MakePlayBuffFromRecvData(&lpTransPlayBuff->sPlayBuff, 0, 0);
			if (iPlayBuffCount == PlayBuffPosi_End)
			{
				if (DisplayFlag)
				{
					pX = lpTransPlayBuff->sPlayBuff.iX;
					pY = lpTransPlayBuff->sPlayBuff.iY;
					pZ = lpTransPlayBuff->sPlayBuff.iZ;

					if (lpTransPlayBuff->sPlayBuff.sStickItems[smPLAYBUFF_ITEM_LEFT] != wStickItems[smPLAYBUFF_ITEM_LEFT])
					{
						if (lpTransPlayBuff->sPlayBuff.sStickItems[smPLAYBUFF_ITEM_LEFT] >= 0)
						{
							ItemData * pItem = ITEMHANDLE->GetItemDataByNumber(lpTransPlayBuff->sPlayBuff.sStickItems[smPLAYBUFF_ITEM_LEFT]);

							if (pItem)
							{
								SetTool(pItem->sBaseItemID.ToInt(), hvPOSI_LHAND);
								HvLeftHand.ColorBlink = 0;
								HvLeftHand.ColorEffect = 0;
								HvLeftHand.ElementEffect = 0;
							}
						}
						else
							SetTool(0, hvPOSI_LHAND);
					}

					if (lpTransPlayBuff->sPlayBuff.sStickItems[smPLAYBUFF_ITEM_RIGHT] != wStickItems[smPLAYBUFF_ITEM_RIGHT])
					{
						if (lpTransPlayBuff->sPlayBuff.sStickItems[smPLAYBUFF_ITEM_RIGHT] >= 0)
						{
							ItemData * pItem = ITEMHANDLE->GetItemDataByNumber(lpTransPlayBuff->sPlayBuff.sStickItems[smPLAYBUFF_ITEM_RIGHT]);

							if (pItem)
							{
								SetTool(pItem->sBaseItemID.ToInt(), hvPOSI_RHAND);
								HvRightHand.ColorBlink = 0;
								HvRightHand.ColorEffect = 0;
								HvRightHand.ElementEffect = 0;
							}
						}
						else
							SetTool(0, hvPOSI_RHAND);
					}
					if (lpTransPlayBuff->sPlayBuff.sStickItems[smPLAYBUFF_ITEM_BODY] != wStickItems[smPLAYBUFF_ITEM_BODY])
					{
						SetChrArmor(this, lpTransPlayBuff->sPlayBuff.sStickItems[smPLAYBUFF_ITEM_BODY]);
						wStickItems[smPLAYBUFF_ITEM_BODY] = lpTransPlayBuff->sPlayBuff.sStickItems[smPLAYBUFF_ITEM_BODY];
					}
				}
			}

			lpTransPlayBuff++;
		}

		if (lpTransPlayData->bUpdateInfo[0] != sCharacterData.bUpdateInfo[0])
		{
			if (!dwUpdateCharInfoTime || (dwUpdateCharInfoTime + 1000) < dwPlayTime)
			{
				Send_GetCharInfo(iID, ServerCode);

				if (sCharacterData.iMonsterEffectID == snCHAR_SOUND_HUNGKY && !dwUpdateCharInfoTime)
				{
					StartEffect(pX, pY + 48 * fONE, pZ, EFFECT_RETURN1);
					SetDynLight(pX, pY, pZ, 50, 100, 70, 0, 300, 1);

					if (psModelAnimation)
					{
						auto iType = psModelAnimation->iType;
						psModelAnimation->iType = ANIMATIONTYPE_Special;
						CharPlaySound(this);
						psModelAnimation->iType = iType;
					}
				}
				if (sCharacterData.iMonsterEffectID == snCHAR_SOUND_DEADHOPT && !dwUpdateCharInfoTime)
				{
					StartEffect(pX, pY + 48 * fONE, pZ, EFFECT_RETURN1);
					SetDynLight(pX, pY, pZ, 50, 100, 70, 0, 300, 1);

					if (psModelAnimation)
					{
						auto iType = psModelAnimation->iType;
						psModelAnimation->iType = ANIMATIONTYPE_Special;
						CharPlaySound(this);
						psModelAnimation->iType = iType;
					}
				}

				if (sCharacterData.iMonsterEffectID == snCHAR_SOUND_BEBECHICK && !dwUpdateCharInfoTime)
				{
					StartEffect(pX, pY + 48 * fONE, pZ, EFFECT_RETURN1);
					SetDynLight(pX, pY, pZ, 50, 100, 70, 0, 300, 1);

					if (psModelAnimation)
					{
						auto iType = psModelAnimation->iType;
						psModelAnimation->iType = ANIMATIONTYPE_Special;
						CharPlaySound(this);
						psModelAnimation->iType = iType;
					}
				}

				dwUpdateCharInfoTime = dwPlayTime;
			}
		}
		
		if (lpCurPlayer->iLoadedMapIndex >= 0 &&
			((STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapType == MAPTYPE_BlessCastle &&
				CastleBattleZone_LineZ > lpCurPlayer->pZ) ||
				(STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == PK_FieldState.FieldCode && PK_FieldState.dwPlay_FieldTime > dwPlayTime && !dwExclusiveNum)))
		{
			if (iCharacterType == CHARACTERTYPE_None &&
				sCharacterData.iType == CHARACTERTYPE_Player &&
				(sCharacterData.iClanID == 0 || sCharacterData.iClanID != lpCurPlayer->sCharacterData.iClanID))
			{
				if (STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID != PK_FieldState.FieldCode || !dwExclusiveNum)
				{
					iCharacterType = sCharacterData.iType;
					sCharacterData.iType = CHARACTERTYPE_Monster;
				}
			}
		}
		else
		{
			if (iCharacterType)
			{
				sCharacterData.iType = iCharacterType;
				iCharacterType = CHARACTERTYPE_None;
			}
		}

		int ChkIceFlag = 0;
		int ChkPoisonFlag = 0;
		int ChkFireFlag = 0;
		DWORD	TradeMsgCode = 0;

		PlayVanish = 0;
		TradeMsgCode = dwTradeMsgCode;
		dwTradeMsgCode = 0;
		PlayCurseQuest = 0;

		if (lpTransPlayData->bEventInfo[TRANS_PLAYDATA_EVENT_EXT])
		{
			lpBuff = (char *)lpTransPlayBuff;

			for (cnt = 0; cnt < lpTransPlayData->bEventInfo[TRANS_PLAYDATA_EVENT_EXT]; cnt++)
			{
				Code = ((int *)lpBuff)[1];
				Size = ((int *)lpBuff)[0];

				switch (Code)
				{
				case smTRANSCODE_EFFECT_ITEM:
					SetTransEffectItems((PacketBuffData *)lpBuff);
					break;
				case smTRANSCODE_EFFECT_ELEMENT:
					SetTransEffectElement((PacketBuffData *)lpBuff);
					break;
				case smTRANSCODE_EFFECT_WEAPON:
					SetTransEffectWeapon((PacketBuffData *)lpBuff);
					break;
				case smTRANSCODE_EFFECT_STUN:
					if (sCharacterData.sHP.sMin > 0)
						AssaParticle_Stune(this, 4);
					break;
				case smTRANSCODE_EFFECT_CURSE:
					if (sCharacterData.sHP.sMin > 0)
						StartEffect_Serqbus_Skill2(this, 4);
					break;
				case smTRANSCODE_EFFECT_ICE:
					if (((PacketBuffData *)lpBuff)->iTime)
						iDistortion = 120;
					else if (((PacketBuffData *)lpBuff)->iClass)
						PlayWeb = 120;
					else
					{
						iDistortion = 0;
						PlayWeb = 0;
						if (AttackIce <= 0)
							AttackIce = 1;
						ChkIceFlag = TRUE;
					}
					break;
				case smTRANSCODE_EFFECT_POISION:
					if (DispPoison <= 0)
						DispPoison = 1;
					ChkPoisonFlag = TRUE;
					break;
				case smTRANSCODE_EFFECT_FIRE:
					if (DispFire <= 0)
						DispFire = 1;
					ChkFireFlag = TRUE;
					break;
				case smTRANSCODE_EFFECT_CURSE_QUEST:
					PlayCurseQuest = 1;
					break;
				case smTRANSCODE_EFFECT_VANISH:
					PlayVanish = ((PacketBuffData *)lpBuff)->dwItemID;
					PlayVague = ((PacketBuffData *)lpBuff)->iTime;
					break;
				case smTRANSCODE_EFFECT_KEEPSKILL:
					PacketBuffData *lpEffect_Item;

					lpEffect_Item = (PacketBuffData *)lpBuff;
					int ItemTime;
					ItemTime = 5;
					// »áÐÄÒ»»÷
					if (lpEffect_Item->iClass == CHARACTERCLASS_Fighter && lpEffect_Item->dwItemID == SKILL_PLAY_CONCENTRATION)
						AssaParticle_ConcentrationEffect(this, ItemTime, SKILL_CONCENTRATION, FALSE);
					// ´ÌÉ±Ö®¸«
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Fighter && lpEffect_Item->dwItemID == SKILL_PLAY_SWIFT_AXE)
						AssaParticle_SwiftAxeEffect(this, ItemTime, SKILL_SWIFT_AXE, FALSE);
					// ·è¿ñÅ­ºð
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Fighter && lpEffect_Item->dwItemID == SKILL_PLAY_BERSERKER)
						SkillWarriorBetserker(this, float(ItemTime), FALSE);
					// ÖÚÉñÖ®Å­
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Fighter && lpEffect_Item->dwItemID == SKILL_PLAY_B_BERSERKER)
						SkillBloodyBerserker(this, float(ItemTime), FALSE);
					// Áé¹â»¤Ìå
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Mechanician && lpEffect_Item->dwItemID == SKILL_PLAY_PHYSICAL_ABSORB)
						StartSkill(pX, pY, pZ, 0, Angle.y, 0, this, SKILL_SHIELD1, lpEffect_Item->iScale);
					// Áé¹â·ÉÑï // ¸ÄÁ¼×¨¼Ò
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Mechanician && lpEffect_Item->dwItemID == SKILL_PLAY_AUTOMATION)
						StartSkill(pX, pY, pZ, 0, Angle.y, 0, this, SKILL_SHIELD2, lpEffect_Item->iScale);
					// ½ðÊôÖØ¼×
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Mechanician && lpEffect_Item->dwItemID == SKILL_PLAY_METAL_ARMOR)
						AssaParticle_MetalArmorEffect(this, ItemTime);
					// ·ÀÓùµç²¨
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Mechanician && lpEffect_Item->dwItemID == SKILL_PLAY_SPARK_SHIELD)
						AssaParticle_SparkShieldEffect(this, ItemTime);
					// ¿ìËÙ´ò»÷
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Mechanician && lpEffect_Item->dwItemID == SKILL_PLAY_H_SONIC)
						AssaParticle_HyperSonic(this, ItemTime);
					// Õ½Éñ×£¸£
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Mechanician && lpEffect_Item->dwItemID == SKILL_PLAY_P_ENHENCE)
						AssaParticle_EnhenceEffect(this, ItemTime);
					// ´ÅÐÔÇòÌå
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Mechanician && lpEffect_Item->dwItemID == SKILL_PLAY_MAGNETIC_SPHERE)
						SkillMetalionSphereEffect(this, float(ItemTime), (float)Magnetic_Sphere_AttackDelay[lpEffect_Item->iScale - 1]);
					// Áé»êÖ®Ó¥
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Archer && lpEffect_Item->dwItemID == SKILL_PLAY_FALCON)
						StartSkill(pX, pY, pZ, 0, 0, 0, this, SKILL_FALCON, ItemTime);
					// »Æ½ðÁÔÓ¥
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Archer && lpEffect_Item->dwItemID == SKILL_PLAY_GOLDEN_FALCON)
						StartSkill(pX, pY, pZ, 0, 0, 0, this, SKILL_GOLDEN_FALCON, ItemTime);
					// ×ÔÈ»Ö®¹â
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Archer && lpEffect_Item->dwItemID == SKILL_PLAY_FORCE_OF_NATURE)
						SkillSagittarionForceOfNature2(this, float(ItemTime));
					// Ç±ÄÜ¼¤·¢
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Pikeman && lpEffect_Item->dwItemID == SKILL_PLAY_AMPLIFIED)
						StartSkill(pX, pY, pZ, 0, Angle.y, 0, this, SKILL_SHIELD1, 1);
					// ×·Ãü¾¢·ç
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Atalanta && lpEffect_Item->dwItemID == SKILL_PLAY_WINDY)
						AssaParticle_Windy(this, ItemTime);
					// Õ½ÀõÅØÏø
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Atalanta && lpEffect_Item->dwItemID == SKILL_PLAY_TRIUMPH_OF_VALHALLA)
						AssaParticle_TriumphOfValhalla(this, ItemTime);
					// Íß¶û¹þÀ­
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Atalanta && lpEffect_Item->dwItemID == SKILL_PLAY_HALL_OF_VALHALLA)
						SkillValhallaHallOfValhallaHandEffect(this, float(ItemTime));
					// ±ùËª±êÇ¹
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Atalanta && lpEffect_Item->dwItemID == SKILL_PLAY_FROST_JAVELIN)
						SkillParticle_FrostJavelin(this, float(ItemTime));
					// ÇáÎè·ÉÑï
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Atalanta && lpEffect_Item->dwItemID == SKILL_PLAY_TALARIA)
						AssaParticle_TaltriaEffect(this, ItemTime);
					// Ê¥¹â»¤Ìå
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Knight && lpEffect_Item->dwItemID == SKILL_PLAY_HOLY_BODY)
						StartSkill(pX, pY, pZ, 0, Angle.y, 0, this, SKILL_SHIELD1, lpEffect_Item->iScale);
					// ÉñÁ¦ÖØ»÷
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Knight && lpEffect_Item->dwItemID == SKILL_PLAY_HOLY_VALOR)
						AssaParticle_HolyValor_Member(this, ItemTime);
					// ÌìÓÓÉñîø
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Knight && lpEffect_Item->dwItemID == SKILL_PLAY_DRASTIC_SPIRIT)
						AssaParticle_DrasticSpirit_JangEffect(this, ItemTime);
					// Ê¥ÁéÖ®Îü
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Knight && lpEffect_Item->dwItemID == SKILL_PLAY_DIVINE_INHALATION)
						AssaParticle_DivineInhalationPart(this, ItemTime);
					// ¾´ÉñÖ®¶Ü
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Knight && lpEffect_Item->dwItemID == SKILL_PLAY_GODLY_SHIELD)
						AssaParticle_DivineInhalationPart(this, ItemTime);
					// ÉÏµÛ×£¸£
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Knight && lpEffect_Item->dwItemID == SKILL_PLAY_GODS_BLESS)
						SkillSaintGodBless(this, float(ItemTime));
					// ÍöÁéÖ®Öä
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Knight && lpEffect_Item->dwItemID == SKILL_PLAY_H_BENEDIC)
						sinEffect_Benedic(lpChar, ItemTime);
					// ¼¯ºÏÖ®Êõ
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Magician && lpEffect_Item->dwItemID == SKILL_PLAY_ZENITH)
						sinEffect_Zenith(this, ItemTime, 0);
					// Ä§·¨ÊØ»¤
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Magician && lpEffect_Item->dwItemID == SKILL_PLAY_ENERGY_SHIELD)
						AssaParticle_EnergyShield(this, ItemTime);
					// Áé»êÕÙ»½
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Magician && lpEffect_Item->dwItemID == SKILL_PLAY_SPIRIT_ELEMENTAL)
						AssaParticle_SpiritElemental(this, ItemTime);
					// ÔªËØÖ®½£
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Magician && lpEffect_Item->dwItemID == SKILL_PLAY_DANCING_SWORD)
					{
						switch (lpEffect_Item->iScale & 0xF)
						{
						case 0:
							AssaParticle_DancingSwordIce(this, ItemTime, (lpEffect_Item->iScale >> 8) & 0xF);
							break;
						case 1:
							AssaParticle_DancingSwordFire(this, ItemTime, (lpEffect_Item->iScale >> 8) & 0xF);
							break;
						}
					}
					// Ê¥¹â·¨Õó
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Magician && lpEffect_Item->dwItemID == SKILL_PLAY_T_ANIMA)
						sinEffect_Anima(this, ItemTime, 0);
					// ÉñÊ¥·´Éä
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Priestess && lpEffect_Item->dwItemID == SKILL_PLAY_HOLY_REFLECTION)
						sinSkillEffect_Holy_ReflectionEffect(this, ItemTime);
					// ÉñÊ¥Ö®¹â
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Priestess && lpEffect_Item->dwItemID == SKILL_PLAY_VIRTUAL_LIFE)
						AssaParticle_VirtualLifeEffect(this, ItemTime);
					// ÌìÅ®É¢»¨
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Priestess && lpEffect_Item->dwItemID == SKILL_PLAY_B_KRISHNA)
						sinEffect_Krishna(this, ItemTime);
					// ÉñÊ¥ÌìÊ¹
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Priestess && lpEffect_Item->dwItemID == SKILL_PLAY_SUMMON_MUSPELL)
						SkillCelestialMusPel(this, float(ItemTime), (float)Summon_Muspell_Attack_Delay[lpEffect_Item->iScale - 1], SKILL_SUMMON_MUSPELL);
					// Ãô½ÝÖ®Á¦
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Assassin && lpEffect_Item->dwItemID == SKILL_PLAY_ALAS)
						AssaCodeSkillEffect("Alas", this, ItemTime, SKILL_ALAS);
					// Ãô½Ý´óÊ¦
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Assassin && lpEffect_Item->dwItemID == SKILL_PLAY_INPES)
						AssaCodeSkillEffect("Inpes", this, ItemTime, SKILL_INPES);
					// Âõ¿Ë¶û
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Shaman && lpEffect_Item->dwItemID == SKILL_PLAY_ADVENT_MIGAL)
						SkillCelestialMusPel(this, (float)ItemTime, 0, SKILL_ADVENT_MIGAL);
					// ÆíÓêÊ¦
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Shaman && lpEffect_Item->dwItemID == SKILL_PLAY_RAINMAKER)
						AssaCodeSkillEffect("RainMaker2", this, ItemTime, SKILL_RAIN_MAKER);
					// Ã×µÂÀ¼´ï
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Shaman && lpEffect_Item->dwItemID == SKILL_PLAY_ADVENT_MIDRANDA)
						SkillCelestialMusPel(this, (float)ItemTime, 0, SKILL_ADVENT_MIDRANDA);
					// ÖäÊõÐÅÑö
					else if (lpEffect_Item->iClass == CHARACTERCLASS_Shaman && lpEffect_Item->dwItemID == SKILL_PLAY_CREED)
						AssaCodeSkillEffect("CreedKeep", this, ItemTime, SKILL_CREED);

					else if (lpEffect_Item->dwItemID == SKILL_PLAY_BLESS_SIEGE_ITEM)
						PlayInvincible = 70 * 5;
					break;
					// ³á°òÐ­Òé
				case smTRANSCODE_EFFECT_WING:
					if (((PacketBuffData *)lpBuff)->dwItemID)
					{
						this->dwWingEffectCode = ((PacketBuffData *)lpBuff)->dwItemID;
						ParkWingEffect(this, ((PacketBuffData *)lpBuff)->dwItemID);
					}
					break;
					// µÈ¼¶·¢¹â
				case smTRANSCODE_EFFECT_LEVEL:
					AssParticle_AdvEffect(this);
					break;
				case smTRANSCODE_EFFECT_PERSHOP:
					dwTradeMsgCode = ((PacketBuffData *)lpBuff)->dwItemID;

					if (TradeMsgCode != dwTradeMsgCode)
					{
						wsprintf(szTradeMessage, "%s :", sCharacterData.szName);
						SendCommand_AreaServer(smTRANSCODE_MYSHOP_MESSAGE, 0, iID, dwTradeMsgCode, 0);
					}
					break;
				case smTRANSCODE_EFFECT_LOWPET:
					if (((PacketBuffData *)lpBuff)->iTime)
						lpChar = FindChrPlayer(((PacketBuffData *)lpBuff)->iTime);
					else
						lpChar = 0;

					switch (((PacketBuffData *)lpBuff)->dwItemID)
					{
					case 1:
						g_LowLevelAddIdlePet(this, PET_TERRY, lpChar);
						break;
					case 2:
						g_LowLevelAddIdlePet(this, PET_NEPSYS, lpChar);
						break;
					case 3:
						g_LowLevelAddIdlePet(this, PET_IO, lpChar);
						break;
					case 4:
						g_LowLevelAddIdlePet(this, PET_MUTE, lpChar);
						break;
					}
					break;
				case smTRANSCODE_EFFECT_PCBANGPET:

					if (((PacketBuffData *)lpBuff)->iTime)
						lpChar = FindChrPlayer(((PacketBuffData *)lpBuff)->iTime);
					else
						lpChar = 0;

					switch (((PacketBuffData *)lpBuff)->dwItemID)
					{
					case 1:
						g_HoPCBangAddIdlePet(this, PCBANG_PET_BURSTP, lpChar);
						break;
					case 2:
						g_HoPCBangAddIdlePet(this, PCBANG_PET_BURSTS, lpChar);
						break;
					case 3:
						g_HoPCBangAddIdlePet(this, PCBANG_PET_BURSTL, lpChar);
						break;
					case 4:
						g_HoPCBangAddIdlePet(this, PCBANG_PET_BURSTD, lpChar);
						break;
					}
					break;

				case smTRANSCODE_EFFECT_CLANMGR:
					dwClanManageBit = ((PacketBuffData *)lpBuff)->dwItemID;
					break;
				case smTRANSCODE_EFFECT_FORCEORB:
					dwForceOrbCode = ((PacketBuffData *)lpBuff)->dwItemID;
					dwForceOrbTime = ((PacketBuffData *)lpBuff)->iTime;
					dwForceOrbTime += dwPlayTime;

					AssaParticle_ShelltomWeapon(this, 70 * 5, ((dwForceOrbCode & 0xFFFF) >> 8) - 1);
					break;

				case smTRANSCODE_EFFECT_BLESS_SCORE:
					sBlessCastle_Damage[0] = ((PacketBuffData *)lpBuff)->sColors[0];
					sBlessCastle_Damage[1] = ((PacketBuffData *)lpBuff)->sColors[1];
					sBlessCastle_Param[0] = ((PacketBuffData *)lpBuff)->sColors[2];
					sBlessCastle_Param[1] = ((PacketBuffData *)lpBuff)->sColors[3];
					break;
					// ÉèÖÃVIPÐ­Òé
				case smTRANSCODE_EFFECT_VIPER:
					dwVipBit = ((PacketBuffData*)lpBuff)->dwItemID;
					break;
				}
				lpBuff += Size;
			}
		}
		if (!ChkIceFlag && AttackIce > 0)
			AttackIce = -AttackIce;
		if (!ChkPoisonFlag && DispPoison > 0)
			DispPoison = -DispPoison;
		if (!ChkFireFlag && DispFire > 0)
			DispFire = -DispFire;
	}


	dwLastTransTime = dwPlayTime;

	return TRUE;
}

//µ¥ÀÌÅ¸¸¦ ¹ÞÀ½
int Unit::RecvPlayData(SocketData * pcSocketData, Packet * psPacket)
{
	int act;
	PacketPlayDataMinor PlayData;
	smTRNAS_PLAYERINFO	*lpTransPlayerInfo;
	//int RecvCode;
	int cnt;
	int len;
	int LastBuffPosi_End;
	//smCHAR	*lpChar;

	switch (psPacket->iHeader)
	{
	case smTRANSCODE_PLAYERINFO:
		lpTransPlayerInfo = (smTRNAS_PLAYERINFO *)psPacket;
		SetTransPlayerInfo(lpTransPlayerInfo);
		return TRUE;

	case smTRANSCODE_PLAYERINFO_Q:
		SetTransPlayerInfoQuick((smTRNAS_PLAYERINFO_QUICK *)psPacket);
		break;

	case smTRANSCODE_PLAYDATA1:
		memcpy(&PlayData, psPacket, sizeof(PacketPlayDataMinor));

		pX = PlayData.iX;
		pY = PlayData.iY;
		pZ = PlayData.iZ;

		Angle.x = PlayData.saAngle[0] & ANGCLIP;
		Angle.y = PlayData.saAngle[1] & ANGCLIP;
		Angle.z = PlayData.saAngle[2] & ANGCLIP;
		act = PlayData.saAngle[3];

		if (act != action)
			iFrame = PlayData.dwFrame;

		action = act;

		iPlayBuffCount = PlayBuffPosi_End;
		MoveCnt = 0;

		dwTarget = 0;
		break;
	case smTRANSCODE_TRANSPLAYDATA:
		PacketPlayData	*lpTransPlayData;
		PlayBufferData	*lpTransPlayBuff;
		PlayBufferData	*lpTransPlayBuff2;

		lpTransPlayData = (PacketPlayData *)psPacket;
		lpTransPlayBuff = (PlayBufferData *)(psPacket + sizeof(PacketPlayData));

		LastBuffPosi_End = PlayBuffPosi_End;

		sCharacterData.sHP.sMin = lpTransPlayData->sHp[0];

		for (cnt = 0; cnt < lpTransPlayData->iPlayBuffCount - 1; cnt++)
		{
			lpTransPlayBuff2 = lpTransPlayBuff + 1;

			len = lpTransPlayBuff2->iCount - lpTransPlayBuff->iCount;
			MakePlayBuffFromRecvData(&lpTransPlayBuff->sPlayBuff, &lpTransPlayBuff2->sPlayBuff, len);

			lpTransPlayBuff++;
		}

		dwTarget = lpTransPlayData->dwTarget;
		break;
	case smTRANSCODE_ATTACKDATA:
		AttackRecvCountUp();

		Record_TotalRecvDamageCount++;

		if (((TRANS_ATTACKDATA *)psPacket)->AttackState == 0x80)
		{
			memcpy(&AttackTrans, (TRANS_ATTACKDATA *)psPacket, sizeof(TRANS_ATTACKDATA));
			XorAttackTrans();
			if (iCharacterType != CHARACTERTYPE_None || (lpCurPlayer->iLoadedMapIndex >= 0 && STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == rsCASTLE_FIELD))
				PlayAttack(TRUE);
			else
				PlayAttack();
			break;
		}

		if (AttackTrans.code^GetAttackTrans_XorCode())
			PlayAttack(TRUE);

		memcpy(&AttackTrans, (TRANS_ATTACKDATA *)psPacket, sizeof(TRANS_ATTACKDATA));
		XorAttackTrans();

		break;
	}

	dwLastTransTime = dwPlayTime;

	return TRUE;
}

void Unit::HandleUnitDataBuffer(char * pBuffer, int iDelayTime, int iSleep)
{
	auto psPacket = (PacketPlayData *)pBuffer;
	auto psPlayBuffData = (PlayBufferData *)(pBuffer + sizeof(PacketPlayData));

	psPacket->iHeader = PKTHDR_PlayDataChar;
	psPacket->dwObjectID = iID;
	psPacket->dwTarget = 0;
	psPacket->iStartPosition = iPlayBuffCount - iDelayTime;
	psPacket->sHPLong.iMin = psPacket->sHp[0] = sinGetLife();
	psPacket->sHPLong.iMax = psPacket->sHp[1] = sCharacterData.sHP.sMax;
	psPacket->sMP.sMin = sinGetMana();
	psPacket->sMP.sMax = sCharacterData.sMP.sMax;
	psPacket->sSP.sMin = sinGetStamina();
	psPacket->sSP.sMax = sCharacterData.sSP.sMax;
	psPacket->saSpeed[0] = sCharacterData.iAttackSpeed;
	psPacket->saSpeed[1] = sCharacterData.iMovementSpeed;
	psPacket->sAngleY = sAngle.iY;
	psPacket->sSize = sCharacterData.sSize;
	psPacket->dwAutoCharCode = sCharacterData.iType == CHARACTERTYPE_Monster ? sUnitInfo.dwHashCharacterName : 0;

	sCharacterData.bUpdateInfo[1] = sinSkill.SkillPoint;

	psPacket->bUpdateInfo[0] = sCharacterData.bUpdateInfo[0];
	psPacket->bUpdateInfo[1] = sCharacterData.bUpdateInfo[1];
	psPacket->bUpdateInfo[2] = 0;
	psPacket->bUpdateInfo[3] = 0;

	int iFistMapIndex = 0;
	int iSecondMapIndex = 0;

	if (iLoadedMapIndex >= 0)
	{
		iFistMapIndex = (iLoadedMapIndex + 0) & 1;
		iSecondMapIndex = (iLoadedMapIndex + 1) & 1;
	}

	psPacket->sMapID = STAGE_MAP[iFistMapIndex] ? (EMapID)STAGE_MAP[iFistMapIndex]->iMapID : MAPID_Invalid;
	psPacket->sSecondMapID = STAGE_MAP[iSecondMapIndex] ? (EMapID)STAGE_MAP[iSecondMapIndex]->iMapID : MAPID_Invalid;
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

	if (HvLeftHand.PatTool && HvLeftHand.dwItemCode && (HvLeftHand.ColorBlink || HvLeftHand.ColorEffect))
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_ITEM;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = HvLeftHand.dwItemCode;
		psPacketBuff->iTime = HvLeftHand.ColorBlink;
		memcpy(psPacketBuff->sColors, HvLeftHand.sColors, sizeof(short) * 4);
		psPacketBuff->iClass = HvLeftHand.ColorEffect;
		psPacketBuff->iScale = HvLeftHand.BlinkScale;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}

	if (HvRightHand.PatTool && HvRightHand.dwItemCode && (HvRightHand.ColorBlink || HvRightHand.ColorEffect))
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_ITEM;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = HvRightHand.dwItemCode;
		psPacketBuff->iTime = HvRightHand.ColorBlink;
		memcpy(psPacketBuff->sColors, HvRightHand.sColors, sizeof(short) * 4);
		psPacketBuff->iClass = HvRightHand.ColorEffect;
		psPacketBuff->iScale = HvRightHand.BlinkScale;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	if (HvLeftHand.PatTool && HvLeftHand.dwItemCode && HvLeftHand.ElementEffect)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_ELEMENT;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = HvLeftHand.dwItemCode;
		psPacketBuff->iTime = LEFTHAND;
		psPacketBuff->iClass = HvLeftHand.ElementEffect;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	if (HvRightHand.PatTool && HvRightHand.dwItemCode && HvRightHand.ElementEffect)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_ELEMENT;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = HvRightHand.dwItemCode;
		psPacketBuff->iTime = RIGHTHAND;
		psPacketBuff->iClass = HvRightHand.ElementEffect;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	if (dwWeaponEffectTime)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_WEAPON;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = WeaponEffect;
		psPacketBuff->iTime = (dwWeaponEffectTime - dwPlayTime) + 500;
		psPacketBuff->iClass = EnchantEffect_Point;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}

	int iHP = sinGetLife();

	if (iStunTimeLeft && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_STUN;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = iStunTimeLeft;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}

	if (PlayHolyPower[1] && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_CURSE;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = PlayHolyPower[1];

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	if (PlaySlowCount > 0 && iHP > 0)
	{
		if (sCharacterData.iType != CHARACTERTYPE_Player || AttackIce || iDistortion || PlayWeb)
		{
			ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

			psPacketBuff->iHeader = smTRANSCODE_EFFECT_ICE;
			psPacketBuff->iLength = sizeof(PacketBuffData);
			psPacketBuff->dwItemID = PlaySlowCount;
			psPacketBuff->iTime = iDistortion;
			psPacketBuff->iClass = PlayWeb;

			psPacket->bEventInfo[3]++;
			psPacket->iLength += sizeof(PacketBuffData);
			psPacketBuff++;
		}
	}

	if (PlayPoison[1] && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_POISION;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = PlayPoison[0];

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	if (PlayFire[1] && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_FIRE;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = PlayFire[0];

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}

	if (PlayCurseQuest && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_CURSE_QUEST;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = PlayCurseQuest;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}

	if (PlayVanish > 0 && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_VANISH;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = PlayVanish;
		psPacketBuff->iTime = PlayVague;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	// »áÐÄÒ»»÷
	if (dwConcentrationTime > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_CONCENTRATION;
		psPacketBuff->iTime = dwConcentrationTime - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Fighter;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	// ´ÌÉ±Ö®¸«
	if (dwSwiftAxeTime > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_SWIFT_AXE;
		psPacketBuff->iTime = dwSwiftAxeTime - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Fighter;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	// ·è¿ñÅ­ºð
	if (dwBetserkerTime > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_BERSERKER;
		psPacketBuff->iTime = dwBetserkerTime - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Fighter;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	//ÖÚÉñÖ®Å­
	if (dwB_Berserker_Time > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_B_BERSERKER;
		psPacketBuff->iTime = dwB_Berserker_Time - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Fighter;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	// Áé¹â»¤Ìå
	if (dwP_Absorb_UseTime > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_PHYSICAL_ABSORB;
		psPacketBuff->iTime = dwP_Absorb_UseTime - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Mechanician;
		psPacketBuff->iScale = cSkill.SearchContiueSkill(SKILL_PHYSICAL_ABSORB);

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	// ¸ÄÁ¼×¨¼Ò
	// Áé¹â·ÉÑï
	if (dwAutomation_Time > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_AUTOMATION;
		psPacketBuff->iTime = dwAutomation_Time - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Mechanician;
		psPacketBuff->iScale = 5;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	// ½ðÊôÖØ¼×
	if (dwMetal_Armor_Time > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_METAL_ARMOR;
		psPacketBuff->iTime = dwMetal_Armor_Time - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Mechanician;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	// ·ÀÓùµç²¨
	if (dwSpark_Shield_Time > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_SPARK_SHIELD;
		psPacketBuff->iTime = dwSpark_Shield_Time - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Mechanician;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	// ´ÅÐÔÇòÌå
	if (dwMagnetic_Sphere_Time > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_MAGNETIC_SPHERE;
		psPacketBuff->iTime = dwMagnetic_Sphere_Time - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Mechanician;
		psPacketBuff->iScale = cSkill.SearchContiueSkill(SKILL_MAGNETIC_SPHERE);

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	// ¿ìËÙ´ò»÷
	if (dwH_Sonic_Time > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_H_SONIC;
		psPacketBuff->iTime = dwH_Sonic_Time - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Mechanician;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	// Õ½Éñ×£¸£
	if (dwP_Enhence_Time > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_P_ENHENCE;
		psPacketBuff->iTime = dwP_Enhence_Time - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Mechanician;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	// Áé»êÖ®Ó¥
	if (dwFalcon_Time > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_FALCON;
		psPacketBuff->iTime = dwFalcon_Time - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Archer;
		psPacketBuff->iScale = 5;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	// »Æ½ðÁÔÓ¥
	if (dwGolden_Falcon_Time > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_GOLDEN_FALCON;
		psPacketBuff->iTime = dwGolden_Falcon_Time - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Archer;
		psPacketBuff->iScale = 5;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	// ×ÔÈ»Ö®¹â
	if (dwForceOfNatureTime > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_FORCE_OF_NATURE;
		psPacketBuff->iTime = dwForceOfNatureTime - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Archer;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	// Ç±ÄÜ¼¤·¢
	if (dwAmplified_Time > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_AMPLIFIED;
		psPacketBuff->iTime = dwAmplified_Time - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Pikeman;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	// ×·Ãü¾¢·ç
	if (dwWindy_Time > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_WINDY;
		psPacketBuff->iTime = dwWindy_Time - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Atalanta;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	// Õ½ÀõÅØÏø
	if (dwT_Of_Valhalla_Time > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_TRIUMPH_OF_VALHALLA;
		psPacketBuff->iTime = dwT_Of_Valhalla_Time - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Atalanta;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	// Íß¶û¹þÀ­Ö®¹â
	if (dwHallOfValhallaTime > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_HALL_OF_VALHALLA;
		psPacketBuff->iTime = dwHallOfValhallaTime - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Atalanta;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	// ±ùËª±êÇ¹
	if (dwFrost_Javelin_Time > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_FROST_JAVELIN;
		psPacketBuff->iTime = dwFrost_Javelin_Time - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Atalanta;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	// ÇáÎè·ÉÑï
	if (dwTalaria_Time > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_TALARIA;
		psPacketBuff->iTime = dwTalaria_Time - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Atalanta;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	// Ê¥¹â»¤Ìå
	if (dwHolyBody_Time > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_HOLY_BODY;
		psPacketBuff->iTime = dwHolyBody_Time - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Knight;
		psPacketBuff->iScale = 5;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	// ÉñÁ¦ÖØ»÷
	if (dwHoly_Valor_Time > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_HOLY_VALOR;
		psPacketBuff->iTime = dwHoly_Valor_Time - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Knight;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	// ÌìÓÓÉñîø
	if (dwDrastic_Spirit_Time > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_DRASTIC_SPIRIT;
		psPacketBuff->iTime = dwDrastic_Spirit_Time - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Knight;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	// Ê¥ÁéÖ®Îü
	if (dwD_Inhalation_Time > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_DIVINE_INHALATION;
		psPacketBuff->iTime = dwD_Inhalation_Time - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Knight;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	// ¾´ÉñÖ®¶Ü
	if (dwGodly_Shield_Time > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_GODLY_SHIELD;
		psPacketBuff->iTime = dwGodly_Shield_Time - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Knight;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	// ÉÏµÛ×£¸£
	if (dwGod_Bless_Time > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_GODS_BLESS;
		psPacketBuff->iTime = dwGod_Bless_Time - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Knight;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	// ÍöÁéÖ®Öä
	if (dwH_Benedic_Time > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_H_BENEDIC;
		psPacketBuff->iTime = dwH_Benedic_Time - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Knight;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	// ¼¯ºÏÖ®Êõ
	if (dwZenith_Time > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_ZENITH;
		psPacketBuff->iTime = dwZenith_Time - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Magician;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	// Ä§·¨ÊØ»¤
	if (dwEnergy_Shield_Time > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_ENERGY_SHIELD;
		psPacketBuff->iTime = dwEnergy_Shield_Time - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Magician;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	// Áé»êÕÙ»½
	if (dwSpirit_Elemental_Time > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_SPIRIT_ELEMENTAL;
		psPacketBuff->iTime = dwSpirit_Elemental_Time - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Magician;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	// ÔªËØÖ®½£
	if (dwDancing_Sword_Time > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_DANCING_SWORD;
		psPacketBuff->iTime = dwDancing_Sword_Time - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Magician;
		psPacketBuff->iScale = dwDancing_Sword_Param;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	// Ê¥¹â·¨Õó
	if (dwT_Anima_Time > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_T_ANIMA;
		psPacketBuff->iTime = dwT_Anima_Time - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Magician;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	// ÉñÊ¥·´Éä
	if (dwHoly_Reflection_Time > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_HOLY_REFLECTION;
		psPacketBuff->iTime = dwHoly_Reflection_Time - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Priestess;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	// ÉñÊ¥Ö®¹â
	if (dwVirtual_Life_Time > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_VIRTUAL_LIFE;
		psPacketBuff->iTime = dwVirtual_Life_Time - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Priestess;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	// ÉñÊ¥ÌìÊ¹
	if (dwSummon_Muspell_Time > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_SUMMON_MUSPELL;
		psPacketBuff->iTime = dwSummon_Muspell_Time - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Priestess;
		psPacketBuff->iScale = cSkill.SearchContiueSkill(SKILL_SUMMON_MUSPELL);

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	// ÌìÅ®É¢»¨
	if (dwB_Krishna_Time > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_B_KRISHNA;
		psPacketBuff->iTime = dwB_Krishna_Time - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Priestess;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	//Ãô½ÝÖ®Á¦
	if (dwAlasTime > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_ALAS;
		psPacketBuff->iTime = dwAlasTime - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Assassin;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	//Ãô½ÝÖ®Á¦
	if (dwInpesTime > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_INPES;
		psPacketBuff->iTime = dwInpesTime - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Assassin;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	//Âõ¿Ë¶û
	if (dwAdvent_Migal_Time > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_ADVENT_MIGAL;
		psPacketBuff->iTime = dwAdvent_Migal_Time - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Shaman;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	//ÆíÓêÊ¦
	if (dwRainmaker_Time > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_RAINMAKER;
		psPacketBuff->iTime = dwRainmaker_Time - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Shaman;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	//Ã×µÂÀ¼´ï
	if (dwAdvent_Midranda_Time > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_ADVENT_MIDRANDA;
		psPacketBuff->iTime = dwAdvent_Midranda_Time - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Shaman;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	//ÖäÊõÐÅÑö
	if (dwCreed_Time > dwPlayTime && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_CREED;
		psPacketBuff->iTime = dwCreed_Time - dwPlayTime;
		psPacketBuff->iClass = CHARACTERCLASS_Shaman;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	if (PlayInvincible > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_KEEPSKILL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = SKILL_PLAY_BLESS_SIEGE_ITEM;
		psPacketBuff->iTime = PlayInvincible;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	if (dwWingEffectCode != 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_WING;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = dwWingEffectCode;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	if (sCharacterData.iLevel == UNIT_LEVEL_MAX && iHP > 0)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_LEVEL;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = dwWingEffectCode;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	if (dwTradeMsgCode)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_PERSHOP;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = dwTradeMsgCode;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}

	if (dwForceOrbTime && dwForceOrbTime > dwPlayTime)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_FORCEORB;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = dwForceOrbCode;
		psPacketBuff->iTime = dwPlayTime - dwForceOrbTime;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}

	if (cHelpPet.PetShow)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_LOWPET;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = cHelpPet.PetKind;
		psPacketBuff->iTime = g_LowLevelPetAttackSerial;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;

		if (g_LowLevelPetAttackSerial) g_LowLevelPetAttackSerial = 0;
	}
	if (cPCBANGPet.PetShow)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_PCBANGPET;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = cPCBANGPet.PetKind;
		psPacketBuff->iTime = g_HoPCBangPetAttackSerial;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;

		if (g_HoPCBangPetAttackSerial) g_HoPCBangPetAttackSerial = 0;
	}
	// SOD»Ê¹Ú
	if (dwClanManageBit)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_CLANMGR;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = dwClanManageBit;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}
	//VIP»Ê¹Ú
	if (dwVipBit)
	{
		ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

		psPacketBuff->iHeader = smTRANSCODE_EFFECT_VIPER;
		psPacketBuff->iLength = sizeof(PacketBuffData);
		psPacketBuff->dwItemID = dwVipBit;

		psPacket->bEventInfo[3]++;
		psPacket->iLength += sizeof(PacketBuffData);
		psPacketBuff++;
	}

	if (iLoadedMapIndex >= 0 && STAGE_MAP[iLoadedMapIndex]->iMapType == MAPTYPE_BlessCastle)
	{
		if (sBlessCastle_Damage[0] || sBlessCastle_Damage[1] || sBlessCastle_Param[0] || sBlessCastle_Param[1])
		{
			ZeroMemory(psPacketBuff, sizeof(PacketBuffData));

			psPacketBuff->iHeader = smTRANSCODE_EFFECT_BLESS_SCORE;
			psPacketBuff->iLength = sizeof(PacketBuffData);
			psPacketBuff->sColors[0] = sBlessCastle_Damage[0];
			psPacketBuff->sColors[1] = sBlessCastle_Damage[1];
			psPacketBuff->sColors[2] = sBlessCastle_Param[0];
			psPacketBuff->sColors[3] = sBlessCastle_Param[1];

			psPacket->bEventInfo[3]++;
			psPacket->iLength += sizeof(PacketBuffData);
			psPacketBuff++;
		}
	}

	uUnitInfoSize = psPacket->iLength;
	
}

int Unit::SetTransEffectItems(PacketBuffData *lpEffectItem)
{
	if (HvRightHand.PatTool && HvRightHand.dwItemCode == lpEffectItem->dwItemID)
	{
		HvRightHand.ColorBlink = lpEffectItem->iTime;
		memcpy(HvRightHand.sColors, lpEffectItem->sColors, sizeof(short) * 4);
		HvRightHand.ColorEffect = lpEffectItem->iClass;
		HvRightHand.BlinkScale = lpEffectItem->iScale;

		GetItemKindFromBliankColor(&HvRightHand);
		if (HvRightHand.ColorEffect)
			AssaParticle_ClassUpWeapon(this);
	}

	if (HvLeftHand.PatTool && HvLeftHand.dwItemCode == lpEffectItem->dwItemID)
	{
		HvLeftHand.ColorBlink = lpEffectItem->iTime;
		memcpy(HvLeftHand.sColors, lpEffectItem->sColors, sizeof(short) * 4);
		HvLeftHand.ColorEffect = lpEffectItem->iClass;
		HvLeftHand.BlinkScale = lpEffectItem->iScale;

		GetItemKindFromBliankColor(&HvLeftHand);
		if (HvLeftHand.ColorEffect)
			AssaParticle_ClassUpWeapon(this);
	}

	return TRUE;
}
int Unit::SetTransEffectElement(PacketBuffData *lpEffectItem)
{
	if (HvRightHand.PatTool && HvRightHand.dwItemCode == lpEffectItem->dwItemID && RIGHTHAND == lpEffectItem->iTime)
	{
		HvRightHand.ElementEffect = lpEffectItem->iClass;

		if (HvRightHand.ElementEffect)
			AssaParticle_ElementWeapon(this, HvRightHand.ElementEffect, RIGHTHAND);
	}
	if (HvLeftHand.PatTool && HvLeftHand.dwItemCode == lpEffectItem->dwItemID && LEFTHAND == lpEffectItem->iTime)
	{
		HvLeftHand.ElementEffect = lpEffectItem->iClass;

		if (HvLeftHand.ElementEffect)
			AssaParticle_ElementWeapon(this, HvLeftHand.ElementEffect, LEFTHAND);
	}
	return TRUE;
}
int Unit::SetTransEffectWeapon(PacketBuffData *lpEffectItem)
{
	int	time;

	if (dwWeaponEffectTime && WeaponEffect == lpEffectItem->dwItemID)
	{
		time = abs(int(dwWeaponEffectTime - dwPlayTime));
		if (abs(int(time - lpEffectItem->iTime)) > 6000)
		{
			switch (lpEffectItem->dwItemID)
			{
			case (sITEMINFO_FIRE + 1):
				AssaParticle_EnchantWeaponFireMember(this, lpEffectItem->iTime / 1000);
				break;
			case (sITEMINFO_ICE + 1):
				AssaParticle_EnchantWeaponIceMember(this, lpEffectItem->iTime / 1000);
				break;
			case (sITEMINFO_LIGHTING + 1):
				AssaParticle_EnchantWeaponLightMember(this, lpEffectItem->iTime / 1000);
				break;
			}
			dwWeaponEffectTime = dwPlayTime + lpEffectItem->iTime;
			EnchantEffect_Point = lpEffectItem->iClass;
		}
	}
	else
	{
		switch (lpEffectItem->dwItemID)
		{
		case (sITEMINFO_FIRE + 1):
			AssaParticle_EnchantWeaponFireMember(this, lpEffectItem->iTime / 1000);
			break;
		case (sITEMINFO_ICE + 1):
			AssaParticle_EnchantWeaponIceMember(this, lpEffectItem->iTime / 1000);
			break;
		case (sITEMINFO_LIGHTING + 1):
			AssaParticle_EnchantWeaponLightMember(this, lpEffectItem->iTime / 1000);
			break;
		}
		WeaponEffect = lpEffectItem->dwItemID;
		dwWeaponEffectTime = dwPlayTime + lpEffectItem->iTime;
		EnchantEffect_Point = lpEffectItem->iClass;
	}

	return TRUE;
}

int Unit::SendCharInfo()
{

	smTRNAS_PLAYERINFO	TransPlayerInfo;

	memcpy(&TransPlayerInfo.sCharacterData, &sCharacterData, sizeof(CharacterData));
	TransPlayerInfo.size = sizeof(smTRNAS_PLAYERINFO);
	TransPlayerInfo.code = smTRANSCODE_PLAYERINFO;
	TransPlayerInfo.dwObjectSerial = iID;

	TransPlayerInfo.x = pX;
	TransPlayerInfo.y = pY;
	TransPlayerInfo.z = pZ;

	SENDPACKETG(&TransPlayerInfo);

	return 1;
}

//¿ªÊ¼¼¼ÄÜ
int Unit::BeginSkill(int SkilCode, int Level, Unit *lpTarChar, int x, int y, int z)
{
	int point;
	int param;
	POINT3D pos;
	int cnt;
	POINT3D	Pos1, Pos2;

	if (sCharacterData.iType == CHARACTERTYPE_Monster && iCharacterType != CHARACTERTYPE_Player)
		return BeginSkill_Monster();

	AttackEffect = 0;
	point = (SkilCode >> 8) & 0xF;
	param = (SkilCode >> 12) & 0xF;
	int SkillCode = SkilCode & 0xFF;

	int JobCode = sCharacterData.iClass;

	switch (JobCode)
	{
		//ÎäÊ¿
	case CHARACTERCLASS_Fighter:
		switch (SkillCode)
		{
			//¾øµØ±©×ß
		case SKILL_PLAY_RAVING:
			//¾«×¼Ö®»÷
		case SKILL_PLAY_IMPACT:
			AttackEffect = TRUE;
			break;
			//¼«µØÅ­ºð
		case SKILL_PLAY_ROAR:
			StartSkill(pX, pY, pZ, 0, 0, 0, SKILL_ROAR, point);
			if ((dwPlayTime & 1) == 0)
				SkillPlaySound(SKILL_SOUND_SKILL_ROAR1, pX, pY, pZ);
			else
				SkillPlaySound(SKILL_SOUND_SKILL_ROAR2, pX, pY, pZ);
			break;
			//Õ½ÉñÖ®Å­
		case SKILL_PLAY_RAGEOF_ZECRAM:
			StartSkill(pX, pY + 24 * fONE, pZ, 0, 0, 0, SKILL_RAGE_OF_ZECRAM_POWER1);
			SkillPlaySound(SKILL_SOUND_SKILL_RAGE_OF_ZECRAM3, pX, pY, pZ);
			break;
			//»áÐÄÒ»»÷
		case SKILL_PLAY_CONCENTRATION:
			AssaParticle_ConcentrationStart(this);
			SkillPlaySound(SKILL_SOUND_SKILL_CONCENTRATION1, pX, pY, pZ);
			break;
			//´ÌÉ±Ö®¸«
		case SKILL_PLAY_SWIFT_AXE:
			AssaParticle_SwiftAxeStart(this);
			SkillPlaySound(SKILL_SOUND_SKILL_SWIFT_AXE1, pX, pY, pZ);
			break;
			//ÆÆ»µÖ®»÷
		case SKILL_PLAY_DESTROYER:
			SkillWarriorDestroyerBlade(this, 3.0f);
			break;
			//·è¿ñÅ­ºð
		case SKILL_PLAY_BERSERKER:
			SkillPlaySound(SKILL_SOUND_SKILL_BERSERKER, pX, pY, pZ);
			break;
			//ì«·çÏ®»÷
		case SKILL_PLAY_CYCLONE_STRIKE:
			SkillWarriorCycloneStrikeBlade(this, 3);
			SkillPlaySound(SKILL_SOUND_SKILL_CYCLONE_STRIKE, pX, pY, pZ);
			break;
			//¿ñ±©Å­Õ¶
		case SKILL_PLAY_D_HIT:
			break;
			//¿ñÒ°³å»÷
		case SKILL_PLAY_P_DASH:
			SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_MAGIC_ICE2, pX, pY, pZ);
			AssaParticle_Extinction(this);
			break;
			//»ØÐýÕ¶»÷
		case SKILL_PLAY_M_BLOW:
			SkillWarriorCycloneStrikeBlade(this, 3);
			break;
			//ÖÚÉñÖ®Å­
		case SKILL_PLAY_B_BERSERKER:
			SkillPlaySound(SKILL_SOUND_SKILL_BERSERKER, pX, pY, pZ);
			break;
		}
		break;
		//»úÐµ
	case CHARACTERCLASS_Mechanician:
		switch (SkillCode)
		{
			//¼«¹âÖ®¶Ü
		case SKILL_PLAY_EXTREME_SHIELD:
			SkillPlaySound(SKILL_SOUND_EXTREME_SHIELD, pX, pY, pZ);
			break;
			//¶¾Ö®·ÀÓù
		case SKILL_PLAY_POISON_ATTRIBUTE:
			StartSkill(pX, pY, pZ, 0, Angle.y, 0, SKILL_UP1);
			SetMotionFromCode(ANIMATIONTYPE_Attack);
			break;
			//»úÐµÁñµ¯
		case SKILL_PLAY_MECHANIC_BOMB:
			HideWeapon = TRUE;
			break;
			//Áé¹â»¤Ìå
		case SKILL_PLAY_PHYSICAL_ABSORB:
			dwDispAppSkill |= SKILL_APPMASK_PHYSICAL_ABSORB;
			StartSkill(pX, pY, pZ, 0, Angle.y, 0, SKILL_PHYSICAL_ABSORB);
			SkillPlaySound(SKILL_SOUND_PHYSICAL_ABSORB1, pX, pY, pZ);
			break;
			//¸ÄÁ¼×¨¼Ò
		case SKILL_PLAY_MAXIMIZE:
			dwDispAppSkill |= SKILL_APPMASK_AUTOMATION;
			StartSkill(pX, pY, pZ, Angle.x, Angle.y, Angle.z, SKILL_MAXIMIZE);
			SkillPlaySound(SKILL_SOUND_SKILL_MAXIMIZE1, pX, pY, pZ);
			break;
			//Áé¹â·ÉÑï
		case SKILL_PLAY_AUTOMATION:
			dwDispAppSkill |= SKILL_APPMASK_AUTOMATION;
			StartSkill(pX, pY, pZ, Angle.x, Angle.y, Angle.z, SKILL_AUTOMATION);
			SkillPlaySound(SKILL_SOUND_SKILL_AUTOMATION1, pX, pY, pZ);
			break;
			//»ð»¨µç³¡
		case SKILL_PLAY_SPARK:
			HideWeapon = TRUE;
			SkillPlaySound(SKILL_SOUND_SKILL_SPARK1, pX, pY, pZ);
			break;
			//½ðÊôÖØ¼×
		case SKILL_PLAY_METAL_ARMOR:
			AssaParticle_MetalArmorStart(this);
			SkillPlaySound(SKILL_SOUND_SKILL_METAL_ARMOR, pX, pY, pZ);
			break;
			//·ÀÓùµç²¨
		case SKILL_PLAY_SPARK_SHIELD:
			AssaParticle_SparkShieldStart(this);
			SkillPlaySound(SKILL_SOUND_SKILL_SPARK1, pX, pY, pZ);
			break;
			//ÍþÉåÅ­ºð
		case SKILL_PLAY_COMPULSION:
			SkillPlaySound(SKILL_SOUND_SKILL_COMPULSION1, pX, pY, pZ);
			break;
			//À×öª³å»÷
		case SKILL_PLAY_IMPULSION:
			SkillImpulsionLight(this, 2);
			break;
			//´ÅÐÔÇòÌå
		case SKILL_PLAY_MAGNETIC_SPHERE:
			SkillMetalionSphereStart(this);
			SkillPlaySound(SKILL_SOUND_SKILL_SPARK1, pX, pY, pZ);
			break;
			//ÖÕ¼«»úÐµ
		case SKILL_PLAY_METAL_GOLEM:
			SkillPlaySound(SKILL_SOUND_SKILL_METAL_GOLEM, pX, pY, pZ);
			break;
			//Åùö¨Ðý·ç
		case SKILL_PLAY_LANDMINNING:
			ParkParticle_LandMinning_Skill(this);
			SkillPlaySound(SKILL_SOUND_SKILL_ARROW_OF_RANGE, pX, pY + 1000, pZ);
			break;
			//¿ìËÙ´ò»÷
		case SKILL_PLAY_H_SONIC:
			SkillMetalionHyperSonic(this);
			SkillPlaySound(SKILL_SOUND_SKILL_AGONY, pX, pY + 1000, pZ);
			break;
			//¾¿¼«Ö®ÈÐ
		case SKILL_PLAY_R_SMASH:
			break;
			//Õ½Éñ×£¸£
		case SKILL_PLAY_P_ENHENCE:
			AssaParticle_EnhenceStart(this);
			SkillPlaySound(SKILL_SOUND_SKILL_FIRE_ELEMENTAL, pX, pY + 1000, pZ);
			break;
		}
		break;
		//¹­ÊÖ
	case CHARACTERCLASS_Archer:
		switch (SkillCode)
		{
			//Õì²ìÖ®Ó¥
		case SKILL_PLAY_SCOUT_HAWK:
			if (HoSkillCode)
			{
				HoSkillCode = 0;
				EffectMgr.Main();
			}
			StartSkill(pX, pY, pZ, 0, Angle.y, 0, this, SKILL_SCOUT_HAWK, point);
			SkillPlaySound(SKILL_SOUND_SCOUT_HAWK1, pX, pY, pZ);
			SkillPlaySound(SKILL_SOUND_SCOUT_HAWK2, pX, pY, pZ);
			HideWeapon = TRUE;
			break;
			//¼²·çÖ®¼ý
		case SKILL_PLAY_WIND_ARROW:
			break;
			//¶áÃüÖ®¼ý
		case SKILL_PLAY_PERFECT_AIM:
			break;
			//Áé»êÖ®Ó¥
		case SKILL_PLAY_FALCON:
			if (HoSkillCode)
			{
				HoSkillCode = 0;
				EffectMgr.Main();
			}
			StartSkill(pX, pY, pZ, 0, 0, 0, this, SKILL_FALCON, Falcon_Time[point - 1]);
			HideWeapon = TRUE;
			SkillPlaySound(SKILL_SOUND_SKILL_FALCON, pX, pY, pZ);
			break;
			//»Æ½ðÁÔÓ¥
		case SKILL_PLAY_GOLDEN_FALCON:
			if (HoSkillCode)
			{
				HoSkillCode = 0;
				EffectMgr.Main();
			}
			StartSkill(pX, pY, pZ, 0, 0, 0, this, SKILL_GOLDEN_FALCON, Golden_Falcon_Time[point - 1]);
			HideWeapon = TRUE;
			SkillPlaySound(SKILL_SOUND_SKILL_GOLDEN_FALCON, pX, pY, pZ);
			break;
			//ÕÙ»½Ñ©ÀÇ
		case SKILL_PLAY_RECALL_WOLVERIN:
			break;
			//ç³»Ë¾øÑ×
		case SKILL_PLAY_PHOENIX_SHOT:
			break;
			//×ÔÈ»Ö®¹â
		case SKILL_PLAY_FORCE_OF_NATURE:
			SkillPlaySound(SKILL_SOUND_SKILL_FORCE_OF_NATURE, pX, pY, pZ);
			break;
			//»ØÐýÖ®Îè
		case SKILL_PLAY_E_SHOT:
			AssaParticle_EvadEshot(this);
			SkillPlaySound(SKILL_SOUND_PHYSICAL_ABSORB1, pX, pY, pZ);
			break;
			//Ðþ¹âÖ®Îè
		case SKILL_PLAY_S_ROPE:
			StartSkill(pX, pY, pZ, Angle.x, Angle.y, Angle.z, SKILL_S_ROPE);
			SkillPlaySound(SKILL_SOUND_SKILL_FIRE_ELEMENTAL, pX, pY, pZ);
			break;
			//º®±ùÖ®¼ý
		case SKILL_PLAY_C_TRAP:
			SkillPlaySound(SKILL_SOUND_SKILL_DRASTICSPIRIT1, pX, pY, pZ);
			break;
		}
		break;
		//Ç¹±ø
	case CHARACTERCLASS_Pikeman:
		switch (SkillCode)
		{
			//Áú¾íÇ¹·ç
		case SKILL_PLAY_PIKEWIND:
			break;
			//Åùö¨Ò»»÷
		case SKILL_PLAY_JUMPING_CRASH:
			AttackEffect = TRUE;
			SkillPlaySound(SKILL_SOUND_JUMPING_CRASH1, pX, pY, pZ);
			break;
			//´óµØÖ®Ç¹
		case SKILL_PLAY_GROUND_PIKE:
			break;
			//Ç¹Ö®ì«·ç
		case SKILL_PLAY_TORNADO:
			break;
			//ÎÞÏÞÁ¦Ç¹
		case SKILL_PLAY_EXPANSION:
			SkillPlaySound(SKILL_SOUND_SKILL_EXPANSION1, pX, pY, pZ);
			break;
			//ÁéÉß±êÇ¹
		case SKILL_PLAY_VENOM_SPEAR:
			AssaParticle_VeonmSpearPike(this);
			SkillPlaySound(SKILL_SOUND_JUMPING_CRASH1, pX, pY, pZ);
			break;
			//Á´ÆïÖ®Ç¹
		case SKILL_PLAY_CHAIN_LANCE:
			break;
			//Òþ°µÖ®Êõ
		case SKILL_PLAY_VANISH:
			AssaParticle_Vanish(this);
			SkillPlaySound(SKILL_SOUND_SKILL_VANISH1, pX, pY, pZ);
			break;
			//°µÉ±Ö®ÑÛ
		case SKILL_PLAY_ASSASSIN_EYE:
			SkillPlaySound(SKILL_SOUND_SKILL_ASSASSIN_EYE, pX, pY, pZ);
			break;
			//×ª»»´ò»÷
		case SKILL_PLAY_CHARGING_STRIKE:
			//ÓîÖæ»ÃÓ°
		case SKILL_PLAY_SHADOW_MASTER:
			if (this == lpCurPlayer) SkillEventDamageCount = 0;
			break;
			//Ó°ÒþÖ®¶Ý
		case SKILL_PLAY_VAGUE:
			SkillPlaySound(SKILL_SOUND_SKILL_VAGUE, pX, pY, pZ);
			break;
			//»ØÐý´ò»÷
		case SKILL_PLAY_D_REAPER:
			SkillWarriorCycloneStrikeBlade(this, 1.0f, 2);
			break;
			//µØÏ®ÆæÇ¹
		case SKILL_PLAY_F_SPEAR:
			if (chrAttackTarget)
				AssParticle_Spear(this);
			break;
			//Ç±ÄÜ¼¤·¢
		case SKILL_PLAY_AMPLIFIED:
			AssaCodeSkillEffect("Skill5PikemanAmplified", this, 3, SKILL_AMPLIFIED);
			break;
			//Ðý·çÖ®Ç¹
		case SKILL_PLAY_SS_ATTACK:
			SkillWarriorCycloneStrikeBlade(this, 2.0f, 3);
			break;
		}
		break;
		//Ä§Ç¹
	case CHARACTERCLASS_Atalanta:
		switch (SkillCode)
		{
			//×·Ãü¾¢·ç
		case SKILL_PLAY_WINDY:
			sinSkillEffect_Windy(this);
			SkillPlaySound(SKILL_SOUND_SKILL_WINDY1, pX, pY, pZ);
			break;
			//×··çÖ®Ç¹
		case SKILL_PLAY_SPLIT_JAVELIN:
			if (chrAttackTarget && AttackCritcal >= 0 && GetAttackPoint(&x, &y, &z) == TRUE)
			{
				Pos1.x = x;
				Pos1.y = y;
				Pos1.z = z;
				Pos2.x = chrAttackTarget->pX;
				Pos2.y = chrAttackTarget->pY + 28 * fONE;
				Pos2.z = chrAttackTarget->pZ;
				AssaParticle_SplitJavelin(&Pos1, &Pos2, param);
			}
			SkillPlaySound(SKILL_SOUND_SKILL_SPLIT_JAVELIN1, pX, pY, pZ);
			break;
			//Õ½ÀõÅØÏø
		case SKILL_PLAY_TRIUMPH_OF_VALHALLA:
			SkillPlaySound(SKILL_SOUND_SKILL_TRIUMPH_OF_VALHALLA1, pX, pY, pZ);
			break;
			//Íß¶û¹þÀ­Ö®¹â
		case SKILL_PLAY_HALL_OF_VALHALLA:
			SkillPlaySound(SKILL_SOUND_SKILL_HALL_OF_VALHALLA, pX, pY, pZ);
			break;
			//Ëª¶³±êÇ¹
		case SKILL_PLAY_FROST_JAVELIN:
			SkillPlaySound(SKILL_SOUND_SKILL_FROST_JAVELIN, pX, pY, pZ);
			sinSkillEffect_Windy(this);
			break;
			//ÇáÎè·ÉÑï
		case SKILL_PLAY_TALARIA:
			AssaParticle_Taltria(this);
			SkillPlaySound(SKILL_SOUND_SKILL_HOLYREFLECTION1, pX, pY, pZ);
			break;
			//ÐÇÓê±êÇ¹
		case SKILL_PLAY_G_COUP:
			SkillPlaySound(SKILL_SOUND_JUMPING_CRASH1, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Atalanta);
			AssaParticle_G_Coup(this);
			if (chrAttackTarget)
			{
				Pos1.x = pX;
				Pos1.y = pY;
				Pos1.z = pZ;
				Pos2.x = chrAttackTarget->pX;
				Pos2.y = chrAttackTarget->pY + 28 * fONE;
				Pos2.z = chrAttackTarget->pZ;
				AssaParticle_G_Coup_Effect(&Pos1, &Pos2, G_Coup_Hit[point - 1]);
				SkillPlaySound(SKILL_SOUND_SKILL_ARROW_OF_RANGE, pX, pY, pZ);
			}
			break;
			//±¿±¿ÐÜ
		case SKILL_PLAY_S_ARCUDA:
			HideWeapon = TRUE;
			break;
		}
		break;
		//ÓÎÏÀ
	case CHARACTERCLASS_Knight:
		switch (SkillCode)
		{
			//Ä§Éñ½£
		case SKILL_PLAY_SWORD_BLAST:
			SkillPlaySound(SKILL_SOUND_SKILL_SWORDBLAST1, pX, pY, pZ);
			break;
			//Ê¥¹â»¤Ìå
		case SKILL_PLAY_HOLY_BODY:
			dwDispAppSkill |= SKILL_APPMASK_PHYSICAL_ABSORB;
			sinEffect_Holy_Body(this);
			SkillPlaySound(SKILL_SOUND_SKILL_HOLYBODY, pX, pY, pZ);
			break;
			//¿ñÔê»ÓÎè
		case SKILL_PLAY_BRANDISH:
			SkillPlaySound(SKILL_SOUND_SKILL_BLANDISH1, pX, pY, pZ);
			break;
			//ÉñÁ¦ÖØ»÷
		case SKILL_PLAY_HOLY_VALOR:
			AssaParticle_HolyValor_Jang(this);
			SkillPlaySound(SKILL_SOUND_SKILL_HOLY_VALOR1, pX, pY, pZ);
			break;
			//Ò»ÎíÒø
		case SKILL_PLAY_PIERCING:
			sinSkillEffect_Piercing(this);
			SkillPlaySound(SKILL_SOUND_SKILL_PIERCING, pX, pY, pZ);
			break;
			//ÌìÓÓÉñîø
		case SKILL_PLAY_DRASTIC_SPIRIT:
			AssaParticle_DrasticSpirit_Jang(this);
			SkillPlaySound(SKILL_SOUND_SKILL_DRASTICSPIRIT1, pX, pY, pZ);
			break;
			//Ê¥ÁéÖ®Îü
		case SKILL_PLAY_DIVINE_INHALATION:
			AssaParticle_DivineInhalationStart(this);
			SkillPlaySound(SKILL_SOUND_SKILL_DIVINE_INHALATION, pX, pY, pZ);
			break;
			//Ê¥ØßÖ®¹â
		case SKILL_PLAY_HOLY_INCANTATION:
			AssaParticle_HolyIncantationHand(this);
			break;
			//ÕæÄ§Éñ½£
		case SKILL_PLAY_SWORD_OF_JUSTICE:
			SkillPlaySound(SKILL_SOUND_SKILL_SWORD_OF_JUSTICE, pX, pY, pZ);
			break;
			//¾´ÉñÖ®¶Ü
		case SKILL_PLAY_GODLY_SHIELD:
			SkillSaintGodlyShieldStart(this);
			SkillPlaySound(SKILL_SOUND_SKILL_GODLY_SHIELD, pX, pY, pZ);
			break;
			//ÉÏµÛ×£¸£
		case SKILL_PLAY_GODS_BLESS:
			SkillGodBless(this);
			SkillPlaySound(SKILL_SOUND_SKILL_GODS_BLESS, pX, pY, pZ);
			break;
			//ÉñÁ¦³å´Ì
		case SKILL_PLAY_S_BREAKER:
			if (chrAttackTarget)
			{
				sinSkillEffect_Breaker(this, chrAttackTarget);
				SkillPlaySound(SKILL_SOUND_EXTREME_SHIELD, pX, pY, pZ);
			}
			break;
			//ÉýÁúÖØ»÷
		case SKILL_PLAY_C_MOON:
			AssaParticle_Moon(this);
			break;
			//ÉÏµÛÖØ»÷
		case SKILL_PLAY_S_BLADE:
			sinSkillEffect_Blade(this);
			SkillPlaySound(SKILL_SOUND_SKILL_VANISH2, pX, pY, pZ);
			break;
			//ÍöÁéÖ®Öä
		case SKILL_PLAY_H_BENEDIC:
			AssaParticle_Benedic(this);
			break;
		}
		break;
		//·¨Ê¦
	case CHARACTERCLASS_Magician:
		switch (SkillCode)
		{
			//Ä§Á¦×ª»¯
		case SKILL_PLAY_AGONY:
			sinEffect_Agony(this);
			SkillPlaySound(SKILL_SOUND_SKILL_CASTING_MAGICIAN, pX, pY, pZ);
			SkillPlaySound(SKILL_SOUND_SKILL_AGONY, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Magician);
			break;
			//¼¯ºÏÖ®Êõ
		case SKILL_PLAY_ZENITH:
			sinEffect_Zenith(this, Zenith_Time[point - 1], 1);
			SkillPlaySound(SKILL_SOUND_SKILL_CASTING_MAGICIAN, pX, pY, pZ);
			SkillPlaySound(SKILL_SOUND_SKILL_ZENITH, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Magician);
			break;
			//»ðÇòÖ®Êõ
		case SKILL_PLAY_FIRE_BALL:
			//»ð¼ýÖ®Êõ
		case SKILL_PLAY_FIRE_BOLT:
			SkillPlaySound(SKILL_SOUND_SKILL_CASTING_MAGICIAN, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Magician);
			break;
			//Áú¾íº£·ç
		case SKILL_PLAY_COLUMN_OF_WATER:
			SkillPlaySound(SKILL_SOUND_SKILL_CASTING_MAGICIAN, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Magician);
			break;
			//ÔªËØÖ®Êõ
		case SKILL_PLAY_ENCHANT_WEAPON:
			SkillPlaySound(SKILL_SOUND_SKILL_CASTING_MAGICIAN, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Magician);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			if (this == lpCurPlayer)
			{
				if (!chrAttackTarget)
				{
					cnt = Enchant_Weapon_Time[point - 1];
					EnchantEffect_Point = point;
					switch (param)
					{
					case 0:
						AssaParticle_EnchantWeaponIceJang(this, cnt);
						WeaponEffect = sITEMINFO_ICE + 1;
						dwWeaponEffectTime = dwPlayTime + cnt * 1000;
						break;
					case 1:
						AssaParticle_EnchantWeaponLightJang(this, cnt);
						WeaponEffect = sITEMINFO_LIGHTING + 1;
						dwWeaponEffectTime = dwPlayTime + cnt * 1000;
						break;
					case 2:
						AssaParticle_EnchantWeaponFireJang(this, cnt);
						WeaponEffect = sITEMINFO_FIRE + 1;
						dwWeaponEffectTime = dwPlayTime + cnt * 1000;
						break;
					}
				}
			}
			SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_CAST, pX, pY, pZ);
			break;
			//Ú¤ÍöÖ®¹â
		case SKILL_PLAY_DEAD_RAY:
			SkillPlaySound(SKILL_SOUND_SKILL_CASTING_MAGICIAN, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Magician);
			break;
			//Ä§·¨ÊØ»¤
		case SKILL_PLAY_ENERGY_SHIELD:
			//µØÁÑ³å»÷
		case SKILL_PLAY_DIASTROPHISM:
			//Áé»êÕÙ»½
		case SKILL_PLAY_SPIRIT_ELEMENTAL:
			//ÔªËØÖ®½£
		case SKILL_PLAY_DANCING_SWORD:
			SkillPlaySound(SKILL_SOUND_SKILL_CASTING_MAGICIAN, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Magician);
			break;
			//ÒÁ·òÁÐÌØ
		case SKILL_PLAY_FIRE_ELEMENTAL:
			SkillPlaySound(SKILL_SOUND_SKILL_FIRE_ELEMENTAL, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Magician);
			break;
			//»ðÑæ²¨¶¯
		case SKILL_PLAY_FLAME_WAVE:
			SkillPlaySound(SKILL_SOUND_SKILL_FLAME_WAVE3, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Magician);
			break;
			//¿Õ¼äÅ¤Çú
		case SKILL_PLAY_DISTORTION:
			SkillPlaySound(SKILL_SOUND_SKILL_DISTORTION, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Magician);
			break;
			//ÔÉÊ¯ÕÙ»½
		case SKILL_PLAY_METEO:
			SkillPlaySound(SKILL_SOUND_SKILL_CASTING_MAGICIAN, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Magician);
			break;
			//Á÷ÐÇ»ðÓê
		case SKILL_PLAY_SILRAPHIM:
			SkillPlaySound(SKILL_SOUND_SKILL_METAL_GOLEM, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic2(&pos, 2);
			sinEffect_Silraphim(this);
			break;
			//ËõÐ¡Ö®Êõ
		case SKILL_PLAY_V_TENUS:
			SkillPlaySound(SKILL_SOUND_SKILL_VAGUE, pX, pY, pZ);
			sinEffect_Tenus(this);
			break;
			//ÉñÊ¥Ï´Àñ
		case SKILL_PLAY_P_IGNIS:
			SkillPlaySound(SKILL_SOUND_SKILL_FLAME_WAVE3, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Magician);
			AssaParticle_Ignis(this, SMMAT_BLEND_LAMP, P_Ignis_Hit[point - 1]);
			break;
			//Ê¥¹â·¨Õó
		case SKILL_PLAY_T_ANIMA:
			SkillPlaySound(SKILL_SOUND_SKILL_CASTING_MAGICIAN, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Magician);
			sinSkillEffect_Anima(this);
			break;
		}
		break;
		//¼ÀË¾
	case CHARACTERCLASS_Priestess:
		switch (SkillCode)
		{
			//ÖÎÓúÖ®Êõ
		case SKILL_PLAY_HEALING:
			if (!lpTarChar && this == lpCurPlayer)
			{
				sinEffect_Healing2(this);
				SkillPlaySound(SKILL_SOUND_SKILL_HEALING, pX, pY, pZ);
			}
			else
			{
				if (lpTarChar)
				{
					sinEffect_Healing2(lpTarChar);
					SkillPlaySound(SKILL_SOUND_SKILL_HEALING, lpTarChar->pX, lpTarChar->pY, lpTarChar->pZ);
				}
			}
			SkillPlaySound(SKILL_SOUND_SKILL_CASTING_PRIEST, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Priestess);
			break;
			//Ê¥¹âµçÇò
		case SKILL_PLAY_HOLY_BOLT:
			//¹âÃ¢ËÄÉä
		case SKILL_PLAY_MULTI_SPARK:
			SkillPlaySound(SKILL_SOUND_SKILL_CASTING_PRIEST, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Priestess);
			break;
			//ÒâÄîÖ®Êõ
		case SKILL_PLAY_HOLY_MIND:
			if (lpTarChar)
			{
				cnt = lpTarChar->sCharacterData.sElementalDef[sITEMINFO_BIONIC];
				if (cnt < 0) cnt = 0;
				if (cnt > 100) cnt = 100;
				cnt = (15 * (100 - cnt)) / 100;
				if (cnt > 0)
					AssaParticle_HolyMind_Attack(lpTarChar, cnt);
			}
			SkillPlaySound(SKILL_SOUND_SKILL_HOLYMIND, pX, pY, pZ);
			SkillPlaySound(SKILL_SOUND_SKILL_CASTING_PRIEST, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Priestess);
			break;
			//ÉñÖ®À×µç
		case SKILL_PLAY_DIVINE_LIGHTNING:
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Priestess);
			SkillPlaySound(SKILL_SOUND_SKILL_CASTING_PRIEST, pX, pY, pZ);
			break;
			//ÉñÊ¥·´Éä
		case SKILL_PLAY_HOLY_REFLECTION:
			sinSkillEffect_Holy_Reflection(this, Holy_Reflection_Time[point - 1]);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Priestess);
			SkillPlaySound(SKILL_SOUND_SKILL_CASTING_PRIEST, pX, pY, pZ);
			SkillPlaySound(SKILL_SOUND_SKILL_HOLYREFLECTION1, pX, pY, pZ);
			break;
			//Ê¥½àÖ®¹â
		case SKILL_PLAY_GREAT_HEALING:
			sinSkillEffect_Great_Healing(this);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Priestess);
			SkillPlaySound(SKILL_SOUND_SKILL_CASTING_PRIEST, pX, pY, pZ);
			SkillPlaySound(SKILL_SOUND_SKILL_GRANDHEALING, pX, pY, pZ);
			break;
			//»ðÓ°Ë«ÖØ
		case SKILL_PLAY_VIGOR_BALL:
			//»ØÉúÖ®Êõ
		case SKILL_PLAY_RESURRECTION:
			//Ê¥¹âÖ®Öä
		case SKILL_PLAY_EXTINCTION:
			//ÉñÊ¥Ö®¹â
		case SKILL_PLAY_VIRTUAL_LIFE:
			SkillPlaySound(SKILL_SOUND_SKILL_CASTING_PRIEST, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Priestess);
			break;
			//±ùËªÊÉÔÂ
		case SKILL_PLAY_GLACIAL_SPIKE:
			SkillPlaySound(SKILL_SOUND_SKILL_CASTING_PRIEST, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Priestess);
			break;
			//ÔÙÉúÁìÓò
		case SKILL_PLAY_REGENERATION_FIELD:
			SkillPlaySound(SKILL_SOUND_SKILL_REGEN_FIELD2, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Priestess);
			break;
			//ÌìÀ×Ö®Å­
		case SKILL_PLAY_CHAIN_LIGHTNING:
			SkillPlaySound(SKILL_SOUND_SKILL_CASTING_PRIEST, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Priestess);
			break;
			//ÉñÊ¥ÌìÊ¹
		case SKILL_PLAY_SUMMON_MUSPELL:
			SkillPlaySound(SKILL_SOUND_SKILL_MUSPELL1, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Priestess);
			break;
			//ÉñÊ¥µç²¨
		case SKILL_PLAY_S_IMPACT:
			break;
			//ÉñÊ¥±ùÈÐ
		case SKILL_PLAY_P_ICE:
			SkillPlaySound(SKILL_SOUND_SKILL_GRAND_CROSS, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Priestess);
			break;
			//±©·çÑ©
		case SKILL_PLAY_S_PRMIEL:
			SkillPlaySound(SKILL_SOUND_SKILL_CASTING_PRIEST, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Priestess);
			break;
			//ÌìÅ®É¢»¨
		case SKILL_PLAY_B_KRISHNA:
			SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_CAST, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic2(&pos, 1);
			sinEffect_Holy_Body_Cross(this);
			break;
		}
		break;
		// ´Ì¿Í
	case CHARACTERCLASS_Assassin:
		switch (SkillCode)
		{
			//´Ì»÷
		case SKILL_PLAY_STRINGER:
			SkillPlaySound(SKILL_SOUND_SKILL_STRINGER, pX, pY, pZ);
			break;
			//ÉÁ»÷
		case SKILL_PLAY_RUNNING_HIT:
			SkillPlaySound(SKILL_SOUND_SKILL_RUNNING_HIT, pX, pY, pZ);
			break;
			//Èõµã¹¥»÷
		case SKILL_PLAY_WISP:
			SkillPlaySound(SKILL_SOUND_SKILL_WISP, pX, pY, pZ);
			AssaParticle_Effect("Wisp1", this, 0);
			break;
			//¶¾ÑÀÁ¬»÷
		case SKILL_PLAY_VENOM_THORN:
			SkillPlaySound(SKILL_SOUND_SKILL_VENOM_THORN, pX, pY, pZ);
			break;
			//Ãô½ÝÖ®Á¦
		case SKILL_PLAY_ALAS:
			SkillPlaySound(SKILL_SOUND_SKILL_ALAS, pX, pY, pZ);
			break;
			//Áé»êÕðº³
		case SKILL_PLAY_SOUL_SHOCK:
			SkillPlaySound(SKILL_SOUND_SKILL_SOUL_SHOCK, pX, pY, pZ);
			break;
			//·É½£Ö®Îè
		case SKILL_PLAY_SORE_SWORD:
			SkillPlaySound(SKILL_SOUND_SKILL_SORE_SWORD, pX, pY, pZ);
			break;
			//ÌøÕ¶
		case SKILL_PLAY_BEAT_UP:
			SkillPlaySound(SKILL_SOUND_SKILL_BEAT_UP, pX, pY, pZ);
			break;
			//Ãô½Ý´óÊ¦
		case SKILL_PLAY_INPES:
			SkillPlaySound(SKILL_SOUND_SKILL_INPES, pX, pY, pZ);
			break;
			//ÖÂÃ¤
		case SKILL_PLAY_BLIND:
			SkillPlaySound(SKILL_SOUND_SKILL_BLIND, pX, pY, pZ);
			AssaParticle_Effect("Blind", this, 0);
			break;
			//±ù¶³Ö®ÈÐ
		case SKILL_PLAY_FROST_WIND:
			SkillPlaySound(SKILL_SOUND_SKILL_FROST_WIND, pX, pY, pZ);
			AssaParticle_Effect("FrostWindBegin", this, 0);
			break;
			//ÎÁÒßÖ®ÈÐ
		case SKILL_PLAY_POLLUTE:
			SkillPlaySound(SKILL_SOUND_SKILL_POLLUTED, pX, pY, pZ);
			AssaParticle_Effect("PollutedBegin", this, 0);
			break;
			//Ó°×ÓÉÁ»÷
		case SKILL_PLAY_PASTING_SHADOW:
			SkillPlaySound(SKILL_SOUND_SKILL_PASTING_SHADOW, pX, pY, pZ);
			AssaParticle_Effect("PastingShadowBegin", this, 0);
			break;
			//Ó°×Ó»ðÑæ
		case SKILL_PLAY_SHADOW_BOMB:
			SkillPlaySound(SKILL_SOUND_SKILL_SHADOW_BOMB, pX, pY, pZ);
			break;
			//µØÁÑÕ¶
		case SKILL_PLAY_RISING_SLASH:
			SkillPlaySound(SKILL_SOUND_SKILL_RISING_SHASH, pX, pY, pZ);
			AssaParticle_Effect("RisingSlash1", this, 0);
			break;
			//ÃÍÁú°ÚÎ²
		case SKILL_PLAY_VIOLENT_STUB:
			SkillPlaySound(SKILL_SOUND_SKILL_VIOLENCE_STAB, pX, pY, pZ);
			AssaParticle_Effect("ViolenceStab1", this, 0);
			break;
			//·ç±©Ö®ÈÐ
		case  SKILL_PLAY_SHADOW_STORM:
			SkillPlaySound(SKILL_SOUND_SKILL_STORM, pX, pY, pZ);
			break;
		}
		break;
		//ÈøÂú
	case CHARACTERCLASS_Shaman:
		switch (SkillCode)
		{
			//°µºÚÉÁµç
		case SKILL_PLAY_DARK_BOLT:
			SkillPlaySound(SKILL_SOUND_SKILL_DARK_BOLT, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Shaman);
			break;
			//°µºÚ²¨ÀË
		case SKILL_PLAY_DARK_WAVE:
			SkillPlaySound(SKILL_SOUND_SKILL_DARK_WAVE, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Shaman);
			break;
			//×çÖäÀ×»÷
		case SKILL_PLAY_INERTIA:
			SkillPlaySound(SKILL_SOUND_SKILL_CURSE_LAZY1, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Shaman);
			AssaParticle_Effect("CurseLazy1", this, 0);
			break;
			//¾«ÉñÖäÊõ
		case SKILL_PLAY_SPIRITUAL_FLARE:
			SkillPlaySound(SKILL_SOUND_SKILL_SPIRITUAL_FLARE1, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Shaman);
			break;
			//Áé»ê¼ÏËø
		case SKILL_PLAY_SPIRITUAL_MANACLE:
			SkillPlaySound(SKILL_SOUND_SKILL_SPIRITUAL_MANACLE1, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Shaman);
			break;
			//ÁÔÈ¡
		case SKILL_PLAY_CHASING_HUNT:
			SkillPlaySound(SKILL_SOUND_SKILL_CHASING_HUNT1, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Shaman);
			break;
			//Âõ¿Ë¶û
		case SKILL_PLAY_ADVENT_MIGAL:
			SkillPlaySound(SKILL_SOUND_SKILL_SKILL_ADVENT_MIGAL1, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Shaman);
			break;
			//ÆíÓêÊ¦
		case SKILL_PLAY_RAINMAKER:
			SkillPlaySound(SKILL_SOUND_SKILL_SKILL_RAIN_MAKER1, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Shaman);
			AssaParticle_Effect("RainMaker1", this, 0);
			break;
			//Â½µØÁé»ê
		case SKILL_PLAY_LAND_OF_GHOST:
			SkillPlaySound(SKILL_SOUND_SKILL_LAND_OF_GHOST1, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Shaman);
			AssaParticle_Effect("LandOfGhost1", this, 0);
			break;
			//¹í»ìÖØ»Ø
		case SKILL_PLAY_HAUNT:
			SkillPlaySound(SKILL_SOUND_SKILL_HAUNT1, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Shaman);
			break;
			//×¥ÆÆ
		case SKILL_PLAY_SCRATCH:
			SkillPlaySound(SKILL_SOUND_SKILL_SCRATCH1, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Shaman);
			AssaParticle_Effect("ScratchAura", this, 0);
			break;
			//ÊÈÑªÖ®Ò¹
		case SKILL_PLAY_CRIMSON_KNIGHT:
			SkillPlaySound(SKILL_SOUND_SKILL_RECALL_BLOODYKNIGHT1, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Shaman);
			AssaParticle_Effect("RecallBloodyKnight", this, 0);
			break;
			//ÉóÅÐ
		case SKILL_PLAY_JUDGEMENT:
			SkillPlaySound(SKILL_SOUND_SKILL_JUDGEMENT1, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Shaman);
			break;
			//Ã×µÂÀ¼´ï
		case SKILL_PLAY_ADVENT_MIDRANDA:
			SkillPlaySound(SKILL_SOUND_SKILL_ADVENT_MIDRANDA1, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Shaman);
			break;
			//ÐñÈÕ¶«Éý
		case SKILL_PLAY_MOURNING_PRAY:
			SkillPlaySound(SKILL_SOUND_SKILL_MOURNING_OF_PRAY1, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Shaman);
			AssaParticle_Effect("MourningOfPreyStart", this, 0);
			break;
			//ÖäÊõÐÅÑö
		case SKILL_PLAY_CREED:
			SkillPlaySound(SKILL_SOUND_SKILL_CREED, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Shaman);
			AssaParticle_Effect("CreedStart", this, 0);
			break;
			//×çÖäÖ®Á¦
		case SKILL_PLAY_PRESS_DEITY:
			SkillPlaySound(SKILL_SOUND_SKILL_PRESS_OF_DEITY, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Shaman);
			break;
			//ËÀÍöÖ®×¦
		case SKILL_PLAY_PHANTOM_NAIL:
			SkillPlaySound(SKILL_SOUND_SKILL_CHOSTY_NAIL1, pX, pY, pZ);
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;
			sinEffect_StartMagic(&pos, CHARACTERCLASS_Shaman);
			AssaParticle_Effect("GhostyNail1", this, 0);
			break;
		}
		break;
	}
	return TRUE;
}

//¸ó½ºÅÍ ÀÏ¹Ý °ø°Ý ½ÃÀÛ
int Unit::BeginAttack_Monster()
{
	switch (sCharacterData.iMonsterEffectID)
	{
	case snCHAR_SOUND_DARKKNIGHT:
		if (sCharacterData.iLevel >= 65)
			AssaParticle_DoomGuardHit1(this);
		break;
	case snCHAR_SOUND_GUARDIAN_SAINT:
		break;
	case snCHAR_SOUND_DEATHKNIGHT:
		if (psModelAnimation->KeyCode != 'L')
			ParkValentSwordShow(this, 70);
		break;

	case snCHAR_SOUND_DEVIL_BIRD:
		if (psModelAnimation->KeyCode != 'B')
			ParkDevilBirdAttackBlur(this);
		break;
	case snCHAR_SOUND_KELVEZU:
		if (psModelAnimation->KeyCode == 'P')
			ParkKelvezuWingShow(this, 70);
		else
			ParkKelvezuFingerShow(this, 70);
		break;
	case snCHAR_SOUND_CHIMERA:
		ParkAssaParticle_ChimeraNormal(this);
		break;
	case snCHAR_SOUND_REVIVED_ARCHER:
		break;
		//°£¿ËË¹
	case MONSTEREFFECTID_Draxos:
		if (psModelAnimation->KeyCode != 'H')
			ParkParticle_DraxosSkill(this, 70);
		break;
	}

	return TRUE;
}

//¸ó½ºÅÍ ½ºÅ³ ½ÃÀÛ
int Unit::BeginSkill_Monster()
{
	POINT3D	pos;

	switch (sCharacterData.iMonsterEffectID)
	{
	case snCHAR_SOUND_NAZ:
	{
		auto sPosition = GetMoveLocation(0, 0, 100 * fONE, 0, Angle.y, 0);
		StartSkillDest(pX, pY, pZ, pX + sPosition.iX, pY, pZ + sPosition.iZ, SKILL_TORNADO2, 1);
	}
		break;

	case snCHAR_SOUND_FURY:
		StartEffectMonster(pX, pY, pZ, 0, Angle.y, 0, MONSTER_FURY_MAGIC1);
		break;

	case snCHAR_SOUND_DARKKNIGHT:
		if (sCharacterData.iLevel >= 65)
			AssaParticle_DoomGuardHit2(this);
		break;

	case snCHAR_SOUND_HEAVYGOBLIN:
		AssaParticle_HeavyGoblinHit1(this);
		break;

	case snCHAR_SOUND_ICEGOBLIN:
		ParkAssaParticle_IceGoblinHit1(this);
		break;

	case snCHAR_SOUND_COLDEYE:
		ParkParticle_ColdEyeSkill(this);
		break;
	case snCHAR_SOUND_CHAOSCARA:
		if (psModelAnimation->KeyCode == 'J')
		{
			if (chrAttackTarget)
				ParkAssaParticle_ChaosKara2(chrAttackTarget);
			LastSkillParam = 0;
		}
		else
		{
			ParkAssaParticle_ChaosKaraSkill_Monster(this);
			SkillPlay_Monster_Effect(this, SKILL_PLAY_CHAOSCARA_VAMP, 220);
			LastSkillParam = 1;
		}
		break;
	case snCHAR_SOUND_DEATHKNIGHT:
		ParkValentSwordShow(this, 70);
		break;
	case snCHAR_SOUND_DEVIL_BIRD:
		DevilBird_Skill(this);
		break;
	case snCHAR_SOUND_KELVEZU:
		if (psModelAnimation->KeyCode == 'I')
			ParkKelvezuWingShow(this, 200);
		else
		{
			ParkKelvezuTaleShow(this, 90);
			ParkKelvezuSkill2(this);
		}
		break;
	case snCHAR_SOUND_NPC_SKILLMASTER:
		switch (psModelAnimation->KeyCode)
		{
		case 'A':
			break;
		case 'B':
		case 'N':
		case 'Y':
			AssaMotionBlur(this, "Bip01 R Hand", "bip01 weapon", 80);
			break;
		case 'M':
			break;

		case 'L':
			SkillLancelotChargingStrike(this);
			break;
		}
		break;
	case snCHAR_SOUND_NPC_MAGICMASTER:
		SkillPlaySound(SKILL_SOUND_SKILL_CASTING_MAGICIAN, pX, pY, pZ);
		pos.x = pX;
		pos.y = pY;
		pos.z = pZ;
		sinEffect_StartMagic(&pos, CHARACTERCLASS_Magician);
		break;
	case snCHAR_SOUND_DEVILSHY:
		switch (psModelAnimation->KeyCode)
		{
		case 'J':
			if (chrAttackTarget)
				ParkAssaParticle_ChaosKara2(chrAttackTarget);
			LastSkillParam = 0;
			break;
		case 'K':
			ParkAssaParticle_ChaosKaraSkill_Monster(this);
			SkillPlay_Monster_Effect(this, SKILL_PLAY_CHAOSCARA_VAMP, 220);
			LastSkillParam = 1;
			break;
		}
		break;
		//°£¿ËË¹
	case MONSTEREFFECTID_Draxos:
		if (psModelAnimation && psModelAnimation->KeyCode == 'J')
			ParkParticle_DraxosSkill(this, 70);
		break;
	case smCHAR_SOUND_ACERO:
		if (psModelAnimation && psModelAnimation->KeyCode == 'J')
			AssaParticle_Effect("AceroStart", this, 0);
		break;
	case smCHAR_SOUND_CHALYBS:
		if (psModelAnimation && psModelAnimation->KeyCode == 'J')
			AssaParticle_Effect("ChalybsStart", this, 0);
		break;
	case smCHAR_SOUND_GREEDY:
		if (psModelAnimation && psModelAnimation->KeyCode == 'K')
			AssaParticle_Effect("GreedyStart", this, 0);
		break;
	case smCHAR_SOUND_NAJAN:
		if (psModelAnimation)
			AssaParticle_Effect("MonsterNajanSkill1", this, 0);
		break;
	case smCHAR_SOUND_WLORD:
		if (psModelAnimation)
		{
			AssaParticle_Effect("WLordSkill1", this, 0);
			LastSkillParam = 0;
		}
		break;
	case smCHAR_SOUND_DEY:
		if (psModelAnimation && psModelAnimation->KeyCode == 'J')
			AssaParticle_Effect("DeyStart", this, 0);
		break;
	case smCHAR_SOUND_GURKOB:
		if (psModelAnimation && psModelAnimation->KeyCode == 'J')
			AssaParticle_Effect("GurkobStart", this, 0);
		break;
	case smCHAR_SOUND_SATHLA:
		if (psModelAnimation && psModelAnimation->KeyCode == 'J')
			AssaParticle_Effect("ShathlaStart", this, 0);
		break;
	case smCHAR_SOUND_YAGDITHA:
		if (psModelAnimation && psModelAnimation->KeyCode == 'J')
			AssaParticle_Effect("YagdithaStart", this, 0);
		break;
	case smCHAR_SOUND_REDEYE:
		ParkParticle_RedEyeSkill(this);
		break;
	case snCHAR_SOUND_CASTLE_SOLDER_A:
		AssaMotionBlur(this, "Bip01_w", "Bip01 Effect", 80);
		break;
	case snCHAR_SOUND_CASTLE_SOLDER_B:
		AssaMotionBlur(this, "Bip01 waraxe", "Bip01 Effect", 80);
		break;
	case snCHAR_SOUND_CASTLE_SOLDER_C:
		AssaMotionBlur(this, "Bip01 Sword", "Bip01 Effect", 80);
		break;
	case snCHAR_SOUND_REVIVED_KNIGHT:
		if (chrAttackTarget)
		{
			if (psModelAnimation->KeyCode == 'H')
				SkillPlaySound(SKILL_SOUND_SKILL_PIERCING, pX, pY, pZ);
		}
		break;
	case snCHAR_SOUND_REVIVED_PRIESTESS:
		SkillPlaySound(SKILL_SOUND_SKILL_CASTING_MAGICIAN, pX, pY, pZ);
		pos.x = pX;
		pos.y = pY;
		pos.z = pZ;
		sinEffect_StartMagic(&pos, CHARACTERCLASS_Magician);
		break;
	case snCHAR_SOUND_REVIVED_PIKEMAN:
		if (chrAttackTarget)
		{
			switch (psModelAnimation->KeyCode)
			{
			case 'Z':
				AssaMotionBlur(this, "Bip01 R Hand", "bip01 wea", 80);
				break;
			}
		}
		break;
	}

	return TRUE;
}

//¸ó½ºÅÍ ½ºÅ³ ÀÌº¥Æ®
int Unit::EventSkill_Monster()
{
	POINT3D	pos, pos2;
	RECT rect;
	int x, y, z;

	switch (sCharacterData.iMonsterEffectID)
	{
	case snCHAR_SOUND_NAZ:
		break;
	case snCHAR_SOUND_HEADCUTTER:
	{
		auto sPosition = GetMoveLocation(0, 0, 60 * fONE, 0, Angle.y, 0);
		StartEffectMonster(pX + sPosition.iX, pY + sPosition.iY, pZ + sPosition.iZ, 0, Angle.y, 0, MONSTER_HEADER_CUTTER_HIT1);
	}
		
		break;
	case snCHAR_SOUND_TEMPLEGUARD:
	case snCHAR_SOUND_DMACHINE:
	case snCHAR_SOUND_TURTLE_CANNON:
		if (chrAttackTarget)
		{
			auto sPosition = GetMoveLocation(0, 40 * fONE, 0, 0, Angle.y, 0);
			StartEffectMonsterDest(pX + sPosition.iX, pY + sPosition.iX, pZ + sPosition.iZ, chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ, MONSTER_DMACHINE_MISSILE2);
		}
		break;
	case snCHAR_SOUND_REVIVED_KNIGHT:
		switch (psModelAnimation->KeyCode)
		{
		case 'H':
			if (chrAttackTarget)
			{
				sinSkillEffect_Piercing_Attack(this);
			}
			break;
		case 'Z':
			if (chrAttackTarget && GetAttackPoint(&x, &y, &z) == TRUE)
			{
				pos.x = x;
				pos.y = y;
				pos.z = z;
				if (MotionEvent == 1)
				{
					AssaParticle_GrandCrossHorz(&pos, Angle.y);
					SkillPlaySound(SKILL_SOUND_SKILL_SWING2, pX, pY, pZ);
				}
				else
				{
					AssaParticle_GrandCrossVert(&pos, Angle.y);
					SkillPlaySound(SKILL_SOUND_SKILL_GRAND_CROSS, pX, pY, pZ);
				}
			}
			else
				PlayWaponSoundDirect(pX, pY, pZ, 13);
			break;
		}
		break;
	case snCHAR_SOUND_OMICRON:
		if (chrAttackTarget)
		{
			auto sPosition = GetMoveLocation(0, 20 * fONE, 20 * fONE, 0, Angle.y, 0);
			StartEffectMonster(pX + sPosition.iX, pY + sPosition.iX, pZ + sPosition.iZ, 0, Angle.y, 0, MONSTER_OMICRON_HIT1);
		}
		break;
	case snCHAR_SOUND_RATOO:
		if (chrAttackTarget)
			AssaParticle_RatooHit1(this);
		break;
	case snCHAR_SOUND_MOKOVA:
	case snCHAR_SOUND_STYGIANLORD:
		if (chrAttackTarget)
			StartEffectMonster(pX, pY, pZ, MONSTER_STYGIANLORD_MAGIC1);
		break;
	case snCHAR_SOUND_SHADOW:
		if (chrAttackTarget)
		{
			auto sPosition = GetMoveLocation(0, 140 * fONE, 32 * fONE, 0, Angle.y, 0);
			StartEffectMonsterDest(pX + sPosition.iX, pY + sPosition.iX, pZ + sPosition.iZ, chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ, Angle.x, Angle.y, Angle.z, MONSTER_SHADOW_SHOT1);
		}
		break;

	case snCHAR_SOUND_SUCCUBUS:
		if (chrAttackTarget)
		{
			if (sCharacterData.iLevel <= 75)
			{
				StartEffectMonster(pX, pY, pZ, MONSTER_SERQBUS_MAGIC1);
				StartEffect_Serqbus_Skill1(chrAttackTarget, SUCCUBUS_CURSE_TIME);
				StartEffectMonster(chrAttackTarget->pX, chrAttackTarget->pY + chrAttackTarget->PatHeight, chrAttackTarget->pZ, MONSTER_SERQBUS_MAGIC_ATTACK1);

				if (chrAttackTarget == lpCurPlayer)
				{
					if (!sDisplayState[0].Absorb)
						sDisplayState[0].Absorb = -GetRandomPos(2, 6);
					sDisplayState[0].MaxTime = dwPlayTime + SUCCUBUS_CURSE_TIME * 1000;
				}
			}
			else if (sCharacterData.iLevel < 80)
			{
				if (chrAttackTarget->sCharacterData.iType != CHARACTERTYPE_Player)
				{
					StartEffectMonster(pX, pY, pZ, MONSTER_SERQBUS_MAGIC2);
					StartEffectMonster(chrAttackTarget->pX, chrAttackTarget->pY + chrAttackTarget->PatHeight, chrAttackTarget->pZ, MONSTER_SERQBUS_MAGIC_ATTACK2);
				}
			}
			else if (sCharacterData.iLevel < 90)
			{
				StartEffectMonster(pX, pY, pZ, MONSTER_SERQBUS_MAGIC3);
				StartEffect_Serqbus_Skill3(chrAttackTarget, SUCCUBUS_CURSE_TIME);
				StartEffectMonster(chrAttackTarget->pX, chrAttackTarget->pY + chrAttackTarget->PatHeight, chrAttackTarget->pZ, MONSTER_SERQBUS_MAGIC_ATTACK3);

				if (chrAttackTarget == lpCurPlayer)
				{
					if (!sDisplayState[1].PercentDamage[0])
					{
						sDisplayState[1].PercentDamage[0] = -GetRandomPos(10, 15);
						sDisplayState[1].PercentDamage[1] = sDisplayState[1].PercentDamage[0];
					}
					sDisplayState[1].MaxTime = dwPlayTime + SUCCUBUS_CURSE_TIME * 1000;
				}
			}
			else
				ParkIncubusSummonerSkill(this);
		}
		break;
	case snCHAR_SOUND_EVILPLANT:
		if (sCharacterData.iLevel >= 60)
			AssaParticle_EvilPlantShot(this);
		else
			AssaParticle_EvilMapleShot(this);
		break;
	case snCHAR_SOUND_STONEGOLEM:
		AssaParticle_StoneGolemShot(this);
		break;
	case snCHAR_SOUND_SOLIDSNAIL:
		if (chrAttackTarget)
		{
			pos.x = chrAttackTarget->pX;
			pos.y = chrAttackTarget->pY;
			pos.z = chrAttackTarget->pZ;

			AssaParticle_SnailShot(this, &pos);
		}
		break;
	case snCHAR_SOUND_SCORPION:
		if (chrAttackTarget && sCharacterData.iLevel == 50)
		{
			pos.x = chrAttackTarget->pX;
			pos.y = chrAttackTarget->pY;
			pos.z = chrAttackTarget->pZ;

			AssaParticle_SnailShot(this, &pos);
		}
		break;
	case snCHAR_SOUND_THORNCRAWLER:
		if (chrAttackTarget)
		{
			pos.x = chrAttackTarget->pX;
			pos.y = chrAttackTarget->pY;
			pos.z = chrAttackTarget->pZ;

			AssaParticle_ThornCrawlerShot(this, &pos);
		}
		break;
	case snCHAR_SOUND_NIGHTMARE:
	case snCHAR_SOUND_HEST:
		AssaParticle_NightMare(this);
		break;
	case snCHAR_SOUND_GUARDIAN_SAINT:
		AssaParticleClanMonsterHit1(this);
		break;
	case snCHAR_SOUND_HYPERMACHINE:
		if (chrAttackTarget)
		{
			pos.x = chrAttackTarget->pX;
			pos.y = chrAttackTarget->pY;
			pos.z = chrAttackTarget->pZ;
			AssaParticle_MonsterIronHyperSkill1(this, &pos);
		}
		break;
	case snCHAR_SOUND_RUNICGUARDIAN:
		if (chrAttackTarget)
			AssaParticle_MonsterIronRunicGuardian(this, chrAttackTarget);
		break;
	case snCHAR_SOUND_BABEL:
		if (chrAttackTarget)
			AssaParticle_MonsterRunicGrardianBossSkill(this);
		break;
	case snCHAR_SOUND_MOUNTAIN:
		AssaParticle_MonsterIronMountainSkill1(this);
		break;
	case snCHAR_SOUND_TOWERGOLEM:
		AssaParticle_MonsterIronTowerGolemSkill1(this);
		break;
	case snCHAR_SOUND_SADNESS:
		AssaParticle_MonsterIronSadNessSkill1(this);
		break;
	case snCHAR_SOUND_IRONFIST:
		AssaParticle_MonsterIronFist(this);
		break;
	case snCHAR_SOUND_MORGON:
	case snCHAR_SOUND_GORGON:
		AssaParticle_MonsterIronMorgonHit(this);
		break;
	case snCHAR_SOUND_ICEGOLEM:
		ParkAssaParticle_IceGolemShot(this);
		break;
	case snCHAR_SOUND_FROST:
		ParkAssaParticle_AcientDia(this);
		break;
	case snCHAR_SOUND_FROZEN:
		if (chrAttackTarget)
			ParkAssaParticle_MistIceBall(this, chrAttackTarget);
		break;
		// ±ùË®¾§
	case snCHAR_SOUND_MYSTIC:
		if (chrAttackTarget)
		{
			StartEffectMonster(pX, pY, pZ, MONSTER_SERQBUS_MAGIC2);
			StartEffect_Serqbus_Skill1(chrAttackTarget, SUCCUBUS_CURSE_TIME);
			StartEffectMonster(chrAttackTarget->pX, chrAttackTarget->pY + chrAttackTarget->PatHeight, chrAttackTarget->pZ, MONSTER_SERQBUS_MAGIC_ATTACK1);

			if (chrAttackTarget == lpCurPlayer)
			{
				if (!sDisplayState[0].Absorb)
					sDisplayState[0].Absorb = -GetRandomPos(10, 16);
				sDisplayState[0].MaxTime = dwPlayTime + SUCCUBUS_CURSE_TIME * 1000;
			}
		}
		break;
	case snCHAR_SOUND_DEATHKNIGHT:
		if (psModelAnimation->KeyCode == 'N')
			ParkAssaParticle_Valento1(this);
		break;
	case snCHAR_SOUND_SPIDER:
		ParkAssaParticle_SpiderTrooperHit1(this);
		break;
	case snCHAR_SOUND_STINGRAY:
		ParkAssaParticle_StingRay(this);
		break;
	case snCHAR_SOUND_M_LORD:
		SkillPlay_MummyLord_Effect(this, 200);
		break;
	case snCHAR_SOUND_GOBLINSHAMAN:
		SkillPlay_MummyLord_Effect(this, 200);
		break;
	case snCHAR_SOUND_BLIZZARD_GIANT:
		if (chrAttackTarget)
			ParkBlizzardGiantSkillToTarget(chrAttackTarget);
		break;
	case snCHAR_SOUND_DEVIL_BIRD:
		if (chrAttackTarget)
			ParkDevilBirdSkillToTarget(chrAttackTarget);
		break;
	case snCHAR_SOUND_KELVEZU:
		if (chrAttackTarget)
		{
			if (psModelAnimation->KeyCode == 'I')
			{
				ParkKelvezuSkillHit(chrAttackTarget);
				ParkKelvezuSkill1(this);
			}
			else
				ParkKelvezuSkillHit(chrAttackTarget);
		}
		break;
	case snCHAR_SOUND_DARKPHALANX:
		ParkAssaParticle_DarkPhalanx(this);
		break;
		// »ðÁÒÊ÷
	case snCHAR_SOUND_FIREWORM:
		if (chrAttackTarget)
			ParkAssaParticle_FireWorm(chrAttackTarget, 1);
		break;
	case snCHAR_SOUND_CHIMERA:
		if (chrAttackTarget)
			ParkAssaParticle_ChimeraSkill(chrAttackTarget);
		break;
	case snCHAR_SOUND_BLOODYKNIGHT:
		ParkAssaParticle_BloodySkill(this);
		break;
	case snCHAR_SOUND_HELLHOUND:
		ParkAssaParticle_HellHoundSkillAttack(this);
		break;
	case snCHAR_SOUND_DARKGUARD:
		if (chrAttackTarget)
			ParkAssaParticle_DarkGuardSkill(this, chrAttackTarget);
		break;
	case snCHAR_SOUND_DARKMAGE:
		if (chrAttackTarget)
			ParkAssaParticle_DarkMageSkill(chrAttackTarget);
		break;
	case snCHAR_SOUND_SETO:
		SkillArchMageFlameWave(this);
		break;
	case snCHAR_SOUND_KINGSPIDER:
		if (chrAttackTarget)
		{
			auto sPosition = GetMoveLocation(0, 0, 68 * fONE, 0, Angle.y, 0);
			StartEffectMonster(pX + sPosition.iX, pY + 22 * fONE, pZ + sPosition.iZ, MONSTER_HULK_HIT1);
		}
		break;
	case snCHAR_SOUND_S_METALGOLEM:
		if (chrAttackTarget)
		{
			auto sPosition = !sCharacterData.sSize ?
				GetMoveLocation(0, 0, 54 * fONE, 0, Angle.y, 0) : 
				GetMoveLocation(0, 0, 54 * sCharacterData.sSize, 0, Angle.y, 0);

			StartEffectMonster(pX + sPosition.iX, pY + 48 * fONE, pZ + sPosition.iZ, MONSTER_HULK_HIT1);
		}
		break;
	case snCHAR_SOUND_S_WOLVERLIN:
		if (chrAttackTarget)
		{
			auto sPosition = !sCharacterData.sSize ?
				GetMoveLocation(0, 0, 50 * fONE, 0, Angle.y, 0) : 
				GetMoveLocation(0, 0, 50 * sCharacterData.sSize, 0, Angle.y, 0);

			x = pX + sPosition.iX;
			z = pZ + sPosition.iZ;
			y = pY + 18 * fONE;
			StartEffectMonster(x, y, z, MONSTER_PIGON_PARTICLE1);
			StartEffectMonster(x, y, z, MONSTER_PIGON_PARTICLE1);
			StartEffectMonster(x, y, z, MONSTER_PIGON_PARTICLE1);
			StartEffectMonster(x, y, z, MONSTER_PIGON_PARTICLE1);
		}
		break;
	case snCHAR_SOUND_S_ARCUDA:
		if (chrAttackTarget)
			AssaParticle_Arcuda(this);
		break;
	case snCHAR_SOUND_NPC_SKILLMASTER:
		if (chrAttackTarget)
		{
			switch (psModelAnimation->KeyCode)
			{
			case 'A':
				StartSkillDest(pX, pY + 24 * fONE, pZ, chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ, SKILL_SPARK, 8);
				SkillPlaySound(SKILL_SOUND_SKILL_SPARK2, pX, pY, pZ);
				break;
			case 'B':
				if (GetAttackPoint(&x, &y, &z) == TRUE)
				{
					StartSkill(x, y, z, 0, 0, 0, SKILL_TRIPLE_IMPACT);
					SetDynLight(x, y, z, 100, 0, 0, 0, 300);
					SkillPlaySound(SKILL_SOUND_SKILL_AVANGING_CRASH, pX, pY, pZ);
				}
				break;
			case 'N':
				if (GetAttackPoint(&x, &y, &z) == TRUE)
				{
					pos.x = x;
					pos.y = y;
					pos.z = z;
					AssaParticle_ChainLance(&pos);
				}
				break;
			case 'M':
			{
				auto sPosition = GetMoveLocation(0, 24 * fONE, 24 * fONE, 0, Angle.y, 0);
				pos.x = pX + sPosition.iX;
				pos.y = pY + sPosition.iY;
				pos.z = pZ + sPosition.iZ;
				pos2.x = chrAttackTarget->pX;
				pos2.y = chrAttackTarget->pY + 24 * fONE;
				pos2.z = chrAttackTarget->pZ;
				SkillSagittarionPhoneixShot(this, &pos, &pos2);
				SkillPlaySound(SKILL_SOUND_SKILL_PHOENIX_SHOT, pX, pY, pZ);
			}
				
				break;
			case 'Y':
				if (GetAttackPoint(&pos.x, &pos.y, &pos.z) == TRUE)
				{
					SkillWarriorDestroyerHit(&pos);
					if (MotionEvent < 3)
						SkillPlaySound(SKILL_SOUND_SKILL_AVANGING_CRASH, pX, pY, pZ);
					else
						SkillPlaySound(SKILL_SOUND_SKILL_EXPANSION2, pX, pY, pZ);
				}
				break;
			case 'L':
				if (GetAttackPoint(&x, &y, &z) == TRUE)
				{
					StartSkill(x, y, z, 0, 0, 0, SKILL_TRIPLE_IMPACT);
					SetDynLight(x, y, z, 100, 0, 0, 0, 400);
					switch (MotionEvent)
					{
					case 1:
						SkillPlaySound(SKILL_SOUND_SKILL_CHAIN_LANCE2, pX, pY, pZ);
						break;
					case 2:
						SkillPlaySound(SKILL_SOUND_SKILL_AVANGING_CRASH, pX, pY, pZ);
						break;
					case 3:
					case 4:
						SkillPlaySound(SKILL_SOUND_SKILL_CHARGING_STRIKE, pX, pY, pZ);
						break;
					}
				}
				break;
			}
		}
		break;
	case snCHAR_SOUND_NPC_MAGICMASTER:
		if (chrAttackTarget)
		{
			switch (psModelAnimation->KeyCode)
			{
			case 'R':
				AssaParticle_EnergyShield(this, 5);
				SkillPlaySound(SKILL_SOUND_SKILL_ENERGY_SHIELD, pX, pY, pZ);
				break;
			case 'E':
				sinEffect_MultiSpark(this, chrAttackTarget, 5);
				SkillPlaySound(SKILL_SOUND_SKILL_MULTISPARK, pX, pY, pZ);
				break;
			case 'U':
			{
				auto sPosition = GetMoveLocation(0, 24 * fONE, 24 * fONE, 0, Angle.y, 0);
				pos.x = pX + sPosition.iX;
				pos.y = pY + sPosition.iY;
				pos.z = pZ + sPosition.iZ;
				pos2.x = chrAttackTarget->pX;
				pos2.y = chrAttackTarget->pY + 32 * fONE;
				pos2.z = chrAttackTarget->pZ;

				AssaParticle_DeadLay(&pos, &pos2);
				SkillPlaySound(SKILL_SOUND_SKILL_DEATHRAY, pX, pY, pZ);
			}
				break;
			case 'I':
			{
				auto sPosition = GetMoveLocation(0, 24 * fONE, 24 * fONE, 0, Angle.y, 0);
				StartEffectMonsterDest(pX + sPosition.iX, pY + sPosition.iY, pZ + sPosition.iZ, chrAttackTarget->pX, chrAttackTarget->pY + 20 * fONE, chrAttackTarget->pZ, MONSTER_PIGON_SHOT1);

				if (((dwPlayTime >> 4) & 1) == 0)
					SkillPlaySound(SKILL_SOUND_SKILL_FIREBALL1, pX, pY, pZ);
				else
					SkillPlaySound(SKILL_SOUND_SKILL_FIREBALL2, pX, pY, pZ);
			}
				break;

			case 'H':
			{
				Angle.y = GetRadian2D(pX, pZ, chrAttackTarget->pX, chrAttackTarget->pZ);
				SkillCelestialGlacialSpike(this);

				auto sPosition = GetMoveLocation(0, 0, 64 * fONE, 0, Angle.y, 0);
				SetDynLight(pX + sPosition.iX, pY, pZ + sPosition.iZ, 0, 0, 100, 0, 700);

				if (rand() % 2)
					SkillPlaySound(SKILL_SOUND_SKILL_GLACIAL_SPIKE1, pX, pY, pZ);
				else
					SkillPlaySound(SKILL_SOUND_SKILL_GLACIAL_SPIKE2, pX, pY, pZ);

				if (chrAttackTarget == lpCurPlayer)
				{
					lpCurPlayer->PlaySlowCount = 90;
					lpCurPlayer->AttackIce -= 160;
				}
			}

				break;

			case 'G':
				pos.x = chrAttackTarget->pX;
				pos.y = chrAttackTarget->pY;
				pos.z = chrAttackTarget->pZ;
				SkillArchMageMeteo(&pos);
				SkillPlaySound(SKILL_SOUND_SKILL_METEO1, pX, pY, pZ);
				break;
			}
		}
		break;
	case snCHAR_SOUND_CASTLE_SOLDER_A:
	case snCHAR_SOUND_CASTLE_SOLDER_B:
	case snCHAR_SOUND_CASTLE_SOLDER_C:
		if (chrAttackTarget)
		{
			if (GetAttackPoint(&x, &y, &z) == TRUE)
			{
				StartSkill(x, y, z, 0, 0, 0, SKILL_TRIPLE_IMPACT);
				SetDynLight(x, y, z, 100, 0, 0, 0, 300);
				SkillPlaySound(SKILL_SOUND_SKILL_AVANGING_CRASH, pX, pY, pZ);
			}
		}
		break;

	case snCHAR_SOUND_CASTLE_CRYSTAL_R:
		AssaParticle_CastleRed(this);
		break;

	case snCHAR_SOUND_CASTLE_CRYSTAL_G:
		AssaParticle_CastleGreen(this);
		break;

	case snCHAR_SOUND_CASTLE_CRYSTAL_B:
		AssaParticle_CastleBlue(this);
		break;
	case snCHAR_SOUND_REVIVED_MAGICIAN:
		if (chrAttackTarget)
		{
			switch (psModelAnimation->KeyCode)
			{
			case 'O':
			{
				auto sPosition = GetMoveLocation(0, 24 * fONE, 24 * fONE, 0, Angle.y, 0);
				pos.x = pX + sPosition.iX;
				pos.y = pY + sPosition.iY;
				pos.z = pZ + sPosition.iZ;
				pos2.x = chrAttackTarget->pX;
				pos2.y = chrAttackTarget->pY + 32 * fONE;
				pos2.z = chrAttackTarget->pZ;

				AssaParticle_DeadLay(&pos, &pos2);
				SkillPlaySound(SKILL_SOUND_SKILL_DEATHRAY, pX, pY, pZ);
			}
				break;
			case 'Q':
				SkillArchMageFlameWave(this);

				if (rand() % 2)
					SkillPlaySound(SKILL_SOUND_SKILL_FLAME_WAVE1, pX, pY, pZ);
				else
					SkillPlaySound(SKILL_SOUND_SKILL_FLAME_WAVE2, pX, pY, pZ);
				break;
			case 'Z':
				pos.x = chrAttackTarget->pX;
				pos.y = chrAttackTarget->pY;
				pos.z = chrAttackTarget->pZ;
				SkillArchMageMeteo(&pos);
				SkillPlaySound(SKILL_SOUND_SKILL_METEO1, pX, pY, pZ);
				break;
			}
		}
		break;
	case snCHAR_SOUND_REVIVED_ARCHER:
		if (chrAttackTarget)
		{
			switch (psModelAnimation->KeyCode)
			{
			case 'O':
				GetAttackPoint(&x, &y, &z);
				StartSkillDest(x, y, z, chrAttackTarget->pX, chrAttackTarget->pY + (24 * fONE), chrAttackTarget->pZ, SKILL_WIND_ARROW);
				SkillPlaySound(SKILL_SOUND_WIND_ARROW, pX, pY, pZ);
				break;
			case 'Z':
				int cnt = iFrame - psModelAnimation->StartFrame * 80;
				if (psModelAnimation->EventFrame[1] <= (DWORD)cnt)
				{
					auto sPosition = GetMoveLocation(0, 24 * fONE, 24 * fONE, 0, Angle.y, 0);
					pos.x = pX + sPosition.iX;
					pos.y = pY + sPosition.iY;
					pos.z = pZ + sPosition.iZ;
					pos2.x = chrAttackTarget->pX;
					pos2.y = chrAttackTarget->pY + 24 * fONE;
					pos2.z = chrAttackTarget->pZ;
					SkillSagittarionPhoneixShot(this, &pos, &pos2);
					SkillPlaySound(SKILL_SOUND_SKILL_PHOENIX_SHOT, pX, pY, pZ);
				}
				break;
			}
		}
		break;
	case snCHAR_SOUND_REVIVED_ATALANTA:
		switch (psModelAnimation->KeyCode)
		{
		case 'O':
			if (chrAttackTarget && GetAttackPoint(&x, &y, &z) == TRUE)
			{
				pos.x = x;
				pos.y = y;
				pos.z = z;
				pos2.x = chrAttackTarget->pX;
				pos2.y = chrAttackTarget->pY + 28 * fONE;
				pos2.z = chrAttackTarget->pZ;

				AssaParticle_StormJavelin(&pos, &pos2);

				rect.left = -30;
				rect.right = 30;
				rect.top = 0;
				rect.bottom = 240;
				rect.bottom += 20;
				rect.bottom += 20;

				for (int cnt = 0; cnt < dmSelected_CharCnt; cnt++)
				{
					if (lpSelected_Char[cnt])
						AssaParticle_StormJavelinHit(lpSelected_Char[cnt], this, 0.5f);
				}
				switch (rand() % 2)
				{
				case 0:
					SkillPlaySound(SKILL_SOUND_SKILL_STORM_JAVELIN1, pX, pY, pZ);
					break;
				case 1:
					SkillPlaySound(SKILL_SOUND_SKILL_STORM_JAVELIN2, pX, pY, pZ);
					break;
				}
			}
			break;
		case 'Z':
			if (chrAttackTarget)
			{
				auto sPosition = GetMoveLocation(0, 24 * fONE, 24 * fONE, 0, Angle.y, 0);
				pos.x = pX + sPosition.iX;
				pos.y = pY + sPosition.iY;
				pos.z = pZ + sPosition.iZ;
				pos2.x = chrAttackTarget->pX;
				pos2.y = chrAttackTarget->pY + 40 * fONE;
				pos2.z = chrAttackTarget->pZ;

				SkillVengeance(&pos, &pos2);

				if (MotionEvent == 1)
					SkillPlaySound(SKILL_SOUND_SKILL_VENGEANCE1, pX, pY, pZ);
				else
					SkillPlaySound(SKILL_SOUND_SKILL_VENGEANCE2, pX, pY, pZ);
			}
			break;
		}
		break;
	case snCHAR_SOUND_REVIVED_FIGTHER:
		if (chrAttackTarget)
		{
			switch (psModelAnimation->KeyCode)
			{
			case 'G':
				AssaParticle_AvangingCrash(this);
				SkillPlaySound(SKILL_SOUND_SKILL_AVANGING_CRASH, pX, pY, pZ);
				break;
			case 'Z':
				if (GetAttackPoint(&pos.x, &pos.y, &pos.z) == TRUE)
				{
					SkillWarriorDestroyerHit(&pos);
					if (MotionEvent < 3)
						SkillPlaySound(SKILL_SOUND_SKILL_AVANGING_CRASH, pX, pY, pZ);
					else
						SkillPlaySound(SKILL_SOUND_SKILL_EXPANSION2, pX, pY, pZ);
				}
				break;
			}
		}
		break;
	case snCHAR_SOUND_REVIVED_MECANICIAN:
		if (chrAttackTarget)
		{
			switch (psModelAnimation->KeyCode)
			{
			case 'O':
				StartSkillDest(pX, pY + 24 * fONE, pZ, chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ, SKILL_SPARK, 8);
				SkillPlaySound(SKILL_SOUND_SKILL_SPARK2, pX, pY, pZ);
				break;
			case 'Z':
				if (GetAttackPoint(&x, &y, &z) == TRUE)
				{
					StartSkill(x, y, z, 0, Angle.y, 0, SKILL_GREAT_SMASH);
					SkillPlaySound(SKILL_SOUND_SKILL_SWING1, pX, pY, pZ);
				}
				break;
			}
		}
		break;
	case snCHAR_SOUND_REVIVED_PIKEMAN:
		if (chrAttackTarget)
		{
			switch (psModelAnimation->KeyCode)
			{
			case 'G':
				if (GetAttackPoint(&x, &y, &z) == TRUE)
				{
					StartEffect(x, y, z, EFFECT_CRITICAL_HIT1);
					SetDynLight(x, y, z, 100, 0, 0, 0, 400);
					SkillPlaySound(SKILL_SOUND_JUMPING_CRASH2, pX, pY, pZ);
				}
				break;
			case 'Z':
				if (GetAttackPoint(&x, &y, &z) == TRUE)
				{
					pos.x = x;
					pos.y = y;
					pos.z = z;
					AssaParticle_ChainLance(&pos);
					switch (MotionEvent)
					{
					case 1:
						SkillPlaySound(SKILL_SOUND_SKILL_CHAIN_LANCE1, pX, pY, pZ);
						break;
					case 2:
						SkillPlaySound(SKILL_SOUND_SKILL_CHAIN_LANCE2, pX, pY, pZ);
						break;
					case 3:
						SkillPlaySound(SKILL_SOUND_SKILL_CHAIN_LANCE3, pX, pY, pZ);
						break;
					}
				}
				break;
			}
		}
		break;
	case snCHAR_SOUND_REVIVED_PRIESTESS:
		if (chrAttackTarget)
		{
			switch (psModelAnimation->KeyCode)
			{
			case 'O':
				sinEffect_MultiSpark(this, chrAttackTarget, 5);
				SkillPlaySound(SKILL_SOUND_SKILL_MULTISPARK, pX, pY, pZ);
				break;
			case 'H':
				AssaParticle_VigorBall(this, chrAttackTarget);
				switch (rand() % 2)
				{
				case 0:
					SkillPlaySound(SKILL_SOUND_SKILL_VIGOR_BALL1, pX, pY, pZ);
					break;
				case 1:
					SkillPlaySound(SKILL_SOUND_SKILL_VIGOR_BALL2, pX, pY, pZ);
					break;
				}
				break;
			case 'Z':
			{
				Angle.y = GetRadian2D(pX, pZ, chrAttackTarget->pX, chrAttackTarget->pZ);
				SkillCelestialGlacialSpike(this);
				auto sPosition = GetMoveLocation(0, 0, 64 * fONE, 0, Angle.y, 0);
				SetDynLight(pX + sPosition.iX, pY, pZ + sPosition.iZ, 0, 0, 100, 0, 700);
				if (rand() % 2)
					SkillPlaySound(SKILL_SOUND_SKILL_GLACIAL_SPIKE1, pX, pY, pZ);
				else
					SkillPlaySound(SKILL_SOUND_SKILL_GLACIAL_SPIKE2, pX, pY, pZ);

				if (chrAttackTarget == lpCurPlayer)
				{
					lpCurPlayer->PlaySlowCount = 90;
					lpCurPlayer->AttackIce -= 160;
				}
			}
				break;
			}
		}
		break;
	case snCHAR_SOUND_HOBOGOLEM:
		if (chrAttackTarget)
		{
			auto sPosition = GetMoveLocation(7000, 30 * fONE, 50 * fONE, 0, Angle.y, 0);
			StartEffectMonsterDest(pX + sPosition.iX, pY + sPosition.iY, pZ + sPosition.iZ, chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ, MONSTER_DMACHINE_MISSILE1);
		}
		break;

	case snCHAR_SOUND_SPRIN:
		if (chrAttackTarget && psModelAnimation->KeyCode == 'J')
		{
			ParkAssaParticle_HellHoundSkillAttack(this);
		}
		break;
	case snCHAR_SOUND_XETAN:
		if (chrAttackTarget && psModelAnimation->KeyCode == 'J')
		{
			ParkAssaParticle_DarkMageSkill(chrAttackTarget);
		}
		break;
	case snCHAR_SOUND_RUCA:
		if (chrAttackTarget && psModelAnimation->KeyCode == 'J')
		{
			auto sPosition = GetMoveLocation(0, 0, 64 * fONE, 0, Angle.y, 0);
			pos.x = pX + sPosition.iX;
			pos.y = pY + sPosition.iY + 32 * fONE;
			pos.z = pZ + sPosition.iZ;
			AssaParticle_MonsterIronHit1(&pos);
		}
		break;
	case snCHAR_SOUND_NAZSENIOR:
		if (chrAttackTarget && psModelAnimation->KeyCode == 'K')
		{
			auto sPosition = GetMoveLocation(0, 0, 100 * fONE, 0, Angle.y, 0);
			StartSkillDest(pX, pY, pZ, pX + sPosition.iX, pY, pZ + sPosition.iZ, SKILL_TORNADO2, 1);
		}
		break;
	case snCHAR_SOUND_UNDEADMAPLE:
		if (chrAttackTarget && psModelAnimation->KeyCode == 'J')
			AssaParticle_EvilPlantShot(this);
		break;
	case snCHAR_SOUND_WATERMELON:
		if (chrAttackTarget && psModelAnimation->KeyCode == 'K')
		{
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;

			pos2.x = chrAttackTarget->pX;
			pos2.y = chrAttackTarget->pY + 32 * fONE;
			pos2.z = chrAttackTarget->pZ;

			AssaParticle_IceShot(&pos, &pos2);
		}
		break;
	case snCHAR_SOUND_PUMPKINGHOST:
		if (chrAttackTarget && psModelAnimation->KeyCode == 'J')
			StartEffectMonster(chrAttackTarget->pX, chrAttackTarget->pY + 12 * fONE, chrAttackTarget->pZ, MONSTER_HULK_HIT1);
		break;
	case snCHAR_SOUND_SNOWMAN:
		if (chrAttackTarget && psModelAnimation->KeyCode == 'J')
		{
			pos.x = pX;
			pos.y = pY;
			pos.z = pZ;

			pos2.x = chrAttackTarget->pX;
			pos2.y = chrAttackTarget->pY + 32 * fONE;
			pos2.z = chrAttackTarget->pZ;

			AssaParticle_IceShot(&pos, &pos2);
		}
		break;
		// ÃÀ¶ÅÉ¯
	case snCHAR_SOUND_BOITATA:
		if (chrAttackTarget && psModelAnimation->KeyCode == 'J')
		{
			pos2.x = chrAttackTarget->pX;
			pos2.y = chrAttackTarget->pY;
			pos2.z = chrAttackTarget->pZ;

			pos.x = pX;
			pos.y = pY + 128 * fONE;
			pos.z = pZ;

			AssaParticle_FireShot(&pos, &pos2);
			AssaParticle_IceShot(&pos, &pos2);
			AssaParticle_LightShot(&pos, &pos2);

			if (rand() % 2)
				SkillPlaySound(SKILL_SOUND_SKILL_FIREBOLT1, pX, pY, pZ);
			else
				SkillPlaySound(SKILL_SOUND_SKILL_FIREBOLT2, pX, pY, pZ);
		}
		break;
	case smCHAR_SOUND_ICESERPENT:
		if (chrAttackTarget && psModelAnimation->KeyCode == 'J')
			AssaParticle_IceserpentSkill(this);
		break;
		// º®±ùÊ÷
	case smCHAR_SOUND_ICEWORM:
		if (chrAttackTarget && psModelAnimation->KeyCode == 'I')
			ParkAssaParticle_IceWorm(chrAttackTarget, TRUE);
		break;
		// º®±ù¶ñÄ§
	case smCHAR_SOUND_MINEBAT:
		if (chrAttackTarget && psModelAnimation->KeyCode == 'J')
			DevilBird_Skill(this);
		break;
		// ¿óÉ½»úÐµ
	case smCHAR_SOUND_MINEGOLEM:
		if (chrAttackTarget && psModelAnimation->KeyCode == 'J')
		{
			auto sPosition = GetMoveLocation(0, 20 * fONE, 100 * fONE, 0, Angle.y, 0);
			StartEffectMonster(pX + sPosition.iX, pY + sPosition.iY, pZ + sPosition.iZ, 0, Angle.y, 0, MONSTER_MINEGOLEM_HIT2);
		}
		break;
		// ¿óÉ½¾§Ê¯
	case smCHAR_SOUND_SEALCRASHER:
		if (chrAttackTarget && psModelAnimation->KeyCode == 'P')
		{
			StartEffectMonster(pX, pY, pZ, MONSTER_SERQBUS_MAGIC2);
			StartEffect_Serqbus_Skill1(chrAttackTarget, SUCCUBUS_CURSE_TIME);
			StartEffectMonster(chrAttackTarget->pX, chrAttackTarget->pY + chrAttackTarget->PatHeight, chrAttackTarget->pZ, MONSTER_SERQBUS_MAGIC_ATTACK1);

			if (chrAttackTarget == lpCurPlayer)
			{
				if (!sDisplayState[0].Absorb)
					sDisplayState[0].Absorb = -GetRandomPos(10, 16);
				sDisplayState[0].MaxTime = dwPlayTime + SUCCUBUS_CURSE_TIME * 1000;
			}
		}
		break;
		// ±ù¼×¶¾Öë
	case smCHAR_SOUND_TARANTULIKA:
		if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'J')
			ParkAssaParticle_Tarantulika(this);
		break;
		// ¶ñÄ§²®¾ô
	case smCHAR_SOUND_TULLA:
		if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'K')
			ParkAssaParticle_Valento3_1(this);
		break;
		//¿óÉ½¹ÜÀíÕß
	case smChAR_SOUND_UNDEADMANAGER:
	case smCHAR_SOUND_UNDEADMINER:
		if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'J')
			AssParticle_UnDeadManger(this, 2);
		break;
		// ÑÐ¾¿Ëù¼¼ÄÜÊ¦
	case smCHAR_SOUND_ITECHNICIAN:
		if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'J')
			AssaParticle_Effect("ItechnicianSkill", chrAttackTarget, 0);
		break;
		// ÑÐ¾¿Ëù¼¼ÊõÊ¦
	case smCHAR_SOUND_LTECHNICIAN:
		if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'J')
			AssaParticle_Effect("LtechnicianSkill", chrAttackTarget, 0);
		break;
		// ÑÐ¾¿Ëù¹¤³ÌÊ¦
	case smCHAR_SOUND_LENGINEER:
		if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'J')
			AssaParticle_Effect("LengineerSkill", chrAttackTarget, 0);
		break;
		// ÑÐ¾¿ËùÉøÍ¸Õß
	case smCHAR_SOUND_ISOLDIER:
		if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'J')
			AssaParticle_Effect("IsoldierSkill", chrAttackTarget, 0);
		break;
		// ÑÐ¾¿Ëù±¬ÆÆ±ø
	case smCHAR_SOUND_IBOMBER:
		if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'J')
			StartSkillDest(pX, pY + 60 * fONE, pZ, chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, SKILL_MECHANIC_BOMB, 10);
		break;
		// ÑÐ¾¿Ëù¾¯ÎÀ±ø
	case smCHAR_SOUND_LGUARDIAN:
		if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'J')
			AssaParticle_Effect("LguardianSkill", chrAttackTarget, 0);
		break;
		// ¸ß¼¶ÇÖÂÔÕß
	case smCHAR_SOUND_IELITE:
		if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'J')
			AssaParticle_Effect("IeliteSkill", chrAttackTarget, 0);
		break;
		// °£¿ËË¹
	case MONSTEREFFECTID_Draxos:
		if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'J')
		{
			if (MotionEvent == 1)
				AssaParticle_Effect("DraxosSkill1", chrAttackTarget, 0);
			else if (MotionEvent == 2)
				AssaParticle_Effect("DraxosSkill2", chrAttackTarget, 0);
		}
		break;
		//´óÂí
	case smCHAR_SOUND_LIZARD_BIGMAMA:
		if (chrAttackTarget)
			AssaParticle_Effect("LizardBigmamaSkill", chrAttackTarget, 0);
		break;
		//Ë¾Áî¹Ù
	case smCHAR_SOUND_LIZADR_COMMANDER:
		if (chrAttackTarget)
			AssaParticle_Effect("LizardCommanderSkill", chrAttackTarget, 0);
		break;
		//
	case smCHAR_SOUND_LIZADR_DOCTOR:
		if (chrAttackTarget)
			AssaParticle_Effect("LizardDoctorSkill", chrAttackTarget, 0);
		break;
	case smCHAR_SOUND_LIZADR_ELDER:
		if (chrAttackTarget)
			AssaParticle_Effect("LizardElderSkill", chrAttackTarget, 0);
		break;
	case smCHAR_SOUND_LIZADR_PAPA:
		if (chrAttackTarget)
			AssaParticle_Effect("LizardPapaSkill", chrAttackTarget, 0);
		break;
	case smCHAR_SOUND_LIZADR_SOLDIER:
		if (chrAttackTarget)
			AssaParticle_Effect("LizardSoldierSkill", chrAttackTarget, 0);
		break;
	case smCHAR_SOUND_NIHIL:
		if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'K')
			AssaParticle_Effect("NihilSkill", chrAttackTarget, 0);
		break;
	case smCHAR_SOUND_ACERO:
		if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'J')
			AssaParticle_Effect("AceroSkill", chrAttackTarget, 0);
		break;
	case smCHAR_SOUND_CHALYBS:
		if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'J')
			AssaParticle_Effect("ChalybsSkill", chrAttackTarget, 0);
		break;
	case smCHAR_SOUND_GREEDY:
		if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'K')
			AssaParticle_Effect("GreedySkill", chrAttackTarget, 0);
		break;
	case smCHAR_SOUND_RGUARD:
		if (chrAttackTarget)
			AssaParticle_Effect("RGuardSkill", chrAttackTarget, 0);
		break;
	case smCHAR_SOUND_DMYSTERY:
		if (chrAttackTarget)
		{
			auto sPosition = GetMoveLocation(0, 140 * fONE, 32 * fONE, 0, Angle.y, 0);
			StartEffectMonsterDest(pX + sPosition.iX, pY + sPosition.iY, pZ + sPosition.iZ, chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ, Angle.x, Angle.y, Angle.z, MONSTER_SHADOW_SHOT2);
		}
		break;
	case smCHAR_SOUND_IGNIS:
		if (chrAttackTarget)
			AssaParticle_Effect("MonsterIgnisSkill", chrAttackTarget, 0);
		break;
	case smCHAR_SOUND_NAJAN:
		if (chrAttackTarget)
		{
			if (MotionEvent == 2)
				AssaParticle_Effect("MonsterNajanSkill2", chrAttackTarget, 0);
		}
		break;
	case smCHAR_SOUND_CRIOS:
		if (chrAttackTarget)
			AssaParticle_Effect("CriosSkill", chrAttackTarget, 0);
		break;
	case smCHAR_SOUND_WLORD:
		if (chrAttackTarget)
			AssaParticle_Effect("WLordSkill2", chrAttackTarget, 0);
		break;
	case smCHAR_SOUND_MIDRANDA:
		if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'K')
			AssaParticle_Effect("MonsterMidrandaSkill", chrAttackTarget, 0);
		break;
	case smCHAR_SOUND_DEY:
		if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'J')
			AssaParticle_Effect("DeySkill", chrAttackTarget, 0);
		break;
	case smCHAR_SOUND_SHOGOTH:
		if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'J')
		{
			StartSkill(chrAttackTarget->pX, chrAttackTarget->pY + 10 * fONE, chrAttackTarget->pZ, 0, 0, 0, SKILL_M_BLOW);
			SkillPlaySound(SKILL_SOUND_SKILL_SWING1, pX, pY, pZ);
		}
		break;
	case smCHAR_SOUND_ARHDYRA:
		if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'J')
			AssaParticle_Effect("ArhdyraSkill", chrAttackTarget, 0);
		break;
	case smCHAR_SOUND_SATHLA:
		if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'J')
			AssaParticle_Effect("ShathlaSkill", chrAttackTarget, 0);
		break;
	case smCHAR_SOUND_FAUGN:
		if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'J')
			AssaParticle_Effect("FaugnSkill", chrAttackTarget, 0);
		break;
	case smCHAR_SOUND_KOON:
		if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'J')
			AssaParticle_Effect("KoonSkill", chrAttackTarget, 0);
		break;
	case smCHAR_SOUND_YAGDITHA:
		if (chrAttackTarget && psModelAnimation && psModelAnimation->KeyCode == 'J')
			AssaParticle_Effect("YagdithaSkill", chrAttackTarget, 0);
		break;
	case smCHAR_SOUND_BLUEMOUNTAIN:
		AssaParticle_BlueMountainSkill(this);
		break;
	case smCHAR_SOUND_MORGONIA:
		AssaParticle_MorgoniaSkill(this);
		break;
	case smCHAR_SOUND_TURTLEDRAGON:
		if (chrAttackTarget)
		{
			auto sPosition = GetMoveLocation(0, 40 * fONE, 0, 0, Angle.y, 0);
			StartEffectMonsterDest(pX + sPosition.iX, pY + sPosition.iY, pZ + sPosition.iZ, chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ, MONSTER_TURTLEDRAGON_SHOT2);
		}
		break;
	case smCHAR_SOUND_BONEHOUND:
		AssaParticle_BoneHoundHit(this);
		break;
	}

	PlayAttack();									//°ø°Ý Àû¿ë
	CharPlaySound(this);

	return TRUE;
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

//½áÊø¼¼ÄÜ
int Unit::EndSkill()
{
	int	point;
	int	param;

	point = (AttackSkil >> 8) & 0xF;
	param = (AttackSkil >> 12) & 0xF;

	switch (sCharacterData.iClass)
	{
	case CHARACTERCLASS_Magician:
		switch (AttackSkil & 0xFF)
		{
		case SKILL_PLAY_DIASTROPHISM:
			if (this == lpCurPlayer && MotionEvent < 3)
			{
				dm_SelectRange(pX, pY, pZ, Diastrophism_Area[point - 1], FALSE);
				dm_SendRangeDamage(pX, pY, pZ, 0, 
					cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin,
					cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax, 0, 0, AttackSkil);
			}
			break;
		case SKILL_PLAY_METEO:
			if (chrAttackTarget && point)
			{
				if (this == lpCurPlayer && MotionEvent < 4)
				{
					dm_SelectRange(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, Meteo_Area[point - 1], FALSE);
					dm_SendRangeDamage(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 0, 0, 0, 0, 0, lpCurPlayer->AttackSkil);
				}
			}
			break;
		}
		break;
	case CHARACTERCLASS_Priestess:
		switch (AttackSkil & 0xFF)
		{
		case SKILL_PLAY_S_PRMIEL:
			if (chrAttackTarget && point)
			{
				if (this == lpCurPlayer && MotionEvent < 4)
				{
					dm_SelectRange(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, S_Ramiel_Area[point - 1], FALSE);
					dm_SendRangeDamage(chrAttackTarget->pX,
						chrAttackTarget->pY,
						chrAttackTarget->pZ,
						0,
						cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin,
						cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax,
						0, 0, AttackSkil);
				}
			}
			break;
		}
		break;
	}

	MotionEvent++;

	return TRUE;
}

//»î¶¯¼¼ÄÜ
int Unit::EventSkill()
{
	int x, y, z;
	int	point;
	int	param;
	int	damage;
	int	temp;
	int cnt;
	POINT3D	Pos1, Pos2;
	RECT rect;
	Unit *lpChar;

	if (sCharacterData.iType == CHARACTERTYPE_Monster && iCharacterType != CHARACTERTYPE_Player)
		return EventSkill_Monster();
	point = (AttackSkil >> 8) & 0xF;
	param = (AttackSkil >> 12) & 0xF;
	int SkillCode = AttackSkil & 0xFF;
	int JobCode = sCharacterData.iClass;

	switch (JobCode)
	{
		//ÎäÊ¿
	case CHARACTERCLASS_Fighter:
		switch (SkillCode)
		{
			//¾øµØ±©×ß
		case SKILL_PLAY_RAVING:
			return FALSE;
			//¾«×¼Ö®»÷
		case SKILL_PLAY_IMPACT:
			if (this == lpCurPlayer && chrAttackTarget && MotionEvent < 2)
			{
				if (AttackCritcal >= 0)
				{
					temp = sCharacterData.iAttackRange;
					sCharacterData.iAttackRange += Impact_Attack_Rating[point - 1];
					cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
					sCharacterData.iAttackRange = temp;
					if (cnt > 0)
					{
						DamageExp(chrAttackTarget, cnt);
						if (AttackExp)
							AttackExp = 0;
					}
				}
			}
			return FALSE;
			//ÍþÁ¦³å»÷
		case SKILL_PLAY_TRIPLE_IMPACT:
			if (AttackCritcal >= 0)
			{
				if (GetAttackPoint(&x, &y, &z) == TRUE)
				{
					StartSkill(x, y, z, 0, 0, 0, SKILL_TRIPLE_IMPACT);
					SetDynLight(x, y, z, 100, 0, 0, 0, 400);
				}
				AttackCritcal = 1;
			}
			WeaponPlaySound(this);
			if (this == lpCurPlayer && chrAttackTarget && MotionEvent < T_Impact_Hit[point - 1])
			{
				if (AttackCritcal >= 0)
				{
					cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
					if (cnt > 0)
					{
						DamageExp(chrAttackTarget, cnt);
						if (AttackExp)
							AttackExp = 0;
					}
				}
			}
			break;
			//ÖÂÃü»ØÐý
		case SKILL_PLAY_BRUTAL_SWING:
			if (AttackCritcal >= 0)
			{
				if (GetAttackPoint(&x, &y, &z) == TRUE)
				{
					StartSkill(x, y, z, 0, 0, 0, SKILL_BRUTAL_SWING);
					SetDynLight(x, y, z, 100, 0, 0, 0, 400);
					SkillPlaySound(SKILL_SOUND_SKILL_SWING1, pX, pY, pZ);
				}
			}
			else
				WeaponPlaySound(this);
			break;
			//Õ½ÉñÖ®Å­
		case SKILL_PLAY_RAGEOF_ZECRAM:
			if (GetAttackPoint(&x, &y, &z) == TRUE)
			{
				if (MotionEvent == 1)
				{
					StartSkill(x, y, z, 0, 0, 0, SKILL_RAGE_OF_ZECRAM_HIT1);
					AddTimeEffect(SKILL_RAGE_OF_ZECRAM_HIT2, dwPlayTime + 600, x, y, z);

					if (this == lpCurPlayer && chrAttackTarget)
					{
						dm_SelectRange(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, R_Zecram_Area[point - 1], FALSE);
						dm_SendRangeDamage(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, 0, 0, lpCurPlayer->AttackSkil);
						SkillPlaySound(SKILL_SOUND_SKILL_RAGE_OF_ZECRAM1, pX, pY, pZ, FALSE);
						SetDynLight(x, y, z, 100, 0, 0, 0, 400);
					}
				}
			}
			break;
			//¼«µØÅ­ºð
		case SKILL_PLAY_ROAR:
			if (this == lpCurPlayer)
			{
				dm_SelectRange(pX, pY, pZ, Roar_Range[point - 1], FALSE);
				dm_SendRangeDamage(pX, pY, pZ, 0, 0, 0, 0, 0, AttackSkil);
			}
			break;
			// »áÐÄÒ»»÷
		case SKILL_PLAY_CONCENTRATION:
			if (point)
			{
				AssaParticle_ConcentrationEffect(this, Concentration_Time[point - 1], SKILL_CONCENTRATION);
				if (this == lpCurPlayer)
					dwConcentrationTime = dwPlayTime + Concentration_Time[point - 1] * 1000;
			}
			break;
			//¸´³ðÁ¬»÷
		case SKILL_PLAY_AVANGING_CRASH:
			if (GetAttackPoint(&x, &y, &z) == TRUE)
			{
				Pos1.x = x;
				Pos1.y = y;
				Pos1.z = z;
				if (AttackCritcal >= 0)
				{
					AssaParticle_AvangingCrash(this);
					SkillPlaySound(SKILL_SOUND_SKILL_AVANGING_CRASH, pX, pY, pZ);
				}
				else
					PlayWaponSoundDirect(pX, pY, pZ, 13);
			}
			if (this == lpCurPlayer && MotionEvent == 1 && chrAttackTarget)
			{
				x = lpCurPlayer->sCharacterData.iAttackRange;
				sCharacterData.iAttackRange += (sCharacterData.iAttackRange * A_Crash_AttackRate[point - 1]) / 100;
				cnt = dm_SendTransDamage(chrAttackTarget, cSkill.GetSkillPoint(SKILL_BRUTAL_SWING), 0, 0, 0, AttackSkil, TRUE);

				if (!cnt)
					AttackCritcal = -1;
				else
				{
					DamageExp(chrAttackTarget, cnt);
					AttackCritcal = 0;
				}
				sCharacterData.iAttackRange = x;
			}
			break;
			// ´ÌÉ±Ö®¸«
		case SKILL_PLAY_SWIFT_AXE:
			if (point)
			{
				AssaParticle_SwiftAxeEffect(this, Swift_Axe_Time[point - 1], SKILL_SWIFT_AXE);
				if (this == lpCurPlayer)
					dwSwiftAxeTime = dwPlayTime + Swift_Axe_Time[point - 1] * 1000;
			}
			break;
			//´ì¹ÇÑï»Ò
		case SKILL_PLAY_BONE_SMASH:
			if (AttackCritcal >= 0)
			{
				AssaParticle_BoneSmash1(this);
				SkillPlaySound(SKILL_SOUND_SKILL_BONE_CRASH1, pX, pY, pZ, FALSE);
			}
			else
				PlayWaponSoundDirect(pX, pY, pZ, 13);
			if (this == lpCurPlayer && MotionEvent == 1 && chrAttackTarget)
			{
				cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, AttackSkil, TRUE);

				if (!cnt)
					AttackCritcal = -1;
				else
				{
					DamageExp(chrAttackTarget, cnt);
					AttackCritcal = 0;
				}
			}
			break;
			//ÆÆ»µÖ®»÷
		case SKILL_PLAY_DESTROYER:
			if (chrAttackTarget)
			{
				if (AttackCritcal >= 0)
				{
					GetAttackPoint(&Pos2.x, &Pos2.y, &Pos2.z);
					SkillWarriorDestroyerHit(&Pos2);
					SetDynLight(Pos2.x, Pos2.y, Pos2.z, 100, 0, 0, 0, 400);
					if (MotionEvent < 3)
						SkillPlaySound(SKILL_SOUND_SKILL_AVANGING_CRASH, pX, pY, pZ);
					else
						SkillPlaySound(SKILL_SOUND_SKILL_EXPANSION2, pX, pY, pZ);
				}
				else
					PlayWaponSoundDirect(pX, pY, pZ, 13);
				if (this == lpCurPlayer && MotionEvent < 3)
				{
					cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
					if (!cnt)
						lpCurPlayer->AttackCritcal = -1;
					else
						lpCurPlayer->AttackCritcal = 0;
				}
			}
			break;
			//·è¿ñÅ­ºð
		case SKILL_PLAY_BERSERKER:
			if (point)
			{
				SkillWarriorBetserker(this, (float)Berserker_Time[point - 1]);
				AttackAnger = 200;
				if (lpCurPlayer == this)
					dwBetserkerTime = dwPlayTime + Berserker_Time[point - 1] * 1000;
			}
			break;
			//ì«·çÏ®»÷
		case SKILL_PLAY_CYCLONE_STRIKE:
			if (lpCurPlayer != this)
			{
				dm_SelectRange(pX, pY, pZ, Cyclone_Strike_Area[point - 1], TRUE, Cyclone_Strike_AttackNum[point - 1]);
				dm_AddRangeDamage(chrAttackTarget);
			}
			for (cnt = 0; cnt < dmSelected_CharCnt; cnt++)
				StartEffect(lpSelected_Char[cnt]->pX, lpSelected_Char[cnt]->pY + 16 * fONE, lpSelected_Char[cnt]->pZ, EFFECT_NORMAL_HIT1);
			break;
			//¿ñ±©Å­Õ¶
		case SKILL_PLAY_D_HIT:
			if (chrAttackTarget)
			{
				WeaponPlaySound(this);

				if (GetAttackPoint(&x, &y, &z) == TRUE)
				{
					SkillWarriorCycloneStrikeBlade(this, 1.0f, 1);
					if (MotionEvent)
					{
						switch (MotionEvent)
						{
						case 3:
							StartEffect(x, y, z, EFFECT_CRITICAL_HIT1);
							SetDynLight(x, y, z, 100, 0, 0, 0, 400, 10);
							SkillPlaySound(SKILL_SOUND_SKILL_BLANDISH2, pX, pY, pZ);
							break;
						default:
							SkillFighterDownHit(this, x, y, z);
							break;
						}
						if (lpCurPlayer == this)
						{
							cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
							if (!cnt)
								lpCurPlayer->AttackCritcal = -1;
							else
							{
								DamageExp(chrAttackTarget, cnt);
								lpCurPlayer->AttackCritcal = 0;
							}
						}
					}
				}
			}
			break;
			//¿ñÒ°³å»÷
		case SKILL_PLAY_P_DASH:
			if (chrAttackTarget && MotionEvent)
			{
				SkillPlaySound(SKILL_SOUND_SKILL_EXTINTION, pX, pY, pZ);
				sinSkillEffect_P_Dash(chrAttackTarget);
				if (lpCurPlayer == this)
				{
					cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, AttackSkil, TRUE);
					if (!cnt)
						AttackCritcal = -1;
					else
					{
						DamageExp(chrAttackTarget, cnt);
						AttackCritcal = 0;
					}
					dm_SelectRange(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, P_Dash_Area[point - 1], FALSE);
					dm_SendRangeDamage(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 0, 0, 0, 0, 0, AttackSkil);
				}
			}
			break;
			//»ØÐýÕ¶»÷
		case SKILL_PLAY_M_BLOW:
			if (chrAttackTarget && point)
			{
				WeaponPlaySound(this);

				if (GetAttackPoint(&x, &y, &z) == TRUE)
				{
					StartSkill(x, y, z, 0, 0, 0, SKILL_M_BLOW);
					SkillPlaySound(SKILL_SOUND_SKILL_SWING1, pX, pY, pZ);

					if (this == lpCurPlayer)
					{
						dm_SelectDamageCount(this, M_Blow_AttackNum[point - 1], M_Blow_Area[point - 1]);
						dm_SendRangeDamage(pX, pY, pZ, 0, 0, 0, 0, 0, AttackSkil);
					}
				}
			}
			break;
			//ÖÚÉñÖ®Å­
		case SKILL_PLAY_B_BERSERKER:
			if (point)
			{
				SkillPlaySound(SKILL_SOUND_SKILL_METAL_GOLEM, pX, pY, pZ);
				SkillBloodyBerserker(this, (float)B_Berserker_Time[point - 1]);
				AttackAnger = 200;
				if (lpCurPlayer == this)
					dwB_Berserker_Time = dwPlayTime + B_Berserker_Time[point - 1] * 1000;
			}
			break;
		}
		break;
		//»úÐµ
	case CHARACTERCLASS_Mechanician:
		switch (SkillCode)
		{
			//¼«¹â»¤¶Ü
		case SKILL_PLAY_EXTREME_SHIELD:
			if (HvLeftHand.PatTool)
			{
				if (GetToolBipPoint(&HvLeftHand, &x, &y, &z))
					StartSkill(x, y, z, 0, 0, 0, SKILL_EXTREME_SHIELD);
				if (this == lpCurPlayer)
					dwE_Shield_UseTime = dwPlayTime + E_Shield_UseTime[point - 1] * 1000;
			}
			break;
			//»úÐµÁñµ¯
		case SKILL_PLAY_MECHANIC_BOMB:
			if (chrAttackTarget)
			{
				if (point)
				{
					damage = GetRandomPos(Mechanic_Bomb_Damage[point - 1][0], Mechanic_Bomb_Damage[point - 1][1]) / 2;
					StartSkillDest(pX, pY + 30 * fONE, pZ, chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, SKILL_MECHANIC_BOMB, point);
					SkillPlaySound(SKILL_SOUND_MECHANIC_BOMB1, pX, pY, pZ);
					if (this == lpCurPlayer)
					{
						dm_SelectRange(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 80 + (point * 5), FALSE);
						dm_SendRangeDamage(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, chrAttackTarget, 0, 0, 0, 0, lpCurPlayer->AttackSkil);
					}
				}
			}
			break;
			//Áé¹â»¤Ìå
		case SKILL_PLAY_PHYSICAL_ABSORB:
			if (point)
			{
				StartSkill(pX, pY, pZ, 0, Angle.y, 0, this, SKILL_SHIELD1, point);
				if (this == lpCurPlayer)
					dwP_Absorb_UseTime = dwPlayTime + P_Absorb_UseTime[point - 1] * 1000;
			}
			break;
			// ¸ÄÁ¼×¨¼Ò
		case SKILL_PLAY_MAXIMIZE:
			if (point)
			{
				StartSkill(pX, pY, pZ, 0, Angle.y, 0, this, SKILL_SHIELD2, point);
				if (this == lpCurPlayer)
					dwAutomation_Time = dwPlayTime + Maximize_Time[point - 1] * 1000;
			}
			break;
			// Áé¹â·ÉÑï
		case SKILL_PLAY_AUTOMATION:
			if (point)
			{
				StartSkill(pX, pY, pZ, 0, Angle.y, 0, this, SKILL_SHIELD2, point);
				if (this == lpCurPlayer)
					dwAutomation_Time = dwPlayTime + Automation_Time[point - 1] * 1000;
			}
			break;
			// //½ðÊôÖØ¼×
		case SKILL_PLAY_METAL_ARMOR:
			if (point)
			{
				AssaParticle_MetalArmorEffect(this, Metal_Armor_Time[point - 1]);
				if (this == lpCurPlayer)
					dwMetal_Armor_Time = dwPlayTime + Metal_Armor_Time[point - 1] * 1000;
			}
			break;
			//ÆÆËé¾Þ»÷
		case SKILL_PLAY_GREAT_SMASH:
			if (GetAttackPoint(&x, &y, &z) == TRUE)
			{
				if (dwActionItemCode)
				{
					StartSkill(x, y, z, 0, Angle.y, 0, SKILL_GREAT_SMASH);
					SkillPlaySound(SKILL_SOUND_SKILL_SWING1, pX, pY, pZ);
				}
			}
			break;
			//»ð»¨µç³¡
		case SKILL_PLAY_SPARK:
			if (chrAttackTarget)
			{
				if (point)
				{
					StartSkillDest(pX, pY + 24 * fONE, pZ, chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ, SKILL_SPARK, point);
					if (this == lpCurPlayer)
					{
						dm_SelectRange(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 80 + (point * 5), FALSE);
						dm_SendRangeDamage(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 0, 0, 0, 0, 0, lpCurPlayer->AttackSkil);
					}
					SkillPlaySound(SKILL_SOUND_SKILL_SPARK2, pX, pY, pZ);
				}
			}
			break;
			//ÐÇ¹âÃð¾ø
		case SKILL_PLAY_GRAND_SMASH:
			if (dwActionItemCode && AttackCritcal >= 0)
			{
				AssaParticle_GrandSmash(this);
				SkillPlaySound(SKILL_SOUND_SKILL_SWING2, pX, pY, pZ);
			}
			else
				PlayWaponSoundDirect(pX, pY, pZ, 13);
			if (this == lpCurPlayer && chrAttackTarget && MotionEvent == 1)
			{
				temp = sCharacterData.iAttackRange;
				sCharacterData.iAttackRange += Grand_Smash_AttackRate[point - 1];
				cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
				sCharacterData.iAttackRange = temp;
				if (!cnt)
					AttackCritcal = -1;
				else
					AttackCritcal = 0;
			}
			break;
			//·ÀÓùµç²¨
		case SKILL_PLAY_SPARK_SHIELD:
			if (HvLeftHand.PatTool)
			{
				AssaParticle_SparkShieldEffect(this, Spark_Shield_Time[point - 1]);
				SkillPlaySound(SKILL_SOUND_SKILL_SPARK3, pX, pY, pZ);
				if (this == lpCurPlayer)
					dwSpark_Shield_Time = dwPlayTime + Spark_Shield_Time[point - 1] * 1000;
			}
			break;
			//À×öª³å»÷
		case SKILL_PLAY_IMPULSION:
			if (point && chrAttackTarget)
			{
				if (GetAttackPoint(&Pos2.x, &Pos2.y, &Pos2.z) == TRUE)
					SkillImpulsionLightHit(&Pos2);
				if (lpCurPlayer != this)
					dm_SelectRange(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, Impulsion_Range[point - 1], TRUE, Impulsion_LightingNum[point - 1]);
				else
				{
					if (MotionEvent == 1)
						dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, lpCurPlayer->AttackSkil, FALSE);
				}
				SkillMetalionImpulsionHit(lpSelected_Char, dmSelected_CharCnt);

				if (dmSelected_CharCnt)
					SkillPlaySound(SKILL_SOUND_SKILL_IMPULSION, pX, pY, pZ);
				SkillPlaySound(SKILL_SOUND_SKILL_CHAIN_LANCE2, pX, pY, pZ);
			}
			break;
			//ÍþÉåÅ­ºð
		case SKILL_PLAY_COMPULSION:
			if (point)
				SkillMetalionCompulsion(this);
			break;
			//´ÅÐÔÇòÌå
		case SKILL_PLAY_MAGNETIC_SPHERE:
			if (point)
			{
				SkillMetalionSphereEffect(this, (float)Magnetic_Sphere_Time[point - 1], (float)Magnetic_Sphere_AttackDelay[point - 1]);
				SkillPlaySound(SKILL_SOUND_SKILL_SPARK3, pX, pY, pZ);
				if (this == lpCurPlayer)
					dwMagnetic_Sphere_Time = dwPlayTime + Magnetic_Sphere_Time[point - 1] * 1000;
			}
			break;
			//ÖÕ¼«»úÐµ
		case SKILL_PLAY_METAL_GOLEM:
			if (point)
				SkillMetalionGolem(this);
			break;
			// Åùö¨Ðý·ç
		case SKILL_PLAY_LANDMINNING:
			if (point)
			{
				if (lpCurPlayer == this)
				{
					dm_SelectRange(pX, pY, pZ, Landminning_Area[point - 1], FALSE);
					dm_SendRangeDamage(pX, pY, pZ, 0, 0, 0, 0, 0, AttackSkil);
				}
			}
			break;
			// ¿ìËÙ´ò»÷
		case SKILL_PLAY_H_SONIC:
			if (point)
			{
				SkillPlaySound(SKILL_SOUND_SKILL_BLANDISH2, pX, pY + 1000, pZ);
				AssaParticle_HyperSonic(this, H_Sonic_Time[point - 1]);
				if (this == lpCurPlayer)
					dwH_Sonic_Time = dwPlayTime + H_Sonic_Time[point - 1] * 1000;
			}
			break;
			// ¾¿¼«Ö®ÈÐ
		case SKILL_PLAY_R_SMASH:
			if (chrAttackTarget && GetAttackPoint(&x, &y, &z) == TRUE)
			{
				if (MotionEvent < 4)
					SkillPlaySound(SKILL_SOUND_SKILL_DVINE_PIERCING, pX, pY + 1000, pZ);
				else
					SkillPlaySound(SKILL_SOUND_SKILL_ENERGY_SHIELD, pX, pY + 1000, pZ);

				AssaParticle_RollingSmashHit(x, y, z);

				switch (MotionEvent)
				{
				case 3:
					sinEffect_RollingSmash(chrAttackTarget, chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ);
					break;
				case 4:
					AssaParticle_RollingSmashDown(chrAttackTarget->pX, chrAttackTarget->pY + 2000, chrAttackTarget->pZ);
					break;
				}
				if (lpCurPlayer == this)
				{
					cnt = cSkill.GetSkillPoint(SKILL_GRAND_SMASH);

					temp = sCharacterData.iAttackRange;

					if (cnt > 0)
						sCharacterData.iAttackRange += Grand_Smash_AttackRate[cnt];

					switch (MotionEvent)
					{
					case 3:
						dm_SelectRange(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 60, FALSE);
						dm_SendRangeDamage(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 0, 0, 0, 3, 0, AttackSkil);
						break;
					case 4:
						dm_SelectRange(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 100, FALSE);
						dm_SendRangeDamage(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 0, 0, 0, 4, 0, AttackSkil);
						break;
					default:
						cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, AttackSkil, TRUE);
						if (cnt == FALSE)
							AttackCritcal = -1;
						else
						{
							DamageExp(chrAttackTarget, cnt);
							AttackCritcal = 0;
						}
						break;
					}

					sCharacterData.iAttackRange = temp;
				}
			}
			break;
			// Õ½Éñ×£¸£
		case SKILL_PLAY_P_ENHENCE:
			if (point)
			{
				AssaParticle_EnhenceEffect(this, P_Enhence_Time[point - 1]);
				if (this == lpCurPlayer)
				{
					SendPartySkillToServer(SKILL_PLAY_P_ENHENCE, point, 200, 0, 0, 0, 0);
					dwP_Enhence_Time = dwPlayTime + P_Enhence_Time[point - 1] * 1000;
				}
			}
			break;
		}
		break;
		//¹­ÊÖ
	case CHARACTERCLASS_Archer:
		switch (SkillCode)
		{
			//¼²·çÖ®¼ý
		case SKILL_PLAY_WIND_ARROW:
			if (chrAttackTarget)
			{
				GetAttackPoint(&x, &y, &z);
				StartSkillDest(x, y, z, chrAttackTarget->pX, chrAttackTarget->pY + (24 * fONE), chrAttackTarget->pZ, SKILL_WIND_ARROW);
				SkillPlaySound(SKILL_SOUND_WIND_ARROW, pX, pY, pZ);
			}
			break;
			//¶áÃüÖ®¼ý
		case SKILL_PLAY_PERFECT_AIM:
			if (chrAttackTarget)
			{
				GetAttackPoint(&x, &y, &z);
				StartSkillDest(x, y, z, chrAttackTarget->pX, chrAttackTarget->pY + (24 * fONE), chrAttackTarget->pZ, SKILL_PERFECT_AIM);
				SkillPlaySound(SKILL_SOUND_PERFECT_AIM, pX, pY, pZ);
			}
			break;
			//Áé»êÖ®Ó¥
		case SKILL_PLAY_FALCON:
			if (point)
			{
				if (lpCurPlayer == this)
					dwFalcon_Time = dwPlayTime + Falcon_Time[point - 1] * 1000;
			}
			break;
			//»Æ½ðÁÔÓ¥
		case SKILL_PLAY_GOLDEN_FALCON:
			if (point)
			{
				if (lpCurPlayer == this)
					dwGolden_Falcon_Time = dwPlayTime + Golden_Falcon_Time[point - 1] * 1000;
			}
			break;
			//¿ñ±©»ð¼ý
		case SKILL_PLAY_ARROWOF_RAGE:
			if (chrAttackTarget && GetAttackPoint(&x, &y, &z) == TRUE)
			{
				StartSkillDest(x, y, z, chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, SKILL_ARROW_OF_RAGE, point);
				if (this == lpCurPlayer && chrAttackTarget)
				{
					dm_SelectRange(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, A_Rage_Area[point - 1], FALSE);
					dm_SendRangeDamage(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 0, 0, 0, 0, 0, lpCurPlayer->AttackSkil);
				}
				SkillPlaySound(SKILL_SOUND_WIND_ARROW, pX, pY, pZ);
			}
			break;
			//Ñ©±ÀÖ®¼ý
		case SKILL_PLAY_AVALANCHE:
			if (chrAttackTarget && GetAttackPoint(&x, &y, &z) == TRUE)
			{
				if (AttackCritcal >= 0)
				{
					StartSkillDest(x, y, z, chrAttackTarget->pX, chrAttackTarget->pY + (24 * fONE), chrAttackTarget->pZ, SKILL_AVALANCHE);
					switch (rand() % 3)
					{
					case 0:
						SkillPlaySound(SKILL_SOUND_SKILL_AVALANCHE1, pX, pY, pZ);
						break;
					case 1:
						SkillPlaySound(SKILL_SOUND_SKILL_AVALANCHE2, pX, pY, pZ);
						break;
					case 2:
						SkillPlaySound(SKILL_SOUND_SKILL_AVALANCHE3, pX, pY, pZ);
						break;
					}
				}
				else
					WeaponPlaySound(this);
			}
			break;
			//ÔªËØ¹¥»÷
		case SKILL_PLAY_ELEMENTAL_SHOT:
			if (chrAttackTarget && GetAttackPoint(&x, &y, &z) == TRUE)
			{
				if (AttackCritcal >= 0)
				{
					Pos1.x = x;
					Pos1.y = y;
					Pos1.z = z;
					Pos2.x = chrAttackTarget->pX;
					Pos2.y = chrAttackTarget->pY + (24 * fONE);
					Pos2.z = chrAttackTarget->pZ;
					if (AttackCritcal >= 0)
					{
						switch (param)
						{
						case 0:
							AssaParticle_ElementalShotFire(&Pos1, &Pos2);
							break;
						case 1:
							AssaParticle_ElementalShotLighting(&Pos1, &Pos2);
							break;
						}
						SkillPlaySound(SKILL_SOUND_SKILL_ELEMENTAL_SHOT, pX, pY, pZ);
					}
				}
			}
			break;
			//±¬ÁÑÖ®¼ý
		case SKILL_PLAY_BOMB_SHOT:
			if (chrAttackTarget && GetAttackPoint(&x, &y, &z) == TRUE)
			{
				if (AttackCritcal >= 0)
				{
					Pos1.x = x;
					Pos1.y = y;
					Pos1.z = z;
					Pos2.x = chrAttackTarget->pX;
					Pos2.y = chrAttackTarget->pY + (24 * fONE);
					Pos2.z = chrAttackTarget->pZ;
					AssaParticle_BombShot(&Pos1, &Pos2);
					SkillPlaySound(SKILL_SOUND_SKILL_BOMB_SHOT1, pX, pY, pZ);
				}
			}
			break;
			//¹ß´©Ö®¼ý
		case SKILL_PLAY_PERFORATION:
			if (chrAttackTarget && GetAttackPoint(&x, &y, &z) == TRUE)
			{
				if (AttackCritcal >= 0)
				{
					Pos1.x = x;
					Pos1.y = y;
					Pos1.z = z;
					Pos2.x = chrAttackTarget->pX;
					Pos2.y = chrAttackTarget->pY + (24 * fONE);
					Pos2.z = chrAttackTarget->pZ;
					AssaParticle_Perforation(&Pos1, &Pos2);
					SkillPlaySound(SKILL_SOUND_SKILL_PERFORATION, pX, pY, pZ);
					rect.left = -40;
					rect.right = 40;
					rect.top = 0;
					rect.bottom = 240;
					rect.bottom += 20;
					rect.bottom += 20;
					dm_SelectRangeBox(this, &rect, FALSE);
					for (cnt = 0; cnt < dmSelected_CharCnt; cnt++)
					{
						if (lpSelected_Char[cnt])
							AssaParticle_PerforationHit(lpSelected_Char[cnt], this, 0.5f);
					}
				}
			}
			break;
			//ÕÙ»½Ñ©ÀÇ
		case SKILL_PLAY_RECALL_WOLVERIN:
			if (point)
			{
				SkillPlaySound(SKILL_SOUND_SKILL_RECALL_WOLVERIN, pX, pY, pZ);
				if (lpCurPlayer == this)
					SendProcessSKillToServer(SKILL_PLAY_RECALL_WOLVERIN, point, 0, 0);
			}
			break;
			//ç³»Ë¾øÑ×
		case SKILL_PLAY_PHOENIX_SHOT:
			if (chrAttackTarget && point)
			{
				cnt = iFrame - psModelAnimation->StartFrame * 160;
				if (psModelAnimation->EventFrame[1] <= (DWORD)cnt)
				{
					auto sPosition = GetMoveLocation(0, 24 * fONE, 24 * fONE, 0, Angle.y, 0);
					Pos1.x = pX + sPosition.iX;
					Pos1.y = pY + sPosition.iY;
					Pos1.z = pZ + sPosition.iZ;
					Pos2.x = chrAttackTarget->pX;
					Pos2.y = chrAttackTarget->pY + 24 * fONE;
					Pos2.z = chrAttackTarget->pZ;
					SkillSagittarionPhoneixShot(this, &Pos1, &Pos2);
					if (this == lpCurPlayer)
					{
						SkillStopSound(SKILL_SOUND_SKILL_CHARGING);
						if (ChargingFlag != 0)
							dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, lpCurPlayer->AttackSkil, FALSE);
						else
						{
							rect.left = -50;
							rect.right = 50;
							rect.top = 0;
							rect.bottom = 300;
							rect.bottom += 20;
							rect.bottom += 20;
							dm_SelectRangeBox(lpCurPlayer, &rect, FALSE);
							dm_SendRangeDamage(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, 0, 0, lpCurPlayer->AttackSkil);
						}
						lpCurPlayer->MotionLoopSpeed = GetAttackSpeedFrame(7);
						lpCurPlayer->MotionLoop = 1;
						MouseButton[1] = 0;
						CancelAttack();
					}
					SkillPlaySound(SKILL_SOUND_SKILL_PHOENIX_SHOT, pX, pY, pZ);
				}
				else
				{
					if (this == lpCurPlayer)
						ChargingFlag = 0;
				}
			}
			break;
			//×ÔÈ»Ö®¹â
		case SKILL_PLAY_FORCE_OF_NATURE:
			if (point)
				SkillSagittarionForceOfNature1(this, (float)Force_Of_Nature_Time[point - 1]);
			break;
			//»ØÐýÖ®Îè
		case SKILL_PLAY_E_SHOT:
			if (point && chrAttackTarget)
			{
				switch (MotionEvent)
				{
				case 1:
					Pos1.x = pX;
					Pos1.y = pY + 2000;
					Pos1.z = pZ;
					AssaParticle_ChainLance(&Pos1);
					SkillPlaySound(SKILL_SOUND_SKILL_EXTREM_RAGE1, pX, pY, pZ);
					if (lpCurPlayer == this)
					{
						cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, AttackSkil, TRUE);

						if (cnt > 0)
						{
							AttackCritcal = 0;
							DamageExp(chrAttackTarget, cnt);
							if (AttackExp)
								AttackExp = 0;
						}
						else
							AttackCritcal = -1;
					}
					break;
				case 2:
					if (GetAttackPoint(&x, &y, &z) == TRUE)
					{
						StartSkillDest(x, y, z, chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, SKILL_AVALANCHE);
						SkillPlaySound(SKILL_SOUND_PERFECT_AIM, pX, pY, pZ);

						if (lpCurPlayer == this)
						{
							dm_SelectRange(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 140, FALSE);
							dm_SendRangeDamage(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 0, 0, 0, 0, 0, AttackSkil);
						}
					}
					break;
				}
			}
			break;
			//Ðþ¹âÖ®Îè
		case SKILL_PLAY_S_ROPE:
			if (point && chrAttackTarget && MotionEvent)
			{
				if (GetAttackPoint(&x, &y, &z) == TRUE)
				{
					Pos1.x = x;
					Pos1.y = y;
					Pos1.z = z;

					Pos2.x = chrAttackTarget->pX;
					Pos2.y = chrAttackTarget->pY;
					Pos2.z = chrAttackTarget->pZ;

					AssaParticle_S_Rope(&Pos1, &Pos2);
					SkillPlaySound(SKILL_SOUND_SKILL_DIVINELIGHTNING2, pX, pY, pZ);

					if (lpCurPlayer == this)
					{
						cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, AttackSkil, TRUE);

						if (cnt > 0)
						{
							AttackCritcal = 0;
							DamageExp(chrAttackTarget, cnt);
							if (AttackExp)
								AttackExp = 0;
						}
						else
							AttackCritcal = -1;

						dm_SelectRange(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 80, FALSE);
						dm_SendRangeDamage(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 0, 0, 0, 0, 0, AttackSkil);
					}
				}
			}
			break;
			//ì«·çÖ®¼ý
		case SKILL_PLAY_N_SPLASH:
			if (point && chrAttackTarget && MotionEvent)
			{
				if (GetAttackPoint(&x, &y, &z) == TRUE)
				{
					StartSkillDest(x, y, z, pX, pY + fONE * 24, pZ, SKILL_AVALANCHE);
					SkillPlaySound(SKILL_SOUND_PERFECT_AIM, pX, pY, pZ);
					sinEffect_Splash(this);
					SkillPlaySound(SKILL_SOUND_SKILL_FIRE_ELEMENTAL, pX, pY, pZ);

					if (lpCurPlayer == this)
					{
						rect.left = -80;
						rect.right = 80;
						rect.top = 0;
						rect.bottom = N_Splash_Range[point - 1];
						rect.bottom += 20;
						rect.bottom += 20;
						dm_SelectRangeBox(this, &rect, FALSE);
						dm_SendRangeDamage(pX, pY, pZ, 0, 0, 0, 0, 0, AttackSkil);
					}
				}
			}
			break;
			//º®±ùÖ®¼ý
		case SKILL_PLAY_C_TRAP:
			if (point && chrAttackTarget && MotionEvent)
			{
				if (GetAttackPoint(&x, &y, &z) == TRUE)
				{
					SkillPlaySound(SKILL_SOUND_PERFECT_AIM, pX, pY, pZ);
					StartSkillDest(x, y, z, chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, SKILL_C_TRAP, point);
					SkillPlaySound(SKILL_SOUND_SKILL_BLANDISH1, pX, pY, pZ);

					if (lpCurPlayer == this)
					{
						dm_SelectRange(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, C_Trap_Area[point - 1], FALSE);
						dm_SendRangeDamage(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 0, 0, 0, 0, 0, AttackSkil);
					}
				}
			}
			break;
		}
		break;
		//Ç¹±ø
	case CHARACTERCLASS_Pikeman:
		switch (SkillCode)
		{
			//Áú¾íÇ¹·ç
		case SKILL_PLAY_PIKEWIND:
			if (point)
			{
				StartSkill(pX, pY, pZ, 0, 0, 0, SKILL_PIKE_WIND, point);
				SkillPlaySound(SKILL_SOUND_PIKE_WIND, pX, pY, pZ);
			}
			break;
			//ÖÂÃü´ò»÷
		case SKILL_PLAY_CRITICAL_HIT:
			return FALSE;
			//Åùö¨Ò»»÷
		case SKILL_PLAY_JUMPING_CRASH:
			if (AttackSkil >= 0)
				SkillPlaySound(SKILL_SOUND_JUMPING_CRASH2, pX, pY, pZ);
			return FALSE;
			//´óµØÖ®Ç¹
		case SKILL_PLAY_GROUND_PIKE:
			if (point)
			{
				auto sPosition = GetMoveLocation(0, 0, 32 * fONE, 0, Angle.y, 0);
				StartSkill(pX + sPosition.iX, pY, pZ + sPosition.iZ, 0, Angle.y, 0, SKILL_GROUND_PIKE, point);
				SetDynLight(pX, pY, pZ, 0, 0, 100, 0, 700);
				SkillPlaySound(SKILL_SOUND_SKILL_GROUND_PIKE, pX, pY, pZ);
			}
			break;
			//ÎÞÏÞÁ¦Ç¹
		case SKILL_PLAY_EXPANSION:
			SkillPlaySound(SKILL_SOUND_SKILL_EXPANSION2, pX, pY, pZ);
			if (GetAttackPoint(&x, &y, &z) == TRUE)
			{
				if (dwActionItemCode)
				{
					StartSkill(x, y, z, 0, Angle.y, 0, SKILL_GREAT_SMASH);
					SetDynLight(x, y, z, 100, 0, 0, 0, 400);
				}
			}
			return FALSE;
			//Ç¹Ö®ì«·ç
		case SKILL_PLAY_TORNADO:
			if (chrAttackTarget)
			{
				x = (pX - chrAttackTarget->pX) >> FLOATNS;
				z = (pZ - chrAttackTarget->pZ) >> FLOATNS;
				if ((x*x + z * z) < (50 * 50))
				{
					y = GetRadian2D(pX, pZ, chrAttackTarget->pX, chrAttackTarget->pZ);
					auto sPosition = GetMoveLocation(0, 0, 50 * fONE, 0, y, 0);
					x = pX + sPosition.iX;
					z = pZ + sPosition.iZ;
					y = chrAttackTarget->pY;
					StartSkillDest(pX, pY, pZ, x, y, z, SKILL_TORNADO, point);
				}
				else
					StartSkillDest(pX, pY, pZ, chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, SKILL_TORNADO, point);

				SkillPlaySound(SKILL_SOUND_SKILL_TORNADO1, pX, pY, pZ);
			}
			break;
			//ÁéÉß±êÇ¹
		case SKILL_PLAY_VENOM_SPEAR:
			if (this == lpCurPlayer)
			{
				dm_SelectDamageCount(this, VenomSpear_Num[point - 1], VenomSpear_Range[point - 1]);
				dm_SendRangeDamage(pX, pY, pZ, 0, 0, 0, 0, 0, AttackSkil);
			}
			SkillPlaySound(SKILL_SOUND_SKILL_VENOM_SPEAR1, pX, pY, pZ);
			if (SkillPlay_VenomSpear_Effect(this, point) > 0)
				SkillPlaySound(SKILL_SOUND_SKILL_VENOM_SPEAR2, pX, pY, pZ);
			break;
			//Òþ°µÖ®Êõ
		case SKILL_PLAY_VANISH:
			SkillPlaySound(SKILL_SOUND_SKILL_VANISH2, pX, pY, pZ);
			if (lpCurPlayer == this)
			{
				PlayVanish = Vanish_Time[point - 1] * 70;
				PlayVague = 0;
				SendProcessSKillToServer(SKILL_PLAY_VANISH, point, 0, 0);
			}
			break;
			//Á´ÆïÖ®Ç¹
		case SKILL_PLAY_CHAIN_LANCE:
			if (chrAttackTarget && GetAttackPoint(&x, &y, &z) == TRUE)
			{
				Pos1.x = x;
				Pos1.y = y;
				Pos1.z = z;
				if (lpCurPlayer->AttackCritcal >= 0)
				{
					AssaParticle_ChainLance(&Pos1);
					switch (MotionEvent)
					{
					case 1:
						SkillPlaySound(SKILL_SOUND_SKILL_CHAIN_LANCE1, pX, pY, pZ);
						break;
					case 2:
						SkillPlaySound(SKILL_SOUND_SKILL_CHAIN_LANCE2, pX, pY, pZ);
						break;
					case 3:
						SkillPlaySound(SKILL_SOUND_SKILL_CHAIN_LANCE3, pX, pY, pZ);
						break;
					}
				}
				else
					PlayWaponSoundDirect(pX, pY, pZ, 13);
			}
			if (this == lpCurPlayer && MotionEvent < 3 && chrAttackTarget)
			{
				cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, AttackSkil, TRUE);
				if (!cnt)
					lpCurPlayer->AttackCritcal = -1;
				else
					lpCurPlayer->AttackCritcal = 0;
			}
			break;
			//°µÉ±Ö®ÑÛ
		case SKILL_PLAY_ASSASSIN_EYE:
			if (point && chrAttackTarget)
				SkillLancelotAssassinEye(chrAttackTarget, (float)Assassin_Eye_Time[point - 1]);
			break;
			//×ª»»´ò»÷
		case SKILL_PLAY_CHARGING_STRIKE:
			if (chrAttackTarget && point)
			{
				cnt = iFrame - psModelAnimation->StartFrame * 160;
				if (psModelAnimation->EventFrame[1] <= (DWORD)cnt)
				{
					SkillLancelotChargingStrike(this);
					if (psModelAnimation->EventFrame[2] <= (DWORD)cnt && GetAttackPoint(&x, &y, &z) == TRUE)
					{
						if (AttackCritcal >= 0)
						{
							StartSkill(x, y, z, 0, 0, 0, SKILL_TRIPLE_IMPACT);
							SetDynLight(x, y, z, 100, 0, 0, 0, 400);
							switch (MotionEvent)
							{
							case 2:
								SkillPlaySound(SKILL_SOUND_SKILL_CHAIN_LANCE2, pX, pY, pZ);
								break;
							case 3:
								SkillPlaySound(SKILL_SOUND_SKILL_AVANGING_CRASH, pX, pY, pZ);
								break;
							case 4:
							case 5:
								SkillPlaySound(SKILL_SOUND_SKILL_CHARGING_STRIKE, pX, pY, pZ);
								break;
							}
						}
						else
							PlayWaponSoundDirect(pX, pY, pZ, 13);
					}
					if (this == lpCurPlayer && SkillEventDamageCount < 3)
					{
						if (SkillEventDamageCount == 0)
							SkillStopSound(SKILL_SOUND_SKILL_CHARGING);
						temp = dm_SendTransDamage(chrAttackTarget, ChargingFlag, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
						if (!temp)
							AttackCritcal = -1;
						else
							AttackCritcal = 0;
						SkillEventDamageCount++;
						MotionLoopSpeed = GetAttackSpeedFrame(7);
						MouseButton[1] = 0;
						CancelAttack();
					}
				}
				else
				{
					if (this == lpCurPlayer)
						ChargingFlag = 0;
				}
				cnt = (psModelAnimation->EventFrame[3] / 160) - psModelAnimation->StartFrame;
				dwEventFrameExt[0] = (psModelAnimation->StartFrame + 140) * 160;
			}
			break;
			//Ó°ÒþÖ®¶Ý
		case SKILL_PLAY_VAGUE:
			if (lpCurPlayer == this)
			{
				PlayVanish = Vague_Time[point - 1] * 70;
				PlayVague = point;
				SendProcessSKillToServer(SKILL_PLAY_VAGUE, point, 0, 0);
			}
			break;
			//ÓîÖæ»ÃÓ°
		case SKILL_PLAY_SHADOW_MASTER:
			dwEventFrameExt[0] = (793 - 710 + psModelAnimation->StartFrame) * 160;
			dwEventFrameExt[1] = (794 - 710 + psModelAnimation->StartFrame) * 160;
			dwEventFrameExt[2] = (795 - 710 + psModelAnimation->StartFrame) * 160;

			if (chrAttackTarget && point)
			{
				for (cnt = 0; cnt < 7; cnt++)
				{
					if (SkillShadowMasterEvent[Shadow_Master_ShadowNum[point - 1]][cnt] == MotionEvent)
					{
						if (AttackCritcal >= 0)
						{
							if (GetAttackPoint(&x, &y, &z) == TRUE)
							{
								StartSkill(x, y, z, 0, 0, 0, SKILL_TRIPLE_IMPACT);
								SetDynLight(x, y, z, 100, 0, 0, 0, 400);
								switch (rand() % 3)
								{
								case 0:
									SkillPlaySound(SKILL_SOUND_SKILL_SHADOW_STRIKE1, pX, pY, pZ);
									break;
								case 1:
									SkillPlaySound(SKILL_SOUND_SKILL_SHADOW_STRIKE2, pX, pY, pZ);
									break;
								case 2:
									SkillPlaySound(SKILL_SOUND_SKILL_SHADOW_STRIKE3, pX, pY, pZ);
									break;
								}
							}
							AttackCritcal = 1;
						}
						else
							PlayWaponSoundDirect(pX, pY, pZ, 13);
						if (lpCurPlayer == this && (SkillEventDamageCount + 1) < Shadow_Master_ShadowNum[point - 1])
						{
							x = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
							if (!x)
								lpCurPlayer->AttackCritcal = -1;
							else
								lpCurPlayer->AttackCritcal = 0;
							SkillEventDamageCount++;
						}
						break;
					}
				}
			}
			break;
			//»ØÐý´ò»÷
		case SKILL_PLAY_D_REAPER:
			if (chrAttackTarget && GetAttackPoint(&x, &y, &z) == TRUE)
			{
				Pos1.x = x;
				Pos1.y = y;
				Pos1.z = z;

				if (AttackCritcal >= 0)
				{
					AssaParticle_Reaper(&Pos1);

					if (MotionEvent == 1)
					{
						StartEffect(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, EFFECT_CRITICAL_HIT1);
						SkillPlaySound(SKILL_SOUND_ARROW_HIT1, pX, pY, pZ);
					}
					SkillPlaySound(SKILL_SOUND_SKILL_AVANGING_CRASH, pX, pY, pZ);
				}
				else
					PlayWaponSoundDirect(pX, pY, pZ, 13);

				if (this == lpCurPlayer)
				{
					cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, AttackSkil, TRUE);
					if (!cnt)
						lpCurPlayer->AttackCritcal = -1;
					else
						lpCurPlayer->AttackCritcal = 0;
				}
			}
			break;
			//µØÏ®ÆæÇ¹
		case SKILL_PLAY_F_SPEAR:
			if (chrAttackTarget)
			{
				if (MotionEvent)
				{
					if (SkillPlay_Spear_Effect(chrAttackTarget, point) > 0)
						SkillPlaySound(SKILL_SOUND_SKILL_VENOM_SPEAR2, pX, pY, pZ);
				}
				SkillPlaySound(SKILL_SOUND_SKILL_VENOM_SPEAR1, pX, pY, pZ);
				if (this == lpCurPlayer)
				{
					dm_SelectDamageCount(this, F_Spear_Num[point - 1], F_Spear_Area[point - 1]);
					dm_SendRangeDamage(pX, pY, pZ, 0, 0, 0, 0, 0, AttackSkil);
				}
			}
			break;
			//Ç±ÄÜ¼¤·¢
		case SKILL_PLAY_AMPLIFIED:
			if (point)
			{
				StartSkill(pX, pY, pZ, 0, Angle.y, 0, this, SKILL_SHIELD1, point);
				SkillPlaySound(SKILL_SOUND_SKILL_EXTINTION, pX, pY, pZ);
				if (this == lpCurPlayer)
				{
					SendProcessSKillToServer(SKILL_PLAY_AMPLIFIED, point, 0, 0);
					dwAmplified_Time = dwPlayTime + Amplified_Time[point - 1] * 1000;
				}
			}
			break;
			//Ðý·çÖ®Ç¹
		case SKILL_PLAY_SS_ATTACK:
			if (chrAttackTarget && GetAttackPoint(&Pos1.x, &Pos1.y, &Pos1.z) == TRUE)
			{
				if (AttackCritcal >= 0)
				{
					if (MotionEvent == 1)
					{
						SkillWarriorDestroyerHit(&Pos1);
						SetDynLight(Pos1.x, Pos1.y, Pos1.z, 100, 0, 0, 0, 400);
						SkillPlaySound(SKILL_SOUND_SKILL_AVANGING_CRASH, pX, pY, pZ);
					}
					else
					{
						StartSkill(chrAttackTarget->pX, chrAttackTarget->pY + fONE * 22, chrAttackTarget->pZ, 0, 0, 0, SKILL_TRIPLE_IMPACT);
						SetDynLight(Pos1.x, Pos1.y + fONE * 22, Pos1.z, 100, 0, 0, 0, 400);
						SkillPlaySound(SKILL_SOUND_SKILL_EXPANSION2, pX, pY, pZ);
					}
				}
				else
					PlayWaponSoundDirect(pX, pY, pZ, 13);

				if (this == lpCurPlayer && MotionEvent < 3)
				{
					cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, AttackSkil, TRUE);
					if (!cnt)
						lpCurPlayer->AttackCritcal = -1;
					else
						lpCurPlayer->AttackCritcal = 0;

					dm_SelectRange(pX, pY, pZ, 100, FALSE);
					dm_SendRangeDamage(pX, pY, pZ, 0, 0, 0, 0, 0, AttackSkil);
				}
			}
			break;
		}
		break;
		//Ä§Ç¹
	case CHARACTERCLASS_Atalanta:
		switch (SkillCode)
		{
			//ÃÀ¶ÅÉ¯¶Ü
		case SKILL_PLAY_SHIELD_STRIKE:
			SkillPlaySound(SKILL_SOUND_SKILL_SHIELDSTRIKE, pX, pY, pZ);
			break;
			//¾«ÉñÖ®Ç¹
		case SKILL_PLAY_VIGOR_SPEAR:
			if (chrAttackTarget && GetAttackPoint(&x, &y, &z) == TRUE)
			{
				sinEffect_VigorSpear(this, chrAttackTarget);
				SkillPlaySound(SKILL_SOUND_SKILL_VIGORSPEAR, pX, pY, pZ);
			}
			break;
			//º¬É³ÉäÓ°
		case SKILL_PLAY_FARINA:
			if (chrAttackTarget && AttackCritcal >= 0)
				SkillPlaySound(SKILL_SOUND_SKILL_FARINA, pX, pY, pZ);
			return FALSE;
			// ×·Ãü¾¢·ç
		case SKILL_PLAY_WINDY:
			if (point)
			{
				AssaParticle_Windy(this, Windy_Time[point - 1]);
				if (lpCurPlayer == this)
					dwWindy_Time = dwPlayTime + Windy_Time[point - 1] * 1000;
			}
			break;
			//ÂÝÐý·É±ê
		case SKILL_PLAY_TWIST_JAVELIN:
			if (chrAttackTarget && AttackCritcal >= 0 && GetAttackPoint(&x, &y, &z) == TRUE)
			{
				Pos1.x = x;
				Pos1.y = y;
				Pos1.z = z;
				Pos2.x = chrAttackTarget->pX;
				Pos2.y = chrAttackTarget->pY + 28 * fONE;
				Pos2.z = chrAttackTarget->pZ;
				AssaParticle_TwistJavelinShot(&Pos1, &Pos2);
				SkillPlaySound(SKILL_SOUND_SKILL_TWISTJAVELIN, pX, pY, pZ);
			}
			return FALSE;
			//Áé»êÍÌÊÉ
		case SKILL_PLAY_SOUL_SUCKER:
			rect.left = -30;
			rect.right = 30;
			rect.top = 0;
			rect.bottom = 200;
			if (Skil_RangeBoxEffect(this, &rect, SKILL_PLAY_SOUL_SUCKER, 0) > 0)
				SkillPlaySound(SKILL_SOUND_SKILL_SOULSUCKER2, pX, pY, pZ);
			else
				SkillPlaySound(SKILL_SOUND_SKILL_SHIELDSTRIKE, pX, pY, pZ);
			break;
			//»ðÑæÁÒÇ¹
		case SKILL_PLAY_FIRE_JAVELIN:
			if (chrAttackTarget && AttackCritcal >= 0 && GetAttackPoint(&x, &y, &z) == TRUE)
			{
				Pos1.x = x;
				Pos1.y = y;
				Pos1.z = z;
				Pos2.x = chrAttackTarget->pX;
				Pos2.y = chrAttackTarget->pY + 28 * fONE;
				Pos2.z = chrAttackTarget->pZ;
				AssaParticle_FireJavelin(&Pos1, &Pos2);
				SkillPlaySound(SKILL_SOUND_SKILL_FIREJAVELIN, pX, pY, pZ);
			}
			return FALSE;
			//×··çÖ®Ç¹
		case SKILL_PLAY_SPLIT_JAVELIN:
			if (chrAttackTarget && AttackCritcal >= 0 && GetAttackPoint(&x, &y, &z) == TRUE)
				SkillPlaySound(SKILL_SOUND_SKILL_SPLIT_JAVELIN2, pX, pY, pZ);
			break;
			//Õ½ÀõÅØÏø
		case SKILL_PLAY_TRIUMPH_OF_VALHALLA:
			if (chrAttackTarget)
			{
				if (chrAttackTarget->sCharacterData.iType == CHARACTERTYPE_Player)
				{
					AssaParticle_TriumphOfValhallaMember(this, chrAttackTarget, T_Of_Valhalla_Time[point - 1]);
					if (this == lpCurPlayer)
						SendProcessSKillToServer(SKILL_PLAY_TRIUMPH_OF_VALHALLA, point, chrAttackTarget->iID, sCharacterData.iLevel);
				}
			}
			else
			{
				AssaParticle_TriumphOfValhalla(this, T_Of_Valhalla_Time[point - 1]);
				if (lpCurPlayer == this)
				{
					dwT_Of_Valhalla_Time = dwPlayTime + T_Of_Valhalla_Time[point - 1] * 1000;
					ClearSkillToPlay(SKILL_HALL_OF_VALHALLA);
				}

			}
			break;
			//¹âÁÔÖ®Ç¹
		case SKILL_PLAY_LIGHTNING_JAVELIN:
			if (chrAttackTarget && GetAttackPoint(&x, &y, &z) == TRUE)
			{
				Pos1.x = x;
				Pos1.y = y;
				Pos1.z = z;
				Pos2.x = chrAttackTarget->pX;
				Pos2.y = chrAttackTarget->pY + 28 * fONE;
				Pos2.z = chrAttackTarget->pZ;
				AssaParticle_LightingJavelin(&Pos1, &Pos2);
				switch (rand() % 2)
				{
				case 0:
					SkillPlaySound(SKILL_SOUND_SKILL_LIGHTNING_JAVELIN1, pX, pY, pZ);
					break;
				case 1:
					SkillPlaySound(SKILL_SOUND_SKILL_LIGHTNING_JAVELIN2, pX, pY, pZ);
					break;
				}
			}
			break;
			//±©·ç¿ñ±ê
		case SKILL_PLAY_STORM_JAVELIN:
			if (chrAttackTarget && AttackCritcal >= 0 && GetAttackPoint(&x, &y, &z) == TRUE)
			{
				Pos1.x = x;
				Pos1.y = y;
				Pos1.z = z;
				Pos2.x = chrAttackTarget->pX;
				Pos2.y = chrAttackTarget->pY + 28 * fONE;
				Pos2.z = chrAttackTarget->pZ;
				AssaParticle_StormJavelin(&Pos1, &Pos2);
				rect.left = -30;
				rect.right = 30;
				rect.top = 0;
				rect.bottom = 240;
				rect.bottom += 20;
				rect.bottom += 20;
				dm_SelectRangeBox(this, &rect, FALSE);
				for (cnt = 0; cnt < dmSelected_CharCnt; cnt++)
				{
					if (lpSelected_Char[cnt])
						AssaParticle_StormJavelinHit(lpSelected_Char[cnt], this, 0.5f);
				}
				switch (rand() % 2)
				{
				case 0:
					SkillPlaySound(SKILL_SOUND_SKILL_STORM_JAVELIN1, pX, pY, pZ);
					break;
				case 1:
					SkillPlaySound(SKILL_SOUND_SKILL_STORM_JAVELIN2, pX, pY, pZ);
					break;
				}
			}
			break;
			//Íß¶û¹þÀ­Ö®¹â
		case SKILL_PLAY_HALL_OF_VALHALLA:
			if (point)
			{
				SkillValhallaHallOfValhalla1(this);
				SkillValhallaHallOfValhallaHandEffect(this, (float)Hall_Of_Valhalla_Time[point - 1]);
			}
			break;
			//Ê®×ÖÅ­»÷
		case SKILL_PLAY_X_RAGE:
			if (chrAttackTarget && point)
			{
				auto sPosition = GetMoveLocation(0, 0, 24 * fONE, 0, Angle.y, 0);
				Pos1.x = pX + sPosition.iX;
				Pos1.y = pY + sPosition.iY;
				Pos1.z = pZ + sPosition.iZ;
				Pos2.x = chrAttackTarget->pX;
				Pos2.y = chrAttackTarget->pY + 40 * fONE;
				Pos2.z = chrAttackTarget->pZ;
				SkillValhallaXRage(&Pos1, &Pos2);
				switch (rand() % 3)
				{
				case 0:
					SkillPlaySound(SKILL_SOUND_SKILL_EXTREM_RAGE1, pX, pY, pZ);
					break;
				case 1:
					SkillPlaySound(SKILL_SOUND_SKILL_EXTREM_RAGE2, pX, pY, pZ);
					break;
				case 2:
					SkillPlaySound(SKILL_SOUND_SKILL_EXTREM_RAGE3, pX, pY, pZ);
					break;
				}
			}
			break;
			//Ëª¶³±êÇ¹
		case SKILL_PLAY_FROST_JAVELIN:
			if (point)
			{
				SkillParticle_FrostJavelin(this, (float)Frost_Javelin_Time[point - 1]);
				if (lpCurPlayer == this)
					dwFrost_Javelin_Time = dwPlayTime + Frost_Javelin_Time[point - 1] * 1000;
			}
			break;
			//¿ñ·ç±¬ÁÑ
		case SKILL_PLAY_VENGEANCE:
			if (chrAttackTarget && point)
			{
				auto sPosition = GetMoveLocation(0, 24 * fONE, 24 * fONE, 0, Angle.y, 0);
				Pos1.x = pX + sPosition.iX;
				Pos1.y = pY + sPosition.iY;
				Pos1.z = pZ + sPosition.iZ;
				Pos2.x = chrAttackTarget->pX;
				Pos2.y = chrAttackTarget->pY + 40 * fONE;
				Pos2.z = chrAttackTarget->pZ;
				if (AttackCritcal >= 0)
					SkillVengeance(&Pos1, &Pos2);
				if (this == lpCurPlayer && MotionEvent == 1)
				{
					cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, AttackSkil, TRUE);
					if (!cnt)
						AttackCritcal = -1;
				}
				if (MotionEvent == 1)
					SkillPlaySound(SKILL_SOUND_SKILL_VENGEANCE1, pX, pY, pZ);
				else
					SkillPlaySound(SKILL_SOUND_SKILL_VENGEANCE2, pX, pY, pZ);
			}
			break;
			//ÇáÎè·ÉÑï
		case SKILL_PLAY_TALARIA:
			if (point)
			{
				AssaParticle_TaltriaEffect(this, Talaria_Time[point - 1]);
				SkillPlaySound(SKILL_SOUND_SKILL_WINDY1, pX, pY, pZ);
				if (this == lpCurPlayer)
					dwTalaria_Time = dwPlayTime + Talaria_Time[point - 1] * 1000;
			}
			break;
			//ÐÇÓê±êÇ¹
		case SKILL_PLAY_G_COUP:
			if (point)
			{
				SkillPlaySound(SKILL_SOUND_SCOUT_HAWK1, pX, pY, pZ);

				if (this == lpCurPlayer && MotionEvent == 1)
				{
					cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, AttackSkil, TRUE);
					if (!cnt)
						lpCurPlayer->AttackCritcal = -1;
					else
						lpCurPlayer->AttackCritcal = 0;
				}
			}
			break;
			//±¿±¿ÐÜ
		case SKILL_PLAY_S_ARCUDA:
			if (point)
			{
				AssaParticle_SummonArcuda(this);
				if (this == lpCurPlayer)
					SendProcessSKillToServer(SKILL_PLAY_S_ARCUDA, point, 0, 0);
			}
			break;
			//ÁÒÑæÍ»Ï®
		case SKILL_PLAY_S_FEAR:
			if (chrAttackTarget && point)
			{
				auto sPosition = GetMoveLocation(0, 24 * fONE, 24 * fONE, 0, Angle.y, 0);
				Pos1.x = pX + sPosition.iX;
				Pos1.y = pY + sPosition.iY;
				Pos1.z = pZ + sPosition.iZ;
				Pos2.x = chrAttackTarget->pX;
				Pos2.y = chrAttackTarget->pY + 40 * fONE;
				Pos2.z = chrAttackTarget->pZ;
				AssaParticle_S_Fear(&Pos1, &Pos2);

				if (this == lpCurPlayer)
				{
					if (MotionEvent == 1 || MotionEvent == 2)
					{
						cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, AttackSkil, TRUE);
						if (!cnt)
							AttackCritcal = -1;
					}
				}
				if (MotionEvent == 1)
					SkillPlaySound(SKILL_SOUND_SKILL_VENGEANCE1, pX, pY, pZ);
				else
					SkillPlaySound(SKILL_SOUND_SKILL_VENGEANCE2, pX, pY, pZ);
			}
			break;
		}
		break;
		//ÓÎÏÀ
	case CHARACTERCLASS_Knight:
		switch (SkillCode)
		{
			//Ä§Éñ½£
		case SKILL_PLAY_SWORD_BLAST:
			if (chrAttackTarget)
			{
				sinEffect_Sword_Blast(this, chrAttackTarget);
				SkillPlaySound(SKILL_SOUND_SKILL_SWORDBLAST2, pX, pY, pZ);
			}
			break;
			//Ê¥¹â»¤Ìå
		case SKILL_PLAY_HOLY_BODY:
			if (lpCurPlayer == this)
			{
				StartSkill(pX, pY, pZ, 0, Angle.y, 0, this, SKILL_SHIELD1, point);
				dwHolyBody_Time = dwPlayTime + HolyBody_Time[point - 1] * 1000;
			}
			break;
			//Ë«ÖØ±¬»÷
		case SKILL_PLAY_DOUBLE_CRASH:
			if (AttackCritcal >= 0)
			{
				if (GetAttackPoint(&x, &y, &z) == TRUE)
				{
					if (AttackCritcal == 0)
					{
						StartEffect(x, y, z, EFFECT_NORMAL_HIT1);
						SetDynLight(x, y, z, 80, 0, 0, 0, 300);
					}
					else
					{
						StartEffect(x, y, z, EFFECT_CRITICAL_HIT1);
						SetDynLight(x, y, z, 100, 0, 0, 0, 400);
					}
				}
			}
			WeaponPlaySound(this);
			if (this == lpCurPlayer && chrAttackTarget && MotionEvent < 2)
			{
				cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);

				if (cnt > 0)
				{
					lpCurPlayer->AttackCritcal = 0;
					DamageExp(chrAttackTarget, cnt);
					if (AttackExp)
						AttackExp = 0;
				}
				else
					lpCurPlayer->AttackCritcal = -1;
			}
			break;
			//ÉñÁ¦ÖØ»÷
		case SKILL_PLAY_HOLY_VALOR:
			if (point)
			{
				AssaParticle_HolyValor_JangEffect(this, Holy_Valor_Time[point - 1]);
				if (this == lpCurPlayer)
				{
					SendPartySkillToServer(SKILL_PLAY_HOLY_VALOR, point, 200, 0, 0, 0, 0);
					dwHoly_Valor_Time = dwPlayTime + Holy_Valor_Time[point - 1] * 1000;
				}
			}
			break;
			//¿ñÔê»ÓÎè
		case SKILL_PLAY_BRANDISH:
			sinSkillEffect_Brandish(this);
			SkillPlaySound(SKILL_SOUND_SKILL_BLANDISH2, pX, pY, pZ);
			break;
			//Ò»ÎíÒø
		case SKILL_PLAY_PIERCING:
			sinSkillEffect_Piercing_Attack(this);
			break;
			//ÌìÓÓÉñîø
		case SKILL_PLAY_DRASTIC_SPIRIT:
			if (point)
			{
				AssaParticle_DrasticSpirit_JangEffect(this, Drastic_Spirit_Time[point - 1]);
				if (lpCurPlayer == this)
					dwDrastic_Spirit_Time = dwPlayTime + Drastic_Spirit_Time[point - 1] * 1000;
			}
			//Ê¥ÁéÖ®Îü
		case SKILL_PLAY_DIVINE_INHALATION:
			if (point)
			{
				AssaParticle_DivineInhalationPart(this, D_Inhalation_Time[point - 1]);
				if (lpCurPlayer == this)
					dwD_Inhalation_Time = dwPlayTime + D_Inhalation_Time[point - 1] * 1000;
			}
			break;
			//Ê¥ØßÖ®¹â
		case SKILL_PLAY_HOLY_INCANTATION:
			if (chrAttackTarget)
			{
				AssaParticle_HolyIncantationShot(chrAttackTarget);
				SkillPlaySound(SKILL_SOUND_SKILL_HOLY_INCANTATION, pX, pY, pZ);
				if (this == lpCurPlayer)
					dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, lpCurPlayer->AttackSkil, FALSE);
			}
			break;
			//Ê¥¹âÊ®×Ö
		case SKILL_PLAY_GRAND_CROSS:
			if (chrAttackTarget && AttackCritcal >= 0 && GetAttackPoint(&x, &y, &z) == TRUE)
			{
				Pos1.x = x;
				Pos1.y = y;
				Pos1.z = z;
				if (MotionEvent == 1)
				{
					AssaParticle_GrandCrossHorz(&Pos1, Angle.y);
					SkillPlaySound(SKILL_SOUND_SKILL_SWING2, pX, pY, pZ);
				}
				else
				{
					AssaParticle_GrandCrossVert(&Pos1, Angle.y);
					SkillPlaySound(SKILL_SOUND_SKILL_GRAND_CROSS, pX, pY, pZ);
				}
			}
			else
				PlayWaponSoundDirect(pX, pY, pZ, 13);
			if (this == lpCurPlayer && chrAttackTarget && MotionEvent == 1)
			{
				x = sCharacterData.iAttackRange;
				sCharacterData.iAttackRange += (sCharacterData.iAttackRange*Grand_Cross_AttackRate[point - 1]) / 100;
				cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
				if (cnt > 0)
					lpCurPlayer->AttackCritcal = 0;
				else
					lpCurPlayer->AttackCritcal = -1;
				sCharacterData.iAttackRange = x;
			}
			break;
			//ÕæÄ§Éñ½£
		case SKILL_PLAY_SWORD_OF_JUSTICE:
			if (point)
				SkillSwordOfUstice(this);
			break;
			//¾´ÉñÖ®¶Ü
		case SKILL_PLAY_GODLY_SHIELD:
			if (point)
			{
				AssaParticle_DivineInhalationPart(this, Godly_Shield_Time[point - 1]);
				if (lpCurPlayer == this)
					dwGodly_Shield_Time = dwPlayTime + Godly_Shield_Time[point - 1] * 1000;
			}
			break;
			//ÉÏµÛ×£¸£
		case SKILL_PLAY_GODS_BLESS:
			if (point)
			{
				SkillSaintGodBless(this, (float)God_Bless_Time[point - 1]);
				if (lpCurPlayer == this)
					dwGod_Bless_Time = dwPlayTime + God_Bless_Time[point - 1] * 1000;
			}
			break;
			//É²¾ç»ÄÎè
		case SKILL_PLAY_DIVINE_PIERCING:
			if (chrAttackTarget && point)
			{
				if (AttackCritcal >= 0)
					SkillSaintDivinePiercing(this);
				if (Divine_Piercing_AttackNum[point - 1] >= 7)
				{
					dwEventFrameExt[0] = (81 - 10 + psModelAnimation->StartFrame) * 160;
					dwEventFrameExt[1] = (102 - 10 + psModelAnimation->StartFrame) * 160;
					dwEventFrameExt[2] = (120 - 10 + psModelAnimation->StartFrame) * 160;
				}
				else if (Divine_Piercing_AttackNum[point - 1] >= 5)
					dwEventFrameExt[0] = (227 - 150 + psModelAnimation->StartFrame) * 160;
				if (MotionEvent == Divine_Piercing_AttackNum[point - 1] && AttackCritcal >= 0)
					SkillPlaySound(SKILL_SOUND_SKILL_DVINE_PIERCING, pX, pY, pZ);
				else
					WeaponPlaySound(this);
				if (lpCurPlayer == this && MotionEvent < Divine_Piercing_AttackNum[point - 1])
				{
					cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
					if (!cnt)
						lpCurPlayer->AttackCritcal = -1;
					else
						lpCurPlayer->AttackCritcal = 0;
				}
			}
			break;
			//ÉñÁ¦³å´Ì
		case SKILL_PLAY_S_BREAKER:
			if (chrAttackTarget && point)
			{
				sinSkillEffect_Breaker2(this);
				sinEffect_Benedic3(this);
				SkillPlaySound(SKILL_SOUND_SKILL_AVANGING_CRASH, pX, pY, pZ);
				if (lpCurPlayer == this)
				{
					x = sCharacterData.iAttackRange;
					sCharacterData.iAttackRange += (sCharacterData.iAttackRange * S_Breaker_AddHit[point - 1]) / 100;

					cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
					if (!cnt)
						AttackCritcal = -1;
					else
						AttackCritcal = 0;

					sCharacterData.iAttackRange = x;
				}
			}
			break;
			//ÉýÁúÖØ»÷
		case SKILL_PLAY_C_MOON:
			if (chrAttackTarget && point)
			{
				AssaParticle_Moon2(chrAttackTarget);
				sinSkillEffect_Moon(chrAttackTarget);
				SkillPlaySound(SKILL_SOUND_SKILL_AUTOMATION2, pX, pY, pZ);
				if (lpCurPlayer == this)
				{
					dm_SelectRange(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, C_Moon_Area[point - 1], FALSE);
					dm_SendRangeDamage(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 0, 0, 0, 0, 0, AttackSkil);
				}
			}
			break;
			//ÉÏµÛÖØ»÷
		case SKILL_PLAY_S_BLADE:
			if (chrAttackTarget && point)
			{
				AssaParticle_Blade(chrAttackTarget);
				SkillPlaySound(SKILL_SOUND_SKILL_CHAIN_LANCE2, pX, pY, pZ);

				if (lpCurPlayer == this)
				{
					cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
					if (!cnt)
						AttackCritcal = -1;
					else
						AttackCritcal = 0;
				}
			}
			break;
			//ÍöÁéÖ®Öä
		case SKILL_PLAY_H_BENEDIC:
			if (chrAttackTarget && point)
			{
				AssaParticle_Benedic2(chrAttackTarget);
				//sinEffect_Benedic(chrAttackTarget,30);
				SkillPlaySound(SKILL_SOUND_SKILL_FORCE_OF_NATURE, pX, pY, pZ);
				if (this == lpCurPlayer)
					SendProcessSKillToServer(SKILL_PLAY_H_BENEDIC, point, chrAttackTarget->iID, 0);

			}
			break;
		}
		break;
		//Ä§·¨Ê¦
	case CHARACTERCLASS_Magician:
		switch (SkillCode)
		{
			//»ð¼ýÖ®Êõ
		case SKILL_PLAY_FIRE_BOLT:
			if (chrAttackTarget)
			{
				auto sPosition = GetMoveLocation(0, 24 * fONE, 24 * fONE, 0, Angle.y, 0);
				StartEffectMonsterDest(pX + sPosition.iX, pY + sPosition.iY, pZ + sPosition.iZ, chrAttackTarget->pX, chrAttackTarget->pY + 20 * fONE, chrAttackTarget->pZ, MONSTER_IMP_SHOT2);
				if (((dwPlayTime >> 4) & 1) == 0)
					SkillPlaySound(SKILL_SOUND_SKILL_FIREBOLT1, pX, pY, pZ);
				else
					SkillPlaySound(SKILL_SOUND_SKILL_FIREBOLT2, pX, pY, pZ);
			}
			break;
			//¼¯ºÏÖ®Êõ
		case SKILL_PLAY_ZENITH:
			if (point)
			{
				if (lpCurPlayer == this)
					dwZenith_Time = dwPlayTime + Zenith_Time[point - 1] * 1000;
			}
			break;
			//»ðÇòÖ®Êõ
		case SKILL_PLAY_FIRE_BALL:
			if (chrAttackTarget)
			{
				auto sPosition = GetMoveLocation(0, 24 * fONE, 24 * fONE, 0, Angle.y, 0);
				StartEffectMonsterDest(pX + sPosition.iX, pY + sPosition.iY, pZ + sPosition.iZ, chrAttackTarget->pX, chrAttackTarget->pY + 20 * fONE, chrAttackTarget->pZ, MONSTER_PIGON_SHOT1);
				if (((dwPlayTime >> 4) & 1) == 0)
					SkillPlaySound(SKILL_SOUND_SKILL_FIREBALL1, pX, pY, pZ);
				else
					SkillPlaySound(SKILL_SOUND_SKILL_FIREBALL2, pX, pY, pZ);
			}
			break;
			//Áú¾íº£·ç
		case SKILL_PLAY_COLUMN_OF_WATER:
			if (chrAttackTarget)
			{
				Pos1.x = pX;
				Pos1.y = pY;
				Pos1.z = pZ;
				Pos2.x = chrAttackTarget->pX;
				Pos2.y = chrAttackTarget->pY;
				Pos2.z = chrAttackTarget->pZ;
				AssaParticle_ColumnOfWater(&Pos1, &Pos2, point);
				switch (rand() % 2)
				{
				case 0:
					SkillPlaySound(SKILL_SOUND_SKILL_WATORNADO1, pX, pY, pZ);
					break;
				case 1:
					SkillPlaySound(SKILL_SOUND_SKILL_WATORNADO2, pX, pY, pZ);
					break;
				}
			}
			break;
			//ÔªËØÖ®Êõ
		case SKILL_PLAY_ENCHANT_WEAPON:
			if (chrAttackTarget)
			{
				AssaParticle_EnchantWeaponJinMember(chrAttackTarget);
				SendProcessSKillToServer(SKILL_PLAY_ENCHANT_WEAPON, point, chrAttackTarget->iID, param);
			}
			else
			{
				if (this == lpCurPlayer)
				{
					SendProcessSKillToServer(SKILL_PLAY_ENCHANT_WEAPON, point, lpCurPlayer->iID, param);
					cSkill.SetEnchant_Weapon(Enchant_Weapon_Time[point - 1], point);
				}
			}
			break;
			//Ú¤ÍöÖ®¹â
		case SKILL_PLAY_DEAD_RAY:
			if (chrAttackTarget)
			{
				auto sPosition = GetMoveLocation(0, 24 * fONE, 24 * fONE, 0, Angle.y, 0);
				Pos1.x = pX + sPosition.iX;
				Pos1.y = pY + sPosition.iY;
				Pos1.z = pZ + sPosition.iZ;
				Pos2.x = chrAttackTarget->pX;
				Pos2.y = chrAttackTarget->pY + 32 * fONE;
				Pos2.z = chrAttackTarget->pZ;
				AssaParticle_DeadLay(&Pos1, &Pos2);
				SkillPlaySound(SKILL_SOUND_SKILL_DEATHRAY, pX, pY, pZ);
			}
			break;
			//Ä§·¨ÊØ»¤
		case SKILL_PLAY_ENERGY_SHIELD:
			if (point)
			{
				AssaParticle_EnergyShield(this, Energy_Shield_Time[point - 1]);
				SkillPlaySound(SKILL_SOUND_SKILL_ENERGY_SHIELD, pX, pY, pZ);
				if (lpCurPlayer == this)
					dwEnergy_Shield_Time = dwPlayTime + Energy_Shield_Time[point - 1] * 1000;
			}
			break;
			//µØÁÑ³å»÷
		case SKILL_PLAY_DIASTROPHISM:
			AssaParticle_Diastrophism(this);
			SkillPlaySound(SKILL_SOUND_SKILL_DIASTROPHISM, pX, pY, pZ);
			if (this == lpCurPlayer && MotionEvent < 2)
			{
				dm_SelectRange(pX, pY, pZ, Diastrophism_Area[point - 1], FALSE);
				dm_SendRangeDamage(pX, pY, pZ, 0, 
					cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin,
					cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax,
					0, 0, AttackSkil);
			}
			break;
			//Áé»êÕÙ»½
		case SKILL_PLAY_SPIRIT_ELEMENTAL:
			if (point)
			{
				AssaParticle_SpiritElemental(this, Spirit_Elemental_Time[point - 1]);
				SkillPlaySound(SKILL_SOUND_SKILL_SPIRIT_ELEMENTAL, pX, pY, pZ);
				if (lpCurPlayer == this)
					dwSpirit_Elemental_Time = dwPlayTime + Spirit_Elemental_Time[point - 1] * 1000;
			}
			break;
			//ÔªËØÖ®½£
		case SKILL_PLAY_DANCING_SWORD:
			if (point)
			{
				switch (param)
				{
				case 0:
					AssaParticle_DancingSwordIce(this, Dancing_Sword_Time[point - 1], point);
					break;
				case 1:
					AssaParticle_DancingSwordFire(this, Dancing_Sword_Time[point - 1], point);
					break;
				}
				SkillPlaySound(SKILL_SOUND_SKILL_DANCING_SWORD, pX, pY, pZ);

				if (lpCurPlayer == this)
				{
					dwDancing_Sword_Time = dwPlayTime + Dancing_Sword_Time[point - 1] * 1000;
					dwDancing_Sword_Param = param | (point << 8);
				}
			}
			break;
			//ÒÁ·òÁÐÌØ
		case SKILL_PLAY_FIRE_ELEMENTAL:
			if (MotionEvent)
			{
				if (lpCurPlayer == this)
					SendProcessSKillToServer(SKILL_PLAY_FIRE_ELEMENTAL, point, 0, 0);
			}
			break;
			//»ðÑæ²¨¶¯
		case SKILL_PLAY_FLAME_WAVE:
			if (point)
			{
				SkillArchMageFlameWave(this);
				if (rand() % 2)
					SkillPlaySound(SKILL_SOUND_SKILL_FLAME_WAVE1, pX, pY, pZ);
				else
					SkillPlaySound(SKILL_SOUND_SKILL_FLAME_WAVE2, pX, pY, pZ);
				if (this == lpCurPlayer && MotionEvent == 1)
				{
					rect.left = -60;
					rect.right = 60;
					rect.top = 0;
					rect.bottom = 300;
					rect.bottom += 20;
					rect.bottom += 20;
					dm_SelectRangeBox(lpCurPlayer, &rect, FALSE);
					dm_SendRangeDamage(lpCurPlayer->pX,
						lpCurPlayer->pY,
						lpCurPlayer->pZ,
						0,
						cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin,
						cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax,
						0, 0, lpCurPlayer->AttackSkil);
				}
			}
			break;
			//¿Õ¼äÅ¤Çú
		case SKILL_PLAY_DISTORTION:
			break;
			//ÔÉÊ¯ÕÙ»½
		case SKILL_PLAY_METEO:
			if (chrAttackTarget && point)
			{
				Pos2.x = chrAttackTarget->pX;
				Pos2.y = chrAttackTarget->pY;
				Pos2.z = chrAttackTarget->pZ;
				SkillArchMageMeteo(&Pos2, SKILL_M_METEO);
				if (this == lpCurPlayer && MotionEvent < 3)
				{
					dm_SelectRange(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, Meteo_Area[point - 1], FALSE);
					dm_SendRangeDamage(chrAttackTarget->pX,
						chrAttackTarget->pY,
						chrAttackTarget->pZ,
						0,
						cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin,
						cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax,
						0, 0, lpCurPlayer->AttackSkil);
				}
				SkillPlaySound(SKILL_SOUND_SKILL_METEO1, pX, pY, pZ);
			}
			break;
			//Á÷ÐÇ»ðÓê
		case SKILL_PLAY_SILRAPHIM:
			if (chrAttackTarget && point)
			{
				auto sPosition = GetMoveLocation(0, 24 * fONE, 24 * fONE, 0, Angle.y, 0);
				StartEffectMonsterDest(pX + sPosition.iX, pY + sPosition.iY, pZ + sPosition.iZ, chrAttackTarget->pX, chrAttackTarget->pY + 20 * fONE, chrAttackTarget->pZ, MONSTER_IMP_SHOT4);
				SkillPlaySound(SKILL_SOUND_SKILL_SPARK3, pX, pY, pZ);
				if (this == lpCurPlayer)
				{
					cnt = dm_SendTransDamage(chrAttackTarget,
						cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin,
						cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax,
						0, 0, AttackSkil, FALSE);
					if (cnt)
						DamageExp(chrAttackTarget, cnt);

					dm_SelectRange(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 60, FALSE);
					dm_SendRangeDamage(chrAttackTarget->pX,
						chrAttackTarget->pY,
						chrAttackTarget->pZ,
						0,
						cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin,
						cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax,
						0, 0, AttackSkil);
				}
			}
			break;
			//ËõÐ¡Ö®Êõ
		case SKILL_PLAY_V_TENUS:
			if (chrAttackTarget && point)
			{
				auto sPosition = GetMoveLocation(0, 24 * fONE, 24 * fONE, 0, Angle.y, 0);
				StartEffectMonsterDest(pX + sPosition.iX, pY + sPosition.iY, pZ + sPosition.iZ, chrAttackTarget->pX, chrAttackTarget->pY + 20 * fONE, chrAttackTarget->pZ, MONSTER_IMP_SHOT5);
				SkillPlaySound(SKILL_SOUND_SKILL_TORNADO1, pX, pY, pZ);
				if (lpCurPlayer == this)
				{
					cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, AttackSkil, FALSE);
					if (cnt)
						DamageExp(chrAttackTarget, cnt);
				}
			}
			break;
			//ÉñÊ¥Ï´Àñ
		case SKILL_PLAY_P_IGNIS:
			if (point)
			{
				SkillPlaySound(SKILL_SOUND_SKILL_DIASTROPHISM, pX, pY, pZ);
				if (lpCurPlayer == this)
				{
					dm_SelectRange(pX, pY, pZ, P_Ignis_Area[point - 1], FALSE);
					dm_SendRangeDamage(pX, pY, pZ, 0, cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin, cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax, 0, 0, AttackSkil);
				}
			}
			break;
			//Ê¥¹â·¨Õó
		case SKILL_PLAY_T_ANIMA:
			if (point)
			{
				sinEffect_Anima(this, T_Anima_Time[point - 1], 1);
				SkillPlaySound(SKILL_SOUND_SKILL_AGONY, pX, pY, pZ);
				if (lpCurPlayer == this)
				{
					cnt = cSkill.GetSkillPoint(SKILL_SPIRIT_ELEMENTAL);
					if (cnt)
						SendProcessSKillToServer(SKILL_PLAY_T_ANIMA, point, cnt, 0);
					else
						SendProcessSKillToServer(SKILL_PLAY_T_ANIMA, point, 0, 0);
					dwT_Anima_Time = dwPlayTime + T_Anima_Time[point - 1] * 1000;
				}
			}
			break;
		}
		break;
		//¼ÀË¾
	case CHARACTERCLASS_Priestess:
		switch (SkillCode)
		{
			//Ê¥¹âµçÇò
		case SKILL_PLAY_HOLY_BOLT:
			if (chrAttackTarget)
			{
				auto sPosition = GetMoveLocation(0, 24 * fONE, 24 * fONE, 0, Angle.y, 0);
				StartEffectMonsterDest(pX + sPosition.iX, pY + sPosition.iY, pZ + sPosition.iZ, chrAttackTarget->pX, chrAttackTarget->pY + 20 * fONE, chrAttackTarget->pZ, MONSTER_MEPHIT_SHOT2);
				SkillPlaySound(SKILL_SOUND_SKILL_HOLYBOLT, pX, pY, pZ);
			}
			break;
			//¹âÃ¢ËÄÉä
		case SKILL_PLAY_MULTI_SPARK:
			if (chrAttackTarget)
			{
				sinEffect_MultiSpark(this, chrAttackTarget, param);
				SkillPlaySound(SKILL_SOUND_SKILL_MULTISPARK, pX, pY, pZ);
			}
			break;
			//ÉñÖ®À×µç
		case SKILL_PLAY_DIVINE_LIGHTNING:
			if (this == lpCurPlayer)
			{
				dm_SelectDamageCount(this, Divine_Lightning_Num[point - 1], 180);
				dm_SendRangeDamage(pX, pY, pZ, 0, cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin, cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax, 0, 0, AttackSkil);
			}
			if (SkillPlay_DivineLightning_Effect(this, point) > 0)
			{
				switch (rand() % 3)
				{
				case 0:
					SkillPlaySound(SKILL_SOUND_SKILL_DIVINELIGHTNING1, pX, pY, pZ);
					break;
				case 1:
					SkillPlaySound(SKILL_SOUND_SKILL_DIVINELIGHTNING2, pX, pY, pZ);
					break;
				case 2:
					SkillPlaySound(SKILL_SOUND_SKILL_DIVINELIGHTNING3, pX, pY, pZ);
					break;
				}
			}
			break;
			//ÉñÊ¥·´Éä
		case SKILL_PLAY_HOLY_REFLECTION:
			if (point)
			{
				if (lpCurPlayer == this)
				{
					SendProcessSKillToServer(SKILL_PLAY_HOLY_REFLECTION, point, 0, 0);
					dwHoly_Reflection_Time = dwPlayTime + Holy_Reflection_Time[point - 1] * 1000;
				}

			}
			break;
			//Ê¥½àÖ®¹â
		case SKILL_PLAY_GREAT_HEALING:
			if (this == lpCurPlayer)
			{
				for (size_t i = 0; i < MAX_PARTY_MEMBERS; i++)
				{
					Unit * p = GAMEUNIT->GetUnitByID(PARTYHANDLE->GetPartyData().saMembers[i].sData.iID);

					if (p)
					{
						if (p->bActive && p->psModelAnimation->iType != ANIMATIONTYPE_Die)
						{
							int iDistance = UNIT->sPosition.GetPTDistance(p->sPosition);

							if (iDistance < (300 * 300))
								sinSkillEffect_Great_Healing_Party(p);
						}
					}
				}
			}
			break;
			//»ðÓ°Ë«ÖØ
		case SKILL_PLAY_VIGOR_BALL:
			if (chrAttackTarget)
			{
				if (this == lpCurPlayer && MotionEvent < 3)
					cnt = dm_SendTransDamage(chrAttackTarget,
						cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin,
						cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax,
						0, 0, AttackSkil, FALSE);
				AssaParticle_VigorBall(this, chrAttackTarget);
				switch (rand() % 2)
				{
				case 0:
					SkillPlaySound(SKILL_SOUND_SKILL_VIGOR_BALL1, pX, pY, pZ);
					break;
				case 1:
					SkillPlaySound(SKILL_SOUND_SKILL_VIGOR_BALL2, pX, pY, pZ);
					break;
				}
			}
			break;
			//»ØÉúÖ®Êõ
		case SKILL_PLAY_RESURRECTION:
			if (this == lpCurPlayer)
			{
				lpChar = FindDeadPartyUser();
				if (lpChar)
				{
					SendProcessSKillToServer(SKILL_PLAY_RESURRECTION, point, lpChar->iID, 0);
					chrAttackTarget = lpChar;
				}
				else
					chrAttackTarget = 0;
			}
			if (chrAttackTarget)
				AssaParticle_ResurrectionShot(chrAttackTarget);
			break;
			//Ê¥¹âÖ®Öä
		case SKILL_PLAY_EXTINCTION:
			break;
			//ÉñÊ¥Ö®¹â
		case SKILL_PLAY_VIRTUAL_LIFE:
			if (point)
			{
				if (chrAttackTarget)
				{
					AssaParticle_VirtualLifeStart(chrAttackTarget);
					AssaParticle_VirtualLifeEffect(chrAttackTarget, Virtual_Life_Time[point - 1]);
				}
				else
				{
					AssaParticle_VirtualLifeStart(this);
					AssaParticle_VirtualLifeEffect(this, Virtual_Life_Time[point - 1]);

					if (lpCurPlayer == this)
						dwVirtual_Life_Time = dwPlayTime + Virtual_Life_Time[point - 1] * 1000;
				}
				SkillPlaySound(SKILL_SOUND_SKILL_VIRTUAL_LIFE, pX, pY, pZ);
			}
			break;
			//±ùËªÊÉÔÂ
		case SKILL_PLAY_GLACIAL_SPIKE:
			if (point && MotionEvent == 1)
			{
				SkillCelestialGlacialSpike(this);
				auto sPosition = GetMoveLocation(0, 0, 64 * fONE, 0, Angle.y, 0);
				SetDynLight(pX + sPosition.iX, pY, pZ + sPosition.iZ, 0, 0, 100, 0, 700);
				if (this == lpCurPlayer)
				{
					rect.left = -50;
					rect.right = 50;
					rect.top = 0;
					rect.bottom = 300;
					rect.bottom += 20;
					rect.bottom += 20;
					dm_SelectRangeBox(lpCurPlayer, &rect, FALSE);
					dm_SendRangeDamage(lpCurPlayer->pX,
						lpCurPlayer->pY,
						lpCurPlayer->pZ,
						0,
						cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin,
						cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax,
						0, 0, lpCurPlayer->AttackSkil);
				}
				if (rand() % 2)
					SkillPlaySound(SKILL_SOUND_SKILL_GLACIAL_SPIKE1, pX, pY, pZ);
				else
					SkillPlaySound(SKILL_SOUND_SKILL_GLACIAL_SPIKE2, pX, pY, pZ);
			}
			break;
			//ÔÙÉúÁìÓò
		case SKILL_PLAY_REGENERATION_FIELD:
			if (point)
			{
				SkillCelestialRegnerationField(this, 2.0f);
				if (this == lpCurPlayer)
				{
					if (MouseButton[1] && cSkill.SearchContiueSkill(SKILL_REGENERATION_FIELD))
						iFrame = psModelAnimation->StartFrame * 160 + psModelAnimation->EventFrame[0];
					else
						cSkill.CancelContinueSkill(SKILL_REGENERATION_FIELD);
				}
				else
				{
					cnt = Regeneration_Field_Area[point - 1];
					cnt *= cnt;
					if (GetDistanceDbl(pX, pZ, lpCurPlayer->pX, lpCurPlayer->pZ) < cnt && abs(lpCurPlayer->pY - pY) < 16 * fONE)
						cSkill.Regeneration_Field(5, point, 1);
				}
			}
			break;
			//ÌìÀ×Ö®Å­
		case SKILL_PLAY_CHAIN_LIGHTNING:
			if (chrAttackTarget && point)
			{
				dm_SelectDamageChainCount(this, chrAttackTarget, Chain_Lightning_Num[point - 1], Chain_Lightning_Range[point - 1]);
				if (dmSelected_CharCnt > 0)
				{
					if (this == lpCurPlayer)
						dm_SendRangeDamage(pX,
							pY,
							pZ,
							0,
							cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin,
							cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax,
							0, 0, AttackSkil);
					SkillCelestialChainLighting(lpSelected_Char, dmSelected_CharCnt);
					if (rand() % 2)
						SkillPlaySound(SKILL_SOUND_SKILL_CHAIN_LIGHTNING1, pX, pY, pZ);
					else
						SkillPlaySound(SKILL_SOUND_SKILL_CHAIN_LIGHTNING2, pX, pY, pZ);
				}
			}
			break;
			//ÉñÊ¥ÌìÊ¹
		case SKILL_PLAY_SUMMON_MUSPELL:
			if (point)
			{
				SkillCelestialMusPel(this, (float)Summon_Muspell_Time[point - 1], (float)Summon_Muspell_Attack_Delay[point - 1], SKILL_SUMMON_MUSPELL);
				SkillPlaySound(SKILL_SOUND_SKILL_MUSPELL2, pX, pY, pZ);
				if (lpCurPlayer == this)
					dwSummon_Muspell_Time = dwPlayTime + Summon_Muspell_Time[point - 1] * 1000;
			}
			break;
			//ÉñÊ¥µç²¨
		case SKILL_PLAY_S_IMPACT:
			if (point && chrAttackTarget)
			{
				StartSkillDest(pX, pY + 24 * fONE, pZ, chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ, SKILL_S_IMPACT, point);
				SkillPlaySound(SKILL_SOUND_SKILL_ASSASSIN_EYE, pX, pY, pZ);

				if (lpCurPlayer == this)
				{
					cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, AttackSkil, TRUE);
					if (!cnt)
						lpCurPlayer->AttackCritcal = -1;
					else
						lpCurPlayer->AttackCritcal = 0;

					dm_SelectRange(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 60, FALSE);
					dm_SendRangeDamage(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 0, 0, 0, 0, 0, AttackSkil);
				}
			}
			break;
			//ÉñÖ®±ùÈÐ
		case SKILL_PLAY_P_ICE:
			if (point)
			{
				SkillPlaySound(SKILL_SOUND_SKILL_RAGE_OF_ZECRAM2, pX, pY, pZ);
				AssaP_IceEffect(this, chrAttackTarget);
				SkillPlaySound(SKILL_SOUND_SKILL_VENOM_SPEAR2, pX, pY, pZ);

				if (lpCurPlayer == this)
				{
					cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, AttackSkil, TRUE);
					if (!cnt)
						lpCurPlayer->AttackCritcal = -1;
					else
						lpCurPlayer->AttackCritcal = 0;
				}
			}
			break;
			//±©·çÑ©
		case SKILL_PLAY_S_PRMIEL:
			if (chrAttackTarget && point)
			{
				SkillIceMeteorite(chrAttackTarget, point);
				SkillPlaySound(SKILL_SOUND_SKILL_METEO1, pX, pY, pZ);
			}
			break;
			//ÌìÅ®É¢»¨
		case SKILL_PLAY_B_KRISHNA:
			if (point)
			{
				Assa_KrishnaEffect(this);
				sinEffect_Krishna(this, B_Krishna_Time[point - 1]);
				if (lpCurPlayer == this)
					dwB_Krishna_Time = dwPlayTime + B_Krishna_Time[point - 1] * 1000;
			}
			break;
		}
		break;
		//´Ì¿Í
	case CHARACTERCLASS_Assassin:
		switch (SkillCode)
		{
			//´Ì»÷
		case SKILL_PLAY_STRINGER:
			if (chrAttackTarget && MotionEvent == 2)
			{
				AssaParticle_Effect("Stingger", chrAttackTarget, 0);
				if (lpCurPlayer == this)
				{
					cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, AttackSkil, TRUE);
					if (!cnt)
						AttackCritcal = -1;
					else
					{
						DamageExp(chrAttackTarget, cnt);
						AttackCritcal = 0;
					}
				}
			}
			break;
			//ÉÁ»÷
		case SKILL_PLAY_RUNNING_HIT:
			if (chrAttackTarget)
			{
				AssaParticle_Effect("RunningHit", chrAttackTarget, 0);
				if (lpCurPlayer == this)
				{
					cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, AttackSkil, TRUE);
					if (!cnt)
						AttackCritcal = -1;
					else
					{
						DamageExp(chrAttackTarget, cnt);
						AttackCritcal = 0;
					}
				}
			}
			break;
			//Èõµã¹¥»÷
		case SKILL_PLAY_WISP:
			if (point && chrAttackTarget && MotionEvent == 1)
			{
				AssaCodeSkillEffect("Wisp2", chrAttackTarget, Wisp_Time[point - 1], SKILL_WISP);
				if (lpCurPlayer == this)
					dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, AttackSkil, TRUE);
			}
			break;
			//¶¾ÑÀÁ¬»÷
		case SKILL_PLAY_VENOM_THORN:
			if (chrAttackTarget)
			{
				AssaParticle_Effect("VenomThrone", chrAttackTarget, 0);
				if (lpCurPlayer == this)
				{
					cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, AttackSkil, TRUE);
					if (!cnt)
						AttackCritcal = -1;
					else
					{
						DamageExp(chrAttackTarget, cnt);
						AttackCritcal = 0;
					}
				}
			}
			break;
			//Ãô½ÝÖ®Á¦
		case SKILL_PLAY_ALAS:
			if (point && MotionEvent == 1)
			{
				if (cSkill.SearchContiueSkillCODE(SKILL_ALAS))
				{
					AssaCodeSkillEffect("Alas", this, Alas_Time[point - 1], SKILL_ALAS);
					if (lpCurPlayer == this)
					{
						SendPartySkillToServer(SKILL_PLAY_ALAS, point, 350, 0, 0, 0, 0);
						dwAlasTime = dwPlayTime + Alas_Time[point - 1] * 1000;
					}
				}
			}
			break;
			//Áé»êÕðº³
		case SKILL_PLAY_SOUL_SHOCK:
			if (point && MotionEvent == 1)
			{
				AssaParticle_Effect("SoulShock", this, SKILL_SOUL_SHOCK);
				if (lpCurPlayer == this)
				{
					dm_SelectRange(pX, pY, pZ, Soul_Shock_Area[point - 1], FALSE);
					dm_SendRangeDamage(pX, pY, pZ, 0, 0, 0, 0, 0, AttackSkil);
				}
			}
			break;
			//·É½£Ö®Îè
		case SKILL_PLAY_SORE_SWORD:
			if (chrAttackTarget)
			{
				AssaParticle_Effect("SoreSword", chrAttackTarget, 0);
				if (lpCurPlayer == this)
				{
					cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, AttackSkil, TRUE);
					if (!cnt)
						AttackCritcal = -1;
					else
					{
						DamageExp(chrAttackTarget, cnt);
						AttackCritcal = 0;
					}
				}
			}
			break;
			//ÌøÕ¶
		case SKILL_PLAY_BEAT_UP:
			if (chrAttackTarget)
			{
				AssaParticle_Effect("BeatUp", chrAttackTarget, 0);
				if (lpCurPlayer == this)
				{
					cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, AttackSkil, TRUE);
					if (!cnt)
						AttackCritcal = -1;
					else
					{
						DamageExp(chrAttackTarget, cnt);
						AttackCritcal = 0;
					}
				}
			}
			break;
			//Ãô½Ý´óÊ¦
		case SKILL_PLAY_INPES:
			if (point && MotionEvent == 1)
			{
				AssaCodeSkillEffect("Inpes", this, Inpes_Time[point - 1], SKILL_INPES);
				dwInpesTime = dwPlayTime + Inpes_Time[point - 1] * 1000;
			}
			break;
			//ÖÂÃ¤
		case SKILL_PLAY_BLIND:
			if (point && MotionEvent == 1)
			{
				if (lpCurPlayer == this)
				{
					PlayVanish = Deception_Time[point - 1] * 70;
					PlayVague = 0;
					SendProcessSKillToServer(SKILL_PLAY_BLIND, point, 0, 0);
				}
			}
			break;
			//±ù¶³Ö®ÈÐ
		case SKILL_PLAY_FROST_WIND:
			if (chrAttackTarget)
			{
				AssaParticle_Effect("FrostWindAttack", chrAttackTarget, 0);
				if (lpCurPlayer == this)
				{
					cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, AttackSkil, TRUE);
					if (!cnt)
						AttackCritcal = -1;
					else
					{
						DamageExp(chrAttackTarget, cnt);
						AttackCritcal = 0;
					}
				}
			}
			break;
			//ÎÁÒßÖ®ÈÐ
		case SKILL_PLAY_POLLUTE:
			if (point && MotionEvent == 2)
			{
				AssaParticle_Effect("PollutedAttack", this, 0);
				if (lpCurPlayer == this)
				{
					dm_SelectRange(pX, pY, pZ, Pollute_Area[point - 1], FALSE);
					dm_SendRangeDamage(pX, pY, pZ, 0, 0, 0, 0, 0, AttackSkil);
				}
			}
			break;
			//Ó°×ÓÉÁ»÷
		case SKILL_PLAY_PASTING_SHADOW:
			if (chrAttackTarget)
			{
				AssaParticle_Effect("PastingShadowAttack", chrAttackTarget, 0);
				if (lpCurPlayer == this)
				{
					cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, AttackSkil, TRUE);
					if (!cnt)
						AttackCritcal = -1;
					else
					{
						DamageExp(chrAttackTarget, cnt);
						AttackCritcal = 0;
					}
				}
			}
			break;
			//Ó°×Ó»ðÑæ
		case SKILL_PLAY_SHADOW_BOMB:
			if (point && MotionEvent == 1)
			{
				AssaParticle_Effect("ShadowBomb", this, 0);
				if (lpCurPlayer == this)
				{
					dm_SelectRange(pX, pY, pZ, Shadow_Bomb_Area[point - 1], FALSE);
					dm_SendRangeDamage(pX, pY, pZ, 0, 0, 0, 0, 0, AttackSkil);
				}
			}
			break;
			//µØÁÑÕ¶
		case SKILL_PLAY_RISING_SLASH:
			if (chrAttackTarget && MotionEvent == 1)
			{
				AssaParticle_Effect("RisingSlash2", chrAttackTarget, 0);
				if (lpCurPlayer == this)
				{
					cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, AttackSkil, TRUE);
					if (!cnt)
						AttackCritcal = -1;
					else
					{
						DamageExp(chrAttackTarget, cnt);
						AttackCritcal = 0;
					}
				}
			}
			break;
			//ÃÍÁú°ÚÎ²
		case SKILL_PLAY_VIOLENT_STUB:
			if (chrAttackTarget)
			{
				switch (MotionEvent)
				{
				case 1:
					AssaParticle_Effect("ViolenceStab2", chrAttackTarget, 0);
					break;
				case 2:
					AssaParticle_Effect("ViolenceStab3", chrAttackTarget, 0);
					break;
				}
				if (lpCurPlayer == this)
				{
					cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, AttackSkil, TRUE);
					if (!cnt)
						AttackCritcal = -1;
					else
					{
						DamageExp(chrAttackTarget, cnt);
						AttackCritcal = 0;
					}
				}
			}
			break;
			//·ç±©Ö®ÈÐ
		case SKILL_PLAY_SHADOW_STORM:
			if (chrAttackTarget && MotionEvent == 1)
			{
				AssaParticle_Effect("Storm", chrAttackTarget, 0);
				if (lpCurPlayer == this)
				{
					dm_SelectRange(pX, pY, pZ, Shadow_Storm_Area[point - 1], FALSE);
					dm_SendRangeDamage(pX, pY, pZ, 0, 0, 0, 0, 0, AttackSkil);
				}
			}
			break;
		}
		break;
		//ÈøÂú
	case CHARACTERCLASS_Shaman:
		switch (SkillCode)
		{
			//°µºÚÉÁµç
		case SKILL_PLAY_DARK_BOLT:
			if (chrAttackTarget)
			{
				AssaDarkWaveEffect(this, chrAttackTarget, SKILL_DARK_BOLT);
				if (lpCurPlayer == this)
				{
					cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, AttackSkil, TRUE);
					if (cnt)
						DamageExp(chrAttackTarget, cnt);
				}
			}
			break;
			//°µºÚ²¨ÀË
		case SKILL_PLAY_DARK_WAVE:
			if (chrAttackTarget && MotionEvent)
			{
				AssaDarkWaveEffect(this, chrAttackTarget, SKILL_DARK_WAVE);
				if (lpCurPlayer == this)
				{
					cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, AttackSkil, TRUE);
					if (cnt)
						DamageExp(chrAttackTarget, cnt);
				}
			}
			break;
			//×çÖäÀ×»÷
		case SKILL_PLAY_INERTIA:
			if (point && chrAttackTarget && MotionEvent == 1)
			{
				SkillPlaySound(SKILL_SOUND_SKILL_CURSE_LAZY2, pX, pY, pZ);
				if (lpCurPlayer == this)
				{
					dm_SelectRange(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, Inertia_Area[point - 1], TRUE);
					dm_SendRangeDamage(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 0, 0, 0, 0, 0, AttackSkil);
				}
			}
			break;
			//¾«ÉñÖäÊõ
		case SKILL_PLAY_SPIRITUAL_FLARE:
			if (point && chrAttackTarget && MotionEvent == 1)
			{
				SkillPlaySound(SKILL_SOUND_SKILL_SPIRITUAL_FLARE2, chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ);
				AssaParticle_Effect("SpiritualFlare", chrAttackTarget, 0);
				if (lpCurPlayer == this)
				{
					dm_SelectRange(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, Spiritual_Flare_Area[point - 1], TRUE);
					dm_SendRangeDamage(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 0, 0, 0, 0, 0, AttackSkil);
				}
			}
			break;
			//Áé»ê¼ÏËø
		case SKILL_PLAY_SPIRITUAL_MANACLE:
			if (chrAttackTarget && MotionEvent == 1)
			{
				SkillPlaySound(SKILL_SOUND_SKILL_SPIRITUAL_MANACLE2, chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ);
				AssaParticle_Effect("SoulManacle", chrAttackTarget, 0);
				if (lpCurPlayer == this)
					dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, AttackSkil, FALSE);
			}
			break;
			//ÁÔÈ¡
		case SKILL_PLAY_CHASING_HUNT:
			if (point && chrAttackTarget && MotionEvent == 1)
			{
				SkillPlaySound(SKILL_SOUND_SKILL_CHASING_HUNT2, pX, pY, pZ);
				AssaParticle_Effect("ChasingHunt", chrAttackTarget, 0);
				if (lpCurPlayer == this)
				{
					dm_SelectRange(pX, pY, pZ, Chasing_Hunt_Sight[point - 1], TRUE);
					dm_SendRangeDamage(pX, pY, pZ, 0, 0, 0, 0, 0, AttackSkil);
				}
			}
			break;
			//Âõ¿Ë¶û
		case SKILL_PLAY_ADVENT_MIGAL:
			if (point && MotionEvent == 1)
			{
				SkillPlaySound(SKILL_SOUND_SKILL_SKILL_ADVENT_MIGAL2, pX, pY, pZ);
				SkillCelestialMusPel(this, (float)Advent_Migal_Time[point - 1], 0, SKILL_ADVENT_MIGAL);
				if (lpCurPlayer == this)
				{
					SendPartySkillToServer(SKILL_PLAY_ADVENT_MIGAL, point, 400, 0, 0, 0, 0);
					dwAdvent_Migal_Time = dwPlayTime + Advent_Migal_Time[point - 1] * 1000;
				}
			}
			break;
			//ÆíÓêÊ¦
		case SKILL_PLAY_RAINMAKER:
			if (point && MotionEvent == 1)
			{
				SkillPlaySound(SKILL_SOUND_SKILL_SKILL_RAIN_MAKER2, pX, pY, pZ);
				AssaCodeSkillEffect("RainMaker2", this, Rainmaker_Time[point - 1], SKILL_RAIN_MAKER);
				if (lpCurPlayer == this)
				{
					SendProcessSKillToServer(SKILL_PLAY_RAINMAKER, point, 0, 0);
					dwRainmaker_Time = dwPlayTime + Rainmaker_Time[point - 1] * 1000;
				}
			}
			break;
			//Â½µØÁé»ê
		case SKILL_PLAY_LAND_OF_GHOST:
			if (point && MotionEvent == 1)
			{
				SkillPlaySound(SKILL_SOUND_SKILL_LAND_OF_GHOST2, pX, pY, pZ);
				AssaParticle_Effect("LandOfGhost2", this, 0);
				if (lpCurPlayer == this)
				{
					dm_SelectRange(pX, pY, pZ, Phantom_Call_Area[point - 1], FALSE);
					dm_SendRangeDamage(pX, pY, pZ, 0, 0, 0, 0, 0, AttackSkil);
				}
			}
			break;
			//¹í»ìÖØ»Ø
		case SKILL_PLAY_HAUNT:
			if (chrAttackTarget && MotionEvent == 1)
			{
				SkillPlaySound(SKILL_SOUND_SKILL_HAUNT2, chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ);
				AssaParticle_Effect("Haunt1", chrAttackTarget, 0);
				AssaParticle_Effect("Haunt2", this, 0);
				if (lpCurPlayer == this)
					dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, AttackSkil, FALSE);
			}
			break;
			//×¥ÆÆ
		case SKILL_PLAY_SCRATCH:
			if (chrAttackTarget && MotionEvent < 3)
			{
				SkillPlaySound(SKILL_SOUND_SKILL_SCRATCH2, chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ);
				switch (MotionEvent)
				{
				case 1:
					AssaParticle_Effect("Scratch1", chrAttackTarget, 0);
					break;
				case 2:
					AssaParticle_Effect("Scratch2", chrAttackTarget, 0);
					break;
				}
				if (lpCurPlayer == this)
				{
					cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, AttackSkil, FALSE);
					if (cnt)
						DamageExp(chrAttackTarget, cnt);
				}
			}
			break;
			//ÊÈÑªÖ®Ò¹
		case SKILL_PLAY_CRIMSON_KNIGHT:
			if (point && MotionEvent == 1)
			{
				SkillPlaySound(SKILL_SOUND_SKILL_RECALL_BLOODYKNIGHT2, pX, pY, pZ);
				if (lpCurPlayer == this)
					SendProcessSKillToServer(SKILL_PLAY_CRIMSON_KNIGHT, point, 0, 0);
			}
			break;
			//ÉóÅÐ
		case SKILL_PLAY_JUDGEMENT:
			if (chrAttackTarget && MotionEvent)
			{
				SkillPlaySound(SKILL_SOUND_SKILL_JUDGEMENT2, chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ);
				auto sPosition = GetMoveLocation(0, 24 * fONE, 24 * fONE, 0, Angle.y, 0);
				Pos2.x = pX + sPosition.iX;
				Pos2.y = pY + sPosition.iY;
				Pos2.z = pZ + sPosition.iZ;

				Pos1.x = chrAttackTarget->pX;
				Pos1.y = chrAttackTarget->pY + 32 * fONE;
				Pos1.z = chrAttackTarget->pZ;

				ParkAssaParticle_Judgement(&Pos2, &Pos1);

				if (lpCurPlayer == this)
				{
					cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, AttackSkil, FALSE);
					if (cnt)
						DamageExp(chrAttackTarget, cnt);
				}
			}
			break;
			//Ã×µÂÀ¼´ï
		case SKILL_PLAY_ADVENT_MIDRANDA:
			if (point && MotionEvent == 1)
			{
				SkillPlaySound(SKILL_SOUND_SKILL_ADVENT_MIDRANDA2, pX, pY, pZ);
				SkillCelestialMusPel(this, (float)Advent_Midranda_Time[point - 1], 0, SKILL_ADVENT_MIDRANDA);
				if (lpCurPlayer == this)
				{
					SendPartySkillToServer(SKILL_PLAY_ADVENT_MIDRANDA, point, 400, 0, 0, 0, 0);
					dwAdvent_Midranda_Time = dwPlayTime + Advent_Midranda_Time[point - 1] * 1000;
				}
			}
			break;
			//ÐñÈÕ¶«Éý
		case SKILL_PLAY_MOURNING_PRAY:
			if (point && MotionEvent == 1)
			{
				SkillPlaySound(SKILL_SOUND_SKILL_MOURNING_OF_PRAY2, pX, pY, pZ);
				AssaParticle_Effect("MourningOfPreyHit", this, 0);
				if (lpCurPlayer == this)
				{
					SendPartySkillToServer(SKILL_PLAY_MOURNING_PRAY, point, 400, 0, 0, 0, 0);
					dm_SelectRange(pX, pY, pZ, Mourning_Pray_Area[point - 1], FALSE);
					dm_SendRangeDamage(pX, pY, pZ, 0, 0, 0, 0, 0, AttackSkil);
				}
			}
			break;
			//ÖäÊõÐÅÑö
		case SKILL_PLAY_CREED:
			if (point && MotionEvent == 1)
			{
				AssaCodeSkillEffect("CreedKeep", this, Creed_Time[point - 1], SKILL_CREED);
				if (lpCurPlayer == this)
					dwCreed_Time = dwPlayTime + Creed_Time[point - 1] * 1000;
			}
			break;
			//×çÖäÖ®Á¦
		case SKILL_PLAY_PRESS_DEITY:
			if (point && MotionEvent)
			{
				Pos2.x = chrAttackTarget->pX;
				Pos2.y = chrAttackTarget->pY;
				Pos2.z = chrAttackTarget->pZ;

				SkillArchMageMeteo(&Pos2, SKILL_PRESS_OF_DEITY);

				if (lpCurPlayer == this)
				{
					dm_SelectRange(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, Press_Deity_Area[point - 1], FALSE);
					dm_SendRangeDamage(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 0, 0, 0, 0, 0, AttackSkil);
				}
			}
			break;
			//ËÀÍöÖ®×¦
		case SKILL_PLAY_PHANTOM_NAIL:
			if (point && chrAttackTarget && MotionEvent)
			{
				SkillPlaySound(SKILL_SOUND_SKILL_CHOSTY_NAIL2, chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ);
				AssaParticle_Effect("GhostyNail2", chrAttackTarget, 0);
				if (lpCurPlayer == this)
				{
					dm_SelectRange(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, Phantom_Nail_Area[point - 1], FALSE);
					dm_SendRangeDamage(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 0, 0, 0, 0, 0, AttackSkil);
				}
			}
			break;
		}
		break;
	}
	return TRUE;
}
int Unit::PlayAttackFromPosi(int ex, int ey, int ez, int Dist, int attack)
{
	int AtDist;
	int	dDist;
	int ay;

	ay = abs(pY - ey);

	if (iLoadedMapIndex >= 0 && STAGE_MAP[iLoadedMapIndex]->iMapID == rsCASTLE_FIELD)
	{
		if (ShootingMode)
		{
			if (ay > 80 * fONE)
				return NULL;
		}
		else
		{
			if (ay > 52 * fONE)
				return NULL;
		}

		if ((pZ<CastleBattleZone_DoorLineZ && ez>CastleBattleZone_DoorLineZ) || (pZ > CastleBattleZone_DoorLineZ && ez < CastleBattleZone_DoorLineZ))
		{
			if (rsBlessCastle.CastleMode && rsBlessCastle.DefenceLevel == 0)
				return NULL;
		}
	}
	else
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
				if (sCharacterData.iType != CHARACTERTYPE_Player || GAMECHARACTER->IsStageVillage() == FALSE)
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
int Unit::SetShootingMode()
{
	if ((dwActionItemCode & sinITEM_MASK2) == sinWD1)
		return ShootingMode ^= TRUE;
	return FALSE;
}

//¸ð¼ÇºÎ·Á ÃÊ±âÈ­
int InitMotionBlur()
{
	int cnt;
	int TlCnt;
	float fVCnt, fVCnt2;
	float fBlurLevel;
	int MbCnt, MvCnt;


	MatMBlur = CreateTextureMaterial("image\\MotionMask.bmp", NULL, TRUE, FALSE, SMMAT_BLEND_ADDCOLOR);

	///////////////////////// 32´Ü°è /////////////////////////

	fBlurLevel = 1.0f / 32;
	TlCnt = 0;
	fVCnt = 0;
	fVCnt2 = 0 + fBlurLevel;

	for (cnt = 0; cnt < 32; cnt++) {

		smTexLinkMotionBlur[TlCnt].NextTex = 0;
		smTexLinkMotionBlur[TlCnt].hTexture = 0;
		smTexLinkMotionBlur[TlCnt].v[0] = fVCnt;
		smTexLinkMotionBlur[TlCnt].v[1] = fVCnt;
		smTexLinkMotionBlur[TlCnt].v[2] = fVCnt2;
		smTexLinkMotionBlur[TlCnt].u[0] = 0;
		smTexLinkMotionBlur[TlCnt].u[1] = 1;
		smTexLinkMotionBlur[TlCnt].u[2] = 0;

		TlCnt++;

		smTexLinkMotionBlur[TlCnt].NextTex = 0;
		smTexLinkMotionBlur[TlCnt].hTexture = 0;
		smTexLinkMotionBlur[TlCnt].v[0] = fVCnt2;
		smTexLinkMotionBlur[TlCnt].v[1] = fVCnt;
		smTexLinkMotionBlur[TlCnt].v[2] = fVCnt2;
		smTexLinkMotionBlur[TlCnt].u[0] = 0;
		smTexLinkMotionBlur[TlCnt].u[1] = 1;
		smTexLinkMotionBlur[TlCnt].u[2] = 1;

		TlCnt++;

		fVCnt = fVCnt2;
		fVCnt2 += fBlurLevel;

	}

	MbCnt = 0;
	MvCnt = 0;

	ZeroMemory(MbVertex, sizeof(smVERTEX) * 64);

	for (cnt = 0; cnt < 32; cnt++) {

		MbFace[MbCnt].lpTexLink = &smTexLinkMotionBlur[MbCnt];
		MbFace[MbCnt].v[0] = MvCnt;
		MbFace[MbCnt].v[1] = MvCnt + 1;
		MbFace[MbCnt].v[2] = MvCnt + 2;
		MbFace[MbCnt].v[3] = MatMBlur;
		MbCnt++;

		MbFace[MbCnt].lpTexLink = &smTexLinkMotionBlur[MbCnt];
		MbFace[MbCnt].v[0] = MvCnt + 2;
		MbFace[MbCnt].v[1] = MvCnt + 1;
		MbFace[MbCnt].v[2] = MvCnt + 3;
		MbFace[MbCnt].v[3] = MatMBlur;
		MbCnt++;
		MvCnt += 2;

	}


	///////////////////////// 16´Ü°è /////////////////////////


	fBlurLevel = 1.0f / 16;
	TlCnt = 0;
	fVCnt = 0;
	fVCnt2 = 0 + fBlurLevel;

	for (cnt = 0; cnt < 16; cnt++) {

		smTexLinkMotionBlur2[TlCnt].NextTex = 0;
		smTexLinkMotionBlur2[TlCnt].hTexture = 0;
		smTexLinkMotionBlur2[TlCnt].v[0] = fVCnt;
		smTexLinkMotionBlur2[TlCnt].v[1] = fVCnt;
		smTexLinkMotionBlur2[TlCnt].v[2] = fVCnt2;
		smTexLinkMotionBlur2[TlCnt].u[0] = 0;
		smTexLinkMotionBlur2[TlCnt].u[1] = 1;
		smTexLinkMotionBlur2[TlCnt].u[2] = 0;

		TlCnt++;

		smTexLinkMotionBlur2[TlCnt].NextTex = 0;
		smTexLinkMotionBlur2[TlCnt].hTexture = 0;
		smTexLinkMotionBlur2[TlCnt].v[0] = fVCnt2;
		smTexLinkMotionBlur2[TlCnt].v[1] = fVCnt;
		smTexLinkMotionBlur2[TlCnt].v[2] = fVCnt2;
		smTexLinkMotionBlur2[TlCnt].u[0] = 0;
		smTexLinkMotionBlur2[TlCnt].u[1] = 1;
		smTexLinkMotionBlur2[TlCnt].u[2] = 1;

		TlCnt++;

		fVCnt = fVCnt2;
		fVCnt2 += fBlurLevel;

	}

	MbCnt = 0;
	MvCnt = 0;

	ZeroMemory(MbVertex, sizeof(smVERTEX) * 32);

	for (cnt = 0; cnt < 16; cnt++) {

		MbFace2[MbCnt].lpTexLink = &smTexLinkMotionBlur2[MbCnt];
		MbFace2[MbCnt].v[0] = MvCnt;
		MbFace2[MbCnt].v[1] = MvCnt + 1;
		MbFace2[MbCnt].v[2] = MvCnt + 2;
		MbFace2[MbCnt].v[3] = MatMBlur;
		MbCnt++;

		MbFace2[MbCnt].lpTexLink = &smTexLinkMotionBlur2[MbCnt];
		MbFace2[MbCnt].v[0] = MvCnt + 2;
		MbFace2[MbCnt].v[1] = MvCnt + 1;
		MbFace2[MbCnt].v[2] = MvCnt + 3;
		MbFace2[MbCnt].v[3] = MatMBlur;
		MbCnt++;
		MvCnt += 2;

	}

	return TRUE;
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




scITEM::scITEM()
{
	Init();
}

scITEM::~scITEM()
{
	Close();
}

void scITEM::Init()
{
	ZeroMemory(&Head, sizeof(scITEM));
}

int scITEM::Close()
{
	Flag = 0;

	if (lpDinaPattern)
	{
		AddRemoveDynPattern(lpDinaPattern);
		lpDinaPattern = 0;
	}

	Pattern = 0;

	return TRUE;
}

//ÆÐÅÏ¼³Á¤
int scITEM::SetPattern(smPAT3D *pat)
{
	Pattern = pat;
	return TRUE;
}


//À§Ä¡¼³Á¤
int scITEM::SetPosi(int x, int y, int z)
{
	int py2 = 0;

	pX = x;
	pZ = z;
	pY = y;

	if (pY == 0)
	{
		if (smGameStage[0])
			pY = smGameStage[0]->GetHeight(pX, pZ);

		if (smGameStage[1])
			py2 = smGameStage[1]->GetHeight(pX, pZ);

		if (py2 > pY)
			pY = py2;
	}

	return TRUE;
}


//¼ö½ÅµÈ ¾ÆÀÌÅÛ ¼³Á¤
int scITEM::SetTransItem(TRANS_ITEM *lpTransItem)
{
	dwLastTransTime = dwPlayTime;

	Flag = TRUE;

	lstrcpy(szName, lpTransItem->szName);
	SetPosi(lpTransItem->x, lpTransItem->y, lpTransItem->z);
	lpStgArea = lpTransItem->lpStgArea;

	ItemCode = lpTransItem->ItemCode;


	Angle.y = ((pX + pZ) >> 2)&ANGCLIP;

	if (sinGetItemInfo(ItemCode, szModelName) == FALSE || ItemCode == 0)
		lstrcpy(szModelName, "char\\flag\\flag.ini");

	if (!PatLoading)
		AddLoaderItem(this, szModelName);

	return TRUE;
}




#define ITEM_TRANS_LIMIT_TIME		10000

int scITEM::Draw()
{
	POINT3D CameraPosi, CameraAngle;
	POINT3D angle;

	int r, g, b;
	int scale;

	if (ItemCode == 0 && !DisplayDebug)
		return FALSE;

	if (!DisplayFlag || !Pattern)
		return FALSE;

	if (dwPlayTime > (dwLastTransTime + ITEM_TRANS_LIMIT_TIME))
	{
		Close();
		return FALSE;
	}

	CameraPosi.x = smCHAR_CameraX;
	CameraPosi.y = smCHAR_CameraY;
	CameraPosi.z = smCHAR_CameraZ;

	CameraAngle.x = smCHAR_CameraAngX;
	CameraAngle.y = smCHAR_CameraAngY;
	CameraAngle.z = smCHAR_CameraAngZ;

	memcpy(&angle, &Angle, sizeof(POINT3D));

	Posi.x = pX;
	Posi.y = pY + 6 * fONE;
	Posi.z = pZ;

	int	BlinkFlag;

	BlinkFlag = FALSE;

	if ((ItemCode&sinITEM_MASK1) == sinITEM_WEAPON)
		angle.x = ANGLE_90;

	if (ItemCode && (dwPlayTime & 0x80))
		BlinkFlag = TRUE;


	//SOD ÇÊµåÀÇ Æ¯Á¤ ¾ÆÀÌÅÛÀÇ °æ¿ì Å©±âº¯ÇüÀ¸·Î °­Á¶
	if (lpCurPlayer->iLoadedMapIndex >= 0 && STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == rsSOD_FIELD)
	{
		if ((ItemCode&sinITEM_MASK2) == sinPM1 || (ItemCode&sinITEM_MASK2) == sinSD2)
		{
			scale = (dwPlayTime >> 2) & 0x1FF;

			if ((scale & 0x100) != 0)
				scale = fONE - (scale & 0xFF);

			if ((ItemCode&sinITEM_MASK2) == sinPM1)
				scale *= 3;

			smRender.ObjectVertexScale = scale + fONE;
		}
	}

	if (BlinkFlag)
	{
		r = smRender.Color_R;
		g = smRender.Color_G;
		b = smRender.Color_B;

		smRender.Color_R += 100;
		smRender.Color_G += 100;
		smRender.Color_B += 100;

		Pattern->SetPosi(&Posi, &angle);
		Pattern->Frame = 0;
		Pattern->RenderD3D(&CameraPosi, &CameraAngle);

		smRender.Color_R = r;
		smRender.Color_G = g;
		smRender.Color_B = b;
	}
	else
	{
		Pattern->SetPosi(&Posi, &angle);
		Pattern->Frame = 0;
		Pattern->RenderD3D(&CameraPosi, &CameraAngle);
	}

	smRender.ObjectVertexScale = 0;

	return TRUE;
}


//////////////////////////////// ¹«Àû¸ðµå ¾Ç¿ë ´ëºñ °¨½ÃÇÔ¼ö ////////////////////////////

DWORD	Ptect_RestartCounter = 0;
DWORD	Ptect_RestartMask = 0;

//°ø°Ý ¸¶Å© º¸¾È Ä«¿îÅÍ Áõ°¡
int	Ptect_IncAttackCount(int Flag)
{
	DWORD	rc;
	smTRANS_COMMAND	smTransCommand;

	rc = Ptect_RestartCounter ^ Ptect_RestartMask;
	Ptect_RestartMask = dwPlayTime;

	switch (Flag) {
	case -1:
		rc = 0;
		break;
	case 0:
		rc++;
		break;
	}

	if (rc > 160) {
		//¼­¹ö¿¡ °æ°í º¸³¿
		smTransCommand.code = smTRANSCODE_WARNING_BLINK_ATT;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = rc;
		smTransCommand.LParam = 0;
		smTransCommand.SParam = 0;
		smTransCommand.EParam = 0;

		SENDPACKETL(&smTransCommand);

		rc = 0;
	}

	rc = rc ^ Ptect_RestartMask;
	Ptect_RestartCounter = rc;

	return TRUE;
}

//°ø°Ý ¸¶Å© º¸¾È Ä«¿îÅÍ ¾ò±â
DWORD Ptect_GetAttackCount()
{
	DWORD	rc;
	rc = Ptect_RestartCounter ^ Ptect_RestartMask;
	Ptect_RestartMask = dwPlayTime;
	Ptect_RestartCounter = rc ^ Ptect_RestartMask;

	return rc;
}


//Ä³½½ ¸¶½ºÅÍ ¾÷µ¥ÀÌÆ®
int UpdateCastleMasterClan(DWORD dwMasterClan)
{
	int cnt;

	SetClanMaster_Player(dwMasterClan);

	for (cnt = 0; cnt < MAX_UNITS; cnt++) 
	{
		if (chrOtherPlayer[cnt].bActive && chrOtherPlayer[cnt].iID) 
		{
			if (chrOtherPlayer[cnt].sCharacterData.iClanID && GetClanCode(chrOtherPlayer[cnt].sCharacterData.iClanID) == dwMasterClan)
				lpCurPlayer->Clan_CastleMasterFlag = TRUE;
			else
				lpCurPlayer->Clan_CastleMasterFlag = FALSE;
		}
	}

	return TRUE;
}

//ÇÃ·¹ÀÌ¾î Å¬·£ ¸¶½ºÅÍ È®ÀÎ
int SetClanMaster_Player(DWORD dwMasterClan)
{
	if (lpCurPlayer->sCharacterData.iClanID && GetClanCode(lpCurPlayer->sCharacterData.iClanID) == dwMasterClan)
		lpCurPlayer->Clan_CastleMasterFlag = TRUE;
	else
		lpCurPlayer->Clan_CastleMasterFlag = FALSE;

	return lpCurPlayer->Clan_CastleMasterFlag;

}