#include "StdAfx.h"
#include "..\\resource.h"

#include "..\\character.h"
#include "..\\fileread.h"
#include "..\\playmain.h"
#include "..\\effectsnd.h"

#include "..\\record.h"
#include "..\playsub.h"

#include "gamesql.h"
#include "DllServer.h"

#include "..\\sinbaram\\sinitem.h"

#include "ClientFuncPos.h"

#include "OnServer.h"
#include "svr_Damage.h"
#include "openlive.h"

#include "svrEventSpawn.h"

#include "svrEventGame.h"

#define	DEFENSE_RATE	80

#include "ServerMsg.h"

char	*finehack_message = "http://info.pristontale.com/blackWarning/warning.asp?id=%s&name=%s";


int LogOnThread_Count;
int	LogOnThread_Process;
int LogOnThread_ProcessTime;
int LogOnThread_Sucess;

char	szLastLogInID[64];
int		LastLogInResult = 0;

int rsRefreshConfig();
int InitMonster();

HFONT	hServerFont = 0;

int		Svr_DisplayMode = 0;

#define	srCRISTAL_MAX		20
#define MARVELCRISTAL_MAX	8
#define srKIDMONSTER_MAX	1
#define srSOD_GUARD_MONSTER_MAX	5

struct srCRISTAL_MONSTER
{
	char *szName;
	CharacterData	*lpCharInfo;
	int	RndCount;
};

static int rsSOD_CRYSTAL_GUARD_MONSTER_POS[7][3] =
{
	{33,		34560,		-25785}, // ¼º¹® ÀÔ±¸ ¹æ¾î
	{33,		34200,		-26080}, // ¼º¹® ±ÙÃ³ ¿ì  
	{33,		34900,		-26080}, // ¼º¹® ±ÙÃ³ ÁÂ
	{33,		33745,		-28575}, // Ä³½½ Áß°£ ¿ì
	{33,		35345,		-28575}, // Ä³½½ Áß°£ ÁÂs
	{33,		34135,		-30575}, // ¹ßÇÒ¶ó ¿ì
	{33,		34975,		-30575}  // ¹ßÇÒ¶ó ÁÂ
};

struct srOPENKID_MONSTER
{
	char *szParentMonName;
	char *szChildMonName;
	int	mon_Num;
	int mon_Count;
};
srOPENKID_MONSTER srOpenKidMonster[srKIDMONSTER_MAX] =
{
	{"¾«ÁéÊóÐ¡µÜ",		"¾«ÁéÊóÐ¡µÜ",			0,		3}
};

srOPENKID_MONSTER srOpenSODCrystalGuardMonster[srSOD_GUARD_MONSTER_MAX] =
{
	{"»ðË®¾§Ëþ" ,		"ÎÀ±ø",		100,		10},
	{"±ùË®¾§Ëþ",		"¾¯ÎÀ±ø",	100,		10},
	{"À×Ë®¾§Ëþ",		"½ûÎÀ±ø",	100,		10},
	{"Íß¶û¹þÀ­Ö®Ëþ",	"¾¯ÎÀ±ø",	100,		10},
	{"³ÇÃÅ",			"ÎÀ±ø",		101,		6}
};

#define	srCRISTAL_RANDOM		8
#define	srCRISTAL_CLAN			9
#define srCLAN_MONSTER_MAX		3
#define	srCRISTAL_CASTLE_START	13
#define	srCRISTAL_CASTLE_END	16

#define	srCRISTAL_SKELETON		16	
#define	srCRISTAL_KAOS			17	
#define	srCRISTAL_IMPERNA		18	
#define srCRISTAL_EXTREME		19
#define	srCRISTAL_MARVEL_RANDOM	20
#define	srCRISTAL_G_DIVINE_CLAN	21

#define rsCRISTAL_ICEGOBLIN		22 //±ù¼×¸ç²¼ÁÖ
#define rsCRISTAL_FROZEN		23 //±ùÑý
#define rsCRISTAL_BLIZZARDGIANT	24 //±ù¼×ÎÞË«
#define rsCRISTAL_MIMIC			41 //Ïä×Ó¹ÖÎï
#define rsCRISTAL_HELLHOUND		42 //µØÓüÁÔÈ®
#define rsCRISTAL_MONKINGSPIDER	43 //ºìÁëÖëÍõ
#define rsCRISTAL_HOBOGOLEM		44 //ÎÞÏ¢Ä§Íõ
#define rsCRISTAL_GORGON		45 //Ã×ÅµÌÕË¹
#define rsCRISTAL_IGOLATION		46 //ËÀÉñ
#define rsCRISTAL_XETAN			47 //ë¯Ì·
#define rsCRISTAL_LENA			48 //ÀÙÄÈ
#define rsCRISTAL_ICESERPENT	49 //º£Áú
#define rsCRISTAL_IBOMBER		50 //±¬ÆÆÇÖÂÔÕß
#define rsCRISTAL_NIHIL			51 //Ï£¶û
#define rsCRISTAL_ARHDYRA		52 //¾ÞÊ¯Ä§ÈË
#define rsCRISTAL_BIGMAMA		53 //Ë®ÓòÊØ»¤Õß

#define srADVCRISTAL_MAX		16
#define	srSKILL_MONSTER_MAX		5


#define	srBC_MONSTER_MAX		4
#define	srBC_MONSTER_TOTAL		16

int	srHammerMonsterCount = 0;


#define MYWM_NOTIFYICON		(WM_USER+140)
#define MYWM_USER_COUNT		(WM_USER+110)
#define ID_MESSTEXT		101

int InitAll();

void RemoveAll();


static CRITICAL_SECTION	cOdbcSection;

char	szServer_DebugString[256];
DWORD	dwServer_DebugMessage;
char	szServer_DebugLastUserID[32];
char	szServer_DebugLastUserName[32];
int		Server_DebugCount;

int		rsNSpriteMode = 0;

int		rsOpenNPC_RandomPos = 0;

HWND	hDebugWnd = 0;
#define	SWM_DISPDEBUG	(WM_USER+77)

int	Server_SqlReady = 0;
int	ServerNameCode = 0;

static HINSTANCE hInst;
extern HWND hwnd;
static HWND hMsgTextWnd;
static HDC	hdc;
static int Quit = 0;
static char *szAppName = "PT Online";

static int WinWidth = 320;
static int WinHeight = 240;

static int WSA_RecvMsgCount = 0;

static	int	ShutDownFlag = 0;
static	int	ShutDownLeftTime = 0;

char szMessageBuff[256];
DWORD ListBuff[8192 / 4];
int PlayerCount;


rsSERVER_NOTICE	rsNoticeMessage;


#define DIST_AROUND_NEAR	(256*256)
#define DIST_AROUND_MIDDLE	(16*64 * 16*64)

#define TRANS_IPMAX			(1000/sizeof(TRANS_IPLIST))

#define AREA_USERMAX		256
#define AREA_MAX			256

#define AUTOPLAYER_MAX		2048
#define AUTOPLAYER_MASK		2047

int rsConnectUserLimit = 800;

#define	TRANS_MAX_CHAR_LIMIT	28
#define	TRANS_MAX_USER_LIMIT	18


#define	OVER_TRANS_TIME		1500

DWORD		dwOffsetTime = 0;

#define	CHR_MONSTER_MAX		400
#define	DEF_ITEM_MAX		2000

#define	REOPEN_COUNT_NUM	256


#define TRANS_VIEW_LIMIT		(64*64)


#define OPEN_START_MONSTER_MAX		3


#define	STG_ITEM_WAIT_TIME		(1000*60*3)
#define	STG_ITEM_WAIT_TIME_LOW	(1000*90)


#define ITEM_SET_DIST	24

POINT	ptItemSettingPosi[8] = {
	{  0			 , -ITEM_SET_DIST },
	{  ITEM_SET_DIST , -ITEM_SET_DIST },
	{  ITEM_SET_DIST ,  0			  },
	{  ITEM_SET_DIST ,  ITEM_SET_DIST },
	{  0             ,  ITEM_SET_DIST },
	{ -ITEM_SET_DIST ,  ITEM_SET_DIST },
	{ -ITEM_SET_DIST ,  0             },
	{ -ITEM_SET_DIST , -ITEM_SET_DIST }
};

int	LoginServer = 0;

int	EventMonster = 0;

#define	LIMIT_PK_LEVEL	20

int	rsHardCoreEvent = 0;
int	rsDamgeOffEvent = 0;

int	rsCristalEvent = 0;

DWORD	dwWeatherPlayTime = 0;
DWORD	dwRainTime = 0;


char *MonsterPath = "GameServer\\monster\\";
char *ItemPath = "GameServer\\OpenItem\\";
char *szNpcInfoPath = "GameServer\\npc\\";
char *szFieldInfoPath = "GameServer\\Field\\";
char *HackLogDirectory = "LogFile";
char *LogDirectory = "LogFile";
char *DebugLogDirectory = "LogDebug";
char *AdminLogDirectory = "LogAdmin";

char *EventLogDirectory = "EventLog";

static char *szDebugServer = "penguin-pc";

static char TransTemp[1024];
static char	szChkID[32];

DWORD	dwConnectCount = 0;
DWORD	rsAutoPlayTransCount = 0;

rsCURRENCY_LOG	CurrencyLog;

int			srAcceptErrorCount = 0;
int			srLastAcceptRsult = 0;
int			srRouteErrorCount = 0;
int			srLogFailedCount = 0;


static int			spJobCode = 0;
static int			spItemNormal = 0;
static DWORD		spJobCodeTime = 0;

static int			spTimeAdjust = 0;
static DWORD		spTimeAdjustTime = 0;


char	*szLogItemDataDirectory = "LogItemData";

rsUSER_LIST_TOP10	rsUserListDamageTop10;

#define	rsBLESSCASTLE_TAX_TIME			2

int SaveThrowItem(User *lpPlayInfo, DWORD dwCode, DWORD dwKey, DWORD dwSum);
int RecordHackLogFile(User *lpPlayInfo, void *lpTransCommand);
int RecordDebugPlayLogFile(User *lpPlayInfo);
int RecordMixItem(User *lpPlayInfo, Item *lpSrcItem, Item *lpMixItem);
int RecordAgingItem(User *lpPlayInfo, Item *lpSrcItem, Item *lpMixItem, int Mode);
int RecordCollectMoney(User *lpPlayInfo, int Money);
int RecordGetHighItem(User *lpPlayInfo, struct MapLoot *lpStgItem);
int	rsShutDown();
int RecordSmeltingItem(User *lpPlayInfo, Item *lpSmeltingItem);
int RecordManufactureItem(User *lpPlayInfo, Item *lpManufactureItem);
int RecordMixtureResetItem(User *lpPlayInfo, Item *lpMixtureResetItem);
// ¼ÇÂ¼Element
int RecordElementItem(User *lpPlayInfo, Item *lpElementItem);
int RecordMovieBloodyBattleItem(User *lpPlayInfo, Item *lpMovieBloodyBattleItem);

int CreatePresentItem(DWORD dwItemCode, Map *lpStgArea, int x, int y, int z, int count);
// ·¢ËÍÓÎÏ··þÎñÆ÷¶À½ÇÊÞÒ»¼Ò
int rsSendGameServer_CaravanHopy(User *lpPlayInfo);
// ÉèÖÃ¶À½ÇÊÞÒ»¼Ò
int rsSetCaravanHopy(User *lpPlayInfo, DWORD Time, int Kind);
// ·¢ËÍÓÎÏ··þÎñÆ÷·ï»Ë
int rsSendGameServer_Phoenix(User *lpPlayInfo);
// ·¢ËÍÓÎÏ··þÎñÆ÷´óÒ©Ò©Ë®
int rsSendGameServer_BigHead(User *lpPlayInfo);
// ·¢ËÍÓÎÏ··þÎñÆ÷¹ûÊµ
int rsSendGameServer_FruitStatus(User *lpPlayInfo, int Kind);

// ·¢ËÍÁ¦Á¿Ê¯Í·
int rsSendServerToForceOrb(User *lpPlayInfo);
int rsCharChanger(Unit *lpChar, CharacterData *lpCharInfo, UnitInfo *lpMonInfo);
int	rsInitHardCoreEvent();
int SendOpenCollectMoney(User *lpPlayInfo, int sEvent, int sEventCount);
int rsCheckHardCoreEventArea(int x, int y, int z);
int	rsTransUpdateSod(User *lpPlayInfo);

extern TRANS_SERVER_LIST	TransServerList;
extern rsSERVER_CONFIG		rsServerConfig;

int rsSendAreaServer(User *pcUser, void *szData);
int rsAddBackListID(char *szID, DWORD dwTime);
DWORD rsCheckBackListID(char *szID);
int rsResetBackList();
int rsFreekBackListID(char *szID);
int rsShowBlackList(User *pcUser, char *szID);
int RecordJobChanger(User *lpPlayInfo);
int	rsCheckBlockUserFile(char *szID);
int rsAddBlockUserFile(char *szID, char *szLog);
int	rsCheckEnableIP(DWORD dwUserIP);
int	rsCheckDisableIP(DWORD dwUserIP);
DWORD GetSwapIPCode(char *szIP);
int	rsCheckAdminIP(DWORD dwUserIP);
int	rsCheckSystemIP(DWORD dwUserIP);
int	rsCheckLoginServerIP(DWORD dwUserIP);
int	rsCheck_ItemSecCode(User *lpPlayInfo, DWORD dwCode, DWORD dwHead, DWORD dwChkSum, int Money, DWORD dwSeCode_0, DWORD dwSeCode_1, DWORD dwSeCode_2, DWORD dwSeCode_3, int *pPotionCount);
int	rsRegist_ItemSecCode(User *lpPlayInfo, TRANS_ITEMINFO *lpTransItemInfo, int NewItem);
int	rsRegist_ItemSecCode(User *lpPlayInfo, smTRANS_COMMAND_EX *lpTransCommandEx);
// ·¢ËÍVIPµ½ÓÎÏ··þÎñÆ÷
int rsSendVipInfoToGameServer(User *lpPlayInfo);
//¹Ø±ÕVIPÐÅÏ¢µ½¿Í»§¶Ë
int rsCloseVipInfoToClient(User *lpPlayInfo);
// È¡ÏûË®¾§Ð­Òé
int rsCancelCrystalToClient(User *lpPlayInfo, Unit *lpChar);
int Record_TempLogFile(char *szMessage);
int Record_BillingLogFile(User *lpPlayInfo, DWORD wParam, DWORD lParam, DWORD sParam, DWORD eParam);
int Record_DeadUser(User *lpPlayInfo, smTRANS_COMMAND *lpTransCommand);
int RecordShutdownLog(int LogCode, int LParam, int SParam);
int rsLoadCopiedItemList();
int rsRemoveCopiedItemList();
int rsCheckCopiedItem(Item *lpItem);
int rsCheckCopiedItem(DWORD dwCode, DWORD dwHead, DWORD dwChkSum);
int rsSend_ResultSOD(User *lpPlayInfo, int Point, int KillCount, int TotalPoint, int TotalSucessUser, int TotalUser, int ClassCode);
int	rsRecvSkillPartyUser(TRANS_PARTY_SKILL *lpTransPartySkill);
int rsRecvProcessSkill(User *lpPlayInfo, smTRANS_COMMAND *lpTransCommand);
int rsCancelSkill(User *lpPlayInfo, smTRANS_COMMAND *lpTransCommand);
int rsUpdateSkill(User *lpPlayInfo, smTRANS_COMMAND *lpTransCommand);
int rsClanUpdate(User *lpPlayInfo, TRANS_CLAN_COMMAND_USER *lpTransClanUser);
int rsRecvYahooMotion(User *lpPlayInfo, smTRANS_COMMAND *lpTransCommand);
User *FindUserFromName(char *szName);
int	rsPushKillMonster(Unit *lpChar, User *lpPlayInfo, Map *lpStgArea);
int	rsSaveAdminCommand(User *lpPlayInfo, char *szChatCommand, int Level);
int	rsRecordAdminCommand(User *lpPlayInfo, char *szChatCommand, int Level);
int	rsCheckAdminPlayer(User *lpPlayInfo);
int rsRecvStarPoint(User *lpPlayInfo, smTRANS_COMMAND *lpTransCommand);
int rsRecvSodClanCash(User *lpPlayInfo, smTRANS_COMMAND *lpTransCommand);
int rsRecvGiveMoney(User *lpPlayInfo, smTRANS_COMMAND *lpTransCommand);
int rsRecvPaymentMoney(User *lpPlayInfo, smTRANS_COMMAND *lpTransCommand);
DWORD rsOpenEventPuzzleItem(User *lpPlayInfo, Unit *lpChar);
int	rsTrade_PersonalShop(User *lpPlayInfo, User *lpPlayInfo2, smTRANS_COMMAND_BUFF *lpTransCommandBuff);
int	rsUseLovelyItem(User *lpPlayInfo, DWORD	dwItemCode);
int	rsMorifEventMessage(Unit *lpChar);
int	rsMollyWolfEventMessage(Unit *lpChar);
int	rsQuestMasterMessage(Unit *lpChar, User *lpPlayInfo);
int	rsSantaGoblinEventMessage(Unit *lpChar);
int	rsChichenDayEventMessage(Unit *lpChar);
int rsGetQuestCommand(User *lpPlayInfo, smTRANS_COMMAND *lpTransCommand);
int	rsSetNoticeMessage(char *szMessage);
int	rsOpenSiegeCastleItem(DWORD dwItemCode, int x, int y, int z, User *lpPlayInfo);
int rsStartUser_PresentItem(User *lpPlayInfo);
int rsRecvUpdateServerParam(User *lpPlayInfo, smTRANS_COMMAND *lpTransCommand);
int rsSendUserID_MainServer(User *lpPlayInfo);
int rsRecvUserID_MainServer(User *lpPlayInfo, smTRANS_CHAR_COMMAND2 *lpTransCharCommand);
int rsRecvHackTrap(User *lpPlayInfo, smTRANS_COMMAND *lpTransCharCommand);

#ifdef _CHECK_MESH
int rsRecvCheckItemMesh(User *lpPlayInfo, smTRANS_COMMAND *lpTransCommand);
#endif
int rsPutItem_TreasureBox(User *lpPlayInfo, DWORD Code);
int rsPutItem_CapsuleItem(User *lpPlayInfo, DWORD Code);
int rsRecvEventGame(User *lpPlayInfo, smTRANS_COMMAND *lpTransCommand);
int Event_UserInfo_Init(User *lpPlayInfo, WORD sTime);


#define	ITEMLOG_GET				0
#define	ITEMLOG_PUT				6
#define	ITEMLOG_MIXING			3
#define	ITEMLOG_MIXLOST			9
#define	ITEMLOG_AGING			4
#define	ITEMLOG_AGINGLOST		10
#define	ITEMLOG_AGINGUP			12
#define	ITEMLOG_BUYSHOP			5
#define	ITEMLOG_SELLSHOP		7
#define	ITEMLOG_TRADE			8
#define	ITEMLOG_USED			11
#define	ITEMLOG_EXPRESS			13
#define	ITEMLOG_GETWING			14
#define	ITEMLOG_WINGLOST		15
#define	ITEMLOG_BUYSTAR			16

#define	ITEMLOG_AGING_2UP		17
#define	ITEMLOG_AGING_2DOWN		18
#define	ITEMLOG_AGING_1DOWN		19
#define	ITEMLOG_AGING_KEEP		20

#define	ITEMLOG_PRESENT			21
#define	ITEMLOG_MYSHOP			22

#define	ITEMLOG_USE_ALCHMY		24
#define	ITEMLOG_LOST_ALCHMY		25
#define	ITEMLOG_GET_ALCHMY		26

#define	ITEMLOG_GET_RECON		27
#define	ITEMLOG_LOST_RECON		28
#define ITEMLOG_SMELTING_LOST	29
#define ITEMLOG_SMELTING_GET	30
#define ITEMLOG_MANUFACTURE_LOST 31	
#define ITEMLOG_MANUFACTURE_GET 32
#define ITEMLOG_MANUFACTURE_FAIL 33
#define ITEMLOG_MIXTURE_RESET_LOST	34
#define ITEMLOG_MIXTURE_RESET_FAIL	35
#define ITEMLOG_MIXTURE_RESET_GET	36
#define ITEMLOG_AGING_10UP		37
#define ITEMLOG_AGING_15UP		38
#define ITEMLOG_AGING_20UP		39

int	rsRecord_ItemLog(User *lpPlayInfo, DWORD dwItemCode, DWORD	dwHead, DWORD dwChkSum, int Flag);
int	rsRecord_ItemLog2(User *lpPlayInfo, DWORD dwItemCode, DWORD	dwHead, DWORD dwChkSum, int Flag);
int	rsRecord_ItemLog_Change(User *lpPlayInfo, DWORD dwItemCode, DWORD	dwHead, DWORD dwChkSum, DWORD dwItemCode2, DWORD	dwHead2, DWORD dwChkSum2, int Flag);
int	rsRecord_ItemLost(User *lpPlayInfo, DWORD *lpItemCode, DWORD *lpHead, DWORD *lpChkSum, int Flag);
int	rsRecord_ItemLog_Trade(User *lpPlayInfo, User *lpPlayInfo2, TRANS_TRADE_ITEMKEY *lpTransTradeItemKey);
int	rsRecord_ItemLog_Post(User *lpPlayInfo, DWORD dwItemCode, DWORD	dwHead, DWORD dwChkSum, DWORD dwGCode, char *szTelNum, int Flag);
int rsRecord_SmeltingItemLog(User *lpPlayInfo, DWORD *lpItemCode, DWORD *lpHead, DWORD *lpChkSum, int Flag);
int rsRecord_ManufactureItemLog(User *lpPlayInfo, DWORD *lpItemCode, DWORD *lpHead, DWORD *lpChkSum, int Flag);
int rsRecord_MixtureResetItemLog(User *lpPlayInfo, sMIXTURE_RESET_ITEM_SERVER *pMixtureResetItem_Server, int Flag);
int rsSendAreaOpenKidMonster(User	*lpPlayInfo, Unit *lpChar);
int rsOpenKidMonster(User *lpPlayInfo, smTRANS_COMMAND *lpTransCommand, int mon_Num);
int rsSendAreaOpenSODGuardMonster(User *lpPlayInfo, Unit *lpChar);
int rsOpenSODGuardMonster(User *lpPlayInfo, smTRANS_COMMAND *lpTransCommand, int mon_Num);


struct	smTRANS_SYSTEM_COMMAND
{
	int		size, code;

	int		tCode;
	DWORD	dwObjectSerial;
	DWORD	dwNameCode;
	int		x, y, z;

	DWORD	Param[32];
};

#define	smTRANS_SYSCODE_CONNECT			0x1000
#define	smTRANS_SYSCODE_KILL_MONSTER	0x1100
#define	smTRANS_SYSCODE_GET_MONEY		0x1110
#define	smTRANS_SYSCODE_GET_ITEM		0x1112
#define	smTRANS_SYSCODE_DMG_USER_LIST	0x1120
#define	smTRANS_SYSCODE_NETSTATE		0x1200
#define	smTRANS_SYSCODE_NETSUCCESS		0x1250

#define	smTRANS_SYSCODE_CONNECT_USER	0x1300
#define	smTRANS_SYSCODE_USER_FAILED		0x1302
#define	smTRANS_SYSCODE_EXP_INFO		0x1310


#define	SER_TO_SERVER_SOCKET_MAX	4
#define	SER_TO_SERVER_SOCKET_MASK	3

DWORD		dwSerToSerIP = 0;
DWORD		dwSerToSer_Count = 0;
char		szSerToSerIP[32];

#define	SER_TO_LOGIN_SOCKET_MAX	16
User	*lpPlayInfo_LoginServer[SER_TO_LOGIN_SOCKET_MAX] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
DWORD		dwSerToLogin_Count = 0;
DWORD		dwSerToLogin_Num = 0;


rsKILL_MONSTER_INFO	rsKillMonster_Que[srMONSTER_KILL_QUE_MAX + 10];
int	rsKillMonster_Push = 0;
int	rsKillMonster_Pop = 0;

HANDLE	hSerToServer_Thread = 0;
DWORD	dwSerToServer_ID = 0;

int	rsSystemNetCount = 0;
int	rsSystemLineConnCount = 0;
int rsSystemLineFailedCount = 0;
int rsSystemLinePlayCount = 0;

int	rsMonHuntCount = 0;
int	rsMonOpenCount = 0;
int	rsItemOpenCount = 0;
int	rsMoneyTotalCount = 0;
int	rsItemBuffOverCount = 0;

extern int	Server_LimitVersion;

int InitAdminCommand();

int rsRefreshConfig()
{

#ifdef _W_SERVER

	SERVER_MUTEX->Lock(3000);

	smConfigDecode("hotuk.ini");
	InitAdminCommand();

	if (rsServerConfig.LimitVersion)
		Server_LimitVersion = rsServerConfig.LimitVersion;

	if (rsServerConfig.Permit_Exp)
		Permit_CheckExp = rsServerConfig.Permit_Exp;
	else
		Permit_CheckExp = TOTAL_CHECK_EXP_MAX;

	if (rsServerConfig.Permit_Money)
		Permit_CheckMoney = rsServerConfig.Permit_Money;
	else
		Permit_CheckMoney = TOTAL_CHECK_MONEY_MAX;

	rsResetBackList();

	rsResetClientFuncPos();

	SERVER_MUTEX->UnLock();

#endif

	return TRUE;
}

//ÓÎÏ·ÍË³ö
int rsLogOut(User *lpPlayInfo)
{
	int BlockTime;
	int Money;

	if (lpPlayInfo && lpPlayInfo->szAccountName[0] && lpPlayInfo->pcSocketData)
	{
		if (lpPlayInfo->szCharacterName[0])
		{
			Money = lpPlayInfo->GetGold() - lpPlayInfo->WareHouseMoney;

			RecordLogSql(LOG_SQL_LOGOUT, lpPlayInfo->pcSocketData->szIP, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->szGPCode, 1, lpPlayInfo->sCharacterData.iClass,
				lpPlayInfo->sCharacterData.iExp, lpPlayInfo->sCharacterData.iLevel, Money);
		}

		if (rsServerConfig.PresentLevel > 0 && lpPlayInfo->spLevel_Start > 0 && rsServerConfig.PresentLevel > lpPlayInfo->CharLevelMax)
		{
			lpPlayInfo->sCharacterData.iLevel = GetLevelFromExp(lpPlayInfo->sCharacterData.iExp);

			if (lpPlayInfo->spLevel_Start < rsServerConfig.PresentLevel && lpPlayInfo->sCharacterData.iLevel >= rsServerConfig.PresentLevel)
			{
				rsAddPostBox_Present(lpPlayInfo);
				rsRecord_ItemLog_Post(lpPlayInfo, 99, 0, 0, lpPlayInfo->sCharacterData.iLevel, 0, ITEMLOG_PRESENT);
			}
		}


		if (lpPlayInfo->BlockTime == 0x7FFFFFFF)
			BlockTime = 60 * 24 * 30 * 3;
		else
			BlockTime = lpPlayInfo->BlockTime / (60 * 1000);

		RecordGameLogSql(GAMELOG_SQL_LOGOUT, lpPlayInfo->pcSocketData->szIP, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->szGPCode, lpPlayInfo->sCharacterData.iClass, lpPlayInfo->szGuid, BlockTime);

		if (lpPlayInfo->szGPCode[0])
			bSql_Logout(lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpPlayInfo->szGPCode, lpPlayInfo->DisuseDay, lpPlayInfo->UsePeriod, lpPlayInfo->szGuid, lpPlayInfo->Bl_RNo);

		if (lpPlayInfo->iTicket && lpPlayInfo->szCharacterName[0])
			bClan_UserTicket(lpPlayInfo, 1);
	}

	return TRUE;
}
DWORD hRecord_Item_Thread = NULL;
DWORD hRecord_Monster_Thread = NULL;

DWORD ReadItem_Thread(void *pInfo)
{
	hRecord_Item_Thread = TRUE;
	hRecord_Item_Thread = FALSE;
	ExitThread(0);
	return TRUE;
}
DWORD ReadMonster_Thread(void *pInfo)
{
	hRecord_Monster_Thread = TRUE;
	InitMonster();
	hRecord_Monster_Thread = FALSE;
	ExitThread(0);
	return TRUE;
}
void ReconfigReadItem()
{
	DWORD dwThreadID;

	if (hRecord_Item_Thread == FALSE)
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ReadItem_Thread, 0, 0, &dwThreadID);
}
void ReconfigReadMonster()
{
	DWORD dwThreadID;

	if (hRecord_Monster_Thread == FALSE)
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ReadMonster_Thread, 0, 0, &dwThreadID);
}
int InitMonster()
{
	/*HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;
	char	szFindPath[64];
	char	szFilePath[64];

	chrMonsterCnt = 0;

	ZeroMemory(chrMonsterList, sizeof(CharacterData)*CHR_MONSTER_MAX);
	ZeroMemory(chrMonInfoList, sizeof(UnitInfo)*CHR_MONSTER_MAX);

	lstrcpy(szFindPath, MonsterPath);
	lstrcat(szFindPath, "*.inf");

	hFindHandle = FindFirstFile(szFindPath, &fd);
	if (hFindHandle != INVALID_HANDLE_VALUE)
	{
		while (1)
		{
			lstrcpy(szFilePath, MonsterPath);
			lstrcat(szFilePath, fd.cFileName);

			smCharDecode(szFilePath, &chrMonsterList[chrMonsterCnt], &chrMonInfoList[chrMonsterCnt], 0);

			chrMonInfoList[chrMonsterCnt].dwHashCharacterName = GetCodebyName(chrMonsterList[chrMonsterCnt].szName);

			ReformCharForm(&chrMonsterList[chrMonsterCnt]);

			chrMonsterCnt++;

			if (FindNextFile(hFindHandle, &fd) == FALSE)
				break;
			if (chrMonsterCnt >= CHR_MONSTER_MAX)
				break;
		}
	}
	FindClose(hFindHandle);*/

	return TRUE;
}
int ConvertMonsterNames()
{
	/*int cnt;

	for (cnt = 0; cnt < chrMonsterCnt; cnt++)
	{
		if (chrMonInfoList[cnt].szName[0] && chrMonsterList[cnt].szName[0])
		{
			lstrcpy(chrMonsterList[cnt].szName, chrMonInfoList[cnt].szName);
			chrMonInfoList[cnt].szName[0] = 0;
		}
	}*/

	return TRUE;
}


char *szUserModelPath = "char\\tmABCD";

int rsCheckActiveFile(char *szFile)
{
	WIN32_FIND_DATA	fd;
	HANDLE	hFindHandle;

	hFindHandle = FindFirstFile(szFile, &fd);
	if (hFindHandle == INVALID_HANDLE_VALUE)
		return FALSE;
	FindClose(hFindHandle);

	int cnt, len;
	char szFileName[128];

	len = lstrlen(szFile);
	memcpy(szFileName, szFile, len + 1);

	for (cnt = len - 1; cnt >= 0; cnt--)
	{
		if (szFileName[cnt] == '\\')
		{
			szFileName[cnt] = 0;
			break;
		}
	}

	if (lstrcmpi(szFileName, szUserModelPath) != 0)
		return FALSE;

	return TRUE;
}
char *SetFieldInfoPath(char *SaveBuff, char *szFieldPath, char *InfoExt)
{
	int cnt;
	int len;
	char *szFile;

	len = lstrlen(szFieldPath);
	cnt = len - 1;

	szFile = szFieldPath;

	while (cnt > 0)
	{
		if (szFieldPath[cnt] == '\\')
		{
			szFile = &szFieldPath[cnt + 1];
			break;
		}
		cnt--;
	}

	wsprintf(SaveBuff, "%s%s.%s", szFieldInfoPath, szFile, InfoExt);

	return SaveBuff;
}
int rsGetUserCounter(int Counter)
{
	return Counter;
}

#define START_POINT_MAX			8
#define START_POINT_MASK		(START_POINT_MAX-1)

POINT	StartPointNpc[START_POINT_MAX] =
{
	{ 1692 , -584 },
	{ 34 , -618 },
	{ -741 , 877 },
	{ 1000 , 1000 }
};

POINT	StartPoint[START_POINT_MAX] =
{
	{	-1500,	-2800 },
	{	600,	-3200 },
	{	840,	-4000 },
	{	-90,	-5000 },
	{	-900,	-6500 },
	{	-1600,	-7100 },
	{	-3000,	-7200 },
	{	400,	-6100 }
};

int StartPointCnt = 0;


int	rsLoadCreateItemToHDD(LootItem	*lpItem, char *szFileCode);
int	rsSaveCreateItemToHDD(LootItem	*lpItem);
int	rsSaveAgingItemToHDD(Item *lpItem);

//ÀÌÀü¿¡ »ý¼ºµÈ ¾ÆÀÌÅÛ ÄÚµå¸¦ Ã£¾Æ ¼³Á¤
int srSetItemFromLogData(LootItem *lpsItem, char *LogFileCode)
{
	//¹ß»ýÇÑ ¾ÆÀÌÅÛ ±â·ÏÁ¤º¸¸¦ Ã£¾Æ¼­ ¼³Á¤
	return rsLoadCreateItemToHDD(lpsItem, LogFileCode);
}

#define	OS_TRAN	(sinOS1|sin06)
#define	OS_MUKY	(sinOS1|sin07)
#define	OS_DEBI	(sinOS1|sin08)
#define	OS_ALL	(sinOS1|sin12)

//¸ð¸®ÇÁ Á¦ÇÑ ÇÊµå ¾ÆÀÌÅÛ
DWORD	dwMorifFieldItem[] = {
	//0		1		2		3
	OS_TRAN,	OS_TRAN,	OS_TRAN,	OS_TRAN,
	//4		5		6		7
	OS_TRAN,	OS_TRAN,	OS_TRAN,	OS_TRAN,
	//8		9		10		11
	OS_TRAN,	OS_MUKY,	OS_MUKY,	OS_MUKY,
	//12		13		14		15
	OS_DEBI ,	OS_MUKY,	OS_MUKY,	OS_DEBI ,
	//16		17		18		19
	OS_TRAN,	OS_TRAN,	OS_TRAN,	OS_TRAN,
	//20		21		22		23
	OS_TRAN,	OS_TRAN,	OS_ALL , 	OS_ALL ,
	//24		25		26		27
	OS_DEBI,	OS_DEBI,	OS_ALL ,	OS_ALL ,
	//28		29		30		31
	OS_ALL,		OS_TRAN,	OS_TRAN,	OS_ALL,
	//32		33		34		35
	OS_TRAN,	OS_TRAN,	OS_TRAN,	OS_TRAN
};

//¸ð¸®ÇÁ ¾ÆÀÌÅÛ ÇÊµå
int	srCheckMorifItemField(DWORD dwItemCode, Map *lpStgArea)
{

	DWORD	dwItemCodeMask = dwItemCode & sinITEM_MASK3;

	if (!lpStgArea || !lpStgArea->pcBaseMap) return FALSE;

	DWORD	dwAreaCode = lpStgArea->pcBaseMap->iMapID;

	if (dwAreaCode >= 0 && dwAreaCode < 36) {

		if (dwMorifFieldItem[dwAreaCode] == OS_ALL && dwItemCodeMask < sin05)	//ÀüÃ¼µå·Ó ÇÊµåÀÇ °æ¿ì os105 ÀÌ»ó¸¸ ³ª¿À°Ô ÇØ´Þ¶ó°í ÇÔ
			return FALSE;

		if (dwItemCodeMask > (dwMorifFieldItem[dwAreaCode] & sinITEM_MASK3))
			return FALSE;
	}

	return TRUE;
}



//¸ó½ºÅÍ¿¡¼­ ³ª¿À´Â ¾ÆÀÌÅÛ ¼³Á¤
int srGetMonsterItem(User *lpPlayInfo, Unit *lpChar, LootItem *lpsItem)
{
	int	rnd;
	int cnt;
	int rcnt;
	DWORD dwCode;
	UnitInfo *lpMonInfo = &lpChar->sUnitInfo;
	Map *lpStgArea;

	ZeroMemory(lpsItem, sizeof(Item));

	if (lpMonInfo->iDropPercentNum == 0 || lpMonInfo->iDropCount == 0) return FALSE;

	rsSendAreaOpenKidMonster(lpPlayInfo, lpChar);

	if (lpPlayInfo->iMapID == MAPID_GhostCastle)
		rsSendAreaOpenSODGuardMonster(lpPlayInfo, lpChar);

	rnd = (rand() << 7) | ((GetCurrentTime() >> 2) & 0x7F);
	rnd = rnd % lpMonInfo->iDropPercentNum;

	if (!rsServerConfig.AreaServer.IP_Count)
	{
		if (!lpMonInfo->saDropData[0].iItemID && (rand() % 1000) < 10)
			return FALSE;
	}

	rcnt = 0;
	for (cnt = 0; cnt < lpMonInfo->iDropCount; cnt++)
	{
		if (rnd >= rcnt && rnd < (rcnt + lpMonInfo->saDropData[cnt].iPercent))
		{
			if (!lpMonInfo->saDropData[cnt].iItemID)
				return FALSE;

			if (lpMonInfo->saDropData[cnt].iItemID == (sinGG1 | sin01))
			{
				rnd = GetRandomPos(lpMonInfo->saDropData[cnt].sGold.sMin, lpMonInfo->saDropData[cnt].sGold.sMax);
				lpsItem->sItem.sItemID = sinGG1 | sin01;
				wsprintf(lpsItem->sItem.szItemName, "%dGold", rnd);
				lpsItem->sItem.iGold = rnd;
				ReformItem(&lpsItem->sItem);
				rsMoneyTotalCount += rnd;
				return TRUE;
			}

			dwCode = lpMonInfo->saDropData[cnt].iItemID;

			auto pDefItem = SERVERITEM->FindItemDefByCode(dwCode);

			if (pDefItem)
			{
				if (lpChar->sCharacterData.iMonsterEffectID == snCHAR_SOUND_NPC_MOLLYWOLF &&
					(dwCode&sinITEM_MASK2) == sinFO1)
				{
					lpStgArea = lpChar->pcMap;
					if (lpStgArea->pcBaseMap && lpStgArea->pcBaseMap->iMapType == MAPTYPE_Forest)
						return FALSE;
				}

				SERVERITEM->CreateItem(&lpsItem->sItem, pDefItem);

				rsSaveCreateItemToHDD(lpsItem);
				rsItemOpenCount++;
				return TRUE;
			}

			return FALSE;
		}
		rcnt += lpMonInfo->saDropData[cnt].iPercent;
	}

	return FALSE;
}
DWORD rsGetItemClass(DWORD Code)
{
	ItemData * pItemData = SERVERITEM->GetItemDataByID(Code);

	return pItemData ? pItemData->iItemSlotFlag : 0;
}

int OpenEventMonster(CharacterData *lpCharInfo, Map *lpStgArea)
{
	int cnt;
	int MonCnt;

	if (lpCharInfo != NULL && lpStgArea != NULL)
	{
		if (lpCharInfo->iMonsterEffectID == snCHAR_SOUND_HOPT)
		{
			if ((rand() % 100) > 30)
				return FALSE;

			MonCnt = 0;
			for (cnt = 0; cnt < MAX_ALIVEMONSTERS; cnt++)
			{
				if (lpStgArea->pcaUnitData[cnt])
				{
					if (lpStgArea->pcaUnitData[cnt]->sCharacterData.iMonsterEffectID == snCHAR_SOUND_HOPYKING)
						MonCnt++;
				}
			}
			if (MonCnt >= 40)
				return FALSE;

			auto pMonstTable = SERVERUNIT->GetMonsterTable();

			for (auto & pc : pMonstTable)
			{
				if (pc->iMonsterEffectID == MONSTEREFFECTID_HOPYKING)
				{
					memcpy(lpCharInfo,pc, sizeof(CharacterData));
					break;
				}
			}
		}
		return TRUE;
	}

	return FALSE;
}

int CloseNPC_Caravan_Hopy(User *lpPlayInfo)
{
	int cnt = 0;

	for (cnt = 0; cnt < AUTOPLAYER_MAX; cnt++)
	{
		Unit *u = UNITSDATA + cnt;

		if (u->bActive && u->pcOwner == lpPlayInfo && u->CaravanSerial == lpPlayInfo->iID)
		{
			u->CaravanTime = 0;
			u->sUnitInfo.Caravan = 0;
			u->Close();
		}
	}

	return TRUE;
}
// Ë¢ÐÂÒÆ¶¯HOPY
Unit *OpenNpc_Caravan_Hopy(int Kind, int x, int y, int z, User *lpPlayInfo)
{
#ifdef _W_SERVER
	/*int cnt, cnt2;
	int height, dx, dy, dz, ta;
	int len = 0;
	Unit	*lpChar;
	Map *lpStgArea;
	STG_CHAR_INFO StgCharInfo;
	char szMsg[128];

	if (lpPlayInfo)
	{
		for (cnt = 0; cnt < AUTOPLAYER_MAX; cnt++)
		{
			Unit *u = UNITSDATA + cnt;

			if (u->bActive && u->pcOwner == lpPlayInfo && u->CaravanSerial == lpPlayInfo->iID)
				u->Close();
		}

		lpStgArea = SERVERMAP->GetMapByXZ(x, z);

		if (lpStgArea)
		{
			for (cnt = 0; cnt < 8; cnt++)
			{
				cnt2 = rand() % 8;

				dx = x + (ptItemSettingPosi[cnt2 & 7].x << (FLOATNS + 1));
				dz = z + (ptItemSettingPosi[cnt2 & 7].y << (FLOATNS + 1));
				dy = y;

				cnt2++;

				height = lpStgArea->pcStage->GetFloorHeight(dx, dy, dz, 32 * fONE);

				if (height != CLIP_OUT)
				{
					ta = abs(height - dy);
					if (ta < 32 * fONE)
						break;
				}
			}
			if (cnt < 8)
			{
				x = dx;
				z = dz;
				y = height;
			}

			StgCharInfo.PosiState = 0;
			StgCharInfo.sCharacterData.iType = CHARACTERTYPE_NPC;
			StgCharInfo.sCharacterData.sHP.sMin = 100;
			StgCharInfo.sCharacterData.sMP.sMin = 100;
			StgCharInfo.sCharacterData.sHP.sMax = 100;

			for (cnt = 0; cnt < chrMonsterCnt; cnt++)
			{
				switch (Kind)
				{
				case 0:
				case 1:
					if (lstrcmp(chrMonsterList[cnt].szName, "Hopy Caravan") == 0)
					{
						memcpy(&StgCharInfo.sCharacterData, &chrMonsterList[cnt], sizeof(CharacterData));
						len++;
						break;
					}
					break;
				case 2:
					if (lstrcmp(chrMonsterList[cnt].szName, "Arma Caravan") == 0)
					{
						memcpy(&StgCharInfo.sCharacterData, &chrMonsterList[cnt], sizeof(CharacterData));
						len++;
						break;
					}
					break;
				case 3:
					if (lstrcmp(chrMonsterList[cnt].szName, "Buma Caravan") == 0)
					{
						memcpy(&StgCharInfo.sCharacterData, &chrMonsterList[cnt], sizeof(CharacterData));
						len++;
						break;
					}
					break;
				case 4:
					if (lstrcmp(chrMonsterList[cnt].szName, "Cuepy Caravan") == 0)
					{
						memcpy(&StgCharInfo.sCharacterData, &chrMonsterList[cnt], sizeof(CharacterData));
						len++;
						break;
					}
					break;
				case 5:
					if (lstrcmp(chrMonsterList[cnt].szName, "Hungky Caravan") == 0)
					{
						memcpy(&StgCharInfo.sCharacterData, &chrMonsterList[cnt], sizeof(CharacterData));
						len++;
						break;
					}
					break;
				case 6:
					if (lstrcmp(chrMonsterList[cnt].szName, "Rabie Caravan") == 0)
					{
						memcpy(&StgCharInfo.sCharacterData, &chrMonsterList[cnt], sizeof(CharacterData));
						len++;
						break;
					}
					break;
				case 7:
					if (lstrcmp(chrMonsterList[cnt].szName, "Tobie Caravan") == 0)
					{
						memcpy(&StgCharInfo.sCharacterData, &chrMonsterList[cnt], sizeof(CharacterData));
						len++;
						break;
					}
					break;
				case 8:
					if (lstrcmp(chrMonsterList[cnt].szName, "Rudolf Caravan") == 0)
					{
						memcpy(&StgCharInfo.sCharacterData, &chrMonsterList[cnt], sizeof(CharacterData));
						len++;
						break;
					}
					break;
				}
			}
			if (len > 0)
			{
				lpStgArea->bForceCreateMonster = TRUE;
				lpChar = lpStgArea->OpenNpc(&StgCharInfo);

				if (lpChar)
				{
					lpChar->pX = x;
					lpChar->pY = y;
					lpChar->pZ = z;
					lpChar->DistAroundDbl = 0;
					lpChar->SetMotionFromCode(ANIMATIONTYPE_Idle);
					lpChar->TargetMoveCount = 0;
					lpChar->pcOwner = lpPlayInfo;
					wsprintf(szMsg, "%s's %s", lpPlayInfo->szCharacterName, lpChar->sCharacterData.szName);
					if (lstrlen(szMsg) <= sizeof(lpChar->sCharacterData.szName))
						lstrcpy(lpChar->sCharacterData.szName, szMsg);
					lpChar->sCharacterData.iOwnerID = lpPlayInfo->iID;
					lpChar->CaravanSerial = lpPlayInfo->iID;
					lpChar->CaravanTime = SERVER_GAMETIME + 4 * 60 * 1000;
					lpChar->CaravanMode = TRUE;

					return lpChar;
				}
			}
		}
	}*/
#endif
	return NULL;
}
//ÈÎÎñµØÍ¼Ë¢ÐÂ¹ÖÎï
Unit *OpenMonster_QuestArena(User *lpPlayInfo, DWORD dwQuestCode, int Param = 0)
{
#ifdef _W_SERVER
	Map	*lpStgArea;
	int	cnt, pow;
	Unit	*lpChar;
	DWORD	dwSndCode;
	int		OpenLevel = 0;

	switch (dwQuestCode)
	{
	case SIN_QUEST_CODE_CHANGEJOB4:
		if (GetRace(lpPlayInfo->sCharacterData.iClass) == BROOD_CODE_TEMPSKRON)
			dwSndCode = snCHAR_SOUND_NPC_SKILLMASTER;
		else
			dwSndCode = snCHAR_SOUND_NPC_MAGICMASTER;
		break;
	case HAQUEST_CODE_FURYOFPHANTOM:
		dwSndCode = snCHAR_SOUND_FURY;
		switch (Param)
		{
		case 1:
			OpenLevel = 118;
			break;
		case 2:
			OpenLevel = 119;
			break;
		case 3:
			OpenLevel = 120;
			break;
		}
	}
	for (cnt = 0; cnt < AUTOPLAYER_MAX; cnt++)
	{
		Unit *u = UNITSDATA + cnt;

		if (u->bActive && u->lpLinkPlayInfo == lpPlayInfo && u->lExclusiveTargetID == lpPlayInfo->iID)
		{
			u->Close();

			Map *pcMap = u->pcMap;

			pcMap->iNumAliveUnitData--;
			SERVERMAP->DelMonsterSpawn(pcMap, u);
		}
	}

	lpStgArea = SERVERMAP->GetMap(MAPID_QuestArena);

	if (lpStgArea)
	{
		auto pMonstTable = SERVERUNIT->GetMonsterTable();

		for (auto & pc : pMonstTable)
		{
			if (pc->iMonsterEffectID == dwSndCode && (OpenLevel == 0 || OpenLevel == pc->iLevel))
			{
				lpStgArea->bForceCreateMonster = TRUE;
				lpChar = SERVERMAP->CreateUnit(lpStgArea, pc);
				if (lpChar)
				{
					lpChar->SetPosi(QUEST_ARENA_NPC_POS_X, 0, QUEST_ARENA_NPC_POS_Z, 0, 0, 0);
					lpChar->iLureDistance = 0;
					lpChar->SetMotionFromCode(ANIMATIONTYPE_Idle);
					lpChar->TargetMoveCount = 0;
					lpChar->lpLinkPlayInfo = lpPlayInfo;
					lpChar->lExclusiveTargetID = lpPlayInfo->iID;
					lpChar->dwLastUpdateTime = SERVER_GAMETIME + 30 * 60 * 1000;

					pow = lpPlayInfo->sCharacterData.iLevel - 60;

					if (pow < 0)
						pow = 0;

					pow += pow / 2;

					lpChar->sCharacterData.sHP.sMin += (lpChar->sCharacterData.sHP.sMin * pow) / 100;
					if (lpChar->sCharacterData.sHP.sMin < 0 || lpChar->sCharacterData.sHP.sMin>30000)
						lpChar->sCharacterData.sHP.sMin = 30000;
					lpChar->sCharacterData.sHP.sMax = lpChar->sCharacterData.sHP.sMin;

					lpChar->sCharacterData.iMinDamage += (lpChar->sCharacterData.iMinDamage * pow) / 100;
					lpChar->sCharacterData.iMaxDamage += (lpChar->sCharacterData.iMaxDamage * pow) / 100;

					lpChar->sUnitInfo.SkillDamage[0] += (lpChar->sUnitInfo.SkillDamage[0] * pow) / 100;
					lpChar->sUnitInfo.SkillDamage[1] += (lpChar->sUnitInfo.SkillDamage[1] * pow) / 100;

					lpChar->sUnitInfo.iMaxPotions += 3;

					return lpChar;
				}
			}
		}
	}
#endif
	return NULL;
}

int rsGetMonCountFlag(Unit *lpChar)
{
	Map *lpStgArea;
	if (!lpChar->pcMap) return -1;

	lpStgArea = lpChar->pcMap;

	return lpStgArea->iaSpawnMonsterActive[lpChar->iSpawnPointIndex];
}
Unit *rsOpenSubMonster(Unit *lpMainChar, DWORD iMonsterEffectID, int x, int y, int z, int MaxFlag)
{
	Map *lpStgArea;
	STG_CHAR_INFO StgCharInfo;
	Unit	*lpChar;

	if (!lpMainChar->pcMap) return FALSE;

	lpStgArea = lpMainChar->pcMap;

	if (lpStgArea->iaSpawnMonsterActive[lpMainChar->iSpawnPointIndex] >= MaxFlag)
		return FALSE;

	if (lpStgArea)
	{
		auto pMonstTable = SERVERUNIT->GetMonsterTable();

		for (auto & pc : pMonstTable)
		{
			if (pc->iMonsterEffectID == iMonsterEffectID)
			{
				lpChar = SERVERUNIT->GetEmptyUnit();
				if (!lpChar) 
					return NULL;

				lpChar->Init();
				lpChar->lpStage = lpMainChar->lpStage;
				lpChar->SetPosi(x, y, z, lpMainChar->Angle.x, lpMainChar->Angle.y, lpMainChar->Angle.z);
				lpChar->sSpawnPosition.iX = x;
				lpChar->sSpawnPosition.iY = lpChar->pY;
				lpChar->sSpawnPosition.iZ = y;
				lpChar->iLureDistance = DIST_AROUND_MIDDLE;
				lpChar->iSpawnPointIndex = lpMainChar->iSpawnPointIndex;

				lpStgArea->iNumAliveUnitData++;
				lpChar->pcMap = lpStgArea;
				lpChar->iID = SERVERUNIT->CreateID();
				lpChar->ActionPattern = 5;
				memcpy(&lpChar->sCharacterData, &StgCharInfo.sCharacterData, sizeof(CharacterData));
				memcpy(&lpChar->sUnitInfo, StgCharInfo.sCharacterData.psUnitInfo, sizeof(UnitInfo));
				lpChar->SetLoadPattern(lpChar->sCharacterData.Player.szBodyModel);
				lpChar->sCharacterData.iStatPoints = StgCharInfo.sCharacterData.psUnitInfo->ClassCode;
				lpChar->iLureDistance = 0;
				lpChar->AttackUserFlag = 0;
				lpChar->pcKillerData = nullptr;
				lpChar->pcLastAttacker = 0;
				lpChar->iDamageLastAttacker = 0;

				SERVERMAP->AddMonsterSpawn(lpStgArea, lpChar);

				lpChar->iDeathCounter = REOPEN_COUNT_NUM;
				lpChar->dwLastActiveTime = SERVER_GAMETIME;

				if (lpChar->sUnitInfo.iMaxPotions)
				{
					if ((rand() % 100) < lpChar->sUnitInfo.iPerPotions)
						lpChar->sUnitInfo.iMaxPotions = (rand() % lpChar->sUnitInfo.iMaxPotions) + 1;
					else
						lpChar->sUnitInfo.iMaxPotions = 0;
				}

				rsMonOpenCount++;

				lpChar->SetMotionFromCode(ANIMATIONTYPE_Idle);
				lpChar->TargetMoveCount = 0;

				return lpChar;
			}
		}
	}

	return FALSE;
}
POINT3D	rsHardCoreEventOpenPos[7][3] =
{
	{ // »ð
		{ 18967,  1154,	3055 },
		{ 19995,  1154,	2134 },
		{ 19485,  1154,	2615 }
	},
	{// Ë®
		{ 20838,  1154,	3024 },
		{ 21671,  1154,	2193 },
		{ 21255,  1154,	2615 }
	},
	{// µØ
		{ 22478,  1154,	3049 },
		{ 23437,  1154,	2135 },
		{ 22948,  1154,	2615 }
	},
	{// ·ç
		{ 24204,  1154,	3094 },
		{ 25173,  1154,	2135 },
		{ 24674,  1154,	2615 }
	},
	{// ÔÂ
		{ 20509,  1621,	5284 },
		{ 21544,  1621,	4261 },
		{ 21012,  1621,	4773 }
	},
	{// ÈÕ
		{ 22575,  1621,	5253 },
		{ 23610,  1621,	4230 },
		{ 23077,  1621,	4742 }
	},
	{// ÌìÌÃ
		{ 21538,  1638,	7057 },
		{ 22527,  1638,	6079 },
		{ 22018,  1638,	6569 }
	}
};
int	rsSod_RoundTable[8][2] =
{
	{	0,	4	},		//1
	{	0,	4	},		//2
	{	0,	4	},		//3
	{	4,	6	},		//4
	{	4,	6	},		//5
	{	4,	6	},		//6
	{	6,	7	},		//7
	{	6,	7	}		//8
};
int	rsSod_RoundRoomTable[4][8] =
{
	{	0,	0,	0,	4,	4,	4,	6,	6	},
	{	1,	1,	1,	4,	4,	4,	6,	6	},
	{	2,	2,	2,	5,	5,	5,	6,	6	},
	{	3,	3,	3,	5,	5,	5,	6,	6	}
};


int rsHardCoreEventArea[4] = { 18516 , 25715, 1541 , 7178 };


int	rsHardCoreEventInterLineZ = -32 * fONE;
int	rsHardCoreEventInterLineZ2 = -64 * fONE;
int	rsHardCoreEventPosY = (950 - 32)*fONE;
int	rsHardCoreEventOutLineZ = -600 * fONE;
int	rsHardCoreEvent_TicketHour = 4;

DWORD	dwHardCoreEvent_OutTime;

int	rsEventTicketCount;
int	rsEventTicketLevel[4];

int	rsHardCoreEventMode = 0;
int	rsHardCoreEventTimeOver = 0;

#define	rsEVENT_TICKET_LEVEL_TOTAL		549


struct	sSOD_USER
{
	User	*lpPlayInfo;
	DWORD		dwConnCode;
	DWORD		Temp[4];
};

#define	rsSOD_USER_MAX	120
#define	rsSOD_UPDATE_TIME	6000

sSOD_USER	rsSodUser[rsSOD_USER_MAX];
int	rsSodUserCount;
DWORD	rsTransSodTime = 0;
DWORD	dwSoD_DelayTime = 0;

int	rsSodTeamScore[4];		//Sod ÆÀ µæÁ¡°ª
int	rsSodTeamRank[4];		//Sod ÆÀ ¼øÀ§

#ifdef	_W_SERVER

#define XOR_ITEM_SeCode_0	0x536c56ba
#define XOR_ITEM_SeCode_1	0x9ab536cd
#define XOR_ITEM_SeCode_2	0xc6abce56

DWORD rsITEM_SecCode_Xor[16] = {
	0x6794bca6 ,		//0
		0x78645fe3 ,		//1
		0xcea82934 ,		//2
		0x56fdca87 ,		//3
		0x357d3653 ,		//4
		0xf3487eba ,		//5
		0x3478978f ,		//6
		0x6793fbc2 ,		//7
		0x5842eec6 ,		//8
		0x257ecdb5 ,		//9
		0x579cbec5 ,		//A
		0x985612ab ,		//B
		0x5487cc56 ,		//C
		0xba7d4553 ,		//D
		0xeca53b96 ,		//E
		0xb5c549ce			//F
};

//#define rsRegist_EnterKey( _dwCode , _dwAdd )  rsITEM_SecCode_Xor[(_dwCode+_dwAdd)&0xF]
DWORD rsRegist_EnterKey(DWORD _dwCode, DWORD _dwAdd)
{
	return rsITEM_SecCode_Xor[(_dwCode + _dwAdd) & 0xF];
}

#define	SOD_DEFAULT_DELAY	5


sHCORE_MONSTER	sHCoreEvent1[] =
{
	{ { "÷¼÷ÃÓÎÆï±ø" , 0, 40 }			, { "Ä§ÊÞ¹Ö", 0, 30 }			, { "Ì©Ì¹¾ÞÈË", 0, 20 }			, { "ÄàÑý", 0, 10 }			, { "³¬¼¶Ä§½£Ê¿", 0, 0 }		, 100 , 6	, 0		, 40 , SOD_DEFAULT_DELAY },
	{ { "Ä¾ÄËÒÁ" , 0, 35 }				, { "Ä§½£Ê¥", 0, 20 }			, { "Ä§Õ½ÑýÍõ", 0, 35 }			, { "»ðÁéÍõ", 0, 10 }		, { "³¬¼¶¶À½ÇÊÞÍõ", 0, 0 }		, 100 , 8	, 0		, 40 , SOD_DEFAULT_DELAY },
	{ { "¾£¼¬ÅÀÐÐÕß" , 0, 35 }			, { "ÃÎ÷Ê", 0, 30 }				, { "ÖØ×°Ä§ÊÞ±ø", 0, 25 }		, { "ÎÞË«Ê¯Ä§", 0, 10 }		, { "³¬¼¶ÓÄÁé", 0, 0 }			, 100 , 10	, 0		, 40 , SOD_DEFAULT_DELAY },
	{ { "Ìú¼×¾Þòá" , 0, 45 }			, { "Ä¾ÄËÒÁÆìÖ÷", 0, 25 }		, { "Ë«µ¶ÄÈåÈ", 0, 20 }			, { "Ö©ÖëÅ®»Ê", 0, 10 }		, { "³¬¼¶ÊÈÑªÍÀÀÇ", 0, 0 }		, 100 , 12	, 0		, 35 , SOD_DEFAULT_DELAY * 2 },
	{ { "ÉñÃØÊ®°Ë" , 0, 30 }			, { "°ÔÌìÖë", 0, 20 }			, { "¾Þ´¸Ä§", 0, 40 }			, { "ÌúÈ­", 0, 10 }			, { "³¬¼¶Ô¶¹Å¼ÀË¾", 0, 0 }		, 100 , 15	, 0		, 30 , SOD_DEFAULT_DELAY },
	{ { "±ù¼×Ä§ÊÞ±ø" , 0, 20 }			, { "ÀäÑÛÄ§", 0, 20 }			, { "±ùÊ¯ÈË", 0, 40 }			, { "º®ËªÄ§", 0, 20 }		, { "ÃüÔËÅ®Éñ", 0, 0 }			, 100 , 18	, 0		, 25 , SOD_DEFAULT_DELAY },
	{ { "±ù¼×¶ÀÑÛ" , 0, 30 }			, { "°ÔÌì¹ê", 0, 40 }			, { "±ù¼×ÎÞË«", 0, 20 } 		, { "±ù·çÄ§Íõ", 0, 10 }		, { "ÃüÔËÅ®Éñ", 0, 0 }			, 100 , 21	, 0		, 20 , SOD_DEFAULT_DELAY * 3 },
	{ { "ÎüÑªòùòð" , 0, 20 }			, { "°Â×È", 0, 30 }				, { "¿¨¿¨àÞ", 0, 30 }			, { "Ë¹ÆÕÁÖ", 0, 20 }		, { "ÃüÔËÖ®Ö÷", 0, 0 }			, 100 , 0	, 50000 , 15 , SOD_DEFAULT_DELAY },
	{ { "" , 0, 0 } 					, { "", 0, 0 } 					, { "", 0, 0 } 					, { "", 0, 0 } 				, { "", 0, 0 }					, 0	  ,	3	, 0		, 0}
};
sHCORE_MONSTER	sHCoreEvent2[] =
{
	{ { "÷¼÷ÃÓÎÆï±ø" , 0, 40 }			, { "Ä§ÊÞ¹Ö", 0, 30 }			, { "Ì©Ì¹¾ÞÈË", 0, 20 }			, { "ÄàÑý", 0, 10 }			, { "³¬¼¶Ä§½£Ê¿", 0, 0 }		, 100 , 6	, 0		, 40 , SOD_DEFAULT_DELAY },
	{ { "Ä¾ÄËÒÁ" , 0, 35 }				, { "Ä§½£Ê¥", 0, 20 }			, { "Ä§Õ½ÑýÍõ", 0, 35 }			, { "»ðÁéÍõ", 0, 10 }		, { "³¬¼¶¶À½ÇÊÞÍõ", 0, 0 }		, 100 , 8	, 0		, 40 , SOD_DEFAULT_DELAY },
	{ { "¾£¼¬ÅÀÐÐÕß" , 0, 35 }			, { "ÃÎ÷Ê", 0, 30 }				, { "ÖØ×°Ä§ÊÞ±ø", 0, 25 }		, { "ÎÞË«Ê¯Ä§", 0, 10 }		, { "³¬¼¶ÓÄÁé", 0, 0 }			, 100 , 10	, 0		, 40 , SOD_DEFAULT_DELAY },
	{ { "Ìú¼×¾Þòá" , 0, 45 }			, { "Ä¾ÄËÒÁÆìÖ÷", 0, 25 }		, { "Ë«µ¶ÄÈåÈ", 0, 20 }			, { "Ö©ÖëÅ®»Ê", 0, 10 }		, { "³¬¼¶ÊÈÑªÍÀÀÇ", 0, 0 }		, 100 , 12	, 0		, 35 , SOD_DEFAULT_DELAY * 2 },
	{ { "ÉñÃØÊ®°Ë" , 0, 30 }			, { "°ÔÌìÖë", 0, 20 }			, { "¾Þ´¸Ä§", 0, 40 }			, { "ÌúÈ­", 0, 10 }			, { "³¬¼¶Ô¶¹Å¼ÀË¾", 0, 0 }		, 100 , 15	, 0		, 30 , SOD_DEFAULT_DELAY },
	{ { "±ù¼×Ä§ÊÞ±ø" , 0, 20 }			, { "ÀäÑÛÄ§", 0, 20 }			, { "±ùÊ¯ÈË", 0, 40 }			, { "º®ËªÄ§", 0, 20 }		, { "ÃüÔËÅ®Éñ", 0, 0 }			, 100 , 18	, 0		, 25 , SOD_DEFAULT_DELAY },
	{ { "±ù¼×¶ÀÑÛ" , 0, 30 }			, { "°ÔÌì¹ê", 0, 40 }			, { "±ù¼×ÎÞË«", 0, 20 } 		, { "±ù·çÄ§Íõ", 0, 10 }		, { "ÃüÔËÅ®Éñ", 0, 0 }			, 100 , 21	, 0		, 20 , SOD_DEFAULT_DELAY * 3 },
	{ { "ÎüÑªòùòð" , 0, 20 }			, { "°Â×È", 0, 30 }				, { "¿¨¿¨àÞ", 0, 30 }			, { "Ë¹ÆÕÁÖ", 0, 20 }		, { "ÃüÔËÖ®Ö÷", 0, 0 }			, 100 , 0	, 50000 , 15 , SOD_DEFAULT_DELAY },
	{ { "" , 0, 0 } 					, { "", 0, 0 } 					, { "", 0, 0 } 					, { "", 0, 0 } 				, { "", 0, 0 }					, 0	  ,	3	, 0		, 0}
};
sHCORE_MONSTER	sHCoreEvent3[] =
{
	{ { "÷¼÷ÃÓÎÆï±ø" , 0, 40 }			, { "Ä§ÊÞ¹Ö", 0, 30 }			, { "Ì©Ì¹¾ÞÈË", 0, 20 }			, { "ÄàÑý", 0, 10 }			, { "³¬¼¶Ä§½£Ê¿", 0, 0 }		, 100 , 6	, 0		, 40 , SOD_DEFAULT_DELAY },
	{ { "Ä¾ÄËÒÁ" , 0, 35 }				, { "Ä§½£Ê¥", 0, 20 }			, { "Ä§Õ½ÑýÍõ", 0, 35 }			, { "»ðÁéÍõ", 0, 10 }		, { "³¬¼¶¶À½ÇÊÞÍõ", 0, 0 }		, 100 , 8	, 0		, 40 , SOD_DEFAULT_DELAY },
	{ { "¾£¼¬ÅÀÐÐÕß" , 0, 35 }			, { "ÃÎ÷Ê", 0, 30 }				, { "ÖØ×°Ä§ÊÞ±ø", 0, 25 }		, { "ÎÞË«Ê¯Ä§", 0, 10 }		, { "³¬¼¶ÓÄÁé", 0, 0 }			, 100 , 10	, 0		, 40 , SOD_DEFAULT_DELAY },
	{ { "Ìú¼×¾Þòá" , 0, 45 }			, { "Ä¾ÄËÒÁÆìÖ÷", 0, 25 }		, { "Ë«µ¶ÄÈåÈ", 0, 20 }			, { "Ö©ÖëÅ®»Ê", 0, 10 }		, { "³¬¼¶ÊÈÑªÍÀÀÇ", 0, 0 }		, 100 , 12	, 0		, 35 , SOD_DEFAULT_DELAY * 2 },
	{ { "ÉñÃØÊ®°Ë" , 0, 30 }			, { "°ÔÌìÖë", 0, 20 }			, { "¾Þ´¸Ä§", 0, 40 }			, { "ÌúÈ­", 0, 10 }			, { "³¬¼¶Ô¶¹Å¼ÀË¾", 0, 0 }		, 100 , 15	, 0		, 30 , SOD_DEFAULT_DELAY },
	{ { "±ù¼×Ä§ÊÞ±ø" , 0, 20 }			, { "ÀäÑÛÄ§", 0, 20 }			, { "±ùÊ¯ÈË", 0, 40 }			, { "º®ËªÄ§", 0, 20 }		, { "ÃüÔËÅ®Éñ", 0, 0 }			, 100 , 18	, 0		, 25 , SOD_DEFAULT_DELAY },
	{ { "±ù¼×¶ÀÑÛ" , 0, 30 }			, { "°ÔÌì¹ê", 0, 40 }			, { "±ù¼×ÎÞË«", 0, 20 } 		, { "±ù·çÄ§Íõ", 0, 10 }		, { "ÃüÔËÅ®Éñ", 0, 0 }			, 100 , 21	, 0		, 20 , SOD_DEFAULT_DELAY * 3 },
	{ { "ÎüÑªòùòð" , 0, 20 }			, { "°Â×È", 0, 30 }				, { "¿¨¿¨àÞ", 0, 30 }			, { "Ë¹ÆÕÁÖ", 0, 20 }		, { "ÃüÔËÖ®Ö÷", 0, 0 }			, 100 , 0	, 50000 , 15 , SOD_DEFAULT_DELAY },
	{ { "" , 0, 0 } 					, { "", 0, 0 } 					, { "", 0, 0 } 					, { "", 0, 0 } 				, { "", 0, 0 }					, 0	  ,	3	, 0		, 0}
};

sHCORE_MONSTER	sHCoreEvent_Bellatra[3][hCORE_ROUND_MAX];
sHCORE_MONSTER	*sHCoreEvent = sHCoreEvent2;

_sHCORE_MONSTER	hCoreMonsters[5];

TRANS_SOD_RESULT	TransSodResult;
TRANS_SOD_RESULT	TransSodResult_RealTime[5];
TRANS_SOD_RESULT	TransSodResult_Round;

int	rsHardCoreEvent_Count;
int rsHardCoreEvent_MonsterMax;

CharacterData	*rsHardCoreBoss;
int rsHardCoreEvent_OpenBoss[8];
int rsHardCoreEvent_OpenCount[8];

int	rsHardCoreEvent_TotalUser;
int	rsSoD_StartCode;
int	rsSOD_Tax = 5;
char rsSOD_Text[256] = { 0, };


// SOD »ñµÃ¾­ÑéÖµ±ÈÂÊ
int	rsSOD_ScoreDiv = 15;

int	rsInitHardCoreEvent()
{
	int cnt;
	int total;

	rsHardCoreEvent_Count = 0;
	rsHardCoreEvent_TotalUser = 0;

	sHCoreEvent = sHCoreEvent1;
	cnt = 0;

	auto pMonstTable = SERVERUNIT->GetMonsterTable();

	while (sHCoreEvent[cnt].hCoreMonster1.szName[0] != 0)
	{
		total = 0;

		for (auto & pc : pMonstTable)
		{
			if (!sHCoreEvent[cnt].hCoreMonster1.lpCharInfo &&
				STRINGCOMPAREI(sHCoreEvent[cnt].hCoreMonster1.szName, pc->szName))
				sHCoreEvent[cnt].hCoreMonster1.lpCharInfo = pc;
			if (!sHCoreEvent[cnt].hCoreMonster2.lpCharInfo &&
				STRINGCOMPAREI(sHCoreEvent[cnt].hCoreMonster2.szName, pc->szName))
				sHCoreEvent[cnt].hCoreMonster2.lpCharInfo = pc;
			if (!sHCoreEvent[cnt].hCoreMonster3.lpCharInfo &&
				STRINGCOMPAREI(sHCoreEvent[cnt].hCoreMonster3.szName, pc->szName))
				sHCoreEvent[cnt].hCoreMonster3.lpCharInfo = pc;
			if (!sHCoreEvent[cnt].hCoreMonster4.lpCharInfo &&
				STRINGCOMPAREI(sHCoreEvent[cnt].hCoreMonster4.szName, pc->szName))
				sHCoreEvent[cnt].hCoreMonster4.lpCharInfo = pc;
			if (!sHCoreEvent[cnt].hCoreMonsterBoss.lpCharInfo &&
				STRINGCOMPAREI(sHCoreEvent[cnt].hCoreMonsterBoss.szName, pc->szName))
				sHCoreEvent[cnt].hCoreMonsterBoss.lpCharInfo = pc;
		}

		if (sHCoreEvent[cnt].hCoreMonster2.lpCharInfo)
			sHCoreEvent[cnt].hCoreMonster2.perCount += sHCoreEvent[cnt].hCoreMonster1.perCount;
		if (sHCoreEvent[cnt].hCoreMonster3.lpCharInfo)
			sHCoreEvent[cnt].hCoreMonster3.perCount += sHCoreEvent[cnt].hCoreMonster2.perCount;
		if (sHCoreEvent[cnt].hCoreMonster4.lpCharInfo)
			sHCoreEvent[cnt].hCoreMonster4.perCount += sHCoreEvent[cnt].hCoreMonster3.perCount;

		cnt++;
	}

	sHCoreEvent = sHCoreEvent2;
	cnt = 0;
	while (sHCoreEvent[cnt].hCoreMonster1.szName[0] != 0)
	{
		total = 0;

		for (auto & pc : pMonstTable)
		{
			if (!sHCoreEvent[cnt].hCoreMonster1.lpCharInfo && 
				STRINGCOMPAREI(sHCoreEvent[cnt].hCoreMonster1.szName, pc->szName))
				sHCoreEvent[cnt].hCoreMonster1.lpCharInfo = pc;
			if (!sHCoreEvent[cnt].hCoreMonster2.lpCharInfo && 
				STRINGCOMPAREI(sHCoreEvent[cnt].hCoreMonster2.szName, pc->szName))
				sHCoreEvent[cnt].hCoreMonster2.lpCharInfo = pc;
			if (!sHCoreEvent[cnt].hCoreMonster3.lpCharInfo && 
				STRINGCOMPAREI(sHCoreEvent[cnt].hCoreMonster3.szName, pc->szName))
				sHCoreEvent[cnt].hCoreMonster3.lpCharInfo = pc;
			if (!sHCoreEvent[cnt].hCoreMonster4.lpCharInfo && 
				STRINGCOMPAREI(sHCoreEvent[cnt].hCoreMonster4.szName, pc->szName))
				sHCoreEvent[cnt].hCoreMonster4.lpCharInfo = pc;
			if (!sHCoreEvent[cnt].hCoreMonsterBoss.lpCharInfo && 
				STRINGCOMPAREI(sHCoreEvent[cnt].hCoreMonsterBoss.szName, pc->szName))
				sHCoreEvent[cnt].hCoreMonsterBoss.lpCharInfo = pc;
		}
		if (sHCoreEvent[cnt].hCoreMonster2.lpCharInfo)
			sHCoreEvent[cnt].hCoreMonster2.perCount += sHCoreEvent[cnt].hCoreMonster1.perCount;
		if (sHCoreEvent[cnt].hCoreMonster3.lpCharInfo)
			sHCoreEvent[cnt].hCoreMonster3.perCount += sHCoreEvent[cnt].hCoreMonster2.perCount;
		if (sHCoreEvent[cnt].hCoreMonster4.lpCharInfo)
			sHCoreEvent[cnt].hCoreMonster4.perCount += sHCoreEvent[cnt].hCoreMonster3.perCount;

		cnt++;
	}

	sHCoreEvent = sHCoreEvent3;
	cnt = 0;

	while (sHCoreEvent[cnt].hCoreMonster1.szName[0] != 0)
	{
		total = 0;

		for (auto & pc : pMonstTable)
		{
			if (!sHCoreEvent[cnt].hCoreMonster1.lpCharInfo && 
				STRINGCOMPAREI(sHCoreEvent[cnt].hCoreMonster1.szName, pc->szName))
				sHCoreEvent[cnt].hCoreMonster1.lpCharInfo = pc;
			if (!sHCoreEvent[cnt].hCoreMonster2.lpCharInfo && 
				STRINGCOMPAREI(sHCoreEvent[cnt].hCoreMonster2.szName, pc->szName))
				sHCoreEvent[cnt].hCoreMonster2.lpCharInfo = pc;
			if (!sHCoreEvent[cnt].hCoreMonster3.lpCharInfo && 
				STRINGCOMPAREI(sHCoreEvent[cnt].hCoreMonster3.szName, pc->szName))
				sHCoreEvent[cnt].hCoreMonster3.lpCharInfo = pc;
			if (!sHCoreEvent[cnt].hCoreMonster4.lpCharInfo && 
				STRINGCOMPAREI(sHCoreEvent[cnt].hCoreMonster4.szName, pc->szName))
				sHCoreEvent[cnt].hCoreMonster4.lpCharInfo = pc;
			if (!sHCoreEvent[cnt].hCoreMonsterBoss.lpCharInfo && 
				STRINGCOMPAREI(sHCoreEvent[cnt].hCoreMonsterBoss.szName, pc->szName))
				sHCoreEvent[cnt].hCoreMonsterBoss.lpCharInfo = pc;
		}

		if (sHCoreEvent[cnt].hCoreMonster2.lpCharInfo)
			sHCoreEvent[cnt].hCoreMonster2.perCount += sHCoreEvent[cnt].hCoreMonster1.perCount;
		if (sHCoreEvent[cnt].hCoreMonster3.lpCharInfo)
			sHCoreEvent[cnt].hCoreMonster3.perCount += sHCoreEvent[cnt].hCoreMonster2.perCount;
		if (sHCoreEvent[cnt].hCoreMonster4.lpCharInfo)
			sHCoreEvent[cnt].hCoreMonster4.perCount += sHCoreEvent[cnt].hCoreMonster3.perCount;

		cnt++;
	}

	memcpy(sHCoreEvent_Bellatra[0], sHCoreEvent1, sizeof(sHCORE_MONSTER)*hCORE_ROUND_MAX);
	memcpy(sHCoreEvent_Bellatra[1], sHCoreEvent2, sizeof(sHCORE_MONSTER)*hCORE_ROUND_MAX);
	memcpy(sHCoreEvent_Bellatra[2], sHCoreEvent3, sizeof(sHCORE_MONSTER)*hCORE_ROUND_MAX);

	memcpy(&hCoreMonsters[0], &sHCoreEvent[0].hCoreMonster1, sizeof(_sHCORE_MONSTER));
	memcpy(&hCoreMonsters[1], &sHCoreEvent[0].hCoreMonster2, sizeof(_sHCORE_MONSTER));
	memcpy(&hCoreMonsters[2], &sHCoreEvent[0].hCoreMonster3, sizeof(_sHCORE_MONSTER));
	memcpy(&hCoreMonsters[3], &sHCoreEvent[0].hCoreMonster4, sizeof(_sHCORE_MONSTER));
	memcpy(&hCoreMonsters[4], &sHCoreEvent[0].hCoreMonsterBoss, sizeof(_sHCORE_MONSTER));
	rsEventTicketCount = 0;

	rsEventTicketLevel[0] = 0;
	rsEventTicketLevel[1] = 0;
	rsEventTicketLevel[2] = 0;
	rsEventTicketLevel[3] = 0;

	rsHardCoreEvent_MonsterMax = 40;

	rsSoD_StartCode = (ServerNameCode << 24) | ((SERVER_LOCATIME) & 0xFFFFFF);

	ZeroMemory(&TransSodResult, sizeof(TRANS_SOD_RESULT));
	ZeroMemory(&TransSodResult_RealTime[0], sizeof(TRANS_SOD_RESULT));
	ZeroMemory(&TransSodResult_RealTime[1], sizeof(TRANS_SOD_RESULT));
	ZeroMemory(&TransSodResult_RealTime[2], sizeof(TRANS_SOD_RESULT));
	ZeroMemory(&TransSodResult_RealTime[3], sizeof(TRANS_SOD_RESULT));
	ZeroMemory(&TransSodResult_RealTime[4], sizeof(TRANS_SOD_RESULT));
	ZeroMemory(&TransSodResult_Round, sizeof(TRANS_SOD_RESULT));

	ZeroMemory(rsSodTeamScore, sizeof(int) * 4);
	ZeroMemory(rsSodUser, sizeof(sSOD_USER)*rsSOD_USER_MAX);
	rsSodUserCount = 0;

	return TRUE;
}

//SOD ÅäÖÃ
int	rsOpen_SODConfig()
{
	int cnt;

	if (Open_SODConfig("Bellatra\\bellatra.ini", sHCoreEvent_Bellatra[0], &rsSOD_Tax, rsSOD_Text, &rsSOD_ScoreDiv) == 0)
	{
		memcpy(sHCoreEvent_Bellatra[0], sHCoreEvent1, sizeof(sHCORE_MONSTER)*hCORE_ROUND_MAX);
		memcpy(sHCoreEvent_Bellatra[1], sHCoreEvent2, sizeof(sHCORE_MONSTER)*hCORE_ROUND_MAX);
		memcpy(sHCoreEvent_Bellatra[2], sHCoreEvent3, sizeof(sHCORE_MONSTER)*hCORE_ROUND_MAX);
		return FALSE;
	}

	sHCoreEvent = sHCoreEvent_Bellatra[0];
	cnt = 0;
	while (1)
	{
		if (sHCoreEvent[cnt].hCoreMonster1.szName[0] == 0)
			break;
		if (cnt >= rsHARDCORE_COUNT_END)
			break;

		auto pMonstTable = SERVERUNIT->GetMonsterTable();

		for (auto & pc : pMonstTable)
		{
			if (!sHCoreEvent[cnt].hCoreMonster1.lpCharInfo &&
				STRINGCOMPAREI(sHCoreEvent[cnt].hCoreMonster1.szName, pc->szName))
				sHCoreEvent[cnt].hCoreMonster1.lpCharInfo = pc;
			if (!sHCoreEvent[cnt].hCoreMonster2.lpCharInfo &&
				STRINGCOMPAREI(sHCoreEvent[cnt].hCoreMonster2.szName, pc->szName))
				sHCoreEvent[cnt].hCoreMonster2.lpCharInfo = pc;
			if (!sHCoreEvent[cnt].hCoreMonster3.lpCharInfo &&
				STRINGCOMPAREI(sHCoreEvent[cnt].hCoreMonster3.szName, pc->szName))
				sHCoreEvent[cnt].hCoreMonster3.lpCharInfo = pc;
			if (!sHCoreEvent[cnt].hCoreMonster4.lpCharInfo &&
				STRINGCOMPAREI(sHCoreEvent[cnt].hCoreMonster4.szName, pc->szName))
				sHCoreEvent[cnt].hCoreMonster4.lpCharInfo = pc;
			if (!sHCoreEvent[cnt].hCoreMonsterBoss.lpCharInfo &&
				STRINGCOMPAREI(sHCoreEvent[cnt].hCoreMonsterBoss.szName, pc->szName))
				sHCoreEvent[cnt].hCoreMonsterBoss.lpCharInfo = pc;
		}

		if (sHCoreEvent[cnt].hCoreMonster2.lpCharInfo)
			sHCoreEvent[cnt].hCoreMonster2.perCount += sHCoreEvent[cnt].hCoreMonster1.perCount;
		if (sHCoreEvent[cnt].hCoreMonster3.lpCharInfo)
			sHCoreEvent[cnt].hCoreMonster3.perCount += sHCoreEvent[cnt].hCoreMonster2.perCount;
		if (sHCoreEvent[cnt].hCoreMonster4.lpCharInfo)
			sHCoreEvent[cnt].hCoreMonster4.perCount += sHCoreEvent[cnt].hCoreMonster3.perCount;

		cnt++;
	}

	memcpy(sHCoreEvent_Bellatra[1], sHCoreEvent, sizeof(sHCORE_MONSTER)*hCORE_ROUND_MAX);
	memcpy(sHCoreEvent_Bellatra[2], sHCoreEvent, sizeof(sHCORE_MONSTER)*hCORE_ROUND_MAX);

	return TRUE;
}
int	rsGetHardCoreEventOpenMonsterPos(int *mx, int *my, int *mz, int Room)
{
	int x, y, z;
	int cx, cz;

	x = rsHardCoreEventOpenPos[Room][0].x;
	y = rsHardCoreEventOpenPos[Room][0].y;
	z = rsHardCoreEventOpenPos[Room][0].z;

	cx = rsHardCoreEventOpenPos[Room][1].x - x;
	cz = z - rsHardCoreEventOpenPos[Room][1].z;

	cx = rand() % cx;
	cz = rand() % cz;

	*mx = (x + cx)*fONE;
	*mz = (z - cz)*fONE;
	*my = y * fONE;

	return TRUE;
}
int rsSetSodTeamRank()
{
	int cnt, cnt1;
	int r1, r2;

	rsSodTeamRank[0] = 0;
	rsSodTeamRank[1] = 1;
	rsSodTeamRank[2] = 2;
	rsSodTeamRank[3] = 3;

	for (cnt = 0; cnt < 4; cnt++)
	{
		for (cnt1 = cnt; cnt1 < 4; cnt1++)
		{
			r1 = rsSodTeamRank[cnt];
			r2 = rsSodTeamRank[cnt1];

			if (rsSodTeamScore[r1] < rsSodTeamScore[r2])
			{
				rsSodTeamRank[cnt] = r2;
				rsSodTeamRank[cnt1] = r1;
			}
		}
	}

	return TRUE;
}

int rsHardCoreEvent_OpenMonster(Map *lpStgArea, STG_CHAR_INFO *lpStgCharInfo)
{
	//STG_CHAR_INFO		 StgCharInfo;

	TRANS_CHATMESSAGE	TransChatMessage;
	TRANS_CHATMESSAGE	TransChatMessage2;
	smTRANS_COMMAND		smTransCommand;
	smTRANS_COMMAND		smTransCommand2;

	Unit	*lpChar;
	int x, y, z;
	int total;
	int	total2;
	int totalScore;

	int cnt,mcnt;
	int	rnk;
	int	money;

	if (rsHardCoreEventTimeOver)
	{
		if (rsHardCoreEventMode)
			rsHardCoreEventTimeOver = FALSE;
		else
			return TRUE;
	}

	if (SERVERMAP->GetTime() == sHCoreEvent[rsHardCoreEvent_Count].StartHour)
	{
		if (rsHardCoreEvent_Count == 0)
			rsOpen_SODConfig();

		for (cnt = 0; cnt < MAX_ALIVEMONSTERS; cnt++)
		{
			if (lpStgArea->pcaUnitData[cnt])
			{
				if (lpStgArea->pcaUnitData[cnt]->bActive &&
					lpStgArea->pcaUnitData[cnt]->dwExclusiveNum == rsHARDCORE_EVENT_FLAG &&
					lpStgArea->pcaUnitData[cnt]->psModelAnimation->iType != ANIMATIONTYPE_Die)
				{
					lpStgArea->pcaUnitData[cnt]->sCharacterData.sHP.sMin = 0;
					lpStgArea->pcaUnitData[cnt]->SetMotionFromCode(ANIMATIONTYPE_Die);

					if (!sHCoreEvent[rsHardCoreEvent_Count].hCoreMonster1.szName[0])
					{
						lpStgArea->pcaUnitData[cnt]->iBellatraRoom = (sinPM1 | sin04);

						if (rsPushKillMonster(lpStgArea->pcaUnitData[cnt], 0, lpStgArea->pcaUnitData[cnt]->pcMap) == FALSE)
							CreatePresentItem(lpStgArea->pcaUnitData[cnt]->iBellatraRoom,
								lpStgArea->pcaUnitData[cnt]->pcMap,
								lpStgArea->pcaUnitData[cnt]->pX,
								lpStgArea->pcaUnitData[cnt]->pY,
								lpStgArea->pcaUnitData[cnt]->pZ, 3);
					}
				}
			}
		}

		if (sHCoreEvent[rsHardCoreEvent_Count].State > 0)
		{
			total = 0;

			for (int i = 0; i < PLAYERS_MAX; i++)
			{
				User *u = USERSDATA + i;

				if (u && u->dwExclusiveNum == rsHARDCORE_EVENT_FLAG)
				{
					if (rsCheckHardCoreEventArea(u->sPosition.iX, u->sPosition.iY, u->sPosition.iZ) == TRUE)
					{
						if (total < u->iBellatraScore)
							total = u->iBellatraScore;
					}
				}
			}

			if (total < sHCoreEvent[rsHardCoreEvent_Count].State)
				rsHardCoreEvent_Count++;
		}

		if (!sHCoreEvent[rsHardCoreEvent_Count].hCoreMonster1.szName[0])
		{
			switch (rand() % 3)
			{
			case 0:
				sHCoreEvent = sHCoreEvent_Bellatra[0];
				break;
			case 1:
				sHCoreEvent = sHCoreEvent_Bellatra[1];
				break;
			case 2:
				sHCoreEvent = sHCoreEvent_Bellatra[2];
				break;
			}

			rsHardCoreEvent_Count = 0;
			memcpy(&hCoreMonsters[0], &sHCoreEvent[rsHardCoreEvent_Count].hCoreMonster1, sizeof(_sHCORE_MONSTER));
			memcpy(&hCoreMonsters[1], &sHCoreEvent[rsHardCoreEvent_Count].hCoreMonster2, sizeof(_sHCORE_MONSTER));
			memcpy(&hCoreMonsters[2], &sHCoreEvent[rsHardCoreEvent_Count].hCoreMonster3, sizeof(_sHCORE_MONSTER));
			memcpy(&hCoreMonsters[3], &sHCoreEvent[rsHardCoreEvent_Count].hCoreMonster4, sizeof(_sHCORE_MONSTER));
			memcpy(&hCoreMonsters[4], &sHCoreEvent[rsHardCoreEvent_Count].hCoreMonsterBoss, sizeof(_sHCORE_MONSTER));

			rsHardCoreEvent_MonsterMax = sHCoreEvent[rsHardCoreEvent_Count].MaxMonster;
			ZeroMemory(rsHardCoreEvent_OpenBoss, sizeof(int) * 8);
			ZeroMemory(rsHardCoreEvent_OpenCount, sizeof(int) * 8);
			rsHardCoreBoss = sHCoreEvent[rsHardCoreEvent_Count].hCoreMonsterBoss.lpCharInfo;

			dwHardCoreEvent_OutTime = SERVER_GAMETIME + 30000;
			rsEventTicketCount = 0;
			rsEventTicketLevel[0] = 0;
			rsEventTicketLevel[1] = 0;
			rsEventTicketLevel[2] = 0;
			rsEventTicketLevel[3] = 0;

			TransChatMessage.code = smTRANSCODE_MESSAGEBOX;
			TransChatMessage.dwIP = 0;
			TransChatMessage.dwObjectSerial = 0;

			total2 = 0;
			totalScore = 0;

			for (int i = 0; i < PLAYERS_MAX; i++)
			{
				User * u = USERSDATA + i;

				if (u && u->dwExclusiveNum == rsHARDCORE_EVENT_FLAG)
				{
					if (rsCheckHardCoreEventArea(u->sPosition.iX, u->sPosition.iY, u->sPosition.iZ) == TRUE)
					{
						totalScore += u->iBellatraScore;
						total2++;
					}
				}
			}

			ZeroMemory(&TransSodResult, sizeof(TRANS_SOD_RESULT));

			for (int i = 0; i < PLAYERS_MAX; i++)
			{
				User * u = USERSDATA + i;

				if (u && u->dwExclusiveNum == rsHARDCORE_EVENT_FLAG)
				{
					if (rsCheckHardCoreEventArea(u->sPosition.iX, u->sPosition.iY, u->sPosition.iZ) == TRUE)
					{
						money = u->iBellatraScore - ((u->iBellatraScore * rsSOD_Tax) / 100);

						ZeroMemory(&smTransCommand, sizeof(smTRANS_COMMAND));
						smTransCommand.code = smTRANSCODE_SOD_INFOMATION;
						smTransCommand.size = sizeof(smTRANS_COMMAND);
						smTransCommand.WParam = 4;
						smTransCommand.LParam = rsHardCoreEvent_Count;
						smTransCommand.SParam = 100;
						smTransCommand.EParam = money;

						SENDPACKET(u, &smTransCommand);

						if (TransSodResult.ResultCount < SOD_RESULT_MAX && !u->bCloak)
						{
							TransSodResult.Result[TransSodResult.ResultCount].lpPlayInfo = u;
							lstrcpy(TransSodResult.Result[TransSodResult.ResultCount].szName, u->sCharacterData.szName);
							TransSodResult.Result[TransSodResult.ResultCount].Class = u->sCharacterData.iClanID;
							TransSodResult.Result[TransSodResult.ResultCount].JobCode = u->sCharacterData.iClass;
							TransSodResult.Result[TransSodResult.ResultCount].Score = u->iBellatraScore;
							TransSodResult.Result[TransSodResult.ResultCount].Monster = u->iBellatraKills;
							TransSodResult.ResultCount++;
						}

						mcnt = money;

						if (mcnt)
							SERVERCHARACTER->GiveGold(u, mcnt);

						rsSend_ResultSOD(u, u->iBellatraScore, u->iBellatraKills, totalScore, total2, rsHardCoreEvent_TotalUser, rsSoD_StartCode);

						if (u->iBellatraScore >= 400000)
						{
							smTransCommand.size = sizeof(smTRANS_COMMAND);
							smTransCommand.code = smTRANSCODE_SET_BLACKLIST;
							smTransCommand.WParam = 21000;
							smTransCommand.SParam = u->dwExclusiveNum;
							smTransCommand.LParam = u->iBellatraScore;
							rsSendDataServer(u, &smTransCommand);
						}
					}
					else
						rsSend_ResultSOD(u, 0, u->iBellatraKills, 0, 0, rsHardCoreEvent_TotalUser, rsSoD_StartCode);
				}
			}

			TransSodResult.code = smTRANSCODE_SOD_RESULT;
			TransSodResult.size = sizeof(TRANS_SOD_RESULT) - ((SOD_RESULT_MAX - TransSodResult.ResultCount) * sizeof(_SOD_RESULT));
			TransSodResult.dwGameCode = rsSoD_StartCode;
			TransSodResult.dwGameTime = (DWORD)SERVER_LOCATIME;
			TransSodResult.dwDisplayMode = TRUE;

			for (cnt = 0; cnt < TransSodResult.ResultCount; cnt++)
			{
				if (TransSodResult.Result[cnt].lpPlayInfo)
					SENDPACKET(TransSodResult.Result[cnt].lpPlayInfo, &TransSodResult);
			}
			TransSodResult.dwDisplayMode = FALSE;

			return TRUE;
		}

		memcpy(&hCoreMonsters[0], &sHCoreEvent[rsHardCoreEvent_Count].hCoreMonster1, sizeof(_sHCORE_MONSTER));
		memcpy(&hCoreMonsters[1], &sHCoreEvent[rsHardCoreEvent_Count].hCoreMonster2, sizeof(_sHCORE_MONSTER));
		memcpy(&hCoreMonsters[2], &sHCoreEvent[rsHardCoreEvent_Count].hCoreMonster3, sizeof(_sHCORE_MONSTER));
		memcpy(&hCoreMonsters[3], &sHCoreEvent[rsHardCoreEvent_Count].hCoreMonster4, sizeof(_sHCORE_MONSTER));
		memcpy(&hCoreMonsters[4], &sHCoreEvent[rsHardCoreEvent_Count].hCoreMonsterBoss, sizeof(_sHCORE_MONSTER));

		rsHardCoreEvent_MonsterMax = sHCoreEvent[rsHardCoreEvent_Count].MaxMonster;

		ZeroMemory(rsHardCoreEvent_OpenBoss, sizeof(int) * 8);
		ZeroMemory(rsHardCoreEvent_OpenCount, sizeof(int) * 8);

		rsHardCoreBoss = sHCoreEvent[rsHardCoreEvent_Count].hCoreMonsterBoss.lpCharInfo;

		if (hCoreMonsters[0].lpCharInfo)
		{
			dwSoD_DelayTime = SERVER_GAMETIME + sHCoreEvent[rsHardCoreEvent_Count].DelayTime * 1000;

			ZeroMemory(&smTransCommand2, sizeof(smTRANS_COMMAND));
			smTransCommand2.code = smTRANSCODE_SOD_INFOMATION;
			smTransCommand2.size = sizeof(smTRANS_COMMAND);
			smTransCommand2.WParam = 1;
			smTransCommand2.LParam = rsHardCoreEvent_Count;
			smTransCommand2.SParam = -1;

			ZeroMemory(&smTransCommand, sizeof(smTRANS_COMMAND));
			smTransCommand.code = smTRANSCODE_SOD_INFOMATION;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.WParam = 3;
			smTransCommand.LParam = rsHardCoreEvent_Count;
			smTransCommand.SParam = -1;

			rsSetSodTeamRank();

			if (rsHardCoreEvent_Count == 3 || rsHardCoreEvent_Count == 6)
			{
				for (int i = 0; i < PLAYERS_MAX; i++)
				{
					User * u = USERSDATA + i;

					if (u && u->dwExclusiveNum == rsHARDCORE_EVENT_FLAG)
					{
						if (rsCheckHardCoreEventArea(u->sPosition.iX, u->sPosition.iY, u->sPosition.iZ) == TRUE)
						{
							if (u->sBellatraRoomID == rsSodTeamRank[0] || (u->sBellatraRoomID == rsSodTeamRank[1] &&
								rsHardCoreEvent_Count == 3))
							{
								if (u->sBellatraRoomID == rsSodTeamRank[0])
									smTransCommand2.SParam = rsSod_RoundRoomTable[0][rsHardCoreEvent_Count];
								else
									smTransCommand2.SParam = rsSod_RoundRoomTable[2][rsHardCoreEvent_Count];

								SENDPACKET(u, &smTransCommand2);
							}
							else
							{
								SENDPACKET(u, &smTransCommand);
								rsSend_ResultSOD(u, -u->iBellatraScore, u->iBellatraKills, 0, 0, rsHardCoreEvent_TotalUser, rsSoD_StartCode);
								money = u->iBellatraScore - ((u->iBellatraScore * rsSOD_Tax) / 100);

								SERVERCHARACTER->GiveGold(u, money);

								u->dwExclusiveNum = 0;
								u->iBellatraScore = 0;
								u->iBellatraKills = 0;

								rnk = 1;

								if (u->sBellatraRoomID == rsSodTeamRank[1])
									rnk = 2;
								if (u->sBellatraRoomID == rsSodTeamRank[2])
									rnk = 3;
								if (u->sBellatraRoomID == rsSodTeamRank[3])
									rnk = 4;
								wsprintf(TransChatMessage2.szMessage, "Your team lost!(Rank: %d) Won %d Gold!", rnk, money);

								TransChatMessage2.code = smTRANSCODE_MESSAGEBOX;
								TransChatMessage2.size = 32 + lstrlen(TransChatMessage2.szMessage);
								TransChatMessage2.dwIP = 0;
								TransChatMessage2.dwObjectSerial = 0;

								SENDPACKET(u, &TransChatMessage2);
							}
						}
					}
				}
				smTransCommand2.size = 0;
			}
		}

		total = 0;

		for (int i = 0; i < PLAYERS_MAX; i++)
		{
			User * u = USERSDATA + i;

			if (u && u->dwExclusiveNum == rsHARDCORE_EVENT_FLAG)
			{
				if (rsCheckHardCoreEventArea(u->sPosition.iX, u->sPosition.iY, u->sPosition.iZ) == TRUE)
				{
					if (smTransCommand2.size)
						SENDPACKET(u, &smTransCommand2);
					total++;
				}
				else
				{
					u->dwExclusiveNum = 0;
					rsSend_ResultSOD(u, 0, u->iBellatraKills, 0, 0, rsHardCoreEvent_TotalUser, rsSoD_StartCode);
				}
			}
		}

		rsHardCoreEvent_Count++;

		return FALSE;
	}

	if (!rsHardCoreEvent_Count)
	{
		if (dwHardCoreEvent_OutTime && dwHardCoreEvent_OutTime < SERVER_GAMETIME)
		{
			for (int i = 0; i < PLAYERS_MAX; i++)
			{
				User * u = USERSDATA + i;

				if (u && u->dwExclusiveNum == rsHARDCORE_EVENT_FLAG)
				{
					u->dwExclusiveNum = 0;
					u->iBellatraScore = 0;
					u->iBellatraKills = 0;

					if (rsCheckHardCoreEventArea(u->sPosition.iX, u->sPosition.iY, u->sPosition.iZ) == TRUE)
					{
						auto pcMap = SERVERMAP->GetMap(MAPID_NaviskoTown);

						if (pcMap)
						{
							smTransCommand.WParam = MAPID_NaviskoTown;
							smTransCommand.code = smTRANSCODE_WARPFIELD;
							smTransCommand.size = sizeof(smTRANS_COMMAND);
							smTransCommand.SParam = pcMap->pcBaseMap->sPositionCenter.iX;
							smTransCommand.LParam = pcMap->pcBaseMap->sPositionCenter.iZ;

							SENDPACKET(u, &smTransCommand);
						}
					}
				}
			}
			rsHardCoreEvent_TotalUser = 0;
			dwHardCoreEvent_OutTime = 0;
			if (!rsHardCoreEventMode)
				rsHardCoreEventTimeOver = TRUE;
			rsSoD_StartCode = (ServerNameCode << 24) | ((SERVER_LOCATIME) & 0xFFFFFF);
			ZeroMemory(rsSodTeamScore, sizeof(int) * 4);
			ZeroMemory(rsSodUser, sizeof(sSOD_USER)*rsSOD_USER_MAX);
			rsSodUserCount = 0;
		}

		return FALSE;
	}

	if (rsTransSodTime < SERVER_GAMETIME)
	{
		rsTransUpdateSod(0);
		rsTransSodTime = SERVER_GAMETIME + rsSOD_UPDATE_TIME;
	}

	int	RndCnt;
	int	MonMax[8];
	int	SodRoundCount = rsHardCoreEvent_Count - 1;

	if (SodRoundCount<0 || SodRoundCount >= 8 || dwSoD_DelayTime>SERVER_GAMETIME)
		return FALSE;

	ZeroMemory(MonMax, sizeof(int) * 8);

	for (cnt = 0; cnt < MAX_ALIVEMONSTERS; cnt++)
	{
		if (lpStgArea->pcaUnitData[cnt])
		{
			if (lpStgArea->pcaUnitData[cnt]->bActive && lpStgArea->pcaUnitData[cnt]->dwExclusiveNum == rsHARDCORE_EVENT_FLAG && lpStgArea->pcaUnitData[cnt]->psModelAnimation->iType != ANIMATIONTYPE_Die)
			{
				if (lpStgArea->pcaUnitData[cnt]->iBellatraRoom >= 0 && lpStgArea->pcaUnitData[cnt]->iBellatraRoom < 8)
					MonMax[lpStgArea->pcaUnitData[cnt]->iBellatraRoom]++;
			}
		}
	}

	for (RndCnt = rsSod_RoundTable[SodRoundCount][0]; RndCnt < rsSod_RoundTable[SodRoundCount][1]; RndCnt++)
	{
		mcnt = MonMax[RndCnt];

		if (mcnt > rsHardCoreEvent_MonsterMax)
			continue;

		if (rsHardCoreBoss && !rsHardCoreEvent_OpenBoss[RndCnt] && rsHardCoreEvent_OpenCount[RndCnt] > (rsHardCoreEvent_MonsterMax - 10))
		{
			memcpy(&lpStgCharInfo->sCharacterData, rsHardCoreBoss, sizeof(CharacterData));
			rsHardCoreEvent_OpenBoss[RndCnt] ++;
		}
		else
		{
			cnt = rand() % 100;
			if (hCoreMonsters[0].lpCharInfo && cnt <= hCoreMonsters[0].perCount)
				memcpy(&lpStgCharInfo->sCharacterData, hCoreMonsters[0].lpCharInfo, sizeof(CharacterData));
			else if (hCoreMonsters[1].lpCharInfo && cnt <= hCoreMonsters[1].perCount)
				memcpy(&lpStgCharInfo->sCharacterData, hCoreMonsters[1].lpCharInfo, sizeof(CharacterData));
			else if (hCoreMonsters[2].lpCharInfo && cnt <= hCoreMonsters[2].perCount)
				memcpy(&lpStgCharInfo->sCharacterData, hCoreMonsters[2].lpCharInfo, sizeof(CharacterData));
			else if (hCoreMonsters[3].lpCharInfo && cnt <= hCoreMonsters[3].perCount)
				memcpy(&lpStgCharInfo->sCharacterData, hCoreMonsters[3].lpCharInfo, sizeof(CharacterData));
		}

		rsGetHardCoreEventOpenMonsterPos(&x, &y, &z, RndCnt);

		lpStgArea->bForceCreateMonster = TRUE;

		lpChar = SERVERMAP->CreateUnit(lpStgArea, &lpStgCharInfo->sCharacterData);
		if (lpChar)
		{
			lpChar->pX = x;
			lpChar->pY = y;
			lpChar->pZ = z;
			lpChar->SetMotionFromCode(ANIMATIONTYPE_Idle);
			lpChar->TargetMoveCount = 0;
			lpChar->dwExclusiveNum = rsHARDCORE_EVENT_FLAG;
			lpChar->iBellatraRoom = RndCnt;

			lpChar->sSpawnPosition.iX = rsHardCoreEventOpenPos[RndCnt][2].x*fONE;
			lpChar->sSpawnPosition.iY = rsHardCoreEventOpenPos[RndCnt][2].y*fONE;
			lpChar->sSpawnPosition.iZ = rsHardCoreEventOpenPos[RndCnt][2].z*fONE;
			lpChar->iLureDistance = (12 * 64 * 12 * 64);

			lpChar->sCharacterData.iSight = 800 * 800;

			rsHardCoreEvent_OpenCount[RndCnt]++;

			continue;
		}
	}

	return FALSE;
}

DWORD	dwSodRealScore_Time[5] = { 0,0,0,0,0 };

//SoD ²é¿´SOD ·ÖÊý
TRANS_SOD_RESULT *rsSod_GetRealTimeScore(User *lpPlayInfo, int TeamNum)
{
	int rc;
	int	Team;

	Team = TeamNum;
	if (Team > 4 || Team < 0)
		Team = 0;

	if ((dwSodRealScore_Time[Team] + 1000 * 60 * 10) < SERVER_GAMETIME)
	{
		ZeroMemory(&TransSodResult_RealTime[Team], sizeof(TRANS_SOD_RESULT));

		for (int i = 0; i < PLAYERS_MAX; i++)
		{
			User * u = USERSDATA + i;

			if (u && u->dwExclusiveNum == rsHARDCORE_EVENT_FLAG && (Team == 0 || (u->sBellatraRoomID + 1) == Team))
			{
				if (!u->bCloak && rsCheckHardCoreEventArea(u->sPosition.iX, u->sPosition.iY, u->sPosition.iZ) == TRUE)
				{
					if (TransSodResult_RealTime[Team].ResultCount < SOD_RESULT_MAX)
					{
						rc = TransSodResult_RealTime[Team].ResultCount;
						TransSodResult_RealTime[Team].Result[rc].lpPlayInfo = u;
						lstrcpy(TransSodResult_RealTime[Team].Result[rc].szName, u->sCharacterData.szName);

						TransSodResult_RealTime[Team].Result[rc].Class = u->sCharacterData.iClanID;
						TransSodResult_RealTime[Team].Result[rc].JobCode = u->sCharacterData.iClass;
						TransSodResult_RealTime[Team].Result[rc].Score = u->iBellatraScore;
						TransSodResult_RealTime[Team].Result[rc].Monster = u->iBellatraKills;
						TransSodResult_RealTime[Team].ResultCount++;
					}
				}
			}
		}

		dwSodRealScore_Time[Team] = SERVER_GAMETIME;
	}

	if (TransSodResult_RealTime[Team].ResultCount == 0)
		return NULL;

	TransSodResult_RealTime[Team].code = smTRANSCODE_SOD_RESULT2;
	TransSodResult_RealTime[Team].size = sizeof(TRANS_SOD_RESULT) - ((SOD_RESULT_MAX - TransSodResult_RealTime[Team].ResultCount) * sizeof(_SOD_RESULT));
	TransSodResult_RealTime[Team].dwGameCode = rsSoD_StartCode;
	TransSodResult_RealTime[Team].dwGameTime = (DWORD)SERVER_LOCATIME;
	TransSodResult_RealTime[Team].dwDisplayMode = TRUE;

	SENDPACKET(lpPlayInfo, &TransSodResult_RealTime[Team]);

	return &TransSodResult_RealTime[Team];
}
int	rsTransUpdateSod(User *lpPlayInfo)
{
	int cnt, SndCount;
	smTRANS_COMMAND_SOD	smTransCommand;

	ZeroMemory(&smTransCommand, sizeof(smTRANS_COMMAND_SOD));
	smTransCommand.smTransCommand.size = sizeof(smTRANS_COMMAND_SOD);
	smTransCommand.smTransCommand.code = smTRANSCODE_SOD_INFOMATION;
	smTransCommand.smTransCommand.WParam = 2;
	smTransCommand.smTransCommand.SParam = rsHardCoreEvent_Count;

	smTransCommand.TeamScore[0] = rsSodTeamScore[0];
	smTransCommand.TeamScore[1] = rsSodTeamScore[1];
	smTransCommand.TeamScore[2] = rsSodTeamScore[2];
	smTransCommand.TeamScore[3] = rsSodTeamScore[3];

	SndCount = 0;

	if (lpPlayInfo)
	{
		if (lpPlayInfo && lpPlayInfo->dwExclusiveNum == rsHARDCORE_EVENT_FLAG)
		{
			smTransCommand.MyScore = lpPlayInfo->iBellatraScore;
			smTransCommand.MyTeam = lpPlayInfo->sBellatraRoomID;
			smTransCommand.smTransCommand.LParam = 1;

			SENDPACKET(lpPlayInfo, &smTransCommand);
			SndCount++;
		}
	}
	else
	{
		for (cnt = 0; cnt < rsSodUserCount; cnt++)
		{
			if (rsSodUser[cnt].lpPlayInfo &&
				rsSodUser[cnt].lpPlayInfo->dwExclusiveNum == rsHARDCORE_EVENT_FLAG &&
				rsSodUser[cnt].lpPlayInfo->dwConnectCount == rsSodUser[cnt].dwConnCode)
			{
				smTransCommand.MyScore = rsSodUser[cnt].lpPlayInfo->iBellatraScore;
				smTransCommand.MyTeam = rsSodUser[cnt].lpPlayInfo->sBellatraRoomID;

				SENDPACKET(rsSodUser[cnt].lpPlayInfo, &smTransCommand);
				SndCount++;
			}
		}
	}


	return SndCount;
}
int rsShowHardCoreEventScore(User *lpPlayInfo)
{
	lpPlayInfo->dwEventTime = SERVER_GAMETIME;

	rsTransUpdateSod(lpPlayInfo);

	return TRUE;
}

int rsShowHardCoreEventScore2(User *lpPlayInfo, Unit *lpChar, int Score)
{
	TRANS_CHATMESSAGE	TransChatMessage;

	wsprintf(TransChatMessage.szMessage, "> %s killed (%d points received)", lpChar->sCharacterData.szName, Score);
	TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
	TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
	TransChatMessage.dwIP = 3;
	TransChatMessage.dwObjectSerial = 0;

	SENDPACKET(lpPlayInfo, &TransChatMessage);

	return TRUE;
}

int rsSoD_CatchItem_SD201(User *lpPlayInfo, int StagePos, Map	*lpStgArea)
{
	int cnt;
	int	Damage;
	int x, z;

	for (cnt = 0; cnt < MAX_ALIVEMONSTERS; cnt++)
	{
		if (lpStgArea->pcaUnitData[cnt])
		{
			if (lpStgArea->pcaUnitData[cnt]->bActive &&
				lpStgArea->pcaUnitData[cnt]->dwExclusiveNum == rsHARDCORE_EVENT_FLAG &&
				lpStgArea->pcaUnitData[cnt]->psModelAnimation->iType != ANIMATIONTYPE_Die &&
				lpStgArea->pcaUnitData[cnt]->sCharacterData.sGlow != MONSTER_CLASS_BOSS)
			{
				x = lpStgArea->pcaUnitData[cnt]->pX >> FLOATNS;
				z = lpStgArea->pcaUnitData[cnt]->pZ >> FLOATNS;

				if (x > rsHardCoreEventOpenPos[StagePos][0].x && x<rsHardCoreEventOpenPos[StagePos][1].x && z>rsHardCoreEventOpenPos[StagePos][1].z && z < rsHardCoreEventOpenPos[StagePos][0].z)
				{
					Damage = lpStgArea->pcaUnitData[cnt]->sCharacterData.sHP.sMax / 3;
					lpStgArea->pcaUnitData[cnt]->sCharacterData.sHP.sMin -= Damage;

					if (lpStgArea->pcaUnitData[cnt]->sCharacterData.sHP.sMin <= 0)
						lpStgArea->pcaUnitData[cnt]->sCharacterData.sHP.sMin = 1;

					lpStgArea->pcaUnitData[cnt]->SetMotionFromCode(ANIMATIONTYPE_Flinch);
				}
			}
		}
	}

	return TRUE;
}
int rsSoD_CatchItem_SD202(User *lpPlayInfo, int StagePos, Map	*lpStgArea)
{
	int cnt;
	int x, z;

	for (cnt = 0; cnt < MAX_ALIVEMONSTERS; cnt++)
	{
		if (lpStgArea->pcaUnitData[cnt])
		{
			if (lpStgArea->pcaUnitData[cnt]->bActive && lpStgArea->pcaUnitData[cnt]->dwExclusiveNum == rsHARDCORE_EVENT_FLAG && lpStgArea->pcaUnitData[cnt]->psModelAnimation->iType != ANIMATIONTYPE_Die)
			{
				x = lpStgArea->pcaUnitData[cnt]->pX >> FLOATNS;
				z = lpStgArea->pcaUnitData[cnt]->pZ >> FLOATNS;

				if (x > rsHardCoreEventOpenPos[StagePos][0].x && x<rsHardCoreEventOpenPos[StagePos][1].x && z>rsHardCoreEventOpenPos[StagePos][1].z && z < rsHardCoreEventOpenPos[StagePos][0].z)
				{
					lpStgArea->pcaUnitData[cnt]->SetMotionFromCode(ANIMATIONTYPE_Flinch);
					lpStgArea->pcaUnitData[cnt]->iStunTimeLeft = 16 * 10;
				}
			}
		}
	}

	return TRUE;
}
int rsSoD_CatchItem_SD203(User *lpPlayInfo, int StagePos, Map	*lpStgArea)
{
	int cnt;
	int x, z;

	for (cnt = 0; cnt < MAX_ALIVEMONSTERS; cnt++)
	{
		if (lpStgArea->pcaUnitData[cnt])
		{
			if (lpStgArea->pcaUnitData[cnt]->bActive && lpStgArea->pcaUnitData[cnt]->dwExclusiveNum == rsHARDCORE_EVENT_FLAG && lpStgArea->pcaUnitData[cnt]->psModelAnimation->iType != ANIMATIONTYPE_Die)
			{
				x = lpStgArea->pcaUnitData[cnt]->pX >> FLOATNS;
				z = lpStgArea->pcaUnitData[cnt]->pZ >> FLOATNS;

				if (x > rsHardCoreEventOpenPos[StagePos][0].x && x<rsHardCoreEventOpenPos[StagePos][1].x && z>rsHardCoreEventOpenPos[StagePos][1].z && z < rsHardCoreEventOpenPos[StagePos][0].z)
				{
					lpStgArea->pcaUnitData[cnt]->SetMotionFromCode(ANIMATIONTYPE_Flinch);
					lpStgArea->pcaUnitData[cnt]->PlaySlowCount = 16 * 15;
					lpStgArea->pcaUnitData[cnt]->PlaySlowSpeed = 0;
				}
			}
		}
	}


	return TRUE;
}
int rsSoD_CatchItem_SD204(User *lpPlayInfo, int StagePos, Map	*lpStgArea)
{
	int cnt;
	int x, z;
	int RndCnt = -1;
	CharacterData	*lpCharInfo = 0;
	//UnitInfo	*lpMonInfo;

	CharacterData	*lpCharInfoBoss = 0;
	//UnitInfo	*lpMonInfoBoss;

	int Param;

	auto pMonstTable = SERVERUNIT->GetMonsterTable();

	for (auto & pc : pMonstTable)
	{
		if (pc->iMonsterEffectID == MONSTEREFFECTID_RABIE && pc->szName[0] != ' ')
		{
			if (!lpCharInfo)
			{
				lpCharInfo = pc;
			}
		}
		if (pc->iMonsterEffectID == snCHAR_SOUND_MUTANTRABIE && pc->sGlow == MONSTER_CLASS_BOSS)
		{
			if (!lpCharInfoBoss)
			{
				lpCharInfoBoss = pc;
			}
		}
	}

	if (!lpCharInfo)
		return FALSE;

	for (cnt = 0; cnt < MAX_ALIVEMONSTERS; cnt++)
	{
		if (lpStgArea->pcaUnitData[cnt])
		{
			if (lpStgArea->pcaUnitData[cnt]->bActive &&
				lpStgArea->pcaUnitData[cnt]->dwExclusiveNum == rsHARDCORE_EVENT_FLAG &&
				lpStgArea->pcaUnitData[cnt]->psModelAnimation->iType != ANIMATIONTYPE_Die &&
				lpStgArea->pcaUnitData[cnt]->sCharacterData.sGlow != MONSTER_CLASS_BOSS)
			{
				x = lpStgArea->pcaUnitData[cnt]->pX >> FLOATNS;
				z = lpStgArea->pcaUnitData[cnt]->pZ >> FLOATNS;

				if (x > rsHardCoreEventOpenPos[StagePos][0].x &&
					x < rsHardCoreEventOpenPos[StagePos][1].x &&
					z > rsHardCoreEventOpenPos[StagePos][1].z &&
					z < rsHardCoreEventOpenPos[StagePos][0].z)
				{
					RndCnt = lpStgArea->pcaUnitData[cnt]->iBellatraRoom;

					if ((rand() % 2) == 0)
					{
						Param = lpStgArea->pcaUnitData[cnt]->iBellatraRoom;

						SERVERUNIT->UnitSwapper(lpStgArea->pcaUnitData[cnt], lpCharInfo, lpCharInfo->psUnitInfo);

						lpStgArea->pcaUnitData[cnt]->dwExclusiveNum = rsHARDCORE_EVENT_FLAG;
						lpStgArea->pcaUnitData[cnt]->iBellatraRoom = Param;

						lpStgArea->pcaUnitData[cnt]->iLureDistance = (12 * 64 * 12 * 64);
						lpStgArea->pcaUnitData[cnt]->sCharacterData.iSight = 800 * 800;
					}

				}
			}
		}
	}

	if (lpCharInfoBoss || RndCnt < 0)
	{
		Unit *lpChar;

		lpStgArea->bForceCreateMonster = TRUE;
		lpChar = SERVERMAP->CreateUnit(lpStgArea, lpCharInfoBoss);

		if (lpChar)
		{
			lpChar->pX = rsHardCoreEventOpenPos[RndCnt][2].x*fONE;
			lpChar->pY = rsHardCoreEventOpenPos[RndCnt][2].y*fONE;
			lpChar->pZ = rsHardCoreEventOpenPos[RndCnt][2].z*fONE;

			lpChar->SetMotionFromCode(ANIMATIONTYPE_Idle);
			lpChar->TargetMoveCount = 0;
			lpChar->dwExclusiveNum = rsHARDCORE_EVENT_FLAG;
			lpChar->iBellatraRoom = RndCnt;

			lpChar->sSpawnPosition.iX = rsHardCoreEventOpenPos[RndCnt][2].x*fONE;
			lpChar->sSpawnPosition.iY = rsHardCoreEventOpenPos[RndCnt][2].y*fONE;
			lpChar->sSpawnPosition.iZ = rsHardCoreEventOpenPos[RndCnt][2].z*fONE;
			lpChar->iLureDistance = (12 * 64 * 12 * 64);

			lpChar->sCharacterData.iSight = 800 * 800;

			SERVERUNIT->ProcessPacketEffectWarp(lpPlayInfo, lpChar->sPosition);
		}
	}

	return TRUE;
}
int rsSoD_CatchItem_SD205(User *lpPlayInfo, int StagePos, Map	*lpStgArea, DWORD MonSndCode, int Level)
{
	int x, y, z;
	CharacterData	*lpCharInfo = 0;
	//UnitInfo	*lpMonInfo;

	auto pMonstTable = SERVERUNIT->GetMonsterTable();

	for (auto & pc : pMonstTable)
	{
		if (pc->iMonsterEffectID == MonSndCode && (Level == 0 || pc->iLevel == Level))
		{
			if (!lpCharInfo)
			{
				lpCharInfo = pc;
				break;
			}
		}
	}

	if (!lpCharInfo || StagePos < 0)
		return FALSE;

	Unit				*lpChar;

	x = rsHardCoreEventOpenPos[StagePos][2].x*fONE;
	y = rsHardCoreEventOpenPos[StagePos][2].y*fONE;
	z = rsHardCoreEventOpenPos[StagePos][2].z*fONE;

	lpStgArea->bForceCreateMonster = TRUE;
	lpChar = SERVERMAP->CreateUnit(lpStgArea, lpCharInfo);

	if (lpChar)
	{
		lpChar->pcOwner = lpPlayInfo;
		lpChar->sUnitInfo.dwHashCharacterName = 0;
		lpChar->sCharacterData.iMonsterType = MONSTERTYPE_Friendly;
		lstrcpy(lpChar->sCharacterData.Pet.szOwnerName, lpPlayInfo->sCharacterData.szName);
		lpChar->sCharacterData.iOwnerID = lpPlayInfo->iID;
		lpChar->dwLastUpdateTime = SERVER_GAMETIME + 4 * 60 * 1000;

		lpChar->pX = x;
		lpChar->pY = y;
		lpChar->pZ = z;

		SERVERUNIT->ProcessPacketEffectWarp(lpPlayInfo, lpChar->sPosition);
	}

	return TRUE;
}
int rsSoD_CatchItem_SD207(User *lpPlayInfo, int StagePos, Map	*lpStgArea)
{
	int team = lpPlayInfo->sBellatraRoomID;

	if (team < 0 || team >= 4)
		return FALSE;

	if (lpPlayInfo->dwExclusiveNum == rsHARDCORE_EVENT_FLAG && rsCheckHardCoreEventArea(lpPlayInfo->sPosition.iX, lpPlayInfo->sPosition.iY, lpPlayInfo->sPosition.iZ) == TRUE)
	{
		lpPlayInfo->iBellatraScore += 5000;
		rsSodTeamScore[team] += 5000;
		rsTransUpdateSod(lpPlayInfo);
	}

	return TRUE;
}
int	rsSendCommandSodUserTeam(User *lpPlayInfo, smTRANS_COMMAND	*lpTransCommandEx)
{
	int SndCnt = 0;

	for (int i = 0; i < PLAYERS_MAX; i++)
	{
		User * u = USERSDATA + i;

		if (u && u->iID)
		{
			if (u->dwExclusiveNum == rsHARDCORE_EVENT_FLAG && u->sBellatraRoomID == lpPlayInfo->sBellatraRoomID &&
				rsCheckHardCoreEventArea(u->sPosition.iX, u->sPosition.iY, u->sPosition.iZ) == TRUE)
			{
				SENDPACKET(u, &lpTransCommandEx);
				SndCnt++;
			}
		}
	}

	return TRUE;
}
int	rsSoD_CatchItem(DWORD dwItemCode, User *lpPlayInfo)
{
	int	StagePos;
	int cnt;
	Map	*lpStgArea;
	int x, z;
	smTRANS_COMMAND	smTransCommand;

	StagePos = -1;

	x = lpPlayInfo->sPosition.iX >> FLOATNS;
	z = lpPlayInfo->sPosition.iZ >> FLOATNS;

	for (cnt = 0; cnt < 7; cnt++)
	{
		if (x > rsHardCoreEventOpenPos[cnt][0].x && x<rsHardCoreEventOpenPos[cnt][1].x && z>rsHardCoreEventOpenPos[cnt][1].z && z < rsHardCoreEventOpenPos[cnt][0].z)
		{
			StagePos = cnt;
			break;
		}
	}
	lpStgArea = SERVERMAP->GetMap(MAPID_Bellatra);

	if (!lpStgArea)
		return FALSE;

	smTransCommand.code = smTRANSCODE_PROCESS_SKILL;;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = SKILL_PLAY_SOD_ITEM;
	smTransCommand.LParam = lpPlayInfo->iID;

	if (StagePos >= 0 && lpStgArea)
	{
		switch (dwItemCode)
		{
		case (sinSD2 | sin01):
			rsSoD_CatchItem_SD201(lpPlayInfo, StagePos, lpStgArea);

			smTransCommand.SParam = 1;
			smTransCommand.EParam = 0;
			rsSendCommandSodUserTeam(lpPlayInfo, &smTransCommand);
			break;

		case (sinSD2 | sin02):
			rsSoD_CatchItem_SD202(lpPlayInfo, StagePos, lpStgArea);

			smTransCommand.SParam = 2;
			smTransCommand.EParam = 0;
			rsSendCommandSodUserTeam(lpPlayInfo, &smTransCommand);
			break;

		case (sinSD2 | sin03):
			rsSoD_CatchItem_SD203(lpPlayInfo, StagePos, lpStgArea);

			smTransCommand.SParam = 3;
			smTransCommand.EParam = 0;
			rsSendCommandSodUserTeam(lpPlayInfo, &smTransCommand);
			break;

		case (sinSD2 | sin04):
			rsSoD_CatchItem_SD204(lpPlayInfo, StagePos, lpStgArea);

			smTransCommand.SParam = 4;
			smTransCommand.EParam = 0;
			rsSendCommandSodUserTeam(lpPlayInfo, &smTransCommand);
			break;

		case (sinSD2 | sin05):
			rsSoD_CatchItem_SD205(lpPlayInfo, StagePos, lpStgArea, snCHAR_SOUND_STYGIANLORD, 85);

			smTransCommand.SParam = 5;
			smTransCommand.EParam = 0;
			rsSendCommandSodUserTeam(lpPlayInfo, &smTransCommand);
			break;

		case (sinSD2 | sin06):
			rsSoD_CatchItem_SD205(lpPlayInfo, StagePos, lpStgArea, snCHAR_SOUND_GUARDIAN_SAINT, 80);

			smTransCommand.SParam = 6;
			smTransCommand.EParam = 0;
			rsSendCommandSodUserTeam(lpPlayInfo, &smTransCommand);
			break;

		case (sinSD2 | sin07):
			rsSoD_CatchItem_SD207(lpPlayInfo, StagePos, lpStgArea);

			smTransCommand.SParam = 7;
			smTransCommand.EParam = 0;

			SENDPACKET(lpPlayInfo, &smTransCommand);
			break;
		}
	}

	return TRUE;
}
int SendOpenEvent(Unit *lpChar, User *lpPlayInfo, int EventFlag)
{
	TRANS_CHATMESSAGE	TransChatMessage;
	int	NpcTeam;
	int	MsgNum = -1;
	int MsgCnt = lpChar->sUnitInfo.iNumMessage;

	NpcTeam = lpChar->sUnitInfo.iBellatraTypeNPC;

	if (NpcTeam <= 0 || NpcTeam > 4)
		return FALSE;

	lpPlayInfo->sBellatraRoomID = NpcTeam - 1;

	TransChatMessage.szMessage[0] = 0;
	TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
	TransChatMessage.dwIP = 0;
	TransChatMessage.dwObjectSerial = lpChar->iID;

	if (!rsHardCoreEventMode)
	{
		if (MsgCnt)
			lstrcpy(TransChatMessage.szMessage, lpChar->sUnitInfo.pszaMessage[5 + rand() % 3]);
		else
			lstrcpy(TransChatMessage.szMessage, "You are not able to enter at this time. Please come back again.");

		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);

		SENDPACKET(lpPlayInfo, &TransChatMessage);

		return TRUE;
	}

	if (lpPlayInfo->sCharacterData.iLevel < 40)
	{
		if (MsgCnt)
			lstrcpy(TransChatMessage.szMessage, lpChar->sUnitInfo.pszaMessage[8]);
		else
			lstrcpy(TransChatMessage.szMessage, "Your skills are not good enough to enter. Please train more and come back later");

		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);

		SENDPACKET(lpPlayInfo, &TransChatMessage);

		rsSod_GetRealTimeScore(lpPlayInfo, NpcTeam);

		if (lpPlayInfo->dwExclusiveNum == 0)
			lpPlayInfo->sBellatraRoomID = NpcTeam - 1;

		return TRUE;
	}

	if ((rsHardCoreEvent_TicketHour != SERVERMAP->GetTime() && (rsHardCoreEvent_TicketHour + 1) != SERVERMAP->GetTime()) || rsEventTicketLevel[NpcTeam - 1] > rsEVENT_TICKET_LEVEL_TOTAL)
	{
		if (MsgCnt)
			lstrcpy(TransChatMessage.szMessage, lpChar->sUnitInfo.pszaMessage[2 + rand() % 3]);
		else
		{
			if ((SERVERMAP->GetTime() & 1) == 0)
				lstrcpy(TransChatMessage.szMessage, "You are not able to enter at this time due to an ongoing event. Please try again early tomorrow.");
			else
				lstrcpy(TransChatMessage.szMessage, "All tickets are sold. Please come back at dawn tomorrow.");
		}

		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);

		SENDPACKET(lpPlayInfo, &TransChatMessage);

		rsSod_GetRealTimeScore(lpPlayInfo, NpcTeam);
		if (lpPlayInfo->dwExclusiveNum == 0)
			lpPlayInfo->sBellatraRoomID = NpcTeam - 1;

		return TRUE;
	}

	if (MsgCnt)
		lstrcpy(TransChatMessage.szMessage, lpChar->sUnitInfo.pszaMessage[0]);
	else
		lstrcpy(TransChatMessage.szMessage, "Tickets for monster super main event are on sale. It will only cost you 100,000 gold!");

	TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);

	SENDPACKET(lpPlayInfo, &TransChatMessage);

	lpPlayInfo->dwExclusiveNum = EventFlag;

	int EventCount = 0;

	for (int i = 0; i < PLAYERS_MAX; i++)
	{
		User * u = USERSDATA + i;

		if (u->iMapID == MAPID_Bellatra)
		{
			if (u->sBellatraRoomID == lpPlayInfo->sBellatraRoomID)
				EventCount++;
		}
	}

	SendOpenCollectMoney(lpPlayInfo, lpPlayInfo->sBellatraRoomID, EventCount);

	return TRUE;
}

int rsEnterHardCoreEvent(User *lpPlayInfo, int Money)
{
	TRANS_CHATMESSAGE	TransChatMessage;
	smTRANS_COMMAND		smTransCommand;

	if (lpPlayInfo->sBellatraRoomID < 0 || lpPlayInfo->sBellatraRoomID >= 4)
		return FALSE;

	if (lpPlayInfo->iGameLevel != GAMELEVEL_None && Money == -1)
		goto skip_enterSOD;

	if (rsEventTicketLevel[lpPlayInfo->sBellatraRoomID] > rsEVENT_TICKET_LEVEL_TOTAL ||
		rsHardCoreEvent_TicketHour > SERVERMAP->GetTime() ||
		(rsHardCoreEvent_TicketHour + 2) < SERVERMAP->GetTime())
	{
		SERVERCHARACTER->GiveGold(lpPlayInfo, Money);

		lstrcpy(TransChatMessage.szMessage, "All tickets are sold out for this event");

		TransChatMessage.code = smTRANSCODE_MESSAGEBOX;
		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
		TransChatMessage.dwIP = 0;
		TransChatMessage.dwObjectSerial = 0;

		SENDPACKET(lpPlayInfo, &TransChatMessage);

		return FALSE;
	}

skip_enterSOD:

	auto pcMap = SERVERMAP->GetMap(MAPID_Bellatra);

	if (pcMap)
	{
		smTransCommand.WParam = pcMap->pcBaseMap->iMapID;
		smTransCommand.code = smTRANSCODE_WARPFIELD;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.SParam = rsHardCoreEventOpenPos[lpPlayInfo->sBellatraRoomID][2].x * fONE;
		smTransCommand.LParam = rsHardCoreEventOpenPos[lpPlayInfo->sBellatraRoomID][2].z * fONE;

		SENDPACKET(lpPlayInfo, &smTransCommand);
		rsEventTicketCount++;
		rsEventTicketLevel[lpPlayInfo->sBellatraRoomID] += lpPlayInfo->sCharacterData.iLevel;
		lpPlayInfo->dwExclusiveNum = rsHARDCORE_EVENT_FLAG;
		lpPlayInfo->iBellatraScore = 0;
		lpPlayInfo->iBellatraKills = 0;
		lpPlayInfo->dwEventTime = SERVER_GAMETIME;

		lpPlayInfo->sPosition.iX = smTransCommand.SParam;
		lpPlayInfo->sPosition.iZ = smTransCommand.LParam;

		rsHardCoreEvent_TotalUser++;

		if (rsSodUserCount < rsSOD_USER_MAX)
		{
			rsSodUser[rsSodUserCount].lpPlayInfo = lpPlayInfo;
			rsSodUser[rsSodUserCount].dwConnCode = lpPlayInfo->dwConnectCount;
			rsSodUserCount++;
		}
	}

	return TRUE;
}
#else

int	rsInitHardCoreEvent()
{
	return TRUE;
}
int rsHardCoreEvent_OpenMonster(Map *lpStgArea, STG_CHAR_INFO *lpStgCharInfo)
{
	return TRUE;
}
int rsShowHardCoreEventScore(User *lpPlayInfo)
{
	return TRUE;
}

#endif

int rsCheckHardCoreEventArea(int x, int y, int z)
{
	int mx, my, mz;

	mx = x >> FLOATNS;
	my = y >> FLOATNS;
	mz = z >> FLOATNS;

	if (y >= rsHardCoreEventOpenPos[0][0].y - 32)
	{
		if (rsHardCoreEventArea[0]<mx && rsHardCoreEventArea[1]>mx && rsHardCoreEventArea[2]<mz && rsHardCoreEventArea[3]>mz)
			return TRUE;
	}

	return FALSE;
}

//SOD Áö¿ª¹øÈ£ ±¸ÇÏ±â
int rsGetSoD_AreaCode(int x, int y, int z)
{
	int mx, my, mz;
	int cnt;

	mx = x >> FLOATNS;
	my = y >> FLOATNS;
	mz = z >> FLOATNS;

	if (y >= rsHardCoreEventOpenPos[0][0].y - 32)
	{
		if (rsHardCoreEventArea[0]<mx && rsHardCoreEventArea[1]>mx && rsHardCoreEventArea[2]<mz && rsHardCoreEventArea[3]>mz)
		{
			for (cnt = 0; cnt < 7; cnt++)
			{
				if (mx > rsHardCoreEventOpenPos[cnt][0].x && mx<rsHardCoreEventOpenPos[cnt][1].x && mz>rsHardCoreEventOpenPos[cnt][1].z && mz < rsHardCoreEventOpenPos[cnt][0].z)
					return cnt;
			}
		}
	}

	return -1;
}

WORD	wLastCheckDay = 0;
WORD	wLastCheckHour = 0;
WORD	wLastCheckMin = 0;

static	int EventBossMonsterFlag = 0;
DWORD	dwEventBossMonterTime = 0;


//»î¶¯¹ÖÎïÊ±¼ä
int EventMonsterTime()
{
	SYSTEMTIME	st;

	int cnt2, cnt3;

	GetLocalTime(&st);

	EventMonster = FALSE;

	rsHardCoreEventMode = FALSE;

	if (st.wDayOfWeek >= 0 && st.wDayOfWeek <= 6)
	{
		if (st.wHour >= 20 && st.wHour < 22)
			rsHardCoreEventMode = TRUE;
	}

	if (rsServerConfig.Event_Cristal)
	{
		if (st.wDayOfWeek != 0 || st.wDayOfWeek != 6)
		{
			if ((st.wHour >= 12 && st.wHour <= 23) || rsServerConfig.Event_Cristal == 2)
				rsCristalEvent = TRUE;
			else
				rsCristalEvent = FALSE;
		}
		else if (st.wDayOfWeek == 0 || st.wDayOfWeek == 6)
			rsCristalEvent = TRUE;
		else
			rsCristalEvent = FALSE;
	}
	else
		rsCristalEvent = FALSE;

	if (!EventBossMonsterFlag && st.wMinute == SERVERMAP->GetBossTimeMin() && (dwEventBossMonterTime + 60 * 1000 * 10) < SERVER_GAMETIME)
	{
		auto pcMapTable = SERVERMAP->GetMapTable();

		for (auto & pcMap : pcMapTable)
		{
			if (pcMap->pcStage && pcMap->sSpawnSetting.iTotalBosses > 0)
			{
				for (cnt2 = 0; cnt2 < pcMap->sSpawnSetting.iTotalBosses; cnt2++)
				{
					for (cnt3 = 0; cnt3 < pcMap->sSpawnSetting.saBoss[cnt2].iBossHours; cnt3++)
					{
						if (st.wHour == pcMap->sSpawnSetting.saBoss[cnt2].caBossHour[cnt3])
						{
							SERVERMAP->SpawnMonsterBoss(pcMap, &pcMap->sSpawnSetting.saBoss[cnt2]);
							break;
						}
					}
				}
			}
		}

		EventBossMonsterFlag = TRUE;
		dwEventBossMonterTime = SERVER_GAMETIME;
	}
	else
	{
		if (EventBossMonsterFlag && st.wMinute != SERVERMAP->GetBossTimeMin())
			EventBossMonsterFlag = 0;
	}

	wLastCheckHour = st.wHour;
	wLastCheckMin = st.wMinute;

	return TRUE;
}

int srInitChar()
{
	int cnt;

	InitPatterns();

	for (cnt = 0; cnt < AUTOPLAYER_MAX; cnt++) 
	{
		Unit *u = UNITSDATA + cnt;

		u->Init();
	}

	return TRUE;
}

int srRemoveChar()
{

	//ÆÐÅÏ¹öÆÛ¸¦ ¸»±âÈ­
	ClosePatterns();

	return TRUE;
}

int rsGetMoney(DWORD dwCode, BOOL Kind)
{
	int Price = 0;

	auto pDefItem = SERVERITEM->FindItemDefByCode(dwCode);

	if (pDefItem)
	{
		Price = pDefItem->sItem.iSalePrice;
	}

	return Price;
}
int rsSendCharInfo(Unit *lpChar, User *lpPlayInfo)
{

	smTRNAS_PLAYERINFO	TransPlayerInfo;

	memcpy(&TransPlayerInfo.sCharacterData, &lpChar->sCharacterData, sizeof(CharacterData));
	TransPlayerInfo.size = sizeof(smTRNAS_PLAYERINFO);
	TransPlayerInfo.code = smTRANSCODE_PLAYERINFO;
	TransPlayerInfo.dwObjectSerial = lpChar->iID;

	TransPlayerInfo.x = lpChar->pX;
	TransPlayerInfo.y = lpChar->pY;
	TransPlayerInfo.z = lpChar->pZ;

	if (lpPlayInfo->iGameLevel == GAMELEVEL_None)
	{
		TransPlayerInfo.sCharacterData.iMinDamage = 1000;
		TransPlayerInfo.sCharacterData.iMaxDamage = 9999;
	}

	SENDPACKET(lpPlayInfo, &TransPlayerInfo);

	return 0;
}


//Ä³¸¯ÅÍ Á¤º¸Àû¾î¼­ µÇµ¹·Á¼­ º¸³¿
int rsSendPlayerInfo(User *lpSndPlayInfo, smTRANS_COMMAND *lpTransCommand)
{
	Unit		*lpChar;
	User	*lpPlayInfo;
	smTRNAS_PLAYERINFO	TransPlayerInfo;

	lpChar = SERVERUNIT->GetUnit(lpTransCommand->WParam);
	if (lpChar) {
		//lpChar->SendCharInfo( lpsmsock );
		rsSendCharInfo(lpChar, lpSndPlayInfo);
		return TRUE;
	}


	//´Ù¸¥ À¯Àúµé
	lpPlayInfo = SERVERUSER->GetUser(lpTransCommand->WParam);
	if (lpPlayInfo && lpPlayInfo->iID && lpSndPlayInfo)
	{
		memcpy(&TransPlayerInfo.sCharacterData, &lpPlayInfo->sCharacterData, sizeof(CharacterData));

		TransPlayerInfo.size = sizeof(smTRNAS_PLAYERINFO);
		TransPlayerInfo.code = smTRANSCODE_PLAYERINFO;
		TransPlayerInfo.dwObjectSerial = lpPlayInfo->iID;

		TransPlayerInfo.x = lpPlayInfo->sPosition.iX;
		TransPlayerInfo.y = lpPlayInfo->sPosition.iY;
		TransPlayerInfo.z = lpPlayInfo->sPosition.iZ;

		SENDPACKET(lpSndPlayInfo, &TransPlayerInfo);
	}

	return TRUE;
}

//Ä³¸¯ÅÍ Á¤º¸Àû¾î¼­ µÇµ¹·Á¼­ º¸³¿ ( Äü»çÀÌÁî )
int rsSendPlayerInfoQuick(User *lpSndPlayInfo, smTRANS_COMMAND *lpTransCommand)
{
	Unit		*lpChar;
	User	*lpPlayInfo;
	smTRNAS_PLAYERINFO_QUICK	TransPlayerInfoQ;
	int			QuickSize;

	//NPC ¶Ç´Â ¸ó½ºÅÍ
	lpChar = SERVERUNIT->GetUnit(lpTransCommand->WParam);
	if (lpChar) {
		rsSendCharInfo(lpChar, lpSndPlayInfo);
		return TRUE;
	}

	//´Ù¸¥ À¯Àúµé
	lpPlayInfo = SERVERUSER->GetUser(lpTransCommand->WParam);
	if (lpPlayInfo && lpPlayInfo->iID && lpSndPlayInfo) {

		if (lpPlayInfo->sCharacterData.bUpdateInfo[0] != 0) {	//¾÷µ¥ÀÌÆ® µÈ Á¤º¸ (Ä³¸¯ÅÍ ÀüÃ¼Á¤º¸ º¸³¿)
			//Ä³¸¯ÅÍ Á¤º¸Àû¾î¼­ µÇµ¹·Á¼­ º¸³¿
			//return rsSendPlayerInfo( lpsmsock , lpTransCommand , lpPlayInfo );
			QuickSize = smCHAR_INFO_QUICK_SIZE2;
		}
		else {
			QuickSize = smCHAR_INFO_QUICK_SIZE;
		}

		memcpy(&TransPlayerInfoQ.sCharacterData, &lpPlayInfo->sCharacterData, QuickSize);
		TransPlayerInfoQ.size = sizeof(smTRNAS_PLAYERINFO_QUICK) - (sizeof(CharacterData) - QuickSize);
		TransPlayerInfoQ.code = smTRANSCODE_PLAYERINFO_Q;
		TransPlayerInfoQ.dwObjectSerial = lpPlayInfo->iID;
		TransPlayerInfoQ.x = lpPlayInfo->sPosition.iX;
		TransPlayerInfoQ.y = lpPlayInfo->sPosition.iY;
		TransPlayerInfoQ.z = lpPlayInfo->sPosition.iZ;

		SENDPACKET(lpSndPlayInfo, &TransPlayerInfoQ);
	}

	return TRUE;
}

int rsSendTransSkillAttack(Unit *lpChar, User *lpPlayInfo)
{
	TRANS_ATTACKDATA	TransAttackData;
	int	temp;

	if (lpChar->iClanID && lpChar->iClanID == lpPlayInfo->iClanID)
		return NULL;

	TransAttackData.code = smTRANSCODE_ATTACKDATA;
	TransAttackData.size = sizeof(TRANS_ATTACKDATA);

	TransAttackData.x = lpPlayInfo->sPosition.iX;
	TransAttackData.y = lpPlayInfo->sPosition.iY;
	TransAttackData.z = lpPlayInfo->sPosition.iZ;

	TransAttackData.AttackState = 0x80;
	TransAttackData.AttackSize = 32 * fONE;
	TransAttackData.Power = GetRandomPos(lpChar->sUnitInfo.SkillDamage[0], lpChar->sUnitInfo.SkillDamage[1]);

	TransAttackData.dwDestObjectSerial = lpChar->iID;
	TransAttackData.dwTarObjectSerial = lpPlayInfo->iID;

	TransAttackData.sRating[0] = lpChar->sCharacterData.iLevel;
	TransAttackData.sRating[1] = lpChar->sCharacterData.iAttackRating;

	if (lpPlayInfo->dwSiegeItem_Scroll_Time && lpPlayInfo->dwSiegeItem_Scroll_Time < SERVER_GAMETIME)
	{
		lpPlayInfo->dwSiegeItem_Scroll_Code = 0;
		lpPlayInfo->dwSiegeItem_Scroll_Time = 0;
	}
	if (lpPlayInfo->dwSiegeItem_Stone1_Time && lpPlayInfo->dwSiegeItem_Stone1_Time < SERVER_GAMETIME)
	{
		lpPlayInfo->dwSiegeItem_Stone1_Code = 0;
		lpPlayInfo->dwSiegeItem_Stone1_Time = 0;
	}

	if (lpChar->sCharacterData.iMonsterEffectID == snCHAR_SOUND_CASTLE_CRYSTAL_B)
	{
		TransAttackData.sRating[0] = -SKILL_PLAY_ICE_CRYSTAL;
		TransAttackData.sRating[1] = 4;
	}
	else if (lpChar->sCharacterData.iMonsterEffectID == snCHAR_SOUND_CASTLE_CRYSTAL_G)
	{
		TransAttackData.sRating[0] = -SKILL_PLAY_LIGHTNING_CRYSTAL;
		TransAttackData.sRating[1] = 3;
	}
	else if (lpChar->sCharacterData.iMonsterEffectID == snCHAR_SOUND_CASTLE_CRYSTAL_R)
	{
		TransAttackData.sRating[0] = -SKILL_PLAY_FIRE_CRYSTAL;
		TransAttackData.sRating[1] = 1;
	}

	if (lpPlayInfo->dwSiegeItem_Stone1_Code && lpPlayInfo->dwSiegeItem_Stone1_Code == lpChar->sCharacterData.iMonsterEffectID)
	{
		TransAttackData.Power /= 2;
		TransAttackData.sRating[0] = lpChar->sCharacterData.iLevel;
		TransAttackData.sRating[1] = lpChar->sCharacterData.iAttackRating;
	}

	if (lpPlayInfo->dwSiegeItem_Scroll_Code == (sinBC1 | sin01))
	{
		if (lpPlayInfo->iMapID == MAPID_BlessCastle)
			return FALSE;
	}
	if (lpPlayInfo->dwSiegeItem_Scroll_Code == (sinBI1 | sin05))
		return FALSE;

	if (lpPlayInfo->dwSkill_PhysicalAbsorb_Time)
	{
		if (lpPlayInfo->dwSkill_PhysicalAbsorb_Time > SERVER_GAMETIME)
		{
			TransAttackData.Power -= lpPlayInfo->dwSkill_PhysicalAbsorb_Param;
			if (TransAttackData.Power < 0)
				return FALSE;
		}
		else
		{
			lpPlayInfo->dwSkill_PhysicalAbsorb_Time = 0;
			lpPlayInfo->dwSkill_PhysicalAbsorb_Param = 0;
		}
	}

	if (lpPlayInfo->dwSkill_MetalArmor_Time)
	{
		if (lpPlayInfo->dwSkill_MetalArmor_Time > SERVER_GAMETIME)
		{
			TransAttackData.Power -= lpPlayInfo->dwSkill_MetalArmor_Param;
			if (TransAttackData.Power < 0)
				return FALSE;
		}
		else
		{
			lpPlayInfo->dwSkill_MetalArmor_Time = 0;
			lpPlayInfo->dwSkill_MetalArmor_Param = 0;
		}
	}

	if (lpPlayInfo->dwSkill_HolyBody_Time)
	{
		if (lpPlayInfo->dwSkill_HolyBody_Time > SERVER_GAMETIME)
		{
			if (lpChar->sCharacterData.iMonsterType == MONSTERTYPE_Undead)
			{
				TransAttackData.Power -= (TransAttackData.Power*lpPlayInfo->dwSkill_HolyBody_Param) / 100;
				if (TransAttackData.Power < 0)
					return FALSE;
			}
		}
		else
		{
			lpPlayInfo->dwSkill_HolyBody_Time = 0;
			lpPlayInfo->dwSkill_HolyBody_Param = 0;
		}
	}

	if (lpPlayInfo->dwSkill_VirtualLife_Time)
	{
		if (lpPlayInfo->dwSkill_VirtualLife_Time > SERVER_GAMETIME)
		{
			TransAttackData.Power -= (TransAttackData.Power*lpPlayInfo->dwSkill_VirtualLife_Param) / 100;
			if (TransAttackData.Power < 0)
				return FALSE;
		}
		else
		{
			lpPlayInfo->dwSkill_VirtualLife_Time = 0;
			lpPlayInfo->dwSkill_VirtualLife_Param = 0;
		}
	}

	if (lpPlayInfo->dwSkill_EnergyShield_Time)
	{
		if (lpPlayInfo->dwSkill_EnergyShield_Time > SERVER_GAMETIME)
		{
			temp = (TransAttackData.Power*lpPlayInfo->dwSkill_EnergyShield_Param) / 100;
			TransAttackData.Power -= temp;
			TransAttackData.AttackState |= (temp << 16);
			if (TransAttackData.Power < 0)
				return FALSE;
		}
		else
		{
			lpPlayInfo->dwSkill_EnergyShield_Time = 0;
			lpPlayInfo->dwSkill_EnergyShield_Param = 0;
		}
	}

	if (lpPlayInfo->dwBlessSkill_Code)
	{
		if (lpPlayInfo->dwBlessSkill_Code == SKILL_PLAY_BLESS_ABSORB)
		{
			if (lpPlayInfo->dwBlessSkill_Time > SERVER_GAMETIME)
			{
				TransAttackData.Power -= lpPlayInfo->dwBlessSkill_Param;
				if (TransAttackData.Power < 0)
					return FALSE;
			}
			else
			{
				lpPlayInfo->dwBlessSkill_Code = 0;
				lpPlayInfo->dwBlessSkill_Time = 0;
			}
		}
	}

	if (lpChar->sUnitInfo.SkillRangeRect.left == 0 && lpChar->sUnitInfo.SkillRangeRect.right == 0)
	{
		switch (lpChar->sCharacterData.iMonsterEffectID)
		{
		case snCHAR_SOUND_CHAOSCARA:
		case snCHAR_SOUND_DEVILSHY:
		case smCHAR_SOUND_WLORD:
			TransAttackData.sRating[0] = -SKILL_PLAY_CHAOSCARA_VAMP;
			TransAttackData.sRating[1] = 0;
			break;
		}
	}

	TransAttackData.dwChkSum = TransAttackData.Power * 2002 + (TransAttackData.x * TransAttackData.y * TransAttackData.z);

	if (lpPlayInfo)
	{
		lpPlayInfo->Send_AttackCount++;
		lpPlayInfo->Send_AttackDamage += TransAttackData.Power;

		TransAttackData.dwDamageChkSum = dm_GetDamgeChkSum_S2V(&TransAttackData);

		SENDPACKET(lpPlayInfo, &TransAttackData);
	}

	return NULL;
}


//Ä³¸¯ÅÍ º¯°æ
int rsCharChanger(Unit *lpChar, CharacterData *lpCharInfo, UnitInfo *lpMonInfo)
{
	int rnd, OsCode;
	int dist;
	Map	*lpStgArea;


	lpStgArea = lpChar->pcMap;

	lpChar->Close();
	lpChar->bActive = TRUE;

	//Ä³¸¯ÅÍÀÇ Á¤º¸ º¯°æ
	rnd = lpChar->sCharacterData.bUpdateInfo[0];
	OsCode = lpChar->iID;


	//¸ó½ºÅÍ Ä³¸¯ÅÍ ¼öÄ¡ ¼³Á¤
	memcpy(&lpChar->sCharacterData, lpCharInfo, sizeof(CharacterData));
	memcpy(&lpChar->sUnitInfo, lpMonInfo, sizeof(UnitInfo));
	lpChar->ActionPattern = 5;

	lpChar->SetLoadPattern(lpChar->sCharacterData.Player.szBodyModel);

	dist = 64 * 30;
	lpChar->iLureDistance = dist * dist;
	lpChar->sSpawnPosition.iX = lpChar->pX;
	lpChar->sSpawnPosition.iZ = lpChar->pZ;

	lpChar->iDeathCounter = REOPEN_COUNT_NUM;
	lpChar->SetMotionFromCode(ANIMATIONTYPE_Idle);
	lpChar->sCharacterData.bUpdateInfo[0] = rnd + 1;
	lpChar->iID = OsCode;
	lpChar->pcFocusTarget = 0;
	lpChar->sCharacterData.sHP.sMin = lpChar->sCharacterData.sHP.sMax;
	lpChar->sCharacterData.iStatPoints = lpMonInfo->ClassCode;

	if (lpChar->sUnitInfo.iMaxPotions)
	{
		if ((rand() % 100) < lpChar->sUnitInfo.iPerPotions)
			lpChar->sUnitInfo.iMaxPotions = (rand() % lpChar->sUnitInfo.iMaxPotions) + 1;
		else
			lpChar->sUnitInfo.iMaxPotions = 0;
	}

	return TRUE;
}


//µ¥¹ÌÁöÁØ À¯Àú 10¸í ¼±º°
int	SelectDamageTop10(Unit *lpChar, rsUSER_LIST_TOP10 *lpUserListDamageTop10)
{
	int cnt, cnt2;
	int ChkCnt;

	if (!lpChar->psaDamageUsersData || !lpUserListDamageTop10) return FALSE;

	ZeroMemory(lpUserListDamageTop10, sizeof(rsUSER_LIST_TOP10));

	for (cnt = 0; cnt < 10; cnt++) {
		ChkCnt = -1;
		for (cnt2 = 0; cnt2 < ATTACK_DAMAGE_LIST_MAX; cnt2++) {
			if (lpChar->psaDamageUsersData[cnt2].iID &&
				lpChar->psaDamageUsersData[cnt2].iDamage > lpUserListDamageTop10->Damage[cnt]) {

				lpUserListDamageTop10->dwUserCode[cnt] = lpChar->psaDamageUsersData[cnt2].iID;
				lpUserListDamageTop10->Damage[cnt] = lpChar->psaDamageUsersData[cnt2].iDamage;
				lpUserListDamageTop10->Counter[cnt] = lpChar->psaDamageUsersData[cnt2].iCounter;

				ChkCnt = cnt2;
			}
		}

		if (ChkCnt >= 0)
			lpChar->psaDamageUsersData[ChkCnt].iID = 0;
	}

	lpUserListDamageTop10->dwUpdateTime = SERVER_GAMETIME;
	lpUserListDamageTop10->dwCharCode = lpChar->iID;

	lpUserListDamageTop10->code = smTRANSCODE_SYSTEM;
	lpUserListDamageTop10->size = sizeof(rsUSER_LIST_TOP10);
	lpUserListDamageTop10->tCode = smTRANS_SYSCODE_DMG_USER_LIST;
	lpUserListDamageTop10->dwObjectSerial = SERVER_CODE;

	if (!dwSerToSerIP) return TRUE;

	//lpsmSock = rsFindNextSertoServerSock();

	//if (lpsmSock)
		//return lpsmSock->Send((char *)lpUserListDamageTop10, lpUserListDamageTop10->size, TRUE);

	return FALSE;
}


//SOD ±ôÂ¦ ¾ÆÀÌÅÛ µå·Ó·ü Å×ÀÌºí
DWORD dwSoD_ItemDropTable[9][2] =
{
	{(sinSD2 | sin01)	,20	},
	{(sinSD2 | sin02)	,40	},
	{(sinSD2 | sin03)	,60	},
	{(sinSD2 | sin04)	,65	},
	{(sinSD2 | sin05)	,80	},
	{(sinSD2 | sin06)	,95	},
	{(sinSD2 | sin07)	,100},
	{(sinQT1 | sin18)	,75	},
	{0				,0	}
};



//SOD ÎïÆ·µôÂä
int rsOpen_SodItem(Unit *lpChar, User *lprsPlayInfo)
{
	int rnd, cnt;

	rnd = rand() % 1000;

	if (rnd < 20)
	{
		rnd = rand() % 100;

		for (cnt = 0; cnt < 8; cnt++)
		{
			if (dwSoD_ItemDropTable[cnt][0] == 0)
				return FALSE;
			if ((DWORD)rnd < dwSoD_ItemDropTable[cnt][1])
			{
				auto pDefItem = SERVERITEM->FindItemDefByCode(dwSoD_ItemDropTable[cnt][0]);

				LootItem sLootItem{ 0 };

				if (pDefItem)
				{
					SERVERITEM->CreateItem(&sLootItem.sItem, pDefItem);

					if (sLootItem.sItem.sItemID.ToInt() == (sinQT1 | sin18))
					{
						SERVERITEM->SendItemData(lprsPlayInfo, &sLootItem.sItem);
					}
					else
					{
						sLootItem.bUse = TRUE;
						auto pLootItem = SERVERMAP->AddItem(lpChar->pcMap, &sLootItem, lpChar->sPosition >> 8, TRUE);

						if (pLootItem)
						{
							SERVERMAP->SendItemStageNearUsers(lpChar->pcMap, pLootItem);
						}
					}
				}
				return TRUE;
			}
		}
	}

	return FALSE;
}

#define TRANS_MAX_USER_LIMIT_OVER		(TRANS_MAX_USER_LIMIT*4)

int rsConnectViewDist = DIST_TRANSLEVEL_CONNECT;


DWORD srAutoTransCounter = 0;

static int srBillingCounter = 0;

static DWORD dwBillingTime = 0;

//ºô¸µ ³²Àº ½Ã°£ Ç¥½Ã
int srDisplayBillingTime(User *lpPlayInfo, int Add_BillingTime)
{
	struct tm today;

	int y, m, d, h, hm, hs;
	TRANS_CHATMESSAGE	TransChatMessage;
	int Time;
	char	*lpBuff;
	char	szBuff[128];

	if ((lpPlayInfo->Bl_Meter&BIMASK_PRORATE_USER) != 0)
		return FALSE;

	if ((lpPlayInfo->Bl_Meter&BIMASK_FREE_USER) != 0)
		return FALSE;

	if (lpPlayInfo->Bl_RNo > 0)
		lpBuff = srMsg_Bl_02;
	else
		lpBuff = "";

	szBuff[0] = 0;

	if (lpPlayInfo->DisuseDay)
	{
		localtime_s(&today, &lpPlayInfo->DisuseDay);

		if (Add_BillingTime)
			localtime_s(&today, (time_t *)&Add_BillingTime);

		y = today.tm_year + 1900;
		m = today.tm_mon + 1;
		d = today.tm_mday;
		h = today.tm_hour;
		hm = today.tm_min;
		hs = today.tm_sec;

		if (hm != 0)
			wsprintf(TransChatMessage.szMessage, "%s. You can play until %d:%d - %d/%d/%d (GMT).%s", lpBuff, y, m, d, h, hm, szBuff);
		else
			wsprintf(TransChatMessage.szMessage, "%s. You can play until %d:%d - %d/%d/%d (GMT).%s", lpBuff, y, m, d, h, hm, szBuff);


		TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
		TransChatMessage.dwIP = 3;
		TransChatMessage.dwObjectSerial = 0;

		SENDPACKET(lpPlayInfo, &TransChatMessage);
	}


	if (lpPlayInfo->dwPeriodTime)
	{
		if (Add_BillingTime)
			wsprintf(szBuff, "You've reserved another [%d hours]", Add_BillingTime / (60 * 60));

		if (lpPlayInfo->dwPeriodTime > (DWORD)SERVER_LOCATIME)
			Time = (lpPlayInfo->dwPeriodTime - (DWORD)SERVER_LOCATIME) / 60;
		else
			Time = 0;

		if (Time < 0) Time = 0;

		Time += Add_BillingTime / 60;
		szBuff[0] = 0;

		h = Time / 60;
		m = Time % 60;

		if (h > 0)
			wsprintf(TransChatMessage.szMessage, "%s. You can play for %d hour %d minutes.%s", lpBuff, h, m, szBuff);
		else
			wsprintf(TransChatMessage.szMessage, "%s. There are %d minutes left.%s", lpBuff, m, szBuff);

		TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
		TransChatMessage.dwIP = 3;
		TransChatMessage.dwObjectSerial = 0;

		SENDPACKET(lpPlayInfo, &TransChatMessage);
	}


	return TRUE;
}





static DWORD FrameSkipTimer = 0;
static DWORD fps = 70;
static DWORD FpsTime;


//ÇÃ·¹ÀÌ ¸ÞÀÎ ·çÇÁ
int srPlayMain()
{
	
	return 0;
}


//ÃÊ±âÈ­
int InitAll()
{
	DWORD nsize = 32;
	char szServerName[32];
	GetComputerName(szServerName, &nsize);

	ServerNameCode = GetCodebyName(szServerName);

	rsNoticeMessage.Counter = 0;
	rsNoticeMessage.szMessage[0] = 0;

	InitMaterial();
	//srInitChar();
	//InitMonster();
	//LoadOftenNpc();
	Stage_StepHeight = fONE * 20;

	//ConvertMonsterNames();

	//SetTimer(hwnd, 0, 100, NULL);

	//InitLogSql();

	//rsResetClientFuncPos();

	//rsLoadCopiedItemList();

	RecordShutdownLog(50020, 0, 0);

	ZeroMemory(&rsUserListDamageTop10, sizeof(rsUSER_LIST_TOP10));

	ZeroMemory(&CurrencyLog, sizeof(rsCURRENCY_LOG));

	return TRUE;
}

//Á¾·á ¸ðµç ÀÛ¾÷À» ¸Þ¸ð¸®¿¡¼­ Á¦°Å
void RemoveAll()
{
	int cnt;
	smTRANS_COMMAND smTransCommand;

	RecordShutdownLog(50030, 0, 0);

	for (cnt = 0; cnt < PLAYERS_MAX; cnt++)
	{
		User * u = USERSDATA + cnt;

		if (u->psCharacterFile)
		{
			if (u && u->szCharacterName[0])
			{
				if (SERVERACCOUNT->SaveFile(u, u->szCharacterName, (PacketCharacterRecordData *)u->psCharacterFile) == TRUE)
				{
					if (lstrcmpi(u->szCharacterName, u->psCharacterFile->sCharInfo.szName) != 0)
					{
						smTransCommand.WParam = 10002;
						smTransCommand.LParam = (DWORD)u->szCharacterName;
						smTransCommand.SParam = (DWORD)u->psCharacterFile->sCharInfo.szName;
						RecordHackLogFile(u, &smTransCommand);
					}

					SERVERUSER->SaveDropItem(u);
					SERVERUSER->InventoryServerCheck(u, 1);
				}
			}
		}
	}

	//rsCloseDataBase();
	//CloseLogSql();

	SERVER_MUTEX->Lock(3000);

	srRemoveChar();

	CloseMaterial();

	SERVER_MUTEX->UnLock();
}

DWORD dwConnIPCheckTime = 0;


int	rsSetNoticeMessage(char *szMessage)
{
	lstrcpy(rsNoticeMessage.szMessage, szMessage);
	rsNoticeMessage.Counter++;

	return rsNoticeMessage.Counter;
}
int	SendSaveClientData(User *lpPlayInfo)
{
	smTRANS_COMMAND	smTransCommand;

	smTransCommand.code = smTRANSCODE_SAVECLIENT;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 0;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;
	smTransCommand.EParam = 0;

	SENDPACKET(lpPlayInfo, &smTransCommand);

	return TRUE;
}
int SaveThrowItemOver(User *lpPlayInfo, DWORD dwCode, DWORD dwKey, DWORD dwSum)
{
	int cnt;
	int LowCount;
	DWORD	LowCode;
	DWORD	Code;

	if (lpPlayInfo->ThrowItemCount <= 0)
		return FALSE;

	LowCount = 0;
	LowCode = lpPlayInfo->ThrowItemInfo[LowCount].dwCode & sinITEM_MASK3;

	for (cnt = 1; cnt < lpPlayInfo->ThrowItemCount; cnt++)
	{
		Code = lpPlayInfo->ThrowItemInfo[cnt].dwCode & sinITEM_MASK3;
		if (Code < LowCode)
		{
			LowCode = Code;
			LowCount = cnt;
		}
	}

	lpPlayInfo->ThrowItemInfo[LowCount].dwCode = dwCode;
	lpPlayInfo->ThrowItemInfo[LowCount].dwKey = dwKey;
	lpPlayInfo->ThrowItemInfo[LowCount].dwSum = dwSum;

	return TRUE;
}
int SaveThrowItem(User *lpPlayInfo, DWORD dwCode, DWORD dwKey, DWORD dwSum)
{
	int cnt;

	if ((dwCode&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
		return TRUE;

	for (cnt = 0; cnt < lpPlayInfo->ThrowItemCount; cnt++)
	{
		if (lpPlayInfo->ThrowItemInfo[cnt].dwCode == dwCode && lpPlayInfo->ThrowItemInfo[cnt].dwKey == dwKey && lpPlayInfo->ThrowItemInfo[cnt].dwSum == dwSum)
			return TRUE;
	}

	if (lpPlayInfo->ThrowItemCount >= THROW_ITEM_INFO_MAX - 1)
		return SaveThrowItemOver(lpPlayInfo, dwCode, dwKey, dwSum);

	lpPlayInfo->ThrowItemInfo[lpPlayInfo->ThrowItemCount].dwCode = dwCode;
	lpPlayInfo->ThrowItemInfo[lpPlayInfo->ThrowItemCount].dwKey = dwKey;
	lpPlayInfo->ThrowItemInfo[lpPlayInfo->ThrowItemCount].dwSum = dwSum;

	if (lpPlayInfo->ThrowItemCount < THROW_ITEM_INFO_MAX - 1)
	{
		lpPlayInfo->ThrowItemCount++;

		if (lpPlayInfo->ThrowItemCount == THROW_ITEM_INFO_MAX - 32 || lpPlayInfo->ThrowItemCount > THROW_ITEM_INFO_MAX - 48)
			SendSaveClientData(lpPlayInfo);
	}

	return TRUE;
}
int SaveThrowItem2(User *lpPlayInfo, DWORD dwCode, DWORD dwKey, DWORD dwSum)
{
	int cnt;

	if ((dwCode&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
		return TRUE;

	for (cnt = 0; cnt < lpPlayInfo->ThrowItemCount; cnt++)
	{
		if (lpPlayInfo->ThrowItemInfo[cnt].dwCode == dwCode && lpPlayInfo->ThrowItemInfo[cnt].dwKey == dwKey && lpPlayInfo->ThrowItemInfo[cnt].dwSum == dwSum)
			return TRUE;
	}

	if (lpPlayInfo->ThrowItemCount >= THROW_ITEM_INFO_MAX - 1)
		return SaveThrowItemOver(lpPlayInfo, dwCode, dwKey, dwSum);

	lpPlayInfo->ThrowItemInfo[lpPlayInfo->ThrowItemCount].dwCode = dwCode;
	lpPlayInfo->ThrowItemInfo[lpPlayInfo->ThrowItemCount].dwKey = dwKey;
	lpPlayInfo->ThrowItemInfo[lpPlayInfo->ThrowItemCount].dwSum = dwSum;

	if (lpPlayInfo->ThrowItemCount < THROW_ITEM_INFO_MAX - 1)
		lpPlayInfo->ThrowItemCount++;

	return TRUE;
}
int SaveThrowItems(User *lpPlayInfo, TRANS_THROW_ITEMS *lpTransThrowItems)
{
	int cnt;

	for (cnt = 0; cnt < lpTransThrowItems->ThrowItemCount; cnt++)
	{
		if (lpPlayInfo->ThrowItemCount >= THROW_ITEM_INFO_MAX - 1)
			SaveThrowItemOver(lpPlayInfo, lpTransThrowItems->ThrowItems[cnt].dwCode, lpTransThrowItems->ThrowItems[cnt].dwHead, lpTransThrowItems->ThrowItems[cnt].dwChkSum);
		else
		{
			lpPlayInfo->ThrowItemInfo[lpPlayInfo->ThrowItemCount].dwCode = lpTransThrowItems->ThrowItems[cnt].dwCode;
			lpPlayInfo->ThrowItemInfo[lpPlayInfo->ThrowItemCount].dwKey = lpTransThrowItems->ThrowItems[cnt].dwHead;
			lpPlayInfo->ThrowItemInfo[lpPlayInfo->ThrowItemCount].dwSum = lpTransThrowItems->ThrowItems[cnt].dwChkSum;
			lpPlayInfo->ThrowItemCount++;
		}
	}

	return TRUE;
}
int rsGetServerPotion(User *lpPlayInfo, DWORD dwPotionCode)
{
	int x = -1, y = -1;

	switch (dwPotionCode)
	{
	case (sinPL1 | sin01):
		x = 0; y = 0;
		break;
	case (sinPL1 | sin02):
		x = 0; y = 1;
		break;
	case (sinPL1 | sin03):
		x = 0; y = 2;
		break;
	case (sinPL1 | sin04):
		x = 0; y = 3;
		break;

	case (sinPM1 | sin01):
		x = 1; y = 0;
		break;
	case (sinPM1 | sin02):
		x = 1; y = 1;
		break;
	case (sinPM1 | sin03):
		x = 1; y = 2;
		break;
	case (sinPM1 | sin04):
		x = 1; y = 3;
		break;

	case (sinPS1 | sin01):
		x = 2; y = 0;
		break;
	case (sinPS1 | sin02):
		x = 2; y = 1;
		break;
	case (sinPS1 | sin03):
		x = 2; y = 2;
		break;
	case (sinPS1 | sin04):
		x = 2; y = 3;
		break;
	}

	if (x >= 0 && y >= 0)
		return lpPlayInfo->ServerPotion[x][y];

	return 0;

}

int rsServerPotionErrorLog(User *lpPlayInfo, DWORD dwCode, int Count, int Position)
{
	smTRANS_COMMAND_EX	smTransCommandEx;

	if (lpPlayInfo->WarningCount < 3)
	{
		smTransCommandEx.WParam = 8810;
		smTransCommandEx.LParam = dwCode;
		smTransCommandEx.SParam = Count;
		smTransCommandEx.EParam = Position;
		RecordHackLogFile(lpPlayInfo, &smTransCommandEx);
	}

	return TRUE;
}

int	rsAddTradePotionInfo(User *lpPlayInfo, DWORD	dwCode)
{

	if (lpPlayInfo->TradePotionInfoCount >= 16)
		return FALSE;

	if (SERVERITEM->GetDropPotion(lpPlayInfo, dwCode) == TRUE)
		return TRUE;

	lpPlayInfo->dwTradePotionInfo[lpPlayInfo->TradePotionInfoCount++] = dwCode;

	return TRUE;
}

int	rsTradeInvenItem(User *lpPlayInfo, User *lpPlayInfo2, TRANS_TRADE_ITEMKEY *lpTransTradeItemKey)
{
	int cnt;
	int money;
	smTRANS_COMMAND_EX	smTransCommand;
	DWORD	dwTradeCode;
	DWORD	dwTradeTime;
	int	PotionCount;

	if (!lpPlayInfo || !lpPlayInfo2)
		return FALSE;

	dwTradeCode = (lpTransTradeItemKey->Money * lpPlayInfo->iID + lpPlayInfo2->iID);
	for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++)
	{
		if (lpTransTradeItemKey->dwItemCode[cnt])
			dwTradeCode += (lpTransTradeItemKey->dwItemCode[cnt] + lpTransTradeItemKey->dwItemKey[cnt] + lpTransTradeItemKey->dwItemSum[cnt])*(cnt + 2);
	}
	dwTradeTime = SERVER_GAMETIME;

	if ((dwTradeTime - lpPlayInfo->dwLastTradeTime) < 8000 && lpPlayInfo->dwLastTradeChksum == dwTradeCode)
	{
		for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++)
		{
			if (lpTransTradeItemKey->dwItemCode[cnt])
			{
				if ((lpTransTradeItemKey->dwItemCode[cnt] & sinITEM_MASK1) != (sinPM1&sinITEM_MASK1))
				{
					if (SERVERITEM->DeleteItemInventory(lpPlayInfo,
						lpTransTradeItemKey->dwItemCode[cnt],
						lpTransTradeItemKey->dwItemKey[cnt],
						lpTransTradeItemKey->dwItemSum[cnt]) == FALSE)
					{
						smTransCommand.WParam = 8000;
						smTransCommand.WxParam = 31;
						smTransCommand.LxParam = (int)"*TRADE CHECKING ERROR*";
						smTransCommand.LParam = lpTransTradeItemKey->dwItemCode[cnt];
						smTransCommand.SParam = lpTransTradeItemKey->dwItemKey[cnt];
						smTransCommand.EParam = lpTransTradeItemKey->dwItemSum[cnt];
						RecordHackLogFile(lpPlayInfo, &smTransCommand);
					}
				}
			}
		}
		return TRUE;
	}

	lpPlayInfo->TradePotionInfoCount = 0;

	if (lpTransTradeItemKey->Money)
	{
		money = lpTransTradeItemKey->Money - 193;
		if (lpPlayInfo->GetGold() < money)
		{
			smTransCommand.WParam = 8010;
			smTransCommand.LParam = 30;
			smTransCommand.SParam = lpPlayInfo->GetGold();
			smTransCommand.EParam = money;
			RecordHackLogFile(lpPlayInfo, &smTransCommand);

			return FALSE;
		}

		SERVERUSER->SubServerUserGold(lpPlayInfo, money, WHEREID_Trade);
		SERVERUSER->AddServerUserGold(lpPlayInfo2, money, WHEREID_Trade);
	}

	for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++)
	{
		if (lpTransTradeItemKey->dwItemCode[cnt])
		{
			if ((lpTransTradeItemKey->dwItemCode[cnt] & sinITEM_MASK1) != (sinPM1&sinITEM_MASK1))
			{
				if (SERVERITEM->DeleteItemInventory(lpPlayInfo,
					lpTransTradeItemKey->dwItemCode[cnt],
					lpTransTradeItemKey->dwItemKey[cnt],
					lpTransTradeItemKey->dwItemSum[cnt]) == FALSE)
				{
					smTransCommand.WParam = 8000;
					smTransCommand.WxParam = 30;
					smTransCommand.LxParam = (int)"*TRADE ITEM*";
					smTransCommand.LParam = lpTransTradeItemKey->dwItemCode[cnt];
					smTransCommand.SParam = lpTransTradeItemKey->dwItemKey[cnt];
					smTransCommand.EParam = lpTransTradeItemKey->dwItemSum[cnt];
					RecordHackLogFile(lpPlayInfo, &smTransCommand);

					lpTransTradeItemKey->dwItemKey[cnt] = 0;
				}
			}
			else
			{
				PotionCount = 0x5cbc ^ (lpTransTradeItemKey->dwItemSum[cnt] >> 16) ^ lpTransTradeItemKey->dwItemSum[cnt];
				PotionCount &= 0xFFFF;

				if (SERVERITEM->AddPotion(lpPlayInfo, lpTransTradeItemKey->dwItemCode[cnt], -PotionCount) < 0)
				{
					rsServerPotionErrorLog(lpPlayInfo, lpTransTradeItemKey->dwItemCode[cnt], -PotionCount, 100);
					return FALSE;
				}
				SERVERITEM->AddPotion(lpPlayInfo2, lpTransTradeItemKey->dwItemCode[cnt], PotionCount);
				rsAddTradePotionInfo(lpPlayInfo, lpTransTradeItemKey->dwItemCode[cnt]);
			}

			if (lpTransTradeItemKey->dwItemKey[cnt])
			{
				SERVERITEM->AddItemInventory(lpPlayInfo2, lpTransTradeItemKey->dwItemCode[cnt], lpTransTradeItemKey->dwItemKey[cnt], lpTransTradeItemKey->dwItemSum[cnt]);
				SaveThrowItem2(lpPlayInfo, lpTransTradeItemKey->dwItemCode[cnt], lpTransTradeItemKey->dwItemKey[cnt], lpTransTradeItemKey->dwItemSum[cnt]);
			}
		}
	}

	lpPlayInfo->dwLastTradeTime = dwTradeTime;
	lpPlayInfo->dwLastTradeChksum = dwTradeCode;

	rsRecord_ItemLog_Trade(lpPlayInfo, lpPlayInfo2, lpTransTradeItemKey);

	return TRUE;
}
int SendShopItemList(User *pcUser, Unit *lpChar)
{
	int cnt;
	char szBuff[8192];
	smTRANS_SELL_ITEM	*lpTransSellItem;
	DefinitionItem		*lpDefItem;
	char *lpBuff;
	int TransLen;
	int	ItemCount;

	lpTransSellItem = (smTRANS_SELL_ITEM *)szBuff;

	lpTransSellItem->code = smTRANSCODE_SHOP_ITEMLIST;

	if (lpChar->sUnitInfo.iWeaponShopCounter) {
		ItemCount = 0;
		//°ø°Ý ¾ÆÀÌÅÛ ÆÇ¸Å ¸ñ·Ï ÀÛ¼º
		lpBuff = ((char *)lpTransSellItem) + sizeof(smTRANS_SELL_ITEM);
		TransLen = sizeof(smTRANS_SELL_ITEM);
		for (cnt = 0; cnt < lpChar->sUnitInfo.iWeaponShopCounter; cnt++) 
		{
			lpDefItem = SERVERITEM->FindItemDefByCode(lpChar->sUnitInfo.dwaWeaponShop[cnt]);

			if (lpDefItem && (TransLen + lpDefItem->DefCompressDataLen) < 8192)
			{
				memcpy(lpBuff, lpDefItem->DefCompressData, lpDefItem->DefCompressDataLen);
				TransLen += lpDefItem->DefCompressDataLen;
				lpBuff += lpDefItem->DefCompressDataLen;
				ItemCount++;
			}
		}
		lpTransSellItem->size = TransLen;
		lpTransSellItem->ItemKind = 1;
		lpTransSellItem->ItemCounter = ItemCount;

		SENDPACKET(pcUser, lpTransSellItem);
	}


	if (lpChar->sUnitInfo.iDefenseShopCounter) {
		ItemCount = 0;
		//¹æ¾î ¾ÆÀÌÅÛ ÆÇ¸Å ¸ñ·Ï ÀÛ¼º
		lpBuff = ((char *)lpTransSellItem) + sizeof(smTRANS_SELL_ITEM);
		TransLen = sizeof(smTRANS_SELL_ITEM);
		for (cnt = 0; cnt < lpChar->sUnitInfo.iDefenseShopCounter; cnt++)
		{
			lpDefItem = SERVERITEM->FindItemDefByCode(lpChar->sUnitInfo.dwaDefenseShop[cnt]);

			if (lpDefItem && (TransLen + lpDefItem->DefCompressDataLen) < 8192)
			{
				memcpy(lpBuff, lpDefItem->DefCompressData, lpDefItem->DefCompressDataLen);
				TransLen += lpDefItem->DefCompressDataLen;
				lpBuff += lpDefItem->DefCompressDataLen;
				ItemCount++;
			}
		}
		lpTransSellItem->size = TransLen;
		lpTransSellItem->ItemKind = 2;
		lpTransSellItem->ItemCounter = ItemCount;

		SENDPACKET(pcUser, lpTransSellItem);
	}


	if (lpChar->sUnitInfo.iMiscShopCounter) {
		ItemCount = 0;
		//¹æ¾î ¾ÆÀÌÅÛ ÆÇ¸Å ¸ñ·Ï ÀÛ¼º
		lpBuff = ((char *)lpTransSellItem) + sizeof(smTRANS_SELL_ITEM);
		TransLen = sizeof(smTRANS_SELL_ITEM);
		for (cnt = 0; cnt < lpChar->sUnitInfo.iMiscShopCounter; cnt++)
		{
			lpDefItem = SERVERITEM->FindItemDefByCode(lpChar->sUnitInfo.dwaMiscShop[cnt]);

			if (lpDefItem && (TransLen + lpDefItem->DefCompressDataLen) < 8192)
			{
				memcpy(lpBuff, lpDefItem->DefCompressData, lpDefItem->DefCompressDataLen);
				TransLen += lpDefItem->DefCompressDataLen;
				lpBuff += lpDefItem->DefCompressDataLen;
				ItemCount++;
			}
		}
		lpTransSellItem->size = TransLen;
		lpTransSellItem->ItemKind = 3;
		lpTransSellItem->ItemCounter = ItemCount;

		SENDPACKET(pcUser, lpTransSellItem);
	}


	return TRUE;
}

int SendSkillMenu(User *pcUser, Unit *lpChar, int Mode)
{
	smTRANS_COMMAND		smTransCommand;

	smTransCommand.code = smTRANSCODE_SKILL_MENU;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = Mode;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;

	if (rsServerConfig.Disable_Quest == Mode)
		smTransCommand.WParam = FALSE;

	SENDPACKET(pcUser, &smTransCommand);

	return 0;
}
// ·¢ËÍ²Ö¿âµ½¿Í»§¶Ë
int SendWareHouseToClient(User *lpPlayInfo)
{
	if ((lpPlayInfo->dwDataError & rsDATA_ERROR_WAREHOUSE) != 0)
		return FALSE;

	if (lpPlayInfo->szAccountName[0] && !lpPlayInfo->szServerID[0] && lpPlayInfo->psCharacterFile->iLength > 0)
		return rsLoadWareHouseData(lpPlayInfo);

	return FALSE;
}
// ·¢ËÍ³èÎï²Ö¿âµ½¿Í»§¶Ë
int SendCaravanToClient(User *lpPlayInfo)
{
	if ((lpPlayInfo->dwDataError & rsDATA_ERROR_CARAVAN) != 0)
		return FALSE;
	if (lpPlayInfo->szCharacterName[0])
		return rsLoadCaravanData(lpPlayInfo);
	return FALSE;
}
// ·¢ËÍ²Ö¿âÐ­Òé
int SendOpenWareHouse(User *pcUser)
{
	smTRANS_COMMAND		smTransCommand;

	smTransCommand.code = smTRANSCODE_OPEN_WAREHOUSE;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 0;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;

	SENDPACKET(pcUser, &smTransCommand);

	return 0;
}

//¾ÆÀÌÅÛ Á¶ÇÕÃ¢ ¿­±â
int SendOpenMixItem(User *pcUser, int MixFlag)
{
	smTRANS_COMMAND		smTransCommand;

	smTransCommand.code = smTRANSCODE_OPEN_MIXITEM;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = MixFlag;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;

	SENDPACKET(pcUser, &smTransCommand);

	return 0;
}

// pluto ¾ÆÀÌÅÛ Á¦·Ã
int SendOpenSmelting(User *pcUser)
{
	smTRANS_COMMAND smTransCommand;

	smTransCommand.code = smTRANSCODE_OPEN_SMELTING;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 0;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;

	SENDPACKET(pcUser, &smTransCommand);

	return 0;
}
// pluto ¾ÆÀÌÅÛ Á¦ÀÛ
int SendOpenManufacture(User *pcUser)
{
	smTRANS_COMMAND smTransCommand;

	smTransCommand.code = smTRANSCODE_OPEN_MANUFACTURE;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 0;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;

	SENDPACKET(pcUser, &smTransCommand);

	return 0;
}
int SendOpenCollectMoney(User *lpPlayInfo, int sEvent, int sEventCount)
{
	smTRANS_COMMAND		smTransCommand;

	smTransCommand.code = smTRANSCODE_OPEN_COLLECT;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 0;
	smTransCommand.LParam = sEvent;
	smTransCommand.SParam = sEventCount;

	SENDPACKET(lpPlayInfo, &smTransCommand);

	return FALSE;
}

//°æÇ°ÀÌº¥Æ®
int SendOpenEventGift(User *pcUser)
{
	smTRANS_COMMAND		smTransCommand;

	smTransCommand.code = smTRANSCODE_OPEN_EVENTGIFT;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 0;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;

	SENDPACKET(pcUser, &smTransCommand);

	return 0;
}


//¿¡ÀÌÂ¡ Ã¢ ¿­±â
int SendOpenAgingItem(User *pcUser)
{
	smTRANS_COMMAND		smTransCommand;

	smTransCommand.code = smTRANSCODE_OPEN_AGING;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 0;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;

	SENDPACKET(pcUser, &smTransCommand);

	return 0;
}
//´ò¿×ÏµÍ³
int SendOpenSocketItem(User *pcUser)
{
	smTRANS_COMMAND smTransCommand;

	smTransCommand.code = smTRANSCODE_OPEN_SOCKET;

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 0;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;

	SENDPACKET(pcUser, &smTransCommand);

	return 0;
}

// ¼®Áö¿ë - ¹Í½ºÃÄ ¸®¼Â Ã¢ ¿­±â
int SendOpenMixtureItemReset(User *pcUser)
{
	smTRANS_COMMAND		smTransCommand;

	smTransCommand.code = smTRANSCODE_OPEN_MIXTURE_RESET;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 0;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;

	SENDPACKET(pcUser, &smTransCommand);

	return 0;
}
// ´ò¿ªÊôÐÔÎïÆ·
int SendOpenElementItem(User *pcUser)
{
	smTRANS_COMMAND smTransCommand;

	smTransCommand.code = smTRANSCODE_OPEN_ELEMENT;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 0;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;

	SENDPACKET(pcUser, &smTransCommand);

	return 0;
}
//´ò¿ª³èÎï²Ö¿â
int SendOpenCaravanItem(User *pcUser, int Kind)
{
	smTRANS_COMMAND smTransCommand;

	smTransCommand.code = smTRANSCODE_OPEN_CARAVAN;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = Kind;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;

	SENDPACKET(pcUser, &smTransCommand);

	return 0;
}
void rsSend_BadPlayerToGameServer(User *pcUser, int BadPlayer)
{
	smTRANS_COMMAND		smTransCommand;

	smTransCommand.code = smTRANSCODE_BAD_PLAYER;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = BadPlayer;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;
	smTransCommand.EParam = 0;

	rsSendGameServer(pcUser, &smTransCommand);
}

//¹èµå ÇÃ·¹ÀÌ¾î °ÔÀÓ¼­¹ö¿¡ ¼³Á¤
int rsSend_PlayerKilling(User *pcUser)
{
	smTRANS_COMMAND		smTransCommand;

	smTransCommand.code = smTRANSCODE_PLAYERKILLING;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 0;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;
	smTransCommand.EParam = 0;

	SENDPACKET(pcUser, &smTransCommand);

	return FALSE;
}


//Å¬·£ ¸Þ´º ¿­±â
int SendOpenClanMenu(User *pcUser)
{
	smTRANS_COMMAND		smTransCommand;

	smTransCommand.code = smTRANSCODE_OPEN_CLANMENU;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 0;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;

	SENDPACKET(pcUser, &smTransCommand);

	return 0;
}

//Äù½ºÆ® ÁøÇà Ã³¸®
int rsProcessQuest(User *lpPlayInfo, Unit *lpChar, int QuestCode, int QuestParam)
{
	smTRANS_COMMAND	smTransCommand;

	smTransCommand.code = smTRANSCODE_QUEST_MESSAGE;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = lpChar->sUnitInfo.iQuestTypeID;
	smTransCommand.LParam = lpChar->sUnitInfo.iQuestSubID;
	smTransCommand.SParam = 0;
	smTransCommand.EParam = 0;

	switch (QuestCode)
	{
	case SIN_QUEST_CODE_CHANGEJOB2_NPC_M:
	case SIN_QUEST_CODE_CHANGEJOB2_NPC_D:
		if (QuestParam == 1)
		{
			SERVERITEM->CreateItem(lpPlayInfo, sinMA1 | sin01);
			smTransCommand.SParam = 1;
		}
		break;

	case SIN_QUEST_CODE_CHANGEJOB4:
	case HAQUEST_CODE_FURYOFPHANTOM:
		smTransCommand.WParam = QuestCode;
		smTransCommand.LParam = QuestParam;
		break;
	}

	SENDPACKET(lpPlayInfo, &smTransCommand);

	return TRUE;
}

//·þÎñÆ÷ÈÎÎñ½ÓÊÕ
int rsGetQuestCommand(User *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{
	switch (lpTransCommand->WParam)
	{
	case SIN_QUEST_CODE_CHANGEJOB4:
		if (lpPlayInfo->sCharacterData.iLevel >= 49 && lpTransCommand->LParam == QUEST_ARENA_FIELD)
			OpenMonster_QuestArena(lpPlayInfo, SIN_QUEST_CODE_CHANGEJOB4);
		break;

	case HAQUEST_CODE_FURYOFPHANTOM:
		if (lpPlayInfo->sCharacterData.iLevel >= 99 && lpTransCommand->LParam == QUEST_ARENA_FIELD)
			OpenMonster_QuestArena(lpPlayInfo, HAQUEST_CODE_FURYOFPHANTOM, lpTransCommand->SParam);
		break;

	}
	switch (lpTransCommand->WParam)
	{
	case SIN_QUEST_CODE_LEVEL85:
		if (lpPlayInfo->sCharacterData.iLevel >= 85 && lpPlayInfo->sCharacterData.iRank >= 4)
		{
			if (lpTransCommand->LParam == 1)
				SERVERITEM->CreateItem(lpPlayInfo, sinQT1 | sin08);
		}
		break;
	case SIN_QUEST_CODE_LEVEL90:
		if (lpPlayInfo->sCharacterData.iLevel >= 90 && lpPlayInfo->sCharacterData.iRank >= 4)
		{
			if (lpTransCommand->LParam == 1)
				SERVERITEM->CreateItem(lpPlayInfo, sinQT1 | sin07);
		}
		break;
	case SIN_QUEST_CODE_LEVEL80_2:
		if (lpPlayInfo->sCharacterData.iLevel >= 80 && lpPlayInfo->sCharacterData.iRank >= 4)
		{
			if (lpTransCommand->LParam == 1)
				SERVERITEM->CreateItem(lpPlayInfo, sinQT1 | sin12);
		}
		break;
	case HAQUEST_CODE_ELEMENTARY_A:
		if (lpTransCommand->LParam == 1)
			SERVERITEM->CreateItem(lpPlayInfo, sinQT1 | sin14);

		if (lpTransCommand->LParam == 2)
		{
			if ((lpPlayInfo->dwElementaryQuestLogCheck & QUESTBIT_ELEMENTARY_A) == 0)
			{
				lpPlayInfo->dwElementaryQuestLogCheck |= QUESTBIT_ELEMENTARY_A;
				SERVERCHARACTER->GiveGold(lpPlayInfo, 50000);
			}
		}
		break;
	case HAQUEST_CODE_ELEMENTARY_B:
		if (lpPlayInfo->sCharacterData.iLevel >= 5)
		{
			if (lpTransCommand->LParam == 1)
			{
				if ((lpPlayInfo->dwElementaryQuestLogCheck & QUESTBIT_ELEMENTARY_B) == 0)
				{
					lpPlayInfo->dwElementaryQuestLogCheck |= QUESTBIT_ELEMENTARY_B;
					SERVERCHARACTER->GiveGold(lpPlayInfo, 100000);
				}
			}
		}
		break;
	case HAQUEST_CODE_ELEMENTARY_C:
		if (lpPlayInfo->sCharacterData.iLevel >= 10)
		{
			if (lpTransCommand->LParam == 1)
			{
				if ((lpPlayInfo->dwElementaryQuestLogCheck & QUESTBIT_ELEMENTARY_C) == 0)
				{
					lpPlayInfo->dwElementaryQuestLogCheck |= QUESTBIT_ELEMENTARY_C;
					SERVERCHARACTER->GiveGold(lpPlayInfo, 250000);
				}
			}
		}
		break;
	case HAQUEST_CODE_ELEMENTARY_D:
		if (lpPlayInfo->sCharacterData.iLevel >= 15)
		{
			if (lpTransCommand->LParam == 1)
				SERVERITEM->CreateItem(lpPlayInfo, sinQT1 | sin15);
			if (lpTransCommand->LParam == 2)
			{
				if ((lpPlayInfo->dwElementaryQuestLogCheck & QUESTBIT_ELEMENTARY_D) == 0)
				{
					lpPlayInfo->dwElementaryQuestLogCheck |= QUESTBIT_ELEMENTARY_D;
					SERVERCHARACTER->GiveGold(lpPlayInfo, 500000);
				}
			}
		}
		break;
	case HAQUEST_CODE_ELEMENTARY_E:
		if (lpPlayInfo->sCharacterData.iLevel >= 25 && lpPlayInfo->sCharacterData.iRank >= 1)
		{
			if (lpTransCommand->LParam == 1)
			{
				if ((lpPlayInfo->dwElementaryQuestLogCheck & QUESTBIT_ELEMENTARY_E) == 0)
				{
					lpPlayInfo->dwElementaryQuestLogCheck |= QUESTBIT_ELEMENTARY_E;
					SERVERCHARACTER->GiveEXP(lpPlayInfo, 1000000);
				}
			}
		}
		break;
	case HAQUEST_CODE_ELEMENTARY_F:
		if (lpPlayInfo->sCharacterData.iLevel >= 35 && lpPlayInfo->sCharacterData.iRank >= 1)
		{
			if (lpTransCommand->LParam == 1)
			{
				if ((lpPlayInfo->dwElementaryQuestLogCheck & QUESTBIT_ELEMENTARY_F) == 0)
				{
					lpPlayInfo->dwElementaryQuestLogCheck |= QUESTBIT_ELEMENTARY_F;
					SERVERCHARACTER->GiveGold(lpPlayInfo, 1000000);
				}
			}
		}
		break;
	case HAQUEST_CODE_ELEMENTARY_G:
		if (lpPlayInfo->sCharacterData.iLevel >= 45 && lpPlayInfo->sCharacterData.iRank >= 2)
		{
			if (lpTransCommand->LParam == 1)
			{
				if ((lpPlayInfo->dwElementaryQuestLogCheck & QUESTBIT_ELEMENTARY_G) == 0)
				{
					lpPlayInfo->dwElementaryQuestLogCheck |= QUESTBIT_ELEMENTARY_G;
					SERVERCHARACTER->GiveEXP(lpPlayInfo, 5000000);
					SERVERITEM->CreateItem(lpPlayInfo, sinGP1 | sin05);
					SERVERITEM->CreateItem(lpPlayInfo, sinGP1 | sin06);
				}
			}
		}
		break;
	case HAQUEST_CODE_ELEMENTARY_H:
		if (lpPlayInfo->sCharacterData.iLevel >= 50 && lpPlayInfo->sCharacterData.iRank >= 2)
		{
			if (lpTransCommand->LParam == 1)
			{
				if ((lpPlayInfo->dwElementaryQuestLogCheck & QUESTBIT_ELEMENTARY_H) == 0)
				{
					lpPlayInfo->dwElementaryQuestLogCheck |= QUESTBIT_ELEMENTARY_H;
					SERVERITEM->CreateItem(lpPlayInfo, sinQT1 | sin17);
				}
			}
		}
		break;
	case HAQUEST_CODE_ELEMENTARY_I:
		if (lpPlayInfo->sCharacterData.iLevel >= 65 && lpPlayInfo->sCharacterData.iRank >= 3)
		{
			if (lpTransCommand->LParam == 1)
			{
				if ((lpPlayInfo->dwElementaryQuestLogCheck & QUESTBIT_ELEMENTARY_I) == 0)
				{
					lpPlayInfo->dwElementaryQuestLogCheck |= QUESTBIT_ELEMENTARY_I;
					SERVERCHARACTER->GiveEXP(lpPlayInfo, 250000000);
				}
			}
		}
		break;
	case HAQUEST_CODE_ELEMENTARY_J:
		if (lpPlayInfo->sCharacterData.iLevel >= 75 && lpPlayInfo->sCharacterData.iRank >= 3)
		{
			if (lpTransCommand->LParam == 1)
			{
				if ((lpPlayInfo->dwElementaryQuestLogCheck & QUESTBIT_ELEMENTARY_J) == 0)
				{
					lpPlayInfo->dwElementaryQuestLogCheck |= QUESTBIT_ELEMENTARY_J;
					SERVERCHARACTER->GiveEXP(lpPlayInfo, 500000000);
				}
			}
		}
		break;
	case HAQUEST_CODE_ELEMENTARY_K:
		if (lpPlayInfo->sCharacterData.iLevel >= 85 && lpPlayInfo->sCharacterData.iRank >= 4)
		{
			if (lpTransCommand->LParam == 1)
			{
				if ((lpPlayInfo->dwElementaryQuestLogCheck & QUESTBIT_ELEMENTARY_K) == 0)
				{
					lpPlayInfo->dwElementaryQuestLogCheck |= QUESTBIT_ELEMENTARY_K;
					SERVERCHARACTER->GiveEXP(lpPlayInfo, 2000000000);
				}
			}
		}
		break;
	case HAQUEST_CODE_ELEMENTARY_L:
		if (lpPlayInfo->sCharacterData.iLevel >= 95 && lpPlayInfo->sCharacterData.iRank >= 4)
		{
			if (lpTransCommand->LParam == 1)
			{
				if ((lpPlayInfo->dwElementaryQuestLogCheck & QUESTBIT_ELEMENTARY_L) == 0)
				{
					lpPlayInfo->dwElementaryQuestLogCheck |= QUESTBIT_ELEMENTARY_L;
					SERVERCHARACTER->GiveEXP(lpPlayInfo, 2500000000);
				}
			}
		}
		break;
	case HAQUEST_CODE_FURYOFPHANTOM:
		if (lpTransCommand->LParam == 2)
		{
			if (lpPlayInfo->sCharacterData.iLevel >= 100 && (lpPlayInfo->dwElementaryQuestLogCheck & QUESTBIT_FURYOFPHANTOM) == 0)
			{
				switch (lpTransCommand->SParam)
				{
				case 1:
					SERVERITEM->CreateItem(lpPlayInfo, sinWA1 | sin20, lpPlayInfo->sCharacterData.iClass, ITEM_UNIQUE_CODE_QUEST);
					break;
				case 2:
					SERVERITEM->CreateItem(lpPlayInfo, sinWC1 | sin20, lpPlayInfo->sCharacterData.iClass, ITEM_UNIQUE_CODE_QUEST);
					break;
				case 3:
					SERVERITEM->CreateItem(lpPlayInfo, sinWH1 | sin21, lpPlayInfo->sCharacterData.iClass, ITEM_UNIQUE_CODE_QUEST);
					break;
				case 4:
					SERVERITEM->CreateItem(lpPlayInfo, sinWP1 | sin21, lpPlayInfo->sCharacterData.iClass, ITEM_UNIQUE_CODE_QUEST);
					break;
				case 5:
					SERVERITEM->CreateItem(lpPlayInfo, sinWS1 | sin22, lpPlayInfo->sCharacterData.iClass, ITEM_UNIQUE_CODE_QUEST);
					break;
				case 6:
					SERVERITEM->CreateItem(lpPlayInfo, sinWS2 | sin23, lpPlayInfo->sCharacterData.iClass, ITEM_UNIQUE_CODE_QUEST);
					break;
				case 7:
					SERVERITEM->CreateItem(lpPlayInfo, sinWT1 | sin21, lpPlayInfo->sCharacterData.iClass, ITEM_UNIQUE_CODE_QUEST);
					break;
				case 8:
					SERVERITEM->CreateItem(lpPlayInfo, sinWM1 | sin21, lpPlayInfo->sCharacterData.iClass, ITEM_UNIQUE_CODE_QUEST);
					break;
				case 9:
					SERVERITEM->CreateItem(lpPlayInfo, sinWD1 | sin21, lpPlayInfo->sCharacterData.iClass, ITEM_UNIQUE_CODE_QUEST);
					break;
				case 10:
					SERVERITEM->CreateItem(lpPlayInfo, sinWN1 | sin21, lpPlayInfo->sCharacterData.iClass, ITEM_UNIQUE_CODE_QUEST);
					break;
				}
				lpPlayInfo->dwElementaryQuestLogCheck |= QUESTBIT_FURYOFPHANTOM;
			}
		}
		break;
	}
	return TRUE;
}
int	rsDeleteClientItem(User *lpPlayInfo, Item *lpItem)
{
	TRANS_ITEM_CODE	TransItemCode;

	TransItemCode.code = smTRANSCODE_ERRORITEM;
	TransItemCode.size = sizeof(TRANS_ITEM_CODE);
	TransItemCode.dwFlag = FALSE;
	TransItemCode.dwHead = lpItem->iChk1;
	TransItemCode.dwChkSum = lpItem->iChk2;
	TransItemCode.dwItemCode = lpItem->sItemID.ToInt();
	TransItemCode.dwTime = 0;

	SENDPACKET(lpPlayInfo, &TransItemCode);

	return TRUE;
}
int	rsDeleteClientItem(User *lpPlayInfo, DWORD dwCode, DWORD dwHead, DWORD dwChkSum)
{
	TRANS_ITEM_CODE	TransItemCode;

	TransItemCode.code = smTRANSCODE_ERRORITEM;
	TransItemCode.size = sizeof(TRANS_ITEM_CODE);
	TransItemCode.dwFlag = FALSE;
	TransItemCode.dwHead = dwHead;
	TransItemCode.dwChkSum = dwChkSum;
	TransItemCode.dwItemCode = dwCode;
	TransItemCode.dwTime = 0;

	SENDPACKET(lpPlayInfo, &TransItemCode);

	return TRUE;
}
int rsRecvAgingUpgradeItem(User	*lpPlayInfo, TRANS_ITEMINFO *lpTransItemInfo)
{
	Item sItemInfo;

	char szMessage[256] = { 0 };

	if (CheckItemForm(&lpTransItemInfo->sItem) == FALSE)
		return FALSE;

	if (SERVERITEM->DeleteItemInventory(lpPlayInfo,
		lpTransItemInfo->sItem.sItemID.ToInt(),
		lpTransItemInfo->sItem.iChk1,
		lpTransItemInfo->sItem.iChk2) == FALSE)
		return FALSE;
	memcpy(&sItemInfo, &lpTransItemInfo->sItem, sizeof(Item));

	lpTransItemInfo->sItem.dwCreateTime = 0;
	sinSetAgingItemIncreState(&lpTransItemInfo->sItem);

	SERVERITEM->AddItemInventory(lpPlayInfo, lpTransItemInfo->sItem.sItemID.ToInt(), lpTransItemInfo->sItem.iChk1, lpTransItemInfo->sItem.iChk2);

	if (lpTransItemInfo->sItem.sAgeLevel >= 14)
	{
		wsprintf(szMessage, "> %s aged %s to %d", lpPlayInfo->szCharacterName, lpTransItemInfo->sItem.szItemName, lpTransItemInfo->sItem.sAgeLevel);
	}

	rsSaveAgingItemToHDD(&lpTransItemInfo->sItem);

	RecordAgingItem(lpPlayInfo, &sItemInfo, &lpTransItemInfo->sItem, TRUE);

	rsRecord_ItemLog_Change(lpPlayInfo, sItemInfo.sItemID.ToInt(), sItemInfo.iChk1, sItemInfo.iChk2, lpTransItemInfo->sItem.sItemID.ToInt(), lpTransItemInfo->sItem.iChk1, lpTransItemInfo->sItem.iChk2, ITEMLOG_AGINGUP);

	SENDPACKET(lpPlayInfo, lpTransItemInfo);

	return 0;
}

//¶ÍÔìÐ­Òé
int rsRecvAgingItem(User *lpPlayInfo, sCRAFTITEM_SERVER *pCraftItem_Server)
{
	cAGING		ccItem;
	Item	sItemInfo;
	smTRANS_COMMAND	smTransCommand;
	smTRANS_COMMAND_EX	smTransCommandEx;
	int cnt;
	int	ErrorFlag;
	int Price;
	int	QuestMode;
	int	AgingCnt, AgingLog;

	char szMessage[256] = { 0 };

	ErrorFlag = 0;

	rsRecord_ItemLost(lpPlayInfo, pCraftItem_Server->SheltomCode, pCraftItem_Server->Head, pCraftItem_Server->CheckSum, ITEMLOG_AGINGLOST);

	for (cnt = 0; cnt < 12; cnt++)
	{
		if (pCraftItem_Server->SheltomCode[cnt])
		{
			if (SERVERITEM->DeleteItemInventory(lpPlayInfo,
				pCraftItem_Server->SheltomCode[cnt],
				pCraftItem_Server->Head[cnt],
				pCraftItem_Server->CheckSum[cnt]) == FALSE)
			{
				smTransCommandEx.WParam = 8000;
				smTransCommandEx.WxParam = 70;
				smTransCommandEx.LxParam = (int)"*AGING SHELTON*";
				smTransCommandEx.LParam = pCraftItem_Server->SheltomCode[cnt];
				smTransCommandEx.SParam = pCraftItem_Server->Head[cnt];
				smTransCommandEx.EParam = pCraftItem_Server->CheckSum[cnt];
				RecordHackLogFile(lpPlayInfo, &smTransCommandEx);
				ErrorFlag++;

				pCraftItem_Server->SheltomCode[cnt] = 0;
			}
			SaveThrowItem(lpPlayInfo, pCraftItem_Server->SheltomCode[cnt], pCraftItem_Server->Head[cnt], pCraftItem_Server->CheckSum[cnt]);
		}
	}

	memcpy(&sItemInfo, &pCraftItem_Server->DesCraftItem.sItem, sizeof(Item));

	Price = ((sItemInfo.sAgeLevel + 1) * rsGetMoney(sItemInfo.sItemID.ToInt(), TRUE)) / 2;

	CurrencyLog.int64_AgingMoney += Price;

	if (sItemInfo.eCraftType != ITEMCRAFTTYPE_QuestWeapon)
	{
		if (lpPlayInfo->GetGold() < Price)
		{
			smTransCommand.WParam = 8010;
			smTransCommand.LParam = 70;
			smTransCommand.SParam = lpPlayInfo->GetGold();
			smTransCommand.EParam = Price;
			RecordHackLogFile(lpPlayInfo, &smTransCommand);

			SERVERUSER->SetServerUserGold(lpPlayInfo, 0, WHEREID_Aging);
			ErrorFlag++;
		}
		else
		{
			SERVERUSER->SubServerUserGold(lpPlayInfo, Price, WHEREID_Aging);
			lpPlayInfo->UnsaveMoney = lpPlayInfo->GetGold();
		}
	}

	if (CheckItemForm(&sItemInfo) == FALSE || CheckMixItem(&sItemInfo) == FALSE)
	{
		sAging_Recv.Result = FALSE;
		sAging_Recv.size = 32;

		SENDPACKET(lpPlayInfo, &sAging_Recv);

		smTransCommand.WParam = 99000;
		smTransCommand.SParam = 0;
		smTransCommand.LParam = 1;
		RecordHackLogFile(lpPlayInfo, &smTransCommand);

		return TRUE;
	}

	if ((sItemInfo.sItemID.ToItemType()) == sinMA1)
		QuestMode = TRUE;
	else
	{
		if (lpPlayInfo->iGameLevel == GAMELEVEL_Four)
			QuestMode = -1;
		else
			QuestMode = FALSE;
	}

	// ¶ÍÔìÔöÇ¿ÎïÆ·
	if (pCraftItem_Server->A_StoneItemCode)
	{
		if ((pCraftItem_Server->A_StoneItemCode == (sinBI1 | sin10) || pCraftItem_Server->A_StoneItemCode == (sinBI1 | sin11) || pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin66) || pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin67) || pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin68) || pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin78) || pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin79) || pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin80) || pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin81)) &&
			SERVERITEM->DeleteItemInventory(lpPlayInfo,
				pCraftItem_Server->A_StoneItemCode,
				pCraftItem_Server->A_StoneHead,
				pCraftItem_Server->A_StoneCheckSum))
		{
			rsRecord_ItemLog2(lpPlayInfo, pCraftItem_Server->A_StoneItemCode, pCraftItem_Server->A_StoneHead, pCraftItem_Server->A_StoneCheckSum, ITEMLOG_AGINGLOST);

			SaveThrowItem(lpPlayInfo, pCraftItem_Server->A_StoneItemCode, pCraftItem_Server->A_StoneHead, pCraftItem_Server->A_StoneCheckSum);
		}
		else
		{
			smTransCommandEx.WParam = 8000;
			smTransCommandEx.WxParam = 70;
			smTransCommandEx.LxParam = (int)"Aging Stone";
			smTransCommandEx.LParam = pCraftItem_Server->A_StoneItemCode;
			smTransCommandEx.SParam = pCraftItem_Server->A_StoneHead;
			smTransCommandEx.EParam = pCraftItem_Server->A_StoneCheckSum;
			RecordHackLogFile(lpPlayInfo, &smTransCommandEx);

			pCraftItem_Server->A_StoneItemCode = 0;
		}
	}
	else
		pCraftItem_Server->A_StoneItemCode = 0;

	ccItem.sinRecvAgingItem(pCraftItem_Server);
	cnt = ccItem.AgingItem(QuestMode);

	// Èç¹û³öÏÖ´íÎó
	if (ErrorFlag)
		sAging_Recv.Result = FALSE;

	if (SERVERITEM->DeleteItemInventory(lpPlayInfo,
		sItemInfo.sItemID.ToInt(),
		sItemInfo.iChk1,
		sItemInfo.iChk2) == FALSE)
	{

		sAging_Recv.size = 32;
		sAging_Recv.Result = FALSE;

		smTransCommandEx.WParam = 8000;
		smTransCommandEx.WxParam = 70;
		smTransCommandEx.LxParam = (int)sItemInfo.szItemName;
		smTransCommandEx.LParam = sItemInfo.sItemID.ToInt();
		smTransCommandEx.SParam = sItemInfo.iChk1;
		smTransCommandEx.EParam = sItemInfo.iChk2;
		RecordHackLogFile(lpPlayInfo, &smTransCommandEx);
	}

	sAging_Recv.code = smTRANSCODE_AGINGITEM;

	if (sAging_Recv.Result)
	{
		// Èç¹ûÊÇÈÎÎñÎïÆ·
		if (QuestMode == TRUE)
		{
			auto pDefItem = SERVERITEM->FindItemDefByCode(sAging_Recv.DesCraftItem.sItem.sItemID.ToInt());

			if (pDefItem)
			{
				SERVERITEM->CreateItem(&sAging_Recv.DesCraftItem.sItem, pDefItem);
			}
		}

		ReformItem(&sAging_Recv.DesCraftItem.sItem);
		sAging_Recv.size = sizeof(ItemData) + 32;

		SERVERITEM->AddItemInventory(lpPlayInfo, sAging_Recv.DesCraftItem.sItem.sItemID.ToInt(), sAging_Recv.DesCraftItem.sItem.iChk1, sAging_Recv.DesCraftItem.sItem.iChk2);

		if (QuestMode != TRUE)
		{
			RecordAgingItem(lpPlayInfo, &sItemInfo, &sAging_Recv.DesCraftItem.sItem, FALSE);

			AgingCnt = sAging_Recv.DesCraftItem.sItem.sAgeLevel - sItemInfo.sAgeLevel;
			AgingLog = ITEMLOG_AGING;

			switch (sAging_Recv.Result)
			{
			case 7:
				AgingLog = ITEMLOG_AGING_20UP;
				wsprintf(szMessage,
					"> %s aged %s to %d",
					lpPlayInfo->szCharacterName,
					sAging_Recv.DesCraftItem.sItem.szItemName,
					sAging_Recv.DesCraftItem.sItem.sAgeLevel);
				SendQuickNoticeMessage(szMessage);
				break;
			case 6:
				AgingLog = ITEMLOG_AGING_15UP;
				wsprintf(szMessage,
					"> %s aged %s to %d",
					lpPlayInfo->szCharacterName,
					sAging_Recv.DesCraftItem.sItem.szItemName,
					sAging_Recv.DesCraftItem.sItem.sAgeLevel);
				SendQuickNoticeMessage(szMessage);
				break;
			case 5:
				AgingLog = ITEMLOG_AGING_10UP;
				break;
			case 4:
				AgingLog = ITEMLOG_AGING_2UP;
				break;
			case 3:
				AgingLog = ITEMLOG_AGING;
				break;
			case 1:
				AgingLog = ITEMLOG_AGING_1DOWN;
				break;
			case 2:
				AgingLog = ITEMLOG_AGING_2DOWN;
				break;
			}

			rsRecord_ItemLog_Change(lpPlayInfo,
				sItemInfo.sItemID.ToInt(),
				sItemInfo.iChk1,
				sItemInfo.iChk2,
				sAging_Recv.DesCraftItem.sItem.sItemID.ToInt(),
				sAging_Recv.DesCraftItem.sItem.iChk1,
				sAging_Recv.DesCraftItem.sItem.iChk2,
				AgingLog);
			rsSaveAgingItemToHDD(&sAging_Recv.DesCraftItem.sItem);
		}

		SaveThrowItem(lpPlayInfo, sItemInfo.sItemID.ToInt(), sItemInfo.iChk1, sItemInfo.iChk2);
	}
	else
	{
		sAging_Recv.size = 32;

		if (QuestMode != TRUE)
		{
			RecordAgingItem(lpPlayInfo, &sItemInfo, 0, FALSE);
			rsRecord_ItemLog2(lpPlayInfo, sItemInfo.sItemID.ToInt(),
				sItemInfo.iChk1,
				sItemInfo.iChk2,
				ITEMLOG_AGINGLOST);
		}
	}

	SENDPACKET(lpPlayInfo, &sAging_Recv);

	return TRUE;
}


//½ÓÊÜºÏ³ÉÐ­Òé
int rsRecvCraftItem(User *lpPlayInfo, sCRAFTITEM_SERVER *pCraftItem_Server)
{
	cCRAFTITEM	ccItem;
	Item	sItemInfo;
	smTRANS_COMMAND	smTransCommand;
	smTRANS_COMMAND_EX	smTransCommandEx;

	int cnt;
	int	ErrorFlag;
	int Result;
	DWORD ItemCraftType = 0;
	int RandNum = 0;

	ErrorFlag = 0;

	for (cnt = 0; cnt < 12; cnt++)
	{
		if ((pCraftItem_Server->SheltomCode[cnt] & sinITEM_MASK2) == sinSE1)
		{
			ItemCraftType = sinSE1;
			break;
		}
	}
	if ((pCraftItem_Server->DesCraftItem.sBaseItemID.ToInt() & sinITEM_MASK2) != sinWA1 &&
		(pCraftItem_Server->DesCraftItem.sBaseItemID.ToInt() & sinITEM_MASK2) != sinWC1 &&
		(pCraftItem_Server->DesCraftItem.sBaseItemID.ToInt() & sinITEM_MASK2) != sinWH1 &&
		(pCraftItem_Server->DesCraftItem.sBaseItemID.ToInt() & sinITEM_MASK2) != sinWM1 &&
		(pCraftItem_Server->DesCraftItem.sBaseItemID.ToInt() & sinITEM_MASK2) != sinWP1 &&
		(pCraftItem_Server->DesCraftItem.sBaseItemID.ToInt() & sinITEM_MASK2) != sinWS1 &&
		(pCraftItem_Server->DesCraftItem.sBaseItemID.ToInt() & sinITEM_MASK2) != sinWS2 &&
		(pCraftItem_Server->DesCraftItem.sBaseItemID.ToInt() & sinITEM_MASK2) != sinWT1 &&
		(pCraftItem_Server->DesCraftItem.sBaseItemID.ToInt() & sinITEM_MASK2) != sinWD1 &&
		(pCraftItem_Server->DesCraftItem.sBaseItemID.ToInt() & sinITEM_MASK2) != sinWN1 &&
		(pCraftItem_Server->DesCraftItem.sBaseItemID.ToInt() & sinITEM_MASK2) != sinDA1 &&
		(pCraftItem_Server->DesCraftItem.sBaseItemID.ToInt() & sinITEM_MASK2) != sinDA2 &&
		(pCraftItem_Server->DesCraftItem.sBaseItemID.ToInt() & sinITEM_MASK2) != sinDS1 &&
		(pCraftItem_Server->DesCraftItem.sBaseItemID.ToInt() & sinITEM_MASK2) != sinOM1 &&
		(pCraftItem_Server->DesCraftItem.sBaseItemID.ToInt() & sinITEM_MASK2) != sinDB1 &&
		(pCraftItem_Server->DesCraftItem.sBaseItemID.ToInt() & sinITEM_MASK2) != sinDG1 &&
		(pCraftItem_Server->DesCraftItem.sBaseItemID.ToInt() & sinITEM_MASK2) != sinOA1 &&
		(pCraftItem_Server->DesCraftItem.sBaseItemID.ToInt() & sinITEM_MASK2) != sinOA2 &&
		(pCraftItem_Server->DesCraftItem.sBaseItemID.ToInt() & sinITEM_MASK2) != sinOR1 &&
		(pCraftItem_Server->DesCraftItem.sBaseItemID.ToInt() & sinITEM_MASK2) != sinOS1)
	{
		ErrorFlag++;
	}

	if (ItemCraftType == sinSE1)
		rsRecord_ItemLost(lpPlayInfo, pCraftItem_Server->SheltomCode, pCraftItem_Server->Head, pCraftItem_Server->CheckSum, ITEMLOG_LOST_RECON);
	else
		rsRecord_ItemLost(lpPlayInfo, pCraftItem_Server->SheltomCode, pCraftItem_Server->Head, pCraftItem_Server->CheckSum, ITEMLOG_MIXLOST);

	for (cnt = 0; cnt < 12; cnt++)
	{
		if (pCraftItem_Server->SheltomCode[cnt])
		{
			if (SERVERITEM->DeleteItemInventory(lpPlayInfo,
				pCraftItem_Server->SheltomCode[cnt],
				pCraftItem_Server->Head[cnt],
				pCraftItem_Server->CheckSum[cnt]) == FALSE)
			{
				smTransCommandEx.WParam = 8000;
				smTransCommandEx.WxParam = 50;
				smTransCommandEx.LxParam = (int)"*MIXTRUE SHELTON*";
				smTransCommandEx.LParam = pCraftItem_Server->SheltomCode[cnt];
				smTransCommandEx.SParam = pCraftItem_Server->Head[cnt];
				smTransCommandEx.EParam = pCraftItem_Server->CheckSum[cnt];
				RecordHackLogFile(lpPlayInfo, &smTransCommandEx);
				ErrorFlag++;

				pCraftItem_Server->SheltomCode[cnt] = 0;
			}

			SaveThrowItem(lpPlayInfo, pCraftItem_Server->SheltomCode[cnt], pCraftItem_Server->Head[cnt], pCraftItem_Server->CheckSum[cnt]);
		}
	}

	memcpy(&sItemInfo, &pCraftItem_Server->DesCraftItem.sItem, sizeof(Item));

	//È¡³öÄ¬ÈÏµÄÎïÆ·µÄ½ðÇ® ·ÀÖ¹Ë¢Ç®

	int Price = rsGetMoney(sItemInfo.sItemID.ToInt(), TRUE);

	if (sItemInfo.iSalePrice < 0 || lpPlayInfo->GetGold() < sItemInfo.iSalePrice)
	{
		smTransCommand.WParam = 8010;
		smTransCommand.LParam = 50;
		smTransCommand.SParam = lpPlayInfo->GetGold();
		smTransCommand.EParam = sItemInfo.iSalePrice;
		RecordHackLogFile(lpPlayInfo, &smTransCommand);

		SERVERUSER->SetServerUserGold(lpPlayInfo,0, WHEREID_MixItem);
		ErrorFlag++;
	}
	else
	{
		SERVERUSER->SubServerUserGold(lpPlayInfo, Price, WHEREID_MixItem);
		lpPlayInfo->UnsaveMoney = lpPlayInfo->GetGold();
	}

	if (CheckItemForm(&sItemInfo) == FALSE || sItemInfo.eCraftType != 0 || CheckMixItem(&sItemInfo) == FALSE)
	{
		sCraftItem_Recv.Result = FALSE;
		sCraftItem_Recv.size = 32;

		SENDPACKET(lpPlayInfo, &sCraftItem_Recv);

		smTransCommand.WParam = 99000;
		smTransCommand.SParam = 0;
		smTransCommand.LParam = 0;
		RecordHackLogFile(lpPlayInfo, &smTransCommand);
		return TRUE;
	}

	if (pCraftItem_Server->A_StoneItemCode)
	{
		if ((pCraftItem_Server->A_StoneItemCode == (sinBI1 | sin90)) &&
			SERVERITEM->DeleteItemInventory(lpPlayInfo,
				pCraftItem_Server->A_StoneItemCode,
				pCraftItem_Server->A_StoneHead,
				pCraftItem_Server->A_StoneCheckSum))
		{
			rsRecord_ItemLog2(lpPlayInfo, pCraftItem_Server->A_StoneItemCode, pCraftItem_Server->A_StoneHead, pCraftItem_Server->A_StoneCheckSum, ITEMLOG_LOST_RECON);

			SaveThrowItem(lpPlayInfo, pCraftItem_Server->A_StoneItemCode, pCraftItem_Server->A_StoneHead, pCraftItem_Server->A_StoneCheckSum);

			spJobCode = lpPlayInfo->sCharacterData.iClass;
		}
		else
		{
			smTransCommandEx.WParam = 8000;
			smTransCommandEx.WxParam = 70;
			smTransCommandEx.LxParam = (int)"Mix Stone";
			smTransCommandEx.LParam = pCraftItem_Server->A_StoneItemCode;
			smTransCommandEx.SParam = pCraftItem_Server->A_StoneHead;
			smTransCommandEx.EParam = pCraftItem_Server->A_StoneCheckSum;
			RecordHackLogFile(lpPlayInfo, &smTransCommandEx);

			pCraftItem_Server->A_StoneItemCode = 0;
		}
	}
	else
		pCraftItem_Server->A_StoneItemCode = 0;

	ccItem.sinRecvCraftItem(pCraftItem_Server);
	Result = ccItem.MixingItem();

	if (ErrorFlag)
		sCraftItem_Recv.Result = FALSE;

	if (Result == 2000)
	{
		auto pDefItem = SERVERITEM->FindItemDefByCode(sCraftItem_Recv.DesCraftItem.sItem.sItemID.ToInt());

		if (pDefItem)
		{
			SERVERITEM->CreateItem(&sCraftItem_Recv.DesCraftItem.sItem, pDefItem);
		}
	}

	sCraftItem_Recv.code = smTRANSCODE_CRAFTITEM;

	if (sCraftItem_Recv.Result == TRUE)
	{
		ReformItem(&sCraftItem_Recv.DesCraftItem.sItem);
		sCraftItem_Recv.size = sizeof(ItemData) + 32;

		if (SERVERITEM->DeleteItemInventory(lpPlayInfo,
			sItemInfo.sItemID.ToInt(),
			sItemInfo.iChk1,
			sItemInfo.iChk2))
		{
			SERVERITEM->AddItemInventory(lpPlayInfo, sCraftItem_Recv.DesCraftItem.sItem.sItemID.ToInt(), sCraftItem_Recv.DesCraftItem.sItem.iChk1, sCraftItem_Recv.DesCraftItem.sItem.iChk2);

			RecordMixItem(lpPlayInfo, &sItemInfo, &sCraftItem_Recv.DesCraftItem.sItem);

			if (ItemCraftType == sinSE1)
				rsRecord_ItemLog_Change(lpPlayInfo,
					sItemInfo.sItemID.ToInt(),
					sItemInfo.iChk1,
					sItemInfo.iChk2,
					sCraftItem_Recv.DesCraftItem.sItem.sItemID.ToInt(),
					sCraftItem_Recv.DesCraftItem.sItem.iChk1,
					sCraftItem_Recv.DesCraftItem.sItem.iChk2, ITEMLOG_GET_RECON);
			else
				rsRecord_ItemLog_Change(lpPlayInfo,
					sItemInfo.sItemID.ToInt(),
					sItemInfo.iChk1,
					sItemInfo.iChk2,
					sCraftItem_Recv.DesCraftItem.sItem.sItemID.ToInt(),
					sCraftItem_Recv.DesCraftItem.sItem.iChk1,
					sCraftItem_Recv.DesCraftItem.sItem.iChk2, ITEMLOG_MIXING);

			rsSaveAgingItemToHDD(&sCraftItem_Recv.DesCraftItem.sItem);
		}
		else
		{
			sCraftItem_Recv.size = 32;
			sCraftItem_Recv.Result = FALSE;

			smTransCommandEx.WParam = 8000;
			smTransCommandEx.WxParam = 50;
			smTransCommandEx.LxParam = (int)sItemInfo.szItemName;
			smTransCommandEx.LParam = sItemInfo.sItemID.ToInt();
			smTransCommandEx.SParam = sItemInfo.iChk1;
			smTransCommandEx.EParam = sItemInfo.iChk2;
			RecordHackLogFile(lpPlayInfo, &smTransCommandEx);
		}
		SaveThrowItem(lpPlayInfo, sItemInfo.sItemID.ToInt(), sItemInfo.iChk1, sItemInfo.iChk2);
	}
	else
		sCraftItem_Recv.size = 32;

	SENDPACKET(lpPlayInfo, &sCraftItem_Recv);

	return TRUE;
}

// pluto Á¦·Ã µ¥ÀÌÅ¸ ¹ÞÀ½
int rsRecvSmeltingItem(User *lpPlayInfo, sSMELTINGITEM_SERVER *pSmeltingItem_Server)
{
	CSmeltingItem ccItem;
	//sITEMINFO	sItemInfo;
	//smTRANS_COMMAND	smTransCommand;
	smTRANS_COMMAND_EX	smTransCommandEx;

	int cnt;
	int	ErrorFlag;
	//int Result;
	DWORD ItemSmeltingType = 0;

	bool bFirst_Ore = TRUE;
	bool bOre_OK = TRUE;
	DWORD first_Ore = 0;
	DWORD Next_Ore = 0;
	int ore_num = 0;
	int crystal_num = 0;

	bool bFirst_Sheltom = TRUE;
	bool bSheltom_OK = TRUE;
	DWORD first_Sheltom = 0;
	DWORD Next_Sheltom = 0;

	ErrorFlag = 0;

	//¾ÆÀÌÅÛ ·Î±× Á¦·Ã¿¡ »ç¿ëµÈ ½©ÅÒ 
	rsRecord_SmeltingItemLog(lpPlayInfo, pSmeltingItem_Server->SmeltingCode, pSmeltingItem_Server->Head, pSmeltingItem_Server->CheckSum, ITEMLOG_SMELTING_LOST);
	for (cnt = 0; cnt < 3; cnt++) // Àåº° - Á¦·Ã ½Ã½ºÅÛ ¼öÁ¤
	{
		if (pSmeltingItem_Server->SmeltingCode[cnt])
		{
			if ((pSmeltingItem_Server->SmeltingCode[cnt] & sinITEM_MASK2) == sinPR1)	// ±¤¼®
			{
				if (ore_num < 3)
				{
					ItemSmeltingType = sinPR1;
					ore_num++; // 4¹Ì¸¸ ÀÌ¸é ½ÇÆÐ´Ù
				}
			}
			else if ((pSmeltingItem_Server->SmeltingCode[cnt] & sinITEM_MASK2) == sinPR2)	// ¼öÁ¤
			{
				if (crystal_num < 3)
				{
					ItemSmeltingType = sinPR2;
					crystal_num++;
				}

			}
			if (SERVERITEM->DeleteItemInventory(lpPlayInfo,
				pSmeltingItem_Server->SmeltingCode[cnt],
				pSmeltingItem_Server->Head[cnt],
				pSmeltingItem_Server->CheckSum[cnt]) == FALSE)
			{
				if (ItemSmeltingType == sinPR1)
				{
					//·Î±×¿¡ ±â·Ï
					smTransCommandEx.WParam = 8000;
					smTransCommandEx.WxParam = 50;
					smTransCommandEx.LxParam = (int)"*SMELTING ORE*";
					smTransCommandEx.LParam = pSmeltingItem_Server->SmeltingCode[cnt];
					smTransCommandEx.SParam = pSmeltingItem_Server->Head[cnt];
					smTransCommandEx.EParam = pSmeltingItem_Server->CheckSum[cnt];
					RecordHackLogFile(lpPlayInfo, &smTransCommandEx);
				}
				else if (ItemSmeltingType == sinPR2)
				{
					//·Î±×¿¡ ±â·Ï
					smTransCommandEx.WParam = 8000;
					smTransCommandEx.WxParam = 50;
					smTransCommandEx.LxParam = (int)"*SMELTING CRYSTAL*";
					smTransCommandEx.LParam = pSmeltingItem_Server->SmeltingCode[cnt];
					smTransCommandEx.SParam = pSmeltingItem_Server->Head[cnt];
					smTransCommandEx.EParam = pSmeltingItem_Server->CheckSum[cnt];
					RecordHackLogFile(lpPlayInfo, &smTransCommandEx);
				}
				ErrorFlag++;

				pSmeltingItem_Server->SmeltingCode[cnt] = 0;			//±¤¼®Á¦°Å
			}
			else
			{
				if (bFirst_Ore)	// Ã¹ ¹øÂ° ±¤¼®¸¸
				{
					first_Ore = pSmeltingItem_Server->SmeltingCode[cnt];
					Next_Ore = pSmeltingItem_Server->SmeltingCode[cnt];
					bFirst_Ore = FALSE;
				}
				else // µÎ¹øÂ° ±¤¼®ºÎÅÍ Âß~~
				{
					Next_Ore = pSmeltingItem_Server->SmeltingCode[cnt];
				}
				if (first_Ore != Next_Ore) // ±¤¼® ¼¯¿© ÀÖÀ¸¸é ½ÇÆÐ
				{
					bOre_OK = FALSE;
					ErrorFlag++;
				}
			}
			SaveThrowItem(lpPlayInfo, pSmeltingItem_Server->SmeltingCode[cnt],
				pSmeltingItem_Server->Head[cnt], pSmeltingItem_Server->CheckSum[cnt]);
		}
	}

	if (ItemSmeltingType == sinPR1 && ore_num != 3) // ±¤¼® 4°³¹Ì¸¸ÀÌ¸é ½ÇÆÐ´Ù // Àåº° - Á¦·Ã ½Ã½ºÅÛ ¼öÁ¤
	{
		bOre_OK = FALSE;
		ErrorFlag++;
	}
	else if (ItemSmeltingType == sinPR2 && crystal_num != 3) // ¼öÁ¤ 4°³¹Ì¸¸ÀÌ¸é ½ÇÆÐ  // Àåº° - Á¦·Ã ½Ã½ºÅÛ ¼öÁ¤
	{
		bOre_OK = FALSE;
		ErrorFlag++;
	}

	if (pSmeltingItem_Server->SmeltingCode[4])
	{
		if (SERVERITEM->DeleteItemInventory(lpPlayInfo,
			pSmeltingItem_Server->SmeltingCode[4],
			pSmeltingItem_Server->Head[4],
			pSmeltingItem_Server->CheckSum[4]) == FALSE)
		{
			//·Î±×¿¡ ±â·Ï
			smTransCommandEx.WParam = 8000;
			smTransCommandEx.WxParam = 50;
			smTransCommandEx.LxParam = (int)"*SMELTING SHELTON*";
			smTransCommandEx.LParam = pSmeltingItem_Server->SmeltingCode[4];
			smTransCommandEx.SParam = pSmeltingItem_Server->Head[4];
			smTransCommandEx.EParam = pSmeltingItem_Server->CheckSum[4];
			RecordHackLogFile(lpPlayInfo, &smTransCommandEx);
			ErrorFlag++;

			pSmeltingItem_Server->SmeltingCode[4] = 0;			//½©ÅÒÁ¦°Å
		}
		if (bFirst_Sheltom)		// ½©ÅÒ ¿©·¯°³ ÀÏ¶§ Áö±ÝÀº ÇÊ¿ä ¾ø´Âµ¥... -_- 
		{
			first_Sheltom = pSmeltingItem_Server->SmeltingCode[4];
			Next_Sheltom = pSmeltingItem_Server->SmeltingCode[4];
			bFirst_Sheltom = FALSE;
		}
		else
		{
			Next_Sheltom = pSmeltingItem_Server->SmeltingCode[4];
		}
		if (first_Sheltom != Next_Sheltom) // ½©ÅÒ ¼¯¿© ÀÖÀ¸¸é ½ÇÆÐÇÑ´Ù
		{
			bSheltom_OK = FALSE;
			ErrorFlag++;
		}
		SaveThrowItem(lpPlayInfo, pSmeltingItem_Server->SmeltingCode[4],
			pSmeltingItem_Server->Head[4], pSmeltingItem_Server->CheckSum[4]);
	}

	DWORD code = 0;//(sinSE1|sin03);
	if (bOre_OK && bSheltom_OK)
	{
		if ((Next_Ore & sinITEM_MASK2) == sinPR1)
		{
			if (Next_Ore == (sinPR1 | sin01) && Next_Sheltom == (sinOS1 | sin06))		// º¸¶óºû ±¤¼® + Æ®·£½ºÆÐ·Î ½©ÅÒ
			{
				code = (sinPR2 | sin01);		// º¸¶óºû ¼öÁ¤
			}
			else if (Next_Ore == (sinPR1 | sin02) && Next_Sheltom == (sinOS1 | sin07))	// Àººû ±¤¼® + ¸ÓÅ° ½©ÅÒ
			{
				code = (sinPR2 | sin02);		// Àººû ¼öÁ¤
			}
			else if (Next_Ore == (sinPR1 | sin03) && Next_Sheltom == (sinOS1 | sin08))	// ±Ýºû ±¤¼® + µ¥ºñ³× ½©ÅÒ
			{
				code = (sinPR2 | sin03);		// ±Ýºû ¼öÁ¤
			}
			else if (Next_Ore == (sinPR1 | sin04) && Next_Sheltom == (sinOS1 | sin09))	// ÇÏ´Ãºû ±¤¼® + ½ì·¹½ºÅä ½©ÅÒ
			{
				code = (sinPR2 | sin04);		// ÇÏ´Ãºû ¼öÁ¤
			}
			else if (Next_Ore == (sinPR1 | sin05) && Next_Sheltom == (sinOS1 | sin10))	// ³²ºû ±¤¼® + ¹Ì¶óÁö ½©ÅÒ
			{
				code = (sinPR2 | sin05);		// ³²ºû ¼öÁ¤
			}
			else if (Next_Ore == (sinPR1 | sin06) && Next_Sheltom == (sinOS1 | sin11))	// ÁÖÈ²ºû ±¤¼® + ÀÎÆä¸£³ª ½©ÅÒ
			{
				code = (sinPR2 | sin06);		// ÁÖÈ²ºû ¼öÁ¤
			}
			else if (Next_Ore == (sinPR1 | sin07) && Next_Sheltom == (sinOS1 | sin12))	// ºÓÀººû ±¤¼® + ÀÌ´Ï±×¸¶ ½©ÅÒ
			{
				code = (sinPR2 | sin07);		// ºÓÀººû ¼öÁ¤
			}
			else if (Next_Ore == (sinPR1 | sin07) && Next_Sheltom == (sinOS1 | sin13))	// ÃÊ·Ïºû ±¤¼® + º§·ë ½©ÅÒ
			{
				code = (sinPR2 | sin08);		// ÃÊ·Ïºû ¼öÁ¤
			}
		}

		else if ((Next_Ore & sinITEM_MASK2) == sinPR2)
		{
			if (Next_Ore == (sinPR2 | sin01) && Next_Sheltom == (sinOS1 | sin07))		// º¸¶óºû ¼öÁ¤ + ¸ÓÅ° ½©ÅÒ
			{
				switch (rand() % 2)
				{
				case 0:
					code = (sinPR3 | sin01);		// º¸¶óºû ·é(A)
					break;
				case 1:
					code = (sinPR4 | sin01);		// º¸¶óºû ·é(B)
					break;
				}
			}
			else if (Next_Ore == (sinPR2 | sin02) && Next_Sheltom == (sinOS1 | sin08))	// Àººû¼öÁ¤ + µ¥ºñ³× ½©ÅÒ
			{
				switch (rand() % 2)
				{
				case 0:
					code = (sinPR3 | sin02);		// Àººû ·é(A)
					break;
				case 1:
					code = (sinPR4 | sin02);		// Àººû ·é(B)
					break;
				}
			}
			else if (Next_Ore == (sinPR2 | sin03) && Next_Sheltom == (sinOS1 | sin09))	// ±Ýºû ¼öÁ¤ + ½ì·¹½ºÅä ½©ÅÒ
			{
				switch (rand() % 2)
				{
				case 0:
					code = (sinPR3 | sin03);		// ±Ýºû ·é(A)
					break;
				case 1:
					code = (sinPR4 | sin03);		// ±Ýºû ·é(B)
					break;
				}
			}
			else if (Next_Ore == (sinPR2 | sin04) && Next_Sheltom == (sinOS1 | sin10))	// ÇÏ´Ãºû ¼öÁ¤ + ¹Ì¶óÁö ½©ÅÒ
			{
				switch (rand() % 2)
				{
				case 0:
					code = (sinPR3 | sin04);		// ÇÏ´Ãºû ·é(A)
					break;
				case 1:
					code = (sinPR4 | sin04);		// ÇÏ´Ãºû ·é(B)
					break;
				}
			}
			else if (Next_Ore == (sinPR2 | sin05) && Next_Sheltom == (sinOS1 | sin11))	// ³²ºû ¼öÁ¤ + ÀÎÆä¸£³ª ½©ÅÒ
			{
				switch (rand() % 2)
				{
				case 0:
					code = (sinPR3 | sin05);		// ³²ºû ·é(A)
					break;
				case 1:
					code = (sinPR4 | sin05);		// ³²ºû ·é(B)
					break;
				}
			}
			else if (Next_Ore == (sinPR2 | sin06) && Next_Sheltom == (sinOS1 | sin12))	// ÁÖÈ²ºû ¼öÁ¤ + ÀÌ´Ï±×¸¶ ½©ÅÒ
			{
				switch (rand() % 2)
				{
				case 0:
					code = (sinPR3 | sin06);		// ÁÖÈ²ºû ·é(A)
					break;
				case 1:
					code = (sinPR4 | sin06);		// ÁÖÈ²ºû ·é(B)
					break;
				}
			}
			else if (Next_Ore == (sinPR2 | sin07) && Next_Sheltom == (sinOS1 | sin13))	// ºÓÀººû ¼öÁ¤ + º§·ë ½©ÅÒ
			{
				switch (rand() % 2)
				{
				case 0:
					code = (sinPR3 | sin07);		// ºÓÀººû ·é(A)
					break;
				case 1:
					code = (sinPR4 | sin07);		// ºÓÀººû ·é(B)
					break;
				}
			}


			// Àåº° - ·é ¸¸µé±â °ø½Ä
			else if (Next_Ore == (sinPR2 | sin09) && Next_Sheltom == (sinOS1 | sin03))	// ´«ÀÇ °áÁ¤ + ÆÄµ¥¿À = ½º³ë¿ì·é
			{
				switch (rand() % 2)
				{
				case 0:
					code = (sinPR3 | sin09);		// ½º³ë¿ì ·é(A)
					break;
				case 1:
					code = (sinPR4 | sin09);		// ½º³ë¿ì ·é(B)
					break;
				}
			}


			else if (Next_Ore == (sinPR2 | sin10) && Next_Sheltom == (sinOS1 | sin04))	// ½º³ë¿ì ÇÃ¶ó¿ö + ½ºÆÄÅ° = ÇÃ¶ó¿ö·é
			{
				switch (rand() % 2)
				{
				case 0:
					code = (sinPR3 | sin10);		// ÇÃ¶ó¿ö ·é(A)
					break;
				case 1:
					code = (sinPR4 | sin10);		// ÇÃ¶ó¿ö ·é(B)
					break;
				}
			}


			else if (Next_Ore == (sinPR2 | sin11) && Next_Sheltom == (sinOS1 | sin05))	// ÇÏ¾á ´«¹° + ·¹ÀÌ´øÆ® = È­ÀÌÆ®·é
			{
				switch (rand() % 2)
				{
				case 0:
					code = (sinPR3 | sin11);		// È­ÀÌÆ® ·é(A)
					break;
				case 1:
					code = (sinPR4 | sin11);		// È­ÀÌÆ® ·é(B)
					break;
				}
			}

			// Àåº° - ´ëÀåÀåÀÌÀÇ È¥
			else if (Next_Ore == (sinPR2 | sin12) && Next_Sheltom == (sinOS1 | sin03))	// ³ì½¼ ¼öÁ¤ + ÆÄµ¥¿À = ÀÏ·çÀü ·é
			{
				switch (rand() % 2)
				{
				case 0:
					code = (sinPR3 | sin12);		// È­ÀÌÆ® ·é(A)
					break;
				case 1:
					code = (sinPR4 | sin12);		// È­ÀÌÆ® ·é(B)
					break;
				}
			}

			else if (Next_Ore == (sinPR2 | sin13) && Next_Sheltom == (sinOS1 | sin04))	// ¿ø¼® Á¶°¢ + ½ºÆÄÅ° = ¾ÆÀÌµð¾ó ·é
			{
				switch (rand() % 2)
				{
				case 0:
					code = (sinPR3 | sin13);		// È­ÀÌÆ® ·é(A)
					break;
				case 1:
					code = (sinPR4 | sin13);		// È­ÀÌÆ® ·é(B)
					break;
				}
			}

			else if (Next_Ore == (sinPR2 | sin14) && Next_Sheltom == (sinOS1 | sin05))	// °ËÀººû ¼öÁ¤ + ·¹ÀÌ´øÆ® = ºê·¹ÀÌÅ© ·é
			{
				switch (rand() % 2)
				{
				case 0:
					code = (sinPR3 | sin14);		// È­ÀÌÆ® ·é(A)
					break;
				case 1:
					code = (sinPR4 | sin14);		// È­ÀÌÆ® ·é(B)
					break;
				}
			}


			//else if( Next_Ore == (sinPR2|sin08) && Next_Sheltom == (sinOS1|sin14) )	// ÃÊ·Ïºû ¼öÁ¤ + ¿À¸£µµ ½©ÅÒ
			//{
			//	switch( rand()%2 )
			//	{
			//	case 0:
			//		code = (sinPR3|sin08);		// ÃÊ·Ïºû ·é(A)
			//		break:
			//	case 1:
			//		code = (sinPR4|sin08);		// ÃÊ·Ïºû ·é(B)
			//		break;
			//	}
			//}
		}
		else
		{
			ErrorFlag++;
		}

		if (code != 0)
		{
			auto pDefItem = SERVERITEM->FindItemDefByCode(code);

			if (pDefItem)
			{
				SERVERITEM->CreateItem(&pSmeltingItem_Server->DesSmeltingItem.sItem, pDefItem);
			}
		}

	}

	ccItem.sinRecvSmeltingItem(pSmeltingItem_Server);

	if (ErrorFlag)
	{
		sSmeltingItem_Recv.Result = FALSE;
	}
	else
	{
		sSmeltingItem_Recv.Result = TRUE;
	}
	if (sSmeltingItem_Recv.Result == TRUE)
	{
		ReformItem(&sSmeltingItem_Recv.DesSmeltingItem.sItem);
		sSmeltingItem_Recv.size = sizeof(ItemData) + 32;

		SERVERITEM->AddItemInventory(lpPlayInfo, sSmeltingItem_Recv.DesSmeltingItem.sItem.sItemID.ToInt(),
			sSmeltingItem_Recv.DesSmeltingItem.sItem.iChk1,
			sSmeltingItem_Recv.DesSmeltingItem.sItem.iChk2);

		rsRecord_ItemLog2(lpPlayInfo, sSmeltingItem_Recv.DesSmeltingItem.sItem.sItemID.ToInt(), sSmeltingItem_Recv.DesSmeltingItem.sItem.iChk1,
			sSmeltingItem_Recv.DesSmeltingItem.sItem.iChk2, ITEMLOG_SMELTING_GET);
		// Á¦·Ã ±â·Ï
		RecordSmeltingItem(lpPlayInfo, &sSmeltingItem_Recv.DesSmeltingItem.sItem);

	}
	else
	{
		sSmeltingItem_Recv.size = 32;
	}

	sSmeltingItem_Recv.code = smTRANSCODE_SMELTINGITEM;

	SENDPACKET(lpPlayInfo, &sSmeltingItem_Recv);

	return TRUE;
}

// pluto Á¦ÀÛ ¾ÆÀÌÅÛ Á¤º¸ // Àåº° - ´ëÀåÀåÀÌÀÇ È¥
int ManufactureItemInfo(User *lpPlayInfo)
{
	// Àåº° - ´ëÀåÀåÀÌÀÇ È¥
	DWORD	dwItem = 0;

	// ÇÁ¸®½ºÆ¼½º ÀÏ °æ¿ì
	if (lpPlayInfo->sCharacterData.iClass == CHARACTERCLASS_Priestess) dwItem = (sinDA2 | sin52);
	// ¸ÞÁö¼Ç ÀÏ °æ¿ì
	else if (lpPlayInfo->sCharacterData.iClass == CHARACTERCLASS_Magician) dwItem = (sinDA2 | sin51);
	// ¾ÆÃ³, ¾ÆÆ²¶õÅ¸ ÀÏ °æ¿ì
	else if (lpPlayInfo->sCharacterData.iClass == CHARACTERCLASS_Archer || lpPlayInfo->sCharacterData.iClass == CHARACTERCLASS_Atalanta) dwItem = (sinDA1 | sin52);
	// ÆÄÀÌÅÍ, ÆÄÀÌÅ©¸Ç, ¸ÞÄ«´Ï¼Ç, ³ªÀÌÆ® ÀÏ °æ¿ì
	else dwItem = (sinDA1 | sin51);

	DWORD CreateItemCode[176] = { (sinWA1 | sin14), (sinWC1 | sin14), (sinWH1 | sin15), (sinWP1 | sin15), (sinWS1 | sin16), (sinWS2 | sin17), (sinWT1 | sin15), (sinWM1 | sin15),  // ÀØÇôÁø ·¹½ÃÇÇ ¹«±¸
									(sinWA1 | sin15), (sinWC1 | sin15), (sinWH1 | sin16), (sinWP1 | sin16), (sinWS1 | sin17), (sinWS2 | sin18), (sinWT1 | sin16), (sinWM1 | sin16), // °í´ëÀÇ ·¹½ÃÇÇ ¹«±¸
									(sinWA1 | sin16), (sinWC1 | sin16), (sinWH1 | sin17), (sinWP1 | sin17), (sinWS1 | sin18), (sinWS2 | sin19), (sinWT1 | sin17), (sinWM1 | sin17), // ´ëÁöÀÇ ¹«±¸
									(sinWA1 | sin17), (sinWC1 | sin17), (sinWH1 | sin18), (sinWP1 | sin18), (sinWS1 | sin19), (sinWS2 | sin20), (sinWT1 | sin18), (sinWM1 | sin18), // ¾îµÒÀÇ ·¹½ÃÇÇ ¹«±¸
									(sinWA1 | sin18), (sinWC1 | sin18), (sinWH1 | sin19), (sinWP1 | sin19), (sinWS1 | sin20), (sinWS2 | sin21), (sinWT1 | sin19), (sinWM1 | sin19), // È­¿°ÀÇ ·¹½ÃÇÇ ¹«±¸
									(sinWA1 | sin19), (sinWC1 | sin19), (sinWH1 | sin20), (sinWP1 | sin20), (sinWS1 | sin21), (sinWS2 | sin22), (sinWT1 | sin20), (sinWM1 | sin20), // ¹Ù¶÷ÀÇ ·¹½ÃÇÇ ¹«±¸
									(sinWA1 | sin21), (sinWC1 | sin21), (sinWH1 | sin22), (sinWP1 | sin22), (sinWS1 | sin23), (sinWS2 | sin24), (sinWT1 | sin22), (sinWM1 | sin22), // ÅÂ¾çÀÇ ·¹½ÃÇÇ ¹«±¸
									(sinWA1 | sin22), (sinWC1 | sin22), (sinWH1 | sin23), (sinWP1 | sin23), (sinWS1 | sin24), (sinWS2 | sin25), (sinWT1 | sin23), (sinWM1 | sin23), // ±¤Æ÷ÇÑ ·¹½ÃÇÇ ¹«±¸
									0, 0, 0, 0, 0, 0, 0, 0, // Ãµ»óÀÇ ·¹½ÃÇÇ ¹«±¸
									0, 0, 0, 0, 0, 0, 0, 0,
									0, 0, 0, 0, 0, 0, 0, 0,
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
										(sinDA1 | sin16), (sinDA2 | sin16), (sinDS1 | sin14), (sinOM1 | sin15), (sinDG1 | sin14), (sinOA2 | sin14), (sinDB1 | sin14), 0, // ÀØÇôÁø ·¹½ÃÇÇ °©ÁÖ
										(sinDA1 | sin17), (sinDA2 | sin17), (sinDS1 | sin15), (sinOM1 | sin16), (sinDG1 | sin15), (sinOA2 | sin15), (sinDB1 | sin15), 0, // °í´ëÀÇ ·¹½ÃÇÇ °©ÁÖ
										(sinDA1 | sin18), (sinDA2 | sin18), (sinDS1 | sin16), (sinOM1 | sin17), (sinDG1 | sin16), (sinOA2 | sin16), (sinDB1 | sin16), 0, // ´ëÁöÀÇ ·¹½ÃÇÇ °©ÁÖ
										(sinDA1 | sin19), (sinDA2 | sin19), (sinDS1 | sin17), (sinOM1 | sin18), (sinDG1 | sin17), (sinOA2 | sin17), (sinDB1 | sin17), 0, // ¾îµÒÀÇ ·¹½ÃÇÇ °©ÁÖ
										(sinDA1 | sin20), (sinDA2 | sin20), (sinDS1 | sin18), (sinOM1 | sin19), (sinDG1 | sin18), (sinOA2 | sin18), (sinDB1 | sin18), 0, // È­¿°ÀÇ ·¹½ÃÇÇ °©ÁÖ
										(sinDA1 | sin21), (sinDA2 | sin21), (sinDS1 | sin19), (sinOM1 | sin20), (sinDG1 | sin19), (sinOA2 | sin19), (sinDB1 | sin19), 0, // ¹Ù¶÷ÀÇ ·¹½ÃÇÇ °©ÁÖ
										(sinDA1 | sin23), (sinDA2 | sin23), (sinDS1 | sin21), (sinOM1 | sin22), (sinDG1 | sin21), (sinOA2 | sin21), (sinDB1 | sin21), 0, // ÅÂ¾çÀÇ ·¹½ÃÇÇ °©ÁÖ
										(sinDA1 | sin24), (sinDA2 | sin24), (sinDS1 | sin22), (sinOM1 | sin23), (sinDG1 | sin22), (sinOA2 | sin22), (sinDB1 | sin22), 0, // ±¤Æ÷ÇÑ ·¹½ÃÇÇ °©ÁÖ
										0, 0, 0, 0, 0, 0, 0, 0,  // Ãµ»óÀÇ ·¹½ÃÇÇ °©ÁÖ
										 (sinOA1 | sin36), 0, 0, 0, 0, 0, 0, 0, // ´«²É ¸ñ°ÉÀÌ
										 dwItem, 0, 0, 0, 0, 0, 0, 0
	};
	int num = 0;
	SManufacture_ResultItemInfo_Server Item_Recv;
	ZeroMemory(&Item_Recv, sizeof(SManufacture_ResultItemInfo_Server));
	Item_Recv.smTransCommand.code = smTRANSCODE_MANUFACTURE_WEIGHT_PRICE;
	Item_Recv.smTransCommand.size = sizeof(SManufacture_ResultItemInfo_Server);
	for (int i = 0; i < 176; i++)
	{
		if (CreateItemCode[i] > 0)
		{
			auto pDefItem = SERVERITEM->FindItemDefByCode(CreateItemCode[i]);

			if (pDefItem)
			{
				Item_Recv.ItemCode[num] = pDefItem->sItem.sItemID.ToInt();
				lstrcpy(Item_Recv.ItemName[num], pDefItem->sItem.szItemName);//pluto ÇØ¿Ü
				Item_Recv.Weight[num] = pDefItem->sItem.iWeight;
				Item_Recv.Price[num] = pDefItem->sItem.iSalePrice;
				num++;
			}
		}
	}

	SENDPACKET(lpPlayInfo, &Item_Recv);

	return TRUE;
}
int rsRecvManufactureItem(User *lpPlayInfo, SManufactureItem_Server *pManufactureItem_Server)
{
	CManufacture ccItem;
	smTRANS_COMMAND_EX	smTransCommandEx;

	int cnt;
	int	ErrorFlag;
	DWORD ItemSmeltingType = 0;
	bool  bProbability = FALSE;
	ErrorFlag = 0;

	if (pManufactureItem_Server->RuneCode[0])
	{
		if (SERVERITEM->DeleteItemInventory(lpPlayInfo,
			pManufactureItem_Server->RuneCode[0],
			pManufactureItem_Server->Head[0],
			pManufactureItem_Server->CheckSum[0]) == FALSE)
		{
			smTransCommandEx.WParam = 8000;
			smTransCommandEx.WxParam = 50;
			smTransCommandEx.LxParam = (int)"*Manufacture Recipe*";
			smTransCommandEx.LParam = pManufactureItem_Server->RuneCode[0];
			smTransCommandEx.SParam = pManufactureItem_Server->Head[0];
			smTransCommandEx.EParam = pManufactureItem_Server->CheckSum[0];
			RecordHackLogFile(lpPlayInfo, &smTransCommandEx);

			ErrorFlag++;

			pManufactureItem_Server->RuneCode[0] = 0;
		}
		SaveThrowItem(lpPlayInfo, pManufactureItem_Server->RuneCode[0], pManufactureItem_Server->Head[0], pManufactureItem_Server->CheckSum[0]);
	}

	for (cnt = 1; cnt < 4; cnt++)
	{
		if (pManufactureItem_Server->RuneCode[cnt])
		{
			if (SERVERITEM->DeleteItemInventory(lpPlayInfo,
				pManufactureItem_Server->RuneCode[cnt],
				pManufactureItem_Server->Head[cnt],
				pManufactureItem_Server->CheckSum[cnt]) == FALSE)
			{
				smTransCommandEx.WParam = 8000;
				smTransCommandEx.WxParam = 50;
				smTransCommandEx.LxParam = (int)"*Manufacture Rune*";
				smTransCommandEx.LParam = pManufactureItem_Server->RuneCode[cnt];
				smTransCommandEx.SParam = pManufactureItem_Server->Head[cnt];
				smTransCommandEx.EParam = pManufactureItem_Server->CheckSum[cnt];
				RecordHackLogFile(lpPlayInfo, &smTransCommandEx);

				ErrorFlag++;

				pManufactureItem_Server->RuneCode[cnt] = 0;
			}
			SaveThrowItem(lpPlayInfo, pManufactureItem_Server->RuneCode[cnt], pManufactureItem_Server->Head[cnt], pManufactureItem_Server->CheckSum[cnt]);

		}
	}

	DWORD ResultItemCode = 0;

	if (ErrorFlag == 0)
	{
		ResultItemCode = ManufactureCheckRune(lpPlayInfo, pManufactureItem_Server->RuneCode[0], pManufactureItem_Server->RuneCode);
		if (ResultItemCode != 0)
		{
			srand(unsigned int(time(NULL)));

			if ((rand() % 100) < 50)
			{
				auto pDefItem = SERVERITEM->FindItemDefByCode(ResultItemCode);

				if (pDefItem)
				{
					SERVERITEM->CreateItem(&pManufactureItem_Server->DesManufactureItem.sItem, pDefItem);
					bProbability = TRUE;
				}
			}
			else
				ErrorFlag++;
		}
		else
			ErrorFlag++;
	}
	else
		ErrorFlag++;

	ccItem.sinRecvManufactureItem(pManufactureItem_Server);

	if (bProbability)
		sManufactureItem_Recv.Result = TRUE;

	if (ErrorFlag)
		sManufactureItem_Recv.Result = FALSE;

	if (sManufactureItem_Recv.Result == TRUE)
	{
		ReformItem(&sManufactureItem_Recv.DesManufactureItem.sItem);
		sManufactureItem_Recv.size = sizeof(ItemData) + 32;
		rsRecord_ManufactureItemLog(lpPlayInfo, pManufactureItem_Server->RuneCode, pManufactureItem_Server->Head, pManufactureItem_Server->CheckSum, ITEMLOG_MANUFACTURE_LOST);

		SERVERITEM->AddItemInventory(lpPlayInfo, sManufactureItem_Recv.DesManufactureItem.sItem.sItemID.ToInt(), sManufactureItem_Recv.DesManufactureItem.sItem.iChk1, sManufactureItem_Recv.DesManufactureItem.sItem.iChk2);

		rsRecord_ItemLog2(lpPlayInfo, sManufactureItem_Recv.DesManufactureItem.sItem.sItemID.ToInt(), sManufactureItem_Recv.DesManufactureItem.sItem.iChk1, sManufactureItem_Recv.DesManufactureItem.sItem.iChk2, ITEMLOG_MANUFACTURE_GET);

		RecordManufactureItem(lpPlayInfo, &sManufactureItem_Recv.DesManufactureItem.sItem);
	}
	else
	{
		sManufactureItem_Recv.size = 32;
		rsRecord_ManufactureItemLog(lpPlayInfo, pManufactureItem_Server->RuneCode, pManufactureItem_Server->Head, pManufactureItem_Server->CheckSum, ITEMLOG_MANUFACTURE_FAIL);
	}

	sManufactureItem_Recv.code = smTRANSCODE_MANUFACTURE;

	SENDPACKET(lpPlayInfo, &sManufactureItem_Recv);

	return TRUE;
}

// »Ø¸´ÊôÐÔÏµÍ³
int rsRecvMixtureResetItem(User *lpPlayInfo, sMIXTURE_RESET_ITEM_SERVER *pMixtureResetItem_Server)
{
	cMIXTURERESET ccItem;
	Item sItemInfo;
	smTRANS_COMMAND_EX	smTransCommandEx;
	int ErrorFlag = 0;
	int MixtureResetSuccess = FALSE;

	if (pMixtureResetItem_Server->dwMixtureResetStoneItemCode)
	{
		if (SERVERITEM->DeleteItemInventory(lpPlayInfo,
			pMixtureResetItem_Server->dwMixtureResetStoneItemCode,
			pMixtureResetItem_Server->dwMixtureResetStoneHead,
			pMixtureResetItem_Server->dwMixtureResetStoneCheckSum) == FALSE)
		{
			smTransCommandEx.WParam = 8000;
			smTransCommandEx.WxParam = 50;
			smTransCommandEx.LxParam = (int)"*Mixture Reset Stone*";
			smTransCommandEx.LParam = pMixtureResetItem_Server->dwMixtureResetStoneItemCode;
			smTransCommandEx.SParam = pMixtureResetItem_Server->dwMixtureResetStoneHead;
			smTransCommandEx.EParam = pMixtureResetItem_Server->dwMixtureResetStoneCheckSum;

			RecordHackLogFile(lpPlayInfo, &smTransCommandEx);

			ErrorFlag++;

			pMixtureResetItem_Server->dwMixtureResetStoneItemCode = 0;
		}

		SaveThrowItem(lpPlayInfo, pMixtureResetItem_Server->dwMixtureResetStoneItemCode, pMixtureResetItem_Server->dwMixtureResetStoneHead, pMixtureResetItem_Server->dwMixtureResetStoneCheckSum);
	}

	memcpy(&sItemInfo, &pMixtureResetItem_Server->DesMixtureResetItem.sItem, sizeof(Item));

	if (CheckItemForm(&sItemInfo) == FALSE ||
		CheckMixItem(&sItemInfo) == FALSE ||
		(sItemInfo.eCraftType != ITEMCRAFTTYPE_Mixing && sItemInfo.eCraftType != ITEMCRAFTTYPE_Aging))
	{
		pMixtureResetItem_Server->Result = FALSE;
		pMixtureResetItem_Server->size = 32;

		SENDPACKET(lpPlayInfo, &pMixtureResetItem_Server);

		smTransCommandEx.WParam = 99000;
		smTransCommandEx.SParam = 0;
		smTransCommandEx.LParam = 1;

		RecordHackLogFile(lpPlayInfo, &smTransCommandEx);

		return TRUE;
	}

	ccItem.sinRecvMixtureItemReset(pMixtureResetItem_Server);

	DWORD dwResultItemCode = 0;
	DWORD dwSpecialJob = 0;

	if (ErrorFlag == 0)
	{
		switch (sMixtureReset_Recv.dwMixtureResetStoneItemCode)
		{
		case sinBI1 | sin89:
			dwResultItemCode = sMixtureReset_Recv.DesMixtureResetItem.sBaseItemID.ToInt();

			if (dwResultItemCode != 0)
			{
				auto pDefItem = SERVERITEM->FindItemDefByCode(dwResultItemCode);

				if (pDefItem)
				{
					SERVERITEM->CreateItem(&sMixtureReset_Recv.DesMixtureResetItem.sItem, pDefItem);
					MixtureResetSuccess = TRUE;
				}
			}
			else
				ErrorFlag++;
			break;
		case sinBI2 | sin48:
			dwResultItemCode = sMixtureReset_Recv.DesMixtureResetItem.sBaseItemID.ToInt();
			dwSpecialJob = sMixtureReset_Recv.DesMixtureResetItem.sItem.eSpecialization;
			int	i;
			DWORD dwJobCode;

			dwJobCode = 0;

			for (i = 1; i <= 10; i++)
			{
				if (CharacterClassToClassFlag((ECharacterClass)i) == dwSpecialJob)
				{
					dwJobCode = i;
					break;
				}
			}
			if (dwResultItemCode != 0)
			{
				auto pDefItem = SERVERITEM->FindItemDefByCode(dwResultItemCode);

				if (pDefItem)
				{
					SERVERITEM->CreateItem(&sMixtureReset_Recv.DesMixtureResetItem.sItem, pDefItem);
					MixtureResetSuccess = TRUE;
				}
			}
			else
				ErrorFlag++;
			break;
		case sinBI2 | sin49:
			if (ccItem.ResetItem(&sMixtureReset_Recv))
				MixtureResetSuccess = TRUE;
			else
				ErrorFlag++;

			break;
		}
	}

	if (ErrorFlag == 0 && MixtureResetSuccess == TRUE)
	{
		sMixtureReset_Recv.Result = TRUE;
		ReformItem(&sMixtureReset_Recv.DesMixtureResetItem.sItem);
		sMixtureReset_Recv.size = sizeof(ItemData) + 32;

		if (SERVERITEM->DeleteItemInventory(lpPlayInfo,
			sItemInfo.sItemID.ToInt(),
			sItemInfo.iChk1,
			sItemInfo.iChk2))
		{
			rsRecord_MixtureResetItemLog(lpPlayInfo, pMixtureResetItem_Server, ITEMLOG_MIXTURE_RESET_LOST);
			SERVERITEM->AddItemInventory(lpPlayInfo,
				sMixtureReset_Recv.DesMixtureResetItem.sItem.sItemID.ToInt(),
				sMixtureReset_Recv.DesMixtureResetItem.sItem.iChk1,
				sMixtureReset_Recv.DesMixtureResetItem.sItem.iChk2);
			rsRecord_ItemLog2(lpPlayInfo,
				sMixtureReset_Recv.DesMixtureResetItem.sItem.sItemID.ToInt(),
				sMixtureReset_Recv.DesMixtureResetItem.sItem.iChk1,
				sMixtureReset_Recv.DesMixtureResetItem.sItem.iChk2,
				ITEMLOG_MIXTURE_RESET_GET);
			RecordMixtureResetItem(lpPlayInfo, &sMixtureReset_Recv.DesMixtureResetItem.sItem);
		}
		else
		{
			sMixtureReset_Recv.Result = FALSE;
			sMixtureReset_Recv.size = 32;
			rsRecord_MixtureResetItemLog(lpPlayInfo, pMixtureResetItem_Server, ITEMLOG_MIXTURE_RESET_FAIL);
		}
	}
	else
	{
		sMixtureReset_Recv.Result = FALSE;
		sMixtureReset_Recv.size = 32;
		rsRecord_MixtureResetItemLog(lpPlayInfo, pMixtureResetItem_Server, ITEMLOG_MIXTURE_RESET_FAIL);
	}
	sMixtureReset_Recv.code = smTRANSCODE_MIXTURE_RESET_ITEM;

	SENDPACKET(lpPlayInfo, &sMixtureReset_Recv);

	return TRUE;
}
// ¸½Ä§ÏµÍ³
int rsRecvElementItem(User *lpPlayInfo, ELEMENT_ITEM_SERVER *pElementItem_server)
{
	cELEMENT			ccItem;
	Item			*pItemInfo;
	Item			sItemInfo;
	smTRANS_COMMAND_EX	smTransCommandEx;
	smTRANS_COMMAND		smTransCommand;
	int					ErrorFlag = 0;
	int					Price;
	int					Result;

	for (int i = 0; i < 5; i++)
	{
		if (pElementItem_server->SheltomCode[i])
		{
			if (SERVERITEM->DeleteItemInventory(lpPlayInfo,
				pElementItem_server->SheltomCode[i],
				pElementItem_server->Head[i],
				pElementItem_server->CheckSum[i]) == FALSE)
			{
				smTransCommandEx.WParam = 8000;
				smTransCommandEx.WxParam = 50;
				smTransCommandEx.LxParam = (int)"*Element Stone*";
				smTransCommandEx.LParam = pElementItem_server->SheltomCode[i];
				smTransCommandEx.SParam = pElementItem_server->Head[i];
				smTransCommandEx.EParam = pElementItem_server->CheckSum[i];

				RecordHackLogFile(lpPlayInfo, &smTransCommandEx);

				ErrorFlag++;

				pElementItem_server->SheltomCode[i] = 0;
			}
			SaveThrowItem(lpPlayInfo, pElementItem_server->SheltomCode[i], pElementItem_server->Head[i], pElementItem_server->CheckSum[i]);
		}
	}

	memcpy(&sItemInfo, &pElementItem_server->DesItem.sItem, sizeof(Item));

	Price = rsGetMoney(sItemInfo.sItemID.ToInt(), TRUE);

	if (sItemInfo.iSalePrice < 0 || lpPlayInfo->GetGold() < sItemInfo.iSalePrice)
	{
		smTransCommand.WParam = 8010;
		smTransCommand.LParam = 50;
		smTransCommand.SParam = lpPlayInfo->GetGold();
		smTransCommand.EParam = sItemInfo.iSalePrice;
		RecordHackLogFile(lpPlayInfo, &smTransCommand);

		ErrorFlag++;
	}
	else
	{
		SERVERUSER->SubServerUserGold(lpPlayInfo, Price, WHEREID_None);
		lpPlayInfo->UnsaveMoney = lpPlayInfo->GetGold();
	}

	if (CheckItemForm(&sItemInfo) == FALSE || CheckMixItem(&sItemInfo) == FALSE)
	{
		pElementItem_server->Result = FALSE;
		pElementItem_server->size = 32;

		SENDPACKET(lpPlayInfo, pElementItem_server);

		smTransCommand.WParam = 99000;
		smTransCommand.SParam = 0;
		smTransCommand.LParam = 1;
		RecordHackLogFile(lpPlayInfo, &smTransCommand);

		return TRUE;
	}
	ccItem.RecvItem(pElementItem_server);
	Result = ccItem.CreateElementItem();

	ccItem.ElementItemServer.code = smTRANSCODE_ELEMENTITEM;

	if (Result > 0 && ErrorFlag == 0)
	{
		ReformItem(&ccItem.ElementItemServer.DesItem.sItem);
		ccItem.ElementItemServer.size = sizeof(ItemData) + 32;

		pItemInfo = &ccItem.ElementItemServer.DesItem.sItem;

		if (SERVERITEM->DeleteItemInventory(lpPlayInfo,
			sItemInfo.sItemID.ToInt(),
			sItemInfo.iChk1,
			sItemInfo.iChk2))
		{
			SERVERITEM->AddItemInventory(lpPlayInfo, pItemInfo->sItemID.ToInt(), pItemInfo->iChk1, pItemInfo->iChk2);
			RecordElementItem(lpPlayInfo, pItemInfo);
		}
		else
		{
			ccItem.ElementItemServer.size = 32;
			smTransCommandEx.WParam = 8000;
			smTransCommandEx.WxParam = 50;
			smTransCommandEx.LxParam = (int)pItemInfo->szItemName;
			smTransCommandEx.LParam = pItemInfo->sItemID.ToInt();
			smTransCommandEx.SParam = pItemInfo->iChk1;
			smTransCommandEx.EParam = pItemInfo->iChk2;

			RecordHackLogFile(lpPlayInfo, &smTransCommandEx);
		}

		SaveThrowItem(lpPlayInfo, sItemInfo.sItemID.ToInt(), sItemInfo.iChk1, sItemInfo.iChk2);
	}
	else
		ccItem.ElementItemServer.size = 32;

	SENDPACKET(lpPlayInfo, &ccItem.ElementItemServer);

	return TRUE;
}

int rsRecvSocketItem(User *lpPlayInfo, SOCKET_ITEM_SERVER *pSocketItem_server)
{
	cSOCKET			ccItem;
	Item			*pItemInfo;
	Item			sItemInfo;
	smTRANS_COMMAND_EX	smTransCommandEx;
	smTRANS_COMMAND		smTransCommand;
	int					ErrorFlag = 0;
	int					Price;
	int					Result;

	for (int i = 0; i < 4; i++)
	{
		if (pSocketItem_server->SheltomCode[i])
		{
			if (SERVERITEM->DeleteItemInventory(lpPlayInfo,
				pSocketItem_server->SheltomCode[i],
				pSocketItem_server->Head[i],
				pSocketItem_server->CheckSum[i]) == FALSE)
			{
				smTransCommandEx.WParam = 8000;
				smTransCommandEx.WxParam = 50;
				smTransCommandEx.LxParam = (int)"*Element Stone*";
				smTransCommandEx.LParam = pSocketItem_server->SheltomCode[i];
				smTransCommandEx.SParam = pSocketItem_server->Head[i];
				smTransCommandEx.EParam = pSocketItem_server->CheckSum[i];

				RecordHackLogFile(lpPlayInfo, &smTransCommandEx);

				ErrorFlag++;

				pSocketItem_server->SheltomCode[i] = 0;
			}

			SaveThrowItem(lpPlayInfo, pSocketItem_server->SheltomCode[i], pSocketItem_server->Head[i], pSocketItem_server->CheckSum[i]);
		}
	}

	memcpy(&sItemInfo, &pSocketItem_server->DesItem.sItem, sizeof(Item));

	Price = rsGetMoney(sItemInfo.sItemID.ToInt(), TRUE);

	if (CheckItemForm(&sItemInfo) == FALSE || CheckMixItem(&sItemInfo) == FALSE)
	{
		pSocketItem_server->Result = FALSE;
		pSocketItem_server->size = 32;

		SENDPACKET(lpPlayInfo, pSocketItem_server);

		smTransCommand.WParam = 99000;
		smTransCommand.SParam = 0;
		smTransCommand.LParam = 1;
		RecordHackLogFile(lpPlayInfo, &smTransCommand);

		return TRUE;
	}

	ccItem.RecvItem(pSocketItem_server);
	Result = ccItem.CreateSocketItem();

	ccItem.SocketItemServer.code = smTRANSCODE_SOCKETITEM;

	if (Result > 0 && ErrorFlag == 0)
	{
		ReformItem(&ccItem.SocketItemServer.DesItem.sItem);

		ccItem.SocketItemServer.size = sizeof(ItemData) + 32;

		pItemInfo = &ccItem.SocketItemServer.DesItem.sItem;

		if (SERVERITEM->DeleteItemInventory(lpPlayInfo,
			sItemInfo.sItemID.ToInt(),
			sItemInfo.iChk1,
			sItemInfo.iChk2))
		{
			SERVERITEM->AddItemInventory(lpPlayInfo, pItemInfo->sItemID.ToInt(), pItemInfo->iChk1, pItemInfo->iChk2);
			RecordElementItem(lpPlayInfo, pItemInfo);
		}
		else
		{
			ccItem.SocketItemServer.size = 32;
			smTransCommandEx.WParam = 8000;
			smTransCommandEx.WxParam = 50;
			smTransCommandEx.LxParam = (int)pItemInfo->szItemName;
			smTransCommandEx.LParam = pItemInfo->sItemID.ToInt();
			smTransCommandEx.SParam = pItemInfo->iChk1;
			smTransCommandEx.EParam = pItemInfo->iChk2;

			RecordHackLogFile(lpPlayInfo, &smTransCommandEx);
		}

		SaveThrowItem(lpPlayInfo, sItemInfo.sItemID.ToInt(), sItemInfo.iChk1, sItemInfo.iChk2);
	}
	else
		ccItem.SocketItemServer.size = 32;

	SENDPACKET(lpPlayInfo, &ccItem.SocketItemServer);

	return TRUE;
}
//½ÓÊÜÁ¦Á¿Ê¯Í·´«ËÍ³á°òµÈÐ­Òé
int rsRecvWingItem(User *lpPlayInfo, sCRAFTITEM_SERVER *pCraftItem_Server)
{
	Item	sItemInfo;
	smTRANS_COMMAND	smTransCommand;
	smTRANS_COMMAND_EX	smTransCommandEx;

	int cnt;
	int	ErrorFlag;
	int	PotionCount = 0;
	int result;
	int	Money;
	int	ForceMode = 0;

	ErrorFlag = 0;

	if (pCraftItem_Server->DesCraftItem.sBaseItemID.ToInt() == 1000)
		ForceMode = TRUE;


	if (ForceMode)
		rsRecord_ItemLost(lpPlayInfo, pCraftItem_Server->SheltomCode, pCraftItem_Server->Head, pCraftItem_Server->CheckSum, ITEMLOG_LOST_ALCHMY);
	else
		rsRecord_ItemLost(lpPlayInfo, pCraftItem_Server->SheltomCode, pCraftItem_Server->Head, pCraftItem_Server->CheckSum, ITEMLOG_WINGLOST);

	for (cnt = 0; cnt < 12; cnt++)
	{
		if (pCraftItem_Server->SheltomCode[cnt])
		{
			if (SERVERITEM->DeleteItemInventory(lpPlayInfo,
				pCraftItem_Server->SheltomCode[cnt],
				pCraftItem_Server->Head[cnt],
				pCraftItem_Server->CheckSum[cnt]) == FALSE)
			{
				smTransCommandEx.WParam = 8000;
				smTransCommandEx.WxParam = 50;
				smTransCommandEx.LxParam = (int)"*WING CRISTAL*";
				smTransCommandEx.LParam = pCraftItem_Server->SheltomCode[cnt];
				smTransCommandEx.SParam = pCraftItem_Server->Head[cnt];
				smTransCommandEx.EParam = pCraftItem_Server->CheckSum[cnt];
				RecordHackLogFile(lpPlayInfo, &smTransCommandEx);
				ErrorFlag++;
			}

			SaveThrowItem(lpPlayInfo, pCraftItem_Server->SheltomCode[cnt], pCraftItem_Server->Head[cnt], pCraftItem_Server->CheckSum[cnt]);
		}
	}

	memcpy(&sItemInfo, &pCraftItem_Server->DesCraftItem.sItem, sizeof(Item));

	if (sItemInfo.sItemID.ToInt() && CheckItemForm(&sItemInfo) == FALSE)
	{
		pCraftItem_Server->Result = FALSE;
		pCraftItem_Server->size = 32;

		SENDPACKET(lpPlayInfo, pCraftItem_Server);

		smTransCommand.WParam = 99000;
		smTransCommand.SParam = 1;
		smTransCommand.LParam = sItemInfo.sItemID.ToInt();
		RecordHackLogFile(lpPlayInfo, &smTransCommand);

		return TRUE;
	}


	SERVERITEM->DeleteItemInventory(lpPlayInfo,
		pCraftItem_Server->DesCraftItem.sItem.sItemID.ToInt(),
		pCraftItem_Server->DesCraftItem.sItem.iChk1,
		pCraftItem_Server->DesCraftItem.sItem.iChk2);


	result = 0;

	if (!ErrorFlag)
		result = sinWingItemQuestServer(pCraftItem_Server, &lpPlayInfo->sCharacterData);
	else
		pCraftItem_Server->Result = FALSE;

	if (result == 0x100)
	{
		TRANS_ITEMINFO_GROUP	TransItemGroup;
		TRANS_ITEMINFO_GROUP2	TransItemGroup2;
		int ItemCnt, LenSize;

		Money = 0;

		for (int i = 0; i < 12; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				if ((pCraftItem_Server->SheltomCode[i] & sinITEM_MASK3) == SheltomCode2[j])
				{
					Money += ForceOrbPriceIndex[j];
					break;
				}
			}
		}
		if (lpPlayInfo->GetGold() >= Money)
		{
			SERVERUSER->SubServerUserGold(lpPlayInfo, Money, WHEREID_ForceOrb);
		}
		else
		{
			smTransCommandEx.WParam = 8000;
			smTransCommandEx.WxParam = 50;
			smTransCommandEx.LxParam = (int)"*FORCE MONEY ERROR*";
			smTransCommandEx.LParam = (sinGG1 | sin01);
			smTransCommandEx.SParam = Money;
			smTransCommandEx.EParam = lpPlayInfo->GetGold();
			RecordHackLogFile(lpPlayInfo, &smTransCommandEx);
			return FALSE;
		}

		ZeroMemory(&TransItemGroup2, sizeof(TRANS_ITEMINFO_GROUP2));

		ItemCnt = 0;

		for (cnt = 0; cnt < 12; cnt++)
		{
			if (pCraftItem_Server->SheltomCode[cnt])
			{
				auto pDefItem = SERVERITEM->FindItemDefByCode(pCraftItem_Server->SheltomCode[cnt]);

				if (pDefItem)
				{
					SERVERITEM->CreateItem(&TransItemGroup.sItemInfo[ItemCnt], pDefItem);
					SERVERITEM->AddItemInventory(lpPlayInfo, TransItemGroup.sItemInfo[ItemCnt].sItemID.ToInt(), TransItemGroup.sItemInfo[ItemCnt].iChk1, TransItemGroup.sItemInfo[ItemCnt].iChk2);
				}
			}
		}

		LenSize = EecodeCompress((BYTE *)TransItemGroup.sItemInfo, (BYTE *)TransItemGroup2.szBuff, sizeof(Item)*ItemCnt, sizeof(Item)*TRANS_GROUPITEM_MAX);
		TransItemGroup2.ItemCount = ItemCnt;
		TransItemGroup2.Result = pCraftItem_Server->Result;
		TransItemGroup2.size = LenSize + TRANS_GROUPITEM_HEADER_SIZE;
		TransItemGroup2.code = smTRANSCODE_ITEM_FORCEORB;

		SENDPACKET(lpPlayInfo, &TransItemGroup2);

		return TRUE;
	}

	if (pCraftItem_Server->Result == SIN_WINGRESULT_CRISTAL)
	{
		bSql_EventJoin(lpPlayInfo);
		pCraftItem_Server->Result = TRUE;
	}
	BOOL bRet = FALSE;

	if (pCraftItem_Server->Result == TRUE && pCraftItem_Server->DesCraftItem.sItem.sItemID.ToInt() && !ErrorFlag)
	{
		if (pCraftItem_Server->DesCraftItem.sItem.eCraftType == ITEMCRAFTTYPE_QuestWeapon)
		{
			auto pDefItem = SERVERITEM->FindItemDefByCode(pCraftItem_Server->DesCraftItem.sItem.sItemID.ToInt(), ITEM_UNIQUE_CODE_QUEST);

			if (pDefItem)
			{
				SERVERITEM->CreateItem(&pCraftItem_Server->DesCraftItem.sItem, pDefItem);
				pCraftItem_Server->DesCraftItem.sItem.eCraftType = ITEMCRAFTTYPE_QuestWeapon;
				SetChangeJob3QuestItem(&pCraftItem_Server->DesCraftItem.sItem);
				bRet = TRUE;
			}
		}
		else 
		{
			auto pDefItem = SERVERITEM->FindItemDefByCode(pCraftItem_Server->DesCraftItem.sItem.sItemID.ToInt());

			if (pDefItem)
			{
				SERVERITEM->CreateItem(&pCraftItem_Server->DesCraftItem.sItem, pDefItem);

				if (pDefItem->sItem.sItemID.ToItemBase() == ITEMBASE_Potion)
				{
					pCraftItem_Server->DesCraftItem.sItem.iPotionCount = PotionCount = 30;

					SERVERITEM->AddPotion(lpPlayInfo, pCraftItem_Server->DesCraftItem.sItem.sItemID.ToInt(), 30);
				}

				bRet = TRUE;
			}
		}
		if (bRet) 
		{

			ReformItem(&pCraftItem_Server->DesCraftItem.sItem);

			SERVERITEM->AddItemInventory(lpPlayInfo,
				pCraftItem_Server->DesCraftItem.sItem.sItemID.ToInt(),
				pCraftItem_Server->DesCraftItem.sItem.iChk1,
				pCraftItem_Server->DesCraftItem.sItem.iChk2);

			pCraftItem_Server->size = sizeof(sCRAFTITEM_SERVER);

			SENDPACKET(lpPlayInfo, &pCraftItem_Server);

			return TRUE;
		}
	}

	smTransCommand.WParam = 99000;
	smTransCommand.SParam = 1;
	smTransCommand.LParam = sItemInfo.sItemID.ToInt();
	RecordHackLogFile(lpPlayInfo, &smTransCommand);

	pCraftItem_Server->size = sizeof(sCRAFTITEM_SERVER);
	pCraftItem_Server->Result = FALSE;

	SENDPACKET(lpPlayInfo, &pCraftItem_Server);

	return TRUE;
}

#ifdef _W_SERVER

//¸µÅ© ÄÚ¾î µî·Ï ¿äÃ»
int rsRecvMakeLinkCore(User *lpPlayInfo, TRANS_ITEMINFO *lpTransItemInfo)
{
	int len, len2;

	if (!lpPlayInfo->szCharacterName[0] || CheckItemForm(&lpTransItemInfo->sItem) == FALSE) return FALSE;

	//¼­¹ö ÀÌº¥ ¾ÆÀÌÅÛ ¼öÁ¤
	if (SERVERITEM->DeleteItemInventory(lpPlayInfo,
		lpTransItemInfo->sItem.sItemID.ToInt(),
		lpTransItemInfo->sItem.iChk1,
		lpTransItemInfo->sItem.iChk2)  == FALSE)
		return FALSE;


	lpTransItemInfo->sItem.BackUpKey = lpTransItemInfo->sItem.iChk1;
	lpTransItemInfo->sItem.BackUpChkSum = lpTransItemInfo->sItem.iChk2;

	len = lstrlen(lpTransItemInfo->sItem.szItemName) + 1;
	len2 = lstrlen(lpPlayInfo->szCharacterName);
	if ((len + len2) > 32) return FALSE;		//ÀÌ¸§ÀÌ ³Ê¹« ±æ´Ù ½ÇÆÐ

	lstrcpy(lpTransItemInfo->sItem.szItemName + len, lpPlayInfo->szCharacterName);

	ReformItem(&lpTransItemInfo->sItem);

	//¼­¹ö ÀÎº¥ ¾ÆÀÌÅÛ Ãß°¡
	SERVERITEM->AddItemInventory(lpPlayInfo, lpTransItemInfo->sItem.sItemID.ToInt(), lpTransItemInfo->sItem.iChk1, lpTransItemInfo->sItem.iChk2);

	SENDPACKET(lpPlayInfo, lpTransItemInfo);

	return TRUE;
}

//Ê¹ÓÃ¹«»á¾íÖá
int rsRecvUseLinkCore(User *lpPlayInfo, TRANS_ITEMINFO *lpTransItemInfo)
{
	char *szName;
	int len;
	User *lpPlayInfo2;
	TRANS_CHATMESSAGE	TransChatMessage;
	smTRANS_COMMAND_EX	smTransCommandEx;
	Map	*lpStgArea = nullptr;

	if (CheckItemForm(&lpTransItemInfo->sItem) == FALSE)
		return FALSE;


	lpTransItemInfo->sItem.szItemName[31] = 0;
	len = lstrlen(lpTransItemInfo->sItem.szItemName);

	szName = &lpTransItemInfo->sItem.szItemName[len + 1];
	if (!szName[0])
		return FALSE;

	lpPlayInfo2 = FindUserFromName(szName);

	if (!lpPlayInfo2 || !lpPlayInfo2->iID || !lpPlayInfo->iClanID || lpPlayInfo->dwExclusiveNum || lpPlayInfo2->dwExclusiveNum ||
		rsCheckHardCoreEventArea(lpPlayInfo2->sPosition.iX, lpPlayInfo2->sPosition.iY, lpPlayInfo2->sPosition.iZ) == TRUE ||
		lpPlayInfo->iMapID == MAPID_QuestArena || lpPlayInfo2->iMapID == MAPID_BlessCastle)
	{
		lstrcpy(TransChatMessage.szMessage, "Cannot use union core");
		TransChatMessage.code = smTRANSCODE_MESSAGEBOX;
		TransChatMessage.dwIP = 0;
		TransChatMessage.dwObjectSerial = 0;
		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);

		SENDPACKET(lpPlayInfo, &TransChatMessage);
		return FALSE;
	}

	if (lpPlayInfo2->iClanID != lpPlayInfo->iClanID)
	{
		lstrcpy(TransChatMessage.szMessage, "  Wrong clan  ");
		TransChatMessage.code = smTRANSCODE_MESSAGEBOX;
		TransChatMessage.dwIP = 0;
		TransChatMessage.dwObjectSerial = 0;
		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);

		SENDPACKET(lpPlayInfo, &TransChatMessage);
		return FALSE;
	}

	lpStgArea = SERVERMAP->GetMapByXZ(lpPlayInfo2->sPosition.iX, lpPlayInfo2->sPosition.iZ);

	if (lpStgArea)
	{
		if (lpStgArea->pcBaseMap)
		{
			if (lpPlayInfo->sCharacterData.iLevel < lpStgArea->pcBaseMap->iLevel ||
				lpStgArea->pcBaseMap->iMapID == QUEST_ARENA_FIELD)
			{
				lstrcpy(TransChatMessage.szMessage, "Level is not high enough to enter ");
				TransChatMessage.code = smTRANSCODE_MESSAGEBOX;
				TransChatMessage.dwIP = 0;
				TransChatMessage.dwObjectSerial = 0;
				TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);

				SENDPACKET(lpPlayInfo, &TransChatMessage);
				return FALSE;
			}
		}

		smTransCommandEx.code = smTRANSCODE_USE_LINKCORE;
		smTransCommandEx.size = sizeof(smTRANS_COMMAND_EX);
		smTransCommandEx.WxParam = lpTransItemInfo->sItem.sItemID.ToInt();
		smTransCommandEx.LxParam = lpTransItemInfo->sItem.iChk1;
		smTransCommandEx.SxParam = lpTransItemInfo->sItem.iChk2;
		smTransCommandEx.ExParam = 0;
		smTransCommandEx.WParam = lpPlayInfo2->sPosition.iX;
		smTransCommandEx.LParam = lpPlayInfo2->sPosition.iY;
		smTransCommandEx.SParam = lpPlayInfo2->sPosition.iZ;
		smTransCommandEx.EParam = lpStgArea->pcBaseMap->iMapID;

		SENDPACKET(lpPlayInfo, &smTransCommandEx);
		return TRUE;
	}

	return FALSE;
}

#endif


//ÖÎÓúÖ®Êõ
int	rsPlayHealing(smTRANS_COMMAND *lpTransCommand)
{
	Unit	*lpChar;
	User *lpPlayInfo;

	lpChar = SERVERUNIT->GetUnit(lpTransCommand->SParam);
	if (lpChar)
	{
		if (lpChar && lpChar->sCharacterData.sHP.sMin > 0) {
			if (!lpChar->iSpecialType || lpChar->sCharacterData.iMonsterEffectID != snCHAR_SOUND_CASTLE_TOWER_B)
			{
				if (lpChar->sCharacterData.iMonsterEffectID == MONSTEREFFECTID_CASTLE_DOOR || lpChar->sCharacterData.iMonsterEffectID == snCHAR_SOUND_CASTLE_TOWER_B)
					return TRUE;

				lpChar->sCharacterData.sHP.sMin += lpTransCommand->WParam;
				if (lpChar->sCharacterData.sHP.sMin > lpChar->sCharacterData.sHP.sMax)
					lpChar->sCharacterData.sHP.sMin = lpChar->sCharacterData.sHP.sMax;
			}
		}
		return TRUE;
	}
	lpPlayInfo = SERVERUSER->GetUser(lpTransCommand->SParam);
	if (lpPlayInfo) {

		if (lpPlayInfo->dwSkill_VirtualLife_Time && lpPlayInfo->dwSkill_VirtualLife_Time > SERVER_GAMETIME) {
			//¹ö«x¶óÀÌÇÁ (¼öÄ¡º¸Á¤ )
			lpTransCommand->WParam -= (lpTransCommand->WParam*lpPlayInfo->dwSkill_VirtualLife_Param) / 100;
		}

		SENDPACKET(lpPlayInfo, lpTransCommand);

		return TRUE;
	}

	return	FALSE;
}

int	rsPlayHolyMind(smTRANS_COMMAND *lpTransCommand)
{
	Unit	*lpChar;
	int time;
	int bio;

	lpChar = SERVERUNIT->GetUnit(lpTransCommand->SParam);
	if (lpChar)
	{
		time = lpTransCommand->LParam << 4;
		bio = lpChar->sCharacterData.sElementalDef[sITEMINFO_BIONIC];
		if (bio < 0)
			bio = 0;
		if (bio > 100)
			bio = 100;
		time = (time*(100 - bio)) / 100;
		if (time > 0)
		{
			lpChar->PlayHolyMind[0] = lpTransCommand->WParam;
			lpChar->PlayHolyMind[1] = time;
		}
		return TRUE;
	}

	return FALSE;
}

//SoD °á°ú¿ë Ã¼Å©¼¶ »ý¼º
int rsCheck_ResulSOD(User *lpPlayInfo, smTRANS_COMMAND_EX *lpTransCommandEx)
{
	DWORD Code;

#ifdef _W_SERVER
	Code = 0x0c5c55cc;

	Code ^= lpTransCommandEx->WParam << 1;
	Code ^= lpTransCommandEx->LParam << 2;
	Code ^= lpTransCommandEx->SParam << 3;
	Code ^= lpTransCommandEx->EParam << 4;

	Code ^= lpTransCommandEx->WxParam << 16;
	Code ^= lpTransCommandEx->LxParam << 17;
	Code ^= lpTransCommandEx->SxParam << 18;

	Code ^= lpPlayInfo->iID << 16;

#else
	Code = 0x3ea832ff;
#endif

	return Code & 0x7FFFFFFF;
}
int rsSend_ResultSOD(User *lpPlayInfo, int Point, int KillCount, int TotalPoint, int TotalSucessUser, int TotalUser, int SoDCode)
{
	smTRANS_COMMAND_EX	smTransCommand;

	smTransCommand.code = smTRANSCODE_SOD_RESULT;
	smTransCommand.size = sizeof(smTRANS_COMMAND_EX);
	smTransCommand.WParam = lpPlayInfo->sCharacterData.iLevel;
	smTransCommand.LParam = Point;
	smTransCommand.SParam = KillCount;
	smTransCommand.EParam = SoDCode;
	smTransCommand.WxParam = TotalPoint;
	smTransCommand.LxParam = TotalSucessUser;
	smTransCommand.SxParam = TotalUser;
	smTransCommand.ExParam = rsCheck_ResulSOD(lpPlayInfo, &smTransCommand);
	rsSendDataServer(lpPlayInfo, &smTransCommand);

	return TRUE;
}
int rsCompAttackData(User *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{
	int avg1, avg2;
	smTRANS_COMMAND	smTransCommand;

	if (lpPlayInfo->Send_AttackCount > 255)
	{
		avg1 = lpPlayInfo->Send_AttackDamage / lpPlayInfo->Send_AttackCount;
		if (lpTransCommand->WParam)
			avg2 = (-lpTransCommand->LParam) / (-lpTransCommand->WParam);
		else
			avg2 = 0;

		if (avg1 > (((avg2 * 340) >> 8) + 16) && lpPlayInfo->WarningCount < 10)
		{
			smTransCommand.code = smTRANSCODE_SET_BLACKLIST;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.WParam = 8110;
			smTransCommand.LParam = avg1;
			smTransCommand.SParam = avg2;
			smTransCommand.EParam = lpPlayInfo->Send_AttackCount;
			if (lpPlayInfo) {
				rsSendDataServer(lpPlayInfo, &smTransCommand);
			}
			lpPlayInfo->WarningCount++;
		}
	}

	return TRUE;
}

int CheckInvenItemPosition(User *lpPlayInfo, TRANS_USINGITEM *lpTransUsingItem)
{
#ifdef _W_SERVER

	int cnt, cnt2;
	int Pos;
	DWORD dwCode;
	int	MaxAttack;
	smTRANS_COMMAND	smTransCommand;

	MaxAttack = 4;

	int	PosOk;

	for (cnt = 0; cnt < lpTransUsingItem->ItemListCount; cnt++)
	{
		dwCode = lpTransUsingItem->ItemList[cnt].dwCode&sinITEM_MASK2;
		Pos = lpTransUsingItem->ItemList[cnt].Performance[0] & 0xFF;
		PosOk = TRUE;

		if (lpTransUsingItem->ItemList[cnt].Performance[1] > MaxAttack)
			MaxAttack = lpTransUsingItem->ItemList[cnt].Performance[1];

		switch (dwCode)
		{
		case sinWA1:
		case sinWC1:
		case sinWH1:
		case sinWM1:
		case sinWN1:
		case sinWP1:
		case sinWS1:
		case sinWS2:
		case sinWT1:
		case sinTW1:
			if (Pos != 1)
				PosOk = FALSE;
			break;
		case sinWD1:
			if (Pos != 1 && Pos != 2)
				PosOk = FALSE;
			break;
		case sinDA1:
		case sinDA2:
			if (Pos != 3)
				PosOk = FALSE;
			break;
		case sinCA1:
			if (Pos != 14)
				PosOk = FALSE;
			break;
		case sinCW1:
			if (Pos != 15)
				PosOk = FALSE;
			break;
		case sinDB1:
			if (Pos != 10)
				PosOk = FALSE;
			break;
		case sinDG1:
			if (Pos != 9)
				PosOk = FALSE;
			break;
		case sinDS1:
		case sinOM1:
			if (Pos != 2)
				PosOk = FALSE;
			break;
		case sinPL1:
		case sinPS1:
		case sinPM1:
			if (Pos < 11 || Pos>13)
				PosOk = FALSE;
			break;
		case sinOS1:
			if (Pos != 7)
				PosOk = FALSE;
			break;
		case sinOA1:
			if (Pos != 4)
				PosOk = FALSE;
			break;
		case sinOA2:
			if (Pos != 8)
				PosOk = FALSE;
			break;
		case sinOR1:
			if (Pos != 5 && Pos != 6)
				PosOk = FALSE;
			break;
		}

		if (PosOk == FALSE)
		{
			smTransCommand.code = smTRANSCODE_SET_BLACKLIST;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.WParam = 8040;
			smTransCommand.LParam = lpTransUsingItem->ItemList[cnt].dwCode;
			smTransCommand.SParam = 0;
			smTransCommand.EParam = lpTransUsingItem->ItemList[cnt].Performance[0];

			if (lpPlayInfo)
				rsSendDataServer(lpPlayInfo, &smTransCommand);

			return FALSE;
		}

		for (cnt2 = 0; cnt2 < lpTransUsingItem->ItemListCount; cnt2++)
		{
			if (cnt != cnt2)
			{
				if (lpTransUsingItem->ItemList[cnt].Performance[0] == lpTransUsingItem->ItemList[cnt2].Performance[0])
				{
					smTransCommand.code = smTRANSCODE_SET_BLACKLIST;
					smTransCommand.size = sizeof(smTRANS_COMMAND);
					smTransCommand.WParam = 8040;
					smTransCommand.LParam = lpTransUsingItem->ItemList[cnt].dwCode;
					smTransCommand.SParam = lpTransUsingItem->ItemList[cnt2].dwCode;
					smTransCommand.EParam = lpTransUsingItem->ItemList[cnt2].Performance[0];

					if (lpPlayInfo)
						rsSendDataServer(lpPlayInfo, &smTransCommand);
					return FALSE;
				}
			}
		}
	}

#endif
	return TRUE;
}

int CheckInvenItemPosition2(User *lpPlayInfo, TRANS_USINGITEM *lpTransUsingItem)
{

#ifdef _W_SERVER

	int cnt, cnt2;
	int Pos;
	DWORD dwCode;
	int	MaxAttack;
	smTRANS_COMMAND	smTransCommand;
	int	eWeapon, eShield;
	DWORD eWeaponCode, eShieldCode;
	DWORD eDaggerCode[2];

	MaxAttack = 4;
	eWeapon = 0;
	eShield = 0;
	eDaggerCode[0] = NULL;
	eDaggerCode[1] = NULL;

	int	PosOk;

	for (cnt = 0; cnt < lpTransUsingItem->ItemListCount; cnt++)
	{
		dwCode = lpTransUsingItem->ItemList[cnt].dwCode&sinITEM_MASK2;
		Pos = lpTransUsingItem->ItemList[cnt].Performance[0] & 0xFF;
		PosOk = TRUE;

		if (lpTransUsingItem->ItemList[cnt].Performance[1] > MaxAttack)
			MaxAttack = lpTransUsingItem->ItemList[cnt].Performance[1];

		switch (dwCode)
		{
		case sinWA1:
		case sinWC1:
		case sinWH1:
		case sinWM1:
		case sinWN1:
		case sinWP1:
		case sinWS1:
		case sinWS2:
		case sinWT1:
		case sinTW1:
			if (Pos != 1)
				PosOk = FALSE;
			eWeapon++;
			eWeaponCode = lpTransUsingItem->ItemList[cnt].dwCode;
			break;
		case sinWD1:
			if (Pos != 1 && Pos != 2)
				PosOk = FALSE;
			else
				eDaggerCode[Pos - 1] = lpTransUsingItem->ItemList[cnt].dwCode;
			break;
		case sinDA1:
		case sinDA2:
			if (Pos != 3)
				PosOk = FALSE;
			break;
		case sinCA1:
			if (Pos != 14)
				PosOk = FALSE;
			break;
		case sinCW1:
			if (Pos != 15)
				PosOk = FALSE;
			break;
		case sinDB1:
			if (Pos != 10)
				PosOk = FALSE;
			break;
		case sinDG1:
			if (Pos != 9)
				PosOk = FALSE;
			break;
		case sinDS1:
		case sinOM1:
			if (Pos != 2)
				PosOk = FALSE;
			eShield++;
			eShieldCode = lpTransUsingItem->ItemList[cnt].dwCode;
			break;
		case sinPL1:
		case sinPS1:
		case sinPM1:
			if (Pos < 11 || Pos>13)
				PosOk = FALSE;
			break;
		case sinOS1:
			if (Pos != 7)
				PosOk = FALSE;
			break;
		case sinOA1:
			if (Pos != 4)
				PosOk = FALSE;
			break;
		case sinOA2:
			if (Pos != 8)
				PosOk = FALSE;
			break;
		case sinOR1:
			if (Pos != 5 && Pos != 6)
				PosOk = FALSE;
			break;
		}

		if (PosOk == FALSE)
		{
			smTransCommand.code = smTRANSCODE_SET_BLACKLIST;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.WParam = 8040;
			smTransCommand.LParam = lpTransUsingItem->ItemList[cnt].dwCode;
			smTransCommand.SParam = 0;
			smTransCommand.EParam = lpTransUsingItem->ItemList[cnt].Performance[0];

			if (lpPlayInfo)
				rsSendDataServer(lpPlayInfo, &smTransCommand);

			return FALSE;
		}

		for (cnt2 = 0; cnt2 < lpTransUsingItem->ItemListCount; cnt2++)
		{
			if (cnt != cnt2)
			{
				if (lpTransUsingItem->ItemList[cnt].Performance[0] == lpTransUsingItem->ItemList[cnt2].Performance[0])
				{
					smTransCommand.code = smTRANSCODE_SET_BLACKLIST;
					smTransCommand.size = sizeof(smTRANS_COMMAND);
					smTransCommand.WParam = 8040;
					smTransCommand.LParam = lpTransUsingItem->ItemList[cnt].dwCode;
					smTransCommand.SParam = lpTransUsingItem->ItemList[cnt2].dwCode;
					smTransCommand.EParam = lpTransUsingItem->ItemList[cnt2].Performance[0];

					if (lpPlayInfo)
						rsSendDataServer(lpPlayInfo, &smTransCommand);

					return FALSE;
				}
			}
		}
	}

	if (eShield && eWeapon)
	{
		if (rsGetItemClass(eWeaponCode) == ITEMSLOTFLAG_LeftRightHand)
		{
			smTransCommand.code = smTRANSCODE_SET_BLACKLIST;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.WParam = 8040;
			smTransCommand.LParam = eWeaponCode;
			smTransCommand.SParam = eShieldCode;
			smTransCommand.EParam = -1;

			rsSendDataServer(lpPlayInfo, &smTransCommand);
			return FALSE;
		}
	}
	int ErrorFlag = 0;

	if (eDaggerCode[0] != NULL || eDaggerCode[1] != NULL)
	{
		if (lpPlayInfo->sCharacterData.iClass == CHARACTERCLASS_Assassin)
		{
			if (eShield)
				ErrorFlag++;
			if (eWeapon)
			{
				if (rsGetItemClass(eWeaponCode) == ITEMSLOTFLAG_LeftRightHand)
					ErrorFlag++;
			}
		}
		else
		{
			if (eWeapon)
				ErrorFlag++;
		}
		if (ErrorFlag != 0)
		{
			smTransCommand.code = smTRANSCODE_SET_BLACKLIST;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.WParam = 8040;
			smTransCommand.LParam = 0;
			smTransCommand.SParam = 0;
			smTransCommand.EParam = 0;

			rsSendDataServer(lpPlayInfo, &smTransCommand);
			return FALSE;
		}
	}

#endif
	return TRUE;
}
int rsRecvRecordTradeItem(User *lpPlayInfo, TRANS_RECORD_TRADE_ITEMS *lpTransRecordTradeItems)
{
	return TRUE;
}
int rsCheckItemTempCode(User *lpPlayInfo, Item *lpItem)
{

#ifdef _W_SERVER
	if (lpItem->iChk2 == (lpItem->Temp0 - lpItem->sItemID.ToInt()))
		return TRUE;
	if ((lpItem->sItemID.ToItemBase()) == (sinPM1&sinITEM_MASK1))
		return TRUE;

	smTRANS_COMMAND	smTransCommand;
	smTransCommand.code = smTRANSCODE_SET_BLACKLIST;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 6810;
	smTransCommand.LParam = lpItem->sItemID.ToInt();
	smTransCommand.SParam = lpItem->iChk1;
	smTransCommand.EParam = lpItem->iChk2;

	rsSendDataServer(lpPlayInfo, &smTransCommand);
#endif
	return FALSE;
}
int	rsCheckItemCode(User *lpPlayInfo, Item *lpItem)
{
#ifdef _W_SERVER
	int result;

	TRANS_ITEM_CODE	TransItemCode;

	if (!lpItem->szItemName[0])
		return TRUE;

	result = CheckItemForm(lpItem);

	if (result == TRUE)
		result = CheckMixItem(lpItem);

	if (result == TRUE)
	{
		rsCheckItemTempCode(lpPlayInfo, lpItem);

		return TRUE;
	}

#ifndef	_NEW_ITEM_FORMCODE

	return TRUE;

#endif

	if (lpItem->iChk1 == 0 || (lpItem->sItemID.ToItemType()) == sinQT1)
		return TRUE;


	TransItemCode.code = smTRANSCODE_ERRORITEM;
	TransItemCode.size = sizeof(TRANS_ITEM_CODE);
	TransItemCode.dwFlag = FALSE;
	TransItemCode.dwHead = lpItem->iChk1;
	TransItemCode.dwChkSum = lpItem->iChk2;
	TransItemCode.dwItemCode = lpItem->sItemID.ToInt();
	TransItemCode.dwTime = 0;

	SENDPACKET(lpPlayInfo, &TransItemCode);

	smTRANS_COMMAND	smTransCommand;
	smTransCommand.code = smTRANSCODE_SET_BLACKLIST;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 6800;
	smTransCommand.LParam = lpItem->sItemID.ToInt();
	smTransCommand.SParam = lpItem->iChk1;
	smTransCommand.EParam = lpItem->iChk2;
	rsSendDataServer(lpPlayInfo, &smTransCommand);

	char	*szErrorItemDir = "ItemError";
	char	szBuff[256];
	FILE	*fp;

	CreateDirectory(szErrorItemDir, NULL);
	wsprintf(szBuff, "%s\\%s(%d).itm", szErrorItemDir, lpPlayInfo->sCharacterData.szName, lpItem->iChk2);
	fopen_s(&fp,szBuff, "wb");
	if (fp) {
		fwrite(lpItem, sizeof(Item), 1, fp);
		fclose(fp);
	}


#endif

	return TRUE;
}


#ifdef	_W_SERVER

int	rsRegist_ItemSecCode(User *lpPlayInfo, smTRANS_COMMAND_EX *lpTransCommandEx)
{
	DWORD	cnt;
	DWORD	Key;

	DWORD	dwOs = lpPlayInfo->iID;
	DWORD	dwCode_Name = lpPlayInfo->dwHashCharacterName;
	DWORD	dwSvCode = SERVER_CODE;
	DWORD	dwSndCount = lpPlayInfo->SndItemSecCodeCount;
	DWORD	dwItemChkSum = lpTransCommandEx->LParam^lpTransCommandEx->SParam;
	DWORD	dwSeCode[4];

	Key = (SERVER_GAMETIME & 0xFFFF) ^ lpTransCommandEx->SParam;
	Key = Key ^ (Key << 10);

	if ((lpTransCommandEx->WParam&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
	{
		Key &= 0xFFFF0000;
		cnt = lpTransCommandEx->EParam^lpTransCommandEx->SParam^lpTransCommandEx->code;
		if (cnt == 0)
			cnt = 1;
		Key |= (cnt & 0xFFFF) ^ 0x3c15;
	}

	dwSeCode[0] = (dwSvCode << 16) | (dwSndCount & 0xFFFF);
	dwSeCode[0] &= 0x7FFFFFFF;

	dwSeCode[1] = dwItemChkSum ^ ((dwCode_Name & 0xFFFF) | (lpPlayInfo->iID << 16));
	dwSeCode[2] = lpTransCommandEx->ExParam^dwSeCode[0] ^ dwSeCode[1];
	dwSeCode[3] = Key;

	lpTransCommandEx->WxParam = dwSeCode[0] ^ (XOR_ITEM_SeCode_0^rsRegist_EnterKey(Key^lpPlayInfo->iID, 0));
	lpTransCommandEx->LxParam = dwSeCode[1] ^ (XOR_ITEM_SeCode_1^rsRegist_EnterKey(Key^lpPlayInfo->iID, 1));
	lpTransCommandEx->SxParam = dwSeCode[2] ^ (XOR_ITEM_SeCode_2^rsRegist_EnterKey(Key^lpPlayInfo->iID, 2));
	lpTransCommandEx->ExParam = dwSeCode[3];

	lpPlayInfo->SndItemSecCodeCount++;

	return TRUE;
}

int	rsRegist_ItemSecCode(User *lpPlayInfo, TRANS_ITEMINFO *lpTransItemInfo, int NewItem)
{
	DWORD	cnt;
	DWORD	Key;

	DWORD	dwOs = lpPlayInfo->iID;
	DWORD	dwCode_Name = lpPlayInfo->dwHashCharacterName;
	DWORD	dwSvCode = SERVER_CODE;
	DWORD	dwSndCount = lpPlayInfo->SndItemSecCodeCount;
	DWORD	dwItemChkSum = lpTransItemInfo->sItem.iChk2^lpTransItemInfo->sItem.iChk1;


	Key = (SERVER_GAMETIME & 0xFFFF) ^ dwItemChkSum;
	Key = Key ^ (Key << 10);

	if ((lpTransItemInfo->sItem.sItemID.ToItemBase()) == (sinPM1&sinITEM_MASK1))
	{
		Key &= 0xFFFF0000;
		cnt = lpTransItemInfo->sItem.iPotionCount;
		if (cnt == 0) cnt = 1;
		Key |= (cnt & 0xFFFF) ^ 0x3c15;
	}

	lpTransItemInfo->dwSeCode[0] = (dwSvCode << 16) | (dwSndCount & 0xFFFF);
	if (NewItem) lpTransItemInfo->dwSeCode[0] |= 0x8000000;
	else lpTransItemInfo->dwSeCode[0] &= 0x7FFFFFFF;

	lpTransItemInfo->dwSeCode[1] = dwItemChkSum ^ ((dwCode_Name & 0xFFFF) | (lpPlayInfo->iID << 16));
	lpTransItemInfo->dwSeCode[2] = lpTransItemInfo->sItem.iGold^lpTransItemInfo->dwSeCode[0] ^ lpTransItemInfo->dwSeCode[1];
	lpTransItemInfo->dwSeCode[3] = Key;

	lpTransItemInfo->dwSeCode[0] ^= (XOR_ITEM_SeCode_0^rsRegist_EnterKey(Key^lpPlayInfo->iID, 0));
	lpTransItemInfo->dwSeCode[1] ^= (XOR_ITEM_SeCode_1^rsRegist_EnterKey(Key^lpPlayInfo->iID, 1));
	lpTransItemInfo->dwSeCode[2] ^= (XOR_ITEM_SeCode_2^rsRegist_EnterKey(Key^lpPlayInfo->iID, 2));

	lpPlayInfo->SndItemSecCodeCount++;

	return TRUE;
}

int rsDEBUG_SecCode_SvCode;
int rsDEBUG_SecCode_SndCount;


int	rsCheck_ItemSecCode(User *lpPlayInfo, DWORD dwCode, DWORD dwHead, DWORD dwChkSum, int Money, DWORD dwSeCode_0, DWORD dwSeCode_1, DWORD dwSeCode_2, DWORD dwSeCode_3, int *pPotionCount)
{
	DWORD	cnt;
	DWORD	Key;

	DWORD	dwSeCode[4];
	smTRANS_COMMAND	smTransCommand;

	Key = dwSeCode_3;

	if ((dwCode&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
		*pPotionCount = (Key & 0xFFFF) ^ 0x3c15;
	else
		*pPotionCount = 0;

	dwSeCode[0] = dwSeCode_0 ^ (XOR_ITEM_SeCode_0^rsRegist_EnterKey(Key^lpPlayInfo->iID, 0));
	dwSeCode[1] = dwSeCode_1 ^ (XOR_ITEM_SeCode_1^rsRegist_EnterKey(Key^lpPlayInfo->iID, 1));
	dwSeCode[2] = dwSeCode_2 ^ (XOR_ITEM_SeCode_2^rsRegist_EnterKey(Key^lpPlayInfo->iID, 2));

	DWORD	dwSvCode;
	DWORD	dwCmpCode;
	int SndCount;

	dwCmpCode = (dwHead^dwChkSum) ^ ((lpPlayInfo->dwHashCharacterName & 0xFFFF) | (lpPlayInfo->iID << 16));
	if (dwSeCode[1] != dwCmpCode)
	{
		smTransCommand.WParam = 8020;
		smTransCommand.LParam = 1;
		smTransCommand.SParam = dwSeCode[1];
		smTransCommand.EParam = dwCmpCode;
		RecordHackLogFile(lpPlayInfo, &smTransCommand);
		return NULL;
	}

	dwCmpCode = Money ^ dwSeCode[0] ^ dwSeCode[1];
	if (dwCmpCode != dwSeCode[2])
	{
		smTransCommand.WParam = 8020;
		smTransCommand.LParam = 2;
		smTransCommand.SParam = dwSeCode[2];
		smTransCommand.EParam = dwCmpCode;
		RecordHackLogFile(lpPlayInfo, &smTransCommand);
		return NULL;
	}

	dwSvCode = (dwSeCode[0] & 0x7FFFFFF) >> 16;
	SndCount = dwSeCode[0] & 0xFFFF;

	if (dwSvCode >= 8)
		return NULL;

	rsDEBUG_SecCode_SvCode = dwSvCode;
	rsDEBUG_SecCode_SndCount = SndCount;

	int	Min, Max, sCnt;
	int	MinCnt;

	Min = 0xFFFF;
	Max = 0;

	for (cnt = 0; cnt < 16; cnt++)
	{
		sCnt = lpPlayInfo->RcvItemSecCodeBuff[dwSvCode][cnt];

		if (sCnt > Max)
			Max = sCnt;
		if (sCnt < Min)
		{
			Min = sCnt;
			MinCnt = cnt;
		}
		if (SndCount == sCnt)
		{
			smTransCommand.WParam = 8020;
			smTransCommand.LParam = 3;
			smTransCommand.SParam = dwSvCode;
			smTransCommand.EParam = SndCount;
			RecordHackLogFile(lpPlayInfo, &smTransCommand);
			return NULL;
		}
	}
	if ((Max - 16) > SndCount)
	{
		smTransCommand.WParam = 8020;
		smTransCommand.LParam = 4;
		smTransCommand.SParam = Max;
		smTransCommand.EParam = SndCount;
		RecordHackLogFile(lpPlayInfo, &smTransCommand);
		return NULL;
	}

	if (SndCount > Max)
		lpPlayInfo->RcvItemSecCodeBuff[dwSvCode][MinCnt] = SndCount;

	if (dwSeCode[0] & 0x7FFFFFF)
		return 2;

	return 1;
}

#else
int	rsRegist_ItemSecCode(User *lpPlayInfo, smTRANS_COMMAND_EX *lpTransCommandEx)
{
	return	TRUE;
}
int	rsRegist_ItemSecCode(User *lpPlayInfo, TRANS_ITEMINFO *lpTransItemInfo, int NewItem)
{
	return	TRUE;
}
int	rsCheck_ItemSecCode(User *lpPlayInfo, DWORD dwCode, DWORD dwHead, DWORD dwChkSum, int Money, DWORD dwSeCode_0, DWORD dwSeCode_1, DWORD dwSeCode_2, DWORD dwSeCode_3, int *pPotionCount)
{
	return	TRUE;
}

#endif


//´ÓÉÌµêÂòÎïÆ·Ð­Òé
int rsRecvBuyShopItem(User *lpPlayInfo, TRANS_BUY_SHOPITEM *lpTransBuyShopItem)
{
	int money;

	if (CheckItemForm(&lpTransBuyShopItem->sItem.sItem) == TRUE &&
		lpTransBuyShopItem->sItem.sItem.iSalePrice <= lpPlayInfo->GetGold())
	{
		ReformItem(&lpTransBuyShopItem->sItem.sItem);
		if (lpPlayInfo && lpPlayInfo->pcSocketData)
		{
			if (lpTransBuyShopItem->ItemCount > 0 && lpTransBuyShopItem->sItem.sItem.sItemID.ToItemBase() == ITEMBASE_Potion)
			{
				money = rsGetMoney(lpTransBuyShopItem->sItem.sItem.sItemID.ToInt(), TRUE) * lpTransBuyShopItem->ItemCount;

				SERVERUSER->SubServerUserGold(lpPlayInfo, money, WHEREID_BuyPotion);

				rsRecord_ItemLog(lpPlayInfo,
					lpTransBuyShopItem->sItem.sItem.sItemID.ToInt(),
					lpTransBuyShopItem->sItem.sItem.iChk1,
					lpTransBuyShopItem->sItem.sItem.iChk2,
					ITEMLOG_BUYSHOP);

				SERVERITEM->AddPotion(lpPlayInfo,
					lpTransBuyShopItem->sItem.sItem.sItemID.ToInt(),
					lpTransBuyShopItem->ItemCount);
			}
			else
			{
				money = rsGetMoney(lpTransBuyShopItem->sItem.sItem.sItemID.ToInt(), TRUE);

				SERVERUSER->SubServerUserGold(lpPlayInfo, money, WHEREID_BuyItem);

				SERVERITEM->AddItemInventory(lpPlayInfo,
					lpTransBuyShopItem->sItem.sItem.sItemID.ToInt(),
					lpTransBuyShopItem->sItem.sItem.iChk1,
					lpTransBuyShopItem->sItem.sItem.iChk2);

				rsRecord_ItemLog(lpPlayInfo,
					lpTransBuyShopItem->sItem.sItem.sItemID.ToInt(),
					lpTransBuyShopItem->sItem.sItem.iChk1,
					lpTransBuyShopItem->sItem.sItem.iChk2, ITEMLOG_BUYSHOP);
			}

			SENDPACKET(lpPlayInfo, lpTransBuyShopItem);

			return 0;
		}
	}

	if (lpTransBuyShopItem->sItem.sItem.iSalePrice > lpPlayInfo->GetGold())
	{
		smTRANS_COMMAND	smTransCommand;
		smTransCommand.WParam = 8010;
		smTransCommand.LParam = 10;
		smTransCommand.SParam = lpPlayInfo->GetGold();
		smTransCommand.EParam = lpTransBuyShopItem->sItem.sItem.iSalePrice;
		RecordHackLogFile(lpPlayInfo, &smTransCommand);
	}

	return FALSE;
}

//Âô³öµÀ¾ß
int rsRecvSellShopItem(User *lpPlayInfo, TRANS_ITEMINFO *lpTransItemInfo)
{
	smTRANS_COMMAND		smTransCommand;
	smTRANS_COMMAND_EX	smTransCommandEx;

	float Dur[2];
	float Price;
	int	  Price2, PriceMax;
	int	  PriceDiv;


	if ((lpTransItemInfo->sItem.sItemID.ToItemBase()) == (sinPM1&sinITEM_MASK1) || lpTransItemInfo->sItem.sItemID.ToInt() == (sinGF1 | sin01))
		return FALSE;

	if (CheckItemForm(&lpTransItemInfo->sItem) == FALSE)
	{
		smTransCommandEx.WParam = 8830;
		smTransCommandEx.LParam = lpTransItemInfo->sItem.sItemID.ToInt();
		smTransCommandEx.SParam = lpTransItemInfo->sItem.iSalePrice;
		smTransCommandEx.EParam = 0;
		RecordHackLogFile(lpPlayInfo, &smTransCommandEx);

		return FALSE;
	}

	if (SERVERITEM->DeleteItemInventory(lpPlayInfo,
		lpTransItemInfo->sItem.sItemID.ToInt(),
		lpTransItemInfo->sItem.iChk1,
		lpTransItemInfo->sItem.iChk2))
	{
		Dur[0] = lpTransItemInfo->sItem.sIntegrity.sMin;
		Dur[1] = lpTransItemInfo->sItem.sIntegrity.sMax;

		Price = float(rsGetMoney(lpTransItemInfo->sItem.sItemID.ToInt(), TRUE));

		if (Dur[0] == 0)
			Dur[0] = 1;
		if (Dur[1] == 0)
			Dur[1] = 1;

		PriceDiv = 5;

		Price2 = (int)((Price*(Dur[0] / Dur[1])) + (Price - (Price*(Dur[0] / Dur[1])))*0.25);
		Price2 = Price2 / PriceDiv;
		PriceMax = lpTransItemInfo->sItem.iSalePrice / PriceDiv;

		smTransCommand.code = smTRANSCODE_SHOP_SELLITEM;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = lpTransItemInfo->sItem.sItemID.ToInt();
		smTransCommand.LParam = lpTransItemInfo->sItem.iChk1;
		smTransCommand.SParam = lpTransItemInfo->sItem.iChk2;

		if (PriceMax < Price2)
			smTransCommand.EParam = PriceMax;
		else
			smTransCommand.EParam = Price2;

		if (lpTransItemInfo->sItem.sItemID.ToInt() == (sinSP1 | sin64) || lpTransItemInfo->sItem.sItemID.ToInt() == (sinSP1 | sin65) ||
			lpTransItemInfo->sItem.sItemID.ToInt() == (sinSP1 | sin66) || lpTransItemInfo->sItem.sItemID.ToInt() == (sinSP1 | sin67) ||
			lpTransItemInfo->sItem.sItemID.ToInt() == (sinSP1 | sin68))
			smTransCommand.EParam = int(Price);

		SENDPACKET(lpPlayInfo, &smTransCommand);

		lpPlayInfo->UnsaveMoney = lpTransItemInfo->y - smTransCommand.EParam;

		SERVERUSER->AddServerUserGold(lpPlayInfo, smTransCommand.EParam, WHEREID_SellItem);

		SaveThrowItem(lpPlayInfo, lpTransItemInfo->sItem.sItemID.ToInt(), lpTransItemInfo->sItem.iChk1, lpTransItemInfo->sItem.iChk2);

		rsRecord_ItemLog(lpPlayInfo, lpTransItemInfo->sItem.sItemID.ToInt(), lpTransItemInfo->sItem.iChk1, lpTransItemInfo->sItem.iChk2, ITEMLOG_SELLSHOP);
	}
	else
	{
		smTransCommandEx.WParam = 8000;
		smTransCommandEx.WxParam = 10;
		smTransCommandEx.LxParam = (int)lpTransItemInfo->sItem.szItemName;
		smTransCommandEx.LParam = lpTransItemInfo->sItem.sItemID.ToInt();
		smTransCommandEx.SParam = lpTransItemInfo->sItem.iChk1;
		smTransCommandEx.EParam = lpTransItemInfo->sItem.iChk2;
		RecordHackLogFile(lpPlayInfo, &smTransCommandEx);
	}

	return TRUE;
}

int	rsCompareItems(Item	*lpItem1, Item	*lpItem2)
{
	if (lpItem1->sItemID.ToInt() && lpItem1->sItemID.ToInt() == lpItem2->sItemID.ToInt())
	{
		if (lpItem1->dwTime == lpItem2->dwTime && lpItem1->iChk2 == lpItem2->iChk2 && lpItem1->iChk1 == lpItem2->iChk1)
			return TRUE;

		if (lpItem1->iChk2 == lpItem2->BackUpChkSum && lpItem1->iChk1 == lpItem2->BackUpKey)
			return TRUE;

		if (lpItem2->iChk2 == lpItem1->BackUpChkSum && lpItem2->iChk1 == lpItem1->BackUpKey)
			return TRUE;

		if (lpItem1->BackUpChkSum && lpItem1->BackUpKey && lpItem2->BackUpChkSum == lpItem1->BackUpChkSum && lpItem2->BackUpKey == lpItem1->BackUpKey)
			return TRUE;
	}

	return FALSE;
}
int rsCheckStgAreaItem(Map *lpStgArea, Item	*lpItem)
{
	int cnt;

	if (lpItem->sItemID.ToInt() < sinPM1 && (lpItem->sItemID.ToItemIndex()) >= sin08)
	{
		for (cnt = 0; cnt < STG_ITEM_MAX; cnt++)
		{
			if (lpStgArea->saLoot[cnt].bInUse)
			{
				if (rsCompareItems(lpItem, &lpStgArea->saLoot[cnt].sLootItem.sItem) == TRUE)
				{
					lpStgArea->saLoot[cnt].bInUse = FALSE;
					return FALSE;
				}
			}
		}
	}

	return TRUE;
}

int rsSendAreaServer(User *pcUser, void *szData)
{
	TRANS_SEND_DATASERVER	TransSendDataServer;
	int size;

	size = ((smTRANS_COMMAND *)szData)->size;

	if (size > 4096 || size < 0) return FALSE;

	memcpy(TransSendDataServer.szBuff, szData, size);
	TransSendDataServer.code = smTRANSCODE_SEND_AREASERVER;
	TransSendDataServer.size = size + 16;

	SENDPACKET(pcUser, &TransSendDataServer);

	return 0;
}

void rsSendDataServer(User *pcUser, void *szData)
{
	TRANS_SEND_DATASERVER	TransSendDataServer;
	int size;

	size = ((smTRANS_COMMAND *)szData)->size;

	if (size > 4096 || size < 0) 
		return;

	memcpy(TransSendDataServer.szBuff, szData, size);
	TransSendDataServer.code = smTRANSCODE_SEND_DATASERVER;
	TransSendDataServer.size = size + 16;

	SENDPACKET(pcUser, &TransSendDataServer);
}

void rsSendGameServer(User *pcUser, void *pcData)
{
	TRANS_SEND_DATASERVER	TransSendDataServer;
	int size;

	size = ((smTRANS_COMMAND *)pcData)->size;

	if (size > 4096 || size < 0) 
		return;

	memcpy(TransSendDataServer.szBuff, pcData, size);
	TransSendDataServer.code = smTRANSCODE_SEND_GAMESERVER;
	TransSendDataServer.size = size + 16;

	SENDPACKET(pcUser, &TransSendDataServer);
}

void rsSendAGameServer(User *pcUser, void *pcData)
{
	TRANS_SEND_DATASERVER TransSendDataServer;
	int size;

	size = ((smTRANS_COMMAND *)pcData)->size;

	if (size > 4096 || size < 0)
		return;

	memcpy(TransSendDataServer.szBuff, pcData, size);
	TransSendDataServer.code = smTRANSCODE_SEND_AGAME_SERVER;
	TransSendDataServer.size = size + 16;

	SENDPACKET(pcUser, &TransSendDataServer);
}
int rsSendAGameServer_PrimeItem2(User *pcUser, void *szData)
{
	TRANS_SEND_DATASERVER TransSendDataServer;
	int size;

	size = ((smTRANS_COMMAND *)szData)->size;

	if (size > 4096 || size < 0)
		return FALSE;

	memcpy(TransSendDataServer.szBuff, szData, size);
	TransSendDataServer.code = smTRANSCODE_SEND_AGAME_PRIMEITEM_DATA2;
	TransSendDataServer.size = size + 16;

	SENDPACKET(pcUser, &TransSendDataServer);

	return 0;
}
int rsSendAGameServer_PrimeItem3(User *pcUser, void *szData)
{
	TRANS_SEND_DATASERVER TransSendDataServer;
	int size;

	size = ((smTRANS_COMMAND *)szData)->size;

	if (size > 4096 || size < 0)
		return FALSE;

	memcpy(TransSendDataServer.szBuff, szData, size);
	TransSendDataServer.code = smTRANSCODE_SEND_AGAME_PRIMEITEM_DATA3;
	TransSendDataServer.size = size + 16;

	SENDPACKET(pcUser, &TransSendDataServer);

	return 0;
}
int rsSendAGameServer_PrimeItem4(User *pcUser, void *szData)
{
	TRANS_SEND_DATASERVER TransSendDataServer;
	int size;

	size = ((smTRANS_COMMAND *)szData)->size;

	if (size > 4096 || size < 0)
		return FALSE;

	memcpy(TransSendDataServer.szBuff, szData, size);
	TransSendDataServer.code = smTRANSCODE_SEND_AGAME_PRIMEITEM_DATA4;
	TransSendDataServer.size = size + 16;

	SENDPACKET(pcUser, &TransSendDataServer);

	return 0;
}
//½ÓÊÜ×îºóµÄ¾­Ñé¼ì²âÊ±¼ä
int	rsCheckTotalExpMoney(User *lpPlayInfo, TRANS_TOTAL_EXPMONEY *TransTotalExpMoney)
{
	lpPlayInfo->dwLastExpMoneyCheckTime = SERVER_GAMETIME;

	return TRUE;
}

#ifdef	_W_SERVER

int rsSendAGameServer_CaravanHopy(User *lpPlayInfo)
{
	smTRANS_COMMAND smTransCommand;

	if (lpPlayInfo->dwCaravan_Hopy_Time)
	{
		if (lpPlayInfo->dwCaravan_SetNextTime < SERVER_GAMETIME)
		{
			lpPlayInfo->dwCaravan_SetNextTime = SERVER_GAMETIME + 1000 * 60;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.code = smTRANSCODE_CARAVAN_HOPY;
			smTransCommand.WParam = lpPlayInfo->dwCaravan_Hopy_Time^smTRANSCODE_CARAVAN_HOPY;
			smTransCommand.LParam = lpPlayInfo->dwCaravan_Param ^ smTRANSCODE_CARAVAN_HOPY;
			smTransCommand.SParam = 0;
			rsSendGameServer(lpPlayInfo, &smTransCommand);

			return 0;
		}
	}
	return FALSE;
}
int rsSendAGameServer_Phoenix(User *lpPlayInfo)
{
	smTRANS_COMMAND smTransCommand;

	if (lpPlayInfo->dwTime_PhenixPet)
	{
		if (lpPlayInfo->dwPhenixPet_SetNextTime < SERVER_GAMETIME)
		{
			lpPlayInfo->dwPhenixPet_SetNextTime = SERVER_GAMETIME + 1000 * 60;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.code = smTRANSCODE_PHENIX_PET;
			smTransCommand.WParam = lpPlayInfo->dwTime_PhenixPet ^ smTRANSCODE_PHENIX_PET;
			smTransCommand.LParam = lpPlayInfo->PhenixPetType ^ smTRANSCODE_PHENIX_PET;
			smTransCommand.SParam = 0;
			rsSendGameServer(lpPlayInfo, &smTransCommand);

			return 0;
		}
	}
	return FALSE;
}
int rsSendAGameServer_BigHead(User *lpPlayInfo)
{
	smTRANS_COMMAND smTransCommand;

	if (lpPlayInfo->dwTime_BigHead)
	{
		if (lpPlayInfo->dwBigHead_SetNextTime < SERVER_GAMETIME)
		{
			lpPlayInfo->dwBigHead_SetNextTime = SERVER_GAMETIME + 1000 * 60;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.code = smTRANSCODE_COMIC_SKIN;
			smTransCommand.WParam = lpPlayInfo->dwTime_BigHead ^ smTRANSCODE_COMIC_SKIN;
			smTransCommand.LParam = lpPlayInfo->BigHeadType ^ smTRANSCODE_COMIC_SKIN;
			smTransCommand.SParam = 0;
			rsSendGameServer(lpPlayInfo, &smTransCommand);

			return 0;
		}
	}

	return FALSE;
}
int rsSendGameServer_PrimeItem(User *lpPlayInfo)
{
	smTRANS_COMMAND_EX	smTransCommand;
	DWORD	dwCodeKey;
	DWORD	dwMaskKey;
	DWORD	dwServTime_T = (DWORD)SERVER_LOCATIME;

	if (lpPlayInfo->dwPrimeItem_NextSetTime < SERVER_GAMETIME)
	{
		dwCodeKey = SERVER_GAMETIME & 0x3FFFFFFF;
		lpPlayInfo->dwPrimeItem_NextSetTime = SERVER_GAMETIME + 1000 * 60;

		dwMaskKey = lpPlayInfo->iID*(lpPlayInfo->dwHashCharacterName << 3);
		dwMaskKey ^= dwCodeKey;

		smTransCommand.code = smTRANSCODE_PRIMEITEM_DATA;
		smTransCommand.size = sizeof(smTRANS_COMMAND_EX);
		smTransCommand.WParam = (lpPlayInfo->dwTime_PrimeItem_X2) ^ dwMaskKey;
		smTransCommand.LParam = (lpPlayInfo->dwTime_PrimeItem_ExpUp) ^ dwMaskKey;
		smTransCommand.SParam = (lpPlayInfo->dwTime_PrimeItem_X2 + lpPlayInfo->dwTime_PrimeItem_ExpUp + smTransCommand.code) ^ dwMaskKey;
		smTransCommand.EParam = dwCodeKey;
		smTransCommand.WxParam = (lpPlayInfo->dwTime_PrimeItem_VampCuspid) ^ dwMaskKey;
		smTransCommand.LxParam = (lpPlayInfo->dwTime_PrimeItem_ManaRecharg) ^ dwMaskKey;
		smTransCommand.SxParam = (lpPlayInfo->dwTime_PrimeItem_VampCuspid + lpPlayInfo->dwTime_PrimeItem_ManaRecharg + smTransCommand.code) ^ dwMaskKey;
		smTransCommand.ExParam = (lpPlayInfo->dwPrimeItem_PackageCode ^ ((smTransCommand.WParam + smTransCommand.LParam)) ^ dwMaskKey);

		rsSendAGameServer(lpPlayInfo, &smTransCommand);
		rsSendGameServer_PrimeItem2(lpPlayInfo);
		rsSendGameServer_PrimeItem3(lpPlayInfo);
	}

	return TRUE;
}

int rsSendGameServer_PrimeItem2(User *lpPlayInfo)
{
	smTRANS_COMMAND_EX	smTransCommand;
	DWORD	dwCodeKey;
	DWORD	dwMaskKey;
	DWORD	dwServTime_T = (DWORD)SERVER_LOCATIME;

	dwCodeKey = SERVER_GAMETIME & 0x3FFFFFFF;

	dwMaskKey = lpPlayInfo->iID*(lpPlayInfo->dwHashCharacterName << 3);
	dwMaskKey ^= dwCodeKey;

	smTransCommand.code = smTRANSCODE_PRIMEITEM_DATA2;
	smTransCommand.size = sizeof(smTRANS_COMMAND_EX);
	smTransCommand.WParam = (lpPlayInfo->dwTime_PrimeItem_ManaReduce) ^ dwMaskKey;
	smTransCommand.LParam = (lpPlayInfo->dwTime_PrimeItem_MightofAwell) ^ dwMaskKey;
	smTransCommand.SParam = (lpPlayInfo->dwTime_PrimeItem_ManaReduce + lpPlayInfo->dwTime_PrimeItem_MightofAwell + smTransCommand.code) ^ dwMaskKey;
	smTransCommand.EParam = dwCodeKey;
	smTransCommand.WxParam = (lpPlayInfo->dwTime_PrimeItem_MightofAwell2) ^ dwMaskKey;
	smTransCommand.LxParam = (lpPlayInfo->dwTime_PrimeItem_PhenixPet) ^ dwMaskKey;
	smTransCommand.SxParam = (lpPlayInfo->dwTime_PrimeItem_MightofAwell2 + lpPlayInfo->dwTime_PrimeItem_PhenixPet + smTransCommand.code) ^ dwMaskKey;

	rsSendAGameServer_PrimeItem2(lpPlayInfo, &smTransCommand);

	return TRUE;
}
int rsSendGameServer_PrimeItem3(User *lpPlayInfo)
{
	smTRANS_COMMAND_EX	smTransCommand;
	DWORD	dwCodeKey;
	DWORD	dwMaskKey;

	dwCodeKey = SERVER_GAMETIME & 0x3FFFFFFF;
	dwMaskKey = lpPlayInfo->iID*(lpPlayInfo->dwHashCharacterName << 3);
	dwMaskKey ^= dwCodeKey;

	smTransCommand.code = smTRANSCODE_PRIMEITEM_DATA3;
	smTransCommand.size = sizeof(smTRANS_COMMAND_EX);
	smTransCommand.WParam = (lpPlayInfo->dwTime_PrimeItem_HelpPet) ^ dwMaskKey;
	smTransCommand.LParam = (lpPlayInfo->dwTime_PrimeItem_VampCuspid_EX) ^ dwMaskKey;
	smTransCommand.SParam = (lpPlayInfo->dwTime_PrimeItem_HelpPet + lpPlayInfo->dwTime_PrimeItem_VampCuspid_EX + smTransCommand.code) ^ dwMaskKey;
	smTransCommand.EParam = dwCodeKey;
	smTransCommand.WxParam = (lpPlayInfo->dwTime_PrimeItem_StaminaReduce) ^ dwMaskKey;
	smTransCommand.LxParam = (0) ^ dwMaskKey;
	smTransCommand.SxParam = (lpPlayInfo->dwTime_PrimeItem_StaminaReduce + 0 + smTransCommand.code) ^ dwMaskKey;
	smTransCommand.ExParam = (0) ^ dwMaskKey;

	rsSendAGameServer_PrimeItem3(lpPlayInfo, &smTransCommand);

	return TRUE;
}
int rsSendGameServer_PrimeItem4(User *lpPlayInfo)
{
	smTRANS_COMMAND_EX	smTransCommand;
	DWORD	dwCodeKey;
	DWORD	dwMaskKey;
	DWORD	dwServTime_T = (DWORD)SERVER_LOCATIME;

	if (lpPlayInfo->dwPrimeItem_NextSetTime < SERVER_GAMETIME)
	{
		dwCodeKey = SERVER_GAMETIME & 0x3FFFFFFF;
		lpPlayInfo->dwPrimeItem_NextSetTime = SERVER_GAMETIME + 1000 * 60;

		dwMaskKey = lpPlayInfo->iID*(lpPlayInfo->dwHashCharacterName << 3);
		dwMaskKey ^= dwCodeKey;

		smTransCommand.code = smTRANSCODE_PRIMEITEM_DATA4;
		smTransCommand.size = sizeof(smTRANS_COMMAND_EX);
		smTransCommand.WParam = (lpPlayInfo->dwTime_PrimeItem_VampCuspid_EX) ^ dwMaskKey;
		smTransCommand.LParam = (0) ^ dwMaskKey;
		smTransCommand.SParam = (lpPlayInfo->dwTime_PrimeItem_VampCuspid_EX + 0 + smTransCommand.code) ^ dwMaskKey;
		smTransCommand.EParam = dwCodeKey;
		smTransCommand.WxParam = (0) ^ dwMaskKey;
		smTransCommand.LxParam = (0) ^ dwMaskKey;
		smTransCommand.SxParam = (0) ^ dwMaskKey;
		smTransCommand.ExParam = (0) ^ dwMaskKey;

		rsSendAGameServer_PrimeItem4(lpPlayInfo, &smTransCommand);
	}

	return TRUE;
}
int rsRecvGameServer_PrimeItem(User *lpPlayInfo, smTRANS_COMMAND_EX *lpTransCommand)
{
	DWORD	dwCodeKey;
	DWORD	dwMaskKey;

	smTRANS_COMMAND_EX	smTransCommand;

	memcpy(&smTransCommand, lpTransCommand, sizeof(smTRANS_COMMAND_EX));

	dwCodeKey = lpTransCommand->EParam;
	dwMaskKey = lpPlayInfo->iID * (lpPlayInfo->dwHashCharacterName << 3);
	dwMaskKey ^= dwCodeKey;

	smTransCommand.WParam ^= dwMaskKey;
	smTransCommand.LParam ^= dwMaskKey;
	smTransCommand.SParam ^= dwMaskKey;
	smTransCommand.WxParam ^= dwMaskKey;
	smTransCommand.LxParam ^= dwMaskKey;
	smTransCommand.SxParam ^= dwMaskKey;
	smTransCommand.ExParam ^= (lpTransCommand->WParam + lpTransCommand->LParam) ^ dwMaskKey;

	if (smTransCommand.SParam == ((smTransCommand.WParam + smTransCommand.LParam + smTransCommand.code)))
	{
		lpPlayInfo->dwTime_PrimeItem_X2 = smTransCommand.WParam;
		lpPlayInfo->dwTime_PrimeItem_ExpUp = smTransCommand.LParam;
	}
	if (smTransCommand.SxParam == ((smTransCommand.WxParam + smTransCommand.LxParam + smTransCommand.code)))
	{
		lpPlayInfo->dwTime_PrimeItem_VampCuspid = smTransCommand.WxParam;
		lpPlayInfo->dwTime_PrimeItem_ManaRecharg = smTransCommand.LxParam;
	}

	if (smTransCommand.WParam || smTransCommand.LParam)
		lpPlayInfo->dwPrimeItem_PackageCode = smTransCommand.ExParam;

	return TRUE;
}
int rsRecvGameServer_PrimeItem2(User *lpPlayInfo, smTRANS_COMMAND_EX *lpTransCommand)
{
	DWORD	dwCodeKey;
	DWORD	dwMaskKey;

	smTRANS_COMMAND_EX	smTransCommand;

	memcpy(&smTransCommand, lpTransCommand, sizeof(smTRANS_COMMAND_EX));

	dwCodeKey = lpTransCommand->EParam;
	dwMaskKey = lpPlayInfo->iID*(lpPlayInfo->dwHashCharacterName << 3);
	dwMaskKey ^= dwCodeKey;

	smTransCommand.WParam ^= dwMaskKey;
	smTransCommand.LParam ^= dwMaskKey;
	smTransCommand.SParam ^= dwMaskKey;
	smTransCommand.WxParam ^= dwMaskKey;
	smTransCommand.LxParam ^= dwMaskKey;
	smTransCommand.SxParam ^= dwMaskKey;
	smTransCommand.ExParam ^= (lpTransCommand->WParam + lpTransCommand->LParam) ^ dwMaskKey;

	if (smTransCommand.SParam == (smTransCommand.WParam + smTransCommand.LParam + smTransCommand.code))
	{
		lpPlayInfo->dwTime_PrimeItem_ManaReduce = smTransCommand.WParam;
		lpPlayInfo->dwTime_PrimeItem_MightofAwell = smTransCommand.LParam;
	}
	if (smTransCommand.SxParam == ((smTransCommand.WxParam + smTransCommand.LxParam + smTransCommand.code)))
	{
		lpPlayInfo->dwTime_PrimeItem_MightofAwell2 = smTransCommand.WxParam;
		lpPlayInfo->dwTime_PrimeItem_PhenixPet = smTransCommand.LxParam;
	}
	return TRUE;
}
int rsRecvGameServer_PrimeItem3(User *lpPlayInfo, smTRANS_COMMAND_EX *lpTransCommand)
{
	DWORD	dwCodeKey;
	DWORD	dwMaskKey;

	smTRANS_COMMAND_EX	smTransCommand;

	memcpy(&smTransCommand, lpTransCommand, sizeof(smTRANS_COMMAND_EX));

	dwCodeKey = lpTransCommand->EParam;
	dwMaskKey = lpPlayInfo->iID*(lpPlayInfo->dwHashCharacterName << 3);
	dwMaskKey ^= dwCodeKey;

	smTransCommand.WParam ^= dwMaskKey;
	smTransCommand.LParam ^= dwMaskKey;
	smTransCommand.SParam ^= dwMaskKey;
	smTransCommand.WxParam ^= dwMaskKey;
	smTransCommand.LxParam ^= dwMaskKey;
	smTransCommand.SxParam ^= dwMaskKey;
	smTransCommand.ExParam ^= (lpTransCommand->WParam + lpTransCommand->LParam) ^ dwMaskKey;

	if (smTransCommand.SParam == (smTransCommand.WParam + smTransCommand.LParam + smTransCommand.code))
	{
		lpPlayInfo->dwTime_PrimeItem_HelpPet = smTransCommand.WParam;
		lpPlayInfo->dwTime_PrimeItem_VampCuspid_EX = smTransCommand.LParam;
	}
	if (smTransCommand.SxParam == ((smTransCommand.WxParam + smTransCommand.LxParam + smTransCommand.code)))
		lpPlayInfo->dwTime_PrimeItem_StaminaReduce = smTransCommand.WxParam;

	return TRUE;
}
int rsRecvGameServer_PrimeItem4(User *lpPlayInfo, smTRANS_COMMAND_EX *lpTransCommand)
{
	DWORD	dwCodeKey;
	DWORD	dwMaskKey;

	smTRANS_COMMAND_EX	smTransCommand;

	memcpy(&smTransCommand, lpTransCommand, sizeof(smTRANS_COMMAND_EX));

	dwCodeKey = lpTransCommand->EParam;
	dwMaskKey = lpPlayInfo->iID*(lpPlayInfo->dwHashCharacterName << 3);
	dwMaskKey ^= dwCodeKey;

	smTransCommand.WParam ^= dwMaskKey;
	smTransCommand.LParam ^= dwMaskKey;
	smTransCommand.SParam ^= dwMaskKey;
	smTransCommand.WxParam ^= dwMaskKey;
	smTransCommand.LxParam ^= dwMaskKey;
	smTransCommand.SxParam ^= dwMaskKey;
	smTransCommand.ExParam ^= (lpTransCommand->WParam + lpTransCommand->LParam) ^ dwMaskKey;

	if (smTransCommand.SParam == (smTransCommand.WParam + smTransCommand.LParam + smTransCommand.code))
		lpPlayInfo->dwTime_PrimeItem_VampCuspid_EX = smTransCommand.WParam;

	return TRUE;
}
int rsSendAreaServer_PCBangPet(User *lpPlayInfo)
{
	smTRANS_COMMAND	smTransCommand;
	DWORD	dwCodeKey;
	DWORD	dwMaskKey;

	if (lpPlayInfo->iID && lpPlayInfo->dwPCBang_Pet_NextSetTime < SERVER_GAMETIME && lpPlayInfo->Bl_RNo>0)
	{
		if (!lpPlayInfo->dwPCBang_Pet_NextSetTime)
		{
			ZeroMemory(&smTransCommand, sizeof(smTRANS_COMMAND));
			smTransCommand.code = smTRANSCODE_PCBANG_PET;
			smTransCommand.size = sizeof(smTRANS_COMMAND);

			SENDPACKET(lpPlayInfo, &smTransCommand);
		}

		dwCodeKey = SERVER_GAMETIME & 0x3FFFFFFF;
		lpPlayInfo->dwPCBang_Pet_NextSetTime = SERVER_GAMETIME + 1000 * 17;

		dwMaskKey = lpPlayInfo->iID*(lpPlayInfo->dwHashCharacterName << 3);
		dwMaskKey ^= dwCodeKey;

		smTransCommand.code = smTRANSCODE_PCBANG_PET;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = (lpPlayInfo->Bl_RNo) ^ dwMaskKey;
		smTransCommand.LParam = (lpPlayInfo->dwPCBang_Pet_NextSetTime) ^ dwMaskKey;
		smTransCommand.SParam = (lpPlayInfo->Bl_RNo + lpPlayInfo->dwPCBang_Pet_NextSetTime + smTransCommand.code) ^ dwMaskKey;
		smTransCommand.EParam = dwCodeKey;

		rsSendAGameServer(lpPlayInfo, &smTransCommand);
	}

	return TRUE;
}
int rsRecvAreaServer_PCBangPet(User *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{
	DWORD	dwCodeKey;
	DWORD	dwMaskKey;

	smTRANS_COMMAND	smTransCommand;

	memcpy(&smTransCommand, lpTransCommand, sizeof(smTRANS_COMMAND));

	dwCodeKey = lpTransCommand->EParam;
	dwMaskKey = lpPlayInfo->iID * (lpPlayInfo->dwHashCharacterName << 3);
	dwMaskKey ^= dwCodeKey;

	smTransCommand.WParam ^= dwMaskKey;
	smTransCommand.LParam ^= dwMaskKey;
	smTransCommand.SParam ^= dwMaskKey;

	if (smTransCommand.SParam == ((smTransCommand.WParam + smTransCommand.LParam + smTransCommand.code))) {
		lpPlayInfo->Bl_RNo = smTransCommand.WParam;
		return TRUE;
	}

	return FALSE;
}
int rsSendAreaServer_HelpPet(User *lpPlayInfo)
{
	smTRANS_COMMAND	smTransCommand;
	DWORD	dwCodeKey;
	DWORD	dwMaskKey;

	if (lpPlayInfo->iID && lpPlayInfo->dwHelp_Pet_NextSetTime < SERVER_GAMETIME && lpPlayInfo->dwTime_PrimeItem_HelpPet > 0)
	{
		if (!lpPlayInfo->dwHelp_Pet_NextSetTime)
		{
			ZeroMemory(&smTransCommand, sizeof(smTRANS_COMMAND));
			smTransCommand.code = smTRANSCODE_HELP_PET;
			smTransCommand.size = sizeof(smTRANS_COMMAND);

			SENDPACKET(lpPlayInfo, &smTransCommand);
		}

		dwCodeKey = SERVER_GAMETIME & 0x3FFFFFFF;
		lpPlayInfo->dwHelp_Pet_NextSetTime = SERVER_GAMETIME + 1000 * 17;

		dwMaskKey = lpPlayInfo->iID*(lpPlayInfo->dwHashCharacterName << 3);
		dwMaskKey ^= dwCodeKey;

		smTransCommand.code = smTRANSCODE_HELP_PET;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = (lpPlayInfo->dwTime_PrimeItem_HelpPet) ^ dwMaskKey;
		smTransCommand.LParam = (lpPlayInfo->dwHelp_Pet_NextSetTime) ^ dwMaskKey;
		smTransCommand.SParam = (lpPlayInfo->dwTime_PrimeItem_HelpPet + lpPlayInfo->dwHelp_Pet_NextSetTime + smTransCommand.code) ^ dwMaskKey;
		smTransCommand.EParam = dwCodeKey;

		rsSendAGameServer_PrimeItem3(lpPlayInfo, &smTransCommand);
	}

	return TRUE;
}
int rsRecvAreaServer_HelpPet(User *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{
	DWORD	dwCodeKey;
	DWORD	dwMaskKey;

	smTRANS_COMMAND	smTransCommand;

	memcpy(&smTransCommand, lpTransCommand, sizeof(smTRANS_COMMAND));

	dwCodeKey = lpTransCommand->EParam;
	dwMaskKey = lpPlayInfo->iID*(lpPlayInfo->dwHashCharacterName << 3);
	dwMaskKey ^= dwCodeKey;

	smTransCommand.WParam ^= dwMaskKey;
	smTransCommand.LParam ^= dwMaskKey;
	smTransCommand.SParam ^= dwMaskKey;

	if (smTransCommand.SParam == ((smTransCommand.WParam + smTransCommand.LParam + smTransCommand.code)))
	{
		lpPlayInfo->dwTime_PrimeItem_HelpPet = smTransCommand.WParam;
		return TRUE;
	}

	return FALSE;
}
int rsSendServerToForceOrb(User *lpPlayInfo)
{
	smTRANS_COMMAND	smTransCommand;

	ZeroMemory(&smTransCommand, sizeof(smTRANS_COMMAND));

	if (lpPlayInfo->dwForceOrb_SaveTime)
	{
		smTransCommand.code = smTRANSCODE_FORCEORB_DATA;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = lpPlayInfo->dwForceOrb_SaveCode ^ smTRANSCODE_FORCEORB_DATA;
		smTransCommand.LParam = (lpPlayInfo->dwForceOrb_SaveTime - SERVER_GAMETIME) ^ smTRANSCODE_FORCEORB_DATA;
	}
	else
	{
		smTransCommand.code = smTRANSCODE_FORCEORB_DATA;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = lpPlayInfo->dwForceOrb_SaveCode ^ smTRANSCODE_FORCEORB_DATA;
		smTransCommand.LParam = lpPlayInfo->dwForceOrb_SaveTime ^ smTRANSCODE_FORCEORB_DATA;
	}
	return rsSendAreaServer(lpPlayInfo, &smTransCommand);

}
int rsSendAreaServerForceOrb(User *lpPlayInfo)
{
	smTRANS_COMMAND	smTransCommand;

	ZeroMemory(&smTransCommand, sizeof(smTRANS_COMMAND));

	if (lpPlayInfo->dwForceOrb_SaveTime && lpPlayInfo->dwForceOrb_SaveTime > SERVER_GAMETIME)
	{
		if (lpPlayInfo->dwForceOrb_NextSetTime && lpPlayInfo->dwForceOrb_NextSetTime > SERVER_GAMETIME)
			return FALSE;

		lpPlayInfo->dwForceOrb_NextSetTime = SERVER_GAMETIME + 1000 * 60;

		smTransCommand.code = smTRANSCODE_FORCEORB_DATA;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = (lpPlayInfo->dwForceOrb_SaveCode) ^ smTRANSCODE_FORCEORB_DATA;
		smTransCommand.LParam = (lpPlayInfo->dwForceOrb_SaveTime - SERVER_GAMETIME) ^ smTRANSCODE_FORCEORB_DATA;
		rsSendAreaServer(lpPlayInfo, &smTransCommand);
	}
	else
	{
		lpPlayInfo->dwForceOrb_NextSetTime = 0;
		lpPlayInfo->dwForceOrb_SaveCode = 0;
		lpPlayInfo->dwForceOrb_SaveTime = 0;
		lpPlayInfo->dwForceOrb_SaveDamage = 0;
	}

	rsSendGameServer_PrimeItem(lpPlayInfo);

	rsSendAGameServer_CaravanHopy(lpPlayInfo);
	rsSendAGameServer_Phoenix(lpPlayInfo);
	rsSendAGameServer_BigHead(lpPlayInfo);

	if (rsServerConfig.Event_PCBangPet)
		rsSendAreaServer_PCBangPet(lpPlayInfo);

	if (lpPlayInfo->dwTime_PrimeItem_HelpPet > 0)
		rsSendAreaServer_HelpPet(lpPlayInfo);

	return TRUE;
}

//½ÓÊÜ·¶Î§µÄÁ¦Á¿Ê¯Í·Ð­Òé
int rsRecvAreaServerForceOrb(User *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{
	//	DWORD	dwCodeKey;
	//	DWORD	dwMaskKey;
	int		cnt;
	smTRANS_COMMAND	smTransCommand;

	DWORD	Code;
	DWORD	Time;

	memcpy(&smTransCommand, lpTransCommand, sizeof(smTRANS_COMMAND));

	Code = smTransCommand.WParam ^ smTRANSCODE_FORCEORB_DATA;
	Time = (smTransCommand.LParam ^ smTRANSCODE_FORCEORB_DATA) / 1000;

	if (Time)
	{
		if (lpPlayInfo->dwForceOrb_Code == NULL)
		{
			if ((Code &sinITEM_MASK2) == sinFO1)
			{
				cnt = (Code&sinITEM_MASK3) >> 8;

				cnt--;

				if (cnt >= 0 && cnt < 16)
				{
					lpPlayInfo->dwForceOrb_Code = Code;
					lpPlayInfo->iForceOrbTime = SERVER_GAMETIME + Time * 1000;
					lpPlayInfo->dwForceOrb_Damage = ForceOrbDamage[cnt];

					smTransCommand.code = smTRANSCODE_FORCE_ROE;
					smTransCommand.size = sizeof(smTRANS_COMMAND);
					smTransCommand.WParam = Code;
					smTransCommand.LParam = Time;
					smTransCommand.SParam = 0;
					smTransCommand.EParam = 0;

					SENDPACKET(lpPlayInfo, &smTransCommand);
				}
			}
		}
	}
	else
	{
		if (lpPlayInfo->dwForceOrb_Code)
		{
			lpPlayInfo->dwForceOrb_Code = NULL;
			lpPlayInfo->iForceOrbTime = NULL;
			lpPlayInfo->dwForceOrb_Damage = NULL;

			smTransCommand.code = smTRANSCODE_FORCE_ROE;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.WParam = 0;
			smTransCommand.LParam = 0;
			smTransCommand.SParam = 0;
			smTransCommand.EParam = 0;

			SENDPACKET(lpPlayInfo, &smTransCommand);
		}
	}

	return FALSE;
}
int rsSendAreaServerBoosterItem(User *lpPlayInfo)
{
	smTRANS_COMMAND	smTransCommand;
	DWORD	dwCodeKey;
	DWORD	dwMaskKey;

	if (lpPlayInfo->dwLifeBooster_SaveTime && lpPlayInfo->dwLifeBooster_SaveTime > SERVER_GAMETIME)
	{

		if (lpPlayInfo->dwLifeBooster_NextSetTime && lpPlayInfo->dwLifeBooster_NextSetTime > SERVER_GAMETIME)
			return FALSE;

		dwCodeKey = SERVER_GAMETIME & 0x3FFFFFFF;
		lpPlayInfo->dwLifeBooster_NextSetTime = SERVER_GAMETIME + 1000 * 30;

		dwMaskKey = lpPlayInfo->iID*(lpPlayInfo->dwHashCharacterName << 3);
		dwMaskKey ^= dwCodeKey;

		smTransCommand.code = smTRANSCODE_BOOSTER_DATA;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = (lpPlayInfo->dwLifeBooster_SaveCode) ^ dwMaskKey;
		smTransCommand.LParam = (lpPlayInfo->dwLifeBooster_SaveTime - SERVER_GAMETIME) ^ dwMaskKey;
		smTransCommand.SParam = lpPlayInfo->dwLifeBooster_SaveData^dwMaskKey;
		smTransCommand.EParam = dwCodeKey;

		rsSendAreaServer(lpPlayInfo, &smTransCommand);
	}
	else
	{
		lpPlayInfo->dwLifeBooster_NextSetTime = 0;
		lpPlayInfo->dwLifeBooster_SaveCode = 0;
		lpPlayInfo->dwLifeBooster_SaveTime = 0;
		lpPlayInfo->dwLifeBooster_SaveData = 0;
	}

	if (lpPlayInfo->dwManaBooster_SaveTime && lpPlayInfo->dwManaBooster_SaveTime > SERVER_GAMETIME)
	{

		if (lpPlayInfo->dwManaBooster_NextSetTime && lpPlayInfo->dwManaBooster_NextSetTime > SERVER_GAMETIME)
			return FALSE;

		dwCodeKey = SERVER_GAMETIME & 0x3FFFFFFF;
		lpPlayInfo->dwManaBooster_NextSetTime = SERVER_GAMETIME + 1000 * 30;

		dwMaskKey = lpPlayInfo->iID*(lpPlayInfo->dwHashCharacterName << 3);
		dwMaskKey ^= dwCodeKey;


		smTransCommand.code = smTRANSCODE_BOOSTER_DATA;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = (lpPlayInfo->dwManaBooster_SaveCode) ^ dwMaskKey;
		smTransCommand.LParam = (lpPlayInfo->dwManaBooster_SaveTime - SERVER_GAMETIME) ^ dwMaskKey;
		smTransCommand.SParam = lpPlayInfo->dwManaBooster_SaveData^dwMaskKey;
		smTransCommand.EParam = dwCodeKey;

		rsSendAreaServer(lpPlayInfo, &smTransCommand);
	}
	else
	{
		lpPlayInfo->dwManaBooster_NextSetTime = 0;
		lpPlayInfo->dwManaBooster_SaveCode = 0;
		lpPlayInfo->dwManaBooster_SaveTime = 0;
		lpPlayInfo->dwManaBooster_SaveData = 0;
	}

	if (lpPlayInfo->dwStaminaBooster_SaveTime && lpPlayInfo->dwStaminaBooster_SaveTime > SERVER_GAMETIME)
	{
		if (lpPlayInfo->dwStaminaBooster_NextSetTime && lpPlayInfo->dwStaminaBooster_NextSetTime > SERVER_GAMETIME)
			return FALSE;

		dwCodeKey = SERVER_GAMETIME & 0x3FFFFFFF;
		lpPlayInfo->dwStaminaBooster_NextSetTime = SERVER_GAMETIME + 1000 * 30;

		dwMaskKey = lpPlayInfo->iID*(lpPlayInfo->dwHashCharacterName << 3);
		dwMaskKey ^= dwCodeKey;


		smTransCommand.code = smTRANSCODE_BOOSTER_DATA;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = (lpPlayInfo->dwStaminaBooster_SaveCode) ^ dwMaskKey;
		smTransCommand.LParam = (lpPlayInfo->dwStaminaBooster_SaveTime - SERVER_GAMETIME) ^ dwMaskKey;
		smTransCommand.SParam = lpPlayInfo->dwStaminaBooster_SaveData^dwMaskKey;
		smTransCommand.EParam = dwCodeKey;

		rsSendAreaServer(lpPlayInfo, &smTransCommand);
	}
	else
	{
		lpPlayInfo->dwStaminaBooster_NextSetTime = 0;
		lpPlayInfo->dwStaminaBooster_SaveCode = 0;
		lpPlayInfo->dwStaminaBooster_SaveTime = 0;
		lpPlayInfo->dwStaminaBooster_SaveData = 0;
	}

	return TRUE;
}
int rsRecvAreaServerBoosterItem(User *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{
	DWORD	dwCodeKey;
	DWORD	dwMaskKey;
	DWORD	dwItemMask;
	int		cnt = 0;
	smTRANS_COMMAND	smTransCommand;

	memcpy(&smTransCommand, lpTransCommand, sizeof(smTRANS_COMMAND));

	dwCodeKey = lpTransCommand->EParam;
	dwMaskKey = lpPlayInfo->iID*(lpPlayInfo->dwHashCharacterName << 3);
	dwMaskKey ^= dwCodeKey;

	smTransCommand.WParam ^= dwMaskKey;
	smTransCommand.LParam ^= dwMaskKey;
	smTransCommand.SParam ^= dwMaskKey;

	if ((smTransCommand.WParam&sinITEM_MASK2) != sinBC1)
		return FALSE;

	dwItemMask = smTransCommand.WParam&sinITEM_MASK3;

	if (dwItemMask == sin21 || dwItemMask == sin24 || dwItemMask == sin27)
		cnt = 0;
	if (dwItemMask == sin22 || dwItemMask == sin25 || dwItemMask == sin28)
		cnt = 1;
	if (dwItemMask == sin23 || dwItemMask == sin26 || dwItemMask == sin29)
		cnt = 2;

	if (dwItemMask == sin21 || dwItemMask == sin22 || dwItemMask == sin23)
	{
		if (smTransCommand.LParam <= (BoosterItem_UseTime[cnt] * 1000))
		{
			lpPlayInfo->dwLifeBooster_Code = smTransCommand.WParam;
			lpPlayInfo->dwLifeBooster_Time = SERVER_GAMETIME + smTransCommand.LParam;
			lpPlayInfo->dwLifeBooster_Data = smTransCommand.SParam;
			return TRUE;
		}
	}
	if (dwItemMask == sin24 || dwItemMask == sin25 || dwItemMask == sin26)
	{
		if (smTransCommand.LParam <= (BoosterItem_UseTime[cnt] * 1000))
		{
			lpPlayInfo->dwManaBooster_Code = smTransCommand.WParam;
			lpPlayInfo->dwManaBooster_Time = SERVER_GAMETIME + smTransCommand.LParam;
			lpPlayInfo->dwManaBooster_Data = smTransCommand.SParam;
			return TRUE;
		}
	}
	if (dwItemMask == sin27 || dwItemMask == sin28 || dwItemMask == sin29)
	{
		if (smTransCommand.LParam <= (BoosterItem_UseTime[cnt] * 1000))
		{
			lpPlayInfo->dwStaminaBooster_Code = smTransCommand.WParam;
			lpPlayInfo->dwStaminaBooster_Time = SERVER_GAMETIME + smTransCommand.LParam;
			lpPlayInfo->dwStaminaBooster_Data = smTransCommand.SParam;
			return TRUE;
		}
	}

	return FALSE;
}
int rsSendAreaServerSkillDelayItem(User *lpPlayInfo)
{
	smTRANS_COMMAND	smTransCommand;
	DWORD	dwCodeKey;
	DWORD	dwMaskKey;

	if (lpPlayInfo->dwSkillDelay_SaveTime && lpPlayInfo->dwSkillDelay_SaveTime > SERVER_GAMETIME)
	{
		if (lpPlayInfo->dwSkillDelay_NextSetTime && lpPlayInfo->dwSkillDelay_NextSetTime > SERVER_GAMETIME)
			return FALSE;

		dwCodeKey = SERVER_GAMETIME & 0x3FFFFFFF;
		lpPlayInfo->dwSkillDelay_NextSetTime = SERVER_GAMETIME + 1000 * 30;		//30ÃÊ ´ÜÀ§·Î º¸³½´Ù

		dwMaskKey = lpPlayInfo->iID*(lpPlayInfo->dwHashCharacterName << 3);
		dwMaskKey ^= dwCodeKey;

		smTransCommand.code = smTRANSCODE_SKILLDELAY_DATA;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = (lpPlayInfo->dwSkillDelay_SaveCode) ^ dwMaskKey;
		smTransCommand.LParam = (lpPlayInfo->dwSkillDelay_SaveTime - SERVER_GAMETIME) ^ dwMaskKey;
		smTransCommand.SParam = lpPlayInfo->dwSkillDelay_SaveData^dwMaskKey;
		smTransCommand.EParam = dwCodeKey;

		rsSendAreaServer(lpPlayInfo, &smTransCommand);			//±º¼­¹ö¿¡ º¸°í
	}
	else
	{
		lpPlayInfo->dwSkillDelay_NextSetTime = 0;
		lpPlayInfo->dwSkillDelay_SaveCode = 0;
		lpPlayInfo->dwSkillDelay_SaveTime = 0;
		lpPlayInfo->dwSkillDelay_SaveData = 0;
	}


	return TRUE;
}

int rsRecvAreaServerSkillDelayItem(User *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{
	DWORD	dwCodeKey;
	DWORD	dwMaskKey;
	DWORD	dwItemMask;
	int		cnt = 0;
	smTRANS_COMMAND	smTransCommand;

	memcpy(&smTransCommand, lpTransCommand, sizeof(smTRANS_COMMAND));

	dwCodeKey = lpTransCommand->EParam;
	dwMaskKey = lpPlayInfo->iID*(lpPlayInfo->dwHashCharacterName << 3);
	dwMaskKey ^= dwCodeKey;

	smTransCommand.WParam ^= dwMaskKey; // ÄÚµå
	smTransCommand.LParam ^= dwMaskKey; // ½Ã°£
	smTransCommand.SParam ^= dwMaskKey; // ¼Ó¼º°ª

	if ((smTransCommand.WParam&sinITEM_MASK2) != sinBC1)
		return FALSE;

	dwItemMask = smTransCommand.WParam&sinITEM_MASK3;
	if (dwItemMask == sin30 || dwItemMask == sin33 || dwItemMask == sin36) cnt = 0; // 1½Ã°£
	if (dwItemMask == sin31 || dwItemMask == sin34 || dwItemMask == sin37) cnt = 1; // 3½Ã°£
	if (dwItemMask == sin32 || dwItemMask == sin35 || dwItemMask == sin38) cnt = 2; // 1ÀÏ

	if (dwItemMask == sin30 || dwItemMask == sin31 || dwItemMask == sin32)
	{
		if (smTransCommand.LParam <= (BoosterItem_UseTime[cnt] * 1000)) // ½Ã°£ ¼ÂÆÃ
		{
			lpPlayInfo->dwSkillDelay_Code = smTransCommand.WParam;
			lpPlayInfo->dwSkillDelay_Time = SERVER_GAMETIME + smTransCommand.LParam;
			lpPlayInfo->dwSkillDelay_Data = smTransCommand.SParam;
			return TRUE;
		}
	}

	return FALSE;
}

#endif

//ÁÖº¯ À¯Àú¿¡°Ô ¸í·É º¸³¿
int	rsSendCommandUser2(User *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{
	int cnt;
	int rx, rz, dist;
	int x, z;

	x = lpPlayInfo->sPosition.iX;
	z = lpPlayInfo->sPosition.iZ;

	for (cnt = 0; cnt < PLAYERS_MAX; cnt++)
	{
		User * u = USERSDATA + cnt;

		if (u && u->iID)
		{
			rx = (x - u->sPosition.iX) >> FLOATNS;
			rz = (z - u->sPosition.iZ) >> FLOATNS;
			dist = rx * rx + rz * rz;

			if (dist < DIST_TRANSLEVEL_HIGH && abs(rx) < TRANS_VIEW_LIMIT && abs(rz) < TRANS_VIEW_LIMIT) 
			{
				SENDPACKET(u, lpTransCommand);
			}
		}
	}

	return TRUE;
}
static int rsCompString(char *src1, char *src2)
{
	int cnt;
	int len1, len2;
	int len;

	len1 = lstrlen(src1);
	len2 = lstrlen(src2);

	if (len1 < len2) len = len1;
	else len = len2;

	if (!len) return NULL;

	for (cnt = 0; cnt < len1; cnt++) {
		if (src1[cnt] == 0) break;
		if (src1[cnt] != src2[cnt]) return NULL;
	}

	return cnt;
}

char *rsGetWord(char *q, char *p)
{

	//	while ( *p != '\n' ) {
	if (*p == 0) { *q = 0; return p; }

	while ((*p == 32) || (*p == 9) || (*p == 58)) // SPACE or TAB or ':'´Â Á¦¿Ü ½ÃÅ´
	{
		p++;
	}

	while ((*p != 32) && (*p != 9) && (*p != 58) && (*p != 0)) // SPACE or TAB
	{
		if (*p == '\n' || *p == '\r') break;
		*q++ = *p++;
	}
	*q++ = 0;	// end of one string, put Null character
//	}
//	*q = '\n';

	return p;
}


User *FindUserFromName(char *szName)
{
	int cnt;

	for (cnt = 0; cnt < PLAYERS_MAX; cnt++)
	{
		User * u = USERSDATA + cnt;

		if (u->pcSocketData && u->TransInfoFlag)
		{
			if (lstrcmpi(u->sCharacterData.szName, szName) == 0)
				return u;
		}
	}

	return NULL;
}

User *FindUserFromName2(char *szName)
{
	int cnt;

	for (cnt = 0; cnt < PLAYERS_MAX; cnt++)
	{
		User * u = USERSDATA + cnt;

		if (u->pcSocketData)
		{
			if (lstrcmpi(u->szCharacterName, szName) == 0)
			{
				return u;
			}
		}
	}

	return NULL;
}

User *FindUserFromName3(char *szName)
{
	int cnt;

	for (cnt = 0; cnt < PLAYERS_MAX; cnt++)
	{
		User * u = USERSDATA + cnt;

		if (u->pcSocketData)
		{
			if (u->szCharacterName[0])
			{
				if (lstrcmpi(u->szCharacterName, szName) == 0)
					return u;
			}
			else
			{
				if (lstrcmpi(u->sCharacterData.szName, szName) == 0)
					return u;
			}
		}
	}

	return NULL;
}

User *FindUserFromCodeName(char *szName, DWORD dwSpeedSum)
{
	int cnt;

	for (cnt = 0; cnt < PLAYERS_MAX; cnt++)
	{
		User * u = USERSDATA + cnt;

		if (u->pcSocketData)
		{
			if (u->dwHashCharacterName == dwSpeedSum && lstrcmpi(u->szCharacterName, szName) == 0)
			{
				return u;
			}
		}
	}

	return NULL;
}


User *FindUserFromID(char *szID)
{
	int cnt;

	for (cnt = 0; cnt < PLAYERS_MAX; cnt++)
	{
		User * u = USERSDATA + cnt;

		if (u->pcSocketData && u->szAccountName[0])
		{
			if (lstrcmpi(u->szAccountName, szID) == 0)
			{
				return u;
			}
		}
	}

	return NULL;
}

int CreatePresentItem(DWORD dwItemCode, Map *lpStgArea, int x, int y, int z, int count)
{
	LootItem			psItem;
	MapLoot		*lpStgItem;

	ZeroMemory(&psItem, sizeof(LootItem));

	auto pDefItem = SERVERITEM->FindItemDefByCode(dwItemCode);

	if (pDefItem)
	{
		SERVERITEM->CreateItem(&psItem.sItem, pDefItem);

		if (psItem.sItem.sItemID.ToItemType() == ITEMBASE_Potion)
		{
			psItem.sItem.iPotionCount = (rand() % count) + 1;
		}

		psItem.bUse = TRUE;

		lpStgItem = SERVERMAP->AddItem(lpStgArea, &psItem, Point3D(x, y, z) >> 8, TRUE);
		lpStgItem->dwDropTime += 5000;

		return TRUE;
	}

	return FALSE;
}

DefinitionItem *rsPutItem3(User *lpPlayInfo, DWORD dwItemCode)
{
	LootItem	psItem;

	auto pDefItem = SERVERITEM->FindItemDefByCode(dwItemCode);

	if (pDefItem)
	{
		SERVERITEM->CreateItem(&psItem.sItem, pDefItem);
		SERVERITEM->SendItemData(lpPlayInfo, &psItem.sItem);

		return pDefItem;
	}
	return NULL;
}

char szAdminChar[32];
char szAdminMessage[4][32];

char *szAdminLogin = "ralley-x";
char *szAdminMaster = "µ¿´ëÀå´Ô";
char *szAdminMsg[4] = {
	"*°øÀÍ±Ù¹«´ë±âÁß!!",
	"^^¹ß·»Å¸ÀÎ21³â»ê^^",
	"(ÇÑ°Ü·¹¼Ò¾¾¸§¹ÎÁ·´ëÃàÀü)~À½¸Å",
	0
};

char *szAdminSpecial = "Legendotaku";
char *szAdminSpecialSucess = "Çê~~ ÁøÂ¥¾ß ?";

char *szAdminSucess[4] = {
	"Command Level (1)  d(+ _ +)b",
	"Command Level (2)  d(^ _ ^)b",
	"Command Level (3)  d(* . *)b",
	0
};

int InitAdminCommand()
{
	int cnt;

	lstrcpy(szAdminChar, szAdminMaster);
	for (cnt = 0; cnt < 3; cnt++)
		lstrcpy(szAdminMessage[cnt], szAdminMsg[cnt]);

	for (cnt = 0; cnt < 3; cnt++)
	{
		if (rsServerConfig.szAdminPassword[cnt][0])
			lstrcpy(szAdminMessage[cnt], rsServerConfig.szAdminPassword[cnt]);
	}

	if (rsServerConfig.szAdminName[0])
		lstrcpy(szAdminChar, rsServerConfig.szAdminName);

	return TRUE;
}


int SendQuickMessage(User *lpPlayInfo, char *szMessage)
{

	TRANS_CHATMESSAGE	TransChatMessage;

	wsprintf(TransChatMessage.szMessage, "From> %s: %s", szAdminChar, szMessage);
	TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
	TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
	TransChatMessage.dwIP = 0;
	TransChatMessage.dwObjectSerial = 0;

	SENDPACKET(lpPlayInfo, &TransChatMessage);

	return TRUE;

}

int SendQuickMessage2(User *lpPlayInfo, char *szMessage, int iType)
{
	TRANS_CHATMESSAGE	TransChatMessage;

	wsprintf(TransChatMessage.szMessage, "%s", szMessage);
	TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
	TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
	TransChatMessage.dwIP = iType;
	TransChatMessage.dwObjectSerial = 0;

	SENDPACKET(lpPlayInfo, &TransChatMessage);

	return TRUE;
}
int SendQuickNoticeMessage(char *szMessage)
{
	TRANS_CHATMESSAGE	TransChatMessage;

	wsprintf(TransChatMessage.szMessage, "%s", szMessage);
	TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
	TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
	TransChatMessage.dwIP = 9;
	TransChatMessage.dwObjectSerial = 0;

	for (int cnt = 0; cnt < PLAYERS_MAX; cnt++)
	{
		User * u = USERSDATA + cnt;

		if (u && u->iID)
			SENDPACKET(u, &TransChatMessage);
	}
	return TRUE;
}
int SendQuickMessageBox(User *lpPlayInfo, char *szMessage)
{
	TRANS_CHATMESSAGE	TransChatMessage;

	wsprintf(TransChatMessage.szMessage, "%s", szMessage);
	TransChatMessage.code = smTRANSCODE_MESSAGEBOX;
	TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
	TransChatMessage.dwIP = 0;
	TransChatMessage.dwObjectSerial = 0;

	SENDPACKET(lpPlayInfo, &TransChatMessage);

	return TRUE;
}
int SendClanNoticeMessage(User *lpPlayInfo, char *szMessage)
{
	TRANS_CHATMESSAGE	TransChatMessage;

	wsprintf(TransChatMessage.szMessage, "%s", szMessage);
	TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
	TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
	TransChatMessage.dwIP = 9;
	TransChatMessage.dwObjectSerial = 0;

	for (int i = 0; i < PLAYERS_MAX; i++)
	{
		User * u = USERSDATA + i;

		if (u != lpPlayInfo)
		{
			if (u && u->iClanID == lpPlayInfo->iClanID)
				SENDPACKET(u, &TransChatMessage);
		}
	}
	return TRUE;
}


void OnRecvMessage(User * pcUser, PacketReceiving * p)
{

#ifdef _W_SERVER

	//DWORD *IPData;
	//User *lpPlayInfo;
	User *lpPlayInfo2;
	smTRANS_COMMAND	*lpTransCommand;
	smTRANS_COMMAND_EX	*lpTransCommandEx;
	smTRANS_COMMAND		smTransCommand;
	smTRANS_COMMAND_EX	smTransCommandEx;
	smTRNAS_PLAYERINFO	*lpTransPlayerInfo;
	Map		*lpStgArea;
	rsRECORD_DBASE *lpRecordBase;
	smTRANS_CHAR_COMMAND	*lpTransCharCommand;
	smTRANS_CHAR_COMMAND2	*lpTransCharCommand2;
	TRANS_CHATMESSAGE	TransChatMessage;
	TRANS_CHATMESSAGE	*lpTransChatMessage;
	TRANS_TRADEITEMS	*lpTransTradeItems;

	TRANS_ITEMINFO		*lpTransItemInfo;
	LootItem		*lpsItem;

	MapLoot		*lpStgItem;
	DWORD	dwTime;

	int cnt, len, rnd;
	int cnt2 = 0;
	Unit	*lpChar;
	int x, z;

	dwTime = GetCurrentTime();

	Packet * psPacket = (Packet*)p->baPacket;

	if (!pcUser || !pcUser->pcSocketData)
	{
		if (pcUser)
			pcUser->dwTimeLastPacket = dwTime;

		return;
	}

	switch (psPacket->iHeader) 
	{
	case smTRANSCODE_SYSTEM:
		break;
	case smTRANSCODE_PROCESSINFO:
		lpTransChatMessage = (TRANS_CHATMESSAGE *)psPacket;

		if (rsServerConfig.ClientCheckSumCount > 0 && pcUser->iGameLevel == GAMELEVEL_None)
		{
			for (cnt = 0; cnt < rsServerConfig.ClientCheckSumCount; cnt++)
			{
				if (lpTransChatMessage->dwObjectSerial == rsServerConfig.dwClientCheckSum[cnt])
				{
					break;
				}
			}
			if (cnt >= rsServerConfig.ClientCheckSumCount)
			{
				smTransCommand.WParam = 1103;
				smTransCommand.SParam = lpTransChatMessage->dwObjectSerial;
				smTransCommand.LParam = (int)lpTransChatMessage->szMessage;
				RecordHackLogFile(pcUser, &smTransCommand);
			}
		}
		break;
	case smTRANSCODE_CONTINUEDATA:
		break;
	case smTRANSCODE_GETPLAYERINFO:
		if (pcUser->iGameLevel != GAMELEVEL_None)
			rsSendPlayerInfo(pcUser, (smTRANS_COMMAND *)psPacket);
		else
			rsSendPlayerInfoQuick(pcUser, (smTRANS_COMMAND *)psPacket);
		break;
	case smTRANSCODE_ATTACKDATA:
		rsRecvAttackData_Old(pcUser, (TRANS_ATTACKDATA *)psPacket, 0, 0);
		break;
	case smTRANSCODE_SKIL_ATTACKDATA:
		rsRecvRangeAttackData_Old(pcUser, (TRANS_SKIL_ATTACKDATA *)psPacket, 0);
		break;
	case smTRANSCODE_ATTACK_DAMAGE:
		rsRecvAttackData(pcUser, (TRANS_ATTACKDATA2 *)psPacket);
		break;
	case smTRANSCODE_RANGE_DAMAGE:
		rsRecvRangeAttackData(pcUser, (TRANS_SKIL_ATTACKDATA2 *)psPacket);
		break;
	case smTRANSCODE_SKIL_ATTACKUSER:
		rsRecvRangeAttackUserData_Old(pcUser, (TRANS_SKIL_ATTACKDATA *)psPacket);
		break;
	case smTRANSCODE_ADD_STARTPOSI:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;

		x = lpTransCommand->LParam;
		z = lpTransCommand->WParam;

		if (pcUser->iGameLevel >= GAMELEVEL_Three)
		{
			lpStgArea = SERVERMAP->GetMapByXZ(x, z);
				
			if (lpStgArea) 
			{
				SERVERMAP->AddFlagPoint(pcUser, "TRUE");
			}
		}
		break;
	case smTRANSCODE_PLAYERINFO2:
		lpTransPlayerInfo = (smTRNAS_PLAYERINFO *)psPacket;

		memcpy(&pcUser->sCharacterData, &lpTransPlayerInfo->sCharacterData, sizeof(CharacterData));

		pcUser->dwHashCharacterName = GetCodebyName(pcUser->sCharacterData.szName);

		if (!pcUser->iID)
			pcUser->iID = lpTransPlayerInfo->dwObjectSerial;
		pcUser->TransInfoFlag = TRUE;
		pcUser->dwLastExpMoneyCheckTime = SERVER_GAMETIME;

		pcUser->iClanID = GetClanCodeByID(pcUser->sCharacterData.iClanID);
		pcUser->UpdateInfo_WarnigCounter++;

		break;
	case smTRANSCODE_ISRECORDDATA:
		//Ä³¸¯ÅÍ°¡ Á¸Àç ÇÏ´ÂÁö È®ÀÎ ( WParam¿¡ °á°ú°ª ÀúÀåÇÏ¿© µÇµ¹·Á º¸³¿ )
		lpRecordBase = new rsRECORD_DBASE;

		lpTransCharCommand2 = (smTRANS_CHAR_COMMAND2 *)psPacket;
		lpTransCharCommand2->WParam = lpRecordBase->IsData(lpTransCharCommand2->szName);

		SENDPACKET(pcUser, lpTransCharCommand2);

		DELET(lpRecordBase);
		break;
	case smTRANSCODE_THROWITEM:
		lpTransItemInfo = (TRANS_ITEMINFO *)psPacket;

		cnt = 0;

		if (SERVERITEM->ValiSecCode(pcUser,
			lpTransItemInfo->sItem.sItemID.ToInt(),
			lpTransItemInfo->sItem.iChk1,
			lpTransItemInfo->sItem.iChk2,
			lpTransItemInfo->sItem.iGold,
			lpTransItemInfo->dwSeCode, cnt) == FALSE)
		{
			break;
		}

		if (cnt && cnt != lpTransItemInfo->sItem.iPotionCount)
		{
			if (cnt < lpTransItemInfo->sItem.iPotionCount)
			{
				if (cnt < 0)
					cnt = 1;
				lpTransItemInfo->sItem.iPotionCount = cnt;
			}
		}

		if (lpTransItemInfo->sItem.sItemID.ToInt() == (sinGF1 | sin01))
		{
			break;
		}

		if ((lpTransItemInfo->sItem.sItemID.ToItemType()) == sinGP1 && lpTransItemInfo->sItem.iPotionCount == 100)
		{
			if (CheckItemForm(&lpTransItemInfo->sItem) == TRUE)
			{
				cnt = SERVERMAP->SpawnCrystal(lpTransItemInfo->sItem.sItemID.ToItemID(), pcUser->sPosition.iX, pcUser->sPosition.iY, pcUser->sPosition.iZ, pcUser);

				if (cnt == TRUE)
					break;
				if (cnt == -1)
				{
					lpTransItemInfo->sItem.iPotionCount = 0;
					SERVERITEM->SendItemData(pcUser, &lpTransItemInfo->sItem);
					break;
				}
				lpTransItemInfo->sItem.iPotionCount = 0;
			}
		}
		if ((lpTransItemInfo->sItem.sItemID.ToItemType()) == sinSP1 && lpTransItemInfo->sItem.iPotionCount == 100)
		{
			if (CheckItemForm(&lpTransItemInfo->sItem) == TRUE)
			{
				cnt = rsUseSoccerBallPotionItem(lpTransItemInfo->sItem.sItemID.ToInt(), pcUser);
				if (cnt == TRUE)
					break;
				if (cnt == -1)
				{
					lpTransItemInfo->sItem.iPotionCount = 0;
					SERVERITEM->SendItemData(pcUser, &lpTransItemInfo->sItem);
					break;
				}
				lpTransItemInfo->sItem.iPotionCount = 0;
			}
		}
		if ((lpTransItemInfo->sItem.sItemID.ToItemType()) == sinCH1 && lpTransItemInfo->sItem.iPotionCount == 100)
		{
			if (CheckItemForm(&lpTransItemInfo->sItem) == TRUE)
			{
				if (rsUseLovelyItem(pcUser, lpTransItemInfo->sItem.sItemID.ToInt()) == TRUE)
					break;
				lpTransItemInfo->sItem.iPotionCount = 0;
			}
		}

		if (((lpTransItemInfo->sItem.sItemID.ToItemType()) == sinBI1 || (lpTransItemInfo->sItem.sItemID.ToItemType()) == sinBI2) && lpTransItemInfo->sItem.iPotionCount == 300)
		{
			if (CheckItemForm(&lpTransItemInfo->sItem) == TRUE)
			{
				cnt = rsOpenSiegeCastleItem(lpTransItemInfo->sItem.sItemID.ToInt(), pcUser->sPosition.iX, pcUser->sPosition.iY, pcUser->sPosition.iZ, pcUser);

				if (cnt == TRUE)
					break;
				if (cnt == -1)
				{
					lpTransItemInfo->sItem.iPotionCount = 0;
					SERVERITEM->SendItemData(pcUser, &lpTransItemInfo->sItem);
					break;
				}
				lpTransItemInfo->sItem.iPotionCount = 0;
				break;
			}
		}

		if (lpTransItemInfo->sItem.sItemID.ToInt() == (sinGG1 | sin01) && lpTransItemInfo->sItem.eCraftType == ITEMCRAFTTYPE_Event)
		{
			if (CheckItemForm(&lpTransItemInfo->sItem) == TRUE)
			{
				pcUser->spMoney_In += lpTransItemInfo->sItem.iGold;
				rsEnterHardCoreEvent(pcUser, lpTransItemInfo->sItem.iGold);
			}
			break;
		}

		if ((lpTransItemInfo->sItem.sItemID.ToItemType()) == sinFO1 && lpTransItemInfo->sItem.iPotionCount == 100)
		{
			/*cnt = (lpTransItemInfo->Item.CODE&sinITEM_MASK3)>>8;

			cnt --;
			if (cnt>=0 && cnt<16)
			{
				pcUser->dwForceOrb_Code		= lpTransItemInfo->Item.CODE;
				pcUser->dwForceOrb_Time		= SERVER_GAMETIME+ForceOrbUseTime[cnt]*1000;
				pcUser->dwForceOrb_Damage	= ForceOrbDamage[cnt];
			}*/
			if (CheckItemForm(&lpTransItemInfo->sItem) == TRUE)
			{

			}

			break;
		}

		if ((lpTransItemInfo->sItem.sItemID.ToItemType()) == sinBC1 && lpTransItemInfo->sItem.iPotionCount == 200)
		{
			if (CheckItemForm(&lpTransItemInfo->sItem) == TRUE)
			{
				cnt = rsOpenSiegeCastleItem(lpTransItemInfo->sItem.sItemID.ToInt(), pcUser->sPosition.iX, pcUser->sPosition.iY, pcUser->sPosition.iZ, pcUser);
				if (cnt == TRUE)
					break;
				if (cnt == -1)
				{
					lpTransItemInfo->sItem.iPotionCount = 0;
					SERVERITEM->SendItemData(pcUser, &lpTransItemInfo->sItem);
					break;
				}
				lpTransItemInfo->sItem.iPotionCount = 0;
			}
		}

		if (rsServerConfig.DisableThrowItem)
			break;

		lpStgArea = SERVERMAP->GetMapByXZ(lpTransItemInfo->x, lpTransItemInfo->z);
		if (lpStgArea)
		{
			lpsItem = new LootItem;
			lpsItem->bUse = TRUE;

			memcpy(&lpsItem->sItem, &lpTransItemInfo->sItem, sizeof(Item));

			if (CheckItemForm(&lpsItem->sItem) == FALSE)
			{
				smTransCommand.code = smTRANSCODE_SET_BLACKLIST;
				smTransCommand.size = sizeof(smTRANS_COMMAND);
				smTransCommand.WParam = 6800;
				smTransCommand.LParam = lpTransItemInfo->sItem.sItemID.ToInt();
				smTransCommand.SParam = lpTransItemInfo->sItem.iChk1;
				smTransCommand.EParam = lpTransItemInfo->sItem.iChk2;

				rsSendDataServer(pcUser, &smTransCommand);
			}

			lpStgItem = SERVERMAP->AddItem(lpStgArea, lpsItem, Point3D(lpTransItemInfo->x, lpTransItemInfo->y, lpTransItemInfo->z) >> 8);

			if (lpTransItemInfo->sItem.sItemID.ToInt() == (sinGG1 | sin01))
				pcUser->spMoney_In += lpTransItemInfo->sItem.iGold;
			else
				rsCheckItemTempCode(pcUser, &lpsItem->sItem);

			delete lpsItem;

			if (lpStgItem)
				SERVERMAP->SendItemStageNearUsers(lpStgArea, lpStgItem);
		}
		break;


	case smTRANSCODE_SAVETHROWITEM:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;

		if (pcUser)
			SaveThrowItem(pcUser, lpTransCommand->WParam, lpTransCommand->LParam, lpTransCommand->SParam);
		break;

	case smTRANSCODE_SAVETHROWITEM2:
		lpTransCommandEx = (smTRANS_COMMAND_EX *)psPacket;

		if (pcUser->dwFuncChkErrorFlag)
			break;

#ifndef _SERVER_MODE_OLD
		len = 0;

		if (pcUser)
		{
			if (SERVERITEM->DeleteItemInventory(pcUser,
				lpTransCommandEx->WParam,
				lpTransCommandEx->LParam,
				lpTransCommandEx->SParam) == FALSE)
			{
				smTransCommandEx.WParam = 8000;
				smTransCommandEx.WxParam = 20;
				smTransCommandEx.LxParam = (int)"*THROW ITEM*";
				smTransCommandEx.LParam = lpTransCommandEx->WParam;
				smTransCommandEx.SParam = lpTransCommandEx->LParam;
				smTransCommandEx.EParam = lpTransCommandEx->SParam;
				RecordHackLogFile(pcUser, &smTransCommandEx);
				break;
			}

			if ((lpTransCommandEx->WParam&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
			{
				cnt = lpTransCommandEx->EParam^lpTransCommandEx->SParam^lpTransCommandEx->code;
				if (cnt <= 0)
				{
					rsServerPotionErrorLog(pcUser, lpTransCommandEx->WParam, -cnt, 201);
					break;
				}
				if (SERVERITEM->AddPotion(pcUser, lpTransCommandEx->WParam, -cnt) < 0)
				{
					rsServerPotionErrorLog(pcUser, lpTransCommandEx->WParam, -cnt, 200);
					break;
				}
			}
			if ((lpTransCommandEx->WParam&sinITEM_MASK1) == (sinFO1&sinITEM_MASK1))
			{
				cnt = lpTransCommandEx->EParam^lpTransCommandEx->SParam^lpTransCommandEx->code;
				if (cnt == 100)
				{
					cnt = (lpTransCommandEx->WParam&sinITEM_MASK3) >> 8;

					cnt--;

					if (cnt >= 0 && cnt < 16)
					{
						pcUser->dwForceOrb_SaveCode = lpTransCommandEx->WParam;
						pcUser->dwForceOrb_SaveTime = SERVER_GAMETIME + ForceOrbUseTime[cnt] * 1000;
						pcUser->dwForceOrb_SaveDamage = ForceOrbDamage[cnt];

						rsSendServerToForceOrb(pcUser);
					}
					len = 100;
				}
			}

			if ((lpTransCommandEx->WParam&sinITEM_MASK1) == (sinBC1&sinITEM_MASK1))
			{
				cnt = lpTransCommandEx->EParam^lpTransCommandEx->SParam^lpTransCommandEx->code;
				if (cnt == 200)
				{
					switch (lpTransCommandEx->WParam)
					{
					case (sinBC1 | sin21):
						pcUser->dwLifeBooster_SaveCode = lpTransCommandEx->WParam;
						pcUser->dwLifeBooster_SaveTime = SERVER_GAMETIME + BoosterItem_UseTime[0] * 1000;
						pcUser->dwLifeBooster_SaveData = BoosterItem_DataPercent[0];
						break;
					case (sinBC1 | sin22):
						pcUser->dwLifeBooster_SaveCode = lpTransCommandEx->WParam;
						pcUser->dwLifeBooster_SaveTime = SERVER_GAMETIME + BoosterItem_UseTime[1] * 1000;
						pcUser->dwLifeBooster_SaveData = BoosterItem_DataPercent[0];
						break;
					case (sinBC1 | sin23):
						pcUser->dwLifeBooster_SaveCode = lpTransCommandEx->WParam;
						pcUser->dwLifeBooster_SaveTime = SERVER_GAMETIME + BoosterItem_UseTime[2] * 1000;
						pcUser->dwLifeBooster_SaveData = BoosterItem_DataPercent[0];
						break;
					case (sinBC1 | sin24):
						pcUser->dwManaBooster_SaveCode = lpTransCommandEx->WParam;
						pcUser->dwManaBooster_SaveTime = SERVER_GAMETIME + BoosterItem_UseTime[0] * 1000;
						pcUser->dwManaBooster_SaveData = BoosterItem_DataPercent[1];
						break;
					case (sinBC1 | sin25):
						pcUser->dwManaBooster_SaveCode = lpTransCommandEx->WParam;
						pcUser->dwManaBooster_SaveTime = SERVER_GAMETIME + BoosterItem_UseTime[1] * 1000;
						pcUser->dwManaBooster_SaveData = BoosterItem_DataPercent[1];
						break;
					case (sinBC1 | sin26):
						pcUser->dwManaBooster_SaveCode = lpTransCommandEx->WParam;
						pcUser->dwManaBooster_SaveTime = SERVER_GAMETIME + BoosterItem_UseTime[2] * 1000;
						pcUser->dwManaBooster_SaveData = BoosterItem_DataPercent[1];
						break;
					case (sinBC1 | sin27):
						pcUser->dwStaminaBooster_SaveCode = lpTransCommandEx->WParam;
						pcUser->dwStaminaBooster_SaveTime = SERVER_GAMETIME + BoosterItem_UseTime[0] * 1000;
						pcUser->dwStaminaBooster_SaveData = BoosterItem_DataPercent[2];
						break;
					case (sinBC1 | sin28):
						pcUser->dwStaminaBooster_SaveCode = lpTransCommandEx->WParam;
						pcUser->dwStaminaBooster_SaveTime = SERVER_GAMETIME + BoosterItem_UseTime[1] * 1000;
						pcUser->dwStaminaBooster_SaveData = BoosterItem_DataPercent[2];
						break;
					case (sinBC1 | sin29):
						pcUser->dwStaminaBooster_SaveCode = lpTransCommandEx->WParam;
						pcUser->dwStaminaBooster_SaveTime = SERVER_GAMETIME + BoosterItem_UseTime[2] * 1000;
						pcUser->dwStaminaBooster_SaveData = BoosterItem_DataPercent[2];
						break;
					case (sinBC1 | sin30):
						pcUser->dwSkillDelay_SaveCode = lpTransCommandEx->WParam;
						pcUser->dwSkillDelay_SaveTime = SERVER_GAMETIME + nSkillDelay_UseTime[0] * 1000;
						pcUser->dwSkillDelay_SaveData = BoosterItem_DataPercent[0];
						break;
					}
					len = 100;
				}
			}

			if ((lpTransCommandEx->WParam&sinITEM_MASK1) == (sinBI1&sinITEM_MASK1) || (lpTransCommandEx->WParam&sinITEM_MASK1) == (sinBI2&sinITEM_MASK1))
			{
				cnt = lpTransCommandEx->EParam^lpTransCommandEx->SParam^lpTransCommandEx->code;
				if (cnt == 300)
				{
					switch (lpTransCommandEx->WParam)
					{
					case sinBI2 | sin01:
						pcUser->dwTime_PrimeItem_X2 = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE1;
						pcUser->dwTime_PrimeItem_ExpUp = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE1;
						pcUser->dwPrimeItem_PackageCode = PRIME_ITEM_PACKAGE_BRONZE;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI2 | sin02:
						pcUser->dwTime_PrimeItem_X2 = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE2;
						pcUser->dwTime_PrimeItem_ExpUp = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE2;
						pcUser->dwPrimeItem_PackageCode = PRIME_ITEM_PACKAGE_BRONZE;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI2 | sin03:
						pcUser->dwTime_PrimeItem_X2 = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE3;
						pcUser->dwTime_PrimeItem_ExpUp = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE3;
						pcUser->dwPrimeItem_PackageCode = PRIME_ITEM_PACKAGE_BRONZE;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI2 | sin04:
						pcUser->dwTime_PrimeItem_X2 = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE4;
						pcUser->dwTime_PrimeItem_ExpUp = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE4;
						pcUser->dwPrimeItem_PackageCode = PRIME_ITEM_PACKAGE_BRONZE;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI2 | sin05:
						pcUser->dwTime_PrimeItem_X2 = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE1;
						pcUser->dwTime_PrimeItem_ExpUp = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE1;
						pcUser->dwPrimeItem_PackageCode = PRIME_ITEM_PACKAGE_SILVER;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI2 | sin06:
						pcUser->dwTime_PrimeItem_X2 = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE2;
						pcUser->dwTime_PrimeItem_ExpUp = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE2;
						pcUser->dwPrimeItem_PackageCode = PRIME_ITEM_PACKAGE_SILVER;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI2 | sin07:
						pcUser->dwTime_PrimeItem_X2 = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE3;
						pcUser->dwTime_PrimeItem_ExpUp = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE3;
						pcUser->dwPrimeItem_PackageCode = PRIME_ITEM_PACKAGE_SILVER;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI2 | sin08:
						pcUser->dwTime_PrimeItem_X2 = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE4;
						pcUser->dwTime_PrimeItem_ExpUp = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE4;
						pcUser->dwPrimeItem_PackageCode = PRIME_ITEM_PACKAGE_SILVER;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI2 | sin09:
						pcUser->dwTime_PrimeItem_X2 = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE1;
						pcUser->dwTime_PrimeItem_ExpUp = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE1;
						pcUser->dwPrimeItem_PackageCode = PRIME_ITEM_PACKAGE_GOLD;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI2 | sin10:
						pcUser->dwTime_PrimeItem_X2 = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE2;
						pcUser->dwTime_PrimeItem_ExpUp = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE2;
						pcUser->dwPrimeItem_PackageCode = PRIME_ITEM_PACKAGE_GOLD;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI2 | sin11:
						pcUser->dwTime_PrimeItem_X2 = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE3;
						pcUser->dwTime_PrimeItem_ExpUp = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE3;
						pcUser->dwPrimeItem_PackageCode = PRIME_ITEM_PACKAGE_GOLD;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI2 | sin12:
						pcUser->dwTime_PrimeItem_X2 = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE4;
						pcUser->dwTime_PrimeItem_ExpUp = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE4;
						pcUser->dwPrimeItem_PackageCode = PRIME_ITEM_PACKAGE_GOLD;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI2 | sin23:
						pcUser->dwTime_PrimeItem_X2 = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE1;
						pcUser->dwTime_PrimeItem_ExpUp = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE1;
						pcUser->dwPrimeItem_PackageCode = PRIME_ITEM_PACKAGE_ULTRA;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI2 | sin24:
						pcUser->dwTime_PrimeItem_X2 = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE2;
						pcUser->dwTime_PrimeItem_ExpUp = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE2;
						pcUser->dwPrimeItem_PackageCode = PRIME_ITEM_PACKAGE_ULTRA;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI2 | sin25:
						pcUser->dwTime_PrimeItem_X2 = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE3;
						pcUser->dwTime_PrimeItem_ExpUp = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE3;
						pcUser->dwPrimeItem_PackageCode = PRIME_ITEM_PACKAGE_ULTRA;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI2 | sin26:
						pcUser->dwTime_PrimeItem_ManaReduce = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE1;
						pcUser->dwTime_PrimeItem_ExpUp = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE1;
						pcUser->dwPrimeItem_PackageCode = PRIME_ITEM_PACKAGE_BRONZE2;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI2 | sin27:
						pcUser->dwTime_PrimeItem_ManaReduce = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE2;
						pcUser->dwTime_PrimeItem_ExpUp = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE2;
						pcUser->dwPrimeItem_PackageCode = PRIME_ITEM_PACKAGE_BRONZE2;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI2 | sin28:
						pcUser->dwTime_PrimeItem_ManaReduce = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE3;
						pcUser->dwTime_PrimeItem_ExpUp = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE3;
						pcUser->dwPrimeItem_PackageCode = PRIME_ITEM_PACKAGE_BRONZE2;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI2 | sin29:
						pcUser->dwTime_PrimeItem_ManaReduce = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE1;
						pcUser->dwTime_PrimeItem_ExpUp = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE1;
						pcUser->dwPrimeItem_PackageCode = PRIME_ITEM_PACKAGE_SILVER2;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI2 | sin30:
						pcUser->dwTime_PrimeItem_ManaReduce = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE2;
						pcUser->dwTime_PrimeItem_ExpUp = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE2;
						pcUser->dwPrimeItem_PackageCode = PRIME_ITEM_PACKAGE_SILVER2;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI2 | sin31:
						pcUser->dwTime_PrimeItem_ManaReduce = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE3;
						pcUser->dwTime_PrimeItem_ExpUp = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE3;
						pcUser->dwPrimeItem_PackageCode = PRIME_ITEM_PACKAGE_SILVER2;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI2 | sin32:
						pcUser->dwTime_PrimeItem_ManaReduce = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE1;
						pcUser->dwTime_PrimeItem_ExpUp = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE1;
						pcUser->dwPrimeItem_PackageCode = PRIME_ITEM_PACKAGE_GOLD2;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI2 | sin33:
						pcUser->dwTime_PrimeItem_ManaReduce = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE2;
						pcUser->dwTime_PrimeItem_ExpUp = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE2;
						pcUser->dwPrimeItem_PackageCode = PRIME_ITEM_PACKAGE_GOLD2;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI2 | sin34:
						pcUser->dwTime_PrimeItem_ManaReduce = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE3;
						pcUser->dwTime_PrimeItem_ExpUp = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE3;
						pcUser->dwPrimeItem_PackageCode = PRIME_ITEM_PACKAGE_GOLD2;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI2 | sin35:
						pcUser->dwTime_PrimeItem_ManaReduce = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE1;
						pcUser->dwTime_PrimeItem_ExpUp = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE1;
						pcUser->dwPrimeItem_PackageCode = PRIME_ITEM_PACKAGE_ULTRA2;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI2 | sin36:
						pcUser->dwTime_PrimeItem_ManaReduce = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE2;
						pcUser->dwTime_PrimeItem_ExpUp = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE2;
						pcUser->dwPrimeItem_PackageCode = PRIME_ITEM_PACKAGE_ULTRA2;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI2 | sin37:
						pcUser->dwTime_PrimeItem_ManaReduce = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE3;
						pcUser->dwTime_PrimeItem_ExpUp = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE3;
						pcUser->dwPrimeItem_PackageCode = PRIME_ITEM_PACKAGE_ULTRA2;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI2 | sin50:
						if (pcUser->sCharacterData.iLevel >= 10)
						{
							pcUser->dwTime_PhenixPet = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_EXPUPx7;
							pcUser->PhenixPetType = rand() % 4 + 1;
							pcUser->dwPhenixPet_SetNextTime = 0;
							rsSendGameServer_Phoenix(pcUser);
						}
						break;
					}
					switch (lpTransCommandEx->WParam)
					{
					case sinBI1 | sin09:
						pcUser->dwTime_BigHead = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE1;
						pcUser->dwBigHead_SetNextTime = 0;
						pcUser->BigHeadType = (rand() % 2) + 1;
						rsSendGameServer_BigHead(pcUser);
						break;
					case sinBI1 | sin12:
						pcUser->dwTime_PrimeItem_X2 = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_THIRDEYES;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI1 | sin13:
						pcUser->dwTime_PrimeItem_ExpUp = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_EXPUP;
						pcUser->dwPrimeItem_NextSetTime = 0;
						pcUser->dwPrimeItem_PackageCode = 0;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI1 | sin14:
						pcUser->dwTime_PrimeItem_X2 = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_THIRDEYESx7;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI1 | sin15:
						pcUser->dwTime_PrimeItem_ExpUp = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_EXPUPx7;
						pcUser->dwPrimeItem_NextSetTime = 0;
						pcUser->dwPrimeItem_PackageCode = 0;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI1 | sin19:
						pcUser->dwTime_PrimeItem_VampCuspid = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_VAMPCUSPID;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI1 | sin20:
						pcUser->dwTime_PrimeItem_VampCuspid = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_VAMPCUSPIDx2;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI1 | sin21:
						pcUser->dwTime_PrimeItem_ManaRecharg = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_MANARECHARG;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI1 | sin22:
						pcUser->dwTime_PrimeItem_ManaRecharg = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_MANARECHARGx2;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI1 | sin24:
						pcUser->dwTime_PrimeItem_ExpUp = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_EXPUP;
						pcUser->dwPrimeItem_NextSetTime = 0;
						pcUser->dwPrimeItem_PackageCode = PRIME_ITEM_PACKAGE_NONE_50_EXPUP;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI1 | sin25:
						pcUser->dwTime_PrimeItem_ExpUp = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_EXPUPx7;
						pcUser->dwPrimeItem_NextSetTime = 0;
						pcUser->dwPrimeItem_PackageCode = PRIME_ITEM_PACKAGE_NONE_50_EXPUP;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI1 | sin26:
						pcUser->dwTime_PrimeItem_MightofAwell = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_EXPUPx7;
						pcUser->dwPrimeItem_NextSetTime = 0;
						pcUser->dwPrimeItem_PackageCode = 0;
						rsSendGameServer_PrimeItem2(pcUser);
						break;
					case sinBI1 | sin27:
						pcUser->dwTime_PrimeItem_MightofAwell = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_6HOUR;
						pcUser->dwPrimeItem_NextSetTime = 0;
						pcUser->dwPrimeItem_PackageCode = 0;
						rsSendGameServer_PrimeItem2(pcUser);
						break;
					case sinBI1 | sin28:
						pcUser->dwTime_PrimeItem_ManaReduce = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_EXPUP;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem2(pcUser);
						break;
					case sinBI1 | sin29:
						pcUser->dwTime_PrimeItem_ManaReduce = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_EXPUPx7;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem2(pcUser);
						break;
					case sinBI1 | sin30:
						pcUser->dwTime_PrimeItem_MightofAwell2 = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_EXPUPx7;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem2(pcUser);
						break;
					case sinBI1 | sin31:
						pcUser->dwTime_PrimeItem_MightofAwell2 = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE4;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem2(pcUser);
						break;
					case sinBI1 | sin43:
						pcUser->dwTime_PrimeItem_ExpUp = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_EXPUP;
						pcUser->dwPrimeItem_NextSetTime = 0;
						pcUser->dwPrimeItem_PackageCode = PRIME_ITEM_PACKAGE_NONE_100_EXPUP;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI1 | sin44:
						pcUser->dwTime_PrimeItem_ExpUp = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_EXPUPx7;
						pcUser->dwPrimeItem_NextSetTime = 0;
						pcUser->dwPrimeItem_PackageCode = PRIME_ITEM_PACKAGE_NONE_100_EXPUP;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI1 | sin50:
						pcUser->dwTime_PrimeItem_ExpUp = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE4;
						pcUser->dwPrimeItem_NextSetTime = 0;
						pcUser->dwPrimeItem_PackageCode = PRIME_ITEM_PACKAGE_NONE_100_EXPUP;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI1 | sin52:
						pcUser->dwTime_PrimeItem_HelpPet = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE4;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem3(pcUser);
						break;
					case sinBI1 | sin53:
						pcUser->dwTime_PrimeItem_HelpPet = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE4;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem3(pcUser);
						break;
					case sinBI1 | sin54:
						pcUser->dwTime_PrimeItem_HelpPet = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE4;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem3(pcUser);
						break;
					case sinBI1 | sin55:
						pcUser->dwTime_PrimeItem_HelpPet = ((DWORD)SERVER_LOCATIME) + (PRIME_ITEM_TIME_PACKAGE4);
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem3(pcUser);
						pcUser->sCharacterData.GravityScroolCheck[1] = 2;
						break;
					case sinBI1 | sin65:
						pcUser->dwTime_PrimeItem_HelpPet = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE3;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem3(pcUser);
						break;
					case sinBI1 | sin66:
						pcUser->dwTime_PrimeItem_HelpPet = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE3;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem3(pcUser);
						break;
					case sinBI1 | sin67:
						pcUser->dwTime_PrimeItem_HelpPet = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE3;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem3(pcUser);
						break;
					case sinBI1 | sin68:
						pcUser->dwTime_PrimeItem_HelpPet = ((DWORD)SERVER_LOCATIME) + (PRIME_ITEM_TIME_PACKAGE3);
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem3(pcUser);
						pcUser->sCharacterData.GravityScroolCheck[1] = 2;
						break;
					case sinBI1 | sin69:
						pcUser->dwTime_PrimeItem_HelpPet = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE2;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem3(pcUser);
						break;
					case sinBI1 | sin70:
						pcUser->dwTime_PrimeItem_HelpPet = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE2;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem3(pcUser);
						break;
					case sinBI1 | sin71:
						pcUser->dwTime_PrimeItem_HelpPet = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE2;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem3(pcUser);
						break;
					case sinBI1 | sin72:
						pcUser->dwTime_PrimeItem_HelpPet = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE2;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem3(pcUser);
						pcUser->sCharacterData.GravityScroolCheck[1] = 2;
						break;
					case sinBI1 | sin73:
						pcUser->dwTime_PrimeItem_HelpPet = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE5;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem3(pcUser);
						break;
					case sinBI1 | sin74:
						pcUser->dwTime_PrimeItem_HelpPet = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE5;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem3(pcUser);
						break;
					case sinBI1 | sin75:
						pcUser->dwTime_PrimeItem_HelpPet = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE5;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem3(pcUser);
						break;
					case sinBI1 | sin76:
						pcUser->dwTime_PrimeItem_HelpPet = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE5;
						pcUser->dwPrimeItem_NextSetTime = 0;
						pcUser->sCharacterData.GravityScroolCheck[1] = 2;
						rsSendGameServer_PrimeItem3(pcUser);
						break;
					case sinBI1 | sin78:
						pcUser->dwTime_PrimeItem_X2 = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE5;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI1 | sin80:
						pcUser->dwTime_PrimeItem_ExpUp = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE5;
						pcUser->dwPrimeItem_NextSetTime = 0;
						pcUser->dwPrimeItem_PackageCode = PRIME_ITEM_PACKAGE_NONE_100_EXPUP;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI1 | sin79:
						pcUser->dwTime_PrimeItem_ExpUp = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE5;
						pcUser->dwPrimeItem_NextSetTime = 0;
						pcUser->dwPrimeItem_PackageCode = PRIME_ITEM_PACKAGE_NONE_50_EXPUP;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI1 | sin81:
						pcUser->dwTime_PrimeItem_VampCuspid = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE5;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI1 | sin82:
						pcUser->dwTime_PrimeItem_ManaRecharg = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE5;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem(pcUser);
						break;
					case sinBI1 | sin83:
						pcUser->dwTime_PrimeItem_ManaReduce = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE5;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem2(pcUser);
						break;
					case sinBI1 | sin86:
						pcUser->dwTime_PrimeItem_VampCuspid_EX = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE5;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem3(pcUser);
						break;
					case sinBI1 | sin87:
						pcUser->dwTime_PrimeItem_VampCuspid_EX = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE1;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem3(pcUser);
						break;
					case sinBI1 | sin88:
						pcUser->dwTime_PrimeItem_VampCuspid_EX = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE2;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem3(pcUser);
						break;
					case sinBI1 | sin91:
						pcUser->dwTime_PrimeItem_StaminaReduce = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_EXPUP;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem3(pcUser);
						break;
					case sinBI1 | sin92:
						pcUser->dwTime_PrimeItem_StaminaReduce = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_EXPUPx7;
						pcUser->dwPrimeItem_NextSetTime = 0;
						rsSendGameServer_PrimeItem3(pcUser);
						break;
						//¶À½ÇÊÞÒ»¼Ò
					case sinBI1 | sin95:
						pcUser->dwCaravan_Hopy_Time = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_EXPUPx7;
						pcUser->dwCaravan_SetNextTime = 0;
						pcUser->dwCaravan_Param = 1;
						rsSendGameServer_CaravanHopy(pcUser);
						break;
						// ´óÍ·
					case sinBI1 | sin96:
						pcUser->dwTime_BigHead = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE1;
						pcUser->dwBigHead_SetNextTime = 0;
						pcUser->BigHeadType = 3;
						rsSendGameServer_BigHead(pcUser);
						break;
					case sinBI1 | sin97:
						pcUser->dwTime_BigHead = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE1;
						pcUser->dwBigHead_SetNextTime = 0;
						pcUser->BigHeadType = 4;
						rsSendGameServer_BigHead(pcUser);
						break;
					case sinBI1 | sin98:
						pcUser->dwTime_BigHead = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE1;
						pcUser->dwBigHead_SetNextTime = 0;
						pcUser->BigHeadType = 5;
						rsSendGameServer_BigHead(pcUser);
						break;
					case sinBI1 | sin99:
						pcUser->dwTime_BigHead = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE1;
						pcUser->dwBigHead_SetNextTime = 0;
						pcUser->BigHeadType = 6;
						rsSendGameServer_BigHead(pcUser);
						break;
					case sinBI2 | sin38:
						pcUser->dwTime_BigHead = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE1;
						pcUser->dwBigHead_SetNextTime = 0;
						pcUser->BigHeadType = 8;
						rsSendGameServer_BigHead(pcUser);
						break;
					case sinBI2 | sin39:
						if (GetSex(pcUser->sCharacterData.iClass) == BROOD_CODE_MAN)
						{
							pcUser->dwTime_BigHead = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE1;
							pcUser->dwBigHead_SetNextTime = 0;
							pcUser->BigHeadType = 9;
							rsSendGameServer_BigHead(pcUser);
						}
						break;
					case sinBI2 | sin40:
						if (GetSex(pcUser->sCharacterData.iClass) == BROOD_CODE_WOMAN)
						{
							pcUser->dwTime_BigHead = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE1;
							pcUser->dwBigHead_SetNextTime = 0;
							pcUser->BigHeadType = 9;
							rsSendGameServer_BigHead(pcUser);
						}
						break;
					case sinBI2 | sin41:
						if (GetSex(pcUser->sCharacterData.iClass) == BROOD_CODE_MAN)
						{
							pcUser->dwTime_BigHead = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE1;
							pcUser->dwBigHead_SetNextTime = 0;
							pcUser->BigHeadType = 10;
							rsSendGameServer_BigHead(pcUser);
						}
						break;
					case sinBI2 | sin42:
						if (GetSex(pcUser->sCharacterData.iClass) == BROOD_CODE_WOMAN)
						{
							pcUser->dwTime_BigHead = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE1;
							pcUser->dwBigHead_SetNextTime = 0;
							pcUser->BigHeadType = 10;
							rsSendGameServer_BigHead(pcUser);
						}
						break;
					case sinBI2 | sin43:
						pcUser->dwTime_BigHead = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE1;
						pcUser->dwBigHead_SetNextTime = 0;
						pcUser->BigHeadType = 11;
						rsSendGameServer_BigHead(pcUser);
						break;
					case sinBI2 | sin44:
						pcUser->dwTime_BigHead = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE1;
						pcUser->dwBigHead_SetNextTime = 0;
						pcUser->BigHeadType = 12;
						rsSendGameServer_BigHead(pcUser);
						break;
					case sinBI2 | sin45:
						pcUser->dwTime_BigHead = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE1;
						pcUser->dwBigHead_SetNextTime = 0;
						pcUser->BigHeadType = 13;
						rsSendGameServer_BigHead(pcUser);
						break;
					case sinBI2 | sin46:
						pcUser->dwTime_BigHead = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE1;
						pcUser->dwBigHead_SetNextTime = 0;
						pcUser->BigHeadType = 14;
						rsSendGameServer_BigHead(pcUser);
						break;
					case sinBI2 | sin47:
						pcUser->dwTime_BigHead = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE1;
						pcUser->dwBigHead_SetNextTime = 0;
						pcUser->BigHeadType = 15;
						rsSendGameServer_BigHead(pcUser);
						break;
					case sinBI2 | sin58:
						pcUser->dwTime_BigHead = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE1;
						pcUser->dwBigHead_SetNextTime = 0;
						pcUser->BigHeadType = 16;
						rsSendGameServer_BigHead(pcUser);
						break;
						//´©É½¼×Ò»¼Ò
					case sinBI2 | sin69:
						pcUser->dwCaravan_Hopy_Time = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_EXPUPx7;
						pcUser->dwCaravan_SetNextTime = 0;
						pcUser->dwCaravan_Param = 2;
						rsSendGameServer_CaravanHopy(pcUser);
						break;
						//²¼ÂíÐÜÒ»¼Ò
					case sinBI2 | sin70:
						pcUser->dwCaravan_Hopy_Time = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_EXPUPx7;
						pcUser->dwCaravan_SetNextTime = 0;
						pcUser->dwCaravan_Param = 3;
						rsSendGameServer_CaravanHopy(pcUser);
						break;
						//ºì¶À½ÇÊÞÒ»¼Ò
					case sinBI2 | sin71:
						pcUser->dwCaravan_Hopy_Time = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_EXPUPx7;
						pcUser->dwCaravan_SetNextTime = 0;
						pcUser->dwCaravan_Param = 4;
						rsSendGameServer_CaravanHopy(pcUser);
						break;
						//Ð¡ÂÌÈËÒ»¼Ò
					case sinBI2 | sin72:
						pcUser->dwCaravan_Hopy_Time = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_EXPUPx7;
						pcUser->dwCaravan_SetNextTime = 0;
						pcUser->dwCaravan_Param = 5;
						rsSendGameServer_CaravanHopy(pcUser);
						break;
						//°×ÍÃÒ»¼Ò
					case sinBI2 | sin73:
						pcUser->dwCaravan_Hopy_Time = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_EXPUPx7;
						pcUser->dwCaravan_SetNextTime = 0;
						pcUser->dwCaravan_Param = 6;
						rsSendGameServer_CaravanHopy(pcUser);
						break;
						//ºìÍÃÒ»¼Ò
					case sinBI2 | sin74:
						pcUser->dwCaravan_Hopy_Time = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_EXPUPx7;
						pcUser->dwCaravan_SetNextTime = 0;
						pcUser->dwCaravan_Param = 7;
						rsSendGameServer_CaravanHopy(pcUser);
						break;
					case sinBI2 | sin75:
						pcUser->dwTime_BigHead = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE1;
						pcUser->dwBigHead_SetNextTime = 0;
						pcUser->BigHeadType = 17;
						rsSendGameServer_BigHead(pcUser);
						break;
					case sinBI2 | sin76:
						pcUser->dwTime_BigHead = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_PACKAGE1;
						pcUser->dwBigHead_SetNextTime = 0;
						pcUser->BigHeadType = 18;
						rsSendGameServer_BigHead(pcUser);
						break;
					case sinBI2 | sin77:
						pcUser->dwCaravan_Hopy_Time = ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_EXPUPx7;
						pcUser->dwCaravan_SetNextTime = 0;
						pcUser->dwCaravan_Param = 8;
						rsSendGameServer_CaravanHopy(pcUser);
						break;
					case sinBI2 | sin82:
						SERVERCHARACTER->GiveEXP(pcUser, 1000000);
						break;
					case sinBI2 | sin83:
						SERVERCHARACTER->GiveEXP(pcUser, 10000000);
						break;
					case sinBI2 | sin84:
						SERVERCHARACTER->GiveEXP(pcUser, 100000000);
						break;
					case sinBI2 | sin85:
						SERVERCHARACTER->GiveEXP(pcUser, 1000000000);
						break;
					case sinBI2 | sin86:
						SERVERCHARACTER->GiveEXP(pcUser, 10000000000);
						break;
					case sinBI2 | sin87:
						SERVERCHARACTER->GiveEXP(pcUser, 100000000000);
						break;
					case sinBI2 | sin88:
						SERVERCHARACTER->GiveEXP(pcUser, 1000000000000);
						break;
					case sinBI2 | sin89:
						SERVERCHARACTER->GiveEXP(pcUser, 10000000000000);
						break;
					case sinBI2 | sin90:
						SERVERCHARACTER->GiveEXP(pcUser, 100000000000000);
						break;
					case sinBI2 | sin91:
						SERVERCHARACTER->GiveEXP(pcUser, 1000000000000000);
						break;
					}

					len = 100;
				}
			}

			if (lpTransCommandEx->WParam == (sinGG1 | sin01))
			{
				if (pcUser->GetGold() >= lpTransCommandEx->ExParam)
					SERVERUSER->SubServerUserGold(pcUser, lpTransCommandEx->ExParam, WHEREID_DropItem);
				else
				{
					smTransCommand.WParam = 8010;
					smTransCommand.LParam = 20;
					smTransCommand.SParam = pcUser->GetGold();
					smTransCommand.EParam = lpTransCommandEx->ExParam;
					RecordHackLogFile(pcUser, &smTransCommand);
					break;
				}
				rsRecord_ItemLog(pcUser, sinGG1 | sin01, lpTransCommandEx->ExParam, 0, ITEMLOG_PUT);
			}
			else
			{
				if (len == 100)
					rsRecord_ItemLog2(pcUser, lpTransCommandEx->WParam, lpTransCommandEx->LParam, lpTransCommandEx->SParam, ITEMLOG_USE_ALCHMY);
				else
					rsRecord_ItemLog(pcUser, lpTransCommandEx->WParam, lpTransCommandEx->LParam, lpTransCommandEx->SParam, ITEMLOG_PUT);
			}

			pcUser->UnsaveMoney = lpTransCommandEx->WxParam - lpTransCommandEx->ExParam;
		}
#endif
		if (pcUser && lpTransCommandEx->WParam != (sinGG1 | sin01))
			SaveThrowItem(pcUser, lpTransCommandEx->WParam, lpTransCommandEx->LParam, lpTransCommandEx->SParam);

		rsRegist_ItemSecCode(pcUser, lpTransCommandEx);

		SENDPACKET(pcUser, lpTransCommandEx);

		break;
		// Êý¾Ý·þÎñÆ÷½ÓÊÜVIPÐÅÏ¢²¢ÅÐ¶ÏVIPÊ±¼ä
	case smTRANSCODE_PLAYER_DATA_VIP:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		if (lpTransCommand->WParam > 0)
			rsSendVipInfoToGameServer(pcUser);
		else
		{
			smTRANS_COMMAND smTransCommand;
			smTransCommand.WParam = 1700;
			smTransCommand.SParam = 0;
			smTransCommand.LParam = 0;
			RecordHackLogFile(pcUser, &smTransCommand);
		}
		break;
		// ÓÎÏ··þÎñÆ÷½ÓÊÜVIPÐÅÏ¢
	case smTRANSCODE_PLAYER_GAME_VIP:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		pcUser->dwVipLevel = lpTransCommand->WParam ^ smTRANSCODE_PLAYER_GAME_VIP;
		pcUser->dwVipTime = lpTransCommand->LParam ^ smTRANSCODE_PLAYER_GAME_VIP;

		if (pcUser->dwVipLevel > 0)
		{
			if (pcUser->dwVipTime <= (DWORD)SERVER_LOCATIME)
			{
				pcUser->dwVipLevel = 0;
				pcUser->dwVipTime = 0;
				rsCloseVipInfoToClient(pcUser); // ½áÊøVIPÐÅÏ¢
			}
		}
		break;
		// È¡ÏûË®¾§
	case smTRANSCODE_CRYSTAL_ORB:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;

		int JobCode, SkillCode;
		JobCode = pcUser->sCharacterData.iClass;
		SkillCode = lpTransCommand->WParam;

		for (int i = 0; i < SIN_MAX_SKILL_LIST; i++)
		{
			if (SkillCode == SKILL_METAL_GOLEM || SkillCode == SKILL_RECALL_WOLVERIN || SkillCode == SKILL_S_ARCUDA || SkillCode == SKILL_FIRE_ELEMENTAL || SkillCode == SKILL_RECALL_BLOODYKNIGHT)
			{
				if (pcUser->lpLinkChar[i])
				{
					if ((JobCode == CHARACTERCLASS_Mechanician && pcUser->lpLinkChar[i]->iPetID == SKILL_PLAY_METAL_GOLEM) ||
						(JobCode == CHARACTERCLASS_Archer && pcUser->lpLinkChar[i]->iPetID == SKILL_PLAY_RECALL_WOLVERIN) ||
						(JobCode == CHARACTERCLASS_Atalanta && pcUser->lpLinkChar[i]->iPetID == SKILL_PLAY_S_ARCUDA) ||
						(JobCode == CHARACTERCLASS_Magician && pcUser->lpLinkChar[i]->iPetID == SKILL_PLAY_FIRE_ELEMENTAL) ||
						(JobCode == CHARACTERCLASS_Shaman && pcUser->lpLinkChar[i]->iPetID == SKILL_PLAY_CRIMSON_KNIGHT))
					{
						rsCancelCrystalToClient(pcUser, pcUser->lpLinkChar[i]);
						break;
					}
				}
			}
			else if (SkillCode == SKILL_CRYSTAL_ORB)
			{
				if (pcUser->lpLinkChar[i] && pcUser->lpLinkChar[i]->iPetID == SkillCode && pcUser->lpLinkChar[i]->iID == lpTransCommand->LParam)
				{
					rsCancelCrystalToClient(pcUser, pcUser->lpLinkChar[i]);
					break;
				}
			}
		}
		break;
		// ÊÍ·Å¶À½ÇÊÞÒ»¼ÒÐ­Òé
	case smTRANSCODE_CARAVAN_HOPY:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		rsSetCaravanHopy(pcUser, lpTransCommand->WParam ^ smTRANSCODE_CARAVAN_HOPY, lpTransCommand->LParam ^ smTRANSCODE_CARAVAN_HOPY);
		break;
		// ¹þ±ÈµÄÍ£Ö¹»ò¸úËæ
	case smTRANSCODE_CARAVAN_SELECT:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		rsSetCaravanHopyMode(pcUser, lpTransCommand->WParam);
		break;
	case smTRANSCODE_SAVETHROWITEMS:

		if (pcUser)
			SaveThrowItems(pcUser, (TRANS_THROW_ITEMS	*)psPacket);
		break;
		// ½ÓÊÜ·¢ËÍ¹ýÀ´µÄ½ðÇ®
	case smTRANSCODE_SAVETHROWMONEY:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		if (pcUser)
			pcUser->UnsaveMoney = lpTransCommand->WParam;
		break;
	case smTRANSCODE_CHECK_EXPMONEY:
		rsCheckTotalExpMoney(pcUser, (TRANS_TOTAL_EXPMONEY *)psPacket);
		break;
	case smTRANSCODE_CHECK_ADMINMODE:
		//°ü¸®ÀÚ ¸ðµå È®ÀÎ
		rsCheckAdminPlayer(pcUser);
		break;
	case smTRANSCODE_SET_OBJSERIAL:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		pcUser->iID = lpTransCommand->WParam;
		pcUser->TransInfoFlag = TRUE;
		break;
	case smTRANSCODE_SET_BLACKLIST:
	case smTRANSCODE_SET_BLACKLIST2:
	case smTRANSCODE_SET_BLACKLIST3:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		RecordHackLogFile(pcUser, lpTransCommand);
		break;

	case smTRANSCODE_SET_ITEMCOPYLIST:
		//º¹»ç ¾ÆÀÌÅÛ ¼ÒÁöÇÑ À¯Àú ·Î±×ÆÄÀÏ¿¡ ±â·Ï
		lpTransCommand = (smTRANS_COMMAND *)psPacket;

		smTransCommand.WParam = 1000;
		smTransCommand.LParam = lpTransCommand->WParam;
		smTransCommand.SParam = 0;
		RecordHackLogFile(pcUser, &smTransCommand);
		break;

	case smTRANSCODE_FINDCRACK:
		break;
		// ·¢ÏÖºÚ¿Í³ÌÐò
	case smTRANSCODE_FINDCRACK2:
		break;

	case smTRANSCODE_MODULE_WARNIG:
		//Å¬¶óÀÌ¾ðÆ®¿¡¼­ ¼ö»óÇÑ ¸ðµâ ¹ß°ß
		lpTransChatMessage = (TRANS_CHATMESSAGE *)psPacket;
		for (cnt = 0; cnt < (int)lpTransChatMessage->dwIP; cnt++)
			lpTransChatMessage->szMessage[cnt] ^= (cnt * 0x15);

		smTransCommand.WParam = 8720;
		smTransCommand.LParam = (DWORD)lpTransChatMessage->szMessage;
		smTransCommand.SParam = lpTransChatMessage->dwObjectSerial;
		RecordHackLogFile(pcUser, &smTransCommand);
		break;
	case smTRANSCODE_UPDATE_CINFO:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		switch (lpTransCommand->WParam)
		{
		case 0:
			pcUser->sCharacterData.iLevel = lpTransCommand->LParam;			//·¹º§ ÀúÀå
			break;
		case 1:
			pcUser->sCharacterData.iLevel = lpTransCommand->LParam;			//·¹º§ ÀúÀå
			pcUser->sCharacterData.iClanID = lpTransCommand->SParam;			//Å¬·£ Á¤º¸
			pcUser->sCharacterData.bUpdateInfo[0] = lpTransCommand->EParam;			//¾÷µ¥ÀÌÆ® Ä«¿îÅÍ °»½Å
			pcUser->iClanID = GetClanCodeByID(pcUser->sCharacterData.iClanID);			//Å¬·£ÄÚµå µî·Ï

			if (LOGIN_SERVER)
				SERVERBLESSCASTLE->SendBlessCastleSkill(pcUser);

			break;
		}
		break;
	case smTRANSCODE_OPENMONSTER:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		switch (lpTransCommand->EParam)
		{
		case	0: // Çö»ó¼ö¹è ¸ð¸®ÇÁ -> ¹Ì´Ï¸ð¸®ÇÁ
			rsOpenKidMonster(pcUser, lpTransCommand, 0);
			break;
		case	100: // ¹ÚÀç¿ø - °ø¼ºÀü Å©¸®½ºÅ» Å¸¿ö ¹æ¾î ¸ó½ºÅÍ ¼ÒÈ¯(Å©¸®½ºÅ» Å¸¿ö¸¦ ¹æ¾îÇÒ ¸ó½ºÅÍ¸¦ ¼ÒÈ¯ÇÑ´Ù.)
			rsOpenSODGuardMonster(pcUser, lpTransCommand, 0);
			break;
		case	101: // ¹ÚÀç¿ø - °ø¼ºÀü Å©¸®½ºÅ» Å¸¿ö ¹æ¾î ¸ó½ºÅÍ ¼ÒÈ¯(¼º¹®À» ¹æ¾îÇÒ ¸ó½ºÅÍ¸¦ ¼ÒÈ¯ÇÑ´Ù.)
			rsOpenSODGuardMonster(pcUser, lpTransCommand, 4);
			break;
		}
		break;

		lpTransCharCommand = (smTRANS_CHAR_COMMAND *)psPacket;

		lpStgArea = SERVERMAP->GetMapByXZ(pcUser->sPosition.iX, pcUser->sPosition.iZ);
		if (lpStgArea)
		{
			lpStgArea->bForceCreateMonster = TRUE;
			CharacterData sCharacterData;

			len = 0;

			if (lpStgArea->sSpawnSetting.iTotalMonsters)
			{
				rnd = (rand() % lpStgArea->sSpawnSetting.iTotalMonsterSpawnRate);
				for (cnt = 0; cnt < lpStgArea->sSpawnSetting.iTotalMonsters; cnt++)
				{
					if (lpStgArea->sSpawnSetting.saMonster[cnt].iSpawnRateCum > rnd)
						break;
				}
				memcpy(&sCharacterData, lpStgArea->sSpawnSetting.saMonster[cnt - 1].psCharacter, sizeof(CharacterData));
				len++;
			}

			BOOL bRet = FALSE;

			if (lpTransCharCommand->szName[0])
			{
				auto pMonstTable = SERVERUNIT->GetMonsterTable();

				for (auto & pc : pMonstTable)
				{
					if (STRINGCOMPARE(pc->szName, lpTransCharCommand->szName))
					{
						memcpy(&sCharacterData, pc, sizeof(CharacterData));
						bRet = TRUE;
						break;
					}
				}
			}

			if (len || bRet)
			{
				lpChar = SERVERMAP->CreateUnit(lpStgArea, &sCharacterData);

				if (lpChar)
				{
					lpChar->pX = pcUser->sPosition.iX;
					lpChar->pY = pcUser->sPosition.iY;
					lpChar->pZ = pcUser->sPosition.iZ;
					lpChar->SetMotionFromCode(ANIMATIONTYPE_Idle);
					lpChar->TargetMoveCount = 0;
				}
			}
		}
		break;

	case smTRANSCODE_TRADEITEMS:
		lpTransTradeItems = (TRANS_TRADEITEMS *)psPacket;
		lpPlayInfo2 = SERVERUSER->GetUser(lpTransTradeItems->dwRecver);

		SENDPACKET(lpPlayInfo2, lpTransTradeItems);
		break;

	case smTRANSCODE_TRADE_ITEMKEY:
		lpTransTradeItems = (TRANS_TRADEITEMS *)psPacket;
		lpPlayInfo2 = SERVERUSER->GetUser(lpTransTradeItems->dwRecver);
		if (lpPlayInfo2)
		{
			if (rsTradeInvenItem(pcUser, lpPlayInfo2, (TRANS_TRADE_ITEMKEY *)psPacket) == TRUE)
				SENDPACKET(lpPlayInfo2, lpTransTradeItems);
		}
		break;

	case smTRANSCODE_TRADE_READYITEM:
		lpTransTradeItems = (TRANS_TRADEITEMS *)psPacket;
		lpPlayInfo2 = SERVERUSER->GetUser(lpTransTradeItems->dwRecver);

		SENDPACKET(lpPlayInfo2, lpTransTradeItems);

		break;

	case smTRANSCODE_TRADE_REQUST:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		lpPlayInfo2 = SERVERUSER->GetUser(lpTransCommand->WParam);
		if (lpPlayInfo2)
		{
			if (pcUser->dwFuncChkErrorFlag || lpPlayInfo2->dwFuncChkErrorFlag)
				break;
			if (pcUser->szServerID[0])
				break;

			SENDPACKET(lpPlayInfo2, lpTransCommand);
		}
		break;
	case smTRANSCODE_PARTY_POTION:

		break;
		// ²Ö¿â½ðÇ®
	case smTRANSCODE_WAREHOUSEMONEY:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;

		if (pcUser->bWarehouseOpen)
		{
			switch (lpTransCommand->LParam)
			{
			case SENDWAREHOUSEMONEY:
				if (lpTransCommand->WParam >= 0 && lpTransCommand->WParam <= pcUser->GetGold())
				{
					pcUser->WareHouseMoney += lpTransCommand->WParam;
					pcUser->iInventoryGold -= lpTransCommand->WParam;
				}
				break;
			case RECVWAREHOUSEMONEY:
				if (lpTransCommand->WParam >= 0 && lpTransCommand->WParam <= pcUser->WareHouseMoney)
				{
					pcUser->WareHouseMoney -= lpTransCommand->WParam;
					pcUser->iInventoryGold += lpTransCommand->WParam;
				}
				break;
			}
		}
		break;
	case smTRANSCODE_WAREHOUSE:
		if (pcUser->dwFuncChkErrorFlag)
		{
			smTransCommand.WParam = 1130;
			smTransCommand.SParam = pcUser->Client_Version;
			smTransCommand.LParam = pcUser->dwFuncChkErrorFlag;
			RecordHackLogFile(pcUser, &smTransCommand);
			SERVERNET->DisconnectUser(pcUser->pcSocketData);
			break;
		}
		if (pcUser->bWarehouseOpen)
		{
			rsSaveWareHouseData(pcUser, (TRANS_WAREHOUSE *)psPacket);
			pcUser->dwRecordDataTime = 1;
		}
		break;
	case smTRANSCODE_OPEN_WAREHOUSE:
		if (!pcUser->dwFuncChkErrorFlag)
			SendWareHouseToClient(pcUser);
		break;
	case smTRANSCODE_OPEN_CARAVAN:
		if (!pcUser->dwFuncChkErrorFlag)
			SendCaravanToClient(pcUser);
		break;
	case smTRANSCODE_CARAVAN:
		if (pcUser->dwFuncChkErrorFlag)
		{
			smTransCommand.WParam = 1130;
			smTransCommand.SParam = pcUser->Client_Version;
			smTransCommand.LParam = pcUser->dwFuncChkErrorFlag;
			RecordHackLogFile(pcUser, &smTransCommand);
			SERVERNET->DisconnectUser(pcUser->pcSocketData);
			break;
		}
		if (pcUser->OpenCaravanInfoFlag)
		{
			rsSaveCaravanData(pcUser->szCharacterName, (TRANS_CARAVAN *)psPacket);
			pcUser->dwRecordDataTime = 1;
		}
		break;
	case smTRANSCODE_COLLECTMONEY:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;

		pcUser->UnsaveMoney = lpTransCommand->LParam;
		pcUser->spMoney_In += lpTransCommand->WParam;
		rsEnterHardCoreEvent(pcUser, lpTransCommand->WParam);
		break;
	case smTRANSCODE_CRAFTITEM:
		rsRecvCraftItem(pcUser, (sCRAFTITEM_SERVER *)psPacket);
		break;
	case smTRANSCODE_AGINGITEM:
		// ¶ÍÔìÎïÆ·Ð­Òé
		rsRecvAgingItem(pcUser, (sCRAFTITEM_SERVER *)psPacket);
		break;
	case smTRANSCODE_AGING_UPGRADE:
		// ¶ÍÔìÉý¼¶
		rsRecvAgingUpgradeItem(pcUser, (TRANS_ITEMINFO *)psPacket);
		break;
	case smTRANSCODE_MAKE_LINKCORE:
		//¸µÅ© ÄÚ¾î µî·Ï ¿äÃ»
		rsRecvMakeLinkCore(pcUser, (TRANS_ITEMINFO *)psPacket);
		break;
	case smTRANSCODE_USE_LINKCORE:
		//¸µÅ©ÄÚ¾î »ç¿ë
		rsRecvUseLinkCore(pcUser, (TRANS_ITEMINFO *)psPacket);
		break;
	case smTRANSCODE_WINGITEM:
		//À® ¾ÆÀÌÅÛ È¹µæ
		rsRecvWingItem(pcUser, (sCRAFTITEM_SERVER *)psPacket);
		break;
	case smTRANSCODE_SHOPTITEM:
		//»óÁ¡ ¾ÆÀÌÅÛ ±¸ÀÔ ¹ÞÀ½
		rsRecvBuyShopItem(pcUser, (TRANS_BUY_SHOPITEM *)psPacket);
		break;
	case smTRANSCODE_SHOP_SELLITEM:
		//»óÁ¡ ¾ÆÀÌÅÛ ÆÇ¸Å ¹ÞÀ½
		rsRecvSellShopItem(pcUser, (TRANS_ITEMINFO *)psPacket);
		break;
	case smTRANSCODE_ELEMENTITEM:
		// ÊôÐÔÏµÍ³Ð­Òé
		rsRecvElementItem(pcUser, (ELEMENT_ITEM_SERVER *)psPacket);
		break;
	case smTRANSCODE_SOCKETITEM:
		//´ò¿×ÏµÍ³
		rsRecvSocketItem(pcUser, (SOCKET_ITEM_SERVER *)psPacket);
		break;
	case smTRANSCODE_CHECKITEM:
		//º¸³»¿Â ¾ÆÀÌÅÛ ÀÎÁõ È®ÀÎ
		rsCheckItemCode(pcUser, &((TRANS_ITEMINFO *)psPacket)->sItem);
		break;
	case smTRANSCODE_CLIENT_FUNCPOS:
		//Å¬¶óÀÌ¾ðÆ® Æã¼Ç Æ÷Áö¼Ç ÀÔ¼ö
		rsRecvClientFuncPos((TRANS_CLIENT_FUNPOS *)psPacket);
		break;
	case smTRANSCODE_FUNCTON_RESULT:
	case smTRANSCODE_FUNCTION_MEM2:
		//Å¬¶óÀÌ¾ðÆ® Æã¼Ç °Ë»ç °á°ú ÀÔ¼ö
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		rsCompClientFuncMem(pcUser, lpTransCommand->WParam, lpTransCommand->EParam);
		break;
	case smTRANSCODE_FUNCERROR:
		if (!pcUser->dwFuncChkErrorFlag)
			pcUser->dwFuncChkErrorFlag = TRUE;
		break;
	case smTRANSCODE_BAD_PLAYER:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		pcUser->BadPlayer = lpTransCommand->WParam;
		break;
	case smTRANSCODE_HEALING:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		rsPlayHealing(lpTransCommand);
		break;
	case smTRANSCODE_GRAND_HEALING:
		PRIESTESSSKILL->RestoreHPPacketParty(pcUser,(PacketRestoreHP *)psPacket);
		break;
	case smTRANSCODE_HOLYMIND:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		rsPlayHolyMind(lpTransCommand);
		break;
	case smTRANSCODE_FIX_ATTACK:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;

		if (!pcUser->BadPlayer)
		{
			lpTransCommand = (smTRANS_COMMAND *)psPacket;
			smTransCommand.WParam = 7100;
			smTransCommand.LParam = lpTransCommand->WParam;
			smTransCommand.SParam = lpTransCommand->LParam;
			smTransCommand.EParam = lpTransCommand->SParam;
			RecordHackLogFile(pcUser, &smTransCommand);
		}

		rsSend_BadPlayerToGameServer(pcUser, 1);
		break;
	case smTRANSCODE_CLIENT_ERROR:

		lpTransCommand = (smTRANS_COMMAND *)psPacket;

		if (!pcUser->BadPlayer)
		{
			lpTransCommand = (smTRANS_COMMAND *)psPacket;
			smTransCommand.WParam = 7110;
			smTransCommand.LParam = lpTransCommand->LParam;
			smTransCommand.SParam = lpTransCommand->SParam;
			smTransCommand.EParam = lpTransCommand->EParam;
			RecordHackLogFile(pcUser, &smTransCommand);
		}

		rsSend_BadPlayerToGameServer(pcUser, 1);

		break;

	case smTRANSCODE_RECORD_TRADE:
		rsRecvRecordTradeItem(pcUser, (TRANS_RECORD_TRADE_ITEMS *)psPacket);
		break;
	case smTRANSCODE_INVEN_ERR_ITEM:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		smTransCommand.WParam = 7150;
		smTransCommand.LParam = lpTransCommand->LParam;
		smTransCommand.SParam = lpTransCommand->SParam;
		smTransCommand.EParam = lpTransCommand->EParam;
		RecordHackLogFile(pcUser, &smTransCommand);
		break;
	case smTRANSCODE_INVEN_ERR_MONEY:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		smTransCommand.WParam = 7160;
		smTransCommand.LParam = lpTransCommand->LParam;
		smTransCommand.SParam = lpTransCommand->SParam;
		smTransCommand.EParam = lpTransCommand->EParam;
		RecordHackLogFile(pcUser, &smTransCommand);
		break;
	/*case smTRANSCODE_GETITEM:
		lpTransCommandEx = (smTRANS_COMMAND_EX *)psPacket;

		cnt = lpTransCommandEx->EParam^smTRANSCODE_GETITEM^lpTransCommandEx->SParam;
		len = 0;

		if (rsCheck_ItemSecCode(pcUser, lpTransCommandEx->WParam, lpTransCommandEx->LParam, lpTransCommandEx->SParam, cnt, lpTransCommandEx->WxParam, lpTransCommandEx->LxParam, lpTransCommandEx->SxParam, lpTransCommandEx->ExParam, &len) > 0)
		{
			if (lpTransCommandEx->WParam == (sinGG1 | sin01))
			{
				SERVERUSER->AddServerUserGold(pcUser, cnt, WHEREID_GetItem);
				rsRecord_ItemLog(pcUser, sinGG1 | sin01, cnt, 0, ITEMLOG_GET);
				if (cnt > 1000000)
				{
					char szTemp[256];
					wsprintf(szTemp, "Debug GetMoney ID(%s) Name(%s) ( Money:%d SvCode:%d SndCount:%d iHead:%d iChkSum:%d SeCode:%d %d %d %d )",
						pcUser->szAccountName, pcUser->szCharacterName, cnt, lpTransCommandEx->LParam, lpTransCommandEx->SParam,
						lpTransCommandEx->WxParam, lpTransCommandEx->LxParam, lpTransCommandEx->SxParam, lpTransCommandEx->ExParam);
					Record_TempLogFile(szTemp);
				}
			}
			else
			{
				if (len)
					SERVERITEM->AddPotion(pcUser, lpTransCommandEx->WParam, len);

				SERVERITEM->AddItemInventory(pcUser, lpTransCommandEx->WParam, lpTransCommandEx->LParam, lpTransCommandEx->SParam);

				rsRecord_ItemLog(pcUser, lpTransCommandEx->WParam, lpTransCommandEx->LParam, lpTransCommandEx->SParam, ITEMLOG_GET);
			}

			SENDPACKET(pcUser, lpTransCommandEx);
		}
		break;*/

	case smTRANSCODE_USEITEM_CODE:
		//»ç¿ëÇÑ ¾ÆÀÌÅÛ
		lpTransCommandEx = (smTRANS_COMMAND_EX *)psPacket;

		//À®¾ÆÀÌÅÛ »ç¶óÁö´Â°Å ¶«½Ã sinQW¸¦ Ãß°¡ Çß´Ù
		if (lpTransCommandEx->WParam >= sinPM1 && (lpTransCommandEx->WParam&sinITEM_MASK2) != sinQW1 &&
			(lpTransCommandEx->WParam&sinITEM_MASK2) != sinPZ1 && (lpTransCommandEx->WParam&sinITEM_MASK2) != sinPZ2 &&
			(lpTransCommandEx->WParam&sinITEM_MASK2) != sinCH1) {

			//ÀÎº¥ ¾ÆÀÌÅÛ Á¦°Å
			SERVERITEM->DeleteItemInventory(pcUser,
				lpTransCommandEx->WParam,
				lpTransCommandEx->LParam,
				lpTransCommandEx->SParam);
			SaveThrowItem(pcUser, lpTransCommandEx->WParam, lpTransCommandEx->LParam, lpTransCommandEx->SParam);

			if ((lpTransCommandEx->WParam&sinITEM_MASK2) == sinGP1 ||
				(lpTransCommandEx->WParam&sinITEM_MASK2) == sinBI1 ||
				(lpTransCommandEx->WParam&sinITEM_MASK2) == sinBC1 ||
				(lpTransCommandEx->WParam&sinITEM_MASK2) == sinSP1) // Àåº° - ¿µÈ­ Ç÷Åõ
			{
				// Àåº° - ¿µÈ­ Ç÷Åõ
				if ((lpTransCommandEx->WParam&sinITEM_MASK2) == sinSP1)
				{
					if ((lpTransCommandEx->WParam&sinITEM_MASK3) == sin60 || (lpTransCommandEx->WParam&sinITEM_MASK3) == sin61 ||
						(lpTransCommandEx->WParam&sinITEM_MASK3) == sin62 || (lpTransCommandEx->WParam&sinITEM_MASK3) == sin63)
					{
						RecordMovieBloodyBattleItem(pcUser, NULL);
					}
				}
				else //»ç¿ëÇÑ ¾ÆÀÌÅÛ ·Î±× ( ¸ó½ºÅÍ Å©¸®½ºÅ» °æÇ° ÀÀ¸ð )
					rsRecord_ItemLog2(pcUser, lpTransCommandEx->WParam, lpTransCommandEx->LParam, lpTransCommandEx->SParam, ITEMLOG_USED);
			}
		}
		else
		{
			smTransCommand.WParam = 8060;
			smTransCommand.LParam = lpTransCommandEx->WParam;
			smTransCommand.SParam = lpTransCommandEx->LParam;
			smTransCommand.EParam = lpTransCommandEx->SParam;
			RecordHackLogFile(pcUser, &smTransCommand);
		}
		if ((lpTransCommandEx->WParam&sinITEM_MASK2) == sinSP1)
		{
			if ((lpTransCommandEx->WParam & sinITEM_MASK3) == sin05 || (lpTransCommandEx->WParam & sinITEM_MASK3) == sin06 || (lpTransCommandEx->WParam & sinITEM_MASK3) == sin07 ||
				(lpTransCommandEx->WParam & sinITEM_MASK3) == sin08 || (lpTransCommandEx->WParam & sinITEM_MASK3) == sin09 || (lpTransCommandEx->WParam & sinITEM_MASK3) == sin10)
			{
				rsPutItem_TreasureBox(pcUser, lpTransCommandEx->WParam);
			}

			if ((lpTransCommandEx->WParam & sinITEM_MASK3) == sin34)
				rsPutItem_CapsuleItem(pcUser, lpTransCommandEx->WParam);
		}
		break;

	case smTRANSCODE_INVEN_POSITION:
		//ÀÎº¥Åä¸® ¾ÆÀÌÅÛ À§Ä¡ Á¤º¸
		CheckInvenItemPosition(pcUser, (TRANS_USINGITEM *)psPacket);
		break;
	case smTRANSCODE_INVEN_POSITION2:
		//ÀÎº¥Åä¸® ¾ÆÀÌÅÛ À§Ä¡ Á¤º¸
		CheckInvenItemPosition2(pcUser, (TRANS_USINGITEM *)psPacket);
		break;

	case smTRANSCODE_NSPRITE:
		//nSprite Áß±¹ÆÇ º¸¾ÈÇÁ·Î±×·¥
		cnt = nSprite_GetResult(((smTRANS_COMMAND_DWORD *)psPacket)->WParam);
		if (cnt != 0) {
			pcUser->dwDisconnectTime = SERVER_GAMETIME + ((rand() % 5) * 1000) + 1000 * 5;
			smTransCommand.WParam = 8130;
			smTransCommand.LParam = ((smTRANS_COMMAND *)psPacket)->WParam;
			smTransCommand.SParam = cnt;
			RecordHackLogFile(pcUser, &smTransCommand);
			pcUser->dwDisconnectTime = SERVER_GAMETIME + 10 * 1000;
		}
		pcUser->dwNSpriteTime = dwTime + 3 * 60000;		//°Ë»ç À¯È¿ ½Ã°£ ( 3ºÐ°£ À¯È¿ )
		break;

	case smTRANSCODE_REC_DAMAGEDATA:
		//°ø°Ý µ¥ÀÌÅ¸ ±â·Ï ¼öÄ¡ ºñ±³
		rsCompAttackData(pcUser, (smTRANS_COMMAND *)psPacket);
		break;

	case smTRANSCODE_SOD_RESULT:
		//SOD °á°ú ¹ÞÀ½
		lpTransCommandEx = (smTRANS_COMMAND_EX *)psPacket;

		if (rsCheck_ResulSOD(pcUser, lpTransCommandEx) == lpTransCommandEx->ExParam) {
			bSql_SODRecord(pcUser, lpTransCommandEx->WParam, lpTransCommandEx->LParam, lpTransCommandEx->SParam,
				lpTransCommandEx->WxParam, lpTransCommandEx->LxParam, lpTransCommandEx->SxParam, lpTransCommandEx->EParam);
		}
		break;

	case smTRANSCODE_SOD_RESULT2:
		if (pcUser->dwExclusiveNum == 0 && pcUser->sBellatraRoomID >= 0 && pcUser->sBellatraRoomID < 4)
			rsSod_GetRealTimeScore(pcUser, pcUser->sBellatraRoomID + 1);
		else
			rsSod_GetRealTimeScore(pcUser, 0);
		break;

	case smTRANSCODE_PARTY_SKILL:
		rsRecvSkillPartyUser((TRANS_PARTY_SKILL *)psPacket);
		break;
	case smTRANSCODE_PROCESS_SKILL:
		rsRecvProcessSkill(pcUser, (smTRANS_COMMAND *)psPacket);
		break;
	case smTRANSCODE_PROCESS_SKILL2:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;

		cnt = lpTransCommand->LParam;
		lpTransCommand->LParam = pcUser->iID;
		if (cnt == dm_GetCommandChkSum(lpTransCommand, pcUser->iID))
		{
			rsRecvProcessSkill(pcUser, lpTransCommand);
			break;
		}
		smTransCommand.code = smTRANSCODE_SET_BLACKLIST;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = 8500;
		smTransCommand.LParam = 3;
		smTransCommand.SParam = SERVER_CODE;
		smTransCommand.EParam = pcUser->iID;
		rsRecordDamageError(pcUser, &smTransCommand);
		break;

	case smTRANSCODE_CANCEL_SKILL:
		rsCancelSkill(pcUser, (smTRANS_COMMAND *)psPacket);
		break;

	case smTRANSCODE_UPDATEL_SKILL:
		//½ºÅ³ º¯°æ ¾÷µ¥ÀÌÆ®
		rsUpdateSkill(pcUser, (smTRANS_COMMAND *)psPacket);
		break;

	case smTRANSCODE_CLAN_SERVICE:
		//Å¬·£ ¼­ºñ½º ¸Þ¼¼Áö
		lpTransCharCommand2 = (smTRANS_CHAR_COMMAND2 *)psPacket;
		lpPlayInfo2 = SERVERUSER->GetUser(lpTransCharCommand2->LParam);

		SENDPACKET(lpPlayInfo2, lpTransCharCommand2);
		break;

	case smTRANSCODE_CLAN_UPDATE:
		//Å¬·£ ¾÷µ¥ÀÌÆ® ÇÏ±â
		rsClanUpdate(pcUser, (TRANS_CLAN_COMMAND_USER *)psPacket);
		break;
	case smTRANSCODE_DEAD_EXP:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;

		pcUser->sBlessCastle_Damage[1] = lpTransCommand->WParam;
		pcUser->sBlessCastle_Param[1] = lpTransCommand->LParam;
		pcUser->sBlessCastle_Param[0] = lpTransCommand->SParam;
		break;
	case smTRANSCODE_CLIENTINFO:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;

		lpTransCommand->WParam ^= ((DWORD *)(pcUser->szAccountName + 0))[0];
		lpTransCommand->LParam ^= ((DWORD *)(pcUser->szAccountName + 1))[0];
		lpTransCommand->SParam ^= ((DWORD *)(pcUser->szAccountName + 2))[0];
		lpTransCommand->EParam ^= ((DWORD *)(pcUser->szAccountName + 3))[0];

		pcUser->dwClentOS = lpTransCommand->WParam;
		pcUser->wClentOSVersion[0] = lpTransCommand->LParam >> 16;
		pcUser->wClentOSVersion[1] = lpTransCommand->LParam & 0xFFFF;
		pcUser->dwClentModulChkSum = lpTransCommand->SParam;
		pcUser->ClentModuleCount = lpTransCommand->EParam;
		break;
	case smTRANSCODE_LIMIT_DAMAGE:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;

		if (!pcUser->iID) break;

		cnt = lpTransCommand->WParam;
		lpTransCommand->WParam = 0;
		if (cnt == dm_GetCommandChkSum(lpTransCommand, pcUser->iID))
		{
			if (!lpTransCommand->LParam && !lpTransCommand->SParam)
			{
				pcUser->sLimitDamage[0] = 12;
				pcUser->sLimitDamage[1] = 15;
				pcUser->sLimitCritical[0] = 5;
			}
			else
			{
				pcUser->sLimitDamage[0] = (lpTransCommand->LParam * 120) / 100;
				pcUser->sLimitDamage[1] = (lpTransCommand->SParam * 120) / 100;
				pcUser->sLimitCritical[0] = (lpTransCommand->EParam * 120) / 100;
			}
		}
		else
		{
			smTransCommand.code = smTRANSCODE_SET_BLACKLIST;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.WParam = 8500;
			smTransCommand.LParam = 4;
			smTransCommand.SParam = SERVER_CODE;
			smTransCommand.EParam = pcUser->iID;
			rsRecordDamageError(pcUser, &smTransCommand);
		}
		break;

	case smTRANSCODE_WARNING_CLIENT:
		//Å¬¶óÀÌ¾ðÆ®·Î ºÎÅÍÀÇ °æ°í
		lpTransCommand = (smTRANS_COMMAND *)psPacket;

		cnt = lpTransCommand->EParam;
		lpTransCommand->EParam = 0;
		if (cnt == dm_GetCommandChkSum(lpTransCommand, pcUser->iID)) {

			switch (lpTransCommand->WParam)
			{
			case 100:
				smTransCommand.WParam = 8520;
				smTransCommand.LParam = ((smTRANS_COMMAND *)psPacket)->LParam;
				smTransCommand.SParam = 0;
				RecordHackLogFile(pcUser, &smTransCommand);

				break;
			case 101:
				smTransCommand.WParam = 8530;
				smTransCommand.LParam = ((smTRANS_COMMAND *)psPacket)->LParam;
				smTransCommand.SParam = 0;
				RecordHackLogFile(pcUser, &smTransCommand);

				break;
			}
		}
		break;

	case smTRANSCODE_WARNING_SKILL:
		//½ºÅ³ °æ°í
		if (pcUser->WarningCount > 3) break;

		lpTransCommand = (smTRANS_COMMAND *)psPacket;

		cnt = lpTransCommand->EParam;
		lpTransCommand->EParam = 0;
		if (cnt == dm_GetCommandChkSum(lpTransCommand, pcUser->iID)) {
			smTransCommand.WParam = 8550;
			smTransCommand.LParam = lpTransCommand->WParam;
			smTransCommand.SParam = lpTransCommand->LParam;
			smTransCommand.EParam = lpTransCommand->SParam;
			RecordHackLogFile(pcUser, &smTransCommand);
		}
		break;

	case smTRANSCODE_YAHOO_MOTION:
		//¾ßÈ£ µ¿ÀÛ ½ÇÇà
		rsRecvYahooMotion(pcUser, (smTRANS_COMMAND *)psPacket);
		break;

	case smTRANSCODE_STARPOINT:
		//º° Æ÷ÀÎÆ® Á¤º¸
		rsRecvStarPoint(pcUser, (smTRANS_COMMAND *)psPacket);
		break;

	case smTRANSCODE_CLANMONEY:
		//Å¬·£¸Ó´Ï µ¥ÀÌÅ¸
		rsRecvSodClanCash(pcUser, (smTRANS_COMMAND *)psPacket);
		break;

	case smTRANSCODE_PAYMENT_MONEY:
		//»ç¿ë¿ä±ÝÀ» ¹Þ´Â´Ù
		rsRecvPaymentMoney(pcUser, (smTRANS_COMMAND *)psPacket);
		break;

	case smTRANSCODE_GIVEMONEY:
		//µ· ±âºÎ
		rsRecvGiveMoney(pcUser, (smTRANS_COMMAND *)psPacket);
		break;

	case smTRANSCODE_OPENLIVE:
		RecvOpenLivePacket(pcUser, psPacket);

		break;
	case smTRANSCODE_REC_ADMIN_COMMAND:
		//¿î¿µÀÚ ¸í·É ÀúÀå
		lpTransChatMessage = (TRANS_CHATMESSAGE *)psPacket;
		rsSaveAdminCommand(pcUser, lpTransChatMessage->szMessage, lpTransChatMessage->dwIP);
		rsCheckAdminPlayer(pcUser);		//°ü¸®ÀÚ ÀÎÁö Á¶»ç
		break;

	case smTRANSCODE_WARNING_BLINK_ATT:
		//¹«Àû¸ðµå °æ°í
		lpTransCommand = (smTRANS_COMMAND *)psPacket;

		smTransCommand.WParam = 8600;
		smTransCommand.LParam = lpTransCommand->WParam;
		smTransCommand.SParam = lpTransCommand->LParam;
		smTransCommand.EParam = lpTransCommand->SParam;
		RecordHackLogFile(pcUser, &smTransCommand);
		break;

		// Àåº° - ÀÔ·ÂÃ¢
	case smTRANSCODE_ITEMDOC:
		lpTransChatMessage = (TRANS_CHATMESSAGE *)psPacket;
		if (pcUser->szServerID[0] || rsServerConfig.DisableThrowItem) break;													//¸ÖÆ¼±º ¿¬µ¿¼­¹ö °Å·¡±ÝÁö
		lpTransChatMessage->szMessage[127] = 0;
		lstrcpy(pcUser->szTradeMessage, lpTransChatMessage->szMessage);
		pcUser->dwTradeMsgCode = lpTransChatMessage->dwIP;
		break;

	case smTRANSCODE_OPEN_MYSHOP:		//°³ÀÎ »óÁ¡ ´ë¿ÀÇÂ
		lpTransChatMessage = (TRANS_CHATMESSAGE *)psPacket;
		if (pcUser->szServerID[0] || rsServerConfig.DisableThrowItem)
			break;
		lpTransChatMessage->szMessage[127] = 0;
		lstrcpy(pcUser->szTradeMessage, lpTransChatMessage->szMessage);
		pcUser->dwTradeMsgCode = lpTransChatMessage->dwIP;
		break;

	case smTRANSCODE_CALL_MYSHOP:		//°³ÀÎ »óÁ¡ Á¤º¸ ¿ä±¸
		lpTransCommand = (smTRANS_COMMAND *)psPacket;

		if (pcUser->szServerID[0] || rsServerConfig.DisableThrowItem)
			break;
		lpPlayInfo2 = SERVERUSER->GetUser(lpTransCommand->LParam);

		SENDPACKET(lpPlayInfo2, lpTransCommand);
		break;

	case smTRANSCODE_MYSHOP_ITEM:
		lpTransTradeItems = (TRANS_TRADEITEMS *)psPacket;
		lpPlayInfo2 = SERVERUSER->GetUser(lpTransTradeItems->dwRecver);
		SENDPACKET(lpPlayInfo2, lpTransTradeItems);
		break;

	case smTRANSCODE_MYSHOP_TRADE:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		if (pcUser->szServerID[0] || rsServerConfig.DisableThrowItem)
			break;
		lpPlayInfo2 = SERVERUSER->GetUser(lpTransCommand->LParam);
		if (lpPlayInfo2)
		{
			if (rsTrade_PersonalShop(pcUser, lpPlayInfo2, (smTRANS_COMMAND_BUFF *)psPacket) == TRUE)
				SENDPACKET(lpPlayInfo2, lpTransCommand);
		}
		break;

	case smTRANSCODE_MYSHOP_MESSAGE:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		lpPlayInfo2 = SERVERUSER->GetUser(lpTransCommand->LParam);

		if (pcUser->szServerID[0] || rsServerConfig.DisableThrowItem)
			break;
		if (lpPlayInfo2 && lpPlayInfo2->dwTradeMsgCode && lpPlayInfo2->dwTradeMsgCode == lpTransCommand->SParam)
		{
			lstrcpy(TransChatMessage.szMessage, lpPlayInfo2->szTradeMessage);
			TransChatMessage.code = smTRANSCODE_MYSHOP_MESSAGE;
			TransChatMessage.dwIP = 0;
			TransChatMessage.dwObjectSerial = lpTransCommand->LParam;
			TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);

			SENDPACKET(pcUser, &TransChatMessage);
		}
		break;

	case smTRANSCODE_FORCEORB_DATA:
		rsRecvAreaServerForceOrb(pcUser, (smTRANS_COMMAND *)psPacket);
		break;
	case smTRANSCODE_CANCEL_FORCE:
		pcUser->dwForceOrb_SaveCode = 0;
		pcUser->dwForceOrb_SaveTime = 0;
		rsSendServerToForceOrb(pcUser);
		break;
	case smTRANSCODE_BOOSTER_DATA: // ¹ÚÀç¿ø - ºÎ½ºÅÍ ¾ÆÀÌÅÛ(»ý¸í·Â, ±â·Â, ±Ù·Â)
		rsRecvAreaServerBoosterItem(pcUser, (smTRANS_COMMAND *)psPacket);
		break;

	case smTRANSCODE_AGING_DATA:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		//lpPlayInfo->iGameLevel = (EGameLevel)lpTransCommand->WParam;
		break;

	case smTRANSCODE_SKILLDELAY_DATA:
		rsRecvAreaServerSkillDelayItem(pcUser, (smTRANS_COMMAND *)psPacket);
		break;

	case smTRANSCODE_PRIMEITEM_DATA:
		//°ÔÀÓ ¼­¹ö°¡ ºô¸µ¾ÆÀÌÅÛ Á¤º¸ ÀÔ¼ö
		rsRecvGameServer_PrimeItem(pcUser, (smTRANS_COMMAND_EX *)psPacket);
		break;

	case smTRANSCODE_PRIMEITEM_DATA2:		// pluto ¸¶³ª ¸®µà½º Æ÷¼Ç ¸¶ÀÌÆ® ¿Àºê ¾ÆÀ£	¸¶ÀÌÆ® ¿Àºê ¾ÆÀ£2, ÇÇ´Ð½º Æê
		rsRecvGameServer_PrimeItem2(pcUser, (smTRANS_COMMAND_EX *)psPacket);
		break;

	case smTRANSCODE_PRIMEITEM_DATA3:		// ¹ÚÀç¿ø - ºô¸µ µµ¿ì¹Ì Æê, ¹ìÇÇ¸¯ Ä¿½ºÇÍ EX, ±Ù·Â ¸®µà½º Æ÷¼Ç, ±×¿Ü ½Ã°£Á¦ ¾ÆÀÌÅÛ Ãß°¡ÇÒ¶§ »ç¿ëÇÔ.
		rsRecvGameServer_PrimeItem3(pcUser, (smTRANS_COMMAND_EX *)psPacket);
		break;

	case smTRANSCODE_PCBANG_PET:
		rsRecvAreaServer_PCBangPet(pcUser, (smTRANS_COMMAND *)psPacket);
		break;
		// ·ï»ËÐ­Òé
	case smTRANSCODE_PHENIX_PET:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		rsSendPhoenixToClient(pcUser, lpTransCommand->WParam^smTRANSCODE_PHENIX_PET, lpTransCommand->LParam^smTRANSCODE_PHENIX_PET);
		break;
		// ´óÍ·Ð­Òé
	case smTRANSCODE_COMIC_SKIN:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		rsSendBigHeadToClient(pcUser, lpTransCommand->WParam^smTRANSCODE_COMIC_SKIN, lpTransCommand->LParam^smTRANSCODE_COMIC_SKIN);
		break;
		//È¡Ïû´óÍ·
	case smTRANSCODE_CANCEL_BIGHEAD:
		pcUser->dwTime_BigHead = 0;
		pcUser->BigHeadType = 0;
		rsSendGameServer_BigHead(pcUser);
		break;
		//È¡Ïû³èÎï²Ö¿â
	case smTRANSCODE_CANCEL_CARAVAN:
		pcUser->dwCaravan_Hopy_Time = 0;
		pcUser->dwCaravan_Param = 0;
		rsSendGameServer_CaravanHopy(pcUser);
		break;
	case smTRANSCODE_HELP_PET:
		rsRecvAreaServer_HelpPet(pcUser, (smTRANS_COMMAND *)psPacket);
		break;
		// ¹ûÊµÐ­Òé
	case smTRANSCODE_FRUIT:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		rsSendFruitToGame(pcUser, lpTransCommand);
		break;
	case smTRANSCODE_QUEST_COMMAND:
		//Äù½ºÆ® ÁøÇà ¸í·É
		rsGetQuestCommand(pcUser, (smTRANS_COMMAND *)psPacket);
		break;

	case smTRANSCODE_UPDATE_SERVER_PARAM:
		//´Ù¸¥¼­¹ö¿¡¼­ÀÇ ¾÷µ¥ÀÌÆ®
		rsRecvUpdateServerParam(pcUser, (smTRANS_COMMAND *)psPacket);
		break;

	case smTRANSCODE_RESISTANCE:
		//¼Ó¼ºÁ¤º¸ ¹ÞÀ½
		memcpy(pcUser->sCharacterData.sElementalDef, ((smTRANS_RESISTANCE *)psPacket)->Resistance, sizeof(short) * 8);
		for (cnt = 0; cnt < 8; cnt++)
		{
			if (pcUser->sCharacterData.sElementalDef[cnt] > 100 || pcUser->sCharacterData.sElementalDef[cnt] < -100)
				pcUser->sCharacterData.sElementalDef[cnt] = 0;
		}

		cnt = ((smTRANS_RESISTANCE *)psPacket)->Absorb;
		if (cnt >= 0 && cnt < 1000)
			pcUser->sCharacterData.iAbsorbRating = cnt;
		break;

	case smTRANSCODE_PUBLIC_POLLING:

		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		if (lpTransCommand->LParam == 0)
			bSql_PollRecord(pcUser, lpTransCommand->WParam, 0, 0);
		else
			bSql_PollRecord(pcUser, lpTransCommand->WParam, lpTransCommand->LParam, ((smTRANS_COMMAND_POLLING *)psPacket)->bPolling);
		break;

	case smTRANSCODE_USER_ID:	//°èÁ¤Á¤º¸ È¹µæ (º£Æ®³²)
		rsRecvUserID_MainServer(pcUser, (smTRANS_CHAR_COMMAND2 *)psPacket);
		break;

	case smTRANSCODE_HACKTRAP:	//ÇØÅ·¿ë ÇÔÁ¤
		rsRecvHackTrap(pcUser, (smTRANS_COMMAND *)psPacket);
		break;
	case smTRANSCODE_MIXTURE_RESET_ITEM:
		// ¼®Áö¿ë - ¹Í½ºÃÄ ¸®¼Â ¸Þ½ÃÁö Ã³¸®
		rsRecvMixtureResetItem(pcUser, (sMIXTURE_RESET_ITEM_SERVER *)psPacket);
		break;
	case smTRANSCODE_SMELTINGITEM:
		// pluto Á¦·Ã ¾ÆÀÌÅÛ ¹ÞÀ½
		rsRecvSmeltingItem(pcUser, (sSMELTINGITEM_SERVER *)psPacket);
		break;
	case smTRANSCODE_MANUFACTURE:
		// pluto Á¦ÀÛ ¾ÆÀÌÅÛ ¹ÞÀ½
		rsRecvManufactureItem(pcUser, (SManufactureItem_Server *)psPacket);
		break;

	case smTRANSCODE_EVENT_GAME: // Àåº° - ÀçºÐ¹è ÀÌº¥Æ®
		rsRecvEventGame(pcUser, (smTRANS_COMMAND *)psPacket);
		break;

	case smTRANSCODE_PREMIUMITEM_INIT:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		switch (lpTransCommand->WParam)
		{
		case 1:
			pcUser->dwTime_PrimeItem_X2 = 0;
			rsSendGameServer_PrimeItem(pcUser);
			break;
		case 2:
			pcUser->dwTime_PrimeItem_ExpUp = 0;
			rsSendGameServer_PrimeItem(pcUser);
			break;
		case 3:
			pcUser->dwTime_PrimeItem_VampCuspid = 0;
			rsSendGameServer_PrimeItem(pcUser);
			break;
		case 4:
			pcUser->dwTime_PrimeItem_ManaRecharg = 0;
			rsSendGameServer_PrimeItem(pcUser);
			break;
		case 5:
			break;
		case 6:
			pcUser->dwTime_PrimeItem_ManaReduce = 0;
			rsSendGameServer_PrimeItem(pcUser);
			break;
		case 7:
			pcUser->dwTime_PrimeItem_PhenixPet = 0;
			rsSendGameServer_PrimeItem(pcUser);
			break;
		case 8:
		case 9:
		case 10:
		case 11:
			pcUser->dwTime_PrimeItem_HelpPet = 0;
			rsSendGameServer_PrimeItem3(pcUser);
			break;
		case 12:
			pcUser->dwTime_PrimeItem_VampCuspid_EX = 0;
			rsSendGameServer_PrimeItem3(pcUser);
			break;
		case 13:
			pcUser->dwTime_PrimeItem_StaminaReduce = 0;
			rsSendGameServer_PrimeItem3(pcUser);
			break;
		}
		break;

	case smTRANSCODE_MANUFACTURE_WEIGHT_PRICE:
		ManufactureItemInfo(pcUser);
		break;
	}

	if (pcUser)
		pcUser->dwTimeLastPacket = dwTime;
#endif
}

int RecordSaveThrowData(User *lpPlayInfo)
{
	return TRUE;
}

extern CRITICAL_SECTION	cSocketSection;


//ShutDown ·Î±× »ý¼º
int RecordShutdownLog(int LogCode, int LParam, int SParam)
{
	smTRANS_COMMAND smTransCommand;

	smTransCommand.WParam = LogCode;
	smTransCommand.LParam = LParam;
	smTransCommand.SParam = SParam;
	RecordHackLogFile(0, &smTransCommand);

	return TRUE;
}



DWORD dwTimeCounter = 0;

int		Th_Record_PCJungFlag = -1;
HANDLE	hRecord_PCJung_Thread = 0;

DWORD WINAPI RecordPCJung_Thread(void *pInfo)
{
	HANDLE	hThread;
	DWORD	dwTime;
	DWORD	dwLastTime;
	int cnt;
	JUNGIP	Record_PcJungIP;
	JUNGIP	Record_PcJungIP2;

	hThread = GetCurrentThread();
	dwTime = GetCurrentTime();
	dwLastTime = dwTime;

	while (1) {
		if (rsServerConfig.Disable_LogIn != 2) {

			SERVER_MUTEX->Lock(3000);

			Record_PcJungIP.IPCount = 0;
			Record_PcJungIP2.IPCount = 0;

			for (cnt = 0; cnt < PLAYERS_MAX; cnt++)
			{
				User * u = USERSDATA + cnt;

				if (u && u->szAccountName[0] && u->GpType == 1)
				{
					if (u->GpCode == 0)
					{
						if (Record_PcJungIP.IPCount < JUNGIP_MAX) 
						{
							Record_PcJungIP.IP[Record_PcJungIP.IPCount++] =
								u->pcSocketData->lIP;
						}
					}
					if (u->GpCode == 1) 
					{
						if (Record_PcJungIP2.IPCount < JUNGIP_MAX) 
						{
							Record_PcJungIP2.IP[Record_PcJungIP2.IPCount++] =
								u->pcSocketData->lIP;
						}
					}
				}
			}

			SERVER_MUTEX->UnLock();

			if (Record_PcJungIP.IPCount) {	//PCÁ¤¾×
				b_IPRecord(SERVER_NAME, &Record_PcJungIP);
			}

			if (Record_PcJungIP2.IPCount) {	//PCÁ¤·®
				b_IPRecordTime(SERVER_NAME, &Record_PcJungIP2);
			}
		}

		Sleep(1000 * 60 * 2);		//2ºÐµ¿¾È ½½¸³
	}

	ExitThread(TRUE);
	return TRUE;
}


//PC¹æ IPÅëº¸ ¾²·¹µå »ý¼º
int OpenRecordPCJung_Thread()
{
	DWORD	dwRecordPCJungThreadID;

	if (!hRecord_PCJung_Thread) {
		hRecord_PCJung_Thread = CreateThread(NULL, 0, RecordPCJung_Thread, 0, 0, &dwRecordPCJungThreadID);
	}

	return TRUE;
}

#define		SERVER_DOWN_MIN			8

DWORD WINAPI ShutDownThreadProc(void *pInfo)
{
	int cnt;

	TRANS_CHATMESSAGE	TransChatMessage;
	int	rsServerDownCount = 0;
	DWORD	dwShutDownTime = GetCurrentTime() + 60 * 1000 * SERVER_DOWN_MIN;

	DWORD	dwTime;
	int		Sec, Min;
	int		SleepTime;

	bSql_ServerDown();

	while (1)
	{
		if (Quit)
		{
			ExitThread(TRUE);
			return TRUE;
		}

		dwTime = GetCurrentTime();
		Sec = (dwShutDownTime - dwTime);
		Sec /= 1000;
		if (Sec < 0)
			break;

		Min = Sec / 60;
		Sec = Sec % 60;
		ShutDownLeftTime = Min;

		if (rsServerDownCount < SERVER_DOWN_MSG_COUNT)
		{
			lstrcpy(TransChatMessage.szMessage, szServerDownMsg[rsServerDownCount]);
			rsServerDownCount++;
			Sleep(500);
		}
		else
		{
			wsprintf(TransChatMessage.szMessage, "Maintenance Countdown> %d mins %d secs.", Min, Sec);
			if (Min == 0)
				Sleep(1000 * 5);
			else
				Sleep(1000 * 30);
		}

		TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
		TransChatMessage.dwIP = 3;
		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
		TransChatMessage.dwObjectSerial = 0;

		for (cnt = 0; cnt < PLAYERS_MAX; cnt++)
		{
			User * u = USERSDATA + cnt;

			SleepTime = 0;
			SERVER_MUTEX->Lock(3000);

			SENDPACKET(u, &TransChatMessage);

			SleepTime = 5;

			SERVER_MUTEX->UnLock();
			if (SleepTime > 0) Sleep(SleepTime);
			if (Quit) {
				ExitThread(TRUE);
				return TRUE;
			}
		}

	}

	Sleep(1000 * 60);

	Quit = 1;

	ExitThread(TRUE);

	return TRUE;
}

HANDLE hShutDownThread = 0;
DWORD dwShutDownThreadId = 0;

int	rsShutDown()
{
	if (!hShutDownThread) {
		hShutDownThread = CreateThread(NULL, 0, ShutDownThreadProc, 0, 0, &dwShutDownThreadId);
		ShutDownFlag = TRUE;
		ShutDownLeftTime = SERVER_DOWN_MIN;

		RecordShutdownLog(50010, 0, 0);
		return TRUE;
	}

	return FALSE;
}

#include "e_serverlog.h"

int	rsSendTransCommand(User *lpPlayInfo, DWORD	dwCode, int WParam, int LParam, int SParam, int EParam)
{
	smTRANS_COMMAND	smTransCommand;

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = dwCode;
	smTransCommand.WParam = WParam;
	smTransCommand.LParam = LParam;
	smTransCommand.SParam = SParam;
	smTransCommand.EParam = EParam;

	SENDPACKET(lpPlayInfo, &smTransCommand);

	return FALSE;
}

//³ö´íÈÕÖ¾
int RecordHackLogFile(User *lpPlayInfo, void *lpBuff)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	smTRANS_COMMAND_EX	*lpTransCommand = (smTRANS_COMMAND_EX *)lpBuff;
	if (lpTransCommand->WParam == 6800)
		return FALSE;

	GetLocalTime(&st);
	wsprintf(szFileName, filenameHack, HackLogDirectory, st.wMonth, st.wDay);
	if (lpPlayInfo && lpPlayInfo->pcSocketData)
	{
		lpPlayInfo->szAccountName[31] = 0; lpPlayInfo->szCharacterName[31] = 0;
		wsprintf(szBuff, "%d:%d:%d IP-( %s ) ID-( %s ) Name-( %s ) / ( %d ) - ( %d , %d )\r\n", st.wHour, st.wMinute, st.wSecond, lpPlayInfo->pcSocketData->szIP, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpTransCommand->WParam, lpTransCommand->LParam, lpTransCommand->SParam);
	}
	else
		wsprintf(szBuff, "%d:%d:%d ( %d ) - ( %d , %d )\r\n", st.wHour, st.wMinute, st.wSecond, lpTransCommand->WParam, lpTransCommand->LParam, lpTransCommand->SParam);

#ifdef _W_SERVER

	smTRANS_COMMAND	smTransCommand;
	if (!lpPlayInfo || !lpPlayInfo->pcSocketData)
		goto LogSkip;
	if (lpTransCommand->WParam == 1000)
	{
		wsprintf(szBuff, msg1000, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam);

		if (!lpPlayInfo->BlockTime)
			lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->szAccountName, 1000 * 60 * 18);
	}
	if (lpTransCommand->WParam == 1010)
		wsprintf(szBuff, msg1010, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam);
	if (lpTransCommand->WParam == 1011)
		wsprintf(szBuff, msg1011, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam);
	if (lpTransCommand->WParam == 1100)
	{
		wsprintf(szBuff, msg1100, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, (char *)lpTransCommand->LParam);
		if (strstr((char *)lpTransCommand->LParam, "FPE") != 0)
			lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->szAccountName, 0x7FFFFFFF);
		else
			lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->szAccountName, 1000 * 60 * 60);
	}
	if (lpTransCommand->WParam == 1101)
	{
		wsprintf(szBuff, msg1101, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->sCharacterData.szName, lpPlayInfo->pcSocketData->szIP, (char *)lpTransCommand->LParam);
		if (strstr((char *)lpTransCommand->LParam, "FPE") != 0)
			lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->szAccountName, 1000 * 60 * 60 * 24);
		else
			lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->szAccountName, 1000 * 60 * 60);
	}
	if (lpTransCommand->WParam == 1102)
	{
		wsprintf(szBuff, msg1102, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam);
		if (!lpPlayInfo->BlockTime)
			lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->szAccountName, 1000 * 60 * 19);
	}
	if (lpTransCommand->WParam == 1103)
		wsprintf(szBuff, msg1103, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->SParam, lpTransCommand->LParam);
	if (lpTransCommand->WParam == 1110)
	{
		wsprintf(szBuff, msg1110, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->SParam, lpTransCommand->LParam);
		if (!lpPlayInfo->BlockTime)
			lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->szAccountName, 1000 * 60 * 60 * 1);
	}
	if (lpTransCommand->WParam == 1120)
	{
		wsprintf(szBuff, msg1120, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->SParam, lpTransCommand->LParam);
		lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->szAccountName, 0x7FFFFFFF);
		SERVERNET->DisconnectUser(lpPlayInfo->pcSocketData);
	}
	if (lpTransCommand->WParam == 1130)
	{
		wsprintf(szBuff, msg1130, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
		lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->szAccountName, 0x7FFFFFFF);
		rsAddBlockUserFile(lpPlayInfo->szAccountName, szBuff);
	}
	if (lpTransCommand->WParam == 1132)
	{
		wsprintf(szBuff, msg1132, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
		if (!lpPlayInfo->BlockTime)
			lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->szAccountName, 1000 * 60 * 60 * 24);
	}
	if (lpTransCommand->WParam == 1150)
		wsprintf(szBuff, msg1150, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->SParam, lpTransCommand->LParam);
	if (lpTransCommand->WParam == 1200)
	{
		wsprintf(szBuff, msg1200, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam);
		lpPlayInfo->CrackWarning = lpTransCommand->WParam;

		if (!lpPlayInfo->BlockTime)
			lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->szAccountName, 1000 * 60 * 60 * 2);
	}
	if (lpTransCommand->WParam == 1250)
	{
		wsprintf(szBuff, msg1250, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
		lpPlayInfo->CrackWarning = lpTransCommand->WParam;
	}
	if (lpTransCommand->WParam == 1400)
		wsprintf(szBuff, msg1400, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->sCharacterData.szName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam);

	if (lpTransCommand->WParam == 1500)
		wsprintf(szBuff, msg1500, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam);

	if (lpTransCommand->WParam == 1510)
	{
		wsprintf(szBuff, msg1510, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam);
		SERVERNET->DisconnectUser(lpPlayInfo->pcSocketData);
	}
	if (lpTransCommand->WParam == 1530)
	{
		wsprintf(szBuff, msg1530, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
		if (rsServerConfig.Dis_PotionError)
		{
			if (!lpPlayInfo->BlockTime)
				lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->szAccountName, rsServerConfig.Dis_PotionError*(1000 * 60));
			lpPlayInfo->dwTime_Disconnect = 1;
			rsSendTransCommand(lpPlayInfo, smTRANSCODE_CLEARPOTION, 0, 0, 0, 0);
		}
	}
	if (lpTransCommand->WParam == 1600)
	{
		wsprintf(szBuff, msg1600, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->sCharacterData.szName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam);
		if (!lpPlayInfo->BlockTime)
			lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->szAccountName, 1000 * 60 * 60);
	}
	if (lpTransCommand->WParam == 1700)
		wsprintf(szBuff, msg1700, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP);
	if (lpTransCommand->WParam == 1800)
		wsprintf(szBuff, msg1800, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->sCharacterData.szName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam);
	if (lpTransCommand->WParam == 1820)
	{
		wsprintf(szBuff, msg1820, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam);
		lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->szAccountName, 0x7FFFFFFF);
	}
	if (lpTransCommand->WParam == 1821)
	{
		wsprintf(szBuff, msg1821, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam);
		lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->szAccountName, 0x7FFFFFFF);
	}
	if (lpTransCommand->WParam == 1823)
	{
		wsprintf(szBuff, msg1823, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam);
	}
	if (lpTransCommand->WParam == 1830)
		wsprintf(szBuff, msg1830, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->sCharacterData.szName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam);
	if (lpTransCommand->WParam == 1833)
		wsprintf(szBuff, msg1833, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->sCharacterData.szName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam);

	if (lpTransCommand->WParam == 1840)
	{
		wsprintf(szBuff, msg1840, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
	}
	if (lpTransCommand->WParam == 1900)
		wsprintf(szBuff, msg1900, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->sCharacterData.szName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam);
	if (lpTransCommand->WParam == 1950)
		wsprintf(szBuff, msg1950, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->sCharacterData.szName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam);
	if (lpTransCommand->WParam == 1960)
		wsprintf(szBuff, msg1960, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
	if (lpTransCommand->WParam == 2000)
		wsprintf(szBuff, msg2000, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
	if (lpTransCommand->WParam == 2100)
	{
		wsprintf(szBuff, msg2100, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
		lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->szAccountName, 0x7FFFFFFF);
	}
	if (lpTransCommand->WParam == 2110)
		wsprintf(szBuff, msg2110, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
	if (lpTransCommand->WParam == 2120)
		wsprintf(szBuff, msg2120, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
	if (lpTransCommand->WParam == 2300)
		wsprintf(szBuff, msg2300, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
	if (lpTransCommand->WParam == 2400)
		wsprintf(szBuff, msg2400, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
	if (lpTransCommand->WParam == 2700)
		wsprintf(szBuff, msg2700, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
	if (lpTransCommand->WParam == 2800)
		wsprintf(szBuff, msg2800, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
	if (lpTransCommand->WParam == 4000)
		wsprintf(szBuff, msg4000, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
	if (lpTransCommand->WParam == 4100)
		wsprintf(szBuff, msg4100, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
	if (lpTransCommand->WParam == 5000)
		wsprintf(szBuff, msg5000, st.wHour, st.wMinute, st.wSecond, lpTransCommand->LParam, lpTransCommand->SParam);
	if (lpTransCommand->WParam == 5100)
		wsprintf(szBuff, msg5100, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->sCharacterData.szName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
	if (lpTransCommand->WParam == 5200)
		wsprintf(szBuff, msg5200, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->SParam, lpTransCommand->LParam);
	if (lpTransCommand->WParam == 6000)
	{
		wsprintf(szBuff, msg6000, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->SParam, lpTransCommand->LParam);
		lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->szAccountName, 1000 * 60 * 60 * 1);
	}
	if (lpTransCommand->WParam == 6100)
		wsprintf(szBuff, msg6100, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
	if (lpTransCommand->WParam == 6200)
	{
		wsprintf(szBuff, msg6200, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
		if (lpPlayInfo->BlockTime < 1000 * 60 * 10)
			lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->szAccountName, 1000 * 60 * 10);
	}
	if (lpTransCommand->WParam == 6500)
		wsprintf(szBuff, msg6500, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
	if (lpTransCommand->WParam == 6510)
		wsprintf(szBuff, msg6510, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);

	if (lpTransCommand->WParam == 6600)
	{
		wsprintf(szBuff, msg6600, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
		lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->szAccountName, 0x7FFFFFFF);
	}
	if (lpTransCommand->WParam == 6610)
		wsprintf(szBuff, msg6610, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
	if (lpTransCommand->WParam == 6611)
	{
		wsprintf(szBuff, msg6611, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
		if (!lpPlayInfo->BlockTime)
			lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->szAccountName, 1000 * 60 * 30);
	}
	if (lpTransCommand->WParam == 6612)
	{
		wsprintf(szBuff, msg6612, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
		if (!lpPlayInfo->BlockTime)
			lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->szAccountName, 1000 * 60 * 30);
	}
	if (lpTransCommand->WParam == 6620)
	{
		wsprintf(szBuff, msg6620, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
		if (!lpPlayInfo->BlockTime)
			lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->szAccountName, 1000 * 60 * 60);
	}
	if (lpTransCommand->WParam == 6630)
		wsprintf(szBuff, msg6630, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
	if (lpTransCommand->WParam == 6800)
	{
		wsprintf(szBuff, msg6800, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
		if (rsServerConfig.ItemCodeOut > 0)
		{
			if ((lpTransCommand->LParam&sinITEM_MASK1) < (sinPM1&sinITEM_MASK1))
				lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->szAccountName, 0x7FFFFFFF);
			lpPlayInfo->dwTime_Disconnect = 1;
		}
	}
	if (lpTransCommand->WParam == 6810)
	{
		wsprintf(szBuff, msg6810, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
		if (rsServerConfig.ItemCodeOut > 1)
		{
			lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->szAccountName, 1000 * 60 * 60 * 24);
			SERVERNET->DisconnectUser(lpPlayInfo->pcSocketData);
		}
	}
	if (lpTransCommand->WParam == 6900)
	{
		wsprintf(szBuff, msg6900, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
		lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->szAccountName, 0x7FFFFFFF);

	}
	if (lpTransCommand->WParam == 6910)
		wsprintf(szBuff, msg6910, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, (lpTransCommand->SParam & 0xFFFF), (lpTransCommand->SParam >> 16), lpTransCommand->EParam);
	if (lpTransCommand->WParam == 6920)
		wsprintf(szBuff, msg6920, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
	if (lpTransCommand->WParam == 7000)
		wsprintf(szBuff, msg7000, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
	if (lpTransCommand->WParam == 7010)
	{
		wsprintf(szBuff, msg7010, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
	}
	if (lpTransCommand->WParam == 7020)
		wsprintf(szBuff, msg7020, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
	if (lpTransCommand->WParam == 7030)
		wsprintf(szBuff, msg7030, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
	if (lpTransCommand->WParam == 7100)
		wsprintf(szBuff, msg7100, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
	if (lpTransCommand->WParam == 7110)
	{
		if (lpPlayInfo->WarningCount > 10 + (rand() % 10))return FALSE;
		wsprintf(szBuff, msg7110, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
		lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->szAccountName, 1000 * 60 * 60);
	}
	if (lpTransCommand->WParam == 7120)
	{
		wsprintf(szBuff, msg7120, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
		lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->szAccountName, 0x7FFFFFFF);
		lpPlayInfo->dwDisconnectTime = 30000;
	}
	if (lpTransCommand->WParam == 7130)
		wsprintf(szBuff, msg7130, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
	if (lpTransCommand->WParam == 7140)
	{
		wsprintf(szBuff, msg7140, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->pcSocketData->szIP);
		rsAddBackListID(lpPlayInfo->szAccountName, 1000 * 60 * 16);
		return FALSE;
	}
	if (lpTransCommand->WParam == 7150)
		wsprintf(szBuff, msg7150, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
	if (lpTransCommand->WParam == 7160)
		wsprintf(szBuff, msg7160, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
	if (lpTransCommand->WParam == 8000)
		wsprintf(szBuff, msg8000, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->WxParam, lpTransCommand->LxParam, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
	if (lpTransCommand->WParam == 8010)
		wsprintf(szBuff, msg8010, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
	if (lpTransCommand->WParam == 8020)
		wsprintf(szBuff, msg8020, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
	if (lpTransCommand->WParam == 8030)
		wsprintf(szBuff, msg8030, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
	if (lpTransCommand->WParam == 8040)
	{
		if (lpPlayInfo->sCharacterData.iLevel >= 21)
		{
			lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->szAccountName, 0x7FFFFFFF);
			lpPlayInfo->dwDisconnectTime = SERVER_GAMETIME + 3 * 60 * 1000;
		}
		if (lpPlayInfo->WarningCount > 10) return FALSE;
		wsprintf(szBuff, msg8040, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
	}
	if (lpTransCommand->WParam == 8050)
	{
		wsprintf(szBuff, msg8050, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
	}
	if (lpTransCommand->WParam == 8060)
		wsprintf(szBuff, msg8060, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
	if (lpTransCommand->WParam == 8070)
		wsprintf(szBuff, msg8070, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->WxParam, lpTransCommand->LxParam, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
	if (lpTransCommand->WParam == 8080)
		wsprintf(szBuff, msg8080, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
	if (lpTransCommand->WParam == 8100)
	{
		wsprintf(szBuff, msg8100, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam);
		if (lpTransCommand->LParam >= 200 && lpPlayInfo->WarningCount > 4)
			rsSend_BadPlayerToGameServer(lpPlayInfo, 1);
	}
	if (lpTransCommand->WParam == 8102)
		wsprintf(szBuff, msg8102, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
	if (lpTransCommand->WParam == 8110)
		wsprintf(szBuff, msg8110, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
	if (lpTransCommand->WParam == 8120)
		wsprintf(szBuff, msg8120, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
	if (lpTransCommand->WParam == 8130)
		wsprintf(szBuff, msg8130, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
	if (lpTransCommand->WParam == 8140)
		wsprintf(szBuff, msg8140, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
	if (lpTransCommand->WParam == 8200)
		wsprintf(szBuff, msg8200, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
	if (lpTransCommand->WParam == 8210)
		wsprintf(szBuff, msg8210, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam, lpTransCommand->SxParam, lpTransCommand->ExParam);
	if (lpTransCommand->WParam == 8300)
		wsprintf(szBuff, msg8300, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam);
	if (lpTransCommand->WParam == 8400)
		wsprintf(szBuff, msg8400, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
	if (lpTransCommand->WParam == 8500)
		wsprintf(szBuff, msg8500, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
	if (lpTransCommand->WParam == 8510)
		wsprintf(szBuff, msg8510, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->WxParam, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam, lpTransCommand->LxParam, lpTransCommand->SxParam, lpTransCommand->ExParam);
	if (lpTransCommand->WParam == 8520)
		wsprintf(szBuff, msg8520, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam);
	if (lpTransCommand->WParam == 8530)
		wsprintf(szBuff, msg8530, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam);
	if (lpTransCommand->WParam == 8540)
	{
		wsprintf(szBuff, msg8540, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
		SERVERNET->DisconnectUser(lpPlayInfo->pcSocketData);
	}
	if (lpTransCommand->WParam == 8550)
	{
		if (lpPlayInfo->WarningCount > 30) return FALSE;
		wsprintf(szBuff, msg8550, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
	}
	if (lpTransCommand->WParam == 8560)
		wsprintf(szBuff, msg8560, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
	if (lpTransCommand->WParam == 8570)
	{
		wsprintf(szBuff, msg8570, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
	}
	if (lpTransCommand->WParam == 8580)
	{
		wsprintf(szBuff, msg8580, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
	}
	if (lpTransCommand->WParam == 8600)
	{
		if (lpPlayInfo->WarningCount > 20 + (rand() % 10))
			return FALSE;
		wsprintf(szBuff, msg8600, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
	}
	if (lpTransCommand->WParam == 8700)
		wsprintf(szBuff, msg8700, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
	if (lpTransCommand->WParam == 8710)
		wsprintf(szBuff, msg8710, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
	if (lpTransCommand->WParam == 8720)
		wsprintf(szBuff, msg8720, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
	if (lpTransCommand->WParam == 8730)
		wsprintf(szBuff, msg8730, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
	if (lpTransCommand->WParam == 8800)
		wsprintf(szBuff, msg8800, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
	if (lpTransCommand->WParam == 8810)
		wsprintf(szBuff, msg8810, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
	if (lpTransCommand->WParam == 8820)
		wsprintf(szBuff, msg8820, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
	if (lpTransCommand->WParam == 8830)
		wsprintf(szBuff, msg8830, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
	if (lpTransCommand->WParam == 8840)
		wsprintf(szBuff, msg8840, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->WxParam, lpTransCommand->LxParam, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
	if (lpTransCommand->WParam == 8850)
		wsprintf(szBuff, msg8850, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
	if (lpTransCommand->WParam == 8860)
		wsprintf(szBuff, msg8860, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->WxParam, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam, lpTransCommand->LxParam);
	if (lpTransCommand->WParam == 8870)
		wsprintf(szBuff, msg8870, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
	if (lpTransCommand->WParam == 8880)
	{
		wsprintf(szBuff, msg8880, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
	}
	if (lpTransCommand->WParam == 8890)
	{
		wsprintf(szBuff, msg8890, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
		lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->szAccountName, 0x7FFFFFFF);
	}
	if (lpTransCommand->WParam == 8900)
		wsprintf(szBuff, msg8900, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
	if (lpTransCommand->WParam == 99000)
		wsprintf(szBuff, "%d:%d:%d - ID:( %s ) / Name:( %s ) / IP ( %s ) Item Mixing Error ( %d )( %d )\r\n", st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
	if (lpTransCommand->WParam == 10000)
		wsprintf(szBuff, msg10000, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->SParam, lpTransCommand->LParam);
	if (lpTransCommand->WParam == 10001)
		wsprintf(szBuff, msg10001, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->SParam, lpTransCommand->LParam);
	if (lpTransCommand->WParam == 10002)
		wsprintf(szBuff, msg10002, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->SParam, lpTransCommand->LParam);
	if (lpTransCommand->WParam == 10003)
		wsprintf(szBuff, msg10003, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->SParam, lpTransCommand->LParam);
	if (lpTransCommand->WParam == 10005)
		wsprintf(szBuff, msg10005, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->SParam, lpTransCommand->LParam);
	if (lpTransCommand->WParam == 10006)
		wsprintf(szBuff, msg10006, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->SParam, lpTransCommand->LParam);
	if (lpTransCommand->WParam == 10007)
		wsprintf(szBuff, msg10007, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->pcSocketData->szIP, lpTransCommand->SParam, lpTransCommand->LParam);
	if (lpTransCommand->WParam == 10010)
		wsprintf(szBuff, msg10010, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam);
	if (lpTransCommand->WParam == 10020)
		wsprintf(szBuff, msg10020, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
	if (lpTransCommand->WParam == 11000)
		wsprintf(szBuff, msg11000, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP);
	if (lpTransCommand->WParam == 21000)
		wsprintf(szBuff, msg21000, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->LParam, lpTransCommand->SParam);
	if (lpTransCommand->WParam < 1000)
	{
		char szTemp[256];
		wsprintf(szTemp, "logfile [ %d %d %d %d ]\r\n", lpTransCommand->WParam, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
		Record_TempLogFile(szTemp);
		if (LoginServer)
			wsprintf(szTemp, "DebugLog - LastMsg( %d ) LastUserID( %s ) LastUserName( %s ) DebugCount( %d )\r\n", dwServer_DebugMessage, szServer_DebugLastUserID, szServer_DebugLastUserName, Server_DebugCount);
		Record_TempLogFile(szTemp);
		if (lpTransCommand->WParam != 100)
		{
			wsprintf(szBuff, msgHack, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->WParam);
			if (lpTransCommand->WParam == 82 || lpTransCommand->WParam == 83 || lpTransCommand->WParam == 5)
			{
				lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->szAccountName, 0x7FFFFFFF);
				lpPlayInfo->dwDisconnectTime = 2000;
			}
			if (lpTransCommand->WParam == 55 || lpTransCommand->WParam == 54)
			{
				if (lpPlayInfo->iGameLevel >= GAMELEVEL_Two)
					return FALSE;
				if (lpPlayInfo->WarningCount > 12 && !lpPlayInfo->dwDisconnectTime)
					lpPlayInfo->dwDisconnectTime = 2000;
			}
		}
		else
		{
			wsprintf(szBuff, msgHack100, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpTransCommand->WParam, lpTransCommand->SParam, lpTransCommand->LParam, lpTransCommand->EParam);
			if (lpPlayInfo->BlockTime && lpTransCommand->LParam >= 140)
			{
				lpPlayInfo->BadPlayer = 2;
				smTransCommand.code = smTRANSCODE_BAD_PLAYER;
				smTransCommand.size = sizeof(smTRANS_COMMAND);
				smTransCommand.WParam = 2;
				smTransCommand.LParam = 0;
				smTransCommand.SParam = 0;
				smTransCommand.EParam = 0;
				rsSendGameServer(lpPlayInfo, &smTransCommand);
			}
		}
		if (!lpPlayInfo->BlockTime && lpTransCommand->WParam != 99)
			lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->szAccountName, 1000 * 60 * 21);

		Record_TempLogFile(szBuff);
		Record_TempLogFile(szFileName);
		Record_TempLogFile(HackLogDirectory);
	}

LogSkip:

	if (lpTransCommand->WParam == 50000)
		wsprintf(szBuff, "%d:%d:%d >**** Timer Overflow **** - ( %d / %d )\r\n", st.wHour, st.wMinute, st.wSecond, lpTransCommand->LParam, lpTransCommand->SParam);
	if (lpTransCommand->WParam == 50010)
		wsprintf(szBuff, "%d:%d:%d >**** Shutdown Service **** - ( %d / %d )\r\n", st.wHour, st.wMinute, st.wSecond, lpTransCommand->LParam, lpTransCommand->SParam);
	if (lpTransCommand->WParam == 50020)
		wsprintf(szBuff, "%d:%d:%d >**** Starting Service **** - ( %d / %d )\r\n", st.wHour, st.wMinute, st.wSecond, lpTransCommand->LParam, lpTransCommand->SParam);
	if (lpTransCommand->WParam == 50030)
		wsprintf(szBuff, "%d:%d:%d >**** Closed Service **** - ( %d / %d )\r\n", st.wHour, st.wMinute, st.wSecond, lpTransCommand->LParam, lpTransCommand->SParam);
#endif

	CreateDirectory(HackLogDirectory, NULL);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	if (lpPlayInfo)
		lpPlayInfo->WarningCount++;

	return TRUE;
}

//µð¹ö±× Á¢¼Ó À¯Àú ±â·Ï ÆÄÀÏ·Î ³²±è
int RecordDebugPlayLogFile(User *lpPlayInfo)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	if (!lpPlayInfo->pcSocketData) return FALSE;

	GetLocalTime(&st);
	wsprintf(szFileName, filenameDebugLogin, DebugLogDirectory, st.wMonth, st.wDay);

	if (lpPlayInfo->szAccountName[0]) {
		wsprintf(szBuff, msgDebugloginID,
			st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName,
			lpPlayInfo->pcSocketData->szIP, lpPlayInfo->iGameLevel);
	}
	else {
		wsprintf(szBuff, msgDebugloginIP,
			st.wHour, st.wMinute, st.wSecond, lpPlayInfo->sCharacterData.szName,
			lpPlayInfo->pcSocketData->szIP, lpPlayInfo->iGameLevel);
	}

	CreateDirectory(DebugLogDirectory, NULL);			//µð·ºÅä¸® »ý¼º

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}


//Àü¾÷ÀÚ ±â·Ï ÆÄÀÏ·Î ³²±è
int RecordJobChanger(User *lpPlayInfo)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	if (!lpPlayInfo->pcSocketData) return FALSE;

	GetLocalTime(&st);
	wsprintf(szFileName, "LogFile\\(Àü¾÷)%d¿ù%dÀÏ.log", st.wMonth, st.wDay);

	wsprintf(szBuff, "ID( %s ) Name( %s ) IP( %s ) - Á÷¾÷( %d )/Àü¾÷( %d )/·¹º§( %d )\r\n",
		lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP,
		lpPlayInfo->sCharacterData.iClass, lpPlayInfo->sCharacterData.iRank, lpPlayInfo->sCharacterData.iLevel);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}

//±âÅ¸ ÀÓ½Ã ±â·Ï ÆÄÀÏ·Î ³²±è
int Record_TempLogFile(char *szMessage)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	int len;
	char	szFileName[128];
	char	szBuff[256];

	GetLocalTime(&st);
	wsprintf(szFileName, "LogFile\\(Temp)%d-%d.log", st.wMonth, st.wDay);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;


	wsprintf(szBuff, "%d:%d:%d - %s", st.wHour, st.wMinute, st.wSecond, szMessage);
	len = lstrlen(szBuff);
	if (szBuff[len - 1] != '\n') {
		szBuff[len] = '\r';
		szBuff[len + 1] = '\n';
		len += 2;
	}

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, len, &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}

//ºô¸µ Á¢¼Ó Á¾·á ±â·Ï ÆÄÀÏ·Î ³²±è
int Record_BillingLogFile(User *lpPlayInfo, DWORD wParam, DWORD lParam, DWORD sParam, DWORD eParam)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	if (!lpPlayInfo || !lpPlayInfo->pcSocketData) return FALSE;

	lpPlayInfo->szAccountName[31] = 0; lpPlayInfo->szCharacterName[31] = 0;

	GetLocalTime(&st);
	wsprintf(szFileName, "LogFile\\(Billing)%d-%d.log", st.wMonth, st.wDay);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	wsprintf(szBuff, "%d:%d:%d - ID( %s ) Name( %s ) IP( %s ) - DisuseDay(%d) dwPeriodTime(%d) tTime(%d) PcUse(%d)\r\n", st.wHour, st.wMinute, st.wSecond,
		lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, wParam, lParam, sParam, eParam);

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}

//Ä³¸¯ÅÍ »ç¸Á ±â·Ï ÆÄÀÏ·Î ³²±è
int Record_DeadUser(User *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	if (!lpPlayInfo->pcSocketData || lpPlayInfo->sCharacterData.iLevel < 30)
		return FALSE;

	GetLocalTime(&st);
	wsprintf(szFileName, "LogFile\\(Death)%d-%d.log", st.wMonth, st.wDay);

	wsprintf(szBuff, "%d:%d:%d - ID( %s ) Name( %s ) IP( %s ) - Level( %d )/Area( %d )\r\n",
		st.wHour, st.wMinute, st.wSecond,
		lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP,
		lpPlayInfo->sCharacterData.iLevel, lpPlayInfo->iMapID);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}


//¾ÆÀÌÅÛ ¹Í½º ±â·Ï
int RecordMixItem(User *lpPlayInfo, Item *lpSrcItem, Item *lpMixItem)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	if (!lpPlayInfo->pcSocketData) return FALSE;

	GetLocalTime(&st);
	wsprintf(szFileName, filenameMixItem, HackLogDirectory, st.wMonth, st.wDay);

	wsprintf(szBuff, msgMixItem,
		st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName,
		lpPlayInfo->pcSocketData->szIP, lpSrcItem->szItemName,
		lpSrcItem->iChk1, lpSrcItem->iChk2, lpSrcItem->dwTime,
		lpMixItem->iChk1, lpMixItem->iChk2, lpMixItem->dwTime);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}

//¾ÆÀÌÅÛ ¿¡ÀÌÂ¡ ±â·Ï
int RecordAgingItem(User *lpPlayInfo, Item *lpSrcItem, Item *lpMixItem, int Mode)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];
	char	*lpMsg;

	if (!lpPlayInfo->pcSocketData)
		return FALSE;

	GetLocalTime(&st);
	wsprintf(szFileName, filenameAgingItem, HackLogDirectory, st.wMonth, st.wDay);

	if (lpMixItem)
	{
		if (!Mode)
			lpMsg = msgAgingItem;
		else
			lpMsg = msgAgingUpItem;

		wsprintf(szBuff, lpMsg,
			st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName,
			lpPlayInfo->pcSocketData->szIP, lpSrcItem->szItemName, lpMixItem->sAgeLevel,
			lpSrcItem->iChk1, lpSrcItem->iChk2, lpSrcItem->dwTime,
			lpMixItem->iChk1, lpMixItem->iChk2, lpMixItem->dwTime);

	}
	else
	{
		wsprintf(szBuff, msgAgingFailItem,
			st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName,
			lpPlayInfo->pcSocketData->szIP, lpSrcItem->szItemName, lpSrcItem->sAgeLevel,
			lpSrcItem->iChk1, lpSrcItem->iChk2, lpSrcItem->dwTime);
	}

	//CreateDirectory( DebugLogDirectory , NULL );			//µð·ºÅä¸® »ý¼º

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}


char *szRecordCollectDirectory = "CollMoney";

int RecordCollectMoney(User *lpPlayInfo, int Money)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];
	int		TotalMoney = 0;
	FILE	*fp;

	CreateDirectory(szRecordCollectDirectory, NULL);
	GetLocalTime(&st);

	wsprintf(szFileName, filenameCollectMoney, szRecordCollectDirectory, st.wMonth, st.wDay);

	fopen_s(&fp,szFileName, "rb");
	if (fp)
	{
		fread(szBuff, 256, 1, fp);
		fclose(fp);
		TotalMoney = atoi(szBuff);
	}

	TotalMoney += Money;

	fopen_s(&fp,szFileName, "wb");
	if (fp)
	{
		wsprintf(szBuff, "%d", TotalMoney);
		fwrite(szBuff, lstrlen(szBuff) + 1, 1, fp);
		fclose(fp);
	}

	wsprintf(szFileName, filenameCollectMoney, szRecordCollectDirectory, st.wMonth, st.wDay);

	wsprintf(szBuff, msgKindPeople,
		st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName,
		lpPlayInfo->pcSocketData->szIP, Money, TotalMoney);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}


//µ· ±â·Ï ÆÄÀÏ·Î ³²±è
int RecordHackLogMoney(CharacterData *lpCharInfo)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];


	if (!lpCharInfo) return FALSE;

	GetLocalTime(&st);
	wsprintf(szFileName, filenameHackLogMoney, HackLogDirectory, st.wMonth, st.wDay);

	CreateDirectory(HackLogDirectory, NULL);			//µð·ºÅä¸® »ý¼º

	wsprintf(szBuff, msgHackMoney,
		st.wHour, st.wMinute, st.wSecond,
		lpCharInfo->szName, lpCharInfo->iLevel, lpCharInfo->iGold);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);


	return TRUE;


}

//°í°¡ÀÇ ¾ÆÀÌÅÛ ÀÔ¼ö ±â·Ï ÆÄÀÏ·Î ³²±è
int RecordGetHighItem(User *lpPlayInfo, MapLoot *lpStgItem)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	if (!lpPlayInfo || !lpStgItem) return FALSE;
	if (!lpStgItem->bExclusive) return FALSE;

	GetLocalTime(&st);
	wsprintf(szFileName, filenameGetHighItem, HackLogDirectory, st.wMonth, st.wDay);

	CreateDirectory(HackLogDirectory, NULL);			//µð·ºÅä¸® »ý¼º

	wsprintf(szBuff, msgHighItem,
		st.wHour, st.wMinute, st.wSecond,
		lpPlayInfo->sCharacterData.szName, lpPlayInfo->sCharacterData.iLevel,
		lpStgItem->sLootItem.sItem.szItemName,
		lpStgItem->sLootItem.sItem.sItemID,
		lpStgItem->sLootItem.sItem.iChk1,
		lpStgItem->sLootItem.sItem.iChk2,
		lpStgItem->sLootItem.sItem.eSpecialization,
		lpStgItem->bExclusive);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}

//Ä³¸¯ÅÍ Á¦°Å ±â·Ï ÆÄÀÏ·Î ³²±è
int RecordDeleteCharacterError(char *szID, char *szName)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	GetLocalTime(&st);
	wsprintf(szFileName, filenameDeleteCharactererror, LogDirectory, st.wMonth, st.wDay);

	CreateDirectory(LogDirectory, NULL);			//µð·ºÅä¸® »ý¼º

	wsprintf(szBuff, msgCharDelete2,
		st.wHour, st.wMinute, st.wSecond,
		szID, szName);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}



//ºí·¢ À¯Àú ±â·Ï ÆÄÀÏ·Î ³²±è
int RecordBlackUser(char *szID, DWORD dwTime)
{
#ifdef _W_SERVER

	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	if (!szID) return FALSE;


	GetLocalTime(&st);
	wsprintf(szFileName, filenameBlackUser, LogDirectory, st.wMonth, st.wDay);

	CreateDirectory(LogDirectory, NULL);			//µð·ºÅä¸® »ý¼º

	wsprintf(szBuff, msgBlackUser,
		st.wHour, st.wMinute, st.wSecond,
		szID, dwTime / (1000 * 60));

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

#endif

	return TRUE;
}

// pluto Á¦·Ã ¾ÆÀÌÅÛ ±â·Ï
int RecordSmeltingItem(User *lpPlayInfo, Item *lpSmeltingItem)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	if (!lpPlayInfo->pcSocketData)
	{
		return FALSE;
	}

	GetLocalTime(&st);
	wsprintf(szFileName, filenameSmeltingItem, HackLogDirectory, st.wMonth, st.wDay);

	wsprintf(szBuff, msgSmeltingItem,
		st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName,
		lpPlayInfo->pcSocketData->szIP, lpSmeltingItem->szItemName,
		lpSmeltingItem->iChk1, lpSmeltingItem->iChk2, lpSmeltingItem->dwTime);


	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}
// pluto Á¦ÀÛ ¾ÆÀÌÅÛ ±â·Ï
int RecordManufactureItem(User *lpPlayInfo, Item *lpManufactureItem)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	if (!lpPlayInfo->pcSocketData)
	{
		return FALSE;
	}

	GetLocalTime(&st);
	wsprintf(szFileName, filenameManufactureItem, HackLogDirectory, st.wMonth, st.wDay);

	wsprintf(szBuff, msgManufactureItem,
		st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName,
		lpPlayInfo->pcSocketData->szIP, lpManufactureItem->szItemName,
		lpManufactureItem->iChk1, lpManufactureItem->iChk2, lpManufactureItem->dwTime);


	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}
// ¼ÇÂ¼»Ø¸´×°±¸ÈÕÖ¾
int RecordMixtureResetItem(User *lpPlayInfo, Item *lpMixtureResetItem)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	if (!lpPlayInfo->pcSocketData)
		return FALSE;

	GetLocalTime(&st);
	wsprintf(szFileName, filenameMixtureResetItem, HackLogDirectory, st.wMonth, st.wDay);

	wsprintf(szBuff, msgMixtureResetItem,
		st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName,
		lpPlayInfo->pcSocketData->szIP, lpMixtureResetItem->szItemName,
		lpMixtureResetItem->iChk1, lpMixtureResetItem->iChk2, lpMixtureResetItem->dwTime);


	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}
// ¼ÇÂ¼Element×°±¸µÄÈÕÖ¾
int RecordElementItem(User *lpPlayInfo, Item *lpElementItem)
{
	HANDLE		hFile;
	DWORD		dwAcess;
	SYSTEMTIME	st;
	char		szFileName[128];
	char		szBuffer[256];

	if (lpPlayInfo->pcSocketData)
	{
		GetLocalTime(&st);
		wsprintf(szFileName, filenameElementItem, HackLogDirectory, st.wMonth, st.wDay);
		wsprintf(szBuffer, msgMixtureResetItem, st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, lpElementItem->szItemName, lpElementItem->iChk1, lpElementItem->iChk2, lpElementItem->dwTime);
		hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile != INVALID_HANDLE_VALUE)
		{
			int FileLen = GetFileSize(hFile, NULL);
			SetFilePointer(hFile, FileLen, NULL, FILE_BEGIN);
			WriteFile(hFile, szBuffer, lstrlen(szBuffer), &dwAcess, NULL);
			CloseHandle(hFile);
			return TRUE;
		}
	}
	return FALSE;
}


// Àåº° - ¿µÈ­ Ç÷Åõ
int RecordMovieBloodyBattleItem(User *lpPlayInfo, Item *lpMovieBloodyBattleItem)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	if (!lpPlayInfo->pcSocketData)
		return FALSE;

	CreateDirectory(EventLogDirectory, NULL);

	GetLocalTime(&st);
	wsprintf(szFileName, filenameMovieBloodyBattleItem, EventLogDirectory, st.wMonth, st.wDay);

	wsprintf(szBuff, MovieBloodyBattleLog,
		st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName);


	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}

#ifdef _W_SERVER
char	*szBlackUserDir = "BlackUser";
char	*szEverBlockDir = "BlockUser";
#else
char	*szBlackUserDir = "WhiteBird";
char	*szEverBlockDir = "StoneBird";
#endif



//À¯Àú¸¦ ¿µ±¸ ºí·°
int rsAddBlockUserFile(char *szID, char *szLog)
{
	char szBuff[256];
	FILE *fp;

	if (!rsServerConfig.ForeverBlockMode)
		return FALSE;

	CreateDirectory(szEverBlockDir, NULL);

	wsprintf(szBuff, "%s\\%s.fev", szEverBlockDir, szID);

	fopen_s(&fp,szBuff, "wb");
	if (fp)
	{
		fwrite(szLog, lstrlen(szLog), 1, fp);
		fclose(fp);
	}

	return TRUE;
}
int	rsCheckBlockUserFile(char *szID)
{
	HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;
	char szBuff[256];

	wsprintf(szBuff, "%s\\%s.fev", szEverBlockDir, szID);

	hFindHandle = FindFirstFile(szBuff, &fd);
	if (hFindHandle == INVALID_HANDLE_VALUE)
		return FALSE;

	FindClose(hFindHandle);
	return TRUE;
}
int ResetBlackUserFiles()
{
	HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;
	char szBuff[256];

	wsprintf(szBuff, "%s\\*.bur", szBlackUserDir);
	CreateDirectory(szBlackUserDir, NULL);

	hFindHandle = FindFirstFile(szBuff, &fd);
	if (hFindHandle == INVALID_HANDLE_VALUE)
	{
		FindClose(hFindHandle);
		return 0;
	}
	while (1)
	{
		wsprintf(szBuff, "%s\\%s", szBlackUserDir, fd.cFileName);
		DeleteFile(szBuff);
		if (FindNextFile(hFindHandle, &fd) == FALSE) break;
	}
	FindClose(hFindHandle);


	return TRUE;
}
int ResetBlackUserFiles(char *szID, DWORD dwTime)
{
	char szBuff[256];
	char szBuff2[256];
	FILE *fp;
	SYSTEMTIME	st;

	wsprintf(szBuff, "%s\\%s.bur", szBlackUserDir, szID);

	if (dwTime)
	{
		GetLocalTime(&st);
		wsprintf(szBuff2, msgBlackUser, st.wHour, st.wMinute, st.wSecond, szID, dwTime / (1000 * 60));
		fopen_s(&fp,szBuff, "wb");
		if (fp)
		{
			fwrite(szBuff2, lstrlen(szBuff2), 1, fp);
			fclose(fp);
		}
	}
	else
		DeleteFile(szBuff);

	return TRUE;
}
int FindBlackUserFile(char *szID)
{
	HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;
	char szBuff[256];

	wsprintf(szBuff, "%s\\%s.bur", szBlackUserDir, szID);

	hFindHandle = FindFirstFile(szBuff, &fd);

	if (hFindHandle == INVALID_HANDLE_VALUE)
		return FALSE;

	FindClose(hFindHandle);
	return TRUE;
}

int rsCompareCharInfo(CharacterData *cSrc, CharacterData *cDest)
{








	return TRUE;
}

struct	srBLACK_LIST {
	char	szID[32];		//ID
	DWORD	dwFreeTime;		//¼³Á¤ ½Ã°£ (ÀÌ ½Ã°£ ÀÌÈÄ¿¡ Ç®¸² )
};

#define	srBLACK_LIST_MAX	400

//ºí·¢¸®½ºÆ® ¸í´Ü
srBLACK_LIST	srBlackList[srBLACK_LIST_MAX];
int	rsBlackListInit = 0;

//³ª»ÛÀÚµé ¸í´Ü µî·Ï
int rsAddBackListID(char *szID, DWORD dwTime)
{
	int cnt;
	DWORD	dwBloackTime;
	DWORD	dwFreeTime;

	if (!szID[0]) return FALSE;

	if (!rsBlackListInit) {
		//³ª»ÛÀÚµé ¸í´Ü ¸ðµÎ ÃÊ±âÈ­
		rsResetBackList();
	}

	dwBloackTime = dwTime;

	if (rsServerConfig.BlockLevel > 0) {
		dwBloackTime = dwTime / rsServerConfig.BlockLevel;
	}
	if (rsServerConfig.BlockLevel < 0) {
		dwBloackTime = dwTime * abs(rsServerConfig.BlockLevel);
	}

	if (rsServerConfig.BlockLevel_LogOut)
		return dwBloackTime;


	dwFreeTime = SERVER_GAMETIME + dwBloackTime;
	if (dwFreeTime < SERVER_GAMETIME) dwFreeTime = 0xFFFFFFFF;

	RecordBlackUser(szID, dwBloackTime);			//µî·Ï

	for (cnt = 0; cnt < srBLACK_LIST_MAX; cnt++) {
		if (srBlackList[cnt].szID[0] && lstrcmpi(srBlackList[cnt].szID, szID) == 0) {
			if (srBlackList[cnt].dwFreeTime < dwFreeTime) {
				srBlackList[cnt].dwFreeTime = dwFreeTime;

				//ºí·¢ À¯Àú ÆÄÀÏ µî·Ï
				ResetBlackUserFiles(szID, dwBloackTime);
			}
			return dwBloackTime;
		}
	}


	for (cnt = 0; cnt < srBLACK_LIST_MAX; cnt++) {
		if (!srBlackList[cnt].szID[0]) {
			lstrcpy(srBlackList[cnt].szID, szID);
			srBlackList[cnt].dwFreeTime = dwFreeTime;

			//ºí·¢ À¯Àú ÆÄÀÏ µî·Ï
			ResetBlackUserFiles(szID, dwBloackTime);

			return dwBloackTime;
		}
	}


	return FALSE;
}

//³ª»ÛÀÚµé ¸í´Ü È®ÀÎ
DWORD rsCheckBackListID(char *szID)
{
	int cnt;

	for (cnt = 0; cnt < srBLACK_LIST_MAX; cnt++) {

		if (srBlackList[cnt].szID[0]) {
			if (srBlackList[cnt].dwFreeTime < SERVER_GAMETIME) {
				//ºí·¢ À¯Àú ÆÄÀÏ »èÁ¦
				ResetBlackUserFiles(srBlackList[cnt].szID, 0);
				srBlackList[cnt].dwFreeTime = 0;
				srBlackList[cnt].szID[0] = 0;
			}
			else {
				if (lstrcmpi(srBlackList[cnt].szID, szID) == 0) {
					//¸í´Ü¿¡¼­ Ã£¾Ò´Ù

					//ºí·¢ À¯Àú ÆÄÀÏÀ» ÀÖ´ÂÁö È®ÀÎ
					if (FindBlackUserFile(szID) == TRUE) {
						return srBlackList[cnt].dwFreeTime;
					}

					//ºí·¢ À¯Àú ÇØÁ¦ ( ÆÄÀÏÀÌ »èÁ¦ µÇ¾úÀ½ )
					srBlackList[cnt].dwFreeTime = 0;
					srBlackList[cnt].szID[0] = 0;
					break;
				}
			}
		}
	}


	return NULL;
}

//³ª»ÛÀÚµé ¸í´Ü¿¡¼­ ÇØÁ¦
int rsFreekBackListID(char *szID)
{
	int cnt;

	for (cnt = 0; cnt < srBLACK_LIST_MAX; cnt++) {
		if (srBlackList[cnt].szID[0] && lstrcmpi(srBlackList[cnt].szID, szID) == 0) {
			//ºí·¢ À¯Àú ÆÄÀÏ »èÁ¦
			ResetBlackUserFiles(srBlackList[cnt].szID, 0);

			srBlackList[cnt].dwFreeTime = 0;
			srBlackList[cnt].szID[0] = 0;
			return TRUE;
		}
	}

	return FALSE;
}

//³ª»ÛÀÚµé ¸í´Ü ¸ðµÎ ÃÊ±âÈ­
int rsResetBackList()
{
	int cnt;

	for (cnt = 0; cnt < srBLACK_LIST_MAX; cnt++) {
		srBlackList[cnt].dwFreeTime = 0;
		srBlackList[cnt].szID[0] = 0;
	}

	//ºí·¢ À¯Àú ÆÄÀÏÀ» ¸ðµÎ ÃÊ±âÈ­
	ResetBlackUserFiles();

	rsBlackListInit = TRUE;

	return TRUE;
}

int rsShowBlackList(User *pcUser, char *szID)
{
	TRANS_CHATMESSAGE	TransChatMessage;
	int cnt;
	int dcnt;

	TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
	TransChatMessage.dwIP = 0;
	TransChatMessage.dwObjectSerial = 0;

	dcnt = 0;

	for (cnt = 0; cnt < srBLACK_LIST_MAX; cnt++) {
		if (srBlackList[cnt].szID[0]) {
			if (!szID[0] || lstrcmpi(szID, srBlackList[cnt].szID) == 0) {
				wsprintf(TransChatMessage.szMessage, "> ID ( %s ) / ( %d )Min.", srBlackList[cnt].szID, (srBlackList[cnt].dwFreeTime - SERVER_GAMETIME) / 60000);
				TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
				SENDPACKET(pcUser, &TransChatMessage);
				dcnt++;
			}
		}
	}

	wsprintf(TransChatMessage.szMessage, "> Total %d Users", dcnt);
	TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);

	SENDPACKET(pcUser, &TransChatMessage);

	return TRUE;
}



//IPÁÖ¼Ò µÚÁý±â
DWORD SwapIPCode(DWORD dwIP)
{
	BYTE	bIP[4];

	bIP[0] = (BYTE)(dwIP & 0xFF);
	bIP[1] = (BYTE)((dwIP >> 8) & 0xFF);
	bIP[2] = (BYTE)((dwIP >> 16) & 0xFF);
	bIP[3] = (BYTE)((dwIP >> 24) & 0xFF);

	return (bIP[0] << 24) | (bIP[1] << 16) | (bIP[2] << 8) | (bIP[3]);
}

//¾ÆÀÌÇÇ ÁÖ¼Ò¸¦ µÚÁý¾î¼­ º¯È¯
DWORD GetSwapIPCode(char *szIP)
{
	return SwapIPCode(inet_addr(szIP));
}

//Á¢±Ù ±ÝÁö IP È®ÀÎ
int	rsCheckDisableIP(DWORD dwUserIP)
{
	DWORD	dwIP;
	int		cnt;

	dwIP = SwapIPCode(dwUserIP);

	for (cnt = 0; cnt < rsServerConfig.DisableIP_Count; cnt++) {
		if (dwIP >= rsServerConfig.DisableIP[cnt][0] && dwIP <= rsServerConfig.DisableIP[cnt][1]) {
			return TRUE;
		}
	}

	return FALSE;
}

//Á¢±Ù Çã°¡ IP È®ÀÎ
int	rsCheckEnableIP(DWORD dwUserIP)
{
	DWORD	dwIP;
	int		cnt;

	dwIP = SwapIPCode(dwUserIP);

	for (cnt = 0; cnt < rsServerConfig.EnableIP_Count; cnt++) {
		if (dwIP >= rsServerConfig.EnableIP[cnt][0] && dwIP <= rsServerConfig.EnableIP[cnt][1]) {
			return TRUE;
		}
	}

	return FALSE;
}

//°ü¸®ÀÚ IP È®ÀÎ
int	rsCheckAdminIP(DWORD dwUserIP)
{
	DWORD	dwIP;
	int		cnt;

	dwIP = SwapIPCode(dwUserIP);

	for (cnt = 0; cnt < rsServerConfig.AdminIP_Count; cnt++) {
		if (dwIP >= rsServerConfig.AdminIP[cnt][0] && dwIP <= rsServerConfig.AdminIP[cnt][1]) {
			return TRUE;
		}
	}

	return FALSE;
}

//½Ã½ºÅÛ IP È®ÀÎ
int	rsCheckSystemIP(DWORD dwUserIP)
{
	DWORD	dwIP;
	int		cnt;

	dwIP = SwapIPCode(dwUserIP);

	for (cnt = 0; cnt < rsServerConfig.SystemIP_Count; cnt++) {
		if (dwIP >= rsServerConfig.SystemIP[cnt][0] && dwIP <= rsServerConfig.SystemIP[cnt][1]) {
			return TRUE;
		}
	}

	return FALSE;
}

//·Î±ä¼­¹ö IP È®ÀÎ
int	rsCheckLoginServerIP(DWORD dwUserIP)
{
	DWORD	dwIP;
	int		cnt;

	dwIP = SwapIPCode(dwUserIP);

	for (cnt = 0; cnt < rsServerConfig.LoginServerIP_Count; cnt++) {
		if (dwIP >= rsServerConfig.LoginServerIP[cnt][0] && dwIP <= rsServerConfig.LoginServerIP[cnt][1]) {
			return TRUE;
		}
	}

	return FALSE;
}
int	rsRecord_ItemLog(User *lpPlayInfo, DWORD dwItemCode, DWORD	dwHead, DWORD dwChkSum, int Flag)
{
	LogITEM	LogItem;

	if (!lpPlayInfo->pcSocketData)
		return FALSE;

	ZeroMemory(&LogItem, sizeof(LogITEM));

	if ((dwItemCode&sinITEM_MASK2) != sinGP1 &&
		(dwItemCode&sinITEM_MASK2) != sinQW1 && (dwItemCode&sinITEM_MASK2) != sinOR2 &&
		(dwItemCode&sinITEM_MASK2) != sinPZ1 && (dwItemCode&sinITEM_MASK2) != sinPZ2 &&
		(dwItemCode&sinITEM_MASK2) != sinSE1 && (dwItemCode&sinITEM_MASK2) != sinBI1 &&
		(dwItemCode&sinITEM_MASK2) != sinBI2 &&
		(dwItemCode&sinITEM_MASK2) != sinGF1 && (dwItemCode&sinITEM_MASK2) != sinBC1 &&
		(dwItemCode&sinITEM_MASK2) != sinPR1 && (dwItemCode&sinITEM_MASK2) != sinPR2 &&
		(dwItemCode&sinITEM_MASK2) != sinPR3 && (dwItemCode&sinITEM_MASK2) != sinPR4 &&
		(dwItemCode&sinITEM_MASK2) != sinWR1 && (dwItemCode&sinITEM_MASK2) != sinDR1 &&
		(dwItemCode&sinITEM_MASK2) != sinSP1)
	{

		if (dwItemCode == (sinGG1 | sin01))
		{
			if (dwHead < 10000)
				return FALSE;
		}
		else
		{
			if (dwItemCode >= sinPM1)
				return FALSE;
			if ((dwItemCode&sinITEM_MASK2) == sinOS1 || (dwItemCode&sinITEM_MASK2) == sinFO1)
			{
				if ((dwItemCode&sinITEM_MASK3) < sin05)
					return FALSE;
			}
			else
			{
				if ((dwItemCode&sinITEM_MASK3) < sin07)
					return FALSE;
			}
		}
	}

	LogItem.Flag = Flag;
	lstrcpy(LogItem.UserID, lpPlayInfo->szAccountName);
	lstrcpy(LogItem.CharName, lpPlayInfo->szCharacterName);
	LogItem.IP = lpPlayInfo->pcSocketData->lIP;
	LogItem.Item[0].dwCode = dwItemCode;
	LogItem.Item[0].dwINo[0] = dwHead;
	LogItem.Item[0].dwINo[1] = dwChkSum;
	LogItem.ItemCount = 1;
	LogItem.size = sizeof(LogITEM) - (sizeof(_LogITEM)*(32 - LogItem.ItemCount));

	return b_PushLogItemQue(1, LogItem.size, &LogItem);
}

//¾ÆÀÌÅÛ ·Î±× ÀÏ¹Ý ¾ÆÀÌÅÛ ( Ãâ/ÀÔ ±â·Ï )
int	rsRecord_ItemLog2(User *lpPlayInfo, DWORD dwItemCode, DWORD	dwHead, DWORD dwChkSum, int Flag)
{
	LogITEM	LogItem;

	ZeroMemory(&LogItem, sizeof(LogITEM));

	if (!lpPlayInfo->pcSocketData) return FALSE;

	LogItem.Flag = Flag;
	lstrcpy(LogItem.UserID, lpPlayInfo->szAccountName);
	lstrcpy(LogItem.CharName, lpPlayInfo->szCharacterName);
	LogItem.IP = lpPlayInfo->pcSocketData->lIP;
	LogItem.Item[0].dwCode = dwItemCode;
	LogItem.Item[0].dwINo[0] = dwHead;
	LogItem.Item[0].dwINo[1] = dwChkSum;
	LogItem.ItemCount = 1;
	LogItem.size = sizeof(LogITEM) - (sizeof(_LogITEM)*(32 - LogItem.ItemCount));	//±¸Á¶Ã¼ÀÇ »ç¿ëµÈ Å©±â

	//¾ÆÀÌÅÛ ·Î±× Å¥¿¡ µ¥ÀÌÅ¸ ³ÖÀ½
	return b_PushLogItemQue(1, LogItem.size, &LogItem);
}

int	rsRecord_ItemLog_Change(User *lpPlayInfo, DWORD dwItemCode, DWORD	dwHead, DWORD dwChkSum, DWORD dwItemCode2, DWORD	dwHead2, DWORD dwChkSum2, int Flag)
{
	LogITEM	LogItem;

	ZeroMemory(&LogItem, sizeof(LogITEM));

	if (!lpPlayInfo->pcSocketData)
		return FALSE;

	LogItem.Flag = Flag;
	lstrcpy(LogItem.UserID, lpPlayInfo->szAccountName);
	lstrcpy(LogItem.CharName, lpPlayInfo->szCharacterName);
	LogItem.IP = lpPlayInfo->pcSocketData->lIP;

	LogItem.Item[0].dwCode = dwItemCode;
	LogItem.Item[0].dwINo[0] = dwHead;
	LogItem.Item[0].dwINo[1] = dwChkSum;

	LogItem.Item[1].dwCode = dwItemCode2;
	LogItem.Item[1].dwINo[0] = dwHead2;
	LogItem.Item[1].dwINo[1] = dwChkSum2;

	LogItem.ItemCount = 2;
	LogItem.size = sizeof(LogITEM) - (sizeof(_LogITEM)*(32 - LogItem.ItemCount));

	return b_PushLogItemQue(1, LogItem.size, &LogItem);
}
int	rsRecord_ItemLost(User *lpPlayInfo, DWORD *lpItemCode, DWORD *lpHead, DWORD *lpChkSum, int Flag)
{
	LogITEM	LogItem;
	int cnt;

	ZeroMemory(&LogItem, sizeof(LogITEM));

	if (!lpPlayInfo->pcSocketData)
		return FALSE;

	LogItem.Flag = Flag;
	lstrcpy(LogItem.UserID, lpPlayInfo->szAccountName);
	lstrcpy(LogItem.CharName, lpPlayInfo->szCharacterName);
	LogItem.IP = lpPlayInfo->pcSocketData->lIP;

	LogItem.ItemCount = 0;
	for (cnt = 0; cnt < 12; cnt++)
	{
		if (lpItemCode[cnt])
		{
			LogItem.Item[LogItem.ItemCount].dwCode = lpItemCode[cnt];
			LogItem.Item[LogItem.ItemCount].dwINo[0] = lpHead[cnt];
			LogItem.Item[LogItem.ItemCount].dwINo[1] = lpChkSum[cnt];
			LogItem.ItemCount++;
		}
	}

	if (LogItem.ItemCount == 0)
		return FALSE;

	LogItem.size = sizeof(LogITEM) - (sizeof(_LogITEM)*(32 - LogItem.ItemCount));

	return b_PushLogItemQue(1, LogItem.size, &LogItem);
}
int	rsRecord_ItemLog_Trade(User *lpPlayInfo, User *lpPlayInfo2, TRANS_TRADE_ITEMKEY *lpTransTradeItemKey)
{

	LogITEM_TRADE	LogItem;
	int cnt;

	ZeroMemory(&LogItem, sizeof(LogITEM_TRADE));

	if (!lpPlayInfo->pcSocketData) return FALSE;
	if (!lpPlayInfo2->pcSocketData) return FALSE;

	LogItem.Flag = 8;
	lstrcpy(LogItem.UserID, lpPlayInfo->szAccountName);
	lstrcpy(LogItem.CharName, lpPlayInfo->szCharacterName);
	lstrcpy(LogItem.TUserID, lpPlayInfo2->szAccountName);
	lstrcpy(LogItem.TCharName, lpPlayInfo2->szCharacterName);
	LogItem.IP = lpPlayInfo->pcSocketData->lIP;
	LogItem.TIP = lpPlayInfo2->pcSocketData->lIP;

	if (lpTransTradeItemKey->Money > 0)
		LogItem.Money = lpTransTradeItemKey->Money - 193;
	else
		LogItem.Money = 0;

	LogItem.ItemCount = 0;

	for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++)
	{
		if (lpTransTradeItemKey->dwItemCode[cnt])
		{
			LogItem.Item[LogItem.ItemCount].dwCode = lpTransTradeItemKey->dwItemCode[cnt];
			LogItem.Item[LogItem.ItemCount].dwINo[0] = lpTransTradeItemKey->dwItemKey[cnt];
			LogItem.Item[LogItem.ItemCount].dwINo[1] = lpTransTradeItemKey->dwItemSum[cnt];
			LogItem.ItemCount++;
		}
	}
	LogItem.size = sizeof(LogITEM_TRADE) - (sizeof(_LogITEM)*(32 - LogItem.ItemCount));

	return b_PushLogItemQue(2, LogItem.size, &LogItem);
}

//¾ÆÀÌÅÛ ·Î±× °³ÀÎ»óÁ¡
int	rsRecord_ItemLog_MyShop(User *lpPlayInfo, User *lpPlayInfo2, DWORD dwItemCode, DWORD dwHead, DWORD dwChkSum, int Price)
{

	LogITEM_TRADE	LogItem;

	if (!lpPlayInfo->pcSocketData) return FALSE;
	if (!lpPlayInfo2->pcSocketData) return FALSE;

	ZeroMemory(&LogItem, sizeof(LogITEM_TRADE));
	LogItem.Flag = ITEMLOG_MYSHOP;
	lstrcpy(LogItem.UserID, lpPlayInfo->szAccountName);
	lstrcpy(LogItem.CharName, lpPlayInfo->szCharacterName);
	lstrcpy(LogItem.TUserID, lpPlayInfo2->szAccountName);
	lstrcpy(LogItem.TCharName, lpPlayInfo2->szCharacterName);
	LogItem.IP = lpPlayInfo->pcSocketData->lIP;
	LogItem.TIP = lpPlayInfo2->pcSocketData->lIP;

	LogItem.Money = Price;

	LogItem.size = sizeof(LogITEM_TRADE) - (sizeof(_LogITEM)*(32 - LogItem.ItemCount));	//±¸Á¶Ã¼ÀÇ »ç¿ëµÈ Å©±â

	//¾ÆÀÌÅÛ ·Î±× Å¥¿¡ µ¥ÀÌÅ¸ ³ÖÀ½
	b_PushLogItemQue(2, LogItem.size, &LogItem);


	ZeroMemory(&LogItem, sizeof(LogITEM_TRADE));
	LogItem.Flag = ITEMLOG_MYSHOP;
	lstrcpy(LogItem.UserID, lpPlayInfo2->szAccountName);
	lstrcpy(LogItem.CharName, lpPlayInfo2->szCharacterName);
	lstrcpy(LogItem.TUserID, lpPlayInfo->szAccountName);
	lstrcpy(LogItem.TCharName, lpPlayInfo->szCharacterName);
	LogItem.IP = lpPlayInfo2->pcSocketData->lIP;
	LogItem.TIP = lpPlayInfo->pcSocketData->lIP;

	LogItem.Item[0].dwCode = dwItemCode;
	LogItem.Item[0].dwINo[0] = dwHead;
	LogItem.Item[0].dwINo[1] = dwChkSum;
	LogItem.ItemCount = 1;

	LogItem.size = sizeof(LogITEM_TRADE) - (sizeof(_LogITEM)*(32 - LogItem.ItemCount));	//±¸Á¶Ã¼ÀÇ »ç¿ëµÈ Å©±â

	//¾ÆÀÌÅÛ ·Î±× Å¥¿¡ µ¥ÀÌÅ¸ ³ÖÀ½
	b_PushLogItemQue(2, LogItem.size, &LogItem);

	return TRUE;
}


//¾ÆÀÌÅÛ ·Î±× ÁõÁ¤ ¾ÆÀÌÅÛ
int	rsRecord_ItemLog_Post(User *lpPlayInfo, DWORD dwItemCode, DWORD	dwHead, DWORD dwChkSum, DWORD dwGCode, char *szTelNum, int Flag)
{
	LogGiftITEM	LogItem;

	if (!lpPlayInfo->pcSocketData) return FALSE;

	ZeroMemory(&LogItem, sizeof(LogGiftITEM));

	LogItem.Flag = Flag;
	lstrcpy(LogItem.UserID, lpPlayInfo->szAccountName);
	lstrcpy(LogItem.CharName, lpPlayInfo->szCharacterName);
	LogItem.IP = lpPlayInfo->pcSocketData->lIP;
	LogItem.Gitem.dwCode = dwItemCode;
	LogItem.Gitem.dwINo[0] = dwHead;
	LogItem.Gitem.dwINo[1] = dwChkSum;
	LogItem.GNo = dwGCode;
	LogItem.size = sizeof(LogGiftITEM);	//±¸Á¶Ã¼ÀÇ »ç¿ëµÈ Å©±â

	if (szTelNum && szTelNum[0]) {
		szTelNum[15] = 0;
		lstrcpy(LogItem.TEL, szTelNum);
	}

	//¾ÆÀÌÅÛ ·Î±× Å¥¿¡ µ¥ÀÌÅ¸ ³ÖÀ½
	return b_PushLogItemQue(3, LogItem.size, &LogItem);
}

// pluto Á¦·Ã ¾ÆÀÌÅÛ ·Î±×
int	rsRecord_SmeltingItemLog(User *lpPlayInfo, DWORD *lpItemCode, DWORD *lpHead, DWORD *lpChkSum, int Flag)
{
	LogITEM LogItem;
	int cnt;
	ZeroMemory(&LogItem, sizeof(LogITEM));

	if (!lpPlayInfo->pcSocketData) return FALSE;

	LogItem.Flag = Flag;
	lstrcpy(LogItem.UserID, lpPlayInfo->szAccountName);
	lstrcpy(LogItem.CharName, lpPlayInfo->szCharacterName);
	LogItem.IP = lpPlayInfo->pcSocketData->lIP;

	LogItem.ItemCount = 0;
	for (cnt = 0; cnt < 5; cnt++)
	{
		if (lpItemCode[cnt])
		{
			LogItem.Item[LogItem.ItemCount].dwCode = lpItemCode[cnt];
			LogItem.Item[LogItem.ItemCount].dwINo[0] = lpHead[cnt];
			LogItem.Item[LogItem.ItemCount].dwINo[1] = lpChkSum[cnt];
			LogItem.ItemCount++;
		}
	}

	if (LogItem.ItemCount == 0) return FALSE;
	LogItem.size = sizeof(LogITEM) - (sizeof(_LogITEM)*(32 - LogItem.ItemCount));

	//¾ÆÀÌÅÛ ·Î±× Å¥¿¡ µ¥ÀÌÅ¸ ³ÖÀ½
	return b_PushLogItemQue(1, LogItem.size, &LogItem);
}
// pluto Á¦ÀÛ ¾ÆÀÌÅÛ ·Î±×
int	rsRecord_ManufactureItemLog(User *lpPlayInfo, DWORD *lpItemCode, DWORD *lpHead, DWORD *lpChkSum, int Flag)
{
	LogITEM LogItem;
	int cnt;
	ZeroMemory(&LogItem, sizeof(LogITEM));

	if (!lpPlayInfo->pcSocketData) return FALSE;

	LogItem.Flag = Flag;
	lstrcpy(LogItem.UserID, lpPlayInfo->szAccountName);
	lstrcpy(LogItem.CharName, lpPlayInfo->szCharacterName);
	LogItem.IP = lpPlayInfo->pcSocketData->lIP;

	LogItem.ItemCount = 0;
	for (cnt = 0; cnt < 4; cnt++)
	{
		if (lpItemCode[cnt])
		{
			LogItem.Item[LogItem.ItemCount].dwCode = lpItemCode[cnt];
			LogItem.Item[LogItem.ItemCount].dwINo[0] = lpHead[cnt];
			LogItem.Item[LogItem.ItemCount].dwINo[1] = lpChkSum[cnt];
			LogItem.ItemCount++;
		}
	}

	if (LogItem.ItemCount == 0) return FALSE;
	LogItem.size = sizeof(LogITEM) - (sizeof(_LogITEM)*(32 - LogItem.ItemCount));

	//¾ÆÀÌÅÛ ·Î±× Å¥¿¡ µ¥ÀÌÅ¸ ³ÖÀ½
	return b_PushLogItemQue(1, LogItem.size, &LogItem);
}

// ¼®Áö¿ë - ¹Í½ºÃÄ ¸®¼Â ¾ÆÀÌÅÛ ·Î±×
int rsRecord_MixtureResetItemLog(User *lpPlayInfo, sMIXTURE_RESET_ITEM_SERVER *pMixtureResetItem_Server, int Flag)
{
	LogITEM LogItem;
	ZeroMemory(&LogItem, sizeof(LogITEM));

	if (!lpPlayInfo->pcSocketData)
		return FALSE;

	LogItem.Flag = Flag;
	lstrcpy(LogItem.UserID, lpPlayInfo->szAccountName);
	lstrcpy(LogItem.CharName, lpPlayInfo->szCharacterName);
	LogItem.IP = lpPlayInfo->pcSocketData->lIP;

	LogItem.ItemCount = 0;

	LogItem.Item[LogItem.ItemCount].dwCode = pMixtureResetItem_Server->DesMixtureResetItem.sItem.sItemID.ToInt();
	LogItem.Item[LogItem.ItemCount].dwINo[0] = pMixtureResetItem_Server->DesMixtureResetItem.sItem.iChk1;
	LogItem.Item[LogItem.ItemCount].dwINo[1] = pMixtureResetItem_Server->DesMixtureResetItem.sItem.iChk2;
	LogItem.ItemCount++;

	LogItem.Item[LogItem.ItemCount].dwCode = pMixtureResetItem_Server->dwMixtureResetStoneItemCode;
	LogItem.Item[LogItem.ItemCount].dwINo[0] = pMixtureResetItem_Server->dwMixtureResetStoneHead;
	LogItem.Item[LogItem.ItemCount].dwINo[1] = pMixtureResetItem_Server->dwMixtureResetStoneCheckSum;
	LogItem.ItemCount++;

	if (LogItem.ItemCount == 0)
		return FALSE;
	LogItem.size = sizeof(LogITEM) - (sizeof(_LogITEM)*(32 - LogItem.ItemCount));

	return b_PushLogItemQue(1, LogItem.size, &LogItem);
}
int	rsSaveAgingItemToHDD(Item *lpItem)
{
	char	szBuff[256];
	FILE	*fp;

	CreateDirectory(szLogItemDataDirectory, NULL);

	wsprintf(szBuff, "%s\\%d@%d.itm", szLogItemDataDirectory, lpItem->iChk1, lpItem->iChk2);
	fopen_s(&fp,szBuff, "wb");
	if (fp)
	{
		fwrite(lpItem, sizeof(Item), 1, fp);
		fclose(fp);
		return TRUE;
	}

	return FALSE;
}

int	rsSaveCreateItemToHDD(LootItem	*lpItem)
{
	DWORD	dwCode;
	char	szBuff[256];
	FILE	*fp;

	dwCode = lpItem->sItem.sItemID.ToInt();
	if (dwCode >= sinPM1)
		return FALSE;
	if ((dwCode&sinITEM_MASK2) == sinOS1)
	{
		if ((dwCode&sinITEM_MASK3) < sin05)
			return FALSE;
	}
	else
	{
		if ((dwCode&sinITEM_MASK3) < sin08)
			return FALSE;
	}

	CreateDirectory(szLogItemDataDirectory, NULL);

	wsprintf(szBuff, "%s\\%d@%d.itm", szLogItemDataDirectory, lpItem->sItem.iChk1, lpItem->sItem.iChk2);
	fopen_s(&fp,szBuff, "wb");
	if (fp)
	{
		fwrite(&lpItem->sItem, sizeof(Item), 1, fp);
		fclose(fp);
		return TRUE;
	}

	return FALSE;
}
int	rsLoadCreateItemToHDD(LootItem	*lpItem, char *szFileCode)
{
	FILE *fp;
	HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;
	char	szBuff[256];

	wsprintf(szBuff, "%s\\%s.itm", szLogItemDataDirectory, szFileCode);

	hFindHandle = FindFirstFile(szBuff, &fd);
	if (hFindHandle != INVALID_HANDLE_VALUE)
	{
		FindClose(hFindHandle);

		fopen_s(&fp,szBuff, "rb");
		if (fp)
		{
			fread(&lpItem->sItem, sizeof(Item), 1, fp);
			fclose(fp);
		}
		return TRUE;
	}

	return FALSE;
}



struct	sRECORD_COPIED_ITEM_HEAD
{
	char	szHeader[16];
	int		TotalCount;
	int		A_ItemCount;
	int		D_ItemCount;
	int		S_ItemCount;
	int		E_ItemCount;

	int		Temp[7];
};

struct	sRECORD_COPIED_ITEM
{
	DWORD	dwItemCode;
	DWORD	dwHead;
	DWORD	dwChkSum;
	DWORD	dwTemp;
};

struct sRECORD_COPIED_ITEM_FILE
{
	sRECORD_COPIED_ITEM_HEAD	sHeader;
	sRECORD_COPIED_ITEM			sCopiedItem[4096];
};


sRECORD_COPIED_ITEM	*lpCopiedItem_List = 0;
sRECORD_COPIED_ITEM	*lpCopiedItem_Sheltom_List = 0;

int rsCopiedItem_Count = 0;
int rsCopiedItem_Sheltom_Count = 0;

int rsLoadCopiedItemList()
{
	sRECORD_COPIED_ITEM_FILE	sCopiedItems;
	FILE *fp;
	int cnt;

	rsRemoveCopiedItemList();

	fopen_s(&fp,"cpItem.dat", "rb");
	if (!fp)
		return FALSE;

	fread(&sCopiedItems, sizeof(sRECORD_COPIED_ITEM_FILE), 1, fp);
	fclose(fp);

	if (sCopiedItems.sHeader.TotalCount >= 4096 || sCopiedItems.sHeader.TotalCount < 0)
		return FALSE;

	rsCopiedItem_Sheltom_Count = 0;
	rsCopiedItem_Count = 0;

	for (cnt = 0; cnt < sCopiedItems.sHeader.TotalCount; cnt++)
	{
		if ((sCopiedItems.sCopiedItem[cnt].dwItemCode&sinITEM_MASK2) == sinOS1)
			rsCopiedItem_Sheltom_Count++;
		else
			rsCopiedItem_Count++;
	}

	if (rsCopiedItem_Count)
		lpCopiedItem_List = new sRECORD_COPIED_ITEM[rsCopiedItem_Count];
	if (rsCopiedItem_Sheltom_Count)
		lpCopiedItem_Sheltom_List = new sRECORD_COPIED_ITEM[rsCopiedItem_Sheltom_Count];

	rsCopiedItem_Sheltom_Count = 0;
	rsCopiedItem_Count = 0;

	for (cnt = 0; cnt < sCopiedItems.sHeader.TotalCount; cnt++)
	{
		if ((sCopiedItems.sCopiedItem[cnt].dwItemCode&sinITEM_MASK2) == sinOS1)
		{
			lpCopiedItem_Sheltom_List[rsCopiedItem_Sheltom_Count].dwItemCode = sCopiedItems.sCopiedItem[cnt].dwItemCode;
			lpCopiedItem_Sheltom_List[rsCopiedItem_Sheltom_Count].dwHead = sCopiedItems.sCopiedItem[cnt].dwHead;
			lpCopiedItem_Sheltom_List[rsCopiedItem_Sheltom_Count].dwChkSum = sCopiedItems.sCopiedItem[cnt].dwChkSum;
			rsCopiedItem_Sheltom_Count++;
		}
		else
		{
			lpCopiedItem_List[rsCopiedItem_Count].dwItemCode = sCopiedItems.sCopiedItem[cnt].dwItemCode;
			lpCopiedItem_List[rsCopiedItem_Count].dwHead = sCopiedItems.sCopiedItem[cnt].dwHead;
			lpCopiedItem_List[rsCopiedItem_Count].dwChkSum = sCopiedItems.sCopiedItem[cnt].dwChkSum;
			rsCopiedItem_Count++;
		}
	}

	return TRUE;
}
int rsRemoveCopiedItemList()
{
	DELET(lpCopiedItem_List);
	DELET(lpCopiedItem_Sheltom_List);

	rsCopiedItem_Sheltom_Count = 0;
	rsCopiedItem_Count = 0;

	return TRUE;
}
int rsCheckCopiedItem(DWORD dwCode, DWORD dwHead, DWORD dwChkSum)
{
	int cnt;

	if ((dwCode&sinITEM_MASK2) == sinOS1)
	{
		if (!lpCopiedItem_Sheltom_List || rsCopiedItem_Sheltom_Count <= 0)
			return FALSE;

		for (cnt = 0; cnt < rsCopiedItem_Sheltom_Count; cnt++)
		{
			if (dwCode == lpCopiedItem_Sheltom_List[cnt].dwItemCode && dwHead == lpCopiedItem_Sheltom_List[cnt].dwHead && dwChkSum == lpCopiedItem_Sheltom_List[cnt].dwChkSum)
				return TRUE;
		}
	}
	else
	{
		if (!lpCopiedItem_List || rsCopiedItem_Count <= 0)
			return FALSE;

		for (cnt = 0; cnt < rsCopiedItem_Count; cnt++)
		{
			if (dwCode == lpCopiedItem_List[cnt].dwItemCode && dwHead == lpCopiedItem_List[cnt].dwHead && dwChkSum == lpCopiedItem_List[cnt].dwChkSum)
				return TRUE;
		}
	}

	return FALSE;
}
int rsCheckCopiedItem(Item *lpItem)
{
	DWORD dwHead, dwChkSum;

	if (lpItem->BackUpKey && lpItem->BackUpChkSum)
	{
		dwHead = lpItem->BackUpKey;
		dwChkSum = lpItem->BackUpChkSum;
	}
	else
	{
		dwHead = lpItem->iChk1;
		dwChkSum = lpItem->iChk2;
	}

	return rsCheckCopiedItem(lpItem->sItemID.ToInt(), dwHead, dwChkSum);
}

int rsGetlpLinkChar(User *lpPlayInfo, Unit *lpChar)
{
	for (int i = 0; i < SIN_MAX_SKILL_LIST; i++)
	{
		if (lpPlayInfo->lpLinkChar[i] == lpChar)
		{
			if (lpPlayInfo->pcSocketData && lpPlayInfo->TransInfoFlag)
				return TRUE;
		}
	}
	return FALSE;
}
//¸üÐÂ³èÎï¹¥»÷Ä£Ê½
int rsUpdateSkill(User *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{
	int JobCode = lpPlayInfo->sCharacterData.iClass;
	int SkillCode = lpTransCommand->WParam;

	for (int i = 0; i < SIN_MAX_SKILL_LIST; i++)
	{
		if (SkillCode == SKILL_METAL_GOLEM || SkillCode == SKILL_RECALL_WOLVERIN || SkillCode == SKILL_S_ARCUDA || SkillCode == SKILL_FIRE_ELEMENTAL || SkillCode == SKILL_RECALL_BLOODYKNIGHT)
		{
			if (lpPlayInfo->lpLinkChar[i])
			{
				if ((JobCode == CHARACTERCLASS_Mechanician && lpPlayInfo->lpLinkChar[i]->iPetID == SKILL_PLAY_METAL_GOLEM) ||
					(JobCode == CHARACTERCLASS_Archer && lpPlayInfo->lpLinkChar[i]->iPetID == SKILL_PLAY_RECALL_WOLVERIN) ||
					(JobCode == CHARACTERCLASS_Atalanta && lpPlayInfo->lpLinkChar[i]->iPetID == SKILL_PLAY_S_ARCUDA) ||
					(JobCode == CHARACTERCLASS_Magician && lpPlayInfo->lpLinkChar[i]->iPetID == SKILL_PLAY_FIRE_ELEMENTAL) ||
					(JobCode == CHARACTERCLASS_Shaman && lpPlayInfo->lpLinkChar[i]->iPetID == SKILL_PLAY_CRIMSON_KNIGHT))
				{
					lpPlayInfo->lpLinkChar[i]->bAggressive = lpTransCommand->LParam;
					lpPlayInfo->lpLinkChar[i]->pcFocusTarget = 0;
					lpPlayInfo->lpLinkChar[i]->pcAttackTarget = 0;
					break;
				}
			}
		}
		else if (SkillCode == SKILL_CRYSTAL_ORB)
		{
			if (lpPlayInfo->lpLinkChar[i] && lpPlayInfo->lpLinkChar[i]->iPetID == SkillCode && lpPlayInfo->lpLinkChar[i]->iID == lpTransCommand->SParam)
			{
				lpPlayInfo->lpLinkChar[i]->bAggressive = lpTransCommand->LParam;
				lpPlayInfo->lpLinkChar[i]->pcFocusTarget = 0;
				lpPlayInfo->lpLinkChar[i]->pcAttackTarget = 0;
				break;
			}
		}
	}
	return TRUE;
}
//ËÀÍö»Ø³Ç
int rsCancelSkill(User *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{
	int SkillCode = lpTransCommand->WParam;
	switch (lpPlayInfo->sCharacterData.iClass)
	{
	case CHARACTERCLASS_Fighter:
		switch (SkillCode)
		{
		case SKILL_BERSERKER:
			// ·è¿ñÅ­ºð
			if (lpPlayInfo->dwSkill_Berserker_Time != 0)
			{
				lpPlayInfo->dwSkill_Berserker_Time = 0;
				lpPlayInfo->dwSkill_Berserker_Param = 0;
			}
			break;
		case SKILL_B_BERSERKER:
			// ÖÚÉñÖ®Å­
			if (lpPlayInfo->dwSkill_B_Berserker_Time != 0)
			{
				lpPlayInfo->dwSkill_B_Berserker_Time = 0;
				lpPlayInfo->dwSkill_B_Berserker_Param = 0;
			}
			break;
		default:
			// ·è¿ñÅ­ºð
			if (lpPlayInfo->dwSkill_Berserker_Time != 0)
			{
				lpPlayInfo->dwSkill_Berserker_Time = 0;
				lpPlayInfo->dwSkill_Berserker_Param = 0;
			}
			// ÖÚÉñÖ®Å­
			if (lpPlayInfo->dwSkill_B_Berserker_Time != 0)
			{
				lpPlayInfo->dwSkill_B_Berserker_Time = 0;
				lpPlayInfo->dwSkill_B_Berserker_Param = 0;
			}
			// Õ½Éñ×£¸£
			if (lpPlayInfo->dwSkill_P_Enhence_Time != 0)
			{
				lpPlayInfo->dwSkill_P_Enhence_Time = 0;
				lpPlayInfo->dwSkill_P_Enhence_Param = 0;
			}
			// ×ÔÈ»Ö®¹â
			if (lpPlayInfo->dwSkill_ForceOfNature_Time != 0)
			{
				lpPlayInfo->dwSkill_ForceOfNature_Time = 0;
				lpPlayInfo->wSkill_ForceOfNature_Param[0] = 0;
				lpPlayInfo->wSkill_ForceOfNature_Param[1] = 0;
			}
			// Õ½ÀõÅØÏø
			if (lpPlayInfo->dwSkill_TriumphOfValhalla_Time != 0)
			{
				lpPlayInfo->dwSkill_TriumphOfValhalla_Time = 0;
				lpPlayInfo->dwSkill_TriumphOfValhalla_Param = 0;
			}
			// Íß¶û¹þÀ­Ö®¹â
			if (lpPlayInfo->dwSkill_HallOfValhalla_Time != 0)
			{
				lpPlayInfo->dwSkill_HallOfValhalla_Time = 0;
				lpPlayInfo->wSkill_HallOfValhalla_Param[0] = 0;
				lpPlayInfo->wSkill_HallOfValhalla_Param[1] = 0;
			}
			//ÍöÁéÖ®Öä
			if (lpPlayInfo->dwSkill_Benedic_Time != 0)
			{
				lpPlayInfo->dwSkill_Benedic_Time = 0;
			}
			// ½µµÍ¹¥»÷
			if (lpPlayInfo->dwCurse_Attack_Time != 0)
			{
				lpPlayInfo->dwCurse_Attack_Time = 0;
				lpPlayInfo->dwCurse_Attack_Param = 0;
			}
			// ½µµÍ·ÀÓù
			if (lpPlayInfo->dwCurse_Defence_Time != 0)
			{
				lpPlayInfo->dwCurse_Defence_Time = 0;
				lpPlayInfo->dwCurse_Defence_Param = 0;
			}
			break;
		}
		break;
	case CHARACTERCLASS_Mechanician:
		switch (SkillCode)
		{
			// ¼«¹â»¤¶Ü
		case SKILL_EXTREME_SHIELD:
			if (lpPlayInfo->dwSkill_ExtreamShield_Time != 0)
			{
				lpPlayInfo->dwSkill_ExtreamShield_Time = 0;
				lpPlayInfo->dwSkill_ExtreamShield_Param = 0;
			}
			break;
			// Áé¹â»¤Ìå
		case SKILL_PHYSICAL_ABSORB:
			if (lpPlayInfo->dwSkill_PhysicalAbsorb_Time != 0)
			{
				lpPlayInfo->dwSkill_PhysicalAbsorb_Time = 0;
				lpPlayInfo->dwSkill_PhysicalAbsorb_Param = 0;
			}
			break;
			// ¸ÄÁ¼×¨¼Ò
		case SKILL_MAXIMIZE:
			if (lpPlayInfo->dwSkill_Maximize_Time != 0)
			{
				lpPlayInfo->dwSkill_Maximize_Time = 0;
				lpPlayInfo->dwSkill_Maximize_Param = 0;
			}
			break;
			// Áé¹â·ÉÑï
		case SKILL_AUTOMATION:
			if (lpPlayInfo->dwSkill_AutoMation_Time != 0)
			{
				lpPlayInfo->dwSkill_AutoMation_Time = 0;
				lpPlayInfo->dwSkill_AutoMation_Param = 0;
			}
			break;
			// ½ðÊôÖØ¼×
		case SKILL_METAL_ARMOR:
			if (lpPlayInfo->dwSkill_MetalArmor_Time != 0)
			{
				lpPlayInfo->dwSkill_MetalArmor_Time = 0;
				lpPlayInfo->dwSkill_MetalArmor_Param = 0;
			}
			break;
			// ·ÀÓùµç²¨
		case SKILL_SPARK_SHIELD:
			if (lpPlayInfo->dwSkill_SparkShield_Time != 0)
			{
				lpPlayInfo->dwSkill_SparkShield_Time = 0;
				lpPlayInfo->dwSkill_SparkShield_Param = 0;
			}
			break;
			// ´ÅÐÔÇòÌå
		case SKILL_MAGNETIC_SPHERE:
			if (lpPlayInfo->dwSkill_MagneticSphere_Time != 0)
			{
				lpPlayInfo->dwSkill_MagneticSphere_Time = 0;
				lpPlayInfo->dwSkill_MagneticSphere_Param = 0;
			}
			break;
		default:
			// ¼«¹â»¤¶Ü
			if (lpPlayInfo->dwSkill_ExtreamShield_Time != 0)
			{
				lpPlayInfo->dwSkill_ExtreamShield_Time = 0;
				lpPlayInfo->dwSkill_ExtreamShield_Param = 0;
			}
			// Áé¹â»¤Ìå
			if (lpPlayInfo->dwSkill_PhysicalAbsorb_Time != 0)
			{
				lpPlayInfo->dwSkill_PhysicalAbsorb_Time = 0;
				lpPlayInfo->dwSkill_PhysicalAbsorb_Param = 0;
			}
			// ¸ÄÁ¼×¨¼Ò
			if (lpPlayInfo->dwSkill_Maximize_Time != 0)
			{
				lpPlayInfo->dwSkill_Maximize_Time = 0;
				lpPlayInfo->dwSkill_Maximize_Param = 0;
			}
			// Áé¹â·ÉÑï
			if (lpPlayInfo->dwSkill_AutoMation_Time != 0)
			{
				lpPlayInfo->dwSkill_AutoMation_Time = 0;
				lpPlayInfo->dwSkill_AutoMation_Param = 0;
			}
			// ½ðÊôÖØ¼×
			if (lpPlayInfo->dwSkill_MetalArmor_Time != 0)
			{
				lpPlayInfo->dwSkill_MetalArmor_Time = 0;
				lpPlayInfo->dwSkill_MetalArmor_Param = 0;
			}
			// ·ÀÓùµç²¨
			if (lpPlayInfo->dwSkill_SparkShield_Time != 0)
			{
				lpPlayInfo->dwSkill_SparkShield_Time = 0;
				lpPlayInfo->dwSkill_SparkShield_Param = 0;
			}
			// ´ÅÐÔÇòÌå
			if (lpPlayInfo->dwSkill_MagneticSphere_Time != 0)
			{
				lpPlayInfo->dwSkill_MagneticSphere_Time = 0;
				lpPlayInfo->dwSkill_MagneticSphere_Param = 0;
			}
			// Õ½Éñ×£¸£
			if (lpPlayInfo->dwSkill_P_Enhence_Time != 0)
			{
				lpPlayInfo->dwSkill_P_Enhence_Time = 0;
				lpPlayInfo->dwSkill_P_Enhence_Param = 0;
			}
			// ×ÔÈ»Ö®¹â
			if (lpPlayInfo->dwSkill_ForceOfNature_Time != 0)
			{
				lpPlayInfo->dwSkill_ForceOfNature_Time = 0;
				lpPlayInfo->wSkill_ForceOfNature_Param[0] = 0;
				lpPlayInfo->wSkill_ForceOfNature_Param[1] = 0;
			}
			// Õ½ÀõÅØÏø
			if (lpPlayInfo->dwSkill_TriumphOfValhalla_Time != 0)
			{
				lpPlayInfo->dwSkill_TriumphOfValhalla_Time = 0;
				lpPlayInfo->dwSkill_TriumphOfValhalla_Param = 0;
			}
			// Íß¶û¹þÀ­Ö®¹â
			if (lpPlayInfo->dwSkill_HallOfValhalla_Time != 0)
			{
				lpPlayInfo->dwSkill_HallOfValhalla_Time = 0;
				lpPlayInfo->wSkill_HallOfValhalla_Param[0] = 0;
				lpPlayInfo->wSkill_HallOfValhalla_Param[1] = 0;
			}
			//ÍöÁéÖ®Öä
			if (lpPlayInfo->dwSkill_Benedic_Time != 0)
			{
				lpPlayInfo->dwSkill_Benedic_Time = 0;
			}
			// ÔªËØÖ®Êõ
			if (lpPlayInfo->dwSkill_EnchantWeapon_Time != 0)
			{
				lpPlayInfo->dwSkill_EnchantWeapon_Time = 0;
				lpPlayInfo->dwSkill_EnchantWeapon_Param = 0;
			}
			// ½µµÍ¹¥»÷
			if (lpPlayInfo->dwCurse_Attack_Time != 0)
			{
				lpPlayInfo->dwCurse_Attack_Time = 0;
				lpPlayInfo->dwCurse_Attack_Param = 0;
			}
			// ½µµÍ·ÀÓù
			if (lpPlayInfo->dwCurse_Defence_Time != 0)
			{
				lpPlayInfo->dwCurse_Defence_Time = 0;
				lpPlayInfo->dwCurse_Defence_Param = 0;
			}
		}
		break;
	case CHARACTERCLASS_Archer:
		switch (SKILL_FALCON)
		{
			// Áé»êÖ®Ó¥
		case SKILL_SCOUT_HAWK:
		case SKILL_FALCON:
		case SKILL_GOLDEN_FALCON:
			if (lpPlayInfo->dwSKill_Falcon_Time != 0)
			{
				lpPlayInfo->dwSKill_Falcon_Time = 0;
				lpPlayInfo->dwSKill_Falcon_Damage[0] = 0;
				lpPlayInfo->dwSKill_Falcon_Damage[1] = 0;
			}
			break;
		default:
			// Áé»êÖ®Ó¥
			if (lpPlayInfo->dwSKill_Falcon_Time != 0)
			{
				lpPlayInfo->dwSKill_Falcon_Time = 0;
				lpPlayInfo->dwSKill_Falcon_Damage[0] = 0;
				lpPlayInfo->dwSKill_Falcon_Damage[1] = 0;
			}
			// ×ÔÈ»Ö®¹â
			if (lpPlayInfo->dwSkill_ForceOfNature_Time != 0)
			{
				lpPlayInfo->dwSkill_ForceOfNature_Time = 0;
				lpPlayInfo->wSkill_ForceOfNature_Param[0] = 0;
				lpPlayInfo->wSkill_ForceOfNature_Param[1] = 0;
			}
			// Õ½Éñ×£¸£
			if (lpPlayInfo->dwSkill_P_Enhence_Time != 0)
			{
				lpPlayInfo->dwSkill_P_Enhence_Time = 0;
				lpPlayInfo->dwSkill_P_Enhence_Param = 0;
			}
			// Õ½ÀõÅØÏø
			if (lpPlayInfo->dwSkill_TriumphOfValhalla_Time != 0)
			{
				lpPlayInfo->dwSkill_TriumphOfValhalla_Time = 0;
				lpPlayInfo->dwSkill_TriumphOfValhalla_Param = 0;
			}
			// Íß¶û¹þÀ­Ö®¹â
			if (lpPlayInfo->dwSkill_HallOfValhalla_Time != 0)
			{
				lpPlayInfo->dwSkill_HallOfValhalla_Time = 0;
				lpPlayInfo->wSkill_HallOfValhalla_Param[0] = 0;
				lpPlayInfo->wSkill_HallOfValhalla_Param[1] = 0;
			}
			//ÍöÁéÖ®Öä
			if (lpPlayInfo->dwSkill_Benedic_Time != 0)
			{
				lpPlayInfo->dwSkill_Benedic_Time = 0;
			}
			// ½µµÍ¹¥»÷
			if (lpPlayInfo->dwCurse_Attack_Time != 0)
			{
				lpPlayInfo->dwCurse_Attack_Time = 0;
				lpPlayInfo->dwCurse_Attack_Param = 0;
			}
			// ½µµÍ·ÀÓù
			if (lpPlayInfo->dwCurse_Defence_Time != 0)
			{
				lpPlayInfo->dwCurse_Defence_Time = 0;
				lpPlayInfo->dwCurse_Defence_Param = 0;
			}
		}
		break;
	case CHARACTERCLASS_Pikeman:
		// Òþ°µÖ®Êõ
		if (lpPlayInfo->dwVanishEndTime != 0)
		{
			lpPlayInfo->dwVanishEndTime = 0;
			lpPlayInfo->saVanishParam[0] = 0;
			lpPlayInfo->saVanishParam[1] = 0;
		}
		// °µÉ±Ö®ÑÛ
		if (lpPlayInfo->dwSkill_AssassinEye_Time != 0)
		{
			lpPlayInfo->dwSkill_AssassinEye_Time = 0;
			lpPlayInfo->dwSkill_AssassinEye_Param = 0;
		}
		// Ó°ÒþÖ®¶Ý
		if (lpPlayInfo->dwSkill_Vague_Time != 0)
		{
			lpPlayInfo->dwSkill_Vague_Time = 0;
			lpPlayInfo->dwSkill_Vague_Param = 0;
		}
		//Ç±ÄÜ¼¤·¢
		if (lpPlayInfo->dwSkill_Amplified_Time != 0)
		{
			lpPlayInfo->dwSkill_Amplified_Time = 0;
			lpPlayInfo->dwSkill_Amplified_Param = 0;
		}
		// Õ½Éñ×£¸£
		if (lpPlayInfo->dwSkill_P_Enhence_Time != 0)
		{
			lpPlayInfo->dwSkill_P_Enhence_Time = 0;
			lpPlayInfo->dwSkill_P_Enhence_Param = 0;
		}
		// ×ÔÈ»Ö®¹â
		if (lpPlayInfo->dwSkill_ForceOfNature_Time != 0)
		{
			lpPlayInfo->dwSkill_ForceOfNature_Time = 0;
			lpPlayInfo->wSkill_ForceOfNature_Param[0] = 0;
			lpPlayInfo->wSkill_ForceOfNature_Param[1] = 0;
		}
		// Õ½ÀõÅØÏø
		if (lpPlayInfo->dwSkill_TriumphOfValhalla_Time != 0)
		{
			lpPlayInfo->dwSkill_TriumphOfValhalla_Time = 0;
			lpPlayInfo->dwSkill_TriumphOfValhalla_Param = 0;
		}
		// Íß¶û¹þÀ­Ö®¹â
		if (lpPlayInfo->dwSkill_HallOfValhalla_Time != 0)
		{
			lpPlayInfo->dwSkill_HallOfValhalla_Time = 0;
			lpPlayInfo->wSkill_HallOfValhalla_Param[0] = 0;
			lpPlayInfo->wSkill_HallOfValhalla_Param[1] = 0;
		}
		//ÍöÁéÖ®Öä
		if (lpPlayInfo->dwSkill_Benedic_Time != 0)
		{
			lpPlayInfo->dwSkill_Benedic_Time = 0;
		}
		// ½µµÍ¹¥»÷
		if (lpPlayInfo->dwCurse_Attack_Time != 0)
		{
			lpPlayInfo->dwCurse_Attack_Time = 0;
			lpPlayInfo->dwCurse_Attack_Param = 0;
		}
		// ½µµÍ·ÀÓù
		if (lpPlayInfo->dwCurse_Defence_Time != 0)
		{
			lpPlayInfo->dwCurse_Defence_Time = 0;
			lpPlayInfo->dwCurse_Defence_Param = 0;
		}
		break;
	case CHARACTERCLASS_Atalanta:
		switch (SkillCode)
		{
			// Ëª¶³±êÇ¹
		case SKILL_FROST_JAVELIN:
			if (lpPlayInfo->dwSkill_FrostJavelin_Time != 0)
			{
				lpPlayInfo->dwSkill_FrostJavelin_Time = 0;
				lpPlayInfo->dwSkill_FrostJavelin_Param = 0;
			}
			break;
		default:
			// Ëª¶³±êÇ¹
			if (lpPlayInfo->dwSkill_FrostJavelin_Time != 0)
			{
				lpPlayInfo->dwSkill_FrostJavelin_Time = 0;
				lpPlayInfo->dwSkill_FrostJavelin_Param = 0;
			}
			// Õ½Éñ×£¸£
			if (lpPlayInfo->dwSkill_P_Enhence_Time != 0)
			{
				lpPlayInfo->dwSkill_P_Enhence_Time = 0;
				lpPlayInfo->dwSkill_P_Enhence_Param = 0;
			}
			// ×ÔÈ»Ö®¹â
			if (lpPlayInfo->dwSkill_ForceOfNature_Time != 0)
			{
				lpPlayInfo->dwSkill_ForceOfNature_Time = 0;
				lpPlayInfo->wSkill_ForceOfNature_Param[0] = 0;
				lpPlayInfo->wSkill_ForceOfNature_Param[1] = 0;
			}
			// Õ½ÀõÅØÏø
			if (lpPlayInfo->dwSkill_TriumphOfValhalla_Time != 0)
			{
				lpPlayInfo->dwSkill_TriumphOfValhalla_Time = 0;
				lpPlayInfo->dwSkill_TriumphOfValhalla_Param = 0;
			}
			// Íß¶û¹þÀ­Ö®¹â
			if (lpPlayInfo->dwSkill_HallOfValhalla_Time != 0)
			{
				lpPlayInfo->dwSkill_HallOfValhalla_Time = 0;
				lpPlayInfo->wSkill_HallOfValhalla_Param[0] = 0;
				lpPlayInfo->wSkill_HallOfValhalla_Param[1] = 0;
			}
			//ÍöÁéÖ®Öä
			if (lpPlayInfo->dwSkill_Benedic_Time != 0)
			{
				lpPlayInfo->dwSkill_Benedic_Time = 0;
			}
			// ½µµÍ¹¥»÷
			if (lpPlayInfo->dwCurse_Attack_Time != 0)
			{
				lpPlayInfo->dwCurse_Attack_Time = 0;
				lpPlayInfo->dwCurse_Attack_Param = 0;
			}
			// ½µµÍ·ÀÓù
			if (lpPlayInfo->dwCurse_Defence_Time != 0)
			{
				lpPlayInfo->dwCurse_Defence_Time = 0;
				lpPlayInfo->dwCurse_Defence_Param = 0;
			}
		}
		break;
	case CHARACTERCLASS_Knight:
		switch (SkillCode)
		{
			// Ê¥ÁéÖ®Îü
		case SKILL_DIVINE_INHALATION:
			if (lpPlayInfo->dwSkill_DivineInhalation_Time != 0)
			{
				lpPlayInfo->dwSkill_DivineInhalation_Time = 0;
				lpPlayInfo->dwSkill_DivineInhalation_Param = 0;
			}
			break;
			// ¾´ÉñÖ®¶Ü
		case SKILL_GODLY_SHIELD:
			if (lpPlayInfo->dwSkill_GodlyShied_Time != 0)
			{
				lpPlayInfo->dwSkill_GodlyShied_Time = 0;
				lpPlayInfo->dwSkill_GodlyShied_Param = 0;
			}
			break;
		default:
			// Ê¥¹â»¤Ìå
			if (lpPlayInfo->dwSkill_HolyBody_Time != 0)
			{
				lpPlayInfo->dwSkill_HolyBody_Time = 0;
				lpPlayInfo->dwSkill_HolyBody_Param = 0;
			}
			// ÉñÁ¦ÖØ»÷
			if (lpPlayInfo->dwSkill_HolyValor_Time != 0)
			{
				lpPlayInfo->dwSkill_HolyValor_Time = 0;
				lpPlayInfo->dwSkill_HolyValor_Param = 0;
			}
			// Ê¥ÁéÖ®Îü
			if (lpPlayInfo->dwSkill_DivineInhalation_Time != 0)
			{
				lpPlayInfo->dwSkill_DivineInhalation_Time = 0;
				lpPlayInfo->dwSkill_DivineInhalation_Param = 0;
			}
			// ¾´ÉñÖ®¶Ü
			if (lpPlayInfo->dwSkill_GodlyShied_Time != 0)
			{
				lpPlayInfo->dwSkill_GodlyShied_Time = 0;
				lpPlayInfo->dwSkill_GodlyShied_Param = 0;
			}
			// ÉÏµÛ×£¸£
			if (lpPlayInfo->dwSkill_GodsBless_Time != 0)
			{
				lpPlayInfo->dwSkill_GodsBless_Time = 0;
				lpPlayInfo->dwSkill_GodsBless_Param = 0;
			}
			// Õ½Éñ×£¸£
			if (lpPlayInfo->dwSkill_P_Enhence_Time != 0)
			{
				lpPlayInfo->dwSkill_P_Enhence_Time = 0;
				lpPlayInfo->dwSkill_P_Enhence_Param = 0;
			}
			//ÍöÁéÖ®Öä
			if (lpPlayInfo->dwSkill_Benedic_Time != 0)
			{
				lpPlayInfo->dwSkill_Benedic_Time = 0;
			}
			// ×ÔÈ»Ö®¹â
			if (lpPlayInfo->dwSkill_ForceOfNature_Time != 0)
			{
				lpPlayInfo->dwSkill_ForceOfNature_Time = 0;
				lpPlayInfo->wSkill_ForceOfNature_Param[0] = 0;
				lpPlayInfo->wSkill_ForceOfNature_Param[1] = 0;
			}
			// Õ½ÀõÅØÏø
			if (lpPlayInfo->dwSkill_TriumphOfValhalla_Time != 0)
			{
				lpPlayInfo->dwSkill_TriumphOfValhalla_Time = 0;
				lpPlayInfo->dwSkill_TriumphOfValhalla_Param = 0;
			}
			// Íß¶û¹þÀ­Ö®¹â
			if (lpPlayInfo->dwSkill_HallOfValhalla_Time != 0)
			{
				lpPlayInfo->dwSkill_HallOfValhalla_Time = 0;
				lpPlayInfo->wSkill_HallOfValhalla_Param[0] = 0;
				lpPlayInfo->wSkill_HallOfValhalla_Param[1] = 0;
			}
			// ½µµÍ¹¥»÷
			if (lpPlayInfo->dwCurse_Attack_Time != 0)
			{
				lpPlayInfo->dwCurse_Attack_Time = 0;
				lpPlayInfo->dwCurse_Attack_Param = 0;
			}
			// ½µµÍ·ÀÓù
			if (lpPlayInfo->dwCurse_Defence_Time != 0)
			{
				lpPlayInfo->dwCurse_Defence_Time = 0;
				lpPlayInfo->dwCurse_Defence_Param = 0;
			}
		}
		break;
	case CHARACTERCLASS_Magician:
		// ÔªËØÖ®Êõ
		if (lpPlayInfo->dwSkill_EnchantWeapon_Time != 0)
		{
			lpPlayInfo->dwSkill_EnchantWeapon_Time = 0;
			lpPlayInfo->dwSkill_EnchantWeapon_Param = 0;
		}
		// Ä§·¨ÊØ»¤
		if (lpPlayInfo->dwSkill_EnergyShield_Time != 0)
		{
			lpPlayInfo->dwSkill_EnergyShield_Time = 0;
			lpPlayInfo->dwSkill_EnergyShield_Param = 0;
		}
		// Áé»êÕÙ»½
		if (lpPlayInfo->dwSkill_SpiritElemental_Time != 0)
		{
			lpPlayInfo->dwSkill_SpiritElemental_Time = 0;
			lpPlayInfo->dwSkill_SpiritElemental_Param = 0;
		}
		// ÔªËØÖ®½£
		if (lpPlayInfo->dwSkill_DancingSword_Time != 0)
		{
			lpPlayInfo->dwSkill_DancingSword_Time = 0;
			lpPlayInfo->dwSkill_DancingSword_Param = 0;
			lpPlayInfo->dwSkill_DancingSword_DelayTime = 0;
		}
		// ÉñÊ¥·¨Õó
		if (lpPlayInfo->dwSkill_T_Anima_Time != 0)
		{
			lpPlayInfo->dwSkill_T_Anima_Time = 0;
			lpPlayInfo->dwSkill_T_Anima_Param = 0;
		}
		// Õ½Éñ×£¸£
		if (lpPlayInfo->dwSkill_P_Enhence_Time != 0)
		{
			lpPlayInfo->dwSkill_P_Enhence_Time = 0;
			lpPlayInfo->dwSkill_P_Enhence_Param = 0;
		}
		// ×ÔÈ»Ö®¹â
		if (lpPlayInfo->dwSkill_ForceOfNature_Time != 0)
		{
			lpPlayInfo->dwSkill_ForceOfNature_Time = 0;
			lpPlayInfo->wSkill_ForceOfNature_Param[0] = 0;
			lpPlayInfo->wSkill_ForceOfNature_Param[1] = 0;
		}
		// Õ½ÀõÅØÏø
		if (lpPlayInfo->dwSkill_TriumphOfValhalla_Time != 0)
		{
			lpPlayInfo->dwSkill_TriumphOfValhalla_Time = 0;
			lpPlayInfo->dwSkill_TriumphOfValhalla_Param = 0;
		}
		// Íß¶û¹þÀ­Ö®¹â
		if (lpPlayInfo->dwSkill_HallOfValhalla_Time != 0)
		{
			lpPlayInfo->dwSkill_HallOfValhalla_Time = 0;
			lpPlayInfo->wSkill_HallOfValhalla_Param[0] = 0;
			lpPlayInfo->wSkill_HallOfValhalla_Param[1] = 0;
		}
		//ÍöÁéÖ®Öä
		if (lpPlayInfo->dwSkill_Benedic_Time != 0)
		{
			lpPlayInfo->dwSkill_Benedic_Time = 0;
		}
		// ½µµÍ¹¥»÷
		if (lpPlayInfo->dwCurse_Attack_Time != 0)
		{
			lpPlayInfo->dwCurse_Attack_Time = 0;
			lpPlayInfo->dwCurse_Attack_Param = 0;
		}
		// ½µµÍ·ÀÓù
		if (lpPlayInfo->dwCurse_Defence_Time != 0)
		{
			lpPlayInfo->dwCurse_Defence_Time = 0;
			lpPlayInfo->dwCurse_Defence_Param = 0;
		}
		break;
		// ¼ÀË¾
	case CHARACTERCLASS_Priestess:
		// ÉñÊ¥·´Éä
		if (lpPlayInfo->dwSkill_HolyReflection_Time != 0)
		{
			lpPlayInfo->dwSkill_HolyReflection_Time = 0;
			lpPlayInfo->dwSkill_HolyReflection_Param = 0;
		}
		// ÉñÊ¥Ö®¹â
		if (lpPlayInfo->dwSkill_VirtualLife_Time != 0)
		{
			lpPlayInfo->dwSkill_VirtualLife_Time = 0;
			lpPlayInfo->dwSkill_VirtualLife_Param = 0;
		}
		// ÉñÊ¥ÌìÊ¹
		if (lpPlayInfo->dwSkill_SummonMuspell_Time != 0)
		{
			lpPlayInfo->dwSkill_SummonMuspell_Time = 0;
			lpPlayInfo->dwSkill_SummonMuspell_Param = 0;
		}
		// ÌìÅ®É¢»¨
		if (lpPlayInfo->dwSkill_Krishna_Time != 0)
		{
			lpPlayInfo->dwSkill_Krishna_Time = 0;
			lpPlayInfo->dwSkill_Krishna_Param = 0;
		}
		// Õ½Éñ×£¸£
		if (lpPlayInfo->dwSkill_P_Enhence_Time != 0)
		{
			lpPlayInfo->dwSkill_P_Enhence_Time = 0;
			lpPlayInfo->dwSkill_P_Enhence_Param = 0;
		}
		// ×ÔÈ»Ö®¹â
		if (lpPlayInfo->dwSkill_ForceOfNature_Time != 0)
		{
			lpPlayInfo->dwSkill_ForceOfNature_Time = 0;
			lpPlayInfo->wSkill_ForceOfNature_Param[0] = 0;
			lpPlayInfo->wSkill_ForceOfNature_Param[1] = 0;
		}
		// Õ½ÀõÅØÏø
		if (lpPlayInfo->dwSkill_TriumphOfValhalla_Time != 0)
		{
			lpPlayInfo->dwSkill_TriumphOfValhalla_Time = 0;
			lpPlayInfo->dwSkill_TriumphOfValhalla_Param = 0;
		}
		// Íß¶û¹þÀ­Ö®¹â
		if (lpPlayInfo->dwSkill_HallOfValhalla_Time != 0)
		{
			lpPlayInfo->dwSkill_HallOfValhalla_Time = 0;
			lpPlayInfo->wSkill_HallOfValhalla_Param[0] = 0;
			lpPlayInfo->wSkill_HallOfValhalla_Param[1] = 0;
		}
		//ÍöÁéÖ®Öä
		if (lpPlayInfo->dwSkill_Benedic_Time != 0)
		{
			lpPlayInfo->dwSkill_Benedic_Time = 0;
		}
		// ½µµÍ¹¥»÷
		if (lpPlayInfo->dwCurse_Attack_Time != 0)
		{
			lpPlayInfo->dwCurse_Attack_Time = 0;
			lpPlayInfo->dwCurse_Attack_Param = 0;
		}
		// ½µµÍ·ÀÓù
		if (lpPlayInfo->dwCurse_Defence_Time != 0)
		{
			lpPlayInfo->dwCurse_Defence_Time = 0;
			lpPlayInfo->dwCurse_Defence_Param = 0;
		}
		break;
		// ´Ì¿Í
	case CHARACTERCLASS_Assassin:
		//ÖÂÃ¤
		if (lpPlayInfo->dwSkill_Blind_Time != 0)
		{
			lpPlayInfo->dwSkill_Blind_Time = 0;
			lpPlayInfo->dwSkill_Blind_Param = 0;
		}
		// Õ½Éñ×£¸£
		if (lpPlayInfo->dwSkill_P_Enhence_Time != 0)
		{
			lpPlayInfo->dwSkill_P_Enhence_Time = 0;
			lpPlayInfo->dwSkill_P_Enhence_Param = 0;
		}
		// ×ÔÈ»Ö®¹â
		if (lpPlayInfo->dwSkill_ForceOfNature_Time != 0)
		{
			lpPlayInfo->dwSkill_ForceOfNature_Time = 0;
			lpPlayInfo->wSkill_ForceOfNature_Param[0] = 0;
			lpPlayInfo->wSkill_ForceOfNature_Param[1] = 0;
		}
		// Õ½ÀõÅØÏø
		if (lpPlayInfo->dwSkill_TriumphOfValhalla_Time != 0)
		{
			lpPlayInfo->dwSkill_TriumphOfValhalla_Time = 0;
			lpPlayInfo->dwSkill_TriumphOfValhalla_Param = 0;
		}
		// Íß¶û¹þÀ­Ö®¹â
		if (lpPlayInfo->dwSkill_HallOfValhalla_Time != 0)
		{
			lpPlayInfo->dwSkill_HallOfValhalla_Time = 0;
			lpPlayInfo->wSkill_HallOfValhalla_Param[0] = 0;
			lpPlayInfo->wSkill_HallOfValhalla_Param[1] = 0;
		}
		//ÍöÁéÖ®Öä
		if (lpPlayInfo->dwSkill_Benedic_Time != 0)
		{
			lpPlayInfo->dwSkill_Benedic_Time = 0;
		}
		// ½µµÍ¹¥»÷
		if (lpPlayInfo->dwCurse_Attack_Time != 0)
		{
			lpPlayInfo->dwCurse_Attack_Time = 0;
			lpPlayInfo->dwCurse_Attack_Param = 0;
		}
		// ½µµÍ·ÀÓù
		if (lpPlayInfo->dwCurse_Defence_Time != 0)
		{
			lpPlayInfo->dwCurse_Defence_Time = 0;
			lpPlayInfo->dwCurse_Defence_Param = 0;
		}
		break;
		//ÈøÂú
	case CHARACTERCLASS_Shaman:
		// Âõ¿Ë¶û
		if (lpPlayInfo->dwSkill_Advent_Migal_Time != 0)
		{
			lpPlayInfo->dwSkill_Advent_Migal_Time = 0;
			lpPlayInfo->dwSkill_Advent_Migal_Param = 0;
		}
		// ÆíÓêÊ¦
		if (lpPlayInfo->dwSkill_Rainmaker_Time != 0)
		{
			lpPlayInfo->dwSkill_Rainmaker_Time = 0;
			lpPlayInfo->dwSkill_Rainmaker_Param = 0;
		}
		// Õ½Éñ×£¸£
		if (lpPlayInfo->dwSkill_P_Enhence_Time != 0)
		{
			lpPlayInfo->dwSkill_P_Enhence_Time = 0;
			lpPlayInfo->dwSkill_P_Enhence_Param = 0;
		}
		// ×ÔÈ»Ö®¹â
		if (lpPlayInfo->dwSkill_ForceOfNature_Time != 0)
		{
			lpPlayInfo->dwSkill_ForceOfNature_Time = 0;
			lpPlayInfo->wSkill_ForceOfNature_Param[0] = 0;
			lpPlayInfo->wSkill_ForceOfNature_Param[1] = 0;
		}
		// Õ½ÀõÅØÏø
		if (lpPlayInfo->dwSkill_TriumphOfValhalla_Time != 0)
		{
			lpPlayInfo->dwSkill_TriumphOfValhalla_Time = 0;
			lpPlayInfo->dwSkill_TriumphOfValhalla_Param = 0;
		}
		// Íß¶û¹þÀ­Ö®¹â
		if (lpPlayInfo->dwSkill_HallOfValhalla_Time != 0)
		{
			lpPlayInfo->dwSkill_HallOfValhalla_Time = 0;
			lpPlayInfo->wSkill_HallOfValhalla_Param[0] = 0;
			lpPlayInfo->wSkill_HallOfValhalla_Param[1] = 0;
		}
		//ÍöÁéÖ®Öä
		if (lpPlayInfo->dwSkill_Benedic_Time != 0)
		{
			lpPlayInfo->dwSkill_Benedic_Time = 0;
		}
		// ½µµÍ¹¥»÷
		if (lpPlayInfo->dwCurse_Attack_Time != 0)
		{
			lpPlayInfo->dwCurse_Attack_Time = 0;
			lpPlayInfo->dwCurse_Attack_Param = 0;
		}
		// ½µµÍ·ÀÓù
		if (lpPlayInfo->dwCurse_Defence_Time != 0)
		{
			lpPlayInfo->dwCurse_Defence_Time = 0;
			lpPlayInfo->dwCurse_Defence_Param = 0;
		}
		break;
	}
	return TRUE;
}

// Ê±¼ä¼¼ÄÜ×é¶ÓÓÃ»§
int rsProcessSkillPartyUser(User *lpPlayInfo, TRANS_PARTY_SKILL *lpTransPartySkill, int JobCode)
{
	int point = lpTransPartySkill->Point - 1;
	if (point < 0 || point >= 10)
		return FALSE;

	int SkillCode = lpTransPartySkill->dwSkillCode & 0xFF;

	switch (JobCode)
	{
		//»úÐµ
	case CHARACTERCLASS_Mechanician:
		switch (SkillCode)
		{
			// Õ½Éñ×£¸£
		case SKILL_PLAY_P_ENHENCE:
			lpPlayInfo->dwSkill_P_Enhence_Time = SERVER_GAMETIME + P_Enhence_Time[point] * 1000;
			lpPlayInfo->dwSkill_P_Enhence_Param = GetRandomPos(P_Enhence_AddDamage[point][0], P_Enhence_AddDamage[point][1]);
			break;
		}
	case CHARACTERCLASS_Knight:
		switch (SkillCode)
		{
			//ÉñÁ¦ÖØ»÷
		case SKILL_PLAY_HOLY_VALOR:
			lpPlayInfo->dwSkill_HolyValor_Time = SERVER_GAMETIME + Holy_Valor_Time[point] * 1000;
			lpPlayInfo->dwSkill_HolyValor_Param = Holy_Valor_Damage[point];
			return TRUE;
		}
		break;
	case CHARACTERCLASS_Shaman:
		switch (SkillCode)
		{
			//Âõ¿Ë¶û
		case SKILL_PLAY_ADVENT_MIGAL:
			lpPlayInfo->dwSkill_Advent_Migal_Time = SERVER_GAMETIME + Advent_Migal_Time[point] * 1000;
			lpPlayInfo->dwSkill_Advent_Migal_Param = Advent_Migal_Atk[point];
			return TRUE;
			//Ã×µÂÀ¼´ï
		case SKILL_PLAY_ADVENT_MIDRANDA:
			return TRUE;
			//ÐñÈÕ¶«Éý
		case SKILL_PLAY_MOURNING_PRAY:
			return TRUE;
		}
		break;
	}
	return FALSE;
}

//½ÓÊÜ×é¶Ó¼¼ÄÜ
int	rsRecvSkillPartyUser(TRANS_PARTY_SKILL *lpTransPartySkill)
{
	int cnt;
	User *lpPlayInfo = NULL;

	lpPlayInfo = SERVERUSER->GetUser(lpTransPartySkill->dwPartyUser[0]);

	if (lpPlayInfo == NULL)
		return FALSE;

	int JobCode = lpPlayInfo->sCharacterData.iClass;

	for (cnt = 0; cnt < lpTransPartySkill->PartyCount; cnt++)
	{
		lpPlayInfo = SERVERUSER->GetUser(lpTransPartySkill->dwPartyUser[cnt]);
		if (lpPlayInfo && lpPlayInfo->pcSocketData)
		{
			if (rsProcessSkillPartyUser(lpPlayInfo, lpTransPartySkill, JobCode) == TRUE)
			{
				lpTransPartySkill->eParam = JobCode;

				SENDPACKET(lpPlayInfo, lpTransPartySkill);
			}
		}
	}

	return TRUE;
}

//½ÓÊÜÊ±¼ä¼¼ÄÜ
int rsRecvProcessSkill(User *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{
	DWORD dwSkillCode;
	int point;
	User *lpPlayInfo2;
	smTRANS_COMMAND_EX	TransCommandEx;
	int	lv;
	Unit	*lpChar;
	int cnt, x, y, z, dist, size;

	dwSkillCode = lpTransCommand->WParam & 0xFF;
	int JobCode = lpPlayInfo->sCharacterData.iClass;
	point = (lpTransCommand->WParam >> 8) & 0xF;
	point -= 1;

	if (point < 0) point = lpTransCommand->LParam - 1;

	if (point < 0 || point >= 10)
		return FALSE;

	if (rsCheckSkillLevel(lpPlayInfo, dwSkillCode) == FALSE)
	{
		if (lpPlayInfo->WarningCount < 5 && JobCode == CHARACTERCLASS_Priestess && dwSkillCode != SKILL_PLAY_RESURRECTION)
		{
			TransCommandEx.size = sizeof(smTRANS_COMMAND);
			TransCommandEx.code = smTRANSCODE_SET_BLACKLIST;
			TransCommandEx.WParam = 8850;
			TransCommandEx.LParam = lpPlayInfo->sCharacterData.iLevel;
			TransCommandEx.SParam = dwSkillCode;
			TransCommandEx.EParam = point;
			rsSendDataServer(lpPlayInfo, &TransCommandEx);
			lpPlayInfo->WarningCount++;
		}
	}
	switch (JobCode)
	{
	case CHARACTERCLASS_Fighter:
		switch (dwSkillCode)
		{
			//·è¿ñÅ­ºð
		case SKILL_PLAY_BERSERKER:
			lpPlayInfo->dwSkill_Berserker_Time = SERVER_GAMETIME + Berserker_Time[point] * 1000;
			lpPlayInfo->dwSkill_Berserker_Param = point;
			break;
			//ÖÚÉñÖ®Å­
		case SKILL_PLAY_B_BERSERKER:
			lpPlayInfo->dwSkill_B_Berserker_Time = SERVER_GAMETIME + B_Berserker_Time[point] * 1000;
			lpPlayInfo->dwSkill_B_Berserker_Param = point;
			break;
		}
		break;
	case CHARACTERCLASS_Mechanician:
		switch (dwSkillCode)
		{
			//¼«¹â»¤¶Ü
		case SKILL_PLAY_EXTREME_SHIELD:
			lpPlayInfo->dwSkill_ExtreamShield_Time = SERVER_GAMETIME + E_Shield_UseTime[point] * 1000;
			lpPlayInfo->dwSkill_ExtreamShield_Param = E_Shield_BlockRate[point];
			break;
			//Áé¹â»¤Ìå
		case SKILL_PLAY_PHYSICAL_ABSORB:
			lpPlayInfo->dwSkill_PhysicalAbsorb_Time = SERVER_GAMETIME + P_Absorb_UseTime[point] * 1000;
			lpPlayInfo->dwSkill_PhysicalAbsorb_Param = P_Absorb[point];
			break;
			//¸ÄÁ¼×¨¼Ò
		case SKILL_PLAY_MAXIMIZE:
			lpPlayInfo->dwSkill_Maximize_Time = SERVER_GAMETIME + Maximize_Time[point] * 1000;
			lpPlayInfo->dwSkill_Maximize_Param = Maximize_Damage[point];
			break;
			//Áé¹â·ÉÑï
		case SKILL_PLAY_AUTOMATION:
			lpPlayInfo->dwSkill_AutoMation_Time = SERVER_GAMETIME + Automation_Time[point] * 1000;
			lpPlayInfo->dwSkill_AutoMation_Param = Automation_Damage[point];
			break;
			//½ðÊôÖØ¼×
		case SKILL_PLAY_METAL_ARMOR:
			lpPlayInfo->dwSkill_MetalArmor_Time = SERVER_GAMETIME + Metal_Armor_Time[point] * 1000;
			if (lpTransCommand->SParam > 0 && lpTransCommand->SParam <= 10)
				lpPlayInfo->dwSkill_MetalArmor_Param = int((float(P_Absorb[lpTransCommand->SParam - 1]) * 2.0f) / 2);
			else
				lpPlayInfo->dwSkill_MetalArmor_Param = 0;
			break;
			//·ÀÓùµç²¨
		case SKILL_PLAY_SPARK_SHIELD:
			lpPlayInfo->dwSkill_SparkShield_Time = SERVER_GAMETIME + Spark_Shield_Time[point] * 1000;
			if (lpTransCommand->SParam > 0 && lpTransCommand->SParam <= 10)
			{
				lpPlayInfo->dwSkill_SparkShield_Param = (Spark_Shield_Damage[point] * Spark_Damage[lpTransCommand->SParam - 1][0]) / 100;
				lpPlayInfo->dwSkill_SparkShield_Param <<= 16;
				lpPlayInfo->dwSkill_SparkShield_Param |= (Spark_Shield_Damage[point] * Spark_Damage[lpTransCommand->SParam - 1][1]) / 100;
			}
			else
				lpPlayInfo->dwSkill_SparkShield_Param = 0;
			break;
			//´ÅÐÔÇòÌå
		case SKILL_PLAY_MAGNETIC_SPHERE:
			lpPlayInfo->dwSkill_MagneticSphere_Time = SERVER_GAMETIME + Magnetic_Sphere_Time[point] * 1000;
			lpPlayInfo->dwSkill_MagneticSphere_Param = point;
			break;
			//ÖÕ¼«»úÐµ
		case SKILL_PLAY_METAL_GOLEM:
			lpChar = SERVERMAP->CreateUnitByID(SKILLPLAYID_T44, lpPlayInfo->sPosition.iX, lpPlayInfo->sPosition.iY, lpPlayInfo->sPosition.iZ, lpPlayInfo, NULL);
			if (lpChar)
			{
				lpChar->dwLastUpdateTime = SERVER_GAMETIME + 355 * 1000;
				lpChar->sCharacterData.iMinDamage = Metal_Golem_Damage[point][0];
				lpChar->sCharacterData.iMaxDamage = Metal_Golem_Damage[point][1];
				lpChar->sCharacterData.iAttackRating = Metal_Golem_Hit[point];
				lpChar->sCharacterData.iDefenseRating = Metal_Golem_Defense[point];
				lpChar->sCharacterData.sHP.sMin = Metal_Golem_Life[point] + lpPlayInfo->sCharacterData.iStrength * 2;
				lpChar->sCharacterData.sHP.sMax = lpChar->sCharacterData.sHP.sMin;
				lpChar->sMoveStepCount[0] = 1;
				lpChar->sMoveStepCount[1] = 2;
				lpChar->sCharacterData.sSize = fONE + point * 15;
			}
			break;
		}
		break;
	case CHARACTERCLASS_Archer:
		switch (dwSkillCode)
		{
			//Áé»êÖ®Ó¥
		case SKILL_PLAY_FALCON:
			lpPlayInfo->dwSKill_Falcon_Time = SERVER_GAMETIME + Falcon_Time[point] * 1000;
			lpPlayInfo->dwSKill_Falcon_Damage[0] = Falcon_Damage[point][0];
			lpPlayInfo->dwSKill_Falcon_Damage[1] = Falcon_Damage[point][1];
			break;
			//»Æ½ðÁÔÓ¥
		case SKILL_PLAY_GOLDEN_FALCON:
			if (lpTransCommand->SParam > 0 && lpTransCommand->SParam <= 10)
			{
				lpPlayInfo->dwSKill_Falcon_Time = SERVER_GAMETIME + Golden_Falcon_Time[point] * 1000;
				lpPlayInfo->dwSKill_Falcon_Damage[0] = Falcon_Damage[lpTransCommand->SParam - 1][0];
				lpPlayInfo->dwSKill_Falcon_Damage[1] = Falcon_Damage[lpTransCommand->SParam - 1][1];
				lpPlayInfo->dwSKill_Falcon_Damage[0] = (lpPlayInfo->dwSKill_Falcon_Damage[0] * Golden_Falcon_Damage[point]) / 100;
				lpPlayInfo->dwSKill_Falcon_Damage[1] = (lpPlayInfo->dwSKill_Falcon_Damage[1] * Golden_Falcon_Damage[point]) / 100;
			}
			break;
			//ÕÙ»½Ñ©ÀÇ
		case SKILL_PLAY_RECALL_WOLVERIN:
			lpChar = SERVERMAP->CreateUnitByID(SKILLPLAYID_T41, lpPlayInfo->sPosition.iX, lpPlayInfo->sPosition.iY, lpPlayInfo->sPosition.iZ, lpPlayInfo, NULL);
			if (lpChar)
			{
				lpChar->dwLastUpdateTime = SERVER_GAMETIME + 355 * 1000;
				lpChar->sCharacterData.iMinDamage = Recall_Wolverin_Damage[point][0];
				lpChar->sCharacterData.iMaxDamage = Recall_Wolverin_Damage[point][1];
				lpChar->sCharacterData.iAttackRating = Recall_Wolverin_Hit[point];
				lpChar->sCharacterData.iDefenseRating = Recall_Wolverin_Defense[point] + lpPlayInfo->sCharacterData.iAgility * 2;
				lpChar->sCharacterData.sHP.sMin = Recall_Wolverin_Life[point];
				lpChar->sCharacterData.sHP.sMax = Recall_Wolverin_Life[point];
				lpChar->sMoveStepCount[0] = 1;
				lpChar->sMoveStepCount[1] = 2;
				lpChar->sCharacterData.sSize = (fONE / 2) + point * 12;
			}
			break;
			//×ÔÈ»Ö®¹â
		case SKILL_PLAY_FORCE_OF_NATURE:
			lpPlayInfo->dwSkill_ForceOfNature_Time = SERVER_GAMETIME + Force_Of_Nature_Time[point] * 1000;
			lpPlayInfo->wSkill_ForceOfNature_Param[0] = Force_Of_Nature_AddDamage[point];
			lpPlayInfo->wSkill_ForceOfNature_Param[1] = Force_Of_Nature_FalconAddDamage[point];
			size = 300 * 300;
			for (cnt = 0; cnt < PLAYERS_MAX; cnt++)
			{
				User * u = USERSDATA + cnt;

				if (u && u->iID && lpPlayInfo != u && u->iMapID == lpPlayInfo->iMapID &&
					(u->iMapID != MAPID_BlessCastle || (u->iClanID && u->iClanID == lpPlayInfo->iClanID)))
				{
					x = (lpPlayInfo->sPosition.iX - u->sPosition.iX) >> FLOATNS;
					y = (lpPlayInfo->sPosition.iY - u->sPosition.iY) >> FLOATNS;
					z = (lpPlayInfo->sPosition.iZ - u->sPosition.iZ) >> FLOATNS;
					dist = x * x + z * z;
					if (dist < size && abs(y) < 80)
					{
						u->dwSkill_ForceOfNature_Time = SERVER_GAMETIME + Force_Of_Nature_Time[point] * 1000;
						u->wSkill_ForceOfNature_Param[0] = Force_Of_Nature_AddDamage[point] / 2;
						u->wSkill_ForceOfNature_Param[1] = Force_Of_Nature_FalconAddDamage[point];
						lpTransCommand->EParam = CHARACTERCLASS_Archer;

						SENDPACKET(u, lpTransCommand);
					}
				}
			}
			break;
		}
		break;
	case CHARACTERCLASS_Pikeman:
		switch (dwSkillCode)
		{
			//Òþ°µÖ®Êõ
		case SKILL_PLAY_VANISH:
			lpPlayInfo->dwVanishEndTime = SERVER_GAMETIME + Vanish_Time[point] * 1000;
			lpPlayInfo->saVanishParam[0] = Vanish_Range[point];
			lpPlayInfo->saVanishParam[1] = Vanish_Damage[point];
			break;
			//°µÉ±Ö®ÑÛ
		case SKILL_PLAY_ASSASSIN_EYE:
			lpPlayInfo->dwSkill_AssassinEye_Time = SERVER_GAMETIME + Assassin_Eye_Time[point] * 1000;
			lpPlayInfo->dwSkill_AssassinEye_Param = point;
			break;
			//Ó°ÒþÖ®¶Ý
		case SKILL_PLAY_VAGUE:
			lpPlayInfo->dwSkill_Vague_Time = SERVER_GAMETIME + Vague_Time[point] * 1000;
			lpPlayInfo->dwSkill_Vague_Param = point;
			break;
			//Ç±ÄÜ¼¤·¢
		case SKILL_PLAY_AMPLIFIED:
			lpPlayInfo->dwSkill_Amplified_Time = SERVER_GAMETIME + Amplified_Time[point] * 1000;
			lpPlayInfo->dwSkill_Amplified_Param = point;
			break;
		}
		break;
	case CHARACTERCLASS_Atalanta:
		switch (dwSkillCode)
		{
			//Õ½ÀõÅØÏø
		case SKILL_PLAY_TRIUMPH_OF_VALHALLA:
			if (lpPlayInfo->sCharacterData.iLevel > 0 && lpPlayInfo->sCharacterData.iLevel < UNIT_LEVEL_MAX)
				lv = lpPlayInfo->sCharacterData.iLevel / 4;
			else
				lv = 0;
			if (!lpTransCommand->SParam)
			{
				lpPlayInfo->dwSkill_TriumphOfValhalla_Time = SERVER_GAMETIME + (T_Of_Valhalla_Time[point] * 1000);
				lpPlayInfo->dwSkill_TriumphOfValhalla_Param = T_Of_Valhalla_Damage[point] + lv;
				lpPlayInfo->dwSkill_HallOfValhalla_Time = 0;
			}
			else
			{
				lpPlayInfo2 = SERVERUSER->GetUser(lpTransCommand->SParam);
				if (lpPlayInfo2)
				{
					if (lpPlayInfo2->dwSkill_HallOfValhalla_Time < SERVER_GAMETIME)
					{
						lpPlayInfo2->dwSkill_TriumphOfValhalla_Time = SERVER_GAMETIME + (T_Of_Valhalla_Time[point] * 1000);
						lpPlayInfo2->dwSkill_TriumphOfValhalla_Param = (T_Of_Valhalla_Damage[point] + lv) / 2;
						lpTransCommand->SParam = lpPlayInfo->sCharacterData.iLevel;
						lpTransCommand->EParam = CHARACTERCLASS_Atalanta;

						SENDPACKET(lpPlayInfo2, lpTransCommand);
					}
				}
			}
			break;
			//Íß¶û¹þÀ­Ö®¹â
		case SKILL_PLAY_HALL_OF_VALHALLA:
			int TempPoint;

			TempPoint = lpTransCommand->SParam;
			if (TempPoint > 10) break;
			if (lpPlayInfo->sCharacterData.iLevel > 0 && lpPlayInfo->sCharacterData.iLevel < UNIT_LEVEL_MAX)
			{
				lv = lpPlayInfo->sCharacterData.iLevel / 4;
				lpTransCommand->SParam = lpPlayInfo->sCharacterData.iLevel;
			}
			else
			{
				lv = 0;
				lpTransCommand->SParam = 1;
			}
			lpTransCommand->SParam |= (TempPoint << 8);

			lpPlayInfo->dwSkill_HallOfValhalla_Time = SERVER_GAMETIME + Hall_Of_Valhalla_Time[point] * 1000;
			lpPlayInfo->wSkill_HallOfValhalla_Param[0] = Hall_Of_Valhalla_AddEvation[point];
			lpPlayInfo->wSkill_HallOfValhalla_Param[1] = T_Of_Valhalla_Damage[TempPoint - 1] + lv;
			lpPlayInfo->dwSkill_TriumphOfValhalla_Time = 0;

			size = 350 * 350;
			for (cnt = 0; cnt < PLAYERS_MAX; cnt++)
			{
				User * u = USERSDATA + cnt;

				if (u && u->iID && lpPlayInfo != u && u->iMapID == lpPlayInfo->iMapID &&
					(u->iMapID != MAPID_BlessCastle || (u->iClanID && u->iClanID == lpPlayInfo->iClanID)))
				{
					x = (lpPlayInfo->sPosition.iX - u->sPosition.iX) >> FLOATNS;
					y = (lpPlayInfo->sPosition.iY - u->sPosition.iY) >> FLOATNS;
					z = (lpPlayInfo->sPosition.iZ - u->sPosition.iZ) >> FLOATNS;

					dist = x * x + z * z;
					if (dist < size && abs(y) < 80)
					{
						if (u->dwSkill_TriumphOfValhalla_Time < SERVER_GAMETIME)
						{
							u->dwSkill_HallOfValhalla_Time = SERVER_GAMETIME + Hall_Of_Valhalla_Time[point] * 1000;
							u->wSkill_HallOfValhalla_Param[0] = Hall_Of_Valhalla_AddEvation[point] / 2;
							u->wSkill_HallOfValhalla_Param[1] = (T_Of_Valhalla_Damage[TempPoint - 1] + lv) / 2;
							lpTransCommand->EParam = CHARACTERCLASS_Atalanta;

							SENDPACKET(u, lpTransCommand);
						}
					}
				}
			}
			break;
			//Ëª¶³±êÇ¹
		case SKILL_PLAY_FROST_JAVELIN:
			lpPlayInfo->dwSkill_FrostJavelin_Time = SERVER_GAMETIME + Frost_Javelin_Time[point] * 1000;
			lpPlayInfo->dwSkill_FrostJavelin_Param = point;
			break;
			//±¿±¿ÐÜ
		case SKILL_PLAY_S_ARCUDA:
			lpChar = SERVERMAP->CreateUnitByID(SKILLPLAYID_T53, lpPlayInfo->sPosition.iX, lpPlayInfo->sPosition.iY, lpPlayInfo->sPosition.iZ, lpPlayInfo, NULL);
			if (lpChar)
			{
				lpChar->dwLastUpdateTime = SERVER_GAMETIME + 355 * 1000;
				lpChar->sCharacterData.iMinDamage = S_Arcuda_Damage[point][0];
				lpChar->sCharacterData.iMaxDamage = S_Arcuda_Damage[point][1];
				lpChar->sCharacterData.iAttackRating = S_Arcuda_AtkRating[point];
				lpChar->sCharacterData.iDefenseRating = S_Arcuda_Defanse[point] + lpPlayInfo->sCharacterData.iAgility * 2;
				lpChar->sCharacterData.sHP.sMin = S_Arcuda_PetHp[point];
				lpChar->sCharacterData.sHP.sMax = S_Arcuda_PetHp[point];
				lpChar->sMoveStepCount[0] = 1;
				lpChar->sMoveStepCount[1] = 2;
				lpChar->sCharacterData.sSize = fONE + point * 12;
			}
			break;
		}
		break;
	case CHARACTERCLASS_Knight:
		switch (dwSkillCode)
		{
			//Ê¥¹â»¤Ìå
		case SKILL_PLAY_HOLY_BODY:
			lpPlayInfo->dwSkill_HolyBody_Time = SERVER_GAMETIME + HolyBody_Time[point] * 1000;
			lpPlayInfo->dwSkill_HolyBody_Param = HolyBody_Absorb[point];
			break;
			//Ê¥ÁéÖ®Îü
		case SKILL_PLAY_DIVINE_INHALATION:
			lpPlayInfo->dwSkill_DivineInhalation_Time = SERVER_GAMETIME + D_Inhalation_Time[point] * 1000;
			lpPlayInfo->dwSkill_DivineInhalation_Param = point;
			break;
			//¾´ÉñÖ®¶Ü
		case SKILL_PLAY_GODLY_SHIELD:
			lpPlayInfo->dwSkill_GodlyShied_Time = SERVER_GAMETIME + Godly_Shield_Time[point] * 1000;
			lpPlayInfo->dwSkill_GodlyShied_Param = point;
			break;
			//ÉÏµÛ×£¸£
		case SKILL_PLAY_GODS_BLESS:
			lpPlayInfo->dwSkill_GodsBless_Time = SERVER_GAMETIME + God_Bless_Time[point] * 1000;
			lpPlayInfo->dwSkill_GodsBless_Param = God_Bless_AddDamage[point];
			break;
			//ÍöÁéÖ®Öä
		case SKILL_PLAY_H_BENEDIC:
			if (lpTransCommand->SParam)
			{
				lpPlayInfo2 = SERVERUSER->GetUser(lpTransCommand->SParam);

				if (lpPlayInfo2 && lpPlayInfo2 != lpPlayInfo)
				{
					if (rand() % 100 < H_Benedic_Hit[point])
					{
						lpPlayInfo2->dwSkill_Benedic_Time = SERVER_GAMETIME + H_Benedic_Time[point] * 1000;
						lpTransCommand->EParam = CHARACTERCLASS_Knight;

						SENDPACKET(lpPlayInfo2, lpTransCommand);
					}
				}
				if (lpPlayInfo2 == NULL)
				{
					lpChar = SERVERUNIT->GetUnit(lpTransCommand->SParam, lpPlayInfo->iMapID);

					if (lpChar)
					{
						if (lpChar->sCharacterData.iMonsterType != MONSTERTYPE_Undead)
						{
							int pow = lpChar->sCharacterData.sElementalDef[sITEMINFO_BIONIC];

							if (pow < 0)
								pow = 0;
							if (pow > 100)
								pow = 100;
							pow = 100 - pow;

							pow = (H_Benedic_Hit[point] * pow) / 100;

							if (rand() % 100 < pow)
							{
								lpChar->HoSkillDeathTime = SERVER_GAMETIME + H_Benedic_Time[point] * 1000;
								lpTransCommand->EParam = CHARACTERCLASS_Knight;

								SENDPACKET(lpPlayInfo, lpTransCommand);
							}
						}
					}
				}
			}

			break;
		}
		break;
	case CHARACTERCLASS_Magician:
		switch (dwSkillCode)
		{
			//ÔªËØÖ®Êõ
		case SKILL_PLAY_ENCHANT_WEAPON:
			lpPlayInfo2 = SERVERUSER->GetUser(lpTransCommand->SParam);
			if (lpPlayInfo2)
			{
				lpPlayInfo2->dwSkill_EnchantWeapon_Time = SERVER_GAMETIME + Enchant_Weapon_Time[point] * 1000;
				lpPlayInfo2->dwSkill_EnchantWeapon_Param = (point + 1) | (lpTransCommand->EParam << 8);
				if (lpPlayInfo2 != lpPlayInfo)
				{
					lpTransCommand->SParam = lpTransCommand->EParam;
					lpTransCommand->EParam = CHARACTERCLASS_Magician;

					SENDPACKET(lpPlayInfo2, lpTransCommand);
				}
			}
			break;
			//Ä§·¨ÊØ»¤
		case SKILL_PLAY_ENERGY_SHIELD:
			lpPlayInfo->dwSkill_EnergyShield_Time = SERVER_GAMETIME + Energy_Shield_Time[point] * 1000;
			lpPlayInfo->dwSkill_EnergyShield_Param = Energy_Shield_DecDamage[point];
			break;
			//Áé»êÕÙ»½
		case SKILL_PLAY_SPIRIT_ELEMENTAL:
			if (lpPlayInfo->dwSkill_T_Anima_Time)
			{
				lpPlayInfo->dwSkill_T_Anima_Time = 0;
				lpPlayInfo->dwSkill_T_Anima_Param = 0;
			}
			lpPlayInfo->dwSkill_SpiritElemental_Time = SERVER_GAMETIME + Spirit_Elemental_Time[point] * 1000;
			lpPlayInfo->dwSkill_SpiritElemental_Param = Spirit_Elemental_Damage[point];
			break;
			//ÔªËØÖ®½£
		case SKILL_PLAY_DANCING_SWORD:
			lpPlayInfo->dwSkill_DancingSword_Time = SERVER_GAMETIME + Dancing_Sword_Time[point] * 1000;
			lpPlayInfo->dwSkill_DancingSword_Param = (lpTransCommand->SParam) | (point << 16);
			lpPlayInfo->dwSkill_DancingSword_DelayTime = 0;
			break;
			//ÒÁ·òÁÐÌØ
		case SKILL_PLAY_FIRE_ELEMENTAL:
			lpChar = SERVERMAP->CreateUnitByID(SKILLPLAYID_T41, lpPlayInfo->sPosition.iX, lpPlayInfo->sPosition.iY, lpPlayInfo->sPosition.iZ, lpPlayInfo, NULL);
			if (lpChar)
			{
				lpChar->dwLastUpdateTime = SERVER_GAMETIME + 355 * 1000;
				lpChar->sCharacterData.iMinDamage = Fire_Elemental_Damage[point][0];
				lpChar->sCharacterData.iMaxDamage = Fire_Elemental_Damage[point][1];
				lpChar->sCharacterData.iAttackRating = Fire_Elemental_Hit[point];
				lpChar->sCharacterData.sHP.sMin = Fire_Elemental_Life[point];
				lpChar->sCharacterData.sHP.sMax = Fire_Elemental_Life[point];
				lpChar->sMoveStepCount[0] = 1;
				lpChar->sMoveStepCount[1] = 2;
			}
			break;
			//ÉñÊ¥·¨Õó
		case SKILL_PLAY_T_ANIMA:
			lpPlayInfo->dwSkill_T_Anima_Time = SERVER_GAMETIME + T_Anima_Time[point] * 1000;
			lpPlayInfo->dwSkill_T_Anima_Param = T_Anima_Dmage[point];

			if (lpPlayInfo->dwSkill_SpiritElemental_Time)
			{
				lpPlayInfo->dwSkill_SpiritElemental_Time = 0;
				lpPlayInfo->dwSkill_SpiritElemental_Param = 0;
			}
			lpPlayInfo->dwSkill_T_Anima_Time = SERVER_GAMETIME + T_Anima_Time[point] * 1000;
			if (lpTransCommand->SParam > 0 && lpTransCommand->SParam <= 10)
				lpPlayInfo->dwSkill_T_Anima_Param = T_Anima_Dmage[point] + Spirit_Elemental_Damage[lpTransCommand->SParam - 1];
			else
				lpPlayInfo->dwSkill_T_Anima_Param = T_Anima_Dmage[point];
			break;
		}
		break;
	case CHARACTERCLASS_Priestess:
		switch (dwSkillCode)
		{
			//ÉñÊ¥·´Éä
		case SKILL_PLAY_HOLY_REFLECTION:
			lpPlayInfo->dwSkill_HolyReflection_Time = SERVER_GAMETIME + Holy_Reflection_Time[point] * 1000;
			lpPlayInfo->dwSkill_HolyReflection_Param = Holy_Reflection_Return_Damage[point];
			break;
			//»ØÉúÖ®Êõ
		case SKILL_PLAY_RESURRECTION:
			if (lpTransCommand->SParam)
			{
				lpPlayInfo2 = SERVERUSER->GetUser(lpTransCommand->SParam);
				if (lpPlayInfo2)
				{
					if ((rand() % 100) < Resurrection_Percent[point])
					{
						if (lpPlayInfo2 != lpPlayInfo)
						{
							lpTransCommand->EParam = CHARACTERCLASS_Priestess;

							SENDPACKET(lpPlayInfo2, lpTransCommand);
						}
					}
				}
			}
			else
			{
				SERVERUNIT->ProcessPacketEffectResurrection(lpPlayInfo, lpPlayInfo->iID);
			}
			break;
			//ÉñÊ¥Ö®¹â
		case SKILL_PLAY_VIRTUAL_LIFE:
			if (!lpTransCommand->SParam)
			{
				lpPlayInfo->dwSkill_VirtualLife_Time = SERVER_GAMETIME + Virtual_Life_Time[point] * 1000;
				lpPlayInfo->dwSkill_VirtualLife_Param = Virtual_Life_Percent[point];
			}
			else
			{
				lpPlayInfo2 = SERVERUSER->GetUser(lpTransCommand->SParam);
				if (lpPlayInfo2 && lpPlayInfo2->dwSkill_VirtualLife_Time < SERVER_GAMETIME)
				{
					lpPlayInfo2->dwSkill_VirtualLife_Time = SERVER_GAMETIME + Virtual_Life_Time[point] * 1000;
					lpPlayInfo2->dwSkill_VirtualLife_Param = Virtual_Life_Percent[point];
					lpTransCommand->EParam = CHARACTERCLASS_Priestess;

					SENDPACKET(lpPlayInfo2, lpTransCommand);
				}
			}
			break;
			//ÔÙÉúÁìÓò
		case SKILL_PLAY_REGENERATION_FIELD:
			lpPlayInfo->dwSkill_RegenerationField_Time = SERVER_GAMETIME + Regeneration_Field_Time[point] * 1000;
			break;
			//ÉñÊ¥ÌìÊ¹
		case SKILL_PLAY_SUMMON_MUSPELL:
			lpPlayInfo->dwSkill_SummonMuspell_Time = SERVER_GAMETIME + Summon_Muspell_Time[point] * 1000;
			lpPlayInfo->dwSkill_SummonMuspell_Param = point;
			break;
			//ÌìÅ®É¢»¨
		case SKILL_PLAY_B_KRISHNA:
			lpPlayInfo->dwSkill_Krishna_Time = SERVER_GAMETIME + B_Krishna_Time[point] * 1000;
			lpPlayInfo->dwSkill_Krishna_Param = point;
			break;
		}
		break;
		// ´Ì¿Í
	case CHARACTERCLASS_Assassin:
		switch (dwSkillCode)
		{
			// ÖÂÃ¤
		case SKILL_PLAY_BLIND:
			lpPlayInfo->dwSkill_Blind_Time = SERVER_GAMETIME + Deception_Time[point] * 1000;
			lpPlayInfo->dwSkill_Blind_Param = point;
			break;
		}
		break;
		//ÈøÂú
	case CHARACTERCLASS_Shaman:
		switch (dwSkillCode)
		{
			//ÆíÓêÊ¦
		case SKILL_PLAY_RAINMAKER:
			lpPlayInfo->dwSkill_Rainmaker_Time = SERVER_GAMETIME + Rainmaker_Time[point] * 1000;
			lpPlayInfo->dwSkill_Rainmaker_Param = point;
			break;
			//ÊÈÑªÖ®Ò¹
		case SKILL_PLAY_CRIMSON_KNIGHT:
			lpChar = SERVERMAP->CreateUnitByID(SKILLPLAYID_T44, lpPlayInfo->sPosition.iX, lpPlayInfo->sPosition.iY, lpPlayInfo->sPosition.iZ, lpPlayInfo, NULL);
			if (lpChar)
			{
				lpChar->dwLastUpdateTime = SERVER_GAMETIME + 355 * 1000;
				lpChar->sCharacterData.iMinDamage = Crimson_Knight_Atk[point][0];
				lpChar->sCharacterData.iMaxDamage = Crimson_Knight_Atk[point][1];
				lpChar->sCharacterData.iAttackRating = Crimson_Knight_AtkRating[point];
				lpChar->sCharacterData.sHP.sMin = Crimson_Knight_PetHp[point];
				lpChar->sCharacterData.sHP.sMax = Crimson_Knight_PetHp[point];
				lpChar->sCharacterData.iDefenseRating = Crimson_Knight_Defanse[point];
				lpChar->sMoveStepCount[0] = 1;
				lpChar->sMoveStepCount[1] = 2;
				lpChar->sCharacterData.sSize = fONE + point * 12;
			}
		}
		break;
	}
	return TRUE;
}


//ÉñÊ¥·´Éä¼¼ÄÜ
int rsProcessAttack_SkillHolyReflection(User *lpPlayInfo, Unit *lpChar)
{
	int pow;
	smTRANS_COMMAND	smTransCommand;
	int rs;

	if (!lpPlayInfo->dwSkill_HolyReflection_Time) return TRUE;

	if (lpPlayInfo->dwSkill_HolyReflection_Time < SERVER_GAMETIME)
	{
		lpPlayInfo->dwSkill_HolyReflection_Time = 0;
		return TRUE;
	}

	if (lpChar->sCharacterData.iMonsterType != MONSTERTYPE_Undead) return TRUE;

	pow = GetRandomPos(lpChar->sCharacterData.iMinDamage, lpChar->sCharacterData.iMaxDamage);
	pow = (pow*lpPlayInfo->dwSkill_HolyReflection_Param) / 100;
	rs = lpChar->sCharacterData.sElementalDef[sITEMINFO_BIONIC];
	if (rs)
	{
		if (rs >= 100) rs = 100;
		if (rs <= -100) rs = -100;
		pow -= ((pow*rs) / 100);
	}
	pow -= (pow * lpChar->sCharacterData.iAbsorbRating) / 100;

	if (pow > 0)
	{
		lpChar->sCharacterData.sHP.sMin -= pow;

		if (lpChar->sCharacterData.sHP.sMin <= 0)
		{
			lpChar->SetMotionFromCode(ANIMATIONTYPE_Die);
			lpChar->pcKillerData = lpPlayInfo;
		}
	}
	if (lpPlayInfo)
	{
		smTransCommand.code = smTRANSCODE_PROCESS_SKILL;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = SKILL_PLAY_HOLY_REFLECTION;
		smTransCommand.LParam = pow;
		smTransCommand.SParam = 0;
		smTransCommand.EParam = lpPlayInfo->sCharacterData.iClass;

		SENDPACKET(lpPlayInfo, &smTransCommand);
	}
	return TRUE;
}

//Å¬·£ ¾÷µ¥ÀÌÆ® ÇÏ±â
int rsClanUpdate(User *lpPlayInfo, TRANS_CLAN_COMMAND_USER *lpTransClanUser)
{
	rsCLAN_INFOMATION	ClanInfomation;
	smTRANS_COMMAND		smTransCommand;
	int	cnt;
	User	*lpPlayInfo2;

	//Å¬·£¿ø Á¤º¸ ÇØµ¶
	if (RecvClanCommand(lpTransClanUser, ClanInfomation.ClanUserInfo) == TRUE) {
		ZeroMemory(&smTransCommand, sizeof(smTRANS_COMMAND));
		smTransCommand.code = smTRANSCODE_CLAN_UPDATE;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = lpPlayInfo->iID;

		for (cnt = 0; cnt < lpTransClanUser->UserCount; cnt++) {
			lpPlayInfo2 = FindUserFromCodeName(ClanInfomation.ClanUserInfo[cnt].szName, ClanInfomation.ClanUserInfo[cnt].dwSpeedSum);
			if (lpPlayInfo2) {

				SENDPACKET(lpPlayInfo2, &smTransCommand);
			}
		}
	}

	return TRUE;
}

//¾ßÈ£ µ¿ÀÛ ½ÇÇà
int rsRecvYahooMotion(User *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{
	int cnt;
	Map	*lpStgArea;
	Unit		*lpCharList[srCLAN_MONSTER_MAX];
	int			ClanMonCount = 0;
	int			ClanPoint;
	int			x, y, z, dist;


	if (lpPlayInfo->iClanID) 
	{
		lpStgArea = SERVERMAP->GetMap(lpPlayInfo->iMapID);

		if (lpStgArea)
		{
			for (cnt = 0; cnt < MAX_ALIVEMONSTERS; cnt++)
			{
				if (lpStgArea->pcaUnitData[cnt] &&
					lpStgArea->pcaUnitData[cnt]->sCharacterData.iClanID == lpPlayInfo->sCharacterData.iClanID)
				{
					if (ClanMonCount >= srCLAN_MONSTER_MAX)
						break;

					x = (lpPlayInfo->sPosition.iX - lpStgArea->pcaUnitData[cnt]->pX) >> FLOATNS;
					y = (lpPlayInfo->sPosition.iY - lpStgArea->pcaUnitData[cnt]->pY) >> FLOATNS;
					z = (lpPlayInfo->sPosition.iZ - lpStgArea->pcaUnitData[cnt]->pZ) >> FLOATNS;
					dist = x * x + y * y + z * z;

					if (dist < DIST_TRANSLEVEL_LOW)
						lpCharList[ClanMonCount++] = lpStgArea->pcaUnitData[cnt];
				}
			}

			if (ClanMonCount)
			{
				ClanPoint = (lpPlayInfo->sCharacterData.iLevel >> 2) / ClanMonCount;
				if (ClanPoint == 0) ClanPoint = 1;

				for (cnt = 0; cnt < ClanMonCount; cnt++) 
				{
					if (lpCharList[cnt]->sCharacterData.sHP.sMin > 0) 
					{
						lpCharList[cnt]->sCharacterData.sHP.sMin += ClanPoint;

						if (lpCharList[cnt]->sCharacterData.sHP.sMin > lpCharList[cnt]->sCharacterData.sHP.sMax)
							lpCharList[cnt]->sCharacterData.sHP.sMin = lpCharList[cnt]->sCharacterData.sHP.sMax;
					}
				}
			}
		}
	}

	return TRUE;
}

//ÁÖº¯ ¸ó½ºÅÍ¸¦ Ã£´Â´Ù
Unit *rsFindAroundMonster(Unit *lpChar, int RoundDist)
{
	Map	*lpStgArea;
	int cnt;
	int x, y, z, dist;
	int ddist2;

	ddist2 = RoundDist * RoundDist;

	lpStgArea = (Map *)lpChar->pcMapSpawn;
	if (lpStgArea) {
		for (cnt = 0; cnt < MAX_ALIVEMONSTERS; cnt++) {
			if (lpStgArea->pcaUnitData[cnt] && lpStgArea->pcaUnitData[cnt] != lpChar &&
				!lpStgArea->pcaUnitData[cnt]->PlayHolyPower[1] &&
				lpStgArea->pcaUnitData[cnt]->sCharacterData.sHP.sMin > 0) {

				x = (lpStgArea->pcaUnitData[cnt]->pX - lpChar->pX) >> FLOATNS;
				y = (lpStgArea->pcaUnitData[cnt]->pY - lpChar->pY) >> FLOATNS;
				z = (lpStgArea->pcaUnitData[cnt]->pZ - lpChar->pZ) >> FLOATNS;
				dist = x * x + z * z;

				if (abs(y) < 80 && dist < ddist2) {
					return lpStgArea->pcaUnitData[cnt];
				}
			}
		}
	}

	return NULL;
}



//ÁÖº¯ ¸ó½ºÅÍ¸¦ Ã£¾Æ µ¥¹ÌÁö °ø°Ý
Unit *rsSkillDamage_AroundMonster(Unit *lpChar)
{
	Map	*lpStgArea;
	int cnt;
	int x, y, z, dist;
	int ddist2;
	Unit *lpTargetChar;

	int RoundDist = lpChar->sUnitInfo.SkillRange;
	int	pw, pow;

	ddist2 = RoundDist * RoundDist;
	pow = GetRandomPos(lpChar->sUnitInfo.SkillDamage[0], lpChar->sUnitInfo.SkillDamage[1]);

	lpStgArea = (Map *)lpChar->pcMapSpawn;
	if (lpStgArea) {
		for (cnt = 0; cnt < MAX_ALIVEMONSTERS; cnt++) {
			if (lpStgArea->pcaUnitData[cnt] && lpStgArea->pcaUnitData[cnt] != lpChar && lpStgArea->pcaUnitData[cnt]->sCharacterData.sHP.sMin > 0) {

				x = (lpStgArea->pcaUnitData[cnt]->pX - lpChar->pX) >> FLOATNS;
				y = (lpStgArea->pcaUnitData[cnt]->pY - lpChar->pY) >> FLOATNS;
				z = (lpStgArea->pcaUnitData[cnt]->pZ - lpChar->pZ) >> FLOATNS;
				dist = x * x + z * z;

				if (abs(y) < 80 && dist < ddist2) {

					lpTargetChar = lpStgArea->pcaUnitData[cnt];

					if (lpChar->sCharacterData.iClanID != 0 &&
						lpChar->sCharacterData.iClanID == lpTargetChar->sCharacterData.iClanID) {
						pw = 0;
					}
					else {
						pw = pow;
						pw -= (pow*lpTargetChar->sCharacterData.iAbsorbRating) / 100;
					}

					if (pw > 0) 
					{
						lpTargetChar->sCharacterData.sHP.sMin -= pw;
						if (lpTargetChar->sCharacterData.sHP.sMin <= 0)
						{
							lpTargetChar->sCharacterData.sHP.sMin = 0;
							lpTargetChar->SetMotionFromCode(ANIMATIONTYPE_Die);
							if (lpChar->pcOwner && lpChar->pcOwner->pcSocketData && lpChar->pcOwner->iID && lpChar->pcOwner->iID == lpChar->sCharacterData.iOwnerID)
							{
								lpTargetChar->pcKillerData = lpChar->pcOwner;
								lpTargetChar->pcBellatraKiller = lpChar;
							}
							else 
							{
								if (lpChar->pcOwner)
								{
									lpChar->sCharacterData.sHP.sMin = 0;
									lpChar->SetMotionFromCode(ANIMATIONTYPE_Die);
								}
								else {
									lpChar->pcAttackTarget = 0;
								}
							}
						}
						else {
							if (lpTargetChar->psModelAnimation->iType != ANIMATIONTYPE_Die) {//<0x100 ) {
								lpTargetChar->SetMotionFromCode(ANIMATIONTYPE_Flinch);
							}
						}
					}
					//return lpStgArea->pcaUnitData[cnt];
				}
			}
		}
	}

	return NULL;
}

//ÁÖº¯ ¸ó½ºÅÍ¸¦ Ã£¾Æ ½ºÅ³ ( ¶óÅõ ÁÖº¯ ¸ó½ºÅÍ ½ºÅÏÁ¦°Å )
Unit *rsSkillMonster_AroundMonster(Unit *lpChar, int RoundDist)
{
	Map	*lpStgArea;
	int cnt;
	int x, y, z, dist;
	int ddist2;
	Unit *lpTargetChar;

	ddist2 = RoundDist * RoundDist;

	lpStgArea = (Map *)lpChar->pcMapSpawn;
	if (lpStgArea) {
		for (cnt = 0; cnt < MAX_ALIVEMONSTERS; cnt++) {
			if (lpStgArea->pcaUnitData[cnt] && lpStgArea->pcaUnitData[cnt] != lpChar && lpStgArea->pcaUnitData[cnt]->sCharacterData.sHP.sMin > 0) {

				x = (lpStgArea->pcaUnitData[cnt]->pX - lpChar->pX) >> FLOATNS;
				y = (lpStgArea->pcaUnitData[cnt]->pY - lpChar->pY) >> FLOATNS;
				z = (lpStgArea->pcaUnitData[cnt]->pZ - lpChar->pZ) >> FLOATNS;
				dist = x * x + z * z;

				if (abs(y) < 80 && dist < ddist2) {
					if (lpChar->sCharacterData.iMonsterEffectID == snCHAR_SOUND_RATOO) {		//¶óÅõ ÁÖº¯ ¸ó½ºÅÍ ½ºÅÏ Á¦°Å
						lpTargetChar = lpStgArea->pcaUnitData[cnt];
						lpTargetChar->iStunTimeLeft = 0;
					}
				}
			}
		}
	}

	return NULL;
}


int	rsPutItemToSystemLine(User *lpPlayInfo, DWORD dwItemCode)
{
	smTRANS_SYSTEM_COMMAND	TransSystemCommand;

	ZeroMemory(&TransSystemCommand, sizeof(smTRANS_SYSTEM_COMMAND));
	TransSystemCommand.code = smTRANSCODE_SYSTEM;
	TransSystemCommand.size = sizeof(smTRANS_SYSTEM_COMMAND);
	TransSystemCommand.tCode = smTRANS_SYSCODE_GET_ITEM;
	TransSystemCommand.dwObjectSerial = SERVER_CODE;
	TransSystemCommand.Param[0] = lpPlayInfo->iID;
	TransSystemCommand.Param[1] = dwItemCode;

	return FALSE;
}

int	rsPushKillMonster(Unit *lpChar, User *lpPlayInfo, Map *lpStgArea)
{
	int cnt;

	if (!dwSerToSerIP) return FALSE;

	if ((rsKillMonster_Push - rsKillMonster_Pop) >= srMONSTER_KILL_QUE_MASK) {


		return TRUE;
	}

	cnt = rsKillMonster_Push & srMONSTER_KILL_QUE_MASK;

	rsKillMonster_Que[cnt].dwAutoCharCode = lpChar->sUnitInfo.dwHashCharacterName;
	rsKillMonster_Que[cnt].dwCharSoundCode = lpChar->sCharacterData.iMonsterEffectID;
	rsKillMonster_Que[cnt].dwMonObjectSerial = lpChar->iID;

	rsKillMonster_Que[cnt].x = lpChar->pX;
	rsKillMonster_Que[cnt].y = lpChar->pY;
	rsKillMonster_Que[cnt].z = lpChar->pZ;

	rsKillMonster_Que[cnt].PartyFlag = lpChar->dwExclusiveNum;

	if (lpPlayInfo)
		rsKillMonster_Que[cnt].dwUserObjectSerial = lpPlayInfo->iID;
	else
		rsKillMonster_Que[cnt].dwUserObjectSerial = 0;

	if (lpStgArea && lpStgArea->pcBaseMap)
		rsKillMonster_Que[cnt].Area = lpStgArea->pcBaseMap->iMapID;
	else
		rsKillMonster_Que[cnt].Area = -1;


	rsKillMonster_Que[cnt].dwParam[0] = 0;
	rsKillMonster_Que[cnt].dwParam[1] = 0;
	rsKillMonster_Que[cnt].dwParam[2] = 0;
	rsKillMonster_Que[cnt].dwParam[3] = 0;

	if (rsKillMonster_Que[cnt].PartyFlag == rsHARDCORE_EVENT_FLAG) {
		rsKillMonster_Que[cnt].dwParam[0] = lpChar->iBellatraRoom;
	}

	rsKillMonster_Push++;

	return TRUE;
}


//¿î¿µÀÚ ¸í·É »ç¿ë±â·Ï
int	rsSaveAdminCommand(User *lpPlayInfo, char *szChatCommand, int Level)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];
	int		len;

	if (!lpPlayInfo->pcSocketData) return FALSE;

	CreateDirectory(AdminLogDirectory, NULL);			//µð·ºÅä¸® »ý¼º

	GetLocalTime(&st);


	wsprintf(szBuff, "%d:%d:%d - ID( %s ) Name( %s ) IP( %s ) AdminLv( %d )> %s\r\n",
		st.wHour, st.wMinute, st.wSecond,
		lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, Level, szChatCommand);

	len = lstrlen(szBuff);

	wsprintf(szFileName, "%s\\(Admin)%d-%d.log", AdminLogDirectory, st.wMonth, st.wDay);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, len, &dwAcess, NULL);
	CloseHandle(hFile);


	return TRUE;
}

//¿î¿µÀÚ ¸í·É »ç¿ë±â·Ï
int	rsRecordAdminCommand(User *lpPlayInfo, char *szChatCommand, int Level)
{
	TRANS_CHATMESSAGE	TransChatMessage;

	if (!rsServerConfig.RecordAdminCommand) return FALSE;
	if (Level > rsServerConfig.RecordAdminCommand) return FALSE;

	if (LoginServer) {
		rsSaveAdminCommand(lpPlayInfo, szChatCommand, lpPlayInfo->iGameLevel);
		return TRUE;
	}

	lstrcpy(TransChatMessage.szMessage, szChatCommand);
	TransChatMessage.dwIP = lpPlayInfo->iGameLevel;
	TransChatMessage.dwObjectSerial = lpPlayInfo->iID;
	TransChatMessage.size = lstrlen(TransChatMessage.szMessage) + 32;
	TransChatMessage.code = smTRANSCODE_REC_ADMIN_COMMAND;

	rsSendDataServer(lpPlayInfo, &TransChatMessage);

	return 0;
}

//¼ì²éGM½ÇÉ«
int	rsCheckAdminPlayer(User *lpPlayInfo)
{
	int cnt;

	if (!lpPlayInfo->AdminIP)
	{
		RecordDebugPlayLogFile(lpPlayInfo);

		if (rsServerConfig.DebugIP_Count > 0)
		{
			for (cnt = 0; cnt < rsServerConfig.DebugIP_Count; cnt++)
			{
				if (strstr(lpPlayInfo->pcSocketData->szIP, rsServerConfig.szDebugIP[cnt]) != 0)
					break;
			}

			if (cnt < rsServerConfig.DebugIP_Count)
				return TRUE;
			else
			{
				if (!lpPlayInfo->BlockTime)
					lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->szAccountName, 1000 * 60 * 60 * 24);

				//DisconnectUser(lpsmSock);
				return FALSE;
			}
		}

		if (rsServerConfig.DebugID_Count > 0)
		{
			for (cnt = 0; cnt < rsServerConfig.DebugID_Count; cnt++)
			{
				if (lstrcmpi(lpPlayInfo->szAccountName, rsServerConfig.szDebugID[cnt]) == 0)
					break;
			}

			if (cnt < rsServerConfig.DebugID_Count)
				return TRUE;
			else
			{
				if (!lpPlayInfo->BlockTime)
					lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->szAccountName, 1000 * 60 * 60 * 24);
				//DisconnectUser(lpsmSock);
				return FALSE;
			}
		}
	}

	return TRUE;
}

//Å¬·£ ¸Ó´Ï ±â·Ï
int	rsClanMoneyLog(User *lpPlayInfo, int Money, int RestMoney)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];
	int		len;

	if (!lpPlayInfo->pcSocketData) return FALSE;

	CreateDirectory(HackLogDirectory, NULL);			//µð·ºÅä¸® »ý¼º

	GetLocalTime(&st);


	wsprintf(szBuff, "%d:%d:%d - ID( %s ) Name( %s ) IP( %s ) Money( %d ) RestMoney( %d )\r\n",
		st.wHour, st.wMinute, st.wSecond,
		lpPlayInfo->szAccountName, lpPlayInfo->szCharacterName, lpPlayInfo->pcSocketData->szIP, Money, RestMoney);

	len = lstrlen(szBuff);

	wsprintf(szFileName, "%s\\(ClanMoney)%d-%d.log", HackLogDirectory, st.wMonth, st.wDay);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, len, &dwAcess, NULL);
	CloseHandle(hFile);


	return TRUE;
}


static int	TestStarPoint = 0;
#define	STAR_POINT_PRICE	100000

//º° Æ÷ÀÎÆ® °ü·Ã Ã³¸®
int rsRecvStarPoint(User *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{
	int cnt;
	int InvFlag;
	int	StarPoint = 0;
	TRANS_CHATMESSAGE	TransChatMessage;

	if (lpTransCommand->WParam > 0)
	{
		StarPoint = lpTransCommand->WParam / STAR_POINT_PRICE;

		if (lpTransCommand->LParam)
		{
			if (lpPlayInfo->GetGold() < lpTransCommand->WParam)
				return FALSE;

			SERVERUSER->SubServerUserGold(lpPlayInfo, lpTransCommand->WParam, WHEREID_StarPoint);

			rsRecord_ItemLog2(lpPlayInfo, sinGG1 | sin01, lpTransCommand->WParam, 0, ITEMLOG_BUYSTAR);
		}
		else
		{
			InvFlag = 0;

			for (cnt = 0; cnt < INVEN_ITEM_INFO_MAX; cnt++)
			{
				if (lpPlayInfo->InvenItemInfo[cnt].dwCode == (sinGF1 | sin01))
				{
					rsRecord_ItemLog2(lpPlayInfo, lpPlayInfo->InvenItemInfo[cnt].dwCode, lpPlayInfo->InvenItemInfo[cnt].dwKey, lpPlayInfo->InvenItemInfo[cnt].dwSum, ITEMLOG_BUYSTAR);

					lpPlayInfo->InvenItemInfo[cnt].dwCode = 0;
					InvFlag++;
				}
			}
			if (InvFlag == 0)
				return FALSE;
		}

		if (bSql_StarPoint(lpPlayInfo, StarPoint, lpTransCommand->LParam) == FALSE)
		{
			TestStarPoint += lpTransCommand->WParam / STAR_POINT_PRICE;
			lpTransCommand->WParam = TestStarPoint;

			SENDPACKET(lpPlayInfo, lpTransCommand);
		}

		if (StarPoint > 0)
		{
			TransChatMessage.code = smTRANSCODE_MESSAGEBOX;
			TransChatMessage.dwIP = 0;
			TransChatMessage.dwObjectSerial = 0;
			wsprintf(TransChatMessage.szMessage, "      Purchased %d stars     ", StarPoint);
			TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);

			SENDPACKET(lpPlayInfo, &TransChatMessage);
		}
	}
	else
	{
		if (bSql_StarPoint(lpPlayInfo, StarPoint, lpTransCommand->LParam) == FALSE)
		{
			lpTransCommand->WParam = TestStarPoint;

			SENDPACKET(lpPlayInfo, lpTransCommand);
		}
	}

	return TRUE;
}


static int	TestSodClanCash = 0;

int rsRecvSodClanCash(User *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{
	int cash, kind;

	cash = lpTransCommand->WParam;
	kind = lpTransCommand->SParam;

	if (cash > 0)
	{
		if (bSql_ClanMoney(lpPlayInfo, cash, 1, kind) == FALSE)
		{
			if (TestSodClanCash < cash)
				return FALSE;

			SERVERUSER->AddServerUserGold(lpPlayInfo, cash, WHEREID_ClanMoney);

			TestSodClanCash -= cash;

			lpTransCommand->WParam = TestSodClanCash;
			lpTransCommand->LParam = cash;

			rsClanMoneyLog(lpPlayInfo, cash, TestSodClanCash);

			SENDPACKET(lpPlayInfo, lpTransCommand);
		}
	}
	else
	{
		if (bSql_ClanMoney(lpPlayInfo, 0, 0, kind) == FALSE)
		{
			lpTransCommand->WParam = TestSodClanCash;
			lpTransCommand->LParam = 0;

			SENDPACKET(lpPlayInfo, lpTransCommand);
		}
	}

	return TRUE;
}
int rsRecvGiveMoney(User *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{
	TRANS_CHATMESSAGE	TransChatMessage;

	if (lpTransCommand->WParam > 0)
	{
		if (lpPlayInfo->GetGold() < lpTransCommand->WParam)
			return FALSE;

		SERVERUSER->SubServerUserGold(lpPlayInfo, lpTransCommand->WParam, WHEREID_GiveMoney);

		bSql_GiveMoney(lpPlayInfo, lpTransCommand->WParam);

		TransChatMessage.code = smTRANSCODE_MESSAGEBOX;
		TransChatMessage.dwIP = 0;
		TransChatMessage.dwObjectSerial = 0;
		wsprintf(TransChatMessage.szMessage, "      ¾èÔù %d        ", lpTransCommand->WParam);
		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);

		SENDPACKET(lpPlayInfo, &TransChatMessage);
	}

	return TRUE;
}
int rsRecvPaymentMoney(User *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{
	if (lpTransCommand->LParam < 0 || lpTransCommand->LParam>1000000)
		return FALSE;

	switch (lpTransCommand->WParam)
	{
	case 1:
		SERVERUSER->SubServerUserGold(lpPlayInfo, lpTransCommand->LParam, WHEREID_LearnSkill);
		break;
	case 2:
		SERVERUSER->SubServerUserGold(lpPlayInfo, lpTransCommand->LParam, WHEREID_WarpGate);
		break;
	}

	return TRUE;
}
int rsEventLogOn_Sucess(User *lpPlayInfo)
{
	smTRANS_COMMAND	smTransCommand;

	if ((lpPlayInfo->Bl_Meter&BIMASK_BIRTHDAY_USER) != 0)
	{
		if (rsServerConfig.Event_ComicBirthDay == 1)
			rsSendBigHeadToClient(lpPlayInfo, 60 * 24 * 6, (rand() % 2) + 1);
	}

	if ((lpPlayInfo->Bl_Meter&BIMASK_VIP_USER) != 0)
	{
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.code = smTRANSCODE_CHANGE_EVENT;
		smTransCommand.WParam = lpPlayInfo->Bl_Meter;
		smTransCommand.LParam = lpPlayInfo->Bl_RNo;
		smTransCommand.SParam = 0;
		smTransCommand.EParam = 1;

		SENDPACKET(lpPlayInfo, &smTransCommand);
	}

	return TRUE;
}

struct	sPUZZLE_ITEM
{
	DWORD	dwItemCode;
	int		Percent;
};

sPUZZLE_ITEM	sPuzzleItem[] =
{
	{	(sinPZ1 | sin01)	,	        743	}, //743
	{	(sinPZ1 | sin02)	,	       1466	}, //723
	{	(sinPZ1 | sin03)	,	       2170	}, //704

	{	(sinPZ2 | sin01)	,	       2913	}, //743
	{	(sinPZ2 | sin02)	,	       3636	}, //723
	{	(sinPZ2 | sin03)	,	       4340	}, //704

	{	(sinPZ1 | sin04)	,	       4990	}, //650
	{	(sinPZ1 | sin05)	,	       5290	}, //300
	{	(sinPZ2 | sin04)	,	       5940	}, //650
	{	(sinPZ2 | sin05)	,	       6240	}, //300

	{	(sinPZ1 | sin05)	,	       6590	}, //350
	{	(sinPZ1 | sin06)	,	       6940	}, //350
	{	(sinPZ2 | sin05)	,	       7290	}, //350
	{	(sinPZ2 | sin06)	,	       7640 }, //350

	{	(sinPZ1 | sin06)	,	       7940	}, //300
	{	(sinPZ1 | sin07)	,	       8320	}, //380
	{	(sinPZ2 | sin06)	,	       8620	}, //300
	{	(sinPZ2 | sin07)	,	       9000	}, //380

	{	(sinPZ1 | sin08)	,	       9500	}, //500
	{	(sinPZ2 | sin08)	,	       10000}, //500
	{	0,0	}
};
DWORD rsOpenEventPuzzleItem(User *lpPlayInfo, Unit *lpChar)
{
	int	cnt;
	int	rnd;

	if (abs(lpPlayInfo->sCharacterData.iLevel - lpChar->sCharacterData.iLevel) > 15)
		return NULL;		//·¹º§Â÷°¡ ¸¹ÀÌ ³ª¼­ ½ÇÆÐ

	if (lpChar->sCharacterData.iLevel < 20 && abs(lpPlayInfo->sCharacterData.iLevel - lpChar->sCharacterData.iLevel)>8)
		return NULL;		//·¹º§ 20 ¹Ì¸¸ ¸ó½ºÅÍ´Â ·¹º§Â÷ 5 ÀÌÇÏ ÀÏ¶§¸¸ Àû¿ë

	//SoD¿¡¼­´Â ÆÛÁñ ¾ÆÀÌÅÛ ¾È³ª¿Â´Ù
	if (lpChar->dwExclusiveNum == rsHARDCORE_EVENT_FLAG) return NULL;

	rnd = rand() % 10000;

	cnt = 0;
	while (1) {
		if (!sPuzzleItem[cnt].dwItemCode) break;

		if (rnd < sPuzzleItem[cnt].Percent)
			return sPuzzleItem[cnt].dwItemCode;

		cnt++;
	}

	return NULL;
}

//µð¹ö±× ¸Þ¼¼Áö Ãâ·Â
int rsDebugMessageToClient(User *lpPlayInfo, char *szDmgMsg)
{
	TRANS_CHATMESSAGE	TransChatMessage;

	if (lpPlayInfo->iGameLevel <= GAMELEVEL_Two) return FALSE;

	lstrcpy(TransChatMessage.szMessage, szDmgMsg);
	TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
	TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
	TransChatMessage.dwIP = 0;
	TransChatMessage.dwObjectSerial = 0;

	SENDPACKET(lpPlayInfo, &TransChatMessage);

	return TRUE;
}


//°³ÀÎ »óÁ¡ °Å·¡ Ã³¸®
int	rsTrade_PersonalShop(User *lpPlayInfo, User *lpPlayInfo2, smTRANS_COMMAND_BUFF *lpTransCommandBuff)
{
	sMYSHOP_ITEM_SERVER	*lpMyShopItem = (sMYSHOP_ITEM_SERVER *)lpTransCommandBuff->Buff;
	int	cnt, mCnt;
	int PotionFlag;

	switch (lpMyShopItem->SendFlag)
	{
	case 1:		//±¸¸Å ¿äÃ»
		if (lpMyShopItem->Price > 500000000)
			return FALSE;
		if (lpPlayInfo->dwMyShopTradeTime > SERVER_GAMETIME)
			return FALSE;

		PotionFlag = TRUE;

		if ((lpMyShopItem->CODE&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
		{
			if (rsGetServerPotion(lpPlayInfo2, lpMyShopItem->CODE) < (int)lpMyShopItem->sTime)
			{
				//¼­¹ö¹°¾à °¹¼ö ¿À·ù
				//rsServerPotionErrorLog( lpPlayInfo2 ,  lpMyShopItem->CODE , -(int)lpMyShopItem->sTime , 300 );
				PotionFlag = FALSE;
			}
		}

		if (SERVERITEM->IsItemInventory(lpPlayInfo2, lpMyShopItem->CODE, lpMyShopItem->Head, lpMyShopItem->CkSum) >= 0 && lpPlayInfo->GetGold() >= (int)lpMyShopItem->Price && PotionFlag == TRUE)
		{
			lpPlayInfo->dwMyShopTradeTime = SERVER_GAMETIME + 500;			//0.5ÃÊ ±¸ÀÔ Á¦ÇÑ ´ë±â

			if (lpPlayInfo->MyShopListCount == 0)
			{
				ZeroMemory(lpPlayInfo->sMyShopList, sizeof(sMYSHOP_SELL_INFO)*MYSHOP_LIST_MAX);
			}
			else
			{
				for (cnt = 0; cnt < MYSHOP_LIST_MAX; cnt++)
				{
					if (lpPlayInfo->sMyShopList[cnt].dwCode &&
						lpMyShopItem->CODE == lpPlayInfo->sMyShopList[cnt].dwCode &&
						lpMyShopItem->Head == lpPlayInfo->sMyShopList[cnt].dwHead &&
						lpMyShopItem->CkSum == lpPlayInfo->sMyShopList[cnt].dwChkSum &&
						lpMyShopItem->Price == lpPlayInfo->sMyShopList[cnt].Price)
					{
						return TRUE;
					}
				}
			}

			mCnt = lpPlayInfo->MyShopListCount&MYSHOP_LIST_MASK;
			lpPlayInfo->sMyShopList[mCnt].dwCode = lpMyShopItem->CODE;
			lpPlayInfo->sMyShopList[mCnt].dwHead = lpMyShopItem->Head;
			lpPlayInfo->sMyShopList[mCnt].dwChkSum = lpMyShopItem->CkSum;
			lpPlayInfo->sMyShopList[mCnt].Price = lpMyShopItem->Price;
			lpPlayInfo->MyShopListCount++;
			return TRUE;
		}

		if (lpPlayInfo->GetGold() >= (int)lpMyShopItem->Price)
		{
			lpTransCommandBuff->smTransCommand.LParam = lpPlayInfo2->iID;
			lpTransCommandBuff->smTransCommand.SParam = lpPlayInfo->iID;
			lpMyShopItem->SendFlag = 3;

			SENDPACKET(lpPlayInfo, lpTransCommandBuff);
		}
		return FALSE;

	case 2:
		if (lpMyShopItem->Price > 500000000)
			return FALSE;

		for (cnt = 0; cnt < MYSHOP_LIST_MAX; cnt++)
		{
			if (lpPlayInfo2->sMyShopList[cnt].dwCode &&
				lpMyShopItem->CODE == lpPlayInfo2->sMyShopList[cnt].dwCode &&
				lpMyShopItem->Head == lpPlayInfo2->sMyShopList[cnt].dwHead &&
				lpMyShopItem->CkSum == lpPlayInfo2->sMyShopList[cnt].dwChkSum &&
				lpMyShopItem->Price == lpPlayInfo2->sMyShopList[cnt].Price)
			{
				if (lpPlayInfo2->GetGold() >= (int)lpMyShopItem->Price)
				{
					if ((lpMyShopItem->CODE&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
					{
						if (SERVERITEM->AddPotion(lpPlayInfo, lpMyShopItem->CODE, -(int)(lpMyShopItem->sTime)) < 0)
						{
							rsServerPotionErrorLog(lpPlayInfo, lpMyShopItem->CODE, -(int)lpMyShopItem->sTime, 310);
							return FALSE;
						}
						SERVERITEM->AddPotion(lpPlayInfo2, lpMyShopItem->CODE, lpMyShopItem->sTime);
					}

					if (SERVERITEM->DeleteItemInventory(lpPlayInfo,
						lpMyShopItem->CODE,
						lpMyShopItem->Head,
						lpMyShopItem->CkSum))
					{
						SERVERUSER->SubServerUserGold(lpPlayInfo2, lpMyShopItem->Price, WHEREID_PersonalShop);
						SERVERUSER->AddServerUserGold(lpPlayInfo, lpMyShopItem->Price, WHEREID_PersonalShop);

						SERVERITEM->AddItemInventory(lpPlayInfo2, lpMyShopItem->CODE, lpMyShopItem->Head, lpMyShopItem->CkSum);

						if ((lpMyShopItem->CODE&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
							rsRecord_ItemLog_MyShop(lpPlayInfo, lpPlayInfo2, lpMyShopItem->CODE, lpMyShopItem->sTime, 0, lpMyShopItem->Price);
						else
							rsRecord_ItemLog_MyShop(lpPlayInfo, lpPlayInfo2, lpMyShopItem->CODE, lpMyShopItem->Head, lpMyShopItem->CkSum, lpMyShopItem->Price);

						return TRUE;
					}
				}
				break;
			}
		}
		return FALSE;
	}

	return TRUE;
}

//»ç¶ûÀÇ ¾ÆÀÌÅÛÀ» »ç¿ë
int	rsUseLovelyItem(User *lpPlayInfo, DWORD	dwItemCode)
{

	int	JobCode;
	int Level = 0;
	smTRANS_COMMAND	smTransCommand;

	JobCode = lpPlayInfo->sCharacterData.iClass;

	switch (dwItemCode)
	{
	case (sinCH1 | sin01):

		if (JobCode == CHARACTERCLASS_Atalanta || JobCode == CHARACTERCLASS_Archer || JobCode == CHARACTERCLASS_Priestess || JobCode == CHARACTERCLASS_Assassin)
			return FALSE;
		Level = 4;
		break;

	case (sinCH1 | sin02):

		if (JobCode == CHARACTERCLASS_Atalanta || JobCode == CHARACTERCLASS_Archer || JobCode == CHARACTERCLASS_Priestess || JobCode == CHARACTERCLASS_Assassin)
			return FALSE;
		Level = 8;

		break;

	case (sinCH1 | sin03):
		if (JobCode != CHARACTERCLASS_Atalanta && JobCode != CHARACTERCLASS_Archer && JobCode != CHARACTERCLASS_Priestess && JobCode != CHARACTERCLASS_Assassin)
			return FALSE;
		Level = 4;
		break;

	case (sinCH1 | sin04):
		if (JobCode != CHARACTERCLASS_Atalanta && JobCode != CHARACTERCLASS_Archer && JobCode != CHARACTERCLASS_Priestess && JobCode != CHARACTERCLASS_Assassin)
			return FALSE;
		Level = 8;
		break;

	}

	if (Level == 0) return FALSE;

	smTransCommand.code = smTRANSCODE_PROCESS_SKILL2;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = SKILL_PLAY_LOVELY_LIFE;
	smTransCommand.LParam = lpPlayInfo->iID;
	smTransCommand.SParam = 0;
	smTransCommand.EParam = 0;

	lpPlayInfo->dwSkill_VirtualLife_Time = SERVER_GAMETIME + Virtual_Life_Time[Level - 1] * 1000;
	lpPlayInfo->dwSkill_VirtualLife_Param = Virtual_Life_Percent[Level - 1];
	smTransCommand.WParam |= (Level << 8);
	rsSendCommandUser2(lpPlayInfo, &smTransCommand);

	return TRUE;
}

static int	Babel_LifeRegenTable[10][2] = {
	{	1800	,	2300	},
	{	1900	,	2400	},
	{	2000	,	2550	},
	{	2150	,	2650	},
	{	2300	,	2800	},
	{	2400	,	2900	},
	{	2500	,	3000	},
	{	2600	,	3100	},
	{	2700	,	3200	},
	{	2800	,	3300	}
};

//¸ó½ºÅÍ »ý¸í·Â Àç»ýÄ¡ ±¸ÇÏ´Â ÇÔ¼ö
int rsGetMonsterLifeRegen(Unit *lpChar)
{
	int cnt;

	Map	*lpStgArea = lpChar->pcMap;
	int x, y, z, dist;
	int NearUserCnt;
	int dRange;
	User	*lpDebugPlayInfo = 0;
	int	RegenLife;

	if (lpChar->sCharacterData.iMonsterEffectID == snCHAR_SOUND_BABEL) 
	{
		dRange = 260 * 260;		//Á¢±Ù Á¦ÇÑ °Å¸®
		NearUserCnt = 0;

		for (cnt = 0; cnt < PLAYERS_MAX; cnt++)
		{
			User * u = USERSDATA + cnt;

			if (u->pcSocketData && u->iID && u->iMapID == (EMapID)lpStgArea->pcBaseMap->iMapID)
			{
				x = (lpChar->pX - u->sPosition.iX) >> FLOATNS;
				y = (lpChar->pY - u->sPosition.iY) >> FLOATNS;
				z = (lpChar->pZ - u->sPosition.iZ) >> FLOATNS;

				dist = x * x + z * z;

				if (abs(y) < 60 && dist < dRange && abs(x) < TRANS_VIEW_LIMIT && abs(z) < TRANS_VIEW_LIMIT) 
				{
					NearUserCnt++;

					if (u->iGameLevel >= GAMELEVEL_Three)
						lpDebugPlayInfo = u;
				}
			}
		}

		cnt = 0;
		if (NearUserCnt > 6) {
			if (NearUserCnt > 15)
				cnt = 9;
			else
				cnt = NearUserCnt - 6;
		}

		if (lpChar->sCharacterData.sHP.sMin < (lpChar->sCharacterData.sHP.sMax / 5))
			RegenLife = Babel_LifeRegenTable[cnt][1];
		else
			RegenLife = Babel_LifeRegenTable[cnt][0];

		return RegenLife;
	}

	return 0;
}

//¹Ùº§ ÀÏ¹Ý°ø°Ý½Ã ½ºÅ³µµ °°ÀÌ Àû¿ë (¹üÀ§ÁöÁ¤)
int rsSendRangeDamage(Unit *lpChar, User *lpMainPlayInfo, int Range, int SubDamgePers)
{
	int cnt;
	Map	*lpStgArea = lpChar->pcMap;
	int x, y, z, dist;
	int dRange = Range * Range;
	int BackDamge[2];

	int		UserCount = 0;
	User	*lpUserList[16];

	int		sndUserCount = 0;
	User	*lpSndUserList[128];


	if (!lpStgArea || !lpStgArea->pcBaseMap) return FALSE;


	lpUserList[UserCount++] = lpMainPlayInfo;
	lpSndUserList[sndUserCount++] = lpMainPlayInfo;

	for (cnt = 0; cnt < PLAYERS_MAX; cnt++)
	{
		User * u = USERSDATA + cnt;

		if (u->pcSocketData && u->iID && u->iMapID == (EMapID)lpStgArea->pcBaseMap->iMapID && u != lpMainPlayInfo)
		{
			x = (lpMainPlayInfo->sPosition.iX - u->sPosition.iX) >> FLOATNS;
			y = (lpMainPlayInfo->sPosition.iY - u->sPosition.iY) >> FLOATNS;
			z = (lpMainPlayInfo->sPosition.iZ - u->sPosition.iZ) >> FLOATNS;
			dist = x * x + z * z;

			if (abs(y) < 60 && dist < dRange && abs(x) < TRANS_VIEW_LIMIT && abs(z) < TRANS_VIEW_LIMIT) 
			{
				if (UserCount < 16)
					lpUserList[UserCount++] = u;
			}

			if (dist < DIST_TRANSLEVEL_HIGH && abs(x) < TRANS_VIEW_LIMIT && abs(z) < TRANS_VIEW_LIMIT) 
			{
				if (sndUserCount < 128)
					lpSndUserList[sndUserCount++] = u;
			}

		}
	}

	BackDamge[0] = lpChar->sCharacterData.iMinDamage;
	BackDamge[1] = lpChar->sCharacterData.iMaxDamage;

	lpChar->sCharacterData.iMinDamage = (lpChar->sCharacterData.iMinDamage * SubDamgePers) / fONE;
	lpChar->sCharacterData.iMaxDamage = (lpChar->sCharacterData.iMaxDamage * SubDamgePers) / fONE;


	for (cnt = 0; cnt < UserCount; cnt++) {
		if (lpUserList[cnt] != lpMainPlayInfo)
			lpChar->SendTransAttack(0, lpUserList[cnt], 0);
	}


	lpChar->sCharacterData.iMinDamage = BackDamge[0];
	lpChar->sCharacterData.iMaxDamage = BackDamge[1];

	TRANS_SKIL_ATTACKDATA	TransSkillAttackData;
	ZeroMemory(&TransSkillAttackData, sizeof(TRANS_SKIL_ATTACKDATA));

	TransSkillAttackData.size = sizeof(TRANS_SKIL_ATTACKDATA) - (sizeof(DWORD)*(SKIL_ATTACK_CHAR_MAX - UserCount));
	if (UserCount > 0 && TransSkillAttackData.size > 32) {
		TransSkillAttackData.code = smTRANSCODE_ATTACK_SLASH_LIST;
		TransSkillAttackData.dwDestObjectSerial = lpChar->iID;
		TransSkillAttackData.TargetCount = UserCount;
		for (cnt = 0; cnt < UserCount; cnt++) {
			TransSkillAttackData.dwTarObjectSerial[cnt] = lpUserList[cnt]->iID;
		}
		for (cnt = 0; cnt < sndUserCount; cnt++) {

			SENDPACKET(lpSndUserList[cnt], &TransSkillAttackData);
		}
	}

	return TRUE;
}
int	rsMorifEventMessage(Unit *lpChar)
{
#ifdef _W_SERVER
	TRANS_CHATMESSAGE	TransChatMessage;
	char	*lpChatMsg = 0;

	if (lpChar->dwMessageEndTime > SERVER_GAMETIME)
		return FALSE;

	if (lpChar->psModelAnimation->iType == ANIMATIONTYPE_Die && lpChar->iFrameTimer > 40)
	{
		lpChatMsg = szMorifChatDropMsg[rand() % MORIF_CHAT_DROP_MAX];
		lpChar->dwMessageEndTime = SERVER_GAMETIME + 60 * 1000;
	}
	else
	{
		if ((rand() % 100) < 15)
			lpChatMsg = szMorifChatMsg[rand() % MORIF_CHAT_MAX];

		lpChar->dwMessageEndTime = SERVER_GAMETIME + 4 * 1000;
	}

	if (lpChar->pcFocusTarget && lpChatMsg)
	{
		wsprintf(TransChatMessage.szMessage, "%s: %s ", lpChar->sCharacterData.szName, lpChatMsg);
		TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
		TransChatMessage.dwIP = 0;
		TransChatMessage.dwObjectSerial = lpChar->iID;

		rsSendCommandUser2(lpChar->pcFocusTarget, (smTRANS_COMMAND *)&TransChatMessage);

		return TRUE;
	}
#endif
	return FALSE;
}

//ÀÌº¥Æ®¿ë ´Á´ë ´ë»ç
int	rsMollyWolfEventMessage(Unit *lpChar)
{
#ifdef _W_SERVER
	TRANS_CHATMESSAGE	TransChatMessage;
	char	*lpChatMsg = 0;

	if (lpChar->dwMessageEndTime > SERVER_GAMETIME) return FALSE;

	if (lpChar->psModelAnimation->iType == ANIMATIONTYPE_Die && lpChar->iFrameTimer > 40) {
		lpChatMsg = szMollyWolfChatDropMsg[rand() % MOLLYWOLF_CHAT_DROP_MAX];
		lpChar->dwMessageEndTime = SERVER_GAMETIME + 60 * 1000;		//60ÃÊÈÄ¿¡
	}
	else {
		if ((rand() % 100) < 15) {
			lpChatMsg = szMollyWolfChatMsg[rand() % MOLLYWOLF_CHAT_MAX];
		}
		lpChar->dwMessageEndTime = SERVER_GAMETIME + 4 * 1000;		//5ÃÊÈÄ¿¡
	}

	if (lpChar->pcFocusTarget && lpChatMsg) {

		wsprintf(TransChatMessage.szMessage, "%s: %s ", lpChar->sCharacterData.szName, lpChatMsg);
		TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
		TransChatMessage.dwIP = 0;
		TransChatMessage.dwObjectSerial = lpChar->iID;

		rsSendCommandUser2(lpChar->pcFocusTarget, (smTRANS_COMMAND *)&TransChatMessage);

		return TRUE;
	}
#endif
	return FALSE;
}


//¹ÚÀç¿ø - º¹³¯ ÀÌº¥Æ® ´ë»ç
int	rsChichenDayEventMessage(Unit *lpChar)
{
#ifdef _W_SERVER
	TRANS_CHATMESSAGE	TransChatMessage;
	char	*lpChatMsg = 0;

	if (lpChar->dwMessageEndTime > SERVER_GAMETIME) return FALSE;

	if (lpChar->psModelAnimation->iType == ANIMATIONTYPE_Die && lpChar->iFrameTimer > 40) {
		lpChatMsg = szPaPaChichenChatDropMsg[rand() % PAPACHICHEN_CHAT_DROP_MAX];
		lpChar->dwMessageEndTime = SERVER_GAMETIME + 60 * 1000;		//60ÃÊÈÄ¿¡
	}
	else
	{
		lpChatMsg = szPaPaChichenChatMsg[rand() % PAPACHICHEN_CHAT_MAX];
		lpChar->dwMessageEndTime = SERVER_GAMETIME + 4 * 1000;		//4ÃÊÈÄ¿¡
	}

	if (lpChar->pcFocusTarget && lpChatMsg) {

		wsprintf(TransChatMessage.szMessage, "%s: %s ", lpChar->sCharacterData.szName, lpChatMsg);
		TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
		TransChatMessage.dwIP = 0;
		TransChatMessage.dwObjectSerial = lpChar->iID;

		rsSendCommandUser2(lpChar->pcFocusTarget, (smTRANS_COMMAND *)&TransChatMessage);

		return TRUE;
	}
#endif
	return FALSE;
}


//Äù½ºÆ®¿ë ¸¶½ºÅÍ ´ë»ç
int	rsQuestMasterMessage(Unit *lpChar, User *lpPlayInfo)
{
#ifdef _W_SERVER
	TRANS_CHATMESSAGE	TransChatMessage;
	char	*lpChatMsg = 0;
	int x, z, dist;

	if (lpChar->dwMessageEndTime > SERVER_GAMETIME) return FALSE;
	if (lpChar->ActionPattern == 12) return FALSE;		//ÀüÅõ Á¾·á Áß¸³¸ðµå

	if ((rand() % 100) < 30) {
		switch (lpChar->sCharacterData.iMonsterEffectID) {
		case snCHAR_SOUND_NPC_SKILLMASTER:
			lpChatMsg = szSkillMasterChatMsg[rand() % SKILLMASTER_CHAT_MAX];
			break;
		case snCHAR_SOUND_NPC_MAGICMASTER:
			lpChatMsg = szMagicMasterChatMsg[rand() % MAGICMASTER_CHAT_MAX];
			break;
		}
	}

	lpChar->dwMessageEndTime = SERVER_GAMETIME + 4 * 1000;		//5ÃÊÈÄ¿¡

	if (lpChar && lpChatMsg) {

		x = (lpChar->pX - lpPlayInfo->sPosition.iX) >> FLOATNS;
		z = (lpChar->pZ - lpPlayInfo->sPosition.iZ) >> FLOATNS;
		dist = x * x + z * z;
		
		if (dist < DIST_TRANSLEVEL_LOW && abs(x) < TRANS_VIEW_LIMIT && abs(z) < TRANS_VIEW_LIMIT) {
			wsprintf(TransChatMessage.szMessage, "%s: %s ", lpChar->sCharacterData.szName, lpChatMsg);
			TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
			TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
			TransChatMessage.dwIP = 0;
			TransChatMessage.dwObjectSerial = lpChar->iID;

			SENDPACKET(lpPlayInfo, &TransChatMessage);
		}
		return TRUE;
	}
#endif
	return FALSE;
}

//»êÅ¸°íºí¸° ´ë»ç
int	rsSantaGoblinEventMessage(Unit *lpChar)
{
#ifdef _W_SERVER
	TRANS_CHATMESSAGE	TransChatMessage;
	char	*lpChatMsg = 0;

	if (lpChar->dwMessageEndTime > SERVER_GAMETIME) return FALSE;


	if (lpChar->psModelAnimation->iType == ANIMATIONTYPE_Die && lpChar->iFrameTimer > 40) {
		lpChar->dwMessageEndTime = SERVER_GAMETIME + 60 * 1000;		//60ÃÊÈÄ¿¡
		return FALSE;
	}
	else {
		if ((rand() % 100) < 15) {
			lpChatMsg = szSantaGoblinChatMsg[rand() % SANTAGOBLIN_CHAT_MAX];
		}
		lpChar->dwMessageEndTime = SERVER_GAMETIME + 4 * 1000;		//5ÃÊÈÄ¿¡
	}

	if (lpChar->pcFocusTarget && lpChatMsg) {

		wsprintf(TransChatMessage.szMessage, "%s: %s ", lpChar->sCharacterData.szName, lpChatMsg);
		TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
		TransChatMessage.dwIP = 0;
		TransChatMessage.dwObjectSerial = lpChar->iID;

		rsSendCommandUser2(lpChar->pcFocusTarget, (smTRANS_COMMAND *)&TransChatMessage);

		return TRUE;
	}
#endif
	return FALSE;
}


int rsSiegeItemSucess(User *lpPlayInfo, DWORD dwItemCode)
{
	smTRANS_COMMAND	smTransCommand;

	smTransCommand.code = smTRANSCODE_PROCESS_SKILL2;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = SKILL_PLAY_BLESS_SIEGE_ITEM;
	smTransCommand.LParam = lpPlayInfo->iID;
	smTransCommand.SParam = dwItemCode;
	smTransCommand.EParam = 0;

	SENDPACKET(lpPlayInfo, &smTransCommand);

	return TRUE;
}
// Ê¹ÓÃ´óÍ·Ò©Ë®
int rsSendBigHeadToClient(User *lpPlayInfo, DWORD Time, int Kind)
{
	smTRANS_COMMAND	smTransCommand;

	if (lpPlayInfo)
	{
		if (Time > (DWORD)SERVER_LOCATIME)
		{
			if (lpPlayInfo->cdwTime_BigHead == 0)
			{
				smTransCommand.size = sizeof(smTRANS_COMMAND);
				smTransCommand.code = smTRANSCODE_COMIC_SKIN;
				smTransCommand.WParam = Kind;
				smTransCommand.LParam = Time;
				smTransCommand.SParam = 0;
				smTransCommand.EParam = 0;

				SENDPACKET(lpPlayInfo, &smTransCommand);

				lpPlayInfo->cdwTime_BigHead = Time;
				lpPlayInfo->cBigHeadType = Kind;

				return TRUE;
			}
		}
		else
		{
			if (lpPlayInfo->cdwTime_BigHead != 0)
			{
				smTransCommand.size = sizeof(smTRANS_COMMAND);
				smTransCommand.code = smTRANSCODE_COMIC_SKIN;
				smTransCommand.WParam = 0;
				smTransCommand.LParam = 0;
				smTransCommand.SParam = 0;
				smTransCommand.EParam = 0;

				SENDPACKET(lpPlayInfo, &smTransCommand);

				lpPlayInfo->cdwTime_BigHead = 0;
				lpPlayInfo->cBigHeadType = 0;

				return TRUE;
			}
		}
	}

	return TRUE;
}
// Ê¹ÓÃÉúÃüÒ©Ë®
int rsSendLifeRegentoClient(User *lpPlayInfo, DWORD Time)
{
	smTRANS_COMMAND smTransCommand;

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = smTRANSCODE_VAMPRIC_CUSPID;
	smTransCommand.WParam = Time;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;
	smTransCommand.EParam = 0;

	SENDPACKET(lpPlayInfo, &smTransCommand);

	return TRUE;
}
// Ê¹ÓÃÄ§·¨Ò©Ë®
int rsSendManaRegentoClient(User *lpPlayInfo, DWORD Time)
{
	smTRANS_COMMAND smTransCommand;

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = smTRANSCODE_MANA_RECHARGING;
	smTransCommand.WParam = Time;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;
	smTransCommand.EParam = 0;

	SENDPACKET(lpPlayInfo, &smTransCommand);

	return TRUE;
}
int rsSendFruitToGame(User *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{
	smTRANS_COMMAND	smTransCommand;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = smTRANSCODE_FRUIT;
	smTransCommand.WParam = lpTransCommand->WParam ^ smTRANSCODE_FRUIT;
	smTransCommand.LParam = lpTransCommand->LParam ^ smTRANSCODE_FRUIT;
	smTransCommand.SParam = 0;
	smTransCommand.EParam = 0;

	SENDPACKET(lpPlayInfo, &smTransCommand);

	return 0;
}
// Ê¹ÓÃ·ï»Ë
int rsSendPhoenixToClient(User *lpPlayInfo, DWORD Time, int Kind)
{
	smTRANS_COMMAND smTransCommand;

	if (lpPlayInfo)
	{
		if (Time > (DWORD)SERVER_LOCATIME)
		{
			if (lpPlayInfo->cdwTime_PhenixPet == 0)
			{
				smTransCommand.size = sizeof(smTRANS_COMMAND);
				smTransCommand.code = smTRANSCODE_PHENIX_PET;
				smTransCommand.WParam = Time;
				smTransCommand.LParam = Kind;
				smTransCommand.SParam = 0;
				smTransCommand.EParam = 0;

				SENDPACKET(lpPlayInfo, &smTransCommand);

				lpPlayInfo->cdwTime_PhenixPet = Time;
				lpPlayInfo->cphenixPetType = Kind;

				return TRUE;
			}
		}
		else
		{
			if (lpPlayInfo->cdwTime_PhenixPet != 0)
			{
				smTransCommand.size = sizeof(smTRANS_COMMAND);
				smTransCommand.code = smTRANSCODE_PHENIX_PET;
				smTransCommand.WParam = 0;
				smTransCommand.LParam = 0;
				smTransCommand.SParam = 0;
				smTransCommand.EParam = 0;

				SENDPACKET(lpPlayInfo, &smTransCommand);

				lpPlayInfo->cdwTime_PhenixPet = 0;
				lpPlayInfo->cphenixPetType = 0;
			}

			return TRUE;
		}
	}

	return FALSE;
}

// BIÎïÆ·Ê¹ÓÃ
int	rsOpenSiegeCastleItem(DWORD dwItemCode, int x, int y, int z, User *lpPlayInfo)
{
	switch (dwItemCode)
	{
	case sinBI1 | sin05:
		lpPlayInfo->dwSiegeItem_Scroll_Time = SERVER_GAMETIME + 30 * 1000;
		lpPlayInfo->dwSiegeItem_Scroll_Code = dwItemCode;
		lpPlayInfo->dwSiegeItem_Scroll_Param = 2;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;
	case sinBI1 | sin06:
		lpPlayInfo->dwSiegeItem_Scroll_Time = SERVER_GAMETIME + 60 * 60 * 1000;
		lpPlayInfo->dwSiegeItem_Scroll_Code = dwItemCode;
		lpPlayInfo->dwSiegeItem_Scroll_Param = 15;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;
	case sinBI1 | sin07:
		lpPlayInfo->dwSiegeItem_Scroll_Time = SERVER_GAMETIME + 60 * 60 * 1000;
		lpPlayInfo->dwSiegeItem_Scroll_Code = dwItemCode;
		lpPlayInfo->dwSiegeItem_Scroll_Param = 15;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;
	case sinBI1 | sin09:
		return TRUE;
	case sinBI1 | sin19:
		rsSendLifeRegentoClient(lpPlayInfo, 60 * 60 * 3);
		return TRUE;
	case sinBI1 | sin20:
		rsSendLifeRegentoClient(lpPlayInfo, 60 * 60 * 6);
		return TRUE;
	case sinBI1 | sin81:
		return TRUE;
	case sinBI1 | sin86:
		return TRUE;
	case sinBI1 | sin87:
		return TRUE;
	case sinBI1 | sin88:
		return TRUE;
	case sinBI1 | sin21:
		rsSendManaRegentoClient(lpPlayInfo, 60 * 60 * 3);
		return TRUE;
	case sinBI1 | sin22:
		rsSendManaRegentoClient(lpPlayInfo, 60 * 60 * 6);
		return TRUE;
	case sinBI1 | sin82:
		return TRUE;
	case sinBI1 | sin12:
	case sinBI1 | sin13:
	case sinBI1 | sin14:
	case sinBI1 | sin15:
	case sinBI1 | sin78:
		return TRUE;
	case sinBI1 | sin95:
		if (lpPlayInfo->dwCaravan_Hopy == NULL)
			rsSetCaravanHopy(lpPlayInfo, ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_EXPUPx7, 1);
		return TRUE;
	case sinBI1 | sin96:
		return TRUE;
	case sinBI1 | sin97:
		return TRUE;
	case sinBI1 | sin98:
		return TRUE;
	case sinBI1 | sin99:
		return TRUE;
	case sinBI2 | sin38:
		return TRUE;
	case sinBI2 | sin39:
		return TRUE;
	case sinBI2 | sin40:
		return TRUE;
	case sinBI2 | sin41:
		return TRUE;
	case sinBI2 | sin42:
		return TRUE;
	case sinBI2 | sin43:
		return TRUE;
	case sinBI2 | sin44:
		return TRUE;
	case sinBI2 | sin45:
		return TRUE;
	case sinBI2 | sin46:
		return TRUE;
	case sinBI2 | sin47:
		return TRUE;
	case sinBI2 | sin58:
		return TRUE;
	case sinBI2 | sin60:
		return TRUE;
	case sinBI2 | sin69: //´©É½¼×Ò»¼Ò
		if (lpPlayInfo->dwCaravan_Hopy == NULL)
			rsSetCaravanHopy(lpPlayInfo, ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_EXPUPx7, 2);
		return TRUE;
	case sinBI2 | sin70: //²¼ÂíÐÜÒ»¼Ò
		if (lpPlayInfo->dwCaravan_Hopy == NULL)
			rsSetCaravanHopy(lpPlayInfo, ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_EXPUPx7, 3);
		return TRUE;
	case sinBI2 | sin71: //ºì¶À½ÇÊÞÒ»¼Ò
		if (lpPlayInfo->dwCaravan_Hopy == NULL)
			rsSetCaravanHopy(lpPlayInfo, ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_EXPUPx7, 4);
		return TRUE;
	case sinBI2 | sin72: //Ð¡ÂÌÈËÒ»¼Ò
		if (lpPlayInfo->dwCaravan_Hopy == NULL)
			rsSetCaravanHopy(lpPlayInfo, ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_EXPUPx7, 5);
		return TRUE;
	case sinBI2 | sin73: //°×ÍÃÒ»¼Ò
		if (lpPlayInfo->dwCaravan_Hopy == NULL)
			rsSetCaravanHopy(lpPlayInfo, ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_EXPUPx7, 6);
		return TRUE;
	case sinBI2 | sin74: //ºìÍÃÒ»¼Ò
		if (lpPlayInfo->dwCaravan_Hopy == NULL)
			rsSetCaravanHopy(lpPlayInfo, ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_EXPUPx7, 7);
		return TRUE;
	case sinBI2 | sin75:
		return TRUE;
	case sinBI2 | sin76:
		return TRUE;
	case sinBI2 | sin77: //Ñ±Â¹Ö®¼Ò
		if (lpPlayInfo->dwCaravan_Hopy == NULL)
			rsSetCaravanHopy(lpPlayInfo, ((DWORD)SERVER_LOCATIME) + PRIME_ITEM_TIME_EXPUPx7, 8);
		return TRUE;
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
		return TRUE;
	case sinBC1 | sin21:
		lpPlayInfo->dwLifeBooster_Code = dwItemCode;
		lpPlayInfo->dwLifeBooster_Time = SERVER_GAMETIME + BoosterItem_UseTime[0] * 1000;
		lpPlayInfo->dwLifeBooster_Data = BoosterItem_DataPercent[0];
		return TRUE;
	case sinBC1 | sin22:
		lpPlayInfo->dwLifeBooster_Code = dwItemCode;
		lpPlayInfo->dwLifeBooster_Time = SERVER_GAMETIME + BoosterItem_UseTime[1] * 1000;
		lpPlayInfo->dwLifeBooster_Data = BoosterItem_DataPercent[0];
		return TRUE;
	case sinBC1 | sin23:
		lpPlayInfo->dwLifeBooster_Code = dwItemCode;
		lpPlayInfo->dwLifeBooster_Time = SERVER_GAMETIME + BoosterItem_UseTime[2] * 1000;
		lpPlayInfo->dwLifeBooster_Data = BoosterItem_DataPercent[0];
		return TRUE;
	case sinBC1 | sin24:
		lpPlayInfo->dwManaBooster_Code = dwItemCode;
		lpPlayInfo->dwManaBooster_Time = SERVER_GAMETIME + BoosterItem_UseTime[0] * 1000;
		lpPlayInfo->dwManaBooster_Data = BoosterItem_DataPercent[1];
		return TRUE;
	case sinBC1 | sin25:
		lpPlayInfo->dwManaBooster_Code = dwItemCode;
		lpPlayInfo->dwManaBooster_Time = SERVER_GAMETIME + BoosterItem_UseTime[1] * 1000;
		lpPlayInfo->dwManaBooster_Data = BoosterItem_DataPercent[1];
		return TRUE;
	case sinBC1 | sin26:
		lpPlayInfo->dwManaBooster_Code = dwItemCode;
		lpPlayInfo->dwManaBooster_Time = SERVER_GAMETIME + BoosterItem_UseTime[2] * 1000;
		lpPlayInfo->dwManaBooster_Data = BoosterItem_DataPercent[1];
		return TRUE;
	case sinBC1 | sin27:
		lpPlayInfo->dwStaminaBooster_Code = dwItemCode;
		lpPlayInfo->dwStaminaBooster_Time = SERVER_GAMETIME + BoosterItem_UseTime[0] * 1000;
		lpPlayInfo->dwStaminaBooster_Data = BoosterItem_DataPercent[2];
		return TRUE;
	case sinBC1 | sin28:
		lpPlayInfo->dwStaminaBooster_Code = dwItemCode;
		lpPlayInfo->dwStaminaBooster_Time = SERVER_GAMETIME + BoosterItem_UseTime[1] * 1000;
		lpPlayInfo->dwStaminaBooster_Data = BoosterItem_DataPercent[2];
		return TRUE;
	case sinBC1 | sin29:
		lpPlayInfo->dwStaminaBooster_Code = dwItemCode;
		lpPlayInfo->dwStaminaBooster_Time = SERVER_GAMETIME + BoosterItem_UseTime[2] * 1000;
		lpPlayInfo->dwStaminaBooster_Data = BoosterItem_DataPercent[2];
		return TRUE;
	}

	if (lpPlayInfo->iMapID != MAPID_BlessCastle)
		return FALSE;

	switch (dwItemCode)
	{
	case sinBC1 | sin01:
		lpPlayInfo->dwSiegeItem_Scroll_Time = SERVER_GAMETIME + 30 * 1000;
		lpPlayInfo->dwSiegeItem_Scroll_Code = dwItemCode;
		lpPlayInfo->dwSiegeItem_Scroll_Param = 2;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case sinBC1 | sin02:
		lpPlayInfo->dwSiegeItem_Scroll_Time = SERVER_GAMETIME + 30 * 1000;
		lpPlayInfo->dwSiegeItem_Scroll_Code = dwItemCode;
		lpPlayInfo->dwSiegeItem_Scroll_Param = 5;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case sinBC1 | sin03:
		lpPlayInfo->dwSiegeItem_Scroll_Time = SERVER_GAMETIME + 30 * 1000;
		lpPlayInfo->dwSiegeItem_Scroll_Code = dwItemCode;
		lpPlayInfo->dwSiegeItem_Scroll_Param = 5;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case sinBC1 | sin04:
	case sinBC1 | sin05:
		return FALSE;

	case sinBC1 | sin06:
		lpPlayInfo->dwSiegeItem_Stone1_Time = SERVER_GAMETIME + 60 * 1000;
		lpPlayInfo->dwSiegeItem_Stone1_Code = snCHAR_SOUND_CASTLE_CRYSTAL_R;
		lpPlayInfo->dwSiegeItem_Stone1_Param = 50;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case sinBC1 | sin07:
		lpPlayInfo->dwSiegeItem_Stone1_Time = SERVER_GAMETIME + 60 * 1000;
		lpPlayInfo->dwSiegeItem_Stone1_Code = snCHAR_SOUND_CASTLE_CRYSTAL_B;
		lpPlayInfo->dwSiegeItem_Stone1_Param = 50;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case sinBC1 | sin08:
		lpPlayInfo->dwSiegeItem_Stone1_Time = SERVER_GAMETIME + 60 * 1000;
		lpPlayInfo->dwSiegeItem_Stone1_Code = snCHAR_SOUND_CASTLE_CRYSTAL_G;
		lpPlayInfo->dwSiegeItem_Stone1_Param = 50;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case sinBC1 | sin09:
		lpPlayInfo->dwSiegeItem_Stone2_Time = SERVER_GAMETIME + 60 * 1000;
		lpPlayInfo->dwSiegeItem_Stone2_Code = CHARACTERCLASS_Fighter;
		lpPlayInfo->dwSiegeItem_Stone2_Param = 5;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case sinBC1 | sin10:
		lpPlayInfo->dwSiegeItem_Stone2_Time = SERVER_GAMETIME + 60 * 1000;
		lpPlayInfo->dwSiegeItem_Stone2_Code = CHARACTERCLASS_Mechanician;
		lpPlayInfo->dwSiegeItem_Stone2_Param = 5;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case sinBC1 | sin11:
		lpPlayInfo->dwSiegeItem_Stone2_Time = SERVER_GAMETIME + 60 * 1000;
		lpPlayInfo->dwSiegeItem_Stone2_Code = CHARACTERCLASS_Pikeman;
		lpPlayInfo->dwSiegeItem_Stone2_Param = 5;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case sinBC1 | sin12:
		lpPlayInfo->dwSiegeItem_Stone2_Time = SERVER_GAMETIME + 60 * 1000;
		lpPlayInfo->dwSiegeItem_Stone2_Code = CHARACTERCLASS_Archer;
		lpPlayInfo->dwSiegeItem_Stone2_Param = 5;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case sinBC1 | sin13:
		lpPlayInfo->dwSiegeItem_Stone2_Time = SERVER_GAMETIME + 60 * 1000;
		lpPlayInfo->dwSiegeItem_Stone2_Code = CHARACTERCLASS_Knight;
		lpPlayInfo->dwSiegeItem_Stone2_Param = 5;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case sinBC1 | sin14:
		lpPlayInfo->dwSiegeItem_Stone2_Time = SERVER_GAMETIME + 60 * 1000;
		lpPlayInfo->dwSiegeItem_Stone2_Code = CHARACTERCLASS_Atalanta;
		lpPlayInfo->dwSiegeItem_Stone2_Param = 5;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case sinBC1 | sin15:
		lpPlayInfo->dwSiegeItem_Stone2_Time = SERVER_GAMETIME + 60 * 1000;
		lpPlayInfo->dwSiegeItem_Stone2_Code = CHARACTERCLASS_Magician;
		lpPlayInfo->dwSiegeItem_Stone2_Param = 5;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case sinBC1 | sin16:
		lpPlayInfo->dwSiegeItem_Stone2_Time = SERVER_GAMETIME + 60 * 1000;
		lpPlayInfo->dwSiegeItem_Stone2_Code = CHARACTERCLASS_Priestess;
		lpPlayInfo->dwSiegeItem_Stone2_Param = 5;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;
	case sinBC1 | sin17:
		lpPlayInfo->dwSiegeItem_Stone2_Time = SERVER_GAMETIME + 60 * 1000;
		lpPlayInfo->dwSiegeItem_Stone2_Code = CHARACTERCLASS_Assassin;
		lpPlayInfo->dwSiegeItem_Stone2_Param = 5;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;
	case sinBC1 | sin18:
		lpPlayInfo->dwSiegeItem_Stone2_Time = SERVER_GAMETIME + 60 * 1000;
		lpPlayInfo->dwSiegeItem_Stone2_Code = CHARACTERCLASS_Shaman;
		lpPlayInfo->dwSiegeItem_Stone2_Param = 5;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;
	}

	return TRUE;
}


//µØÍ¼´íÎó
int rsFault_PlayField(User *lpPlayInfo, int height)
{
	smTRANS_COMMAND_EX	smTransCommandEx;

	lpPlayInfo->sCheckPlayField_Count[1]++;

	if (lpPlayInfo->WarningCount < 10 && lpPlayInfo->sCheckPlayField_Count[1] >= 3)
	{
		smTransCommandEx.size = sizeof(smTRANS_COMMAND_EX);
		smTransCommandEx.code = smTRANSCODE_SET_BLACKLIST;
		smTransCommandEx.WParam = 8860;
		smTransCommandEx.LParam = lpPlayInfo->sPosition.iX / fONE;
		smTransCommandEx.SParam = lpPlayInfo->sPosition.iY / fONE;
		smTransCommandEx.EParam = lpPlayInfo->sPosition.iZ / fONE;
		smTransCommandEx.WxParam = lpPlayInfo->iMapID;
		smTransCommandEx.LxParam = height / fONE;
		smTransCommandEx.SxParam = 0;
		smTransCommandEx.ExParam = 0;

		rsSendDataServer(lpPlayInfo, &smTransCommandEx);
		lpPlayInfo->WarningCount++;

		lpPlayInfo->sCheckPlayField_Count[1] = 0;
	}

	return TRUE;
}

#define PRESENTITEM_LEVEL_MAX		4

#include "AutoDropItem.h"

//´Ù¸¥¼­¹ö¿¡¼­ÀÇ ¾÷µ¥ÀÌÆ®
int rsRecvUpdateServerParam(User *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{

	switch (lpTransCommand->WParam) {
	case smUPDATE_PARAM_LOWUSER_PRESENT:
		lpPlayInfo->sLowLevel_PresentItem[0] = lpTransCommand->LParam;
		lpPlayInfo->sLowLevel_PresentItem[1] = lpTransCommand->SParam;
		break;
	}

	return TRUE;
}

//±º¼·¿¡ ¾÷µ¥ÀÌÆ® Á¤º¸ º¸³¿
int	rsUpdateServerParam(User *lpPlayInfo, DWORD dwUpdateCode, int Param1, int Param2, int TargetMode)
{
	smTRANS_COMMAND	smTransCommand;

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = smTRANSCODE_UPDATE_SERVER_PARAM;
	smTransCommand.WParam = dwUpdateCode;
	smTransCommand.LParam = Param1;
	smTransCommand.SParam = Param2;
	smTransCommand.EParam = SERVER_CODE;

	if (lpPlayInfo->pcSocketData) {
		if (TargetMode)
			rsSendDataServer(lpPlayInfo, &smTransCommand);
		else
			rsSendGameServer(lpPlayInfo, &smTransCommand);
	}

	return NULL;
}


//Ãâ·Ñ·¢ËÍÎïÆ·¸øÓÃ»§ 
int rsStartUser_PresentItem(User *lpPlayInfo)
{
	TRANS_CHATMESSAGE TransChatMessage;
	DefinitionItem *lpDefItem = 0;

	switch (lpPlayInfo->dwStartUser_PresentItem_Count)
	{
	case 1:
		if (lpPlayInfo->sCharacterData.iClass == CHARACTERCLASS_Archer)
			lpDefItem = rsPutItem3(lpPlayInfo, (sinWS1 | sin01));
		else if (lpPlayInfo->sCharacterData.iClass == CHARACTERCLASS_Atalanta)
			lpDefItem = rsPutItem3(lpPlayInfo, (sinWT1 | sin01));
		else if (lpPlayInfo->sCharacterData.iClass == CHARACTERCLASS_Magician)
			lpDefItem = rsPutItem3(lpPlayInfo, (sinWM1 | sin01));
		else if (lpPlayInfo->sCharacterData.iClass == CHARACTERCLASS_Priestess)
			lpDefItem = rsPutItem3(lpPlayInfo, (sinWM1 | sin01));
		else if (lpPlayInfo->sCharacterData.iClass == CHARACTERCLASS_Assassin)
			lpDefItem = rsPutItem3(lpPlayInfo, (sinWD1 | sin01));
		else if (lpPlayInfo->sCharacterData.iClass == CHARACTERCLASS_Shaman)
			lpDefItem = rsPutItem3(lpPlayInfo, (sinWN1 | sin01));
		else
		{
			switch (rand() % 3)
			{
			case 0:
				lpDefItem = rsPutItem3(lpPlayInfo, (sinWS2 | sin01));
				break;
			case 1:
				lpDefItem = rsPutItem3(lpPlayInfo, (sinWA1 | sin01));
				break;
			case 2:
				lpDefItem = rsPutItem3(lpPlayInfo, (sinWH1 | sin01));
				break;
			}
		}
		break;
	case 2:
		if (lpPlayInfo->sCharacterData.iClass == CHARACTERCLASS_Magician || lpPlayInfo->sCharacterData.iClass == CHARACTERCLASS_Priestess || lpPlayInfo->sCharacterData.iClass == CHARACTERCLASS_Shaman)
			lpDefItem = rsPutItem3(lpPlayInfo, (sinDA2 | sin02));
		else
			lpDefItem = rsPutItem3(lpPlayInfo, (sinDA1 | sin02));
		break;

	case 3:
		lpDefItem = rsPutItem3(lpPlayInfo, (sinGP1 | sin01));
		break;
	case 4:
		lpDefItem = rsPutItem3(lpPlayInfo, (sinGP1 | sin01));
		break;
	case 5:
		lpDefItem = rsPutItem3(lpPlayInfo, (sinGP1 | sin01));
		break;
	}

	if (lpDefItem)
	{
		wsprintf(TransChatMessage.szMessage, "»ñµÃÁË %s ÎïÆ·      ", lpDefItem->sItem.szItemName);
		TransChatMessage.code = smTRANSCODE_MESSAGEBOX;
		TransChatMessage.dwIP = 0;
		TransChatMessage.dwObjectSerial = 0;
		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);

		SENDPACKET(lpPlayInfo, &TransChatMessage);

		smTRANS_COMMAND	smTransCommand;
		smTransCommand.code = smTRANSCODE_NOTICE_BOX;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = lpDefItem->sItem.sItemID.ToInt();
		smTransCommand.LParam = 0;
		smTransCommand.SParam = 0;
		smTransCommand.EParam = 0;

		SENDPACKET(lpPlayInfo, &smTransCommand);
	}

	lpPlayInfo->dwStartUser_PresentItem_Count++;

	lpPlayInfo->dwStartUser_PresentItem_Time = SERVER_GAMETIME + 1000 * 3 * 1;

	return TRUE;
}
//°ÑVIPÐÅÏ¢·¢ËÍµ½ÓÎÏ··þÎñÆ÷
int rsSendVipInfoToGameServer(User *lpPlayInfo)
{
	smTRANS_CHAR_COMMAND smTransCharCommand;
	smTransCharCommand.code = smTRANSCODE_PLAYER_GAME_VIP;
	smTransCharCommand.size = sizeof(smTRANS_CHAR_COMMAND);
	smTransCharCommand.WParam = lpPlayInfo->dwVipLevel ^smTRANSCODE_PLAYER_GAME_VIP;
	smTransCharCommand.LParam = lpPlayInfo->dwVipTime ^ smTRANSCODE_PLAYER_GAME_VIP;
	smTransCharCommand.SParam = 0;
	rsSendGameServer(lpPlayInfo, &smTransCharCommand);

	return 0;
}
//½áÊøVIPÐÅÏ¢µ½¿Í»§¶Ë
int rsCloseVipInfoToClient(User *lpPlayInfo)
{
	smTRANS_CHAR_COMMAND smTransCharCommand = { 0 };
	smTransCharCommand.code = smTRANSCODE_PLAYER_GAME_VIP;
	smTransCharCommand.size = sizeof(smTRANS_CHAR_COMMAND);

	SENDPACKET(lpPlayInfo, &smTransCharCommand);

	return 0;
}
// È¡ÏûË®¾§Ð­Òé
int rsCancelCrystalToClient(User *lpPlayInfo, Unit *lpChar)
{
	smTRANS_CHAR_COMMAND smTransCharCommand;
	smTransCharCommand.code = smTRANSCODE_CANCEL_SKILL;
	smTransCharCommand.size = sizeof(smTRANS_COMMAND);
	smTransCharCommand.WParam = lpChar->iPetID;
	smTransCharCommand.LParam = lpChar->iID;
	smTransCharCommand.SParam = 0;

	SENDPACKET(lpPlayInfo, &smTransCharCommand);

	lpChar->Close();

	lpChar->pcMap->iNumAliveUnitData--;

	SERVERMAP->DelMonsterSpawn(lpChar->pcMap,lpChar);

	return TRUE;
}
// ·¢ËÍÓÎÏ··þÎñÆ÷¶À½ÇÊÞÒ»¼ÒÐ­Òé
int rsSendGameServer_CaravanHopy(User *lpPlayInfo)
{
	smTRANS_COMMAND smTransCommand;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = smTRANSCODE_CARAVAN_HOPY;
	smTransCommand.WParam = lpPlayInfo->dwCaravan_Hopy_Time^smTRANSCODE_CARAVAN_HOPY;
	smTransCommand.LParam = lpPlayInfo->dwCaravan_Param ^ smTRANSCODE_CARAVAN_HOPY;
	smTransCommand.SParam = 0;
	rsSendGameServer(lpPlayInfo, &smTransCommand);

	return 0;
}
// ·¢ËÍÓÎÏ··þÎñÆ÷·ï»ËÐ­Òé
int rsSendGameServer_Phoenix(User *lpPlayInfo)
{
	smTRANS_COMMAND smTransCommand;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = smTRANSCODE_PHENIX_PET;
	smTransCommand.WParam = lpPlayInfo->dwTime_PhenixPet^smTRANSCODE_PHENIX_PET;
	smTransCommand.LParam = lpPlayInfo->PhenixPetType^smTRANSCODE_PHENIX_PET;
	smTransCommand.SParam = 0;
	rsSendGameServer(lpPlayInfo, &smTransCommand);

	return 0;
}
// ·¢ËÍÓÎÏ··þÎñÆ÷´óÍ·Ð­Òé
int rsSendGameServer_BigHead(User *lpPlayInfo)
{
	smTRANS_COMMAND smTransCommand;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = smTRANSCODE_COMIC_SKIN;
	smTransCommand.WParam = lpPlayInfo->dwTime_BigHead^smTRANSCODE_COMIC_SKIN;
	smTransCommand.LParam = lpPlayInfo->BigHeadType^smTRANSCODE_COMIC_SKIN;
	smTransCommand.SParam = 0;
	rsSendGameServer(lpPlayInfo, &smTransCommand);

	return 0;
}
//·¢ËÍÓÎÏ··þÎñÆ÷¹ûÊµÐ­Òé
int rsSendGameServer_FruitStatus(User *lpPlayInfo, int Kind)
{
	smTRANS_COMMAND smTransCommand;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = smTRANSCODE_FRUIT;
	smTransCommand.WParam = lpPlayInfo->dwPrimeItem_FruitData ^ smTRANSCODE_FRUIT;
	smTransCommand.LParam = Kind ^ smTRANSCODE_FRUIT;
	smTransCommand.SParam = 0;
	rsSendGameServer(lpPlayInfo, &smTransCommand);

	return 0;
}
//·¢ËÍ×¨Ö°ÐÅÏ¢µ½¿Í»§¶Ë
int rsSendChangeJobLevelToClient(User *lpPlayInfo)
{
	int ChangeJob;

	smTRANS_COMMAND smTransCommand;

	ZeroMemory(&smTransCommand, sizeof(smTRANS_COMMAND));

	if (lpPlayInfo->sCharacterData.iRank < CHAR_CHANGE_JOB_LEVEL)
	{
		ChangeJob = lpPlayInfo->sCharacterData.iRank;
		ChangeJob++;

		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.code = smTRANSCODE_CHANGEJOBLEVEL;
		smTransCommand.WParam = ChangeJob;

		SENDPACKET(lpPlayInfo, &smTransCommand);
	}

	return FALSE;
}
int rsSetCaravanHopy(User *lpPlayInfo, DWORD Time, int Kind)
{
	Unit *lpChar = NULL;
	smTRANS_COMMAND smTransCommand;

	if (lpPlayInfo)
	{
		if (Time > (DWORD)SERVER_LOCATIME)
		{
			if ((lpPlayInfo->dwCaravan_Hopy == NULL) || (lpPlayInfo->dwCaravan_Hopy && lpPlayInfo->dwCaravan_Hopy->bActive == FALSE))
			{
				if (lpPlayInfo->iMapID != MAPID_BlessCastle &&
					lpPlayInfo->iMapID != MAPID_Bellatra &&
					lpPlayInfo->iMapID != MAPID_QuestArena &&
					lpPlayInfo->iMapID != MAPID_GhostCastle)
				{
					lpChar = OpenNpc_Caravan_Hopy(Kind, lpPlayInfo->sPosition.iX, lpPlayInfo->sPosition.iY, lpPlayInfo->sPosition.iZ, lpPlayInfo);
					if (lpChar)
					{
						lpChar->CaravanTime = Time;
						lpChar->sUnitInfo.Caravan = Kind;
						lpPlayInfo->dwCaravan_Hopy = lpChar;

						smTransCommand.size = sizeof(smTRANS_COMMAND);
						smTransCommand.code = smTRANSCODE_CARAVAN_HOPY;
						smTransCommand.WParam = Time;
						smTransCommand.LParam = Kind;
						smTransCommand.SParam = 0;

						SENDPACKET(lpPlayInfo, &smTransCommand);
					}
				}
			}
		}
		else
		{
			if (lpPlayInfo->dwCaravan_Hopy)
			{
				CloseNPC_Caravan_Hopy(lpPlayInfo);
				lpPlayInfo->dwCaravan_Hopy = NULL;
				smTransCommand.size = sizeof(smTRANS_COMMAND);
				smTransCommand.code = smTRANSCODE_CARAVAN_HOPY;
				smTransCommand.WParam = 0;
				smTransCommand.LParam = 0;
				smTransCommand.SParam = 0;

				SENDPACKET(lpPlayInfo, &smTransCommand);
			}
		}
	}
	return FALSE;
}
int rsSetCaravanHopyMode(User *lpPlayInfo, int Kind)
{
	if (lpPlayInfo->dwCaravan_Hopy && lpPlayInfo->dwCaravan_Hopy->bActive)
	{
		if (lpPlayInfo->dwCaravan_Hopy->CaravanMode == FALSE && Kind == TRUE)
			lpPlayInfo->dwCaravan_Hopy->CaravanMode = TRUE;
		else if (lpPlayInfo->dwCaravan_Hopy->CaravanMode == TRUE && Kind == FALSE)
			lpPlayInfo->dwCaravan_Hopy->CaravanMode = FALSE;
		return TRUE;
	}
	return FALSE;
}
int rsSendUserID_MainServer(User *lpPlayInfo)
{
	smTRANS_CHAR_COMMAND2	smTransCharCommand;

	smTransCharCommand.code = smTRANSCODE_USER_ID;
	smTransCharCommand.size = sizeof(smTRANS_CHAR_COMMAND2);
	smTransCharCommand.WParam = 0;
	smTransCharCommand.LParam = 0;
	smTransCharCommand.SParam = 0;

	lstrcpy(smTransCharCommand.szId, lpPlayInfo->szAccountName);
	lstrcpy(smTransCharCommand.szName, lpPlayInfo->szCharacterName);

	rsSendGameServer(lpPlayInfo, &smTransCharCommand);

	return 0;
}

int rsRecvUserID_MainServer(User *lpPlayInfo, smTRANS_CHAR_COMMAND2 *lpTransCharCommand)
{
	lstrcpy(lpPlayInfo->szUserExpTimeID, lpTransCharCommand->szId);
	lstrcpy(lpPlayInfo->szUserExpTimeName, lpTransCharCommand->szName);

	if (lpPlayInfo->dwExpGameTimeCheck == 0)
		bSql_GetExpGameTime(lpPlayInfo, 0);

	return TRUE;
}
int rsGetExp_GameTime(User *lpPlayInfo)
{
	int gTime = lpPlayInfo->dwExpGameTime / (1000 * 60 * 60);

	if (lpPlayInfo->dwExpGameTimeCheck)
	{
		if (gTime < 3)
			return 100;
		else if (gTime < 5)
			return 50;
		return 0;
	}

	return 100;
}

int rsDispay_GameTime(User *lpPlayInfo, DWORD dwTimeOld)//ÇØ¿Ü
{
	return 0;
}


#include "HackTrap.h"


int rsRecvHackTrap(User *lpPlayInfo, smTRANS_COMMAND *lpTransCharCommand)
{
	smTRANS_COMMAND		smTransCommand;

	switch (lpTransCharCommand->WParam)
	{
	case 100:
		if ((rsHackTrap_FieldNPC[lpTransCharCommand->SParam] & lpTransCharCommand->LParam) == 0)
		{
			if (lpPlayInfo->WarningCount < 20)
			{
				smTransCommand.WParam = 8900;
				smTransCommand.LParam = lpTransCharCommand->SParam;
				smTransCommand.SParam = lpTransCharCommand->LParam;
				RecordHackLogFile(lpPlayInfo, &smTransCommand);
			}
		}
		break;
	}
	return TRUE;
}
// pluto Á¦ÀÛ ·é °Ë»ç
DWORD ManufactureCheckRune(User *lpPlayInfo, DWORD RecipeCode, DWORD *pRuneCode) // Àåº° - ´ëÀåÀåÀÌÀÇ È¥
{
	int RuneCnt = 0;
	DWORD Arm_Armor_Code[11] = { sin01, sin02, sin03, sin04, sin05, sin06, sin07, sin08, sin09, sin10, sin11 }; // ·¹½ÃÇÇ Á¾·ù
	DWORD CheckRuneCode[11][8][3] = { {	{ (sinPR3 | sin01), (sinPR3 | sin02), (sinPR3 | sin03) },  // ·é Á¶ÇÕ½ÄÀÌ´Ù
										{ (sinPR3 | sin01), (sinPR3 | sin02), (sinPR4 | sin03) },
										{ (sinPR3 | sin01), (sinPR4 | sin02), (sinPR3 | sin03) },
										{ (sinPR3 | sin01), (sinPR4 | sin02), (sinPR4 | sin03) },
										{ (sinPR4 | sin01), (sinPR3 | sin02), (sinPR3 | sin03) },
										{ (sinPR4 | sin01), (sinPR3 | sin02), (sinPR4 | sin03) },
										{ (sinPR4 | sin01), (sinPR4 | sin02), (sinPR3 | sin03) },
										{ (sinPR4 | sin01), (sinPR4 | sin02), (sinPR4 | sin03) } },
		////////////////////////////////////////////////////////////////////////////////////////////	ÀØÇôÁø ·¹½ÃÇÇ
	 {  { (sinPR3 | sin02), (sinPR3 | sin03), (sinPR3 | sin04) },
		{ (sinPR3 | sin02), (sinPR3 | sin03), (sinPR4 | sin04) },
		{ (sinPR3 | sin02), (sinPR4 | sin03), (sinPR3 | sin04) },
		{ (sinPR3 | sin02), (sinPR4 | sin03), (sinPR4 | sin04) },
		{ (sinPR4 | sin02), (sinPR3 | sin03), (sinPR3 | sin04) },
		{ (sinPR4 | sin02), (sinPR3 | sin03), (sinPR4 | sin04) },
		{ (sinPR4 | sin02), (sinPR4 | sin03), (sinPR3 | sin04) },
		{ (sinPR4 | sin02), (sinPR4 | sin03), (sinPR4 | sin04) } },
		////////////////////////////////////////////////////////////////////////////////////////////	°í´ëÀÇ ·¹½ÃÇÇ
	 {  { (sinPR3 | sin03), (sinPR3 | sin04), (sinPR3 | sin05) },
		{ (sinPR3 | sin03), (sinPR3 | sin04), (sinPR4 | sin05) },
		{ (sinPR3 | sin03), (sinPR4 | sin04), (sinPR3 | sin05) },
		{ (sinPR3 | sin03), (sinPR4 | sin04), (sinPR4 | sin05) },
		{ (sinPR4 | sin03), (sinPR3 | sin04), (sinPR3 | sin05) },
		{ (sinPR4 | sin03), (sinPR3 | sin04), (sinPR4 | sin05) },
		{ (sinPR4 | sin03), (sinPR4 | sin04), (sinPR3 | sin05) },
		{ (sinPR4 | sin03), (sinPR4 | sin04), (sinPR4 | sin05) } },
		////////////////////////////////////////////////////////////////////////////////////////////	´ëÁöÀÇ ·¹½ÃÇÇ
	 {  { (sinPR3 | sin03), (sinPR3 | sin04), (sinPR3 | sin05) },
		{ (sinPR3 | sin03), (sinPR3 | sin04), (sinPR4 | sin05) },
		{ (sinPR3 | sin03), (sinPR4 | sin04), (sinPR3 | sin05) },
		{ (sinPR3 | sin03), (sinPR4 | sin04), (sinPR4 | sin05) },
		{ (sinPR4 | sin03), (sinPR3 | sin04), (sinPR3 | sin05) },
		{ (sinPR4 | sin03), (sinPR3 | sin04), (sinPR4 | sin05) },
		{ (sinPR4 | sin03), (sinPR4 | sin04), (sinPR3 | sin05) },
		{ (sinPR4 | sin03), (sinPR4 | sin04), (sinPR4 | sin05) } },
		////////////////////////////////////////////////////////////////////////////////////////////	¾îµÒÀÇ ·¹½ÃÇÇ
	{	{ (sinPR3 | sin03), (sinPR3 | sin04), (sinPR3 | sin05) },
		{ (sinPR3 | sin03), (sinPR3 | sin04), (sinPR4 | sin05) },
		{ (sinPR3 | sin03), (sinPR4 | sin04), (sinPR3 | sin05) },
		{ (sinPR3 | sin03), (sinPR4 | sin04), (sinPR4 | sin05) },
		{ (sinPR4 | sin03), (sinPR3 | sin04), (sinPR3 | sin05) },
		{ (sinPR4 | sin03), (sinPR3 | sin04), (sinPR4 | sin05) },
		{ (sinPR4 | sin03), (sinPR4 | sin04), (sinPR3 | sin05) },
		{ (sinPR4 | sin03), (sinPR4 | sin04), (sinPR4 | sin05) } },
		////////////////////////////////////////////////////////////////////////////////////////////	È­¿°ÀÇ ·¹½ÃÇÇ
	{  { (sinPR3 | sin03), (sinPR3 | sin04), (sinPR3 | sin05) },
		{ (sinPR3 | sin03), (sinPR3 | sin04), (sinPR4 | sin05) },
		{ (sinPR3 | sin03), (sinPR4 | sin04), (sinPR3 | sin05) },
		{ (sinPR3 | sin03), (sinPR4 | sin04), (sinPR4 | sin05) },
		{ (sinPR4 | sin03), (sinPR3 | sin04), (sinPR3 | sin05) },
		{ (sinPR4 | sin03), (sinPR3 | sin04), (sinPR4 | sin05) },
		{ (sinPR4 | sin03), (sinPR4 | sin04), (sinPR3 | sin05) },
		{ (sinPR4 | sin03), (sinPR4 | sin04), (sinPR4 | sin05) } },
		////////////////////////////////////////////////////////////////////////////////////////////	¹Ù¶÷ÀÇ ·¹½ÃÇÇ
	{  { (sinPR3 | sin04), (sinPR3 | sin05), (sinPR3 | sin06) },
		{ (sinPR3 | sin04), (sinPR3 | sin05), (sinPR4 | sin06) },
		{ (sinPR3 | sin04), (sinPR4 | sin05), (sinPR3 | sin06) },
		{ (sinPR3 | sin04), (sinPR4 | sin05), (sinPR4 | sin06) },
		{ (sinPR4 | sin04), (sinPR3 | sin05), (sinPR3 | sin06) },
		{ (sinPR4 | sin04), (sinPR3 | sin05), (sinPR4 | sin06) },
		{ (sinPR4 | sin04), (sinPR4 | sin05), (sinPR3 | sin06) },
		{ (sinPR4 | sin04), (sinPR4 | sin05), (sinPR4 | sin06) } },
		////////////////////////////////////////////////////////////////////////////////////////////	ÅÂ¾çÀÇ ·¹½ÃÇÇ
	{  { (sinPR3 | sin05), (sinPR3 | sin06), (sinPR3 | sin07) },
		{ (sinPR3 | sin05), (sinPR3 | sin06), (sinPR4 | sin07) },
		{ (sinPR3 | sin05), (sinPR4 | sin06), (sinPR3 | sin07) },
		{ (sinPR3 | sin05), (sinPR4 | sin06), (sinPR4 | sin07) },
		{ (sinPR4 | sin05), (sinPR3 | sin06), (sinPR3 | sin07) },
		{ (sinPR4 | sin05), (sinPR3 | sin06), (sinPR4 | sin07) },
		{ (sinPR4 | sin05), (sinPR4 | sin06), (sinPR3 | sin07) },
		{ (sinPR4 | sin05), (sinPR4 | sin06), (sinPR4 | sin07) } },
		////////////////////////////////////////////////////////////////////////////////////////////	±¤Æ÷ÇÑ ·¹½ÃÇÇ
	{  { (sinPR3 | sin06), (sinPR3 | sin07), (sinPR3 | sin08) },
		{ (sinPR3 | sin06), (sinPR3 | sin07), (sinPR4 | sin08) },
		{ (sinPR3 | sin06), (sinPR4 | sin07), (sinPR3 | sin08) },
		{ (sinPR3 | sin06), (sinPR4 | sin07), (sinPR4 | sin08) },
		{ (sinPR4 | sin06), (sinPR3 | sin07), (sinPR3 | sin08) },
		{ (sinPR4 | sin06), (sinPR3 | sin07), (sinPR4 | sin08) },
		{ (sinPR4 | sin06), (sinPR4 | sin07), (sinPR3 | sin08) },
		{ (sinPR4 | sin06), (sinPR4 | sin07), (sinPR4 | sin08) } },
		////////////////////////////////////////////////////////////////////////////////////////////	Ãµ»óÀÇ ·¹½ÃÇÇ

	{  { (sinPR3 | sin09), (sinPR4 | sin10), (sinPR3 | sin11) },
		{ 0,0,0 },
		{ 0,0,0 },
		{ 0,0,0 },
		{ 0,0,0 },
		{ 0,0,0 },
		{ 0,0,0 },
		{ 0,0,0 } },
		////////////////////////////////////////////////////////////////////////////////////////////	Æ÷¼³ÀÇ ·¹½ÃÇÇ // Àåº°

	{  { (sinPR3 | sin12), (sinPR3 | sin13), (sinPR3 | sin14) },
		{ 0,0,0 },
		{ 0,0,0 },
		{ 0,0,0 },
		{ 0,0,0 },
		{ 0,0,0 },
		{ 0,0,0 },
		{ 0,0,0 } }
		////////////////////////////////////////////////////////////////////////////////////////////	±â¾ïÀÇ ·¹½ÃÇÇ // Àåº° - ´ëÀåÀåÀÌÀÇ È¥
	};

	// Àåº° - ´ëÀåÀåÀÌÀÇ È¥
	DWORD	dwItem = 0;

	// ÇÁ¸®½ºÆ¼½º ÀÏ °æ¿ì
	if (lpPlayInfo->sCharacterData.iClass == CHARACTERCLASS_Priestess) dwItem = (sinDA2 | sin52);
	// ¸ÞÁö¼Ç ÀÏ °æ¿ì
	else if (lpPlayInfo->sCharacterData.iClass == CHARACTERCLASS_Magician) dwItem = (sinDA2 | sin51);
	// ¾ÆÃ³, ¾ÆÆ²¶õÅ¸ ÀÏ °æ¿ì
	else if (lpPlayInfo->sCharacterData.iClass == CHARACTERCLASS_Archer || lpPlayInfo->sCharacterData.iClass == CHARACTERCLASS_Atalanta) dwItem = (sinDA1 | sin52);
	// ÆÄÀÌÅÍ, ÆÄÀÌÅ©¸Ç, ¸ÞÄ«´Ï¼Ç, ³ªÀÌÆ® ÀÏ °æ¿ì
	else dwItem = (sinDA1 | sin51);


	// ·¹½ÃÇÇ¿Í ·éÁ¶ÇÕ¿¡ ¸Â´Â ¹ß»ý ¾ÆÀÌÅÛ // Àåº° - Á¦ÀÛ
	DWORD CreateItemCode[2][11][8] = { {	{ (sinWA1 | sin14), (sinWC1 | sin14), (sinWH1 | sin15), (sinWP1 | sin15), (sinWS1 | sin16), (sinWS2 | sin17), (sinWT1 | sin15), (sinWM1 | sin15) }, // ÀØÇôÁø ·¹½ÃÇÇ ¹«±¸
											{ (sinWA1 | sin15), (sinWC1 | sin15), (sinWH1 | sin16), (sinWP1 | sin16), (sinWS1 | sin17), (sinWS2 | sin18), (sinWT1 | sin16), (sinWM1 | sin16) }, // °í´ëÀÇ ·¹½ÃÇÇ ¹«±¸
											{ (sinWA1 | sin16), (sinWC1 | sin16), (sinWH1 | sin17), (sinWP1 | sin17), (sinWS1 | sin18), (sinWS2 | sin19), (sinWT1 | sin17), (sinWM1 | sin17) }, // ´ëÁöÀÇ ¹«±¸
											{ (sinWA1 | sin17), (sinWC1 | sin17), (sinWH1 | sin18), (sinWP1 | sin18), (sinWS1 | sin19), (sinWS2 | sin20), (sinWT1 | sin18), (sinWM1 | sin18) }, // ¾îµÒÀÇ ·¹½ÃÇÇ ¹«±¸
											{ (sinWA1 | sin18), (sinWC1 | sin18), (sinWH1 | sin19), (sinWP1 | sin19), (sinWS1 | sin20), (sinWS2 | sin21), (sinWT1 | sin19), (sinWM1 | sin19) }, // È­¿°ÀÇ ·¹½ÃÇÇ ¹«±¸
											{ (sinWA1 | sin19), (sinWC1 | sin19), (sinWH1 | sin20), (sinWP1 | sin20), (sinWS1 | sin21), (sinWS2 | sin22), (sinWT1 | sin20), (sinWM1 | sin20) }, // ¹Ù¶÷ÀÇ ·¹½ÃÇÇ ¹«±¸
											{ (sinWA1 | sin21), (sinWC1 | sin21), (sinWH1 | sin22), (sinWP1 | sin22), (sinWS1 | sin23), (sinWS2 | sin24), (sinWT1 | sin22), (sinWM1 | sin22) }, // ÅÂ¾çÀÇ ·¹½ÃÇÇ ¹«±¸
											{ (sinWA1 | sin22), (sinWC1 | sin22), (sinWH1 | sin23), (sinWP1 | sin23), (sinWS1 | sin24), (sinWS2 | sin25), (sinWT1 | sin23), (sinWM1 | sin23) }, // ±¤Æ÷ÇÑ ·¹½ÃÇÇ ¹«±¸
											{ 0, 0, 0, 0, 0, 0, 0, 0 } , // Ãµ»óÀÇ ·¹½ÃÇÇ ¹«±¸
											{ 0, 0, 0, 0, 0, 0, 0, 0 } ,
											{ 0, 0, 0, 0, 0, 0, 0, 0}}, // ±â¾ïÀÇ ·¹½ÃÇÇ // Àåº° -  ´ëÀåÀåÀÌÀÇ È¥
											//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
										{	{ (sinDA1 | sin16), (sinDA2 | sin16), (sinDS1 | sin14), (sinOM1 | sin15), (sinDG1 | sin14), (sinOA2 | sin14), (sinDB1 | sin14), 0 }, // ÀØÇôÁø ·¹½ÃÇÇ °©ÁÖ
											{ (sinDA1 | sin17), (sinDA2 | sin17), (sinDS1 | sin15), (sinOM1 | sin16), (sinDG1 | sin15), (sinOA2 | sin15), (sinDB1 | sin15), 0 }, // °í´ëÀÇ ·¹½ÃÇÇ °©ÁÖ
											{ (sinDA1 | sin18), (sinDA2 | sin18), (sinDS1 | sin16), (sinOM1 | sin17), (sinDG1 | sin16), (sinOA2 | sin16), (sinDB1 | sin16), 0 }, // ´ëÁöÀÇ ·¹½ÃÇÇ °©ÁÖ
											{ (sinDA1 | sin19), (sinDA2 | sin19), (sinDS1 | sin17), (sinOM1 | sin18), (sinDG1 | sin17), (sinOA2 | sin17), (sinDB1 | sin17), 0 }, // ¾îµÒÀÇ ·¹½ÃÇÇ °©ÁÖ
											{ (sinDA1 | sin20), (sinDA2 | sin20), (sinDS1 | sin18), (sinOM1 | sin19), (sinDG1 | sin18), (sinOA2 | sin18), (sinDB1 | sin18), 0 }, // È­¿°ÀÇ ·¹½ÃÇÇ °©ÁÖ
											{ (sinDA1 | sin21), (sinDA2 | sin21), (sinDS1 | sin19), (sinOM1 | sin20), (sinDG1 | sin19), (sinOA2 | sin19), (sinDB1 | sin19), 0 }, // ¹Ù¶÷ÀÇ ·¹½ÃÇÇ °©ÁÖ
											{ (sinDA1 | sin23), (sinDA2 | sin23), (sinDS1 | sin21), (sinOM1 | sin22), (sinDG1 | sin21), (sinOA2 | sin21), (sinDB1 | sin21), 0 }, // ÅÂ¾çÀÇ ·¹½ÃÇÇ °©ÁÖ
											{ (sinDA1 | sin24), (sinDA2 | sin24), (sinDS1 | sin22), (sinOM1 | sin23), (sinDG1 | sin22), (sinOA2 | sin22), (sinDB1 | sin22), 0 }, // ±¤Æ÷ÇÑ ·¹½ÃÇÇ °©ÁÖ
											{ 0, 0, 0, 0, 0, 0, 0, 0 },  // Ãµ»óÀÇ ·¹½ÃÇÇ °©ÁÖ
											{ (sinOA1 | sin36), 0, 0, 0, 0, 0, 0}, // ´«°áÁ¤ ¸ñ°ÉÀÌ
											{ dwItem, 0, 0, 0, 0, 0, 0}} // Àåº° - ´ëÀåÀåÀÌÀÇ È¥
	};
	if ((RecipeCode & sinITEM_MASK2) == sinWR1)		// ¹«±¸
	{
		for (int i = 0; i < MAX_RECIPE_KIND; i++)
		{
			if (Arm_Armor_Code[i] == (RecipeCode & sinITEM_MASK3))
			{
				for (int j = 0; j < MAX_RUNE; j++)   // ·é Á¶ÇÕ 
				{
					RuneCnt = 0;
					for (int x = 0; x < 3; x++) // ÇÊ¿äÇÑ ·é
					{
						for (int y = 0; y < 3; y++)
						{
							if (CheckRuneCode[i][j][x] == pRuneCode[y + 1])
							{
								RuneCnt++;
								break;
							}
						}
						if (RuneCnt == 3)
						{
							return CreateItemCode[0][i][j];
						}
					}
				}
			}
		}
	}
	else if ((RecipeCode & sinITEM_MASK2) == sinDR1)		// °©ÁÖ
	{
		for (int i = 0; i < MAX_RECIPE_KIND; i++)
		{
			if (Arm_Armor_Code[i] == (RecipeCode & sinITEM_MASK3))
			{
				for (int j = 0; j < MAX_RUNE; j++)
				{
					RuneCnt = 0;
					for (int x = 0; x < 3; x++)
					{
						for (int y = 0; y < 3; y++)
						{
							if (CheckRuneCode[i][j][x] == pRuneCode[y + 1])
							{
								RuneCnt++;
								break;
							}
						}
						if (RuneCnt == 3)
						{
							if (j == 7)
							{
								int ArmorRand = 0;
								ArmorRand = rand() % 7;
								return CreateItemCode[1][i][ArmorRand];
							}
							return CreateItemCode[1][i][j];
						}
					}
				}
			}
		}
	}
	return FALSE;
}


// pluto ¼±¹°»óÀÚ
int rsPutItem_TreasureBox(User *lpPlayInfo, DWORD Code)
{
	int cnt;
	int nClass = 0;
	int Randum[6][8] =
	{
		{ 2000, 2900, 1000, 1500, 1000, 100, 750, 750 },
		{ 2600, 2620, 700, 1000, 1500, 80, 750, 750 },
		{ 2750, 2400, 800, 1500, 1000, 50, 750, 750 },
		{ 2450, 2850, 500, 1500, 1000, 200, 750, 750 },
		{ 2320, 2000, 1500, 1500, 1000, 180, 750, 750 },
		{ 2850, 2000, 1000, 1500, 1000, 150, 750, 750 }
	};

	switch ((Code & sinITEM_MASK3))
	{
	case sin05:
		nClass = 0;
		break;
	case sin06:
		nClass = 1;
		break;
	case sin07:
		nClass = 2;
		break;
	case sin08:
		nClass = 3;
		break;
	case sin09:
		nClass = 4;
		break;
	case sin10:
		nClass = 5;
		break;
	}

	int CodeCount = 0;
	int RndNum = rand() % 10000;
	int RndCnt = 0;
	for (cnt = 0; cnt < 8; cnt++)
	{
		if (Randum[nClass][CodeCount])
		{
			RndCnt += Randum[nClass][cnt];
			if (RndNum < RndCnt)
			{
				CodeCount = cnt;
				break;
			}
		}
	}

	DWORD ItemCode[6][8] =
	{
		{ (sinPM1 | sin04), (sinBI1 | sin08), (sinGP1 | sin19), (sinFO1 | sin08),(sinFO1 | sin08), (sinBI2 | sin09), (sinBI1 | sin21), (sinBI1 | sin19) },	// pluto 1µî±Þ
		{ (sinPM1 | sin04), (sinBI1 | sin08), (sinGP1 | sin19), (sinFO1 | sin08),(sinFO1 | sin07), (sinBI2 | sin09), (sinBI1 | sin21), (sinBI1 | sin19) },	// pluto 2µî±Þ
		{ (sinPM1 | sin04), (sinBI1 | sin08), (sinGP1 | sin18), (sinFO1 | sin07),(sinFO1 | sin06), (sinBI2 | sin09), (sinBI1 | sin21), (sinBI1 | sin19) },	// pluto 3µî±Þ
		{ (sinPM1 | sin03), (sinBI1 | sin08), (sinGP1 | sin18), (sinFO1 | sin06),(sinFO1 | sin05), (sinBI2 | sin05), (sinBI1 | sin21), (sinBI1 | sin19) },	// pluto 4µî±Þ
		{ (sinPM1 | sin03), (sinBI1 | sin08), (sinGP1 | sin17), (sinFO1 | sin04),(sinFO1 | sin04), (sinBI2 | sin05), (sinBI1 | sin21), (sinBI1 | sin19) },	// pluto 5µî±Þ
		{ (sinPM1 | sin02), (sinBI1 | sin08), (sinGP1 | sin17), (sinFO1 | sin04),(sinFO1 | sin04), (sinBI2 | sin05), (sinBI1 | sin21), (sinBI1 | sin19) }	// pluto 6µî±Þ
	};
	if ((Code & sinITEM_MASK2) == sinSP1)
	{
		SERVERITEM->CreateItem(lpPlayInfo, ItemCode[nClass][CodeCount], CodeCount == 0 ? 10 : 1);
	}
	return TRUE;
}

// ¹ÚÀç¿ø - Ä¸½¶ ¾ÆÀÌÅÛ¿¡ ´ëÇÑ ¾ÆÀÌÅÛ ·£´ý º¸»ó(È£¶ûÀÌ Ä¸½¶ »ç¿ë)
int rsPutItem_CapsuleItem(User *lpPlayInfo, DWORD Code)
{
	int cnt;
	int nClass = 0;
	int Randum[1][12] = // Ä¸½¶Çü ¾ÆÀÌÅÛ °è¼Ó Ãß°¡ 
	{
		{ 1000, 500, 1000,  1000,  1000,  800, 1000, 600,  1000,  1000,  800, 300} // sinSP1|sin34 È£¶ûÀÌ Ä¸½¶
	};

	switch ((Code & sinITEM_MASK3))
	{
	case sin34: // ¹ÚÀç¿ø - È£¶ûÀÌ Ä¸½¶ Ãß°¡
		nClass = 0;
		break;
	}

	int CodeCount = 0;
	int RndNum = rand() % 10000;
	int RndCnt = 0;
	for (cnt = 0; cnt < 12; cnt++)
	{
		if (Randum[nClass][CodeCount])
		{
			RndCnt += Randum[nClass][cnt];
			if (RndNum < RndCnt)
			{
				CodeCount = cnt;
				break;
			}
		}
	}

	DWORD ItemCode[1][12] =
	{
		{ (sinFO1 | sin06), (sinFO1 | sin06), (sinFO1 | sin07), (sinFO1 | sin08), (sinFO1 | sin09), (sinFO1 | sin10), // È£¶ûÀÌ Ä¸½¶
		(sinFO1 | sin25), (sinFO1 | sin25), (sinFO1 | sin26), (sinFO1 | sin27), (sinFO1 | sin28), (sinSE1 | sin01) }
	};

	if ((Code & sinITEM_MASK2) == sinSP1)
	{
		SERVERITEM->CreateItem(lpPlayInfo, ItemCode[nClass][CodeCount], (CodeCount == 10 || CodeCount == 11) ? 30 : 1);
	}
	return TRUE;

}

// ¹ÚÀç¿ø - ¹Ì´Ï ¸ó½ºÅÍ ¼ÒÈ¯ // ¹ÚÀç¿ø - ¹Ì´Ï ¸ð¸®ÇÁ ÀÌº¥Æ®¶§ ¹Ì´Ï ¸ð¸®ÇÁ¸¦ ¼ÒÈ¯ÇÑ´Ù.
int rsSendAreaOpenKidMonster(User	*lpPlayInfo, Unit *lpChar)
{
	int cnt2;

	for (cnt2 = 0; cnt2 < srKIDMONSTER_MAX; cnt2++)
	{
		if (lstrcmp(lpChar->sCharacterData.szName, srOpenKidMonster[cnt2].szParentMonName) == 0)
		{
			smTRANS_COMMAND smTransCommand;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.code = smTRANSCODE_OPENMONSTER;
			smTransCommand.WParam = lpChar->pX;
			smTransCommand.SParam = lpChar->pY;
			smTransCommand.LParam = lpChar->pZ;
			smTransCommand.EParam = srOpenKidMonster[cnt2].mon_Num;;
			rsSendAreaServer(lpPlayInfo, &smTransCommand);

			break;
		}
	}

	return TRUE;
}

// ¹ÚÀç¿ø - ¹Ì´Ï ¸ð¸®ÇÁ ÀÌº¥Æ®¶§ ¹Ì´Ï ¸ð¸®ÇÁ¸¦ ¼ÒÈ¯ÇÑ´Ù.
int rsOpenKidMonster(User *lpPlayInfo, smTRANS_COMMAND *lpTransCommand, int mon_Num)
{
	int x = 0;
	int z = 0;
	Map		*lpStgArea;
	Unit			*lpChar;

	auto pMonstTable = SERVERUNIT->GetMonsterTable();

	for (auto &pc : pMonstTable)
	{
		if (STRINGCOMPARE(pc->szName, srOpenKidMonster[mon_Num].szChildMonName))
		{
			for (int i = 0; i < srOpenKidMonster[mon_Num].mon_Count; i++)
			{
				x = rand() % (128 * fONE);
				z = rand() % (128 * fONE);
				x -= 64 * fONE;
				z -= 64 * fONE;
				lpStgArea = SERVERMAP->GetMapByXZ(lpPlayInfo->sPosition.iX, lpPlayInfo->sPosition.iZ);

				if (lpStgArea)
				{
					lpStgArea->bForceCreateMonster = TRUE;

					lpChar = SERVERMAP->CreateUnit(lpStgArea, pc);

					if (lpChar)
					{
						lpChar->pX = lpTransCommand->WParam + x;
						lpChar->pY = lpTransCommand->SParam;
						lpChar->pZ = lpTransCommand->LParam + z;
						lpChar->iLureDistance = 0;
						lpChar->SetMotionFromCode(ANIMATIONTYPE_Idle);
						lpChar->TargetMoveCount = 0;

						SERVERUNIT->ProcessPacketEffectWarp(lpPlayInfo, lpChar->sPosition);
					}
				}
			}
			break;
		}
	}

	return TRUE;
}


// ¹ÚÀç¿ø - °ø¼ºÀü Å©¸®½ºÅ» Å¸¿ö ¹æ¾î ¸ó½ºÅÍ ¼ÒÈ¯
int rsSendAreaOpenSODGuardMonster(User *lpPlayInfo, Unit *lpChar)
{
	int cnt2;

	for (cnt2 = 0; cnt2 < srSOD_GUARD_MONSTER_MAX; cnt2++)
	{
		if (lstrcmp(lpChar->sCharacterData.szName, srOpenSODCrystalGuardMonster[cnt2].szParentMonName) == 0)
		{
			smTRANS_COMMAND smTransCommand;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.code = smTRANSCODE_OPENMONSTER;
			smTransCommand.WParam = lpChar->pX;
			smTransCommand.SParam = lpChar->pY;
			smTransCommand.LParam = lpChar->pZ;
			smTransCommand.EParam = srOpenSODCrystalGuardMonster[cnt2].mon_Num; // ¸ó½ºÅÍ ¼ø¹ø 
			rsSendAreaServer(lpPlayInfo, &smTransCommand);

			break;
		}
	}

	return TRUE;
}


// ¹ÚÀç¿ø - °ø¼ºÀü Å©¸®½ºÅ» Å¸¿ö ¹æ¾î ¸ó½ºÅÍ(Å©¸®½ºÅ» Å¸¿ö¸¦ »ç³ÉÇÏ¸é ¹æ¾îÇÒ ¸ó½ºÅÍ°¡ ¼ÒÈ¯µÈ´Ù.)
int rsOpenSODGuardMonster(User *lpPlayInfo, smTRANS_COMMAND *lpTransCommand, int mon_Num)
{
	int x = 0;
	int z = 0;
	Map		*lpStgArea;
	STG_CHAR_INFO	StgCharInfo;
	Unit			*lpChar;
	int mon_x = 0;
	int mon_z = 0;
	int dist = 0;
	int rand_num = 0;

	if (mon_Num == 4)  // ¸ó½ºÅÍ ¼ø¹ø 4´Â ¼º¹® ¼öÈ£º´Àº °íÁ¤
	{
		rand_num = 4;
	}
	else
		rand_num = GetRandomPos(0, 2); // 1."¸®Ä«¸£ÅÙ ¹Îº´´ë"  2."¸®Ä«¸£ÅÙ °æºñ´ë"  3."ºí·¹½º¿Õ±¹ °æºñ´ë"

	auto pMonstTable = SERVERUNIT->GetMonsterTable();

	for (auto &pc : pMonstTable)
	{
		if (STRINGCOMPARE(pc->szName, srOpenSODCrystalGuardMonster[rand_num].szChildMonName))
		{
			for (int j = 0; j < 7; j++)
			{
				if (lpPlayInfo->iMapID == rsSOD_CRYSTAL_GUARD_MONSTER_POS[j][0])
				{
					mon_x = abs(lpTransCommand->WParam / fONE - rsSOD_CRYSTAL_GUARD_MONSTER_POS[j][1]);
					mon_z = abs(lpTransCommand->LParam / fONE - rsSOD_CRYSTAL_GUARD_MONSTER_POS[j][2]);
					dist = mon_x * mon_x + mon_z * mon_z;
					if (dist < 300 * 300)
					{
						for (int i = 0; i < srOpenSODCrystalGuardMonster[rand_num].mon_Count; i++) // ¼ÒÈ¯ÇÒ ¹æ¾î ¸ó½ºÅÍ °³¼ö ¸¸Å­
						{
							x = rand() % (128 * fONE);
							z = rand() % (128 * fONE);
							x -= 64 * fONE;
							z -= 64 * fONE;
							lpStgArea = SERVERMAP->GetMapByXZ(lpPlayInfo->sPosition.iX, lpPlayInfo->sPosition.iZ);

							if (lpStgArea)
							{
								lpStgArea->bForceCreateMonster = TRUE;
								lpChar = SERVERMAP->CreateUnit(lpStgArea, pc);
								if (lpChar)
								{
									lpChar->pX = rsSOD_CRYSTAL_GUARD_MONSTER_POS[j][1] * fONE + x;
									lpChar->pY = lpTransCommand->SParam;
									lpChar->pZ = rsSOD_CRYSTAL_GUARD_MONSTER_POS[j][2] * fONE + z;
									lpChar->sSpawnPosition.iX = rsSOD_CRYSTAL_GUARD_MONSTER_POS[j][1] * fONE + x;
									lpChar->sSpawnPosition.iY = lpTransCommand->SParam;
									lpChar->sSpawnPosition.iZ = rsSOD_CRYSTAL_GUARD_MONSTER_POS[j][2] * fONE + z;
									lpChar->iLureDistance = DIST_AROUND_MIDDLE;
									lpChar->SetMotionFromCode(ANIMATIONTYPE_Idle);
									lpChar->TargetMoveCount = 0;

									SERVERUNIT->ProcessPacketEffectWarp(lpPlayInfo, lpChar->sPosition);
								}
							}
						}
					}
				}
			}
			break;
		}
	}

	return TRUE;
}

int rsRecvEventGame(User *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{

	switch (lpTransCommand->WParam)
	{
	case smCODE_EVENT_STATE_INIT:
		rsEventGame_State_Init(lpPlayInfo, lpTransCommand);
		break;
	}

	return TRUE;
}
int	rsUseSoccerBallPotionItem(DWORD dwItemCode, User *lpPlayInfo)
{
	if (dwItemCode != (sinSP1 | sin40))
		return -1;

	switch (dwItemCode)
	{
	case (sinSP1 | sin40):
		rsSendBigHeadToClient(lpPlayInfo, 60 * 60 * 3, 7);
		break;
	}

	return TRUE;
}
int SetAgingItem(Item *pItem, int AgingNum)
{
	pItem->eCraftType = ITEMCRAFTTYPE_Aging;

	if (((pItem->sItemID.ToItemType()) >= sinWA1) && ((pItem->sItemID.ToItemType()) <= sinDA2))
	{
		for (int i = 0; i < AgingNum; i++)
			sinSetAgingItemIncreState(pItem);
	}

	return TRUE;
}