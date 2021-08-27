#include "StdAfx.h"
#include "ServerPvP.h"

CServerPvP::CServerPvP()
{

}
CServerPvP::~CServerPvP()
{

}
void CServerPvP::OnKilled(User * pcKiller, User * pcVictim)
{
	BOOL bBlockKill = FALSE;

	if (pcKiller->pcSocketData->lIP == pcVictim->pcSocketData->lIP)
		bBlockKill = TRUE;

	if (pcKiller->dwLastKillIP == pcVictim->pcSocketData->lIP)
		bBlockKill = TRUE;
	else
		pcKiller->dwLastKillIP = pcVictim->pcSocketData->lIP;

	if (pcKiller->iClanID != 0 && pcVictim->iClanID != 0 && (pcKiller->iClanID == pcVictim->iClanID))
	{
		bBlockKill = TRUE;
	}

	if (bBlockKill == FALSE)
	{
		pcKiller->iPVPKills++;
		pcKiller->iPVPKillStreak++;

		if (pcKiller->iLastKillSafeID != pcVictim->GetID())
		{
			pcKiller->iKillSafe++;
			pcKiller->iLastKillSafeID = pcVictim->GetID();
		}
		else
		{
			bBlockKill = TRUE;
		}

		if (pcKiller->bResetKillStreak)
		{
			pcKiller->iPVPKillStreak = 1;
			pcKiller->bResetKillStreak = FALSE;
		}

		if (pcKiller->dwKillSafeTimeOut < TICKCOUNT)
		{
			pcKiller->iKillSafe = 1;

			pcKiller->dwKillSafeTimeOut = TICKCOUNT + (MAX_TIME_KILLSAFE * 1000);
		}
	}

	//Kill Show
	if ((pcKiller->dwKillSafeTimeOut > TICKCOUNT) && (bBlockKill == FALSE))
	{
		int iType = PVPKILLTYPE_None;

		if (pcKiller->iKillSafe == 2)
			iType = PVPKILLTYPE_DoubleKill;
		else if (pcKiller->iKillSafe == 3)
			iType = PVPKILLTYPE_TripleKill;
		else if (pcKiller->iKillSafe == 4)
			iType = PVPKILLTYPE_QuadraKill;
		else if (pcKiller->iKillSafe == 5)
			iType = PVPKILLTYPE_PentaKill;
		else if (pcKiller->iKillSafe == 6)
			iType = PVPKILLTYPE_Rampage;
		else
		{
			if (pcKiller->iKillSafe > 6)
				iType = PVPKILLTYPE_Unstoppable;
		}

		if (iType != PVPKILLTYPE_None)
			ProcessPvPKill(pcKiller, pcVictim, iType);

		//Check if Victim have Kills before die
		if ((pcVictim->dwKillSafeTimeOut > TICKCOUNT) && (pcVictim->iKillSafe >= 2))
		{
			//Send Shutdown
			ProcessPvPKill(pcKiller, pcVictim, PVPKILLTYPE_Shutdown);
		}
	}

	pcVictim->iPVPDeaths++;
	pcVictim->bResetKillStreak = TRUE;
	pcVictim->iKillSafe = 0;
	pcVictim->dwKillSafeTimeOut = 0;

	if (pcKiller->GetID() != pcVictim->GetID())
	{
		SERVERCHAT->SendChatEx(pcKiller, CHATCOLOR_Notice, "> You killed %s!", SERVERCHARACTER->GetCharacterName(pcVictim));
		SERVERCHAT->SendChatEx(pcVictim, CHATCOLOR_Notice, "> %s killed you!", SERVERCHARACTER->GetCharacterName(pcKiller));
	}

	if (bBlockKill == FALSE)
	{
		BOOL bKill = TRUE;

		ProcessPvPData(pcKiller, pcVictim->iID, bKill);
	}

	ProcessPvPData(pcVictim, pcKiller->iID, FALSE);
}
void CServerPvP::ProcessPvPKill(User * pcKiller, User * pcVictim, int iType)
{
	int iMapID = pcKiller->GetMapID();
	BOOL bSend = FALSE;

	if (iMapID == MAPID_BlessCastle)
	{
		bSend = TRUE;
	}

	if (bSend == TRUE)
	{
		PacketPvPKillType sPacket;
		sPacket.iLength = sizeof(PacketPvPKillType);
		sPacket.iHeader = PKTHDR_PvPKill;
		sPacket.iKillType = iType;
		sPacket.iKillerClass = pcKiller->sCharacterData.iClass;
		sPacket.iVictimClass = pcVictim->sCharacterData.iClass;
		STRINGCOPY(sPacket.szKillerName, SERVERCHARACTER->GetCharacterName(pcKiller));
		STRINGCOPY(sPacket.szVictimName, SERVERCHARACTER->GetCharacterName(pcVictim));
		SENDPACKETSTAGE(&sPacket, pcKiller->iMapID);
	}
}
void CServerPvP::ProcessPvPData(User * pcUser, int iID, BOOL bKill)
{
	PacketPvPData sPacket;
	sPacket.iLength = sizeof(PacketPvPData);
	sPacket.iHeader = PKTHDR_PVPDataUpdate;
	sPacket.iPVPKills = pcUser->iPVPKills;
	sPacket.iPVPDeaths = pcUser->iPVPDeaths;
	sPacket.iPVPKillStreak = pcUser->iPVPKillStreak;
	sPacket.bKill = bKill;
	sPacket.iID = iID;
	SENDPACKET(pcUser, &sPacket, TRUE);
}
BOOL CServerPvP::SQLSelectCharacterPvP(User * pcUser)
{
	BOOL bRet = FALSE;
	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);
	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT ID FROM CharacterPvP WHERE CharacterName=?"))
		{
			char * pszCharacterName = SERVERCHARACTER->GetCharacterName(pcUser);
			pcDB->BindParameterInput(1, PARAMTYPE_String, pszCharacterName);

			if (pcDB->Execute() && pcDB->Fetch())
				bRet = TRUE;
		}
		pcDB->Close();
	}
	return bRet;
}
BOOL CServerPvP::SQLGetTopPvP(PvPClassData & s)
{
	BOOL bRet = FALSE;

	ZeroMemory(&s, sizeof(PvPClassData));

	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);

	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT TOP 100 CharacterName FROM CharacterPvP WHERE (Kills>0) ORDER BY Kills DESC"))
		{
			if (pcDB->Execute())
			{
				char szCharacterName[32] = { 0 };

				while (pcDB->Fetch())
				{
					pcDB->GetData(1, PARAMTYPE_String, szCharacterName, _countof(szCharacterName));
					for (int i = 0; i < 10; i++)
					{
						if (s.szCharacterName[i][0] == 0)
						{
							if (SERVERCHARACTER->SQLGetCharacterClass(szCharacterName) == (i + 1))
							{
								STRINGCOPY(s.szCharacterName[i], szCharacterName);
								bRet = TRUE;
								break;
							}
						}
					}
				}
			}
		}

		pcDB->Close();
	}
	return bRet;
}
void CServerPvP::SQLSetTopPvP(PvPClassData & s)
{
	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);

	if (pcDB->Open())
	{
		for (int i = 0; i < 10; i++)
		{
			if (s.szCharacterName[i][0] != 0)
			{
				if (pcDB->Prepare("UPDATE CharacterPvP SET TopPvP=1 WHERE CharacterName=?"))
				{
					pcDB->BindParameterInput(1, PARAMTYPE_String, s.szCharacterName[i], STRLEN(s.szCharacterName[i]));
					pcDB->Execute();
				}
			}

			pcDB->Clear();
		}
		pcDB->Close();
	}
}
void CServerPvP::OnLoadUser(User * pcUser)
{
	if (!GAME_SERVER)
	{
		BOOL bPvP = FALSE;
		SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);
		if (pcDB->Open())
		{
			if (pcDB->Prepare("SELECT Kills, Deaths, TopPvP FROM CharacterPvP WHERE CharacterName=?"))
			{
				char * pszCharacterName = SERVERCHARACTER->GetCharacterName(pcUser);
				pcDB->BindParameterInput(1, PARAMTYPE_String, pszCharacterName);

				if (pcDB->Execute() && pcDB->Fetch())
				{
					pcDB->GetData(1, PARAMTYPE_Integer, &pcUser->iPVPKills, 0);
					pcDB->GetData(2, PARAMTYPE_Integer, &pcUser->iPVPDeaths, 0);
					pcDB->GetData(3, PARAMTYPE_Integer, &bPvP, 0);
				}
			}
			pcDB->Close();
		}

		if (bPvP)
		{
			if (pcDB->Open())
			{
				if (pcDB->Prepare("UPDATE CharacterPvP SET TopPvp=0 WHERE CharacterName=?"))
				{
					char * pszCharacterName = SERVERCHARACTER->GetCharacterName(pcUser);
					pcDB->BindParameterInput(1, PARAMTYPE_String, pszCharacterName);

					pcDB->Execute();
				}
				pcDB->Close();
			}

			//ITEMSERVER->CreatePremium(pcUser, ITEMID_BCBuff, ITEMTIMERTYPE_BCBuff, ITEMTIMERTIME_72H);
		}

		ProcessPvPData(pcUser, 0, FALSE);
	}
}
void CServerPvP::OnUnLoadUser(User * pcUser)
{
	if (!GAME_SERVER)
	{
		SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);

		if (SQLSelectCharacterPvP(pcUser))
		{
			if (pcDB->Open())
			{
				if (pcDB->Prepare("UPDATE CharacterPvP SET Kills=?, Deaths=?, KillStreak=? WHERE CharacterName=?"))
				{
					char * pszCharacterName = SERVERCHARACTER->GetCharacterName(pcUser);
					pcDB->BindParameterInput(1, PARAMTYPE_Integer, &pcUser->iPVPKills);
					pcDB->BindParameterInput(2, PARAMTYPE_Integer, &pcUser->iPVPDeaths);
					pcDB->BindParameterInput(3, PARAMTYPE_Integer, &pcUser->iPVPKillStreak);
					pcDB->BindParameterInput(4, PARAMTYPE_String, pszCharacterName);
					pcDB->Execute();
				}
				pcDB->Close();
			}
		}
		else
		{
			if (pcDB->Open())
			{
				if (pcDB->Prepare("INSERT INTO CharacterPvP([CharacterName],[Kills],[Deaths],[KillStreak],[TopPvP]) VALUES (?,?,?,?,0)"))
				{
					char * pszCharacterName = SERVERCHARACTER->GetCharacterName(pcUser);
					pcDB->BindParameterInput(1, PARAMTYPE_String, pszCharacterName);
					pcDB->BindParameterInput(2, PARAMTYPE_Integer, &pcUser->iPVPKills);
					pcDB->BindParameterInput(3, PARAMTYPE_Integer, &pcUser->iPVPDeaths);
					pcDB->BindParameterInput(4, PARAMTYPE_Integer, &pcUser->iPVPKillStreak);
					pcDB->Execute();
				}
				pcDB->Close();
			}
		}
	}
}
void CServerPvP::ResetPvPBuffer()
{
	for (int i = 0; i < PLAYERS_MAX; i++)
	{
		User * pcUser = USERSDATA + i;

		if (pcUser->pcSocketData && pcUser->iID)
		{
			pcUser->iPVPKills = 0;
			pcUser->iPVPDeaths = 0;
			pcUser->iPVPKillStreak = 0;

			OnUnLoadUser(pcUser);

			ProcessPvPData(pcUser, 0, FALSE);
		}
	}

	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);

	if (pcDB->Open())
	{
		if (pcDB->Prepare("UPDATE CharacterPvP SET Kills=0, Deaths=0, KillStreak=0, TopPvP=0"))
		{
			pcDB->Execute();
		}
		pcDB->Close();
	}
}
void CServerPvP::Update()
{
	if (GAME_SERVER)
		return;

	if (m_dwTick < TICKCOUNT)
	{
		SYSTEMTIME * ps = SERVERINFO->GetServerTime();

		if (ps->wDayOfWeek == 6 && m_sLastDay != ps->wDay)
		{
			for (int i = 0; i < PLAYERS_MAX; i++)
			{
				User * pcUser = USERSDATA + i;

				if (pcUser->pcSocketData && pcUser->iID)
				{
					OnUnLoadUser(pcUser);
				}
			}

			PvPClassData s;
			if (SQLGetTopPvP(s))
			{
				for (int i = 0; i < 10; i++)
				{
					int iClass = (i + 1);

					if (s.szCharacterName[i][0] != 0)
					{
						char * pszClass = "Fighter";

						if (iClass == CHARACTERCLASS_Mechanician)
							pszClass = "Mechanician";
						if (iClass == CHARACTERCLASS_Archer)
							pszClass = "Archer";
						if (iClass == CHARACTERCLASS_Pikeman)
							pszClass = "Pikeman";
						if (iClass == CHARACTERCLASS_Atalanta)
							pszClass = "Atalanta";
						if (iClass == CHARACTERCLASS_Knight)
							pszClass = "Knight";
						if (iClass == CHARACTERCLASS_Magician)
							pszClass = "Magician";
						if (iClass == CHARACTERCLASS_Priestess)
							pszClass = "Priestess";
						if (iClass == CHARACTERCLASS_Assassin)
							pszClass = "Assassin";
						if (iClass == CHARACTERCLASS_Shaman)
							pszClass = "Shaman";

						SERVERCHAT->SendChatAllEx(CHATCOLOR_Global, "PvP> Top Rank %s: %s", pszClass, s.szCharacterName[i]);
					}
				}

				ResetPvPBuffer();

				SERVERCHAT->SendChatAll(CHATCOLOR_Global, "PvP> Rank Resetted!");

				SQLSetTopPvP(s);

				for (int i = 0; i < PLAYERS_MAX; i++)
				{
					User * pcUser = USERSDATA + i;

					if (pcUser->pcSocketData &&pcUser->iID)
					{
						for (int i = 0; i < 10; i++)
						{
							if (s.szCharacterName[i][0] != 0)
							{
								if (STRINGCOMPARE(SERVERCHARACTER->GetCharacterName(pcUser), s.szCharacterName[i]))
								{
									//ITEMSERVER->CreatePremium(ud, ITEMID_BCBuff, ITEMTIMERTYPE_BCBuff, ITEMTIMERTIME_72H);
								}
							}
						}
					}
				}
			}

			m_sLastDay = ps->wDay;
		}

		m_dwTick = TICKCOUNT + (120 * 1000);
	}
}