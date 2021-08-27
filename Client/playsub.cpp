#include "StdAfx.h"

#include "smwsock.h"
#include "character.h"
#include "playmain.h"
#include "srcsound\\dxwav.h"
#include "fileread.h"

#include "particle.h"
#include "netplay.h"
#include "effectsnd.h"

#include "record.h"
#include "playsub.h"
#include "resource.h"
#include "drawsub.h"

#include "tjboy\\clanmenu\\tjclanDEF.h"
#include "tjboy\\clanmenu\\tjclan.h"
#include "tjboy\\clanmenu\\cE_CViewClanInfo.h"

#include "BellatraFontEffect.h"
#include "TextMessage.h"

#include "WinInt\\WinIntThread.h"
#include "FullZoomMap.h"
#include "FontImage.h"

extern HINSTANCE hinst;

int rsCheckHardCoreEventArea(int x, int y, int z);

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


int	PlaySub_StartFunc()
{
	return FALSE;
}
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
int	Mix_CodeVram()
{
	DWORD	dwTime;
	DWORD	dwNewTime;

	dwTime = (dwPlayTime >> 4) & 0xFF;
	dwNewTime = (dwTime << 24) | (dwTime << 16) | (dwTime << 8) | dwTime;

	dwTime = lpCodeVram[3];

	lpCodeVram[0] = (lpCodeVram[0] ^ dwTime) ^ dwNewTime;
	lpCodeVram[1] = (lpCodeVram[1] ^ dwTime) ^ dwNewTime;
	lpCodeVram[2] = (lpCodeVram[2] ^ dwTime) ^ dwNewTime;
	lpCodeVram[3] = dwNewTime;

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
int LoadOftenModels()
{
	return TRUE;
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
	int cnt;

	cnt = 0;
	while (szOftenNPC[cnt])
	{
		LoadOftenMeshPattern(szOftenNPC[cnt]);
		cnt++;
	}

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
int  LoadOftenItem()
{
	char szBuff[256];

	auto vpItemTable = ITEMHANDLE->GetItemTable();

	for (auto & pItem : vpItemTable)
	{
		if (pItem->szModelName == NULL)
			continue;
		wsprintf(szBuff, "Image\\sinImage\\Items\\DropItem\\it%s.ASE", pItem->szModelName);

		LoadOftenMeshPattern(szBuff);

		if (pItem->sBaseItemID.ToInt() == (sinGG1 | sin01))
			break;
	}

	return TRUE;
}
int CheckOftenMeshTextureSwap()
{
	return TRUE;
}
//设置用户铠甲
int SetPlayerArmor(int armor, int Kind)
{
	char szbuff[256] = { 0 };
	int jobNum;

	if ((PlayerArmor == armor && Kind == PlayerArmorFlag) || lpCurPlayer->bLoading || !lpCurPlayer->sCharacterData.Player.szHeadModel[0])
		return FALSE;
	if (armor == -1)
		armor = 0;

	jobNum = lpCurPlayer->sCharacterData.iClass;

	if (jobNum > MAX_JOBNUM)
		jobNum = 0;

	switch (Kind)
	{
	case 0:
		if (armor > ARMOR_FILE_MAX - 1)
			armor = ARMOR_FILE_MAX - 1;

		lstrcpy(szbuff, szArmorDirectory);
		lstrcat(szbuff, szArmorNumFile[ArmorJobNum[jobNum]][armor]);
		break;
	case 1:
		if (armor > COSTME_ARMOR_FILE_MAX - 1)
			armor = COSTME_ARMOR_FILE_MAX - 1;

		lstrcpy(szbuff, szArmorDirectory);
		lstrcat(szbuff, szCostmeArorNumFile[ArmorJobNum[jobNum]][armor]);
		break;
	case 2:
		if (armor > COSTME_NEW_ARMOR_FILE_MAX - 1)
			armor = COSTME_NEW_ARMOR_FILE_MAX - 1;

		lstrcpy(szbuff, szArmorDirectory);
		lstrcat(szbuff, szCostmeNewArorNumFile[ArmorJobNum[jobNum]][armor]);
		break;
	}

	lpCurPlayer->bLoading = TRUE;

	if (!szbuff[0])
	{
		lstrcpy(szbuff, szArmorDirectory);
		lstrcat(szbuff, szArmorNumFile[ArmorJobNum[jobNum]][0]);
	}

	AddLoaderPattern(lpCurPlayer, szbuff, lpCurPlayer->sCharacterData.Player.szHeadModel);

	PlayerArmor = armor;

	PlayerArmorFlag = Kind;

	return TRUE;
}

//设置角色铠甲
int SetChrArmor(Unit *lpChar, int ItemNum)
{
	char szbuff[256] = { 0 };
	int armor = 0;
	int jobNum;
	int Kind = 0;

	if (!lpChar->DisplayFlag || lpChar->wStickItems[smPLAYBUFF_ITEM_BODY] == ItemNum || lpChar->bLoading || !lpChar->sCharacterData.Player.szHeadModel[0])
		return FALSE;

	if (ItemNum >= 0)
	{
		ItemData * pItem = ITEMHANDLE->GetItemDataByNumber(ItemNum);

		switch (pItem->sBaseItemID.ToItemType())
		{
		case sinDA1:
		case sinDA2:
			Kind = 0;
			if ((pItem->sBaseItemID.ToItemIndex() >> 8) >= 77)
			{
				armor = ((pItem->sBaseItemID.ToItemIndex() >> 8) - 77);
				Kind = 2;
			}
			else if ((pItem->sBaseItemID.ToItemIndex() >> 8) > 25)
				armor = ((pItem->sBaseItemID.ToItemIndex() >> 8) - 16);
			else
				armor = pItem->sBaseItemID.ToItemIndex() >> 8;
			break;
		case sinCA1:
			Kind = 1;
			armor = ((pItem->sBaseItemID.ToItemIndex() >> 8) - 47);
			break;
		}
	}
	else
		armor = 0;

	jobNum = lpChar->sCharacterData.iClass;

	if (jobNum > MAX_JOBNUM)
		jobNum = 0;

	switch (Kind)
	{
	case 0:
		if (armor < 0)
			armor = 0;
		if (armor > ARMOR_FILE_MAX - 1)
			armor = ARMOR_FILE_MAX - 1;
		lstrcpy(szbuff, szArmorDirectory);
		lstrcat(szbuff, szArmorNumFile[ArmorJobNum[jobNum]][armor]);
		break;
	case 1:
		if (armor < 0)
			armor = 0;
		if (armor > COSTME_ARMOR_FILE_MAX - 1)
			armor = COSTME_ARMOR_FILE_MAX - 1;

		lstrcpy(szbuff, szArmorDirectory);
		lstrcat(szbuff, szCostmeArorNumFile[ArmorJobNum[jobNum]][armor]);
		break;
	case 2:
		if (armor < 0)
			armor = 0;
		if (armor > COSTME_NEW_ARMOR_FILE_MAX - 1)
			armor = COSTME_NEW_ARMOR_FILE_MAX - 1;

		lstrcpy(szbuff, szArmorDirectory);
		lstrcat(szbuff, szCostmeNewArorNumFile[ArmorJobNum[jobNum]][armor]);
		break;
	}

	if (!szbuff[0])
	{
		lstrcpy(szbuff, szArmorDirectory);
		lstrcat(szbuff, szArmorNumFile[ArmorJobNum[jobNum]][0]);
	}

	lpChar->bLoading = TRUE;
	AddLoaderPattern(lpChar, szbuff, lpChar->sCharacterData.Player.szHeadModel);

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

//改变模型外观
int	ChangeModelSkin(Unit *lpChar, int ComicArmor, int ComicHeadNum, char *szArmor, char *szHead)
{
	char szArmorName[32];
	char szHeadName[32];
	char szbuff1[256];
	char szbuff2[256];

	int len, cnt;
	int jobNum;
	int SelCount;
	int FindArmor, FindHead;
	char *lpArmorFile;
	char *lpHeadFile;

	char **lpSelFace = 0;
	char *lpSelFaceName = 0;

	jobNum = lpChar->sCharacterData.iClass;

	if (jobNum > MAX_JOBNUM)
		jobNum = 0;

	if (szArmor)
		lpArmorFile = szArmor;
	else
		lpArmorFile = lpChar->sCharacterData.Player.szBodyModel;

	if (szHead)
		lpHeadFile = szHead;
	else
		lpHeadFile = lpChar->sCharacterData.Player.szHeadModel;

	szArmorName[0] = 0;
	szHeadName[0] = 0;

	len = lstrlen(lpArmorFile);

	for (cnt = len - 1; cnt >= 0; cnt--)
	{
		if (lpArmorFile[cnt] == '\\')
		{
			lstrcpy(szArmorName, &lpArmorFile[cnt + 1]);
			break;
		}
	}

	lstrcpy(szHeadName, lpHeadFile);

	if (!szArmorName[0] || !szHeadName[0])
		return FALSE;

	SelCount = ComicHeadNum;

	FindArmor = 0;
	FindHead = 0;

	if (FindArmor == 0)
	{
		for (cnt = 0; cnt < ARMOR_FILE_MAX; cnt++)
		{
			if (lstrcmpi(szArmorName, szArmorNumFile[ArmorJobNum[jobNum]][cnt]) == 0)
			{
				lstrcpy(szArmorName, szArmorNumFile[ArmorJobNum[jobNum]][cnt]);

				FindArmor++;
				break;
			}
		}
	}
	if (FindArmor == 0)
	{
		for (cnt = 0; cnt < COSTME_ARMOR_FILE_MAX; cnt++)
		{
			if (lstrcmpi(szArmorName, szCostmeArorNumFile[ArmorJobNum[jobNum]][cnt]) == 0)
			{
				lstrcpy(szArmorName, szCostmeArorNumFile[ArmorJobNum[jobNum]][cnt]);
				FindArmor++;
				break;
			}
		}
	}
	if (FindArmor == 0)
	{
		for (cnt = 0; cnt < COSTME_NEW_ARMOR_FILE_MAX; cnt++)
		{
			if (lstrcmpi(szArmorName, szCostmeNewArorNumFile[ArmorJobNum[jobNum]][cnt]) == 0)
			{
				lstrcpy(szArmorName, szCostmeNewArorNumFile[ArmorJobNum[jobNum]][cnt]);
				FindArmor++;
				break;
			}
		}
	}

	int FindFaceValue = FindFaceSkin(lpChar, szHeadName, &lpSelFace, &lpSelFaceName);
	if (FindFaceValue < 0)
		return FALSE;
	int HairCode = FindFaceValue & 0xFF;
	int FaceCode = FindFaceValue >> 8;

	if (CheckHairSkinCode(lpChar->sCharacterData.Player.iPlayerID) == FALSE)
		lpChar->sCharacterData.Player.iPlayerID = GetHairSkinCode(FaceCode, HairCode);

	switch (jobNum)
	{
	case CHARACTERCLASS_Fighter:
		lstrcpy(szHeadName, szModel_FighterFaceName[SelCount][HairCode]);
		break;
	case CHARACTERCLASS_Mechanician:
		lstrcpy(szHeadName, szModel_MechFaceName[SelCount][HairCode]);
		break;
	case CHARACTERCLASS_Archer:
		lstrcpy(szHeadName, szModel_ArcherFaceName[SelCount][HairCode]);
		break;
	case CHARACTERCLASS_Pikeman:
		lstrcpy(szHeadName, szModel_PikeFaceName[SelCount][HairCode]);
		break;
	case CHARACTERCLASS_Atalanta:
		lstrcpy(szHeadName, szModel_AtalantaFaceName[SelCount][HairCode]);
		break;
	case CHARACTERCLASS_Knight:
		lstrcpy(szHeadName, szModel_KnightFaceName[SelCount][HairCode]);
		break;
	case CHARACTERCLASS_Magician:
		lstrcpy(szHeadName, szModel_MagicanFaceName[SelCount][HairCode]);
		break;
	case CHARACTERCLASS_Priestess:
		lstrcpy(szHeadName, szModel_PristessFaceName[SelCount][HairCode]);
		break;
	case CHARACTERCLASS_Assassin:
		lstrcpy(szHeadName, szModel_AssaFaceName[SelCount][HairCode]);
		break;
	case CHARACTERCLASS_Shaman:
		lstrcpy(szHeadName, szModel_ShamanFaceName[SelCount][HairCode]);
		break;
	}
	lstrcpy(szbuff1, szArmorDirectory);
	lstrcat(szbuff1, szArmorName);
	lstrcpy(szbuff2, szHeadName);

	lpChar->bLoading = TRUE;
	AddLoaderPattern(lpChar, szbuff1, szbuff2);

	return TRUE;
}
//改变发型模型
int ChangeHairModel(int HairCode)
{
	Unit *lpChar = lpCurPlayer;

	int jobNum = lpChar->sCharacterData.iClass;
	char *lpHeadName = lpChar->sCharacterData.Player.szHeadModel;
	char **lpSelFace = 0;
	char *lpSelFaceName = 0;

	if (HairCode < 0 || HairCode >= HEAREPOTION_MAX)
		return FALSE;

	int FindFaceValue = FindFaceSkin(lpChar, lpHeadName, &lpSelFace, &lpSelFaceName);

	if (FindFaceValue < 0 || lpSelFace == 0)
		return FALSE;

	int FaceCode = FindFaceValue >> 8;

	if (lstrcmpi(lpChar->sCharacterData.Player.szHeadModel, lpSelFace[HairCode]) == 0)
		return FALSE;

	lstrcpy(lpChar->sCharacterData.Player.szHeadModel, lpSelFace[HairCode]);
	lpChar->sCharacterData.Player.iPlayerID = GetHairSkinCode(FaceCode, HairCode);

	lpChar->bLoading = TRUE;
	AddLoaderPattern(lpChar, lpChar->sCharacterData.Player.szBodyModel, lpChar->sCharacterData.Player.szHeadModel);

	lpCurPlayer->sCharacterData.bUpdateInfo[0]++;
	ReformCharForm();
	SendSetObjectSerial(lpCurPlayer->iID);
	SaveGameData();

	StartSkill(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, SKILL_UP1);
	SkillPlaySound(SKILL_SOUND_LEARN, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);


	return TRUE;
}

// 锻造颜色

const int  CONST_AGINGBCOLOR_MAX = 24;

static short	AgingBlinkColor[CONST_AGINGBCOLOR_MAX][6] =
{
	{100	,40		,90		,0		,smTEXTATE_MIXNON		,smTEXSTATE_FS_NONE		},
	{120	,100	,10		,0		,smTEXTATE_MIXNON		,smTEXSTATE_FS_NONE		},
	{0		,110	,30		,0		,smTEXTATE_MIXNON		,smTEXSTATE_FS_NONE		},
	{0		,50		,140	,0		,smTEXTATE_MIXS01		,smTEXSTATE_FS_SCROLL5	},
	{100	,0		,90		,0		,smTEXTATE_MIXS02		,smTEXSTATE_FS_SCROLL6	},
	{150	,60		,0		,0		,smTEXTATE_MIXS03		,smTEXSTATE_FS_SCROLL6	},
	{150	,10		,0		,0		,smTEXTATE_MIXS04		,smTEXSTATE_FS_SCROLL8	},
	{20		,220	,190	,0		,smTEXTATE_MIXS05		,smTEXSTATE_FS_SCROLL8	},
	{10		,220	,30		,0		,smTEXTATE_MIXS05		,smTEXSTATE_FS_SCROLL8	},
	{170	,40		,170	,0		,smTEXTATE_MIXS05		,smTEXSTATE_FS_SCROLL9	},
	{250	,30		,160	,0		,smTEXTATE_MIXS05		,smTEXSTATE_FS_SCROLL9	},
	{30		,190	,255	,0		,smTEXTATE_MIXS05		,smTEXSTATE_FS_SCROLL9	},
	{250	,130	,30		,0		,smTEXTATE_MIXS05		,smTEXSTATE_FS_SCROLL9	},
	{120	,30		,30		,0		,smTEXTATE_MIXM01		,smTEXSTATE_FS_SCROLL10	},
	{130	,0		,255	,0		,smTEXTATE_MIXM01		,smTEXSTATE_FS_SCROLL10	},
	{220	,240	,70		,0		,smTEXTATE_MIXM01		,smTEXSTATE_FS_SCROLL10	},
	{240	,240	,240	,0		,smTEXTATE_MIXM01		,smTEXSTATE_FS_SCROLL10	},
	{218	,15		,15		,0		,smTEXTATE_MIXM01		,smTEXSTATE_FS_SCROLL10	},
	{0		,255	,145	,0		,smTEXTATE_MIXM01		,smTEXSTATE_FS_SCROLL10	},
	{22		,42		,172	,0		,smTEXTATE_MIXM01		,smTEXSTATE_FS_SCROLL10	},
	{102	,0		,255	,0		,smTEXTATE_MIXM01		,smTEXSTATE_FS_SCROLL10	}
};

static short	CraftBlinkColor[6][6] =
{
	{13		,0		,5		,0		,smTEXTATE_MIXM05		,smTEXSTATE_FS_SCROLL4	},
	{13		,0		,6		,0		,smTEXTATE_MIXM01		,smTEXSTATE_FS_SCROLL4	},
	{13		,0		,7		,0		,smTEXTATE_MIXM02		,smTEXSTATE_FS_SCROLL5	},
	{13		,0		,8		,0		,smTEXTATE_MIXM03		,smTEXSTATE_FS_SCROLL5	},
	{13		,0		,9		,0		,smTEXTATE_MIXM04		,smTEXSTATE_FS_SCROLL5	},
	{13		,0		,10		,0		,smTEXTATE_MIXM05		,smTEXSTATE_FS_SCROLL5	}
};
int GetItemKindFromBliankColor(smCHARTOOL *lpCharTool)
{
	int cnt;

	lpCharTool->TexMixCode = -1;
	lpCharTool->TexScroll = 0;

	for (cnt = 0; cnt < CONST_AGINGBCOLOR_MAX; cnt++)
	{
		if (AgingBlinkColor[cnt][0] == lpCharTool->sColors[SMC_R] &&
			AgingBlinkColor[cnt][1] == lpCharTool->sColors[SMC_G] &&
			AgingBlinkColor[cnt][2] == lpCharTool->sColors[SMC_B] &&
			AgingBlinkColor[cnt][3] == lpCharTool->sColors[SMC_A])
		{
			lpCharTool->TexMixCode = AgingBlinkColor[cnt][4];
			lpCharTool->TexScroll = AgingBlinkColor[cnt][5];
			return TRUE;
		}
	}
	for (cnt = 0; cnt < 6; cnt++)
	{
		if (CraftBlinkColor[cnt][0] == lpCharTool->sColors[SMC_R] &&
			CraftBlinkColor[cnt][1] == lpCharTool->sColors[SMC_G] &&
			CraftBlinkColor[cnt][2] == lpCharTool->sColors[SMC_B] &&
			CraftBlinkColor[cnt][3] == lpCharTool->sColors[SMC_A])
		{
			lpCharTool->TexMixCode = CraftBlinkColor[cnt][4];
			lpCharTool->TexScroll = CraftBlinkColor[cnt][5];
			return TRUE;
		}
	}
	return FALSE;
}

int sinSetCharItem(DWORD CODE, DWORD Posi, BOOL SetFlag)
{
	DWORD	dwCode;
	Item *lpItemInfo;
	DWORD	dwMotionCode;
	int		FrameCounter;
	int		cnt;

	switch (Posi)
	{
	case ITEMSLOTFLAG_LeftHand:
		if (SetFlag)
		{
			lpCurPlayer->SetTool(CODE, hvPOSI_LHAND);

			lpItemInfo = &cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sItem;
			if (!lpItemInfo->szItemName[0])
				lpItemInfo = &cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem;

			lpCurPlayer->HvLeftHand.ColorBlink = lpItemInfo->EffectBlink[0];
			memcpy(lpCurPlayer->HvLeftHand.sColors, lpItemInfo->EffectColor, sizeof(short) * 4);
			lpCurPlayer->HvLeftHand.ColorEffect = lpItemInfo->bEnableEffect;
			lpCurPlayer->HvLeftHand.BlinkScale = lpItemInfo->ScaleBlink[0];
			lpCurPlayer->HvLeftHand.ElementEffect = lpItemInfo->ItemElement;
			lpCurPlayer->HvLeftHand.EffectKind = 0;

			if (lpItemInfo->eCraftType == ITEMCRAFTTYPE_Aging)
			{
				cnt = lpItemInfo->sAgeLevel;
				if (cnt >= 4 && cnt <= CONST_AGINGBCOLOR_MAX)
				{
					cnt -= 4;
					lpCurPlayer->HvLeftHand.ColorBlink = 9;
					lpCurPlayer->HvLeftHand.sColors[SMC_R] = AgingBlinkColor[cnt][0];
					lpCurPlayer->HvLeftHand.sColors[SMC_G] = AgingBlinkColor[cnt][1];
					lpCurPlayer->HvLeftHand.sColors[SMC_B] = AgingBlinkColor[cnt][2];
					lpCurPlayer->HvLeftHand.sColors[SMC_A] = AgingBlinkColor[cnt][3];
				}
			}
			if (lpItemInfo->eCraftType == ITEMCRAFTTYPE_Mixing)
			{
				cnt = lpItemInfo->sMixID;
				if (cnt >= 6 && cnt <= 10)
					cnt -= 5;
				else
				{
					if (cnt == 0)
						cnt = 0;
					else
						cnt = -1;
				}
				if (cnt >= 0)
				{
					lpCurPlayer->HvLeftHand.ColorBlink = 9;
					lpCurPlayer->HvLeftHand.sColors[SMC_R] = CraftBlinkColor[cnt][0];
					lpCurPlayer->HvLeftHand.sColors[SMC_G] = CraftBlinkColor[cnt][1];
					lpCurPlayer->HvLeftHand.sColors[SMC_B] = CraftBlinkColor[cnt][2];
					lpCurPlayer->HvLeftHand.sColors[SMC_A] = CraftBlinkColor[cnt][3];
				}
			}

			GetItemKindFromBliankColor(&lpCurPlayer->HvLeftHand);

			//任务武器
			if (lpCurPlayer->HvLeftHand.ColorEffect)
				AssaParticle_ClassUpWeapon(lpCurPlayer);

			if (lpCurPlayer->HvLeftHand.ElementEffect)
				AssaParticle_ElementWeapon(lpCurPlayer, lpCurPlayer->HvLeftHand.ElementEffect, LEFTHAND);
		}
		else
			lpCurPlayer->SetTool(0, hvPOSI_LHAND);
		break;

	case ITEMSLOTFLAG_RightHand:
		if (SetFlag)
		{
			lpCurPlayer->SetTool(CODE, hvPOSI_RHAND);

			lpItemInfo = &cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem;
			lpCurPlayer->HvRightHand.ColorBlink = lpItemInfo->EffectBlink[0];
			memcpy(lpCurPlayer->HvRightHand.sColors, lpItemInfo->EffectColor, sizeof(short) * 4);
			lpCurPlayer->HvRightHand.ColorEffect = lpItemInfo->bEnableEffect;
			lpCurPlayer->HvRightHand.BlinkScale = lpItemInfo->ScaleBlink[0];
			lpCurPlayer->HvRightHand.ElementEffect = lpItemInfo->ItemElement;
			lpCurPlayer->HvRightHand.EffectKind = 0;

			if (lpItemInfo->eCraftType == ITEMCRAFTTYPE_Aging)
			{
				cnt = lpItemInfo->sAgeLevel;
				if (cnt >= 4 && cnt <= CONST_AGINGBCOLOR_MAX)
				{
					cnt -= 4;
					lpCurPlayer->HvRightHand.ColorBlink = 9;
					lpCurPlayer->HvRightHand.sColors[SMC_R] = AgingBlinkColor[cnt][0];
					lpCurPlayer->HvRightHand.sColors[SMC_G] = AgingBlinkColor[cnt][1];
					lpCurPlayer->HvRightHand.sColors[SMC_B] = AgingBlinkColor[cnt][2];
					lpCurPlayer->HvRightHand.sColors[SMC_A] = AgingBlinkColor[cnt][3];
				}
			}
			if (lpItemInfo->eCraftType == ITEMCRAFTTYPE_Mixing)
			{
				cnt = lpItemInfo->sMixID;
				if (cnt >= 6 && cnt <= 10)
					cnt -= 5;
				else
				{
					if (cnt == 0)
						cnt = 0;
					else
						cnt = -1;
				}
				if (cnt >= 0)
				{
					lpCurPlayer->HvRightHand.ColorBlink = 9;
					lpCurPlayer->HvRightHand.sColors[SMC_R] = CraftBlinkColor[cnt][0];
					lpCurPlayer->HvRightHand.sColors[SMC_G] = CraftBlinkColor[cnt][1];
					lpCurPlayer->HvRightHand.sColors[SMC_B] = CraftBlinkColor[cnt][2];
					lpCurPlayer->HvRightHand.sColors[SMC_A] = CraftBlinkColor[cnt][3];
				}
			}

			GetItemKindFromBliankColor(&lpCurPlayer->HvRightHand);

			if (lpCurPlayer->HvRightHand.ColorEffect)
				AssaParticle_ClassUpWeapon(lpCurPlayer);

			if (lpCurPlayer->HvRightHand.ElementEffect)
				AssaParticle_ElementWeapon(lpCurPlayer, lpCurPlayer->HvRightHand.ElementEffect, RIGHTHAND);
		}
		else
			lpCurPlayer->SetTool(0, hvPOSI_RHAND);
		break;
	case ITEMSLOTFLAG_Costume:
	case ITEMSLOTFLAG_Armor:
		dwMotionCode = lpCurPlayer->psModelAnimation->iType;
		FrameCounter = lpCurPlayer->iFrameTimer;

		if (CODE != NULL)
		{
			if (SetFlag)
			{
				dwCode = CODE;

				switch (dwCode&sinITEM_MASK2)
				{
				case sinDA1:
				case sinDA2:
					if (((dwCode&sinITEM_MASK3) >> 8) >= 77)
						SetPlayerArmor(((dwCode&sinITEM_MASK3) >> 8) - 77, 2);
					else if (((dwCode&sinITEM_MASK3) >> 8) > 25)
						SetPlayerArmor(((dwCode&sinITEM_MASK3) >> 8) - 16, 0);
					else
						SetPlayerArmor((dwCode&sinITEM_MASK3) >> 8, 0);
					break;
				case sinCA1:
					SetPlayerArmor(((dwCode&sinITEM_MASK3) >> 8) - 47, 1);
					break;
				}
				lpCurPlayer->wStickItems[smPLAYBUFF_ITEM_BODY] = ITEMHANDLE->GetItemNumberFromID(dwCode);
			}
			else
			{
				SetPlayerArmor(0, 0);
				lpCurPlayer->wStickItems[smPLAYBUFF_ITEM_BODY] = -2;
			}
			if (dwMotionCode == ANIMATIONTYPE_Die)
			{
				lpCurPlayer->SetMotionFromCode(dwMotionCode);
				lpCurPlayer->iFrame = (lpCurPlayer->psModelAnimation->EndFrame - 1) * 160;
				lpCurPlayer->iFrameTimer = FrameCounter;
			}
		}
		else
		{
			SetPlayerArmor(-1, 0);
			lpCurPlayer->wStickItems[smPLAYBUFF_ITEM_BODY] = -2;
		}
		break;
	case ITEMSLOTFLAG_WingRight:
		if (SetFlag)
		{
			lpCurPlayer->dwWingEffectCode = CODE;
			ParkWingEffect(lpCurPlayer, CODE);
		}
		else
			lpCurPlayer->dwWingEffectCode = 0;
		break;
	}
	return TRUE;
}
// 丢物品到地图
int sinThrowItemToFeild(ItemData *pItem)
{
	ItemData	sThrowItem;
	int		ThrowItemBackup = 0;

	// BI物品不能丢弃
	if ((pItem->sItem.sItemID.ToItemType()) == sinBI1 ||
		(pItem->sItem.sItemID.ToItemType()) == sinBI2)
	{
		if (pItem->sItem.iPotionCount == 0)
			return FALSE;
	}

	if (cWareHouse.OpenFlag)
	{
		if (!cWareHouse.CloseWareHouse())
		{
			pItem->bValid = 0;
			return FALSE;
		}
	}

	if (lpCurPlayer->iLoadedMapIndex >= 0 && STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == QUEST_ARENA_FIELD)
	{
		if ((pItem->sItem.sItemID.ToItemType()) != sinFO1 &&
			(pItem->sItem.sItemID.ToItemType()) != sinCH1)
			return FALSE;

		if (pItem->sItem.iPotionCount != 100)
			return FALSE;
	}

	if (pItem->sItem.sItemID.ToInt() != (sinGG1 | sin01) && !pItem->bValid)
		return FALSE;

	if (pItem->sItem.iPotionCount == 100)
	{
		int BlessCristalCode = -1;
		int BlessSolderTotal;

		switch (pItem->sItem.sItemID.ToInt())
		{
		case sinGP1 | sin14:
			BlessCristalCode = 0;
			break;
		case sinGP1 | sin15:
			BlessCristalCode = 1;
			break;
		case sinGP1 | sin16:
			BlessCristalCode = 2;
			break;
		}
		if (BlessCristalCode >= 0)
		{
			if (!rsBlessCastle.CastleMode || (lpCurPlayer->iLoadedMapIndex >= 0 && STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID != rsCASTLE_FIELD) && !lpCurPlayer->Clan_CastleMasterFlag)
			{
				cMessageBox.ShowMessageEvent("   你不能够使用这个水晶   ");
				return FALSE;
			}

			BlessSolderTotal = rsBlessCastle.bCrystalSolderCount[0] + rsBlessCastle.bCrystalSolderCount[1] + rsBlessCastle.bCrystalSolderCount[2] + rsBlessCastle.bCrystalSolderCount[3];

			if (rsBlessCastle.bCrystalSolderCount[BlessCristalCode] >= srCASLTE_SOLDER_KIND_MAX || BlessSolderTotal >= srCASLTE_SOLDER_CLAN_MAX)
			{
				cMessageBox.ShowMessageEvent("  It has already exceeded amount of summons  ");
				return FALSE;
			}
		}
	}

	if (!CheckItemForm(&pItem->sItem))
	{
		SendSetHackUser(80);
		return TRUE;
	}

	if (cShop.OpenFlag || SkillMasterFlag || cCraftItem.OpenFlag || cAging.OpenFlag || SmeltingItem.OpenFlag || ManufactureItem.m_OpenFlag || cMixtureReset.OpenFlag || cElement.OpenFlag || cCaravan.OpenFlag || cSocket.OpenFlag)
	{
		if (pItem->sItem.sItemID.ToInt() == (sinGG1 | sin01))
			return FALSE;
	}

	if ((pItem->sItem.sItemID.ToItemBase()) == (sinPM1&sinITEM_MASK1))
	{
		ThrowItemBackup = 1;
		memcpy(&sThrowItem, pItem, sizeof(ItemData));
		ReformItem(&pItem->sItem);
	}

	if (ThrowPutItem(pItem, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ) == TRUE)
	{
		SubInvenItemCode(&pItem->sItem);
		pItem->bValid = 0;
		return TRUE;
	}

	if (ThrowItemBackup)
		memcpy(pItem, &sThrowItem, sizeof(ItemData));

	return FALSE;
}

//使用药水
int sinActionPotion()
{
	if (sinGetLife() > 0 && lpCurPlayer->psModelAnimation->iType != ANIMATIONTYPE_Potion &&
		lpCurPlayer->psModelAnimation->iType != ANIMATIONTYPE_Die)
	{
		if (lpCurPlayer->psModelAnimation->iType == ANIMATIONTYPE_Attack || lpCurPlayer->psModelAnimation->iType == ANIMATIONTYPE_Skill)
			lpCurPlayer->dwNextMotionCode = ANIMATIONTYPE_Potion;
		else
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Potion);
		return TRUE;
	}

	return FALSE;
}

//传送卷轴
int	ActionEtherCore(ItemData *lpItem)
{
	DWORD	dwCode = lpItem->sItem.sItemID.ToInt();

	if (lpCurPlayer->iLoadedMapIndex >= 0 &&
		STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapType == MAPTYPE_ChessRoom ||
		lpCurPlayer->sCharacterData.wPlayerKilling[0])
		return TRUE;

	if (sinGetLife() > 0 && lpCurPlayer->psModelAnimation->iType != ANIMATIONTYPE_Die)
	{
		if (lpCurPlayer->psModelAnimation->iType == ANIMATIONTYPE_Attack || lpCurPlayer->psModelAnimation->iType == ANIMATIONTYPE_Skill)
			lpCurPlayer->dwNextMotionCode = ANIMATIONTYPE_Potion;
		else
		{
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Potion);
			StartEffect(lpCurPlayer->pX, lpCurPlayer->pY + 48 * fONE, lpCurPlayer->pZ, EFFECT_RETURN1);
			SkillPlaySound(SKILL_SOUND_LEARN, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
		}

		UseEtherCoreCode = dwCode;

		if ((lpItem->sItem.sItemID.ToItemType()) == sinEC1)
			SendUseItemCodeToServer(&lpItem->sItem);

		return TRUE;
	}

	return FALSE;
}
//获取死亡经验减少的部分
int GetDeathPenalty()
{
	Item	*lpItemInfo;

	int	Penalty = 0;

	if (sInven[4].ItemIndex)
	{
		lpItemInfo = &cInvenTory.InvenItem[sInven[4].ItemIndex - 1].sItem;

		if (lpItemInfo->sItemID.ToInt() == (sinOR2 | sin01) && lpItemInfo->eCraftType == ITEMCRAFTTYPE_Aging)
		{
			if (lpItemInfo->sAgeLevel >= Penalty)
				Penalty = lpItemInfo->sAgeLevel;
		}
	}

	if (sInven[5].ItemIndex)
	{
		lpItemInfo = &cInvenTory.InvenItem[sInven[5].ItemIndex - 1].sItem;

		if (lpItemInfo->sItemID.ToInt() == (sinOR2 | sin01) && lpItemInfo->eCraftType == ITEMCRAFTTYPE_Aging)
		{
			if (lpItemInfo->sAgeLevel >= Penalty)
				Penalty = lpItemInfo->sAgeLevel;
		}
	}

	if (lpCurPlayer->iLoadedMapIndex >= 0 && STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapType == MAPTYPE_BlessCastle)
		return 0;

	lpItemInfo = FindItemFromCode(sinBI1 | sin04);

	if (lpItemInfo)
	{
		SendUseItemCodeToServer(lpItemInfo);
		cInvenTory.DeleteInvenItemToServer(lpItemInfo->sItemID.ToInt(), lpItemInfo->iChk1, lpItemInfo->iChk2);
		PlayUsed_Resurrection++;
		return 0;
	}
	if (Penalty >= 8)
		return 100;

	if (Penalty >= 6)
		return 50;

	if ((sinQuest_levelLog&QUESTBIT_LEVEL_85) != 0 && lpCurPlayer->sCharacterData.iLevel >= 85)
		return 50;
	return 33;
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

//获取经验值
INT64 GetExp64(CharacterData *sCharacterData)
{
	INT64 exp1, exp2;
	exp1 = (INT64)sCharacterData->iExp;
	exp2 = (INT64)sCharacterData->iExp;

	return (exp2 << 32) | (exp1 & 0xFFFFFFFF);
}
//设置经验
int	SetExp64(CharacterData *sCharacterData, INT64 Exp64)
{
	sCharacterData->iExp = (int)(Exp64 >> 32);
	sCharacterData->iExp = (int)(Exp64 & 0xFFFFFFFF);

	return sCharacterData->iExp;
}
int SetExp(int Exp_High, int Exp, int Flag)
{
	INT64 exp64;
	INT64 iexp;
	INT64 ChkSum;
	int level;

	exp64 = GAMEUNIT->GetExp(lpCurPlayer);

	exp64 = (INT64(Exp_High) << 32) | (INT64(Exp) & 0xFFFFFFFF);
	SetExp64(&lpCurPlayer->sCharacterData, exp64);

	ReformCharForm();

	level = lpCurPlayer->sCharacterData.iLevel;
	iexp = uUnitExpTables[level];

	if (iexp >= 0 && exp64 >= iexp && lpCurPlayer->sCharacterData.iLevel < UNIT_LEVEL_MAX)
	{
		if (Flag == FALSE)
		{
			ChkSum = CheckLevelTable();
			if (LevelTableSum == ChkSum)
			{
				level = GetLevelFromExp(exp64);
				lpCurPlayer->sCharacterData.iLevel = level;

				//lpCurPlayer->sCharacterData.iOwnerID = (int)uUnitExpTables[level];
				StartEffect(lpCurPlayer->pX, lpCurPlayer->pY + 32 * fONE, lpCurPlayer->pZ, EFFECT_LEVELUP1);
				esPlaySound(7, 400);

				ReformCharForm();

				SendPlayUpdateInfo();
				SaveGameData();

				return TRUE;
			}
		}
	}

	return FALSE;
}
//增加经验
int AddExp(int Exp)
{
	int Level;
	INT64 iexp;
	INT64 ChkSum;
	INT64 exp64;
	int mlevel;

	exp64 = GAMEUNIT->GetExp(lpCurPlayer);

	mlevel = UNIT_LEVEL_MAX - 1;

	if (exp64 < uUnitExpTables[mlevel])
		exp64 += Exp;

	SetExp64(&lpCurPlayer->sCharacterData, exp64);

	ReformCharForm();

	Level = lpCurPlayer->sCharacterData.iLevel;
	iexp = uUnitExpTables[Level];

	if (iexp >= 0 && exp64 >= iexp && lpCurPlayer->sCharacterData.iLevel < UNIT_LEVEL_MAX)
	{
		// 升级
		ChkSum = CheckLevelTable();

		if (LevelTableSum != ChkSum)
			return FALSE;

		// 经验太多获取新的等级,防止经验过多等级出错
		mlevel = GetLevelFromExp(exp64);
		lpCurPlayer->sCharacterData.iLevel = mlevel;

//		lpCurPlayer->sCharacterData.iOwnerID = (int)uUnitExpTables[mlevel];
		StartEffect(lpCurPlayer->pX, lpCurPlayer->pY + 32 * fONE, lpCurPlayer->pZ, EFFECT_LEVELUP1);
		esPlaySound(7, 400);

		ReformCharForm();

		SendPlayUpdateInfo();
		SaveGameData();
	}

	return TRUE;
}
//检查地图经验
int CheckFieldContExp()
{
	int Level;
	INT64 LowExp;
	INT64 HighExp;
	INT64 exp;
	INT64 exp64;

	Level = lpCurPlayer->sCharacterData.iLevel;
	if (Level >= 11)
	{
		LowExp = uUnitExpTables[Level - 1];
		HighExp = uUnitExpTables[Level];
		exp = (HighExp - LowExp) / 100; //1%

		exp64 = GAMEUNIT->GetExp(lpCurPlayer);

		exp = exp64 - exp;
		if (exp < LowExp)
			return FALSE;
	}
	else
	{
		if (lpCurPlayer->iLoadedMapIndex >= 0 && STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapType != MAPTYPE_Forest)
			return FALSE;
	}

	return TRUE;
}
//获取下一等级的经验
INT64 GetNextExp(int Level)
{
	return uUnitExpTables[Level];
}

//死亡角色的经验
int DeadPlayerExp(Unit *lpChar)
{
	int Level;
	INT64 LowExp;
	INT64 HighExp;
	INT64 exp;
	INT64 ep;
	INT64 exp64;
	int Money;
	int ExpLower = 0;
	int	Penalty = GetDeathPenalty();

	Level = lpChar->sCharacterData.iLevel;
	if (Level >= 11)
	{
		LowExp = uUnitExpTables[Level - 1];
		HighExp = uUnitExpTables[Level];
		if (Penalty)
			exp = (HighExp - LowExp) / Penalty;
		else
			exp = 0;

		exp64 = GAMEUNIT->GetExp(lpCurPlayer);

		if (exp64 >= LowExp)
		{
			ep = exp64;
			exp64 -= exp;
			if (exp64 < LowExp)
			{
				exp64 = LowExp;
				ExpLower = TRUE;
			}
			SetExp64(&lpCurPlayer->sCharacterData, exp64);
			ep = ep - exp64;
			SetTotalSubExp((int)ep);
		}

		if (Penalty)
			Money = lpChar->sCharacterData.iGold / Penalty;
		else
			Money = 0;

		lpChar->sCharacterData.iGold -= Money;
		if (lpChar->sCharacterData.iGold < 0)
		{
			Money = -Money;
			lpChar->sCharacterData.iGold = 0;
		}
		SetTotalSubMoney(Money);

		ReformCharForm();
		ResetInvenMoney();
		return TRUE;
	}

	return FALSE;
}

//鞘靛俊辑 犁矫累 某腐磐 版氰摹 眠啊 憋烙
int ContGameExp(Unit *lpChar)
{
	int Level;
	INT64 LowExp;
	INT64 HighExp;
	INT64 exp;
	INT64 ep;
	INT64 exp64;
	int Money;

	Level = lpChar->sCharacterData.iLevel;
	if (Level >= 11)
	{
		LowExp = uUnitExpTables[Level - 1];
		HighExp = uUnitExpTables[Level];
		exp = (HighExp - LowExp) / 100;

		exp64 = GAMEUNIT->GetExp(lpCurPlayer);

		if (exp64 > LowExp)
		{
			ep = exp64;
			exp64 -= exp;
			if (exp64 < LowExp)
				exp64 = LowExp;

			SetExp64(&lpCurPlayer->sCharacterData, exp64);

			ep = ep - exp64;
			SetTotalSubExp((int)ep);
		}

		Money = lpChar->sCharacterData.iGold / 100;
		lpChar->sCharacterData.iGold -= Money;
		if (lpChar->sCharacterData.iGold < 0)
		{
			Money = -Money;
			lpChar->sCharacterData.iGold = 0;
		}

		SetTotalSubMoney(Money);

		ReformCharForm();
		ResetInvenMoney();
	}

	return TRUE;
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
	weight = lpDefenceCharInfo->sWeight.sMax;
	weight = lpDefenceCharInfo->sWeight.sMin;
	defence = (int)(((((ar / (ar + (def / 2))) - ((dLv - aLv) / 50))) * 100)) - (weight / 10000);

	if (defence > 95)
		defence = 95;

	return defence;
}
int RainMaterial[4][8];

int InitWeatherSystem()
{
	RainMaterial[0][0] = CreateTextureMaterial("rain\\ll.bmp", 0, TRUE, FALSE, SMMAT_BLEND_ADDCOLOR);

	RainMaterial[1][0] = CreateTextureMaterial("rain\\45rain01.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);
	RainMaterial[1][1] = CreateTextureMaterial("rain\\45rain02.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);
	RainMaterial[1][2] = CreateTextureMaterial("rain\\45rain03.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);
	RainMaterial[1][3] = CreateTextureMaterial("rain\\45rain04.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);
	RainMaterial[1][4] = CreateTextureMaterial("rain\\45rain05.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);
	RainMaterial[1][5] = CreateTextureMaterial("rain\\45rain06.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);

	RainMaterial[2][0] = CreateTextureMaterial("rain\\80rain01.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);
	RainMaterial[2][1] = CreateTextureMaterial("rain\\80rain02.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);
	RainMaterial[2][2] = CreateTextureMaterial("rain\\80rain03.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);
	RainMaterial[2][3] = CreateTextureMaterial("rain\\80rain04.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);
	RainMaterial[2][4] = CreateTextureMaterial("rain\\80rain05.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);
	RainMaterial[2][5] = CreateTextureMaterial("rain\\80rain06.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);

	RainMaterial[3][0] = CreateTextureMaterial("rain\\90rain01.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);
	RainMaterial[3][1] = CreateTextureMaterial("rain\\90rain02.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);
	RainMaterial[3][2] = CreateTextureMaterial("rain\\90rain03.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);
	RainMaterial[3][3] = CreateTextureMaterial("rain\\90rain04.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);
	RainMaterial[3][4] = CreateTextureMaterial("rain\\90rain05.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);
	RainMaterial[3][5] = CreateTextureMaterial("rain\\90rain06.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);

	return TRUE;
}
extern int WeatherMode;

int DrawWeather(int ax)
{
	smFACE2D face2d;

	int tm;
	float fx;
	int RainMode;

	if (ax < ANGLE_45 - 256)
		RainMode = 0;
	else
	{
		if (ax > ANGLE_45 + 256)
			RainMode = 3;
		else
		{
			if (ax > ANGLE_45)
				RainMode = 2;
			else
				RainMode = 1;
		}
	}

	if (WeatherMode == 2)
	{
		if (lpCurPlayer->iLoadedMapIndex >= 0 &&
			(STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapType == MAPTYPE_Dungeon ||
				STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapType == MAPTYPE_ChessRoom ||
				STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapType == MAPTYPE_Ice ||
				STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapType == MAPTYPE_Distorted))
			return TRUE;

		smRender.Init();

		switch (RainMode)
		{
		case 0:
			tm = timeGetTime();
			tm = (tm >> 2) & 0x3FF;
			fx = ((float)tm) / 256;
			tm = timeGetTime();
			tm = (tm) & 0x3FF;
			fx = ((float)tm) / 256;

			face2d.TexRect.left = fx;
			face2d.TexRect.right = fx + 3;
			face2d.TexRect.top = fx;
			face2d.TexRect.bottom = fx + 0.5f;
			face2d.width = RESOLUTION_WIDTH;
			face2d.height = RESOLUTION_HEIGHT;
			face2d.Transparency = 255;
			face2d.r = 255;
			face2d.g = 255;
			face2d.b = 255;
			face2d.x = 0;
			face2d.z = 0;
			face2d.y = 0;
			face2d.MatNum = RainMaterial[RainMode][0];
			smRender.AddFace2D_Direct(&face2d);
			break;
		case 1:
			tm = timeGetTime() >> 6;

			face2d.TexRect.left = 1;
			face2d.TexRect.right = 0;
			face2d.TexRect.top = 0;
			face2d.TexRect.bottom = 1;
			face2d.width = (int)RESOLUTION_WIDTH / 2;
			face2d.height = RESOLUTION_HEIGHT;
			face2d.Transparency = 160;
			face2d.r = 255;
			face2d.g = 255;
			face2d.b = 255;
			face2d.x = 0;
			face2d.z = 0;
			face2d.y = 0;
			face2d.MatNum = RainMaterial[RainMode][tm % 6];
			smRender.AddFace2D_Direct(&face2d);

			face2d.TexRect.left = 0;
			face2d.TexRect.right = 1;
			face2d.TexRect.top = 0;
			face2d.TexRect.bottom = 1;
			face2d.width = (int)RESOLUTION_WIDTH / 2;
			face2d.height = RESOLUTION_HEIGHT;
			face2d.Transparency = 160;
			face2d.r = 255;
			face2d.g = 255;
			face2d.b = 255;
			face2d.x = (int)RESOLUTION_WIDTH / 2;
			face2d.z = 0;
			face2d.y = 0;
			face2d.MatNum = RainMaterial[RainMode][(tm + 3) % 6];
			smRender.AddFace2D_Direct(&face2d);
			break;
		case 2:
			tm = timeGetTime() >> 6;

			face2d.TexRect.left = 1;
			face2d.TexRect.right = 0;
			face2d.TexRect.top = 0;
			face2d.TexRect.bottom = 1;
			face2d.width = (int)RESOLUTION_WIDTH / 2;
			face2d.height = RESOLUTION_HEIGHT;
			face2d.Transparency = 128;
			face2d.r = 255;
			face2d.g = 255;
			face2d.b = 255;
			face2d.x = 0;
			face2d.z = 0;
			face2d.y = 0;
			face2d.MatNum = RainMaterial[RainMode][tm % 6];
			smRender.AddFace2D_Direct(&face2d);

			face2d.TexRect.left = 0;
			face2d.TexRect.right = 1;
			face2d.TexRect.top = 0;
			face2d.TexRect.bottom = 1;
			face2d.width = (int)RESOLUTION_WIDTH / 2;
			face2d.height = RESOLUTION_HEIGHT;
			face2d.Transparency = 128;
			face2d.r = 255;
			face2d.g = 255;
			face2d.b = 255;
			face2d.x = (int)RESOLUTION_WIDTH / 2;
			face2d.z = 0;
			face2d.y = 0;
			face2d.MatNum = RainMaterial[RainMode][(tm + 3) % 6];
			smRender.AddFace2D_Direct(&face2d);
			break;
		case 3:
			tm = timeGetTime() >> 6;

			face2d.TexRect.left = 0;
			face2d.TexRect.right = 1;
			face2d.TexRect.top = 0;
			face2d.TexRect.bottom = 1;
			face2d.width = (int)RESOLUTION_WIDTH / 2;
			face2d.height = (int)RESOLUTION_HEIGHT / 2;
			face2d.Transparency = 128;
			face2d.r = 255;
			face2d.g = 255;
			face2d.b = 255;
			face2d.x = 0;
			face2d.z = 0;
			face2d.y = 0;
			face2d.MatNum = RainMaterial[RainMode][tm % 6];
			smRender.AddFace2D_Direct(&face2d);

			face2d.TexRect.left = 1;
			face2d.TexRect.right = 0;
			face2d.TexRect.top = 0;
			face2d.TexRect.bottom = 1;
			face2d.width = (int)RESOLUTION_WIDTH / 2;
			face2d.height = (int)RESOLUTION_HEIGHT / 2;
			face2d.Transparency = 128;
			face2d.r = 255;
			face2d.g = 255;
			face2d.b = 255;
			face2d.x = (int)RESOLUTION_WIDTH / 2;
			face2d.z = 0;
			face2d.y = 0;
			face2d.MatNum = RainMaterial[RainMode][(tm + 3) % 6];
			smRender.AddFace2D_Direct(&face2d);

			face2d.TexRect.left = 0;
			face2d.TexRect.right = 1;
			face2d.TexRect.top = 1;
			face2d.TexRect.bottom = 0;
			face2d.width = (int)RESOLUTION_WIDTH / 2;
			face2d.height = (int)RESOLUTION_HEIGHT / 2;
			face2d.Transparency = 128;
			face2d.r = 255;
			face2d.g = 255;
			face2d.b = 255;
			face2d.x = 0;
			face2d.z = 0;
			face2d.y = (int)RESOLUTION_HEIGHT >> 1;
			face2d.MatNum = RainMaterial[RainMode][(tm + 1) % 6];
			smRender.AddFace2D_Direct(&face2d);

			face2d.TexRect.left = 1;
			face2d.TexRect.right = 0;
			face2d.TexRect.top = 1;
			face2d.TexRect.bottom = 0;
			face2d.width = (int)RESOLUTION_WIDTH / 2;
			face2d.height = (int)RESOLUTION_HEIGHT / 2;
			face2d.Transparency = 128;
			face2d.r = 255;
			face2d.g = 255;
			face2d.b = 255;
			face2d.x = (int)RESOLUTION_WIDTH / 2;
			face2d.z = 0;
			face2d.y = (int)RESOLUTION_HEIGHT >> 1;
			face2d.MatNum = RainMaterial[RainMode][(tm + 4) % 6];
			smRender.AddFace2D_Direct(&face2d);
		}
		smRender.SetClipStates(0);
		smRender.ClipRendFace();
		smRender.RenderD3D();
	}

	return TRUE;
}

HANDLE	hLoadingThread = 0;
HBITMAP hBitmapLoadImage[2] = { 0 };
HDC	hdcBitmapLoadImage = NULL;

int DispLoading = FALSE;

DWORD dwLampThreadId;

int DispCnt = 1;

//LOADIN显示
DWORD WINAPI DispLoadingThreadProc(void *pInfo)
{
	HANDLE	hThread;
	HDC	hdc;
	int Counter = 0;

	DispLoading = 0;
	hThread = GetCurrentThread();

	while (!quit)
	{
		if (!DispLoading)
			SuspendThread(hThread);

		EnterCriticalSection(&cDrawSection);

		hdc = GetDC(hwnd);

		int w = 173;
		int h = 37;

		int x = ((int)RESOLUTION_WIDTH >> 1) - (w >> 1);
		int y = RESOLUTION_HEIGHT - 80;

		SelectObject(hdcBitmapLoadImage, hBitmapLoadImage[0]);
		TransparentBlt(hdc, x, y, w, h, hdcBitmapLoadImage, 0, 0, w, h, RGB(0, 0, 0));

		if (LoadingCount > 0 && LoadingCnt > 0)
		{
			int sw = (w >> 1) * LoadingCnt / LoadingCount;

			sw = DispCnt * sw;

			SelectObject(hdcBitmapLoadImage, hBitmapLoadImage[1]);
			TransparentBlt(hdc, x, y, sw, h, hdcBitmapLoadImage, 0, 0, sw, h, RGB(0, 0, 0));
		}

		ReleaseDC(hwnd, hdc);

		LeaveCriticalSection(&cDrawSection);

		Counter++;
		Sleep(10);
	}

	ExitThread(TRUE);
	return TRUE;
}
//初始化加载图片
int InitLoadingLamp(HWND hWnd)
{
	HDC hdc;

	hdc = GetDC(hWnd);

	hBitmapLoadImage[0] = (HBITMAP)LoadImage(NULL, "image\\loadingbar.bmp", IMAGE_BITMAP, 173, 37, LR_LOADFROMFILE);
	hBitmapLoadImage[1] = (HBITMAP)LoadImage(NULL, "image\\loadingbar_.bmp", IMAGE_BITMAP, 173, 37, LR_LOADFROMFILE);

	hdcBitmapLoadImage = CreateCompatibleDC(hdc);
	ReleaseDC(hWnd, hdc);

	hLoadingThread = CreateThread(NULL, 0, DispLoadingThreadProc, 0, 0, &dwLampThreadId);

	return TRUE;
}

//关闭加载图片
int CloseLoadingLamp()
{
	if (hBitmapLoadImage[0])
	{
		DeleteObject(hBitmapLoadImage[0]);
		hBitmapLoadImage[0] = NULL;
	}
	if (hBitmapLoadImage[1])
	{
		DeleteObject(hBitmapLoadImage[1]);
		hBitmapLoadImage[1] = NULL;
	}
	if (hdcBitmapLoadImage)
	{
		DeleteDC(hdcBitmapLoadImage);
		hdcBitmapLoadImage = NULL;
	}

	return TRUE;
}

//打开显示loading
int OpenDispLoading()
{
	if (hLoadingThread)
	{
		DispLoading = TRUE;
		ResumeThread(hLoadingThread);
	}

	return TRUE;
}
//关闭显示loading
int CloseDispLoading()
{
	DispLoading = FALSE;
	DispCnt++;
	if (DispCnt >= 3)
		DispCnt = 1;

	return TRUE;
}

#define DYN_REMOVER_MAX		64
#define DYN_REMOVER_MASK	(DYN_REMOVER_MAX-1)

smDPAT *DynRemoveList[DYN_REMOVER_MAX];
int DynRemoveCnt = 0;
int DynRemovePush = 0;

HANDLE	hRemoverThread = 0;

DWORD WINAPI RemoveDynaPatternThreadProc(void *pInfo)
{
	HANDLE	hThread;
	int Counter = 0;
	int RemoveCnt;

	hThread = GetCurrentThread();

	while (!quit)
	{
		if ((DynRemovePush - DynRemoveCnt) > 32)
		{
			EnterCriticalSection(&cLoadSection);
			EnterCriticalSection(&cDrawSection);

			while (1)
			{
				RemoveCnt = DynRemoveCnt & DYN_REMOVER_MASK;
				smDPAT_Delete(DynRemoveList[RemoveCnt]);
				DynRemoveCnt++;
				if (DynRemovePush <= DynRemoveCnt)
					break;
			}
			LeaveCriticalSection(&cDrawSection);
			LeaveCriticalSection(&cLoadSection);
		}
		else
			SuspendThread(hThread);

		Counter++;
	}

	ExitThread(TRUE);
	return TRUE;
}

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
	DynRemoveList[DynRemovePush&DYN_REMOVER_MASK] = lpDinaPattern;
	DynRemovePush++;
	RemoveDynPatSub();

	return DynRemovePush;
}

struct	sCOMPACT_MAP
{
	smTEXTUREHANDLE	*hTexHandle;
	smTEXTUREHANDLE	*hTexTitleHandle;
	RECT	StageRect;
	BaseMap	*lpField;
	int		rx, ry;
};

sCOMPACT_MAP sCompactMap[4];

int MatArrow;
int MatMapBox;
int	MatPlayPos[5];
int	MatNpcPos;

//初始化小地图
int InitFieldMap()
{
	ZeroMemory(sCompactMap, sizeof(sCOMPACT_MAP) * 4);
	MatArrow = CreateTextureMaterial("Image\\ARROW.tga", 0, 0, FALSE, SMMAT_BLEND_ALPHA);
	MatMapBox = CreateTextureMaterial("Image\\MapBox.tga", 0, 0, FALSE, SMMAT_BLEND_ALPHA);
	MatPlayPos[0] = CreateTextureMaterial("Image\\ZoomField\\green.png", 0, 0, FALSE, SMMAT_BLEND_ALPHA);
	MatPlayPos[1] = CreateTextureMaterial("Image\\ZoomField\\red.png", 0, 0, FALSE, SMMAT_BLEND_ALPHA);
	MatPlayPos[2] = CreateTextureMaterial("Image\\ZoomField\\white.png", 0, 0, FALSE, SMMAT_BLEND_ALPHA);
	MatPlayPos[3] = CreateTextureMaterial("Image\\ZoomField\\yellow.png", 0, 0, FALSE, SMMAT_BLEND_ALPHA);
	MatPlayPos[4] = CreateTextureMaterial("Image\\ZoomField\\boss.png", 0, 0, FALSE, SMMAT_BLEND_ALPHA);
	MatNpcPos = CreateTextureMaterial("Image\\npc.tga", 0, 0, FALSE, SMMAT_BLEND_ALPHA);

	return TRUE;
}
// 加载地图
int LoadFieldMap(int PosNum, BaseMap *lpField, smSTAGE3D *lpStage)
{
	int ReadTexFlag = 0;

	if (!lpField || !lpStage || sCompactMap[PosNum].lpField == lpField)
		return TRUE;

	sCompactMap[PosNum].lpField = lpField;

	memcpy(&sCompactMap[PosNum].StageRect, &lpStage->StageMapRect, sizeof(RECT));

	if (sCompactMap[PosNum].hTexHandle)
	{
		smTexture.Delete(sCompactMap[PosNum].hTexHandle);
		sCompactMap[PosNum].hTexHandle = 0;
	}
	if (sCompactMap[PosNum].hTexTitleHandle)
	{
		smTexture.Delete(sCompactMap[PosNum].hTexTitleHandle);
		sCompactMap[PosNum].hTexTitleHandle = 0;
	}
	if (lpField->szMiniMapFilePath[0])
	{
		sCompactMap[PosNum].hTexHandle = smTexture.Add(lpField->szMiniMapFilePath, 0);

		sCompactMap[PosNum].rx = (lpStage->StageMapRect.right - lpStage->StageMapRect.left) >> FLOATNS;
		sCompactMap[PosNum].ry = (lpStage->StageMapRect.bottom - lpStage->StageMapRect.top) >> FLOATNS;

		ReadTexFlag = TRUE;
	}
	else
	{
		sCompactMap[PosNum].hTexHandle = 0;
		return FALSE;
	}

	if (lpField->szMiniMapNameFilePath[0])
	{
		sCompactMap[PosNum].hTexTitleHandle = smTexture.Add(lpField->szMiniMapNameFilePath, 0);

		ReadTexFlag = TRUE;
	}
	else
	{
		sCompactMap[PosNum].hTexTitleHandle = 0;
		return FALSE;
	}

	if (ReadTexFlag)
		ReadTextures();

	return TRUE;
}
int psDrawTexImage(smTEXTUREHANDLE *hTexHandle, float x, float y, float w, float h, float fx, float fy, float fw, float fh, int Transp, int specular);
int psDrawTexImage_Point(smTEXTUREHANDLE *hTexHandle, float x, float y, float w, float h, float fx, float fy, float fw, float fh, int Transp, int specular);
int psDrawTexImage2(smTEXTUREHANDLE *hTexHandle, float *x, float *y, float fx, float fy, float fw, float fh, int Transp, int specular);
int DrawMapArrow(int x, int y, int Angle);
int DrawFieldMap(sCOMPACT_MAP *lpCompactMap, int px, int py, int size);

int FieldMapDrawMode = 2;

int FieldMapDrawSize[3] = { 8 , 16 , 24 };
int FieldMapViewSize1 = 18 * 64 * fONE;
int FieldMapViewSize2 = 8 * 64 * fONE;


int MainFieldMap()
{
	if (FieldMapViewSize1 > FieldMapViewSize2)
	{
		FieldMapViewSize2 += 2048;
		if (FieldMapViewSize1 < FieldMapViewSize2)
			FieldMapViewSize2 = FieldMapViewSize1;
	}

	if (FieldMapViewSize1 < FieldMapViewSize2)
	{
		FieldMapViewSize2 -= 2048;
		if (FieldMapViewSize1 > FieldMapViewSize2)
			FieldMapViewSize2 = FieldMapViewSize1;
	}

	return TRUE;
}

extern int MatEachBox;
int	DrawMapPartyPlayer(int px, int py);
int	DrawMapNPC(int px, int py);

int	GetFieldMapCursor()
{
	int px = 656 + (RESOLUTION_WIDTH - 800);
	int py = 426 + (RESOLUTION_HEIGHT - 600);

	if ((int)RESOLUTION_WIDTH <= 800 && cSkill.OpenFlag)
		return FALSE;

	if (pCursorPos.x > px && pCursorPos.x<px + 128 && pCursorPos.y>py && pCursorPos.y < py + 128 && lpCurPlayer->dwTradeMsgCode == 0)
	{
		if (lpCurPlayer->iLoadedMapIndex >= 0 && (STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == rsSOD_FIELD ||
			STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == QUEST_ARENA_FIELD))
			return FALSE;
		return TRUE;
	}
	return FALSE;
}
//渲染小地图
int DrawFieldMap()
{
	int px = 656 + (RESOLUTION_WIDTH - 800);
	int py = 426 + (RESOLUTION_HEIGHT - 600);
	int sz;
	int flCode;
	int	dSpe;

	if (lpCurPlayer->dwTradeMsgCode)
		return FALSE;

	if (lpCurPlayer->iLoadedMapIndex >= 0 &&
		(STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == rsSOD_FIELD ||
			STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == QUEST_ARENA_FIELD ||
			STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapType == MAPTYPE_Distorted) ||
		STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == 36)
		return FALSE;

	if (lpCurPlayer->iLoadedMapIndex >= 0 &&
		STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapType == MAPTYPE_Dungeon)
		FieldMapDrawMode = 1;
	else
		FieldMapDrawMode = 2;

	FieldMapViewSize1 = FieldMapDrawSize[FieldMapDrawMode] * 64 * fONE;
	sz = FieldMapViewSize2;

	psSetRenderState(1);

	dsDrawColorBox(D3DCOLOR_RGBA(0, 0, 0, 128), px, py, 128, 128);

	DrawFieldMap(&sCompactMap[1], px + 1, py + 1, sz);
	DrawFieldMap(&sCompactMap[0], px + 1, py + 1, sz);

	DrawMapNPC(px + 64, py + 64);

	if (InterfaceParty.PartyMemberCount)
		DrawMapPartyPlayer(px + 64, py + 64);

	DrawMapArrow(px + 64, py + 64, lpCurPlayer->Angle.y);

	if (GetFieldMapCursor() == TRUE)
		dSpe = 96;
	else
		dSpe = 0;

	if (MatMapBox >= 0)
		dsDrawTexImage(MatMapBox, px, py, 128, 128, 255, dSpe);

	flCode = 0;
	if (lpCurPlayer->iLoadedMapIndex >= 0)
	{
		if (STAGE_MAP[lpCurPlayer->iLoadedMapIndex] == sCompactMap[0].lpField)
			flCode = 0;
		if (STAGE_MAP[lpCurPlayer->iLoadedMapIndex] == sCompactMap[1].lpField)
			flCode = 1;
	}

	if (sCompactMap[flCode].hTexTitleHandle)
		psDrawTexImage_Point(sCompactMap[flCode].hTexTitleHandle, (float)px, (float)py - 16, 128, 16, 0, 0, 1.0f, 1.0f, 255, dSpe >> 2);

	return TRUE;
}
int	DrawMapPartyPlayer(int px, int py)
{
	int cnt;
	int	x, y;
	int	size;
	float sz;
	float sx, sy;
	float fx, fy;
	int dist;

	size = FieldMapViewSize2;
	sz = (float)(FieldMapViewSize2 / 64);
	fx = (float)px;
	fy = (float)py;

	for (cnt = 0; cnt < InterfaceParty.PartyMemberCount; cnt++)
	{
		if (InterfaceParty.PartyMember[cnt].ChrCode != lpCurPlayer->iID)
		{
			x = InterfaceParty.PartyMember[cnt].CharacterPos.x - lpCurPlayer->pX;
			y = InterfaceParty.PartyMember[cnt].CharacterPos.z - lpCurPlayer->pZ;
			if (abs(x) < size && abs(y) < size)
			{
				sx = fx + (((float)x) / sz);
				sy = fy - (((float)y) / sz);

				x >>= FLOATNS;
				y >>= FLOATNS;
				dist = x * x + y * y;
				if (dist < PARTY_GETTING_DIST2)
					dsDrawTexImageFloat(MatPlayPos[0], sx - 3, sy - 3, 8, 8, 255, 0);
				else
					dsDrawTexImageFloat(MatPlayPos[2], sx - 3, sy - 3, 8, 8, 255, 0);
			}
		}
	}

	return TRUE;
}


int	DrawMapNPC(int px, int py)
{
	int cnt;
	int	x, y;
	int	size;
	float sz;
	float sx, sy;
	float fx, fy;
	int TransNum;

	size = FieldMapViewSize2;
	sz = (float)(FieldMapViewSize2 / 64);
	fx = (float)px;
	fy = (float)py;

	TransNum = 127;

	for (cnt = 0; cnt < MAX_UNITS; cnt++)
	{
		if (chrOtherPlayer[cnt].bActive && chrOtherPlayer[cnt].sCharacterData.iType == CHARACTERTYPE_NPC)
		{
			x = chrOtherPlayer[cnt].pX - lpCurPlayer->pX;
			y = chrOtherPlayer[cnt].pZ - lpCurPlayer->pZ;
			if (abs(x) < size && abs(y) < size)
			{
				sx = fx + (((float)x) / sz);
				sy = fy - (((float)y) / sz);
				dsDrawTexImageFloat(MatNpcPos, sx - 3, sy - 3, 8, 8, TransNum + 128, 0);
			}
		}
		if (chrOtherPlayer[cnt].bActive && chrOtherPlayer[cnt].psModelAnimation && chrOtherPlayer[cnt].sCharacterData.iMonsterType != MONSTERTYPE_Friendly && chrOtherPlayer[cnt].psModelAnimation->iType != ANIMATIONTYPE_Die)
		{
			x = chrOtherPlayer[cnt].pX - lpCurPlayer->pX;
			y = chrOtherPlayer[cnt].pZ - lpCurPlayer->pZ;
			if (abs(x) < size && abs(y) < size)
			{
				sx = fx + (((float)x) / sz);
				sy = fy - (((float)y) / sz);

				if (chrOtherPlayer[cnt].sCharacterData.iType == CHARACTERTYPE_Monster)
				{
					if (chrOtherPlayer[cnt].sCharacterData.sGlow == MONSTER_CLASS_BOSS)
						dsDrawTexImageFloat(MatPlayPos[4], sx - 3, sy - 3, 16, 16, 255, 0);
					else
						dsDrawTexImageFloat(MatPlayPos[1], sx - 3, sy - 3, 8, 8, 255, 0);
				}
				else if (chrOtherPlayer[cnt].sCharacterData.iType == CHARACTERTYPE_Player && chrOtherPlayer[cnt].iID != lpCurPlayer->iID)
				{
					if (chrOtherPlayer[cnt].sCharacterData.iClanID != 0 &&
						chrOtherPlayer[cnt].sCharacterData.iClanID == lpCurPlayer->sCharacterData.iClanID)
						dsDrawTexImageFloat(MatPlayPos[3], sx - 3, sy - 3, 8, 8, 255, 0);
					else
						dsDrawTexImageFloat(MatPlayPos[2], sx - 3, sy - 3, 8, 8, 255, 0);
				}
			}
		}
	}

	return TRUE;
}
int DrawMapArrow(int x, int y, int Angle)
{
	float fx[4], fy[4];
	int sinY, cosY;
	int dx[4], dy[4];
	int cnt;

	sinY = GetSin[Angle&ANGCLIP];
	cosY = GetCos[(Angle + ANGLE_180)&ANGCLIP];

	dx[0] = -8; dy[0] = -8;
	dx[1] = -8; dy[1] = 8;
	dx[2] = 8; dy[2] = -8;
	dx[3] = 8; dy[3] = 8;

	for (cnt = 0; cnt < 4; cnt++)
	{
		fx[cnt] = (float)((dy[cnt] * sinY + dx[cnt] * cosY) >> 8);
		fy[cnt] = (float)((dy[cnt] * cosY - dx[cnt] * sinY) >> 8);
		fx[cnt] /= 256;
		fy[cnt] /= 256;
		fx[cnt] += (float)x;
		fy[cnt] += (float)y;
	}
	if (smMaterial[MatArrow].smTexture[0])
		psDrawTexImage2(smMaterial[MatArrow].smTexture[0], fx, fy, 0, 0, 1, 1, 255, 0);

	return TRUE;
}
int DrawFieldMap(sCOMPACT_MAP *lpCompactMap, int px, int py, int size)
{
	int x, z;
	int w, h;
	int left, right, bottom, top;
	float fx, fy, fw, fh;

	float dx, dy, dw, dh;
	float sc;

	if (!lpCompactMap->lpField || !lpCompactMap->hTexHandle)
		return FALSE;

	w = lpCompactMap->rx;
	h = lpCompactMap->ry;
	x = (lpCurPlayer->pX - lpCompactMap->StageRect.left);
	z = (lpCompactMap->StageRect.bottom - lpCurPlayer->pZ);

	left = x - size;
	right = x + size;
	top = z - size;
	bottom = z + size;

	dx = (float)px;
	dy = (float)py;
	dw = 126;
	dh = 126;

	float fpx;
	float fpy;
	float fmx, fmy;

	fpx = ((float)((size >> FLOATNS))) / (float)w;
	fpy = ((float)((size >> FLOATNS))) / (float)h;

	fmx = ((float)(x >> FLOATNS)) / (float)w;
	fmy = ((float)(z >> FLOATNS)) / (float)h;

	fx = fmx - fpx;
	fw = fmx + fpx;

	fy = fmy - fpy;
	fh = fmy + fpy;

	if ((fx < 0 && fw < 0) || (fx > 1 && fw > 1))
		return FALSE;
	if ((fy < 0 && fh < 0) || (fy > 1 && fh > 1))
		return FALSE;

	if (fx < 0)
	{
		sc = (-fx * (64 / fpx));
		dx = dx + sc;
		dw = dw - sc;
		fx = 0;
	}
	if (fw > 1)
	{
		sc = ((fw - 1)*(64 / fpx));
		dw = dw - sc;
		fw = 1;
	}

	if (fy < 0)
	{
		sc = (-fy * (64 / fpy));
		dy = dy + sc;
		dh = dh - sc;
		fy = 0;
	}
	if (fh > 1)
	{
		sc = ((fh - 1)*(64 / fpy));
		dh = dh - sc;
		fh = 1;
	}

	psDrawTexImage(lpCompactMap->hTexHandle, dx, dy, dw, dh, fx, fy, fw, fh, 255, 0);

	return TRUE;
}
int psDrawTexImage(smTEXTUREHANDLE *hTexHandle, float x, float y, float w, float h, float fx, float fy, float fw, float fh, int Transp, int specular)
{
	D3DTLVERTEX9 tlVertex[4];
	int cnt;

	for (cnt = 0; cnt < 4; cnt++)
	{
		tlVertex[cnt].rhw = 1;
		tlVertex[cnt].color = D3DCOLOR_RGBA(255, 255, 255, Transp);
		tlVertex[cnt].specular = D3DCOLOR_RGBA(specular, specular, specular, 0);
		tlVertex[cnt].sz = 0;
	}

	tlVertex[0].sx = x;
	tlVertex[0].sy = y;
	tlVertex[0].tu = fx;
	tlVertex[0].tv = fy;

	tlVertex[1].sx = x;
	tlVertex[1].sy = y + h;
	tlVertex[1].tu = fx;
	tlVertex[1].tv = fh;

	tlVertex[2].sx = x + w;
	tlVertex[2].sy = y;
	tlVertex[2].tu = fw;
	tlVertex[2].tv = fy;

	tlVertex[3].sx = x + w;
	tlVertex[3].sy = y + h;
	tlVertex[3].tu = fw;
	tlVertex[3].tv = fh;

	psSetRenderState(1);
	psDraw2DImage(hTexHandle->m_pTexture, tlVertex);

	return TRUE;
}
int psDrawTexImage_Point(smTEXTUREHANDLE *hTexHandle, float x, float y, float w, float h, float fx, float fy, float fw, float fh, int Transp, int specular)
{
	D3DTLVERTEX9 tlVertex[4];
	int cnt;

	for (cnt = 0; cnt < 4; cnt++)
	{
		tlVertex[cnt].rhw = 1;
		tlVertex[cnt].color = D3DCOLOR_RGBA(255, 255, 255, Transp);
		tlVertex[cnt].specular = D3DCOLOR_RGBA(specular, specular, specular, 0);
		tlVertex[cnt].sz = 0;
	}

	tlVertex[0].sx = x;
	tlVertex[0].sy = y;
	tlVertex[0].tu = fx;
	tlVertex[0].tv = fy;

	tlVertex[1].sx = x;
	tlVertex[1].sy = y + h;
	tlVertex[1].tu = fx;
	tlVertex[1].tv = fh;

	tlVertex[2].sx = x + w;
	tlVertex[2].sy = y;
	tlVertex[2].tu = fw;
	tlVertex[2].tv = fy;

	tlVertex[3].sx = x + w;
	tlVertex[3].sy = y + h;
	tlVertex[3].tu = fw;
	tlVertex[3].tv = fh;

	psSetRenderState(0);
	psDraw2DImage(hTexHandle->m_pTexture, tlVertex);

	return TRUE;
}
int psDrawTexImage2(smTEXTUREHANDLE *hTexHandle, float *x, float *y, float fx, float fy, float fw, float fh, int Transp, int specular)
{
	D3DTLVERTEX9 tlVertex[4];
	int cnt;

	for (cnt = 0; cnt < 4; cnt++)
	{
		tlVertex[cnt].rhw = 1;
		tlVertex[cnt].color = D3DCOLOR_RGBA(255, 255, 255, Transp);
		tlVertex[cnt].specular = D3DCOLOR_RGBA(specular, specular, specular, 0);
		tlVertex[cnt].sz = 0;
	}

	tlVertex[0].sx = x[0];
	tlVertex[0].sy = y[0];
	tlVertex[0].tu = fx;
	tlVertex[0].tv = fy;

	tlVertex[1].sx = x[1];
	tlVertex[1].sy = y[1];
	tlVertex[1].tu = fx;
	tlVertex[1].tv = fh;

	tlVertex[2].sx = x[2];
	tlVertex[2].sy = y[2];
	tlVertex[2].tu = fw;
	tlVertex[2].tv = fy;

	tlVertex[3].sx = x[3];
	tlVertex[3].sy = y[3];
	tlVertex[3].tu = fw;
	tlVertex[3].tv = fh;

	psSetRenderState(0);
	psDraw2DImage(hTexHandle->m_pTexture, tlVertex);

	return TRUE;
}
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
	int cnt;
	int dist;
	int dx, dz;

	for (cnt = 0; cnt < MAX_UNITS; cnt++)
	{
		if (chrOtherPlayer[cnt].bActive && chrOtherPlayer[cnt].sCharacterData.sHP.sMin > 0 && (chrOtherPlayer[cnt].dwLastTransTime + DISPLAY_TRANS_TIME_OVER) > dwPlayTime)
		{
			if ((y - 16 * fONE) < chrOtherPlayer[cnt].pY && (y + 16 * fONE) > chrOtherPlayer[cnt].pY)
			{
				dx = (chrOtherPlayer[cnt].pX - x) >> FLOATNS;
				dz = (chrOtherPlayer[cnt].pZ - z) >> FLOATNS;
				dist = dx * dx + dz * dz;
				if (dist < (16 * 16))
					return &chrOtherPlayer[cnt];
			}
		}
	}

	return NULL;
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
	code += CompareStateCode((char *)&lpItemInfo1->sHPRecovery, (char *)&lpItemInfo2->sHPRecovery, sizeof(MinMax));

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
	ReformStateCode((char *)&lpItemInfo->bEnableEffect, sizeof(DWORD));
	ReformStateCode((char *)&lpItemInfo->ItemElement, sizeof(WORD));

	return iFormCode;
}

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
	code += CompareStateCode((char *)&lpItemInfo1->bEnableEffect, (char *)&lpItemInfo2->bEnableEffect, sizeof(DWORD));
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
	ReformStateCode((char *)lpCharInfo->iMinDamage, sizeof(int));
	ReformStateCode((char *)lpCharInfo->iMaxDamage, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->iAttackSpeed, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->iAttackRange, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->iCritical, sizeof(int));

	ReformStateCode((char *)&lpCharInfo->iDefenseRating, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->iBlockRating, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->iAbsorbRating, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->iMovementSpeed, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->iSight, sizeof(int));
	//ReformStateCode((char *)lpCharInfo->sWeight.sMax sizeof(short) * 2);

	ReformStateCode((char *)lpCharInfo->sElementalDef, sizeof(short) * 8);
	ReformStateCode((char *)lpCharInfo->sElementalAtk, sizeof(short) * 8);

	ReformStateCode((char *)&lpCharInfo->sHP, sizeof(CurMax));
	ReformStateCode((char *)&lpCharInfo->sMP, sizeof(CurMax));
	ReformStateCode((char *)&lpCharInfo->sSP, sizeof(CurMax));

	ReformStateCode((char *)&lpCharInfo->iExp, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->iOwnerID, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->iGold, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->iStatPoints, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->iExp, sizeof(int));

	return iFormCode;
}


static int ItemFormVersion = 12;
static int ItemFormKey = 0;


int ReformItem(Item *lpItemInfo)
{
	DWORD dwCode;

	if (!lpItemInfo->sItemID.ToInt() || lpItemInfo->sItemID.ToInt() == (sinGG1 | sin01) || (lpItemInfo->sItemID.ToItemBase()) == (sinPM1&sinITEM_MASK1))
	{
		lpItemInfo->iChk1 = ItemFormKey + GetCurrentTime();

		dwCode = GetRefromItemCode(lpItemInfo, lpItemInfo->iChk1);

		lpItemInfo->iChk2 = dwCode;
		lpItemInfo->dwVersion = ItemFormVersion;
	}

	ItemFormKey++;

	return TRUE;
}
int ReformItem_AdjustTime(Item *lpItemInfo, int TimeAdjust)
{

	ItemFormKey++;

	return TRUE;
}


int CheckItemForm(Item *lpItemInfo)
{
	DWORD dwCode;

	dwCode = GetRefromItemCode(lpItemInfo, lpItemInfo->iChk1);

	if (lpItemInfo->iChk2 == dwCode) return TRUE;

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

	lpCharInfo->RefomCode = dwCode;

	ItemFormKey++;

	return TRUE;
}
int CheckCharForm(CharacterData *lpCharInfo)
{
	DWORD dwCode;

	dwCode = GetRefromCharState(lpCharInfo, 10);

	if (lpCharInfo->RefomCode == dwCode)
		return TRUE;

	return FALSE;
}
int ReformCharForm()
{
	return ReformCharForm(&lpCurPlayer->sCharacterData);
}
int CheckCharForm()
{
	int val;

	val = CheckCharForm(&lpCurPlayer->sCharacterData);

	if (val == FALSE)
	{
		SendSetHackUser(81);

		GAMESOCKET->iDisconnectType = 4;
		GAMESOCKET->iDisconnectTime = TICKCOUNT;
	}

	return val;
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
	DWORD dwCode;

	dwCode = GetRefromTradeCode((sTRADE *)lpTrade, 84);

	if (((sTRADE *)lpTrade)->CheckMoney == (int)dwCode)
		return TRUE;

	SendSetHackUser2(4000, 0);

	return FALSE;
}
short GetMixItemForm(Item *lpItemInfo)
{
	short sCode = 0;


	return sCode;
}
int ReformMixItem(Item *lpItemInfo)
{

	return TRUE;
}
int CheckMixItem(Item *lpItemInfo)
{
	return TRUE;
}

float GetItemAbsorb(Item *lpItemInfo)
{
	return lpItemInfo->fAbsorbRating;
}



#define WAIT_BATTLE_QUIT_TIME		10000


int QuitGame()
{
	if (quit)
		return TRUE;

	if (dwBattleTime)
	{
		if ((dwBattleTime + WAIT_BATTLE_QUIT_TIME) > dwPlayTime)
		{
			dwBattleQuitTime = dwPlayTime;
			return FALSE;
		}
	}
	if (cWareHouse.OpenFlag || cCraftItem.OpenFlag || cTrade.OpenFlag || cAging.OpenFlag || SmeltingItem.OpenFlag || ManufactureItem.m_OpenFlag || cMixtureReset.OpenFlag || cElement.OpenFlag || cCaravan.OpenFlag || cSocket.OpenFlag)
	{
		dwCloseBoxTime = dwPlayTime + 2000;
		return FALSE;
	}
	quit = 1;

	return TRUE;
}

#define CHARINFO_CACHE_MAX		200

smTRNAS_PLAYERINFO	CharInfo_Cache[CHARINFO_CACHE_MAX];
DWORD	dwCharInfo_CacheCode[CHARINFO_CACHE_MAX];
int	CharInfoCacheCnt = 0;


smTRNAS_PLAYERINFO	*GetCharInfoCache(char *lpData)
{
	DWORD	dwChkCode;
	int cnt;
	PacketPlayDataMinor *lpPlayData;
	PacketPlayData	*lpTransPlayData;
	PlayBufferData	*lpTransPlayBuff;
	int	RecvCode;
	smTRNAS_PLAYERINFO	*lpTransPlayInfo;

	RecvCode = ((int *)lpData)[1];

	dwChkCode = 0;

	switch (RecvCode)
	{
	case smTRANSCODE_PLAYDATA1:
		lpPlayData = (PacketPlayDataMinor *)lpData;
		dwChkCode = lpPlayData->dwAutoCharCode;
		break;
	case smTRANSCODE_TRANSPLAYDATA:
		lpTransPlayData = (PacketPlayData *)lpData;
		lpTransPlayBuff = (PlayBufferData *)(lpData + sizeof(PacketPlayData));
		if (lpTransPlayData->iPlayBuffCount > 0)
			dwChkCode = lpTransPlayData->dwAutoCharCode;
		break;
	}

	if (!dwChkCode)
		return NULL;

	for (cnt = 0; cnt < CharInfoCacheCnt; cnt++)
	{
		if (dwChkCode == dwCharInfo_CacheCode[cnt])
		{
			lpTransPlayInfo = &CharInfo_Cache[cnt];

			switch (RecvCode)
			{
			case smTRANSCODE_PLAYDATA1:
				lpTransPlayInfo->x = lpPlayData->iX;
				lpTransPlayInfo->y = lpPlayData->iY;
				lpTransPlayInfo->z = lpPlayData->iZ;
				lpTransPlayInfo->ax = lpPlayData->iX;
				lpTransPlayInfo->ay = lpPlayData->iY;
				lpTransPlayInfo->az = lpPlayData->iZ;
				lpTransPlayInfo->dwObjectSerial = lpPlayData->dwObjectID;
				lpTransPlayInfo->sCharacterData.dwObjectSerial = lpPlayData->dwObjectID;
				break;
			case smTRANSCODE_TRANSPLAYDATA:
				lpTransPlayBuff = (PlayBufferData *)(((char *)lpTransPlayData) + sizeof(PacketPlayData));
				lpTransPlayBuff += lpTransPlayData->iPlayBuffCount - 1;

				lpTransPlayInfo->x = lpTransPlayBuff->sPlayBuff.iX;
				lpTransPlayInfo->y = lpTransPlayBuff->sPlayBuff.iY;
				lpTransPlayInfo->z = lpTransPlayBuff->sPlayBuff.iZ;

				lpTransPlayInfo->ax = lpTransPlayBuff->sPlayBuff.saAngle[0];
				lpTransPlayInfo->ay = lpTransPlayBuff->sPlayBuff.saAngle[1];
				lpTransPlayInfo->az = lpTransPlayBuff->sPlayBuff.saAngle[2];
				lpTransPlayInfo->dwObjectSerial = lpTransPlayData->dwObjectID;
				lpTransPlayInfo->sCharacterData.dwObjectSerial = lpTransPlayData->dwObjectID;
				break;
			}

			lpTransPlayInfo->sCharacterData.sHP.sMin = lpTransPlayInfo->sCharacterData.sHP.sMax;
			return lpTransPlayInfo;
		}
	}

	return NULL;
}
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


int OpenPartyPlayer(char *szName, char *szModelFile1, char *szModelFile2)
{
	AddLoaderPattern(&chrPartyPlayer, szModelFile1, szModelFile2);

	chrPartyPlayer.SetMotionFromCode(ANIMATIONTYPE_Idle);
	chrPartyPlayer.ActionPattern = 101;
	chrPartyPlayer.bActive = TRUE;
	chrPartyPlayer.lpStage = 0;
	chrPartyPlayer.iLoadedMapIndex = lpCurPlayer->iLoadedMapIndex;

	lstrcpy(chrPartyPlayer.sCharacterData.szName, szName);

	OpenEachPlayer(&chrPartyPlayer);

	return TRUE;
}

char	szLastWhisperName[32] = { 0 };
int		LastWhisperLen = 0;

int	WhisperPartyPlayer(char *szName)
{
	char szBuff[128];
	int len;

	lstrcpy(szLastWhisperName, szName);

	chatlistSPEAKERflagChg(FALSE);
	hFocusWnd = hTextWnd;
	wsprintf(szBuff, "/:%s ", szName);
	len = lstrlen(szBuff);
	LastWhisperLen = len;
	SetWindowText(hFocusWnd, szBuff);
	SendMessage(hFocusWnd, EM_SETSEL, len, len);

	SetIME_Mode(TRUE);

	return TRUE;
}

int	SetClanChatting()
{
	char szBuff[128];
	int len;

	szLastWhisperName[0] = 0;
	hFocusWnd = hTextWnd;
	wsprintf(szBuff, "/CLAN> ");
	len = lstrlen(szBuff);
	LastWhisperLen = len;
	SetWindowText(hFocusWnd, szBuff);
	SendMessage(hFocusWnd, EM_SETSEL, len, len);

	SetIME_Mode(TRUE);

	return TRUE;
}
int IsClanChatting()
{
	if (lpCurPlayer->sCharacterData.iClanID)
	{
		if (!chatlistSPEAKERflag())
		{
			chatlistSPEAKERflagChg(TRUE);
			SetClanChatting();
			return TRUE;
		}
		else
		{
			chatlistSPEAKERflagChg(FALSE);
			SetWindowText(hFocusWnd, "");
			return TRUE;
		}
		szLastWhisperName[0] = 0;
	}

	return FALSE;
}


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

int SetJobFace(char *szModelName)
{
	lstrcpy(lpCurPlayer->sCharacterData.Player.szHeadModel, szModelName);
	AddLoaderPattern(lpCurPlayer, lpCurPlayer->sCharacterData.Player.szBodyModel, lpCurPlayer->sCharacterData.Player.szHeadModel);
	lpCurPlayer->sCharacterData.bUpdateInfo[0]++;
	ReformCharForm();	//某腐磐 沥焊 牢刘 罐扁

	SendSetObjectSerial(lpCurPlayer->iID);

	return TRUE;
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
//专职
int ChangeJobFace()
{
	int cnt1;

	cnt1 = 0;

	StartSkill(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, SKILL_UP1);
	SkillPlaySound(SKILL_SOUND_LEARN, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);

	CheckCharForm();

	ChangeModelSkin(lpCurPlayer, 0, lpCurPlayer->sCharacterData.iRank, 0, 0);
	lpCurPlayer->sCharacterData.bUpdateInfo[0]++;
	ReformCharForm();
	SendSetObjectSerial(lpCurPlayer->iID);

	return FALSE;
}

#define	TIME_EFFECT_BUFF_MAX	16

struct sTIME_EFFECT_BUFF
{
	DWORD	dwCode;
	DWORD	dwTime;
	int		x, y, z;
	Unit	*lpChar;
};

sTIME_EFFECT_BUFF TimeEffectBuff[TIME_EFFECT_BUFF_MAX];


int InitTimeEffect()
{
	int cnt;
	for (cnt = 0; cnt < TIME_EFFECT_BUFF_MAX; cnt++)
		TimeEffectBuff[cnt].dwCode = 0;
	return TRUE;
}

//增加时间效果
int AddTimeEffect(DWORD EffectCode, DWORD dwTime, int x, int y, int z, Unit *lpChar)
{
	int cnt;
	for (cnt = 0; cnt < TIME_EFFECT_BUFF_MAX; cnt++)
	{
		if (!TimeEffectBuff[cnt].dwCode)
		{
			TimeEffectBuff[cnt].dwCode = EffectCode;
			TimeEffectBuff[cnt].dwTime = dwTime;
			TimeEffectBuff[cnt].x = x;
			TimeEffectBuff[cnt].y = y;
			TimeEffectBuff[cnt].z = z;
			TimeEffectBuff[cnt].lpChar = lpChar;
			return TRUE;
		}
	}
	return FALSE;
}

int AddTimeEffect(DWORD EffectCode, DWORD dwTime, int x, int y, int z)
{
	return AddTimeEffect(EffectCode, dwTime, x, y, z, 0);
}
int TimeEffectMain()
{
	int cnt;
	for (cnt = 0; cnt < TIME_EFFECT_BUFF_MAX; cnt++)
	{
		if (TimeEffectBuff[cnt].dwCode && TimeEffectBuff[cnt].dwTime < dwPlayTime)
		{

			switch (TimeEffectBuff[cnt].dwCode)
			{
			case SKILL_RAGE_OF_ZECRAM_HIT2:
				StartSkill(TimeEffectBuff[cnt].x, TimeEffectBuff[cnt].y, TimeEffectBuff[cnt].z, 0, 0, 0, SKILL_RAGE_OF_ZECRAM_HIT2);
				SkillPlaySound(SKILL_SOUND_SKILL_RAGE_OF_ZECRAM2, TimeEffectBuff[cnt].x, TimeEffectBuff[cnt].y, TimeEffectBuff[cnt].z);
				SetDynLight(TimeEffectBuff[cnt].x, TimeEffectBuff[cnt].y, TimeEffectBuff[cnt].z, 100, 0, 0, 0, 500);
				break;
			case smTRANSCODE_SUCCESS_EVATION:
				cInterFace.SetStringEffect(HA_EVASION);
				break;
			case SKILL_EFFECT_FIREFLOWER:
				if (TimeEffectBuff[cnt].lpChar && TimeEffectBuff[cnt].lpChar->bActive)
				{
					ParkAssaParticle_FireCracker(TimeEffectBuff[cnt].lpChar, TimeEffectBuff[cnt].x);
					esPlaySound(23 + (rand() % 3), GetDistVolume(TimeEffectBuff[cnt].lpChar->pX, TimeEffectBuff[cnt].lpChar->pY, TimeEffectBuff[cnt].lpChar->pZ));
				}
				break;
			}

			TimeEffectBuff[cnt].dwCode = 0;
		}
	}
	return TRUE;
}

#define		ROT_PLAYER_MAX		128
#define		ROT_PLAYER_MIN		80

Unit	*lpChrPlayers[ROT_PLAYER_MAX];


Unit *InitRotPlayer()
{
	int cnt;
	for (cnt = 0; cnt < ROT_PLAYER_MAX; cnt++)
		lpChrPlayers[cnt] = NULL;

	return SelectRotPlayer(0);
}
int	CloseRotPlayer()
{
	int cnt;
	for (cnt = 0; cnt < ROT_PLAYER_MAX; cnt++)
		DELET(lpChrPlayers[cnt]);

	return TRUE;
}
Unit *SelectRotPlayer(Unit *lpCurrentChar)
{
	int rnd;
	Unit *lpChar;

	rnd = rand() % ROT_PLAYER_MIN;
	lpChar = lpChrPlayers[rnd];
	if (!lpChar)
	{
		lpChar = new Unit;
		lpChrPlayers[rnd] = lpChar;
	}

	if (!lpChar)
		return NULL;

	if (lpCurrentChar && lpCurrentChar != lpChar)
		memcpy(lpChar, lpCurrentChar, sizeof(Unit));

	if (!lpCurrentChar && lpChar)
		ZeroMemory(lpChar, sizeof(Unit));

	return lpChar;
}

int	PlaySub_EndFunc()
{
	return TRUE;
}

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

int	XorCheckPotion(sCHK_POTION_COUNT *ChkPotion)
{
	ChkPotion->Pl101 ^= tXorPotionCount;
	ChkPotion->Pl102 ^= tXorPotionCount;
	ChkPotion->Pl103 ^= tXorPotionCount;
	ChkPotion->Pl104 ^= tXorPotionCount;

	ChkPotion->Pm101 ^= tXorPotionCount;
	ChkPotion->Pm102 ^= tXorPotionCount;
	ChkPotion->Pm103 ^= tXorPotionCount;
	ChkPotion->Pm104 ^= tXorPotionCount;

	ChkPotion->Ps101 ^= tXorPotionCount;
	ChkPotion->Ps102 ^= tXorPotionCount;
	ChkPotion->Ps103 ^= tXorPotionCount;
	ChkPotion->Ps104 ^= tXorPotionCount;

	return TRUE;
}
int	ComparePotion()
{
	sCHK_POTION_COUNT ChkPotionCount;
	int	CompareError = 0;

	XorCheckPotion(&sPotionTotalCount);

	GetInvenPotionCount(&ChkPotionCount);

	if (ChkPotionCount.Pl101 > sPotionTotalCount.Pl101)
		CompareError++;
	if (ChkPotionCount.Pl102 > sPotionTotalCount.Pl102)
		CompareError++;
	if (ChkPotionCount.Pl103 > sPotionTotalCount.Pl103)
		CompareError++;
	if (ChkPotionCount.Pl104 > sPotionTotalCount.Pl104)
		CompareError++;

	if (ChkPotionCount.Pm101 > sPotionTotalCount.Pm101)
		CompareError++;
	if (ChkPotionCount.Pm102 > sPotionTotalCount.Pm102)
		CompareError++;
	if (ChkPotionCount.Pm103 > sPotionTotalCount.Pm103)
		CompareError++;
	if (ChkPotionCount.Pm104 > sPotionTotalCount.Pm104)
		CompareError++;

	if (ChkPotionCount.Ps101 > sPotionTotalCount.Ps101)
		CompareError++;
	if (ChkPotionCount.Ps102 > sPotionTotalCount.Ps102)
		CompareError++;
	if (ChkPotionCount.Ps103 > sPotionTotalCount.Ps103)
		CompareError++;
	if (ChkPotionCount.Ps104 > sPotionTotalCount.Ps104)
		CompareError++;

	int cnt1, cnt2;
	cnt1 = ChkPotionCount.Pl101 + ChkPotionCount.Pl102 + ChkPotionCount.Pl103 + ChkPotionCount.Pl104 + ChkPotionCount.Pm101 + ChkPotionCount.Pm102 + ChkPotionCount.Pm103 + ChkPotionCount.Pm104 + ChkPotionCount.Ps101 + ChkPotionCount.Ps102 + ChkPotionCount.Ps103 + ChkPotionCount.Ps104;

	cnt2 = sPotionTotalCount.Pl101 + sPotionTotalCount.Pl102 + sPotionTotalCount.Pl103 + sPotionTotalCount.Pl104 + sPotionTotalCount.Pm101 + sPotionTotalCount.Pm102 + sPotionTotalCount.Pm103 + sPotionTotalCount.Pm104 + sPotionTotalCount.Ps101 + sPotionTotalCount.Ps102 + sPotionTotalCount.Ps103 + sPotionTotalCount.Ps104;

	if (CompareError)
		SendSetHackUser3(1530, CompareError, cnt1 - cnt2);

	tXorPotionCount = dwPlayTime & 0xFFFFFFF;
	memcpy(&sPotionTotalCount, &ChkPotionCount, sizeof(sCHK_POTION_COUNT));
	XorCheckPotion(&sPotionTotalCount);

	return CompareError;
}
int	ResetPotion()
{
	GetInvenPotionCount(&sPotionTotalCount);
	tXorPotionCount = dwPlayTime & 0xFFFFFFF;
	XorCheckPotion(&sPotionTotalCount);

	return TRUE;
}
int	ResetPotion2()
{
	int cnt1, cnt2;
	sCHK_POTION_COUNT ChkPotionCount;

	XorCheckPotion(&sPotionTotalCount);
	GetInvenPotionCount(&ChkPotionCount);

	cnt1 = ChkPotionCount.Pl101 + ChkPotionCount.Pl102 + ChkPotionCount.Pl103 + ChkPotionCount.Pl104 +
		ChkPotionCount.Pm101 + ChkPotionCount.Pm102 + ChkPotionCount.Pm103 + ChkPotionCount.Pm104 +
		ChkPotionCount.Ps101 + ChkPotionCount.Ps102 + ChkPotionCount.Ps103 + ChkPotionCount.Ps104;

	cnt2 = sPotionTotalCount.Pl101 + sPotionTotalCount.Pl102 + sPotionTotalCount.Pl103 + sPotionTotalCount.Pl104 +
		sPotionTotalCount.Pm101 + sPotionTotalCount.Pm102 + sPotionTotalCount.Pm103 + sPotionTotalCount.Pm104 +
		sPotionTotalCount.Ps101 + sPotionTotalCount.Ps102 + sPotionTotalCount.Ps103 + sPotionTotalCount.Ps104;

	if (cnt1 > (cnt2 + TransRecvItem.sItem.iPotionCount))
		return TRUE;

	memcpy(&sPotionTotalCount, &ChkPotionCount, sizeof(sCHK_POTION_COUNT));
	tXorPotionCount = dwPlayTime & 0xFFFFFFF;
	XorCheckPotion(&sPotionTotalCount);

	return FALSE;
}
int	IncPotionCount(sCHK_POTION_COUNT *ChkPotion, Item *lpItem)
{
	int	PotionCount;

	PotionCount = lpItem->iPotionCount;

	if (!PotionCount) return FALSE;

	if (lpItem->sItemID.ToInt() == (sinPL1 | sin01))
		ChkPotion->Pl101 += PotionCount;
	if (lpItem->sItemID.ToInt() == (sinPL1 | sin02))
		ChkPotion->Pl102 += PotionCount;
	if (lpItem->sItemID.ToInt() == (sinPL1 | sin03))
		ChkPotion->Pl103 += PotionCount;
	if (lpItem->sItemID.ToInt() == (sinPL1 | sin04))
		ChkPotion->Pl104 += PotionCount;

	if (lpItem->sItemID.ToInt() == (sinPM1 | sin01))
		ChkPotion->Pm101 += PotionCount;
	if (lpItem->sItemID.ToInt() == (sinPM1 | sin02))
		ChkPotion->Pm102 += PotionCount;
	if (lpItem->sItemID.ToInt() == (sinPM1 | sin03))
		ChkPotion->Pm103 += PotionCount;
	if (lpItem->sItemID.ToInt() == (sinPM1 | sin04))
		ChkPotion->Pm104 += PotionCount;

	if (lpItem->sItemID.ToInt() == (sinPS1 | sin01))
		ChkPotion->Ps101 += PotionCount;
	if (lpItem->sItemID.ToInt() == (sinPS1 | sin02))
		ChkPotion->Ps102 += PotionCount;
	if (lpItem->sItemID.ToInt() == (sinPS1 | sin03))
		ChkPotion->Ps103 += PotionCount;
	if (lpItem->sItemID.ToInt() == (sinPS1 | sin04))
		ChkPotion->Ps104 += PotionCount;

	return TRUE;
}
int GetInvenPotionCount(sCHK_POTION_COUNT *ChkPotion)
{
	int cnt;

	ZeroMemory(ChkPotion, sizeof(sCHK_POTION_COUNT));

	for (cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if (cInvenTory.InvenItem[cnt].bValid)
			IncPotionCount(ChkPotion, &cInvenTory.InvenItem[cnt].sItem);
	}

	for (cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if (cInvenTory.InvenItemTemp[cnt].bValid)
			IncPotionCount(ChkPotion, &cInvenTory.InvenItemTemp[cnt].sItem);
	}

	if (cTrade.OpenFlag)
	{
		for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++)
		{
			if (sTrade.TradeItem[cnt].bValid)
				IncPotionCount(ChkPotion, &sTrade.TradeItem[cnt].sItem);
		}
	}

	if (MouseItem.bValid)
		IncPotionCount(ChkPotion, &MouseItem.sItem);

	return TRUE;
}

int	GetItemCheckCode(Item *lpItem)
{
	if (lpItem->sItemID.ToInt() < sinPM1 && lpItem->szItemName[0])
		return lpItem->iChk2;
	return 0;
}
DWORD GetInvenItemCode()
{
	int cnt;

	DWORD	dwCode;

	dwCode = 0;

	for (cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if (cInvenTory.InvenItem[cnt].bValid)
			dwCode += GetItemCheckCode(&cInvenTory.InvenItem[cnt].sItem);
	}
	for (cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if (cInvenTory.InvenItemTemp[cnt].bValid)
			dwCode += GetItemCheckCode(&cInvenTory.InvenItemTemp[cnt].sItem);
	}
	if (cTrade.OpenFlag)
	{
		for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++)
		{
			if (sTrade.TradeItem[cnt].bValid)
				dwCode += GetItemCheckCode(&sTrade.TradeItem[cnt].sItem);
		}
	}
	if (MouseItem.bValid)
		dwCode += GetItemCheckCode(&MouseItem.sItem);

	if (cWareHouse.OpenFlag)
	{
		for (cnt = 0; cnt < 100; cnt++)
		{
			if (cWareHouse.WareHouse.WareHouseItem[cnt].bValid)
				dwCode += GetItemCheckCode(&cWareHouse.WareHouse.WareHouseItem[cnt].sItem);
		}
	}

	if (cCraftItem.OpenFlag)
	{
		for (cnt = 0; cnt < 15; cnt++)
		{
			if (sCraftItem.CraftItem[cnt].bValid)
				dwCode += GetItemCheckCode(&sCraftItem.CraftItem[cnt].sItem);
		}
	}

	if (cAging.OpenFlag)
	{
		for (cnt = 0; cnt < 15; cnt++)
		{
			if (sAgingItem.AgingItem[cnt].bValid)
				dwCode += GetItemCheckCode(&sAgingItem.AgingItem[cnt].sItem);
		}
	}
	if (SmeltingItem.OpenFlag)
	{
		for (cnt = 0; cnt < 5; cnt++)
		{
			if (S_smeltingItem.SmeltingItem[cnt].bValid)
				dwCode += GetItemCheckCode(&S_smeltingItem.SmeltingItem[cnt].sItem);
		}
	}
	if (ManufactureItem.m_OpenFlag)
	{
		for (cnt = 0; cnt < 4; cnt++)
		{
			if (sManufactureItem.ManufactureItem[cnt].bValid)
				dwCode += GetItemCheckCode(&sManufactureItem.ManufactureItem[cnt].sItem);
		}
	}
	if (cMixtureReset.OpenFlag)
	{
		for (cnt = 0; cnt < 2; cnt++)
		{
			if (sMixtureResetItem.MixtureResetItem[cnt].bValid)
				dwCode += GetItemCheckCode(&sMixtureResetItem.MixtureResetItem[cnt].sItem);
		}
	}
	if (cElement.OpenFlag)
	{
		for (cnt = 0; cnt < 6; cnt++)
		{
			if (cElement.ElementItem[cnt].bValid)
				dwCode += GetItemCheckCode(&cElement.ElementItem[cnt].sItem);
		}
	}
	if (cSocket.OpenFlag)
	{
		for (cnt = 0; cnt < 5; cnt++)
		{
			if (cSocket.SocketItem[cnt].bValid)
				dwCode += GetItemCheckCode(&cSocket.SocketItem[cnt].sItem);
		}
	}
	if (cCaravan.OpenFlag)
	{
		for (cnt = 0; cnt < 100; cnt++)
		{
			if (cCaravan.sCaravan.Item[cnt].bValid)
				dwCode += GetItemCheckCode(&cCaravan.sCaravan.Item[cnt].sItem);
		}
	}

	return dwCode;
}


DWORD	dwTotal_InvenItemCode;
DWORD	dwTotal_InvenItemPlayTime;


int	ResetInvenItemCode()
{
	dwTotal_InvenItemCode = GetInvenItemCode();
	dwTotal_InvenItemCode = dwPlayTime ^ dwTotal_InvenItemCode;
	dwTotal_InvenItemPlayTime = dwPlayTime;

	return TRUE;
}
int SubInvenItemCode(Item *lpItem)
{
	DWORD	dwCode;

	dwCode = dwTotal_InvenItemCode ^ dwTotal_InvenItemPlayTime;
	dwTotal_InvenItemCode = dwCode - GetItemCheckCode(lpItem);

	dwTotal_InvenItemCode = dwPlayTime ^ dwTotal_InvenItemCode;
	dwTotal_InvenItemPlayTime = dwPlayTime;

	return TRUE;
}
int	CheckInvenItemCode()
{
	DWORD dwCode;
	smTRANS_COMMAND	smTransCommand;

	dwCode = GetInvenItemCode();

	if (dwCode != (dwTotal_InvenItemCode^dwTotal_InvenItemPlayTime)) {
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.code = smTRANSCODE_SET_BLACKLIST3;
		smTransCommand.WParam = 7010;
		smTransCommand.LParam = dwTotal_InvenItemCode ^ dwTotal_InvenItemPlayTime;
		smTransCommand.SParam = dwCode;

		SENDPACKETL(&smTransCommand);
	}

	dwTotal_InvenItemCode = dwPlayTime ^ dwCode;
	dwTotal_InvenItemPlayTime = dwPlayTime;

	return TRUE;
}


void CheckPlaySubFunc2()
{
	if (dwPlaySub_CheckResult != PLAYSUB_CHECKRESULT)
	{
		SendSetHackUser2(1120, dwPlaySub_CheckResult);
		GAMESOCKET->iDisconnectTime = TICKCOUNT;
	}
}

short	sChkLife[2];
short	sChkMana[2];
short	sChkStamina[2];
int		EnergyGraphErrorCount[4] = { 0,0,0,0 };


int CheckEnergyGraphError()
{
	int Life, Mana, Stamina;
	smTRANS_COMMAND	smTransCommand;

	Life = EnergyGraphErrorCount[0] - EnergyGraphErrorCount[3];
	Mana = EnergyGraphErrorCount[1] - EnergyGraphErrorCount[3];
	Stamina = EnergyGraphErrorCount[2] - EnergyGraphErrorCount[3];

	if (Life > 0 || Mana > 0 || Stamina > 0)
	{
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.code = smTRANSCODE_CLIENT_ERROR;
		smTransCommand.WParam = 0;

		smTransCommand.LParam = Life;
		smTransCommand.SParam = Mana;
		smTransCommand.EParam = Stamina;

		SENDPACKETL(&smTransCommand);
	}

	EnergyGraphErrorCount[3] = lpCurPlayer->pX;
	EnergyGraphErrorCount[0] = EnergyGraphErrorCount[3] + Life;
	EnergyGraphErrorCount[1] = EnergyGraphErrorCount[3] + Life;
	EnergyGraphErrorCount[2] = EnergyGraphErrorCount[3] + Life;

	return TRUE;
}

int	ResetEnergyGraph(int Num)
{
	int	Pos;

	Pos = lpCurPlayer->pZ;

	switch (Num)
	{
	case 0:
		//LIFE
		sChkLife[0] = Pos;
		sChkLife[1] = Pos ^ (-1);
		break;

	case 1:
		//MANA
		sChkMana[0] = Pos;
		sChkMana[1] = Pos ^ (-1);
		break;

	case 2:
		//STAMINA
		sChkStamina[0] = Pos;
		sChkStamina[1] = Pos ^ (-1);
		break;

	case 3:
	case 4:
		//ALL
		sChkLife[0] = Pos;
		sChkLife[1] = Pos ^ (-1);
		sChkMana[0] = Pos;
		sChkMana[1] = Pos ^ (-1);
		sChkStamina[0] = Pos;
		sChkStamina[1] = Pos ^ (-1);
		break;
	}

	return TRUE;
}
int CheckEnergyGraph()
{
	int	Pos;
	int	Grp;
	int	Last_Grp;
	int cnt;

	Pos = lpCurPlayer->pZ;

	Last_Grp = sChkLife[0] ^ sChkLife[1];
	Grp = sinGetLife();
	if (Last_Grp != -1)
	{
		cnt = Grp - Last_Grp;
		if (cnt > 15)
			EnergyGraphErrorCount[0] ++;
	}
	sChkLife[0] = Pos;
	sChkLife[1] = Pos ^ Grp;

	Last_Grp = sChkMana[0] ^ sChkMana[1];
	Grp = sinGetMana();
	if (Last_Grp != -1)
	{
		cnt = Grp - Last_Grp;
		if (cnt > 15)
			EnergyGraphErrorCount[1] ++;
	}
	sChkMana[0] = Pos;
	sChkMana[1] = Pos ^ Grp;

	Last_Grp = sChkStamina[0] ^ sChkStamina[1];
	Grp = sinGetStamina();
	if (Last_Grp != -1)
	{
		cnt = Grp - Last_Grp;
		if (cnt > 50)
			EnergyGraphErrorCount[2] ++;
	}
	sChkStamina[0] = Pos;
	sChkStamina[1] = Pos ^ Grp;

	return TRUE;
}
Item *FindInvenItem(DWORD dwItemCode, DWORD dwHead, DWORD dwChkSum)
{
	int cnt;
	Item *lpItem;

	if ((dwItemCode&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
		return NULL;

	for (cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if (cInvenTory.InvenItem[cnt].bValid)
		{
			lpItem = &cInvenTory.InvenItem[cnt].sItem;
			if (lpItem->sItemID.ToInt() == dwItemCode && lpItem->iChk1 == dwHead && lpItem->iChk2 == dwChkSum)
				return lpItem;
		}
	}

	for (cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if (cInvenTory.InvenItemTemp[cnt].bValid)
		{
			lpItem = &cInvenTory.InvenItemTemp[cnt].sItem;

			if (lpItem->sItemID.ToInt() == dwItemCode && lpItem->iChk1 == dwHead && lpItem->iChk2 == dwChkSum)
				return lpItem;
		}
	}
	if (cTrade.OpenFlag)
	{
		for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++)
		{
			if (sTrade.TradeItem[cnt].bValid)
			{
				lpItem = &sTrade.TradeItem[cnt].sItem;
				if (lpItem->sItemID.ToInt() == dwItemCode && lpItem->iChk1 == dwHead && lpItem->iChk2 == dwChkSum)
					return lpItem;
			}
		}
	}

	if (MouseItem.bValid)
	{
		lpItem = &MouseItem.sItem;
		if (lpItem->sItemID.ToInt() == dwItemCode && lpItem->iChk1 == dwHead && lpItem->iChk2 == dwChkSum)
			return lpItem;
	}

	if (cWareHouse.OpenFlag)
	{
		for (cnt = 0; cnt < 100; cnt++)
		{
			if (cWareHouse.WareHouse.WareHouseItem[cnt].bValid)
			{
				lpItem = &cWareHouse.WareHouse.WareHouseItem[cnt].sItem;
				if (lpItem->sItemID.ToInt() == dwItemCode && lpItem->iChk1 == dwHead && lpItem->iChk2 == dwChkSum)
					return lpItem;
			}
		}
	}

	if (cCraftItem.OpenFlag)
	{
		for (cnt = 0; cnt < 15; cnt++)
		{
			if (sCraftItem.CraftItem[cnt].bValid)
			{
				lpItem = &sCraftItem.CraftItem[cnt].sItem;
				if (lpItem->sItemID.ToInt() == dwItemCode && lpItem->iChk1 == dwHead && lpItem->iChk2 == dwChkSum)
					return lpItem;
			}
		}
	}

	if (cAging.OpenFlag)
	{
		for (cnt = 0; cnt < 15; cnt++)
		{
			if (sAgingItem.AgingItem[cnt].bValid)
			{
				lpItem = &sAgingItem.AgingItem[cnt].sItem;
				if (lpItem->sItemID.ToInt() == dwItemCode && lpItem->iChk1 == dwHead && lpItem->iChk2 == dwChkSum)
					return lpItem;
			}
		}
	}
	if (SmeltingItem.OpenFlag)
	{
		for (cnt = 0; cnt < 5; cnt++)
		{
			if (S_smeltingItem.SmeltingItem[cnt].bValid)
			{
				lpItem = &S_smeltingItem.SmeltingItem[cnt].sItem;
				if (lpItem->sItemID.ToInt() == dwItemCode && lpItem->iChk1 == dwHead && lpItem->iChk2 == dwChkSum)
					return lpItem;
			}
		}
	}
	if (ManufactureItem.m_OpenFlag)
	{
		for (cnt = 0; cnt < 4; cnt++)
		{
			if (sManufactureItem.ManufactureItem[cnt].bValid)
			{
				lpItem = &sManufactureItem.ManufactureItem[cnt].sItem;
				if (lpItem->sItemID.ToInt() == dwItemCode && lpItem->iChk1 == dwHead && lpItem->iChk2 == dwChkSum)
					return lpItem;
			}
		}
	}
	if (cMixtureReset.OpenFlag)
	{
		for (cnt = 0; cnt < 2; cnt++)
		{
			if (sMixtureResetItem.MixtureResetItem[cnt].bValid)
			{
				lpItem = &sMixtureResetItem.MixtureResetItem[cnt].sItem;
				if (lpItem->sItemID.ToInt() == dwItemCode && lpItem->iChk1 == dwHead && lpItem->iChk2 == dwChkSum)
					return lpItem;
			}
		}
	}
	if (cElement.OpenFlag)
	{
		for (cnt = 0; cnt < 6; cnt++)
		{
			if (cElement.ElementItem[cnt].bValid)
			{
				lpItem = &cElement.ElementItem[cnt].sItem;
				if (lpItem->sItemID.ToInt() == dwItemCode && lpItem->iChk1 == dwHead && lpItem->iChk2 == dwChkSum)
					return lpItem;
			}
		}
	}
	if (cSocket.OpenFlag)
	{
		for (cnt = 0; cnt < 5; cnt++)
		{
			lpItem = &cSocket.SocketItem[cnt].sItem;

			if (lpItem->sItemID.ToInt() == dwItemCode && lpItem->iChk1 == dwHead && lpItem->iChk2 == dwChkSum)
				return lpItem;
		}
	}
	if (cCaravan.OpenFlag)
	{
		for (cnt = 0; cnt < 100; cnt++)
		{
			if (cCaravan.sCaravan.Item[cnt].bValid)
			{
				lpItem = &cCaravan.sCaravan.Item[cnt].sItem;
				if (lpItem->sItemID.ToInt() == dwItemCode && lpItem->iChk1 == dwHead && lpItem->iChk2 == dwChkSum)
					return lpItem;
			}
		}
	}
	return NULL;
}
int SendInvenItemError(DWORD dwKind, DWORD dwItemCode, DWORD dwHead, DWORD dwChkSum)
{
	smTRANS_COMMAND	smTransCommand;

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = smTRANSCODE_INVEN_ERR_ITEM;
	smTransCommand.WParam = dwKind;

	smTransCommand.LParam = dwItemCode;
	smTransCommand.SParam = dwHead;
	smTransCommand.EParam = dwChkSum;

	SENDPACKETL(&smTransCommand);

	return TRUE;
}

int	GetTotalInvenMoney()
{
	int Money;

	Money = lpCurPlayer->sCharacterData.iGold;

	if (cTrade.OpenFlag && sTrade.Money)
		Money += sTrade.Money - 193;

	if (cWareHouse.OpenFlag)
		//Money += sWareHouse.Money -2023;
		Money += cWareHouse.Money;

	return Money;
}

DWORD	dwTotal_CheckMoney = 0;
DWORD	dwTotal_CheckMoneyTime = 0;
#define	TOTAL_CHECK_MONEY_MASK	0x0018cccc
int		NChkMode = 0;


int	ResetInvenMoney()
{
	dwTotal_CheckMoney = GetTotalInvenMoney();
	dwTotal_CheckMoney = dwPlayTime ^ dwTotal_CheckMoney;
	dwTotal_CheckMoneyTime = dwPlayTime ^ TOTAL_CHECK_MONEY_MASK;

	return TRUE;
}
int	AddInvenMoney(int Money)
{
	int	m;

	m = dwTotal_CheckMoney ^ (dwTotal_CheckMoneyTime^TOTAL_CHECK_MONEY_MASK);
	m += Money;
	if (m < 0) m = 0;

	dwTotal_CheckMoney = dwPlayTime ^ m;
	dwTotal_CheckMoneyTime = dwPlayTime ^ TOTAL_CHECK_MONEY_MASK;

	return TRUE;
}
int	CheckInvenMoney()
{
	DWORD dwCode;
	smTRANS_COMMAND	smTransCommand;

	if (cShop.OpenFlag || SkillMasterFlag || cCraftItem.OpenFlag || cAging.OpenFlag || SmeltingItem.OpenFlag || ManufactureItem.m_OpenFlag || cMixtureReset.OpenFlag)  // 籍瘤侩 - 雇胶媚 府悸 芒 眠啊
	{
		NChkMode = TRUE;
		return TRUE;
	}

	if (NChkMode)
	{
		NChkMode = 0;
		ResetInvenMoney();
		if (NChkMode == 0) return TRUE;
		dwCode = 0;
	}
	else
		dwCode = GetTotalInvenMoney();

	if (dwCode != (dwTotal_CheckMoney ^ (dwTotal_CheckMoneyTime^TOTAL_CHECK_MONEY_MASK)))
	{
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.code = smTRANSCODE_INVEN_ERR_MONEY;
		smTransCommand.WParam = 0;
		smTransCommand.LParam = dwCode;
		smTransCommand.SParam = (dwTotal_CheckMoney ^ (dwTotal_CheckMoneyTime^TOTAL_CHECK_MONEY_MASK));
		smTransCommand.EParam = 0;

		SENDPACKETL(&smTransCommand);
	}

	dwTotal_CheckMoney = dwPlayTime ^ dwCode;
	dwTotal_CheckMoneyTime = dwPlayTime ^ TOTAL_CHECK_MONEY_MASK;

	return TRUE;
}

int SendUsingItemListToServer()
{
	int cnt;
	Item *lpItem;

	TRANS_USINGITEM	TransUsingItem;

	ZeroMemory(&TransUsingItem, sizeof(TRANS_USINGITEM));

	TransUsingItem.size = sizeof(TRANS_USINGITEM);
	TransUsingItem.code = smTRANSCODE_INVEN_POSITION;

	for (cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if (cInvenTory.InvenItem[cnt].bValid && cInvenTory.InvenItem[cnt].iItemSlot)
		{
			lpItem = &cInvenTory.InvenItem[cnt].sItem;
			if (lpItem->szItemName[0])
			{
				if (TransUsingItem.ItemListCount >= 16) break;
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].dwCode = lpItem->sItemID.ToInt();
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].Performance[0] = cInvenTory.InvenItem[cnt].iItemSlot;
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].Performance[1] = lpItem->sDamage.sMax;
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].Performance[2] = lpItem->iDefenseRating;
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].Performance[3] = (short)lpItem->fBlockRating;
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].Performance[4] = (short)lpItem->fAbsorbRating;
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].Performance[5] = lpItem->iAttackRating;
				TransUsingItem.ItemListCount++;
			}
		}
	}

	for (cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if (cInvenTory.InvenItemTemp[cnt].bValid && cInvenTory.InvenItemTemp[cnt].iItemSlot)
		{
			lpItem = &cInvenTory.InvenItemTemp[cnt].sItem;
			if (lpItem->szItemName[0])
			{
				if (TransUsingItem.ItemListCount >= 16)
					break;
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].dwCode = lpItem->sItemID.ToInt();
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].Performance[0] = cInvenTory.InvenItemTemp[cnt].iItemSlot | 0x100;
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].Performance[1] = lpItem->sDamage.sMax;
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].Performance[2] = lpItem->iDefenseRating;
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].Performance[3] = (short)lpItem->fBlockRating;
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].Performance[4] = (short)lpItem->fAbsorbRating;
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].Performance[5] = lpItem->iAttackRating;
				TransUsingItem.ItemListCount++;
			}
		}
	}

	SENDPACKETG(&TransUsingItem);

	return NULL;
}
int SendUsingItemListToServer2()
{
	int cnt;
	Item *lpItem;

	TRANS_USINGITEM	TransUsingItem;

	ZeroMemory(&TransUsingItem, sizeof(TRANS_USINGITEM));

	TransUsingItem.size = sizeof(TRANS_USINGITEM);
	TransUsingItem.code = smTRANSCODE_INVEN_POSITION2;

	for (cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if (cInvenTory.InvenItem[cnt].bValid && cInvenTory.InvenItem[cnt].iItemSlot)
		{
			lpItem = &cInvenTory.InvenItem[cnt].sItem;
			if (lpItem->szItemName[0])
			{
				if (TransUsingItem.ItemListCount >= 16)
					break;
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].dwCode = lpItem->sItemID.ToInt();
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].Performance[0] = cInvenTory.InvenItem[cnt].iItemSlot;
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].Performance[1] = lpItem->sDamage.sMax;
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].Performance[2] = lpItem->iDefenseRating;
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].Performance[3] = (short)lpItem->fBlockRating;
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].Performance[4] = (short)lpItem->fAbsorbRating;
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].Performance[5] = lpItem->iAttackRating;
				TransUsingItem.ItemListCount++;
			}
		}
	}

	SENDPACKETG(&TransUsingItem);

	return NULL;
}
int CheckChangeJob(CharacterData *pCharInfo)
{
	if (pCharInfo->iLevel < 20)
		return FALSE;
	else if (pCharInfo->iLevel < 40)
	{
		if (pCharInfo->iRank > 0)
			return FALSE;
	}
	else if (pCharInfo->iLevel < 60)
	{
		if (pCharInfo->iRank > 1)
			return FALSE;
	}
	else if (pCharInfo->iLevel < 80)
	{
		if (pCharInfo->iRank > 2)
			return FALSE;
	}
	if (pCharInfo->iRank >= CHARACTERRANK_Rank5)
		return FALSE;

	return TRUE;
}
DWORD GetPlayTime_T()
{
	DWORD dwTime;

	if (dwTime_ServerT)
	{
		dwTime = (dwPlayTime - dwTime_ConnectMS) / 1000;
		dwTime = dwTime_ServerT + dwTime;
		return dwTime;
	}

	return NULL;
}
//改变大头模式
int	ChangeBigHeadMode(int Mode)
{
	//DWORD	dwTime;

	if (Mode)
		ChangeModelSkin(lpCurPlayer, 1, Mode + 4, 0, 0);
	else
		ChangeModelSkin(lpCurPlayer, 0, lpCurPlayer->sCharacterData.iRank, 0, GetFaceHairSkin(lpCurPlayer));

	lpCurPlayer->sCharacterData.bUpdateInfo[0]++;
	ReformCharForm();
	SendSetObjectSerial(lpCurPlayer->iID);

	if (RestartPlayCount < 350)
		RestartPlayCount = 350;

	return TRUE;
}
//设置大头到图片
int SetBigHeadToImage(int Kind, int Time)
{
	int Sex;
	chaPremiumitem.m_BigHeadTime = Time;
#ifdef ENGLISH_LANGUAGE
	switch (Kind)
	{
	case 1:
	case 2:
		chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIG_HEAD, chaPremiumitem.m_BigHeadTime, true, "Big Head", Kind);
		break;
	case 3:
		chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIG_HEAD, chaPremiumitem.m_BigHeadTime, true, "Big Head Of Shyness", Kind);
		break;
	case 4:
		chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIG_HEAD, chaPremiumitem.m_BigHeadTime, true, "Big Head Of Love", Kind);
		break;
	case 5:
		chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIG_HEAD, chaPremiumitem.m_BigHeadTime, true, "Big Head Of Sadness", Kind);
		break;
	case 6:
		chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIG_HEAD, chaPremiumitem.m_BigHeadTime, true, "Big Head Of Happyness", Kind);
		break;
	case 7:
		chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIG_HEAD, chaPremiumitem.m_BigHeadTime, true, "Big Head");
		break;
	case 8:
		chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIG_GIRAFFEHAT, chaPremiumitem.m_BigHeadTime, true, "Giraffe Hat");
		break;
	case 9:
		Sex = GetSex(sinChar->iClass);
		switch (Sex)
		{
		case BROOD_CODE_MAN:
			chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIG_MAGICIANHAT, chaPremiumitem.m_BigHeadTime, true, "Magician Hat");
			break;
		case BROOD_CODE_WOMAN:
			chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIG_WITCHHAT, chaPremiumitem.m_BigHeadTime, true, "Witch Hat");
			break;
		}
		break;
	case 10:
		Sex = GetSex(sinChar->iClass);
		switch (Sex)
		{
		case BROOD_CODE_MAN:
			chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIG_MASKEDMAN, chaPremiumitem.m_BigHeadTime, true, "Traditional Mask");
			break;
		case BROOD_CODE_WOMAN:
			chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIG_MASKEDWOMAN, chaPremiumitem.m_BigHeadTime, true, "Traditional Mask");
			break;
		}
		break;
	case 11:
		chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIG_PUMPKINHAT, chaPremiumitem.m_BigHeadTime, true, "Pumpkin Hat");
		break;
	case 12:
		chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIG_SHEEPHAT, chaPremiumitem.m_BigHeadTime, true, "Sheep Hat");
		break;
	case 13:
		chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIG_SOCCERHAT, chaPremiumitem.m_BigHeadTime, true, "Soccer Hat");
		break;
	case 14:
		chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIG_GREENXMASHAT, chaPremiumitem.m_BigHeadTime, true, "Green Xmas Hat");
		break;
	case 15:
		chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIG_REDXMASHAT, chaPremiumitem.m_BigHeadTime, true, "Red Xmas Hat");
		break;
	case 16:
		chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIG_EASTER, chaPremiumitem.m_BigHeadTime, true, "Bunny Ears");
		break;
	case 17:
		chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIG_BIRTHDAY, chaPremiumitem.m_BigHeadTime, true, "Birthday Hat");
		break;
	case 18:
		chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIG_BLUEXMASHAT, chaPremiumitem.m_BigHeadTime, true, "Blue Xmas Hat");
		break;
	}
#else
	switch (Kind)
	{
	case 1:
	case 2:
		chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIG_HEAD, chaPremiumitem.m_BigHeadTime, true, "大头药水", Kind);
		break;
	case 3:
		chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIG_HEAD, chaPremiumitem.m_BigHeadTime, true, "快乐药水", Kind);
		break;
	case 4:
		chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIG_HEAD, chaPremiumitem.m_BigHeadTime, true, "爱情药水", Kind);
		break;
	case 5:
		chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIG_HEAD, chaPremiumitem.m_BigHeadTime, true, "悲伤药水", Kind);
		break;
	case 6:
		chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIG_HEAD, chaPremiumitem.m_BigHeadTime, true, "兴奋药水", Kind);
		break;
	case 7:
		chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIG_HEAD, chaPremiumitem.m_BigHeadTime, true, "大头药水");
		break;
	case 8:
		chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIG_GIRAFFEHAT, chaPremiumitem.m_BigHeadTime, true, "长颈鹿");
		break;
	case 9:
		Sex = GetSex(sinChar->iClass);
		switch (Sex)
		{
		case BROOD_CODE_MAN:
			chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIG_MAGICIANHAT, chaPremiumitem.m_BigHeadTime, true, "魔法帽子");
			break;
		case BROOD_CODE_WOMAN:
			chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIG_WITCHHAT, chaPremiumitem.m_BigHeadTime, true, "魔法帽子");
			break;
		}
		break;
	case 10:
		Sex = GetSex(sinChar->iClass);
		switch (Sex)
		{
		case BROOD_CODE_MAN:
			chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIG_MASKEDMAN, chaPremiumitem.m_BigHeadTime, true, "面具");
			break;
		case BROOD_CODE_WOMAN:
			chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIG_MASKEDWOMAN, chaPremiumitem.m_BigHeadTime, true, "面具");
			break;
		}
		break;
	case 11:
		chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIG_PUMPKINHAT, chaPremiumitem.m_BigHeadTime, true, "南瓜头");
		break;
	case 12:
		chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIG_SHEEPHAT, chaPremiumitem.m_BigHeadTime, true, "喜洋洋");
		break;
	case 13:
		chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIG_SOCCERHAT, chaPremiumitem.m_BigHeadTime, true, "足球帽");
		break;
	case 14:
		chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIG_GREENXMASHAT, chaPremiumitem.m_BigHeadTime, true, "圣诞帽子");
		break;
	case 15:
		chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIG_REDXMASHAT, chaPremiumitem.m_BigHeadTime, true, "圣诞帽子");
		break;
	case 16:
		chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIG_EASTER, chaPremiumitem.m_BigHeadTime, true, "复活节耳朵");
		break;
	case 17:
		chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIG_BIRTHDAY, chaPremiumitem.m_BigHeadTime, true, "生日帽子");
		break;
	case 18:
		chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIG_BLUEXMASHAT, chaPremiumitem.m_BigHeadTime, true, "圣诞帽子");
		break;
	}
#endif
	return TRUE;
}
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

							LoadOftenMeshPattern(szFilePath);
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
extern SBL_SetFontEffect SoD_SetFontEffect;


int	Sod_SodEffect(int Round)
{
	if (!BellatraEffectInitFlag)
		return FALSE;

	SetBellatraFontEffect(E_BL_FONT_ROUND);

	switch (Round)
	{
	case 1:
		SetBellatraFontEffect(E_BL_FONT_COUNT_1);
		break;
	case 2:
		SetBellatraFontEffect(E_BL_FONT_COUNT_2);
		break;
	case 3:
		SetBellatraFontEffect(E_BL_FONT_COUNT_3);
		break;
	case 4:
		SetBellatraFontEffect(E_BL_FONT_COUNT_4);
		break;
	case 5:
		SetBellatraFontEffect(E_BL_FONT_COUNT_5);
		break;
	case 6:
		SetBellatraFontEffect(E_BL_FONT_COUNT_6);
		break;
	case 7:
		SetBellatraFontEffect(E_BL_FONT_COUNT_7);
		break;
	case 8:
		SetBellatraFontEffect(E_BL_FONT_COUNT_8);
		break;
	}
	SetBellatraFontEffect(E_BL_FONT_START);

	esPlayContSound(Round);

	return TRUE;
}



SBL_SetFontEffect SoD_SetFontEffect_CloseScreen;
char	szSOD_String[64] = { 0, };
BYTE	bSOD_StringColor[4];
int		SOD_StringCount = 0;
int		TeamScoreSort[4];
int		TeamMarkSort[4] = { 3 , 0 , 2 , 1 };
int		SoDGateFlag;


int	SetSodScoreResult()
{
	int cnt;

	g_EventScore.TeamNum = 0;
	g_EventScore.EntryTeamNum = 0;

	for (cnt = 0; cnt < 4; cnt++)
	{
		g_EventScore.TeamMarkBuff[cnt] = TeamMarkSort[TeamScoreSort[cnt]];
		wsprintf(g_EventScore.szTeamPointBuff[cnt], "%d", sSodScore.TeamScore[TeamScoreSort[cnt]]);
	}
	for (cnt = 0; cnt < 2; cnt++)
		g_EventScore.EntryTeamMarkBuff[cnt] = g_EventScore.TeamMarkBuff[cnt];

	if (sSodScore.Round > 0 && sSodScore.Round <= 4)
	{
		g_EventScore.TeamNum = 4;
		g_EventScore.EntryTeamNum = 2;
	}
	if (sSodScore.Round > 4 && sSodScore.Round <= 6)
	{
		g_EventScore.TeamNum = 2;
		g_EventScore.EntryTeamNum = 1;
	}

	if (!g_EventScore.TeamNum) return FALSE;

	return TRUE;
}

int	SodScoreMain()
{
	int dx, dy, dz;
	int cnt;

	if (!SodScoreFlag)
	{
		SodScoreFlag = TRUE;
		ZeroMemory(&sSodScore, sizeof(sSOD_SCORE));
	}

	if (SOD_StringCount)
		SOD_StringCount--;


	if (sSodScore.dwSoD_NextStageTime)
	{
		if (sSodScore.dwSoD_CloseStageTime && sSodScore.dwSoD_CloseStageTime < dwPlayTime)
		{
			if (SoD_SetFontEffect_CloseScreen.eBL_Type != E_BL_CHANGE_TRUE)
			{
				if (SoDGateFlag == TRUE && SetSodScoreResult() == TRUE)
					SetBellatraFontEffect(E_BL_CHANGE_TRUE, &SoD_SetFontEffect_CloseScreen, E_BL_EVENT_SCORE);
				else
					SetBellatraFontEffect(E_BL_CHANGE_TRUE, &SoD_SetFontEffect_CloseScreen);

				esPlaySound(18, 400);
			}

			sSodScore.dwSoD_CloseStageTime = 0;
		}

		if (sSodScore.dwSoD_NextStageTime < dwPlayTime)
		{
			if (SoD_SetFontEffect_CloseScreen.eBL_Type == E_BL_CHANGE_TRUE)
			{
				CheckBellatraFontEffect(&SoD_SetFontEffect_CloseScreen, TRUE);
				SetBellatraFontEffect(E_BL_CHANGE_FALSE, &SoD_SetFontEffect_CloseScreen);
				esPlaySound(18, 400);
			}

			if (sSodScore.SodNextStageNum >= 0 && lpCurPlayer->psModelAnimation->iType != ANIMATIONTYPE_Die)
			{
				if (CheckHardCoreEventArea(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ) == TRUE && sSodScore.SodNextStageNum < 100)
				{
					dx = HardCoreEventOpenPos[sSodScore.SodNextStageNum][2].x*fONE;
					dy = HardCoreEventOpenPos[sSodScore.SodNextStageNum][2].y*fONE;
					dz = HardCoreEventOpenPos[sSodScore.SodNextStageNum][2].z*fONE;

					CloseEachPlayer();

					GAMEMAP->WarpMap(MAPID_Bellatra, dx, dz);

					lpCurPlayer->SetPosi(dx, 0, dz, 0, 0, 0);
					TraceCameraPosi.x = lpCurPlayer->pX;
					TraceCameraPosi.y = lpCurPlayer->pY;
					TraceCameraPosi.z = lpCurPlayer->pZ;
					TraceTargetPosi.x = lpCurPlayer->pX;
					TraceTargetPosi.y = lpCurPlayer->pY;
					TraceTargetPosi.z = lpCurPlayer->pZ;

					lpCurPlayer->iLoadedMapIndex = -1;

					if (smGameStage[0])
					{
						cnt = smGameStage[0]->GetFloorHeight(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, lpCurPlayer->Pattern->SizeHeight);
						lpCurPlayer->iLoadedMapIndex = 0;
					}
					if (cnt == CLIP_OUT && smGameStage[1])
						lpCurPlayer->iLoadedMapIndex = 1;

					sSodScore.EffectStartCount = 70 * 1;
					sSodScore.EffectCode = sSodScore.NextRound;
				}
			}
			else if (sSodScore.SodNextStageNum == -1)
			{
				BaseMap * pcMap = GAMEMAP->pcaBaseMap + rsSOD_VILLAGE;
				Point3D sPosition = pcMap->sPositionCenter;

				CloseEachPlayer();

				GAMEMAP->WarpMap(MAPID_NaviskoTown, sPosition.iX, sPosition.iZ);

				lpCurPlayer->SetPosi(sPosition.iX, 0, sPosition.iZ, 0, 0, 0);
				TraceCameraPosi.x = lpCurPlayer->pX;
				TraceCameraPosi.y = lpCurPlayer->pY;
				TraceCameraPosi.z = lpCurPlayer->pZ;
				TraceTargetPosi.x = lpCurPlayer->pX;
				TraceTargetPosi.y = lpCurPlayer->pY;
				TraceTargetPosi.z = lpCurPlayer->pZ;

				lpCurPlayer->iLoadedMapIndex = -1;

				if (smGameStage[0])
				{
					cnt = smGameStage[0]->GetFloorHeight(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, lpCurPlayer->Pattern->SizeHeight);
					lpCurPlayer->iLoadedMapIndex = 0;
				}
				if (cnt == CLIP_OUT && smGameStage[1])
					lpCurPlayer->iLoadedMapIndex = 1;
			}
			else if (sSodScore.SodNextStageNum == -2)
			{
				if (SoD_SetFontEffect.eBL_Type == E_BL_LODING)
					CheckBellatraFontEffect(&SoD_SetFontEffect, TRUE);
			}

			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Idle);
			lpCurPlayer->dwNextMotionCode = 0;
			sSodScore.dwSoD_NextStageTime = 0;
		}
		else
		{
			if (sSodScore.SodNextStageNum >= 0)
				lpCurPlayer->dwNextMotionCode = ANIMATIONTYPE_Yahoo;
		}
	}

	if (sSodScore.EffectStartCount)
	{
		sSodScore.EffectStartCount--;
		if (sSodScore.EffectStartCount == 0)
		{
			switch (sSodScore.EffectCode)
			{
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
				Sod_SodEffect(sSodScore.EffectCode);
				break;
			}
		}
	}

	if (sSodScore.ScoreEffectCount)
	{
		sSodScore.ScoreEffectCount -= 8;
		if (sSodScore.ScoreEffectCount < 0)
			sSodScore.ScoreEffectCount = 0;
	}

	if (rsBlessCastle.CastleMode == 3)
	{
		if (rsBlessCastle.dwMasterClan &&
			rsBlessCastle.dwMasterClan == GetClanCode(lpCurPlayer->sCharacterData.iClanID))
		{
			if (!lpCurPlayer->dwNextMotionCode)
				lpCurPlayer->dwNextMotionCode = ANIMATIONTYPE_Yahoo;
		}
	}

	return TRUE;
}

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

int	DisplaySodScore()
{
	char szBuff[256];
	int x, y;
	int cnt, cnt2;
	DWORD	dwColor;
	DWORD tM, tS;
	int len;
	int RnkCnt = 0;

	if (!SodScoreFlag)
	{
		SodScoreFlag = TRUE;
		ZeroMemory(&sSodScore, sizeof(sSOD_SCORE));
	}

	psSetRenderState(1);

	if (SOD_StringCount)
	{
		len = lstrlen(szSOD_String);
		if ((SOD_StringCount & 0x8) == 0)
			DrawFontImage(szSOD_String, MidX - len * 16, 330, D3DCOLOR_RGBA(bSOD_StringColor[0], bSOD_StringColor[1], bSOD_StringColor[2], 255), 2.0f);
	}

	if (sSodScore.dwDispTime > dwPlayTime && CheckHardCoreEventArea(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ) == TRUE)
	{
		x = ((int)RESOLUTION_WIDTH / 2) - 80; y = 8;

		wsprintf(szBuff, "ROUND %d", sSodScore.Round);
		DrawFontImage(szBuff, x - 40, y, D3DCOLOR_RGBA(80, 255, 40, 255), 0.9f);

		if (sSodScore.dwPlayTime)
		{
			tM = (dwPlayTime - sSodScore.dwPlayTime) / 1000;
			tS = tM % 60;
			tM = tM / 60;
			if (tM > 99 || tM < 0) tM = 99;
		}
		else
		{
			tM = 0;
			tS = 0;
		}

		wsprintf(szBuff, "PlayTime %d:%d", tM, tS);
		DrawFontImage(szBuff, x + 160, y + 2, D3DCOLOR_RGBA(80, 160, 255, 255), 0.7f);

		y += 24;

		wsprintf(szBuff, "Score %d", sSodScore.Score);

		if (sSodScore.ScoreEffectCount)
			DrawFontImage(szBuff, x - 40, y + 8, D3DCOLOR_RGBA(255, 128, 64, 255 - sSodScore.ScoreEffectCount), 0.9f);
		else
			DrawFontImage(szBuff, x - 40, y + 8, D3DCOLOR_RGBA(255, 255, 0, 255), 0.9f);


		SodTeamSort();

		for (cnt = 0; cnt < 4; cnt++)
		{
			cnt2 = TeamScoreSort[cnt];

			if (sSodScore.MyTeam == cnt2)
				dwColor = D3DCOLOR_RGBA(255, 255, 0, 255);
			else
				dwColor = D3DCOLOR_RGBA(255, 128, 0, 255);

			DrawSpecialFontImage(TeamMarkSort[cnt2], x + 160, y, D3DCOLOR_RGBA(255, 255, 255, 255), 0.7f);

			wsprintf(szBuff, "Team %d", sSodScore.TeamScore[cnt2]);
			DrawFontImage(szBuff, x + 190, y, dwColor, 0.7f);
			y += 18;
		}
	}

	return FALSE;
}