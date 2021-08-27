#include "StdAfx.h"
#include "GameUnit.h"

CGameUnit::CGameUnit()
{
	//pcaUnit = new Unit[MAX_UNITS];
}
CGameUnit::~CGameUnit()
{
	//DELETA(pcaUnit);
}
void CGameUnit::ClearFarUnits()
{
	for (int i = 0; i < MAX_UNITS; i++)
	{
		Unit *pc = &chrOtherPlayer[i];

		if (pc->bActive)
		{
			BOOL bCanClose = FALSE;

			if (pc->dwLastTransTime + 8000 < TICKCOUNT)
				bCanClose = TRUE;

			int iX = (lpCurPlayer->pX - pc->pX) >> 8;
			int iZ = (lpCurPlayer->pZ - pc->pZ) >> 8;

			int iDist = iX * iX + iZ * iZ;

			if ((pc->DisplayFlag && iDist > 0x320000) || bCanClose)
			{
				pc->bActive = FALSE;
				pc->Close();
			}
		}
	}
}
void CGameUnit::AddExp(INT64 iExpNew)
{
	INT64 iExp = GetExp(UNIT);

	int iLevel = UNIT_LEVEL_MAX - 1;

	if (iExp < uUnitExpTables[iLevel])
		iExp += iExpNew;

	SetExp(UNIT, iExp);

	UPDATE_CHARACTER_CHECKSUM;

	iLevel = UNIT->sCharacterData.iLevel;

	INT64 iExpOld = uUnitExpTables[iLevel];

	if (iExpOld >= 0 && iExp >= iExpOld && iLevel < UNIT_LEVEL_MAX)
	{
		iLevel = GetLevelFromExp(iExp);
		UNIT->sCharacterData.iLevel = iLevel;
		StartEffect(UNIT->pX, UNIT->pY + 32 * 256, UNIT->pZ, EFFECT_LEVELUP1);
		esPlaySound(7, 400);

		UPDATE_CHARACTER_CHECKSUM;

		SendPlayUpdateInfo();
		SaveGameData();
	}
}
int CGameUnit::GetLevelFromExp(INT64 iExp)
{
	for (int i = 0; i < UNIT_LEVEL_MAX; i++)
	{
		if (iExp >= uUnitExpTables[i] && iExp < uUnitExpTables[i + 1])
			return i + 1;
	}

	return 1;
}
INT64 CGameUnit::GetExpFromLevel(int iLevel)
{
	if (iLevel > 0 && iLevel < UNIT_LEVEL_MAX)
	{
		return uUnitExpTables[iLevel - 1];
	}

	return 0;
}
void CGameUnit::SetExp(Unit *pcUnit, INT64 iExp)
{
	LARGE_INTEGER liExp;

	liExp.QuadPart = iExp;

	pcUnit->sCharacterData.iExp = liExp.HighPart;
	pcUnit->sCharacterData.iExp = liExp.LowPart;
}
INT64 CGameUnit::GetExp(Unit *pcUnit)
{
	if (pcUnit)
	{
		INT64 iExpL = pcUnit->sCharacterData.iExp;
		INT64 iExpH = pcUnit->sCharacterData.iExp;

		return (iExpH << 32) | (iExpL & 0xFFFFFFFF);
	}

	return 0;
}
void CGameUnit::ChecksumUpdate(Unit *pcUnit)
{
	if (pcUnit)
	{
		ReformCharForm(&pcUnit->sCharacterData);
	}
}
void CGameUnit::ChecksumCheck(Unit *pcUnit)
{
	
}
BOOL CGameUnit::OnLoseEXP()
{
	if (GAMECHARACTER->IsStageVillage() || MAP_ID == MAPID_BlessCastle || MAP_ID == MAPID_QuestArena ||
		MAP_ID == MAPID_Bellatra)

		return FALSE;

	INT64 iEXPCharacter = GetExp(UNIT);

	LARGE_INTEGER liEXPLevel;

	liEXPLevel.QuadPart = GetExpFromLevel(UNIT->sCharacterData.iLevel);

	INT64 iEXP = GetExpFromLevel(UNIT->sCharacterData.iLevel + 1) - liEXPLevel.QuadPart;

	return FALSE;
}
void CGameUnit::Fun()
{
	int i = (rand() % 8192) * 2;
	DWORD dwTable = GetTableNum(i);
	AddTimeEffect(SKILL_EFFECT_FIREFLOWER, dwPlayTime, (dwTable >> 24) & 0xFF, 0, 0, UNIT);
	AddTimeEffect(SKILL_EFFECT_FIREFLOWER, dwPlayTime + 500, (dwTable >> 16) & 0xFF, 0, 0, UNIT);
	AddTimeEffect(SKILL_EFFECT_FIREFLOWER, dwPlayTime + 1000, (dwTable >> 8) & 0xFF, 0, 0, UNIT);
	AddTimeEffect(SKILL_EFFECT_FIREFLOWER, dwPlayTime + 1500, dwTable & 0xFF, 0, 0, UNIT);

	UNIT->dwNextMotionCode = ANIMATIONTYPE_Yahoo;

	SendCommandUser(smCOMMNAD_USER_FIREFLOWER, i, 0, 0);
}
void CGameUnit::SendUnitDataEx()
{
	//Prepare Packet
	PacketPlayDataEx sPacket;
	ZeroMemory(&sPacket, sizeof(PacketPlayDataEx));
	sPacket.iLength = sizeof(PacketPlayDataEx);
	sPacket.iHeader = PKTHDR_PlayDataEx;
	sPacket.bGameMaster = SETTINGHANDLE->Get().bDebugMode;
	sPacket.iMapID = MAP_ID;

	// Skills levels
	//for (int i = 0; i < SKILL_COUNT_CHARACTER; i++)
		//sPacket.iLevelSkill[i] = SKILLSCHARACTER[i + 1].iLevel;
}
Unit * CGameUnit::GetUnitByID(ID lID)
{
	if (UNIT->iID == lID)
		return UNIT;

	for (int i = 0; i < MAX_UNITS; i++)
	{
		Unit * pcUnit = chrOtherPlayer + i;

		if (pcUnit->bActive && pcUnit->iID == lID)
			return pcUnit;
	}

	return nullptr;
}