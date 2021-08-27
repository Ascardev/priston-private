#pragma once
#define PREMIUM_ITEM_TOTAL 50

enum EItemTimerType
{
	ITEMTIMERTYPE_None,
	ITEMTIMERTYPE_ExpUp,
	ITEMTIMERTYPE_ThirdEye,
	ITEMTIMERTYPE_Phoenix,
	ITEMTIMERTYPE_PhoenixFire,
	ITEMTIMERTYPE_PhoenixIce,
	ITEMTIMERTYPE_PhoenixLightning,
	ITEMTIMERTYPE_PhoenixHeal,
	ITEMTIMERTYPE_MPDown,
	ITEMTIMERTYPE_SPDown,
	ITEMTIMERTYPE_HPUp,
	ITEMTIMERTYPE_MPUp,
	ITEMTIMERTYPE_BigHead,
	ITEMTIMERTYPE_WeightStone,
	ITEMTIMERTYPE_MatureStone,
	ITEMTIMERTYPE_SkillStone,
	ITEMTIMERTYPE_CartolaHat,
	ITEMTIMERTYPE_WitchHat,
	ITEMTIMERTYPE_SheepHat,
	ITEMTIMERTYPE_GiraffeHat,
	ITEMTIMERTYPE_SoccerHat,
	ITEMTIMERTYPE_XMasGreenHat,
	ITEMTIMERTYPE_XMasRedHat,
	ITEMTIMERTYPE_BigHeadHappiness,
	ITEMTIMERTYPE_BigHeadLove,
	ITEMTIMERTYPE_BigHeadSadness,
	ITEMTIMERTYPE_BigHeadShyness,
	ITEMTIMERTYPE_BigHeadAngry,
	ITEMTIMERTYPE_BigHeadSurprised,
	ITEMTIMERTYPE_BigHeadSensual,
	ITEMTIMERTYPE_BCBuff,
	ITEMTIMERTYPE_PumpkinHat,
};

enum
{
	ITEMTIMERTIME_1H = (60 * 60),
	ITEMTIMERTIME_3H = (60 * 60 * 3),
	ITEMTIMERTIME_6H = (60 * 60 * 6),
	ITEMTIMERTIME_12H = (60 * 60 * 12),
	ITEMTIMERTIME_24H = (60 * 60 * 24),
	ITEMTIMERTIME_48H = (60 * 60 * 48),
	ITEMTIMERTIME_72H = (60 * 60 * 72),
};
struct ItemPremium
{
	EItemTimerType			eType;
	DWORD					dwCode;
	DWORD					dwTimeLeft;
	DWORD					dwTimeTotal;
};

struct PacketItemPremiumData : Packet
{
	ItemPremium				saItemList[PREMIUM_ITEM_TOTAL];
};
//Timers

struct PacketOldHeadUse : Packet
{
	char				szHeadModel[64];

	BOOL				bUpdate;

	PacketOldHeadUse() {};
	PacketOldHeadUse(BOOL bUpdateHead) { bUpdate = bUpdateHead; }
};

struct PacketCancelItemTimer : Packet
{
	EItemTimerType		iType;

	EItemID				iItemID;
};
struct PacketNewItemTimer : Packet
{
	EItemTimerType		iType;

	EItemID				iItemID;

	int					iChk1;
	int					iChk2;

	DWORD				dwTimeLeft;
	DWORD				dwTimeTotal;

	PacketNewItemTimer(EItemID iItemID, int iChk1, int iChk2) { this->iItemID = iItemID; this->iChk1 = iChk1; this->iChk2 = iChk2; }
	PacketNewItemTimer() { }
};

struct PacketNetPremium : Packet
{
	UINT		uObjectID;
	ItemPremium sItem;
};

static BOOL ItemTimerCanStack(int iType)
{
	BOOL bRet = FALSE;

	switch (iType)
	{
	case ITEMTIMERTYPE_BCBuff:
	case ITEMTIMERTYPE_PhoenixFire:
	case ITEMTIMERTYPE_PhoenixIce:
	case ITEMTIMERTYPE_PhoenixLightning:
	case ITEMTIMERTYPE_PhoenixHeal:
		bRet = TRUE;
		break;
	}

	return bRet;
}
static BOOL ItemTimerIsSame(int iType, int iTypeOther)
{
	BOOL bRet = FALSE;

	switch (iType)
	{
	case ITEMTIMERTYPE_PhoenixFire:
	case ITEMTIMERTYPE_PhoenixIce:
	case ITEMTIMERTYPE_PhoenixLightning:
	case ITEMTIMERTYPE_PhoenixHeal:
		switch (iTypeOther)
		{
		case ITEMTIMERTYPE_PhoenixFire:
		case ITEMTIMERTYPE_PhoenixIce:
		case ITEMTIMERTYPE_PhoenixLightning:
		case ITEMTIMERTYPE_PhoenixHeal:
			bRet = TRUE;
			break;
		}
		break;
	}

	return bRet;
}
static BOOL ItemTimerIsHead(int iType)
{
	BOOL bRet = FALSE;

	switch (iType)
	{
	case ITEMTIMERTYPE_BigHead:
	case ITEMTIMERTYPE_BigHeadHappiness:
	case ITEMTIMERTYPE_BigHeadLove:
	case ITEMTIMERTYPE_BigHeadSadness:
	case ITEMTIMERTYPE_BigHeadShyness:
	case ITEMTIMERTYPE_BigHeadAngry:
	case ITEMTIMERTYPE_BigHeadSurprised:
	case ITEMTIMERTYPE_BigHeadSensual:
	case ITEMTIMERTYPE_CartolaHat:
	case ITEMTIMERTYPE_WitchHat:
	case ITEMTIMERTYPE_XMasGreenHat:
	case ITEMTIMERTYPE_XMasRedHat:
	case ITEMTIMERTYPE_SheepHat:
	case ITEMTIMERTYPE_GiraffeHat:
	case ITEMTIMERTYPE_SoccerHat:
	case ITEMTIMERTYPE_PumpkinHat:
		bRet = TRUE;
		break;

	default:
		break;
	}

	return bRet;
}
