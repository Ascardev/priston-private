#include "StdAfx.h"
#include "ServerMap.h"
#include "SrcServer/onserver.h"

#define ITEM_SET_DIST	24

static Point3D sPositionList[8] =
{
	{  0			 ,	0 , -ITEM_SET_DIST },
	{  ITEM_SET_DIST ,	0 , -ITEM_SET_DIST },
	{  ITEM_SET_DIST ,	0 ,  0			   },
	{  ITEM_SET_DIST ,	0 ,  ITEM_SET_DIST },
	{  0             ,	0 ,  ITEM_SET_DIST },
	{ -ITEM_SET_DIST ,	0 ,  ITEM_SET_DIST },
	{ -ITEM_SET_DIST ,	0 ,  0             },
	{ -ITEM_SET_DIST ,	0 , -ITEM_SET_DIST },
};

CServerMap::CServerMap()
{
	eBabelMapID = MAPID_Invalid;
	dwBabelEndTime = 0;
}
CServerMap::~CServerMap()
{
	
}
void CServerMap::Init()
{
	if (!GAME_SERVER)
		return;

	Load();

	m_iBossTime = (rand() % 45) + 1;
}
void CServerMap::Shutdown()
{
	for (auto &pcMap : m_vpMap)
	{
		pcMap->Free();

		DELET(pcMap);
	}

	m_vpMap.clear();
}
void CServerMap::Load()
{
	//Open SQL Connection
	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_GameDB);

	//Get Total Maps in SQL
	int iCountMaps = 0;
	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT COUNT(*) FROM MapList"))
		{
			if (pcDB->Execute() && pcDB->Fetch())
				pcDB->GetData(1, PARAMTYPE_Integer, &iCountMaps, 0);
		}
		pcDB->Close();
	}

	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT * FROM MapList ORDER BY ID ASC"))
		{
			if (pcDB->Execute() && pcDB->Fetch())
			{
				for (int i = 0; i < iCountMaps; i++)
				{
					//Get Parameters
					char szShortName[256] = { 0 };
					int iLevelMap = 0;
					char szFilePath[256] = { 0 };
					int iPVP = 0;

					pcDB->GetData(3, PARAMTYPE_String, szShortName, 256);
					pcDB->GetData(5, PARAMTYPE_Integer, &iLevelMap, 0);
					pcDB->GetData(6, PARAMTYPE_Integer, &iPVP, 0);
					pcDB->GetData(7, PARAMTYPE_String, szFilePath, 256);

					BaseMap * pcBaseMap = new BaseMap;

					ZeroMemory(pcBaseMap, sizeof(BaseMap));

					pcBaseMap->SetID((EMapID)i);
					pcBaseMap->SetLevelRequirement(MAPLEVEL(i));
					pcBaseMap->SetPVP(iPVP);
					pcBaseMap->SetFileName(szFilePath, szShortName);

					//Navisko Town?
					if (i == MAPID_NaviskoTown)
					{
						pcBaseMap->SetType(MAPTYPE_Desert);
						pcBaseMap->SetNightSpawn(TRUE);
						pcBaseMap->SetCenter(21928, -2335);
						pcBaseMap->AddSpawn(21928, -2335);
					}
					//Bless Castle?
					else if (i == MAPID_BlessCastle)
					{
						pcBaseMap->SetType(MAPTYPE_BlessCastle);
						pcBaseMap->SetCenter(35225, -23847);
						pcBaseMap->AddSpawn(33920, -23479);
					}

					Map * pcMap = new Map;

					pcMap->Load(pcBaseMap->szStageFilePath);
					pcMap->pcBaseMap = pcBaseMap;

					m_vpMap.push_back(pcMap);

					pcDB->Fetch();
				}
			}
		}
		pcDB->Close();
	}

	for (auto &pcMap : m_vpMap)
	{
		//monster position point;
		ReadUnitSpawnData(pcMap);

		//NPC position potion;
		ReadUnitNpcStand(pcMap);

		//Spawn NPCs
		for (UINT i = 0; i < MAX_NPCINMAP; i++)
		{
			PacketUnitInfo * psNPC = pcMap->saNPC + i;

			if ((psNPC->iHeader != 0))
				SpawnNPC(pcMap, psNPC);
		}

		//monst boss type
		ReadUnitEnemyStage(&pcMap->sSpawnSetting);
	}
}
Map * CServerMap::GetMap(EMapID iMapID)
{
	for (auto &pcMap : m_vpMap)
	{
		if (pcMap->pcBaseMap->iMapID == iMapID && pcMap->pcStage)
		{
			return pcMap;
		}
	}

	return nullptr;
}
BOOL CServerMap::IsValidMap(Map *pcMap)
{
	for (auto &pc : m_vpMap)
	{
		if (pc == pcMap)
			return TRUE;
	}

	return FALSE;
}
void CServerMap::Update()
{
	//Only GameServer
	if (!GAME_SERVER)
		return;

	//Update each Map

	for (auto &pcMap : m_vpMap)
	{
		UpdateMap(pcMap);
	}

	if (m_iDay != SERVERINFO->GetServerTime()->wDay)
	{
		m_iDay = SERVERINFO->GetServerTime()->wDay;
		//reset set Boss Time
		m_iBossTime = (rand() % 45) + 1;

		UpdateUsersBossTime();
	}

	//Update Time
	UpdateTime();
}
void CServerMap::UpdateMap(Map * pcMap)
{
	DWORD dwTickCount = TICKCOUNT;

	if (pcMap->pcStage != NULL)
	{
		pcMap->uCounter++;

		//Spawn a Monster
		if ((pcMap->uCounter % pcMap->sSpawnSetting.iSpawnIntervalMin) == 0)
		{
			if (pcMap->iNumAliveUnitData < pcMap->sSpawnSetting.iSpawnMaxMonsters)
			{
				if ((pcMap->pcBaseMap->bNightSpawn == FALSE) || (pcMap->bNight == TRUE))
				{
					if (pcMap->sSpawnSetting.iTotalMonsters > 0)
					{
						CharacterData sMonster;
						sMonster.szName[0] = 0;

						int iSpawnRate = 0;
						int iRandomSpawnRate = RandomI(0, pcMap->sSpawnSetting.iTotalMonsterSpawnRate);

						for (int i = 0; i < pcMap->sSpawnSetting.iTotalMonsters; i++)
						{
							iSpawnRate += pcMap->sSpawnSetting.saMonster[i].iSpawnRate;

							if (iSpawnRate > iRandomSpawnRate)
							{
								CopyMemory(&sMonster, pcMap->sSpawnSetting.saMonster[i].psCharacter, sizeof(CharacterData));

								break;
							}
						}

						if (sMonster.szName[0])
						{
							UnitInfo * psNewUnitInfo = sMonster.psUnitInfo;

							int iSpawnCount = RandomI(psNewUnitInfo->iGroupLimitMin, psNewUnitInfo->iGroupLimitMax);

							if (iSpawnCount <= 0)
								iSpawnCount = 1;

							XMASHANDLE->OnSpawnMonsterEvent(&sMonster, pcMap);

							CreateUnit(pcMap, &sMonster, iSpawnCount);
						}
					}
				}
			}
		}

		//Update Spawn Activity based on Users
		switch (pcMap->uCounter % 512)
		{
		case 128:
		{
			//Reset Active Spawn
			ZeroMemory(pcMap->baSpawnFlagActive, sizeof(pcMap->baSpawnFlagActive));

			//Update Spawns to Active (And Show Spawn Flags)
			UINT uUsersInGame = SERVERUSER->uUsersInGame;
			User ** pcaUserInGame = SERVERUSER->pcaUserInGame;
			for (UINT i = 0; i < uUsersInGame; i++)
			{
				User * pcUser = pcaUserInGame[i];

				SendStageSpawn(pcMap, pcUser);
			}
		}
			break;
		case 192:
		{
			//Show Loot
			UINT uUsersInGame = SERVERUSER->uUsersInGame;
			User ** pcaUserInGame = SERVERUSER->pcaUserInGame;
			for (UINT i = 0; i < uUsersInGame; i++)
			{
				User * pcUser = pcaUserInGame[i];

				if ((dwTickCount - pcUser->dwTimeLastPacket) < 1500)
					SendStageItem(pcMap, pcUser);
			}
		}
			break;
		}

		//Remove Timed Out Loot
		for (int i = 0; i < MAX_LOOT; i++)
		{
			MapLoot * pLoot = pcMap->saLoot + i;

			if ((pLoot->bInUse) && (pLoot->dwEndTime < TICKCOUNT))
				pLoot->bInUse = FALSE;
		}

		//Bellatra Map Update
		if (pcMap->pcBaseMap->iMapID == MAPID_Bellatra)
		{
			if (pcMap->sSpawnSetting.iTotalMonsters > 0)
			{
				CharacterData sNewCharacterData;
				CopyMemory(&sNewCharacterData, pcMap->sSpawnSetting.saMonster[0].psCharacter, sizeof(CharacterData));

				//BELLATRASERVER->UpdateServer(pcMap, &s);
				//rsHardCoreEvent_OpenMonster(pcMap, &s);
			}
		}

		//Bless Castle Map Update
		if (pcMap->pcBaseMap->iMapID == MAPID_BlessCastle)
		{
			//Update BC
			SERVERBLESSCASTLE->Update();
		}

		//Swifts in Map from Night to Day or vice versa
		if (pcMap->bNight != IsNight())
		{
			//DayNight swift in maps with Night Spawn on (Navisko Town)
			if (pcMap->pcBaseMap->bNightSpawn)
			{
				if (IsNight())
				{
					CharacterData * psZombie = SERVERUNIT->GetCharacterDataByEffect(MONSTEREFFECTID_ZOMBI);

					UINT uUsersInGame = SERVERUNIT->uUnitsInGame;
					Unit ** pcaUnitInGame = SERVERUNIT->pcaUnitInGame;

					for (UINT i = 0; i < uUsersInGame; i++)
					{
						Unit * pcUnit = pcaUnitInGame[i];

						//In Use AND Same Map AND NPC AND Not Bellatra NPC?
						if (pcUnit->bActive == TRUE &&
							pcUnit->pcMap == pcMap &&
							pcUnit->sCharacterData.iType == CHARACTERTYPE_NPC &&
							pcUnit->sUnitInfo.iBellatraTypeNPC == 0)
						{
							//Reset Unit Data
							pcUnit->Close();

							//Set in Use again
							pcUnit->bActive = TRUE;

							//Copy Zombie Data
							CopyMemory(&pcUnit->sCharacterData, psZombie, sizeof(CharacterData));
							CopyMemory(&pcUnit->sUnitInfo, psZombie->psUnitInfo, sizeof(UnitInfo));

							//Set Mode
							pcUnit->ActionPattern = UPDATEMODE_ServerMonster;

							//Update Num Alive
							pcMap->iNumAliveUnitData++;

							//Load Model INI
							pcUnit->SetLoadPattern(pcUnit->sCharacterData.Monster.szBodyModel);

							//Set Lure Distance
							pcUnit->iLureDistance = UNIT_DEFAULT_LURE_DISTANCE_FAR;

							AddMonsterSpawn(pcMap, pcUnit);

							//Set Death Timer
							pcUnit->iDeathCounter = 256;

							//Animate to Idle
							pcUnit->SetMotionFromCode(ANIMATIONTYPE_Idle);

							//Make Unit appear as New Load
							pcUnit->sCharacterData.bUpdateInfo[0]++;
						}
					}
				}
				else
				{
					//Kill Alive Monsters
					UINT uUsersInGame = SERVERUNIT->uUnitsInGame;
					Unit ** pcaUnitInGame = SERVERUNIT->pcaUnitInGame;

					for (UINT i = 0; i < uUsersInGame; i++)
					{
						Unit * pcUnit = pcaUnitInGame[i];

						//InUse AND Same Map AND Monster?
						if (pcUnit->bActive == TRUE &&
							pcUnit->pcMap == pcMap &&
							pcUnit->sCharacterData.iType == CHARACTERTYPE_Monster)
						{
							//Kill Unit
							pcUnit->SetMotionFromCode(ANIMATIONTYPE_Die);
							pcUnit->sCharacterData.sHP.sMin = 0;
						}
					}

					//Spawn NPCs
					for (UINT i = 0; i < MAX_NPCINMAP; i++)
					{
						PacketUnitInfo * psNPC = pcMap->saNPC + i;

						if ((psNPC->iHeader != 0))
							SpawnNPC(pcMap, psNPC);
					}
				}
			}

			//DayNight swift in Ricarten

			if (pcMap->pcBaseMap->iMapID == MAPID_RicartenTown)
			{
				SERVERUNIT->FreeEventUnit(100);

				if (IsNight())
				{
					SERVERUNIT->CreateEventUnit(100);
				}
				else
				{
					//Switching to Day.. spawn Wolverine NPCs
					for (UINT i = 0; i < MAX_NPCINMAP; i++)
					{
						PacketUnitInfo * psNPC = pcMap->saNPC + i;

						if ((psNPC->iHeader != 0) && (psNPC->sCharacterData.iMonsterEffectID == MONSTEREFFECTID_WOLVERLIN))
							SpawnNPC(pcMap, psNPC);
					}
				}
			}

			//Swift DayNight Time in Map
			pcMap->bNight = IsNight();
		}
	}
}
void CServerMap::SendItemStageNearUsers(Map * pcMap, MapLoot * psItemStage)
{
	PacketStageItemData sPacket;
	ZeroMemory(&sPacket, sizeof(PacketStageItemData));
	sPacket.iLength = sizeof(PacketStageItemData::StageItemData) + 16;
	sPacket.iHeader = PKTHDR_PlayItem;
	sPacket.bActive = TRUE;

	ItemID sItemID = psItemStage->sLootItem.sItem.sItemID;

	sPacket.saItems[sPacket.iCount].bActive = psItemStage->bInUse;
	sPacket.saItems[sPacket.iCount].iX = psItemStage->sPosition.iX << 8;
	sPacket.saItems[sPacket.iCount].iY = psItemStage->sPosition.iY << 8;
	sPacket.saItems[sPacket.iCount].iZ = psItemStage->sPosition.iZ << 8;
	sPacket.saItems[sPacket.iCount].iItemID = sItemID.ToInt();
	sPacket.saItems[sPacket.iCount].iClass = ClassFlagToCharacterClass((EClassFlag)psItemStage->sLootItem.sItem.eSpecialization);

	if (psItemStage->sLootItem.sItem.iPotionCount > 1 && sItemID.ToItemBase() == ITEMBASE_Potion)
		STRINGFORMAT(sPacket.saItems[sPacket.iCount].szName, "%sx%d", psItemStage->sLootItem.sItem.szItemName, psItemStage->sLootItem.sItem.iPotionCount);
	else
		STRINGCOPY(sPacket.saItems[sPacket.iCount].szName, psItemStage->sLootItem.sItem.szItemName);

	sPacket.iCount++;

	Point3D sPosition = psItemStage->sPosition << 8;

	for (int i = 0; i < SERVERUSER->uUsersInGame; i++)
	{
		User * pcUser = SERVERUSER->pcaUserInGame[i];

		if (sPosition.WithinPTDistance(&pcUser->sPosition, 544))
			SENDPACKET(pcUser, &sPacket);
	}
}
void CServerMap::SendItemStageUser(Map * pcMap, User * pcUser, MapLoot * psItemStage)
{
	PacketStageItemData sPacket;
	ZeroMemory(&sPacket, sizeof(PacketStageItemData));
	sPacket.iLength = sizeof(PacketStageItemData::StageItemData) + 16;
	sPacket.iHeader = PKTHDR_PlayItem;
	sPacket.bActive = TRUE;

	ItemID sItemID = psItemStage->sLootItem.sItem.sItemID;

	sPacket.saItems[sPacket.iCount].bActive = psItemStage->bInUse;
	sPacket.saItems[sPacket.iCount].iX = psItemStage->sPosition.iX << 8;
	sPacket.saItems[sPacket.iCount].iY = psItemStage->sPosition.iY << 8;
	sPacket.saItems[sPacket.iCount].iZ = psItemStage->sPosition.iZ << 8;
	sPacket.saItems[sPacket.iCount].iItemID = sItemID.ToInt();
	sPacket.saItems[sPacket.iCount].iClass = ClassFlagToCharacterClass((EClassFlag)psItemStage->sLootItem.sItem.eSpecialization);

	if (psItemStage->sLootItem.sItem.iPotionCount > 1 && sItemID.ToItemBase() == ITEMBASE_Potion)
		STRINGFORMAT(sPacket.saItems[sPacket.iCount].szName, "%sx%d", psItemStage->sLootItem.sItem.szItemName, psItemStage->sLootItem.sItem.iPotionCount);
	else
		STRINGCOPY(sPacket.saItems[sPacket.iCount].szName, psItemStage->sLootItem.sItem.szItemName);

	sPacket.iCount++;

	SENDPACKET(pcUser, &sPacket);
}
void CServerMap::SendStageSpawn(Map * pcMap, User * pcUser)
{
	if (pcUser)
	{
		PacketStageItemData sPacket;
		ZeroMemory(&sPacket, sizeof(PacketStageItemData));

		pcMap->iNumActiveSpawnFlag = 0;
		pcMap->iNumSpawnFlag = 0;

		int dX = 0, dZ = 0, iDistance = 0;
		for (int i = 0; i < 200; i++)
		{
			if (sPacket.iCount == 50 && pcUser->iGameLevel >= GAMELEVEL_Three)
			{
				sPacket.iLength = (sizeof(PacketStageItemData::StageItemData)* sPacket.iCount) + 16;
				sPacket.iHeader = PKTHDR_PlayItem;
				sPacket.bActive = TRUE;
				SENDPACKET(pcUser, &sPacket, TRUE);
				ZeroMemory(&sPacket, sizeof(PacketStageItemData));
			}

			SpawnFlag * p = pcMap->saSpawnFlag + i;

			if (p->bActive)
			{
				dX = p->iX - (pcUser->sPosition.iX >> 8);
				dZ = p->iZ - (pcUser->sPosition.iZ >> 8);

				iDistance = (dX*dX + dZ * dZ);

				if (iDistance < 0xC8000 && abs(dX) < 4096 && abs(dZ) < 4096)
				{
					if (pcUser->iGameLevel >= GAMELEVEL_Three && (pcMap->uCounter & 0x1FF) == 0x80)
					{
						sPacket.saItems[sPacket.iCount].bActive = p->bActive;
						sPacket.saItems[sPacket.iCount].iX = p->iX << 8;
						sPacket.saItems[sPacket.iCount].iY = 0;
						sPacket.saItems[sPacket.iCount].iZ = p->iZ << 8;
						sPacket.saItems[sPacket.iCount].iItemID = 0;
						sPacket.saItems[sPacket.iCount].iClass = 0;
						STRINGCOPY(sPacket.saItems[sPacket.iCount].szName,p->szName);

						sPacket.iCount++;
					}
				}

				if (iDistance < 0x1C2000 && abs(dX) < 4096 && abs(dZ) < 4096)
				{
					pcMap->baSpawnFlagActive[i]++;
				}

				if (pcMap->baSpawnFlagActive[i])
					pcMap->iNumActiveSpawnFlag++;
				pcMap->iNumSpawnFlag++;
			}
		}
		if (sPacket.iCount > 0 && pcUser->iGameLevel >= GAMELEVEL_Three)
		{
			sPacket.iLength = (sizeof(PacketStageItemData::StageItemData)* sPacket.iCount) + 16;
			sPacket.iHeader = PKTHDR_PlayItem;
			sPacket.bActive = TRUE;
			SENDPACKET(pcUser, &sPacket, TRUE);
		}
	}
}

void CServerMap::SendStageItem(Map * pcMap, User * pcUser)
{
	if (!pcUser)
		return;

	PacketStageItemData sPacket;
	ZeroMemory(&sPacket, sizeof(PacketStageItemData));

	int dX = 0, dZ = 0, iDistance = 0;
	for (int i = 0; i < MAX_LOOT; i++)
	{
		if (sPacket.iCount == 50)
			break;

		MapLoot * p = pcMap->saLoot + i;
		if (p->bInUse && p->dwDropTime < TICKCOUNT && (p->dwEndTime - 10000) > TICKCOUNT)
		{
			if (p->bExclusive && (p->lExclusiveOwnerID != 0 && p->lExclusiveOwnerID != 1) && (p->lExclusiveOwnerID != pcUser->iID))
				continue;

			dX = p->sPosition.iX - (pcUser->sPosition.iX >> 8);
			dZ = p->sPosition.iZ - (pcUser->sPosition.iZ >> 8);

			iDistance = (dX*dX + dZ * dZ);

			if (iDistance < 0xC8000 && abs(dX) < 4096 && abs(dZ) < 4096)
			{
				DWORD dwCode = p->sLootItem.sItem.sItemID.ToItemID();

				sPacket.saItems[sPacket.iCount].bActive = p->bInUse;
				sPacket.saItems[sPacket.iCount].iX = p->sPosition.iX << 8;
				sPacket.saItems[sPacket.iCount].iY = p->sPosition.iY << 8;
				sPacket.saItems[sPacket.iCount].iZ = p->sPosition.iZ << 8;
				sPacket.saItems[sPacket.iCount].iItemID = dwCode;
				sPacket.saItems[sPacket.iCount].iClass = ClassFlagToCharacterClass((EClassFlag)p->sLootItem.sItem.eSpecialization);

				dwCode &= 0xFFFF0000;

				if (p->sLootItem.sItem.iPotionCount > 1 && (dwCode & 0xFF000000) == 0x04000000)
					STRINGFORMAT(sPacket.saItems[sPacket.iCount].szName, "%sx%d", p->sLootItem.sItem.szItemName, p->sLootItem.sItem.iPotionCount);
				else
					STRINGCOPY(sPacket.saItems[sPacket.iCount].szName, p->sLootItem.sItem.szItemName);

				sPacket.iCount++;
			}
		}
	}
	if (sPacket.iCount > 0)
	{
		sPacket.iLength = (sizeof(PacketStageItemData::StageItemData) * sPacket.iCount) + 16;
		sPacket.iHeader = PKTHDR_PlayItem;
		sPacket.bActive = TRUE;
		SENDPACKET(pcUser, &sPacket, TRUE);
	}
}

MapLoot * CServerMap::FindItemStage(Map * pcMap, Point3D sPosition)
{
	for (int i = 0; i < MAX_LOOT; i++)
	{
		MapLoot * p = pcMap->saLoot + i;

		if (p->bInUse && p->sPosition == sPosition)
			return p;
	}

	return nullptr;
}
MapLoot * CServerMap::AddItem(Map * pcMap, LootItem * psItem, Point3D sPosition, BOOL bNewItem)
{
	Point3D sNewPosition;
	int iHeight = 0;

	BOOL bRet = FALSE;

	for (int i = 0; i < 8; i++)
	{
		sNewPosition = (sPosition + sPositionList[RandomI(0, 8) & 7]) << 8;

		iHeight = pcMap->pcStage->GetFloorHeight(sNewPosition.iX, sNewPosition.iY, sNewPosition.iZ, 0x2000);

		if (iHeight != CLIP_OUT)
		{
			if (abs(iHeight - sNewPosition.iY) < 0x2000)
			{
				if (!FindItemStage(pcMap, sPosition))
					bRet = TRUE;
			}
		}
	}
	
	if (bRet)
	{
		sPosition = Point3D(sNewPosition.iX, iHeight, sNewPosition.iZ) >> 8;

		for (int iCount = 0; iCount < 2; iCount++)
		{
			for (int i = 0; i < MAX_LOOT; i++)
			{
				MapLoot * pLoot = pcMap->saLoot + i;

				if (!pLoot->bInUse || (iCount && pLoot->lExclusiveOwnerID == 0))
				{
					pLoot->sPosition = sPosition;
					pLoot->bInUse = TRUE;
					CopyMemory(&pLoot->sLootItem, psItem, sizeof(LootItem));

					pLoot->dwDropTime = TICKCOUNT;
					pLoot->bExclusive = bNewItem;

					EItemType sItemType = pLoot->sLootItem.sItem.sItemID.ToItemType();

					pLoot->dwEndTime = (sItemType == ITEMTYPE_GoldAndExp ||
						sItemType == ITEMTYPE_HealthPotion ||
						sItemType == ITEMTYPE_StaminaPotion) ?
						TICKCOUNT + 1000 * 90 :
						TICKCOUNT + 1000 * 60 * 3;

					if (sItemType != ITEMTYPE_HealthPotion &&
						sItemType != ITEMTYPE_ManaPotion &&
						sItemType != ITEMTYPE_StaminaPotion &&
						sItemType != ITEMTYPE_GoldAndExp)
						pLoot->lExclusiveOwnerID = 1;

					return pLoot;
				}
			}
		}
	}

	return nullptr;
}
void CServerMap::DelItem(Map * pcMap, MapLoot * psItem)
{
	if (psItem)
	{
		psItem->bInUse = FALSE;

		PacketGetItem sPacket;
		sPacket.iHeader = PKTHDR_DeleteItem;
		sPacket.iLength = sizeof(PacketGetItem);
		sPacket.sPosition = psItem->sPosition << 8;
		sPacket.pcMap = pcMap;

		for (size_t i = 0; i < PLAYERS_MAX; i++)
		{
			User * pcUser = USERSDATA + i;

			if (pcUser->pcSocketData && pcUser->iID && pcUser->iMapID == pcMap->pcBaseMap->iMapID)
			{
				int iX = psItem->sPosition.iX - (pcUser->sPosition.iX >> 8);
				int iZ = psItem->sPosition.iZ - (pcUser->sPosition.iZ >> 8);
				int iDistance = iX * iX + iZ * iZ;

				if (iDistance < 0xC8000 && abs(iX) < 4096 && abs(iZ) < 4096)
					SENDPACKET(pcUser, &sPacket);
			}
		}
	}
}

BOOL CServerMap::IsEXPMap(int iMapID)
{
	BOOL bResult = FALSE;
	switch (iMapID)
	{
	case MAPID_MysteryForest1:
	case MAPID_MysteryForest2:
	case MAPID_MysteryForest3:
	case MAPID_MysteryDesert1:
	case MAPID_MysteryDesert2:
	case MAPID_MysteryDesert3:
	case MAPID_ForgottenTempleF1:
	case MAPID_ForgottenTempleF2:
	case MAPID_AncientDungeonF1:
	case MAPID_AncientDungeonF2:
	case MAPID_AncientDungeonF3:
		bResult = TRUE;
		break;
	default:
		break;
	}
	return bResult;
}
BOOL CServerMap::IsPVPMap(int iMapID)
{
	if (iMapID == MAPID_BlessCastle)
		return TRUE;

	if (EVENT_PVP)
	{
		for (auto &pcMap : m_vpMap)
		{
			if (iMapID != MAPID_Invalid && iMapID == pcMap->pcBaseMap->GetID())
			{
				if (pcMap->pcBaseMap->bPvp && IsTownMap(iMapID) == FALSE)
					return TRUE;
			}
		}
	}

	return FALSE;
}

BOOL CServerMap::IsTownMap(int iMapID)
{
	BOOL bResult = FALSE;
	switch (iMapID)
	{
	case MAPID_RicartenTown:
	case MAPID_PhillaiTown:
	case MAPID_Atlantis:
		bResult = TRUE;
		break;
	default:
		break;
	}
	return bResult;
}

void CServerMap::UpdateTime()
{
	m_iTime = GetGameTime();

	m_bNight = (m_iTime >= 4 && m_iTime < 23) ? FALSE : TRUE;
}
int CServerMap::GetGameTime()
{
	DWORD dwTime;

	dwTime = TICKCOUNT;
	dwTime = (dwTime / GAME_WORLDTIME) / 60;
	dwTime = dwTime - (((int)(dwTime / 24)) * 24);

	return (int)dwTime;
}
Map *CServerMap::GetMapByXZ(int iX, int iZ)
{
	for (auto & pcMap : m_vpMap)
	{
		if (pcMap->pcStage)
		{
			int iHeight = pcMap->pcStage->GetHeight(iX, iZ);

			if (iHeight > 0)
				return pcMap;
		}
	}

	return nullptr;
}
void CServerMap::SpawnMonsterBoss(Map * pcMap, BossMonster *psBoss)
{
	if (psBoss && psBoss->pcdBoss)
	{
		if (psBoss->pcdBoss->iMonsterEffectID == MONSTEREFFECTID_BABEL)
		{
			if (dwBabelEndTime > SERVER_GAMETIME)
				return;

			eBabelMapID = (EMapID)pcMap->pcBaseMap->iMapID;

			for (int i = 0; i < MAX_ALIVEMONSTERS; i++)
			{
				Unit * pcUnit = pcMap->pcaUnitData[i];

				if (pcUnit)
				{
					if (pcUnit->bActive && pcUnit->GetAnimation() != ANIMATIONTYPE_Die)
					{
						pcUnit->SetMotionFromCode(ANIMATIONTYPE_Flinch);
						pcUnit->iStunTimeLeft = 16 * 8;
					}
				}
			}
		}

		Point3D sPosition;

		if (psBoss->pcdBoss->bExclusiveBoss = SetBossPosition(pcMap, psBoss->pcdBoss, sPosition))
		{
			pcMap->sMonsterPosition = sPosition;
		}

		Unit *pcUnit = nullptr;

		if (psBoss->pcdBoss)
		{
			pcMap->bForceCreateMonster = TRUE;
			pcUnit = CreateUnit(pcMap, psBoss->pcdBoss, 0);
		}
		if (psBoss->pcdMinion)
		{
			pcMap->bForceCreateMonster = TRUE;
			pcUnit = CreateUnit(pcMap, psBoss->pcdMinion, psBoss->iMinions);
		}

		if (psBoss->pcdBoss->bExclusiveBoss && pcUnit)
		{
			SERVERCHAT->SendChatAllUsersInStage(pcMap->pcBaseMap->iMapID, CHATCOLOR_Global, "Boss> %s Spawned!", psBoss->pcdBoss->szName);
		}

		if (pcMap->sMonsterPosition != Point3D())
		{
			pcMap->sMonsterPosition = Point3D();

			if (pcUnit)
			{
				pcUnit->psaDamageUsersData = new AttackDamageData[ATTACK_DAMAGE_LIST_MAX];

				ZeroMemory(pcUnit->psaDamageUsersData, sizeof(AttackDamageData)*ATTACK_DAMAGE_LIST_MAX);
			}
		}
	}
}
BOOL CServerMap::SetBossPosition(Map * pcMap, CharacterData * psCharacterData, Point3D &sPosition)
{
	BOOL bUpdate = FALSE;

	if (pcMap && pcMap->pcBaseMap && psCharacterData)
	{
		int iMapID = pcMap->pcBaseMap->iMapID;

		DWORD dwEffectID = psCharacterData->iMonsterEffectID;

		switch (iMapID)
		{
		case MAPID_RailwayOfChaos:
			if (dwEffectID == MONSTEREFFECTID_BABEL)
			{
				sPosition = Point3D(50172, 0, 13193) * 256;
				bUpdate = TRUE;
			}
			break;
		case MAPID_HeartOfPerum:
			if (dwEffectID == MONSTEREFFECTID_BABEL)
			{
				sPosition = Point3D(37086, 0, 26425) * 256;
				bUpdate = TRUE;
			}
			break;
		case MAPID_GallubiaValley:
			if (dwEffectID == MONSTEREFFECTID_CHAOSCARA)
			{
				sPosition = Point3D(8733873,0, 9408604);
				bUpdate = TRUE;
			}
			break;

		case MAPID_FrozenSanctuary:
			if (dwEffectID == MONSTEREFFECTID_DEATHKNIGHT)
			{
				sPosition = Point3D(9721570, 0, 12473917);
				bUpdate = TRUE;
			}
			break;

		case MAPID_KelvezuLair:
			if (dwEffectID == MONSTEREFFECTID_KELVEZU)
			{
				sPosition = Point3D(33023, 0, 52608) * 256;
				bUpdate = TRUE;
			}
			break;

		case MAPID_LostTemple:
			if (dwEffectID == MONSTEREFFECTID_MOKOVA)
			{
				sPosition = Point3D(-12057, 0, 13225) * 256;
				bUpdate = TRUE;
			}
			break;

		case MAPID_EndlessTowerF1:
			if (dwEffectID == MONSTEREFFECTID_GOBLINSHAMAN)
			{
				sPosition = Point3D(3646068, 0, -10323850);
				bUpdate = TRUE;
			}
			break;

		case MAPID_EndlessTowerF2:
			if (dwEffectID == MONSTEREFFECTID_GORGON)
			{
				sPosition = Point3D(1348259, 0, -9876309);
				bUpdate = TRUE;
			}
			break;

		case MAPID_EndlessTowerF3:
			if (dwEffectID == MONSTEREFFECTID_GORGON)
			{
				sPosition = Point3D(1348259, 0, -9876309);
				bUpdate = TRUE;
			}
			break;

		case MAPID_IceMineF1:
			if (dwEffectID == MONSTEREFFECTID_TULLA)
			{
				sPosition = Point3D(6456813, 0, -9239019);
				bUpdate = TRUE;
			}
			break;

		case MAPID_AbyssSea:
			if (dwEffectID == MONSTEREFFECTID_Yagditha)
			{
				sPosition = Point3D(-5900643, 0, 17478);
				bUpdate = TRUE;
			}
			break;

		case MAPID_SecretLaboratory:
			if (dwEffectID == MONSTEREFFECTID_Draxos)
			{
				sPosition = Point3D(-3076384, 0, -15012873);
				bUpdate = TRUE;
			}
			break;

		default:
			break;
		}
	}

	return bUpdate;
}
int CServerMap::GetEmptyIndexUnit(Map *pcMap)
{
	for (int i = 0; i < MAX_ALIVEMONSTERS; i++)
	{
		//Empty Pointer? Found.
		if (pcMap->pcaUnitData[i] == NULL)
			return i;
	}

	return -1;
}
BOOL CServerMap::AddMonsterSpawn(Map * pcMap, Unit * pcUnit)
{
	//Get Index of empyt Unit in Stage
	int iIndex = GetEmptyIndexUnit(pcMap);

	if (iIndex >= 0)
	{
		//Set Unit to stage
		pcMap->pcaUnitData[iIndex] = pcUnit;

		pcMap->iaSpawnMonsterActive[pcUnit->iSpawnPointIndex]++;

		pcUnit->pcMapSpawn = pcMap;

		//Set last Unit Pointer at Stage
		for (int i = iIndex; i < MAX_ALIVEMONSTERS; i++)
		{
			if (pcMap->pcaUnitData[i] != NULL)
				pcMap->iNumUsingUnit = i + 1;
		}

		return TRUE;
	}

	return FALSE;
}
BOOL CServerMap::DelMonsterSpawn(Map * pcMap, Unit * pcUnit)
{
	if (pcMap->iaSpawnMonsterActive[pcUnit->iSpawnPointIndex] > 0)
		pcMap->iaSpawnMonsterActive[pcUnit->iSpawnPointIndex] --;

	//Clear Unit Pointer on Stage (killed or closed Unit)
	for (int i = 0; i < MAX_ALIVEMONSTERS; i++)
	{
		if (pcMap->pcaUnitData[i] == pcUnit)
		{
			pcMap->pcaUnitData[i] = NULL;

			return TRUE;
		}
	}

	return FALSE;
}
BOOL CServerMap::SetSpawnMonster(Map * pcMap, Unit * pcUnit)
{
	int iFlag = 0, iX = 0, iZ = 0;

	for (int i = pcMap->iNumActiveSpawns; i < 200; i++)
	{
		SpawnFlag * p = pcMap->saSpawnFlag + i;

		if (p->bActive && pcMap->baSpawnFlagActive[i] &&
			pcMap->iaSpawnMonsterActive[i] < pcMap->sSpawnSetting.iSpawnMonsters &&
			pcMap->dwaTimeLastMonsterSpawned[i] < SERVER_GAMETIME)
		{
			iX = p->iX << 8;
			iZ = p->iZ << 8;
			pcMap->iNumActiveSpawns = i + 1;
			pcMap->iLastActiveSpawn = i;
			iFlag++;
			break;
		}
	}

	if (iFlag == 0)
	{
		for (int i = 0; i < 200; i++)
		{
			SpawnFlag * p = pcMap->saSpawnFlag + i;

			if (p->bActive && pcMap->baSpawnFlagActive[i] &&
				pcMap->iaSpawnMonsterActive[i] < pcMap->sSpawnSetting.iSpawnMonsters &&
				pcMap->dwaTimeLastMonsterSpawned[i] < SERVER_GAMETIME)
			{
				iX = p->iX << 8;
				iZ = p->iZ << 8;
				pcMap->iNumActiveSpawns = i + 1;
				pcMap->iLastActiveSpawn = i;
				iFlag++;
				break;
			}
		}
	}

	if (iFlag == 0 && (pcMap->bForceCreateMonster || pcUnit->sCharacterData.sGlow == TRUE))
	{
		pcMap->bForceCreateMonster = FALSE;

		for (int i = pcMap->iNumActiveSpawns; i < 200; i++)
		{
			SpawnFlag * p = pcMap->saSpawnFlag + i;

			if (p->bActive && pcMap->baSpawnFlagActive[i])
			{
				iX = p->iX << 8;
				iZ = p->iZ << 8;
				iFlag++;
				break;
			}
		}

		if (iFlag == 0 && pcMap->iNumActiveSpawns < 200)
		{
			for (int i = 0; i < pcMap->iNumActiveSpawns; i++)
			{
				SpawnFlag * p = pcMap->saSpawnFlag + i;

				if (p->bActive && pcMap->baSpawnFlagActive[i])
				{
					iX = p->iX << 8;
					iZ = p->iZ << 8;
					iFlag++;
					break;
				}
			}
		}

		if (iFlag == 0)
		{
			for (int i = 0; i < 200; i++)
			{
				SpawnFlag * p = pcMap->saSpawnFlag + i;

				if (p->bActive)
				{
					iX = p->iX << 8;
					iZ = p->iZ << 8;
					iFlag++;
					break;
				}
			}
		}
	}

	if (iFlag > 0)
	{
		if (pcMap->sMonsterPosition != Point3D())
		{
			iX = pcMap->sMonsterPosition.iX;
			iZ = pcMap->sMonsterPosition.iZ;
		}

		pcUnit->Init();
		pcUnit->lpStage = pcMap->pcStage;

		int iXRand = 0;
		int iZRand = 0;
		iXRand = rand() % (128 << 8);
		iZRand = rand() % (128 << 8);
		iXRand -= 64 << 8;
		iZRand -= 64 << 8;

		iX += iXRand;
		iZ += iZRand;

		pcUnit->SetPosi(iX, 0, iZ, 0, 0, 0);

		pcUnit->sSpawnPosition.iX = iX;
		pcUnit->sSpawnPosition.iY = pcUnit->pY;
		pcUnit->sSpawnPosition.iZ = iZ;
		pcUnit->iLureDistance = 256 * 256;

		pcUnit->iSpawnPointIndex = pcMap->iLastActiveSpawn;

		pcMap->dwaTimeLastMonsterSpawned[pcMap->iLastActiveSpawn] = SERVER_GAMETIME + pcMap->sSpawnSetting.iSpawnIntervalMax;

		return TRUE;
	}

	return FALSE;
}
BOOL CServerMap::SetSpawnMonster(Map * pcMap, Unit * pcUnit, Point3D sPosition)
{
	for (int i = 0; i < 8; i++)
	{
		Point3D sPositionNew = sPosition + (sPositionList[RandomI(0, 8) & 7] << 8);

		int iHeight = pcMap->pcStage->GetFloorHeight(sPositionNew.iX, sPositionNew.iY, sPositionNew.iZ, 0x2000);

		if (iHeight != CLIP_OUT)
		{
			if (abs(iHeight - sPositionNew.iY) < 0x4000)
			{
				pcUnit->Init();
				pcUnit->lpStage = pcMap->pcStage;
				pcUnit->SetPosi(sPositionNew.iX, 0, sPositionNew.iZ, 0, 0, 0);
				pcUnit->sSpawnPosition.iX = sPositionNew.iX;
				pcUnit->sSpawnPosition.iY = pcUnit->pY;
				pcUnit->sSpawnPosition.iZ = sPositionNew.iZ;
				pcUnit->iLureDistance = 256 * 256;
				pcUnit->iSpawnPointIndex = pcMap->iLastActiveSpawn;
				return TRUE;
			}
		}
	}

	return FALSE;
}
void CServerMap::SetSpawnMonster(Map * pcMap)
{
	int iIndex = 1;

	for (int i = 199; i >= 0; i--)
	{
		if (pcMap->saSpawnFlag[i].bActive)
			iIndex = i + 1;
	}

	pcMap->iNumActiveSpawns = rand() % iIndex;
}

BOOL CServerMap::SpawnMonsterBC(Map * pcMap, CharacterData * psCharacterData, Point3D sPosition, int iClanID)
{
	if (pcMap)
	{
		pcMap->bForceCreateMonster = TRUE;

		Unit * pcUnit = CreateUnit(pcMap, psCharacterData);

		if (pcUnit)
		{
			pcUnit->sPosition = sPosition;
			pcUnit->sAngle = Point3D();
			pcUnit->iLureDistance = 0;
			pcUnit->SetMotionFromCode(ANIMATIONTYPE_Idle);
			pcUnit->TargetMoveCount = 0;

			int iMonsterEffectID = pcUnit->sCharacterData.iMonsterEffectID;

			if (iMonsterEffectID == MONSTEREFFECTID_CASTLE_TOWER_B ||
				iMonsterEffectID == MONSTEREFFECTID_CASTLE_CRYSTAL_R ||
				iMonsterEffectID == MONSTEREFFECTID_CASTLE_CRYSTAL_G ||
				iMonsterEffectID == MONSTEREFFECTID_CASTLE_CRYSTAL_B ||
				iMonsterEffectID == MONSTEREFFECTID_CASTLE_CRYSTAL_N ||
				iMonsterEffectID == MONSTEREFFECTID_CASTLE_DOOR)
			{
				pcUnit->iSpecialType = 2;

				SERVERUNIT->IsMultiplyHPMonter(pcUnit, TRUE);
			}
			else
			{
				pcUnit->sSpawnPosition = sPosition;
				pcUnit->iLureDistance = 16 * 64 * 16 * 64;
			}

			pcUnit->iClanID = iClanID;

			return TRUE;
		}
	}

	return FALSE;
}
void CServerMap::AddFlagPoint(User * pcUser, const char * pszDescription)
{
	if (pcUser && lstrlenA(pszDescription))
	{
		int iX = pcUser->sPosition.iX;
		int iZ = pcUser->sPosition.iZ;
		int iStageID = pcUser->iMapID;

		auto pcMap = GetMapByXZ(iX, iZ);

		if (pcMap != 0)
		{

			// Get Last ID
			int iID = 0;
			SQLConnection * pcDB = SQLCONNECTION(DATABASEID_GameDB);

			if (pcDB->Open())
			{
				if (pcDB->Prepare("SELECT TOP 1 ID FROM MapSpawnPoint ORDER BY ID DESC"))
				{
					if (pcDB->Execute() && pcDB->Fetch())
						pcDB->GetData(1, PARAMTYPE_Integer, &iID, 0);
				}
				pcDB->Close();
			}

			iID++;
			if (pcDB->Open())
			{
				if (pcDB->Prepare("INSERT INTO MapSpawnPoint([ID],[Stage],[X],[Z],[Description]) VALUES(?,?,?,?,?)"))
				{
					pcDB->BindParameterInput(1, PARAMTYPE_Integer, &iID);
					pcDB->BindParameterInput(2, PARAMTYPE_Integer, &iStageID);
					int ishrX = iX >> 8;
					int ishrZ = iZ >> 8;
					pcDB->BindParameterInput(3, PARAMTYPE_Integer, &ishrX);
					pcDB->BindParameterInput(4, PARAMTYPE_Integer, &ishrZ);
					pcDB->BindParameterInput(5, PARAMTYPE_String, (void*)pszDescription);
					pcDB->Execute();
				}
				pcDB->Close();
			}

			AddMapSpawnData(pcMap, pszDescription, iID, iX >> 8, iZ >> 8);
			SendFlagPoint(pcMap);

			SERVERCHAT->SendDebugChat(pcUser, CHATCOLOR_Error, "> Flag Point '%s' Added! [X: %d   Z: %d]", pszDescription, iX >> 8, iZ >> 8);
		}
		else
			SERVERCHAT->SendChat(pcUser, CHATCOLOR_Error, "> Map not found!");
	}
}
void CServerMap::DeleteFlagPoint(User * pcUser, PacketDeleteFlagPoint * psPacket)
{
	if (pcUser && pcUser->iGameLevel > GAMELEVEL_Three)
	{
		Map * pcMap = GetMapByXZ(psPacket->iX, psPacket->iZ);
		if (pcMap)
		{
			if (pcMap->pcBaseMap)
			{
				SQLConnection * pcDB = SQLCONNECTION(DATABASEID_GameDB);

				int iX = psPacket->iX >> 8;
				int iZ = psPacket->iZ >> 8;

				if (pcDB->Open())
				{
					if (pcDB->Prepare("DELETE FROM MapSpawnPoint WHERE (X=?) AND (Z=?)"))
					{
						pcDB->BindParameterInput(1, PARAMTYPE_Integer, &iX);
						pcDB->BindParameterInput(2, PARAMTYPE_Integer, &iZ);
						pcDB->Execute();
					}
					pcDB->Close();
				}

				DelMapSpawnData(pcMap, iX, iZ);
				SendFlagPoint(pcMap);
			}
		}
	}
}
void CServerMap::AddMapSpawnData(Map * pcMap, const char * pszName, int iID, int iX, int iZ)
{
	for (int i = 0; i < MAX_SPAWNFLAGS; i++)
	{
		if (!pcMap->saSpawnFlag[i].bActive)
		{
			pcMap->saSpawnFlag[i].bActive = TRUE;
			pcMap->saSpawnFlag[i].iID = iID;
			pcMap->saSpawnFlag[i].iX = iX;
			pcMap->saSpawnFlag[i].iZ = iZ;

			STRINGCOPY(pcMap->saSpawnFlag[i].szName, pszName);

			pcMap->iaSpawnMonsterActive[i] = 0;
		}
	}
}
void CServerMap::DelMapSpawnData(Map * pcMap, int iX, int iZ)
{
	for (int i = 0; i < MAX_SPAWNFLAGS; i++)
	{
		if (pcMap->saSpawnFlag[i].bActive && pcMap->saSpawnFlag[i].iX == iX && pcMap->saSpawnFlag[i].iZ == iZ)
		{
			ZeroMemory(&pcMap->saSpawnFlag[i], sizeof(SpawnFlag));
			pcMap->iaSpawnMonsterActive[i] = 0;
		}
	}
}
Unit * CServerMap::CreateUnit(Map * pcMap, CharacterData * psCharacterData, int iGroup)
{
	Unit *pcUnit = SERVERUNIT->GetEmptyUnit();

	if (!pcUnit)
		return NULL;

	int iDist = 4096 * 400;

	if (SetSpawnMonster(pcMap, pcUnit))
	{
		pcMap->iNumAliveUnitData++;

		pcUnit->pcMap = pcMap;
		pcUnit->iID = SERVERUNIT->CreateID();
		pcUnit->ActionPattern = 5;
		memcpy(&pcUnit->sCharacterData, psCharacterData, sizeof(CharacterData));
		memcpy(&pcUnit->sUnitInfo, psCharacterData->psUnitInfo, sizeof(UnitInfo));

		pcUnit->SetLoadPattern(pcUnit->sCharacterData.Player.szBodyModel);

		pcUnit->sCharacterData.iStatPoints = psCharacterData->psUnitInfo->ClassCode;

		pcUnit->iLureDistance = iDist;
		pcUnit->AttackUserFlag = 0;
		pcUnit->pcKillerData = nullptr;

		pcUnit->pcLastAttacker = nullptr;
		pcUnit->iDamageLastAttacker = 0;

		pcUnit->sAngle.iY = (TICKCOUNT << 2) & ANGCLIP;
		pcUnit->SetMotionFromCode(ANIMATIONTYPE_Idle);
		pcUnit->TargetMoveCount = 0;

		AddMonsterSpawn(pcMap, pcUnit);

		pcUnit->iDeathCounter = 256;
		pcUnit->dwLastActiveTime = SERVER_GAMETIME;

		SERVERUNIT->IsMultiplyHPMonter(pcUnit);

		if (pcUnit->sCharacterData.iMonsterEffectID == MONSTEREFFECTID_VAMPRICMACHINE)
			pcUnit->iSpecialType = 1;
	}
	else
	{
		pcUnit->Close();
		return NULL;
	}

	Point3D sPosition = pcUnit->sPosition;

	for (int i = 1; i < iGroup; i++)
	{
		pcUnit = SERVERUNIT->GetEmptyUnit();

		if (!pcUnit)
			return NULL;

		if (SetSpawnMonster(pcMap, pcUnit, sPosition))
		{
			pcMap->iNumAliveUnitData++;

			pcUnit->pcMap = pcMap;
			pcUnit->iID = SERVERUNIT->CreateID();
			pcUnit->ActionPattern = 5;
			memcpy(&pcUnit->sCharacterData, psCharacterData, sizeof(CharacterData));
			memcpy(&pcUnit->sUnitInfo, psCharacterData->psUnitInfo, sizeof(UnitInfo));

			pcUnit->SetLoadPattern(pcUnit->sCharacterData.Player.szBodyModel);

			pcUnit->sCharacterData.iStatPoints = psCharacterData->psUnitInfo->ClassCode;

			pcUnit->iLureDistance = iDist;
			pcUnit->AttackUserFlag = 0;
			pcUnit->pcKillerData = nullptr;

			pcUnit->pcLastAttacker = nullptr;
			pcUnit->iDamageLastAttacker = 0;

			pcUnit->sAngle.iY = (TICKCOUNT << 2) & ANGCLIP;
			pcUnit->SetMotionFromCode(ANIMATIONTYPE_Idle);
			pcUnit->TargetMoveCount = 0;

			AddMonsterSpawn(pcMap, pcUnit);

			pcUnit->iDeathCounter = 256;
			pcUnit->dwLastActiveTime = SERVER_GAMETIME;

			if (pcUnit->sUnitInfo.iMaxPotions)
			{
				if ((rand() % 100) < pcUnit->sUnitInfo.iPerPotions)
					pcUnit->sUnitInfo.iMaxPotions = (rand() % pcUnit->sUnitInfo.iMaxPotions) + 1;
				else
					pcUnit->sUnitInfo.iMaxPotions = 0;
			}
			switch (pcUnit->sCharacterData.iMonsterEffectID)
			{
			case MONSTEREFFECTID_VAMPRICMACHINE:
			case MONSTEREFFECTID_CASTLE_DOOR:
				pcUnit->iSpecialType = 2;
				break;
			}
		}
		else
		{
			pcUnit->Close();
			return NULL;
		}
	}

	return pcUnit;
}
void CServerMap::SpawnNPC(Map * pcMap, PacketUnitInfo * psPacket)
{
	for (int i = 0; i < UNITS_MAX; i++)
	{
		Unit *u = UNITSDATA + i;

		if (u->bActive &&
			u->sCharacterData.iType == CHARACTERTYPE_NPC &&
			u->sPosition == psPacket->sPosition)
			return;
	}

	Unit *pcUnit = SERVERUNIT->GetEmptyUnit();

	if (pcUnit)
	{
		pcUnit->Init();

		psPacket->iID = SERVERUNIT->CreateID();
		pcUnit->sPosition = psPacket->sPosition;
		pcUnit->sAngle = psPacket->sAngle;
		pcUnit->sSpawnPosition = psPacket->sPosition;
		pcUnit->pcMap = pcMap;
		pcUnit->iID = psPacket->iID;
		pcUnit->ActionPattern = 12;

		STRINGCOPY(pcUnit->sCharacterData.szName, psPacket->sCharacterData.szName);

		pcUnit->szMessage[0] = 0;
		ZeroMemory(&pcUnit->sUnitInfo, sizeof(UnitInfo));

		SERVERUNIT->ReadUnitNpcData(&pcUnit->sCharacterData, &pcUnit->sUnitInfo, pcUnit->szMessage);

		if (pcUnit->sUnitInfo.szName[0])
		{
			STRINGCOPY(pcUnit->sCharacterData.szName, pcUnit->sUnitInfo.szName);
			pcUnit->sUnitInfo.szName[0] = 0;
		}

		int iDist = pcUnit->sUnitInfo.MoveRange >> 8;

		pcUnit->iLureDistance = iDist * iDist;

		pcUnit->SetLoadPattern(pcUnit->sCharacterData.Player.szBodyModel);
		pcUnit->lpStage = pcMap->pcStage;

		if (pcUnit->FindMotionCountFromCode(ANIMATIONTYPE_Walking) == 0)
			pcUnit->MoveSpeed = 0;
	}
}
void CServerMap::SendFlagPoint(Map *pcMap)
{
	ZeroMemory(pcMap->baSpawnFlagActive, sizeof(int) * MAX_SPAWNFLAGS);

	for (int i = 0; i < PLAYERS_MAX; i++)
	{
		User * u = USERSDATA + i;

		if (u && u->iID)
			SendStageSpawn(pcMap, u);
	}
}
void CServerMap::ReadUnitSpawnData(Map * pcMap)
{
	if (!GAME_SERVER)
		return;

	// Get Pointers
	SpawnFlag * pSpawnInfo = pcMap->saSpawnFlag;

	int iCount = 0;

	// Get SQL count
	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_GameDB);

	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT COUNT(ID) FROM MapSpawnPoint WHERE Stage=?"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_Integer, &m_uCurrentStageUnitSpawn);
			if (pcDB->Execute() && pcDB->Fetch())
				pcDB->GetData(1, PARAMTYPE_Integer, &iCount, 0);
		}
		pcDB->Close();
	}

	// Max Spawn is MAX_SPAWN_PER_MAP
	if (iCount > MAX_SPAWNFLAGS)
		iCount = MAX_SPAWNFLAGS;

	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT * FROM MapSpawnPoint WHERE Stage=?"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_Integer, &m_uCurrentStageUnitSpawn);
			if (pcDB->Execute() && pcDB->Fetch())
			{
				for (int i = 0; i < iCount; i++)
				{
					pSpawnInfo[i].bActive = TRUE;
					pcDB->GetData(1, PARAMTYPE_Integer, &pSpawnInfo[i].iID, 0);
					pcDB->GetData(3, PARAMTYPE_Integer, &pSpawnInfo[i].iX, 0);
					pcDB->GetData(4, PARAMTYPE_Integer, &pSpawnInfo[i].iZ, 0);
					pcDB->GetData(5, PARAMTYPE_String, pSpawnInfo[i].szName, 32);
					pcDB->Fetch();
				}
			}
		}
		pcDB->Close();
	}

	pcMap->iState = 1;
	m_uCurrentStageUnitSpawn++;
}
void CServerMap::ReadUnitNpcStand(Map * pcMap)
{
	if (!GAME_SERVER)
		return;

	int iTotalUnits = 0;

	// Get Count NPCs in Stage

	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_GameDB);

	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT COUNT(*) FROM MapNPC WHERE Stage=?"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_Integer, &m_uCurrentStageUnitStand);
			if (pcDB->Execute() && pcDB->Fetch())
				pcDB->GetData(1, PARAMTYPE_Integer, &iTotalUnits, 0);
		}
		pcDB->Close();
	}

	if (iTotalUnits != 0)
	{
		// Pointer to packet PlayInfo[200] in StageData
		PacketUnitInfo * psPacket = pcMap->saNPC;

		// Get Data Array

		if (pcDB->Open())
		{
			if (pcDB->Prepare("SELECT * FROM MapNPC WHERE Stage=?"))
			{
				pcDB->BindParameterInput(1, PARAMTYPE_Integer, &m_uCurrentStageUnitStand);

				if (pcDB->Execute() && pcDB->Fetch())
				{
					int j = _countof(pcMap->saNPC);

					for (int i = 0; i < iTotalUnits && i < j; i++)
					{
						BOOL bEnabled = FALSE;

						// SQL data
						pcDB->GetData(3, PARAMTYPE_Integer, &psPacket[i].sPosition.iX, 0);
						pcDB->GetData(4, PARAMTYPE_Integer, &psPacket[i].sPosition.iY, 0);
						pcDB->GetData(5, PARAMTYPE_Integer, &psPacket[i].sPosition.iZ, 0);
						pcDB->GetData(6, PARAMTYPE_Integer, &psPacket[i].sAngle.iY, 0);
						pcDB->GetData(7, PARAMTYPE_String, psPacket[i].sCharacterData.szName, 32);
						pcDB->GetData(8, PARAMTYPE_Integer, &bEnabled, 0);
						pcDB->GetData(9, PARAMTYPE_Integer, &psPacket[i].sCharacterData.iClanID, 0);

						// Packet structure
						psPacket[i].iLength = sizeof(PacketUnitInfo);

						// Is Enabled?
						if (bEnabled)
							psPacket[i].iHeader = PKTHDR_NpcData;

						psPacket[i].sCharacterData.sHP.sMin = 100; // HP default
						psPacket[i].sCharacterData.sHP.sMax = 100; // HP default
						psPacket[i].iID = 8100; // Default ID
						psPacket[i].sPosition.iX *= 256; // X << 8
						psPacket[i].sPosition.iY *= 256; // Y << 8
						psPacket[i].sPosition.iZ *= 256; // Z << 8
						pcDB->Fetch();
					}
				}
			}
			pcDB->Close();
		}
	}

	// Next Stage
	m_uCurrentStageUnitStand++;
}
void CServerMap::ReadUnitEnemyStage(SpawnSetting * pMonsterStageList)
{
	if (!GAME_SERVER)
		return;

	pMonsterStageList->iSpawnIntervalMin = 127;
	pMonsterStageList->iSpawnMonsters = 3;

	int iCount = 0;

	const int iEnemyCountStage = 12; // Total Enemy in Stage
	const int iBossCountStage = 3;   // Total Boss in Stage

	// Get Count Data in SQL
	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_GameDB);

	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT COUNT(Stage) FROM MapMonster WHERE Stage=?"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_Integer, &m_uCurrentStageUnitEnemy);
			if (pcDB->Execute() && pcDB->Fetch())
			{
				pcDB->GetData(1, PARAMTYPE_Integer, &iCount, 0);
			}
		}
		pcDB->Close();
	}

	// Is Data?
	if (iCount != 0)
	{
		// Get Enemies in Stage
		if (pcDB->Open())
		{
			if (pcDB->Prepare("SELECT * FROM MapMonster WHERE Stage=?"))
			{
				pcDB->BindParameterInput(1, PARAMTYPE_Integer, &m_uCurrentStageUnitEnemy);
				if (pcDB->Execute() && pcDB->Fetch())
				{

					// Stage Enemy Settings
					{
						pcDB->GetData(3, PARAMTYPE_Integer, &pMonsterStageList->iSpawnMaxMonsters, 0);
						pcDB->GetData(4, PARAMTYPE_Integer, &pMonsterStageList->iSpawnIntervalMax, 0);
						pcDB->GetData(5, PARAMTYPE_Integer, &pMonsterStageList->iSpawnMonsters, 0);
						pMonsterStageList->iSpawnIntervalMax *= 1000;
						pMonsterStageList->iSpawnIntervalMin = 1 << 5;
					}

					// Get Enemy data
					for (int i = 0; i < iEnemyCountStage; i++)
					{
						char szEnemyName[32] = { 0 };
						pcDB->GetData(6 + (i * 2), PARAMTYPE_String, szEnemyName, 32);

						// Is enemy?
						if (!IsNull(szEnemyName))
						{
							CharacterData * pEnemyInfo = SERVERUNIT->GetCharacterDataByName(szEnemyName);

							// Is Enemy in Data?
							if (pEnemyInfo)
							{
								STRINGCOPY(pMonsterStageList->saMonster[pMonsterStageList->iTotalMonsters].szMonsterName, szEnemyName);
								pMonsterStageList->saMonster[pMonsterStageList->iTotalMonsters].psCharacter = pEnemyInfo;
								pcDB->GetData(6 + (i * 2) + 1, PARAMTYPE_Integer, &pMonsterStageList->saMonster[pMonsterStageList->iTotalMonsters].iSpawnRate, 0);
								pMonsterStageList->saMonster[pMonsterStageList->iTotalMonsters].iSpawnRateCum = pMonsterStageList->iTotalMonsterSpawnRate;
								pMonsterStageList->iTotalMonsterSpawnRate += pMonsterStageList->saMonster[pMonsterStageList->iTotalMonsters].iSpawnRate;
								pMonsterStageList->iTotalMonsters++;
							}
						}
					}

					// Get Boss data
					std::vector<std::string> vTimeBoss;
					for (int i = 0; i < iBossCountStage; i++)
					{
						char szBossName[32] = { 0 };
						pcDB->GetData(30 + (i * 4), PARAMTYPE_String, szBossName, 32);

						// Is Boss?
						if (!IsNull(szBossName))
						{
							CharacterData * pBossInfo = SERVERUNIT->GetCharacterDataByName(szBossName);

							// Is Boss in Data?
							if (pBossInfo)
							{
								char szTimeBoss[128] = { 0 };
								pcDB->GetData(30 + (i * 4) + 1, PARAMTYPE_String, szTimeBoss, 128);
								vTimeBoss = split(szTimeBoss, ' ');

								pMonsterStageList->saBoss[pMonsterStageList->iTotalBosses].pcdBoss = pBossInfo;

								for (UINT u = 0; u < vTimeBoss.size(); u++)
								{
									pMonsterStageList->saBoss[pMonsterStageList->iTotalBosses].caBossHour[u] = (char)atoi(vTimeBoss[u].c_str());
									pMonsterStageList->saBoss[pMonsterStageList->iTotalBosses].iBossHours++;
								}

								// Minion Boss
								char szMinionBoss[32] = { 0 };
								int iMinionCount = 0;
								pcDB->GetData(30 + (i * 4) + 2, PARAMTYPE_String, szMinionBoss, 32);
								pcDB->GetData(30 + (i * 4) + 3, PARAMTYPE_Integer, &iMinionCount, 32);

								// Is Minion Boss?
								if (!IsNull(szMinionBoss))
								{
									CharacterData * pMinionBossInfo = SERVERUNIT->GetCharacterDataByName(szMinionBoss);

									// Is Minion Boss in Data?
									if (pMinionBossInfo)
									{
										pMonsterStageList->saBoss[pMonsterStageList->iTotalBosses].pcdMinion = pMinionBossInfo;
										pMonsterStageList->saBoss[pMonsterStageList->iTotalBosses].iMinions  = iMinionCount;
									}
								}
								pMonsterStageList->iTotalBosses++;
							}
						}
					}
				}
			}
			pcDB->Close();
		}
	}

	m_uCurrentStageUnitEnemy++;
}
BOOL CServerMap::SpawnCrystal(EItemID iItemID, int iX, int iY, int iZ, User * pcUser)
{
	struct CrystalData
	{
		EItemID			iItemID;

		int				iChance; //0~99%

		int				iTime;

		char			* pszName;
	};

	static const CrystalData saNormalData[] =
	{
		{ ITEMID_HopyCrystal, 20, 5, "Hopy_Crystal" },
		{ ITEMID_HobgoblinCrystal, 18, 5, "Hobgoblin_Crystal" },
		{ ITEMID_DecoyCrystal, 16, 5, "Decoy_Crystal" },
		{ ITEMID_BargonCrystal, 14, 5, "Bargon_Crystal" },
		{ ITEMID_HeadCutterCrystal, 12, 5, "Head Cutter_Crystal" },
		{ ITEMID_FigonCrystal, 10, 5, "Figon_Crystal" },
		{ ITEMID_KingHopyCrystal, 8, 5, "King Hopy_Crystal" },
		{ ITEMID_HulkCrystal, 2, 5, "Hulk_Crystal" },
		{ ITEMID_GuardianSaintCrystal, 0, 5, "Guardian Saint_Crystal" },
		{ ITEMID_WebCrystal, 0, 5, "Web_Crystal" },
		{ ITEMID_DarkSpecterCrystal, 0, 5, "Dark Specter_Crystal" },
		{ ITEMID_IronGuardCrystal, 0, 5, "Iron Guard_Crystal" },
		{ ITEMID_RicartenMilitiaGuardCrystal, 0, 5, "Ricarten Militia" },
		{ ITEMID_RicartenGuardCrystal, 0, 5, "Ricarten Guard" },
		{ ITEMID_RoyalBlessGuardCrystal, 0, 5, "Royal Bless Guard" },
	};

	static const CrystalData saDuskCrystalData[] =
	{
		{ ITEMID_HopyCrystal, 20, 7, "Typhoon_Crystal" },
		{ ITEMID_HobgoblinCrystal, 18, 7, "Grotesque_Crystal" },
		{ ITEMID_DecoyCrystal, 16, 7, "Stygian_Crystal" },
		{ ITEMID_BargonCrystal, 14, 7, "Dark Specter_Crystal" },
	};

	static const CrystalData saDoomedCrystalData[] =
	{
		{ ITEMID_HopyCrystal, 20, 8, "Dark Phalanx_Crystal" },
		{ ITEMID_HobgoblinCrystal, 18, 8, "King Spider_Crystal" },
		{ ITEMID_DecoyCrystal, 16, 8, "Seto_Crystal" },
		{ ITEMID_BargonCrystal, 14, 8, "Hell Hound_Crystal" },
	};

	static const CrystalData saOccultCrystalData[] =
	{
		{ ITEMID_HopyCrystal, 20, 9, "Atalanta Spirit_Crystal" },
		{ ITEMID_HobgoblinCrystal, 18, 9, "Archer Spirit_Crystal" },
		{ ITEMID_DecoyCrystal, 16, 9, "Pikeman Spirit_Crystal" },
		{ ITEMID_BargonCrystal, 14, 9, "Mechanician Spirit_Crystal" },
	};

	static const CrystalData saArticCrystalData[] =
	{
		{ ITEMID_HopyCrystal, 20, 10, "Undead Miner_Crystal" },
		{ ITEMID_HobgoblinCrystal, 18, 10, "Tarantulika_Crystal" },
		{ ITEMID_DecoyCrystal, 16, 10, "Mine Bat_Crystal" },
		{ ITEMID_BargonCrystal, 14, 10, "Ice Serpent_Crystal" },
	};

	static const CrystalData saAbysmalCrystalData[] =
	{
		{ ITEMID_HopyCrystal, 20, 10, "Dey_Crystal" },
		{ ITEMID_HobgoblinCrystal, 18, 10, "Koon_Crystal" },
		{ ITEMID_DecoyCrystal, 16, 10, "Sathla_Crystal" },
	};

	static const CrystalData saBossData[] =
	{
		{ ITEMID_HopyCrystal, 20, 5, "Zzangpy_Crystal" },
		{ ITEMID_HobgoblinCrystal, 18, 5, "Wild Goblin_Crystal" },
		{ ITEMID_DecoyCrystal, 16, 5, "Maximum Decoy_Crystal" },
		{ ITEMID_BargonCrystal, 14, 5, "Bauton_Crystal" },
		{ ITEMID_HeadCutterCrystal, 12, 5, "Vega Demir_Crystal" },
		{ ITEMID_FigonCrystal, 10, 5, "HellSing_Crystal" },
		{ ITEMID_KingHopyCrystal, 8, 5, "Horropion_Crystal" },
		{ ITEMID_HulkCrystal, 2, 5, "Typhoon_Crystal" },
		{ ITEMID_GuardianSaintCrystal, 0, 5, "Guardian King_Crystal" },
		{ ITEMID_WebCrystal, 0, 5, "Cursed Web_Crystal" },
		{ ITEMID_DarkSpecterCrystal, 0, 5, "Dark Phantom_Crystal" },
		{ ITEMID_IronGuardCrystal, 0, 5, "Imitir Guard_Crystal" },
		{ ITEMID_RicartenMilitiaGuardCrystal, 0, 5, "Ricarten Militia" },
		{ ITEMID_RicartenGuardCrystal, 0, 5, "Ricarten Guard" },
		{ ITEMID_RoyalBlessGuardCrystal, 0, 5, "Royal Bless Guard" },
	};

	BOOL bBossCrystal = rsCristalEvent;
	BOOL bBlessCastleCrystal = FALSE;

	const CrystalData * psCrystal = NULL;

	const CrystalData * psaCrystals = saNormalData;
	int iCount = _countof(saNormalData);

	if (bBossCrystal)
	{
		psaCrystals = saBossData;
		iCount = _countof(saBossData);
	}
	if (iItemID == ITEMID_DuskyCrystal)
	{
		psaCrystals = saDuskCrystalData;
		iCount = _countof(saDuskCrystalData);
	}
	else if (iItemID == ITEMID_DoomedCrystal)
	{
		psaCrystals = saDoomedCrystalData;
		iCount = _countof(saDoomedCrystalData);
	}
	else if (iItemID == ITEMID_OccultCrystal)
	{
		psaCrystals = saOccultCrystalData;
		iCount = _countof(saOccultCrystalData);
	}
	else if (iItemID == ITEMID_ArcticCrystal)
	{
		psaCrystals = saArticCrystalData;
		iCount = _countof(saArticCrystalData);
	}
	else if (iItemID == ITEMID_AbysmalCrystal)
	{
		psaCrystals = saAbysmalCrystalData;
		iCount = _countof(saAbysmalCrystalData);
	}

	//Mystic Crystal
	if (iItemID == ITEMID_MysticCrystal ||
		iItemID == ITEMID_DuskyCrystal ||
		iItemID == ITEMID_DoomedCrystal ||
		iItemID == ITEMID_OccultCrystal ||
		iItemID == ITEMID_ArcticCrystal ||
		iItemID == ITEMID_AbysmalCrystal)
	{
		int iRandom = RandomI(0, 100);

		int iRandomCount = 0;

		for (int i = 0; i < iCount; i++)
		{
			iRandomCount += psaCrystals[i].iChance;

			if (iRandom < iRandomCount)
			{
				psCrystal = psaCrystals + i;
				break;
			}
		}

		if (psCrystal == NULL)
			psCrystal = &psaCrystals[0];
	}

	//Normal Crystal
	if (psCrystal == NULL)
	{
		for (int i = 0; i < iCount; i++)
		{
			if (psaCrystals[i].iItemID == iItemID)
			{
				psCrystal = psaCrystals + i;
				break;
			}
		}
	}

	if (psCrystal != NULL)
	{
		auto * pcMap = GetMapByXZ(iX, iZ);

		if (pcMap)
		{
			if (pcMap->pcBaseMap->iMapType == MAPTYPE_Town)
				return FALSE;

			//Bless Castle Crystal?
			if ((psCrystal->iItemID == ITEMID_RicartenGuardCrystal) ||
				(psCrystal->iItemID == ITEMID_RicartenMilitiaGuardCrystal) ||
				(psCrystal->iItemID == ITEMID_RoyalBlessGuardCrystal))
			{
				BlessCastleStatusData * psBC = SERVERBLESSCASTLE->GetBlessCastleStatusData();

				if (!psBC->iCastleMode || !pcUser->iClanID ||
					pcUser->iClanID != psBC->iClanID ||
					pcUser->iMapID != MAPID_BlessCastle)
				{
					SERVERCHAT->SendChat(pcUser, CHATCOLOR_Error, "You can't summon a Bless Castle guard now!");

					return FALSE;
				}

				int iaBCGuard[3] = { 0,0,0 };
				int iClanMonster = 0;
				int iSelfMonster = 0;

				for (int i = 0; i < MAX_ALIVEMONSTERS; i++)
				{
					Unit * pcUnit = pcMap->pcaUnitData[i];

					if (pcUnit && pcUnit->iClanID == pcUser->iClanID)
					{
						iClanMonster++;

						if (pcUnit->sCharacterData.iOwnerID == pcUser->iID)
							iSelfMonster++;

						switch (pcUnit->sCharacterData.iMonsterEffectID)
						{
						case MONSTEREFFECTID_CASTLE_SOLDER_A:
							iaBCGuard[0]++;
							break;
						case MONSTEREFFECTID_CASTLE_SOLDER_B:
							iaBCGuard[1]++;
							break;
						case MONSTEREFFECTID_CASTLE_SOLDER_C:
							iaBCGuard[2]++;
							break;
						}
					}
				}

				int iBlessCrystalID = 0;

				if (iItemID == ITEMID_RicartenMilitiaGuardCrystal)
					iBlessCrystalID = 0;
				else if (iItemID == ITEMID_RicartenGuardCrystal)
					iBlessCrystalID = 1;
				else if (iItemID == ITEMID_RoyalBlessGuardCrystal)
					iBlessCrystalID = 2;

				if (iClanMonster >= 20 || iSelfMonster >= 1 || iaBCGuard[iBlessCrystalID] >= 5)
				{
					SERVERCHAT->SendChat(pcUser, CHATCOLOR_Error, "You can't summon a Bless Castle guard now!");

					return FALSE;
				}

				bBlessCastleCrystal = TRUE;
			}

			Point3D sNewPosition(0, 0, 0);

			int iPos = 0;
			int iHeight = 0;

			for (int i = 0; i < 8; i++)
			{
				int j = RandomI(0, 8);

				sNewPosition = Point3D(iX, iY, iZ) + (sPositionList[j & 7] << 8);

				j++;

				iHeight = pcMap->pcStage->GetFloorHeight(sNewPosition.iX, sNewPosition.iY, sNewPosition.iZ, 0x2000);

				if (iHeight != CLIP_OUT)
				{
					if (abs(iHeight - sNewPosition.iY) < 0x2000)
						break;
				}

				iPos++;
			}

			if (iPos < 8)
			{
				iX = sNewPosition.iX;
				iY = iHeight;
				iZ = sNewPosition.iZ;
			}

			Unit * pcUnit = SERVERUNIT->CreateUnitEnemy(psCrystal->pszName, iX, iY, iZ, pcUser);

			if (pcUnit)
			{
				int iLengthName = STRLEN(pcUnit->sCharacterData.szName);
				int iLength = STRLEN("_Crystal");

				ZeroMemory(&pcUnit->sCharacterData.szName[iLengthName - iLength], iLength);

				STRINGCOPY(pcUnit->sCharacterData.Pet.szOwnerName, SERVERCHARACTER->GetCharacterName(pcUser));

				pcUnit->sUnitInfo.dwHashCharacterName = 0;
				pcUnit->sCharacterData.iMonsterType = MONSTERTYPE_Friendly;
				pcUnit->sCharacterData.iOwnerID = pcUser->iID;

				pcUnit->pcOwner = pcUser;
				pcUnit->dwLastUpdateTime = TICKCOUNT + (psCrystal->iTime * 60 * 1000);

				int iPet = pcUser->UseMonsterNum % 10;

				pcUser->lpLinkChar[iPet] = pcUnit;
				pcUser->dwLinkCharCode[iPet] = pcUnit->iID;

				pcUser->UseMonsterNum++;

				SERVERITEM->OnUseCrystal(pcUser, pcUnit, iItemID);

				SERVERUNIT->ProcessPacketEffectWarp(pcUser, Point3D(iX, iY, iZ));

				return TRUE;
			}
		}
	}

	return FALSE;
}
Unit * CServerMap::CreateUnitByID(ESkillPlayID iID, int iX, int iY, int iZ, User * pcUser, Unit * pcUnitEnemy)
{
	char szName[64] = { 0 };

	if (pcUnitEnemy)
	{
		if (pcUnitEnemy->sCharacterData.iMonsterEffectID == MONSTEREFFECTID_NPC_SKILLMASTER)
		{
			if (iID == SKILLPLAYID_T44)
			{
				STRINGCOPY(szName, "Metal Golem");
			}
			else if (iID == SKILLPLAYID_T41)
			{
				STRINGCOPY(szName, "Wolverine");
			}
		}
		else if (pcUnitEnemy->sCharacterData.iMonsterEffectID == MONSTEREFFECTID_NPC_MAGICMASTER)
		{
			if (iID == SKILLPLAYID_T41)
			{
				STRINGCOPY(szName, "Fire Elemental");
			}
		}
	}
	else
	{
		if (pcUser->sCharacterData.iClass == CHARACTERCLASS_Mechanician && iID == SKILLPLAYID_T44)
		{
			STRINGCOPY(szName, "Metal Golem");
		}
		else if (pcUser->sCharacterData.iClass == CHARACTERCLASS_Archer && iID == SKILLPLAYID_T41)
		{
			STRINGCOPY(szName, "Wolverine");
		}
		else if (pcUser->sCharacterData.iClass == CHARACTERCLASS_Atalanta && iID == SKILLPLAYID_T53)
		{
			//lpCristalMonster = &srSkillMonster[2];
		}
		else if (pcUser->sCharacterData.iClass == CHARACTERCLASS_Magician && iID == SKILLPLAYID_T41)
		{
			STRINGCOPY(szName, "Fire Elemental");
		}
		else if (pcUser->sCharacterData.iClass == CHARACTERCLASS_Shaman && iID == SKILLPLAYID_T41)
		{
			STRINGCOPY(szName, "Hestian");
		}
	}

	if (pcUser)
	{
		for (int i = 0; i < UNITS_MAX; i++)
		{
			Unit * pcUnit = UNITSDATA + i;

			if (pcUnit->bActive && pcUnit->pcOwner == pcUser && pcUnit->iPetID == iID && pcUnit->sCharacterData.sHP.sMin > 0)
			{
				pcUnit->sCharacterData.sHP.sMin = 0;
				pcUnit->iPetID = 0;
				pcUnit->SetMotionFromCode(ANIMATIONTYPE_Die);
			}
		}
	}

	Map * pcMap = SERVERMAP->GetMapByXZ(iX, iZ);

	if (pcMap && szName[0])
	{
		if (pcMap->pcBaseMap->iMapType == MAPTYPE_Town)
			return NULL;

		Point3D sNewPosition(0, 0, 0);

		int iPos = 0;
		int iHeight = 0;

		for (int i = 0; i < 8; i++)
		{
			int j = RandomI(0, 8);

			sNewPosition = Point3D(iX, iY, iZ) + (sPositionList[j & 7] << 8);

			j++;

			iHeight = pcMap->pcStage->GetFloorHeight(sNewPosition.iX, sNewPosition.iY, sNewPosition.iZ, 0x2000);

			if (iHeight != CLIP_OUT)
			{
				if (abs(iHeight - sNewPosition.iY) < 0x2000)
					break;
			}

			iPos++;
		}

		if (iPos < 8)
		{
			iX = sNewPosition.iX;
			iY = iHeight;
			iZ = sNewPosition.iZ;
		}

		Unit * pcUnit = SERVERUNIT->CreateUnitEnemy(szName, iX, iY, iZ, pcUser);

		if (pcUnit)
		{
			pcUnit->sPosition = Point3D(iX, iY, iZ);
			pcUnit->iLureDistance = 0;
			pcUnit->SetMotionFromCode(ANIMATIONTYPE_Idle);
			pcUnit->TargetMoveCount = 0;

			SERVERUNIT->ProcessPacketEffectWarp(pcUser, pcUnit->sPosition);

			if (pcUser && !pcUnitEnemy)
			{
				pcUnit->pcOwner = pcUser;
				pcUnit->sUnitInfo.dwHashCharacterName = 0;
				pcUnit->iPetID = iID;
				pcUnit->bAggressive = TRUE;
				pcUnit->sCharacterData.iMonsterType = MONSTERTYPE_Friendly;
				STRINGCOPY(pcUnit->sCharacterData.Pet.szOwnerName, pcUser->sCharacterData.szName);
				pcUnit->sCharacterData.iOwnerID = pcUser->iID;
				pcUnit->dwLastUpdateTime = SERVER_GAMETIME + 4 * 60 * 1000;

				int iPet = pcUser->UseMonsterNum % 10;

				pcUser->lpLinkChar[iPet] = pcUnit;
				pcUser->dwLinkCharCode[iPet] = pcUnit->iID;
				pcUser->UseMonsterNum++;

				pcUnit->bBlessCastleCrown = TRUE;
			}
			if (pcUnitEnemy && pcUnitEnemy->lpLinkPlayInfo)
			{
				pcUnit->lpLinkPlayInfo = pcUnitEnemy->lpLinkPlayInfo;
				pcUnit->lExclusiveTargetID = pcUnitEnemy->lExclusiveTargetID;
				pcUnit->pcExclusiveUnitTarget = pcUnitEnemy;
				pcUnit->dwLastUpdateTime = SERVER_GAMETIME + 5 * 60 * 1000;
			}

			return pcUnit;
		}
	}

	return NULL;
}
BOOL CServerMap::HandleUnitQuestMap(Map * pcMap, Unit * pcUnit)
{
	if (!pcUnit->sUnitInfo.eSpecialType || !pcMap)
		return FALSE;

	if (pcUnit->sUnitInfo.eSpecialType == SPECIALUNITTYPE_QuestWolverine && !SERVERMAP->IsNight())
		return FALSE;

	auto pMonstTable = SERVERUNIT->GetMonsterTable();

	for (auto & psCharacterData : pMonstTable)
	{
		if (psCharacterData->psUnitInfo->eSpecialType == pcUnit->sUnitInfo.eSpecialType &&
			psCharacterData->psUnitInfo->EventInfo == pcUnit->sUnitInfo.EventInfo &&
			STRINGCOMPARE(psCharacterData->szName, pcUnit->sCharacterData.szName))
		{
			pcMap->bForceCreateMonster = TRUE;
			CreateUnit(pcMap, psCharacterData);
			return TRUE;
		}
	}

	return FALSE;
}
void CServerMap::HandlePacket(User * pcUser, PacketBossTimeUpdate * psPacket)
{
	if ((psPacket->iMapID >= 0) && (psPacket->iMapID < (int)m_vpMap.size()))
	{
		UpdateUserBossTime(pcUser, psPacket->iMapID);
	}
}
void CServerMap::UpdateUserBossTime(User * pcUser, int iMapID)
{
	if ((iMapID >= 0) && (iMapID < (int)m_vpMap.size()))
	{
		Map * pcMap = GetMap((EMapID)iMapID);

		if (pcMap)
		{
			SYSTEMTIME sBossTime;
			CopyMemory(&sBossTime, SERVERINFO->GetServerTime(), sizeof(SYSTEMTIME));

			DWORD dwLessTimeBoss = 0;
			char * pszBossName = NULL;

			//Get Boss Time
			for (int i = 0; i < pcMap->sSpawnSetting.iTotalBosses; i++)
			{
				for (int j = 0; j < pcMap->sSpawnSetting.saBoss[i].iBossHours; j++)
				{
					//Get Boss Time
					sBossTime.wHour = pcMap->sSpawnSetting.saBoss[i].caBossHour[j];
					sBossTime.wMinute = m_iBossTime;
					sBossTime.wSecond = 0;

					//After the Time?
					if (sBossTime.wMinute >= SERVERINFO->GetServerTime()->wMinute)
					{
						//If Boss was spawned at the current boss time on loop, go to the next day...
						if (sBossTime.wHour < SERVERINFO->GetServerTime()->wHour)
							sBossTime.wDay++;
					}

					DWORD dwBossTime = SystemTimeToDWORD(&sBossTime);
					DWORD dwServerTime = SystemTimeToDWORD(SERVERINFO->GetServerTime());
					if (dwBossTime >= dwServerTime)
					{
						DWORD dwDifference = dwBossTime - dwServerTime;
						if ((dwLessTimeBoss > dwDifference) || (dwLessTimeBoss == 0))
						{
							pszBossName = pcMap->sSpawnSetting.saBoss[i].pcdBoss->szName;
							dwLessTimeBoss = dwDifference;
						}
					}

					//Backup Time
					CopyMemory(&sBossTime, SERVERINFO->GetServerTime(), sizeof(SYSTEMTIME));
				}
			}

			PacketBossTimeUpdate sPacket;
			ZeroMemory(&sPacket, sizeof(PacketBossTimeUpdate));
			sPacket.iLength = sizeof(PacketBossTimeUpdate);
			sPacket.iHeader = PKTHDR_BossTimeUpdate;

			if (pszBossName)
			{
				STRINGCOPY(sPacket.szBossName, pszBossName);
				sPacket.dwTime = dwLessTimeBoss;
			}

			SENDPACKET(pcUser, &sPacket);
		}
	}
}
void CServerMap::UpdateUsersBossTime()
{
	//Update Users about Boss Time
	UINT uUsersInGame = SERVERUSER->uUsersInGame;
	User ** pcaUserInGame = SERVERUSER->pcaUserInGame;
	for (UINT i = 0; i < uUsersInGame; i++)
	{
		User * pcUser = pcaUserInGame[i];
		UpdateUserBossTime(pcUser, pcUser->GetMapID());
	}
}
void CServerMap::OnSendDebugDamage(User * pcUser, PacketDebugDamageInfo * psPacket)
{
	if (pcUser)
	{
		psPacket->dwObjectID = pcUser->iID;

		for (int i = 0; i < PLAYERS_MAX; i++)
		{
			User * pc = USERSDATA + i;

			if (pc->pcSocketData && pc != pcUser && pc->iMapID == pcUser->iMapID)
			{
				int iX = (pcUser->sPosition.iX - pc->sPosition.iX) >> 8;
				int iY = (pcUser->sPosition.iY - pc->sPosition.iY) >> 8;
				int iZ = (pcUser->sPosition.iZ - pc->sPosition.iZ) >> 8;
				int iXZ = abs((iX * iX) - (iZ * iZ));

				if (iXZ <= 90000 && iY <= 80)
					SENDPACKET(pc, psPacket);
			}
		}
	}
}
void CServerMap::OnSendDebugDamageUnit(Unit * pcUnit, int iDamage, EDamageInfo eTypeAction)
{
	if (pcUnit && pcUnit->sCharacterData.iType != 0 && iDamage > 0)
	{
		PacketDebugDamageInfo sPacket;
		sPacket.iLength = sizeof(PacketDebugDamageInfo);
		sPacket.iHeader = PKTHDR_DamageDebugInfo;
		sPacket.dwObjectID = pcUnit->iID;
		sPacket.iTypeAction = eTypeAction;
		sPacket.iValue = iDamage;

		for (int i = 0; i < PLAYERS_MAX; i++)
		{
			User * pc = USERSDATA + i;

			if (pc->pcSocketData)
			{
				int iX = (pcUnit->sPosition.iX - pc->sPosition.iX) >> 8;
				int iY = (pcUnit->sPosition.iY - pc->sPosition.iY) >> 8;
				int iZ = (pcUnit->sPosition.iZ - pc->sPosition.iZ) >> 8;
				int iXZ = abs((iX * iX) - (iZ * iZ));
				if (iXZ <= 90000 && iY <= 80)
					SENDPACKET(pc, &sPacket);
			}
		}
	}
}