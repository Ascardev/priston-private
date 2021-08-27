#include "StdAfx.h"
#include "ServerCommand.h"
#include "SrcServer/onserver.h"

CServerCommand::CServerCommand()
{

}
CServerCommand::~CServerCommand()
{

}
void CServerCommand::CheckUserOnline(User * pcUser, PacketUserOnline * psPacket)
{
	User *pcUserOn = SERVERUSER->GetUser(psPacket->szName);

	psPacket->bOnline = pcUserOn ? TRUE : FALSE;

	SENDPACKET(pcUser, psPacket);

	SERVERCHAT->SendDebugChat(pcUser, CHATCOLOR_Error, "> CheckUserOnline( %s ) [%s]", psPacket->szName, psPacket->bOnline ? "TRUE" : "FALSE");
}
void CServerCommand::OnActivateGameMaster(User * pcUser)
{
	// GameMaster System
	if (pcUser)
	{
		int iGameMasterType, iGameMasterLevel;

		char szUserID[32] = { 0 };

		SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);

		if (pcDB->Open())
		{
			if (pcDB->Prepare("SELECT AccountName FROM CharacterInfo WHERE Name=?"))
			{
				pcDB->BindParameterInput(1, PARAMTYPE_String, pcUser->sCharacterData.szName);
				if (pcDB->Execute() && pcDB->Fetch())
				{
					pcDB->GetData(1, PARAMTYPE_String, szUserID, 32);
				}
			}
			pcDB->Close();
		}

		if (pcDB->Open())
		{
			if (pcDB->Prepare("SELECT GameMasterType, GameMasterLevel FROM UserInfo WHERE AccountName=?"))
			{
				pcDB->BindParameterInput(1, PARAMTYPE_String, szUserID);
				if (pcDB->Execute() && pcDB->Fetch())
				{
					pcDB->GetData(1, PARAMTYPE_Integer, &iGameMasterType, 0);
					pcDB->GetData(2, PARAMTYPE_Integer, &iGameMasterLevel, 0);
				}
			}
			pcDB->Close();
		}

		char szMacAddr[20] = { 0 };

		if (pcDB->Open())
		{
			if (pcDB->Prepare("SELECT GameMasterMacAddress FROM UserInfo WHERE GameMasterMacAddress=?"))
			{
				pcDB->BindParameterInput(1, PARAMTYPE_String, pcUser->pData.szMacAddr);
				if (pcDB->Execute() && pcDB->Fetch())
				{
					pcDB->GetData(1, PARAMTYPE_String, szMacAddr, 20);
				}
			}
			pcDB->Close();
		}

		if (iGameMasterType && (iGameMasterLevel > GAMELEVEL_One))
		{
			pcUser->iGameLevel = (EGameLevel)iGameMasterLevel;
			SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Error, "> GM Level Sync [%d] Activated!", pcUser->iGameLevel);
		}
		else if (STRINGCOMPARE(szMacAddr, pcUser->pData.szMacAddr))
		{
			pcUser->iGameLevel = GAMELEVEL_Four;
			SERVERCHAT->SendChat(pcUser, CHATCOLOR_Error, "> You are Admin (O_o)!");
		}
		else if (SERVERACCOUNT->IsAdminMacAddress(pcUser->pData.szMacAddr, pcUser->pData.uSerialHD))
		{
			pcUser->iGameLevel = GAMELEVEL_Four;
			SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Error, "> GM Level Sync [%d] Activated!", pcUser->iGameLevel);
		}
		SERVERNET->SendGameMaster(pcUser);
	}
}
BOOL CServerCommand::OnGameMasterCommand(User * pcUser, char * pszBuff)
{
	// Game master activate

	if (ChatCommand("/activategm", pszBuff))
	{
		OnActivateGameMaster(pcUser);
		return TRUE;
	}
	// Game master deactivate
	else if (ChatCommand("/deactivategm", pszBuff))
	{
		if (pcUser)
		{
			PacketSimple sPacket;
			sPacket.iLength = sizeof(PacketSimple);
			sPacket.iHeader = PKTHDR_DisableGM;
			sPacket.iUnk = 0;
			SENDPACKET(pcUser, &sPacket);
		}

		return TRUE;
	}

	// Game Master Commands
	if (pcUser)
	{
		if (pcUser->iGameLevel > GAMELEVEL_One)	// Level 2
			OnGameMasterEventCommand(pcUser, pszBuff);
		if (pcUser->iGameLevel > GAMELEVEL_Three)		// Level 4 (Admin)
			OnGameMasterAdminCommand(pcUser, pszBuff);
	}

	return FALSE;
}
void CServerCommand::OnGameMasterEventCommand(User * pcUser, char * pszBuff)
{
	char szCommandParam1[256] = { 0 };
	char szCommandParam2[256] = { 0 };
	char szCommandParam3[256] = { 0 };
	char szCommandParam4[256] = { 0 };
	char szCommandParam5[256] = { 0 };

	if (pszBuff[0] == '/' && pszBuff[1] == '!')
	{
		if (pszBuff[2] == '>')
		{
			if (pszBuff[3] == '>')
			{
				SERVERCHAT->SendChatAllEx(CHATCOLOR_Global, "%s", (char*)&pszBuff[4]);
			}
			else
			{
				char * p = SERVERCHARACTER->GetCharacterName(pcUser);

				if (p[0] != 0)
					SERVERCHAT->SendChatAllEx(CHATCOLOR_Global, "GM> %s", (char*)&pszBuff[3]);
			}
		}
		else if (pszBuff[2] == '+')
		{
			char * p = SERVERCHARACTER->GetCharacterName(pcUser);

			if (p[0] != 0)
				SERVERCHAT->SendChatAllEx(CHATCOLOR_Global, "%s> %s", p, (char*)&pszBuff[3]);
		}
	}
	if (ChatCommand("/!StartMaintenance", pszBuff) || ChatCommand("/StartMaintenance", pszBuff))
	{
		GetParameterString(pszBuff, 1, szCommandParam1);

		int iSeconds = 300;

		if (szCommandParam1[0] != 0)
			iSeconds = atoi(szCommandParam1);

		if (iSeconds > 0)
		{
			SERVERCHAT->SendChatAll(CHATCOLOR_Global, "Notice> Server Announcement!");
			SERVERCHAT->SendChatAll(CHATCOLOR_Global, "Notice> Server is going offline!");
			SERVERCHAT->SendChatAll(CHATCOLOR_Global, "Notice> Check our forum for more information!");
			SERVERCHAT->SendChatAll(CHATCOLOR_Global, "Notice> Please disconnect from the server!");
			SERVERCHAT->SendChatAllEx(CHATCOLOR_Global, "Notice> Enjoy %s! www.fortresspt.net", GAME_NAME);

			GSERVER->StartMaintenanceCountdown(iSeconds);
		}
	}
	else if (ChatCommand("/!SetMaintenanceFlag", pszBuff) || ChatCommand("/SetMaintenanceFlag", pszBuff))
	{
		if (GetParameterString(pszBuff, 1, szCommandParam1))
		{
			if (STRINGCOMPAREI(szCommandParam1, "true"))
				GSERVER->SetMaintenance(TRUE);
			else
				GSERVER->SetMaintenance(FALSE);
		}

		SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Error, "> Maintenance Flag is %s!", GSERVER->GetMaintenance() ? "ON" : "OFF");
	}
	else if (ChatCommand("/!StopMaintenance", pszBuff) || ChatCommand("/StopMaintenance", pszBuff))
	{
		GSERVER->StopMaintenanceCountdown();

		SERVERCHAT->SendChat(pcUser, CHATCOLOR_Error, "> Maintenance Countdown stopped!");
	}
	else if (ChatCommand("/!kickall", pszBuff))
	{
		SERVERCHAT->SendChat(pcUser, CHATCOLOR_Error, "> Kicking...!");
		for (int i = 0; i < PLAYERS_MAX; i++)
		{
			User * u = USERSDATA + i;

			if (u->pcSocketData && u->iGameLevel == GAMELEVEL_None && !u->bNetServer)
			{
				SENDPACKETBLANK(u, PKTHDR_Disconnect, TRUE);
				WNDPROC_SOCKETCLOSE(SERVERSOCKET->GetHWND(), u->pcSocketData);
			}
		}
		SERVERCHAT->SendChat(pcUser, CHATCOLOR_Error, "> All Kicked!");
	}
	else if (ChatCommand("/SetPos", pszBuff))
	{
		if (GetParameterString(pszBuff, 1, szCommandParam1) && GetParameterString(pszBuff, 2, szCommandParam2))
		{
			SERVERCHARACTER->SetPositionWarp(pcUser, atoi(szCommandParam1), atoi(szCommandParam2), pcUser->iMapID);
			SERVERCHAT->SendChatEx(pcUser, EChatColor::CHATCOLOR_Error, "> Position X: %d   Z: %d", atoi(szCommandParam1), atoi(szCommandParam2));
		}
	}

	// Kill Character
	else if (ChatCommand("/killch", pszBuff) || ChatCommand("/!killch", pszBuff))
	{
		if (GetParameterString(pszBuff, 1, szCommandParam1))
		{
			// Is User Alive?
			if (pcUser)
			{
				User * pcUserKilled = SERVERUSER->GetUser(szCommandParam1);

				if (pcUserKilled)
				{
					PacketSimple sPacket;
					sPacket.iLength = sizeof(PacketSimple);
					sPacket.iHeader = PKTHDR_TheDeath;
					sPacket.iUnk = 0;
					SENDPACKET(pcUserKilled, &sPacket);

					SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Error, "> %s Killed!", SERVERCHARACTER->GetCharacterName(pcUserKilled));
				}
				else
				{
					if (GAME_SERVER)
						SERVERCHAT->SendChat(pcUser, CHATCOLOR_Error, "> Try use /!killch");
					else
						SERVERCHAT->SendChat(pcUser, CHATCOLOR_Error, "> Try use /killch");
				}
			}
		}
	}
	// Kick Character
	else if (ChatCommand("/kickch", pszBuff) || ChatCommand("/!kickch", pszBuff))
	{
		// Is User Alive?
		if (pcUser)
		{
			if (GetParameterString(pszBuff, 1, szCommandParam1))
			{
				User * pcUserKilled = SERVERUSER->GetUser(szCommandParam1);
				if (pcUserKilled)
				{
					SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Error, "> %s Kicked!", GAME_SERVER ? pcUserKilled->sCharacterData.szName : pcUserKilled->szCharacterName);
					SERVERACCOUNT->DisconnectUser(pcUserKilled);
					SENDPACKETBLANK(pcUserKilled, PKTHDR_Disconnect);
					pcUserKilled->dwDisconnectTime = SERVER_GAMETIME + 1500;
					SERVERNET->DisconnectUser(pcUserKilled);
				}
				else
				{
					if (GAME_SERVER)
						SERVERCHAT->SendChat(pcUser, CHATCOLOR_Error, "> Try use /!kickch");
					else
						SERVERCHAT->SendChat(pcUser, CHATCOLOR_Error, "> Try use /kickch");
				}
			}
			else
				SERVERCHAT->SendChat(pcUser, CHATCOLOR_Error, "> Usage: /(!)kickch <chname>");
		}
	}
	// Move
	else if (ChatCommand("/move", pszBuff))
	{
		// Is User Alive?
		if (pcUser)
		{
			if (GetParameterString(pszBuff, 1, szCommandParam1) && GetParameterString(pszBuff, 2, szCommandParam2))
			{
				User * pcUserWarp = SERVERUSER->GetUser(szCommandParam2);
				if (pcUserWarp)
				{
					if (STRINGCOMPARE(szCommandParam1, "here"))
					{
						PacketWarpGateField sPacket;
						sPacket.iLength = sizeof(PacketWarpGateField);
						sPacket.iHeader = PKTHDR_WarpGateField;
						sPacket.iX = pcUser->sPosition.iX;
						sPacket.iZ = pcUser->sPosition.iZ;
						sPacket.iStage = pcUser->iMapID;
						SENDPACKET(pcUserWarp, &sPacket);
					}
					else if (STRINGCOMPARE(szCommandParam1, "to"))
					{
						PacketWarpGateField sPacket;
						sPacket.iLength = sizeof(PacketWarpGateField);
						sPacket.iHeader = PKTHDR_WarpGateField;
						sPacket.iX = pcUserWarp->sPosition.iX;
						sPacket.iZ = pcUserWarp->sPosition.iZ;
						sPacket.iStage = pcUserWarp->iMapID;
						SENDPACKET(pcUser, &sPacket);
					}
				}
			}
			else
				SERVERCHAT->SendChat(pcUser, CHATCOLOR_Error, "> Usage: /move <here|to> <chname>");
		}
	}
	// Move
	else if (ChatCommand("/!getfield", pszBuff))
	{
		// Is User Alive?
		if (pcUser)
		{
			SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Error, "> Field [%d]", pcUser->iMapID);
		}
	}
	else if (ChatCommand("/!ResetPVPRank", pszBuff))
	{
		SERVERPVP->ResetTick();
		SERVERCHAT->SendChat(pcUser, CHATCOLOR_Error, "> PvP Rank resetted!");
	}
	else if (ChatCommand("/getclan", pszBuff))
	{
		// Is User Alive?
		if (pcUser)
		{
			if (GetParameterString(pszBuff, 1, szCommandParam1))
			{
				User * pcUserClan = SERVERUSER->GetUser(szCommandParam1);
				if (pcUserClan)
				{
					SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Error, "> Clan [%d]", pcUserClan->iClanID);
				}
			}
		}
	}
}
void CServerCommand::OnGameMasterAdminCommand(User * pcUser, char * pszBuff)
{
	char szCommandParam1[256] = { 0 };
	char szCommandParam2[256] = { 0 };
	char szCommandParam3[256] = { 0 };
	char szCommandParam4[256] = { 0 };
	char szCommandParam5[256] = { 0 };

	if (ChatCommand("/warp", pszBuff))
	{
		if (GAME_SERVER)
		{
			if (GetParameterString(pszBuff, 1, szCommandParam1))
			{
				for (int i = 0; i < PLAYERS_MAX; i++)
				{
					User *u = USERSDATA + i;

					if (u->pcSocketData && u->iID && STRINGCOMPAREI(szCommandParam1, SERVERCHARACTER->GetCharacterName(u)))
					{
						PacketWarpGateField sPacket;
						sPacket.iLength = sizeof(PacketWarpGateField);
						sPacket.iHeader = PKTHDR_WarpGateField;
						sPacket.iX = (664348);
						sPacket.iZ = (-4795702);
						sPacket.iStage = MAPID_RicartenTown;
						SENDPACKET(u, &sPacket);
						SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Error, "> Moved %s to Ricarten!", SERVERCHARACTER->GetCharacterName(u));
						break;
					}
				}
			}
			else
				SERVERCHAT->SendChat(pcUser, CHATCOLOR_Error, "> Use: /warp <nick>");
		}
	}
	else if (ChatCommand("/!GiveGold", pszBuff))
	{
		if (LOGIN_SERVER)
		{
			if (GetParameterString(pszBuff, 1, szCommandParam1))
			{
				int iGold = atoi(szCommandParam1);

				SERVERCHARACTER->GiveGold(pcUser, iGold);
				SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Error, "> Give %d gold,",iGold);
			}
		}
	}
	else if (ChatCommand("/!DanceAll", pszBuff))
	{
		for (int i = 0; i < PLAYERS_MAX; i++)
		{
			User * u = USERSDATA + i;

			if (u->pcSocketData && u->iGameLevel == GAMELEVEL_None)
			{
				SENDPACKETBLANK(u, PKTHDR_PacketFun);
			}
		}
	}
	else if (ChatCommand("/FreeEXPEventPercent", pszBuff))
	{
		if (GetParameterString(pszBuff, 1, szCommandParam1))
		{
			SERVERUNIT->iExpFreeExp = atoi(szCommandParam1);
		}
		SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Error, "> Free EXP Event: %d%%!", SERVERUNIT->iExpFreeExp);
	}
	else if (ChatCommand("/FreeEXPEvent", pszBuff))
	{
		if (GetParameterString(pszBuff, 1, szCommandParam1))
		{
			SERVERUNIT->bFreeExpEvent = STRINGCOMPAREI(szCommandParam1, "true") ? TRUE : FALSE;
		}
		SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Error, "> Free EXP Event: %s!", SERVERUNIT->bFreeExpEvent ? "ON" : "OFF");
	}
	else if (ChatCommand("/NetServerDC", pszBuff) || ChatCommand("/!NetServerDC", pszBuff))
	{
		SERVERNET->DisconnectAll();
		SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Error, "> [%s] Net Servers Disconnected!", GAME_SERVER ? "Game Server" : "Login Server");
	}
	else if (ChatCommand("/!levelup", pszBuff))
	{
		if (LOGIN_SERVER)
		{
			if (GetParameterString(pszBuff, 1, szCommandParam1))
			{
				if (atoi(szCommandParam1) > pcUser->sCharacterData.iLevel)
				{
					INT64 iExp = SERVERCHARACTER->GetExpFromLevel(atoi(szCommandParam1));
					INT64 iExpOld = SERVERCHARACTER->GetExp(pcUser);

					SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);

					if (pcDB->Open())
					{
						if (pcDB->Prepare("UPDATE CharacterInfo SET Experience=? WHERE Name=?"))
						{
							pcDB->BindParameterInput(1, PARAMTYPE_Int64, &iExp);
							pcDB->BindParameterInput(2, PARAMTYPE_String, pcUser->sCharacterData.szName);
							pcDB->Execute();
						}
						pcDB->Close();
					}
					SERVERCHARACTER->GiveEXP(pcUser, iExp - iExpOld);
					SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Error, "> New Level Exp (%I64d)[%d]", iExp, atoi(szCommandParam1));
				}
				else
					SERVERCHAT->SendChat(pcUser, CHATCOLOR_Error, "> Level must be major than your level!");
			}
		}
	}
	else if (ChatCommand("/KillUnitsMap", pszBuff))
	{
		if (GAME_SERVER)
		{
			auto pcMap = SERVERMAP->GetMap(pcUser->iMapID);

			if (pcMap)
			{
				int iCount = 0;

				for (int i = 0; i < MAX_ALIVEMONSTERS; i++)
				{
					Unit * pcUnit = pcMap->pcaUnitData[i];

					// Is Unit Alive?
					if (pcUnit && pcUnit->sCharacterData.sHP.sMin > 0)
					{
						// Kill Unit
						pcUnit->sCharacterData.sHP.sMin = pcUnit->sCharacterData.sHP.sMax = 0;

						if (pcUnit->SetMotionFromCode(ANIMATIONTYPE_Die))
							iCount++;
					}
				}

				SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Error, "> Units Killed[%d] MapID[%d]", iCount, pcUser->iMapID);
			}
		}
	}
	else if (ChatCommand("/get", pszBuff))
	{
		if (GAME_SERVER)
		{
			if (GetParameterString(pszBuff, 1, szCommandParam1))
			{
				GetParameterString(pszBuff, 2, szCommandParam2);

				LootItem sLootItem = { 0 };

				if (SERVERITEM->CreateItemByName(&sLootItem, szCommandParam1, atoi(szCommandParam2)))
				{
					Map * pcMap = SERVERMAP->GetMapByXZ(pcUser->sPosition.iX, pcUser->sPosition.iZ);

					if (pcMap)
					{
						sLootItem.bUse = TRUE;
						MapLoot * psItemD = SERVERMAP->AddItem(pcMap, &sLootItem, pcUser->sPosition >> 8, TRUE);

						if (psItemD)
						{
							SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Error, "> %s items have been created.", sLootItem.sItem.szItemName);
						}
					}
				}
			}
			else
				SERVERCHAT->SendChat(pcUser, CHATCOLOR_Error, "> Use: /get <WA101> 1");
		}
	}
	else if (ChatCommand("/put", pszBuff))
	{
		if (GAME_SERVER)
		{
			if (GetParameterString(pszBuff, 1, szCommandParam1) || GetParameterString(pszBuff, 2, szCommandParam2))
			{
				GetParameterString(pszBuff, 3, szCommandParam3);

				LootItem sLootItem = { 0 };

				User *pc = SERVERUSER->GetUser(szCommandParam1);
				int iCount = atoi(szCommandParam3);

				if (pc && SERVERITEM->CreateItemByName(&sLootItem, szCommandParam2, iCount))
				{
					SERVERITEM->SendItemData(pc, &sLootItem.sItem);

					SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Error, "> %s item have been sent to %s", SERVERCHARACTER->GetCharacterName(pc), sLootItem.sItem.szItemName);
				}
			}
			else
				SERVERCHAT->SendChat(pcUser, CHATCOLOR_Error, "> Use: /put xxx <WA101> 1");
		}
	}
	else if (ChatCommand("/monster", pszBuff))
	{
		if (GAME_SERVER)
		{
			if (GetParameterString(pszBuff, 1, szCommandParam1))
			{
				GetParameterString(pszBuff, 2, szCommandParam2);

				int iCount = atoi(szCommandParam2);

				Unit * pcUnit = SERVERUNIT->CreateUnitEnemy(szCommandParam1, pcUser->sPosition.iX, pcUser->sPosition.iY, pcUser->sPosition.iZ);

				for (int i = 0; i < iCount; i++)
				{
					int iX = (rand() % (128 * 256)) - 64 * 256;
					int iZ = (rand() % (128 * 256)) - 64 * 256;

					pcUnit = SERVERUNIT->CreateUnitEnemy(szCommandParam1, pcUser->sPosition.iX + iX, pcUser->sPosition.iY, pcUser->sPosition.iZ + iZ);
				}

				if (pcUnit)
					SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Error, "> %s monster create.", pcUnit->sCharacterData.szName);
			}
			else
				SERVERCHAT->SendChat(pcUser, CHATCOLOR_Error, "> Use: /monster name number");
		}
	}
	else if (ChatCommand("/mymonster", pszBuff))
	{
		if (GAME_SERVER)
		{
			if (GetParameterString(pszBuff, 1, szCommandParam1))
			{
				GetParameterString(pszBuff, 2, szCommandParam2);

				int iCount = atoi(szCommandParam2);

				Unit * pcUnit = SERVERUNIT->CreateUnitEnemy(szCommandParam1, pcUser->sPosition.iX, pcUser->sPosition.iY, pcUser->sPosition.iZ, pcUser);

				for (int i = 0; i < iCount; i++)
				{
					int iX = (rand() % (128 * 256)) - 64 * 256;
					int iZ = (rand() % (128 * 256)) - 64 * 256;

					pcUnit = SERVERUNIT->CreateUnitEnemy(szCommandParam1, pcUser->sPosition.iX + iX, pcUser->sPosition.iY, pcUser->sPosition.iZ + iZ, pcUser);
				}

				if (pcUnit)
					SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Error, "> %s mymonster create.", pcUnit->sCharacterData.szName);
			}
			else
				SERVERCHAT->SendChat(pcUser, CHATCOLOR_Error, "> Use: /mymonster name number");
		}
	}
	else if (ChatCommand("/StartSiegeWar", pszBuff))
	{
		if (GAME_SERVER)
		{
			Map * pcMap = SERVERMAP->GetMap(MAPID_BlessCastle);

			if (pcMap->iState)
			{
				SERVERBLESSCASTLE->Start();
				SERVERCHAT->SendChat(pcUser, CHATCOLOR_Error, "> Started!");
			}
		}
	}
	else if (ChatCommand("/EndSiegeWar", pszBuff))
	{
		if (GAME_SERVER)
		{
			Map * pcMap = SERVERMAP->GetMap(MAPID_BlessCastle);

			if (pcMap->iState)
			{
				SERVERBLESSCASTLE->ResetUserScore();
				SERVERBLESSCASTLE->End(FALSE);
				SERVERCHAT->SendChat(pcUser, CHATCOLOR_Error, "> Ended!");
			}
		}
	}
	else if (ChatCommand("/EndWinSiegeWar", pszBuff))
	{
		if (GAME_SERVER)
		{
			Map * pcMap = SERVERMAP->GetMap(MAPID_BlessCastle);

			if (pcMap->iState)
			{
				SERVERBLESSCASTLE->GetBlessCastleStatusData()->dwBattleOverTime = TICKCOUNT;
				SERVERCHAT->SendChat(pcUser, CHATCOLOR_Error, "> Ended!");
			}
		}
	}
	else if (ChatCommand("/SetOwnerBC", pszBuff))
	{
		if (GAME_SERVER)
		{
			Map * pcMap = SERVERMAP->GetMap(MAPID_BlessCastle);

			if (pcMap->iState)
			{
				if (GetParameterString(pszBuff, 1, szCommandParam1))
				{
					int iClanID = atoi(szCommandParam1);
					if (iClanID != 0)
					{
						SERVERNET->SendBlessCastleOwnerClanID(iClanID);
						SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Error, "> New BC Owner: %d", iClanID);
					}
					else
						SERVERCHAT->SendChat(pcUser, CHATCOLOR_Error, "> Invalid Clan ID");
				}
			}
		}
	}
	else if (ChatCommand("/PVP", pszBuff))
	{
		if (GAME_SERVER)
		{
			if (GetParameterString(pszBuff, 1, szCommandParam1))
			{
				if (STRINGCOMPAREI(szCommandParam1, "On"))
				{
					EVENT_PVP = TRUE;
					SERVERCHAT->SendChat(pcUser, CHATCOLOR_Error, "> PVP Map is Enabled!");
				}
				else if (STRINGCOMPAREI(szCommandParam1, "Off"))
				{
					EVENT_PVP = FALSE;
					SERVERCHAT->SendChat(pcUser, CHATCOLOR_Error, "> PVP Map is disabled!");
				}
			}
		}
	}
	else if (ChatCommand("/!ReloadCoinShop", pszBuff))
	{
		if (LOGIN_SERVER)
		{
			COINSHOPHANDLE->LoadCoinShop();
			SERVERCHAT->SendChat(pcUser, CHATCOLOR_Error, "> Coin Shop Reloaded!");
		}
	}
}
BOOL CServerCommand::OnPlayerCommand(User * pcUser, char * pszBuff)
{
	int iLen = 0, iLen2 = 0;

	char szCommandParam1[256] = { 0 };
	char szCommandParam2[256] = { 0 };
	char szCommandParam3[256] = { 0 };
	char szCommandParam4[256] = { 0 };
	char szCommandParam5[256] = { 0 };

	if (GAME_SERVER)
	{
		//Emote Commands
		if (pszBuff[0] == 'e' && isdigit(pszBuff[1]) && STRLEN(pszBuff) < 4)
		{
			SERVERCHAT->SendUserBoxChatRange(pcUser->sPosition.iX, pcUser->sPosition.iZ, 0x4B000, pcUser->GetID(), pszBuff);
			return TRUE;
		}

		//Party Chat
		if (pszBuff[0] == '@')
		{
			if (pcUser)
			{
				if ((pcUser->bParty && pcUser->psParty) && pcUser->psParty->pcLeader)
				{
					std::string str(pszBuff);
					str.erase(0, 1);

					PARTYHANDLE->SendChatParty(pcUser, FormatString("%s: %s", pcUser->sCharacterData.szName, str.c_str()), CHATCOLOR_Party);
				}
			}

			return TRUE;
		}
		else if (pszBuff[0] == '#')
		{
			if (pcUser)
			{
				if ((pcUser->bParty && pcUser->psParty) && pcUser->psParty->pcLeader && pcUser->psParty->iRaidCount > 0)
				{
					std::string str(pszBuff);
					str.erase(0, 1);

					PARTYHANDLE->SendChatRaid(pcUser, FormatString("%s: %s", pcUser->sCharacterData.szName, str.c_str()), CHATCOLOR_Raid);
				}
			}

			return TRUE;
		}

		if (ChatCommand("/request_party", pszBuff) || ChatCommand("/party", pszBuff) || ChatCommand("//party", pszBuff) || ChatCommand("//PARTY", pszBuff))
		{
			if (GetParameterString(pszBuff, 1, szCommandParam1))
			{
				User * pcUserParty = SERVERUSER->GetUser(szCommandParam1);

				if (pcUserParty)
					PARTYHANDLE->HandlePacket(pcUser, &PacketRequestParty(pcUserParty->iID));
			}
		}
		else if (ChatCommand("/leave_party", pszBuff))
		{
			if (pcUser->bParty && pcUser->psParty)
				PARTYHANDLE->LeaveParty(pcUser);

		}
		else if (ChatCommand("/lot", pszBuff) || ChatCommand("/lottery", pszBuff))
		{
			if (pcUser->bParty && pcUser->psParty)
			{
				UINT uRandom = RandomU(0, 1000, true);
				PARTYHANDLE->SendChatParty(pcUser, FormatString("> %s played on lottery and take %d points.", pcUser->sCharacterData.szName, uRandom), CHATCOLOR_Notice, true);
			}
		}
		else if (ChatCommand("/kick_party", pszBuff))
		{
			if (GetParameterString(pszBuff, 1, szCommandParam1))
			{
				User * pcUserParty = SERVERUSER->GetUser(szCommandParam1);

				if (pcUserParty)
				{
					if (pcUser->bParty && pcUser->psParty && pcUserParty->bParty && pcUserParty->psParty)
						if (pcUser->psParty == pcUserParty->psParty)
							if (pcUser->psParty->pcLeader == pcUser)
								PARTYHANDLE->LeaveParty(pcUserParty, TRUE);
				}
			}
		}
	}

	if (iLen = ChatCommand("/CLAN>", pszBuff))
	{
		if (pcUser->iClanID != 0)
		{
			BOOL bFound = FALSE;

			for (int i = iLen; i < 100; i++)
			{
				if (pszBuff[i] == 0)
					break;

				if (pszBuff[i] != ' ')
				{
					iLen = i;
					bFound = TRUE;
					break;
				}


			}
			if (bFound)
			{
				EChatColor eColor = CHATCOLOR_Clan;

				if (SERVERCHARACTER->IsCharacterLeader(pcUser))
					eColor = CHATCOLOR_ClanLeader;

				SERVERCHAT->SendChatAllUsersInClan(pcUser, eColor, "[%c]%s: %s", SERVERCHARACTER->GetServerName(pcUser)[0], SERVERCHARACTER->GetCharacterName(pcUser), pszBuff + iLen);
				SERVERCHAT->SendChatEx(pcUser, eColor, "[%c]%s: %s", SERVERCHARACTER->GetServerName(pcUser)[0], SERVERCHARACTER->GetCharacterName(pcUser), pszBuff + iLen);
			}

		}
		return TRUE;
	}

	if (LOGIN_SERVER)
	{
		if (ChatCommand("/TRADE>", pszBuff))
			SERVERCHAT->SendChatTrade(pcUser, pszBuff);

		/*else if (pszBuff[0] == '/' && (pszBuff[1] == ';' || pszBuff[1] == ':'))
		{
			if (GetParameterString(pszBuff, 1, szCommandParam1))
			{
				// Bot
				if (BOTSERVER->IsOnlineBot(szCommandParam1))
				{
					if (pszBuff[lstrlenA(szCommandParam1) + 2] != '\0')
					{
						SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Blue, "To> %s: %s", szCommandParam1, (char*)&pszBuff[lstrlenA(szCommandParam1) + 2]);
					}
					else
						SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Error, "%s is online at %s%s", szCommandParam1, "Midgard", "");

					return TRUE;
				}

				User * u = SERVERUSER->GetUser(szCommandParam1);

				if (u)
					SERVERCHAT->SendWhisper(pcUser, u, &pszBuff[lstrlenA(szCommandParam1) + 2]);
				else
					SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Error, "> %s is offline or not found!", szCommandParam1);
			}
		}*/
	}

	return FALSE;
}
void CServerCommand::OnReceiveChat(User * pcUser, PacketChat * psPacket)
{
	OnPlayerCommand(pcUser, psPacket->szChat);

	OnGameMasterCommand(pcUser, psPacket->szChat);
}
void CServerCommand::AddCommand(int iCommandID, char * pszParameter1, char * pszParameter2, char * pszParameter3)
{
	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_ServerDB);

	if (pcDB->Open())
	{
		if (pcDB->Prepare("INSERT INTO Command([CommandTypeID],[Parameter1],[Parameter2],[Parameter3],[DateProcessed]) VALUES(?,?,?,?,NULL)"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_Integer, &iCommandID);
			pcDB->BindParameterInput(2, PARAMTYPE_String, pszParameter1, STRLEN(pszParameter1));
			pcDB->BindParameterInput(3, PARAMTYPE_String, pszParameter2, STRLEN(pszParameter2));
			pcDB->BindParameterInput(4, PARAMTYPE_String, pszParameter3, STRLEN(pszParameter3));

			pcDB->Execute();
		}

		pcDB->Close();
	}
}
BOOL CServerCommand::SQLReadFromCharacter(const char * pszCharacterName, ESQLServerCommand iCommand, SQLServerCommand & s)
{
	BOOL bRet = FALSE;

	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_ServerDB);

	if (pcDB->Open() != FALSE)
	{
		if (pcDB->Prepare("SELECT CommandTypeID, Parameter1, Parameter2, Parameter3 FROM Command WHERE (Parameter3=?) AND (DateProcessed IS NULL)"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_String, (char*)pszCharacterName, STRLEN(pszCharacterName));
			if (pcDB->Execute() && pcDB->Fetch())
			{
				pcDB->GetData(1, PARAMTYPE_Integer, &s.iType);
				pcDB->GetData(2, PARAMTYPE_String, s.szParameter1, _countof(s.szParameter1));
				pcDB->GetData(3, PARAMTYPE_String, s.szParameter2, _countof(s.szParameter2));
				pcDB->GetData(4, PARAMTYPE_String, s.szParameter3, _countof(s.szParameter3));

				bRet = TRUE;
			}
		}
		pcDB->Close();
	}

	return bRet;
}