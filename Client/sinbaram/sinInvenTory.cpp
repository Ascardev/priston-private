#include "StdAfx.h"

#include "..\\tjboy\\clanmenu\\tjclanDEF.h"
#include "..\\tjboy\\clanmenu\\tjclan.h"

int LbuttonUpCheckFlag = 0;

int sinInterHeight2 = -50;

int sinTempDamage2[2] = { 0,0 };
int sinTempAbsorb = 0;
int sinTempBlock = 0;

Item TempLinkCoreItem;
POINT UnionCorePosi = { 0,0 };
int   sinOverWeightCnt = 0;
int sinMyShopItemPass = 0;

int nName = 0;
int nYesButton = 0;
int nNoButton = 0;
int BackUpPosX, BackUpPosY = 0;
int BackUpButton2X, BackUpButton2Y = 0;
int BackUpButton3X, BackUpButton3Y = 0;

cINVENTORY	cInvenTory;

sINVENTORY_EFFECT	sInven_Effect[MAX_INVEN_PARTICLE];
sINVENTORY_EFFECT   UnionCore_Effect[100];				//À¯´Ï¿Â ÄÚ¾î ÀÎº¥ ÆÄÆ¼Å¬ 
sINVENTORY_EFFECT   UnionCore_Effect_Bone[10];			//À¯´Ï¿Â ÄÚ¾î ÀÎº¥ ÆÄÆ¼Å¬ 
sINVENTORY_EFFECT   UnionCore_Effect_Bomb[50];			//À¯´Ï¿Â ÄÚ¾î ÅÍÁö´Â ÀÌÆåÆ®

sINVENTORY_EFFECT   ForceOrb_Effect;  //ForceOrb ÀÌÆåÆ® 
int MatForceOrbEffect[8] = { 0 };
ItemData MyShopMouseItem;

sELEMENT_ATTACK	sElement_Attack;
sUNIONCORE_EFFECT   sUCore_Effect[10];

int StartX;
int StartY;

int EndX;
int EndY;

int ColorIndex;					//ÄÃ·¯ ¹Ú½ºÀÇ ÀÎµ¦½º 
RECT ColorRect = { 0,0,0,0 };		//»öÀÌ Ç¥½ÃµÉ ¿µ¿ª 

int CrashItemIndex[2] = { 0,0 };	//¾ÆÀÌÅÛÀÌ 2°³ÀÌ»ó °ãÄ¡°ÔµÇ¸é ¼ÂÆÃÀ» ÇÒ¼ö¾ø´Ù 
int AutoSetItemIndex = 0;       //¾ç¼Õ¹«±â¸¦ ¼ÂÆÃÇÒ°æ¿ì ÀÚµ¿À¸·Î ¼ÂÆÃµÉ ¾ÆÀÌÅÛÀÇ ÀÎµ¦½º 

int SelectInvenItemIndex = 0;		//¼±ÅÃµÉ ¾ÆÀÌÅÛÀÇ ÀÎµ¦½º 

int SelectPotionIndex = 0;

int ArrowState[2] = { 0,0 };

int InvenArrowPosi = 0;

ItemData *pUsePotion = 0;          //»ç¿ëÇÒ Æ÷¼ÇÀÇ Æ÷ÀÎÅÍ 

int sinLoadOK = 0;				//·Îµå°¡ µÇ¸é 1À» ÁØ´Ù 

int PotionIndex = 0;              //¹Ú½º °Å·¡¸¦ À§ÇØ ÀÎµ¦½º¸¦ ÀúÀåÇÑ´Ù

ItemData *sinPosionItem = 0;        //¹°¾à ¹®Á¦ÇØ°áÀ» À§ÇÑ Æ÷ÀÎÅÍ 
int BackUpItemIndex = 0;		//¹°¾à ¹®Á¦ÇØ°ÜÀ» À§ÇÑ ¾ÆÀÌÅÛ ÀÎµ¦½º 
int NotPotionFlag = 0;			//¹°¾àÀ» Áý¾ú´ÂÁö ¾Æ´ÑÁö¸¦ Ã¤Å© 	

char sinTestBuff[128];			//Å×½ºÆ®¸¦ ÇÏ±âÀ§ÇÑ ¹öÆÛ 

int GhostPotionCheckFlag = 0;		// 'E'Å°·ÎÀÎÇÑ ¹°¾à »ç¶óÁö´Â ¹ö±×¸¦ ¼öÁ¤ÇÏ±âÀ§ÇÑ ³¯Ä¡±â ÇÃ·¢ 

int sinChangeSetFlag = 0;

int sinUsePotionDelayFlag = 0;
int PotionCheckNumJumpFlag = 1;

/////////////// ½ºÅ³°ü·Ã
int sinUndeadAbsorb = 0;

int sinItemPickUpDelayFlag = 0;
float   sinAdd_fMagic_Mastery = 0;			//¸¶¹ý¼÷·Ãµµ 
int sinDamageFunction[3] = { 0,0,0 };


int MatUnionCoreEffect = 0;


int IndiShopIconFlag = 0;


sWINGQUEST sWingQuest[MAX_WINGQUEST] =
{
	#include "sinWingItem.h"
};

int SpecialItemShowFlag = 0;
int NotChangeSetItemFlag = 0;
int PuzzleOkFlag = 0;

int PuzzleOkY = 0;

int sinTestFlag2 = 0;


sINVENTORY sInven[INVENTORY_MAX_POS] =
{
	{ITEMSLOTFLAG_RightHand  ,{574 + 1		, 433 + 1 , 640			, 544	}},
	{ITEMSLOTFLAG_LeftHand  ,{722 + 1		, 433 + 1 , 788			, 544	}},
	{ITEMSLOTFLAG_Armor  ,{648 + 1		, 433 + 1 , 714			, 544	}},
	{ITEMSLOTFLAG_Amulet ,{304 + 1		, 438 + 1 , 326			, 460	}},
	{ITEMSLOTFLAG_RingRight  ,{356 + 1		, 438 + 1 , 378			, 460	}},
	{ITEMSLOTFLAG_RingLeft  ,{330 + 1		, 438 + 1 , 352			, 460	}},
	{ITEMSLOTFLAG_Sheltom,{382 + 1		, 438 + 1 , 404			, 460	}},
	{ITEMSLOTFLAG_Bracelets ,{411 + 1		, 438 + 1 , 455			, 482	}},
	{ITEMSLOTFLAG_Gauntlets ,{462 + 1		, 438 + 1 , 506			, 482	}},
	{ITEMSLOTFLAG_Boots  ,{513 + 1		, 438 + 1 , 557			, 482	}},
	{ITEMSLOTFLAG_Potion ,{495			, 565   , 495 + 26		, 565 + 26}},
	{ITEMSLOTFLAG_Potion ,{495 + 26		, 565	, 495 + 26 + 26		, 565 + 26}},
	{ITEMSLOTFLAG_Potion ,{495 + 26 + 26	, 565	, 495 + 26 + 26 + 26	, 565 + 26}},
	{ITEMSLOTFLAG_Costume ,{648 + 1		, 433 + 1 , 714			, 544	}},
	{ITEMSLOTFLAG_WingRight  ,{574 + 1		, 433 + 1 , 640			, 544	}},
	{ITEMSLOTFLAG_WingLeft  ,{722 + 1		, 433 + 1 , 788			, 544	}}
};


int ArrowPosi[10][4] =
{
	{26,572,26 + 22,591},
	{48,572,48 + 22,591},
	{519,514,538,533},
	{541,514,560,533},
	{266,572,266 + 22,591},
	{302,467,321,486},
	{120,572,120 + 20,591},
	{70,572,70 + 22,591},
	{98,572,98 + 22,591},
	{497,514,516,533}
};


int InvenTextPosi[2][4] =
{
	{121,579,209,592},
	{322,473,404,486},

};
int ForceOrbUseLevel[][2] =
{
	{1,19},{1,29},{1,39},{1,49},{50,200},{50,200},{50,200},{50,200},{50,200},{50,200},{50,200},{50,200},{50,200},{50,200},{50,200},{50,200},
};

int ForceOrbUseTime[] = { 500,500,500,500,700,900,1800,2400,3600,4800,6000,7200,8400,10000,12000,14400 };

int ForceOrbDamage[] = { 2,4,7,10,15,25,40,60,80,100,120,140,160,180,200,220 };

int BoosterItem_UseTime[] = { 3600,10800,86400 };
int BoosterItem_DataPercent[] = { 15,15,15 };

// Àåº° - ½ºÅ³ µô·¹ÀÌ
int nSkillDelay_UseTime[] = { 300,10800,86400 };

/*----------------------------------------------------------------------------*
*						(ÀÎº¥ Åä¸®)ÀÎº¥  ÄÃ·¯ ÃÊ±âÈ­
*-----------------------------------------------------------------------------*/
DWORD sinInvenColor[7] = { D3DCOLOR_RGBA(160,235,256,128) , D3DCOLOR_RGBA(255,255,255,128) ,D3DCOLOR_RGBA(255,0,0,128),
					D3DCOLOR_RGBA(255,255,255,128) , D3DCOLOR_RGBA(255,200,0,128) ,D3DCOLOR_RGBA(0,231,123,128),
					D3DCOLOR_RGBA(173,203,247,128)

};

//ÀÏ°ö°¡Áö Å©¸®½ºÅ» º¸Àº  Å©¸®½ºÅ» ÄÚµå
DWORD CristalEventCODE[12] = { (sinGP1 | sin01),(sinGP1 | sin02),(sinGP1 | sin03),(sinGP1 | sin04),(sinGP1 | sin05)
						   ,(sinGP1 | sin06),(sinGP1 | sin07),(sinGP1 | sin08),(sinGP1 | sin09),
							(sinGP1 | sin11),(sinGP1 | sin12),(sinGP1 | sin13) };

//¹ÚÀç¿ø - ¼ö¹Ú ¸ð¾Æ¿À±â(È£¹Ú) //¹ÚÀç¿ø - ¹ãÇÏ´ÃÀÇ ¼Ò¿ø ÀÌº¥Æ®
DWORD WatermelonEventCODE = (sinSP1 | sin26);
// Àåº° - ¹ß·»Å¸ÀÎ ÀÌº¥Æ®
DWORD ValentineEventCODE = (sinSP1 | sin35);

// ¹ÚÀç¿ø - ¾ËÆÄºª Á¶ÇÕ ÀÌº¥Æ®
DWORD PristonAlphabetEventCODE[7] = { (sinSP1 | sin27), (sinSP1 | sin28), (sinSP1 | sin29),
									  (sinSP1 | sin30), (sinSP1 | sin31), (sinSP1 | sin32), (sinSP1 | sin33) };

// Àåº° - Äµµðµ¥ÀÌÁî
DWORD CandydaysEventCODE = (sinSP1 | sin36);

// Àåº° - ¸ÅÁöÄÃ±×¸°
DWORD MagicalGreenEventCODE[2] = { (sinSP1 | sin37), (sinSP1 | sin38) };

// Àåº° - Ä«¶óÀÇ ´«¹°
DWORD TeatOfKaraEventCODE = (sinSP1 | sin39);

// Àåº° - Á¶»ç¿øÀ» Ã£¾Æ¶ó - ¸¶·Â¿¬±¸ÀÚ
DWORD FindinvestigatorEventCODE[2] = { (sinGF1 | sin07), (sinGF1 | sin08) };

/*----------------------------------------------------------------------------*
*							Å¬·¡½º ÃÊ±â, Á¾·á
*-----------------------------------------------------------------------------*/
cINVENTORY::cINVENTORY()
{
	for (int i = 0; i < INVENTORY_MAXITEM; i++)
		memset(&InvenItem[i], 0, sizeof(ItemData));

}
cINVENTORY::~cINVENTORY()
{

}

void cINVENTORY::Init()
{
	StartX = 23;
	StartY = 436;

	EndX = StartX + ((INVENTORY_BOX_ROW) * 22);
	EndY = StartY + ((INVENTORY_BOX_COL) * 22);

	Load();

	ReformCharForm();
	SearchJobAndSetting();
	CheckWeight();
	SetItemToChar();

	sinSetLife(sinChar->sHP.sMax);
	sinSetMana(sinChar->sMP.sMax);
	sinSetStamina(sinChar->sSP.sMax);
	ReformCharForm();

	//dwLastTime = 0;
	ZeroMemory(dwLastTime, sizeof(dwLastTime));

	int i = 0;
	char szBuff[128];
	for (i = 0; i < 5; i++)
	{
		wsprintf(szBuff, "Image\\SinImage\\Effect\\Particle\\InvenPaticle%d.tga", i);
		MatInvenParticle[i] = CreateTextureMaterial(szBuff, 0, 0, 0, SMMAT_BLEND_ALPHA);
	}
	MatUnionCoreEffect = CreateTextureMaterial("image\\Sinimage\\Effect\\InterEffect\\UC-hall.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	LoadCharState();
}

void cINVENTORY::Load()
{
	char szBuff[128];
	for (int i = 0; i < 4; i++)
	{
		wsprintf(szBuff, "image\\Sinimage\\Effect\\InterEffect\\UC-0%d.bmp", i + 1);
		lpUnionCoreEffect[i] = LoadDibSurfaceOffscreen(szBuff);
	}

	lpIndiShopIcon = LoadDibSurfaceOffscreen("Image\\SinImage\\indishop\\indishop_icon.bmp");
	lpMyShopIcon_T = LoadDibSurfaceOffscreen("Image\\SinImage\\Inven\\InfoBox\\inven-SaleT.bmp");

	lpMyShopIcon = LoadDibSurfaceOffscreen("Image\\SinImage\\Inven\\inven-Sale.bmp");

	lpSpecialItem[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inven\\QuestItem_.bmp");
	lpSpecialItem[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inven\\QuestItem.bmp");

	lpSpecialItemInfo[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inven\\InfoBox\\Questitem.bmp");
	lpSpecialItemInfo[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inven\\InfoBox\\close.bmp");

	lpSpecialInven = LoadDibSurfaceOffscreen("Image\\SinImage\\Inven\\QuestItembox.bmp");
	lpCostumeUI = LoadDibSurfaceOffscreen("Image\\SinImage\\Inven\\Costume-UI.bmp");

	lpInvenMain[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inven\\Inven.bmp");
	lpInvenMain[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inven\\Inven2.bmp");

	lpInvenArrow[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inven\\LeftArrow.bmp");
	lpInvenArrow[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inven\\RightArrow.bmp");
	lpInvenArrow[2] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inven\\CArrow.bmp");

	lpCoverSmall = LoadDibSurfaceOffscreen("Image\\SinImage\\Inven\\CoverSmall.bmp");
	lpCoverMiddle = LoadDibSurfaceOffscreen("Image\\SinImage\\Inven\\CoverMiddle.bmp");
	lpCoverLarge = LoadDibSurfaceOffscreen("Image\\SinImage\\Inven\\CoverLarge.bmp");

	lpPotionBack = LoadDibSurfaceOffscreen("Image\\SinImage\\Inven\\PotionBack.bmp");

	lpChangeABInfo[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inven\\InfoBox\\ButtonA.bmp");
	lpChangeABInfo[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inven\\InfoBox\\ButtonB.bmp");
	lpConstmeInfo = LoadDibSurfaceOffscreen("Image\\SinImage\\Inven\\InfoBox\\Costume.bmp");

	lpExitInfo = LoadDibSurfaceOffscreen("Image\\SinImage\\Inven\\InfoBox\\ButtonExit.bmp");
	lpWeightInfo = LoadDibSurfaceOffscreen("Image\\SinImage\\Inven\\InfoBox\\ButtonWeight.bmp");

	lpItemABInfo[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inven\\InfoBox\\ButtonItemA.bmp");
	lpItemABInfo[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inven\\InfoBox\\ButtonItemB.bmp");

	lpShowWeaponClass[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\Items\\Weapon_Onehand.bmp");
	lpShowWeaponClass[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\Items\\Weapon_Twohand.bmp");
	lpShowWeaponClass[2] = LoadDibSurfaceOffscreen("Image\\SinImage\\Items\\Weapon_Knight.bmp");
	lpShowWeaponClass[3] = LoadDibSurfaceOffscreen("Image\\SinImage\\Items\\Weapon_Wizard.bmp");
	lpItemElementClass[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\Items\\ElementIcon\\Fire.png");
	lpItemElementClass[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\Items\\ElementIcon\\Ice.png");
	lpItemElementClass[2] = LoadDibSurfaceOffscreen("Image\\SinImage\\Items\\ElementIcon\\Lightning.png");

	lpPuzzleInven = LoadDibSurfaceOffscreen("Image\\SinImage\\Inven\\NYEAR_00.bmp");
	lpPuzzlewidth = LoadDibSurfaceOffscreen("Image\\SinImage\\Inven\\NYEAR_01.bmp");
	lpPuzzleHeight = LoadDibSurfaceOffscreen("Image\\SinImage\\Inven\\NYEAR_02.bmp");

}

void cINVENTORY::InvenItemLoad()
{
	char szFilePath[256];
	for (int i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].bValid)
		{
			ItemData *pItem = ITEMHANDLE->GetItemDataByID(InvenItem[i].sBaseItemID.ToInt());

			if (pItem)
			{
				wsprintf(szFilePath, "Image\\sinImage\\Items\\%s\\it%s.bmp", pItem->szCategory, pItem->szInventoryName);
				if (!pItem->pcTempInventoryTexture)
					pItem->pcTempInventoryTexture = LoadDibSurfaceOffscreen(szFilePath);
				InvenItem[i].pcInventoryTexture = pItem->pcTempInventoryTexture;
			}
		}
		if (InvenItemTemp[i].bValid)
		{
			ItemData *pItem = ITEMHANDLE->GetItemDataByID(InvenItemTemp[i].sBaseItemID.ToInt());

			if (pItem)
			{
				wsprintf(szFilePath, "Image\\sinImage\\Items\\%s\\it%s.bmp", pItem->szCategory, pItem->szInventoryName);
				if (!pItem->pcTempInventoryTexture)
					pItem->pcTempInventoryTexture = LoadDibSurfaceOffscreen(szFilePath);
				InvenItemTemp[i].pcInventoryTexture = pItem->pcTempInventoryTexture;
			}
		}
	}
}
void cINVENTORY::InvenItemRelease()
{
	int i = 0;

	for (i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].bValid)
			DELET(InvenItem[i].pcInventoryTexture);

		if (InvenItemTemp[i].bValid)
			DELET(InvenItemTemp[i].pcInventoryTexture);
	}
}
void cINVENTORY::Release()
{
	DELET(lpCoverSmall);
	DELET(lpCoverMiddle);
	DELET(lpCoverLarge);
	DELET(lpPotionBack);
	DELET(lpExitInfo);
	DELET(lpWeightInfo);
	DELET(lpSpecialInven);
	DELET(lpCostumeUI);
	DELET(lpConstmeInfo);
	DELET(lpGold7);
	DELET(lpExp7);
	for (int i = 0; i < 2; i++)
	{
		DELET(lpChangeABInfo[i]);
		DELET(lpItemABInfo[i]);
		DELET(lpInvenMain[i]);
		DELET(lpSpecialItem[i]);
		DELET(lpSpecialItemInfo[i]);
	}
	for (int i = 0; i < 3; i++)
	{
		DELET(lpItemElementClass[i]);
		DELET(lpInvenArrow[i]);
	}
	for (int i = 0; i < 4; i++)
	{
		DELET(lpShowWeaponClass[i]);
		DELET(lpUnionCoreEffect[i]);
	}
}

int CoreEffectTime = 0;
int CoreEffectFlag = 0;

void cINVENTORY::Draw()
{
	int i = 0;

	if (sinChar->iClass == CHARACTERCLASS_Assassin)
		DrawSprite(0, 600 - sinMoveKindInter[SIN_INVENTORY] + 56, lpInvenMain[1], 0, 0, 800, 200);
	else
		DrawSprite(0, 600 - sinMoveKindInter[SIN_INVENTORY] + 56, lpInvenMain[0], 0, 0, 800, 200);

	if (nName == 1)
	{
		Interface_clanmenu.DrawBox(BackStartPos.x, BackStartPos.y, 2, 3);
		dsDrawTexImage(MatHelpBoxImage[9], BackStartPos.x + 7, BackStartPos.y + 35, 180, 15, 255);


		dsDrawTexImage(MatMyShopPRBoxLine, BackStartPos.x + 28, BackStartPos.y - 120, 254, 30, 255);

		DrawSprite(BackStartPos.x + BackUpButton2X, BackStartPos.y + BackUpButton2Y - 200, cMessageBox.lpButtonBox07, 0, 0, 48, 23, 1);
		DrawSprite(BackStartPos.x + BackUpButton3X, BackStartPos.y + BackUpButton3Y - 200, cMessageBox.lpButtonBox07, 0, 0, 48, 23, 1);

		if (pCursorPos.x >= BackStartPos.x + BackUpButton2X && pCursorPos.x <= BackStartPos.x + BackUpButton2X + 48 && pCursorPos.y >= BackStartPos.y + BackUpButton2Y - 30 && pCursorPos.y <= BackStartPos.y + BackUpButton2Y - 7)
			nYesButton = 1;
		else
			nYesButton = 0;

		if (pCursorPos.x >= BackStartPos.x + BackUpButton3X && pCursorPos.x <= BackStartPos.x + BackUpButton3X + 48 && pCursorPos.y >= BackStartPos.y + BackUpButton2Y - 30 && pCursorPos.y <= BackStartPos.y + BackUpButton2Y - 7)
		{
			nNoButton = 1;
			nName = 0;
			isDrawClanMenu = 0;
			sinMessageBoxShowFlag = 0;
			hFocusWnd = 0;
			SetIME_Mode(FALSE);
		}
		else
			nNoButton = 0;

		if (nYesButton == 0)
			DrawSprite(BackStartPos.x + BackUpButton2X + 7, BackStartPos.y + BackUpButton2Y - 200 + 3, cMessageBox.lpButtonYesGlay07, 0, 0, 32, 16, 1);
		else
			DrawSprite(BackStartPos.x + BackUpButton2X + 7, BackStartPos.y + BackUpButton2Y - 200 + 3, cMessageBox.lpButtonYes07, 0, 0, 32, 16, 1);

		if (nNoButton == 0)
			DrawSprite(BackStartPos.x + BackUpButton3X + 7, BackStartPos.y + BackUpButton3Y - 200 + 3, cMessageBox.lpButtonNoGlay07, 0, 0, 32, 16, 1);
		else
			DrawSprite(BackStartPos.x + BackUpButton3X + 7, BackStartPos.y + BackUpButton3Y - 200 + 3, cMessageBox.lpButtonNo07, 0, 0, 32, 16, 1);
	}
	if (sinChar->CostmePos == FALSE)
	{
		for (i = 0; i < 3; i++)
		{
			if (sInven[i].ItemIndex && InvenItem[sInven[i].ItemIndex - 1].bValid)
				DrawSprite(sInven[i].Rect.left, sInven[i].Rect.top + (256 - sinMoveKindInter[SIN_INVENTORY]), lpCoverLarge, 0, 0, 66, 110);
		}
	}

	for (i = 3; i < 7; i++)
	{
		if (sInven[i].ItemIndex && InvenItem[sInven[i].ItemIndex - 1].bValid)
			DrawSprite(sInven[i].Rect.left, sInven[i].Rect.top + (256 - sinMoveKindInter[SIN_INVENTORY]), lpCoverSmall, 0, 0, 22, 22);
	}

	for (i = 7; i < 10; i++)
	{
		if (sInven[i].ItemIndex && InvenItem[sInven[i].ItemIndex - 1].bValid)
			DrawSprite(sInven[i].Rect.left, sInven[i].Rect.top + (256 - sinMoveKindInter[SIN_INVENTORY]), lpCoverMiddle, 0, 0, 44, 44);
	}

	if (ArrowState[0])
		DrawSprite(ArrowPosi[1][0], ArrowPosi[1][1] + (256 - sinMoveKindInter[SIN_INVENTORY]), lpInvenArrow[1], 0, 0, 20, 20);
	else
		DrawSprite(ArrowPosi[0][0], ArrowPosi[0][1] + (256 - sinMoveKindInter[SIN_INVENTORY]), lpInvenArrow[0], 0, 0, 20, 20);

	if (ArrowState[1])
		DrawSprite(ArrowPosi[3][0], ArrowPosi[3][1] + (256 - sinMoveKindInter[SIN_INVENTORY]), lpInvenArrow[1], 0, 0, 20, 20);
	else
		DrawSprite(ArrowPosi[2][0], ArrowPosi[2][1] + (256 - sinMoveKindInter[SIN_INVENTORY]), lpInvenArrow[0], 0, 0, 20, 20);

	if (sinChar->CostmePos == TRUE)
	{
		DrawSprite(ArrowPosi[9][0], ArrowPosi[9][1] + (256 - sinMoveKindInter[SIN_INVENTORY]), lpInvenArrow[2], 0, 0, 20, 20);
		DrawSprite(573, 436 + (256 - sinMoveKindInter[SIN_INVENTORY]), lpCostumeUI, 0, 0, 218, 111);

		for (i = 13; i < 16; i++)
		{
			if (sInven[i].ItemIndex && InvenItem[sInven[i].ItemIndex - 1].bValid)
				DrawSprite(sInven[i].Rect.left, sInven[i].Rect.top + (256 - sinMoveKindInter[SIN_INVENTORY]), lpCoverLarge, 0, 0, 66, 110);
		}
	}

	DrawSprite(sInven[10].Rect.left, sInven[10].Rect.top, lpPotionBack, 0, 0, 77, 25);


	if (!SpecialItemShowFlag)
		DrawSprite(ArrowPosi[7][0], ArrowPosi[7][1] + (256 - sinMoveKindInter[SIN_INVENTORY]), lpSpecialItem[0], 0, 0, 20, 20);
	else
	{
		for (i = 0; i < 6; i++)
		{
			for (int j = 0; j < 3; j++)
				DrawSprite(StartX + (i * 44), StartY + (j * 44) + (256 - sinMoveKindInter[SIN_INVENTORY]), lpSpecialInven, 0, 0, 44, 44);
		}

		DrawSprite(ArrowPosi[7][0], ArrowPosi[7][1] + (256 - sinMoveKindInter[SIN_INVENTORY]), lpSpecialItem[1], 0, 0, 20, 20);
	}

	switch (ColorIndex)
	{
	case SET_ITEM_CHECK_COLOR:
		if (MouseItem.bValid)
			dsDrawColorBox(sinInvenColor[0],
				ColorRect.left,
				ColorRect.top + (256 - sinMoveKindInter[SIN_INVENTORY]),
				ColorRect.right,
				ColorRect.bottom);
		break;
	case OVERLAP_ITEM_COLOR:
		if (CrashItemIndex[0])
			dsDrawColorBox(sinInvenColor[1],
				InvenItem[CrashItemIndex[0] - 1].iPlaceX,
				InvenItem[CrashItemIndex[0] - 1].iPlaceY + (256 - sinMoveKindInter[SIN_INVENTORY]),
				InvenItem[CrashItemIndex[0] - 1].iWidth,
				InvenItem[CrashItemIndex[0] - 1].iHeight);
		break;
	case NOT_SETTING_COLOR:
		dsDrawColorBox(sinInvenColor[2], ColorRect.left, ColorRect.top + (256 - sinMoveKindInter[SIN_INVENTORY]), ColorRect.right, ColorRect.bottom);
		break;
	case NOT_USE_COLOR:
		dsDrawColorBox(sinInvenColor[2], ColorRect.left, ColorRect.top + (256 - sinMoveKindInter[SIN_INVENTORY]), ColorRect.right, ColorRect.bottom);
		break;
	case OVERLAP_BOX_COLOR:
		if (CrashItemIndex[0])
			dsDrawColorBox(sinInvenColor[1],
				sInven[InvenItem[CrashItemIndex[0] - 1].iItemSlot - 1].Rect.left,
				sInven[InvenItem[CrashItemIndex[0] - 1].iItemSlot - 1].Rect.top + (256 - sinMoveKindInter[SIN_INVENTORY]),
				sInven[InvenItem[CrashItemIndex[0] - 1].iItemSlot - 1].Rect.right - sInven[InvenItem[CrashItemIndex[0] - 1].iItemSlot - 1].Rect.left,
				sInven[InvenItem[CrashItemIndex[0] - 1].iItemSlot - 1].Rect.bottom - sInven[InvenItem[CrashItemIndex[0] - 1].iItemSlot - 1].Rect.top);
		break;
	case SELECT_ITEM_COLOR:
		if (!SelectInvenItemIndex)
			break;
		if (InvenItem[SelectInvenItemIndex - 1].iItemSlot)
			dsDrawColorBox(sinInvenColor[4],
				sInven[InvenItem[SelectInvenItemIndex - 1].iItemSlot - 1].Rect.left,
				sInven[InvenItem[SelectInvenItemIndex - 1].iItemSlot - 1].Rect.top + (256 - sinMoveKindInter[SIN_INVENTORY]),
				sInven[InvenItem[SelectInvenItemIndex - 1].iItemSlot - 1].Rect.right - sInven[InvenItem[SelectInvenItemIndex - 1].iItemSlot - 1].Rect.left,
				sInven[InvenItem[SelectInvenItemIndex - 1].iItemSlot - 1].Rect.bottom - sInven[InvenItem[SelectInvenItemIndex - 1].iItemSlot - 1].Rect.top);
		else
			dsDrawColorBox(sinInvenColor[4],
				InvenItem[SelectInvenItemIndex - 1].iPlaceX,
				InvenItem[SelectInvenItemIndex - 1].iPlaceY + (256 - sinMoveKindInter[SIN_INVENTORY]),
				InvenItem[SelectInvenItemIndex - 1].iWidth,
				InvenItem[SelectInvenItemIndex - 1].iHeight);
		break;

	}
	for (i = 0; i < 10; i++)
	{
		if (sUCore_Effect[i].Flag && sUCore_Effect[i].Time > 0)
			dsDrawTexImage(sUCore_Effect[i].MatNum,
				sUCore_Effect[i].x,
				sUCore_Effect[i].y,
				sUCore_Effect[i].w,
				sUCore_Effect[i].h,
				sUCore_Effect[i].Alpha);
	}

	for (int cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if (InvenItem[cnt].bValid == 1)
		{
			if (InvenItem[cnt].sItem.sItemID.ToItemType() == sinPZ1 || InvenItem[cnt].sItem.sItemID.ToItemType() == sinPZ2)
				DrawSprite(StartX + (22 * 8), sInven[0].Rect.top + (256 - sinMoveKindInter[SIN_INVENTORY]) + 2, lpPuzzleInven, 0, 0, 88, 88);

			if (InvenItem[cnt].sItem.bCanNotUse && !MyShopItemIndex[cnt])
			{
				if (sinChar->CostmePos == TRUE)
				{
					if (InvenItem[cnt].iItemSlot != 1 &&
						InvenItem[cnt].iItemSlot != 2 &&
						InvenItem[cnt].iItemSlot != 3)
					{
						dsDrawColorBox(sinInvenColor[2],
							InvenItem[cnt].iPlaceX,
							InvenItem[cnt].iPlaceY + (256 - sinMoveKindInter[SIN_INVENTORY]),
							InvenItem[cnt].iWidth,
							InvenItem[cnt].iHeight);
						if (InvenItem[cnt].iItemSlot != 0)
							dsDrawColorBox(sinInvenColor[2],
								sInven[InvenItem[cnt].iItemSlot - 1].Rect.left,
								sInven[InvenItem[cnt].iItemSlot - 1].Rect.top + (256 - sinMoveKindInter[SIN_INVENTORY]),
								sInven[InvenItem[cnt].iItemSlot - 1].Rect.right - sInven[InvenItem[cnt].iItemSlot - 1].Rect.left,
								sInven[InvenItem[cnt].iItemSlot - 1].Rect.bottom - sInven[InvenItem[cnt].iItemSlot - 1].Rect.top);
					}
				}
				else
				{
					if (InvenItem[cnt].iItemSlot != 14 &&
						InvenItem[cnt].iItemSlot != 15 &&
						InvenItem[cnt].iItemSlot != 16)
					{
						dsDrawColorBox(sinInvenColor[2],
							InvenItem[cnt].iPlaceX,
							InvenItem[cnt].iPlaceY + (256 - sinMoveKindInter[SIN_INVENTORY]),
							InvenItem[cnt].iWidth,
							InvenItem[cnt].iHeight);
						if (InvenItem[cnt].iItemSlot != 0)
							dsDrawColorBox(sinInvenColor[2],
								sInven[InvenItem[cnt].iItemSlot - 1].Rect.left,
								sInven[InvenItem[cnt].iItemSlot - 1].Rect.top + (256 - sinMoveKindInter[SIN_INVENTORY]),
								sInven[InvenItem[cnt].iItemSlot - 1].Rect.right - sInven[InvenItem[cnt].iItemSlot - 1].Rect.left,
								sInven[InvenItem[cnt].iItemSlot - 1].Rect.bottom - sInven[InvenItem[cnt].iItemSlot - 1].Rect.top);
					}
				}
			}
		}
	}

	for (i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].bValid)
		{
			if (InvenItem[i].iItemSlot != 11 &&
				InvenItem[i].iItemSlot != 12 &&
				InvenItem[i].iItemSlot != 13)
			{
				if (MyShopItemIndex[i])
					dsDrawColorBox(D3DCOLOR_RGBA(45, 133, 255, 180),
						InvenItem[i].iPlaceX,
						InvenItem[i].iPlaceY + (256 - sinMoveKindInter[SIN_INVENTORY]),
						InvenItem[i].iWidth,
						InvenItem[i].iHeight);

				if (sinChar->CostmePos == TRUE)
				{
					if (InvenItem[i].iItemSlot == 1 ||
						InvenItem[i].iItemSlot == 2 ||
						InvenItem[i].iItemSlot == 3)
						continue;
				}
				else
				{
					if (InvenItem[i].iItemSlot == 14 ||
						InvenItem[i].iItemSlot == 15 ||
						InvenItem[i].iItemSlot == 16)
						continue;
				}

				DrawSprite(InvenItem[i].iPlaceX,
					InvenItem[i].iPlaceY + (256 - sinMoveKindInter[SIN_INVENTORY]),
					(smTEXTUREHANDLE *)InvenItem[i].pcInventoryTexture,
					0,
					0,
					InvenItem[i].iWidth,
					InvenItem[i].iHeight);

				if (!((smTEXTUREHANDLE *)(InvenItem[i].pcInventoryTexture))->m_pTexture)
				{
					if (InvenItem[i].iPlaceX > 10)
						dsDrawColorBox(D3DCOLOR_RGBA(125 + (i * 10), 125 + (i * 10), 255 + (i * 10), 125 + (i * 10)),
							InvenItem[i].iPlaceX,
							InvenItem[i].iPlaceY + (256 - sinMoveKindInter[SIN_INVENTORY]),
							InvenItem[i].iWidth,
							InvenItem[i].iHeight);
				}
				if ((InvenItem[i].sBaseItemID.ToInt() & sinITEM_MASK2) == sinFO1)
					DrawForceOrbEffect(InvenItem[i].iPlaceX,
						InvenItem[i].iPlaceY + (256 - sinMoveKindInter[SIN_INVENTORY]));
			}
			else
				DrawSprite(InvenItem[i].iPlaceX,
					InvenItem[i].iPlaceY,
					(smTEXTUREHANDLE *)InvenItem[i].pcInventoryTexture,
					0,
					0,
					InvenItem[i].iWidth,
					InvenItem[i].iHeight);
		}
	}

	if (PuzzleOkFlag)
	{
		dsDrawColorBox(D3DCOLOR_RGBA(255, 255, 0, 30), StartX + (22 * 8), sInven[0].Rect.top + (256 - sinMoveKindInter[SIN_INVENTORY]) + 2, 88, 88);

		dsDrawColorBox(D3DCOLOR_RGBA(255, 123, 0, 180), StartX + (22 * 8), PuzzleOkY + sInven[0].Rect.top + (256 - sinMoveKindInter[SIN_INVENTORY]) + 4, 88, 2);
		dsDrawColorBox(D3DCOLOR_RGBA(255, 123, 0, 180), StartX + (22 * 8), (80 - PuzzleOkY) + sInven[0].Rect.top + (256 - sinMoveKindInter[SIN_INVENTORY]) + 4, 88, 2);
	}

	int len = 0;
	if (CoreEffectFlag == 0)
		CoreEffectTime++;
	else
		CoreEffectTime--;

	if (CoreEffectTime > 38)
		CoreEffectFlag = 1;
	else if (CoreEffectTime < 1)
		CoreEffectFlag = 0;


	for (i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].bValid)
		{
			if (InvenItem[i].sItem.sItemID.ToInt() == (sinEC1 | sin05))
			{
				len = lstrlen(InvenItem[i].sItem.szItemName);
				if (InvenItem[i].sItem.szItemName[len + 1] != NULL)
					DrawSprite(InvenItem[i].iPlaceX,
						InvenItem[i].iPlaceY + (256 - sinMoveKindInter[SIN_INVENTORY]),
						lpUnionCoreEffect[CoreEffectTime / 10],
						0,
						0, 
						44,
						22);
			}
		}
	}
	switch (InvenArrowPosi)
	{
	case 1:
		DrawSprite(ArrowPosi[0][0], ArrowPosi[0][1] + (256 - sinMoveKindInter[SIN_INVENTORY]), lpInvenArrow[0], 0, 0, 20, 20);
		DrawSprite(ArrowPosi[0][0], ArrowPosi[0][1] - 27 + (256 - sinMoveKindInter[SIN_INVENTORY]), lpItemABInfo[0], 0, 0, 57, 27);
		break;
	case 2:
		DrawSprite(ArrowPosi[1][0], ArrowPosi[1][1] + (256 - sinMoveKindInter[SIN_INVENTORY]), lpInvenArrow[1], 0, 0, 20, 20);
		DrawSprite(ArrowPosi[1][0], ArrowPosi[1][1] - 27 + (256 - sinMoveKindInter[SIN_INVENTORY]), lpItemABInfo[1], 0, 0, 57, 27);
		break;
	case 3:
		DrawSprite(ArrowPosi[2][0], ArrowPosi[2][1] + (256 - sinMoveKindInter[SIN_INVENTORY]), lpInvenArrow[0], 0, 0, 20, 20);
		DrawSprite(ArrowPosi[2][0], ArrowPosi[2][1] - 27 + (256 - sinMoveKindInter[SIN_INVENTORY]), lpChangeABInfo[0], 0, 0, 70, 27);
		break;
	case 4:
		DrawSprite(ArrowPosi[3][0], ArrowPosi[3][1] + (256 - sinMoveKindInter[SIN_INVENTORY]), lpInvenArrow[1], 0, 0, 20, 20);
		DrawSprite(ArrowPosi[3][0], ArrowPosi[3][1] - 27 + (256 - sinMoveKindInter[SIN_INVENTORY]), lpChangeABInfo[1], 0, 0, 70, 27);
		break;
	case 5:
		DrawSprite(ArrowPosi[4][0], ArrowPosi[4][1] + (256 - sinMoveKindInter[SIN_INVENTORY]), cShop.lpExit, 0, 0, 20, 20);
		DrawSprite(ArrowPosi[4][0] - 8, ArrowPosi[4][1] - 27 + (256 - sinMoveKindInter[SIN_INVENTORY]), lpExitInfo, 0, 0, 47, 27);
		break;
	case 6:
		break;
	case 8:
		if (!SpecialItemShowFlag)
		{
			DrawSprite(ArrowPosi[7][0], ArrowPosi[7][1] + (256 - sinMoveKindInter[SIN_INVENTORY]), lpSpecialItem[1], 0, 0, 20, 20);
			DrawSprite(ArrowPosi[7][0], ArrowPosi[7][1] - 27 + (256 - sinMoveKindInter[SIN_INVENTORY]), lpSpecialItemInfo[0], 0, 0, 100, 27);
		}
		else
		{
			DrawSprite(ArrowPosi[7][0], ArrowPosi[7][1] + (256 - sinMoveKindInter[SIN_INVENTORY]), lpSpecialItem[1], 0, 0, 20, 20);
			DrawSprite(ArrowPosi[7][0], ArrowPosi[7][1] - 27 + (256 - sinMoveKindInter[SIN_INVENTORY]), lpSpecialItemInfo[1], 0, 0, 70, 27);
		}
		break;
	case 9:
		DrawSprite(ArrowPosi[8][0], ArrowPosi[8][1] + (256 - sinMoveKindInter[SIN_INVENTORY]), lpMyShopIcon, 0, 0, 20, 20);
		DrawSprite(ArrowPosi[8][0] - 39, ArrowPosi[8][1] - 27 + (256 - sinMoveKindInter[SIN_INVENTORY]), lpMyShopIcon_T, 0, 0, 100, 26);
		break;
	case 10:
		//×Ô¶¨Òå
		DrawSprite(ArrowPosi[9][0], ArrowPosi[9][1] + (256 - sinMoveKindInter[SIN_INVENTORY]), lpInvenArrow[2], 0, 0, 20, 20);
		DrawSprite(ArrowPosi[9][0], ArrowPosi[9][1] - 27 + (256 - sinMoveKindInter[SIN_INVENTORY]), lpConstmeInfo, 0, 0, 80, 27);
		break;
	}

	if (sinSkill.pLeftSkill)
	{
		if (sinSkill.pLeftSkill->UseSkillFlag)
			DrawSprite(sLeftRightSkill[0].BoxRect.left, sLeftRightSkill[0].BoxRect.top, cSkill.lpSkillButton[sinSkill.pLeftSkill->Position - 1], 0, 0, 40, 40);
		else
			DrawSprite(sLeftRightSkill[0].BoxRect.left, sLeftRightSkill[0].BoxRect.top, cSkill.lpSkillButton_Gray[sinSkill.pLeftSkill->Position - 1], 0, 0, 40, 40);

	}
	if (sinSkill.pRightSkill)
	{
		if (sinSkill.pRightSkill->UseSkillFlag)
			DrawSprite(sLeftRightSkill[1].BoxRect.left, sLeftRightSkill[1].BoxRect.top, cSkill.lpSkillButton[sinSkill.pRightSkill->Position - 1], 0, 0, 40, 40);
		else
			DrawSprite(sLeftRightSkill[1].BoxRect.left, sLeftRightSkill[1].BoxRect.top, cSkill.lpSkillButton_Gray[sinSkill.pRightSkill->Position - 1], 0, 0, 40, 40);
	}

	for (i = 0; i < 100; i++)
	{
		if (UnionCore_Effect[i].Flag)
			cInvenTory.sinDrawInvenTexImage(&UnionCore_Effect[i].InvenFace);
	}

	for (i = 0; i < 50; i++)
	{
		if (UnionCore_Effect_Bomb[i].Flag)
			cInvenTory.sinDrawInvenTexImage(&UnionCore_Effect_Bomb[i].InvenFace);
	}
	if (IndiShopIconFlag)
	{
		DrawSprite(225, 570, lpIndiShopIcon, 0, 0, 27, 25);
		DrawSprite(225 - 35, 570 - 27, cShop.lpMyShop_T, 0, 0, 100, 26);
	}
}

int InvenMainCount = 0;
int SetDelayFlag = 0;
bool bGiftBoxDelay = false;
DWORD dwUsePotionDelayTime = 0;
DWORD dwCheckHackCharStateTime = 0;
DWORD dwCheckHackCharStateFlag = 0;
DWORD dwCheckPickUpItemTime = 0;
int	  CharToItemFirstFlag = 0;
DWORD CharToItemFirstTime = 0;
DWORD dwUseCristalDelayTime = 0;
int   sinUseCristalDelayFlag = 0;


DWORD dwCheckAutoMouseTime = 0;

int   CheckPosiFlag = 0;
#define   CHECKAUTOMOUSE_DISTANCE		(200*200)
#define   CHECKAUTOMOUSE_SETITEM_MAX	500
#define   CHECKAUTOMOUSE_TIME			(70*60*30)

int   CheckX = 0, CheckZ = 0;
int   CheckResultX = 0, CheckResultZ = 0;

DWORD dwPuzzleOkTime = 0;
int ReversEffectFlag = 0;
DWORD dwForceOrbTime = 0;
int   ForceOrbEffectIndex = 0;
void cINVENTORY::Main()
{
	dwForceOrbTime++;
	if (dwForceOrbTime > 8)
	{
		dwForceOrbTime = 0;
		ForceOrbEffectIndex++;
		if (ForceOrbEffectIndex > 7)
			ForceOrbEffectIndex = 0;
	}

	if (PuzzleOkFlag)
	{
		dwPuzzleOkTime++;
		if (dwPuzzleOkTime > 2)
		{
			dwPuzzleOkTime = 0;
			if (PuzzleOkY > 82)
				ReversEffectFlag = 1;
			if (ReversEffectFlag)
			{
				PuzzleOkY--;
				if (PuzzleOkY <= 0)
					ReversEffectFlag = 0;
			}
			else
				PuzzleOkY++;
		}
	}
	else
	{
		PuzzleOkY = 0;
		dwPuzzleOkTime = 0;
	}

	int dist = 0;

	if (!CheckPosiFlag)
	{
		CheckX = lpCurPlayer->pX;
		CheckZ = lpCurPlayer->pZ;
		CheckPosiFlag = 1;
	}

	dwCheckAutoMouseTime++;
	if (dwCheckAutoMouseTime >= CHECKAUTOMOUSE_TIME)
	{
		if (sinOverWeightCnt > CHECKAUTOMOUSE_SETITEM_MAX)
		{
			CheckResultX = (lpCurPlayer->pX - CheckX) >> FLOATNS;
			CheckResultZ = (lpCurPlayer->pZ - CheckZ) >> FLOATNS;
			dist = CheckResultX * CheckResultX + CheckResultZ * CheckResultZ;
			if (CHECKAUTOMOUSE_DISTANCE >= dist)
			{
				sinOverWeightCnt = 0;
				CheckPosiFlag = 0;
				dwCheckAutoMouseTime = 0;
			}
			else
			{
				sinOverWeightCnt = 0;
				CheckPosiFlag = 0;
				dwCheckAutoMouseTime = 0;
			}
		}
		else
		{
			sinOverWeightCnt = 0;
			CheckPosiFlag = 0;
			dwCheckAutoMouseTime = 0;
		}
	}
	if (sinUseCristalDelayFlag)
	{
		dwUseCristalDelayTime++;
		if (dwUseCristalDelayTime > 70)
		{
			sinUseCristalDelayFlag = 0;
			dwUseCristalDelayTime = 0;
		}
	}

	UnionCoreParticleProcess();
	dwCheckHackCharStateTime++;
	if (dwCheckHackCharStateTime >= 30 * 70)
	{
		SetItemToChar(TRUE);
		dwCheckHackCharStateTime = 0;
	}
	if (sinUsePotionDelayFlag)
	{
		dwUsePotionDelayTime++;
		if (dwUsePotionDelayTime > 50)
		{
			dwUsePotionDelayTime = 0;
			sinUsePotionDelayFlag = 0;
		}
	}

	if (SetDelayFlag)
	{
		InvenMainCount++;
		if (InvenMainCount >= 70)
		{
			SetDelayFlag = 0;
			InvenMainCount = 0;
		}

	}
	if (nName)
	{
		BackUpButton2X = 35;
		BackUpButton2Y = 157;
		BackUpButton3X = 115;
		BackUpButton3Y = 157;

		BackUpPosX = BackStartPos.x;
		BackUpPosY = BackStartPos.y;

		if (pCursorPos.x >= BackStartPos.x + BackUpButton2X && pCursorPos.x <= BackStartPos.x + BackUpButton2X + 48 && pCursorPos.y >= BackStartPos.y + BackUpButton2Y - 30 && pCursorPos.y <= BackStartPos.y + BackUpButton2Y - 7)
			nYesButton = 1;

		if (pCursorPos.x >= BackStartPos.x + BackUpButton3X && pCursorPos.x <= BackStartPos.x + BackUpButton3X + 48 && pCursorPos.y >= BackStartPos.y + BackUpButton2Y - 30 && pCursorPos.y <= BackStartPos.y + BackUpButton2Y - 7)
			nNoButton = 1;

		BackStartPos.x = BackUpPosX;
		BackStartPos.y = BackUpPosY;

	}
	if (bGiftBoxDelay)
	{
		InvenMainCount++;
		if (InvenMainCount >= 140)
		{
			bGiftBoxDelay = false;
			InvenMainCount = 0;
		}
	}
	InvenArrowPosi = 0;
	int i = 0;
	if (OpenFlag)
	{
		for (i = 0; i < 10; i++)
		{
			if (ArrowPosi[i][0] < pCursorPos.x  && ArrowPosi[i][2] > pCursorPos.x  && ArrowPosi[i][1] < pCursorPos.y  && ArrowPosi[i][3] > pCursorPos.y)
				InvenArrowPosi = i + 1;
		}
	}

	for (i = 0; i < 3; i++)
	{
		if (sInven[i + 10].Rect.left < pCursorPos.x  && sInven[i + 10].Rect.right > pCursorPos.x  && sInven[i + 10].Rect.top < pCursorPos.y  && sInven[i + 10].Rect.bottom > pCursorPos.y)
			cHelpPet.PetMessage("*Potion_ShortKey", 0);
	}

	PickUpInvenItem(pCursorPos.x, pCursorPos.y);

	int BackdsDrawOffsetArray = 0;
	if (MouseItem.bValid)
	{
		SetInvenItemAreaCheck(&MouseItem);
		sinItemPickUpDelayFlag = 1;
	}
	if (sinItemPickUpDelayFlag)
	{
		dwCheckPickUpItemTime++;
		if (dwCheckPickUpItemTime > 70)
		{
			sinItemPickUpDelayFlag = 0;
			dwCheckPickUpItemTime = 0;
		}
	}
	else
	{
		sinItemPickUpDelayFlag = 0;
		dwCheckPickUpItemTime = 0;
	}

	if (!PotionCheckNumJumpFlag)
		CheckPotionNumForm();

	if (!CharToItemFirstFlag)
	{
		CharToItemFirstTime++;
		if (CharToItemFirstTime >= 70 * 3)
		{
			SetItemToChar(0);
			SetItemToChar();
			CharToItemFirstFlag = 1;
		}
	}
}

void cINVENTORY::Close()
{
	Release();
}
int sinButtonFlag = 0;
void cINVENTORY::LButtonDown(int x, int y)
{
	if (nYesButton == 1)
	{
		lstrcpy(cInvenTory.szSendDoc, cInvenTory.szDoc);
		SetIME_Mode(FALSE);
		nName = 0;
		isDrawClanMenu = 0;
		sinMessageBoxShowFlag = 0;
		hFocusWnd = 0;
		SendsServerDoc(cInvenTory.szSendDoc);
	}

	if (nNoButton == 1)
	{
		SetIME_Mode(FALSE);
		nName = 0;
		isDrawClanMenu = 0;
		sinMessageBoxShowFlag = 0;
		hFocusWnd = 0;
	}
	int i = 0;

	for (i = 0; i < 3; i++)
	{
		if (sInven[i + 10].Rect.left < pCursorPos.x  && sInven[i + 10].Rect.right > pCursorPos.x  && sInven[i + 10].Rect.top < pCursorPos.y  && sInven[i + 10].Rect.bottom > pCursorPos.y)
			cHelpPet.PetMessage("*Potion_ShortKey", 1);
	}
	if (InvenArrowPosi && InvenArrowPosi < 5)
	{
		if (sinButtonFlag == InvenArrowPosi)
			return;
		sinButtonFlag = InvenArrowPosi;

		if (InvenArrowPosi <= 2)
			ChangeABItem(InvenArrowPosi);
		if (InvenArrowPosi >= 3)
			sinChangeSetFlag = InvenArrowPosi;
	}
	else if (InvenArrowPosi == 5)
		OpenFlag = 0;

	else if (InvenArrowPosi == 7)
	{
		if (!MouseItem.bValid)
		{
			if (!cTrade.OpenFlag && !cMyShop.OpenFlag && !MyShopSendButton && !cCharShop.OpenFlag && !sSinWarpGate.ShowFlag)
				cMessageBox.ShowMessage2(MESSAGE_THROW_MONEY);
			if (cWareHouse.OpenFlag)
				cMessageBox.ShowMessage2(MESSAGE_MOVE_MONEY_MOVE);
		}
	}
	else if (InvenArrowPosi == 8)
	{
		if (!cTrade.OpenFlag && !cWareHouse.OpenFlag && !cCraftItem.OpenFlag && !cMyShop.OpenFlag && !cCharShop.OpenFlag && !MyShopSendButton && !cCaravan.OpenFlag)
			ChangeSpecialItem();
	}
	else if (InvenArrowPosi == 9)
	{
		if (!MouseItem.bValid)
			cInterFace.CheckAllBox(SIN_MYSHOP);
	}
	else if (InvenArrowPosi == 10)
	{
		//if (SetDelayTime(5,0))
			//return;
		sinChar->CostmePos ^= TRUE;

		if (sinChar->CostmePos == TRUE)
			sinChangeSetFlag = 5;
		else
			sinChangeSetFlag = 6;
	}

	if (bGiftBoxDelay)
		return;

	if (sinCraftItemStartFlag || StartInterEffectAging2)
		return;
	else if ((ManufactureItem.m_OpenFlag || SmeltingItem.OpenFlag) && MixCancelButtonDelayFlag)
		return;
	if (MouseItem.bValid)
	{
		if (cInvenTory.OpenFlag && MouseItem.sItem.SpecialItemFlag[1] == ITEMCRAFTTYPE_Special)
		{
			if (ColorIndex == OVERLAP_ITEM_COLOR || ColorIndex == SET_ITEM_CHECK_COLOR)
			{
				if (!SpecialItemShowFlag)
				{
					cInvenTory.UnionCoreParticle2(MouseItem.iPlaceX, MouseItem.iPlaceY);
					sinPlaySound(SIN_SOUND_EAT_POTION2);
				}
				SetSpecialItem(&MouseItem);
				MouseItem.bValid = 0;
				ReFormInvenItem();
				ReformCharForm();
				return;
			}
		}

		if (SpecialItemShowFlag)
			return;
		if (SetDelayFlag)
			return;

		if (!sSinWarpGate.ShowFlag)
			ThrowInvenItemToField(&MouseItem);

		if (ColorIndex == NO_BOX_COLOR || ColorIndex == NOT_SETTING_COLOR)
			return;
		if (!CheckSetOk(&MouseItem))
			return;
		if (MouseItem.iItemSlotFlag == ITEMSLOTFLAG_Potion)
		{
			if (!MouseSetPotion(&MouseItem))
			{
				if (MouseItem.bValid)
					NoSettingThrowItem(&MouseItem);
			}
			else
				CheckWeight();
		}
		else
		{
			if (!ChangeInvenItem(&MouseItem))
			{
				if (MouseItem.iItemSlot)
				{
					if (sInven[MouseItem.iItemSlot - 1].ItemIndex && InvenItem[sInven[MouseItem.iItemSlot - 1].ItemIndex - 1].bValid)
						return;
				}
				if (!LastSetInvenItem(&MouseItem))
				{
					if (MouseItem.bValid)
					{
						if ((MouseItem.sItem.sItemID.ToItemType()) == sinMA1 ||
							(MouseItem.sItem.sItemID.ToItemType()) == sinMA2 ||
							(MouseItem.sItem.sItemID.ToItemType()) == sinQT1 ||
							(MouseItem.sItem.sItemID.ToItemType()) == sinQW1)
						{

						}
						else
							NoSettingThrowItem(&MouseItem);
					}
				}
			}
		}
	}
	else
	{
		if (lpCurPlayer->psModelAnimation->iType == ANIMATIONTYPE_Attack || lpCurPlayer->psModelAnimation->iType == ANIMATIONTYPE_Skill)
			return;

		pMessageItem = 0;
		CheckInvenItemForm();
		if (cMyShop.OpenFlag)
			PickUpInvenItem(pCursorPos.x, pCursorPos.y, 2);
		else
		{
			if (!MyShopSendButton && !cCharShop.OpenFlag && !sSinWarpGate.ShowFlag)
				PickUpInvenItem(pCursorPos.x, pCursorPos.y, 1);
		}
		ReFormInvenItem();
		if (MouseItem.bValid)
		{
			if (MouseItem.iItemSlotFlag != ITEMSLOTFLAG_Potion)
				CopyItemClear(&MouseItem);
		}
	}
	if (MouseItem.bValid)
		LbuttonUpCheckFlag = 1;
}
void cINVENTORY::LButtonUp(int x, int y)
{
	LbuttonUpCheckFlag = 0;
	sinMyShopItemPass = 0;
}

DWORD dwBoosterItemCode[] = { sin21,sin22,sin23,sin24,sin25,sin26,sin27,sin28,sin29,0 };
DWORD dwCastlItemCODE[] = { sin01,sin02,sin03,sin04,sin05,sin06,sin07,sin08,sin09,sin10,sin11,sin12,sin13,sin14,sin15,sin16,sin17,sin18,0 };
DWORD dwNotUseVillageItemCODE[3] =
{
	(sinBI1 | sin05),
	(sinBI1 | sin06),
	(sinBI1 | sin07)
};
DWORD dwNotUseItemCODE[6][3] =
{
	{SCROLL_INVULNERABILITY		,(sinBC1 | sin01),1},
	{SCROLL_CRITICAL			,(sinBC1 | sin02),2},
	{SCROLL_EVASION				,(sinBC1 | sin03),3},
	{SCROLL_P_INVULNERABILITY	,(sinBI1 | sin05),1},
	{SCROLL_P_CRITICAL			,(sinBI1 | sin06),2},
	{SCROLL_P_EVASION			,(sinBI1 | sin07),3}
};
DWORD dwSkillDelayItemCode[] = { sin30,sin31,sin32, 0 };


// ÎïÆ·ÓÒ¼üÊó±ê
void cINVENTORY::RButtonDown(int x, int y)
{
	if (MouseItem.bValid || sinItemPickUpDelayFlag)
		return;

	int i = 0;
	for (i = 0; i < 3; i++)
	{
		if (sInven[i + 10].Rect.left < pCursorPos.x  && sInven[i + 10].Rect.right > pCursorPos.x  && sInven[i + 10].Rect.top < pCursorPos.y  && sInven[i + 10].Rect.bottom > pCursorPos.y)
			cHelpPet.PetMessage("*Potion_ShortKey", 2);
	}
	for (int j = 0; j < SIN_MAX_HELP_NUMBER; j++)
	{
		if (sSinHelp[j].KindFlag == SIN_HELP_KIND_TELEPORT_SCROLL)
			return;
	}

	if (MouseItem.bValid)
		return;
	if (cWareHouse.OpenFlag || cTrade.OpenFlag || cCraftItem.OpenFlag || cShop.OpenFlag || cAging.OpenFlag || cMixtureReset.OpenFlag || cMyShop.OpenFlag || cCharShop.OpenFlag || SmeltingItem.OpenFlag || ManufactureItem.m_OpenFlag || cElement.OpenFlag || cCaravan.OpenFlag || cSocket.OpenFlag)
		return;
	UsePotion(x, y);

	if (SelectInvenItemIndex)
	{
		cHelpPet.PetMessage("*InvenTory_Item", 2);

		// Á¦Á¿Ê¯Í·
		if ((InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() & sinITEM_MASK2) == sinFO1)
		{
			if (((InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() & sinITEM_MASK3) >= sin01) && ((InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() & sinITEM_MASK3) <= sin16))
				UseForceOrb(&InvenItem[SelectInvenItemIndex - 1]);
		}

		if ((InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() & sinITEM_MASK2) == sinEC1)
			UseEcore(&InvenItem[SelectInvenItemIndex - 1]);

		if ((InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() & sinITEM_MASK2) == sinSP1)
		{
			if (InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() == (sinSP1 | sin16))
				return;
			if (InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() == (sinSP1 | sin05) ||
				InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() == (sinSP1 | sin06) ||
				InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() == (sinSP1 | sin07) ||
				InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() == (sinSP1 | sin08) ||
				InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() == (sinSP1 | sin09) ||
				InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() == (sinSP1 | sin10))
			{
				ItemData temp;
				temp = InvenItem[SelectInvenItemIndex - 1];
				if (!CheckInvenEmpty(&temp))
				{
					cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
					return;
				}
				if (sinChar->sWeight.sMin + 10 >= sinChar->sWeight.sMax)
				{
					cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
					return;
				}

				bGiftBoxDelay = true;
				if (sinActionPotion())
				{
					pUsePotion = &InvenItem[SelectInvenItemIndex - 1];
					sinUsePotionDelayFlag = 1;
				}
			}
			else if (InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() == (sinSP1 | sin34))
			{
				UseCapsuleItem(&InvenItem[SelectInvenItemIndex - 1]);
			}
			else if (InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() == (sinSP1 | sin15))
			{
				if (sinActionPotion())
					pUsePotion = &InvenItem[SelectInvenItemIndex - 1];
			}
			else if (InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() == (sinSP1 | sin26))
			{
				return;
			}
			else if (InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() == (sinSP1 | sin27) ||
				InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() == (sinSP1 | sin28) ||
				InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() == (sinSP1 | sin29) ||
				InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() == (sinSP1 | sin30) ||
				InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() == (sinSP1 | sin31) ||
				InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() == (sinSP1 | sin32) ||
				InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() == (sinSP1 | sin33))
			{
				return;
			}
			else if (InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() == (sinSP1 | sin35))
			{
				if (sinActionPotion())
					pUsePotion = &InvenItem[SelectInvenItemIndex - 1];
			}
			else if (InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() == (sinSP1 | sin36))
			{
				if (sinActionPotion())
					pUsePotion = &InvenItem[SelectInvenItemIndex - 1];
			}

			else if (InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() == (sinSP1 | sin37) ||
				InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() == (sinSP1 | sin38))
				return;

			else if (InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() == (sinSP1 | sin39))
				return;

			else if (InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() == (sinSP1 | sin42))
			{
				if (sinActionPotion())
					pUsePotion = &InvenItem[SelectInvenItemIndex - 1];
			}
			else if (InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() == (sinSP1 | sin64) ||
				InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() == (sinSP1 | sin65) ||
				InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() == (sinSP1 | sin66) ||
				InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() == (sinSP1 | sin67) ||
				InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() == (sinSP1 | sin68))
				return;
			else
			{
				if (sinActionPotion())
					pUsePotion = &InvenItem[SelectInvenItemIndex - 1];
			}
		}

		if ((InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() &sinITEM_MASK2) == sinGP1)
		{
			if (lpCurPlayer->iLoadedMapIndex >= 0 &&
				STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapType == MAPTYPE_Town)
				return;

			if (InvenItem[SelectInvenItemIndex - 1].sItem.sItemID.ToInt() == (sinGP1 | sin17) ||
				InvenItem[SelectInvenItemIndex - 1].sItem.sItemID.ToInt() == (sinGP1 | sin18) ||
				InvenItem[SelectInvenItemIndex - 1].sItem.sItemID.ToInt() == (sinGP1 | sin19) ||
				InvenItem[SelectInvenItemIndex - 1].sItem.sItemID.ToInt() == (sinGP1 | sin20))
			{
				if (chaPremiumitem.haItemUseDelayFlag)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_DELAYTIME);
					return;
				}
			}
			if (InvenItem[SelectInvenItemIndex - 1].sItem.iLevel > sinChar->iLevel)
				return;

			if (InvenItem[SelectInvenItemIndex - 1].sItem.sItemID.ToInt() == (sinGP1 | sin10) ||
				InvenItem[SelectInvenItemIndex - 1].sItem.sItemID.ToInt() == (sinGP1 | sin22))
			{
				if (!sinChar->iClanID || cldata.stats[0] != '1')
				{
					cMessageBox.ShowMessage(MESSAGE_USE_REGULAR_CLAN_ONLY);
					return;
				}
				else
				{
					if (!sinUseCristalDelayFlag)
						sinUseCristalDelayFlag = 1;
					else
						return;
				}
			}
			if (SetDelayTime(5, 1))
				return;
			if (!sinItemPickUpDelayFlag)
			{
				InvenItem[SelectInvenItemIndex - 1].sItem.iPotionCount = 100;
				sinThrowItemToFeild(&InvenItem[SelectInvenItemIndex - 1]);
				InvenItem[SelectInvenItemIndex - 1].bValid = 0;
				cInvenTory.CheckWeight();
				ReFormInvenItem();
				chaPremiumitem.haItemUseDelayFlag = true;
			}
		}
		for (i = 0; i < 6; i++)
		{
			if (cSkill.SearchContiueSkillCODE(dwNotUseItemCODE[i][0]))
			{
				for (int j = 0; j < 6; j++)
				{
					if (InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() == dwNotUseItemCODE[j][1] && dwNotUseItemCODE[j][1] != dwNotUseItemCODE[i][1])
					{
						if (dwNotUseItemCODE[j][2] == dwNotUseItemCODE[i][2])
						{
							cMessageBox.ShowMessage(MESSAGE_ASATTRIBUTE_USE);
							return;
						}
					}
				}
			}
		}
		if ((InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() & sinITEM_MASK2) == sinBC1)
		{
			if (lpCurPlayer->iLoadedMapIndex >= 0 &&
				STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID != rsCASTLE_FIELD &&
				(InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() & sinITEM_MASK3) <= sin18)
				return;

			if (InvenItem[SelectInvenItemIndex - 1].sItem.sItemID.ToInt() == (sinBC1 | sin05))
				return;

			for (i = 0; i < 18; i++)
			{
				if ((InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() & sinITEM_MASK3) == dwCastlItemCODE[i])
				{
					chaSiege.SetCastleItemSkill(i + 1);
					SetItemToChar();
					break;
				}
			}
			if (((InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() &sinITEM_MASK3) >= sin21) && ((InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() &sinITEM_MASK3) <= sin29))
				cSkill.UseBoosterItem(&InvenItem[SelectInvenItemIndex - 1]);

			if (((InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() &sinITEM_MASK3) >= sin30))
				cSkill.UseSkillDelayItem(&InvenItem[SelectInvenItemIndex - 1]);

			if (haCastleSkillUseFlag != 1)
				return;

			if (!sinItemPickUpDelayFlag)
			{
				InvenItem[SelectInvenItemIndex - 1].sItem.iPotionCount = 200;
				sinThrowItemToFeild(&InvenItem[SelectInvenItemIndex - 1]);
				InvenItem[SelectInvenItemIndex - 1].bValid = 0;
				cInvenTory.CheckWeight();
				ReFormInvenItem();
			}
		}
		if ((InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() &sinITEM_MASK2) == sinBI1 || (InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() &sinITEM_MASK2) == sinBI2)
		{
			chaPremiumitem.TelePortCore.ItemIndex = 0;
			if (lpCurPlayer->iLoadedMapIndex >= 0 &&
				STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapType == MAPTYPE_Town)
			{
				for (int i = 0; i < 3; i++)
				{
					if (InvenItem[SelectInvenItemIndex - 1].sItem.sItemID.ToInt() == dwNotUseVillageItemCODE[i])
						return;
				}
			}

			iEventBuyItemKind = 0;

			if (SetDelayTime(5, 1))
				return;

			switch (InvenItem[SelectInvenItemIndex - 1].sItem.sItemID.ToInt())
			{
			case sinBI1 | sin01:
				chaPremiumitem.UsePremiumItem(1);
				break;
			case sinBI1 | sin02:
				chaPremiumitem.UsePremiumItem(2);
				break;
			case sinBI1 | sin03:
				chaPremiumitem.UsePremiumItem(3);
				break;
			case sinBI1 | sin04:
				return;
			case sinBI1 | sin05:
				chaPremiumitem.UsePremiumItem(5);
				break;
			case sinBI1 | sin06:
				for (i = 0; i < SIN_MAX_SKILL_LIST; i++)
				{
					if (ContinueSkill[i].CODE == SCROLL_P_EVASION)
					{
						if (ContinueSkill[i].Flag)
						{
							cMessageBox.ShowMessage(MESSAGE_NO_USE_ITEM);
							return;
						}
					}
				}
				chaPremiumitem.UsePremiumItem(6);
				break;
			case sinBI1 | sin07:
				for (i = 0; i < SIN_MAX_SKILL_LIST; i++)
				{
					if (ContinueSkill[i].CODE == SCROLL_P_CRITICAL)
					{
						if (ContinueSkill[i].Flag)
						{
							cMessageBox.ShowMessage(MESSAGE_NO_USE_ITEM);
							return;
						}
					}
				}
				chaPremiumitem.UsePremiumItem(7);
				break;
			case sinBI1 | sin08:
				chaPremiumitem.TelePortCore.ItemIndex = SelectInvenItemIndex - 1;
				chaPremiumitem.UsePremiumItem(8);
				break;
			case sinBI1 | sin09:
				if (chaPremiumitem.m_BigHeadTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}
				chaPremiumitem.UsePremiumItem(9);
				break;
			case sinBI1 | sin10:
				chaPremiumitem.UsePremiumItem(10);
				break;
			case sinBI1 | sin11:
				chaPremiumitem.UsePremiumItem(11);
				break;
			case sinBI1 | sin12:
				if (chaPremiumitem.m_ThirdEyesTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				chaPremiumitem.UsePremiumItem(12);
				break;
			case sinBI1 | sin13:
				if (chaPremiumitem.m_ExpUpPotionTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				chaPremiumitem.UsePremiumItem(13);
				break;
			case sinBI1 | sin14:
				if (chaPremiumitem.m_ThirdEyesTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				chaPremiumitem.UsePremiumItem(14);
				break;
			case sinBI1 | sin15:
				if (chaPremiumitem.m_ExpUpPotionTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}
				chaPremiumitem.UsePremiumItem(15);
				break;
			case sinBI1 | sin16:
				chaPremiumitem.UsePremiumItem(16);
				break;
			case sinBI1 | sin17:
				chaPremiumitem.UsePremiumItem(17);
				break;
			case sinBI1 | sin18:
				chaPremiumitem.UsePremiumItem(18);
				break;
			case sinBI1 | sin19:
				if (chaPremiumitem.m_VampiricCuspidTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				chaPremiumitem.UsePremiumItem(19);
				break;
			case sinBI1 | sin20:
				if (chaPremiumitem.m_VampiricCuspidTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				chaPremiumitem.UsePremiumItem(20);
				break;
			case sinBI1 | sin21:
				if (chaPremiumitem.m_ManaRechargingPTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				chaPremiumitem.UsePremiumItem(21);
				break;
			case sinBI1 | sin22:
				if (chaPremiumitem.m_ManaRechargingPTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				chaPremiumitem.UsePremiumItem(22);
				break;
			case sinBI1 | sin23:
				chaPremiumitem.UsePremiumItem(23);
				break;
			case sinBI2 | sin01:
				chaPremiumitem.UsePremiumItem(24);
				break;
			case sinBI2 | sin02:
				chaPremiumitem.UsePremiumItem(25);
				break;
			case sinBI2 | sin03:
				chaPremiumitem.UsePremiumItem(26);
				break;
			case sinBI2 | sin04:
				chaPremiumitem.UsePremiumItem(27);
				break;
			case sinBI2 | sin05:
				chaPremiumitem.UsePremiumItem(28);
				break;
			case sinBI2 | sin06:
				chaPremiumitem.UsePremiumItem(29);
				break;
			case sinBI2 | sin07:
				chaPremiumitem.UsePremiumItem(30);
				break;
			case sinBI2 | sin08:
				chaPremiumitem.UsePremiumItem(31);
				break;
			case sinBI2 | sin09:
				chaPremiumitem.UsePremiumItem(32);
				break;
			case sinBI2 | sin10:
				chaPremiumitem.UsePremiumItem(33);
				break;
			case sinBI2 | sin11:
				chaPremiumitem.UsePremiumItem(34);
				break;
			case sinBI2 | sin12:
				chaPremiumitem.UsePremiumItem(35);
				break;
			case sinBI2 | sin13:
				chaPremiumitem.UsePremiumItem(36);
				break;
			case sinBI2 | sin14:
				chaPremiumitem.UsePremiumItem(37);
				break;
			case sinBI2 | sin15:
				chaPremiumitem.UsePremiumItem(38);
				break;
			case sinBI2 | sin16:
				chaPremiumitem.UsePremiumItem(39);
				break;
			case sinBI2 | sin17:
				chaPremiumitem.UsePremiumItem(40);
				break;
			case sinBI2 | sin18:
				chaPremiumitem.UsePremiumItem(41);
				break;
			case sinBI2 | sin19:
				chaPremiumitem.UsePremiumItem(42);
				break;
			case sinBI2 | sin20:
				chaPremiumitem.UsePremiumItem(43);
				break;
			case sinBI2 | sin21:
				chaPremiumitem.UsePremiumItem(44);
				break;
			case sinBI2 | sin22:
				chaPremiumitem.UsePremiumItem(45);
				break;
			case sinBI1 | sin24:
				chaPremiumitem.UsePremiumItem(46);
				break;
			case sinBI1 | sin25:
				chaPremiumitem.UsePremiumItem(47);
				break;
			case sinBI1 | sin26:
				chaPremiumitem.UsePremiumItem(48);
				break;
			case sinBI1 | sin27:
				chaPremiumitem.UsePremiumItem(49);
				break;
			case sinBI1 | sin28:
				if (chaPremiumitem.m_ManaReducePotiontime > 0)
					return;

				chaPremiumitem.UsePremiumItem(50);
				break;
			case sinBI1 | sin29:
				if (chaPremiumitem.m_ManaReducePotiontime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}
				chaPremiumitem.UsePremiumItem(51);
				break;
			case sinBI2 | sin26:
				chaPremiumitem.UsePremiumItem(52);
				break;
			case sinBI2 | sin27:
				chaPremiumitem.UsePremiumItem(53);
				break;
			case sinBI2 | sin28:
				chaPremiumitem.UsePremiumItem(54);
				break;
			case sinBI2 | sin29:
				chaPremiumitem.UsePremiumItem(55);
				break;
			case sinBI2 | sin30:
				chaPremiumitem.UsePremiumItem(56);
				break;
			case sinBI2 | sin31:
				chaPremiumitem.UsePremiumItem(57);
				break;
			case sinBI2 | sin32:
				chaPremiumitem.UsePremiumItem(58);
				break;
			case sinBI2 | sin33:
				chaPremiumitem.UsePremiumItem(59);
				break;
			case sinBI2 | sin34:
				chaPremiumitem.UsePremiumItem(60);
				break;
			case sinBI2 | sin35:
				chaPremiumitem.UsePremiumItem(61);
				break;
			case sinBI2 | sin36:
				chaPremiumitem.UsePremiumItem(62);
				break;
			case sinBI2 | sin37:
				chaPremiumitem.UsePremiumItem(63);
				break;
			case sinBI1 | sin30:
				chaPremiumitem.UsePremiumItem(64);
				break;
			case sinBI1 | sin31:
				chaPremiumitem.UsePremiumItem(65);
				break;
			case sinBI2 | sin23:
				chaPremiumitem.UsePremiumItem(66);
				break;
			case sinBI2 | sin24:
				chaPremiumitem.UsePremiumItem(67);
				break;
			case sinBI2 | sin25:
				chaPremiumitem.UsePremiumItem(68);
				break;
			case sinBI1 | sin36:
				if (!cInvenTory.InvenItem[sInven[0].ItemIndex - 1].bValid ||
					!cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.bMaturing)
				{
					cMessageBox.ShowMessage(MESSAGE_HAVE_NOT_AGINGITEM);
					return;
				}
				chaPremiumitem.UsePremiumItem(73);
				break;
			case sinBI1 | sin37:
				if (!cInvenTory.InvenItem[sInven[1].ItemIndex - 1].bValid ||
					!cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sItem.bMaturing)
				{
					cMessageBox.ShowMessage(MESSAGE_HAVE_NOT_AGINGITEM);
					return;
				}
				chaPremiumitem.UsePremiumItem(74);
				break;
			case sinBI1 | sin38:
				if (!cInvenTory.InvenItem[sInven[2].ItemIndex - 1].bValid ||
					!cInvenTory.InvenItem[sInven[2].ItemIndex - 1].sItem.bMaturing)
				{
					cMessageBox.ShowMessage(MESSAGE_HAVE_NOT_AGINGITEM);
					return;
				}
				chaPremiumitem.UsePremiumItem(75);
				break;
			case sinBI1 | sin39:
				if (cSkill.CheckMaturedSkill(1) == FALSE)
				{
					cMessageBox.ShowMessage(MESSAGE_HAVE_NOT_MATURESKILL);
					return;
				}
				chaPremiumitem.UsePremiumItem(76);
				break;
			case sinBI1 | sin40:
				if (cSkill.CheckMaturedSkill(2) == FALSE)
				{
					cMessageBox.ShowMessage(MESSAGE_HAVE_NOT_MATURESKILL);
					return;
				}
				chaPremiumitem.UsePremiumItem(77);
				break;
			case sinBI1 | sin41:
				if (cSkill.CheckMaturedSkill(3) == 0)
				{
					cMessageBox.ShowMessage(MESSAGE_HAVE_NOT_MATURESKILL);
					return;
				}
				chaPremiumitem.UsePremiumItem(78);
				break;
			case sinBI1 | sin42:
				if (STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapType == MAPTYPE_ChessRoom ||
					STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == MAPID_RicartenTown ||
					STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == MAPID_PhillaiTown ||
					STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == rsCASTLE_FIELD ||
					STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == rsSOD_FIELD ||
					STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == MAPID_Eura)
				{
					cMessageBox.ShowMessage(MESSAGE_NO_USE_ITEM);
					return;
				}
				iEventBuyItemKind = 79;
				chaPremiumitem.Using_SelectInvenItemIndex = SelectInvenItemIndex - 1;
				cMessageBox.ShowMessage3(MESSAGE_EVENT_ITEMOK, InvenItem[SelectInvenItemIndex - 1].sItem.szItemName);
				break;
			case sinBI1 | sin43:
				if (chaPremiumitem.m_ExpUpPotionTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				chaPremiumitem.UsePremiumItem(80);
				break;
			case sinBI1 | sin44:
				if (chaPremiumitem.m_ExpUpPotionTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}
				chaPremiumitem.UsePremiumItem(81);
				break;
			case sinBI1 | sin45:
				chaPremiumitem.UsePremiumItem(82);
				break;
			case sinBI1 | sin46:
				chaPremiumitem.UsePremiumItem(83);
				break;
			case sinBI1 | sin47:
				chaPremiumitem.UsePremiumItem(84);
				break;
			case sinBI1 | sin48:
				chaPremiumitem.UsePremiumItem(85);
				break;
			case sinBI1 | sin49:
				chaPremiumitem.UsePremiumItem(86);
				break;
			case sinBI1 | sin50:
				if (chaPremiumitem.m_ExpUpPotionTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				chaPremiumitem.UsePremiumItem(87);
				break;
			case sinBI1 | sin60:
				chaPremiumitem.UsePremiumItem(97);
				break;
			case sinBI1 | sin61:
				chaPremiumitem.UsePremiumItem(98);
				break;
			case sinBI1 | sin52:
				if (sinChar->iLevel < 10)
				{
					cMessageBox.ShowMessage(MESSAGE_PET_USE_LEVEL);
					return;
				}
				chaPremiumitem.UsePremiumItem(99);
				break;
			case sinBI1 | sin53:
				if (sinChar->iLevel < 10)
				{
					cMessageBox.ShowMessage(MESSAGE_PET_USE_LEVEL);
					return;
				}
				chaPremiumitem.UsePremiumItem(100);
				break;
			case sinBI1 | sin54:
				if (sinChar->iLevel < 10)
				{
					cMessageBox.ShowMessage(MESSAGE_PET_USE_LEVEL);
					return;
				}
				chaPremiumitem.UsePremiumItem(101);
				break;
			case sinBI1 | sin55:
				if (sinChar->iLevel < 10)
				{
					cMessageBox.ShowMessage(MESSAGE_PET_USE_LEVEL);
					return;
				}
				chaPremiumitem.UsePremiumItem(102);
				break;
			case sinBI1 | sin69:
				if (sinChar->iLevel < 10)
				{
					cMessageBox.ShowMessage(MESSAGE_PET_USE_LEVEL);
					return;
				}
				chaPremiumitem.UsePremiumItem(103);
				break;
			case sinBI1 | sin70:
				if (sinChar->iLevel < 10)
				{
					cMessageBox.ShowMessage(MESSAGE_PET_USE_LEVEL);
					return;
				}
				chaPremiumitem.UsePremiumItem(104);
				break;
			case sinBI1 | sin71:
				if (sinChar->iLevel < 10)
				{
					cMessageBox.ShowMessage(MESSAGE_PET_USE_LEVEL);
					return;
				}
				chaPremiumitem.UsePremiumItem(105);
				break;
			case sinBI1 | sin72:
				if (sinChar->iLevel < 10)
				{
					cMessageBox.ShowMessage(MESSAGE_PET_USE_LEVEL);
					return;
				}
				chaPremiumitem.UsePremiumItem(106);
				break;
			case sinBI1 | sin80:
				if (chaPremiumitem.m_ExpUpPotionTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				chaPremiumitem.UsePremiumItem(107);
				break;
			case sinBI1 | sin65:
				if (sinChar->iLevel < 10)
				{
					cMessageBox.ShowMessage(MESSAGE_PET_USE_LEVEL);
					return;
				}
				chaPremiumitem.UsePremiumItem(109);
				break;
			case sinBI1 | sin66:
				if (sinChar->iLevel < 10)
				{
					cMessageBox.ShowMessage(MESSAGE_PET_USE_LEVEL);
					return;
				}
				chaPremiumitem.UsePremiumItem(110);
				break;
			case sinBI1 | sin67:
				if (sinChar->iLevel < 10)
				{
					cMessageBox.ShowMessage(MESSAGE_PET_USE_LEVEL);
					return;
				}
				chaPremiumitem.UsePremiumItem(111);
				break;
			case sinBI1 | sin68:
				if (sinChar->iLevel < 10)
				{
					cMessageBox.ShowMessage(MESSAGE_PET_USE_LEVEL);
					return;
				}
				chaPremiumitem.UsePremiumItem(112);
				break;
			case sinBI1 | sin62:
				if (!cInvenTory.InvenItem[sInven[7].ItemIndex - 1].bValid ||
					!cInvenTory.InvenItem[sInven[7].ItemIndex - 1].sItem.bMaturing)
				{
					cMessageBox.ShowMessage(MESSAGE_HAVE_NOT_AGINGITEM);
					return;
				}
				chaPremiumitem.UsePremiumItem(113);
				break;
			case sinBI1 | sin63:
				if (!cInvenTory.InvenItem[sInven[8].ItemIndex - 1].bValid ||
					!cInvenTory.InvenItem[sInven[8].ItemIndex - 1].sItem.bMaturing)
				{
					cMessageBox.ShowMessage(MESSAGE_HAVE_NOT_AGINGITEM);
					return;
				}
				chaPremiumitem.UsePremiumItem(114);
				break;
			case sinBI1 | sin64:
				if (!cInvenTory.InvenItem[sInven[9].ItemIndex - 1].bValid ||
					!cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItem.bMaturing)
				{
					cMessageBox.ShowMessage(MESSAGE_HAVE_NOT_AGINGITEM);
					return;
				}
				chaPremiumitem.UsePremiumItem(115);
				break;
			case sinBI1 | sin84:
				chaPremiumitem.UsePremiumItem(116);
				break;
			case sinBI1 | sin73:
				if (sinChar->iLevel < 10)
				{
					cMessageBox.ShowMessage(MESSAGE_PET_USE_LEVEL);
					return;
				}
				chaPremiumitem.UsePremiumItem(117);
				break;
			case sinBI1 | sin74:
				if (sinChar->iLevel < 10)
				{
					cMessageBox.ShowMessage(MESSAGE_PET_USE_LEVEL);
					return;
				}
				chaPremiumitem.UsePremiumItem(118);
				break;
			case sinBI1 | sin75:
				if (sinChar->iLevel < 10)
				{
					cMessageBox.ShowMessage(MESSAGE_PET_USE_LEVEL);
					return;
				}
				chaPremiumitem.UsePremiumItem(119);
				break;
			case sinBI1 | sin76:
				if (sinChar->iLevel < 10)
				{
					cMessageBox.ShowMessage(MESSAGE_PET_USE_LEVEL);
					return;
				}
				chaPremiumitem.UsePremiumItem(120);
				break;
			case sinBI1 | sin78:
				if (chaPremiumitem.m_ThirdEyesTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}
				chaPremiumitem.UsePremiumItem(121);
				break;
			case sinBI1 | sin85:
				chaPremiumitem.UsePremiumItem(122);
				break;
			case sinBI1 | sin79:
				if (chaPremiumitem.m_ExpUpPotionTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}
				chaPremiumitem.UsePremiumItem(123);
				break;
			case sinBI1 | sin81:
				if (chaPremiumitem.m_VampiricCuspidTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}
				chaPremiumitem.UsePremiumItem(124);
				break;
			case sinBI1 | sin82:
				if (chaPremiumitem.m_ManaRechargingPTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}
				chaPremiumitem.UsePremiumItem(125);
				break;
			case sinBI1 | sin83:
				if (chaPremiumitem.m_ManaReducePotiontime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}
				chaPremiumitem.UsePremiumItem(126);
				break;
			case sinBI1 | sin86:
				break;
			case sinBI1 | sin87:
				break;
			case sinBI1 | sin88:
				break;
			case sinBI1 | sin89:
				chaPremiumitem.UsePremiumItem(130);
				break;
			case sinBI1 | sin90:
				chaPremiumitem.UsePremiumItem(131);
				break;
			case sinBI1 | sin91:
				if (chaPremiumitem.m_StaminaReducePotiontime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}
				chaPremiumitem.UsePremiumItem(132);
				break;
			case sinBI1 | sin92:
				if (chaPremiumitem.m_StaminaReducePotiontime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}
				chaPremiumitem.UsePremiumItem(133);
				break;
			case sinBI1 | sin93:
				if (sinChar->iLevel > 19)
				{
					chaPremiumitem.TelePortCore.ItemIndex = SelectInvenItemIndex - 1;
					chaPremiumitem.UsePremiumItem(134);
				}
				else
					cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_LEVEL);
				break;
			case sinBI1 | sin94:
				if (sinChar->iLevel > 19)
				{
					chaPremiumitem.TelePortCore.ItemIndex = SelectInvenItemIndex - 1;
					chaPremiumitem.UsePremiumItem(135);
				}
				else
					cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_LEVEL);
				break;
			case sinBI1 | sin95:
			case sinBI2 | sin69:
			case sinBI2 | sin70:
			case sinBI2 | sin71:
			case sinBI2 | sin72:
			case sinBI2 | sin73:
			case sinBI2 | sin74:
			case sinBI2 | sin77:
				if (chaPremiumitem.m_Caravan_HopyTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}
				chaPremiumitem.UsePremiumItem(136);
				break;
			case sinBI1 | sin96:
			case sinBI1 | sin97:
			case sinBI1 | sin98:
			case sinBI1 | sin99:
			case sinBI2 | sin38:
			case sinBI2 | sin43:
			case sinBI2 | sin44:
			case sinBI2 | sin45:
			case sinBI2 | sin46:
			case sinBI2 | sin47:
			case sinBI2 | sin58:
			case sinBI2 | sin75:
			case sinBI2 | sin76:
				if (chaPremiumitem.m_BigHeadTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}
				chaPremiumitem.UsePremiumItem(137);
				break;
			case sinBI2 | sin39:
			case sinBI2 | sin41:
				if (chaPremiumitem.m_BigHeadTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}
				if (GetSex(sinChar->iClass) == BROOD_CODE_WOMAN)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_USE_FEMALE);
					return;
				}
				chaPremiumitem.UsePremiumItem(137);
				break;
			case sinBI2 | sin40:
			case sinBI2 | sin42:
				if (chaPremiumitem.m_BigHeadTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}
				if (GetSex(sinChar->iClass) == BROOD_CODE_MAN)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_USE_MALE);
					return;
				}
				chaPremiumitem.UsePremiumItem(137);
				break;
			case sinBI2 | sin50:
				if (chaPremiumitem.m_PhenixPetTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}
				if (sinChar->iLevel < 10)
				{
					cMessageBox.ShowMessage(MESSAGE_PET_USE_LEVEL);
					return;
				}
				chaPremiumitem.UsePremiumItem(137);
				break;
			case sinBI2 | sin51:
				chaPremiumitem.UsePremiumItem(138);
				break;
			case sinBI2 | sin52:
				chaPremiumitem.UsePremiumItem(139);
				break;
			case sinBI2 | sin53:
				chaPremiumitem.UsePremiumItem(140);
				break;
			case sinBI2 | sin54:
				chaPremiumitem.UsePremiumItem(141);
				break;
			case sinBI2 | sin55:
				chaPremiumitem.UsePremiumItem(142);
				break;
			case sinBI2 | sin56:
				chaPremiumitem.UsePremiumItem(143);
				break;
			case sinBI2 | sin57:
				chaPremiumitem.UsePremiumItem(144);
				break;
			case sinBI2 | sin60:
				chaPremiumitem.TelePortCore.ItemIndex = SelectInvenItemIndex - 1;
				chaPremiumitem.UsePremiumItem(145);
				break;
			case sinBI2 | sin61:
				chaPremiumitem.TelePortCore.ItemIndex = SelectInvenItemIndex - 1;
				chaPremiumitem.UsePremiumItem(146);
				break;
			case sinBI2 | sin62:
				chaPremiumitem.TelePortCore.ItemIndex = SelectInvenItemIndex - 1;
				chaPremiumitem.UsePremiumItem(146);
				break;
			case sinBI2 | sin63:
				chaPremiumitem.TelePortCore.ItemIndex = SelectInvenItemIndex - 1;
				chaPremiumitem.UsePremiumItem(146);
				break;
			case sinBI2 | sin64:
				chaPremiumitem.TelePortCore.ItemIndex = SelectInvenItemIndex - 1;
				chaPremiumitem.UsePremiumItem(146);
				break;
			case sinBI2 | sin65:
				chaPremiumitem.TelePortCore.ItemIndex = SelectInvenItemIndex - 1;
				chaPremiumitem.UsePremiumItem(146);
				break;
			case sinBI2 | sin66:
			case sinBI2 | sin67:
			case sinBI2 | sin68:
				chaPremiumitem.UsePremiumItem(147);
				break;
			case sinBI2 | sin78:
			case sinBI2 | sin79:
			case sinBI2 | sin80:
			case sinBI2 | sin81:
				chaPremiumitem.UsePremiumItem(10);
				break;
			case sinBI2 | sin82:
			case sinBI2 | sin83:
			case sinBI2 | sin84:
			case sinBI2 | sin85:
			case sinBI2 | sin86:
			case sinBI2 | sin87:
			case sinBI2 | sin88:
			case sinBI2 | sin89:
			case sinBI2 | sin90:
			case sinBI2 | sin91:
				chaPremiumitem.UsePremiumItem(148);
				break;
			}

			if (haCastleSkillUseFlag != 1)
				return;

			if (!sinItemPickUpDelayFlag)
			{
				InvenItem[SelectInvenItemIndex - 1].sItem.iPotionCount = 300;
				sinThrowItemToFeild(&InvenItem[SelectInvenItemIndex - 1]);
				InvenItem[SelectInvenItemIndex - 1].bValid = 0;
				cInvenTory.CheckWeight();
				ReFormInvenItem();
				SaveGameData();
			}
		}

		int UseFlag2 = 0;

		if ((InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() & sinITEM_MASK2) == sinCH1)
		{
			if (lpCurPlayer->iLoadedMapIndex >= 0 &&
				STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapType == MAPTYPE_Town)
				return;

			for (int i = 0; i < SIN_MAX_SKILL_LIST; i++)
			{
				if (ContinueSkill[i].Flag)
				{
					if (ContinueSkill[i].CODE == SKILL_VIRTUAL_LIFE)
						return;
				}
			}

			if ((InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() & sinITEM_MASK3) == sin01 || (InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() & sinITEM_MASK3) == sin02)
			{
				if (GetSex(sinChar->iClass) == BROOD_CODE_WOMAN)
					cMessageBox.ShowMessage(MESSAGE_NOT_USE_FEMALE);
				else
					UseFlag2 = 1;
			}

			if ((InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() & sinITEM_MASK3) == sin03 || (InvenItem[SelectInvenItemIndex - 1].sBaseItemID.ToInt() & sinITEM_MASK3) == sin04)
			{
				if (GetSex(sinChar->iClass) == BROOD_CODE_MAN)
					cMessageBox.ShowMessage(MESSAGE_NOT_USE_MALE);
				else
					UseFlag2 = 1;
			}

			if (cItem.GetItemLimitTime(&InvenItem[SelectInvenItemIndex - 1]) == FALSE)
			{
				CHATGAMEHANDLE->SendChat(FALSE, FormatString("%s : %s", sinChar->szName, "The taste sucks really bad!"));

				InvenItem[SelectInvenItemIndex - 1].bValid = 0;
				sinUsePotionDelayFlag = 1;
				UseFlag2 = 0;
				cInvenTory.CheckWeight();
				ReFormInvenItem();
			}

			if (!sinItemPickUpDelayFlag && UseFlag2)
			{
				InvenItem[SelectInvenItemIndex - 1].sItem.iPotionCount = 100;
				sinThrowItemToFeild(&InvenItem[SelectInvenItemIndex - 1]);
				InvenItem[SelectInvenItemIndex - 1].bValid = 0;
				cInvenTory.CheckWeight();
				ReFormInvenItem();
			}
		}
	}
	ReFormPotionNum();

}
void cINVENTORY::RButtonUp(int x, int y)
{

}
void cINVENTORY::KeyDown()
{
	ItemData TempPotion;

	memset(&TempPotion, 0, sizeof(ItemData));
	int CountTemp = 0;
	int sArrowPosi = 0;
	char szKeyBuff[3] = { '1','2','3' };

	if (sinGetKeyClick('V'))
	{
		cHelpPet.PetMessage("*InvenTory", 3);
		if (cInvenTory.OpenFlag)
			cInvenTory.OpenFlag = SIN_CLOSE;
		else
			cInvenTory.OpenFlag = SIN_OPEN;
		cInterFace.CheckAllBox(SIN_INVENTORY);
		if (cInvenTory.OpenFlag)
		{
			if (!sinFireShow)
			{
				StartMenuFlame(0, 350);
				sinPlaySound(0);
			}
			else
				sinPlaySound(SIN_SOUND_SHOW_INTER);
			sinFireShow = 1;
		}
	}

	int TempPotionCount = 0;

	for (int i = 0; i < 3; i++)
	{
		if (sinGetKeyClick(szKeyBuff[i]))
		{
			if (SelectPotionIndex)
			{
				if (VRKeyBuff[VK_SHIFT])
				{
					if (MouseItem.bValid)
						break;
					if (MyShopSendButton || cMyShop.OpenFlag)
						break;
					if (InvenItem[SelectPotionIndex - 1].sItem.iPotionCount <= 0)
					{
						InvenItem[SelectPotionIndex - 1].bValid = 0;
						ReFormInvenItem();
						ReFormPotionNum();
						break;
					}
					if (sInven[i + 10].ItemIndex)
					{
						if (InvenItem[sInven[i + 10].ItemIndex - 1].sBaseItemID.ToInt() == InvenItem[SelectPotionIndex - 1].sBaseItemID.ToInt())
						{
							TempPotionCount = InvenItem[SelectPotionIndex - 1].sItem.iPotionCount;
							for (int p = 0; p < TempPotionCount; p++)
							{
								if (sinChar->iPotionStorage > InvenItem[sInven[i + 10].ItemIndex - 1].sItem.iPotionCount)
								{
									InvenItem[sInven[i + 10].ItemIndex - 1].sItem.iPotionCount++;
									InvenItem[SelectPotionIndex - 1].sItem.iPotionCount--;
									sinPlaySound(InvenItem[SelectPotionIndex - 1].iInvItemSound);
									if (InvenItem[SelectPotionIndex - 1].sItem.iPotionCount <= 0)
									{
										InvenItem[SelectPotionIndex - 1].bValid = 0;
										break;
									}
								}
							}
						}
					}
					else
					{
						memcpy(&TempPotion, &InvenItem[SelectPotionIndex - 1], sizeof(ItemData));
						TempPotion.iPlaceX = sInven[i + 10].Rect.left + (((sInven[i + 10].Rect.right - sInven[i + 10].Rect.left) - InvenItem[SelectPotionIndex - 1].iWidth) / 2);
						TempPotion.iPlaceY = sInven[i + 10].Rect.top + (((sInven[i + 10].Rect.bottom - sInven[i + 10].Rect.top) - InvenItem[SelectPotionIndex - 1].iHeight) / 2);

						TempPotion.sItem.iPotionCount = 0;
						TempPotion.bValid = 1;
						TempPotion.iItemSlot = i + 10 + 1;
						CountTemp = InvenItem[SelectPotionIndex - 1].sItem.iPotionCount;
						for (int f = 0; f < CountTemp; f++)
						{
							if (sinChar->iPotionStorage > TempPotion.sItem.iPotionCount)
							{
								TempPotion.sItem.iPotionCount++;
								InvenItem[SelectPotionIndex - 1].sItem.iPotionCount--;
								if (InvenItem[SelectPotionIndex - 1].sItem.iPotionCount <= 0)
								{
									InvenItem[SelectPotionIndex - 1].bValid = 0;
									break;
								}
							}
						}
						LastSetInvenItem(&TempPotion, 1);
					}
				}
				else
				{
					if (VRKeyBuff[VK_SHIFT])
						break;
					if (cWareHouse.OpenFlag || cTrade.OpenFlag || cCraftItem.OpenFlag)
						break;
					if (sInven[i + 10].ItemIndex)
					{
						if (sinActionPotion())
						{
							pUsePotion = &InvenItem[sInven[i + 10].ItemIndex - 1];
							break;
						}
					}
				}
			}
			else
			{
				if (VRKeyBuff[VK_SHIFT])
					break;
				if (cWareHouse.OpenFlag || cTrade.OpenFlag || cCraftItem.OpenFlag)
					break;
				if (sInven[i + 10].ItemIndex)
				{
					if (sinActionPotion())
					{
						cHelpPet.PetMessage("*Potion_ShortKey", 3 + i);
						pUsePotion = &InvenItem[sInven[i + 10].ItemIndex - 1];
						break;
					}
				}
			}
		}
	}

	if (!sinUsePotionDelayFlag)
	{
		if (sinGetKeyClick('E'))
		{
			if (ArrowState[0] == 0)
				sArrowPosi = 2;
			else
				sArrowPosi = 1;
			sinButtonFlag = sArrowPosi;
			SelectInvenItemIndex = 0;
			ChangeABItem(sArrowPosi);
		}
		else if (sinGetKeyClick('W'))
		{
			if (ArrowState[1] == 0)
				sArrowPosi = 4;
			else
				sArrowPosi = 3;
			sinButtonFlag = sArrowPosi;
			sinChangeSetFlag = sArrowPosi;
			SetItemToChar();
		}
		else if (sinGetKeyClick('T'))
		{
			sinChar->CostmePos ^= TRUE;
			if (sinChar->CostmePos == TRUE)
				sinChangeSetFlag = 5;
			else
				sinChangeSetFlag = 6;
		}
	}
}
int cINVENTORY::SetDelayTime(int Time, int Kind)
{
	if (DWORD(Kind) < sizeof(dwLastTime) / sizeof(DWORD))
	{
		if (dwLastTime[Kind] && (dwPlayTime - dwLastTime[Kind]) <= 1000 * DWORD(Time))
		{
			CHATGAMEHANDLE->AddChatBoxTextEx(CHATCOLOR_Error,
				"Please wait %d seconds", (Time - (dwPlayTime - dwLastTime[Kind]) / 1000));
			return TRUE;
		}
		dwLastTime[Kind] = dwPlayTime;
	}

	return FALSE;
}
int cINVENTORY::LoadItemInfo()
{
	int i;

	int TempItemIndex[17] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	int TempItemIndex2[17] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

	char szFilePath[256];

	ItemData sinTempItem;
	int TEstFlag = 1;
	int cnt = 0;

	for (i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItemTemp[i].bValid)
			sinSetSpecialItemCode(&InvenItemTemp[i].sItem);

		if (InvenItem[i].bValid)
		{
			sinSetSpecialItemCode(&InvenItem[i].sItem);

			ItemData * pItem = ITEMHANDLE->GetItemDataByID(InvenItem[i].sItem.sItemID.ToInt());

			if (pItem)
			{
				CopyMemory(&sinTempItem, pItem, sizeof(ItemData));
				CopyMemory(&sinTempItem.sItem, &InvenItem[i].sItem, sizeof(Item));
				wsprintf(szFilePath, "Image\\sinImage\\Items\\%s\\it%s.bmp", pItem->szCategory, pItem->szInventoryName);
				if (!pItem->pcTempInventoryTexture)
				{
					pItem->pcTempInventoryTexture = LoadDibSurfaceOffscreen(szFilePath);
					if (!pItem->pcTempInventoryTexture)
						TEstFlag = 0;
				}
				sinTempItem.pcInventoryTexture = pItem->pcTempInventoryTexture;
				sinTempItem.iPlaceX = InvenItem[i].iPlaceX;
				sinTempItem.iPlaceY = InvenItem[i].iPlaceY;
				sinTempItem.iItemSlot = InvenItem[i].iItemSlot;
				sinTempItem.bValid = 1;
				CopyMemory(&InvenItem[i], &sinTempItem, sizeof(ItemData));
				if (InvenItem[i].iItemSlot)
				{
					if ((InvenItem[i].sBaseItemID.ToInt() & sinITEM_MASK2) == sinWD1)
					{
						switch (InvenItem[i].iItemSlot)
						{
						case 1:
							InvenItem[i].iVisibleItemType = ITEMSLOTFLAG_RightHand;
							break;
						case 2:
							InvenItem[i].iVisibleItemType = ITEMSLOTFLAG_LeftHand;
							break;
						}
					}
					if (sinChar->CostmePos)
					{
						if (InvenItem[i].iItemSlot == 3)
							continue;
					}
					else
					{
						if (InvenItem[i].iItemSlot == 14)
							continue;
					}
					sInven[InvenItem[i].iItemSlot - 1].ItemIndex = i + 1;
					sinSetCharItem(InvenItem[i].sBaseItemID.ToInt(), InvenItem[i].iVisibleItemType, TRUE);
				}
			}
		}
	}

	for (i = 0; i < 84; i++)
	{
		if (InvenItemTemp[i].bValid)
		{
			ItemData * pItem = ITEMHANDLE->GetItemDataByID(InvenItemTemp[i].sItem.sItemID.ToInt());

			if (pItem)
			{
				memcpy(&sinTempItem, pItem, sizeof(ItemData));
				memcpy(&sinTempItem.sItem, &InvenItemTemp[i].sItem, sizeof(Item));
				wsprintf(szFilePath, "Image\\sinImage\\Items\\%s\\it%s.bmp", pItem->szCategory, pItem->szInventoryName);
				if (!pItem->pcTempInventoryTexture)
				{
					pItem->pcTempInventoryTexture = LoadDibSurfaceOffscreen(szFilePath);

					if (!pItem->pcTempInventoryTexture)
						TEstFlag = 0;
				}

				sinTempItem.pcInventoryTexture = pItem->pcTempInventoryTexture;
				sinTempItem.iPlaceX = InvenItemTemp[i].iPlaceX;
				sinTempItem.iPlaceY = InvenItemTemp[i].iPlaceY;
				sinTempItem.iItemSlot = InvenItemTemp[i].iItemSlot;
				sinTempItem.bValid = 1;
				memcpy(&InvenItemTemp[i], &sinTempItem, sizeof(ItemData));
			}
		}
	}
	for (i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItemTemp[i].bValid)
		{
			cItem.GetItemLimitTime(&InvenItemTemp[i]);
			if (InvenItemTemp[i].iPlaceX < StartX ||
				InvenItemTemp[i].iPlaceX > 800 ||
				InvenItemTemp[i].iPlaceY < StartY ||
				InvenItemTemp[i].iPlaceY > 600)
				ReSetPotionXY(&InvenItemTemp[i], 1);

			if (InvenItemTemp[i].iItemSlot)
			{
				if (!TempItemIndex2[InvenItemTemp[i].iItemSlot])
					TempItemIndex2[InvenItemTemp[i].iItemSlot] = i + 1;
				else
				{
					InvenItemTemp[i].bValid = 0;
					InvenItemTemp[TempItemIndex2[InvenItemTemp[i].iItemSlot] - 1].bValid = 0;
				}
			}
			if (InvenItemTemp[i].iItemSlot == 2)
			{
				if (InvenItemTemp[i].iItemSlotFlag == ITEMSLOTFLAG_LeftRightHand && (InvenItemTemp[i].sBaseItemID.ToInt() & sinITEM_MASK2) != sinWD1)
					break;
			}
			else if (InvenItemTemp[i].iItemSlot == 16)
			{
				if (InvenItemTemp[i].iItemSlotFlag == ITEMSLOTFLAG_Wing)
					break;
			}

			if (!CheckItemForm(&InvenItemTemp[i].sItem))
			{
				SendSetHackUser(FALSE);
				InvenItemTemp[i].bValid = 0;
			}
		}
	}
	bool ArmorFlag = false;

	for (i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].bValid)
		{
			cItem.GetItemLimitTime(&InvenItem[i]);
			if (InvenItem[i].iPlaceX < StartX ||
				InvenItem[i].iPlaceX > 800 ||
				InvenItem[i].iPlaceY < StartY ||
				InvenItem[i].iPlaceY > 600)
				ReSetPotionXY(&InvenItem[i]);

			if (InvenItem[i].iItemSlot > 0)
			{
				if (InvenItem[i].iItemSlot >= 17)
					continue;
				if (InvenItem[i].iItemSlot == 3 || InvenItem[i].iItemSlot == 14)
					ArmorFlag = true;

				if (!TempItemIndex[InvenItem[i].iItemSlot])
					TempItemIndex[InvenItem[i].iItemSlot] = i + 1;
				else
				{
					InvenItem[i].bValid = 0;
					InvenItem[TempItemIndex[InvenItem[i].iItemSlot] - 1].bValid = 0;
					if (InvenItem[TempItemIndex[InvenItem[i].iItemSlot] - 1].iItemSlotFlag == ITEMSLOTFLAG_LeftRightHand &&
						(InvenItem[TempItemIndex[InvenItem[i].iItemSlot] - 1].sBaseItemID.ToInt() & sinITEM_MASK2) != sinWD1)
					{
						if (InvenItem[TempItemIndex[InvenItem[i].iItemSlot] - 1].iItemSlot == 1)
						{
							if (InvenItem[TempItemIndex[InvenItem[i].iItemSlot] - 1].sBaseItemID.ToInt() == InvenItem[sInven[1].ItemIndex - 1].sBaseItemID.ToInt())
							{
								InvenItem[sInven[1].ItemIndex - 1].bValid = 0;
								sInven[1].ItemIndex = 0;
							}
						}
						if (InvenItem[TempItemIndex[InvenItem[i].iItemSlot] - 1].iItemSlot == 2)
						{
							if (InvenItem[TempItemIndex[InvenItem[i].iItemSlot] - 1].sBaseItemID.ToInt() == InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt())
							{
								InvenItem[sInven[0].ItemIndex - 1].bValid = 0;
								sInven[0].ItemIndex = 0;
							}
						}
					}
					else if (InvenItem[TempItemIndex[InvenItem[i].iItemSlot] - 1].iItemSlotFlag == ITEMSLOTFLAG_Wing)
					{
						if (InvenItem[TempItemIndex[InvenItem[i].iItemSlot] - 1].iItemSlot == 15)
						{
							if (InvenItem[TempItemIndex[InvenItem[i].iItemSlot] - 1].sBaseItemID.ToInt() == InvenItem[sInven[1].ItemIndex - 1].sBaseItemID.ToInt())
							{
								InvenItem[sInven[15].ItemIndex - 1].bValid = 0;
								sInven[15].ItemIndex = 0;
							}
						}
						if (InvenItem[TempItemIndex[InvenItem[i].iItemSlot] - 1].iItemSlot == 16)
						{
							if (InvenItem[TempItemIndex[InvenItem[i].iItemSlot] - 1].sBaseItemID.ToInt() == InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt())
							{
								InvenItem[sInven[14].ItemIndex - 1].bValid = 0;
								sInven[14].ItemIndex = 0;
							}
						}
					}
					if (InvenItem[TempItemIndex[InvenItem[i].iItemSlot] - 1].iItemSlot)
						sInven[TempItemIndex[InvenItem[i].iItemSlot] - 1].ItemIndex = 0;

					if (InvenItem[i].iVisibleItemType)
						sinSetCharItem(InvenItem[i].sBaseItemID.ToInt(), InvenItem[i].iVisibleItemType, FALSE);
					if (InvenItem[TempItemIndex[InvenItem[i].iItemSlot] - 1].iVisibleItemType)
						sinSetCharItem(InvenItem[TempItemIndex[InvenItem[i].iItemSlot] - 1].sBaseItemID.ToInt(),
							InvenItem[TempItemIndex[InvenItem[i].iItemSlot] - 1].iVisibleItemType, FALSE);
					if (InvenItem[i].iItemSlot) {
						sInven[InvenItem[i].iItemSlot - 1].ItemIndex = 0;

					}
					if (InvenItem[i].iItemSlotFlag == ITEMSLOTFLAG_LeftRightHand &&
						(InvenItem[i].sBaseItemID.ToInt() & sinITEM_MASK2) != sinWD1)
					{
						if (InvenItem[i].iItemSlot == 1)
						{
							if (InvenItem[i].sBaseItemID.ToInt() == InvenItem[sInven[1].ItemIndex - 1].sBaseItemID.ToInt())
							{
								InvenItem[sInven[1].ItemIndex - 1].bValid = 0;
								sInven[1].ItemIndex = 0;
							}
						}
						if (InvenItem[i].iItemSlot == 2)
						{
							if (InvenItem[i].sBaseItemID.ToInt() == InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt())
							{
								InvenItem[sInven[0].ItemIndex - 1].bValid = 0;
								sInven[0].ItemIndex = 0;
							}
						}
					}
					else if (InvenItem[i].iItemSlotFlag == ITEMSLOTFLAG_Wing)
					{
						if (InvenItem[i].iItemSlot == 15)
						{
							if (InvenItem[i].sBaseItemID.ToInt() == InvenItem[sInven[1].ItemIndex - 1].sBaseItemID.ToInt())
							{
								InvenItem[sInven[15].ItemIndex - 1].bValid = 0;
								sInven[15].ItemIndex = 0;
							}
						}
						if (InvenItem[i].iItemSlot == 16)
						{
							if (InvenItem[i].sBaseItemID.ToInt() == InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt())
							{
								InvenItem[sInven[14].ItemIndex - 1].bValid = 0;
								sInven[14].ItemIndex = 0;
							}
						}
					}
				}
				if (InvenItem[i].iItemSlotFlag == ITEMSLOTFLAG_LeftRightHand && (InvenItem[i].sBaseItemID.ToInt() & sinITEM_MASK2) != sinWD1)
				{
					if (InvenItem[i].iItemSlot == 1)
					{
						if (InvenItem[i].sBaseItemID.ToInt() != InvenItem[sInven[1].ItemIndex - 1].sBaseItemID.ToInt())
						{
							InvenItem[sInven[1].ItemIndex - 1].bValid = 0;
							InvenItem[i].bValid = 0;
							sInven[1].ItemIndex = 0;
							sInven[0].ItemIndex = 0;
							if (InvenItem[i].iVisibleItemType)
								sinSetCharItem(InvenItem[i].sBaseItemID.ToInt(), InvenItem[i].iVisibleItemType, FALSE);

						}
					}
					if (InvenItem[i].iItemSlot == 2)
					{
						if (InvenItem[i].sBaseItemID.ToInt() != InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt())
						{
							InvenItem[sInven[0].ItemIndex - 1].bValid = 0;
							InvenItem[i].bValid = 0;
							sInven[0].ItemIndex = 0;
							sInven[1].ItemIndex = 0;
							if (InvenItem[i].iVisibleItemType)
								sinSetCharItem(InvenItem[i].sBaseItemID.ToInt(), InvenItem[i].iVisibleItemType, FALSE);
						}
					}
				}
				else if (InvenItem[i].iItemSlotFlag == ITEMSLOTFLAG_Wing)
				{
					if (InvenItem[i].iItemSlot == 15)
					{
						if (InvenItem[i].sBaseItemID.ToInt() != InvenItem[sInven[15].ItemIndex - 1].sBaseItemID.ToInt())
						{
							InvenItem[sInven[15].ItemIndex - 1].bValid = 0;
							InvenItem[i].bValid = 0;
							sInven[15].ItemIndex = 0;
							sInven[14].ItemIndex = 0;
							if (InvenItem[i].iVisibleItemType)
								sinSetCharItem(InvenItem[i].sBaseItemID.ToInt(), InvenItem[i].iVisibleItemType, FALSE);

						}
					}
					if (InvenItem[i].iItemSlot == 16)
					{
						if (InvenItem[i].sBaseItemID.ToInt() != InvenItem[sInven[14].ItemIndex - 1].sBaseItemID.ToInt())
						{
							InvenItem[sInven[14].ItemIndex - 1].bValid = 0;
							InvenItem[i].bValid = 0;
							sInven[15].ItemIndex = 0;
							sInven[14].ItemIndex = 0;
							if (InvenItem[i].iVisibleItemType)
								sinSetCharItem(InvenItem[i].sBaseItemID.ToInt(), InvenItem[i].iVisibleItemType, FALSE);
						}
					}
				}
			}

			if (!InvenItem[i].pcInventoryTexture)
				cMessageBox.ShowMessage(MESSAGE_NOTEXIT_ITEMIMAGE);

			if (InvenItem[i].iItemSlot == 2)
			{
				if (InvenItem[i].iItemSlotFlag == ITEMSLOTFLAG_LeftRightHand && (InvenItem[i].sBaseItemID.ToInt() & sinITEM_MASK2) != sinWD1)
					continue;
			}
			else if (InvenItem[i].iItemSlot == 16)
			{
				if (InvenItem[i].iItemSlotFlag == ITEMSLOTFLAG_Wing)
					continue;
			}

			if (!CheckItemForm(&InvenItem[i].sItem))
			{
				SendSetHackUser(FALSE);
				InvenItem[i].bValid = 0;
				if (InvenItem[i].iItemSlot)
				{
					sInven[InvenItem[i].iItemSlot - 1].ItemIndex = 0;
					sinSetCharItem(InvenItem[i].sBaseItemID.ToInt(), InvenItem[i].iVisibleItemType, FALSE);
				}
				if (InvenItem[i].iItemSlotFlag == ITEMSLOTFLAG_LeftRightHand && (InvenItem[i].sBaseItemID.ToInt() & sinITEM_MASK2) != sinWD1)
				{
					InvenItem[sInven[1].ItemIndex - 1].bValid = 0;
					sInven[1].ItemIndex = 0;
				}
				else if (InvenItem[i].iItemSlotFlag == ITEMSLOTFLAG_Wing)
				{
					InvenItem[sInven[15].ItemIndex - 1].bValid = 0;
					sInven[15].ItemIndex = 0;
				}
			}
		}
	}
	if (!ArmorFlag)
		sinSetCharItem(NULL, ITEMSLOTFLAG_Armor, FALSE);

	ReformCharForm();
	LoadCharState();

	SearchJobAndSetting();
	ReFormInvenItem();

	CheckWeight();

	cSkill.SearchUseSkill();
	SetItemToChar();

	ReFormPotionNum();
	PotionCheckNumJumpFlag = 0;
	CheckRequireItem();

	if (MouseItem.bValid)
	{
		ItemData * pItem = ITEMHANDLE->GetItemDataByID(MouseItem.sItem.sItemID.ToInt());

		if (pItem)
		{
			CopyMemory(&sinTempItem, pItem, sizeof(ItemData));
			CopyMemory(&sinTempItem.sItem, &MouseItem.sItem, sizeof(Item));
			wsprintf(szFilePath, "Image\\sinImage\\Items\\%s\\it%s.bmp", pItem->szCategory, pItem->szInventoryName);
			if (!pItem->pcTempInventoryTexture)
				pItem->pcTempInventoryTexture = LoadDibSurfaceOffscreen(szFilePath);
			sinTempItem.pcInventoryTexture = pItem->pcTempInventoryTexture;
			sinTempItem.iPlaceX = MouseItem.iPlaceX;
			sinTempItem.iPlaceY = MouseItem.iPlaceY;
			sinTempItem.iItemSlot = MouseItem.iItemSlot;
			sinTempItem.bValid = 1;
			ReFormInvenItem();
			CopyMemory(&MouseItem, &sinTempItem, sizeof(ItemData));
			cInvenTory.AutoSetInvenItem(&MouseItem);
		}
	}

	CheckResetInvenItem();
	cSkill.InitReformSkillPointForm();
	ReFormMousePotionNum();
	CheckSpecialItemPosi();
	ChangeSpecialItem(2);
	CheckChangeJob_QuestItem();
	CheckPuzzle();
	cHelpPet.CheckPetData();
	cPCBANGPet.CheckPetData();
	ReSetQuestItemPosi();
	return TRUE;
}


int cINVENTORY::ReSetQuestItemPosi()
{
	ItemData *pItem = 0;
	for (int i = 0; i < INVENTORY_MAXITEM * 2; i++)
	{
		if (i < 100)
		{
			if (!InvenItem[i].bValid)continue;
			pItem = &InvenItem[i];
		}
		else
		{
			if (!InvenItemTemp[i - 100].bValid)continue;
			pItem = &InvenItemTemp[i - 100];
		}
		if (pItem->iPlaceX > 1000 && pItem->iPlaceX < 2000)
		{
			pItem->iPlaceX += 9000;
		}
	}
	return TRUE;
}

int cINVENTORY::SetSpecialItem(ItemData *pItem)
{
	if (pItem->sItem.SpecialItemFlag[1] != ITEMCRAFTTYPE_Special)
		return FALSE;

	int cntx, cnty;
	int cx, cy;

	RECT	rect;
	int		flag;

	cx = (44 * 6) - pItem->iWidth;
	cy = (44 * 3) - pItem->iHeight;

	int TempWidth = 0;
	if (SpecialItemShowFlag)
		TempWidth = 0;
	else
		TempWidth = 10000;

	for (cntx = (StartX + TempWidth); cntx <= StartX + TempWidth + cx; cntx += 44)
	{
		for (cnty = StartY; cnty <= StartY + cy; cnty += 44)
		{
			flag = 0;
			for (int i = 84; i < INVENTORY_MAXITEM; i++)
			{
				if (InvenItem[i].bValid && InvenItem[i].sItem.SpecialItemFlag[1] == ITEMCRAFTTYPE_Special)
				{
					if (InvenItem[i].iPlaceX < TempWidth)
					{
						rect.left = InvenItem[i].iPlaceX + TempWidth;
						rect.right = InvenItem[i].iPlaceX + TempWidth + InvenItem[i].iWidth;
					}
					else
					{
						rect.left  = InvenItem[i].iPlaceX;
						rect.right = InvenItem[i].iPlaceX + InvenItem[i].iWidth;
					}
					rect.top = InvenItem[i].iPlaceY;
					rect.bottom = InvenItem[i].iPlaceY + InvenItem[i].iHeight;

					if (cntx > rect.left - pItem->iWidth &&
						cntx < rect.right &&
						cnty > rect.top - pItem->iHeight &&
						cnty < rect.bottom)
						flag++;
				}
			}
			if (flag == 0)
			{
				pItem->iPlaceX = cntx + ((44 - pItem->iWidth) / 2);
				pItem->iPlaceY = cnty + ((44 - pItem->iHeight) / 2);
				pItem->iItemSlot = 0;

				for (int j = 84; j < INVENTORY_MAXITEM; j++)
				{
					if (InvenItem[j].bValid == 0)
					{
						CheckInvenItemForm();
						memcpy(&InvenItem[j], pItem, sizeof(ItemData));
						InvenItem[j].iPlaceX = pItem->iPlaceX;
						InvenItem[j].iPlaceY = pItem->iPlaceY;
						ReFormInvenItem();
						SetItemToChar();
						sinPlaySound(InvenItem[j].iInvItemSound);
						CheckWeight();

						SendCheckItemToServer(&InvenItem[j].sItem);
						CheckDamage();
						ReFormPotionNum();
						return TRUE;
					}
				}
			}
		}
	}

	return FALSE;
}
int cINVENTORY::AutoSetInvenItem(ItemData *pItem, int PostBox)
{
	char szBuff[128];
	if (SetSpecialItem(pItem))
		return TRUE;

	ChangeSpecialItem(2);

	if (!PostBox)
	{
		if (!CheckSetOk(pItem, 1))
			return FALSE;
	}
	if (PostBox == 2)
	{
		pItem->iPlaceX = StartX + (22 * 8);
		pItem->iPlaceY = StartY;
		if (LastSetInvenItem(pItem, 1))
		{
			wsprintf(szBuff, "%s %s", pItem->sItem.szItemName, "I received the item");
			cMessageBox.ShowMessageEvent(szBuff);
			return TRUE;
		}
	}
	if (PostBox == 3)
	{
		wsprintf(szBuff, "%s %s", pItem->sItem.szItemName, "I received the item");
		cMessageBox.ShowMessageEvent(szBuff);
	}

	if (AutoSetPotion(pItem))
		return TRUE;

	for (int i = 0; i < INVENTORY_MAX_POS; i++)
	{
		if (pItem->iItemSlotFlag & sInven[i].Position)
		{
			if (!sInven[i].ItemIndex)
			{
				if (sInven[i].ItemIndex)
					break;

				if (sinChar->iClass == CHARACTERCLASS_Assassin)
				{
					if (sInven[1].ItemIndex == NULL && (pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinDS1)
						break;
				}
				else
				{
					if (sInven[1].ItemIndex == NULL && (pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinWD1)
						break;
				}
				if (pItem->iItemSlotFlag == ITEMSLOTFLAG_LeftRightHand && (pItem->sBaseItemID.ToInt() & sinITEM_MASK2) != sinWD1)
				{
					if (sInven[0].ItemIndex || sInven[1].ItemIndex)
						break;
				}
				else if (pItem->iItemSlotFlag == ITEMSLOTFLAG_Wing)
				{
					if (sInven[14].ItemIndex || sInven[15].ItemIndex)
						break;
				}
				if (pItem->iItemSlotFlag == ITEMSLOTFLAG_Costume ||
					pItem->iItemSlotFlag == ITEMSLOTFLAG_Wing)
				{
					if (!sinChar->CostmePos)
						break;
				}
				else if (pItem->iItemSlotFlag == ITEMSLOTFLAG_Armor ||
					pItem->iItemSlotFlag == ITEMSLOTFLAG_LeftRightHand ||
					pItem->iItemSlotFlag == ITEMSLOTFLAG_RightHand)
				{
					if (sinChar->CostmePos)
						break;
				}

				if (pItem->sItem.bCanNotUse)
					break;
				pItem->iPlaceX = sInven[i].Rect.left + (((sInven[i].Rect.right - sInven[i].Rect.left) - pItem->iWidth) / 2);
				pItem->iPlaceY = sInven[i].Rect.top + (((sInven[i].Rect.bottom - sInven[i].Rect.top) - pItem->iHeight) / 2);
				pItem->iItemSlot = i + 1;

				if (LastSetInvenItem(pItem, 1))
					return TRUE;
			}
		}
	}
	if (InvenEmptyAearCheck(pItem))
		return TRUE;

	cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
	sinOverWeightCnt++;
	return FALSE;
}
int cINVENTORY::InvenEmptyAearCheck(ItemData *pItem)
{
	int cntx, cnty;
	int cx, cy;

	RECT	rect;
	int		flag;

	if (AutoSetPotionToBox(pItem))return TRUE;

	cx = (22 * INVENTORY_BOX_ROW) - pItem->iWidth;
	cy = (22 * INVENTORY_BOX_COL) - pItem->iHeight;

	for (cntx = StartX; cntx <= StartX + cx; cntx += 22)
	{
		for (cnty = StartY; cnty <= StartY + cy; cnty += 22)
		{
			flag = 0;
			for (int i = 0; i < INVENTORY_MAXITEM; i++)
			{
				if (InvenItem[i].bValid)
				{
					rect.left	= InvenItem[i].iPlaceX;
					rect.right	= InvenItem[i].iPlaceX + InvenItem[i].iWidth;
					rect.top	= InvenItem[i].iPlaceY;
					rect.bottom = InvenItem[i].iPlaceY + InvenItem[i].iHeight;

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
				LastSetInvenItem(pItem, 1);
				return TRUE;
			}
		}
	}
	return FALSE;
}
int cINVENTORY::LastSetInvenItem(ItemData *pItem, int AutoSet)
{
	int PassFlag = 0;
	if (!AutoSet)
	{
		if (!InvenNotOpenCheck(pItem))
			return FALSE;
	}

	for (int j = 0; j < INVENTORY_MAXITEM; j++)
	{
		if (InvenItem[j].bValid == 0)
		{
			if (sinPosionItem)
			{
				if (sinPosionItem->sItem.iChk1 == InvenItem[j].sItem.iChk1)
					continue;
			}
			CheckInvenItemForm();
			memcpy(&InvenItem[j], pItem, sizeof(ItemData));
			InvenItem[j].iPlaceX = pItem->iPlaceX;
			InvenItem[j].iPlaceY = pItem->iPlaceY;
			if (InvenItem[j].iItemSlot)
			{
				SetTwoHandItem(&InvenItem[j]);
				sInven[InvenItem[j].iItemSlot - 1].ItemIndex = j + 1;
				if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK2) == sinWD1)
				{
					switch (pItem->iItemSlot)
					{
					case 1:
						pItem->iVisibleItemType = ITEMSLOTFLAG_RightHand;
						break;
					case 2:
						pItem->iVisibleItemType = ITEMSLOTFLAG_LeftHand;
						break;
					}
				}
				sinSetCharItem(InvenItem[j].sBaseItemID.ToInt(), pItem->iVisibleItemType, TRUE);
			}
			pItem->bValid = 0;
			ReFormInvenItem();
			SetItemToChar();
			sinPlaySound(InvenItem[j].iInvItemSound);
			CheckWeight();
			if (InvenItem[j].iPlaceX < StartX ||
				InvenItem[j].iPlaceX > 800 ||
				InvenItem[j].iPlaceY < StartY ||
				InvenItem[j].iPlaceY > 600)
				AutoSetInvenItem(&InvenItem[j]);

			SendCheckItemToServer(&InvenItem[j].sItem);
			CheckDamage();
			ReFormPotionNum();

			CheckPuzzle();
			return TRUE;
		}
	}
	ReFormInvenItem();
	return FALSE;
}
int cINVENTORY::UsePotion(int x, int y)
{
	for (int i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].bValid)
		{
			if (InvenItem[i].iPlaceX < x  &&
				InvenItem[i].iPlaceX + InvenItem[i].iWidth > x  &&
				InvenItem[i].iPlaceY < y  &&
				InvenItem[i].iPlaceY + InvenItem[i].iHeight > y)
			{
				if (InvenItem[i].iItemSlot == 11 ||
					InvenItem[i].iItemSlot == 12 ||
					InvenItem[i].iItemSlot == 13)
				{
					if (InvenItem[i].iItemSlotFlag == ITEMSLOTFLAG_Potion)
					{
						if (sinActionPotion())
						{
							pUsePotion = &InvenItem[i];
							sinUsePotionDelayFlag = 1;
						}
					}
				}
				else
				{
					if (!OpenFlag)
						break;
					if (InvenItem[i].iItemSlotFlag == ITEMSLOTFLAG_Potion)
					{
						if (sinActionPotion())
						{
							pUsePotion = &InvenItem[i];
							sinUsePotionDelayFlag = 1;
						}
					}
				}
			}
		}
	}
	ReFormPotionNum();
	return FALSE;
}

int cINVENTORY::ReSettingPotion()
{
	ItemData TempPotionItem;
	int i = 0, j = 0, cnt = 0;

	memset(&TempPotionItem, 0, sizeof(ItemData));
	for (i = 10; i < 13; i++)
	{
		if (sInven[i].ItemIndex)
		{
			if (InvenItem[sInven[i].ItemIndex - 1].bValid)
			{
				memcpy(&TempPotionItem, &InvenItem[sInven[i].ItemIndex - 1], sizeof(ItemData));
				cnt = TempPotionItem.sItem.iPotionCount;
				if (sinChar->iPotionStorage < InvenItem[sInven[i].ItemIndex - 1].sItem.iPotionCount)
				{
					TempPotionItem.sItem.iPotionCount = InvenItem[sInven[i].ItemIndex - 1].sItem.iPotionCount - sinChar->iPotionStorage;
					InvenItem[sInven[i].ItemIndex - 1].sItem.iPotionCount -= TempPotionItem.sItem.iPotionCount;
					if (!InvenEmptyAearCheck(&TempPotionItem))
						NoSettingThrowItem(&TempPotionItem);
				}
			}
		}
	}
	ReFormPotionNum();

	return TRUE;
}
int BackUpX, BackUpY, BackUpPosi = 0;

int cINVENTORY::MouseSetPotion(ItemData *pItem)
{
	int i = 0, cnt;
	ItemData TempPotionItem;
	sinPosionItem = 0;

	if (!pItem->bValid)return FALSE;
	BackUpItemIndex = 0;
	if (CrashItemIndex[0])
	{
		if (pMessageItem)
		{
			BackUpX = pMessageItem->iPlaceX;
			BackUpY = pMessageItem->iPlaceY;
			BackUpPosi = pMessageItem->iItemSlot;
			sinPosionItem = &InvenItem[CrashItemIndex[0] - 1];
			BackUpItemIndex = CrashItemIndex[0];
		}
		if (pItem->iItemSlot)
		{
			memcpy(&TempPotionItem, pItem, sizeof(ItemData));
			if (pItem->sBaseItemID.ToInt() == InvenItem[CrashItemIndex[0] - 1].sBaseItemID.ToInt())
			{
				cnt = pItem->sItem.iPotionCount;
				for (i = 0; i < cnt; i++)
				{
					if (sinChar->iPotionStorage > InvenItem[CrashItemIndex[0] - 1].sItem.iPotionCount)
					{
						InvenItem[CrashItemIndex[0] - 1].sItem.iPotionCount++;
						pItem->sItem.iPotionCount--;
						if (pItem->sItem.iPotionCount <= 0)
						{
							pItem->bValid = 0;
							sinPlaySound(pItem->iInvItemSound);
							ReFormPotionNum();
							return TRUE;
						}
					}
					else
					{
						if (InvenEmptyAearCheck(pItem))
						{
							ReFormPotionNum();
							return TRUE;
						}
						else
						{
							ResetPotion2();
							if (sinThrowItemToFeild(pItem))
							{
								ReformCharForm();
								cInvenTory.ReFormPotionNum();
								return TRUE;
							}
							else
							{
								ReformCharForm();
								cInvenTory.ReFormPotionNum();
								return FALSE;
							}
						}
					}
				}
			}
			else
			{
				memcpy(&TempItem, &InvenItem[CrashItemIndex[0] - 1], sizeof(ItemData));
				InvenItem[CrashItemIndex[0] - 1].bValid = 0;
				if (sinPosionItem)
					sinPosionItem->bValid = 0;
				TempPotionItem.sItem.iPotionCount = 0;
				cnt = pItem->sItem.iPotionCount;
				for (i = 0; i < cnt; i++)
				{
					if (sinChar->iPotionStorage < pItem->sItem.iPotionCount)
					{
						pItem->sItem.iPotionCount--;
						TempPotionItem.sItem.iPotionCount++;
					}
					else
					{
						ReFormInvenItem();
						if (LastSetInvenItem(pItem))
						{
							if (TempPotionItem.sItem.iPotionCount > 0)
							{
								if (InvenEmptyAearCheck(&TempPotionItem))
								{
									memcpy(pItem, &TempItem, sizeof(ItemData));
									pMessageItem = sinPosionItem;
									pMessageItem->iPlaceX = BackUpX;
									pMessageItem->iPlaceY = BackUpY;
									pMessageItem->iItemSlot = BackUpPosi;
									sinPosionItem = 0;
									ReFormPotionNum();
									return TRUE;
								}
								else
								{
									memcpy(pItem, &TempItem, sizeof(ItemData));
									if (sinPosionItem)
									{
										pMessageItem = sinPosionItem;
										pMessageItem->iPlaceX = BackUpX;
										pMessageItem->iPlaceY = BackUpY;
										pMessageItem->iItemSlot = BackUpPosi;
										sinPosionItem = 0;
									}
									sinThrowItemToFeild(&TempPotionItem);
									ReFormPotionNum();
									return TRUE;
								}
							}
							memcpy(pItem, &TempItem, sizeof(ItemData));
							if (sinPosionItem)
							{
								pMessageItem = sinPosionItem;
								pMessageItem->iPlaceX = BackUpX;
								pMessageItem->iPlaceY = BackUpY;
								pMessageItem->iItemSlot = BackUpPosi;
								sinPosionItem = 0;
							}
							ReFormPotionNum();
							return TRUE;
						}
						else
						{
							ReFormPotionNum();
							return FALSE;
						}
					}
				}
			}
		}
		else
		{
			if (pItem->sBaseItemID.ToInt() == InvenItem[CrashItemIndex[0] - 1].sBaseItemID.ToInt())
			{
				if (!cInvenTory.OpenFlag)
				{
					SendSetHackUser2(1960, 3);
					return TRUE;
				}
				InvenItem[CrashItemIndex[0] - 1].sItem.iPotionCount += pItem->sItem.iPotionCount;
				pItem->bValid = 0;
				sinPlaySound(pItem->iInvItemSound);
				ReFormPotionNum();
				return TRUE;
			}
			else
			{
				memcpy(&TempItem, &InvenItem[CrashItemIndex[0] - 1], sizeof(ItemData));
				InvenItem[CrashItemIndex[0] - 1].bValid = 0;

				TempItem.iPlaceX = pItem->iPlaceX;
				TempItem.iPlaceY = pItem->iPlaceY;
				ReFormInvenItem();
				LastSetInvenItem(pItem);
				memcpy(pItem, &TempItem, sizeof(ItemData));
				if (sinPosionItem)
				{
					pMessageItem = sinPosionItem;
					pMessageItem->iPlaceX = BackUpX;
					pMessageItem->iPlaceY = BackUpY;
					pMessageItem->iItemSlot = BackUpPosi;
					sinPosionItem = 0;
				}
				ReFormPotionNum();
				return TRUE;
			}
		}
	}
	else
	{
		if (pItem->iItemSlot)
		{
			memcpy(&TempPotionItem, pItem, sizeof(ItemData));
			TempPotionItem.sItem.iPotionCount = 0;
			cnt = pItem->sItem.iPotionCount;
			for (i = 0; i < cnt; i++)
			{
				if (sinChar->iPotionStorage < pItem->sItem.iPotionCount)
				{
					pItem->sItem.iPotionCount--;
					TempPotionItem.sItem.iPotionCount++;
				}
				else
				{
					ReFormInvenItem();
					if (LastSetInvenItem(pItem))
					{
						if (TempPotionItem.sItem.iPotionCount > 0)
						{
							if (InvenEmptyAearCheck(&TempPotionItem))
							{
								ReFormPotionNum();
								return TRUE;
							}
							else
							{
								sinThrowItemToFeild(&TempPotionItem);
								ReFormPotionNum();
								return FALSE;
							}
						}
						ReFormPotionNum();
						return TRUE;
					}
					else
					{
						ReFormPotionNum();
						return FALSE;
					}
				}
			}
		}
		else
		{
			ReFormInvenItem();
			if (LastSetInvenItem(pItem))
			{
				ReFormPotionNum();
				return TRUE;
			}
		}
	}
	ReFormPotionNum();
	return FALSE;
}

int cINVENTORY::AutoSetPotionToBox(ItemData *pItem)
{
	if (pItem->iItemSlotFlag != ITEMSLOTFLAG_Potion)
		return FALSE;
	for (int i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].bValid)
		{
			if (pItem->sBaseItemID.ToInt() == InvenItem[i].sBaseItemID.ToInt())
			{
				if (InvenItem[i].iItemSlot)
					continue;
				InvenItem[i].sItem.iPotionCount += pItem->sItem.iPotionCount;
				pItem->bValid = 0;
				sinPlaySound(pItem->iInvItemSound);
				if (InvenItem[i].iPlaceX < 3 || InvenItem[i].iPlaceY < 10)
					ReSetPotionXY(&InvenItem[i]);
				ReformCharForm();
				cInvenTory.ReFormPotionNum();

				return TRUE;
			}
		}
	}

	return FALSE;
}
int cINVENTORY::AutoSetPotion(ItemData *pItem)
{
	int i = 0, j = 0, cnt = 0;
	ItemData TempPotion;

	if (pItem->iItemSlotFlag != ITEMSLOTFLAG_Potion)
		return FALSE;
	for (i = 0; i < INVENTORY_MAX_POS; i++)
	{
		if (pItem->iItemSlotFlag & sInven[i].Position)
		{
			if (sInven[i].ItemIndex)
			{
				if (pItem->sBaseItemID.ToInt() == InvenItem[sInven[i].ItemIndex - 1].sBaseItemID.ToInt())
				{
					if (sinChar->iPotionStorage == InvenItem[sInven[i].ItemIndex - 1].sItem.iPotionCount)
						continue;
					cnt = pItem->sItem.iPotionCount;
					for (j = 0; j < cnt; j++)
					{
						if (sinChar->iPotionStorage > InvenItem[sInven[i].ItemIndex - 1].sItem.iPotionCount)
						{
							InvenItem[sInven[i].ItemIndex - 1].sItem.iPotionCount++;
							pItem->sItem.iPotionCount--;
							sinPlaySound(pItem->iInvItemSound);
							if (pItem->sItem.iPotionCount <= 0)
							{
								pItem->bValid = 0;
								ReformCharForm();
								cInvenTory.ReFormPotionNum();
								return TRUE;
							}
						}
						else
						{
							if (InvenEmptyAearCheck(pItem))
							{
								ReformCharForm();
								cInvenTory.ReFormPotionNum();
								return TRUE;
							}
							else
							{
								ResetPotion2();
								if (sinThrowItemToFeild(pItem))
								{
									ReformCharForm();
									cInvenTory.ReFormPotionNum();
									return TRUE;
								}
							}
						}
					}
				}
				else
					continue;
			}
			else
			{
				pItem->iPlaceX = sInven[i].Rect.left + (((sInven[i].Rect.right - sInven[i].Rect.left) - pItem->iWidth) / 2);
				pItem->iPlaceY = sInven[i].Rect.top + (((sInven[i].Rect.bottom - sInven[i].Rect.top) - pItem->iHeight) / 2);

				cnt = pItem->sItem.iPotionCount;
				pItem->iItemSlot = i + 1;
				memcpy(&TempPotion, pItem, sizeof(ItemData));
				TempPotion.sItem.iPotionCount = 0;
				for (j = 0; j < cnt; j++)
				{
					if (sinChar->iPotionStorage < pItem->sItem.iPotionCount)
					{
						pItem->sItem.iPotionCount--;
						TempPotion.sItem.iPotionCount++;
					}
					else
					{
						if (LastSetInvenItem(pItem, 1))
						{
							if (TempPotion.sItem.iPotionCount > 0)
							{
								if (InvenEmptyAearCheck(&TempPotion))
								{
									ReformCharForm();
									cInvenTory.ReFormPotionNum();
									return TRUE;
								}
							}
							else
							{
								ReformCharForm();
								cInvenTory.ReFormPotionNum();
								return TRUE;
							}
						}
					}
				}
			}
		}
	}

	return FALSE;
}
int cINVENTORY::ClearTwoHandPosiAndItem(ItemData *pItem)
{
	if (pItem->iItemSlotFlag == ITEMSLOTFLAG_LeftRightHand && (pItem->sBaseItemID.ToInt() & sinITEM_MASK2) != sinWD1)
	{
		if (sInven[0].ItemIndex)
		{
			InvenItem[sInven[0].ItemIndex - 1].bValid = 0;
			sInven[0].ItemIndex = 0;
			if (InvenItem[sInven[0].ItemIndex - 1].iItemSlot)
			{
				if (InvenItem[sInven[0].ItemIndex - 1].iVisibleItemType)
					sinSetCharItem(InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt(),
						InvenItem[sInven[0].ItemIndex - 1].iVisibleItemType, FALSE);
			}
		}
		if (sInven[1].ItemIndex)
		{
			InvenItem[sInven[1].ItemIndex - 1].bValid = 0;
			sInven[1].ItemIndex = 0;
			if (InvenItem[sInven[1].ItemIndex - 1].iItemSlot)
			{
				if (InvenItem[sInven[1].ItemIndex - 1].iVisibleItemType)
					sinSetCharItem(InvenItem[sInven[1].ItemIndex - 1].sBaseItemID.ToInt(),
						InvenItem[sInven[1].ItemIndex - 1].iVisibleItemType, FALSE);
			}
		}
	}
	else if (pItem->iItemSlotFlag == ITEMSLOTFLAG_Wing)
	{
		if (sInven[14].ItemIndex)
		{
			InvenItem[sInven[14].ItemIndex - 1].bValid = 0;
			sInven[14].ItemIndex = 0;
			if (InvenItem[sInven[14].ItemIndex - 1].iItemSlot)
			{
				if (InvenItem[sInven[14].ItemIndex - 1].iVisibleItemType)
					sinSetCharItem(InvenItem[sInven[14].ItemIndex - 1].sBaseItemID.ToInt(),
						InvenItem[sInven[14].ItemIndex - 1].iVisibleItemType, FALSE);
			}
		}
		if (sInven[15].ItemIndex)
		{
			InvenItem[sInven[15].ItemIndex - 1].bValid = 0;
			sInven[15].ItemIndex = 0;
			if (InvenItem[sInven[15].ItemIndex - 1].iItemSlot)
			{
				if (InvenItem[sInven[15].ItemIndex - 1].iVisibleItemType)
					sinSetCharItem(InvenItem[sInven[15].ItemIndex - 1].sBaseItemID.ToInt(),
						InvenItem[sInven[15].ItemIndex - 1].iVisibleItemType, FALSE);
			}
		}
	}
	return TRUE;
}
int cINVENTORY::SetTwoHandItem(ItemData *pItem)
{
	ItemData TempTwoHandItem;

	memset(&TempTwoHandItem, 0, sizeof(ItemData));

	if (pItem->iItemSlotFlag == ITEMSLOTFLAG_LeftRightHand)
	{
		if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK2) != sinWD1)
		{
			if (pItem->iItemSlot == 2)
			{
				pItem->iItemSlot = 1;
				pItem->iPlaceX = sInven[0].Rect.left + (((sInven[0].Rect.right - sInven[0].Rect.left) - pItem->iWidth) / 2);
				pItem->iPlaceY = sInven[0].Rect.top + (((sInven[0].Rect.bottom - sInven[0].Rect.top) - pItem->iHeight) / 2);
			}
			TempTwoHandItem.iPlaceX = sInven[1].Rect.left + (((sInven[1].Rect.right - sInven[1].Rect.left) - pItem->iWidth) / 2);
			TempTwoHandItem.iPlaceY = sInven[1].Rect.top + (((sInven[1].Rect.bottom - sInven[1].Rect.top) - pItem->iHeight) / 2);
			TempTwoHandItem.iWidth = pItem->iWidth;
			TempTwoHandItem.iHeight = pItem->iHeight;
			TempTwoHandItem.iItemSlot = 2;
			TempTwoHandItem.iItemSlotFlag = pItem->iItemSlotFlag;
			TempTwoHandItem.sItem.sItemID = pItem->sBaseItemID;
			TempTwoHandItem.sItem.iSalePrice = pItem->sItem.iSalePrice;
			memcpy(&TempTwoHandItem.pcInventoryTexture, &pItem->pcInventoryTexture, sizeof(void *));
			TempTwoHandItem.bValid = 1;
			for (int j = 0; j < INVENTORY_MAXITEM; j++)
			{
				if (InvenItem[j].bValid == 0)
				{
					memcpy(&InvenItem[j], &TempTwoHandItem, sizeof(ItemData));
					sInven[1].ItemIndex = j + 1;
					break;
				}
			}
		}
	}
	else if (pItem->iItemSlotFlag == ITEMSLOTFLAG_Wing)
	{
		if (pItem->iItemSlot == 16)
		{
			pItem->iItemSlot = 15;
			pItem->iPlaceX = sInven[14].Rect.left + (((sInven[14].Rect.right - sInven[14].Rect.left) - pItem->iWidth) / 2);
			pItem->iPlaceY = sInven[14].Rect.top + (((sInven[14].Rect.bottom - sInven[14].Rect.top) - pItem->iHeight) / 2);
		}
		TempTwoHandItem.iPlaceX = sInven[15].Rect.left + (((sInven[15].Rect.right - sInven[15].Rect.left) - pItem->iWidth) / 2);
		TempTwoHandItem.iPlaceY = sInven[15].Rect.top + (((sInven[15].Rect.bottom - sInven[15].Rect.top) - pItem->iHeight) / 2);
		TempTwoHandItem.iWidth = pItem->iWidth;
		TempTwoHandItem.iHeight = pItem->iHeight;
		TempTwoHandItem.iItemSlot = 16;
		TempTwoHandItem.iItemSlotFlag = pItem->iItemSlotFlag;
		TempTwoHandItem.sItem.sItemID = pItem->sBaseItemID;
		TempTwoHandItem.sItem.iSalePrice = pItem->sItem.iSalePrice;
		memcpy(&TempTwoHandItem.pcInventoryTexture, &pItem->pcInventoryTexture, sizeof(void *));
		TempTwoHandItem.bValid = 1;
		for (int j = 0; j < INVENTORY_MAXITEM; j++)
		{
			if (InvenItem[j].bValid == 0)
			{
				memcpy(&InvenItem[j], &TempTwoHandItem, sizeof(ItemData));
				sInven[15].ItemIndex = j + 1;
				break;
			}
		}
	}

	return TRUE;
}

int cINVENTORY::PickUpTwoHandItem(ItemData *pItem)
{
	ItemData TempPickItem;
	memset(&TempPickItem, 0, sizeof(ItemData));

	DWORD TempCode = pItem->sBaseItemID.ToInt() & sinITEM_MASK2;

	if (TempCode != sinWD1)
	{
		if (pItem->iItemSlot == 1 || pItem->iItemSlot == 2)
		{
			if (sInven[0].ItemIndex && sInven[1].ItemIndex)
			{
				memcpy(&TempPickItem, &InvenItem[sInven[0].ItemIndex - 1], sizeof(ItemData));
				InvenItem[sInven[0].ItemIndex - 1].bValid = 0;
				InvenItem[sInven[1].ItemIndex - 1].bValid = 0;
				sInven[0].ItemIndex = 0;
				sInven[1].ItemIndex = 0;
				memcpy(pItem, &TempPickItem, sizeof(ItemData));
				ReFormInvenItem();
				ReformCharForm();
				ReFormPotionNum();
				return TRUE;
			}
		}
		else if (pItem->iItemSlot == 15 || pItem->iItemSlot == 16)
		{
			if (sInven[14].ItemIndex && sInven[15].ItemIndex)
			{
				memcpy(&TempPickItem, &InvenItem[sInven[14].ItemIndex - 1], sizeof(ItemData));
				InvenItem[sInven[14].ItemIndex - 1].bValid = 0;
				InvenItem[sInven[15].ItemIndex - 1].bValid = 0;
				sInven[14].ItemIndex = 0;
				sInven[15].ItemIndex = 0;
				memcpy(pItem, &TempPickItem, sizeof(ItemData));
				ReFormInvenItem();
				ReformCharForm();
				ReFormPotionNum();
				return TRUE;
			}
		}
	}
	else
	{
		switch (pItem->iItemSlot)
		{
		case 1:
			pItem->iVisibleItemType = ITEMSLOTFLAG_RightHand;
			return TRUE;
		case 2:
			pItem->iVisibleItemType = ITEMSLOTFLAG_LeftHand;
			return TRUE;
		}
	}
	return FALSE;
}
int cINVENTORY::OverlapTwoHandItem(ItemData *pItem)
{
	AutoSetItemIndex = 0;
	if (pItem->iItemSlotFlag == ITEMSLOTFLAG_LeftRightHand && (pItem->sBaseItemID.ToInt() & sinITEM_MASK2) != sinWD1)
	{
		if (sInven[1].ItemIndex)
		{
			if (InvenItem[sInven[1].ItemIndex - 1].iItemSlotFlag != ITEMSLOTFLAG_LeftRightHand || (InvenItem[sInven[1].ItemIndex - 1].sBaseItemID.ToInt() & sinITEM_MASK2) == sinWD1)
			{
				if (pItem->iItemSlot == 1)
				{
					if (sInven[1].ItemIndex)
						AutoSetItemIndex = sInven[1].ItemIndex;
				}
				if (pItem->iItemSlot == 2)
				{
					if (sInven[0].ItemIndex)
						AutoSetItemIndex = sInven[0].ItemIndex;
				}
			}
		}
	}
	else if (pItem->iItemSlotFlag == ITEMSLOTFLAG_Wing)
	{
		if (sInven[15].ItemIndex)
		{
			if (InvenItem[sInven[15].ItemIndex - 1].iItemSlotFlag != ITEMSLOTFLAG_Wing)
			{
				if (pItem->iItemSlot == 16)
				{
					if (sInven[15].ItemIndex)
						AutoSetItemIndex = sInven[15].ItemIndex;
				}
				if (pItem->iItemSlot == 15)
				{
					if (sInven[14].ItemIndex)
						AutoSetItemIndex = sInven[14].ItemIndex;
				}
			}
		}
	}
	return TRUE;
}
int cINVENTORY::OverlapTwoHandSwitch(ItemData *pItem)
{
	if (pItem->iItemSlotFlag == ITEMSLOTFLAG_LeftRightHand && (pItem->sBaseItemID.ToInt() & sinITEM_MASK2) != sinWD1)
	{
		if (pItem->iItemSlot == 1)
		{
			if (sInven[1].ItemIndex)
				CrashItemIndex[0] = sInven[1].ItemIndex;
		}
		if (pItem->iItemSlot == 2)
		{
			if (sInven[0].ItemIndex)
				CrashItemIndex[0] = sInven[0].ItemIndex;
		}
	}
	else if (pItem->iItemSlotFlag == ITEMSLOTFLAG_Wing)
	{
		if (pItem->iItemSlot == 15)
		{
			if (sInven[15].ItemIndex)
				CrashItemIndex[0] = sInven[15].ItemIndex;
		}
		if (pItem->iItemSlot == 16)
		{
			if (sInven[14].ItemIndex)
				CrashItemIndex[0] = sInven[14].ItemIndex;

		}
	}
	return TRUE;
}
int cINVENTORY::InvenNotOpenCheck(ItemData *pItem)
{
	if (!OpenFlag)
	{
		if (pItem->iItemSlot != 11 && pItem->iItemSlot != 12 && pItem->iItemSlot != 13)
			return FALSE;
	}
	return TRUE;
}

int cINVENTORY::PickUpInvenItem(int x, int y, int PickUpFlag)
{
	NotPotionFlag = 0;
	sITEMPRICE sinItemPriceTemp;
	SelectInvenItemIndex = 0;
	SelectPotionIndex = 0;
	int kk = 0;
	for (int i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].bValid)
		{
			if (InvenItem[i].iPlaceX < x  &&
				InvenItem[i].iPlaceX + InvenItem[i].iWidth > x  &&
				InvenItem[i].iPlaceY < y  &&
				InvenItem[i].iPlaceY + InvenItem[i].iHeight > y)
			{
				if (!InvenNotOpenCheck(&InvenItem[i]))
					return FALSE;
				if (PickUpFlag == 1)
				{
					if (MyShopItemIndex[i])
						return FALSE;
					if (InvenItem[i].iItemSlot)
					{
						if (sinChar->sWeight.sMin > sinChar->sWeight.sMax)
						{
							cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
							sinOverWeightCnt++;
							return FALSE;
						}
					}
					if (!((smTEXTUREHANDLE *)InvenItem[i].pcInventoryTexture)->m_pTexture)
					{
						cMessageBox.ShowMessage(MESSAGE_NOTEXIT_ITEMIMAGE);
						return FALSE;
					}
					for (int j = 0; j < SIN_MAX_HELP_NUMBER; j++)
					{
						if (sSinHelp[j].KindFlag == SIN_HELP_KIND_TELEPORT_SCROLL)
							return FALSE;
					}
					if (CURSORHANDLE->GetMouseCurosr() == ECURSORICON_Repair)
					{
						sinItemPriceTemp = GetInvenItemPrice(&InvenItem[i]);

						if (RepairInvenItem(&InvenItem[i], sinItemPriceTemp.RepairCost))
							sinPlaySound(SIN_SOUND_REPAIR_ITEM);
						return TRUE;
					}
					InvenItem[i].iOldX = InvenItem[i].iPlaceX;
					InvenItem[i].iOldY = InvenItem[i].iPlaceY;
					pMessageItem = &InvenItem[i];
					PotionIndex = i + 1;
					BackUpItemIndex = i + 1;

					if (sinChar->CostmePos == TRUE)
					{
						if (InvenItem[i].iItemSlot == 1 || InvenItem[i].iItemSlot == 2 || InvenItem[i].iItemSlot == 3)
							continue;
					}
					else
					{
						if (InvenItem[i].iItemSlot == 14 || InvenItem[i].iItemSlot == 15 || InvenItem[i].iItemSlot == 16)
							continue;
					}

					if (CURSORHANDLE->GetMouseCurosr() == ECURSORICON_Sell)
					{
						if (!InvenItem[i].sItem.iChk2)
							return TRUE;

						for (kk = 0; kk < NotSell_Item_CODECnt; kk++)
						{
							if (NotSell_Item_CODE[kk] == InvenItem[i].sItem.sItemID.ToInt())
								return TRUE;
						}
						for (kk = 0; kk < NotSell_Item_MASKCnt; kk++)
						{
							if ((InvenItem[i].sItem.sItemID.ToItemType()) == NotSell_Item_MASK[kk])
								return TRUE;
						}
						for (kk = 0; kk < NotSell_Item_KINDCnt; kk++)
						{
							if (NotSell_Item_KIND[kk] == InvenItem[i].sItem.eCraftType)
								return TRUE;
						}
						if (InvenItem[i].iItemSlotFlag == ITEMSLOTFLAG_Potion || InvenItem[i].sItem.sItemID.ToInt() == (sinGF1 | sin01))
							return TRUE;
						else
						{
							if (!cShop.SellItemToShop(&InvenItem[i]))
								return TRUE;
						}
					}
					else
					{
						if (InvenItem[i].iItemSlotFlag == ITEMSLOTFLAG_LeftRightHand ||
							InvenItem[i].iItemSlotFlag == ITEMSLOTFLAG_Wing)
							PickUpTwoHandItem(&InvenItem[i]);
						memcpy(&MouseItem, &InvenItem[i], sizeof(ItemData));
					}

					InvenItem[i].bValid = 0;
					if (InvenItem[i].iItemSlot)
					{
						sinSetCharItem(InvenItem[i].sBaseItemID.ToInt(), InvenItem[i].iVisibleItemType, FALSE);
						sInven[InvenItem[i].iItemSlot - 1].ItemIndex = 0;
					}
					ReFormInvenItem();
					CheckWeight();
					SetItemToChar();
					sinPlaySound(InvenItem[i].iInvItemSound);
					ColorIndex = 0;
					CheckPuzzle();
					cHelpPet.PetMessage("*InvenTory_Item", 1);
					return TRUE;
				}
				else if (PickUpFlag == 2)
				{
					if (MyShopSendButton)
						return FALSE;
					if (MyShopItemIndex[i])
						return FALSE;
					if (InvenItem[i].iItemSlot)
						return FALSE;
					if (InvenItem[i].sItem.sItemID.ToInt() == (sinGF1 | sin01))
						return FALSE;

					if (InvenItem[i].sItem.sItemID.ToInt() == (sinOA1 | sin36))
						return FALSE;

					if (InvenItem[i].sItem.sItemID.ToInt() == (sinOA1 | sin37))
						return FALSE;

					for (kk = 0; kk < NotSell_Item_CODECnt; kk++)
					{
						if (NotSell_Item_CODE[kk] == InvenItem[i].sItem.sItemID.ToInt())
							return FALSE;
					}
					for (kk = 0; kk < NotSell_Item_MASKCnt; kk++)
					{
						if ((InvenItem[i].sItem.sItemID.ToItemType()) == NotSell_Item_MASK[kk])
							return FALSE;
					}
					for (kk = 0; kk < NotSell_Item_KINDCnt; kk++)
					{
						if (NotSell_Item_KIND[kk] == InvenItem[i].sItem.eCraftType)
							return FALSE;
					}

					memcpy(&MyShopMouseItem, &InvenItem[i], sizeof(ItemData));
					ZeroMemory(&MyShopMouseItem.sItem, sizeof(Item));

					MyShopMouseItem.sItem.iPotionCount = InvenItem[i].sItem.iPotionCount;
					MyShopMouseItem.sItem.iChk1 = InvenItem[i].sItem.iChk1;
					MyShopMouseItem.sItem.dwVersion = InvenItem[i].sItem.dwVersion;
					MyShopMouseItem.sItem.dwTime = InvenItem[i].sItem.dwTime;
					MyShopMouseItem.sItem.iChk2 = InvenItem[i].sItem.iChk2;
					MyShopMouseItem.sItem.iIndex = i + 1;
					sinMyShopItemPass = 1;
				}
				else
				{
					if (InvenItem[i].iItemSlotFlag == ITEMSLOTFLAG_Potion)
					{
						if (!InvenItem[i].iItemSlot)
							SelectPotionIndex = i + 1;
					}
					if (sinChar->CostmePos == TRUE)
					{
						if (InvenItem[i].iItemSlot == 1 ||
							InvenItem[i].iItemSlot == 2 ||
							InvenItem[i].iItemSlot == 3)
							continue;
					}
					else
					{
						if (InvenItem[i].iItemSlot == 14 ||
							InvenItem[i].iItemSlot == 15 ||
							InvenItem[i].iItemSlot == 16)
							continue;
					}
					cItem.GetItemLimitTime(&InvenItem[i]);
					SelectInvenItemIndex = i + 1;
					ColorIndex = SELECT_ITEM_COLOR;
					sinShowItemInfoFlag = 2;
					cHelpPet.PetMessage("*InvenTory_Item", 0);

					if (cMyShop.OpenFlag)
						cItem.ShowItemInfo(&InvenItem[i], 2, i);
					else
						cItem.ShowItemInfo(&InvenItem[i], 2);
				}
			}
		}
	}
	return FALSE;
}
int cINVENTORY::SetInvenItemAreaCheck(ItemData *pItem)
{
	int i, j;
	ColorIndex = 0;
	CrashItemIndex[0] = 0;
	CrashItemIndex[1] = 0;
	AutoSetItemIndex = 0;

	if (!cInvenTory.OpenFlag)
		return FALSE;
	for (i = 0; i < INVENTORY_MAX_POS; i++)
	{
		if (CheckInvenPos(pItem->iPlaceX + 11,
			pItem->iPlaceY + 11,
			pItem->iPlaceX + pItem->iWidth - 11,
			pItem->iPlaceY + pItem->iHeight - 11,
			sInven[i].Rect))
		{
			if (sinChar->CostmePos == TRUE)
			{
				if (i == 0 || i == 1 || i == 2)
					continue;
			}
			else
			{
				if (i == 13 || i == 14 || i == 15)
					continue;
			}
			ColorRect.left = sInven[i].Rect.left;
			ColorRect.top = sInven[i].Rect.top;
			ColorRect.right = sInven[i].Rect.right - sInven[i].Rect.left;
			ColorRect.bottom = sInven[i].Rect.bottom - sInven[i].Rect.top;
			pItem->iPlaceX = sInven[i].Rect.left + ((ColorRect.right - pItem->iWidth) / 2);
			pItem->iPlaceY = ColorRect.top + ((ColorRect.bottom - pItem->iHeight) / 2);
			pItem->iItemSlot = i + 1;

			if (!(sInven[i].Position & pItem->iItemSlotFlag))
			{
				ColorIndex = NOT_SETTING_COLOR;
				return FALSE;
			}
			if (pItem->sItem.bCanNotUse)
			{
				ColorIndex = NOT_USE_COLOR;
				return FALSE;
			}
			if (sinChar->iClass == CHARACTERCLASS_Assassin)
			{
				if (pItem->iItemSlot == 2 && (pItem->sItem.sItemID.ToItemType()) == sinDS1)
				{
					ColorIndex = NOT_SETTING_COLOR;
					return FALSE;
				}
			}
			else
			{
				if (pItem->iItemSlot == 2 && (pItem->sItem.sItemID.ToItemType()) == sinWD1)
				{
					ColorIndex = NOT_SETTING_COLOR;
					return FALSE;
				}
			}
			CrashItemIndex[0] = CrashInvenItem(ColorRect);

			if (CrashItemIndex[0])
			{
				OverlapTwoHandItem(pItem);
				ColorIndex = OVERLAP_BOX_COLOR;
				return TRUE;
			}
			OverlapTwoHandSwitch(pItem);
			ColorIndex = SET_ITEM_CHECK_COLOR;
			return TRUE;
		}
	}
	for (i = pItem->iPlaceX + 11; i < pItem->iPlaceX + pItem->iWidth; i += 22)
	{
		for (j = pItem->iPlaceY + 11; j < pItem->iPlaceY + pItem->iHeight; j += 22)
		{
			if (StartX <= i && EndX > i && StartY <= j && EndY > j)
			{
				ColorRect.left = StartX + (((i - StartX) / 22) * 22);
				ColorRect.top = StartY + (((j - StartY) / 22) * 22);
				ColorRect.right = pItem->iWidth;
				ColorRect.bottom = pItem->iHeight;
				if (EndX < (ColorRect.left + ColorRect.right) - 11 || EndY < (ColorRect.top + ColorRect.bottom) - 11)
				{
					InitColorRect();
					return FALSE;
				}
				pItem->iPlaceX = ColorRect.left;
				pItem->iPlaceY = ColorRect.top;
				pItem->iItemSlot = 0;
				ColorIndex = SET_ITEM_CHECK_COLOR;
				if (CrashItemIndex[0] = CrashInvenItem(ColorRect))
				{
					if (CrashItemIndex[1] = CrashInvenItem(ColorRect, CrashItemIndex[0]))
					{
						ColorIndex = NOT_SETTING_COLOR;
						CrashItemIndex[1] = 0;
						return FALSE;
					}
					ColorIndex = OVERLAP_ITEM_COLOR;
					return TRUE;
				}
				return TRUE;
			}
		}
	}

	return TRUE;
}
int cINVENTORY::InitColorRect()
{
	ColorRect.left = 0;
	ColorRect.top = 0;
	ColorRect.right = 0;
	ColorRect.bottom = 0;
	return TRUE;

}
int cINVENTORY::CrashInvenItem(RECT &desRect, int PassItemIndex)
{
	RECT rect;

	for (int i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].bValid)
		{
			if (PassItemIndex != 0)
			{
				if (PassItemIndex == i + 1)
					continue;
			}
			rect.left   = InvenItem[i].iPlaceX;
			rect.right  = InvenItem[i].iPlaceX + InvenItem[i].iWidth;
			rect.top    = InvenItem[i].iPlaceY;
			rect.bottom = InvenItem[i].iPlaceY + InvenItem[i].iHeight;

			if (desRect.left > rect.left - desRect.right  && desRect.left < rect.right && desRect.top > rect.top - desRect.bottom && desRect.top < rect.bottom)
			{
				if (sinChar->CostmePos)
				{
					if (InvenItem[i].iItemSlotFlag == ITEMSLOTFLAG_Armor ||
						InvenItem[i].iItemSlotFlag == ITEMSLOTFLAG_RightHand ||
						InvenItem[i].iItemSlotFlag == ITEMSLOTFLAG_LeftRightHand)
					{
						if (InvenItem[i].iItemSlot)
							continue;
					}
				}
				else
				{
					if (InvenItem[i].iItemSlotFlag == ITEMSLOTFLAG_Costume ||
						InvenItem[i].iItemSlotFlag == ITEMSLOTFLAG_Wing)
					{
						if (InvenItem[i].iItemSlot)
							continue;
					}
				}
				return i + 1;
			}
		}
	}

	return FALSE;

}
int cINVENTORY::CheckInvenPos(int x, int y, int lx, int ly, RECT &rect)
{
	if (x <= rect.left)
	{
		if (rect.left >= lx)
			return FALSE;
	}
	else
	{
		if (x >= rect.right)
			return FALSE;
	}
	if (y <= rect.top)
	{
		if (rect.top >= ly)
			return FALSE;
	}
	else
	{
		if (y >= rect.bottom)
			return FALSE;
	}

	return TRUE;
}
int cINVENTORY::ChangeInvenItem(ItemData *pItem)
{
	int BackUpX = 0, BackUpY = 0, BackUpPosi = 0;
	for (int j = 0; j < SIN_MAX_HELP_NUMBER; j++)
	{
		if (sSinHelp[j].KindFlag == SIN_HELP_KIND_TELEPORT_SCROLL)
		{
			return TRUE;
			if (NoSettingThrowItem(&MouseItem))
				return FALSE;
		}
	}

	if (lpCurPlayer->psModelAnimation->iType == ANIMATIONTYPE_Attack || lpCurPlayer->psModelAnimation->iType == ANIMATIONTYPE_Skill)
		return FALSE;
	if (!InvenNotOpenCheck(pItem))
		return FALSE;
	if (CrashItemIndex[0])
	{
		CheckInvenItemForm();
		if (InvenItem[CrashItemIndex[0] - 1].iItemSlotFlag == ITEMSLOTFLAG_Potion)
		{
			if (pMessageItem)
			{
				BackUpX = pMessageItem->iPlaceX;
				BackUpY = pMessageItem->iPlaceY;
				BackUpPosi = pMessageItem->iItemSlot;
				sinPosionItem = &InvenItem[CrashItemIndex[0] - 1];
				BackUpItemIndex = CrashItemIndex[0];
			}
		}
		if (InvenItem[CrashItemIndex[0] - 1].iItemSlotFlag == ITEMSLOTFLAG_LeftRightHand || InvenItem[CrashItemIndex[0] - 1].iItemSlotFlag == ITEMSLOTFLAG_Wing)
			PickUpTwoHandItem(&InvenItem[CrashItemIndex[0] - 1]);

		memcpy(&TempItem, &InvenItem[CrashItemIndex[0] - 1], sizeof(ItemData));
		if (InvenItem[CrashItemIndex[0] - 1].iItemSlot)
			sinSetCharItem(InvenItem[CrashItemIndex[0] - 1].sBaseItemID.ToInt(), InvenItem[CrashItemIndex[0] - 1].iVisibleItemType, FALSE);
		InvenItem[CrashItemIndex[0] - 1].bValid = 0;
		TempItem.iPlaceX = pItem->iPlaceX;
		TempItem.iPlaceY = pItem->iPlaceY;
		if (AutoSetItemIndex)
		{
			ReFormInvenItem();
			sinSetCharItem(InvenItem[AutoSetItemIndex - 1].sBaseItemID.ToInt(), InvenItem[AutoSetItemIndex - 1].iVisibleItemType, FALSE);
			if (!InvenEmptyAearCheck(&InvenItem[AutoSetItemIndex - 1]))
			{
				if (AutoSetItemIndex)
					NoSettingThrowItem(&InvenItem[AutoSetItemIndex - 1], 1);
			}
		}
		ReFormInvenItem();
		LastSetInvenItem(pItem);
		memcpy(pItem, &TempItem, sizeof(ItemData));
		if (sinPosionItem)
		{
			if (InvenItem[CrashItemIndex[0] - 1].iItemSlotFlag == ITEMSLOTFLAG_Potion)
			{
				pMessageItem = sinPosionItem;
				pMessageItem->iPlaceX = BackUpX;
				pMessageItem->iPlaceY = BackUpY;
				pMessageItem->iItemSlot = BackUpPosi;
				sinPosionItem = 0;
			}
		}
		ReFormInvenItem();
		return TRUE;
	}

	return FALSE;
}
int cINVENTORY::NoSettingThrowItem(ItemData *pItem, int Flag)
{
	if (!pItem || !pItem->bValid)
		return FALSE;
	if (!Flag)
	{
		if (cTrade.OpenFlag || cWareHouse.OpenFlag || cCraftItem.OpenFlag || cAging.OpenFlag || SmeltingItem.OpenFlag || ManufactureItem.m_OpenFlag || cMixtureReset.OpenFlag || cElement.OpenFlag || cCaravan.OpenFlag || cSocket.OpenFlag)
			return FALSE;
	}
	if (!pItem->sItem.iChk1 || pItem->sItem.iChk1 < 0)
		return FALSE;
	if (pItem->sItem.sItemID.ToInt() == (sinGF1 | sin01))
		return FALSE;

	int kk = 0;

	for (kk = 0; kk < NotDrow_Item_CODECnt; kk++)
	{
		if (NotDrow_Item_CODE[kk] == pItem->sItem.sItemID.ToInt())
			return FALSE;
	}
	for (kk = 0; kk < NotDrow_Item_MASKCnt; kk++)
	{
		if (pItem->sItem.sItemID.ToItemType() == NotDrow_Item_MASK[kk])
			return FALSE;
	}
	for (kk = 0; kk < NotDrow_Item_KINDCnt; kk++)
	{
		if (NotDrow_Item_KIND[kk] == pItem->sItem.eCraftType)
			return FALSE;
	}

	if (sinThrowItemToFeild(pItem))
	{
		sinPlaySound(pItem->iInvItemSound);
		pItem->bValid = 0;
	}
	else
		pItem->bValid = 0;

	return TRUE;
}
int cINVENTORY::ThrowInvenItemToField(ItemData *pItem)
{
	if (cTrade.OpenFlag || cWareHouse.OpenFlag || cShop.OpenFlag || cCraftItem.OpenFlag || cAging.OpenFlag || SmeltingItem.OpenFlag || ManufactureItem.m_OpenFlag || cMixtureReset.OpenFlag || cElement.OpenFlag || cCaravan.OpenFlag || cSocket.OpenFlag)
		return TRUE;

	if (sMessageBox3[MESSAGE_TELEPORT_CORE].Flag)
		return TRUE;
	for (int i = 0; i < SIN_MAX_HELP_NUMBER; i++)
	{
		if (sSinHelp[i].KindFlag == SIN_HELP_KIND_TELEPORT_SCROLL)
			return TRUE;
	}

	int kk = 0;

	for (kk = 0; kk < NotDrow_Item_CODECnt; kk++)
	{
		if (NotDrow_Item_CODE[kk] == pItem->sItem.sItemID.ToInt())
			return TRUE;
	}
	for (kk = 0; kk < NotDrow_Item_MASKCnt; kk++)
	{
		if (pItem->sItem.sItemID.ToItemType() == NotDrow_Item_MASK[kk])
			return TRUE;

	}
	for (kk = 0; kk < NotDrow_Item_KINDCnt; kk++)
	{
		if (NotDrow_Item_KIND[kk] == pItem->sItem.eCraftType)
			return TRUE;
	}

	if (cCraftItem.OpenFlag)
	{
		if (0 < pCursorPos.x && 256 + 128 > pCursorPos.x && 130 < pCursorPos.y && 130 + (22 * 10) > pCursorPos.y)
			return TRUE;
	}
	if (pItem->sItem.sItemID.ToInt() == (sinGF1 | sin01))
		return TRUE;

	if (pItem->sItem.SpecialItemFlag[0] == CHECK_COPY_ITEM ||
		pItem->sItem.SpecialItemFlag[0] == CHECK_GIVE_ITEM ||
		pItem->sItem.eCraftType == ITEMCRAFTTYPE_Quest ||
		pItem->sItem.sItemID.ToItemType() == sinMA1 ||
		pItem->sItem.sItemID.ToItemType() == sinMA2 ||
		pItem->sItem.sItemID.ToItemType() == sinQW1 ||
		pItem->sItem.sItemID.ToItemType() == sinBI1 ||
		pItem->sItem.sItemID.ToItemType() == sinBI2 ||
		pItem->sItem.sItemID.ToInt() == (sinOA2 | sin31) ||
		pItem->sItem.sItemID.ToInt() == (sinOA2 | sin32) ||
		pItem->sItem.sItemID.ToInt() == (sinDB1 | sin31) ||
		pItem->sItem.sItemID.ToInt() == (sinDB1 | sin32) ||
		pItem->sItem.sItemID.ToInt() == (sinOA1 | sin36) ||
		pItem->sItem.sItemID.ToInt() == (sinOA1 | sin37) ||
		pItem->sItem.sItemID.ToInt() == (sinDB1 | sin33) ||
		pItem->sItem.sItemID.ToInt() == (sinOA2 | sin33) ||
		pItem->sItem.sItemID.ToInt() == (sinDB1 | sin34) ||
		pItem->sItem.sItemID.ToInt() == (sinOA2 | sin34) ||
		pItem->sItem.sItemID.ToInt() == (sinBI1 | sin84) ||
		pItem->sItem.sItemID.ToInt() == (sinGF1 | sin07) || pItem->sItem.sItemID.ToInt() == (sinGF1 | sin08))
		return TRUE;

	if (!pItem->bValid)
		return FALSE;
	if (OpenFlag)
	{
		if (pItem->iPlaceY + pItem->iHeight < (600) - 180)
		{
			if (pItem->iItemSlotFlag == ITEMSLOTFLAG_Potion)
			{
				if (pItem->sItem.iPotionCount == 1)
				{
					if (sinThrowItemToFeild(pItem))
					{
						sinPlaySound(pItem->iInvItemSound);
						pItem->bValid = 0;
						ReFormPotionNum();
						return TRUE;
					}
				}
				if (pMessageItem)
				{
					if (GhostPotionCheckFlag)
					{
						if (sinThrowItemToFeild(pItem))
						{
							sinPlaySound(pItem->iInvItemSound);
							pItem->bValid = 0;
							GhostPotionCheckFlag = 0;
							ReFormPotionNum();
							return TRUE;
						}
					}
					cMessageBox.ShowMessage2(MESSAGE_THROW_ITEM);
					pItem->bValid = 0;
					pMessageItem->bValid = 1;
					sInven[pMessageItem->iItemSlot - 1].ItemIndex = BackUpItemIndex;
					CheckOverlapItem(pMessageItem, BackUpItemIndex);
					ReSettingPotion();
					CheckWeight();
					ReFormPotionNum();
					if (pMessageItem->iItemSlot)
						sInven[pMessageItem->iItemSlot - 1].ItemIndex = PotionIndex;
					return TRUE;
				}
			}
			if (sinThrowItemToFeild(pItem))
			{
				sinPlaySound(pItem->iInvItemSound);
				pItem->bValid = 0;
			}
		}
	}
	else
	{
		if (pItem->iPlaceY + pItem->iHeight < 540)
		{
			if (pItem->iItemSlotFlag == ITEMSLOTFLAG_Potion)
			{
				if (pItem->sItem.iPotionCount == 1)
				{
					if (sinThrowItemToFeild(pItem))
					{
						sinPlaySound(pItem->iInvItemSound);
						pItem->bValid = 0;
						return TRUE;
					}
				}
				if (pMessageItem)
				{
					if (GhostPotionCheckFlag)
					{
						if (sinThrowItemToFeild(pItem))
						{
							sinPlaySound(pItem->iInvItemSound);
							pItem->bValid = 0;
							GhostPotionCheckFlag = 0;
							ReFormPotionNum();
							return TRUE;
						}
					}
					cMessageBox.ShowMessage2(MESSAGE_THROW_ITEM);
					pItem->bValid = 0;
					pMessageItem->bValid = 1;
					sInven[pMessageItem->iItemSlot - 1].ItemIndex = BackUpItemIndex;
					CheckOverlapItem(pMessageItem, BackUpItemIndex);
					ReSettingPotion();
					CheckWeight();
					ReFormPotionNum();
					if (pMessageItem->iItemSlot)
						sInven[pMessageItem->iItemSlot - 1].ItemIndex = PotionIndex;
					return TRUE;
				}
			}
			if (sinThrowItemToFeild(pItem))
			{
				sinPlaySound(pItem->iInvItemSound);
				pItem->bValid = 0;
			}
		}
	}
	return TRUE;
}
int cINVENTORY::CharOnlySetItem(ItemData *pItem)
{
	if (sinChar->iClass == CHARACTERCLASS_Priestess || sinChar->iClass == CHARACTERCLASS_Atalanta || sinChar->iClass == CHARACTERCLASS_Archer || sinChar->iClass == CHARACTERCLASS_Assassin)
	{
		if (pItem->sItem.sItemID.ToItemType() == sinCA1)
		{
			if ((pItem->sItem.sItemID.ToItemIndex()) == sin31 || (pItem->sItem.sItemID.ToItemIndex()) == sin33 ||
				(pItem->sItem.sItemID.ToItemIndex()) == sin36 || (pItem->sItem.sItemID.ToItemIndex()) == sin38 ||
				(pItem->sItem.sItemID.ToItemIndex()) == sin40 || (pItem->sItem.sItemID.ToItemIndex()) == sin42 ||
				(pItem->sItem.sItemID.ToItemIndex()) == sin44 || (pItem->sItem.sItemID.ToItemIndex()) == sin46 ||
				(pItem->sItem.sItemID.ToItemIndex()) == sin48 || (pItem->sItem.sItemID.ToItemIndex()) == sin50 ||
				(pItem->sItem.sItemID.ToItemIndex()) == sin52 || (pItem->sItem.sItemID.ToItemIndex()) == sin54 ||
				(pItem->sItem.sItemID.ToItemIndex()) == sin56 || (pItem->sItem.sItemID.ToItemIndex()) == sin58 ||
				(pItem->sItem.sItemID.ToItemIndex()) == sin60 || (pItem->sItem.sItemID.ToItemIndex()) == sin62 ||
				(pItem->sItem.sItemID.ToItemIndex()) == sin64 || (pItem->sItem.sItemID.ToItemIndex()) == sin66 ||
				(pItem->sItem.sItemID.ToItemIndex()) == sin68 || (pItem->sItem.sItemID.ToItemIndex()) == sin70 ||
				(pItem->sItem.sItemID.ToItemIndex()) == sin73 || (pItem->sItem.sItemID.ToItemIndex()) == sin91 ||
				(pItem->sItem.sItemID.ToItemIndex()) == sin93)
				pItem->sItem.bCanNotUse = TRUE;
		}
		if ((pItem->sItem.sItemID.ToItemType()) == sinDA1 || (pItem->sItem.sItemID.ToItemType()) == sinDA2)
		{
			if ((pItem->sItem.sItemID.ToItemIndex()) == sin71 || (pItem->sItem.sItemID.ToItemIndex()) == sin73 ||
				(pItem->sItem.sItemID.ToItemIndex()) == sin75 || (pItem->sItem.sItemID.ToItemIndex()) == sin77 ||
				(pItem->sItem.sItemID.ToItemIndex()) == sin79 || (pItem->sItem.sItemID.ToItemIndex()) == sin81 ||
				(pItem->sItem.sItemID.ToItemIndex()) == sin83 || (pItem->sItem.sItemID.ToItemIndex()) == sin85 ||
				(pItem->sItem.sItemID.ToItemIndex()) == sin87 || (pItem->sItem.sItemID.ToItemIndex()) == sin89)
				pItem->sItem.bCanNotUse = TRUE;
		}
	}
	else
	{
		if ((pItem->sItem.sItemID.ToItemType()) == sinCA1)
		{
			if ((pItem->sItem.sItemID.ToItemIndex()) == sin32 || (pItem->sItem.sItemID.ToItemIndex()) == sin34 ||
				(pItem->sItem.sItemID.ToItemIndex()) == sin37 || (pItem->sItem.sItemID.ToItemIndex()) == sin39 ||
				(pItem->sItem.sItemID.ToItemIndex()) == sin41 || (pItem->sItem.sItemID.ToItemIndex()) == sin43 ||
				(pItem->sItem.sItemID.ToItemIndex()) == sin45 || (pItem->sItem.sItemID.ToItemIndex()) == sin47 ||
				(pItem->sItem.sItemID.ToItemIndex()) == sin49 || (pItem->sItem.sItemID.ToItemIndex()) == sin51 ||
				(pItem->sItem.sItemID.ToItemIndex()) == sin53 || (pItem->sItem.sItemID.ToItemIndex()) == sin55 ||
				(pItem->sItem.sItemID.ToItemIndex()) == sin57 || (pItem->sItem.sItemID.ToItemIndex()) == sin59 ||
				(pItem->sItem.sItemID.ToItemIndex()) == sin61 || (pItem->sItem.sItemID.ToItemIndex()) == sin63 ||
				(pItem->sItem.sItemID.ToItemIndex()) == sin65 || (pItem->sItem.sItemID.ToItemIndex()) == sin67 ||
				(pItem->sItem.sItemID.ToItemIndex()) == sin69 || (pItem->sItem.sItemID.ToItemIndex()) == sin71 ||
				(pItem->sItem.sItemID.ToItemIndex()) == sin74 || (pItem->sItem.sItemID.ToItemIndex()) == sin92 ||
				(pItem->sItem.sItemID.ToItemIndex()) == sin94)
				pItem->sItem.bCanNotUse = TRUE;
		}
		if ((pItem->sItem.sItemID.ToItemType()) == sinDA1 || (pItem->sItem.sItemID.ToItemType()) == sinDA2)
		{
			if ((pItem->sItem.sItemID.ToItemIndex()) == sin72 || (pItem->sItem.sItemID.ToItemIndex()) == sin74 ||
				(pItem->sItem.sItemID.ToItemIndex()) == sin76 || (pItem->sItem.sItemID.ToItemIndex()) == sin78 ||
				(pItem->sItem.sItemID.ToItemIndex()) == sin80 || (pItem->sItem.sItemID.ToItemIndex()) == sin82 ||
				(pItem->sItem.sItemID.ToItemIndex()) == sin84 || (pItem->sItem.sItemID.ToItemIndex()) == sin86 ||
				(pItem->sItem.sItemID.ToItemIndex()) == sin88 || (pItem->sItem.sItemID.ToItemIndex()) == sin90)
				pItem->sItem.bCanNotUse = TRUE;
		}
	}
	if (sinChar->iClass == CHARACTERCLASS_Magician || sinChar->iClass == CHARACTERCLASS_Priestess || sinChar->iClass == CHARACTERCLASS_Shaman)
	{
		if ((pItem->sItem.sItemID.ToItemType()) == sinDA1)
			pItem->sItem.bCanNotUse = TRUE;
	}
	else
	{
		if ((pItem->sItem.sItemID.ToItemType()) == sinDA2 || (pItem->sItem.sItemID.ToItemType()) == sinOM1)
			pItem->sItem.bCanNotUse = TRUE;
	}

	return TRUE;
}
int cINVENTORY::CheckRequireItem()
{
	int NotUseItemFlag = 0;
	int i, j;

	for (i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].bValid)
		{
			if (InvenItem[i].sItem.iLevel > sinChar->iLevel)
				NotUseItemFlag = 1;
			if (InvenItem[i].sItem.iAgility > sinChar->iAgility)
				NotUseItemFlag = 1;
			if (InvenItem[i].sItem.iStrength > sinChar->iStrength)
				NotUseItemFlag = 1;
			if (InvenItem[i].sItem.iTalent > sinChar->iTalent)
				NotUseItemFlag = 1;
			if (InvenItem[i].sItem.iSpirit > sinChar->iSpirit)
				NotUseItemFlag = 1;
			if (InvenItem[i].sItem.iHealth > sinChar->iHealth)
				NotUseItemFlag = 1;
			if (DeleteEventItem_TimeOut(&InvenItem[i].sItem) == TRUE)
				NotUseItemFlag = 1;
			if (NotUseItemFlag)
			{
				InvenItem[i].sItem.bCanNotUse = TRUE;
				NotUseItemFlag = 0;
			}
			else
				InvenItem[i].sItem.bCanNotUse = FALSE;
			CharOnlySetItem(&InvenItem[i]);
			if ((InvenItem[i].sItem.sItemID.ToItemType()) == sinFO1)
			{
				for (j = 0; j < 16; j++)
				{
					if ((InvenItem[i].sItem.sItemID.ToItemIndex()) == SheltomCode2[j])
						break;
				}
				if ((InvenItem[i].sItem.sItemID.ToItemIndex()) < sin21)
				{
					if (sinChar->iLevel < ForceOrbUseLevel[j][0] || sinChar->iLevel > ForceOrbUseLevel[j][1])
					{
						InvenItem[i].sItem.bCanNotUse = TRUE;
						NotUseItemFlag = 0;
					}
					else
						InvenItem[i].sItem.bCanNotUse = FALSE;
				}
			}
		}
	}
	return TRUE;
}
int cINVENTORY::CheckRequireItemToSet(ItemData *pItem)
{
	int NotUseItemFlag = 0;

	if (pItem->sItem.iLevel > sinChar->iLevel)
		NotUseItemFlag = 1;
	if (pItem->sItem.iAgility > sinChar->iAgility)
		NotUseItemFlag = 1;
	if (pItem->sItem.iStrength > sinChar->iStrength)
		NotUseItemFlag = 1;
	if (pItem->sItem.iTalent > sinChar->iTalent)
		NotUseItemFlag = 1;
	if (pItem->sItem.iSpirit > sinChar->iSpirit)
		NotUseItemFlag = 1;
	if (pItem->sItem.iHealth > sinChar->iHealth)
		NotUseItemFlag = 1;
	if (NotUseItemFlag)
	{
		pItem->sItem.bCanNotUse = TRUE;
		NotUseItemFlag = 0;
	}
	else
		pItem->sItem.bCanNotUse = FALSE;

	CharOnlySetItem(pItem);
	return TRUE;
}

//äÖÈ¾ÎïÆ·ÎÄ×Ö
int cINVENTORY::DrawInvenText()
{
	char strBuff[128];

	memset(strBuff, 0, sizeof(strBuff));

	DWORD Color = D3DCOLOR_XRGB(255, 255, 255);

	POINT NoImageMessagePosi = { 0,0 };

	int i = 0;

	if (OpenFlag)
	{
		NumLineComa(sinChar->iGold, strBuff);
		dsTextLineOut(0, CheckEditSize(InvenTextPosi[0][0] + 26, InvenTextPosi[0][2], strBuff), InvenTextPosi[0][1] + (256 - sinMoveKindInter[SIN_INVENTORY]), strBuff, lstrlen(strBuff), Color);

		wsprintf(strBuff, "%d/%d", sinChar->sWeight.sMin, sinChar->sWeight.sMax);
		dsTextLineOut(0, CheckEditSize(InvenTextPosi[1][0], InvenTextPosi[1][2], strBuff), InvenTextPosi[1][1] + (256 - sinMoveKindInter[SIN_INVENTORY]), strBuff, lstrlen(strBuff), Color);
	}

	for (i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].bValid)
		{
			if (!((smTEXTUREHANDLE *)InvenItem[i].pcInventoryTexture)->m_pTexture)
			{
				if (InvenItem[i].iPlaceX > 10)
				{
					NoImageMessagePosi.x = InvenItem[i].iPlaceX + (InvenItem[i].iWidth / 2) - 5;
					NoImageMessagePosi.y = InvenItem[i].iPlaceY + (InvenItem[i].iHeight / 2) - 20;
					lstrcpy(strBuff, "NO");
					dsTextLineOut(0, NoImageMessagePosi.x, NoImageMessagePosi.y + (256 - sinMoveKindInter[SIN_INVENTORY]), strBuff, lstrlen(strBuff), Color);

					NoImageMessagePosi.x = InvenItem[i].iPlaceX + (InvenItem[i].iWidth / 2) - 15;
					NoImageMessagePosi.y = InvenItem[i].iPlaceY + (InvenItem[i].iHeight / 2) - 13;
					lstrcpy(strBuff, "IMAGE");
					dsTextLineOut(0, NoImageMessagePosi.x, NoImageMessagePosi.y + (256 - sinMoveKindInter[SIN_INVENTORY]) + 20, strBuff, lstrlen(strBuff), Color);
				}
			}
			if (InvenItem[i].iItemSlotFlag == ITEMSLOTFLAG_Potion)
			{
				wsprintf(strBuff, "%d", InvenItem[i].sItem.iPotionCount);

				if (InvenItem[i].iItemSlot == 11 ||
					InvenItem[i].iItemSlot == 12 ||
					InvenItem[i].iItemSlot == 13)
					dsTextLineOut(0,
						InvenItem[i].iPlaceX,
						InvenItem[i].iPlaceY,
						strBuff,
						lstrlen(strBuff),
						Color);
				else
				{
					if (OpenFlag)
						dsTextLineOut(0, 
							InvenItem[i].iPlaceX,
							InvenItem[i].iPlaceY + (256 - sinMoveKindInter[SIN_INVENTORY]),
							strBuff,
							lstrlen(strBuff),
							Color);
				}
			}
		}
	}


	int BackUpPosY = 0;
	int Start = 0, End = 0, Conut = 0;
	char szBuff2[128];

	if (nName == 1)
	{
		dsTextLineOut(1, BackStartPos.x + 60, BackStartPos.y, "Name", lstrlen("Name"), D3DCOLOR_XRGB(65, 177, 240));

		hFocusWnd = hTextWnd;
		sinMessageBoxShowFlag = 1;

		hFocusWnd = hTextWnd;
		GetWindowText(hFocusWnd, cInvenTory.szDoc, 20);

		SetIME_Mode(TRUE);

		int len = 0;
		int line = 1;
		len = lstrlen(cInvenTory.szDoc);

		line += (len / 20);

		for (int i = 0; i < len; i++)
		{
			ZeroMemory(szBuff2, sizeof(szBuff2));
			while (1)
			{
				if (cInvenTory.szDoc[End] == NULL)
					break;
				if (cInvenTory.szDoc[End] & 0x80)
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
			memcpy(szBuff2, &cInvenTory.szDoc[Start], End - Start);

			dsTextLineOut(0, BackStartPos.x + 32, BackStartPos.y + (i * 20) - 110, szBuff2, lstrlen(szBuff2), Color);

			if (cInvenTory.szDoc[End] != NULL)
			{
				if (cInvenTory.szDoc[End] == ' ')
					End += 1;
				Start = End;
				Conut = 0;
			}
			else break;
		}
	}

	return TRUE;
}

// èÖÃÖ°ÒµÌØÐ?
int cINVENTORY::SearchJobAndSetting()
{
	int iCounter = _countof(saCharacterClassData);

	for (int i = 0; i < iCounter; i++)
	{
		CharacterClassData * ps = saCharacterClassData + i;

		if (ps->iClass == sinChar->iClass)
		{
			auto PsCharacterClassData = GetCharacterClassData(sinChar->iClass, sinChar->iRank);

			if (PsCharacterClassData)
			{
				STRINGCOPY(JobName, PsCharacterClassData->pszName);
				sinChar->iFlag = (EClassFlag)ps->iClassBit;
				sinChar->iHPType = ps->iHP;
				sinChar->iMPType = ps->iMP;
				sinChar->iSPType = ps->iSP;
				sinDamageFunction[0] = ps->sDamage[0];
				sinDamageFunction[1] = ps->sDamage[1];
				sinDamageFunction[2] = ps->sUnk;
			}

			break;
		}
	}

	return TRUE;
}

// èÖÃÎïÆ·µ½½ÇÉ?
int cINVENTORY::SetItemToChar(int CheckHackFlag)
{
	ZeroMemory(&sElement_Attack, sizeof(sELEMENT_ATTACK));
	CheckCharForm();

	int i = 0;
	int j = 0;
	int t = 0;

	sinTempDamage2[0] = 0;
	sinTempDamage2[1] = 0;

	int cnt = 0;
	int sinAttack_Rating = 0;
	int sinAttack_Damage[2] = { 0,0 };
	int sinCritical = 0;
	int sinDefense = 0;
	float sinAbsorption = 0;
	int   sinTempAbsorption = 0;
	float sinTempAbsorption2 = 0;
	float sinBlock_Rate = 0;
	int sinWeight = 0;
	float sinMoveSpeed = 0;
	int sinWeaponSpeed = 0;
	int sinShooting_Range = 0;
	int sinSight = 0;
	int sinResistance[8] = { 0,0,0,0,0,0,0,0 };
	int sinPotion_Space = 2;
	int sinSkillMasteryItem = 0;

	int sinSkillDamage[2] = { 0,0 };
	int sinSkillResistance[8] = { 0,0,0,0,0,0,0,0 };
	int sinSkillWeaponSpeed = 0;

	int sinCharItemDamage = 0;

	float	sinAdd_fAbsorb = 0;
	int     sinAdd_Defence = 0;
	float   sinAdd_fSpeed = 0;
	float   sinAdd_fBlock_Rating = 0;
	int     sinAdd_Attack_Speed = 0;
	int     sinAdd_Critical_Hit = 0;
	int     sinAdd_Shooting_Range = 0;
	short	sinAdd_Resistance[8] = { 0,0,0,0,0,0,0,0 };

	short	sinLev_Attack_Resistance[8] = { 0,0,0,0,0,0,0,0 };
	int		sinLev_Mana = 0;
	int		sinLev_Life = 0;
	int     sinLev_Attack_Rating = 0;
	short	sinLev_Damage[2] = { 0,0 }; // ¹¥»÷Á¦

	float	sinPer_Mana_Regen = 0;
	float	sinPer_Life_Regen = 0;
	float 	sinPer_Stamina_Regen = 0;

	float fstrength, fhealth, ftalent, fLevel, fMaxWeight, fNowWeight, fSpirit, fDexterity;
	float fAttack_Rating, fDefense;

	sinAdd_fMagic_Mastery = 0;

	float sinfIncreLife = 0;
	float sinfIncreMana = 0;
	float sinfIncreStamina = 0;

	float sinfRegenLife = 0;
	float sinfRegenMana = 0;
	float sinfRegenStamina = 0;

	sinUndeadAbsorb = 0;

	int InvenCheckItem[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	ItemData sinTempItem;
	ZeroMemory(&sinTempItem, sizeof(ItemData));

	int CountAbsorbItem = 0;

	for (i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].bValid)
		{
			if (InvenItem[i].iItemSlot)
			{
				if (InvenItem[i].sItem.sItemID.ToInt() > sinPM1)
					continue;
				if (InvenItem[i].sItem.bCanNotUse)
					continue;

				if (!CheckRequireItemToSet2(&InvenItem[i]))
					continue;

				if ((InvenItem[i].iItemSlotFlag == ITEMSLOTFLAG_LeftRightHand &&
					(InvenItem[i].sBaseItemID.ToInt() & sinITEM_MASK2) != sinWD1) ||
					(InvenItem[i].iItemSlotFlag == ITEMSLOTFLAG_Wing))
				{
					if (InvenItem[i].sItem.iChk2 == 0)
						continue;
				}

				if (!InvenCheckItem[InvenItem[i].iItemSlot])
					InvenCheckItem[InvenItem[i].iItemSlot] = i + 1;
				else
					continue;
				if (!CheckItemForm(&InvenItem[i].sItem))
				{
					SendSetHackUser(1);
					InvenItem[i].bValid = 0;
					if (InvenItem[i].iItemSlot)
					{
						sInven[InvenItem[i].iItemSlot - 1].ItemIndex = 0;
						sinSetCharItem(InvenItem[i].sBaseItemID.ToInt(), InvenItem[i].iVisibleItemType, FALSE);
					}
					if (InvenItem[i].iItemSlotFlag == ITEMSLOTFLAG_LeftRightHand && (InvenItem[i].sBaseItemID.ToInt() & sinITEM_MASK2) != sinWD1)
					{
						InvenItem[sInven[1].ItemIndex - 1].bValid = 0;
						sInven[1].ItemIndex = 0;
					}
					else if (InvenItem[i].iItemSlotFlag == ITEMSLOTFLAG_Wing)
					{
						InvenItem[sInven[15].ItemIndex - 1].bValid = 0;
						sInven[15].ItemIndex = 0;
					}
					continue;
				}
				if ((InvenItem[i].sBaseItemID.ToInt() & sinITEM_MASK2) == sinWD1)
				{
					sinAttack_Rating += InvenItem[i].sItem.iAttackRating / 2;
					sinAttack_Damage[0] += InvenItem[i].sItem.sDamage.sMin / 2;
					sinAttack_Damage[1] += InvenItem[i].sItem.sDamage.sMax / 2;
					sinCritical += InvenItem[i].sItem.iCritical / 2;

					sinDefense += InvenItem[i].sItem.iDefenseRating / 2;
				}
				else
				{
					sinAttack_Rating += InvenItem[i].sItem.iAttackRating;
					sinAttack_Damage[0] += InvenItem[i].sItem.sDamage.sMin;
					sinAttack_Damage[1] += InvenItem[i].sItem.sDamage.sMax;
					sinCritical += InvenItem[i].sItem.iCritical;

					sinDefense += InvenItem[i].sItem.iDefenseRating;
				}

				sinTempAbsorption = (int)(GetItemAbsorb(&InvenItem[i].sItem)*10.000001f);
				sinTempAbsorption2 = ((float)sinTempAbsorption / 10.0f);
				sinTempAbsorption2 += 0.000001f;


				if (InvenItem[i].sItem.fAbsorbRating)
					CountAbsorbItem++;

				sinAbsorption += sinTempAbsorption2;

				if ((InvenItem[i].sBaseItemID.ToInt() & sinITEM_MASK2) == sinWD1)
				{
					sinBlock_Rate += InvenItem[i].sItem.fBlockRating / 2;
					sinMoveSpeed += InvenItem[i].sItem.fMovementSpeed / 2;
				}
				else
				{
					sinBlock_Rate += InvenItem[i].sItem.fBlockRating;
					sinMoveSpeed += InvenItem[i].sItem.fMovementSpeed;
				}

				if (CheckQuestItemDownFlag && InvenItem[i].sItem.eCraftType == ITEMCRAFTTYPE_QuestWeapon)
					sinWeaponSpeed += InvenItem[i].sItem.iAttackSpeed - 2;
				else
				{
					if ((InvenItem[i].sBaseItemID.ToInt() & sinITEM_MASK2) == sinWD1)
						sinWeaponSpeed += InvenItem[i].sItem.iAttackSpeed / 2;
					else
						sinWeaponSpeed += InvenItem[i].sItem.iAttackSpeed;
				}

				if ((InvenItem[i].sBaseItemID.ToInt() & sinITEM_MASK2) == sinWD1)
				{
					sinShooting_Range += InvenItem[i].sItem.iAttackRange / 2;
					sinSight += InvenItem[i].sItem.iSight / 2;
					sinfRegenLife += InvenItem[i].sItem.fHPRegen * 0.5f;
					sinfRegenMana += InvenItem[i].sItem.fMPRegen * 0.5f;
					sinfRegenStamina += InvenItem[i].sItem.fSPRegen * 0.5f;

					sinfIncreLife += InvenItem[i].sItem.fAddHP / 2;
					sinfIncreMana += InvenItem[i].sItem.fAddMP / 2;
					sinfIncreStamina += InvenItem[i].sItem.fAddSP / 2;
				}
				else
				{
					sinShooting_Range += InvenItem[i].sItem.iAttackRange;
					sinSight += InvenItem[i].sItem.iSight;
					sinfRegenLife += InvenItem[i].sItem.fHPRegen;
					sinfRegenMana += InvenItem[i].sItem.fMPRegen;
					sinfRegenStamina += InvenItem[i].sItem.fSPRegen;

					sinfIncreLife += InvenItem[i].sItem.fAddHP;
					sinfIncreMana += InvenItem[i].sItem.fAddMP;
					sinfIncreStamina += InvenItem[i].sItem.fAddSP;
				}

				sinAdd_fMagic_Mastery = InvenItem[i].sItem.fMagicMastery;

				if (InvenItem[i].sItem.iPotionStorage)
				{
					if (DeleteEventItem_TimeOut(&InvenItem[i].sItem) == TRUE)
						sinPotion_Space = 2;
					else
						sinPotion_Space = InvenItem[i].sItem.iPotionStorage;
				}
				if (sinChar->iFlag == InvenItem[i].sItem.eSpecialization)
				{
					sinTempAbsorption = (int)(InvenItem[i].sItem.sSpecData.fSpecAbsorbRating*10.000001f);
					sinTempAbsorption2 = ((float)sinTempAbsorption / 10.0f);
					sinTempAbsorption2 += 0.000001f;
					sinAdd_fAbsorb += sinTempAbsorption2;

					if (InvenItem[i].sItem.sSpecData.fSpecAbsorbRating)
						CountAbsorbItem++;

					if ((InvenItem[i].sBaseItemID.ToInt() & sinITEM_MASK2) == sinWD1)
					{
						sinAdd_Defence += InvenItem[i].sItem.sSpecData.iSpecDefenseRating / 2;
						sinAdd_fSpeed += InvenItem[i].sItem.sSpecData.fSpecMovementSpeed / 2;
						sinAdd_fBlock_Rating += InvenItem[i].sItem.sSpecData.fSpecBlockRating / 2;
						sinAdd_Attack_Speed += InvenItem[i].sItem.sSpecData.iSpecAttackSpeed / 2;
						sinAdd_Critical_Hit += InvenItem[i].sItem.sSpecData.iSpecCritical / 2;
						sinAdd_Shooting_Range += InvenItem[i].sItem.sSpecData.iSpecAttackRange / 2;
						sinAdd_fMagic_Mastery += InvenItem[i].sItem.sSpecData.fSpecMagicMastery / 2;

						if (InvenItem[i].sItem.sSpecData.iSpecAddMPDiv)
							sinLev_Mana += (sinChar->iLevel / InvenItem[i].sItem.sSpecData.iSpecAddMPDiv) / 2;
						if (InvenItem[i].sItem.sSpecData.iSpecAddHPDiv)
							sinLev_Life += (sinChar->iLevel / InvenItem[i].sItem.sSpecData.iSpecAddHPDiv) / 2;
						if (InvenItem[i].sItem.sSpecData.iSpecAttackRatingDiv)
							sinLev_Attack_Rating += (sinChar->iLevel / InvenItem[i].sItem.sSpecData.iSpecAttackRatingDiv) / 2;
						if (InvenItem[i].sItem.sSpecData.iSpecAttackPowerDiv)
							sinLev_Damage[1] += (sinChar->iLevel / InvenItem[i].sItem.sSpecData.iSpecAttackPowerDiv) / 2;
						if (InvenItem[i].sItem.sSpecData.fSpecMPRegen)
							sinPer_Mana_Regen += (InvenItem[i].sItem.sSpecData.fSpecMPRegen / 2.0f) * 0.5f;
						if (InvenItem[i].sItem.sSpecData.fSpecHPRegen)
							sinPer_Life_Regen += (InvenItem[i].sItem.sSpecData.fSpecHPRegen / 2.0f) * 0.5f;
						if (InvenItem[i].sItem.sSpecData.fSpecSPRegen)
							sinPer_Stamina_Regen += (InvenItem[i].sItem.sSpecData.fSpecSPRegen / 2.0f) * 0.5f;

						for (int t = 0; t < 8; t++)
						{
							sinAdd_Resistance[t] += (int)InvenItem[i].sItem.sSpecData.saSpecElementalDef[t] / 2;
							if (InvenItem[i].sItem.sSpecData.saSpecElementalAtkDiv[t])
								sinLev_Attack_Resistance[t] += (int)(InvenItem[i].sItem.sSpecData.saSpecElementalAtkDiv[t] + (sinChar->iLevel / InvenItem[i].sItem.sSpecData.saSpecElementalAtkDiv[t])) / 2;
						}
					}
					else
					{
						sinAdd_Defence += InvenItem[i].sItem.sSpecData.iSpecDefenseRating;
						sinAdd_fSpeed += InvenItem[i].sItem.sSpecData.fSpecMovementSpeed;
						sinAdd_fBlock_Rating += InvenItem[i].sItem.sSpecData.fSpecBlockRating;
						sinAdd_Attack_Speed += InvenItem[i].sItem.sSpecData.iSpecAttackSpeed;
						sinAdd_Critical_Hit += InvenItem[i].sItem.sSpecData.iSpecCritical;
						sinAdd_Shooting_Range += InvenItem[i].sItem.sSpecData.iSpecAttackRange;
						sinAdd_fMagic_Mastery += InvenItem[i].sItem.sSpecData.fSpecMagicMastery;

						if (InvenItem[i].sItem.sSpecData.iSpecAddMPDiv)
							sinLev_Mana += (sinChar->iLevel / InvenItem[i].sItem.sSpecData.iSpecAddMPDiv);
						if (InvenItem[i].sItem.sSpecData.iSpecAddHPDiv)
							sinLev_Life += (sinChar->iLevel / InvenItem[i].sItem.sSpecData.iSpecAddHPDiv);
						if (InvenItem[i].sItem.sSpecData.iSpecAttackRatingDiv)
							sinLev_Attack_Rating += (sinChar->iLevel / InvenItem[i].sItem.sSpecData.iSpecAttackRatingDiv);
						if (InvenItem[i].sItem.sSpecData.iSpecAttackPowerDiv)
							sinLev_Damage[1] += (sinChar->iLevel / InvenItem[i].sItem.sSpecData.iSpecAttackPowerDiv);
						if (InvenItem[i].sItem.sSpecData.fSpecMPRegen)
							sinPer_Mana_Regen += (InvenItem[i].sItem.sSpecData.fSpecMPRegen / 2.0f);
						if (InvenItem[i].sItem.sSpecData.fSpecHPRegen)
							sinPer_Life_Regen += (InvenItem[i].sItem.sSpecData.fSpecHPRegen / 2.0f);
						if (InvenItem[i].sItem.sSpecData.fSpecSPRegen)
							sinPer_Stamina_Regen += (InvenItem[i].sItem.sSpecData.fSpecSPRegen / 2.0f);

						for (t = 0; t < 8; t++)
						{
							sinAdd_Resistance[t] += (int)InvenItem[i].sItem.sSpecData.saSpecElementalDef[t];
							if (InvenItem[i].sItem.sSpecData.saSpecElementalAtkDiv[t])
								sinLev_Attack_Resistance[t] += (int)InvenItem[i].sItem.sSpecData.saSpecElementalAtkDiv[t] + (sinChar->iLevel / InvenItem[i].sItem.sSpecData.saSpecElementalAtkDiv[t]);
						}
					}
				}

				if ((InvenItem[i].sBaseItemID.ToInt() & sinITEM_MASK2) == sinWD1)
				{
					for (j = 0; j < 8; j++)
						sinResistance[j] += (int)InvenItem[i].sItem.saElementalDef[j] / 2;
				}
				else
				{
					for (j = 0; j < 8; j++)
						sinResistance[j] += (int)InvenItem[i].sItem.saElementalDef[j];
				}
			}
		}
	}

	float TempSkillData = 0;
	float TempDamage[2] = { 0,0 };
	int   TempAttack_Rating = 0;
	int   TempDefense = 0;
	int   TempDefense2 = 0;
	int   TempWeaponSpeed = 0;
	float TempCritical = 0;
	int	  MetalArmor = 0;

	if (sInven[0].ItemIndex)
	{
		TempDamage[0] += cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin;
		TempDamage[1] += cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax;

		TempWeaponSpeed += cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.iAttackSpeed;

		if (sinChar->iFlag == cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.eSpecialization)
			TempWeaponSpeed += cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sSpecData.iSpecAttackSpeed;

		TempCritical += (float)cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.iCritical;
	}

	if (sinChar->iClass == CHARACTERCLASS_Assassin)
	{
		if (sInven[1].ItemIndex)
		{
			TempDamage[0] += cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sItem.sDamage.sMin;
			TempDamage[1] += cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sItem.sDamage.sMax;

			TempWeaponSpeed += cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sItem.iAttackSpeed;

			if (sinChar->iFlag == cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sItem.eSpecialization)
				TempWeaponSpeed += cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sItem.sSpecData.iSpecAttackSpeed;

			TempCritical += (float)cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sItem.iCritical;
		}
	}
	else
	{
		if (sInven[1].ItemIndex)
		{
			TempDefense2 = cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sItem.iDefenseRating;
			if (sinChar->iFlag == cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sItem.eSpecialization)
				TempDefense2 += cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sItem.sSpecData.iSpecDefenseRating;
		}
	}

	if (sInven[2].ItemIndex)
	{
		TempDefense = cInvenTory.InvenItem[sInven[2].ItemIndex - 1].sItem.iDefenseRating;
		if (sinChar->iFlag == cInvenTory.InvenItem[sInven[2].ItemIndex - 1].sItem.eSpecialization)
		{
			TempDefense += cInvenTory.InvenItem[sInven[2].ItemIndex - 1].sItem.sSpecData.iSpecDefenseRating;
			MetalArmor = 1;
		}
	}

	int sinSkillTimeDamage[2] = { 0,0 };
	sinTempBlock = 0;
	sinTempAbsorb = 0;

	int Count2 = 0;
	int Point2 = 0;
	int p = 0;
	int Flag3 = 0;
	int Flag4 = 0;

	SkillTextColor[SIN2_ATTACK_RATE] = SIN_TEXT_COLOR_WHITE;
	SkillTextColor[SIN2_LIFE] = SIN_TEXT_COLOR_WHITE;
	SkillTextColor[SIN2_MANA] = SIN_TEXT_COLOR_WHITE;
	SkillTextColor[SIN2_STAMINA] = SIN_TEXT_COLOR_WHITE;
	SkillTextColor[SIN2_DEFENSE] = SIN_TEXT_COLOR_WHITE;
	SkillTextColor[SIN2_ABSORB] = SIN_TEXT_COLOR_WHITE;
	SkillTextColor[SIN2_SPEED] = SIN_TEXT_COLOR_WHITE;

	for (i = 0; i < SIN_MAX_SKILL_LIST; i++)
	{
		if (ContinueSkill[i].Flag)
		{
			switch (ContinueSkill[i].CODE)
			{
				//¼«¹â»¤¶Ü
			case SKILL_EXTREME_SHIELD:
				if (sinDS1 == (cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sBaseItemID.ToInt()&sinITEM_MASK2))
				{
					sinTempBlock += ContinueSkill[i].PlusState[0];
					SendProcessSKillToServer(SKILL_PLAY_EXTREME_SHIELD, ContinueSkill[i].Point, 0, 0);
				}
				else
					SendCancelSkillToServer(SKILL_PLAY_EXTREME_SHIELD, ContinueSkill[i].Point, 0, 0);
				break;
				//Áé¹â»¤Ìå
			case SKILL_PHYSICAL_ABSORB:
				sinTempAbsorb += ContinueSkill[i].PlusState[0];
				break;
				// ¸ÄÁ¼×¨¼Ò
			case SKILL_MAXIMIZE:
				SendProcessSKillToServer(SKILL_PLAY_MAXIMIZE, ContinueSkill[i].Point, 0, 0);
				sinTempDamage2[1] += (int)(((float)ContinueSkill[i].PlusState[0] / 100.0f)*TempDamage[1]);
				break;
				// Áé¹â·ÉÑï
			case SKILL_AUTOMATION:
				if (sinWS1 == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt()&sinITEM_MASK2) || sinWT1 == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt()&sinITEM_MASK2))
				{
					sinTempDamage2[0] += (int)(((float)Automation_Damage[ContinueSkill[i].Point - 1] / 100)*TempDamage[0]);
					sinTempDamage2[1] += (int)(((float)Automation_Damage[ContinueSkill[i].Point - 1] / 100)*TempDamage[1]);
					sinSkillWeaponSpeed += ContinueSkill[i].PlusState[0];
					SendProcessSKillToServer(SKILL_PLAY_AUTOMATION, ContinueSkill[i].Point, 0, 0);
				}
				else
					SendCancelSkillToServer(SKILL_PLAY_AUTOMATION, ContinueSkill[i].Point, 0, 0);
				break;
				// ½ðÊôÖØ¼×
			case SKILL_METAL_ARMOR:
				if (MetalArmor)
				{
					sinDefense += (Metal_Armor_Defense[ContinueSkill[i].Point - 1] * (TempDefense)) / 100;
					SkillTextColor[SIN2_DEFENSE] = SIN_TEXT_COLOR_BLUE;
					Point2 = cSkill.GetSkillPoint(SKILL_PHYSICAL_ABSORB);
					if (Point2)
						sinTempAbsorb += (int)((float(P_Absorb[Point2 - 1])*2.0f) / 2);
				}
				break;
				//·ÀÓùµç²¨
			case SKILL_SPARK_SHIELD:
				if (sInven[1].ItemIndex)
				{
					if (sinDS1 == (cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sBaseItemID.ToInt() & sinITEM_MASK2))
						sinDefense += Spark_Shield_Defense[ContinueSkill[i].Point - 1];
				}
				break;
				// Íþ åÅ­ºð
			case SKILL_COMPULSION:
				sinTempAbsorb += Compulsion_AddAbsorb[ContinueSkill[i].Point - 1];
				SkillTextColor[SIN2_ABSORB] = SIN_TEXT_COLOR_BLUE;
				break;
				// ´ÅÐÔÇòÌå
			case SKILL_MAGNETIC_SPHERE:
				break;
				// Õ½ ñ×£¸?
			case SKILL_P_ENHENCE:
				sinTempDamage2[0] += P_Enhence_AddDamage[ContinueSkill[i].Point - 1][0] * (int)(TempDamage[0]) / 100;
				sinTempDamage2[1] += P_Enhence_AddDamage[ContinueSkill[i].Point - 1][1] * (int)(TempDamage[1]) / 100;
				sinDefense += P_Enhence_Defanse[ContinueSkill[i].Point - 1];
				break;
				//´Ì ±Ö®¸«
			case SKILL_SWIFT_AXE:
				if (sInven[0].ItemIndex)
				{
					if (ContinueSkill[i].Skill_Info.UseWeaponCode[0] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt()&sinITEM_MASK2))
					{
						sinSkillWeaponSpeed += (int)((Swift_Axe_Speed[ContinueSkill[i].Point - 1] * TempWeaponSpeed) / 100);
						Flag4 = 1;
					}
				}
				break;
				//·è¿ñÅ­ºð
			case SKILL_BERSERKER:
				sinTempDamage2[0] += Berserker_AddAttack[ContinueSkill[i].Point - 1];
				sinTempDamage2[1] += Berserker_AddAttack[ContinueSkill[i].Point - 1];
				sinTempAbsorb += Berserker_SubAbsorb[ContinueSkill[i].Point - 1];
				SkillTextColor[SIN2_ABSORB] = SIN_TEXT_COLOR_RED;
				break;
				//°µ ±Ö®ÑÛ
			case SKILL_ASSASSIN_EYE:
				break;
				// Ç±ÄÜ¼¤·¢
			case SKILL_AMPLIFIED:
				sinTempDamage2[0] += Amplified_MinAddDamage[ContinueSkill[i].Point - 1] * (int)(TempDamage[0]) / 100;
				sinTempAbsorb += Amplified_SubAbs[ContinueSkill[i].Point - 1];
				sinAttack_Rating += Amplified_AddHit[ContinueSkill[i].Point - 1] * sinAttack_Rating / 100;
				break;
				// »Æ½ðÁÔÓ¥
			case SKILL_GOLDEN_FALCON:
				sinfRegenLife += Golden_Falcon_LifeRegen[ContinueSkill[i].Point - 1];
				break;
				//×ÔÈ»Ö®¹â
			case SKILL_FORCE_OF_NATURE:
				sinTempDamage2[0] += Force_Of_Nature_AddDamage[ContinueSkill[i].Point - 1] / ContinueSkill[i].Flag;
				sinTempDamage2[1] += Force_Of_Nature_AddDamage[ContinueSkill[i].Point - 1] / ContinueSkill[i].Flag;
				sinAttack_Rating += Force_Of_Nature_AddHit[ContinueSkill[i].Point - 1] / ContinueSkill[i].Flag;
				SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_GOLD;
				SkillTextColor[SIN2_ATTACK_RATE] = SIN_TEXT_COLOR_ORANGE;
				break;
				// ñÁ¦ÖØ»?
			case SKILL_HOLY_VALOR:
				sinDefense += 300;
				break;
				// Ê¥ÁéÖ®Îü
			case SKILL_DIVINE_INHALATION:
				if (sinDS1 == (cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sBaseItemID.ToInt()&sinITEM_MASK2))
				{
					sinTempBlock += D_Inhalation_Block[ContinueSkill[i].Point - 1];
					SendProcessSKillToServer(SKILL_PLAY_DIVINE_INHALATION, ContinueSkill[i].Point, 0, 0);
				}
				else
					SendCancelSkillToServer(SKILL_PLAY_DIVINE_INHALATION, ContinueSkill[i].Point, 0, 0);
				break;
				// ¾´ ñÖ®¶Ü
			case SKILL_GODLY_SHIELD:
				if (sinDS1 == (cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sBaseItemID.ToInt()&sinITEM_MASK2))
					SendProcessSKillToServer(SKILL_PLAY_GODLY_SHIELD, ContinueSkill[i].Point, 0, 0);
				else
					SendCancelSkillToServer(SKILL_PLAY_GODLY_SHIELD, ContinueSkill[i].Point, 0, 0);
				break;
				//  ÏµÛ×£¸?
			case SKILL_GOD_BLESS:
				sinTempDamage2[0] += God_Bless_AddDamage[ContinueSkill[i].Point - 1];
				sinTempDamage2[1] += God_Bless_AddDamage[ContinueSkill[i].Point - 1];
				SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_GOLD;
				break;
				// ×·Ãü¾¢·ç
			case SKILL_WINDY:
				if (sinWT1 == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt()&sinITEM_MASK2))
				{
					sinAttack_Rating += (Windy_Attack_Rating[ContinueSkill[i].Point - 1] * TempAttack_Rating) / 100;
					sinShooting_Range += 30;
					SkillTextColor[SIN2_ATTACK_RATE] = SIN_TEXT_COLOR_ORANGE;
				}
				else
				{
					ContinueSkill[i].CheckTime = ContinueSkill[i].UseTime * 70;
					SkillTextColor[SIN2_ATTACK_RATE] = SIN_TEXT_COLOR_WHITE;
					lpCurPlayer->ClearSkillToPlay(SKILL_WINDY);
				}
				break;
				// Õ½ÀõÅØÏø
			case SKILL_TRIUMPH_OF_VALHALLA:
				sinTempDamage2[1] += (T_Of_Valhalla_Damage[ContinueSkill[i].Point - 1] + (SetT_Of_ValhallaLV / 1)) / (SetT_Of_ValhallaFlag + 1);
				SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_GOLD;
				break;
				// Íß¶û¹þÀ­Ö®¹â
			case SKILL_HALL_OF_VALHALLA:
				if (SetT_Of_ValhallaPOINT)
				{
					sinTempDamage2[1] += (T_Of_Valhalla_Damage[SetT_Of_ValhallaPOINT - 1] + (SetH_Of_ValhallaLV / 1)) / ContinueSkill[i].Flag;
					SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_GOLD;
				}
				break;
				// Ëª¶³±êÇ¹
			case SKILL_FROST_JAVELIN:
				if (sinWT1 == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt()&sinITEM_MASK2))
				{
					sinTempDamage2[0] += Frost_Javelin_IceAddDamage[ContinueSkill[i].Point - 1][0];
					sinTempDamage2[1] += Frost_Javelin_IceAddDamage[ContinueSkill[i].Point - 1][1];
				}
				else
				{
					ContinueSkill[i].CheckTime = ContinueSkill[i].UseTime * 70;
					SkillTextColor[SIN2_ATTACK_RATE] = SIN_TEXT_COLOR_WHITE;
					lpCurPlayer->ClearSkillToPlay(SKILL_FROST_JAVELIN);
					SendCancelSkillToServer(SKILL_PLAY_FROST_JAVELIN, 0, 0, 0);
				}
				break;
				// ÇáÎè·ÉÑï
			case SKILL_TALARIA:
				sinMoveSpeed += Talaria_MoveSpeed[ContinueSkill[i].Point - 1];
				break;
				//  úÃüÖ®¹â
			case SKILL_VIRTUAL_LIFE:
				SkillTextColor[SIN2_LIFE] = SIN_TEXT_COLOR_PINK;
				break;
				//ÌìÅ® ¢»?
			case SKILL_B_KRISHNA:
				sinTempAbsorb += B_Krishna_Abs[ContinueSkill[i].Point - 1];
				break;
				// Áé»êÕÙ»½
			case SKILL_SPIRIT_ELEMENTAL:
				sinfRegenMana += Spirit_Elemental_RegenMana[ContinueSkill[i].Point - 1];
				break;
				//Âõ¿Ë¶û
			case SKILL_ADVENT_MIGAL:
				sinTempDamage2[0] += Advent_Migal_Atk[ContinueSkill[i].Point - 1];
				sinTempDamage2[1] += Advent_Migal_Atk[ContinueSkill[i].Point - 1];
				SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_GOLD;
				break;
				// ÆíÓêÊ¦
			case SKILL_RAIN_MAKER:
				sinTempAbsorb += (Rainmaker_Abs[ContinueSkill[i].Point - 1] * sinTempAbsorb) / 100;
				sinAttack_Rating += (Rainmaker_AtkRating[ContinueSkill[i].Point - 1] * TempAttack_Rating) / 100;
				SkillTextColor[SIN2_ATTACK_RATE] = SIN_TEXT_COLOR_ORANGE;
				break;
				//Ã×µÂÀ¼´ï
			case SKILL_ADVENT_MIDRANDA:
				if (sInven[0].ItemIndex)
				{
					if (ContinueSkill[i].Skill_Info.UseWeaponCode[0] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt()&sinITEM_MASK2))
					{
						sinSkillWeaponSpeed += (int)((Advent_Midranda_Speed[ContinueSkill[i].Point - 1] * TempWeaponSpeed) / 100);
						Flag4 = 1;
					}
				}
				break;
			case CLANSKILL_ABSORB:
				sinTempAbsorb += 20;
				SkillTextColor[SIN2_ABSORB] = SIN_TEXT_COLOR_BLUE;
				break;
			case SCROLL_INVULNERABILITY:
			case SCROLL_P_INVULNERABILITY:
				sinTempDamage2[0] -= (sinChar->iMinDamage) / 2;
				sinTempDamage2[1] -= (sinChar->iMaxDamage) / 2;
				SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_RED;
				break;
			case BOOSTER_ITEM_LIFE:
				SkillTextColor[SIN2_LIFE] = SIN_TEXT_COLOR_PINK;

				if (AddBoosterLife)
				{
					if (!LifeFlag)
					{
						tempLife[0] = ((sinChar->sHP.sMax + AddVirtualLife[0]) * (short)BoosterItem_DataPercent[0]) / 100;
						LifeFlag = 1;
					}
					else if (sinChar->iLevel != tempLife[1])
					{
						tempLife[0] = ((sinChar->sHP.sMax + AddVirtualLife[0] - tempLife[0]) * (short)BoosterItem_DataPercent[0]) / 100;
						tempLife[1] = sinChar->iLevel;
					}
					else if (!AddVirtualLife[1] && LifeFlag == 1)
					{
						sinChar->sHP.sMax -= tempLife[0];
						tempLife[0] = (sinChar->sHP.sMax * (short)BoosterItem_DataPercent[0]) / 100;
					}

					sinfIncreLife = sinfIncreLife + tempLife[0];
				}
				else
					tempLife[0] = 0;
				break;
			case BOOSTER_ITEM_MANA:
				SkillTextColor[SIN2_MANA] = SIN_TEXT_COLOR_PINK;

				if (AddVirtualMana[1])
				{
					if (!ManaFlag)
					{
						tempMana[0] = (sinChar->sMP.sMax * (short)BoosterItem_DataPercent[0]) / 100;
						ManaFlag = 1;
					}
					else if (sinChar->iLevel != tempMana[1])
					{
						tempMana[0] = ((sinChar->sMP.sMax - tempMana[0]) * (short)BoosterItem_DataPercent[0]) / 100;
						tempMana[1] = sinChar->iLevel;
					}

					sinfIncreMana = sinfIncreMana + tempMana[0];
				}
				else
					tempMana[0] = 0;
				break;
			case BOOSTER_ITEM_STAMINA:
				SkillTextColor[SIN2_STAMINA] = SIN_TEXT_COLOR_PINK;

				if (AddVirtualStamina[1])
				{
					if (!StaminaFlag)
					{
						tempStamina[0] = (sinChar->sSP.sMax * (short)BoosterItem_DataPercent[0]) / 100;
						StaminaFlag = 1;
					}
					else if (sinChar->iLevel != tempStamina[1])
					{
						tempStamina[0] = ((sinChar->sSP.sMax - tempStamina[0]) * (short)BoosterItem_DataPercent[0]) / 100;
						tempStamina[1] = sinChar->iLevel;
					}
					sinfIncreStamina = sinfIncreStamina + tempStamina[0];
				}
				else
					tempStamina[0] = 0;
				break;
			}
		}
	}

	for (i = 1; i < MAX_USESKILL; i++)
	{
		if (sinSkill.UseSkill[i].Flag && sinSkill.UseSkill[i].Point)
		{
			switch (sinSkill.UseSkill[i].CODE)
			{
			case SKILL_POISON_ATTRIBUTE:
				sinSkillResistance[sITEMINFO_POISON] = PlusPoison[sinSkill.UseSkill[i].Point - 1];
				break;
			case SKILL_ICE_ATTRIBUTE:
				sinSkillResistance[sITEMINFO_ICE] = PlusIce[sinSkill.UseSkill[i].Point - 1];
				break;
			case SKILL_FIRE_ATTRIBUTE:
				sinSkillResistance[sITEMINFO_FIRE] = PlusFire[sinSkill.UseSkill[i].Point - 1];
				break;
			}
		}
	}

	int TempDivide = 1;
	for (i = 0; i < SIN_MAX_SKILL_LIST; i++)
	{
		if (ContinueSkill[i].Flag)
		{
			switch (ContinueSkill[i].CODE)
			{
			case SKILL_ZENITH:
				if (ContinueSkill[i].PartyFlag)
					TempDivide = 2;
				sinSkillResistance[sITEMINFO_BIONIC] += Zenith_Element[ContinueSkill[i].Point - 1] / TempDivide;
				sinSkillResistance[sITEMINFO_FIRE] += Zenith_Element[ContinueSkill[i].Point - 1] / TempDivide;
				sinSkillResistance[sITEMINFO_ICE] += Zenith_Element[ContinueSkill[i].Point - 1] / TempDivide;
				sinSkillResistance[sITEMINFO_LIGHTING] += Zenith_Element[ContinueSkill[i].Point - 1] / TempDivide;
				sinSkillResistance[sITEMINFO_POISON] += Zenith_Element[ContinueSkill[i].Point - 1] / TempDivide;
				break;
			}
		}
	}
	for (i = 0; i < 8; i++)
		sinChar->sElementalDef[i] = sinResistance[i] + sinAdd_Resistance[i] + sinSkillResistance[i];

	for (i = 1; i < MAX_USESKILL; i++)
	{
		if (sinSkill.UseSkill[i].Flag && sinSkill.UseSkill[i].Point)
		{
			for (cnt = 0; cnt < 10; cnt++)
			{
				switch (sinSkill.UseSkill[i].CODE)
				{
				case SKILL_MELEE_MASTERY:
					if (sInven[0].ItemIndex)
					{
						if (sinSkill.UseSkill[i].Skill_Info.UseWeaponCode[cnt] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt() & sinITEM_MASK2))
						{
							sinSkillDamage[0] = (int)(((float)Melee_Mastery_DamagePercent[sinSkill.UseSkill[i].Point - 1] / 100)*TempDamage[0]);
							sinSkillDamage[1] = (int)(((float)Melee_Mastery_DamagePercent[sinSkill.UseSkill[i].Point - 1] / 100)*TempDamage[1]);
						}
					}
					break;
				case SKILL_SHOOTING_MASTERY:
					if (sInven[0].ItemIndex)
					{
						if (sinSkill.UseSkill[i].Skill_Info.UseWeaponCode[cnt] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt()&sinITEM_MASK2))
						{
							sinSkillDamage[0] = (int)(((float)S_Mastery_DamagePercent[sinSkill.UseSkill[i].Point - 1] / 100)*TempDamage[0]);
							sinSkillDamage[1] = (int)(((float)S_Mastery_DamagePercent[sinSkill.UseSkill[i].Point - 1] / 100)*TempDamage[1]);
						}
					}
					break;
				case SKILL_WEAPONE_DEFENCE_MASTERY:
					if (sInven[0].ItemIndex)
					{
						if (sinSkill.UseSkill[i].Skill_Info.UseWeaponCode[cnt] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt()&sinITEM_MASK2))
						{
							if (sInven[1].ItemIndex)
							{
								if (sinDS1 == (cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sBaseItemID.ToInt()&sinITEM_MASK2))
									break;
							}
							sinBlock_Rate += W_D_Mastery_Block[sinSkill.UseSkill[i].Point - 1];
						}
					}
					break;
				case SKILL_DIONS_EYE:
					if (sInven[0].ItemIndex)
					{
						if (sinSkill.UseSkill[i].Skill_Info.UseWeaponCode[cnt] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt()&sinITEM_MASK2))
							sinAttack_Rating += (D_Eye_Attack_Rate[sinSkill.UseSkill[i].Point - 1] * sinAttack_Rating) / 100;
					}
					break;
				case SKILL_THROWING_MASTERY:
					if (sInven[0].ItemIndex)
					{
						if (sinSkill.UseSkill[i].Skill_Info.UseWeaponCode[cnt] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt()&sinITEM_MASK2))
						{
							sinSkillDamage[0] = (int)(((float)T_Mastery_Damage[sinSkill.UseSkill[i].Point - 1] / 100)*TempDamage[0]);
							sinSkillDamage[1] = (int)(((float)T_Mastery_Damage[sinSkill.UseSkill[i].Point - 1] / 100)*TempDamage[1]);
						}
					}
					break;
				case SKILL_MECHANIC_WEAPON:
					if (sInven[0].ItemIndex)
					{
						if (sinChar->iFlag == InvenItem[sInven[0].ItemIndex - 1].sItem.eSpecialization)
						{
							sinSkillDamage[0] = (int)(((float)M_Weapon_Mastey[sinSkill.UseSkill[i].Point - 1] / 100)*TempDamage[0]);
							sinSkillDamage[1] = (int)(((float)M_Weapon_Mastey[sinSkill.UseSkill[i].Point - 1] / 100)*TempDamage[1]);
						}
						if (InvenItem[sInven[0].ItemIndex - 1].sItem.iItemUniqueID == 2)
						{
							sinSkillDamage[0] = (int)(((float)M_Weapon_Mastey[sinSkill.UseSkill[i].Point - 1] / 100)*TempDamage[0]);
							sinSkillDamage[1] = (int)(((float)M_Weapon_Mastey[sinSkill.UseSkill[i].Point - 1] / 100)*TempDamage[1]);
						}
					}
					break;
				case SKILL_CRITICAL_MASTERY:
					if (sInven[0].ItemIndex)
					{
						if (sinSkill.UseSkill[i].Skill_Info.UseWeaponCode[cnt] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt()&sinITEM_MASK2))
							sinCritical += Critical_Mastery_Critical[sinSkill.UseSkill[i].Point - 1];
					}
					break;
				case SKILL_SWORD_MASTERY:
					if (sInven[0].ItemIndex)
					{
						if (sinSkill.UseSkill[i].Skill_Info.UseWeaponCode[cnt] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt()&sinITEM_MASK2))
						{
							sinSkillDamage[0] = (int)(((float)Sword_Mastery_DamagePercent[sinSkill.UseSkill[i].Point - 1] / 100)*TempDamage[0]);
							sinSkillDamage[1] = (int)(((float)Sword_Mastery_DamagePercent[sinSkill.UseSkill[i].Point - 1] / 100)*TempDamage[1]);
						}
					}
					break;
				case SKILL_SWORDMASTERY:
					if (sInven[0].ItemIndex || sInven[1].ItemIndex)
					{
						if (sinSkill.UseSkill[i].Skill_Info.UseWeaponCode[cnt] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt()&sinITEM_MASK2) ||
							sinSkill.UseSkill[i].Skill_Info.UseWeaponCode[cnt] == (cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sBaseItemID.ToInt()&sinITEM_MASK2))
						{
							sinSkillDamage[0] = (int)(((float)Sword_Mastery_Damage[sinSkill.UseSkill[i].Point - 1] / 100)*TempDamage[0]);
							sinSkillDamage[1] = (int)(((float)Sword_Mastery_Damage[sinSkill.UseSkill[i].Point - 1] / 100)*TempDamage[1]);
						}
					}
					break;
					//¹¥»÷´óÊ¦
				case SKILL_ATTACK_MASTERY:
					if (sInven[0].ItemIndex || sInven[1].ItemIndex)
					{
						if (sinSkill.UseSkill[i].Skill_Info.UseWeaponCode[cnt] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt()&sinITEM_MASK2) ||
							sinSkill.UseSkill[i].Skill_Info.UseWeaponCode[cnt] == (cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sBaseItemID.ToInt()&sinITEM_MASK2))
						{
							sinSkillDamage[0] = (int)(((float)Blade_Mastery_Attack[sinSkill.UseSkill[i].Point - 1] / 100)*TempDamage[0]);
							sinSkillDamage[1] = (int)(((float)Blade_Mastery_Attack[sinSkill.UseSkill[i].Point - 1] / 100)*TempDamage[1]);
						}
					}
					break;
					//ÖÂÃü´óÊ¦
				case SKILL_FATAL_MASTERY:
					if (sInven[0].ItemIndex || sInven[1].ItemIndex)
					{
						if (sinSkill.UseSkill[i].Skill_Info.UseWeaponCode[cnt] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt()&sinITEM_MASK2) ||
							sinSkill.UseSkill[i].Skill_Info.UseWeaponCode[cnt] == (cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sBaseItemID.ToInt()&sinITEM_MASK2))
							sinCritical += Fatal_Mastery_Critical[sinSkill.UseSkill[i].Point - 1];
					}
					break;
				}
			}
		}
	}

	switch (sinChar->iClass)
	{
	case CHARACTERCLASS_Fighter:
		if (sinWA1 == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt()&sinITEM_MASK2))
			sinCharItemDamage += sinChar->iLevel / 6;
		break;
	case CHARACTERCLASS_Mechanician:
		if (sInven[0].ItemIndex)
		{
			if (sinChar->iFlag == InvenItem[sInven[0].ItemIndex - 1].sItem.eSpecialization)
				sinCharItemDamage += sinChar->iLevel / 6;
			else if (InvenItem[sInven[0].ItemIndex - 1].sItem.iItemUniqueID == 2)
				sinCharItemDamage += sinChar->iLevel / 6;
		}
		break;
	case CHARACTERCLASS_Archer:
		if (sinWS1 == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt()&sinITEM_MASK2))
			sinCharItemDamage += sinChar->iLevel / 6;
		break;
	case CHARACTERCLASS_Pikeman:
		if (sinWP1 == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt()&sinITEM_MASK2))
			sinCharItemDamage += sinChar->iLevel / 6;
		break;
	case CHARACTERCLASS_Knight:
		if (sinWS2 == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt()&sinITEM_MASK2))
			sinCharItemDamage += sinChar->iLevel / 6;
		break;
	case CHARACTERCLASS_Atalanta:
		if (sinWT1 == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt()&sinITEM_MASK2))
			sinCharItemDamage += sinChar->iLevel / 6;
		break;
	case CHARACTERCLASS_Priestess:
		if (sinWM1 == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt()&sinITEM_MASK2))
			sinCharItemDamage += sinChar->iLevel / 6;
		break;
	case CHARACTERCLASS_Magician:
		if (sinWM1 == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt()&sinITEM_MASK2))
			sinCharItemDamage += sinChar->iLevel / 6;
		break;
	case CHARACTERCLASS_Assassin:
		if (sinWD1 == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt() & sinITEM_MASK2))
			sinCharItemDamage += sinChar->iLevel / 6;
		else if (sinWD1 == (cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sBaseItemID.ToInt() & sinITEM_MASK2))
			sinCharItemDamage += sinChar->iLevel / 6;
		break;
	case CHARACTERCLASS_Shaman:
		if (sinWN1 == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt() & sinITEM_MASK2))
			sinCharItemDamage += sinChar->iLevel / 6;
		break;
	}
	int TempChangeDamageFlag = 0;
	int TempChangeAbsorbFlag = 0;

	for (i = 0; i < SIN_MAX_SKILL_LIST; i++)
	{
		if (ContinueSkill[i].Flag)
		{
			for (cnt = 0; cnt < 10; cnt++)
			{
				switch (ContinueSkill[i].CODE)
				{
				case SKILL_AUTOMATION:
				case SKILL_MAXIMIZE:
					if (ContinueSkill[i].Skill_Info.UseWeaponCode[cnt] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt()&sinITEM_MASK2))
						TempChangeDamageFlag = 1;
					break;
				case SKILL_METAL_ARMOR:
					if (MetalArmor)
						TempChangeAbsorbFlag = 1;
					break;
				case SKILL_PHYSICAL_ABSORB:
					TempChangeAbsorbFlag = 1;
					break;
				case SKILL_FORCE_ORB:
					TempChangeDamageFlag = 1;
					break;
				case SKILL_COMPULSION:
					TempChangeAbsorbFlag = 1;
					break;
				case CLANSKILL_ABSORB:
					TempChangeAbsorbFlag = 1;
					break;
				case CLANSKILL_ATTACK:
					TempChangeDamageFlag = 1;
					break;
				case SCROLL_INVULNERABILITY:
					TempChangeDamageFlag = 1;
					break;
				case SKILL_RAIN_MAKER:
					TempChangeAbsorbFlag = 1;
					break;
				}
			}
		}
	}

	if (sinCharItemDamage)
		SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_GOLD;
	else if (TempChangeDamageFlag)
		SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_GOLD;
	else
		SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_WHITE;

	if (TempChangeAbsorbFlag)
		SkillTextColor[SIN2_ABSORB] = SIN_TEXT_COLOR_BLUE;
	else
		SkillTextColor[SIN2_ABSORB] = SIN_TEXT_COLOR_WHITE;

	sinChar->iPotionStorage = sinPotion_Space;

	fstrength = (float)sinChar->iStrength;
	fhealth = (float)sinChar->iHealth;
	ftalent = (float)sinChar->iTalent;
	fSpirit = (float)sinChar->iSpirit;
	fDexterity = (float)sinChar->iAgility;
	fLevel = (float)sinChar->iLevel;

	sinChar->iAttackRating = (int)(sinAttack_Rating + fDexterity * 3.1f + fLevel * 1.9f + ftalent * 1.5f + sinLev_Attack_Rating);

	if (sinDamageFunction[0] == 1 && !sInven[0].ItemIndex) // ÎäÊ¿ ¿ÕÊÖ
	{
		sinChar->iMinDamage = 2 + ((sinChar->iStrength + 130) / 130) + ((sinChar->iTalent + sinChar->iAgility) / 40) + sinLev_Damage[0];
		sinChar->iMaxDamage = 4 + ((sinChar->iStrength + 130) / 130) + ((sinChar->iTalent + sinChar->iAgility) / 35) + sinLev_Damage[1];
	}
	if ((sinDamageFunction[0] == 2 || sinDamageFunction[0] == 3 || sinDamageFunction[0] == 4) && !sInven[0].ItemIndex)
	{
		sinChar->iMinDamage = 2 + ((sinChar->iStrength + 200) / 200) + ((sinChar->iTalent + sinChar->iAgility) / 50) + sinLev_Damage[0];
		sinChar->iMaxDamage = 4 + ((sinChar->iStrength + 200) / 200) + ((sinChar->iTalent + sinChar->iAgility) / 45) + sinLev_Damage[1];
	}
	if (sinChar->iClass == CHARACTERCLASS_Assassin)
	{
		if ((sinDamageFunction[0] == 1 && (InvenItem[sInven[0].ItemIndex - 1].iItemWpnDmg == 1 || InvenItem[sInven[0].ItemIndex - 1].iItemWpnDmg == 3)) ||
			(sinDamageFunction[0] == 1 && (InvenItem[sInven[1].ItemIndex - 1].iItemWpnDmg == 1 || InvenItem[sInven[1].ItemIndex - 1].iItemWpnDmg == 3)))
		{
			sinChar->iMinDamage = 2 + (sinAttack_Damage[0] * (sinChar->iStrength + 130) / 130) + ((sinChar->iTalent + sinChar->iAgility) / 40) + sinLev_Damage[0] + sinSkillDamage[0] + sinCharItemDamage;
			sinChar->iMaxDamage = 5 + (sinAttack_Damage[1] * (sinChar->iStrength + 130) / 130) + ((sinChar->iTalent + sinChar->iAgility) / 35) + sinLev_Damage[1] + sinSkillDamage[1] + sinCharItemDamage;
		}
	}
	else
	{
		if ((sinDamageFunction[0] == 1 && (InvenItem[sInven[0].ItemIndex - 1].iItemWpnDmg == 1 ||
			InvenItem[sInven[0].ItemIndex - 1].iItemWpnDmg == 3)))
		{
			sinChar->iMinDamage = 2 + (sinAttack_Damage[0] * (sinChar->iStrength + 130) / 130) + ((sinChar->iTalent + sinChar->iAgility) / 40) + sinLev_Damage[0] + sinSkillDamage[0] + sinCharItemDamage;
			sinChar->iMaxDamage = 5 + (sinAttack_Damage[1] * (sinChar->iStrength + 130) / 130) + ((sinChar->iTalent + sinChar->iAgility) / 35) + sinLev_Damage[1] + sinSkillDamage[1] + sinCharItemDamage;
		}
	}

	if ((sinDamageFunction[0] == 2 && (InvenItem[sInven[0].ItemIndex - 1].iItemWpnDmg == 1 ||
		InvenItem[sInven[0].ItemIndex - 1].iItemWpnDmg == 3)))
	{
		sinChar->iMinDamage = 2 + (sinAttack_Damage[0] * (sinChar->iStrength + 150) / 150) + ((sinChar->iTalent + sinChar->iAgility) / 45) + sinLev_Damage[0] + sinSkillDamage[0] + sinCharItemDamage;
		sinChar->iMaxDamage = 5 + (sinAttack_Damage[1] * (sinChar->iStrength + 150) / 150) + ((sinChar->iTalent + sinChar->iAgility) / 45) + sinLev_Damage[1] + sinSkillDamage[1] + sinCharItemDamage;
	}
	if ((sinDamageFunction[0] == 3 && (InvenItem[sInven[0].ItemIndex - 1].iItemWpnDmg == 1 || InvenItem[sInven[0].ItemIndex - 1].iItemWpnDmg == 3)))
	{
		sinChar->iMinDamage = 2 + (sinAttack_Damage[0] * (sinChar->iStrength + 145) / 145) + ((sinChar->iTalent + sinChar->iAgility) / 50) + sinLev_Damage[0] + sinSkillDamage[0] + sinCharItemDamage;
		sinChar->iMaxDamage = 5 + (sinAttack_Damage[1] * (sinChar->iStrength + 145) / 145) + ((sinChar->iTalent + sinChar->iAgility) / 45) + sinLev_Damage[1] + sinSkillDamage[1] + sinCharItemDamage;
	}

	if (sinDamageFunction[1] == 1 && InvenItem[sInven[0].ItemIndex - 1].iItemWpnDmg == 2)
	{
		sinChar->iMinDamage = 2 + (sinAttack_Damage[0] * (sinChar->iAgility + 130) / 130) + ((sinChar->iTalent + sinChar->iStrength) / 40) + sinLev_Damage[0] + sinSkillDamage[0] + sinCharItemDamage;
		sinChar->iMaxDamage = 5 + (sinAttack_Damage[1] * (sinChar->iAgility + 130) / 130) + ((sinChar->iTalent + sinChar->iStrength) / 40) + sinLev_Damage[1] + sinSkillDamage[1] + sinCharItemDamage;
	}
	if (sinDamageFunction[1] == 2 && InvenItem[sInven[0].ItemIndex - 1].iItemWpnDmg == 2)
	{
		sinChar->iMinDamage = 2 + (sinAttack_Damage[0] * (sinChar->iAgility + 190) / 190) + ((sinChar->iTalent + sinChar->iStrength) / 50) + sinLev_Damage[0] + sinSkillDamage[0] + sinCharItemDamage;
		sinChar->iMaxDamage = 5 + (sinAttack_Damage[1] * (sinChar->iAgility + 190) / 190) + ((sinChar->iTalent + sinChar->iStrength) / 50) + sinLev_Damage[1] + sinSkillDamage[1] + sinCharItemDamage;
	}

	if (sinDamageFunction[2] == 1 && InvenItem[sInven[0].ItemIndex - 1].iItemWpnDmg == 3)
	{
		sinChar->iMinDamage = 2 + (sinAttack_Damage[0] * (sinChar->iSpirit + 150) / 150) + ((sinChar->iTalent) / 30) + sinLev_Damage[0] + sinSkillDamage[0] + sinCharItemDamage;
		sinChar->iMaxDamage = 5 + (sinAttack_Damage[1] * (sinChar->iSpirit + 150) / 150) + ((sinChar->iTalent) / 30) + sinLev_Damage[1] + sinSkillDamage[1] + sinCharItemDamage;
	}
	if (sinDamageFunction[2] == 2 && InvenItem[sInven[0].ItemIndex - 1].iItemWpnDmg == 3)
	{
		sinChar->iMinDamage = 2 + (sinAttack_Damage[0] * (sinChar->iSpirit + 170) / 170) + ((sinChar->iTalent) / 30) + sinLev_Damage[0] + sinSkillDamage[0] + sinCharItemDamage;
		sinChar->iMaxDamage = 5 + (sinAttack_Damage[1] * (sinChar->iSpirit + 170) / 170) + ((sinChar->iTalent) / 30) + sinLev_Damage[1] + sinSkillDamage[1] + sinCharItemDamage;
	}

	sinChar->iCritical = sinCritical + sinAdd_Critical_Hit;

	fstrength = (float)sinChar->iStrength;
	fhealth = (float)sinChar->iHealth;
	ftalent = (float)sinChar->iTalent;
	fSpirit = (float)sinChar->iSpirit;

	sinChar->iDefenseRating = (int)((fDexterity / 1.0f) + (ftalent / 4.0f) + fLevel * 1.5f + sinDefense) + sinAdd_Defence;
	fDefense = (float)sinChar->iDefenseRating;

	CountAbsorbItem /= 2;
	if (CountAbsorbItem > 2)
		CountAbsorbItem = 2;

	sinChar->iAbsorbRating = (int)(fDefense / 100.0f + fstrength / 40.0f + fSpirit / 40.0f + ftalent / 40.0f + fLevel / 10.0f + 1.0f + CountAbsorbItem);
	sinChar->iAbsorbRating += (int)(sinAbsorption + sinAdd_fAbsorb);

	sinChar->iAttackRange = sinShooting_Range + sinAdd_Shooting_Range;

	sinChar->iSight = sinSight + 180;

	sinChar->iCritical = (int)(sinBlock_Rate + sinAdd_fBlock_Rating);

	sinChar->sWeight.sMax = (short)(fstrength * 2.0f + fhealth * 1.5f + fLevel * 3.0f + fSpirit + fDexterity + 60.0f);

	if (chaPremiumitem.m_MightofAwellTime > 0)
		sinChar->sWeight.sMax += (short)(chaPremiumitem.m_MightofAwellWeight);

	fMaxWeight = (float)sinChar->sWeight.sMax;
	fNowWeight = (float)sinChar->sWeight.sMin;

	fAttack_Rating = (float)sinChar->iAttackRating;

	int Accuracy_Temp;

	while (Accuracy_Table[cnt][0] != 0)
	{
		Accuracy_Temp = sinChar->iAttackRating;
		if (Accuracy_Temp > Accuracy_Table[cnt][0] && Accuracy_Temp < Accuracy_Table[cnt + 1][0])
		{
			sinChar->iAccuracy = Accuracy_Table[cnt + 1][1];
			break;
		}
		cnt++;
	}

	sinChar->iMovementSpeed = (int)(1.4f + fhealth / 150.0f + ftalent / 150.0f + fLevel / 150.0f - (fNowWeight / fMaxWeight) + sinMoveSpeed + sinAdd_fSpeed);
	sinChar->iMovementSpeed += 1;

	switch (sinChar->iHPType)
	{
	case 1://ÎäÊ¿,Ç¹±ø HP³É³¤
		sinChar->sHP.sMax = (short)(fLevel * 3.4f + fstrength * 2.4f + fhealth * 2.4f);
		sinChar->sHP.sMax += (short)(sinLev_Life + sinfIncreLife);
		break;
	case 2://»úÐµ ÓÎÏÀ Ä§Ç¹ ÈøÂú
		sinChar->sHP.sMax = (short)(fLevel * 3.4f + fstrength * 2.1f + fhealth * 2.2f);
		sinChar->sHP.sMax += (short)(sinLev_Life + sinfIncreLife);
		break;
	case 3: // ¹­ÊÖ ´Ì¿Í
		sinChar->sHP.sMax = (short)(fLevel * 3.2f + fstrength * 2.0f + fhealth * 2.6);
		sinChar->sHP.sMax += (short)(sinLev_Life + sinfIncreLife);
		break;
	case 4:// ¼ÀË¾
		sinChar->sHP.sMax = (short)(fLevel * 4.2f + fhealth * 3.0f);
		sinChar->sHP.sMax += (short)(sinLev_Life + sinfIncreLife);
		break;
	case 5: // ·¨Ê¦
		sinChar->sHP.sMax = (short)(fLevel * 3.2f + fhealth * 2.0f);
		sinChar->sHP.sMax += (short)(sinLev_Life + sinfIncreLife);
		break;
	}

	if (!sinQuest_ChangeJob3.CODE && !SearchItemCode(0, ITEMCRAFTTYPE_QuestWeapon) && sinChar->iRank >= 2 && sinChar->iLevel >= 40)
		sinChar->sHP.sMax += 15;

	if ((sinQuest_levelLog & QUESTBIT_LEVEL_90) == QUESTBIT_LEVEL_90)
	{
		if (sinChar->iLevel >= 90)
			sinChar->sHP.sMax += 40;
	}

	switch (sinChar->iMPType)
	{
	case 1: // ¼ÀË¾ Ä§·¨Ê¦ ÈøÂú
		sinChar->sMP.sMax = (short)(fLevel * 1.2f + fSpirit * 3.6f);
		sinChar->sMP.sMax += (short)(sinLev_Mana + sinfIncreMana);
		break;
	case 2:// »úÐµ ÓÎÏÀ Ä§Ç¹
		sinChar->sMP.sMax = (short)(fLevel * 0.9f + fSpirit * 2.7f);
		sinChar->sMP.sMax += (short)(sinLev_Mana + sinfIncreMana);
		break;
	case 3: //ÎäÊ¿ Ç¹±ø ¹­ÊÖ ´Ì¿Í
		sinChar->sMP.sMax = (short)(fLevel * 0.6f + fSpirit * 2.2f);
		sinChar->sMP.sMax += (short)(sinLev_Mana + sinfIncreMana);
		break;
	}

	sinChar->sSP.sMax = (short)(fLevel * 2.3f + fstrength * 0.5f + fSpirit * 1.0f + ftalent * 0.5f + fhealth * 1.4 + 80.0f);
	sinChar->sSP.sMax += (short)(sinfIncreStamina);

	sinChar->fHPRegen = sinfRegenLife + sinPer_Life_Regen;
	sinChar->fMPRegen = sinfRegenMana + sinPer_Mana_Regen;
	sinChar->fSPRegen = sinfRegenStamina + sinPer_Stamina_Regen;

	sinChar->iAttackSpeed = sinWeaponSpeed + sinAdd_Attack_Speed + sinSkillWeaponSpeed;

	for (i = 1; i < MAX_USESKILL; i++)
	{
		if (sinSkill.UseSkill[i].Flag && sinSkill.UseSkill[i].Point)
		{
			switch (sinSkill.UseSkill[i].CODE)
			{
			case SKILL_PHYSICAL_TRANING:
				TempSkillData = (((float)P_Traning_Stamina[sinSkill.UseSkill[i].Point - 1])*(float)sinChar->sSP.sMax / 100.0f);
				sinChar->sSP.sMax += (short)TempSkillData;
				break;
			case SKILL_FIRE_JAVELIN:
				sElement_Attack.Fire[0] += Fire_Javelin_Damage[sinSkill.UseSkill[i].Point - 1][0];
				sElement_Attack.Fire[1] += Fire_Javelin_Damage[sinSkill.UseSkill[i].Point - 1][1];
				break;
			case SKILL_MEDITATION:
				sinChar->fMPRegen += Meditation_Regen[sinSkill.UseSkill[i].Point - 1];
				break;
			case SKILL_MENTAL_MASTERY:
				TempSkillData = (float)((float)(Mental_Mastery_Mana[sinSkill.UseSkill[i].Point - 1])*((float)sinChar->sMP.sMax / 100.0f));
				sinChar->sMP.sMax += (short)TempSkillData;
				break;
			case SKILL_BOOST_HEALTH:
				sinChar->sHP.sMax += (short)Boost_Health_Life[sinSkill.UseSkill[i].Point - 1];
				break;
				//ÄÚÐÄÆ½ºÍ
			case SKILL_INNER_PEACE:
				TempSkillData = (float)((float)(Inner_Peace_AddMana[sinSkill.UseSkill[i].Point - 1])*((float)sinChar->sMP.sMax / 100.0f));
				sinChar->sMP.sMax += (short)TempSkillData;
				break;
				//Ôö¼Ó úÃ?
			case SKILL_HIGH_REGENERATION:
				TempSkillData = (float)((float)(Occult_Lift_HP[sinSkill.UseSkill[i].Point - 1])*((float)sinChar->sHP.sMax / 100.0f));
				sinChar->sHP.sMax += (short)TempSkillData;
				break;
			}
		}
	}

	for (i = 0; i < SINUPKEEPITEM_MAX; i++)
	{
		switch (chaPremiumitem.UpKeepItem[i].TGAImageNumber)
		{
		case nsPremiumItem::BIG_HEAD:
			switch (chaPremiumitem.UpKeepItem[i].Per)
			{
			case 1:
			case 2:
			case 7:
				sinTempDamage2[0] += (sinChar->iMinDamage * 5) / 100;
				sinTempDamage2[1] += (sinChar->iMaxDamage * 5) / 100;
				SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_GOLD;
				break;
			case 3:
				sinChar->sHP.sMax += 50;
				sinChar->sMP.sMax += 50;
				sinChar->sSP.sMax += 50;
				SkillTextColor[SIN2_LIFE] = SIN_TEXT_COLOR_GOLD;
				SkillTextColor[SIN2_MANA] = SIN_TEXT_COLOR_BLUE;
				SkillTextColor[SIN2_STAMINA] = SIN_TEXT_COLOR_GREEN;
				break;
			case 4:
				sinChar->sHP.sMax += 10;
				sinChar->fHPRegen += 10.0f;
				SkillTextColor[SIN2_LIFE] = SIN_TEXT_COLOR_GOLD;
				break;
			case 5:
				sinChar->iMovementSpeed += 3;
				SkillTextColor[SIN2_SPEED] = SIN_TEXT_COLOR_BLUE;
				break;
			case 6:
				sinChar->iBlockRating += 2;
				break;
			}
			break;
		case nsPremiumItem::BIG_GIRAFFEHAT:
			sinChar->iCritical += 5;
			break;
		case nsPremiumItem::BIG_MAGICIANHAT:
		case nsPremiumItem::BIG_WITCHHAT:
			sinChar->fMPRegen += 15.0f;
			break;
		case nsPremiumItem::BIG_MASKEDMAN:
		case nsPremiumItem::BIG_MASKEDWOMAN:
			sinChar->iDefenseRating += 10;
			SkillTextColor[SIN2_DEFENSE] = SIN_TEXT_COLOR_BLUE;
			break;
		case nsPremiumItem::BIG_PUMPKINHAT:
			sinChar->iAbsorbRating += 10;
			SkillTextColor[SIN2_ABSORB] = SIN_TEXT_COLOR_BLUE;
			break;
		case nsPremiumItem::BIG_SHEEPHAT:
			sinChar->sHP.sMax += 100;
			SkillTextColor[SIN2_LIFE] = SIN_TEXT_COLOR_GOLD;
			break;
		case nsPremiumItem::BIG_SOCCERHAT:
			sinChar->iMovementSpeed += 1;
			SkillTextColor[SIN2_SPEED] = SIN_TEXT_COLOR_BLUE;
			break;
		case nsPremiumItem::BIG_GREENXMASHAT:
			sinChar->fMPRegen += 5.0f;
			break;
		case nsPremiumItem::BIG_REDXMASHAT:
			sinChar->fHPRegen += 10.0f;
			break;
		case nsPremiumItem::BIG_EASTER:
			sinChar->iAttackRating += 100;
			SkillTextColor[SIN2_ATTACK_RATE] = SIN_TEXT_COLOR_ORANGE;
			break;
		case nsPremiumItem::BIG_BIRTHDAY:
			sinChar->iBlockRating += 3;
			break;
		case nsPremiumItem::BIG_BLUEXMASHAT:
			sinChar->sMP.sMax += 100;
			SkillTextColor[SIN2_MANA] = SIN_TEXT_COLOR_BLUE;
			break;
		case nsPremiumItem::VAMPIRIC_CUS:
			sinChar->fHPRegen += 25.0f;
			break;
		case nsPremiumItem::MANA_RECHAR_P:
			sinChar->fMPRegen += 25.0f;
			break;
		}
	}

	if (sinChar->iCritical > 50)
		sinChar->iCritical = 50;

	int OrbDamageTemp2 = 0;

	for (i = 0; i < SIN_MAX_SKILL_LIST; i++)
	{
		if (ContinueSkill[i].Flag)
		{
			switch (ContinueSkill[i].CODE)
			{
				// Õ½ ñ×£¸?
			case SKILL_P_ENHENCE:
				SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_GOLD;
				SkillTextColor[SIN2_DEFENSE] = SIN_TEXT_COLOR_BLUE;
				break;
				// Ç±ÄÜ¼¤·¢
			case SKILL_AMPLIFIED:
				SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_GOLD;
				SkillTextColor[SIN2_ATTACK_RATE] = SIN_TEXT_COLOR_ORANGE;
				SkillTextColor[SIN2_ABSORB] = SIN_TEXT_COLOR_RED;
				break;
				//ÇáÎè·ÉÑï
			case SKILL_TALARIA:
				SkillTextColor[SIN2_SPEED] = SIN_TEXT_COLOR_BLUE;
				break;
			case SKILL_HOLY_BODY:
				TempSkillData = ((float)HolyBody_Absorb[ContinueSkill[i].Point - 1] / 100.0f);
				sinUndeadAbsorb = (int)((float)sinChar->iAbsorbRating*TempSkillData);
				break;
				//  ñÁ¦ÖØ»?
			case SKILL_HOLY_VALOR:
				SkillTextColor[SIN2_DEFENSE] = SIN_TEXT_COLOR_BLUE;
				break;
			case SKILL_DRASTIC_SPIRIT:
				TempSkillData = ((float)Drastic_Spirit_Defense[ContinueSkill[i].Point - 1] / 100.0f);
				sinChar->iDefenseRating += (int)((float)sinChar->iDefenseRating * TempSkillData);
				SkillTextColor[SIN2_DEFENSE] = SIN_TEXT_COLOR_BLUE;
				break;
			case SKILL_SPARK_SHIELD:
			case SKILL_METAL_ARMOR:
				if (MetalArmor)
					SkillTextColor[SIN2_DEFENSE] = SIN_TEXT_COLOR_BLUE;
				break;
				//ÌìÅ® ¢»?
			case SKILL_B_KRISHNA:
				SkillTextColor[SIN2_ABSORB] = SIN_TEXT_COLOR_BLUE;
				break;
			case SKILL_CONCENTRATION:
				for (p = 0; p < 10; p++)
				{
					if (sInven[0].ItemIndex)
					{
						if (ContinueSkill[i].Skill_Info.UseWeaponCode[p] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt()&sinITEM_MASK2))
						{
							sinChar->iAttackRating += Concentration_AttackRate[ContinueSkill[i].Point - 1];
							SkillTextColor[SIN2_ATTACK_RATE] = SIN_TEXT_COLOR_ORANGE;
							Flag3 = 1;
							break;
						}
					}
				}
				if (!Flag3)
					SkillTextColor[SIN2_ATTACK_RATE] = SIN_TEXT_COLOR_WHITE;
				break;
			case SKILL_FORCE_ORB:
				OrbDamageTemp2 = (sinChar->iMinDamage + ((sinChar->iMaxDamage - sinChar->iMinDamage) / 2)) / 10;
				sinTempDamage2[0] += OrbDamageTemp2;
				sinTempDamage2[1] += OrbDamageTemp2;

				sinTempDamage2[0] += ForceOrbDamage[ContinueSkill[i].Point - 1];
				sinTempDamage2[1] += ForceOrbDamage[ContinueSkill[i].Point - 1];
				break;
			case SKILL_REGENERATION_FIELD:
				sinChar->fMPRegen += Regeneration_Field_ManaRegen[ContinueSkill[i].Point - 1] / ContinueSkill[i].Flag;
				sinChar->fHPRegen += Regeneration_Field_LifeRegen[ContinueSkill[i].Point - 1];
				break;
			case SKILL_BERSERKER:
				SkillTextColor[SIN2_ABSORB] = SIN_TEXT_COLOR_RED;
				break;
			case SCROLL_INVULNERABILITY:
			case SCROLL_P_INVULNERABILITY:
				SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_RED;
				break;
			case CLANSKILL_ATTACK:
				sinTempDamage2[0] += (int)(sinChar->iMinDamage * 15) / 100;
				sinTempDamage2[1] += (int)(sinChar->iMaxDamage * 15) / 100;
				SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_GOLD;
				break;
				//ÖäÊõÐÅÑö
			case SKILL_CREED:
				sinChar->sMP.sMax += (int)(sinChar->sMP.sMax * Creed_AddMP[ContinueSkill[i].Point - 1]) / 100;
				sinChar->sSP.sMax += (int)(sinChar->sSP.sMax * Creed_AddSP[ContinueSkill[i].Point - 1]) / 100;
				SkillTextColor[SIN2_MANA] = SIN_TEXT_COLOR_BLUE;
				SkillTextColor[SIN2_STAMINA] = SIN_TEXT_COLOR_GREEN;
				break;
			}
		}
	}

	if (chaPremiumitem.m_HelpPetTime > 0 && sinChar->GravityScroolCheck[1] == 2)
	{
		sinTempDamage2[0] += (sinTempDamage2[0] * 10) / 100;
		sinTempDamage2[1] += (sinTempDamage2[1] * 10) / 100;
	}

	if (sinQuest_Level90_2.CODE && sinQuest_Level90_2.State >= 2)
	{
		sinTempDamage2[0] = (sinTempDamage2[0] * 70) / 100;
		sinTempDamage2[1] = (sinTempDamage2[1] * 70) / 100;

		sinChar->iMinDamage = (sinChar->iMinDamage * 70) / 100;
		sinChar->iMaxDamage = (sinChar->iMaxDamage * 70) / 100;
	}

	CheckRequireItem();
	ReformCharForm();
	ReSettingPotion();

	if (!CheckHackFlag)
		memcpy(&sinCharDisplay, sinChar, sizeof(CharacterData));
	else
		HackCharStateCheck(sinChar, &sinCharDisplay);

	return TRUE;
}
void cINVENTORY::LoadCharState()
{
	if (sinChar->sViewBoxZoom.sMin == NULL)
		sinChar->sViewBoxZoom.sMin = 1;
	if (sinChar->sViewBoxZoom.sMax == NULL)
		sinChar->sViewBoxZoom.sMax = 3;
	if (sinChar->sViewBoxZoom.sMin == 1)
		ArrowState[0] = 0;
	if (sinChar->sViewBoxZoom.sMin == 2)
		ArrowState[0] = 1;
	if (sinChar->sViewBoxZoom.sMax == 3)
		ArrowState[1] = 0;
	if (sinChar->sViewBoxZoom.sMax == 4)
		ArrowState[1] = 1;

	OldLevel = sinChar->iLevel;
	OldLevelTemp = OldLevel + 176;
	sinLoadOK = 1;
}

//ÇÐ»»ÎäÆ÷
int cINVENTORY::ChangeABItem(int Posi)
{
	SetDelayFlag = 1;

	if (NotChangeSetItemFlag)
		return TRUE;
	if (ChangeSpecialItem(1))
		return TRUE;

	if (cWareHouse.OpenFlag)
	{
		if (MouseItem.bValid)
			return TRUE;
	}
	if (cCaravan.OpenFlag)
	{
		if (MouseItem.bValid)
			return TRUE;
	}

	if (sMessageBox3[MESSAGE_SELL_HIGHRANK_ITEM].Flag)
		return TRUE;
	if (SpecialItemShowFlag)
		return TRUE;

	CheckInvenItemForm();

	int desPosi;
	int i, j, t;

	if (sMessageBox3[MESSAGE_TELEPORT_CORE].Flag)
		return TRUE;
	for (i = 0; i < SIN_MAX_HELP_NUMBER; i++)
	{
		if (sSinHelp[i].KindFlag == SIN_HELP_KIND_TELEPORT_SCROLL)
			return TRUE;
	}
	if (sinCraftItemStartFlag || StartInterEffectAging2)
		return TRUE;

	else if ((ManufactureItem.m_OpenFlag || SmeltingItem.OpenFlag) && MixCancelButtonDelayFlag)
		return TRUE;

	switch (Posi)
	{
	case 1:
	case 2:
		desPosi = 1;
		break;
	case 3:
	case 4:
		desPosi = 2;
		break;
	case 5:
		desPosi = 3;
		break;
	case 6:
		desPosi = 4;
		break;
	}

	if (Posi == 1)
	{
		ArrowState[0] = 0;
		sinChar->sViewBoxZoom.sMin = 1;
	}
	if (Posi == 2)
	{
		ArrowState[0] = 1;
		sinChar->sViewBoxZoom.sMin = 2;
	}
	if (Posi == 3)
	{
		ArrowState[1] = 0;
		sinChar->sViewBoxZoom.sMax = 3;
	}
	if (Posi == 4)
	{
		ArrowState[1] = 1;
		sinChar->sViewBoxZoom.sMax = 4;
	}
	switch (desPosi)
	{
	case 1:
		memcpy(&BackUpInvenItemTemp, &InvenItemTemp, sizeof(ItemData) * 80);
		for (t = 0; t < 80; t++)
			InvenItemTemp[t].bValid = 0;
		for (i = 0; i < 80; i++)
		{
			if (InvenItem[i].bValid)
			{
				if (InvenItem[i].iItemSlot == 0)
				{
					for (j = 0; j < 80; j++)
					{
						if (!InvenItemTemp[j].bValid)
						{
							memcpy(&InvenItemTemp[j], &InvenItem[i], sizeof(ItemData));
							InvenItem[i].bValid = 0;
							break;
						}
					}
				}
			}
		}
		for (i = 0; i < 80; i++)
		{
			if (BackUpInvenItemTemp[i].bValid)
			{
				for (j = 0; j < 80; j++)
				{
					if (!InvenItem[j].bValid)
					{
						memcpy(&InvenItem[j], &BackUpInvenItemTemp[i], sizeof(ItemData));
						BackUpInvenItemTemp[i].bValid = 0;
						break;
					}
				}
			}
		}
		break;
	case 2:
		ContinueSkillCancelFlag = 1;
		memcpy(&BackUpInvenItemTemp[80], &InvenItemTemp[80], sizeof(ItemData) * 2);
		for (t = 80; t < 82; t++)
			InvenItemTemp[t].bValid = 0;
		for (i = 0; i < 80; i++)
		{
			if (InvenItem[i].bValid)
			{
				if (InvenItem[i].iItemSlot == 1 || InvenItem[i].iItemSlot == 2)
				{
					for (j = 80; j < 82; j++)
					{
						if (!InvenItemTemp[j].bValid)
						{
							memcpy(&InvenItemTemp[j], &InvenItem[i], sizeof(ItemData));
							InvenItem[i].bValid = 0;
							sInven[InvenItem[i].iItemSlot - 1].ItemIndex = 0;
							sinSetCharItem(InvenItem[i].sBaseItemID.ToInt(), InvenItem[i].iVisibleItemType, FALSE);
							break;
						}
					}
				}
			}
		}

		for (i = 80; i < 82; i++)
		{
			if (BackUpInvenItemTemp[i].bValid)
			{
				for (j = 0; j < 80; j++)
				{
					if (!InvenItem[j].bValid)
					{
						memcpy(&InvenItem[j], &BackUpInvenItemTemp[i], sizeof(ItemData));
						BackUpInvenItemTemp[i].bValid = 0;
						sInven[InvenItem[j].iItemSlot - 1].ItemIndex = j + 1;
						if ((InvenItem[j].sBaseItemID.ToInt() & sinITEM_MASK2) == sinWD1)
						{
							switch (InvenItem[j].iItemSlot)
							{
							case 1:
								InvenItem[j].iVisibleItemType = ITEMSLOTFLAG_RightHand;
								break;
							case 2:
								InvenItem[j].iVisibleItemType = ITEMSLOTFLAG_LeftHand;
								break;
							}
						}
						sinSetCharItem(InvenItem[j].sBaseItemID.ToInt(), InvenItem[j].iVisibleItemType, TRUE);
						if (InvenItem[j].iInvItemSound)
							sinPlaySound(InvenItem[j].iInvItemSound);
						break;
					}
				}
			}
		}
		SetItemToChar();
		break;
	case 3:
		for (i = 0; i < 80; i++)
		{
			if (InvenItem[i].bValid)
			{
				if (InvenItem[i].iItemSlot == 3)
				{
					sInven[InvenItem[i].iItemSlot - 1].ItemIndex = 0;
					sinSetCharItem(InvenItem[i].sBaseItemID.ToInt(), InvenItem[i].iVisibleItemType, FALSE);
				}
			}
		}
		for (i = 0; i < 80; i++)
		{
			if (InvenItem[i].bValid)
			{
				if (InvenItem[i].iItemSlot == 14)
				{
					sInven[InvenItem[i].iItemSlot - 1].ItemIndex = i + 1;
					sinSetCharItem(InvenItem[i].sBaseItemID.ToInt(), InvenItem[i].iVisibleItemType, TRUE);
					if (InvenItem[i].iInvItemSound)
						sinPlaySound(InvenItem[i].iInvItemSound);
				}
			}
		}
		break;
	case 4:
		for (i = 0; i < 80; i++)
		{
			if (InvenItem[i].bValid)
			{
				if (InvenItem[i].iItemSlot == 14)
				{
					sInven[InvenItem[i].iItemSlot - 1].ItemIndex = 0;
					sinSetCharItem(InvenItem[i].sBaseItemID.ToInt(), InvenItem[i].iVisibleItemType, FALSE);
				}
			}
		}
		for (i = 0; i < 80; i++)
		{
			if (InvenItem[i].bValid)
			{
				if (InvenItem[i].iItemSlot == 3)
				{
					sInven[InvenItem[i].iItemSlot - 1].ItemIndex = i + 1;
					sinSetCharItem(InvenItem[i].sBaseItemID.ToInt(), InvenItem[i].iVisibleItemType, TRUE);
					if (InvenItem[i].iInvItemSound)
						sinPlaySound(InvenItem[i].iInvItemSound);
					break;
				}
			}
		}
		break;
	}

	for (i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].bValid)
		{
			if (InvenItem[i].iItemSlot)
			{
				if (InvenItem[i].iItemSlotFlag == ITEMSLOTFLAG_LeftRightHand && (InvenItem[i].sBaseItemID.ToInt() & sinITEM_MASK2) != sinWD1)
				{
					if (InvenItem[i].iItemSlot == 1)
					{
						if (InvenItem[i].sItem.sItemID.ToInt() != InvenItem[sInven[1].ItemIndex - 1].sItem.sItemID.ToInt())
						{
							InvenItem[sInven[1].ItemIndex - 1].bValid = 0;
							InvenItem[i].bValid = 0;
							sInven[1].ItemIndex = 0;
							sInven[0].ItemIndex = 0;

							if (InvenItem[i].iVisibleItemType)
								sinSetCharItem(InvenItem[i].sBaseItemID.ToInt(), InvenItem[i].iVisibleItemType, FALSE);
						}
					}
					if (InvenItem[i].iItemSlot == 2)
					{
						if (InvenItem[i].sItem.sItemID.ToInt() != InvenItem[sInven[0].ItemIndex - 1].sItem.sItemID.ToInt())
						{
							InvenItem[sInven[0].ItemIndex - 1].bValid = 0;
							InvenItem[i].bValid = 0;
							sInven[0].ItemIndex = 0;
							sInven[1].ItemIndex = 0;

							if (InvenItem[i].iVisibleItemType)
								sinSetCharItem(InvenItem[i].sBaseItemID.ToInt(), InvenItem[i].iVisibleItemType, FALSE);
						}
					}
				}
			}
		}
	}

	if (MouseItem.bValid)
	{
		if (MouseItem.iItemSlotFlag == ITEMSLOTFLAG_Potion)
			GhostPotionCheckFlag = 1;
		else
			GhostPotionCheckFlag = 0;
	}
	else
		GhostPotionCheckFlag = 0;

	CheckRequireItem();
	ReFormInvenItem();
	cInvenTory.CheckPuzzle();
	return TRUE;
}
sITEMPRICE cINVENTORY::GetInvenItemPrice(ItemData *pItem)
{
	sITEMPRICE sinItemPrice;

	if (pItem->iItemSlotFlag == ITEMSLOTFLAG_LeftRightHand && (pItem->sBaseItemID.ToInt() & sinITEM_MASK2) != sinWD1)
	{
		if (pItem->iItemSlot)
			pItem = &InvenItem[sInven[0].ItemIndex - 1];
	}
	else if (pItem->iItemSlotFlag == ITEMSLOTFLAG_Wing)
	{
		if (pItem->iItemSlot)
			pItem = &InvenItem[sInven[14].ItemIndex - 1];
	}

	float Dur[2];
	float Price;

	Dur[0] = pItem->sItem.sIntegrity.sMin;
	Dur[1] = pItem->sItem.sIntegrity.sMax;
	Price = (float)pItem->sItem.iSalePrice;
	if (Dur[0] == 0)
		Dur[0] = 1;
	if (Dur[1] == 0)
		Dur[1] = 1;

	sinItemPrice.PureSellPrice = (int)((Price*(Dur[0] / Dur[1])) + (Price - (Price*(Dur[0] / Dur[1])))*0.25);
	sinItemPrice.SellPrice = (int)sinItemPrice.PureSellPrice / 5;
	sinItemPrice.RepairCost = (pItem->sItem.iSalePrice - sinItemPrice.PureSellPrice) / 8;

	if (pItem->sBaseItemID.ToInt() == (sinSP1 | sin64) ||
		pItem->sBaseItemID.ToInt() == (sinSP1 | sin65) ||
		pItem->sBaseItemID.ToInt() == (sinSP1 | sin66) ||
		pItem->sBaseItemID.ToInt() == (sinSP1 | sin67) ||
		pItem->sBaseItemID.ToInt() == (sinSP1 | sin68))
	{
		sinItemPrice.SellPrice = int(Price);
		sinItemPrice.RepairCost = 0;
	}


	return sinItemPrice;

}
int cINVENTORY::RepairInvenItem(ItemData *pItem, int RepairCost)
{
	if (pItem->iItemSlotFlag == ITEMSLOTFLAG_LeftRightHand && (pItem->sBaseItemID.ToInt() & sinITEM_MASK2) != sinWD1)
	{
		if (pItem->iItemSlot)
			pItem = &InvenItem[sInven[0].ItemIndex - 1];
	}
	else if (pItem->iItemSlotFlag == ITEMSLOTFLAG_Wing)
	{
		if (pItem->iItemSlot)
			pItem = &InvenItem[sInven[14].ItemIndex - 1];
	}

	CheckCharForm();
	if (!pItem->sItem.sIntegrity.sMax)
		return FALSE;
	if (sinChar->iGold - RepairCost > 0)
	{
		if (pItem->sItem.sIntegrity.sMin < pItem->sItem.sIntegrity.sMax)
		{
			sinMinusMoney(RepairCost);
			pItem->sItem.sIntegrity.sMin = pItem->sItem.sIntegrity.sMax;
			ReformCharForm();
			SendSaveMoney();
			return TRUE;
		}
	}
	return FALSE;

}
void cINVENTORY::CheckWeight()
{
	CheckCharForm();

	sinChar->sWeight.sMin = 0;
	for (int i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].bValid)
		{
			if (InvenItem[i].iItemSlotFlag == ITEMSLOTFLAG_Potion)
			{
				if (InvenItem[i].sItem.iPotionCount < 0)
					continue;
				sinChar->sWeight.sMin += InvenItem[i].sItem.iPotionCount;
				continue;
			}
			if (InvenItem[i].sItem.iWeight < 0)
				continue;
			sinChar->sWeight.sMin += InvenItem[i].sItem.iWeight;
		}
	}
	for (int j = 0; j < INVENTORY_MAXITEM; j++)
	{
		if (InvenItemTemp[j].bValid)
		{
			if (InvenItemTemp[j].iItemSlotFlag == ITEMSLOTFLAG_Potion)
			{
				if (InvenItemTemp[j].sItem.iPotionCount < 0)
					continue;
				sinChar->sWeight.sMin += InvenItemTemp[j].sItem.iPotionCount;
				continue;
			}
			if (InvenItemTemp[j].sItem.iWeight < 0)
				continue;
			sinChar->sWeight.sMin += InvenItemTemp[j].sItem.iWeight;
		}
	}

	ReformCharForm();

}
int cINVENTORY::CheckSetOk(ItemData *pItem, int AutoFlag)
{
	if (pItem->iItemSlotFlag == ITEMSLOTFLAG_Potion)
	{
		if (sinChar->sWeight.sMin + pItem->sItem.iPotionCount > sinChar->sWeight.sMax)
		{
			cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
			sinOverWeightCnt++;
			return FALSE;
		}
	}
	else
	{
		if (sinChar->sWeight.sMin + pItem->sItem.iWeight > sinChar->sWeight.sMax)
		{
			if (pItem->sItem.eCraftType != ITEMCRAFTTYPE_QuestWeapon)
			{
				cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
				sinOverWeightCnt++;
				return FALSE;
			}
		}
	}
	if (!AutoFlag)
	{
		if (pItem->iItemSlot)
		{
			if (pItem->sItem.bCanNotUse)
			{
				cMessageBox.ShowMessage(MESSAGE_NO_USE_ITEM);
				return FALSE;
			}
		}
	}
	return TRUE;
}
int cINVENTORY::CopyItemClear(ItemData *pItem)
{
	int CopyItemCnt = 0;
	for (int i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].bValid)
		{
			if (CompareItems(&pItem->sItem, &InvenItem[i].sItem))
			{
				InvenItem[i].bValid = 0;
				if (InvenItem[i].iItemSlot)
				{
					sInven[InvenItem[i].iItemSlot - 1].ItemIndex = 0;
					sinSetCharItem(InvenItem[i].sBaseItemID.ToInt(), InvenItem[i].iVisibleItemType, FALSE);
					ClearTwoHandPosiAndItem(&InvenItem[i]);
				}
				CopyItemCnt++;
			}
		}
		if (InvenItemTemp[i].bValid)
		{
			if (CompareItems(&pItem->sItem, &InvenItemTemp[i].sItem))
			{
				InvenItemTemp[i].bValid = 0;
				if (InvenItemTemp[i].iItemSlotFlag == ITEMSLOTFLAG_LeftRightHand && (InvenItemTemp[i].sBaseItemID.ToInt() & sinITEM_MASK2) != sinWD1)
				{
					if (InvenItemTemp[i].iItemSlot == 1 ||
						InvenItemTemp[i].iItemSlot == 2)
					{
						for (int k = 0; k < INVENTORY_MAXITEM; k++)
						{
							if (InvenItemTemp[k].bValid)
							{
								if (InvenItemTemp[k].iItemSlot == 1 ||
									InvenItemTemp[k].iItemSlot == 2)
								{
									if (InvenItemTemp[i].sItem.sItemID.ToInt() == InvenItemTemp[k].sItem.sItemID.ToInt())
										InvenItemTemp[k].bValid = 0;
								}
							}
						}
					}
				}
				else if (InvenItemTemp[i].iItemSlotFlag == ITEMSLOTFLAG_Wing)
				{
					if (InvenItemTemp[i].iItemSlot == 15 || InvenItemTemp[i].iItemSlot == 16)
					{
						for (int k = 0; k < INVENTORY_MAXITEM; k++)
						{
							if (InvenItemTemp[k].bValid)
							{
								if (InvenItemTemp[k].iItemSlot == 15 || InvenItemTemp[k].iItemSlot == 16)
								{
									if (InvenItemTemp[i].sItem.sItemID.ToInt() == InvenItemTemp[k].sItem.sItemID.ToInt())
										InvenItemTemp[k].bValid = 0;
								}
							}
						}
					}
				}
				CopyItemCnt++;
			}
		}
	}
	if (CopyItemCnt)
	{
		SendCopyItemUser(CopyItemCnt);
		CopyItemCnt = 0;
	}
	return TRUE;

}

POINT ResultSize;

int cINVENTORY::ImsiCheckItemImageSize()
{
	ItemData TestItem;
	POINT TestPoint = { 0,0 };
	char szFilePath[256];
	sinTestBuff[0] = 0;
	auto vItemTable = ITEMHANDLE->GetItemTable();

	for (auto &pItem : vItemTable)
	{
		wsprintf(szFilePath, "Image\\sinImage\\Items\\%s\\it%s.bmp", pItem->szCategory, pItem->szInventoryName);
		memcpy(&TestItem, pItem, sizeof(ItemData));
		TestItem.pcInventoryTexture = LoadDibSurfaceOffscreen(szFilePath);
		TestPoint.x = 0;
		TestPoint.y = 0;
		if (TestItem.pcInventoryTexture)
		{
			TestPoint.x = ((smTEXTUREHANDLE *)(TestItem.pcInventoryTexture))->Width;
			TestPoint.y = ((smTEXTUREHANDLE *)(TestItem.pcInventoryTexture))->Height;

			if (TestPoint.x != pItem->iWidth || TestPoint.y != pItem->iHeight)
				lstrcpy(sinTestBuff, pItem->szInventoryName);
		}
	}

	return TRUE;
}
int cINVENTORY::CheckOverlapItem(ItemData *pItem, int PassItemIndex)
{
	int ReSetXYFlag = 0;
	if (!pItem)
		return FALSE;
	if (pItem->iItemSlot)
	{
		if (pItem->iItemSlot < 11)
		{
			sInven[pItem->iItemSlot - 1].ItemIndex = 0;
			pItem->iItemSlot = 0;
			ReSetXYFlag = 1;
		}
		else
			ReSetXYFlag = 0;
	}

	RECT Rect;
	int  TempPosiFlag = 0;
	Rect.left	= pItem->iPlaceX;
	Rect.top	= pItem->iPlaceY;
	Rect.right	= pItem->iWidth;
	Rect.bottom = pItem->iHeight;

	int cntx, cnty;
	int cx, cy;

	RECT	rect;
	int		flag;

	cx = (22 * INVENTORY_BOX_ROW) - pItem->iWidth;
	cy = (22 * INVENTORY_BOX_COL) - pItem->iHeight;

	if (CrashInvenItem(Rect, PassItemIndex) || ReSetXYFlag)
	{
		for (cntx = StartX; cntx <= StartX + cx; cntx += 22)
		{
			for (cnty = StartY; cnty <= StartY + cy; cnty += 22)
			{
				flag = 0;
				for (int i = 0; i < INVENTORY_MAXITEM; i++)
				{
					if (InvenItem[i].bValid)
					{
						rect.left   = InvenItem[i].iPlaceX;
						rect.right  = InvenItem[i].iPlaceX + InvenItem[i].iWidth;
						rect.top    = InvenItem[i].iPlaceY;
						rect.bottom = InvenItem[i].iPlaceY + InvenItem[i].iHeight;

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

					sInven[pItem->iItemSlot - 1].ItemIndex = 0;
					pItem->iItemSlot = 0;
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}
int cINVENTORY::ReSetPotionXY(ItemData *pItem, int kind)
{

	RECT Rect;
	Rect.left	= pItem->iPlaceX;
	Rect.top	= pItem->iPlaceY;
	Rect.right	= pItem->iWidth;
	Rect.bottom = pItem->iHeight;

	int cntx, cnty;
	int cx, cy;

	RECT	rect;
	int		flag;

	cx = (22 * INVENTORY_BOX_ROW) - pItem->iWidth;
	cy = (22 * INVENTORY_BOX_COL) - pItem->iHeight;

	if (kind == 1)
	{
		for (cntx = StartX; cntx <= StartX + cx; cntx += 22)
		{
			for (cnty = StartY; cnty <= StartY + cy; cnty += 22)
			{
				flag = 0;
				for (int i = 0; i < INVENTORY_MAXITEM; i++)
				{
					if (InvenItemTemp[i].bValid)
					{
						rect.left	= InvenItemTemp[i].iPlaceX;
						rect.right	= InvenItemTemp[i].iPlaceX + InvenItemTemp[i].iWidth;
						rect.top	= InvenItemTemp[i].iPlaceY;
						rect.bottom = InvenItemTemp[i].iPlaceY + InvenItemTemp[i].iHeight;

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
	}
	else
	{
		for (cntx = StartX; cntx <= StartX + cx; cntx += 22)
		{
			for (cnty = StartY; cnty <= StartY + cy; cnty += 22)
			{
				flag = 0;
				for (int i = 0; i < INVENTORY_MAXITEM; i++)
				{
					if (InvenItem[i].bValid)
					{
						rect.left	= InvenItem[i].iPlaceX;
						rect.right	= InvenItem[i].iPlaceX + InvenItem[i].iWidth;
						rect.top	= InvenItem[i].iPlaceY;
						rect.bottom = InvenItem[i].iPlaceY + InvenItem[i].iHeight;

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

					sInven[pItem->iItemSlot - 2].ItemIndex = 0;
					pItem->iItemSlot = 0;
					return TRUE;
				}
			}
		}
	}
	return FALSE;

}
int cINVENTORY::UseEcore(ItemData *pItem)
{
	char szLinkName[24];
	int len = lstrlen(pItem->sItem.szItemName);
	if (sinItemPickUpDelayFlag)
		return FALSE;
	if (STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapType == MAPTYPE_ChessRoom)
	{
		if (pItem->sItem.sItemID.ToInt() == (sinEC1 | sin01) ||
			pItem->sItem.sItemID.ToInt() == (sinEC1 | sin02) ||
			pItem->sItem.sItemID.ToInt() == (sinEC1 | sin04) ||
			pItem->sItem.sItemID.ToInt() == (sinEC1 | sin06))
		{
			cMessageBox.ShowMessage(MESSAGE_NO_USE_ITEM);
			return FALSE;
		}
	}
	if (pItem->sItem.sItemID.ToInt() == (sinEC1 | sin05))
	{
		if (sinChar->iClanID)
		{
			if (cldata.stats[0] == '1')
			{
				if (pItem->sItem.szItemName[len + 1] == NULL)
				{
					UnionCorePosi.x = pItem->iPlaceX;
					UnionCorePosi.y = pItem->iPlaceY;
					memset(&TempLinkCoreItem, 0, sizeof(Item));
					memcpy(&TempLinkCoreItem, &pItem->sItem, sizeof(Item));
					cMessageBox.ShowMessage3(MESSAGE_LINKCORE, "");
				}
				else
				{
					lstrcpy(szLinkName, &pItem->sItem.szItemName[len + 1]);
					if (lstrcmpi(sinChar->szName, szLinkName) != 0)
						SendLinkCoreToServer(&pItem->sItem);
				}
			}
			else
				cMessageBox.ShowMessage(MESSAGE_USE_REGULAR_CLAN_ONLY);
		}
		else
			cMessageBox.ShowMessage(MESSAGE_USE_CLAN_ONLY);
	}
	else
	{
		CheckInvenItemForm();
		ActionEtherCore(pItem);
		pItem->bValid = 0;
		CheckWeight();
		ReFormInvenItem();
	}
	sinUsePotionDelayFlag = 1;
	return TRUE;
}
int cINVENTORY::EatSongPyeun(ItemData *pItem)
{
	if ((pItem->sBaseItemID.ToInt() & sinITEM_MASK3) == sin05 ||
		(pItem->sBaseItemID.ToInt() & sinITEM_MASK3) == sin06 ||
		(pItem->sBaseItemID.ToInt() & sinITEM_MASK3) == sin07 ||
		(pItem->sBaseItemID.ToInt() & sinITEM_MASK3) == sin08 ||
		(pItem->sBaseItemID.ToInt() & sinITEM_MASK3) == sin09 ||
		(pItem->sBaseItemID.ToInt() & sinITEM_MASK3) == sin10)
	{
		ReFormInvenItem();
		sinUsePotionDelayFlag = 1;
		return TRUE;
	}

	if (cItem.GetItemLimitTime(pItem) == FALSE)
	{
		CHATGAMEHANDLE->SendChat(FALSE, FormatString("%s : %s", sinChar->szName, "Oh, this moon cake is broken.!"));
		ReFormInvenItem();
		sinUsePotionDelayFlag = 1;
		return FALSE;
	}
	int TempRandPotion = 0;
	int ResultPotion = 0;
	int Life = 0, Mana = 0, Stamina = 0;

	TempRandPotion = pItem->sItem.sHPRecovery.sMax - pItem->sItem.sHPRecovery.sMin;
	ResultPotion = pItem->sItem.sHPRecovery.sMin + (rand() % TempRandPotion);
	sinSetLife((sinGetLife() + ResultPotion));
	Life = (sinGetLife() + ResultPotion);

	TempRandPotion = pItem->sItem.sMPRecovery.sMax - pItem->sItem.sMPRecovery.sMin;
	ResultPotion = pItem->sItem.sMPRecovery.sMin + (rand() % TempRandPotion);
	sinSetMana((sinGetMana() + ResultPotion));
	Mana = (sinGetLife() + ResultPotion);

	TempRandPotion = pItem->sItem.sSPRecovery.sMax - pItem->sItem.sSPRecovery.sMin;
	ResultPotion = pItem->sItem.sSPRecovery.sMin + (rand() % TempRandPotion);
	sinSetStamina((sinGetStamina() + ResultPotion));
	Stamina = (sinGetLife() + ResultPotion);

	smTRANS_COMMAND	smTransCommand;

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = smTRANSCODE_PARTY_POTION;
	smTransCommand.WParam = Life;
	smTransCommand.LParam = Mana;
	smTransCommand.SParam = Stamina;
	smTransCommand.EParam = lpCurPlayer->iID;

	if (InterfaceParty.PartyMemberCount)
		SENDPACKETG(&smTransCommand);

	ReFormInvenItem();
	sinUsePotionDelayFlag = 1;

	return TRUE;

}
int cINVENTORY::ResetMouseItem()
{
	if (MouseItem.bValid)
	{
		if (cInvenTory.AutoSetInvenItem(&MouseItem))
			MouseItem.bValid = 0;
	}

	return TRUE;
}
int cINVENTORY::CheckInvenItemForm()
{
	DWORD TempCheckDataSum = 0;

	for (int i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].bValid)
		{
			if (InvenItem[i].iItemSlotFlag != ITEMSLOTFLAG_Potion)
			{
				TempCheckDataSum += (i + 1)*InvenItem[i].iPlaceY;
				TempCheckDataSum += (i + 1)*InvenItem[i].iItemSlotFlag;
				TempCheckDataSum += InvenItem[i].sItem.iChk2;
				TempCheckDataSum += InvenItem[i].sItem.iChk1;
			}

		}
		if (InvenItemTemp[i].bValid)
		{
			if (InvenItemTemp[i].iItemSlotFlag != ITEMSLOTFLAG_Potion)
			{
				TempCheckDataSum += (i + 1)*InvenItemTemp[i].iPlaceY;
				TempCheckDataSum += (i + 1)*InvenItemTemp[i].iItemSlotFlag;
				TempCheckDataSum += InvenItemTemp[i].sItem.iChk2;
				TempCheckDataSum += InvenItemTemp[i].sItem.iChk1;
			}
		}
	}
	if (TempCheckDataSum != InvenDataCheckSum)
		SendSetHackUser(2);
	return TRUE;
}
int cINVENTORY::ReFormInvenItem()
{
	DWORD Temp = 0;
	InvenDataCheckSum = 0;

	for (int i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].bValid)
		{
			if (InvenItem[i].iItemSlotFlag != ITEMSLOTFLAG_Potion)
			{
				InvenDataCheckSum += (i + 1)*InvenItem[i].iPlaceY;
				InvenDataCheckSum += (i + 1)*InvenItem[i].iItemSlotFlag;
				InvenDataCheckSum += InvenItem[i].sItem.iChk2;
				InvenDataCheckSum += InvenItem[i].sItem.iChk1;
			}
		}
		if (InvenItemTemp[i].bValid)
		{
			if (InvenItemTemp[i].iItemSlotFlag != ITEMSLOTFLAG_Potion)
			{
				InvenDataCheckSum += (i + 1)*InvenItemTemp[i].iPlaceY;
				InvenDataCheckSum += (i + 1)*InvenItemTemp[i].iItemSlotFlag;
				InvenDataCheckSum += InvenItemTemp[i].sItem.iChk2;
				InvenDataCheckSum += InvenItemTemp[i].sItem.iChk1;
			}
		}
	}
	Temp = InvenDataCheckSum;

	return TRUE;

}
int cINVENTORY::CheckMoneyLimit(int Money)
{
	int MoneyX2 = 1;

	if ((haElementaryQuestLog & QUESTBIT_ELEMENTARY_H) != 0)
		MoneyX2 = 2;

	if (sinChar->iLevel <= 10)
	{
		if ((sinChar->iGold + Money) <= 200000 * MoneyX2)
			return TRUE;
	}
	else
	{
		switch (sinChar->iRank)
		{
		case 0:
			if ((sinChar->iGold + Money) <= ((sinChar->iLevel * 200000) - 1800000) * MoneyX2)
				return TRUE;
			break;
		case 1:
			if ((sinChar->iGold + Money) <= 10000000 * MoneyX2)
				return TRUE;
			break;
		case 2:
			if ((sinChar->iGold + Money) <= 50000000 * MoneyX2)
				return TRUE;
			break;
		case 3:
			if ((sinChar->iGold + Money) <= 100000000 * MoneyX2)
				return TRUE;
			break;
		case 4:
			if ((sinChar->iGold + Money) <= 500000000 * MoneyX2)
				return TRUE;
			break;
		}
	}

	cMessageBox.ShowMessage(MESSAGE_OVER_MONEY);
	return FALSE;
}

int sinPotionNum[4] = { 0,0,0,0 };
int CheckPotionNum[4] = { 0,0,0,0 };
int cINVENTORY::ReFormPotionNum()
{
	PotionCheckNumJumpFlag = 1;

	for (int j = 0; j < 4; j++)
		sinPotionNum[j] = 0;

	for (int i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].bValid)
		{
			if (InvenItem[i].iItemSlotFlag == ITEMSLOTFLAG_Potion)
			{
				switch (InvenItem[i].sBaseItemID.ToInt() & sinITEM_MASK3)
				{
				case sin01:
					sinPotionNum[0] += InvenItem[i].sItem.iPotionCount;
					break;
				case sin02:
					sinPotionNum[1] += InvenItem[i].sItem.iPotionCount;
					break;
				case sin03:
					sinPotionNum[2] += InvenItem[i].sItem.iPotionCount;
					break;
				case sin04:
					sinPotionNum[3] += InvenItem[i].sItem.iPotionCount;
					break;
				}
			}
		}
		if (InvenItemTemp[i].bValid)
		{
			if (InvenItemTemp[i].iItemSlotFlag == ITEMSLOTFLAG_Potion)
			{
				switch (InvenItemTemp[i].sBaseItemID.ToInt() & sinITEM_MASK3)
				{
				case sin01:
					sinPotionNum[0] += InvenItemTemp[i].sItem.iPotionCount;
					break;
				case sin02:
					sinPotionNum[1] += InvenItemTemp[i].sItem.iPotionCount;
					break;
				case sin03:
					sinPotionNum[2] += InvenItemTemp[i].sItem.iPotionCount;
					break;
				case sin04:
					sinPotionNum[3] += InvenItemTemp[i].sItem.iPotionCount;
					break;
				}
			}
		}
	}
	PotionCheckNumJumpFlag = 0;
	return TRUE;
}

DWORD PotionCheckDelayTime = 0;
int cINVENTORY::CheckPotionNumForm()
{
	for (int k = 0; k < 4; k++)
		CheckPotionNum[k] = 0;
	for (int i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].bValid)
		{
			if (InvenItem[i].iItemSlotFlag == ITEMSLOTFLAG_Potion)
			{
				switch (InvenItem[i].sBaseItemID.ToInt() & sinITEM_MASK3)
				{
				case sin01:
					CheckPotionNum[0] += InvenItem[i].sItem.iPotionCount;
					break;
				case sin02:
					CheckPotionNum[1] += InvenItem[i].sItem.iPotionCount;
					break;
				case sin03:
					CheckPotionNum[2] += InvenItem[i].sItem.iPotionCount;
					break;
				case sin04:
					CheckPotionNum[3] += InvenItem[i].sItem.iPotionCount;
					break;
				}
			}
		}
		if (InvenItemTemp[i].bValid)
		{
			if (InvenItemTemp[i].iItemSlotFlag == ITEMSLOTFLAG_Potion)
			{
				switch (InvenItemTemp[i].sBaseItemID.ToInt() & sinITEM_MASK3)
				{
				case sin01:
					CheckPotionNum[0] += InvenItemTemp[i].sItem.iPotionCount;
					break;
				case sin02:
					CheckPotionNum[1] += InvenItemTemp[i].sItem.iPotionCount;
					break;
				case sin03:
					CheckPotionNum[2] += InvenItemTemp[i].sItem.iPotionCount;
					break;
				case sin04:
					CheckPotionNum[3] += InvenItemTemp[i].sItem.iPotionCount;
					break;
				}
			}
		}
	}
	for (int j = 0; j < 4; j++)
	{
		if (CheckPotionNum[j] != sinPotionNum[j])
			SendSetHackUser2(1510, j);
	}
	return TRUE;
}
int cINVENTORY::CheckSpecialItem(ItemData *pItem)
{
	if (pItem->sItem.eCraftType == ITEMCRAFTTYPE_Quest || pItem->sItem.iItemUniqueID)
		return FALSE;

	return TRUE;
}
int dwInvenParticleShowTime = 0;
int cINVENTORY::ShowInvenEffectParticle()
{
	int i = 0;

	dwInvenParticleShowTime++;
	if (dwInvenParticleShowTime <= 5)
		return FALSE;
	dwInvenParticleShowTime = 0;

	int TempX, TempY;

	if (MouseItem.bValid)
	{
		if (MouseItem.sItem.eCraftType == ITEMCRAFTTYPE_Quest || MouseItem.sItem.iItemUniqueID)
		{
			TempX = rand() % MouseItem.iWidth;
			TempY = rand() % MouseItem.iHeight;
			SetInvenParticle(MouseItem.iPlaceX + TempX,
				MouseItem.iPlaceY + TempY, SIN_EFFECT_SHOW_INVEN);
		}
	}

	for (i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].bValid)
		{
			if (InvenItem[i].sItem.eCraftType == ITEMCRAFTTYPE_Quest || InvenItem[i].sItem.iItemUniqueID)
			{
				TempX = rand() % InvenItem[i].iWidth;
				TempY = rand() % InvenItem[i].iHeight;
				SetInvenParticle(InvenItem[i].iPlaceX + TempX,
					InvenItem[i].iPlaceY + TempY, SIN_EFFECT_SHOW_INVEN);

				if (InvenItem[i].iItemSlotFlag == ITEMSLOTFLAG_LeftRightHand && (InvenItem[i].sBaseItemID.ToInt() & sinITEM_MASK2) != sinWD1)
				{
					if (i == sInven[0].ItemIndex - 1)
					{
						TempX = rand() % (sInven[1].Rect.right - 10 - sInven[1].Rect.left + 10);
						TempY = rand() % (sInven[1].Rect.bottom - 10 - sInven[1].Rect.top + 10);
						SetInvenParticle(sInven[1].Rect.left + TempX, sInven[1].Rect.top + TempY, SIN_EFFECT_SHOW_INVEN);
					}
				}
			}
		}
	}

	for (i = 0; i < MAX_TRADE_ITEM; i++)
	{
		if (sTrade.TradeItem[i].bValid)
		{
			if (sTrade.TradeItem[i].sItem.iItemUniqueID)
			{
				TempX = rand() % sTrade.TradeItem[i].iWidth;
				TempY = rand() % sTrade.TradeItem[i].iHeight;
				SetInvenParticle(sTrade.TradeItem[i].iPlaceX + TempX,
					sTrade.TradeItem[i].iPlaceY + TempY,
					SIN_EFFECT_SHOW_TRADE);
			}
		}
		if (sTradeRecv.TradeItem[i].bValid)
		{
			if (sTradeRecv.TradeItem[i].sItem.iItemUniqueID)
			{
				TempX = rand() % sTradeRecv.TradeItem[i].iWidth;
				TempY = rand() % sTradeRecv.TradeItem[i].iHeight;
				SetInvenParticle(sTradeRecv.TradeItem[i].iPlaceX + TempX,
					sTradeRecv.TradeItem[i].iPlaceY + TempY, SIN_EFFECT_SHOW_TRADE);
			}
		}
	}

	for (i = 0; i < 100; i++)
	{
		if (cWareHouse.WareHouse.WareHouseItem[i].bValid)
		{
			if (cWareHouse.WareHouse.WareHouseItem[i].sItem.iItemUniqueID)
			{
				TempX = rand() % cWareHouse.WareHouse.WareHouseItem[i].iWidth;
				TempY = rand() % cWareHouse.WareHouse.WareHouseItem[i].iHeight;
				SetInvenParticle(cWareHouse.WareHouse.WareHouseItem[i].iPlaceX + TempX,
					cWareHouse.WareHouse.WareHouseItem[i].iPlaceY + TempY,
					SIN_EFFECT_SHOW_WAREHOUSE);
			}
		}
	}

	return TRUE;
}
int cINVENTORY::SetInvenParticle(int x, int y, int Kind)
{
	int i, k;
	int TempSize;
	int Count = 0;

	for (i = 0; i < MAX_INVEN_PARTICLE; i++)
	{
		if (!sInven_Effect[i].Time)
		{
			sInven_Effect[i].Kind = Kind;
			sInven_Effect[i].Time = 1;
			sInven_Effect[i].Max_Time = rand() % 20 + 3;

			sInven_Effect[i].InvenFace.x = x;
			sInven_Effect[i].InvenFace.y = y;
			TempSize = rand() % 13 + 1;
			sInven_Effect[i].InvenFace.width = TempSize;
			sInven_Effect[i].InvenFace.height = TempSize;
			sInven_Effect[i].Speed.y = rand() % 12 + 3;

			if (Kind == SIN_EFFECT_SHOW_GYUNGFUM)
			{
				sInven_Effect[i].InvenFace.MatNum = MatInvenParticle[4];
				sInven_Effect[i].InvenFace.r = 255;
				sInven_Effect[i].InvenFace.g = 255;
				sInven_Effect[i].InvenFace.b = 255;
				sInven_Effect[i].InvenFace.Transparency = rand() % 55 + 200;
				sInven_Effect[i].FadeType = 1;
				if (sInven_Effect[i].InvenFace.width > 5)
				{
					sInven_Effect[i].InvenFace.width -= 2;
					sInven_Effect[i].InvenFace.height -= 2;

				}
				if (sInven_Effect[i].InvenFace.width < 5)
					memset(&sInven_Effect[i], 0, sizeof(sINVENTORY_EFFECT));
			}
			else
			{
				sInven_Effect[i].InvenFace.MatNum = MatInvenParticle[0];
				sInven_Effect[i].InvenFace.r = 255;
				sInven_Effect[i].InvenFace.g = 255;
				sInven_Effect[i].InvenFace.b = 255;
				sInven_Effect[i].InvenFace.Transparency = rand() % 55 + 200;
				sInven_Effect[i].FadeType = 1;
			}
			if (Kind == 1)
			{
				for (k = 0; k < MAX_INVEN_PARTICLE; k++)
				{
					if (!sInven_Effect[k].Time)
					{
						Count++;
						if (Count > 2)
						{
							Count = 0;
							break;
						}
						memcpy(&sInven_Effect[k], &sInven_Effect[i], sizeof(sINVENTORY_EFFECT));
					}
				}
			}
			break;
		}
	}

	return TRUE;
}

DWORD dwInvenParticleMoveTime = 0;

int cINVENTORY::MoveInvenParticle()
{
	dwInvenParticleMoveTime++;
	if (dwInvenParticleMoveTime <= 5)return FALSE;
	dwInvenParticleMoveTime = 0;

	int i;
	for (i = 0; i < MAX_INVEN_PARTICLE; i++)
	{
		if (sInven_Effect[i].Time)
		{
			sInven_Effect[i].Time++;
			sInven_Effect[i].InvenFace.y -= sInven_Effect[i].Speed.y;

			if (sInven_Effect[i].FadeType == 1)
				sInven_Effect[i].InvenFace.Transparency += 14;
			if (sInven_Effect[i].FadeType == 2)
				sInven_Effect[i].InvenFace.Transparency -= 30;

			if (sInven_Effect[i].InvenFace.Transparency >= 255)
				sInven_Effect[i].FadeType = 2;

			if (sInven_Effect[i].InvenFace.Transparency <= 0)
				sInven_Effect[i].Time = 0;

			if (sInven_Effect[i].Kind != SIN_EFFECT_SHOW_GYUNGFUM)
			{
				if ((sInven_Effect[i].Time % 5) == 0)
				{
					sInven_Effect[i].AniCount++;
					if (sInven_Effect[i].AniCount > 3)
						sInven_Effect[i].AniCount = 0;
					sInven_Effect[i].InvenFace.MatNum = MatInvenParticle[sInven_Effect[i].AniCount];
				}
			}

			if (sInven_Effect[i].InvenFace.Transparency <= 0)
				sInven_Effect[i].Time = 0;
		}
	}

	return TRUE;
}
int cINVENTORY::sinDrawInvenTexImage(smFACE2D *Face)
{
	D3DTLVERTEX9 tlVertex[4];
	int cnt;
	int x, y;

	x = Face->x;
	y = Face->y;
	dsGetDrawOffset(&x, &y);

	for (cnt = 0; cnt < 4; cnt++)
	{
		tlVertex[cnt].rhw = 1;
		tlVertex[cnt].color = D3DCOLOR_RGBA(Face->r, Face->g, Face->b, Face->Transparency);
		tlVertex[cnt].specular = D3DCOLOR_RGBA(0, 0, 0, 0);
		tlVertex[cnt].sz = 0;
	}

	tlVertex[0].sx = (float)x;
	tlVertex[0].sy = (float)y;
	tlVertex[0].tu = 0;
	tlVertex[0].tv = 0;

	tlVertex[1].sx = (float)x + (float)Face->width;
	tlVertex[1].sy = (float)y;
	tlVertex[1].tu = 1;
	tlVertex[1].tv = 0;

	tlVertex[2].sx = (float)x;
	tlVertex[2].sy = (float)y + (float)Face->height;
	tlVertex[2].tu = 0;
	tlVertex[2].tv = 1;

	tlVertex[3].sx = ((float)x + (float)Face->width);
	tlVertex[3].sy = ((float)y + (float)Face->height);
	tlVertex[3].tu = 1;
	tlVertex[3].tv = 1;

	psSetRenderState(0);

	if (smMaterial[Face->MatNum].smTexture[0] != NULL && smMaterial[Face->MatNum].smTexture[0]->m_pTexture != NULL)
		psDraw2DImage(smMaterial[Face->MatNum].smTexture[0]->m_pTexture, tlVertex);

	return TRUE;
}
int cINVENTORY::CheckSetEmptyArea(ItemData *pItem)
{
	int cntx, cnty;
	int cx, cy;

	RECT	rect = { 0,0,0,0 };
	int		flag = 0;

	cx = (22 * INVENTORY_BOX_ROW) - pItem->iWidth;
	cy = (22 * INVENTORY_BOX_COL) - pItem->iHeight;

	for (cntx = StartX; cntx <= StartX + cx; cntx += 22)
	{
		for (cnty = StartY; cnty <= StartY + cy; cnty += 22)
		{
			flag = 0;

			for (int i = 0; i < INVENTORY_MAXITEM; i++)
			{
				if (InvenItem[i].bValid)
				{
					rect.left   = InvenItem[i].iPlaceX;
					rect.right  = InvenItem[i].iPlaceX + InvenItem[i].iWidth;
					rect.top    = InvenItem[i].iPlaceY;
					rect.bottom = InvenItem[i].iPlaceY + InvenItem[i].iHeight;

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
int cINVENTORY::ResetInvenItemToServer(DWORD CODE, DWORD Head, DWORD CheckSum, DWORD Time)
{
	int i = 0;
	for (i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].bValid)
		{
			if (InvenItem[i].sBaseItemID.ToInt() == CODE && InvenItem[i].sItem.iChk1 == Head && InvenItem[i].sItem.iChk2 == CheckSum)
			{
				InvenItem[i].sItem.dwTime = Time;
				return TRUE;
			}

		}
		if (InvenItemTemp[i].bValid)
		{
			if (InvenItemTemp[i].sBaseItemID.ToInt() == CODE && InvenItemTemp[i].sItem.iChk1 == Head && InvenItemTemp[i].sItem.iChk2 == CheckSum)
			{
				InvenItemTemp[i].sItem.dwTime = Time;
				return TRUE;
			}
		}
	}
	return FALSE;
}
int cINVENTORY::DeleteInvenItemToServer(DWORD CODE, DWORD Head, DWORD CheckSum)
{
	if (MouseItem.bValid && MouseItem.sBaseItemID.ToInt() == CODE && MouseItem.sItem.iChk1 == Head && MouseItem.sItem.iChk2 == CheckSum)
		MouseItem.bValid = 0;

	int i = 0;
	for (i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].bValid)
		{
			if (InvenItem[i].sBaseItemID.ToInt() == CODE && InvenItem[i].sItem.iChk1 == Head && InvenItem[i].sItem.iChk2 == CheckSum)
			{
				InvenItem[i].bValid = 0;
				if (InvenItem[i].iItemSlot)
				{
					if (InvenItem[i].iItemSlotFlag == ITEMSLOTFLAG_LeftRightHand && (InvenItem[i].sBaseItemID.ToInt() & sinITEM_MASK2) != sinWD1)
					{
						if (InvenItem[i].iItemSlot == 1)
						{
							if (InvenItem[i].sBaseItemID.ToInt() != InvenItem[sInven[1].ItemIndex - 1].sBaseItemID.ToInt())
							{
								InvenItem[sInven[1].ItemIndex - 1].bValid = 0;
								InvenItem[i].bValid = 0;
								sInven[1].ItemIndex = 0;
								sInven[0].ItemIndex = 0;
								if (InvenItem[i].iVisibleItemType)
									sinSetCharItem(InvenItem[i].sBaseItemID.ToInt(), InvenItem[i].iVisibleItemType, FALSE);

							}
						}
						if (InvenItem[i].iItemSlot == 2)
						{
							if (InvenItem[i].sBaseItemID.ToInt() != InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt())
							{
								InvenItem[sInven[0].ItemIndex - 1].bValid = 0;
								InvenItem[i].bValid = 0;
								sInven[0].ItemIndex = 0;
								sInven[1].ItemIndex = 0;
								if (InvenItem[i].iVisibleItemType)
									sinSetCharItem(InvenItem[i].sBaseItemID.ToInt(), InvenItem[i].iVisibleItemType, FALSE);
							}
						}
					}
					sInven[InvenItem[i].iItemSlot - 1].ItemIndex = 0;
					if (InvenItem[i].iVisibleItemType)
						sinSetCharItem(InvenItem[i].sBaseItemID.ToInt(), InvenItem[i].iVisibleItemType, FALSE);

				}
				ReFormInvenItem();
				ReformCharForm();
				ReFormPotionNum();
				SetItemToChar();
				break;
			}
		}
		if (InvenItemTemp[i].bValid)
		{
			if (InvenItemTemp[i].sBaseItemID.ToInt() == CODE && InvenItemTemp[i].sItem.iChk1 == Head && InvenItemTemp[i].sItem.iChk2 == CheckSum)
			{
				InvenItemTemp[i].bValid = 0;
				ReFormInvenItem();
				ReformCharForm();
				ReFormPotionNum();
				SetItemToChar();
				break;
			}
		}
	}
	if (!sInven[0].ItemIndex)
	{
		if (sInven[1].ItemIndex)
		{
			if (InvenItem[sInven[1].ItemIndex - 1].bValid)
			{
				if (InvenItem[sInven[1].ItemIndex - 1].iItemSlotFlag == ITEMSLOTFLAG_LeftRightHand && (InvenItem[sInven[1].ItemIndex - 1].sBaseItemID.ToInt() & sinITEM_MASK2) != sinWD1)
				{
					if (!InvenItem[sInven[1].ItemIndex - 1].sItem.iChk1)
					{
						InvenItem[sInven[1].ItemIndex - 1].bValid = 0;
						sInven[1].ItemIndex = 0;
						ReFormInvenItem();
						ReformCharForm();
						ReFormPotionNum();
						SetItemToChar();
					}
				}
			}
		}
	}
	cInvenTory.CheckWeight();
	return TRUE;
}

int cINVENTORY::HackCharStateCheck(CharacterData *pChar_Info, CharacterData *desChar_Info)
{
	int HackFlag = 0;

	if (pChar_Info->iMinDamage < desChar_Info->iMinDamage)
		HackFlag = 1;
	if (pChar_Info->iMaxDamage < desChar_Info->iMaxDamage)
		HackFlag = 1;
	if (pChar_Info->iDefenseRating < desChar_Info->iDefenseRating)
		HackFlag = 1;
	if (pChar_Info->iAbsorbRating < desChar_Info->iAbsorbRating)
		HackFlag = 1;
	if (pChar_Info->iAccuracy < desChar_Info->iAccuracy)
		HackFlag = 1;
	if (pChar_Info->iAttackSpeed < desChar_Info->iAttackSpeed)
		HackFlag = 1;
	if (pChar_Info->iBlockRating < desChar_Info->iBlockRating)
		HackFlag = 1;
	if (pChar_Info->iCritical < desChar_Info->iCritical)
		HackFlag = 1;
	if (pChar_Info->iAttackRange < desChar_Info->iAttackRange)
		HackFlag = 1;
	if (HackFlag)
	{
		smTRANS_COMMAND	smTransCommand;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.code = smTRANSCODE_FIX_ATTACK;
		smTransCommand.WParam = pChar_Info->iMinDamage;
		smTransCommand.LParam = pChar_Info->iDefenseRating;
		smTransCommand.SParam = (int)(pChar_Info->iAbsorbRating * 256);
		smTransCommand.EParam = 0;

		SENDPACKETL(&smTransCommand);

		return FALSE;
	}
	return TRUE;
}
int cINVENTORY::CheckResetInvenItem()
{
	RECT rect;
	for (int i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].bValid)
		{
			if (InvenItem[i].iItemSlot)
			{
				if (!sInven[InvenItem[i].iItemSlot - 1].ItemIndex ||
					sInven[InvenItem[i].iItemSlot - 1].ItemIndex - 1 != i)
					continue;
				rect.left	= sInven[InvenItem[i].iItemSlot - 1].Rect.left;
				rect.top	= sInven[InvenItem[i].iItemSlot - 1].Rect.top;
				rect.right	= sInven[InvenItem[i].iItemSlot - 1].Rect.right;
				rect.bottom = sInven[InvenItem[i].iItemSlot - 1].Rect.bottom;

				if (InvenItem[i].iPlaceX < rect.left ||
					InvenItem[i].iPlaceY < rect.top ||
					InvenItem[i].iPlaceX + InvenItem[i].iWidth > rect.right + 2 ||
					InvenItem[i].iPlaceY + InvenItem[i].iHeight > rect.bottom + 2)
				{

					InvenItem[i].iPlaceX = rect.left + (((rect.right - rect.left) - InvenItem[i].iWidth) / 2);
					InvenItem[i].iPlaceY = rect.top + (((rect.bottom - rect.top) - InvenItem[i].iHeight) / 2);
					ReFormInvenItem();
				}
			}

		}
		if (InvenItemTemp[i].bValid)
		{
			if (InvenItemTemp[i].iItemSlot)
			{
				rect.left = sInven[InvenItemTemp[i].iItemSlot - 1].Rect.left;
				rect.top = sInven[InvenItemTemp[i].iItemSlot - 1].Rect.top;
				rect.right = sInven[InvenItemTemp[i].iItemSlot - 1].Rect.right;
				rect.bottom = sInven[InvenItemTemp[i].iItemSlot - 1].Rect.bottom;

				if (InvenItemTemp[i].iPlaceX < rect.left ||
					InvenItemTemp[i].iPlaceY < rect.top ||
					InvenItemTemp[i].iPlaceX + InvenItemTemp[i].iWidth > rect.right + 2 ||
					InvenItemTemp[i].iPlaceY + InvenItemTemp[i].iHeight > rect.bottom + 2)
				{
					InvenItemTemp[i].iPlaceX = rect.left + (((rect.right - rect.left) - InvenItemTemp[i].iWidth) / 2);
					InvenItemTemp[i].iPlaceY = rect.top + (((rect.bottom - rect.top) - InvenItemTemp[i].iHeight) / 2);
					ReFormInvenItem();
				}
			}
		}
	}
	return TRUE;
}
int cINVENTORY::SearchItemCode(DWORD CODE, int KindFlag)
{
	int ItemCount = 0;
	if (CODE)
	{
		for (int i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItem[i].bValid)
			{
				if (InvenItem[i].sBaseItemID.ToInt() == CODE)
					ItemCount++;
			}
			if (InvenItemTemp[i].bValid)
			{
				if (InvenItemTemp[i].sBaseItemID.ToInt() == CODE)
					ItemCount++;
			}
		}
		return ItemCount;
	}

	if (KindFlag)
	{
		for (int i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItem[i].bValid)
			{
				if (InvenItem[i].sItem.eCraftType == KindFlag)
					ItemCount++;
			}
			if (InvenItemTemp[i].bValid)
			{
				if (InvenItemTemp[i].sItem.eCraftType == KindFlag)
					ItemCount++;
			}
		}
		return ItemCount;
	}
	return FALSE;
}
int cINVENTORY::CheckDamage()
{
	int Damage[2] = { 0,0 };
	int Critical = 0;
	int SendDamage[2] = { 0,0 };
	int SendCritical = 0;
	int RealDamage[2] = { 0,0 };
	int RealSendCritical = 0;

	int i = 0, j = 0, k = 0, t = 0;

	DWORD WeaponCode[9] = { sinWA1,sinWS1,sinWP1,sinWS2,sinWT1,sinWM1,sinWM1,sinWD1,sinWN1 };
	int   CharCode[9] = { CHARACTERCLASS_Fighter,CHARACTERCLASS_Archer,CHARACTERCLASS_Pikeman,CHARACTERCLASS_Knight,CHARACTERCLASS_Atalanta,CHARACTERCLASS_Priestess,CHARACTERCLASS_Magician,CHARACTERCLASS_Assassin,CHARACTERCLASS_Shaman };

	ItemData *pItem = 0;
	pItem = new ItemData;
	for (i = 0; i < INVENTORY_MAXITEM * 2; i++)
	{
		Damage[0] = 0; Damage[1] = 0; Critical = 0;
		if (i < 100)
		{
			if (!InvenItem[i].bValid)
				continue;
			if (InvenItem[i].iNotUse)
				continue;
			memcpy(pItem, &InvenItem[i], sizeof(ItemData));
		}
		else
		{
			if (!InvenItemTemp[i - 100].bValid)
				continue;
			if (InvenItemTemp[i - 100].iNotUse)
				continue;
			memcpy(pItem, &InvenItemTemp[i - 100], sizeof(ItemData));
		}
		if (pItem->sItem.sDamage.sMin || pItem->sItem.sDamage.sMax || pItem->sItem.iCritical)
		{
			Damage[0] += pItem->sItem.sDamage.sMin;
			Damage[1] += pItem->sItem.sDamage.sMax;

			Critical += pItem->sItem.iCritical;

			if ((sinDamageFunction[0] == 1 && (pItem->iItemWpnDmg == 1 || pItem->iItemWpnDmg == 3)))
			{
				SendDamage[0] = 1 + (Damage[0] * (sinChar->iStrength + 130) / 130) + ((sinChar->iTalent + sinChar->iAgility) / 40) + ((Damage[0] + Damage[1]) / 16);
				SendDamage[1] = 3 + (Damage[1] * (sinChar->iStrength + 130) / 130) + ((sinChar->iTalent + sinChar->iAgility) / 40);
			}

			if ((sinDamageFunction[0] == 2 && (pItem->iItemWpnDmg == 1 || pItem->iItemWpnDmg == 3)))
			{
				SendDamage[0] = 1 + (Damage[0] * (sinChar->iStrength + 150) / 150) + ((sinChar->iTalent + sinChar->iAgility) / 45) + ((Damage[0] + Damage[1]) / 16);
				SendDamage[1] = 3 + (Damage[1] * (sinChar->iStrength + 150) / 150) + ((sinChar->iTalent + sinChar->iAgility) / 45);
			}
			if ((sinDamageFunction[0] == 3 && (pItem->iItemWpnDmg == 1 || pItem->iItemWpnDmg == 3)))
			{
				SendDamage[0] = 1 + (Damage[0] * (sinChar->iStrength + 190) / 190) + ((sinChar->iTalent + sinChar->iAgility) / 50) + ((Damage[0] + Damage[1]) / 16);
				SendDamage[1] = 3 + (Damage[1] * (sinChar->iStrength + 190) / 190) + ((sinChar->iTalent + sinChar->iAgility) / 50);
			}
			if (sinDamageFunction[1] == 1 && pItem->iItemWpnDmg == 2)
			{
				SendDamage[0] = 1 + (Damage[0] * (sinChar->iAgility + 130) / 130) + ((sinChar->iTalent + sinChar->iStrength) / 40) + ((Damage[0] + Damage[1]) / 16);
				SendDamage[1] = 3 + (Damage[1] * (sinChar->iAgility + 130) / 130) + ((sinChar->iTalent + sinChar->iStrength) / 40);
			}

			if (sinDamageFunction[1] == 2 && pItem->iItemWpnDmg == 2)
			{
				SendDamage[0] = 1 + (Damage[0] * (sinChar->iAgility + 190) / 190) + ((sinChar->iTalent + sinChar->iStrength) / 50) + ((Damage[0] + Damage[1]) / 16);
				SendDamage[1] = 3 + (Damage[1] * (sinChar->iAgility + 190) / 190) + ((sinChar->iTalent + sinChar->iStrength) / 50);
			}
			if (sinDamageFunction[2] == 1 && pItem->iItemWpnDmg == 3)
			{
				SendDamage[0] = 1 + (Damage[0] * (sinChar->iSpirit + 150) / 150) + ((sinChar->iTalent) / 30) + ((Damage[0] + Damage[1]) / 16);
				SendDamage[1] = 3 + (Damage[1] * (sinChar->iSpirit + 150) / 150) + ((sinChar->iTalent) / 30);
			}
			if (sinDamageFunction[2] == 2 && pItem->iItemWpnDmg == 3)
			{
				SendDamage[0] = 1 + (Damage[0] * (sinChar->iSpirit + 180) / 180) + ((sinChar->iTalent) / 30);
				SendDamage[1] = 2 + (Damage[1] * (sinChar->iSpirit + 180) / 180) + ((sinChar->iTalent) / 25);
			}
			if (sinDamageFunction[2] == 2 && pItem->iItemWpnDmg == 3)
			{
				SendDamage[0] = 1 + (Damage[0] * (sinChar->iSpirit + 170) / 170) + ((sinChar->iTalent) / 30) + ((Damage[0] + Damage[1]) / 16);
				SendDamage[1] = 3 + (Damage[1] * (sinChar->iSpirit + 170) / 170) + ((sinChar->iTalent) / 30);
			}

			for (j = 0; j < 9; j++)
			{
				if (CharCode[j] == sinChar->iClass)
				{
					if (WeaponCode[j] == (pItem->sItem.sItemID.ToItemType()))
					{
						SendDamage[0] += sinChar->iLevel / 6;
						SendDamage[1] += sinChar->iLevel / 6;
					}
				}
			}
			if (sinChar->iClass == SIN_CHAR_MECANICIAN)
			{
				if (sinChar->iFlag == pItem->sItem.eSpecialization)
				{
					SendDamage[0] += sinChar->iLevel / 6;
					SendDamage[1] += sinChar->iLevel / 6;
				}
			}

			for (k = 1; k < MAX_USESKILL; k++)
			{
				if (sinSkill.UseSkill[k].Flag && sinSkill.UseSkill[k].Point)
				{
					for (t = 0; t < 10; t++)
					{
						switch (sinSkill.UseSkill[k].CODE)
						{
						case SKILL_MELEE_MASTERY:
							if (sinSkill.UseSkill[k].Skill_Info.UseWeaponCode[t] == (pItem->sItem.sItemID.ToItemType()))
							{
								SendDamage[0] += (int)(((float)Melee_Mastery_DamagePercent[sinSkill.UseSkill[k].Point - 1] / 100)*pItem->sItem.sDamage.sMin);
								SendDamage[1] += (int)(((float)Melee_Mastery_DamagePercent[sinSkill.UseSkill[k].Point - 1] / 100)*pItem->sItem.sDamage.sMax);
							}
							break;
						case SKILL_SHOOTING_MASTERY:
							if (sinSkill.UseSkill[k].Skill_Info.UseWeaponCode[t] == (pItem->sItem.sItemID.ToItemType()))
							{
								SendDamage[0] += (int)(((float)S_Mastery_DamagePercent[sinSkill.UseSkill[k].Point - 1] / 100)*pItem->sItem.sDamage.sMin);
								SendDamage[1] += (int)(((float)S_Mastery_DamagePercent[sinSkill.UseSkill[k].Point - 1] / 100)*pItem->sItem.sDamage.sMax);
							}
							break;
						case SKILL_THROWING_MASTERY:
							if (sinSkill.UseSkill[k].Skill_Info.UseWeaponCode[t] == (pItem->sItem.sItemID.ToItemType()))
							{
								SendDamage[0] += (int)(((float)T_Mastery_Damage[sinSkill.UseSkill[k].Point - 1] / 100)*pItem->sItem.sDamage.sMin);
								SendDamage[1] += (int)(((float)T_Mastery_Damage[sinSkill.UseSkill[k].Point - 1] / 100)*pItem->sItem.sDamage.sMax);
							}
							break;
						case SKILL_CRITICAL_MASTERY:
							if (sinSkill.UseSkill[k].Skill_Info.UseWeaponCode[t] == (pItem->sItem.sItemID.ToItemType()))
								Critical += Critical_Mastery_Critical[sinSkill.UseSkill[k].Point - 1];
							break;
						case SKILL_SWORD_MASTERY:
							if (sinSkill.UseSkill[k].Skill_Info.UseWeaponCode[t] == (pItem->sItem.sItemID.ToItemType()))
							{
								SendDamage[0] += (int)(((float)Sword_Mastery_DamagePercent[sinSkill.UseSkill[k].Point - 1] / 100)*pItem->sItem.sDamage.sMin);
								SendDamage[1] += (int)(((float)Sword_Mastery_DamagePercent[sinSkill.UseSkill[k].Point - 1] / 100)*pItem->sItem.sDamage.sMax);
							}
							break;
						case SKILL_SWORDMASTERY:
							if (sinSkill.UseSkill[k].Skill_Info.UseWeaponCode[t] == (pItem->sItem.sItemID.ToItemType()))
							{
								SendDamage[0] += (int)(((float)Sword_Mastery_Damage[sinSkill.UseSkill[k].Point - 1] / 100)*pItem->sItem.sDamage.sMin);
								SendDamage[1] += (int)(((float)Sword_Mastery_Damage[sinSkill.UseSkill[k].Point - 1] / 100)*pItem->sItem.sDamage.sMax);
							}
							break;
							//¹¥»÷´óÊ¦
						case SKILL_ATTACK_MASTERY:
							if (sinSkill.UseSkill[k].Skill_Info.UseWeaponCode[t] == (pItem->sItem.sItemID.ToItemType()))
							{
								SendDamage[0] += (int)(((float)Blade_Mastery_Attack[sinSkill.UseSkill[k].Point - 1] / 100)*pItem->sItem.sDamage.sMin);
								SendDamage[1] += (int)(((float)Blade_Mastery_Attack[sinSkill.UseSkill[k].Point - 1] / 100)*pItem->sItem.sDamage.sMax);
							}
							break;
							//ÖÂÃü´óÊ¦
						case SKILL_FATAL_MASTERY:
							if (sinSkill.UseSkill[k].Skill_Info.UseWeaponCode[t] == (pItem->sItem.sItemID.ToItemType()))
								Critical += Fatal_Mastery_Critical[sinSkill.UseSkill[k].Point - 1];
							break;
						}
					}
				}
			}
			if (sinChar->iFlag == pItem->sItem.eSpecialization)
			{
				if (pItem->sItem.sSpecData.iSpecAttackPowerDiv)
					SendDamage[1] += (sinChar->iLevel / pItem->sItem.sSpecData.iSpecAttackPowerDiv);
				if (pItem->sItem.sSpecData.iSpecCritical)
					Critical += pItem->sItem.sSpecData.iSpecCritical;
			}
			SendCritical = Critical;
			SendDamage[0] += 1;
			SendDamage[1] += 1;

			if (RealDamage[0] < SendDamage[0])
				RealDamage[0] = SendDamage[0];
			if (RealDamage[1] < SendDamage[1])
				RealDamage[1] = SendDamage[1];
			if (RealSendCritical < SendCritical)
				RealSendCritical = SendCritical;
		}
	}
	SendMaxDamageToServer(RealDamage[0], RealDamage[1], RealSendCritical);
	return TRUE;
}

int cINVENTORY::ClearQuestItem()
{
	ItemData *pItem = 0;
	for (int i = 0; i < INVENTORY_MAXITEM * 2; i++)
	{
		if (i < 100)
		{
			if (!InvenItem[i].bValid)
				continue;
			pItem = &InvenItem[i];
		}
		else
		{
			if (!InvenItemTemp[i - 100].bValid)
				continue;
			pItem = &InvenItemTemp[i - 100];
		}
		if ((pItem->sItem.sItemID.ToItemType()) == sinMA2)
			pItem->bValid = 0;
	}
	cInvenTory.ReFormInvenItem();
	ResetInvenItemCode();
	return TRUE;
}
int cINVENTORY::DeleteCoupleRing()
{
	ItemData *pItem = 0;
	for (int i = 0; i < INVENTORY_MAXITEM * 2; i++)
	{
		if (i < 100)
		{
			if (!InvenItem[i].bValid)
				continue;
			pItem = &InvenItem[i];
		}
		else
		{
			if (!InvenItemTemp[i - 100].bValid)
				continue;
			pItem = &InvenItemTemp[i - 100];
		}
		if (pItem->sItem.sItemID.ToInt() == (sinSP1 | sin16))
		{
			pItem->bValid = 0;
			break;
		}
	}
	cInvenTory.ReFormInvenItem();
	ResetInvenItemCode();
	return TRUE;
}
int cINVENTORY::RecvLinkCore(Item *pItemInfo)
{
	Item *pItemInfo2 = 0;
	for (int i = 0; i < INVENTORY_MAXITEM * 2; i++)
	{
		if (i < 100)
		{
			if (!InvenItem[i].bValid)
				continue;
			pItemInfo2 = &InvenItem[i].sItem;
		}
		else
		{
			if (!InvenItemTemp[i - 100].bValid)
				continue;
			pItemInfo2 = &InvenItemTemp[i - 100].sItem;
		}
		if (pItemInfo->BackUpChkSum == pItemInfo2->BackUpChkSum && pItemInfo->BackUpKey == pItemInfo2->BackUpKey && pItemInfo->sItemID.ToInt() == pItemInfo2->sItemID.ToInt())
		{
			memcpy(pItemInfo2, pItemInfo, sizeof(Item));
			CheckWeight();
			ReFormInvenItem();
			return TRUE;
		}
	}
	return FALSE;
}
int sinMousePotionNum[4] = { 0,0,0,0 };
int ChecMousekPotionNum[4] = { 0,0,0,0 };

int cINVENTORY::CheckMousePotionNumForm()
{
	for (int k = 0; k < 4; k++)
		ChecMousekPotionNum[k] = 0;

	if (MouseItem.bValid)
	{
		if (MouseItem.iItemSlotFlag == ITEMSLOTFLAG_Potion)
		{
			switch (MouseItem.sItem.sItemID.ToItemIndex())
			{
			case sin01:
				ChecMousekPotionNum[0] += MouseItem.sItem.iPotionCount;
				break;
			case sin02:
				ChecMousekPotionNum[1] += MouseItem.sItem.iPotionCount;
				break;
			case sin03:
				ChecMousekPotionNum[2] += MouseItem.sItem.iPotionCount;
				break;
			case sin04:
				ChecMousekPotionNum[3] += MouseItem.sItem.iPotionCount;
				break;
			}
		}
	}
	for (int j = 0; j < 4; j++)
	{
		if (ChecMousekPotionNum[j] != sinMousePotionNum[j])
			SendSetHackUser2(1510, j);
	}

	return TRUE;
}

int cINVENTORY::ReFormMousePotionNum()
{
	for (int j = 0; j < 4; j++)
		sinMousePotionNum[j] = 0;
	if (MouseItem.bValid)
	{
		if (MouseItem.iItemSlotFlag == ITEMSLOTFLAG_Potion)
		{
			switch (MouseItem.sItem.sItemID.ToItemIndex())
			{
			case sin01:
				sinMousePotionNum[0] += MouseItem.sItem.iPotionCount;

				break;
			case sin02:
				sinMousePotionNum[1] += MouseItem.sItem.iPotionCount;

				break;
			case sin03:
				sinMousePotionNum[2] += MouseItem.sItem.iPotionCount;

				break;
			case sin04:
				sinMousePotionNum[3] += MouseItem.sItem.iPotionCount;

				break;
			}
		}
	}
	return TRUE;
}
int cINVENTORY::SetUnionCoreEffect(int x, int y)
{
	for (int i = 0; i < 10; i++)
	{
		if (!UnionCore_Effect_Bone[i].Flag)
		{
			UnionCore_Effect_Bone[i].DesPosi.x = x + 22;
			UnionCore_Effect_Bone[i].DesPosi.y = y;
			UnionCore_Effect_Bone[i].Flag = 1;
			UnionCore_Effect_Bone[i].Posi.y -= 350;
			UnionCore_Effect_Bone[i].InvenFace.MatNum = *(int *)AssaSearchRes("par2.tga", SMMAT_BLEND_ALPHA);
			UnionCore_Effect_Bone[i].Max_Time = 100;
			UnionCore_Effect_Bone[i].InvenFace.r = 255;
			UnionCore_Effect_Bone[i].InvenFace.g = 255;
			UnionCore_Effect_Bone[i].InvenFace.b = 255;
			UnionCore_Effect_Bone[i].InvenFace.Transparency = 255;
			UnionCore_Effect_Bone[i].InvenFace.height = 32;
			UnionCore_Effect_Bone[i].InvenFace.width = 32;
			UnionCore_Effect_Bone[i].InvenFace.TexRect = sinTexRect;
			UnionCore_Effect_Bone[i].Flag = 1;
		}
	}
	return TRUE;
}

int cINVENTORY::UnionCoreParticleProcess()
{
	int i = 0;

	for (i = 0; i < 10; i++)
	{
		if (UnionCore_Effect_Bone[i].Flag)
		{
			UnionCore_Effect_Bone[i].Time += GetRandomPos(1, 3);
			UnionCore_Effect_Bone[i].Posi.y += 30;
			UnionCore_Effect_Bone[i].InvenFace.y = UnionCore_Effect_Bone[i].Posi.y;
			UnionCore_Effect_Bone[i].Posi.x = UnionCore_Effect_Bone[i].DesPosi.x - 5;
			UnionCore_Effect_Bone[i].InvenFace.x = UnionCore_Effect_Bone[i].Posi.x;
			if (UnionCore_Effect_Bone[i].Posi.y <= UnionCore_Effect_Bone[i].DesPosi.y - 10)
				UnionCoreParticle(UnionCore_Effect_Bone[i].Posi.x, UnionCore_Effect_Bone[i].Posi.y);

			if (UnionCore_Effect_Bone[i].Posi.y >= UnionCore_Effect_Bone[i].DesPosi.y)
			{
				UnionCoreParticle2(UnionCore_Effect_Bone[i].InvenFace.x, UnionCore_Effect_Bone[i].InvenFace.y);
				memset(&UnionCore_Effect_Bone[i], 0, sizeof(sINVENTORY_EFFECT));
			}
		}
	}

	for (i = 0; i < 100; i++)
	{
		if (UnionCore_Effect[i].Flag)
		{
			UnionCore_Effect[i].Time++;
			if (UnionCore_Effect[i].Direction == 1)
				UnionCore_Effect[i].InvenFace.x -= GetRandomPos(0, 1);
			else
				UnionCore_Effect[i].InvenFace.x += GetRandomPos(0, 1);
			if (UnionCore_Effect[i].Time >= UnionCore_Effect[i].Max_Time)
				memset(&UnionCore_Effect[i], 0, sizeof(sINVENTORY_EFFECT));
		}
	}


	for (i = 0; i < 50; i++)
	{
		if (UnionCore_Effect_Bomb[i].Flag)
		{
			UnionCore_Effect_Bomb[i].Time++;
			if (UnionCore_Effect_Bomb[i].Time >= UnionCore_Effect_Bomb[i].Max_Time)
				memset(&UnionCore_Effect_Bomb[i], 0, sizeof(sINVENTORY_EFFECT));
		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (sUCore_Effect[i].Flag)
		{
			sUCore_Effect[i].Time++;
			if (sUCore_Effect[i].Time > 0)
			{
				sUCore_Effect[i].h += 2;
				sUCore_Effect[i].w += 2;
				sUCore_Effect[i].x--;
				sUCore_Effect[i].y--;
				sUCore_Effect[i].Alpha -= 6;
			}

			if (sUCore_Effect[i].Time > sUCore_Effect[i].Max_Time)
				memset(&sUCore_Effect[i], 0, sizeof(sUNIONCORE_EFFECT));
		}
	}

	return TRUE;
}

int cINVENTORY::UnionCoreParticle(int x, int y)
{
	for (int i = 0; i < 100; i++)
	{
		if (!UnionCore_Effect[i].Flag)
		{
			UnionCore_Effect[i].InvenFace.MatNum = *(int *)AssaSearchRes("par2.tga", SMMAT_BLEND_ALPHA);
			UnionCore_Effect[i].InvenFace.x = x + GetRandomPos(-3, 3);
			UnionCore_Effect[i].InvenFace.y = y + GetRandomPos(-15, 15);
			UnionCore_Effect[i].Max_Time = GetRandomPos(8, 15);
			UnionCore_Effect[i].InvenFace.r = 255;
			UnionCore_Effect[i].InvenFace.g = 255;
			UnionCore_Effect[i].InvenFace.b = 255;
			UnionCore_Effect[i].InvenFace.Transparency = 255;
			UnionCore_Effect[i].InvenFace.height = GetRandomPos(10, 11);
			UnionCore_Effect[i].InvenFace.width = UnionCore_Effect[i].InvenFace.height;
			UnionCore_Effect[i].InvenFace.TexRect = sinTexRect;
			UnionCore_Effect[i].Flag = 1;
			if ((i % 2) == 0)
				UnionCore_Effect[i].Direction = 1;
			else UnionCore_Effect[i].Direction = -1;

			break;
		}
	}
	return TRUE;
}
int cINVENTORY::UnionCoreParticle2(int x, int y, int Flag)
{
	int Count = 0;
	for (int i = 0; i < 10; i++)
	{
		if (!sUCore_Effect[i].Flag)
		{
			if (Flag)
				sUCore_Effect[i].MatNum = MatInterEffectAging[0];
			else
				sUCore_Effect[i].MatNum = MatUnionCoreEffect;

			sUCore_Effect[i].x = x + 12;
			sUCore_Effect[i].y = y;
			sUCore_Effect[i].Max_Time = 40;
			sUCore_Effect[i].Alpha = 255;
			sUCore_Effect[i].w = 20;
			sUCore_Effect[i].h = 20;
			sUCore_Effect[i].Flag = 1;
			Count++;
			if (Count > 1)
				break;
		}
	}
	return TRUE;
}
int cINVENTORY::CheckInvenEmpty(ItemData *pItem)
{
	if (pItem->sBaseItemID.ToInt() == (sinGG1 | sin01) || pItem->sBaseItemID.ToInt() == (sinGG1 | sin02))
		return TRUE;

	char szFilePath[256];

	ItemData * pItemData = ITEMHANDLE->GetItemDataByID(pItem->sBaseItemID.ToInt());

	if (pItemData)
	{
		wsprintf(szFilePath, "Image\\sinImage\\Items\\%s\\it%s.bmp", pItemData->szCategory, pItemData->szInventoryName);
		if (!pItemData->pcTempInventoryTexture)
			pItemData->pcTempInventoryTexture = LoadDibSurfaceOffscreen(szFilePath);
		pItem->pcInventoryTexture = pItemData->pcTempInventoryTexture;
		pItem->iWidth = pItemData->iWidth;
		pItem->iHeight = pItemData->iHeight;
	}

	memcpy(&cTrade.CheckItem, &cInvenTory.InvenItem, sizeof(ItemData) * 100);
	if (cTrade.TradeCheckEmptyArea(pItem))
		return TRUE;
	else return FALSE;
}
int cINVENTORY::LoadMoneyExpImage(ItemData *pItem)
{
	if (pItem->sBaseItemID.ToInt() == (sinGG1 | sin01))
	{
		if (!lpGold7)
			lpGold7 = LoadDibSurfaceOffscreen("image\\Sinimage\\MessageBox\\Gold7.bmp");
		pItem->pcInventoryTexture = lpGold7;

	}
	if (pItem->sBaseItemID.ToInt() == (sinGG1 | sin02))
	{
		if (!lpExp7)
			lpExp7 = LoadDibSurfaceOffscreen("image\\Sinimage\\MessageBox\\Exp7.bmp");
		pItem->pcInventoryTexture = lpExp7;

	}
	pItem->iWidth = 44;
	pItem->iHeight = 44;
	return TRUE;
}
int cINVENTORY::SetInvenToItemInfo(Item *pItemInfo)
{
	if (pItemInfo->sItemID.ToInt() == (sinGG1 | sin01))
	{
		CheckCharForm();
		sinPlusMoney(pItemInfo->iGold);
		ReformCharForm();
		SendSaveMoney();
		sinPlaySound(SIN_SOUND_COIN);
		return TRUE;
	}
	if (pItemInfo->sItemID.ToInt() == (sinGG1 | sin02))
	{
		AddExp(pItemInfo->iGold);
		sinPlaySound(SIN_SOUND_EAT_POTION2);
		return TRUE;

	}
	ItemData TempItem;
	if (LoadItemImage(pItemInfo, &TempItem))
	{
		if (cInvenTory.CheckRequireItemToSet(&TempItem))
		{
			if (!cInvenTory.AutoSetInvenItem(&TempItem, 1))
			{
				TempItem.bValid = 0;
				return FALSE;
			}
		}
	}
	return TRUE;
}
int cINVENTORY::sinWingQuestNpc()
{
	ItemData *pItem = 0;
	int   Index = 0;
	int   i = 0;

	WingItemQuestIndex = 0;
	memset(&sWingItem_Send, 0, sizeof(sCRAFTITEM_SERVER));

	for (i = 0; i < INVENTORY_MAXITEM * 2; i++)
	{
		if (i < 100)
		{
			if (!InvenItem[i].bValid)
				continue;
			pItem = &InvenItem[i];
		}
		else
		{
			if (!InvenItemTemp[i - 100].bValid)
				continue;
			pItem = &InvenItemTemp[i - 100];
		}
		switch (pItem->sItem.sItemID.ToInt())
		{
		case (sinQW1 | sin01):
			Index = 1;
			memcpy(&sWingItem_Send.DesCraftItem, pItem, sizeof(ItemData));

			break;
		case (sinQW1 | sin02):
			Index = 2;
			memcpy(&sWingItem_Send.DesCraftItem, pItem, sizeof(ItemData));

			break;
		case (sinQW1 | sin03):
			Index = 3;
			memcpy(&sWingItem_Send.DesCraftItem, pItem, sizeof(ItemData));
			break;
		case (sinQW1 | sin04):
			Index = 4;
			memcpy(&sWingItem_Send.DesCraftItem, pItem, sizeof(ItemData));
			break;
		case (sinQW1 | sin05):
			Index = 5;
			memcpy(&sWingItem_Send.DesCraftItem, pItem, sizeof(ItemData));
			break;
		case (sinQW1 | sin06):
			if (SETTINGHANDLE->Get().bDebugMode)
				if (WingItemQuestIndex = 1000)
					cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST_WING, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), WingQuestFilePath_b[6]);
			return FALSE;

			break;
		}
	}
	int CodeCount = 0;
	int ItemCount = 0;

	for (int j = 0; j < 6; j++)
	{
		if (sWingQuest[Index].NeedItemCode[j])
		{
			CodeCount++;
			for (i = 0; i < INVENTORY_MAXITEM * 2; i++)
			{
				if (i < 100)
				{
					if (!InvenItem[i].bValid)
						continue;
					pItem = &InvenItem[i];
				}
				else
				{
					if (!InvenItemTemp[i - 100].bValid)
						continue;
					pItem = &InvenItemTemp[i - 100];
				}
				if (sWingQuest[Index].NeedItemCode[j] == pItem->sItem.sItemID.ToInt())
				{
					sWingItem_Send.SheltomCode[ItemCount] = pItem->sItem.sItemID.ToInt();
					sWingItem_Send.Head[ItemCount] = pItem->sItem.iChk1;
					sWingItem_Send.CheckSum[ItemCount] = pItem->sItem.iChk2;
					ItemCount++;
					break;
				}
			}
		}
	}


	if (CodeCount == ItemCount && sinChar->iGold >= sWingQuest[Index].Money)
	{
		WingItemQuestIndex = Index;
		sWingItem_Send.Index = Index;
		sWingItem_Send.Money = sWingQuest[Index].Money;
		cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST_WING, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), WingQuestFilePath_b[Index]);
	}
	else
	{
		WingItemQuestIndex = 1000;
		cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST_WING, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), WingQuestFilePath_a[Index]);
	}

	return TRUE;
}
int cINVENTORY::CheckRequireItemToSet2(ItemData *pItem)
{
	int i = 0;

	int NotUseItemFlag = 0;

	if (pItem->sItem.iLevel > sinChar->iLevel)
		NotUseItemFlag = 1;
	if (pItem->sItem.iAgility > sinChar->iAgility)
		NotUseItemFlag = 1;
	if (pItem->sItem.iStrength > sinChar->iStrength)
		NotUseItemFlag = 1;
	if (pItem->sItem.iTalent > sinChar->iTalent)
		NotUseItemFlag = 1;
	if (pItem->sItem.iSpirit > sinChar->iSpirit)
		NotUseItemFlag = 1;
	if (pItem->sItem.iHealth > sinChar->iHealth)
		NotUseItemFlag = 1;
	if ((pItem->sItem.sItemID.ToItemType()) == sinFO1)
	{
		for (i = 0; i < 16; i++)
		{
			if ((pItem->sBaseItemID.ToInt()&sinITEM_MASK3) == SheltomCode2[i])
				break;
		}
		if (sinChar->iLevel < ForceOrbUseLevel[i][0] || sinChar->iLevel > ForceOrbUseLevel[i][1])
			NotUseItemFlag = 1;
		else
			NotUseItemFlag = 0;
	}

	if (NotUseItemFlag)
		return FALSE;
	return TRUE;
}
int cINVENTORY::CheckSpecialItemPosi()
{
	int j = 0;
	for (int i = 0; i < 84; i++)
	{
		if (InvenItem[i].bValid)
		{
			if (InvenItem[i].sItem.SpecialItemFlag[1] == ITEMCRAFTTYPE_Special)
			{
				for (j = 84; j < INVENTORY_MAXITEM; j++)
				{
					if (!InvenItem[j].bValid)
					{
						memcpy(&InvenItem[j], &InvenItem[i], sizeof(ItemData));
						ZeroMemory(&InvenItem[i], sizeof(ItemData));
					}
				}
			}
		}
		if (InvenItemTemp[i].bValid)
		{
			if (InvenItemTemp[i].sItem.SpecialItemFlag[1] == ITEMCRAFTTYPE_Special)
			{
				for (j = 84; j < INVENTORY_MAXITEM; j++)
				{
					if (!InvenItem[j].bValid)
					{
						memcpy(&InvenItem[j], &InvenItemTemp[i], sizeof(ItemData));
						ZeroMemory(&InvenItemTemp[i], sizeof(ItemData));
					}
				}
			}
		}
	}
	ReFormInvenItem();
	ReformCharForm();
	ReFormPotionNum();
	SetItemToChar();
	return TRUE;
}
int cINVENTORY::ChangeSpecialItem(int Flag)
{
	if (Flag == 1)
	{
		if (SpecialItemShowFlag)
			SpecialItemShowFlag = 0;
		else
			return FALSE;
	}
	else if (Flag == 2)
		SpecialItemShowFlag = 0;
	else
		SpecialItemShowFlag ^= 1;

	for (int i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].bValid)
		{
			if (SpecialItemShowFlag)
			{
				if (InvenItem[i].sItem.SpecialItemFlag[1] == ITEMCRAFTTYPE_Special)
				{
					if (InvenItem[i].iPlaceX > 10000)
						InvenItem[i].iPlaceX -= 10000;
				}
				else
				{
					if (!InvenItem[i].iItemSlot && InvenItem[i].iPlaceX < 10000)
						InvenItem[i].iPlaceX += 10000;
				}
			}
			else
			{
				if (InvenItem[i].sItem.SpecialItemFlag[1] == ITEMCRAFTTYPE_Special)
				{
					if (InvenItem[i].iPlaceX < 10000)
					{
						InvenItem[i].iPlaceX += 10000;
					}
				}
				else
				{
					if (!InvenItem[i].iItemSlot)
					{
						if (InvenItem[i].iPlaceX > 10000)
							InvenItem[i].iPlaceX -= 10000;
					}
				}
			}
		}
	}
	return TRUE;
}
int cINVENTORY::SearchItemIndex(DWORD CODE, int KindFlag)
{
	int i = 0;
	if (CODE)
	{
		for (i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItem[i].bValid)
			{
				if (InvenItem[i].sBaseItemID.ToInt() == CODE)
					return i + 1;
			}
		}
		for (i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItemTemp[i].bValid)
			{
				if (InvenItemTemp[i].sBaseItemID.ToInt() == CODE)
					return 100 + i + 1;
			}
		}
	}

	if (KindFlag)
	{
		for (int i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItem[i].bValid)
			{
				if (InvenItem[i].sItem.eCraftType == KindFlag)
					return i + 1;
			}
			if (InvenItemTemp[i].bValid)
			{
				if (InvenItemTemp[i].sItem.eCraftType == KindFlag)
					return 100 + i + 1;
			}
		}
	}
	return FALSE;
}


int WatermelonEventItemIndex[INVENTORY_MAXITEM * 2] = { 0, };

int ValentineEventItemIndex[INVENTORY_MAXITEM * 2] = { 0, };

int CandydaysEventItemIndex[INVENTORY_MAXITEM * 2] = { 0, };

int MagicalGreenEventItemIndex[INVENTORY_MAXITEM * 2] = { 0, };
int MagicalGreenEmeraldEventItemIndex[INVENTORY_MAXITEM * 2] = { 0, };

int TearOfKaraEventItemIndex[INVENTORY_MAXITEM * 2] = { 0, };

int FindinvestigatorNineEventItemIndex[INVENTORY_MAXITEM * 2] = { 0, };
int FindinvestigatorTaleEventItemIndex[INVENTORY_MAXITEM * 2] = { 0, };


int cINVENTORY::CheckItemCount(DWORD CODE)
{
	int i = 0;
	int item_count = 0;
	if (CODE)
	{
		for (i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItem[i].bValid)
			{
				if (InvenItem[i].sBaseItemID.ToInt() == CODE)
				{
					item_count++;
					WatermelonEventItemIndex[item_count - 1] = i + 1;
				}
			}
		}

		for (i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItemTemp[i].bValid)
			{
				if (InvenItemTemp[i].sBaseItemID.ToInt() == CODE)
				{
					item_count++;
					WatermelonEventItemIndex[item_count - 1] = 100 + i + 1;
				}
			}
		}
	}

	return item_count;
}

int cINVENTORY::CheckValentineItemCount(DWORD CODE)
{
	int i = 0;
	int item_count = 0;
	if (CODE)
	{
		for (i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItem[i].bValid)
			{
				if (InvenItem[i].sBaseItemID.ToInt() == CODE)
				{
					item_count++;
					ValentineEventItemIndex[item_count - 1] = i + 1;
				}
			}
		}

		for (i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItemTemp[i].bValid)
			{
				if (InvenItemTemp[i].sBaseItemID.ToInt() == CODE)
				{
					item_count++;
					ValentineEventItemIndex[item_count - 1] = 100 + i + 1;
				}
			}
		}
	}

	return item_count;
}

int cINVENTORY::CheckCandyItemCount(DWORD CODE)
{
	int i = 0;
	int item_count = 0;
	if (CODE)
	{
		for (i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItem[i].bValid)
			{
				if (InvenItem[i].sBaseItemID.ToInt() == CODE)
				{
					item_count++;
					CandydaysEventItemIndex[item_count - 1] = i + 1;
				}
			}
		}

		for (i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItemTemp[i].bValid)
			{
				if (InvenItemTemp[i].sBaseItemID.ToInt() == CODE)
				{
					item_count++;
					CandydaysEventItemIndex[item_count - 1] = 100 + i + 1;
				}
			}
		}
	}

	return item_count;
}

int cINVENTORY::CheckMagicalGreenItemCount(DWORD CODE)
{
	int i = 0;
	int item_count = 0;
	if (CODE)
	{
		for (i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItem[i].bValid)
			{
				if (InvenItem[i].sBaseItemID.ToInt() == CODE)
				{
					item_count++;
					MagicalGreenEventItemIndex[item_count - 1] = i + 1;
				}
			}
		}

		for (i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItemTemp[i].bValid)
			{
				if (InvenItemTemp[i].sBaseItemID.ToInt() == CODE)
				{
					item_count++;
					MagicalGreenEventItemIndex[item_count - 1] = 100 + i + 1;
				}
			}
		}
	}

	return item_count;
}
int cINVENTORY::CheckMagicalGreenItemEmeraldCount(DWORD CODE)
{
	int i = 0;
	int item_count = 0;
	if (CODE)
	{
		for (i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItem[i].bValid)
			{
				if (InvenItem[i].sBaseItemID.ToInt() == CODE)
				{
					item_count++;
					MagicalGreenEmeraldEventItemIndex[item_count - 1] = i + 1;
				}
			}
		}

		for (i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItemTemp[i].bValid)
			{
				if (InvenItemTemp[i].sBaseItemID.ToInt() == CODE)
				{
					item_count++;
					MagicalGreenEmeraldEventItemIndex[item_count - 1] = 100 + i + 1;
				}
			}
		}
	}

	return item_count;
}
int cINVENTORY::CheckTearOfKaraItemCount(DWORD CODE)
{
	int i = 0;
	int item_count = 0;
	if (CODE)
	{
		for (i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItem[i].bValid)
			{
				if (InvenItem[i].sBaseItemID.ToInt() == CODE)
				{
					item_count++;
					TearOfKaraEventItemIndex[item_count - 1] = i + 1;
				}
			}
		}

		for (i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItemTemp[i].bValid)
			{
				if (InvenItemTemp[i].sBaseItemID.ToInt() == CODE)
				{
					item_count++;
					TearOfKaraEventItemIndex[item_count - 1] = 100 + i + 1;
				}
			}
		}
	}

	return item_count;
}

int cINVENTORY::CheckFindinvestigatorNineItemCount(DWORD CODE)
{
	int i = 0;
	int item_count = 0;
	if (CODE)
	{
		for (i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItem[i].bValid)
			{
				if (InvenItem[i].sBaseItemID.ToInt() == CODE)
				{
					item_count++;
					FindinvestigatorNineEventItemIndex[item_count - 1] = i + 1;
				}
			}
		}

		for (i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItemTemp[i].bValid)
			{
				if (InvenItemTemp[i].sBaseItemID.ToInt() == CODE)
				{
					item_count++;
					FindinvestigatorNineEventItemIndex[item_count - 1] = 100 + i + 1;
				}
			}
		}
	}

	return item_count;
}
int cINVENTORY::CheckFindinvestigatorTaleItemCount(DWORD CODE)
{
	int i = 0;
	int item_count = 0;
	if (CODE)
	{
		for (i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItem[i].bValid)
			{
				if (InvenItem[i].sBaseItemID.ToInt() == CODE)
				{
					item_count++;
					FindinvestigatorTaleEventItemIndex[item_count - 1] = i + 1;
				}
			}
		}

		for (i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItemTemp[i].bValid)
			{
				if (InvenItemTemp[i].sBaseItemID.ToInt() == CODE)
				{
					item_count++;
					FindinvestigatorTaleEventItemIndex[item_count - 1] = 100 + i + 1;
				}
			}
		}
	}

	return item_count;
}
int cINVENTORY::ChangePuzzle(ItemData *pItem)
{
	char szTestBuff2[256];
	szTestBuff2[0] = 0;
	if ((pItem->sItem.sItemID.ToItemType()) == sinPZ1 || (pItem->sItem.sItemID.ToItemType()) == sinPZ2)
	{
		if (pItem->sItem.iPotionCount <= 1)
		{
			pItem->sItem.iPotionCount = 2;

			ItemData * pItemData = ITEMHANDLE->GetItemDataByID(pItem->sItem.sItemID.ToInt());

			if (pItemData)
			{
				CheckInvenItemForm();

				wsprintf(szTestBuff2, "Image\\sinImage\\Items\\%s\\it%s.bmp", pItemData->szCategory, pItemData->szInventoryName);
				pItemData->pcTempInventoryTexture = LoadDibSurfaceOffscreen(szTestBuff2);
				pItem->pcInventoryTexture = pItemData->pcTempInventoryTexture;
				pItem->iWidth = pItemData->iWidth;
				pItem->iHeight = pItemData->iHeight;
				pItem->sBaseItemID = pItemData->sBaseItemID;
				CheckWeight();
				ReFormInvenItem();
				sinMinusMoney(1000);
				ReformCharForm();
				SendSaveMoney();
				sinUsePotionDelayFlag = 1;
				cInvenTory.UnionCoreParticle2(pItem->iPlaceX, pItem->iPlaceY, 1);
				cInvenTory.UnionCoreParticle2(pItem->iPlaceX, pItem->iPlaceY, 1);
				cInvenTory.UnionCoreParticle2(pItem->iPlaceX, pItem->iPlaceY, 1);
				sinPlaySound(SIN_SOUND_EAT_POTION2);
				SaveGameData();
				return TRUE;
			}
		}
	}
	return FALSE;
}

DWORD CheckPuzzleIndex[4][4] =
{
	{sin01,0,sin02,0},
	{sin03,sin04,0,sin06},
	{0,sin05,0,0},
	{sin07,0,sin08,0},
};
DWORD CheckPuzzleIndex2[4][4] =
{
	{sin01,0,sin02,0},
	{sin03,sin04,0,sin06},
	{0,sin05,0,0},
	{sin07,0,sin08,0},
};

DWORD CheckPuzzleX[4] = { 8,9,10,11 };
int   PuzzleIndex[8] = { 0, };

int cINVENTORY::CheckPuzzle()
{
	int Count = 0;
	int Count2 = 0;
	int i, j, k;
	PuzzleOkFlag = 0;
	for (int p = 0; p < 8; p++) {
		PuzzleIndex[p] = 0;

	}

	for (i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].bValid)
		{
			if ((InvenItem[i].sItem.sItemID.ToItemType()) == sinPZ1)
			{
				for (j = 0; j < 4; j++)
				{
					for (k = 0; k < 4; k++)
					{
						if ((InvenItem[i].sItem.sItemID.ToItemIndex()) == CheckPuzzleIndex[j][k])
						{
							if ((StartX + (CheckPuzzleX[k] * 22)) == InvenItem[i].iPlaceX &&
								(StartY + (j * 22)) == InvenItem[i].iPlaceY)
							{
								PuzzleIndex[Count] = i + 1;
								Count++;
							}
						}
					}
				}
			}

			if ((InvenItem[i].sItem.sItemID.ToItemType()) == sinPZ2)
			{
				for (j = 0; j < 4; j++)
				{
					for (k = 0; k < 4; k++)
					{
						if ((InvenItem[i].sItem.sItemID.ToItemIndex()) == CheckPuzzleIndex2[j][k])
						{
							if ((StartX + (CheckPuzzleX[k] * 22)) == InvenItem[i].iPlaceX &&
								(StartY + (j * 22)) == InvenItem[i].iPlaceY)
							{
								PuzzleIndex[Count2] = i + 1;
								Count2++;
							}
						}
					}
				}
			}
		}
	}
	if (Count == 8 || Count2 == 8)
		PuzzleOkFlag = 1;
	return TRUE;
}
int cINVENTORY::CheckEventItem()
{

	int ItemIndex = SearchItemIndex((sinGF1 | sin02), 0);
	if (ItemIndex && ItemIndex < 100)
	{
		cInterFace.CheckAllBox(SIN_INVENTORY);
		cMessageBox.ShowMessage3(MESSAGE_EVENTITEM_SEND, "Babel's Horn");
		return TRUE;
	}
	else
		cSinHelp.sinShowHelp(SIN_HELP_KIND_BABEL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), BabelEventDoc);
	cMessageBox.ShowMessage3(MESSAGE_FALLGAME, FallGameName);
	return TRUE;
}
int cINVENTORY::SendEventItem()
{
	int Count = 0;
	int ItemIndex = 0;
	ItemData TempItem;
	TempItem.iWidth = 22 * 2;
	TempItem.iHeight = 22 * 2;


	memset(&sWingItem_Send, 0, sizeof(sCRAFTITEM_SERVER));

	ItemIndex = SearchItemIndex((sinGF1 | sin02), 0);
	if (ItemIndex && ItemIndex < 100)
	{
		if (sinChar->sWeight.sMin + 30 > sinChar->sWeight.sMax)
		{
			cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
			return FALSE;
		}
		if (!cCraftItem.CraftCheckEmptyArea(&TempItem))
		{
			cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
			return FALSE;
		}
		sWingItem_Send.SheltomCode[0] = InvenItem[ItemIndex - 1].sItem.sItemID.ToInt();
		sWingItem_Send.Head[0] = InvenItem[ItemIndex - 1].sItem.iChk1;
		sWingItem_Send.CheckSum[0] = InvenItem[ItemIndex - 1].sItem.iChk2;
	}

	sWingItem_Send.DocIndex = 2;
	return TRUE;

}
int cINVENTORY::CheckFoxEventItem()
{
	int ItemIndex = SearchItemIndex((sinGF1 | sin03), 0);
	int ItemIndex2 = SearchItemIndex((sinGF1 | sin04), 0);

	if (ItemIndex && ItemIndex < 100 && ItemIndex2 && ItemIndex2 < 100)
	{
		cInterFace.CheckAllBox(SIN_INVENTORY);
		cMessageBox.ShowMessage3(MESSAGE_FOXEVENTITEM_SEND, "Nine & Tail");
	}
	else
		cSinHelp.sinShowHelp(SIN_HELP_KIND_BABEL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), NineTailFoxDoc);
	return TRUE;
}
int cINVENTORY::SendFoxEventItem()
{
	int Count = 0;
	int ItemIndex = 0;
	int ItemIndex2 = 0;
	ItemData TempItem;
	TempItem.iWidth = 22 * 3;
	TempItem.iHeight = 22 * 4;


	memset(&sWingItem_Send, 0, sizeof(sCRAFTITEM_SERVER));

	ItemIndex = SearchItemIndex((sinGF1 | sin03), 0);
	ItemIndex2 = SearchItemIndex((sinGF1 | sin04), 0);
	if (ItemIndex && ItemIndex < 100 && ItemIndex2 && ItemIndex2 < 100)
	{
		if (sinChar->sWeight.sMin + 100 > sinChar->sWeight.sMax)
		{
			cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
			return FALSE;
		}

		if (!cCraftItem.CraftCheckEmptyArea(&TempItem))
		{
			cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
			return FALSE;
		}
		sWingItem_Send.SheltomCode[0] = InvenItem[ItemIndex - 1].sItem.sItemID.ToInt();
		sWingItem_Send.Head[0] = InvenItem[ItemIndex - 1].sItem.iChk1;
		sWingItem_Send.CheckSum[0] = InvenItem[ItemIndex - 1].sItem.iChk2;

		sWingItem_Send.SheltomCode[1] = InvenItem[ItemIndex2 - 1].sItem.sItemID.ToInt();
		sWingItem_Send.Head[1] = InvenItem[ItemIndex2 - 1].sItem.iChk1;
		sWingItem_Send.CheckSum[1] = InvenItem[ItemIndex2 - 1].sItem.iChk2;

	}
	sWingItem_Send.DocIndex = 2;
	return TRUE;

}
int cINVENTORY::CheckChristMasEventItem()
{

	int ItemIndex = SearchItemIndex((sinGF1 | sin05), 0);

	if (ItemIndex && ItemIndex < 100)
		cInterFace.CheckAllBox(SIN_INVENTORY);
	else
		cSinHelp.sinShowHelp(SIN_HELP_KIND_BABEL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), StarDustDoc);
	return TRUE;
}
int cINVENTORY::SendChristmasEventItem()
{
	int Count = 0;
	int ItemIndex = 0;

	ItemData TempItem;
	TempItem.iWidth = 22 * 3;
	TempItem.iHeight = 22 * 4;


	memset(&sWingItem_Send, 0, sizeof(sCRAFTITEM_SERVER));

	ItemIndex = SearchItemIndex((sinGF1 | sin05), 0);

	if (ItemIndex && ItemIndex < 100)
	{
		if (sinChar->sWeight.sMin + 100 > sinChar->sWeight.sMax)
		{
			cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
			return FALSE;
		}
		if (!cCraftItem.CraftCheckEmptyArea(&TempItem))
		{
			cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
			return FALSE;
		}
		sWingItem_Send.SheltomCode[0] = InvenItem[ItemIndex - 1].sItem.sItemID.ToInt();
		sWingItem_Send.Head[0] = InvenItem[ItemIndex - 1].sItem.iChk1;
		sWingItem_Send.CheckSum[0] = InvenItem[ItemIndex - 1].sItem.iChk2;

	}
	sWingItem_Send.DocIndex = 2;
	return TRUE;
}

int cINVENTORY::CheckSendPuzzle()
{
	int Count = 0;
	memset(&sWingItem_Send, 0, sizeof(sCRAFTITEM_SERVER));
	for (int i = 0; i < 8; i++)
	{
		if (PuzzleIndex[i] && InvenItem[PuzzleIndex[i] - 1].bValid)
		{
			if ((InvenItem[PuzzleIndex[i] - 1].sItem.sItemID.ToItemType()) == sinPZ1 || (InvenItem[PuzzleIndex[i] - 1].sItem.sItemID.ToItemType()) == sinPZ2)
			{
				sWingItem_Send.SheltomCode[i] = InvenItem[PuzzleIndex[i] - 1].sItem.sItemID.ToInt();
				sWingItem_Send.Head[i] = InvenItem[PuzzleIndex[i] - 1].sItem.iChk1;
				sWingItem_Send.CheckSum[i] = InvenItem[PuzzleIndex[i] - 1].sItem.iChk2;
				Count++;
			}
		}
	}
	if (Count == 8)
	{
		DWORD Temp = 0;
		for (int j = 0; j < 8; j++)
		{
			for (int k = 0; k < 8; k++)
			{
				if (j == k)
					continue;
				if (sWingItem_Send.SheltomCode[j] == sWingItem_Send.SheltomCode[k])
				{
					cMessageBox.ShowMessage(MESSAGE_FAILD_PUZZLE);
					return FALSE;
				}
			}
		}
	}
	else
	{
		cMessageBox.ShowMessage(MESSAGE_FAILD_PUZZLE);
		return FALSE;
	}
	if (sinChar->sWeight.sMin + 120 > sinChar->sWeight.sMax)
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
		return FALSE;
	}
	sWingItem_Send.DocIndex = 1;
	return TRUE;
}

int cINVENTORY::SendPuzzleNpc()
{
	if (PuzzleOkFlag)
	{
		cInterFace.CheckAllBox(SIN_INVENTORY);
		cMessageBox.ShowMessage3(MESSAGE_PUZZLE_SEND, "Puzzle");
	}
	else
	{
		WingItemQuestIndex = 1000;
		cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST_WING, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), WingQuestFilePath_a[6]);  //WingQuestFilePath_a[5]);  //¿ø·¡°ª //ÇØ¿Ü
	}
	return TRUE;
}
int cINVENTORY::DrawForceOrbEffect(int x, int y)
{
	int i = 0;
	char *Path = "image\\Sinimage\\Effect\\ForceOrb\\P_0%d.tga";
	char szBuff[128];
	if (!MatForceOrbEffect[0])
	{
		for (i = 0; i < 8; i++)
		{
			wsprintf(szBuff, Path, i + 1);
			MatForceOrbEffect[i] = CreateTextureMaterial(szBuff, 0, 0, 0, SMMAT_BLEND_ALPHA);
		}
		ReadTextures();
	}
	ForceOrb_Effect.InvenFace.MatNum = MatForceOrbEffect[ForceOrbEffectIndex];
	ForceOrb_Effect.InvenFace.x = x - 5;
	ForceOrb_Effect.InvenFace.y = y - 5;
	ForceOrb_Effect.InvenFace.r = 255;
	ForceOrb_Effect.InvenFace.g = 255;
	ForceOrb_Effect.InvenFace.b = 255;
	ForceOrb_Effect.InvenFace.Transparency = 255;
	ForceOrb_Effect.InvenFace.height = 32;
	ForceOrb_Effect.InvenFace.width = 32;
	ForceOrb_Effect.InvenFace.TexRect = sinTexRect;

	sinDrawInvenTexImage(&ForceOrb_Effect.InvenFace);
	return TRUE;
}

//Ê¹ÓÃÁ¦Á¿Ê¯Í·
int cINVENTORY::UseForceOrb(ItemData *pItem, int Flag)
{
	if (lpCurPlayer->iLoadedMapIndex >= 0 && STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapType == MAPTYPE_Town)
		return FALSE;

	if (sinItemPickUpDelayFlag)
		return FALSE;

	int UseFlag = 0;

	int i = 0;

	for (i = 0; i < 16; i++)
	{
		if ((pItem->sBaseItemID.ToInt()&sinITEM_MASK3) == SheltomCode2[i])
		{
			if (sinChar->iLevel >= ForceOrbUseLevel[i][0] && sinChar->iLevel <= ForceOrbUseLevel[i][1])
				UseFlag = i + 1;
		}
	}

	if (!UseFlag)
	{
		cMessageBox.ShowMessage(MESSAGE_NOT_USE_FORCEORB);
		return FALSE;
	}

	if (cSkill.SearchContiueSkill(SKILL_FORCE_ORB))
	{
		cMessageBox.ShowMessage(MESSAGE_NOT_USE_FORCEORB2);
		return FALSE;
	}

	pItem->sItem.iPotionCount = 100;
	sinThrowItemToFeild(pItem);
	pItem->bValid = 0;

	cInvenTory.SetItemToChar();
	cInvenTory.ReFormInvenItem();
	cInvenTory.CheckWeight();
	sinUsePotionDelayFlag = 1;
	sinPlaySound(SIN_SOUND_EAT_POTION2);
	return TRUE;
}
int cINVENTORY::SetForceOrb(DWORD ItemCODE, int Time)
{
	int UseFlag = 0;
	sSKILL TempSkill;
	memset(&TempSkill, 0, sizeof(sSKILL));

	for (int i = 0; i < 16; i++)
	{
		if ((ItemCODE&sinITEM_MASK3) == SheltomCode2[i])
			UseFlag = i + 1;
	}
	char *Path = "image\\Sinimage\\skill\\ForceOrb\\FOS_0%d.tga";
	char szBuff[128];
	if (!MatForceOrb[UseFlag - 1])
	{
		wsprintf(szBuff, Path, UseFlag);
		MatForceOrb[UseFlag - 1] = CreateTextureMaterial(szBuff, 0, 0, 0, SMMAT_BLEND_ALPHA);
		ReadTextures();
	}

	TempSkill.CODE = SKILL_FORCE_ORB;
	TempSkill.Point = UseFlag;
	TempSkill.UseTime = ForceOrbUseTime[UseFlag - 1];
	TempSkill.CheckTime = ForceOrbUseTime[UseFlag - 1] * 70 - Time * 70;
	TempSkill.MatIcon = MatForceOrb[UseFlag - 1];
	sinContinueSkillSet(&TempSkill);
	return TRUE;
}
int cINVENTORY::UseCapsuleItem(ItemData *pItem)
{
	ItemData TempItem;
	TempItem.iWidth = 22 * 2;
	TempItem.iHeight = 22 * 2;

	if (!cCraftItem.CraftCheckEmptyArea(&TempItem))
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
		return FALSE;
	}

	if (pItem->sBaseItemID.ToInt() == (sinSP1 | sin34))
	{
		if (sinChar->sWeight.sMin + 5 >= sinChar->sWeight.sMax)
		{
			cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
			return FALSE;
		}
	}

	bGiftBoxDelay = true;

	if (sinActionPotion())
	{
		pUsePotion = &InvenItem[SelectInvenItemIndex - 1];
		cInvenTory.ReFormInvenItem();
		cInvenTory.CheckWeight();
		sinUsePotionDelayFlag = 1;
	}

	return TRUE;
}

int CristalEventItemIndex[7] = { 0, };

int PristonAlphabetEventItemIndex[7] = { 0, };

int cINVENTORY::CheckCristalEventItem()
{
	int i, cnt = 0;
	for (i = 0; i < 7; i++)
		CristalEventItemIndex[i] = 0;

	for (i = 0; i < 12; i++)
	{
		if (cnt < 7)
		{
			if (CristalEventItemIndex[cnt] == 0)
				CristalEventItemIndex[cnt] = SearchItemIndex(CristalEventCODE[i], 0);
			if (CristalEventItemIndex[cnt] != 0)
				cnt++;
		}
	}
	if (cnt == 7)
	{
		cInterFace.CheckAllBox(SIN_INVENTORY);
#ifdef ENGLISH_LANGUAGE
		cMessageBox.ShowMessage3(MESSAGE_CRISTALEVENTITEM_SEND, "7 Crystals");
#else
		cMessageBox.ShowMessage3(MESSAGE_CRISTALEVENTITEM_SEND, "Ë®¾§");
#endif
	}
	else
		cSinHelp.sinShowHelp(SIN_HELP_KIND_BABEL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), CristalEventDoc);

	return TRUE;
}
int cINVENTORY::SendCristalEventItem()
{
	ItemData TempItem;
	TempItem.iWidth = 22 * 3;
	TempItem.iHeight = 22 * 4;

	memset(&sWingItem_Send, 0, sizeof(sCRAFTITEM_SERVER));

	if (sinChar->sWeight.sMin + 100 > sinChar->sWeight.sMax)
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
		return FALSE;
	}
	if (!cCraftItem.CraftCheckEmptyArea(&TempItem))
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
		return FALSE;
	}
	for (int i = 0; i < 7; i++)
	{
		if (CristalEventItemIndex[i] > 100)
		{
			sWingItem_Send.SheltomCode[i] = InvenItemTemp[CristalEventItemIndex[i] - 100 - 1].sItem.sItemID.ToInt();
			sWingItem_Send.Head[i] = InvenItemTemp[CristalEventItemIndex[i] - 100 - 1].sItem.iChk1;
			sWingItem_Send.CheckSum[i] = InvenItemTemp[CristalEventItemIndex[i] - 100 - 1].sItem.iChk2;
			continue;
		}
		if (CristalEventItemIndex[i])
		{
			sWingItem_Send.SheltomCode[i] = InvenItem[CristalEventItemIndex[i] - 1].sItem.sItemID.ToInt();
			sWingItem_Send.Head[i] = InvenItem[CristalEventItemIndex[i] - 1].sItem.iChk1;
			sWingItem_Send.CheckSum[i] = InvenItem[CristalEventItemIndex[i] - 1].sItem.iChk2;
		}
	}
	sWingItem_Send.DocIndex = 2;
	return TRUE;
}
int cINVENTORY::CheckWatermelonEventItem()
{
	int i, cnt = 0;
	for (i = 0; i < 7; i++)
		WatermelonEventItemIndex[i] = 0;

	cnt = CheckItemCount(WatermelonEventCODE);

	if (cnt >= 7)
	{
		cInterFace.CheckAllBox(SIN_INVENTORY);
		cMessageBox.ShowMessage3(MESSAGE_WATERMELON_EVENTITEM, StarItem);
	}
	else
		cSinHelp.sinShowHelp(SIN_HELP_KIND_BABEL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), StarDoc);

	return TRUE;
}
int cINVENTORY::CheckValentineEventItem()
{
	int i, cnt = 0;
	for (i = 0; i < 7; i++)
		ValentineEventItemIndex[i] = 0;

	cnt = CheckValentineItemCount(ValentineEventCODE);

	if (cnt >= 7)
	{
		cInterFace.CheckAllBox(SIN_INVENTORY);
		cMessageBox.ShowMessage3(MESSAGE_VALENTINE_EVENTITEM, ValentineItem);
	}
	else
		cSinHelp.sinShowHelp(SIN_HELP_KIND_BABEL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), ValentineDoc);  // Àåº° - ¹ß·»Å¸ÀÎ ÀÌº¥Æ®  

	return TRUE;
}
int cINVENTORY::CheckCandydaysEventItem()
{
	int i, cnt = 0;
	for (i = 0; i < 7; i++)
		CandydaysEventItemIndex[i] = 0;

	cnt = CheckCandyItemCount(CandydaysEventCODE);

	if (cnt >= 7)
	{
		cInterFace.CheckAllBox(SIN_INVENTORY);
		cMessageBox.ShowMessage3(MESSAGE_CANDYDAYS_EVENTITEM, CandydaysItem);
	}
	else
		cSinHelp.sinShowHelp(SIN_HELP_KIND_BABEL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), CandydaysDoc);  // Àåº° - Äµµðµ¥ÀÌÁî

	return TRUE;
}
int cINVENTORY::CheckMagicalGreenEventItem()
{
	int i, cnt = 0, cnt2 = 0;
	for (i = 0; i < 7; i++)
	{
		MagicalGreenEventItemIndex[i] = 0;
		MagicalGreenEmeraldEventItemIndex[i] = 0;
	}

	cnt = CheckMagicalGreenItemCount(MagicalGreenEventCODE[0]);
	cnt2 = CheckMagicalGreenItemEmeraldCount(MagicalGreenEventCODE[1]);

	if (cnt >= 7)
	{
		cInterFace.CheckAllBox(SIN_INVENTORY);
		cMessageBox.ShowMessage3(MESSAGE_MAGICALGREEN_EVENTITEM, MagicalGreenJadeItem);
	}

	else if (cnt2 >= 7)
	{
		cInterFace.CheckAllBox(SIN_INVENTORY);
		cMessageBox.ShowMessage3(MESSAGE_MAGICALGREEN_EVENTITEM_EMERALD, MagicalGreenEmeraldItem);
	}

	else
		cSinHelp.sinShowHelp(SIN_HELP_KIND_BABEL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), MagicalGreenDoc);

	return TRUE;
}
int cINVENTORY::CheckTearOfKaraEventItem()
{
	int i, cnt = 0;
	for (i = 0; i < 7; i++)
		TearOfKaraEventItemIndex[i] = 0;

	cnt = CheckTearOfKaraItemCount(TeatOfKaraEventCODE);

	if (cnt >= 7)
	{
		cInterFace.CheckAllBox(SIN_INVENTORY);
		cMessageBox.ShowMessage3(MESSAGE_TEAROFKARA_EVENTITEM, TearOfKaraItem);
	}
	else
		cSinHelp.sinShowHelp(SIN_HELP_KIND_BABEL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), TearOfKaraDoc);

	return TRUE;
}
int cINVENTORY::CheckFindinvestigatorEventItem()
{
	int i, cnt = 0, cnt2 = 0;

	for (i = 0; i < 1; i++)
	{
		FindinvestigatorNineEventItemIndex[i] = 0;
		FindinvestigatorTaleEventItemIndex[i] = 0;
	}

	cnt = CheckFindinvestigatorNineItemCount(FindinvestigatorEventCODE[0]);
	cnt2 = CheckFindinvestigatorTaleItemCount(FindinvestigatorEventCODE[1]);

	if (cnt == 0 && cnt2 == 0)
	{
		cSinHelp.sinShowHelp(SIN_HELP_KIND_BABEL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), Findinvestigator1_1Doc);
		cMessageBox.ShowMessage3(MESSAGE_FIND_EVENTITEM, FindinvestigatorItem);
	}
	else if (cnt == 1)
		cSinHelp.sinShowHelp(SIN_HELP_KIND_BABEL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), Findinvestigator1_2Doc);

	else if (cnt == 0 && cnt2 == 1)
		cSinHelp.sinShowHelp(SIN_HELP_KIND_BABEL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), Findinvestigator1_3Doc);

	return TRUE;
}
int cINVENTORY::CheckFindinvestigatorKamiuEventItem()
{
	int i, cnt = 0;

	for (i = 0; i < 1; i++)
		FindinvestigatorNineEventItemIndex[i] = 0;

	cnt = CheckFindinvestigatorNineItemCount(FindinvestigatorEventCODE[0]);

	if (cnt == 1)
	{
		cSinHelp.sinShowHelp(SIN_HELP_KIND_BABEL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), Findinvestigator2_1Doc);
		cMessageBox.ShowMessage3(MESSAGE_FINDKAMIU_EVENTITEM, FindinvestigatorNineItem);
	}
	else if (cnt == 0)
		cSinHelp.sinShowHelp(SIN_HELP_KIND_BABEL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), Findinvestigator2_2Doc);

	return TRUE;
}
int cINVENTORY::CheckFindinvestigatorEtoEventItem()
{
	int i, cnt = 0;

	for (i = 0; i < 1; i++)
		FindinvestigatorTaleEventItemIndex[i] = 0;

	cnt = CheckFindinvestigatorTaleItemCount(FindinvestigatorEventCODE[1]);

	if (cnt == 1)
	{
		cSinHelp.sinShowHelp(SIN_HELP_KIND_BABEL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), Findinvestigator3_1Doc);
		cMessageBox.ShowMessage3(MESSAGE_FINDETO_EVENTITEM, FindinvestigatorTaleItem);
	}
	else if (cnt == 0)
		cSinHelp.sinShowHelp(SIN_HELP_KIND_BABEL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), Findinvestigator3_2Doc);

	return TRUE;
}
int cINVENTORY::SendWatermelonEventItem()
{
	ItemData TempItem;
	TempItem.iWidth = 22 * 3;
	TempItem.iHeight = 22 * 4;

	memset(&sWingItem_Send, 0, sizeof(sCRAFTITEM_SERVER));

	if (sinChar->sWeight.sMin + 10 > sinChar->sWeight.sMax)
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
		return FALSE;
	}
	if (!cCraftItem.CraftCheckEmptyArea(&TempItem))
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
		return FALSE;
	}
	for (int i = 0; i < 7; i++)
	{
		if (WatermelonEventItemIndex[i] > 100)
		{
			sWingItem_Send.SheltomCode[i] = InvenItemTemp[WatermelonEventItemIndex[i] - 100 - 1].sItem.sItemID.ToInt();
			sWingItem_Send.Head[i] = InvenItemTemp[WatermelonEventItemIndex[i] - 100 - 1].sItem.iChk1;
			sWingItem_Send.CheckSum[i] = InvenItemTemp[WatermelonEventItemIndex[i] - 100 - 1].sItem.iChk2;
			continue;
		}
		if (WatermelonEventItemIndex[i])
		{
			sWingItem_Send.SheltomCode[i] = InvenItem[WatermelonEventItemIndex[i] - 1].sItem.sItemID.ToInt();
			sWingItem_Send.Head[i] = InvenItem[WatermelonEventItemIndex[i] - 1].sItem.iChk1;
			sWingItem_Send.CheckSum[i] = InvenItem[WatermelonEventItemIndex[i] - 1].sItem.iChk2;
		}
	}
	sWingItem_Send.DocIndex = 2;
	return TRUE;
}
int cINVENTORY::SendValentineEventItem()
{
	ItemData TempItem;
	TempItem.iWidth = 22 * 3;
	TempItem.iHeight = 22 * 4;

	memset(&sWingItem_Send, 0, sizeof(sCRAFTITEM_SERVER));

	if (sinChar->sWeight.sMin + 50 > sinChar->sWeight.sMax)
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
		return FALSE;
	}
	if (!cCraftItem.CraftCheckEmptyArea(&TempItem))
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
		return FALSE;
	}
	for (int i = 0; i < 7; i++)
	{
		if (ValentineEventItemIndex[i] > 100)
		{
			sWingItem_Send.SheltomCode[i] = InvenItemTemp[ValentineEventItemIndex[i] - 100 - 1].sItem.sItemID.ToInt();
			sWingItem_Send.Head[i] = InvenItemTemp[ValentineEventItemIndex[i] - 100 - 1].sItem.iChk1;
			sWingItem_Send.CheckSum[i] = InvenItemTemp[ValentineEventItemIndex[i] - 100 - 1].sItem.iChk2;
			continue;
		}
		if (ValentineEventItemIndex[i])
		{
			sWingItem_Send.SheltomCode[i] = InvenItem[ValentineEventItemIndex[i] - 1].sItem.sItemID.ToInt();
			sWingItem_Send.Head[i] = InvenItem[ValentineEventItemIndex[i] - 1].sItem.iChk1;
			sWingItem_Send.CheckSum[i] = InvenItem[ValentineEventItemIndex[i] - 1].sItem.iChk2;
		}
	}
	sWingItem_Send.DocIndex = 2;
	return TRUE;
}
int cINVENTORY::CheckPristonAlphabetEventItem()
{
	int i, cnt = 0;
	for (i = 0; i < 7; i++)
		PristonAlphabetEventItemIndex[i] = 0;

	for (i = 0; i < 7; i++)
	{
		if (cnt < 7)
		{
			if (PristonAlphabetEventItemIndex[cnt] == 0)
				PristonAlphabetEventItemIndex[cnt] = SearchItemIndex(PristonAlphabetEventCODE[i], 0);
			if (PristonAlphabetEventItemIndex[cnt] != 0)
				cnt++;
		}
	}
	if (cnt == 7)
	{
		cInterFace.CheckAllBox(SIN_INVENTORY);
		cMessageBox.ShowMessage3(MESSAGE_PRISTON_ALPHABET_EVENTITEM, PristonAlphabetItem);
	}
	else
		cSinHelp.sinShowHelp(SIN_HELP_KIND_BABEL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), PristonAlphabetDoc);

	return TRUE;
}
int cINVENTORY::SendPristonAlphabetEventItem()
{
	ItemData TempItem;
	TempItem.iWidth = 22 * 3;
	TempItem.iHeight = 22 * 4;

	memset(&sWingItem_Send, 0, sizeof(sCRAFTITEM_SERVER));

	if (sinChar->sWeight.sMin + 20 > sinChar->sWeight.sMax)
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
		return FALSE;
	}
	if (!cCraftItem.CraftCheckEmptyArea(&TempItem))
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
		return FALSE;
	}
	for (int i = 0; i < 7; i++)
	{
		if (PristonAlphabetEventItemIndex[i] > 100)
		{
			sWingItem_Send.SheltomCode[i] = InvenItemTemp[PristonAlphabetEventItemIndex[i] - 100 - 1].sItem.sItemID.ToInt();
			sWingItem_Send.Head[i] = InvenItemTemp[PristonAlphabetEventItemIndex[i] - 100 - 1].sItem.iChk1;
			sWingItem_Send.CheckSum[i] = InvenItemTemp[PristonAlphabetEventItemIndex[i] - 100 - 1].sItem.iChk2;
			continue;
		}
		if (PristonAlphabetEventItemIndex[i])
		{
			sWingItem_Send.SheltomCode[i] = InvenItem[PristonAlphabetEventItemIndex[i] - 1].sItem.sItemID.ToInt();
			sWingItem_Send.Head[i] = InvenItem[PristonAlphabetEventItemIndex[i] - 1].sItem.iChk1;
			sWingItem_Send.CheckSum[i] = InvenItem[PristonAlphabetEventItemIndex[i] - 1].sItem.iChk2;
		}
	}
	sWingItem_Send.DocIndex = 2;
	return TRUE;
}
int cINVENTORY::SendCandydaysEventItem()
{
	ItemData TempItem;
	TempItem.iWidth = 22 * 3;
	TempItem.iHeight = 22 * 4;

	ZeroMemory(&sWingItem_Send, sizeof(sCRAFTITEM_SERVER));

	if (sinChar->sWeight.sMin + 50 > sinChar->sWeight.sMax)
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
		return FALSE;
	}
	if (!cCraftItem.CraftCheckEmptyArea(&TempItem))
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
		return FALSE;
	}
	for (int i = 0; i < 7; i++)
	{
		if (CandydaysEventItemIndex[i] > 100)
		{
			sWingItem_Send.SheltomCode[i] = InvenItemTemp[CandydaysEventItemIndex[i] - 100 - 1].sItem.sItemID.ToInt();
			sWingItem_Send.Head[i] = InvenItemTemp[CandydaysEventItemIndex[i] - 100 - 1].sItem.iChk1;
			sWingItem_Send.CheckSum[i] = InvenItemTemp[CandydaysEventItemIndex[i] - 100 - 1].sItem.iChk2;
			continue;
		}
		if (CandydaysEventItemIndex[i])
		{
			sWingItem_Send.SheltomCode[i] = InvenItem[CandydaysEventItemIndex[i] - 1].sItem.sItemID.ToInt();
			sWingItem_Send.Head[i] = InvenItem[CandydaysEventItemIndex[i] - 1].sItem.iChk1;
			sWingItem_Send.CheckSum[i] = InvenItem[CandydaysEventItemIndex[i] - 1].sItem.iChk2;
		}
	}
	sWingItem_Send.DocIndex = 2;
	return TRUE;
}
int cINVENTORY::SendMagicalGreenEventItem()
{
	ItemData TempItem;
	TempItem.iWidth = 22 * 3;
	TempItem.iHeight = 22 * 4;

	ZeroMemory(&sWingItem_Send, sizeof(sCRAFTITEM_SERVER));

	if (sinChar->sWeight.sMin + 70 > sinChar->sWeight.sMax)
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
		return FALSE;
	}
	if (!cCraftItem.CraftCheckEmptyArea(&TempItem))
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
		return FALSE;
	}
	for (int i = 0; i < 7; i++)
	{
		if (MagicalGreenEventItemIndex[i] > 100)
		{
			sWingItem_Send.SheltomCode[i] = InvenItemTemp[MagicalGreenEventItemIndex[i] - 100 - 1].sItem.sItemID.ToInt();
			sWingItem_Send.Head[i] = InvenItemTemp[MagicalGreenEventItemIndex[i] - 100 - 1].sItem.iChk1;
			sWingItem_Send.CheckSum[i] = InvenItemTemp[MagicalGreenEventItemIndex[i] - 100 - 1].sItem.iChk2;
			continue;
		}
		if (MagicalGreenEventItemIndex[i])
		{
			sWingItem_Send.SheltomCode[i] = InvenItem[MagicalGreenEventItemIndex[i] - 1].sItem.sItemID.ToInt();
			sWingItem_Send.Head[i] = InvenItem[MagicalGreenEventItemIndex[i] - 1].sItem.iChk1;
			sWingItem_Send.CheckSum[i] = InvenItem[MagicalGreenEventItemIndex[i] - 1].sItem.iChk2;
		}
	}
	sWingItem_Send.DocIndex = 2;
	return TRUE;
}
int cINVENTORY::SendMagicalGreenEmeraldEventItem()
{
	ItemData TempItem;
	TempItem.iWidth = 22 * 3;
	TempItem.iHeight = 22 * 4;

	ZeroMemory(&sWingItem_Send, sizeof(sCRAFTITEM_SERVER));

	if (sinChar->sWeight.sMin + 70 > sinChar->sWeight.sMax)
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
		return FALSE;
	}
	if (!cCraftItem.CraftCheckEmptyArea(&TempItem))
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
		return FALSE;
	}
	for (int i = 0; i < 7; i++)
	{
		if (MagicalGreenEmeraldEventItemIndex[i] > 100)
		{
			sWingItem_Send.SheltomCode[i] = InvenItemTemp[MagicalGreenEmeraldEventItemIndex[i] - 100 - 1].sItem.sItemID.ToInt();
			sWingItem_Send.Head[i] = InvenItemTemp[MagicalGreenEmeraldEventItemIndex[i] - 100 - 1].sItem.iChk1;
			sWingItem_Send.CheckSum[i] = InvenItemTemp[MagicalGreenEmeraldEventItemIndex[i] - 100 - 1].sItem.iChk2;
			continue;
		}
		if (MagicalGreenEmeraldEventItemIndex[i])
		{
			sWingItem_Send.SheltomCode[i] = InvenItem[MagicalGreenEmeraldEventItemIndex[i] - 1].sItem.sItemID.ToInt();
			sWingItem_Send.Head[i] = InvenItem[MagicalGreenEmeraldEventItemIndex[i] - 1].sItem.iChk1;
			sWingItem_Send.CheckSum[i] = InvenItem[MagicalGreenEmeraldEventItemIndex[i] - 1].sItem.iChk2;
		}
	}
	sWingItem_Send.DocIndex = 2;
	return TRUE;
}
int cINVENTORY::SendTearOfKaraEventItem()
{
	ItemData TempItem;
	TempItem.iWidth = 22 * 2;
	TempItem.iHeight = 22 * 2;

	ZeroMemory(&sWingItem_Send, sizeof(sCRAFTITEM_SERVER));

	if (sinChar->sWeight.sMin + 10 > sinChar->sWeight.sMax)
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
		return FALSE;
	}
	if (!cCraftItem.CraftCheckEmptyArea(&TempItem))
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
		return FALSE;
	}
	for (int i = 0; i < 7; i++)
	{
		if (TearOfKaraEventItemIndex[i] > 100)
		{
			sWingItem_Send.SheltomCode[i] = InvenItemTemp[TearOfKaraEventItemIndex[i] - 100 - 1].sItem.sItemID.ToInt();
			sWingItem_Send.Head[i] = InvenItemTemp[TearOfKaraEventItemIndex[i] - 100 - 1].sItem.iChk1;
			sWingItem_Send.CheckSum[i] = InvenItemTemp[TearOfKaraEventItemIndex[i] - 100 - 1].sItem.iChk2;
			continue;
		}
		if (TearOfKaraEventItemIndex[i])
		{
			sWingItem_Send.SheltomCode[i] = InvenItem[TearOfKaraEventItemIndex[i] - 1].sItem.sItemID.ToInt();
			sWingItem_Send.Head[i] = InvenItem[TearOfKaraEventItemIndex[i] - 1].sItem.iChk1;
			sWingItem_Send.CheckSum[i] = InvenItem[TearOfKaraEventItemIndex[i] - 1].sItem.iChk2;
		}
	}
	sWingItem_Send.DocIndex = 2;
	return TRUE;
}
int cINVENTORY::UseSoccerBallPotionItem(ItemData *pItem)
{
	pItem->sItem.iPotionCount = 100;
	sinThrowItemToFeild(pItem);
	pItem->bValid = 0;

	cInvenTory.SetItemToChar();
	cInvenTory.ReFormInvenItem();
	cInvenTory.CheckWeight();
	sinUsePotionDelayFlag = 1;
	sinPlaySound(SIN_SOUND_EAT_POTION2);

	return TRUE;
}
int cINVENTORY::SendFindinvestigatorNineEventItem()
{
	ItemData TempItem;
	TempItem.iWidth = 22 * 2;
	TempItem.iHeight = 22 * 2;

	ZeroMemory(&sWingItem_Send, sizeof(sCRAFTITEM_SERVER));

	if (sinChar->sWeight.sMin + 5 > sinChar->sWeight.sMax)
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
		return FALSE;
	}
	if (!cCraftItem.CraftCheckEmptyArea(&TempItem))
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
		return FALSE;
	}
	for (int i = 0; i < 1; i++)
	{
		if (FindinvestigatorNineEventItemIndex[i] > 100)
		{
			sWingItem_Send.SheltomCode[i] = InvenItemTemp[FindinvestigatorNineEventItemIndex[i] - 100 - 1].sItem.sItemID.ToInt();
			sWingItem_Send.Head[i] = InvenItemTemp[FindinvestigatorNineEventItemIndex[i] - 100 - 1].sItem.iChk1;
			sWingItem_Send.CheckSum[i] = InvenItemTemp[FindinvestigatorNineEventItemIndex[i] - 100 - 1].sItem.iChk2;
			continue;
		}
		if (FindinvestigatorNineEventItemIndex[i])
		{
			sWingItem_Send.SheltomCode[i] = InvenItem[FindinvestigatorNineEventItemIndex[i] - 1].sItem.sItemID.ToInt();
			sWingItem_Send.Head[i] = InvenItem[FindinvestigatorNineEventItemIndex[i] - 1].sItem.iChk1;
			sWingItem_Send.CheckSum[i] = InvenItem[FindinvestigatorNineEventItemIndex[i] - 1].sItem.iChk2;
		}
	}
	sWingItem_Send.DocIndex = 2;
	return TRUE;
}

int cINVENTORY::SendFindinvestigatorTaleEventItem()
{
	ItemData TempItem;
	TempItem.iWidth = 22 * 2;
	TempItem.iHeight = 22 * 2;

	ZeroMemory(&sWingItem_Send, sizeof(sCRAFTITEM_SERVER));

	if (sinChar->sWeight.sMin + 5 > sinChar->sWeight.sMax)
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
		return FALSE;
	}
	if (!cCraftItem.CraftCheckEmptyArea(&TempItem))
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
		return FALSE;
	}
	for (int i = 0; i < 1; i++)
	{
		if (FindinvestigatorNineEventItemIndex[i] > 100)
		{
			sWingItem_Send.SheltomCode[i] = InvenItemTemp[FindinvestigatorNineEventItemIndex[i] - 100 - 1].sItem.sItemID.ToInt();
			sWingItem_Send.Head[i] = InvenItemTemp[FindinvestigatorNineEventItemIndex[i] - 100 - 1].sItem.iChk1;
			sWingItem_Send.CheckSum[i] = InvenItemTemp[FindinvestigatorNineEventItemIndex[i] - 100 - 1].sItem.iChk2;
			continue;
		}
		if (FindinvestigatorNineEventItemIndex[i])
		{
			sWingItem_Send.SheltomCode[i] = InvenItem[FindinvestigatorNineEventItemIndex[i] - 1].sItem.sItemID.ToInt();
			sWingItem_Send.Head[i] = InvenItem[FindinvestigatorNineEventItemIndex[i] - 1].sItem.iChk1;
			sWingItem_Send.CheckSum[i] = InvenItem[FindinvestigatorNineEventItemIndex[i] - 1].sItem.iChk2;
		}
	}
	sWingItem_Send.DocIndex = 2;
	return TRUE;
}
int cINVENTORY::SendFindinvestigatorTaleEtoEventItem()
{
	ItemData TempItem;
	TempItem.iWidth = 22 * 2;
	TempItem.iHeight = 22 * 2;

	ZeroMemory(&sWingItem_Send, sizeof(sCRAFTITEM_SERVER));

	if (sinChar->sWeight.sMin + 10 > sinChar->sWeight.sMax)
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
		return FALSE;
	}
	if (!cCraftItem.CraftCheckEmptyArea(&TempItem))
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
		return FALSE;
	}
	for (int i = 0; i < 1; i++)
	{
		if (FindinvestigatorTaleEventItemIndex[i] > 100)
		{
			sWingItem_Send.SheltomCode[i] = InvenItemTemp[FindinvestigatorTaleEventItemIndex[i] - 100 - 1].sItem.sItemID.ToInt();
			sWingItem_Send.Head[i] = InvenItemTemp[FindinvestigatorTaleEventItemIndex[i] - 100 - 1].sItem.iChk1;
			sWingItem_Send.CheckSum[i] = InvenItemTemp[FindinvestigatorTaleEventItemIndex[i] - 100 - 1].sItem.iChk2;
			continue;
		}
		if (FindinvestigatorTaleEventItemIndex[i])
		{
			sWingItem_Send.SheltomCode[i] = InvenItem[FindinvestigatorTaleEventItemIndex[i] - 1].sItem.sItemID.ToInt();
			sWingItem_Send.Head[i] = InvenItem[FindinvestigatorTaleEventItemIndex[i] - 1].sItem.iChk1;
			sWingItem_Send.CheckSum[i] = InvenItem[FindinvestigatorTaleEventItemIndex[i] - 1].sItem.iChk2;
		}
	}
	sWingItem_Send.DocIndex = 2;
	return TRUE;
}