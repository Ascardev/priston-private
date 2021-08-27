#include "StdAfx.h"

cTRADE cTrade;
sTRADE sTrade;
sTRADE sTradeRecv;

// ÊôÐÔÏµÍ³
cELEMENT cElement;
//  ´ò¿×ÏµÍ³
cSOCKET cSocket;
// ³èÎï²Ö¿â
cCARAVAN cCaravan;

cMIXTURERESET cMixtureReset;
sMIXTURE_RESET_ITEM	sMixtureResetItem;
sMIXTURE_RESET_ITEM sMixtureResetItemBackUp;
int	MixtureResetCheckFlag = 0;
sMIXTURE_RESET_ITEM_SERVER	sMixtureReset_Send;
sMIXTURE_RESET_ITEM_SERVER	sMixtureReset_Recv;

cAGING	cAging;
sAGINGITEM sAgingItem;
sAGINGITEM sAgingItemBackUp;

sCRAFTITEM_SERVER sAging_Send;
sCRAFTITEM_SERVER sAging_Recv;

cWAREHOUSE cWareHouse;
sWAREHOUSE sWareHouse;

int WareHouseSaveFlag = 0;
int CloseWareHouseCheckFlag2 = 0;
int CloseWareHouseCheckFlag3 = 0;

cCRAFTITEM cCraftItem;
sCRAFTITEM sCraftItem;
sCRAFTITEM sCraftItemBackUp;

CSmeltingItem SmeltingItem;
SSmeltingItem S_smeltingItem;
SSmeltingItem sSmeltingItemBackUp;
sSMELTINGITEM_SERVER sSmeltingItem_Send;
sSMELTINGITEM_SERVER sSmeltingItem_Recv;

CManufacture ManufactureItem;
SManufactureItem sManufactureItem;
SManufactureItem sManufactureItemBackUp;
SManufactureItem_Server sManufactureItem_Send;
SManufactureItem_Server sManufactureItem_Recv;
SManufacture_Rune sManufacture_Rune[MAX_RECIPE_KIND];
SManufacture_ResultItemInfo g_Manufacture_ItemInfo[MAX_HANDMADEITEM];

sCRAFTITEM_SERVER sCraftItem_Send;
sCRAFTITEM_SERVER sCraftItem_Recv;

sCRAFTITEM_SERVER sWingItem_Send;
sCRAFTITEM_SERVER sWingItem_Recv;

int MixItemNoCopyFlag = 0;


int CraftItemButtonIndex = 0;
int CraftItemSendServerIndex = 0;

int CheckMixItemCopyFlag = 0;

int ShowItemCraftMessageFlag = 0;
int ShowItemAgingMessageFlag = 0;
int ShowItemSmeltingMessageFlag = 0;
int ShowItemManufactureMessageFlag = 0;
int ShowItemOverSpace = 0;

char szAgingItemBuff[128];
char szCraftItemBuff[128];
POINT CraftItemMessageBoxPosi = { 0,0 };
POINT CraftItemMessageSize = { 0,0 };


ItemData *BackUpInvenItem2;
ItemData *BackUpInvenTempItem2;
int   InvenGold = 0;
int   RealGold = 0;

int TradeCheckFlag = 0;

int CopyItemIndex7[10] = { 0,0,0,0,0,0,0,0,0,0 };

int CopyItemIndex8[10] = { 0,0,0,0,0,0,0,0,0,0 };

int TradeColorIndex = 0;
int	TradeCrashItemIndex[2] = { 0,0 };
RECT TradeColorRect = { 0,0,0,0 };
int  SelectTradeItemIndex = 0;
int RequestTradeButtonFlag = 0;

int ItemKindFlag = 0;

int CheckDelayFlag = 0;
int sinCancelFlag = 0;

int TempShowMoney = 0;

int CloseWareHouseFlag = 0;

int ItemPickUpFlag = 0;

sPOSTBOX_ITEM sPostbox_Item[50];
int PostBoxIndexCnt = 0;
DWORD ExpressItemCode = 0;
char  szExpressItemName[64];

char *PostBoxDocFilePath[] =
{
	"image\\Sinimage\\shopall\\PostBox.sin",
};

// Ï´Ê¯ÐÅÏ¢
#ifdef ENGLISH_LANGUAGE
sRECON_ITEM sReconItem[MAX_SEEL_COUNT] =
{
	//CODE         level    count price
   {(sinSE1 | sin01) ,{101,125}	,2   ,70000},
   {(sinSE1 | sin02) ,{61,100}	,2   ,50000 },
   {(sinSE1 | sin03) ,{0,60}		,2   ,2000  },
   {(sinSE1 | sin04) ,{126,160}	,2   ,100000 }
};
#else
sRECON_ITEM sReconItem[MAX_SEEL_COUNT] =
{
	//CODE         level    count price
	{(sinSE1 | sin01) ,{0,110}	,2   ,70000},
	{(sinSE1 | sin02) ,{40,79}	,2   ,50000 },
	{(sinSE1 | sin03) ,{0,39}		,2   ,2000  },
	{(sinSE1 | sin04) ,{0,140}	,2   ,100000 }
};
#endif

#define T_REVISION_Y			22*5


#define TRADEBUTTONMAIN_X		513
#define TRADEBUTTONMAIN_Y		3

#include "..\\nettype.hpp"

//ºÏ³É¹«Ê½
sCRAFTITEM_INFO sCraftItem_Info[MAX_CRAFTITEM_INFO] =
{
	#include "sinCraftItem.h"
};


sMAKEITEM_INFO sMakeItem_Info[MAX_MAKEITEM_INFO] =
{
	{{(sinMA1 | sin01),(sinMA2 | sin01),(sinMA2 | sin01),(sinMA2 | sin01),(sinMA2 | sin01),(sinMA2 | sin01),(sinMA2 | sin01),(sinMA2 | sin01),(sinMA2 | sin01),(sinMA2 | sin01)},(sinQT1 | sin04)},
	{{(sinMA1 | sin01),(sinMA2 | sin02),(sinMA2 | sin02),(sinMA2 | sin02),(sinMA2 | sin02),(sinMA2 | sin02),(sinMA2 | sin02),(sinMA2 | sin02),},(sinQT1 | sin05)}
};


DWORD sinTradeColor = 0;

char szAgingMsgBuff[128];

#define MAX_AGING_ITEM 17

DWORD AgingItemCode3[MAX_AGING_ITEM] = { sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1,sinWD1,sinWN1,sinDA1,sinDS1,sinOM1,sinDA2,sinDG1	,sinDB1,sinOA2 };
DWORD SheltomCODE[MAX_SHELTOM] = { sin01 ,sin02 ,sin03 ,sin04 ,sin05 ,sin06 ,sin07 ,sin08 ,sin09 ,sin10 ,sin11 ,sin12 ,sin13 ,sin14	,sin15	,sin16 };

int AgingLevelAttack[25] = { 100		,130	,169	,219	,284	,369	,479	,622	,808	,1049	,1362	,1769	,2297	,2983	,3874	,5031	,6534	,8486	,11021	,14313	,18513	,24013	,30213	,37313 };
int AgingLevelCritical[25] = { 12		,16		,21		,27		,35		,45		,58		,75		,97		,126	,164	,213	,277	,360	,468	,608	,790	,1026	,1332	,1730	,2070	,2430	,2850	,3300 };
int AgingLevelBlock[25] = { 15		,19		,25		,32		,42		,55		,71		,92		,119	,155	,201	,261	,339	,440	,571	,742	,964	,1252	,1626	,2112	,2712	,3412	,4162	,4662 };
int AgingLevelHit[25] = { 45		,58		,75		,97		,126	,164	,213	,277	,360	,468	,608	,790	,1026	,1332	,1730	,2247	,2918	,3790	,4922	,6392	,7492	,8692	,10092	,11692 };
int AgingBlast[25] = { 0		,0		,0		,0		,0		,0		,0		,0		,15		,20		,30		,40		,50		,60		,70		,80		,80		,80		,80		,80		,80		,80		,80		,80		,80 };

int PlusAgingPercent[24] = { 30		,25		,20		,10		,10		,10		,10		,5		,5		,5		,5		,4		,4		,3		,3		,2		,2		,2		,0		,0		,0		,0		,0		,0 };
int AgingOkPercent[24] = { 0		,0		,0		,0		,0		,0		,5		,10		,15		,20		,25		,30		,35		,40		,45		,50		,55		,65		,70		,75		,80		,85		,90		,95 };
int AgingStoneAgingOkPercent5[24] = { 0		,0		,0		,0		,0		,0		,0		,5		,10		,15		,20		,25		,30		,35		,40		,45		,50		,60		,65		,70		,75		,80		,85		,90 };
int AgingStoneAgingOkPercent10[24] = { 0		,0		,0		,0		,0		,0		,0		,0		,5		,10		,15		,20		,25		,30		,35		,40		,45		,55		,60		,65		,70		,75		,80		,85 };
int AgingStoneAgingOkPercent15[24] = { 0		,0		,0		,0		,0		,0		,0		,0		,0		,5		,10		,15		,20		,25		,30		,35		,40		,50		,55		,60		,65		,70		,75		,80 };
int AgingStoneAgingOkPercent20[24] = { 0		,0		,0		,0		,0		,0		,0		,0		,0		,0		,5		,10		,15		,20		,25		,30		,35		,45		,50		,55		,60		,65		,70		,75 };
int AgingStoneAgingOkPercent25[24] = { 0		,0		,0		,0		,0		,0		,0		,0		,0		,0		,0		,5		,10		,15		,20		,25		,30		,40		,45		,50		,55		,60		,65		,70 };

int AgingLevelSheltom[24][12] =
{
	{3	,3	,4	,4	,5	,0	,0	,0	,0	,0	,0	,0	},
	{3	,3	,4	,4	,5	,5	,0	,0	,0	,0	,0	,0	},
	{3	,3	,4	,4	,5	,5	,6	,0	,0	,0	,0	,0	},
	{3	,3	,4	,4	,5	,5	,6	,6	,0	,0	,0	,0	},
	{3	,3	,4	,4	,5	,5	,6	,6	,7	,0	,0	,0	},
	{3	,3	,4	,4	,5	,5	,6	,6	,7	,7	,0	,0	},
	{3	,3	,4	,4	,5	,5	,6	,6	,7	,7	,8	,0	},
	{3	,3	,4	,4	,5	,5	,6	,6	,7	,7	,8	,8	},
	{4	,4	,5	,5	,6	,6	,7	,7	,8	,8	,9	,0	},
	{4	,4	,5	,5	,6	,6	,7	,7	,8	,8	,9	,9	},

	{5	,5	,6	,6	,7	,7	,8	,8	,9	,9	,10	,0	},
	{5	,5	,6	,6	,7	,7	,8	,8	,9	,9	,10	,10	},
	{6	,6	,7	,7	,8	,8	,9	,9	,10	,10	,11	,0	},
	{6	,6	,7	,7	,8	,8	,9	,9	,10	,10	,11	,11	},
	{7	,7	,8	,8	,9	,9	,10	,10	,11	,11	,12	,0	},
	{7	,7	,8	,8	,9	,9	,10	,10	,11	,11	,12	,12	},

	{8	,8	,9	,9	,10	,10	,11	,11	,12	,12	,13	,0	},
	{8	,8	,9	,9	,10	,10	,11	,11	,12	,12	,13	,13	},
	{9	,9	,10	,10	,11	,11	,12	,12	,13	,13	,14	,0	},
	{9	,9	,10	,10	,11	,11	,12	,12	,13	,13	,14	,14	},
	{10	,10	,11	,11	,12	,12	,13	,13	,14	,14	,15	,0	},
	{10	,10	,11	,11	,12	,12	,13	,13	,14	,14	,15	,15	},
	{11	,11	,12	,12	,13	,13	,14	,14	,15	,15	,16	,0	},
	{11	,11	,12	,12	,13	,13	,14	,14	,15	,15	,16	,16	},
};

int AgingLevelSheltomIndex[4][3] =
{
	0,0,0,
	0,0,0,
	0,0,0,
	0,0,0
};


int AgingCheckSheltomFlag = 0;
int AgingSheltomCnt2 = 0;

#define SIN_AGING_MASK	0x00101011

int AgingLevelMoney[20] = { 1000 ^ SIN_AGING_MASK,2000 ^ SIN_AGING_MASK,3000 ^ SIN_AGING_MASK,4000 ^ SIN_AGING_MASK,5000 ^ SIN_AGING_MASK,
							6000 ^ SIN_AGING_MASK,7000 ^ SIN_AGING_MASK,8000 ^ SIN_AGING_MASK,9000 ^ SIN_AGING_MASK,10000 ^ SIN_AGING_MASK,
							11000 ^ SIN_AGING_MASK,12000 ^ SIN_AGING_MASK,13000 ^ SIN_AGING_MASK,14000 ^ SIN_AGING_MASK,15000 ^ SIN_AGING_MASK,
							16000 ^ SIN_AGING_MASK,17000 ^ SIN_AGING_MASK,18000 ^ SIN_AGING_MASK,19000 ^ SIN_AGING_MASK,20000 ^ SIN_AGING_MASK };


int ForceItemPrice2 = 0;
smTEXTUREHANDLE	*lpForceMain;
smTEXTUREHANDLE	*lpForceButtonInfo;
smTEXTUREHANDLE	*lpForceTitle;

DWORD NoMixItem3[] =
{
	(sinOA1 | sin32),(sinOA1 | sin33),
	(sinOA1 | sin34),(sinOA1 | sin35),
	(sinOA1 | sin36),(sinOA1 | sin37),
	(sinOA1 | sin38),(sinOA1 | sin39),
	(sinOA1 | sin40),(sinOA1 | sin41),
	(sinOA1 | sin42),
	(sinOA2 | sin31),(sinOA2 | sin32),
	(sinOA2 | sin33),(sinOA2 | sin34),
	(sinDB1 | sin31),(sinDB1 | sin32),
	(sinDB1 | sin33),(sinDB1 | sin34),
};


cTRADE::cTRADE()
{

}
cTRADE::~cTRADE()
{

}

DWORD TradeSpotTimer = 0;


DWORD	dwTradeDelayTime = 0;
DWORD	dwTradeDelayTime2 = 0;
DWORD	dwTradeDelayTime3 = 0;
DWORD	dwTradeDelayTime4 = 0;

DWORD   dwCraftItemInfoDelayTime = 0;
DWORD   dwMixDelayTime = 0;
DWORD	dwMixItemColyTime = 0;
int		MixCancelButtonDelayFlag = 0;
DWORD   dwForceDelayTime = 0;



int SendServerFlag7 = 0;


int ForceOrbPriceIndex[] = { 200,500,1000,2000,4000,5000,10000,20000,30000,40000,50000,60000,70000,80000,90000,100000 };

DWORD SheltomCode2[] = { sin01,sin02,sin03,sin04,sin05,sin06,sin07,sin08,sin09,sin10,sin11,sin12,sin13,sin14,sin15,sin16 };

int cCRAFTITEM::CheckForceOrbPrice()
{
	ForceItemPrice = 0;
	for (int j = 1; j < 15; j++)
	{
		if (sCraftItem.CraftItem[j].bValid)
		{
			for (int t = 0; t < 16; t++)
			{
				if ((sCraftItem.CraftItem[j].sItem.sItemID.ToItemIndex()) <= sin20)
				{
					if ((sCraftItem.CraftItem[j].sItem.sItemID.ToItemIndex()) == SheltomCode2[t])
					{
						ForceItemPrice += ForceOrbPriceIndex[t];
						break;
					}
				}
			}
		}
	}
	ForceItemPrice2 = ForceItemPrice;
	return TRUE;
}
int cCRAFTITEM::CheckForceOrbPrice(ItemData *pItem)
{
	int TempPrice = 0;
	for (int j = 1; j < 15; j++)
	{
		if (sCraftItem.CraftItem[j].bValid)
		{
			for (int t = 0; t < 16; t++)
			{
				if ((sCraftItem.CraftItem[j].sItem.sItemID.ToItemIndex()) == SheltomCode2[t])
				{
					TempPrice += ForceOrbPriceIndex[t];
					break;
				}
			}
		}
	}

	for (int t = 0; t < 16; t++)
	{
		if ((pItem->sItem.sItemID.ToItemIndex()) == SheltomCode2[t])
			return TempPrice + ForceOrbPriceIndex[t];
	}
	return FALSE;
}

DWORD SheltomCode[MAX_MIX_STONE] = { sin01,sin02,sin03,sin04,sin05,sin06,sin07,sin08,sin09,sin10,sin11,sin12,sin13,sin14,sin15,sin16 };

//ºÏ³ÉÎïÆ·
int cCRAFTITEM::MixingItem()
{
	int i, j, t, k, CheckFlag = 0, Temp = 0, LineCount = 0;
	DWORD TempCode2 = 0;
	int  ReConCnt = 0;
	int Result[MAX_SEEL_COUNT] = { 0 };
	// Ôì»¯Ê¯
	if (sCraftItem_Recv.DocIndex == 2000)
	{
		for (i = 0; i < 12; i++)
		{
			if (sCraftItem_Recv.SheltomCode[i])
			{
				TempCode2 = sCraftItem_Recv.SheltomCode[i];

				for (j = 0; j < MAX_SEEL_COUNT; j++)
				{
					if (sReconItem[j].dwCODE == sCraftItem_Recv.SheltomCode[i])
					{
						if (sCraftItem_Recv.DesCraftItem.sItem.iLevel >= sReconItem[j].iLevel[0] && sCraftItem_Recv.DesCraftItem.sItem.iLevel <= sReconItem[j].iLevel[1])
						{
							Result[j] ++;
							break;
						}
					}
				}
			}
		}
		for (j = 0; j < MAX_SEEL_COUNT; j++)
		{
			if (Result[j] == sReconItem[j].iCount)
				ReConCnt++;
		}
		if (!ReConCnt)
		{
			sCraftItem_Recv.Result = FALSE;
			return FALSE;
		}
		sCraftItem_Recv.Result = TRUE;
		return 2000;
	}
	for (j = 0; j < 12; j++)
	{
		if ((sCraftItem_Recv.SheltomCode[j] & sinITEM_MASK2) == sinSE1)
		{
			sCraftItem_Recv.Result = FALSE;
			return FALSE;
		}
	}
	for (j = 0; j < MAX_MIX_STONE; j++)
		sCraftItem.SheltomIndex[j] = 0;

	for (i = 0; i < 12; i++)
	{
		if ((sCraftItem_Recv.SheltomCode[i] & sinITEM_MASK2) == sinOS1)
		{
			for (j = 0; j < MAX_MIX_STONE; j++)
			{
				if ((sCraftItem_Recv.SheltomCode[i] & sinITEM_MASK3) == SheltomCode[j])
				{
					sCraftItem.SheltomIndex[j]++;
					break;
				}
			}
		}
	}
	for (i = 0; i < MAX_CRAFTITEM_INFO; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (sCraftItem_Recv.DesCraftItem.bValid)
			{
				if ((sCraftItem_Info[i].MainItemCode[j] & sinITEM_MASK2) == (sCraftItem_Recv.DesCraftItem.sItem.sItemID.ToItemType()))
				{
					// ÅÐ¶ÏÊ¯Í·µÄÊýÁ¿
					for (t = 0; t < MAX_MIX_STONE; t++)
					{
						if (sCraftItem_Info[i].AddItem[t] != sCraftItem.SheltomIndex[t])
						{
							CheckFlag = 1;
							break;
						}
						CheckFlag = 0;
					}

					if (!CheckFlag)
					{
						for (k = 0; k < 9; k++)
						{
							if (sCraftItem.SheltomIndex[k])
								sCraftItem_Recv.DesCraftItem.sItem.sAgeLevel = k + 1;

							if (sCraftItem_Info[i].PlusElementCode[k])
							{
								switch (sCraftItem_Info[i].PlusElementCode[k])
								{
								case SIN_ADD_FIRE:
									sCraftItem_Recv.DesCraftItem.sItem.saElementalDef[sITEMINFO_FIRE] += (int)sCraftItem_Info[i].AddElement[k];
									sCraftItem_Recv.DesCraftItem.sItem.eMixEffect |= SIN_ADD_FIRE;

									break;
								case SIN_ADD_ICE:
									sCraftItem_Recv.DesCraftItem.sItem.saElementalDef[sITEMINFO_ICE] += (int)sCraftItem_Info[i].AddElement[k];
									sCraftItem_Recv.DesCraftItem.sItem.eMixEffect |= SIN_ADD_ICE;
									break;
								case SIN_ADD_LIGHTNING:
									sCraftItem_Recv.DesCraftItem.sItem.saElementalDef[sITEMINFO_LIGHTING] += (int)sCraftItem_Info[i].AddElement[k];
									sCraftItem_Recv.DesCraftItem.sItem.eMixEffect |= SIN_ADD_LIGHTNING;
									break;

								case SIN_ADD_POISON:
									sCraftItem_Recv.DesCraftItem.sItem.saElementalDef[sITEMINFO_POISON] += (int)sCraftItem_Info[i].AddElement[k];
									sCraftItem_Recv.DesCraftItem.sItem.eMixEffect |= SIN_ADD_POISON;
									break;
								case SIN_ADD_BIO:
									sCraftItem_Recv.DesCraftItem.sItem.saElementalDef[sITEMINFO_BIONIC] += (int)sCraftItem_Info[i].AddElement[k];
									sCraftItem_Recv.DesCraftItem.sItem.eMixEffect |= SIN_ADD_BIO;
									break;
								case SIN_ADD_CRITICAL:// ±ØÉ±
									if (sCraftItem_Info[i].ElementKind[k] == SIN_ADD_NUM)
										sCraftItem_Recv.DesCraftItem.sItem.iCritical += (int)sCraftItem_Info[i].AddElement[k];
									else
										sCraftItem_Recv.DesCraftItem.sItem.iCritical += (sCraftItem_Recv.DesCraftItem.sItem.iCritical*((int)sCraftItem_Info[i].AddElement[k])) / 100;
									sCraftItem_Recv.DesCraftItem.sItem.eMixEffect |= SIN_ADD_CRITICAL;
									break;
								case SIN_ADD_ATTACK_RATE:// ÃüÖÐ
									if (sCraftItem_Info[i].ElementKind[k] == SIN_ADD_NUM)
										sCraftItem_Recv.DesCraftItem.sItem.iAttackRating += (int)sCraftItem_Info[i].AddElement[k];
									else
										sCraftItem_Recv.DesCraftItem.sItem.iAttackRating += (sCraftItem_Recv.DesCraftItem.sItem.iAttackRating*((int)sCraftItem_Info[i].AddElement[k])) / 100;
									sCraftItem_Recv.DesCraftItem.sItem.eMixEffect |= SIN_ADD_ATTACK_RATE;
									break;
								case SIN_ADD_DAMAGE_MIN:	//×îÐ¡ÉËº¦
									if (sCraftItem_Info[i].ElementKind[k] == SIN_ADD_NUM)
										sCraftItem_Recv.DesCraftItem.sItem.sDamage.sMin += (int)sCraftItem_Info[i].AddElement[k];
									else
										sCraftItem_Recv.DesCraftItem.sItem.sDamage.sMin += (sCraftItem_Recv.DesCraftItem.sItem.sDamage.sMin * ((int)sCraftItem_Info[i].AddElement[k])) / 100;
									sCraftItem_Recv.DesCraftItem.sItem.eMixEffect |= SIN_ADD_DAMAGE_MIN;
									break;

								case SIN_ADD_DAMAGE_MAX:	//×î´óÉËº¦
									if (sCraftItem_Info[i].ElementKind[k] == SIN_ADD_NUM)
										sCraftItem_Recv.DesCraftItem.sItem.sDamage.sMax += (int)sCraftItem_Info[i].AddElement[k];
									else
										sCraftItem_Recv.DesCraftItem.sItem.sDamage.sMax += (sCraftItem_Recv.DesCraftItem.sItem.sDamage.sMax * ((int)sCraftItem_Info[i].AddElement[k])) / 100;
									sCraftItem_Recv.DesCraftItem.sItem.eMixEffect |= SIN_ADD_DAMAGE_MAX;
									break;
								case SIN_ADD_ATTACK_SPEED:	//¹¥»÷ËÙ¶È
									if (sCraftItem_Info[i].ElementKind[k] == SIN_ADD_NUM)
										sCraftItem_Recv.DesCraftItem.sItem.iAttackSpeed += (int)sCraftItem_Info[i].AddElement[k];
									else
										sCraftItem_Recv.DesCraftItem.sItem.iAttackSpeed += (sCraftItem_Recv.DesCraftItem.sItem.iAttackSpeed*((int)sCraftItem_Info[i].AddElement[k])) / 100;
									sCraftItem_Recv.DesCraftItem.sItem.eMixEffect |= SIN_ADD_ATTACK_SPEED;
									break;
								case SIN_ADD_ABSORB:	//Èí¼ö·Â 
									if (sCraftItem_Info[i].ElementKind[k] == SIN_ADD_NUM)
										sCraftItem_Recv.DesCraftItem.sItem.fAbsorbRating += sCraftItem_Info[i].AddElement[k];
									else
										sCraftItem_Recv.DesCraftItem.sItem.fAbsorbRating += (GetItemAbsorb(&sCraftItem_Recv.DesCraftItem.sItem)*(sCraftItem_Info[i].AddElement[k] / 100));
									sCraftItem_Recv.DesCraftItem.sItem.eMixEffect |= SIN_ADD_ABSORB;
									break;
								case SIN_ADD_DEFENCE:	//¹æ¾î·Â 
									if (sCraftItem_Info[i].ElementKind[k] == SIN_ADD_NUM)
										sCraftItem_Recv.DesCraftItem.sItem.iDefenseRating += (int)sCraftItem_Info[i].AddElement[k];
									else
										sCraftItem_Recv.DesCraftItem.sItem.iDefenseRating += (sCraftItem_Recv.DesCraftItem.sItem.iDefenseRating*((int)sCraftItem_Info[i].AddElement[k])) / 100;
									sCraftItem_Recv.DesCraftItem.sItem.eMixEffect |= SIN_ADD_DEFENCE;
									break;
								case SIN_ADD_BLOCK_RATE: //ºí·°À² 
									if (sCraftItem_Info[i].ElementKind[k] == SIN_ADD_NUM)
										sCraftItem_Recv.DesCraftItem.sItem.fBlockRating += sCraftItem_Info[i].AddElement[k];
									else
										sCraftItem_Recv.DesCraftItem.sItem.fBlockRating += (sCraftItem_Recv.DesCraftItem.sItem.fBlockRating*(sCraftItem_Info[i].AddElement[k] / 100));
									sCraftItem_Recv.DesCraftItem.sItem.eMixEffect |= SIN_ADD_BLOCK_RATE;
									break;
								case SIN_ADD_MOVE_SPEED: //ÀÌµ¿¼Óµµ 
									if (sCraftItem_Info[i].ElementKind[k] == SIN_ADD_NUM)
										sCraftItem_Recv.DesCraftItem.sItem.fMovementSpeed += sCraftItem_Info[i].AddElement[k];
									else
										sCraftItem_Recv.DesCraftItem.sItem.fMovementSpeed += (sCraftItem_Recv.DesCraftItem.sItem.fMovementSpeed*(sCraftItem_Info[i].AddElement[k] / 100));
									sCraftItem_Recv.DesCraftItem.sItem.eMixEffect |= SIN_ADD_MOVE_SPEED;
									break;
								case SIN_ADD_LIFE:
									if (sCraftItem_Info[i].ElementKind[k] == SIN_ADD_NUM)
										sCraftItem_Recv.DesCraftItem.sItem.fAddHP += sCraftItem_Info[i].AddElement[k];
									else
										sCraftItem_Recv.DesCraftItem.sItem.fAddHP += (sCraftItem_Recv.DesCraftItem.sItem.fAddHP*(sCraftItem_Info[i].AddElement[k] / 100));
									sCraftItem_Recv.DesCraftItem.sItem.eMixEffect |= SIN_ADD_LIFE;
									break;

								case SIN_ADD_MANA:
									if (sCraftItem_Info[i].ElementKind[k] == SIN_ADD_NUM)
										sCraftItem_Recv.DesCraftItem.sItem.fAddMP += sCraftItem_Info[i].AddElement[k];
									else
										sCraftItem_Recv.DesCraftItem.sItem.fAddMP += (sCraftItem_Recv.DesCraftItem.sItem.fAddMP*(sCraftItem_Info[i].AddElement[k] / 100));
									sCraftItem_Recv.DesCraftItem.sItem.eMixEffect |= SIN_ADD_MANA;
									break;
								case SIN_ADD_STAMINA:
									if (sCraftItem_Info[i].ElementKind[k] == SIN_ADD_NUM)
										sCraftItem_Recv.DesCraftItem.sItem.fAddSP += sCraftItem_Info[i].AddElement[k];
									else
										sCraftItem_Recv.DesCraftItem.sItem.fAddSP += (sCraftItem_Recv.DesCraftItem.sItem.fAddSP*(sCraftItem_Info[i].AddElement[k] / 100));
									sCraftItem_Recv.DesCraftItem.sItem.eMixEffect |= SIN_ADD_STAMINA;
									break;
								case SIN_ADD_LIFEREGEN:
									if (sCraftItem_Info[i].ElementKind[k] == SIN_ADD_NUM)
										sCraftItem_Recv.DesCraftItem.sItem.fHPRegen += sCraftItem_Info[i].AddElement[k];
									else
										sCraftItem_Recv.DesCraftItem.sItem.fHPRegen += (sCraftItem_Recv.DesCraftItem.sItem.fHPRegen*(sCraftItem_Info[i].AddElement[k] / 100));
									sCraftItem_Recv.DesCraftItem.sItem.eMixEffect |= SIN_ADD_LIFEREGEN;
									break;
								case SIN_ADD_MANAREGEN:
									if (sCraftItem_Info[i].ElementKind[k] == SIN_ADD_NUM)
										sCraftItem_Recv.DesCraftItem.sItem.fMPRegen += sCraftItem_Info[i].AddElement[k];
									else
										sCraftItem_Recv.DesCraftItem.sItem.fMPRegen += (sCraftItem_Recv.DesCraftItem.sItem.fMPRegen*(sCraftItem_Info[i].AddElement[k] / 100));
									sCraftItem_Recv.DesCraftItem.sItem.eMixEffect |= SIN_ADD_MANAREGEN;

									break;
								case SIN_ADD_STAMINAREGEN:
									if (sCraftItem_Info[i].ElementKind[k] == SIN_ADD_NUM)
										sCraftItem_Recv.DesCraftItem.sItem.fSPRegen += sCraftItem_Info[i].AddElement[k];
									else
										sCraftItem_Recv.DesCraftItem.sItem.fSPRegen += (sCraftItem_Recv.DesCraftItem.sItem.fSPRegen*(sCraftItem_Info[i].AddElement[k] / 100));
									sCraftItem_Recv.DesCraftItem.sItem.eMixEffect |= SIN_ADD_STAMINAREGEN;

									break;

								}
							}
						}

						sCraftItem_Recv.DesCraftItem.sItem.ItemCraftCode = i;

						ReformItem(&sCraftItem_Recv.DesCraftItem.sItem);

						if (!CheckMixItem(&sCraftItem_Recv.DesCraftItem.sItem))
						{
							return FALSE;
						}


						sCraftItem_Recv.DesCraftItem.sItem.eCraftType = ITEMCRAFTTYPE_Mixing;
						ReformMixItem(&sCraftItem_Recv.DesCraftItem.sItem);

						sCraftItem_Recv.DocIndex = i;
						sCraftItem_Recv.Result = TRUE;

						return TRUE;

					}
				}
			}
		}
	}

	sCraftItem_Recv.Result = FALSE;

	return FALSE;
}


int CraftItemCheckDelayTime = 0;


//¶ÍÔìÎïÆ· 
int cAGING::AgingItem(int MakeItemFlag)
{
#ifdef _W_SERVER
	int ResultCount = 0;
	int ResultCountCheck = 0;
	DWORD TempCODE[16] = { 0, };

	switch (sAging_Recv.A_StoneItemCode)
	{
	case sinBI1 | sin10:
		AginStoneKind = 1; //×ÏË®¾§
		break;
	case sinBI1 | sin11:
		AginStoneKind = 2; //¶ÍÔìÊØ»¤
		break;
	case sinBI2 | sin66:
		AginStoneKind = 3; //ÁÒ»ð¶ÍÔìË®¾§
		break;
	case sinBI2 | sin67:
		AginStoneKind = 4; //º®±ù¶ÍÔìË®¾§
		break;
	case sinBI2 | sin68:
		AginStoneKind = 5; //ÓÄÂÌ¶ÍÔìË®¾§
		break;
	case sinBI2 | sin78:
		AginStoneKind = 6; //»ÆË®¾§
		break;
	case sinBI2 | sin79:
		AginStoneKind = 7; //ºìË®¾§
		break;
	case sinBI2 | sin80:
		AginStoneKind = 8; //À¶Ë®¾§
		break;
	case sinBI2 | sin81:
		AginStoneKind = 9; //ÂÌË®¾§
		break;
	default:
		AginStoneKind = 0;
		break;
	}
	if (sAging_Recv.DesCraftItem.sItem.eCraftType == ITEMCRAFTTYPE_QuestWeapon) // ÈÎÎñÎäÆ÷
	{
		if (SetChangeJob3QuestItem(&sAging_Recv.DesCraftItem.sItem))
		{
			ReformMixItem(&sAging_Recv.DesCraftItem.sItem);
			sAging_Recv.Result = 100 + sAging_Recv.DesCraftItem.sItem.sAgeLevel;
			return TRUE;
		}
		sAging_Recv.Result = FALSE;
		return FALSE;
	}

	for (int i = 0; i < MAX_MAKEITEM_INFO; i++)
	{
		TempCODE[0] = sAging_Recv.DesCraftItem.sItem.sItemID.ToInt(); //ÎïÆ·´úÂë
		for (int p = 0; p < 15; p++)
		{
			if (sAging_Recv.SheltomCode[p])
				TempCODE[p + 1] = sAging_Recv.SheltomCode[p];
		}
		for (int j = 0; j < 15; j++)
		{
			if (sMakeItem_Info[i].CODE[j])
			{
				ResultCount++;
				for (int k = 0; k < 15; k++)
				{
					if (sAging_Recv.SheltomCode[k] && TempCODE[k])
					{
						if (TempCODE[k] == sMakeItem_Info[i].CODE[j])
						{
							TempCODE[k] = -1;
							ResultCountCheck++;
						}
					}
				}
				if (sAging_Recv.DesCraftItem.sItem.sItemID.ToInt() == sMakeItem_Info[i].CODE[j])
					ResultCountCheck++;
			}
		}
		if (ResultCount && ResultCountCheck &&ResultCount == ResultCountCheck)
		{
			sAging_Recv.DesCraftItem.sItem.sItemID = sMakeItem_Info[i].Result_CODE;
			sAging_Recv.Result = TRUE;
			return TRUE;
		}
		else
			AgingCheckSheltomFlag = 0;
		ResultCount = 0;
		ResultCountCheck = 0;

	}

	if (MakeItemFlag > 0)
		return FALSE;
	int DestroyPersent = 0;

	DWORD CheckSheltomCODE[12] = { 0, };
	DWORD CheckSheltomCODE2[12] = { 0, };

	DWORD ItemCode[] = { sinOA1,sinOR1,sinOS1 }; // ²»ÄÜ¶ÍÔìµÄÎïÆ·

	for (int i = 0; i < sizeof(ItemCode) / sizeof(DWORD); i++)
	{
		if ((sAging_Recv.DesCraftItem.sItem.sItemID.ToItemType()) == ItemCode[i])
		{
			sAging_Recv.Result = FALSE;
			return FALSE;
		}
	}
	int AgingLevel = sAging_Recv.DesCraftItem.sItem.sAgeLevel;

	for (int g = 0; g < 12; g++)
	{
		if (AgingLevelSheltom[AgingLevel][g])
		{
			CheckSheltomCODE[g] = sinOS1 | (SheltomCODE[AgingLevelSheltom[AgingLevel][g] - 1]);
			CheckSheltomCODE2[g] = sAging_Recv.SheltomCode[g];
		}
	}
	DWORD Temp = 0;
	for (int i = 11; i > 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (CheckSheltomCODE[j] < CheckSheltomCODE[j + 1])
			{
				Temp = CheckSheltomCODE[j + 1];
				CheckSheltomCODE[j + 1] = CheckSheltomCODE[j];
				CheckSheltomCODE[j] = Temp;
			}
			if (CheckSheltomCODE2[j] < CheckSheltomCODE2[j + 1])
			{
				Temp = CheckSheltomCODE2[j + 1];
				CheckSheltomCODE2[j + 1] = CheckSheltomCODE2[j];
				CheckSheltomCODE2[j] = Temp;
			}
		}
	}
	for (int i = 0; i < 12; i++)
	{
		if (CheckSheltomCODE[i])
		{
			if (CheckSheltomCODE2[i] != CheckSheltomCODE[i])
				return FALSE;
		}
	}

	ItemData *pItem = &sAging_Recv.DesCraftItem;

	if (!sinCheckAgingItemHack(pItem))
	{
		sAging_Recv.Result = FALSE;
		return FALSE;
	}

	if (MakeItemFlag == -1)
		DestroyPersent = 100;
	else
		DestroyPersent = GetRandomPos(0, 100);

	int AgingItemFaildNum = 3;

	int DownPersent = GetRandomPos(0, 100);
	int PlusPersent = GetRandomPos(0, 100);

	int CurrentDestoryPersent;

	switch (AginStoneKind)
	{
	case 1:
		CurrentDestoryPersent = AgingStoneAgingOkPercent5[sAging_Recv.DesCraftItem.sItem.sAgeLevel];
		break;
	case 6:
		CurrentDestoryPersent = AgingStoneAgingOkPercent10[sAging_Recv.DesCraftItem.sItem.sAgeLevel];
		break;
	case 7:
		CurrentDestoryPersent = AgingStoneAgingOkPercent15[sAging_Recv.DesCraftItem.sItem.sAgeLevel];
		break;
	case 8:
		CurrentDestoryPersent = AgingStoneAgingOkPercent20[sAging_Recv.DesCraftItem.sItem.sAgeLevel];
		break;
	case 9:
		CurrentDestoryPersent = AgingStoneAgingOkPercent25[sAging_Recv.DesCraftItem.sItem.sAgeLevel];
		break;
	default:
		CurrentDestoryPersent = AgingOkPercent[sAging_Recv.DesCraftItem.sItem.sAgeLevel];
		break;
	}
	if (CurrentDestoryPersent > DestroyPersent)
	{ //µÍÓÚ¶ÍÔìÂÊ½øÐÐÊ§°Ü´¦Àí
		switch (sAging_Recv.DesCraftItem.sItem.sAgeLevel)
		{
		case 6:
			if (DownPersent < 90)
				AgingItemFaildNum = 1; //-1
			else
				AgingItemFaildNum = 2; //-2
			break;
		case 7:
			if (DownPersent < 80)
				AgingItemFaildNum = 1;
			else
				AgingItemFaildNum = 2;
			break;
		case 8:
			if (DownPersent < 70)
				AgingItemFaildNum = 1;
			else if (DownPersent >= 70 && DownPersent < 85)
				AgingItemFaildNum = 2;
			else
				AgingItemFaildNum = 0;
			break;
		case 9:
			if (DownPersent < 60)
				AgingItemFaildNum = 1;
			else if (DownPersent >= 60 && DownPersent < 80)
				AgingItemFaildNum = 2;
			else
				AgingItemFaildNum = 0;
			break;
		case 10:
			if (DownPersent < 50)
				AgingItemFaildNum = 1;
			else if (DownPersent >= 50 && DownPersent < 70)
				AgingItemFaildNum = 2;
			else
				AgingItemFaildNum = 0;
			break;
		case 11:
			if (DownPersent < 40)
				AgingItemFaildNum = 1;
			else if (DownPersent >= 40 && DownPersent < 60)
				AgingItemFaildNum = 2;
			else
				AgingItemFaildNum = 0;
			break;
		case 12:
			if (DownPersent < 30)
				AgingItemFaildNum = 1;
			else if (DownPersent >= 30 && DownPersent < 50)
				AgingItemFaildNum = 2;
			else
				AgingItemFaildNum = 0;
			break;
		case 13:
			if (DownPersent < 30)
				AgingItemFaildNum = 1;
			else if (DownPersent >= 30 && DownPersent < 40)
				AgingItemFaildNum = 2;
			else
				AgingItemFaildNum = 0;
			break;
		case 14:
			if (DownPersent < 20)
				AgingItemFaildNum = 1;
			else if (DownPersent >= 20 && DownPersent < 30)
				AgingItemFaildNum = 2;
			else
				AgingItemFaildNum = 0;
			break;
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:
		case 20:
		case 21:
		case 22:
		case 23:
		case 24:
			if (DownPersent < 10)
				AgingItemFaildNum = 1;
			else if (DownPersent >= 10 && DownPersent < 20)
				AgingItemFaildNum = 2;
			else
				AgingItemFaildNum = 0;
			break;
		}
	}
	else
	{ // ³É¹¦´¦Àí
		if (sAging_Recv.DesCraftItem.sItem.sAgeLevel < 10)// ¶ÍÔìµÈ¼¶Ð¡ÓÚ10
		{
			if ((PlusAgingPercent[sAging_Recv.DesCraftItem.sItem.sAgeLevel] * 2) > PlusPersent)
			{
				sinSetAgingItemIncreState(&sAging_Recv.DesCraftItem.sItem);
				AgingItemFaildNum = 4;
			}
		}
	}
	switch (AginStoneKind)
	{
	case 2:
		if (AgingItemFaildNum == 0)
		{
			if (rand() % 100 < 81)
				AgingItemFaildNum = 1;
			else
				AgingItemFaildNum = 2;
		}
		break;
	case 3:
		if (sAging_Recv.DesCraftItem.sItem.sAgeLevel < 10)
			AgingItemFaildNum = 5; //¶ÍÔì10
		break;
	case 4:
		if (sAging_Recv.DesCraftItem.sItem.sAgeLevel < 15)
			AgingItemFaildNum = 6; //¶ÍÔì15
		break;
	case 5:
		if (sAging_Recv.DesCraftItem.sItem.sAgeLevel < 20)
			AgingItemFaildNum = 7; //¶ÍÔì20
		break;
	}
	//ÎïÆ·±¬ÁË
	if (AgingItemFaildNum == 0)
	{
		sAging_Recv.Result = FALSE;
		return FALSE;
	}
	// ½µµÍ¶ÍÔìµÈ¼¶
	switch (AgingItemFaildNum)
	{
	case 1:
		sinAgingItemInit(&pItem->sItem);
		break;
	case 2:
		for (int k = 0; k < 2; k++)
			sinAgingItemInit(&pItem->sItem);
		break;
		// ¶ÍÔì+ 10
	case 5:
	{
		int i = 10 - sAging_Recv.DesCraftItem.sItem.sAgeLevel;

		if (i > 0)
		{
			for (int k = 0; k < i; k++)
				sinSetAgingItemIncreState(&sAging_Recv.DesCraftItem.sItem);
		}
	}
		
		break;
		// ¶ÍÔì+ 15
	case 6:
	{
		int i = 15 - sAging_Recv.DesCraftItem.sItem.sAgeLevel;

		if (i > 0)
		{
			for (int k = 0; k < i; k++)
				sinSetAgingItemIncreState(&sAging_Recv.DesCraftItem.sItem);
		}
	}
		break;
		// ¶ÍÔì + 20
	case 7:
	{
		int i = 20 - sAging_Recv.DesCraftItem.sItem.sAgeLevel;

		if (i > 0)
		{
			for (int k = 0; k < i; k++)
				sinSetAgingItemIncreState(&sAging_Recv.DesCraftItem.sItem);
		}
	}
		break;
	}
	if (AgingItemFaildNum >= 5)
	{
		pItem->sItem.bMaturing = 0;	//¶ÍÔì×´Ì¬
		pItem->sItem.sMatureBar.sMin = 0;
		pItem->sItem.eCraftType = ITEMCRAFTTYPE_Aging;
		memcpy(&sAging_Recv.DesCraftItem, pItem, sizeof(ItemData));
		ReformMixItem(&sAging_Recv.DesCraftItem.sItem);
		sAging_Recv.Result = AgingItemFaildNum;
		return TRUE;
	}

	//¹¥»÷±ØÉ±
	if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinWC1 ||
		(pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinWS2 ||
		(pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinWP1 ||
		(pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinWD1)
	{
		pItem->sItem.sMatureBar.sMax = AgingLevelCritical[pItem->sItem.sAgeLevel];
		if (AgingItemFaildNum <= 2)
			pItem->sItem.sMatureBar.sMin = pItem->sItem.sMatureBar.sMax / 2;
	}
	//¹¥»÷
	if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinWA1 ||
		(pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinWH1 ||
		(pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinWM1 ||
		(pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinWS1 ||
		(pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinWT1 ||
		(pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinWN1)
	{
		pItem->sItem.sMatureBar.sMax = AgingLevelAttack[pItem->sItem.sAgeLevel];
		if (AgingItemFaildNum <= 2)
			pItem->sItem.sMatureBar.sMin = pItem->sItem.sMatureBar.sMax / 2;
	}
	//¸ñµ²
	if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinDS1)
	{
		pItem->sItem.sMatureBar.sMax = AgingLevelBlock[pItem->sItem.sAgeLevel];
		if (AgingItemFaildNum <= 2)
			pItem->sItem.sMatureBar.sMin = pItem->sItem.sMatureBar.sMax / 2;

	}
	//·ÀÓù
	if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinDA1 ||
		(pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinDA2 ||
		(pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinOM1 ||
		(pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinDB1 ||
		(pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinDG1 ||
		(pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinOA2)
	{
		pItem->sItem.sMatureBar.sMax = AgingLevelHit[pItem->sItem.sAgeLevel];
		if (AgingItemFaildNum <= 2)
			pItem->sItem.sMatureBar.sMin = pItem->sItem.sMatureBar.sMax / 2;

	}
	if (pItem->sBaseItemID.ToInt() == (sinOR2 | sin01))
		pItem->sItem.sMatureBar.sMax = 60 * 20;

	pItem->sItem.bMaturing = 1;	//¶ÍÔì×´Ì¬
	pItem->sItem.eCraftType = ITEMCRAFTTYPE_Aging;
	if (AgingItemFaildNum >= 3)
		pItem->sItem.sMatureBar.sMin = 0;

	memcpy(&sAging_Recv.DesCraftItem, pItem, sizeof(ItemData));
	ReformMixItem(&sAging_Recv.DesCraftItem.sItem);
	sAging_Recv.Result = AgingItemFaildNum;

#endif

	return TRUE;
}

int cAGING::CheckItem(ItemData *pItem)
{
	int k = 0;
	int SheltomCnt = 0;
	if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinOS1)
		AgingSheltomCnt2++;
	else
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 3; j++)
				AgingLevelSheltomIndex[i][j] = AgingLevelSheltom[pItem->sItem.sAgeLevel][k++];
		}

	}
	if (AgingSheltomCnt2)
	{
		if (sAgingItem.AgingItem[0].bValid)
		{
			for (int h = 0; h < 12; h++)
			{
				if (AgingLevelSheltom[sAgingItem.AgingItem[0].sItem.sAgeLevel][h])
					SheltomCnt++;
			}

		}
		if (AgingSheltomCnt2 == SheltomCnt)
			AgingCheckSheltomFlag = 1;
		else
			AgingCheckSheltomFlag = 0;

	}

	return FALSE;
}

int CheckCraftMoney = 0;


int cCRAFTITEM::sinRecvCraftItem(sCRAFTITEM_SERVER *pCraftItem_Server)
{
	memcpy(&sCraftItem_Recv, pCraftItem_Server, sizeof(sCRAFTITEM_SERVER));

	return TRUE;
}
int cAGING::sinRecvAgingItem(sCRAFTITEM_SERVER *pCraftItem_Server)
{
	memcpy(&sAging_Recv, pCraftItem_Server, sizeof(sCRAFTITEM_SERVER));

	return TRUE;
}
int CopyMixItemCheckDelete(ItemData *pItem)
{
	return TRUE;
}

int sinMakeItemCheck()
{
	int ResultCount = 0;
	int ResultCountCheck = 0;
	DWORD TempCODE[15] = { 0, };
	int  i = 0;

	for (i = 0; i < MAX_MAKEITEM_INFO; i++)
	{
		for (int p = 0; p < 15; p++)
		{
			if (sAgingItem.AgingItem[p].bValid)
				TempCODE[p] = sAgingItem.AgingItem[p].sBaseItemID.ToInt();
		}

		for (int j = 0; j < 15; j++)
		{
			if (sMakeItem_Info[i].CODE[j])
			{
				ResultCount++;
				for (int k = 0; k < 15; k++)
				{
					if (sAgingItem.AgingItem[k].bValid && TempCODE[k])
					{
						if (TempCODE[k] == sMakeItem_Info[i].CODE[j])
						{
							ResultCountCheck++;
							TempCODE[k] = -1;
						}
					}
				}
			}
		}
		if (ResultCount && ResultCountCheck && (ResultCount == ResultCountCheck))
		{
			AgingCheckSheltomFlag = 1;
			return TRUE;
		}
		else
			AgingCheckSheltomFlag = 0;
		ResultCount = 0;
		ResultCountCheck = 0;
	}

	return TRUE;
}

int sinPosBoxNpc()
{
	
	return TRUE;
}

int	cMIXTURERESET::sinRecvMixtureItemReset(sMIXTURE_RESET_ITEM_SERVER *pMixtureResetItem)
{
	memcpy(&sMixtureReset_Recv, pMixtureResetItem, sizeof(sMIXTURE_RESET_ITEM_SERVER));

	return TRUE;
}
int cMIXTURERESET::ResetItem(sMIXTURE_RESET_ITEM_SERVER *pResetItem)
{
	int Result = FALSE;

	switch (pResetItem->DesMixtureResetItem.sItem.eCraftType)
	{
	case ITEMCRAFTTYPE_Mixing:
		int ItemCraftCode;
		ItemCraftCode = pResetItem->DesMixtureResetItem.sItem.ItemCraftCode;

		if (ItemCraftCode >= 0 && ItemCraftCode < MAX_CRAFTITEM_INFO)
		{
			for (int k = 0; k < 9; k++)
			{
				if (pResetItem->DesMixtureResetItem.sItem.eMixEffect & sCraftItem_Info[ItemCraftCode].PlusElementCode[k])
				{
					switch (sCraftItem_Info[ItemCraftCode].PlusElementCode[k])
					{
					case SIN_ADD_FIRE:
						pResetItem->DesMixtureResetItem.sItem.saElementalDef[sITEMINFO_FIRE] -= (int)sCraftItem_Info[ItemCraftCode].AddElement[k];
						if (pResetItem->DesMixtureResetItem.sItem.saElementalDef[sITEMINFO_FIRE] < 0)
							pResetItem->DesMixtureResetItem.sItem.saElementalDef[sITEMINFO_FIRE] = 0;
						break;
					case SIN_ADD_ICE:
						pResetItem->DesMixtureResetItem.sItem.saElementalDef[SIN_ADD_ICE] -= (int)sCraftItem_Info[ItemCraftCode].AddElement[k];
						if (pResetItem->DesMixtureResetItem.sItem.saElementalDef[SIN_ADD_ICE] < 0)
							pResetItem->DesMixtureResetItem.sItem.saElementalDef[SIN_ADD_ICE] = 0;
						break;
					case SIN_ADD_LIGHTNING:
						pResetItem->DesMixtureResetItem.sItem.saElementalDef[SIN_ADD_LIGHTNING] -= (int)sCraftItem_Info[ItemCraftCode].AddElement[k];
						if (pResetItem->DesMixtureResetItem.sItem.saElementalDef[SIN_ADD_LIGHTNING] < 0)
							pResetItem->DesMixtureResetItem.sItem.saElementalDef[SIN_ADD_LIGHTNING] = 0;
						break;
					case SIN_ADD_POISON:
						pResetItem->DesMixtureResetItem.sItem.saElementalDef[SIN_ADD_POISON] -= (int)sCraftItem_Info[ItemCraftCode].AddElement[k];
						if (pResetItem->DesMixtureResetItem.sItem.saElementalDef[SIN_ADD_POISON] < 0)
							pResetItem->DesMixtureResetItem.sItem.saElementalDef[SIN_ADD_POISON] = 0;
						break;
					case SIN_ADD_BIO:
						pResetItem->DesMixtureResetItem.sItem.saElementalDef[SIN_ADD_BIO] -= (int)sCraftItem_Info[ItemCraftCode].AddElement[k];
						if (pResetItem->DesMixtureResetItem.sItem.saElementalDef[SIN_ADD_BIO] < 0)
							pResetItem->DesMixtureResetItem.sItem.saElementalDef[SIN_ADD_BIO] = 0;
						break;
					case SIN_ADD_CRITICAL:
						if (sCraftItem_Info[ItemCraftCode].ElementKind[k] == SIN_ADD_NUM)
							pResetItem->DesMixtureResetItem.sItem.iCritical -= (int)sCraftItem_Info[ItemCraftCode].AddElement[k];
						else
							pResetItem->DesMixtureResetItem.sItem.iCritical = (100 * pResetItem->DesMixtureResetItem.sItem.iCritical) / (100 + (int)sCraftItem_Info[ItemCraftCode].AddElement[k]);

						if (pResetItem->DesMixtureResetItem.sItem.iCritical < 0)
							pResetItem->DesMixtureResetItem.sItem.iCritical = 0;
						break;
					case SIN_ADD_ATTACK_RATE:
						if (sCraftItem_Info[ItemCraftCode].ElementKind[k] == SIN_ADD_NUM)
							pResetItem->DesMixtureResetItem.sItem.iAttackRating -= (int)sCraftItem_Info[ItemCraftCode].AddElement[k];
						else
							pResetItem->DesMixtureResetItem.sItem.iAttackRating = (100 * pResetItem->DesMixtureResetItem.sItem.iAttackRating) / (100 + (int)sCraftItem_Info[ItemCraftCode].AddElement[k]);
						if (pResetItem->DesMixtureResetItem.sItem.iAttackRating < 0)
							pResetItem->DesMixtureResetItem.sItem.iAttackRating = 0;
						break;
					case SIN_ADD_DAMAGE_MIN:
						if (sCraftItem_Info[ItemCraftCode].ElementKind[k] == SIN_ADD_NUM)
							pResetItem->DesMixtureResetItem.sItem.sDamage.sMin -= (short)sCraftItem_Info[ItemCraftCode].AddElement[k];
						else
							pResetItem->DesMixtureResetItem.sItem.sDamage.sMin = (100 * pResetItem->DesMixtureResetItem.sItem.sDamage.sMin) / (100 + (short)sCraftItem_Info[ItemCraftCode].AddElement[k]);
						if (pResetItem->DesMixtureResetItem.sItem.sDamage.sMin < 0)
							pResetItem->DesMixtureResetItem.sItem.sDamage.sMin = 1;
						break;
					case SIN_ADD_DAMAGE_MAX:
						if (sCraftItem_Info[ItemCraftCode].ElementKind[k] == SIN_ADD_NUM)
							pResetItem->DesMixtureResetItem.sItem.sDamage.sMax -= (short)sCraftItem_Info[ItemCraftCode].AddElement[k];
						else
							pResetItem->DesMixtureResetItem.sItem.sDamage.sMax = (100 * pResetItem->DesMixtureResetItem.sItem.sDamage.sMax) / (100 + (short)sCraftItem_Info[ItemCraftCode].AddElement[k]);
						if (pResetItem->DesMixtureResetItem.sItem.sDamage.sMax < 0)
							pResetItem->DesMixtureResetItem.sItem.sDamage.sMax = 1;
						break;
					case SIN_ADD_ATTACK_SPEED:
						if (sCraftItem_Info[ItemCraftCode].ElementKind[k] == SIN_ADD_NUM)
							pResetItem->DesMixtureResetItem.sItem.iAttackSpeed -= (int)sCraftItem_Info[ItemCraftCode].AddElement[k];
						else
							pResetItem->DesMixtureResetItem.sItem.iAttackSpeed = (100 * pResetItem->DesMixtureResetItem.sItem.iAttackSpeed) / (100 + (int)sCraftItem_Info[ItemCraftCode].AddElement[k]);
						if (pResetItem->DesMixtureResetItem.sItem.iAttackSpeed < 0)
							pResetItem->DesMixtureResetItem.sItem.iAttackSpeed = 0;
						break;
					case SIN_ADD_ABSORB:
						if (sCraftItem_Info[ItemCraftCode].ElementKind[k] == SIN_ADD_NUM)
							pResetItem->DesMixtureResetItem.sItem.fAbsorbRating -= sCraftItem_Info[ItemCraftCode].AddElement[k];
						else
							pResetItem->DesMixtureResetItem.sItem.fAbsorbRating = (100 * pResetItem->DesMixtureResetItem.sItem.fAbsorbRating) / (100 + sCraftItem_Info[ItemCraftCode].AddElement[k]);
						if (pResetItem->DesMixtureResetItem.sItem.fAbsorbRating < 0)
							pResetItem->DesMixtureResetItem.sItem.fAbsorbRating = 0;
						break;
					case SIN_ADD_DEFENCE:
						if (sCraftItem_Info[ItemCraftCode].ElementKind[k] == SIN_ADD_NUM)
							pResetItem->DesMixtureResetItem.sItem.iDefenseRating -= (int)sCraftItem_Info[ItemCraftCode].AddElement[k];
						else
							pResetItem->DesMixtureResetItem.sItem.iDefenseRating = (100 * pResetItem->DesMixtureResetItem.sItem.iDefenseRating) / (100 + (int)sCraftItem_Info[ItemCraftCode].AddElement[k]);
						if (pResetItem->DesMixtureResetItem.sItem.iDefenseRating < 0)
							pResetItem->DesMixtureResetItem.sItem.iDefenseRating = 0;
						break;
					case SIN_ADD_BLOCK_RATE:
						if (sCraftItem_Info[ItemCraftCode].ElementKind[k] == SIN_ADD_NUM)
							pResetItem->DesMixtureResetItem.sItem.fBlockRating -= sCraftItem_Info[ItemCraftCode].AddElement[k];
						else
							pResetItem->DesMixtureResetItem.sItem.fBlockRating = (100 * pResetItem->DesMixtureResetItem.sItem.fBlockRating) / (100 + sCraftItem_Info[ItemCraftCode].AddElement[k]);
						if (pResetItem->DesMixtureResetItem.sItem.fBlockRating < 0)
							pResetItem->DesMixtureResetItem.sItem.fBlockRating = 0;
						break;
					case SIN_ADD_MOVE_SPEED:
						if (sCraftItem_Info[ItemCraftCode].ElementKind[k] == SIN_ADD_NUM)
							pResetItem->DesMixtureResetItem.sItem.fMovementSpeed -= sCraftItem_Info[ItemCraftCode].AddElement[k];
						else
							pResetItem->DesMixtureResetItem.sItem.fMovementSpeed = (100 * pResetItem->DesMixtureResetItem.sItem.fMovementSpeed) / (100 + sCraftItem_Info[ItemCraftCode].AddElement[k]);
						if (pResetItem->DesMixtureResetItem.sItem.fMovementSpeed < 0)
							pResetItem->DesMixtureResetItem.sItem.fMovementSpeed = 0;
						break;
					case SIN_ADD_LIFE:
						if (sCraftItem_Info[ItemCraftCode].ElementKind[k] == SIN_ADD_NUM)
							pResetItem->DesMixtureResetItem.sItem.fAddHP -= sCraftItem_Info[ItemCraftCode].AddElement[k];
						else
							pResetItem->DesMixtureResetItem.sItem.fAddHP = (100 * pResetItem->DesMixtureResetItem.sItem.fAddHP) / (100 + sCraftItem_Info[ItemCraftCode].AddElement[k]);
						if (pResetItem->DesMixtureResetItem.sItem.fAddHP < 0)
							pResetItem->DesMixtureResetItem.sItem.fAddHP = 0;
						break;
					case SIN_ADD_MANA:
						if (sCraftItem_Info[ItemCraftCode].ElementKind[k] == SIN_ADD_NUM)
							pResetItem->DesMixtureResetItem.sItem.fAddMP -= sCraftItem_Info[ItemCraftCode].AddElement[k];
						else
							pResetItem->DesMixtureResetItem.sItem.fAddMP = (100 * pResetItem->DesMixtureResetItem.sItem.fAddMP) / (100 + sCraftItem_Info[ItemCraftCode].AddElement[k]);
						if (pResetItem->DesMixtureResetItem.sItem.fAddMP < 0)
							pResetItem->DesMixtureResetItem.sItem.fAddMP = 0;
						break;
					case SIN_ADD_STAMINA:
						if (sCraftItem_Info[ItemCraftCode].ElementKind[k] == SIN_ADD_NUM)
							pResetItem->DesMixtureResetItem.sItem.fAddSP -= sCraftItem_Info[ItemCraftCode].AddElement[k];
						else
							pResetItem->DesMixtureResetItem.sItem.fAddSP = (100 * pResetItem->DesMixtureResetItem.sItem.fAddSP) / (100 + sCraftItem_Info[ItemCraftCode].AddElement[k]);
						if (pResetItem->DesMixtureResetItem.sItem.fAddSP < 0)
							pResetItem->DesMixtureResetItem.sItem.fAddSP = 0;
						break;
					case SIN_ADD_LIFEREGEN:
						if (sCraftItem_Info[ItemCraftCode].ElementKind[k] == SIN_ADD_NUM)
							pResetItem->DesMixtureResetItem.sItem.fHPRegen -= sCraftItem_Info[ItemCraftCode].AddElement[k];
						else
							pResetItem->DesMixtureResetItem.sItem.fHPRegen = (100 * pResetItem->DesMixtureResetItem.sItem.fHPRegen) / (100 + sCraftItem_Info[ItemCraftCode].AddElement[k]);
						if (pResetItem->DesMixtureResetItem.sItem.fHPRegen < 0)
							pResetItem->DesMixtureResetItem.sItem.fHPRegen = 0;
						break;
					case SIN_ADD_MANAREGEN:
						if (sCraftItem_Info[ItemCraftCode].ElementKind[k] == SIN_ADD_NUM)
							pResetItem->DesMixtureResetItem.sItem.fMPRegen -= sCraftItem_Info[ItemCraftCode].AddElement[k];
						else
							pResetItem->DesMixtureResetItem.sItem.fMPRegen = (100 * pResetItem->DesMixtureResetItem.sItem.fMPRegen) / (100 + sCraftItem_Info[ItemCraftCode].AddElement[k]);
						if (pResetItem->DesMixtureResetItem.sItem.fMPRegen < 0)
							pResetItem->DesMixtureResetItem.sItem.fMPRegen = 0;
						break;
					case SIN_ADD_STAMINAREGEN:
						if (sCraftItem_Info[ItemCraftCode].ElementKind[k] == SIN_ADD_NUM)
							pResetItem->DesMixtureResetItem.sItem.fSPRegen -= sCraftItem_Info[ItemCraftCode].AddElement[k];
						else
							pResetItem->DesMixtureResetItem.sItem.fSPRegen = (100 * pResetItem->DesMixtureResetItem.sItem.fSPRegen) / (100 + sCraftItem_Info[ItemCraftCode].AddElement[k]);
						if (pResetItem->DesMixtureResetItem.sItem.fSPRegen < 0)
							pResetItem->DesMixtureResetItem.sItem.fSPRegen = 0;
						break;
					}
				}
			}
			pResetItem->DesMixtureResetItem.sItem.eCraftType = ITEMCRAFTTYPE_None;
			pResetItem->DesMixtureResetItem.sItem.eMixEffect = 0;
			pResetItem->DesMixtureResetItem.sItem.sAgeLevel = 0;
			pResetItem->DesMixtureResetItem.sItem.bMaturing = 0;
			pResetItem->DesMixtureResetItem.sItem.ItemCraftCode = 0;
			pResetItem->DesMixtureResetItem.sItem.ItemElement = 0;
			ReformItem(&pResetItem->DesMixtureResetItem.sItem);
			Result = TRUE;
		}
		break;
	case ITEMCRAFTTYPE_Aging:
		int ItemAginNum;
		ItemAginNum = pResetItem->DesMixtureResetItem.sItem.sAgeLevel;
		for (int i = 0; i < ItemAginNum; i++)
			sinAgingItemInit(&pResetItem->DesMixtureResetItem.sItem);
		pResetItem->DesMixtureResetItem.sItem.eCraftType = ITEMCRAFTTYPE_None;
		pResetItem->DesMixtureResetItem.sItem.sAgeLevel = 0;
		pResetItem->DesMixtureResetItem.sItem.bMaturing = 0;
		pResetItem->DesMixtureResetItem.sItem.sMatureBar.sMin = 0;
		pResetItem->DesMixtureResetItem.sItem.sMatureBar.sMax = 0;
		pResetItem->DesMixtureResetItem.sItem.ItemElement = 0;
		ReformItem(&pResetItem->DesMixtureResetItem.sItem);
		Result = TRUE;
		break;
	}

	return Result;
}





int CSmeltingItem::sinRecvSmeltingItem(sSMELTINGITEM_SERVER *pSmeltingItem_Server)
{
	memcpy(&sSmeltingItem_Recv, pSmeltingItem_Server, sizeof(sSMELTINGITEM_SERVER));
	return TRUE;
}

// pluto ±¤¼®, ¼öÁ¤ Á¦·Ã ºñ¿ë
int CSmeltingItem::CheckSmeltingPrice()
{
	int SmeltingPriceIndexOre = 25000;

	int SmeltingPriceIndexCrystal = 50000;

	m_SmeltingPrice = 0;
	if (S_smeltingItem.SmeltingItem[0].bValid)
	{
		if ((S_smeltingItem.SmeltingItem[0].sItem.sItemID.ToItemType()) == sinPR1)
		{
			m_SmeltingPrice = SmeltingPriceIndexOre;
			ForceItemPrice2 = m_SmeltingPrice;
			return TRUE;
		}
		else if ((S_smeltingItem.SmeltingItem[0].sItem.sItemID.ToItemType()) == sinPR2)
		{

			m_SmeltingPrice = SmeltingPriceIndexCrystal;
			ForceItemPrice2 = m_SmeltingPrice;
			return TRUE;
		}
	}
	return TRUE;
}

int CManufacture::sinRecvManufactureItem(SManufactureItem_Server *pManufactureItem_Server)
{
	memcpy(&sManufactureItem_Recv, pManufactureItem_Server, sizeof(SManufactureItem_Server));
	return TRUE;
}

void CManufacture::RuneIndexInit()
{
	for (int i = 0; i < MAX_RECIPE_KIND; i++)
		ZeroMemory(&sManufacture_Rune[i], sizeof(SManufacture_Rune));

	sManufacture_Rune[0].RecipeCode = EXTREME_RECIPE;
	sManufacture_Rune[0].NeedRuneIndex[0] = 1;
	sManufacture_Rune[0].NeedRuneIndex[1] = 2;
	sManufacture_Rune[0].NeedRuneIndex[2] = 3;

	sManufacture_Rune[1].RecipeCode = ANCIENT_RECIPE;
	sManufacture_Rune[1].NeedRuneIndex[0] = 2;
	sManufacture_Rune[1].NeedRuneIndex[1] = 3;
	sManufacture_Rune[1].NeedRuneIndex[2] = 4;

	sManufacture_Rune[2].RecipeCode = MINOTAUR_RECIPE;
	sManufacture_Rune[2].NeedRuneIndex[0] = 3;
	sManufacture_Rune[2].NeedRuneIndex[1] = 4;
	sManufacture_Rune[2].NeedRuneIndex[2] = 5;

	sManufacture_Rune[3].RecipeCode = DOOM_RECIPE;
	sManufacture_Rune[3].NeedRuneIndex[0] = 3;
	sManufacture_Rune[3].NeedRuneIndex[1] = 4;
	sManufacture_Rune[3].NeedRuneIndex[2] = 5;

	sManufacture_Rune[4].RecipeCode = SALAMANDER_RECIPE;
	sManufacture_Rune[4].NeedRuneIndex[0] = 3;
	sManufacture_Rune[4].NeedRuneIndex[1] = 4;
	sManufacture_Rune[4].NeedRuneIndex[2] = 5;

	sManufacture_Rune[5].RecipeCode = WYVERN_RECIPE;
	sManufacture_Rune[5].NeedRuneIndex[0] = 3;
	sManufacture_Rune[5].NeedRuneIndex[1] = 4;
	sManufacture_Rune[5].NeedRuneIndex[2] = 5;

	sManufacture_Rune[6].RecipeCode = PHOENIX_RECIPE;
	sManufacture_Rune[6].NeedRuneIndex[0] = 4;
	sManufacture_Rune[6].NeedRuneIndex[1] = 5;
	sManufacture_Rune[6].NeedRuneIndex[2] = 6;

	sManufacture_Rune[7].RecipeCode = FRENZY_RECIPE;
	sManufacture_Rune[7].NeedRuneIndex[0] = 5;
	sManufacture_Rune[7].NeedRuneIndex[1] = 6;
	sManufacture_Rune[7].NeedRuneIndex[2] = 7;

	sManufacture_Rune[8].RecipeCode = HEAVENS_RECIPE;
	sManufacture_Rune[8].NeedRuneIndex[0] = 6;
	sManufacture_Rune[8].NeedRuneIndex[1] = 7;
	sManufacture_Rune[8].NeedRuneIndex[2] = 8;

	sManufacture_Rune[9].RecipeCode = SNOW_RECIPE;
	sManufacture_Rune[9].NeedRuneIndex[0] = 9;
	sManufacture_Rune[9].NeedRuneIndex[1] = 10;
	sManufacture_Rune[9].NeedRuneIndex[2] = 11;

	sManufacture_Rune[10].RecipeCode = MEMORY_RECIPE;
	sManufacture_Rune[10].NeedRuneIndex[0] = 12;
	sManufacture_Rune[10].NeedRuneIndex[1] = 13;
	sManufacture_Rune[10].NeedRuneIndex[2] = 14;
}
int CManufacture::GetRecipeIndex(DWORD Code)
{
	int RecipeIndex = -1;

	switch (Code)
	{
	case sin01:
		RecipeIndex = EXTREME_RECIPE;
		break;
	case sin02:
		RecipeIndex = ANCIENT_RECIPE;
		break;
	case sin03:
		RecipeIndex = MINOTAUR_RECIPE;
		break;
	case sin04:
		RecipeIndex = DOOM_RECIPE;
		break;
	case sin05:
		RecipeIndex = SALAMANDER_RECIPE;
		break;
	case sin06:
		RecipeIndex = WYVERN_RECIPE;
		break;
	case sin07:
		RecipeIndex = PHOENIX_RECIPE;
		break;
	case sin08:
		RecipeIndex = FRENZY_RECIPE;
		break;
	case sin09:
		RecipeIndex = HEAVENS_RECIPE;
		break;
	case sin10:
		RecipeIndex = SNOW_RECIPE;
		break;

	case sin11:
		RecipeIndex = MEMORY_RECIPE;
		break;
	}
	return RecipeIndex;
}

int CSmeltingItem::GetSheltomIndex(DWORD SmeltingItemCode)
{
	DWORD SmeltingItemAray[] = { (sinPR1 | sin01), (sinPR1 | sin02), (sinPR1 | sin03), (sinPR1 | sin04), (sinPR1 | sin05), (sinPR1 | sin06), (sinPR1 | sin07), (sinPR1 | sin08),
								 (sinPR2 | sin01), (sinPR2 | sin02), (sinPR2 | sin03), (sinPR2 | sin04), (sinPR2 | sin05), (sinPR2 | sin06), (sinPR2 | sin07), (sinPR2 | sin08),
								 (sinPR2 | sin09), (sinPR2 | sin10), (sinPR2 | sin11), (sinPR2 | sin12), (sinPR2 | sin13), (sinPR2 | sin14) };
	int SheltomAray[] = { 6, 7, 8, 9, 10, 11, 12, 13,
						  7, 8, 9, 10, 11, 12, 13, 14,
							3, 4, 5, 3, 4, 5 }; // ±¤¼®ÀÌ³ª ¼öÁ¤ ¹øÈ£
	for (int i = 0; i < 22; i++)
	{
		if (SmeltingItemCode == SmeltingItemAray[i])
		{
			return SheltomAray[i];
		}
	}
	return FALSE;
}

// pluto Á¦ÀÛµÉ ¾ÆÀÌÅÛ ÄÚµå. ¹«°Ô °Ë»ç ÇÒ·Á°í // Àåº° - Á¦ÀÛ
SManufacture_ResultItemInfo CManufacture::ManufactureCheckItem(ItemData *pItemCode, CharacterData *charInfo) // Àåº° - ´ëÀåÀåÀÌÀÇ È¥
{
	int RuneCnt = 0;
	SManufacture_ResultItemInfo Result;
	memset(&Result, 0, sizeof(SManufacture_ResultItemInfo));
	DWORD Arm_Armor_Code[MAX_RECIPE_KIND] = { sin01, sin02, sin03, sin04, sin05, sin06, sin07, sin08, sin09, sin10, sin11 }; // ·¹½ÃÇÇ Á¾·ù // Àåº° - ´ëÀåÀåÀÌÀÇ È¥
	DWORD CheckRuneCode[MAX_HANDMADEITEM][8][3] = { {	{ (sinPR3 | sin01), (sinPR3 | sin02), (sinPR3 | sin03) },  // ·é Á¶ÇÕ½ÄÀÌ´Ù
										{ (sinPR3 | sin01), (sinPR3 | sin02), (sinPR4 | sin03) },
										{ (sinPR3 | sin01), (sinPR4 | sin02), (sinPR3 | sin03) },
										{ (sinPR3 | sin01), (sinPR4 | sin02), (sinPR4 | sin03) },
										{ (sinPR4 | sin01), (sinPR3 | sin02), (sinPR3 | sin03) },
										{ (sinPR4 | sin01), (sinPR3 | sin02), (sinPR4 | sin03) },
										{ (sinPR4 | sin01), (sinPR4 | sin02), (sinPR3 | sin03) },
										{ (sinPR4 | sin01), (sinPR4 | sin02), (sinPR4 | sin03) } },
		////////////////////////////////////////////////////////////////////////////////////////////	ÀØÇôÁø Á¦ÀÛ¼­
	 {  { (sinPR3 | sin02), (sinPR3 | sin03), (sinPR3 | sin04) },
		{ (sinPR3 | sin02), (sinPR3 | sin03), (sinPR4 | sin04) },
		{ (sinPR3 | sin02), (sinPR4 | sin03), (sinPR3 | sin04) },
		{ (sinPR3 | sin02), (sinPR4 | sin03), (sinPR4 | sin04) },
		{ (sinPR4 | sin02), (sinPR3 | sin03), (sinPR3 | sin04) },
		{ (sinPR4 | sin02), (sinPR3 | sin03), (sinPR4 | sin04) },
		{ (sinPR4 | sin02), (sinPR4 | sin03), (sinPR3 | sin04) },
		{ (sinPR4 | sin02), (sinPR4 | sin03), (sinPR4 | sin04) } },
		////////////////////////////////////////////////////////////////////////////////////////////	°í´ëÀÇ Á¦ÀÛ¼­
	 {  { (sinPR3 | sin03), (sinPR3 | sin04), (sinPR3 | sin05) },
		{ (sinPR3 | sin03), (sinPR3 | sin04), (sinPR4 | sin05) },
		{ (sinPR3 | sin03), (sinPR4 | sin04), (sinPR3 | sin05) },
		{ (sinPR3 | sin03), (sinPR4 | sin04), (sinPR4 | sin05) },
		{ (sinPR4 | sin03), (sinPR3 | sin04), (sinPR3 | sin05) },
		{ (sinPR4 | sin03), (sinPR3 | sin04), (sinPR4 | sin05) },
		{ (sinPR4 | sin03), (sinPR4 | sin04), (sinPR3 | sin05) },
		{ (sinPR4 | sin03), (sinPR4 | sin04), (sinPR4 | sin05) } },
		////////////////////////////////////////////////////////////////////////////////////////////	´ëÁöÀÇ Á¦ÀÛ¼­
	 {  { (sinPR3 | sin03), (sinPR3 | sin04), (sinPR3 | sin05) },
		{ (sinPR3 | sin03), (sinPR3 | sin04), (sinPR4 | sin05) },
		{ (sinPR3 | sin03), (sinPR4 | sin04), (sinPR3 | sin05) },
		{ (sinPR3 | sin03), (sinPR4 | sin04), (sinPR4 | sin05) },
		{ (sinPR4 | sin03), (sinPR3 | sin04), (sinPR3 | sin05) },
		{ (sinPR4 | sin03), (sinPR3 | sin04), (sinPR4 | sin05) },
		{ (sinPR4 | sin03), (sinPR4 | sin04), (sinPR3 | sin05) },
		{ (sinPR4 | sin03), (sinPR4 | sin04), (sinPR4 | sin05) } },
		////////////////////////////////////////////////////////////////////////////////////////////	¾îµÒÀÇ Á¦ÀÛ¼­
	 {	{ (sinPR3 | sin03), (sinPR3 | sin04), (sinPR3 | sin05) },
		{ (sinPR3 | sin03), (sinPR3 | sin04), (sinPR4 | sin05) },
		{ (sinPR3 | sin03), (sinPR4 | sin04), (sinPR3 | sin05) },
		{ (sinPR3 | sin03), (sinPR4 | sin04), (sinPR4 | sin05) },
		{ (sinPR4 | sin03), (sinPR3 | sin04), (sinPR3 | sin05) },
		{ (sinPR4 | sin03), (sinPR3 | sin04), (sinPR4 | sin05) },
		{ (sinPR4 | sin03), (sinPR4 | sin04), (sinPR3 | sin05) },
		{ (sinPR4 | sin03), (sinPR4 | sin04), (sinPR4 | sin05) } },
		////////////////////////////////////////////////////////////////////////////////////////////	È­¿°ÀÇ Á¦ÀÛ¼­
	 {  { (sinPR3 | sin03), (sinPR3 | sin04), (sinPR3 | sin05) },
		{ (sinPR3 | sin03), (sinPR3 | sin04), (sinPR4 | sin05) },
		{ (sinPR3 | sin03), (sinPR4 | sin04), (sinPR3 | sin05) },
		{ (sinPR3 | sin03), (sinPR4 | sin04), (sinPR4 | sin05) },
		{ (sinPR4 | sin03), (sinPR3 | sin04), (sinPR3 | sin05) },
		{ (sinPR4 | sin03), (sinPR3 | sin04), (sinPR4 | sin05) },
		{ (sinPR4 | sin03), (sinPR4 | sin04), (sinPR3 | sin05) },
		{ (sinPR4 | sin03), (sinPR4 | sin04), (sinPR4 | sin05) } },
		////////////////////////////////////////////////////////////////////////////////////////////	¹Ù¶÷ÀÇ Á¦ÀÛ¼­
	 {  { (sinPR3 | sin04), (sinPR3 | sin05), (sinPR3 | sin06) },
		{ (sinPR3 | sin04), (sinPR3 | sin05), (sinPR4 | sin06) },
		{ (sinPR3 | sin04), (sinPR4 | sin05), (sinPR3 | sin06) },
		{ (sinPR3 | sin04), (sinPR4 | sin05), (sinPR4 | sin06) },
		{ (sinPR4 | sin04), (sinPR3 | sin05), (sinPR3 | sin06) },
		{ (sinPR4 | sin04), (sinPR3 | sin05), (sinPR4 | sin06) },
		{ (sinPR4 | sin04), (sinPR4 | sin05), (sinPR3 | sin06) },
		{ (sinPR4 | sin04), (sinPR4 | sin05), (sinPR4 | sin06) } },
		////////////////////////////////////////////////////////////////////////////////////////////	ÅÂ¾çÀÇ Á¦ÀÛ¼­
	 {  { (sinPR3 | sin05), (sinPR3 | sin06), (sinPR3 | sin07) },
		{ (sinPR3 | sin05), (sinPR3 | sin06), (sinPR4 | sin07) },
		{ (sinPR3 | sin05), (sinPR4 | sin06), (sinPR3 | sin07) },
		{ (sinPR3 | sin05), (sinPR4 | sin06), (sinPR4 | sin07) },
		{ (sinPR4 | sin05), (sinPR3 | sin06), (sinPR3 | sin07) },
		{ (sinPR4 | sin05), (sinPR3 | sin06), (sinPR4 | sin07) },
		{ (sinPR4 | sin05), (sinPR4 | sin06), (sinPR3 | sin07) },
		{ (sinPR4 | sin05), (sinPR4 | sin06), (sinPR4 | sin07) } },
		////////////////////////////////////////////////////////////////////////////////////////////	±¤Æ÷ÇÑ Á¦ÀÛ¼­
	 {  { (sinPR3 | sin06), (sinPR3 | sin07), (sinPR3 | sin08) },
		{ (sinPR3 | sin06), (sinPR3 | sin07), (sinPR4 | sin08) },
		{ (sinPR3 | sin06), (sinPR4 | sin07), (sinPR3 | sin08) },
		{ (sinPR3 | sin06), (sinPR4 | sin07), (sinPR4 | sin08) },
		{ (sinPR4 | sin06), (sinPR3 | sin07), (sinPR3 | sin08) },
		{ (sinPR4 | sin06), (sinPR3 | sin07), (sinPR4 | sin08) },
		{ (sinPR4 | sin06), (sinPR4 | sin07), (sinPR3 | sin08) },
		{ (sinPR4 | sin06), (sinPR4 | sin07), (sinPR4 | sin08) } },
		////////////////////////////////////////////////////////////////////////////////////////////	Ãµ»óÀÇ Á¦ÀÛ¼­

	 {  { (sinPR3 | sin09), (sinPR4 | sin10), (sinPR3 | sin11) },
		{ 0, 0, 0 },
		{ 0, 0, 0 },
		{ 0, 0, 0 },
		{ 0, 0, 0 },
		{ 0, 0, 0 },
		{ 0, 0, 0 },
		{ 0, 0, 0 } },
		////////////////////////////////////////////////////////////////////////////////////////////	Æ÷¼³ÀÇ Á¦ÀÛ¼­ //Àåº°

		{  { (sinPR3 | sin12), (sinPR3 | sin13), (sinPR3 | sin14) },
		{ 0, 0, 0 },
		{ 0, 0, 0 },
		{ 0, 0, 0 },
		{ 0, 0, 0 },
		{ 0, 0, 0 },
		{ 0, 0, 0 },
		{ 0, 0, 0 } },
		////////////////////////////////////////////////////////////////////////////////////////////	±â¾ïÀÇ Á¦ÀÛ¼­ // Àåº° - ´ëÀåÀåÀÌÀÇ È¥
	};

	// Àåº° - ´ëÀåÀåÀÌÀÇ È¥
	DWORD	dwItem = 0;

	// ÇÁ¸®½ºÆ¼½º ÀÏ °æ¿ì
	if (charInfo->iClass == CHARACTERCLASS_Priestess) dwItem = (sinDA2 | sin52);
	// ¸ÞÁö¼Ç ÀÏ °æ¿ì
	else if (charInfo->iClass == CHARACTERCLASS_Magician) dwItem = (sinDA2 | sin51);
	// ¾ÆÃ³, ¾ÆÆ²¶õÅ¸ ÀÏ °æ¿ì
	else if (charInfo->iClass == CHARACTERCLASS_Archer || charInfo->iClass == CHARACTERCLASS_Atalanta) dwItem = (sinDA1 | sin52);
	// ÆÄÀÌÅÍ, ÆÄÀÌÅ©¸Ç, ¸ÞÄ«´Ï¼Ç, ³ªÀÌÆ® ÀÏ °æ¿ì
	else dwItem = (sinDA1 | sin51);


	// Àåº° ¹è¿­ ¼ýÀÚ [a][b][c] a = ¹«±¸ or °©ÁÖ / b = ·¹½ÃÇÇ Á¾·ù / c = »ý¼ºµÉ ¾ÆÀÌÅÛ Á¾·ù(°íÁ¤)
	// ·¹½ÃÇÇ¿Í ·éÁ¶ÇÕ¿¡ ¸Â´Â ¹ß»ý ¾ÆÀÌÅÛ
	DWORD CreateItemCode[2][MAX_HANDMADEITEM][8] = { {	{ (sinWA1 | sin14), (sinWC1 | sin14), (sinWH1 | sin15), (sinWP1 | sin15), (sinWS1 | sin16), (sinWS2 | sin17), (sinWT1 | sin15), (sinWM1 | sin15) }, // ÀØÇôÁø ·¹½ÃÇÇ ¹«±¸
											{ (sinWA1 | sin15), (sinWC1 | sin15), (sinWH1 | sin16), (sinWP1 | sin16), (sinWS1 | sin17), (sinWS2 | sin18), (sinWT1 | sin16), (sinWM1 | sin16) }, // °í´ëÀÇ ·¹½ÃÇÇ ¹«±¸
											{ (sinWA1 | sin16), (sinWC1 | sin16), (sinWH1 | sin17), (sinWP1 | sin17), (sinWS1 | sin18), (sinWS2 | sin19), (sinWT1 | sin17), (sinWM1 | sin17) }, // ´ëÁöÀÇ ¹«±¸
											{ (sinWA1 | sin17), (sinWC1 | sin17), (sinWH1 | sin18), (sinWP1 | sin18), (sinWS1 | sin19), (sinWS2 | sin20), (sinWT1 | sin18), (sinWM1 | sin18) }, // ¾îµÒÀÇ ·¹½ÃÇÇ ¹«±¸
											{ (sinWA1 | sin18), (sinWC1 | sin18), (sinWH1 | sin19), (sinWP1 | sin19), (sinWS1 | sin20), (sinWS2 | sin21), (sinWT1 | sin19), (sinWM1 | sin19) }, // È­¿°ÀÇ ·¹½ÃÇÇ ¹«±¸
											{ (sinWA1 | sin19), (sinWC1 | sin19), (sinWH1 | sin20), (sinWP1 | sin20), (sinWS1 | sin21), (sinWS2 | sin22), (sinWT1 | sin20), (sinWM1 | sin20) }, // ¹Ù¶÷ÀÇ ·¹½ÃÇÇ ¹«±¸
											{ (sinWA1 | sin21), (sinWC1 | sin21), (sinWH1 | sin22), (sinWP1 | sin22), (sinWS1 | sin23), (sinWS2 | sin24), (sinWT1 | sin22), (sinWM1 | sin22) }, // ÅÂ¾çÀÇ ·¹½ÃÇÇ ¹«±¸
											{ (sinWA1 | sin22), (sinWC1 | sin22), (sinWH1 | sin23), (sinWP1 | sin23), (sinWS1 | sin24), (sinWS2 | sin25), (sinWT1 | sin23), (sinWM1 | sin23) }, // ±¤Æ÷ÇÑ ·¹½ÃÇÇ ¹«±¸
											{ 0, 0, 0, 0, 0, 0, 0, 0 } , // Ãµ»óÀÇ ·¹½ÃÇÇ ¹«±¸
											{ 0, 0, 0, 0, 0, 0, 0, 0 } , // Æ÷¼³ÀÇ ·¹½ÃÇÇ // Àåº°
											{ 0, 0, 0, 0, 0, 0, 0, 0 } }, // ±â¾ïÀÇ ·¹½ÃÇÇ // Àåº° - ´ëÀåÀåÀÌÀÇ È¥
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
										{	{ (sinDA1 | sin16), (sinDA2 | sin16), (sinDS1 | sin14), (sinOM1 | sin15), (sinDG1 | sin14), (sinOA2 | sin14), (sinDB1 | sin14), 0 }, // ÀØÇôÁø ·¹½ÃÇÇ °©ÁÖ
											{ (sinDA1 | sin17), (sinDA2 | sin17), (sinDS1 | sin15), (sinOM1 | sin16), (sinDG1 | sin15), (sinOA2 | sin15), (sinDB1 | sin15), 0 }, // °í´ëÀÇ ·¹½ÃÇÇ °©ÁÖ
											{ (sinDA1 | sin18), (sinDA2 | sin18), (sinDS1 | sin16), (sinOM1 | sin17), (sinDG1 | sin16), (sinOA2 | sin16), (sinDB1 | sin16), 0 }, // ´ëÁöÀÇ ·¹½ÃÇÇ °©ÁÖ
											{ (sinDA1 | sin19), (sinDA2 | sin19), (sinDS1 | sin17), (sinOM1 | sin18), (sinDG1 | sin17), (sinOA2 | sin17), (sinDB1 | sin17), 0 }, // ¾îµÒÀÇ ·¹½ÃÇÇ °©ÁÖ
											{ (sinDA1 | sin20), (sinDA2 | sin20), (sinDS1 | sin18), (sinOM1 | sin19), (sinDG1 | sin18), (sinOA2 | sin18), (sinDB1 | sin18), 0 }, // È­¿°ÀÇ ·¹½ÃÇÇ °©ÁÖ
											{ (sinDA1 | sin21), (sinDA2 | sin21), (sinDS1 | sin19), (sinOM1 | sin20), (sinDG1 | sin19), (sinOA2 | sin19), (sinDB1 | sin19), 0 }, // ¹Ù¶÷ÀÇ ·¹½ÃÇÇ °©ÁÖ
											{ (sinDA1 | sin23), (sinDA2 | sin23), (sinDS1 | sin21), (sinOM1 | sin22), (sinDG1 | sin21), (sinOA2 | sin21), (sinDB1 | sin21), 0 }, // ÅÂ¾çÀÇ ·¹½ÃÇÇ °©ÁÖ
											{ (sinDA1 | sin24), (sinDA2 | sin24), (sinDS1 | sin22), (sinOM1 | sin23), (sinDG1 | sin22), (sinOA2 | sin22), (sinDB1 | sin22), 0 }, // ±¤Æ÷ÇÑ ·¹½ÃÇÇ °©ÁÖ
											{ 0, 0, 0, 0, 0, 0, 0, 0 } , // Ãµ»óÀÇ ·¹½ÃÇÇ °©ÁÖ
											{ (sinOA1 | sin36), 0, 0, 0, 0, 0, 0, 0 } , // Æ÷¼³ÀÇ ·¹½ÃÇÇ //Àåº°
											{ dwItem, 0, 0, 0, 0, 0, 0, 0 } } // ±â¾ïÀÇ ·¹½ÃÇÇ // Àåº° - ´ëÀåÀåÀÌÀÇ È¥
	};

	if ((pItemCode[0].sBaseItemID.ToInt() & sinITEM_MASK2) == sinWR1)
	{
		for (int i = 0; i < MAX_RECIPE_KIND; i++)
		{
			if (Arm_Armor_Code[i] == (pItemCode[0].sBaseItemID.ToInt() & sinITEM_MASK3))
			{
				for (int j = 0; j < MAX_RUNE; j++)
				{
					RuneCnt = 0;
					for (int x = 0; x < 3; x++)
					{
						for (int y = 0; y < 3; y++)
						{
							if (CheckRuneCode[i][j][x] == pItemCode[y + 1].sBaseItemID.ToInt())
							{
								RuneCnt++;
								break;
							}
						}
						if (RuneCnt == 3)
						{
							for (int c = 0; c < MAX_HANDMADEITEM; c++)
							{
								if (CreateItemCode[0][i][j] == g_Manufacture_ItemInfo[c].ItemCode)
								{
									Result.ItemCode = g_Manufacture_ItemInfo[c].ItemCode;
									lstrcpy(Result.ItemName, g_Manufacture_ItemInfo[c].ItemName);
									Result.Weight = g_Manufacture_ItemInfo[c].Weight;
									Result.Price = g_Manufacture_ItemInfo[c].Price / 3;
									ForceItemPrice2 = Result.Price;
									m_ManufacturePrice = Result.Price;
								}
							}
							return Result;
						}
					}
				}
			}
		}
	}
	else if ((pItemCode[0].sBaseItemID.ToInt() & sinITEM_MASK2) == sinDR1)
	{
		for (int i = 0; i < MAX_RECIPE_KIND; i++)
		{
			if (Arm_Armor_Code[i] == (pItemCode[0].sBaseItemID.ToInt() & sinITEM_MASK3))
			{
				for (int j = 0; j < MAX_RUNE; j++)
				{
					RuneCnt = 0;
					for (int x = 0; x < 3; x++)
					{
						for (int y = 0; y < 3; y++)
						{
							if (CheckRuneCode[i][j][x] == pItemCode[y + 1].sBaseItemID.ToInt())
							{
								RuneCnt++;
								break;
							}
						}
						if (RuneCnt == 3)
						{
							for (int c = 0; c < MAX_HANDMADEITEM; c++)
							{
								if (CreateItemCode[1][i][j] == g_Manufacture_ItemInfo[c].ItemCode)
								{
									Result.ItemCode = g_Manufacture_ItemInfo[c].ItemCode;
									lstrcpy(Result.ItemName, g_Manufacture_ItemInfo[c].ItemName);
									Result.Weight = g_Manufacture_ItemInfo[c].Weight;
									Result.Price = g_Manufacture_ItemInfo[c].Price / 3;
									ForceItemPrice2 = Result.Price;
									m_ManufacturePrice = Result.Price;
								}
							}
							if (j == 7)
							{
								for (int c = 0; c < MAX_HANDMADEITEM; c++)
								{
									if (CreateItemCode[1][i][0] == g_Manufacture_ItemInfo[c].ItemCode)
									{
										Result.ItemCode = g_Manufacture_ItemInfo[c].ItemCode;
#ifdef ENGLISH_LANGUAGE
										lstrcpy(Result.ItemName, "Result of manufacturing");
#else
										lstrcpy(Result.ItemName, "ÖÆÔìÎïÆ·");
#endif 
										Result.Weight = g_Manufacture_ItemInfo[c].Weight;
										Result.Price = g_Manufacture_ItemInfo[c].Price / 3;
										ForceItemPrice2 = Result.Price;
										m_ManufacturePrice = Result.Price;
									}
								}
								return Result;
							}
							return Result;
						}
					}
				}
			}
		}
	}
	return Result;
}
int ManufactureItemResultInfo(SManufacture_ResultItemInfo_Server *pResultItemInfo)
{
	for (int i = 0; i < MAX_HANDMADEITEM; i++)
	{
		g_Manufacture_ItemInfo[i].ItemCode = pResultItemInfo->ItemCode[i];
		lstrcpy(g_Manufacture_ItemInfo[i].ItemName, pResultItemInfo->ItemName[i]);
		g_Manufacture_ItemInfo[i].Weight = pResultItemInfo->Weight[i];
		g_Manufacture_ItemInfo[i].Price = pResultItemInfo->Price[i];
	}
	return TRUE;
}
int Element_StoneInfo[3][6] =
{
	{sinSS1 | sin01,sinSS1 | sin01,sinSS1 | sin01,sinSS1 | sin01,sinES1 | sin01,ELEMENT_FIRE},
	{sinSS1 | sin02,sinSS1 | sin02,sinSS1 | sin02,sinSS1 | sin02,sinES1 | sin02,ELEMENT_ICE},
	{sinSS1 | sin03,sinSS1 | sin03,sinSS1 | sin03,sinSS1 | sin03,sinES1 | sin03,ELEMENT_THUNDER},
};

int cELEMENT::RecvItem(ELEMENT_ITEM_SERVER *pItemServer)
{
	memcpy(&ElementItemServer, pItemServer, sizeof(ELEMENT_ITEM_SERVER));
	return TRUE;
}
int cELEMENT::CreateElementItem()
{
	int ItemElement = 0;

	ElementItemServer.Result = FALSE;

	for (int i = 0; i < 3; i++)
	{
		if (ElementItemServer.SheltomCode[0] == Element_StoneInfo[i][0] &&
			ElementItemServer.SheltomCode[1] == Element_StoneInfo[i][1] &&
			ElementItemServer.SheltomCode[2] == Element_StoneInfo[i][2] &&
			ElementItemServer.SheltomCode[3] == Element_StoneInfo[i][3] &&
			ElementItemServer.SheltomCode[4] == Element_StoneInfo[i][4])
		{
			ItemElement = Element_StoneInfo[i][5];
			ElementItemServer.Result = TRUE;
			break;
		}
	}
	ElementItemServer.DesItem.sItem.ItemElement = ItemElement;

	ReformMixItem(&ElementItemServer.DesItem.sItem);

	return ItemElement;
}

int Socket_StoneInfo[8][4] =
{
	{sinSR1 | sin01,sinSR1 | sin01,sinSR1 | sin01,sinSR1 | sin01},
	{sinSR1 | sin02,sinSR1 | sin02,sinSR1 | sin02,sinSR1 | sin02},
	{sinSR1 | sin03,sinSR1 | sin03,sinSR1 | sin03,sinSR1 | sin03},
	{sinSR1 | sin04,sinSR1 | sin04,sinSR1 | sin04,sinSR1 | sin04},
	{sinSR1 | sin05,sinSR1 | sin05,sinSR1 | sin05,sinSR1 | sin05},
	{sinSR1 | sin06,sinSR1 | sin06,sinSR1 | sin06,sinSR1 | sin06},
};
int cSOCKET::CheckItem()
{
	for (int i = 0; i < 6; i++)
	{
		if (SocketItem[1].sItem.sItemID.ToInt() == Socket_StoneInfo[i][0] &&
			SocketItem[2].sItem.sItemID.ToInt() == Socket_StoneInfo[i][1] &&
			SocketItem[3].sItem.sItemID.ToInt() == Socket_StoneInfo[i][2] &&
			SocketItem[4].sItem.sItemID.ToInt() == Socket_StoneInfo[i][3])
		{
			SocketCheckFlag = TRUE;
			break;
		}
		else
			SocketCheckFlag = FALSE;
	}
	return TRUE;
}
int cSOCKET::RecvItem(SOCKET_ITEM_SERVER *pItemServer)
{
	memcpy(&SocketItemServer, pItemServer, sizeof(SOCKET_ITEM_SERVER));
	return TRUE;
}
int cSOCKET::CreateSocketItem()
{
	int ItemSocket = 0;

	SocketItemServer.Result = FALSE;

	for (int i = 0; i < 5; i++)
	{
		if (SocketItemServer.SheltomCode[0] == Socket_StoneInfo[i][0] &&
			SocketItemServer.SheltomCode[1] == Socket_StoneInfo[i][1] &&
			SocketItemServer.SheltomCode[2] == Socket_StoneInfo[i][2] &&
			SocketItemServer.SheltomCode[3] == Socket_StoneInfo[i][3])
		{
			if (i == 0)
				ItemSocket = 6;
			else if (i == 1)
				ItemSocket = 1;
			else if (i == 2)
				ItemSocket = 2;
			else if (i == 3)
				ItemSocket = 3;
			else if (i == 4)
				ItemSocket = 4;
			else if (i == 5)
				ItemSocket = 5;

			break;
		}
	}

	if (ItemSocket)
	{
		for (int i = 0; i < 2; i++)
		{
			if ((SocketItemServer.DesItem.sItem.ItemSocket[i] & 0xF0) == 0)
			{
				SocketItemServer.DesItem.sItem.ItemSocket[i] = (ItemSocket << 4);
				SocketItemServer.Result = TRUE;
				break;
			}
		}
	}
	ReformMixItem(&SocketItemServer.DesItem.sItem);

	return ItemSocket;
}