#include "StdAfx.h"
#include "AgeHandle.h"

CAgeHandle::CAgeHandle()
{

}
CAgeHandle::~CAgeHandle()
{

}
void CAgeHandle::SQLItemBroke(User * pcUser, Item * psItem)
{
	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_LogDB);

	if (pcDB->Open())
	{
		if (pcDB->Prepare("INSERT INTO AgingRecovery([AccountName],[CharacterID],[Date],[ItemName],[AgeNumber],[Code1],[Code2],[DateRecovered]) VALUES (?,?,GETDATE(),?,?,?,?,NULL)"))
		{
			int iAge = (int)psItem->sAgeLevel;
			pcDB->BindParameterInput(1, PARAMTYPE_String, pcUser->szAccountName, STRLEN(pcUser->szAccountName));
			pcDB->BindParameterInput(2, PARAMTYPE_Integer, &pcUser->iCharacterID);
			pcDB->BindParameterInput(3, PARAMTYPE_String, psItem->szItemName, STRLEN(psItem->szItemName));
			pcDB->BindParameterInput(4, PARAMTYPE_Integer, &iAge);
			pcDB->BindParameterInput(5, PARAMTYPE_Integer, &psItem->iChk1);
			pcDB->BindParameterInput(6, PARAMTYPE_Integer, &psItem->iChk2);

			pcDB->Execute();
		}

		pcDB->Close();
	}
}
void CAgeHandle::SQLItemBrokeRecovered(User * pcUser, int iID)
{
	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_LogDB);

	if (pcDB->Open())
	{
		if (pcDB->Prepare("UPDATE AgingRecovery SET DateRecovered=GETDATE() WHERE (AccountName=?) AND (ID=?)"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_String, pcUser->szAccountName, STRLEN(pcUser->szAccountName));
			pcDB->BindParameterInput(2, PARAMTYPE_Integer, &iID);

			pcDB->Execute();
		}

		pcDB->Close();
	}
}
BOOL CAgeHandle::GetItemDataBroke(User * pcUser, Item * psItem, int iID)
{
	BOOL bRet = FALSE;

	char szCode[128] = { 0 };

	if (pcUser && psItem)
	{
		SQLConnection * pcDB = SQLCONNECTION(DATABASEID_LogDB);

		if (pcDB->Open())
		{
			if (pcDB->Prepare("SELECT [Code1],[Code2] FROM AgingRecovery WHERE (AccountName=?) AND (ID=?) AND (DateRecovered IS NULL)"))
			{
				pcDB->BindParameterInput(1, PARAMTYPE_String, pcUser->szAccountName, STRLEN(pcUser->szAccountName));
				pcDB->BindParameterInput(2, PARAMTYPE_Integer, &iID);

				if (pcDB->Execute() && pcDB->Fetch())
				{
					ZeroMemory(psItem, sizeof(Item));

					int iCode1 = 0, iCode2 = 0;

					pcDB->GetData(1, PARAMTYPE_Integer, &iCode1);
					pcDB->GetData(2, PARAMTYPE_Integer, &iCode2);

					STRINGFORMAT(szCode, "%d@%d", iCode1, iCode2);
				}
			}

			pcDB->Close();
		}

		if (szCode[0] != 0)
		{
			ItemLoadData sData;

			if (SERVERITEM->OnLoadItemData(&sData, szCode))
			{
				CopyMemory(psItem, &sData.sItem, sizeof(Item));
				bRet = TRUE;
			}
		}
	}
	return bRet;
}
std::vector<AgingRecoveryDataHandle> CAgeHandle::SQLGetBrokeItems(char * pszAccountName)
{
	std::vector<AgingRecoveryDataHandle> vData;

	AgingRecoveryDataHandle sData;

	ZeroMemory(&sData, sizeof(AgingRecoveryDataHandle));

	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_LogDB);

	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT [ID],[ItemName],[AgeNumber],[Date] FROM AgingRecovery WHERE (AccountName=?) AND (DateRecovered IS NULL) ORDER BY ID DESC"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_String, pszAccountName, STRLEN(pszAccountName));

			if (pcDB->Execute())
			{
				while (pcDB->Fetch())
				{
					ZeroMemory(&sData, sizeof(AgingRecoveryDataHandle));

					pcDB->GetData(1, PARAMTYPE_Integer, &sData.iID);
					pcDB->GetData(2, PARAMTYPE_String, sData.szItemName, _countof(sData.szItemName));
					pcDB->GetData(3, PARAMTYPE_Integer, &sData.iAgeNumber);
					pcDB->GetData(4, PARAMTYPE_Time, &sData.sDate);

					vData.push_back(sData);
				}
			}
		}

		pcDB->Close();
	}

	return vData;
}
void CAgeHandle::DownDamage(Item * psItem, int iDown, int iLevel)
{
	if (iLevel < 10)
	{
		psItem->sDamage.sMin -= (short)iDown;
		psItem->sDamage.sMax -= (short)iDown;
	}
	else
	{
		switch (iDown)
		{
		case 1:
			psItem->sDamage.sMin -= 2;
			psItem->sDamage.sMax -= 2;
			break;
		case 2:
			if (iLevel == 10)
			{
				psItem->sDamage.sMin -= 2 + 1;
				psItem->sDamage.sMax -= 2 + 1;
			}
			else
			{
				psItem->sDamage.sMin -= 2 * 2;
				psItem->sDamage.sMax -= 2 * 2;
			}
			break;
		case 3:
			if (iLevel == 10)
			{
				psItem->sDamage.sMin -= 2 + 1 + 1;
				psItem->sDamage.sMax -= 2 + 1 + 1;
			}
			else if (iLevel == 11)
			{
				psItem->sDamage.sMin -= (2 * 2) + 1;
				psItem->sDamage.sMax -= (2 * 2) + 1;
			}
			else
			{
				psItem->sDamage.sMin -= 2 * 3;
				psItem->sDamage.sMax -= 2 * 3;
			}
			break;

		default:
			break;
		}
	}
}
void CAgeHandle::DownDefense(Item * psItem, int iDown, int iPercent)
{
	for (int i = 0; i < iDown; i++)
	{
		float f = (100.0f * (float)psItem->iDefenseRating) / (100.0f + (float)iPercent);
		psItem->iDefenseRating = (int)round(f);
	}
}
void CAgeHandle::DownAttackRating(Item * psItem, int iDown, int iNum)
{
	psItem->iAttackRating -= iNum * iDown;
}
void CAgeHandle::DownAbsorbRating(Item * psItem, int iDown, float fPercent, int iLevel)
{
	psItem->fAbsorbRating -= fPercent * (float)iDown;

	int i = iLevel - 9;
	if (i > 0)
	{
		if (i == 1)
			psItem->fAbsorbRating -= fPercent;
		else
			psItem->fAbsorbRating -= fPercent * (float)iDown;
	}
}
void CAgeHandle::DownCritical(Item * psItem, int iDown)
{
	if (psItem->sAgeLevel && (psItem->sAgeLevel % 2) == 1)
		psItem->iCritical -= 1;

	if (iDown > 2)
	{
		if (psItem->sAgeLevel && (psItem->sAgeLevel % 2) == 1)
			psItem->iCritical -= 1;
	}
}
void CAgeHandle::DownBlockRating(Item * psItem, int iDown)
{
	if (psItem->sAgeLevel && (psItem->sAgeLevel % 2) == 1)
		psItem->fBlockRating -= 1.0f;

	if (iDown > 2)
	{
		if (psItem->sAgeLevel && (psItem->sAgeLevel % 2) == 1)
			psItem->fBlockRating -= 1.0f;
	}
}
void CAgeHandle::UpDamage(Item * psItem)
{
	psItem->sDamage.sMin++;
	psItem->sDamage.sMax++;

	if (psItem->sAgeLevel >= 9)
	{
		psItem->sDamage.sMin++;
		psItem->sDamage.sMax++;
	}
}
void CAgeHandle::UpDefense(Item * psItem, int iPercent)
{
	float f = (float)psItem->iDefenseRating / (100.0f / (float)iPercent);
	psItem->iDefenseRating += (int)round(f);
}
void CAgeHandle::UpAttackRating(Item * psItem, int iNum)
{
	psItem->iAttackRating += iNum;
}
void CAgeHandle::UpAbsorbRating(Item * psItem, float fPercent)
{
	psItem->fAbsorbRating += fPercent;

	if (psItem->sAgeLevel >= 9)
		psItem->fAbsorbRating += fPercent;
}
void CAgeHandle::UpCritical(Item * psItem)
{
	if (psItem->sAgeLevel && (psItem->sAgeLevel % 2) == 1)
		psItem->iCritical++;
}
void CAgeHandle::UpBlockRating(Item * psItem)
{
	if (psItem->sAgeLevel && (psItem->sAgeLevel % 2) == 1)
		psItem->fBlockRating += 1.0f;
}
void CAgeHandle::OnDownAge(Item * psItem, int iCount)
{
	int iAgeLevel = (int)psItem->sAgeLevel;

	int iDown = iCount + 1;

	int iLevelAge = Base::Coin::GetLevelItemEachAge(psItem);

	int iDownResult = 1;

	if (iLevelAge == 4)
		iDownResult = 0;

	psItem->sAgeLevel -= (short)iDown;

	switch (psItem->sItemID.ToItemType())
	{
	case ITEMTYPE_Axe:
		DownDamage(psItem, iDown, iAgeLevel);
		DownAttackRating(psItem, iDown, 10);
		break;

	case ITEMTYPE_Hammer:
		DownDamage(psItem, iDown, iAgeLevel);
		DownAttackRating(psItem, iDown, 8);
		DownCritical(psItem, iDown);
		break;

	case ITEMTYPE_Scythe:
	case ITEMTYPE_Dagger:
	case ITEMTYPE_Sword:
	case ITEMTYPE_Claw:
		DownDamage(psItem, iDown, iAgeLevel);
		DownAttackRating(psItem, iDown, 5);
		DownCritical(psItem, iDown);
		break;

	case ITEMTYPE_Phantom:
	case ITEMTYPE_Wand:
		DownDamage(psItem, iDown, iAgeLevel);
		DownAttackRating(psItem, iDown, 8);
		DownCritical(psItem, iDown);
		psItem->fAddMP -= 10.0f * (float)iDown;
		break;

	case ITEMTYPE_Bow:
	case ITEMTYPE_Javelin:
		DownDamage(psItem, iDown, iAgeLevel);
		DownCritical(psItem, iDown);
		break;

	case ITEMTYPE_Shield:
		DownDefense(psItem, iDown, 5);
		DownBlockRating(psItem, iDown);
		DownAbsorbRating(psItem, iDown, 0.4f, iAgeLevel);
		break;

	case ITEMTYPE_Orb:
		DownDefense(psItem, iDown, 6);
		DownAbsorbRating(psItem, iDown, 0.5f, iAgeLevel);
		break;

	case ITEMTYPE_Robe:
	case ITEMTYPE_Armor:
		DownDefense(psItem, iDown, 5);
		DownAbsorbRating(psItem, iDown, 0.5f, iAgeLevel);
		break;

	default:
		break;
	}

	psItem->bMaturing = FALSE;
	psItem->sMatureBar.sMin = 0;
	psItem->sMatureBar.sMax = 0;

	if (iLevelAge > 0)
	{
		if (iLevelAge == 4)
		{
			psItem->iLevel -= (iAgeLevel / 4) - (psItem->sAgeLevel / 4);
		}
		else
		{
			if ((psItem->sAgeLevel % iLevelAge) == iDownResult)
				psItem->iLevel -= 1;

			if (iDown > 2)
			{
				if ((psItem->sAgeLevel % iLevelAge) == iDownResult)
					psItem->iLevel -= 1;
			}
		}
	}
}
void CAgeHandle::OnDownAgeHandler(Item * psItem, int iCount)
{
	if (iCount > 0)
	{
		for (int i = 0; i < iCount; i++)
			OnDownAge(psItem, 0);
	}

	OnDownAge(psItem, 0);

	SERVERITEM->ValidateItem(psItem);
}
void CAgeHandle::OnUpAge(Item * psItem)
{
	switch (psItem->sItemID.ToItemType())
	{
	case ITEMTYPE_Axe:
		UpDamage(psItem);
		UpAttackRating(psItem, 10);
		break;

	case ITEMTYPE_Hammer:
		UpDamage(psItem);
		UpAttackRating(psItem, 8);
		UpCritical(psItem);
		break;

	case ITEMTYPE_Scythe:
	case ITEMTYPE_Dagger:
	case ITEMTYPE_Sword:
	case ITEMTYPE_Claw:
		UpDamage(psItem);
		UpAttackRating(psItem, 5);
		UpCritical(psItem);
		break;

	case ITEMTYPE_Phantom:
	case ITEMTYPE_Wand:
		UpDamage(psItem);
		UpAttackRating(psItem, 8);
		UpCritical(psItem);
		psItem->fAddMP += 10;
		break;

	case ITEMTYPE_Bow:
	case ITEMTYPE_Javelin:
		UpDamage(psItem);
		UpCritical(psItem);
		break;

	case ITEMTYPE_Shield:
		UpDefense(psItem, 5);
		UpBlockRating(psItem);
		UpAbsorbRating(psItem, 0.4f);
		break;

	case ITEMTYPE_Orb:
		UpDefense(psItem, 6);
		UpAbsorbRating(psItem, 0.5f);
		break;

	case ITEMTYPE_Robe:
	case ITEMTYPE_Armor:
		UpDefense(psItem, 5);
		UpAbsorbRating(psItem, 0.5f);
		break;

	default:
		break;
	}

	psItem->bMaturing = FALSE;
	psItem->sMatureBar.sMin = 0;
	psItem->sMatureBar.sMax = 0;

	psItem->sAgeLevel++;

	int iLevelAge = Base::Coin::GetLevelItemEachAge(psItem);

	if (iLevelAge > 0)
	{
		if ((psItem->sAgeLevel % iLevelAge) == 0)
			psItem->iLevel++;
	}
}
void CAgeHandle::OnUpAgeHandler(Item * psItem, int iCount)
{
	for (int i = 0; i < iCount; i++)
		OnUpAge(psItem);

	SERVERITEM->ValidateItem(psItem);
}
void CAgeHandle::OnBrokeItemHandler(User * pcUser, Item * psItem)
{
	if (pcUser && psItem)
	{
		SERVERITEM->SaveItemData(psItem);

		SQLItemBroke(pcUser, psItem);
	}
}