#include "StdAfx.h"
#include "ServerUnit.h"
#include "SrcServer/onserver.h"

CServerUnit::CServerUnit()
{
	
}
CServerUnit::~CServerUnit()
{
	
}
void CServerUnit::Init()
{
	if (!GAME_SERVER)
		return;

	LoadUnit();
	LoadUnitEnemyData();
}
void CServerUnit::Shutdown()
{
	for (auto &v : m_vMonsterTable)
	{
		auto p = v->psUnitInfo;

		DELET(p);
		DELET(v);
	}

	m_vMonsterTable.clear();

	DELETA(pcaUnitInGame);
	DELETA(pcaUnit);
}
void CServerUnit::LoadUnitEnemyData()
{
	int iCount = 0;

	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_GameDB);

	// Get Total Monsters
	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT COUNT(*) FROM MonsterList"))
		{
			if (pcDB->Execute() && pcDB->Fetch())
			{
				pcDB->GetData(1, PARAMTYPE_Integer, &iCount, 0);
			}
		}
		pcDB->Close();
	}

	// Select Data Monster
	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT * FROM MonsterList"))
		{
			if (pcDB->Execute() && pcDB->Fetch())
			{
				for (int i = 0; i < iCount; i++)
				{
					CharacterData * paCharacterData = new CharacterData;
					UnitInfo * paUnitInfo = new UnitInfo;

					ZeroMemory(paCharacterData, sizeof(CharacterData));
					ZeroMemory(paUnitInfo, sizeof(UnitInfo));

					// ID
					int iEnemyID = 0;
					pcDB->GetData(1, PARAMTYPE_Integer, &iEnemyID, 0);

					// Name
					pcDB->GetData(2, PARAMTYPE_String, paCharacterData->szName, 32);
					STRINGCOPY(paUnitInfo->szName, paCharacterData->szName);

					// Model
					pcDB->GetData(3, PARAMTYPE_String, paCharacterData->Player.szBodyModel, 64);

					// State
					paCharacterData->iType = CHARACTERTYPE_Monster;

					// Level
					pcDB->GetData(4, PARAMTYPE_Integer, &paCharacterData->iLevel, 0);

					// Glow
					pcDB->GetData(5, PARAMTYPE_Short, &paCharacterData->sGlow, 0);

					// Size
					float fSize = 0.0f;
					pcDB->GetData(6, PARAMTYPE_Float, &fSize, 0);
					paCharacterData->sSize = (short)(fSize * 256.0f);

					// Camera Y
					pcDB->GetData(7, PARAMTYPE_Short, &paCharacterData->sViewBoxZoom.sMin, 0);
					// Camera Z
					pcDB->GetData(8, PARAMTYPE_Short, &paCharacterData->sViewBoxZoom.sMax, 0);

					// pcUnitData ID
					pcDB->GetData(9, PARAMTYPE_Integer, &paUnitInfo->ClassCode, 0);

					// Spawn Time
					pcDB->GetData(10, PARAMTYPE_Integer, &paUnitInfo->iActiveHour, 0);

					// Spawn pcUnitData Min
					pcDB->GetData(11, PARAMTYPE_Integer, &paUnitInfo->iGroupLimitMin, 0);

					// Spawn pcUnitData Max
					pcDB->GetData(12, PARAMTYPE_Integer, &paUnitInfo->iGroupLimitMax, 0);

					// IQ
					pcDB->GetData(13, PARAMTYPE_Integer, &paUnitInfo->IQ, 0);

					// Nature
					char szNatureName[32] = { 0 };
					pcDB->GetData(14, PARAMTYPE_String, szNatureName, 32);
					{
						paUnitInfo->iNature = MONSTERNATURE_Neutral;

						if (STRINGCOMPAREI(szNatureName, "good"))
							paUnitInfo->iNature = MONSTERNATURE_Good;
						else if (STRINGCOMPAREI(szNatureName, "evil"))
							paUnitInfo->iNature = MONSTERNATURE_Evil;
					}

					// View Sight
					pcDB->GetData(15, PARAMTYPE_Integer, &paUnitInfo->iSight, 0);
					paCharacterData->iSight = paUnitInfo->iSight;
					paCharacterData->iSight *= paCharacterData->iSight;

					// HP
					pcDB->GetData(16, PARAMTYPE_Short, &paCharacterData->sHP.sMin, 0);
					paCharacterData->sHP.sMax = paCharacterData->sHP.sMin;

					// EXP
					INT64 iExp = 0;
					pcDB->GetData(17, PARAMTYPE_Int64, &iExp, 0);

					int iRateExp = SERVERINFO->GetEvent()->iRate_Exp;

					if (iRateExp > 0)
						iExp = iExp * iRateExp;

					paUnitInfo->iExp = (int)iExp;

					paCharacterData->iExp = iExp;

					// Special Skill Curse
					pcDB->GetData(18, PARAMTYPE_Integer, &paUnitInfo->SkillCurse, 0);

					// Special Skill Distance
					pcDB->GetData(19, PARAMTYPE_Integer, &paUnitInfo->SkillDistance, 0);

					// Special Skill Rating
					pcDB->GetData(20, PARAMTYPE_Integer, &paUnitInfo->SkillRating, 0);

					// Special Skill Range
					pcDB->GetData(21, PARAMTYPE_Integer, &paUnitInfo->SkillRange, 0);

					// Special Skill Damage Min
					pcDB->GetData(22, PARAMTYPE_Short, &paUnitInfo->SkillDamage[0], 0);

					// Special Skill Damage Max
					pcDB->GetData(23, PARAMTYPE_Short, &paUnitInfo->SkillDamage[1], 0);

					// Damage Min
					pcDB->GetData(24, PARAMTYPE_Integer, &paCharacterData->iMinDamage, 0);

					// Damage Max
					pcDB->GetData(25, PARAMTYPE_Integer, &paCharacterData->iMaxDamage, 0);

					// Absorption
					pcDB->GetData(26, PARAMTYPE_Integer, &paCharacterData->iAbsorbRating, 0);

					// Stun Chance ( 0% ~ 100% )
					pcDB->GetData(27, PARAMTYPE_Integer, &paUnitInfo->DamageStunPers, 0);

					// Block
					pcDB->GetData(28, PARAMTYPE_Integer, &paCharacterData->iBlockRating, 0);

					// Defense
					pcDB->GetData(29, PARAMTYPE_Integer, &paCharacterData->iDefenseRating, 0);

					// Attack Speed
					pcDB->GetData(30, PARAMTYPE_Integer, &paCharacterData->iAttackSpeed, 0);
					paCharacterData->iAttackSpeed *= 256;

					// Attack Rating
					pcDB->GetData(31, PARAMTYPE_Integer, &paCharacterData->iAttackRating, 0);

					// Shooting Range
					pcDB->GetData(32, PARAMTYPE_Integer, &paCharacterData->iAttackRange, 0);
					paCharacterData->iAttackRange *= 256;

					// Attack Percent
					pcDB->GetData(33, PARAMTYPE_Integer, &paUnitInfo->SpAttackPercetage, 0);

					// Size Shadow
					pcDB->GetData(34, PARAMTYPE_Integer, &paCharacterData->iShadowSize, 0);

					// Organic
					pcDB->GetData(35, PARAMTYPE_Short, &paCharacterData->sElementalDef[ELEMENTID_Organic], 0);

					// Lightning
					pcDB->GetData(36, PARAMTYPE_Short, &paCharacterData->sElementalDef[ELEMENTID_Lighting], 0);

					// Ice
					pcDB->GetData(37, PARAMTYPE_Short, &paCharacterData->sElementalDef[ELEMENTID_Ice], 0);

					// Fire
					pcDB->GetData(38, PARAMTYPE_Short, &paCharacterData->sElementalDef[ELEMENTID_Fire], 0);

					// Poison
					pcDB->GetData(39, PARAMTYPE_Short, &paCharacterData->sElementalDef[ELEMENTID_Poison], 0);

					// Magic
					pcDB->GetData(40, PARAMTYPE_Short, &paCharacterData->sElementalDef[ELEMENTID_Wind], 0);

					// Property Monster
					char szPropertyName[32] = { 0 };
					pcDB->GetData(41, PARAMTYPE_String, szPropertyName, 32);
					{
						paCharacterData->iMonsterType = MONSTERTYPE_Normal;

						if (STRINGCOMPAREI(szPropertyName, "undead"))
							paCharacterData->iMonsterType = MONSTERTYPE_Undead;
						else if (STRINGCOMPAREI(szPropertyName, "mutant"))
							paCharacterData->iMonsterType = MONSTERTYPE_Mutant;
						else if (STRINGCOMPAREI(szPropertyName, "demon"))
							paCharacterData->iMonsterType = MONSTERTYPE_Demon;
						else if (STRINGCOMPAREI(szPropertyName, "machine"))
							paCharacterData->iMonsterType = MONSTERTYPE_Mechanic;
					}

					// Move Speed
					pcDB->GetData(42, PARAMTYPE_Integer, &paCharacterData->iMovementSpeed, 0);
					paCharacterData->iMovementSpeed = (int)(((float)paCharacterData->iMovementSpeed - 9) * 16) + 256;

					// Percent Potion
					pcDB->GetData(43, PARAMTYPE_Integer, &paUnitInfo->iPerPotions, 0);

					// Potion Count
					pcDB->GetData(44, PARAMTYPE_Integer, &paUnitInfo->iMaxPotions, 0);

					// Sound Effect
					char szEffectName[64] = { 0 };
					pcDB->GetData(45, PARAMTYPE_String, szEffectName, 64);
					paCharacterData->iMonsterEffectID = (EMonsterEffectID)GetEnemyEffect(szEffectName);

					// Quest Item
					char szQuestItem[10] = { 0 };
					pcDB->GetData(46, PARAMTYPE_String, szQuestItem, 10);
					ItemData * pItem = SERVERITEM->FindItemPointerTable(szQuestItem);
					if (pItem)
						paUnitInfo->iQuestItemID = pItem->sBaseItemID.ToItemID();

					// Quest ID
					pcDB->GetData(47, PARAMTYPE_Integer, &paUnitInfo->eSpecialType, 0);

					// Quest Map
					pcDB->GetData(48, PARAMTYPE_Integer, &paUnitInfo->EventInfo, 0);

					paCharacterData->psUnitInfo = (UnitInfo*)paUnitInfo;

					ReformCharForm(paCharacterData);

					m_vMonsterTable.push_back(paCharacterData);

					pcDB->Fetch();
				}
			}
		}

		pcDB->Close();
	}

	ReadDropItem();
}
void CServerUnit::LoadUnit()
{
	pcaUnitInGame = new Unit *[UNITS_MAX];
	pcaUnit = new Unit[UNITS_MAX];

	InitPatterns();

	for (int i = 0; i < UNITS_MAX; i++)
	{
		Unit * pcUnit = pcaUnit + i;

		ZeroMemory(pcUnit, sizeof(Unit));

		pcUnit->uIndex = i;

		pcUnit->Init();
		
	}
}
void CServerUnit::Update()
{
	if (!GAME_SERVER)
		return;

	static UINT iUnitWheel = 0;

	//Check if actiion wheel must be set
	if (iActiveWheel == 0)
	{
		if ((iUnitWheel % 64) == 0)
			iActiveWheel = 4;
	}
	else
		iActiveWheel--;

	uUnitsInGame = 0;

	for (int i = 0; i < UNITS_MAX; i++)
	{
		Unit *pcUnit = pcaUnit + i;

		if (pcaUnit->bActive)
		{
			pcaUnitInGame[uUnitsInGame++] = pcUnit;

			//Frame Check
			if ((i % 4) == (iUnitWheel % 4))
			{
				UpdateUnit(pcUnit);

				//Status Update?
				if (iActiveWheel != 0)
					pcUnit->uLastUpdate++;
			}
		}
	}

	iUnitWheel++;
}
void CServerUnit::UpdateUnit(Unit *pcUnit)
{
	m_pcUnit = pcUnit;

	if ((pcUnit->iAliveCounter != 0) ||
		(pcUnit->GetAnimation() == ANIMATIONTYPE_Die) ||
		(pcUnit->sUnitInfo.eSpecialType != SPECIALUNITTYPE_None))
	{
		//UpdateUnitData(pcUnit->pcUnitData);
		UpdateUnitData(pcUnit);
		pcUnit->iAliveCounter--;
	}
	else
	{
		if (pcUnit->sCharacterData.iType == CHARACTERTYPE_Monster)
		{
			pcUnit->iDeathCounter--;

			if (pcUnit->iDeathCounter <= 0)
			{
				pcUnit->Close();

				pcUnit->pcMap->iNumAliveUnitData--;

				SERVERMAP->DelMonsterSpawn(pcUnit->pcMap, pcUnit);
			}
		}
	}
}
BOOL CServerUnit::UpdateUnitData(Unit * pcUnit)
{
	//Cannot move? no Update...
	if (pcUnit->bLoading)
		return TRUE;

	pcUnit->Main();

	//Animated?
	if (pcUnit->psModelAnimation)
	{
		if (pcUnit->psModelAnimation->iType == ANIMATIONTYPE_Die)
		{
			//Handle Servers Update
			XMASHANDLE->OnSayTime(pcUnit);

			if (pcUnit->pcKillerData && pcUnit->iFrameTimer > 128 && !pcUnit->pcOwner)
			{
				User * u = pcUnit->pcKillerData;

				pcUnit->pcKillerData = NULL;

				//Have Last User Attack and not the same User?
				if (pcUnit->pcLastAttacker && pcUnit->pcLastAttacker != u)
				{
					if (pcUnit->iDamageLastAttacker >= ((pcUnit->sCharacterData.sHP.sMax * 40) / 100))
						u = pcUnit->pcLastAttacker;
				}

				//Quest Unit?
				if (pcUnit->sUnitInfo.iQuestItemID)
				{
					if (pcUnit->sUnitInfo.eSpecialType)
						SERVERMAP->HandleUnitQuestMap(pcUnit->pcMap, pcUnit);
				}

				//User Alive?
				if (u->pcSocketData && u->iID)
				{
					//Handle Kill
					HandleKill(pcUnit, u);

					//Increment Counter Unit Kills
					u->uUnitKillCounter++;
				}

				//Update Top10 Damage on Bosses
				if (pcUnit->psaDamageUsersData)
				{
					if (pcUnit->pcKillerData)
					{
						//QUESTARENAHANDLER->OnUnitKilled(pcUnit->pcKillerData, pcUnit, TRUE);
					}
					//Not Valhalla?
					if (pcUnit->sCharacterData.iMonsterEffectID != MONSTEREFFECTID_CASTLE_TOWER_B)
					{
						//Get Top10
						//UnitServer::GetTop10Damage(pcUnitData, pcUnitData->psaDamageUsersData);
						//SelectDamageTop10(pcUnit, &rsUserListDamageTop10);
					}
				}

				//Bellatra User and Unit?
				if (u->dwExclusiveNum == 0x100 && pcUnit->dwExclusiveNum == 0x100)
				{
					//Don't Have Killer of Bellatra?
					if (!pcUnit->pcBellatraKiller)
					{
						//Score
						LARGE_INTEGER lsScore;
						lsScore.QuadPart = pcUnit->sCharacterData.iExp / EVENT_BELLATRA_DIVSCORE;

						//Boss?
						if (pcUnit->sCharacterData.sGlow == TRUE)
						{
							//Notify Kill
							SERVERCHAT->SendChatEx(u, EChatColor::CHATCOLOR_Global, "Bellatra> %s killed!", pcUnit->sCharacterData.szName);
							SERVERCHAT->SendChatEx(u, EChatColor::CHATCOLOR_Global, "Bellatra> %s points", FormatNumber(lsScore.LowPart));
						}

						//Add Score
						u->iBellatraScore += lsScore.LowPart;
						u->iBellatraKills++;

						if (u->sBellatraRoomID >= 0 && u->sBellatraRoomID < 4)
							rsSodTeamScore[u->sBellatraRoomID] += lsScore.LowPart;

						//User Personal Kills
						/*{
							PacketSimple s;
							s.iLength = sizeof(PacketSimple);
							s.iHeader = PKTHDR_KillsInSod;
							s.iUnk = u->iBellatraKills;
							SENDPACKET(u, &s, TRUE);
						}*/

						rsShowHardCoreEventScore(u);

						rsOpen_SodItem(pcUnit, u);
					}
				}

				//Unit disappearing?
				if (pcUnit->iFrameTimer > 400)
				{
					//Is a Pet and User Owner Pet is Online?
					if (pcUnit->pcOwner && pcUnit->pcOwner->pcSocketData)
					{
						//Crystal Die
						SERVERITEM->OnUseCrystalDie(pcUnit->pcOwner, pcUnit);

						if (pcUnit->iPetID)
						{
							//Send Cancel Pet Skill
							PacketSimple s;

							ZeroMemory(&s, sizeof(PacketSimple));

							s.iLength = sizeof(PacketSimple);
							s.iHeader = PKTHDR_CancelSkill;
							s.iUnk = pcUnit->iID;
							s.iUnk2 = pcUnit->iPetID;
							SENDPACKET(pcUnit->pcOwner, &s, TRUE);
						}
					}

					Map * pcMap = pcUnit->pcMap;

					pcUnit->Close();

					pcMap->iNumAliveUnitData--;
					SERVERMAP->DelMonsterSpawn(pcMap, pcUnit);
					return TRUE;
				}
			}
		}

		//Unit Swapper
		OnUnitChanger(pcUnit);
	}

	if (pcUnit->AttackUserFlag)
	{
		pcUnit->AttackUserFlag = 0;

		if (pcUnit->pcFocusTarget)
			pcUnit->pcFocusTarget->HitMonsterCount = 0;
	}

	if (pcUnit->sCharacterData.sHP.sMin < 0)
		pcUnit->sCharacterData.sHP.sMin = 0;
	if (pcUnit->sCharacterData.sHP.sMin > pcUnit->sCharacterData.sHP.sMax)
		pcUnit->sCharacterData.sHP.sMin = pcUnit->sCharacterData.sHP.sMax;

	pcUnit->iDeathCounter = 256;

	if (iActiveWheel != 0)
	{
		pcUnit->HandleUnitDataBuffer((char *)pcUnit->baUnitBufferNew, 0x10, 4);

		int iX = pcUnit->sPosition.iX;
		int iY = pcUnit->sPosition.iY;
		int iZ = pcUnit->sPosition.iZ;

		int iDistanceMin = 0x00320000;

		Map * pcMap = pcUnit->pcMap;

		if (pcMap && pcUnit->pcOwner)
		{
			Unit * pcTarget = NULL;

			BOOL bCanAttack = FALSE;

			//Set Target for Pet
			for (int i = 0; i < pcMap->iNumUsingUnit; i++)
			{
				Unit * ps = pcMap->pcaUnitData[i];

				//Alive and not the same Unit?
				if (ps && ps != pcUnit && ps->sCharacterData.sHP.sMin > 0)
				{
					//Both is Pet?
					if (pcUnit->pcOwner && ps->pcOwner)
						continue;

					if (ps->sCharacterData.sGlow == 1 && pcUnit->psModelAnimation && ps->psModelAnimation &&
						pcUnit->psModelAnimation->iType != ANIMATIONTYPE_Die && ps->psModelAnimation->iType != ANIMATIONTYPE_Die)
					{
						//Relative Position
						int iX = (pcUnit->sPosition.iX - ps->sPosition.iX) >> 8;
						int iY = (pcUnit->sPosition.iY - ps->sPosition.iY) >> 8;
						int iZ = (pcUnit->sPosition.iZ - ps->sPosition.iZ) >> 8;

						//Calculate Distance
						int iDistance = (iX*iX) + (iY*iY) + (iZ*iZ);

						//Unit Near from Pet?
						if (iDistance < 0x4B000 && abs(iX) < (64 * 64) && abs(iZ) < (64 * 64))
						{
							int iEffectID = ps->sCharacterData.iMonsterEffectID;

							if (iEffectID != MONSTEREFFECTID_CASTLE_TOWER_B &&
								iEffectID != MONSTEREFFECTID_CASTLE_DOOR &&
								iEffectID != MONSTEREFFECTID_CASTLE_CRYSTAL_R &&
								iEffectID != MONSTEREFFECTID_CASTLE_CRYSTAL_G &&
								iEffectID != MONSTEREFFECTID_CASTLE_CRYSTAL_B &&
								iEffectID != MONSTEREFFECTID_CASTLE_CRYSTAL_N &&
								iEffectID != MONSTEREFFECTID_CASTLE_SOLDER_A &&
								iEffectID != MONSTEREFFECTID_CASTLE_SOLDER_B &&
								iEffectID != MONSTEREFFECTID_CASTLE_SOLDER_C)
							{

								//Kill
								pcUnit->sCharacterData.sHP.sMin = 0;
								pcUnit->SetMotionFromCode(ANIMATIONTYPE_Die);
								return TRUE;
							}
						}
					}

					if (pcUnit->iPetID && !pcUnit->bAggressive && pcUnit->pcOwner)
					{
						BOOL bContinue = FALSE;

						//User Owner Pet not targetting same Unit? go to the next Target
						if (pcUnit->pcOwner->pcLastAttack != ps)
							bContinue = TRUE;

						if (pcUnit->pcFocusingTarget)
						{
							if ((pcUnit->pcFocusingTarget == ps) && (ps->iID == pcUnit->iFocusingLastID))
								bContinue = FALSE;
						}

						if (bContinue)
							continue;
					}

					//Can Attack Unit
					bCanAttack = TRUE;

					//Unit is the same Clan Pet? then cannot Attack
					if (pcUnit->sCharacterData.iClanID && pcUnit->sCharacterData.iClanID == ps->sCharacterData.iClanID)
						bCanAttack = FALSE;

					//Check Unit Clan SW Master Type
					if (pcUnit->iPetID && pcUnit->bBlessCastleCrown && ps->bBlessCastleCrown)
					{
						//Pet? then cannot Attack
						if (ps->iPetID)
							bCanAttack = FALSE;

						//Unit Pet is not of User? then cannot Attack
						if (ps->lExclusiveTargetID && ps->lExclusiveTargetID != pcUnit->pcOwner->iID)
							bCanAttack = FALSE;
					}

					//SW Pet? then cannot Attack
					if (pcUnit->bBlessCastleCrown && ps->bBlessCastleCrown)
						bCanAttack = FALSE;

					//Unit Exclusive? then cannot Attack
					if (pcUnit == ps->pcExclusiveUnitTarget || pcUnit->pcExclusiveUnitTarget == ps)
						bCanAttack = FALSE;

					//Can Attack?
					if (bCanAttack)
					{
						//Priority to this Target
						if (pcUnit->pcFocusingTarget == ps)
						{
							if (ps->iID == pcUnit->iFocusingLastID)
							{
								pcTarget = pcUnit->pcFocusingTarget;
								break;
							}
							else
							{
								pcUnit->pcFocusingTarget = NULL;
								pcUnit->iFocusingLastID = -1;
							}
						}

						//Relative Position
						int iX = (pcUnit->sPosition.iX - ps->sPosition.iX) >> 8;
						int iY = (pcUnit->sPosition.iY - ps->sPosition.iY) >> 8;
						int iZ = (pcUnit->sPosition.iZ - ps->sPosition.iZ) >> 8;

						//Calculate Distance
						int iDistance = (iX*iX) + (iY*iY) + (iZ*iZ);

						//Unit Near from Pet?
						if (iDistance < DISTANCE_UNIT_FAR && abs(iX) < (64 * 64) && abs(iZ) < (64 * 64))
						{
							//Unit Near from Minimal Distance and Not bove or above from Pet?
							if (iDistance < iDistanceMin && abs(iY) < 140)
							{
								//Update Minimal Distance
								iDistanceMin = iDistance;

								//Pet can view Unit?
								if (iDistance < pcUnit->sCharacterData.iSight)
								{
									//Set Pet Target
									pcTarget = ps;
								}
							}
						}
					}
				}
			}

			//Update Target
			pcUnit->pcAttackTarget = pcTarget;

			//Have Unit Target?
			if (pcTarget)
			{
				//Update Position to Target Position
				pcUnit->SetNextTarget(pcTarget->sPosition.iX, pcTarget->sPosition.iY, pcTarget->sPosition.iZ);
			}

			//Time Alive is Over?
			if (pcUnit->dwLastUpdateTime && pcUnit->dwLastUpdateTime < SERVER_GAMETIME && pcUnit->sCharacterData.sHP.sMin > 0)
			{
				//Kill Unit
				pcUnit->sCharacterData.sHP.sMin = 0;
				pcUnit->SetMotionFromCode(ANIMATIONTYPE_Die);
			}
		}
		else
		{
			BOOL bNextTarget = FALSE;

			//Unit received Compulsion Skill?
			if (pcUnit->dwHookedTargetEndTime && (pcUnit->sCharacterData.sGlow == 0))
			{
				User * u = pcUnit->pcHookedTarget;

				//Compulsion Alive?
				if (pcUnit->dwHookedTargetEndTime > SERVER_GAMETIME && u && u->pcSocketData)
				{
					//Set Focus on User
					pcUnit->pcFocusTarget = u;

					//Update Position to Target Position
					pcUnit->SetNextTarget(u->sPosition.iX, u->sPosition.iY, u->sPosition.iZ);

					//Find Next Target
					bNextTarget = TRUE;
				}
				else
				{
					//Clear Compulsion Skill
					pcUnit->dwHookedTargetEndTime = 0;
					pcUnit->pcHookedTarget = NULL;
				}
			}

			//Next Target?
			if (!bNextTarget)
			{
				//Not Target?
				if (!pcUnit->pcAttackTarget)
				{
					//Find Users Near
					User * pcTarget = NULL;

					for (int i = 0; i < PLAYERS_MAX; i++)
					{
						User * u = USERSDATA + i;

						if (u->pcSocketData && u->iID && u->sCharacterData.sHP.sMin && u->sCharacterData.iType != 1 && u->bCloak == FALSE)
						{
							//Not Exlusive User? Next Target...
							if (pcUnit->lExclusiveTargetID && pcUnit->lExclusiveTargetID != u->iID)
								continue;

							//Unit is Pet Clan of User? Next Target...
							if (pcUnit->iClanID && pcUnit->iClanID == u->iClanID)
								continue;

							//Relative Position
							int iX = (pcUnit->sPosition.iX - u->sPosition.iX) >> 8;
							int iY = (pcUnit->sPosition.iY - u->sPosition.iY) >> 8;
							int iZ = (pcUnit->sPosition.iZ - u->sPosition.iZ) >> 8;

							//Calculate Distance
							int iDistance = (iX*iX) + (iY*iY) + (iZ*iZ);

							//User Near from Unit?
							if (iDistance < DISTANCE_UNIT_FAR && abs(iX) < (64 * 64) && abs(iZ) < (64 * 64))
							{
								//Area Skill?
								if (pcUnit->iAreaDamageArea && abs(iY) < 140)
								{
									//Inside Area Skill?
									if (pcUnit->sUnitInfo.SkillDistance && pcUnit->sUnitInfo.SkillRangeRect.right && pcUnit->sUnitInfo.SkillRangeRect.left)
									{
										//Inside X?
										if (u->sPosition.iX > pcUnit->sUnitInfo.SkillRangeRect.left &&
											u->sPosition.iX < pcUnit->sUnitInfo.SkillRangeRect.right)
										{
											//Inside Z?
											if (u->sPosition.iZ > pcUnit->sUnitInfo.SkillRangeRect.top &&
												u->sPosition.iZ < pcUnit->sUnitInfo.SkillRangeRect.bottom)
											{
												//Send Damage to User
												rsSendTransSkillAttack(pcUnit, u);
											}
										}
									}
									else if (iDistance < pcUnit->iAreaDamageArea)
									{
										//Send Damage to User
										rsSendTransSkillAttack(pcUnit, u);
									}
								}

								//Distance minor than Minimal Distance?
								if (iDistance < iDistanceMin && abs(iY) < 140)
								{
									//New Distance relative to View Sight of Unit
									int iDistanceN = pcUnit->sCharacterData.iSight;

									//Vanish Effect
									DWORD dwTimeEnd = u->dwVanishEndTime;

									//Vanish?
									if (dwTimeEnd && dwTimeEnd > SERVER_GAMETIME)
									{
										//Not Boss?
										if (pcUnit->sCharacterData.sGlow != 1)
										{
											//Vanish Distance can affect Unit
											iDistanceN = (pcUnit->sUnitInfo.iSight * (int)u->saVanishParam[0]) / 100;
											iDistanceN += pcUnit->sUnitInfo.iSight;

											//Compute Sight Distance
											if (iDistanceN > 0)
												iDistanceN *= iDistanceN;
											else
												iDistanceN = 0;
										}
									}
									else
									{
										//Clear Vanish
										u->dwVanishEndTime = 0;
									}

									//Not Hidden and on distance?
									if (iDistance < iDistanceN && !u->bCloak)
									{
										//Both in Bellatra?
										if (pcUnit->dwExclusiveNum == 0x100)
										{
											if (u->dwExclusiveNum == 0x100)
											{
												//Target User
												pcTarget = u;
											}
										}
										else
											pcTarget = u;

										//Update Minimal Distance
										iDistanceMin = iDistance;
									}
								}
							}
						}
					}

					//Freeze Stun? No Target
					if (pcUnit->iStunTimeLeft)
						pcTarget = NULL;

					//Range Skill? Clear it...
					if (pcUnit->iAreaDamageArea)
						pcUnit->iAreaDamageArea = 0;

					//Not Time Locked Target?
					if (pcUnit->dwIgnoreOthersTime == 0)
					{
						//Set New Target
						pcUnit->pcFocusTarget = pcTarget;

						//Have Target?
						if (pcTarget)
						{
							smSTAGE3D * pcStage = pcUnit->lpStage;

							if (pcStage)
							{
								//Update Position to Target Position
								pcUnit->SetNextTarget(pcTarget->sPosition.iX, pcTarget->sPosition.iY, pcTarget->sPosition.iZ);

								if (IsSafeStuckUnit(pcUnit))
								{
									if (pcUnit->sPosition.WithinPTDistance(&pcUnit->sSpawnPosition, 448) == FALSE)
									{
										pcUnit->SetNextTarget(pcUnit->sSpawnPosition.iX, pcUnit->sSpawnPosition.iY, pcUnit->sSpawnPosition.iZ);

										if (pcUnit->sCharacterData.sHP.sMin < pcUnit->sCharacterData.sHP.sMax)
										{
											pcUnit->sCharacterData.sHP.sMin += 1000;

											if (pcUnit->sCharacterData.sHP.sMin > pcUnit->sCharacterData.sHP.sMax)
												pcUnit->sCharacterData.sHP.sMin = pcUnit->sCharacterData.sHP.sMax;

											if (pcUnit->iHPBlocks > 0)
												pcUnit->sHPBlocks.sMin = (short)pcUnit->iHPBlocks;

											pcUnit->pcFocusTarget = NULL;

											pcUnit->dwIgnoreOthersTime = SERVER_GAMETIME + 5000;
										}
									}
								}
							}
						}
					}
					else
					{
						if (pcUnit->dwIgnoreOthersTime < SERVER_GAMETIME)
							pcUnit->dwIgnoreOthersTime = 0;
					}
				}
				else
				{
					Unit * pcTarget = pcUnit->pcAttackTarget;

					//Update Position to Target Position
					pcUnit->SetNextTarget(pcTarget->sPosition.iX, pcTarget->sPosition.iY, pcTarget->sPosition.iZ);
				}
			}
		}

		//Not Alive?
		if (pcUnit->ActionPattern == UPDATEMODE_ServerMonster && pcUnit->dwLastActiveTime)
		{
			DWORD dwTime = pcUnit->dwLastActiveTime + (5 * 60 * 1000);

			if (!pcUnit->dwLastUpdateTime && dwTime < SERVER_GAMETIME)
			{
				//Close Unit
				pcUnit->Close();

				//Decrease Monster Counter on Map and delete from Spawn Flag
				pcMap->iNumAliveUnitData--;
				SERVERMAP->DelMonsterSpawn(pcMap, pcUnit);
			}
		}

		//Pet?
		if (pcUnit->pcOwner)
		{
			User * u = pcUnit->pcOwner;
			Map * pa = pcUnit->pcMap;

			//Online?
			if (pa && pa->pcBaseMap && u->pcSocketData)
			{
				if (u->iMapID != pa->pcBaseMap->iMapID)
				{
					//Close Unit
					pcUnit->Close();

					//Decrease Monster Counter on Map and delete from Spawn Flag
					pcMap->iNumAliveUnitData--;
					SERVERMAP->DelMonsterSpawn(pcMap, pcUnit);
				}
			}
		}
	}

	return TRUE;
}
BOOL CServerUnit::HandleKill(Unit * pcUnit, User * pcUser)
{
	//Quest
	if (pcUnit->sUnitInfo.iQuestItemID)
	{
		if (IsEventItem(pcUnit->sUnitInfo.iQuestItemID, pcUser, pcUnit))
			SERVERITEM->CreateItem(pcUser, pcUnit->sUnitInfo.iQuestItemID, 1);
	}
	//Extra Drops
	for (int i = 0; i < pcUnit->sUnitInfo.iDropPlusCount; i++)
	{
		if (RandomI(0, 10000) < pcUnit->sUnitInfo.saDropDataCustom[i].iPercent)
		{
			auto iItemID = pcUnit->sUnitInfo.saDropDataCustom[i].iItemID;

			DefinitionItem * pItem = SERVERITEM->FindItemDefByCode(iItemID);

			LootItem sLootItem;

			if (pItem && (pItem->sItem.iItemUniqueID == FALSE))
			{
				SERVERITEM->CreateItem(&sLootItem.sItem, pItem);

				if ((sLootItem.sItem.sItemID.ToItemType() == ITEMTYPE_Quest) || (sLootItem.sItem.sItemID.ToItemType() == ITEMTYPE_MorionT2Quest))
				{
					SERVERITEM->SendItemData(pcUser, &sLootItem.sItem);
					break;
				}
				if (pcUnit->dwExclusiveNum != 0x100 || (pItem->sItem.sItemID.ToItemType() != ITEMTYPE_GoldAndExp && pItem->sItem.sItemID.ToItemBase() != ITEMBASE_Potion))
				{
					auto pcMap = pcUnit->pcMap;

					if (pcMap)
					{
						MapLoot *psItemD = SERVERMAP->AddItem(pcMap, &sLootItem, pcUnit->sPosition >> 8, TRUE);

						if (psItemD)
						{
							if (pcUnit->sUnitInfo.bPublicDrop)
								SERVERMAP->SendItemStageNearUsers(pcMap, psItemD);
							else
								SERVERMAP->SendItemStageUser(pcMap, pcUser, psItemD);

							psItemD->dwDropTime += 5000;
							break;
						}
					}
				}
			}
		}
	}

	//Set the quantity of drops
	OnSetDrop(pcUser, pcUnit);

	//Normal Drops
	int iDropIndex = 1;

	for (int i = 0; i < pcUnit->sUnitInfo.iNumDrops; i++)
	{
		LootItem sItemLoot;

		if (srGetMonsterItem(pcUser, pcUnit, &sItemLoot))
		{
			if ((sItemLoot.sItem.sItemID.ToItemType() == ITEMTYPE_Quest) || (sItemLoot.sItem.sItemID.ToItemType() == ITEMTYPE_MorionT2Quest))
			{
				SERVERITEM->SendItemData(pcUser, &sItemLoot.sItem);
				break;
			}

			if (pcUnit->dwExclusiveNum != 0x100 || (sItemLoot.sItem.sItemID.ToItemType() != ITEMTYPE_GoldAndExp && sItemLoot.sItem.sItemID.ToItemBase() != ITEMBASE_Potion))
			{
				sItemLoot.bUse = TRUE;

				Map * pcMap = pcUnit->pcMap;
				if (pcMap)
				{
					MapLoot * psItemD = SERVERMAP->AddItem(pcMap, &sItemLoot, pcUnit->sPosition >> 8, TRUE);

					if (psItemD)
					{
						psItemD->dwDropTime += 5000;

						if (pcUnit->sUnitInfo.bPublicDrop)
						{
							//if (ROLLDICEHANDLER->OnExchangeItemDrop(pcUnit, pcMap, psItemD, iDropIndex++) == FALSE)
							SERVERMAP->SendItemStageNearUsers(pcMap, psItemD);
						}
						else
							SERVERMAP->SendItemStageUser(pcMap, pcUser, psItemD);
					}
				}
			}
		}
	}

	//Send EXP from Monster
	OnSendExp(pcUser, pcUnit);

	//Update Monsters killed by User
	pcUser->uUnitKillCounter++;

	return FALSE;
}
BOOL CServerUnit::OnUnitNpcClick(User * pcUser, Unit * pcUnit)
{
	/*if (pcUnit)
	{
		// Is only Game Master?
		if (pcUnit->sUnitInfo.bGMOnly)
		{
			SERVERCHAT->SendDebugChat(pcUser, CHATCOLOR_Global, "> Only for GameMaster!");
			return FALSE;
		}

		// Is Warehouse Pet?
		if (pcUnit->sUnitInfo.iWarehouse && pcUnit->lExclusiveTargetID && pcUser->iGameLevel <= GAMELEVEL_One &&
			pcUser->iID != pcUnit->lExclusiveTargetID)
			return FALSE;

		// Manufacture
		if (pcUnit->sUnitInfo.iSmelting == NPCEVENTCODE_Manufacture)
			SENDPACKETBLANK(pcUser, PKTHDR_OpenManufacture);

		if (pcUnit->sUnitInfo.iSmelting == NPCEVENTCODE_Smelting)
			SENDPACKETBLANK(pcUser, PKTHDR_OpenSmelting);

		if (pcUnit->sUnitInfo.iSmelting == NPCEVENTCODE_IhinEvent)
			SENDPACKETBLANK(pcUser, PKTHDR_NPCIhinRewardRequest);

		if (pcUnit->sUnitInfo.iSmelting == NPCEVENTCODE_EasterNPC)
			SENDPACKETBLANK(pcUser, PKTHDR_NPCEasterEgg);

		if (pcUnit->sUnitInfo.iSmelting == NPCEVENTCODE_ResetItem)
			SENDPACKETBLANK(pcUser, PKTHDR_OpenResetItem);
		if (pcUnit->sUnitInfo.iSmelting == NPCEVENTCODE_CoinShop)
			SENDPACKETBLANK(pcUser, PKTHDR_OpenCoinShop);
		if (pcUnit->sUnitInfo.iSmelting == NPCEVENTCODE_LarryQuestsNPC)
			SENDPACKETBLANK(pcUser, PKTHDR_NPCLarryOpen);
		if (pcUnit->sUnitInfo.iSmelting == NPCEVENTCODE_MarinaQuestsNPC)
			SENDPACKETBLANK(pcUser, PKTHDR_NPCMarinaOpen);
		if (pcUnit->sUnitInfo.iSmelting == NPCEVENTCODE_RudolphXmasNPC)
			SENDPACKETBLANK(pcUser, PKTHDR_NPCRudolphXmas);
		if (pcUnit->sUnitInfo.iSmelting == NPCEVENTCODE_FuryArenaNPCTeleportCT2)
		{
			if (SERVER_CODE == 1)
			{
				PacketFuryArenaRequest sPacket;
				sPacket.iLength = sizeof(PacketFuryArenaRequest);
				sPacket.iHeader = PKTHDR_FuryArena;
				sPacket.eState = FURYARENASTATEID_OpenNPC;
				sPacket.iEventID = FURYARENAHANDLER->GetEventID();
				sPacket.dwTimeLeft = FURYARENAHANDLER->GetTimeLeft(GetServerTime());
				SENDPACKET(USERDATATOUSER(pcUserData), &sPacket, TRUE);
			}
			else
			{
				CHATSERVER->SendChat(USERDATATOUSER(pcUserData), CHATCOLOR_Global, "FuryArena> The Grand Fury is closed on this server!");
			}
		}
		if (pcUnit->sUnitInfo.iSmelting == NPCEVENTCODE_FuryArenaNPCEnter)
		{
			if (SERVER_CODE == 1)
			{
				PacketFuryArenaRequest sPacket;
				sPacket.iLength = sizeof(PacketFuryArenaRequest);
				sPacket.iHeader = PKTHDR_FuryArena;
				sPacket.eState = FURYARENASTATEID_OpenNPCEntrance;
				sPacket.iEventID = FURYARENAHANDLER->GetEventID();
				sPacket.dwTimeLeft = FURYARENAHANDLER->GetTimeLeft(GetServerTime());
				SENDPACKET(USERDATATOUSER(pcUserData), &sPacket, TRUE);
			}
			else
			{
				CHATSERVER->SendChat(USERDATATOUSER(pcUserData), CHATCOLOR_Global, "FuryArena> The Grand Fury is closed on this server!");
			}
		}
		if (pcUnitData->sUnitInfo.iSmelting == NPCEVENTCODE_SocketSystemNPCDrill || pcUnitData->sUnitInfo.iSmelting == NPCEVENTCODE_SocketSystemNPCStone)
		{
			int iID = pcUnitData->sUnitInfo.iSmelting == NPCEVENTCODE_SocketSystemNPCDrill ? 0x0E : 0x0F;
			PacketSimple s;
			s.iLength = sizeof(PacketSimple);
			s.iHeader = PKTHDR_OpenNPC;
			s.iUnk = 0;
			s.iUnk2 = iID;
			s.iUnk3 = 0;
			s.iUnk4 = 0;
			SENDPACKET(USERDATATOUSER(pcUserData), &s, TRUE);
		}
		if (pcUnitData->sUnitInfo.iEventGirl)
		{
			PacketEventGirl s;
			s.iLength = sizeof(PacketEventGirl);
			s.iHeader = PTKHDR_OpenEventGirl;
			s.bFreeGold = FREE_EVENTGIRL;
			SENDPACKET(USERDATATOUSER(pcUserData), &s);
		}
	}*/

	return FALSE;
}

void CServerUnit::OnSetDrop(User * pcUser, Unit * pcUnit)
{
	if (pcUser && pcUnit)
	{
		//Premium Third Eye?
		ItemPremium * psPremium = SERVERITEM->GetPremiumUse(pcUser, ITEMTIMERTYPE_ThirdEye);
		if (psPremium && psPremium->dwTimeLeft)
		{
			int iDropCount = pcUnit->sUnitInfo.iNumDrops;
			pcUnit->sUnitInfo.iNumDrops++;

			SERVERCHAT->SendDebugChat(pcUser, CHATCOLOR_Error, "> ThirdEye +1 Drop [ %d -> %d ]", iDropCount, pcUnit->sUnitInfo.iNumDrops);
		}

		//Is in Party?
		if ((pcUser->bParty && pcUser->psParty) && pcUser->psParty->iMembersCount > 1 && pcUser->psParty->iMode != PARTYMODE_Normal)
		{
			int iMembers = 1;
			for (int i = 0; i < MAX_PARTY_MEMBERS; i++)
			{
				User * p = i == 0 ? pcUser->psParty->pcLeader : pcUser->psParty->pcaMembers[i - 1];
				if (p && p != pcUser && p->pcSocketData)
				{
					int iX = (p->sPosition.iX - pcUser->sPosition.iX) >> 8;
					int iZ = (p->sPosition.iZ - pcUser->sPosition.iZ) >> 8;

					int iDistance = iX * iX + iZ * iZ;

					if (iDistance < PARTY_GETTING_DIST)
						iMembers++;
				}
			}

			//Party Drop
			if (iMembers > 1)
			{
				int iRand = 0;

				if (iMembers == 2)
					iRand = pcUser->psParty->iMode == PARTYMODE_EXP ? 10 : 10;
				else if (iMembers == 3)
					iRand = pcUser->psParty->iMode == PARTYMODE_EXP ? 20 : 20;
				else if (iMembers == 4)
					iRand = pcUser->psParty->iMode == PARTYMODE_EXP ? 40 : 30;
				else if (iMembers == 5)
					iRand = pcUser->psParty->iMode == PARTYMODE_EXP ? 60 : 40;
				else if (iMembers == 6)
					iRand = pcUser->psParty->iMode == PARTYMODE_EXP ? 80 : 50;

				bool bExtra = RandomI(0, 100) < iRand ? true : false;

				int iDropCount = pcUnit->sUnitInfo.iNumDrops;
				if (pcUser->psParty->iMode == PARTYMODE_EXP)
					pcUnit->sUnitInfo.iNumDrops -= bExtra ? 2 : 1;
				else
					pcUnit->sUnitInfo.iNumDrops += bExtra ? 2 : 1;

				SERVERCHAT->SendDebugChat(pcUser, CHATCOLOR_Error, "> Party Drop [ %d -> %d ]", iDropCount, pcUnit->sUnitInfo.iNumDrops);
			}
		}

		//Quest Reduce Drop
		//if (pcUnit->sUnitInfo.iNumDrops > 1)
			//pcUnit->sUnitInfo.iNumDrops -= QUESTSERVER->GetReduceQuestDrop(pcUser, pcUnit);
	}
}
void CServerUnit::OnSendExp(User * pcUser, Unit * pcUnit)
{
	if (pcUser && pcUnit)
	{
		INT64 iExp = pcUnit->sCharacterData.iExp;

		//EXP Party
		if ((pcUser->bParty && pcUser->psParty && pcUser->psParty->pcLeader) && pcUser->psParty->iMembersCount > 1)
		{
			PartyInfo * psParty = pcUser->psParty;

			int iPercent = 0;

			//Percentage to EXP Mode, Normal Mode and Hunt Mode
			if (psParty->iMode == PARTYMODE_EXP)
				iPercent = 180 + (80 * (psParty->iMembersCount - 2));
			else if (psParty->iMode == PARTYMODE_Normal)
				iPercent = 140 + (40 * (psParty->iMembersCount - 2));
			else if (psParty->iMode == PARTYMODE_Hunt)
				iPercent = 80 + (20 * (psParty->iMembersCount - 2));

			iExp = ((iExp * iPercent) / 100) / psParty->iMembersCount;
			INT64 iExpParty = iExp;

			//Get Level Average
			int iLevelAvg = psParty->pcLeader->sCharacterData.iLevel;

			for (size_t i = 0; i < MAX_PARTY_MEMBERS - 1; i++)
			{
				User * p = psParty->pcaMembers[i];
				if (p && p->pcSocketData)
					iLevelAvg += p->sCharacterData.iLevel;
			}

			iLevelAvg /= psParty->iMembersCount;

			if (iLevelAvg > pcUnit->sCharacterData.iLevel)
				iExpParty = GetExpLevelDiference(iLevelAvg, pcUnit->sCharacterData.iLevel, iExp);

			//Send EXP to Users
			for (size_t i = 0; i < MAX_PARTY_MEMBERS; i++)
			{
				User * p = i == 0 ? psParty->pcLeader : psParty->pcaMembers[i - 1];
				if (p)
				{
					int iX = (p->sPosition.iX - pcUser->sPosition.iX) >> 8;
					int iZ = (p->sPosition.iZ - pcUser->sPosition.iZ) >> 8;
					int iDist = iX * iX + iZ * iZ;

					INT64 iGain = 0;
					ItemPremium * psPremium = SERVERITEM->GetPremiumUse(p, ITEMTIMERTYPE_ExpUp);

					//EXP Pot
					if (psPremium && psPremium->dwTimeLeft)
						iGain = (iExpParty * 30) / 100;

					//Is near distance?
					if (iDist < PARTY_GETTING_DIST && p->GetMapID() == pcUser->iMapID)
					{
						int iLevel = p->sCharacterData.iLevel;
						if (iLevel >= 0 && iLevel <= 80 && bFreeExpEvent)
						{
							iGain += ((iExpParty + iGain) * iExpFreeExp) / 100;
							SERVERCHAT->SendChatEx(p, CHATCOLOR_Notice, "> Free EXP +%d%%", iExpFreeExp);
						}

						SERVERCHARACTER->GiveEXP(p, iExpParty + iGain);

						if (psPremium && psPremium->dwTimeLeft)
							SERVERCHAT->SendDebugChat(p, CHATCOLOR_Error, "> ExpUp +30%%");

						SERVERCHAT->SendChatEx(p, CHATCOLOR_Notice, "> Gained %s exp [%d%% / %d] in party!", FormatNumber(iExp + iGain), iPercent, psParty->iMembersCount);
					}
				}
			}

			//Raid & Party Kill
			if (psParty->iRaidCount > 0)
			{
				for (int i = 0; i < MAX_RAID; i++)
				{
					PartyInfo * psP = i == 0 ? psParty->pcRaidLeader : psParty->pcaRaid[i - 1];
					for (size_t j = 0; j < MAX_PARTY_MEMBERS; j++)
					{
						User * p = j == 0 ? psP->pcLeader : psP->pcaMembers[j - 1];
						if (p)
						{
							int iX = (p->sPosition.iX - pcUser->sPosition.iX) >> 8;
							int iZ = (p->sPosition.iZ - pcUser->sPosition.iZ) >> 8;
							int iDist = iX * iX + iZ * iZ;

							//Is near distance?
							if (iDist < PARTY_GETTING_DIST && p->GetMapID() == pcUser->iMapID)
							{
								ProcessPacketKillUnitID(p, pcUnit->iID);
							}
						}
					}
				}
			}
			else
			{
				for (size_t i = 0; i < MAX_PARTY_MEMBERS; i++)
				{
					User * p = i == 0 ? psParty->pcLeader : psParty->pcaMembers[i - 1];
					if (p)
					{
						int iX = (p->sPosition.iX - pcUser->sPosition.iX) >> 8;
						int iZ = (p->sPosition.iZ - pcUser->sPosition.iZ) >> 8;
						int iDist = iX * iX + iZ * iZ;

						//Is near distance?
						if (iDist < PARTY_GETTING_DIST && p->GetMapID() == pcUser->iMapID)
						{
							ProcessPacketKillUnitID(p, pcUnit->iID);
						}
					}
				}
			}
		}
		else
		{
			if (pcUser->sCharacterData.iLevel > pcUnit->sCharacterData.iLevel)
				iExp = GetExpLevelDiference(pcUser->sCharacterData.iLevel, pcUnit->sCharacterData.iLevel, iExp);

			ItemPremium * psPremium = SERVERITEM->GetPremiumUse(pcUser, ITEMTIMERTYPE_ExpUp);
			// Premium Exp pot?
			if (psPremium && psPremium->dwTimeLeft)
			{
				INT64 iGain = (iExp * 30) / 100;
				iExp += iGain;
			}

			//Quest Increase EXP
			//iExp += QUESTSERVER->GetQuestEXPOnKill(pcUser, pcUnit, iExp);

			int iLevel = pcUser->sCharacterData.iLevel;
			if (iLevel >= 0 && iLevel <= 80 && bFreeExpEvent)
			{
				iExp += (iExp * iExpFreeExp) / 100;
				SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Notice, "> Free EXP +%d%%", iExpFreeExp);
			}
			SERVERCHARACTER->GiveEXP(pcUser, iExp);

			if (psPremium && psPremium->dwTimeLeft)
				SERVERCHAT->SendDebugChat(pcUser, CHATCOLOR_Error, "> ExpUp +30%%");

			ProcessPacketKillUnitID(pcUser, pcUnit->iID);

			SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Notice, "> Gained %s Exp", FormatNumber(iExp));
		}
	}
}
void CServerUnit::ProcessPacketKillUnitID(User * pcUser, int iID)
{
	PacketExperienceOld sPacketOld;
	sPacketOld.iLength = sizeof(PacketExperienceOld);
	sPacketOld.iHeader = PKTHDR_SetExpOld;
	sPacketOld.iMonsterID = iID;
	sPacketOld.WParam = 0;
	sPacketOld.SParam = 0;
	sPacketOld.EParam = 0;
	SENDPACKET(pcUser, &sPacketOld);
}
void CServerUnit::ProcessPacketEffectWarp(User * pcUser, Point3D sPosition)
{
	//User Warp Effect summon crystal
	PacketUserEffectWarp sPacketEffect;

	ZeroMemory(&sPacketEffect, sizeof(PacketUserEffectWarp));
	sPacketEffect.iLength = sizeof(PacketUserEffectWarp);
	sPacketEffect.iHeader = PKTHDR_UseEffect;
	sPacketEffect.eEffectID = EFFECTID_Warp;
	sPacketEffect.sPosition = sPosition;

	SENDPACKETRANGE(&sPacketEffect, &pcUser->sPosition, DISTANCE_UNIT_NEAR);
}
void CServerUnit::ProcessPacketEffectResurrection(User * pcUser, int iID)
{
	PacketUserEffectResurrection sPacketEffect;

	ZeroMemory(&sPacketEffect, sizeof(PacketUserEffectResurrection));
	sPacketEffect.iLength = sizeof(PacketUserEffectResurrection);
	sPacketEffect.iHeader = PKTHDR_UseEffect;
	sPacketEffect.eEffectID = EFFECTID_Resurrection;
	sPacketEffect.lID = iID;

	SENDPACKETRANGE(&sPacketEffect, &pcUser->sPosition, DISTANCE_UNIT_NEAR);
}
void CServerUnit::ProcessPacketEffectValento(User * pcUser, int iMonsterID, int iUserID)
{
	PacketUserEffectValento sPacketEffect;

	ZeroMemory(&sPacketEffect, sizeof(PacketUserEffectValento));
	sPacketEffect.iLength = sizeof(PacketUserEffectValento);
	sPacketEffect.iHeader = PKTHDR_UseEffect;
	sPacketEffect.eEffectID = EFFECTID_Valento;
	sPacketEffect.lMonsterID = iMonsterID;
	sPacketEffect.lUserID = iUserID;

	SENDPACKETRANGE(&sPacketEffect, &pcUser->sPosition, DISTANCE_UNIT_NEAR);
}
void CServerUnit::ProcessPacketEffectHolyIncAntation(User * pcUser, int iID, int iTime)
{
	PacketUserEffectHolyIncAntation sPacketEffect;

	ZeroMemory(&sPacketEffect, sizeof(PacketUserEffectHolyIncAntation));
	sPacketEffect.iLength = sizeof(PacketUserEffectHolyIncAntation);
	sPacketEffect.iHeader = PKTHDR_UseEffect;
	sPacketEffect.eEffectID = EFFECTID_HolyIncAntation;
	sPacketEffect.lID = iID;
	sPacketEffect.iTime = iTime;

	SENDPACKETRANGE(&sPacketEffect, &pcUser->sPosition, DISTANCE_UNIT_NEAR);
}
void CServerUnit::HandlePacket(User * pcUser, PacketUserEffect * psPacket)
{
	if (!GAME_SERVER)
		return;

	if (IsUseEffect(psPacket) != EFFECTID_None)
		SENDPACKETRANGE(psPacket, &pcUser->sPosition, DISTANCE_UNIT_NEAR);
}
void CServerUnit::HandlePacket(User * pcUser, PacketUseGold * psPacket)
{
	if (psPacket->eWhere == WHEREID_UnitDie)
	{
		int iGold = pcUser->GetGold() / 100;

		//Lost Gold
		SERVERCHARACTER->GiveGold(pcUser, -iGold, WHEREID_UnitDie);
	}
}
INT64 CServerUnit::GetExpLevelDiference(int iLevel1, int iLevel2, INT64 iExp)
{
	int iLevel = abs(iLevel1 - iLevel2);

	if (iLevel < 10)
		iExp = iExp;
	else if (iLevel < 15)
		iExp = (iExp * 75) / 100;
	else if (iLevel < 20)
		iExp = (iExp * 50) / 100;
	else
		iExp = (iExp * 25) / 100;

	return iExp;
}
Unit * CServerUnit::GetUnitFromPosition(int iX, int iY, int iZ)
{
	auto pcMap = m_pcUnit->pcMap;

	if (pcMap)
	{
		for (int i = 0; i < pcMap->iNumUsingUnit; i++)
		{
			auto pcUnit = pcMap->pcaUnitData[i];

			if (pcUnit && m_pcUnit != pcUnit && pcUnit->sCharacterData.sHP.sMin > 0)
			{
				if ((iY - 32 * 256) < pcUnit->pY && (iY + 32 * 256) > pcUnit->pY)
				{
					int iMapX = (pcUnit->pX - iX) >> 8;
					int iMapZ = (pcUnit->pZ - iZ) >> 8;

					int iDist = iMapX * iMapX + iMapZ * iMapZ;

					if (iDist < (32 * 32))
						return pcUnit;
				}
			}
		}
	}

	return nullptr;
}
BOOL CServerUnit::IsMultiplyHPMonter(Unit * pcUnit, BOOL bMulit)
{
	BOOL bMultiply = FALSE;

	// Monsters from effect ID
	switch (pcUnit->sCharacterData.iMonsterEffectID)
	{
	case MONSTEREFFECTID_DEATHKNIGHT:
	case MONSTEREFFECTID_KELVEZU:
	case MONSTEREFFECTID_MOKOVA:
	case MONSTEREFFECTID_TULLA:
	case MONSTEREFFECTID_Yagditha:
	case MONSTEREFFECTID_Draxos:
		bMultiply = TRUE;
		break;
	default:
		break;
	}

	// By Name
	if (STRINGCOMPARE("King Fury", pcUnit->sCharacterData.szName))
		bMultiply = TRUE;

	// Multiply HP?
	if (bMultiply || bMulit)
	{
		pcUnit->iHPBlocks = pcUnit->sUnitInfo.iMaxPotions;
		pcUnit->sHPBlocks.sMin = (short)pcUnit->iHPBlocks;
		pcUnit->sHPBlocks.sMax = (short)pcUnit->iHPBlocks;
		pcUnit->sVirtualHP.sMin = (short)pcUnit->iHPBlocks;
		pcUnit->sVirtualHP.sMax = (short)pcUnit->iHPBlocks;
	}
	else
	{
		// Set potion percent, maybe pot anim
		if (pcUnit->sUnitInfo.iMaxPotions)
		{
			if ((rand() % 100) < pcUnit->sUnitInfo.iPerPotions)
			{
				pcUnit->sUnitInfo.iMaxPotions = (rand() % pcUnit->sUnitInfo.iMaxPotions) + 1;
			}
			else
			{
				pcUnit->sUnitInfo.iMaxPotions = 0;
			}
		}
	}
	return bMultiply;
}
Unit * CServerUnit::GetEmptyUnit()
{
	for (int i = 0; i < UNITS_MAX; i++)
	{
		Unit * pcUnit = pcaUnit + i;

		if (pcUnit->bActive == FALSE)
			return pcUnit;
	}

	return nullptr;
}
Unit *CServerUnit::GetUnit(UINT iID, EMapID iMapID)
{
	if (iID != 0)
	{
		if (iMapID != MAPID_Invalid)
		{
			Map * pcMap = SERVERMAP->GetMap(iMapID);

			if (pcMap)
			{
				for (int i = 0; i < MAX_ALIVEMONSTERS; i++)
				{
					Unit * pcUnit = pcMap->pcaUnitData[i];

					if (pcUnit && pcUnit->iID == iID)
						return pcUnit;
				}
			}
		}
		else
		{
			for (int i = 0; i < UNITS_MAX; i++)
			{
				Unit *pcUnit = pcaUnit + i;

				if (pcUnit->iID == iID && pcUnit->bActive)
					return pcUnit;
			}
		}
	}

	return nullptr;
}
Unit *CServerUnit::GetPetUnit(Unit *pcMasterUnit)
{
	for (int i = 0; i < UNITS_MAX; i++)
	{
		Unit * pcUnit = pcaUnit + i;

		if (pcUnit->bActive &&
			pcUnit != pcMasterUnit &&
			pcUnit->pcExclusiveUnitTarget == pcMasterUnit &&
			pcUnit->sCharacterData.sHP.sMin > 0)
		{
			if (!pcMasterUnit->lpLinkPlayInfo || pcMasterUnit->lpLinkPlayInfo == pcUnit->lpLinkPlayInfo)
				return pcUnit;
		}
	}

	return nullptr;
}
ID CServerUnit::CreateID()
{
	static ID iIDIndex = 0x2000;

	ID iID = (iIDIndex & 0x0FFFFFFF) | (SERVER_CODE << 28);

	iIDIndex++;

	return iID;
}
BOOL CServerUnit::IsSafeStuckUnit(Unit * pcUnit)
{
	Point3D sPosition;

	if (SERVERMAP->SetBossPosition(pcUnit->pcMap, &pcUnit->sCharacterData, sPosition))
		return TRUE;

	return FALSE;
}
BOOL CServerUnit::IsEventItem(DWORD iItemID, User *pcUser, Unit *pcUnit)
{
	if (pcUnit->sUnitInfo.iQuestItemID == ITEMID_RoyalAmulet)
	{
		return pcUser->sCharacterData.iRank < 3 && rand() % 100 <= 20 ? TRUE : FALSE;
	}

	return TRUE;
}
int CServerUnit::GetTotalHP(Unit * pcUnit)
{
	if (pcUnit)
	{
		int iHP = pcUnit->iHPBlocks;
		return ((int)pcUnit->sCharacterData.sHP.sMax * iHP) + (int)pcUnit->sCharacterData.sHP.sMax;
	}

	return 0;
}
int CServerUnit::IsFreezedUnitFollow(Unit * pcUnit)
{
	//Return 0 = jump all, 1 = can die, 2 = follow
	if (pcUnit->pcOwner == NULL)
		return 0;

	if (pcUnit->iPetID == 0)
	{
		if (pcUnit->lExclusiveTargetID)
		{
			Map * pcMap = SERVERMAP->GetMap(MAPID_T5QuestArena);

			if (pcMap)
			{
				if ((pcUnit->pcMap == pcMap) && (pcUnit->lExclusiveTargetID == pcUnit->pcOwner->iID))
					return 0;
			}
		}

		//Follow
		if (pcUnit->sCharacterData.iMonsterType == MONSTERTYPE_Friendly)
			return 2;

		//Follow
		if (pcUnit->sCharacterData.iType == CHARACTERTYPE_NPC)
			return 2;

		return 0;
	}

	if (pcUnit->pcOwner->pcSocketData == NULL)
		return 0;

	if (pcUnit->sCharacterData.sHP.sMin <= 0)
		return 0;

	// No Pet
	if (IsPet(pcUnit) == FALSE)
	{
		//Die
		if (pcUnit->iPetID != 1)
			return 1;
	}

	//Follow
	return 2;
}
BOOL CServerUnit::IsPet(Unit *pcUnit)
{
	for (int i = 0; i < 10; i++)
	{
		if (pcUnit->pcOwner && pcUnit->pcOwner->lpLinkChar[i] == pcUnit)
			return TRUE;
	}

	return FALSE;
}

CharacterData * CServerUnit::GetCharacterDataByEffect(DWORD dwEffect, int iClass)
{
	for (auto & v : m_vMonsterTable)
	{
		if (v->iMonsterEffectID == dwEffect)
		{
			if (iClass != 0)
			{
				if (v->sGlow == (WORD)iClass)
					return v;
			}
			else
				return v;
		}
	}

	return nullptr;
}

CharacterData * CServerUnit::GetCharacterDataByName(const char * pszName)
{
	for (auto & v : m_vMonsterTable)
	{
		if (STRINGCOMPAREI(v->szName, pszName))
			return v;
	}

	return NULL;
}

Unit * CServerUnit::CreateUnitEnemy(const char * pszName, int iX, int iY, int iZ, User * pcUser)
{
	Map *pcMap = SERVERMAP->GetMapByXZ(iX, iZ);

	if (pcMap)
	{
		CharacterData *pCharData = NULL;

		if (pszName && pszName[0])
		{
			pCharData = GetCharacterDataByName(pszName);
		}

		if (pCharData)
		{
			pcMap->bForceCreateMonster = TRUE;

			Unit *pcUnit = SERVERMAP->CreateUnit(pcMap, pCharData);

			if (pcUnit)
			{
				pcUnit->sPosition = Point3D(iX, iY, iZ);
				pcUnit->iLureDistance = 0;
				pcUnit->SetMotionFromCode(ANIMATIONTYPE_Idle);
				pcUnit->TargetMoveCount = 0;

				if (pcUser)
				{
					pcUnit->pcOwner = pcUser;
					pcUnit->sUnitInfo.dwHashCharacterName = 0;
					pcUnit->sCharacterData.iMonsterType = MONSTERTYPE_Friendly;

					STRINGCOPY(pcUnit->sCharacterData.Pet.szOwnerName, pcUser->sCharacterData.szName);
					pcUnit->sCharacterData.iOwnerID = pcUser->iID;
					pcUnit->dwLastUpdateTime = SERVER_GAMETIME + 4 * 60 * 1000;
				}

				return pcUnit;
			}
		}
	}

	return nullptr;
}

BOOL CServerUnit::OnUnitChanger(Unit * pcUnit)
{
	BOOL bRet = FALSE;

	//Special Summon Effect?
	if (pcUnit->psModelAnimation->iType == ANIMATIONTYPE_Special && pcUnit->iFrameTimer > 60)
	{
		EMonsterEffectID eEffect = (EMonsterEffectID)pcUnit->sCharacterData.iMonsterEffectID;

		//Mini Hulk?
		if (eEffect == MONSTEREFFECTID_HUNGKY)
		{
			//Find Hulk
			for (auto &ps : m_vMonsterTable)
			{
				//Hulk and not Crystal or Bellatra Monster?
				if (ps->iMonsterEffectID == MONSTEREFFECTID_HULK && ps->szName[0] != ' ')
				{
					auto psU = ps->psUnitInfo;

					if (pcUnit->AttackAnger <= 80)
					{
						if (ps->iLevel < 80)
						{
							//Change
							UnitSwapper(pcUnit, ps, psU);
							bRet = TRUE;
							break;
						}
					}
					else if (ps->iLevel >= 80)
					{
						//Change
						UnitSwapper(pcUnit, ps, psU);
						bRet = TRUE;
						break;
					}
				}
			}
		}

		//Mini Dead Hopy?
		if (eEffect == MONSTEREFFECTID_DEADHOPT)
		{
			//Find Dead King Hopy
			for (auto &ps : m_vMonsterTable)
			{
				auto psU = ps->psUnitInfo;

				//Dead King Hopy and not Crystal or Bellatra Monster?
				if (ps->iMonsterEffectID == MONSTEREFFECTID_DEADKINGHOPY && ps->szName[0] != ' ')
				{
					if (ps->iLevel >= 108)
					{
						//Change
						UnitSwapper(pcUnit, ps, psU);
						bRet = TRUE;
						break;
					}
				}
			}
		}
	}

	return bRet;
}
void CServerUnit::UnitSwapper(Unit *pcUnit, CharacterData *psCharacterData, UnitInfo *psUnitInfo)
{
	if (pcUnit)
	{
		Map *pcMap = pcUnit->pcMap;
		int iDist = 64 * 30;

		pcUnit->Close();
		pcUnit->bActive = TRUE;

		ID iID = pcUnit->iID;

		CopyMemory(&pcUnit->sCharacterData, psCharacterData, sizeof(CharacterData));
		CopyMemory(&pcUnit->sUnitInfo, psUnitInfo, sizeof(UnitInfo));

		pcUnit->ActionPattern = 5;
		pcUnit->SetLoadPattern(pcUnit->sCharacterData.Player.szBodyModel);
		pcUnit->iLureDistance = iDist * iDist;
		pcUnit->sSpawnPosition.iX = pcUnit->pX;
		pcUnit->sSpawnPosition.iZ = pcUnit->pZ;
		pcUnit->iDeathCounter = 256;
		pcUnit->SetMotionFromCode(ANIMATIONTYPE_Idle);
		pcUnit->sCharacterData.bUpdateInfo[0]++;
		pcUnit->iID = iID;
		pcUnit->pcFocusTarget = 0;
		pcUnit->sCharacterData.sHP.sMin = pcUnit->sCharacterData.sHP.sMax;
		pcUnit->sCharacterData.iStatPoints = psUnitInfo->ClassCode;

		if (pcUnit->sUnitInfo.iMaxPotions)
		{
			if ((rand() % 100) < pcUnit->sUnitInfo.iPerPotions)
				pcUnit->sUnitInfo.iMaxPotions = (rand() % pcUnit->sUnitInfo.iMaxPotions) + 1;
			else
				pcUnit->sUnitInfo.iMaxPotions = 0;
		}
	}
}
void CServerUnit::CreateEventUnit(UINT uCode)
{
	for (auto & psCharacterData : m_vMonsterTable)
	{
		if (psCharacterData->psUnitInfo->eSpecialType == 100)
		{
			auto pcMap = SERVERMAP->GetMap((EMapID)psCharacterData->psUnitInfo->EventInfo);

			if (pcMap)
			{
				pcMap->bForceCreateMonster = TRUE;

				SERVERMAP->CreateUnit(pcMap, psCharacterData);
				SERVERMAP->SetSpawnMonster(pcMap);
				break;
			}
		}
	}
}

void CServerUnit::FreeEventUnit(UINT uCode)
{
	for (int i = 0; i < UNITS_MAX; i++)
	{
		Unit *pcUnit = pcaUnit + i;

		if (pcUnit->bActive && pcUnit->sUnitInfo.eSpecialType == uCode)
		{
			Map * pcMap = pcUnit->pcMap;

			if (pcUnit->psModelAnimation->iType != ANIMATIONTYPE_Die)
			{
				if (pcUnit->SetMotionFromCode(ANIMATIONTYPE_Special) == FALSE)
					pcUnit->Close();

				if (pcMap)
				{
					pcMap->iNumAliveUnitData--;

					SERVERMAP->DelMonsterSpawn(pcMap, pcUnit);
				}
			}
			else
			{
				pcUnit->Close();

				if (pcMap)
				{
					pcMap->iNumAliveUnitData--;

					SERVERMAP->DelMonsterSpawn(pcMap, pcUnit);
				}
			}
		}
	}
}
EMonsterEffectID CServerUnit::GetEnemyEffect(char * pszEffect)
{
	for (auto f : saCharacterSoundEffect)
	{
		if (STRINGCOMPAREI(f.szCodeName, pszEffect))
			return f.iMonsterEffectID;
	}
	return MONSTEREFFECTID_None;
}
void CServerUnit::ReadDropItem()
{
	int iEnemy = 0;

	UINT uCount = m_vMonsterTable.size();

	for (UINT u = 0; u < uCount; u++)
	{
		CharacterData * paMonsterCharInfo = m_vMonsterTable.at(u);

		UnitInfo * pMonsterInfo = paMonsterCharInfo->psUnitInfo;

		SQLConnection * pcDB = SQLCONNECTION(DATABASEID_GameDB);
		if (pcDB->Open())
		{
			if (pcDB->Prepare("SELECT COUNT(ID) FROM DropList WHERE MonsterName=?"))
			{
				pcDB->BindParameterInput(1, PARAMTYPE_String, pMonsterInfo->szName);
				if (pcDB->Execute() && pcDB->Fetch())
				{
					pcDB->GetData(1, PARAMTYPE_Integer, &iEnemy, 0);
				}
			}
			pcDB->Close();
		}

		// Is Enemy in SQL?
		if (!IsNull(iEnemy))
		{
			// Get Data DropList
			int iDropID = 0;

			if (pcDB->Open())
			{
				if (pcDB->Prepare("SELECT * FROM DropList WHERE MonsterName=?"))
				{
					pcDB->BindParameterInput(1, PARAMTYPE_String, pMonsterInfo->szName);
					if (pcDB->Execute() && pcDB->Fetch())
					{
						pcDB->GetData(1, PARAMTYPE_Integer, &iDropID, 0);
						pcDB->GetData(3, PARAMTYPE_Integer, &pMonsterInfo->bPublicDrop, 0);
						pcDB->GetData(4, PARAMTYPE_Integer, &pMonsterInfo->iNumDrops, 0);
					}
				}
				pcDB->Close();
			}

			// Get Data DropItem
			int iCountDrop = 0;

			if (pcDB->Open())
			{
				if (pcDB->Prepare("SELECT COUNT(ID) FROM DropItem WHERE DropID=?"))
				{
					pcDB->BindParameterInput(1, PARAMTYPE_Integer, &iDropID);
					if (pcDB->Execute() && pcDB->Fetch())
					{
						pcDB->GetData(1, PARAMTYPE_Integer, &iCountDrop, 0);
					}
				}
				pcDB->Close();
			}

			// Is Drops in SQL?
			if (!IsNull(iCountDrop))
			{
				std::vector<std::string> vItems;

				if (pcDB->Open())
				{
					if (pcDB->Prepare("SELECT * FROM DropItem WHERE DropID=? ORDER BY Chance ASC"))
					{
						pcDB->BindParameterInput(1, PARAMTYPE_Integer, &iDropID);
						if (pcDB->Execute() && pcDB->Fetch())
						{
							for (int i = 0; i < iCountDrop; i++)
							{
								char szItems[512] = { 0 };
								int iChance = 0;
								int iGoldMin = 0;
								int iGoldMax = 0;

								pcDB->GetData(3, PARAMTYPE_String, szItems, 512);
								pcDB->GetData(4, PARAMTYPE_Integer, &iChance, 0);
								pcDB->GetData(5, PARAMTYPE_Integer, &iGoldMin, 0);
								pcDB->GetData(6, PARAMTYPE_Integer, &iGoldMax, 0);

								EnemyDataItem(pMonsterInfo, szItems, iChance, iGoldMin, iGoldMax);

								// Is Max items?
								if (pMonsterInfo->iDropCount == 200)
									break;

								pcDB->Fetch();
							}
						}
					}
					pcDB->Close();
				}
			}
		}
	}
}
BOOL CServerUnit::EnemyDataItem(UnitInfo * pMonsterInfo, const char * pszItems, int iChance, int iGoldMin, int iGoldMax)
{
	if (pMonsterInfo->iDropCount == 200)
		return FALSE;

	// Gold or Air
	{
		if (STRINGCOMPAREI(pszItems, "Gold"))
		{
			pMonsterInfo->saDropData[pMonsterInfo->iDropCount].iItemID = ITEMID_Gold;
			pMonsterInfo->saDropData[pMonsterInfo->iDropCount].iPercent = iChance;
			pMonsterInfo->saDropData[pMonsterInfo->iDropCount].sGold.sMin = iGoldMin;
			pMonsterInfo->saDropData[pMonsterInfo->iDropCount].sGold.sMax = iGoldMax;
			pMonsterInfo->iDropPercentNum += iChance;
			pMonsterInfo->iDropCount++;
			return TRUE;
		}
		else if (STRINGCOMPAREI(pszItems, "Air"))
		{
			pMonsterInfo->saDropData[pMonsterInfo->iDropCount].iItemID = 0;
			pMonsterInfo->saDropData[pMonsterInfo->iDropCount].iPercent = iChance;
			pMonsterInfo->saDropData[pMonsterInfo->iDropCount].sGold.sMin = iGoldMin;
			pMonsterInfo->saDropData[pMonsterInfo->iDropCount].sGold.sMax = iGoldMax;
			pMonsterInfo->iDropPercentNum += iChance;
			pMonsterInfo->iDropCount++;
			return TRUE;
		}
	}


	std::vector<std::string> vItems = split(pszItems, ' ');

	UINT uVecSize = vItems.size() + pMonsterInfo->iDropCount;
	if (uVecSize > 200)
		uVecSize = 200;

	int iPosition = 0;

	pMonsterInfo->iDropPercentNum += iChance;

	UINT uTotalItem = uVecSize - pMonsterInfo->iDropCount;

	for (UINT u = pMonsterInfo->iDropCount; u < uVecSize; u++)
	{

		ItemData * pItem = SERVERITEM->FindItemPointerTable(vItems[iPosition++].c_str());
		if (pItem)
		{
			pMonsterInfo->saDropData[pMonsterInfo->iDropCount].iItemID = pItem->sBaseItemID.ToInt();
			pMonsterInfo->saDropData[pMonsterInfo->iDropCount].iPercent = iChance / uTotalItem;
			pMonsterInfo->saDropData[pMonsterInfo->iDropCount].sGold.sMin = iGoldMin;
			pMonsterInfo->saDropData[pMonsterInfo->iDropCount].sGold.sMax = iGoldMax;
			pMonsterInfo->iDropCount++;
			if (pMonsterInfo->iDropCount == 200)
				return FALSE;
		}
	}
	return TRUE;
}
void CServerUnit::ReadUnitNpcData(CharacterData * pCharInfo, UnitInfo *pMonInfo, char *pDialogMessage)
{
	if (!GAME_SERVER)
		return;

	int iUnitID = atoi(pCharInfo->szName);
	int iGMOnly = pCharInfo->iClanID;
	pCharInfo->iClanID = 0;

	pCharInfo->Player.szHeadModel[0] = 0;
	pCharInfo->sSize = 0;
	pCharInfo->sViewBoxZoom.sMin = 0;
	pCharInfo->sViewBoxZoom.sMax = 0;

	ZeroMemory((void*)pMonInfo, sizeof(UnitInfo));
	pMonInfo->MoveRange = 64 * 256;

	//NPC Movement Range
	if (iUnitID == 16)
		pMonInfo->MoveRange = 8 * 256;

	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_GameDB);

	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT * FROM NPCList WHERE ID=?"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_Integer, &iUnitID);

			if (pcDB->Execute() && pcDB->Fetch())
			{
				pcDB->GetData(2, PARAMTYPE_String, pCharInfo->szName, 32);
				pcDB->GetData(3, PARAMTYPE_String, pCharInfo->Player.szBodyModel, 64);

				// Messages Npc
				{
					// Set Npc Messages
					for (int i = 0; i < 4; i++)
					{
						pcDB->GetData(4 + i, PARAMTYPE_String, pDialogMessage, 128);

						// Is string and not null?
						if ((lstrlenA(pDialogMessage) > 0) && (!IsNull(pDialogMessage)))
							pMonInfo->pszaMessage[pMonInfo->iNumMessage++] = (char *)SetNpcMessage(pDialogMessage);
					}
				}

				int iEventNpc = 0;
				int iEventParam = 0;
				int iTeleport = 0;

				//NPC Event data
				pcDB->GetData(8, PARAMTYPE_Integer, &iEventNpc, 0);
				pcDB->GetData(9, PARAMTYPE_Integer, &iEventParam, 0);

				//Skill Quests
				pcDB->GetData(10, PARAMTYPE_Integer, &pMonInfo->iSkillMasterRank, 0);

				//Quest ID
				pcDB->GetData(11, PARAMTYPE_Integer, &pCharInfo->sGlow, 0);

				//Quest Type
				pcDB->GetData(12, PARAMTYPE_Integer, &pMonInfo->iQuestTypeID, 0);

				//Quest TypeSub
				pcDB->GetData(13, PARAMTYPE_Integer, &pMonInfo->iQuestSubID, 0);

				//Teleport
				pcDB->GetData(14, PARAMTYPE_Integer, &iTeleport, 0);

				//Event NPC
				switch (iEventNpc)
				{
				case NPCID_EventGirl:
					pMonInfo->iEventGirl = TRUE;
					break;

				case NPCID_ItemDistributor:
					pMonInfo->iItemBox = TRUE;
					break;

				case NPCID_Warehouse:
					pMonInfo->iWarehouse = TRUE;
					break;

				case NPCID_Force:
					pMonInfo->iMixMaster = NPCEVENTCODE_Force;
					break;

				case NPCID_CastleControl:
					pMonInfo->iCastleController = TRUE;
					if (iEventParam != 0)
						pMonInfo->iCastleController = iEventParam;
					break;

				case NPCID_Aging:
					pMonInfo->iAgeMaster = TRUE;
					break;

				case NPCID_Smelting:
					pMonInfo->iSmelting = NPCEVENTCODE_Smelting;
					break;

				case NPCID_ClanControl:
					pMonInfo->iClanController = TRUE;
					break;

				case NPCID_Teleport:
					pMonInfo->iTeleport = iTeleport;
					break;

				case NPCID_SkillMaster:
					pMonInfo->iSkillMaster = TRUE;
					break;

				case NPCID_Mixing:
					pMonInfo->iMixMaster = TRUE;
					break;

				case NPCID_Manufacturing:
					pMonInfo->iSmelting = NPCEVENTCODE_Manufacture;
					break;

				case NPCID_ResetItem:
					pMonInfo->iSmelting = NPCEVENTCODE_ResetItem;
					break;

				case NPCID_CoinShop:
					pMonInfo->iSmelting = NPCEVENTCODE_CoinShop;
					break;

				case NPCID_FuryArenaNPC:
					pMonInfo->iSmelting = NPCEVENTCODE_FuryArenaNPCTeleportCT2;
					break;

				case NPCID_FuryArenaNPCEnter:
					pMonInfo->iSmelting = NPCEVENTCODE_FuryArenaNPCEnter;
					break;

				case NPCID_SocketSystemNPCDrill:
					pMonInfo->iSmelting = NPCEVENTCODE_SocketSystemNPCDrill;
					break;

				case NPCID_SocketSystemNPCStone:
					pMonInfo->iSmelting = NPCEVENTCODE_SocketSystemNPCStone;
					break;

				case NPCID_NPCEasterEgg:
					pMonInfo->iSmelting = NPCEVENTCODE_EasterNPC;
					break;

				case NPCID_LarryQuests:
					pMonInfo->iSmelting = NPCEVENTCODE_LarryQuestsNPC;
					break;

				case NPCID_IhinEvent:
					pMonInfo->iSmelting = NPCEVENTCODE_IhinEvent;
					break;

				case NPCID_MarinaQuests:
					pMonInfo->iSmelting = NPCEVENTCODE_MarinaQuestsNPC;
					break;

				case NPCID_RudolphXmas:
					pMonInfo->iSmelting = NPCEVENTCODE_RudolphXmasNPC;
					break;

				case NPCID_WarpGate:
					pMonInfo->iWarpgate = TRUE;
					if (iEventParam != 0)
						pMonInfo->iWarpgate = iEventParam;
					break;

				case NPCID_Bellatra:
					pMonInfo->iBellatraTypeNPC = TRUE;
					if (iEventParam != 0)
						pMonInfo->iBellatraTypeNPC = iEventParam;
					break;

				default:
					break;
				}

				// Weapon Shop
				{
					char szShopBuffer[512] = { 0 };
					ItemData * pItem = NULL;
					pcDB->GetData(15, PARAMTYPE_String, szShopBuffer, 512);
					std::vector<std::string> strShopItems = split(szShopBuffer, ' ');

					for (auto v : strShopItems)
					{
						pItem = SERVERITEM->FindItemPointerTable(v.c_str());

						if (pItem)
							pMonInfo->dwaWeaponShop[pMonInfo->iWeaponShopCounter++] = pItem->sBaseItemID.ToInt();

						if (pMonInfo->iWeaponShopCounter == 32)
							break;
					}
				}

				// Defense Shop
				{
					char szShopBuffer[512] = { 0 };
					ItemData * pItem = NULL;
					pcDB->GetData(16, PARAMTYPE_String, szShopBuffer, 512);
					std::vector<std::string> strShopItems = split(szShopBuffer, ' ');

					for (auto v : strShopItems)
					{
						pItem = SERVERITEM->FindItemPointerTable(v.c_str());

						if (pItem)
							pMonInfo->dwaDefenseShop[pMonInfo->iDefenseShopCounter++] = pItem->sBaseItemID.ToInt();

						if (pMonInfo->iDefenseShopCounter == 32)
							break;
					}
				}

				// Misc Shop
				{
					char szShopBuffer[512] = { 0 };
					ItemData * pItem = NULL;
					pcDB->GetData(17, PARAMTYPE_String, szShopBuffer, 512);
					std::vector<std::string> strShopItems = split(szShopBuffer, ' ');

					for (auto v : strShopItems)
					{
						pItem = SERVERITEM->FindItemPointerTable(v.c_str());
						if (pItem)
							pMonInfo->dwaMiscShop[pMonInfo->iMiscShopCounter++] = pItem->sBaseItemID.ToInt();

						if (pMonInfo->iMiscShopCounter == 32)
							break;
					}
				}

				// GM Only
				pMonInfo->bGMOnly = iGMOnly;

				// Set pcUnitData pointer
				pCharInfo->psUnitInfo = (UnitInfo*)pMonInfo;
			}
		}

		pcDB->Close();
	}
}
const char *CServerUnit::SetNpcMessage(const char *pDialogMessage)
{
	DWORD dwCode = GetCodebyName((char *)pDialogMessage);

	for (auto s : m_sMessage)
	{
		if (dwCode == s.first && STRINGCOMPAREI(pDialogMessage, s.second.c_str()))
			return pDialogMessage;
	}

	m_sMessage.insert(make_pair(dwCode, pDialogMessage));

	return pDialogMessage;
}