#include "StdAfx.h"
#include "smwsock.h"
#include "character.h"
#include "playmain.h"
#include "srcsound\\dxwav.h"
#include "fileread.h"

#include "particle.h"
#include "netplay.h"

#include "record.h"
#include "playsub.h"

#include "TextMessage.h"

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
extern time_t				tServerTime;
extern int					Server_DebugCount;

#include "resource.h"

static char LastAcessID[64];


struct sREC_DATABUFF
{
	void	*lpPlayInfo;
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

int CheckRecWaitData(char *szName);


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
		wsprintf(szFileName, "%s\\%d\\＃%s.dat", szPostBoxDir, GetUserCode(szID), szID);
		GetCharSize(szFileName, MaxSize);
		return TRUE;
	}

	if (szID[3] == 0 && ((szID[0] == 'p' || szID[0] == 'P') && (szID[1] == 'r' || szID[1] == 'R') && (szID[2] == 'n' || szID[2] == 'N')) || ((szID[0] == 'c' || szID[0] == 'C') && (szID[1] == 'o' || szID[1] == 'O') && (szID[2] == 'n' || szID[2] == 'N')))
	{
		wsprintf(szFileName, "%s\\%d\\＃%s.dat", szPostBoxDir, GetUserCode(szID), szID);
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
		wsprintf(szFileName, "DataServer\\%s\\%d\\＃%s.dat", szRecordUserInfoDir, GetUserCode(szID), szID);
		GetCharSize(szFileName, MaxSize);
		return TRUE;
	}

	if (szID[3] == 0 && ((szID[0] == 'p' || szID[0] == 'P') && (szID[1] == 'r' || szID[1] == 'R') && (szID[2] == 'n' || szID[2] == 'N')) || ((szID[0] == 'c' || szID[0] == 'C') && (szID[1] == 'o' || szID[1] == 'O') && (szID[2] == 'n' || szID[2] == 'N')))
	{
		wsprintf(szFileName, "DataServer\\%s\\%d\\＃%s.dat", szRecordUserInfoDir, GetUserCode(szID), szID);
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
		wsprintf(szFileName, "%s\\DataServer\\%s\\%d\\＃%s.dat", szTTServerPath, szRecordUserInfoDir, GetUserCode(szRealID), szRealID);
		GetCharSize(szFileName, MaxSize);
		return TRUE;
	}
	if (szID[3] == 0 && ((szID[0] == 'p' || szID[0] == 'P') && (szID[1] == 'r' || szID[1] == 'R') && (szID[2] == 'n' || szID[2] == 'N')) || ((szID[0] == 'c' || szID[0] == 'C') && (szID[1] == 'o' || szID[1] == 'O') && (szID[2] == 'n' || szID[2] == 'N')))
	{
		wsprintf(szFileName, "%s\\DataServer\\%s\\%d\\＃%s.dat", szTTServerPath, szRecordUserInfoDir, GetUserCode(szRealID), szRealID);
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
		wsprintf(szFileName, "DataServer\\%s\\%d\\＃%s.dat", szRecordWareHouseDir, GetUserCode(szID), szID);
		GetCharSize(szFileName, MaxSize);
		return TRUE;
	}
	if (szID[3] == 0 && ((szID[0] == 'p' || szID[0] == 'P') && (szID[1] == 'r' || szID[1] == 'R') && (szID[2] == 'n' || szID[2] == 'N')) || ((szID[0] == 'c' || szID[0] == 'C') && (szID[1] == 'o' || szID[1] == 'O') && (szID[2] == 'n' || szID[2] == 'N')))
	{
		wsprintf(szFileName, "DataServer\\%s\\%d\\＃%s.dat", szRecordWareHouseDir, GetUserCode(szID), szID);
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
		wsprintf(szFileName, "%s\\%s\\%d\\＃%s.dat", szBuff, szRecordWareHouseDir, GetUserCode(szID), szID);
		GetCharSize(szFileName, MaxSize);
		return TRUE;
	}
	if (szID[3] == 0 && ((szID[0] == 'p' || szID[0] == 'P') && (szID[1] == 'r' || szID[1] == 'R') && (szID[2] == 'n' || szID[2] == 'N')) || ((szID[0] == 'c' || szID[0] == 'C') && (szID[1] == 'o' || szID[1] == 'O') && (szID[2] == 'n' || szID[2] == 'N')))
	{
		wsprintf(szFileName, "%s\\%s\\%d\\＃%s.dat", szBuff, szRecordWareHouseDir, GetUserCode(szID), szID);
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

//学习技能保存
int	SaveSkill(RecordSkill *lpRecordSkill)
{
	int cnt;
	int mcnt;

	for (cnt = 1; cnt < SIN_MAX_USE_SKILL; cnt++)
	{
		mcnt = cnt - 1;
		lpRecordSkill->bSkillPoint[mcnt] = sinSkill.UseSkill[cnt].Point;
		if (sinSkill.UseSkill[cnt].Point > 255) lpRecordSkill->bSkillPoint[mcnt] = 255;

		if (sinSkill.UseSkill[cnt].UseSkillCount < 10000)
			lpRecordSkill->wSkillMastery[mcnt] = sinSkill.UseSkill[cnt].UseSkillCount;
		else
			lpRecordSkill->wSkillMastery[mcnt] = 10000;

		lpRecordSkill->wShortKey[mcnt] = sinSkill.UseSkill[cnt].ShortKey | (sinSkill.UseSkill[cnt].MousePosi << 8);
	}

	lpRecordSkill->wSelectSkill[0] = 0;
	lpRecordSkill->wSelectSkill[1] = 0;

	if (sinSkill.pLeftSkill && sinSkill.pLeftSkill->CODE != SKILL_NORMAL_ATTACK)
		lpRecordSkill->wSelectSkill[0] = sinSkill.pLeftSkill->Skill_Info.SkillNum + 1;
	if (sinSkill.pRightSkill && sinSkill.pRightSkill->CODE != SKILL_NORMAL_ATTACK)
		lpRecordSkill->wSelectSkill[1] = sinSkill.pRightSkill->Skill_Info.SkillNum + 1;

	return TRUE;
}

//任务获得的技能点
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
//任务获得的属性点
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
//恢复技能
int	RestoreSkill(RecordSkill *lpRecordSkill, DWORD dwLevelQuestLog)
{
	int cnt, mcnt;
	int	Point, EPoint;

	Point = 0;
	EPoint = 0;

	for (cnt = 1; cnt < SIN_MAX_USE_SKILL; cnt++)
	{
		mcnt = cnt - 1;

		sinSkill.UseSkill[cnt].Point = lpRecordSkill->bSkillPoint[mcnt];
		sinSkill.UseSkill[cnt].UseSkillCount = lpRecordSkill->wSkillMastery[mcnt];
		sinSkill.UseSkill[cnt].ShortKey = lpRecordSkill->wShortKey[mcnt] & 0xFF;
		sinSkill.UseSkill[cnt].MousePosi = lpRecordSkill->wShortKey[mcnt] >> 8;
		sinSkill.UseSkill[cnt].Position = cnt + 1;
	}

	for (cnt = 1; cnt < 13; cnt++)
		Point += sinSkill.UseSkill[cnt].Point;
	for (cnt = 13; cnt < SIN_MAX_USE_SKILL; cnt++)
		EPoint += sinSkill.UseSkill[cnt].Point;

	sinSkill.UseSkill[0].Point = 1;
	sinSkill.UseSkill[0].UseSkillFlag = 1;
	sinSkill.UseSkill[0].Position = 1;


	sinSkill.pLeftSkill = &sinSkill.UseSkill[lpRecordSkill->wSelectSkill[0]];
	sinSkill.pRightSkill = &sinSkill.UseSkill[lpRecordSkill->wSelectSkill[1]];

	if (lpCurPlayer->sCharacterData.iLevel >= 10)
	{
		sinSkill.SkillPoint = ((lpCurPlayer->sCharacterData.iLevel - 8) / 2) - Point;
		sinSkill.SkillPoint += GetSkillPoint_LevelQuest(lpCurPlayer->sCharacterData.iLevel, dwLevelQuestLog);

		if (sinSkill.SkillPoint < 0)
		{
			for (cnt = 0; cnt < 13; cnt++)
			{
				sinSkill.UseSkill[cnt].Point = 0;
				sinSkill.UseSkill[cnt].UseSkillCount = 0;
			}
			sinSkill.SkillPoint = 0;
		}
	}
	else
		sinSkill.SkillPoint = 0;

	if (lpCurPlayer->sCharacterData.iLevel >= 60)
	{
		sinSkill.SkillPoint4 = ((lpCurPlayer->sCharacterData.iLevel - 58) / 2) - EPoint;

		if (sinSkill.SkillPoint4 < 0)
		{
			for (cnt = 13; cnt < SIN_MAX_USE_SKILL; cnt++)
			{
				sinSkill.UseSkill[cnt].Point = 0;
				sinSkill.UseSkill[cnt].UseSkillCount = 0;
			}
			sinSkill.SkillPoint4 = 0;
		}
	}
	else
		sinSkill.SkillPoint4 = 0;

	cInvenTory.SetItemToChar();
	cSkill.InitReformSkillPointForm();

	return TRUE;
}
//检测技能点
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
		for (int i = 0; i < CHARACTER_JOB_MAX; i++)
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
int RecordGameData(CharacterSave *lpGameSaveInfo)
{
	lpGameSaveInfo->dwHeader = dwRecordVersion;
	lpGameSaveInfo->iCameraMode = cInterFace.sInterFlags.CameraAutoFlag;

	if (lpCurPlayer->iLoadedMapIndex >= 0)
		lpGameSaveInfo->iMapID = STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID;
	else
		lpGameSaveInfo->iMapID = -1;

	lpGameSaveInfo->iCameraPositionX = lpCurPlayer->pX;
	lpGameSaveInfo->iCameraPositionZ = lpCurPlayer->pZ;

	if (lstrlen(UserAccount) < 32)
		lstrcpy(lpGameSaveInfo->szMasterID, UserAccount);

	lpGameSaveInfo->TotalExp = GetTotalExp() ^ lpGameSaveInfo->iCameraPositionX;
	lpGameSaveInfo->TotalMoney = GetTotalMoney() ^ lpGameSaveInfo->iCameraPositionZ;
	lpGameSaveInfo->TotalSubExp = GetTotalSubExp();

	SaveSkill(&lpGameSaveInfo->sSkillInfo);

	lpGameSaveInfo->ShortKey_NormalAttack = sinSkill.UseSkill[0].ShortKey | (sinSkill.UseSkill[0].MousePosi << 4);

	QuestCharacterSave	QuestInfo;
	DWORD	QuestCode;

	ZeroMemory(&QuestInfo, sizeof(QuestCharacterSave));

	QuestCode = sinSaveQuest(&QuestInfo.Data);
	QuestInfo.wQuestCode[0] = (WORD)QuestCode;

	memcpy(&lpGameSaveInfo->QuestInfo, &QuestInfo, sizeof(QuestCharacterSave));
	memcpy(&lpGameSaveInfo->LastQuestInfo, &RecordLastQuestInfo, sizeof(LastQuestSave));

	lpGameSaveInfo->sPetInfo[0] = (short)cHelpPet.PetKind;
	lpGameSaveInfo->sPetInfo[1] = (short)cHelpPet.PetShow;

	lpGameSaveInfo->dwLevelQuestLog = sinQuest_levelLog;
	lpGameSaveInfo->dwElementaryQuestLog = haElementaryQuestLog;
	lpGameSaveInfo->wFruitStatus[0] = sinFruitStatus[0];
	lpGameSaveInfo->wFruitStatus[1] = sinFruitStatus[1];

	memcpy(lpGameSaveInfo->TempStatus, sinTempStatus, sizeof(BYTE) * 8);

	return TRUE;
}

//恢复游戏数据
int RestoreGameData(CharacterSave *lpGameSaveInfo)
{
	cInterFace.sInterFlags.CameraAutoFlag = lpGameSaveInfo->iCameraMode;
	if (lpGameSaveInfo->QuestInfo.wQuestCode[0])
		sinLoadQuest(lpGameSaveInfo->QuestInfo.wQuestCode[0], &lpGameSaveInfo->QuestInfo.Data);

	memcpy(&RecordLastQuestInfo, &lpGameSaveInfo->LastQuestInfo, sizeof(LastQuestSave));

	SetQuestBoard();

	if (sBiInfo)
	{
		sBiInfo->PCRNo = lpGameSaveInfo->PCRNo;
		sBiInfo->EventPlay[0] = lpGameSaveInfo->EventPlay[0];
		sBiInfo->EventPlay[1] = lpGameSaveInfo->EventPlay[1];
	}

	cHelpPet.PetKind = (int)lpGameSaveInfo->sPetInfo[0];
	cHelpPet.PetShow = (int)lpGameSaveInfo->sPetInfo[1];
	sinQuest_levelLog = lpGameSaveInfo->dwLevelQuestLog;
	haElementaryQuestLog = lpGameSaveInfo->dwElementaryQuestLog;
	sinFruitStatus[0] = lpGameSaveInfo->wFruitStatus[0];
	sinFruitStatus[1] = lpGameSaveInfo->wFruitStatus[1];

	memcpy(sinTempStatus, lpGameSaveInfo->TempStatus, sizeof(BYTE) * 8);

	cSinSiege.SetTaxRate(lpGameSaveInfo->BlessCastleTax);
	SetBlessCastleMaster(lpGameSaveInfo->dwBlessCastleMaster, 0);

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

// 制造保存数据
int rsRECORD_DBASE::MakeRecordData(CharacterData *lpCharInfo, ItemData *lpItems, ItemData *lpItems2, ItemData *lpMouseItem)
{
	int cnt;

	BYTE	*lpRecItem;
	sRECORD_ITEM	sRecordItem;
	int		CompSize;

	lstrcpy(TransRecordData.szHeader, szRecordHeader);
	memcpy(&TransRecordData.sCharInfo, lpCharInfo, sizeof(CharacterData));

	TransRecordData.sCharInfo.wVersion[0] = Version_CharInfo;

	ZeroMemory(&TransRecordData.GameSaveInfo, sizeof(CharacterSave));

	TransRecordData.ThrowItemCount = 0;

	RecordGameData(&TransRecordData.GameSaveInfo);

	TransRecordData.GameSaveInfo.dwChecksum = GetCharInfoCode(lpCharInfo);

	TransRecordData.ItemCount = 0;
	lpRecItem = TransRecordData.Data;
	TransRecordData.DataSize = 0;

	for (cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if (lpItems[cnt].bValid)
		{
			sRecordItem.ItemCount = cnt;
			sRecordItem.x = lpItems[cnt].iPlaceX;
			sRecordItem.y = lpItems[cnt].iPlaceY;
			sRecordItem.ItemPosition = lpItems[cnt].iItemSlot;

			memcpy(&sRecordItem.sItemInfo, &lpItems[cnt].sItem, sizeof(Item));

			CompSize = EecodeCompress((BYTE *)&sRecordItem, (BYTE *)lpRecItem, sizeof(sRECORD_ITEM));

			lpRecItem += CompSize;
			TransRecordData.DataSize += CompSize;
			TransRecordData.ItemCount++;
		}
	}

	TransRecordData.ItemSubStart = TransRecordData.ItemCount;

	for (cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if (lpItems2[cnt].bValid)
		{
			sRecordItem.ItemCount = cnt;
			sRecordItem.x = lpItems2[cnt].iPlaceX;
			sRecordItem.y = lpItems2[cnt].iPlaceY;
			sRecordItem.ItemPosition = lpItems2[cnt].iItemSlot;

			memcpy(&sRecordItem.sItemInfo, &lpItems2[cnt].sItem, sizeof(Item));

			CompSize = EecodeCompress((BYTE *)&sRecordItem, (BYTE *)lpRecItem, sizeof(sRECORD_ITEM));

			lpRecItem += CompSize;
			TransRecordData.DataSize += CompSize;
			TransRecordData.ItemCount++;
		}
	}

	if (lpMouseItem && lpMouseItem->bValid)
	{
		sRecordItem.ItemCount = 0;
		sRecordItem.x = 0;
		sRecordItem.y = 0;
		sRecordItem.ItemPosition = -1;
		memcpy(&sRecordItem.sItemInfo, &lpMouseItem->sItem, sizeof(Item));

		CompSize = EecodeCompress((BYTE *)&sRecordItem, (BYTE *)lpRecItem, sizeof(sRECORD_ITEM));

		lpRecItem += CompSize;
		TransRecordData.DataSize += CompSize;
		TransRecordData.ItemCount++;
	}

	TransRecordData.iHeader = smTRANSCODE_RECORDDATA;
	TransRecordData.iLength = (WORD)(((DWORD)lpRecItem) - ((DWORD)&TransRecordData));

	return TRUE;
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
int rsRECORD_DBASE::ResotrRecordData(CharacterData *lpCharInfo, ItemData *lpItems, ItemData *lpItems2, ItemData *lpMouseItem)
{
	int cnt;
	int cnt2, cnt3;
	ItemData *lpChkItem[512];
	int		ChkCnt;
	int		CopyItemCount;
	int		BadItemCount;
	int		SetFlag;
	DWORD	dwItemCode;
	int		WeightError = 0;
	int		PostionError = 0;
	int		SvrPotionError = 0;
	int		ReformItemCount = 0;
	DWORD	dwCode;
	Item	*lpsItemInfo;

	BYTE	*lpRecItem;
	ItemData	*lpSaveItem;
	sRECORD_ITEM	sRecordItem;
	ItemData	sItem_Buff;
	int		PotionCnt;

	CheckCharForm();

	memcpy(lpCharInfo, &TransRecordData.sCharInfo, sizeof(CharacterData));
	lpCharInfo->bUpdateInfo[0] = 0;

	ResetClientRecordPotion(&TransRecordData.GameSaveInfo);

	CheckCharForm();

	ZeroMemory(lpItems, sizeof(ItemData) * INVENTORY_MAXITEM);
	ZeroMemory(lpItems2, sizeof(ItemData) * INVENTORY_MAXITEM);

	lpRecItem = (BYTE *)&TransRecordData.Data;

	ChkCnt = 0;
	CopyItemCount = 0;
	BadItemCount = 0;

	if (TransRecordData.GameSaveInfo.dwTime_PrimeItem_MightofAwell)
	{
		if (lpCharInfo->sWeight.sMin <0 || lpCharInfo->sWeight.sMin >lpCharInfo->sWeight.sMax + 300)
		{
			WeightError = TRUE;
			SendSetHackUser2(1900, lpCharInfo->sWeight.sMin);
		}
	}
	else if (TransRecordData.GameSaveInfo.dwTime_PrimeItem_MightofAwell2)
	{
		if (lpCharInfo->sWeight.sMin <0 || lpCharInfo->sWeight.sMin >lpCharInfo->sWeight.sMax + 500)
		{
			WeightError = TRUE;
			SendSetHackUser2(1900, lpCharInfo->sWeight.sMin);
		}
	}
	else
	{
		if (lpCharInfo->sWeight.sMin <0 || lpCharInfo->sWeight.sMin >lpCharInfo->sWeight.sMax)
		{
			WeightError = TRUE;
			SendSetHackUser2(1900, lpCharInfo->sWeight.sMin);
		}
	}

	for (cnt = 0; cnt < TransRecordData.ItemCount; cnt++)
	{
		lpsItemInfo = 0;
		DecodeCompress((BYTE *)lpRecItem, (BYTE *)&sRecordItem);

		SetFlag = TRUE;
		dwItemCode = sRecordItem.sItemInfo.sItemID.ToItemType();

		for (cnt2 = 0; cnt2 < TransRecordData.ThrowItemCount; cnt2++)
		{
			if (TransRecordData.ThrowItemInfo[cnt2].dwCode == sRecordItem.sItemInfo.sItemID.ToInt() && TransRecordData.ThrowItemInfo[cnt2].dwKey == sRecordItem.sItemInfo.iChk1 && TransRecordData.ThrowItemInfo[cnt2].dwSum == sRecordItem.sItemInfo.iChk2)
			{
				SetFlag = FALSE;
				break;
			}
		}
		if (sRecordItem.ItemPosition > 3 && sRecordItem.ItemPosition < 14)
		{
			dwCode = sRecordItem.sItemInfo.sItemID.ToInt() >> 24;
			if (dwCode == 1)
				PostionError++;

			dwCode = sRecordItem.sItemInfo.sItemID.ToInt() >> 16;
			if (dwCode == 0x0201 || dwCode == 0x0204 || dwCode == 0x0206 || dwCode == 0x0207)
				PostionError++;
		}

		if (sRecordItem.ItemPosition != 2 && sRecordItem.ItemPosition != 16 && CheckItemForm(&sRecordItem.sItemInfo) == FALSE)
		{
			SetFlag = FALSE;
			SendSetHackUser2(1950, 0);
		}
		if (!sRecordItem.sItemInfo.iChk1 || !sRecordItem.sItemInfo.iChk2)
		{
			if (sRecordItem.sItemInfo.szItemName[0])
			{
				SetFlag = FALSE;
				SendSetHackUser2(1950, 0);
			}
		}

		if (TransRecordData.GameSaveInfo.TT_ServerID)
		{
			if (sRecordItem.sItemInfo.sItemID.ToItemType() == sinBC1)
				SetFlag = FALSE;
		}

		if (sRecordItem.sItemInfo.sItemID.ToItemBase() == (sinPM1&sinITEM_MASK1))
		{
			if (sRecordItem.sItemInfo.iPotionCount <= 0)
				SetFlag = FALSE;
			else
			{
				PotionCnt = AddRecordPotion(sRecordItem.sItemInfo.sItemID.ToInt(), -sRecordItem.sItemInfo.iPotionCount);
				if (PotionCnt < 0)
				{
					sRecordItem.sItemInfo.iPotionCount += PotionCnt;
					SvrPotionError -= PotionCnt;

					if (sRecordItem.sItemInfo.iPotionCount <= 0)
						SetFlag = FALSE;
				}
			}
		}

		if (DeleteEventItem_TimeOut(&sRecordItem.sItemInfo) == TRUE)
		{
			SetFlag = FALSE;
			CHATGAMEHANDLE->AddChatBoxTextEx(CHATCOLOR_Error,
				"The item was deleted by the item( %s )'s time of validity", sRecordItem.sItemInfo.szItemName);

			if (sRecordItem.sItemInfo.sItemID.ToInt() == (sinOR2 | sin01) ||
				sRecordItem.sItemInfo.sItemID.ToInt() == (sinOA1 | sin32) ||
				sRecordItem.sItemInfo.sItemID.ToInt() == (sinOA1 | sin33) ||
				sRecordItem.sItemInfo.sItemID.ToInt() == (sinOA1 | sin34) ||
				sRecordItem.sItemInfo.sItemID.ToInt() == (sinOA1 | sin35) ||
				sRecordItem.sItemInfo.sItemID.ToInt() == (sinOA1 | sin36) ||
				sRecordItem.sItemInfo.sItemID.ToInt() == (sinOA1 | sin37) ||
				sRecordItem.sItemInfo.sItemID.ToInt() == (sinOA1 | sin39) ||
				sRecordItem.sItemInfo.sItemID.ToInt() == (sinOA1 | sin40) ||
				sRecordItem.sItemInfo.sItemID.ToInt() == (sinOA1 | sin41) ||
				sRecordItem.sItemInfo.sItemID.ToInt() == (sinOA1 | sin42) ||
				sRecordItem.sItemInfo.sItemID.ToInt() == (sinOA1 | sin38) ||
				sRecordItem.sItemInfo.sItemID.ToInt() == (sinDS1 | sin31) ||
				sRecordItem.sItemInfo.sItemID.ToInt() == (sinDS1 | sin32) ||
				sRecordItem.sItemInfo.sItemID.ToInt() == (sinDS1 | sin33))
				memcpy(&sItem_Buff.sItem, &sRecordItem.sItemInfo, sizeof(Item));
		}
		if (SetFlag)
		{
			if (dwItemCode != sinPM1 && dwItemCode != sinPL1 && dwItemCode != sinPS1)
			{
				for (cnt3 = 0; cnt3 < ChkCnt; cnt3++)
				{
					if (sRecordItem.sItemInfo.szItemName[0] && CompareItems(&sRecordItem.sItemInfo, &lpChkItem[cnt3]->sItem) == TRUE)
					{
						CopyItemCount++;
						break;
					}
				}
			}
			else
				cnt3 = ChkCnt;

			if (!sRecordItem.sItemInfo.Temp0)
				sRecordItem.sItemInfo.Temp0 = sRecordItem.sItemInfo.iChk2 + sRecordItem.sItemInfo.sItemID.ToInt();

			if (cnt3 >= ChkCnt)
			{
				if (cnt < TransRecordData.ItemSubStart)
					lpSaveItem = &lpItems[sRecordItem.ItemCount];
				else
					lpSaveItem = &lpItems2[sRecordItem.ItemCount];


				if (sRecordItem.ItemPosition == -1)
				{
					if (lpMouseItem)
						lpSaveItem = lpMouseItem;
					else
						lpSaveItem = &lpItems2[INVENTORY_MAXITEM - 1];

					sRecordItem.ItemPosition = 0;
				}

				lpSaveItem->iPlaceX = sRecordItem.x;
				lpSaveItem->iPlaceY = sRecordItem.y;
				lpSaveItem->iItemSlot = sRecordItem.ItemPosition;
				lpSaveItem->bValid = TRUE;
				memcpy(&lpSaveItem->sItem, &sRecordItem.sItemInfo, sizeof(Item));

				if (dwItemCode != sinPM1 && dwItemCode != sinPL1 && dwItemCode != sinPS1)
					lpChkItem[ChkCnt++] = lpSaveItem;
			}
		}
		lpRecItem += ((int *)lpRecItem)[0];
	}

	RestoreGameData(&TransRecordData.GameSaveInfo);

	if (TransRecordData.GameSaveInfo.iLastGold > 0)
	{
		CheckCharForm();
		lpCharInfo->iGold = TransRecordData.GameSaveInfo.iLastGold - 1;
		ReformCharForm();
	}

	if (CopyItemCount)
		SendCopyItemUser(CopyItemCount);
	if (BadItemCount)
		SendCopyItemUser(BadItemCount + 10000);

	if (PostionError)
	{
		PostionError += 10000;
		SendSetHackUser2(1900, PostionError);
		SendSetHackUser2(99, 0);
	}

	if (SvrPotionError)
	{
		SvrPotionError += 20000;
		SendSetHackUser2(1900, SvrPotionError);
		SendSetHackUser2(99, 0);
	}

	CheckCharForm();
	cInvenTory.LoadItemInfo();
	CheckCharForm();

	RestoreSkill(&TransRecordData.GameSaveInfo.sSkillInfo, TransRecordData.GameSaveInfo.dwLevelQuestLog);

	sinSkill.UseSkill[0].ShortKey = TransRecordData.GameSaveInfo.ShortKey_NormalAttack & 0xF;
	sinSkill.UseSkill[0].MousePosi = TransRecordData.GameSaveInfo.ShortKey_NormalAttack >> 4;

	if (TransRecordData.GameSaveInfo.wLifeBoosterUsing[0] && TransRecordData.GameSaveInfo.wLifeBoosterUsing[1])
	{
		cSkill.SetBoosterItem(sinBC1 + TransRecordData.GameSaveInfo.wLifeBoosterUsing[0], TransRecordData.GameSaveInfo.wLifeBoosterUsing[1] * 60);

		lpCurPlayer->dwLifeBoosterCode = sinBC1 + TransRecordData.GameSaveInfo.wLifeBoosterUsing[0];
		lpCurPlayer->dwLifeBoosterTime = dwPlayTime + (DWORD)TransRecordData.GameSaveInfo.wLifeBoosterUsing[1] * 1000;
	}
	if (TransRecordData.GameSaveInfo.wManaBoosterUsing[0] && TransRecordData.GameSaveInfo.wManaBoosterUsing[1])
	{
		cSkill.SetBoosterItem(sinBC1 + TransRecordData.GameSaveInfo.wManaBoosterUsing[0], TransRecordData.GameSaveInfo.wManaBoosterUsing[1] * 60);

		lpCurPlayer->dwManaBoosterCode = sinBC1 + TransRecordData.GameSaveInfo.wManaBoosterUsing[0];
		lpCurPlayer->dwManaBoosterTime = dwPlayTime + (DWORD)TransRecordData.GameSaveInfo.wManaBoosterUsing[1] * 1000;
	}
	if (TransRecordData.GameSaveInfo.wStaminaBoosterUsing[0] && TransRecordData.GameSaveInfo.wStaminaBoosterUsing[1])
	{
		cSkill.SetBoosterItem(sinBC1 + TransRecordData.GameSaveInfo.wStaminaBoosterUsing[0], TransRecordData.GameSaveInfo.wStaminaBoosterUsing[1] * 60);

		lpCurPlayer->dwStaminaBoosterCode = sinBC1 + TransRecordData.GameSaveInfo.wStaminaBoosterUsing[0];
		lpCurPlayer->dwStaminaBoosterTime = dwPlayTime + (DWORD)TransRecordData.GameSaveInfo.wStaminaBoosterUsing[1] * 1000;
	}
	if (TransRecordData.GameSaveInfo.wSkillDelayUsing[0] && TransRecordData.GameSaveInfo.wSkillDelayUsing[1])
	{
		cSkill.SetSkillDelayItem(sinBC1 + TransRecordData.GameSaveInfo.wSkillDelayUsing[0], TransRecordData.GameSaveInfo.wSkillDelayUsing[1] * 60);
		lpCurPlayer->dwSkillDelayCode = sinBC1 + TransRecordData.GameSaveInfo.wSkillDelayUsing[0];
		lpCurPlayer->dwSkillDelayTime = dwPlayTime + (DWORD)TransRecordData.GameSaveInfo.wSkillDelayUsing[1] * 1000;
	}
	if (TransRecordData.GameSaveInfo.wForceOrbUsing[0] && TransRecordData.GameSaveInfo.wForceOrbUsing[1])
	{
		if (TransRecordData.GameSaveInfo.wForceOrbUsing[0] >= sin01 && TransRecordData.GameSaveInfo.wForceOrbUsing[0] <= sin16)
			cInvenTory.SetForceOrb(sinFO1 + TransRecordData.GameSaveInfo.wForceOrbUsing[0], TransRecordData.GameSaveInfo.wForceOrbUsing[1]);

		lpCurPlayer->dwForceOrbCode = sinFO1 + TransRecordData.GameSaveInfo.wForceOrbUsing[0];
		lpCurPlayer->dwForceOrbTime = dwPlayTime + (DWORD)TransRecordData.GameSaveInfo.wForceOrbUsing[1] * 1000;
		AssaParticle_ShelltomWeapon(lpCurPlayer, (DWORD)TransRecordData.GameSaveInfo.wForceOrbUsing[1] * 70, ((TransRecordData.GameSaveInfo.wForceOrbUsing[0]) >> 8) - 1);
	}

	int	PrimeItem_Time;

	if (TransRecordData.GameSaveInfo.dwTime_PrimeItem_X2)
	{
		PrimeItem_Time = TransRecordData.GameSaveInfo.dwTime_PrimeItem_X2;//-GetPlayTime_T();
		if (PrimeItem_Time > 0)
		{
			chaPremiumitem.m_ThirdEyesTime = PrimeItem_Time;

			switch (TransRecordData.GameSaveInfo.dwPrimeItem_PackageCode)
			{
			case PRIME_ITEM_PACKAGE_NONE:
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::THIRD_EYES, chaPremiumitem.m_ThirdEyesTime, true, "Third Eye", 50);
				break;
			case PRIME_ITEM_PACKAGE_BRONZE:
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::THIRD_EYES, chaPremiumitem.m_ThirdEyesTime, true, "Third Eye", 20);
				break;
			case PRIME_ITEM_PACKAGE_SILVER:
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::THIRD_EYES, chaPremiumitem.m_ThirdEyesTime, true, "Third Eye", 30);
				break;
			case PRIME_ITEM_PACKAGE_GOLD:
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::THIRD_EYES, chaPremiumitem.m_ThirdEyesTime, true, "Third Eye", 40);
				break;
			case PRIME_ITEM_PACKAGE_ULTRA:
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::THIRD_EYES, chaPremiumitem.m_ThirdEyesTime, true, "Third Eye", 50);
				break;
			default:
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::THIRD_EYES, chaPremiumitem.m_ThirdEyesTime, true, "Third Eye", 50);
				break;
			}
		}
	}
	if (TransRecordData.GameSaveInfo.dwTime_PrimeItem_ExpUp)
	{
		PrimeItem_Time = TransRecordData.GameSaveInfo.dwTime_PrimeItem_ExpUp;//-GetPlayTime_T();
		if (PrimeItem_Time > 0)
		{
			chaPremiumitem.m_ExpUpPotionTime = PrimeItem_Time;

			switch (TransRecordData.GameSaveInfo.dwPrimeItem_PackageCode)
			{
			case PRIME_ITEM_PACKAGE_NONE:
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::EXPUP_POTION, chaPremiumitem.m_ExpUpPotionTime, true, "EXP Potion", 30);
				break;
			case PRIME_ITEM_PACKAGE_BRONZE:
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::EXPUP_POTION, chaPremiumitem.m_ExpUpPotionTime, true, "EXP Potion", 10);
				break;
			case PRIME_ITEM_PACKAGE_SILVER:
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::EXPUP_POTION, chaPremiumitem.m_ExpUpPotionTime, true, "EXP Potion", 20);
				break;
			case PRIME_ITEM_PACKAGE_GOLD:
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::EXPUP_POTION, chaPremiumitem.m_ExpUpPotionTime, true, "EXP Potion", 30);
				break;
			case PRIME_ITEM_PACKAGE_ULTRA:
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::EXPUP_POTION, chaPremiumitem.m_ExpUpPotionTime, true, "EXP Potion", 40);
				break;
			case PRIME_ITEM_PACKAGE_BRONZE2:
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::EXPUP_POTION, chaPremiumitem.m_ExpUpPotionTime, true, "EXP Potion", 10);
				break;
			case PRIME_ITEM_PACKAGE_SILVER2:
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::EXPUP_POTION, chaPremiumitem.m_ExpUpPotionTime, true, "EXP Potion", 20);
				break;
			case PRIME_ITEM_PACKAGE_GOLD2:
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::EXPUP_POTION, chaPremiumitem.m_ExpUpPotionTime, true, "EXP Potion", 30);
				break;
			case PRIME_ITEM_PACKAGE_ULTRA2:
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::EXPUP_POTION, chaPremiumitem.m_ExpUpPotionTime, true, "EXP Potion", 40);
				break;
			case PRIME_ITEM_PACKAGE_NONE_50_EXPUP:
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::EXPUP_POTION, chaPremiumitem.m_ExpUpPotionTime, true, "EXP Potion", 50);
				break;
			case PRIME_ITEM_PACKAGE_NONE_100_EXPUP:
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::EXPUP_POTION, chaPremiumitem.m_ExpUpPotionTime, true, "EXP Potion", 100);
				break;
			}
		}
	}

	if (TransRecordData.GameSaveInfo.dwTime_PrimeItem_VampCuspid)
	{
		PrimeItem_Time = TransRecordData.GameSaveInfo.dwTime_PrimeItem_VampCuspid;//-GetPlayTime_T();
		if (PrimeItem_Time > 0)
		{
			chaPremiumitem.m_VampiricCuspidTime = PrimeItem_Time;

			chaPremiumitem.SetUpKeepItem(nsPremiumItem::VAMPIRIC_CUS, chaPremiumitem.m_VampiricCuspidTime, true, "Vampire Teeth");

			cInvenTory.SetItemToChar();
		}
	}
	if (TransRecordData.GameSaveInfo.dwTime_PrimeItem_ManaRecharg)
	{
		PrimeItem_Time = TransRecordData.GameSaveInfo.dwTime_PrimeItem_ManaRecharg;//-GetPlayTime_T();
		if (PrimeItem_Time > 0)
		{
			chaPremiumitem.m_ManaRechargingPTime = PrimeItem_Time;

			chaPremiumitem.SetUpKeepItem(nsPremiumItem::MANA_RECHAR_P, chaPremiumitem.m_ManaRechargingPTime, true, "Mana Aura");

			cInvenTory.SetItemToChar();
		}
	}

	if (TransRecordData.GameSaveInfo.dwTime_PrimeItem_ManaReduce)
	{
		PrimeItem_Time = TransRecordData.GameSaveInfo.dwTime_PrimeItem_ManaReduce;//-GetPlayTime_T();
		if (PrimeItem_Time > 0)
		{
			chaPremiumitem.m_ManaReducePotiontime = PrimeItem_Time;

			switch (TransRecordData.GameSaveInfo.dwPrimeItem_PackageCode)
			{
			case PRIME_ITEM_PACKAGE_NONE:
				chaPremiumitem.m_ManaReducePotionValue = 30;
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, chaPremiumitem.m_ManaReducePotiontime, true, "MP Down", 30);
				break;
			case PRIME_ITEM_PACKAGE_BRONZE2:
				chaPremiumitem.m_ManaReducePotionValue = 10;
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, chaPremiumitem.m_ManaReducePotiontime, true, "MP Down", 10);
				break;
			case PRIME_ITEM_PACKAGE_SILVER2:
				chaPremiumitem.m_ManaReducePotionValue = 20;
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, chaPremiumitem.m_ManaReducePotiontime, true, "MP Down", 20);
				break;
			case PRIME_ITEM_PACKAGE_GOLD2:
				chaPremiumitem.m_ManaReducePotionValue = 30;
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, chaPremiumitem.m_ManaReducePotiontime, true, "MP Down", 30);
				break;
			case PRIME_ITEM_PACKAGE_ULTRA2:
				chaPremiumitem.m_ManaReducePotionValue = 40;
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, chaPremiumitem.m_ManaReducePotiontime, true, "MP Down", 40);
				break;
			default:
				chaPremiumitem.m_ManaReducePotionValue = 30;
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, chaPremiumitem.m_ManaReducePotiontime, true, "MP Down", 30);
				break;
			}
		}
	}
	if (TransRecordData.GameSaveInfo.dwTime_PrimeItem_MightofAwell)
	{
		PrimeItem_Time = TransRecordData.GameSaveInfo.dwTime_PrimeItem_MightofAwell;//-GetPlayTime_T();
		if (PrimeItem_Time > 0)
		{
			chaPremiumitem.m_MightofAwellTime = PrimeItem_Time;
			chaPremiumitem.m_MightofAwellWeight = 300;
			chaPremiumitem.SetUpKeepItem(nsPremiumItem::MIGHT_OF_AWELL, chaPremiumitem.m_MightofAwellTime, true, "Might of Awell", 300);
		}
	}
	if (TransRecordData.GameSaveInfo.dwTime_PrimeItem_MightofAwell2)
	{
		PrimeItem_Time = TransRecordData.GameSaveInfo.dwTime_PrimeItem_MightofAwell2;//-GetPlayTime_T();
		if (PrimeItem_Time > 0)
		{
			chaPremiumitem.m_MightofAwellTime = PrimeItem_Time;
			chaPremiumitem.m_MightofAwellWeight = 500;
			chaPremiumitem.SetUpKeepItem(nsPremiumItem::MIGHT_OF_AWELL, chaPremiumitem.m_MightofAwellTime, true, "Might of Awell", 500);
		}
	}
	if (TransRecordData.GameSaveInfo.dwTime_PrimeItem_HelpPet)
	{
		PrimeItem_Time = TransRecordData.GameSaveInfo.dwTime_PrimeItem_HelpPet;//-GetPlayTime_T();
		if (PrimeItem_Time > 0)
		{
			chaPremiumitem.SetHelpPetTimeTime(PrimeItem_Time);

			switch (cHelpPet.PetKind)
			{
			case 1:
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::HELP_PET_TERRY, chaPremiumitem.m_HelpPetTime, true, "Dragon Pet");
				break;
			case 2:
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::HELP_PET_NEPSYS, chaPremiumitem.m_HelpPetTime, true, "Dragon Pet");
				break;
			case 3:
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::HELP_PET_IO, chaPremiumitem.m_HelpPetTime, true, "Dragon Pet");
				break;
			case 4:
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::HELP_PET_MUTE, chaPremiumitem.m_HelpPetTime, true, "Dragon Pet");
				break;
			}
			for (int m = 0; m < SINUPKEEPITEM_MAX; m++)
			{
				if (chaPremiumitem.UpKeepItem[m].TGAImageNumber == nsPremiumItem::HELP_PET_TERRY)
					lpCharInfo->GravityScroolCheck[1] = 1;
			}
			cHelpPet.ShowPet();
		}
	}
	if (TransRecordData.GameSaveInfo.dwTime_PrimeItem_StaminaReduce)
	{
		PrimeItem_Time = TransRecordData.GameSaveInfo.dwTime_PrimeItem_StaminaReduce;//-GetPlayTime_T();
		if (PrimeItem_Time > 0)
		{
			chaPremiumitem.m_StaminaReducePotiontime = PrimeItem_Time;
			chaPremiumitem.m_StaminaReducePotionValue = 30;

			chaPremiumitem.SetUpKeepItem(nsPremiumItem::STAMINA_REDUCE_P, chaPremiumitem.m_StaminaReducePotiontime, true, "SP Down", 30);

		}
	}
	int IsBigMode = FALSE;

	if (TransRecordData.GameSaveInfo.dwTime_PrimeItem_BigHead)
	{
		PrimeItem_Time = TransRecordData.GameSaveInfo.dwTime_PrimeItem_BigHead;//-GetPlayTime_T();

		if (PrimeItem_Time > 0)
		{
			if (TransRecordData.GameSaveInfo.dwPrimeItem_BigHead)
			{
				ChangeModelSkin(lpCurPlayer, 1, TransRecordData.GameSaveInfo.dwPrimeItem_BigHead + 4, 0, 0);
				ReformCharForm();
				SetBigHeadToImage(TransRecordData.GameSaveInfo.dwPrimeItem_BigHead, PrimeItem_Time);
				cInvenTory.SetItemToChar();
				IsBigMode = TRUE;
			}
		}
	}
	if (IsBigMode == FALSE)
	{
		ChangeModelSkin(lpCurPlayer, 0, lpCurPlayer->sCharacterData.iRank, 0, GetFaceHairSkin(lpCurPlayer));
		ReformCharForm();
	}
	return TRUE;
}
//发送保存数据到服务器
int rsRECORD_DBASE::SendRecordDataToServer(smWINSOCK *lpsmSock)
{
	int cnt;
	int PartTotal;
	char *lpData;
	int TotalLen;
	int len;

	TRANS_RECORD_DATAS TransRecord;
	CharacterFile *lpTransRecord;

	lpTransRecord = &TransRecordData;
	lpData = (char *)lpTransRecord;

	cnt = 0;
	TotalLen = 0;
	PartTotal = lpTransRecord->iLength / TRANS_RECORD_LEN;
	if ((lpTransRecord->iLength % TRANS_RECORD_LEN) != 0)
	{
		if (lpTransRecord->iLength > TRANS_RECORD_LEN)
			PartTotal++;
	}

	while (1)
	{
		len = lpTransRecord->iLength - TotalLen;
		if (len > TRANS_RECORD_LEN)
			len = TRANS_RECORD_LEN;

		TransRecord.code = smTRANSCODE_RECORDDATA;
		TransRecord.size = len + 32;
		TransRecord.Count = cnt;
		TransRecord.Total = PartTotal;
		TransRecord.TransSize = len;

		memcpy(TransRecord.szData, &lpData[TotalLen], len);

		SENDPACKETL(&TransRecord);
		cnt++;

		TotalLen += len;
		if (TotalLen >= lpTransRecord->iLength)
			break;
	}

	return TRUE;
}


extern int RecordHackLogMoney(CharacterData *lpCharInfo);

#define	RECORD_ITEM_INFO_HEAD_SIZE		44

int rsRECORD_DBASE::RecvRecordDataFromServer(TRANS_RECORD_DATAS *lpTransRecord)
{
	char *lpData;
	int cnt;

	lpData = (char *)&TransRecordData;

	memcpy(&lpData[lpTransRecord->Count*TRANS_RECORD_LEN], lpTransRecord->szData, lpTransRecord->TransSize);
	TransDataBlock[lpTransRecord->Count] = 1;

	for (cnt = 0; cnt < lpTransRecord->Total; cnt++)
	{
		if (!TransDataBlock[cnt])
			break;
	}

	if (cnt == lpTransRecord->Total && TransRecordData.iHeader == smTRANSCODE_RECORDDATA)
	{
		TransRecordData.iHeader = 0;
		return TRUE;
	}

	TransLastPartCount = lpTransRecord->Count;

	return FALSE;
}


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

int RecordDeleteCharacterError(char *szID, char *szName);

#include	"checkname.h"

int rsRECORD_DBASE::IsData(char *szName)
{
	char	szFile[256];
	WIN32_FIND_DATA		ffd;
	HANDLE				hFind;

	if (lstrlen(szName) >= CHAR_NAME_MAXLEN)
		return TRUE;

	if (!c_CheckName(".\\CharacterNameList", szName))
		return TRUE;

	GetUserDataFile(szName, szFile, sizeof(szFile));

	hFind = FindFirstFile(szFile, &ffd);
	FindClose(hFind);
	if (hFind != INVALID_HANDLE_VALUE)
		return TRUE;

	return FALSE;
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
		//农府萍漠 冀记 秦力
		LeaveCriticalSection(&cRecDataSection);

		//汗荤等 单捞鸥甫 窍靛叼胶农俊 历厘茄促
		//农府萍漠 冀记 急攫
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
		//农府萍漠 冀记 秦力
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

int PeekMonMsg();
int	MonQuit = 0;
HWND hDialog;
HWND hWndMon;
extern HINSTANCE hinst;

#define RECORD_MONEY_LIMIT		100000


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
								wsprintf(szLogBuff, "%s (%s) -> 角菩 ( 脚痹某腐捞粮犁 )\r\n", decode, strBuff);
								fwrite(szLogBuff, lstrlen(szLogBuff), 1, fp3);
							}
						}

						if (flag)
						{
							wsprintf(szFile, "BackupUser\\%s.dat", strBuff);
							CopyFile(szDestDataFile, szFile, TRUE);

							CopyFile(szSrcDataFile, szDestDataFile, FALSE);

							wsprintf(szLogBuff, "%s (%s) -> 己傍\r\n", decode, strBuff);
							fwrite(szLogBuff, lstrlen(szLogBuff), 1, fp3);
						}
					}
					else
					{
						wsprintf(szLogBuff, "%s (%s) -> 角菩 ( 拌沥捞绝澜 )\r\n", decode, strBuff);
						fwrite(szLogBuff, lstrlen(szLogBuff), 1, fp3);
					}
				}
				else
				{
					wsprintf(szLogBuff, "%s (%s) -> 角菩 ( 家胶颇老绝澜 )\r\n", decode, strBuff);
					fwrite(szLogBuff, lstrlen(szLogBuff), 1, fp3);
				}
			}
		}
	}

	fclose(fp3);
	fclose(fp);

	return TRUE;
}