#include "StdAfx.h"
#include "..\\AreaServer.h"

cHaPremiumItem  chaPremiumitem;

#define  TELEPORT_FIELDMAX 33
//´«ËÍ¾íÖá
int TelePort_FieldNum[][3] =
{
	// Page1 -> ·çÖ®Â·,ÇïÖ®¹È  ÐÄÇéÊ÷ÁÖ  ½ºÖ®ÁÖ      ×ÔÓÉÍ¥Ôº    ·ÏÐæÄ¹µØ   ·ÏÐæ        ÒÅÍüµØÓò     ×çÖäÖ®µØ     ÂÌÖÞ
	{0	,20	,MAPLEVEL(20)	},{1	,19	,MAPLEVEL(19)},{2	,17	,MAPLEVEL(17)	},{3	, 0	,MAPLEVEL(0)	},{4	,2	,MAPLEVEL(2)	},{5	,4	,MAPLEVEL(4)	}, {6	,5	,MAPLEVEL(5)	},{7	,7	,MAPLEVEL(7)	},{8	,8	,MAPLEVEL(8)	},{9	,10	,MAPLEVEL(10)	},

	// Page2 -> ¹Å´úÕ½³¡ ·âÓ¡Ö®µØ ·ä·¿     Ä¢¹½      Ê¥µî        µØÀÎ1²ã     µØÀÎ2²ã    µØÀÎ3²ã      »ÞÆøËÂÃí1    »ÞÆøËÂÃí2
{10	,11	,MAPLEVEL(11)	},{11	,12	,MAPLEVEL(12)},{12	,25	,MAPLEVEL(25)	},{13	,24	,MAPLEVEL(24)	},{14	,26	,MAPLEVEL(26)	},{15	,13	,MAPLEVEL(13)	}, {16	,14	,MAPLEVEL(14)	},{17	,15	,MAPLEVEL(15)	},{18	,22	,MAPLEVEL(22)	},{19	,23	,MAPLEVEL(23)	},

// Page3 ->»ÞÆøËÂÃí3 Ì°À·Ö®ºþ Ìú1    Ìú2         ÓÄÀ­        ±ù1         ±ù2         Áú¶´        ÃÔÊ§1       ÃÔÊ§2
{20	,42	,MAPLEVEL(42)	},{21	,34	,MAPLEVEL(34)},{22	,27	,MAPLEVEL(27)	},{23	,28	,MAPLEVEL(28)	},{24	,29	,MAPLEVEL(29)	},{25	,31	,MAPLEVEL(31)	}, {26	,35	,MAPLEVEL(35)	},{27	,36	,MAPLEVEL(36)	},{28	,37	,MAPLEVEL(37)	},{29	,38	,MAPLEVEL(38)	},

// Page4 -> Ê§Âä1 Ê§Âä2   Ê§Âä3
{30	,40	,MAPLEVEL(40)	},{31	,41	,MAPLEVEL(41)},{32	,43	,MAPLEVEL(43)	},{33	,44	,MAPLEVEL(44)	}
};
char *haTeleport_Field[] =
{
	"image\\Sinimage\\help\\haTeleport_Field[1].sin",
		"image\\Sinimage\\help\\haTeleport_Field[2].sin",
		"image\\Sinimage\\help\\haTeleport_Field[3].sin",
		"image\\Sinimage\\help\\haTeleport_Field[4].sin",
};
int ItemUseLeftPosi[SINUPKEEPITEM_MAX][2] = { 0 };

cHaPremiumItem::cHaPremiumItem()
{
	TelePortCore.PageButtonFlag[0] = 0;
	TelePortCore.PageButtonFlag[1] = 0;
	TelePortCore.FieldIndex[0] = 0;
	TelePortCore.FieldIndex[1] = 0;
	TelePortCore.PageIndex = 0;
	Using_ItemKind = 0;
	Using_SelectInvenItemIndex = 0;
	for (int i = 0; i < SINUPKEEPITEM_MAX; i++)
	{
		UpKeepItem[i].PosiX = 0;
		UpKeepItem[i].PosiY = 0;
		UpKeepItem[i].Visible = false;
		UpKeepItem[i].IconTime[0] = 0;
		UpKeepItem[i].IconTime[1] = 0;
		UpKeepItem[i].Alpha = 255;
		UpKeepItem[i].Alphakind = 0;
		UpKeepItem[i].Per = 0;
		memset(UpKeepItem[i].Id, NULL, sizeof(UpKeepItem[i].Id));
	}

	m_ThirdEyesTime = 0;
	m_ExpUpPotionTime = 0;
	m_VampiricCuspidTime = 0;
	m_ManaRechargingPTime = 0;
	m_ManaReducePotiontime = 0;
	m_ManaReducePotionValue = 0;
	m_MightofAwellTime = 0;
	m_MightofAwellWeight = 0;
	m_HelpPetTime = 0;
	m_StaminaReducePotiontime = 0;
	m_StaminaReducePotionValue = 0;
	m_VipInfoTime = 0;
	m_Caravan_HopyTime = 0;
	m_BigHeadTime = 0;
	m_PhenixPetTime = 0;

	int ColLen = 0;
	int RowLen = 0;

	for (int k = 1; k <= SINUPKEEPITEM_MAX; k++)
	{
		ItemUseLeftPosi[k - 1][0] = 8 + RowLen;
		ItemUseLeftPosi[k - 1][1] = 80 + ColLen;

		ColLen += 36;

		if (k % 6 == 0)
		{
			RowLen += 36;
			ColLen = 0;
		}
	}
}
cHaPremiumItem::~cHaPremiumItem()
{
	for (int i = 0; i < SINUPKEEPITEM_MAX; i++)
		DELET(lpUpKeepItemBackImage[i]);
}
void cHaPremiumItem::init()
{
	UpKeepItemTGAImage[0] = CreateTextureMaterial("image\\Sinimage\\Premium\\ThirdEyes.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[1] = CreateTextureMaterial("image\\Sinimage\\Premium\\ExpUpPotion.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[2] = CreateTextureMaterial("image\\Sinimage\\Premium\\Vampiric.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[3] = CreateTextureMaterial("image\\Sinimage\\Premium\\M_Rechar.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[4] = CreateTextureMaterial("image\\Sinimage\\Premium\\M_Might.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[5] = CreateTextureMaterial("image\\Sinimage\\Premium\\M_Reduce.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[6] = CreateTextureMaterial("image\\Sinimage\\Premium\\Pet_terry-pose.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[7] = CreateTextureMaterial("image\\Sinimage\\Premium\\Pet_nepsys-pose.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[8] = CreateTextureMaterial("image\\Sinimage\\Premium\\Pet_io-pose.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[9] = CreateTextureMaterial("image\\Sinimage\\Premium\\Pet-mute-pose.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[10] = CreateTextureMaterial("image\\Sinimage\\Premium\\Vampiric_EX.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[11] = CreateTextureMaterial("image\\Sinimage\\Premium\\S_Reduce.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[12] = CreateTextureMaterial("image\\Sinimage\\Premium\\VipInfo.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[13] = CreateTextureMaterial("image\\Sinimage\\Premium\\CaravanHopy.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[14] = CreateTextureMaterial("image\\Sinimage\\Premium\\BigHead.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[15] = CreateTextureMaterial("image\\Sinimage\\Premium\\GiraffeHat.png", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[16] = CreateTextureMaterial("image\\Sinimage\\Premium\\MagicianHat.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[17] = CreateTextureMaterial("image\\Sinimage\\Premium\\WitchHat.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[18] = CreateTextureMaterial("image\\Sinimage\\Premium\\maskedman.png", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[19] = CreateTextureMaterial("image\\Sinimage\\Premium\\maskedwoman.png", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[20] = CreateTextureMaterial("image\\Sinimage\\Premium\\PumpkinHat.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[21] = CreateTextureMaterial("image\\Sinimage\\Premium\\SheepHat.png", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[22] = CreateTextureMaterial("image\\Sinimage\\Premium\\SoccerHat.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[23] = CreateTextureMaterial("image\\Sinimage\\Premium\\GreenXmasHat.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[24] = CreateTextureMaterial("image\\Sinimage\\Premium\\RedXmasHat.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[25] = CreateTextureMaterial("image\\Sinimage\\Premium\\PhoenixFire.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[26] = CreateTextureMaterial("image\\Sinimage\\Premium\\PhoenixIce.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[27] = CreateTextureMaterial("image\\Sinimage\\Premium\\PhoenixLightning.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[28] = CreateTextureMaterial("image\\Sinimage\\Premium\\PhoenixHeal.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[29] = CreateTextureMaterial("image\\Sinimage\\Premium\\easterears.png", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[30] = CreateTextureMaterial("image\\Sinimage\\Premium\\CaravanArma.TGA", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[31] = CreateTextureMaterial("image\\Sinimage\\Premium\\CaravanBuma.TGA", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[32] = CreateTextureMaterial("image\\Sinimage\\Premium\\CaravanCuepy.TGA", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[33] = CreateTextureMaterial("image\\Sinimage\\Premium\\CaravanHungky.TGA", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[34] = CreateTextureMaterial("image\\Sinimage\\Premium\\CaravanRabie.TGA", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[35] = CreateTextureMaterial("image\\Sinimage\\Premium\\CaravanTobie.TGA", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[36] = CreateTextureMaterial("image\\Sinimage\\Premium\\birthday.png", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[37] = CreateTextureMaterial("image\\Sinimage\\Premium\\BlueXmasHat.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[38] = CreateTextureMaterial("image\\Sinimage\\Premium\\CaravanRudolf.TGA", 0, 0, 0, SMMAT_BLEND_ALPHA);

	lpUpKeepItemBackImage[0] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\ThirdEyes_Back.bmp");
	lpUpKeepItemBackImage[1] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\ExpUpPotion_Back.bmp");
	lpUpKeepItemBackImage[2] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\Vampiric_back.bmp");
	lpUpKeepItemBackImage[3] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\M_Rechar_back.bmp");
	lpUpKeepItemBackImage[4] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\M_Might_back.bmp");
	lpUpKeepItemBackImage[5] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\M_Reduce_back.bmp");
	lpUpKeepItemBackImage[6] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\M_Phoenix_back.BMP");
	lpUpKeepItemBackImage[7] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\M_Phoenix_back.BMP");
	lpUpKeepItemBackImage[8] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\M_Phoenix_back.BMP");
	lpUpKeepItemBackImage[9] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\M_Phoenix_back.BMP");
	lpUpKeepItemBackImage[10] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\Vampiric_back_EX.bmp");
	lpUpKeepItemBackImage[11] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\S_Reduce_back.bmp");
	lpUpKeepItemBackImage[12] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\VipInfo_back.bmp");
	lpUpKeepItemBackImage[13] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\CaravanHopy_.tga");
	lpUpKeepItemBackImage[14] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\BigHead_.tga");
	lpUpKeepItemBackImage[15] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\GiraffeHat_.png");
	lpUpKeepItemBackImage[16] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\MagicianHat_.tga");
	lpUpKeepItemBackImage[17] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\WitchHat_.tga");
	lpUpKeepItemBackImage[18] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\maskedman_.png");
	lpUpKeepItemBackImage[19] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\maskedwoman_.png");
	lpUpKeepItemBackImage[20] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\PumpkinHat_.tga");
	lpUpKeepItemBackImage[21] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\SheepHat_.png");
	lpUpKeepItemBackImage[22] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\SoccerHat_.tga");
	lpUpKeepItemBackImage[23] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\GreenXmasHat_.tga");
	lpUpKeepItemBackImage[24] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\RedXmasHat_.tga");
	lpUpKeepItemBackImage[25] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\PhoenixFire_.tga");
	lpUpKeepItemBackImage[26] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\PhoenixIce_.tga");
	lpUpKeepItemBackImage[27] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\PhoenixLightning_.tga");
	lpUpKeepItemBackImage[28] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\PhoenixHeal_.tga");
	lpUpKeepItemBackImage[29] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\easterears_.png");
	lpUpKeepItemBackImage[30] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\CaravanArma_.TGA");
	lpUpKeepItemBackImage[31] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\CaravanBuma_.TGA");
	lpUpKeepItemBackImage[32] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\CaravanCuepy_.TGA");
	lpUpKeepItemBackImage[33] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\CaravanHungky_.TGA");
	lpUpKeepItemBackImage[34] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\CaravanRabie_.TGA");
	lpUpKeepItemBackImage[35] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\CaravanTobie_.TGA");
	lpUpKeepItemBackImage[36] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\birthday_.png");
	lpUpKeepItemBackImage[37] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\BlueXmasHat_.TGA");
	lpUpKeepItemBackImage[38] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\CaravanRudolf_.TGA");

	haItemUseDelayFlag = false;
}
DWORD dwDelayTime = 0;

void cHaPremiumItem::Main()
{
	if (chaPremiumitem.haItemUseDelayFlag == true)
	{
		dwDelayTime++;
		if (dwDelayTime > 210)
		{
			chaPremiumitem.haItemUseDelayFlag = false;
			dwDelayTime = 0;
		}
	}

	int i, cnt = 0;

	for (i = 0; i < SINUPKEEPITEM_MAX; i++)
	{
		if (UpKeepItem[i].IconTime[0] < UpKeepItem[i].IconTime[1])
		{
			if (UpKeepItem[i].Visible == true)
			{
				if (UpKeepItem[i].IconTime[1] - UpKeepItem[i].IconTime[0] <= 0)
				{
					UpKeepItem[i].Visible = false;
					CheckUpKeepItem();
				}
				cnt++;

				DWORD NowTime = GetPlayTime_T();

				switch (UpKeepItem[i].TGAImageNumber)
				{
				case nsPremiumItem::THIRD_EYES:
					if (m_ThirdEyesTime > 0)
						UpKeepItem[i].IconTime[0] = NowTime;
					break;
				case nsPremiumItem::EXPUP_POTION:
					if (m_ExpUpPotionTime > 0)
						UpKeepItem[i].IconTime[0] = NowTime;
					break;
				case nsPremiumItem::VAMPIRIC_CUS:
					if (m_VampiricCuspidTime > 0)
						UpKeepItem[i].IconTime[0] = NowTime;
					break;
				case nsPremiumItem::MANA_RECHAR_P:
					if (m_ManaRechargingPTime > 0)
						UpKeepItem[i].IconTime[0] = NowTime;
					break;
				case nsPremiumItem::MIGHT_OF_AWELL:
					if (m_MightofAwellTime > 0)
						UpKeepItem[i].IconTime[0] = NowTime;
					break;
				case nsPremiumItem::MANA_REDUCE_P:
					if (m_ManaReducePotiontime > 0)
						UpKeepItem[i].IconTime[0] = NowTime;
					break;
				case nsPremiumItem::HELP_PET_TERRY:
				case nsPremiumItem::HELP_PET_NEPSYS:
				case nsPremiumItem::HELP_PET_IO:
				case nsPremiumItem::HELP_PET_MUTE:
					if (m_HelpPetTime > 0)
						UpKeepItem[i].IconTime[0] = NowTime;
					break;
				case nsPremiumItem::STAMINA_REDUCE_P:
					if (m_StaminaReducePotiontime > 0)
						UpKeepItem[i].IconTime[0] = NowTime;
					break;
				case nsPremiumItem::VIP_INFO:
					if (m_VipInfoTime > 0)
						UpKeepItem[i].IconTime[0] = NowTime;
					break;
					//¶À½ÇÊÞÒ»¼Ò
				case nsPremiumItem::CARAVAN_HOPY:
				case nsPremiumItem::CARAVAN_ARMA:
				case nsPremiumItem::CARAVAN_BUMA:
				case nsPremiumItem::CARAVAN_CUEPY:
				case nsPremiumItem::CARAVAN_HUNGKY:
				case nsPremiumItem::CARAVAN_RABIE:
				case nsPremiumItem::CARAVAN_TOBIE:
				case nsPremiumItem::CARAVAN_RUDOLF:
					if (m_Caravan_HopyTime > 0)
						UpKeepItem[i].IconTime[0] = NowTime;
					break;
				case nsPremiumItem::BIG_HEAD:
				case nsPremiumItem::BIG_GIRAFFEHAT:
				case nsPremiumItem::BIG_MAGICIANHAT:
				case nsPremiumItem::BIG_WITCHHAT:
				case nsPremiumItem::BIG_MASKEDMAN:
				case nsPremiumItem::BIG_MASKEDWOMAN:
				case nsPremiumItem::BIG_PUMPKINHAT:
				case nsPremiumItem::BIG_SHEEPHAT:
				case nsPremiumItem::BIG_SOCCERHAT:
				case nsPremiumItem::BIG_GREENXMASHAT:
				case nsPremiumItem::BIG_REDXMASHAT:
				case nsPremiumItem::BIG_EASTER:
				case nsPremiumItem::BIG_BIRTHDAY:
				case nsPremiumItem::BIG_BLUEXMASHAT:
					if (m_BigHeadTime > 0)
						UpKeepItem[i].IconTime[0] = NowTime;
					break;
				case nsPremiumItem::PHONEIX_FIRE:
				case nsPremiumItem::PHONEIX_ICE:
				case nsPremiumItem::PHONEIX_LIGHTNING:
				case nsPremiumItem::PHONEIX_HEAL:
					if (m_PhenixPetTime > 0)
						UpKeepItem[i].IconTime[0] = NowTime;
					break;
				}
			}
		}
		else
			UpKeepItem[i].Visible = false;
		if (UpKeepItem[i].Visible == true)
		{
			if (UpKeepItem[i].PosiY > ItemUseLeftPosi[cnt - 1][1])
				UpKeepItem[i].PosiY -= 1;
			else
			{
				UpKeepItem[i].PosiY = ItemUseLeftPosi[cnt - 1][1];
				UpKeepItem[i].PosiX = ItemUseLeftPosi[cnt - 1][0];
			}
			if (pCursorPos.x > UpKeepItem[i].PosiX && pCursorPos.x < UpKeepItem[i].PosiX + 30 && pCursorPos.y > UpKeepItem[i].PosiY && pCursorPos.y < UpKeepItem[i].PosiY + 30)
				UpKeepItem[i].Infoflag = true;
			else
				UpKeepItem[i].Infoflag = false;
		}
	}
	switch (Using_ItemKind)
	{
	case 8:
		if (pCursorPos.x > 100 && pCursorPos.x < 100 + 20 && pCursorPos.y > 365 && pCursorPos.y < 365 + 20)
			TelePortCore.PageButtonFlag[0] = 1;
		else if (pCursorPos.x > 330 && pCursorPos.x < 330 + 20 && pCursorPos.y > 365 && pCursorPos.y < 365 + 20)
			TelePortCore.PageButtonFlag[1] = 1;
		else
		{
			TelePortCore.PageButtonFlag[0] = 0;
			TelePortCore.PageButtonFlag[1] = 0;
		}
		break;
	}
}
void cHaPremiumItem::Draw()
{
	switch (Using_ItemKind)
	{
	case 8:
		if (TelePortCore.PageButtonFlag[0])
			DrawSprite(100, 365, chaQuest.lpQuestButtonImage[2], 0, 0, 20, 20);
		else
			DrawSprite(100, 365, chaQuest.lpQuestButtonImage[0], 0, 0, 20, 20);
		if (TelePortCore.PageButtonFlag[1])
			DrawSprite(330, 365, chaQuest.lpQuestButtonImage[3], 0, 0, 20, 20);
		else
			DrawSprite(330, 365, chaQuest.lpQuestButtonImage[1], 0, 0, 20, 20);
	}
}

DWORD dwKeepItemTime[6] = { 0, SINITEM_TIME_1HOURS, SINITEM_TIME_3HOURS, SINITEM_TIME_ONEDAY, SINITEM_TIME_SEVENDAY, SINITEM_TIME_30DAY };

int  cHaPremiumItem::CheckTime(DWORD CurrentTime)
{
	for (int i = 0; i < 5; i++)
	{
		if (dwKeepItemTime[i] < CurrentTime  &&  CurrentTime < dwKeepItemTime[i + 1])
			return i + 1;
	}

	return false;
}
void cHaPremiumItem::DrawUp()
{
	int i;
	for (i = 0; i < SINUPKEEPITEM_MAX; i++)
	{
		if (UpKeepItem[i].Visible == true)
		{
			dsDrawTexImage(UpKeepItemTGAImage[UpKeepItem[i].TGAImageNumber - 1], UpKeepItem[i].PosiX, UpKeepItem[i].PosiY, 32, 32, UpKeepItem[i].Alpha);

			int    MinLen = 0;
			DWORD  dwCurrentTime = UpKeepItem[i].IconTime[1] - UpKeepItem[i].IconTime[0];
			switch (UpKeepItem[i].TGAImageNumber)
			{
			case nsPremiumItem::THIRD_EYES:
				switch (CheckTime(dwCurrentTime))
				{
				case 1:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_1HOURS / 32));
					break;
				case 2:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_3HOURS / 32));
					break;
				case 3:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_ONEDAY / 32));
					break;
				case 4:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_SEVENDAY / 32));
					break;
				case 5:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_30DAY / 32));
					break;
				}
				if (dwCurrentTime <= 0)
					m_ThirdEyesTime = 0;
				break;
			case nsPremiumItem::EXPUP_POTION:
				switch (CheckTime(dwCurrentTime))
				{
				case 1:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_1HOURS / 32));
					break;
				case 2:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_3HOURS / 32));
					break;
				case 3:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_ONEDAY / 32));
					break;
				case 4:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_SEVENDAY / 32));
					break;
				case 5:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_30DAY / 32));
					break;
				}
				if (dwCurrentTime <= 0)
					m_ExpUpPotionTime = 0;
				break;
			case nsPremiumItem::MIGHT_OF_AWELL:
				switch (CheckTime(dwCurrentTime))
				{
				case 1:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_1HOURS / 32));
					break;
				case 2:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_3HOURS / 32));
					break;
				case 3:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_ONEDAY / 32));
					break;
				case 4:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_SEVENDAY / 32));
					break;
				case 5:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_30DAY / 32));
					break;
				}
				break;
			case nsPremiumItem::MANA_REDUCE_P:
				switch (CheckTime(dwCurrentTime))
				{
				case 1:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_1HOURS / 32));
					break;
				case 2:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_3HOURS / 32));
					break;
				case 3:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_ONEDAY / 32));
					break;
				case 4:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_SEVENDAY / 32));
					break;
				case 5:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_30DAY / 32));
					break;
				}
				if (dwCurrentTime <= 0)
				{
					m_ManaReducePotiontime = 0;
					m_ManaReducePotionValue = 0;
				}
				break;
			case nsPremiumItem::VAMPIRIC_CUS:
				switch (CheckTime(dwCurrentTime))
				{
				case 1:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_1HOURS / 32));
					break;
				case 2:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_3HOURS / 32));
					break;
				case 3:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_ONEDAY / 32));
					break;
				case 4:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_SEVENDAY / 32));
					break;
				case 5:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_30DAY / 32));
					break;
				}
				if (dwCurrentTime <= 0)
					m_VampiricCuspidTime = 0;
				break;
			case nsPremiumItem::MANA_RECHAR_P:
				switch (CheckTime(dwCurrentTime))
				{
				case 1:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_1HOURS / 32));
					break;
				case 2:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_3HOURS / 32));
					break;
				case 3:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_ONEDAY / 32));
					break;
				case 4:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_SEVENDAY / 32));
					break;
				case 5:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_30DAY / 32));
					break;
				}
				if (dwCurrentTime <= 0)
					m_ManaRechargingPTime = 0;
				break;
			case nsPremiumItem::STAMINA_REDUCE_P:
				switch (CheckTime(dwCurrentTime))
				{
				case 1:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_1HOURS / 32));
					break;
				case 2:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_3HOURS / 32));
					break;
				case 3:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_ONEDAY / 32));
					break;
				case 4:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_SEVENDAY / 32));
					break;
				case 5:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_30DAY / 32));
					break;
				}
				if (dwCurrentTime <= 0)
				{
					m_StaminaReducePotiontime = 0;
					m_StaminaReducePotionValue = 0;
				}
				break;
			case nsPremiumItem::VIP_INFO:
				switch (CheckTime(dwCurrentTime))
				{
				case 1:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_1HOURS / 32));
					break;
				case 2:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_3HOURS / 32));
					break;
				case 3:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_ONEDAY / 32));
					break;
				case 4:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_SEVENDAY / 32));
					break;
				case 5:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_30DAY / 32));
					break;
				}
				if (dwCurrentTime <= 0)
					m_VipInfoTime = 0;
				break;
			case nsPremiumItem::CARAVAN_HOPY:
			case nsPremiumItem::CARAVAN_ARMA:
			case nsPremiumItem::CARAVAN_BUMA:
			case nsPremiumItem::CARAVAN_CUEPY:
			case nsPremiumItem::CARAVAN_HUNGKY:
			case nsPremiumItem::CARAVAN_RABIE:
			case nsPremiumItem::CARAVAN_TOBIE:
			case nsPremiumItem::CARAVAN_RUDOLF:
				switch (CheckTime(dwCurrentTime))
				{
				case 1:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_1HOURS / 32));
					break;
				case 2:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_3HOURS / 32));
					break;
				case 3:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_ONEDAY / 32));
					break;
				case 4:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_SEVENDAY / 32));
					break;
				case 5:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_30DAY / 32));
					break;
				}
				if (dwCurrentTime <= 0)
					m_Caravan_HopyTime = 0;
				break;
			case nsPremiumItem::BIG_HEAD:
			case nsPremiumItem::BIG_GIRAFFEHAT:
			case nsPremiumItem::BIG_MAGICIANHAT:
			case nsPremiumItem::BIG_WITCHHAT:
			case nsPremiumItem::BIG_MASKEDMAN:
			case nsPremiumItem::BIG_MASKEDWOMAN:
			case nsPremiumItem::BIG_PUMPKINHAT:
			case nsPremiumItem::BIG_SHEEPHAT:
			case nsPremiumItem::BIG_SOCCERHAT:
			case nsPremiumItem::BIG_GREENXMASHAT:
			case nsPremiumItem::BIG_REDXMASHAT:
			case nsPremiumItem::BIG_EASTER:
			case nsPremiumItem::BIG_BIRTHDAY:
			case nsPremiumItem::BIG_BLUEXMASHAT:
				switch (CheckTime(dwCurrentTime))
				{
				case 1:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_1HOURS / 32));
					break;
				case 2:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_3HOURS / 32));
					break;
				case 3:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_ONEDAY / 32));
					break;
				case 4:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_SEVENDAY / 32));
					break;
				case 5:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_30DAY / 32));
					break;
				}
				if (dwCurrentTime <= 0)
					m_BigHeadTime = 0;
				break;
			case nsPremiumItem::PHONEIX_FIRE:
			case nsPremiumItem::PHONEIX_ICE:
			case nsPremiumItem::PHONEIX_LIGHTNING:
			case nsPremiumItem::PHONEIX_HEAL:
				switch (CheckTime(dwCurrentTime))
				{
				case 1:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_1HOURS / 32));
					break;
				case 2:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_3HOURS / 32));
					break;
				case 3:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_ONEDAY / 32));
					break;
				case 4:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_SEVENDAY / 32));
					break;
				case 5:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_30DAY / 32));
					break;
				}
				if (dwCurrentTime <= 0)
					m_PhenixPetTime = 0;
				break;
			}
			//10Ãë
			if (UpKeepItem[i].IconTime[1] - UpKeepItem[i].IconTime[0] <= 10)
			{
				if (UpKeepItem[i].TGAImageNumber == nsPremiumItem::HELP_PET_TERRY || UpKeepItem[i].TGAImageNumber == nsPremiumItem::HELP_PET_NEPSYS || UpKeepItem[i].TGAImageNumber == nsPremiumItem::HELP_PET_IO || UpKeepItem[i].TGAImageNumber == nsPremiumItem::HELP_PET_MUTE)
				{
					if (UpKeepItem[i].IconTime[1] - UpKeepItem[i].IconTime[0] <= 0)
					{
						chaPremiumitem.UpKeepItem[i].PosiX = 0;
						chaPremiumitem.UpKeepItem[i].PosiY = 0;
						chaPremiumitem.UpKeepItem[i].Visible = false;
						chaPremiumitem.UpKeepItem[i].TGAImageNumber = 0;
						chaPremiumitem.UpKeepItem[i].IconTime[0] = 0;
						chaPremiumitem.UpKeepItem[i].IconTime[1] = 0;
						chaPremiumitem.UpKeepItem[i].Alpha = 255;
						chaPremiumitem.UpKeepItem[i].Alphakind = 0;
						chaPremiumitem.UpKeepItem[i].Per = 0;
						ZeroMemory(chaPremiumitem.UpKeepItem[i].Id, sizeof(chaPremiumitem.UpKeepItem[i].Id));

						m_HelpPetTime = 0;

						sinChar->GravityScroolCheck[1] = 0;
						cHelpPet.ClosePet();
					}
				}
				else
				{
					chaPremiumitem.UpKeepItem[i].PosiX = 0;
					chaPremiumitem.UpKeepItem[i].PosiY = 0;
					chaPremiumitem.UpKeepItem[i].Visible = false;
					chaPremiumitem.UpKeepItem[i].TGAImageNumber = 0;
					chaPremiumitem.UpKeepItem[i].IconTime[0] = 0;
					chaPremiumitem.UpKeepItem[i].IconTime[1] = 0;
					chaPremiumitem.UpKeepItem[i].Alpha = 255;
					chaPremiumitem.UpKeepItem[i].Alphakind = 0;
					chaPremiumitem.UpKeepItem[i].Per = 0;
					ZeroMemory(chaPremiumitem.UpKeepItem[i].Id, sizeof(chaPremiumitem.UpKeepItem[i].Id));
				}

				if (UpKeepItem[i].Alpha == 255)
					UpKeepItem[i].Alphakind = 1;
				if (UpKeepItem[i].Alpha == 50)
					UpKeepItem[i].Alphakind = 2;
			}
			else
			{
				if (UpKeepItem[i].Alpha == 0)
					UpKeepItem[i].Alphakind = 0;
			}
			if (UpKeepItem[i].Alphakind == 0)
				DrawSprite(UpKeepItem[i].PosiX, UpKeepItem[i].PosiY + (32 - MinLen), lpUpKeepItemBackImage[UpKeepItem[i].TGAImageNumber - 1], 0, 32 - MinLen, 32, 32);

			switch (UpKeepItem[i].Alphakind)
			{
			case 0:
				if (UpKeepItem[i].Alpha < 255)
					UpKeepItem[i].Alpha++;
				else
					UpKeepItem[i].Alpha = 255;
				break;
			case 1:
				if (UpKeepItem[i].Alpha > 50)
					UpKeepItem[i].Alpha -= 5;
				else
					UpKeepItem[i].Alpha = 50;
				break;
			case 2:
				if (UpKeepItem[i].Alpha < 255)
					UpKeepItem[i].Alpha += 5;
				else
					UpKeepItem[i].Alpha = 255;
				break;
			}
		}
	}
}
void cHaPremiumItem::LButtonDown(int x, int y)
{
	if (TelePortCore.PageButtonFlag[1])
	{
		if (TelePortCore.PageIndex < 3)
			TelePortCore.PageIndex++;
		cSinHelp.sinShowHelp(SIN_HELP_KIND_TELEPORT_SCROLL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), haTeleport_Field[TelePortCore.PageIndex]);
	}
	if (TelePortCore.PageButtonFlag[0])
	{
		if (0 < TelePortCore.PageIndex)
			TelePortCore.PageIndex--;
		cSinHelp.sinShowHelp(SIN_HELP_KIND_TELEPORT_SCROLL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), haTeleport_Field[TelePortCore.PageIndex]);
	}
}
void cHaPremiumItem::LButtonUp(int x, int y)
{

}
DWORD dwPremiumItemCode[] = { (sinBI1 | sin01),(sinBI1 | sin02),(sinBI1 | sin03),(sinBI1 | sin04),(sinBI1 | sin05),(sinBI1 | sin06),(sinBI1 | sin07) };

int cHaPremiumItem::UsePremiumItem(int kind)
{
	Using_ItemKind = 0;
	switch (kind)
	{
	case 1:
		cCharStatus.InitCharStatus(1);
		cInvenTory.SetItemToChar();
		if (sinChar->sHP.sMax < sinGetLife())
		{
			sinSetLife(sinChar->sHP.sMax);
			ReformCharForm();
			ResetEnergyGraph(4);
		}
		haCastleSkillUseFlag = 1;
		break;
	case 2:
		cSkill.InitSkillPoint(1);
		haCastleSkillUseFlag = 1;
		break;
	case 3:
		cSkill.InitSkillPoint(1);
		cCharStatus.InitCharStatus(1);
		cInvenTory.SetItemToChar();
		if (sinChar->sHP.sMax < sinGetLife())
		{
			sinSetLife(sinChar->sHP.sMax);
			ReformCharForm();
			ResetEnergyGraph(4);
		}
		haCastleSkillUseFlag = 1;
		break;
	case 5:
		SetPremiumItemSkill(1);
		cInvenTory.SetItemToChar();
		break;
	case 6:
		SetPremiumItemSkill(2);
		break;
	case 7:
		SetPremiumItemSkill(3);
		break;
	case 8:
		if (!CheckWindowOpen())
			break;
		Using_ItemKind = kind;
		cSinHelp.sinShowHelp(SIN_HELP_KIND_TELEPORT_SCROLL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), haTeleport_Field[TelePortCore.PageIndex]);
		haCastleSkillUseFlag = 0;
		HelpBoxKindIndex = 0;
		break;
	case 9:
		haCastleSkillUseFlag = 1;
		break;
	case 10:
	case 11:
		haCastleSkillUseFlag = 0;
		break;
	case 12:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::THIRD_EYES, SINITEM_TIME_ONEDAY, true, "Third Eye", 50);
		break;
	case 13:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_ONEDAY, true, "EXP Potion", 30);
		break;
	case 14:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::THIRD_EYES, SINITEM_TIME_SEVENDAY, true, "Third Eye", 50);
		break;
	case 15:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_SEVENDAY, true, "EXP Potion", 30);
		break;
	case 16:
		if (UseHairtintPotion(1))
			haCastleSkillUseFlag = 1;
		break;
	case 17:
		if (UseHairtintPotion(2))
			haCastleSkillUseFlag = 1;
		break;
	case 18:
		if (UseHairtintPotion(3))
			haCastleSkillUseFlag = 1;
		break;
	case 19:
		haCastleSkillUseFlag = 1;
		break;
	case 20:
		haCastleSkillUseFlag = 1;
		break;
	case 21:
		haCastleSkillUseFlag = 1;
		break;
	case 22:
		haCastleSkillUseFlag = 1;
		break;
	case 23:
		haCastleSkillUseFlag = 1;
		break;
	case 24:
		haCastleSkillUseFlag = 1;
		if (SetUpKeepItem(nsPremiumItem::THIRD_EYES, SINITEM_TIME_3HOURS, true, "Third Eye", 20, 1))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_3HOURS, true, "EXP Potion", 10);
		break;
	case 25:
		haCastleSkillUseFlag = 1;
		if (SetUpKeepItem(nsPremiumItem::THIRD_EYES, SINITEM_TIME_ONEDAY, true, "Third Eye", 20, 1))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_ONEDAY, true, "EXP Potion", 10);
		break;
	case 26:
		haCastleSkillUseFlag = 1;
		if (SetUpKeepItem(nsPremiumItem::THIRD_EYES, SINITEM_TIME_SEVENDAY, true, "Third Eye", 20, 1))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_SEVENDAY, true, "EXP Potion", 10);
		break;
	case 27:
		haCastleSkillUseFlag = 1;
		if (SetUpKeepItem(nsPremiumItem::THIRD_EYES, SINITEM_TIME_30DAY, true, "Third Eye", 20, 1))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_30DAY, true, "EXP Potion", 10);
		break;
	case 28:
		haCastleSkillUseFlag = 1;
		if (SetUpKeepItem(nsPremiumItem::THIRD_EYES, SINITEM_TIME_3HOURS, true, "Third Eye", 30, 1))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_3HOURS, true, "EXP Potion", 20);
		break;
	case 29:
		haCastleSkillUseFlag = 1;
		if (SetUpKeepItem(nsPremiumItem::THIRD_EYES, SINITEM_TIME_ONEDAY, true, "Third Eye", 30, 1))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_ONEDAY, true, "EXP Potion", 20);
		break;
	case 30:
		haCastleSkillUseFlag = 1;
		if (SetUpKeepItem(nsPremiumItem::THIRD_EYES, SINITEM_TIME_SEVENDAY, true, "Third Eye", 30, 1))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_SEVENDAY, true, "EXP Potion", 20);
		break;
	case 31:
		haCastleSkillUseFlag = 1;
		if (SetUpKeepItem(nsPremiumItem::THIRD_EYES, SINITEM_TIME_30DAY, true, "Third Eye", 30, 1))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_30DAY, true, "EXP Potion", 20);
		break;
	case 32:
		haCastleSkillUseFlag = 1;
		if (SetUpKeepItem(nsPremiumItem::THIRD_EYES, SINITEM_TIME_3HOURS, true, "Third Eye", 40, 1))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_3HOURS, true, "EXP Potion", 30);
		break;
	case 33:
		haCastleSkillUseFlag = 1;
		if (SetUpKeepItem(nsPremiumItem::THIRD_EYES, SINITEM_TIME_ONEDAY, true, "Third Eye", 40, 1))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_ONEDAY, true, "EXP Potion", 30);
		break;
	case 34:
		haCastleSkillUseFlag = 1;
		if (SetUpKeepItem(nsPremiumItem::THIRD_EYES, SINITEM_TIME_SEVENDAY, true, "Third Eye", 40, 1))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_SEVENDAY, true, "EXP Potion", 30);
		break;
	case 35:
		haCastleSkillUseFlag = 1;
		if (SetUpKeepItem(nsPremiumItem::THIRD_EYES, SINITEM_TIME_30DAY, true, "Third Eye", 40, 1))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_30DAY, true, "EXP Potion", 30);
		break;
	case 36:
		if (UseHairtintPotion(4))
			haCastleSkillUseFlag = 1;
		break;
	case 37:
		if (UseHairtintPotion(5))
			haCastleSkillUseFlag = 1;
		break;
	case 38:
		if (UseHairtintPotion(6))
			haCastleSkillUseFlag = 1;
		break;
	case 39:
		if (UseHairtintPotion(7))
			haCastleSkillUseFlag = 1;
		break;
	case 40:
		if (UseHairtintPotion(8))
			haCastleSkillUseFlag = 1;
		break;
	case 41:
		if (UseHairtintPotion(9))
			haCastleSkillUseFlag = 1;
		break;
	case 42:
		if (UseHairtintPotion(10))
			haCastleSkillUseFlag = 1;
		break;
	case 43:
		if (UseHairtintPotion(11))
			haCastleSkillUseFlag = 1;
		break;
	case 44:
		if (UseHairtintPotion(12))
			haCastleSkillUseFlag = 1;
		break;
	case 45:
		if (UseHairtintPotion(13))
			haCastleSkillUseFlag = 1;
		break;
	case 46:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_ONEDAY, true, "EXP Potion", 50);
		break;
	case 47:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_SEVENDAY, true, "EXP Potion", 50);
		break;
	case 48:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::MIGHT_OF_AWELL, SINITEM_TIME_SEVENDAY, true, "Might of Awell", 300);
		break;
	case 49:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::MIGHT_OF_AWELL, SINITEM_TIME_30DAY, true, "Might of Awell", 300);
		break;
	case 50:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, SINITEM_TIME_ONEDAY, true, "MP Down", 30);
		break;
	case 51:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, SINITEM_TIME_SEVENDAY, true, "MP Down", 30);
		break;
	case 52:
		haCastleSkillUseFlag = 1;
		if (SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, SINITEM_TIME_3HOURS, true, "MP Down", 10, 2))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_3HOURS, true, "EXP Potion", 10);
		break;
	case 53:
		haCastleSkillUseFlag = 1;
		if (SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, SINITEM_TIME_ONEDAY, true, "MP Down", 10, 2))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_ONEDAY, true, "EXP Potion", 10);
		break;
	case 54:
		haCastleSkillUseFlag = 1;
		if (SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, SINITEM_TIME_SEVENDAY, true, "MP Down", 10, 2))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_SEVENDAY, true, "EXP Potion", 10);
		break;
	case 55:
		haCastleSkillUseFlag = 1;
		if (SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, SINITEM_TIME_3HOURS, true, "MP Down", 20, 2))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_3HOURS, true, "EXP Potion", 20);
		break;
	case 56:
		haCastleSkillUseFlag = 1;
		if (SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, SINITEM_TIME_ONEDAY, true, "MP Down", 20, 2))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_ONEDAY, true, "EXP Potion", 20);
		break;
	case 57:
		haCastleSkillUseFlag = 1;
		if (SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, SINITEM_TIME_SEVENDAY, true, "MP Down", 20, 2))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_SEVENDAY, true, "EXP Potion", 20);
		break;
	case 58:
		haCastleSkillUseFlag = 1;
		if (SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, SINITEM_TIME_3HOURS, true, "MP Down", 30, 2))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_3HOURS, true, "EXP Potion", 30);
		break;
	case 59:
		haCastleSkillUseFlag = 1;
		if (SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, SINITEM_TIME_ONEDAY, true, "MP Down", 30, 2))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_ONEDAY, true, "EXP Potion", 30);
		break;
	case 60:
		haCastleSkillUseFlag = 1;
		if (SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, SINITEM_TIME_SEVENDAY, true, "MP Down", 30, 2))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_SEVENDAY, true, "EXP Potion", 30);
		break;
	case 61:
		haCastleSkillUseFlag = 1;
		if (SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, SINITEM_TIME_3HOURS, true, "MP Down", 40, 2))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_3HOURS, true, "EXP Potion", 40);
		break;
	case 62:
		haCastleSkillUseFlag = 1;
		if (SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, SINITEM_TIME_ONEDAY, true, "MP Down", 40, 2))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_ONEDAY, true, "EXP Potion", 40);
		break;
	case 63:
		haCastleSkillUseFlag = 1;
		if (SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, SINITEM_TIME_SEVENDAY, true, "MP Down", 40, 2))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_SEVENDAY, true, "EXP Potion", 40);
		break;
	case 64:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::MIGHT_OF_AWELL, SINITEM_TIME_SEVENDAY, true, "Might of Awell", 500);
		break;
	case 65:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::MIGHT_OF_AWELL, SINITEM_TIME_30DAY, true, "Might of Awell", 500);
		break;
	case 66:
		haCastleSkillUseFlag = 1;
		if (SetUpKeepItem(nsPremiumItem::THIRD_EYES, SINITEM_TIME_3HOURS, true, "Third Eye", 50, 1))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_3HOURS, true, "EXP Potion", 40);
		break;
	case 67:
		haCastleSkillUseFlag = 1;
		if (SetUpKeepItem(nsPremiumItem::THIRD_EYES, SINITEM_TIME_ONEDAY, true, "Third Eye", 50, 1))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_ONEDAY, true, "EXP Potion", 40);
		break;
	case 68:
		haCastleSkillUseFlag = 1;
		if (SetUpKeepItem(nsPremiumItem::THIRD_EYES, SINITEM_TIME_SEVENDAY, true, "Third Eye", 50, 1))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_SEVENDAY, true, "EXP Potion", 40);
		break;
	case 69:
		haCastleSkillUseFlag = 1;
		break;
	case 70:
		haCastleSkillUseFlag = 1;
		break;
	case 71:
		haCastleSkillUseFlag = 1;
		break;
	case 73:
		haCastleSkillUseFlag = 1;
		UseAgingMaster(0);
		break;
	case 74:
		haCastleSkillUseFlag = 1;
		UseAgingMaster(1);
		break;
	case 75:
		haCastleSkillUseFlag = 1;
		UseAgingMaster(2);
		break;
	case 76:
		haCastleSkillUseFlag = 1;
		UseSkillMaster(1);
		break;
	case 77:
		haCastleSkillUseFlag = 1;
		UseSkillMaster(2);
		break;
	case 78:
		haCastleSkillUseFlag = 1;
		UseSkillMaster(3);
		break;
	case 79:
		haCastleSkillUseFlag = 1;
		cInvenTory.InvenItem[Using_SelectInvenItemIndex].sItem.iPotionCount = 300;
		sinThrowItemToFeild(&cInvenTory.InvenItem[Using_SelectInvenItemIndex]);
		cInvenTory.InvenItem[Using_SelectInvenItemIndex].bValid = 0;
		cInvenTory.CheckWeight();
		cInvenTory.ReFormInvenItem();
		SaveGameData();
		UseMoveShop();
		break;
	case 80:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_ONEDAY, true, "EXP Potion", 100);
		break;
	case 81:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_SEVENDAY, true, "EXP Potion", 100);
		break;
	case 82:
		cCharStatus.InitCharStatus_Attribute(1);
		cInvenTory.SetItemToChar();
		if (sinChar->sHP.sMax < sinGetLife())
		{
			sinSetLife(sinChar->sHP.sMax);
			ReformCharForm();
			ResetEnergyGraph(4);
		}
		haCastleSkillUseFlag = 1;
		break;
	case 83:
		cCharStatus.InitCharStatus_Attribute(2);
		cInvenTory.SetItemToChar();
		if (sinChar->sHP.sMax < sinGetLife())
		{
			sinSetLife(sinChar->sHP.sMax);
			ReformCharForm();
			ResetEnergyGraph(4);
		}
		haCastleSkillUseFlag = 1;
		break;
	case 84:
		cCharStatus.InitCharStatus_Attribute(3);
		cInvenTory.SetItemToChar();
		if (sinChar->sHP.sMax < sinGetLife())
		{
			sinSetLife(sinChar->sHP.sMax);
			ReformCharForm();
			ResetEnergyGraph(4);
		}
		haCastleSkillUseFlag = 1;
		break;
	case 85:
		cCharStatus.InitCharStatus_Attribute(4);
		cInvenTory.SetItemToChar();
		if (sinChar->sHP.sMax < sinGetLife())
		{
			sinSetLife(sinChar->sHP.sMax);
			ReformCharForm();
			ResetEnergyGraph(4);
		}
		haCastleSkillUseFlag = 1;
		break;
	case 86:
		cCharStatus.InitCharStatus_Attribute(5);
		cInvenTory.SetItemToChar();
		if (sinChar->sHP.sMax < sinGetLife())
		{
			sinSetLife(sinChar->sHP.sMax);
			ReformCharForm();
			ResetEnergyGraph(4);
		}
		haCastleSkillUseFlag = 1;
		break;
	case 87:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_30DAY, true, "EXP Potion", 100);
		break;
	case 88:
		haCastleSkillUseFlag = 1;
		break;
	case 97:
	case 98:
		haCastleSkillUseFlag = 0;
		break;
	case 99:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::HELP_PET_TERRY, SINITEM_TIME_30DAY, true, "Dragon Pet", 30, 3);
		sinChar->GravityScroolCheck[1] = 1;
		break;
	case 100:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::HELP_PET_NEPSYS, SINITEM_TIME_30DAY, true, "Dragon Pet", 30, 3);
		break;
	case 101:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::HELP_PET_IO, SINITEM_TIME_30DAY, true, "Dragon Pet", 30, 3);
		break;
	case 102:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::HELP_PET_MUTE, SINITEM_TIME_30DAY, true, "Dragon Pet", 30, 3);
		sinChar->GravityScroolCheck[1] = 2;
		break;
	case 103:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::HELP_PET_TERRY, SINITEM_TIME_ONEDAY, true, "Dragon Pet", 30, 3);
		sinChar->GravityScroolCheck[1] = 1;
		break;
	case 104:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::HELP_PET_NEPSYS, SINITEM_TIME_ONEDAY, true, "Dragon Pet", 30, 3);
		break;
	case 105:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::HELP_PET_IO, SINITEM_TIME_ONEDAY, true, "Dragon Pet", 30, 3);
		break;
	case 106:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::HELP_PET_MUTE, SINITEM_TIME_ONEDAY, true, "Dragon Pet", 30, 3);
		sinChar->GravityScroolCheck[1] = 2;
		break;
	case 107:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_1HOURS, true, "EXP Potion", 100);
		break;
	case 108:
		haCastleSkillUseFlag = 1;
		break;
	case 109:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::HELP_PET_TERRY, SINITEM_TIME_SEVENDAY, true, "Dragon Pet", 30, 3);
		sinChar->GravityScroolCheck[1] = 1;
		break;
	case 110:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::HELP_PET_NEPSYS, SINITEM_TIME_SEVENDAY, true, "Dragon Pet", 30, 3);
		break;
	case 111:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::HELP_PET_IO, SINITEM_TIME_SEVENDAY, true, "Dragon Pet", 30, 3);
		break;
	case 112:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::HELP_PET_MUTE, SINITEM_TIME_SEVENDAY, true, "Dragon Pet", 30, 3);
		sinChar->GravityScroolCheck[1] = 2;
		break;
	case 113:
		haCastleSkillUseFlag = 1;
		UseAgingMaster(3);
		break;
	case 114:
		haCastleSkillUseFlag = 1;
		UseAgingMaster(4);
		break;
	case 115:
		haCastleSkillUseFlag = 1;
		UseAgingMaster(5);
		break;
	case 116:
		if (sinChar->GravityScroolCheck[0] == 5)
		{
			cMessageBox.ShowMessage(MESSAGE_GRAVITYSCROOLFAIL);
			return FALSE;
		}
		cMessageBox.ShowMessage(MESSAGE_GRAVITYSCROOLOK);
		sinChar->GravityScroolCheck[0] += 1;
		cCharStatus.UseGravityScrool();
		cInvenTory.SetItemToChar();
		ReformCharForm();
		haCastleSkillUseFlag = 1;
		break;
	case 117:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::HELP_PET_TERRY, SINITEM_TIME_1HOURS, true, "Dragon Pet", 30, 3);
		sinChar->GravityScroolCheck[1] = 1;
		break;
	case 118:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::HELP_PET_NEPSYS, SINITEM_TIME_1HOURS, true, "Dragon Pet", 30, 3);
		break;
	case 119:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::HELP_PET_IO, SINITEM_TIME_1HOURS, true, "Dragon Pet", 30, 3);
		break;
	case 120:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::HELP_PET_MUTE, SINITEM_TIME_1HOURS, true, "Dragon Pet", 30, 3);
		sinChar->GravityScroolCheck[1] = 2;
		break;
	case 121:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::THIRD_EYES, SINITEM_TIME_1HOURS, true, "Third Eye", 50);
		break;
	case 122:
		haCastleSkillUseFlag = 0;
		break;
	case 123:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_1HOURS, true, "EXP Potion", 50);
		break;
	case 124:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::VAMPIRIC_CUS, SINITEM_TIME_1HOURS, true, "Vampire Teeth");
		m_VampiricCuspidTime = SINITEM_TIME_1HOURS;
		break;
	case 125:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::MANA_RECHAR_P, SINITEM_TIME_1HOURS, true, "Mana Aura");
		m_ManaRechargingPTime = SINITEM_TIME_1HOURS;
		break;
	case 126:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, SINITEM_TIME_1HOURS, true, "MP Down", 30);
		break;
	case 127:
		haCastleSkillUseFlag = 1;
		break;
	case 128:
		haCastleSkillUseFlag = 1;
		break;
	case 129:
		haCastleSkillUseFlag = 1;
		break;
	case 130:
		haCastleSkillUseFlag = 0;
		break;
	case 131:
		haCastleSkillUseFlag = 0;
		break;
	case 132:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::STAMINA_REDUCE_P, SINITEM_TIME_ONEDAY, true, "SP Down", 30);
		break;
	case 133:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::STAMINA_REDUCE_P, SINITEM_TIME_SEVENDAY, true, "SP Down", 30);
		break;
	case 136:
		haCastleSkillUseFlag = 1;
		break;
	case 137:
		haCastleSkillUseFlag = 1;
		break;
	case 138:
		if (UseHairtintPotion(14))
			haCastleSkillUseFlag = 1;
		break;
	case 139:
		if (UseHairtintPotion(15))
			haCastleSkillUseFlag = 1;
		break;
	case 140:
		if (UseHairtintPotion(16))
			haCastleSkillUseFlag = 1;
		break;
	case 141:
		if (UseHairtintPotion(17))
			haCastleSkillUseFlag = 1;
		break;
	case 142:
		if (UseHairtintPotion(18))
			haCastleSkillUseFlag = 1;
		break;
	case 143:
		if (UseHairtintPotion(19))
			haCastleSkillUseFlag = 1;
		break;
	case 144:
		if (UseHairtintPotion(20))
			haCastleSkillUseFlag = 1;
		break;
	case 145:
		if (CheckChangeJob(sinChar) == FALSE)
			cMessageBox.ShowMessageEvent("Highest Rank already reached!      ");
		else
		{
			auto ps = GetCharacterClassData(sinChar->iClass, sinChar->iRank + 1);

			if (ps)
			{
				cMessageBox.ShowMessage3(MESSAGE_LEVEL_JOB, ps->pszName);
			}
		}
		haCastleSkillUseFlag = 0;
		break;
	case 146:
		if (sinFruitStatus[0] < sinFruitStatus[1])
			cMessageBox.ShowMessage3(MESSAGE_FRUIT, cInvenTory.InvenItem[TelePortCore.ItemIndex].sItem.szItemName);
		else
			cMessageBox.ShowMessageEvent("Unable to use more fruits      ");
		haCastleSkillUseFlag = 0;
		break;
	case 147:
		haCastleSkillUseFlag = 0;
		break;
	case 148:
		haCastleSkillUseFlag = 1;
		break;
	}
	return TRUE;
}
int cHaPremiumItem::SetPremiumItemSkill(int kind)
{
	haCastleSkillUseFlag = 0;
	DWORD SkillCODE;
	int   SkillTime;

	switch (kind)
	{
	case 1:
		SkillCODE = SCROLL_P_INVULNERABILITY;
		SkillTime = 30;
		break;
	case 2:
		SkillCODE = SCROLL_P_CRITICAL;
		SkillTime = 60 * 60;
		break;
	case 3:
		SkillCODE = SCROLL_P_EVASION;
		SkillTime = 60 * 60;
		break;
	}
	sSKILL TempSkill;

	if (cSkill.SearchContiueSkillCODE(SkillCODE) == SkillCODE && SkillCODE != 0)
	{
		cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
		haCastleSkillUseFlag = 0;
		return TRUE;
	}
	haCastleSkillUseFlag = 1;

	for (int j = 0; j < SIN_MAX_SKILL; j++)
	{
		if (sSkill[j].CODE == SkillCODE)
		{
			memcpy(&TempSkill, &sSkill[j], sizeof(sSKILL));
			TempSkill.UseTime = SkillTime;
			sinContinueSkillSet(&TempSkill);
			SwitchSkill(&TempSkill);
			break;
		}
	}
	return TRUE;
}
// ´«ËÍ¾íÖá
int cHaPremiumItem::UseTeleportScrollItem(short ItemIndex)
{
	if (chaPremiumitem.TelePortCore.FieldIndex[1] == FALSE)
		return FALSE;

	if (STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapType == MAPTYPE_ChessRoom)
	{
		cMessageBox.ShowMessage(MESSAGE_NO_USE_ITEM);
		return FALSE;
	}
	for (int i = 0; i < TELEPORT_FIELDMAX; i++)
	{
		if ((chaPremiumitem.TelePortCore.FieldIndex[1] - 1) == TelePort_FieldNum[i][0])
		{
			if (TelePort_FieldNum[i][2] <= sinChar->iLevel)
			{
				GAMEMAP->LoadWarpMap((EMapID)TelePort_FieldNum[i][1]);
				cInvenTory.InvenItem[chaPremiumitem.TelePortCore.ItemIndex].sItem.iPotionCount = 300;
				sinThrowItemToFeild(&cInvenTory.InvenItem[chaPremiumitem.TelePortCore.ItemIndex]);
				cInvenTory.InvenItem[chaPremiumitem.TelePortCore.ItemIndex].bValid = 0;
				cInvenTory.CheckWeight();
				cInvenTory.ReFormInvenItem();
			}
			else
				cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_LEVEL);
		}
	}
	return TRUE;
}
int cHaPremiumItem::UseChangeJobItem()
{
	if (sinChar->iRank < 4)
	{
		cInvenTory.InvenItem[chaPremiumitem.TelePortCore.ItemIndex].sItem.iPotionCount = 300;
		sinThrowItemToFeild(&cInvenTory.InvenItem[chaPremiumitem.TelePortCore.ItemIndex]);
		cInvenTory.CheckWeight();
		cInvenTory.ReFormInvenItem();
		SaveGameData();
	}
	return FALSE;
}
int cHaPremiumItem::UseFruitItem()
{
	cInvenTory.InvenItem[TelePortCore.ItemIndex].sItem.iPotionCount = 300;
	sinThrowItemToFeild(&cInvenTory.InvenItem[TelePortCore.ItemIndex]);
	cInvenTory.CheckWeight();
	cInvenTory.ReFormInvenItem();
	SaveGameData();
	return TRUE;
}
int cHaPremiumItem::CheckWindowOpen()
{
	haCastleSkillUseFlag = 0;
	if (cWareHouse.OpenFlag)
		return false;
	if (cTrade.OpenFlag)
		return false;
	if (cShop.OpenFlag)
		return false;
	if (cAging.OpenFlag)
		return false;
	if (cCraftItem.OpenFlag)
		return false;
	if (sSinWarpGate.ShowFlag)
		return false;
	if (cSinHelp.NPCTeleportFlag)
		return false;
	if (isDrawClanMenu)
		return false;
	if (haMovieFlag)
		return false;
	if (SmeltingItem.OpenFlag)
		return false;
	if (ManufactureItem.m_OpenFlag)
		return false;
	if (cMixtureReset.OpenFlag)
		return false;
	if (cElement.OpenFlag)
		return false;
	if (cCaravan.OpenFlag)
		return false;
	if (cSocket.OpenFlag)
		return false;
	return true;
}
int cHaPremiumItem::CheckUpKeepItem()
{
	int i;
	for (i = 0; i < SINUPKEEPITEM_MAX; i++)
	{
		if (UpKeepItem[i].Visible == false)
		{
			if (UpKeepItem[i + 1].Visible == true)
			{
				memcpy(&UpKeepItem[i], &UpKeepItem[i + 1], sizeof(sUpKeepItem));
				UpKeepItem[i + 1].Visible = false;
				break;
			}
		}
	}
	return true;
}

int cHaPremiumItem::SetUpKeepItem(int kind, DWORD dwTime, bool visible, char* id, int Percent, short ItemType)
{
	haCastleSkillUseFlag = 0;
	int i;

	for (i = 0; i < SINUPKEEPITEM_MAX; i++)
	{
		if (UpKeepItem[i].Visible == false)
		{
			UpKeepItem[i].TGAImageNumber = kind;
			UpKeepItem[i].Visible = true;
			UpKeepItem[i].IconTime[0] = 1;
			UpKeepItem[i].IconTime[1] = GetPlayTime_T() + dwTime;
			UpKeepItem[i].Alpha = 0;
			UpKeepItem[i].Alphakind = 0;
			UpKeepItem[i].Per = Percent;

			lstrcpy(UpKeepItem[i].Id, id);
			haCastleSkillUseFlag = 1;
			return TRUE;
		}
		else
		{
			switch (ItemType)
			{
			case 0:
				if (UpKeepItem[i].TGAImageNumber == kind)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					haCastleSkillUseFlag = 0;
					return FALSE;
				}
				break;
			case 1:
				for (int j = 0; j < SINUPKEEPITEM_MAX; j++)
				{
					if (UpKeepItem[j].TGAImageNumber == THIRD_EYES || UpKeepItem[j].TGAImageNumber == EXPUP_POTION)
					{
						cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
						haCastleSkillUseFlag = 0;
						return  FALSE;
					}
				}
				break;
			case 2:
				for (int j = 0; j < SINUPKEEPITEM_MAX; j++)
				{
					if (UpKeepItem[j].TGAImageNumber == MANA_REDUCE_P || UpKeepItem[j].TGAImageNumber == EXPUP_POTION)
					{
						cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
						haCastleSkillUseFlag = 0;
						return  FALSE;
					}
				}
				break;
			case 3:
				for (int j = 0; j < SINUPKEEPITEM_MAX; j++)
				{
					if (cHelpPet.PetShow == 1)
					{
						cMessageBox.ShowMessage(MESSAGE_ASATTRIBUTE_USE);
						haCastleSkillUseFlag = 0;
						return  FALSE;
					}
				}
				break;
			}
		}
	}
	return TRUE;
}
void cHaPremiumItem::InfoBox(int PoisX, int PosiY, int Width, int Height)
{
	int i, j;
	for (i = 0; i < Width; i++)
	{
		for (j = 0; j < Height; j++)
		{
			if (i == 0 && j == 0)
				dsDrawTexImage(cItem.MatItemInfoBox_TopLeft, PoisX + (i * 16), PosiY + (j * 16), 16, 16, 255);
			if (j == 0 && i != 0 && i + 1 < Width)
				dsDrawTexImage(cItem.MatItemInfoBox_TopCenter, PoisX + (i * 16), PosiY + (j * 16), 16, 16, 255);
			if (j == 0 && i + 1 == Width)
				dsDrawTexImage(cItem.MatItemInfoBox_TopRight, PoisX + (i * 16), PosiY + (j * 16), 16, 16, 255);
			if (i == 0 && j != 0 && j + 1 != Height)
				dsDrawTexImage(cItem.MatItemInfoBox_Left, PoisX + (i * 16), PosiY + (j * 16), 16, 16, 255);
			if (i != 0 && j != 0 && i + 1 != Width && j + 1 != Height)
				dsDrawTexImage(cItem.MatItemInfoBox_Center, PoisX + (i * 16), PosiY + (j * 16), 16, 16, 255);
			if (i + 1 == Width && j != 0 && j + 1 != Height)
				dsDrawTexImage(cItem.MatItemInfoBox_Right, PoisX + (i * 16), PosiY + (j * 16), 16, 16, 255);
			if (i == 0 && j + 1 == Height)
				dsDrawTexImage(cItem.MatItemInfoBox_BottomLeft, PoisX + (i * 16), PosiY + (j * 16), 16, 16, 255);
			if (i != 0 && j + 1 == Height && i + 1 != Width)
				dsDrawTexImage(cItem.MatItemInfoBox_BottomCenter, PoisX + (i * 16), PosiY + (j * 16), 16, 16, 255);
			if (j + 1 == Height && i + 1 == Width)
				dsDrawTexImage(cItem.MatItemInfoBox_BottomRight, PoisX + (i * 16), PosiY + (j * 16), 16, 16, 255);
		}
	}
}
// VIPÎïÆ·Ê¹ÓÃºóäÖÈ¾
int cHaPremiumItem::DrawText()
{
	char strBuff[32];
	memset(strBuff, 0, sizeof(strBuff));
	int i, cnt = 0;
	DWORD Color = D3DCOLOR_XRGB(255, 255, 255);
	for (i = 0; i < SINUPKEEPITEM_MAX; i++)
	{
		if (cSinHelp.sinGetHelpShowFlag())
			break;
		if (!CheckWindowOpen())
			break;
		if (UpKeepItem[i].Visible == true)
		{
			if (UpKeepItem[i].Infoflag == true)
			{
				InfoBox(UpKeepItem[i].PosiX + 30, UpKeepItem[i].PosiY, 10, 6);

				dsTextLineOut(1, UpKeepItem[i].PosiX + 50, UpKeepItem[i].PosiY + 20, UpKeepItem[i].Id, lstrlen(UpKeepItem[i].Id), Color);

				Color = D3DCOLOR_XRGB(255, 180, 100);

				switch (UpKeepItem[i].TGAImageNumber)
				{
				case nsPremiumItem::THIRD_EYES:
					wsprintf(strBuff, "Extra Drop Rate %d%s", UpKeepItem[i].Per, "%");
					break;
				case nsPremiumItem::EXPUP_POTION:
					wsprintf(strBuff, "Extra Experience %d%s", UpKeepItem[i].Per, "%");
					break;
				case nsPremiumItem::VAMPIRIC_CUS:
					wsprintf(strBuff, "+25 Life Regen");
					break;
				case nsPremiumItem::MANA_RECHAR_P:
					wsprintf(strBuff, "+25 Mana Regen");
					break;
				case nsPremiumItem::MIGHT_OF_AWELL:
					wsprintf(strBuff, "Extra Weight %d", UpKeepItem[i].Per);
					break;
				case nsPremiumItem::MANA_REDUCE_P:
					wsprintf(strBuff, "Skill Mana use -%d%s", UpKeepItem[i].Per, "%");
					break;
				case nsPremiumItem::HELP_PET_TERRY:
					wsprintf(strBuff, "Fire Element (Terry)");
					break;
				case nsPremiumItem::HELP_PET_NEPSYS:
					wsprintf(strBuff, "Ice Element (Nepsys)");
					break;
				case nsPremiumItem::HELP_PET_IO:
					wsprintf(strBuff, "Lightning Element (Io)");
					break;
				case nsPremiumItem::HELP_PET_MUTE:
					wsprintf(strBuff, "Healing Element (Mute)");
					break;
				case nsPremiumItem::STAMINA_REDUCE_P:
					wsprintf(strBuff, "Skill Stamina use -%d%s", UpKeepItem[i].Per, "%");
					break;
				case nsPremiumItem::VIP_INFO:
					wsprintf(strBuff, "VIP");
					break;
				case nsPremiumItem::CARAVAN_HOPY:
				case nsPremiumItem::CARAVAN_ARMA:
				case nsPremiumItem::CARAVAN_BUMA:
				case nsPremiumItem::CARAVAN_CUEPY:
				case nsPremiumItem::CARAVAN_HUNGKY:
				case nsPremiumItem::CARAVAN_RABIE:
				case nsPremiumItem::CARAVAN_TOBIE:
				case nsPremiumItem::CARAVAN_RUDOLF:
					switch (cCaravan.SelectMode)
					{
					case 0:
						wsprintf(strBuff, "Status: %s", "Stop");
						break;
					case 1:
						wsprintf(strBuff, "Status: %s", "Follow");
						break;
					}
					break;
				case nsPremiumItem::BIG_HEAD:
					switch (UpKeepItem[i].Per)
					{
					case 1:
					case 2:
						wsprintf(strBuff, "+5%s Damage Boost", "%");
						break;
					case 3:
						wsprintf(strBuff, "+50 HP +50 MP +50 STM");
						break;
					case 4:
						wsprintf(strBuff, "HP+10 Life Regen+10");
						break;
					case 5:
						wsprintf(strBuff, "+3 Movement Speed");
						break;
					case 6:
						wsprintf(strBuff, "+2 Block Rating");
						break;
					default:
						wsprintf(strBuff, "ÆäËûÐ§¹û");
						break;
					}
					break;
				case nsPremiumItem::BIG_GIRAFFEHAT:
					wsprintf(strBuff, "+5%s Critical Rate", "%");
					break;
				case nsPremiumItem::BIG_MAGICIANHAT:
				case nsPremiumItem::BIG_WITCHHAT:
					wsprintf(strBuff, "+15 Mana Regen");
					break;
				case nsPremiumItem::BIG_MASKEDMAN:
				case nsPremiumItem::BIG_MASKEDWOMAN:
					wsprintf(strBuff, "+25 Defense Rating");
					break;
				case nsPremiumItem::BIG_PUMPKINHAT:
					wsprintf(strBuff, "+10 Absorb Rating");
					break;
				case nsPremiumItem::BIG_SHEEPHAT:
					wsprintf(strBuff, "+100 HP");
					break;
				case nsPremiumItem::BIG_SOCCERHAT:
					wsprintf(strBuff, "+1 Movement Speed");
					break;
				case nsPremiumItem::BIG_GREENXMASHAT:
					wsprintf(strBuff, "+5 Mana Regen");
					break;
				case nsPremiumItem::BIG_REDXMASHAT:
					wsprintf(strBuff, "+10 HP Regen");
					break;
				case nsPremiumItem::PHONEIX_FIRE:
					wsprintf(strBuff, "Fire Element");
					break;
				case nsPremiumItem::PHONEIX_ICE:
					wsprintf(strBuff, "Ice Element");
					break;
				case nsPremiumItem::PHONEIX_LIGHTNING:
					wsprintf(strBuff, "Lightning Element");
					break;
				case nsPremiumItem::PHONEIX_HEAL:
					wsprintf(strBuff, "Healing Element");
					break;
				case nsPremiumItem::BIG_EASTER:
					wsprintf(strBuff, "+100 Attack Rating");
					break;
				case nsPremiumItem::BIG_BIRTHDAY:
					wsprintf(strBuff, "+3 Block Rating");
					break;
				case nsPremiumItem::BIG_BLUEXMASHAT:
					wsprintf(strBuff, "+100 MP");
					break;
				}

				dsTextLineOut(0, UpKeepItem[i].PosiX + 50, UpKeepItem[i].PosiY + 20 + 20, strBuff, lstrlen(strBuff), Color);

				smTIME smTime;
				GetSinTime2(UpKeepItem[i].IconTime[1] - UpKeepItem[i].IconTime[0], &smTime);
				if (smTime.Day > 0)
					STRINGFORMAT(strBuff, "Time left: %02d:%02d:%02d:%02d\r", smTime.Day, smTime.Hour, smTime.Minute, smTime.Sec);
				else
					STRINGFORMAT(strBuff, "Time left: %02d:%02d:%02d\r", smTime.Hour, smTime.Minute, smTime.Sec);

				dsTextLineOut(0, UpKeepItem[i].PosiX + 50, UpKeepItem[i].PosiY + 20 + 46, strBuff, lstrlen(strBuff), D3DCOLOR_XRGB(50, 250, 50));
			}
		}
	}

	return TRUE;
}
int cHaPremiumItem::UseHairtintPotion(int ItemKind)
{
	if (ItemKind > 0 && ItemKind <= 20)
	{
		if (ChangeHairModel(ItemKind - 1))
			return TRUE;
	}
	cMessageBox.ShowMessage(MESSAGE_NOT_HAIRTINTPOTION);
	return FALSE;
}
int cHaPremiumItem::UseAgingMaster(int ItemKind)
{
	switch (ItemKind)
	{
	case 0:
		sinCheckAgingLevel(SIN_AGING_ATTACK, true);
		sinCheckAgingLevel(SIN_AGING_CRITICAL, true);
		ReformCharForm();
		cMessageBox.ShowMessage(MESSAGE_AGING_MATURE_SUCCESS);
		break;
	case 1:
		if (cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sBaseItemID.ToItemType() == sinDS1)
		{
			sinCheckAgingLevel(SIN_AGING_BLOCK, true);
			ReformCharForm();
			cMessageBox.ShowMessage(MESSAGE_AGING_MATURE_SUCCESS);
		}
		else if (cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sBaseItemID.ToItemType() == sinOM1)
		{
			sinCheckAgingLevel(SIN_AGING_DEFENSE_ORB, true);
			ReformCharForm();
			cMessageBox.ShowMessage(MESSAGE_AGING_MATURE_SUCCESS);
		}
		break;
	case 2:
		sinCheckAgingLevel(SIN_AGING_DEFENSE_ARMOR, true);
		ReformCharForm();
		cMessageBox.ShowMessage(MESSAGE_AGING_MATURE_SUCCESS);
		break;
	case 3:
		sinCheckAgingLevel(SIN_AGING_DEFENSE_ARMLETS, true);
		ReformCharForm();
		cMessageBox.ShowMessage(MESSAGE_AGING_MATURE_SUCCESS);
		break;
	case 4:
		sinCheckAgingLevel(SIN_AGING_DEFENSE_GLOVES, true);
		ReformCharForm();
		cMessageBox.ShowMessage(MESSAGE_AGING_MATURE_SUCCESS);
		break;
	case 5:
		sinCheckAgingLevel(SIN_AGING_DEFENSE_BOOTS, true);
		ReformCharForm();
		cMessageBox.ShowMessage(MESSAGE_AGING_MATURE_SUCCESS);
		break;
	}

	return TRUE;
}

int cHaPremiumItem::UseSkillMaster(int ItemKind)
{
	switch (ItemKind)
	{
	case 1:
		for (int j = 1; j < 5; j++)
		{
			if (sinSkill.UseSkill[j].UseSkillCount < 10000)
			{
				if (sinSkill.UseSkill[j].Flag && sinSkill.UseSkill[j].Point)
				{
					sinSkill.UseSkill[j].UseSkillCount += 10000;
					cSkill.ReformSkillMasteryForm(0, j);
				}
			}
		}
		cMessageBox.ShowMessage(MESSAGE_SKILL_MATURE_SUCCESS);
		sinPlaySound(SIN_SOUND_EAT_POTION2);
		sinEffect_Agony(lpCurPlayer);
		break;
	case 2:
		for (int j = 5; j < 9; j++)
		{
			if (sinSkill.UseSkill[j].UseSkillCount < 10000)
			{
				if (sinSkill.UseSkill[j].Flag && sinSkill.UseSkill[j].Point)
				{
					sinSkill.UseSkill[j].UseSkillCount += 10000;
					cSkill.ReformSkillMasteryForm(0, j);
				}
			}
		}
		cMessageBox.ShowMessage(MESSAGE_SKILL_MATURE_SUCCESS);
		sinPlaySound(SIN_SOUND_EAT_POTION2);
		sinEffect_Agony(lpCurPlayer);
		break;
	case 3:
		for (int j = 9; j < 13; j++)
		{
			if (sinSkill.UseSkill[j].UseSkillCount < 10000)
			{
				if (sinSkill.UseSkill[j].Flag && sinSkill.UseSkill[j].Point)
				{
					sinSkill.UseSkill[j].UseSkillCount += 10000;
					cSkill.ReformSkillMasteryForm(0, j);
				}
			}
		}
		cMessageBox.ShowMessage(MESSAGE_SKILL_MATURE_SUCCESS);
		sinPlaySound(SIN_SOUND_EAT_POTION2);
		sinEffect_Agony(lpCurPlayer);
		break;
	}

	return TRUE;
}
int cHaPremiumItem::UseMoveShop()
{
	if (cShop.OpenFlag == SIN_CLOSE)
	{
		sinShopKind = 1;
		cShop.OpenFlag = SIN_OPEN;
		cShop.UseItemFlag = 1;
	}
	else
	{
		cShop.OpenFlag = SIN_CLOSE;
		cShop.UseItemFlag = 0;
	}

	return TRUE;
}
