#include "StdAfx.h"


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

int sinMoveKindInter[MAX_SIN_KIND_INTER] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }; //눗왯잚깎

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
	"Image\\SinImage\\Sound\\interface-on.wav",		//0 (인터페이스 First Start 사운드 )
	"Image\\SinImage\\Sound\\Axes.wav",				//1	(Axe)
	"Image\\SinImage\\Sound\\Claws.wav",			//2 (Claws)
	"Image\\SinImage\\Sound\\Hammer.wav",			//3 (Hammer)
	"Image\\SinImage\\Sound\\Magicial_Stuffs.wav",	//4 (Magicial_Stuffs)
	"Image\\SinImage\\Sound\\Poles.wav",			//5 (Poles)
	"Image\\SinImage\\Sound\\Shooters.wav",			//6 (Shooters)
	"Image\\SinImage\\Sound\\Swords.wav",			//7 (Swords)
	"Image\\SinImage\\Sound\\Throwing.wav",			//8 (Throwing)
	"Image\\SinImage\\Sound\\Armor.wav",			//9 (로브)
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
	"Image\\SinImage\\Sound\\drink1.wav",			//20 (물약먹는 사운드)
	"Image\\SinImage\\Sound\\interface.wav",		//21 (인터페이스 사운드 *처음시작을 제외하고 나오는 사운드)
	"Image\\SinImage\\Sound\\repair.wav",			//22 (수리시 사운드)
	"Image\\SinImage\\Sound\\sheltom-failure.wav",  //23 (믹스쳐, 에이징 실패시 사운드)
	"Image\\SinImage\\Sound\\Armor-w.wav",          //24 (갑옷)
	"Image\\SinImage\\Sound\\drink2.wav",           //25 (기력약 사운드)
	0
};

extern int DecodeCompress(BYTE *lpSrcData, BYTE *lpDestData);

int RecvCountFlag = 0;
int CheckPotionDelayFlag = 0;

DWORD sinSpecialCODE[] =
{
	(sinQT1 | sin01),(sinQT1 | sin02),(sinQT1 | sin03),(sinQT1 | sin04),(sinQT1 | sin05),(sinQT1 | sin06),
	(sinMA1 | sin01),(sinMA2 | sin01),(sinMA2 | sin02),(sinQW1 | sin01),(sinQW1 | sin02),(sinQW1 | sin03),
	(sinQW1 | sin04),(sinQW1 | sin05),(sinQT1 | sin07),(sinQT1 | sin08),
	(sinQT1 | sin09),(sinQT1 | sin10),(sinQT1 | sin11),(sinQT1 | sin12),(sinQT1 | sin13),
	(sinQT1 | sin14),(sinQT1 | sin15),(sinQT1 | sin16),(sinQW1 | sin06),(sinQT1 | sin17),(sinQT1 | sin18),(sinQT1 | sin19),
	0
};

void *szKindInter[] =
{
	&cSkill,
	&cTrade,
	&cWareHouse,
	&cCraftItem,
	&cAging,
	&SmeltingItem,
	&ManufactureItem,
	&cMixtureReset,
	&cElement,
	&cCaravan,
	&cSocket,
	0,
};

int FirstMove[MAX_SIN_KIND_INTER] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };// 눗왯


#define SIN_POTION_LIFE			1
#define SIN_POTION_MANA			2
#define SIN_POTION_STAMINA		3
#define SIN_POTION_SONGPYEUN	4


float fTempLIFE = 0;
float fTempMANA = 0;
float fTempSTM_Incre = 0;
float fTempSTM_Decre = 0;


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



int CheatHelpOpenFlag = 0;



DWORD dwCurrentTime = 0;



static int LastPartyMode = -1;
int haSiegeBoardTempFlag = 0;



int sinSetDurabilityAging(Item *pItem)
{
	int Temp = 0;
	Temp = pItem->sIntegrity.sMax / 100;
	Temp += 1;
	pItem->sIntegrity.sMax -= Temp;
	if (pItem->sIntegrity.sMax < 0)
		pItem->sIntegrity.sMax = 0;
	if (pItem->sIntegrity.sMax < pItem->sIntegrity.sMin)
		pItem->sIntegrity.sMin = pItem->sIntegrity.sMax;

	return TRUE;
}
//묑샌제藤속
int sinSetDamageAging(Item *pItem)
{
	pItem->sDamage.sMin++;
	pItem->sDamage.sMax++;

	if (pItem->sAgeLevel >= 9)
	{
		pItem->sDamage.sMin++;
		pItem->sDamage.sMax++;
	}
	if (pItem->sAgeLevel >= 19)
	{
		pItem->sDamage.sMin++;
		pItem->sDamage.sMax++;
	}

	return TRUE;
}
int sinSetDefenseAging(Item *pItem, int Percent, int Type)
{
	float Temp = 0;

	switch (Type)
	{
	case 0:
		Temp = (float)pItem->iDefenseRating / (100.0f / (float)Percent);
		pItem->iDefenseRating += (int)Temp;
		break;
	case 1:
		pItem->iDefenseRating += Percent;
		break;
	}

	return TRUE;
}
int sinSetAttackRateAging(Item *pItem, int AddNum)
{
	pItem->iAttackRating += AddNum;
	return TRUE;
}
int sinSetAbsorbAging(Item *pItem, float Percent)
{
	pItem->fAbsorbRating += Percent;

	if (pItem->sAgeLevel >= 9)
		pItem->fAbsorbRating += Percent;
	if (pItem->sAgeLevel >= 19)
		pItem->fAbsorbRating += Percent;
	return TRUE;
}
int sinSetCriticalAging(Item *pItem)
{
	if (pItem->sAgeLevel && (pItem->sAgeLevel % 2) == 1)
		pItem->iCritical += 1;
	return TRUE;
}
int sinSetBlockRateAging(Item *pItem)
{
	if (pItem->sAgeLevel && (pItem->sAgeLevel % 2) == 1)
		pItem->fBlockRating += 1;
	return TRUE;
}

int sinSetAgingItemIncreState(Item *pItem)
{
	switch (pItem->sItemID.ToItemType())
	{
	case sinWA1:
		sinSetDamageAging(pItem);
		sinSetAttackRateAging(pItem, 10);
		sinSetDurabilityAging(pItem);
		break;
	case sinWC1:
		sinSetDamageAging(pItem);
		sinSetAttackRateAging(pItem, 5);
		sinSetCriticalAging(pItem);
		break;
	case sinWH1:
		sinSetDamageAging(pItem);
		sinSetAttackRateAging(pItem, 10);
		sinSetDurabilityAging(pItem);
		break;
	case sinWM1:
		sinSetDamageAging(pItem);
		sinSetAttackRateAging(pItem, 10);
		pItem->fAddMP += 10;
		break;
	case sinWP1:
		sinSetDamageAging(pItem);
		sinSetAttackRateAging(pItem, 5);
		sinSetCriticalAging(pItem);
		break;
	case sinWS1:
		sinSetDamageAging(pItem);
		sinSetCriticalAging(pItem);
		sinSetDurabilityAging(pItem);
		break;
	case sinWS2:
		sinSetDamageAging(pItem);
		sinSetAttackRateAging(pItem, 5);
		sinSetCriticalAging(pItem);
		break;
	case sinWT1:
		sinSetDamageAging(pItem);
		sinSetCriticalAging(pItem);
		break;
	case sinWD1:
		sinSetDamageAging(pItem);
		sinSetAttackRateAging(pItem, 5);
		sinSetCriticalAging(pItem);
		break;
	case sinWN1:
		sinSetDamageAging(pItem);
		sinSetAttackRateAging(pItem, 10);
		pItem->fAddMP += 10;
		break;
	case sinDS1:
		sinSetBlockRateAging(pItem);
		sinSetAbsorbAging(pItem, 0.2f);
		sinSetDurabilityAging(pItem);
		break;
	case sinOM1:
		sinSetDefenseAging(pItem, 15, 1);
		sinSetAbsorbAging(pItem, 0.5f);
		sinSetDurabilityAging(pItem);
		break;
	case sinDA1:
	case sinDA2:
		sinSetDefenseAging(pItem, 5, 0);
		sinSetAbsorbAging(pItem, 0.5f);
		sinSetDurabilityAging(pItem);
		break;
	case sinDB1:
		sinSetDefenseAging(pItem, 10, 1);
		sinSetAbsorbAging(pItem, 0.5f);
		sinSetDurabilityAging(pItem);
		break;
	case sinDG1:
		sinSetDefenseAging(pItem, 10, 1);
		sinSetAbsorbAging(pItem, 0.5f);
		sinSetDurabilityAging(pItem);
		break;
	case sinOA2:
		sinSetDefenseAging(pItem, 10, 1);
		sinSetAttackRateAging(pItem, 5);
		sinSetDurabilityAging(pItem);
		break;
	}

	pItem->sAgeLevel++;

	pItem->bMaturing = 0;
	pItem->sMatureBar.sMin = 0;
	pItem->sMatureBar.sMax = 0;

	if ((pItem->sAgeLevel % 2) == 0)
	{
		if (pItem->iLevel < UNIT_LEVEL_MAX)
			pItem->iLevel++;
	}

	ReformItem(pItem);
	return TRUE;
}
int sinDownDurabilityAging(Item *pItem)
{
	int Temp = 0;
	Temp = pItem->sIntegrity.sMax / 100;
	Temp += 1;
	pItem->sIntegrity.sMax += Temp;
	if (pItem->sIntegrity.sMax < 0)
		pItem->sIntegrity.sMax = 0;
	if (pItem->sIntegrity.sMax < pItem->sIntegrity.sMin)
		pItem->sIntegrity.sMin = pItem->sIntegrity.sMax;

	return TRUE;
}
int sinDownDamageAging(Item *pItem)
{
	pItem->sDamage.sMin--;
	pItem->sDamage.sMax--;

	if (pItem->sAgeLevel > 9)
	{
		pItem->sDamage.sMin--;
		pItem->sDamage.sMax--;
	}
	if (pItem->sAgeLevel > 19)
	{
		pItem->sDamage.sMin--;
		pItem->sDamage.sMax--;
	}

	return TRUE;
}
int sinDownDefenseAging(Item *pItem, int Percent, int Type)
{
	float Temp = 0;
	int TempDefence = 0;

	switch (Type)
	{
	case 0:
		Temp = (100.0f*(float)pItem->iDefenseRating) / (100.0f + (float)Percent);
		TempDefence = pItem->iDefenseRating - (int)Temp;
		pItem->iDefenseRating -= TempDefence;
		break;
	case 1:
		pItem->iDefenseRating -= Percent;
		break;
	}
	return TRUE;
}
int sinDownAttackRateAging(Item *pItem, int AddNum)
{
	pItem->iAttackRating -= AddNum;
	return TRUE;
}
int sinDownAbsorbAging(Item *pItem, float Percent)
{
	pItem->fAbsorbRating -= Percent;

	if (pItem->sAgeLevel > 9)
		pItem->fAbsorbRating -= Percent;
	if (pItem->sAgeLevel > 19)
		pItem->fAbsorbRating -= Percent;
	return TRUE;
}
int sinDownCriticalAging(Item *pItem)
{
	if (pItem->sAgeLevel && (pItem->sAgeLevel % 2) == 1)
		pItem->iCritical -= 1;
	return TRUE;

}
int sinDownBlockRateAging(Item *pItem)
{
	if (pItem->sAgeLevel && (pItem->sAgeLevel % 2) == 1)
		pItem->fBlockRating -= 1;
	return TRUE;

}

//슉됴똴芚된섬
int sinAgingItemInit(Item *pItem)
{
	switch (pItem->sItemID.ToItemType())
	{
	case sinWA1:
		sinDownDamageAging(pItem);
		sinDownAttackRateAging(pItem, 10);
		sinDownDurabilityAging(pItem);
		break;
	case sinWC1:
		sinDownDamageAging(pItem);
		sinDownAttackRateAging(pItem, 5);
		sinDownCriticalAging(pItem);
		break;
	case sinWH1:
		sinDownDamageAging(pItem);
		sinDownAttackRateAging(pItem, 10);
		sinDownDurabilityAging(pItem);
		break;
	case sinWM1:
		sinDownDamageAging(pItem);
		sinDownAttackRateAging(pItem, 10);
		pItem->fAddMP -= 10;
		break;
	case sinWP1:
		sinDownDamageAging(pItem);
		sinDownAttackRateAging(pItem, 5);
		sinDownCriticalAging(pItem);
		break;
	case sinWS1:
		sinDownDamageAging(pItem);
		sinDownCriticalAging(pItem);
		sinDownDurabilityAging(pItem);
		break;
	case sinWS2:
		sinDownDamageAging(pItem);
		sinDownAttackRateAging(pItem, 5);
		sinDownCriticalAging(pItem);
		break;
	case sinWT1:
		sinDownDamageAging(pItem);
		sinDownCriticalAging(pItem);
		break;
	case sinWD1:
		sinDownDamageAging(pItem);
		sinDownAttackRateAging(pItem, 5);
		sinDownCriticalAging(pItem);
		break;
	case sinWN1:
		sinDownDamageAging(pItem);
		sinDownAttackRateAging(pItem, 10);
		pItem->fAddMP -= 10;
		break;
	case sinDS1:
		sinDownBlockRateAging(pItem);
		sinDownAbsorbAging(pItem, 0.2f);
		sinDownDurabilityAging(pItem);
		break;
	case sinOM1:
		sinDownDefenseAging(pItem, 15, 1);
		sinDownAbsorbAging(pItem, 0.5f);
		sinDownDurabilityAging(pItem);
		break;
	case sinDA1:
	case sinDA2:
		sinDownDefenseAging(pItem, 5, 0);
		sinDownAbsorbAging(pItem, 0.5f);
		sinDownDurabilityAging(pItem);
		break;
	case sinDB1:
		sinDownDefenseAging(pItem, 10, 1);
		sinDownAbsorbAging(pItem, 0.5f);
		sinDownDurabilityAging(pItem);
		break;
	case sinDG1:
		sinDownDefenseAging(pItem, 10, 1);
		sinDownAbsorbAging(pItem, 0.5f);
		sinDownDurabilityAging(pItem);
		break;
	case sinOA2:
		sinDownDefenseAging(pItem, 10, 1);
		sinDownAttackRateAging(pItem, 5);
		sinDownDurabilityAging(pItem);
		break;
	}

	pItem->sAgeLevel--;
	pItem->bMaturing = 0;
	pItem->sMatureBar.sMin = 0;
	pItem->sMatureBar.sMax = 0;

	if ((pItem->sAgeLevel % 2) == 1)
	{
		if (pItem->iLevel > 0)
			pItem->iLevel -= 1;
		else
			pItem->iLevel = 0;
	}

	ReformItem(pItem);
	return TRUE;
}
int sinCheckAgingItemHack(ItemData *pItem)
{
	if (pItem->sItem.eCraftType == ITEMCRAFTTYPE_Mixing)
		return FALSE;

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

DWORD CristalEventCODE[12] = { (sinGP1 | sin01),(sinGP1 | sin02),(sinGP1 | sin03),(sinGP1 | sin04),(sinGP1 | sin05)
						   ,(sinGP1 | sin06),(sinGP1 | sin07),(sinGP1 | sin08),(sinGP1 | sin09),
							(sinGP1 | sin11),(sinGP1 | sin12),(sinGP1 | sin13) };

//박재원 - 수박 모아오기(호박) //박재원 - 밤하늘의 소원 이벤트
DWORD WatermelonEventCODE = (sinSP1 | sin26);
// 장별 - 발렌타인 이벤트
DWORD ValentineEventCODE = (sinSP1 | sin35);

// 박재원 - 알파벳 조합 이벤트
DWORD PristonAlphabetEventCODE[7] = { (sinSP1 | sin27), (sinSP1 | sin28), (sinSP1 | sin29),
									  (sinSP1 | sin30), (sinSP1 | sin31), (sinSP1 | sin32), (sinSP1 | sin33) };

// 장별 - 캔디데이즈
DWORD CandydaysEventCODE = (sinSP1 | sin36);

// 장별 - 매지컬그린
DWORD MagicalGreenEventCODE[2] = { (sinSP1 | sin37), (sinSP1 | sin38) };

// 장별 - 카라의 눈물
DWORD TeatOfKaraEventCODE = (sinSP1 | sin39);

// 장별 - 조사원을 찾아라 - 마력연구자
DWORD FindinvestigatorEventCODE[2] = { (sinGF1 | sin07), (sinGF1 | sin08) };

struct sWINGQUEST
{
	DWORD NeedItemCode[6];
	int   Money;
	DWORD ChangeItemCode;
};



sWINGQUEST sWingQuest[6] =
{
	{ {(sinGP1 | sin01), (sinGP1 | sin02), 0, 0, 0}, 3000, (sinQW1 | sin01)},
	{ {(sinQW1 | sin01),(sinGP1 | sin02),(sinGP1 | sin03),0,0},5000,(sinQW1 | sin02) },
	{ {(sinQW1 | sin02),(sinGP1 | sin03),(sinGP1 | sin04),0,0},10000,(sinQW1 | sin03) },
	{ {(sinQW1 | sin03),(sinGP1 | sin05),(sinGP1 | sin06),0,0},20000,(sinQW1 | sin04) },
	{ {(sinQW1 | sin04),(sinGP1 | sin06),(sinGP1 | sin07),0,0},40000,(sinQW1 | sin05) },
	{ {(sinQW1 | sin05),(sinGP1 | sin07),(sinGP1 | sin08),0,0},80000,(sinQW1 | sin06) },
};

DWORD sinWingItemQuestServer(sCRAFTITEM_SERVER *pWingItem, CharacterData *pChar_Info)
{
	int i = 0, j = 0, k = 0;
	int CodeCount = 0;
	int ItemCount = 0;
	int ItemCountPuzzle = 0;
	int PresentPercent = 0;
	int PresentItemIndex = 0;
	int PresentPercentSum = 0;
	int PresentItemCount = 0;
	int PotionNum = 0;
	short ItemCount80_2[4] = { 0, };

	int ItemIndex = 0;
	char *((*pPresentWeaponName)[9]);
	char *((*pPresentArmorName)[9]);
	int  *pPresentPercentIndex;

	int RandomTemp = 0;

	int CristalCount = 0;
	int CristalFlag = 0;

	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < 12; j++)
		{
			if (pWingItem->SheltomCode[i] == CristalEventCODE[j])
				CristalCount = i + 1;
		}
	}

	int WatermelonCount = 0;
	int WatermelonFlag = 0;

	for (int n = 0; n < 7; n++)
	{
		if (pWingItem->SheltomCode[n] == WatermelonEventCODE)
			WatermelonCount = n + 1;
	}

	int ValentineCount = 0;
	int ValentineFlag = 0;

	for (int n = 0; n < 7; n++)
	{
		if (pWingItem->SheltomCode[n] == ValentineEventCODE)
			ValentineCount = n + 1;
	}

	int CandydaysCount = 0;
	int CandydaysFlag = 0;

	for (int n = 0; n < 7; n++)
	{
		if (pWingItem->SheltomCode[n] == CandydaysEventCODE)
			CandydaysCount = n + 1;
	}

	int MagicalGreenEmeraldCount = 0;
	int MagicalGreenEmeraldFlag = 0;
	int MagicalGreenJadeCount = 0;
	int MagicalGreenJadeFlag = 0;

	for (int a = 0; a < 7; a++)
	{
		if (pWingItem->SheltomCode[a] == MagicalGreenEventCODE[1])
			MagicalGreenEmeraldCount = a + 1;
	}

	for (int b = 0; b < 7; b++)
	{
		if (pWingItem->SheltomCode[b] == MagicalGreenEventCODE[0])
			MagicalGreenJadeCount = b + 1;
	}

	int TearOfKaraCount = 0;
	int TearOfKaraFlag = 0;

	for (int n = 0; n < 7; n++)
	{
		if (pWingItem->SheltomCode[n] == TeatOfKaraEventCODE)
			TearOfKaraCount = n + 1;
	}

	int FindinvestigatorNineCount = 0;
	int FindinvestigatorNineFlag = 0;
	int FindinvestigatorTaleCount = 0;
	int FindinvestigatorTaleFlag = 0;

	for (int a = 0; a < 1; a++)
	{
		if (pWingItem->SheltomCode[a] == FindinvestigatorEventCODE[0])
			FindinvestigatorNineCount = a + 1;
	}

	for (int b = 0; b < 1; b++)
	{
		if (pWingItem->SheltomCode[b] == FindinvestigatorEventCODE[1])
			FindinvestigatorTaleCount = b + 1;
	}

	int PristonAlphabetCount = 0;
	int PristonAlphabetFlag = 0;

	for (int c = 0; c < 7; c++)
	{
		for (int d = 0; d < 7; d++)
		{
			if (pWingItem->SheltomCode[c] == PristonAlphabetEventCODE[d])
				PristonAlphabetCount = c + 1;
		}
	}
	if (pWingItem->SheltomCode[0] == (sinGF1 | sin02))
	{
		RandomTemp = GetRandomPos(0, 100);
		ItemIndex = 5;
		pPresentWeaponName = PresentWeaponName;
		pPresentArmorName = PresentArmorName;
		pPresentPercentIndex = PresentPercentIndex;
		PotionNum = 30;
		if (RandomTemp < 50)
			ItemCountPuzzle = 8;
		else
			ItemCountPuzzle = 16;
	}
	else if (pWingItem->SheltomCode[0] == (sinGF1 | sin03) && pWingItem->SheltomCode[1] == (sinGF1 | sin04))
	{
		RandomTemp = GetRandomPos(0, 100);
		ItemIndex = 6;
		pPresentWeaponName = PresentWeaponName2;
		pPresentArmorName = PresentArmorName2;
		pPresentPercentIndex = PresentPercentIndex2;
		PotionNum = 20;
		if (RandomTemp < 50)
			ItemCountPuzzle = 8;
		else
			ItemCountPuzzle = 16;
	}
	else if (pWingItem->SheltomCode[0] == (sinGF1 | sin05))
	{
		RandomTemp = GetRandomPos(0, 100);
		ItemIndex = 6;
		pPresentWeaponName = PresentWeaponName2;
		pPresentArmorName = PresentArmorName2;
		pPresentPercentIndex = PresentPercentIndex2;
		PotionNum = 20;
		if (RandomTemp < 50)
			ItemCountPuzzle = 8;
		else
			ItemCountPuzzle = 16;
	}
	else if (CristalCount == 7)
	{
		CristalFlag = 1;
		RandomTemp = GetRandomPos(0, 100);
		ItemIndex = 5;
		pPresentWeaponName = PresentWeaponName3;
		pPresentArmorName = PresentArmorName3;
		pPresentPercentIndex = PresentPercentIndex3;
		PotionNum = 40;
		if (RandomTemp < 50)
			ItemCountPuzzle = 8;
		else
			ItemCountPuzzle = 16;
	}
	else if (WatermelonCount == 7)
	{
		WatermelonFlag = 1;
		RandomTemp = GetRandomPos(0, 100);
		ItemIndex = 9;
		pPresentWeaponName = PresentWeaponName3;
		pPresentArmorName = PresentArmorName3;
		pPresentPercentIndex = PresentPercentIndex3;
		PotionNum = 5;
		if (RandomTemp < 50)
			ItemCountPuzzle = 8;
		else
			ItemCountPuzzle = 16;
	}
	else if (ValentineCount == 7)
	{
		ValentineFlag = 1;
		RandomTemp = GetRandomPos(0, 100);
		ItemIndex = 17;
		pPresentWeaponName = PresentChocoWeaponName3;
		pPresentArmorName = PresentChocoArmorName3;
		pPresentPercentIndex = PresentChocoPercentIndex3;
		PotionNum = 5;
		if (RandomTemp < 50)
			ItemCountPuzzle = 8;
		else
			ItemCountPuzzle = 16;
	}
	else if (PristonAlphabetCount == 7)
	{
		PristonAlphabetFlag = 1;
		RandomTemp = GetRandomPos(0, 100);
		ItemIndex = 11;
		pPresentWeaponName = PresentWeaponName5;
		pPresentArmorName = PresentArmorName5;
		pPresentPercentIndex = PresentPercentIndex5;
		PotionNum = 20;
		if (RandomTemp < 50)
			ItemCountPuzzle = 8;
		else
			ItemCountPuzzle = 16;
	}
	else if (CandydaysCount == 7)
	{
		CandydaysFlag = 1;
		RandomTemp = GetRandomPos(0, 100);
		ItemIndex = 17;
		pPresentWeaponName = PresentCandyWeaponName3;
		pPresentArmorName = PresentCandyArmorName3;
		pPresentPercentIndex = PresentCandyPercentIndex3;
		PotionNum = 5;
		if (RandomTemp < 50)
			ItemCountPuzzle = 8;
		else
			ItemCountPuzzle = 16;
	}
	else if (MagicalGreenJadeCount == 7)
	{
		MagicalGreenJadeFlag = 1;
		RandomTemp = GetRandomPos(0, 100);
		ItemIndex = 15;
		pPresentWeaponName = PresentMagicalGreenJadeWeaponName3;
		pPresentArmorName = PresentMagicalGreedJadeArmorName3;
		pPresentPercentIndex = PresentMagicalGreedJadePercentIndex3;
		PotionNum = 10;
		if (RandomTemp < 50)
			ItemCountPuzzle = 8;
		else
			ItemCountPuzzle = 16;
	}
	else if (MagicalGreenEmeraldCount == 7)
	{
		MagicalGreenEmeraldFlag = 1;
		RandomTemp = GetRandomPos(0, 100);
		ItemIndex = 18;
		pPresentWeaponName = PresentMagicalGreenEmeraldWeaponName3;
		pPresentArmorName = PresentMagicalGreenEmeraldArmorName3;
		pPresentPercentIndex = PresentMagicalGreenEmeraldPercentIndex3;
		PotionNum = 20;
		if (RandomTemp < 50)
			ItemCountPuzzle = 8;
		else
			ItemCountPuzzle = 16;
	}
	else if (TearOfKaraCount == 7)
	{
		TearOfKaraFlag = 1;
		RandomTemp = GetRandomPos(0, 100);
		ItemIndex = 18;
		pPresentWeaponName = PresentTearOfKaraWeaponName3;
		pPresentArmorName = PresentTearOfKaraArmorName3;
		pPresentPercentIndex = PresentTearOfKaraPercentIndex3;
		PotionNum = 10;
		if (RandomTemp < 50)
			ItemCountPuzzle = 8;
		else
			ItemCountPuzzle = 16;
	}
	else if (FindinvestigatorNineCount == 0 && FindinvestigatorTaleCount == 0 && pWingItem->DesCraftItem.sBaseItemID.ToInt() != 1000)
	{
		for (i = 0; i < 5; i++)
		{
			if (sWingQuest[pWingItem->Index].ChangeItemCode)
			{
				if (sWingQuest[pWingItem->Index].NeedItemCode[i] == pWingItem->SheltomCode[i])
					break;
			}

			switch (pWingItem->SheltomCode[i])
			{
			case (sinQT1 | sin09):
			case (sinQT1 | sin10):
			case (sinQT1 | sin11):
			case (sinQT1 | sin06):
			case (sinQT1 | sin12):
				break;
			default:
				FindinvestigatorNineFlag = 1;
				RandomTemp = GetRandomPos(0, 100);
				ItemIndex = 1;
				pPresentWeaponName = PresentFindinvestigatorNineWeaponName3;
				pPresentArmorName = PresentFindinvestigatorNineArmorName3;
				pPresentPercentIndex = PresentFindinvestigatorNinePercentIndex3;
				PotionNum = 10;
				if (RandomTemp < 50)
					ItemCountPuzzle = 8;
				else
					ItemCountPuzzle = 16;
				break;
			}
		}
	}
	else if (FindinvestigatorNineCount == 1)
	{
		FindinvestigatorNineFlag = 1;
		RandomTemp = GetRandomPos(0, 100);
		ItemIndex = 1;
		pPresentWeaponName = PresentFindinvestigatorNineTaleWeaponName3;
		pPresentArmorName = PresentFindinvestigatorNineTaleArmorName3;
		pPresentPercentIndex = PresentFindinvestigatorNineTalePercentIndex3;
		PotionNum = 10;
		if (RandomTemp < 50)
			ItemCountPuzzle = 8;
		else
			ItemCountPuzzle = 16;
	}
	else if (FindinvestigatorTaleCount == 1)
	{
		FindinvestigatorTaleFlag = 1;
		RandomTemp = GetRandomPos(0, 100);
		ItemIndex = 12;
		pPresentWeaponName = PresentFindinvestigatorWeaponName3;
		pPresentArmorName = PresentFindinvestigatorArmorName3;
		pPresentPercentIndex = PresentFindinvestigatorPercentIndex3;
		PotionNum = 10;
		if (RandomTemp < 50)
			ItemCountPuzzle = 8;
		else
			ItemCountPuzzle = 16;
	}

	else
	{
		ItemIndex = 8;
		pPresentWeaponName = PresentWeaponName2;
		pPresentArmorName = PresentArmorName2;
		pPresentPercentIndex = PresentPercentIndex2;
		PotionNum = 10;

		for (i = 0; i < 8; i++)
		{
			if ((pWingItem->SheltomCode[i] & sinITEM_MASK2) == sinPZ1 || (pWingItem->SheltomCode[i] & sinITEM_MASK2) == sinPZ2)
			{
				for (j = 0; j < 8; j++)
				{
					if (i == j)
						continue;
					if (pWingItem->SheltomCode[i] == pWingItem->SheltomCode[j])
					{
						pWingItem->Result = FALSE;
						return FALSE;
					}
				}
				if ((pWingItem->SheltomCode[i] & sinITEM_MASK2) == sinPZ1)
					ItemCountPuzzle++;
				if ((pWingItem->SheltomCode[i] & sinITEM_MASK2) == sinPZ2)
					ItemCountPuzzle += 2;
			}
		}
	}
	if (ItemCountPuzzle == 8 || ItemCountPuzzle == 16)
	{
		PresentPercent = GetRandomPos(0, 10000);
		for (i = 0; i < ItemIndex; i++)
		{
			if (PresentPercent >= PresentPercentSum && (pPresentPercentIndex[i] + PresentPercentSum) >= PresentPercent)
			{
				PresentItemCount = 0;
				if (ItemCountPuzzle == 8)
				{
					for (k = 0; k < 9; k++)
					{
						if (pPresentWeaponName[i][k])
							PresentItemCount++;
					}
					PresentItemIndex = GetRandomPos(0, PresentItemCount - 1);
					while (1)
					{
						if (pPresentWeaponName[i][PresentItemIndex])
						{
							auto pItemData = SERVERITEM->FindItemPointerTable(pPresentWeaponName[i][PresentItemIndex]);

							if (pItemData)
							{
								pWingItem->DesCraftItem.sItem.sItemID = pItemData->sBaseItemID;
								if ((pWingItem->DesCraftItem.sItem.sItemID.ToItemType()) == sinPM1)
									pWingItem->DesCraftItem.sItem.iPotionCount = PotionNum;
								if (CristalFlag)
									pWingItem->Result = SIN_WINGRESULT_CRISTAL;
								else
									pWingItem->Result = TRUE;
								return TRUE;
							}
						}
						PresentItemIndex--;
						if (PresentItemIndex < 0)
							break;
					}
				}
				PresentItemCount = 0;
				if (ItemCountPuzzle == 16)
				{
					for (k = 0; k < 9; k++)
					{
						if (pPresentArmorName[i][k])
							PresentItemCount++;
					}
					PresentItemIndex = GetRandomPos(0, PresentItemCount - 1);
					while (1)
					{
						if (pPresentArmorName[i][PresentItemIndex])
						{
							auto pItemData = SERVERITEM->FindItemPointerTable(pPresentArmorName[i][PresentItemIndex]);

							if (pItemData)
							{
								pWingItem->DesCraftItem.sItem.sItemID = pItemData->sBaseItemID;
								if ((pWingItem->DesCraftItem.sItem.sItemID.ToItemType()) == sinPM1)
									pWingItem->DesCraftItem.sItem.iPotionCount = PotionNum;
								if (CristalFlag)
									pWingItem->Result = SIN_WINGRESULT_CRISTAL;
								else
									pWingItem->Result = TRUE;
								return TRUE;
							}
						}
						PresentItemIndex--;
						if (PresentItemIndex < 0)break;
					}
				}
			}
			else PresentPercentSum += pPresentPercentIndex[i];
		}
	}

	for (i = 0; i < 3; i++)
	{
		switch (pWingItem->SheltomCode[i])
		{
		case (sinQT1 | sin09):
			ItemCount80_2[0] = 1;
			break;
		case (sinQT1 | sin10):
			ItemCount80_2[1] = 1;
			break;
		case (sinQT1 | sin11):
			ItemCount80_2[2] = 1;
			break;
		}
	}
	if (ItemCount80_2[0] && ItemCount80_2[1] && ItemCount80_2[2])
	{
		pWingItem->Result = TRUE;
		pWingItem->DesCraftItem.sItem.sItemID = (sinQT1 | sin12);
		return TRUE;
	}
	for (i = 0; i < 3; i++)
	{
		if (pWingItem->SheltomCode[i] == (sinQT1 | sin06))
			ItemCount++;
	}
	if (ItemCount == 3 && pChar_Info)
	{
		pWingItem->Result = TRUE;
		switch (pChar_Info->iClass)
		{
		case CHARACTERCLASS_Fighter:
			pWingItem->DesCraftItem.sItem.sItemID = (sinWA1 | sin08);
			break;
		case CHARACTERCLASS_Mechanician:
			pWingItem->DesCraftItem.sItem.sItemID = (sinWC1 | sin08);
			break;
		case CHARACTERCLASS_Archer:
			pWingItem->DesCraftItem.sItem.sItemID = (sinWS1 | sin10);
			break;
		case CHARACTERCLASS_Pikeman:
			pWingItem->DesCraftItem.sItem.sItemID = (sinWP1 | sin09);
			break;
		case CHARACTERCLASS_Atalanta:
			pWingItem->DesCraftItem.sItem.sItemID = (sinWT1 | sin09);
			break;
		case CHARACTERCLASS_Knight:
			pWingItem->DesCraftItem.sItem.sItemID = (sinWS2 | sin10);
			break;
		case CHARACTERCLASS_Magician:
			pWingItem->DesCraftItem.sItem.sItemID = (sinWM1 | sin09);
			break;
		case CHARACTERCLASS_Priestess:
			pWingItem->DesCraftItem.sItem.sItemID = (sinWM1 | sin09);
			break;
		case CHARACTERCLASS_Assassin:
			pWingItem->DesCraftItem.sItem.sItemID = (sinWD1 | sin09);
			break;
		case CHARACTERCLASS_Shaman:
			pWingItem->DesCraftItem.sItem.sItemID = (sinWN1 | sin09);
			break;
		}

		pWingItem->DesCraftItem.sItem.eCraftType = ITEMCRAFTTYPE_QuestWeapon;
		return TRUE;
	}
	if (pWingItem->DesCraftItem.sBaseItemID.ToInt() == 1000)
	{
		for (i = 0; i < 12; i++)
		{
			for (j = 0; j < 16; j++)
			{
				if ((pWingItem->SheltomCode[i] & sinITEM_MASK3) == SheltomCode2[j])
				{
					pWingItem->Head[i] = 0;
					pWingItem->CheckSum[i] = 0;
					pWingItem->SheltomCode[i] = sinForceOrbCode[j];
					break;
				}
			}
		}
		pWingItem->Result = TRUE;
		return 0x100;
	}
	else
	{
		for (i = 0; i < 5; i++)
		{
			if (sWingQuest[pWingItem->Index].ChangeItemCode)
			{
				CodeCount++;
				if (sWingQuest[pWingItem->Index].NeedItemCode[i] == pWingItem->SheltomCode[i])
					ItemCount++;
			}
		}
		if (CodeCount == ItemCount)
		{
			pWingItem->DesCraftItem.sItem.sItemID = sWingQuest[pWingItem->Index].ChangeItemCode;
			pWingItem->DesCraftItem.sItem.eCraftType = ITEMCRAFTTYPE_None;
			pWingItem->Result = TRUE;
			return TRUE;
		}
	}
	pWingItem->Result = FALSE;
	return FALSE;
}
int OverDay_Item_Flag = 0;

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