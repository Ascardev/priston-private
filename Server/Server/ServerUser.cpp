#include "StdAfx.h"
#include "ServerUser.h"
#include "SrcServer/onserver.h"

CServerUser::CServerUser()
{
	pcaUserInGame = new User *[PLAYERS_MAX + 256];
	pcaUser = new User[PLAYERS_MAX + 256];

	pcaCharacterFile = new CharacterFile[PLAYERS_MAX + 256];

	for (int i = 0; i < PLAYERS_MAX + 256; i++)
	{
		User * u = pcaUser + i;

		ZeroMemory(u, sizeof(User));

		u->uIndex = i;
	}

	for (int i = 0; i < PLAYERS_MAX + 256; i++)
	{
		CharacterFile *p = pcaCharacterFile + i;

		ZeroMemory(p, sizeof(CharacterFile));
	}
}
CServerUser::~CServerUser()
{
	DELETA(pcaUserInGame);
	DELETA(pcaCharacterFile);
	DELETA(pcaUser);
}
User *CServerUser::GetFreeUser()
{
	for (int i = 0; i < PLAYERS_MAX; i++)
	{
		User * u = USERSDATA + i;

		if (!u->bInUse)
		{
			u->Init(i);
			u->uIndex = i;

			return u;
		}
	}

	//Error;
	return nullptr;
}
void CServerUser::AddReconnectUser(User * pcUser)
{
	BOOL bHave = FALSE;

	for (int i = PLAYERS_MAX; i < PLAYERS_MAX + 256; i++)
	{
		User *u = USERSDATA + i;

		if (u->szAccountName[0] && STRINGCOMPAREI(u->szAccountName, pcUser->szAccountName) && pcUser->iID == u->iID)
		{
			bHave = TRUE;

			if (pcUser->bWarehouseOpen)
				u->szAccountName[0] = 0;

			break;
		}
	}

	if (pcUser->bWarehouseOpen)
		return;

	if (bHave == FALSE)
	{
		SERVERUSER->SetUserID(pcUser);

		static int iReconnectWheel = 0;

		int i = (iReconnectWheel % 255) + PLAYERS_MAX;

		User * u = pcUser + i;

		SocketData *pcSocketData = pcUser->pcSocketData;

		CopyMemory(u, pcUser, sizeof(User));

		u->bInUse = TRUE;
		u->uIndex = i;
		u->psCharacterFile = CHARSDATA + i;

		if (pcUser->psCharacterFile)
		{
			CopyMemory(u->psCharacterFile, pcUser->psCharacterFile, sizeof(CharacterFile));
		}

		u->psCharacterData = nullptr;

		u->bParty = FALSE;
		u->psParty = NULL;

		iReconnectWheel++;
	}

	DELET(pcUser->psCharacterData);
}
BOOL CServerUser::DeleteReconnectUser(const char * pszAccountName)
{
	BOOL bRet = FALSE;

	for (int i = PLAYERS_MAX; i < PLAYERS_MAX + 256; i++)
	{
		User * u = USERSDATA + i;
		if (u->szAccountName[0] && STRINGCOMPAREI(u->szAccountName, pszAccountName))
		{
			u->szAccountName[0] = 0;

			bRet = TRUE;
			break;
		}
	}

	return bRet;
}
void CServerUser::ReconnectUser(User * pcUser, struct PacketReconnectUser * psPacket)
{
	SocketData * pcSocket = pcUser->pcSocketData;

	for (int i = PLAYERS_MAX; i < PLAYERS_MAX + 256; i++)
	{
		User * u = USERSDATA + i;

		if (u && u->bNetServer == FALSE && u->szAccountName[0] && (psPacket->dwObjectID == u->iID) && STRINGCOMPAREI(u->szAccountName, psPacket->szUserID) && u != pcUser && pcUser->pcSocketData)
		{
			CharacterFile * pCharaerFile = pcUser->psCharacterFile;

			int iIndex = pcUser->uIndex;

			CopyMemory(pcUser, u, sizeof(User));

			pcUser->psCharacterFile = pCharaerFile;

			if (pcUser->psCharacterFile && u->psCharacterFile)
			{
				CopyMemory(pcUser->psCharacterFile, u->psCharacterFile, sizeof(CharacterFile));
				u->psCharacterFile->iLength = 0;
			}

			//Clearold
			ZeroMemory(u, sizeof(User));
			
			pcUser->uIndex = iIndex;
			pcUser->iID = psPacket->dwObjectID;
			pcUser->pcSocketData = pcSocket;

			SERVERUSER->UpdateID(pcUser);

			if ((pcUser->szAccountName[0] != 0) && (SERVERCHARACTER->GetCharacterName(pcUser)[0] != 0))
			{
				SERVERACCOUNT->SQLUserOnline(pcUser->szAccountName, "", "", 0, 1, 0, 0);
				SERVERACCOUNT->SQLUserOnline(pcUser->szAccountName,
					SERVERCHARACTER->GetCharacterName(pcUser),
					pcSocket->szIP,
					pcUser->iTicket,
					0,
					pcUser->sCharacterData.iClass,
					pcUser->sCharacterData.iLevel);
			}

			pcUser->bParty = FALSE;
			pcUser->psParty = NULL;

			SERVERSOCKET->AddReconnectedUser(pcUser);

			if (!GAME_SERVER)
				SENDPACKETBLANK(pcUser, PKTHDR_Save);

			break;
		}
	}
}
BOOL CServerUser::SetUserID(User * pcUser)
{
	if (pcUser && !pcUser->szAccountName[0])
	{
		char szUserID[32] = { 0 };
		ZeroMemory(szUserID, 32);
		char * pszCharName = SERVERCHARACTER->GetCharacterName(pcUser);

		SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);
		if (pcDB->Open())
		{
			if (pcDB->Prepare("SELECT AccountName FROM CharacterInfo WHERE Name=?"))
			{
				pcDB->BindParameterInput(1, PARAMTYPE_String, pszCharName);
				if (pcDB->Execute() && pcDB->Fetch())
				{
					pcDB->GetData(1, PARAMTYPE_String, szUserID, 32);
				}
			}
			pcDB->Close();
		}

		if (IsNull(szUserID))
			return FALSE;

		STRINGCOPY(pcUser->szAccountName, szUserID);

		return TRUE;
	}
	return FALSE;
}
void CServerUser::UpdateID(User * pcUser)
{
	if (pcUser)
	{
		pcUser->iCharacterID = SERVERCHARACTER->SQLGetCharacterID(SERVERCHARACTER->GetCharacterName(pcUser));
	}
}
void CServerUser::OnLoadUser(User * pcUser)
{
	SERVERUSER->UpdateID(pcUser);
	SERVERPVP->OnLoadUser(pcUser);
}
void CServerUser::OnUnLoadUser(User * pcUser)
{
	SERVERPVP->OnUnLoadUser(pcUser);
	SERVERITEM->OnUnLoadUser(pcUser);

	if (!GAME_SERVER)
	{
		SERVERCHARACTER->OnCharacterDataExSave(pcUser);
		SERVERNET->OnUnloadUser(pcUser);
	}
}
void CServerUser::Update()
{
	static UINT iWheel = 0;

	USERS_ONLINE = 0;

	for (int i = 0; i < PLAYERS_MAX; i++)
	{
		User *pcUser = USERSDATA + i;

		if (pcUser && pcUser->IsConnected())
		{
			if (pcUser->IsInGame())
			{
				pcaUserInGame[uUsersInGame] = pcUser;

				USERS_ONLINE++;

				if (GAME_SERVER)
				{
					UpdateUnitStatus(pcUser);
					UpdateSkillStatus(pcUser);

					if ((i % 16) == (iWheel % 16))
					{
						pcUser->b16 = TRUE;
					}
					else
					{
						pcUser->b16 = FALSE;
					}
					//Frame Check

					if ((i % 32) == (iWheel % 32))
					{
						//Status Update
						pcUser->b32 = TRUE;

						if ((i % 64) == (iWheel % 64))
						{
							//Deep Status Update
							pcUser->b64 = TRUE;
						}
						else
						{
							//No Deep Status Update
							pcUser->b64 = FALSE;
						}
					}
					else
					{
						// No Status Update
						pcUser->b32 = FALSE;
						pcUser->b64 = FALSE;
					}
				}
			}

			if ((i % 512) == (iWheel % 512))
			{
				DWORD dwDisconnectTime = pcUser->dwDisconnectTime;

				if (dwDisconnectTime != 0)
				{
					if (TICKCOUNT > dwDisconnectTime && pcUser->pcSocketData)
					{
						SocketData * sd = pcUser->pcSocketData;
						if ((sd->bKeepAlive == FALSE) && (pcUser->bNetServer == FALSE))
						{
							pcUser->dwDisconnectTime = 0;
							//LOGSERVER->LogSocketClose(sd, "UserServer::Update()::OldDisconnectTime", _ReturnAddress());
							WNDPROC_SOCKETCLOSE(SERVERSOCKET->GetHWND(), sd);
						}
					}
				}

				//Lag Grace
				DWORD dwTimeLastPacketReceived = 0;

				if (pcUser && pcUser->pcSocketData)
					dwTimeLastPacketReceived = pcUser->pcSocketData->dwTimeLastPacketReceived;

				if (dwTimeLastPacketReceived != 0)
				{
					SocketData * sd = pcUser->pcSocketData;

					if (sd && (sd->bKeepAlive == FALSE) && (pcUser->bNetServer == FALSE))
					{
						DWORD dwLag = TICKCOUNT - dwTimeLastPacketReceived;

						if (dwLag > 5 * 60 * 1000)
						{
							//LOGSERVER->LogSocketClose(sd, "UserServer::Update()::LagGrace", _ReturnAddress());
							WNDPROC_SOCKETCLOSE(SERVERSOCKET->GetHWND(), sd);
						}
					}
				}
			}
		}
	}

	iWheel++;
}
void CServerUser::UpdateUnitStatus(User * pcUser)
{
	//User Unit Status
	pcUser->sUnitStatusContainer.iHeader = PKTHDR_UnitStatusContainer;
	pcUser->sUnitStatusContainer.iCounter = pcUser->iUnitStatusCounter & 0x00FFFFFF;

	//Monster Unit Status
	pcUser->sUnitStatusContainerM.iHeader = PKTHDR_UnitStatusContainer;
	pcUser->sUnitStatusContainerM.iCounter = (pcUser->iUnitStatusCounter & 0x00FFFFFF) - 0x80000000;

	//Increment Status Counter
	pcUser->iUnitStatusCounter++;

	//Priority
	if (pcUser->iMovingIndex != 0)
	{
		pcUser->iMovingIndex++;

		UINT uPriorityCounter = (pcUser->uPriorityCounter++);

		if (pcUser->uPriority < 4)
		{
			if (uPriorityCounter > 1200)
			{
				pcUser->uPriority = 2;
			}
			else if (uPriorityCounter > 480)
			{
				pcUser->uPriority = 2;
			}
			else if (uPriorityCounter > 240)
			{
				pcUser->uPriority = 2;
			}
			else if (uPriorityCounter > 64)
			{
				pcUser->uPriority = 1;
			}
			else
			{
				pcUser->uPriority = 0;
			}
		}

		//AFK check
		if (uPriorityCounter > 1920)
		{
			pcUser->bAFK = TRUE;
		}
		else
		{
			pcUser->bAFK = FALSE;
		}
	}
	else
	{
		pcUser->uPriorityCounter = 0;
		pcUser->uPriority = 0;

		pcUser->bAFK = FALSE;
	}
}
void CServerUser::UpdateSkillStatus(User * pcUser)
{
	PacketSkillStatus & p = pcUser->sSkillStatus;

	p.iLength = sizeof(PacketSkillStatus);
	p.iHeader = PKTHDR_SkillStatus;
	p.iID = pcUser->GetID();

	//Lambda Function for repeatable usage
	auto SetSkillTime = [](short & sPacketLevel, short & sPacketTime, UINT & uUserLevel, DWORD & dwUserTimeOut)-> void
	{
		if (dwUserTimeOut)
		{
			if (dwUserTimeOut > TICKCOUNT)
			{
				sPacketLevel = (short)uUserLevel;
				sPacketTime = (short)(dwUserTimeOut - TICKCOUNT);
			}
			else
			{
				uUserLevel = 0;
				dwUserTimeOut = 0;
				sPacketTime = 0;
				sPacketLevel = 0;
			}
		}
		else
		{
			uUserLevel = 0;
			dwUserTimeOut = 0;
			sPacketTime = 0;
			sPacketLevel = 0;
		}
	};

	//Lethal Sight
	SetSkillTime(p.sLethalSightLevel, p.sLethalSightTimeLeft, pcUser->uLethalSightLevel, pcUser->dwLethalSightTimeOut);

	//Fierce Wind
	SetSkillTime(p.sFierceWindLevel, p.sFierceWindTimeLeft, pcUser->uFierceWindLevel, pcUser->dwFierceWindTimeOut);

	//Holy Conviction
	SetSkillTime(p.sHolyConvictionLevel, p.sHolyConvictionTimeLeft, pcUser->uHolyConvictionLevel, pcUser->dwHolyConvictionTimeOut);

	//Wizard Trance
	SetSkillTime(p.sWizardTranceLevel, p.sWizardTranceTimeLeft, pcUser->uWizardTranceLevel, pcUser->dwWizardTranceTimeOut);
}

void CServerUser::Loop()
{
	if (!GAME_SERVER)
		return;

	for (int i = 0, j = uUsersInGame; i < j; i++)
	{
		User * pcUser = pcaUserInGame[i];

		if (pcUser->b32)
		{
			DWORD dwTimeDifference = TICKCOUNT - pcUser->dwTimeLastPacket;

			if (dwTimeDifference < USER_STATUS_UPDATE_GRACE)
			{
				if (pcUser->b64)
				{
					//Send Unit Status of other Monsters to this User
					LoopUnits(pcUser);
				}

				//Send Unit Status of other Users to this User
				LoopUsers(pcUser);
			}
		}
	}
}
void CServerUser::LoopUsers(User * pcUser)
{
	//Update Party
	if (pcUser->bParty && pcUser->psParty)
		PARTYHANDLE->UpdatePartyData(pcUser, pcUser->psParty);

	//Do Chat Update?
	BOOL bChat = pcUser->szChat[0] != 0;

	//Do Status Update?
	BOOL bStatus = (pcUser->dwTimeLastStatusUpdate + USER_USER_STATUS_UPDATE_GRACE) >= TICKCOUNT;

	//Update Chat or Status?
	if (bChat || bStatus)
	{
		//Fill Chat Packet
		PacketChatBoxMessage sPacketChat;

		if (bChat)
		{
			sPacketChat.iHeader = PKTHDR_ChatMessage;
			sPacketChat.iChatColor = CHATCOLOR_Normal;
			sPacketChat.lID = pcUser->iID;
			STRINGCOPY(sPacketChat.szChatBoxMessage, pcUser->szChat);

			sPacketChat.iLength = sizeof(Packet) + sizeof(sPacketChat.iChatColor) + sizeof(sPacketChat.lID) + STRLEN(sPacketChat.szChatBoxMessage) + 1;

			pcUser->szChat[0] = 0;
		}

		//Send Chat Message and Receive Unit Status
		for (UINT i = 0, j = uUsersInGame; i < j; i++)
		{
			User * pcOtherUser = pcaUserInGame[i];

			if (pcOtherUser != pcUser)
			{
				if (bChat)
				{
					if (pcUser->sPosition.WithinPTDistance(&pcOtherUser->sPosition, USER_TALKRANGE))
						SENDPACKET(pcOtherUser, &sPacketChat);
				}

				if (bStatus)
				{
					if ((pcOtherUser->uUnitStatusNum > 0) && (pcUser->CanSee(pcOtherUser)))
					{
						UINT uOtherIndex = pcOtherUser->uIndex;

						UINT uMyUnitStatusNumOfOther = pcUser->uaUpdateCounter1[uOtherIndex];
						UINT uUnitStatusNumber = pcOtherUser->uUnitStatusNum;

						int iDistanceA, iDistanceB, iDistanceC;
						pcUser->sPosition.GetPTDistanceXZ(&pcOtherUser->sPosition, iDistanceA, iDistanceB, iDistanceC);

						if ((iDistanceA < USER_SIGHTRANGE_FAR) && (iDistanceB < MISC_DISTANCE) && (iDistanceC < MISC_DISTANCE))
						{
							ID lOtherID = pcOtherUser->GetID();
							int iOtherMovingIndex = pcOtherUser->iMovingIndex;

							UINT uUnitStatusIndex = 0;

							if (pcUser->uaUpdateCounter2[uOtherIndex] == lOtherID)
							{
								if ((iOtherMovingIndex == 0) || (uMyUnitStatusNumOfOther < uUnitStatusNumber))
								{
									if ((uMyUnitStatusNumOfOther == 0) || (uMyUnitStatusNumOfOther >= uUnitStatusNumber))
									{
										pcUser->uaUpdateCounter1[uOtherIndex] = uUnitStatusNumber;
										continue;
									}
									else
									{
										UINT uTemp = uUnitStatusNumber - uMyUnitStatusNumOfOther;

										if (uTemp > 3)
											uMyUnitStatusNumOfOther = uUnitStatusNumber - 3;

										uUnitStatusIndex = uMyUnitStatusNumOfOther % 4;

										uMyUnitStatusNumOfOther++;
										pcUser->uaUpdateCounter1[uOtherIndex] = uMyUnitStatusNumOfOther;
									}
								}
								else
								{
									if (pcUser->uaUpdateCounter4[uOtherIndex] == 0)
									{
										if (pcOtherUser->uPriority > 0)
										{
											UINT uCounter3 = (pcUser->uaUpdateCounter3[uOtherIndex]++);

											BOOL bContinue;
											switch (pcOtherUser->uPriority)
											{
											case 1:
												if (uCounter3 > 2)
												{
													bContinue = FALSE;
													break;
												}

												bContinue = TRUE;
												break;
											case 2:
												if (uCounter3 > 4)
												{
													bContinue = FALSE;
													break;
												}

												bContinue = TRUE;
												break;
											case 3:
												if (uCounter3 > 8)
												{
													bContinue = FALSE;
													break;
												}

												bContinue = TRUE;
												break;
											default:
												if (uCounter3 > 12)
												{
													bContinue = FALSE;
													break;
												}

												bContinue = TRUE;
												break;
											}

											if (bContinue)
												continue;
										}
									}

									uUnitStatusIndex = 4;
								}

								pcUser->uaUpdateCounter3[uOtherIndex] = 0;
							}
							else
							{
								pcUser->uaUpdateCounter1[uOtherIndex] = uUnitStatusNumber;
								pcUser->uaUpdateCounter2[uOtherIndex] = lOtherID;
								pcUser->uaUpdateCounter3[uOtherIndex] = 0;
								pcUser->uaUpdateCounter4[uOtherIndex] = 4;

								uUnitStatusIndex = 4;
							}

							if ((iDistanceA < USER_UPDATERANGE_FAR) || (uUnitStatusIndex == 4))
							{
								if (pcUser->uaUpdateCounter4[uOtherIndex] > 0)
									pcUser->uaUpdateCounter4[uOtherIndex]--;

								if (pcOtherUser->dwaTimeUnitStatus[uUnitStatusIndex] != 0)
									SendUnitStatus(pcUser, (Packet *)(pcOtherUser->baUnitStatusNew[uUnitStatusIndex]));

								SendSkillStatus(pcUser, &pcOtherUser->sSkillStatus);

								//CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Unit Status [%s] [%d]", pcOtherUserData->sCharacterData.szName, uUnitStatusIndex );
							}
							else
							{
								PacketUnitStatusMove sMovePacket;
								sMovePacket.iLength = sizeof(sMovePacket);
								sMovePacket.iHeader = PKTHDR_UnitStatusMove;
								sMovePacket.lID = pcOtherUser->iID;
								sMovePacket.sPosition = pcOtherUser->sPosition;
								sMovePacket.sAngleX = 0;
								sMovePacket.sAngleY = pcOtherUser->sAngle.iY;
								sMovePacket.sAngleZ = 0;
								sMovePacket.sAnimationType = ANIMATIONTYPE_None;
								sMovePacket.iFrame = 0;
								sMovePacket.dwHashCharacterName = 0;

								SendUnitStatus(pcUser, &sMovePacket);

								//if( pcUserData->bShowDebugInfo )
								//	ChatServer::SendChatEx( pcUser, CHATCOLOR_Error, "> Move Status [%s]", pcOtherUserData->sCharacterData.szName );
							}
						}
						else
						{
							//Reset so it will refresh again next time even if same User is still logged in
							pcUser->uaUpdateCounter2[uOtherIndex] = 0;
						}
					}
				}
			}
		}

		ClearUnitStatus(pcUser);
	}
}
void CServerUser::LoopUnits(User * pcUser)
{
	int uUnitsInGame = SERVERUNIT->uUnitsInGame;

	Unit **pcaUnitInGame = SERVERUNIT->pcaUnitInGame;

	//Receive Unit Status
	for (int i = 0, j = uUnitsInGame; i < j; i++)
	{
		Unit *pcUnit = pcaUnitInGame[i];

		if (pcUnit->uUnitInfoSize != 0)
		{
			if (pcUser->CanSee(pcUnit))
			{
				int iDistanceA, iDistanceB, iDistanceC;
				pcUser->sPosition.GetPTDistanceXZ(&pcUnit->sPosition, iDistanceA, iDistanceB, iDistanceC);

				if ((iDistanceA < USER_SIGHTRANGE_FAR) && (iDistanceB < MISC_DISTANCE) && (iDistanceC < MISC_DISTANCE))
				{
					BOOL bForceUnitStatus = FALSE;

					if (pcUnit->iSpecialType != 0)
					{
						switch (pcUnit->sCharacterData.iMonsterEffectID)
						{
						case MONSTEREFFECTID_CASTLE_DOOR:
						case MONSTEREFFECTID_CASTLE_TOWER_B:
							bForceUnitStatus = TRUE;
							break;
						}
					}
					if ((bForceUnitStatus) || (iDistanceA < USER_UPDATERANGE_FAR))
					{
						if (pcUser->uaUpdateCounter5[pcUnit->uIndex] != pcUnit->uLastUpdate)
						{
							SendUnitStatusM(pcUser, (Packet *)(pcUnit->baUnitBufferNew));

							pcUnit->iAliveCounter = 256;

							pcUser->uaUpdateCounter5[pcUnit->uIndex] = pcUnit->uLastUpdate;
						}
					}
					else
					{
						if (pcUnit->GetAnimation() != ANIMATIONTYPE_Die)
						{
							PacketUnitStatusMove sMovePacket;
							sMovePacket.iLength = sizeof(sMovePacket);
							sMovePacket.iHeader = PKTHDR_UnitStatusMove;
							sMovePacket.lID = pcUnit->iID;
							sMovePacket.sPosition = pcUnit->sPosition;
							sMovePacket.sAngleX = pcUnit->sAngle.iX;
							sMovePacket.sAngleY = pcUnit->sAngle.iY;
							sMovePacket.sAngleZ = pcUnit->sAngle.iZ;
							sMovePacket.sAnimationType = pcUnit->GetAnimation();
							sMovePacket.iFrame = pcUnit->iFrame;
							sMovePacket.dwHashCharacterName = pcUnit->sUnitInfo.dwHashCharacterName;

							SendUnitStatusM(pcUser, &sMovePacket);

							pcUnit->iAliveCounter = 256;

							//if( pcUserData->bShowDebugInfo )
							//	ChatServer::SendChatEx( pcUser, CHATCOLOR_Error, "> Move Status [%s]", pcUnitData->sCharacterData.szName );
						}
					}
				}
			}
		}
	}

	//Game Status Babel Storm Map
	EMapID eMapID = SERVERMAP->eBabelMapID;

	if ((pcUser->GetMapID() == eMapID) && (SERVERMAP->dwBabelEndTime > TICKCOUNT))
	{
		PacketGameStatusBabelStormMap sPacket;
		sPacket.iLength = sizeof(sPacket);
		sPacket.iHeader = PKTHDR_GameStatus;
		sPacket.iStatusID = 0x200;
		sPacket.lID = pcUser->GetID();
		sPacket.eBabelStormMapID = eMapID;
		SendUnitStatusM(pcUser, &sPacket, FALSE);
	}

	//Game Status Bless Castle
	if (pcUser->GetMapID() == MAPID_BlessCastle)
	{
		PacketGameStatusBlessCastle sPacket;
		BlessCastleStatusData * pcBC = SERVERBLESSCASTLE->GetBlessCastleStatusData();

		sPacket.iLength = sizeof(sPacket);
		sPacket.iHeader = PKTHDR_GameStatus;
		sPacket.iStatusID = 0x210;
		sPacket.lID = pcUser->GetID();
		sPacket.iCastMode = pcBC->iCastleMode;
		sPacket.iDefenseLevel = pcBC->iDefenseLevel;
		sPacket.iClanID = pcBC->iClanID;
		sPacket.baSoldierCount[0] = pcBC->baSoldierCount[0];
		sPacket.baSoldierCount[1] = pcBC->baSoldierCount[1];
		sPacket.baSoldierCount[2] = pcBC->baSoldierCount[2];
		sPacket.baSoldierCount[3] = pcBC->baSoldierCount[3];
		sPacket.saTimeSec[0] = pcBC->saTimeSec[0];
		sPacket.saTimeSec[1] = pcBC->saTimeSec[1];
		sPacket.sConRate = pcUser->sBlessCastle_Damage[0];
		sPacket.sBattlePoints = pcUser->sBlessCastle_Damage[1];

		SendUnitStatusM(pcUser, &sPacket, FALSE);
	}

	if (SERVERMAP->IsPVPMap(pcUser->iMapID))
	{
		PacketGameStatusPvPMap sPacket;
		sPacket.iLength = sizeof(sPacket);
		sPacket.iHeader = PKTHDR_GameStatus;
		sPacket.iStatusID = 0x220;
		sPacket.lID = pcUser->GetID();
		sPacket.iPvPMapID = pcUser->iMapID;
		SendUnitStatusM(pcUser, &sPacket, FALSE);
	}

	ClearUnitStatusM(pcUser);
}

void CServerUser::SendUnitStatus(User * pcUser, Packet * psPacket, BOOL bIncrementAmount)
{
	if (psPacket->iLength > 0x1FF0)
		return;

	psPacket->iEncKeyIndex = 0;
	psPacket->iEncrypted = 0;

	UINT uFreeSpace = 0x1FF0 - pcUser->uBufferPosition;

	if (psPacket->iLength > uFreeSpace)
		ClearUnitStatus(pcUser);

	BYTE * buf = ((BYTE*)pcUser->sUnitStatusContainer.baBuffer) + pcUser->uBufferPosition;

	CopyMemory(buf, psPacket, psPacket->iLength);

	pcUser->uBufferPosition += psPacket->iLength;

	if (bIncrementAmount)
		pcUser->sUnitStatusContainer.iAmount++;
}
void CServerUser::SendUnitStatusM(User * pcUser, Packet * psPacket, BOOL bIncrementAmount)
{
	if (psPacket->iLength > 0x1FF0)
		return;

	psPacket->iEncKeyIndex = 0;
	psPacket->iEncrypted = 0;

	UINT uFreeSpace = 0x1FF0 - pcUser->uBufferPositionM;

	if (psPacket->iLength > uFreeSpace)
		ClearUnitStatusM(pcUser);

	BYTE * buf = ((BYTE*)pcUser->sUnitStatusContainerM.baBuffer) + pcUser->uBufferPositionM;

	CopyMemory(buf, psPacket, psPacket->iLength);

	pcUser->uBufferPositionM += psPacket->iLength;
	if (bIncrementAmount)
		pcUser->sUnitStatusContainerM.iAmount++;
}
void CServerUser::SendSkillStatus(User * pcUser, PacketSkillStatus * psPacket)
{
	if ((pcUser->uBufferSkillPosition + psPacket->iLength) >= SKILLCONTAINER_LENGTH)
		ClearSkillStatus(pcUser);

	CopyMemory(pcUser->sSkillContainer.baBuffer + pcUser->uBufferSkillPosition, psPacket, sizeof(PacketSkillStatus));

	pcUser->uBufferSkillPosition += psPacket->iLength;

	pcUser->sSkillContainer.iAmount++;
}

void CServerUser::ClearUnitStatus(User * pcUser)
{
	if ((pcUser->sUnitStatusContainer.iAmount > 0) || (pcUser->uBufferPosition > 0))
	{
		pcUser->sUnitStatusContainer.iLength = sizeof(Packet) + sizeof(int) + sizeof(int) + pcUser->uBufferPosition;

		SENDPACKET(pcUser, &pcUser->sUnitStatusContainer);

		pcUser->uBufferPosition = 0;
		pcUser->sUnitStatusContainer.iAmount = 0;
	}
}
void CServerUser::ClearUnitStatusM(User * pcUser)
{
	if ((pcUser->sUnitStatusContainerM.iAmount > 0) || (pcUser->uBufferPositionM > 0))
	{
		pcUser->sUnitStatusContainerM.iLength = sizeof(Packet) + sizeof(int) + sizeof(int) + pcUser->uBufferPositionM;

		SENDPACKET(pcUser, &pcUser->sUnitStatusContainerM);

		pcUser->uBufferPositionM = 0;
		pcUser->sUnitStatusContainerM.iAmount = 0;
	}
}
void CServerUser::ClearSkillStatus(User * pcUser)
{
	if ((pcUser->sSkillContainer.iAmount > 0) || (pcUser->uBufferSkillPosition > 0))
	{
		pcUser->sSkillContainer.iLength = sizeof(Packet) + sizeof(int) + pcUser->uBufferSkillPosition;
		pcUser->sSkillContainer.iHeader = PKTHDR_SkillStatusContainer;

		SENDPACKET(pcUser, &pcUser->sSkillContainer, TRUE);

		ZeroMemory(&pcUser->sSkillContainer, sizeof(PacketSkillStatusContainer));

		pcUser->sSkillContainer.iAmount = 0;
		pcUser->uBufferSkillPosition = 0;
	}
}

void CServerUser::HandlePacket(User *pcUser, PacketPlayData * psPacket)
{
	if ((int)psPacket->sMapID != pcUser->iMapID)
	{
		if (SERVERCHARACTER->CharacterInCityStage(pcUser))
			ResetSkills(pcUser);
	}

	pcUser->iMapID = (EMapID)psPacket->sMapID;
	pcUser->sCharacterData.sMP = psPacket->sMP;
	pcUser->sCharacterData.sSP = psPacket->sSP;
	pcUser->sCharacterData.iAttackSpeed = psPacket->saSpeed[0];
	pcUser->sCharacterData.iMovementSpeed = psPacket->saSpeed[1];
	pcUser->sAngle.iY = psPacket->sAngleY;
	pcUser->sCharacterData.sSize = psPacket->sSize;
	pcUser->sCharacterData.iLevel = psPacket->iLevel;

	//Buffer
	if (psPacket->iPlayBuffCount < 32)
	{
		int iIndex = 0;

		if (psPacket->iPlayBuffCount <= 1)
		{
			if (pcUser->iMovingIndex == 0)
				pcUser->iMovingIndex = 1;

			iIndex = 4;
		}
		else
		{
			iIndex = pcUser->uUnitStatusNum % 4;
			pcUser->iMovingIndex = 0;
			pcUser->uUnitStatusNum++;
		}

		CopyMemory(pcUser->baUnitStatusNew[iIndex], psPacket, psPacket->iLength);
		pcUser->dwaTimeUnitStatus[iIndex] = psPacket->iLength;
	}


	if (psPacket->iPlayBuffCount > 0)
	{
		auto sPlayBuffData = (PlayBufferData *)(((char *)psPacket) + sizeof(PacketPlayData));
		sPlayBuffData += psPacket->iPlayBuffCount - 1;

		int iX = sPlayBuffData->sPlayBuff.iX;
		int iY = sPlayBuffData->sPlayBuff.iY;
		int iZ = sPlayBuffData->sPlayBuff.iZ;

		pcUser->sPosition = Point3D(iX, iY, iZ);

		CheckMapLevel(pcUser);
	}

	if (psPacket->bUpdateInfo[0] != pcUser->sCharacterData.bUpdateInfo[0])
	{
		if (pcUser->UpdateInfo_WaitCounter > 6 && (pcUser->UpdateInfo_WaitCounter & 0x7) == 0)
		{
			PacketSimple sPacket;

			sPacket.iLength = sizeof(PacketSimple);
			sPacket.iHeader = PKTHDR_GetUnitInfoData;
			sPacket.iUnk = pcUser->sCharacterData.bUpdateInfo[0];
			sPacket.iUnk2 = pcUser->iID;
			sPacket.iUnk3 = psPacket->bUpdateInfo[0];

			SENDPACKET(pcUser,&sPacket,TRUE);

			pcUser->UpdateInfo_WarnigCounter++;
		}
		pcUser->UpdateInfo_WaitCounter++;
	}
	else
		pcUser->UpdateInfo_WaitCounter = 0;

	if (pcUser->UpdateInfo_WarnigCounter > 50)
	{
		PacketLogCheat s;
		s.iCheatID = CHEATLOGID_TooManyUpdatedCharInfo;
		s.iLParam = pcUser->sCharacterData.bUpdateInfo[0];
		s.iSParam = psPacket->bUpdateInfo[0];
		s.iEParam = pcUser->UpdateInfo_WarnigCounter;

		SERVERLOG->LogCheat(pcUser, &s);
	}

	pcUser->dwTimeLastStatusUpdate = SERVER_GAMETIME;
}
//48470020
void CServerUser::OnUserSyncData(User *pcUser, PacketPlayInfo *psPacket)
{
	memcpy(&pcUser->sCharacterData, &psPacket->sCharacterData, sizeof(CharacterData));

	pcUser->dwHashCharacterName = GetCodebyName(pcUser->sCharacterData.szName);

	pcUser->sPosition = psPacket->sPosition;

	if (pcUser->iID == NULL)
		pcUser->iID = pcUser->sCharacterData.iID;

	if (pcUser->iID == NULL)
		SERVERNET->DisconnectUser(pcUser->pcSocketData);
	else
	{
		pcUser->iClanID = GetClanCodeByID(pcUser->sCharacterData.iClanID);

		PacketSimple sPacket;

		sPacket.iLength = sizeof(PacketSimple);
		sPacket.iHeader = PKTHDR_Connected;
		sPacket.iUnk = TICKCOUNT;
		sPacket.iUnk2 = pcUser->iID;

		SENDPACKET(pcUser, &sPacket);

		char *pszCharacterName = SERVERCHARACTER->GetCharacterName(pcUser);

		User *u = GetUser(pszCharacterName);

		if (u && u->pcSocketData && u->TransInfoFlag && u->iGameLevel == GAMELEVEL_None)
			SERVERNET->DisconnectUser(u->pcSocketData);
		else
		{
			pcUser->TransInfoFlag = TRUE;
			pcUser->dwLastExpMoneyCheckTime = SERVER_GAMETIME;
			pcUser->UpdateInfo_WarnigCounter++;

			SERVERNET->SendSyncChar(pcUser);
			SERVERCHARACTER->OnCharacterSyncData(pcUser);
		}
	}
}

void CServerUser::ResetSkills(User *pcUser)
{

}

void CServerUser::SettingsDataSet(User * pcUser, PacketSettingsData * psPacket)
{
	if (!GAME_SERVER)
	{
		if (pcUser->sSettingsData.bNoWhisper != psPacket->bNoWhisper)
			SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Error, "> Whisper %s!", pcUser->sSettingsData.bNoWhisper ? "enabled" : "disabled");

		if (pcUser->sSettingsData.bNoTradeChat != psPacket->bNoTradeChat)
			SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Error, "> Trade Chat %s!", pcUser->sSettingsData.bNoTradeChat ? "enabled" : "disabled");

		if (pcUser->sSettingsData.bNoPartyRequest != psPacket->bNoPartyRequest)
			SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Error, "> Party Requests %s!", pcUser->sSettingsData.bNoPartyRequest ? "enabled" : "disabled");

		if (pcUser->sSettingsData.bNoTradeRequest != psPacket->bNoTradeRequest)
			SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Error, "> Trade Requests %s!", pcUser->sSettingsData.bNoTradeRequest ? "enabled" : "disabled");
	}

	CopyMemory(&pcUser->sSettingsData, psPacket, sizeof(PacketSettingsData));
}

void CServerUser::DisconnectUser(User * pcUser)
{
	for (int i = 0; i < PLAYERS_MAX; i++)
	{
		User * u = USERSDATA + i;

		if (u != pcUser && (u->iID == pcUser->GetID() || STRINGCOMPAREI(SERVERCHARACTER->GetCharacterName(u), SERVERCHARACTER->GetCharacterName(pcUser))))
		{
			if (u->pcSocketData)
				WNDPROC_SOCKETCLOSE(SERVERSOCKET->GetHWND(), u->pcSocketData);
			else
			{
				ZeroMemory(u, sizeof(this));
			}
		}
	}
}
DWORD CServerUser::AllowPacket(User * pcUser)
{
#define MAX_PACKETFLOW 175
#define TIM_PACKETFLOW 1750

	DWORD dwTickCount = TICKCOUNT;

	if (pcUser->bNetServer == FALSE)
	{
		//Flood protection
		if (pcUser->iPacketCounter > MAX_PACKETFLOW)
		{
			PacketLogCheat s;
			s.iLParam = pcUser->iPacketCounter;
			s.iSParam = MAX_PACKETFLOW;
			s.iEParam = TIM_PACKETFLOW;
			s.iCheatID = CHEATLOGID_TooManyPackets;
			SERVERLOG->LogCheat(pcUser, &s);
			return 0;
		}

		if ((dwTickCount - pcUser->dwTickPacketCounter) > TIM_PACKETFLOW)
		{
			pcUser->iPacketCounter = 0;
			pcUser->dwTickPacketCounter = dwTickCount;
		}
		else
			pcUser->iPacketCounter++;
	}

	pcUser->dwTimeLastPacket = dwTickCount;

	return dwTickCount;
}
void CServerUser::SaveDropItem(User *pcUser)
{
	if (pcUser->psCharacterFile)
	{
		DropItemData * psDropItem = pcUser->ThrowItemInfo;
		CharacterFile *psCharacterFile = pcUser->psCharacterFile;

		int iCount = pcUser->ThrowItemCount;

		if (iCount > THROW_ITEM_INFO_MAX)
			iCount = THROW_ITEM_INFO_MAX;

		CopyMemory(&psCharacterFile->ThrowItemInfo, psDropItem, sizeof(DropItemData) * iCount);

		psCharacterFile->ThrowItemCount = iCount;

		if (pcUser->UnsaveMoney >= 0 && psCharacterFile->sCharInfo.iGold > pcUser->UnsaveMoney)
			psCharacterFile->GameSaveInfo.iLastGold = pcUser->UnsaveMoney + 1;

		pcUser->ThrowItemCount = 0;
		pcUser->UnsaveMoney = -1;
	}
}
void CServerUser::SaveDropItemOver(User * pcUser, ItemID sItemID, int iChk1, int iChk2)
{
	if (pcUser->ThrowItemCount > 0)
	{
		int iCount = 0;
		DWORD iLowID = pcUser->ThrowItemInfo[iCount].dwCode & 0x0000FFFF;

		for (int i = 1; i < pcUser->ThrowItemCount; i++)
		{
			DWORD iID = pcUser->ThrowItemInfo[i].dwCode & 0x0000FFFF;
			if (iID < iLowID)
			{
				iLowID = iID;
				iCount = i;
			}
		}

		pcUser->ThrowItemInfo[iCount].dwCode = sItemID.ToInt();
		pcUser->ThrowItemInfo[iCount].dwKey = iChk1;
		pcUser->ThrowItemInfo[iCount].dwSum = iChk2;
	}
}
void CServerUser::SaveDropItem(User * pcUser, ItemID sItemID, int iChk1, int iChk2)
{
	if (sItemID.ToItemBase() != ITEMBASE_Potion)
	{
		for (int i = 0; i < pcUser->ThrowItemCount; i++)
		{
			if (pcUser->ThrowItemInfo[i].dwCode == sItemID.ToInt() &&
				pcUser->ThrowItemInfo[i].dwKey == iChk1 &&
				pcUser->ThrowItemInfo[i].dwSum == iChk2)
				return;
		}

		if (pcUser->ThrowItemCount >= THROW_ITEM_INFO_MAX - 1)
		{
			SaveDropItemOver(pcUser, sItemID, iChk1, iChk2);
		}
		else
		{
			pcUser->ThrowItemInfo[pcUser->ThrowItemCount].dwCode = sItemID.ToInt();
			pcUser->ThrowItemInfo[pcUser->ThrowItemCount].dwKey = iChk1;
			pcUser->ThrowItemInfo[pcUser->ThrowItemCount].dwSum = iChk2;

			if (pcUser->ThrowItemCount < THROW_ITEM_INFO_MAX - 1)
			{
				pcUser->ThrowItemCount++;

				if (pcUser->ThrowItemCount == THROW_ITEM_INFO_MAX - 32 ||
					pcUser->ThrowItemCount > THROW_ITEM_INFO_MAX - 48)
					SENDPACKETBLANK(pcUser, PKTHDR_Save);
			}
		}
	}
}
BOOL CServerUser::InventoryServerCheck(User *pcUser, int iUnused)
{
	//Check
	if (pcUser->psCharacterFile == NULL)
		return FALSE;

	if (pcUser->iGameLevel >= GAMELEVEL_Three)
		return FALSE;

	PacketCharacterRecordData * psCharacter = (PacketCharacterRecordData*)pcUser->psCharacterFile;

	RecordItem sRecordItem;

	DropItemData sDropData[64];

	ZeroMemory(sDropData, sizeof(DropItemData) * 64);

	BYTE * pbaItems = psCharacter->baData;

	int iBufferWheel = 0;

	int iCount = 0;

	int iDropItemCount = 0;

	for (int i = 0; i < psCharacter->iItemCount; i++)
	{
		//Inventory Limit...
		if (i >= 200)
			break;

		SERVERITEM->DecodeItemsData((BYTE *)pbaItems, (BYTE *)&sRecordItem, 44);

		if (sRecordItem.sItem.sItemID.ToInt() && sRecordItem.sItem.iChk1 && sRecordItem.sItem.iChk2)
		{
			iCount = 0;

			if (sRecordItem.sItem.sItemID.ToItemBase() == ITEMBASE_Potion)
			{
				if (pcUser->TradePotionInfoCount > 0)
				{
					if (SERVERITEM->GetDropPotion(pcUser, sRecordItem.sItem.sItemID.ToInt()))
						iCount = 1;
				}
				else
					iCount = (-1);
			}
			else
			{
				//Inventory 1 and 2, backup
				for (int j = 0; j < 300; j++)
				{
					DropItemData * ps = pcUser->InvenItemInfo + j;

					if (ps->dwCode && (ps->dwKey == sRecordItem.sItem.iChk1) && (ps->dwSum == sRecordItem.sItem.iChk2))
					{
						ps->dwCode = ITEMID_None;

						iCount++;
					}
				}

				//Warehouse
				for (int j = 0; j < 420; j++)
				{
					DropItemData * ps = pcUser->sWarehouseItems + j;

					if (ps->dwCode && (ps->dwKey == sRecordItem.sItem.iChk1) && (ps->dwSum == sRecordItem.sItem.iChk2))
					{
						PacketLogCheat s;
						s.iCheatID = CHEATLOGID_ItemErrorInventoryRecord;
						s.iWxParam = 1;
						s.iLxParam = (int)"*RECORD ITEM WAREHOUSE";
						s.iLParam = sRecordItem.sItem.sItemID.ToInt();
						s.iSParam = sRecordItem.sItem.iChk1;
						s.iEParam = sRecordItem.sItem.iChk2;

						SERVERLOG->LogCheat(pcUser, &s);
						iCount++;
					}
				}
			}

			//Not Found...
			if (iCount == 0)
			{

				int iLoop = 0;

				for (iLoop = 0; iLoop < psCharacter->iDropItemCount; iLoop++)
				{
					DropItemData * ps = psCharacter->sDropItemData + iLoop;

					if ((ps->dwCode == sRecordItem.sItem.sItemID.ToInt()) && (ps->dwKey == sRecordItem.sItem.iChk1) && (ps->dwSum == sRecordItem.sItem.iChk2))
						break;
				}


				if (iDropItemCount < 64)
				{
					int k = 0;

					for (k = 0; k < iDropItemCount; k++)
					{
						DropItemData * ps = sDropData + k;

						if ((ps->dwCode == sRecordItem.sItem.sItemID.ToInt()) && (ps->dwKey == sRecordItem.sItem.iChk1) && (ps->dwSum == sRecordItem.sItem.iChk2))
							break;
					}

					if (k >= iDropItemCount)
					{
						sDropData[iDropItemCount].dwCode = sRecordItem.sItem.sItemID.ToInt();
						sDropData[iDropItemCount].dwKey = sRecordItem.sItem.iChk1;
						sDropData[iDropItemCount].dwSum = sRecordItem.sItem.iChk2;
						iDropItemCount++;
					}
				}

				if (iLoop >= psCharacter->iDropItemCount)
				{
					PacketLogCheat s;
					s.iCheatID = CHEATLOGID_ItemErrorInventoryRecord;
					s.iWxParam = 1;
					s.iLxParam = (int)"*RECORD ITEM";
					s.iLParam = sRecordItem.sItem.sItemID.ToInt();
					s.iSParam = sRecordItem.sItem.iChk1;
					s.iEParam = sRecordItem.sItem.iChk2;

					SERVERLOG->LogCheat(pcUser, &s);
				}
			}
			else
			{
				if (iCount > 0)
				{
					for (int j = 0; j < psCharacter->iDropItemCount; j++)
					{
						DropItemData * ps = psCharacter->sDropItemData + j;

						if ((ps->dwCode == sRecordItem.sItem.sItemID.ToInt()) && (ps->dwKey == sRecordItem.sItem.iChk1) && (ps->dwSum == sRecordItem.sItem.iChk2))
						{
							if (iDropItemCount < 64)
							{
								sDropData[iDropItemCount].dwCode = sRecordItem.sItem.sItemID.ToInt();
								sDropData[iDropItemCount].dwKey = sRecordItem.sItem.iChk1;
								sDropData[iDropItemCount].dwSum = sRecordItem.sItem.iChk2;
								iDropItemCount++;
							}
							break;
						}
					}
				}
			}

			if (iCount > 1)
			{
				PacketLogCheat s;
				s.iCheatID = CHEATLOGID_ItemErrorInventoryRecord;
				s.iWxParam = iCount;
				s.iLxParam = (int)"*RECORD COPIED ITEM";
				s.iLParam = sRecordItem.sItem.sItemID.ToInt();
				s.iSParam = sRecordItem.sItem.iChk1;
				s.iEParam = sRecordItem.sItem.iChk2;

				SERVERLOG->LogCheat(pcUser, &s);
			}
		}

		int iSize = ((int*)pbaItems)[0];

		iBufferWheel += iSize;

		pbaItems += iSize;

		if (iBufferWheel >= (sizeof(RecordItem) * 200))
			break;
	}

	if (iDropItemCount > 0)
	{
		CopyMemory(psCharacter->sDropItemData, sDropData, sizeof(DropItemData) * iDropItemCount);
		psCharacter->iDropItemCount = iDropItemCount;
	}

	if (psCharacter->sCharacterData.iGold > pcUser->iInventoryGold)
	{
		PacketLogCheat s;
		s.iCheatID = CHEATLOGID_ServerMoneyErrorInventory;
		s.iLParam = 1;
		s.iSParam = pcUser->iInventoryGold;
		s.iEParam = psCharacter->sCharacterData.iGold;
		SERVERLOG->LogCheat(pcUser, &s);

		psCharacter->sCharacterData.iGold = pcUser->iInventoryGold;

		pcUser->UnsaveMoney = (-1);

		if (psCharacter->sCharacterData.iGold < 0)
			psCharacter->sCharacterData.iGold = 0;
	}

	int iGold = psCharacter->sCharacterSaveData.iLastGold;

	if (iGold && (iGold - 1) > pcUser->iInventoryGold)
	{
		PacketLogCheat s;
		s.iCheatID = CHEATLOGID_ServerMoneyErrorInventory;
		s.iLParam = 3;
		s.iSParam = pcUser->iInventoryGold;
		s.iEParam = psCharacter->sCharacterSaveData.iLastGold - 1;
		SERVERLOG->LogCheat(pcUser, &s);

		psCharacter->sCharacterSaveData.iLastGold = pcUser->iInventoryGold + 1;

		if (psCharacter->sCharacterSaveData.iLastGold < 0)
			psCharacter->sCharacterSaveData.iLastGold = 0;
	}

	return TRUE;
}
void CServerUser::CheckMapLevel(User *pcUser)
{
	if (pcUser->iGameLevel != GAMELEVEL_None)
	{
		EMapID iMapID = pcUser->iMapID;
	}
}

User * CServerUser::GetUser(int iID)
{
	if (iID != 0)
	{
		for (int i = 0; i < PLAYERS_MAX; i++)
		{
			User * u = USERSDATA + i;

			if (u->pcSocketData && u->iID == iID)
			{
				return u;
			}
		}
	}

	return nullptr;
}

User * CServerUser::GetUser(const char *pszCharacterName)
{
	for (int i = 0; i < PLAYERS_MAX; i++)
	{
		User *u = USERSDATA + i;

		if (u->pcSocketData)
		{
			if (GAME_SERVER)
			{
				if (STRINGCOMPAREI(u->sCharacterData.szName, pszCharacterName))
					return u;
			}
			else
			{
				if (STRINGCOMPAREI(u->szCharacterName, pszCharacterName))
					return u;
			}
		}
	}

	return nullptr;
}
User *CServerUser::GetUserByAccount(const char * pszAccountName)
{
	for (int i = 0; i < PLAYERS_MAX; i++)
	{
		User * pcUser = USERSDATA + i;

		if (pcUser && pcUser->IsConnected() && pcUser->szAccountName[0])
		{
			if (STRINGCOMPAREI(pcUser->szAccountName, pszAccountName))
				return pcUser;
		}
	}

	return nullptr;
}
void CServerUser::OnKilled(User * pcUser, PacketDeadCharacter * psPacket)
{
	ResetSkills(pcUser);

	User * pcKiller = GetUser(psPacket->dwObjectID);

	if (pcKiller)
	{
		if (LOGIN_SERVER)
		{
			SERVERPVP->OnKilled(pcKiller, pcUser);
		}
		else if (GAME_SERVER)
			SERVERITEM->ProcessIntegrity(pcUser, INTEGRITYUPDATE_KilledUser);

		return;
	}
	else if (GAME_SERVER)
	{
		SERVERITEM->ProcessIntegrity(pcUser, INTEGRITYUPDATE_KilledMonster);

		Unit * pcUnit = SERVERUNIT->GetUnit(psPacket->dwObjectID, pcUser->iMapID);

		if (pcUnit)
		{
			if (pcUnit->sCharacterData.iMonsterEffectID == MONSTEREFFECTID_DEATHKNIGHT)
			{
				//send valento Effect
				SERVERUNIT->ProcessPacketEffectValento(pcUser, pcUnit->iID, pcUser->iID);

				if (pcUnit->iHPBlocks)
				{
					pcUnit->sHPBlocks.sMin += (pcUnit->sHPBlocks.sMax / 3);
					pcUnit->sHPBlocks.sMin = low(pcUnit->sHPBlocks.sMin, pcUnit->sHPBlocks.sMax);

					pcUnit->sCharacterData.sHP.sMin = pcUnit->sCharacterData.sHP.sMax;
				}
			}
		}
	}
}
void CServerUser::AddServerUserGold(User * pcUser, int iGold, EWhereAction eWhere)
{
	if (pcUser)
	{
		int iOldGold = pcUser->GetGold();

		pcUser->iInventoryGold += iGold;

		if ((iOldGold >= 0 && pcUser->GetGold() < 0) || iGold < 0 || iGold > SERVER_GOLD_MAX)
		{
			pcUser->iInventoryGold = iOldGold;

			PacketLogCheat sPacket;
			const char *pszLog = FormatString("AddGold[%s]", GetWhereToString(eWhere));

			sPacket.iCheatID = CHEATLOGID_ServerMoneyOverflow;
			sPacket.iWxParam = eWhere;
			sPacket.iLxParam = (int)pszLog;
			sPacket.iLParam = iOldGold;
			sPacket.iSParam = iGold;
			sPacket.iEParam = pcUser->iInventoryGold;

			SERVERLOG->LogCheat(pcUser, &sPacket);
		}
	}
}
void CServerUser::SubServerUserGold(User * pcUser, int iGold, EWhereAction eWhere)
{
	if (pcUser)
	{
		int iOldGold = pcUser->GetGold();

		pcUser->iInventoryGold -= iGold;

		if ((iOldGold >= 0 && pcUser->GetGold() < 0) || iGold < 0 || iGold > SERVER_GOLD_MAX)
		{
			PacketLogCheat sPacket;
			const char *pszLog = FormatString("SubtractGold[%s]", GetWhereToString(eWhere));

			sPacket.iCheatID = CHEATLOGID_ServerMoneyOverflow;
			sPacket.iWxParam = eWhere;
			sPacket.iLxParam = (int)pszLog;
			sPacket.iLParam = iOldGold;
			sPacket.iSParam = iGold;
			sPacket.iEParam = pcUser->iInventoryGold;

			SERVERLOG->LogCheat(pcUser, &sPacket);

			pcUser->iInventoryGold = iOldGold;
		}
	}
}
void CServerUser::SetServerUserGold(User * pcUser, int iGold, EWhereAction eWhere)
{
	if (pcUser)
	{
		int iOldGold = pcUser->GetGold();

		pcUser->iInventoryGold = iGold;

		if ((iOldGold >= 0 && pcUser->GetGold() < 0) || iGold < 0 || iGold > SERVER_GOLD_MAX)
		{
			PacketLogCheat sPacket;
			const char *pszLog = FormatString("SetGold[%s]", GetWhereToString(eWhere));

			sPacket.iCheatID = CHEATLOGID_ServerMoneyOverflow;
			sPacket.iWxParam = eWhere;
			sPacket.iLxParam = (int)pszLog;
			sPacket.iLParam = iOldGold;
			sPacket.iSParam = iGold;
			sPacket.iEParam = pcUser->iInventoryGold;

			SERVERLOG->LogCheat(pcUser, &sPacket);

			pcUser->iInventoryGold = iOldGold;
		}
	}
}
int CServerUser::SQLGetAccountID(const char * pszAccountName)
{
	int iRet = -1;

	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);
	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT ID FROM UserInfo WHERE AccountName=?"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_String, (char*)pszAccountName, STRLEN(pszAccountName));
			if (pcDB->Execute() && pcDB->Fetch())
			{
				pcDB->GetData(1, PARAMTYPE_Integer, &iRet, 32);
			}
		}
		pcDB->Close();
	}

	return iRet;
}
char * CServerUser::SQLGetAccountByCharacterName(const char * pszCharacterName)
{
	static char szAccountName[32] = { 0 };

	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);
	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT AccountName FROM CharacterInfo WHERE Name=?"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_String, (char *)pszCharacterName, 32);

			if (pcDB->Execute() && pcDB->Fetch())
			{
				pcDB->GetData(1, PARAMTYPE_String, szAccountName, 32);
			}
		}
		pcDB->Close();
	}

	return szAccountName;
}
void CServerUser::CancelForceOrb(User * pcUser)
{
	if (pcUser->iForceOrbTime)
	{
		pcUser->iForceOrbTime = 1;
		pcUser->dwForceOrb_Code = 0;
		pcUser->dwLastForceTime = SERVER_GAMETIME;
		SERVERNET->SendForceOrb(pcUser, TRUE);
		SERVERCHAT->SendChat(pcUser, EChatColor::CHATCOLOR_Error, "> Force Orb is gone!");
	}
}
BOOL CServerUser::GetClanLeaderAccount(int iClanID, char szLeaderAccount[32])
{
	BOOL bRet = FALSE;

	szLeaderAccount[0] = 0;

	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_ClanDB);
	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT AccountName FROM ClanList WHERE IconID=?"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_Integer, &iClanID);

			if (pcDB->Execute() && pcDB->Fetch())
			{
				pcDB->GetData(1, PARAMTYPE_String, szLeaderAccount, 32);

				bRet = TRUE;
			}
		}
		pcDB->Close();
	}

	return bRet;
}
BOOL CServerUser::GetClanName(int iClanID, char szName[32])
{
	BOOL bRet = FALSE;

	szName[0] = 0;

	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_ClanDB);
	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT ClanName FROM ClanList WHERE IconID=?"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_Integer, &iClanID);

			if (pcDB->Execute() && pcDB->Fetch())
			{
				pcDB->GetData(1, PARAMTYPE_String, szName, 32);

				bRet = TRUE;
			}
		}
		pcDB->Close();
	}

	return bRet;
}
BOOL CServerUser::IsClanID(User * pcUser, int iID)
{
	if (iID != -1)
	{
		DWORD dwCode = GetClanCodeByID(iID);

		if (pcUser->iClanID != 0 && pcUser->iClanID != dwCode)
		{
			PacketLogCheat s;
			s.iCheatID = CHEATLOGID_CompareClanCodeError;
			s.iLParam = pcUser->iClanID;
			s.iSParam = dwCode;

			SERVERLOG->LogCheat(pcUser, &s);

			return FALSE;
		}
	}

	return TRUE;
}
