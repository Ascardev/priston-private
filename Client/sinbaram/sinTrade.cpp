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
sINVENTORY *BackUpsInven;
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
	#include "sinMakeItem.h"
};


DWORD sinTradeColor = D3DCOLOR_RGBA(0, 200, 255, 80);


int UpTradePosi[5][4] =
{
	{21,136 + sinInterHeight2,21 + (22 * 9),136 + (22 * 4) + sinInterHeight2},
	{231,170 + sinInterHeight2,250,189 + sinInterHeight2},
	{251,120,326,137},
	{251,118,326,162},
	{252,221 + sinInterHeight2,252 + 26,221 + 26 + sinInterHeight2}

};

int DownTradePosi[6][4] =
{
	{21,224 + 21 + sinInterHeight2,21 + (22 * 9),224 + 21 + (22 * 4) + sinInterHeight2},
	{225,205,250,226},
	{251,206,326,224},
	{251,232,326,250},
	{252 + 1,310 + sinInterHeight2,252 + 26,310 + 26 + sinInterHeight2},
	{305,314 + sinInterHeight2,304 + 20,314 + 20 + sinInterHeight2},

};


int TradeStartX = DownTradePosi[T_SET_BOX][0], TradeStartY = DownTradePosi[T_SET_BOX][1], TradeEndX = DownTradePosi[T_SET_BOX][2], TradeEndY = DownTradePosi[T_SET_BOX][3];

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

POINT AgingLevelSheltomXY[4][3] =
{
	{{218,193 + sinInterHeight2}			,{218 + 22,193 + sinInterHeight2}		  ,{218 + 22 + 22,193 + sinInterHeight2}},
	{{218,193 + 22 + sinInterHeight2}		,{218 + 22,193 + 22 + sinInterHeight2}	  ,{218 + 22 + 22,193 + 22 + sinInterHeight2}},
	{{218,193 + 22 + 22 + sinInterHeight2}	,{218 + 22,193 + 22 + 22 + sinInterHeight2}   ,{218 + 22 + 22,193 + 22 + 22 + sinInterHeight2}},
	{{218,193 + 22 + 22 + 22 + sinInterHeight2} ,{218 + 22,193 + 22 + 22 + 22 + sinInterHeight2},{218 + 22 + 22,193 + 22 + 22 + 22 + sinInterHeight2}}

};

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
void cTRADE::Init()
{
	memset(&sCraftItem, 0, sizeof(sCRAFTITEM));
	memset(&sCraftItem_Recv, 0, sizeof(sCRAFTITEM_SERVER));

	MatTradebuttonMain = CreateTextureMaterial("Image\\SinImage\\Shopall\\TradeButton\\TradeButtonMain.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatTradebuttonCancel = CreateTextureMaterial("Image\\SinImage\\Shopall\\TradeButton\\ButtonCancel.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	ManufactureItem.RuneIndexInit();
	Load();
}
void cTRADE::Load()
{
	char szTemp[256];

	lpCheck = LoadDibSurfaceOffscreen("Image\\SinImage\\shopall\\Trade_Check.bmp");
	lpCheckInfo = LoadDibSurfaceOffscreen("Image\\SinImage\\shopall\\Trade_Check_Info.bmp");
	lpDelayCheck = LoadDibSurfaceOffscreen("Image\\SinImage\\shopall\\Trade_Check_Delay.bmp");

	lpbuttonOk = LoadDibSurfaceOffscreen("Image\\SinImage\\shopall\\TradeButton\\ButtonOk.bmp");

	lpbuttonCancel = LoadDibSurfaceOffscreen("Image\\SinImage\\shopall\\Trade_Cancel.bmp");
	lpbuttonCancelInfo = LoadDibSurfaceOffscreen("Image\\SinImage\\shopall\\Trade_CancelInfo.bmp");

	lpCheck_Glay = LoadDibSurfaceOffscreen("Image\\SinImage\\shopall\\Trade_Check_Glay.bmp");
	lpCenterBox = LoadDibSurfaceOffscreen("Image\\SinImage\\shopall\\Trade_0.bmp");

	for (int i = 0; i < MAX_SHELTOM; i++)
	{
		wsprintf(szTemp, "Image\\SinImage\\shopall\\Aging\\itos%d_.bmp", 100 + i + 1);
		cAging.lpGraySheltom[i] = LoadDibSurfaceOffscreen(szTemp);
	}
}
void cTRADE::Release()
{
	DELET(lpCheck);
	DELET(lpCheckInfo);
	DELET(lpDelayCheck);
	DELET(lpbuttonOk);
	DELET(lpbuttonCancel);
	DELET(lpbuttonCancelInfo);
	DELET(lpCheck_Glay);
}
DWORD TradeSpotTimer = 0;

void cTRADE::Draw()
{
	sinInterHeight2 = -50;

	int i = 0, j = 0;

	DrawSprite(0 - (256 + 128 - sinMoveKindInter[SIN_WAREHOUSE]), 90 + sinInterHeight2, cShop.lpShopMain, 0, 0, 344, 264);

	DrawSprite(0 - (256 + 128 - sinMoveKindInter[SIN_TRADE]), 90 + sinInterHeight2, cShop.lpShopMain, 0, 0, 344, 264);
	DrawSprite(225 - (256 + 128 - sinMoveKindInter[SIN_TRADE]), 47, cShop.lpTitle_Trade, 0, 0, 111, 244);

	DrawSprite(0 - (256 + 128 - sinMoveKindInter[SIN_CRAFTITEM]), 90 + sinInterHeight2, cShop.lpShopMain, 0, 0, 344, 264);
	DrawSprite(225 - (256 + 128 - sinMoveKindInter[SIN_CRAFTITEM]), 47, cShop.lpTitle_CraftItem, 0, 0, 111, 32);
	DrawSprite(18 - (256 + 128 - sinMoveKindInter[SIN_CRAFTITEM]), 135 + sinInterHeight2, cShop.lpCraftItemMain, 0, 0, 320, 208);

	DrawSprite(200 - (256 + 128 - sinMoveKindInter[SIN_CRAFTITEM]), 314 + sinInterHeight2, cShop.lpGoldEdit, 0, 0, 98, 21);

	if (cCraftItem.ForceFlag)
	{
		if (!lpForceMain)
		{
			lpForceMain = LoadDibSurfaceOffscreen("Image\\SinImage\\shopall\\shop_alchemy.bmp");
			lpForceButtonInfo = LoadDibSurfaceOffscreen("Image\\SinImage\\shopall\\Bt_alchemy.bmp");
			lpForceTitle = LoadDibSurfaceOffscreen("Image\\SinImage\\shopall\\title_alchemy.bmp");
		}
		DrawSprite(17 - (256 + 128 - sinMoveKindInter[SIN_CRAFTITEM]), 134 + sinInterHeight2, lpForceMain, 0, 0, 217, 208);
		DrawSprite(225 - (256 + 128 - sinMoveKindInter[SIN_CRAFTITEM]), 47, lpForceTitle, 0, 0, 111, 32);
	}

	DrawSprite(0 - (256 + 128 - sinMoveKindInter[SIN_AGING]), 90 + sinInterHeight2, cShop.lpShopMain, 0, 0, 344, 264);
	DrawSprite(225 - (256 + 128 - sinMoveKindInter[SIN_AGING]), 47, cShop.lpTitle_Aging, 0, 0, 111, 32);
	DrawSprite(18 - (256 + 128 - sinMoveKindInter[SIN_AGING]), 135 + sinInterHeight2, cShop.lpCraftItemMain, 0, 0, 320, 208);
	DrawSprite(200 - (256 + 128 - sinMoveKindInter[SIN_AGING]), 314 + sinInterHeight2, cShop.lpGoldEdit, 0, 0, 98, 21);

	DrawSprite(0 - (256 + 128 - sinMoveKindInter[SIN_SMELTING]), 90 + sinInterHeight2, cShop.lpShopMain, 0, 0, 344, 264);
	DrawSprite(225 - (256 + 128 - sinMoveKindInter[SIN_SMELTING]), 47, cShop.lpTitle_SmeltingItem, 0, 0, 111, 32);
	DrawSprite(18 - (256 + 128 - sinMoveKindInter[SIN_SMELTING]), 135 + sinInterHeight2, cShop.lpSmeltingItemMain, 0, 0, 320, 208);
	DrawSprite(200 - (256 + 128 - sinMoveKindInter[SIN_SMELTING]), 314 + sinInterHeight2, cShop.lpGoldEdit, 0, 0, 98, 21);

	DrawSprite(0 - (256 + 128 - sinMoveKindInter[SIN_MANUFACTURE]), 90 + sinInterHeight2, cShop.lpShopMain, 0, 0, 344, 264);
	DrawSprite(225 - (256 + 128 - sinMoveKindInter[SIN_MANUFACTURE]), 47, cShop.lpTitle_ManufactureItem, 0, 0, 111, 32);
	DrawSprite(18 - (256 + 128 - sinMoveKindInter[SIN_MANUFACTURE]), 135 + sinInterHeight2, cShop.lpManufactureItemMain, 0, 0, 320, 208);
	DrawSprite(200 - (256 + 128 - sinMoveKindInter[SIN_MANUFACTURE]), 314 + sinInterHeight2, cShop.lpGoldEdit, 0, 0, 98, 21);

	DrawSprite(0 - (256 + 128 - sinMoveKindInter[SIN_MIXTURE_RESET]), 90 + sinInterHeight2, cShop.lpShopMain, 0, 0, 344, 264);
	DrawSprite(225 - (256 + 128 - sinMoveKindInter[SIN_MIXTURE_RESET]), 47, cShop.lpMResetTitle, 0, 0, 111, 32);
	DrawSprite(18 - (256 + 128 - sinMoveKindInter[SIN_MIXTURE_RESET]), 135 + sinInterHeight2, cShop.lpMResetMain, 0, 0, 320, 208);

	DrawSprite(0 - (256 + 128 - sinMoveKindInter[SIN_ELEMENT]), 90 + sinInterHeight2, cShop.lpShopMain, 0, 0, 344, 264);
	DrawSprite(225 - (256 + 128 - sinMoveKindInter[SIN_ELEMENT]), 47, cShop.lpElementTitle, 0, 0, 111, 32);
	DrawSprite(18 - (256 + 128 - sinMoveKindInter[SIN_ELEMENT]), 135 + sinInterHeight2, cShop.lpElementMain, 0, 0, 320, 208);
	DrawSprite(200 - (256 + 128 - sinMoveKindInter[SIN_ELEMENT]), 314 + sinInterHeight2, cShop.lpGoldEdit, 0, 0, 98, 21);

	DrawSprite(0 - (256 + 128 - sinMoveKindInter[SIN_SOCKET]), 90 + sinInterHeight2, cShop.lpShopMain, 0, 0, 344, 264);
	DrawSprite(225 - (256 + 128 - sinMoveKindInter[SIN_SOCKET]), 47, cShop.lpSocketTitle, 0, 0, 111, 32);
	DrawSprite(18 - (256 + 128 - sinMoveKindInter[SIN_SOCKET]), 135 + sinInterHeight2, cShop.lpSocketMain, 0, 0, 320, 208);
	DrawSprite(200 - (256 + 128 - sinMoveKindInter[SIN_SOCKET]), 314 + sinInterHeight2, cShop.lpGoldEdit, 0, 0, 98, 21);

	DrawSprite(0 - (256 + 128 - sinMoveKindInter[SIN_CARAVAN]), 90 + sinInterHeight2, cShop.lpCaravanMain[cCaravan.SelectTypeFlag - 1], 0, 0, 344, 264);

	for (i = 0; i < 9; i++)
		DrawSprite(21 + (i * 22) - (256 + 128 - sinMoveKindInter[SIN_TRADE]), 224 + sinInterHeight2, lpCenterBox, 0, 0, 22, 21);

	if (sTrade.CheckFlag)
	{
		if (!CheckDelayFlag)
			DrawSprite(DownTradePosi[T_CHECK_POSI][0] - (256 + 128 - sinMoveKindInter[SIN_TRADE]), DownTradePosi[T_CHECK_POSI][1], lpCheck, 0, 0, 26, 26);
	}
	if (sTradeRecv.CheckFlag)
		DrawSprite(UpTradePosi[T_CHECK_POSI][0] - (256 + 128 - sinMoveKindInter[SIN_TRADE]), UpTradePosi[T_CHECK_POSI][1], lpCheck, 0, 0, 26, 26);

	if (TradeCheckFlag == T_CHECK_POSI)
		DrawSprite(DownTradePosi[T_CHECK_POSI][0] - (256 + 128 - sinMoveKindInter[SIN_TRADE]), DownTradePosi[T_CHECK_POSI][1] - 27, lpCheckInfo, 0, 0, 47, 27);

	if (TradeCheckFlag == T_CLOSE_POSI)
	{
		DrawSprite(DownTradePosi[T_CLOSE_POSI][0] - (256 + 128 - sinMoveKindInter[SIN_TRADE]), DownTradePosi[T_CLOSE_POSI][1], lpbuttonCancel, 0, 0, 20, 20);
		DrawSprite(DownTradePosi[T_CLOSE_POSI][0] - 27 - (256 + 128 - sinMoveKindInter[SIN_TRADE]), DownTradePosi[T_CLOSE_POSI][1] - 27, lpbuttonCancelInfo, 0, 0, 77, 27);
	}

	if (CheckDelayFlag)
		DrawSprite(DownTradePosi[T_CHECK_POSI][0] - (256 + 128 - sinMoveKindInter[SIN_TRADE]), DownTradePosi[T_CHECK_POSI][1], lpCheck_Glay, 0, 0, 26, 26);

	if (cAging.OpenFlag)
	{
		for (i = 0; i < 4; i++)
		{
			for (int t = 0; t < 3; t++)
			{
				if (AgingLevelSheltomIndex[i][t])
					DrawSprite(AgingLevelSheltomXY[i][t].x, AgingLevelSheltomXY[i][t].y, cAging.lpGraySheltom[AgingLevelSheltomIndex[i][t] - 1], 0, 0, 22, 22);
			}
		}
		//DrawSprite(34-(256+128-sinMoveKindInter[SIN_AGING]),312+sinInterHeight2,cShop.lpAging_Gate,0,0,113,21);
	}

	if (SmeltingItem.OpenFlag)
	{
		int SheltomIndex = 0;
		if (S_smeltingItem.SmeltingItem[0].bValid)
		{
			SheltomIndex = SmeltingItem.GetSheltomIndex(S_smeltingItem.SmeltingItem[0].sBaseItemID.ToInt());
			if (SheltomIndex)
				DrawSprite(AgingLevelSheltomXY[0][0].x + 22, AgingLevelSheltomXY[0][0].y + 30, cAging.lpGraySheltom[SheltomIndex - 1], 0, 0, 22, 22);
		}
	}

	switch (TradeColorIndex)
	{
	case SET_ITEM_CHECK_COLOR:
		if (MouseItem.bValid)
		{
			dsDrawColorBox(sinInvenColor[0], TradeColorRect.left - (256 + 128 - sinMoveKindInter[SIN_TRADE]), TradeColorRect.top, TradeColorRect.right, TradeColorRect.bottom);
			dsDrawColorBox(sinInvenColor[0], TradeColorRect.left - (256 + 128 - sinMoveKindInter[SIN_WAREHOUSE]), TradeColorRect.top, TradeColorRect.right, TradeColorRect.bottom);
			dsDrawColorBox(sinInvenColor[0], TradeColorRect.left - (256 + 128 - sinMoveKindInter[SIN_CRAFTITEM]), TradeColorRect.top, TradeColorRect.right, TradeColorRect.bottom);
			dsDrawColorBox(sinInvenColor[0], TradeColorRect.left - (256 + 128 - sinMoveKindInter[SIN_AGING]), TradeColorRect.top, TradeColorRect.right, TradeColorRect.bottom);

			dsDrawColorBox(sinInvenColor[0], TradeColorRect.left - (256 + 128 - sinMoveKindInter[SIN_SMELTING]), TradeColorRect.top, TradeColorRect.right, TradeColorRect.bottom);
			dsDrawColorBox(sinInvenColor[0], TradeColorRect.left - (256 + 128 - sinMoveKindInter[SIN_MANUFACTURE]), TradeColorRect.top, TradeColorRect.right, TradeColorRect.bottom);
			dsDrawColorBox(sinInvenColor[0], TradeColorRect.left - (256 + 128 - sinMoveKindInter[SIN_MIXTURE_RESET]), TradeColorRect.top, TradeColorRect.right, TradeColorRect.bottom);
			dsDrawColorBox(sinInvenColor[0], TradeColorRect.left - (256 + 128 - sinMoveKindInter[SIN_ELEMENT]), TradeColorRect.top, TradeColorRect.right, TradeColorRect.bottom);
			dsDrawColorBox(sinInvenColor[0], TradeColorRect.left - (256 + 128 - sinMoveKindInter[SIN_CARAVAN]), TradeColorRect.top, TradeColorRect.right, TradeColorRect.bottom);
		}
		break;
	case OVERLAP_ITEM_COLOR:
		if (TradeCrashItemIndex[0])
			//dsDrawColorBox(sinInvenColor[1],sWareHouse.WareHouseItem[TradeCrashItemIndex[0]-1].x-(256+128-sinMoveKindInter[SIN_WAREHOUSE]),sWareHouse.WareHouseItem[TradeCrashItemIndex[0]-1].y, sWareHouse.WareHouseItem[TradeCrashItemIndex[0]-1].w, sWareHouse.WareHouseItem[TradeCrashItemIndex[0]-1].h);
			dsDrawColorBox(sinInvenColor[1],
				cWareHouse.WareHouse.WareHouseItem[TradeCrashItemIndex[0] - 1].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_WAREHOUSE]),
				cWareHouse.WareHouse.WareHouseItem[TradeCrashItemIndex[0] - 1].iPlaceY,
				cWareHouse.WareHouse.WareHouseItem[TradeCrashItemIndex[0] - 1].iWidth,
				cWareHouse.WareHouse.WareHouseItem[TradeCrashItemIndex[0] - 1].iHeight);
		break;
	case NOT_SETTING_COLOR:
		dsDrawColorBox(sinInvenColor[2], TradeColorRect.left - (256 + 128 - sinMoveKindInter[SIN_TRADE]), TradeColorRect.top, TradeColorRect.right, TradeColorRect.bottom);
		dsDrawColorBox(sinInvenColor[2], TradeColorRect.left - (256 + 128 - sinMoveKindInter[SIN_WAREHOUSE]), TradeColorRect.top, TradeColorRect.right, TradeColorRect.bottom);
		dsDrawColorBox(sinInvenColor[2], TradeColorRect.left - (256 + 128 - sinMoveKindInter[SIN_CRAFTITEM]), TradeColorRect.top, TradeColorRect.right, TradeColorRect.bottom);
		dsDrawColorBox(sinInvenColor[2], TradeColorRect.left - (256 + 128 - sinMoveKindInter[SIN_AGING]), TradeColorRect.top, TradeColorRect.right, TradeColorRect.bottom);
		dsDrawColorBox(sinInvenColor[2], TradeColorRect.left - (256 + 128 - sinMoveKindInter[SIN_SMELTING]), TradeColorRect.top, TradeColorRect.right, TradeColorRect.bottom);
		dsDrawColorBox(sinInvenColor[2], TradeColorRect.left - (256 + 128 - sinMoveKindInter[SIN_MANUFACTURE]), TradeColorRect.top, TradeColorRect.right, TradeColorRect.bottom);
		dsDrawColorBox(sinInvenColor[2], TradeColorRect.left - (256 + 128 - sinMoveKindInter[SIN_MIXTURE_RESET]), TradeColorRect.top, TradeColorRect.right, TradeColorRect.bottom);
		dsDrawColorBox(sinInvenColor[2], TradeColorRect.left - (256 + 128 - sinMoveKindInter[SIN_ELEMENT]), TradeColorRect.top, TradeColorRect.right, TradeColorRect.bottom);
		dsDrawColorBox(sinInvenColor[2], TradeColorRect.left - (256 + 128 - sinMoveKindInter[SIN_CARAVAN]), TradeColorRect.top, TradeColorRect.right, TradeColorRect.bottom);
		break;
	case NOT_AGING_ITEM:
		dsDrawColorBox(sinInvenColor[2], TradeColorRect.left - (256 + 128 - sinMoveKindInter[SIN_AGING]), TradeColorRect.top, TradeColorRect.right, TradeColorRect.bottom);
	case NOT_USE_COLOR:
		dsDrawColorBox(sinInvenColor[2], TradeColorRect.left - (256 + 128 - sinMoveKindInter[SIN_TRADE]), TradeColorRect.top, TradeColorRect.right, TradeColorRect.bottom);
		break;
	case SELECT_ITEM_COLOR:
		for (i = 0; i < 10; i++)
		{
			if (CopyItemIndex7[i])
				dsDrawColorBox(sinInvenColor[4],
					cWareHouse.WareHouse.WareHouseItem[CopyItemIndex7[i] - 1].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_WAREHOUSE]),
					cWareHouse.WareHouse.WareHouseItem[CopyItemIndex7[i] - 1].iPlaceY,
					cWareHouse.WareHouse.WareHouseItem[CopyItemIndex7[i] - 1].iWidth,
					cWareHouse.WareHouse.WareHouseItem[CopyItemIndex7[i] - 1].iHeight);
			if (CopyItemIndex8[i])
				dsDrawColorBox(sinInvenColor[4],
					cCaravan.sCaravan.Item[CopyItemIndex8[i] - 1].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_CARAVAN]),
					cCaravan.sCaravan.Item[CopyItemIndex8[i] - 1].iPlaceY,
					cCaravan.sCaravan.Item[CopyItemIndex8[i] - 1].iWidth,
					cCaravan.sCaravan.Item[CopyItemIndex8[i] - 1].iHeight);
		}
		if (!SelectTradeItemIndex)
			break;
		if (ItemKindFlag == 1)
			dsDrawColorBox(sinInvenColor[4],
				sTrade.TradeItem[SelectTradeItemIndex - 1].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_TRADE]),
				sTrade.TradeItem[SelectTradeItemIndex - 1].iPlaceY,
				sTrade.TradeItem[SelectTradeItemIndex - 1].iWidth,
				sTrade.TradeItem[SelectTradeItemIndex - 1].iHeight);
		if (ItemKindFlag == 2)
			dsDrawColorBox(sinInvenColor[4],
				sTradeRecv.TradeItem[SelectTradeItemIndex - 1].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_TRADE]),
				sTradeRecv.TradeItem[SelectTradeItemIndex - 1].iPlaceY - T_REVISION_Y,
				sTradeRecv.TradeItem[SelectTradeItemIndex - 1].iWidth,
				sTradeRecv.TradeItem[SelectTradeItemIndex - 1].iHeight);
		if (cWareHouse.WareHouse.WareHouseItem[SelectTradeItemIndex - 1].bValid)
			dsDrawColorBox(sinInvenColor[4],
				cWareHouse.WareHouse.WareHouseItem[SelectTradeItemIndex - 1].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_WAREHOUSE]),
				cWareHouse.WareHouse.WareHouseItem[SelectTradeItemIndex - 1].iPlaceY,
				cWareHouse.WareHouse.WareHouseItem[SelectTradeItemIndex - 1].iWidth,
				cWareHouse.WareHouse.WareHouseItem[SelectTradeItemIndex - 1].iHeight);
		if (sCraftItem.CraftItem[SelectTradeItemIndex - 1].bValid)
			dsDrawColorBox(sinInvenColor[4],
				sCraftItem.CraftItem[SelectTradeItemIndex - 1].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_CRAFTITEM]),
				sCraftItem.CraftItem[SelectTradeItemIndex - 1].iPlaceY,
				sCraftItem.CraftItem[SelectTradeItemIndex - 1].iWidth,
				sCraftItem.CraftItem[SelectTradeItemIndex - 1].iHeight);
		if (sAgingItem.AgingItem[SelectTradeItemIndex - 1].bValid)
			dsDrawColorBox(sinInvenColor[4],
				sAgingItem.AgingItem[SelectTradeItemIndex - 1].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_AGING]),
				sAgingItem.AgingItem[SelectTradeItemIndex - 1].iPlaceY,
				sAgingItem.AgingItem[SelectTradeItemIndex - 1].iWidth,
				sAgingItem.AgingItem[SelectTradeItemIndex - 1].iHeight);
		if (S_smeltingItem.SmeltingItem[SelectTradeItemIndex - 1].bValid)
			dsDrawColorBox(sinInvenColor[4],
				S_smeltingItem.SmeltingItem[SelectTradeItemIndex - 1].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_SMELTING]),
				S_smeltingItem.SmeltingItem[SelectTradeItemIndex - 1].iPlaceY,
				S_smeltingItem.SmeltingItem[SelectTradeItemIndex - 1].iWidth,
				S_smeltingItem.SmeltingItem[SelectTradeItemIndex - 1].iHeight);
		if (sManufactureItem.ManufactureItem[SelectTradeItemIndex - 1].bValid)
			dsDrawColorBox(sinInvenColor[4],
				sManufactureItem.ManufactureItem[SelectTradeItemIndex - 1].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_MANUFACTURE]),
				sManufactureItem.ManufactureItem[SelectTradeItemIndex - 1].iPlaceY,
				sManufactureItem.ManufactureItem[SelectTradeItemIndex - 1].iWidth,
				sManufactureItem.ManufactureItem[SelectTradeItemIndex - 1].iHeight);
		if (sMixtureResetItem.MixtureResetItem[SelectTradeItemIndex - 1].bValid)
			dsDrawColorBox(sinInvenColor[4],
				sMixtureResetItem.MixtureResetItem[SelectTradeItemIndex - 1].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_MIXTURE_RESET]),
				sMixtureResetItem.MixtureResetItem[SelectTradeItemIndex - 1].iPlaceY,
				sMixtureResetItem.MixtureResetItem[SelectTradeItemIndex - 1].iWidth,
				sMixtureResetItem.MixtureResetItem[SelectTradeItemIndex - 1].iHeight);
		if (cElement.ElementItem[SelectTradeItemIndex - 1].bValid)
			dsDrawColorBox(sinInvenColor[4],
				cElement.ElementItem[SelectTradeItemIndex - 1].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_ELEMENT]),
				cElement.ElementItem[SelectTradeItemIndex - 1].iPlaceY,
				cElement.ElementItem[SelectTradeItemIndex - 1].iWidth,
				cElement.ElementItem[SelectTradeItemIndex - 1].iHeight);
		if (cSocket.SocketItem[SelectTradeItemIndex - 1].bValid)
			dsDrawColorBox(sinInvenColor[4],
				cSocket.SocketItem[SelectTradeItemIndex - 1].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_SOCKET]),
				cSocket.SocketItem[SelectTradeItemIndex - 1].iPlaceY,
				cSocket.SocketItem[SelectTradeItemIndex - 1].iWidth,
				cSocket.SocketItem[SelectTradeItemIndex - 1].iHeight);
		if (cCaravan.sCaravan.Item[SelectTradeItemIndex - 1].bValid)
			dsDrawColorBox(sinInvenColor[4],
				cCaravan.sCaravan.Item[SelectTradeItemIndex - 1].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_CARAVAN]),
				cCaravan.sCaravan.Item[SelectTradeItemIndex - 1].iPlaceY,
				cCaravan.sCaravan.Item[SelectTradeItemIndex - 1].iWidth,
				cCaravan.sCaravan.Item[SelectTradeItemIndex - 1].iHeight);
		break;

	}
	for (i = 0; i < MAX_TRADE_ITEM; i++)
	{
		if (sTrade.TradeItem[i].bValid)
		{
			DrawSprite(sTrade.TradeItem[i].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_TRADE]),
				sTrade.TradeItem[i].iPlaceY,
				(smTEXTUREHANDLE *)sTrade.TradeItem[i].pcInventoryTexture,
				0,
				0,
				sTrade.TradeItem[i].iWidth,
				sTrade.TradeItem[i].iHeight);
			if ((sTrade.TradeItem[i].sBaseItemID.ToInt() & sinITEM_MASK2) == sinFO1)
				cInvenTory.DrawForceOrbEffect(sTrade.TradeItem[i].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_TRADE]),
					sTrade.TradeItem[i].iPlaceY);

		}
		if (sTradeRecv.TradeItem[i].bValid)
		{
			DrawSprite(sTradeRecv.TradeItem[i].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_TRADE]),
				sTradeRecv.TradeItem[i].iPlaceY - T_REVISION_Y,
				(smTEXTUREHANDLE *)sTradeRecv.TradeItem[i].pcInventoryTexture,
				0,
				0,
				sTradeRecv.TradeItem[i].iWidth,
				sTradeRecv.TradeItem[i].iHeight);
			if ((sTradeRecv.TradeItem[i].sBaseItemID.ToInt() & sinITEM_MASK2) == sinFO1)
				cInvenTory.DrawForceOrbEffect(sTradeRecv.TradeItem[i].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_TRADE]),
					sTradeRecv.TradeItem[i].iPlaceY - T_REVISION_Y);
		}
	}
	if (TradeRequestFlag)
	{
		TradeSpotTimer++;
		if (TradeSpotTimer > 15)
		{
			dsDrawColorBox(sinTradeColor, TRADEBUTTONMAIN_X + 5, TRADEBUTTONMAIN_Y + 5, 160, 53);
			if (TradeSpotTimer > 30)
				TradeSpotTimer = 0;

		}

		dsDrawTexImage(MatTradebuttonMain, TRADEBUTTONMAIN_X, TRADEBUTTONMAIN_Y, 256, 64, 255);
		if (RequestTradeButtonFlag == 1)
			DrawSprite(TRADEBUTTONMAIN_X + 140, TRADEBUTTONMAIN_Y + 11, lpbuttonOk, 0, 0, 23, 23);
		if (RequestTradeButtonFlag == 2)
			dsDrawTexImage(MatTradebuttonCancel, TRADEBUTTONMAIN_X + 144, TRADEBUTTONMAIN_Y + 37, 16, 16, 255);

	}

	if (cWareHouse.OpenFlag)
	{
		for (i = 0; i < 100; i++)
		{
			if (cWareHouse.WareHouse.WareHouseItem[i].bValid)
			{
				DrawSprite(cWareHouse.WareHouse.WareHouseItem[i].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_WAREHOUSE]),
					cWareHouse.WareHouse.WareHouseItem[i].iPlaceY,
					(smTEXTUREHANDLE *)cWareHouse.WareHouse.WareHouseItem[i].pcInventoryTexture,
					0,
					0,
					cWareHouse.WareHouse.WareHouseItem[i].iWidth,
					cWareHouse.WareHouse.WareHouseItem[i].iHeight);
				if ((cWareHouse.WareHouse.WareHouseItem[i].sBaseItemID.ToInt() & sinITEM_MASK2) == sinFO1)
					cInvenTory.DrawForceOrbEffect(cWareHouse.WareHouse.WareHouseItem[i].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_WAREHOUSE]),
						cWareHouse.WareHouse.WareHouseItem[i].iPlaceX);
			}
		}

		DrawSprite(231 - (256 + 128 - sinMoveKindInter[SIN_WAREHOUSE]), 243 + sinInterHeight2, cShop.lpGoldEdit, 0, 0, 99, 24);
		DrawSprite(231 - (256 + 128 - sinMoveKindInter[SIN_WAREHOUSE]), 241 + sinInterHeight2, cShop.lpWeightEdit, 0, 0, 20, 20);
		DrawSprite(243 - (256 + 128 - sinMoveKindInter[SIN_WAREHOUSE]), 100, cShop.lpTitle_WareHouse, 0, 0, 79, 40);

		/*DrawSprite(311-(256+128-sinMoveKindInter[SIN_WAREHOUSE]) , 243+sinInterHeight2, cShop.lpArrow[0] ,0,0, 20 , 20);
		DrawSprite(231-(256+128-sinMoveKindInter[SIN_WAREHOUSE]) , 243+sinInterHeight2, cShop.lpArrow[1] ,0,0, 20 , 20);

		if (pCursorPos.x > 314 && pCursorPos.x < 334 && pCursorPos.y > 194 && pCursorPos.y < 214)
			DrawSprite(311-(256+128-sinMoveKindInter[SIN_WAREHOUSE]) , 243+sinInterHeight2, cShop.lpArrow[2] ,0,0, 20 , 20);
		if (pCursorPos.x > 234 && pCursorPos.x < 254 && pCursorPos.y > 194 && pCursorPos.y < 214)
			DrawSprite(231-(256+128-sinMoveKindInter[SIN_WAREHOUSE]) , 243+sinInterHeight2, cShop.lpArrow[3] ,0,0, 20 , 20);*/
	}

	if (CloseWareHouseFlag)
	{
		DrawSprite(304 - (256 + 128 - sinMoveKindInter[SIN_WAREHOUSE]), 313 + sinInterHeight2, cShop.lpExit, 0, 0, 20, 20);
		DrawSprite(304 - (256 + 128 - sinMoveKindInter[SIN_WAREHOUSE]), 313 - 27 + sinInterHeight2, cInvenTory.lpExitInfo, 0, 0, 47, 27);
	}

	if (AgingCheckSheltomFlag)
		DrawSprite(158 - (256 + 128 - sinMoveKindInter[SIN_AGING]), 222 + sinInterHeight2, cShop.lpCraftItemButton, 0, 0, 26, 26);

	if (CraftItemButtonIndex == 1)
	{
		DrawSprite(158 - (256 + 128 - sinMoveKindInter[SIN_CRAFTITEM]), 222 + sinInterHeight2, cShop.lpCraftItemButton, 0, 0, 26, 26);
		if (cCraftItem.ForceFlag)
			DrawSprite(148 - (256 + 128 - sinMoveKindInter[SIN_CRAFTITEM]) - 27, 222 - 27 + sinInterHeight2, lpForceButtonInfo, 0, 0, 100, 27);
		else
			DrawSprite(158 - (256 + 128 - sinMoveKindInter[SIN_CRAFTITEM]) - 27, 222 - 27 + sinInterHeight2, cShop.lpCraftItemButtonInfo, 0, 0, 80, 27);
		if (SmeltingItem.OpenFlag)
		{
			DrawSprite(158 - (256 + 128 - sinMoveKindInter[SIN_SMELTING]), 222 + sinInterHeight2, cShop.lpCraftItemButton, 0, 0, 26, 26);
			DrawSprite(158 - (256 + 128 - sinMoveKindInter[SIN_SMELTING]) - 27, 222 - 27 + sinInterHeight2, cShop.lpSmeltingItemButtonInfo, 0, 0, 80, 27);
		}
		if (ManufactureItem.m_OpenFlag)
		{
			DrawSprite(158 - (256 + 128 - sinMoveKindInter[SIN_MANUFACTURE]), 222 + sinInterHeight2, cShop.lpCraftItemButton, 0, 0, 26, 26);
			DrawSprite(158 - (256 + 128 - sinMoveKindInter[SIN_MANUFACTURE]) - 27, 222 - 27 + sinInterHeight2, cShop.lpManufactureItemButtonInfo, 0, 0, 80, 27);
		}
	}

	if (MixtureResetCheckFlag)
		DrawSprite(158 - (256 + 128 - sinMoveKindInter[SIN_MIXTURE_RESET]), 221 + sinInterHeight2, cShop.lpMResetButton, 0, 0, 26, 26);

	if (CraftItemButtonIndex == 1 && MixtureResetCheckFlag)
		DrawSprite(158 - (256 + 128 - sinMoveKindInter[SIN_MIXTURE_RESET]) - 27, 222 - 27 + sinInterHeight2, cShop.lpMResetButtonInfo, 0, 0, 80, 27);

	if (CraftItemButtonIndex == 1 && AgingCheckSheltomFlag)
	{
		DrawSprite(158 - (256 + 128 - sinMoveKindInter[SIN_AGING]), 222 + sinInterHeight2, cShop.lpCraftItemButton, 0, 0, 26, 26);
		DrawSprite(158 - (256 + 128 - sinMoveKindInter[SIN_AGING]) - 27, 222 - 27 + sinInterHeight2, cShop.lpAging_Info, 0, 0, 80, 27);
	}

	if (CraftItemButtonIndex == 2)
	{
		DrawSprite(304 - (256 + 128 - sinMoveKindInter[SIN_CRAFTITEM]) + 2 - 2, 313 + 1 + sinInterHeight2, cShop.lpExit, 0, 0, 20, 20);
		DrawSprite(304 - (256 + 128 - sinMoveKindInter[SIN_CRAFTITEM]) - 2, 313 - 27 + sinInterHeight2, cInvenTory.lpExitInfo, 0, 0, 47, 27);
		DrawSprite(304 - (256 + 128 - sinMoveKindInter[SIN_AGING]) + 2 - 2, 313 + 1 + sinInterHeight2, cShop.lpExit, 0, 0, 20, 20);
		DrawSprite(304 - (256 + 128 - sinMoveKindInter[SIN_AGING]) - 2, 313 - 27 + sinInterHeight2, cInvenTory.lpExitInfo, 0, 0, 47, 27);

		DrawSprite(304 - (256 + 128 - sinMoveKindInter[SIN_SMELTING]) + 2 - 2, 313 + 1 + sinInterHeight2, cShop.lpExit, 0, 0, 20, 20);
		DrawSprite(304 - (256 + 128 - sinMoveKindInter[SIN_SMELTING]) - 2, 313 - 27 + sinInterHeight2, cInvenTory.lpExitInfo, 0, 0, 47, 27);

		DrawSprite(304 - (256 + 128 - sinMoveKindInter[SIN_MANUFACTURE]) + 2 - 2, 313 + 1 + sinInterHeight2, cShop.lpExit, 0, 0, 20, 20);
		DrawSprite(304 - (256 + 128 - sinMoveKindInter[SIN_MANUFACTURE]) - 2, 313 - 27 + sinInterHeight2, cInvenTory.lpExitInfo, 0, 0, 47, 27);

		DrawSprite(304 - (256 + 128 - sinMoveKindInter[SIN_MIXTURE_RESET]) + 2 - 2, 313 + 1 + sinInterHeight2, cShop.lpExit, 0, 0, 20, 20);
		DrawSprite(304 - (256 + 128 - sinMoveKindInter[SIN_MIXTURE_RESET]) - 2, 313 - 27 + sinInterHeight2, cInvenTory.lpExitInfo, 0, 0, 47, 27);

		DrawSprite(304 - (256 + 128 - sinMoveKindInter[SIN_ELEMENT]) + 2 - 2, 313 + 1 + sinInterHeight2, cShop.lpExit, 0, 0, 20, 20);
		DrawSprite(304 - (256 + 128 - sinMoveKindInter[SIN_ELEMENT]) - 2, 313 - 27 + sinInterHeight2, cInvenTory.lpExitInfo, 0, 0, 47, 27);
	}
	if (cCraftItem.OpenFlag || cAging.OpenFlag)
	{
		for (i = 0; i < 15; i++)
		{
			if (sCraftItem.CraftItem[i].bValid)
				DrawSprite(sCraftItem.CraftItem[i].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_CRAFTITEM]),
					sCraftItem.CraftItem[i].iPlaceY,
					(smTEXTUREHANDLE *)sCraftItem.CraftItem[i].pcInventoryTexture,
					0,
					0,
					sCraftItem.CraftItem[i].iWidth,
					sCraftItem.CraftItem[i].iHeight);
			if (sAgingItem.AgingItem[i].bValid)
				DrawSprite(sAgingItem.AgingItem[i].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_AGING]),
					sAgingItem.AgingItem[i].iPlaceY,
					(smTEXTUREHANDLE *)sAgingItem.AgingItem[i].pcInventoryTexture,
					0,
					0,
					sAgingItem.AgingItem[i].iWidth,
					sAgingItem.AgingItem[i].iHeight);
		}
	}
	if (cMixtureReset.OpenFlag)
	{
		for (i = 0; i < 2; i++)
		{
			if (sMixtureResetItem.MixtureResetItem[i].bValid)
				DrawSprite(sMixtureResetItem.MixtureResetItem[i].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_MIXTURE_RESET]),
					sMixtureResetItem.MixtureResetItem[i].iPlaceX,
					(smTEXTUREHANDLE *)sMixtureResetItem.MixtureResetItem[i].pcInventoryTexture,
					0,
					0,
					sMixtureResetItem.MixtureResetItem[i].iWidth,
					sMixtureResetItem.MixtureResetItem[i].iHeight);
		}
	}
	if (cElement.OpenFlag)
	{
		for (i = 0; i < 6; i++)
		{
			if (cElement.ElementItem[i].bValid)
				DrawSprite(cElement.ElementItem[i].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_ELEMENT]),
					cElement.ElementItem[i].iPlaceY,
					(smTEXTUREHANDLE *)cElement.ElementItem[i].pcInventoryTexture,
					0,
					0,
					cElement.ElementItem[i].iWidth,
					cElement.ElementItem[i].iHeight);
		}
		if (cElement.ElementCheckFlag == TRUE)
		{
			DrawSprite(158 - (256 + 128 - sinMoveKindInter[SIN_ELEMENT]), 221 + sinInterHeight2, cShop.lpElementButton, 0, 0, 26, 26);
			if (CraftItemButtonIndex == 1)
				DrawSprite(158 - (256 + 128 - sinMoveKindInter[SIN_ELEMENT]) - 27, 222 - 27 + sinInterHeight2, cShop.lpElementButtonInfo, 0, 0, 80, 27);
		}
	}
	if (cSocket.OpenFlag)
	{
		for (i = 0; i < 5; i++)
		{
			if (cSocket.SocketItem[i].bValid)
				DrawSprite(cSocket.SocketItem[i].iPlaceX - 256 + 128 - sinMoveKindInter[SIN_SOCKET],
					cSocket.SocketItem[i].iPlaceY,
					(smTEXTUREHANDLE *)cSocket.SocketItem[i].pcInventoryTexture,
					0,
					0,
					cSocket.SocketItem[i].iWidth,
					cSocket.SocketItem[i].iHeight);
		}
		if (cSocket.SocketCheckFlag == TRUE)
		{
			DrawSprite(158 - (256 + 128 - sinMoveKindInter[SIN_SOCKET]), 221 + sinInterHeight2, cShop.lpSocketButton, 0, 0, 26, 26);
			if (CraftItemButtonIndex == 1)
				DrawSprite(158 - (256 + 128 - sinMoveKindInter[SIN_SOCKET]) - 27, 222 - 27 + sinInterHeight2, cShop.lpSocketButtonInfo, 0, 0, 80, 27);
		}
	}
	if (cCaravan.OpenFlag)
	{
		DrawSprite(300 - (256 + 128 - sinMoveKindInter[SIN_CARAVAN]), 90 + 177 + sinInterHeight2, cShop.lpCaravanRename[0], 0, 0, 28, 28);
		switch (cCaravan.SelectMode)
		{
		case 0:
			DrawSprite(230 - (256 + 128 - sinMoveKindInter[SIN_CARAVAN]), 90 + 177 + sinInterHeight2, cShop.lpCaravanStart[0], 0, 0, 28, 28);
			DrawSprite(265 - (256 + 128 - sinMoveKindInter[SIN_CARAVAN]), 90 + 177 + sinInterHeight2, cShop.lpCaravanStop[1], 0, 0, 28, 28);
			break;
		case 1:
			DrawSprite(230 - (256 + 128 - sinMoveKindInter[SIN_CARAVAN]), 90 + 177 + sinInterHeight2, cShop.lpCaravanStart[1], 0, 0, 28, 28);
			DrawSprite(265 - (256 + 128 - sinMoveKindInter[SIN_CARAVAN]), 90 + 177 + sinInterHeight2, cShop.lpCaravanStop[0], 0, 0, 28, 28);
			break;
		}
		for (i = 0; i < 100; i++)
		{
			if (cCaravan.sCaravan.Item[i].bValid)
				DrawSprite(cCaravan.sCaravan.Item[i].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_CARAVAN]),
					cCaravan.sCaravan.Item[i].iPlaceY,
					(smTEXTUREHANDLE *)cCaravan.sCaravan.Item[i].pcInventoryTexture,
					0,
					0,
					cCaravan.sCaravan.Item[i].iWidth,
					cCaravan.sCaravan.Item[i].iHeight);
		}
		switch (cCaravan.SelectFlag)
		{
		case 1:
			DrawSprite(304 - (256 + 128 - sinMoveKindInter[SIN_CARAVAN]) + 2 - 2, 313 + sinInterHeight2, cShop.lpExit, 0, 0, 20, 20);
			DrawSprite(304 - (256 + 128 - sinMoveKindInter[SIN_CARAVAN]) - 2, 313 - 27 + sinInterHeight2, cInvenTory.lpExitInfo, 0, 0, 47, 27);
			break;
		case 2:
			DrawSprite(230 - (256 + 128 - sinMoveKindInter[SIN_CARAVAN]), 90 + 177 + sinInterHeight2, cShop.lpCaravanStart[1], 0, 0, 28, 28);
			break;
		case 3:
			DrawSprite(265 - (256 + 128 - sinMoveKindInter[SIN_CARAVAN]), 90 + 177 + sinInterHeight2, cShop.lpCaravanStop[1], 0, 0, 28, 28);
			break;
		case 4:
			DrawSprite(300 - (256 + 128 - sinMoveKindInter[SIN_CARAVAN]), 90 + 177 + sinInterHeight2, cShop.lpCaravanRename[1], 0, 0, 28, 28);
			break;
		}
	}
	if (SmeltingItem.OpenFlag)
	{
		for (i = 0; i < 5; i++)
		{
			if (S_smeltingItem.SmeltingItem[i].bValid)
				DrawSprite(S_smeltingItem.SmeltingItem[i].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_SMELTING]),
					S_smeltingItem.SmeltingItem[i].iPlaceY,
					(smTEXTUREHANDLE *)S_smeltingItem.SmeltingItem[i].pcInventoryTexture,
					0,
					0,
					S_smeltingItem.SmeltingItem[i].iWidth,
					S_smeltingItem.SmeltingItem[i].iHeight);
		}
	}
	if (ManufactureItem.m_OpenFlag)
	{
		for (i = 0; i < 4; i++)
		{
			if (sManufactureItem.ManufactureItem[i].bValid)
				DrawSprite(sManufactureItem.ManufactureItem[i].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_MANUFACTURE]),
					sManufactureItem.ManufactureItem[i].iPlaceY,
					(smTEXTUREHANDLE *)sManufactureItem.ManufactureItem[i].pcInventoryTexture,
					0,
					0,
					sManufactureItem.ManufactureItem[i].iWidth,
					sManufactureItem.ManufactureItem[i].iHeight);
		}
	}

	CraftItemMessageBoxPosi.x = 230;
	CraftItemMessageBoxPosi.y = 200;

	if (ShowItemCraftMessageFlag || ShowItemAgingMessageFlag || ShowItemSmeltingMessageFlag || ShowItemManufactureMessageFlag || ShowItemOverSpace)
	{
		for (i = 0; i < CraftItemMessageSize.x; i++)
		{
			for (int j = 0; j < CraftItemMessageSize.y; j++)
			{
				if (i == 0 && j == 0)
					dsDrawTexImage(cItem.MatItemInfoBox_TopLeft, CraftItemMessageBoxPosi.x + (i * 16), CraftItemMessageBoxPosi.y + (j * 16), 16, 16, 255);
				if (j == 0 && i != 0 && i + 1 < CraftItemMessageSize.x)
					dsDrawTexImage(cItem.MatItemInfoBox_TopCenter, CraftItemMessageBoxPosi.x + (i * 16), CraftItemMessageBoxPosi.y + (j * 16), 16, 16, 255);
				if (j == 0 && i + 1 == CraftItemMessageSize.x)
					dsDrawTexImage(cItem.MatItemInfoBox_TopRight, CraftItemMessageBoxPosi.x + (i * 16), CraftItemMessageBoxPosi.y + (j * 16), 16, 16, 255);

				if (i == 0 && j != 0 && j + 1 != CraftItemMessageSize.y)
					dsDrawTexImage(cItem.MatItemInfoBox_Left, CraftItemMessageBoxPosi.x + (i * 16), CraftItemMessageBoxPosi.y + (j * 16), 16, 16, 255);
				if (i != 0 && j != 0 && i + 1 != CraftItemMessageSize.x && j + 1 != CraftItemMessageSize.y)
					dsDrawTexImage(cItem.MatItemInfoBox_Center, CraftItemMessageBoxPosi.x + (i * 16), CraftItemMessageBoxPosi.y + (j * 16), 16, 16, 255);
				if (i + 1 == CraftItemMessageSize.x && j != 0 && j + 1 != CraftItemMessageSize.y)
					dsDrawTexImage(cItem.MatItemInfoBox_Right, CraftItemMessageBoxPosi.x + (i * 16), CraftItemMessageBoxPosi.y + (j * 16), 16, 16, 255);

				if (i == 0 && j + 1 == CraftItemMessageSize.y)
					dsDrawTexImage(cItem.MatItemInfoBox_BottomLeft, CraftItemMessageBoxPosi.x + (i * 16), CraftItemMessageBoxPosi.y + (j * 16), 16, 16, 255);
				if (i != 0 && j + 1 == CraftItemMessageSize.y && i + 1 != CraftItemMessageSize.x)
					dsDrawTexImage(cItem.MatItemInfoBox_BottomCenter, CraftItemMessageBoxPosi.x + (i * 16), CraftItemMessageBoxPosi.y + (j * 16), 16, 16, 255);
				if (j + 1 == CraftItemMessageSize.y && i + 1 == CraftItemMessageSize.x)
					dsDrawTexImage(cItem.MatItemInfoBox_BottomRight, CraftItemMessageBoxPosi.x + (i * 16), CraftItemMessageBoxPosi.y + (j * 16), 16, 16, 255);
			}
		}
	}
}
DWORD	dwTradeDelayTime = 0;
DWORD	dwTradeDelayTime2 = 0;
DWORD	dwTradeDelayTime3 = 0;
DWORD	dwTradeDelayTime4 = 0;

DWORD   dwCraftItemInfoDelayTime = 0;
DWORD   dwMixDelayTime = 0;
DWORD	dwMixItemColyTime = 0;
int		MixCancelButtonDelayFlag = 0;
DWORD   dwForceDelayTime = 0;

void cTRADE::Main()
{
	if (cCraftItem.ForceFlag)
	{
		if (MixItemNoCopyFlag)
		{
			dwForceDelayTime++;
			if (dwForceDelayTime > 70 * 5)
			{
				if (MixItemNoCopyFlag)
					MixItemNoCopyFlag = 0;
				dwForceDelayTime = 0;
			}
		}
		else dwForceDelayTime = 0;
	}

	if (CheckMixItemCopyFlag)
	{
		dwMixItemColyTime++;
		if (dwMixItemColyTime > 70 * 60 * 2)
		{
			dwMixItemColyTime = 0;
			CheckMixItemCopyFlag = 0;
		}
	}
	else
		dwMixItemColyTime = 0;

	if (MixCancelButtonDelayFlag)
	{
		dwMixDelayTime++;
		if (dwMixDelayTime > 70 * 10)
		{
			MixCancelButtonDelayFlag = 0;
			dwMixDelayTime = 0;
		}
	}
	else
		dwMixDelayTime = 0;

	cAging.CheckAgingData();
	int i, j = 0;
	CraftItemButtonIndex = 0;
	RequestTradeButtonFlag = 0;
	CloseWareHouseFlag = 0;
	TradeCheckFlag = 0;
	cCaravan.SelectFlag = 0;
	if (TradeRequestFlag)
	{
		if (pCursorPos.x >= TRADEBUTTONMAIN_X + 138 && pCursorPos.x <= TRADEBUTTONMAIN_X + 138 + 16 && pCursorPos.y >= TRADEBUTTONMAIN_Y + 12 && pCursorPos.y <= TRADEBUTTONMAIN_Y + 12 + 16)
			RequestTradeButtonFlag = 1;
		if (pCursorPos.x >= TRADEBUTTONMAIN_X + 138 && pCursorPos.x <= TRADEBUTTONMAIN_X + 138 + 16 && pCursorPos.y >= TRADEBUTTONMAIN_Y + 33 && pCursorPos.y <= TRADEBUTTONMAIN_Y + 33 + 16)
			RequestTradeButtonFlag = 2;
		dwTradeDelayTime3++;
		if (dwTradeDelayTime3 >= 70 * 10)
		{
			TradeRequestFlag = 0;
			dwTradeDelayTime3 = 0;
		}
	}

	if (OpenFlag)
	{
		if (pCursorPos.x >= DownTradePosi[T_CHECK_POSI][0] && pCursorPos.x <= DownTradePosi[T_CHECK_POSI][2] && pCursorPos.y >= DownTradePosi[T_CHECK_POSI][1] && pCursorPos.y <= DownTradePosi[T_CHECK_POSI][3])
			TradeCheckFlag = T_CHECK_POSI;
		if (pCursorPos.x >= DownTradePosi[T_CLOSE_POSI][0] && pCursorPos.x <= DownTradePosi[T_CLOSE_POSI][2] && pCursorPos.y >= DownTradePosi[T_CLOSE_POSI][1] && pCursorPos.y <= DownTradePosi[T_CLOSE_POSI][3])
			TradeCheckFlag = T_CLOSE_POSI;
		if (pCursorPos.x >= DownTradePosi[T_MONEY_POSI][0] + 10 && pCursorPos.x <= DownTradePosi[T_MONEY_POSI][2] + 10 && pCursorPos.y >= DownTradePosi[T_MONEY_POSI][1] && pCursorPos.y <= DownTradePosi[T_MONEY_POSI][3])
			TradeCheckFlag = T_MONEY_POSI;

		PickUpTradeItem(pCursorPos.x, pCursorPos.y);
		if (MouseItem.bValid)
			SetTradeItemAreaCheck(&MouseItem);

		if (CheckDelayFlag)
		{
			dwTradeDelayTime++;
			if (dwTradeDelayTime >= 70 * 2)
			{
				CheckDelayFlag = 0;
				dwTradeDelayTime = 0;
			}
		}

		if (sTrade.CheckFlag && sTradeRecv.CheckFlag)
		{
			dwTradeDelayTime2++;
			if (dwTradeDelayTime2 >= 70 * 5)
			{
				dwTradeDelayTime2 = 0;
				sinCancelFlag = 1;
			}
		}
		else
			sinCancelFlag = 0;

		if (ItemPickUpFlag)
		{
			dwTradeDelayTime4++;
			if (dwTradeDelayTime4 > 70 * 2)
			{
				dwTradeDelayTime4 = 0;
				ItemPickUpFlag = 0;
			}
		}
	}

	if (cWareHouse.OpenFlag)
	{
		if (pCursorPos.x >= DownTradePosi[T_CLOSE_POSI][0] && pCursorPos.x <= DownTradePosi[T_CLOSE_POSI][2] && pCursorPos.y >= DownTradePosi[T_CLOSE_POSI][1] && pCursorPos.y <= DownTradePosi[T_CLOSE_POSI][3])
			CloseWareHouseFlag = 1;
		cWareHouse.PickUpWareHouseItem(pCursorPos.x, pCursorPos.y);

		if (MouseItem.bValid)
			cWareHouse.SetWareHouseItemAreaCheck(&MouseItem);
	}

	if (cCraftItem.OpenFlag || cAging.OpenFlag || SmeltingItem.OpenFlag || ManufactureItem.m_OpenFlag || cMixtureReset.OpenFlag || cElement.OpenFlag || cSocket.OpenFlag)
	{
		if (!MouseItem.bValid)
		{
			if (pCursorPos.x >= 158 && pCursorPos.x <= 158 + 26 && pCursorPos.y >= 222 + sinInterHeight2 && pCursorPos.y <= 222 + 26 + sinInterHeight2)
			{
				if (!MixCancelButtonDelayFlag)
					CraftItemButtonIndex = 1;
			}

			if (pCursorPos.x >= DownTradePosi[T_CLOSE_POSI][0] && pCursorPos.x <= DownTradePosi[T_CLOSE_POSI][2] && pCursorPos.y >= DownTradePosi[T_CLOSE_POSI][1] && pCursorPos.y <= DownTradePosi[T_CLOSE_POSI][3])
			{
				if (!MixCancelButtonDelayFlag)
					CraftItemButtonIndex = 2;
			}
		}
	}
	if (cCraftItem.OpenFlag)
	{
		if (MouseItem.bValid)
			cCraftItem.SetCraftItemAreaCheck(&MouseItem);
		else
			cCraftItem.PickUpCraftItem(pCursorPos.x, pCursorPos.y);
	}
	if (cAging.OpenFlag)
	{
		// ¶ÍÔìÎïÆ·¼ì²é
		if (MouseItem.bValid)
			cAging.SetAgingItemAreaCheck(&MouseItem);
		else
			cCraftItem.PickUpCraftItem(pCursorPos.x, pCursorPos.y, 0, 1);
	}
	if (SmeltingItem.OpenFlag)
	{
		if (MouseItem.bValid)
		{
			if ((MouseItem.sItem.sItemID.ToItemType()) == sinPR1 ||
				(MouseItem.sItem.sItemID.ToItemType()) == sinPR2)
			{
				if (S_smeltingItem.SmeltingItem[0].bValid && S_smeltingItem.SmeltingItem[0].sBaseItemID.ToInt() != MouseItem.sBaseItemID.ToInt())
					return;

				if (S_smeltingItem.SmeltingItem[0].bValid && S_smeltingItem.SmeltingItem[1].bValid && S_smeltingItem.SmeltingItem[2].bValid)
					return;
			}
			SmeltingItem.SetSmeltingItemAreaCheck(&MouseItem);
		}
		else
			SmeltingItem.PickUpSmeltingItem(pCursorPos.x, pCursorPos.y);
	}
	if (ManufactureItem.m_OpenFlag)
	{
		if (MouseItem.bValid)
			ManufactureItem.SetManufactureItemAreaCheck(&MouseItem);
		else
			ManufactureItem.PickUpManufactureItem(pCursorPos.x, pCursorPos.y);
	}
	if (cMixtureReset.OpenFlag)
	{
		if (MouseItem.bValid)
			cMixtureReset.SetMixtureItemResetAreaCheck(&MouseItem);
		else
			cMixtureReset.PickUpMixtureResetItem(pCursorPos.x, pCursorPos.y);
	}
	if (cElement.OpenFlag)
	{
		if (MouseItem.bValid)
			cElement.SetElementItemAreaCheck(&MouseItem);
		else
			cElement.PickUpElementItem(pCursorPos.x, pCursorPos.y);
	}
	if (cSocket.OpenFlag)
	{
		if (MouseItem.bValid)
			cSocket.SetSocketItemAreaCheck(&MouseItem);
		else
			cSocket.PickUpSocketItem(pCursorPos.x, pCursorPos.y, 0, 0);
	}
	if (cCaravan.OpenFlag)
	{
		if (MouseItem.bValid)
			cCaravan.SetCaravanItemAreaCheck(&MouseItem);
		else
		{
			if (pCursorPos.x >= DownTradePosi[T_CLOSE_POSI][0] && pCursorPos.x <= DownTradePosi[T_CLOSE_POSI][2] && pCursorPos.y >= DownTradePosi[T_CLOSE_POSI][1] && pCursorPos.y <= DownTradePosi[T_CLOSE_POSI][3])
				cCaravan.SelectFlag = 1;
			else if (pCursorPos.x > 230 && pCursorPos.x < 230 + 28 && pCursorPos.y > 90 + 177 + sinInterHeight2 && pCursorPos.y < 90 + 177 + sinInterHeight2 + 28)
				cCaravan.SelectFlag = 2;
			else if (pCursorPos.x > 265 && pCursorPos.x < 265 + 28 && pCursorPos.y > 90 + 177 + sinInterHeight2 && pCursorPos.y < 90 + 177 + sinInterHeight2 + 28)
				cCaravan.SelectFlag = 3;
			else if (pCursorPos.x > 300 && pCursorPos.x < 300 + 28 && pCursorPos.y > 90 + 177 + sinInterHeight2 && pCursorPos.y < 90 + 177 + sinInterHeight2 + 28)
				cCaravan.SelectFlag = 4;
			cCaravan.PickUpCaravanItem(pCursorPos.x, pCursorPos.y);
		}
		if (SETTINGHANDLE->Get().bDebugMode)
		{
			for (i = 0; i < 10; i++)
				CopyItemIndex8[i] = 0;
			for (i = 0; i < 100; i++)
			{
				if (cCaravan.sCaravan.Item[i].bValid)
				{
					for (j = 0; j < 100; j++)
					{
						if (cCaravan.sCaravan.Item[j].bValid)
						{
							if (i == j)
								continue;
							if (CompareItems(&cCaravan.sCaravan.Item[i].sItem, &cCaravan.sCaravan.Item[j].sItem))
							{
								for (int k = 0; k < 10; k++)
								{
									if (!CopyItemIndex8[k])
									{
										CopyItemIndex7[k] = i + 1;
										CopyItemIndex7[k + 1] = j + 1;
										break;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	if (ShowItemCraftMessageFlag || ShowItemAgingMessageFlag || ShowItemSmeltingMessageFlag || ShowItemManufactureMessageFlag || ShowItemOverSpace)
	{
		dwCraftItemInfoDelayTime++;
		if (dwCraftItemInfoDelayTime >= 70 * 10)
		{
			ShowItemCraftMessageFlag = 0;
			ShowItemAgingMessageFlag = 0;
			dwCraftItemInfoDelayTime = 0;
			ShowItemSmeltingMessageFlag = 0;
			ShowItemManufactureMessageFlag = 0;
			ShowItemOverSpace = 0;
		}
	}
	if (cWareHouse.OpenFlag)
		CloseWareHouseCheckFlag2 = 1;

	if (!CloseWareHouseCheckFlag3 && !cWareHouse.OpenFlag && CloseWareHouseCheckFlag2 == 1)
	{
		cWareHouse.RestoreInvenItem();
		CloseWareHouseCheckFlag3 = 0;
		CloseWareHouseCheckFlag2 = 0;
	}
}
void cTRADE::Close()
{

}
void cTRADE::LButtonDown(int x, int y)
{
	if (LbuttonUpCheckFlag)
		return;

	int i, TempFlag = 0;
	if (TradeCheckFlag == T_CHECK_POSI)
	{
		if (!MouseItem.bValid)
		{
			if (!CheckDelayFlag)
			{
				if (!ItemPickUpFlag)
				{
					if (CheckTradeItemSet())
					{
						sTrade.CheckFlag = 1;
						SendTradeItem(TradeCharCode);
						CheckTradeButtonOk();
					}
				}
			}
		}
	}
	if (TradeCheckFlag == T_CLOSE_POSI)
	{
		if (!dwTradeMaskTime || sinCancelFlag)
		{
			SendRequestTrade(TradeCharCode, 3);
			cTrade.OpenFlag = 0;
			cInvenTory.OpenFlag = 0;
			CancelTradeItem();
			sinCancelFlag = 0;
		}
	}
	if (RequestTradeButtonFlag == 2)
	{
		TradeRequestFlag = 0;
		TradeCharCode = 0;
		dwTradeDelayTime3 = 0;

	}
	if (RequestTradeButtonFlag == 1)
	{
		if (!MouseItem.bValid)
		{
			if (GetTradeDistanceFromCode(TradeCharCode) == TRUE)
				SendRequestTrade(TradeCharCode, 1);
			TradeRequestFlag = 0;
			dwTradeDelayTime3 = 0;
		}
	}
	if (cTrade.OpenFlag)
	{
		if (MouseItem.bValid && !sTrade.CheckFlag)
		{
			cInvenTory.CheckRequireItemToSet(&MouseItem);
			if (TradeColorIndex != NO_BOX_COLOR && TradeColorIndex != NOT_SETTING_COLOR)
				LastSetTradeItem(&MouseItem);
		}
		else
		{
			if (!TradeItemSucessFlag && !TradeSendSucessFlag && !sTrade.CheckFlag)
			{
				PickUpTradeItem(pCursorPos.x, pCursorPos.y, 1);
				if (TradeCheckFlag == T_MONEY_POSI && !sTrade.CheckFlag)
					cMessageBox.ShowMessage2(MESSAGE_MOVE_MONEY_TRADE);
			}
		}
	}
	if (cShop.OpenFlag)
	{
		if (MouseItem.bValid)
		{
			if (18 < MouseItem.iPlaceX &&
				18 + (22 * 10) > MouseItem.iPlaceX &&
				134 + sinInterHeight2 < MouseItem.iPlaceY &&
				134 + (22 * 10) + sinInterHeight2 > MouseItem.iPlaceY)
			{
				if ((MouseItem.sItem.sItemID.ToItemType()) == sinQT1 ||
					(MouseItem.sItem.sItemID.ToItemType()) == sinQW1 ||
					MouseItem.iItemSlotFlag == ITEMSLOTFLAG_Potion)
					TradeColorIndex = NOT_SETTING_COLOR;
				else
					TradeColorIndex = SET_ITEM_CHECK_COLOR;

				if (TradeColorIndex == SET_ITEM_CHECK_COLOR)
				{
					if (cShop.CheckHighRankItem(&MouseItem))
					{
						CURSORHANDLE->SetMouseCursor(ECURSORICON_Default);
						MouseItem.bValid = 0;
						ResetInvenItemCode();
						cMessageBox.ShowMessage3(MESSAGE_SELL_HIGHRANK_ITEM, MouseItem.sItem.szItemName);
					}
					else
						cShop.SellItemToShop(&MouseItem);
				}
			}
		}
	}
	if (CloseWareHouseFlag)
		cWareHouse.CloseWareHouse();
	if (cWareHouse.OpenFlag)
	{
		if (MouseItem.bValid)
		{
			cInvenTory.CheckRequireItemToSet(&MouseItem);
			if (TradeColorIndex == NO_BOX_COLOR || TradeColorIndex == NOT_SETTING_COLOR)
				return;
			if (!cWareHouse.ChangeWareHouseItem(&MouseItem))
				cWareHouse.LastSetWareHouseItem(&MouseItem);
		}
		else
			cWareHouse.PickUpWareHouseItem(pCursorPos.x, pCursorPos.y, 1);

		if (pCursorPos.x >= 231 && pCursorPos.x <= 231 + 20 && pCursorPos.y >= 213 + sinInterHeight2 && pCursorPos.y <= 213 + 20 + sinInterHeight2)
			cMessageBox.ShowMessage2(MESSAGE_MOVE_MONEY_RECV);

		/*if (pCursorPos.x > 314 && pCursorPos.x < 334 && pCursorPos.y > 194 && pCursorPos.y < 214)
			cWareHouse.Page[0] ++;
		if (pCursorPos.x > 234 && pCursorPos.x < 254 && pCursorPos.y > 194 && pCursorPos.y < 214)
			cWareHouse.Page[0] --;

		if (cWareHouse.Page[0] > 5)
			cWareHouse.Page[0] = 5;

		if (cWareHouse.Page[0] < 1)
			cWareHouse.Page[0] = 1;*/
	}

	int CloseButtonFlag = 0;
	int SheltomCount = 0;

	if (cCraftItem.OpenFlag)
	{
		if (MouseItem.bValid)
		{
			// ºÏ³É´ò¿ª
			if (cCraftItem.ForceFlag == NULL)
			{
				if (sCraftItem.CraftItem[0].bValid == NULL)
				{
					if ((MouseItem.sItem.sItemID.ToItemType()) == sinSE1)
					{
						cMessageBox.ShowMessage(MESSAGE_NOT_RECONITEM);
						TradeColorIndex = NOT_SETTING_COLOR;
					}
				}
			}
			if (TradeColorIndex != NO_BOX_COLOR || TradeColorIndex != NOT_SETTING_COLOR)
			{
				if (MouseItem.sItem.eCraftType == ITEMCRAFTTYPE_Aging || MouseItem.sItem.eCraftType == ITEMCRAFTTYPE_Mixing || MouseItem.sItem.iItemUniqueID)
				{
					if (cCraftItem.ForceFlag == NULL)
						cMessageBox.ShowMessage(MESSAGE_NOT_CRAFT_ITEM);
				}
				else
				{
					if (TradeColorIndex == NOT_ENOUGH_MONEY)
					{
						cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_MONEY);
						return;
					}
					cInvenTory.CheckRequireItemToSet(&MouseItem);

					if (MouseItem.sItem.sItemID.ToInt() == (sinBI1 | sin90))
					{
						if (159 + 11 <= MouseItem.iPlaceX + 22 && 159 + 11 > MouseItem.iPlaceX &&
							268 + 11 + sinInterHeight2 < MouseItem.iPlaceY + 22 &&
							268 + 11 + sinInterHeight2 > MouseItem.iPlaceY)
							TradeColorIndex = SET_ITEM_CHECK_COLOR;
					}
					if (TradeColorIndex == NO_BOX_COLOR || TradeColorIndex == NOT_SETTING_COLOR)
						return;
					cCraftItem.LastSetCraftItem(&MouseItem);
				}
			}
		}
		else
		{
			if (!StartInterEffectAging2 && !sinCraftItemStartFlag && !CheckMixItemCopyFlag)
			{
				if (!sinCraftItemStartFlag2 && !MixItemNoCopyFlag)
					cCraftItem.PickUpCraftItem(pCursorPos.x, pCursorPos.y, 1);

				if (CraftItemButtonIndex == 2)
				{
					SheltomCount = 0;
					if (sCraftItem.CraftItem[0].bValid)
					{
						for (i = 0; i < sCraftItem.CraftItem[0].iHeight / 22; i++)
							SheltomCount += sCraftItem.CraftItem[0].iWidth / 22;

						if (!cCraftItem.CraftCheckEmptyArea(&sCraftItem.CraftItem[0]))
							SheltomCount = 100;
					}
					for (i = 1; i < 15; i++)
					{
						if (sCraftItem.CraftItem[i].bValid)
						{
							if (cCraftItem.CraftCheckEmptyArea(&sCraftItem.CraftItem[i]))
								CloseButtonFlag = 0;
							else
							{
								CloseButtonFlag = 1;
								break;
							}
							SheltomCount++;
						}
					}
					if (!CloseButtonFlag && SheltomCount <= cCraftItem.GetCraftCheckEmptyArea())
						cCraftItem.CancelMixItem();
					else
						cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
				}
				if (CraftItemButtonIndex == 1)
				{
					if (cCraftItem.ForceFlag)
					{
						SheltomCount = 0;
						for (i = 1; i < 15; i++)
						{
							if (sCraftItem.CraftItem[i].bValid)
								SheltomCount++;
						}
						if (SheltomCount <= cCraftItem.GetCraftCheckEmptyArea())
							cCraftItem.sinSendCraftItem();
						else
							cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
					}
					else if (cCraftItem.haCheckReconItem())
					{
						if (sCraftItem.CraftItem[0].bValid && !sCraftItem.CraftItem[0].sItem.eCraftType)
						{
							for (i = 1; i < 15; i++)
							{
								if (sCraftItem.CraftItem[i].bValid)
									CopyMixItemCheckDelete(&sCraftItem.CraftItem[i - 1]);
							}

							if (cCraftItem.CraftCheckEmptyArea(&sCraftItem.CraftItem[0]))
							{
								if (!sinCraftItemStartFlag2)
								{
									sinCraftItemStartFlag = 1;
									SetInterEffectAging();
								}
							}
							else
								cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
						}
					}
					else
					{
						if (sCraftItem.CraftItem[0].bValid && !sCraftItem.CraftItem[0].sItem.eCraftType)
						{
							for (i = 1; i < 15; i++)
							{
								if (sCraftItem.CraftItem[i].bValid)
									CopyMixItemCheckDelete(&sCraftItem.CraftItem[i - 1]);
							}
							for (i = 1; i < 15; i++)
							{
								if (sCraftItem.CraftItem[i].bValid)
								{
									if (cCraftItem.CraftCheckEmptyArea(&sCraftItem.CraftItem[0]) && !sCraftItem.CraftItem[14].bValid)
									{
										if (!sinCraftItemStartFlag2)
										{
											sinCraftItemStartFlag = 1;
											SetInterEffectAging();
											TempFlag = 1;
											MixCancelButtonDelayFlag = 1;
											CheckMixItemCopyFlag = 1;
										}
									}
									else
									{
										if (sCraftItem.CraftItem[14].bValid)
											cMessageBox.ShowMessage(MESSAGE_CANNOT_RECONITEM);
										else
											cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);

										TempFlag = 1;
									}
								}
							}
							if (!TempFlag)
								cMessageBox.ShowMessage(MESSAGE_NOT_CRAFT_ITEM);
						}
						else
							cMessageBox.ShowMessage(MESSAGE_NOT_CRAFT_ITEM);
					}
				}
			}
		}
	}
	// ºÏ³É»Ø¸´°´Å¥
	if (cMixtureReset.OpenFlag)
	{
		if (MouseItem.bValid)
		{
			if (!sMixtureResetItem.MixtureResetItem[0].bValid)
			{
				if (MouseItem.sItem.sItemID.ToInt() == (sinBI1 | sin89) ||
					MouseItem.sItem.sItemID.ToInt() == (sinBI2 | sin48) ||
					MouseItem.sItem.sItemID.ToInt() == (sinBI2 | sin49))
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_MIXTURE_RESET_STONE);
					TradeColorIndex = NOT_SETTING_COLOR;
				}
			}
			if (TradeColorIndex != NO_BOX_COLOR && TradeColorIndex != NOT_SETTING_COLOR)
			{
				if (MouseItem.sItem.sItemID.ToInt() == (sinBI1 | sin89) ||
					MouseItem.sItem.sItemID.ToInt() == (sinBI2 | sin48) ||
					MouseItem.sItem.sItemID.ToInt() == (sinBI2 | sin49))
				{
					cMixtureReset.LastSetMixtureResetItem(&MouseItem, 1);
					MixtureResetCheckFlag = 1;
				}
				else if (MouseItem.sItem.eCraftType == ITEMCRAFTTYPE_Mixing || (MouseItem.sItem.eCraftType == ITEMCRAFTTYPE_Aging && MouseItem.sItem.sMatureBar.sMax == 0))
					cMixtureReset.LastSetMixtureResetItem(&MouseItem, 2);
			}
		}
		else
		{
			if (!StartInterEffectAging2 && !sinCraftItemStartFlag)
			{
				if (!sinCraftItemStartFlag2)
					cMixtureReset.PickUpMixtureResetItem(pCursorPos.x, pCursorPos.y, 1);

				if (CraftItemButtonIndex == 2)
				{
					CloseButtonFlag = 0;
					SheltomCount = 0;

					if (sMixtureResetItem.MixtureResetItem[0].bValid)
					{
						for (int i = 0; i < sMixtureResetItem.MixtureResetItem[0].iHeight / 22; i++)
							SheltomCount += sMixtureResetItem.MixtureResetItem[0].iWidth / 22;

						if (!cCraftItem.CraftCheckEmptyArea(&sMixtureResetItem.MixtureResetItem[0]))
							SheltomCount = 100;
					}
					if (sMixtureResetItem.MixtureResetItem[1].bValid)
					{
						if (cCraftItem.CraftCheckEmptyArea(&sMixtureResetItem.MixtureResetItem[1]))
							CloseButtonFlag = 0;
						else
							CloseButtonFlag = 1;
						SheltomCount++;
					}
					if (!CloseButtonFlag && SheltomCount <= cCraftItem.GetCraftCheckEmptyArea())
						cMixtureReset.CancelMixtureItemReset();
					else
						cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
				}
				if (CraftItemButtonIndex == 1 && sMixtureResetItem.MixtureResetItem[1].bValid)
				{
					if (cCraftItem.CraftCheckEmptyArea(&sMixtureResetItem.MixtureResetItem[0]))
					{
						if (!sinCraftItemStartFlag2)
						{
							sinCraftItemStartFlag = 1;
							SetInterEffectMixtureReset();
							MixCancelButtonDelayFlag = 1;
							MixtureResetCheckFlag = 0;
						}
					}
					else
						cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
				}
			}
		}
	}

	if (cAging.OpenFlag)
	{
		if (MouseItem.bValid)
		{
			if (TradeColorIndex == NOT_AGING_ITEM)
			{
				cMessageBox.ShowMessage(MESSAGE_NOT_AGING_ITEM);
			}
			else
			{
				if (TradeColorIndex == NOT_ENOUGH_MONEY)
					cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_MONEY);
				if (TradeColorIndex != NO_BOX_COLOR && TradeColorIndex != NOT_SETTING_COLOR && TradeColorIndex != NOT_ENOUGH_MONEY)
				{
					if ((MouseItem.sItem.sItemID.ToItemType()) == sinMA1 ||
						(MouseItem.sItem.sItemID.ToItemType()) == sinMA2)
					{
						cCraftItem.LastSetCraftItem(&MouseItem, 2);
						sinMakeItemCheck();
					}
					else if (MouseItem.sItem.sItemID.ToInt() == (sinBI1 | sin10) ||
						MouseItem.sItem.sItemID.ToInt() == (sinBI1 | sin11) ||
						MouseItem.sItem.sItemID.ToInt() == (sinBI2 | sin66) ||
						MouseItem.sItem.sItemID.ToInt() == (sinBI2 | sin67) ||
						MouseItem.sItem.sItemID.ToInt() == (sinBI2 | sin68) ||
						MouseItem.sItem.sItemID.ToInt() == (sinBI2 | sin78) ||
						MouseItem.sItem.sItemID.ToInt() == (sinBI2 | sin79) ||
						MouseItem.sItem.sItemID.ToInt() == (sinBI2 | sin80) ||
						MouseItem.sItem.sItemID.ToInt() == (sinBI2 | sin81))
					{
						if (!StartInterEffectAging2 && !sinCraftItemStartFlag)
							cCraftItem.LastSetCraftItem(&MouseItem, 3);
					}
					else
					{
						cCraftItem.LastSetCraftItem(&MouseItem, 1);
						cAging.CheckItem(&MouseItem);
					}
				}
			}
		}
		else
		{
			if (!StartInterEffectAging2 && !sinCraftItemStartFlag)
			{
				if (!sinCraftItemStartFlag2)
					cCraftItem.PickUpCraftItem(pCursorPos.x, pCursorPos.y, 1, 1);
				if (CraftItemButtonIndex == 2)
				{
					SheltomCount = 0;
					CloseButtonFlag = 0;

					if (sAgingItem.AgingItem[0].bValid)
					{
						for (i = 0; i < sAgingItem.AgingItem[0].iHeight / 22; i++)
							SheltomCount += sAgingItem.AgingItem[0].iWidth / 22;

						if (!cCraftItem.CraftCheckEmptyArea(&sAgingItem.AgingItem[0]))
							SheltomCount = 100;
					}
					for (i = 1; i < 15; i++)
					{
						if (sAgingItem.AgingItem[i].bValid)
						{
							if (cCraftItem.CraftCheckEmptyArea(&sAgingItem.AgingItem[i]))
								CloseButtonFlag = 0;
							else
							{
								CloseButtonFlag = 1;
								break;
							}
							SheltomCount++;
						}
					}
					if (!CloseButtonFlag && SheltomCount <= cCraftItem.GetCraftCheckEmptyArea())
						cAging.CancelAgingItem();
					else
						cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
				}
				if (CraftItemButtonIndex == 1 && AgingCheckSheltomFlag)
				{
					if (cCraftItem.CraftCheckEmptyArea(&sAgingItem.AgingItem[0]))
					{
						if (!sinCraftItemStartFlag2)
						{
							sinCraftItemStartFlag = 1;
							SetInterEffectAging();
							MixCancelButtonDelayFlag = 1;
						}
					}
					else
						cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
				}
			}
		}
	}
	if (SmeltingItem.OpenFlag)
	{
		if (MouseItem.bValid)
		{
			if (TradeColorIndex == NO_BOX_COLOR || TradeColorIndex == NOT_SETTING_COLOR)
			{
				return;
			}
			if ((MouseItem.sItem.sItemID.ToItemType()) == sinPR1 ||
				(MouseItem.sItem.sItemID.ToItemType()) == sinPR2)
			{
				if (S_smeltingItem.SmeltingItem[0].bValid && S_smeltingItem.SmeltingItem[0].sBaseItemID.ToInt() != MouseItem.sBaseItemID.ToInt())
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_SAME_SMELTINGITEM);
					return;
				}

				if (S_smeltingItem.SmeltingItem[0].bValid && S_smeltingItem.SmeltingItem[1].bValid && S_smeltingItem.SmeltingItem[2].bValid)
					return;

			}
			if (TradeColorIndex == NOT_ENOUGH_MONEY)
			{
				cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_MONEY);
				return;
			}
			SmeltingItem.LastSetSmeltingItem(&MouseItem);
		}
		else
		{
			if (!StartInterEffectAging2 && !sinCraftItemStartFlag && !CheckMixItemCopyFlag)
			{
				if (!sinCraftItemStartFlag2 && !MixCancelButtonDelayFlag)
					SmeltingItem.PickUpSmeltingItem(pCursorPos.x, pCursorPos.y, 1);

				if (CraftItemButtonIndex == 2)
				{
					for (i = 0; i < 5; i++)
					{
						if (S_smeltingItem.SmeltingItem[i].bValid)
						{
							if (SmeltingItem.SmeltingCheckEmptyArea(&S_smeltingItem.SmeltingItem[i]))
								CloseButtonFlag = 0;
							else
							{
								CloseButtonFlag = 1;
								break;
							}
							SheltomCount++;
						}
					}
					if (!CloseButtonFlag && SheltomCount <= SmeltingItem.GetSmeltingCheckEmptyArea())
						SmeltingItem.CancelSmeltingItem();
					else
					{
						int LineCount = 0, Temp;
						ShowItemOverSpace = 1;

						lstrcpy(szCraftItemBuff, "There is not enough space");

						lstrcat(szCraftItemBuff, "\r");
						Temp = lstrlen(szCraftItemBuff);
						for (i = 0; i < Temp; i++)
						{
							if (szCraftItemBuff[i] == '\r')
								LineCount++;
						}
						CraftItemMessageSize.x = 14;
						CraftItemMessageSize.y = ((LineCount) * 2) + 2;
						sinPlaySound(SIN_SOUND_FAILD_MIXITEM);
					}
				}
				else if (CraftItemButtonIndex == 1)
				{
					if (S_smeltingItem.SmeltingItem[0].bValid && !S_smeltingItem.SmeltingItem[0].sItem.eCraftType &&
						S_smeltingItem.SmeltingItem[1].bValid && !S_smeltingItem.SmeltingItem[1].sItem.eCraftType &&
						S_smeltingItem.SmeltingItem[2].bValid && !S_smeltingItem.SmeltingItem[2].sItem.eCraftType)
					{
						ItemData * pItemData = ITEMHANDLE->GetItemDataByID(sinPR1 | sin01);

						ItemData sTempItemData;
						if (pItemData)
						{
							CopyMemory(&sTempItemData, pItemData, sizeof(ItemData));

							if (cInvenTory.CheckInvenEmpty(&sTempItemData))
							{
								if (S_smeltingItem.SmeltingItem[4].bValid)
								{
									if (!sinCraftItemStartFlag2)
									{
										sinCraftItemStartFlag = 1;
										SetInterEffectSmelting();
										MixCancelButtonDelayFlag = 1;
									}
								}
							}
							else
								cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
						}
					}
				}
			}
		}
	}

	if (ManufactureItem.m_OpenFlag)
	{
		if (MouseItem.bValid)
		{
			if (TradeColorIndex == NOT_SETTING_COLOR)
				return;
			else if (TradeColorIndex == NO_BOX_COLOR)
			{
				cMessageBox.ShowMessage(MESSAGE_NOT_NEED_RUNE);
				return;
			}
			else if (TradeColorIndex == NOT_ENOUGH_MONEY)
			{
				cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_MONEY);
				return;
			}
			ManufactureItem.LastSetManufactureItem(&MouseItem);
		}
		else
		{
			if (!StartInterEffectAging2 && !sinCraftItemStartFlag && !CheckMixItemCopyFlag)
			{
				if (!sinCraftItemStartFlag2 && !MixCancelButtonDelayFlag)
					ManufactureItem.PickUpManufactureItem(pCursorPos.x, pCursorPos.y, 1);

				if (CraftItemButtonIndex == 2)
				{
					CloseButtonFlag = 0;
					for (i = 0; i < 4; i++)
					{
						if (sManufactureItem.ManufactureItem[i].bValid)
						{
							if (ManufactureItem.ManufactureCheckEmptyArea(&sManufactureItem.ManufactureItem[i]))
								CloseButtonFlag = 0;
							else
							{
								CloseButtonFlag = 1;
								break;
							}
							SheltomCount++;
						}
					}
					if (!CloseButtonFlag && SheltomCount <= ManufactureItem.GetManufactureCheckEmptyArea())
						ManufactureItem.CancelManufactureItem();
					else
					{
						int LineCount = 0, Temp;
						ShowItemOverSpace = 1;
						lstrcpy(szCraftItemBuff, "There is not enough space");

						lstrcat(szCraftItemBuff, "\r");
						Temp = lstrlen(szCraftItemBuff);
						for (i = 0; i < Temp; i++)
						{
							if (szCraftItemBuff[i] == '\r')
								LineCount++;
						}
						CraftItemMessageSize.x = 14;
						CraftItemMessageSize.y = ((LineCount) * 2) + 2;
						sinPlaySound(SIN_SOUND_FAILD_MIXITEM);
					}
				}
				else if (CraftItemButtonIndex == 1)
				{
					if (sManufactureItem.ManufactureItem[0].bValid && !sManufactureItem.ManufactureItem[0].sItem.eCraftType)
					{
						if (sManufactureItem.ManufactureItem[1].bValid && sManufactureItem.ManufactureItem[2].bValid && sManufactureItem.ManufactureItem[3].bValid)
						{
							SManufacture_ResultItemInfo ResultItem;
							memset(&ResultItem, 0, sizeof(SManufacture_ResultItemInfo));

							ResultItem = ManufactureItem.ManufactureCheckItem(sManufactureItem.ManufactureItem, sinChar);

							ItemData * pItemData = ITEMHANDLE->GetItemDataByID(ResultItem.ItemCode);
							
							ItemData sTempItemData;

							if (pItemData)
							{
								CopyMemory(&sTempItemData, pItemData, sizeof(ItemData));

								if (cInvenTory.CheckInvenEmpty(&sTempItemData))
								{
									if (sinChar->sWeight.sMin + ResultItem.Weight <= sinChar->sWeight.sMax)
									{
										if (ForceItemPrice2 <= sinChar->iGold)
										{
											if (!sinCraftItemStartFlag2)
												cMessageBox.ShowMessage3(MESSAGE_MANUFACTURE, ResultItem.ItemName);
										}
										else
											cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_MONEY);
									}
									else
										cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
								}
								else
									cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
							}
						}
					}
				}
			}
		}
	}
	// ÊôÐÔÏµÍ³
	if (cElement.OpenFlag)
	{
		if (MouseItem.bValid)
		{
			if (!cElement.ElementItem[0].bValid)
			{
				if ((MouseItem.sItem.sItemID.ToItemType()) == sinOS1 ||
					(MouseItem.sItem.sItemID.ToItemType()) == sinBI1)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_MIXTURE_RESET_STONE);
					TradeColorIndex = NOT_SETTING_COLOR;
				}
			}
			if (TradeColorIndex == NOT_ENOUGH_MONEY)
			{
				cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_MONEY);
				TradeColorIndex = NOT_SETTING_COLOR;
			}
			if (TradeColorIndex != NO_BOX_COLOR && TradeColorIndex != NOT_SETTING_COLOR)
			{
				switch (MouseItem.sItem.sItemID.ToItemType())
				{
				case sinES1:
					cElement.LastSetElementItem(&MouseItem, 2);
					break;
				case sinSS1:
					cElement.LastSetElementItem(&MouseItem, 1);
					break;
				default:
					cElement.LastSetElementItem(&MouseItem);
					break;
				}
				cElement.CheckItem();
			}
		}
		else
		{
			if (!StartInterEffectAging2 && !sinCraftItemStartFlag)
			{
				if (!sinCraftItemStartFlag2)
					cElement.PickUpElementItem(pCursorPos.x, pCursorPos.y, TRUE);

				switch (CraftItemButtonIndex)
				{
				case 1:
					if (cElement.ElementCheckFlag)
					{
						if (cCraftItem.CraftCheckEmptyArea(&cElement.ElementItem[0]))
						{
							if (!sinCraftItemStartFlag2)
							{
								sinCraftItemStartFlag = 1;
								SetInterEffectElement();
								MixCancelButtonDelayFlag = TRUE;
								cElement.ElementCheckFlag = FALSE;
							}
						}
						else
							cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
					}
					break;
				case 2:
					CloseButtonFlag = 0;
					SheltomCount = 0;

					if (cElement.ElementItem[0].bValid)
					{
						for (i = 0; i < cElement.ElementItem[0].iHeight / 22; i++)
							SheltomCount += cElement.ElementItem[0].iWidth / 22;

						if (cCraftItem.CraftCheckEmptyArea(&cElement.ElementItem[0]) == NULL)
							SheltomCount = 100;
					}
					for (i = 1; i < 6; i++)
					{
						if (cElement.ElementItem[i].bValid)
						{
							if (cCraftItem.CraftCheckEmptyArea(&cElement.ElementItem[i]))
								CloseButtonFlag = 0;
							else
							{
								CloseButtonFlag = 1;
								break;
							}
							SheltomCount++;
						}
					}
					if (CloseButtonFlag == NULL && SheltomCount <= cCraftItem.GetCraftCheckEmptyArea())
						cElement.CancelElementItem();
					else
						cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
					break;
				}
			}
		}
	}
	// ´ò¿×ÏµÍ³
	if (cSocket.OpenFlag)
	{
		if (MouseItem.bValid)
		{
			if (!cSocket.SocketItem[0].bValid)
			{
				if ((MouseItem.sItem.sItemID.ToItemType()) == sinOS1 ||
					(MouseItem.sItem.sItemID.ToItemType()) == sinBI1)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_MIXTURE_RESET_STONE);
					TradeColorIndex = NOT_SETTING_COLOR;
				}
			}
			if (TradeColorIndex == NOT_ENOUGH_MONEY)
			{
				cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_MONEY);
				TradeColorIndex = NOT_SETTING_COLOR;
			}
			if (TradeColorIndex != NO_BOX_COLOR && TradeColorIndex != NOT_SETTING_COLOR)
			{
				switch (MouseItem.sItem.sItemID.ToItemType())
				{
				case sinSR1:
					cSocket.LastSetSocketItem(&MouseItem, 1);
					break;
				default:
					cSocket.LastSetSocketItem(&MouseItem, 0);
					break;
				}
				cSocket.CheckItem();
			}
		}
		else
		{
			if (!StartInterEffectAging2 && !sinCraftItemStartFlag)
			{
				if (!sinCraftItemStartFlag2)
					cSocket.PickUpSocketItem(pCursorPos.x, pCursorPos.y, TRUE, 0);

				switch (CraftItemButtonIndex)
				{
				case 1:
					if (cSocket.SocketCheckFlag)
					{
						if (cCraftItem.CraftCheckEmptyArea(&cSocket.SocketItem[0]))
						{
							if (!sinCraftItemStartFlag2)
							{
								sinCraftItemStartFlag = 1;
								SetInterEffectElement();
								MixCancelButtonDelayFlag = TRUE;
								cSocket.SocketCheckFlag = FALSE;
							}
							else
								cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
						}
					}
					break;
				case 2:
					CloseButtonFlag = 0;
					SheltomCount = 0;

					if (cSocket.SocketItem[0].bValid)
					{
						for (i = 0; i < cSocket.SocketItem[0].iHeight / 22; i++)
							SheltomCount += cSocket.SocketItem[0].iWidth / 22;

						if (cCraftItem.CraftCheckEmptyArea(&cSocket.SocketItem[0]) == NULL)
							SheltomCount = 100;
					}
					for (i = 1; i < 5; i++)
					{
						if (cSocket.SocketItem[i].bValid)
						{
							if (cCraftItem.CraftCheckEmptyArea(&cSocket.SocketItem[i]))
								CloseButtonFlag = 0;
							else
							{
								CloseButtonFlag = 1;
								break;
							}
							SheltomCount++;
						}
					}

					if (CloseButtonFlag == NULL && SheltomCount <= cCraftItem.GetCraftCheckEmptyArea())
						cSocket.CancelSocketItem(0);
					else
						cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
					break;
				}
			}
		}
	}
	// ³èÎï²Ö¿â
	if (cCaravan.OpenFlag)
	{
		// Êó±êµãÆðÀ´
		if (MouseItem.bValid)
		{
			cInvenTory.CheckRequireItemToSet(&MouseItem);
			if (TradeColorIndex == NO_BOX_COLOR || TradeColorIndex == NOT_SETTING_COLOR)
				return;
			if (!cCaravan.ChangeCaravanItem(&MouseItem))
				cCaravan.LastSetCaravanItem(&MouseItem);
		}
		else
		{
			cCaravan.PickUpCaravanItem(pCursorPos.x, pCursorPos.y, TRUE);
			switch (cCaravan.SelectFlag)
			{
			case 1:
				cCaravan.CloseCaravan();
				break;
			case 2:
				cCaravan.SetHopySelect(TRUE);
				break;
			case 3:
				cCaravan.SetHopySelect(FALSE);
				break;
			case 4:
				break;
			}
		}
	}
}
void cTRADE::LButtonUp(int x, int y)
{

}
void cTRADE::RButtonDown(int x, int y)
{
	if (MouseItem.bValid == NULL)
	{
		ItemData *pItem;
		if (cTrade.OpenFlag)
		{
			if (SelectInvenItemIndex)
			{
				pItem = &cInvenTory.InvenItem[SelectInvenItemIndex - 1];
				if (pItem && cTrade.SetTradeItem(pItem) && sTrade.CheckFlag == NULL)
				{
					CheckInvenItemStatus(pItem);
					pItem->iItemSlot = 0;
					LastSetTradeItem(pItem);
					ReFormInvenItemStatus();
				}
			}
			else
			{
				if (TradeItemSucessFlag == NULL && TradeSendSucessFlag == NULL && sTrade.CheckFlag == NULL)
					PickUpTradeItem(pCursorPos.x, pCursorPos.y, 2);
			}
		}
		if (cShop.OpenFlag)
		{
			if (SelectInvenItemIndex)
			{
				pItem = &cInvenTory.InvenItem[SelectInvenItemIndex - 1];
				if (pItem && ((pItem->sItem.sItemID.ToItemType()) != sinQT1 && (pItem->sItem.sItemID.ToItemType()) != sinQW1 && pItem->iItemSlotFlag != ITEMSLOTFLAG_Potion))
				{
					CheckInvenItemStatus(pItem);
					pItem->iItemSlot = 0;

					if (cShop.CheckHighRankItem(pItem))
					{
						CURSORHANDLE->SetMouseCursor(ECURSORICON_Default);
						pItem->bValid = 0;
						memcpy(&MouseItem, pItem, sizeof(ItemData));
						ResetInvenItemCode();
						cMessageBox.ShowMessage3(MESSAGE_SELL_HIGHRANK_ITEM, pItem->sItem.szItemName);
					}
					else
						cShop.SellItemToShop(pItem);
					ReFormInvenItemStatus();
				}
			}
		}
		if (cWareHouse.OpenFlag)
		{
			if (SelectInvenItemIndex)
			{
				pItem = &cInvenTory.InvenItem[SelectInvenItemIndex - 1];
				if (pItem && cWareHouse.SetWareHouseItem(pItem))
				{
					CheckInvenItemStatus(pItem);
					pItem->iItemSlot = 0;
					if (cWareHouse.ChangeWareHouseItem(pItem) == FALSE)
						cWareHouse.LastSetWareHouseItem(pItem);
					ReFormInvenItemStatus();
				}
			}
			else
				cWareHouse.PickUpWareHouseItem(pCursorPos.x, pCursorPos.y, 2);
		}
		if (cCraftItem.OpenFlag)
		{
			if (SelectInvenItemIndex)
			{
				pItem = &cInvenTory.InvenItem[SelectInvenItemIndex - 1];
				if (pItem && cCraftItem.SetCraftItem(pItem))
				{
					CheckInvenItemStatus(pItem);
					pItem->iItemSlot = 0;
					cCraftItem.LastSetCraftItem(pItem);
					ReFormInvenItemStatus();
				}
			}
			else
				cCraftItem.PickUpCraftItem(pCursorPos.x, pCursorPos.y, 2, 0);
		}
		if (cAging.OpenFlag)
		{
			if (SelectInvenItemIndex)
			{
				pItem = &cInvenTory.InvenItem[SelectInvenItemIndex - 1];
				if (pItem && cAging.SetAgingItem(pItem))
				{
					CheckInvenItemStatus(pItem);
					pItem->iItemSlot = 0;
					if ((pItem->sItem.sItemID.ToItemType()) == sinMA1 ||
						(pItem->sItem.sItemID.ToItemType()) == sinMA2)
					{
						cCraftItem.LastSetCraftItem(pItem, 2);
						sinMakeItemCheck();
					}
					else if (pItem->sItem.sItemID.ToInt() == (sinBI1 | sin10) ||
						pItem->sItem.sItemID.ToInt() == (sinBI1 | sin11) ||
						pItem->sItem.sItemID.ToInt() == (sinBI2 | sin66) ||
						pItem->sItem.sItemID.ToInt() == (sinBI2 | sin67) ||
						pItem->sItem.sItemID.ToInt() == (sinBI2 | sin68) ||
						pItem->sItem.sItemID.ToInt() == (sinBI2 | sin78) ||
						pItem->sItem.sItemID.ToInt() == (sinBI2 | sin79) ||
						pItem->sItem.sItemID.ToInt() == (sinBI2 | sin80) ||
						pItem->sItem.sItemID.ToInt() == (sinBI2 | sin81))
					{
						if (!StartInterEffectAging2 && !sinCraftItemStartFlag)
							cCraftItem.LastSetCraftItem(pItem, 3);
					}
					else
					{
						cAging.CheckItem(pItem);
						cCraftItem.LastSetCraftItem(pItem, 1);
					}
					ReFormInvenItemStatus();
				}
			}
			else
				cCraftItem.PickUpCraftItem(pCursorPos.x, pCursorPos.y, 2, 1);
		}
		if (cMixtureReset.OpenFlag)
		{
			if (SelectInvenItemIndex)
			{
				pItem = &cInvenTory.InvenItem[SelectInvenItemIndex - 1];
				if (pItem && cMixtureReset.SetMixtureItemReset(pItem))
				{
					CheckInvenItemStatus(pItem);
					pItem->iItemSlot = 0;
					if (pItem->sItem.sItemID.ToInt() == (sinBI1 | sin89) ||
						pItem->sItem.sItemID.ToInt() == (sinBI2 | sin48) ||
						pItem->sItem.sItemID.ToInt() == (sinBI2 | sin49))
					{
						cMixtureReset.LastSetMixtureResetItem(pItem, 1);
						MixtureResetCheckFlag = 1;
					}
					else if (pItem->sItem.eCraftType == ITEMCRAFTTYPE_Mixing || (pItem->sItem.eCraftType == ITEMCRAFTTYPE_Aging && pItem->sItem.sMatureBar.sMax == 0))
						cMixtureReset.LastSetMixtureResetItem(pItem, 2);

					ReFormInvenItemStatus();
				}
			}
			else
				cMixtureReset.PickUpMixtureResetItem(pCursorPos.x, pCursorPos.y, 2);
		}
		if (cElement.OpenFlag)
		{
			if (SelectInvenItemIndex)
			{
				pItem = &cInvenTory.InvenItem[SelectInvenItemIndex - 1];
				if (pItem && cElement.SetElementItem(pItem))
				{
					CheckInvenItemStatus(pItem);
					pItem->iItemSlot = 0;
					switch (pItem->sItem.sItemID.ToItemType())
					{
					case sinES1:
						cElement.LastSetElementItem(pItem, 2);
						break;
					case sinSS1:
						cElement.LastSetElementItem(pItem, 1);
						break;
					default:
						cElement.LastSetElementItem(pItem);
						break;
					}
					cElement.CheckItem();
					ReFormInvenItemStatus();
				}
			}
			else
				cElement.PickUpElementItem(pCursorPos.x, pCursorPos.y, 2);
		}
		if (cSocket.OpenFlag)
		{
			if (SelectInvenItemIndex)
			{
				pItem = &cInvenTory.InvenItem[SelectInvenItemIndex - 1];
				if (pItem && cSocket.SetSocketItem(pItem))
				{
					CheckInvenItemStatus(pItem);
					pItem->iItemSlot = 0;
					switch (pItem->sItem.sItemID.ToItemType())
					{
					case sinSR1:
						cSocket.LastSetSocketItem(pItem, 1);
						break;
					default:
						cSocket.LastSetSocketItem(pItem, 0);
						break;
					}
					cSocket.CheckItem();
					ReFormInvenItemStatus();
				}
			}
			else
				cSocket.PickUpSocketItem(pCursorPos.x, pCursorPos.y, 2, 0);
		}
		if (cCaravan.OpenFlag)
		{
			if (SelectInvenItemIndex)
			{
				pItem = &cInvenTory.InvenItem[SelectInvenItemIndex - 1];
				if (pItem && cCaravan.SetCaravanItem(pItem))
				{
					CheckInvenItemStatus(pItem);
					pItem->iItemSlot = 0;
					if (cCaravan.ChangeCaravanItem(pItem) == FALSE)
						cCaravan.LastSetCaravanItem(pItem);
					ReFormInvenItemStatus();
				}
			}
			else
				cCaravan.PickUpCaravanItem(pCursorPos.x, pCursorPos.y, 2);
		}
	}
}
void cTRADE::RButtonUp(int x, int y)
{

}
void cTRADE::KeyDown()
{

}
void cTRADE::DrawTradeText()
{
	if (ShowItemAgingMessageFlag || ShowItemCraftMessageFlag || TradeRequestFlag || ShowItemSmeltingMessageFlag || ShowItemManufactureMessageFlag || ShowItemOverSpace || sinMoveKindInter[SIN_TRADE] || sinMoveKindInter[SIN_CRAFTITEM] || sinMoveKindInter[SIN_WAREHOUSE] || sinMoveKindInter[SIN_AGING] || sinMoveKindInter[SIN_SMELTING] || sinMoveKindInter[SIN_MANUFACTURE] || sinMoveKindInter[SIN_ELEMENT] || sinMoveKindInter[SIN_CARAVAN])
	{
		int i;

		char strBuff[128];

		memset(strBuff, 0, sizeof(strBuff));

		if (TradeRequestFlag)
		{
			if (cTrade.szTradeCharName[0])
			{
				lstrcpy(strBuff, cTrade.szTradeCharName);
				dsTextLineOut(0, TRADEBUTTONMAIN_X + 38, TRADEBUTTONMAIN_Y + 17, strBuff, lstrlen(strBuff), D3DCOLOR_XRGB(255, 255, 255));
			}
		}
		if (cWareHouse.OpenFlag)
		{
			memset(strBuff, 0, sizeof(strBuff));
			//NumLineComa(sWareHouse.Money-2023,strBuff);
			NumLineComa(cWareHouse.Money, strBuff);
			dsTextLineOut(0, CheckEditSize(ShopGoldEdit[0][0], ShopGoldEdit[0][2], strBuff) - (256 + 128 - sinMoveKindInter[SIN_WAREHOUSE]), ShopGoldEdit[0][1], strBuff, lstrlen(strBuff), D3DCOLOR_XRGB(255, 255, 255));

			memset(strBuff, 0, sizeof(strBuff));
			wsprintf(strBuff, "%d/%d", cWareHouse.Weight[0], cWareHouse.Weight[1]);
			dsTextLineOut(0, CheckEditSize(ShopGoldEdit[1][0], ShopGoldEdit[1][2], strBuff) - (256 + 128 - sinMoveKindInter[SIN_WAREHOUSE]), ShopGoldEdit[1][1], strBuff, lstrlen(strBuff), D3DCOLOR_XRGB(255, 255, 255));

			for (i = 0; i < 100; i++)
			{
				if (cWareHouse.WareHouse.WareHouseItem[i].bValid)
				{
					if (cWareHouse.WareHouse.WareHouseItem[i].iItemSlotFlag == ITEMSLOTFLAG_Potion)
					{
						wsprintf(strBuff, "%d", cWareHouse.WareHouse.WareHouseItem[i].sItem.iPotionCount);
						dsTextLineOut(0,
							cWareHouse.WareHouse.WareHouseItem[i].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_WAREHOUSE]),
							cWareHouse.WareHouse.WareHouseItem[i].iPlaceY,
							strBuff,
							lstrlen(strBuff),
							D3DCOLOR_XRGB(255, 255, 255));
					}
				}
			}
		}

		if (OpenFlag)
		{
			lstrcpy(strBuff, cTrade.szTradeCharName);
			dsTextLineOut(0, CheckEditSize(229, 332, strBuff) - (256 + 128 - sinMoveKindInter[SIN_TRADE]), 94, strBuff, lstrlen(strBuff), D3DCOLOR_XRGB(255, 255, 255));

			if (sTradeRecv.Weight > 0)
			{
				wsprintf(strBuff, "%d", sTradeRecv.Weight);
				dsTextLineOut(0, CheckEditSize(251, 326, strBuff) - (256 + 128 - sinMoveKindInter[SIN_TRADE]), 152, strBuff, lstrlen(strBuff), D3DCOLOR_XRGB(255, 255, 255));
			}

			if (sTradeRecv.Money > 0)
			{
				memset(strBuff, 0, sizeof(strBuff));
				NumLineComa(sTradeRecv.Money - 193, strBuff);
				dsTextLineOut(0, CheckEditSize(251, 326, strBuff) - (256 + 128 - sinMoveKindInter[SIN_TRADE]), 127, strBuff, lstrlen(strBuff), D3DCOLOR_XRGB(255, 255, 255));
			}

			memset(strBuff, 0, sizeof(strBuff));
			wsprintf(strBuff, "%d", sTrade.Weight);
			dsTextLineOut(0, CheckEditSize(DownTradePosi[T_WEIGHT_TEXT_POSI][0], DownTradePosi[T_WEIGHT_TEXT_POSI][2], strBuff) - 2 - (256 + 128 - sinMoveKindInter[SIN_TRADE]), DownTradePosi[T_WEIGHT_TEXT_POSI][1] + 5 + 2, strBuff, lstrlen(strBuff), D3DCOLOR_XRGB(255, 255, 255));

			memset(strBuff, 0, sizeof(strBuff));
			NumLineComa(TempShowMoney, strBuff);
			dsTextLineOut(0, CheckEditSize(DownTradePosi[T_MONEY_TEXT_POSI][0], DownTradePosi[T_MONEY_TEXT_POSI][2], strBuff) - 2 - (256 + 128 - sinMoveKindInter[SIN_TRADE]), DownTradePosi[T_MONEY_TEXT_POSI][1] + 5 + 2 + 2, strBuff, lstrlen(strBuff), D3DCOLOR_XRGB(255, 255, 255));

			for (int i = 0; i < MAX_TRADE_ITEM; i++)
			{
				if (sTrade.TradeItem[i].bValid)
				{
					if (sTrade.TradeItem[i].iItemSlotFlag == ITEMSLOTFLAG_Potion)
					{
						wsprintf(strBuff, "%d", sTrade.TradeItem[i].sItem.iPotionCount);
						dsTextLineOut(0, sTrade.TradeItem[i].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_TRADE]),
							sTrade.TradeItem[i].iPlaceY, strBuff, lstrlen(strBuff), D3DCOLOR_XRGB(255, 255, 255));

					}
				}
				if (sTradeRecv.TradeItem[i].bValid)
				{
					if (sTradeRecv.TradeItem[i].iItemSlotFlag == ITEMSLOTFLAG_Potion)
					{
						wsprintf(strBuff, "%d", sTradeRecv.TradeItem[i].sItem.iPotionCount);
						dsTextLineOut(0,
							sTradeRecv.TradeItem[i].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_TRADE]),
							sTradeRecv.TradeItem[i].iPlaceY - T_REVISION_Y,
							strBuff,
							lstrlen(strBuff),
							D3DCOLOR_XRGB(255, 255, 255));

					}
				}
			}
		}
		char szMoneyTemp[256];

		if (sAgingItem.AgingItem[0].bValid)
		{
			// ¶ÍÔìÎïÆ·½ðÇ®
			int Succed, Blast;

			Succed = AgingOkPercent[sAgingItem.AgingItem[0].sItem.sAgeLevel];
			Blast = AgingBlast[sAgingItem.AgingItem[0].sItem.sAgeLevel];
			if (sAgingItem.AgingItem[14].bValid && sAgingItem.AgingItem[14].sBaseItemID.ToInt() == (sinBI1 | sin10))
				Succed = AgingStoneAgingOkPercent5[sAgingItem.AgingItem[0].sItem.sAgeLevel];

			else if (sAgingItem.AgingItem[14].bValid && sAgingItem.AgingItem[14].sBaseItemID.ToInt() == (sinBI2 | sin78))
				Succed = AgingStoneAgingOkPercent10[sAgingItem.AgingItem[0].sItem.sAgeLevel];

			else if (sAgingItem.AgingItem[14].bValid && sAgingItem.AgingItem[14].sBaseItemID.ToInt() == (sinBI2 | sin79))
				Succed = AgingStoneAgingOkPercent15[sAgingItem.AgingItem[0].sItem.sAgeLevel];

			else if (sAgingItem.AgingItem[14].bValid && sAgingItem.AgingItem[14].sBaseItemID.ToInt() == (sinBI2 | sin80))
				Succed = AgingStoneAgingOkPercent20[sAgingItem.AgingItem[0].sItem.sAgeLevel];

			else if (sAgingItem.AgingItem[14].bValid && sAgingItem.AgingItem[14].sBaseItemID.ToInt() == (sinBI2 | sin81))
				Succed = AgingStoneAgingOkPercent25[sAgingItem.AgingItem[0].sItem.sAgeLevel];

			else if (sAgingItem.AgingItem[14].bValid && sAgingItem.AgingItem[14].sBaseItemID.ToInt() == (sinBI1 | sin11))
				Blast = 0;

			Succed = 100 - Succed;

			wsprintf(szMoneyTemp, "Success Chance: %d %", Succed);

			DWORD Color = 0;

			static BOOL Flag = FALSE;

			static float fAngle = 0.0f;
			static int Num = 0;

			if (fAngle > 0.0f && Flag == TRUE)
			{
				fAngle -= 0.4f * 10.0f;
				if (fAngle <= 0.0f)
				{
					Flag = FALSE;
					Num++;
				}
			}

			if (fAngle < 255.0f && Flag == FALSE)
			{
				fAngle += 0.4f * 10.0f;
				if (fAngle >= 255.0f)
					Flag = TRUE;
			}

			if (Num & 1)
			{
				wsprintf(szMoneyTemp, "Break Chance: %d %", Blast);
				Color = D3DCOLOR_RGBA(255, 50, 0, int(fAngle));
			}
			else
			{
				wsprintf(szMoneyTemp, "Success Chance: %d %", Succed);
				Color = D3DCOLOR_RGBA(255, 200, 0, int(fAngle));
			}

			dsTextLineOut(0, 60, 318 + sinInterHeight2, szMoneyTemp, lstrlen(szMoneyTemp), Color);
			wsprintf(szMoneyTemp, "%d", cShop.haShopItemPrice((sAgingItem.AgingItem[0].sItem.iSalePrice + (sAgingItem.AgingItem[0].sItem.iSalePrice*sAgingItem.AgingItem[0].sItem.sAgeLevel)) / 2));
			dsTextLineOut(0, CheckEditSize(200, 275, szMoneyTemp), 323 + sinInterHeight2, szMoneyTemp, lstrlen(szMoneyTemp), D3DCOLOR_XRGB(255, 255, 255));
		}
		if (sCraftItem.CraftItem[0].bValid)
		{
			wsprintf(szMoneyTemp, "%d", cShop.haShopItemPrice(sCraftItem.CraftItem[0].sItem.iSalePrice));
			dsTextLineOut(0, CheckEditSize(200, 325, szMoneyTemp), 322 + sinInterHeight2, szMoneyTemp, lstrlen(szMoneyTemp), D3DCOLOR_XRGB(255, 255, 255));
		}
		if (cCraftItem.ForceFlag)
		{
			wsprintf(szMoneyTemp, "%d", cShop.haShopItemPrice(ForceItemPrice2));
			dsTextLineOut(0, CheckEditSize(200, 325, szMoneyTemp) - (256 + 128 - sinMoveKindInter[SIN_CRAFTITEM]), 322 + sinInterHeight2, szMoneyTemp, lstrlen(szMoneyTemp), D3DCOLOR_XRGB(255, 255, 255));
		}
		if (S_smeltingItem.SmeltingItem[0].bValid)
		{
			wsprintf(szMoneyTemp, "%d", ForceItemPrice2);
			dsTextLineOut(0, CheckEditSize(200, 325, szMoneyTemp), 322 + sinInterHeight2, szMoneyTemp, lstrlen(szMoneyTemp), D3DCOLOR_XRGB(255, 255, 255));
		}
		if (sManufactureItem.ManufactureItem[0].bValid)
		{
			wsprintf(szMoneyTemp, "%d", ForceItemPrice2);
			dsTextLineOut(0, CheckEditSize(200, 325, szMoneyTemp), 322 + sinInterHeight2, szMoneyTemp, lstrlen(szMoneyTemp), D3DCOLOR_XRGB(255, 255, 255));
		}
		// ÊôÐÔÏµÍ³ÐèÒªµÄ½ðÇ®
		if (cElement.ElementItem[0].bValid)
		{
			wsprintf(szMoneyTemp, "%d", cShop.haShopItemPrice(cElement.ElementItem[0].sItem.iSalePrice));
			dsTextLineOut(0, CheckEditSize(200, 325, szMoneyTemp), 322 + sinInterHeight2, szMoneyTemp, lstrlen(szMoneyTemp), D3DCOLOR_XRGB(255, 255, 255));
		}
		// ´ò¿×ÏµÍ³ÐèÒªµÄ½ðÇ®
		if (cSocket.SocketItem[0].bValid)
		{
			wsprintf(szMoneyTemp, "%d", cShop.haShopItemPrice(cSocket.SocketItem[0].sItem.iSalePrice));
			dsTextLineOut(0, CheckEditSize(200, 325, szMoneyTemp), 322 + sinInterHeight2, szMoneyTemp, lstrlen(szMoneyTemp), D3DCOLOR_XRGB(255, 255, 255));
		}

		char *pCraftItemInfo[10];

		int len, Templen = 0, Textlen = 0;
		int Count = 0;
		int SetTextXposi = 0;
		char TempszCraftItemBuff[128];

		lstrcpy(TempszCraftItemBuff, szCraftItemBuff);

		if (ShowItemCraftMessageFlag || ShowItemAgingMessageFlag || ShowItemSmeltingMessageFlag || ShowItemManufactureMessageFlag || ShowItemOverSpace)
		{
			if (ShowItemCraftMessageFlag)
				dsTextLineOut(1, CraftItemMessageBoxPosi.x + 53, CraftItemMessageBoxPosi.y + 13, "Item Mixture Result", lstrlen("Item Mixture Result"), D3DCOLOR_XRGB(222, 231, 255));
			if (ShowItemSmeltingMessageFlag)
				dsTextLineOut(1, CraftItemMessageBoxPosi.x + 53, CraftItemMessageBoxPosi.y + 13, "ÎïÆ·Ò±Á¶", lstrlen("ÎïÆ·Ò±Á¶"), D3DCOLOR_XRGB(222, 231, 255));
			if (ShowItemManufactureMessageFlag)
				dsTextLineOut(1, CraftItemMessageBoxPosi.x + 53, CraftItemMessageBoxPosi.y + 13, "ÎïÆ·ÖÆÔì", lstrlen("ÎïÆ·ÖÆÔì"), D3DCOLOR_XRGB(222, 231, 255));
			if (ShowItemOverSpace)
				dsTextLineOut(1, CraftItemMessageBoxPosi.x + 53, CraftItemMessageBoxPosi.y + 13, InventoryFull, lstrlen("InventoryFull"), D3DCOLOR_XRGB(222, 231, 255));

			len = lstrlen(TempszCraftItemBuff);
			for (i = 0; i < len; i++)
			{
				if (TempszCraftItemBuff[i] == '\r')
				{
					pCraftItemInfo[Count] = &TempszCraftItemBuff[Templen];
					TempszCraftItemBuff[i] = 0;
					Templen = i + 1;
					Textlen = lstrlen(pCraftItemInfo[Count]);
					//SetTextXposi = ((CraftItemMessageBoxPosi.x+((CraftItemMessageSize.x*16)/2))  - ((Textlen/2)*11));

					SetTextXposi = CraftItemMessageBoxPosi.y + 13;
					//if(Textlen <= 12)
						//SetTextXposi -=6;

					dsTextLineOut(0, SetTextXposi + 27, CraftItemMessageBoxPosi.y + 38 + ((Count) * 18), pCraftItemInfo[Count], Textlen, D3DCOLOR_XRGB(255, 255, 255));
					Count++;
				}
			}
		}
	}
}
int cTRADE::SetTradeItemAreaCheck(ItemData *pItem)
{
	int i, j;
	TradeColorIndex = 0;
	TradeCrashItemIndex[0] = 0;
	InitTradeColorRect();

	TradeStartX = DownTradePosi[T_SET_BOX][0];
	TradeStartY = DownTradePosi[T_SET_BOX][1];
	TradeEndX = DownTradePosi[T_SET_BOX][2];
	TradeEndY = DownTradePosi[T_SET_BOX][3];

	for (i = pItem->iPlaceX + 11; i < pItem->iPlaceX + pItem->iWidth; i += 22)
	{
		for (j = pItem->iPlaceY + 11; j < pItem->iPlaceY + pItem->iHeight; j += 22)
		{
			if (TradeStartX <= i && TradeEndX > i && TradeStartY <= j && TradeEndY > j)
			{
				TradeColorRect.left = TradeStartX + (((i - TradeStartX) / 22) * 22);
				TradeColorRect.top = TradeStartY + (((j - TradeStartY) / 22) * 22);
				TradeColorRect.right = pItem->iWidth;
				TradeColorRect.bottom = pItem->iHeight;
				if (TradeEndX < (TradeColorRect.left + TradeColorRect.right) - 11 ||
					TradeEndY < (TradeColorRect.top + TradeColorRect.bottom) - 11)
				{
					InitTradeColorRect();
					return FALSE;
				}

				pItem->iPlaceX = TradeColorRect.left;
				pItem->iPlaceY = TradeColorRect.top;
				pItem->iItemSlot = 0;
				TradeColorIndex = SET_ITEM_CHECK_COLOR;

				if (TradeCrashItemIndex[0] = CrashTradeItem(TradeColorRect))
				{
					TradeColorIndex = NOT_SETTING_COLOR;
					return FALSE;
				}
				if (pItem->sItem.SpecialItemFlag[0] == CHECK_COPY_ITEM ||
					pItem->sItem.SpecialItemFlag[0] == CHECK_GIVE_ITEM ||
					pItem->sItem.eCraftType == ITEMCRAFTTYPE_Quest ||
					(pItem->sItem.sItemID.ToItemType()) == sinMA1 ||
					(pItem->sItem.sItemID.ToItemType()) == sinMA2 ||
					(pItem->sItem.sItemID.ToItemType()) == sinQW1 ||
					(pItem->sItem.sItemID.ToItemType()) == sinQT1 ||

					pItem->sItem.sItemID.ToInt() == (sinGF1 | sin01) ||
					pItem->sItem.sItemID.ToInt() == (sinGF1 | sin07) ||
					pItem->sItem.sItemID.ToInt() == (sinGF1 | sin08) ||
					pItem->iItemSlot)
				{
					TradeColorIndex = NOT_SETTING_COLOR;
					return FALSE;

				}

				return TRUE;
			}
		}
	}

	return FALSE;
}
int cTRADE::SetTradeItem(ItemData *pItem)
{
	if (pItem->sItem.SpecialItemFlag[0] == CHECK_COPY_ITEM ||
		pItem->sItem.SpecialItemFlag[0] == CHECK_GIVE_ITEM ||
		pItem->sItem.eCraftType == ITEMCRAFTTYPE_Quest ||
		(pItem->sItem.sItemID.ToItemType()) == sinMA1 ||
		(pItem->sItem.sItemID.ToItemType()) == sinMA2 ||
		(pItem->sItem.sItemID.ToItemType()) == sinQW1 ||
		(pItem->sItem.sItemID.ToItemType()) == sinQT1 ||

		pItem->sItem.sItemID.ToInt() == (sinGF1 | sin01) ||
		pItem->sItem.sItemID.ToInt() == (sinGF1 | sin07) ||
		pItem->sItem.sItemID.ToInt() == (sinGF1 | sin08))
	{
		return FALSE;
	}
	if (GetEmptyArea(pItem))
	{
		pItem->iPlaceX = pItem->iPlaceX;
		pItem->iPlaceY = pItem->iPlaceY;
		return TRUE;
	}
	return FALSE;
}
int cTRADE::InitTradeColorRect()
{
	TradeColorRect.left = 0;
	TradeColorRect.top = 0;
	TradeColorRect.right = 0;
	TradeColorRect.bottom = 0;
	return TRUE;
}
int cTRADE::GetEmptyArea(ItemData *pItem)
{
	int cntx, cnty;
	int cx, cy;

	RECT	rect;
	int		flag;
	int StartX = DownTradePosi[T_SET_BOX][0];
	int StartY = DownTradePosi[T_SET_BOX][1];

	cx = (22 * 9) - pItem->iWidth;
	cy = (22 * 4) - pItem->iHeight;

	for (cnty = StartY; cnty <= StartY + cy; cnty += 22)
	{
		for (cntx = StartX; cntx <= StartX + cx; cntx += 22)
		{
			flag = 0;
			for (int i = 0; i < MAX_TRADE_ITEM; i++)
			{
				if (sTrade.TradeItem[i].bValid)
				{
					rect.left	= sTrade.TradeItem[i].iPlaceX;
					rect.right	= sTrade.TradeItem[i].iPlaceX + sTrade.TradeItem[i].iWidth;
					rect.top	= sTrade.TradeItem[i].iPlaceY;
					rect.bottom = sTrade.TradeItem[i].iPlaceY + sTrade.TradeItem[i].iHeight;

					if (cntx > rect.left - pItem->iWidth &&
						cntx < rect.right &&
						cnty > rect.top - pItem->iHeight &&
						cnty < rect.bottom)
						flag++;
				}
			}
			if (flag == 0)
			{
				pItem->iPlaceX = cntx;
				pItem->iPlaceY = cnty;
				return TRUE;
			}
		}
	}

	return FALSE;
}
int cTRADE::CrashTradeItem(RECT &desRect, int PassItemIndex, int Kind)
{
	RECT rect;
	int i;

	switch (Kind)
	{
	case 0:
		for (i = 0; i < MAX_TRADE_ITEM; i++)
		{
			if (sTrade.TradeItem[i].bValid)
			{
				if (PassItemIndex != 0)
				{
					if (PassItemIndex == i + 1)
						continue;
				}
				rect.left	= sTrade.TradeItem[i].iPlaceX;
				rect.right	= sTrade.TradeItem[i].iPlaceX + sTrade.TradeItem[i].iWidth;
				rect.top	= sTrade.TradeItem[i].iPlaceY;
				rect.bottom = sTrade.TradeItem[i].iPlaceY + sTrade.TradeItem[i].iHeight;

				if (desRect.left > rect.left - desRect.right  &&
					desRect.left < rect.right &&
					desRect.top > rect.top - desRect.bottom &&
					desRect.top < rect.bottom)
					return i + 1;
			}
		}
		break;
	case 1:
		for (i = 0; i < 100; i++)
		{
			if (cWareHouse.WareHouse.WareHouseItem[i].bValid)
			{
				if (PassItemIndex != 0)
				{
					if (PassItemIndex == i + 1)
						continue;
				}
				rect.left	= cWareHouse.WareHouse.WareHouseItem[i].iPlaceX;
				rect.right	= cWareHouse.WareHouse.WareHouseItem[i].iPlaceX + cWareHouse.WareHouse.WareHouseItem[i].iWidth;
				rect.top	= cWareHouse.WareHouse.WareHouseItem[i].iPlaceY;
				rect.bottom = cWareHouse.WareHouse.WareHouseItem[i].iPlaceY + cWareHouse.WareHouse.WareHouseItem[i].iHeight;

				if (desRect.left > rect.left - desRect.right  &&
					desRect.left < rect.right &&
					desRect.top > rect.top - desRect.bottom &&
					desRect.top < rect.bottom)
					return i + 1;
			}
		}
		break;
	case 2:
		for (i = 0; i < 15; i++)
		{
			if (sCraftItem.CraftItem[i].bValid)
			{
				if (PassItemIndex != 0)
				{
					if (PassItemIndex == i + 1)
						continue;
				}
				rect.left	= sCraftItem.CraftItem[i].iPlaceX;
				rect.right	= sCraftItem.CraftItem[i].iPlaceX + sCraftItem.CraftItem[i].iWidth;
				rect.top	= sCraftItem.CraftItem[i].iPlaceY;
				rect.bottom = sCraftItem.CraftItem[i].iPlaceY + sCraftItem.CraftItem[i].iHeight;

				if (desRect.left > rect.left - desRect.right  &&
					desRect.left < rect.right &&
					desRect.top > rect.top - desRect.bottom && 
					desRect.top < rect.bottom)
					return i + 1;
			}
		}
		break;
	case 3:
		for (i = 0; i < 15; i++)
		{
			if (sAgingItem.AgingItem[i].bValid)
			{
				if (PassItemIndex != 0)
				{
					if (PassItemIndex == i + 1)
						continue;
				}
				rect.left	= sAgingItem.AgingItem[i].iPlaceX;
				rect.right	= sAgingItem.AgingItem[i].iPlaceX + sAgingItem.AgingItem[i].iWidth;
				rect.top	= sAgingItem.AgingItem[i].iPlaceY;
				rect.bottom = sAgingItem.AgingItem[i].iPlaceY + sAgingItem.AgingItem[i].iHeight;

				if (desRect.left > rect.left - desRect.right  &&
					desRect.left < rect.right &&
					desRect.top > rect.top - desRect.bottom &&
					desRect.top < rect.bottom)
					return i + 1;
			}
		}
		break;
	case 4:
		for (i = 0; i < 5; i++)
		{
			if (S_smeltingItem.SmeltingItem[i].bValid)
			{
				if (PassItemIndex != 0)
				{
					if (PassItemIndex == i + 1)
						continue;
				}
				rect.left	= S_smeltingItem.SmeltingItem[i].iPlaceX;
				rect.right	= S_smeltingItem.SmeltingItem[i].iPlaceX + S_smeltingItem.SmeltingItem[i].iWidth;
				rect.top	= S_smeltingItem.SmeltingItem[i].iPlaceY;
				rect.bottom = S_smeltingItem.SmeltingItem[i].iPlaceY + S_smeltingItem.SmeltingItem[i].iHeight;

				if (desRect.left > rect.left - desRect.right &&
					desRect.left < rect.right &&
					desRect.top > rect.top - desRect.bottom &&
					desRect.top < rect.bottom)
					return i + 1;
			}
		}
		break;
	case 5:
		for (i = 0; i < 4; i++)
		{
			if (sManufactureItem.ManufactureItem[i].bValid)
			{
				if (PassItemIndex != 0)
				{
					if (PassItemIndex == i + 1)
						continue;
				}
				rect.left	= sManufactureItem.ManufactureItem[i].iPlaceX;
				rect.right	= sManufactureItem.ManufactureItem[i].iPlaceX + sManufactureItem.ManufactureItem[i].iWidth;
				rect.top	= sManufactureItem.ManufactureItem[i].iPlaceY;
				rect.bottom = sManufactureItem.ManufactureItem[i].iPlaceY + sManufactureItem.ManufactureItem[i].iHeight;

				if (desRect.left > rect.left - desRect.right && desRect.left < rect.right && desRect.top > rect.top - desRect.bottom && desRect.top < rect.bottom)
					return i + 1;
			}
		}
		break;
	case 6:
		for (i = 0; i < 2; i++)
		{
			if (sMixtureResetItem.MixtureResetItem[i].bValid)
			{
				if (PassItemIndex != 0)
				{
					if (PassItemIndex == i + 1)
						continue;
				}
				rect.left	= sMixtureResetItem.MixtureResetItem[i].iPlaceX;
				rect.right	= sMixtureResetItem.MixtureResetItem[i].iPlaceX + sMixtureResetItem.MixtureResetItem[i].iWidth;
				rect.top	= sMixtureResetItem.MixtureResetItem[i].iPlaceY;
				rect.bottom = sMixtureResetItem.MixtureResetItem[i].iPlaceY + sMixtureResetItem.MixtureResetItem[i].iHeight;

				if (desRect.left > rect.left - desRect.right &&
					desRect.left < rect.right &&
					desRect.top > rect.top - desRect.bottom &&
					desRect.top < rect.bottom)
					return i + 1;
			}
		}
		break;
	case 7:
		for (i = 0; i < 6; i++)
		{
			if (cElement.ElementItem[i].bValid)
			{
				if (PassItemIndex != 0)
				{
					if (PassItemIndex == i + 1)
						continue;
				}
				rect.left	= cElement.ElementItem[i].iPlaceX;
				rect.right	= cElement.ElementItem[i].iPlaceX + cElement.ElementItem[i].iWidth;
				rect.top	= cElement.ElementItem[i].iPlaceY;
				rect.bottom = cElement.ElementItem[i].iPlaceY + cElement.ElementItem[i].iHeight;

				if (desRect.left > rect.left - desRect.right &&
					desRect.left < rect.right &&
					desRect.top > rect.top - desRect.bottom &&
					desRect.top < rect.bottom)
					return i + 1;
			}
		}
		break;
	case 8:
		for (i = 0; i < 100; i++)
		{
			if (cCaravan.sCaravan.Item[i].bValid)
			{
				if (PassItemIndex != 0)
				{
					if (PassItemIndex == i + 1)
						continue;
				}
				rect.left	= cCaravan.sCaravan.Item[i].iPlaceX;
				rect.right	= cCaravan.sCaravan.Item[i].iPlaceX + cCaravan.sCaravan.Item[i].iWidth;
				rect.top	= cCaravan.sCaravan.Item[i].iPlaceY;
				rect.bottom = cCaravan.sCaravan.Item[i].iPlaceY + cCaravan.sCaravan.Item[i].iHeight;

				if (desRect.left > rect.left - desRect.right  &&
					desRect.left < rect.right &&
					desRect.top > rect.top - desRect.bottom &&
					desRect.top < rect.bottom)
					return i + 1;
			}
		}
		break;
	case 9:
		for (i = 0; i < 5; i++)
		{
			if (cSocket.SocketItem[i].bValid)
			{
				if (PassItemIndex != 0)
				{
					if (PassItemIndex == i + 1)
						continue;
				}
				rect.left	= cSocket.SocketItem[i].iPlaceX;
				rect.right	= cSocket.SocketItem[i].iPlaceX + cSocket.SocketItem[i].iWidth;
				rect.top	= cSocket.SocketItem[i].iPlaceY;
				rect.bottom = cSocket.SocketItem[i].iPlaceY + cSocket.SocketItem[i].iHeight;

				if (desRect.left > rect.left - desRect.right &&
					desRect.left < rect.right &&
					desRect.top > rect.top - desRect.bottom &&
					desRect.top < rect.bottom)
					return i + 1;
			}
		}
		break;
	}

	return FALSE;

}
int cTRADE::LastSetTradeItem(ItemData *pItem)
{
	CheckTradeItemForm();

	for (int j = 0; j < MAX_TRADE_ITEM; j++)
	{
		if (!sTrade.TradeItem[j].bValid)
		{
			if (!CheckTrade((void *)&sTrade))
				CancelTradeItem();

			memcpy(&sTrade.TradeItem[j], pItem, sizeof(ItemData));
			sTrade.TradeItem[j].iPlaceX = pItem->iPlaceX;
			sTrade.TradeItem[j].iPlaceY = pItem->iPlaceY;
			pItem->bValid = 0;
			sTrade.CheckFlag = 0;
			sinPlaySound(sTrade.TradeItem[j].iInvItemSound);
			ReformTrade((void *)&sTrade);
			GetWeight();
			SendTradeItem(TradeCharCode);
			ReFormTradeItem();
			return TRUE;
		}
	}
	cMessageBox.ShowMessage(MESSAGE_TRADE_OVER_NUM);
	ReFormTradeItem();
	return FALSE;
}

int cTRADE::PickUpTradeItem(int x, int y, int PickUpFlag)
{
	int i = 0;
	SelectTradeItemIndex = 0;
	ItemKindFlag = 0;
	for (i = 0; i < MAX_TRADE_ITEM; i++)
	{
		if (sTrade.TradeItem[i].bValid)
		{
			if (sTrade.TradeItem[i].iPlaceX < x  &&
				sTrade.TradeItem[i].iPlaceX + sTrade.TradeItem[i].iWidth > x  &&
				sTrade.TradeItem[i].iPlaceY < y  &&
				sTrade.TradeItem[i].iPlaceY + sTrade.TradeItem[i].iHeight > y)
			{
				switch (PickUpFlag)
				{
				case 1:
					CheckTradeItemForm();
					if (!CheckTrade((void *)&sTrade))
						CancelTradeItem();
					memcpy(&MouseItem, &sTrade.TradeItem[i], sizeof(ItemData));
					sTrade.TradeItem[i].bValid = 0;
					sinPlaySound(sTrade.TradeItem[i].iInvItemSound);
					TradeColorIndex = 0;
					CheckDelayFlag = 1;
					sTrade.CheckFlag = 0;
					ReformTrade((void *)&sTrade);
					GetWeight();
					SendTradeItem(TradeCharCode);
					ReFormTradeItem();
					return TRUE;
					break;
				case 2:
					if (cCraftItem.CraftCheckEmptyArea(&sTrade.TradeItem[i]))
					{
						CheckTradeItemForm();
						if (!cInvenTory.AutoSetInvenItem(&sTrade.TradeItem[i]))
						{
							sinThrowItemToFeild(&sTrade.TradeItem[i]);
							sTrade.TradeItem[i].bValid = 0;
						}
						TradeColorIndex = 0;
						GetWeight();
						ReFormTradeItem();
						return TRUE;
					}
					break;
				default:
					SelectTradeItemIndex = i + 1;
					TradeColorIndex = SELECT_ITEM_COLOR;
					ItemKindFlag = 1;
					sinShowItemInfoFlag = 1;
					cItem.ShowItemInfo(&sTrade.TradeItem[i], 2);
					break;
				}
			}
		}
	}
	for (i = 0; i < MAX_TRADE_ITEM; i++)
	{
		if (sTradeRecv.TradeItem[i].bValid)
		{
			if (sTradeRecv.TradeItem[i].iPlaceX < x  &&
				sTradeRecv.TradeItem[i].iPlaceX + sTradeRecv.TradeItem[i].iWidth > x  &&
				sTradeRecv.TradeItem[i].iPlaceY - T_REVISION_Y < y  &&
				sTradeRecv.TradeItem[i].iPlaceY - T_REVISION_Y + sTradeRecv.TradeItem[i].iHeight > y)
			{
				SelectTradeItemIndex = i + 1;
				TradeColorIndex = SELECT_ITEM_COLOR;
				ItemKindFlag = 2;
				sinShowItemInfoFlag = 1;
				sTradeRecv.TradeItem[i].iPlaceY -= T_REVISION_Y;
				cItem.ShowItemInfo(&sTradeRecv.TradeItem[i], 2);
				sTradeRecv.TradeItem[i].iPlaceY += T_REVISION_Y;
				return TRUE;

			}
		}
	}

	return FALSE;
}
int cTRADE::CheckTradeItemSet()
{
	int i = 0;
	int TempWeight = 0;

	memcpy(&CheckItem, &cInvenTory.InvenItem, sizeof(ItemData) * 100);
	memcpy(&CheckRecvItem, &sTradeRecv.TradeItem, sizeof(ItemData)*MAX_TRADE_ITEM);

	for (i = 0; i < MAX_TRADE_ITEM; i++)
	{
		if (CheckRecvItem[i].bValid)
		{
			if (CheckRecvItem[i].iItemSlotFlag == ITEMSLOTFLAG_Potion)
				TempWeight += CheckRecvItem[i].sItem.iPotionCount;
			else
				TempWeight += CheckRecvItem[i].sItem.iWeight;
		}
	}
	if (TempWeight + sinChar->sWeight.sMin > sinChar->sWeight.sMax)
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
		return FALSE;

	}
	for (i = 0; i < MAX_TRADE_ITEM; i++)
	{
		if (CheckRecvItem[i].bValid)
		{
			if (!TradeCheckEmptyArea(&CheckRecvItem[i]))
			{
				cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
				return FALSE;
			}
		}
	}

	if (sTradeRecv.Money > 0)
	{
		if (!cInvenTory.CheckMoneyLimit(sTradeRecv.Money - 193))
			return FALSE;
	}

	return TRUE;
}
int cTRADE::TradeCheckEmptyArea(ItemData *pItem)
{
	int cntx, cnty;
	int cx, cy;

	RECT	rect = { 0,0,0,0 };
	int		flag = 0;

	int StartX = 23;
	int StartY = 436;

	cx = (22 * INVENTORY_BOX_ROW) - pItem->iWidth;
	cy = (22 * INVENTORY_BOX_COL) - pItem->iHeight;

	for (cntx = StartX; cntx <= StartX + cx; cntx += 22)
	{
		for (cnty = StartY; cnty <= StartY + cy; cnty += 22)
		{
			flag = 0;
			for (int i = 0; i < INVENTORY_MAXITEM; i++)
			{
				if (CheckItem[i].bValid)
				{
					rect.left	= CheckItem[i].iPlaceX;
					rect.right	= CheckItem[i].iPlaceX + CheckItem[i].iWidth;
					rect.top	= CheckItem[i].iPlaceY;
					rect.bottom = CheckItem[i].iPlaceY + CheckItem[i].iHeight;

					if (cntx > rect.left - pItem->iWidth &&
						cntx < rect.right &&
						cnty > rect.top - pItem->iHeight &&
						cnty < rect.bottom)
						flag++;
				}
			}
			if (flag == 0)
			{
				pItem->iPlaceX = cntx;
				pItem->iPlaceY = cnty;
				pItem->iItemSlot = 0;
				if (ChecketInvenItem(pItem))
					return TRUE;
			}
		}
	}

	return FALSE;

}

int cTRADE::ChecketInvenItem(ItemData *pItem)
{
	for (int j = 0; j < INVENTORY_MAXITEM; j++)
	{
		if (CheckItem[j].bValid == 0)
		{
			memcpy(&CheckItem[j], pItem, sizeof(ItemData));
			CheckItem[j].iPlaceX = pItem->iPlaceX;
			CheckItem[j].iPlaceY = pItem->iPlaceY;
			pItem->bValid = 0;
			return TRUE;
		}
	}

	return FALSE;
}
int cTRADE::CheckOkTradeItem()
{
	int i = 0;
	for (i = 0; i < MAX_TRADE_ITEM; i++)
	{
		if (sTradeRecv.TradeItem[i].bValid)
		{
			if (cInvenTory.CheckRequireItemToSet(&sTradeRecv.TradeItem[i]))
			{
				if (!cInvenTory.AutoSetInvenItem(&sTradeRecv.TradeItem[i]))
				{
					if (sinThrowItemToFeild(&sTradeRecv.TradeItem[i]))
						sTradeRecv.TradeItem[i].bValid = 0;
				}
			}
		}
	}
	if (sTradeRecv.Money > 0)
	{
		CheckCharForm();
		sinPlusMoney(sTradeRecv.Money - 193);
		ReformCharForm();
		SendSaveMoney();
		sinPlaySound(SIN_SOUND_COIN);
	}
	cTrade.OpenFlag = FALSE;
	TempShowMoney = 0;
	ItemPickUpFlag = 0;

	cInvenTory.CheckWeight();

	return TRUE;
}
int cTRADE::CancelTradeItem()
{
	int sArrowPosi = 0;

	if (TradeItemSucessFlag)
	{
		memset(&sTrade, 0, sizeof(sTRADE));
		memset(&sTradeRecv, 0, sizeof(sTRADE));
	}
	int i = 0;
	for (i = 0; i < MAX_TRADE_ITEM; i++)
	{
		if (sTrade.TradeItem[i].bValid)
		{
			if (cInvenTory.CheckRequireItemToSet(&sTrade.TradeItem[i]))
			{
				if (!cInvenTory.AutoSetInvenItem(&sTrade.TradeItem[i]))
				{
					if (ArrowState[0] == 0)
						sArrowPosi = 2;
					else
						sArrowPosi = 1;
					sinButtonFlag = sArrowPosi;
					SelectInvenItemIndex = 0;
					cInvenTory.ChangeABItem(sArrowPosi);

					if (!cInvenTory.AutoSetInvenItem(&sTrade.TradeItem[i]))
					{
						if (sinThrowItemToFeild(&sTrade.TradeItem[i]))
							sTrade.TradeItem[i].bValid = 0;
					}

					if (sinThrowItemToFeild(&sTrade.TradeItem[i]))
						sTrade.TradeItem[i].bValid = 0;
				}
			}
		}
	}

	if (sTrade.Money > 0)
	{
		CheckCharForm();
		sinPlusMoney(sTrade.Money - 193);
		ReformCharForm();
		SendSaveMoney();
		sinPlaySound(SIN_SOUND_COIN);
	}
	if (MouseItem.bValid)
	{
		if (cInvenTory.CheckRequireItemToSet(&MouseItem))
		{
			if (!cInvenTory.AutoSetInvenItem(&MouseItem))
			{
				if (sinThrowItemToFeild(&MouseItem))
					MouseItem.bValid = 0;
			}
		}
	}

	if (sinMessageBoxShowFlag)
	{
		if (sMessageBox2[MESSAGE_MOVE_MONEY_TRADE].Flag)
		{
			sMessageBox2[MESSAGE_MOVE_MONEY_TRADE].Flag = 0;
			sinMessageBoxShowFlag = 0;
		}
	}

	cTrade.OpenFlag = FALSE;
	cMessageBox.ShowMessage(MESSAGE_TRADE_CANCEL);

	memset(&sTrade, 0, sizeof(sTRADE));
	memset(&sTradeRecv, 0, sizeof(sTRADE));
	TempShowMoney = 0;
	ItemPickUpFlag = 0;

	CloseEachPlayer();
	cInvenTory.CheckWeight();
	return TRUE;
}
int cTRADE::LoadTradeItemIamge()
{
	char szFilePath[256];
	int  cnt = 0;
	for (int i = 0; i < MAX_TRADE_ITEM; i++)
	{
		if (sTradeRecv.TradeItem[i].bValid)
		{
			ItemData * pItemData = ITEMHANDLE->GetItemDataByID(sTradeRecv.TradeItem[i].sItem.sItemID.ToInt());

			if (pItemData)
			{
				wsprintf(szFilePath, "Image\\sinImage\\Items\\%s\\it%s.bmp", pItemData->szCategory, pItemData->szInventoryName);

				if (!pItemData->pcTempInventoryTexture)
					pItemData->pcTempInventoryTexture = LoadDibSurfaceOffscreen(szFilePath);

				sTradeRecv.TradeItem[i].pcInventoryTexture = pItemData->pcTempInventoryTexture;
			}
		}
	}
	return TRUE;
}

int cTRADE::CheckTradeButtonOk()
{
	if (!TradeSendSucessFlag && sTrade.CheckFlag && sTradeRecv.CheckFlag)
	{
		SendTradeCheckItem(TradeCharCode);
		TradeSendSucessFlag = TRUE;
	}

	return TRUE;
}
int cTRADE::GetWeight()
{
	sTrade.Weight = 0;
	for (int i = 0; i < MAX_TRADE_ITEM; i++)
	{
		if (sTrade.TradeItem[i].bValid)
		{
			if (sTrade.TradeItem[i].iItemSlotFlag == ITEMSLOTFLAG_Potion)
				sTrade.Weight += sTrade.TradeItem[i].sItem.iPotionCount;
			else
				sTrade.Weight += sTrade.TradeItem[i].sItem.iWeight;
		}
	}

	return TRUE;
}
int cTRADE::CheckInvenItemStatus(ItemData *pItem)
{
	if ((pItem->iItemSlotFlag == ITEMSLOTFLAG_LeftRightHand && (pItem->sBaseItemID.ToInt() & sinITEM_MASK2) != sinWD1) || (pItem->iItemSlotFlag == ITEMSLOTFLAG_Wing))
		cInvenTory.PickUpTwoHandItem(pItem);

	if (pItem->iItemSlot)
	{
		sinSetCharItem(pItem->sBaseItemID.ToInt(), pItem->iVisibleItemType, FALSE);
		sInven[pItem->iItemSlot - 1].ItemIndex = 0;
	}
	return TRUE;
}
int cTRADE::ReFormInvenItemStatus()
{
	cInvenTory.ReFormInvenItem();
	cInvenTory.CheckWeight();
	cInvenTory.SetItemToChar();
	return TRUE;
}
cWAREHOUSE::cWAREHOUSE()
{
	SaveFlag = FALSE;
	Weight[0] = 0;
	Weight[1] = 1000;
}
cWAREHOUSE::~cWAREHOUSE()
{

}
int cWAREHOUSE::CheckWareHouseForm()
{
	int TempCheckDataSum = 0;

	for (int i = 0; i < 100; i++)
	{
		if (WareHouse.WareHouseItem[i].bValid)
		{
			TempCheckDataSum += (i + 1)*WareHouse.WareHouseItem[i].iPlaceX;
			TempCheckDataSum += (i + 1)*WareHouse.WareHouseItem[i].iPlaceY;
			TempCheckDataSum += WareHouse.WareHouseItem[i].sItem.iChk2;
			TempCheckDataSum += WareHouse.WareHouseItem[i].sItem.iChk1;
		}
	}

	if (TempCheckDataSum != WareHouseCheckSum)
		SendSetHackUser(11);

	return TRUE;

}

int cWAREHOUSE::ReFormWareHouse()
{
	WareHouseCheckSum = 0;

	for (int i = 0; i < 100; i++)
	{
		if (WareHouse.WareHouseItem[i].bValid)
		{
			WareHouseCheckSum += (i + 1)*WareHouse.WareHouseItem[i].iPlaceX;
			WareHouseCheckSum += (i + 1)*WareHouse.WareHouseItem[i].iPlaceY;
			WareHouseCheckSum += WareHouse.WareHouseItem[i].sItem.iChk2;
			WareHouseCheckSum += WareHouse.WareHouseItem[i].sItem.iChk1;
		}
	}

	return TRUE;
}
int cWAREHOUSE::CheckWareHouseEmptyArea(ItemData *pItem)
{
	int cntx, cnty;
	int cx, cy;

	RECT	rect;
	int		flag;

	int StartX = 21;
	int StartY = 136 + sinInterHeight2;

	cx = (22 * 9) - pItem->iWidth;
	cy = (22 * 9) - pItem->iHeight;

	for (cnty = StartY; cnty <= StartY + cy; cnty += 22)
	{
		for (cntx = StartX; cntx <= StartX + cx; cntx += 22)
		{
			flag = 0;

			for (int i = 0; i < 100; i++)
			{
				rect.left	= WareHouse.WareHouseItem[i].iPlaceX;
				rect.right	= WareHouse.WareHouseItem[i].iPlaceX + WareHouse.WareHouseItem[i].iWidth;
				rect.top	= WareHouse.WareHouseItem[i].iPlaceY;
				rect.bottom = WareHouse.WareHouseItem[i].iPlaceY + WareHouse.WareHouseItem[i].iHeight;

				if (cntx > rect.left - pItem->iWidth &&
					cntx < rect.right &&
					cnty > rect.top - pItem->iHeight &&
					cnty < rect.bottom)
					flag++;
			}
			if (flag == 0)
			{
				pItem->iPlaceX = cntx;
				pItem->iPlaceY = cnty;
				return TRUE;
			}
		}
	}
	return FALSE;
}
int cWAREHOUSE::SetWareHouseItemAreaCheck(ItemData *pItem)
{
	int i, j;
	TradeColorIndex = 0;
	TradeCrashItemIndex[0] = 0;
	cTrade.InitTradeColorRect();

	TradeStartX = 21;
	TradeStartY = 136 + sinInterHeight2;
	TradeEndX = TradeStartX + (22 * 9);
	TradeEndY = TradeStartY + (22 * 9);

	for (i = pItem->iPlaceX + 11; i < pItem->iPlaceX + pItem->iWidth; i += 22)
	{
		for (j = pItem->iPlaceY + 11; j < pItem->iPlaceY + pItem->iHeight; j += 22)
		{
			if (TradeStartX <= i && TradeEndX > i && TradeStartY <= j && TradeEndY > j)
			{
				TradeColorRect.left		= TradeStartX + (((i - TradeStartX) / 22) * 22);
				TradeColorRect.top		= TradeStartY + (((j - TradeStartY) / 22) * 22);
				TradeColorRect.right	= pItem->iWidth;
				TradeColorRect.bottom	= pItem->iHeight;
				if (TradeEndX < (TradeColorRect.left + TradeColorRect.right) - 11 ||
					TradeEndY < (TradeColorRect.top + TradeColorRect.bottom) - 11)
				{
					cTrade.InitTradeColorRect();
					return FALSE;
				}
				if (pItem->sItem.eCraftType == ITEMCRAFTTYPE_Quest ||
					(pItem->sItem.sItemID.ToItemType()) == sinMA1 ||
					(pItem->sItem.sItemID.ToItemType()) == sinMA2 ||
					(pItem->sItem.sItemID.ToItemType()) == sinQW1 ||
					(pItem->sItem.sItemID.ToItemType()) == sinQT1)
				{
					TradeColorIndex = NOT_SETTING_COLOR;
					return FALSE;
				}
				if (pItem->sItem.eCraftType == ITEMCRAFTTYPE_Event)
				{
					TradeColorIndex = NOT_SETTING_COLOR;
					return FALSE;

				}
				if ((pItem->sItem.sItemID.ToItemType()) == sinCH1)
				{
					TradeColorIndex = NOT_SETTING_COLOR;
					return FALSE;
				}
				if (pItem->sItem.sItemID.ToInt() == (sinGF1 | sin01))
				{
					TradeColorIndex = NOT_SETTING_COLOR;
					return FALSE;
				}

				pItem->iPlaceX = TradeColorRect.left;
				pItem->iPlaceY = TradeColorRect.top;
				pItem->iItemSlot = 0;
				TradeColorIndex = SET_ITEM_CHECK_COLOR;

				if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 1))
				{
					if (!CopyItemNotPickUp(&WareHouse.WareHouseItem[TradeCrashItemIndex[0] - 1], TradeCrashItemIndex[0] - 1))
					{
						TradeColorIndex = NOT_SETTING_COLOR;
						TradeCrashItemIndex[0] = 0;
						TradeCrashItemIndex[1] = 0;
						return FALSE;
					}
					if (TradeCrashItemIndex[1] = cTrade.CrashTradeItem(TradeColorRect, TradeCrashItemIndex[0], 1))
					{
						TradeColorIndex = NOT_SETTING_COLOR;
						TradeCrashItemIndex[1] = 0;
						return FALSE;
					}
					TradeColorIndex = OVERLAP_ITEM_COLOR;

				}
				return TRUE;
			}
		}
	}

	return TRUE;
}
int cWAREHOUSE::SetWareHouseItem(ItemData *pItem)
{
	int ErrorFlag = 0;

	if (pItem->sItem.eCraftType == ITEMCRAFTTYPE_Quest ||
		(pItem->sItem.sItemID.ToItemType()) == sinMA1 ||
		(pItem->sItem.sItemID.ToItemType()) == sinMA2 ||
		(pItem->sItem.sItemID.ToItemType()) == sinQW1 ||
		(pItem->sItem.sItemID.ToItemType()) == sinQT1)
	{
		return FALSE;
	}
	if (pItem->sItem.eCraftType == ITEMCRAFTTYPE_Event)
		return FALSE;
	if ((pItem->sItem.sItemID.ToItemType()) == sinCH1)
		return FALSE;
	if (pItem->sItem.sItemID.ToInt() == (sinGF1 | sin01))
		return FALSE;

	for (int i = 0; i < 100; i++)
	{
		if (CopyItemNotPickUp(&WareHouse.WareHouseItem[i], i) == NULL)
			return FALSE;
	}

	if (CheckWareHouseEmptyArea(pItem))
	{
		pItem->iPlaceX = pItem->iPlaceX;
		pItem->iPlaceY = pItem->iPlaceY;
		return TRUE;
	}
	return FALSE;

}
int cWAREHOUSE::LastSetWareHouseItem(ItemData *pItem)
{
	CheckWareHouseForm();

	for (int i = 0; i < 100; i++)
	{
		if (!WareHouse.WareHouseItem[i].bValid)
		{
			memcpy(&WareHouse.WareHouseItem[i], pItem, sizeof(ItemData));
			WareHouse.WareHouseItem[i].iPlaceX = pItem->iPlaceX;
			WareHouse.WareHouseItem[i].iPlaceY = pItem->iPlaceY;
			pItem->bValid = 0;
			sinPlaySound(WareHouse.WareHouseItem[i].iInvItemSound);
			GetWeight();
			ReFormWareHouse();
			return TRUE;
		}
	}
	ReFormWareHouse();
	return FALSE;
}
int cWAREHOUSE::CloseWareHouse()
{
	int RestoreFlag = TRUE;

	CloseWareHouseCheckFlag3 = 1;

	OpenFlag = FALSE;

	if (SaveFlag)
	{
		if (!SaveWareHouse(&WareHouse))
		{
			RestoreInvenItem();
			cMessageBox.ShowMessage(MESSAGE_OVER_ITEM_NUM);
			RestoreFlag = FALSE;
		}
		else
		{
			DELET(BackUpInvenItem2);
			DELET(BackUpInvenTempItem2);
			DELET(BackUpsInven);
		}
	}

	SaveFlag = FALSE;

	ResetInvenItemCode();
	ResetInvenMoney();
	return RestoreFlag;
}
int cWAREHOUSE::PickUpWareHouseItem(int x, int y, int PickUpFlag)
{
	int i = 0;
	SelectTradeItemIndex = 0;

	for (int i = 0; i < 100; i++)
	{
		if (WareHouse.WareHouseItem[i].bValid)
		{
			if (WareHouse.WareHouseItem[i].iPlaceX < x &&
				WareHouse.WareHouseItem[i].iPlaceX + WareHouse.WareHouseItem[i].iWidth > x &&
				WareHouse.WareHouseItem[i].iPlaceY < y &&
				WareHouse.WareHouseItem[i].iPlaceY + WareHouse.WareHouseItem[i].iHeight > y)
			{
				switch (PickUpFlag)
				{
				case 1:
				{
					ItemData TempItem;
					TempItem.iWidth = ITEMSIZE * 2;
					TempItem.iHeight = ITEMSIZE * 4;
					TempItem.bValid = 1;

					if (cInvenTory.CheckSetEmptyArea(&TempItem))
					{
						if (CopyItemNotPickUp(&WareHouse.WareHouseItem[i], i))
						{
							if (CheckWeight(&WareHouse.WareHouseItem[i]))
							{
								CheckWareHouseForm();
								memcpy(&MouseItem, &WareHouse.WareHouseItem[i], sizeof(ItemData));
								WareHouse.WareHouseItem[i].bValid = 0;
								sinPlaySound(WareHouse.WareHouseItem[i].iInvItemSound);
								TradeColorIndex = 0;
								GetWeight();
								ReFormWareHouse();
								return TRUE;
							}
							else
							{
								cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
								return FALSE;
							}
						}
					}
					else
					{
						cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
						return FALSE;
					}
					if (CopyItemNotPickUp(&WareHouse.WareHouseItem[i], i))
					{
						CheckWareHouseForm();
						memcpy(&MouseItem, &WareHouse.WareHouseItem[i], sizeof(ItemData));
						WareHouse.WareHouseItem[i].bValid = 0;
						sinPlaySound(WareHouse.WareHouseItem[i].iInvItemSound);
						TradeColorIndex = 0;
						GetWeight();
						ReFormWareHouse();
						return TRUE;
					}
				}
					
					break;
				case 2:
					if (CopyItemNotPickUp(&WareHouse.WareHouseItem[i], i))
					{
						if (cCraftItem.CraftCheckEmptyArea(&WareHouse.WareHouseItem[i]))
						{
							if (CheckWeight(&WareHouse.WareHouseItem[i]))
							{
								CheckWareHouseForm();
								if (!cInvenTory.AutoSetInvenItem(&WareHouse.WareHouseItem[i]))
								{
									sinThrowItemToFeild(&WareHouse.WareHouseItem[i]);
									WareHouse.WareHouseItem[i].bValid = 0;
								}
								TradeColorIndex = 0;
								GetWeight();
								ReFormWareHouse();
								return TRUE;
							}
							else
							{
								cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
								return FALSE;
							}
						}
						else
						{
							cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
							return FALSE;
						}
					}
					break;
				default:
					SelectTradeItemIndex = i + 1;
					TradeColorIndex = SELECT_ITEM_COLOR;
					sinShowItemInfoFlag = 1;
					cItem.ShowItemInfo(&WareHouse.WareHouseItem[i], 2);
					break;
				}
			}
		}
	}
	return FALSE;
}
int cWAREHOUSE::ChangeWareHouseItem(ItemData *pItem)
{
	if (pItem->iItemSlotFlag == ITEMSLOTFLAG_Potion)
	{
		cMessageBox.ShowMessage(MESSAGE_POTION_NOT_SETTING);
		return TRUE;
	}

	if (pItem->sItem.iWeight + Weight[0] > Weight[1])
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
		return TRUE;
	}

	CheckWareHouseForm();

	if (TradeCrashItemIndex[0])
	{
		if (WareHouse.WareHouseItem[TradeCrashItemIndex[0] - 1].iItemSlotFlag == ITEMSLOTFLAG_Potion)
		{
			if (WareHouse.WareHouseItem[TradeCrashItemIndex[0] - 1].sBaseItemID.ToInt() == pItem->sBaseItemID.ToInt())
			{
				WareHouse.WareHouseItem[TradeCrashItemIndex[0] - 1].sItem.iPotionCount += pItem->sItem.iPotionCount;
				pItem->bValid = 0;
				GetWeight();
				ReFormWareHouse();
				return TRUE;
			}
		}

		memcpy(&TempItem, &WareHouse.WareHouseItem[TradeCrashItemIndex[0] - 1], sizeof(ItemData));
		WareHouse.WareHouseItem[TradeCrashItemIndex[0] - 1].bValid = 0;
		TempItem.iPlaceX = pItem->iPlaceX;
		TempItem.iPlaceY = pItem->iPlaceY;
		ReFormWareHouse();
		LastSetWareHouseItem(pItem);
		memcpy(pItem, &TempItem, sizeof(ItemData));
		GetWeight();
		ReFormWareHouse();
		return TRUE;
	}
	ReFormWareHouse();
	return FALSE;
}
int cWAREHOUSE::GetWeight()
{
	Weight[0] = 0;
	for (int i = 0; i < 100; i++)
	{
		if (WareHouse.WareHouseItem[i].bValid)
		{
			if (WareHouse.WareHouseItem[i].iItemSlotFlag == ITEMSLOTFLAG_Potion)
				Weight[0] += WareHouse.WareHouseItem[i].sItem.iPotionCount;
			else
				Weight[0] += WareHouse.WareHouseItem[i].sItem.iWeight;
		}
	}
	SaveFlag = TRUE;

	return TRUE;
}
int cWAREHOUSE::CheckWeight(ItemData *pItem)
{
	if ((pItem->sItem.iWeight + sinChar->sWeight.sMin) > sinChar->sWeight.sMax)
		return FALSE;
	return TRUE;
}
int cWAREHOUSE::LoadWareHouseMoney(int money)
{
	Money = money;
	return TRUE;
}
int cWAREHOUSE::LoadWareHouseItemIamge()
{
	char szFilePath[256];
	int  cnt = 0;

	for (int i = 0; i < 100; i++)
	{
		if (WareHouse.WareHouseItem[i].bValid)
		{
			ItemData * pItem = ITEMHANDLE->GetItemDataByID(WareHouse.WareHouseItem[i].sItem.sItemID.ToInt());

			if (pItem)
			{
				WareHouse.WareHouseItem[i].iWidth = pItem->iWidth;
				WareHouse.WareHouseItem[i].iHeight = pItem->iHeight;
				wsprintf(szFilePath, "Image\\sinImage\\Items\\%s\\it%s.bmp", pItem->szCategory, pItem->szInventoryName);
				if (!pItem->pcTempInventoryTexture)
					pItem->pcTempInventoryTexture = LoadDibSurfaceOffscreen(szFilePath);

				WareHouse.WareHouseItem[i].pcInventoryTexture = pItem->pcTempInventoryTexture;
			}
		}
	}

	GetWeight();

	cInterFace.CheckAllBox(SIN_WAREHOUSE);

	return TRUE;
}
int cWAREHOUSE::BackUpInvenItem()
{
	BackUpInvenItem2 = 0;
	BackUpInvenTempItem2 = 0;
	BackUpsInven = 0;

	BackUpInvenItem2 = new ItemData[100];
	BackUpInvenTempItem2 = new ItemData[100];
	BackUpsInven = new sINVENTORY[INVENTORY_MAX_POS];

	memcpy(BackUpInvenItem2, &cInvenTory.InvenItem, sizeof(ItemData) * 100);
	memcpy(BackUpInvenTempItem2, &cInvenTory.InvenItemTemp, sizeof(ItemData) * 100);
	memcpy(BackUpsInven, &sInven, sizeof(sINVENTORY)*INVENTORY_MAX_POS);

	InvenGold = sinChar->iGold + 2023;

	RealGold = InvenGold * 3;

	return TRUE;
}
int cWAREHOUSE::RestoreInvenItem()
{
	sinSetCharItem(cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt(), cInvenTory.InvenItem[sInven[0].ItemIndex - 1].iVisibleItemType, FALSE);
	sinSetCharItem(cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sBaseItemID.ToInt(), cInvenTory.InvenItem[sInven[1].ItemIndex - 1].iVisibleItemType, FALSE);
	if (sinChar->CostmePos == TRUE)
		sinSetCharItem(cInvenTory.InvenItem[sInven[13].ItemIndex - 1].sBaseItemID.ToInt(), cInvenTory.InvenItem[sInven[13].ItemIndex - 1].iVisibleItemType, FALSE);
	else
		sinSetCharItem(cInvenTory.InvenItem[sInven[2].ItemIndex - 1].sBaseItemID.ToInt(), cInvenTory.InvenItem[sInven[2].ItemIndex - 1].iVisibleItemType, FALSE);

	memcpy(&cInvenTory.InvenItem, BackUpInvenItem2, sizeof(ItemData) * 100);
	memcpy(&cInvenTory.InvenItemTemp, BackUpInvenTempItem2, sizeof(ItemData) * 100);
	memcpy(&sInven, BackUpsInven, sizeof(sINVENTORY)*INVENTORY_MAX_POS);

	if (MouseItem.bValid)
		MouseItem.bValid = 0;

	DELET(BackUpInvenItem2);
	DELET(BackUpInvenTempItem2);
	DELET(BackUpsInven);

	if (sInven[0].ItemIndex)
		sinSetCharItem(cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt(), cInvenTory.InvenItem[sInven[0].ItemIndex - 1].iVisibleItemType, TRUE);
	if (sInven[1].ItemIndex)
		sinSetCharItem(cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sBaseItemID.ToInt(), cInvenTory.InvenItem[sInven[1].ItemIndex - 1].iVisibleItemType, TRUE);
	if (sinChar->CostmePos == TRUE)
	{
		if (sInven[13].ItemIndex)
			sinSetCharItem(cInvenTory.InvenItem[sInven[13].ItemIndex - 1].sBaseItemID.ToInt(), cInvenTory.InvenItem[sInven[13].ItemIndex - 1].iVisibleItemType, TRUE);
	}
	else
	{
		if (sInven[2].ItemIndex)
			sinSetCharItem(cInvenTory.InvenItem[sInven[2].ItemIndex - 1].sBaseItemID.ToInt(), cInvenTory.InvenItem[sInven[2].ItemIndex - 1].iVisibleItemType, TRUE);
	}

	if ((InvenGold - 2023) == (RealGold / 3) - 2023)
	{
		CheckCharForm();
		sinChar->iGold = InvenGold - 2023;
		ReformCharForm();
	}
	else
		SendSetHackUser(6);

	InvenGold = 0;
	RealGold = 0;

	cInvenTory.SetItemToChar();
	cInvenTory.ReFormInvenItem();
	cInvenTory.CheckWeight();

	return TRUE;
}
int cWAREHOUSE::CopyItemNotPickUp(ItemData *pItem, int JumpIndex)
{
	if (SETTINGHANDLE->Get().bDebugMode)
		return TRUE;

	for (int i = 0; i < 100; i++)
	{
		if (WareHouse.WareHouseItem[i].bValid)
		{
			if (JumpIndex == i)
				continue;
			if (CompareItems(&pItem->sItem, &WareHouse.WareHouseItem[i].sItem))
			{
				CopyItemIndex7[i] = i + 1;
				return FALSE;
			}
		}
	}

	return TRUE;
}

int SendServerFlag7 = 0;

int cWAREHOUSE::CheckCopyItem()
{
	if (SendServerFlag7)
		return FALSE;
	for (int i = 0; i < 100; i++)
	{
		if (WareHouse.WareHouseItem[i].bValid)
		{
			for (int j = 0; j < 100; j++)
			{
				if (i != j && WareHouse.WareHouseItem[j].bValid)
				{
					if (CompareItems(&WareHouse.WareHouseItem[i].sItem, &WareHouse.WareHouseItem[j].sItem))
					{
						SendSetHackUser2(1010, WareHouse.WareHouseItem[i].sBaseItemID.ToInt());
						SendServerFlag7 = 1;
						break;
					}
				}
			}
		}
	}
	return TRUE;
}
int cWAREHOUSE::DeleteCopyItem()
{
	for (int i = 0; i < 100; i++)
	{
		if (WareHouse.WareHouseItem[i].bValid)
		{
			for (int j = 0; j < 100; j++)
			{
				if (i != j && WareHouse.WareHouseItem[j].bValid)
				{
					if (CompareItems(&WareHouse.WareHouseItem[i].sItem, &WareHouse.WareHouseItem[j].sItem))
					{
						WareHouse.WareHouseItem[j].bValid = 0;
						cWareHouse.ReFormWareHouse();
						break;
					}
				}
			}
		}
	}
	return TRUE;
}
int cCRAFTITEM::SetCraftItemAreaCheck(ItemData *pItem, int Kind)
{
	int i, j;
	TradeColorIndex = 0;
	TradeCrashItemIndex[0] = 0;
	cTrade.InitTradeColorRect();

	if (pItem->sItem.sItemID.ToInt() == (sinBI1 | sin90))
	{
		int ReconStoneX = 159 + 11, ReconStoneY = 268 + 11 + sinInterHeight2;
		TradeColorIndex = 0;
		if (ReconStoneX <=pItem->iPlaceX + 22 &&
			ReconStoneX > pItem->iPlaceX &&
			ReconStoneY < pItem->iPlaceY + 22 &&
			ReconStoneY > pItem->iPlaceY)
		{
			pItem->iPlaceX = ReconStoneX + (((pItem->iPlaceX + 22 - ReconStoneX) / 22) * 22) - 11;
			pItem->iPlaceY = ReconStoneY + (((pItem->iPlaceY + 22 - ReconStoneY) / 22) * 22) - 11;
			pItem->iItemSlot = 0;
			TradeColorIndex = SET_ITEM_CHECK_COLOR;
			if (TradeEndX < (TradeColorRect.left + TradeColorRect.right) - 11 || TradeEndY < (TradeColorRect.top + TradeColorRect.bottom) - 11)
			{
				cTrade.InitTradeColorRect();
				return FALSE;
			}
			if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 2))
			{
				TradeColorIndex = NOT_SETTING_COLOR;
				return FALSE;
			}
			return TRUE;
		}
	}
	if (sCraftItem.CraftItem[0].bValid || ForceFlag)
	{
		if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinOS1 || (pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinSE1)
		{
			TradeStartX = 218;
			TradeStartY = 193 + sinInterHeight2;
			TradeEndX = TradeStartX + (3 * 22);
			TradeEndY = TradeStartY + (4 * 22);

			for (i = pItem->iPlaceX + 11; i < pItem->iPlaceX + pItem->iWidth; i += 22)
			{
				for (j = pItem->iPlaceY + 11; j < pItem->iPlaceY + pItem->iHeight; j += 22)
				{
					if (TradeStartX <= i && TradeEndX > i && TradeStartY <= j && TradeEndY > j)
					{
						TradeColorRect.left = TradeStartX + (((i - TradeStartX) / 22) * 22);
						TradeColorRect.top = TradeStartY + (((j - TradeStartY) / 22) * 22);
						TradeColorRect.right = pItem->iWidth;
						TradeColorRect.bottom = pItem->iHeight;
						if (TradeEndX < (TradeColorRect.left + TradeColorRect.right) - 11 ||
							TradeEndY < (TradeColorRect.top + TradeColorRect.bottom) - 11)
						{
							cTrade.InitTradeColorRect();
							return FALSE;
						}

						pItem->iPlaceX = TradeColorRect.left;
						pItem->iPlaceY = TradeColorRect.top;
						pItem->iItemSlot = 0;
						TradeColorIndex = SET_ITEM_CHECK_COLOR;

						if (cCraftItem.ForceFlag)
						{
							if (cShop.haBuyMoneyCheck(cCraftItem.CheckForceOrbPrice(pItem)) == 0)
							{
								TradeColorIndex = NOT_ENOUGH_MONEY;
								return FALSE;
							}
							if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinSE1)
							{
								TradeColorIndex = NOT_SETTING_COLOR;
								return FALSE;
							}
						}
						if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 2))
						{
							TradeColorIndex = NOT_SETTING_COLOR;
							return FALSE;
						}
						return TRUE;
					}
				}
			}
		}
	}
	else
	{
		if (cCraftItem.ForceFlag)
			return FALSE;
		TradeColorIndex = 0;
		TradeCrashItemIndex[0] = 0;
		cTrade.InitTradeColorRect();

		TradeStartX = 58;
		TradeStartY = 193 + sinInterHeight2;
		TradeEndX = TradeStartX + (3 * 22);
		TradeEndY = TradeStartY + (4 * 22);
		if (TradeStartX <= pCursorPos.x && TradeEndX > pCursorPos.x && TradeStartY <= pCursorPos.y && TradeEndY > pCursorPos.y)
		{
			TradeColorRect.left = TradeStartX;
			TradeColorRect.top = TradeStartY;
			TradeColorRect.right = TradeEndX - TradeStartX;
			TradeColorRect.bottom = TradeEndY - TradeStartY;


			pItem->iPlaceX = TradeStartX + ((TradeEndX - TradeStartX) - pItem->iWidth) / 2;
			pItem->iPlaceY = TradeStartY + ((TradeEndY - TradeStartY) - pItem->iHeight) / 2;
			pItem->iItemSlot = 0;
			TradeColorIndex = SET_ITEM_CHECK_COLOR;

			if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 2))
			{
				TradeColorIndex = NOT_SETTING_COLOR;
				return FALSE;
			}
			// ÂòÎïÆ·½ðÇ®¼ì²â
			if (cShop.haBuyMoneyCheck(pItem->sItem.iSalePrice) == 0)
			{
				TradeColorIndex = NOT_ENOUGH_MONEY;
				return FALSE;
			}
			if ((pItem->sItem.sItemID.ToItemType()) != sinWA1 &&
				(pItem->sItem.sItemID.ToItemType()) != sinWC1 &&
				(pItem->sItem.sItemID.ToItemType()) != sinWH1 &&
				(pItem->sItem.sItemID.ToItemType()) != sinWM1 &&
				(pItem->sItem.sItemID.ToItemType()) != sinWP1 &&
				(pItem->sItem.sItemID.ToItemType()) != sinWS1 &&
				(pItem->sItem.sItemID.ToItemType()) != sinWS2 &&
				(pItem->sItem.sItemID.ToItemType()) != sinWT1 &&
				(pItem->sItem.sItemID.ToItemType()) != sinWD1 &&
				(pItem->sItem.sItemID.ToItemType()) != sinWN1 &&
				(pItem->sItem.sItemID.ToItemType()) != sinDA1 &&
				(pItem->sItem.sItemID.ToItemType()) != sinDA2 &&
				(pItem->sItem.sItemID.ToItemType()) != sinDS1 &&
				(pItem->sItem.sItemID.ToItemType()) != sinOM1 &&
				(pItem->sItem.sItemID.ToItemType()) != sinDB1 &&
				(pItem->sItem.sItemID.ToItemType()) != sinDG1 &&
				(pItem->sItem.sItemID.ToItemType()) != sinOA1 &&
				(pItem->sItem.sItemID.ToItemType()) != sinOA2 &&
				(pItem->sItem.sItemID.ToItemType()) != sinOR1 &&
				(pItem->sItem.sItemID.ToItemType()) != sinOS1)
			{
				TradeColorIndex = NOT_SETTING_COLOR;
				return FALSE;
			}
			for (int i = 0; i < sizeof(NoMixItem3) / sizeof(DWORD); i++)
			{
				if (pItem->sItem.sItemID.ToInt() == NoMixItem3[i])
				{
					TradeColorIndex = NOT_SETTING_COLOR;
					return FALSE;
				}
			}

			return TRUE;
		}
	}
	return TRUE;
}
int cCRAFTITEM::SetCraftItem(ItemData *pItem)
{
	if (sCraftItem.CraftItem[0].bValid == NULL && ForceFlag == NULL)
	{
		if (ForceFlag == NULL)
		{
			if ((pItem->sItem.sItemID.ToItemType()) != sinWA1 &&
				(pItem->sItem.sItemID.ToItemType()) != sinWC1 &&
				(pItem->sItem.sItemID.ToItemType()) != sinWH1 &&
				(pItem->sItem.sItemID.ToItemType()) != sinWM1 &&
				(pItem->sItem.sItemID.ToItemType()) != sinWP1 &&
				(pItem->sItem.sItemID.ToItemType()) != sinWS1 &&
				(pItem->sItem.sItemID.ToItemType()) != sinWS2 &&
				(pItem->sItem.sItemID.ToItemType()) != sinWT1 &&
				(pItem->sItem.sItemID.ToItemType()) != sinWD1 &&
				(pItem->sItem.sItemID.ToItemType()) != sinWN1 &&
				(pItem->sItem.sItemID.ToItemType()) != sinDA1 &&
				(pItem->sItem.sItemID.ToItemType()) != sinDA2 &&
				(pItem->sItem.sItemID.ToItemType()) != sinDS1 &&
				(pItem->sItem.sItemID.ToItemType()) != sinOM1 &&
				(pItem->sItem.sItemID.ToItemType()) != sinDB1 &&
				(pItem->sItem.sItemID.ToItemType()) != sinDG1 &&
				(pItem->sItem.sItemID.ToItemType()) != sinOA1 &&
				(pItem->sItem.sItemID.ToItemType()) != sinOA2 &&
				(pItem->sItem.sItemID.ToItemType()) != sinOR1 &&
				(pItem->sItem.sItemID.ToItemType()) != sinOS1)
			{
				return FALSE;
			}
			for (int i = 0; i < sizeof(NoMixItem3) / sizeof(DWORD); i++)
			{
				if (pItem->sItem.sItemID.ToInt() == NoMixItem3[i])
					return FALSE;
			}
			if (pItem->sItem.iItemUniqueID || pItem->sItem.eCraftType == ITEMCRAFTTYPE_Mixing || pItem->sItem.eCraftType == ITEMCRAFTTYPE_Quest || pItem->sItem.eCraftType == ITEMCRAFTTYPE_Aging || pItem->sItem.SpecialItemFlag[0] == CHECK_GIVE_ITEM)
				return FALSE;

			if (cShop.haBuyMoneyCheck(pItem->sItem.iSalePrice) == 0)
			{
				cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_MONEY);
				return FALSE;
			}

			if (sCraftItem.CraftItem[0].bValid == NULL)
			{
				int Startx = 58;
				int Starty = 193 + sinInterHeight2;
				int Endx = Startx + 3 * 22;
				int Endy = Starty + 4 * 22;
				pItem->iPlaceX = Startx + ((Endx - Startx) - pItem->iWidth) / 2;
				pItem->iPlaceY = Starty + ((Endy - Starty) - pItem->iHeight) / 2;
				return TRUE;
			}
		}
	}
	else
	{
		if ((pItem->sItem.sItemID.ToItemType()) == sinOS1 ||
			(pItem->sItem.sItemID.ToItemType()) == sinSE1)
		{
			if (ForceFlag)
			{
				if (cShop.haBuyMoneyCheck(CheckForceOrbPrice(pItem)) == 0)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_MONEY);
					return FALSE;
				}
				if ((pItem->sItem.sItemID.ToItemType()) == sinSE1)
					return FALSE;
			}
			if (ForceFlag == NULL)
			{
				if (sCraftItem.CraftItem[0].bValid == NULL)
					return FALSE;
			}
			if (GetEmptyArea(pItem))
			{
				pItem->iPlaceX = pItem->iPlaceX;
				pItem->iPlaceY = pItem->iPlaceY;
				return TRUE;
			}
		}
	}
	return FALSE;
}

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
int cCRAFTITEM::LastSetCraftItem(ItemData *pItem, int Kind)
{
	int TempLevel = 0;
	int TempLevel2 = 0;
	if (Kind == 0)
	{
		CheckCraftItemForm();

		if (sCraftItem.CraftItem[0].bValid == NULL && ForceFlag == NULL)
		{
			if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK2) != sinSE1 && (pItem->sBaseItemID.ToInt() & sinITEM_MASK2) != sinBI1)
			{
				memcpy(&sCraftItem.CraftItem[0], pItem, sizeof(ItemData));
				sCraftItem.CraftItem[0].iPlaceX = pItem->iPlaceX;
				sCraftItem.CraftItem[0].iPlaceY = pItem->iPlaceY;
				pItem->bValid = 0;
				sinPlaySound(sCraftItem.CraftItem[0].iInvItemSound);
				ReFormCraftItem();
				return TRUE;
			}
		}
		else
		{
			if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinOS1)
			{
				for (int j = 1; j < 15; j++)
				{
					if (!sCraftItem.CraftItem[j].bValid)
					{
						memcpy(&sCraftItem.CraftItem[j], pItem, sizeof(ItemData));
						sCraftItem.CraftItem[j].iPlaceX = pItem->iPlaceX;
						sCraftItem.CraftItem[j].iPlaceY = pItem->iPlaceY;
						pItem->bValid = 0;
						sinPlaySound(sCraftItem.CraftItem[j].iInvItemSound);
						ReFormCraftItem();
						CheckForceOrbPrice();
						return TRUE;
					}
				}
			}
			else if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinSE1)
			{
				// Ï´Ê¯Í·µÈ¼¶ÅÐ¶Ï
				if (sCraftItem.CraftItem[0].bValid)
				{
					TempLevel = sCraftItem.CraftItem[0].sItem.iLevel;

					for (int k = 0; k < MAX_SEEL_COUNT; k++)
					{
						if (pItem->sBaseItemID.ToInt() == sReconItem[k].dwCODE)
						{
							if (!(TempLevel >= sReconItem[k].iLevel[0] && TempLevel <= sReconItem[k].iLevel[1]))
							{
								cMessageBox.ShowMessage(MESSAGE_NOT_RECONITEM);
								return FALSE;
							}
						}
					}
				}
				for (int j = 1; j < 15; j++)
				{
					if (!sCraftItem.CraftItem[j].bValid)
					{
						memcpy(&sCraftItem.CraftItem[j], pItem, sizeof(ItemData));
						sCraftItem.CraftItem[j].iPlaceX = pItem->iPlaceX;
						sCraftItem.CraftItem[j].iPlaceY = pItem->iPlaceY;
						pItem->bValid = 0;
						sinPlaySound(sCraftItem.CraftItem[j].iInvItemSound);
						ReFormCraftItem();
						return TRUE;
					}
				}

			}
			else if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinBI1)
			{
				if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK3) == sin90)
				{
					if (!sCraftItem.CraftItem[14].bValid)
					{
						memcpy(&sCraftItem.CraftItem[14], pItem, sizeof(ItemData));
						sCraftItem.CraftItem[14].iPlaceX = pItem->iPlaceX;
						sCraftItem.CraftItem[14].iPlaceY = pItem->iPlaceY;
						pItem->bValid = 0;
						sinPlaySound(sCraftItem.CraftItem[14].iInvItemSound);
						return TRUE;
					}
				}
			}
		}
	}

	if (Kind == 1)
	{
		if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinOS1)
		{
			for (int j = 1; j < 15; j++)
			{
				if (!sAgingItem.AgingItem[j].bValid)
				{
					memcpy(&sAgingItem.AgingItem[j], pItem, sizeof(ItemData));
					sAgingItem.AgingItem[j].iPlaceX = pItem->iPlaceX;
					sAgingItem.AgingItem[j].iPlaceY = pItem->iPlaceY;
					pItem->bValid = 0;
					sinPlaySound(sAgingItem.AgingItem[j].iInvItemSound);
					return TRUE;
				}
			}
		}
		else
		{
			if (!sAgingItem.AgingItem[0].bValid)
			{
				memcpy(&sAgingItem.AgingItem[0], pItem, sizeof(ItemData));
				sAgingItem.AgingItem[0].iPlaceX = pItem->iPlaceX;
				sAgingItem.AgingItem[0].iPlaceY = pItem->iPlaceY;
				pItem->bValid = 0;
				sinPlaySound(sAgingItem.AgingItem[0].iInvItemSound);
				return TRUE;
			}
		}
	}
	if (Kind == 2)
	{
		for (int j = 0; j < 15; j++)
		{
			if (!sAgingItem.AgingItem[j].bValid)
			{
				memcpy(&sAgingItem.AgingItem[j], pItem, sizeof(ItemData));
				sAgingItem.AgingItem[j].iPlaceX = pItem->iPlaceX;
				sAgingItem.AgingItem[j].iPlaceY = pItem->iPlaceY;
				pItem->bValid = 0;
				sinPlaySound(sAgingItem.AgingItem[j].iInvItemSound);
				return TRUE;
			}
		}
	}
	if (Kind == 3)
	{
		if (!sAgingItem.AgingItem[14].bValid)
		{
			memcpy(&sAgingItem.AgingItem[14], pItem, sizeof(ItemData));
			sAgingItem.AgingItem[14].iPlaceX = pItem->iPlaceX;
			sAgingItem.AgingItem[14].iPlaceY = pItem->iPlaceY;
			pItem->bValid = 0;
			sinPlaySound(sAgingItem.AgingItem[14].iInvItemSound);
			return TRUE;
		}
	}

	return TRUE;

}
int cCRAFTITEM::PickUpCraftItem(int x, int y, int PickUpFlag, int Kind)
{
	int i = 0;
	SelectTradeItemIndex = 0;
	if (Kind == 0)
	{
		for (i = 0; i < 15; i++)
		{
			if (sCraftItem.CraftItem[i].bValid)
			{
				if (sCraftItem.CraftItem[i].iPlaceX < x  &&
					sCraftItem.CraftItem[i].iPlaceX + sCraftItem.CraftItem[i].iWidth > x  &&
					sCraftItem.CraftItem[i].iPlaceY < y  &&
					sCraftItem.CraftItem[i].iPlaceY + sCraftItem.CraftItem[i].iHeight > y)
				{
					int cnt = 0;
					switch (PickUpFlag)
					{
					case 1:
						for (cnt = 1; cnt < 15; cnt++)
						{
							if (i == 0 && sCraftItem.CraftItem[cnt].bValid)
							{
								cMessageBox.ShowMessage(MESSAGE_NOT_AGINGPICKUP);
								return FALSE;
							}
						}
						CheckCraftItemForm();
						memcpy(&MouseItem, &sCraftItem.CraftItem[i], sizeof(ItemData));
						sCraftItem.CraftItem[i].bValid = 0;
						haCraftSortItem(&sCraftItem);

						sinPlaySound(sCraftItem.CraftItem[i].iInvItemSound);
						TradeColorIndex = 0;
						ReFormCraftItem();
						if (ForceFlag)
							CheckForceOrbPrice();
						return TRUE;
						break;
					case 2:
						for (cnt = 1; cnt < 15; cnt++)
						{
							if (i == 0 && sCraftItem.CraftItem[cnt].bValid)
							{
								cMessageBox.ShowMessage(MESSAGE_NOT_AGINGPICKUP);
								return FALSE;
							}
						}
						CheckCraftItemForm();
						if (cCraftItem.CraftCheckEmptyArea(&sCraftItem.CraftItem[i]))
						{
							if (!cInvenTory.AutoSetInvenItem(&sCraftItem.CraftItem[i]))
							{
								sinThrowItemToFeild(&sCraftItem.CraftItem[i]);
								sCraftItem.CraftItem[i].bValid = 0;
							}
						}
						ReFormCraftItem();
						if (ForceFlag)
							CheckForceOrbPrice();
						return TRUE;
						break;
					default:
						SelectTradeItemIndex = i + 1;
						TradeColorIndex = SELECT_ITEM_COLOR;
						sinShowItemInfoFlag = 1;
						cItem.ShowItemInfo(&sCraftItem.CraftItem[i], 2);
						break;
					}
				}
			}
		}
	}
	if (Kind == 1)
	{
		for (i = 0; i < 15; i++)
		{
			if (sAgingItem.AgingItem[i].bValid)
			{
				if (sAgingItem.AgingItem[i].iPlaceX < x  &&
					sAgingItem.AgingItem[i].iPlaceX + sAgingItem.AgingItem[i].iWidth > x  &&
					sAgingItem.AgingItem[i].iPlaceY < y  &&
					sAgingItem.AgingItem[i].iPlaceY + sAgingItem.AgingItem[i].iHeight > y)
				{
					int cnt = 0;
					switch (PickUpFlag)
					{
					case 1:
						for (cnt = 1; cnt < 15; cnt++)
						{
							if (i == 0 && sAgingItem.AgingItem[cnt].bValid)
							{
								cMessageBox.ShowMessage(MESSAGE_NOT_AGINGPICKUP);
								return FALSE;
							}
						}
						memcpy(&MouseItem, &sAgingItem.AgingItem[i], sizeof(ItemData));
						sAgingItem.AgingItem[i].bValid = 0;
						sinPlaySound(sAgingItem.AgingItem[i].iInvItemSound);

						if (i == 0)
						{
							for (int y = 0; y < 4; y++)
							{
								for (int h = 0; h < 3; h++)
									AgingLevelSheltomIndex[y][h] = 0;
							}
						}

						if (sAgingItem.AgingItem[i].sItem.sItemID.ToInt() == (sinBI1 | sin10) ||
							sAgingItem.AgingItem[i].sItem.sItemID.ToInt() == (sinBI1 | sin11) ||
							sAgingItem.AgingItem[i].sItem.sItemID.ToInt() == (sinBI2 | sin66) ||
							sAgingItem.AgingItem[i].sItem.sItemID.ToInt() == (sinBI2 | sin67) ||
							sAgingItem.AgingItem[i].sItem.sItemID.ToInt() == (sinBI2 | sin68) ||
							sAgingItem.AgingItem[i].sItem.sItemID.ToInt() == (sinBI2 | sin78) ||
							sAgingItem.AgingItem[i].sItem.sItemID.ToInt() == (sinBI2 | sin79) ||
							sAgingItem.AgingItem[i].sItem.sItemID.ToInt() == (sinBI2 | sin80) ||
							sAgingItem.AgingItem[i].sItem.sItemID.ToInt() == (sinBI2 | sin81))
							return TRUE;
						TradeColorIndex = 0;
						if ((MouseItem.sItem.sItemID.ToItemType()) == sinMA1 ||
							(MouseItem.sItem.sItemID.ToItemType()) == sinMA2)
							sinMakeItemCheck();
						else
						{
							if (i != 0)
							{
								if (AgingSheltomCnt2)
								{
									AgingSheltomCnt2--;
									AgingCheckSheltomFlag = 0;
								}
							}
						}
						return TRUE;
						break;
					case 2:
						for (cnt = 1; cnt < 15; cnt++)
						{
							if (i == 0 && sAgingItem.AgingItem[cnt].bValid)
							{
								cMessageBox.ShowMessage(MESSAGE_NOT_AGINGPICKUP);
								return FALSE;
							}
						}
						if (cCraftItem.CraftCheckEmptyArea(&sAgingItem.AgingItem[i]))
						{
							if (!cInvenTory.AutoSetInvenItem(&sAgingItem.AgingItem[i]))
							{
								sinThrowItemToFeild(&sAgingItem.AgingItem[i]);
								sAgingItem.AgingItem[i].bValid = 0;
							}
						}
						if (i == 0)
						{
							for (int y = 0; y < 4; y++)
							{
								for (int h = 0; h < 3; h++)
									AgingLevelSheltomIndex[y][h] = 0;
							}
						}
						if (sAgingItem.AgingItem[i].sItem.sItemID.ToInt() == (sinBI1 | sin10) ||
							sAgingItem.AgingItem[i].sItem.sItemID.ToInt() == (sinBI1 | sin11) ||
							sAgingItem.AgingItem[i].sItem.sItemID.ToInt() == (sinBI2 | sin66) ||
							sAgingItem.AgingItem[i].sItem.sItemID.ToInt() == (sinBI2 | sin67) ||
							sAgingItem.AgingItem[i].sItem.sItemID.ToInt() == (sinBI2 | sin68) ||
							sAgingItem.AgingItem[i].sItem.sItemID.ToInt() == (sinBI2 | sin78) ||
							sAgingItem.AgingItem[i].sItem.sItemID.ToInt() == (sinBI2 | sin79) ||
							sAgingItem.AgingItem[i].sItem.sItemID.ToInt() == (sinBI2 | sin80) ||
							sAgingItem.AgingItem[i].sItem.sItemID.ToInt() == (sinBI2 | sin81))
							return TRUE;
						TradeColorIndex = 0;
						if ((MouseItem.sItem.sItemID.ToItemType()) == sinMA1 ||
							(MouseItem.sItem.sItemID.ToItemType()) == sinMA2)
							sinMakeItemCheck();
						else
						{
							if (i != 0)
							{
								if (AgingSheltomCnt2)
								{
									AgingSheltomCnt2--;
									AgingCheckSheltomFlag = 0;
								}
							}
						}
						return TRUE;
						break;
					default:
						SelectTradeItemIndex = i + 1;
						TradeColorIndex = SELECT_ITEM_COLOR;
						sinShowItemInfoFlag = 1;
						cItem.ShowItemInfo(&sAgingItem.AgingItem[i], 2);
						break;
					}
				}
			}
		}
	}
	return FALSE;
}

DWORD SheltomCode[MAX_MIX_STONE] = { sin01,sin02,sin03,sin04,sin05,sin06,sin07,sin08,sin09,sin10,sin11,sin12,sin13,sin14,sin15,sin16 };


int cCRAFTITEM::CraftCheckEmptyArea(ItemData *pItem)
{
	int cntx, cnty;
	int cx, cy;

	RECT	rect;
	int		flag;
	int StartX = 23;
	int StartY = 436;

	cx = (22 * INVENTORY_BOX_ROW) - pItem->iWidth;
	cy = (22 * INVENTORY_BOX_COL) - pItem->iHeight;

	for (cntx = StartX; cntx <= StartX + cx; cntx += 22)
	{
		for (cnty = StartY; cnty <= StartY + cy; cnty += 22)
		{
			flag = 0;
			for (int i = 0; i < INVENTORY_MAXITEM; i++)
			{
				if (cInvenTory.InvenItem[i].bValid)
				{
					rect.left	= cInvenTory.InvenItem[i].iPlaceX;
					rect.right	= cInvenTory.InvenItem[i].iPlaceX + cInvenTory.InvenItem[i].iWidth;
					rect.top	= cInvenTory.InvenItem[i].iPlaceY;
					rect.bottom = cInvenTory.InvenItem[i].iPlaceY + cInvenTory.InvenItem[i].iHeight;

					if (cntx > rect.left - pItem->iWidth &&
						cntx < rect.right &&
						cnty > rect.top - pItem->iHeight &&
						cnty < rect.bottom)
						flag++;
				}
			}
			if (flag == 0)
			{
				pItem->iPlaceX = cntx;
				pItem->iPlaceY = cnty;
				pItem->iItemSlot = 0;
				return TRUE;
			}
		}
	}

	return FALSE;
}
int cCRAFTITEM::GetEmptyArea(ItemData *pItem)
{
	int cntx, cnty;
	int cx, cy;

	RECT	rect;
	int		flag;
	int StartX = 218;
	int StartY = 193 + sinInterHeight2;

	cx = (22 * 3) - pItem->iWidth;
	cy = (22 * 4) - pItem->iHeight;

	for (cnty = StartY; cnty <= StartY + cy; cnty += 22)
	{
		for (cntx = StartX; cntx <= StartX + cx; cntx += 22)
		{
			flag = 0;
			for (int i = 1; i < 14; i++)
			{
				if (sCraftItem.CraftItem[i].bValid)
				{
					rect.left	= sCraftItem.CraftItem[i].iPlaceX;
					rect.right	= sCraftItem.CraftItem[i].iPlaceX + sCraftItem.CraftItem[i].iWidth;
					rect.top	= sCraftItem.CraftItem[i].iPlaceY;
					rect.bottom = sCraftItem.CraftItem[i].iPlaceY + sCraftItem.CraftItem[i].iHeight;

					if (cntx > rect.left - pItem->iWidth &&
						cntx < rect.right &&
						cnty > rect.top - pItem->iHeight &&
						cnty < rect.bottom)
						flag++;
				}
			}
			if (flag == 0)
			{
				pItem->iPlaceX = cntx;
				pItem->iPlaceY = cnty;
				pItem->iItemSlot = 0;
				return TRUE;
			}
		}
	}

	return FALSE;
}
int cCRAFTITEM::CancelMixItem()
{
	if (MixItemNoCopyFlag)
		return FALSE;
	for (int i = 0; i < 15; i++)
	{
		if (sCraftItem.CraftItem[i].bValid)
		{
			if (!cInvenTory.AutoSetInvenItem(&sCraftItem.CraftItem[i]))
			{
				sinThrowItemToFeild(&sCraftItem.CraftItem[i]);
				sCraftItem.CraftItem[i].bValid = 0;
			}
		}
	}

	cCraftItem.OpenFlag = 0;
	memset(&sCraftItem, 0, sizeof(sCRAFTITEM));
	ResetInvenItemCode();

	memset(&sCraftItem_Recv, 0, sizeof(sCRAFTITEM_SERVER));
	memset(&sCraftItem_Send, 0, sizeof(sCRAFTITEM_SERVER));

	ForceFlag = 0;
	ForceItemPrice = 0;
	ForceItemPrice2 = 0;
	return TRUE;
}

int CraftItemCheckDelayTime = 0;

//ºÏ³É¼ì²âÎïÆ·
int cCRAFTITEM::CheckHackCraftItem()
{
	CraftItemCheckDelayTime++;
	if (CraftItemCheckDelayTime < 70 * 10)
		return FALSE;

	CraftItemCheckDelayTime = 0;

	unsigned int AddItemCheckSum = 0;
	unsigned int CheckAddItemData = 2774094026;

	for (int i = 0; i < MAX_CRAFTITEM_INFO; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			AddItemCheckSum += (int)((j + 1)*sCraftItem_Info[i].AddElement[j]);
			AddItemCheckSum += (j + 1)*sCraftItem_Info[i].AddItem[j];
			AddItemCheckSum += (j + 1)*sCraftItem_Info[i].ElementKind[j];
			AddItemCheckSum += (j + 1)*sCraftItem_Info[i].PlusElementCode[j];
			AddItemCheckSum += (j + 1)*sCraftItem_Info[i].MainItemCode[j];
		}
	}
	if (CheckAddItemData != AddItemCheckSum)
		SendSetHackUser(8);

	return TRUE;
}
int cCRAFTITEM::CheckCraftItemForm()
{
	int TempCheckDataSum = 0;

	if (!cCraftItem.ForceFlag)
	{
		for (int i = 0; i < 15; i++)
		{
			if (sCraftItem.CraftItem[i].bValid)
			{
				TempCheckDataSum += (i + 1)*sCraftItem.CraftItem[i].iPlaceX;
				TempCheckDataSum += (i + 1)*sCraftItem.CraftItem[i].iPlaceY;
				TempCheckDataSum += sCraftItem.CraftItem[i].sItem.iChk2;
				TempCheckDataSum += sCraftItem.CraftItem[i].sItem.iChk1;
			}
		}
	}
	return TRUE;

}

int cCRAFTITEM::ReFormCraftItem()
{
	CraftItemCheckSum = 0;
	for (int i = 0; i < 15; i++)
	{
		if (sCraftItem.CraftItem[i].bValid)
		{
			CraftItemCheckSum += (i + 1)*sCraftItem.CraftItem[i].iPlaceX;
			CraftItemCheckSum += (i + 1)*sCraftItem.CraftItem[i].iPlaceY;
			CraftItemCheckSum += sCraftItem.CraftItem[i].sItem.iChk2;
			CraftItemCheckSum += sCraftItem.CraftItem[i].sItem.iChk1;
		}
	}

	return TRUE;
}
int cTRADE::CheckTradeItemForm()
{
	int TempCheckDataSum = 0;
	for (int i = 0; i < MAX_TRADE_ITEM; i++)
	{
		if (sTrade.TradeItem[i].bValid)
		{
			TempCheckDataSum += (i + 1)*sTrade.TradeItem[i].iPlaceX;
			TempCheckDataSum += (i + 1)*sTrade.TradeItem[i].iPlaceY;
			TempCheckDataSum += sTrade.TradeItem[i].sItem.iChk2;
			TempCheckDataSum += sTrade.TradeItem[i].sItem.iChk1;
		}
	}
	if (TempCheckDataSum != TradeItemCheckSum)
		SendSetHackUser(10);

	return TRUE;

}

int cTRADE::ReFormTradeItem()
{
	TradeItemCheckSum = 0;
	for (int i = 0; i < MAX_TRADE_ITEM; i++)
	{
		if (sTrade.TradeItem[i].bValid)
		{
			TradeItemCheckSum += (i + 1)*sTrade.TradeItem[i].iPlaceX;
			TradeItemCheckSum += (i + 1)*sTrade.TradeItem[i].iPlaceY;
			TradeItemCheckSum += sTrade.TradeItem[i].sItem.iChk2;
			TradeItemCheckSum += sTrade.TradeItem[i].sItem.iChk1;
		}
	}
	return TRUE;
}

int cAGING::CancelAgingItem(int Flag)
{
	if (MixItemNoCopyFlag)
		return FALSE;
	for (int i = 0; i < 15; i++)
	{
		if (sAgingItem.AgingItem[i].bValid)
		{
			if (!cInvenTory.AutoSetInvenItem(&sAgingItem.AgingItem[i]))
				sinThrowItemToFeild(&sAgingItem.AgingItem[i]);

			sAgingItem.AgingItem[i].bValid = 0;
		}
	}

	for (int y = 0; y < 4; y++)
	{
		for (int h = 0; h < 3; h++)
			AgingLevelSheltomIndex[y][h] = 0;
	}

	AgingCheckSheltomFlag = 0;
	AgingSheltomCnt2 = 0;
	if (!Flag)
		cAging.OpenFlag = 0;

	ResetInvenItemCode();
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

int cAGING::SetAgingItemAreaCheck(ItemData *pItem)
{
	int SheltomIndex2 = 0;
	int i, j;
	if (pItem->sItem.sItemID.ToInt() == (sinBI1 | sin10) ||
		pItem->sItem.sItemID.ToInt() == (sinBI1 | sin11) ||
		pItem->sItem.sItemID.ToInt() == (sinBI2 | sin66) ||
		pItem->sItem.sItemID.ToInt() == (sinBI2 | sin67) ||
		pItem->sItem.sItemID.ToInt() == (sinBI2 | sin68) ||
		pItem->sItem.sItemID.ToInt() == (sinBI2 | sin78) ||
		pItem->sItem.sItemID.ToInt() == (sinBI2 | sin79) ||
		pItem->sItem.sItemID.ToInt() == (sinBI2 | sin80) ||
		pItem->sItem.sItemID.ToInt() == (sinBI2 | sin81))
	{
		int AgingStoneX = 159 + 11, AgingStoneY = 268 + 11 + sinInterHeight2;
		TradeColorIndex = 0;
		cTrade.InitTradeColorRect();
		if (AgingStoneX <=pItem->iPlaceX + 22 &&
			AgingStoneX > pItem->iPlaceX &&
			AgingStoneY < pItem->iPlaceY + 22 &&
			AgingStoneY > pItem->iPlaceY)
		{
			pItem->iPlaceX = AgingStoneX + (((pItem->iPlaceX + 22 - AgingStoneX) / 22) * 22) - 11;
			pItem->iPlaceY = AgingStoneY + (((pItem->iPlaceY + 22 - AgingStoneY) / 22) * 22) - 11;
			pItem->iItemSlot = 0;
			TradeColorIndex = SET_ITEM_CHECK_COLOR;
			if (TradeEndX < (TradeColorRect.left + TradeColorRect.right) - 11 ||
				TradeEndY < (TradeColorRect.top + TradeColorRect.bottom) - 11)
			{
				cTrade.InitTradeColorRect();
				return FALSE;
			}
			if (sAgingItem.AgingItem[0].bValid == NULL)
			{
				TradeColorIndex = NOT_SETTING_COLOR;
				return FALSE;
			}
			switch (pItem->sItem.sItemID.ToInt())
			{
			case sinBI2 | sin66:
				if (sAgingItem.AgingItem[0].sItem.sAgeLevel >= 10)
				{
					TradeColorIndex = NOT_SETTING_COLOR;
					return FALSE;
				}
				break;
			case sinBI2 | sin67:
				if (sAgingItem.AgingItem[0].sItem.sAgeLevel >= 15)
				{
					TradeColorIndex = NOT_SETTING_COLOR;
					return FALSE;
				}
				break;
			case sinBI2 | sin68:
				if (sAgingItem.AgingItem[0].sItem.sAgeLevel >= 20)
				{
					TradeColorIndex = NOT_SETTING_COLOR;
					return FALSE;
				}
				break;
			}
			if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 3))
			{
				TradeColorIndex = NOT_SETTING_COLOR;
				return FALSE;
			}
			return TRUE;
		}
	}
	if ((pItem->sItem.sItemID.ToItemType()) == sinMA2)
	{
		if (sAgingItem.AgingItem[0].bValid && (sAgingItem.AgingItem[0].sItem.sItemID.ToItemType()) == sinMA1)
		{
			TradeColorIndex = 0;
			TradeCrashItemIndex[0] = 0;
			cTrade.InitTradeColorRect();
			TradeStartX = 218;
			TradeStartY = 193 + sinInterHeight2;
			TradeEndX = TradeStartX + (3 * 22);
			TradeEndY = TradeStartY + (4 * 22);

			for (i = pItem->iPlaceX + 11; i < pItem->iPlaceX + pItem->iWidth; i += 22)
			{
				for (j = pItem->iPlaceY + 11; j < pItem->iPlaceY + pItem->iHeight; j += 22)
				{
					if (TradeStartX <= i && TradeEndX > i && TradeStartY <= j && TradeEndY > j)
					{
						TradeColorRect.left = TradeStartX + (((i - TradeStartX) / 22) * 22);
						TradeColorRect.top = TradeStartY + (((j - TradeStartY) / 22) * 22);
						TradeColorRect.right = pItem->iWidth;
						TradeColorRect.bottom = pItem->iHeight;
						if (TradeEndX < (TradeColorRect.left + TradeColorRect.right) - 11 ||
							TradeEndY < (TradeColorRect.top + TradeColorRect.bottom) - 11)
						{
							cTrade.InitTradeColorRect();
							return FALSE;
						}

						pItem->iPlaceX = TradeColorRect.left;
						pItem->iPlaceY = TradeColorRect.top;
						pItem->iItemSlot = 0;
						TradeColorIndex = SET_ITEM_CHECK_COLOR;

						if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 3))
						{
							TradeColorIndex = NOT_SETTING_COLOR;
							return FALSE;
						}
						return TRUE;
					}
				}
			}
		}
	}
	if ((pItem->sItem.sItemID.ToItemType()) == sinMA1)
	{
		TradeColorIndex = 0;
		TradeCrashItemIndex[0] = 0;
		cTrade.InitTradeColorRect();

		TradeStartX = 58;
		TradeStartY = 193 + sinInterHeight2;
		TradeEndX = TradeStartX + (3 * 22);
		TradeEndY = TradeStartY + (4 * 22);
		if (TradeStartX <= pCursorPos.x && TradeEndX > pCursorPos.x && TradeStartY <= pCursorPos.y && TradeEndY > pCursorPos.y)
		{
			TradeColorRect.left = TradeStartX;
			TradeColorRect.top = TradeStartY;
			TradeColorRect.right = TradeEndX - TradeStartX;
			TradeColorRect.bottom = TradeEndY - TradeStartY;

			pItem->iPlaceX = TradeStartX + ((TradeEndX - TradeStartX) - pItem->iWidth) / 2;
			pItem->iPlaceY = TradeStartY + ((TradeEndY - TradeStartY) - pItem->iHeight) / 2;
			pItem->iItemSlot = 0;
			TradeColorIndex = SET_ITEM_CHECK_COLOR;
			if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 3))
			{
				TradeColorIndex = NOT_SETTING_COLOR;
				return FALSE;
			}
			return TRUE;
		}
	}
	for (int y = 0; y < MAX_SHELTOM; y++)
	{
		if (SheltomCODE[y] == (pItem->sItem.sItemID.ToItemIndex()))
		{
			SheltomIndex2 = y + 1;
			break;
		}
	}

	int AgingOkWeaponGroupFlag = 0;
	TradeColorIndex = 0;
	TradeCrashItemIndex[0] = 0;
	cTrade.InitTradeColorRect();

	if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinOS1)
	{
		for (int p = 0; p < 4; p++)
		{
			for (int m = 0; m < 3; m++)
			{
				if (AgingLevelSheltomIndex[p][m] == SheltomIndex2)
				{
					TradeStartX = AgingLevelSheltomXY[p][m].x;
					TradeStartY = AgingLevelSheltomXY[p][m].y;
					TradeEndX = TradeStartX + 22;
					TradeEndY = TradeStartY + 22;

					for (i = pItem->iPlaceX + 11; i < pItem->iPlaceX + pItem->iWidth; i += 22)
					{
						for (j = pItem->iPlaceY + 11; j < pItem->iPlaceY + pItem->iHeight; j += 22)
						{
							if (TradeStartX <= i && TradeEndX > i && TradeStartY <= j && TradeEndY > j)
							{
								TradeColorRect.left = TradeStartX + (((i - TradeStartX) / 22) * 22);
								TradeColorRect.top = TradeStartY + (((j - TradeStartY) / 22) * 22);
								TradeColorRect.right = pItem->iWidth;
								TradeColorRect.bottom = pItem->iHeight;
								if (TradeEndX < (TradeColorRect.left + TradeColorRect.right) - 11 ||
									TradeEndY < (TradeColorRect.top + TradeColorRect.bottom) - 11)
								{
									cTrade.InitTradeColorRect();
									return FALSE;
								}

								pItem->iPlaceX = TradeColorRect.left;
								pItem->iPlaceY = TradeColorRect.top;
								pItem->iItemSlot = 0;
								if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK3) > sin20)
									TradeColorIndex = NOT_SETTING_COLOR;
								else
									TradeColorIndex = SET_ITEM_CHECK_COLOR;

								if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 3))
								{
									TradeColorIndex = NOT_SETTING_COLOR;
									return FALSE;
								}
								return TRUE;
							}
						}
					}
				}
			}
		}
	}
	else
	{
		TradeColorIndex = 0;
		TradeCrashItemIndex[0] = 0;
		cTrade.InitTradeColorRect();

		TradeStartX = 58;
		TradeStartY = 193 + sinInterHeight2;
		TradeEndX = TradeStartX + (3 * 22);
		TradeEndY = TradeStartY + (4 * 22);
		if (TradeStartX <= pCursorPos.x && TradeEndX > pCursorPos.x && TradeStartY <= pCursorPos.y && TradeEndY > pCursorPos.y)
		{
			TradeColorRect.left = TradeStartX;
			TradeColorRect.top = TradeStartY;
			TradeColorRect.right = TradeEndX - TradeStartX;
			TradeColorRect.bottom = TradeEndY - TradeStartY;

			pItem->iPlaceX = TradeStartX + ((TradeEndX - TradeStartX) - pItem->iWidth) / 2;
			pItem->iPlaceY = TradeStartY + ((TradeEndY - TradeStartY) - pItem->iHeight) / 2;
			pItem->iItemSlot = 0;
			TradeColorIndex = SET_ITEM_CHECK_COLOR;

			for (int i = 0; i < MAX_AGING_ITEM; i++)
			{
				if ((pItem->sBaseItemID.ToInt() &  sinITEM_MASK2) == AgingItemCode3[i])
					AgingOkWeaponGroupFlag = 1;
			}

			if (!AgingOkWeaponGroupFlag || pItem->sItem.sAgeLevel >= MAX_AGING)
			{
				TradeColorIndex = NOT_AGING_ITEM;
				return FALSE;
			}

			if (pItem->sItem.iItemUniqueID || pItem->sItem.eCraftType == ITEMCRAFTTYPE_Mixing || pItem->sItem.bMaturing == 1 || pItem->sItem.eCraftType == ITEMCRAFTTYPE_Quest || pItem->sItem.SpecialItemFlag[0] == CHECK_GIVE_ITEM)
			{
				TradeColorIndex = NOT_AGING_ITEM;
				return FALSE;
			}

			for (int i = 0; i < sizeof(NoMixItem3) / sizeof(DWORD); i++)
			{
				if (NoMixItem3[i] == pItem->sItem.sItemID.ToInt())
				{
					TradeColorIndex = NOT_AGING_ITEM;
					return FALSE;
				}
			}

			if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 3))
			{
				TradeColorIndex = NOT_SETTING_COLOR;
				return FALSE;
			}
			if (cShop.haBuyMoneyCheck((pItem->sItem.iSalePrice + (pItem->sItem.iSalePrice*pItem->sItem.sAgeLevel)) / 2) == 0)
			{
				TradeColorIndex = NOT_ENOUGH_MONEY;
				return FALSE;
			}
			return TRUE;
		}
	}

	return TRUE;
}
int cAGING::SetAgingItem(ItemData *pItem)
{
	int SheltomIndex2 = 0;

	if (pItem->sItem.sItemID.ToInt() == (sinBI1 | sin10) ||
		pItem->sItem.sItemID.ToInt() == (sinBI1 | sin11) ||
		pItem->sItem.sItemID.ToInt() == (sinBI2 | sin66) ||
		pItem->sItem.sItemID.ToInt() == (sinBI2 | sin67) ||
		pItem->sItem.sItemID.ToInt() == (sinBI2 | sin68) ||
		pItem->sItem.sItemID.ToInt() == (sinBI2 | sin78) ||
		pItem->sItem.sItemID.ToInt() == (sinBI2 | sin79) ||
		pItem->sItem.sItemID.ToInt() == (sinBI2 | sin80) ||
		pItem->sItem.sItemID.ToInt() == (sinBI2 | sin81))
	{
		if (sAgingItem.AgingItem[0].bValid && sAgingItem.AgingItem[14].bValid == NULL)
		{
			switch (pItem->sItem.sItemID.ToInt())
			{
			case sinBI2 | sin66:
				if (sAgingItem.AgingItem[0].sItem.sAgeLevel >= 10)
					return FALSE;
			case sinBI2 | sin67:
				if (sAgingItem.AgingItem[0].sItem.sAgeLevel >= 15)
					return FALSE;
			case sinBI2 | sin68:
				if (sAgingItem.AgingItem[0].sItem.sAgeLevel >= 20)
					return FALSE;
			}
			pItem->iPlaceX = 159;
			pItem->iPlaceY = 268 + sinInterHeight2;
			return TRUE;
		}
	}
	if ((pItem->sItem.sItemID.ToItemType()) == sinMA2)
	{
		if (sAgingItem.AgingItem[0].bValid && (sAgingItem.AgingItem[0].sItem.sItemID.ToItemType()) == sinMA1)
		{
			if (GetEmptyArea(pItem))
			{
				pItem->iPlaceX = pItem->iPlaceX;
				pItem->iPlaceY = pItem->iPlaceY;
				return TRUE;
			}
		}
	}
	if ((pItem->sItem.sItemID.ToItemType()) == sinMA1)
	{
		if (sAgingItem.AgingItem[0].bValid == NULL)
		{
			int Startx = 58;
			int Starty = 193 + sinInterHeight2;
			int Endx = Startx + 3 * 22;
			int Endy = Starty + 4 * 22;

			pItem->iPlaceX = Startx + ((Endx - Startx) - pItem->iWidth) / 2;
			pItem->iPlaceY = Starty + ((Endy - Starty) - pItem->iHeight) / 2;
			return TRUE;
		}
	}
	for (int y = 0; y < MAX_SHELTOM; y++)
	{
		if (SheltomCODE[y] == (pItem->sItem.sItemID.ToItemIndex()))
		{
			SheltomIndex2 = y + 1;
			break;
		}
	}

	if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinOS1)
	{
		for (int p = 0; p < 4; p++)
		{
			for (int m = 0; m < 3; m++)
			{
				if (AgingLevelSheltomIndex[p][m] == SheltomIndex2)
				{
					int ErrorFlag = 0;

					for (int i = 1; i < 14; i++)
					{
						if (sAgingItem.AgingItem[i].bValid)
						{
							int x = sAgingItem.AgingItem[i].iPlaceX;
							int y = sAgingItem.AgingItem[i].iPlaceY;

							if (x == AgingLevelSheltomXY[p][m].x && y == AgingLevelSheltomXY[p][m].y)
								ErrorFlag++;
						}
						if (ErrorFlag == 0 && sAgingItem.AgingItem[i].bValid == NULL)
						{
							pItem->iPlaceX = AgingLevelSheltomXY[p][m].x;
							pItem->iPlaceY = AgingLevelSheltomXY[p][m].y;
							return TRUE;
						}
					}
				}
			}
		}
	}
	else
	{
		int Flag = 0;

		for (int i = 0; i < MAX_AGING_ITEM; i++)
		{
			if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == AgingItemCode3[i])
				Flag++;
		}
		if (Flag == 0)
			return FALSE;

		if (pItem->sItem.sAgeLevel >= MAX_AGING)
			return FALSE;

		if (pItem->sItem.iItemUniqueID || pItem->sItem.eCraftType == ITEMCRAFTTYPE_Mixing || pItem->sItem.bMaturing == 1 || pItem->sItem.eCraftType == ITEMCRAFTTYPE_Quest || pItem->sItem.SpecialItemFlag[0] == CHECK_GIVE_ITEM)
			return FALSE;

		for (int i = 0; i < sizeof(NoMixItem3) / sizeof(DWORD); i++)
		{
			if (NoMixItem3[i] == pItem->sItem.sItemID.ToInt())
				return FALSE;
		}
		if (cShop.haBuyMoneyCheck((pItem->sItem.iSalePrice + (pItem->sItem.iSalePrice*pItem->sItem.sAgeLevel)) / 2) == 0)
		{
			cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_MONEY);
			return FALSE;
		}

		if (sAgingItem.AgingItem[0].bValid == NULL)
		{
			int Startx = 58;
			int Starty = 193 + sinInterHeight2;
			int Endx = Startx + 3 * 22;
			int Endy = Starty + 4 * 22;
			pItem->iPlaceX = Startx + ((Endx - Startx) - pItem->iWidth) / 2;
			pItem->iPlaceY = Starty + ((Endy - Starty) - pItem->iHeight) / 2;
			return TRUE;
		}
	}
	return FALSE;
}
int cAGING::GetEmptyArea(ItemData *pItem)
{
	int cntx, cnty;
	int cx, cy;

	RECT	rect;
	int		flag;
	int StartX = 218;
	int StartY = 193 + sinInterHeight2;

	cx = (22 * 3) - pItem->iWidth;
	cy = (22 * 4) - pItem->iHeight;

	for (cnty = StartY; cnty <= StartY + cy; cnty += 22)
	{
		for (cntx = StartX; cntx <= StartX + cx; cntx += 22)
		{
			flag = 0;
			for (int i = 1; i < 14; i++)
			{
				if (sAgingItem.AgingItem[i].bValid)
				{
					rect.left	= sAgingItem.AgingItem[i].iPlaceX;
					rect.right	= sAgingItem.AgingItem[i].iPlaceX + sCraftItem.CraftItem[i].iWidth;
					rect.top	= sAgingItem.AgingItem[i].iPlaceY;
					rect.bottom = sAgingItem.AgingItem[i].iPlaceY + sCraftItem.CraftItem[i].iHeight;

					if (cntx > rect.left - pItem->iWidth &&
						cntx < rect.right &&
						cnty > rect.top - pItem->iHeight &&
						cnty < rect.bottom)
						flag++;
				}
			}
			if (flag == 0)
			{
				pItem->iPlaceX = cntx;
				pItem->iPlaceY = cnty;
				pItem->iItemSlot = 0;
				return TRUE;
			}
		}
	}

	return FALSE;
}
int AgingItemCheckDelayTime = 0;

int cAGING::CheckAgingData()
{
	return TRUE;
}
int CheckCraftMoney = 0;


int cCRAFTITEM::sinSendCraftItem()
{
	if (MixItemNoCopyFlag)
		return FALSE;

	int i = 0;

	// ºÏ³É
	memcpy(&sCraftItemBackUp, &sCraftItem, sizeof(sCRAFTITEM));

	MixItemNoCopyFlag = 1;

	// Á¦Á¿Ê¯Í·
	if (ForceFlag)
	{
		memset(&sCraftItem_Send.DesCraftItem, 0, sizeof(ItemData));
		memset(&sCraftItemBackUp, 0, sizeof(sCRAFTITEM));
		sCraftItem_Send.DesCraftItem.sBaseItemID = 1000;
		sCraftItem_Send.Money = ForceItemPrice;

	}
	if (cCraftItem.iReconItemFlag)
	{
		memset(&sCraftItem_Send.DesCraftItem, 0, sizeof(ItemData));
		memset(&sCraftItemBackUp, 0, sizeof(sCRAFTITEM));
		sCraftItem_Send.DocIndex = 2000;
	}
	if (sCraftItem.CraftItem[0].bValid)
	{
		sCraftItem_Send.DesCraftItem = sCraftItem.CraftItem[0];
		sCraftItem_Send.Money = sCraftItem.CraftItem[0].sItem.iSalePrice;
	}
	for (i = 0; i < 12; i++)
	{
		if (sCraftItem.CraftItem[i + 1].bValid)
		{
			sCraftItem_Send.SheltomCode[i] = sCraftItem.CraftItem[i + 1].sBaseItemID.ToInt();
			sCraftItem_Send.CheckSum[i] = sCraftItem.CraftItem[i + 1].sItem.iChk2;
			sCraftItem_Send.Head[i] = sCraftItem.CraftItem[i + 1].sItem.iChk1;
		}
	}
	if (sCraftItem.CraftItem[14].bValid)
	{
		sCraftItem_Send.A_StoneItemCode = sCraftItem.CraftItem[14].sBaseItemID.ToInt();
		sCraftItem_Send.A_StoneCheckSum = sCraftItem.CraftItem[14].sItem.iChk2;
		sCraftItem_Send.A_StoneHead = sCraftItem.CraftItem[14].sItem.iChk1;
	}

	CheckCraftMoney = sCraftItem_Send.Money;

	CraftItemSendServerIndex++;
	sCraftItem_Send.Index = CraftItemSendServerIndex;

	cCraftItem.iReconItemFlag = 0;

	if (ForceFlag)
		SendWingItemToServer(&sCraftItem_Send);
	else
		SendCraftItemToServer(&sCraftItem_Send);

	return TRUE;
}
int cAGING::sinSendAgingItem()
{
	int i = 0;

	memcpy(&sAgingItemBackUp, &sAgingItem, sizeof(sAGINGITEM));

	MixItemNoCopyFlag = 1;
	if (sAgingItem.AgingItem[0].bValid)
		sAging_Send.DesCraftItem = sAgingItem.AgingItem[0];
	for (i = 0; i < 12; i++)
	{
		if (sAgingItem.AgingItem[i + 1].bValid)
		{
			sAging_Send.SheltomCode[i] = sAgingItem.AgingItem[i + 1].sBaseItemID.ToInt();
			sAging_Send.CheckSum[i] = sAgingItem.AgingItem[i + 1].sItem.iChk2;
			sAging_Send.Head[i] = sAgingItem.AgingItem[i + 1].sItem.iChk1;
		}
	}
	if (sAgingItem.AgingItem[14].bValid)
	{
		sAging_Send.A_StoneItemCode = sAgingItem.AgingItem[14].sBaseItemID.ToInt();
		sAging_Send.A_StoneCheckSum = sAgingItem.AgingItem[14].sItem.iChk2;
		sAging_Send.A_StoneHead = sAgingItem.AgingItem[14].sItem.iChk1;
	}

	// ¶ÍÔì½ðÇ®
	sAging_Send.Money = sAgingItem.AgingItem[0].sItem.iSalePrice;
	CheckCraftMoney = sAging_Send.Money;

	CraftItemSendServerIndex++;
	sAging_Send.Index = CraftItemSendServerIndex;

	SendAgingItemToServer(&sAging_Send);

	// ¶ÍÔì½ðÇ®
	int Price = ((sAgingItem.AgingItem[0].sItem.sAgeLevel + 1)*sAgingItem.AgingItem[0].sItem.iSalePrice) / 2;

	CheckCharForm();
	sinMinusMoney(Price, 1);
	ReformCharForm();
	SendSaveMoney();
	return TRUE;
}
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
int cAGING::sinRecvAgingItemResult(sCRAFTITEM_SERVER *pCraftItem_Server)
{
	if (pCraftItem_Server->DesCraftItem.sItem.eCraftType == ITEMCRAFTTYPE_QuestWeapon)
	{
		if (pCraftItem_Server->Result)
		{
			cInvenTory.DeleteInvenItemToServer(TempQuestItem.sItem.sItemID.ToInt(), TempQuestItem.sItem.iChk1, TempQuestItem.sItem.iChk2);
			memset(&TempQuestItem, 0, sizeof(ItemData));

			pCraftItem_Server->DesCraftItem.sItem.sMatureBar.sMin = pCraftItem_Server->DesCraftItem.sItem.sMatureBar.sMax;
			if (cInvenTory.AutoSetInvenItem(&pCraftItem_Server->DesCraftItem))
			{
				cMessageBox.ShowMessage(MESSAGE_QUEST_ITEM_AGING);
				sinPlaySound(SIN_SOUND_EAT_POTION2);
				StartEffect(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, EFFECT_AGING);
				sinQuest_ChangeJob3.Monster[0] = pCraftItem_Server->DesCraftItem.sItem.sAgeLevel;
				StartQuest_Code(sinQuest_ChangeJob3.CODE);
			}
			if (pCraftItem_Server->DesCraftItem.sItem.sAgeLevel == 4)
				sinQuest_ChangeJob3.State = 4;
		}
		else
			cInvenTory.AutoSetInvenItem(&TempQuestItem);

		memset(&sAging_Recv, 0, sizeof(sCRAFTITEM_SERVER));
		memset(&sAging_Send, 0, sizeof(sCRAFTITEM_SERVER));
		NotChangeSetItemFlag = 0;
		return TRUE;
	}

	if (!cAging.OpenFlag)
	{
		AgingCheckSheltomFlag = 0;
		AgingSheltomCnt2 = 0;
		MixItemNoCopyFlag = 0;
		memset(&sCraftItem_Recv, 0, sizeof(sCRAFTITEM_SERVER));
		memset(&sCraftItem_Send, 0, sizeof(sCRAFTITEM_SERVER));
		MixCancelButtonDelayFlag = 0;
		return FALSE;
	}

	if (pCraftItem_Server->Result)
	{
		if ((pCraftItem_Server->DesCraftItem.sItem.sItemID.ToItemType()) == sinQT1)
			sinSetQuestItem(&pCraftItem_Server->DesCraftItem.sItem);
		else
		{
			if (!cInvenTory.AutoSetInvenItem(&pCraftItem_Server->DesCraftItem))
				sinThrowItemToFeild(&pCraftItem_Server->DesCraftItem);

			CheckCharForm();
			switch (pCraftItem_Server->Result)
			{
			case 1:
				cMessageBox.ShowMessage(MESSAGE_AGING_LEVEL_DOWN1);
				sinPlaySound(SIN_SOUND_FAILD_MIXITEM);
				break;
			case 2:
				cMessageBox.ShowMessage(MESSAGE_AGING_LEVEL_DOWN2);
				sinPlaySound(SIN_SOUND_FAILD_MIXITEM);
				break;
			case 3:
				cMessageBox.ShowMessage(MESSAGE_AGING_LEVEL_PLUS);
				sinPlaySound(SIN_SOUND_EAT_POTION2);
				break;
			case 4:
				cMessageBox.ShowMessage(MESSAGE_AGING_LEVEL_PLUS2);
				sinPlaySound(SIN_SOUND_EAT_POTION2);
				break;
			case 5:
#ifdef ENGLISH_LANGUAGE
				cMessageBox.ShowMessageEvent("Upgrade level has increased by +10     ");
#else
				cMessageBox.ShowMessageEvent("Éý¼¶µÈ¼¶ÒÑ¾­Ôö¼ÓÁË+10     ");
#endif
				sinPlaySound(SIN_SOUND_EAT_POTION2);
				break;
			case 6:
#ifdef ENGLISH_LANGUAGE
				cMessageBox.ShowMessageEvent("Upgrade level has increased by +15     ");
#else
				cMessageBox.ShowMessageEvent("Éý¼¶µÈ¼¶ÒÑ¾­Ôö¼ÓÁË+15     ");
#endif
				sinPlaySound(SIN_SOUND_EAT_POTION2);
				break;
			case 7:
#ifdef ENGLISH_LANGUAGE
				cMessageBox.ShowMessageEvent("Upgrade level has increased by +20     ");
#else
				cMessageBox.ShowMessageEvent("Éý¼¶µÈ¼¶ÒÑ¾­Ôö¼ÓÁË+20     ");
#endif
				sinPlaySound(SIN_SOUND_EAT_POTION2);
				break;
			}
			SendSaveMoney();
			ReformCharForm();
		}
	}
	else
	{
		sinPlaySound(SIN_SOUND_FAILD_MIXITEM);
		cMessageBox.ShowMessage(MESSAGE_FAILD_AGING_ITEM);
	}

	for (int y = 0; y < 4; y++)
	{
		for (int h = 0; h < 3; h++)
			AgingLevelSheltomIndex[y][h] = 0;
	}

	for (int i = 0; i < 15; i++)
	{
		if (sAgingItemBackUp.AgingItem[i].bValid)
			cInvenTory.DeleteInvenItemToServer(sAgingItemBackUp.AgingItem[i].sItem.sItemID.ToInt(), sAgingItemBackUp.AgingItem[i].sItem.iChk1, sAgingItemBackUp.AgingItem[i].sItem.iChk2);
	}

	memset(&sAgingItem, 0, sizeof(sAGINGITEM));
	memset(&sAgingItemBackUp, 0, sizeof(sAGINGITEM));
	cAging.OpenFlag = 0;
	AgingCheckSheltomFlag = 0;
	AgingSheltomCnt2 = 0;
	MixItemNoCopyFlag = 0;
	MixCancelButtonDelayFlag = 0;
	memset(&sAging_Recv, 0, sizeof(sCRAFTITEM_SERVER));
	memset(&sAging_Send, 0, sizeof(sCRAFTITEM_SERVER));
	cInvenTory.CheckDamage();
	return TRUE;
}

int cCRAFTITEM::sinRecvCraftItemResult(sCRAFTITEM_SERVER *pCraftItem_Server)
{
	CheckMixItemCopyFlag = 0;
	if (!cCraftItem.OpenFlag)
	{
		MixItemNoCopyFlag = 0;
		memset(&sCraftItem, 0, sizeof(sCRAFTITEM));
		memset(&sCraftItemBackUp, 0, sizeof(sCRAFTITEM));
		memset(&sCraftItem_Recv, 0, sizeof(sCRAFTITEM_SERVER));
		memset(&sCraftItem_Send, 0, sizeof(sCRAFTITEM_SERVER));
		MixCancelButtonDelayFlag = 0;
		return FALSE;
	}

	int i, LineCount = 0, Temp;

	if (pCraftItem_Server->Result)
	{
		if (pCraftItem_Server->DocIndex == 2000)
		{
			ItemData TempItem;
			if (LoadItemImage(&pCraftItem_Server->DesCraftItem.sItem, &TempItem))
			{
				if (cInvenTory.CheckRequireItemToSet(&TempItem))
				{
					if (!cInvenTory.AutoSetInvenItem(&TempItem, 1))
					{
						sinThrowItemToFeild(&pCraftItem_Server->DesCraftItem);
						memset(&sCraftItem, 0, sizeof(sCRAFTITEM));
						cCraftItem.OpenFlag = 0;
						return FALSE;
					}
				}

			}
			cMessageBox.ShowMessage(MESSAGE_RECONITEM_OK);
		}
		else
		{
			// ºÏ³ÉÎïÆ·µÄÏÔÊ¾
			ShowItemCraftMessageFlag = 1;

			lstrcpy(szCraftItemBuff, sCraftItem_Info[pCraftItem_Server->DocIndex].Doc);

			Temp = lstrlen(szCraftItemBuff);

			for (i = 0; i < Temp; i++)
			{
				if (szCraftItemBuff[i] == '\r')
					LineCount++;
			}

			CraftItemMessageSize.x = 14;
			CraftItemMessageSize.y = ((LineCount) * 2) + 2;


			sinAgingSuccessFlag2 = 1;

			if (!cInvenTory.AutoSetInvenItem(&pCraftItem_Server->DesCraftItem))
				sinThrowItemToFeild(&pCraftItem_Server->DesCraftItem);

			if (sCraftItemBackUp.CraftItem[0].bValid)
				cInvenTory.DeleteInvenItemToServer(sCraftItemBackUp.CraftItem[0].sItem.sItemID.ToInt(), sCraftItemBackUp.CraftItem[0].sItem.iChk1, sCraftItemBackUp.CraftItem[0].sItem.iChk2);
		}
		cCraftItem.OpenFlag = 0;
		CheckCharForm();
		sinMinusMoney(sCraftItem.CraftItem[0].sItem.iSalePrice, 1);
		ReformCharForm();
		SendSaveMoney();
		SaveGameData();
	}
	else
	{
		if (!cInvenTory.AutoSetInvenItem(&sCraftItem.CraftItem[0]))
			sinThrowItemToFeild(&sCraftItem.CraftItem[0]);

		CheckCharForm();
		sinMinusMoney(sCraftItem.CraftItem[0].sItem.iSalePrice, 1);
		ReformCharForm();
		SendSaveMoney();

		cCraftItem.OpenFlag = 0;
		cMessageBox.ShowMessage(MESSAGE_FAILD_CRAFT_ITEM);
		sinPlaySound(SIN_SOUND_FAILD_MIXITEM);
	}

	for (i = 1; i < 15; i++)
	{
		if (sCraftItemBackUp.CraftItem[i].bValid)
			cInvenTory.DeleteInvenItemToServer(sCraftItemBackUp.CraftItem[i].sItem.sItemID.ToInt(), sCraftItemBackUp.CraftItem[i].sItem.iChk1, sCraftItemBackUp.CraftItem[i].sItem.iChk2);
	}
	memset(&sCraftItem, 0, sizeof(sCRAFTITEM));
	memset(&sCraftItemBackUp, 0, sizeof(sCRAFTITEM));
	memset(&sCraftItem_Recv, 0, sizeof(sCRAFTITEM_SERVER));
	memset(&sCraftItem_Send, 0, sizeof(sCRAFTITEM_SERVER));

	MixItemNoCopyFlag = 0;
	MixCancelButtonDelayFlag = 0;
	return TRUE;
}
int CopyMixItemCheckDelete(ItemData *pItem)
{
	for (int i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (cInvenTory.InvenItem[i].bValid)
		{
			if (CompareItems(&cInvenTory.InvenItem[i].sItem, &pItem->sItem))
				cInvenTory.InvenItem[i].bValid = 0;
		}
		if (cInvenTory.InvenItemTemp[i].bValid)
		{
			if (CompareItems(&cInvenTory.InvenItemTemp[i].sItem, &pItem->sItem))
				cInvenTory.InvenItemTemp[i].bValid = 0;
		}
	}
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
	HelpBoxKindIndex = SIN_POST_BOX;
	cSinHelp.sinShowHelp(SIN_HELP_KIND_POSTBOX, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), PostBoxDocFilePath[0]);
	cInvenTory.OpenFlag = 1;
	cInterFace.CheckAllBox(SIN_INVENTORY);
	return TRUE;
}
int cCRAFTITEM::haCheckReconItem()
{
	int cnt[MAX_SEEL_COUNT] = { 0 };
	int CheckNotReconItem = 0;
	int CheckBlockCount = 0;
	cCraftItem.iReconItemFlag = 0;

	for (int k = 1; k < 14; k++)
	{
		if (sCraftItem.CraftItem[k].bValid)
		{
			if ((sCraftItem.CraftItem[k].sBaseItemID.ToInt() & sinITEM_MASK2) == sinSE1)
				CheckBlockCount++;
			else
				CheckNotReconItem++;
		}
		else
			memset(&sCraftItem.CraftItem[k], 0, sizeof(ItemData));
	}

	for (int i = 1; i < 14; i++)
	{
		if ((sCraftItem.CraftItem[i].sBaseItemID.ToInt() & sinITEM_MASK2) == sinSE1 && sCraftItem.CraftItem[i].bValid)
		{
			for (int k = 0; k < MAX_SEEL_COUNT; k++)
			{
				if (sCraftItem.CraftItem[i].sBaseItemID.ToInt() == sReconItem[k].dwCODE)
				{
					cnt[k]++;
					if (sReconItem[k].iCount == cnt[k] && CheckNotReconItem < 1 && CheckBlockCount == cnt[k])
					{
						cCraftItem.iReconItemFlag = 1;
						return TRUE;
					}
				}
			}
		}
	}
	return FALSE;
}

int cCRAFTITEM::haCraftSortItem(sCRAFTITEM *pCraftItem)
{
	int i;
	for (i = 1; i < 13; i++)
	{
		if (!pCraftItem->CraftItem[i].bValid)
		{
			pCraftItem->CraftItem[i] = pCraftItem->CraftItem[i + 1];
			pCraftItem->CraftItem[i + 1].bValid = 0;
		}
	}
	return TRUE;
}

int cCRAFTITEM::GetCraftCheckEmptyArea()
{
	int cntx, cnty;
	int cx, cy;

	RECT	rect;
	int		flag;
	int StartX = 23;
	int StartY = 436;

	cx = (22 * INVENTORY_BOX_ROW) - 22;
	cy = (22 * INVENTORY_BOX_COL) - 22;

	int count = 0;
	for (cntx = StartX; cntx <= StartX + cx; cntx += 22)
	{
		for (cnty = StartY; cnty <= StartY + cy; cnty += 22)
		{
			flag = 0;
			for (int i = 0; i < INVENTORY_MAXITEM; i++)
			{
				if (cInvenTory.InvenItem[i].bValid)
				{
					rect.left	= cInvenTory.InvenItem[i].iPlaceX;
					rect.right	= cInvenTory.InvenItem[i].iPlaceX + cInvenTory.InvenItem[i].iWidth;
					rect.top	= cInvenTory.InvenItem[i].iPlaceY;
					rect.bottom = cInvenTory.InvenItem[i].iPlaceY + cInvenTory.InvenItem[i].iHeight;

					if (cntx > rect.left - 22 && cntx< rect.right && cnty > rect.top - 22 && cnty < rect.bottom)
						flag++;
				}
			}
			if (flag == 0)
				count++;
		}
	}
	if (count)
		return count;
	else
		return 0;
}

int cMIXTURERESET::SetMixtureItemResetAreaCheck(ItemData *pItem)
{
	TradeColorIndex = 0;
	TradeCrashItemIndex[0] = 0;
	cTrade.InitTradeColorRect();

	if (pItem->sBaseItemID.ToInt() == (sinBI1 | sin89) ||
		pItem->sBaseItemID.ToInt() == (sinBI2 | sin48) ||
		pItem->sBaseItemID.ToInt() == (sinBI2 | sin49))
	{
		TradeStartX = AgingLevelSheltomXY[0][0].x + 23;
		TradeStartY = AgingLevelSheltomXY[0][0].y + 31;
		TradeEndX = TradeStartX + 22;
		TradeEndY = TradeStartY + 22;

		int i, j;
		for (i = pItem->iPlaceX + 11; i < pItem->iPlaceX + pItem->iWidth; i += 22)
		{
			for (j = pItem->iPlaceY + 11; j < pItem->iPlaceY + pItem->iHeight; j += 22)
			{
				if (TradeStartX <= i && TradeEndX > i && TradeStartY <= j && TradeEndY > j)
				{
					TradeColorRect.left		= TradeStartX + (((i - TradeStartX) / 22) * 22);
					TradeColorRect.top		= TradeStartY + (((j - TradeStartY) / 22) * 22);
					TradeColorRect.right	= pItem->iWidth;
					TradeColorRect.bottom	= pItem->iHeight;

					if (TradeEndX < (TradeColorRect.left + TradeColorRect.right) - 11 || TradeEndY < (TradeColorRect.top + TradeColorRect.bottom) - 11)
					{
						cTrade.InitTradeColorRect();
						return FALSE;
					}

					pItem->iPlaceX = TradeColorRect.left;
					pItem->iPlaceY = TradeColorRect.top;
					pItem->iItemSlot = 0;

					TradeColorIndex = SET_ITEM_CHECK_COLOR;

					if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 6))
					{
						TradeColorIndex = NOT_SETTING_COLOR;
						return FALSE;
					}

					return TRUE;
				}
			}
		}
	}
	else
	{
		if (pItem->sItem.eCraftType == ITEMCRAFTTYPE_Mixing || (pItem->sItem.eCraftType == ITEMCRAFTTYPE_Aging && pItem->sItem.sMatureBar.sMax == 0))
		{
			TradeColorIndex = 0;
			TradeCrashItemIndex[0] = 0;
			cTrade.InitTradeColorRect();

			TradeStartX = 58;
			TradeStartY = 193 + sinInterHeight2;
			TradeEndX = TradeStartX + (3 * 22);
			TradeEndY = TradeStartY + (4 * 22);

			if (TradeStartX <= pCursorPos.x && TradeEndX > pCursorPos.x && TradeStartY <= pCursorPos.y && TradeEndY > pCursorPos.y)
			{
				TradeColorRect.left = TradeStartX;
				TradeColorRect.top = TradeStartY;
				TradeColorRect.right = TradeEndX - TradeStartX;
				TradeColorRect.bottom = TradeEndY - TradeStartY;

				pItem->iPlaceX = TradeStartX + ((TradeEndX - TradeStartX) - pItem->iWidth) / 2;
				pItem->iPlaceY = TradeStartY + ((TradeEndY - TradeStartY) - pItem->iHeight) / 2;
				pItem->iItemSlot = 0;
				TradeColorIndex = SET_ITEM_CHECK_COLOR;

				if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 6))
				{
					TradeColorIndex = NOT_SETTING_COLOR;
					return FALSE;
				}
				return TRUE;
			}
		}
		else
		{
			TradeStartX = 58;
			TradeStartY = 193 + sinInterHeight2;
			TradeEndX = TradeStartX + (3 * 22);
			TradeEndY = TradeStartY + (4 * 22);
			if (TradeStartX <= pCursorPos.x && TradeEndX > pCursorPos.x && TradeStartY <= pCursorPos.y && TradeEndY > pCursorPos.y)
			{
				TradeColorRect.left = TradeStartX;
				TradeColorRect.top = TradeStartY;
				TradeColorRect.right = TradeEndX - TradeStartX;
				TradeColorRect.bottom = TradeEndY - TradeStartY;

				pItem->iPlaceX = TradeStartX + ((TradeEndX - TradeStartX) - pItem->iWidth) / 2;
				pItem->iPlaceY = TradeStartY + ((TradeEndY - TradeStartY) - pItem->iHeight) / 2;
				pItem->iItemSlot = 0;
				TradeColorIndex = SET_ITEM_CHECK_COLOR;

				if (pItem->sItem.eCraftType != ITEMCRAFTTYPE_Mixing && pItem->sItem.eCraftType != ITEMCRAFTTYPE_Aging)
				{
					TradeColorIndex = NOT_SETTING_COLOR;
					return FALSE;
				}
			}
		}
	}

	return TRUE;
}
int cMIXTURERESET::SetMixtureItemReset(ItemData *pItem)
{
	if (pItem->sItem.sItemID.ToInt() == (sinBI1 | sin89) ||
		pItem->sItem.sItemID.ToInt() == (sinBI2 | sin48) ||
		pItem->sItem.sItemID.ToInt() == (sinBI2 | sin49))
	{
		if (sMixtureResetItem.MixtureResetItem[0].bValid && sMixtureResetItem.MixtureResetItem[1].bValid == NULL)
		{
			pItem->iPlaceX = AgingLevelSheltomXY[0][0].x + 23;
			pItem->iPlaceY = AgingLevelSheltomXY[0][0].y + 31;
			return TRUE;
		}
	}
	else
	{
		if (pItem->sItem.eCraftType == ITEMCRAFTTYPE_Mixing ||
			(pItem->sItem.eCraftType == ITEMCRAFTTYPE_Aging && pItem->sItem.sMatureBar.sMax == 0))
		{
			if (sMixtureResetItem.MixtureResetItem[0].bValid == NULL)
			{
				int Startx = 58;
				int Starty = 193 + sinInterHeight2;
				int Endx = Startx + 3 * 22;
				int Endy = Starty + 4 * 22;
				pItem->iPlaceX = Startx + ((Endx - Startx) - pItem->iWidth) / 2;
				pItem->iPlaceY = Starty + ((Endy - Starty) - pItem->iHeight) / 2;
				return TRUE;
			}
		}
	}
	return FALSE;
}
int cMIXTURERESET::CheckMixtureResetItemForm()
{
	int TempCheckDataSum = 0;

	for (int i = 0; i < 2; i++)
	{
		if (sMixtureResetItem.MixtureResetItem[i].bValid)
		{
			TempCheckDataSum += (i + 1) * sMixtureResetItem.MixtureResetItem[i].iPlaceX;
			TempCheckDataSum += (i + 1) * sMixtureResetItem.MixtureResetItem[i].iPlaceY;
			TempCheckDataSum += sMixtureResetItem.MixtureResetItem[i].sItem.iChk2;
			TempCheckDataSum += sMixtureResetItem.MixtureResetItem[i].sItem.iChk1;
		}
	}
	return TRUE;
}
int cMIXTURERESET::ReformMixtureResetItem()
{
	MixtureResetItemCheckSum = 0;

	for (int i = 0; i < 2; i++)
	{
		if (sMixtureResetItem.MixtureResetItem[i].bValid)
		{
			MixtureResetItemCheckSum += (i + 1) * sMixtureResetItem.MixtureResetItem[i].iPlaceX;
			MixtureResetItemCheckSum += (i + 1) * sMixtureResetItem.MixtureResetItem[i].iPlaceY;
			MixtureResetItemCheckSum += sMixtureResetItem.MixtureResetItem[i].sItem.iChk2;
			MixtureResetItemCheckSum += sMixtureResetItem.MixtureResetItem[i].sItem.iChk1;
		}
	}

	return TRUE;
}
int cMIXTURERESET::PickUpMixtureResetItem(int x, int y, int PickUpFlag, int Kind)
{
	int i = 0;
	SelectTradeItemIndex = 0;

	if (Kind == 0)
	{
		for (i = 0; i < 2; i++)
		{
			if (sMixtureResetItem.MixtureResetItem[i].bValid)
			{
				if (sMixtureResetItem.MixtureResetItem[i].iPlaceX < x  &&
					sMixtureResetItem.MixtureResetItem[i].iPlaceX + sMixtureResetItem.MixtureResetItem[i].iWidth > x  &&
					sMixtureResetItem.MixtureResetItem[i].iPlaceY < y  &&
					sMixtureResetItem.MixtureResetItem[i].iPlaceY + sMixtureResetItem.MixtureResetItem[i].iHeight > y)
				{
					switch (PickUpFlag)
					{
					case 1:
						if (i == 1)
							MixtureResetCheckFlag = 0;

						if (sMixtureResetItem.MixtureResetItem[1].bValid && i == 0)
						{
							cMessageBox.ShowMessage(MESSAGE_NOT_MIXTURE_RESET_ITEM);
							return FALSE;
						}

						CheckMixtureResetItemForm();
						memcpy(&MouseItem, &sMixtureResetItem.MixtureResetItem[i], sizeof(ItemData));
						sMixtureResetItem.MixtureResetItem[i].bValid = 0;
						memset(&sMixtureResetItem.MixtureResetItem[i], 0, sizeof(ItemData));

						sinPlaySound(sMixtureResetItem.MixtureResetItem[i].iInvItemSound);
						TradeColorIndex = 0;
						ReformMixtureResetItem();
						return TRUE;
						break;
					case 2:
						if (i == 1)
							MixtureResetCheckFlag = 0;

						if (sMixtureResetItem.MixtureResetItem[1].bValid && i == 0)
						{
							cMessageBox.ShowMessage(MESSAGE_NOT_MIXTURE_RESET_ITEM);
							return FALSE;
						}
						CheckMixtureResetItemForm();
						if (cCraftItem.CraftCheckEmptyArea(&sMixtureResetItem.MixtureResetItem[i]))
						{
							if (!cInvenTory.AutoSetInvenItem(&sMixtureResetItem.MixtureResetItem[i]))
							{
								sinThrowItemToFeild(&sMixtureResetItem.MixtureResetItem[i]);
								sMixtureResetItem.MixtureResetItem[i].bValid = 0;
							}
						}
						ReformMixtureResetItem();
						return TRUE;
						break;
					default:
						SelectTradeItemIndex = i + 1;
						TradeColorIndex = SELECT_ITEM_COLOR;
						sinShowItemInfoFlag = 1;
						cItem.ShowItemInfo(&sMixtureResetItem.MixtureResetItem[i], 2);
						break;
					}
				}
			}
		}
	}

	return FALSE;
}
int cMIXTURERESET::LastSetMixtureResetItem(ItemData *pItem, int kind)
{
	if (kind == 1)
	{
		if (sMixtureResetItem.MixtureResetItem[0].bValid && !sMixtureResetItem.MixtureResetItem[1].bValid)
		{
			memcpy(&sMixtureResetItem.MixtureResetItem[1], pItem, sizeof(ItemData));
			sMixtureResetItem.MixtureResetItem[1].iPlaceX = pItem->iPlaceX;
			sMixtureResetItem.MixtureResetItem[1].iPlaceY = pItem->iPlaceY;
			pItem->bValid = 0;
			sinPlaySound(sMixtureResetItem.MixtureResetItem[1].iInvItemSound);
			return TRUE;
		}
	}
	else if (kind == 2)
	{
		if (!sMixtureResetItem.MixtureResetItem[0].bValid)
		{
			memcpy(&sMixtureResetItem.MixtureResetItem[0], pItem, sizeof(ItemData));
			sMixtureResetItem.MixtureResetItem[0].iPlaceX = pItem->iPlaceX;
			sMixtureResetItem.MixtureResetItem[0].iPlaceY = pItem->iPlaceY;
			pItem->bValid = 0;
			sinPlaySound(sMixtureResetItem.MixtureResetItem[0].iInvItemSound);
			return TRUE;
		}
	}

	return TRUE;
}
int cMIXTURERESET::CancelMixtureItemReset(int Flag)
{
	if (MixItemNoCopyFlag)
		return FALSE;

	for (int i = 0; i < 2; i++)
	{
		if (sMixtureResetItem.MixtureResetItem[i].bValid)
		{
			if (!cInvenTory.AutoSetInvenItem(&sMixtureResetItem.MixtureResetItem[i]))
				sinThrowItemToFeild(&sMixtureResetItem.MixtureResetItem[i]);

			sMixtureResetItem.MixtureResetItem[i].bValid = 0;
		}
	}

	MixtureResetCheckFlag = 0;

	if (!Flag)
		cMixtureReset.OpenFlag = 0;

	ResetInvenItemCode();

	return TRUE;
}
int cMIXTURERESET::sinSendMixtureItemReset()
{
	if (MixItemNoCopyFlag)
		return FALSE;

	memcpy(&sMixtureResetItemBackUp, &sMixtureResetItem, sizeof(sMIXTURE_RESET_ITEM));
	MixItemNoCopyFlag = 1;
	memset(&sMixtureReset_Send, 0, sizeof(sMIXTURE_RESET_ITEM_SERVER));

	if (sMixtureResetItem.MixtureResetItem[0].bValid)
		sMixtureReset_Send.DesMixtureResetItem = sMixtureResetItem.MixtureResetItem[0];

	if (sMixtureResetItem.MixtureResetItem[1].bValid)
	{
		sMixtureReset_Send.dwMixtureResetStoneItemCode = sMixtureResetItem.MixtureResetItem[1].sBaseItemID.ToInt();
		sMixtureReset_Send.dwMixtureResetStoneCheckSum = sMixtureResetItem.MixtureResetItem[1].sItem.iChk2;
		sMixtureReset_Send.dwMixtureResetStoneHead = sMixtureResetItem.MixtureResetItem[1].sItem.iChk1;
	}

	CraftItemSendServerIndex++;
	sMixtureReset_Send.Index = CraftItemSendServerIndex;

	SendMixtureResetItemToServer(&sMixtureReset_Send);

	return TRUE;
}
int cMIXTURERESET::sinRecvMixtureItemResetResult(sMIXTURE_RESET_ITEM_SERVER *pMixtureResetItem_Server)
{
	CheckMixItemCopyFlag = 0;

	if (!cMixtureReset.OpenFlag)
	{
		MixItemNoCopyFlag = 0;
		memset(&sMixtureResetItem, 0, sizeof(sMIXTURE_RESET_ITEM));
		memset(&sMixtureResetItemBackUp, 0, sizeof(sMIXTURE_RESET_ITEM));
		memset(&sMixtureReset_Recv, 0, sizeof(sMIXTURE_RESET_ITEM_SERVER));
		memset(&sMixtureReset_Send, 0, sizeof(sMIXTURE_RESET_ITEM_SERVER));
		MixCancelButtonDelayFlag = 0;

		return FALSE;
	}

	int i, LineCount = 0, Temp;

	if (pMixtureResetItem_Server->Result)
	{
		ItemData TempItem;
		if (LoadItemImage(&pMixtureResetItem_Server->DesMixtureResetItem.sItem, &TempItem))
		{
			lstrcpy(szCraftItemBuff, pMixtureResetItem_Server->DesMixtureResetItem.sItem.szItemName);
			lstrcat(szCraftItemBuff, "\r");

			Temp = lstrlen(szCraftItemBuff);
			for (i = 0; i < Temp; i++)
			{
				if (szCraftItemBuff[i] == '\r')
					LineCount++;
			}

			CraftItemMessageSize.x = 14;
			CraftItemMessageSize.y = ((LineCount) * 2) + 2;

			if (cInvenTory.CheckRequireItemToSet(&TempItem))
			{
				if (!cInvenTory.AutoSetInvenItem(&TempItem, 1))
					sinThrowItemToFeild(&pMixtureResetItem_Server->DesMixtureResetItem);
			}
		}

		cMessageBox.ShowMessage(MESSAGE_OK_MIXTURE_RESET_ITEM);

		CheckCharForm();
		ReformCharForm();
		SendSaveMoney();
		SaveGameData();
		cMixtureReset.OpenFlag = 0;
	}
	else
	{
		CheckCharForm();
		ReformCharForm();
		SendSaveMoney();
		cMixtureReset.OpenFlag = 0;
		cMessageBox.ShowMessage(MESSAGE_FAIL_MIXTURE_RESET_ITEM);
	}

	for (i = 0; i < 2; i++)
	{
		if (sMixtureResetItemBackUp.MixtureResetItem[i].bValid)
			cInvenTory.DeleteInvenItemToServer(sMixtureResetItemBackUp.MixtureResetItem[i].sItem.sItemID.ToInt(), sMixtureResetItemBackUp.MixtureResetItem[i].sItem.iChk1, sMixtureResetItemBackUp.MixtureResetItem[i].sItem.iChk2);
	}

	memset(&sMixtureResetItem, 0, sizeof(sMIXTURE_RESET_ITEM));
	memset(&sMixtureResetItemBackUp, 0, sizeof(sMIXTURE_RESET_ITEM));
	memset(&sMixtureReset_Recv, 0, sizeof(sMIXTURE_RESET_ITEM_SERVER));
	memset(&sMixtureReset_Send, 0, sizeof(sMIXTURE_RESET_ITEM_SERVER));

	MixItemNoCopyFlag = 0;
	MixCancelButtonDelayFlag = 0;

	return TRUE;
}
int CSmeltingItem::CancelSmeltingItem()
{
	for (int i = 0; i < 5; i++)
	{
		if (S_smeltingItem.SmeltingItem[i].bValid)
		{
			if (!cInvenTory.AutoSetInvenItem(&S_smeltingItem.SmeltingItem[i]))
			{
				sinThrowItemToFeild(&S_smeltingItem.SmeltingItem[i]);
				S_smeltingItem.SmeltingItem[i].bValid = 0;
			}
		}
	}

	SmeltingItem.OpenFlag = 0;
	m_SmeltingPrice = 0;
	ForceItemPrice2 = 0;
	memset(&S_smeltingItem, 0, sizeof(SSmeltingItem));
	ResetInvenItemCode();

	memset(&sSmeltingItem_Recv, 0, sizeof(sSMELTINGITEM_SERVER));
	memset(&sSmeltingItem_Send, 0, sizeof(sSMELTINGITEM_SERVER));

	return TRUE;
}

// pluto Á¦·Ã
int CSmeltingItem::SetSmeltingItemAreaCheck(ItemData *pItem, int Kind)
{
	int SmeltingPriceIndexOre = 25000;

	int SmeltingPriceIndexCrystal = 50000;

	DWORD SmeltingCode[] = { sin01, sin02, sin03, sin04, sin05, sin06, sin07, sin08, sin09, sin10, sin11, sin12, sin13, sin14 };

	int i, j;
	TradeColorIndex = 0;
	TradeCrashItemIndex[0] = 0;
	cTrade.InitTradeColorRect(); //ÃÊ±âÈ­

	if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinOS1)
	{
		int SmeltingSheltomIndex = 0;
		SmeltingSheltomIndex = GetSheltomIndex(S_smeltingItem.SmeltingItem[0].sBaseItemID.ToInt());
		int Smelting_SheltomIndex = 0;
		DWORD SheltomAray[MAX_SHELTOM] = { sin01, sin02, sin03, sin04, sin05, sin06, sin07, sin08, sin09, sin10, sin11, sin12, sin13 };

		for (int q = 0; q < MAX_SHELTOM; q++)
		{
			if (SheltomAray[q] == (pItem->sItem.sItemID.ToItemIndex()))
			{
				Smelting_SheltomIndex = q + 1;
				break;
			}
		}
		//for(int p = 0 ; p < 4 ; p++)			// ½©ÅÒ °¹¼ö ´Ã¾î ³ª¸é ¾²ÀÚ
		{
			//for(int m=0; m < 3 ; m++)
			{
				if (SmeltingSheltomIndex == Smelting_SheltomIndex)
				{
					TradeStartX = AgingLevelSheltomXY[0][0].x + 22;			// ÁÂÇ¥´Â °°¾Æ¼­ °Á ›§À½
					TradeStartY = AgingLevelSheltomXY[0][0].y + 30;
					TradeEndX = TradeStartX + 22;
					TradeEndY = TradeStartY + 22;
					for (i = pItem->iPlaceX + 11; i < pItem->iPlaceX + pItem->iWidth; i += 22)
					{
						for (j = pItem->iPlaceY + 11; j < pItem->iPlaceY + pItem->iHeight; j += 22)
						{
							if (TradeStartX <= i && TradeEndX > i && TradeStartY <= j && TradeEndY > j)
							{ //ÀÎº¥Åä¸® ¹Ú½º¿¡ µé¾î°¬´ÂÁö¸¦ Ã¼Å© 
								TradeColorRect.left = TradeStartX + (((i - TradeStartX) / 22) * 22);
								TradeColorRect.top = TradeStartY + (((j - TradeStartY) / 22) * 22);
								TradeColorRect.right = pItem->iWidth;
								TradeColorRect.bottom = pItem->iHeight;
								if (TradeEndX < (TradeColorRect.left + TradeColorRect.right) - 11 || TradeEndY < (TradeColorRect.top + TradeColorRect.bottom) - 11)
								{
									cTrade.InitTradeColorRect(); //ÄÃ·¯ ¹Ú½º RECT ÃÊ±âÈ­ (ÄÃ·¯ ¹Ú½º RECTÁß ÇÏ³ª¶óµÎ 0 ÀÌ¸é ¼ÂÆÃÇÒ¼ö ¾ø´Ù 
									return FALSE;
								}

								pItem->iPlaceX = TradeColorRect.left;
								pItem->iPlaceY = TradeColorRect.top;
								pItem->iItemSlot = 0; //¹è¿­ÀÇ ÀÎµ¦½º¸¦ ÀúÀåÇÑ´Ù

								TradeColorIndex = SET_ITEM_CHECK_COLOR; //¼ÂÆÃÇÒ¿µ¿ª
								if (!S_smeltingItem.SmeltingItem[0].bValid)
								{
									TradeColorIndex = NOT_SETTING_COLOR;
									return FALSE;
								}

								if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 4))
								{  //°ãÄ¡´Â ¾ÆÀÌÅÛÀÌ ÀÖ³ª Ã¼Å© 
									TradeColorIndex = NOT_SETTING_COLOR;
									return FALSE;

								}
								return TRUE;
							}
						}
					}
				}
			}
		}
	}
	else if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinPR1 || (pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinPR2)
	{
		//char *p = pItem->LastCategory;
		//if( strcmp( p, "SE101") )
		//{
		//	return false;
		//}
		TradeColorIndex = 0; //ÃÊ±âÈ­   (Æ®·¹ÀÌµå Ã¢°ú Ã¢°í°¡ °°ÀÌ ¾´´Ù)
		TradeCrashItemIndex[0] = 0; //Ãæµ¹µÈ ¾ÆÀÌÅÛ Index ÃÊ±âÈ­ 
		cTrade.InitTradeColorRect(); //ÃÊ±âÈ­

		//TradeStartX = 58;
		//TradeStartY = 193+sinInterHeight2;
		//TradeEndX = TradeStartX+(3*22);
		//TradeEndY = TradeStartY+(3*22);

		TradeStartX = 69;
		TradeStartY = 212 + sinInterHeight2;
		TradeEndX = TradeStartX + (2 * 18);
		TradeEndY = TradeStartY + (2 * 18);
		for (i = pItem->iPlaceX + 11; i < pItem->iPlaceX + pItem->iWidth; i += 22)
		{
			for (j = pItem->iPlaceY + 11; j < pItem->iPlaceY + pItem->iHeight; j += 22)
			{
				if (TradeStartX <= pCursorPos.x && TradeEndX > pCursorPos.x && TradeStartY <= pCursorPos.y && TradeEndY > pCursorPos.y)
				{ //ÀÎº¥Åä¸® ¹Ú½º¿¡ µé¾î°¬´ÂÁö¸¦ Ã¼Å© // ÇÏ´ÂÁß
					if (!(80 <= pCursorPos.x && 101 >= pCursorPos.x && 143 <= pCursorPos.y && 164 >= pCursorPos.y))
					{
						TradeColorRect.left = TradeStartX + (((i - TradeStartX) / 22) * 22);
						TradeColorRect.top = TradeStartY + (((j - TradeStartY) / 22) * 22);
						TradeColorRect.right = pItem->iWidth;
						TradeColorRect.bottom = pItem->iHeight;
						if (TradeEndX < (TradeColorRect.left + TradeColorRect.right) - 11 ||
							TradeEndY < (TradeColorRect.top + TradeColorRect.bottom) - 11)
						{
							cTrade.InitTradeColorRect(); //ÄÃ·¯ ¹Ú½º RECT ÃÊ±âÈ­ (ÄÃ·¯ ¹Ú½º RECTÁß ÇÏ³ª¶óµÎ 0 ÀÌ¸é ¼ÂÆÃÇÒ¼ö ¾ø´Ù 
							return FALSE;
						}

						pItem->iPlaceX = TradeColorRect.left;
						pItem->iPlaceY = TradeColorRect.top;
						pItem->iItemSlot = 0; //¹è¿­ÀÇ ÀÎµ¦½º¸¦ ÀúÀåÇÑ´Ù 
						TradeColorIndex = SET_ITEM_CHECK_COLOR; //¼ÂÆÃÇÒ¿µ¿ª

						if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 4))
						{  //°ãÄ¡´Â ¾ÆÀÌÅÛÀÌ ÀÖ³ª Ã¼Å© 
							TradeColorIndex = NOT_SETTING_COLOR;
							return FALSE;
						}

						// Á¦·Ã ÇÒ¼ö ÀÖ´Â µ·ÀÌ ÀÖ³ª °Ë»ç
						for (int i = 0; i < 7; i++)
						{
							// ±¤¼®
							if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinPR1)
							{
								if ((pItem->sItem.sItemID.ToItemIndex()) == SmeltingCode[i])
								{
									if (sinChar->iGold < SmeltingPriceIndexOre)
									{
										TradeColorIndex = NOT_ENOUGH_MONEY;
										return FALSE;
									}
								}
							}
						}

						for (int i = 0; i < 14; i++) // Àåº° - Á¦·Ã // Àåº° - ´ëÀåÀåÀÌÀÇ È¥
						{
							// ¼öÁ¤
							if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinPR2)
							{
								if ((pItem->sItem.sItemID.ToItemIndex()) == SmeltingCode[i])
								{
									if (sinChar->iGold < SmeltingPriceIndexCrystal)
									{
										TradeColorIndex = NOT_ENOUGH_MONEY;
										return FALSE;
									}
								}
							}
						}

						////º¹»çµÇ ¾ÆÀÌÅÛÀº ¹Í½ºÃÄ¿Í ¿¡ÀÌÂ¡À» ÇÒ¼ö¾ø´Ù MakeItemÀº ¹Í½ºÇÒ¼ö¾ø´Ù 
						if (pItem->sItem.SpecialItemFlag[0] == CHECK_COPY_ITEM ||
							pItem->sItem.eCraftType == ITEMCRAFTTYPE_Quest ||
							(pItem->sItem.sItemID.ToItemType()) == sinMA1 ||
							(pItem->sItem.sItemID.ToItemType()) == sinMA2 ||
							(pItem->sItem.sItemID.ToItemType()) == sinQW1 ||
							(pItem->sItem.sItemID.ToItemType()) == sinPZ1 || //ÆÛÁñµµ ¿Ã¸±¼ö¾öµû 
							(pItem->sItem.sItemID.ToItemType()) == sinPZ2 ||
							(pItem->sItem.sItemID.ToItemType()) == sinFO1 || //Æ÷½ºµµ¾ÈµÈ´Ù
							pItem->sItem.sItemID.ToInt() == (sinGF1 | sin01) ||
							pItem->sItem.sItemID.ToInt() == (sinGF1 | sin02) ||
							pItem->sItem.sItemID.ToInt() == (sinGF1 | sin03) ||
							pItem->sItem.sItemID.ToInt() == (sinGF1 | sin04) ||
							pItem->sItem.sItemID.ToInt() == (sinGF1 | sin05) ||
							pItem->sItem.sItemID.ToInt() == (sinGF1 | sin06) ||
							pItem->sItem.sItemID.ToInt() == (sinGF1 | sin07) ||	// Àåº° - Á¶»ç¿øÀ» Ã£¾Æ¶ó
							pItem->sItem.sItemID.ToInt() == (sinGF1 | sin08))
						{

							TradeColorIndex = NOT_SETTING_COLOR;
							return FALSE;
						}
						return TRUE;
					}

				}
			}
		}
	}
	return TRUE;
}

// pluto Á¦·Ã
int CSmeltingItem::LastSetSmeltingItem(ItemData *pItem, int Kind)
{
	if (Kind == 0)
	{
		CheckSmeltingItemForm();
		if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinOS1)
		{ //½©ÅÒÀÏ °æ¿ì
			//for(int j=12 ; j < 24 ; j++)
			//{
			//	if(!S_smeltingItem.SmeltingItem[j].Flag)
			//	{
			//		memcpy(&S_smeltingItem.SmeltingItem[j],pItem,sizeof(ItemData));
			//		S_smeltingItem.SmeltingItem[j].x = pItem->SetX;
			//		S_smeltingItem.SmeltingItem[j].y = pItem->SetY;
			//		pItem->Flag = 0; //ÃÊ±âÈ­ 
			//		sinPlaySound(S_smeltingItem.SmeltingItem[j].SoundIndex);
			//		ReFormSmeltingItem();
			//		return TRUE;
			//	}
			//}
			if (!S_smeltingItem.SmeltingItem[4].bValid)	// pluto ½©ÅÒ ÇÑ°³¸¸ ³õ´Â´Ù 
			{
				memcpy(&S_smeltingItem.SmeltingItem[4], pItem, sizeof(ItemData));
				S_smeltingItem.SmeltingItem[4].iPlaceX = pItem->iPlaceX;
				S_smeltingItem.SmeltingItem[4].iPlaceY = pItem->iPlaceY;
				pItem->bValid = 0; //ÃÊ±âÈ­ 
				sinPlaySound(S_smeltingItem.SmeltingItem[4].iInvItemSound);
				ReFormSmeltingItem();
				return TRUE;
			}

		}
		else
		{
			int k = 3; // Àåº° - Á¦·Ã ½Ã½ºÅÛ ¼öÁ¤
			//if( (pItem->CODE & sinITEM_MASK2) == sinPR1 )
			//{
			//	k = 5;		// ±¤¼®
			//}
			//else if( (pItem->CODE & sinITEM_MASK2) == sinPR2 )
			//{
			//	k = 3;		// ¼öÁ¤
			//}

			for (int i = 0; i < k; i++)
			{
				if (!S_smeltingItem.SmeltingItem[i].bValid)		// ±¤¼®, ¼öÁ¤
				{
					memcpy(&S_smeltingItem.SmeltingItem[i], pItem, sizeof(ItemData));
					S_smeltingItem.SmeltingItem[i].iPlaceX = pItem->iPlaceX;
					S_smeltingItem.SmeltingItem[i].iPlaceY = pItem->iPlaceY;
					pItem->bValid = 0; //ÃÊ±âÈ­ 
					sinPlaySound(sCraftItem.CraftItem[i].iInvItemSound);
					ReFormSmeltingItem();
					CheckSmeltingPrice();
					return TRUE;
				}
			}
		}
	}
	return TRUE;
}

// pluto Á¦·Ã
int CSmeltingItem::CheckSmeltingItemForm()
{ //Ã¼Å©  
	int TempCheckDataSum = 0;



	for (int i = 0; i < 5; i++)
	{
		if (S_smeltingItem.SmeltingItem[i].bValid)
		{
			TempCheckDataSum += (i + 1)*S_smeltingItem.SmeltingItem[i].iPlaceX;
			TempCheckDataSum += (i + 1)*S_smeltingItem.SmeltingItem[i].iPlaceY;
			TempCheckDataSum += S_smeltingItem.SmeltingItem[i].sItem.iChk2;
			TempCheckDataSum += S_smeltingItem.SmeltingItem[i].sItem.iChk1;
		}
	}
	return TRUE;
}

// pluto Á¦·Ã
int CSmeltingItem::ReFormSmeltingItem()
{ //ÀÎÁõ 

	SmeltingItemCheckSum = 0;
	for (int i = 0; i < 5; i++)
	{
		if (S_smeltingItem.SmeltingItem[i].bValid)
		{
			SmeltingItemCheckSum += (i + 1)*S_smeltingItem.SmeltingItem[i].iPlaceX;
			SmeltingItemCheckSum += (i + 1)*S_smeltingItem.SmeltingItem[i].iPlaceY;
			SmeltingItemCheckSum += S_smeltingItem.SmeltingItem[i].sItem.iChk2;
			SmeltingItemCheckSum += S_smeltingItem.SmeltingItem[i].sItem.iChk1;
		}
	}

	return TRUE;
}

// pluto Á¦·Ã ¾ÆÀÌÅÛ Áý±â
int CSmeltingItem::PickUpSmeltingItem(int x, int y, int PickUpFlag, int Kind)
{
	int i = 0;
	SelectTradeItemIndex = 0;    //ÁýÀ» ¾ÆÀÌÅÛ 
	if (Kind == 0)
	{
		for (i = 0; i < 5; i++)
		{
			if (S_smeltingItem.SmeltingItem[i].bValid)
			{
				if (S_smeltingItem.SmeltingItem[i].iPlaceX < x  &&
					S_smeltingItem.SmeltingItem[i].iPlaceX + S_smeltingItem.SmeltingItem[i].iWidth > x  &&
					S_smeltingItem.SmeltingItem[i].iPlaceY < y  &&
					S_smeltingItem.SmeltingItem[i].iPlaceY + S_smeltingItem.SmeltingItem[i].iHeight > y)
				{
					if (PickUpFlag)
					{
						if (i < 4 && S_smeltingItem.SmeltingItem[4].bValid)
						{
							cMessageBox.ShowMessage(MESSAGE_NOT_SMELTING);
							return FALSE;
						}
						CheckSmeltingItemForm();
						memcpy(&MouseItem, &S_smeltingItem.SmeltingItem[i], sizeof(ItemData));
						S_smeltingItem.SmeltingItem[i].bValid = 0;
						memset(&S_smeltingItem.SmeltingItem[i], 0, sizeof(ItemData));  //¼­¹ö ÇØÅ· ¿¡·¯ ¶§¹®¿¡ ÀÓ½Ã ¹æÆíÀÌ´Ù.

						sinPlaySound(S_smeltingItem.SmeltingItem[i].iInvItemSound);
						TradeColorIndex = 0;
						ReFormSmeltingItem();
						return TRUE;
					}
					else
					{
						SelectTradeItemIndex = i + 1;
						TradeColorIndex = SELECT_ITEM_COLOR;
						sinShowItemInfoFlag = 1; //¾ÆÀÌÅÛÀÇ Á¤º¸¸¦ º¸¿©ÁØ´Ù 
						cItem.ShowItemInfo(&S_smeltingItem.SmeltingItem[i], 2);
					}
				}
			}
		}
	}
	return FALSE;
}

// pluto Á¦·Ã
int CSmeltingItem::sinSendSmeltingItem()
{
	if (MixItemNoCopyFlag)
	{
		return FALSE;
	}

	int i = 0;

	//º¹»ç¸¦ Ã¼Å©ÇÏ±âÀ§ÇÑ ¹é¾÷º»À» ¸¸µç´Ù
	memcpy(&sSmeltingItemBackUp, &S_smeltingItem, sizeof(SSmeltingItem));
	MixItemNoCopyFlag = 1; //¾ÆÀÌÅÛÀÌ º¹»çµÇ´Â°É ¹æÁöÇÏ±âÀ§ÇØ ÇÃ·ºÀ»ÁØ´Ù
	memset(&sSmeltingItem_Send.DesSmeltingItem, 0, sizeof(ItemData));

	sSmeltingItem_Send.Money = m_SmeltingPrice;

	for (i = 0; i < 5; i++)
	{
		if (S_smeltingItem.SmeltingItem[i].bValid)
		{
			sSmeltingItem_Send.SmeltingCode[i] = S_smeltingItem.SmeltingItem[i].sBaseItemID.ToInt();
			sSmeltingItem_Send.CheckSum[i] = S_smeltingItem.SmeltingItem[i].sItem.iChk2;
			sSmeltingItem_Send.Head[i] = S_smeltingItem.SmeltingItem[i].sItem.iChk1;
		}
	}

	CheckCraftMoney = sSmeltingItem_Send.Money;

	CraftItemSendServerIndex++; //ÀÎµ¦½º¸¦ º¸³½´Ù 
	sSmeltingItem_Send.Index = CraftItemSendServerIndex;
	//ÀúÀåµÈ ±¸Á¶Ã¼¸¦ ¼­¹ö¿¡ º¸³½´Ù 


	SendSmeltingItemToServer(&sSmeltingItem_Send);

	return TRUE;
}

int CSmeltingItem::sinRecvSmeltingItem(sSMELTINGITEM_SERVER *pSmeltingItem_Server)
{
	memcpy(&sSmeltingItem_Recv, pSmeltingItem_Server, sizeof(sSMELTINGITEM_SERVER));
	return TRUE;
}

int CSmeltingItem::sinRecvSmeltingItemResult(sSMELTINGITEM_SERVER *pSmeltingItem_Server)
{
	CheckMixItemCopyFlag = 0;
	if (!SmeltingItem.OpenFlag)
	{
		MixItemNoCopyFlag = 0;
		memset(&S_smeltingItem, 0, sizeof(SSmeltingItem));
		memset(&sSmeltingItemBackUp, 0, sizeof(SSmeltingItem));
		memset(&sSmeltingItem_Recv, 0, sizeof(sSMELTINGITEM_SERVER));
		memset(&sSmeltingItem_Send, 0, sizeof(sSMELTINGITEM_SERVER));
		MixCancelButtonDelayFlag = 0;
		return FALSE;
	}

	int i, LineCount = 0, Temp;


	if (pSmeltingItem_Server->Result)
	{
		ShowItemSmeltingMessageFlag = 1;

		ItemData TempItem;
		if (LoadItemImage(&pSmeltingItem_Server->DesSmeltingItem.sItem, &TempItem))
		{
			lstrcpy(szCraftItemBuff, pSmeltingItem_Server->DesSmeltingItem.sItem.szItemName);

			lstrcat(szCraftItemBuff, "\r");
			Temp = lstrlen(szCraftItemBuff);
			for (i = 0; i < Temp; i++)
			{
				if (szCraftItemBuff[i] == '\r')
					LineCount++;
			}
			CraftItemMessageSize.x = 14;
			CraftItemMessageSize.y = ((LineCount) * 2) + 2;

			if (cInvenTory.CheckRequireItemToSet(&TempItem))
			{
				if (!cInvenTory.AutoSetInvenItem(&TempItem, 1))
					sinThrowItemToFeild(&pSmeltingItem_Server->DesSmeltingItem);
			}
		}

		CheckCharForm();
		sinMinusMoney(m_SmeltingPrice);
		ReformCharForm();
		SendSaveMoney();
		SaveGameData();
		SmeltingItem.OpenFlag = 0;
	}
	else
	{
		CheckCharForm();
		sinMinusMoney(m_SmeltingPrice);
		ReformCharForm();
		SendSaveMoney();
		SmeltingItem.OpenFlag = 0;
		cMessageBox.ShowMessage(MESSAGE_FAILD_SMELTING_ITEM);
	}
	for (i = 0; i < 5; i++)
	{
		if (sSmeltingItemBackUp.SmeltingItem[i].bValid)
			cInvenTory.DeleteInvenItemToServer(sSmeltingItemBackUp.SmeltingItem[i].sItem.sItemID.ToInt(), sSmeltingItemBackUp.SmeltingItem[i].sItem.iChk1, sSmeltingItemBackUp.SmeltingItem[i].sItem.iChk2);
	}
	memset(&S_smeltingItem, 0, sizeof(SSmeltingItem));
	memset(&sSmeltingItemBackUp, 0, sizeof(SSmeltingItem));
	memset(&sSmeltingItem_Recv, 0, sizeof(sSMELTINGITEM_SERVER));
	memset(&sSmeltingItem_Send, 0, sizeof(sSMELTINGITEM_SERVER));

	MixItemNoCopyFlag = 0;
	MixCancelButtonDelayFlag = 0;
	m_SmeltingPrice = 0;
	ForceItemPrice2 = 0;
	return TRUE;
}

// pluto Á¦·Ã
int CSmeltingItem::SmeltingCheckEmptyArea(ItemData *pItem)
{
	int cntx, cnty;
	int cx, cy;

	RECT	rect;
	int		flag;
	int StartX = 23;  //ÀÎº¥ ¹Ú½ºÀÇ ½ÃÀÛÁ¡ X
	int StartY = 436; // Y

	cx = (22 * INVENTORY_BOX_ROW) - pItem->iWidth; //¾ÆÀÌÅÛÀÌ µé¾î°¥¼öÀÖ´Â °¡Àå ³¡ XÁÂÇ¥ 
	cy = (22 * INVENTORY_BOX_COL) - pItem->iHeight; //¾ÆÀÌÅÛÀÌ µé¾î°¥¼öÀÖ´Â °¡Àå ³¡ YÁÂÇ¥

	//ÄÚµå°¡ °°Áö ¾Ê°Å³ª ¾ÆÀÌÅÛÀÌ ºñ¾îÀÖÁö ¾ÊÀº °÷¿¡ ¼ÂÆÃÇÒ¶§ °Ë»öÇØ¼­ À§Ä¡¸¦ Ã£¾Æ³½´Ù 
	for (cntx = StartX; cntx <= StartX + cx; cntx += 22) 
	{
		for (cnty = StartY; cnty <= StartY + cy; cnty += 22) 
		{
			flag = 0;
			for (int i = 0; i < INVENTORY_MAXITEM; i++) 
			{
				if (cInvenTory.InvenItem[i].bValid)
				{
					rect.left	= cInvenTory.InvenItem[i].iPlaceX;
					rect.right	= cInvenTory.InvenItem[i].iPlaceX + cInvenTory.InvenItem[i].iWidth;
					rect.top	= cInvenTory.InvenItem[i].iPlaceY;
					rect.bottom = cInvenTory.InvenItem[i].iPlaceY + cInvenTory.InvenItem[i].iHeight;

					if (cntx > rect.left - pItem->iWidth &&
						cntx < rect.right &&
						cnty > rect.top - pItem->iHeight &&
						cnty < rect.bottom)
						flag++;
				}
			}
			if (flag == 1) { // Àåº° - Á¦·Ã ½Ã½ºÅÛ ¼öÁ¤
				pItem->iPlaceX = cntx;
				pItem->iPlaceY = cnty;
				pItem->iItemSlot = 0;
				return TRUE;
			}
		}
	}

	return FALSE;
}

int CSmeltingItem::GetSmeltingCheckEmptyArea()
{
	int cntx, cnty;
	int cx, cy;

	RECT	rect;
	int		flag;
	int StartX = 23;  //ÀÎº¥ ¹Ú½ºÀÇ ½ÃÀÛÁ¡ X
	int StartY = 436; // Y

	cx = (22 * INVENTORY_BOX_ROW) - 22; //¾ÆÀÌÅÛÀÌ µé¾î°¥¼öÀÖ´Â °¡Àå ³¡ XÁÂÇ¥ 
	cy = (22 * INVENTORY_BOX_COL) - 22; //¾ÆÀÌÅÛÀÌ µé¾î°¥¼öÀÖ´Â °¡Àå ³¡ YÁÂÇ¥

	int count = 0;
	//ÄÚµå°¡ °°Áö ¾Ê°Å³ª ¾ÆÀÌÅÛÀÌ ºñ¾îÀÖÁö ¾ÊÀº °÷¿¡ ¼ÂÆÃÇÒ¶§ °Ë»öÇØ¼­ À§Ä¡¸¦ Ã£¾Æ³½´Ù 
	for (cntx = StartX; cntx <= StartX + cx; cntx += 22) 
	{
		for (cnty = StartY; cnty <= StartY + cy; cnty += 22) 
		{
			flag = 0;
			for (int i = 0; i < INVENTORY_MAXITEM; i++) 
			{
				if (cInvenTory.InvenItem[i].bValid)
				{
					rect.left	= cInvenTory.InvenItem[i].iPlaceX;
					rect.right	= cInvenTory.InvenItem[i].iPlaceX + cInvenTory.InvenItem[i].iWidth;
					rect.top	= cInvenTory.InvenItem[i].iPlaceY;
					rect.bottom = cInvenTory.InvenItem[i].iPlaceY + cInvenTory.InvenItem[i].iHeight;

					if (cntx > rect.left - 22 && cntx< rect.right &&
						cnty > rect.top - 22 && cnty < rect.bottom)
						flag++;
				}
			}
			if (flag == 1) { // Àåº° - Á¦·Ã ½Ã½ºÅÛ ¼öÁ¤
				count++;
			}
		}
	}
	if (count)
		return count;
	else
		return 0;
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
int CManufacture::CancelManufactureItem()
{
	for (int i = 0; i < 4; i++)
	{
		if (sManufactureItem.ManufactureItem[i].bValid)
		{
			if (!cInvenTory.AutoSetInvenItem(&sManufactureItem.ManufactureItem[i]))
			{
				sinThrowItemToFeild(&sManufactureItem.ManufactureItem[i]);
				sManufactureItem.ManufactureItem[i].bValid = 0;
			}
		}
	}

	ManufactureItem.m_OpenFlag = 0;
	m_ManufacturePrice = 0;
	ForceItemPrice2 = 0;
	memset(&sManufactureItem, 0, sizeof(SManufactureItem));
	ResetInvenItemCode();

	memset(&sManufactureItem_Recv, 0, sizeof(SManufactureItem_Server));
	memset(&sManufactureItem_Send, 0, sizeof(SManufactureItem_Server));

	return TRUE;
}
int CManufacture::SetManufactureItemAreaCheck(ItemData *pItem)
{
	POINT ManufactureRuneXY[3] = { {240, 159},  {215, 190}, {265, 190} };

	int i, j;
	TradeColorIndex = 0;
	TradeCrashItemIndex[0] = 0;
	cTrade.InitTradeColorRect();

	if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinPR3 || (pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinPR4)
	{
		int RuneItemIndex = 0;
		DWORD RuneAray[MAX_RUNE] = { sin01, sin02, sin03, sin04 ,sin05, sin06, sin07, sin08, sin09, sin10, sin11, sin12, sin13, sin14 };
		for (int q = 0; q < MAX_RUNE; q++)
		{
			if (RuneAray[q] == (pItem->sItem.sItemID.ToItemIndex()))
			{
				RuneItemIndex = q + 1;
				break;
			}
		}
		int RecipeIndex = 0;
		RecipeIndex = ManufactureItem.GetRecipeIndex(sManufactureItem.ManufactureItem[0].sBaseItemID.ToInt() & sinITEM_MASK3);

		for (int p = 0; p < 3; p++)
		{
			for (int r = 0; r < MAX_RECIPE_KIND; r++)
			{
				if (sManufacture_Rune[r].RecipeCode == RecipeIndex)
				{
					if (sManufacture_Rune[r].NeedRuneIndex[p] == RuneItemIndex)
					{
						TradeStartX = ManufactureRuneXY[p].x;
						TradeStartY = ManufactureRuneXY[p].y;

						TradeEndX = TradeStartX + 22;
						TradeEndY = TradeStartY + 22;

						for (i = pItem->iPlaceX + 11; i < pItem->iPlaceX + pItem->iWidth; i += 22)
						{
							for (j = pItem->iPlaceY + 11; j < pItem->iPlaceY + pItem->iHeight; j += 22)
							{
								if (TradeStartX <= i && TradeEndX > i && TradeStartY <= j && TradeEndY > j)
								{
									TradeColorRect.left = TradeStartX + (((i - TradeStartX) / 22) * 22);
									TradeColorRect.top = TradeStartY + (((j - TradeStartY) / 22) * 22);
									TradeColorRect.right = pItem->iWidth;
									TradeColorRect.bottom = pItem->iHeight;
									if (TradeEndX < (TradeColorRect.left + TradeColorRect.right) - 11 ||
										TradeEndY < (TradeColorRect.top + TradeColorRect.bottom) - 11)
									{
										cTrade.InitTradeColorRect();
										return FALSE;
									}

									pItem->iPlaceX = TradeColorRect.left;
									pItem->iPlaceY = TradeColorRect.top;
									pItem->iItemSlot = 0;

									TradeColorIndex = SET_ITEM_CHECK_COLOR;

									if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 5))
									{
										TradeColorIndex = NOT_SETTING_COLOR;
										return FALSE;
									}

									return TRUE;
								}
							}
						}
					}
				}
			}
		}
	}
	else if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinWR1 ||
		(pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinDR1)
	{
		TradeColorIndex = 0;
		TradeCrashItemIndex[0] = 0;
		cTrade.InitTradeColorRect();

		TradeStartX = 58;
		TradeStartY = 193 + sinInterHeight2;
		TradeEndX = TradeStartX + (3 * 22);
		TradeEndY = TradeStartY + (4 * 22);
		if (TradeStartX <= pCursorPos.x && TradeEndX > pCursorPos.x && TradeStartY <= pCursorPos.y && TradeEndY > pCursorPos.y)
		{
			TradeColorRect.left = TradeStartX;
			TradeColorRect.top = TradeStartY;
			TradeColorRect.right = TradeEndX - TradeStartX;
			TradeColorRect.bottom = TradeEndY - TradeStartY;

			pItem->iPlaceX = TradeStartX + ((TradeEndX - TradeStartX) - pItem->iWidth) / 2;
			pItem->iPlaceY = TradeStartY + ((TradeEndY - TradeStartY) - pItem->iHeight) / 2;
			pItem->iItemSlot = 0;
			TradeColorIndex = SET_ITEM_CHECK_COLOR;

			if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 5))
			{
				TradeColorIndex = NOT_SETTING_COLOR;
				return FALSE;

			}
			if (sinChar->iGold < pItem->sItem.iSalePrice)
			{
				TradeColorIndex = NOT_ENOUGH_MONEY;
				return FALSE;
			}
			return TRUE;
		}
	}
	return TRUE;
}
int CManufacture::LastSetManufactureItem(ItemData *pItem)
{
	CheckManufactureItem();
	if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinPR3 || (pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinPR4)
	{
		for (int j = 1; j < 4; j++)
		{
			if (!sManufactureItem.ManufactureItem[j].bValid)
			{
				memcpy(&sManufactureItem.ManufactureItem[j], pItem, sizeof(ItemData));
				sManufactureItem.ManufactureItem[j].iPlaceX = pItem->iPlaceX;
				sManufactureItem.ManufactureItem[j].iPlaceY = pItem->iPlaceY;
				pItem->bValid = 0;
				sinPlaySound(sManufactureItem.ManufactureItem[j].iInvItemSound);
				ReFormManufactureItem();
				return TRUE;
			}
		}
	}
	else
	{
		if (!sManufactureItem.ManufactureItem[0].bValid)
		{
			memcpy(&sManufactureItem.ManufactureItem[0], pItem, sizeof(ItemData));
			sManufactureItem.ManufactureItem[0].iPlaceX = pItem->iPlaceX;
			sManufactureItem.ManufactureItem[0].iPlaceY = pItem->iPlaceY;
			pItem->bValid = 0;
			sinPlaySound(sManufactureItem.ManufactureItem[0].iInvItemSound);
			ReFormManufactureItem();
			return TRUE;
		}
	}
	return TRUE;

}
int CManufacture::CheckManufactureItem()
{
	int TempCheckDataSum = 0;

	for (int i = 0; i < 4; i++)
	{
		if (sManufactureItem.ManufactureItem[i].bValid)
		{
			TempCheckDataSum += (i + 1)*sManufactureItem.ManufactureItem[i].iPlaceX;
			TempCheckDataSum += (i + 1)*sManufactureItem.ManufactureItem[i].iPlaceY;
			TempCheckDataSum += sManufactureItem.ManufactureItem[i].sItem.iChk2;
			TempCheckDataSum += sManufactureItem.ManufactureItem[i].sItem.iChk1;
		}
	}
	return TRUE;
}

int CManufacture::ReFormManufactureItem()
{
	m_ManufactureItemCheckSum = 0;
	for (int i = 0; i < 4; i++)
	{
		if (sManufactureItem.ManufactureItem[i].bValid)
		{
			m_ManufactureItemCheckSum += (i + 1)*sManufactureItem.ManufactureItem[i].iPlaceX;
			m_ManufactureItemCheckSum += (i + 1)*sManufactureItem.ManufactureItem[i].iPlaceY;
			m_ManufactureItemCheckSum += sManufactureItem.ManufactureItem[i].sItem.iChk2;
			m_ManufactureItemCheckSum += sManufactureItem.ManufactureItem[i].sItem.iChk1;
		}
	}
	return TRUE;
}


int CManufacture::PickUpManufactureItem(int x, int y, int PickUpFlag)
{
	int i = 0;
	SelectTradeItemIndex = 0;

	for (i = 0; i < 4; i++)
	{
		if (sManufactureItem.ManufactureItem[i].bValid)
		{
			if (sManufactureItem.ManufactureItem[i].iPlaceX < x  &&
				sManufactureItem.ManufactureItem[i].iPlaceX + sManufactureItem.ManufactureItem[i].iWidth > x  &&
				sManufactureItem.ManufactureItem[i].iPlaceY < y  &&
				sManufactureItem.ManufactureItem[i].iPlaceY + sManufactureItem.ManufactureItem[i].iHeight > y)
			{
				if (PickUpFlag)
				{
					int cnt = 0;
					for (cnt = 1; cnt < 4; cnt++)
					{
						if (i == 0 && sManufactureItem.ManufactureItem[cnt].bValid)
						{
							cMessageBox.ShowMessage(MESSAGE_NOT_MANUFACTURE);
							return FALSE;
						}
					}

					CheckManufactureItem();
					memcpy(&MouseItem, &sManufactureItem.ManufactureItem[i], sizeof(ItemData));
					sManufactureItem.ManufactureItem[i].bValid = 0;
					ZeroMemory(&sManufactureItem.ManufactureItem[i], sizeof(ItemData));

					sinPlaySound(sManufactureItem.ManufactureItem[i].iInvItemSound);
					TradeColorIndex = 0;
					ReFormManufactureItem();
					return TRUE;
				}
				else
				{
					SelectTradeItemIndex = i + 1;
					TradeColorIndex = SELECT_ITEM_COLOR;
					sinShowItemInfoFlag = 1;
					cItem.ShowItemInfo(&sManufactureItem.ManufactureItem[i], 2);
				}
			}
		}
	}
	return FALSE;
}
int CManufacture::ManufactureCheckEmptyArea(ItemData *pItem)
{
	int cntx, cnty;
	int cx, cy;

	RECT rect;
	int	flag;
	int StartX = 23;
	int StartY = 436;

	cx = (22 * INVENTORY_BOX_ROW) - pItem->iWidth;
	cy = (22 * INVENTORY_BOX_COL) - pItem->iHeight;

	for (cntx = StartX; cntx <= StartX + cx; cntx += 22)
	{
		for (cnty = StartY; cnty <= StartY + cy; cnty += 22)
		{
			flag = 0;

			for (int i = 0; i < INVENTORY_MAXITEM; i++)
			{
				if (cInvenTory.InvenItem[i].bValid)
				{
					rect.left	= cInvenTory.InvenItem[i].iPlaceX;
					rect.right	= cInvenTory.InvenItem[i].iPlaceX + cInvenTory.InvenItem[i].iWidth;
					rect.top	= cInvenTory.InvenItem[i].iPlaceY;
					rect.bottom = cInvenTory.InvenItem[i].iPlaceY + cInvenTory.InvenItem[i].iHeight;

					if (cntx > rect.left - pItem->iWidth &&
						cntx < rect.right &&
						cnty > rect.top - pItem->iHeight &&
						cnty < rect.bottom)
						flag++;
				}
			}
			if (flag == 0)
			{
				pItem->iPlaceX = cntx;
				pItem->iPlaceY = cnty;
				pItem->iItemSlot = 0;
				return TRUE;
			}
		}
	}

	return FALSE;
}

int CManufacture::sinSendManufactureItem()
{
	if (MixItemNoCopyFlag)
		return FALSE;

	int i = 0;

	memcpy(&sManufactureItemBackUp, &sManufactureItem, sizeof(SManufactureItem));
	MixItemNoCopyFlag = 1;
	ZeroMemory(&sManufactureItem_Send.DesManufactureItem, sizeof(ItemData));

	sManufactureItem_Send.Money = m_ManufacturePrice;

	for (i = 0; i < 4; i++)
	{
		if (sManufactureItem.ManufactureItem[i].bValid)
		{
			sManufactureItem_Send.RuneCode[i] = sManufactureItem.ManufactureItem[i].sBaseItemID.ToInt();
			sManufactureItem_Send.CheckSum[i] = sManufactureItem.ManufactureItem[i].sItem.iChk2;
			sManufactureItem_Send.Head[i] = sManufactureItem.ManufactureItem[i].sItem.iChk1;
		}
	}

	CheckCraftMoney = sManufactureItem_Send.Money;

	CraftItemSendServerIndex++;
	sManufactureItem_Send.Index = CraftItemSendServerIndex;

	SendManufactureItemToServer(&sManufactureItem_Send);

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
int CManufacture::RecvManufactureItemResult(SManufactureItem_Server *pManufactureItem_Server)
{
	CheckMixItemCopyFlag = 0;
	if (!ManufactureItem.m_OpenFlag)
	{
		MixItemNoCopyFlag = 0;
		memset(&sManufactureItem, 0, sizeof(SManufactureItem));
		memset(&sManufactureItemBackUp, 0, sizeof(SManufactureItem));
		memset(&sManufactureItem_Recv, 0, sizeof(SManufactureItem_Server));
		memset(&sManufactureItem_Send, 0, sizeof(SManufactureItem_Server));
		MixCancelButtonDelayFlag = 0;
		return FALSE;
	}

	int i, LineCount = 0, Temp;

	if (pManufactureItem_Server->Result)
	{
		ShowItemManufactureMessageFlag = 1;

		ItemData TempItem;
		if (LoadItemImage(&pManufactureItem_Server->DesManufactureItem.sItem, &TempItem))
		{
			lstrcpy(szCraftItemBuff, pManufactureItem_Server->DesManufactureItem.sItem.szItemName);
			lstrcat(szCraftItemBuff, "\r");
			Temp = lstrlen(szCraftItemBuff);
			for (i = 0; i < Temp; i++)
			{
				if (szCraftItemBuff[i] == '\r')
				{
					LineCount++;
				}
			}
			CraftItemMessageSize.x = 14;
			CraftItemMessageSize.y = ((LineCount) * 2) + 2;

			if (cInvenTory.CheckRequireItemToSet(&TempItem))
			{
				if (!cInvenTory.AutoSetInvenItem(&TempItem, 1))
					sinThrowItemToFeild(&pManufactureItem_Server->DesManufactureItem);
			}

		}

		CheckCharForm();
		sinMinusMoney(m_ManufacturePrice);
		ReformCharForm();
		SendSaveMoney();
		SaveGameData();
		ManufactureItem.m_OpenFlag = 0;
	}
	else
	{
		CheckCharForm();
		sinMinusMoney(m_ManufacturePrice);
		ReformCharForm();
		SendSaveMoney();
		ManufactureItem.m_OpenFlag = 0;
		cMessageBox.ShowMessage(MESSAGE_FAILD_MANUFACTURE_ITEM);
	}

	for (i = 0; i < 4; i++)
	{
		if (sManufactureItemBackUp.ManufactureItem[i].bValid)
			cInvenTory.DeleteInvenItemToServer(sManufactureItemBackUp.ManufactureItem[i].sItem.sItemID.ToInt(), sManufactureItemBackUp.ManufactureItem[i].sItem.iChk1, sManufactureItemBackUp.ManufactureItem[i].sItem.iChk2);
	}
	ZeroMemory(&sManufactureItem, sizeof(SManufactureItem));
	ZeroMemory(&sManufactureItemBackUp, sizeof(SManufactureItem));
	ZeroMemory(&sManufactureItem_Recv, sizeof(SManufactureItem_Server));
	ZeroMemory(&sManufactureItem_Send, sizeof(SManufactureItem_Server));

	MixItemNoCopyFlag = 0;
	MixCancelButtonDelayFlag = 0;
	m_ManufacturePrice = 0;
	ForceItemPrice2 = 0;
	return TRUE;
}

int CManufacture::GetManufactureCheckEmptyArea()
{
	int cntx, cnty;
	int cx, cy;

	RECT	rect;
	int		flag;
	int StartX = 23;
	int StartY = 436;

	cx = (22 * INVENTORY_BOX_ROW) - 22;
	cy = (22 * INVENTORY_BOX_COL) - 22;

	int count = 0;

	for (cntx = StartX; cntx <= StartX + cx; cntx += 22)
	{
		for (cnty = StartY; cnty <= StartY + cy; cnty += 22)
		{
			flag = 0;
			for (int i = 0; i < INVENTORY_MAXITEM; i++)
			{
				if (cInvenTory.InvenItem[i].bValid)
				{
					rect.left	= cInvenTory.InvenItem[i].iPlaceX;
					rect.right	= cInvenTory.InvenItem[i].iPlaceX + cInvenTory.InvenItem[i].iWidth;
					rect.top	= cInvenTory.InvenItem[i].iPlaceY;
					rect.bottom = cInvenTory.InvenItem[i].iPlaceY + cInvenTory.InvenItem[i].iHeight;

					if (cntx > rect.left - 22 &&
						cntx < rect.right &&
						cnty > rect.top - 22 &&
						cnty < rect.bottom)
						flag++;
				}
			}
			if (flag == 0)
				count++;
		}
	}
	if (count)
		return count;
	else
		return 0;
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
										lstrcpy(Result.ItemName, "Result of manufacturing");
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
int cELEMENT::CheckItem()
{
	for (int i = 0; i < 3; i++)
	{
		if (ElementItem[1].sItem.sItemID.ToInt() == Element_StoneInfo[i][0] &&
			ElementItem[2].sItem.sItemID.ToInt() == Element_StoneInfo[i][1] &&
			ElementItem[3].sItem.sItemID.ToInt() == Element_StoneInfo[i][2] &&
			ElementItem[4].sItem.sItemID.ToInt() == Element_StoneInfo[i][3] &&
			ElementItem[5].sItem.sItemID.ToInt() == Element_StoneInfo[i][4])
		{
			ElementCheckFlag = TRUE;
			break;
		}
		else
			ElementCheckFlag = FALSE;
	}
	return TRUE;
}
int cELEMENT::ReformElementItem()
{
	ElementItemCheckSum = 0;
	for (int i = 0; i < MAX_ELEMENT; i++)
	{
		if (ElementItem[i].bValid)
		{
			ElementItemCheckSum += (i + 1) * ElementItem[i].iPlaceX;
			ElementItemCheckSum += (i + 1) * ElementItem[i].iPlaceY;
			ElementItemCheckSum += ElementItem[i].sItem.iChk2;
			ElementItemCheckSum += ElementItem[i].sItem.iChk1;
		}
	}
	return TRUE;
}
int cELEMENT::PickUpElementItem(int x, int y, int PickUpFlag, int Kind)
{
	SelectTradeItemIndex = 0;
	if (Kind == 0)
	{
		for (int i = 0; i < 6; i++)
		{
			if (ElementItem[i].bValid)
			{
				if (ElementItem[i].iPlaceX < x &&
					ElementItem[i].iPlaceX + ElementItem[i].iWidth > x &&
					ElementItem[i].iPlaceY < y &&
					ElementItem[i].iPlaceY + ElementItem[i].iHeight > y)
				{
					switch (PickUpFlag)
					{
					case 1:
						if (i != 0)
							ElementCheckFlag = FALSE;
						for (int j = 1; j <= 5; j++)
						{
							if (ElementItem[j].bValid && i == 0)
							{
								cMessageBox.ShowMessage(MESSAGE_NOT_MIXTURE_RESET_ITEM);
								return FALSE;
							}
						}
						memcpy(&MouseItem, &ElementItem[i], sizeof(ItemData));
						ElementItem[i].bValid = 0;
						sinPlaySound(ElementItem[i].iInvItemSound);
						ZeroMemory(&ElementItem[i], sizeof(ItemData));
						TradeColorIndex = 0;
						return TRUE;
						break;
					case 2:
						if (i != 0)
							ElementCheckFlag = FALSE;
						for (int j = 1; j <= 5; j++)
						{
							if (ElementItem[j].bValid && i == 0)
							{
								cMessageBox.ShowMessage(MESSAGE_NOT_MIXTURE_RESET_ITEM);
								return FALSE;
							}
						}
						if (cCraftItem.CraftCheckEmptyArea(&ElementItem[i]))
						{
							if (!cInvenTory.AutoSetInvenItem(&ElementItem[i]))
							{
								sinThrowItemToFeild(&ElementItem[i]);
								ElementItem[i].bValid = 0;
							}
						}
						else
							cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);

						return TRUE;
						break;
					default:
						SelectTradeItemIndex = i + 1;
						TradeColorIndex = SELECT_ITEM_COLOR;
						sinShowItemInfoFlag = 1;
						cItem.ShowItemInfo(&ElementItem[i], 2);
						break;
					}
				}
			}
		}
	}
	return FALSE;
}
int cELEMENT::LastSetElementItem(ItemData *pItem, int Kind)
{
	switch (Kind)
	{
	case 0:
		if (!ElementItem[0].bValid)
		{
			memcpy(&ElementItem[0], pItem, sizeof(ItemData));
			ElementItem[0].iPlaceX = pItem->iPlaceX;
			ElementItem[0].iPlaceY = pItem->iPlaceY;
			pItem->bValid = 0;
			sinPlaySound(ElementItem[0].iInvItemSound);
			return TRUE;
		}
		break;
	case 1:
		if (ElementItem[0].bValid)
		{
			for (int i = 1; i <= 4; i++)
			{
				if (!ElementItem[i].bValid)
				{
					memcpy(&ElementItem[i], pItem, sizeof(ItemData));
					ElementItem[i].iPlaceX = pItem->iPlaceX;
					ElementItem[i].iPlaceY = pItem->iPlaceY;
					pItem->bValid = 0;
					sinPlaySound(ElementItem[i].iInvItemSound);
					return TRUE;
				}
			}
		}
		break;
	case 2:
		if (ElementItem[0].bValid && !ElementItem[5].bValid)
		{
			memcpy(&ElementItem[5], pItem, sizeof(ItemData));
			ElementItem[5].iPlaceX = pItem->iPlaceX;
			ElementItem[5].iPlaceY = pItem->iPlaceY;
			pItem->bValid = 0;
			sinPlaySound(ElementItem[5].iInvItemSound);
			return TRUE;
		}
		break;
	}
	return FALSE;
}
// ¼ì²éÊôÐÔÏµÍ³
int cELEMENT::SetElementItemAreaCheck(ItemData *pItem)
{
	TradeColorIndex = 0;
	TradeCrashItemIndex[0] = 0;

	cTrade.InitTradeColorRect();

	switch (pItem->sItem.sItemID.ToItemType())
	{
	case sinWA1:
	case sinWC1:
	case sinWH1:
	case sinWP1:
	case sinWS1:
	case sinWS2:
	case sinWM1:
	case sinWT1:
	case sinWD1:
	case sinWN1:
		if (pItem->sItem.eCraftType == ITEMCRAFTTYPE_Quest)
		{
			TradeColorIndex = NOT_SETTING_COLOR;
			return FALSE;
		}
		TradeStartX = 58;
		TradeStartY = 193 + sinInterHeight2;
		TradeEndX = TradeStartX + (3 * 22);
		TradeEndY = TradeStartY + (4 * 22);

		if (TradeStartX <= pCursorPos.x && TradeEndX > pCursorPos.x && TradeStartY <= pCursorPos.y && TradeEndY > pCursorPos.y)
		{
			TradeColorRect.left = TradeStartX;
			TradeColorRect.top = TradeStartY;
			TradeColorRect.right = TradeEndX - TradeStartX;
			TradeColorRect.bottom = TradeEndY - TradeStartY;

			pItem->iPlaceX = TradeStartX + ((TradeEndX - TradeStartX) - pItem->iWidth) / 2;
			pItem->iPlaceY = TradeStartY + ((TradeEndY - TradeStartY) - pItem->iHeight) / 2;
			pItem->iItemSlot = 0;

			TradeColorIndex = SET_ITEM_CHECK_COLOR;

			if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 7))
			{
				TradeColorIndex = NOT_SETTING_COLOR;
				return FALSE;
			}
		}
		if (cShop.haBuyMoneyCheck(pItem->sItem.iSalePrice) == 0)
		{
			TradeColorIndex = NOT_ENOUGH_MONEY;
			return FALSE;
		}
		if (pItem->sItem.ItemElement > 0)
		{
			TradeColorIndex = NOT_SETTING_COLOR;
			return FALSE;
		}
		break;
	case sinSS1:
		TradeStartX = AgingLevelSheltomXY[0][0].x + 11;
		TradeStartY = AgingLevelSheltomXY[0][0].y + 19;
		TradeEndX = TradeStartX + 22 * 2;
		TradeEndY = TradeStartY + 22 * 2;

		for (int i = pItem->iPlaceX + 11; i < pItem->iPlaceX + pItem->iWidth; i += 22)
		{
			for (int j = pItem->iPlaceY + 11; j < pItem->iPlaceY + pItem->iHeight; j += 22)
			{
				if (TradeStartX <= i && TradeEndX > i && TradeStartY <= j && TradeEndY > j)
				{
					TradeColorRect.left = TradeStartX + (((i - TradeStartX) / 22) * 22);
					TradeColorRect.top = TradeStartY + (((j - TradeStartY) / 22) * 22);
					TradeColorRect.right = pItem->iWidth;
					TradeColorRect.bottom = pItem->iHeight;

					if (TradeEndX < (TradeColorRect.left + TradeColorRect.right) - 11 || TradeEndY < (TradeColorRect.top + TradeColorRect.bottom) - 11)
					{
						cTrade.InitTradeColorRect();
						return FALSE;
					}
					pItem->iPlaceX = TradeColorRect.left;
					pItem->iPlaceY = TradeColorRect.top;
					pItem->iItemSlot = 0;
					TradeColorIndex = SET_ITEM_CHECK_COLOR;
					if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 7))
					{
						TradeColorIndex = NOT_SETTING_COLOR;
						return FALSE;
					}
				}
			}
		}
		break;
	case sinES1:
		TradeStartX = 160;
		TradeStartY = 268 + sinInterHeight2;
		TradeEndX = TradeStartX + 22;
		TradeEndY = TradeStartY + 22;

		for (int i = pItem->iPlaceX + 11; i < pItem->iPlaceX + pItem->iWidth; i += 22)
		{
			for (int j = pItem->iPlaceY + 11; j < pItem->iPlaceY + pItem->iHeight; j += 22)
			{
				if (TradeStartX <= i && TradeEndX > i && TradeStartY <= j && TradeEndY > j)
				{
					TradeColorRect.left = TradeStartX + (((i - TradeStartX) / 22) * 22);
					TradeColorRect.top = TradeStartY + (((j - TradeStartY) / 22) * 22);
					TradeColorRect.right = pItem->iWidth;
					TradeColorRect.bottom = pItem->iHeight;

					if (TradeEndX < (TradeColorRect.left + TradeColorRect.right) - 11 ||
						TradeEndY < (TradeColorRect.top + TradeColorRect.bottom) - 11)
					{
						cTrade.InitTradeColorRect();
						return FALSE;
					}
					pItem->iPlaceX = TradeColorRect.left;
					pItem->iPlaceY = TradeColorRect.top;
					pItem->iItemSlot = 0;
					TradeColorIndex = SET_ITEM_CHECK_COLOR;
					if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 7))
					{
						TradeColorIndex = NOT_SETTING_COLOR;
						return FALSE;
					}
				}
			}
		}
		break;
	}
	return TRUE;
}
// ÉèÖÃÓÒ¼ü
int cELEMENT::SetElementItem(ItemData *pItem)
{
	int ErrorFlag = 0;

	switch (pItem->sItem.sItemID.ToItemType())
	{
	case sinWA1:
	case sinWC1:
	case sinWH1:
	case sinWP1:
	case sinWS1:
	case sinWS2:
	case sinWM1:
	case sinWT1:
	case sinWD1:
	case sinWN1:
		if (pItem->sItem.eCraftType == ITEMCRAFTTYPE_Quest)
			return FALSE;
		if (cShop.haBuyMoneyCheck(pItem->sItem.iSalePrice) == 0)
		{
			cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_MONEY);
			return FALSE;
		}
		if (pItem->sItem.ItemElement > 0)
			return FALSE;
		if (ElementItem[0].bValid == NULL)
		{
			int Startx = 58;
			int Starty = 193 + sinInterHeight2;
			int Endx = Startx + 3 * 22;
			int Endy = Starty + 4 * 22;
			pItem->iPlaceX = Startx + ((Endx - Startx) - pItem->iWidth) / 2;
			pItem->iPlaceY = Starty + ((Endy - Starty) - pItem->iHeight) / 2;
			return TRUE;
		}
		break;
	case sinSS1:
		if (ElementItem[0].bValid)
		{
			if (GetEmptyArea(pItem))
			{
				pItem->iPlaceX = pItem->iPlaceX;
				pItem->iPlaceY = pItem->iPlaceY;
				return TRUE;
			}
		}
		break;
	case sinES1:
		if (ElementItem[0].bValid)
		{
			if (ElementItem[5].bValid == NULL)
			{
				pItem->iPlaceX = 160;
				pItem->iPlaceY = 268 + sinInterHeight2;
				return TRUE;
			}
		}
		break;
	}
	return FALSE;
}
int cELEMENT::GetEmptyArea(ItemData *pItem)
{
	int cntx, cnty;
	int cx, cy;

	RECT	rect;
	int		flag;
	int StartX = 218 + 11;
	int StartY = 193 + 19 + sinInterHeight2;

	cx = (22 * 2) - pItem->iWidth;
	cy = (22 * 2) - pItem->iHeight;

	for (cnty = StartY; cnty <= StartY + cy; cnty += 22)
	{
		for (cntx = StartX; cntx <= StartX + cx; cntx += 22)
		{
			flag = 0;
			for (int i = 1; i < 5; i++)
			{
				if (ElementItem[i].bValid)
				{
					rect.left	= ElementItem[i].iPlaceX;
					rect.right	= ElementItem[i].iPlaceX + ElementItem[i].iWidth;
					rect.top	= ElementItem[i].iPlaceY;
					rect.bottom = ElementItem[i].iPlaceY + ElementItem[i].iHeight;

					if (cntx > rect.left - pItem->iWidth &&
						cntx < rect.right &&
						cnty > rect.top - pItem->iHeight &&
						cnty < rect.bottom)
						flag++;
				}
			}
			if (flag == 0)
			{
				pItem->iPlaceX = cntx;
				pItem->iPlaceY = cnty;
				pItem->iItemSlot = 0;
				return TRUE;
			}
		}
	}

	return FALSE;
}
// È¡ÏûÊôÐÔÏµÍ³
int cELEMENT::CancelElementItem(int Flag)
{
	if (CheckMixItemCopyFlag == FALSE)
	{
		for (int i = 0; i < 6; i++)
		{
			if (ElementItem[i].bValid)
			{
				if (!cInvenTory.AutoSetInvenItem(&ElementItem[i]))
					sinThrowItemToFeild(&ElementItem[i]);
				ElementItem[0].bValid = 0;
			}
		}

		OpenFlag = FALSE;
		ResetInvenItemCode();

		return TRUE;
	}

	return FALSE;
}
int cELEMENT::SendElementItem()
{
	if (MixItemNoCopyFlag == FALSE)
	{
		memcpy(ElementItemBackUp, ElementItem, sizeof(ItemData)*MAX_ELEMENT);
		MixItemNoCopyFlag = TRUE;
		ZeroMemory(&ElementItemServer, sizeof(ELEMENT_ITEM_SERVER));

		if (ElementItem[0].bValid)
			ElementItemServer.DesItem = ElementItem[0];

		for (int i = 0; i < 5; i++)
		{
			ElementItemServer.SheltomCode[i] = ElementItem[i + 1].sBaseItemID.ToInt();
			ElementItemServer.CheckSum[i] = ElementItem[i + 1].sItem.iChk2;
			ElementItemServer.Head[i] = ElementItem[i + 1].sItem.iChk1;
		}
		CraftItemSendServerIndex++;

		ElementItemServer.Index = CraftItemSendServerIndex;
		ElementItemServer.Money = ElementItem[0].sItem.iSalePrice;

		SendElementItemToServer(&ElementItemServer);

		CheckCharForm();
		sinMinusMoney(ElementItemServer.Money, 1);
		ReformElementItem();
		SendSaveMoney();
	}
	return FALSE;
}
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
int cELEMENT::RecvElementResult(ELEMENT_ITEM_SERVER *pItemServer)
{
	CheckMixItemCopyFlag = FALSE;

	if (OpenFlag == FALSE)
	{
		MixItemNoCopyFlag = 0;
		MixCancelButtonDelayFlag = 0;
		ZeroMemory(ElementItem, sizeof(ItemData) * MAX_ELEMENT);
		ZeroMemory(ElementItemBackUp, sizeof(ItemData) * MAX_ELEMENT);
		ZeroMemory(&ElementItemServer, sizeof(ELEMENT_ITEM_SERVER));
		return FALSE;
	}

	if (pItemServer->Result == TRUE)
	{
		if (cInvenTory.CheckRequireItemToSet(&pItemServer->DesItem))
		{
			if (!cInvenTory.AutoSetInvenItem(&pItemServer->DesItem, 1))
				sinThrowItemToFeild(&pItemServer->DesItem);
		}

		cMessageBox.ShowMessage(MESSAGE_OK_MIXTURE_RESET_ITEM);
		sinPlaySound(SIN_SOUND_EAT_POTION2);
	}
	else
	{
		sinPlaySound(SIN_SOUND_FAILD_MIXITEM);
		cMessageBox.ShowMessage(MESSAGE_FAIL_MIXTURE_RESET_ITEM);
	}

	for (int i = 0; i < 6; i++)
	{
		if (ElementItemBackUp[i].bValid)
			cInvenTory.DeleteInvenItemToServer(ElementItemBackUp[i].sItem.sItemID.ToInt(), ElementItemBackUp[i].sItem.iChk1, ElementItemBackUp[i].sItem.iChk2);
	}

	MixItemNoCopyFlag = 0;
	MixCancelButtonDelayFlag = 0;
	ZeroMemory(ElementItem, sizeof(ItemData) * MAX_ELEMENT);
	ZeroMemory(ElementItemBackUp, sizeof(ItemData) * MAX_ELEMENT);
	ZeroMemory(&ElementItemServer, sizeof(ELEMENT_ITEM_SERVER));
	OpenFlag = FALSE;
	return TRUE;
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
int cSOCKET::CancelSocketItem(int Flag)
{
	if (CheckMixItemCopyFlag == FALSE)
	{
		for (int i = 0; i < 5; i++)
		{
			if (SocketItem[i].bValid)
			{
				if (!cInvenTory.AutoSetInvenItem(&SocketItem[i]))
					sinThrowItemToFeild(&SocketItem[i]);
				SocketItem[i].bValid = 0;
			}
		}

		OpenFlag = FALSE;
		ResetInvenItemCode();

		return TRUE;
	}

	return FALSE;
}
int cSOCKET::ReformSocketItem()
{
	SocketItemCheckSum = 0;

	for (int i = 0; i < MAX_SOCKET; i++)
	{
		if (SocketItem[i].bValid)
		{
			SocketItemCheckSum += (i + 1) * SocketItem[i].iPlaceX;
			SocketItemCheckSum += (i + 1) * SocketItem[i].iPlaceY;
			SocketItemCheckSum += SocketItem[i].sItem.iChk2;
			SocketItemCheckSum += SocketItem[i].sItem.iChk1;
		}
	}

	return TRUE;
}
int cSOCKET::PickUpSocketItem(int x, int y, int PickUpFlag, int Kind)
{
	SelectTradeItemIndex = 0;
	if (Kind == 0)
	{
		for (int i = 0; i < 6; i++)
		{
			if (SocketItem[i].bValid)
			{
				if (SocketItem[i].iPlaceX < x &&
					SocketItem[i].iPlaceX + SocketItem[i].iWidth > x &&
					SocketItem[i].iPlaceY < y &&
					SocketItem[i].iPlaceY + SocketItem[i].iHeight > y)
				{
					switch (PickUpFlag)
					{
					case 1:
						if (i != 0)
							SocketCheckFlag = FALSE;

						for (int j = 1; j <= 4; j++)
						{
							if (SocketItem[j].bValid && i == 0)
							{
								cMessageBox.ShowMessage(MESSAGE_NOT_MIXTURE_RESET_ITEM);
								return FALSE;
							}
						}
						memcpy(&MouseItem, &SocketItem[i], sizeof(ItemData));
						SocketItem[i].bValid = 0;
						sinPlaySound(SocketItem[i].iInvItemSound);
						ZeroMemory(&SocketItem[i], sizeof(ItemData));
						TradeColorIndex = 0;
						return TRUE;
						break;
					case 2:
						if (i != 0)
							SocketCheckFlag = FALSE;

						for (int j = 1; j <= 5; j++)
						{
							if (SocketItem[j].bValid && i == 0)
							{
								cMessageBox.ShowMessage(MESSAGE_NOT_MIXTURE_RESET_ITEM);
								return FALSE;
							}
						}
						if (cCraftItem.CraftCheckEmptyArea(&SocketItem[i]))
						{
							if (!cInvenTory.AutoSetInvenItem(&SocketItem[i]))
							{
								sinThrowItemToFeild(&SocketItem[i]);
								SocketItem[i].bValid = 0;
							}
						}
						else
							cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);

						return TRUE;
						break;
					default:
						SelectTradeItemIndex = i + 1;
						TradeColorIndex = SELECT_ITEM_COLOR;
						sinShowItemInfoFlag = 1;
						cItem.ShowItemInfo(&SocketItem[i], 2);
						break;
					}
				}
			}
		}
	}
	return FALSE;
}
int cSOCKET::LastSetSocketItem(ItemData *pItem, int Kind)
{
	switch (Kind)
	{
	case 0:
		if (!SocketItem[0].bValid)
		{
			memcpy(&SocketItem[0], pItem, sizeof(ItemData));
			SocketItem[0].iPlaceX = pItem->iPlaceX;
			SocketItem[0].iPlaceY = pItem->iPlaceY;
			pItem->bValid = 0;
			sinPlaySound(SocketItem[0].iInvItemSound);
			return TRUE;
		}
		break;
	case 1:
		if (SocketItem[0].bValid)
		{
			for (int i = 1; i <= 4; i++)
			{
				if (!SocketItem[i].bValid)
				{
					memcpy(&SocketItem[i], pItem, sizeof(ItemData));
					SocketItem[i].iPlaceX = pItem->iPlaceX;
					SocketItem[i].iPlaceY = pItem->iPlaceY;
					pItem->bValid = 0;
					sinPlaySound(SocketItem[i].iInvItemSound);
					return TRUE;
				}
			}
		}
		break;
	}
	return FALSE;
}
int cSOCKET::SetSocketItemAreaCheck(ItemData *pItem)
{
	TradeColorIndex = 0;
	TradeCrashItemIndex[0] = 0;

	cTrade.InitTradeColorRect();

	switch (pItem->sItem.sItemID.ToItemType())
	{
	case sinWA1:
	case sinWC1:
	case sinWH1:
	case sinWP1:
	case sinWS1:
	case sinWS2:
	case sinWM1:
	case sinWT1:
	case sinWD1:
	case sinWN1:
	case sinDA1:
	case sinDA2:
	case sinDB1:
	case sinDG1:
	case sinOM1:
	case sinDS1:
		if (pItem->sItem.eCraftType == ITEMCRAFTTYPE_Quest)
		{
			TradeColorIndex = NOT_SETTING_COLOR;
			return FALSE;
		}

		TradeStartX = 58;
		TradeStartY = 193 + sinInterHeight2;

		TradeEndX = TradeStartX + (3 * 22);
		TradeEndY = TradeStartY + (4 * 22);

		if (TradeStartX <= pCursorPos.x && TradeEndX > pCursorPos.x &&
			TradeStartY <= pCursorPos.y && TradeEndY > pCursorPos.y)
		{
			TradeColorRect.left = TradeStartX;
			TradeColorRect.top = TradeStartY;
			TradeColorRect.right = TradeEndX - TradeStartX;
			TradeColorRect.bottom = TradeEndY - TradeStartY;

			pItem->iPlaceX = TradeStartX + ((TradeEndX - TradeStartX) - pItem->iWidth) / 2;
			pItem->iPlaceY = TradeStartY + ((TradeEndY - TradeStartY) - pItem->iHeight) / 2;
			pItem->iItemSlot = 0;

			TradeColorIndex = SET_ITEM_CHECK_COLOR;

			if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 9))
			{
				TradeColorIndex = NOT_SETTING_COLOR;
				return FALSE;
			}
		}
		if (cShop.haBuyMoneyCheck(pItem->sItem.iSalePrice) == 0)
		{
			TradeColorIndex = NOT_ENOUGH_MONEY;
			return FALSE;
		}
		int SocketisHave;

		SocketisHave = 0;

		for (int i = 0; i < 2; i++)
		{
			if (pItem->sItem.ItemSocket[i] & 0xF0)
				SocketisHave++;
		}
		if (SocketisHave == 2)
		{
			TradeColorIndex = NOT_SETTING_COLOR;
			return FALSE;
		}
		break;
	case sinSR1:
		TradeStartX = AgingLevelSheltomXY[0][0].x + 11;
		TradeStartY = AgingLevelSheltomXY[0][0].y + 19;
		TradeEndX = TradeStartX + 22 * 2;
		TradeEndY = TradeStartY + 22 * 2;

		for (int i = pItem->iPlaceX + 11; i < pItem->iPlaceX + pItem->iWidth; i += 22)
		{
			for (int j = pItem->iPlaceY + 11; j < pItem->iPlaceY + pItem->iHeight; j += 22)
			{
				if (TradeStartX <= i && TradeEndX > i && TradeStartY <= j && TradeEndY > j)
				{
					TradeColorRect.left = TradeStartX + (((i - TradeStartX) / 22) * 22);
					TradeColorRect.top = TradeStartY + (((j - TradeStartY) / 22) * 22);
					TradeColorRect.right = pItem->iWidth;
					TradeColorRect.bottom = pItem->iHeight;

					if (TradeEndX < (TradeColorRect.left + TradeColorRect.right) - 11 ||
						TradeEndY < (TradeColorRect.top + TradeColorRect.bottom) - 11)
					{
						cTrade.InitTradeColorRect();
						return FALSE;
					}

					pItem->iPlaceX = TradeColorRect.left;
					pItem->iPlaceY = TradeColorRect.top;
					pItem->iItemSlot = 0;
					TradeColorIndex = SET_ITEM_CHECK_COLOR;

					if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 9))
					{
						TradeColorIndex = NOT_SETTING_COLOR;
						return FALSE;
					}
				}
			}
		}
		break;
	}
	return TRUE;
}
int cSOCKET::SetSocketItem(ItemData *pItem)
{
	int ErrorFlag = 0;

	switch (pItem->sItem.sItemID.ToItemType())
	{
	case sinWA1:
	case sinWC1:
	case sinWH1:
	case sinWP1:
	case sinWS1:
	case sinWS2:
	case sinWM1:
	case sinWT1:
	case sinWD1:
	case sinWN1:
	case sinDA1:
	case sinDA2:
	case sinDB1:
	case sinDG1:
	case sinOM1:
	case sinDS1:
		if (pItem->sItem.eCraftType == ITEMCRAFTTYPE_Quest)
			return FALSE;
		if (cShop.haBuyMoneyCheck(pItem->sItem.iSalePrice) == 0)
		{
			cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_MONEY);
			return FALSE;
		}
		if (pItem->sItem.ItemElement > 0)
			return FALSE;

		int SocketisHave;

		SocketisHave = 0;

		for (int i = 0; i < 2; i++)
		{
			if (pItem->sItem.ItemSocket[i] & 0xF0)
				SocketisHave++;

		}
		if (SocketisHave == 2)
		{
			TradeColorIndex = NOT_SETTING_COLOR;
			return FALSE;
		}
		if (SocketItem[0].bValid == NULL)
		{
			int Startx = 58;
			int Starty = 193 + sinInterHeight2;
			int Endx = Startx + 3 * 22;
			int Endy = Starty + 4 * 22;
			pItem->iPlaceX = Startx + ((Endx - Startx) - pItem->iWidth) / 2;
			pItem->iPlaceY = Starty + ((Endy - Starty) - pItem->iHeight) / 2;
			return TRUE;
		}
		break;
	case sinSR1:
		if (SocketItem[0].bValid)
		{
			if (GetEmptyArea(pItem))
			{
				pItem->iPlaceX = pItem->iPlaceX;
				pItem->iPlaceY = pItem->iPlaceY;
				return TRUE;
			}
		}
		break;
	}
	return FALSE;
}
int cSOCKET::GetEmptyArea(ItemData *pItem)
{
	int cntx, cnty;
	int cx, cy;

	RECT	rect;
	int		flag;
	int StartX = 218 + 11;
	int StartY = 193 + 19 + sinInterHeight2;

	cx = (22 * 2) - pItem->iWidth;
	cy = (22 * 2) - pItem->iHeight;

	for (cnty = StartY; cnty <= StartY + cy; cnty += 22)
	{
		for (cntx = StartX; cntx <= StartX + cx; cntx += 22)
		{
			flag = 0;
			for (int i = 1; i < 5; i++)
			{
				if (SocketItem[i].bValid)
				{
					rect.left	= SocketItem[i].iPlaceX;
					rect.right	= SocketItem[i].iPlaceX + SocketItem[i].iWidth;
					rect.top	= SocketItem[i].iPlaceY;
					rect.bottom = SocketItem[i].iPlaceY + SocketItem[i].iHeight;

					if (cntx > rect.left - pItem->iWidth &&
						cntx< rect.right &&
						cnty > rect.top - pItem->iHeight &&
						cnty < rect.bottom)
						flag++;
				}
			}
			if (flag == 0)
			{
				pItem->iPlaceX = cntx;
				pItem->iPlaceY = cnty;
				pItem->iItemSlot = 0;
				return TRUE;
			}
		}
	}

	return FALSE;
}
int cSOCKET::SendSocketItem()
{
	if (MixItemNoCopyFlag == FALSE)
	{
		memcpy(SocketItemBackUp, SocketItem, sizeof(ItemData)*MAX_SOCKET);
		MixItemNoCopyFlag = TRUE;
		ZeroMemory(&SocketItemServer, sizeof(SOCKET_ITEM_SERVER));

		if (SocketItem[0].bValid)
			SocketItemServer.DesItem = SocketItem[0];

		for (int i = 0; i < 4; i++)
		{
			SocketItemServer.SheltomCode[i] = SocketItem[i + 1].sBaseItemID.ToInt();
			SocketItemServer.CheckSum[i] = SocketItem[i + 1].sItem.iChk2;
			SocketItemServer.Head[i] = SocketItem[i + 1].sItem.iChk1;
		}
		CraftItemSendServerIndex++;

		SocketItemServer.Index = CraftItemSendServerIndex;
		SocketItemServer.Money = SocketItem[0].sItem.iSalePrice;

		SendSocketItemToServer(&SocketItemServer);

		CheckCharForm();
		sinMinusMoney(SocketItemServer.Money, 1);
		ReformSocketItem();
		SendSaveMoney();
	}
	return FALSE;
}
int cSOCKET::RecvSocketResult(SOCKET_ITEM_SERVER *pItemServer)
{
	CheckMixItemCopyFlag = FALSE;

	if (OpenFlag == FALSE)
	{
		MixItemNoCopyFlag = 0;
		MixCancelButtonDelayFlag = 0;
		ZeroMemory(SocketItem, sizeof(ItemData) * MAX_SOCKET);
		ZeroMemory(SocketItemBackUp, sizeof(ItemData) * MAX_SOCKET);
		ZeroMemory(&SocketItemServer, sizeof(SOCKET_ITEM_SERVER));
		return FALSE;
	}
	if (pItemServer->Result == TRUE)
	{
		if (cInvenTory.CheckRequireItemToSet(&pItemServer->DesItem))
		{
			if (!cInvenTory.AutoSetInvenItem(&pItemServer->DesItem, 1))
				sinThrowItemToFeild(&pItemServer->DesItem);
		}

		cMessageBox.ShowMessage(MESSAGE_OK_MIXTURE_RESET_ITEM);
		sinPlaySound(SIN_SOUND_EAT_POTION2);
	}
	else
	{
		sinPlaySound(SIN_SOUND_FAILD_MIXITEM);
		cMessageBox.ShowMessage(MESSAGE_FAIL_MIXTURE_RESET_ITEM);
	}

	for (int i = 0; i < 5; i++)
	{
		if (SocketItemBackUp[i].bValid)
			cInvenTory.DeleteInvenItemToServer(SocketItemBackUp[i].sItem.sItemID.ToInt(), SocketItemBackUp[i].sItem.iChk1, SocketItemBackUp[i].sItem.iChk2);
	}

	MixItemNoCopyFlag = 0;
	MixCancelButtonDelayFlag = 0;
	ZeroMemory(SocketItem, sizeof(ItemData) * MAX_SOCKET);
	ZeroMemory(SocketItemBackUp, sizeof(ItemData) * MAX_SOCKET);
	ZeroMemory(&SocketItemServer, sizeof(SOCKET_ITEM_SERVER));
	OpenFlag = FALSE;
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
cCARAVAN::cCARAVAN()
{
	SelectMode = TRUE;
	SelectTypeFlag = 1;
}
cCARAVAN::~cCARAVAN()
{

}
int cCARAVAN::SetSelectType(int Kind)
{
	if (Kind > 0)
		SelectTypeFlag = Kind;


	if (SelectTypeFlag > 7)
		SelectTypeFlag = 1;
	return TRUE;
}
int cCARAVAN::SetHopySelect(int Kind)
{
	if (SelectMode != Kind)
	{
		SendSelectHopyToServer(Kind);
		SelectMode = Kind;
		return TRUE;
	}
	return FALSE;
}
int cCARAVAN::CheckCaravanForm()
{
	int TempCheckDataSum = 0;
	for (int i = 0; i < 100; i++)
	{
		if (sCaravan.Item[i].bValid)
		{
			TempCheckDataSum += (i + 1)*sCaravan.Item[i].iPlaceX;
			TempCheckDataSum += (i + 1)*sCaravan.Item[i].iPlaceY;
			TempCheckDataSum += sCaravan.Item[i].sItem.iChk2;
			TempCheckDataSum += sCaravan.Item[i].sItem.iChk1;
		}
	}
	if (TempCheckDataSum != CaravanCheckSum)
		SendSetHackUser(11);

	return TRUE;
}
int cCARAVAN::ReFormCaravan()
{
	CaravanCheckSum = 0;
	for (int i = 0; i < 100; i++)
	{
		if (sCaravan.Item[i].bValid)
		{
			CaravanCheckSum += (i + 1)*sCaravan.Item[i].iPlaceX;
			CaravanCheckSum += (i + 1)*sCaravan.Item[i].iPlaceY;
			CaravanCheckSum += sCaravan.Item[i].sItem.iChk2;
			CaravanCheckSum += sCaravan.Item[i].sItem.iChk1;
		}
	}
	return TRUE;
}
int cCARAVAN::GetEmptyArea(ItemData *pItem)
{
	int cntx, cnty;
	int cx, cy;

	RECT	rect;
	int		flag;

	int StartX = 21;
	int StartY = 136 + sinInterHeight2;

	cx = (22 * 9) - pItem->iWidth;
	cy = (22 * 9) - pItem->iHeight;

	for (cnty = StartY; cnty <= StartY + cy; cnty += 22)
	{
		for (cntx = StartX; cntx <= StartX + cx; cntx += 22)
		{
			flag = 0;

			for (int i = 0; i < 100; i++)
			{
				if (sCaravan.Item[i].bValid)
				{
					rect.left	= sCaravan.Item[i].iPlaceX;
					rect.right	= sCaravan.Item[i].iPlaceX + sCaravan.Item[i].iWidth;
					rect.top	= sCaravan.Item[i].iPlaceY;
					rect.bottom = sCaravan.Item[i].iPlaceY + sCaravan.Item[i].iHeight;

					if (cntx > rect.left - pItem->iWidth &&
						cntx < rect.right &&
						cnty > rect.top - pItem->iHeight &&
						cnty < rect.bottom)
						flag++;
				}
			}
			if (flag == 0)
			{
				pItem->iPlaceX = cntx;
				pItem->iPlaceY = cnty;
				return TRUE;
			}
		}
	}
	return FALSE;
}
int cCARAVAN::CheckCopyItem()
{
	int i, j;
	if (SendServerFlag7)
		return FALSE;
	for (i = 0; i < 100; i++)
	{
		if (sCaravan.Item[i].bValid)
		{
			for (j = 0; j < 100; j++)
			{
				if (i != j && sCaravan.Item[j].bValid)
				{
					if (CompareItems(&sCaravan.Item[i].sItem, &sCaravan.Item[j].sItem))
					{
						SendSetHackUser2(1010, sCaravan.Item[i].sBaseItemID.ToInt());
						SendServerFlag7 = TRUE;
						break;
					}
				}
			}
		}
	}
	return TRUE;
}
int cCARAVAN::DeleteCopyItem()
{
	int i, j;
	for (i = 0; i < 100; i++)
	{
		if (sCaravan.Item[i].bValid)
		{
			for (j = 0; j < 100; j++)
			{
				if (i != j && sCaravan.Item[j].bValid)
				{
					if (CompareItems(&sCaravan.Item[i].sItem, &sCaravan.Item[j].sItem))
					{
						sCaravan.Item[j].bValid = 0;
						ReFormCaravan();
						break;
					}
				}
			}
		}
	}
	return TRUE;
}
int cCARAVAN::CloseCaravan()
{
	int RestoreFlag = 1;

	OpenFlag = FALSE;

	if (SaveFlag == TRUE)
	{
		if (!SaveCaravan(&sCaravan, NULL))
		{
			RestoreInvenItem();
			cMessageBox.ShowMessage(MESSAGE_OVER_ITEM_NUM);
			RestoreFlag = 0;
		}
		else
		{
			DELET(BackUpInvenItem2);
			DELET(BackUpInvenTempItem2);
			DELET(BackUpsInven);
		}
	}
	SaveFlag = FALSE;
	ResetInvenItemCode();

	return RestoreFlag;
}
int cCARAVAN::RestoreInvenItem()
{
	sinSetCharItem(cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt(), cInvenTory.InvenItem[sInven[0].ItemIndex - 1].iVisibleItemType, FALSE);
	sinSetCharItem(cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sBaseItemID.ToInt(), cInvenTory.InvenItem[sInven[1].ItemIndex - 1].iVisibleItemType, FALSE);
	if (sinChar->CostmePos == TRUE)
		sinSetCharItem(cInvenTory.InvenItem[sInven[13].ItemIndex - 1].sBaseItemID.ToInt(), cInvenTory.InvenItem[sInven[13].ItemIndex - 1].iVisibleItemType, FALSE);
	else
		sinSetCharItem(cInvenTory.InvenItem[sInven[2].ItemIndex - 1].sBaseItemID.ToInt(), cInvenTory.InvenItem[sInven[2].ItemIndex - 1].iVisibleItemType, FALSE);

	memcpy(&cInvenTory.InvenItem, BackUpInvenItem2, sizeof(ItemData) * 100);
	memcpy(&cInvenTory.InvenItemTemp, BackUpInvenTempItem2, sizeof(ItemData) * 100);
	memcpy(&sInven, BackUpsInven, sizeof(sINVENTORY)*INVENTORY_MAX_POS);

	if (MouseItem.bValid)
		MouseItem.bValid = 0;

	DELET(BackUpInvenItem2);
	DELET(BackUpInvenTempItem2);
	DELET(BackUpsInven);

	if (sInven[0].ItemIndex)
		sinSetCharItem(cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt(),
			cInvenTory.InvenItem[sInven[0].ItemIndex - 1].iVisibleItemType, TRUE);
	if (sInven[1].ItemIndex)
		sinSetCharItem(cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sBaseItemID.ToInt(),
			cInvenTory.InvenItem[sInven[1].ItemIndex - 1].iVisibleItemType, TRUE);
	if (sinChar->CostmePos == TRUE)
	{
		if (sInven[13].ItemIndex)
			sinSetCharItem(cInvenTory.InvenItem[sInven[13].ItemIndex - 1].sBaseItemID.ToInt(),
				cInvenTory.InvenItem[sInven[13].ItemIndex - 1].iVisibleItemType, TRUE);
	}
	else
	{
		if (sInven[2].ItemIndex)
			sinSetCharItem(cInvenTory.InvenItem[sInven[2].ItemIndex - 1].sBaseItemID.ToInt(),
				cInvenTory.InvenItem[sInven[2].ItemIndex - 1].iVisibleItemType, TRUE);
	}

	cInvenTory.SetItemToChar();
	cInvenTory.ReFormInvenItem();
	cInvenTory.CheckWeight();

	return TRUE;
}
int cCARAVAN::BackUpInvenItem()
{
	BackUpInvenItem2 = new ItemData[100];
	BackUpInvenTempItem2 = new ItemData[100];
	BackUpsInven = new sINVENTORY[INVENTORY_MAX_POS];

	memcpy(BackUpInvenItem2, &cInvenTory.InvenItem, sizeof(ItemData) * 100);
	memcpy(BackUpInvenTempItem2, &cInvenTory.InvenItemTemp, sizeof(ItemData) * 100);
	memcpy(BackUpsInven, &sInven, sizeof(sINVENTORY)*INVENTORY_MAX_POS);

	return TRUE;
}
int cCARAVAN::SetCaravanItemAreaCheck(ItemData *pItem)
{
	int i, j;
	TradeColorIndex = 0;
	TradeCrashItemIndex[0] = 0;
	cTrade.InitTradeColorRect();

	TradeStartX = 21;
	TradeStartY = 136 + sinInterHeight2;
	TradeEndX = TradeStartX + (22 * 9);
	TradeEndY = TradeStartY + (22 * 9);

	for (i = pItem->iPlaceX + 11; i < pItem->iPlaceX + pItem->iWidth; i += 22)
	{
		for (j = pItem->iPlaceY + 11; j < pItem->iPlaceY + pItem->iHeight; j += 22)
		{
			if (TradeStartX <= i && TradeEndX > i && TradeStartY <= j && TradeEndY > j)
			{
				TradeColorRect.left = TradeStartX + (((i - TradeStartX) / 22) * 22);
				TradeColorRect.top = TradeStartY + (((j - TradeStartY) / 22) * 22);
				TradeColorRect.right = pItem->iWidth;
				TradeColorRect.bottom = pItem->iHeight;

				if (TradeEndX < (TradeColorRect.left + TradeColorRect.right) - 11 || TradeEndY < (TradeColorRect.top + TradeColorRect.bottom) - 11)
				{
					cTrade.InitTradeColorRect();
					return FALSE;
				}
				if (pItem->sItem.eCraftType == ITEMCRAFTTYPE_Quest ||
					(pItem->sItem.sItemID.ToItemType()) == sinMA1 ||
					(pItem->sItem.sItemID.ToItemType()) == sinMA2 ||
					(pItem->sItem.sItemID.ToItemType()) == sinQW1 ||
					(pItem->sItem.sItemID.ToItemType()) == sinQT1 ||
					pItem->sItem.sItemID.ToInt() == (sinGF1 | sin01))
				{
					TradeColorIndex = NOT_SETTING_COLOR;
					return FALSE;
				}
				if (pItem->sItem.eCraftType == ITEMCRAFTTYPE_Event)
				{
					TradeColorIndex = NOT_SETTING_COLOR;
					return FALSE;
				}
				if ((pItem->sItem.sItemID.ToItemType()) == sinCH1)
				{
					TradeColorIndex = NOT_SETTING_COLOR;
					return FALSE;
				}

				pItem->iPlaceX = TradeColorRect.left;
				pItem->iPlaceY = TradeColorRect.top;
				pItem->iItemSlot = 0;
				TradeColorIndex = SET_ITEM_CHECK_COLOR;

				if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 8))
				{
					if (!CopyItemNotPickUp(&sCaravan.Item[TradeCrashItemIndex[0] - 1], TradeCrashItemIndex[0] - 1))
					{
						TradeColorIndex = NOT_SETTING_COLOR;
						TradeCrashItemIndex[0] = 0;
						TradeCrashItemIndex[1] = 0;
						return FALSE;
					}
					if (TradeCrashItemIndex[1] = cTrade.CrashTradeItem(TradeColorRect, TradeCrashItemIndex[0], 8))
					{
						TradeColorIndex = NOT_SETTING_COLOR;
						TradeCrashItemIndex[1] = 0;
						return FALSE;
					}
					TradeColorIndex = OVERLAP_ITEM_COLOR;
				}
				return TRUE;
			}
		}
	}
	return TRUE;
}
int cCARAVAN::SetCaravanItem(ItemData *pItem)
{
	if (pItem->sItem.eCraftType == ITEMCRAFTTYPE_Quest ||
		(pItem->sItem.sItemID.ToItemType()) == sinMA1 ||
		(pItem->sItem.sItemID.ToItemType()) == sinMA2 ||
		(pItem->sItem.sItemID.ToItemType()) == sinQW1 ||
		(pItem->sItem.sItemID.ToItemType()) == sinQT1 ||
		pItem->sItem.sItemID.ToInt() == (sinGF1 | sin01))
		return FALSE;
	if (pItem->sItem.eCraftType == ITEMCRAFTTYPE_Event)
		return FALSE;
	if ((pItem->sItem.sItemID.ToItemType()) == sinCH1)
		return FALSE;
	for (int i = 0; i < 100; i++)
	{
		if (CopyItemNotPickUp(&sCaravan.Item[i], i) == FALSE)
			return FALSE;
	}
	if (GetEmptyArea(pItem))
	{
		pItem->iPlaceX = pItem->iPlaceX;
		pItem->iPlaceY = pItem->iPlaceY;
		return TRUE;
	}
	return FALSE;
}
int cCARAVAN::LoadCaravanItemIamge()
{
	char szFilePath[256];

	int  cnt = 0;

	for (int i = 0; i < 100; i++)
	{
		if (sCaravan.Item[i].bValid)
		{
			ItemData * pItemData = ITEMHANDLE->GetItemDataByID(sCaravan.Item[i].sItem.sItemID.ToInt());

			if (pItemData)
			{
				sCaravan.Item[i].iWidth = pItemData->iWidth;
				sCaravan.Item[i].iHeight = pItemData->iHeight;

				wsprintf(szFilePath, "Image\\sinImage\\Items\\%s\\it%s.bmp", pItemData->szCategory, pItemData->szInventoryName);

				if (!pItemData->pcTempInventoryTexture)
					pItemData->pcTempInventoryTexture = LoadDibSurfaceOffscreen(szFilePath);

				sCaravan.Item[i].pcInventoryTexture = pItemData->pcTempInventoryTexture;
			}
		}
	}
	cInterFace.CheckAllBox(SIN_CARAVAN);

	return TRUE;
}
int cCARAVAN::CopyItemNotPickUp(ItemData *pItem, int Jumpindex)
{
	if (SETTINGHANDLE->Get().bDebugMode)
		return TRUE;
	for (int i = 0; i < 100; i++)
	{
		if (sCaravan.Item[i].bValid)
		{
			if (Jumpindex == i)
				continue;
			if (CompareItems(&pItem->sItem, &sCaravan.Item[i].sItem))
			{
				CopyItemIndex8[i] = i + 1;
				return FALSE;
			}
		}
	}

	return TRUE;
}
int cCARAVAN::LastSetCaravanItem(ItemData *pItem)
{
	CheckCaravanForm();
	for (int j = 0; j < 100; j++)
	{
		if (!sCaravan.Item[j].bValid)
		{
			memcpy(&sCaravan.Item[j], pItem, sizeof(ItemData));
			sCaravan.Item[j].iPlaceX = pItem->iPlaceX;
			sCaravan.Item[j].iPlaceY = pItem->iPlaceY;
			pItem->bValid = 0;
			sinPlaySound(sCaravan.Item[j].iInvItemSound);
			SaveFlag = TRUE;
			ReFormCaravan();
			return TRUE;
		}
	}
	ReFormCaravan();
	return FALSE;
}
int cCARAVAN::ChangeCaravanItem(ItemData *pItem)
{
	if (pItem->iItemSlotFlag == ITEMSLOTFLAG_Potion)
	{
		cMessageBox.ShowMessage(MESSAGE_POTION_NOT_SETTING);
		return TRUE;
	}
	CheckCaravanForm();
	if (TradeCrashItemIndex[0])
	{
		if (sCaravan.Item[TradeCrashItemIndex[0] - 1].iItemSlotFlag == ITEMSLOTFLAG_Potion)
		{
			if (sCaravan.Item[TradeCrashItemIndex[0] - 1].sBaseItemID.ToInt() == pItem->sBaseItemID.ToInt())
			{
				sCaravan.Item[TradeCrashItemIndex[0] - 1].sItem.iPotionCount += pItem->sItem.iPotionCount;
				pItem->bValid = FALSE;
				SaveFlag = TRUE;
				ReFormCaravan();
				return TRUE;
			}
		}
		memcpy(&TempItem, &sCaravan.Item[TradeCrashItemIndex[0] - 1], sizeof(ItemData));
		sCaravan.Item[TradeCrashItemIndex[0] - 1].bValid = 0;
		TempItem.iPlaceX = pItem->iPlaceX;
		TempItem.iPlaceY = pItem->iPlaceY;
		ReFormCaravan();
		LastSetCaravanItem(pItem);
		memcpy(pItem, &TempItem, sizeof(ItemData));
		SaveFlag = TRUE;
		ReFormCaravan();
		return TRUE;
	}
	ReFormCaravan();
	return FALSE;
}
int cCARAVAN::PickUpCaravanItem(int x, int y, int PickUpFlag)
{
	int i = 0;
	SelectTradeItemIndex = 0;

	for (i = 0; i < 100; i++)
	{
		if (sCaravan.Item[i].bValid)
		{
			if (sCaravan.Item[i].iPlaceX < x  &&
				sCaravan.Item[i].iPlaceX + sCaravan.Item[i].iWidth > x  &&
				sCaravan.Item[i].iPlaceY < y  &&
				sCaravan.Item[i].iPlaceY + sCaravan.Item[i].iHeight > y)
			{
				switch (PickUpFlag)
				{
				case 1:
				{
					ItemData TempItem;

					TempItem.iWidth = ITEMSIZE * 2;
					TempItem.iHeight = ITEMSIZE * 4;
					TempItem.bValid = 1;

					if (cInvenTory.CheckSetEmptyArea(&TempItem))
					{
						if (CopyItemNotPickUp(&sCaravan.Item[i], i))
						{
							CheckCaravanForm();
							memcpy(&MouseItem, &sCaravan.Item[i], sizeof(ItemData));
							sCaravan.Item[i].bValid = FALSE;
							sinPlaySound(sCaravan.Item[i].iInvItemSound);
							TradeColorIndex = 0;
							SaveFlag = TRUE;
							ReFormCaravan();
							return TRUE;
						}
					}
					else
					{
						cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
						return FALSE;
					}
					if (CopyItemNotPickUp(&sCaravan.Item[i], i))
					{
						CheckCaravanForm();
						memcpy(&MouseItem, &sCaravan.Item[i], sizeof(ItemData));
						sCaravan.Item[i].bValid = 0;
						sinPlaySound(sCaravan.Item[i].iInvItemSound);
						TradeColorIndex = 0;
						SaveFlag = TRUE;
						ReFormCaravan();
						return TRUE;
					}
				}
					
					break;
				case 2:
					if (CopyItemNotPickUp(&sCaravan.Item[i], i))
					{
						if (cCraftItem.CraftCheckEmptyArea(&sCaravan.Item[i]))
						{
							CheckCaravanForm();
							if (!cInvenTory.AutoSetInvenItem(&sCaravan.Item[i]))
							{
								sinThrowItemToFeild(&sCaravan.Item[i]);
								sCaravan.Item[i].bValid = FALSE;
							}
							TradeColorIndex = 0;
							SaveFlag = TRUE;
							ReFormCaravan();
							return TRUE;
						}
						else
						{
							cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
							return FALSE;
						}
					}
					break;
				default:
					SelectTradeItemIndex = i + 1;
					TradeColorIndex = SELECT_ITEM_COLOR;
					sinShowItemInfoFlag = 1;
					cItem.ShowItemInfo(&sCaravan.Item[i], 2);
					break;
				}
			}
		}
	}
	return FALSE;
}