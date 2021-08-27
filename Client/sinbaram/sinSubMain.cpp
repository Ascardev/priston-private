#include "StdAfx.h"
#include "..\\tjboy\\clanmenu\\tjclanDEF.h"
#include "..\\tjboy\\clanmenu\\tjclan.h"
#include "..\\tjboy\\clanmenu\\Help.h"

#include "..\\FullZoomMap.h"


int sinTestFlag;
int sinSecretFlag = 0;


int sinMouseButton[2] = { 0,0 };
int sinKeyClick[256];

int MouseButtonUpEvent = 0;

int MatCursorDefault;
int MatCursorSell;
int MatCursorBuy;
int MatCursorRepair;
int MatCursorAttack;
int MatCursorGetItem1;
int MatCursorGetItem2;
int MatCursorTalk;

int CursorClass = 1;

int sinMoveKindInter[MAX_SIN_KIND_INTER] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }; //´°¿ÚÀà±ð

int sinSec = 0;
int sinMainCounter = 0;

float DeCreaSTM = 0;
float InCreaSTM = 0;
float InCreaLIFE = 0;
float InCreaMANA = 0;

char szTestBuff2[64];
POINT TestImageSize = { 0,0 };

int Accuracy_Table[][2] =
{
#include "sinTable.h"
	- 1
};


int ItemIndex1[3] = { 0,0,0 };
int ItemIndex2[3] = { 0,0,0 };

int ChangeJobButonCheck2 = 0;
int ItemImageNotExitFlag = 0;
int DownNum = 0;

char *sinSoundWav[] =
{
	"Image\\SinImage\\Sound\\interface-on.wav",		//0 (ÀÎÅÍÆäÀÌ½º First Start »ç¿îµå )
	"Image\\SinImage\\Sound\\Axes.wav",				//1	(Axe)
	"Image\\SinImage\\Sound\\Claws.wav",			//2 (Claws)
	"Image\\SinImage\\Sound\\Hammer.wav",			//3 (Hammer)
	"Image\\SinImage\\Sound\\Magicial_Stuffs.wav",	//4 (Magicial_Stuffs)
	"Image\\SinImage\\Sound\\Poles.wav",			//5 (Poles)
	"Image\\SinImage\\Sound\\Shooters.wav",			//6 (Shooters)
	"Image\\SinImage\\Sound\\Swords.wav",			//7 (Swords)
	"Image\\SinImage\\Sound\\Throwing.wav",			//8 (Throwing)
	"Image\\SinImage\\Sound\\Armor.wav",			//9 (·Îºê)
	"Image\\SinImage\\Sound\\Boots.wav",			//10 (Boots)
	"Image\\SinImage\\Sound\\Gloves.wav",			//11 (Gloves)
	"Image\\SinImage\\Sound\\Shields.wav",			//12 (Shields)
	"Image\\SinImage\\Sound\\Amulet.wav",			//13 (Amulet)
	"Image\\SinImage\\Sound\\Armlet.wav",			//14 (Armlet)
	"Image\\SinImage\\Sound\\Ring.wav",				//15 (Ring)
	"Image\\SinImage\\Sound\\Sheltom.wav",			//16 (Sheltom)
	"Image\\SinImage\\Sound\\Potion.wav",			//17 (Potion)
	"Image\\SinImage\\Sound\\Coin.wav",				//18 (Coin)
	"Image\\SinImage\\Sound\\Magicial_weapon.wav",	//19 (Magicial_weapon)
	"Image\\SinImage\\Sound\\drink1.wav",			//20 (¹°¾à¸Ô´Â »ç¿îµå)
	"Image\\SinImage\\Sound\\interface.wav",		//21 (ÀÎÅÍÆäÀÌ½º »ç¿îµå *Ã³À½½ÃÀÛÀ» Á¦¿ÜÇÏ°í ³ª¿À´Â »ç¿îµå)
	"Image\\SinImage\\Sound\\repair.wav",			//22 (¼ö¸®½Ã »ç¿îµå)
	"Image\\SinImage\\Sound\\sheltom-failure.wav",  //23 (¹Í½ºÃÄ, ¿¡ÀÌÂ¡ ½ÇÆÐ½Ã »ç¿îµå)
	"Image\\SinImage\\Sound\\Armor-w.wav",          //24 (°©¿Ê)
	"Image\\SinImage\\Sound\\drink2.wav",           //25 (±â·Â¾à »ç¿îµå)
	0
};

/*----------------------------------------------------------------------------*
*					    ¼­ºê¸ÞÀÎ ÃÊ±âÈ­
*-----------------------------------------------------------------------------*/
void InitSub()
{

}
/*----------------------------------------------------------------------------*
*						¼­ºê¸ÞÀÎ ¸ÞÀÎ
*-----------------------------------------------------------------------------*/
void MainSub()
{
	sinProc(SINKEYDOWN);
	sinSec++;
	sinMainCounter++;

	if (sinSec >= 70)
	{
		sinRegen();
		sinUseStamina();
		sinSec = 0;
	}
	if ((sinMainCounter & 3) == 0)
		sinSetRegen();

	if ((sinMainCounter % 70) == 0)
		AgingRing();

	cSkill.CheckSkillMastery();
	CheckContinueSkill();
}
void DrawSub()
{

}
void CloseSub()
{

}
void DrawSprite(int winX, int winY, smTEXTUREHANDLE *pdds, int x, int y, int width, int height, int Bltflag)
{
	if (Bltflag != 777)
		dsGetDrawOffset(&winX, &winY);

	if (pdds == nullptr)
		return;

	UI::ImageRender::Render(pdds->m_pTexture, winX, winY, width, height, x, y, -1);
}
void DrawRotSprite(int winX, int winY, LPDIRECT3DTEXTURE9 lpTexture, int x, int y, int width, int height)
{
	
}
int  sinGetItemInfo(DWORD CODE, char *szImagePath)
{
	if (!szImagePath) return FALSE;

	ItemData * pItemData = ITEMHANDLE->GetItemDataByID(CODE);

	if (pItemData)
	{
		wsprintf(szImagePath, "Image\\sinImage\\Items\\DropItem\\it%s.ASE", pItemData->szModelName);
		return TRUE;
	}

	return FALSE;
}

extern int DecodeCompress(BYTE *lpSrcData, BYTE *lpDestData);

int sinRecvMessage(DWORD dwCode, void *RecvBuff)
{
	Item *lpItemInfo;
	smTRANS_SELL_ITEM		*lpTransSellItem;
	BYTE *lpBuff;
	int cnt;

	switch (dwCode)
	{
	case smTRANSCODE_SHOP_ITEMLIST:
		lpTransSellItem = (smTRANS_SELL_ITEM *)RecvBuff;

		lpItemInfo = new Item[lpTransSellItem->ItemCounter];
		lpBuff = (BYTE *)RecvBuff + sizeof(smTRANS_SELL_ITEM);
		for (cnt = 0; cnt < lpTransSellItem->ItemCounter; cnt++)
			lpBuff += DecodeCompress(lpBuff, (BYTE *)&lpItemInfo[cnt]);
		sinSetShopItem(lpItemInfo, lpTransSellItem->ItemCounter, lpTransSellItem->ItemKind);
		delete lpItemInfo;
		break;
	}

	return TRUE;
}
int RecvCountFlag = 0;

int sinSetShopItem(Item *pItem, int ItemCount, int ItemKind)
{
	int i = 0;

	for (i = 0; i < SIN_MAX_HELP_NUMBER; i++)
	{
		if (sSinHelp[i].KindFlag)
			return FALSE;
	}

	ItemData sinTempItem;

	sinShopKind = ItemKind;

	if (sinShopKind == 2)
		sinShopKind = 1;

	RecvCountFlag++;

	if (RecvCountFlag == 1)
		memset(&cShop.ShopItem, 0, sizeof(ItemData) * 60);
	else
		RecvCountFlag = 0;

	if (sinShopKind == 3)
		RecvCountFlag = 0;

	for (i = 0; i < ItemCount; i++)
	{
		if (LoadItemImage(&pItem[i], &sinTempItem))
		{
			if (ItemKind == 2)
				memcpy(&cShop.ShopItem[i + 30], &sinTempItem, sizeof(ItemData));
			else
				memcpy(&cShop.ShopItem[i], &sinTempItem, sizeof(ItemData));
		}
	}
	TalkNpcState = 1;
	cShop.CopyShopItemToShow(0);
	cInterFace.CheckAllBox(SIN_SHOP);
	ShopArrowPosi = 0;
	return TRUE;
}

int sinSetQuestItem(Item *sItemInfo)
{
	sinSetSpecialItemCode(sItemInfo);

	int sArrowPosi = 0, i = 0;
	ItemData sinTempItem;

	if (sinChar->iRank == 0 && !sinQuest_ChangeJob.CODE && !sinQuest_ChangeJob2.CODE)
	{
		if ((sItemInfo->sItemID.ToInt() == (sinQT1 | sin01)) ||
			(sItemInfo->sItemID.ToInt() == (sinQT1 | sin02)) ||
			(sItemInfo->sItemID.ToInt() == (sinQT1 | sin03)) ||
			(sItemInfo->sItemID.ToInt() == (sinQT1 | sin04)) ||
			(sItemInfo->sItemID.ToInt() == (sinQT1 | sin05)) ||
			(sItemInfo->sItemID.ToInt() == (sinQT1 | sin06)))
			return FALSE;
	}
	if (sinQuest_ChangeJob.CODE == SIN_QUEST_CODE_CHANGEJOB)
	{
		if (cInvenTory.SearchItemCode(sItemInfo->sItemID.ToInt()))
			return FALSE;
		if (sItemInfo->sItemID.ToInt() == (sinQT1 | sin04))
			return FALSE;
		if (sItemInfo->sItemID.ToInt() == (sinQT1 | sin05))
			return FALSE;
	}
	if (sinQuest_ChangeJob2.CODE == SIN_QUEST_CODE_CHANGEJOB2_NPC_M || sinQuest_ChangeJob2.CODE == SIN_QUEST_CODE_CHANGEJOB2_NPC_D)
	{
		if (sItemInfo->sItemID.ToInt() == (sinQT1 | sin01))
			return FALSE;
		if (sItemInfo->sItemID.ToInt() == (sinQT1 | sin02))
			return FALSE;
		if (sItemInfo->sItemID.ToInt() == (sinQT1 | sin03))
			return FALSE;
		if (sItemInfo->sItemID.ToInt() == (sinQT1 | sin06))
			return FALSE;
	}
	if (sinChar->iRank >= 1)
	{
		if ((sItemInfo->sItemID.ToInt() == (sinQT1 | sin01)) ||
			(sItemInfo->sItemID.ToInt() == (sinQT1 | sin02)) ||
			(sItemInfo->sItemID.ToInt() == (sinQT1 | sin03)) ||
			(sItemInfo->sItemID.ToInt() == (sinQT1 | sin04)) ||
			(sItemInfo->sItemID.ToInt() == (sinQT1 | sin05)))
			return FALSE;
	}
	if (sinQuest_ChangeJob3.CODE == SIN_QUEST_CODE_CHANGEJOB3)
	{
		if (sItemInfo->sItemID.ToInt() == (sinQT1 | sin01))
			return FALSE;
		if (sItemInfo->sItemID.ToInt() == (sinQT1 | sin02))
			return FALSE;
		if (sItemInfo->sItemID.ToInt() == (sinQT1 | sin03))
			return FALSE;
		if (sItemInfo->sItemID.ToInt() == (sinQT1 | sin04))
			return FALSE;
		if (sItemInfo->sItemID.ToInt() == (sinQT1 | sin05))
			return FALSE;
	}
	if (!sinQuest_Level80_2.CODE)
	{
		if (sItemInfo->sItemID.ToInt() == (sinQT1 | sin09))
			return FALSE;
		if (sItemInfo->sItemID.ToInt() == (sinQT1 | sin10))
			return FALSE;
		if (sItemInfo->sItemID.ToInt() == (sinQT1 | sin11))
			return FALSE;
	}
	else
	{
		if (cInvenTory.SearchItemCode(sinQT1 | sin09))
		{
			if (sItemInfo->sItemID.ToInt() == (sinQT1 | sin09))
				return FALSE;
		}
		if (cInvenTory.SearchItemCode(sinQT1 | sin10))
		{
			if (sItemInfo->sItemID.ToInt() == (sinQT1 | sin10))
				return FALSE;
		}
		if (cInvenTory.SearchItemCode(sinQT1 | sin11))
		{
			if (sItemInfo->sItemID.ToInt() == (sinQT1 | sin11))
				return FALSE;
		}
	}

	if (sItemInfo->sItemID.ToInt() == (sinQT1 | sin06) && sinQuest_ChangeJob3.State >= 3)
		return FALSE;

	if (sinChar->iRank >= 2 && sItemInfo->sItemID.ToInt() == (sinQT1 | sin06))
		return FALSE;

	switch (sItemInfo->sItemID.ToItemType())
	{
	case sinQT1:
		sItemInfo->eCraftType = ITEMCRAFTTYPE_Quest;
		break;
	case sinSP1:
		sItemInfo->eCraftType = ITEMCRAFTTYPE_Event;
		break;
	}
	if (LoadItemImage(sItemInfo, &sinTempItem))
	{
		if (sinTempItem.sItem.iPotionCount <= 0)
			sinTempItem.sItem.iPotionCount = 1;

		if (!cInvenTory.AutoSetInvenItem(&sinTempItem, 1))
		{
			if (ArrowState[0] == 0)
				sArrowPosi = 2;
			else
				sArrowPosi = 1;
			sinButtonFlag = sArrowPosi;
			SelectInvenItemIndex = 0;
			cInvenTory.ChangeABItem(sArrowPosi);
			if (!cInvenTory.AutoSetInvenItem(&sinTempItem, 1))
			{
				sinTempItem.bValid = 0;
				return FALSE;
			}
		}
	}

	return TRUE;
}

int CheckPotionDelayFlag = 0;

int sinSetInvenItem(Item *sItemInfo)
{
	SpecialItemShowFlag = 0;
	sinSetSpecialItemCode(sItemInfo);
	ItemData sinTempItem;
	pMessageItem = 0;

	if (LoadItemImage(sItemInfo, &sinTempItem))
	{
		if (sinTempItem.sItem.iPotionCount <= 0)
			sinTempItem.sItem.iPotionCount = 1;

		if (MouseItem.bValid || g_IsDxProjectZoomIn)
		{
			if (cInvenTory.CheckRequireItemToSet(&sinTempItem))
			{
				if (!cInvenTory.AutoSetInvenItem(&sinTempItem))
				{
					if (sinThrowItemToFeild(&sinTempItem))
						sinTempItem.bValid = 0;
				}
				else
				{
					cInvenTory.SetItemToChar();
					cInvenTory.CheckWeight();
				}
			}
		}
		else
		{
			if (cInvenTory.OpenFlag)
			{
				if (sinTempItem.iItemSlotFlag == ITEMSLOTFLAG_Potion)
				{
					if (sinTempItem.sItem.iPotionCount + sinChar->sWeight.sMin > sinChar->sWeight.sMax)
					{
						cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
						sinOverWeightCnt++;
						sinThrowItemToFeild(&sinTempItem);
						return FALSE;
					}
				}
				else
				{
					if (sinTempItem.sItem.iWeight + sinChar->sWeight.sMin > sinChar->sWeight.sMax)
					{
						cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
						sinOverWeightCnt++;
						sinThrowItemToFeild(&sinTempItem);
						return FALSE;
					}
				}
				cInvenTory.CheckRequireItemToSet(&sinTempItem);
				memcpy(&MouseItem, &sinTempItem, sizeof(ItemData));
				cInvenTory.ReFormMousePotionNum();
			}

			else
			{
				if (cInvenTory.CheckRequireItemToSet(&sinTempItem))
				{
					if (!cInvenTory.AutoSetInvenItem(&sinTempItem))
					{
						if (sinThrowItemToFeild(&sinTempItem))
							sinTempItem.bValid = 0;
					}
					else
					{
						cInvenTory.SetItemToChar();
						cInvenTory.CheckWeight();
					}
				}
			}
		}
	}

	CURSORHANDLE->SetMouseCursor(MouseItem.bValid ? ECURSORICON_None : ECURSORICON_Default);

	SaveGameData();
	return TRUE;
}

DWORD sinSpecialCODE[] =
{
	(sinQT1 | sin01),(sinQT1 | sin02),(sinQT1 | sin03),(sinQT1 | sin04),(sinQT1 | sin05),(sinQT1 | sin06),
	(sinMA1 | sin01),(sinMA2 | sin01),(sinMA2 | sin02),(sinQW1 | sin01),(sinQW1 | sin02),(sinQW1 | sin03),
	(sinQW1 | sin04),(sinQW1 | sin05),(sinQT1 | sin07),(sinQT1 | sin08),
	(sinQT1 | sin09),(sinQT1 | sin10),(sinQT1 | sin11),(sinQT1 | sin12),(sinQT1 | sin13),
	(sinQT1 | sin14),(sinQT1 | sin15),(sinQT1 | sin16),(sinQW1 | sin06),(sinQT1 | sin17),(sinQT1 | sin18),(sinQT1 | sin19),
	0
};

int sinSetSpecialItemCode(Item *pItemInfo)
{
	int Count = 0;
	while (1)
	{
		if (sinSpecialCODE[Count])
		{
			if (pItemInfo->sItemID.ToInt() == sinSpecialCODE[Count])
			{
				pItemInfo->SpecialItemFlag[1] = ITEMCRAFTTYPE_Special;
				break;
			}
			Count++;
		}
		else break;
	}
	cInvenTory.ChangeSpecialItem(2);
	return TRUE;
}
int LoadItemImage(Item *sItemInfo, ItemData *TempItem)
{
	char szFilePath[256];
	szTestBuff2[0] = 0;

	ItemData * pItemData = ITEMHANDLE->GetItemDataByID(sItemInfo->sItemID.ToInt());

	if (pItemData)
	{
		wsprintf(szFilePath, "Image\\sinImage\\Items\\%s\\it%s.bmp", pItemData->szCategory, pItemData->szInventoryName);
		memcpy(TempItem, pItemData, sizeof(ItemData));

		memcpy(&TempItem->sItem, sItemInfo, sizeof(Item));
		if (!pItemData->pcTempInventoryTexture)
			pItemData->pcTempInventoryTexture = LoadDibSurfaceOffscreen(szFilePath);
		TempItem->pcInventoryTexture = pItemData->pcTempInventoryTexture;
		TestImageSize.x = TempItem->iWidth;
		TestImageSize.y = TempItem->iHeight;
		if (!TempItem->pcInventoryTexture)
		{
			lstrcpy(szTestBuff2, pItemData->szInventoryName);
			ItemImageNotExitFlag = 1;
			cMessageBox.ShowMessage(MESSAGE_NOTEXIT_ITEMIMAGE);
		}

		TempItem->bValid = 1;
		return TRUE;
	}

	return FALSE;
}
void sinLButtonUp()
{
	MouseButtonUpEvent = SINLBUTTONUP;
}
void sinRButtonUp()
{
	MouseButtonUpEvent = SINRBUTTONUP;
}
void sinLButtonDown()
{

}
int sinGetMouseButton(int num)
{
	if (MouseButton[num] && !sinMouseButton[num])
	{
		sinMouseButton[num] = TRUE;
		return TRUE;
	}
	return FALSE;
}
void sinMouseMain()
{
	int cnt;
	for (cnt = 0; cnt < 2; cnt++)
	{
		if (!MouseButton[cnt])
		{
			if (sinMouseButton[cnt])
				sinMouseButton[cnt] = FALSE;
		}
	}
}

int sinGetKeyClick(int num)
{
	if (VRKeyBuff[num] && !sinKeyClick[num])
	{
		sinKeyClick[num] = TRUE;
		return TRUE;
	}
	return FALSE;
}

void sinKeyClickMain()
{
	int cnt;
	for (cnt = 0; cnt < 255; cnt++)
	{
		if (!VRKeyBuff[cnt])
		{
			if (sinKeyClick[cnt])
				sinKeyClick[cnt] = FALSE;
		}
	}
}

void *szKindInter[] =
{
	&cCharStatus,
	&cInvenTory,
	&cShop,
	&cSkill,
	&cTrade,
	&cWareHouse,
	&cCraftItem,
	&cAging,
	&cMyShop,
	&cCharShop,
	&SmeltingItem,
	&ManufactureItem,
	&cMixtureReset,
	&cElement,
	&cCaravan,
	&cSocket,
	0,
};

class sinFlag
{
public:
	int	OpenFlag;
};

int FirstMove[MAX_SIN_KIND_INTER] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };// ´°¿Ú

void ShowInterFace()
{
	int cnt = 0;
	int StopMove[MAX_SIN_KIND_INTER] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }; // ´°¿Ú

	while (szKindInter[cnt] != 0)
	{
		if (((sinFlag *)szKindInter[cnt])->OpenFlag > 0)
		{
			if (!FirstMove[cnt])
			{
				if (cnt == SIN_SHOP || cnt == SIN_TRADE || cnt == SIN_WAREHOUSE || cnt == SIN_CRAFTITEM || cnt == SIN_AGING || cnt == SIN_MYSHOP || cnt == SIN_CHARSHOP || cnt == SIN_SMELTING || cnt == SIN_MANUFACTURE || cnt == SIN_MIXTURE_RESET || cnt == SIN_ELEMENT || cnt == SIN_CARAVAN || cnt == SIN_SOCKET)
				{
					sinMoveKindInter[cnt] += 184 + 128;
					FirstMove[cnt] = 1;

				}
				else
				{
					sinMoveKindInter[cnt] += 184;
					FirstMove[cnt] = 1;
				}
			}
			else
			{
				if (cnt == SIN_SHOP || cnt == SIN_TRADE || cnt == SIN_WAREHOUSE || cnt == SIN_CRAFTITEM || cnt == SIN_AGING || cnt == SIN_MYSHOP || cnt == SIN_CHARSHOP || cnt == SIN_SMELTING || cnt == SIN_MANUFACTURE || cnt == SIN_MIXTURE_RESET || cnt == SIN_ELEMENT || cnt == SIN_CARAVAN || cnt == SIN_SOCKET)
				{
					if (sinMoveKindInter[cnt] >= 256 + 128)
					{
						sinMoveKindInter[cnt] = 256 + 128;
						StopMove[cnt] = 1;

					}
					if (!StopMove[cnt])
					{
						sinMoveKindInter[cnt] += 7;
						if (sinMoveKindInter[cnt] >= 200 + 128)
							sinMoveKindInter[cnt] -= 2;
						if (sinMoveKindInter[cnt] >= 230 + 128)
							sinMoveKindInter[cnt] -= 2;
					}

				}
				else
				{
					if (sinMoveKindInter[cnt] >= 256)
					{
						sinMoveKindInter[cnt] = 256;
						StopMove[cnt] = 1; // ´°¿ÚÍ£Ö¹

					}
					if (!StopMove[cnt])
					{
						sinMoveKindInter[cnt] += 7;
						if (sinMoveKindInter[cnt] >= 200)
							sinMoveKindInter[cnt] -= 2;
						if (sinMoveKindInter[cnt] >= 230)
							sinMoveKindInter[cnt] -= 2;
					}
				}
			}
		}
		else
		{
			if (cnt == 1)
				SelectPotionIndex = 0;

			if (sinMoveKindInter[cnt] > 0)
				sinMoveKindInter[cnt] -= 16;
			else
			{
				sinMoveKindInter[cnt] = 0;
				FirstMove[cnt] = 0;
			}
		}
		cnt++;
	}
}
int CheckEditSize(int x, int lx, char *String)
{
	int len = 0;
	int ResultX = 0;
	int Temp = 0, Temp2 = 0, Temp3 = 0;

	len = lstrlen(String);

	Temp = lx - x;
	Temp2 = (Temp - len * 6) / 2;

	return Temp2 + x;
}

#define SIN_POTION_LIFE			1
#define SIN_POTION_MANA			2
#define SIN_POTION_STAMINA		3
#define SIN_POTION_SONGPYEUN	4

int sinUsePotion()
{
	CheckCharForm();

	int PotionKind = 0;
	int ResultPotion = 0;
	int TempRandPotion = 0;

	if (pUsePotion == 0)
		return FALSE;
	if (!pUsePotion->bValid)
		return FALSE;
	if (MouseItem.bValid)
	{
		if (MouseItem.sItem.iChk1 == pUsePotion->sItem.iChk1)
			return FALSE;
	}

	if ((pUsePotion->sBaseItemID.ToInt() & sinITEM_MASK2) == sinPL1)
	{
		TempRandPotion = pUsePotion->sItem.sHPRecovery.sMax - pUsePotion->sItem.sHPRecovery.sMin;
		ResultPotion = pUsePotion->sItem.sHPRecovery.sMin + (rand() % TempRandPotion);
		sinSetLife((sinGetLife() + ResultPotion));
		PotionKind = SIN_POTION_LIFE;
	}
	if ((pUsePotion->sBaseItemID.ToInt() & sinITEM_MASK2) == sinPM1)
	{
		TempRandPotion = pUsePotion->sItem.sMPRecovery.sMax - pUsePotion->sItem.sMPRecovery.sMin;
		ResultPotion = pUsePotion->sItem.sMPRecovery.sMin + (rand() % TempRandPotion);
		sinSetMana((sinGetMana() + ResultPotion));
		PotionKind = SIN_POTION_MANA;
	}
	if ((pUsePotion->sBaseItemID.ToInt() & sinITEM_MASK2) == sinPS1)
	{
		TempRandPotion = pUsePotion->sItem.sSPRecovery.sMax - pUsePotion->sItem.sSPRecovery.sMin;
		ResultPotion = pUsePotion->sItem.sSPRecovery.sMin + (rand() % TempRandPotion);
		sinSetStamina((sinGetStamina() + ResultPotion));
		PotionKind = SIN_POTION_STAMINA;
	}
	if ((pUsePotion->sBaseItemID.ToInt() & sinITEM_MASK2) == sinSP1)
	{
		if ((pUsePotion->sBaseItemID.ToInt() & sinITEM_MASK3) == sin01 || (pUsePotion->sBaseItemID.ToInt() & sinITEM_MASK3) == sin02 ||
			(pUsePotion->sBaseItemID.ToInt() & sinITEM_MASK3) == sin03 || (pUsePotion->sBaseItemID.ToInt() & sinITEM_MASK3) == sin15 ||
			(pUsePotion->sBaseItemID.ToInt() & sinITEM_MASK3) == sin35 ||
			(pUsePotion->sBaseItemID.ToInt() & sinITEM_MASK3) == sin36 || (pUsePotion->sBaseItemID.ToInt() & sinITEM_MASK3) == sin42)
		{
			pUsePotion->sItem.iPotionCount = 0;
			if (cInvenTory.EatSongPyeun(pUsePotion))
				PotionKind = SIN_POTION_SONGPYEUN;
			else
				PotionKind = 5;
		}
		if ((pUsePotion->sBaseItemID.ToInt() & sinITEM_MASK3) == sin05 ||
			(pUsePotion->sBaseItemID.ToInt() & sinITEM_MASK3) == sin06 ||
			(pUsePotion->sBaseItemID.ToInt() & sinITEM_MASK3) == sin07 ||
			(pUsePotion->sBaseItemID.ToInt() & sinITEM_MASK3) == sin08 ||
			(pUsePotion->sBaseItemID.ToInt() & sinITEM_MASK3) == sin09 ||
			(pUsePotion->sBaseItemID.ToInt() & sinITEM_MASK3) == sin10)
		{
			PotionKind = 6;
		}

		if ((pUsePotion->sBaseItemID.ToInt() & sinITEM_MASK3) == sin34)
			PotionKind = 7;
	}
	if (PotionKind)
	{
		if (pUsePotion->sItem.iPotionCount >= 2)
		{
			pUsePotion->sItem.iPotionCount--;
			sinPlaySound(SIN_SOUND_EAT_POTION);
		}
		else
		{
			pUsePotion->bValid = 0;
			sInven[pUsePotion->iItemSlot - 1].ItemIndex = 0;
			if (PotionKind != 5)
				sinPlaySound(SIN_SOUND_EAT_POTION);
		}

		pUsePotion = 0;
		ReformCharForm();
		cInvenTory.CheckWeight();
		cInvenTory.ReFormPotionNum();
		cInvenTory.ReFormInvenItem();
		return PotionKind;
	}

	return FALSE;

}
void sinRegen()
{
	InCreaSTM = 0;
	InCreaMANA = 0;
	InCreaLIFE = 0;

	float	fLevel = 0;
	float	fStrength = 0;
	float	fHealth = 0;
	float	fSpirit = 0;

	if (lpCurPlayer->psModelAnimation->iType == ANIMATIONTYPE_Idle)
	{
		switch (sinChar->iSPType)
		{
		case 1:
			InCreaSTM = (float)(3.8 + sinChar->iLevel / 7 + sinChar->fSPRegen);
			break;
		case 2:
			InCreaSTM = (float)(3.3 + sinChar->iLevel / 7 + sinChar->fSPRegen);
			break;
		case 3:
			InCreaSTM = (float)(2.9 + sinChar->iLevel / 7 + sinChar->fSPRegen);
			break;
		default:
			InCreaSTM = (float)(3.8 + sinChar->iLevel / 7 + sinChar->fSPRegen);
			break;
		}

	}
	if (lpCurPlayer->psModelAnimation->iType == ANIMATIONTYPE_Walking)
	{
		switch (sinChar->iSPType)
		{
		case 1:
			InCreaSTM = (float)((3.8 + sinChar->iLevel / 7 + sinChar->fSPRegen)*0.6);
			break;
		case 2:
			InCreaSTM = (float)((3.3 + sinChar->iLevel / 7 + sinChar->fSPRegen)*0.6);
			break;
		case 3:
			InCreaSTM = (float)((2.9 + sinChar->iLevel / 7 + sinChar->fSPRegen)*0.6);
			break;
		default:
			InCreaSTM = (float)((3.8 + sinChar->iLevel / 7 + sinChar->fSPRegen)*0.6);
			break;
		}
	}
	fLevel = (float)sinChar->iLevel;
	fStrength = (float)sinChar->iStrength;
	fHealth = (float)sinChar->iHealth;
	fSpirit = (float)sinChar->iSpirit;

	if (lpCurPlayer->psModelAnimation->iType != ANIMATIONTYPE_Die)
	{
		InCreaLIFE = (float)(((fLevel + (fStrength / 2) + fHealth) / 180 + sinChar->fHPRegen) / 1.5);
		InCreaMANA = (fLevel + (fSpirit*1.2f) + (fHealth / 2)) / 115 + sinChar->fMPRegen;
	}
}

void sinUseStamina()
{
	DeCreaSTM = 0;
	if (lpCurPlayer->psModelAnimation->iType == ANIMATIONTYPE_Running)
		DeCreaSTM = (float)((1000 + sinChar->sWeight.sMin) / (sinChar->sWeight.sMax + (sinChar->iStrength / 2) + 500) + 0.4);
}


float fTempLIFE = 0;
float fTempMANA = 0;
float fTempSTM_Incre = 0;
float fTempSTM_Decre = 0;

void sinSetRegen()
{
	CheckCharForm();

	if (DeCreaSTM)
	{
		fTempSTM_Decre += DeCreaSTM / (70 / 4);
		if (fTempSTM_Decre >= 1)
		{
			sinSetStamina(sinGetStamina() - (short)fTempSTM_Decre);
			fTempSTM_Decre -= 1;
		}
	}
	if (InCreaSTM)
	{
		fTempSTM_Incre += InCreaSTM / (70 / 4);
		if (fTempSTM_Incre >= 1)
		{
			sinSetStamina(sinGetStamina() + (short)fTempSTM_Incre);
			while (1)
			{
				if (fTempSTM_Incre > 1)
					fTempSTM_Incre -= 1;
				else
					break;
			}
		}
	}

	if (InCreaLIFE)
	{
		fTempLIFE += InCreaLIFE / (70 / 4);
		if (fTempLIFE >= 1)
		{
			sinSetLife(sinGetLife() + (short)fTempLIFE);
			while (1)
			{
				if (fTempLIFE > 1)
					fTempLIFE -= 1;
				else
					break;
			}
		}
	}

	if (InCreaMANA)
	{
		fTempMANA += InCreaMANA / (70 / 4);
		if (fTempMANA >= 1)
		{
			sinSetMana(sinGetMana() + (short)fTempMANA);
			while (1)
			{
				if (fTempMANA > 1)
					fTempMANA -= 1;
				else
					break;
			}
		}
	}
	ReformCharForm();
}
int sinGetAC(int AC)
{
	int cnt = 0;
	while (1)
	{
		if (Accuracy_Table[cnt][0] == 0)
			break;
		if (AC > Accuracy_Table[cnt][0] && AC < Accuracy_Table[cnt + 1][0])
			return Accuracy_Table[cnt + 1][1];
		cnt++;
	}
	return FALSE;
}

int cnt = 0;
int AC_R = 0;
int RealAC = 0;
int Result = 0;
float fDesLV = 0;
float fMyLV = 0;
float fWeifht[2] = { 0,0 };


int sinGetAccuracy(int desLV, int desDefense)
{
	cnt = 0;
	AC_R = (int)(((float)sinChar->iAttackRating - (float)desDefense)*1.4);

	while (1)
	{
		if (AC_R < -190)
		{
			RealAC = 50;
			break;
		}
		if (AC_R > 2100)
		{
			RealAC = 95;
			break;
		}
		if (Accuracy_Table[cnt][1] == 0)
			break;
		if (AC_R >= Accuracy_Table[cnt][0] && AC_R <= Accuracy_Table[cnt + 1][0])
		{
			RealAC = Accuracy_Table[cnt + 1][1];
			break;

		}
		cnt++;
	}
	fDesLV = (float)desLV;
	fMyLV = (float)sinChar->iLevel;
	fWeifht[0] = sinChar->sWeight.sMin;
	fWeifht[1] = sinChar->sWeight.sMax;

	Result = (int)(RealAC - ((fDesLV - fMyLV) / 100) * 28);

	if (Result < 30)
		Result = 30;
	if (Result > 95)
		Result = 95;
	return Result;
}
int sinGetMonsterAccuracy(int MonsterLV, int MonsterAttack_Rating)
{
	cnt = 0;
	AC_R = (MonsterAttack_Rating - sinChar->iDefenseRating) * 2;

	while (1)
	{
		if (Accuracy_Table[cnt][0] == 0)
			break;
		if (AC_R > Accuracy_Table[cnt][0] && AC_R < Accuracy_Table[cnt + 1][0])
		{
			RealAC = Accuracy_Table[cnt + 1][1];
			break;

		}
		cnt++;
	}
	fDesLV = (float)sinChar->iLevel;
	fMyLV = (float)MonsterLV;

	Result = (int)(RealAC - ((fDesLV - fMyLV) / 100) * 50);

	if (Result < 30)
		Result = 30;
	if (Result > 95)
		Result = 95;

	return Result;
}
int sinGetPVPAccuracy(int MyLevel, int MyAttack_Rating, int DesLevel, int DesDefense)
{
	cnt = 0;
	AC_R = (int)(((float)MyAttack_Rating - (float)DesDefense)*1.4);

	while (1)
	{
		if (AC_R < -190)
		{
			RealAC = 50;
			break;
		}
		if (AC_R > 2100)
		{
			RealAC = 95;
			break;
		}
		if (Accuracy_Table[cnt][1] == 0)
			break;
		if (AC_R > Accuracy_Table[cnt][0] && AC_R < Accuracy_Table[cnt + 1][0])
		{
			RealAC = Accuracy_Table[cnt + 1][1];
			break;

		}
		cnt++;
	}
	fDesLV = (float)DesLevel;
	fMyLV = (float)MyLevel;

	Result = (int)(RealAC - ((fDesLV - fMyLV) / 100) * 28);

	if (Result < 30)
		Result = 30;
	if (Result > 95)
		Result = 95;
	return Result;
}
int sinGetCritical(int desLV)
{
	fDesLV = (float)desLV;
	fMyLV = (float)sinChar->iLevel;

	Result = (int)(sinChar->iCritical + ((fMyLV - fDesLV) / 100) * 25);
	if (Result > 70)
		Result = 70;

	return Result;
}
int sinGetBlockRating(int desLV)
{
	fDesLV = (float)desLV;
	fMyLV = (float)sinChar->iLevel;

	Result = (int)(sinChar->iBlockRating + ((fMyLV - fDesLV) / 100) * 25);
	return Result;
}

#define SIN_MONSTER_UNDEAD		1

int sinGetAbsorb(int Type)
{
	switch (Type)
	{
	case SIN_MONSTER_UNDEAD:
		return sinChar->iAbsorbRating + sinUndeadAbsorb;
		break;
	default:
		return sinChar->iAbsorbRating;
		break;
	}
	return TRUE;
}


void sinReload()
{
	cCharStatus.Release(); ///////Release
	cInterFace.Release();
	cInvenTory.Release();
	cItem.Release();
	cMessageBox.Release();
	cShop.Release();
	cSkill.Release();
	cTrade.Release();
	cInvenTory.InvenItemRelease();

	cCharStatus.Load(); ///////Load
	cInterFace.Load();
	cInvenTory.Load();
	cItem.Load();
	cMessageBox.Load();
	cShop.Load();
	cSkill.Load();
	cTrade.Load();
	cInvenTory.InvenItemLoad();

	chaSiege.Release();
}

int StopCharMotion(int x, int y)
{
	if (MOUSEHANDLER->IsNoMove())
		return TRUE;

	if (SkillMasterFlag && sinChangeJobButtonShow)
	{
		if (x > 240 && x < 240 + 44 && y > 380 && y < 380 + 44)
		{
			if (CheckNowQuestState(SIN_QUEST_CODE_CHANGEJOB))
			{
				if (!chaQuest.haQuestCheck(0))
					return FALSE;

				sinChangeJobButtonShow = 0;
				SkillMasterFlag = 0;
				HelpBoxKindIndex = SIN_CHANGEJOB_MESSAGE;
				cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath[0]);
				ChangeJobButonCheck2 = 1;
				return TRUE;
			}
		}
	}

	char ch = 0;

	if (SkillMasterFlag && sinChangeJobButtonShow2)
	{
		if (x > 240 && x < 240 + 44 && y > 380 && y < 380 + 44)
		{
			if (CheckNowQuestState(SIN_QUEST_CODE_CHANGEJOB2_NPC_M) || CheckNowQuestState(SIN_QUEST_CODE_CHANGEJOB2_NPC_D))
			{
				if (!chaQuest.haQuestCheck(0))
					return FALSE;

				sinChangeJobButtonShow2 = 0;
				SkillMasterFlag = 0;

				int len = lstrlen(sinChar->szName);

				for (int cnt = 0; cnt < len; cnt++)
					ch += sinChar->szName[cnt];
				if ((ch & 2) == 0)
					sinQuest_ChangeJob2.Kind = 1;
				else
					sinQuest_ChangeJob2.Kind = 2;

				cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath[sinQuest_ChangeJob2.Kind + 9]);
				ChangeJobButonCheck2 = 1;
				return TRUE;
			}
		}
	}
	if (SkillMasterFlag && sinChangeJobButtonShow3)
	{
		if (x > 240 && x < 240 + 44 && y > 380 && y < 380 + 44)
		{
			if (CheckNowQuestState(SIN_QUEST_CODE_CHANGEJOB3))
			{
				sinChangeJobButtonShow3 = 0;
				SkillMasterFlag = 0;
				cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath3[0]);
				ChangeJobButonCheck2 = 1;
			}
		}
	}

	if (SkillMasterFlag && sinChangeJobButtonShow4 != 0)
	{
		if (x > 240 && x < 240 + 44 && y > 380 && y < 380 + 44)
		{
			if (CheckNowQuestState(SIN_QUEST_CODE_CHANGEJOB4))
			{
				sinChangeJobButtonShow4 = 0;
				SkillMasterFlag = 0;
				cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath4[0]);
				ChangeJobButonCheck2 = 1;
			}
		}
	}

	for (int i = 0; i < SIN_MAX_HELP_NUMBER; i++)
	{
		if (sSinHelp[i].KindFlag)
			return TRUE;
	}
	
	// ¼ÙÈçÊÇÉèÖÃÄ£Ê½½ûÖ¹×ß¶¯
	if (SkillNpcFlag || sinMessageBoxShowFlag || MouseItem.bValid || cWareHouse.OpenFlag || cTrade.OpenFlag || cCraftItem.OpenFlag || cAging.OpenFlag || cMyShop.OpenFlag || cCharShop.OpenFlag || SmeltingItem.OpenFlag || ManufactureItem.m_OpenFlag || cMixtureReset.OpenFlag || cElement.OpenFlag || cCaravan.OpenFlag || cSocket.OpenFlag)
		return TRUE;

	if (cCharStatus.OpenFlag || cInvenTory.OpenFlag || cSkill.OpenFlag)
		if (y > 425)
			return TRUE;
	if (cShop.OpenFlag)
		if (x > 0 && x < 384 && y > 40 && y < 370 - 40)
			return TRUE;
	if (cWareHouse.OpenFlag)
		if (x > 0 && x < 384 && y > 40 && y < 370 - 40)
			return TRUE;

	if (y > 540 && x > 270)
		return TRUE;

	if (RequestTradeButtonFlag)
		return TRUE;
	if (sSinWarpGate.ShowFlag)
		return TRUE;

	if (HoStopCharMotion())
		return TRUE;
	if (isDrawClanMenu)
		return TRUE;

	if (MyShopSendButton)
		return TRUE;

	if (PetMessageOkButtonFlag)
		return TRUE;

	if (ContinueSkillMouseIndex)
		return TRUE;

	if (haSiegeMenuFlag)
		return TRUE;

	if (haMovieFlag)
		return TRUE;

	for (int i = 0; i < SINUPKEEPITEM_MAX; i++)
	{
		if (chaPremiumitem.UpKeepItem[i].Infoflag == true)
			return TRUE;
	}

	return FALSE;
}

int CheatHelpOpenFlag = 0;

void sinTestDrawText()
{
	char strBuff[128];

	DWORD Color = D3DCOLOR_XRGB(255, 255, 0);

	if (sinTestFlag)
	{
		wsprintf(strBuff, "°ø°Ý¼Óµµ:%d", sinChar->iAttackSpeed);
		dsTextLineOut(0, 100, 300, strBuff, lstrlen(strBuff), Color);

		wsprintf(strBuff, "ºí·°À²:%d", sinChar->iBlockRating + sinTempBlock);
		dsTextLineOut(0, 200, 300, strBuff, lstrlen(strBuff), Color);

		wsprintf(strBuff, "Å©¸®Æ¼ÄÃ:%d", sinChar->iCritical);
		dsTextLineOut(0, 300, 300, strBuff, lstrlen(strBuff), Color);

		wsprintf(strBuff, "½´ÆÃ±æÀÌ:%d", sinChar->iAttackRange);
		dsTextLineOut(0, 400, 300, strBuff, lstrlen(strBuff), Color);

	}
	if (SETTINGHANDLE->Get().bDebugMode)
	{
		if (sinSecretFlag)
		{
			if (CheatHelpOpenFlag)
			{
				wsprintf(strBuff, "(P) ´ÙÀ½°æÇèÄ¡±îÁö 10% ");
				dsTextLineOut(0, 100, 200, strBuff, lstrlen(strBuff), Color);

				wsprintf(strBuff, "(L) µ· 200000 ");
				dsTextLineOut(0, 100, 230, strBuff, lstrlen(strBuff), Color);

				wsprintf(strBuff, "(B) LV 65 µ· 300000");
				dsTextLineOut(0, 100, 260, strBuff, lstrlen(strBuff), Color);

				wsprintf(strBuff, "(Y) ¹Í½ºÃÄ ¾ÆÀÌÅÛ ½ÇÇà ");
				dsTextLineOut(0, 100, 290, strBuff, lstrlen(strBuff), Color);

				wsprintf(strBuff, "(U) Àü¾÷  ");
				dsTextLineOut(0, 100, 320, strBuff, lstrlen(strBuff), Color);

				wsprintf(strBuff, "(F) ¼÷·Ãµµ Up  ");
				dsTextLineOut(0, 100, 350, strBuff, lstrlen(strBuff), Color);

				wsprintf(strBuff, "(N) ¼÷·Ãµµ Down  ");
				dsTextLineOut(0, 100, 380, strBuff, lstrlen(strBuff), Color);
			}
		}
	}
}

void sinTestKey()
{
	int TempExp = 0;
	int TempExp2 = 0;

	int CountTemp = 0;

	if (SETTINGHANDLE->Get().bDebugMode)
	{
		if (sinGetKeyClick('I'))
		{
			sinCheckAgingLevel(SIN_AGING_ATTACK, false);
			sinCheckAgingLevel(SIN_AGING_DEFENSE_ARMOR, false);
			sinCheckAgingLevel(SIN_AGING_DEFENSE_ORB, false);
			sinCheckAgingLevel(SIN_AGING_DEFENSE_BOOTS, false);
			sinCheckAgingLevel(SIN_AGING_DEFENSE_GLOVES, false);
			sinCheckAgingLevel(SIN_AGING_DEFENSE_ARMLETS, false);
			sinCheckAgingLevel(SIN_AGING_CRITICAL, false);
			sinCheckAgingLevel(SIN_AGING_BLOCK, false);
			ReformCharForm();
		}

		if (!sinSecretFlag)
			return;

		if (sinGetKeyClick('U'))
		{
			for (int j = 1; j < SIN_MAX_USE_SKILL; j++)
			{
				if (sinSkill.UseSkill[j].Flag && sinSkill.UseSkill[j].Point)
				{
					sinSkill.UseSkill[j].UseSkillCount += 100;
					cSkill.ReformSkillMasteryForm(0, j);
				}
			}
			cSkill.ReFormCharSkillInfo();
			ReformCharForm();
		}
	}
}
int sinRequestTrade(DWORD CODE, char *CharName)
{
	if (cTrade.OpenFlag)
		return FALSE;

	cTrade.TradeRequestFlag = 1;
	cTrade.TradeCharCode = CODE;
	lstrcpy(cTrade.szTradeCharName, CharName);
	return TRUE;

}

DWORD dwCurrentTime = 0;

//¼¼ÄÜ´óÊ¦  Ñ§Ï°¼¼ÄÜ
int sinSkillMaster(int ChangeJob)
{
	int i = 0, j = 0;

	for (i = 0; i < SIN_MAX_HELP_NUMBER; i++)
	{
		if (sSinHelp[i].KindFlag)
			return FALSE;
	}

	int SkillTreeCheckFlag = 0;
	int ChangeJobItemCnt = 0;

	if (ChangeJob)
	{
		for (i = 0; i < 3; i++)
		{
			ItemIndex1[i] = 0;
			ItemIndex2[i] = 0;
		}
		if (sinQuest_ChangeJob.CODE == SIN_QUEST_CODE_CHANGEJOB)
		{
			SkillNpcFlag = 0;
			if (sinQuest_ChangeJob.State == SIN_QUEST_PROGRESS)
			{
				if (sinChar->iRank == 0)
				{
					for (i = 0; i < 100; i++)
					{
						if (cInvenTory.InvenItem[i].bValid)
						{
							if (cInvenTory.InvenItem[i].sBaseItemID.ToInt() == (sinQT1 | sin01))
								ItemIndex1[0] = i + 1;
							if (cInvenTory.InvenItem[i].sBaseItemID.ToInt() == (sinQT1 | sin02))
								ItemIndex1[1] = i + 1;
							if (cInvenTory.InvenItem[i].sBaseItemID.ToInt() == (sinQT1 | sin03))
								ItemIndex1[2] = i + 1;

						}
						if (cInvenTory.InvenItemTemp[i].bValid)
						{
							if (cInvenTory.InvenItemTemp[i].sBaseItemID.ToInt() == (sinQT1 | sin01))
								ItemIndex1[0] = i + 1;
							if (cInvenTory.InvenItemTemp[i].sBaseItemID.ToInt() == (sinQT1 | sin02))
								ItemIndex1[1] = i + 1;
							if (cInvenTory.InvenItemTemp[i].sBaseItemID.ToInt() == (sinQT1 | sin03))
								ItemIndex1[2] = i + 1;
						}
					}
				}
			}
		}
		if (ItemIndex1[0] && ItemIndex1[1] && ItemIndex1[2])
		{
			SkillNpcFlag = 0;
			cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath[1]);
			cSkill.OpenFlag = 1;
			cInterFace.CheckAllBox(SIN_SKILL);
		}

		else if ((FindLastQuestCode(SIN_QUEST_CODE_CHANGEJOB2_NPC_M) || FindLastQuestCode(SIN_QUEST_CODE_CHANGEJOB2_NPC_D)) && sinChar->iRank < 1)
		{
			cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath[9]);
			cInterFace.CheckAllBox(SIN_SKILL);
			sinQuest_ChangeJob2.State = 0;
			SkillNpcFlag = 0;
		}
		else if (sinQuest_ChangeJob4.CODE)
		{
			SkillNpcFlag = 0;
			sinCheckChangeJobQuest4();
		}
		else
		{
			if (!sinNpcChangeJob3()) //Ñ§Ï°¼¼ÄÜ
				SkillMasterFlag = 1;
		}
	}
	else
		SkillMasterFlag = 1;

	cSkill.OpenFlag = 1;
	cInterFace.CheckAllBox(SIN_SKILL);


	if (sinQuest_ChangeJob.State)
		sinChangeJobButtonShow = 0;
	if (sinQuest_ChangeJob2.State)
		sinChangeJobButtonShow2 = 0;
	if (sinQuest_ChangeJob3.State)
		sinChangeJobButtonShow3 = 0;
	if (sinQuest_ChangeJob4.State)
		sinChangeJobButtonShow4 = 0;

	if ((FindLastQuestCode(SIN_QUEST_CODE_CHANGEJOB2_NPC_M) || FindLastQuestCode(SIN_QUEST_CODE_CHANGEJOB2_NPC_D)) && sinChar->iRank < 1)
		sinChangeJobButtonShow2 = 0;

	switch (sinChar->iRank)
	{
	case 0:
		ChangeJobSkillPlus = 5;
		break;
	case 1:
		ChangeJobSkillPlus = 9;
		break;
	case 2:
		ChangeJobSkillPlus = 13;
		break;
	case 3:
		ChangeJobSkillPlus = 17;
		break;
	case 4:
		ChangeJobSkillPlus = 21;
		break;
	}

	SkillTreeCheckFlag = 1;

	for (int i = 1; i < ChangeJobSkillPlus; i++)
	{
		if (!sinSkill.UseSkill[i].Point)
			SkillTreeCheckFlag = 0;
	}
	CheckQuestButtonShow1 = 0;
	CheckQuestButtonShow2 = 0;
	CheckQuestButtonShow3 = 0;

	switch (ChangeJob)
	{
	case 1:
		if (sinChar->iRank == 0)
			if (SkillTreeCheckFlag)CheckQuestButtonShow1 = 1;
		break;
	case 2:
		if (sinChar->iRank == 0)
			if (SkillTreeCheckFlag)CheckQuestButtonShow1 = 1;
		if (sinChar->iRank == 1)
			if (SkillTreeCheckFlag)CheckQuestButtonShow2 = 1;
		if (sinChar->iRank == 2)
			if (SkillTreeCheckFlag)CheckQuestButtonShow3 = 1;
		break;
	case 3:
		if (sinChar->iRank == 0)
			if (SkillTreeCheckFlag)CheckQuestButtonShow1 = 1;
		if (sinChar->iRank == 1)
			if (SkillTreeCheckFlag)CheckQuestButtonShow2 = 1;
		if (sinChar->iRank == 2)
			if (SkillTreeCheckFlag)CheckQuestButtonShow3 = 1;
		break;

	}

	return TRUE;
}
int sinSkillMasterClose()
{
	SkillMasterFlag = 0;
	cSkill.OpenFlag = 0;
	dwCurrentTime = dwPlayTime + 5000;
	return TRUE;
}


static int LastPartyMode = -1;
int haSiegeBoardTempFlag = 0;

int ShowParty()
{
	int ls;

	if (InterfaceParty.PartyPosState == PARTY_START || InterfaceParty.PartyPosState == PARTY_END)
		return FALSE;

	InterfaceParty.qN_Pressf_CLEAR();

	ls = LastPartyMode;

	LastPartyMode = 1;

	if (InterfaceParty.PartyPosState == PARTY_PROCESS && LastPartyMode != ls)
	{
		InterfaceParty.Main_menuSet(1);
		return TRUE;
	}

	InterfaceParty.InitMenuSet(1);

	switch (InterfaceParty.PartyPosState)
	{
	case PARTY_NONE:
		InterfaceParty.PartyPosState = PARTY_START;
		haSiegeBoardTempFlag = 1;
		break;
	case PARTY_PROCESS:
		InterfaceParty.PartyPosState = PARTY_END;
		haSiegeBoardTempFlag = 0;
		break;
	}

	return TRUE;
}
int ShowQuest()
{
	int ls;

	InterfaceParty.qN_Pressf_CLEAR();

	if (InterfaceParty.PartyPosState == PARTY_START || InterfaceParty.PartyPosState == PARTY_END)
		return FALSE;

	ls = LastPartyMode;

	LastPartyMode = 0;

	if (InterfaceParty.PartyPosState == PARTY_PROCESS && LastPartyMode != ls)
	{
		InterfaceParty.Main_menuSet(0);
		return TRUE;
	}

	InterfaceParty.InitMenuSet(0);

	switch (InterfaceParty.PartyPosState)
	{
	case PARTY_NONE:
		InterfaceParty.PartyPosState = PARTY_START;
		haSiegeBoardTempFlag = 1;
		break;
	case PARTY_PROCESS:
		InterfaceParty.PartyPosState = PARTY_END;
		haSiegeBoardTempFlag = 0;
		break;
	}

	return TRUE;
}
short sinGetLife()
{
	return (sinChar->sHP.sMin) ^ CodeXorLife;
}
short sinGetMana()
{
	return sinChar->sMP.sMin;
}
short sinGetStamina()
{
	return sinChar->sSP.sMin;
}

//ÉèÖÃÉúÃü
void sinSetLife(short Life)
{
	sinChar->sHP.sMin = Life;
	if (sinChar->sHP.sMin < 0)
		sinChar->sHP.sMin = 0;
	if (sinChar->sHP.sMin >= sinChar->sHP.sMax)
		sinChar->sHP.sMin = sinChar->sHP.sMax;
	sinChar->sHP.sMin ^= CodeXorLife;
	ReformCharForm();
}
void sinSetMana(short Mana)
{
	sinChar->sMP.sMin = Mana;
	if (sinChar->sMP.sMin < 0)
		sinChar->sMP.sMin = 0;
	if (sinChar->sMP.sMin >= sinChar->sMP.sMax)
		sinChar->sMP.sMin = sinChar->sMP.sMax;
	ReformCharForm();
}
void sinSetStamina(short Stamina)
{
	sinChar->sSP.sMin = Stamina;
	if (sinChar->sSP.sMin < 0)
		sinChar->sSP.sMin = 0;
	if (sinChar->sSP.sMin >= sinChar->sSP.sMax)
		sinChar->sSP.sMin = sinChar->sSP.sMax;
	ReformCharForm();
}

// ¼ì²é¶ÍÔìµÄµÈ¼¶
int sinCheckAgingLevel(int Kind, bool bBillingUse)
{
	ItemData *pItem = 0;
	switch (Kind)
	{
	case  SIN_AGING_ATTACK:
		if (!cInvenTory.InvenItem[sInven[0].ItemIndex - 1].bValid || !cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.bMaturing)
			return FALSE;
		if ((cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt() &sinITEM_MASK2) == sinWA1 ||
			(cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt() &sinITEM_MASK2) == sinWH1 ||
			(cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt() &sinITEM_MASK2) == sinWM1 ||
			(cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt() &sinITEM_MASK2) == sinWN1)
			pItem = &cInvenTory.InvenItem[sInven[0].ItemIndex - 1];
		break;
	case  SIN_AGING_CRITICAL:
		if (!cInvenTory.InvenItem[sInven[0].ItemIndex - 1].bValid || !cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.bMaturing)
			return FALSE;
		if ((cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt() &sinITEM_MASK2) == sinWC1 ||
			(cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt() &sinITEM_MASK2) == sinWS2 ||
			(cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt() &sinITEM_MASK2) == sinWS1 ||
			(cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt() &sinITEM_MASK2) == sinWP1 ||
			(cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt() &sinITEM_MASK2) == sinWT1 ||
			(cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt() &sinITEM_MASK2) == sinWD1)
			pItem = &cInvenTory.InvenItem[sInven[0].ItemIndex - 1];
		break;
	case  SIN_AGING_BLOCK:
		if (!cInvenTory.InvenItem[sInven[1].ItemIndex - 1].bValid ||
			!cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sItem.bMaturing)
			return FALSE;

		if ((cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sBaseItemID.ToInt() &sinITEM_MASK2) == sinDS1)
			pItem = &cInvenTory.InvenItem[sInven[1].ItemIndex - 1];
		break;
	case SIN_AGING_DEFENSE_ARMOR:
		if (cInvenTory.InvenItem[sInven[2].ItemIndex - 1].bValid ||
			cInvenTory.InvenItem[sInven[2].ItemIndex - 1].sItem.bMaturing)
		{
			if ((cInvenTory.InvenItem[sInven[2].ItemIndex - 1].sBaseItemID.ToInt() &sinITEM_MASK2) == sinDA1 ||
				(cInvenTory.InvenItem[sInven[2].ItemIndex - 1].sBaseItemID.ToInt() &sinITEM_MASK2) == sinDA2)
				pItem = &cInvenTory.InvenItem[sInven[2].ItemIndex - 1];
		}
		break;
	case SIN_AGING_DEFENSE_ORB:
		if (cInvenTory.InvenItem[sInven[1].ItemIndex - 1].bValid || cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sItem.bMaturing)
		{
			if ((cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sBaseItemID.ToInt() &sinITEM_MASK2) == sinOM1)
				pItem = &cInvenTory.InvenItem[sInven[1].ItemIndex - 1];
		}
		break;
	case SIN_AGING_DEFENSE_BOOTS:
		if (!cInvenTory.InvenItem[sInven[9].ItemIndex - 1].bValid || !cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItem.bMaturing)
			return FALSE;

		if ((cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sBaseItemID.ToInt() &sinITEM_MASK2) == sinDB1)
			pItem = &cInvenTory.InvenItem[sInven[9].ItemIndex - 1];
		break;
	case SIN_AGING_DEFENSE_GLOVES:
		if (!cInvenTory.InvenItem[sInven[8].ItemIndex - 1].bValid || !cInvenTory.InvenItem[sInven[8].ItemIndex - 1].sItem.bMaturing)
			return FALSE;

		if ((cInvenTory.InvenItem[sInven[8].ItemIndex - 1].sBaseItemID.ToInt() &sinITEM_MASK2) == sinDG1)
			pItem = &cInvenTory.InvenItem[sInven[8].ItemIndex - 1];
		break;
	case SIN_AGING_DEFENSE_ARMLETS:
		if (!cInvenTory.InvenItem[sInven[7].ItemIndex - 1].bValid || !cInvenTory.InvenItem[sInven[7].ItemIndex - 1].sItem.bMaturing)
			return FALSE;
		if ((cInvenTory.InvenItem[sInven[7].ItemIndex - 1].sBaseItemID.ToInt() &sinITEM_MASK2) == sinOA2)
			pItem = &cInvenTory.InvenItem[sInven[7].ItemIndex - 1];
		break;
	}

	if (!pItem || pItem->sItem.eCraftType != ITEMCRAFTTYPE_Aging)
		return FALSE;

	if (SETTINGHANDLE->Get().bDebugMode)
	{
		if (bBillingUse == false)
			pItem->sItem.sMatureBar.sMin += 200;
		else if (bBillingUse == true)
			pItem->sItem.sMatureBar.sMin = pItem->sItem.sMatureBar.sMax;
	}
	else
	{
		if (bBillingUse == false)
			pItem->sItem.sMatureBar.sMin++;
		else if (bBillingUse == true)
			pItem->sItem.sMatureBar.sMin = pItem->sItem.sMatureBar.sMax;
	}
	if (pItem->sItem.sMatureBar.sMax && pItem->sItem.sMatureBar.sMin >= pItem->sItem.sMatureBar.sMax)
	{
		pItem->sItem.sMatureBar.sMin = pItem->sItem.sMatureBar.sMax;
		SendAgingUpgradeItemToServer(&pItem->sItem);
	}

	return TRUE;
}
int sinRecvAgingIncreStateItem(Item *pItem)
{
	for (int i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (cInvenTory.InvenItem[i].sItem.BackUpChkSum == pItem->BackUpChkSum && cInvenTory.InvenItem[i].sItem.BackUpKey == pItem->BackUpKey && cInvenTory.InvenItem[i].sItem.sItemID.ToInt() == pItem->sItemID.ToInt())
		{
			memcpy(&cInvenTory.InvenItem[i].sItem, pItem, sizeof(Item));
			cInvenTory.ReFormInvenItem();
			cInvenTory.CheckRequireItemToSet(&cInvenTory.InvenItem[i]);
			cInvenTory.SetItemToChar();
			break;
		}
	}

	return TRUE;
}
int sinCheckAgingItemHack(ItemData *pItem)
{
	if (pItem->sItem.eCraftType == ITEMCRAFTTYPE_Mixing)
		return FALSE;

	return TRUE;
}
int sinMinusMoney(int Money, int Kind)
{
	if (Kind)
	{
		sinChar->iGold -= Money + ((Money*cSinSiege.GetTaxRate()) / 100);
		SetTotalSubMoney(Money + (Money*cSinSiege.GetTaxRate()) / 100);
	}
	else
	{
		sinChar->iGold -= Money;
		SetTotalSubMoney(Money);
	}

	ReformCharForm();
	SendSaveMoney();
	return TRUE;
}

int sinPlusMoney(int Money)
{
	sinChar->iGold += Money;

	ReformCharForm();
	SetTotalAddMoney(Money);
	SendSaveMoney();

	return TRUE;
}
int sinMinusMoney2(int Money)
{
	sinChar->iGold -= Money;
	ReformCharForm();
	SendSaveMoney();
	return TRUE;
}

int sinPlusMoney2(int Money)
{
	sinChar->iGold += Money;
	ReformCharForm();
	SendSaveMoney();
	return TRUE;
}

int sinGetElement(CharacterData *pCharInfo)
{
	return TRUE;
}
char  *PresentWeaponName[5][9] =
{
	{"sp103",0		,0		,0		,0,0,0,0,0},
	{"fo104","fo105","fo106",0		,0,0,0,0,0},
	{"fo101","fo102","fo103","os106",0,0,0,0,0},
	{"fo107","se103","se102","os107",0,0,0,0,0},
	{"se101","os108","fo108","gp111",0,0,0,0,0},
};


char  *PresentArmorName[5][9] =
{
	{"pm104",0		,0		,0		,0,0,0,0,0},
	{"gp104","gp105","gp106","gp107",0,0,0,0,0},
	{"gp101","gp102","gp103","os106",0,0,0,0,0},
	{"gp108","gp109","gp110","os107",0,0,0,0,0},
	{"se101","os108","fo108","gp111",0,0,0,0,0},
};

int PresentPercentIndex[5] = { 5900,2250,1450,250,150 };


char  *PresentWeaponName2[8][9] =
{
	{"bi123",0,0,0,0,0,0,0,0}, // 2500
	{"pm104",0,0,0,0,0,0,0,0}, // 2500
	{"os106",0,0,0,0,0,0,0,0}, // 1590
	{"gp109",0,0,0,0,0,0,0,0}, // 1500
	{"or228",0,0,0,0,0,0,0,0}, // 700
	{"oa133",0,0,0,0,0,0,0,0}, // 700
	{"gp121",0,0,0,0,0,0,0,0}, // 500
	{"os109",0,0,0,0,0,0,0,0}, // 10
};

char  *PresentArmorName2[8][9] =
{
	{"bi123",0,0,0,0,0,0,0,0}, // 2500
	{"pm104",0,0,0,0,0,0,0,0}, // 2500
	{"os106",0,0,0,0,0,0,0,0}, // 1590
	{"gp109",0,0,0,0,0,0,0,0}, // 1500
	{"or228",0,0,0,0,0,0,0,0}, // 700
	{"oa133",0,0,0,0,0,0,0,0}, // 700
	{"gp121",0,0,0,0,0,0,0,0}, // 500
	{"os109",0,0,0,0,0,0,0,0}, // 10
};

int PresentPercentIndex2[8] = { 2500,2500,1590,1500,700,700,500,10 };

char  *PresentChocoWeaponName3[17][9] =
{
	{"sp115",0,0,0,0,0,0,0,0},		//1
	{"pm104",0,0,0,0,0,0,0,0},		//2
	{"GP120",0,0,0,0,0,0,0,0},		//3
	{"GP109",0,0,0,0,0,0,0,0},		//4
	{"bi106",0,0,0,0,0,0,0,0},		//5
	{"Bi107",0,0,0,0,0,0,0,0},		//6
	{"OS107",0,0,0,0,0,0,0,0},		//7
	{"OS108",0,0,0,0,0,0,0,0},		//8
	{"Da131",0,0,0,0,0,0,0,0},		//9
	{"Da231",0,0,0,0,0,0,0,0},		//10
	{"Da133",0,0,0,0,0,0,0,0},		//11
	{"Da233",0,0,0,0,0,0,0,0},		//12
	{"OR233",0,0,0,0,0,0,0,0},		//13
	{"FO107",0,0,0,0,0,0,0,0},		//14
	{"FO106",0,0,0,0,0,0,0,0},		//15
	{"bi108",0,0,0,0,0,0,0,0},		//16
	{"OS109",0,0,0,0,0,0,0,0},		//17
};

char  *PresentChocoArmorName3[17][9] =
{
	{"sp115",0,0,0,0,0,0,0,0},		//1
	{"pm104",0,0,0,0,0,0,0,0},		//2
	{"GP120",0,0,0,0,0,0,0,0},		//3
	{"GP109",0,0,0,0,0,0,0,0},		//4
	{"bi106",0,0,0,0,0,0,0,0},		//5
	{"Bi107",0,0,0,0,0,0,0,0},		//6
	{"OS107",0,0,0,0,0,0,0,0},		//7
	{"OS108",0,0,0,0,0,0,0,0},		//8
	{"Da131",0,0,0,0,0,0,0,0},		//9
	{"Da231",0,0,0,0,0,0,0,0},		//10
	{"Da133",0,0,0,0,0,0,0,0},		//11
	{"Da233",0,0,0,0,0,0,0,0},		//12
	{"OR233",0,0,0,0,0,0,0,0},		//13
	{"FO107",0,0,0,0,0,0,0,0},		//14
	{"FO106",0,0,0,0,0,0,0,0},		//15
	{"bi108",0,0,0,0,0,0,0,0},		//16
	{"OS109",0,0,0,0,0,0,0,0},		//17
};

int PresentChocoPercentIndex3[17] = { 1000,1000,100,200,1200,1200,489,10,600,600,600,600,400,900,900,200,1 };

char  *PresentCandyWeaponName3[17][9] =
{
	{"sp115",0,0,0,0,0,0,0,0},		//1
	{"pm104",0,0,0,0,0,0,0,0},		//2
	{"GP121",0,0,0,0,0,0,0,0},		//3
	{"GP109",0,0,0,0,0,0,0,0},		//4
	{"bi106",0,0,0,0,0,0,0,0},		//5
	{"Bi107",0,0,0,0,0,0,0,0},		//6
	{"OS107",0,0,0,0,0,0,0,0},		//7
	{"OS108",0,0,0,0,0,0,0,0},		//8
	{"Da139",0,0,0,0,0,0,0,0},		//9
	{"Da239",0,0,0,0,0,0,0,0},		//10
	{"Da141",0,0,0,0,0,0,0,0},		//11
	{"DA241",0,0,0,0,0,0,0,0},		//12
	{"OA137",0,0,0,0,0,0,0,0},		//13
	{"FO107",0,0,0,0,0,0,0,0},		//14
	{"FO106",0,0,0,0,0,0,0,0},		//15
	{"bi108",0,0,0,0,0,0,0,0},		//16
	{"OS109",0,0,0,0,0,0,0,0},		//17
};

char  *PresentCandyArmorName3[17][9] =
{
	{"sp115",0,0,0,0,0,0,0,0},		//1
	{"pm104",0,0,0,0,0,0,0,0},		//2
	{"GP121",0,0,0,0,0,0,0,0},		//3
	{"GP109",0,0,0,0,0,0,0,0},		//4
	{"bi106",0,0,0,0,0,0,0,0},		//5
	{"Bi107",0,0,0,0,0,0,0,0},		//6
	{"OS107",0,0,0,0,0,0,0,0},		//7
	{"OS108",0,0,0,0,0,0,0,0},		//8
	{"Da139",0,0,0,0,0,0,0,0},		//9
	{"Da239",0,0,0,0,0,0,0,0},		//10
	{"Da141",0,0,0,0,0,0,0,0},		//11
	{"DA241",0,0,0,0,0,0,0,0},		//12
	{"OA137",0,0,0,0,0,0,0,0},		//13
	{"FO107",0,0,0,0,0,0,0,0},		//14
	{"FO106",0,0,0,0,0,0,0,0},		//15
	{"bi108",0,0,0,0,0,0,0,0},		//16
	{"OS109",0,0,0,0,0,0,0,0},		//17
};

int PresentCandyPercentIndex3[17] = { 1000,1000,100,200,1200,1200,489,10,600,600,600,600,400,900,900,200,1 };


char  *PresentMagicalGreenEmeraldWeaponName3[18][9] =
{
	{"pm104",0,0,0,0,0,0,0,0},	//1
	{"bi119",0,0,0,0,0,0,0,0},		//2
	{"gp118",0,0,0,0,0,0,0,0},		//3
	{"gp120",0,0,0,0,0,0,0,0},		//4
	{"gp119",0,0,0,0,0,0,0,0},		//5
	{"se101",0,0,0,0,0,0,0,0},		//6
	{"os107",0,0,0,0,0,0,0,0},		//7
	{"os108",0,0,0,0,0,0,0,0},		//8
	{"os109",0,0,0,0,0,0,0,0},		//9
	{"os110",0,0,0,0,0,0,0,0},		//10
	{"os111",0,0,0,0,0,0,0,0},		//11
	{"bi112",0,0,0,0,0,0,0,0},		//12
	{"bi108",0,0,0,0,0,0,0,0},		//13
	{"bi107",0,0,0,0,0,0,0,0},		//14
	{"bi106",0,0,0,0,0,0,0,0},		//15
	{"fo107",0,0,0,0,0,0,0,0},		//16
	{"fo108",0,0,0,0,0,0,0,0},		//17
	{"fo109",0,0,0,0,0,0,0,0},		//18
};

char  *PresentMagicalGreenEmeraldArmorName3[18][9] =
{
	{"pm104",0,0,0,0,0,0,0,0},	//1
	{"bi119",0,0,0,0,0,0,0,0},		//2
	{"gp118",0,0,0,0,0,0,0,0},		//3
	{"gp120",0,0,0,0,0,0,0,0},		//4
	{"gp119",0,0,0,0,0,0,0,0},		//5
	{"se101",0,0,0,0,0,0,0,0},		//6
	{"os107",0,0,0,0,0,0,0,0},		//7
	{"os108",0,0,0,0,0,0,0,0},		//8
	{"os109",0,0,0,0,0,0,0,0},		//9
	{"os110",0,0,0,0,0,0,0,0},		//10
	{"os111",0,0,0,0,0,0,0,0},		//11
	{"bi112",0,0,0,0,0,0,0,0},		//12
	{"bi108",0,0,0,0,0,0,0,0},		//13
	{"bi107",0,0,0,0,0,0,0,0},		//14
	{"bi106",0,0,0,0,0,0,0,0},		//15
	{"fo107",0,0,0,0,0,0,0,0},		//16
	{"fo108",0,0,0,0,0,0,0,0},		//17
	{"fo109",0,0,0,0,0,0,0,0},		//18
};

int PresentMagicalGreenEmeraldPercentIndex3[18] = { 1400,300,400,200,100,1,300,200,1,1,1,100,1500,1500,1500,1200,800, 496 };

char  *PresentMagicalGreenJadeWeaponName3[15][9] =
{
	{"pm103",0,0,0,0,0,0,0,0},	//1
	{"Gp109",0,0,0,0,0,0,0,0},	//2
	{"Gp121",0,0,0,0,0,0,0,0},	//3
	{"Fo104",0,0,0,0,0,0,0,0},		//4
	{"Fo105",0,0,0,0,0,0,0,0},		//5
	{"Fo106",0,0,0,0,0,0,0,0},		//6
	{"Os105",0,0,0,0,0,0,0,0},		//7
	{"Os106",0,0,0,0,0,0,0,0},		//8
	{"Da135",0,0,0,0,0,0,0,0},		//9
	{"Da137",0,0,0,0,0,0,0,0},		//10
	{"da235",0,0,0,0,0,0,0,0},		//11
	{"Da237",0,0,0,0,0,0,0,0},		//12
	{"Bi112",0,0,0,0,0,0,0,0},		//13
	{"Bi119",0,0,0,0,0,0,0,0},		//14
	{"bi121",0,0,0,0,0,0,0,0},		//15
};

char  *PresentMagicalGreedJadeArmorName3[15][9] =
{
	{"pm103",0,0,0,0,0,0,0,0},	//1
	{"Gp109",0,0,0,0,0,0,0,0},	//2
	{"Gp121",0,0,0,0,0,0,0,0},	//3
	{"Fo104",0,0,0,0,0,0,0,0},		//4
	{"Fo105",0,0,0,0,0,0,0,0},		//5
	{"Fo106",0,0,0,0,0,0,0,0},		//6
	{"Os105",0,0,0,0,0,0,0,0},		//7
	{"Os106",0,0,0,0,0,0,0,0},		//8
	{"Da135",0,0,0,0,0,0,0,0},		//9
	{"Da137",0,0,0,0,0,0,0,0},		//10
	{"da235",0,0,0,0,0,0,0,0},		//11
	{"Da237",0,0,0,0,0,0,0,0},		//12
	{"Bi112",0,0,0,0,0,0,0,0},		//13
	{"Bi119",0,0,0,0,0,0,0,0},		//14
	{"bi121",0,0,0,0,0,0,0,0},		//15
};

int PresentMagicalGreedJadePercentIndex3[15] = { 1500,1500,200,1500,1500,1000,300,200,500,500,500,500,100,100,100 };

char  *PresentTearOfKaraWeaponName3[18][9] =
{
	{"pm104",0,0,0,0,0,0,0,0},		//1
	{"bi119",0,0,0,0,0,0,0,0},		//2
	{"gp109",0,0,0,0,0,0,0,0},		//3
	{"gp121",0,0,0,0,0,0,0,0},		//4
	{"gp119",0,0,0,0,0,0,0,0},		//5
	{"se101",0,0,0,0,0,0,0,0},		//6
	{"os107",0,0,0,0,0,0,0,0},		//7
	{"os108",0,0,0,0,0,0,0,0},		//8
	{"os109",0,0,0,0,0,0,0,0},		//9
	{"os110",0,0,0,0,0,0,0,0},		//10
	{"os111",0,0,0,0,0,0,0,0},		//11
	{"bi112",0,0,0,0,0,0,0,0},		//12
	{"bi108",0,0,0,0,0,0,0,0},		//13
	{"bi107",0,0,0,0,0,0,0,0},		//14
	{"bi106",0,0,0,0,0,0,0,0},		//15
	{"fo107",0,0,0,0,0,0,0,0},		//16
	{"fo108",0,0,0,0,0,0,0,0},		//17
	{"fo109",0,0,0,0,0,0,0,0},		//18
};

char  *PresentTearOfKaraArmorName3[18][9] =
{
	{"pm104",0,0,0,0,0,0,0,0 },		//1
	{"bi119",0,0,0,0,0,0,0,0 },		//2
	{"gp109",0,0,0,0,0,0,0,0 },		//3
	{"gp121",0,0,0,0,0,0,0,0 },		//4
	{"gp119",0,0,0,0,0,0,0,0},		//5
	{"se101",0,0,0,0,0,0,0,0},		//6
	{"os107",0,0,0,0,0,0,0,0},		//7
	{"os108",0,0,0,0,0,0,0,0},		//8
	{"os109",0,0,0,0,0,0,0,0},		//9
	{"os110",0,0,0,0,0,0,0,0},		//10
	{"os111",0,0,0,0,0,0,0,0},		//11
	{"bi112",0,0,0,0,0,0,0,0},		//12
	{"bi108",0,0,0,0,0,0,0,0},		//13
	{"bi107",0,0,0,0,0,0,0,0},		//14
	{"bi106",0,0,0,0,0,0,0,0},		//15
	{"fo107",0,0,0,0,0,0,0,0},		//16
	{"fo108",0,0,0,0,0,0,0,0},		//17
	{"fo109",0,0,0,0,0,0,0,0},		//18
};

int PresentTearOfKaraPercentIndex3[18] = { 1400,300,400,200,100,1,300,200,1,1,1,100,1500,1500,1500,1200,800,496 };

char  *PresentFindinvestigatorNineWeaponName3[1][9] = { "gf107",0,0,0,0,0,0,0,0 };
char  *PresentFindinvestigatorNineArmorName3[1][9] = { "gf107",0,0,0,0,0,0,0,0 };
int PresentFindinvestigatorNinePercentIndex3[1] = { 10000 };

char  *PresentFindinvestigatorNineTaleWeaponName3[1][9] = { "gf108",0,0,0,0,0,0,0,0 };
char  *PresentFindinvestigatorNineTaleArmorName3[1][9] = { "gf108",0,0,0,0,0,0,0,0 };
int PresentFindinvestigatorNineTalePercentIndex3[1] = { 10000 };

char  *PresentFindinvestigatorWeaponName3[12][9] =
{
	{"bi109",0,0,0,0,0,0,0,0 },		//1
	{"pm104",0,0,0,0,0,0,0,0 },		//2
	{"fo109",0,0,0,0,0,0,0,0 },		//3
	{"fo110",0,0,0,0,0,0,0,0 },		//4
	{"gp110",0,0,0,0,0,0,0,0},		//5
	{"gp119",0,0,0,0,0,0,0,0},		//6
	{"gp120",0,0,0,0,0,0,0,0},		//7
	{"bi178",0,0,0,0,0,0,0,0},		//8
	{"bi183",0,0,0,0,0,0,0,0},		//9
	{"bi177",0,0,0,0,0,0,0,0},		//10
	{"oa135",0,0,0,0,0,0,0,0},		//11
	{"or230",0,0,0,0,0,0,0,0},		//12
};

char  *PresentFindinvestigatorArmorName3[12][9] =
{
	{"bi109",0,0,0,0,0,0,0,0 },		//1
	{"pm104",0,0,0,0,0,0,0,0 },		//2
	{"fo109",0,0,0,0,0,0,0,0 },		//3
	{"fo110",0,0,0,0,0,0,0,0 },		//4
	{"gp110",0,0,0,0,0,0,0,0},		//5
	{"gp119",0,0,0,0,0,0,0,0},		//6
	{"gp120",0,0,0,0,0,0,0,0},		//7
	{"bi178",0,0,0,0,0,0,0,0},		//8
	{"bi183",0,0,0,0,0,0,0,0},		//9
	{"bi177",0,0,0,0,0,0,0,0},		//10
	{"oa135",0,0,0,0,0,0,0,0},		//11
	{"or230",0,0,0,0,0,0,0,0},		//12
};

int PresentFindinvestigatorPercentIndex3[12] = { 1500,1500,1300,1000,1500,1000,1500,300,200,100,50,50 };

char  *PresentWeaponName3[9][9] =
{
	{"pm104",0,0,0,0,0,0,0,0 },		//1
	{"sp115",0,0,0,0,0,0,0,0 },		//2
	{"fo107",0,0,0,0,0,0,0,0 },		//3
	{"os107",0,0,0,0,0,0,0,0},		//4
	{"bi119",0,0,0,0,0,0,0,0},		//5
	{"bi107",0,0,0,0,0,0,0,0},		//6
	{"bi106",0,0,0,0,0,0,0,0},		//7
	{"gp120",0,0,0,0,0,0,0,0},		//8
	{"os109",0,0,0,0,0,0,0,0 },		//9
};

char  *PresentArmorName3[9][9] =
{
	{"pm104",0,0,0,0,0,0,0,0 },		//1
	{"sp115",0,0,0,0,0,0,0,0 },		//2
	{"fo107",0,0,0,0,0,0,0,0 },		//3
	{"os107",0,0,0,0,0,0,0,0},		//4
	{"bi119",0,0,0,0,0,0,0,0},		//5
	{"bi107",0,0,0,0,0,0,0,0},		//6
	{"bi106",0,0,0,0,0,0,0,0},		//7
	{"gp120",0,0,0,0,0,0,0,0},		//8
	{"os109",0,0,0,0,0,0,0,0 },		//9
};

int PresentPercentIndex3[9] = { 2000,2000,1300,1200,1000,1000,1000,499,1 };

char  *PresentWeaponName5[11][9] =
{
	{"pm104",0,0,0,0,0,0,0,0},													//1
	{"bi108",0,0,0,0,0,0,0,0},													//2
	{"bi106","bi107",0,0,0,0,0,0,0},											//3
	{"fo107",0,0,0,0,0,0,0,0},													//4
	{"or228","oa133",0,0,0,0,0,0,0},											//5
	{"os107","os108","fo109",0,0,0,0,0,0},										//6
	{"bi119",0,0,0,0,0,0,0,0},													//7
	{"gp119","gp120","gp121",0,0,0,0,0,0},										//8
	{"bi112",0,0,0,0,0,0,0,0},													//9
	{"bi213","bi214","bi215","bi216","bi217","bi218","bi219","bi220",0},		//10
	{"os109","se101",0,0,0,0,0,0,0},											//11
};

char  *PresentArmorName5[11][9] =
{
	{"pm104",0,0,0,0,0,0,0,0},													//1
	{"bi108",0,0,0,0,0,0,0,0},													//2
	{"bi106","bi107",0,0,0,0,0,0,0},											//3
	{"fo107",0,0,0,0,0,0,0,0},													//4
	{"or228","oa133",0,0,0,0,0,0,0},											//5
	{"os107","os108","fo109",0,0,0,0,0,0},										//6
	{"bi119",0,0,0,0,0,0,0,0},													//7
	{"gp119","gp120","gp121",0,0,0,0,0,0},										//8
	{"bi112",0,0,0,0,0,0,0,0},													//9
	{"bi213","bi214","bi215","bi216","bi217","bi218","bi219","bi220",0},		//10
	{"os109","se101",0,0,0,0,0,0,0},											//11
};

int PresentPercentIndex5[11] = { 1450,1300,2600,1198,1000,1000,300,100,50,1000,20 };

DWORD sinForceOrbCode[] = { (sinFO1 | sin01),(sinFO1 | sin02),(sinFO1 | sin03),(sinFO1 | sin04),(sinFO1 | sin05),(sinFO1 | sin06),(sinFO1 | sin07),(sinFO1 | sin08),(sinFO1 | sin09),(sinFO1 | sin10),(sinFO1 | sin11),(sinFO1 | sin12),(sinFO1 | sin13),(sinFO1 | sin14),(sinFO1 | sin15),(sinFO1 | sin16) };

int SendWingQuestItem()
{
	SendWingItemToServer(&sWingItem_Send);
	return TRUE;
}
int RecvWingItem(sCRAFTITEM_SERVER *pWingItem)
{
	ItemData *pItem = 0;
	int   Index = 0;
	int   i = 0;
	ItemData sinTempItem;

	for (i = 0; i < INVENTORY_MAXITEM * 2; i++)
	{
		if (i < 100)
		{
			if (!cInvenTory.InvenItem[i].bValid)
				continue;
			pItem = &cInvenTory.InvenItem[i];
		}
		else
		{
			if (!cInvenTory.InvenItemTemp[i - 100].bValid)
				continue;
			pItem = &cInvenTory.InvenItemTemp[i - 100];
		}
		if (pWingItem->Result == FALSE)
			cInvenTory.DeleteInvenItemToServer(pWingItem->DesCraftItem.sItem.sItemID.ToInt(), pWingItem->DesCraftItem.sItem.iChk1, pWingItem->DesCraftItem.sItem.iChk2);
		if (pItem->iItemSlot == 2)
		{
			if (pItem->iItemSlotFlag == ITEMSLOTFLAG_LeftRightHand && (pItem->sBaseItemID.ToInt() & sinITEM_MASK2) != sinWD1)
				continue;
		}
		else if (pItem->iItemSlot == 16)
		{
			if (pItem->iItemSlotFlag == ITEMSLOTFLAG_Wing)
				continue;
		}
		for (int j = 0; j < 8; j++)
		{
			if (pItem->sItem.sItemID.ToInt() == pWingItem->SheltomCode[j] && pItem->sItem.iChk1 == pWingItem->Head[j] && pItem->sItem.iChk2 == pWingItem->CheckSum[j])
			{
				pItem->bValid = 0;
				cInvenTory.ReFormInvenItem();
				cInvenTory.CheckWeight();
			}
		}
	}

	if (pWingItem->Result == TRUE)
	{
		sinMinusMoney(pWingItem->Money);
		SendSaveMoney();

		if (pWingItem->DesCraftItem.sItem.sItemID.ToInt())
		{
			if (LoadItemImage(&pWingItem->DesCraftItem.sItem, &sinTempItem))
			{
				if (sinTempItem.sItem.eCraftType == ITEMCRAFTTYPE_QuestWeapon)
					sinQuest_ChangeJob3.StartLevel = sinChar->iLevel;

				sinSetSpecialItemCode(&sinTempItem.sItem);
				cInvenTory.AutoSetInvenItem(&sinTempItem, 1 + pWingItem->DocIndex);
				cInvenTory.ReFormInvenItem();
				ResetPotion();
				cInvenTory.ReFormPotionNum();
			}
		}
	}

	ReformCharForm();
	cInvenTory.SetItemToChar();
	cInvenTory.CheckWeight();

	sinbaram_Stop = 0;
	cInvenTory.CheckPuzzle();

	return TRUE;
}
int AgingRing()
{
	if (sInven[4].ItemIndex)
	{
		if (cInvenTory.InvenItem[sInven[4].ItemIndex - 1].sItem.sMatureBar.sMax && cInvenTory.InvenItem[sInven[4].ItemIndex - 1].sItem.sItemID.ToInt() == (sinOR2 | sin01))
		{
			if (SETTINGHANDLE->Get().bDebugMode)
				cInvenTory.InvenItem[sInven[4].ItemIndex - 1].sItem.sMatureBar.sMin += 100;
			else
				cInvenTory.InvenItem[sInven[4].ItemIndex - 1].sItem.sMatureBar.sMin++;
			if (cInvenTory.InvenItem[sInven[4].ItemIndex - 1].sItem.sMatureBar.sMin >= cInvenTory.InvenItem[sInven[4].ItemIndex - 1].sItem.sMatureBar.sMax)
				SendAgingUpgradeItemToServer(&cInvenTory.InvenItem[sInven[4].ItemIndex - 1].sItem);
		}
	}
	if (sInven[5].ItemIndex)
	{
		if (cInvenTory.InvenItem[sInven[5].ItemIndex - 1].sItem.sMatureBar.sMax && cInvenTory.InvenItem[sInven[5].ItemIndex - 1].sItem.sItemID.ToInt() == (sinOR2 | sin01))
		{
			if (SETTINGHANDLE->Get().bDebugMode)
				cInvenTory.InvenItem[sInven[5].ItemIndex - 1].sItem.sMatureBar.sMin += 100;
			else
				cInvenTory.InvenItem[sInven[5].ItemIndex - 1].sItem.sMatureBar.sMin++;
			if (cInvenTory.InvenItem[sInven[5].ItemIndex - 1].sItem.sMatureBar.sMin >= cInvenTory.InvenItem[sInven[5].ItemIndex - 1].sItem.sMatureBar.sMax)
				SendAgingUpgradeItemToServer(&cInvenTory.InvenItem[sInven[5].ItemIndex - 1].sItem);
		}
	}

	return TRUE;
}
int NumLineComa(int Num, char *pBuff)
{
	int i = 0;
	char strBuff[128];
	wsprintf(strBuff, "%d", Num);
	int cnt = 0;
	int cnt2 = 0;
	int cnt3 = 0;

	int len = lstrlen(strBuff);
	while (1)
	{
		if (strBuff[cnt])
		{
			pBuff[cnt + cnt2] = strBuff[cnt];
			cnt3 = (len - 1) - cnt;
			if ((cnt3 % 3) == 0 && cnt3 != 0)
			{
				cnt2++;
				pBuff[cnt + cnt2] = ',';
			}
			cnt++;
		}
		else break;
	}
	return TRUE;
}
int sinSaveGame(DWORD CODE, int Count)
{
	DWORD MASK_CODE = (CODE & sinITEM_MASK2);

	if (MASK_CODE == sinPM1 && Count >= 4)
		SaveGameData();

	if ((MASK_CODE == sinPL1 || MASK_CODE == sinPS1) && Count >= 10)
		SaveGameData();

	return TRUE;
}
int OverDay_Item_Flag = 0;
int OverDay_Item_Delete(ItemData *pItem)
{
	OverDay_Item_Flag = 1;
	lstrcpy(sLost_Item.szDoc, pItem->sItem.szItemName);
	sLost_Item.LostItem[0].sBaseItemID = pItem->sItem.sItemID.ToInt();
	sLost_Item.LostItem[1].sBaseItemID = 0;
	sLost_Item.Flag = 1;
	cInvenTory.CheckInvenEmpty(&sLost_Item.LostItem[0]);
	cInvenTory.CheckInvenEmpty(&sLost_Item.LostItem[1]);
	return TRUE;
}
int sinCloseInterFace()
{
	if (cMixtureReset.OpenFlag)
		cMixtureReset.OpenFlag = SIN_CLOSE;
	if (cElement.OpenFlag)
		cElement.OpenFlag = SIN_CLOSE;
	if (cSocket.OpenFlag)
		cSocket.OpenFlag = SIN_CLOSE;
	if (cTrade.OpenFlag)
		cTrade.OpenFlag = SIN_CLOSE;
	if (cShop.OpenFlag)
		cShop.OpenFlag = SIN_CLOSE;
	if (cSkill.OpenFlag)
		cSkill.OpenFlag = SIN_CLOSE;
	if (cAging.OpenFlag)
		cAging.OpenFlag = SIN_CLOSE;
	if (cCraftItem.OpenFlag)
		cCraftItem.OpenFlag = SIN_CLOSE;
	if (cCharStatus.OpenFlag)
		cCharStatus.OpenFlag = SIN_CLOSE;
	if (SmeltingItem.OpenFlag)
		SmeltingItem.OpenFlag = SIN_CLOSE;
	if (ManufactureItem.m_OpenFlag)
		ManufactureItem.m_OpenFlag = SIN_CLOSE;
	if (cMyShop.OpenFlag)
	{
		cMyShop.OpenFlag = SIN_CLOSE;
		cMyShop.OpenFlag = 0;
		memset(cMyShop.MyShopItem, 0, sizeof(ItemData) * 30);
		memset(MyShopItemIndex, 0, sizeof(int) * 100);
		MyShopSendButton = 0;
	}
	if (cInvenTory.OpenFlag)
		cInvenTory.OpenFlag = SIN_CLOSE;
	if (cCharShop.OpenFlag)
		cCharShop.OpenFlag = SIN_CLOSE;
	if (cCharShop.OpenFlag)
	{
		cCharShop.OpenFlag = 0;
		memset(cCharShop.CharShopItem, 0, sizeof(ItemData) * 30);
	}
	cInvenTory.ChangeSpecialItem(2);
	return TRUE;
}

int sinCheck_ShowHelpMap()
{
	if (SkillNpcFlag || sinMessageBoxShowFlag || MouseItem.bValid || cWareHouse.OpenFlag || cTrade.OpenFlag || cCraftItem.OpenFlag || cAging.OpenFlag || cMyShop.OpenFlag || cCharShop.OpenFlag || ExitButtonClick || MyShopSendButton || SmeltingItem.OpenFlag || ManufactureItem.m_OpenFlag || cMixtureReset.OpenFlag || cElement.OpenFlag || cSocket.OpenFlag || cCaravan.OpenFlag || ReStartFlag)
		return FALSE;
	if (g_IsDxProjectZoomIn <= 0)
		SetFullZoomMap(1);
	return TRUE;
}
int sinRecvForceOrb(Item *pItemInfo, int Count)
{
	int i = 0;
	sinMinusMoney(sCraftItem_Send.Money, 1);
	SendSaveMoney();

	SpecialItemShowFlag = 0;
	ItemData sinTempItem;

	for (i = 0; i < Count; i++)
	{
		if (LoadItemImage(&pItemInfo[i], &sinTempItem))
		{
			if (!cInvenTory.AutoSetInvenItem(&sinTempItem))
			{
				if (sinThrowItemToFeild(&sinTempItem))
					sinTempItem.bValid = 0;
			}
			cMessageBox.ShowMessage(MESSAGE_FORCEORB_REFINING);
		}
	}
	memset(&sCraftItem, 0, sizeof(sCRAFTITEM));
	memset(&sCraftItem_Recv, 0, sizeof(sCRAFTITEM_SERVER));
	memset(&sCraftItem_Send, 0, sizeof(sCRAFTITEM_SERVER));

	cInvenTory.SetItemToChar();
	cInvenTory.ReFormInvenItem();
	cInvenTory.CheckWeight();
	ReformCharForm();
	sinbaram_Stop = 0;
	MixItemNoCopyFlag = 0;
	cCraftItem.OpenFlag = 0;

	cCraftItem.ForceFlag = 0;
	cCraftItem.ForceItemPrice = 0;
	ForceItemPrice2 = 0;

	return TRUE;
}

//Ë«»÷Êó±ê ³èÎïÕÙ»½
int sinDoubleClick()
{
	DWORD Code = TempContinueSkill[ContinueSkillMouseIndex - 1].CODE;

	for (int i = 0; i < SIN_MAX_SKILL_LIST; i++)
	{
		if (Code == SKILL_METAL_GOLEM || Code == SKILL_FIRE_ELEMENTAL || Code == SKILL_RECALL_WOLVERIN || Code == SKILL_S_ARCUDA || Code == SKILL_RECALL_BLOODYKNIGHT)
		{
			if (ContinueSkill[i].CODE == Code)
			{
				ContinueSkill[i].SkillCodeIndex ^= TRUE;
				SendUpdateSkillToServer(Code, ContinueSkill[i].SkillCodeIndex, 0, 0);
				break;
			}
		}
		else if (Code == SKILL_CRYSTAL_ORB)
		{
			if (ContinueSkill[i].CODE == Code && ContinueSkill[i].dwObjectSerial == TempContinueSkill[ContinueSkillMouseIndex - 1].dwObjectSerial)
			{
				ContinueSkill[i].SkillCodeIndex ^= TRUE;
				SendUpdateSkillToServer(Code, ContinueSkill[i].SkillCodeIndex, TempContinueSkill[ContinueSkillMouseIndex - 1].dwObjectSerial, 0);
				break;
			}
		}
	}
	for (int i = 0; i < SINUPKEEPITEM_MAX; i++)
	{
		if (chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::CARAVAN_HOPY ||
			chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::CARAVAN_ARMA ||
			chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::CARAVAN_BUMA ||
			chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::CARAVAN_CUEPY ||
			chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::CARAVAN_HUNGKY ||
			chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::CARAVAN_RABIE ||
			chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::CARAVAN_TOBIE ||
			chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::CARAVAN_RUDOLF)
		{
			if (chaPremiumitem.UpKeepItem[i].Infoflag == true)
			{
				cCaravan.SetHopySelect(cCaravan.SelectMode ^ TRUE);
				break;
			}
		}
	}

	return TRUE;
}
int GetRace(int Class)
{
	switch (Class)
	{
	case CHARACTERCLASS_Fighter:
	case CHARACTERCLASS_Mechanician:
	case CHARACTERCLASS_Archer:
	case CHARACTERCLASS_Pikeman:
	case CHARACTERCLASS_Assassin:
		return BROOD_CODE_TEMPSKRON;
	case CHARACTERCLASS_Atalanta:
	case CHARACTERCLASS_Knight:
	case CHARACTERCLASS_Magician:
	case CHARACTERCLASS_Priestess:
	case CHARACTERCLASS_Shaman:
		return BROOD_CODE_MORAYION;
	}
	return FALSE;
}
int GetSex(int Class)
{
	switch (Class)
	{
	case CHARACTERCLASS_Fighter:
	case CHARACTERCLASS_Mechanician:
	case CHARACTERCLASS_Pikeman:
	case CHARACTERCLASS_Knight:
	case CHARACTERCLASS_Magician:
	case CHARACTERCLASS_Shaman:
		return BROOD_CODE_MAN;
	case CHARACTERCLASS_Archer:
	case CHARACTERCLASS_Atalanta:
	case CHARACTERCLASS_Priestess:
	case CHARACTERCLASS_Assassin:
		return BROOD_CODE_WOMAN;
	}
	return FALSE;
}