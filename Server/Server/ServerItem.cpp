#include "StdAfx.h"
#include "serveritem.h"
#include "SrcServer/onserver.h"

CServerItem::CServerItem()
{

}
CServerItem::~CServerItem()
{

}

void CServerItem::Init()
{
	Load();
}
void CServerItem::Shutdown()
{
	for (auto &v : m_vItemTable)
	{
		DELET(v);
	}

	m_vItemTable.clear();

	for (auto & v : m_vAllocItemTable)
	{
		DELET(v);
	}

	m_vAllocItemTable.clear();
}
void CServerItem::OnUnLoadUser(User * pcUser)
{
	UpdateItemTimer(pcUser);
}
void CServerItem::UpdateItemTimer(User * pcUser)
{
	if (GAME_SERVER)
	{
		for (int i = 0; i < PREMIUM_ITEM_TOTAL; i++)
		{
			ItemPremium * psItem = &pcUser->sPremiumData.saItemList[i];

			if (psItem->eType != ITEMTIMERTYPE_None)
			{
				if (psItem->dwTimeLeft > 2)
					SQLUpdateItemTimer(pcUser, psItem->eType, psItem->dwTimeLeft);
				else
				{
					SQLDeleteItemTimer(pcUser, psItem->dwCode);
					SERVERLOG->OnLogItemEx(pcUser, ITEMLOGID_PremiumTimerOver, "[%s](%s) Item Premium Over [%d][0x%08X][%d]", pcUser->szAccountName,
						SERVERCHARACTER->GetCharacterName(pcUser), psItem->eType, psItem->dwCode, psItem->dwTimeTotal);

					psItem->eType = ITEMTIMERTYPE_None;
				}
			}
		}
	}
}
DefinitionItem *CServerItem::FindItemDefByCode(DWORD dwCode, int iUnique)
{
	for (auto & v : m_vItemTable)
	{
		if (iUnique)
		{
			if (v->sItem.sItemID.ToInt() == dwCode && v->sItem.iItemUniqueID == iUnique)
				return v;
		}
		else
		{
			if (v->sItem.sItemID.ToInt() == dwCode && !v->sItem.iItemUniqueID)
				return v;
		}
	}

	return nullptr;
}
DefinitionItem *CServerItem::FindItemDefByCode(const char * pszCode, int iUnique)
{
	ItemData * psItemData = FindItemPointerTable(pszCode);

	if (psItemData)
	{
		return FindItemDefByCode(psItemData->sBaseItemID.ToInt(), iUnique);
	}

	return nullptr;
}
DefinitionItem * CServerItem::FindItemDefByLevelBase(int iItemBase, int iLevel)
{
	for (auto & psDefItem : m_vItemTable)
	{
		if (psDefItem->sItem.sItemID.ToItemType() == iItemBase && psDefItem->sItem.iLevel == iLevel)
			return psDefItem;
	}

	return nullptr;
}
void CServerItem::CreateItem(Item * psItem, DefinitionItem * psDefItem, int iClass, BOOL IsPerfect)
{
	CopyMemory(psItem, &psDefItem->sItem, sizeof(Item));

	// Interrity
	if (psDefItem->sIntegrity.sMin)
	{
		if (psDefItem->sIntegrity.sMax)
			psItem->sIntegrity.sMax = IsPerfect ? psDefItem->sIntegrity.sMax : RandomS(psDefItem->sIntegrity.sMin, psDefItem->sIntegrity.sMax);
		else
			psItem->sIntegrity.sMax = psDefItem->sIntegrity.sMin;

		psItem->sIntegrity.sMin = IsPerfect ? psItem->sIntegrity.sMax : RandomS(psItem->sIntegrity.sMax / 2, psItem->sIntegrity.sMax);
	}

	//Element
	for (int i = 0; i < 8; i++)
	{
		if (psDefItem->saElementalDef[i].sMax)
			psItem->saElementalDef[i] = IsPerfect ? psDefItem->saElementalDef[i].sMax : psDefItem->saElementalDef[i].RandomValue();
		else
			psItem->saElementalDef[i] = psDefItem->saElementalDef[i].sMin;
	}

	//AttackDamgae
	if (psDefItem->sDamage[1] || psDefItem->sDamage[3])
	{
		psItem->sDamage.sMin = IsPerfect ? psDefItem->sDamage[1] : RandomS(psDefItem->sDamage[0], psDefItem->sDamage[1]);
		psItem->sDamage.sMax = IsPerfect ? psDefItem->sDamage[3] : RandomS(psDefItem->sDamage[2], psDefItem->sDamage[3]);
	}

	//Attack Rating
	if (psDefItem->sAttack_Rating[1])
		psItem->iAttackRating = IsPerfect ? psDefItem->sAttack_Rating[1] : RandomS(psDefItem->sAttack_Rating[0], psDefItem->sAttack_Rating[1]);
	else
		psItem->iAttackRating = psDefItem->sAttack_Rating[0];

	//Absorb
	if (psDefItem->fAbsorb[1] != 0)
		psItem->fAbsorbRating = IsPerfect ? psDefItem->fAbsorb[1] : RandomF(psDefItem->fAbsorb[0], psDefItem->fAbsorb[1]);
	else
		psItem->fAbsorbRating = psDefItem->fAbsorb[0];

	//Defence
	if (psDefItem->sDefence[1])
		psItem->iDefenseRating = IsPerfect ? psDefItem->sDefence[1] : RandomS(psDefItem->sDefence[0], psDefItem->sDefence[1]);
	else
		psItem->iDefenseRating = psDefItem->sDefence[0];

	//Block
	if (psDefItem->fBlock_Rating[1] != 0)
		psItem->fBlockRating = IsPerfect ? psDefItem->fBlock_Rating[1] : RandomF(psDefItem->fBlock_Rating[0], psDefItem->fBlock_Rating[1]);
	else
		psItem->fBlockRating = psDefItem->fBlock_Rating[0];

	//Moveent Speed
	if (psDefItem->fSpeed[1] != 0)
		psItem->fMovementSpeed = IsPerfect ? psDefItem->fSpeed[1] : RandomF(psDefItem->fSpeed[0], psDefItem->fSpeed[1]);
	else
		psItem->fMovementSpeed = psDefItem->fSpeed[0];

	//Mana Regen
	if (psDefItem->fMana_Regen[1] != 0)
		psItem->fMPRegen = IsPerfect ? psDefItem->fMana_Regen[1] : RandomF(psDefItem->fMana_Regen[0], psDefItem->fMana_Regen[1]);
	else
		psItem->fMPRegen = psDefItem->fMana_Regen[0];

	//HP Regen
	if (psDefItem->fLife_Regen[1] != 0)
		psItem->fHPRegen = IsPerfect ? psDefItem->fLife_Regen[1] : RandomF(psDefItem->fLife_Regen[0], psDefItem->fLife_Regen[1]);
	else
		psItem->fHPRegen = psDefItem->fLife_Regen[0];

	//STM Regen
	if (psDefItem->fStamina_Regen[1] != 0)
		psItem->fSPRegen = IsPerfect ? psDefItem->fStamina_Regen[1] : RandomF(psDefItem->fStamina_Regen[0], psDefItem->fStamina_Regen[1]);
	else
		psItem->fSPRegen = psDefItem->fStamina_Regen[0];

	//HP Inc
	if (psDefItem->Increase_Life[1])
		psItem->fAddHP = IsPerfect ? (float)psDefItem->Increase_Life[1] : (float)RandomI(psDefItem->Increase_Life[0], psDefItem->Increase_Life[1]);
	else
		psItem->fAddHP = (float)psDefItem->Increase_Life[0];

	//MP Inc
	if (psDefItem->Increase_Mana[1])
		psItem->fAddMP = IsPerfect ? (float)psDefItem->Increase_Mana[1] : (float)RandomI(psDefItem->Increase_Mana[0], psDefItem->Increase_Mana[1]);
	else
		psItem->fAddMP = (float)psDefItem->Increase_Mana[0];

	//STM Inc
	if (psDefItem->Increase_Stamina[1])
		psItem->fAddSP = IsPerfect ? (float)psDefItem->Increase_Stamina[1] : (float)RandomI(psDefItem->Increase_Stamina[0], psDefItem->Increase_Stamina[1]);
	else
		psItem->fAddSP = (float)psDefItem->Increase_Stamina[0];

	if (iClass > 0)
	{
		CharacterClassData * psCharacterClassData = GetItemSpecClassJob(iClass, psDefItem);

		if (psCharacterClassData)
		{
			int iClassBit = psCharacterClassData->iClassBit;

			BOOL bClass = FALSE;

			for (int i = 0; i < psDefItem->JobBitCodeRandomCount; i++)
			{
				if (psDefItem->dwJobBitCode_Random[i] == iClassBit)
				{
					bClass = TRUE;
					break;
				}
			}

			if (bClass == FALSE)
			{
				if (iClassBit != psItem->eSpecialization)
					iClass = 0;
			}
		}
	}

	if (psItem->eSpecialization || psDefItem->JobBitCodeRandomCount || iClass)
	{
		if (rand() % 10 <= 3 || iClass)
		{
			int irnd = rand() % 10;

			int iClassBit = psItem->eSpecialization;

			if (rand() % 10 < 3 && psDefItem->JobBitCodeRandomCount)
				psItem->eSpecialization = 0;

			if (!psItem->eSpecialization && psDefItem->JobBitCodeRandomCount)
			{
				int iClassBit = psDefItem->dwJobBitCode_Random[rand() % psDefItem->JobBitCodeRandomCount];
				psItem->eSpecialization = iClassBit;
			}

			if (iClass > 0)
			{
				CharacterClassData * psCharacterClassData = GetItemSpecClassJob(iClass, psDefItem);

				if (psCharacterClassData)
					psItem->eSpecialization = psCharacterClassData->iClassBit;
			}

			if (psItem->eSpecialization)
				psItem->iSalePrice += (psItem->iSalePrice * 2) / 10;

			OnSetItem(psItem, IsPerfect);

			//Spec Abs
			if (psDefItem->fSpecial_Absorb[1] != 0)
				psItem->sSpecData.fSpecAbsorbRating = IsPerfect ? psDefItem->fSpecial_Absorb[1] : RandomF(psDefItem->fSpecial_Absorb[0], psDefItem->fSpecial_Absorb[1]);
			else
				psItem->sSpecData.fSpecAbsorbRating = psDefItem->fSpecial_Absorb[0];

			//spec Def
			if (psDefItem->sSpecial_Defence[1])
				psItem->sSpecData.iSpecDefenseRating = IsPerfect ? psDefItem->sSpecial_Defence[1] : RandomI(psDefItem->sSpecial_Defence[0], psDefItem->sSpecial_Defence[1]);
			else
				psItem->sSpecData.iSpecDefenseRating = psDefItem->sSpecial_Defence[0];

			//spec move speed
			if (psDefItem->fSpecial_fSpeed[1] != 0)
				psItem->sSpecData.fSpecMovementSpeed = IsPerfect ? psDefItem->fSpecial_fSpeed[1] : RandomF(psDefItem->fSpecial_fSpeed[0], psDefItem->fSpecial_fSpeed[1]);
			else
				psItem->sSpecData.fSpecMovementSpeed = psDefItem->fSpecial_fSpeed[0];

			//spec mastery
			if (psDefItem->fSpecial_Magic_Mastery[1] != 0)
				psItem->sSpecData.fSpecMagicMastery = IsPerfect ? psDefItem->fSpecial_Magic_Mastery[1] : RandomF(psDefItem->fSpecial_Magic_Mastery[0], psDefItem->fSpecial_Magic_Mastery[1]);
			else
				psItem->sSpecData.fSpecMagicMastery = psDefItem->fSpecial_Magic_Mastery[0];

			//spec MP Regen
			if (psDefItem->fSpecial_Mana_Regen[1] != 0)
				psItem->sSpecData.fSpecMPRegen = IsPerfect ? psDefItem->fSpecial_Mana_Regen[1] : RandomF(psDefItem->fSpecial_Mana_Regen[0], psDefItem->fSpecial_Mana_Regen[1]);
			else
				psItem->sSpecData.fSpecMPRegen = psDefItem->fSpecial_Mana_Regen[0];

			//spec Attack Ratring
			if (psDefItem->Lev_Attack_Rating[1])
				psItem->sSpecData.iSpecAttackRatingDiv = IsPerfect ? psDefItem->Lev_Attack_Rating[0] : RandomI(psDefItem->Lev_Attack_Rating[0], psDefItem->Lev_Attack_Rating[1]);
			else
				psItem->sSpecData.iSpecAttackRatingDiv = psDefItem->Lev_Attack_Rating[0];
		}
		else
			psItem->eSpecialization = 0;
	}

	if (!psItem->eSpecialization)
		ZeroMemory(&psItem->sSpecData, sizeof(SpecItemData));

	ReformItem(psItem);
}
void CServerItem::CreateItem(User * pcUser, DWORD iItem, int iCount)
{
	auto pItem = FindItemDefByCode(iItem);

	if (pItem)
	{
		LootItem sLootItem;
		CreateItem(&sLootItem.sItem, pItem);

		if (sLootItem.sItem.sItemID.ToItemBase() == ITEMBASE_Potion)
		{
			sLootItem.sItem.iPotionCount = iCount;
		}

		SendItemData(pcUser, &sLootItem.sItem);
	}
}
void CServerItem::CreateItem(User * pcUser, DWORD iItem, int iClass, int iUnique)
{
	auto pDefItem = FindItemDefByCode(iItem,iUnique);

	if (pDefItem)
	{
		LootItem sLootItem;
		CreateItem(&sLootItem.sItem, pDefItem, iClass);

		SendItemData(pcUser, &sLootItem.sItem);
	}
}
void CServerItem::CreatePerfectItem(Item * psOut, DefinitionItem * psIn, int iSpeck)
{
	CreateItem(psOut, psIn, iSpeck, TRUE);

	psOut->bPerfectItem = TRUE;
}
void CServerItem::UpgradeNewItem(Item * psItemOld, Item * psItemNew)
{
	if (psItemOld->eCraftType == ITEMCRAFTTYPE_Mixing)
	{
		psItemNew->eCraftType = ITEMCRAFTTYPE_Mixing;
		//MIXHANDLER->SetItemMixByMixName(psItemNew, psItemOld->eMixTypeName);
		psItemNew->eMixEffect = psItemOld->eMixEffect;
		psItemNew->sMixID = psItemOld->sMixID;
		ValidateItem(psItemNew);
	}
	else if (psItemOld->eCraftType == ITEMCRAFTTYPE_Aging)
	{
		if (psItemNew->sItemID.ToItemType() == ITEMTYPE_Boots || psItemNew->sItemID.ToItemType() == ITEMTYPE_Gauntlets || psItemNew->sItemID.ToItemType() == ITEMTYPE_Bracelets)
			return;

		psItemNew->eCraftType = ITEMCRAFTTYPE_Aging;
		AGEHANDLE->OnUpAgeHandler(psItemNew, (int)psItemOld->sAgeLevel);
		psItemNew->bMaturing = psItemOld->bMaturing;
		psItemNew->sMatureBar = psItemOld->sMatureBar;
		ValidateItem(psItemNew);
	}
}
BOOL CServerItem::CreateItemByName(LootItem * psLootItem, const char *pszCode, int iCount)
{
	auto pDefItem = FindItemDefByCode(pszCode);

	if (pDefItem)
	{
		CreateItem(&psLootItem->sItem, pDefItem);

		if (pDefItem->sItem.sItemID.ToItemBase() == ITEMBASE_Potion)
		{
			psLootItem->sItem.iPotionCount = iCount;
		}

		return TRUE;
	}

	return FALSE;
}
BOOL CServerItem::T2ItemCheck(User *pcUser, int iRank)
{
	if (pcUser->sCharacterData.iRank == 1 && iRank == 2)
	{
		EItemID iIemID = ITEMID_EmperorRing;

		if (pcUser->sCharacterData.iClass == CHARACTERCLASS_Magician ||
			pcUser->sCharacterData.iClass == CHARACTERCLASS_Priestess ||
			pcUser->sCharacterData.iClass == CHARACTERCLASS_Shaman)

			iIemID = ITEMID_ArcaneRing;

		else if (pcUser->sCharacterData.iClass == CHARACTERCLASS_Atalanta ||
			pcUser->sCharacterData.iClass == CHARACTERCLASS_Archer ||
			pcUser->sCharacterData.iClass == CHARACTERCLASS_Assassin)
			iIemID = ITEMID_FocusRing;

		if (IsItemInventory(pcUser, iIemID) == FALSE)
		{
			auto pItem = FindItemDefByCode(iIemID);

			if (pItem)
			{
				LootItem sLootItem;
				CreateItem(&sLootItem.sItem, pItem);

				sLootItem.sItem.eCraftType = ITEMCRAFTTYPE_QuestWeapon;
				ValidateItem(&sLootItem.sItem);

				SendItemData(pcUser, &sLootItem.sItem);

				return TRUE;
			}
		}
	}

	return FALSE;
}
void CServerItem::SendItemData(User *pcUser, Item *psItem, BOOL bNewItem)
{
	//Is user alive and have item?
	if (pcUser && psItem)
	{
		PacketItem sPacket;

		ZeroMemory(&sPacket, sizeof(PacketItem));
		sPacket.iLength = sizeof(PacketItem);
		sPacket.iHeader = PKTHDR_NewItem;

		CopyMemory(&sPacket.sItem, psItem, sizeof(Item));

		if (psItem->sItemID.ToItemID() == ITEMID_Gold)
		{
			pcUser->iGoldOut += psItem->iGold;
			sPacket.iX = TICKCOUNT;
			sPacket.iY = sPacket.sItem.iChk2;
			sPacket.iZ = pcUser->iGoldOut ^ (sPacket.iX + sPacket.iY);
		}

		ValidateItem(&sPacket.sItem);
		RegisterItemSecCode(pcUser, &sPacket, bNewItem);
		SENDPACKET(pcUser, &sPacket);
	}
}
BOOL CServerItem::ValidateItem(Item * psItem, BOOL iCheck)
{
	return iCheck ? (CheckMixItem(psItem) && CheckItemForm(psItem)) ? TRUE : FALSE : ReformItem(psItem);
}

#define ITEM_SecCode_0	0x536c56ba
#define ITEM_SecCode_1	0x9ab536cd
#define ITEM_SecCode_2	0xc6abce56

void CServerItem::RegisterItemSecCode(User * pcUser, PacketItem * psPacket, BOOL bNew)
{
	DWORD iChk = psPacket->sItem.iChk2^psPacket->sItem.iChk1;

	DWORD dwKey = (TICKCOUNT & 0xFFFF) ^ iChk;
	dwKey = dwKey ^ (dwKey << 10);

	if (psPacket->sItem.sItemID.ToItemBase() == ITEMBASE_Potion)
	{
		dwKey &= 0xFFFF0000;
		int iCount = psPacket->sItem.iPotionCount;
		iCount = iCount == 0 ? 1 : iCount;
		dwKey |= (iCount & 0xFFFF) ^ 0x3c15;
	}

	DWORD dwSecCode = (SERVER_CODE << 16) | (pcUser->SndItemSecCodeCount & 0xFFFF);

	psPacket->dwSecCode[0] = (bNew) ? dwSecCode |= 0x8000000 : dwSecCode &= 0x7FFFFFFF;
	psPacket->dwSecCode[1] = iChk ^ ((pcUser->dwHashCharacterName & 0xFFFF) | (pcUser->iID << 16));
	psPacket->dwSecCode[2] = psPacket->sItem.iGold^psPacket->dwSecCode[0] ^ psPacket->dwSecCode[1];
	psPacket->dwSecCode[3] = dwKey;

	psPacket->dwSecCode[0] ^= (ITEM_SecCode_0 ^ RegistEnterKey(dwKey^pcUser->iID, 0));
	psPacket->dwSecCode[1] ^= (ITEM_SecCode_1 ^ RegistEnterKey(dwKey^pcUser->iID, 1));
	psPacket->dwSecCode[2] ^= (ITEM_SecCode_2 ^ RegistEnterKey(dwKey^pcUser->iID, 2));

	pcUser->SndItemSecCodeCount++;
}
BOOL CServerItem::ValiSecCode(User * pcUser, int iItemID, int iChk1, int iChk2, int iGold, DWORD dwSecCode[4], int &iPotionCount)
{
	DWORD dwKey = dwSecCode[3];

	iPotionCount = (iItemID & 0xFF000000) == ITEMBASE_Potion ? (dwKey & 0xFFFF) ^ 0x3c15 : 0;

	dwSecCode[0] = dwSecCode[0] ^ (ITEM_SecCode_0^RegistEnterKey(dwKey ^ pcUser->iID, 0));
	dwSecCode[1] = dwSecCode[1] ^ (ITEM_SecCode_1^RegistEnterKey(dwKey ^ pcUser->iID, 1));
	dwSecCode[2] = dwSecCode[2] ^ (ITEM_SecCode_2^RegistEnterKey(dwKey ^ pcUser->iID, 2));

	DWORD dwChk = (iChk1 ^ iChk2) ^ ((pcUser->dwHashCharacterName & 0xFFFF) | (pcUser->iID << 16));

	if (dwSecCode[1] == dwChk)
	{
		dwChk = iGold ^ dwSecCode[0] ^ dwSecCode[1];

		if (dwSecCode[2] == dwChk)
		{
			return TRUE;
		}
	}

	return FALSE;
}
DWORD CServerItem::RegistEnterKey(DWORD dwCode, int iv)
{
	static DWORD sItem_SecCode[16] = 
	{
		0x6794bca6 ,		//0
		0x78645fe3 ,		//1
		0xcea82934 ,		//2
		0x56fdca87 ,		//3
		0x357d3653 ,		//4
		0xf3487eba ,		//5
		0x3478978f ,		//6
		0x6793fbc2 ,		//7
		0x5842eec6 ,		//8
		0x257ecdb5 ,		//9
		0x579cbec5 ,		//A
		0x985612ab ,		//B
		0x5487cc56 ,		//C
		0xba7d4553 ,		//D
		0xeca53b96 ,		//E
		0xb5c549ce			//F
	};

	return sItem_SecCode[(dwCode + iv) & 0xF];
}
void CServerItem::AddPremiumUse(User * pcUser, ItemPremium * psItem)
{
	if (pcUser && psItem)
	{
		for (int i = 0; i < PREMIUM_ITEM_TOTAL; i++)
		{
			ItemPremium * pc = pcUser->sPremiumData.saItemList + i;

			if (pc->eType == ITEMTIMERTYPE_None)
			{
				CopyMemory(pc, psItem, sizeof(ItemPremium));
				break;
			}
		}
	}
}
ItemPremium * CServerItem::GetPremiumUse(User * pcUser, EItemTimerType eType)
{
	if (pcUser)
	{
		for (int i = 0; i < PREMIUM_ITEM_TOTAL; i++)
		{
			if (pcUser->sPremiumData.saItemList[i].eType == eType)
			{
				if (pcUser->sPremiumData.saItemList[i].dwTimeLeft)
					return &pcUser->sPremiumData.saItemList[i];
				else
					return NULL;
			}
		}
	}

	return NULL;
}
ItemPremium * CServerItem::GetPremiumUse(User * pcUser, EItemID eID)
{
	if (pcUser)
	{
		for (int i = 0; i < PREMIUM_ITEM_TOTAL; i++)
		{
			if (pcUser->sPremiumData.saItemList[i].dwCode == eID)
				return &pcUser->sPremiumData.saItemList[i];
		}
	}

	return NULL;
}
void CServerItem::ProcessIntegrity(User * pcUser, EIntegrityUpdate eUpdate)
{
	PacketUpdateIntegrity sPacket;
	sPacket.iHeader = PKTHDR_IntegrityUpdateItem;
	sPacket.iLength = sizeof(PacketUpdateIntegrity);
	sPacket.eUpdate = eUpdate;
	SENDPACKET(pcUser, &sPacket);
}
void CServerItem::MakeInvenItem(User *pcUser, PacketCharacterRecordData *paPacket)
{
	if (paPacket->iItemCount > RECORD_ITEM_MAX)
		paPacket->iItemCount = RECORD_ITEM_MAX;

	if (paPacket->iDropItemCount > THROW_ITEM_INFO_MAX)
		paPacket->iDropItemCount = THROW_ITEM_INFO_MAX;

	BYTE *baData = paPacket->baData;

	DropItemData sDropItemData[64];
	int			 iDropItemCount = 0;
	int			 uSizeBuffer = 0;

	ZeroMemory(pcUser->ServerPotion, sizeof(pcUser->ServerPotion));

	for (int i = 0; i < paPacket->iItemCount; i++)
	{
		//Inventory Limit...
		if (i >= 200)
			break;

		RecordItem sRecItem;
		DecodeCompress_ItemPotion(pcUser, (BYTE *)baData, (BYTE *)&sRecItem, 44, paPacket);

		if (sRecItem.sItem.sItemID.ToInt() &&
			sRecItem.sItem.iChk1 &&
			sRecItem.sItem.iChk2 &&
			sRecItem.sItem.sItemID.ToItemBase() != ITEMBASE_Potion)
		{
			BOOL bRet = FALSE;

			for (int j = 0; j < paPacket->iDropItemCount; j++)
			{
				DropItemData * pDropItem = paPacket->sDropItemData + j;

				if (pDropItem->dwCode == sRecItem.sItem.sItemID.ToInt() &&
					pDropItem->dwKey == sRecItem.sItem.iChk1 &&
					pDropItem->dwSum == sRecItem.sItem.iChk2)
				{
					if (iDropItemCount < THROW_ITEM_INFO_MAX)
					{
						CopyMemory(&sDropItemData[iDropItemCount++], pDropItem, sizeof(DropItemData));

						bRet = TRUE;
						break;
					}
				}
			}

			if (bRet == FALSE)
			{
				//Error
				BOOL bError = FALSE;
				for (int j = 0; j < i; j++)
				{
					DropItemData *pDropItem = pcUser->InvenItemInfo + j;

					if (pDropItem->dwCode &&
						pDropItem->dwCode == sRecItem.sItem.sItemID.ToInt() &&
						pDropItem->dwKey == sRecItem.sItem.iChk1 &&
						pDropItem->dwSum == sRecItem.sItem.iChk2)
					{
						//LOG
						//*INVENTORY
						//copy Item
						bError = TRUE;
						break;
					}
				}

				if (bError == FALSE)
				{
					DropItemData *pDropItem = pcUser->InvenItemInfo + i;

					pDropItem->dwCode = sRecItem.sItem.sItemID.ToInt();
					pDropItem->dwKey = sRecItem.sItem.iChk1;
					pDropItem->dwSum = sRecItem.sItem.iChk2;
				}
			}
		}

		int uSize = ((int *)baData)[0];
		uSizeBuffer += uSize;
		baData += uSize;

		if (uSizeBuffer >= (sizeof(RecordItem) * 200))
			break;
	}

	pcUser->ThrowItemCount = iDropItemCount;

	CopyMemory(pcUser->ThrowItemInfo, sDropItemData, sizeof(DropItemData) * pcUser->ThrowItemCount);
}

BOOL CServerItem::CheckInvenItem(PacketCharacterRecordData *paPacket)
{
	BYTE *pbData = paPacket->baData;

	int uSizeTotal = 0;

	for (int i = 0; i < paPacket->iItemCount; i++)
	{
		int uSize = ((int *)pbData)[0];
		uSizeTotal += uSize;
		pbData += uSize;

		if (uSizeTotal > paPacket->iDataSize || uSizeTotal < 0)
			return FALSE;
	}

	return uSizeTotal == paPacket->iDataSize ? TRUE : FALSE;
}
void CServerItem::DecodeItemsData(BYTE *pItemData, BYTE *pItemDest, int iSize)
{
	int iCount = 4;
	int uSize = ((int *)pItemData)[0];
	int iDestCount = 0;

	while (iCount < uSize)
	{
		if (pItemData[iCount] & 0x80)
		{
			int iLength = pItemData[iCount++] & 0x7F;

			for (int i = 0; i < iLength; i++)
			{
				if (iDestCount >= iSize)
					return;
				pItemDest[iDestCount++] = 0;
			}
		}
		else
		{
			int iLength = pItemData[iCount++] & 0x7F;

			for (int i = 0; i < iLength; i++)
			{
				if (iDestCount >= iSize)
					return;
				pItemDest[iDestCount++] = pItemData[iCount++];
			}
		}
	}
}
BOOL CServerItem::GetDropPotion(User * pcUser, int iItemID)
{
	for (int i = 0; i < pcUser->TradePotionInfoCount; i++)
	{
		if (pcUser->dwTradePotionInfo[i] == iItemID)
			return TRUE;
	}

	return FALSE;
}
int CServerItem::AddPotion(User *pcUser, DWORD dwCode, int iPotionCount)
{
	Point2D sPosition = Point2D(-1, -1);

	switch (dwCode)
	{
	case ITEMTYPE_HealthPotion | ITEMINDEX_01:
		sPosition = Point2D(0, 0);
		break;
	case ITEMTYPE_HealthPotion | ITEMINDEX_02:
		sPosition = Point2D(0, 1);
		break;
	case ITEMTYPE_HealthPotion | ITEMINDEX_03:
		sPosition = Point2D(0, 2);
		break;
	case ITEMTYPE_HealthPotion | ITEMINDEX_04:
		sPosition = Point2D(0, 3);
		break;
	case ITEMTYPE_ManaPotion | ITEMINDEX_01:
		sPosition = Point2D(1, 0);
		break;
	case ITEMTYPE_ManaPotion | ITEMINDEX_02:
		sPosition = Point2D(1, 1);
		break;
	case ITEMTYPE_ManaPotion | ITEMINDEX_03:
		sPosition = Point2D(1, 2);
		break;
	case ITEMTYPE_ManaPotion | ITEMINDEX_04:
		sPosition = Point2D(1, 3);
		break;
	case ITEMTYPE_StaminaPotion | ITEMINDEX_01:
		sPosition = Point2D(2, 0);
		break;
	case ITEMTYPE_StaminaPotion | ITEMINDEX_02:
		sPosition = Point2D(2, 1);
		break;
	case ITEMTYPE_StaminaPotion | ITEMINDEX_03:
		sPosition = Point2D(2, 2);
		break;
	case ITEMTYPE_StaminaPotion | ITEMINDEX_04:
		sPosition = Point2D(2, 3);
		break;
	}

	if (sPosition.iX >= 0 && sPosition.iY >= 0 && iPotionCount > 0)
	{
		int iCount = pcUser->ServerPotion[sPosition.iX][sPosition.iY] + iPotionCount;

		if (iCount < 0)
		{
			pcUser->ServerPotion[sPosition.iX][sPosition.iY] = 0;
			return -1;
		}

		pcUser->ServerPotion[sPosition.iX][sPosition.iY] = iCount;

		return iCount;
	}

	return -1;
}
void CServerItem::ComparePotion(User *pcUser, CharacterSave *pCharacterSave)
{
	if (pCharacterSave->sPotionUpdate[0] && pCharacterSave->sPotionUpdate[0] == pCharacterSave->sPotionUpdate[1])
	{
		BOOL bErr = FALSE;

		int sOverPotion[3] = { 0,0,0 };

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (((int)pCharacterSave->sPotionCount[i][j]) < pcUser->ServerPotion[i][j])
				{
					// Error CopyPotion;
					int iPotionCount = pcUser->ServerPotion[i][j] - pCharacterSave->sPotionCount[i][j];
					sOverPotion[i] += iPotionCount;
					bErr = TRUE;
				}
			}
		}

		if (bErr)
		{
			// LOG

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					pcUser->ServerPotion[i][j] = pCharacterSave->sPotionCount[i][j];

					if (pcUser->ServerPotion[i][j] < 0)
						pcUser->ServerPotion[i][j] = 0;
				}
			}
		}
	}
}
void CServerItem::SavePotion(User *pcUser, CharacterSave *pCharacterSave)
{
	if (pcUser)
	{
		pCharacterSave->sPotionUpdate[0] = 1;
		pCharacterSave->sPotionUpdate[1] = 0;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 4; j++)
				pCharacterSave->sPotionCount[i][j] = (short)pcUser->ServerPotion[i][j];
		}
	}
}
void CServerItem::SaveForce(User *pcUser, CharacterSave *pCharacterSave)
{
	if (pcUser)
	{
		if (pcUser->dwForceOrb_SaveTime && pcUser->dwForceOrb_SaveTime > SERVER_GAMETIME)
		{
			int iItemID = pcUser->dwForceOrb_SaveCode & 0x0000FFFF;
			int isec = (pcUser->dwForceOrb_SaveTime - SERVER_GAMETIME) / 1000;

			pCharacterSave->wForceOrbUsing[0] = (WORD)(iItemID);
			pCharacterSave->wForceOrbUsing[1] = (WORD)(isec);
		}
	}
}
void CServerItem::LoadForce(User *pcUser, CharacterSave *pCharacterSave)
{
	if (pcUser)
	{
		if (pCharacterSave->wForceOrbUsing[0] && pCharacterSave->wForceOrbUsing[1])
		{
			int iID = pCharacterSave->wForceOrbUsing[0] >> 8;

			iID--;

			if (iID >= 0 && iID < 16)
			{
				if (pCharacterSave->wForceOrbUsing[1] <= ForceOrbUseTime[iID])
				{
					pcUser->dwForceOrb_SaveCode = sinFO1 + pCharacterSave->wForceOrbUsing[0];
					pcUser->dwForceOrb_SaveTime = SERVER_GAMETIME + pCharacterSave->wForceOrbUsing[1] * 1000;
					pcUser->dwForceOrb_SaveDamage = ForceOrbDamage[iID];
				}
			}
		}
	}
}
BOOL CServerItem::SaveItemData(Item * psItem)
{
	EItemBase iItemBase = psItem->sItemID.ToItemBase();

	if (((psItem->iChk1 == 0) && (psItem->iChk2 == 0)) || (psItem->sItemID.ToItemID() == ITEMID_None))
		return FALSE;

	if ((iItemBase != ITEMBASE_Weapon) && (iItemBase != ITEMBASE_Defense) && (iItemBase != ITEMBASE_Accessory))
		return FALSE;

	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_LogDB);
	if (pcDB->Open())
	{
		if (pcDB->Prepare("INSERT INTO ItemCreateLog([ItemID],[Code1],[Code2],[Item],[Date]) VALUES(?,?,?,?,GETDATE())"))
		{
			int iItemID = psItem->sItemID.ToInt();

			pcDB->BindParameterInput(1, PARAMTYPE_Integer, &iItemID);
			pcDB->BindParameterInput(2, PARAMTYPE_Integer, &psItem->iChk1);
			pcDB->BindParameterInput(3, PARAMTYPE_Integer, &psItem->iChk2);
			pcDB->BindParameterInput(4, PARAMTYPE_Binary, psItem, sizeof(Item));

			pcDB->Execute();
		}
		pcDB->Close();

		return TRUE;
	}

	return FALSE;
}
BOOL CServerItem::OnLoadItemData(ItemLoadData * psItem, const char * pszCode)
{
	BOOL bRet = FALSE;
	std::vector<std::string> v = split(pszCode, '@');

	if (v.size() == 2)
	{
		int iCode1 = atoi(v[0].c_str());
		int iCode2 = atoi(v[1].c_str());

		SQLConnection * pcDB = SQLCONNECTION(DATABASEID_LogDB);
		if (pcDB->Open())
		{
			if (pcDB->Prepare("SELECT TOP 1 Item FROM ItemCreateLog WHERE (Code1=?) AND (Code2=?)"))
			{
				pcDB->BindParameterInput(1, PARAMTYPE_Integer, &iCode1);
				pcDB->BindParameterInput(2, PARAMTYPE_Integer, &iCode2);

				if (pcDB->Execute() && pcDB->Fetch())
				{
					pcDB->GetData(1, PARAMTYPE_Binary, &psItem->sItem, sizeof(Item));
					bRet = TRUE;
				}
			}
			pcDB->Close();
		}
	}

	return bRet;
}
void CServerItem::OnLoadUser(User * pcUser)
{
	ZeroMemory(&pcUser->sPremiumData, sizeof(PacketItemPremiumData));

	pcUser->sPremiumData.iLength = sizeof(PacketItemPremiumData);
	pcUser->sPremiumData.iHeader = PKTHDR_PremiumData;

	EItemID iItemID = ITEMID_None;
	int iType = 0;
	DWORD dwTimeLeft = 0, dwTimeTotal = 0;
	int i = 0;

	iType = ITEMTIMERTYPE_ExpUp;

	if (SQLGetItemTimer(pcUser, iType, iItemID, dwTimeLeft, dwTimeTotal))
	{
		pcUser->sPremiumData.saItemList[i].eType = (EItemTimerType)iType;
		pcUser->sPremiumData.saItemList[i].dwCode = iItemID;
		pcUser->sPremiumData.saItemList[i].dwTimeLeft = dwTimeLeft;
		pcUser->sPremiumData.saItemList[i].dwTimeTotal = dwTimeTotal;
		i++;
		//SERVERNET->SendEXPPotion(pcUser, TRUE);
	}
	iType = ITEMTIMERTYPE_ThirdEye;
	if (SQLGetItemTimer(pcUser, iType, iItemID, dwTimeLeft, dwTimeTotal))
	{
		pcUser->sPremiumData.saItemList[i].eType = (EItemTimerType)iType;
		pcUser->sPremiumData.saItemList[i].dwCode = iItemID;
		pcUser->sPremiumData.saItemList[i].dwTimeLeft = dwTimeLeft;
		pcUser->sPremiumData.saItemList[i].dwTimeTotal = dwTimeTotal;
		i++;
	}
	iType = ITEMTIMERTYPE_MPDown;
	if (SQLGetItemTimer(pcUser, iType, iItemID, dwTimeLeft, dwTimeTotal))
	{
		pcUser->sPremiumData.saItemList[i].eType = (EItemTimerType)iType;
		pcUser->sPremiumData.saItemList[i].dwCode = iItemID;
		pcUser->sPremiumData.saItemList[i].dwTimeLeft = dwTimeLeft;
		pcUser->sPremiumData.saItemList[i].dwTimeTotal = dwTimeTotal;
		i++;
	}
	iType = ITEMTIMERTYPE_MPUp;
	if (SQLGetItemTimer(pcUser, iType, iItemID, dwTimeLeft, dwTimeTotal))
	{
		pcUser->sPremiumData.saItemList[i].eType = (EItemTimerType)iType;
		pcUser->sPremiumData.saItemList[i].dwCode = iItemID;
		pcUser->sPremiumData.saItemList[i].dwTimeLeft = dwTimeLeft;
		pcUser->sPremiumData.saItemList[i].dwTimeTotal = dwTimeTotal;
		i++;
	}
	iType = ITEMTIMERTYPE_HPUp;
	if (SQLGetItemTimer(pcUser, iType, iItemID, dwTimeLeft, dwTimeTotal))
	{
		pcUser->sPremiumData.saItemList[i].eType = (EItemTimerType)iType;
		pcUser->sPremiumData.saItemList[i].dwCode = iItemID;
		pcUser->sPremiumData.saItemList[i].dwTimeLeft = dwTimeLeft;
		pcUser->sPremiumData.saItemList[i].dwTimeTotal = dwTimeTotal;
		i++;
	}
	iType = ITEMTIMERTYPE_SPDown;
	if (SQLGetItemTimer(pcUser, iType, iItemID, dwTimeLeft, dwTimeTotal))
	{
		pcUser->sPremiumData.saItemList[i].eType = (EItemTimerType)iType;
		pcUser->sPremiumData.saItemList[i].dwCode = iItemID;
		pcUser->sPremiumData.saItemList[i].dwTimeLeft = dwTimeLeft;
		pcUser->sPremiumData.saItemList[i].dwTimeTotal = dwTimeTotal;
		i++;
	}
	iType = ITEMTIMERTYPE_BigHead;
	if (SQLGetItemTimer(pcUser, iType, iItemID, dwTimeLeft, dwTimeTotal))
	{
		pcUser->sPremiumData.saItemList[i].eType = (EItemTimerType)iType;
		pcUser->sPremiumData.saItemList[i].dwCode = iItemID;
		pcUser->sPremiumData.saItemList[i].dwTimeLeft = dwTimeLeft;
		pcUser->sPremiumData.saItemList[i].dwTimeTotal = dwTimeTotal;
		i++;
	}
	iType = ITEMTIMERTYPE_CartolaHat;
	if (SQLGetItemTimer(pcUser, iType, iItemID, dwTimeLeft, dwTimeTotal))
	{
		pcUser->sPremiumData.saItemList[i].eType = (EItemTimerType)iType;
		pcUser->sPremiumData.saItemList[i].dwCode = iItemID;
		pcUser->sPremiumData.saItemList[i].dwTimeLeft = dwTimeLeft;
		pcUser->sPremiumData.saItemList[i].dwTimeTotal = dwTimeTotal;
		i++;
	}
	iType = ITEMTIMERTYPE_WitchHat;
	if (SQLGetItemTimer(pcUser, iType, iItemID, dwTimeLeft, dwTimeTotal))
	{
		pcUser->sPremiumData.saItemList[i].eType = (EItemTimerType)iType;
		pcUser->sPremiumData.saItemList[i].dwCode = iItemID;
		pcUser->sPremiumData.saItemList[i].dwTimeLeft = dwTimeLeft;
		pcUser->sPremiumData.saItemList[i].dwTimeTotal = dwTimeTotal;
		i++;
	}
	iType = ITEMTIMERTYPE_PhoenixFire;
	if (SQLGetItemTimer(pcUser, iType, iItemID, dwTimeLeft, dwTimeTotal))
	{
		pcUser->sPremiumData.saItemList[i].eType = (EItemTimerType)iType;
		pcUser->sPremiumData.saItemList[i].dwCode = iItemID;
		pcUser->sPremiumData.saItemList[i].dwTimeLeft = dwTimeLeft;
		pcUser->sPremiumData.saItemList[i].dwTimeTotal = dwTimeTotal;
		i++;
	}
	iType = ITEMTIMERTYPE_PhoenixIce;
	if (SQLGetItemTimer(pcUser, iType, iItemID, dwTimeLeft, dwTimeTotal))
	{
		pcUser->sPremiumData.saItemList[i].eType = (EItemTimerType)iType;
		pcUser->sPremiumData.saItemList[i].dwCode = iItemID;
		pcUser->sPremiumData.saItemList[i].dwTimeLeft = dwTimeLeft;
		pcUser->sPremiumData.saItemList[i].dwTimeTotal = dwTimeTotal;
		i++;
	}
	iType = ITEMTIMERTYPE_PhoenixLightning;
	if (SQLGetItemTimer(pcUser, iType, iItemID, dwTimeLeft, dwTimeTotal))
	{
		pcUser->sPremiumData.saItemList[i].eType = (EItemTimerType)iType;
		pcUser->sPremiumData.saItemList[i].dwCode = iItemID;
		pcUser->sPremiumData.saItemList[i].dwTimeLeft = dwTimeLeft;
		pcUser->sPremiumData.saItemList[i].dwTimeTotal = dwTimeTotal;
		i++;
	}
	iType = ITEMTIMERTYPE_PhoenixHeal;
	if (SQLGetItemTimer(pcUser, iType, iItemID, dwTimeLeft, dwTimeTotal))
	{
		pcUser->sPremiumData.saItemList[i].eType = (EItemTimerType)iType;
		pcUser->sPremiumData.saItemList[i].dwCode = iItemID;
		pcUser->sPremiumData.saItemList[i].dwTimeLeft = dwTimeLeft;
		pcUser->sPremiumData.saItemList[i].dwTimeTotal = dwTimeTotal;
		i++;
	}
	iType = ITEMTIMERTYPE_WeightStone;
	if (SQLGetItemTimer(pcUser, iType, iItemID, dwTimeLeft, dwTimeTotal))
	{
		pcUser->sPremiumData.saItemList[i].eType = (EItemTimerType)iType;
		pcUser->sPremiumData.saItemList[i].dwCode = iItemID;
		pcUser->sPremiumData.saItemList[i].dwTimeLeft = dwTimeLeft;
		pcUser->sPremiumData.saItemList[i].dwTimeTotal = dwTimeTotal;
		i++;
	}
	iType = ITEMTIMERTYPE_GiraffeHat;
	if (SQLGetItemTimer(pcUser, iType, iItemID, dwTimeLeft, dwTimeTotal))
	{
		pcUser->sPremiumData.saItemList[i].eType = (EItemTimerType)iType;
		pcUser->sPremiumData.saItemList[i].dwCode = iItemID;
		pcUser->sPremiumData.saItemList[i].dwTimeLeft = dwTimeLeft;
		pcUser->sPremiumData.saItemList[i].dwTimeTotal = dwTimeTotal;
		i++;
	}
	iType = ITEMTIMERTYPE_SheepHat;
	if (SQLGetItemTimer(pcUser, iType, iItemID, dwTimeLeft, dwTimeTotal))
	{
		pcUser->sPremiumData.saItemList[i].eType = (EItemTimerType)iType;
		pcUser->sPremiumData.saItemList[i].dwCode = iItemID;
		pcUser->sPremiumData.saItemList[i].dwTimeLeft = dwTimeLeft;
		pcUser->sPremiumData.saItemList[i].dwTimeTotal = dwTimeTotal;
		i++;
	}
	iType = ITEMTIMERTYPE_SoccerHat;
	if (SQLGetItemTimer(pcUser, iType, iItemID, dwTimeLeft, dwTimeTotal))
	{
		pcUser->sPremiumData.saItemList[i].eType = (EItemTimerType)iType;
		pcUser->sPremiumData.saItemList[i].dwCode = iItemID;
		pcUser->sPremiumData.saItemList[i].dwTimeLeft = dwTimeLeft;
		pcUser->sPremiumData.saItemList[i].dwTimeTotal = dwTimeTotal;
		i++;
	}
	iType = ITEMTIMERTYPE_XMasGreenHat;
	if (SQLGetItemTimer(pcUser, iType, iItemID, dwTimeLeft, dwTimeTotal))
	{
		pcUser->sPremiumData.saItemList[i].eType = (EItemTimerType)iType;
		pcUser->sPremiumData.saItemList[i].dwCode = iItemID;
		pcUser->sPremiumData.saItemList[i].dwTimeLeft = dwTimeLeft;
		pcUser->sPremiumData.saItemList[i].dwTimeTotal = dwTimeTotal;
		i++;
	}
	iType = ITEMTIMERTYPE_XMasRedHat;
	if (SQLGetItemTimer(pcUser, iType, iItemID, dwTimeLeft, dwTimeTotal))
	{
		pcUser->sPremiumData.saItemList[i].eType = (EItemTimerType)iType;
		pcUser->sPremiumData.saItemList[i].dwCode = iItemID;
		pcUser->sPremiumData.saItemList[i].dwTimeLeft = dwTimeLeft;
		pcUser->sPremiumData.saItemList[i].dwTimeTotal = dwTimeTotal;
		i++;
	}
	iType = ITEMTIMERTYPE_BigHeadLove;
	if (SQLGetItemTimer(pcUser, iType, iItemID, dwTimeLeft, dwTimeTotal))
	{
		pcUser->sPremiumData.saItemList[i].eType = (EItemTimerType)iType;
		pcUser->sPremiumData.saItemList[i].dwCode = iItemID;
		pcUser->sPremiumData.saItemList[i].dwTimeLeft = dwTimeLeft;
		pcUser->sPremiumData.saItemList[i].dwTimeTotal = dwTimeTotal;
		i++;
	}
	iType = ITEMTIMERTYPE_BigHeadLove;
	if (SQLGetItemTimer(pcUser, iType, iItemID, dwTimeLeft, dwTimeTotal))
	{
		pcUser->sPremiumData.saItemList[i].eType = (EItemTimerType)iType;
		pcUser->sPremiumData.saItemList[i].dwCode = iItemID;
		pcUser->sPremiumData.saItemList[i].dwTimeLeft = dwTimeLeft;
		pcUser->sPremiumData.saItemList[i].dwTimeTotal = dwTimeTotal;
		i++;
	}
	iType = ITEMTIMERTYPE_BigHeadHappiness;
	if (SQLGetItemTimer(pcUser, iType, iItemID, dwTimeLeft, dwTimeTotal))
	{
		pcUser->sPremiumData.saItemList[i].eType = (EItemTimerType)iType;
		pcUser->sPremiumData.saItemList[i].dwCode = iItemID;
		pcUser->sPremiumData.saItemList[i].dwTimeLeft = dwTimeLeft;
		pcUser->sPremiumData.saItemList[i].dwTimeTotal = dwTimeTotal;
		i++;
	}
	iType = ITEMTIMERTYPE_BigHeadLove;
	if (SQLGetItemTimer(pcUser, iType, iItemID, dwTimeLeft, dwTimeTotal))
	{
		pcUser->sPremiumData.saItemList[i].eType = (EItemTimerType)iType;
		pcUser->sPremiumData.saItemList[i].dwCode = iItemID;
		pcUser->sPremiumData.saItemList[i].dwTimeLeft = dwTimeLeft;
		pcUser->sPremiumData.saItemList[i].dwTimeTotal = dwTimeTotal;
		i++;
	}
	iType = ITEMTIMERTYPE_BigHeadSadness;
	if (SQLGetItemTimer(pcUser, iType, iItemID, dwTimeLeft, dwTimeTotal))
	{
		pcUser->sPremiumData.saItemList[i].eType = (EItemTimerType)iType;
		pcUser->sPremiumData.saItemList[i].dwCode = iItemID;
		pcUser->sPremiumData.saItemList[i].dwTimeLeft = dwTimeLeft;
		pcUser->sPremiumData.saItemList[i].dwTimeTotal = dwTimeTotal;
		i++;
	}
	iType = ITEMTIMERTYPE_BigHeadShyness;
	if (SQLGetItemTimer(pcUser, iType, iItemID, dwTimeLeft, dwTimeTotal))
	{
		pcUser->sPremiumData.saItemList[i].eType = (EItemTimerType)iType;
		pcUser->sPremiumData.saItemList[i].dwCode = iItemID;
		pcUser->sPremiumData.saItemList[i].dwTimeLeft = dwTimeLeft;
		pcUser->sPremiumData.saItemList[i].dwTimeTotal = dwTimeTotal;
		i++;
	}
	iType = ITEMTIMERTYPE_BigHeadAngry;
	if (SQLGetItemTimer(pcUser, iType, iItemID, dwTimeLeft, dwTimeTotal))
	{
		pcUser->sPremiumData.saItemList[i].eType = (EItemTimerType)iType;
		pcUser->sPremiumData.saItemList[i].dwCode = iItemID;
		pcUser->sPremiumData.saItemList[i].dwTimeLeft = dwTimeLeft;
		pcUser->sPremiumData.saItemList[i].dwTimeTotal = dwTimeTotal;
		i++;
	}
	iType = ITEMTIMERTYPE_BigHeadSurprised;
	if (SQLGetItemTimer(pcUser, iType, iItemID, dwTimeLeft, dwTimeTotal))
	{
		pcUser->sPremiumData.saItemList[i].eType = (EItemTimerType)iType;
		pcUser->sPremiumData.saItemList[i].dwCode = iItemID;
		pcUser->sPremiumData.saItemList[i].dwTimeLeft = dwTimeLeft;
		pcUser->sPremiumData.saItemList[i].dwTimeTotal = dwTimeTotal;
		i++;
	}
	iType = ITEMTIMERTYPE_BigHeadSensual;
	if (SQLGetItemTimer(pcUser, iType, iItemID, dwTimeLeft, dwTimeTotal))
	{
		pcUser->sPremiumData.saItemList[i].eType = (EItemTimerType)iType;
		pcUser->sPremiumData.saItemList[i].dwCode = iItemID;
		pcUser->sPremiumData.saItemList[i].dwTimeLeft = dwTimeLeft;
		pcUser->sPremiumData.saItemList[i].dwTimeTotal = dwTimeTotal;
		i++;
	}

	iType = ITEMTIMERTYPE_BCBuff;
	if (SQLGetItemTimer(pcUser, iType, iItemID, dwTimeLeft, dwTimeTotal))
	{
		pcUser->sPremiumData.saItemList[i].eType = (EItemTimerType)iType;
		pcUser->sPremiumData.saItemList[i].dwCode = iItemID;
		pcUser->sPremiumData.saItemList[i].dwTimeLeft = dwTimeLeft;
		pcUser->sPremiumData.saItemList[i].dwTimeTotal = dwTimeTotal;
		i++;
	}

	SENDPACKET(pcUser, &pcUser->sPremiumData);
}
BOOL CServerItem::SQLAddItemTimer(User * pcUser, int iType, EItemID iItemID, DWORD dwTimeTotal)
{
	if (pcUser == NULL)
		return FALSE;

	//New Item Index
	int iIndex = -1;

	for (int i = 0; i < PREMIUM_ITEM_TOTAL; i++)
	{
		//Find New Item Slot
		if (pcUser->sPremiumData.saItemList[i].eType == ITEMTIMERTYPE_None)
		{
			if (iIndex == (-1))
				iIndex = i;
		}
		else
		{
			//Find if can Stack
			if ((pcUser->sPremiumData.saItemList[i].eType == iType) || (ItemTimerIsSame(pcUser->sPremiumData.saItemList[i].eType, iType) == TRUE))
			{
				//Can stack?
				if (ItemTimerCanStack(iType))
				{
					//Set Index
					iIndex = i;

					//Delete Old
					SQLDeleteItemTimer(pcUser, pcUser->sPremiumData.saItemList[i].dwCode);

					break;
				}
			}
		}
	}

	if (iIndex != -1)
	{
		pcUser->sPremiumData.saItemList[iIndex].dwCode = iItemID;
		pcUser->sPremiumData.saItemList[iIndex].dwTimeLeft = dwTimeTotal;
		pcUser->sPremiumData.saItemList[iIndex].dwTimeTotal = dwTimeTotal;
		pcUser->sPremiumData.saItemList[iIndex].eType = (EItemTimerType)iType;

		//if ((EItemTimerType)iType == ITEMTIMERTYPE_ExpUp)
			//SERVERNET->SendEXPPotion(pcUser, TRUE);

		SERVERNET->SendPremium(pcUser, &pcUser->sPremiumData.saItemList[iIndex]);

		SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);

		if (pcDB->Open())
		{
			if (pcDB->Prepare("INSERT INTO CharacterItemTimer([CharacterName],[ItemTimerType],[ItemID],[TimeLeft],[TimeTotal]) VALUES(?,?,?,?,?)"))
			{
				pcDB->BindParameterInput(1, PARAMTYPE_String, SERVERCHARACTER->GetCharacterName(pcUser));
				pcDB->BindParameterInput(2, PARAMTYPE_Integer, &iType);
				pcDB->BindParameterInput(3, PARAMTYPE_Integer, &iItemID);
				pcDB->BindParameterInput(4, PARAMTYPE_Integer, &dwTimeTotal);
				pcDB->BindParameterInput(5, PARAMTYPE_Integer, &dwTimeTotal);

				pcDB->Execute();
			}

			pcDB->Close();
		}

		return TRUE;
	}

	return FALSE;
}
BOOL CServerItem::SQLGetItemTimer(User * pcUser, int iType, EItemID & iItemID, DWORD & dwTimeLeft, DWORD & dwTimeTotal)
{
	if (pcUser == NULL)
		return FALSE;

	BOOL bRet = FALSE;

	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);
	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT ItemID, TimeLeft, TimeTotal FROM CharacterItemTimer WHERE CharacterName=? AND ItemTimerType=?"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_String, SERVERCHARACTER->GetCharacterName(pcUser));
			pcDB->BindParameterInput(2, PARAMTYPE_Integer, &iType);

			if ((pcDB->Execute()) && (pcDB->Fetch()))
			{
				pcDB->GetData(1, PARAMTYPE_Integer, &iItemID, 0);
				pcDB->GetData(2, PARAMTYPE_Integer, &dwTimeLeft, 0);
				pcDB->GetData(3, PARAMTYPE_Integer, &dwTimeTotal, 0);

				bRet = TRUE;
			}
		}
		pcDB->Close();
	}

	return bRet;
}
void CServerItem::SQLDeleteItemTimer(User * pcUser, int iItemID)
{
	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);

	if (pcDB->Open())
	{
		if (pcDB->Prepare("DELETE FROM CharacterItemTimer WHERE CharacterName=? AND ItemID=?"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_String, SERVERCHARACTER->GetCharacterName(pcUser));
			pcDB->BindParameterInput(2, PARAMTYPE_Integer, &iItemID);

			pcDB->Execute();
		}

		pcDB->Close();
	}
}
void CServerItem::SQLUpdateItemTimer(User * pcUser, int iType, DWORD dwTimeLeft)
{
	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);

	if (pcDB->Open())
	{
		if (pcDB->Prepare("UPDATE CharacterItemTimer SET TimeLeft=? WHERE CharacterName=? AND ItemTimerType=? AND TimeLeft>?"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_Integer, &dwTimeLeft);
			pcDB->BindParameterInput(2, PARAMTYPE_String, SERVERCHARACTER->GetCharacterName(pcUser));
			pcDB->BindParameterInput(3, PARAMTYPE_Integer, &iType);
			pcDB->BindParameterInput(4, PARAMTYPE_Integer, &dwTimeLeft);
			pcDB->Execute();
		}

		pcDB->Close();
	}
}
void CServerItem::HandlePacket(User * pcUser, PacketNewItemTimer * psPacket)
{
	DWORD dwTime = 0;

	psPacket->dwTimeLeft = psPacket->dwTimeTotal = 0;

	//For Delete...
	int iOldItemID = psPacket->iItemID;

	//Hour
	switch (psPacket->iItemID)
	{
	case ITEMID_ThirdEye1H:
	case ITEMID_ExpUp1H:
		psPacket->dwTimeTotal = ITEMTIMERTIME_1H;
		break;

	case ITEMID_BigHeadLove:
	case ITEMID_BigHeadSadness:
	case ITEMID_BigHeadHappyness:
	case ITEMID_BigHeadShyness:
	case ITEMID_BigHeadAngry:
	case ITEMID_BigHeadSurprised:
	case ITEMID_BigHeadSensual:
		psPacket->dwTimeTotal = ITEMTIMERTIME_3H;
		break;

	case ITEMID_SheepHat:
	case ITEMID_GiraffeHat:
	case ITEMID_SoccerHat:
		psPacket->dwTimeTotal = ITEMTIMERTIME_6H;
		break;

	case ITEMID_MPDown12H:
	case ITEMID_MPUp12H:
	case ITEMID_SPDown12H:
	case ITEMID_HPUp12H:
	case ITEMID_CartolaHat:
	case ITEMID_WitchHat:
	case ITEMID_XMasGreenHat:
	case ITEMID_XMasRedHat:
		psPacket->dwTimeTotal = ITEMTIMERTIME_12H;
		break;


	case ITEMID_ExpUp24H:
	case ITEMID_ThirdEye24H:
		psPacket->dwTimeTotal = ITEMTIMERTIME_24H;
		break;

	case ITEMID_ExpUp48H:
	case ITEMID_ThirdEye48H:
		psPacket->dwTimeTotal = ITEMTIMERTIME_48H;
		break;

	case ITEMID_ExpUp72H:
	case ITEMID_ThirdEye72H:
	case ITEMID_GravityStone72H:
	case ITEMID_PhoenixEgg:
		psPacket->dwTimeTotal = ITEMTIMERTIME_72H;
		break;

	default:
		break;
	}

	//Used for PHPet...
	int iRandom = RandomI(0, 100);

	//Type
	switch (psPacket->iItemID)
	{
	case ITEMID_ExpUp1H:
	case ITEMID_ExpUp24H:
	case ITEMID_ExpUp48H:
	case ITEMID_ExpUp72H:
		psPacket->iType = ITEMTIMERTYPE_ExpUp;
		break;

	case ITEMID_ThirdEye1H:
	case ITEMID_ThirdEye24H:
	case ITEMID_ThirdEye48H:
	case ITEMID_ThirdEye72H:
		psPacket->iType = ITEMTIMERTYPE_ThirdEye;
		break;

	case ITEMID_MPDown12H:
		psPacket->iType = ITEMTIMERTYPE_MPDown;
		break;

	case ITEMID_SPDown12H:
		psPacket->iType = ITEMTIMERTYPE_SPDown;
		break;

	case ITEMID_HPUp12H:
		psPacket->iType = ITEMTIMERTYPE_HPUp;
		break;

	case ITEMID_MPUp12H:
		psPacket->iType = ITEMTIMERTYPE_MPUp;
		break;

	case ITEMID_GravityStone72H:
		psPacket->iType = ITEMTIMERTYPE_WeightStone;
		break;

	case ITEMID_CartolaHat:
		psPacket->iType = ITEMTIMERTYPE_CartolaHat;
		break;

	case ITEMID_WitchHat:
		psPacket->iType = ITEMTIMERTYPE_WitchHat;
		break;

	case ITEMID_SheepHat:
		psPacket->iType = ITEMTIMERTYPE_SheepHat;
		break;

	case ITEMID_GiraffeHat:
		psPacket->iType = ITEMTIMERTYPE_GiraffeHat;
		break;

	case ITEMID_SoccerHat:
		psPacket->iType = ITEMTIMERTYPE_SoccerHat;
		break;

	case ITEMID_XMasRedHat:
		psPacket->iType = ITEMTIMERTYPE_XMasRedHat;
		break;

	case ITEMID_XMasGreenHat:
		psPacket->iType = ITEMTIMERTYPE_XMasGreenHat;
		break;

	case ITEMID_BigHeadLove:
		psPacket->iType = ITEMTIMERTYPE_BigHeadLove;
		break;

	case ITEMID_BigHeadSadness:
		psPacket->iType = ITEMTIMERTYPE_BigHeadSadness;
		break;

	case ITEMID_BigHeadHappyness:
		psPacket->iType = ITEMTIMERTYPE_BigHeadHappiness;
		break;

	case ITEMID_BigHeadShyness:
		psPacket->iType = ITEMTIMERTYPE_BigHeadShyness;
		break;

	case ITEMID_BigHeadAngry:
		psPacket->iType = ITEMTIMERTYPE_BigHeadAngry;
		break;

	case ITEMID_BigHeadSurprised:
		psPacket->iType = ITEMTIMERTYPE_BigHeadSurprised;
		break;

	case ITEMID_BigHeadSensual:
		psPacket->iType = ITEMTIMERTYPE_BigHeadSensual;
		break;

	case ITEMID_PhoenixEgg:
		psPacket->iType = ITEMTIMERTYPE_PhoenixFire;
		psPacket->iItemID = ITEMID_PhoenixFire;

		if (iRandom < 25)
		{
			psPacket->iType = ITEMTIMERTYPE_PhoenixIce;
			psPacket->iItemID = ITEMID_PhoenixIce;
		}
		else if (iRandom < 50)
		{
			psPacket->iType = ITEMTIMERTYPE_PhoenixLightning;
			psPacket->iItemID = ITEMID_PhoenixLightning;
		}
		else if (iRandom < 75)
		{
			psPacket->iType = ITEMTIMERTYPE_PhoenixHeal;
			psPacket->iItemID = ITEMID_PhoenixHealing;
		}
		break;

	default:
		break;
	}

	//Have Time?
	if (psPacket->dwTimeTotal > 0)
	{
		//Update Time Left
		psPacket->dwTimeLeft = psPacket->dwTimeTotal;

		//Delete Item From Server
		if (DeleteItemInventory(pcUser, iOldItemID, psPacket->iChk1, psPacket->iChk2) == FALSE)
		{
			//Item Name
			char szItemName[32] = { 0 };
			if (FindItemName(iOldItemID, szItemName))
			{
				//Log It...
				PacketLogCheat sPacket;
				sPacket.iCheatID = CHEATLOGID_ItemTimerFakeInventory;
				sPacket.iLParam = iOldItemID;
				sPacket.iSParam = psPacket->iChk1;
				sPacket.iEParam = psPacket->iChk2;
				sPacket.iLxParam = (int)szItemName;
				SERVERLOG->LogCheat(pcUser, &sPacket);
			}
		}

		//Add To User
		if (SQLAddItemTimer(pcUser, psPacket->iType, psPacket->iItemID, psPacket->dwTimeTotal))
		{
			//Notify New Item to User...
			SENDPACKET(pcUser, psPacket);
		}
	}
}
void CServerItem::HandlePacket(User * pcUser, PacketCancelItemTimer * psPacket)
{
	for (int i = 0; i < PREMIUM_ITEM_TOTAL; i++)
	{
		ItemPremium * psItem = &pcUser->sPremiumData.saItemList[i];

		if ((psItem->eType == psPacket->iType) && (psItem->dwCode == psPacket->iItemID))
		{
			SQLDeleteItemTimer(pcUser, psPacket->iItemID);
			psItem->eType = ITEMTIMERTYPE_None;
			break;
		}
	}
}
void CServerItem::HandlePacket(User * pcUser, PacketOldHeadUse * psPacket)
{
	if (psPacket->bUpdate)
	{
		SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);

		if (pcDB->Open())
		{
			if (pcDB->Prepare("UPDATE CharacterInfo SET OldHead=? WHERE ID=?"))
			{
				pcDB->BindParameterInput(1, PARAMTYPE_String, pcUser->sCharacterData.Player.szHeadModel);
				pcDB->BindParameterInput(2, PARAMTYPE_Integer, &pcUser->iCharacterID);
				pcDB->Execute();
			}

			pcDB->Close();
		}
	}
	else
	{
		SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);

		if (pcDB->Open())
		{
			if (pcDB->Prepare("SELECT OldHead FROM CharacterInfo WHERE ID=?"))
			{
				pcDB->BindParameterInput(1, PARAMTYPE_Integer, &pcUser->iCharacterID);

				if (pcDB->Execute() && pcDB->Fetch())
				{
					char szHead[64] = { 0 };
					pcDB->GetData(1, PARAMTYPE_String, szHead, _countof(szHead));

					if (IsNull(szHead))
						ZeroMemory(szHead, _countof(szHead));

					STRINGCOPY(pcUser->sCharacterData.Player.szHeadModel, szHead);
					STRINGCOPY(psPacket->szHeadModel, szHead);

					SENDPACKET(pcUser, psPacket);
				}
			}

			pcDB->Close();
		}
	}
}
void CServerItem::HandlePacket(User * pcUser, PacketSlotItemHandle * psPacket)
{
	char * pszCharacterName = SERVERCHARACTER->GetCharacterName(pcUser);

	char * pszAction = "Get";
	char * pszWhere = "null";

	int iLogID = ITEMLOGID_GetPerfectize;

	BOOL bPut = (psPacket->iTypeHandle == ESlotTypeHandle::ITEMSLOTHANDLE_Put) ? TRUE : FALSE;

	if (psPacket->iTypeHandle == ESlotTypeHandle::ITEMSLOTHANDLE_Put)
		pszAction = "Put";

	if (psPacket->iTypeWhere == ESlotTypeHandleWhere::ITEMSLOTHANDLEWHERE_Perfectize)
	{
		pszWhere = "Perfectize";

		iLogID = ITEMLOGID_GetPerfectize;
		if (bPut)
			iLogID = ITEMLOGID_PutPerfectize;
	}
	else if (psPacket->iTypeWhere == ESlotTypeHandleWhere::ITEMSLOTHANDLEWHERE_Swap)
	{
		pszWhere = "Swap";

		iLogID = ITEMLOGID_GetSwap;
		if (bPut)
			iLogID = ITEMLOGID_PutSwap;
	}
	else if (psPacket->iTypeWhere == ESlotTypeHandleWhere::ITEMSLOTHANDLEWHERE_Sender)
	{
		pszWhere = "Sender";

		iLogID = ITEMLOGID_GetSwap;
		if (bPut)
			iLogID = ITEMLOGID_PutSwap;
	}

	char szItemName[32] = { 0 };
	FindItemName(psPacket->iItemID, szItemName);

	SERVERLOG->OnLogItemEx(pcUser, iLogID, "[%s](%s) %s item on %s ( [%s][0x%08X] %d x %d )",
		pcUser->szAccountName, pszCharacterName, pszAction, pszWhere, szItemName, psPacket->iItemID, psPacket->iChk1, psPacket->iChk2);
}
void CServerItem::HandlePacket(User * pcUser, PacketGetItem * psPacket)
{
	if (!GAME_SERVER)
		return;

	if (psPacket->iLength != sizeof(PacketGetItem))
		return;

	//Valid Pointer?
	Map * pcMap = SERVERMAP->GetMap(pcUser->GetMapID());
	if (!pcMap)
		return;

	//It's a valid map?
	if (!SERVERMAP->IsValidMap(pcMap))
		return;

	//Item Found?
	MapLoot * pcLootItem = SERVERMAP->FindItemStage(pcMap, psPacket->sPosition >> 8);

	if (pcLootItem)
	{
		//Bellatra Item
		if (pcLootItem->sLootItem.sItem.sItemID.ToItemType() == ITEMTYPE_Bellatra)
		{
			rsSoD_CatchItem(pcLootItem->sLootItem.sItem.sItemID.ToInt(), pcUser);
			SERVERMAP->DelItem(pcMap, pcLootItem);
			return;
		}

		//Item Drop
		SendItemData(pcUser, &pcLootItem->sLootItem.sItem);

		if (pcLootItem->bExclusive && pcLootItem->sLootItem.sItem.sItemID.ToItemID() != ITEMID_None)
		{
			if ((pcUser->psParty && pcUser->bParty) && pcUser->psParty->pcLeader)
			{
				char szMessage[256] = { 0 };
				STRINGFORMAT(szMessage, "> %s gained %s!", SERVERCHARACTER->GetCharacterName(pcUser), pcLootItem->sLootItem.sItem.sItemID.ToItemID() == ITEMID_Gold ? FormatString("%s Gold", FormatNumber(pcLootItem->sLootItem.sItem.iGold)) : pcLootItem->sLootItem.sItem.szItemName);
				PARTYHANDLE->SendChatParty(pcUser, szMessage, CHATCOLOR_Notice, TRUE);
			}
			else
				SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Notice, "> %s gained %s!", SERVERCHARACTER->GetCharacterName(pcUser), pcLootItem->sLootItem.sItem.sItemID.ToItemID() == ITEMID_Gold ? FormatString("%s Gold", FormatNumber(pcLootItem->sLootItem.sItem.iGold)) : pcLootItem->sLootItem.sItem.szItemName);
		}

		SERVERMAP->DelItem(pcMap, pcLootItem);
	}
}
void CServerItem::HandlePacket(User * pcUser, PacketUseItem * psPacket)
{
	if (psPacket->sItem.ToInt() > 0x4010000)
	{
		if (psPacket->sItem.ToItemType() != ITEMTYPE_Wing &&
			psPacket->sItem.ToItemType() != ITEMTYPE_Chocolate)
		{
			DeleteItemInventory(pcUser, psPacket->sItem.ToInt(), psPacket->iChk1, psPacket->iChk2);
			SERVERUSER->SaveDropItem(pcUser, psPacket->sItem, psPacket->iChk1, psPacket->iChk2);

			if (psPacket->sItem.ToItemType() == ITEMTYPE_MonsterCrystal ||
				psPacket->sItem.ToItemType() == ITEMTYPE_BlessCastle ||
				psPacket->sItem.ToItemType() == ITEMTYPE_Premium1 ||
				psPacket->sItem.ToItemType() == ITEMTYPE_Premium2)
			{
				SERVERLOG->OnLogItem(pcUser, psPacket->sItem.ToInt(), psPacket->iChk1, psPacket->iChk2, ITEMLOGID_Used);
			}
		}
	}
}
void CServerItem::HandlePacket(User * pcUser, PacketPutItem * psPacket)
{
	int iPotionCount = 0;

	if (ValiSecCode(pcUser, psPacket->iItemID, psPacket->iChk1, psPacket->iChk2, psPacket->iGold, psPacket->dwSeCode, iPotionCount))
	{
		if (psPacket->iItemID == ITEMID_Gold)
		{
			SERVERUSER->AddServerUserGold(pcUser, psPacket->iGold, WHEREID_GetItem);
		}
		else
		{
			if (iPotionCount)
			{
				SERVERITEM->AddPotion(pcUser, psPacket->iItemID, iPotionCount);
			}

			SERVERITEM->AddItemInventory(pcUser, psPacket->iItemID, psPacket->iChk1, psPacket->iChk2);
		}

		SERVERLOG->OnLogItem(pcUser, psPacket->iItemID, psPacket->iChk1, psPacket->iChk2, ITEMLOGID_Get);

		SENDPACKET(pcUser, psPacket);
	}
}
BOOL CServerItem::AddItemInventory(User * pcUser, int iItemID, int iChk1, int iChk2)
{
	if ((iItemID & 0xFF000000) == ITEMBASE_Potion || iItemID == (sinGG1 | sin01))
		return TRUE;

	for (int i = 0; i < INVEN_ITEM_INFO_MAX; i++)
	{
		DropItemData * pDropItem = pcUser->InvenItemInfo + i;

		if (pDropItem->dwCode)
		{
			//a have
			if (pDropItem->dwCode == iItemID && pDropItem->dwKey == iChk1 && pDropItem->dwSum == iChk2)
				return TRUE;
		}
		else
		{
			// new item
			pDropItem->dwCode = iItemID;
			pDropItem->dwKey = iChk1;
			pDropItem->dwSum = iChk2;
			return TRUE;
		}
	}

	//LOG

	return FALSE;
}
BOOL CServerItem::DeleteItemInventory(User *pcUser, DWORD dwCode, DWORD dwHead, DWORD dwChkSum)
{
	if ((dwCode & 0xFF000000) == ITEMBASE_Potion || dwCode == ITEMID_Gold)
		return TRUE;

	for (int i = 0; i < INVEN_ITEM_INFO_MAX; i++)
	{
		DropItemData * pDropItem = pcUser->InvenItemInfo + i;

		if (pDropItem->dwCode && pDropItem->dwCode == dwCode && pDropItem->dwKey == dwHead && pDropItem->dwSum == dwChkSum)
		{
			pDropItem->dwCode = 0;
			return TRUE;
		}
	}

	return FALSE;
}
BOOL CServerItem::IsItemInventory(User * pcUser, EItemID iItemID)
{
	for (int i = 0; i < 300; i++)
	{
		if (pcUser->InvenItemInfo[i].dwCode == iItemID)
			return TRUE;
	}

	return FALSE;
}
BOOL CServerItem::IsItemInventory(User * pcUser, DWORD dwCode, DWORD dwHead, DWORD dwChkSum)
{
	if ((dwCode & 0xFF000000) == ITEMBASE_Potion || dwCode == (sinGG1 | sin01))
		return TRUE;

	for (int i = 0; i < INVEN_ITEM_INFO_MAX; i++)
	{
		DropItemData * pDropItem = pcUser->InvenItemInfo + i;

		if (pDropItem->dwCode && pDropItem->dwCode == dwCode && pDropItem->dwKey == dwHead && pDropItem->dwSum == dwChkSum)
		{
			return TRUE;
		}
	}

	return FALSE;
}
void CServerItem::SetLowerItem(DefinitionItem *pDefItem)
{
	Item *pItem = &pDefItem->sItem;

	if (pDefItem->sIntegrity.sMin)
	{
		int iMin = pDefItem->sIntegrity.sMin;
		pItem->sIntegrity.sMin = iMin;
		pItem->sIntegrity.sMax = iMin;
	}

	for (int i  = 0; i < 8; i++) 
	{
		pItem->saElementalDef[i] = pDefItem->saElementalDef[i].sMin;
	}

	if (pDefItem->sDamage[1] || pDefItem->sDamage[3])
	{
		pItem->sDamage = MinMax(pDefItem->sDamage[0], pDefItem->sDamage[2]);
	}

	pItem->iAttackRating = pDefItem->sAttack_Rating[0];
	pItem->fAbsorbRating = pDefItem->fAbsorb[0];
	pItem->iDefenseRating = pDefItem->sDefence[0];
	pItem->fBlockRating = pDefItem->fBlock_Rating[0];
	pItem->fMovementSpeed = pDefItem->fSpeed[0];

	pItem->fMPRegen = pDefItem->fMana_Regen[0];
	pItem->fHPRegen = pDefItem->fLife_Regen[0];
	pItem->fSPRegen = pDefItem->fStamina_Regen[0];

	pItem->fAddHP = (float)pDefItem->Increase_Life[0];
	pItem->fAddMP = (float)pDefItem->Increase_Mana[0];
	pItem->fAddSP = (float)pDefItem->Increase_Stamina[0];

	if (pItem->eSpecialization)
	{
		for (int i = 1; i < 11; i++)
		{
			if (saItemRequeriments[i].iClass == pItem->eSpecialization)
			{
				OnSetItem(pItem, FALSE);
			}
		}

		pItem->sSpecData.fSpecAbsorbRating = pDefItem->fSpecial_Absorb[0];
		pItem->sSpecData.iSpecDefenseRating = pDefItem->sSpecial_Defence[0];
		pItem->sSpecData.fSpecMovementSpeed = pDefItem->fSpecial_fSpeed[0];
		pItem->sSpecData.fSpecMagicMastery = pDefItem->fSpecial_Magic_Mastery[0];
		pItem->sSpecData.fSpecMPRegen = pDefItem->fSpecial_Mana_Regen[0];
		pItem->sSpecData.iSpecAttackRatingDiv = pDefItem->Lev_Attack_Rating[1] == 0 ? pDefItem->Lev_Attack_Rating[0] : 
			pDefItem->Lev_Attack_Rating[0] + (pDefItem->Lev_Attack_Rating[1] - pDefItem->Lev_Attack_Rating[0]) / 2;

	}
	else 
	{
		ZeroMemory(&pItem->sSpecData, sizeof(SpecItemData));
	}

	ValidateItem(pItem);
}

void CServerItem::OnSetItem(Item * pItem, BOOL IsPerfect)
{
	if (!pItem)
		return;

	int iCharacterClass = ClassFlagToCharacterClass((EClassFlag)pItem->eSpecialization);

	// Set Status
	{
		// Get Minor
		int iLevel =  IsPerfect == TRUE ? low(saItemRequeriments[iCharacterClass].sLevel[0], saItemRequeriments[iCharacterClass].sLevel[1]) :
			RandomS(saItemRequeriments[iCharacterClass].sLevel[0], saItemRequeriments[iCharacterClass].sLevel[1]);
		int iStrength = IsPerfect == TRUE ? low(saItemRequeriments[iCharacterClass].sStrength[0], saItemRequeriments[iCharacterClass].sStrength[1]) :
			RandomS(saItemRequeriments[iCharacterClass].sStrength[0], saItemRequeriments[iCharacterClass].sStrength[1]);
		int iSpirit = IsPerfect == TRUE ? low(saItemRequeriments[iCharacterClass].sSpirit[0], saItemRequeriments[iCharacterClass].sSpirit[1]) :
			RandomS(saItemRequeriments[iCharacterClass].sSpirit[0], saItemRequeriments[iCharacterClass].sSpirit[1]);
		int iTalent = IsPerfect == TRUE ? low(saItemRequeriments[iCharacterClass].sTalent[0], saItemRequeriments[iCharacterClass].sTalent[1]) :
			RandomS(saItemRequeriments[iCharacterClass].sTalent[0], saItemRequeriments[iCharacterClass].sTalent[1]);
		int iAgility = IsPerfect == TRUE ? low(saItemRequeriments[iCharacterClass].sAgility[0], saItemRequeriments[iCharacterClass].sAgility[1]) :
			RandomS(saItemRequeriments[iCharacterClass].sAgility[0], saItemRequeriments[iCharacterClass].sAgility[1]);
		int iHealth = IsPerfect == TRUE ? low(saItemRequeriments[iCharacterClass].sHealth[0], saItemRequeriments[iCharacterClass].sHealth[1]) :
			RandomS(saItemRequeriments[iCharacterClass].sHealth[0], saItemRequeriments[iCharacterClass].sHealth[1]);

		if (pItem->iLevel && iLevel)
			pItem->iLevel += (pItem->iLevel * iLevel) / 100;

		if (pItem->iStrength && iStrength)
			pItem->iStrength += (pItem->iStrength * iStrength) / 100;

		if (pItem->iSpirit && iSpirit)
			pItem->iSpirit += (pItem->iSpirit * iSpirit) / 100;

		if (pItem->iTalent && iTalent)
			pItem->iTalent += (pItem->iTalent * iTalent) / 100;

		if (pItem->iAgility && iAgility)
			pItem->iAgility += (pItem->iAgility * iAgility) / 100;

		if (pItem->iHealth && iHealth)
			pItem->iHealth += (pItem->iHealth * iHealth) / 100;
	}
}
BOOL CServerItem::FindItemName(UINT uCode, char * szBufName)
{
	STRINGCOPYLEN(szBufName, 32, "NULL");

	char szCharSpecial[2] = { 0x27, 0 };

	for (auto psItem : m_vAllocItemTable)
	{
		if (psItem->sBaseItemID.ToItemID() == uCode)
		{
			STRINGCOPYLEN(szBufName, 32, psItem->szBaseName);

			char * pszCharSpecial = strstr(szBufName, szCharSpecial);

			if (pszCharSpecial)
				*(char*)&pszCharSpecial[0] = ' ';

			return TRUE;
		}
	}

	return FALSE;
}
BOOL CServerItem::FindItemName(char * pszCode, char * szBufName)
{
	STRINGCOPYLEN(szBufName, 32, "NULL");
	char szCharSpecial[2] = { 0x27, 0 };
	
	for (auto &psItem : m_vAllocItemTable)
	{
		if (STRINGCOMPAREI(psItem->szInventoryName, pszCode))
		{
			STRINGCOPYLEN(szBufName, 32, psItem->szBaseName);
			char * pszCharSpecial = strstr(szBufName, szCharSpecial);
			if (pszCharSpecial)
				*(char*)&pszCharSpecial[0] = ' ';
			return TRUE;
		}
	}

	return FALSE;
}

ItemData * CServerItem::FindItemPointerTable(const char * szCode)
{
	for (auto &pItemData : m_vAllocItemTable)
	{
		if (STRINGCOMPAREI(szCode, pItemData->szInventoryName))
			return pItemData;
	}

	return nullptr;
}
ItemData * CServerItem::GetItemDataByID(UINT uID)
{
	for (auto &pItemData : m_vAllocItemTable)
	{
		if (pItemData->sBaseItemID.ToInt() == uID)
			return pItemData;
	}

	return nullptr;
}
int CServerItem::GetItemIDByItemCode(char * pszCode)
{
	for (auto &pItemData : m_vAllocItemTable)
	{
		if (STRINGCOMPAREI(pItemData->szInventoryName, pszCode))
		{
			return pItemData->sBaseItemID.ToItemID();
		}
	}

	return 0;
}
void CServerItem::OnUseCrystal(User * pcUser, Unit * pcUnit, DWORD dwItemID, DWORD dwTime)
{
	PacketCrystalUse sPacket;
	sPacket.iLength = sizeof(PacketCrystalUse);
	sPacket.iHeader = PKTHDR_CrystalUse;
	sPacket.dwObjectID = pcUnit->iID;
	sPacket.dwItemID = dwItemID;
	if (dwTime == 0)
		sPacket.dwTime = (pcUnit->dwLastUpdateTime - TICKCOUNT) / 1000; // 6min 50sec
	else
		sPacket.dwTime = dwTime;
	SENDPACKET(pcUser, &sPacket);
}
void CServerItem::OnUseCrystalDie(User * pcUser, Unit * pcUnit)
{
	PacketCrystalUseDie sPacket;
	sPacket.iLength = sizeof(PacketCrystalUseDie);
	sPacket.iHeader = PKTHDR_CrystalUseDie;
	sPacket.dwObjectID = pcUnit->iID;
	SENDPACKET(pcUser, &sPacket);
}
CharacterClassData * CServerItem::GetItemSpecClassJob(int iClass, DefinitionItem * psDefItem)
{
	int iCounter = _countof(saCharacterClassData);

	int iJobID = iClass;

	if (iJobID == 0 && RandomI(1, 100) < 50)
	{
		if (psDefItem->JobBitCodeRandomCount > 0)
			iJobID = ClassFlagToCharacterClass((EClassFlag)psDefItem->dwJobBitCode_Random[rand() % psDefItem->JobBitCodeRandomCount]);
	}


	for (int i = 0; i < iCounter; i++)
	{
		CharacterClassData * ps = saCharacterClassData + i;

		if (ps->iClass == iJobID)
			return ps;
	}

	return NULL;
}
void CServerItem::Load()
{
	int iCount = 0;

	for (auto &v : m_vAllocItemTable)
	{
		DELET(v);
	}

	m_vAllocItemTable.clear();

	// Get Total Item
	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_GameDB);

	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT COUNT(*) FROM ItemList"))
		{
			if (pcDB->Execute() && pcDB->Fetch())
			{
				pcDB->GetData(1, PARAMTYPE_Integer, &iCount, 0);
			}
		}
		pcDB->Close();
	}

	DefinitionItem sDefItem;

	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT * FROM ItemList ORDER BY ID ASC"))
		{
			if (pcDB->Execute() && pcDB->Fetch())
			{
				for (int i = 0; i < iCount; i++)
				{
					DefinitionItem * pDefItem = new DefinitionItem;

					ZeroMemory(pDefItem, sizeof(DefinitionItem));
					// Code

					pcDB->GetData(2, PARAMTYPE_Integer, &pDefItem->sItem.sItemID, 0);

					// NAME
					pcDB->GetData(3, PARAMTYPE_String, pDefItem->sItem.szItemName, 32);

					// Item Table vars
					int iCode = 0;
					char szLastCategory[10] = { 0 };
					char szDropItem[64] = { 0 };
					int iWidth = 0;
					int iHeight = 0;
					char szItemPath[64] = { 0 };
					int iClass = 0;
					int iModelPosition = 0;
					int iSoundIndex = 0;
					int iWeaponClass = 0;

					{
						// Code
						iCode = pDefItem->sItem.sItemID.ToItemID();

						// Last Category
						pcDB->GetData(5, PARAMTYPE_String, szLastCategory, 10);

						// Drop Item Image
						pcDB->GetData(6, PARAMTYPE_String, szDropItem, 64);

						// Width x Height
						pcDB->GetData(7, PARAMTYPE_Integer, &iWidth, 0);
						pcDB->GetData(8, PARAMTYPE_Integer, &iHeight, 0);

						// Path File Item
						pcDB->GetData(9, PARAMTYPE_String, szItemPath, 64);

						// Class Item
						pcDB->GetData(10, PARAMTYPE_Integer, &iClass, 0);

						// Model Position
						pcDB->GetData(11, PARAMTYPE_Integer, &iModelPosition, 0);

						// Sound
						pcDB->GetData(12, PARAMTYPE_Integer, &iSoundIndex, 0);

						// Weapon Class
						pcDB->GetData(13, PARAMTYPE_Integer, &iWeaponClass, 0);
					}

					pcDB->GetData(14, PARAMTYPE_Integer, &pDefItem->sItem.iItemUniqueID, 0);

					// Item Table
					{
						// FirstRead
						// Is in table?
						if (!pDefItem->sItem.iItemUniqueID && m_bFirstRead == FALSE)
						{
							ItemData * pItemData = new ItemData;

							ZeroMemory(pItemData, sizeof(ItemData));

							// Code
							pItemData->sBaseItemID = pDefItem->sItem.sItemID.ToInt();

							// Name
							STRINGCOPY(pItemData->szBaseName, pDefItem->sItem.szItemName);

							// Last Category
							STRINGCOPY(pItemData->szInventoryName, szLastCategory);

							// Drop Item Image
							STRINGCOPY(pItemData->szModelName, szDropItem);

							// Width x Height
							pItemData->iWidth = iWidth;
							pItemData->iHeight = iHeight;

							// Path File Item
							STRINGCOPY(pItemData->szCategory, szItemPath);

							// Class Item
							pItemData->iItemSlotFlag = (EItemSlotFlag)iClass;

							// Model Position
							pItemData->iVisibleItemType = (EItemSlotFlag)iModelPosition;

							// Sound
							pItemData->iInvItemSound = (EItemInvSound)iSoundIndex;

							// Weapon Class
							pItemData->iItemWpnDmg = iWeaponClass;

							m_vAllocItemTable.push_back(pItemData);
						}
					}

					// Quest
					{
						// R
						pcDB->GetData(15, PARAMTYPE_Short, &pDefItem->sItem.EffectColor[0], 0);

						// G
						pcDB->GetData(16, PARAMTYPE_Short, &pDefItem->sItem.EffectColor[1], 0);

						// B
						pcDB->GetData(17, PARAMTYPE_Short, &pDefItem->sItem.EffectColor[2], 0);

						// A
						pcDB->GetData(18, PARAMTYPE_Short, &pDefItem->sItem.EffectColor[3], 0);

						// Flashing Time
						pcDB->GetData(19, PARAMTYPE_Short, &pDefItem->sItem.EffectBlink[0], 0);
					}

					// Req. Level
					pcDB->GetData(20, PARAMTYPE_Integer, &pDefItem->sItem.iLevel, 0);

					// Req. Strength
					pcDB->GetData(21, PARAMTYPE_Integer, &pDefItem->sItem.iStrength, 0);

					// Req. Spirit
					pcDB->GetData(22, PARAMTYPE_Integer, &pDefItem->sItem.iSpirit, 0);

					// Req. Talent
					pcDB->GetData(23, PARAMTYPE_Integer, &pDefItem->sItem.iTalent, 0);

					// Req. Agility
					pcDB->GetData(24, PARAMTYPE_Integer, &pDefItem->sItem.iAgility, 0);

					// Req. Health
					pcDB->GetData(25, PARAMTYPE_Integer, &pDefItem->sItem.iHealth, 0);

					// Integrity Min
					pcDB->GetData(26, PARAMTYPE_Short, &pDefItem->sIntegrity.sMin, 0);

					// Integrity Max
					pcDB->GetData(27, PARAMTYPE_Short, &pDefItem->sIntegrity.sMax, 0);

					// Weight
					pcDB->GetData(28, PARAMTYPE_Integer, &pDefItem->sItem.iWeight, 0);

					// Price
					pcDB->GetData(29, PARAMTYPE_Integer, &pDefItem->sItem.iSalePrice, 0);

					// Organic
					pcDB->GetData(30, PARAMTYPE_Short, &pDefItem->sOrganic.sMin, 0);
					pcDB->GetData(31, PARAMTYPE_Short, &pDefItem->sOrganic.sMax, 0);

					// Fire
					pcDB->GetData(32, PARAMTYPE_Short, &pDefItem->sFire.sMin, 0);
					pcDB->GetData(33, PARAMTYPE_Short, &pDefItem->sFire.sMax, 0);

					// Frost
					pcDB->GetData(34, PARAMTYPE_Short, &pDefItem->sFrost.sMin, 0);
					pcDB->GetData(35, PARAMTYPE_Short, &pDefItem->sFrost.sMax, 0);

					// Lightning
					pcDB->GetData(36, PARAMTYPE_Short, &pDefItem->sLightning.sMin, 0);
					pcDB->GetData(37, PARAMTYPE_Short, &pDefItem->sLightning.sMax, 0);

					// Poison
					pcDB->GetData(38, PARAMTYPE_Short, &pDefItem->sPoison.sMin, 0);
					pcDB->GetData(39, PARAMTYPE_Short, &pDefItem->sPoison.sMax, 0);

					// Attack Power 1
					pcDB->GetData(40, PARAMTYPE_Short, &pDefItem->sDamage[0], 0);
					pcDB->GetData(41, PARAMTYPE_Short, &pDefItem->sDamage[1], 0);

					// Attack Power 2
					pcDB->GetData(42, PARAMTYPE_Short, &pDefItem->sDamage[2], 0);
					pcDB->GetData(43, PARAMTYPE_Short, &pDefItem->sDamage[3], 0);

					// Shooting Range
					pcDB->GetData(44, PARAMTYPE_Integer, &pDefItem->sItem.iAttackRange, 0);

					// Attack Speed
					pcDB->GetData(45, PARAMTYPE_Integer, &pDefItem->sItem.iAttackSpeed, 0);

					// Attack Rating
					pcDB->GetData(46, PARAMTYPE_Short, &pDefItem->sAttack_Rating[0], 0);
					pcDB->GetData(47, PARAMTYPE_Short, &pDefItem->sAttack_Rating[1], 0);

					// Critical
					pcDB->GetData(48, PARAMTYPE_Integer, &pDefItem->sItem.iCritical, 0);

					// Block
					pcDB->GetData(49, PARAMTYPE_Float, &pDefItem->fBlock_Rating[0], 0);
					pcDB->GetData(50, PARAMTYPE_Float, &pDefItem->fBlock_Rating[1], 0);

					// Absorb
					pcDB->GetData(51, PARAMTYPE_Float, &pDefItem->fAbsorb[0], 0);
					pcDB->GetData(52, PARAMTYPE_Float, &pDefItem->fAbsorb[1], 0);

					// Defense
					pcDB->GetData(53, PARAMTYPE_Short, &pDefItem->sDefence[0], 0);
					pcDB->GetData(54, PARAMTYPE_Short, &pDefItem->sDefence[1], 0);

					// Potions
					pcDB->GetData(55, PARAMTYPE_Integer, &pDefItem->sItem.iPotionStorage, 0);

					// Potions
					pcDB->GetData(56, PARAMTYPE_Integer, &pDefItem->sItem.iPotionCount, 0);

					// Regeneration HP, MP, STM
					pcDB->GetData(57, PARAMTYPE_Float, &pDefItem->fLife_Regen[0], 0);
					pcDB->GetData(58, PARAMTYPE_Float, &pDefItem->fLife_Regen[1], 0);
					pcDB->GetData(59, PARAMTYPE_Float, &pDefItem->fMana_Regen[0], 0);
					pcDB->GetData(60, PARAMTYPE_Float, &pDefItem->fMana_Regen[1], 0);
					pcDB->GetData(61, PARAMTYPE_Float, &pDefItem->fStamina_Regen[0], 0);
					pcDB->GetData(62, PARAMTYPE_Float, &pDefItem->fStamina_Regen[1], 0);

					// Add HP
					pcDB->GetData(63, PARAMTYPE_Integer, &pDefItem->Increase_Life[0], 0);
					pcDB->GetData(64, PARAMTYPE_Integer, &pDefItem->Increase_Life[1], 0);

					// Add MP
					pcDB->GetData(65, PARAMTYPE_Integer, &pDefItem->Increase_Mana[0], 0);
					pcDB->GetData(66, PARAMTYPE_Integer, &pDefItem->Increase_Mana[1], 0);

					// Add STM
					pcDB->GetData(67, PARAMTYPE_Integer, &pDefItem->Increase_Stamina[0], 0);
					pcDB->GetData(68, PARAMTYPE_Integer, &pDefItem->Increase_Stamina[1], 0);

					// Recovery HP
					pcDB->GetData(69, PARAMTYPE_Short, &pDefItem->sItem.sHPRecovery.sMin, 0);
					pcDB->GetData(70, PARAMTYPE_Short, &pDefItem->sItem.sHPRecovery.sMax, 0);

					// Recovery MP
					pcDB->GetData(71, PARAMTYPE_Short, &pDefItem->sItem.sMPRecovery.sMin, 0);
					pcDB->GetData(72, PARAMTYPE_Short, &pDefItem->sItem.sMPRecovery.sMax, 0);

					// Recovery STM
					pcDB->GetData(73, PARAMTYPE_Short, &pDefItem->sItem.sSPRecovery.sMin, 0);
					pcDB->GetData(74, PARAMTYPE_Short, &pDefItem->sItem.sSPRecovery.sMax, 0);

					// Run Speed
					pcDB->GetData(75, PARAMTYPE_Float, &pDefItem->fSpeed[0], 0);
					pcDB->GetData(76, PARAMTYPE_Float, &pDefItem->fSpeed[1], 0);

					// Specs
					pcDB->GetData(77, PARAMTYPE_Integer, &pDefItem->sItem.eSpecialization, 0);
					pDefItem->sItem.eSpecialization = CharacterClassToClassFlag((ECharacterClass)pDefItem->sItem.eSpecialization);

					for (int j = 0; j < 12; j++)
					{
						pcDB->GetData(78 + j, PARAMTYPE_Integer, &pDefItem->dwJobBitCode_Random[pDefItem->JobBitCodeRandomCount], 0);
						if (pDefItem->dwJobBitCode_Random[pDefItem->JobBitCodeRandomCount])
						{
							pDefItem->dwJobBitCode_Random[pDefItem->JobBitCodeRandomCount] = CharacterClassToClassFlag((ECharacterClass)(j + 1));
							pDefItem->JobBitCodeRandomCount++;
						}
					}

					// Spec Data
					{
						// Run Speed
						pcDB->GetData(90, PARAMTYPE_Float, &pDefItem->fSpecial_fSpeed[0], 0);
						pcDB->GetData(91, PARAMTYPE_Float, &pDefItem->fSpecial_fSpeed[1], 0);

						// Absorb
						pcDB->GetData(92, PARAMTYPE_Float, &pDefItem->fSpecial_Absorb[0], 0);
						pcDB->GetData(93, PARAMTYPE_Float, &pDefItem->fSpecial_Absorb[1], 0);

						// Defense
						pcDB->GetData(94, PARAMTYPE_Short, &pDefItem->sSpecial_Defence[0], 0);
						pcDB->GetData(95, PARAMTYPE_Short, &pDefItem->sSpecial_Defence[1], 0);

						// Attack Speed
						pcDB->GetData(96, PARAMTYPE_Integer, &pDefItem->sItem.sSpecData.iSpecAttackSpeed, 0);

						// Critical
						pcDB->GetData(97, PARAMTYPE_Integer, &pDefItem->sItem.sSpecData.iSpecCritical, 0);

						// Attack Power
						pcDB->GetData(98, PARAMTYPE_Short, &pDefItem->sItem.sSpecData.iSpecAttackPowerDivMin, 0);
						pcDB->GetData(99, PARAMTYPE_Short, &pDefItem->sItem.sSpecData.iSpecAttackPowerDiv, 0);

						// Attack Rating
						pcDB->GetData(100, PARAMTYPE_Integer, &pDefItem->Lev_Attack_Rating[0], 0);
						pcDB->GetData(101, PARAMTYPE_Integer, &pDefItem->Lev_Attack_Rating[1], 0);

						// HP Regen
						pcDB->GetData(102, PARAMTYPE_Float, &pDefItem->sItem.sSpecData.fSpecHPRegen, 0);

						// MP Regen
						pcDB->GetData(103, PARAMTYPE_Float, &pDefItem->fSpecial_Mana_Regen[0], 0);
						pcDB->GetData(104, PARAMTYPE_Float, &pDefItem->fSpecial_Mana_Regen[1], 0);

						// STM Regen
						pcDB->GetData(105, PARAMTYPE_Float, &pDefItem->sItem.sSpecData.fSpecSPRegen, 0);

						// Block
						pcDB->GetData(106, PARAMTYPE_Float, &pDefItem->sItem.sSpecData.fSpecBlockRating, 0);

						// Shooting Range
						pcDB->GetData(107, PARAMTYPE_Integer, &pDefItem->sItem.sSpecData.iSpecAttackRange, 0);

						// Cannot Drop
						pcDB->GetData(108, PARAMTYPE_Integer, &pDefItem->sItem.bEnableEffect, 0);

						memcpy(&sDefItem, pDefItem, sizeof(DefinitionItem));

						sDefItem.sItem.BackUpKey = 0;
						sDefItem.sItem.BackUpChkSum = 0;
						sDefItem.sItem.dwCreateTime = 0;

						SERVERITEM->SetLowerItem(&sDefItem);

						pDefItem->DefCompressDataLen = EecodeCompress((BYTE *)&sDefItem.sItem, (BYTE *)pDefItem->DefCompressData, sizeof(Item));

						m_vItemTable.push_back(pDefItem);
					}

					pcDB->Fetch();
				}
			}
		}

		pcDB->Close();
	}

	// Create Item table

	if (m_bFirstRead == FALSE && LOGIN_SERVER)
	{
		CFILE::Ini cReader(SERVERINFO->GetConfigFile());

		const char * pszFilePath = FormatString("%s\\items.dat", cReader.ReadString("Database", "NetFolder").c_str());

		CFILE::Bin cWrite(pszFilePath, BIN_WRITE);

		if (cWrite.IsOpen())
		{
			for (auto & v : m_vAllocItemTable)
			{
				cWrite.Write(v, sizeof(ItemData));
			}

			cWrite.Close();
		}
	}
}