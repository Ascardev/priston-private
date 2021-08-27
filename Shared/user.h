#pragma once

#define USER_TALKRANGE			1200
#define USER_TALKRANGE_FAR		307200

#define USER_VIEWRANGE			2400
#define USER_VIEWRANGE_FAR		614400

#define USER_UPDATERANGE		3600
#define USER_UPDATERANGE_FAR	921600

#define USER_SIGHTRANGE			4800
#define USER_SIGHTRANGE_FAR		1228800

#define USER_STATUS_UPDATE_GRACE		2500
#define USER_USER_STATUS_UPDATE_GRACE	10000

#define MAX_DROPITEM			64
#define MAX_INTENTORYITEM		316

enum EGameLevel
{
	GAMELEVEL_None	= 0,
	GAMELEVEL_One	= 1,
	GAMELEVEL_Two	= 2,
	GAMELEVEL_Three = 3,
	GAMELEVEL_Four	= 4,
};

enum EWhereAction
{
	WHEREID_None			= 0,
	WHEREID_LoadPlayer		= 100,
	WHEREID_DropItem		= 120,
	WHEREID_GetItem			= 130,
	WHEREID_BuyItem			= 200,
	WHEREID_BuyPotion		= 210,
	WHEREID_SellItem		= 220,
	WHEREID_Trade			= 300,
	WHEREID_PersonalShop	= 320,
	WHEREID_Aging			= 400,
	WHEREID_MixItem			= 420,
	WHEREID_ForceOrb		= 440,
	WHEREID_LearnSkill		= 460,
	WHEREID_WarpGate		= 470,
	WHEREID_OpenWarehouse	= 500,
	WHEREID_QuestGold		= 501,
	WHEREID_FuryArena		= 502,
	WHEREID_Distributor		= 600,
	WHEREID_StarPoint		= 620,
	WHEREID_ClanMoney		= 630,
	WHEREID_GiveMoney		= 640,
	WHEREID_UnitDie			= 650,
};



static const char * GetWhereToString(EWhereAction e)
{
	switch (e)
	{
	case WHEREID_None:
		break;
	case WHEREID_Trade:
		return "Trade";
	case WHEREID_Distributor:
		return "Distributor";
	case WHEREID_Aging:
		return "Aging";
	case WHEREID_MixItem:
		return "MixItem";
	case WHEREID_ForceOrb:
		return "ForceOrb";
	case WHEREID_LearnSkill:
		return "LearnSkill";
	case WHEREID_WarpGate:
		return "WarpGate";
	case WHEREID_BuyItem:
		return "BuyItem";
	case WHEREID_BuyPotion:
		return "BuyPotion";
	case WHEREID_SellItem:
		return "SellItem";
	case WHEREID_LoadPlayer:
		return "LoadPlayer";
	case WHEREID_DropItem:
		return "DropItem";
	case WHEREID_GetItem:
		return "GetItem";
	case WHEREID_StarPoint:
		return "StartPoint";
	case WHEREID_ClanMoney:
		return "ClanMoney";
	case WHEREID_GiveMoney:
		return "GiveMoney";
	case WHEREID_PersonalShop:
		return "PersonalShop";
	case WHEREID_OpenWarehouse:
		return "OpenWarehouse";
	case WHEREID_QuestGold:
		return "QuestGold";
	case WHEREID_FuryArena:
		return "FuryArena";
	case WHEREID_UnitDie:
		return "CharacterDie";
	default:
		break;
	}

	return "Unknow";
}
static DWORD GetClanCodeByID(int iID)
{
	return (iID % 1000000) + (iID / 100000000) * 100000000;
}

struct PacketPlayInfo : Packet
{
	CharacterData	sCharacterData;

	ID iID;
	Point3D sPosition;
	Point3D sAngle;
	BOOL bInUse;
};
