#pragma once

//Lag Grace = 10 minutes
#define MAX_LAGGRACE			1000 * 60 * 10
#define NUM_ENCKEYS				256

#define MAX_PKTSIZ				0x2000
#define PKTHDR_ENCMAX			0x10

#define DISTANCE_UNIT_FAR				0x12C000
#define DISTANCE_UNIT_VIEWLIMIT			(64*64)
#define DISTANCE_UNIT_NEAR				((10*64)*(10*64))
#define DISTANCE_UNIT_PARTY_MAX			((17*64))

#define PKTLENBFRHDR			4
#define PKTLEN					WORD
#define PKTENC					BYTE
#define PKTCRC					BYTE
#define PKTHDR					DWORD

enum EChatColor;

enum PacketsHeader
{
	PKTHDR_KeySet						= 0x4847FFFF,
	//Net Server
	PKTHDR_NetIdentifier				= 0x7F000001,
	PKTHDR_NetExp						= 0x7F000002,
	PKTHDR_NetGetExp					= 0x7F000003,
	PKTHDR_NetGameMaster				= 0x7F000004,
	PKTHDR_NetGetGameMaster				= 0x7F000005,
	PKTHDR_NetClan						= 0x7F000006,
	PKTHDR_NetDisconnectUser			= 0x7F000007,
	PKTHDR_NetForceOrb					= 0x7F000008,
	PKTHDR_NetVersion					= 0x7F000009,
	PKTHDR_NetCharacterSync				= 0x7F00000A,
	PKTHDR_NetGiveExp					= 0x7F00000B,
	PKTHDR_NetPingPong					= 0x7F00000C,
	PKTHDR_NetBCStatusReq				= 0x7F00000D,
	PKTHDR_NetBCStatusSnd				= 0x7F00000E,
	PKTHDR_NetBCNewOwnerClanID			= 0x7F00000F,
	PKTHDR_NetBotAdd					= 0x7F000010,
	PKTHDR_NetPremiumEXP				= 0x7F000011,
	PKTHDR_NetUnloadUser				= 0x7F000012,
	PKTHDR_NetEXPEvent					= 0x7F000013,
	PKTHDR_NetTradeCoin					= 0x7F000014,
	PKTHDR_NetUsersOnline				= 0x7F000015,
	PKTHDR_NetQuestT5Data				= 0x7F000016,
	PKTHDR_NetQuestUpdateData			= 0x7F000017,
	PKTHDR_NetGiveGold					= 0x7F000018,
	PKTHDR_NetPremium					= 0x7F000019,

	//Packets Protect
	PKTHDR_LogCheat						= 0x6F6A0001,
	PKTHDR_DCAccount					= 0x6A6A0001,
	PKTHDR_ReconnectedServer			= 0x6A6A0002,
	PKTHDR_SendToLoginServer			= 0x6A6A0003,
	PKTHDR_Microphone					= 0x6A6A0004,
	PKTHDR_LogDataSimple				= 0x6A6A0005,
	PKTHDR_CheckSum						= 0x6A6A0006,
	PKTHDR_LogDebugger					= 0x6A6A0008,
	PKTHDR_UndentifiedPacket			= 0x6A6A0007,
	PKTHDR_AddExp						= 0x6A6A0009,
	PKTHDR_LoseExp						= 0x6A6A000A,
	PKTHDR_GetItemData					= 0x6A6A000B,
	PKTHDR_SetItemData					= 0x6A6A000C,
	PKTHDR_SetGold						= 0x6A6A000D,
	PKTHDR_WindowList					= 0x6A6A000E,
	PKTHDR_SettingsData					= 0x6A6A000F,
	PKTHDR_RetryWarehouse				= 0x6A6A0010,
	PKTHDR_WarehouseSaveSuccess			= 0x6A6A0011,
	PKTHDR_DamageQuick					= 0x6A6A0012,
	PKTHDR_QuestNPCOpen					= 0x6A6A0013,
	PKTHDR_QuestNPCAccept				= 0x6A6A0014,
	PKTHDR_QuestStartData				= 0x6A6A0015,
	PKTHDR_QuestUpdateData				= 0x6A6A0016,
	PKTHDR_QuestCancel					= 0x6A6A0017,
	PKTHDR_QuestNPCFinish				= 0x6A6A0018,
	PKTHDR_QuestNPCItemList				= 0x6A6A0019,
	PKTHDR_QuestHandleFinished			= 0x6A6A001A,
	PKTHDR_CharacterDataEx				= 0x6A6A001B,
	PKTHDR_ItemSlotHandle				= 0x6A6A001C,
	PKTHDR_T5QuestArena					= 0x6A6A001D,
	PKTHDR_DynamicQuestOpen				= 0x6A6A001F,
	PKTHDR_DynamicQuestOpenNPC			= 0x6A6A0020,
	PKTHDR_QuestItemSwap				= 0x6A6A0021,
	PKTHDR_BossTimeUpdate				= 0x6A6A0022,
	PKTHDR_UseGold						= 0x6A6A002B,
	PKTHDR_UseItem						= 0x6A6A002C,

	//Party
	PKTHDR_RequestParty					= 0x6A6A0023,
	PKTHDR_JoinParty					= 0x6A6A0024,
	PKTHDR_UpdateParty					= 0x6A6A0025,
	PKTHDR_UpdatePartyData				= 0x6A6A0026,
	PKTHDR_ActionParty					= 0x6A6A0027,
	PKTHDR_RequestRaid					= 0x6A6A0028,
	PKTHDR_JoinRaid						= 0x6A6A0029,

	//Packets Event
	PKTHDR_KillsInSod					= 0x503220B1,

	//Packets Sync Data
	PKTHDR_PersonalShopMessage			= 0x48478AC0,
	PKTHDR_SkillStatusContainer			= 0x435A000D,
	PKTHDR_SkillStatus					= 0x435A000E,
	PKTHDR_PlayDataChar					= 0x48470013,
	PKTHDR_UnitStatusContainer			= 0x48470014,
	PKTHDR_GameStatus					= 0x48470018,
	PKTHDR_CharacterData				= 0x48470020,
	PKTHDR_GetUnitInfoData				= 0x48470021,
	PKTHDR_UpdateCharacterData			= 0x48470032,
	PKTHDR_UseEffect					= 0x4847005C,
	PKTHDR_Disconnect					= 0x484700E6,
	PKTHDR_Save							= 0x484700E8,
	PKTHDR_ChatGame						= 0x48471001,
	PKTHDR_ChatMessage					= 0x48471005,
	PKTHDR_ChatItemLink					= 0x48471007,
	PKTHDR_Reconnect					= 0x48478010,
	PKTHDR_ReconnectLogin				= 0x48478011,
	PKTHDR_ChatMessageBox				= 0x48478100,
	PKTHDR_Ping							= 0x435A0007,
	PKTHDR_SaveAndClose					= 0x435A0011,
	PKTHDR_KillCharacter				= 0x50320E00,

	// Packets Login
	PKTHDR_Connected					= 0x48470080,
	PKTHDR_SaveData						= 0x48470081,
	PKTHDR_SelectCharacter				= 0x48470082,
	PKTHDR_NewCharacter					= 0x48470083,
	PKTHDR_SaveResult					= 0x48470084,
	PKTHDR_UserInfo						= 0x48470086,
	PKTHDR_DeleteCharacter				= 0x48470087,
	PKTHDR_CreateCharacter				= 0x48470088,
	PKTHDR_Version						= 0x4847008A,
	PKTHDR_ServerList					= 0x484700C0,
	PKTHDR_AccountLoginCode				= 0x48470023,
	PKTHDR_LoginUser					= 0x48480001,

		//Coin Shop
	PKTHDR_CoinShopNPC					= 0x48476A01,
	PKTHDR_CoinShopAmount				= 0x48476A02,
	PKTHDR_CoinShopOpenTab				= 0x48476A03,
	PKTHDR_CoinShopTab					= 0x48476A04,
	PKTHDR_CoinShopOpenItemData			= 0x48476A05,
	PKTHDR_CoinShopItemData				= 0x48476A06,
	PKTHDR_CoinShopBuy					= 0x48476A07,
	PKTHDR_OpenCoinShop					= 0x48476A08,
	PKTHDR_CoinServiceOpen				= 0x48476A09,
	PKTHDR_CoinServiceBuy				= 0x48476A0A,
	PKTHDR_CoinServiceAgingRecoveryOpen	= 0x48476A0B,
	PKTHDR_CoinTraded					= 0x48476A0C,
	PKTHDR_CoinTradeSet					= 0x48476A0D,

		//Distributor
	PKTHDR_DistrbutorNPC				= 0x48476A0E,
	PKTHDR_DistrbutorItemShow			= 0x48476A0F,
	PKTHDR_DistrbutorItemAccept			= 0x48476A10,
	PKTHDR_DistrbutorItemDelete			= 0x48476A11,
	PKTHDR_DistrbutorItemSend			= 0x48476A12,

		//Packet Skills
	PKTHDR_BuffSkillsParty				= 0x50320A00,
	PKTHDR_CancelDrasticSpirit			= 0x50320A11,
	PKTHDR_CancelSkill					= 0x50320A10,
	PKTHDR_SkillCast					= 0x50320A20,
	PKTHDR_SkillCastData				= 0x50320A30,
	PKTHDR_BlessCastleSkill				= 0x50320A35,
	PKTHDR_EvasionSuccess				= 0x50320A50,
	PKTHDR_PartyUsePot					= 0x484700D0,
	PKTHDR_HolyMind						= 0x484700D3,
	PKTHDR_Wisp							= 0x484700C3,

	//Packets Unit
	PKTHDR_UnitStatusMove				= 0x48470010,
	PKTHDR_OpenNPC						= 0x48470024,
	PKTHDR_NpcData						= 0x48470070,
	PKTHDR_SetExpOld					= 0x48470031,

	//Packets Buff
	PKTHDR_IceDistortionBuff			= 0x48478008,
	PKTHDR_PoisionDistortionBuff		= 0x4847800A,
	PKTHDR_FireDistortionBuff			= 0x4847800B,

	//Packets Item
	PKTHDR_DeleteItem					= 0x48470051,
	PKTHDR_NewItem						= 0x48470052,
	PKTHDR_PutItem						= 0x4847005A,
	PKTHDR_IntegrityUpdateItem			= 0x6A6A002A,

	//Packets Map
	PKTHDR_WarpGateField				= 0x48470040,
	PKTHDR_DeleteFlagPoint				= 0x48470061,
	PKTHDR_TheDeath						= 0x48478800,
	PKTHDR_PlayItem						= 0x48470050,
	PKTHDR_UseUnionCore					= 0x50320206,
	PKTHDR_BellatraInformation			= 0x503220B0,
	PKTHDR_BlessCastleInfomation		= 0x503220C0,
	PKTHDR_BlessCastleTax				= 0x503220D0,
	PKTHDR_BlessCastleShowDamage		= 0x503220D1,

	//Character
	PKTHDR_PacketFun					= 0x43550001,
	PKTHDR_DamageDebugInfo				= 0x43550004,
	PKTHDR_ServerInfo					= 0x43550005,
	PKTHDR_PlayDataEx					= 0x43550006,
	PKTHDR_PremiumData					= 0x43550007,
	PKTHDR_SetItemTimer					= 0x43550008,
	PKTHDR_DisableGM					= 0x43550009,
	PKTHDR_PVPDataUpdate				= 0x4355000F,
	PKTHDR_UpdateSWPhase				= 0x43550010,
	PKTHDR_CrystalUse					= 0x43550012,
	PKTHDR_CrystalUseDie				= 0x43550013,
	PKTHDR_UserOnline					= 0x43550014,
	PKTHDR_CancelForceOrb				= 0x43550015,
	PKTHDR_PvPKill						= 0x43550018,
	PKTHDR_CharacterHeadOldUse			= 0x4355001A,
	PKTHDR_BlessCastleIndividualScore	= 0x4355001B,
	PKTHDR_BlessCastleUserScoreUpdate	= 0x4355001C,
	PKTHDR_CancelItemTimer				= 0x4355001E,
	PKTHDR_GameMasterStatus				= 0x4355001F,
	PKTHDR_GameMasterCheck				= 0x43550020,
};

enum EPvPKillType
{
	PVPKILLTYPE_None,
	PVPKILLTYPE_DoubleKill,
	PVPKILLTYPE_TripleKill,
	PVPKILLTYPE_QuadraKill,
	PVPKILLTYPE_PentaKill,
	PVPKILLTYPE_Shutdown,
	PVPKILLTYPE_Rampage,
	PVPKILLTYPE_Unstoppable,
	PVPKILLTYPE_COUNT,
};

enum ELogCheat
{
	CHEATLOGID_DelaySkillHack				= 52,
	CHEATLOGID_ValidateCharacterError		= 81,
	CHEATLOGID_CopiedItemError				= 99,
	CHEATLOGID_CopiedItem					= 1000,
	CHEATLOGID_CopiedItemWarehouse			= 1010,
	CHEATLOGID_WarehouseGold				= 1011,
	CHEATLOGID_WarehouseNewClone			= 1012,
	CHEATLOGID_WarehouseBug					= 1013,
	CHEATLOGID_HackDetected					= 1100,
	CHEATLOGID_FocusChanged					= 1101,

	CHEATLOGID_GoldLimit					= 1150,
	CHEATLOGID_SpeedHack					= 1200,
	CHEATLOGID_TimeErrorSpeedHack			= 1250,
	CHEATLOGID_TimeMismatch					= 1400,
	CHEATLOGID_AttackRatioError				= 1500,
	CHEATLOGID_PotionCheckError				= 1510,
	CHEATLOGID_PotionCountError				= 1530,

	CHEATLOGID_CharInfoSaveError			= 1600,
	CHEATLOGID_DefaultAttackRatingError		= 1820,
	CHEATLOGID_DefaultAttackSizeError		= 1821,
	CHEATLOGID_ContinuousAttackError		= 1823,
	CHEATLOGID_SkillAttackRatingError		= 1830,
	CHEATLOGID_SkillContinuousAttackError	= 1833,
	CHEATLOGID_RestrictedAreaTrespassed		= 1840,
	CHEATLOGID_WeightError					= 1900,

	CHEATLOGID_ItemError					= 1950,
	CHEATLOGID_CopiedItemRecall				= 1960,
	CHEATLOGID_ForcedPenaltyBoot			= 2000,
	CHEATLOGID_SavedItemError				= 2400,
	CHEATLOGID_ContinuousSaveFailedError	= 2700,
	CHEATLOGID_AccountCharacterError		= 2800,
	CHEATLOGID_TradeAuthorizationError		= 4000,
	CHEATLOGID_MoneyTransferError			= 4100,
	CHEATLOGID_MultipleConnectionsIP		= 5000,
	CHEATLOGID_TooManyPackets				= 5100,
	CHEATLOGID_GameServerIPError			= 5200,
	CHEATLOGID_StartCharacterError			= 6000,
	CHEATLOGID_ServerMoneyError1			= 6610,
	CHEATLOGID_ServerMoneyError2			= 6611,
	CHEATLOGID_ServerMoneyError3			= 6612,
	CHEATLOGID_ItemCodeError				= 6800,
	CHEATLOGID_ItemTempCodeError			= 6810,
	CHEATLOGID_CharacterStateError1			= 6900,
	CHEATLOGID_CharacterSkillPointError		= 6910,
	CHEATLOGID_CharacterWeightError			= 6920,
	CHEATLOGID_ClientProcessTimeOut			= 7000,
	CHEATLOGID_InventoryItemError			= 7010,
	CHEATLOGID_CharacterModelError			= 7020,
	CHEATLOGID_JobCodeError					= 7030,

	CHEATLOGID_ClientAttackDefenseError		= 7100,
	CHEATLOGID_ClientEnergyBarError			= 7110,
	CHEATLOGID_CopiedItemFromFloor			= 7130,
	CHEATLOGID_TriedConnectDisableIP		= 7140,
	CHEATLOGID_ItemErrorInventory			= 7150,
	CHEATLOGID_MoneyErrorInventory			= 7160,

	CHEATLOGID_ServerItemErrorInventory		= 8000,
	CHEATLOGID_ItemErrorInventoryRecord		= 8001,
	CHEATLOGID_ServerMoneyErrorInventory	= 8010,
	CHEATLOGID_ServerToServerItemError		= 8020,
	CHEATLOGID_WrongSavingCharacterName		= 8030,
	CHEATLOGID_ItemPositionError			= 8040,
	CHEATLOGID_ServerInventoryUsedFull		= 8050,
	CHEATLOGID_UsedItemCodeWarning			= 8060,
	CHEATLOGID_ServerInventoryCopiedItem	= 8070,
	CHEATLOGID_ServerCopiedItemWarehouse	= 8071,
	CHEATLOGID_MemoryBufferSavingError		= 8080,
	CHEATLOGID_WarningAutoMouse				= 8100,
	CHEATLOGID_WarningMacroMouse			= 8102,
	CHEATLOGID_WarningAvgDamageDefense		= 8110,
	CHEATLOGID_WarningAvgDamageAttack		= 8120,
	CHEATLOGID_AgingFailedCopiedItemSheltom = 8200,
	CHEATLOGID_AgingFailedCopiedItem		= 8210,
	CHEATLOGID_ReconnectServer				= 8300,
	CHEATLOGID_CheckedInventoryData			= 8400,
	CHEATLOGID_TeleportFieldHack			= 8401,
	CHEATLOGID_DamagePacketError			= 8500,
	CHEATLOGID_LimitDamageOver				= 8510,
	CHEATLOGID_ClientWarningMotionSpeed		= 8520,
	CHEATLOGID_ClientWarningSkillAttack		= 8530,
	CHEATLOGID_ClientWarningSkillForgery	= 8540,
	CHEATLOGID_ClientWarningSkillForgery2	= 8550,
	CHEATLOGID_InitialCharacterLevelError	= 8560,
	CHEATLOGID_TooManyUpdatedCharInfo		= 8570,
	CHEATLOGID_ClientDamagePacketError		= 8580,
	CHEATLOGID_WarningInvincibleMode		= 8600,
	CHEATLOGID_FindThreadHack				= 8720,
	CHEATLOGID_CharacterStateError2			= 8730,
	CHEATLOGID_ServerPotionError			= 8800,
	CHEATLOGID_ServerPotionMovingError		= 8810,
	CHEATLOGID_LevelQuestCodeWarning		= 8820,
	CHEATLOGID_ShopBuyForgeryItem			= 8830,
	CHEATLOGID_ServerMoneyOverflow			= 8840,
	CHEATLOGID_SkillUsedLevelError			= 8850,
	CHEATLOGID_CheckPlayFieldWarning		= 8860,
	CHEATLOGID_CompareClanCodeError			= 8870,
	CHEATLOGID_ModelFileError				= 8880,
	CHEATLOGID_WarningCharacterReloading	= 8890,
	CHEATLOGID_FieldNPCWarning				= 8900,
	CHEATLOGID_LevelHack					= 8901,
	CHEATLOGID_ItemMeshError				= 8910,
	CHEATLOGID_IllegallyServerConnect		= 8920,

	CHEATLOGID_MatureHack					= 8950,
	CHEATLOGID_AgingHack					= 8951,
	CHEATLOGID_FakeGM						= 8952,
	CHEATLOGID_RunSpeedHack					= 8953,
	CHEATLOGID_CheckSumFunctionError		= 8954,
	CHEATLOGID_WindowHack					= 8955,
	CHEATLOGID_StateCharacterHack			= 8956,
	CHEATLOGID_DebuggerHack					= 8957,
	CHEATLOGID_GMReason						= 8958,
	CHEATLOGID_BellatraGoldHackLeader		= 8959,
	CHEATLOGID_DefenseMultHack				= 8960,
	CHEATLOGID_RegenFormulaHack				= 8961,
	CHEATLOGID_EasterEggFakeItem			= 8962,
	CHEATLOGID_RespecFakeItem				= 8963,
	CHEATLOGID_NPCItemShopFakeItem			= 8964,
	CHEATLOGID_ItemTimerFakeInventory		= 8965,
	CHEATLOGID_ManufactureItemFake			= 8966,
	CHEATLOGID_SkillCooldown				= 8967,
	CHEATLOGID_XmasRudolphFakeBox			= 8968,

	CHEATLOGID_MemorySaveNameError1			= 10000,
	CHEATLOGID_MemorySaveNameError2			= 10001,
	CHEATLOGID_MemorySaveNameError3			= 10002,
	CHEATLOGID_MemorySaveNameError4			= 10003,
	CHEATLOGID_MemorySaveNameError5			= 10005,
	CHEATLOGID_InitialSaveMemoryError		= 10006,
	CHEATLOGID_SaveBufferPointError			= 10007,
	CHEATLOGID_CharacterAccountMismatch		= 10010,
	CHEATLOGID_AuthenticationError			= 10020,
	CHEATLOGID_ShutdownService				= 11000,
	CHEATLOGID_EventHighScore				= 21000,

	CHEATLOGID_GoldHackNPC					= 11037,
	CHEATLOGID_GoldHackWH					= 11034,
	CHEATLOGID_MixingItemHack				= 99000,
};

struct Packet //Header
{
	PKTLEN iLength;				//Packet Length
	PKTENC iEncKeyIndex = 0;	//Packet Encryption Key Index
	PKTENC iEncrypted = 0;		//Packet Encrypted
	PKTHDR iHeader;				//Packet Header
}; //Size = 0x08

struct PacketKeySet : Packet
{
	BYTE	  baKeySet[NUM_ENCKEYS];
};

struct PacketTime : Packet
{
	DWORD	  dwTime;
	ID		  iID;
	DWORD	  dwReserved1;
	DWORD	  dwReserved2;
};

struct PacketNetIdentifier : Packet
{
	int			iServerID;
	int			iPort;

	UINT		uPasswordNUM; //= 0x33445566
};
struct PacketNetExp : Packet
{
	UINT		uObjectID;
	INT64		iExp;
};
struct PacketNetForceOrbTime : Packet
{
	DWORD		dwObjectID;
	BOOL		bUpdate;
	DWORD		dwTime;
};

struct PacketNetEXPPotion : Packet
{
	DWORD		dwObjectID;
	BOOL		bExp;
};

struct PacketNetExpEvent : Packet
{
	int			iPercent;
};

struct PacketNetUsersOnline : Packet
{
	int			iID;
	int			iUsersOnline;
};

struct PacketNetClan : Packet
{
	UINT		uObjectID;
	DWORD		dwClan;
};

struct PacketNetCharacterSync : Packet
{
	DWORD		dwObjectID;
	char		szCharName[32];
};

struct PacketNetDisconnectUser : Packet
{
	DWORD		dwObjectID;
};

struct PacketNetUnloadUser : Packet
{
	DWORD		dwObjectID;
};

struct PacketNetGameMaster : Packet
{
	UINT		uObjectID;
	int			iGameMasterLevel;
};
struct PacketNetGetGameMaster : Packet
{
	UINT		uObjectID;
	int			iGameMasterLevel;
	char		szName[32];
};

struct PacketNetGetExp : Packet
{
	UINT		uObjectID;
};

struct PacketNetVersion : Packet
{
	int			iVersion;
};

struct PacketNetBCNewOwnerClanID : Packet
{
	DWORD		dwNewClanID;
};

struct PacketNetGold : Packet
{
	UINT		uObjectID;
	int			iGold;
};

struct PacketSync : Packet
{
	DWORD	  dwReserved1;
	DWORD	  dwTime;
	DWORD	  dwReserved2;
	DWORD	  dwReserved3;
};

struct PacketPing : Packet
{
	DWORD	  dwTime;
	DWORD	  dwTick;
};

struct PacketChat : Packet
{
	char szChat[128];
};
struct PacketVersion : Packet
{
	BOOL	bServerFull;
	int		iVersion;
	int		iUnk2;
};
struct PacketLoginUser : Packet
{

	DWORD			dwUnk[3];

	char			szUserID[32];
	char			szPassword[32];
	char			szMacAddr[20];
	char			szPCName[32];
	DWORD			dwSerialHD;

	char			szVideoName[256];

	UINT			uWidthScreen;
	UINT			uHeightScreen;

	int				iSystemOS;
};
struct	_TRANS_CHAR_INFO
{
	char	szName[32];
	char	szModelName[64];
	char	szModelName2[64];
	DWORD	JOB_CODE;
	int		Level;
	DWORD	Brood;
	DWORD	dwArmorCode;
	int		StartField;
	int		PosX, PosZ;
	DWORD	dwTemp[13];
};

struct PacketUserWarpEffect : Packet
{
	int					iX;
	int					iID;
	int					iY;
	int					iZ;
}; 
struct PacketUserValenToEffect : Packet
{
	ID					lMonsterID;
	int					iID;
	ID					lUserID;
};

struct	PacketUserInfo : Packet
{
	char					szUserID[32];
	int						CharCount;

	_TRANS_CHAR_INFO		sCharacterData[6];
};

struct PacketDeleteCharacter : Packet
{
	int						iUnknown;
	int						iCode;
	int						iUnk;
	char					szUserID[32];
	char					szCharname[32];
};
struct PacketCreateCharacter : Packet
{
	int						iUnknown;
	int						iCode;
	int						iUnk;
	char					szUserID[32];
	char					szCharname[32];
};
struct PacketSelectCharacter : Packet
{
	int dwReserved1;
	int dwReserved2;
	int dwReserved3;
	char szCharName[32];
};
struct PacketReconnectUser : Packet
{
	int		iUnk;
	DWORD	dwObjectID;
	char	szUserID[32];
};
struct PacketChatBoxMessage : Packet
{
	EChatColor	iChatColor;	//Chat Type, Party, Clan, Trade, etc.
	ID			lID;		//User ID, if 0 only shows in Chat Box, otherwise also above User
	char		szChatBoxMessage[256 + 8];
};
struct PacketUnitStatusContainer : Packet
{
	int			iAmount;
	int			iCounter;

	BYTE		baBuffer[0x1FF0];
};
struct PacketSettingsData : Packet
{
	BOOL		bNoTradeChat;
	BOOL		bNoPartyRequest;
	BOOL		bNoTradeRequest;
	BOOL		bNoWhisper;
};

enum EPhoenixType
{
	PHOENIXTYPEID_None,
	PHOENIXTYPEID_Fire,
	PHOENIXTYPEID_Ice,
	PHOENIXTYPEID_Lightning,
	PHOENIXTYPEID_Healing,
	PHOENIXTYPEID_ElementHealing = 2,
	PHOENIXTYPEID_DeleteMask = 4855374,
};
struct PacketPhoenixPet : Packet
{
	int										iElementType;			// 2 = Healing
	EPhoenixType							eType;
	int										iUnk;
	DWORD									dwMask;					// 4855374 = Delete Phoenix
};
struct PacketSetPremium : Packet
{
	DWORD									dwCode;
};
struct PacketExperience : Packet
{
	INT64		iAddExp;
};
struct PacketLoseExperience : Packet
{
	INT64		iSubExp;
	int			iLevel;
	int			iMapID;
	int			iPercent;
	BOOL		bRessurectionItem;
};

struct PacketLogCheat : Packet
{
	int			iLParam;
	int			iCheatID;
	int			iSParam;
	int			iEParam;

	int			iLxParam;
	int			iWxParam;
	int			iSxParam;
	int			iExParam;

};

struct PacketLogCheatEx : Packet
{
	int			iLParam;
	int			iCheatID;
	int			iSParam;
	int			iEParam;

	int			iLxParam;
	int			iWxParam;
	int			iSxParam;
	int			iExParam;

	char		szParam[256];
};
struct PlayBuffer
{
	int			iX;
	int			iY;
	int			iZ;
	DWORD		dwFrame;
	short		saAngle[4];
	short		sStickItems[4];
	DWORD		dwTargetSerial;
};
struct PlayBufferData
{
	int						iCount;
	PlayBuffer				sPlayBuff;
};

struct PacketPlayDataMinor : Packet
{
	DWORD					dwObjectID;
	int						iX;
	int						iY;
	int						iZ;
	short					saAngle[4];
	DWORD					dwFrame;
	DWORD					dwAutoCharCode;
};

struct PacketPlayData : Packet
{
	DWORD					dwObjectID;
	DWORD					dwTarget;

	int						iPlayBuffCount;
	int						iStartPosition;

	short					sHp[2];
	DWORD					dwAutoCharCode;
	short					sMapID;
	short					sUnk;
	BYTE					bUpdateInfo[4];
	BYTE					bEventInfo[4];

	CurMax					sMP;
	CurMax					sSP;

	bool					bPartyLeader;

	short					sSecondMapID;

	short					saSpeed[2];

	IMinMax					sHPLong;

	short					sAngleY;
	short					sSize;

	int						iLevel;

	BYTE					baPadding[0x2C];
};

struct PacketStageItemData : Packet
{
	struct StageItemData
	{
		BOOL								bActive;
		int									iType;
		int									iItemID;
		int									iX;
		int									iY;
		int									iZ;
		char								szName[32];
		int									iClass;
	};
	BOOL									bActive;
	int										iCount;
	StageItemData							saItems[50];
};

struct PacketBuffData : Packet
{
	DWORD					dwItemID;
	int						iTime;
	short					sColors[4];
	int						iClass;
	int						iScale;
};

struct PacketServerList : Packet
{
	struct Header
	{
		char				szServerName[16];
		DWORD				dwTime;
		int					iTicket;
		DWORD				dwUnknown;
		int					iClanServerIndex;
		int					iGameServers;
	};

	struct Server
	{
		char				szName[32];
		char				szaIP[3][20];
		int					iaPort[4];
	};

	Header					sHeader;
	Server					sServers[4];
};

struct PacketUserOnline : Packet
{
	int						iType;
	int						iID;
	BOOL					bOnline;
	char					szName[32];
};

struct PacketSimple : Packet
{
	int						iUnk;
	int						iUnk2;
	int						iUnk3;
	int						iUnk4;
};

struct PacketDeadCharacter : Packet
{
	int						iUnk;
	int						dwObjectID;
};
struct PacketPvPKillType : Packet
{
	char				szKillerName[32];
	char				szVictimName[32];

	int					iKillerClass;
	int					iVictimClass;

	int					iKillType;
};

struct PacketPvPData : Packet
{
	int					iPVPKills;
	int					iPVPDeaths;
	int					iPVPKillStreak;
	BOOL				bKill;
	int					iID;
};

struct PacketWarpGateField : Packet
{
	int					iZ;
	int					iStage;
	int					iX;
};
struct PacketDeleteFlagPoint : Packet
{
	int					iX;
	int					iZ;
};
struct PacketSetCharacterGold : Packet
{
	DWORD				dwGold;
};

// Save
struct	PacketSaveData : Packet
{
	int					iCurrentPage;
	int					iTotalPage;
	int					iDataSize;

	char				szData[8160];
};

struct PacketServerInfo : Packet
{
	int					iUsers;
	int					iMaxUsers;
	int					iBossTime;
	int					iServerVersion;
	short				sSiegeWarDay;
	short				sSiegeWarHour;
	BYTE				bSiegeWarType;
	BOOL				bGameMaster;
	SYSTEMTIME			sServerTime;
};

struct PacketExperienceOld : Packet
{
	int					iMonsterID;
	int					WParam;
	int					SParam;
	int					EParam;
};
struct PacketCrystalUse : Packet
{
	DWORD				dwObjectID;
	DWORD				dwItemID;
	DWORD				dwTime;
};
struct PacketCrystalUseDie : Packet
{
	DWORD				dwObjectID;
};

struct PacketSaveResult : Packet
{
	int					iUnk;
	BOOL				bResult;
	int					iTex;
	int					iClanID;
};

//BlessCastle

struct BlessCastleStatusShort
{
	DWORD				iClanID;
	int					iTax;
	int					iSkill;
	int					iaTowerType[6];
	int					iaGuardAmount[3];
};


struct PacketBlessCastleStatusSettingsData : Packet
{
	int					iMode;
	int					iTax;
	short				saTowerType[12];	//1 = ice, 2 = lightning, 3 = fire
	unsigned char		caGuardAmount[4];	//max = 20
	int					iSkill;				//1 = absorb, 2 = damage, 3 = evasion
	int					iPrice;
	DWORD				iClanID;
	DWORD				dwUnk[4];
};

#define MAX_TOP_DAMAGEDATA		10
#define MAX_DAMAGEDATA			100

enum ESiegeWarMode : int
{
	SIEGEWARMODE_Normal,
	SIEGEWARMODE_TheConquest,
	SIEGEWARMODE_TheMassacre,
};

struct PacketBlessCastleTopIndividual : Packet
{
	char				szCharacterName[3][32];
	int					iClass[3];
	int					iDamage[3];
	int					iMode;
};

struct PacketBlessCastleUserScoreUpdate : Packet
{
	int					iUserScore;
	int					iMode;
};

struct PacketBlessCastleTopData : Packet
{
	int					iUnk01;

	int					iID;
	DWORD				dwUnk02;

	Point3D				sPosition;

	DWORD				dwUnk03;
	DWORD				dwUpdateTime;
	DWORD				dwTotalDamage;

	BYTE				baCrystalTowerCount[4];
	DWORD				dwFree[2];

	union
	{
		int				iUserID[MAX_TOP_DAMAGEDATA];
		int				iClanID[MAX_TOP_DAMAGEDATA];
	};

	int					iDamage[MAX_TOP_DAMAGEDATA];
	int					iCounter[MAX_TOP_DAMAGEDATA];
};

struct BlessCastleStatusData
{
	int										iCastleMode;
	DWORD									iClanID;
	int										iDefenseLevel;
	DWORD									dwTimeLimit;
	int										iCounter;

	int										iTax;
	int										iTaxNow;

	DWORD									dwBattleOverTime;

	int										iFountainPotionCount;
	DWORD									dwFountainTime;
	DWORD									dwFountainLastUseTime;
	int										iFountainCountUsers;

	DWORD									dwStartTime;
	short									saTimeSec[2];
	int										iSkill;
	int										iUnk[10];
	PacketBlessCastleStatusSettingsData		sSettings;
	PacketBlessCastleTopData				sPacketTopData;
	struct AttackDamageData					* psaDamageData;

	BYTE									baSoldierCount[4];
	BYTE									baCrystalTowerCount[4];
	class Unit								* pcUnitDataTower;
	DWORD									dwScoreTime;
};

struct BlessCastlePVPLeague
{
	int						iMode;
	DWORD					dwBeginTime;
	DWORD					dwEndTime;
	DWORD					dwRestartTime;
};

struct PacketNetBCStatus : Packet
{
	BlessCastleStatusShort	sBlessCastleStatus;
};

struct PacketBlessCastleStatus : Packet
{
	BlessCastleStatusShort	sBlessCastleStatus;
};
struct PacketBlessCastleTex : Packet
{
	int iClanID;
	int iTax;
};
struct PacketBlessCastleSkill : Packet
{
	int iSkill;
	int iClanID;
	int iChk;
};
struct PacketSiegeWarPhase : Packet
{
	int					iPhaseID;
};

enum EDamageInfo : int
{
	DAMAGEINFO_Defence		= 1,
	DAMAGEINFO_Block		= 2,
	DAMAGEINFO_Evasion		= 3,
	DAMAGEINFO_Other		= 4,
	DAMAGEINFO_Normal		= 5,
	DAMAGEINFO_Ice			= 6,
};

struct PacketDebugDamageInfo : Packet
{

	DWORD				dwObjectID;
	EDamageInfo			iTypeAction;
	int					iValue;
};

enum EEffectID : int
{
	EFFECTID_None				= 0,
	EFFECTID_Warp				= 1,
	EFFECTID_AgingUp			= 2,
	EFFECTID_HolyIncAntation	= 3,
	EFFECTID_Resurrection		= 4,
	EFFECTID_Forceorb			= 5,
	EFFECTID_Valento			= 6,
	EFFECTID_FireFlower			= 7,
};

struct PacketUserEffect : Packet
{
	EEffectID eEffectID;
};

struct PacketUserEffectWarp : PacketUserEffect
{
	Point3D sPosition;
};

struct PacketUserEffectAgingUp : PacketUserEffect
{
	ID lID;
};

struct PacketUserEffectHolyIncAntation : PacketUserEffect
{
	ID lID;
	int iTime;
};

struct PacketUserEffectResurrection : PacketUserEffect
{
	ID lID;
};

struct PacketUserEffectForceorb : PacketUserEffect
{
	ID lID;
};

struct PacketUserEffectValento : PacketUserEffect
{
	ID lUserID;
	ID lMonsterID;
};
struct PacketUserEffectFireFlower : PacketUserEffect
{
	ID lID;
	int iNumber;
};

static EEffectID IsUseEffect(PacketUserEffect * psPacket)
{
	if (psPacket->eEffectID == EFFECTID_Warp ||
		psPacket->eEffectID == EFFECTID_AgingUp ||
		psPacket->eEffectID == EFFECTID_HolyIncAntation ||
		psPacket->eEffectID == EFFECTID_Resurrection ||
		psPacket->eEffectID == EFFECTID_Forceorb ||
		psPacket->eEffectID == EFFECTID_Valento ||
		psPacket->eEffectID == EFFECTID_FireFlower)
	{
		return psPacket->eEffectID;
	}

	return EFFECTID_None;
}
