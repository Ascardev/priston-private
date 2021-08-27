#include "StdAfx.h"
#include "character.h"
#include "playmain.h"
#include "fileread.h"
#include "record.h"
#include "netplay.h"
#include "playsub.h"
#include "cracker.h"

#include "skillsub.h"

#include "AreaServer.h"

#include "srcserver\\onserver.h"

extern HWND hwnd;

#define SERVER_CHAR_INFO


#define RECORD_TIME_STEP		(5*60*1000)

#define NET_LOADING_WAIT_LIMIT		10000



DWORD	dwLastRecordTime = 0;

int Debug_SendCount = 0;
int Debug_RecvCount1 = 0;
int Debug_RecvCount2 = 0;
int Debug_RecvCount3 = 0;

int NetWorkInitFlag = 0;
int	BellatraEffectInitFlag = 0;


DWORD	dwTime_ServerT = 0;
DWORD	dwTime_ConnectMS = 0;
DWORD   dwTime_ServerGMT = 0;

//경굶뵀
#define	CLIENT_VERSION_NUM		3101
#define CLIENT_VERSION_CHECK	(-CLIENT_VERSION_NUM*2)

int	Client_Version = CLIENT_VERSION_NUM;
int	Server_LimitVersion = 167;


int	Version_WareHouse = 1;
int	Version_CharInfo = 1;
int Version_Caravan = 1;

int	ReconnDataServer = 0;
int	ReconnServer = 0;

char	szConnServerName[16];

DWORD	dwRecvUserServerTime = 0;
DWORD	dwRecvDataServerTime = 0;
DWORD	dwRecvServerTime = 0;
DWORD	dwRecvExtendServerTime = 0;

int	rsRecvDataServer = TRUE;
int	rsRecvServer = TRUE;
int	rsRecvUserServer = TRUE;
int	rsRecvExtendServer = TRUE;

DWORD dwMyIP;

char *szDefaultServIP = "127.0.0.1";

char *szNetLogFile = "debugnet.log";

int	DisconnectFlag = 0;
int	DisconnectServerCode = 0;

int	WarningHack = 0;

DWORD	dwQuestDelayTime = 0;

DWORD	dwLoadingTime = 0;

char szServIP[32];
DWORD dwServPort;
char szDataServIP[32];
DWORD dwDataServPort;
char szUserServIP[32];
DWORD dwUserServPort;
char szExtendServIP[32];
DWORD dwExtendServPort;



DWORD	dwConnectedClientTime = 0;
DWORD	dwConnectedServerTime = 0;
DWORD	dwLastRecvGameServerTime = 0;
DWORD	dwLastRecvGameServerTime2 = 0;
DWORD	dwLastRecvGameServerTime3 = 0;
DWORD	dwLastRecvGameServerTime4 = 0;

typedef DWORD(*LPFN_CheckMem)(TRANS_FUNC_MEMORY *TransFuncMem, smTRANS_COMMAND	*lpTransCommand);
LPFN_CheckMem	fnChkMem2;


//static int	CompWareHouseMoney = 0;
int	WareHouseSubMoney = 0;					//창고에서 나온 누적 금액
int TotalSubMoney = 0;						//돈이 나간 금액
int TotalAddMoney = 0;						//돈이 들어온 금액
int	TotalAddExp = 0;						//들어온 경험치
int	TotalSubExp = 0;						//줄어든 경험치


smTRANS_COMMAND	*lpTransVirtualPotion = 0;


LPFN_CheckMem	fnChkMem;
DWORD	dwMemFunChkCode = 0;
//서버에서 메모리 값을 정해서 가져간다
DWORD funcCheckMemSum(DWORD FuncPoint, int count);



PacketPlayDataMinor	PlayData;
char	TransBuff[8192];
int		TransLen;



TRANS_ITEMINFO	TransThrowItem;
TRANS_ITEMINFO	TransRecvItem;


TRANS_TRADE_ITEMKEY	LastTransTradeItemKey;
DWORD				dwLastTransTradeKeyTime = 0;

int					InitClanMode = 0;

DWORD				dwYahooTime = 0;			//야호 유지시간

int					ServerHideMode = 0;			//서버 투명관리자 모드



PK_FIELD_STATE	PK_FieldState;


struct TRANS_TRADE_CHECKITEM
{
	int size, code;
	DWORD	dwSender;
	DWORD	dwRecver;
	DWORD	dwSum;

	DWORD	dwSendItemCode[MAX_TRADE_ITEM];
	DWORD	dwSendItemSum[MAX_TRADE_ITEM];

	DWORD	dwRecvItemCode[MAX_TRADE_ITEM];
	DWORD	dwRecvItemSum[MAX_TRADE_ITEM];
};


int		TradeItemSucessFlag = 0;
int		TradeRecvItemKeyFlag = 0;
int		TradeSendSucessFlag = 0;
DWORD	dwTradeMaskTime = 0;
int		TradeItemCancelCount = 0;

TRANS_TRADEITEMS	TransLastRecvTrade;

TRANS_TRADEITEMS	TransTradeItems_MyShop;			//개인상점 압축 구조


DWORD	dwLastWareHouseChkSum = 0;
int		TransAgingItemFlag;

smTRANS_COMMAND	TransServerConnectInfo;

DWORD	dwResistance_SendingTime = 0;

#define	ATT_MONSTER_MAX	128
#define	ATT_MONSTER_MASK	(ATT_MONSTER_MAX-1)

DWORD	dwAttMonsterCodeList[ATT_MONSTER_MAX];
int		AttMonsterCodeCount = 0;


int ClearAttMonsterCode()
{
	int cnt;
	for (cnt = 0; cnt < ATT_MONSTER_MAX; cnt++)
		dwAttMonsterCodeList[cnt] = 0;

	return TRUE;
}

int	AddAttMonsterCode(DWORD dwCode)
{
	int mcnt;
	if (dwCode)
	{
		mcnt = (AttMonsterCodeCount - 1)&ATT_MONSTER_MASK;
		if (dwAttMonsterCodeList[mcnt] == dwCode)
			return TRUE;
		mcnt = AttMonsterCodeCount & ATT_MONSTER_MASK;
		dwAttMonsterCodeList[mcnt] = dwCode;
		AttMonsterCodeCount++;
		return TRUE;
	}

	return FALSE;
}

int	CheckAttMonsterCode(DWORD dwCode)
{
	int cnt;
	for (cnt = 0; cnt < ATT_MONSTER_MAX; cnt++) {
		if (dwAttMonsterCodeList[cnt] == dwCode) return TRUE;
	}
	return FALSE;
}


sSERVER_MONEY	sServerMoney[3] = { {0,0,0,0,0},{0,0,0,0,0} };
sSERVER_EXP		sServerExp[3] = { {0,0,0,0},{0,0,0,0} };
DWORD			dwLastSendTotalExpMoenyTime = 0;


DWORD ConvSysTimeToGameTime(DWORD dwTime)
{
	return dwTime / GAME_WORLDTIME_MIN;
}

#define RECV_DATA_QUE_COUNT		64
#define RECV_DATA_QUE_MASK		63


DWORD	dwGetCharInfoTime = 0;


extern int szSpaceSorting(char *lpString);


#define SAVE_CHAT_COMMAND_MAX		16
#define SAVE_CHAT_COMMAND_MASK		15

DWORD	dwContiueChatCount = 0;

char *rsGetWord(char *q, char *p);

extern int WaveCameraMode;


int Ts_LastSendCounter;
DWORD	dwLastSendPosiTime = 0;
DWORD	dwLastSendPlayTime = 0;
DWORD	dwExtendServ_RecvTime = 0;
DWORD	dwUserServ_RecvTime = 0;
DWORD	dwMainServ_RecvTime = 0;
DWORD	dwDataServ_RecvTime = 0;




int LastSendCnt;

#define	NET_SENDING_WAIT_TIME		400
#define	NET_SENDING_WAIT_TIME2		1000

int NetStandCnt = 0;

DWORD	NetScoopTime = 3000;


int	ThrowPotionCount = 0;

char *szCmdOpenMonster[10] =
{
	"홉고블린",
	"홉고블린",
	"홉고블린",
	"킹호피",
	"타이탄",
	0,0,0,0,0
};

smTRANS_COMMAND	smMessageCommandBuff;


#define DEADLOCK_CHECK_LIMIT_TIME		(30*1000)
#define DEADLOCK_CHECK_LIMIT_TIME2		(60*1000)
#define RECONNECT_LIMIT_TIME			(7*1000)


static DWORD dwCheckNetCount = 0;
static DWORD dwLastTransCheckTime = 0;
static int	ReconnectCount = 0;



TRANS_SKIL_ATTACKDATA	Back_TransSkilAttackData;




DWORD EncodeParam(DWORD Param)
{
	return (Param + (Param << 4)) * 2002;
}
// 괏닸꾑욋
int	SaveWareHouse(sWAREHOUSE *lpWareHouse, TRANS_WAREHOUSE *lpTransWareHouse)
{
	TRANS_WAREHOUSE	TransWareHouse;
	sWAREHOUSE	WareHouseCheck;
	int	CompSize;
	int cnt;
	DWORD	dwChkSum;
	char	*szComp1, *szComp2;
	int	flag;

	if (lpTransWareHouse)
		flag = 1;
	else
		flag = 0;

	if (!flag && QuitSave)
		return FALSE;

	for (cnt = 0; cnt < 100; cnt++)
	{
		if (!lpWareHouse->WareHouseItem[cnt].bValid)
			ZeroMemory(&lpWareHouse->WareHouseItem[cnt], sizeof(ItemData));
	}

	CompSize = EecodeCompress((BYTE *)lpWareHouse, (BYTE *)TransWareHouse.Data, sizeof(sWAREHOUSE), sizeof(ItemData) * 100);

	if (!flag && CompSize > (8192 - 256))
		return FALSE;

	if (flag && CompSize > (8192 - 140))
		return FALSE;

	DecodeCompress((BYTE *)TransWareHouse.Data, (BYTE *)&WareHouseCheck, sizeof(sWAREHOUSE));

	szComp1 = (char *)lpWareHouse;
	szComp2 = (char *)&WareHouseCheck;

	dwChkSum = 0;

	for (cnt = 0; cnt < sizeof(sWAREHOUSE); cnt++)
	{
		if (szComp1[cnt] != szComp2[cnt])
			return FALSE;
		else
			dwChkSum += szComp1[cnt] * (cnt + 1);
	}

	TransWareHouse.code = smTRANSCODE_WAREHOUSE;
	TransWareHouse.size = sizeof(TRANS_WAREHOUSE) - (sizeof(sWAREHOUSE) - CompSize);
	TransWareHouse.DataSize = CompSize;
	TransWareHouse.dwChkSum = dwChkSum;
	TransWareHouse.wVersion[0] = Version_WareHouse;
	TransWareHouse.wVersion[1] = 0;

	TransWareHouse.dwTemp[0] = 0;
	TransWareHouse.dwTemp[1] = 0;
	TransWareHouse.dwTemp[2] = 0;
	TransWareHouse.dwTemp[3] = 0;
	TransWareHouse.dwTemp[4] = 0;

	dwLastWareHouseChkSum = dwChkSum;

	if (flag)
	{
		memcpy(lpTransWareHouse, &TransWareHouse, sizeof(TRANS_WAREHOUSE));
		return TRUE;
	}

	if (TransWareHouse.size > 8192)
		TransWareHouse.size = 8192;

	return FALSE;
}
int	SaveWareHouse(sWAREHOUSE *lpWareHouse)
{
	return SaveWareHouse(lpWareHouse, 0);
}
// 괏닸녘膠꾑욋
int SaveCaravan(sCARAVAN *lpCaravan, TRANS_CARAVAN *lpTransCaravan)
{
	TRANS_CARAVAN	TransCaravan;
	sCARAVAN		CaravanCheck;
	int	CompSize;
	int cnt;
	DWORD	dwChkSum;
	char	*szComp1, *szComp2;
	int		flag;

	if (lpTransCaravan)
		flag = 1;
	else
		flag = 0;

	if (!flag && QuitSave)
		return FALSE;

	for (cnt = 0; cnt < 100; cnt++)
	{
		if (!lpCaravan->Item[cnt].bValid)
			ZeroMemory(&lpCaravan->Item[cnt], sizeof(ItemData));
	}

	CompSize = EecodeCompress((BYTE *)lpCaravan, (BYTE *)TransCaravan.Data, sizeof(sCARAVAN), sizeof(ItemData) * 100);

	if (!flag && CompSize > (8192 - 256))
		return FALSE;

	if (flag && CompSize > (8192 - 140))
		return FALSE;

	DecodeCompress((BYTE *)TransCaravan.Data, (BYTE *)&CaravanCheck, sizeof(sCARAVAN));

	szComp1 = (char *)lpCaravan;
	szComp2 = (char *)&CaravanCheck;

	dwChkSum = 0;

	for (cnt = 0; cnt < sizeof(sCARAVAN); cnt++)
	{
		if (szComp1[cnt] != szComp2[cnt])
			return FALSE;
		else
			dwChkSum += szComp1[cnt] * (cnt + 1);
	}

	TransCaravan.code = smTRANSCODE_CARAVAN;
	TransCaravan.size = sizeof(TRANS_CARAVAN) - (sizeof(sCARAVAN) - CompSize);
	TransCaravan.DataSize = CompSize;
	TransCaravan.dwChkSum = dwChkSum;
	TransCaravan.wVersion[0] = Version_Caravan;
	TransCaravan.wVersion[1] = 0;

	if (flag)
	{
		memcpy(lpTransCaravan, &TransCaravan, sizeof(TRANS_CARAVAN));
		return TRUE;
	}
	if (TransCaravan.size > 8192)
		TransCaravan.size = 8192;

	return FALSE;
}

DWORD funcCheckMemSum(DWORD FuncPoint, int count)
{
	int cnt;
	DWORD dwSum;
	int	xcnt;
	DWORD *lpGetPrtectPoint;


	lpGetPrtectPoint = (DWORD *)FuncPoint;

	dwSum = 0;
	xcnt = 1;

	for (cnt = 0; cnt < count; cnt++) {
		xcnt += cnt;
		dwSum += lpGetPrtectPoint[cnt] * xcnt;
	}

	return dwSum;
}
DWORD	dwFuncList[][2] =
{
	{ 0,0 }
};

#define	RECV_TRANSITEM_QUE_MAX			256
#define	RECV_TRANSITEM_QUE_MASK			255

TRANS_ITEMINFO	Recv_TransItemInfo_Que[RECV_TRANSITEM_QUE_MAX];

int	RecvTransItemQue_Push = 0;
int	RecvTransItemQue_Pop = 0;


int	PushRecvTransItemQue(TRANS_ITEMINFO *lpTransItemInfo)
{
	int mCnt;

	mCnt = RecvTransItemQue_Push & RECV_TRANSITEM_QUE_MASK;

	memcpy(&Recv_TransItemInfo_Que[mCnt], lpTransItemInfo, sizeof(TRANS_ITEMINFO));
	RecvTransItemQue_Push++;
	RecvTransItemQue_Pop = RecvTransItemQue_Push - RECV_TRANSITEM_QUE_MASK;
	if (RecvTransItemQue_Pop < 0) RecvTransItemQue_Pop = 0;

	return TRUE;
}


TRANS_ITEMINFO	*FindRecvTransItemQue(DWORD dwCode, DWORD dwHead, DWORD dwChkSum)
{
	int cnt, mCnt;

	for (cnt = RecvTransItemQue_Pop; cnt < RecvTransItemQue_Push; cnt++)
	{
		mCnt = cnt & RECV_TRANSITEM_QUE_MASK;

		if (Recv_TransItemInfo_Que[mCnt].sItem.sItemID.ToInt() == dwCode && Recv_TransItemInfo_Que[mCnt].sItem.iChk1 == dwHead && Recv_TransItemInfo_Que[mCnt].sItem.iChk2 == dwChkSum)
			return &Recv_TransItemInfo_Que[mCnt];
	}

	return NULL;
}

struct	sDAMAGE_RECORD
{
	int	Damage;
	int	Count;
};

sDAMAGE_RECORD	sRecvDamage[3];
sDAMAGE_RECORD	sSendDamage[3];

//클랜원 정보 해독
int	RecvClanCommand(TRANS_CLAN_COMMAND_USER *lpTransClanUser, _CLAN_USER_INFO *ClanUserInfo)// char **lpClanUserName , DWORD *dwUserSpeedSum )
{
	int cnt;
	int cnt2;
	char *lpBuff;
	char	ch;

	lpBuff = lpTransClanUser->szUserBuff;

	if (lpTransClanUser->UserCount >= CLAN_USER_MAX) return FALSE;

	for (cnt = 0; cnt < lpTransClanUser->UserCount; cnt++) {
		ClanUserInfo[cnt].dwSpeedSum = ((DWORD *)lpBuff)[0];
		lpBuff += sizeof(DWORD);
		for (cnt2 = 0; cnt2 < 32; cnt2++) {
			ch = *lpBuff;
			ClanUserInfo[cnt].szName[cnt2] = ch;
			lpBuff++;
			if (!ch) break;
		}
		ClanUserInfo[cnt].szName[31] = 0;
	}

	return TRUE;
}