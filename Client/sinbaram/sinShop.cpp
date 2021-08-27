#include "StdAfx.h"
#include "..\\tjboy\\clanmenu\\tjclan.h"
#include "..\\tjboy\\clanmenu\\clan_Enti.h"
#include "..\\CurseFilter.h"

cSHOP		cShop;
cMYSHOP		cMyShop;
cCHARSHOP	cCharShop;
sMYSHOP     sMyShop;
sMYSHOP     sRecvMyShop;
sMYSHOP_ITEM_SERVER sMyShop_Server;

Item   MyShopPotion;

int CloseMyShopFlag = 0;
int CloseCharShopFlag = 0;
int SelectShopButtonPosi = 0;
int MyShopItemIndex[100] = { 0, };


int sinShopKind = 1;

int ShopArrowPosi = 0;

RECT ShopItemRect = { 0,0,0,0 };

int	GridRow, GridCol, StartGirdX, StartGirdY;

int ShopItemPrice = 0;
int ShowShopItemIndex = 0;

int TalkNpcState = 0;

int haCharShopDelayFlag = 0;


int ReStartButtonRect2[3][4] =
{
	{21,22,21 + 44,22 + 44},
	{72,22,72 + 44,22 + 44},
	{123,22,123 + 44,22 + 44},

};

int ShopButtonPosi[9][4] =
{
	{269,278 + sinInterHeight2,269 + 28,278 + 28 + sinInterHeight2},
	{238,278 + sinInterHeight2,238 + 28,278 + 28 + sinInterHeight2},
	{238,309 + sinInterHeight2,238 + 28,309 + 28 + sinInterHeight2},
	{269,309 + sinInterHeight2,269 + 28,309 + 28 + sinInterHeight2},
	{279,182 + sinInterHeight2,279 + 20,182 + 20 + sinInterHeight2},
	{257,182 + sinInterHeight2,257 + 20,182 + 20 + sinInterHeight2},
	{304,314 + sinInterHeight2,304 + 20,314 + 20 + sinInterHeight2},
	{231,136 + sinInterHeight2,231 + 42,136 + 46 + sinInterHeight2},
	{281,136 + sinInterHeight2,281 + 42,136 + 46 + sinInterHeight2},

};

int ShopGoldEdit[2][4] =
{
	{231,213 + 5 + sinInterHeight2,231 + 120,213 + 5 + 24 + sinInterHeight2},
	{231,243 + 5 + sinInterHeight2,231 + 120,243 + 5 + 24 + sinInterHeight2},
};


int ShowShopItemIndex2 = 0;

int BuyItemServerFlag = 0;
int BuyItemIndexCopy = 0;

int SelectMyShopButtonPosi = 0;
int SelectMyShopItemIndex = 0;

int MyShopSendButton = 0;
int MyShopExpBox = 0;
int MyShopExpButtonOK = 0;
int MyShopExpButtonCancel = 0;

int SelectCharShopButtonPosi = 0;

int MyShopExpBoxX = 250;
int MyShopExpBoxY = 100;

int MyShopItemCancelIndex[2] = { 0,0 };

cSHOP::cSHOP()
{

}
cSHOP::~cSHOP()
{

}
void cSHOP::Init()
{
	Load();

	MatMyShop_Button = CreateTextureMaterial("Image\\SinImage\\Shopall\\MyShopButton.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

}
void cSHOP::Load()
{

	lpShopMain = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\shop-1.bmp");
	lpShopMain2 = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\shop-2.bmp");

	lpGoldEdit = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\my_money.bmp");

	lpAllRepair = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\AllRepair.bmp");
	lpRepair = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\Repair.bmp");

	lpSell = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\Sell.bmp");
	lpBuy = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\Buy.bmp");

	lpAllRepair_D = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\DefaultAllRepair.bmp");
	lpRepair_D = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\DefaultRepair.bmp");

	lpSell_D = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\Sell0.bmp");
	lpBuy_D = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\Buy0.bmp");

	lpArrow[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\RightArrow.bmp");
	lpArrow[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\LeftArrow.bmp");
	lpArrow[2] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inven\\RightArrow.bmp");
	lpArrow[3] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inven\\LeftArrow.bmp");

	lpTabAttack = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\TabAttack.bmp");
	lpTabDefense = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\TabDefense.bmp");
	lpTabEtc = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\TabEtc.bmp");

	lpTabAttack_D = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\TabAttack0.bmp");
	lpTabDefense_D = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\TabDefense0.bmp");
	lpTabEtc_D = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\TabEtc.bmp");

	lpExit = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\ButtonExit.bmp");
	lpGrid = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\Grid.bmp");

	lpRepairAllInfo = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\ButtonInfo\\RepairAllInfo.bmp");
	lpRepairInfo = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\ButtonInfo\\RepairInfo.bmp");
	lpSellInfo = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\ButtonInfo\\SellInfo.bmp");
	lpBuyInfo = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\ButtonInfo\\BuyInfo.bmp");

	lpDefaultRepairAll = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\DefaultAllRepair.bmp");
	lpDefaultRepair = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\DefaultRepair.bmp");

	lpTitle_Attack = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\title-shop.bmp");
	lpTitle_Etc = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\title-TabEtc.bmp");
	lpTitle_Trade = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\Trade.bmp");
	lpTitle_WareHouse = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\Warehouse.bmp");

	lpWeightEdit = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\weight.bmp");
	lpNoUseBox = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\NoUseBox.bmp");

	lpCraftItemMain = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\CraftItem\\CraftItemMain.bmp");
	lpCraftItemButton = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\CraftItem\\Button.bmp");
	lpCraftItemButtonInfo = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\CraftItem\\ButtonInfo.bmp");
	lpTitle_CraftItem = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\CraftItem\\Title.bmp");
	lpTitle_Aging = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\Aging\\Aging_Title.bmp");
	lpAging_Info = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\Aging\\ButtonInfo.bmp");

	lpSmeltingItemMain = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\SmeltingItem\\SmeltingMain.bmp");
	lpTitle_SmeltingItem = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\SmeltingItem\\SmeltingTitle.bmp");
	lpSmeltingItemButtonInfo = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\SmeltingItem\\ButtonInfo.bmp");

	lpManufactureItemMain = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\Manufacture\\ManufactureMain.bmp");
	lpTitle_ManufactureItem = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\Manufacture\\ManufactureTitle.bmp");
	lpManufactureItemButtonInfo = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\Manufacture\\ButtonInfo.bmp");

	lpMResetTitle = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\CraftItem\\MResetTitle.bmp");
	lpMResetMain = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\CraftItem\\MResetMain.bmp");
	lpMResetButton = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\CraftItem\\MResetButton.bmp");
	lpMResetButtonInfo = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\CraftItem\\MResetButtonInfo.bmp");

	lpElementTitle = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\Element\\ElementTitle.bmp");
	lpElementMain = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\Element\\ElementMain.bmp");
	lpElementButton = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\Element\\Ebutton.bmp");
	lpElementButtonInfo = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\Element\\EbuttonInfo.bmp");

	lpSocketTitle = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\Socket\\SocketTitle.bmp");
	lpSocketMain = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\Socket\\SocketMain.bmp");
	lpSocketButton = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\Socket\\Sbutton.bmp");
	lpSocketButtonInfo = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\Socket\\SbuttonInfo.bmp");

	lpCaravanMain[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\CaravanHopy\\window.bmp");
	lpCaravanMain[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\CaravanHopy\\window_arma.bmp");
	lpCaravanMain[2] = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\CaravanHopy\\window_buma.bmp");
	lpCaravanMain[3] = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\CaravanHopy\\window_cuepy.bmp");
	lpCaravanMain[4] = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\CaravanHopy\\window_hungky.bmp");
	lpCaravanMain[5] = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\CaravanHopy\\window_rabie.bmp");
	lpCaravanMain[6] = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\CaravanHopy\\window_tobie.bmp");
	lpCaravanStart[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\CaravanHopy\\Start.png");
	lpCaravanStart[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\CaravanHopy\\Start_.png");
	lpCaravanStop[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\CaravanHopy\\Stop.png");
	lpCaravanStop[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\CaravanHopy\\Stop_.png");
	lpCaravanRename[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\CaravanHopy\\Rename.png");
	lpCaravanRename[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\Shopall\\CaravanHopy\\Rename_.png");

	lpMyShopExp = LoadDibSurfaceOffscreen("Image\\SinImage\\indishop\\indishop_exp.bmp");
	lpMyShopExp_ = LoadDibSurfaceOffscreen("Image\\SinImage\\indishop\\indishop_exp_.bmp");
	lpMyShopExp_T = LoadDibSurfaceOffscreen("Image\\SinImage\\indishop\\indishop_expT.bmp");
	lpMyShopNoSale = LoadDibSurfaceOffscreen("Image\\SinImage\\indishop\\indishop_nosale.bmp");
	lpMyShopNoSale_ = LoadDibSurfaceOffscreen("Image\\SinImage\\indishop\\indishop_nosale_.bmp");
	lpMyShopNoSale_T = LoadDibSurfaceOffscreen("Image\\SinImage\\indishop\\indishop_nosaleT.bmp");
	lpMyShopSale = LoadDibSurfaceOffscreen("Image\\SinImage\\indishop\\indishop_sale.bmp");
	lpMyShopSale_ = LoadDibSurfaceOffscreen("Image\\SinImage\\indishop\\indishop_sale_.bmp");
	lpMyShopSale_T = LoadDibSurfaceOffscreen("Image\\SinImage\\indishop\\indishop_saleT.bmp");
	lpTitle_MyShop = LoadDibSurfaceOffscreen("Image\\SinImage\\indishop\\indishop_title.bmp");
	lpImage_MyShop = LoadDibSurfaceOffscreen("Image\\SinImage\\indishop\\indishop_image.bmp");
	lpMyShop_T = LoadDibSurfaceOffscreen("Image\\SinImage\\indishop\\indishop_T.bmp");
}
void cSHOP::Release()
{
	DELET(lpAllRepair);
	DELET(lpRepair);
	DELET(lpSell);
	DELET(lpBuy);
	DELET(lpAllRepair_D);
	DELET(lpRepair_D);
	DELET(lpSell_D);
	DELET(lpBuy_D);
	DELET(lpArrow[0]);
	DELET(lpArrow[1]);
	DELET(lpArrow[2]);
	DELET(lpArrow[3]);
	DELET(lpTabAttack);
	DELET(lpTabDefense);
	DELET(lpTabEtc);
	DELET(lpTabAttack_D);
	DELET(lpTabDefense_D);
	DELET(lpTabEtc_D);
	DELET(lpExit);
	DELET(lpGrid);
	DELET(lpRepairAllInfo);
	DELET(lpRepairInfo);
	DELET(lpSellInfo);
	DELET(lpBuyInfo);
	DELET(lpDefaultRepairAll);
	DELET(lpDefaultRepair);
	DELET(lpTitle_Attack);
	DELET(lpTitle_Etc);
	DELET(lpTitle_Trade);
	DELET(lpTitle_WareHouse);
	DELET(lpCraftItemMain);
	DELET(lpCraftItemButton);
	DELET(lpCraftItemButtonInfo);
	DELET(lpTitle_CraftItem);
	DELET(lpSmeltingItemMain);
	DELET(lpTitle_SmeltingItem);
	DELET(lpTitle_Aging);
	DELET(lpAging_Info);
	DELET(lpSmeltingItemButtonInfo);
	DELET(lpManufactureItemMain);
	DELET(lpTitle_ManufactureItem);
	DELET(lpManufactureItemButtonInfo);
	DELET(lpMResetTitle);
	DELET(lpMResetMain);
	DELET(lpMResetButton);
	DELET(lpMResetButtonInfo);
	DELET(lpElementTitle);
	DELET(lpElementMain);
	DELET(lpElementButton);
	DELET(lpElementButtonInfo);
	DELET(lpSocketTitle);
	DELET(lpSocketMain);
	DELET(lpSocketButton);
	DELET(lpSocketButtonInfo);
	for (int i = 0; i < 7; i++)
		DELET(lpCaravanMain[i]);
	for (int i = 0; i < 2; i++)
	{
		DELET(lpCaravanStart[i]);
		DELET(lpCaravanStop[i]);
		DELET(lpCaravanRename[i]);
	}
}
void cSHOP::Draw()
{
	if (ReStartFlag)
	{
		DrawSprite(ReStartMainXY.x, ReStartMainXY.y, cInterFace.lpReStartMain, 0, 0, 188, 128);
		if (ReStartIndex && RestartCheckExp)
		{
			if (ReStartIndex != 1)
				DrawSprite(ReStartMainXY.x + ReStartButtonRect2[ReStartIndex - 1][0], ReStartMainXY.y + ReStartButtonRect2[ReStartIndex - 1][1], cInterFace.lpReStartButton[ReStartIndex - 1], 0, 0, 44, 44);
		}
		if (ReStartIndex == 1 && !RestartCheckExp)
			DrawSprite(ReStartMainXY.x + ReStartButtonRect2[ReStartIndex - 1][0], ReStartMainXY.y + ReStartButtonRect2[ReStartIndex - 1][1], cInterFace.lpReStartButton[ReStartIndex - 1], 0, 0, 44, 44);
	}

	int i = 0, j = 0;

	DrawSprite(0 - (256 + 128 - sinMoveKindInter[SIN_MYSHOP]), 90 + sinInterHeight2, cShop.lpShopMain2, 0, 0, 344, 264);

	DrawSprite(0 - (256 + 128 - sinMoveKindInter[SIN_CHARSHOP]), 90 + sinInterHeight2, cShop.lpShopMain2, 0, 0, 344, 264);

	DrawSprite(0 - (256 + 128 - sinMoveKindInter[SIN_SHOP]), 90 + sinInterHeight2, lpShopMain, 0, 0, 344, 264);

	if (sinShopKind == SIN_WEAPON || sinShopKind == SIN_DEFENSE)
	{
		DrawSprite(239 - (256 + 128 - sinMoveKindInter[SIN_SHOP]), 87, lpTabAttack_D, 0, 0, 41, 45);
		DrawSprite(280 - (256 + 128 - sinMoveKindInter[SIN_SHOP]), 87, lpTabDefense_D, 0, 0, 41, 45);
		DrawSprite(ShopButtonPosi[SINALLREPAIR - 1][0] - (256 + 128 - sinMoveKindInter[SIN_SHOP]), ShopButtonPosi[SINALLREPAIR - 1][1], lpAllRepair_D, 0, 0, 28, 28);
		DrawSprite(ShopButtonPosi[SINREPAIR - 1][0] - (256 + 128 - sinMoveKindInter[SIN_SHOP]), ShopButtonPosi[SINREPAIR - 1][1], lpRepair_D, 0, 0, 28, 28);

		DrawSprite(225 - (256 + 128 - sinMoveKindInter[SIN_SHOP]), 47, lpTitle_Attack, 0, 0, 111, 32);

		if (sinShopKind == SIN_WEAPON)
			DrawSprite(239 - (256 + 128 - sinMoveKindInter[SIN_SHOP]), 87, lpTabAttack, 0, 0, 41, 45);
		if (sinShopKind == SIN_DEFENSE)
			DrawSprite(280 - (256 + 128 - sinMoveKindInter[SIN_SHOP]), 87, lpTabDefense, 0, 0, 41, 45);
	}

	if (sinShopKind == SIN_ETC)
	{
		DrawSprite(232 - (256 + 128 - sinMoveKindInter[SIN_SHOP]), 93, lpTabEtc_D, 0, 0, 98, 40);
		DrawSprite(225 - (256 + 128 - sinMoveKindInter[SIN_SHOP]), 47, lpTitle_Etc, 0, 0, 111, 32);
	}
	DrawSprite(ShopButtonPosi[SINSELL - 1][0] - (256 + 128 - sinMoveKindInter[SIN_SHOP]), ShopButtonPosi[SINSELL - 1][1], lpSell_D, 0, 0, 28, 28);
	DrawSprite(ShopButtonPosi[SINBUY - 1][0] - (256 + 128 - sinMoveKindInter[SIN_SHOP]), ShopButtonPosi[SINBUY - 1][1], lpBuy_D, 0, 0, 28, 28);

	DrawSprite(231 - (256 + 128 - sinMoveKindInter[SIN_SHOP]), 243 + sinInterHeight2, lpGoldEdit, 0, 0, 99, 24);

	DrawSprite(282 - (256 + 128 - sinMoveKindInter[SIN_SHOP]), 182 + sinInterHeight2, lpArrow[0], 0, 0, 20, 20);
	DrawSprite(260 - (256 + 128 - sinMoveKindInter[SIN_SHOP]), 182 + sinInterHeight2, lpArrow[1], 0, 0, 20, 20);

	if (ShopArrowPosi == 0 || ShopArrowPosi == 3)
		DrawSprite(260 - (256 + 128 - sinMoveKindInter[SIN_SHOP]), 132, cInvenTory.lpInvenArrow[0], 0, 0, 20, 20);
	if (ShopArrowPosi == 1 || ShopArrowPosi == 4)
		DrawSprite(282 - (256 + 128 - sinMoveKindInter[SIN_SHOP]), 132, cInvenTory.lpInvenArrow[1], 0, 0, 20, 20);

	DrawSprite(ShopButtonPosi[SINALLREPAIR - 1][0] - (256 + 128 - sinMoveKindInter[SIN_MYSHOP]), ShopButtonPosi[SINALLREPAIR - 1][1], lpMyShopNoSale_, 0, 0, 28, 28);
	DrawSprite(ShopButtonPosi[SINREPAIR - 1][0] - (256 + 128 - sinMoveKindInter[SIN_MYSHOP]), ShopButtonPosi[SINREPAIR - 1][1], lpMyShopSale_, 0, 0, 28, 28);

	DrawSprite(238 - (256 + 128 - sinMoveKindInter[SIN_MYSHOP]), 90, lpImage_MyShop, 0, 0, 53, 59);
	DrawSprite(225 - (256 + 128 - sinMoveKindInter[SIN_MYSHOP]), 47, lpTitle_MyShop, 0, 0, 111, 32);

	DrawSprite(ShopButtonPosi[SINBUY - 1][0] - (256 + 128 - sinMoveKindInter[SIN_CHARSHOP]), ShopButtonPosi[SINBUY - 1][1], lpBuy_D, 0, 0, 28, 28);
	DrawSprite(238 - (256 + 128 - sinMoveKindInter[SIN_CHARSHOP]), 90, lpImage_MyShop, 0, 0, 53, 59);
	DrawSprite(225 - (256 + 128 - sinMoveKindInter[SIN_CHARSHOP]), 47, lpTitle_MyShop, 0, 0, 111, 32);

	char strBuff[128];
	memset(strBuff, 0, sizeof(strBuff));

	DWORD Color = D3DCOLOR_XRGB(255, 255, 255);

	int Money2 = 0;

	int len3 = 0;

	if (cMyShop.OpenFlag)
	{
		for (int i = 0; i < 30; i++)
		{
			if (cMyShop.MyShopItem[i].bValid)
			{
				if (cMyShop.MyShopItem[i].iItemSlotFlag == ITEMSLOTFLAG_Potion)
					Money2 += cMyShop.MyShopItem[i].sItem.iGold * cMyShop.MyShopItem[i].sItem.iPotionCount;
				else
					Money2 += cMyShop.MyShopItem[i].sItem.iGold;
			}
		}

		NumLineComa(cMyShop.GetLimitMoney(Money2), strBuff);
		len3 = lstrlen(strBuff);
		dsTextLineOut(0, CheckEditSize(ShopGoldEdit[1][0], ShopGoldEdit[1][2], strBuff) - (256 + 128 - sinMoveKindInter[SIN_MYSHOP]) - (len3 / 2), ShopGoldEdit[1][1], strBuff, lstrlen(strBuff), Color);

		memset(strBuff, 0, sizeof(strBuff));
		NumLineComa(Money2, strBuff);
		len3 = lstrlen(strBuff);
		dsTextLineOut(0, CheckEditSize(ShopGoldEdit[0][0], ShopGoldEdit[0][2], strBuff) - (256 + 128 - sinMoveKindInter[SIN_MYSHOP]) - (len3 / 2), ShopGoldEdit[0][1], strBuff, lstrlen(strBuff), Color);

	}
	if (cCharShop.OpenFlag)
	{
		memset(strBuff, 0, sizeof(strBuff));
		NumLineComa(sinChar->iGold, strBuff);
		len3 = lstrlen(strBuff);
		dsTextLineOut(0, CheckEditSize(ShopGoldEdit[1][0], ShopGoldEdit[1][2], strBuff) - (256 + 128 - sinMoveKindInter[SIN_MYSHOP]) - (len3 / 2), ShopGoldEdit[1][1], strBuff, lstrlen(strBuff), Color);
	}

	switch (SelectCharShopButtonPosi)
	{
	case 4:
		DrawSprite(ShopButtonPosi[SINBUY - 1][0] - (256 + 128 - sinMoveKindInter[SIN_CHARSHOP]), ShopButtonPosi[SINBUY - 1][1], lpBuy, 0, 0, 28, 28);
		DrawSprite(ShopButtonPosi[SINBUY - 1][0] - 26 - (256 + 128 - sinMoveKindInter[SIN_CHARSHOP]), ShopButtonPosi[SINBUY - 1][1] - 27, lpBuyInfo, 0, 0, 77, 27);
		break;
	case SINSHOPEXIT:
		DrawSprite(304 - (256 + 128 - sinMoveKindInter[SIN_CHARSHOP]), 313 + sinInterHeight2, lpExit, 0, 0, 20, 20);
		DrawSprite(314 - 10 - (256 + 128 - sinMoveKindInter[SIN_CHARSHOP]), 313 - 27 + sinInterHeight2, cInvenTory.lpExitInfo, 0, 0, 47, 27);
		break;

	}
	if (MyShopSendButton)
		DrawSprite(ShopButtonPosi[SINREPAIR - 1][0] - (256 + 128 - sinMoveKindInter[SIN_MYSHOP]), ShopButtonPosi[SINREPAIR - 1][1], lpMyShopSale, 0, 0, 28, 28);

	switch (SelectMyShopButtonPosi)
	{
	case 1:
		DrawSprite(ShopButtonPosi[SINALLREPAIR - 1][0] - (256 + 128 - sinMoveKindInter[SIN_MYSHOP]), ShopButtonPosi[SINALLREPAIR - 1][1], lpMyShopNoSale, 0, 0, 28, 28);
		DrawSprite(ShopButtonPosi[SINALLREPAIR - 1][0] - 26 - (256 + 128 - sinMoveKindInter[SIN_MYSHOP]) - 8, ShopButtonPosi[SINALLREPAIR - 1][1] - 27, lpMyShopNoSale_T, 0, 0, 100, 26);
		break;
	case 2:
		DrawSprite(ShopButtonPosi[SINREPAIR - 1][0] - (256 + 128 - sinMoveKindInter[SIN_MYSHOP]), ShopButtonPosi[SINREPAIR - 1][1], lpMyShopSale, 0, 0, 28, 28);
		DrawSprite(ShopButtonPosi[SINREPAIR - 1][0] - 26 - (256 + 128 - sinMoveKindInter[SIN_MYSHOP]) - 8, ShopButtonPosi[SINREPAIR - 1][1] - 27, lpMyShopSale_T, 0, 0, 100, 26);

		break;
	case SINSHOPEXIT:
		DrawSprite(304 - (256 + 128 - sinMoveKindInter[SIN_MYSHOP]), 313 + sinInterHeight2, lpExit, 0, 0, 20, 20);
		DrawSprite(314 - 10 - (256 + 128 - sinMoveKindInter[SIN_MYSHOP]), 313 - 27 + sinInterHeight2, cInvenTory.lpExitInfo, 0, 0, 47, 27);
		break;
	}
	switch (SelectShopButtonPosi)
	{
	case SINALLREPAIR:
		if (sinShopKind != 3)
		{
			DrawSprite(ShopButtonPosi[SINALLREPAIR - 1][0] - (256 + 128 - sinMoveKindInter[SIN_SHOP]), ShopButtonPosi[SINALLREPAIR - 1][1], lpAllRepair, 0, 0, 28, 28);
			DrawSprite(ShopButtonPosi[SINALLREPAIR - 1][0] - 26 - (256 + 128 - sinMoveKindInter[SIN_SHOP]), ShopButtonPosi[SINALLREPAIR - 1][1] - 27, lpRepairAllInfo, 0, 0, 77, 27);
		}
		break;
	case SINREPAIR:
		if (sinShopKind != 3)
		{
			DrawSprite(ShopButtonPosi[SINREPAIR - 1][0] - (256 + 128 - sinMoveKindInter[SIN_SHOP]), ShopButtonPosi[SINREPAIR - 1][1], lpRepair, 0, 0, 28, 28);
			DrawSprite(ShopButtonPosi[SINREPAIR - 1][0] - 26 - (256 + 128 - sinMoveKindInter[SIN_SHOP]), ShopButtonPosi[SINREPAIR - 1][1] - 27, lpRepairInfo, 0, 0, 77, 27);
		}
		break;
	case SINSELL:
		DrawSprite(ShopButtonPosi[SINSELL - 1][0] - (256 + 128 - sinMoveKindInter[SIN_SHOP]), ShopButtonPosi[SINSELL - 1][1], lpSell, 0, 0, 28, 28);
		DrawSprite(ShopButtonPosi[SINSELL - 1][0] - 26 - (256 + 128 - sinMoveKindInter[SIN_SHOP]), ShopButtonPosi[SINSELL - 1][1] - 27, lpSellInfo, 0, 0, 77, 27);
		break;
	case SINBUY:
		DrawSprite(ShopButtonPosi[SINBUY - 1][0] - (256 + 128 - sinMoveKindInter[SIN_SHOP]), ShopButtonPosi[SINBUY - 1][1], lpBuy, 0, 0, 28, 28);
		DrawSprite(ShopButtonPosi[SINBUY - 1][0] - 26 - (256 + 128 - sinMoveKindInter[SIN_SHOP]), ShopButtonPosi[SINBUY - 1][1] - 27, lpBuyInfo, 0, 0, 77, 27);
		break;
	case SINRIGHTARROW:
		DrawSprite(282 - (256 + 128 - sinMoveKindInter[SIN_SHOP]), 182 + sinInterHeight2, cInvenTory.lpInvenArrow[1], 0, 0, 20, 20);

		break;
	case SINLEFTARROW:
		DrawSprite(260 - (256 + 128 - sinMoveKindInter[SIN_SHOP]), 182 + sinInterHeight2, cInvenTory.lpInvenArrow[0], 0, 0, 20, 20);
		break;
	case SINSHOPEXIT:
		DrawSprite(304 - (256 + 128 - sinMoveKindInter[SIN_SHOP]), 313 + sinInterHeight2, lpExit, 0, 0, 20, 20);
		DrawSprite(314 - 10 - (256 + 128 - sinMoveKindInter[SIN_SHOP]), 313 - 27 + sinInterHeight2, cInvenTory.lpExitInfo, 0, 0, 47, 27);

		break;

	}

	if (cShop.OpenFlag)
	{
		for (int cnt = 0; cnt < 30; cnt++)
		{
			if (ShowShopItem[cnt].bValid == 1)
			{
				if (ShowShopItem[cnt].sItem.bCanNotUse)
					dsDrawColorBox(sinInvenColor[2], ShowShopItem[cnt].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_SHOP]),
						ShowShopItem[cnt].iPlaceY,
						ShowShopItem[cnt].iWidth,
						ShowShopItem[cnt].iHeight);
			}
		}
	}
	if (ShowShopItemIndex)
	{
		for (i = 0; i < GridRow; i++)
		{
			for (j = 0; j < GridCol; j++)
				DrawSprite(StartGirdX + (22 * i) - (256 + 128 - sinMoveKindInter[SIN_SHOP]), StartGirdY + (22 * j), lpGrid, 0, 0, 22, 22);
		}

		dsDrawColorBox(sinInvenColor[0], ShopItemRect.left - (256 + 128 - sinMoveKindInter[SIN_SHOP]), ShopItemRect.top, ShopItemRect.right, ShopItemRect.bottom);
	}

	for (i = 0; i < 30; i++)
	{
		if (ShowShopItem[i].bValid)
			DrawSprite(ShowShopItem[i].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_SHOP]),
				ShowShopItem[i].iPlaceY,
				(smTEXTUREHANDLE *)ShowShopItem[i].pcInventoryTexture,
				0,
				0,
				ShowShopItem[i].iWidth,
				ShowShopItem[i].iHeight);
	}

	if (SelectMyShopItemIndex)
		dsDrawColorBox(sinInvenColor[4],
			cMyShop.MyShopItem[SelectMyShopItemIndex - 1].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_MYSHOP]),
			cMyShop.MyShopItem[SelectMyShopItemIndex - 1].iPlaceY,
			cMyShop.MyShopItem[SelectMyShopItemIndex - 1].iWidth,
			cMyShop.MyShopItem[SelectMyShopItemIndex - 1].iHeight);

	if (cMyShop.OpenFlag)
	{
		for (i = 0; i < 30; i++)
		{
			if (cMyShop.MyShopItem[i].bValid)
			{
				DrawSprite(cMyShop.MyShopItem[i].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_MYSHOP]),
					cMyShop.MyShopItem[i].iPlaceY,
					(smTEXTUREHANDLE *)cMyShop.MyShopItem[i].pcInventoryTexture,
					0,
					0,
					cMyShop.MyShopItem[i].iWidth,
					cMyShop.MyShopItem[i].iHeight);

				if ((cMyShop.MyShopItem[i].sBaseItemID.ToInt() & sinITEM_MASK2) == sinFO1)
					cInvenTory.DrawForceOrbEffect(cMyShop.MyShopItem[i].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_MYSHOP]),
						cMyShop.MyShopItem[i].iPlaceY);
			}
		}
	}


	int x, y;
	if (cMyShop.OpenFlag)
	{
		if (MyShopMouseItem.bValid)
		{
			if (!sMessageBox2[MESSAGE_MYSHOP_ITEM].Flag)
			{
				x = pCursorPos.x - (MyShopMouseItem.iWidth / 2);
				y = pCursorPos.y - (MyShopMouseItem.iHeight / 2);

				dsDrawOffsetArray = dsARRAY_TOP;
				DrawSprite(x, y, (smTEXTUREHANDLE *)MyShopMouseItem.pcInventoryTexture, 0, 0, MyShopMouseItem.iWidth, MyShopMouseItem.iHeight);
				dsDrawColorBox(D3DCOLOR_RGBA(0, 0, 128, 125), x, y, MyShopMouseItem.iWidth, MyShopMouseItem.iHeight);
				DrawSprite(x, y, (smTEXTUREHANDLE *)MyShopMouseItem.pcInventoryTexture, 0, 0, MyShopMouseItem.iWidth, MyShopMouseItem.iHeight);
			}
		}
	}


	if (SelectMyShopItemIndex)
		dsDrawColorBox(sinInvenColor[4],
			cCharShop.CharShopItem[SelectMyShopItemIndex - 1].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_CHARSHOP]),
			cCharShop.CharShopItem[SelectMyShopItemIndex - 1].iPlaceY,
			cCharShop.CharShopItem[SelectMyShopItemIndex - 1].iWidth,
			cCharShop.CharShopItem[SelectMyShopItemIndex - 1].iHeight);

	if (cCharShop.OpenFlag)
	{
		for (i = 0; i < 30; i++)
		{
			if (cCharShop.CharShopItem[i].bValid)
			{
				DrawSprite(cCharShop.CharShopItem[i].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_CHARSHOP]),
					cCharShop.CharShopItem[i].iPlaceY,
					(smTEXTUREHANDLE *)cCharShop.CharShopItem[i].pcInventoryTexture,
					0,
					0,
					cCharShop.CharShopItem[i].iWidth,
					cCharShop.CharShopItem[i].iHeight);
				if ((cCharShop.CharShopItem[i].sBaseItemID.ToInt() & sinITEM_MASK2) == sinFO1)
					cInvenTory.DrawForceOrbEffect(cCharShop.CharShopItem[i].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_CHARSHOP]),
						cCharShop.CharShopItem[i].iPlaceY);
			}
		}
	}

	if (MyShopSendButton && !cMyShop.OpenFlag)
		dsDrawTexImage(MatMyShop_Button, 10, 220, 70, 70, 255);


	int BackUpPosX, BackUpPosY = 0;
	int BackUpButton2X, BackUpButton2Y = 0;
	int BackUpButton3X, BackUpButton3Y = 0;

	if (MyShopExpBox)
	{
		BackUpButton2X = 35;
		BackUpButton2Y = 157;
		BackUpButton3X = 115;
		BackUpButton3Y = 157;

		BackUpPosX = BackStartPos.x;
		BackUpPosY = BackStartPos.y;

		BackStartPos.x = MyShopExpBoxX;
		BackStartPos.y = MyShopExpBoxY;

		Interface_clanmenu.DrawBox(BackStartPos.x, BackStartPos.y, 2, 3);
		dsDrawTexImage(MatHelpBoxImage[9], BackStartPos.x + 7, BackStartPos.y + 35, 180, 15, 255);

		dsDrawTexImage(MatMyShopPRBoxLine, BackStartPos.x + 28, BackStartPos.y + 50, 254, 90, 255);

		DrawSprite(BackStartPos.x + BackUpButton2X, BackStartPos.y + BackUpButton2Y, cMessageBox.lpButtonBox07, 0, 0, 48, 23, 1);
		DrawSprite(BackStartPos.x + BackUpButton3X, BackStartPos.y + BackUpButton3Y, cMessageBox.lpButtonBox07, 0, 0, 48, 23, 1);

		if (MyShopExpButtonOK)
			DrawSprite(BackStartPos.x + BackUpButton2X + 7, BackStartPos.y + BackUpButton2Y + 3, cMessageBox.lpButtonYes07, 0, 0, 32, 16, 1);
		else DrawSprite(BackStartPos.x + BackUpButton2X + 7, BackStartPos.y + BackUpButton2Y + 3, cMessageBox.lpButtonYesGlay07, 0, 0, 32, 16, 1);
		if (MyShopExpButtonCancel)
			DrawSprite(BackStartPos.x + BackUpButton3X + 7, BackStartPos.y + BackUpButton3Y + 3, cMessageBox.lpButtonNo07, 0, 0, 32, 16, 1);
		else DrawSprite(BackStartPos.x + BackUpButton3X + 7, BackStartPos.y + BackUpButton3Y + 3, cMessageBox.lpButtonNoGlay07, 0, 0, 32, 16, 1);

		BackStartPos.x = BackUpPosX;
		BackStartPos.y = BackUpPosY;
	}
}

DWORD dwBuyItemServerTime = 0;
int MyShopItemSellMoney2 = 0;
DWORD dwBuyCharShopTime = 0;

void cSHOP::Main()
{
	int i = 0;

	if (haCharShopDelayFlag)
	{
		dwBuyCharShopTime++;
		if (dwBuyCharShopTime >= 1 * 70)
		{
			haCharShopDelayFlag = 0;
			dwBuyCharShopTime = 0;
		}
	}

	cMyShop.AutoCloseShop();

	MyShopExpBoxX = 300;
	MyShopExpBoxY = 170;

	CheckShopNpcState();
	SelectShopButtonPosi = 0;
	ShowShopItemIndex = 0;
	ShopItemPrice = 0;

	CloseMyShopFlag = 0;
	CloseCharShopFlag = 0;


	int BackUpPosX, BackUpPosY = 0;

	MyShopExpButtonOK = 0;
	MyShopExpButtonCancel = 0;

	int BackUpButton2X, BackUpButton2Y = 0;
	int BackUpButton3X, BackUpButton3Y = 0;

	if (MyShopExpBox)
	{
		BackUpPosX = BackStartPos.x;
		BackUpPosY = BackStartPos.y;

		BackStartPos.x = MyShopExpBoxX;
		BackStartPos.y = MyShopExpBoxY;

		BackUpButton2X = 35;
		BackUpButton2Y = 157;
		BackUpButton3X = 115;
		BackUpButton3Y = 157;

		if (pCursorPos.x > BackStartPos.x + BackUpButton2X && pCursorPos.x < BackStartPos.x + BackUpButton2X + 32 && pCursorPos.y >BackStartPos.y + BackUpButton2Y && pCursorPos.y < BackStartPos.y + BackUpButton2Y + 16)
			MyShopExpButtonOK = 1;

		if (pCursorPos.x > BackStartPos.x + BackUpButton3X && pCursorPos.x < BackStartPos.x + BackUpButton3X + 32 && pCursorPos.y >BackStartPos.y + BackUpButton3Y && pCursorPos.y < BackStartPos.y + BackUpButton3Y + 16)
			MyShopExpButtonCancel = 1;

		BackStartPos.x = BackUpPosX;
		BackStartPos.y = BackUpPosY;

	}

	if (cMyShop.OpenFlag)
	{
		if (pCursorPos.x >= DownTradePosi[T_CLOSE_POSI][0] && pCursorPos.x <= DownTradePosi[T_CLOSE_POSI][2] && pCursorPos.y >= DownTradePosi[T_CLOSE_POSI][1] && pCursorPos.y <= DownTradePosi[T_CLOSE_POSI][3])
			CloseMyShopFlag = 1;
	}

	if (cCharShop.OpenFlag)
	{
		if (pCursorPos.x >= DownTradePosi[T_CLOSE_POSI][0] && pCursorPos.x <= DownTradePosi[T_CLOSE_POSI][2] && pCursorPos.y >= DownTradePosi[T_CLOSE_POSI][1] && pCursorPos.y <= DownTradePosi[T_CLOSE_POSI][3])
			CloseCharShopFlag = 1;
	}

	SelectMyShopButtonPosi = 0;
	if (cMyShop.OpenFlag)
	{
		if (!MyShopExpBox)
		{
			for (i = 0; i < 9; i++)
			{
				if (ShopButtonPosi[i][0] < pCursorPos.x  && ShopButtonPosi[i][2] > pCursorPos.x && ShopButtonPosi[i][1] < pCursorPos.y  && ShopButtonPosi[i][3] > pCursorPos.y && !MouseItem.bValid)
					SelectMyShopButtonPosi = i + 1;
			}
		}
	}

	SelectCharShopButtonPosi = 0;
	if (cCharShop.OpenFlag)
	{
		for (i = 0; i < 9; i++)
		{
			if (ShopButtonPosi[i][0] < pCursorPos.x  && ShopButtonPosi[i][2] > pCursorPos.x && ShopButtonPosi[i][1] < pCursorPos.y  && ShopButtonPosi[i][3] > pCursorPos.y && !MouseItem.bValid)
				SelectCharShopButtonPosi = i + 1;
		}
	}

	int Index2 = 0;
	int BackUpX = 0, BackUpY = 0;
	SelectMyShopItemIndex = 0;
	if (cMyShop.OpenFlag)
	{
		for (i = 0; i < 30; i++)
		{
			if (cMyShop.MyShopItem[i].bValid)
			{
				if (cMyShop.MyShopItem[i].iPlaceX < pCursorPos.x  &&
					cMyShop.MyShopItem[i].iPlaceX + cMyShop.MyShopItem[i].iWidth > pCursorPos.x  &&
					cMyShop.MyShopItem[i].iPlaceY < pCursorPos.y  &&
					cMyShop.MyShopItem[i].iPlaceY + cMyShop.MyShopItem[i].iHeight > pCursorPos.y)
				{
					Index2 = cMyShop.SearchShopItemToInven(&cMyShop.MyShopItem[i]);
					if (Index2)
					{
						SelectMyShopItemIndex = i + 1;
						BackUpX = cInvenTory.InvenItem[Index2 - 1].iPlaceX;
						BackUpY = cInvenTory.InvenItem[Index2 - 1].iPlaceY;
						cInvenTory.InvenItem[Index2 - 1].iPlaceX = cMyShop.MyShopItem[i].iPlaceX;
						cInvenTory.InvenItem[Index2 - 1].iPlaceY = cMyShop.MyShopItem[i].iPlaceY;
						sinShowItemInfoFlag = 1;
						MyShopItemSellMoney2 = cMyShop.MyShopItem[i].sItem.iGold;
						cItem.ShowItemInfo(&cInvenTory.InvenItem[Index2 - 1], 3, Index2 - 1);
						cInvenTory.InvenItem[Index2 - 1].iPlaceX = BackUpX;
						cInvenTory.InvenItem[Index2 - 1].iPlaceY = BackUpY;
					}
				}
			}
		}
	}
	if (cCharShop.OpenFlag)
	{
		for (i = 0; i < 30; i++)
		{
			if (cCharShop.CharShopItem[i].bValid)
			{
				if (cCharShop.CharShopItem[i].iPlaceX < pCursorPos.x  &&
					cCharShop.CharShopItem[i].iPlaceX + cCharShop.CharShopItem[i].iWidth > pCursorPos.x  &&
					cCharShop.CharShopItem[i].iPlaceY < pCursorPos.y  &&
					cCharShop.CharShopItem[i].iPlaceY + cCharShop.CharShopItem[i].iHeight > pCursorPos.y)
				{
					SelectMyShopItemIndex = i + 1;
					Index2 = cCharShop.SearchMyShopItem(cCharShop.CharShopItem[i].sItem.sItemID.ToInt(), cCharShop.CharShopItem[i].sItem.iChk1, cCharShop.CharShopItem[i].sItem.iChk2);
					if (Index2)
					{
						sinShowItemInfoFlag = 1;
						MyShopItemSellMoney2 = sRecvMyShop.sMyShopItem[Index2 - 1].Price;
						cItem.ShowItemInfo(&cCharShop.CharShopItem[i], 3);
					}
				}
			}
		}
	}

	if (BuyItemServerFlag)
	{
		dwBuyItemServerTime++;
		if (dwBuyItemServerTime >= 10 * 70)
		{
			BuyItemServerFlag = 0;
			dwBuyItemServerTime = 0;
		}
	}

	if (OpenFlag)
	{
		for (i = 0; i < 9; i++)
		{
			if (ShopButtonPosi[i][0] < pCursorPos.x  && ShopButtonPosi[i][2] > pCursorPos.x && ShopButtonPosi[i][1] < pCursorPos.y  && ShopButtonPosi[i][3] > pCursorPos.y && !MouseItem.bValid)
				SelectShopButtonPosi = i + 1;
		}

	}
	if (OpenFlag)
	{
		for (i = 0; i < 30; i++)
		{
			cInvenTory.CharOnlySetItem(&ShowShopItem[i]);
			cInvenTory.CheckRequireItemToSet(&ShowShopItem[i]);
			if (ShowShopItem[i].iPlaceX < pCursorPos.x  &&
				ShowShopItem[i].iPlaceX + ShowShopItem[i].iWidth > pCursorPos.x &&
				ShowShopItem[i].iPlaceY < pCursorPos.y  &&
				ShowShopItem[i].iPlaceY + ShowShopItem[i].iHeight > pCursorPos.y)
			{
				if (ShowShopItem[i].bValid)
				{
					if (!MouseItem.bValid)
					{
						ShopItemRect.left	= ShowShopItem[i].iPlaceX;
						ShopItemRect.top	= ShowShopItem[i].iPlaceY;
						ShopItemRect.right	= ShowShopItem[i].iWidth;
						ShopItemRect.bottom = ShowShopItem[i].iHeight;

						GridRow = ShowShopItem[i].iWidth / 22;
						GridCol = ShowShopItem[i].iHeight / 22;
						StartGirdX = ShowShopItem[i].iPlaceX;
						StartGirdY = ShowShopItem[i].iPlaceY;
						sinShowItemInfoFlag = 1;

						ShopItemPrice = ShowShopItem[i].sItem.iSalePrice;
						cItem.ShowItemInfo(&ShowShopItem[i], 1);
						ShowShopItemIndex = i + 1;
					}
				}
			}
		}
	}
}
void cSHOP::Close()
{
	Release();
}
void cSHOP::LButtonDown(int x, int y)
{
	int cnt = 0;
	ItemData TempItem;

	if (MyShopSendButton && !cMyShop.OpenFlag)
	{
		if (x >= 10 && x <= 10 + 70 && y >= 220 && y <= 220 + 70)
			cInterFace.CheckAllBox(SIN_MYSHOP);
	}

	memset(&TempItem, 0, sizeof(ItemData));

	MyShopItemCancelIndex[0] = 0;
	MyShopItemCancelIndex[1] = 0;
	int Index3 = 0;

	if (cMyShop.OpenFlag && !MyShopMouseItem.bValid)
	{
		if (!MyShopSendButton)
		{
			for (int i = 0; i < 30; i++)
			{
				if (cMyShop.MyShopItem[i].bValid)
				{
					if (cMyShop.MyShopItem[i].iPlaceX < pCursorPos.x  &&
						cMyShop.MyShopItem[i].iPlaceX + cMyShop.MyShopItem[i].iWidth > pCursorPos.x  &&
						cMyShop.MyShopItem[i].iPlaceY < pCursorPos.y  &&
						cMyShop.MyShopItem[i].iPlaceY + cMyShop.MyShopItem[i].iHeight > pCursorPos.y)
					{
						Index3 = cMyShop.SearchShopItemToInven(&cMyShop.MyShopItem[i]);
						if (Index3)
						{
							cMessageBox.ShowMessage3(MESSAGE_MYSHOP_ITEM_CANCEL, cInvenTory.InvenItem[Index3 - 1].sItem.szItemName);
							MyShopItemCancelIndex[0] = Index3;
							MyShopItemCancelIndex[1] = i + 1;
							break;
						}
					}
				}
			}
		}
	}

	if (cMyShop.OpenFlag)
	{
		if (MyShopMouseItem.bValid)
		{
			if (!sinMyShopItemPass && !MyShopSendButton)
			{
				if (!cMyShop.SetMyShopItem(&MyShopMouseItem))
					memset(&MyShopMouseItem, 0, sizeof(ItemData));
			}
		}
		if (CloseMyShopFlag)
		{
			if (!MyShopSendButton)
			{
				cMyShop.OpenFlag = 0;
				memset(cMyShop.MyShopItem, 0, sizeof(ItemData) * 30);
				memset(MyShopItemIndex, 0, sizeof(int) * 100);
				MyShopSendButton = 0;
			}
			else
				cMyShop.OpenFlag = 0;
		}
	}

	int Index2 = 0;
	if (cCharShop.OpenFlag)
	{
		if (CloseCharShopFlag)
		{
			cCharShop.OpenFlag = 0;
			memset(cCharShop.CharShopItem, 0, sizeof(ItemData) * 30);
		}
		memset(&sMyShop_Server, 0, sizeof(sMYSHOP_ITEM_SERVER));
		if (SelectMyShopItemIndex)
		{
			if (!haCharShopDelayFlag)
			{
				cCharShop.BuyItem(SelectMyShopItemIndex - 1);
				haCharShopDelayFlag = 1;
			}
		}
	}

	if (MyShopExpButtonOK)
	{
		lstrcpy(cMyShop.szSendDoc, cMyShop.szDoc);
		MyShopExpBox = 0;
		isDrawClanMenu = 0;
		hFocusWnd = 0;
		sinMessageBoxShowFlag = 0;
		MyShopSendButton = 1;
		cMyShop.SendMyShopItem();
		SetIME_Mode(FALSE);
	}
	if (MyShopExpButtonCancel)
	{
		MyShopExpBox = 0;
		isDrawClanMenu = 0;
		hFocusWnd = 0;
		sinMessageBoxShowFlag = 0;
		SetIME_Mode(FALSE);
	}

	int j = 0;
	int CheckMyShopItemFlag = 0;

	switch (SelectMyShopButtonPosi)
	{
	case 1:
		MyShopSendButton = 0;
		SendClosePersonalTrade();
		break;
	case 2:
		for (j = 0; j < 100; j++)
		{
			if (MyShopItemIndex[j])
				CheckMyShopItemFlag = 1;
		}

		if (CheckMyShopItemFlag)
		{
			if (!MyShopSendButton)
			{
				if (!MyShopSendButton)
				{
					SetIME_Mode(TRUE);
					MyShopExpBox = 1;
					hFocusWnd = hTextWnd;
					sinMessageBoxShowFlag = 1;
				}
			}
		}
		else
			cMessageBox.ShowMessage(MESSAGE_NOT_SALE_ITEM);
		break;
	}

	sITEMPRICE sinItemPrice;

	if (ShowShopItemIndex)
	{
		if (CURSORHANDLE->GetMouseCurosr() == ECURSORICON_Default ||
			CURSORHANDLE->GetMouseCurosr() == ECURSORICON_Buy)
		{
			if (ShowShopItem[ShowShopItemIndex - 1].iItemSlotFlag == ITEMSLOTFLAG_Potion)
			{
				pMessageItem = &ShowShopItem[ShowShopItemIndex - 1];
				cMessageBox.ShowMessage2(MESSAGE_BUY_ITEM);
				BuyItemIndexCopy = ShowShopItemIndex;
			}
			else
			{
				pMessageItem = &ShowShopItem[ShowShopItemIndex - 1];
				cMessageBox.ShowMessage2(MESSAGE_BUY_ITEM_DEFALT);
				BuyItemIndexCopy = ShowShopItemIndex;
			}

		}
	}

	switch (SelectShopButtonPosi)
	{
	case 1:
		if (sinShopKind == 3)
			break;
		for (cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
		{
			if (cInvenTory.InvenItem[cnt].bValid)
			{
				sinItemPrice = cInvenTory.GetInvenItemPrice(&cInvenTory.InvenItem[cnt]);
				if (!cInvenTory.RepairInvenItem(&cInvenTory.InvenItem[cnt], sinItemPrice.RepairCost))
					continue;
			}
		}
		sinPlaySound(SIN_SOUND_REPAIR_ITEM);
		break;
	case 2:
		if (sinShopKind == 3)
			break;
		CURSORHANDLE->SetMouseCursor(ECURSORICON_Repair);
		break;
	case 3:
		CURSORHANDLE->SetMouseCursor(ECURSORICON_Sell);
		break;
	case 4:
		CURSORHANDLE->SetMouseCursor(ECURSORICON_Buy);
		break;
	case 5:
		ShopArrowPosi = 1;

		if (sinShopKind == 2)
			CopyShopItemToShow(ShowShopItemIndex2, 1);
		else
			CopyShopItemToShow(ShowShopItemIndex2, 0);
		break;
	case 6:

		ShopArrowPosi = 0;
		if (sinShopKind == 2)
			CopyShopItemToShow(0, 1);
		else
			CopyShopItemToShow(0, 0);
		break;
	case 7:
		OpenFlag = 0;
		break;
	case 8:
		if (sinShopKind == 3)
			break;
		sinShopKind = 1;
		ShowShopItemIndex2 = 0;
		CopyShopItemToShow(0, 0);
		ShopArrowPosi = 0;
		break;
	case 9:
		if (sinShopKind == 3)
			break;
		sinShopKind = 2;
		ShowShopItemIndex2 = 0;
		CopyShopItemToShow(0, 1);
		ShopArrowPosi = 0;
		break;
	default:
		CURSORHANDLE->SetMouseCursor(MouseItem.bValid ? ECURSORICON_None : ECURSORICON_Default);
		break;
	}

	if (cCharShop.OpenFlag)
	{
		if (SelectCharShopButtonPosi == 4)
			CURSORHANDLE->SetMouseCursor(ECURSORICON_Buy);
	}

	DeleteShopItem();

	if (MouseItem.bValid)
		cInvenTory.CheckRequireItemToSet(&MouseItem);

}

void cSHOP::LButtonUp(int x, int y)
{


}

void cSHOP::RButtonDown(int x, int y)
{
	ItemData TempItem;
	memset(&TempItem, 0, sizeof(ItemData));
	if (cCharShop.OpenFlag)
	{
		if (SelectMyShopItemIndex)
			cCharShop.BuyItem(SelectMyShopItemIndex - 1);
	}

	if (ShowShopItemIndex)
	{
		if (CURSORHANDLE->GetMouseCurosr() == ECURSORICON_Default ||
			CURSORHANDLE->GetMouseCurosr() == ECURSORICON_Buy)
		{
			if (ShowShopItem[ShowShopItemIndex - 1].iItemSlotFlag == ITEMSLOTFLAG_Potion)
			{
				pMessageItem = &ShowShopItem[ShowShopItemIndex - 1];
				cMessageBox.ShowMessage2(MESSAGE_BUY_ITEM);
				BuyItemIndexCopy = ShowShopItemIndex;

			}
			else
			{
				if (!BuyItemServerFlag)
					SendBuyItemToServer(&ShowShopItem[ShowShopItemIndex - 1]);
			}
		}
	}
	if (cMyShop.OpenFlag)
	{
		cInvenTory.PickUpInvenItem(pCursorPos.x, pCursorPos.y, 2);
		if (MyShopMouseItem.bValid)
		{
			if (!MyShopSendButton)
			{
				if (sinMyShopItemPass != 0)
					sinMyShopItemPass = 0;
				cMyShop.SetMyShopItem(&MyShopMouseItem, TRUE);
			}
		}
	}
}
void cSHOP::RButtonUp(int x, int y)
{

}
void cSHOP::KeyDown()
{
	DeleteShopItem();
}
void cSHOP::CheckShopNpcState()
{
	if (!DispEachMode)
	{
		if (TalkNpcState)
		{
			cShop.OpenFlag = 0;
			cInvenTory.OpenFlag = 0;
			TalkNpcState = 0;
		}
	}
}
void cSHOP::CopyShopItemToShow(int Index, int Kind)
{
	memset(ShowShopItem, 0, sizeof(ItemData) * 30);

	for (int i = 0; i < 30 - Index; i++)
	{
		if (GetShopItemXY(&ShopItem[i + Index + (Kind * 30)]))
			memcpy(&ShowShopItem[i], &ShopItem[i + Index + (Kind * 30)], sizeof(ItemData));
		else
		{
			ShowShopItemIndex2 = i + Index;
			break;
		}
	}
}
int cSHOP::GetShopItemXY(ItemData *pItem)
{
	int cntx, cnty;
	int cx, cy;

	RECT	rect;
	int		flag;

	int StartX = 21;
	int StartY = 136 + sinInterHeight2;

	cx = (22 * SHOP_ROW) - pItem->iWidth;
	cy = (22 * SHOP_COL) - pItem->iHeight;

	for (cntx = StartX; cntx <= StartX + cx; cntx += 22)
	{
		for (cnty = StartY; cnty <= StartY + cy; cnty += 22)
		{
			flag = 0;
			for (int i = 0; i < 30; i++)
			{
				if (ShowShopItem[i].bValid)
				{
					rect.left   = ShowShopItem[i].iPlaceX;
					rect.right  = ShowShopItem[i].iPlaceX + ShowShopItem[i].iWidth;
					rect.top    = ShowShopItem[i].iPlaceY;
					rect.bottom = ShowShopItem[i].iPlaceY + ShowShopItem[i].iHeight;

					if (cntx > rect.left - pItem->iWidth && cntx< rect.right &&
						cnty > rect.top - pItem->iHeight && cnty < rect.bottom)
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
int cSHOP::SendBuyItemToServer(ItemData *pItem, int ItemCount)
{
	if (!cInvenTory.CheckSetEmptyArea(pItem))
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
		return FALSE;
	}
	if (cShop.haBuyMoneyCheck(pItem->sItem.iSalePrice*ItemCount) == 0)
	{
		cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_MONEY);
		return FALSE;
	}
	if (pItem->sItem.iWeight + sinChar->sWeight.sMin > sinChar->sWeight.sMax)
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
		return FALSE;
	}
	BuyItemServerFlag = 1;

	TRANS_BUY_SHOPITEM	TransBuyShopItem;

	TransBuyShopItem.code = smTRANSCODE_SHOPTITEM;
	TransBuyShopItem.size = sizeof(TRANS_BUY_SHOPITEM);
	TransBuyShopItem.ItemCount = ItemCount;
	memcpy(&TransBuyShopItem.sItem, pItem, sizeof(ItemData));

	SENDPACKETL(&TransBuyShopItem);

	return FALSE;
}

//接受买物品到服务器
int cSHOP::RecvBuyItemToServer(ItemData *pItem, int ItemCount)
{
	BuyItemServerFlag = 0;
	CheckCharForm();

	if (haBuyMoneyCheck(pItem->sItem.iSalePrice*ItemCount))
	{
		sinMinusMoney(pItem->sItem.iSalePrice*ItemCount, 1);
		if (pItem->iItemSlotFlag == ITEMSLOTFLAG_Potion)
			pItem->sItem.iPotionCount = ItemCount;

		ReformCharForm();
		SendSaveMoney();
		if (cInvenTory.CheckRequireItemToSet(pItem))
		{
			if (CheckItemForm(&pItem->sItem))
				ReformItem(&pItem->sItem);
			else
			{
				SendSetHackUser(3);
				return FALSE;
			}
			if (cInvenTory.AutoSetInvenItem(pItem))
			{
				cInvenTory.SetItemToChar();

				if (ShowShopItemIndex)
				{
					//ShowShopItem[ShowShopItemIndex-1].Flag = 0;
				}
				else
				{
					if (BuyItemIndexCopy)
						ShowShopItem[BuyItemIndexCopy - 1].bValid = 0;
				}
				BuyItemIndexCopy = 0;
				ShowShopItemIndex = 0;
				cInvenTory.CheckWeight();
				if (pItem->iItemSlotFlag == ITEMSLOTFLAG_Potion ||
					pItem->iItemSlotFlag == ITEMSLOTFLAG_Inventory)
					pItem->bValid = 1;
				SaveGameData();
				return TRUE;
			}
			else
			{
				CheckCharForm();
				sinPlusMoney(pItem->sItem.iSalePrice*ItemCount);
				ReformCharForm();
				SendSaveMoney();
			}
		}
	}
	else
		cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_MONEY);

	return FALSE;
}
int cSHOP::SellItemToShop(ItemData *pItem, int ItemCount)
{
	if (!CheckItemForm(&pItem->sItem))
	{
		SendSetHackUser(4);
		pItem->bValid = 0;
		CheckCharForm();
		sinMinusMoney(pItem->iSalePrice * ItemCount);
		if (sinChar->iGold < 0)sinChar->iGold = 0;
		ReformCharForm();
		SendSaveMoney();
		sinPlaySound(pItem->iInvItemSound);
		return FALSE;

	}
	if (sinChar->iLevel <= 10)
	{
		if (sinChar->iGold + pItem->iSalePrice * ItemCount > 200000)
		{
			cMessageBox.ShowMessage(MESSAGE_OVER_MONEY);
			cInvenTory.ReFormInvenItem();
			return FALSE;
		}
	}
	else
	{
		switch (sinChar->iRank)
		{
		case 0:
			if ((sinChar->iGold + pItem->iSalePrice*ItemCount) >= (sinChar->iLevel * 200000) - 1800000)
			{
				cMessageBox.ShowMessage(MESSAGE_OVER_MONEY);
				cInvenTory.ReFormInvenItem();
				return FALSE;
			}
			break;
		case 1:
			if ((sinChar->iGold + pItem->iSalePrice*ItemCount) >= 10000000)
			{
				cMessageBox.ShowMessage(MESSAGE_OVER_MONEY);
				cInvenTory.ReFormInvenItem();
				return FALSE;
			}
			break;
		case 2:
			if ((sinChar->iGold + pItem->iSalePrice*ItemCount) >= 50000000)
			{
				cMessageBox.ShowMessage(MESSAGE_OVER_MONEY);
				cInvenTory.ReFormInvenItem();
				return FALSE;
			}
			break;
		case 3:
			if ((sinChar->iGold + pItem->iSalePrice * ItemCount) >= 100000000)
			{
				cMessageBox.ShowMessage(MESSAGE_OVER_MONEY);
				cInvenTory.ReFormInvenItem();
				return FALSE;
			}
			break;
		case 4:
			if ((sinChar->iGold + pItem->iSalePrice * ItemCount) >= 500000000)
			{
				cMessageBox.ShowMessage(MESSAGE_OVER_MONEY);
				cInvenTory.ReFormInvenItem();
				return FALSE;
			}
			break;
		}
	}

	if ((pItem->iItemSlotFlag == ITEMSLOTFLAG_LeftRightHand && CURSORHANDLE->GetMouseCurosr() == ECURSORICON_Sell && (pItem->sBaseItemID.ToInt() & sinITEM_MASK2) != sinWD1) ||
		(pItem->iItemSlotFlag == ITEMSLOTFLAG_Wing && CURSORHANDLE->GetMouseCurosr() == ECURSORICON_Sell))
		cInvenTory.PickUpTwoHandItem(pItem);

	SellItemToServer(&pItem->sItem, ItemCount);

	sinPlaySound(pItem->iInvItemSound);
	pItem->bValid = 0;
	ResetInvenItemCode();

	return TRUE;
}

//商店文字渲染
void cSHOP::DrawShopText()
{
	DWORD Color;

	if (ReStartFlag)
	{
		char strBuff[128];
		memset(strBuff, 0, sizeof(strBuff));

		if (ReStartIndex == 1 && RestartCheckExp)
			Color = D3DCOLOR_XRGB(255, 0, 0);
		else
			Color = D3DCOLOR_XRGB(255, 255, 255);

		if (szReStartMsg[0])
		{
			dsTextLineOut(0, ReStartTextXY.x, ReStartTextXY.y + 2, szReStartMsg, lstrlen(szReStartMsg), Color);
		}
		if (szReStartMsg2[0])
		{
			dsTextLineOut(0, ReStartTextXY.x, ReStartTextXY.y + 18, szReStartMsg2, lstrlen(szReStartMsg2), Color);
		}
	}

	if (!sinMoveKindInter[SIN_SHOP] && !sinMoveKindInter[SIN_MYSHOP] && !sinMoveKindInter[SIN_CHARSHOP])
		return;

	char strBuff[128];
	memset(strBuff, 0, sizeof(strBuff));

	Color = D3DCOLOR_XRGB(255, 255, 255);

	if (OpenFlag)
	{
		NumLineComa(sinChar->iGold, strBuff);
		dsTextLineOut(0, CheckEditSize(ShopGoldEdit[1][0], ShopGoldEdit[1][2], strBuff) - (256 + 128 - sinMoveKindInter[SIN_SHOP]), ShopGoldEdit[1][1], strBuff, lstrlen(strBuff), Color);

		if (ShopItemPrice)
		{
			memset(strBuff, 0, sizeof(strBuff));
			NumLineComa(haShopItemPrice(ShopItemPrice), strBuff);
			dsTextLineOut(0, CheckEditSize(ShopGoldEdit[0][0], ShopGoldEdit[0][2], strBuff) - (256 + 128 - sinMoveKindInter[SIN_SHOP]), ShopGoldEdit[0][1], strBuff, lstrlen(strBuff), Color);
		}

	}
	int BackUpPosX, BackUpPosY = 0;
	int Start = 0, End = 0, Conut = 0;

	char szBuff2[64];

	if (cMyShop.OpenFlag)
	{
		for (int i = 0; i < 30; i++)
		{
			if (cMyShop.MyShopItem[i].bValid)
			{
				if (cMyShop.MyShopItem[i].iItemSlotFlag == ITEMSLOTFLAG_Potion)
				{
					wsprintf(strBuff, "%d", cMyShop.MyShopItem[i].sItem.iPotionCount);
					dsTextLineOut(0,
						cMyShop.MyShopItem[i].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_MYSHOP]),
						cMyShop.MyShopItem[i].iPlaceY,
						strBuff,
						lstrlen(strBuff),
						Color);
				}
			}
		}
	}
	if (cCharShop.OpenFlag)
	{
		for (int i = 0; i < 30; i++)
		{
			if (cCharShop.CharShopItem[i].bValid)
			{
				if (cCharShop.CharShopItem[i].iItemSlotFlag == ITEMSLOTFLAG_Potion)
				{
					wsprintf(strBuff, "%d", cCharShop.CharShopItem[i].sItem.iPotionCount);
					dsTextLineOut(0,
						cCharShop.CharShopItem[i].iPlaceX - (256 + 128 - sinMoveKindInter[SIN_CHARSHOP]),
						cCharShop.CharShopItem[i].iPlaceY,
						strBuff,
						lstrlen(strBuff),
						Color);
				}
			}
		}
	}
	if (MyShopExpBox)
	{
		BackUpPosX = BackStartPos.x;
		BackUpPosY = BackStartPos.y;

		BackStartPos.x = MyShopExpBoxX;
		BackStartPos.y = MyShopExpBoxY;
		dsTextLineOut(1, BackStartPos.x + 60, BackStartPos.y + 20, "Notice", lstrlen("Shop Notice"), D3DCOLOR_XRGB(65, 177, 240));

		hFocusWnd = hTextWnd;
		GetWindowText(hFocusWnd, cMyShop.szDoc, 128);

		int len = 0;
		int line = 1;
		len = lstrlen(cMyShop.szDoc);

		line += (len / 20);

		for (int i = 0; i < len; i++)
		{
			memset(szBuff2, 0, sizeof(szBuff2));
			while (cMyShop.szDoc[End] != NULL)
			{
				if (cMyShop.szDoc[End] & 0x80)
				{
					End += 2;
					Conut += 2;
				}
				else
				{
					End++;
					Conut++;
				}
				if (Conut > 20)
					break;
			}
			memcpy(szBuff2, &cMyShop.szDoc[Start], End - Start);

			dsTextLineOut(0, BackStartPos.x + 32, BackStartPos.y + 60 + (i * 20), szBuff2, lstrlen(szBuff2), Color);

			if (cMyShop.szDoc[End] != NULL)
			{
				if (cMyShop.szDoc[End] == ' ')
					End += 1;
				Start = End;
				Conut = 0;
			}
			else
				break;

		}

		BackStartPos.x = BackUpPosX;
		BackStartPos.y = BackUpPosY;
	}
}

void cSHOP::DeleteShopItem()
{
	if (!OpenFlag)
	{
		if (cShop.ShopItem)
			memset(&cShop.ShopItem, 0, sizeof(ItemData) * 60);

		if (ShowShopItem)
			memset(&ShowShopItem, 0, sizeof(ItemData) * 30);
	}
}
int cSHOP::CheckHighRankItem(ItemData *pItem)
{
	DWORD Code[] = { sinOS1,sinQT1,sinSP1,sinGP1,sinQW1,sinGF1,sinMA1,sinMA2,sinSE1,sinBI1, sinBI2, sinWR1, sinDR1, sinPR1, sinPR2, sinPR3 };
	int Cnt = 0;
	while (1)
	{
		if (!Code[Cnt])
			break;
		if ((pItem->sItem.sItemID.ToItemType()) == Code[Cnt])
			return TRUE;
		Cnt++;
	}
	if ((pItem->sItem.sItemID.ToItemIndex()) > sin30)
		return TRUE;
	if (pItem->sItem.iLevel >= 41)
		return TRUE;
	if (pItem->sItem.eCraftType == ITEMCRAFTTYPE_Mixing || pItem->sItem.eCraftType == ITEMCRAFTTYPE_Aging)
		return TRUE;

	return FALSE;
}
int cMYSHOP::SetMyShopItem(ItemData *pItem, int Kind)
{
	int i;
	int SetFlag = 0;
	int SetCount = 0;

	int MyShopStartX = 21;
	int MyShopStartY = 136 - 50;
	int MyShopEndX = MyShopStartX + (22 * 9);
	int MyShopEndY = MyShopStartY + (22 * 9);

	if (Kind == 0)
	{
		if (MyShopStartX <= pItem->iPlaceX + 11 &&
			MyShopEndX > pItem->iPlaceX &&
			MyShopStartY <= pItem->iPlaceY + 11 &&
			MyShopEndY > pItem->iPlaceY)
			SetFlag = 1;

		if (SetFlag == NULL)
			return FALSE;
	}

	int cntx, cnty;
	int cx, cy;

	RECT	rect;
	int		flag;

	cx = (22 * 9) - pItem->iWidth;
	cy = (22 * 9) - pItem->iHeight;

	for (cntx = MyShopStartX; cntx <= MyShopStartX + cx; cntx += 22)
	{
		for (cnty = MyShopStartY; cnty <= MyShopStartY + cy; cnty += 22)
		{
			flag = 0;
			for (i = 0; i < 30; i++)
			{
				if (MyShopItem[i].bValid)
				{
					rect.left   = MyShopItem[i].iPlaceX;
					rect.right  = MyShopItem[i].iPlaceX + MyShopItem[i].iWidth;
					rect.top    = MyShopItem[i].iPlaceY;
					rect.bottom = MyShopItem[i].iPlaceY + MyShopItem[i].iHeight;

					if (cntx > rect.left - pItem->iWidth &&
						cntx < rect.right &&
						cnty > rect.top - pItem->iHeight &&
						cnty < rect.bottom)
						flag++;
				}
			}
			if (flag == 0)
			{
				if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinPZ1 ||
					(pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinPZ2)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_MYSHOP_ITEM);
					return TRUE;
				}
				else if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinOA2)
				{
					if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK3) == sin31 ||
						(pItem->sBaseItemID.ToInt() & sinITEM_MASK3) == sin32 ||
						(pItem->sBaseItemID.ToInt() & sinITEM_MASK3) == sin33 ||
						(pItem->sBaseItemID.ToInt() & sinITEM_MASK3) == sin34)
					{
						cMessageBox.ShowMessage(MESSAGE_NOT_MYSHOP_ITEM);
						return TRUE;
					}
				}
				else if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinDB1)
				{
					if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK3) == sin31 ||
						(pItem->sBaseItemID.ToInt() & sinITEM_MASK3) == sin32 ||
						(pItem->sBaseItemID.ToInt() & sinITEM_MASK3) == sin33 ||
						(pItem->sBaseItemID.ToInt() & sinITEM_MASK3) == sin34)
					{
						cMessageBox.ShowMessage(MESSAGE_NOT_MYSHOP_ITEM);
						return TRUE;
					}
				}
				else if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinOA1)
				{
					if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK3) == sin36)
					{
						cMessageBox.ShowMessage(MESSAGE_NOT_MYSHOP_ITEM);
						return TRUE;
					}
				}
				else if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinOA1)
				{
					if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK3) == sin37)
					{
						cMessageBox.ShowMessage(MESSAGE_NOT_MYSHOP_ITEM);
						return TRUE;
					}
				}

				else if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinGF1)
				{
					if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK3) == sin07 ||
						(pItem->sBaseItemID.ToInt() & sinITEM_MASK3) == sin08)
					{
						cMessageBox.ShowMessage(MESSAGE_NOT_MYSHOP_ITEM);
						return TRUE;
					}
				}
				cMessageBox.ShowMessage2(MESSAGE_MYSHOP_ITEM);
				return TRUE;
			}
		}
	}
	cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
	return FALSE;
}
int cMYSHOP::LastSetMyShopItem(ItemData *pItem)
{
	int cntx, cnty;
	int cx, cy;
	int MyShopStartX = 21;
	int MyShopStartY = 136 - 50;
	int MyShopEndX = MyShopStartX + (22 * 9);
	int MyShopEndY = MyShopStartY + (22 * 9);

	RECT	rect;
	int		flag;

	cx = (22 * 9) - pItem->iWidth;
	cy = (22 * 9) - pItem->iHeight;

	for (cntx = MyShopStartX; cntx <= MyShopStartX + cx; cntx += 22)
	{
		for (cnty = MyShopStartY; cnty <= MyShopStartY + cy; cnty += 22)
		{
			flag = 0;
			for (int i = 0; i < 30; i++)
			{
				if (MyShopItem[i].bValid)
				{
					rect.left	= MyShopItem[i].iPlaceX;
					rect.right	= MyShopItem[i].iPlaceX + MyShopItem[i].iWidth;
					rect.top	= MyShopItem[i].iPlaceY;
					rect.bottom = MyShopItem[i].iPlaceY + MyShopItem[i].iHeight;

					if (cntx > rect.left - pItem->iWidth &&
						cntx < rect.right &&
						cnty > rect.top - pItem->iHeight &&
						cnty < rect.bottom)
						flag++;
				}
			}
			if (flag == 0)
			{
				for (int j = 0; j < 30; j++)
				{
					if (!cMyShop.MyShopItem[j].bValid)
					{
						memcpy(&cMyShop.MyShopItem[j], pItem, sizeof(ItemData));
						cMyShop.MyShopItem[j].iPlaceX = cntx;
						cMyShop.MyShopItem[j].iPlaceY = cnty;
						SetShopItemToInven(pItem);
						pItem->bValid = 0;
						return TRUE;
					}
				}
			}
		}
	}
	return FALSE;
}
int cMYSHOP::SetShopItemToInven(ItemData *pItem)
{
	int i = 0, j = 0;
	for (i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (cInvenTory.InvenItem[i].bValid)
		{
			if (i + 1 == pItem->sItem.iIndex &&
				cInvenTory.InvenItem[i].sItem.iChk1 == pItem->sItem.iChk1 &&
				cInvenTory.InvenItem[i].sItem.iChk2 == pItem->sItem.iChk2)
			{
				MyShopItemIndex[i] = 1;
				return TRUE;
			}
		}
	}
	return TRUE;
}
int cMYSHOP::SearchShopItemToInven(ItemData *pItem)
{
	int i = 0, j = 0;
	for (i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (cInvenTory.InvenItem[i].bValid)
		{
			if (i + 1 == pItem->sItem.iIndex && cInvenTory.InvenItem[i].sItem.iChk1 == pItem->sItem.iChk1 && cInvenTory.InvenItem[i].sItem.iChk2 == pItem->sItem.iChk2)
				return i + 1;
		}
	}
	return FALSE;
}
int cMYSHOP::SendMyShopItem()
{
	int i = 0, j = 0, index = 0;

	memset(&sMyShop, 0, sizeof(sMYSHOP));
	for (i = 0; i < 30; i++)
	{
		if (cMyShop.MyShopItem[i].bValid)
		{
			index = SearchShopItemToInven(&cMyShop.MyShopItem[i]);
			if (index)
			{
				for (j = 0; j < 30; j++)
				{
					if (!sMyShop.sMyShopItem[j].sItem.sItemID.ToInt())
					{
						sMyShop.sMyShopItem[j].Price = cMyShop.MyShopItem[i].sItem.iGold;
						sMyShop.sMyShopItem[j].Posi[0] = cMyShop.MyShopItem[i].iPlaceX;
						sMyShop.sMyShopItem[j].Posi[1] = cMyShop.MyShopItem[i].iPlaceY;
						memcpy(&sMyShop.sMyShopItem[j].sItem, &cInvenTory.InvenItem[index - 1].sItem, sizeof(Item));
						break;
					}
				}
			}
		}
	}

	sMyShop.CHAR_CODE = lpCurPlayer->iID;
	SendOpenPersonalTrade(cMyShop.szSendDoc, &sMyShop);

	return TRUE;
}
int SerchsMyShopItem(ItemData *pItem)
{
	int i = 0, j = 0;
	for (i = 0; i < 30; i++)
	{
		if (sMyShop.sMyShopItem[i].sItem.iChk1 == pItem->sItem.iChk1 && sMyShop.sMyShopItem[i].sItem.iChk2 == pItem->sItem.iChk2 && sMyShop.sMyShopItem[i].sItem.sItemID.ToInt() == pItem->sBaseItemID.ToInt())
			return i + 1;
	}
	return 0;

}
int cMYSHOP::RecvMyShopItem(DWORD dwCharCode, sMYSHOP_ITEM_SERVER *lpShopItem)
{
	Unit *lpChar;

	int i = 0, j = 0, index = 0;
	memset(&sMyShop_Server, 0, sizeof(sMYSHOP_ITEM_SERVER));
	DWORD 	MASK_CODE = 0;
	MASK_CODE = (lpShopItem->CODE & sinITEM_MASK2);

	int ExitItemFlag = 0;
	int index5 = 0;

	switch (lpShopItem->SendFlag)
	{
	case 1:
		if (MyShopSendButton)
		{
			for (i = 0; i < 30; i++)
			{
				if (cMyShop.MyShopItem[i].bValid)
				{
					index = SearchShopItemToInven(&cMyShop.MyShopItem[i]);
					if (index)
					{
						if (lpShopItem->CkSum == cInvenTory.InvenItem[index - 1].sItem.iChk2 &&
							lpShopItem->Head == cInvenTory.InvenItem[index - 1].sItem.iChk1 &&
							lpShopItem->CODE == cInvenTory.InvenItem[index - 1].sItem.sItemID.ToInt())
						{
							ExitItemFlag = 1;
							index5 = SerchsMyShopItem(&cMyShop.MyShopItem[i]);
							if (!index5)
								break;

							if (MASK_CODE == sinPM1 || MASK_CODE == sinPL1 || MASK_CODE == sinPS1)
							{
								if (lpShopItem->Price != sMyShop.sMyShopItem[index5 - 1].Price*lpShopItem->sTime)
								{
									memcpy(&sMyShop_Server, lpShopItem, sizeof(sMYSHOP_ITEM_SERVER));
									sMyShop_Server.SendFlag = 7;
									sMyShop_Server.Price = sMyShop.sMyShopItem[index5 - 1].Price;
									Send_PersonalShopItem(sMyShop_Server.Buyer, &sMyShop_Server);
									UpdateMyShopList(&sMyShop);
									break;
								}
							}
							else
							{
								if (lpShopItem->Price != sMyShop.sMyShopItem[index5 - 1].Price)
								{
									memcpy(&sMyShop_Server, lpShopItem, sizeof(sMYSHOP_ITEM_SERVER));
									sMyShop_Server.SendFlag = 7;
									sMyShop_Server.Price = sMyShop.sMyShopItem[index5 - 1].Price;
									Send_PersonalShopItem(sMyShop_Server.Buyer, &sMyShop_Server);
									UpdateMyShopList(&sMyShop);
									break;
								}
							}

							lpChar = FindAutoPlayer(dwCharCode);
							CheckCharForm();
							if (MASK_CODE == sinPM1 || MASK_CODE == sinPL1 || MASK_CODE == sinPS1)
							{
								if (cInvenTory.InvenItem[index - 1].sItem.iPotionCount >= (int)lpShopItem->sTime)
								{
									sinPlusMoney(lpShopItem->Price);
									cInvenTory.InvenItem[index - 1].sItem.iPotionCount -= lpShopItem->sTime;
									cMyShop.MyShopItem[i].sItem.iPotionCount -= lpShopItem->sTime;
									sMyShop.sMyShopItem[index5 - 1].sItem.iPotionCount -= lpShopItem->sTime;
									if (cMyShop.MyShopItem[i].sItem.iPotionCount == 0)
									{
										cInvenTory.InvenItem[index - 1].bValid = 0;
										cMyShop.MyShopItem[i].bValid = 0;
										memset(&sMyShop.sMyShopItem[index5 - 1], 0, sizeof(sMYSHOP_ITEM));
									}
									if (lpChar)
									{
										CHATGAMEHANDLE->AddChatBoxTextEx(CHATCOLOR_Notice, " %s bought %s from you for %d GP, quantity %d",
											lpChar->sCharacterData.szName, cInvenTory.InvenItem[index - 1].sItem.szItemName, lpShopItem->Price, lpShopItem->sTime);
									}
									memcpy(&sMyShop_Server, lpShopItem, sizeof(sMYSHOP_ITEM_SERVER));
									sMyShop_Server.SendFlag = 2;
								}
								else
								{
									memcpy(&sMyShop_Server, lpShopItem, sizeof(sMYSHOP_ITEM_SERVER));
									sMyShop_Server.sTime = cInvenTory.InvenItem[index - 1].sItem.iPotionCount;
									cMyShop.MyShopItem[i].sItem.iPotionCount = cInvenTory.InvenItem[index - 1].sItem.iPotionCount;
									sMyShop.sMyShopItem[index5 - 1].sItem.iPotionCount = cInvenTory.InvenItem[index - 1].sItem.iPotionCount;
									sMyShop_Server.SendFlag = 6;
								}

							}
							else
							{
								if (lpChar)
								{
									CHATGAMEHANDLE->AddChatBoxTextEx(CHATCOLOR_Notice,
										" %s bought %s from you for %d GP, quantity %d", lpChar->sCharacterData.szName, cInvenTory.InvenItem[index - 1].sItem.szItemName, lpShopItem->Price, 1);
								}
								sinPlusMoney(lpShopItem->Price);
								cInvenTory.InvenItem[index - 1].bValid = 0;
								cMyShop.MyShopItem[i].bValid = 0;
								memset(&sMyShop.sMyShopItem[index5 - 1], 0, sizeof(sMYSHOP_ITEM));
								memcpy(&sMyShop_Server, lpShopItem, sizeof(sMYSHOP_ITEM_SERVER));
								sMyShop_Server.SendFlag = 2;
							}
							Send_PersonalShopItem(dwCharCode, &sMyShop_Server);
							UpdateMyShopList(&sMyShop);
							cInvenTory.ReFormInvenItem();
							ReformCharForm();
							ResetInvenItemCode();
							cInvenTory.ReFormPotionNum();
							ResetPotion();
							cInvenTory.CheckWeight();
							SaveGameData();
							break;
						}
					}
				}
			}
			if (!ExitItemFlag)
			{
				memcpy(&sMyShop_Server, lpShopItem, sizeof(sMYSHOP_ITEM_SERVER));
				sMyShop_Server.SendFlag = 3;
				Send_PersonalShopItem(sMyShop_Server.Buyer, &sMyShop_Server);
			}
		}
		else
		{
			memcpy(&sMyShop_Server, lpShopItem, sizeof(sMYSHOP_ITEM_SERVER));
			sMyShop_Server.SendFlag = 4;
			Send_PersonalShopItem(sMyShop_Server.Buyer, &sMyShop_Server);
		}
		break;
	case 2:
		lpChar = FindAutoPlayer(dwCharCode);
		index = cCharShop.SearchMyShopItem(lpShopItem->CODE, lpShopItem->Head, lpShopItem->CkSum);
		if (index)
		{
			CheckCharForm();
			if (MASK_CODE == sinPM1 || MASK_CODE == sinPL1 || MASK_CODE == sinPS1)
			{
				if (lpChar)
				{
					CHATGAMEHANDLE->AddChatBoxTextEx(CHATCOLOR_Notice,
						"%s sold you a %s for %d GP, quantity %d", lpChar->sCharacterData.szName, sRecvMyShop.sMyShopItem[index - 1].sItem.szItemName, lpShopItem->Price, lpShopItem->sTime);
				}
				sRecvMyShop.sMyShopItem[index - 1].sItem.iPotionCount = lpShopItem->sTime;
				cCharShop.CharShopItem[index - 1].sItem.iPotionCount -= lpShopItem->sTime;
				sinMinusMoney(lpShopItem->Price);
				cCharShop.SetCharShopItemToInven(&sRecvMyShop.sMyShopItem[index - 1].sItem);
				if (cCharShop.CharShopItem[index - 1].sItem.iPotionCount == 0)
				{
					cCharShop.CharShopItem[index - 1].bValid = 0;
					memset(&sRecvMyShop.sMyShopItem[index - 1].sItem, 0, sizeof(Item));
				}
			}
			else
			{
				if (lpChar)
				{
					CHATGAMEHANDLE->AddChatBoxTextEx(CHATCOLOR_Notice,
						"%s sold you a %s for %d GP, quantity %d", lpChar->sCharacterData.szName, sRecvMyShop.sMyShopItem[index - 1].sItem.szItemName, lpShopItem->Price, 1);
				}
				sinMinusMoney(lpShopItem->Price);
				cCharShop.CharShopItem[index - 1].bValid = 0;
				cCharShop.SetCharShopItemToInven(&sRecvMyShop.sMyShopItem[index - 1].sItem);
				memset(&sRecvMyShop.sMyShopItem[index - 1].sItem, 0, sizeof(Item));

			}
			cInvenTory.ReFormInvenItem();
			ReformCharForm();
			ResetInvenItemCode();
			cInvenTory.ReFormPotionNum();
			ResetPotion();
			cInvenTory.CheckWeight();
			SaveGameData();

		}
		break;
	case 3:
		cMessageBox.ShowMessage(MESSAGE_MYSHOP_ITEM_DOWN);
		break;
	case 4:
		cMessageBox.ShowMessage(MESSAGE_MYSHOP_CLOSE);
		break;
	case 5:
		cMessageBox.ShowMessage(MESSAGE_MYSHOP_NOT_SEARCH);
		break;
	case 6:
		index = cCharShop.SearchMyShopItem(lpShopItem->CODE, lpShopItem->Head, lpShopItem->CkSum);
		if (index)
		{
			if (MASK_CODE == sinPM1 || MASK_CODE == sinPL1 || MASK_CODE == sinPS1)
			{
				sRecvMyShop.sMyShopItem[index - 1].sItem.iPotionCount = lpShopItem->sTime;
				cCharShop.CharShopItem[index - 1].sItem.iPotionCount = lpShopItem->sTime;
				cMessageBox.ShowMessage(MESSAGE_MYSHOP_POTION_NUM2);
			}
		}
		break;
	case 7:
		index = cCharShop.SearchMyShopItem(lpShopItem->CODE, lpShopItem->Head, lpShopItem->CkSum);
		if (index)
		{
			sRecvMyShop.sMyShopItem[index - 1].Price = lpShopItem->Price;
			cCharShop.CharShopItem[index - 1].sItem.iSalePrice = lpShopItem->Price;
			cMessageBox.ShowMessage(MESSAGE_MYSHOP_CHANGE_PRICE);
		}
		break;
	}

	return TRUE;
}

int cCHARSHOP::RecvShopItem(sMYSHOP *sMyShop)
{
	char szFilePath[256];
	ItemData TempItem;
	for (int i = 0; i < 30; i++)
	{
		if (sMyShop->sMyShopItem[i].Price)
		{
			ItemData * pItem = ITEMHANDLE->GetItemDataByID(sMyShop->sMyShopItem[i].sItem.sItemID.ToInt());

			if (pItem)
			{
				wsprintf(szFilePath, "Image\\sinImage\\Items\\%s\\it%s.bmp", pItem->szCategory, pItem->szInventoryName);
				memcpy(&TempItem, pItem, sizeof(ItemData));

				memcpy(&TempItem.sItem, &sMyShop->sMyShopItem[i].sItem, sizeof(Item));
				if (!pItem->pcTempInventoryTexture)
					pItem->pcTempInventoryTexture = LoadDibSurfaceOffscreen(szFilePath);
				TempItem.pcInventoryTexture = pItem->pcTempInventoryTexture;
				TempItem.iPlaceX = sMyShop->sMyShopItem[i].Posi[0];
				TempItem.iPlaceY = sMyShop->sMyShopItem[i].Posi[1];
				memcpy(&CharShopItem[i], &TempItem, sizeof(ItemData));
				CharShopItem[i].bValid = 1;
			}
		}
	}
	memcpy(&sRecvMyShop, sMyShop, sizeof(sMYSHOP));
	cInterFace.CheckAllBox(SIN_CHARSHOP);
	return TRUE;
}
int cCHARSHOP::SearchMyShopItem(DWORD CODE, DWORD Head, DWORD CheckSum)
{
	for (int i = 0; i < 30; i++)
	{
		if (sRecvMyShop.sMyShopItem[i].sItem.iChk1 == Head && sRecvMyShop.sMyShopItem[i].sItem.iChk2 == CheckSum && sRecvMyShop.sMyShopItem[i].sItem.sItemID.ToInt() == CODE)
			return i + 1;
	}
	return FALSE;

}
int cCHARSHOP::SetCharShopItemToInven(Item *pItem_Info)
{
	char szTestBuff2[256];
	ItemData TempItem;
	szTestBuff2[0] = 0;
	memset(&TempItem, 0, sizeof(ItemData));

	ItemData * pItem = ITEMHANDLE->GetItemDataByID(pItem_Info->sItemID.ToInt());

	if (pItem)
	{
		wsprintf(szTestBuff2, "Image\\sinImage\\Items\\%s\\it%s.bmp", pItem->szCategory, pItem->szInventoryName);
		if (!pItem->pcTempInventoryTexture)
			pItem->pcTempInventoryTexture = LoadDibSurfaceOffscreen(szTestBuff2);
		memcpy(&TempItem, pItem, sizeof(ItemData));
		memcpy(&TempItem.sItem, pItem_Info, sizeof(Item));
		TempItem.pcInventoryTexture = pItem->pcTempInventoryTexture;
		TempItem.bValid = 1;
		cInvenTory.CheckRequireItemToSet(&TempItem);
		cInvenTory.AutoSetInvenItem(&TempItem);
		cInvenTory.ReFormInvenItem();
	}
	return TRUE;
}
int cCHARSHOP::BuyItem(int Index)
{
	int Index2 = 0;
	DWORD MASK_CODE = 0;
	memset(&MyShopPotion, 0, sizeof(Item));
	Index2 = cCharShop.SearchMyShopItem(cCharShop.CharShopItem[Index].sItem.sItemID.ToInt(), cCharShop.CharShopItem[SelectMyShopItemIndex - 1].sItem.iChk1, cCharShop.CharShopItem[Index].sItem.iChk2);
	if (Index2)
	{
		sMyShop_Server.Buyer = lpCurPlayer->iID;
		sMyShop_Server.CkSum = sRecvMyShop.sMyShopItem[Index2 - 1].sItem.iChk2;
		sMyShop_Server.Head = sRecvMyShop.sMyShopItem[Index2 - 1].sItem.iChk1;
		sMyShop_Server.Price = sRecvMyShop.sMyShopItem[Index2 - 1].Price;
		sMyShop_Server.sTime = sRecvMyShop.sMyShopItem[Index2 - 1].sItem.dwTime;
		sMyShop_Server.CODE = sRecvMyShop.sMyShopItem[Index2 - 1].sItem.sItemID.ToInt();
		sMyShop_Server.SendFlag = 1;
		TempItem.sBaseItemID = sRecvMyShop.sMyShopItem[Index2 - 1].sItem.sItemID.ToInt();

		MASK_CODE = (TempItem.sBaseItemID.ToInt() & sinITEM_MASK2);
		if (MASK_CODE == sinPM1 || MASK_CODE == sinPL1 || MASK_CODE == sinPS1)
		{
			if (cInvenTory.CheckInvenEmpty(&TempItem))
			{
				memcpy(&MyShopPotion, &sRecvMyShop.sMyShopItem[Index2 - 1].sItem, sizeof(Item));
				MyShopPotion.dwVersion = sRecvMyShop.sMyShopItem[Index2 - 1].Price;
				MyShopPotion.iPotionCount = cCharShop.CharShopItem[Index].sItem.iPotionCount;
				cMessageBox.ShowMessage2(MESSAGE_MYSHOP_POTION);
				return TRUE;
			}
			else
				cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
		}
		if ((sinChar->iGold - (int)sMyShop_Server.Price) >= 0)
		{
			if (cInvenTory.CheckInvenEmpty(&TempItem))
			{
				if (sinChar->sWeight.sMin + sRecvMyShop.sMyShopItem[Index2 - 1].sItem.iWeight <= sinChar->sWeight.sMax)
					cMessageBox.ShowMessage3(MESSAGE_MYSHOP_ITEM_BUY, sRecvMyShop.sMyShopItem[Index2 - 1].sItem.szItemName);
				else
					cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
			}
			else
				cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
		}
		else
			cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_MONEY);
	}
	return TRUE;
}
int cMYSHOP::GetLimitMoney(int Money)
{
	int CheckMoney = 0;
	if (sinChar->iLevel <= 10)
		return 200000 - (Money - sinChar->iGold);
	else
	{
		switch (sinChar->iRank)
		{
		case 0:
			return (((sinChar->iLevel * 200000) - 1800000) - (Money + sinChar->iGold));
			break;
		case 1:
			return ((10000000) - (Money + sinChar->iGold));
			break;
		case 2:
			return ((50000000) - (Money + sinChar->iGold));
			break;
		case 3:
			return ((100000000) - (Money + sinChar->iGold));
			break;
		case 4:
			return ((500000000) - (Money + sinChar->iGold));
			break;
		}
	}
	return FALSE;
}
int cMYSHOP::AutoCloseShop()
{
	int i = 0;
	int CheckFlag = 0;
	if (MyShopSendButton)
	{
		CheckFlag = 1;
		for (i = 0; i < 30; i++)
		{
			if (cMyShop.MyShopItem[i].bValid)
				CheckFlag = 2;
		}
	}
	if (MyShopSendButton)
	{
		if (CheckFlag == 1)
		{
			cMyShop.OpenFlag = 0;
			memset(cMyShop.MyShopItem, 0, sizeof(ItemData) * 30);
			memset(MyShopItemIndex, 0, sizeof(int) * 100);
			MyShopSendButton = 0;
			SendClosePersonalTrade();
		}
	}
	return TRUE;
}
int cMYSHOP::GetTotalMyShopItemMoney()
{
	int TotalMoney = 0;
	if (cMyShop.OpenFlag)
	{
		for (int i = 0; i < 30; i++)
		{
			if (cMyShop.MyShopItem[i].bValid)
			{
				if (cMyShop.MyShopItem[i].iItemSlotFlag == ITEMSLOTFLAG_Potion)
					TotalMoney += cMyShop.MyShopItem[i].sItem.iGold*cMyShop.MyShopItem[i].sItem.iPotionCount;
				else
					TotalMoney += cMyShop.MyShopItem[i].sItem.iGold;
			}
		}
	}
	return TotalMoney;
}
// 祝福冠军金钱比率
int cSHOP::haBuyMoneyCheck(int BuyMoney)
{
	if (sinChar->iGold - (BuyMoney + (BuyMoney*cSinSiege.GetTaxRate()) / 100) >= 0) {
		return TRUE;
	}
	return FALSE;
}
int cSHOP::haShopItemPrice(int Money)
{
	if (Money)
	{
		Money += ((Money*cSinSiege.GetTaxRate()) / 100);
		return Money;
	}
	return FALSE;
}