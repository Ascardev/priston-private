#include "StdAfx.h"
#include "character.h"
#include "playmain.h"
#include "fileread.h"
#include "netplay.h"

#include "record.h"
#include "playsub.h"
#include "srcserver\\onserver.h"

char	*szRecordHeader = "RC 1.70";
DWORD	dwRecordVersion = 170;

char	*szRecordUserDataDir = "userdata";
char	*szRecordUserBackupDataDir = "userdata_backup";
char	*szRecordUserInfoDir = "userinfo";
char	*szRecordWareHouseDir = "warehouse";
char	*szRecordDeleteDir = "deleted";
char	*szPostBoxDir = "PostBox";
char	*szRecordCaravanDir = "Caravandata";

LastQuestSave	RecordLastQuestInfo;

#define	CHAR_NAME_MAXLEN	(16+2)

int	Permit_CheckMoney = TOTAL_CHECK_MONEY_MAX;
int	Permit_CheckExp = TOTAL_CHECK_EXP_MAX;

extern rsSERVER_CONFIG		rsServerConfig;

extern int					Server_DebugCount;


int RecordHackLogFile(User *lpPlayInfo, void *lpTransCommand);

#include "resource.h"

static char LastAcessID[64];


struct sREC_DATABUFF
{
	User	*lpPlayInfo;
	DWORD		dwConnectCount;
	char		szName[32];
	char		szFileName[128];
	char		szBackupFileName[128];
	CharacterFile	TransRecData;
};

#define	REC_DATABUFF_MAX		128
#define	REC_DATABUFF_MASK		127
#define	REC_DATABUFF_LIMIT		64

sREC_DATABUFF	*sRecDataBuff = 0;
int				sRecDataBuffCount;
HANDLE			hRecThread = 0;
DWORD			dwRecThreadId;
DWORD			dwLastRecDataTime = 0;

CRITICAL_SECTION	cRecDataSection;
CRITICAL_SECTION	cSaveDataSection;

int rsSaveRecData(CharacterFile *lpTransRecordData, User *lpPlayInfo, char *szFileName, char *szBackupFileName);
int CheckRecWaitData(char *szName);
int	OpenStarPointEvent(User *lpPlayInfo, CharacterData *lpCharInfo);
int	CloseStarPointEvent(User *lpPlayInfo, CharacterData *lpCharInfo);


int	EncodeFileName(char *szName, char *szDecodeName)
{
	int	len;
	int cnt;
	int cnt2;
	BYTE ch1, ch2;
	DWORD ch;

	len = lstrlen(szName);

	cnt2 = 0;

	for (cnt = 0; cnt < len; cnt++)
	{
		ch = (DWORD)szName[cnt];
		ch1 = (BYTE)(ch >> 4) & 0xF;
		ch2 = (BYTE)ch & 0xF;
		ch1 += 'a';
		ch2 += 'a';
		szDecodeName[cnt2++] = (char)ch1;
		szDecodeName[cnt2++] = (char)ch2;
	}
	szDecodeName[cnt2] = 0;

	return TRUE;
}
static int GetCharSize(char *Buffer, int MaxSize)
{
	if (lstrlen(Buffer) < 0 || lstrlen(Buffer) > MaxSize)
		Buffer[MaxSize] = '\0';
	return TRUE;
}
static int GetUserCode(char *szName)
{
	int cnt, len;
	BYTE ch;
	BYTE *lpData = (BYTE *)szName;

	len = lstrlen(szName);

	ch = 0;

	for (cnt = 0; cnt < len; cnt++)
	{
		if (lpData[cnt] >= 'a' && lpData[cnt] <= 'z')
			ch += (lpData[cnt] - 0x20);
		else
			ch += lpData[cnt];
	}

	return ch;
}
int GetPostBoxFile(char *szID, char *szFileName, int MaxSize)
{
	if (szID[4] == 0 && szID[3] >= '0' && szID[3] <= '9' && (((szID[0] == 'c' || szID[0] == 'C') && (szID[1] == 'o' || szID[1] == 'O') && (szID[2] == 'm' || szID[2] == 'M')) || ((szID[0] == 'l' || szID[0] == 'L') && (szID[1] == 'p' || szID[1] == 'P') && (szID[2] == 't' || szID[2] == 'T'))))
	{
		wsprintf(szFileName, "%s\\%d\\££%s.dat", szPostBoxDir, GetUserCode(szID), szID);
		GetCharSize(szFileName, MaxSize);
		return TRUE;
	}

	if (szID[3] == 0 && ((szID[0] == 'p' || szID[0] == 'P') && (szID[1] == 'r' || szID[1] == 'R') && (szID[2] == 'n' || szID[2] == 'N')) || ((szID[0] == 'c' || szID[0] == 'C') && (szID[1] == 'o' || szID[1] == 'O') && (szID[2] == 'n' || szID[2] == 'N')))
	{
		wsprintf(szFileName, "%s\\%d\\££%s.dat", szPostBoxDir, GetUserCode(szID), szID);
		GetCharSize(szFileName, MaxSize);
		return TRUE;
	}

	wsprintf(szFileName, "%s\\%d\\%s.dat", szPostBoxDir, GetUserCode(szID), szID);

	GetCharSize(szFileName, MaxSize);

	return TRUE;
}

static int GetUserInfoFile(char *szID, char *szFileName, int MaxSize)
{
	if (szID[4] == 0 && szID[3] >= '0' && szID[3] <= '9' && (((szID[0] == 'c' || szID[0] == 'C') && (szID[1] == 'o' || szID[1] == 'O') && (szID[2] == 'm' || szID[2] == 'M')) || ((szID[0] == 'l' || szID[0] == 'L') && (szID[1] == 'p' || szID[1] == 'P') && (szID[2] == 't' || szID[2] == 'T'))))
	{
		wsprintf(szFileName, "DataServer\\%s\\%d\\££%s.dat", szRecordUserInfoDir, GetUserCode(szID), szID);
		GetCharSize(szFileName, MaxSize);
		return TRUE;
	}

	if (szID[3] == 0 && ((szID[0] == 'p' || szID[0] == 'P') && (szID[1] == 'r' || szID[1] == 'R') && (szID[2] == 'n' || szID[2] == 'N')) || ((szID[0] == 'c' || szID[0] == 'C') && (szID[1] == 'o' || szID[1] == 'O') && (szID[2] == 'n' || szID[2] == 'N')))
	{
		wsprintf(szFileName, "DataServer\\%s\\%d\\££%s.dat", szRecordUserInfoDir, GetUserCode(szID), szID);
		GetCharSize(szFileName, MaxSize);
		return TRUE;
	}

	wsprintf(szFileName, "DataServer\\%s\\%d\\%s.dat", szRecordUserInfoDir, GetUserCode(szID), szID);

	GetCharSize(szFileName, MaxSize);

	return TRUE;
}

int GetUserDataFile(char *szName, char *szFileName, int MaxSize)
{
	wsprintf(szFileName, "DataServer\\%s\\%d\\%s.dat", szRecordUserDataDir, GetUserCode(szName), szName);
	GetCharSize(szFileName, MaxSize);

	return TRUE;
}
int GetCaravanFile(char *szName, char *szFileName, int MaxSize)
{
	wsprintf(szFileName, "DataServer\\%s\\%d\\%s.dat", szRecordCaravanDir, GetUserCode(szName), szName);
	GetCharSize(szFileName, MaxSize);

	return TRUE;
}
int GetTT_ServerPath(char *szServerID, char *szTTServerPath)
{
	int cnt;

	szTTServerPath[0] = 0;

	for (cnt = 0; cnt < rsServerConfig.TT_DataServer_Count; cnt++)
	{
		if (lstrcmpi(szServerID, rsServerConfig.TT_DataServer[cnt].szServerID) == 0)
		{
			lstrcpy(szTTServerPath, rsServerConfig.TT_DataServer[cnt].szServerPath);
			return TRUE;
		}
	}

	return FALSE;
}


int GetRealID(char *szID, char *szRealID)
{
	int cnt, len;

	len = lstrlen(szID);
	lstrcpy(szRealID, szID);
	for (cnt = len - 1; cnt >= 0; cnt--)
	{
		if (szRealID[cnt] == '@')
		{
			szRealID[cnt] = 0;
			return TRUE;
		}
	}

	return FALSE;
}
int SetServerID(char *szID, char *szServerID)
{
	char szFile[64];
	int cnt, len;

	if (rsServerConfig.TT_DataServer_Count)
	{
		lstrcpy(szFile, szID);
		len = lstrlen(szFile);

		for (cnt = len - 1; cnt >= 0; cnt--)
		{
			if (szFile[cnt] == '@')
			{
				lstrcpy(szServerID, szFile + cnt + 1);
				szServerID[4] = 0;
				return TRUE;
			}
		}
	}

	return FALSE;
}
static int GetUserInfoFile2(char *szID, char *szFileName, char *szServerID, int MaxSize)
{
	char szTTServerPath[128];
	GetTT_ServerPath(szServerID, szTTServerPath);

	char szRealID[64];

	GetRealID(szID, szRealID);

	if (szID[4] == 0 && szID[3] >= '0' && szID[3] <= '9' && (((szID[0] == 'c' || szID[0] == 'C') && (szID[1] == 'o' || szID[1] == 'O') && (szID[2] == 'm' || szID[2] == 'M')) || ((szID[0] == 'l' || szID[0] == 'L') && (szID[1] == 'p' || szID[1] == 'P') && (szID[2] == 't' || szID[2] == 'T'))))
	{
		wsprintf(szFileName, "%s\\DataServer\\%s\\%d\\££%s.dat", szTTServerPath, szRecordUserInfoDir, GetUserCode(szRealID), szRealID);
		GetCharSize(szFileName, MaxSize);
		return TRUE;
	}
	if (szID[3] == 0 && ((szID[0] == 'p' || szID[0] == 'P') && (szID[1] == 'r' || szID[1] == 'R') && (szID[2] == 'n' || szID[2] == 'N')) || ((szID[0] == 'c' || szID[0] == 'C') && (szID[1] == 'o' || szID[1] == 'O') && (szID[2] == 'n' || szID[2] == 'N')))
	{
		wsprintf(szFileName, "%s\\DataServer\\%s\\%d\\££%s.dat", szTTServerPath, szRecordUserInfoDir, GetUserCode(szRealID), szRealID);
		GetCharSize(szFileName, MaxSize);
		return TRUE;
	}

	wsprintf(szFileName, "%s\\DataServer\\%s\\%d\\%s.dat", szTTServerPath, szRecordUserInfoDir, GetUserCode(szRealID), szRealID);
	GetCharSize(szFileName, MaxSize);

	return TRUE;
}
int GetUserDataFile2(char *szName, char *szFileName, char *szServerID, int MaxSize)
{
	char szTTServerPath[128];
	GetTT_ServerPath(szServerID, szTTServerPath);

	wsprintf(szFileName, "%s\\DataServer\\%s\\%d\\%s.dat", szTTServerPath, szRecordUserDataDir, GetUserCode(szName), szName);
	GetCharSize(szFileName, MaxSize);

	return TRUE;
}
static int GetDeleteDataFile(char *szName, char *szFileName, int MaxSize)
{
	wsprintf(szFileName, "DataServer\\%s\\%s.dat", szRecordDeleteDir, szName);
	GetCharSize(szFileName, MaxSize);

	return TRUE;
}

static int GetUserDataBackupFile(char *szName, char *szFileName, int MaxSize)
{
	wsprintf(szFileName, "DataServer\\%s\\%d\\%s.dat", szRecordUserBackupDataDir, GetUserCode(szName), szName);
	GetCharSize(szFileName, MaxSize);

	return TRUE;
}

static int GetWareHouseFile(char *szName, char *szFileName, int MaxSize)
{
	char *szID = szName;

	if (szID[4] == 0 && szID[3] >= '0' && szID[3] <= '9' && (((szID[0] == 'c' || szID[0] == 'C') && (szID[1] == 'o' || szID[1] == 'O') && (szID[2] == 'm' || szID[2] == 'M')) || ((szID[0] == 'l' || szID[0] == 'L') && (szID[1] == 'p' || szID[1] == 'P') && (szID[2] == 't' || szID[2] == 'T'))))
	{
		wsprintf(szFileName, "DataServer\\%s\\%d\\££%s.dat", szRecordWareHouseDir, GetUserCode(szID), szID);
		GetCharSize(szFileName, MaxSize);
		return TRUE;
	}
	if (szID[3] == 0 && ((szID[0] == 'p' || szID[0] == 'P') && (szID[1] == 'r' || szID[1] == 'R') && (szID[2] == 'n' || szID[2] == 'N')) || ((szID[0] == 'c' || szID[0] == 'C') && (szID[1] == 'o' || szID[1] == 'O') && (szID[2] == 'n' || szID[2] == 'N')))
	{
		wsprintf(szFileName, "DataServer\\%s\\%d\\££%s.dat", szRecordWareHouseDir, GetUserCode(szID), szID);
		GetCharSize(szFileName, MaxSize);
		return TRUE;
	}
	wsprintf(szFileName, "DataServer\\%s\\%d\\%s.war", szRecordWareHouseDir, GetUserCode(szName), szName);
	GetCharSize(szFileName, MaxSize);

	return TRUE;
}

static int GetUserDataFile_BackupDay(char *szName, char *szFileName, int Day, int MaxSize)
{
	wsprintf(szFileName, "%s\\%d\\%s\\%d\\%s.dat", rsServerConfig.szBackupPath, Day, szRecordUserDataDir, GetUserCode(szName), szName);
	GetCharSize(szFileName, MaxSize);

	return TRUE;
}

static int GetWareHouseFile_Backup(char *szName, char *szFileName, int Day, int MaxSize)
{
	char *szID = szName;
	char szBuff[256];

	wsprintf(szBuff, "%s\\%d", rsServerConfig.szBackupPath, Day);

	if (szID[4] == 0 && szID[3] >= '0' && szID[3] <= '9' && (((szID[0] == 'c' || szID[0] == 'C') && (szID[1] == 'o' || szID[1] == 'O') && (szID[2] == 'm' || szID[2] == 'M')) || ((szID[0] == 'l' || szID[0] == 'L') && (szID[1] == 'p' || szID[1] == 'P') && (szID[2] == 't' || szID[2] == 'T'))))
	{
		wsprintf(szFileName, "%s\\%s\\%d\\££%s.dat", szBuff, szRecordWareHouseDir, GetUserCode(szID), szID);
		GetCharSize(szFileName, MaxSize);
		return TRUE;
	}
	if (szID[3] == 0 && ((szID[0] == 'p' || szID[0] == 'P') && (szID[1] == 'r' || szID[1] == 'R') && (szID[2] == 'n' || szID[2] == 'N')) || ((szID[0] == 'c' || szID[0] == 'C') && (szID[1] == 'o' || szID[1] == 'O') && (szID[2] == 'n' || szID[2] == 'N')))
	{
		wsprintf(szFileName, "%s\\%s\\%d\\££%s.dat", szBuff, szRecordWareHouseDir, GetUserCode(szID), szID);
		GetCharSize(szFileName, MaxSize);
		return TRUE;
	}

	wsprintf(szFileName, "%s\\%s\\%d\\%s.war", szBuff, szRecordWareHouseDir, GetUserCode(szName), szName);
	GetCharSize(szFileName, MaxSize);

	return TRUE;
}

int CreateDataServerDirectory()
{
	int cnt;
	char szBuff[256];

	CreateDirectory("DataServer", NULL);

	wsprintf(szBuff, "DataServer\\%s", szRecordUserInfoDir);
	CreateDirectory(szBuff, NULL);
	wsprintf(szBuff, "DataServer\\%s", szRecordUserDataDir);
	CreateDirectory(szBuff, NULL);
	wsprintf(szBuff, "DataServer\\%s", szRecordWareHouseDir);
	CreateDirectory(szBuff, NULL);
	wsprintf(szBuff, "DataServer\\%s", szRecordUserBackupDataDir);
	CreateDirectory(szBuff, NULL);
	wsprintf(szBuff, "DataServer\\%s", szRecordDeleteDir);
	CreateDirectory(szBuff, NULL);
	wsprintf(szBuff, "DataServer\\%s", szRecordCaravanDir);
	CreateDirectory(szBuff, NULL);
	wsprintf(szBuff, "%s", szPostBoxDir);
	CreateDirectory(szBuff, NULL);

	for (cnt = 0; cnt < 256; cnt++)
	{
		wsprintf(szBuff, "DataServer\\%s\\%d", szRecordUserInfoDir, cnt);
		CreateDirectory(szBuff, NULL);

		wsprintf(szBuff, "DataServer\\%s\\%d", szRecordUserDataDir, cnt);
		CreateDirectory(szBuff, NULL);

		wsprintf(szBuff, "DataServer\\%s\\%d", szRecordWareHouseDir, cnt);
		CreateDirectory(szBuff, NULL);

		wsprintf(szBuff, "DataServer\\%s\\%d", szRecordUserBackupDataDir, cnt);
		CreateDirectory(szBuff, NULL);

		wsprintf(szBuff, "DataServer\\%s\\%d", szRecordDeleteDir, cnt);
		CreateDirectory(szBuff, NULL);

		wsprintf(szBuff, "DataServer\\%s\\%d", szRecordCaravanDir, cnt);
		CreateDirectory(szBuff, NULL);

		wsprintf(szBuff, "%s\\%d", szPostBoxDir, cnt);
		CreateDirectory(szBuff, NULL);
	}

	return TRUE;
}

DWORD GetCharInfoCode(CharacterData *lpCharInfo)
{
	int cnt;
	int size;
	BYTE *lpCharBuff;
	DWORD	dwKey;
	DWORD	dwCode;

	size = sizeof(CharacterData);
	lpCharBuff = (BYTE *)lpCharInfo;

	dwKey = 0;

	for (cnt = 0; cnt < size; cnt++)
		dwKey += lpCharBuff[cnt];

	dwCode = 0;

	for (cnt = 0; cnt < size; cnt++)
		dwCode += (dwKey + cnt)*lpCharBuff[cnt];

	return dwCode;
}

//ÈÎÎñ»ñµÃµÄ¼¼ÄÜµã
int GetSkillPoint_LevelQuest(int Level, DWORD dwLevelQuestLog)
{
	int Point = 0;

	if (dwLevelQuestLog&QUESTBIT_LEVEL_55 && Level >= 55)
		Point++;
	if (dwLevelQuestLog&QUESTBIT_LEVEL_70 && Level >= 70)
		Point++;
	if (dwLevelQuestLog&QUESTBIT_LEVEL_80 && Level >= 80)
		Point += 2;
	return Point;
}
//ÈÎÎñ»ñµÃµÄÊôÐÔµã
int GetStatePoint_LevelQuest(int Level, DWORD dwLevelQuestLog)
{
	int Point = 0;

	if (dwLevelQuestLog&QUESTBIT_LEVEL_30 && Level >= 30)
		Point += 5;
	if (dwLevelQuestLog&QUESTBIT_LEVEL_70 && Level >= 70)
		Point += 5;
	if (dwLevelQuestLog&QUESTBIT_LEVEL_80 && Level >= 80)
		Point += 5;
	if (dwLevelQuestLog&QUESTBIT_LEVEL_80_2 && Level >= 80)
		Point += (Level - 79) * 2;
	if (dwLevelQuestLog&QUESTBIT_LEVEL_90_2 && Level >= 90)
		Point += (Level - 89) * 3;
	return Point;
}
//¼ì²â¼¼ÄÜµã
int	CheckSkillPoint(int Level, RecordSkill *lpRecordSkill, int *spTotal, DWORD dwLevelQuestLog)
{
	int cnt, mcnt;
	int	Point, EPoint;
	int SkillPoint;
	int ExtraPoint;

	Point = 0;
	EPoint = 0;

	for (cnt = 0; cnt < 12; cnt++)
	{
		if (lpRecordSkill->bSkillPoint[cnt] > 10)
			return FALSE;
		Point += abs(lpRecordSkill->bSkillPoint[cnt]);
	}

	for (cnt = 13; cnt < SIN_MAX_USE_SKILL; cnt++)
	{
		mcnt = cnt - 1;
		if (lpRecordSkill->bSkillPoint[mcnt] > 10)
			return FALSE;
		EPoint += abs(lpRecordSkill->bSkillPoint[mcnt]);
	}

	if (spTotal) *spTotal = (Point + (EPoint << 16));

	if (Level >= 10)
	{
		SkillPoint = ((Level - 8) / 2) - Point;
		SkillPoint += GetSkillPoint_LevelQuest(Level, dwLevelQuestLog);

		if (SkillPoint < 0)
			return FALSE;
	}
	else
	{
		if (Point > 0)
			return FALSE;
	}
	if (Level >= 60)
	{
		ExtraPoint = ((Level - 58) / 2) - EPoint;
		if (ExtraPoint < 0)
			return FALSE;
	}
	else
	{
		if (EPoint > 0)
			return FALSE;
	}

	return TRUE;
}
int TempNewCharacterInit[5][6] =
{
	//JobCode, Strentch, Sprit, Talent, Defence, Health
	{2,        24,       8,     25,     18,      24}, //»úÐµ
	{1,        28,       6,     21,     17,      27}, //ÎäÊ¿
	{4,        26,       9,     20,     19,      25}, //Ç¹±ø
	{3,        17,      11,     21,     27,      23},  //¹­ÊÖ
	{9,        25,      10,     22,     20,      22}  //´Ì¿Í
};

int MorNewCharacterInit[5][6] =
{
	//JobCode, Strentch, Sprit, Talent, Defence, Health
	{6,        26,       13,     17,     19,      24}, //ÓÎÏÀ
	{5,        23,       15,     19,     19,      23}, //Ä§Ç¹
	{8,        15,       28,     21,     15,      20}, //¼ÀË¾
	{7,        16,       29,     19,     14,      21},  //·¨Ê¦
	{10,       15,       27,     20,     15,      22}  //·¨Ê¦
};

int ReformCharStatePoint(CharacterData *lpCharInfo, DWORD dwLevelQuestLog, DWORD Point)
{
	int Total;
	int NewState;

	Total = abs(lpCharInfo->iStrength) +
		abs(lpCharInfo->iSpirit) +
		abs(lpCharInfo->iAgility) +
		abs(lpCharInfo->iHealth) +
		abs(lpCharInfo->iTalent) +
		abs(lpCharInfo->iStatPoints);

	NewState = 99 + ((lpCharInfo->iLevel - 1) * 5);
	NewState += GetStatePoint_LevelQuest(lpCharInfo->iLevel, dwLevelQuestLog);
	NewState += Point;

	lpCharInfo->iStatPoints += (NewState - Total);

	if (lpCharInfo->iStatPoints <= -10)
	{
		for (int i = 0; i < 5; i++)
		{
			if (lpCharInfo->iClass == TempNewCharacterInit[i][0])
			{
				lpCharInfo->iStrength = TempNewCharacterInit[i][1];
				lpCharInfo->iSpirit = TempNewCharacterInit[i][2];
				lpCharInfo->iTalent = TempNewCharacterInit[i][3];
				lpCharInfo->iAgility = TempNewCharacterInit[i][4];
				lpCharInfo->iHealth = TempNewCharacterInit[i][5];
				lpCharInfo->iStatPoints = 0;
			}
			if (lpCharInfo->iClass == MorNewCharacterInit[i][0])
			{
				lpCharInfo->iStrength = MorNewCharacterInit[i][1];
				lpCharInfo->iSpirit = MorNewCharacterInit[i][2];
				lpCharInfo->iTalent = MorNewCharacterInit[i][3];
				lpCharInfo->iAgility = MorNewCharacterInit[i][4];
				lpCharInfo->iHealth = MorNewCharacterInit[i][5];
				lpCharInfo->iStatPoints = 0;
			}
		}

		return FALSE;
	}
	if (lpCharInfo->iStatPoints < 0)
		lpCharInfo->iStatPoints = 0;

	return TRUE;
}
int Record_LastQuest(WORD wQuestCode)
{
	int cnt;

	cnt = RecordLastQuestInfo.LastQuestCount&LAST_QUEST_MASK;
	RecordLastQuestInfo.wLastQuest[cnt] = wQuestCode;
	RecordLastQuestInfo.LastQuestCount++;

	return TRUE;
}
int FindLastQuestCode(WORD wQuestCode)
{
	int cnt, mcnt, start;

	if (RecordLastQuestInfo.LastQuestCount > LAST_QUEST_MASK)
		start = RecordLastQuestInfo.LastQuestCount - LAST_QUEST_MASK;
	else
		start = 0;

	for (cnt = start; cnt < RecordLastQuestInfo.LastQuestCount; cnt++)
	{
		mcnt = cnt & LAST_QUEST_MASK;
		if (RecordLastQuestInfo.wLastQuest[mcnt] == wQuestCode)
			return TRUE;
	}
	return FALSE;
}
int CheckRecordDataItem(CharacterFile *lpRecordData)
{
	int DataSize, size;
	int ItemCount;
	int cnt;
	int SizeCount;

	BYTE *lpRecordItem;

	DataSize = lpRecordData->DataSize;
	ItemCount = lpRecordData->ItemCount;
	lpRecordItem = lpRecordData->Data;

	SizeCount = 0;

	for (cnt = 0; cnt < ItemCount; cnt++)
	{
		size = ((int *)lpRecordItem)[0];
		SizeCount += size;
		lpRecordItem += size;

		if (SizeCount > DataSize || SizeCount < 0)
			return FALSE;
	}

	if (SizeCount == DataSize)
		return TRUE;

	return FALSE;
}

int ClientRecordPotion[3][4];
int ClientRecordPotionFlag = 0;

int ResetClientRecordPotion(CharacterSave *lpGameSaveInfo)
{
	int cnt, cnt2;

	if (!lpGameSaveInfo->sPotionUpdate[0] || lpGameSaveInfo->sPotionUpdate[0] != lpGameSaveInfo->sPotionUpdate[1])
		return FALSE;

	ClientRecordPotionFlag = TRUE;

	for (cnt = 0; cnt < 3; cnt++)
	{
		for (cnt2 = 0; cnt2 < 4; cnt2++)
			ClientRecordPotion[cnt][cnt2] = lpGameSaveInfo->sPotionCount[cnt][cnt2];
	}

	return TRUE;
}

int AddRecordPotion(DWORD dwPotionCode, int PotionCount)
{
	int Count = PotionCount;
	int x = -1;
	int y = -1;

	if (ClientRecordPotionFlag == 0)
		return 0;

	switch (dwPotionCode)
	{
	case sinPL1 | sin01:
		x = 0;
		y = 0;
		break;
	case sinPL1 | sin02:
		x = 0;
		y = 1;
		break;
	case sinPL1 | sin03:
		x = 0;
		y = 2;
		break;
	case sinPL1 | sin04:
		x = 0;
		y = 3;
		break;
	case sinPM1 | sin01:
		x = 1;
		y = 0;
		break;
	case sinPM1 | sin02:
		x = 1;
		y = 1;
		break;
	case sinPM1 | sin03:
		x = 1;
		y = 2;
		break;
	case sinPM1 | sin04:
		x = 1;
		y = 3;
		break;
	case sinPS1 | sin01:
		x = 2;
		y = 0;
		break;
	case sinPS1 | sin02:
		x = 2;
		y = 1;
		break;
	case sinPS1 | sin03:
		x = 2;
		y = 2;
		break;
	case sinPS1 | sin04:
		x = 2;
		y = 3;
		break;
	}
	if (x >= 0 && y >= 0)
	{
		ClientRecordPotion[x][y] += Count;
		return ClientRecordPotion[x][y];
	}

	return 0;
}


extern int RecordHackLogMoney(CharacterData *lpCharInfo);

#define	RECORD_ITEM_INFO_HEAD_SIZE		44

int rsRECORD_DBASE::MakeRecordItemList(User *lpPlayInfo)
{
	int cnt, cnt2;

	BYTE	*lpRecItem;
	sRECORD_ITEM	sRecordItem;
	int		size;
	int		BuffSize;
	smTRANS_COMMAND_EX	smTransCommand;

	DropItemData	ThrowItemInfo[THROW_ITEM_INFO_MAX];
	int				ThrowItemCount;

	lpRecItem = (BYTE *)&TransRecordData.Data;
	BuffSize = 0;
	ThrowItemCount = 0;

	ZeroMemory(lpPlayInfo->ServerPotion, sizeof(int) * 3 * 4);

	if (TransRecordData.ItemCount > RECORD_ITEM_MAX)
		TransRecordData.ItemCount = RECORD_ITEM_MAX;

	if (TransRecordData.ThrowItemCount > THROW_ITEM_INFO_MAX)
		TransRecordData.ThrowItemCount = THROW_ITEM_INFO_MAX;

	for (cnt = 0; cnt < TransRecordData.ItemCount; cnt++)
	{
		if (cnt >= (INVENTORY_MAXITEM * 2))
			break;

		DecodeCompress_ItemPotion(lpPlayInfo, (BYTE *)lpRecItem, (BYTE *)&sRecordItem, RECORD_ITEM_INFO_HEAD_SIZE, &TransRecordData);

		if (sRecordItem.sItemInfo.sItemID.ToInt() &&
			sRecordItem.sItemInfo.iChk1 &&
			sRecordItem.sItemInfo.iChk2 &&
			sRecordItem.sItemInfo.sItemID.ToItemBase() != ITEMBASE_Potion)
		{
			for (cnt2 = 0; cnt2 < TransRecordData.ThrowItemCount; cnt2++)
			{
				if (TransRecordData.ThrowItemInfo[cnt2].dwCode == sRecordItem.sItemInfo.sItemID.ToInt() &&
					TransRecordData.ThrowItemInfo[cnt2].dwKey == sRecordItem.sItemInfo.iChk1 &&
					TransRecordData.ThrowItemInfo[cnt2].dwSum == sRecordItem.sItemInfo.iChk2)
				{
					if (ThrowItemCount < THROW_ITEM_INFO_MAX)
						memcpy(&ThrowItemInfo[ThrowItemCount++], &TransRecordData.ThrowItemInfo[cnt2], sizeof(DropItemData));
					break;
				}
			}

			if (cnt2 >= TransRecordData.ThrowItemCount)
			{
				for (cnt2 = 0; cnt2 < cnt; cnt2++)
				{
					if (lpPlayInfo->InvenItemInfo[cnt2].dwCode &&
						lpPlayInfo->InvenItemInfo[cnt2].dwCode == sRecordItem.sItemInfo.sItemID.ToInt() &&
						lpPlayInfo->InvenItemInfo[cnt2].dwKey == sRecordItem.sItemInfo.iChk1 &&
						lpPlayInfo->InvenItemInfo[cnt2].dwSum == sRecordItem.sItemInfo.iChk2)
					{
						smTransCommand.WParam = 8070;
						smTransCommand.WxParam = 1;
						smTransCommand.LxParam = (int)"*INVENTORY";
						smTransCommand.LParam = sRecordItem.sItemInfo.sItemID.ToInt();
						smTransCommand.SParam = sRecordItem.sItemInfo.iChk1;
						smTransCommand.EParam = sRecordItem.sItemInfo.iChk2;
						RecordHackLogFile(lpPlayInfo, &smTransCommand);
						break;
					}
				}
				if (cnt2 >= cnt)
				{
					lpPlayInfo->InvenItemInfo[cnt].dwCode = sRecordItem.sItemInfo.sItemID.ToInt();
					lpPlayInfo->InvenItemInfo[cnt].dwKey = sRecordItem.sItemInfo.iChk1;
					lpPlayInfo->InvenItemInfo[cnt].dwSum = sRecordItem.sItemInfo.iChk2;
				}
			}
		}

		size = ((int *)lpRecItem)[0];
		BuffSize += size;
		lpRecItem += size;
		if (BuffSize >= (sizeof(sRECORD_ITEM)*RECORD_ITEM_MAX))
			break;
	}

	lpPlayInfo->ThrowItemCount = ThrowItemCount;
	memcpy(lpPlayInfo->ThrowItemInfo, ThrowItemInfo, sizeof(DropItemData)*ThrowItemCount);

	return TRUE;
}

#ifdef _W_SERVER
int	CheckPlayExpTable[15] =
{
	40000,			//0
	100000,			//1
	300000,			//2
	500000,			//3
	800000,			//4
	1200000,		//5
	1600000,		//6
	2000000,		//7
	3000000,		//8
	4000000,		//9
	4000000,		//10
	6000000,		//11
	6000000,		//12
	8000000,		//13
	8000000			//14
};
#else
int	CheckPlayExpTable[15] =
{
	0,		//0
	0,		//1
	0,		//2
	0,		//3
	0,		//4
	0,		//5
	0,		//6
	0,		//7
	0,		//8
	0,		//9
	0,		//10
	0,		//11
	0,		//12
	0,		//13
	0		//14
};
#endif


int RecordDeleteCharacterError(char *szID, char *szName);

int rsRECORD_DBASE::SendUserDataToClient(char *szID, User *pcUser, char *szServerID)
{
	char	szFile[256];
	char	szFile2[256];
	char	szFileInfo[256];
	WIN32_FIND_DATA		ffd;
	HANDLE				hFind;
	sPLAY_USER_DATA		sPlayUserData;
	TRANS_USERCHAR_INFO	TransUserCharInfo;
	_TRANS_CHAR_INFO	*lpCharInfo;
	FILE	*fp;
	int		cnt;
	int		FindCnt;
	int		DeleteCnt;
	int		LevelMax = 0;
	int		CharNameMax = CHAR_NAME_MAXLEN;

	if (rsServerConfig.TT_DataServer_Count)
		CharNameMax = CHAR_NAME_MAXLEN + 6;

	GetUserInfoFile(szID, szFileInfo, sizeof(szFileInfo));

	lstrcpy(LastAcessID, szID);

	hFind = FindFirstFile(szFileInfo, &ffd);
	FindClose(hFind);

	if (hFind == INVALID_HANDLE_VALUE)
	{
		ZeroMemory(&sPlayUserData, sizeof(sPLAY_USER_DATA));
		lstrcpy(sPlayUserData.szID, szID);
		lstrcpy(sPlayUserData.szHeader, "PS_TAILID 1.10");

		fopen_s(&fp, szFileInfo, "wb");
		if (!fp)
			return FALSE;
		fwrite(&sPlayUserData, sizeof(sPLAY_USER_DATA), 1, fp);
		fclose(fp);
	}
	else
	{
		ZeroMemory(&sPlayUserData, sizeof(sPLAY_USER_DATA));

		fopen_s(&fp, szFileInfo, "rb");
		if (!fp)
			return FALSE;
		fread(&sPlayUserData, sizeof(sPLAY_USER_DATA), 1, fp);
		fclose(fp);

		if (lstrcmpi(sPlayUserData.szID, szID) != 0)
		{
			ZeroMemory(&sPlayUserData, sizeof(sPLAY_USER_DATA));
			lstrcpy(sPlayUserData.szID, szID);
			lstrcpy(sPlayUserData.szHeader, "PS_TAILID 1.10");

			fopen_s(&fp, szFileInfo, "wb");
			if (!fp)
				return FALSE;
			fwrite(&sPlayUserData, sizeof(sPLAY_USER_DATA), 1, fp);
			fclose(fp);
		}
	}

	TransUserCharInfo.code = smTRANSCODE_ID_SETUSERINFO;
	TransUserCharInfo.size = sizeof(TRANS_USERCHAR_INFO);
	lstrcpy(TransUserCharInfo.szID, szID);

	FindCnt = 0;
	DeleteCnt = 0;

	for (cnt = 0; cnt < sPLAY_CHAR_MAX; cnt++)
	{
		if (sPlayUserData.szCharName[cnt][0])
		{
			GetUserDataFile(sPlayUserData.szCharName[cnt], szFile, sizeof(szFile));
			ZeroMemory(&TransRecordData, sizeof(CharacterFile));

			fopen_s(&fp, szFile, "rb");
			if (fp)
			{
				fread(&TransRecordData, sizeof(CharacterFile), 1, fp);
				fclose(fp);

				if (lstrcmpi(TransRecordData.sCharInfo.szName, sPlayUserData.szCharName[cnt]) == 0 && lstrlen(sPlayUserData.szCharName[cnt]) < CharNameMax)
				{
					lpCharInfo = (_TRANS_CHAR_INFO *)&TransUserCharInfo.CharInfo[FindCnt];

					lstrcpy(lpCharInfo->szName, TransRecordData.sCharInfo.szName);
					lstrcpy(lpCharInfo->szModelName, TransRecordData.sCharInfo.Player.szBodyModel);
					lstrcpy(lpCharInfo->szModelName2, TransRecordData.sCharInfo.Player.szHeadModel);

					lpCharInfo->Brood = TransRecordData.sCharInfo.iMonsterType;
					lpCharInfo->dwArmorCode = 0;
					lpCharInfo->JOB_CODE = TransRecordData.sCharInfo.iClass;
					lpCharInfo->Level = TransRecordData.sCharInfo.iLevel;

					if (rsServerConfig.FixedStartField)
						lpCharInfo->StartField = rsServerConfig.FixedStartField;
					else
						lpCharInfo->StartField = TransRecordData.GameSaveInfo.iMapID;

					if (lpCharInfo->StartField == rsSOD_FIELD)
						lpCharInfo->StartField = rsSOD_VILLAGE;

					if (lpCharInfo->StartField == QUEST_ARENA_FIELD)
					{
						if (GetRace(lpCharInfo->JOB_CODE) == BROOD_CODE_TEMPSKRON)
							lpCharInfo->StartField = MAPID_RicartenTown;
						else
							lpCharInfo->StartField = MAPID_PhillaiTown;
					}
					if (lpCharInfo->StartField == rsACTION_FIELD)
						lpCharInfo->StartField = MAPID_RicartenTown;

					lpCharInfo->PosX = TransRecordData.GameSaveInfo.iCameraPositionX;
					lpCharInfo->PosZ = TransRecordData.GameSaveInfo.iCameraPositionZ;

					if (LevelMax < lpCharInfo->Level)
						LevelMax = lpCharInfo->Level;

					FindCnt++;
				}
				else
				{
					if (TransRecordData.iLength)
					{
						GetDeleteDataFile(sPlayUserData.szCharName[cnt], szFile2, sizeof(szFile2));
						CopyFile(szFile, szFile2, FALSE);
						RecordDeleteCharacterError(szID, szFile);
					}

					DeleteFile(szFile);

					sPlayUserData.szCharName[cnt][0] = 0;
					DeleteCnt++;
				}
			}
			else
			{
				sPlayUserData.szCharName[cnt][0] = 0;
				DeleteCnt++;
			}
		}
	}

	if (FindCnt > 5)
		FindCnt = 5;

	TransUserCharInfo.PlayUserCount = FindCnt;

	SENDPACKET(pcUser, &TransUserCharInfo);

	if (DeleteCnt)
	{
		fopen_s(&fp, szFileInfo, "wb");
		if (fp)
		{
			fwrite(&sPlayUserData, sizeof(sPLAY_USER_DATA), 1, fp);
			fclose(fp);
		}
	}

	return LevelMax;
}

int rsRECORD_DBASE::InsertCharData(char *szID, char *szName, int Mode)
{
	char	szFile[256];
	sPLAY_USER_DATA		sPlayUserData;
	FILE	*fp;
	int		cnt;

	if (!Mode && IsData(szName) == TRUE)
		return FALSE;

	GetUserInfoFile(szID, szFile, sizeof(szFile));

	fopen_s(&fp, szFile, "rb");
	if (!fp)
		return FALSE;

	fread(&sPlayUserData, sizeof(sPLAY_USER_DATA), 1, fp);
	fclose(fp);

	for (cnt = 0; cnt < sPLAY_CHAR_MAX; cnt++)
	{
		if (!sPlayUserData.szCharName[cnt][0])
		{
			lstrcpy(sPlayUserData.szCharName[cnt], szName);
			fopen_s(&fp, szFile, "wb");
			if (fp)
			{
				fwrite(&sPlayUserData, sizeof(sPLAY_USER_DATA), 1, fp);
				fclose(fp);
			}

			if (!Mode)
			{
				GetUserDataFile(sPlayUserData.szCharName[cnt], szFile, sizeof(szFile));
				ZeroMemory(&TransRecordData, sizeof(CharacterFile));

				fopen_s(&fp, szFile, "wb");
				if (fp)
				{
					fwrite(&TransRecordData, srRECORD_MEMORY_SIZE, 1, fp);
					fclose(fp);
				}
			}
			return TRUE;
		}
	}

	return FALSE;
}

int rsRECORD_DBASE::DeleteCharData(char *szID, char *szName)
{
	char szFile[256];
	char szDelFile[256];
	char szDelBackupFile[256];
	FILE	*fp;
	int		cnt;
	sPLAY_USER_DATA		sPlayUserData;

	GetUserDataFile(szName, szDelFile, sizeof(szDelFile));

	fopen_s(&fp, szDelFile, "rb");
	if (fp)
	{
		fread(&TransRecordData, sizeof(CharacterFile), 1, fp);
		fclose(fp);
	}

	GetUserInfoFile(szID, szFile, sizeof(szFile));

	fopen_s(&fp, szFile, "rb");
	if (!fp)
		return FALSE;

	fread(&sPlayUserData, sizeof(sPLAY_USER_DATA), 1, fp);
	fclose(fp);

	for (cnt = 0; cnt < sPLAY_CHAR_MAX; cnt++)
	{
		if (sPlayUserData.szCharName[cnt][0] && lstrcmpi(sPlayUserData.szCharName[cnt], szName) == 0)
		{
			sPlayUserData.szCharName[cnt][0] = 0;

			fopen_s(&fp, szFile, "wb");
			if (fp)
			{
				fwrite(&sPlayUserData, sizeof(sPLAY_USER_DATA), 1, fp);
				fclose(fp);
				if (TransRecordData.sCharInfo.iLevel >= 10)
				{
					GetDeleteDataFile(szName, szDelBackupFile, sizeof(szDelBackupFile));
					if (TransRecordData.sCharInfo.iLevel >= 20)
						CopyFile(szDelFile, szDelBackupFile, TRUE);
					else
						CopyFile(szDelFile, szDelBackupFile, FALSE);
				}

				DeleteFile(szDelFile);
			}
			return TRUE;
		}
	}

	return TRUE;
}

int rsRECORD_DBASE::IsData(char *szName)
{
	char	szFile[256];
	WIN32_FIND_DATA		ffd;
	HANDLE				hFind;

	if (lstrlen(szName) >= CHAR_NAME_MAXLEN)
		return TRUE;

	GetUserDataFile(szName, szFile, sizeof(szFile));

	hFind = FindFirstFile(szFile, &ffd);
	FindClose(hFind);
	if (hFind != INVALID_HANDLE_VALUE)
		return TRUE;

	return FALSE;
}

int rsRECORD_DBASE::SaveThrowData(char *szName, DropItemData *lpThrowItemList, int Count, int SaveMoney)
{
	char szFile[256];
	FILE	*fp;

	if (!szName[0])
		return FALSE;

	GetUserDataFile(szName, szFile, sizeof(szFile));

	fopen_s(&fp, szFile, "rb");
	if (!fp)
		return FALSE;

	fread(&TransRecordData, sizeof(CharacterFile), 1, fp);
	fclose(fp);

	memcpy(&TransRecordData.ThrowItemInfo, lpThrowItemList, sizeof(DropItemData)*Count);
	TransRecordData.ThrowItemCount = Count;

	if (SaveMoney >= 0 && TransRecordData.sCharInfo.iGold > SaveMoney)
		TransRecordData.GameSaveInfo.iLastGold = SaveMoney + 1;


	fopen_s(&fp, szFile, "wb");
	if (!fp)
		return FALSE;

	fwrite(&TransRecordData, sizeof(CharacterFile), 1, fp);
	fclose(fp);

	return TRUE;
}

//±£´æ²Ö¿âÊý¾Ý
int rsSaveWareHouseData(User *lpPlayInfo, TRANS_WAREHOUSE *lpTransWareHouse)
{
	char szFileName[128];
	FILE	*fp;

	GetWareHouseFile(lpPlayInfo->szAccountName, szFileName, sizeof(szFileName));

	fopen_s(&fp, szFileName, "wb");

	if (fp)
	{
		lpTransWareHouse->WareHouseMoney = lpPlayInfo->WareHouseMoney;

		fwrite(lpTransWareHouse, lpTransWareHouse->size, 1, fp);
		fclose(fp);
		return TRUE;
	}

	return FALSE;
}
// ¼ÓÔØ²Ö¿âÊý¾Ý
int rsLoadWareHouseData(User *lpPlayInfo)
{
	char szFileName[128];
	TRANS_WAREHOUSE TransWareHouse;
	sWAREHOUSE	WareHouseCheck;
	FILE	*fp;
	smTRANS_COMMAND_EX	smTransCommand;
	int	CopiedItemFlag;

	WIN32_FIND_DATA		ffd;
	HANDLE				hFind;
	int	Money;
	int cnt, cnt2;

	GetWareHouseFile(lpPlayInfo->szAccountName, szFileName, sizeof(szFileName));

	hFind = FindFirstFile(szFileName, &ffd);
	FindClose(hFind);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		fopen_s(&fp, szFileName, "rb");
		if (fp)
		{
			fread(&TransWareHouse, sizeof(TRANS_WAREHOUSE), 1, fp);
			fclose(fp);
		}
	}
	else
	{
		TransWareHouse.code = smTRANSCODE_WAREHOUSE;
		TransWareHouse.size = sizeof(TRANS_WAREHOUSE) - sizeof(sWAREHOUSE);
		TransWareHouse.DataSize = 0;
		TransWareHouse.dwChkSum = 0;
		TransWareHouse.wVersion[0] = Version_WareHouse;
		TransWareHouse.wVersion[1] = 0;
		TransWareHouse.WareHouseMoney = 0;
		TransWareHouse.dwTemp[0] = 0;
		TransWareHouse.dwTemp[1] = 0;
		TransWareHouse.dwTemp[2] = 0;
		TransWareHouse.dwTemp[3] = 0;
		TransWareHouse.dwTemp[4] = 0;
	}

	if (TransWareHouse.size >= 8192)
		TransWareHouse.size = 8192;

	Money = TransWareHouse.WareHouseMoney;
	lpPlayInfo->WareHouseMoney = Money;

	CopiedItemFlag = 0;

	if (!lpPlayInfo->bWarehouseOpen)
	{
		lpPlayInfo->bWarehouseOpen = TRUE;

		ZeroMemory(lpPlayInfo->WareHouseItemInfo, sizeof(DropItemData) * 100);

		if (TransWareHouse.DataSize)
		{
			DecodeCompress((BYTE *)TransWareHouse.Data, (BYTE *)&WareHouseCheck, sizeof(sWAREHOUSE));

			DWORD	dwChkSum = 0;
			char	*szComp = (char *)&WareHouseCheck;

			for (cnt = 0; cnt < sizeof(sWAREHOUSE); cnt++)
				dwChkSum += szComp[cnt] * (cnt + 1);

			if (dwChkSum != TransWareHouse.dwChkSum)
			{
				lpPlayInfo->bWarehouseOpen = FALSE;
				lpPlayInfo->dwDataError |= rsDATA_ERROR_WAREHOUSE;
				return 0;
			}
			for (cnt = 0; cnt < 100; cnt++)
			{
				if (WareHouseCheck.WareHouseItem[cnt].bValid)
				{
					for (cnt2 = 0; cnt2 < INVEN_ITEM_INFO_MAX; cnt2++)
					{
						if (lpPlayInfo->InvenItemInfo[cnt2].dwCode && lpPlayInfo->InvenItemInfo[cnt2].dwCode == WareHouseCheck.WareHouseItem[cnt].sItem.sItemID.ToInt() && lpPlayInfo->InvenItemInfo[cnt2].dwKey == WareHouseCheck.WareHouseItem[cnt].sItem.iChk1 && lpPlayInfo->InvenItemInfo[cnt2].dwSum == WareHouseCheck.WareHouseItem[cnt].sItem.iChk2)
						{
							smTransCommand.WParam = 8070;
							smTransCommand.WxParam = 2;
							smTransCommand.LxParam = (int)"*WAREHOUSE";
							smTransCommand.LParam = WareHouseCheck.WareHouseItem[cnt].sItem.sItemID.ToInt();
							smTransCommand.SParam = WareHouseCheck.WareHouseItem[cnt].sItem.iChk1;
							smTransCommand.EParam = WareHouseCheck.WareHouseItem[cnt].sItem.iChk2;
							RecordHackLogFile(lpPlayInfo, &smTransCommand);
							CopiedItemFlag++;
							break;
						}
					}
					if (cnt2 >= INVEN_ITEM_INFO_MAX)
					{
						lpPlayInfo->WareHouseItemInfo[cnt].dwCode = WareHouseCheck.WareHouseItem[cnt].sItem.sItemID.ToInt();
						lpPlayInfo->WareHouseItemInfo[cnt].dwKey = WareHouseCheck.WareHouseItem[cnt].sItem.iChk1;
						lpPlayInfo->WareHouseItemInfo[cnt].dwSum = WareHouseCheck.WareHouseItem[cnt].sItem.iChk2;
					}
				}
			}
		}
	}

	if (!CopiedItemFlag)
	{
		SENDPACKET(lpPlayInfo, &TransWareHouse);
	}

	return TRUE;
}
int rsLoadWareHouseData_Admin(User *lpPlayInfo, char *szID, int Day)
{
	char szFileName[128];
	TRANS_WAREHOUSE TransWareHouse;
	FILE	*fp;

	WIN32_FIND_DATA		ffd;
	HANDLE				hFind;

	if (Day == 0)
		GetWareHouseFile(szID, szFileName, sizeof(szFileName));
	else
		GetWareHouseFile_Backup(szID, szFileName, Day, sizeof(szFileName));

	hFind = FindFirstFile(szFileName, &ffd);
	FindClose(hFind);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		fopen_s(&fp, szFileName, "rb");
		if (fp)
		{
			fread(&TransWareHouse, sizeof(TRANS_WAREHOUSE), 1, fp);
			fclose(fp);
		}
	}
	else
		return FALSE;

	if (TransWareHouse.size >= 8192)
		TransWareHouse.size = 8192;

	lpPlayInfo->bWarehouseOpen = FALSE;

	SENDPACKET(lpPlayInfo, &TransWareHouse);

	return TRUE;
}
// ¼ÓÔØ³èÎï²Ö¿â
int rsLoadCaravanData(User *lpPlayInfo)
{
	char szFileName[128];
	TRANS_CARAVAN	TransCaravan;
	sCARAVAN		CaranvanCheck;

	FILE *fp;
	HANDLE	hFind;
	WIN32_FIND_DATA ffd;
	int cnt, cnt2;
	smTRANS_COMMAND_EX	smTransCommand;

	GetCaravanFile(lpPlayInfo->szCharacterName, szFileName, sizeof(szFileName));

	hFind = FindFirstFile(szFileName, &ffd);
	FindClose(hFind);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		fopen_s(&fp, szFileName, "rb");
		if (fp)
		{
			fread(&TransCaravan, sizeof(TRANS_CARAVAN), 1, fp);
			fclose(fp);
		}
	}
	else
	{
		TransCaravan.code = smTRANSCODE_CARAVAN;
		TransCaravan.size = sizeof(TRANS_CARAVAN) - sizeof(sCARAVAN);
		TransCaravan.DataSize = 0;
		TransCaravan.dwChkSum = 0;
		TransCaravan.wVersion[0] = Version_Caravan;
		TransCaravan.wVersion[1] = 0;
	}

	if (TransCaravan.size >= 8192)
		TransCaravan.size = 8192;

	int CopiedItemFlag = 0;

	if (!lpPlayInfo->OpenCaravanInfoFlag)
	{
		lpPlayInfo->OpenCaravanInfoFlag = TRUE;

		ZeroMemory(lpPlayInfo->CaravanItemInfo, sizeof(DropItemData) * 100);

		if (TransCaravan.DataSize)
		{
			DecodeCompress((BYTE *)TransCaravan.Data, (BYTE *)&CaranvanCheck, sizeof(sCARAVAN));

			DWORD	dwChkSum = 0;
			char	*szComp = (char *)&CaranvanCheck;

			for (cnt = 0; cnt < sizeof(sCARAVAN); cnt++)
				dwChkSum += szComp[cnt] * (cnt + 1);

			if (dwChkSum != TransCaravan.dwChkSum)
			{
				lpPlayInfo->OpenCaravanInfoFlag = FALSE;
				lpPlayInfo->dwDataError |= rsDATA_ERROR_CARAVAN;
				return FALSE;
			}
			for (cnt = 0; cnt < 100; cnt++)
			{
				if (CaranvanCheck.Item[cnt].bValid)
				{
					for (cnt2 = 0; cnt2 < INVEN_ITEM_INFO_MAX; cnt2++)
					{
						if (lpPlayInfo->InvenItemInfo[cnt2].dwCode && lpPlayInfo->InvenItemInfo[cnt2].dwCode == CaranvanCheck.Item[cnt].sItem.sItemID.ToInt() && lpPlayInfo->InvenItemInfo[cnt2].dwKey == CaranvanCheck.Item[cnt].sItem.iChk1 && lpPlayInfo->InvenItemInfo[cnt2].dwSum == CaranvanCheck.Item[cnt].sItem.iChk2)
						{
							smTransCommand.WParam = 8070;
							smTransCommand.WxParam = 4;
							smTransCommand.LxParam = (int)"*CARAVAN";
							smTransCommand.LParam = CaranvanCheck.Item[cnt].sItem.sItemID.ToInt();
							smTransCommand.SParam = CaranvanCheck.Item[cnt].sItem.iChk1;
							smTransCommand.EParam = CaranvanCheck.Item[cnt].sItem.iChk2;
							RecordHackLogFile(lpPlayInfo, &smTransCommand);
							CopiedItemFlag++;
							break;
						}
					}
					if (cnt2 >= INVEN_ITEM_INFO_MAX)
					{
						lpPlayInfo->CaravanItemInfo[cnt].dwCode = CaranvanCheck.Item[cnt].sItem.sItemID.ToInt();
						lpPlayInfo->CaravanItemInfo[cnt].dwKey = CaranvanCheck.Item[cnt].sItem.iChk1;
						lpPlayInfo->CaravanItemInfo[cnt].dwSum = CaranvanCheck.Item[cnt].sItem.iChk2;
					}
				}
			}
		}
	}
	if (!CopiedItemFlag)
	{
		SENDPACKET(lpPlayInfo, &TransCaravan);
	}

	return TRUE;
}
// ±£´æ³èÎï²Ö¿âÊý¾Ý
int rsSaveCaravanData(char *szName, TRANS_CARAVAN *lpTransCaravan)
{
	char szFileName[128];
	FILE	*fp;

	GetCaravanFile(szName, szFileName, sizeof(szFileName));
	fopen_s(&fp, szFileName, "wb");
	if (fp)
	{
		fwrite(lpTransCaravan, lpTransCaravan->size, 1, fp);
		fclose(fp);
	}
	return TRUE;
}
int rsCheckAccountChar(char *szID, char *szName)
{
	char	szFileInfo[128];
	sPLAY_USER_DATA		sPlayUserData;
	FILE	*fp;
	int		cnt;

	GetUserInfoFile(szID, szFileInfo, sizeof(szFileInfo));

	ZeroMemory(&sPlayUserData, sizeof(sPLAY_USER_DATA));

	fopen_s(&fp, szFileInfo, "rb");
	if (!fp)
		return FALSE;
	fread(&sPlayUserData, sizeof(sPLAY_USER_DATA), 1, fp);
	fclose(fp);

	if (lstrcmpi(sPlayUserData.szID, szID) != 0)
		return FALSE;

	for (cnt = 0; cnt < sPLAY_CHAR_MAX; cnt++)
	{
		if (sPlayUserData.szCharName[cnt][0])
		{
			if (lstrcmpi(sPlayUserData.szCharName[cnt], szName) == 0)
				return TRUE;
		}
	}

	return FALSE;
}
// ¼ÓÔØbiÎïÆ·
int rsLoadServerForce(User *lpPlayInfo, CharacterSave *lpGameSaveInfo)
{
	int cnt;
	int cnt2;

	if (lpGameSaveInfo->wForceOrbUsing[0] && lpGameSaveInfo->wForceOrbUsing[1])
	{
		cnt = lpGameSaveInfo->wForceOrbUsing[0] >> 8;

		cnt--;
		if (cnt >= 0 && cnt < 16)
		{
			if (lpGameSaveInfo->wForceOrbUsing[1] <= ForceOrbUseTime[cnt])
			{
				lpPlayInfo->dwForceOrb_SaveCode = sinFO1 + lpGameSaveInfo->wForceOrbUsing[0];
				lpPlayInfo->dwForceOrb_SaveTime = SERVER_GAMETIME + lpGameSaveInfo->wForceOrbUsing[1] * 1000;
				lpPlayInfo->dwForceOrb_SaveDamage = ForceOrbDamage[cnt];
			}
		}
	}
	if (lpGameSaveInfo->wLifeBoosterUsing[0] && lpGameSaveInfo->wLifeBoosterUsing[1])
	{
		cnt2 = lpGameSaveInfo->wLifeBoosterUsing[0] >> 8;
		cnt2 -= 21;
		if (lpGameSaveInfo->wLifeBoosterUsing[1] <= BoosterItem_UseTime[cnt2] / 60)
		{
			lpPlayInfo->dwLifeBooster_SaveCode = sinBC1 + lpGameSaveInfo->wLifeBoosterUsing[0];
			lpPlayInfo->dwLifeBooster_SaveTime = SERVER_GAMETIME + lpGameSaveInfo->wLifeBoosterUsing[1] * 60 * 1000;
			lpPlayInfo->dwLifeBooster_SaveData = BoosterItem_DataPercent[0];
		}
	}
	if (lpGameSaveInfo->wManaBoosterUsing[0] && lpGameSaveInfo->wManaBoosterUsing[1])
	{
		cnt2 = lpGameSaveInfo->wManaBoosterUsing[0] >> 8;
		if (lpGameSaveInfo->wManaBoosterUsing[0] >= sin26)
			cnt2 -= 16;
		cnt2 -= 24;
		if (lpGameSaveInfo->wManaBoosterUsing[1] <= BoosterItem_UseTime[cnt2] / 60)
		{
			lpPlayInfo->dwManaBooster_SaveCode = sinBC1 + lpGameSaveInfo->wManaBoosterUsing[0];
			lpPlayInfo->dwManaBooster_SaveTime = SERVER_GAMETIME + lpGameSaveInfo->wManaBoosterUsing[1] * 60 * 1000;
			lpPlayInfo->dwManaBooster_SaveData = BoosterItem_DataPercent[1];
		}
	}
	if (lpGameSaveInfo->wStaminaBoosterUsing[0] && lpGameSaveInfo->wStaminaBoosterUsing[1])
	{
		cnt2 = lpGameSaveInfo->wStaminaBoosterUsing[0] >> 8;
		if (lpGameSaveInfo->wStaminaBoosterUsing[0] >= sin26)
			cnt2 -= 16;
		cnt2 -= 27;
		if (lpGameSaveInfo->wStaminaBoosterUsing[1] <= BoosterItem_UseTime[cnt2] / 60)
		{
			lpPlayInfo->dwStaminaBooster_SaveCode = sinBC1 + lpGameSaveInfo->wStaminaBoosterUsing[0];
			lpPlayInfo->dwStaminaBooster_SaveTime = SERVER_GAMETIME + lpGameSaveInfo->wStaminaBoosterUsing[1] * 60 * 1000;
			lpPlayInfo->dwStaminaBooster_SaveData = BoosterItem_DataPercent[2];
		}
	}

	if (lpGameSaveInfo->wSkillDelayUsing[0] && lpGameSaveInfo->wSkillDelayUsing[1])
	{
		cnt2 = lpGameSaveInfo->wSkillDelayUsing[0] >> 8;
		if (lpGameSaveInfo->wSkillDelayUsing[0] >= sin26)
			cnt2 -= 16;

		cnt2 -= 27;
		if (lpGameSaveInfo->wSkillDelayUsing[1] <= nSkillDelay_UseTime[cnt2 - 3] / 60)
		{
			lpPlayInfo->dwSkillDelay_SaveCode = sinBC1 + lpGameSaveInfo->wSkillDelayUsing[0];
			lpPlayInfo->dwSkillDelay_SaveTime = SERVER_GAMETIME + lpGameSaveInfo->wSkillDelayUsing[1] * 60 * 1000;
		}
	}

	if (lpGameSaveInfo->dwTime_PrimeItem_X2)
		lpPlayInfo->dwTime_PrimeItem_X2 = lpGameSaveInfo->dwTime_PrimeItem_X2 + (DWORD)SERVER_LOCATIME;

	if (lpGameSaveInfo->dwTime_PrimeItem_ExpUp)
		lpPlayInfo->dwTime_PrimeItem_ExpUp = lpGameSaveInfo->dwTime_PrimeItem_ExpUp + (DWORD)SERVER_LOCATIME;

	if (lpPlayInfo->dwTime_PrimeItem_X2 || lpGameSaveInfo->dwTime_PrimeItem_ExpUp)
		lpPlayInfo->dwPrimeItem_PackageCode = lpGameSaveInfo->dwPrimeItem_PackageCode;

	if (lpGameSaveInfo->dwTime_PrimeItem_VampCuspid)
		lpPlayInfo->dwTime_PrimeItem_VampCuspid = lpGameSaveInfo->dwTime_PrimeItem_VampCuspid + (DWORD)SERVER_LOCATIME;

	if (lpGameSaveInfo->dwTime_PrimeItem_VampCuspid_EX)
		lpPlayInfo->dwTime_PrimeItem_VampCuspid_EX = lpGameSaveInfo->dwTime_PrimeItem_VampCuspid_EX + (DWORD)SERVER_LOCATIME;

	if (lpGameSaveInfo->dwTime_PrimeItem_ManaRecharg)
		lpPlayInfo->dwTime_PrimeItem_ManaRecharg = lpGameSaveInfo->dwTime_PrimeItem_ManaRecharg + (DWORD)SERVER_LOCATIME;

	if (lpGameSaveInfo->dwTime_PrimeItem_ManaReduce)
		lpPlayInfo->dwTime_PrimeItem_ManaReduce = lpGameSaveInfo->dwTime_PrimeItem_ManaReduce + (DWORD)SERVER_LOCATIME;

	if (lpGameSaveInfo->dwTime_PrimeItem_MightofAwell)
		lpPlayInfo->dwTime_PrimeItem_MightofAwell = lpGameSaveInfo->dwTime_PrimeItem_MightofAwell + (DWORD)SERVER_LOCATIME;

	if (lpGameSaveInfo->dwTime_PrimeItem_MightofAwell2)
		lpPlayInfo->dwTime_PrimeItem_MightofAwell2 = lpGameSaveInfo->dwTime_PrimeItem_MightofAwell2 + (DWORD)SERVER_LOCATIME;

	if (lpGameSaveInfo->dwTime_PrimeItem_HelpPet)
		lpPlayInfo->dwTime_PrimeItem_HelpPet = lpGameSaveInfo->dwTime_PrimeItem_HelpPet + (DWORD)SERVER_LOCATIME;

	if (lpGameSaveInfo->dwTime_PrimeItem_StaminaReduce)
		lpPlayInfo->dwTime_PrimeItem_StaminaReduce = lpGameSaveInfo->dwTime_PrimeItem_StaminaReduce + (DWORD)SERVER_LOCATIME;

	if (lpGameSaveInfo->dwTime_CaravanHopy)
	{
		lpPlayInfo->dwCaravan_Hopy_Time = lpGameSaveInfo->dwTime_CaravanHopy + (DWORD)SERVER_LOCATIME;
		lpPlayInfo->dwCaravan_Param = lpGameSaveInfo->dwCaravanParam;
	}
	if (lpGameSaveInfo->dwTime_PrimeItem_PhenixPet)
	{
		lpPlayInfo->dwTime_PhenixPet = lpGameSaveInfo->dwTime_PrimeItem_PhenixPet + (DWORD)SERVER_LOCATIME;
		lpPlayInfo->PhenixPetType = lpGameSaveInfo->dwPhoenix;
	}
	if (lpGameSaveInfo->dwTime_PrimeItem_BigHead)
	{
		lpPlayInfo->dwTime_BigHead = lpGameSaveInfo->dwTime_PrimeItem_BigHead + (DWORD)SERVER_LOCATIME;
		lpPlayInfo->BigHeadType = lpGameSaveInfo->dwPrimeItem_BigHead;
	}

	return TRUE;

}
// ±£´æbiÎïÆ·
int rsSaveServerForce(User *lpPlayInfo, CharacterSave *lpGameSaveInfo)
{
	int sec;
	int LifeBooster_sec;
	int ManaBooster_sec;
	int StaminaBooster_sec;
	int nSkillDelay_sec;

	sec = (lpPlayInfo->dwForceOrb_SaveTime - SERVER_GAMETIME) / 1000;

	LifeBooster_sec = (lpPlayInfo->dwLifeBooster_SaveTime - SERVER_GAMETIME) / 1000 / 60;
	ManaBooster_sec = (lpPlayInfo->dwManaBooster_SaveTime - SERVER_GAMETIME) / 1000 / 60;
	StaminaBooster_sec = (lpPlayInfo->dwStaminaBooster_SaveTime - SERVER_GAMETIME) / 1000 / 60;
	nSkillDelay_sec = (lpPlayInfo->dwSkillDelay_SaveTime - SERVER_GAMETIME) / 1000 / 60;

	if (lpPlayInfo->dwForceOrb_SaveTime && lpPlayInfo->dwForceOrb_SaveTime > SERVER_GAMETIME)
	{
		lpGameSaveInfo->wForceOrbUsing[0] = (WORD)(lpPlayInfo->dwForceOrb_SaveCode&sinITEM_MASK3);
		lpGameSaveInfo->wForceOrbUsing[1] = (WORD)sec;
	}
	else
	{
		lpGameSaveInfo->wForceOrbUsing[0] = 0;
		lpGameSaveInfo->wForceOrbUsing[1] = 0;
	}

	if (lpPlayInfo->dwLifeBooster_SaveTime && lpPlayInfo->dwLifeBooster_SaveTime > SERVER_GAMETIME)
	{
		lpGameSaveInfo->wLifeBoosterUsing[0] = (WORD)(lpPlayInfo->dwLifeBooster_SaveCode&sinITEM_MASK3);
		lpGameSaveInfo->wLifeBoosterUsing[1] = (WORD)LifeBooster_sec;
	}
	else
	{
		lpGameSaveInfo->wLifeBoosterUsing[0] = 0;
		lpGameSaveInfo->wLifeBoosterUsing[1] = 0;
	}
	if (lpPlayInfo->dwManaBooster_SaveTime && lpPlayInfo->dwManaBooster_SaveTime > SERVER_GAMETIME)
	{
		lpGameSaveInfo->wManaBoosterUsing[0] = (WORD)(lpPlayInfo->dwManaBooster_SaveCode&sinITEM_MASK3);
		lpGameSaveInfo->wManaBoosterUsing[1] = (WORD)ManaBooster_sec;
	}
	else
	{
		lpGameSaveInfo->wManaBoosterUsing[0] = 0;
		lpGameSaveInfo->wManaBoosterUsing[1] = 0;
	}
	if (lpPlayInfo->dwStaminaBooster_SaveTime && lpPlayInfo->dwStaminaBooster_SaveTime > SERVER_GAMETIME)
	{
		lpGameSaveInfo->wStaminaBoosterUsing[0] = (WORD)(lpPlayInfo->dwStaminaBooster_SaveCode&sinITEM_MASK3);
		lpGameSaveInfo->wStaminaBoosterUsing[1] = (WORD)StaminaBooster_sec;
	}
	else
	{
		lpGameSaveInfo->wStaminaBoosterUsing[0] = 0;
		lpGameSaveInfo->wStaminaBoosterUsing[1] = 0;
	}
	if (lpPlayInfo->dwSkillDelay_SaveTime && lpPlayInfo->dwSkillDelay_SaveTime > SERVER_GAMETIME)
	{
		lpGameSaveInfo->wSkillDelayUsing[0] = (WORD)(lpPlayInfo->dwSkillDelay_SaveCode&sinITEM_MASK3);
		lpGameSaveInfo->wSkillDelayUsing[1] = (WORD)nSkillDelay_sec;
	}
	else
	{
		lpGameSaveInfo->wSkillDelayUsing[0] = 0;
		lpGameSaveInfo->wSkillDelayUsing[1] = 0;
	}
	if (lpPlayInfo->dwTime_PrimeItem_X2 > (DWORD)SERVER_LOCATIME)
		lpGameSaveInfo->dwTime_PrimeItem_X2 = lpPlayInfo->dwTime_PrimeItem_X2 - (DWORD)SERVER_LOCATIME;
	else
		lpGameSaveInfo->dwTime_PrimeItem_X2 = 0;

	if (lpPlayInfo->dwTime_PrimeItem_ExpUp > (DWORD)SERVER_LOCATIME)
		lpGameSaveInfo->dwTime_PrimeItem_ExpUp = lpPlayInfo->dwTime_PrimeItem_ExpUp - (DWORD)SERVER_LOCATIME;
	else
		lpGameSaveInfo->dwTime_PrimeItem_ExpUp = 0;

	if (lpPlayInfo->dwTime_PrimeItem_X2 || lpGameSaveInfo->dwTime_PrimeItem_ExpUp)
		lpGameSaveInfo->dwPrimeItem_PackageCode = lpPlayInfo->dwPrimeItem_PackageCode;

	if (lpPlayInfo->dwTime_PrimeItem_VampCuspid > (DWORD)SERVER_LOCATIME)
		lpGameSaveInfo->dwTime_PrimeItem_VampCuspid = lpPlayInfo->dwTime_PrimeItem_VampCuspid - (DWORD)SERVER_LOCATIME;
	else
		lpGameSaveInfo->dwTime_PrimeItem_VampCuspid = 0;

	if (lpPlayInfo->dwTime_PrimeItem_VampCuspid_EX > (DWORD)SERVER_LOCATIME)
		lpGameSaveInfo->dwTime_PrimeItem_VampCuspid_EX = lpPlayInfo->dwTime_PrimeItem_VampCuspid_EX - (DWORD)SERVER_LOCATIME;
	else
		lpGameSaveInfo->dwTime_PrimeItem_VampCuspid_EX = 0;

	if (lpPlayInfo->dwTime_PrimeItem_ManaRecharg > (DWORD)SERVER_LOCATIME)
		lpGameSaveInfo->dwTime_PrimeItem_ManaRecharg = lpPlayInfo->dwTime_PrimeItem_ManaRecharg - (DWORD)SERVER_LOCATIME;
	else
		lpGameSaveInfo->dwTime_PrimeItem_ManaRecharg = 0;

	if (lpPlayInfo->dwTime_PrimeItem_ManaReduce > (DWORD)SERVER_LOCATIME)
		lpGameSaveInfo->dwTime_PrimeItem_ManaReduce = lpPlayInfo->dwTime_PrimeItem_ManaReduce - (DWORD)SERVER_LOCATIME;
	else
		lpGameSaveInfo->dwTime_PrimeItem_ManaReduce = 0;

	if (lpPlayInfo->dwTime_PrimeItem_MightofAwell > (DWORD)SERVER_LOCATIME)
		lpGameSaveInfo->dwTime_PrimeItem_MightofAwell = lpPlayInfo->dwTime_PrimeItem_MightofAwell - (DWORD)SERVER_LOCATIME;
	else
		lpGameSaveInfo->dwTime_PrimeItem_MightofAwell = 0;

	if (lpPlayInfo->dwTime_PrimeItem_MightofAwell2 > (DWORD)SERVER_LOCATIME)
		lpGameSaveInfo->dwTime_PrimeItem_MightofAwell2 = lpPlayInfo->dwTime_PrimeItem_MightofAwell2 - (DWORD)SERVER_LOCATIME;
	else
		lpGameSaveInfo->dwTime_PrimeItem_MightofAwell2 = 0;

	if (lpPlayInfo->dwTime_PrimeItem_HelpPet > (DWORD)SERVER_LOCATIME)
		lpGameSaveInfo->dwTime_PrimeItem_HelpPet = lpPlayInfo->dwTime_PrimeItem_HelpPet - (DWORD)SERVER_LOCATIME;
	else
	{
		lpPlayInfo->sCharacterData.GravityScroolCheck[1] = 0;
		lpGameSaveInfo->dwTime_PrimeItem_HelpPet = 0;
		lpGameSaveInfo->sPetInfo[0] = 0;
		lpGameSaveInfo->sPetInfo[1] = 0;
	}

	if (lpPlayInfo->dwTime_PrimeItem_StaminaReduce > (DWORD)SERVER_LOCATIME)
		lpGameSaveInfo->dwTime_PrimeItem_StaminaReduce = lpPlayInfo->dwTime_PrimeItem_StaminaReduce - (DWORD)SERVER_LOCATIME;
	else
		lpGameSaveInfo->dwTime_PrimeItem_StaminaReduce = 0;

	if (lpPlayInfo->dwCaravan_Hopy_Time > (DWORD)SERVER_LOCATIME)
	{
		lpGameSaveInfo->dwTime_CaravanHopy = lpPlayInfo->dwCaravan_Hopy_Time - (DWORD)SERVER_LOCATIME;
		lpGameSaveInfo->dwCaravanParam = lpPlayInfo->dwCaravan_Param;
	}
	else
	{
		lpGameSaveInfo->dwTime_CaravanHopy = 0;
		lpGameSaveInfo->dwCaravanParam = 0;
	}
	if (lpPlayInfo->dwTime_PhenixPet > (DWORD)SERVER_LOCATIME)
	{
		lpGameSaveInfo->dwTime_PrimeItem_PhenixPet = lpPlayInfo->dwTime_PhenixPet - (DWORD)SERVER_LOCATIME;
		lpGameSaveInfo->dwPhoenix = lpPlayInfo->PhenixPetType;
	}
	else
	{
		lpGameSaveInfo->dwTime_PrimeItem_PhenixPet = 0;
		lpGameSaveInfo->dwPhoenix = 0;
	}
	if (lpPlayInfo->dwTime_BigHead > (DWORD)SERVER_LOCATIME)
	{
		lpGameSaveInfo->dwTime_PrimeItem_BigHead = lpPlayInfo->dwTime_BigHead - (DWORD)SERVER_LOCATIME;
		lpGameSaveInfo->dwPrimeItem_BigHead = lpPlayInfo->BigHeadType;
	}

	return TRUE;
}
int rsSaveServerPotion(User *lpPlayInfo, CharacterSave *lpGameSaveInfo)
{
	int cnt1, cnt2;

	if (lpPlayInfo->AdminOperMode == 0)
	{
		lpGameSaveInfo->sPotionUpdate[0] = 1;
		lpGameSaveInfo->sPotionUpdate[1] = 0;

		for (cnt1 = 0; cnt1 < 3; cnt1++)
		{
			for (cnt2 = 0; cnt2 < 4; cnt2++)
				lpGameSaveInfo->sPotionCount[cnt1][cnt2] = (short)lpPlayInfo->ServerPotion[cnt1][cnt2];
		}
	}
	else
	{
		lpGameSaveInfo->sPotionUpdate[0] = 0;
		lpGameSaveInfo->sPotionUpdate[1] = 0;
	}

	return TRUE;
}
int rsCompareServerPotion(User *lpPlayInfo, CharacterSave *lpGameSaveInfo)
{
	int cnt1, cnt2, pot;
	int OverPotion[3][4];
	int OverPotion2[3] = { 0,0,0 };
	int ErrFlag;
	smTRANS_COMMAND	smTransCommand;

	if (lpGameSaveInfo->sPotionUpdate[0] && lpGameSaveInfo->sPotionUpdate[0] == lpGameSaveInfo->sPotionUpdate[1])
	{
		ErrFlag = 0;

		for (cnt1 = 0; cnt1 < 3; cnt1++)
		{
			for (cnt2 = 0; cnt2 < 4; cnt2++)
			{
				if (((int)lpGameSaveInfo->sPotionCount[cnt1][cnt2]) < lpPlayInfo->ServerPotion[cnt1][cnt2])
				{
					pot = lpPlayInfo->ServerPotion[cnt1][cnt2] - lpGameSaveInfo->sPotionCount[cnt1][cnt2];
					OverPotion[cnt1][cnt2] = pot;
					OverPotion2[cnt1] += pot;
					ErrFlag++;
				}
				else
					OverPotion[cnt1][cnt2] = 0;
			}
		}

		if (ErrFlag)
		{
			smTransCommand.WParam = 8800;
			smTransCommand.LParam = OverPotion2[0];
			smTransCommand.SParam = OverPotion2[1];
			smTransCommand.EParam = OverPotion2[2];
			RecordHackLogFile(lpPlayInfo, &smTransCommand);

			for (cnt1 = 0; cnt1 < 3; cnt1++) {
				for (cnt2 = 0; cnt2 < 4; cnt2++) {
					lpPlayInfo->ServerPotion[cnt1][cnt2] = lpGameSaveInfo->sPotionCount[cnt1][cnt2];
					if (lpPlayInfo->ServerPotion[cnt1][cnt2] < 0) lpPlayInfo->ServerPotion[cnt1][cnt2] = 0;
				}
			}
		}
	}

	return TRUE;
}
int ImportTTServerUser(char *szID, char *szServerID)
{
	char szRealID[32];
	char szTTServerPath[128];
	sPLAY_USER_DATA		sPlayUserData;
	char szFile[256];
	char szFile2[256];
	CharacterFile	TransRecordData;
	char szName[64];
	int	size;
	int cnt;
	FILE	*fp;

	GetTT_ServerPath(szServerID, szTTServerPath);
	GetRealID(szID, szRealID);

	GetUserInfoFile2(szID, szFile, szServerID, sizeof(szFile));

	ZeroMemory(&sPlayUserData, sizeof(sPLAY_USER_DATA));
	fopen_s(&fp, szFile, "rb");
	if (!fp)
		return FALSE;
	fread(&sPlayUserData, sizeof(sPLAY_USER_DATA), 1, fp);
	fclose(fp);

	for (cnt = 0; cnt < sPLAY_CHAR_MAX; cnt++)
	{
		if (sPlayUserData.szCharName[cnt][0])
		{
			GetUserDataFile2(sPlayUserData.szCharName[cnt], szFile2, szServerID, sizeof(szFile2));

			wsprintf(szName, "%s@%s", sPlayUserData.szCharName[cnt], szServerID);
			lstrcpy(sPlayUserData.szCharName[cnt], szName);

			ZeroMemory(&TransRecordData, sizeof(CharacterFile));
			fopen_s(&fp, szFile2, "rb");
			if (fp)
			{
				fread(&TransRecordData, sizeof(CharacterFile), 1, fp);
				fclose(fp);
			}
			if (TransRecordData.iLength > 0)
			{
				GetUserDataFile(sPlayUserData.szCharName[cnt], szFile2, sizeof(szFile2));
				lstrcpy(TransRecordData.sCharInfo.szName, szName);
				lstrcpy(TransRecordData.GameSaveInfo.szMasterID, szID);

				size = TransRecordData.iLength;
				if (size < 16384) size = 16384;

				fopen_s(&fp, szFile2, "wb");
				if (fp)
				{
					fwrite(&TransRecordData, size, 1, fp);
					fclose(fp);
				}
			}
		}
	}

	GetUserInfoFile(szID, szFile, sizeof(szFile));

	lstrcpy(sPlayUserData.szID, szID);

	fopen_s(&fp, szFile, "wb");
	if (fp)
	{
		fwrite(&sPlayUserData, sizeof(sPLAY_USER_DATA), 1, fp);
		fclose(fp);
	}

	return TRUE;
}

DWORD WINAPI RecDataThreadProc(void *pInfo)
{
	HANDLE	hThread;
	int cnt;
	int size;
	FILE *fp;
	sREC_DATABUFF	*recDataBuff;
	int	recDataBuffCount;

	recDataBuff = new sREC_DATABUFF[REC_DATABUFF_MAX];


	hThread = GetCurrentThread();
	dwLastRecDataTime = GetCurrentTime();

	while (1)
	{
		SuspendThread(hThread);

		if (sRecDataBuffCount == 0)
		{
			dwLastRecDataTime = GetCurrentTime();
			continue;
		}

		EnterCriticalSection(&cRecDataSection);
		recDataBuffCount = sRecDataBuffCount;
		memcpy(recDataBuff, sRecDataBuff, sizeof(sREC_DATABUFF)*sRecDataBuffCount);
		sRecDataBuffCount = 0;
		dwLastRecDataTime = GetCurrentTime();
		//Å©¸®Æ¼Ä® ¼½¼Ç ÇØÁ¦
		LeaveCriticalSection(&cRecDataSection);

		//º¹»çµÈ µ¥ÀÌÅ¸¸¦ ÇÏµåµð½ºÅ©¿¡ ÀúÀåÇÑ´Ù
		//Å©¸®Æ¼Ä® ¼½¼Ç ¼±¾ð
		EnterCriticalSection(&cSaveDataSection);
		for (cnt = 0; cnt < recDataBuffCount; cnt++)
		{
			size = recDataBuff[cnt].TransRecData.iLength;
			if (size < 16000)
				size = 16000;

			CopyFile(recDataBuff[cnt].szFileName, recDataBuff[cnt].szBackupFileName, FALSE);
			fopen_s(&fp, recDataBuff[cnt].szFileName, "wb");
			if (fp)
			{
				fwrite(&recDataBuff[cnt].TransRecData, size, 1, fp);
				fclose(fp);
			}
		}
		//Å©¸®Æ¼Ä® ¼½¼Ç ÇØÁ¦
		LeaveCriticalSection(&cSaveDataSection);
	}

	ExitThread(TRUE);
	return TRUE;
}
int rsInitDataBase()
{
	InitializeCriticalSection(&cRecDataSection);

	InitializeCriticalSection(&cSaveDataSection);

	if (!sRecDataBuff)
	{
		sRecDataBuff = new sREC_DATABUFF[REC_DATABUFF_MAX];
		if (!sRecDataBuff)
			return FALSE;
	}
	if (!hRecThread)
	{
		hRecThread = CreateThread(NULL, 0, RecDataThreadProc, 0, 0, &dwRecThreadId);
		if (!hRecThread)
		{
			delete sRecDataBuff;
			sRecDataBuff = 0;
			return FALSE;
		}
	}
	sRecDataBuffCount = 0;

	return TRUE;
}
int rsCloseDataBase()
{
	if (sRecDataBuff)
	{
		delete sRecDataBuff;
		sRecDataBuff = 0;
	}

	return TRUE;
}
int rsSaveRecData(CharacterFile *lpTransRecordData, User *lpPlayInfo, char *szFileName, char *szBackupFileName)
{
	if (sRecDataBuff && hRecThread)
	{
		if (sRecDataBuffCount >= REC_DATABUFF_MAX)
			return FALSE;
		if (sRecDataBuffCount >= REC_DATABUFF_LIMIT)
			ResumeThread(hRecThread);

		EnterCriticalSection(&cRecDataSection);

		sRecDataBuff[sRecDataBuffCount].lpPlayInfo = lpPlayInfo;
		if (lpPlayInfo)
			sRecDataBuff[sRecDataBuffCount].dwConnectCount = lpPlayInfo->dwConnectCount;
		else
			sRecDataBuff[sRecDataBuffCount].dwConnectCount = 0;

		lstrcpy(sRecDataBuff[sRecDataBuffCount].szName, lpTransRecordData->sCharInfo.szName);

		lstrcpy(sRecDataBuff[sRecDataBuffCount].szFileName, szFileName);
		lstrcpy(sRecDataBuff[sRecDataBuffCount].szBackupFileName, szBackupFileName);
		memcpy(&sRecDataBuff[sRecDataBuffCount].TransRecData, lpTransRecordData, lpTransRecordData->iLength);
		sRecDataBuffCount++;

		LeaveCriticalSection(&cRecDataSection);
		return TRUE;
	}

	return FALSE;
}

int CheckRecWaitData(char *szName)
{
	return FALSE;
}
int rsTimeRecData()
{
	DWORD dwTime;

	dwTime = GetCurrentTime();

	if (hRecThread && (dwTime - dwLastRecDataTime) > 5000)
	{
		ResumeThread(hRecThread);
		return TRUE;
	}

	return FALSE;
}
int	rsAddPostBox_Present(User *lpPlayInfo)
{
	char	szFileName[64];
	int		len;

	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;

	char	strBuff[16384];

	if (!lpPlayInfo->szAccountName[0])
		return FALSE;

	hFile = CreateFile("Present.dat", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	len = GetFileSize(hFile, NULL);
	if (len > 16384)
		return FALSE;

	ReadFile(hFile, strBuff, len, &dwAcess, NULL);
	CloseHandle(hFile);

	GetPostBoxFile(lpPlayInfo->szAccountName, szFileName, sizeof(szFileName));

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);

	WriteFile(hFile, strBuff, len, &dwAcess, NULL);

	CloseHandle(hFile);

	return TRUE;
}


//º° Æ÷ÀÎÆ® ÀÌº¥Æ® Æ¼ÄÏ ¹ß»ý ¼³Á¤
int	OpenStarPointEvent(User *lpPlayInfo, CharacterData *lpCharInfo)
{
	int cnt;

	if (!lpCharInfo)
	{
		if (lpPlayInfo->CharLevelMax < rsServerConfig.Event_StarPointTicket)
		{

			if (!lpPlayInfo->CharLevelMax)
				lpPlayInfo->Event_StarTicketLevel = 3 + (rand() % 6);
			else
			{
				cnt = (lpPlayInfo->CharLevelMax / 10) + 1;
				cnt = cnt * 10;
				lpPlayInfo->Event_StarTicketLevel = cnt + (rand() % 10);
			}
		}

		return TRUE;
	}

	if (lpPlayInfo->CharLevelMax < rsServerConfig.Event_StarPointTicket && lpCharInfo->iLevel >= lpPlayInfo->CharLevelMax)
	{

		if (lpCharInfo->sEventParam[0] == CHAR_EVENT_STARPOINT)
		{

		}
		else
		{
			lpCharInfo->sEventParam[0] = CHAR_EVENT_STARPOINT;
			lpCharInfo->sEventParam[1] = 0;
		}

		cnt = (lpCharInfo->iLevel / 10) + 1;
		cnt = cnt * 10;

		if (lpCharInfo->iLevel > lpCharInfo->sEventParam[1])
			lpCharInfo->sEventParam[1] = cnt + (rand() % 10);

		lpPlayInfo->Event_StarTicketLevel = lpCharInfo->sEventParam[1];
	}

	return TRUE;
}
int	CloseStarPointEvent(User *lpPlayInfo, CharacterData *lpCharInfo)
{
	if (lpPlayInfo->Event_StarTicketLevel)
	{
		lpCharInfo->sEventParam[0] = CHAR_EVENT_STARPOINT;
		lpCharInfo->sEventParam[1] = lpPlayInfo->Event_StarTicketLevel;
	}

	return TRUE;

}
int SaveCloseUserRecord(char *szUserName, int Level, int Exp, int Money)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	char	szFileName[128];
	char	szBuff[256];
	int		TotalMoney = 0;


	wsprintf(szFileName, "UserRecord.txt");

	wsprintf(szBuff, "%s		·¹º§(%d)	°æÇèÄ¡(%d)	µ·(%d)\r\n", szUserName, Level, Exp, Money);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}
int SaveWareHouseRecord(char *szUserName, int Money, int Weight1, int Weight2)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	char	szFileName[128];
	char	szBuff[256];
	int		TotalMoney = 0;

	wsprintf(szFileName, "UserRecord.txt");

	wsprintf(szBuff, "ID( %s )	Ã¢°íµ·(%d)	¹«°Ô( %d/%d )\r\n", szUserName, Money, Weight1, Weight2);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}

int PeekMonMsg();
int	MonQuit = 0;
HWND hDialog;
HWND hWndMon;
extern HINSTANCE hinst;

#define RECORD_MONEY_LIMIT		100000


int CheckUserData(char *szName)
{
	char *lpData;
	char szFile[256];
	FILE *fp;
	int	recFlag = 0;

	CharacterFile TransRecordData;
	CharacterFile *lpTransRecord;

	lpData = (char *)&TransRecordData;
	lpTransRecord = &TransRecordData;

	GetUserDataFile(szName, szFile, sizeof(szFile));

	fopen_s(&fp, szFile, "rb");
	if (fp)
	{
		fread(lpTransRecord, sizeof(CharacterFile), 1, fp);
		fclose(fp);
	}
	else
		return FALSE;

	return TRUE;
}

int CheckWareHouseData(char *szFile)
{
	TRANS_WAREHOUSE	TransWareHouse;
	sWAREHOUSE	WareHouse;
	FILE *fp;
	//int cnt,len;
	//char szName[256];

	fopen_s(&fp, szFile, "rb");
	if (fp)
	{
		fread(&TransWareHouse, sizeof(TRANS_WAREHOUSE), 1, fp);
		fclose(fp);
	}
	else
		return FALSE;

	DecodeCompress((BYTE *)&TransWareHouse.Data, (BYTE *)&WareHouse);

	/*if (WareHouse.Weight[0]>WareHouse.Weight[1] || WareHouse.Money>=RECORD_MONEY_LIMIT)
	{
		lstrcpy(szName,szFile);
		len = lstrlen(szName);

		for (cnt=0;cnt<len;cnt++)
		{
			if (szName[cnt]=='.')
			{
				szName[cnt] = 0;
				break;
			}
		}
		for (cnt=cnt;cnt>=0;cnt--)
		{
			if (szName[cnt]=='\\')
			{
				cnt++;
				break;
			}
		}
		SaveWareHouseRecord(szName+cnt,WareHouse.Money,WareHouse.Weight[0],WareHouse.Weight[1]);
	}*/

	return TRUE;
}

int CheckUserDataFull()
{
	HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;
	char	szFindPath[64];
	char	szUserName[64];
	char	szMsgBuff[256];
	int		cnt, len;
	int		UserCnt;
	int		CharCount = 0;

	for (UserCnt = 0; UserCnt < 256; UserCnt++)
	{
		wsprintf(szFindPath, "DataServer\\UserData\\%d\\*.dat", UserCnt);

		wsprintf(szMsgBuff, "Ä³¸¯ÅÍ È®ÀÎÁß ( %d/255 ) - %d", UserCnt, CharCount);
		//SetWindowText(GetDlgItem(hDialog, IDC_EDIT1), szMsgBuff);

		hFindHandle = FindFirstFile(szFindPath, &fd);
		if (hFindHandle != INVALID_HANDLE_VALUE)
		{
			while (1)
			{
				lstrcpy(szUserName, fd.cFileName);
				len = lstrlen(szUserName);

				for (cnt = 0; cnt < len; cnt++)
				{
					if (szUserName[cnt] == '.')
					{
						szUserName[cnt] = 0;
						break;
					}
				}

				CheckUserData(szUserName);
				CharCount++;

				PeekMonMsg();

				if (FindNextFile(hFindHandle, &fd) == FALSE)
					break;
				if (MonQuit)
					break;
			}
		}
		FindClose(hFindHandle);
	}

	return TRUE;
}

int CheckWareHouseDataFull()
{
	HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;
	char	szFindPath[64];
	char	szUserName[64];
	char	szUserPath[64];
	char	szMsgBuff[256];

	int		cnt, len;
	int		UserCnt;
	int		CharCount = 0;

	for (UserCnt = 0; UserCnt < 256; UserCnt++)
	{
		wsprintf(szFindPath, "DataServer\\WareHouse\\%d\\*.war", UserCnt);

		wsprintf(szMsgBuff, "¾ÆÀÌÅÛº¸°ü¼Ò È®ÀÎÁß ( %d/255 ) - %d", UserCnt, CharCount);
		//SetWindowText(GetDlgItem(hDialog, IDC_EDIT1), szMsgBuff);

		hFindHandle = FindFirstFile(szFindPath, &fd);
		if (hFindHandle != INVALID_HANDLE_VALUE)
		{
			while (1)
			{
				lstrcpy(szUserName, fd.cFileName);
				len = lstrlen(szUserName);

				for (cnt = 0; cnt < len; cnt++)
				{
					if (szUserName[cnt] == '.')
					{
						szUserName[cnt] = 0;
						break;
					}
				}

				wsprintf(szUserPath, "DataServer\\WareHouse\\%d\\%s", UserCnt, fd.cFileName);
				CheckWareHouseData(szUserPath);

				CharCount++;
				PeekMonMsg();

				if (FindNextFile(hFindHandle, &fd) == FALSE)
					break;
				if (MonQuit)
					break;
			}
		}
		FindClose(hFindHandle);
	}

	return TRUE;
}


int PeekMonMsg()
{
	MSG msg;

	while (1)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
			break;
	}
	return TRUE;
}

static char decode[512];
static char line[512];

static char *GetWord(char *q, char *p)
{

	while ((*p == 32) || (*p == 9))
	{
		p++;
	}

	while ((*p != 32) && (*p != 9))
	{
		if (*p == '\n' || *p == '\r')
			break;
		*q++ = *p++;
	}
	*q++ = 0;

	return p;
}
int RestoreBackupData(char *szListFile, char *BackupPath)
{
	FILE	*fp, *fp2, *fp3;
	char strBuff[256];
	char *p;
	WIN32_FIND_DATA		ffd;
	HANDLE				hFind;
	sPLAY_USER_DATA		sPlayUserData;
	int cnt;
	int flag;

	char szInfoFile[256];
	char szSrcDataFile[256];
	char szDestDataFile[256];
	char szLogBuff[256];
	char szFile[256];

	fopen_s(&fp, szListFile, "rb");
	if (fp == NULL) return FALSE;

	fopen_s(&fp3, "BackupData.log", "wb");
	if (fp3 == NULL)
	{
		fclose(fp);
		return FALSE;
	}

	CreateDirectory("BackupUser", 0);

	while (!feof(fp))
	{
		if (fgets(line, 255, fp) == NULL)
			break;

		p = GetWord(decode, line);

		if (decode[0])
		{
			p = GetWord(strBuff, p);

			if (strBuff[0])
			{
				GetUserInfoFile(decode, szInfoFile, sizeof(szInfoFile));
				GetUserDataFile(strBuff, szDestDataFile, sizeof(szDestDataFile));
				lstrcpy(szSrcDataFile, BackupPath);
				lstrcat(szSrcDataFile, szDestDataFile);

				flag = TRUE;

				hFind = FindFirstFile(szSrcDataFile, &ffd);
				FindClose(hFind);

				if (hFind != INVALID_HANDLE_VALUE)
				{
					fopen_s(&fp2, szInfoFile, "rb");
					if (fp2)
					{
						fread(&sPlayUserData, sizeof(sPLAY_USER_DATA), 1, fp2);
						fclose(fp2);

						for (cnt = 0; cnt < sPLAY_CHAR_MAX; cnt++)
						{
							if (sPlayUserData.szCharName[cnt][0])
							{
								if (lstrcmpi(sPlayUserData.szCharName[cnt], strBuff) == 0)
									break;
							}
						}

						if (cnt >= sPLAY_CHAR_MAX)
						{
							hFind = FindFirstFile(szDestDataFile, &ffd);
							FindClose(hFind);
							if (hFind == INVALID_HANDLE_VALUE)
							{
								for (cnt = 0; cnt < sPLAY_CHAR_MAX; cnt++)
								{
									if (!sPlayUserData.szCharName[cnt][0])
									{
										lstrcpy(sPlayUserData.szCharName[cnt], strBuff);
										fopen_s(&fp2, szInfoFile, "wb");
										if (fp2)
										{
											fwrite(&sPlayUserData, sizeof(sPLAY_USER_DATA), 1, fp2);
											fclose(fp2);
										}
										break;
									}
								}
							}
							else
							{
								flag = FALSE;
								wsprintf(szLogBuff, "%s (%s) -> ½ÇÆÐ ( ½Å±ÔÄ³¸¯ÀÌÁ¸Àç )\r\n", decode, strBuff);
								fwrite(szLogBuff, lstrlen(szLogBuff), 1, fp3);
							}
						}

						if (flag)
						{
							wsprintf(szFile, "BackupUser\\%s.dat", strBuff);
							CopyFile(szDestDataFile, szFile, TRUE);

							CopyFile(szSrcDataFile, szDestDataFile, FALSE);

							wsprintf(szLogBuff, "%s (%s) -> ¼º°ø\r\n", decode, strBuff);
							fwrite(szLogBuff, lstrlen(szLogBuff), 1, fp3);
						}
					}
					else
					{
						wsprintf(szLogBuff, "%s (%s) -> ½ÇÆÐ ( °èÁ¤ÀÌ¾øÀ½ )\r\n", decode, strBuff);
						fwrite(szLogBuff, lstrlen(szLogBuff), 1, fp3);
					}
				}
				else
				{
					wsprintf(szLogBuff, "%s (%s) -> ½ÇÆÐ ( ¼Ò½ºÆÄÀÏ¾øÀ½ )\r\n", decode, strBuff);
					fwrite(szLogBuff, lstrlen(szLogBuff), 1, fp3);
				}
			}
		}
	}

	fclose(fp3);
	fclose(fp);

	return TRUE;
}

//µÇÂ¼·þÎñÆ÷µÄKEY
#define	LOGIN_SERVER_KEY		0x542634c5
#define	LOGIN_SERVER_SHIFT		6