#include "StdAfx.h"

CDistributorHandle::CDistributorHandle()
{

}
CDistributorHandle::~CDistributorHandle()
{

}
BOOL CDistributorHandle::SQLLoadItemBox(User * pcUser)
{
	if (!GAME_SERVER)
	{
		if ((pcUser != NULL) && (pcUser->szAccountName[0] != 0))
		{
			ZeroMemory(&pcUser->sItemBox, sizeof(ItemBoxSlot));

			SQLConnection * pcDB = SQLCONNECTION(DATABASEID_LogDB);

			if (pcDB->Open() != FALSE)
			{
				if (pcDB->Prepare("SELECT ID, ItemCode, ItemSpec FROM ItemBox WHERE AccountName=? AND DateReceived IS NULL"))
				{
					pcDB->BindParameterInput(1, PARAMTYPE_String, pcUser->szAccountName, _countof(pcUser->szAccountName));

					if (pcDB->Execute())
					{
						int i = 0;
						while ((i < MAX_ITEMSINITEMBOX) && (pcDB->Fetch()))
						{
							ItemBoxItem * psItemBoxItem = &pcUser->sItemBox.saItemBox[i];

							psItemBoxItem->bValid = TRUE;
							pcDB->GetData(1, PARAMTYPE_Integer, &psItemBoxItem->iID);

							char szItemCode[32] = { 0 };
							pcDB->GetData(2, PARAMTYPE_String, szItemCode, _countof(szItemCode));
							psItemBoxItem->iItemID = SERVERITEM->GetItemIDByItemCode(szItemCode);
							// Item error check
							if (psItemBoxItem->iItemID == 0)
								continue;

							pcDB->GetData(3, PARAMTYPE_Integer, &psItemBoxItem->iSpecialization);

							i++;
						}

						pcUser->sItemBox.iNumItems = i;
					}
				}

				pcDB->Close();
			}

			return TRUE;
		}
	}

	return FALSE;
}
BOOL CDistributorHandle::SQLLoadItemBoxEx(User * pcUser)
{
	if (!GAME_SERVER)
	{
		if ((pcUser != NULL) && (pcUser->szAccountName[0] != 0))
		{
			ZeroMemory(&pcUser->sItemBoxEx, sizeof(ItemBoxSlotEx));

			SQLConnection * pcDB = SQLCONNECTION(DATABASEID_LogDB);

			if (pcDB->Open() != FALSE)
			{
				if (pcDB->Prepare("SELECT [ID], [CharName2], [Item] FROM ItemBoxEx WHERE (AccountID=?) AND (CharName1=?) AND DateReceived IS NULL"))
				{
					pcDB->BindParameterInput(1, PARAMTYPE_String, pcUser->szAccountName, _countof(pcUser->szAccountName));
					pcDB->BindParameterInput(2, PARAMTYPE_String, pcUser->szCharacterName, _countof(pcUser->szCharacterName));

					if (pcDB->Execute())
					{
						int i = 0;
						while ((i < MAX_ITEMSINITEMBOX) && (pcDB->Fetch()))
						{
							ItemBoxItemEx * psItemBoxItemEx = &pcUser->sItemBoxEx.saItemBoxEx[i];

							psItemBoxItemEx->bValid = TRUE;
							pcDB->GetData(1, PARAMTYPE_Integer, &psItemBoxItemEx->iID);
							pcDB->GetData(2, PARAMTYPE_String, psItemBoxItemEx->szCharName, 32);
							pcDB->GetData(3, PARAMTYPE_Binary, &psItemBoxItemEx->sItem, sizeof(Item));

							i++;
						}

						pcUser->sItemBoxEx.iNumItems = i;
					}
				}

				pcDB->Close();
			}

			return TRUE;
		}
	}

	return FALSE;
}
void CDistributorHandle::SQLUpdateItemBox(int iID)
{
	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_LogDB);

	if (pcDB->Open() != FALSE)
	{
		if (pcDB->Prepare("UPDATE ItemBox SET DateReceived=GETDATE() WHERE ID=?"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_Integer, &iID);

			pcDB->Execute();
		}

		pcDB->Close();
	}
}
void CDistributorHandle::SQLUpdateItemBoxEx(int iID)
{
	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_LogDB);

	if (pcDB->Open() != FALSE)
	{
		if (pcDB->Prepare("UPDATE ItemBoxEx SET DateReceived=GETDATE() WHERE ID=?"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_Integer, &iID);

			pcDB->Execute();
		}

		pcDB->Close();
	}
}
BOOL CDistributorHandle::AddItemOpenBox(User * pcUser, char * pszItemName, int iSpec, int iQuantity)
{
	return AddItemOpenBox(pcUser->szAccountName, pszItemName, iSpec, iQuantity);
}
BOOL CDistributorHandle::AddItemOpenBox(char * pszAccountName, char * pszItemName, int iSpec, int iQuantity)
{
	char szItemName[32] = { 0 };

	std::string strItemName = MakeUpper(pszItemName);
	STRINGCOPY(szItemName, strItemName.c_str());

	if (STRLEN(pszItemName) >= 2)
	{
		SQLConnection * pcDB = SQLCONNECTION(DATABASEID_LogDB);

		if (pcDB->Open() != FALSE)
		{
			BOOL bQuantitySpec = FALSE;

			if (szItemName[0] == 'P' && (szItemName[1] == 'L' || szItemName[1] == 'M' || szItemName[1] == 'S'))
				bQuantitySpec = TRUE;

			if (STRINGCOMPAREI(szItemName, "GG102") || STRINGCOMPAREI(szItemName, "GG101"))
				bQuantitySpec = TRUE;

			if (bQuantitySpec)
			{
				if (pcDB->Prepare("INSERT INTO ItemBox([AccountName],[ItemCode],[ItemSpec],[DateReceived]) VALUES(?,?,?,NULL)"))
				{
					pcDB->BindParameterInput(1, PARAMTYPE_String, pszAccountName, 32);
					pcDB->BindParameterInput(2, PARAMTYPE_String, szItemName, 32);
					pcDB->BindParameterInput(3, PARAMTYPE_Integer, &iQuantity);
					pcDB->Execute();
				}
				pcDB->Clear();
			}
			else
			{
				for (int i = 0; i < iQuantity; i++)
				{
					if (pcDB->Prepare("INSERT INTO ItemBox([AccountName],[ItemCode],[ItemSpec],[DateReceived]) VALUES(?,?,?,NULL)"))
					{
						pcDB->BindParameterInput(1, PARAMTYPE_String, pszAccountName, 32);
						pcDB->BindParameterInput(2, PARAMTYPE_String, szItemName, 32);
						pcDB->BindParameterInput(3, PARAMTYPE_Integer, &iSpec);
						pcDB->Execute();
					}
					pcDB->Clear();
				}
			}
			pcDB->Close();

			return TRUE;
		}
	}

	return FALSE;
}

BOOL CDistributorHandle::AddItemOpenBoxEx(char * pszAccountName, char * pszCharName1, char * pszCharName2, Item * psItem)
{
	if (psItem != NULL)
	{
		SQLConnection * pcDB = SQLCONNECTION(DATABASEID_LogDB);

		if (pcDB->Open() != FALSE)
		{
			if (pcDB->Prepare("INSERT INTO ItemBoxEx([AccountID],[CharName1],[CharName2],[Item],[DateReceived]) VALUES(?,?,?,?,NULL)"))
			{
				pcDB->BindParameterInput(1, PARAMTYPE_String, pszAccountName, 32);
				pcDB->BindParameterInput(2, PARAMTYPE_String, pszCharName1, 32);
				pcDB->BindParameterInput(3, PARAMTYPE_String, pszCharName2, 32);
				pcDB->BindParameterInput(4, PARAMTYPE_Binary, psItem, sizeof(Item));
				pcDB->Execute();
			}

			pcDB->Close();

			return TRUE;
		}
	}

	return FALSE;
}
int CDistributorHandle::SQLItemBoxCount(User * pcUser)
{
	int iCount = 0;

	char * pszCharacterName = SERVERCHARACTER->GetCharacterName(pcUser);

	if (pcUser->szAccountName && pcUser->szAccountName[0])
	{
		int i = 0;

		SQLConnection * pcDB = SQLCONNECTION(DATABASEID_LogDB);

		if (pcDB->Open() != FALSE)
		{
			if (pcDB->Prepare("SELECT COUNT(ID) FROM ItemBox WHERE AccountName=? AND DateReceived IS NULL"))
			{
				pcDB->BindParameterInput(1, PARAMTYPE_String, pcUser->szAccountName, 32);
				if (pcDB->Execute() && pcDB->Fetch())
					pcDB->GetData(1, PARAMTYPE_Integer, &i);
			}
			pcDB->Close();
		}

		iCount += i;

		if (pcDB->Open() != FALSE)
		{
			if (pcDB->Prepare("SELECT COUNT(ID) FROM ItemBoxEx WHERE (AccountID=?) AND (CharName1=?) AND DateReceived IS NULL"))
			{
				pcDB->BindParameterInput(1, PARAMTYPE_String, pcUser->szAccountName, 32);
				pcDB->BindParameterInput(2, PARAMTYPE_String, pszCharacterName, 32);
				if (pcDB->Execute() && pcDB->Fetch())
					pcDB->GetData(1, PARAMTYPE_Integer, &i);
			}
			pcDB->Close();
		}

		iCount += i;
	}

	return iCount;
}
void CDistributorHandle::OpenDistributorItem(User * pcUser)
{
	if (!GAME_SERVER)
	{
		PacketItemBoxShow sPacket;

		ZeroMemory(&sPacket, sizeof(PacketItemBoxShow));
		sPacket.iLength = sizeof(PacketItemBoxShow);
		sPacket.iHeader = PKTHDR_DistrbutorItemShow;

		if (pcUser->pcSocketData)
		{
			if (SQLLoadItemBox(pcUser) && pcUser->sItemBox.iNumItems > 0)
			{
				//Show next Item
				for (int i = 0; i < pcUser->sItemBox.iNumItems; i++)
				{
					ItemBoxItem * psItemBoxItem = &pcUser->sItemBox.saItemBox[i];

					if (psItemBoxItem->bValid != FALSE)
					{
						psItemBoxItem->bValid = FALSE;

						DefinitionItem * itm = SERVERITEM->FindItemDefByCode(psItemBoxItem->iItemID);

						if (itm != NULL)
						{
							sPacket.iItemID = psItemBoxItem->iItemID;
							sPacket.sWeight = itm->sItem.iWeight;

							if ((psItemBoxItem->iItemID & 0xFF000000) == 0x04000000)
							{
								sPacket.sWeight = psItemBoxItem->iSpecialization;
							}

							STRINGCOPY(sPacket.szPlayerName, "Sever");

							auto sTime = SERVERINFO->GetServerTime();

							STRINGFORMAT(sPacket.szMessage, "%02d-%02d-%04d %02d:%02d", sTime->wMonth, sTime->wDay, sTime->wYear, sTime->wHour, sTime->wMinute);

							SENDPACKET(pcUser, &sPacket);

							return;
						}
					}
				}
			}
			else if (SQLLoadItemBoxEx(pcUser) && pcUser->sItemBoxEx.iNumItems > 0)
			{
				//Show next ItemEx
				for (int i = 0; i < pcUser->sItemBoxEx.iNumItems; i++)
				{
					ItemBoxItemEx * psItemBoxItemEx = &pcUser->sItemBoxEx.saItemBoxEx[i];

					if (psItemBoxItemEx->bValid != FALSE)
					{
						psItemBoxItemEx->bValid = FALSE;

						sPacket.iItemID = psItemBoxItemEx->sItem.sItemID.ToInt();
						sPacket.sWeight = psItemBoxItemEx->sItem.iWeight;

						if (psItemBoxItemEx->sItem.sItemID.ToItemBase() == ITEMBASE_Potion)
						{
							sPacket.sWeight = psItemBoxItemEx->sItem.iPotionCount;
						}

						STRINGCOPY(sPacket.szPlayerName, psItemBoxItemEx->szCharName);

						auto sTime = SERVERINFO->GetServerTime();

						STRINGFORMAT(sPacket.szMessage, "%02d-%02d-%04d %02d:%02d", sTime->wMonth, sTime->wDay, sTime->wYear, sTime->wHour, sTime->wMinute);

						SENDPACKET(pcUser, &sPacket);

						return;
					}
				}
			}

			SENDPACKET(pcUser, &sPacket);
		}
	}
}
void CDistributorHandle::AcceptDistributorItem(User * pcUser)
{
	if (!GAME_SERVER)
	{
		PacketItemBoxAccept sPacket;
		ZeroMemory(&sPacket, sizeof(PacketItemBoxAccept));
		sPacket.iLength = sizeof(PacketItemBoxAccept);
		sPacket.iHeader = PKTHDR_DistrbutorItemAccept;

		if (pcUser->pcSocketData)
		{
			// Item Shop
			if (SQLLoadItemBox(pcUser) && pcUser->sItemBox.iNumItems > 0)
			{
				//Show next Item
				for (int i = 0; i < pcUser->sItemBox.iNumItems; i++)
				{
					ItemBoxItem * psItemBoxItem = &pcUser->sItemBox.saItemBox[i];

					if (psItemBoxItem->bValid != FALSE)
					{
						psItemBoxItem->bValid = FALSE;

						if (psItemBoxItem->iItemID == ITEMID_Gold)
						{
							int iGold = psItemBoxItem->iSpecialization;

							if ((iGold > 0) && (iGold <= 1000000000))
								SERVERCHARACTER->GiveGold(pcUser, iGold, WHEREID_Distributor);
						}
						else if (psItemBoxItem->iItemID == ITEMID_Experience)
						{
							int iEXP = psItemBoxItem->iSpecialization;

							if (iEXP > 0)
								SERVERCHARACTER->GiveEXP(pcUser, iEXP);
						}
						else
						{
							DefinitionItem * itm = SERVERITEM->FindItemDefByCode(psItemBoxItem->iItemID);
							if (itm != NULL)
							{
								if ((psItemBoxItem->iItemID & 0xFF000000) == 0x04000000)
								{
									SERVERITEM->CreateItem(&sPacket.sItem, itm, 0);
									sPacket.sItem.iPotionCount = psItemBoxItem->iSpecialization;
								}
								else if (psItemBoxItem->iSpecialization)
									SERVERITEM->CreatePerfectItem(&sPacket.sItem, itm, psItemBoxItem->iSpecialization);
								else
									SERVERITEM->CreateItem(&sPacket.sItem, itm, psItemBoxItem->iSpecialization);

								//Put Item In Server Inventory
								if (sPacket.sItem.iPotionCount > 0)
									SERVERITEM->AddPotion(pcUser, sPacket.sItem.sItemID.ToInt(), sPacket.sItem.iPotionCount);
								else
									SERVERITEM->AddItemInventory(pcUser, sPacket.sItem.sItemID.ToItemID(), sPacket.sItem.iChk1, sPacket.sItem.iChk2);
							}
						}

						//Update SQL Get Next Item
						SQLUpdateItemBox(psItemBoxItem->iID);

						SENDPACKET(pcUser, &sPacket);
						break;
					}
				}
			}
			// Sender Item
			else if (SQLLoadItemBoxEx(pcUser) && pcUser->sItemBoxEx.iNumItems > 0)
			{
				//Show next ItemEx
				for (int i = 0; i < pcUser->sItemBoxEx.iNumItems; i++)
				{
					ItemBoxItemEx * psItemBoxItemEx = &pcUser->sItemBoxEx.saItemBoxEx[i];

					if (psItemBoxItemEx->bValid != FALSE)
					{
						psItemBoxItemEx->bValid = FALSE;

						if (SERVERITEM->ValidateItem(&psItemBoxItemEx->sItem, TRUE))
						{
							CopyMemory(&sPacket.sItem, &psItemBoxItemEx->sItem, sizeof(Item));

							//Put Item In Server Inventory
							if (sPacket.sItem.iPotionCount > 0)
								SERVERITEM->AddPotion(pcUser, sPacket.sItem.sItemID.ToInt(), sPacket.sItem.iPotionCount);
							else
								SERVERITEM->AddItemInventory(pcUser, sPacket.sItem.sItemID.ToItemID(), sPacket.sItem.iChk1, sPacket.sItem.iChk2);
						}
						else
							SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Error, "> %s Item Hack Change", psItemBoxItemEx->sItem.szItemName);

						//Update SQL Get Next Item
						SQLUpdateItemBoxEx(psItemBoxItemEx->iID);

						SENDPACKET(pcUser, &sPacket);
						break;
					}
				}
			}

			OpenDistributorItem(pcUser);
		}
	}
}
void CDistributorHandle::DeleteDistributorItem(User * pcUser)
{
	if (!GAME_SERVER)
	{
		if (pcUser->pcSocketData)
		{
			//Item Shop
			if (SQLLoadItemBox(pcUser) && pcUser->sItemBox.iNumItems > 0)
			{
				for (int i = 0; i < pcUser->sItemBox.iNumItems; i++)
				{
					ItemBoxItem * psItemBoxItem = &pcUser->sItemBox.saItemBox[i];

					if (psItemBoxItem->bValid != FALSE)
					{
						psItemBoxItem->bValid = FALSE;

						char szItemName[32] = { 0 };

						if (SERVERITEM->FindItemName(psItemBoxItem->iItemID, szItemName))
						{
							SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Global, "> %s Delete Item Sucess", szItemName);
						}
						//Update ID;
						SQLUpdateItemBox(psItemBoxItem->iID);
						break;
					}
				}
			}
			// Normal Item
			else if (SQLLoadItemBoxEx(pcUser) && pcUser->sItemBoxEx.iNumItems > 0)
			{
				for (int i = 0; i < pcUser->sItemBoxEx.iNumItems; i++)
				{
					ItemBoxItemEx * psItemBoxItemEx = &pcUser->sItemBoxEx.saItemBoxEx[i];

					if (psItemBoxItemEx->bValid != FALSE)
					{
						psItemBoxItemEx->bValid = FALSE;

						SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Global, "> %s Delete Item Sucess", psItemBoxItemEx->sItem.szItemName);

						//Update ID;
						SQLUpdateItemBoxEx(psItemBoxItemEx->iID);
						break;
					}
				}
			}

			OpenDistributorItem(pcUser);
		}
	}
}
void CDistributorHandle::HandlePacket(User * pcUser, PacketItemBoxSend * psPacket)
{
	char * pszCharName = psPacket->szCharacterName;

	int iCharNameLen = STRLEN(pszCharName);

	if (iCharNameLen > 0 && iCharNameLen < 32)
	{
		char * pszAccountName = SERVERUSER->SQLGetAccountByCharacterName(pszCharName);

		int iGold = 75000;

		if (pszAccountName && pszAccountName[0])
		{
			if (pcUser->GetGold() >= iGold)
			{
				Item sItem;

				CopyMemory(&sItem, &psPacket->sItem, sizeof(Item));

				if (SERVERITEM->DeleteItemInventory(pcUser, sItem.sItemID.ToInt(), sItem.iChk1, sItem.iChk2))
				{
					if (SERVERITEM->ValidateItem(&sItem, TRUE))
					{
						if (AddItemOpenBoxEx(pszAccountName, pszCharName, pcUser->szCharacterName, &sItem))
						{
							SERVERCHARACTER->GiveGold(pcUser, -iGold, WHEREID_Distributor);

							ZeroMemory(&psPacket->sItem, sizeof(Item));
							SENDPACKET(pcUser, psPacket);
						}
					}
				}

				SERVERUSER->SaveDropItem(pcUser, sItem.sItemID.ToInt(), sItem.iChk1, sItem.iChk2);
			}
			else
				SERVERCHAT->SendChatMessageBox(pcUser, "Not enough gold! You need %d gp!", iGold);
		}
		else
			SERVERCHAT->SendChatMessageBox(pcUser, "Please check the username");
	}
}