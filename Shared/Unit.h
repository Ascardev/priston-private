#pragma once

#define	MAX_NPC_MESSAGE					20
#define MAX_FALLITEM					200
#define	MAX_LAST_QUEST					32
#define	ATTACK_DAMAGE_MAX				100

#define UNIT_DEFAULT_LURE_DISTANCE_FAR	1638400

enum EAnimationType : int
{
	ANIMATIONTYPE_None		= 0x0000,	//0
	ANIMATIONTYPE_Idle		= 0x0040,	//64
	ANIMATIONTYPE_Walking	= 0x0050,	//80
	ANIMATIONTYPE_Running	= 0x0060,	//96
	ANIMATIONTYPE_Sprint	= 0x0070,	//112
	ANIMATIONTYPE_Falling	= 0x0080,	//128
	ANIMATIONTYPE_Attack	= 0x0100,	//256
	ANIMATIONTYPE_Flinch	= 0x0110,	//272
	ANIMATIONTYPE_Die		= 0x0120,	//288
	ANIMATIONTYPE_Potion	= 0x0140,	//320
	ANIMATIONTYPE_Skill		= 0x0150,	//336
	ANIMATIONTYPE_FallLow	= 0x0170,	//368
	ANIMATIONTYPE_FallHigh	= 0x0180,	//384
	ANIMATIONTYPE_Revive	= 0x0200,	//512
	ANIMATIONTYPE_Special	= 0x0210,	//528
	ANIMATIONTYPE_Yahoo		= 0x0220,	//544
	ANIMATIONTYPE_Taunt		= 0x0230,	//560
	ANIMATIONTYPE_Hammer	= 0x0300,	//768
};

enum ECharacterType : int
{
	CHARACTERTYPE_None			= 0,

	CHARACTERTYPE_NPC			= 0x00,
	CHARACTERTYPE_Monster		= 0x01,
	CHARACTERTYPE_Player		= 0x80,
};
enum ESpecialUnitType
{
	SPECIALUNITTYPE_None			= 0,

	SPECIALUNITTYPE_QuestWolverine	= 100,
	SPECIALUNITTYPE_QuestSpawn		= 200,
};
enum EMonsterType
{
	MONSTERTYPE_Normal		= 0x00,
	MONSTERTYPE_Undead		= 0x90,
	MONSTERTYPE_Mutant		= 0x91,
	MONSTERTYPE_Demon		= 0x92,
	MONSTERTYPE_Mechanic	= 0x93,
	MONSTERTYPE_Friendly	= 0xA0,
};

enum EUpdateMode : int
{
	UPDATEMODE_ClientSelf		= 0,
	UPDATEMODE_ServerMonster	= 5,
	UPDATEMODE_ServerNPC		= 12,
	UPDATEMODE_ClientUnit		= 99,
	UPDATEMODE_ClientTarget		= 101,
};

enum ENPCID : int
{
	NPCID_EventGirl				= 1,
	NPCID_ItemDistributor		= 2,
	NPCID_Warehouse				= 3,
	NPCID_Force					= 4,
	NPCID_CastleControl			= 5,
	NPCID_Aging					= 6,
	NPCID_Smelting				= 7,
	NPCID_ClanControl			= 8,
	NPCID_Teleport				= 9,
	NPCID_SkillMaster			= 10,
	NPCID_Mixing				= 11,
	NPCID_Manufacturing			= 12,
	NPCID_WarpGate				= 13,
	NPCID_Bellatra				= 14,
	NPCID_ResetItem				= 15,
	NPCID_CoinShop				= 16,
	NPCID_FuryArenaNPC			= 17,
	NPCID_FuryArenaNPCEnter		= 18,
	NPCID_SocketSystemNPCDrill	= 19,
	NPCID_SocketSystemNPCStone	= 20,

	NPCID_NPCEasterEgg			= 21,

	NPCID_LarryQuests			= 22,
	NPCID_IhinEvent				= 23,
	NPCID_MarinaQuests			= 24,
	NPCID_RudolphXmas			= 25,
};

enum ENPCEventCode : int
{
	NPCEVENTCODE_Force						= 200,
	NPCEVENTCODE_Smelting					= 2,
	NPCEVENTCODE_Manufacture				= 3,
	NPCEVENTCODE_ResetItem					= 4,
	NPCEVENTCODE_CoinShop					= 5,
	NPCEVENTCODE_FuryArenaNPCTeleportCT2	= 6,
	NPCEVENTCODE_FuryArenaNPCEnter			= 7,
	NPCEVENTCODE_SocketSystemNPCDrill		= 8,
	NPCEVENTCODE_SocketSystemNPCStone		= 9,
	NPCEVENTCODE_EasterNPC					= 10,
	NPCEVENTCODE_LarryQuestsNPC				= 11,
	NPCEVENTCODE_IhinEvent					= 12,
	NPCEVENTCODE_MarinaQuestsNPC			= 13,
	NPCEVENTCODE_RudolphXmasNPC				= 14,
};

enum EMapID;

#define UNIT_LEVEL_MAX		160

static const INT64 uUnitExpTables[] =
{
	0,//			1
	1000,//		2
	2500,//		3
	5000,//		4
	9500,//		5
	17100,//		6
	29925,//		7
	51471,//		8
	87500,//		9
	140001,//		10
	212801,//		11
	306434,//		12
	416750,//		13
	537608,//		14
	672010,//		15
	833293,//		16
	1024950,//	17
	1250439,//	18
	1515533,//	19
	1824702,//	20
	2182343,//	21
	2592624,//	22
	3059296,//	23
	3591614,//	24
	4195005,//	25
	4874596,//	26
	5635033,//	27
	6480288,//	28
	7413449,//	29
	8443919,//	30
	9575404,//	31
	10820207,//	32
	12194373,//	33
	13706475,//	34
	15378665,//	35
	17224105,//	36
	19273774,//	37
	21548079,//	38
	24069204,//	39
	26861232,//	40
	29950274,//	41
	33364605,//	42
	37134805,//	43
	41293904,//	44
	45836233,//	45
	50878219,//	46
	56474823,//	47
	62687054,//	48
	69582630,//	49
	77236719,//	50
	85809995,//	51
	95334904,//	52
	105917079,//	53
	117673875,//	54
	130735675,//	55
	145312702,//	56
	161515069,//	57
	179523999,//	58
	199540925,//	59
	221789738,//	60
	246630189,//	61
	274252770,//	62
	304969080,//	63
	339125617,//	64
	377107687,//	65
	419532302,//	66
	466729685,//	67
	519236775,//	68
	577650912,//	69
	642636640,//	70
	715254581,//	71
	796078348,//	72
	886035202,//	73
	986157179,//	74
	1097592941,//	75
	1222169740,//	76
	1360886005,//	77
	1515346567,//	78
	1687338402,//	79
	1878851311,//	80

	2104313468,	//81
	2356831084,	//82
	2639650815,	//83
	2956408912,	//84
	3311177982,	//85
	3708519340,	//86
	4153541661,	//87
	4651966660,	//88
	5210202659,	//89
	6252243191,	//90
	7502691829,	//91
	9003230195,	//92
	10803876234,	//93
	12964651481,	//94
	15557581778,	//95
	18669098134,	//96
	22402917760,	//97
	26883501313,	//98
	32260201575,	//99
	38712241890,	//100
	46454690268,    //101
	55745628322,    //102
	66894753987,    //103
	80273704784,    //104
	96328445741,    //105
	115594134890,   //106
	138712961868,   //107
	166455554241,   //108
	199746665090,   //109
	239695998108,   //110
	287635197729,	//111
	345162237275,	//112
	414194684730,	//113
	497033621676,	//114
	596440346012,	//115
	715728415214,	//116
	858874098257,	//117
	1030648917908,	//118
	1236778701490,	//119
	1484134441788,	//120

	1780961330146,	//121
	2137153596175,	//122
	2564584315410,	//123
	3077501178492,	//124
	3693001414190,	//125
	4431601697028,	//126
	5317922036434,	//127
	6381506443721,	//128
	7657807732465,	//129
	9189369278958,	//130
	11027243134750,	//131
	13232691761700,	//132
	15879230114040,	//133
	19055076136848,	//134
	22866091364218,	//135
	27439309637062,	//136
	32927171564474,	//137
	39512605877369,	//138
	47415127052843,	//139
	56898152463412,	//140
	67708801431460,	//141
	79896385689122,	//142
	93478771256272,	//143
	108435374657275,	//144
	124700680855866,	//145
	142158776175687,	//146
	160639417078526,	//147
	179916147127949,	//148
	199706923312023,	//149
	219677615643225,	//150
	263613138771870,	//151
	316335766526244,	//152
	379602919831492,	//153
	455523503797791,	//154
	546628204557349,	//155
	655953845468818,	//156
	787144614562581,	//157
	944573537475097,	//158
	1133488244970116,	//159
	1360185893964140,	//160
	1632223072756976,	//161
	-1,
};


static CharacterDataState sCharacterDataState[10] =
{
	{CHARACTERCLASS_Fighter,        28,       6,      21,     17,      27}, //武士
	{CHARACTERCLASS_Mechanician,    24,       8,      25,     18,      24}, //机械
	{CHARACTERCLASS_Archer,			17,       11,     21,     27,      23},  //弓手
	{CHARACTERCLASS_Pikeman,        26,       9,      20,     19,      25}, //枪兵
	{CHARACTERCLASS_Atalanta,		23,       15,     19,     19,      23}, //魔枪
	{CHARACTERCLASS_Knight,			26,       13,     17,     19,      24}, //游侠
	{CHARACTERCLASS_Magician,		16,       29,     19,     14,      21},  //法师
	{CHARACTERCLASS_Priestess,		15,       28,     21,     15,      20}, //祭司
	{CHARACTERCLASS_Assassin,		25,       10,     22,     20,      22},  //刺客
	{CHARACTERCLASS_Shaman,			15,       27,     20,     15,      22},  //法师
};

struct PacketUnitStatusMove : Packet
{
	ID					  lID;
	Point3D				  sPosition;
	short				  sAngleX;
	short				  sAngleY;
	short				  sAngleZ;
	short				  sAnimationType;
	int					  iFrame;
	DWORD				  dwHashCharacterName;
}; //Size = 0x28

struct ModelAnimation
{
	EAnimationType		iType;

	DWORD				MotionKeyWord_1;
	DWORD				StartFrame;
	DWORD				MotionKeyWord_2;
	DWORD				EndFrame;

	DWORD				EventFrame[4];

	int					ItemCodeCount;
	WORD				ItemCodeList[52];
	DWORD				dwJobCodeBit;
	BYTE				SkillCodeList[8];

	int					MapPosition;

	DWORD				Repeat;
	CHAR				KeyCode;
	int					MotionFrame;
};


struct UnitInfo
{
	char					szName[32];

	short					SkillDamage[2];
	int						SkillRange;
	int						SkillRating;
	int						SkillDistance;
	RECT					SkillRangeRect;
	int						SkillCurse;

	int						AttackPattern;
	int						iActiveHour;
	int						IQ;
	EMonsterNature			iNature;
	int						Undead;
	int						iGroupLimitMin;
	int						iGroupLimitMax;
	int						iExp;
	int						SpAttackPercetage;
	int						MoveRange;

	int			DamageStunPers;

	int			iMaxPotions;
	int			iPerPotions;

	BOOL		bPublicDrop;
	int			iDropCount;
	int			iDropPercentNum;

	int			iNumDrops;
	int			iDropPlusCount;

	int			ClassCode;

	int			UseEventModel;

	int			iSight;

	DropSettingsData	saDropData[200];
	DropSettingsData	saDropDataCustom[3];

	int		iWeaponShopCounter;
	DWORD	dwaWeaponShop[32];
	int		iDefenseShopCounter;
	DWORD	dwaDefenseShop[32];
	int		iMiscShopCounter;
	DWORD	dwaMiscShop[32];

	int		iSkillMaster;
	int		iSkillMasterRank;
	int		iWarehouse;
	int		iMixMaster;
	int		iAgeMaster;
	int		CollectMoney;
	int		iEventGirl;
	int		iSmelting;
	int		Manufacture;
	int		MixtureReset;
	int		Element;
	int		Caravan;
	int		ItemSocket;


	ESpecialUnitType		eSpecialType;
	int		EventInfo;
	DWORD	iQuestItemID;
	int		iBellatraTypeNPC;
	int		iClanController;
	int		iItemBox;
	int		iWarpgate;
	int		StarPointNpc;
	int		GiveMoneyNpc;
	int		iTeleport;
	int		iCastleController;
	int		PollingNpc;

	char	*szMediaPlayNPC_Title;
	char	*szMediaPlayNPC_Path;

	int		iQuestTypeID;
	int		iQuestSubID;

	short	OpenCount[2];

	BOOL	bGMOnly;

	DWORD	dwHashCharacterName;

	char	*pszaMessage[MAX_NPC_MESSAGE];
	int		iNumMessage;
};

struct CharacterData
{
	char				szName[32];
	union
	{
		struct
		{
			char		szBodyModel[64];
			char		szHeadModel[60];
			int			iPlayerID;
		} Player;
		struct
		{
			char		szBodyModel[64];
			char		szHeadModel[60];
			int			iMonsterID;
		} Monster;
		struct
		{
			char		szBodyModel[64];
			char		szHeadModel[60];
			int			iNPCID;
		} NPC;
		struct
		{
			char		szBodyModel[65];
			char		szOwnerName[63];
		} Pet;
	};

	ID					iID;
	unsigned int		iClanID;
	ECharacterType		iType;
	int					SizeLevel;
	int					iShadowSize;
	EMonsterEffectID	iMonsterEffectID;
	ECharacterClass		iClass;
	int					iLevel;
	int					iStrength;
	int					iSpirit;
	int					iTalent;
	int					iAgility;
	int					iHealth;
	int					iAccuracy;
	int					iAttackRating;
	int					iMinDamage;
	int					iMaxDamage;
	int					iAttackSpeed;
	int					iAttackRange;
	int					iCritical;
	int					iDefenseRating;
	int					iBlockRating;
	int					iAbsorbRating;
	int					iMovementSpeed;
	int					iSight;

	CurMax				sWeight;
	short				sElementalDef[8];
	short				sElementalAtk[8];
	WORD				wPlayerKilling[2];
	DWORD				dwEventTime_T;
	CurMax				sHP;
	CurMax				sMP;
	CurMax				sSP;
	float				fHPRegen;
	float				fMPRegen;
	float				fSPRegen;
	INT64				iExp;
	int					iOwnerID;
	int					iGold;
	union
	{
		struct UnitInfo	* psUnitInfo;
		int				 sBSAL;
	};
	EMonsterType		iMonsterType;
	int					iStatPoints;
	BYTE				bUpdateInfo[4];
	MinMax				sViewBoxZoom;
	int					iHPType;
	int					iMPType;
	int					iSPType;
	DWORD				dwChecksum;
	DWORD				RefomCode;
	DWORD	dwObjectSerial;
	int					iPotionStorage;
	int					iRank;
	EClassFlag			iFlag;
	short				sGlow;
	short				sSize;
	short				sEventParam[2];

	short				sPresentItem[2];

	short				GravityScroolCheck[2];

	int					CostmePos;

	DWORD				dwTemp[10];

	BOOL				bExclusiveBoss;
	BOOL				bGrandFuryBoss;

	WORD				wVersion[2];
};

struct QuestCharacterSave
{
	WORD	wQuestCode[2];

	DWORD	Data[7];
};

struct LastQuestSave
{
	WORD wLastQuest[MAX_LAST_QUEST];
	int	LastQuestCount;
};

struct CharacterSave
{
	DWORD	dwHeader;

	int		iMapID;
	int		iCameraMode;
	int		iCameraPositionX;
	int		iCameraPositionZ;
	int		iLastGold;

	DWORD	dwChecksum;

	RecordSkill	sSkillInfo;

	int		iSaveTime;

	int		PCRNo;
	short	EventPlay[2];

	short	sPetInfo[2];

	short	sPotionUpdate[2];
	short	sPotionCount[3][4];
	WORD	wForceOrbUsing[2];

	DWORD	dwLevelQuestLog;

	int		ShortKey_NormalAttack;

	int		BlessCastleTax;
	DWORD	dwBlessCastleMaster;

	DWORD	dwElementaryQuestLog;

	DWORD	dwTime_PrimeItem_X2;
	DWORD	dwTime_PrimeItem_ExpUp;
	DWORD	dwTime_PrimeItem_VampCuspid;
	DWORD	dwTime_PrimeItem_ManaRecharg;
	DWORD	dwPrimeItem_PackageCode;
	DWORD	dwTime_PrimeItem_MightofAwell;
	DWORD	dwTime_PrimeItem_MightofAwell2;
	DWORD	dwTime_PrimeItem_ManaReduce;
	DWORD	dwTime_PrimeItem_PhenixPet;
	DWORD	dwTime_PrimeItem_HelpPet;
	DWORD	dwTime_PrimeItem_VampCuspid_EX;
	DWORD	dwTime_PrimeItem_StaminaReduce;

	int		TotalSubExp;
	int		TotalMoney;
	int		TotalExp;

	char	szMasterID[32];	

	QuestCharacterSave			QuestInfo;
	LastQuestSave	LastQuestInfo;

	DWORD	TT_ServerID;

	WORD	wLifeBoosterUsing[2];
	WORD	wManaBoosterUsing[2];
	WORD	wStaminaBoosterUsing[2];

	WORD	wSkillDelayUsing[2];
	DWORD	dwTime_CaravanHopy;
	DWORD	dwPhoenix;
	WORD	wFruitStatus[2];
	BYTE	TempStatus[8];
	DWORD	dwCaravanParam;
	DWORD	dwTime_PrimeItem_BigHead;
	DWORD	dwPrimeItem_BigHead;

	DWORD	dwTemp2[26];
};

struct	CharacterFile : Packet
{
	char	szHeader[8];

	CharacterData sCharInfo;

	CharacterSave	GameSaveInfo;

	DropItemData	ThrowItemInfo[64];
	int		ThrowItemCount;

	int		ItemCount;
	int		ItemSubStart;

	int		DataSize;
	BYTE	Data[sizeof(sRECORD_ITEM) * 200];
};
struct	PacketCharacterRecordData : Packet
{
	char			szHeader[8];

	CharacterData	sCharacterData;
	CharacterSave	sCharacterSaveData;

	DropItemData	sDropItemData[64];
	int				iDropItemCount;

	int				iItemCount;
	int				iItemSubStart;

	int				iDataSize;
	BYTE			baData[sizeof(RecordItem) * 200];
};
struct PacketGameStatusBase : Packet
{
	int					  iStatusID;
	ID					  lID;
};

struct PacketGameStatusBabelStormMap : PacketGameStatusBase
{
	EMapID				  eBabelStormMapID;
};

struct PacketUnitInfo : Packet
{
	CharacterData			sCharacterData;
	ID						iID;
	Point3D					sPosition;
	Point3D					sAngle;
	BOOL					bActive;
};

struct PacketGameStatusBlessCastle : PacketGameStatusBase
{
	int					iCastMode;
	int					iDefenseLevel;
	int					iClanID;
	BYTE				baSoldierCount[4];
	short				saTimeSec[2];
	short				sConRate;
	short				sBattlePoints;
};

struct PacketGameStatusPvPMap : PacketGameStatusBase
{
	EMapID				  iPvPMapID;
};

struct AttackDamageData
{
	int					iID;
	int					iDamage;
	int					iCounter;
};

static DWORD GetCodeFromCharacterData(CharacterData *psCharacterData)
{
	BYTE *pbBuff = (BYTE *)psCharacterData;

	DWORD dwKey = 0;

	for (int i = 0; i < sizeof(CharacterData); i++)
		dwKey += pbBuff[i];

	DWORD dwCode = 0;

	for (int i = 0; i < sizeof(CharacterData); i++)
		dwCode += (dwKey + i)*pbBuff[i];

	return dwCode;
}