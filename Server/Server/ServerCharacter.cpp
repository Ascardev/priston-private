#include "StdAfx.h"
#include "ServerCharacter.h"

CServerCharacter::CServerCharacter()
{

}
CServerCharacter::~CServerCharacter()
{

}
char * CServerCharacter::GetServerName(User * pcUser)
{
	return SERVERINFO->GetServerName(pcUser->iServerIndexID);
}
char * CServerCharacter::GetCharacterName(User * pcUser)
{
	if (!GAME_SERVER)
		return pcUser->szCharacterName;

	return pcUser->sCharacterData.szName;
}
BOOL CServerCharacter::CharacterInCityStage(User * pcUser)
{
	if (pcUser)
	{
		if (pcUser->iMapID < 0 || pcUser->iMapID > NUM_MAPS)
			return TRUE;

		switch (pcUser->iMapID)
		{
		case MAPID_RicartenTown:
		case MAPID_PhillaiTown:
		case MAPID_BattleTown:
			return TRUE;
		}
	}

	return FALSE;
}
int CServerCharacter::SQLGetCharacterClass(char * pszCharacterName)
{
	int iClass = 0;

	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB_2);

	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT JobCode FROM CharacterInfo WHERE Name=?"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_String, pszCharacterName, STRLEN(pszCharacterName));

			if (pcDB->Execute() && pcDB->Fetch())
				pcDB->GetData(1, PARAMTYPE_Integer, &iClass);
		}
		pcDB->Close();
	}

	return iClass;
}
int CServerCharacter::SQLGetCharacterID(char * pszName)
{
	int iID = -1;

	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);

	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT ID FROM CharacterInfo WHERE Name=?"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_String, pszName, STRLEN(pszName));

			if (pcDB->Execute() && pcDB->Fetch())
				pcDB->GetData(1, PARAMTYPE_Integer, &iID);
		}

		pcDB->Close();
	}

	return iID;
}
int CServerCharacter::SQLGetCharacterClanID(char * pszCharacterName)
{
	int iID = -1;

	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);

	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT ClanID FROM CharacterInfo WHERE Name=?"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_String, pszCharacterName, STRLEN(pszCharacterName));

			if (pcDB->Execute() && pcDB->Fetch())
			{
				pcDB->GetData(1, PARAMTYPE_Integer, &iID);
			}
		}

		pcDB->Close();
	}

	return iID;
}
BOOL CServerCharacter::IsCharacterLeader(User * pcUser)
{
	BOOL bRet = FALSE;
	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_ClanDB);
	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT ID FROM ClanList WHERE ClanLeader=?"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_String, GetCharacterName(pcUser));
			if (pcDB->Execute() && pcDB->Fetch())
				bRet = TRUE;
		}
		pcDB->Close();
	}
	return bRet;
}
void CServerCharacter::SetExp(User * pcUser, INT64 iExp)
{
	int iLevelCap = UNIT_LEVEL_MAX;
	if (pcUser->iGameLevel >= GAMELEVEL_Two)
		iLevelCap = 160;

	if (pcUser && !GAME_SERVER)
	{
		pcUser->liEXP.QuadPart = iExp;
		INT64 iExpMax = GetExpFromLevel(iLevelCap);

		if (pcUser->liEXP.QuadPart > iExpMax)
			pcUser->liEXP.QuadPart = iExpMax;
	}
}
void CServerCharacter::GiveEXP(User * pcUser, INT64 iExp)
{
	if (pcUser)
	{
		INT64 iExpCharacter = GetExp(pcUser) + iExp;
		INT64 iExpCharacterOld = GetExp(pcUser);

		if (GAME_SERVER)
			SERVERNET->GiveEXP(pcUser, iExp);
		else
		{
			SetExp(pcUser, iExpCharacter);
			PacketExperience sPacket;
			ZeroMemory(&sPacket, sizeof(PacketExperience));
			sPacket.iLength = sizeof(PacketExperience);
			sPacket.iHeader = PKTHDR_AddExp;
			sPacket.iAddExp = GetExp(pcUser) - iExpCharacterOld;
			SENDPACKET(pcUser, &sPacket);
		}
	}
}
INT64 CServerCharacter::GetExpFromLevel(int iLevel)
{
	return uUnitExpTables[iLevel - 1];
}
INT64 CServerCharacter::GetExp(User * pcUser)
{
	return pcUser ? pcUser->liEXP.QuadPart : 0;
}
int CServerCharacter::GetLevelFromExp(INT64 iExp)
{
	for (int i = 0; i < UNIT_LEVEL_MAX; i++)
	{
		if (iExp >= uUnitExpTables[i] && iExp < uUnitExpTables[i + 1])
			return i + 1;
	}

	return 1;
}
int CServerCharacter::GetStatePointFromQuestLevel(int iLevel, DWORD dwQuestLevel)
{
	int iPoint = 0;

	if (dwQuestLevel & QUESTBIT_LEVEL_30 && iLevel >= 30)
		iPoint += 5;
	if (dwQuestLevel & QUESTBIT_LEVEL_70 && iLevel >= 70)
		iPoint += 5;
	if (dwQuestLevel & QUESTBIT_LEVEL_80 && iLevel >= 80)
		iPoint += 5;
	if (dwQuestLevel & QUESTBIT_LEVEL_80_2 && iLevel >= 80)
		iPoint += (iLevel - 79) * 2;
	if (dwQuestLevel & QUESTBIT_LEVEL_90_2 && iLevel >= 90)
		iPoint += (iLevel - 89) * 3;

	return iPoint;
}
int CServerCharacter::GetSkillPointFromQuestLevel(int iLevel, DWORD dwQuestLevel)
{
	int iPoint = 0;

	if (dwQuestLevel & QUESTBIT_LEVEL_55 && iLevel >= 55)
		iPoint++;
	if (dwQuestLevel & QUESTBIT_LEVEL_70 && iLevel >= 70)
		iPoint++;
	if (dwQuestLevel & QUESTBIT_LEVEL_80 && iLevel >= 80)
		iPoint += 2;

	return iPoint;
}
BOOL CServerCharacter::CheckCharacterStatePoint(CharacterData *psCharacterData, DWORD dwQuestLevel)
{
	int iTotalPoint = abs(psCharacterData->iStrength) +
		abs(psCharacterData->iSpirit) +
		abs(psCharacterData->iTalent) +
		abs(psCharacterData->iAgility) +
		abs(psCharacterData->iHealth);

	int iPoint = 99 + ((psCharacterData->iLevel - 1) * 5) +
		GetStatePointFromQuestLevel(psCharacterData->iLevel, dwQuestLevel);

	psCharacterData->iStatPoints = iPoint - iTotalPoint;

	if (psCharacterData->iStatPoints <= -10)
	{
		for (int i = 0; i < _countof(sCharacterDataState); i++)
		{
			if (psCharacterData->iClass == sCharacterDataState[i].iClass)
			{
				psCharacterData->iStrength = sCharacterDataState[i].iStrength;
				psCharacterData->iSpirit = sCharacterDataState[i].iSpirit;
				psCharacterData->iTalent = sCharacterDataState[i].iTalent;
				psCharacterData->iAgility = sCharacterDataState[i].iAgility;
				psCharacterData->iHealth = sCharacterDataState[i].iHealth;
				psCharacterData->iStatPoints = 0;
			}
		}

		return FALSE;
	}
	else if (psCharacterData->iStatPoints < 0)
		psCharacterData->iStatPoints = 0;

	return TRUE;
}
BOOL CServerCharacter::CheckCharacterSkillPoint(int iLevel, RecordSkill *pSkill, DWORD dwQuestLevel)
{
	int iNPoint = 0;

	for (int i = 0; i < 12; i++)
	{
		if (pSkill->bSkillPoint[i] > 10)
			return FALSE;

		iNPoint += abs(pSkill->bSkillPoint[i]);
	}

	int iEPoint = 0;

	for (int i = 12; i < 20; i++)
	{
		if (pSkill->bSkillPoint[i] > 10)
			return FALSE;

		iEPoint += abs(pSkill->bSkillPoint[i]);
	}

	if (iLevel >= 10)
	{
		int iPoint = ((iLevel - 8) / 2) - iNPoint;

		iPoint += GetSkillPointFromQuestLevel(iLevel, dwQuestLevel);

		if (iPoint < 0)
			return FALSE;
	}
	else
	{
		if (iNPoint > 0)
			return FALSE;
	}

	if (iLevel >= 60)
	{
		int iPoint = ((iLevel - 58) / 2) - iEPoint;

		if (iPoint < 0)
			return FALSE;
	}
	else
	{
		if (iEPoint > 0)
			return FALSE;
	}

	return TRUE;
}
void CServerCharacter::OnLoseExp(User * pcUser, PacketLoseExperience * psPacket)
{
	int iLevelCap = UNIT_LEVEL_MAX;
	if (pcUser->iGameLevel >= GAMELEVEL_Two)
		iLevelCap = 160;

	// User alive and not in city maps and not in Bless Castle?
	if (pcUser && pcUser->pcSocketData && psPacket->iLevel > 0 && psPacket->iLevel < iLevelCap)
	{
		LARGE_INTEGER liEXPLevel;

		liEXPLevel.QuadPart = GetExpFromLevel(psPacket->iLevel);

		INT64 iEXP = GetExpFromLevel(psPacket->iLevel + 1) - liEXPLevel.QuadPart;

		// Is Hack or bug?
		if (psPacket->iSubExp < 0)
			return;

		INT64 iExpCharacter = pcUser->liEXP.QuadPart - 0;

		if (psPacket->iPercent > 0 && psPacket->iPercent <= 3)
		{
			INT64 iExpLose = (INT64)round(((double)iEXP * psPacket->iPercent) / (double)100);

			iEXP = pcUser->liEXP.QuadPart - iExpLose;

			if (iEXP < liEXPLevel.QuadPart)
			{
				iEXP = liEXPLevel.QuadPart;
				iExpLose = pcUser->liEXP.QuadPart - liEXPLevel.QuadPart;
			}

			iExpCharacter = pcUser->liEXP.QuadPart - iExpLose;

			if (iExpCharacter < liEXPLevel.QuadPart)
				iExpCharacter = liEXPLevel.QuadPart;

			SetExp(pcUser, iExpCharacter);

			psPacket->iSubExp = iExpLose;

			SENDPACKET(pcUser, psPacket);
		}
	}
}
void CServerCharacter::SetPositionWarp(User * pcUser, int iX, int iZ, int iStageID)
{
	if (pcUser)
	{
		PacketWarpGateField sPacket;
		sPacket.iLength = sizeof(PacketWarpGateField);
		sPacket.iHeader = PKTHDR_WarpGateField;
		sPacket.iStage = iStageID != -1 ? iStageID : pcUser->iMapID;
		sPacket.iX = iX;
		sPacket.iZ = iZ;
		SENDPACKET(pcUser, &sPacket);

		if (iStageID != -1)
			pcUser->iMapID = (EMapID)iStageID;

		pcUser->sPosition.iX = iX;
		pcUser->sPosition.iZ = iZ;
	}
}
void CServerCharacter::GiveGold(User * pcUser, int iGold, EWhereAction eWhere)
{
	if (pcUser)
	{
		if (GAME_SERVER)
			SERVERNET->GiveGold(pcUser, iGold);
		else
		{
			if (iGold > 0)
				SERVERUSER->AddServerUserGold(pcUser, iGold, eWhere);

			if (iGold < 0)
				SERVERUSER->SubServerUserGold(pcUser, abs(iGold), eWhere);

			PacketSetCharacterGold sPacket;
			sPacket.iLength = sizeof(PacketSetCharacterGold);
			sPacket.iHeader = PKTHDR_SetGold;
			sPacket.dwGold = pcUser->GetGold();
			SENDPACKET(pcUser, &sPacket);
		}
	}
}
void CServerCharacter::UpdateForceOrb(User * pcUser)
{
	if (pcUser && pcUser->iID)
	{
		if (GAME_SERVER)
		{
			if (!CharacterInCityStage(pcUser))
			{
				// Send that now is in city stage
				if (!pcUser->dwLastForceTime)
				{
					pcUser->dwLastForceTime = TICKCOUNT;
				}

				// Update Time? update force
				if (pcUser->iForceOrbTime > 0)
				{
					DWORD dwTime = (TICKCOUNT - pcUser->dwLastForceTime);
					pcUser->iForceOrbTime -= 1000;
					if (pcUser->iForceOrbTime <= 2)
						pcUser->iForceOrbTime = 0;
					pcUser->dwLastForceTime = TICKCOUNT;
					if ((pcUser->iForceOrbTime % 2000) == 0)
						SERVERNET->SendForceOrb(pcUser, TRUE);
				}
			}
		}
	}
}
void CServerCharacter::UpdatePremiumTimer(User * pcUser)
{
	if (pcUser && pcUser->pcSocketData)
	{
		DWORD dwLag = TICKCOUNT - pcUser->pcSocketData->dwTimeLastPacketReceived;

		if (GAME_SERVER && dwLag <= 10000)
		{
			if (!CharacterInCityStage(pcUser))
			{
				for (int i = 0; i < PREMIUM_ITEM_TOTAL; i++)
				{
					ItemPremium * psItem = &pcUser->sPremiumData.saItemList[i];

					if (psItem->eType == ITEMTIMERTYPE_ExpUp || psItem->eType == ITEMTIMERTYPE_ThirdEye)
					{
						if (pcUser->GetMapID() == MAPID_BlessCastle)
							continue;
					}

					if (psItem->dwCode && psItem->dwTimeLeft)
					{
						if (psItem->dwTimeLeft <= 2)
						{
							psItem->dwTimeLeft = 0;

							//if (psItem->eType == ITEMTIMERTYPE_ExpUp)
								//SERVERNET->SendEXPPotion(pcUser, FALSE);

							SERVERITEM->UpdateItemTimer(pcUser);
						}
						else
						{
							psItem->dwTimeLeft -= 1;
						}
					}
				}
			}
		}
	}
}
void CServerCharacter::CheckGold(User * pcUser)
{
	if (!GAME_SERVER && pcUser)
	{
		if (pcUser->pData.dwGold != pcUser->iInventoryGold && !pcUser->bWarehouseOpen)
		{

		}
		if (pcUser->iInventoryGold == -150000000)
		{
			SERVERLOG->LogSocketClose(pcUser->pcSocketData, "CharacterServer::CheckGold()", _ReturnAddress());
			WNDPROC_SOCKETCLOSE(SERVERSOCKET->GetHWND(), pcUser->pcSocketData);
		}
	}
}
void CServerCharacter::OnCharacterSyncData(User * pcUser)
{
	SERVERUSER->DisconnectUser(pcUser);

	char szMessageLogin[128] = { 0 };

	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_ServerDB);

	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT Message FROM MessageLogin"))
		{
			if (pcDB->Execute())
			{
				while (pcDB->Fetch())
				{
					pcDB->GetData(1, PARAMTYPE_String, szMessageLogin, 128);
					SERVERCHAT->SendChat(pcUser, CHATCOLOR_Global, szMessageLogin);
				}
			}
		}
		pcDB->Close();
	}

	SERVERUSER->SetUserID(pcUser);
	SERVERUSER->DeleteReconnectUser(pcUser->szAccountName);

	SERVERNET->GetGameMaster(pcUser);

	SERVERITEM->OnLoadUser(pcUser);

	SERVERUSER->UpdateID(pcUser);

	SendCharacterDataEx(pcUser);

	// Online Status
	pcDB = SQLCONNECTION(DATABASEID_UserDB);

	if (pcDB->Open())
	{
		if (pcDB->Prepare("UPDATE CharacterInfo SET IsOnline=1, JobCode=? WHERE Name=?"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_Integer, &pcUser->sCharacterData.iClass);
			pcDB->BindParameterInput(2, PARAMTYPE_String, GetCharacterName(pcUser));
			pcDB->Execute();
		}
		pcDB->Close();
	}

	// Clan Message
	int iClanID = 0;
	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT ClanID FROM CharacterInfo WHERE Name=?"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_String, pcUser->sCharacterData.szName);
			if (pcDB->Execute() && pcDB->Fetch())
			{
				pcDB->GetData(1, PARAMTYPE_Integer, &iClanID, 0);
			}
		}
		pcDB->Close();
	}

	pcDB = SQLCONNECTION(DATABASEID_ClanDB);

	if (iClanID > 0)
	{
		char szClanMessage[128];
		if (pcDB->Open())
		{
			if (pcDB->Prepare("SELECT LoginMessage FROM ClanList WHERE ID=?"))
			{
				pcDB->BindParameterInput(1, PARAMTYPE_Integer, &iClanID);
				if (pcDB->Execute() && pcDB->Fetch())
				{
					pcDB->GetData(1, PARAMTYPE_String, szClanMessage, 128);
				}
			}
			pcDB->Close();
		}

		if (!IsNull(szClanMessage))
		{
			SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Clan, "> %s", szClanMessage);
		}
	}

	// Get Item Box
	int iItemsBox = DISTRIBUTORHANDLE->SQLItemBoxCount(pcUser);
	if (iItemsBox > 0)
	{
		SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Global, "> You have %d item%s in Item Distributor!", iItemsBox, iItemsBox == 1 ? "" : "s");
	}
	// Get Coin Amount
	int iCoinAmount = COINSHOPHANDLE->GetCoinAmount(pcUser->szAccountName);
	if (iCoinAmount > 0)
	{
		SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Global, "> You have %d credits!", iCoinAmount);
	}

	std::vector<std::string> vNotification = SERVERACCOUNT->SQLGetAccountNotification(pcUser->szAccountName);
	if (vNotification.size() > 0)
	{
		SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Error, "> You have %d new notification%s:", vNotification.size(), vNotification.size() > 1 ? "s" : "");

		for (auto &str  : vNotification)
		{
			SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Error, "> %s", str.c_str());
		}
	}

	SERVERBLESSCASTLE->SendUserScore(pcUser);
}
void CServerCharacter::OnCharacterSyncDataEx(User * pcUser, PacketPlayDataEx * psPacket)
{
	SERVERNET->SendClan(pcUser);
	memcpy(&pcUser->pData, psPacket, sizeof(PacketPlayDataEx));

	pcUser->sCharacterData.iStrength = pcUser->pData.sCharacterData.iStrength;
	pcUser->sCharacterData.iSpirit = pcUser->pData.sCharacterData.iSpirit;
	pcUser->sCharacterData.iTalent = pcUser->pData.sCharacterData.iTalent;
	pcUser->sCharacterData.iAgility = pcUser->pData.sCharacterData.iAgility;
	pcUser->sCharacterData.iHealth = pcUser->pData.sCharacterData.iHealth;
	pcUser->sCharacterData.iAccuracy = pcUser->pData.sCharacterData.iAccuracy;
	pcUser->sCharacterData.iAttackRating = pcUser->pData.sCharacterData.iAttackRating;
	pcUser->sCharacterData.iMinDamage = pcUser->pData.sCharacterData.iMinDamage;
	pcUser->sCharacterData.iMaxDamage = pcUser->pData.sCharacterData.iMaxDamage;
	pcUser->sCharacterData.iAttackSpeed = pcUser->pData.sCharacterData.iAttackSpeed;
	pcUser->sCharacterData.iCritical = pcUser->pData.iCritical;

	if (pcUser->iGameLevel == GAMELEVEL_None)
	{
		if (!GAME_SERVER && psPacket->dwSpeed >= ((((25 * 10) + 250) * 460) >> 8))
		{
			PacketLogCheat sPacket;
			sPacket.iCheatID = CHEATLOGID_RunSpeedHack;
			sPacket.iLParam = psPacket->dwSpeed;
			SERVERLOG->LogCheat(pcUser, &sPacket);
			return;
		}
	}

	UpdateForceOrb(pcUser);

	// Check Gold
	CheckGold(pcUser);

	// Not Game Master?
	if (pcUser->pData.bGameMaster && !pcUser->iGameLevel)
	{
		if (pcUser->bCheckedGameMaster)
		{
			PacketLogCheat sPacket;
			sPacket.iCheatID = CHEATLOGID_FakeGM;
			SERVERLOG->LogCheat(pcUser, &sPacket);
		}
		else
			pcUser->bCheckedGameMaster = TRUE;
	}
	if (!pcUser->pData.bGameMaster)
		pcUser->bCheckedGameMaster = FALSE;

	if (!pcUser->dwTimeSync)
	{
		pcUser->dwTimeSync = TICKCOUNT;
	}

	// Server ID
	pcUser->iServerIndexID = psPacket->dwServerID;

	// Login Server?
	if (GAME_SERVER)
	{
		// Send server information to user debug
		PacketServerInfo sPacket;
		ZeroMemory(&sPacket, sizeof(PacketServerInfo));
		sPacket.iLength = sizeof(PacketServerInfo);
		sPacket.iHeader = PKTHDR_ServerInfo;
		sPacket.iUsers = pcUser->iGameLevel > 0 ? USERS_ONLINE : 0;
		sPacket.iMaxUsers = pcUser->iGameLevel > 0 ? MAX_USERS : 0;
		sPacket.iBossTime = 0;
		sPacket.iServerVersion = SERVER_VERSION;
		sPacket.bSiegeWarType = SERVERBLESSCASTLE->GetSiegeWarMode();
		sPacket.sSiegeWarDay = EVENT_BLESSCASTLE_DAY;
		sPacket.sSiegeWarHour = EVENT_BLESSCASTLE_HOUR;
		GetSystemTime(&sPacket.sServerTime);

		if (pcUser->iGameLevel)
			sPacket.bGameMaster = TRUE;

		SENDPACKET(pcUser, &sPacket);
	}

	// Check State Hack
	//CHEATSERVER->CheckStatePoint(pcUser, psPacket->dwQuestLevelLog);
}
void CServerCharacter::GiveGameMaster(User * pcUser, int iGameLevel)
{
	PacketSimple sPacket;
	ZeroMemory(&sPacket, sizeof(PacketSimple));

	sPacket.iLength = sizeof(PacketSimple);
	sPacket.iHeader = PKTHDR_GameMasterStatus;
	sPacket.iUnk = pcUser->iGameLevel;

	SENDPACKET(pcUser, &sPacket);
}
void CServerCharacter::OnCharacterDataExSave(User * pcUser)
{
	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);

	if (pcDB->Open())
	{
		if (pcDB->Prepare("UPDATE CharacterInfo SET FSP=? WHERE Name=?"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_Integer, &pcUser->sCharacterDataEx.iFSP);
			pcDB->BindParameterInput(2, PARAMTYPE_String, GetCharacterName(pcUser), STRLEN(GetCharacterName(pcUser)));
			pcDB->Execute();
		}
		pcDB->Close();
	}
}
void CServerCharacter::HandlePacket(User * pcUser, PacketCharacterDataEx * psPacket)
{
	CopyMemory(&pcUser->sCharacterDataEx, &psPacket->sData, sizeof(CharacterDataEx));
	SERVERCHAT->SendDebugChat(pcUser, CHATCOLOR_Error, "> SaveEx Success");
}
void CServerCharacter::SendCharacterDataEx(User * pcUser)
{
	if (pcUser)
	{
		PacketCharacterDataEx s;
		ZeroMemory(&s, sizeof(PacketCharacterDataEx));
		s.iLength = sizeof(PacketCharacterDataEx);
		s.iHeader = PKTHDR_CharacterDataEx;

		SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);

		if (pcDB->Open())
		{
			if (pcDB->Prepare("SELECT OldHead, FSP FROM CharacterInfo WHERE ID=?"))
			{
				pcDB->BindParameterInput(1, PARAMTYPE_Integer, &pcUser->iCharacterID);

				if (pcDB->Execute())
				{
					if (pcDB->Fetch())
					{
						pcDB->GetData(1, PARAMTYPE_String, s.sData.szOldHead, _countof(s.sData.szOldHead));
						pcDB->GetData(2, PARAMTYPE_Integer, &s.sData.iFSP);

						if (IsNull(s.sData.szOldHead))
							ZeroMemory(s.sData.szOldHead, _countof(s.sData.szOldHead));
					}
				}
			}
			pcDB->Close();
		}

		SENDPACKET(pcUser, &s);
	}
}
