#include "StdAfx.h"
#include "ServerBlessCastle.h"
#include "SrcServer/onserver.h"

CServerBlessCastle::CServerBlessCastle()
{
	m_psBlessCastlePVPLeague = new BlessCastlePVPLeague;
	m_psBlessCastleStatusData = new BlessCastleStatusData;

	ZeroMemory(m_psBlessCastlePVPLeague, sizeof(BlessCastlePVPLeague));
	ZeroMemory(m_psBlessCastleStatusData, sizeof(BlessCastleStatusData));
}
CServerBlessCastle::~CServerBlessCastle()
{
	DELET(m_psBlessCastleStatusData);
	DELET(m_psBlessCastlePVPLeague);
}
void CServerBlessCastle::Init()
{
	if (!m_bInit && m_pcUnitDoor)
	{
		m_bCastleDoor = TRUE;
		m_bTowers = TRUE;
		m_bPhase3 = FALSE;
		m_bPhase4 = FALSE;
		m_iPhaseID = 1;
		m_iOldPhaseID = 0;
		m_bInit = TRUE;
	}
}
void CServerBlessCastle::Update()
{
	UpdateBC();

	if (GAME_SERVER && SERVER_CODE == 1)
	{
		//Bless Castle Type 1.
		if (GetSiegeWarMode() == SIEGEWARMODE_TheConquest || GetSiegeWarMode() == SIEGEWARMODE_TheMassacre)
		{
			//Reset
			SYSTEMTIME * ps = SERVERINFO->GetServerTime();

			if ((ps->wDayOfWeek == 0) && (m_sLastDay != ps->wDay))
			{
				SERVERCHAT->SendChatAll(CHATCOLOR_Global, "BlessCastle> Siege War Crown resetted!");
				if (GetSiegeWarMode() == SIEGEWARMODE_TheConquest)
					SERVERCHAT->SendChatAll(CHATCOLOR_Global, "BlessCastle> Mode: The Conquest!");
				else if (GetSiegeWarMode() == SIEGEWARMODE_TheMassacre)
					SERVERCHAT->SendChatAll(CHATCOLOR_Global, "BlessCastle> Mode: The Massacre!");

				BlessCastleStatusData * psBC = m_psBlessCastleStatusData;

				psBC->iClanID = 0;
				psBC->sSettings.iSkill = RandomI(1, 3, true);
				psBC->sSettings.caGuardAmount[0] = 20;
				psBC->sSettings.caGuardAmount[1] = 20;
				psBC->sSettings.caGuardAmount[2] = 20;
				psBC->sSettings.saTowerType[0] = RandomI(1, 3, true);
				psBC->sSettings.saTowerType[1] = RandomI(1, 3, true);
				psBC->sSettings.saTowerType[2] = RandomI(1, 3, true);
				psBC->sSettings.saTowerType[3] = RandomI(1, 3, true);
				psBC->sSettings.saTowerType[4] = RandomI(1, 3, true);
				psBC->sSettings.saTowerType[5] = RandomI(1, 3, true);

				NetSendBlessCastleStatus(SERVERNET->GetLoginServerConnection());

				m_sLastDay = ps->wDay;
			}
		}

		if (m_psBlessCastleStatusData->iCastleMode)
		{
			Init();

			if (m_bInit)
			{
				int iTowers = UpdateTower();

				if (m_pcUnitDoor && m_pcUnitDoor->IsDead() && m_bCastleDoor)
				{
					if (GetSiegeWarMode() != SIEGEWARMODE_TheMassacre)
					{
						if (iTowers == 6)
							SERVERCHAT->SendChatAll(CHATCOLOR_Global, "BlessCastle> Siege War has entered Phase 2!");
						m_pcUnitDoor = NULL;
						m_bCastleDoor = FALSE;
						m_iPhaseID = 2;
					}
				}

				if (m_bTowers && !m_bCastleDoor)
				{
					if (iTowers == 4 && !m_bPhase3)
					{
						SERVERCHAT->SendChatAll(CHATCOLOR_Global, "BlessCastle> Siege War has entered Phase 3!");
						m_bPhase3 = TRUE;
						m_iPhaseID = 3;
					}
					else if (iTowers == 2 && !m_bPhase4)
					{
						SERVERCHAT->SendChatAll(CHATCOLOR_Global, "BlessCastle> Siege War has entered Phase 4!");
						m_bPhase4 = TRUE;
						m_iPhaseID = 4;
					}
					else if (iTowers == 0)
					{
						SERVERCHAT->SendChatAll(CHATCOLOR_Global, "BlessCastle> Siege War has entered the Final Phase!");
						m_bTowers = FALSE;
						m_iPhaseID = 5;
					}
				}

				// Update Users
				if (m_iPhaseID != m_iOldPhaseID)
				{
					UpdatePhase(m_iPhaseID);
					m_iOldPhaseID = m_iPhaseID;
				}
				else if (TICKCOUNT > m_dwTickUpdate)
				{
					UpdatePhase(m_iPhaseID);
					m_dwTickUpdate = TICKCOUNT + 5000;
				}
			}
		}
		else
		{
			m_pcUnitDoor = nullptr;
			m_bInit = FALSE;
		}
	}
}
void CServerBlessCastle::UpdateBC()
{
	if (!GAME_SERVER)
		return;

	m_psBlessCastleStatusData->iCounter++;

	Map * pcMap = SERVERMAP->GetMap(MAPID_BlessCastle);

	int iUpdate = 0;

	MainFountain();

	if (m_psBlessCastlePVPLeague->iMode)
	{
		if (m_psBlessCastlePVPLeague->dwEndTime && (m_psBlessCastlePVPLeague->dwEndTime < TICKCOUNT))
			m_psBlessCastlePVPLeague->iMode = 0;
		else
		{
			if (m_psBlessCastleStatusData->iCastleMode == 0)
			{
				if (m_psBlessCastlePVPLeague->dwRestartTime && (m_psBlessCastlePVPLeague->dwRestartTime < TICKCOUNT))
					Start();
			}
		}
	}

	if (m_psBlessCastleStatusData->iCastleMode == 0)
	{
		m_psBlessCastleStatusData->saTimeSec[0] = 0;
		m_psBlessCastleStatusData->saTimeSec[1] = 0;
	}
	else if (m_psBlessCastleStatusData->iCastleMode == 3)
	{
		if (m_psBlessCastleStatusData->dwBattleOverTime < TICKCOUNT)
			End();
	}
	else
	{
		if ((m_psBlessCastleStatusData->iCounter & 0x1F) == 0)
		{
			m_psBlessCastleStatusData->saTimeSec[0] = (short)((TICKCOUNT - m_psBlessCastleStatusData->dwStartTime) / 1000);
			m_psBlessCastleStatusData->saTimeSec[1] = (short)((m_psBlessCastleStatusData->dwBattleOverTime - m_psBlessCastleStatusData->dwStartTime) / 1000);

			m_psBlessCastleStatusData->baSoldierCount[0] = 0;
			m_psBlessCastleStatusData->baSoldierCount[1] = 0;
			m_psBlessCastleStatusData->baSoldierCount[2] = 0;
			m_psBlessCastleStatusData->baSoldierCount[3] = 0;

			m_psBlessCastleStatusData->baCrystalTowerCount[0] = 0;
			m_psBlessCastleStatusData->baCrystalTowerCount[1] = 0;
			m_psBlessCastleStatusData->baCrystalTowerCount[2] = 0;
			m_psBlessCastleStatusData->baCrystalTowerCount[3] = 0;

			//Tick
			if (m_dwTickUpdateUsersScore < TICKCOUNT)
			{
				UpdateIndividualScores();

				SendIndividualScore();

				m_dwTickUpdateUsersScore = TICKCOUNT + 1500;
			}

			BOOL bCastleDoor = FALSE;
			Unit * pcTower = NULL;
			int iValhallaCount = 0; //Further New BC?
			int iCrystalTowerCount = 0;

			for (int i = 0; i < MAX_ALIVEMONSTERS; i++)
			{
				Unit * pc = pcMap->pcaUnitData[i];

				if (pc && (pc->sCharacterData.sHP.sMin > 0))
				{
					//BC Door Alive?
					if (pc->sCharacterData.iMonsterEffectID == MONSTEREFFECTID_CASTLE_DOOR)
					{
						//Set
						bCastleDoor = TRUE;

						//Conquest Mode?
						if (GetSiegeWarMode() == SIEGEWARMODE_TheConquest)
						{
							//Set Door to score on Siege War..
							if (m_psBlessCastleStatusData->iDefenseLevel == 0 && m_psBlessCastleStatusData->psaDamageData)
							{
								if (pc->psaSiegeWarDataList == NULL)
									pc->psaSiegeWarDataList = m_psBlessCastleStatusData->psaDamageData;
							}
						}

						m_pcUnitDoor = pc;
					}
					else if (pc->sCharacterData.iMonsterEffectID == MONSTEREFFECTID_CASTLE_TOWER_B)
					{
						pcTower = pc;
						iValhallaCount++;
					}
					else if (pc->sCharacterData.iMonsterEffectID == MONSTEREFFECTID_CASTLE_CRYSTAL_N ||
						pc->sCharacterData.iMonsterEffectID == MONSTEREFFECTID_CASTLE_CRYSTAL_R ||
						pc->sCharacterData.iMonsterEffectID == MONSTEREFFECTID_CASTLE_CRYSTAL_G ||
						pc->sCharacterData.iMonsterEffectID == MONSTEREFFECTID_CASTLE_CRYSTAL_B)
					{
						switch (pc->sCharacterData.iMonsterEffectID)
						{
						case MONSTEREFFECTID_CASTLE_CRYSTAL_R:
							if (m_psBlessCastleStatusData->baCrystalTowerCount[0] < 100)
								m_psBlessCastleStatusData->baCrystalTowerCount[0]++;
							break;

						case MONSTEREFFECTID_CASTLE_CRYSTAL_G:
							if (m_psBlessCastleStatusData->baCrystalTowerCount[1] < 100)
								m_psBlessCastleStatusData->baCrystalTowerCount[1]++;
							break;

						case MONSTEREFFECTID_CASTLE_CRYSTAL_B:
							if (m_psBlessCastleStatusData->baCrystalTowerCount[2] < 100)
								m_psBlessCastleStatusData->baCrystalTowerCount[2]++;
							break;

						case MONSTEREFFECTID_CASTLE_CRYSTAL_N:
							if (m_psBlessCastleStatusData->baCrystalTowerCount[3] < 100)
								m_psBlessCastleStatusData->baCrystalTowerCount[3]++;
							break;

						default:
							break;
						}

						iCrystalTowerCount++;

						if (m_psBlessCastleStatusData->iDefenseLevel == 0 && m_psBlessCastleStatusData->psaDamageData)
						{
							if (pc->psaSiegeWarDataList == NULL)
								pc->psaSiegeWarDataList = m_psBlessCastleStatusData->psaDamageData;
						}
					}
					else if (pc->sCharacterData.iOwnerID)
					{
						BOOL bSoldier = FALSE;

						switch (pc->sCharacterData.iMonsterEffectID)
						{
						case MONSTEREFFECTID_CASTLE_SOLDER_A:
							if (m_psBlessCastleStatusData->baSoldierCount[0] < 100)
								m_psBlessCastleStatusData->baSoldierCount[0]++;

							bSoldier = TRUE;
							break;
						case MONSTEREFFECTID_CASTLE_SOLDER_B:
							if (m_psBlessCastleStatusData->baSoldierCount[1] < 100)
								m_psBlessCastleStatusData->baSoldierCount[1]++;

							bSoldier = TRUE;
							break;
						case MONSTEREFFECTID_CASTLE_SOLDER_C:
							if (m_psBlessCastleStatusData->baSoldierCount[2] < 100)
								m_psBlessCastleStatusData->baSoldierCount[2]++;

							bSoldier = TRUE;
							break;

						default:
							break;
						}

						if (bSoldier)
						{
							//Conquest Mode?
							if (GetSiegeWarMode() == SIEGEWARMODE_TheConquest)
							{
								//Set Soldiers to score on Siege War..
								if (m_psBlessCastleStatusData->psaDamageData)
								{
									if (pc->psaSiegeWarDataList == NULL)
										pc->psaSiegeWarDataList = m_psBlessCastleStatusData->psaDamageData;
								}
							}
						}
					}
					else if (pc->sCharacterData.iMonsterEffectID == MONSTEREFFECTID_CASTLE_SOLDER_A ||
						pc->sCharacterData.iMonsterEffectID == MONSTEREFFECTID_CASTLE_SOLDER_B ||
						pc->sCharacterData.iMonsterEffectID == MONSTEREFFECTID_CASTLE_SOLDER_C)
					{
						//Conquest Mode?
						if (GetSiegeWarMode() == SIEGEWARMODE_TheConquest)
						{
							//Set Soldiers to score on Siege War..
							if (m_psBlessCastleStatusData->psaDamageData)
							{
								if (pc->psaSiegeWarDataList == NULL)
									pc->psaSiegeWarDataList = m_psBlessCastleStatusData->psaDamageData;
							}
						}
					}

					pc->dwLastActiveTime = TICKCOUNT;
					pc->iAliveCounter = 256;
				}
			}

			//Check for Users inside castle
			if (bCastleDoor && (GetSiegeWarMode() == SIEGEWARMODE_TheConquest))
			{
				UINT uUsersInGame = SERVERUSER->uUsersInGame;
				User ** pcaUserInGame = SERVERUSER->pcaUserInGame;

				for (UINT i = 0; i < uUsersInGame; i++)
				{
					User * pcUser = pcaUserInGame[i];

					if (pcUser->IsInGame() && (pcUser->GetMapID() == MAPID_BlessCastle) && (pcUser->GetGameLevel() < GAMELEVEL_Two))
					{
						if (pcUser->sPosition.iZ < ((-25580) << 8))
						{
							SERVERCHARACTER->SetPositionWarp(pcUser, 8859282, -5931214, MAPID_BlessCastle);
						}
					}
				}
			}

			if ((m_psBlessCastleStatusData->iDefenseLevel == 0) && (bCastleDoor == FALSE))
				m_psBlessCastleStatusData->iDefenseLevel++;

			BOOL bFinished = FALSE;

			if (iValhallaCount == 0)
			{
				End(FALSE);

				if (m_psBlessCastleStatusData->sPacketTopData.iClanID[0])
				{
					m_psBlessCastleStatusData->iClanID = GetClanCodeByID(m_psBlessCastleStatusData->sPacketTopData.iClanID[0]);

					KillBuffs();

					ResetUserScore();

					SERVERNET->SendBlessCastleOwnerClanID(m_psBlessCastleStatusData->iClanID);

					iUpdate = 2;

					SQLWriteBlessCastleStatus();

					bFinished = TRUE;
				}
			}
			else if (m_psBlessCastleStatusData->dwBattleOverTime < TICKCOUNT)
			{
				//Change to new Mode = TRUE
				BOOL bUnitsAlive = FALSE;

				//Conquest Mode? Units Alive
				if (GetSiegeWarMode() == SIEGEWARMODE_TheConquest)
					bUnitsAlive = TRUE;

				End(bUnitsAlive);

				if (m_psBlessCastleStatusData->sPacketTopData.iClanID[0])
				{
					//Conquest Mode?
					if ((GetSiegeWarMode() == SIEGEWARMODE_TheConquest))
					{
						//No Winner
						m_psBlessCastleStatusData->iClanID = 0;
					}
					else if ((GetSiegeWarMode() == SIEGEWARMODE_TheMassacre))
					{
						//Otherwise, on Normal Mode...
						m_psBlessCastleStatusData->iClanID = GetClanCodeByID(m_psBlessCastleStatusData->sPacketTopData.iClanID[0]);
					}

					KillBuffs();

					ResetUserScore();

					SERVERNET->SendBlessCastleOwnerClanID(m_psBlessCastleStatusData->iClanID);

					iUpdate = 2;

					SQLWriteBlessCastleStatus();

					bFinished = TRUE;
				}
			}

			//Finished?
			if (bFinished)
			{
				//Handle Prizes
				if (GetSiegeWarMode() == SIEGEWARMODE_TheConquest)
				{
					char szAccountName[32] = { 0 };
					char szClanName[32] = { 0 };
					char szGold[32] = { 0 };

					//1st
					int iGold = 0;

					//5,000,000 every 10,000 points
					iGold = ((m_psBlessCastleStatusData->sPacketTopData.iDamage[0] / 10000) * 5000000);

					if (SERVERUSER->GetClanLeaderAccount(m_psBlessCastleStatusData->sPacketTopData.iClanID[0], szAccountName))
					{
						if (iGold > MAX_GOLD_PERBOX)
						{
							int iGoldR = iGold;
							int iCount = (iGold / MAX_GOLD_PERBOX) + 1;
							for (int i = 0; i < iCount; i++)
							{
								int j = iGoldR > MAX_GOLD_PERBOX ? MAX_GOLD_PERBOX : iGoldR;
								DISTRIBUTORHANDLE->AddItemOpenBox(szAccountName, "GG101", 0, j);
								iGoldR -= MAX_GOLD_PERBOX;
							}
						}
						else
							DISTRIBUTORHANDLE->AddItemOpenBox(szAccountName, "GG101", 0, iGold);
					}

					if (SERVERUSER->GetClanName(m_psBlessCastleStatusData->sPacketTopData.iClanID[0], szClanName))
					{
						STRINGCOPY(szGold, FormatNumber(iGold));
						SERVERCHAT->SendChatAllEx(CHATCOLOR_Global, "BlessCastle> Winner Clan: %s!", szClanName);
						SERVERCHAT->SendChatAllEx(CHATCOLOR_Global, "BlessCastle> 1st Place: %s", szClanName);
						SERVERCHAT->SendChatAllEx(CHATCOLOR_Global, "BlessCastle> %s Points, %s gp!", FormatNumber(m_psBlessCastleStatusData->sPacketTopData.iDamage[0]), szGold);
					}

					//2nd
					if (m_psBlessCastleStatusData->sPacketTopData.iClanID[1])
					{
						iGold = ((m_psBlessCastleStatusData->sPacketTopData.iDamage[1] / 10000) * 5000000);

						if (SERVERUSER->GetClanLeaderAccount(m_psBlessCastleStatusData->sPacketTopData.iClanID[1], szAccountName))
						{
							if (iGold > MAX_GOLD_PERBOX)
							{
								int iGoldR = iGold;
								int iCount = (iGold / MAX_GOLD_PERBOX) + 1;
								for (int i = 0; i < iCount; i++)
								{
									int j = iGoldR > MAX_GOLD_PERBOX ? MAX_GOLD_PERBOX : iGoldR;
									DISTRIBUTORHANDLE->AddItemOpenBox(szAccountName, "GG101", 0, j);
									iGoldR -= MAX_GOLD_PERBOX;
								}
							}
							else
								DISTRIBUTORHANDLE->AddItemOpenBox(szAccountName, "GG101", 0, iGold);
						}

						if (SERVERUSER->GetClanName(m_psBlessCastleStatusData->sPacketTopData.iClanID[1], szClanName))
						{
							STRINGCOPY(szGold, FormatNumber(iGold));
							SERVERCHAT->SendChatAllEx(CHATCOLOR_Global, "BlessCastle> 2nd Place: %s", szClanName);
							SERVERCHAT->SendChatAllEx(CHATCOLOR_Global, "BlessCastle> %s Points, %s gp!", FormatNumber(m_psBlessCastleStatusData->sPacketTopData.iDamage[1]), szGold);
						}
					}

					//3rd
					if (m_psBlessCastleStatusData->sPacketTopData.iClanID[2])
					{
						iGold = ((m_psBlessCastleStatusData->sPacketTopData.iDamage[2] / 10000) * 5000000);

						if (SERVERUSER->GetClanLeaderAccount(m_psBlessCastleStatusData->sPacketTopData.iClanID[2], szAccountName))
						{
							if (iGold > MAX_GOLD_PERBOX)
							{
								int iGoldR = iGold;
								int iCount = (iGold / MAX_GOLD_PERBOX) + 1;
								for (int i = 0; i < iCount; i++)
								{
									int j = iGoldR > MAX_GOLD_PERBOX ? MAX_GOLD_PERBOX : iGoldR;
									DISTRIBUTORHANDLE->AddItemOpenBox(szAccountName, "GG101", 0, j);
									iGoldR -= MAX_GOLD_PERBOX;
								}
							}
							else
								DISTRIBUTORHANDLE->AddItemOpenBox(szAccountName, "GG101", 0, iGold);
						}

						if (SERVERUSER->GetClanName(m_psBlessCastleStatusData->sPacketTopData.iClanID[2], szClanName))
						{
							STRINGCOPY(szGold, FormatNumber(iGold));
							SERVERCHAT->SendChatAllEx(CHATCOLOR_Global, "BlessCastle> 3rd Place: %s", szClanName);
							SERVERCHAT->SendChatAllEx(CHATCOLOR_Global, "BlessCastle> %s Points, %s gp!", FormatNumber(m_psBlessCastleStatusData->sPacketTopData.iDamage[2]), szGold);
						}
					}

					HandleIndividualScore();

					//Notify Users
					SERVERCHAT->SendChatAll(CHATCOLOR_Global, "BlessCastle> All prizes delivered to the leaders!");
				}
				else if (GetSiegeWarMode() == SIEGEWARMODE_TheMassacre)
				{
					char szAccountName[32] = { 0 };
					char szClanName[32] = { 0 };
					char szGold[32] = { 0 };

					//1st
					int iGold = 0;

					//5,000,000 every 10,000 points
					iGold = ((m_psBlessCastleStatusData->sPacketTopData.iDamage[0] / 5000) * 5000000);

					if (SERVERUSER->GetClanLeaderAccount(m_psBlessCastleStatusData->sPacketTopData.iClanID[0], szAccountName))
						DISTRIBUTORHANDLE->AddItemOpenBox(szAccountName, "GG101", 0, iGold);


					if (SERVERUSER->GetClanName(m_psBlessCastleStatusData->sPacketTopData.iClanID[0], szClanName))
					{
						STRINGCOPY(szGold, FormatNumber(iGold));
						SERVERCHAT->SendChatAllEx(CHATCOLOR_Global, "BlessCastle> Winner Clan: %s!", szClanName);
						SERVERCHAT->SendChatAllEx(CHATCOLOR_Global, "BlessCastle> 1st Place: %s", szClanName);
						SERVERCHAT->SendChatAllEx(CHATCOLOR_Global, "BlessCastle> %s Points, %s gp!", FormatNumber(m_psBlessCastleStatusData->sPacketTopData.iDamage[0]), szGold);
					}

					//2nd
					if (m_psBlessCastleStatusData->sPacketTopData.iClanID[1])
					{
						iGold = ((m_psBlessCastleStatusData->sPacketTopData.iDamage[1] / 5000) * 5000000);

						if (SERVERUSER->GetClanLeaderAccount(m_psBlessCastleStatusData->sPacketTopData.iClanID[1], szAccountName))
							DISTRIBUTORHANDLE->AddItemOpenBox(szAccountName, "GG101", 0, iGold);

						if (SERVERUSER->GetClanName(m_psBlessCastleStatusData->sPacketTopData.iClanID[1], szClanName))
						{
							STRINGCOPY(szGold, FormatNumber(iGold));
							SERVERCHAT->SendChatAllEx(CHATCOLOR_Global, "BlessCastle> 2nd Place: %s", szClanName);
							SERVERCHAT->SendChatAllEx(CHATCOLOR_Global, "BlessCastle> %s Points, %s gp!", FormatNumber(m_psBlessCastleStatusData->sPacketTopData.iDamage[1]), szGold);
						}
					}

					//3rd
					if (m_psBlessCastleStatusData->sPacketTopData.iClanID[2])
					{
						iGold = ((m_psBlessCastleStatusData->sPacketTopData.iDamage[2] / 5000) * 5000000);

						if (SERVERUSER->GetClanLeaderAccount(m_psBlessCastleStatusData->sPacketTopData.iClanID[2], szAccountName))
							DISTRIBUTORHANDLE->AddItemOpenBox(szAccountName, "GG101", 0, iGold);

						if (SERVERUSER->GetClanName(m_psBlessCastleStatusData->sPacketTopData.iClanID[2], szClanName))
						{
							STRINGCOPY(szGold, FormatNumber(iGold));
							SERVERCHAT->SendChatAllEx(CHATCOLOR_Global, "BlessCastle> 3rd Place: %s", szClanName);
							SERVERCHAT->SendChatAllEx(CHATCOLOR_Global, "BlessCastle> %s Points, %s gp!", FormatNumber(m_psBlessCastleStatusData->sPacketTopData.iDamage[2]), szGold);
						}
					}

					HandleIndividualScore();

					//Notify Users
					SERVERCHAT->SendChatAll(CHATCOLOR_Global, "BlessCastle> All prizes delivered to the leaders!");
				}
			}

			m_psBlessCastleStatusData->pcUnitDataTower = pcTower;

			if (pcTower)
			{
				if (iCrystalTowerCount > 0)
					pcTower->sCharacterData.sHP.sMin = pcTower->sCharacterData.sHP.sMax;
				else
				{
					if (pcTower->psaDamageUsersData == NULL)
					{
						if (m_psBlessCastleStatusData->psaDamageData)
						{
							pcTower->psaDamageUsersData = m_psBlessCastleStatusData->psaDamageData;

							m_psBlessCastleStatusData->psaDamageData = NULL;
						}
						else
						{
							pcTower->psaDamageUsersData = new AttackDamageData[MAX_DAMAGEDATA];

							if (pcTower->psaDamageUsersData)
								ZeroMemory(pcTower->psaDamageUsersData, sizeof(AttackDamageData) * MAX_DAMAGEDATA);
						}
					}
				}

				GetTop10ClanDamage(pcTower, &m_psBlessCastleStatusData->sPacketTopData);
			}
		}

		if (m_psBlessCastleStatusData->sPacketTopData.iHeader)
		{
			for (int i = (m_psBlessCastleStatusData->iCounter & 0x1F); i < PLAYERS_MAX; i += 0x20)
			{
				User * pc = &USERSDATA[i];

				if (pc->pcSocketData && pc->iID && pc->iMapID == MAPID_BlessCastle)
				{
					if (CanShowScore() || (pc->iGameLevel >= GAMELEVEL_Two))
					{
						SENDPACKET(pc, &m_psBlessCastleStatusData->sPacketTopData);
					}

					if (iUpdate > 0)
					{
						//BlessCastleServer::SendBlessCastleDataToLoginServer(pc);
						NetSendBlessCastleStatus(SERVERNET->GetLoginServerConnection());

						iUpdate--;
					}
				}
			}
		}
	}
}
void CServerBlessCastle::OnTime()
{
	if (GAME_SERVER && SERVER_CODE == 1)
	{
		SYSTEMTIME * ps = SERVERINFO->GetServerTime();

		BlessCastleStatusData * psBC = m_psBlessCastleStatusData;

		if (m_sLastHour != ps->wHour && ps->wHour == 2)
		{
			psBC->iTax = psBC->iTaxNow;
			psBC->iSkill = psBC->sSettings.iSkill;
		}
		if (EVENT_BLESSCASTLE_DAY && EVENT_BLESSCASTLE_HOUR)
		{
			if (EVENT_BLESSCASTLE)
			{
				if (!psBC->iCastleMode && m_sLastHour != ps->wHour && ps->wDayOfWeek == EVENT_BLESSCASTLE_DAY && ps->wHour == EVENT_BLESSCASTLE_HOUR)
					SERVERBLESSCASTLE->Start();
			}

			if (m_sLastMin == 29 && ps->wMinute == 30 && ps->wDayOfWeek == EVENT_BLESSCASTLE_DAY && ps->wHour == EVENT_BLESSCASTLE_HOUR - 1)
				SERVERCHAT->SendChatAll(CHATCOLOR_Global, "BlessCastle> Siege War will start in 30 minutes!!!");
			if (m_sLastHour == EVENT_BLESSCASTLE_HOUR - 2 && ps->wDayOfWeek == EVENT_BLESSCASTLE_DAY && ps->wHour == EVENT_BLESSCASTLE_HOUR - 1)
				SERVERCHAT->SendChatAll(CHATCOLOR_Global, "BlessCastle> Siege War will start in 1 hour");
		}

		m_sLastHour = ps->wHour;
		m_sLastMin = ps->wMinute;
	}
}
void CServerBlessCastle::Start()
{
	Map * pcBCMap = SERVERMAP->GetMap(MAPID_BlessCastle);

	if (EVENT_BLESSCASTLE == 2)
	{
		m_psBlessCastlePVPLeague->iMode = 1;
		m_psBlessCastlePVPLeague->dwBeginTime = TICKCOUNT;
		m_psBlessCastlePVPLeague->dwEndTime = m_iBlessCastleMode == SIEGEWARMODE_TheMassacre ?
			TICKCOUNT + (30 * 60 * 1000) : TICKCOUNT + (120 * 60 * 1000);

		EVENT_BLESSCASTLE = 1;
	}

	m_psBlessCastleStatusData->iCastleMode = 1;
	m_psBlessCastleStatusData->iCounter = 0;
	m_psBlessCastleStatusData->iDefenseLevel = 0;
	m_psBlessCastleStatusData->dwBattleOverTime = m_iBlessCastleMode == SIEGEWARMODE_TheMassacre ?
		TICKCOUNT + (30 * 60 * 1000) : TICKCOUNT + (120 * 60 * 1000);

	m_psBlessCastleStatusData->dwStartTime = TICKCOUNT;
	m_psBlessCastleStatusData->saTimeSec[0] = 0;
	m_psBlessCastleStatusData->saTimeSec[1] = 0;
	m_psBlessCastleStatusData->dwScoreTime = TICKCOUNT + (5 * 60 * 1000);

	if (m_psBlessCastlePVPLeague->iMode)
	{
		m_psBlessCastlePVPLeague->dwRestartTime = 0;
	}

	if (m_psBlessCastleStatusData->psaDamageData == NULL)
		m_psBlessCastleStatusData->psaDamageData = new AttackDamageData[ATTACK_DAMAGE_MAX];

	ZeroMemory(m_psBlessCastleStatusData->psaDamageData, sizeof(AttackDamageData) * ATTACK_DAMAGE_MAX);

	if (m_psBlessCastleStatusData->iClanID == 0)
	{
		m_psBlessCastleStatusData->sSettings.caGuardAmount[0] = 20;
		m_psBlessCastleStatusData->sSettings.caGuardAmount[1] = 20;
		m_psBlessCastleStatusData->sSettings.caGuardAmount[2] = 20;
		m_psBlessCastleStatusData->sSettings.caGuardAmount[3] = 0;

		//Towers
		for (int i = 0; i < 6; i++)
			m_psBlessCastleStatusData->sSettings.saTowerType[i] = (rand() % 3) + 1;
	}

	ZeroMemory(&m_psBlessCastleStatusData->sPacketTopData, sizeof(PacketBlessCastleTopData));

	for (int i = 0; i < MAX_UNITS; i++)
	{
		Unit * pc = UNITSDATA + i;

		if (pc->bActive && pc->pcMap == pcBCMap)
		{
			pc->Close();

			if (SERVERMAP->DelMonsterSpawn(pcBCMap, pc))
				pcBCMap->iNumAliveUnitData--;
		}
	}

	auto pMonstTable = SERVERUNIT->GetMonsterTable();

	CharacterData * psCastleDoor = NULL;
	CharacterData * psValhalla = NULL;
	CharacterData * psTowerR = NULL;
	CharacterData * psTowerG = NULL;
	CharacterData * psTowerB = NULL;
	CharacterData * psTowerN = NULL;
	CharacterData * psCastleGuardA = NULL;
	CharacterData * psCastleGuardB = NULL;
	CharacterData * psCastleGuardC = NULL;
	CharacterData * psSetTower = NULL;

	UINT iClanID = m_psBlessCastleStatusData->iClanID;

	for (auto & ps : pMonstTable)
	{
		if (ps->iMonsterEffectID == MONSTEREFFECTID_CASTLE_DOOR)
			psCastleDoor = ps;
		else if (ps->iMonsterEffectID == MONSTEREFFECTID_CASTLE_TOWER_B)
			psValhalla = ps;
		else if (ps->iMonsterEffectID == MONSTEREFFECTID_CASTLE_CRYSTAL_R)
			psTowerR = ps;
		else if (ps->iMonsterEffectID == MONSTEREFFECTID_CASTLE_CRYSTAL_G)
			psTowerG = ps;
		else if (ps->iMonsterEffectID == MONSTEREFFECTID_CASTLE_CRYSTAL_B)
			psTowerB = ps;
		else if (ps->iMonsterEffectID == MONSTEREFFECTID_CASTLE_CRYSTAL_N)
			psTowerN = ps;
		else if (ps->iMonsterEffectID == MONSTEREFFECTID_CASTLE_SOLDER_A)
			psCastleGuardA = ps;
		else if (ps->iMonsterEffectID == MONSTEREFFECTID_CASTLE_SOLDER_B)
			psCastleGuardB = ps;
		else if (ps->iMonsterEffectID == MONSTEREFFECTID_CASTLE_SOLDER_C)
			psCastleGuardC = ps;
	}

	if (psCastleDoor)
	{
		SERVERMAP->SpawnMonsterBC(pcBCMap, psCastleDoor, sCastleDoorPosition << 8, iClanID);
	}

	if (psValhalla)
	{
		SERVERMAP->SpawnMonsterBC(pcBCMap, psValhalla, sCastleValhallaPosition << 8, iClanID);
	}

	for (int i = 0; i < _countof(saBlessCastleTowerPosition); i++)
	{
		if (saBlessCastleTowerPosition[i].iX == 0)
			break;

		psSetTower = psTowerN;

		switch (m_psBlessCastleStatusData->sSettings.saTowerType[i])
		{
		case 1: //Ice
			psSetTower = psTowerB;
			break;
		case 2: //Lightning
			psSetTower = psTowerG;
			break;
		case 3: //Fire
			psSetTower = psTowerR;
			break;
		default:
			break;
		}

		if (psSetTower)
			SERVERMAP->SpawnMonsterBC(pcBCMap, psSetTower, saBlessCastleTowerPosition[i] << 8, iClanID);
	}

	for (int i = 0; i < 3; i++)
	{
		if (m_psBlessCastleStatusData->sSettings.caGuardAmount[i] > 20)
			m_psBlessCastleStatusData->sSettings.caGuardAmount[i] = 20;
	}

	if (psCastleGuardA)
	{
		for (int i = 0; i < m_psBlessCastleStatusData->sSettings.caGuardAmount[0]; i++)
			SERVERMAP->SpawnMonsterBC(pcBCMap, psCastleGuardA, saCastleGuardPositionA[i] << 8, iClanID);
	}
	if (psCastleGuardB)
	{
		for (int i = 0; i < m_psBlessCastleStatusData->sSettings.caGuardAmount[1]; i++)
			SERVERMAP->SpawnMonsterBC(pcBCMap, psCastleGuardB, saCastleGuardPositionB[i] << 8, iClanID);
	}
	if (psCastleGuardC)
	{
		for (int i = 0; i < m_psBlessCastleStatusData->sSettings.caGuardAmount[2]; i++)
			SERVERMAP->SpawnMonsterBC(pcBCMap, psCastleGuardC, saCastleGuardPositionC[i] << 8, iClanID);
	}

	SERVERCHAT->SendChatAllUsersInStage(MAPID_BlessCastle, CHATCOLOR_Global, "BlessCastle> Siege War started! Good Luck for all clans!");
}
void CServerBlessCastle::End(BOOL bUnitsAlive)
{
	Map * pcBCMap = SERVERMAP->GetMap(MAPID_BlessCastle);

	m_psBlessCastleStatusData->iCastleMode = 3;
	m_psBlessCastleStatusData->dwBattleOverTime = TICKCOUNT + 5000;

	for (int i = 0; i < MAX_UNITS; i++)
	{
		Unit * pcUnit = UNITSDATA + i;

		if (pcUnit->bActive && pcUnit->pcMap == pcBCMap && pcUnit->sCharacterData.iType == CHARACTERTYPE_Monster)
		{
			if (bUnitsAlive && pcUnit->sCharacterData.iMonsterEffectID == MONSTEREFFECTID_CASTLE_TOWER_B)
			{
				pcUnit->sCharacterData.sHP.sMin = pcUnit->sCharacterData.sHP.sMax;
				pcUnit->SetMotionFromCode(ANIMATIONTYPE_Idle);
			}
			else
			{
				pcUnit->sCharacterData.sHP.sMin = 0;
				pcUnit->SetMotionFromCode(ANIMATIONTYPE_Die);
			}
		}
	}

	//Spawn NPCs
	for (UINT i = 0; i < MAX_NPCINMAP; i++)
	{
		PacketUnitInfo * psNPC = pcBCMap->saNPC + i;

		if ((psNPC->iHeader != 0))
			SERVERMAP->SpawnNPC(pcBCMap, psNPC);
	}
}
void CServerBlessCastle::End()
{
	Map * pcBCMap = SERVERMAP->GetMap(MAPID_BlessCastle);

	m_psBlessCastleStatusData->iCastleMode = 0;
	m_psBlessCastleStatusData->saTimeSec[0] = 0;
	m_psBlessCastleStatusData->saTimeSec[1] = 0;

	ZeroMemory(m_psBlessCastleStatusData->sSettings.caGuardAmount, sizeof(char) * 4);
	ZeroMemory(m_psBlessCastleStatusData->sSettings.saTowerType, sizeof(short) * 12);

	DELETA(m_psBlessCastleStatusData->psaDamageData);

	for (int i = 0; i < MAX_UNITS; i++)
	{
		Unit * pc = UNITSDATA + i;

		if (pc->bActive && pc->pcMap == pcBCMap)
		{
			pc->Close();

			if (SERVERMAP->DelMonsterSpawn(pcBCMap, pc))
				pcBCMap->iNumAliveUnitData--;
		}
	}

	//Spawn NPCs
	for (UINT i = 0; i < MAX_NPCINMAP; i++)
	{
		PacketUnitInfo * psNPC = pcBCMap->saNPC + i;

		if ((psNPC->iHeader != 0))
			SERVERMAP->SpawnNPC(pcBCMap, psNPC);
	}

	SERVERCHAT->SendChatAllUsersInStage(MAPID_BlessCastle, CHATCOLOR_Global, "BlessCastle> Siege War has finished! thanks for joining...");

	if (m_psBlessCastlePVPLeague->iMode)
	{
		m_psBlessCastlePVPLeague->iMode = 0;
		m_psBlessCastlePVPLeague->dwEndTime = 0;
		m_psBlessCastlePVPLeague->dwRestartTime = 0;
	}
}
void CServerBlessCastle::SetSiegeWarMode(ESiegeWarMode iNewMode)
{
	m_iBlessCastleMode = iNewMode;
}
void CServerBlessCastle::SendUserScore(User * pcUser)
{
	if (m_psBlessCastleStatusData->iCastleMode <= 0)
		return;

	PacketBlessCastleUserScoreUpdate s;

	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);

	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT [BlessCastleScore] FROM CharacterInfo WHERE Name=?"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_String, SERVERCHARACTER->GetCharacterName(pcUser));

			if (pcDB->Execute() && pcDB->Fetch())
			{
				pcDB->GetData(1, PARAMTYPE_Integer, &pcUser->iBlessCastleScore);

				s.iLength = sizeof(PacketBlessCastleUserScoreUpdate);
				s.iHeader = PKTHDR_BlessCastleUserScoreUpdate;
				s.iUserScore = pcUser->iBlessCastleScore;

				SENDPACKET(pcUser, &s);
			}
		}

		pcDB->Close();
	}
}
void CServerBlessCastle::NetSendBlessCastleStatus(NetConnection * psNetConnection)
{
	BlessCastleStatusShort sBlessCastleStatusShort = { 0 };

	sBlessCastleStatusShort.iClanID = m_psBlessCastleStatusData->iClanID;
	sBlessCastleStatusShort.iTax = m_psBlessCastleStatusData->iTax;
	sBlessCastleStatusShort.iSkill = (int)m_psBlessCastleStatusData->iSkill;
	sBlessCastleStatusShort.iaTowerType[0] = (int)(m_psBlessCastleStatusData->sSettings.saTowerType[0]);
	sBlessCastleStatusShort.iaTowerType[1] = (int)(m_psBlessCastleStatusData->sSettings.saTowerType[1]);
	sBlessCastleStatusShort.iaTowerType[2] = (int)(m_psBlessCastleStatusData->sSettings.saTowerType[2]);
	sBlessCastleStatusShort.iaTowerType[3] = (int)(m_psBlessCastleStatusData->sSettings.saTowerType[3]);
	sBlessCastleStatusShort.iaTowerType[4] = (int)(m_psBlessCastleStatusData->sSettings.saTowerType[4]);
	sBlessCastleStatusShort.iaTowerType[5] = (int)(m_psBlessCastleStatusData->sSettings.saTowerType[5]);
	sBlessCastleStatusShort.iaGuardAmount[0] = (int)(m_psBlessCastleStatusData->sSettings.caGuardAmount[0]);
	sBlessCastleStatusShort.iaGuardAmount[1] = (int)(m_psBlessCastleStatusData->sSettings.caGuardAmount[1]);
	sBlessCastleStatusShort.iaGuardAmount[2] = (int)(m_psBlessCastleStatusData->sSettings.caGuardAmount[2]);

	PacketNetBCStatus sPacketNet;
	sPacketNet.iLength = sizeof(PacketNetBCStatus);
	sPacketNet.iHeader = PKTHDR_NetBCStatusSnd;
	CopyMemory(&sPacketNet.sBlessCastleStatus, &sBlessCastleStatusShort, sizeof(sPacketNet.sBlessCastleStatus));

	if (psNetConnection == NULL)
		SERVERNET->SendPacketGameServers(&sPacketNet);
	else
		SERVERNET->SendPacket(psNetConnection->pcSocketData, &sPacketNet);
}
void CServerBlessCastle::NetRecvBlessCastleStatus(PacketNetBCStatus * psPacket)
{
	BlessCastleStatusShort sBlessCastleStatusShort = { 0 };

	memcpy(&sBlessCastleStatusShort, &psPacket->sBlessCastleStatus, sizeof(sBlessCastleStatusShort));

	m_psBlessCastleStatusData->iClanID = sBlessCastleStatusShort.iClanID;
	m_psBlessCastleStatusData->iTax = sBlessCastleStatusShort.iTax;
	m_psBlessCastleStatusData->iTaxNow = sBlessCastleStatusShort.iTax;
	m_psBlessCastleStatusData->iSkill = sBlessCastleStatusShort.iSkill;
	m_psBlessCastleStatusData->sSettings.iTax = sBlessCastleStatusShort.iTax;
	m_psBlessCastleStatusData->sSettings.saTowerType[0] = (short)(sBlessCastleStatusShort.iaTowerType[0]);
	m_psBlessCastleStatusData->sSettings.saTowerType[1] = (short)(sBlessCastleStatusShort.iaTowerType[1]);
	m_psBlessCastleStatusData->sSettings.saTowerType[2] = (short)(sBlessCastleStatusShort.iaTowerType[2]);
	m_psBlessCastleStatusData->sSettings.saTowerType[3] = (short)(sBlessCastleStatusShort.iaTowerType[3]);
	m_psBlessCastleStatusData->sSettings.saTowerType[4] = (short)(sBlessCastleStatusShort.iaTowerType[4]);
	m_psBlessCastleStatusData->sSettings.saTowerType[5] = (short)(sBlessCastleStatusShort.iaTowerType[5]);
	m_psBlessCastleStatusData->sSettings.caGuardAmount[0] = (unsigned char)(sBlessCastleStatusShort.iaGuardAmount[0]);
	m_psBlessCastleStatusData->sSettings.caGuardAmount[1] = (unsigned char)(sBlessCastleStatusShort.iaGuardAmount[1]);
	m_psBlessCastleStatusData->sSettings.caGuardAmount[2] = (unsigned char)(sBlessCastleStatusShort.iaGuardAmount[2]);
	m_psBlessCastleStatusData->sSettings.iSkill = sBlessCastleStatusShort.iSkill;

	if (!GAME_SERVER)
		SQLWriteBlessCastleStatus();
}
void CServerBlessCastle::SQLUpdateUserScore(User * pcUser)
{
	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);

	if (pcDB->Open())
	{
		if (pcDB->Prepare("UPDATE CharacterInfo SET [BlessCastleScore]=? WHERE Name=?"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_Integer, &pcUser->iBlessCastleScore);
			pcDB->BindParameterInput(2, PARAMTYPE_String, SERVERCHARACTER->GetCharacterName(pcUser));

			pcDB->Execute();
		}

		pcDB->Close();
	}
}

void CServerBlessCastle::SQLWriteBlessCastleStatus()
{
	if (!GAME_SERVER)
	{
		BlessCastleStatusShort sBlessCastleStatusShort = { 0 };

		sBlessCastleStatusShort.iClanID = m_psBlessCastleStatusData->iClanID;
		sBlessCastleStatusShort.iTax = m_psBlessCastleStatusData->iTax;
		sBlessCastleStatusShort.iSkill = (int)m_psBlessCastleStatusData->iSkill;
		sBlessCastleStatusShort.iaTowerType[0] = (int)(m_psBlessCastleStatusData->sSettings.saTowerType[0]);
		sBlessCastleStatusShort.iaTowerType[1] = (int)(m_psBlessCastleStatusData->sSettings.saTowerType[1]);
		sBlessCastleStatusShort.iaTowerType[2] = (int)(m_psBlessCastleStatusData->sSettings.saTowerType[2]);
		sBlessCastleStatusShort.iaTowerType[3] = (int)(m_psBlessCastleStatusData->sSettings.saTowerType[3]);
		sBlessCastleStatusShort.iaTowerType[4] = (int)(m_psBlessCastleStatusData->sSettings.saTowerType[4]);
		sBlessCastleStatusShort.iaTowerType[5] = (int)(m_psBlessCastleStatusData->sSettings.saTowerType[5]);
		sBlessCastleStatusShort.iaGuardAmount[0] = (int)(m_psBlessCastleStatusData->sSettings.caGuardAmount[0]);
		sBlessCastleStatusShort.iaGuardAmount[1] = (int)(m_psBlessCastleStatusData->sSettings.caGuardAmount[1]);
		sBlessCastleStatusShort.iaGuardAmount[2] = (int)(m_psBlessCastleStatusData->sSettings.caGuardAmount[2]);

		SQLConnection * pcDB = SQLCONNECTION(DATABASEID_ServerDB);

		if (pcDB->Open())
		{
			if (pcDB->Prepare("UPDATE BlessCastleSettings SET ClanID=?,Tax=?,Skill=?,Tower1Type=?,Tower2Type=?,Tower3Type=?,Tower4Type=?,Tower5Type=?,Tower6Type=?,Guard1Amount=?,Guard2Amount=?,Guard3Amount=?"))
			{
				pcDB->BindParameterInput(1, PARAMTYPE_Integer, &sBlessCastleStatusShort.iClanID);
				pcDB->BindParameterInput(2, PARAMTYPE_Integer, &sBlessCastleStatusShort.iTax);
				pcDB->BindParameterInput(3, PARAMTYPE_Integer, &sBlessCastleStatusShort.iSkill);
				pcDB->BindParameterInput(4, PARAMTYPE_Integer, &sBlessCastleStatusShort.iaTowerType[0]);
				pcDB->BindParameterInput(5, PARAMTYPE_Integer, &sBlessCastleStatusShort.iaTowerType[1]);
				pcDB->BindParameterInput(6, PARAMTYPE_Integer, &sBlessCastleStatusShort.iaTowerType[2]);
				pcDB->BindParameterInput(7, PARAMTYPE_Integer, &sBlessCastleStatusShort.iaTowerType[3]);
				pcDB->BindParameterInput(8, PARAMTYPE_Integer, &sBlessCastleStatusShort.iaTowerType[4]);
				pcDB->BindParameterInput(9, PARAMTYPE_Integer, &sBlessCastleStatusShort.iaTowerType[5]);
				pcDB->BindParameterInput(10, PARAMTYPE_Integer, &sBlessCastleStatusShort.iaGuardAmount[0]);
				pcDB->BindParameterInput(11, PARAMTYPE_Integer, &sBlessCastleStatusShort.iaGuardAmount[1]);
				pcDB->BindParameterInput(12, PARAMTYPE_Integer, &sBlessCastleStatusShort.iaGuardAmount[2]);

				pcDB->Execute();
			}

			pcDB->Close();
		}

		NetSendBlessCastleStatus();
	}
}

void CServerBlessCastle::ResetUserScore()
{
	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);

	if (pcDB->Open())
	{
		if (pcDB->Prepare("UPDATE CharacterInfo SET [BlessCastleScore]=0"))
		{
			pcDB->Execute();
		}

		pcDB->Close();
	}
}

void CServerBlessCastle::UpdateIndividualScores(BOOL bReset)
{
	for (int i = 0; i < PLAYERS_MAX; i++)
	{
		User * pcUser = &USERSDATA[i];

		if (pcUser->pcSocketData && pcUser->iID && pcUser->iMapID == MAPID_BlessCastle && pcUser->iBlessCastleScore > 0)
		{
			if (bReset)
				pcUser->iBlessCastleScore = 0;

			SQLUpdateUserScore(pcUser);
		}
	}
}
void CServerBlessCastle::SendIndividualScore()
{
	PacketBlessCastleTopIndividual s1, s2;

	ZeroMemory(&s1, sizeof(PacketBlessCastleTopIndividual));
	ZeroMemory(&s2, sizeof(PacketBlessCastleTopIndividual));

	s1.iLength = sizeof(PacketBlessCastleTopIndividual);
	s1.iHeader = PKTHDR_BlessCastleIndividualScore;
	s1.iMode = GetSiegeWarMode();

	s2.iLength = sizeof(PacketBlessCastleTopIndividual);
	s2.iHeader = PKTHDR_BlessCastleIndividualScore;
	s2.iMode = GetSiegeWarMode();

	int i = 0;

	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);

	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT TOP 3 [Name],[JobCode],[BlessCastleScore] FROM CharacterInfo ORDER BY BlessCastleScore DESC"))
		{
			if (pcDB->Execute())
			{
				while (pcDB->Fetch())
				{
					pcDB->GetData(1, PARAMTYPE_String, s1.szCharacterName[i], 32);
					pcDB->GetData(2, PARAMTYPE_Integer, &s1.iClass[i]);
					pcDB->GetData(3, PARAMTYPE_Integer, &s1.iDamage[i]);

					i++;
				}
			}
		}

		pcDB->Close();
	}

	if (i > 0)
	{
		if (CanShowScore())
		{
			SENDPACKETSTAGE(&s1, MAPID_BlessCastle);
		}
		else
		{
			for (int i = 0; i < PLAYERS_MAX; i++)
			{
				User * pcUser = &USERSDATA[i];

				if (pcUser->pcSocketData && pcUser->iID && pcUser->iMapID == MAPID_BlessCastle)
				{
					SENDPACKET(pcUser, pcUser->iGameLevel >= GAMELEVEL_Two ? &s1 : &s2);
				}
			}
		}
	}
}
BOOL CServerBlessCastle::CanShowScore()
{
	BOOL bRet = TRUE;

	if (GetSiegeWarMode() == SIEGEWARMODE_TheMassacre)
	{
		bRet = FALSE;

		DWORD dwTime = m_psBlessCastleStatusData->dwBattleOverTime - m_psBlessCastleStatusData->dwStartTime;

		//5 minutes or less than? Show score
		if ((5 * 60 * 1000) >= dwTime)
			bRet = TRUE;
	}

	return bRet;
}

void CServerBlessCastle::KillBuffs()
{
	for (int i = 0; i < PLAYERS_MAX; i++)
	{
		User * pcUser = &USERSDATA[i];

		if (pcUser->pcSocketData && pcUser->iID)
		{
			pcUser->dwBlessSkill_Code = 0;
			pcUser->dwBlessSkill_Time = 0;
		}
	}
}
void CServerBlessCastle::HandleIndividualScore()
{
	char szAccountName[3][32] = { 0 };
	char szCharacterName[3][32] = { 0 };
	int iCharacterScore[3] = { 0 };
	char szGold[32] = { 0 };

	UpdateIndividualScores();

	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);

	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT TOP 3 [AccountName],[Name],[BlessCastleScore] FROM CharacterInfo ORDER BY BlessCastleScore DESC"))
		{
			int i = 0;

			if (pcDB->Execute())
			{
				while (pcDB->Fetch())
				{
					pcDB->GetData(1, PARAMTYPE_String, szAccountName[i], 32);
					pcDB->GetData(2, PARAMTYPE_String, szCharacterName[i], 32);
					pcDB->GetData(3, PARAMTYPE_Integer, &iCharacterScore[i]);

					i++;
				}
			}
		}

		pcDB->Close();

		//Conquest Mode?
		if ((GetSiegeWarMode() == SIEGEWARMODE_TheConquest) || (GetSiegeWarMode() == SIEGEWARMODE_TheMassacre))
		{
			SERVERCHAT->SendChatAll(CHATCOLOR_Global, "BlessCastle> Player Top Scores:");

			if (szCharacterName[0] && iCharacterScore[0] > 0)
			{
				STRINGCOPY(szGold, FormatNumber(30000000));
				SERVERCHAT->SendChatAllEx(CHATCOLOR_Global, "BlessCastle> 1st Place: %s", szCharacterName[0]);
				SERVERCHAT->SendChatAllEx(CHATCOLOR_Global, "BlessCastle> %s Points, %s gp!", FormatNumber(iCharacterScore[0]), szGold);
				DISTRIBUTORHANDLE->AddItemOpenBox(szAccountName[0], "GG101", 0, 30000000);
			}
			if (szCharacterName[1] && iCharacterScore[1] > 0)
			{
				STRINGCOPY(szGold, FormatNumber(20000000));
				SERVERCHAT->SendChatAllEx(CHATCOLOR_Global, "BlessCastle> 2nd Place: %s", szCharacterName[1]);
				SERVERCHAT->SendChatAllEx(CHATCOLOR_Global, "BlessCastle> %s Points, %s gp!", FormatNumber(iCharacterScore[1]), szGold);
				DISTRIBUTORHANDLE->AddItemOpenBox(szAccountName[1], "GG101", 0, 20000000);
			}
			if (szCharacterName[2] && iCharacterScore[2] > 0)
			{
				STRINGCOPY(szGold, FormatNumber(10000000));
				SERVERCHAT->SendChatAllEx(CHATCOLOR_Global, "BlessCastle> 3rd Place: %s", szCharacterName[2]);
				SERVERCHAT->SendChatAllEx(CHATCOLOR_Global, "BlessCastle> %s Points, %s gp!", FormatNumber(iCharacterScore[2]), szGold);
				DISTRIBUTORHANDLE->AddItemOpenBox(szAccountName[2], "GG101", 0, 10000000);
			}
		}
	}

	UpdateIndividualScores(TRUE);
}
void CServerBlessCastle::GetTop10ClanDamage(Unit * pcUnit, PacketBlessCastleTopData * psPacket)
{
	if (psPacket)
	{
		BlessCastleStatusData * psBC = m_psBlessCastleStatusData;

		AttackDamageData sAttackDamageData[ATTACK_DAMAGE_MAX];

		ZeroMemory(psPacket, sizeof(PacketBlessCastleTopData));

		BOOL bRet = FALSE;

		if (pcUnit->psaDamageUsersData) 
		{
			memcpy(sAttackDamageData, pcUnit->psaDamageUsersData, sizeof(AttackDamageData) * ATTACK_DAMAGE_MAX);
			bRet = TRUE;
		}
		else if (psBC->psaDamageData)
		{
			memcpy(sAttackDamageData, psBC->psaDamageData, sizeof(AttackDamageData) * ATTACK_DAMAGE_MAX);
			bRet = TRUE;
		}

		if (bRet)
		{
			int iTotalDamage = 0;

			for (int i = 0; i < ATTACK_DAMAGE_MAX; i++)
			{
				iTotalDamage += sAttackDamageData[i].iDamage;
			}

			for (int i = 0; i < 10; i++) 
			{
				int iIndex = -1;

				for (int j = 0; j < ATTACK_DAMAGE_MAX; j++)
				{
					AttackDamageData * pAttackDamageData = sAttackDamageData + j;

					if (pAttackDamageData->iID &&
						GetClanCodeByID(pAttackDamageData->iID) != psBC->iClanID &&
						pAttackDamageData->iDamage > psPacket->iDamage[i]) 
					{
						psPacket->iUserID[i] = pAttackDamageData->iID;
						psPacket->iDamage[i] = pAttackDamageData->iDamage;
						psPacket->iCounter[i] = pAttackDamageData->iCounter;

						iIndex = j;
					}
				}

				if (iIndex >= 0)
					sAttackDamageData[iIndex].iID = 0;
			}

			psPacket->baCrystalTowerCount[0] = psBC->baCrystalTowerCount[0];
			psPacket->baCrystalTowerCount[1] = psBC->baCrystalTowerCount[1];
			psPacket->baCrystalTowerCount[2] = psBC->baCrystalTowerCount[2];
			psPacket->baCrystalTowerCount[3] = psBC->baCrystalTowerCount[3];
			psPacket->dwUpdateTime = TICKCOUNT;

			psPacket->iHeader = PKTHDR_BlessCastleShowDamage;
			psPacket->iLength = sizeof(PacketBlessCastleTopData);
			psPacket->dwTotalDamage = iTotalDamage;

			if (psBC->dwScoreTime && psBC->dwScoreTime < TICKCOUNT)
				psBC->dwScoreTime = TICKCOUNT + 5 * 60 * 1000;
		}
	}
}
void CServerBlessCastle::SQLReadBlessCastleStatus()
{
	if (!GAME_SERVER)
	{
		BlessCastleStatusShort sBlessCastleStatusShort = { 0 };

		SQLConnection * pcDB = SQLCONNECTION(DATABASEID_ServerDB);

		if (pcDB->Open())
		{
			if (pcDB->Prepare("SELECT ClanID,Tax,Skill,Tower1Type,Tower2Type,Tower3Type,Tower4Type,Tower5Type,Tower6Type,Guard1Amount,Guard2Amount,Guard3Amount FROM BlessCastleSettings"))
			{
				if (pcDB->Execute())
				{
					if (pcDB->Fetch())
					{
						pcDB->GetData(1, PARAMTYPE_Integer, &sBlessCastleStatusShort.iClanID, 0);
						pcDB->GetData(2, PARAMTYPE_Integer, &sBlessCastleStatusShort.iTax, 0);
						pcDB->GetData(3, PARAMTYPE_Integer, &sBlessCastleStatusShort.iSkill, 0);
						pcDB->GetData(4, PARAMTYPE_Integer, &sBlessCastleStatusShort.iaTowerType[0], 0);
						pcDB->GetData(5, PARAMTYPE_Integer, &sBlessCastleStatusShort.iaTowerType[1], 0);
						pcDB->GetData(6, PARAMTYPE_Integer, &sBlessCastleStatusShort.iaTowerType[2], 0);
						pcDB->GetData(7, PARAMTYPE_Integer, &sBlessCastleStatusShort.iaTowerType[3], 0);
						pcDB->GetData(8, PARAMTYPE_Integer, &sBlessCastleStatusShort.iaTowerType[4], 0);
						pcDB->GetData(9, PARAMTYPE_Integer, &sBlessCastleStatusShort.iaTowerType[5], 0);
						pcDB->GetData(10, PARAMTYPE_Integer, &sBlessCastleStatusShort.iaGuardAmount[0], 0);
						pcDB->GetData(11, PARAMTYPE_Integer, &sBlessCastleStatusShort.iaGuardAmount[1], 0);
						pcDB->GetData(12, PARAMTYPE_Integer, &sBlessCastleStatusShort.iaGuardAmount[2], 0);
					}
				}
			}

			pcDB->Close();
		}

		m_psBlessCastleStatusData->iClanID = sBlessCastleStatusShort.iClanID;
		m_psBlessCastleStatusData->iTax = sBlessCastleStatusShort.iTax;
		m_psBlessCastleStatusData->iTaxNow = sBlessCastleStatusShort.iTax;
		m_psBlessCastleStatusData->iSkill = sBlessCastleStatusShort.iSkill;
		m_psBlessCastleStatusData->sSettings.iTax = sBlessCastleStatusShort.iTax;
		m_psBlessCastleStatusData->sSettings.saTowerType[0] = (short)(sBlessCastleStatusShort.iaTowerType[0]);
		m_psBlessCastleStatusData->sSettings.saTowerType[1] = (short)(sBlessCastleStatusShort.iaTowerType[1]);
		m_psBlessCastleStatusData->sSettings.saTowerType[2] = (short)(sBlessCastleStatusShort.iaTowerType[2]);
		m_psBlessCastleStatusData->sSettings.saTowerType[3] = (short)(sBlessCastleStatusShort.iaTowerType[3]);
		m_psBlessCastleStatusData->sSettings.saTowerType[4] = (short)(sBlessCastleStatusShort.iaTowerType[4]);
		m_psBlessCastleStatusData->sSettings.saTowerType[5] = (short)(sBlessCastleStatusShort.iaTowerType[5]);
		m_psBlessCastleStatusData->sSettings.caGuardAmount[0] = (unsigned char)(sBlessCastleStatusShort.iaGuardAmount[0]);
		m_psBlessCastleStatusData->sSettings.caGuardAmount[1] = (unsigned char)(sBlessCastleStatusShort.iaGuardAmount[1]);
		m_psBlessCastleStatusData->sSettings.caGuardAmount[2] = (unsigned char)(sBlessCastleStatusShort.iaGuardAmount[2]);
		m_psBlessCastleStatusData->sSettings.iSkill = sBlessCastleStatusShort.iSkill;
		NetSendBlessCastleStatus();
	}
	else
	{
		Packet sPacket;
		sPacket.iLength = sizeof(sPacket);
		sPacket.iHeader = PKTHDR_NetBCStatusReq;

		NetConnection * nc = SERVERNET->GetLoginServerConnection();
		if (nc)
			SERVERNET->SendPacket(nc->pcSocketData, &sPacket);
	}
}
void CServerBlessCastle::SetBlessCastleOwnerClanID(DWORD iClanID)
{
	m_psBlessCastleStatusData->iClanID = iClanID;

	SQLWriteBlessCastleStatus();
}
void CServerBlessCastle::HandlePacket(User *pcUser, PacketBlessCastleStatusSettingsData * psPacket)
{
	BlessCastleStatusData * psBC = m_psBlessCastleStatusData;

	if (pcUser->iClanID == m_psBlessCastleStatusData->iClanID || pcUser->iGameLevel > GAMELEVEL_Three)
	{
		Map * pcMap = SERVERMAP->GetMap(MAPID_BlessCastle);

		if (pcMap)
		{
			CopyMemory(&psBC->sSettings, psPacket, sizeof(PacketBlessCastleStatusSettingsData));

			psBC->iTaxNow = psBC->sSettings.iTax;

			NetSendBlessCastleStatus(SERVERNET->GetLoginServerConnection());
		}
	}
}
void CServerBlessCastle::HandlePacket(User *pcUser, PacketBlessCastleTex * psPacket)
{
	BlessCastleStatusData * psBC = m_psBlessCastleStatusData;

	if (psPacket->iTax != psBC->iTax) 
	{
		PacketBlessCastleTex sPacket;

		sPacket.iLength = sizeof(PacketBlessCastleTex);
		sPacket.iHeader = PKTHDR_BlessCastleTax;
		sPacket.iClanID = psBC->iClanID;
		sPacket.iTax = psBC->iTax;

		SENDPACKET(pcUser, &sPacket);
	}
}
void CServerBlessCastle::HandlePacket(User * pcUser, PacketBlessCastleSkill * psPacket)
{
	if (!GAME_SERVER)
		return;

	if (psPacket->iChk == GetBlessCastleSkillSum(pcUser, psPacket))
	{
		switch (psPacket->iSkill) 
		{
		case SIN_CLANSKILL_ABSORB:
			pcUser->dwBlessSkill_Code = SKILL_PLAY_BLESS_ABSORB;
			pcUser->dwBlessSkill_Time = TICKCOUNT + 1000 * 60 * 10;
			pcUser->dwBlessSkill_Param = 20;
			break;
		case SIN_CLANSKILL_DAMAGE:
			pcUser->dwBlessSkill_Code = SKILL_PLAY_BLESS_DAMAGE;
			pcUser->dwBlessSkill_Time = TICKCOUNT + 1000 * 60 * 10;
			pcUser->dwBlessSkill_Param = 15;
			break;
		case SIN_CLANSKILL_EVASION:
			pcUser->dwBlessSkill_Code = SKILL_PLAY_BLESS_EVADE;
			pcUser->dwBlessSkill_Time = TICKCOUNT + 1000 * 60 * 10;
			pcUser->dwBlessSkill_Param = 20;
			break;
		}

		SERVERCHAT->SendDebugChat(pcUser, CHATCOLOR_Error, "> Process Clan Skill[%d] ( %d )", SERVER_CODE, psPacket->iSkill);
	}
}
void CServerBlessCastle::ProcessPacket(User * pcUser)
{
	PacketBlessCastleStatusSettingsData sPacket;

	BlessCastleStatusData * psBC = m_psBlessCastleStatusData;

	CopyMemory(&sPacket, &psBC->sSettings, sizeof(PacketBlessCastleStatusSettingsData));

	sPacket.iLength = sizeof(PacketBlessCastleStatusSettingsData);
	sPacket.iHeader = PKTHDR_BlessCastleInfomation;
	sPacket.iClanID = psBC->iClanID;
	sPacket.iPrice = 0;

	if (pcUser->iClanID == psBC->iClanID || pcUser->iGameLevel != GAMELEVEL_None)
		SENDPACKET(pcUser, &sPacket);
}
void CServerBlessCastle::SendBlessCastleSkill(User * pcUser)
{
	BlessCastleStatusData * psBC = m_psBlessCastleStatusData;

	if (pcUser->iClanID && pcUser->iClanID == psBC->iClanID)
	{
		if (!pcUser->CastleMaster.Flag)
		{
			pcUser->CastleMaster.dwCheckTime = 0;
			pcUser->CastleMaster.SelectSkill = psBC->iSkill;
			pcUser->CastleMaster.Flag = TRUE;
		}

		if (pcUser->CastleMaster.dwCheckTime < TICKCOUNT)
		{
			PacketBlessCastleSkill sPacket;

			sPacket.iLength = sizeof(PacketBlessCastleSkill);
			sPacket.iHeader = PKTHDR_BlessCastleSkill;
			sPacket.iSkill	= psBC->iSkill;
			sPacket.iClanID = pcUser->iClanID;
			sPacket.iChk = GetBlessCastleSkillSum(pcUser, &sPacket);

			SENDPACKET(pcUser, &sPacket);

			pcUser->CastleMaster.dwCheckTime = TICKCOUNT + 1000 * 60;
		}
	}
}
void CServerBlessCastle::MainFountain()
{
	if (m_psBlessCastleStatusData->iClanID && m_psBlessCastleStatusData->iCastleMode == 0)
	{
		if (m_psBlessCastleStatusData->dwFountainTime < TICKCOUNT)
		{
			m_psBlessCastleStatusData->dwFountainTime = TICKCOUNT + 60 + 1000;

			if (m_psBlessCastleStatusData->iFountainPotionCount < 1440)
				m_psBlessCastleStatusData->iFountainPotionCount++;
		}

		if (m_psBlessCastleStatusData->iFountainPotionCount && m_psBlessCastleStatusData->dwFountainLastUseTime < TICKCOUNT)
		{
			m_psBlessCastleStatusData->dwFountainLastUseTime = TICKCOUNT + 1000;

			int iCount = m_psBlessCastleStatusData->iFountainCountUsers + PLAYERS_MAX;

			for (int i = m_psBlessCastleStatusData->iFountainCountUsers + 1; i < iCount; i++)
			{
				int iIndex = i % PLAYERS_MAX;

				User * pcUser = USERSDATA + iIndex;

				if (pcUser && pcUser->iID && pcUser->iMapID == MAPID_BlessCastle)
				{
					if (m_psBlessCastleStatusData->iFountainPotionCount > 0 &&
						pcUser->iClanID &&
						pcUser->iClanID == m_psBlessCastleStatusData->iClanID &&
						pcUser->sPosition.iX > saCastleSoulFountainPosition[0].iX * 256 &&
						pcUser->sPosition.iX < saCastleSoulFountainPosition[1].iX * 256 &&
						pcUser->sPosition.iZ > saCastleSoulFountainPosition[0].iZ * 256 &&
						pcUser->sPosition.iZ < saCastleSoulFountainPosition[1].iZ * 256)
					{
						SERVERITEM->CreateItem(pcUser, 0x4010400);

						m_psBlessCastleStatusData->iFountainPotionCount--;

						SERVERCHAT->SendChatAllUsersInRange(pcUser->sPosition.iX,
							pcUser->sPosition.iZ,
							0x4B000,
							CHATCOLOR_Global,
							"> %s recived Mystic Mana. %d left.",
							SERVERCHARACTER->GetCharacterName(pcUser), m_psBlessCastleStatusData->iFountainPotionCount);
						
						m_psBlessCastleStatusData->iFountainCountUsers = iIndex;
						break;
					}
				}
			}
		}
	}
}
int CServerBlessCastle::UpdateTower()
{
	int iCountTower = 0;

	BlessCastleStatusData * psBC = m_psBlessCastleStatusData;

	if (psBC->baCrystalTowerCount[0])
		iCountTower += (int)psBC->baCrystalTowerCount[0];
	if (psBC->baCrystalTowerCount[1])
		iCountTower += (int)psBC->baCrystalTowerCount[1];
	if (psBC->baCrystalTowerCount[2])
		iCountTower += (int)psBC->baCrystalTowerCount[2];
	if (psBC->baCrystalTowerCount[3])
		iCountTower += (int)psBC->baCrystalTowerCount[3];

	return iCountTower;
}
void CServerBlessCastle::UpdatePhase(int iPhase)
{
	PacketSiegeWarPhase sPacket;
	sPacket.iLength = sizeof(PacketSiegeWarPhase);
	sPacket.iHeader = PKTHDR_UpdateSWPhase;
	sPacket.iPhaseID = iPhase;
	SENDPACKETSTAGE(&sPacket, MAPID_BlessCastle, TRUE);
}
int CServerBlessCastle::GetBlessCastleSkillSum(User * pcUser, PacketBlessCastleSkill * psPacket)
{
	DWORD dwSum = 0x0c3c5645;

	dwSum ^= psPacket->iSkill << 2;
	dwSum ^= psPacket->iClanID << 6;
	dwSum ^= pcUser->iID << 16;

	return dwSum;
}