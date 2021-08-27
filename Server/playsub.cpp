#include "StdAfx.h"
#include "character.h"
#include "playmain.h"
#include "fileread.h"
#include "netplay.h"
#include "effectsnd.h"

#include "record.h"
#include "playsub.h"
#include "resource.h"

#include "srcserver\\onserver.h"

extern HINSTANCE hinst;

int rsCheckHardCoreEventArea(int x, int y, int z);
extern POINT3D	rsHardCoreEventOpenPos[7][3];

int	CodeXorLife = 0;
int	CodeXorMana = 0;
int	CodeXorStamina = 0;
int	CodeXorMoney = 0;

#define	PLAYSUB_CHECKRESULT		1884018394

DWORD	dwPlaySub_CheckResult = PLAYSUB_CHECKRESULT;

static char *szArmorDirectory = "char\\tmABCD\\";
static char *szNpcDirectory = "char\\npc\\";

#include "playmodel.h"

int ArmorJobNum[11] = { 0,1,0,3,2,5,4,7,6,8,9 };

int	PlayerArmor = 0;
int PlayerArmorFlag = 0;

#define TEMP_DYNPAT_MAX		2048 * 4

smDPAT	*DynTempPat[TEMP_DYNPAT_MAX];

int DynTempPatCnt = 0;

int	PlayUsed_Resurrection = 0;


DWORD	dwSafeCodeSum;

BYTE	dwAsmJmpCode = 0xE0;

DWORD	dwStartFuncPoint = 0;
DWORD	dwFuncLen = 0;
DWORD	dwFuncSafeMemCount;
DWORD	dwFuncSafeMemCode;

DWORD	dwFuncChkTime = 0;
DWORD	dwFuncSafeCode = 0;

char	*lpFuncBackupBuff = 0;

extern char *szBangImage;

DWORD	*lpCodeVram = 0;


int Code_VRamBuffOpen()
{

	lpCodeVram = new DWORD[256];

	return (DWORD)lpCodeVram;

}
int Code_VramClear()
{
	lpCodeVram[0] = 777;
	lpCodeVram[1] = 0;
	lpCodeVram[2] = 777;
	lpCodeVram[3] = 0;

	return TRUE;
}
int Code_VramSave(DWORD Param1, DWORD Param2, DWORD Param3)
{
	DWORD	dwTime;

	if (lpCodeVram)
	{
		dwTime = GetCurrentTime();

		lpCodeVram[3] = dwTime;
		lpCodeVram[0] = Param1 ^ dwTime;
		lpCodeVram[1] = Param2 ^ dwTime;
		lpCodeVram[2] = Param3 ^ dwTime;
	}

	return TRUE;
}
int Code_VramLoad(DWORD *Param1, DWORD *Param2, DWORD *Param3)
{
	*Param1 = lpCodeVram[0] ^ lpCodeVram[3];
	*Param2 = lpCodeVram[1] ^ lpCodeVram[3];
	*Param3 = lpCodeVram[2] ^ lpCodeVram[3];

	return TRUE;
}

DWORD GetMemBase(DWORD &dwMemPosition)
{
	HMODULE hMod;
	PIMAGE_DOS_HEADER pDosHeader;
	PIMAGE_NT_HEADERS pNtHeader;
	PIMAGE_FILE_HEADER pFileHeader;
	PIMAGE_OPTIONAL_HEADER pOptionalHeader;
	PIMAGE_SECTION_HEADER pSectionHeader;
	DWORD ImageBase;
	DWORD dwSectionNum;

	hMod = GetModuleHandle(0);

	if (hMod)
	{
		pDosHeader = (PIMAGE_DOS_HEADER)hMod;
		pNtHeader = (PIMAGE_NT_HEADERS)((ULONG)hMod + pDosHeader->e_lfanew);
		pFileHeader = &(pNtHeader->FileHeader);
		pOptionalHeader = &(pNtHeader->OptionalHeader);
		ImageBase = pOptionalHeader->ImageBase;
		pSectionHeader = IMAGE_FIRST_SECTION(pNtHeader);
		dwSectionNum = pFileHeader->NumberOfSections;

		for (DWORD i = 0; i < dwSectionNum; i++, pSectionHeader++)
		{
			if (lstrcmpi((char *)pSectionHeader->Name, ".text") == 0)
			{
				dwMemPosition = (DWORD)(pSectionHeader->VirtualAddress) + ImageBase;

				return pSectionHeader->SizeOfRawData;
			}
		}
	}
	return 0;
}
DWORD Check_CodeSafe(DWORD dwStartFunc)
{
	BYTE	*lpFunc;
	DWORD	PointMin, PointMax;

	DWORD	dwCode, dwCnt;
	DWORD	dwLen;
	DWORD	*lpdwFunc;
	BYTE	JmpCode = 9;
	DWORD	dwCodeSeg;
	DWORD	dwCodeAddr;
	DWORD	dwHeaderPos = 0x30;

	JmpCode += dwAsmJmpCode;

	dwStartFunc = 0x4c11cc;

	lpFunc = (BYTE *)dwStartFunc;
	dwCodeSeg = dwStartFunc & 0xFFF00000;
	dwCodeAddr = dwStartFunc & 0x000FFFFF;

	lpdwFunc = (DWORD *)(dwCodeSeg + dwHeaderPos + 0xC);
	lpdwFunc = (DWORD *)(lpdwFunc[0] + dwCodeSeg);
	PointMax = lpdwFunc[0x4B] + dwCodeSeg;
	PointMin = dwCodeSeg + 0x1000;

	dwCode = 0;
	dwLen = (PointMax - PointMin) >> 2;
	if (dwLen > 200000) dwLen = 200000;

	lpdwFunc = (DWORD *)PointMin;

	dwStartFuncPoint = PointMin ^ (dwLen << 8);
	dwFuncLen = dwLen;

	for (dwCnt = 0; dwCnt < dwLen; dwCnt++)
		dwCode = dwCode + (lpdwFunc[dwCnt] * ((dwCnt & 0x3) + 1));

	DWORD FnCode;

	dwFuncChkTime = GetCurrentTime();
	FnCode = dwCode ^ ((dwFuncChkTime << 16) | (dwFuncChkTime & 0xFFFF));

	dwFuncSafeCode = FnCode;
	dwFuncSafeMemCount = 0;
	dwFuncSafeMemCode = 0;

	Code_VramSave(FnCode, dwFuncChkTime, dwCode);

	lpFunc = 0;
	lpdwFunc = 0;

	return dwCode;
}
DWORD	GetSafeCode()
{
	return dwFuncSafeCode ^ ((dwFuncChkTime << 16) | (dwFuncChkTime & 0xFFFF));
}
DWORD	GetSafeCode2()
{
	DWORD	dwCode, dwFnChkTime, dwFnSafeCode;
	DWORD	dwOriginal;

	Code_VramLoad(&dwCode, &dwFnChkTime, &dwFnSafeCode);

	dwOriginal = dwCode ^ ((dwFnChkTime << 16) | (dwFnChkTime & 0xFFFF));

	if ((dwOriginal^dwFnSafeCode) == 0)
		return dwOriginal;
	return FALSE;
}
int	LoadOftenMeshPattern(char *szFileName)
{

	DynTempPat[DynTempPatCnt] = smPattern.LoadCharactor(szFileName);
	if (DynTempPat[DynTempPatCnt])
	{
		DynTempPat[DynTempPatCnt]->UseCount = 99;
		DynTempPatCnt++;
		return TRUE;
	}

	return FALSE;
}

int	LoadOftenFullPattern()
{
	int cnt, cnt2;
	int	ErrorCount;
	char szBuff[128];

	ErrorCount = 0;

	for (cnt = 0; cnt < MAX_JOBNUM; cnt++)
	{
		for (cnt2 = 0; cnt2 < ARMOR_FILE_MAX; cnt2++)
		{
			lstrcpy(szBuff, szArmorDirectory);
			lstrcat(szBuff, szArmorNumFile[cnt][cnt2]);

			if (LoadOftenMeshPattern(szBuff) == FALSE)
				ErrorCount++;
		}
		for (cnt2 = 0; cnt2 < COSTME_ARMOR_FILE_MAX; cnt2++)
		{
			lstrcpy(szBuff, szArmorDirectory);
			lstrcat(szBuff, szCostmeArorNumFile[cnt][cnt2]);

			if (LoadOftenMeshPattern(szBuff) == FALSE)
				ErrorCount++;
		}
		for (cnt2 = 0; cnt2 < COSTME_NEW_ARMOR_FILE_MAX; cnt2++)
		{
			lstrcpy(szBuff, szArmorDirectory);
			lstrcat(szBuff, szCostmeNewArorNumFile[cnt][cnt2]);

			if (LoadOftenMeshPattern(szBuff) == FALSE)
				ErrorCount++;
		}
	}

	for (cnt = 0; cnt < FACE_MODEL_MAX; cnt++)
	{
		for (cnt2 = 0; cnt2 < HEAREPOTION_MAX; cnt2++)
		{
			if (LoadOftenMeshPattern(szModel_FighterFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
			if (LoadOftenMeshPattern(szModel_MechFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
			if (LoadOftenMeshPattern(szModel_ArcherFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
			if (LoadOftenMeshPattern(szModel_PikeFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
			if (LoadOftenMeshPattern(szModel_KnightFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
			if (LoadOftenMeshPattern(szModel_AtalantaFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
			if (LoadOftenMeshPattern(szModel_PristessFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
			if (LoadOftenMeshPattern(szModel_MagicanFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
			if (LoadOftenMeshPattern(szModel_AssaFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
			if (LoadOftenMeshPattern(szModel_ShamanFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
		}
	}

	HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;

	char	szFindPath[64];
	char	szFilePath[64];

	lstrcpy(szFindPath, szNpcDirectory);
	lstrcat(szFindPath, "*.ini");

	hFindHandle = FindFirstFile(szFindPath, &fd);
	if (hFindHandle != INVALID_HANDLE_VALUE)
	{
		while (TRUE)
		{
			lstrcpy(szFilePath, szNpcDirectory);
			lstrcat(szFilePath, fd.cFileName);

			LoadOftenMeshPattern(szFilePath);

			if (FindNextFile(hFindHandle, &fd) == FALSE)
				break;
		}
	}
	FindClose(hFindHandle);

	return ErrorCount;
}
char *szOftenNPC[] =
{
	0
};
int LoadFolder_Ini(char *szPath, char *szWildCard, char *szChgExt, int OftSave);

int Make_CharAll_SMD()
{
	LoadOftenFullPattern();
	LoadFolder_Ini("Char\\Npc", "*.ini", 0, 0);
	LoadFolder_Ini("Char\\Monster", "*.ini", 0, 0);

	return TRUE;
}
int LoadOftenNpc()
{
	LoadFolder_Ini("Char\\Npc", "*.inx", "ini", TRUE);

	return TRUE;
}
int LoadOftenFace()
{
	int cnt, cnt2;
	int ErrorCount = 0;

	for (cnt = 0; cnt < 6; cnt++)
	{
		for (cnt2 = 0; cnt2 < HEAREPOTION_MAX; cnt2++)
		{
			if (LoadOftenMeshPattern(szModel_FighterFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
			if (LoadOftenMeshPattern(szModel_MechFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
			if (LoadOftenMeshPattern(szModel_ArcherFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
			if (LoadOftenMeshPattern(szModel_PikeFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
			if (LoadOftenMeshPattern(szModel_KnightFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
			if (LoadOftenMeshPattern(szModel_AtalantaFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
			if (LoadOftenMeshPattern(szModel_PristessFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
			if (LoadOftenMeshPattern(szModel_MagicanFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
			if (LoadOftenMeshPattern(szModel_AssaFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
			if (LoadOftenMeshPattern(szModel_ShamanFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
		}
	}
	if (ErrorCount)
		return FALSE;

	return TRUE;

}
// 加载铠甲
int LoadOftenArmor()
{
	int cntW, cntH;
	char szName[128];

	for (cntH = 0; cntH < MAX_JOBNUM; cntH++)
	{
		for (cntW = 0; cntW < 18; cntW++)
		{
			if (cntW == 0 || cntW >= 10)
			{
				lstrcpy(szName, szArmorDirectory);
				lstrcat(szName, szArmorNumFile[cntH][cntW]);
				LoadOftenMeshPattern(szName);
			}
		}
	}

	return TRUE;
}

DWORD GetHairSkinCode(int FaceCode, int HairCode)
{
	return ((FaceCode & 0xFF) << 8) | (HairCode & 0xFF) | ((((FaceCode + 1) + (HairCode + 1) * 3) & 0xFF) << 16);
}
int CheckHairSkinCode(DWORD dwModelCode)
{
	if (dwModelCode)
	{
		int FaceCode = (dwModelCode >> 8) & 0xFF;
		int HairCode = dwModelCode & 0xFF;
		int Sum = (dwModelCode >> 16) & 0xFF;
		if ((((FaceCode + 1) + (HairCode + 1) * 3) & 0xFF) == Sum)
			return TRUE;
	}
	return FALSE;
}
char *GetFaceHairSkin(Unit *lpChar)
{
	DWORD dwModelCode = lpChar->sCharacterData.Player.iPlayerID;
	int FaceCode = (dwModelCode >> 8) & 0xFF;
	int HairCode = dwModelCode & 0xFF;

	if (CheckHairSkinCode(dwModelCode) == FALSE)
		return NULL;

	char *szHeadName = 0;

	switch (lpChar->sCharacterData.iClass)
	{
	case CHARACTERCLASS_Fighter:
		szHeadName = szModel_FighterFaceName[FaceCode][HairCode];
		break;
	case CHARACTERCLASS_Mechanician:
		szHeadName = szModel_MechFaceName[FaceCode][HairCode];
		break;
	case CHARACTERCLASS_Archer:
		szHeadName = szModel_ArcherFaceName[FaceCode][HairCode];
		break;
	case CHARACTERCLASS_Pikeman:
		szHeadName = szModel_PikeFaceName[FaceCode][HairCode];
		break;
	case CHARACTERCLASS_Atalanta:
		szHeadName = szModel_AtalantaFaceName[FaceCode][HairCode];
		break;
	case CHARACTERCLASS_Knight:
		szHeadName = szModel_KnightFaceName[FaceCode][HairCode];
		break;
	case CHARACTERCLASS_Magician:
		szHeadName = szModel_MagicanFaceName[FaceCode][HairCode];
		break;
	case CHARACTERCLASS_Priestess:
		szHeadName = szModel_PristessFaceName[FaceCode][HairCode];
		break;
	case CHARACTERCLASS_Assassin:
		szHeadName = szModel_AssaFaceName[FaceCode][HairCode];
		break;
	case CHARACTERCLASS_Shaman:
		szHeadName = szModel_ShamanFaceName[FaceCode][HairCode];
		break;
	}

	return szHeadName;
}
int FindFaceSkin(Unit *lpChar, char *lpHeadName, char ***lpSelFace, char **lpSelFaceName)
{
	int cnt, cnt2;
	int FindCount = 0;
	int FaceCode;
	int HairCode;

	switch (lpChar->sCharacterData.iClass)
	{
	case CHARACTERCLASS_Fighter:
		for (cnt = 0; cnt < FACE_MODEL_MAX; cnt++)
		{
			for (cnt2 = 0; cnt2 < HEAREPOTION_MAX; cnt2++)
			{
				if (lstrcmpi(szModel_FighterFaceName[cnt][cnt2], lpHeadName) == 0)
				{
					*lpSelFace = szModel_FighterFaceName[cnt];
					*lpSelFaceName = szModel_FighterFaceName[cnt][cnt2];
					FaceCode = cnt;
					HairCode = cnt2;
					FindCount++;
					break;
				}
			}
			if (cnt2 < HEAREPOTION_MAX)
				break;
		}
		break;
	case CHARACTERCLASS_Mechanician:
		for (cnt = 0; cnt < FACE_MODEL_MAX; cnt++)
		{
			for (cnt2 = 0; cnt2 < HEAREPOTION_MAX; cnt2++)
			{
				if (lstrcmpi(szModel_MechFaceName[cnt][cnt2], lpHeadName) == 0)
				{
					*lpSelFace = szModel_MechFaceName[cnt];
					*lpSelFaceName = szModel_MechFaceName[cnt][cnt2];
					FaceCode = cnt;
					HairCode = cnt2;
					FindCount++;
					break;
				}
			}
			if (cnt2 < HEAREPOTION_MAX)
				break;
		}
		break;
	case CHARACTERCLASS_Archer:
		for (cnt = 0; cnt < FACE_MODEL_MAX; cnt++)
		{
			for (cnt2 = 0; cnt2 < HEAREPOTION_MAX; cnt2++)
			{
				if (lstrcmpi(szModel_ArcherFaceName[cnt][cnt2], lpHeadName) == 0)
				{
					*lpSelFace = szModel_ArcherFaceName[cnt];
					*lpSelFaceName = szModel_ArcherFaceName[cnt][cnt2];
					FaceCode = cnt;
					HairCode = cnt2;
					FindCount++;
					break;
				}
			}
			if (cnt2 < HEAREPOTION_MAX)
				break;
		}
		break;
	case CHARACTERCLASS_Pikeman:
		for (cnt = 0; cnt < FACE_MODEL_MAX; cnt++)
		{
			for (cnt2 = 0; cnt2 < HEAREPOTION_MAX; cnt2++)
			{
				if (lstrcmpi(szModel_PikeFaceName[cnt][cnt2], lpHeadName) == 0)
				{
					*lpSelFace = szModel_PikeFaceName[cnt];
					*lpSelFaceName = szModel_PikeFaceName[cnt][cnt2];
					FaceCode = cnt;
					HairCode = cnt2;
					FindCount++;
					break;
				}
			}
			if (cnt2 < HEAREPOTION_MAX)
				break;
		}
		break;
	case CHARACTERCLASS_Atalanta:
		for (cnt = 0; cnt < FACE_MODEL_MAX; cnt++)
		{
			for (cnt2 = 0; cnt2 < HEAREPOTION_MAX; cnt2++)
			{
				if (lstrcmpi(szModel_AtalantaFaceName[cnt][cnt2], lpHeadName) == 0)
				{
					*lpSelFace = szModel_AtalantaFaceName[cnt];
					*lpSelFaceName = szModel_AtalantaFaceName[cnt][cnt2];
					FaceCode = cnt;
					HairCode = cnt2;
					FindCount++;
					break;
				}
			}
			if (cnt2 < HEAREPOTION_MAX)
				break;
		}
		break;
	case CHARACTERCLASS_Knight:
		for (cnt = 0; cnt < FACE_MODEL_MAX; cnt++)
		{
			for (cnt2 = 0; cnt2 < HEAREPOTION_MAX; cnt2++)
			{
				if (lstrcmpi(szModel_KnightFaceName[cnt][cnt2], lpHeadName) == 0)
				{
					*lpSelFace = szModel_KnightFaceName[cnt];
					*lpSelFaceName = szModel_KnightFaceName[cnt][cnt2];
					FaceCode = cnt;
					HairCode = cnt2;
					FindCount++;
					break;
				}
			}
			if (cnt2 < HEAREPOTION_MAX)
				break;
		}
		break;
	case CHARACTERCLASS_Magician:
		for (cnt = 0; cnt < FACE_MODEL_MAX; cnt++)
		{
			for (cnt2 = 0; cnt2 < HEAREPOTION_MAX; cnt2++)
			{
				if (lstrcmpi(szModel_MagicanFaceName[cnt][cnt2], lpHeadName) == 0)
				{
					*lpSelFace = szModel_MagicanFaceName[cnt];
					*lpSelFaceName = szModel_MagicanFaceName[cnt][cnt2];
					FaceCode = cnt;
					HairCode = cnt2;
					FindCount++;
					break;
				}
			}
			if (cnt2 < HEAREPOTION_MAX)
				break;
		}
		break;
	case CHARACTERCLASS_Priestess:
		for (cnt = 0; cnt < FACE_MODEL_MAX; cnt++)
		{
			for (cnt2 = 0; cnt2 < HEAREPOTION_MAX; cnt2++)
			{
				if (lstrcmpi(szModel_PristessFaceName[cnt][cnt2], lpHeadName) == 0)
				{
					*lpSelFace = szModel_PristessFaceName[cnt];
					*lpSelFaceName = szModel_PristessFaceName[cnt][cnt2];
					FaceCode = cnt;
					HairCode = cnt2;
					FindCount++;
					break;
				}
			}
			if (cnt2 < HEAREPOTION_MAX)
				break;
		}
		break;
	case CHARACTERCLASS_Assassin:
		for (cnt = 0; cnt < FACE_MODEL_MAX; cnt++)
		{
			for (cnt2 = 0; cnt2 < HEAREPOTION_MAX; cnt2++)
			{
				if (lstrcmpi(szModel_AssaFaceName[cnt][cnt2], lpHeadName) == 0)
				{
					*lpSelFace = szModel_AssaFaceName[cnt];
					*lpSelFaceName = szModel_AssaFaceName[cnt][cnt2];
					FaceCode = cnt;
					HairCode = cnt2;
					FindCount++;
					break;
				}
			}
			if (cnt2 < HEAREPOTION_MAX)
				break;
		}
		break;
	case CHARACTERCLASS_Shaman:
		for (cnt = 0; cnt < FACE_MODEL_MAX; cnt++)
		{
			for (cnt2 = 0; cnt2 < HEAREPOTION_MAX; cnt2++)
			{
				if (lstrcmpi(szModel_ShamanFaceName[cnt][cnt2], lpHeadName) == 0)
				{
					*lpSelFace = szModel_ShamanFaceName[cnt];
					*lpSelFaceName = szModel_ShamanFaceName[cnt][cnt2];
					FaceCode = cnt;
					HairCode = cnt2;
					FindCount++;
					break;
				}
			}
			if (cnt2 < HEAREPOTION_MAX)
				break;
		}
		break;
	}

	if (!FindCount)
		return -1;

	return (FaceCode << 8) | HairCode;
}

INT64 LevelTableSum = 1584390854576370149;

// 检测经验表
INT64 CheckLevelTable()
{
	INT64 cnt = 0;
	INT64 ChkSum = 0;

	while (uUnitExpTables[cnt] != -1)
	{
		ChkSum += uUnitExpTables[cnt] * (cnt + 1);
		cnt++;
	}

	return ChkSum;
}
// 检测经验等级
int	CheckLevelExp(int Level, INT64 Exp)
{
	INT64 xp;
	INT64 np;

	if (Level > 0 && Level <= UNIT_LEVEL_MAX)
	{
		xp = uUnitExpTables[Level - 1];
		np = uUnitExpTables[Level];

		if (Exp >= xp && Exp <= np)
			return TRUE;
	}

	return FALSE;
}
// 从经验值判断等级
int	GetLevelFromExp(INT64 Exp)
{
	int	cnt;

	for (cnt = 0; cnt < UNIT_LEVEL_MAX; cnt++)
	{
		if (Exp >= uUnitExpTables[cnt] && Exp < uUnitExpTables[cnt + 1])
			return cnt + 1;
	}

	return NULL;
}
//获取下一等级的经验
INT64 GetNextExp(int Level)
{
	return uUnitExpTables[Level];
}
//获取用户的防御
int GetPlayDefence(CharacterData *lpAttackCharInfo, CharacterData *lpDefenceCharInfo)
{
	int defence;

	float ar, def, dLv, aLv;
	int weight;

	ar = (float)lpAttackCharInfo->iAttackRating;
	aLv = (float)lpAttackCharInfo->iLevel;
	def = (float)lpDefenceCharInfo->iDefenseRating;
	dLv = (float)lpDefenceCharInfo->iLevel;
	weight = lpDefenceCharInfo->sWeight.sMin;
	defence = (int)(((((ar / (ar + (def / 2))) - ((dLv - aLv) / 50))) * 100)) - (weight / 10000);

	if (defence > 95)
		defence = 95;

	return defence;
}
int RainMaterial[4][8];

extern int WeatherMode;


HANDLE	hLoadingThread = 0;
HBITMAP hBitmapLoadImage[2] = { 0 };
HDC	hdcBitmapLoadImage = NULL;

int DispLoading = FALSE;

DWORD dwLampThreadId;

int DispCnt = 1;



#define DYN_REMOVER_MAX		64
#define DYN_REMOVER_MASK	(DYN_REMOVER_MAX-1)

smDPAT *DynRemoveList[DYN_REMOVER_MAX];
int DynRemoveCnt = 0;
int DynRemovePush = 0;

HANDLE	hRemoverThread = 0;

int RemoveDynPatSub()
{
	int RemoveCnt;

	while (1)
	{
		if ((DynRemovePush - DynRemoveCnt) > 32)
		{
			while (1)
			{
				RemoveCnt = DynRemoveCnt & DYN_REMOVER_MASK;
				smDPAT_Delete(DynRemoveList[RemoveCnt]);
				DynRemoveCnt++;
				if (DynRemovePush <= DynRemoveCnt)
					break;
			}
		}
		else
			break;
	}

	return TRUE;
}
int AddRemoveDynPattern(smDPAT *lpDinaPattern)
{
	if (lpDinaPattern->UseCount > 1)
		smDPAT_Delete(lpDinaPattern);

	return TRUE;
}

int MatArrow;
int MatMapBox;
int	MatPlayPos[5];
int	MatNpcPos;



int FieldMapDrawMode = 2;

int FieldMapDrawSize[3] = { 8 , 16 , 24 };
int FieldMapViewSize1 = 18 * 64 * fONE;
int FieldMapViewSize2 = 8 * 64 * fONE;

extern int MatEachBox;


int EecodeCompress(BYTE *lpSrcData, BYTE *lpDestData, int size, int DestSize)
{
	int EncCounter;
	int cnt;
	int Counter;
	int pSet;
	BYTE c1, c2;
	int lsize;

	Counter = 0;
	EncCounter = 4;
	lsize = size - 1;

	while (1)
	{
		if (Counter >= size)
			break;
		if (EncCounter >= DestSize)
			break;

		c1 = lpSrcData[Counter];

		if (Counter < lsize)
			c2 = lpSrcData[Counter + 1];
		else
			c2 = c1;

		if (c1 == 0 && c2 == 0)
		{
			for (cnt = 0; cnt < 0x7F; cnt++)
			{
				if (Counter >= size)
					break;
				if (lpSrcData[Counter] != 0)
					break;
				Counter++;
			}
			if (EncCounter >= DestSize)
				break;
			lpDestData[EncCounter++] = cnt | 0x80;
		}
		else
		{
			pSet = EncCounter;
			EncCounter++;

			for (cnt = 0; cnt < 0x7F; cnt++)
			{
				c1 = lpSrcData[Counter];
				if (Counter < lsize)
					c2 = lpSrcData[Counter + 1];
				else
					c2 = c1;

				if (Counter >= size)
					break;
				if (EncCounter >= DestSize)
					break;
				if (c1 == 0 && c2 == 0)
					break;
				lpDestData[EncCounter++] = lpSrcData[Counter++];
			}
			lpDestData[pSet] = cnt;
		}
	}

	((int *)lpDestData)[0] = EncCounter;

	return EncCounter;
}
int DecodeCompress_ItemPotion(User *lpPlayInfo, BYTE *lpSrcData, BYTE *lpDestData, int deCount, void *lpTransRecdata)
{
	int DecCounter;
	int cnt;
	int Counter;
	int size;
	int len;
	int dCount = deCount;
	int pCnt;
	CharacterFile	*lpTransRecordData = (CharacterFile *)lpTransRecdata;

	sRECORD_ITEM	*lpRecordItem = (sRECORD_ITEM *)lpDestData;

	size = ((int *)lpSrcData)[0];

	Counter = 4;
	DecCounter = 0;

	while (1)
	{
		if (Counter >= size)
			break;
		if (lpSrcData[Counter] & 0x80)
		{
			len = lpSrcData[Counter++] & 0x7F;
			for (cnt = 0; cnt < len; cnt++)
			{
				if (DecCounter >= dCount)
				{
					if (dCount >= sizeof(sRECORD_ITEM))
						goto Skip_Decmp;
					if ((lpRecordItem->sItemInfo.sItemID.ToItemBase()) != (sinPM1&sinITEM_MASK1))
						return Counter;

					dCount = sizeof(sRECORD_ITEM);
				}
				lpDestData[DecCounter++] = 0;
			}

		}
		else 
		{
			len = lpSrcData[Counter++] & 0x7F;

			for (cnt = 0; cnt < len; cnt++) 
			{
				if (DecCounter >= dCount) 
				{
					if (dCount >= sizeof(sRECORD_ITEM)) 
						goto Skip_Decmp;
					if ((lpRecordItem->sItemInfo.sItemID.ToItemBase()) != (sinPM1&sinITEM_MASK1))
						return Counter;

					dCount = sizeof(sRECORD_ITEM);
				}
				lpDestData[DecCounter++] = lpSrcData[Counter++];
			}
		}
	}

Skip_Decmp:

	if (lpTransRecordData)
	{
		for (cnt = 0; cnt < lpTransRecordData->ThrowItemCount; cnt++)
		{
			if (lpTransRecordData->ThrowItemInfo[cnt].dwCode == lpRecordItem->sItemInfo.sItemID.ToInt() &&
				lpTransRecordData->ThrowItemInfo[cnt].dwKey == lpRecordItem->sItemInfo.iChk1 &&
				lpTransRecordData->ThrowItemInfo[cnt].dwSum == lpRecordItem->sItemInfo.iChk2)
				return Counter;
		}
	}

	pCnt = lpRecordItem->sItemInfo.iPotionCount;
	if (pCnt == 0)
		pCnt = 1;

	SERVERITEM->AddPotion(lpPlayInfo, lpRecordItem->sItemInfo.sItemID.ToInt(), pCnt);
	return Counter;
}

int DecodeCompress(BYTE *lpSrcData, BYTE *lpDestData, int dCount)
{
	int DecCounter;
	int cnt;
	int Counter;
	int size;
	int len;

	size = ((int *)lpSrcData)[0];

	Counter = 4;
	DecCounter = 0;

	while (1)
	{
		if (Counter >= size)
			break;
		if (lpSrcData[Counter] & 0x80)
		{
			len = lpSrcData[Counter++] & 0x7F;
			for (cnt = 0; cnt < len; cnt++)
			{
				if (DecCounter >= dCount)
					return Counter;
				lpDestData[DecCounter++] = 0;
			}

		}
		else
		{
			len = lpSrcData[Counter++] & 0x7F;
			for (cnt = 0; cnt < len; cnt++)
			{
				if (DecCounter >= dCount)
					return Counter;
				lpDestData[DecCounter++] = lpSrcData[Counter++];
			}
		}
	}

	return Counter;
}
int DecodeCompress(BYTE *lpSrcData, BYTE *lpDestData)
{
	return DecodeCompress(lpSrcData, lpDestData, 0x7FFFF);
}
int EecodeCompress(BYTE *lpSrcData, BYTE *lpDestData, int size)
{
	return EecodeCompress(lpSrcData, lpDestData, size, 0x7FFFF);
}
Unit *CheckOtherPlayPosi(int x, int y, int z)
{
	return SERVERUNIT->GetUnitFromPosition(x, y, z);
}

int MessageLoading = 0;


int smPlayWindowMessage()
{
	MSG msg;

	MessageLoading = TRUE;

	while (1)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			if (msg.message == WM_SYSKEYDOWN || msg.message == WM_SYSKEYUP)
				continue;
			DispatchMessage(&msg);
		}
		else
			break;
	}

	MessageLoading = FALSE;
	return TRUE;
}

static DWORD iFormCode;
static DWORD iFromCnt;

static DWORD ReformStateCode(char *lpState, int size)
{
	int cnt;

	for (cnt = 0; cnt < size; cnt++)
	{
		iFormCode += ((DWORD)lpState[cnt])*((iFromCnt & 0x1FFF) + 1);
		iFromCnt++;
	}

	return iFormCode;
}

static DWORD CompareStateCode(char *lpState1, char *lpState2, int size)
{
	int cnt;

	for (cnt = 0; cnt < size; cnt++)
	{
		if (lpState1[cnt] != lpState2[cnt])
			return 1;
	}

	return 0;
}
static DWORD GetRefromItemCode_Old(Item *lpItemInfo, int Key) {

	iFormCode = 0;
	iFromCnt = Key;

	ReformStateCode((char *)&lpItemInfo->sItemID, sizeof(DWORD));
	ReformStateCode((char *)lpItemInfo->szItemName, 32);

	ReformStateCode((char *)&lpItemInfo->iWeight, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->iSalePrice, sizeof(int));

	ReformStateCode((char *)lpItemInfo->saElementalDef, sizeof(short) * 8);
	ReformStateCode((char *)&lpItemInfo->sDamage, sizeof(MinMax));

	//ReformStateCode( (char *)&lpItemInfo->Defence , sizeof(int) );

	ReformStateCode((char *)&lpItemInfo->iAttackRange, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->iAttackSpeed, sizeof(int));

	ReformStateCode((char *)&lpItemInfo->iAttackRating, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->iCritical, sizeof(int));

	ReformStateCode((char *)&lpItemInfo->fMovementSpeed, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->iPotionStorage, sizeof(int));

	ReformStateCode((char *)&lpItemInfo->fMagicMastery, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->fMPRegen, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->fHPRegen, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->fSPRegen, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->fAddHP, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->fAddMP, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->fAddSP, sizeof(float));

	ReformStateCode((char *)&lpItemInfo->iLevel, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->iStrength, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->iSpirit, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->iTalent, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->iAgility, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->iHealth, sizeof(int));

	ReformStateCode((char *)&lpItemInfo->sMPRecovery, sizeof(MinMax));
	ReformStateCode((char *)&lpItemInfo->sHPRecovery, sizeof(MinMax));
	ReformStateCode((char *)&lpItemInfo->sSPRecovery, sizeof(MinMax));

	ReformStateCode((char *)&lpItemInfo->iGold, sizeof(int));

	ReformStateCode((char *)&lpItemInfo->eSpecialization, sizeof(int));

	ReformStateCode((char *)&lpItemInfo->sSpecData, sizeof(SpecItemData));

	return iFormCode;
}
static DWORD GetRefromItemCode_V10(Item *lpItemInfo, int Key) {

	iFormCode = 0;
	iFromCnt = Key;

	ReformStateCode((char *)&lpItemInfo->sItemID, sizeof(DWORD));
	ReformStateCode((char *)lpItemInfo->szItemName, 32);

	ReformStateCode((char *)&lpItemInfo->iWeight, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->iSalePrice, sizeof(int));

	ReformStateCode((char *)lpItemInfo->saElementalDef, sizeof(short) * 8);
	ReformStateCode((char *)&lpItemInfo->sDamage, sizeof(MinMax));

	ReformStateCode((char *)&lpItemInfo->iDefenseRating, sizeof(int));

	ReformStateCode((char *)&lpItemInfo->iAttackRange, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->iAttackSpeed, sizeof(int));

	ReformStateCode((char *)&lpItemInfo->iAttackRating, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->iCritical, sizeof(int));

	ReformStateCode((char *)&lpItemInfo->fMovementSpeed, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->iPotionStorage, sizeof(int));

	ReformStateCode((char *)&lpItemInfo->fMagicMastery, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->fMPRegen, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->fHPRegen, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->fSPRegen, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->fAddHP, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->fAddMP, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->fAddSP, sizeof(float));

	ReformStateCode((char *)&lpItemInfo->iLevel, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->iStrength, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->iSpirit, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->iTalent, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->iAgility, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->iHealth, sizeof(int));

	ReformStateCode((char *)&lpItemInfo->sMPRecovery, sizeof(MinMax));
	ReformStateCode((char *)&lpItemInfo->sHPRecovery, sizeof(MinMax));
	ReformStateCode((char *)&lpItemInfo->sSPRecovery, sizeof(MinMax));

	ReformStateCode((char *)&lpItemInfo->iGold, sizeof(int));

	ReformStateCode((char *)&lpItemInfo->eSpecialization, sizeof(int));

	ReformStateCode((char *)&lpItemInfo->sSpecData, sizeof(SpecItemData));

	return iFormCode;
}
static int CompareReformItemCode_V10(Item *lpItemInfo1, Item *lpItemInfo2)
{

	int code;

	code = 0;

	code += CompareStateCode((char *)&lpItemInfo1->sItemID, (char *)&lpItemInfo2->sItemID, sizeof(DWORD));
	code += CompareStateCode((char *)lpItemInfo1->szItemName, (char *)lpItemInfo2->szItemName, 32);

	code += CompareStateCode((char *)&lpItemInfo1->iWeight, (char *)&lpItemInfo2->iWeight, sizeof(int));
	code += CompareStateCode((char *)&lpItemInfo1->iSalePrice, (char *)&lpItemInfo2->iSalePrice, sizeof(int));

	code += CompareStateCode((char *)lpItemInfo1->saElementalDef, (char *)lpItemInfo2->saElementalDef, sizeof(short) * 8);
	code += CompareStateCode((char *)&lpItemInfo1->sDamage, (char *)&lpItemInfo2->sDamage, sizeof(MinMax));

	code += CompareStateCode((char *)&lpItemInfo1->iDefenseRating, (char *)&lpItemInfo2->iDefenseRating, sizeof(int));

	code += CompareStateCode((char *)&lpItemInfo1->iAttackRange, (char *)&lpItemInfo2->iAttackRange, sizeof(int));
	code += CompareStateCode((char *)&lpItemInfo1->iAttackSpeed, (char *)&lpItemInfo2->iAttackSpeed, sizeof(int));

	code += CompareStateCode((char *)&lpItemInfo1->iAttackRating, (char *)&lpItemInfo2->iAttackRating, sizeof(int));
	code += CompareStateCode((char *)&lpItemInfo1->iCritical, (char *)&lpItemInfo2->iCritical, sizeof(int));

	code += CompareStateCode((char *)&lpItemInfo1->fMovementSpeed, (char *)&lpItemInfo2->fMovementSpeed, sizeof(float));
	code += CompareStateCode((char *)&lpItemInfo1->iPotionStorage, (char *)&lpItemInfo2->iPotionStorage, sizeof(int));

	code += CompareStateCode((char *)&lpItemInfo1->fMagicMastery, (char *)&lpItemInfo2->fMagicMastery, sizeof(float));
	code += CompareStateCode((char *)&lpItemInfo1->fMPRegen, (char *)&lpItemInfo2->fMPRegen, sizeof(float));
	code += CompareStateCode((char *)&lpItemInfo1->fHPRegen, (char *)&lpItemInfo2->fHPRegen, sizeof(float));
	code += CompareStateCode((char *)&lpItemInfo1->fSPRegen, (char *)&lpItemInfo2->fSPRegen, sizeof(float));
	code += CompareStateCode((char *)&lpItemInfo1->fAddHP, (char *)&lpItemInfo2->fAddHP, sizeof(float));
	code += CompareStateCode((char *)&lpItemInfo1->fAddMP, (char *)&lpItemInfo2->fAddMP, sizeof(float));
	code += CompareStateCode((char *)&lpItemInfo1->fAddSP, (char *)&lpItemInfo2->fAddSP, sizeof(float));

	code += CompareStateCode((char *)&lpItemInfo1->iLevel, (char *)&lpItemInfo2->iLevel, sizeof(int));
	code += CompareStateCode((char *)&lpItemInfo1->iStrength, (char *)&lpItemInfo2->iStrength, sizeof(int));
	code += CompareStateCode((char *)&lpItemInfo1->iSpirit, (char *)&lpItemInfo2->iSpirit, sizeof(int));
	code += CompareStateCode((char *)&lpItemInfo1->iTalent, (char *)&lpItemInfo2->iTalent, sizeof(int));
	code += CompareStateCode((char *)&lpItemInfo1->iAgility, (char *)&lpItemInfo2->iAgility, sizeof(int));
	code += CompareStateCode((char *)&lpItemInfo1->iHealth, (char *)&lpItemInfo2->iHealth, sizeof(int));

	code += CompareStateCode((char *)&lpItemInfo1->sMPRecovery, (char *)&lpItemInfo2->sMPRecovery, sizeof(MinMax));
	code += CompareStateCode((char *)&lpItemInfo1->sHPRecovery, (char *)&lpItemInfo2->sHPRecovery, sizeof(MinMax));
	code += CompareStateCode((char *)&lpItemInfo1->sSPRecovery, (char *)&lpItemInfo2->sSPRecovery, sizeof(MinMax));

	code += CompareStateCode((char *)&lpItemInfo1->iGold, (char *)&lpItemInfo2->iGold, sizeof(int));

	code += CompareStateCode((char *)&lpItemInfo1->eSpecialization, (char *)&lpItemInfo2->eSpecialization, sizeof(int));

	code += CompareStateCode((char *)&lpItemInfo1->sSpecData, (char *)&lpItemInfo2->sSpecData, sizeof(SpecItemData));

	return code;
}

static DWORD GetRefromItemCode(Item *lpItemInfo, int Key)
{
	iFormCode = 0;
	iFromCnt = Key;

	ReformStateCode((char *)&lpItemInfo->sItemID, sizeof(DWORD));
	ReformStateCode((char *)lpItemInfo->szItemName, 32);

	ReformStateCode((char *)&lpItemInfo->iWeight, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->iSalePrice, sizeof(int));

	ReformStateCode((char *)lpItemInfo->saElementalDef, sizeof(short) * 8);
	ReformStateCode((char *)&lpItemInfo->sDamage, sizeof(MinMax));

	ReformStateCode((char *)&lpItemInfo->fAbsorbRating, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->iDefenseRating, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->fBlockRating, sizeof(float));

	ReformStateCode((char *)&lpItemInfo->iAttackRange, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->iAttackSpeed, sizeof(int));

	ReformStateCode((char *)&lpItemInfo->iAttackRating, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->iCritical, sizeof(int));

	ReformStateCode((char *)&lpItemInfo->fMovementSpeed, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->iPotionStorage, sizeof(int));

	ReformStateCode((char *)&lpItemInfo->fMagicMastery, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->fMPRegen, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->fHPRegen, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->fSPRegen, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->fAddHP, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->fAddMP, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->fAddSP, sizeof(float));

	ReformStateCode((char *)&lpItemInfo->iLevel, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->iStrength, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->iSpirit, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->iTalent, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->iAgility, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->iHealth, sizeof(int));

	ReformStateCode((char *)&lpItemInfo->sMPRecovery, sizeof(MinMax));
	ReformStateCode((char *)&lpItemInfo->sHPRecovery, sizeof(MinMax));
	ReformStateCode((char *)&lpItemInfo->sSPRecovery, sizeof(MinMax));

	ReformStateCode((char *)&lpItemInfo->iGold, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->eSpecialization, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->sSpecData, sizeof(SpecItemData));

	ReformStateCode((char *)&lpItemInfo->iItemUniqueID, sizeof(int));
	ReformStateCode((char *)lpItemInfo->EffectBlink, sizeof(short) * 2);
	ReformStateCode((char *)lpItemInfo->EffectColor, sizeof(short) * 4);
	ReformStateCode((char *)lpItemInfo->ScaleBlink, sizeof(short) * 2);
	ReformStateCode((char *)&lpItemInfo->bEnableEffect, sizeof(BOOL));
	ReformStateCode((char *)&lpItemInfo->ItemElement, sizeof(WORD));

	return iFormCode;
}

#ifdef _W_SERVER

static DWORD rsReformStateCode(char *lpState, int size)
{
	int cnt;

	for (cnt = 0; cnt < size; cnt++)
	{
		iFormCode += ((DWORD)lpState[cnt])*((iFromCnt & 0x7FF) + 1);
		iFromCnt++;
	}

	return iFormCode;
}


static DWORD rsGetRefromItemCode(Item *lpItemInfo, int Key)
{
	iFormCode = 0;
	iFromCnt = Key;

	rsReformStateCode((char *)&lpItemInfo->sItemID, sizeof(DWORD));
	rsReformStateCode((char *)lpItemInfo->szItemName, 32);

	rsReformStateCode((char *)&lpItemInfo->iWeight, sizeof(int));
	rsReformStateCode((char *)&lpItemInfo->iSalePrice, sizeof(int));

	rsReformStateCode((char *)lpItemInfo->saElementalDef, sizeof(short) * 8);
	rsReformStateCode((char *)&lpItemInfo->sDamage, sizeof(MinMax));

	rsReformStateCode((char *)&lpItemInfo->fAbsorbRating, sizeof(float));
	rsReformStateCode((char *)&lpItemInfo->iDefenseRating, sizeof(int));
	rsReformStateCode((char *)&lpItemInfo->fBlockRating, sizeof(float));

	rsReformStateCode((char *)&lpItemInfo->iAttackRange, sizeof(int));
	rsReformStateCode((char *)&lpItemInfo->iAttackSpeed, sizeof(int));

	rsReformStateCode((char *)&lpItemInfo->iAttackRating, sizeof(int));
	rsReformStateCode((char *)&lpItemInfo->iCritical, sizeof(int));

	rsReformStateCode((char *)&lpItemInfo->fMovementSpeed, sizeof(float));
	rsReformStateCode((char *)&lpItemInfo->iPotionStorage, sizeof(int));

	rsReformStateCode((char *)&lpItemInfo->fMagicMastery, sizeof(float));
	rsReformStateCode((char *)&lpItemInfo->fMPRegen, sizeof(float));
	rsReformStateCode((char *)&lpItemInfo->fHPRegen, sizeof(float));
	rsReformStateCode((char *)&lpItemInfo->fSPRegen, sizeof(float));
	rsReformStateCode((char *)&lpItemInfo->fAddHP, sizeof(float));
	rsReformStateCode((char *)&lpItemInfo->fAddMP, sizeof(float));
	rsReformStateCode((char *)&lpItemInfo->fAddSP, sizeof(float));

	rsReformStateCode((char *)&lpItemInfo->iLevel, sizeof(int));
	rsReformStateCode((char *)&lpItemInfo->iStrength, sizeof(int));
	rsReformStateCode((char *)&lpItemInfo->iSpirit, sizeof(int));
	rsReformStateCode((char *)&lpItemInfo->iTalent, sizeof(int));
	rsReformStateCode((char *)&lpItemInfo->iAgility, sizeof(int));
	rsReformStateCode((char *)&lpItemInfo->iHealth, sizeof(int));

	rsReformStateCode((char *)&lpItemInfo->sMPRecovery, sizeof(MinMax));
	rsReformStateCode((char *)&lpItemInfo->sHPRecovery, sizeof(MinMax));
	rsReformStateCode((char *)&lpItemInfo->sSPRecovery, sizeof(MinMax));

	rsReformStateCode((char *)&lpItemInfo->iGold, sizeof(int));
	rsReformStateCode((char *)&lpItemInfo->eSpecialization, sizeof(int));
	rsReformStateCode((char *)&lpItemInfo->sSpecData, sizeof(SpecItemData));

	rsReformStateCode((char *)&lpItemInfo->iItemUniqueID, sizeof(int));
	rsReformStateCode((char *)lpItemInfo->EffectBlink, sizeof(short) * 2);
	rsReformStateCode((char *)lpItemInfo->EffectColor, sizeof(short) * 4);
	rsReformStateCode((char *)lpItemInfo->ScaleBlink, sizeof(short) * 2);
	rsReformStateCode((char *)&lpItemInfo->bEnableEffect, sizeof(BOOL));
	rsReformStateCode((char *)&lpItemInfo->ItemElement, sizeof(WORD));

	return iFormCode;
}

#ifdef _NEW_ITEM_FORMCODE3
#include "ItemForm2.h"
#else
#include "ItemForm.h"
#endif

int	rsGetItemForm_Server(Item *lpItemInfo)
{

	return rsGetItem_ServerForm(lpItemInfo);
}

int	rsReformItem_Server(Item *lpItemInfo)
{
	DWORD dwCode;

	dwCode = rsGetItemForm_Server(lpItemInfo);

	lpItemInfo->dwTime = dwCode;

	return TRUE;
}
#else
int	rsGetItemForm_Server(Item *lpItemInfo)
{

	return TRUE;
}

int	rsReformItem_Server(Item *lpItemInfo)
{

	return TRUE;
}


#endif

static int CompareReformItemCode(Item *lpItemInfo1, Item *lpItemInfo2)
{
	int code;

	code = 0;

	code += CompareStateCode((char *)&lpItemInfo1->sItemID, (char *)&lpItemInfo2->sItemID, sizeof(DWORD));
	code += CompareStateCode((char *)lpItemInfo1->szItemName, (char *)lpItemInfo2->szItemName, 32);

	code += CompareStateCode((char *)&lpItemInfo1->iWeight, (char *)&lpItemInfo2->iWeight, sizeof(int));
	code += CompareStateCode((char *)&lpItemInfo1->iSalePrice, (char *)&lpItemInfo2->iSalePrice, sizeof(int));

	code += CompareStateCode((char *)lpItemInfo1->saElementalDef, (char *)lpItemInfo2->saElementalDef, sizeof(short) * 8);
	code += CompareStateCode((char *)&lpItemInfo1->sDamage, (char *)&lpItemInfo2->sDamage, sizeof(MinMax));

	code += CompareStateCode((char *)&lpItemInfo1->fAbsorbRating, (char *)&lpItemInfo2->fAbsorbRating, sizeof(float));
	code += CompareStateCode((char *)&lpItemInfo1->iDefenseRating, (char *)&lpItemInfo2->iDefenseRating, sizeof(int));
	code += CompareStateCode((char *)&lpItemInfo1->fBlockRating, (char *)&lpItemInfo2->fBlockRating, sizeof(float));

	code += CompareStateCode((char *)&lpItemInfo1->iAttackRange, (char *)&lpItemInfo2->iAttackRange, sizeof(int));
	code += CompareStateCode((char *)&lpItemInfo1->iAttackSpeed, (char *)&lpItemInfo2->iAttackSpeed, sizeof(int));

	code += CompareStateCode((char *)&lpItemInfo1->iAttackRating, (char *)&lpItemInfo2->iAttackRating, sizeof(int));
	code += CompareStateCode((char *)&lpItemInfo1->iCritical, (char *)&lpItemInfo2->iCritical, sizeof(int));

	code += CompareStateCode((char *)&lpItemInfo1->fMovementSpeed, (char *)&lpItemInfo2->fMovementSpeed, sizeof(float));
	code += CompareStateCode((char *)&lpItemInfo1->iPotionStorage, (char *)&lpItemInfo2->iPotionStorage, sizeof(int));

	code += CompareStateCode((char *)&lpItemInfo1->fMagicMastery, (char *)&lpItemInfo2->fMagicMastery, sizeof(float));
	code += CompareStateCode((char *)&lpItemInfo1->fMPRegen, (char *)&lpItemInfo2->fMPRegen, sizeof(float));
	code += CompareStateCode((char *)&lpItemInfo1->fHPRegen, (char *)&lpItemInfo2->fHPRegen, sizeof(float));
	code += CompareStateCode((char *)&lpItemInfo1->fSPRegen, (char *)&lpItemInfo2->fSPRegen, sizeof(float));
	code += CompareStateCode((char *)&lpItemInfo1->fAddHP, (char *)&lpItemInfo2->fAddHP, sizeof(float));
	code += CompareStateCode((char *)&lpItemInfo1->fAddMP, (char *)&lpItemInfo2->fAddMP, sizeof(float));
	code += CompareStateCode((char *)&lpItemInfo1->fAddSP, (char *)&lpItemInfo2->fAddSP, sizeof(float));

	code += CompareStateCode((char *)&lpItemInfo1->iLevel, (char *)&lpItemInfo2->iLevel, sizeof(int));
	code += CompareStateCode((char *)&lpItemInfo1->iStrength, (char *)&lpItemInfo2->iStrength, sizeof(int));
	code += CompareStateCode((char *)&lpItemInfo1->iSpirit, (char *)&lpItemInfo2->iSpirit, sizeof(int));
	code += CompareStateCode((char *)&lpItemInfo1->iTalent, (char *)&lpItemInfo2->iTalent, sizeof(int));
	code += CompareStateCode((char *)&lpItemInfo1->iAgility, (char *)&lpItemInfo2->iAgility, sizeof(int));
	code += CompareStateCode((char *)&lpItemInfo1->iHealth, (char *)&lpItemInfo2->iHealth, sizeof(int));

	code += CompareStateCode((char *)&lpItemInfo1->sMPRecovery, (char *)&lpItemInfo2->sMPRecovery, sizeof(MinMax));
	code += CompareStateCode((char *)&lpItemInfo1->sHPRecovery, (char *)&lpItemInfo2->sHPRecovery, sizeof(MinMax));
	code += CompareStateCode((char *)&lpItemInfo1->sSPRecovery, (char *)&lpItemInfo2->sSPRecovery, sizeof(MinMax));

	code += CompareStateCode((char *)&lpItemInfo1->iGold, (char *)&lpItemInfo2->iGold, sizeof(int));
	code += CompareStateCode((char *)&lpItemInfo1->eSpecialization, (char *)&lpItemInfo2->eSpecialization, sizeof(int));
	code += CompareStateCode((char *)&lpItemInfo1->sSpecData, (char *)&lpItemInfo2->sSpecData, sizeof(SpecItemData));

	code += CompareStateCode((char *)&lpItemInfo1->iItemUniqueID, (char *)&lpItemInfo2->iItemUniqueID, sizeof(int));
	code += CompareStateCode((char *)lpItemInfo1->EffectBlink, (char *)lpItemInfo2->EffectBlink, sizeof(short) * 2);
	code += CompareStateCode((char *)lpItemInfo1->EffectColor, (char *)lpItemInfo2->EffectColor, sizeof(short) * 4);
	code += CompareStateCode((char *)lpItemInfo1->ScaleBlink, (char *)lpItemInfo2->ScaleBlink, sizeof(short) * 2);
	code += CompareStateCode((char *)&lpItemInfo1->bEnableEffect, (char *)&lpItemInfo2->bEnableEffect, sizeof(BOOL));
	code += CompareStateCode((char *)&lpItemInfo1->ItemElement, (char *)&lpItemInfo2->ItemElement, sizeof(WORD));

	return code;
}
static DWORD GetRefromTradeCode(sTRADE *lpTrade, int Key)
{

	int cnt;

	iFormCode = 0;
	iFromCnt = Key;

	for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++)
	{
		if (lpTrade->TradeItem[cnt].bValid)
		{
			ReformStateCode((char *)&lpTrade->TradeItem[cnt].sItem.sItemID, sizeof(DWORD));
			ReformStateCode((char *)&lpTrade->TradeItem[cnt].sItem.iChk2, sizeof(DWORD));
		}
	}
	ReformStateCode((char *)&lpTrade->Money, sizeof(int));

	return iFormCode;
}
static DWORD GetRefromCharState(CharacterData *lpCharInfo, int Key)
{
	iFormCode = 0;
	iFromCnt = Key;

	ReformStateCode((char *)&lpCharInfo->Player.szHeadModel, 64);

	ReformStateCode((char *)&lpCharInfo->iLevel, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->iStrength, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->iSpirit, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->iTalent, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->iAgility, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->iHealth, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->iLevel, sizeof(int));

	ReformStateCode((char *)&lpCharInfo->iAccuracy, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->iAttackRating, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->iMinDamage, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->iMaxDamage, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->iAttackSpeed, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->iAttackRange, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->iCritical, sizeof(int));

	ReformStateCode((char *)&lpCharInfo->iDefenseRating, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->iBlockRating, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->iAbsorbRating, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->iMovementSpeed, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->iSight, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->sWeight, sizeof(CurMax));

	ReformStateCode((char *)lpCharInfo->sElementalDef, sizeof(short) * 8);
	ReformStateCode((char *)lpCharInfo->sElementalAtk, sizeof(short) * 8);

	ReformStateCode((char *)&lpCharInfo->sHP, sizeof(CurMax));
	ReformStateCode((char *)&lpCharInfo->sMP, sizeof(CurMax));
	ReformStateCode((char *)&lpCharInfo->sSP, sizeof(CurMax));

	ReformStateCode((char *)&lpCharInfo->iExp, sizeof(INT64));
	ReformStateCode((char *)&lpCharInfo->iOwnerID, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->iGold, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->iStatPoints, sizeof(int));

	return iFormCode;
}


static int ItemFormVersion = 12;
static int ItemFormKey = 0;


int ReformItem(Item *lpItemInfo)
{
	DWORD dwCode;

	lpItemInfo->iChk1 = ItemFormKey + GetCurrentTime();

	dwCode = GetRefromItemCode(lpItemInfo, lpItemInfo->iChk1);

	lpItemInfo->iChk2 = dwCode;
	lpItemInfo->dwVersion = ItemFormVersion;
	lpItemInfo->dwCreateTime = (DWORD)TICKCOUNT;

	if (!lpItemInfo->BackUpKey || !lpItemInfo->BackUpChkSum)
	{
		lpItemInfo->BackUpKey = lpItemInfo->iChk1;
		lpItemInfo->BackUpChkSum = lpItemInfo->iChk2;
	}

	ReformMixItem(lpItemInfo);
	rsReformItem_Server(lpItemInfo);

	lpItemInfo->Temp0 = lpItemInfo->iChk2 + lpItemInfo->sItemID.ToInt();


	ItemFormKey++;

	return TRUE;
}
int ReformItem_AdjustTime(Item *lpItemInfo, int TimeAdjust)
{

#ifdef _W_SERVER
	DWORD dwCode;

	lpItemInfo->iChk1 = ItemFormKey + GetCurrentTime();

	dwCode = GetRefromItemCode(lpItemInfo, lpItemInfo->iChk1);

	lpItemInfo->iChk2 = dwCode;
	lpItemInfo->dwVersion = ItemFormVersion;
	lpItemInfo->dwCreateTime = (DWORD)SERVER_LOCATIME + TimeAdjust;

	if (!lpItemInfo->BackUpKey || !lpItemInfo->BackUpChkSum)
	{
		lpItemInfo->BackUpKey = lpItemInfo->iChk1;
		lpItemInfo->BackUpChkSum = lpItemInfo->iChk2;
	}

	ReformMixItem(lpItemInfo);
	rsReformItem_Server(lpItemInfo);

	lpItemInfo->Temp0 = lpItemInfo->iChk2 + lpItemInfo->sItemID.ToInt();

#endif

	ItemFormKey++;

	return TRUE;
}


int CheckItemForm(Item *lpItemInfo)
{
	DWORD dwCode;

	if (lpItemInfo->sItemID.ToInt() == (sinGG1 | sin01) || (lpItemInfo->sItemID.ToItemBase()) == (sinPM1&sinITEM_MASK1))
	{
		dwCode = GetRefromItemCode(lpItemInfo, lpItemInfo->iChk1);
		if (lpItemInfo->iChk2 == dwCode)
			return TRUE;
		return FALSE;
	}

	dwCode = rsGetItemForm_Server(lpItemInfo);

	if (lpItemInfo->dwTime == dwCode)
		return TRUE;

	return FALSE;
}


int CompareItems(Item *lpItemInfo1, Item *lpItemInfo2)
{

	if (lpItemInfo1->dwVersion != (DWORD)ItemFormVersion)
		CheckItemForm(lpItemInfo1);
	if (lpItemInfo2->dwVersion != (DWORD)ItemFormVersion)
		CheckItemForm(lpItemInfo2);

	if (lpItemInfo1->sItemID.ToInt() != lpItemInfo2->sItemID.ToInt())
		return FALSE;
	if (lpItemInfo1->iChk1 != lpItemInfo2->iChk1)
		return FALSE;
	if (lpItemInfo1->iChk2 != lpItemInfo2->iChk2)
		return FALSE;

	if (CompareReformItemCode(lpItemInfo1, lpItemInfo2) == 0)
		return TRUE;

	return FALSE;
}
int ReformCharForm(CharacterData *lpCharInfo)
{
	DWORD dwCode;

	dwCode = GetRefromCharState(lpCharInfo, 10);

	lpCharInfo->dwChecksum = dwCode;

	ItemFormKey++;

	return TRUE;
}
int CheckCharForm(CharacterData *lpCharInfo)
{
	DWORD dwCode;

	dwCode = GetRefromCharState(lpCharInfo, 10);

	if (lpCharInfo->dwChecksum == dwCode)
		return TRUE;

	return FALSE;
}
int ReformTrade(void *lpTrade)
{
	DWORD dwCode;

	dwCode = GetRefromTradeCode((sTRADE *)lpTrade, 84);

	((sTRADE *)lpTrade)->CheckMoney = dwCode;

	ItemFormKey++;

	return TRUE;
}
int CheckTrade(void *lpTrade)
{
	return FALSE;
}
short GetMixItemForm(Item *lpItemInfo)
{
	short sCode = 0;

#ifdef _W_SERVER

	DWORD dwCode;
	DWORD dwItemKey;

	if (lpItemInfo->eCraftType)
	{
		dwItemKey = lpItemInfo->iChk2;

		dwCode = lpItemInfo->eCraftType*(lpItemInfo->sAgeLevel * 3 + lpItemInfo->bMaturing * 7 + lpItemInfo->sMatureBar.sMax * 17 + 17);

		dwCode = dwCode ^ dwItemKey;

		sCode = (short)((dwCode >> 16) ^ (dwCode & 0xFFFF));
	}
#endif

	return sCode;
}
int ReformMixItem(Item *lpItemInfo)
{
#ifdef _W_SERVER
	lpItemInfo->ItemAgingProtect[0] = GetMixItemForm(lpItemInfo);
#endif
	return TRUE;
}
int CheckMixItem(Item *lpItemInfo)
{
#ifdef _W_SERVER
	if (GetMixItemForm(lpItemInfo) == lpItemInfo->ItemAgingProtect[0]) {
		return TRUE;
	}
#else
	return TRUE;
#endif

	return FALSE;
}

float GetItemAbsorb(Item *lpItemInfo)
{
	return lpItemInfo->fAbsorbRating;
}



#define WAIT_BATTLE_QUIT_TIME		10000

#define CHARINFO_CACHE_MAX		200

smTRNAS_PLAYERINFO	CharInfo_Cache[CHARINFO_CACHE_MAX];
DWORD	dwCharInfo_CacheCode[CHARINFO_CACHE_MAX];
int	CharInfoCacheCnt = 0;

int SaveCharInfoCache(smTRNAS_PLAYERINFO *lpTransPlayInfo)
{
	int cnt;
	DWORD	dwCode;

	dwCode = GetCodebyName(lpTransPlayInfo->sCharacterData.szName);

	for (cnt = 0; cnt < CharInfoCacheCnt; cnt++)
	{
		if (dwCode == dwCharInfo_CacheCode[cnt])
			return NULL;
	}

	dwCharInfo_CacheCode[CharInfoCacheCnt] = dwCode;
	memcpy(&CharInfo_Cache[CharInfoCacheCnt], lpTransPlayInfo, sizeof(smTRNAS_PLAYERINFO));
	CharInfoCacheCnt++;

	return TRUE;
}


Unit	chrPartyPlayer;

char	szLastWhisperName[32] = { 0 };
int		LastWhisperLen = 0;



int	PlayAttackCount = 0;
int	MotionAttackCount = 0;

int	AttackRecvCountUp()
{
	PlayAttackCount++;
	return PlayAttackCount;
}

int AttackMotionCountUp()
{
	MotionAttackCount++;
	if (MotionAttackCount > 30)
	{
		CheckPlayAttackCount();
	}

	return MotionAttackCount;
}

int	CheckPlayAttackCount()
{
	if (MotionAttackCount > 30 && PlayAttackCount <= 3)
	{
		//秦欧 矫档茄 蜡历 磊悼 脚绊
		//SendSetHackUser2( 1500 , MotionAttackCount-PlayAttackCount );
	}

	MotionAttackCount = 0;
	PlayAttackCount = 0;

	return TRUE;
}

struct	sCOPY_ITEM_INFO {
	DWORD	dwItemCode;
	int		ChkSum;
	int		Header;
};

sCOPY_ITEM_INFO	sCopyItemList[] =
{
	{	0,0,0	}

};

int	CheckCopyItem(Item *lpItem)
{
	int cnt;

	cnt = 0;

	if (!lpItem->szItemName[0])
		return FALSE;
	if (lpItem->SpecialItemFlag[0])
		return FALSE;

	if (!lpItem->BackUpKey || !lpItem->BackUpChkSum)
	{
		lpItem->BackUpKey = lpItem->iChk1;
		lpItem->BackUpChkSum = lpItem->iChk2;
	}

	while (1)
	{
		if (sCopyItemList[cnt].dwItemCode == 0)
			break;


		if (sCopyItemList[cnt].dwItemCode == lpItem->sItemID.ToInt())
		{
			if (sCopyItemList[cnt].ChkSum == (int)lpItem->iChk2 && sCopyItemList[cnt].Header == (int)lpItem->iChk1)
			{
				lpItem->SpecialItemFlag[0] = CHECK_COPY_ITEM;
				return TRUE;
			}
			if (sCopyItemList[cnt].ChkSum == (int)lpItem->BackUpChkSum && sCopyItemList[cnt].Header == (int)lpItem->BackUpKey)
			{
				lpItem->SpecialItemFlag[0] = CHECK_COPY_ITEM;
				return TRUE;
			}
		}
		cnt++;
	}


	return FALSE;
}

#define	_CHANGE_JOB_COUNT_MAX		FACE_MODEL_MAX
#define	_FACE_COUNT_MAX				HEAREPOTION_MAX

//检查角色模型
int	CheckUserModel(CharacterData *lpCharInfo)
{
	int cnt, cnt2, len;
	char	szBuff[64];
	char	*lpBuff;

	lpCharInfo->Player.szBodyModel[31] = 0;
	lpCharInfo->Player.szHeadModel[31] = 0;

	len = lstrlen(lpCharInfo->Player.szBodyModel);
	lstrcpy(szBuff, lpCharInfo->Player.szBodyModel);
	for (cnt = len - 1; cnt >= 0; cnt--)
	{
		if (szBuff[cnt] == '\\')
		{
			szBuff[cnt + 1] = 0;
			break;
		}
	}

	if (lstrcmpi(szBuff, "char\\tmABCD\\") != 0)
		return FALSE;
	lpBuff = &lpCharInfo->Player.szBodyModel[len - 3];
	if (lstrcmpi(lpBuff, "ini") != 0)
		return FALSE;

	switch (lpCharInfo->iClass)
	{
	case CHARACTERCLASS_Fighter:
		for (cnt = 0; cnt < _CHANGE_JOB_COUNT_MAX; cnt++)
		{
			for (cnt2 = 0; cnt2 < _FACE_COUNT_MAX; cnt2++)
			{
				if (lstrcmpi(szModel_FighterFaceName[cnt][cnt2], lpCharInfo->Player.szHeadModel) == 0)
					return TRUE;
			}
		}
		if (!lpCharInfo->Player.szHeadModel[0])
		{
			lstrcpy(lpCharInfo->Player.szHeadModel, szModel_FighterFaceName[0][0]);
			return TRUE;
		}
		break;
	case CHARACTERCLASS_Mechanician:
		for (cnt = 0; cnt < _CHANGE_JOB_COUNT_MAX; cnt++)
		{
			for (cnt2 = 0; cnt2 < _FACE_COUNT_MAX; cnt2++)
			{
				if (lstrcmpi(szModel_MechFaceName[cnt][cnt2], lpCharInfo->Player.szHeadModel) == 0)
					return TRUE;
			}
		}
		if (!lpCharInfo->Player.szHeadModel[0])
		{
			lstrcpy(lpCharInfo->Player.szHeadModel, szModel_MechFaceName[0][0]);
			return TRUE;
		}
		break;
	case CHARACTERCLASS_Archer:
		for (cnt = 0; cnt < _CHANGE_JOB_COUNT_MAX; cnt++)
		{
			for (cnt2 = 0; cnt2 < _FACE_COUNT_MAX; cnt2++)
			{
				if (lstrcmpi(szModel_ArcherFaceName[cnt][cnt2], lpCharInfo->Player.szHeadModel) == 0)
					return TRUE;
			}
		}
		if (!lpCharInfo->Player.szHeadModel[0])
		{
			lstrcpy(lpCharInfo->Player.szHeadModel, szModel_ArcherFaceName[0][0]);
			return TRUE;
		}

		break;
	case CHARACTERCLASS_Pikeman:
		for (cnt = 0; cnt < _CHANGE_JOB_COUNT_MAX; cnt++)
		{
			for (cnt2 = 0; cnt2 < _FACE_COUNT_MAX; cnt2++)
			{
				if (lstrcmpi(szModel_PikeFaceName[cnt][cnt2], lpCharInfo->Player.szHeadModel) == 0)
				{
					return TRUE;
				}
			}
		}
		if (!lpCharInfo->Player.szHeadModel[0])
		{
			lstrcpy(lpCharInfo->Player.szHeadModel, szModel_PikeFaceName[0][0]);
			return TRUE;
		}
		break;

	case 0:
		return TRUE;
	case CHARACTERCLASS_Atalanta:
		for (cnt = 0; cnt < _CHANGE_JOB_COUNT_MAX; cnt++)
		{
			for (cnt2 = 0; cnt2 < _FACE_COUNT_MAX; cnt2++)
			{
				if (lstrcmpi(szModel_AtalantaFaceName[cnt][cnt2], lpCharInfo->Player.szHeadModel) == 0)
					return TRUE;
			}
		}
		if (!lpCharInfo->Player.szHeadModel[0])
		{
			lstrcpy(lpCharInfo->Player.szHeadModel, szModel_AtalantaFaceName[0][0]);
			return TRUE;
		}
		break;
	case CHARACTERCLASS_Knight:
		for (cnt = 0; cnt < _CHANGE_JOB_COUNT_MAX; cnt++)
		{
			for (cnt2 = 0; cnt2 < _FACE_COUNT_MAX; cnt2++)
			{
				if (lstrcmpi(szModel_KnightFaceName[cnt][cnt2], lpCharInfo->Player.szHeadModel) == 0)
					return TRUE;
			}
		}
		if (!lpCharInfo->Player.szHeadModel[0])
		{
			lstrcpy(lpCharInfo->Player.szHeadModel, szModel_KnightFaceName[0][0]);
			return TRUE;
		}
		break;
	case CHARACTERCLASS_Magician:
		for (cnt = 0; cnt < _CHANGE_JOB_COUNT_MAX; cnt++)
		{
			for (cnt2 = 0; cnt2 < _FACE_COUNT_MAX; cnt2++)
			{
				if (lstrcmpi(szModel_MagicanFaceName[cnt][cnt2], lpCharInfo->Player.szHeadModel) == 0)
					return TRUE;
			}
		}
		if (!lpCharInfo->Player.szHeadModel[0])
		{
			lstrcpy(lpCharInfo->Player.szHeadModel, szModel_MagicanFaceName[0][0]);
			return TRUE;
		}
		break;
	case CHARACTERCLASS_Priestess:
		for (cnt = 0; cnt < _CHANGE_JOB_COUNT_MAX; cnt++)
		{
			for (cnt2 = 0; cnt2 < _FACE_COUNT_MAX; cnt2++)
			{
				if (lstrcmpi(szModel_PristessFaceName[cnt][cnt2], lpCharInfo->Player.szHeadModel) == 0)
					return TRUE;
			}
		}
		if (!lpCharInfo->Player.szHeadModel[0])
		{
			lstrcpy(lpCharInfo->Player.szHeadModel, szModel_PristessFaceName[0][0]);
			return TRUE;
		}
		break;
	case CHARACTERCLASS_Assassin:
		for (cnt = 0; cnt < _CHANGE_JOB_COUNT_MAX; cnt++)
		{
			for (cnt2 = 0; cnt2 < _FACE_COUNT_MAX; cnt2++)
			{
				if (lstrcmpi(szModel_AssaFaceName[cnt][cnt2], lpCharInfo->Player.szHeadModel) == 0)
					return TRUE;
			}
		}
		if (!lpCharInfo->Player.szHeadModel[0])
		{
			lstrcpy(lpCharInfo->Player.szHeadModel, szModel_AssaFaceName[0][0]);
			return TRUE;
		}
		break;
	case CHARACTERCLASS_Shaman:
		for (cnt = 0; cnt < _CHANGE_JOB_COUNT_MAX; cnt++)
		{
			for (cnt2 = 0; cnt2 < _FACE_COUNT_MAX; cnt2++)
			{
				if (lstrcmpi(szModel_ShamanFaceName[cnt][cnt2], lpCharInfo->Player.szHeadModel) == 0)
					return TRUE;
			}
		}
		if (!lpCharInfo->Player.szHeadModel[0])
		{
			lstrcpy(lpCharInfo->Player.szHeadModel, szModel_ShamanFaceName[0][0]);
			return TRUE;
		}
		break;
	}

	return FALSE;
}



#define		ROT_PLAYER_MAX		128
#define		ROT_PLAYER_MIN		80


int	Check_PlaySubReleaseFunc()
{
	DWORD	dwStartFunc;
	DWORD	dwEndFunc;
	DWORD	*lpStartFunc;
	int		cnt, len;
	DWORD	dwChkSum;

	dwStartFunc = (DWORD)Code_VRamBuffOpen;
	dwEndFunc = (DWORD)Check_PlaySubReleaseFunc;
	len = (dwEndFunc - dwStartFunc) >> 2;

	dwChkSum = 0;

	lpStartFunc = (DWORD *)dwStartFunc;

	if (len < 0)
		return FALSE;

	for (cnt = 0; cnt < len; cnt++)
		dwChkSum += (lpStartFunc[cnt] * ((cnt & 0x3FF) + 1));

	dwPlaySub_CheckResult = dwChkSum;

	if (PLAYSUB_CHECKRESULT != dwChkSum)
		return dwChkSum;

	return NULL;
}

sCHK_POTION_COUNT	sPotionTotalCount;
int	tXorPotionCount = 0;



DWORD	dwTotal_InvenItemCode;
DWORD	dwTotal_InvenItemPlayTime;



short	sChkLife[2];
short	sChkMana[2];
short	sChkStamina[2];
int		EnergyGraphErrorCount[4] = { 0,0,0,0 };


DWORD	dwTotal_CheckMoney = 0;
DWORD	dwTotal_CheckMoneyTime = 0;
#define	TOTAL_CHECK_MONEY_MASK	0x0018cccc
int		NChkMode = 0;

int GetAttackSpeedMainFrame(int AttackSpeed)
{
	int cnt;

	cnt = AttackSpeed - 6;
	if (cnt < 0)
		cnt = 0;
	if (cnt > 6)
		cnt = 6;

	return fONE + 32 * cnt;
}
int	GetAttackSpeedFrame(int AttackSpeed, int AddSpeed)
{
	int cnt;

	cnt = GetAttackSpeedMainFrame(AttackSpeed);
	if (AddSpeed < 6 && AddSpeed>0)
		cnt += AddSpeed * 32;

	return (80 * cnt) >> FLOATNS;
}
int	GetAttackSpeedFrame(int AttackSpeed)
{
	int cnt;

	cnt = GetAttackSpeedMainFrame(AttackSpeed);

	return (80 * cnt) >> FLOATNS;
}
int LoadFolder_Ini(char *szPath, char *szWildCard, char *szChgExt, int OftSave)
{
	HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;
	char	szFindPath[64];
	char	szFilePath[64];
	char	*lpPath;

	HANDLE hFindHandle2;
	WIN32_FIND_DATA	fd2;
	char	szFindPath2[64];

	smDPAT	*lpDPatTest[65536];
	int		DPatCount = 0;
	int		cnt;

	lstrcpy(szFindPath, szPath);
	lstrcat(szFindPath, "\\*.*");


	hFindHandle = FindFirstFile(szFindPath, &fd);
	if (hFindHandle != INVALID_HANDLE_VALUE)
	{
		while (1)
		{
			if ((fd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY) != 0)
			{
				wsprintf(szFindPath2, "%s\\%s\\%s", szPath, fd.cFileName, szWildCard);

				hFindHandle2 = FindFirstFile(szFindPath2, &fd2);
				if (hFindHandle2 != INVALID_HANDLE_VALUE)
				{
					while (1)
					{
						wsprintf(szFilePath, "%s\\%s\\%s", szPath, fd.cFileName, fd2.cFileName);


						if (OftSave)
						{
							if (szChgExt)
								lpPath = ChangeFileExt(szFilePath, szChgExt);
							else
								lpPath = 0;

							if (!lpPath) lpPath = szFilePath;

							lstrcpy(szFilePath, lpPath);

							//LoadOftenMeshPattern(szFilePath);
						}
						else
						{
							lpDPatTest[DPatCount] = smPattern.LoadCharactor(szFilePath);
							if (lpDPatTest[DPatCount])
								DPatCount++;
							else
								DPatCount = DPatCount;
						}

						if (FindNextFile(hFindHandle2, &fd2) == FALSE) break;
					}
					FindClose(hFindHandle2);
				}
			}

			if (FindNextFile(hFindHandle, &fd) == FALSE)
				break;
		}
		FindClose(hFindHandle);
	}

	for (cnt = 0; cnt < DPatCount; cnt++)
		smDPAT_Delete(lpDPatTest[cnt]);

	return TRUE;
}

sSOD_SCORE	sSodScore;
int			SodScoreFlag = 0;


char	szSOD_String[64] = { 0, };
BYTE	bSOD_StringColor[4];
int		SOD_StringCount = 0;
int		TeamScoreSort[4];
int		TeamMarkSort[4] = { 3 , 0 , 2 , 1 };
int		SoDGateFlag;


int SodTeamSort()
{
	int cnt, cnt1;
	int r1, r2;

	for (cnt = 0; cnt < 4; cnt++)
		TeamScoreSort[cnt] = cnt;

	for (cnt = 0; cnt < 4; cnt++)
	{
		for (cnt1 = cnt; cnt1 < 4; cnt1++)
		{
			r1 = TeamScoreSort[cnt];
			r2 = TeamScoreSort[cnt1];

			if (sSodScore.TeamScore[r1] < sSodScore.TeamScore[r2])
			{
				TeamScoreSort[cnt] = r2;
				TeamScoreSort[cnt1] = r1;
			}
		}
	}

	return TRUE;
}