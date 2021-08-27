#include "StdAfx.h"
#include "ItemHandle.h"

CItemHandle::CItemHandle()
{

}
CItemHandle::~CItemHandle()
{

}
void CItemHandle::Init()
{
	CFILE::Bin cReader("Resources\\Items\\Item.dat", BIN_READ);

	if (cReader.IsOpen())
	{
		UINT uSize = cReader.GetSize();

		if (uSize % sizeof(ItemData) == 0)
		{
			BYTE * pszBuf = new BYTE[uSize];

			ZeroMemory(pszBuf, sizeof(BYTE) * uSize);

			cReader.Read(pszBuf, uSize);

			for (size_t i = 0; i < uSize; i++)
			{
				ItemData * pItem = new ItemData;

				CopyMemory(pItem, pszBuf + sizeof(ItemData) * i, sizeof(ItemData));

				pItem->sItem.sItemID = pItem->sBaseItemID;

				m_vpItemTable.push_back(pItem);
			}

			DELETA(pszBuf);
		}

		cReader.Close();
	}
	/*else
	{
		MessageBoxA(0, "No Item", "Error!", MB_OK | MB_ICONEXCLAMATION);
	}*/
}
void CItemHandle::Shutdown()
{
	for (auto &pItem : m_vpItemTable)
	{
		DELET(pItem->pcTempInventoryTexture);
		DELET(pItem);
	}

	m_vpItemTable.clear();
}
BOOL CItemHandle::IsBeginnerSet(ItemData * pcItemData)
{
	BOOL bRet = FALSE;
	switch (pcItemData->sItem.sItemID.ToItemID())
	{
	case ITEMID_BeginnerAxe:
	case ITEMID_BeginnerClaw:
	case ITEMID_BeginnerHammer:
	case ITEMID_BeginnerSword:
	case ITEMID_BeginnerJavelin:
	case ITEMID_BeginnerBow:
	case ITEMID_BeginnerScythe:
	case ITEMID_BeginnerPhantom:
	case ITEMID_BeginnerDagger:
	case ITEMID_BeginnerStaff:
	case ITEMID_BeginnerBoots:
	case ITEMID_BeginnerGauntlet:
	case ITEMID_BeginnerBracelet:
	case ITEMID_GrumpyArmor:
	case ITEMID_GrumpyRobe:
		bRet = TRUE;
		break;

	default:
		break;
	}

	return bRet;
}
DWORD CItemHandle::GetItemPlayTime(EItemID eID)
{
	DWORD dwTime = 0;
	switch (eID)
	{
		// 7 Days
		// Beginner Set
	case ITEMID_BeginnerAxe:
	case ITEMID_BeginnerClaw:
	case ITEMID_BeginnerHammer:
	case ITEMID_BeginnerStaff:
	case ITEMID_BeginnerSword:
	case ITEMID_BeginnerJavelin:
	case ITEMID_BeginnerScythe:
	case ITEMID_BeginnerBow:
	case ITEMID_BeginnerBoots:
	case ITEMID_BeginnerBracelet:
	case ITEMID_BeginnerDagger:
	case ITEMID_BeginnerPhantom:
	case ITEMID_BeginnerGauntlet:
	case ITEMID_GrumpyArmor:
	case ITEMID_GrumpyRobe:

		// Xmas
	case ITEMID_XMasElegantCostumeM:
	case ITEMID_XMasElegantCostumeF:
	case ITEMID_XMasCloatCostumeTM:
	case ITEMID_XMasCloatCostumeTF:
	case ITEMID_XMasCloatCostumeMM:
	case ITEMID_XMasCloatCostumeMF:
		// Halloween
	case ITEMID_VampireSuit:
	case ITEMID_Succubus:

		dwTime = (60 * 60 * 24 * 7);
		break;

	default:
		break;
	}
	return dwTime;
}
BOOL CItemHandle::IsExpiredItemTime(Item * psItemInfo)
{
	EItemID eItemID = psItemInfo->sItemID.ToItemID();

	DWORD dwTime = GetItemPlayTime(eItemID);

	if (dwTime && psItemInfo->szItemName[0] != 0)
	{
		if (GetPlayTime_T() > (psItemInfo->dwCreateTime + dwTime))
			return TRUE;
	}

	return FALSE;
}
BOOL CItemHandle::GetItemPrice(class ItemData * pcItemData, PriceItem * psSellData)
{
	if (!pcItemData || !psSellData)
		return FALSE;

	if (pcItemData->iItemSlotFlag == ITEMSLOTFLAG_LeftRightHand)
	{
		if (pcItemData->iItemSlot)
			pcItemData = &cInvenTory.InvenItem[sInven[0].ItemIndex - 1];
	}

	float fIntegrity[2];
	float fPrice;


	fPrice = (float)pcItemData->sItem.iSalePrice;
	fIntegrity[0] = pcItemData->sItem.sIntegrity.sMin == 0 ? 1.0f : (float)(int)pcItemData->sItem.sIntegrity.sMin;
	fIntegrity[1] = pcItemData->sItem.sIntegrity.sMax == 0 ? 1.0f : (float)(int)pcItemData->sItem.sIntegrity.sMax;

	psSellData->iRealPrice = (int)((fPrice*(fIntegrity[0] / fIntegrity[1])) + (fPrice - (fPrice*(fIntegrity[0] / fIntegrity[1])))*0.25);
	psSellData->iPrice = psSellData->iRealPrice / 5;
	psSellData->iRepairPrice = (pcItemData->sItem.iSalePrice - psSellData->iRealPrice) / 8;

	return TRUE;
}
int CItemHandle::GetItemNumberFromID(UINT uID)
{
	for (size_t t = 0; t < m_vpItemTable.size(); t++)
	{
		if (m_vpItemTable.at(t)->sBaseItemID.ToInt() == uID)
			return (int)t;
	}

	return -1;
}
ItemData * CItemHandle::GetItemDataByID(UINT uID)
{
	for (auto &pItem : m_vpItemTable)
	{
		if (pItem->sBaseItemID.ToInt() == uID)
			return pItem;
	}

	return nullptr;
}
ItemData * CItemHandle::GetItemDataByName(char *pszName)
{
	for (auto &pItem : m_vpItemTable)
	{
		if (STRINGCOMPAREI(pszName, pItem->szInventoryName))
		{
			return pItem;
		}
	}

	return nullptr;
}
ItemData * CItemHandle::GetItemDataByNumber(int iNumber)
{
	if (iNumber >= 0 && iNumber < (int)m_vpItemTable.size())
		return m_vpItemTable.at(iNumber);

	return nullptr;
}
BOOL CItemHandle::IsItemDataByID(int iFindNumber, UINT uID)
{
	if (iFindNumber >= 0 && iFindNumber < (int)m_vpItemTable.size())
	{
		if (m_vpItemTable.at(iFindNumber)->sBaseItemID.ToInt() == uID)
			return TRUE;
	}

	return FALSE;
}