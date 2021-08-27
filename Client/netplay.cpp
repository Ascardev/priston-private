#include "StdAfx.h"
#include "smwsock.h"
#include "character.h"
#include "playmain.h"
#include "fileread.h"

#include "particle.h"
#include "record.h"
#include "netplay.h"
#include "playsub.h"
#include "cracker.h"
#include "srcLang\\jts.h"
#include "TextMessage.h"

#include "tjboy\\clanmenu\\tjclanDEF.h"
#include "tjboy\\clanmenu\\tjclan.h"
#include "tjboy\\clanmenu\\help.h"
#include "damage.h"
#include "skillsub.h"

#include "AreaServer.h"

#include "BellatraFontEffect.h"

#include "WinInt\\WinIntThread.h"
#include "WinInt\\WavIntHttp.h"
#include "WinInt\\ZipLib.h"

#include "CurseFilter.h"


//À¯·á ¾ÆÀÌÅÛ ±âº» »ç¿ë½Ã°£ ¼³Á¤
#define	PRIME_ITEM_TIME_THIRDEYES		(60*60*24)
#define	PRIME_ITEM_TIME_EXPUP			(60*60*24)

#define	PRIME_ITEM_TIME_THIRDEYESx7		(60*60*24*7)
#define	PRIME_ITEM_TIME_EXPUPx7			(60*60*24*7)

#define	PRIME_ITEM_TIME_VAMPCUSPID		(60*60*3)	// pluto ¹ìÇÇ¸¯ Ä¿½ºÇÍ 3½Ã°£
#define	PRIME_ITEM_TIME_MANARECHARG		(60*60*3)	// pluto ¸¶³ª ¸®Â÷Â¡ Æ÷¼Ç 3½Ã°£

#define	PRIME_ITEM_TIME_VAMPCUSPIDx2	(60*60*6)	// pluto ¹ìÇÇ¸¯ Ä¿½ºÇÍ 1ÀÏ
#define	PRIME_ITEM_TIME_MANARECHARGx2	(60*60*6)	// pluto ¸¶³ª ¸®Â÷Â¡ Æ÷¼Ç 1ÀÏ
#define PRIME_ITEM_TIME_6HOUR			(60*60*6)

#define	PRIME_ITEM_TIME_PACKAGE1		(60*60*3)
#define	PRIME_ITEM_TIME_PACKAGE2		(60*60*24)
#define	PRIME_ITEM_TIME_PACKAGE3		(60*60*24*7)
#define	PRIME_ITEM_TIME_PACKAGE4		(60*60*24*30)
#define	PRIME_ITEM_TIME_PACKAGE5		(60*60*1) // Àåº° - °æÇèÄ¡Áõ°¡ Æ÷¼Ç(100% 1½Ã°£)

extern HWND hwnd;

#define SERVER_CHAR_INFO


#define RECORD_TIME_STEP		(5*60*1000)

#define NET_LOADING_WAIT_LIMIT		10000

rsBLESS_CASTLE	rsBlessCastle;


extern CRITICAL_SECTION	cSection;
extern rsRECORD_DBASE	rsRecorder;
DWORD	dwLastRecordTime = 0;

CRITICAL_SECTION	cServSection;

DWORD dwWeatherPlayTime = 0;
DWORD dwBabelPlayTime = 0;
DWORD BabelPlayField = 0;

int Debug_RecvCount1 = 0;
int Debug_RecvCount2 = 0;
int Debug_RecvCount3 = 0;

int NetWorkInitFlag = 0;
int	BellatraEffectInitFlag = 0;
SBL_SetFontEffect SoD_SetFontEffect;


DWORD	dwTime_ServerT = 0;
DWORD	dwTime_ConnectMS = 0;
DWORD   dwTime_ServerGMT = 0;


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
int	rsRecvExtendServer = TRUE;

DWORD dwMyIP;

char *szDefaultServIP = "127.0.0.1";

char *szNetLogFile = "debugnet.log";

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


//static int	CompWareHouseMoney = 0;
int	WareHouseSubMoney = 0;					//Ã¢°í¿¡¼­ ³ª¿Â ´©Àû ±Ý¾×
int TotalSubMoney = 0;						//µ·ÀÌ ³ª°£ ±Ý¾×
int TotalAddMoney = 0;						//µ·ÀÌ µé¾î¿Â ±Ý¾×
int	TotalAddExp = 0;						//µé¾î¿Â °æÇèÄ¡
int	TotalSubExp = 0;						//ÁÙ¾îµç °æÇèÄ¡


smTRANS_COMMAND	*lpTransVirtualPotion = 0;

DWORD	dwMemFunChkCode = 0;

DWORD funcCheckMemSum(DWORD FuncPoint, int count);
//¸ðµâ°Ë»ç ÇÏ¿© ¼­¹ö·Î º¸³»±â
int CheckProcessModule();



PacketPlayDataMinor	PlayData;
char	TransBuff[smSOCKBUFF_SIZE];
int		TransLen;



TRANS_ITEMINFO	TransThrowItem;
TRANS_ITEMINFO	TransRecvItem = { 0 };


TRANS_TRADE_ITEMKEY	LastTransTradeItemKey;
DWORD				dwLastTransTradeKeyTime = 0;

int					InitClanMode = 0;

DWORD				dwYahooTime = 0;			//¾ßÈ£ À¯Áö½Ã°£

int					ServerHideMode = 0;			//¼­¹ö Åõ¸í°ü¸®ÀÚ ¸ðµå



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

TRANS_TRADEITEMS	TransTradeItems_MyShop;			//°³ÀÎ»óÁ¡ ¾ÐÃà ±¸Á¶


DWORD	dwLastWareHouseChkSum = 0;
int		TransAgingItemFlag;

smTRANS_COMMAND	TransServerConnectInfo;

int HoRecvMessage(DWORD dwCode, void *RecvBuff);
int RecvTradeSucessKey(TRANS_TRADE_ITEMKEY *lpTransTradeItemKey, sTRADE *lpTrade);
int SendTradeSucessKey(sTRADE *lpTrade, DWORD dwSender);
int RecvTradeCheckItem(TRANS_TRADE_CHECKITEM *lpTransTradeCheckItem);
int ThrowItemToServer(smTRANS_COMMAND_EX *lpTransCommand);
int RecvCheckItemFromServer(TRANS_ITEM_CODE *lpTransItemCode);
int	SendClientFuncPos();
int OpenTimeCheckThread();
int SendPlayTimerMax();

TRANS_ITEMINFO	*FindRecvTransItemQue(DWORD dwCode, DWORD dwHead, DWORD dwChkSum);
int	PushRecvTransItemQue(TRANS_ITEMINFO *lpTransItemInfo);
int RecvProcessSkill(smTRANS_COMMAND *lpTransCommand);
int RecvPartySkillFromServer(TRANS_PARTY_SKILL *lpTransPartySkill);
int FiltQuestItem(TRANS_ITEMINFO	*lpTransItemInfo, DWORD dwPacketCode);
int SucessLinkCore(smTRANS_COMMAND_EX *lpTransCommandEx);
int RecvSodGameInfomation(void *Info);
int RecvForceOrbItem(TRANS_ITEMINFO_GROUP2 *lpTransItemGroup2);

rsBLESS_CASTLE	rsBlessCastleOld;
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

int CheckServerInfo(smTRANS_COMMAND *lpTransCommand)
{
	if (GAME_VERSION < lpTransCommand->WParam)
	{
		SetGameError(1);
		return TRUE;
	}
	if (lpTransCommand->LParam > 0)
	{
		SetGameError(2);
		return TRUE;
	}
	SetGameError(0);
	return TRUE;
}
int SendProcessInfo()
{
	TRANS_CHATMESSAGE	smTransChatMessage;

	smTransChatMessage.code = smTRANSCODE_PROCESSINFO;
	smTransChatMessage.dwIP = dwExeCheckSum;
	smTransChatMessage.dwObjectSerial = dwExeCheckSum;

	lstrcpy(smTransChatMessage.szMessage, szProcessPath);
	smTransChatMessage.size = 32 + lstrlen(szProcessPath);

	SENDPACKETL(&smTransChatMessage);

	return FALSE;
}

scITEM *FindScItem(int x, int z)
{
	int cnt;

	for (cnt = 0; cnt < DISP_ITEM_MAX; cnt++)
	{
		if (scItems[cnt].Flag && scItems[cnt].pX == x && scItems[cnt].pZ == z)
			return &scItems[cnt];
	}

	return NULL;
}
scITEM *FindEmptyScItem()
{
	int cnt;

	for (cnt = 0; cnt < DISP_ITEM_MAX; cnt++)
	{
		if (!scItems[cnt].Flag)
			return &scItems[cnt];
	}

	return NULL;
}
int GetTradeDistance(Unit *lpChar)
{
	int	x, y, z;
	int dist;

	x = (lpCurPlayer->pX - lpChar->pX) >> FLOATNS;
	y = (lpCurPlayer->pY - lpChar->pY) >> FLOATNS;
	z = (lpCurPlayer->pZ - lpChar->pZ) >> FLOATNS;

	dist = x * x + y * y + z * z;

	if (dist < (256 * 256))
		return TRUE;

	return FALSE;
}
int GetTradeDistanceFromCode(DWORD dwObjectSerial)
{
	Unit *lpChar;

	lpChar = FindAutoPlayer(dwObjectSerial);

	if (lpChar && lpChar->DisplayFlag && lpChar->sCharacterData.szName[0])
		return  GetTradeDistance(lpChar);

	return FALSE;
}
int	CheckStartCharInfo()
{
	CharacterData	sCharacterData;
	int cnt;

	memcpy(&sCharacterData, sinChar, sizeof(CharacterData));

	CheckCharForm();

	CodeXorLife = (dwPlayTime*sCharacterData.sHP.sMin) & 0xFFFF;
	cnt = sCharacterData.iAgility +
		sCharacterData.iHealth + 
		sCharacterData.iSpirit +
		sCharacterData.iStrength +
		sCharacterData.iTalent;

	if (sCharacterData.iLevel >= 2 || cnt > 102 || sCharacterData.iExp || sCharacterData.iRank || sCharacterData.iGold)
	{
		SendSetHackUser2(6000, sCharacterData.iGold);
		WarningHack = TRUE;
		return FALSE;
	}

	lpCurPlayer->sCharacterData.sHP.sMin ^= CodeXorLife;
	ReformCharForm();

	return TRUE;
}

sSERVER_MONEY	sServerMoney[3] = { {0,0,0,0,0},{0,0,0,0,0} };
sSERVER_EXP		sServerExp[3] = { {0,0,0,0},{0,0,0,0} };
DWORD			dwLastSendTotalExpMoenyTime = 0;

//·¢ËÍ×ÜµÄ½ðÇ®ºÍ½ðÇ®µ½·þÎñÆ÷
int	SendTotalExpMoney()
{
	TRANS_TOTAL_EXPMONEY	TransTotalExpMoney;

	if ((dwLastSendTotalExpMoenyTime + 30000) > dwPlayTime)
		return FALSE;

	TransTotalExpMoney.code = smTRANSCODE_CHECK_EXPMONEY;
	TransTotalExpMoney.size = sizeof(TRANS_TOTAL_EXPMONEY);

	dwLastSendTotalExpMoenyTime = dwPlayTime;

	return TRUE;
}
int CheckServerMoney(SocketData * pcSocketData, TRANS_ITEMINFO	*lpTransItemInfo)
{
	sSERVER_MONEY	*lpServerMoney;

	lpServerMoney = &sServerMoney[0];

	if (lpServerMoney)
	{
		lpServerMoney->InputMoney += lpTransItemInfo->sItem.iGold;
		lpServerMoney->Counter++;
		lpServerMoney->TotalX = lpTransItemInfo->x;
		lpServerMoney->TotalY = lpTransItemInfo->y;
		lpServerMoney->TotalZ = lpTransItemInfo->z;

		int cnt;
		cnt = lpServerMoney->TotalZ ^ (lpServerMoney->TotalX + lpServerMoney->TotalY);
		cnt += 200;
		if (cnt < lpServerMoney->InputMoney) {
			//SendSetHackUser( 82 );
		}
	}

	return TRUE;
}

Unit *FindAutoPlayer(DWORD dwObjectSerial)
{
	int cnt;

	for (cnt = 0; cnt < MAX_UNITS; cnt++)
	{
		if (chrOtherPlayer[cnt].bActive && chrOtherPlayer[cnt].iID == dwObjectSerial)
			return &chrOtherPlayer[cnt];
	}

	return NULL;
}
Unit *FindChrPlayer(DWORD dwObjectSerial)
{
	int cnt;

	if (lpCurPlayer->iID == dwObjectSerial)
		return lpCurPlayer;

	for (cnt = 0; cnt < MAX_UNITS; cnt++)
	{
		if (chrOtherPlayer[cnt].bActive && chrOtherPlayer[cnt].iID == dwObjectSerial)
			return &chrOtherPlayer[cnt];
	}

	return NULL;
}
Unit *FindDeadPartyUser()
{
	int cnt;
	Unit *lpChar;
	int dist, x, y, z;
	int	NearDist;

	lpChar = 0;
	NearDist = 300 * 300;

	for (cnt = 0; cnt < MAX_UNITS; cnt++)
	{
		if (chrOtherPlayer[cnt].bActive && chrOtherPlayer[cnt].dwExclusiveNum && chrOtherPlayer[cnt].sCharacterData.iType == CHARACTERTYPE_Player)
		{
			if (chrOtherPlayer[cnt].psModelAnimation->iType == ANIMATIONTYPE_Die)
			{
				x = (lpCurPlayer->pX - chrOtherPlayer[cnt].pX) >> FLOATNS;
				y = (lpCurPlayer->pY - chrOtherPlayer[cnt].pY) >> FLOATNS;
				z = (lpCurPlayer->pZ - chrOtherPlayer[cnt].pZ) >> FLOATNS;

				dist = x * x + z * z + y * y;

				if (dist < NearDist)
				{
					lpChar = &chrOtherPlayer[cnt];
					NearDist = dist;
				}
			}
		}
	}

	return lpChar;
}
Unit *FindNearMonster(Unit *lpCurChar)
{
	int cnt;
	Unit *lpChar;
	int dist, x, y, z;
	int	NearDist;

	lpChar = NULL;
	NearDist = 300 * 300;

	if (!lpCurChar)
		return NULL;

	if (lpCurChar != lpCurPlayer)
	{
		x = (lpCurChar->pX - lpCurPlayer->pX) >> FLOATNS;
		y = (lpCurChar->pY - lpCurPlayer->pY) >> FLOATNS;
		z = (lpCurChar->pZ - lpCurPlayer->pZ) >> FLOATNS;

		dist = x * x + z * z + y * y;
		if (dist < NearDist)
		{
			if (!lpCurChar->sCharacterData.iClanID ||
				lpCurChar->sCharacterData.iClanID != lpCurPlayer->sCharacterData.iClanID)
			{
				if (lpCurChar->sCharacterData.iType == CHARACTERTYPE_Monster)
				{
					lpChar = lpCurPlayer;
					NearDist = dist;
				}
			}
		}
	}

	for (cnt = 0; cnt < MAX_UNITS; cnt++)
	{
		if (chrOtherPlayer[cnt].bActive && chrOtherPlayer[cnt].sCharacterData.iType == CHARACTERTYPE_Monster && lpCurChar != &chrOtherPlayer[cnt])
		{
			if (chrOtherPlayer[cnt].sCharacterData.iMonsterType != MONSTERTYPE_Friendly &&
				chrOtherPlayer[cnt].sCharacterData.sHP.sMin > 0 &&
				(!chrOtherPlayer[cnt].sCharacterData.iClanID || chrOtherPlayer[cnt].sCharacterData.iClanID != lpCurChar->sCharacterData.iClanID))
			{
				x = (lpCurChar->pX - chrOtherPlayer[cnt].pX) >> FLOATNS;
				y = (lpCurChar->pY - chrOtherPlayer[cnt].pY) >> FLOATNS;
				z = (lpCurChar->pZ - chrOtherPlayer[cnt].pZ) >> FLOATNS;

				dist = x * x + z * z + y * y;

				if (dist < NearDist)
				{
					lpChar = &chrOtherPlayer[cnt];
					NearDist = dist;
				}
			}
		}
	}

	return lpChar;
}
Unit *FindEmptyChar()
{
	int cnt;

	for (cnt = 0; cnt < MAX_UNITS; cnt++)
	{
		if (!chrOtherPlayer[cnt].bActive)
			return &chrOtherPlayer[cnt];
	}

	return NULL;
}
DWORD ConvSysTimeToGameTime(DWORD dwTime)
{
	return dwTime / GAME_WORLDTIME_MIN;
}

#define RECV_DATA_QUE_COUNT		64
#define RECV_DATA_QUE_MASK		63


class	rsTRANS_SERVER
{
	char	TransBuff[smSOCKBUFF_SIZE];

	rsRECORD_DBASE	*lpRecorder;


	smTHREADSOCK	*RecvDataQue[RECV_DATA_QUE_COUNT];
	int				RecvDataQuePush;
	int				RecvDataQuePop;

	TRANS_PLAYPOS	TransPlayPosLast;
	int				TransPlayPosCount;

public:

	int	Init();
	int RecvMessage(SocketData * pcSocketData, Packet * psPacket);
};

DWORD	dwGetCharInfoTime = 0;


int rsTRANS_SERVER::RecvMessage(SocketData * pcSocketData, Packet * psPacket)
{
	//DWORD *IPData;
	int cnt;
	int x;
	int ServerCode;
	Unit	*lpChar;

	int RcvCnt;

	TRANS_ITEMINFO				*lpTransItemInfo;

	PacketPlayDataMinor			*lpPlayData1;
	smTRANS_COMMAND				TransCommand;
	smTRANS_COMMAND_EX			TransCommandEx;
	smTRANS_COMMAND				*lpTransCommand;
	smTRANS_ACITON_ITEM			*lpTransActionItem;
	smTRANS_CHAR_COMMAND		*lpTransCharCommand;
	smTRNAS_PLAYERINFO			*lpTransPlayerInfo;
	TRANS_CHATMESSAGE			*lpTransChatMessage;
	TRANS_POST_ITEM				*lpTransPostItem;

	switch (psPacket->iHeader)
	{
	case smTRANSCODE_CHATMESSAGE:
		break;
	case smTRANSCODE_PLAYLIST:
		break;

	case smTRANSCODE_PLAYERINFO:
		lpTransPlayerInfo = (smTRNAS_PLAYERINFO *)psPacket;

		lpChar = FindAutoPlayer(lpTransPlayerInfo->dwObjectSerial);

		if (lpChar)
		{
			lpChar->RecvPlayData(pcSocketData, psPacket);
		}

		if (lpTransPlayerInfo->sCharacterData.iType == CHARACTERTYPE_Monster && lpTransPlayerInfo->sCharacterData.iMonsterType != MONSTERTYPE_Friendly)
			SaveCharInfoCache(lpTransPlayerInfo);

		break;

	case smTRANSCODE_PLAYERINFO_Q:
		lpChar = FindAutoPlayer(((smTRNAS_PLAYERINFO_QUICK *)psPacket)->dwObjectSerial);

		if (lpChar)
		{
			lpChar->RecvPlayData(pcSocketData, psPacket);
		}
		break;

	case smTRANSCODE_PLAYDATAGROUP:
		smPLAYDATA_GROUP *lpPlayDataGroup;

		PacketGameStatusBase * psPacketGameStatus;

		char *lpTransBuff;

		lpPlayDataGroup = (smPLAYDATA_GROUP *)psPacket;
		lpTransBuff = (char *)psPacket + sizeof(smPLAYDATA_GROUP);

		ServerCode = 0;
		RcvCnt = 0;

		ServerCode = PLAY_SERVER_CODE_MAIN;

		for (cnt = 0; cnt < lpPlayDataGroup->PlayDataCnt; cnt++)
		{
			lpPlayData1 = (PacketPlayDataMinor *)lpTransBuff;
			lpChar = FindAutoPlayer(lpPlayData1->dwObjectID);

			if (lpChar)
			{
				lpChar->RecvPlayData2(lpTransBuff);

				if (lpChar->iPlayBuffCount < (lpChar->PlayBuffPosi_End - 70))
					lpChar->iPlayBuffCount = lpChar->PlayBuffPosi_End - 70;
			}
			else
			{
				if (RcvCnt < 8 || (RcvCnt < 16 && ((int *)lpTransBuff)[1] == smTRANSCODE_TRANSPLAYDATA))
				{
					RcvCnt++;
					lpChar = FindEmptyChar();
					if (lpChar)
					{
						lpChar->Init();
						lpChar->bActive = TRUE;
						lpChar->sCharacterData.szName[0] = 0;
						lpChar->ActionPattern = 99;
						lpChar->Pattern = 0;
						lpChar->AutoPlayer = TRUE;
						lpChar->DisplayFlag = FALSE;
						lpChar->psModelAnimation = 0;

						lpChar->iID = lpPlayData1->dwObjectID;
						lpChar->ServerCode = ServerCode;

						lpChar->ResetAttackTrans();

						lpTransPlayerInfo = GetCharInfoCache(lpTransBuff);
						if (lpTransPlayerInfo)
						{
							lpChar->SetTransPlayerInfo(lpTransPlayerInfo);
						}
						else
						{
							TransCommand.code = smTRANSCODE_GETPLAYERINFO;
							TransCommand.size = sizeof(smTRANS_COMMAND);
							TransCommand.WParam = lpPlayData1->dwObjectID;

							if (pcSocketData == SOCKETG)
								SENDPACKETG(&TransCommand);
							else
								SENDPACKETL(&TransCommand);
						}
					}
				}
			}
			lpTransBuff += lpPlayData1->iLength;
		}

		psPacketGameStatus = (PacketGameStatusBase *)lpTransBuff;

		if (psPacketGameStatus->iHeader == PKTHDR_GameStatus && psPacketGameStatus->lID == UNIT->iID)
		{
			switch (psPacketGameStatus->iStatusID)
			{
			case smCOMMAND_PLAY_BABEL:
			{
				PacketGameStatusBabelStormMap * psPackets;
				psPackets = (PacketGameStatusBabelStormMap *)psPacketGameStatus;

				dwBabelPlayTime = dwPlayTime + 5000;
				BabelPlayField = psPackets->eBabelStormMapID;
			}
				break;
			case smCOMMAND_PLAY_PK_FIELD:
			{
				PacketGameStatusPvPMap * psPackets;
				psPackets = (PacketGameStatusPvPMap *)psPacketGameStatus;

				PK_FieldState.dwPlay_FieldTime = dwPlayTime + 10000;
				PK_FieldState.FieldCode = psPackets->iPvPMapID;
			}
				break;
			case smCOMMAND_PLAY_BELSS_CASTLE:
			{
				PacketGameStatusBlessCastle * psPackets;
				psPackets = (PacketGameStatusBlessCastle *)psPacketGameStatus;

				memcpy(&rsBlessCastleOld, &rsBlessCastle, sizeof(rsBLESS_CASTLE));

				rsBlessCastle.CastleMode = psPackets->iCastMode;
				rsBlessCastle.DefenceLevel = psPackets->iDefenseLevel;
				rsBlessCastle.dwMasterClan = psPackets->iClanID;
				rsBlessCastle.TimeSec[0] = psPackets->saTimeSec[0];
				rsBlessCastle.TimeSec[1] = psPackets->saTimeSec[1];
				rsBlessCastle.bCrystalSolderCount[0] = psPackets->baSoldierCount[0];
				rsBlessCastle.bCrystalSolderCount[1] = psPackets->baSoldierCount[1];
				rsBlessCastle.bCrystalSolderCount[2] = psPackets->baSoldierCount[2];
				rsBlessCastle.bCrystalSolderCount[3] = psPackets->baSoldierCount[3];

				chaSiege.ShowPlayTime(rsBlessCastle.TimeSec[1] - rsBlessCastle.TimeSec[0]);

				lpCurPlayer->sBlessCastle_Damage[0] = psPackets->sConRate;
				lpCurPlayer->sBlessCastle_Damage[1] = psPackets->sBattlePoints;
				lpCurPlayer->sBlessCastle_Param[0] = 0;
				lpCurPlayer->sBlessCastle_Param[1] = 0;

				if (rsBlessCastle.CastleMode == 3)
				{
					if (rsBlessCastleOld.CastleMode == 1)
					{
						RestartPlayCount = 400;
						StopBGM();
						esPlayContSound(14);
						chaSiege.ShowExitMessage();

						if (rsBlessCastle.dwMasterClan && rsBlessCastle.dwMasterClan == GetClanCode(lpCurPlayer->sCharacterData.iClanID))
							lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Yahoo);
					}
				}
				else if (rsBlessCastleOld.CastleMode && rsBlessCastle.CastleMode == 0)
				{
					if (!lpCurPlayer->sCharacterData.iClanID ||
						rsBlessCastle.dwMasterClan != GetClanCode(lpCurPlayer->sCharacterData.iClanID))
						GAMEMAP->LoadWarpMap(MAPID_BlessCastle);
				}
				if ((dwResistance_SendingTime + 1000 * 60) < dwPlayTime)
					SendResistanceToServer();

				if (rsBlessCastle.dwMasterClan != rsBlessCastleOld.dwMasterClan)
					UpdateCastleMasterClan(rsBlessCastle.dwMasterClan);
			}
				break;
				//ÏÂÓêÐ§¹û
			case smCOMMAND_PLAY_WEATHER:
			{
				//dwWeatherPlayTime = dwPlayTime + lpTransCommand->SParam * 1000;
			}
				break;
			}
		}
		break;

	case smTRANSCODE_ATTACKDATA:
		if (((TRANS_ATTACKDATA *)psPacket)->dwDamageChkSum != dm_GetDamgeChkSum_S2V((TRANS_ATTACKDATA *)psPacket))
		{
			SendSetHackUser3(8580, ((TRANS_ATTACKDATA *)psPacket)->Power, 0);
			break;
		}
		CheckInvenItemToServer();
		Record_RecvDamage(pcSocketData, ((TRANS_ATTACKDATA *)psPacket)->Power);

	case smTRANSCODE_PLAYDATA1:
	case smTRANSCODE_TRANSPLAYDATA:

		ServerCode = PLAY_SERVER_CODE_MAIN;
		
		lpPlayData1 = (PacketPlayDataMinor *)psPacket;
		lpChar = FindAutoPlayer(lpPlayData1->dwObjectID);
		if (lpChar)
		{
			lpChar->RecvPlayData(pcSocketData, psPacket);
			if (lpChar->iPlayBuffCount < (lpChar->PlayBuffPosi_End - 70))
				lpChar->iPlayBuffCount = lpChar->PlayBuffPosi_End - 70;
		}
		break;

	case smTRANSCODE_ATTACK_SLASH_LIST:
		memcpy(&Trans_SplashCharList, psPacket, sizeof(TRANS_SKIL_ATTACKDATA));
		break;
		// µØÃæÊ°È¡ÎïÆ·
	case smTRANSCODE_PLAYITEM:
		smTRANS_ITEMS	*lpTransItems;
		scITEM			*lpScItem;

		lpTransItems = (smTRANS_ITEMS *)psPacket;

		ServerCode = PLAY_SERVER_CODE_MAIN;

		for (cnt = 0; cnt < lpTransItems->Count; cnt++)
		{
			lpScItem = FindScItem(lpTransItems->Items[cnt].x, lpTransItems->Items[cnt].z);
			if (lpScItem)
				lpScItem->dwLastTransTime = dwPlayTime;
			else
			{
				lpScItem = FindEmptyScItem();
				if (lpScItem)
				{
					lpScItem->SetTransItem(&lpTransItems->Items[cnt]);
					lpScItem->ServerCode = ServerCode;
				}
			}
		}
		break;

	case smTRANSCODE_DELITEM:
		lpTransActionItem = (smTRANS_ACITON_ITEM *)psPacket;
		lpScItem = FindScItem(lpTransActionItem->x, lpTransActionItem->z);

		if (lpScItem)
		{
			EnterCriticalSection(&cDrawSection);
			smEnterTextureCriticalSection();

			lpScItem->Close();

			smLeaveTextureCriticalSection();
			LeaveCriticalSection(&cDrawSection);
		}
		break;
	case smTRANSCODE_PUTITEM:
		lpTransItemInfo = (TRANS_ITEMINFO *)psPacket;

		if (FiltQuestItem(lpTransItemInfo, smTRANSCODE_PUTITEM) == FALSE)
			break;

		if (PushRecvTransItemQue(lpTransItemInfo) == TRUE)
		{
			TransCommandEx.code = smTRANSCODE_GETITEM;
			TransCommandEx.size = sizeof(smTRANS_COMMAND_EX);
			TransCommandEx.WParam = lpTransItemInfo->sItem.sItemID.ToInt();
			TransCommandEx.LParam = lpTransItemInfo->sItem.iChk1;
			TransCommandEx.SParam = lpTransItemInfo->sItem.iChk2;
			TransCommandEx.EParam = lpTransItemInfo->sItem.iGold^smTRANSCODE_GETITEM^lpTransItemInfo->sItem.iChk2;

			TransCommandEx.WxParam = lpTransItemInfo->dwSeCode[0];
			TransCommandEx.LxParam = lpTransItemInfo->dwSeCode[1];
			TransCommandEx.SxParam = lpTransItemInfo->dwSeCode[2];
			TransCommandEx.ExParam = lpTransItemInfo->dwSeCode[3];

			SENDPACKETL(&TransCommandEx);

			break;
		}
		break;
	case smTRANSCODE_GETITEM:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;

		lpTransItemInfo = FindRecvTransItemQue(lpTransCommand->WParam, lpTransCommand->LParam, lpTransCommand->SParam);

		if (!lpTransItemInfo)
			break;

		if (FiltQuestItem(lpTransItemInfo, smTRANSCODE_GETITEM) == FALSE)
			break;

		ComparePotion();

		memcpy(&TransRecvItem, lpTransItemInfo, sizeof(TRANS_ITEMINFO));

		if (CheckItemForm(&lpTransItemInfo->sItem) == TRUE)
		{
			if (lpTransItemInfo->sItem.sItemID.ToInt() == (sinGG1 | sin01))
			{
				if (cInvenTory.CheckMoneyLimit(lpTransItemInfo->sItem.iGold) == TRUE)
				{
					lpCurPlayer->sCharacterData.iGold += lpTransItemInfo->sItem.iGold;
					ReformCharForm();
					sinPlaySound(SIN_SOUND_COIN, 400);

					CheckServerMoney(pcSocketData, lpTransItemInfo);

				}
				else
					ThrowPutItem2(&lpTransItemInfo->sItem, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
			}
			else
			{
				if ((lpTransItemInfo->sItem.sItemID.ToItemType()) == sinQT1 || lpTransItemInfo->sItem.eCraftType == ITEMCRAFTTYPE_QuestWeapon)
				{
					if (sinSetQuestItem(&lpTransItemInfo->sItem) == TRUE)
						SaveGameData();
				}
				else
				{
					if ((lpTransItemInfo->sItem.sItemID.ToItemBase()) == (sinPM1&sinITEM_MASK1))
					{
						if (SETTINGHANDLE->Get().bDebugMode && VRKeyBuff['P'] && VRKeyBuff['O'])
							lpTransItemInfo->sItem.iPotionCount *= 2;
					}

					sinSetInvenItem(&lpTransItemInfo->sItem);

					if (lpTransItemInfo->sItem.iSalePrice >= 3000)
						SaveGameData();

					if ((lpTransItemInfo->sItem.sItemID.ToItemBase()) == (sinPM1&sinITEM_MASK1))
						ResetPotion2();
				}
			}
		}
		ZeroMemory(&TransRecvItem, sizeof(TRANS_ITEMINFO));
		ZeroMemory(lpTransItemInfo, sizeof(TRANS_ITEMINFO));

		ResetInvenItemCode();
		break;

	case smTRANSCODE_MESSAGEBOX:
		lpTransChatMessage = (TRANS_CHATMESSAGE *)psPacket;
		cMessageBox.ShowMessageEvent(lpTransChatMessage->szMessage);
		break;
		//½ÓÊÜÏûÏ¢Ð­Òé
	case PKTHDR_ChatMessage:
		CHATBOX->HandlePacket((PacketChatBoxMessage *)psPacket);
		break;
		//½ÓÊÜÉËº¦ÏÔÊ¾Ð­Òé
	case smTRANSCODE_DISPLAYDAMGE:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		lpChar = FindAutoPlayer((DWORD)(lpTransCommand->LParam));
		if (lpChar)
		{
			lpChar->dwDamgeTimer = dwPlayTime + 1000 * 2;
			lpChar->Damge = lpTransCommand->WParam;
			lpChar->DmgType[0] = lpTransCommand->SParam;
			lpChar->DmgType[1] = lpTransCommand->EParam;
			lpChar->DmgBlendValue = 255;
		}
		break;
		// ½ÓÊÜµÇÂ¼ºóµÄÐÅÏ¢
	case smTRANSCODE_RECORDDATA:
		if (!lpRecorder)
		{
			lpRecorder = new rsRECORD_DBASE;
			lpRecorder->TransLastPartCount = 0;
			ZeroMemory(lpRecorder->TransDataBlock, 64);
		}
		if (lpRecorder->RecvRecordDataFromServer((TRANS_RECORD_DATAS *)psPacket) == TRUE)
		{
			lpRecorder->ResotrRecordData(&lpCurPlayer->sCharacterData, cInvenTory.InvenItem, cInvenTory.InvenItemTemp, &MouseItem);

			if (SETTINGHANDLE->Get().bDebugMode)
				CHATGAMEHANDLE->AddChatBoxText(lpRecorder->TransRecordData.GameSaveInfo.szMasterID);

			delete lpRecorder;
			lpRecorder = 0;

			dwLoadingTime = 0;

			if ((lpCurPlayer->sCharacterData.iClass == CHARACTERCLASS_Archer || lpCurPlayer->sCharacterData.iClass == CHARACTERCLASS_Atalanta || lpCurPlayer->sCharacterData.iClass == CHARACTERCLASS_Priestess || lpCurPlayer->sCharacterData.iClass == CHARACTERCLASS_Assassin) && lpCurPlayer->Pattern)
				lpCurPlayer->SetPattern(lpCurPlayer->Pattern);

			lpCurPlayer->bActive = TRUE;

			if (!lpCurPlayer->sCharacterData.dwEventTime_T || GetPlayTime_T() > lpCurPlayer->sCharacterData.dwEventTime_T)
			{
				lpCurPlayer->sCharacterData.SizeLevel = 1;
				lpCurPlayer->sCharacterData.dwEventTime_T = 0;
			}
			if (cldata.myPosition == 100 || cldata.myPosition == 101 || cldata.myPosition == 104)
			{
				lpCurPlayer->sCharacterData.iClanID = cldata.intClanMark;
				lpCurPlayer->dwClanManageBit = cldata.CNFlag;
			}
			else
				lpCurPlayer->sCharacterData.iClanID = 0;

			if (cldata.myPosition)
				InitClanMode = cldata.myPosition;

			rsRecorder.dwNextRecordTime = dwPlayTime + RECORD_TIME_STEP;
			lpCurPlayer->SendCharInfo();


			if (lpCurPlayer->sCharacterData.sHP.sMin == 0)
			{
				lpCurPlayer->MoveFlag = FALSE;

				Point3D sPosition = GAMEMAP->WarpMap();

				lpCurPlayer->SetPosi(sPosition.iX, 0, sPosition.iZ, 0, 0, 0);
				TraceCameraPosi.x = lpCurPlayer->pX;
				TraceCameraPosi.y = lpCurPlayer->pY;
				TraceCameraPosi.z = lpCurPlayer->pZ;
				TraceTargetPosi.x = lpCurPlayer->pX;
				TraceTargetPosi.y = lpCurPlayer->pY;
				TraceTargetPosi.z = lpCurPlayer->pZ;

				lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Revive);
				StartEffect(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, EFFECT_GAME_START1);
				SetDynLight(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 100, 100, 100, 0, 200);
				CharPlaySound(lpCurPlayer);
				dwBattleTime = 0;
				dwBattleQuitTime = 0;

				lpCurPlayer->iLoadedMapIndex = -1;
				if (smGameStage[0]) {
					cnt = smGameStage[0]->GetFloorHeight(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, lpCurPlayer->Pattern->SizeHeight);
					lpCurPlayer->iLoadedMapIndex = 0;
				}
				if (cnt == CLIP_OUT && smGameStage[1])
					lpCurPlayer->iLoadedMapIndex = 1;
			}

			cnt = lpCurPlayer->sCharacterData.sHP.sMin;

			if (cnt > lpCurPlayer->sCharacterData.sHP.sMax || cnt < 0)
			{
				CheckCharForm();
				lpCurPlayer->sCharacterData.sHP.sMin = lpCurPlayer->sCharacterData.sHP.sMax / 2;
				ReformCharForm();
			}

			CheckCharForm();

			CodeXorLife = (dwPlayTime*lpCurPlayer->sCharacterData.sHP.sMin) & 0xFFFF;

			lpCurPlayer->sCharacterData.sHP.sMin ^= CodeXorLife;
			ReformCharForm();

			ResetPotion();
			ResetInvenItemCode();
			ReformSkillInfo();
			SendProcessInfo();
			ResetEnergyGraph(4);
			ResetInvenMoney();
			CheckPlaySkill();
		}
		break;
	case smTRANSCODE_FAILRECORDDATA:
		lpTransCharCommand = (smTRANS_CHAR_COMMAND *)psPacket;
		lpCurPlayer->sCharacterData.dwObjectSerial = lpTransCharCommand->WParam;

		if (!lpCurPlayer->sCharacterData.iClass && !SETTINGHANDLE->Get().bDebugMode)
		{
			GAMESOCKET->iDisconnectTime = TICKCOUNT;
			break;
		}
		CheckStartCharInfo();
		rsRecorder.dwNextRecordTime = dwPlayTime + RECORD_TIME_STEP;
		dwLoadingTime = 0;
		lpCurPlayer->SendCharInfo();

		InitHelp();
		cHelpPet.CheckPetData();
		cPCBANGPet.CheckPetData();
		break;
	case smTRANSCODE_RECORDRESULT:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		rsRecorder.dwRecordTime = 0;
		rsRecorder.dwNextRecordTime = dwPlayTime + RECORD_TIME_STEP;
		dwLastRecordTime = dwPlayTime;
		if (lpTransCommand->WParam)
		{
			RecordFailCount = 0;
			if (SETTINGHANDLE->Get().bDebugMode)
				CHATGAMEHANDLE->AddChatBoxText("SaveGame Sucess");
		}
		else
		{
			RecordFailCount++;
			if (SETTINGHANDLE->Get().bDebugMode)
				CHATGAMEHANDLE->AddChatBoxText("SaveGame Failed");
		}

		cSinSiege.SetTaxRate(lpTransCommand->SParam);
		SetBlessCastleMaster(lpTransCommand->EParam, 0);
		break;
	case smTRANSCODE_BLESSCASTLE_TAX:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		cSinSiege.SetTaxRate(lpTransCommand->SParam);
		break;

	case smTRANSCODE_ADDEXP:
	case smTRANSCODE_ADDEXP_PARTY:
		// »ñµÃ¾­ÑéÐ­Òé
		lpTransCommand = (smTRANS_COMMAND *)psPacket;

		lpChar = FindAutoPlayer(lpTransCommand->LParam);

		if (lpChar && !lpChar->RecvExp)
		{
			if (lpTransCommand->SParam == ((lpTransCommand->WParam * 3 + lpTransCommand->LParam * 13) * 2002))
			{
				if (psPacket->iHeader == smTRANSCODE_ADDEXP)
					CheckChangeJob3QuestItem(lpChar->sCharacterData.iStatPoints);
			}
			else
				SendSetHackUser2(1800, lpTransCommand->WParam);
		}
		break;
		//ÉèÖÃ¾­ÑéµÈ¼¶
	case smTRANSOCDE_SET_EXPUP:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		SetExp(lpTransCommand->LParam, lpTransCommand->WParam, lpTransCommand->SParam);
		break;
	case smTRANSOCDE_SET_PLAYSIZE:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		lpCurPlayer->sCharacterData.sSize = lpTransCommand->WParam *fONE;
		break;
	case smTRANSCODE_SERVER_INFO:
		PacketServerList	*psPacketServerList;

		psPacketServerList = (PacketServerList *)psPacket;
		sinItemTime = psPacketServerList->sHeader.dwTime;
		dwTime_ServerT = sinItemTime;
		dwTime_ConnectMS = GetCurrentTime();
		dwTime_ServerGMT = psPacketServerList->sHeader.dwUnknown;

		cnt = psPacketServerList->sHeader.iClanServerIndex;
		if (cnt)
		{
			cnt = psPacketServerList->sHeader.iGameServers;
			web_DB_ip_port_init(psPacketServerList->sServers[cnt].szaIP[0], psPacketServerList->sServers[cnt].iaPort[0],
				psPacketServerList->sServers[cnt].szaIP[1], psPacketServerList->sServers[cnt].iaPort[1],
				psPacketServerList->sHeader.iTicket);
		}

		CheckProcessModule();
		HoRecvMessage(psPacket->iHeader, psPacket);
		break;
	case smTRANSCODE_ID_SETUSERINFO:
		if (SETTINGHANDLE->Get().bDebugMode)
		{
			TRANS_USERCHAR_INFO	*lpTransUserCharInfo = (TRANS_USERCHAR_INFO	*)psPacket;
			FILE	*fp;
			for (cnt = 0; cnt < lpTransUserCharInfo->PlayUserCount; cnt++) 
			{
				if (!lpTransUserCharInfo->CharInfo[cnt].szModelName2[0]) 
				{
					fopen_s(&fp,lpTransUserCharInfo->CharInfo[cnt].szModelName, "rb");
					if (!fp)
					{
						x = lstrlen(lpTransUserCharInfo->CharInfo[cnt].szModelName);
						lpTransUserCharInfo->CharInfo[cnt].szModelName[x - 1] = 'x';
						fopen_s(&fp,lpTransUserCharInfo->CharInfo[cnt].szModelName, "rb");
					}
					if (fp)
						fclose(fp);
					else
						lstrcpy(lpTransUserCharInfo->CharInfo[cnt].szModelName, "char\\monster\\hopy\\hopy.ini");
				}
			}
		}

	case smTRANSCODE_ISRECORDDATA:
	case PKTHDR_CreateCharacter:
	case smTRANSCODE_FAILCONNECT:
		HoRecvMessage(psPacket->iHeader, psPacket);
		break;
	case smTRANSCODE_SHOP_ITEMLIST:
		ComparePotion();

		sinRecvMessage(psPacket->iHeader, psPacket);

		Send_GetBlessCastleTax();
		break;
	case smTRANSCODE_SKILL_MENU:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;

		if (lpCurPlayer->iLoadedMapIndex >= 0)
		{
			if (dwQuestDelayTime > dwPlayTime)
				lpTransCommand->WParam = 0;

			if (STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == MAPID_RicartenTown)
			{
				if (GetRace(lpCurPlayer->sCharacterData.iClass) == BROOD_CODE_TEMPSKRON)
					sinSkillMaster(lpTransCommand->WParam);
			}
			if (STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == MAPID_PhillaiTown)
			{
				if (GetRace(lpCurPlayer->sCharacterData.iClass) == BROOD_CODE_MORAYION)
					sinSkillMaster(lpTransCommand->WParam);
			}

			dwQuestDelayTime = dwPlayTime + 1000 * 5;
		}
		break;
	case smTRANSCODE_VERSION:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;

		if (pcSocketData == SOCKETL)
			memcpy(&TransServerConnectInfo, lpTransCommand, sizeof(smTRANS_COMMAND));

		if (pcSocketData == SOCKETL || pcSocketData == SOCKETG)
			CheckServerInfo(lpTransCommand);
		break;
	case smTRANSCODE_WARPFIELD:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;

		if (lpTransCommand->WParam == rsSOD_FIELD &&
			lpCurPlayer->iLoadedMapIndex >= 0 && STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == rsSOD_VILLAGE)
		{
			if (!BellatraEffectInitFlag)
			{
				CreateBellatraFontEffect();
				BellatraEffectInitFlag = TRUE;
			}

			if (SoD_SetFontEffect.eBL_Type != E_BL_LODING)
			{
				SetBellatraFontEffect(E_BL_LODING, &SoD_SetFontEffect);
				sSodScore.SodNextStageNum = -2;
				sSodScore.dwSoD_NextStageTime = dwPlayTime + 3000;
				sSodScore.NextRound = 0;
				StopBGM();
			}
		}

		CloseEachPlayer();

		GAMEMAP->WarpMap((EMapID)lpTransCommand->WParam, lpTransCommand->SParam, lpTransCommand->LParam);

		lpCurPlayer->SetPosi(lpTransCommand->SParam, 0, lpTransCommand->LParam, 0, 0, 0);
		TraceCameraPosi.x = lpCurPlayer->pX;
		TraceCameraPosi.y = lpCurPlayer->pY;
		TraceCameraPosi.z = lpCurPlayer->pZ;
		TraceTargetPosi.x = lpCurPlayer->pX;
		TraceTargetPosi.y = lpCurPlayer->pY;
		TraceTargetPosi.z = lpCurPlayer->pZ;

		lpCurPlayer->iLoadedMapIndex = -1;
		if (smGameStage[0])
		{
			cnt = smGameStage[0]->GetFloorHeight(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, lpCurPlayer->Pattern->SizeHeight);
			lpCurPlayer->iLoadedMapIndex = 0;
		}
		if (cnt == CLIP_OUT && smGameStage[1])
			lpCurPlayer->iLoadedMapIndex = 1;
		break;
	case smTRANSCODE_TRADEITEMS:
		if (cTrade.OpenFlag && cTrade.TradeCharCode == ((TRANS_TRADEITEMS *)psPacket)->dwSender)
			RecvTradeItems((TRANS_TRADEITEMS *)psPacket);
		break;

	case smTRANSCODE_TRADE_ITEMKEY:
		if (GAMESOCKET->iDisconnectTime)
			break;
		if (!TradeRecvItemKeyFlag)
		{
			if (RecvTradeSucessKey((TRANS_TRADE_ITEMKEY *)psPacket, &sTradeRecv) == TRUE)
			{
				TradeRecvItemKeyFlag = TRUE;
				if (TradeItemSucessFlag)
				{
					if (sTrade.Money)
						AddInvenMoney(-(sTrade.Money - 193));
					if (sTradeRecv.Money)
						AddInvenMoney(sTradeRecv.Money - 193);

					memset(sTrade.TradeItem, 0, sizeof(ItemData)*MAX_TRADE_ITEM);
					sTrade.Money = 0;
					ReformTrade(&sTrade);

					CloseEachPlayer();
					cTrade.CheckOkTradeItem();
					ResetPotion();
					SaveGameData();
					ResetInvenItemCode();
				}
			}
			else
				cTrade.CancelTradeItem();
		}
		break;
	case smTRANSCODE_TRADE_READYITEM:
		if (GAMESOCKET->iDisconnectTime)
			break;
		if (TradeItemSucessFlag)
			break;
		if (sTrade.CheckFlag)
		{
			TradeItemSucessFlag = TRUE;
			sTradeRecv.CheckFlag = TRUE;
			if (RecvTradeCheckItem((TRANS_TRADE_CHECKITEM *)psPacket) == TRUE)
			{
				SendTradeSucessKey(((TRANS_TRADE_CHECKITEM *)psPacket)->dwSender);

				if (TradeRecvItemKeyFlag)
				{
					if (sTrade.Money)
						AddInvenMoney(-(sTrade.Money - 193));
					if (sTradeRecv.Money)
						AddInvenMoney(sTradeRecv.Money - 193);

					ZeroMemory(sTrade.TradeItem, sizeof(ItemData)*MAX_TRADE_ITEM);
					sTrade.Money = 0;
					ReformTrade(&sTrade);

					CloseEachPlayer();
					cTrade.CheckOkTradeItem();
					ResetPotion();
					SaveGameData();
					ResetInvenItemCode();
				}
			}
			break;
		}
		cTrade.CancelTradeItem();
		break;
	case smTRANSCODE_TRADE_REQUST:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		lpChar = FindAutoPlayer(lpTransCommand->SParam);

		if (lpChar &&
			lpChar->DisplayFlag &&
			lpChar->sCharacterData.szName[0] &&
			!cWareHouse.OpenFlag &&
			!cCraftItem.OpenFlag &&
			!cAging.OpenFlag &&
			!cMyShop.OpenFlag && 
			!cCaravan.OpenFlag || cMixtureReset.OpenFlag)
		{
			switch (lpTransCommand->LParam)
			{
			case 0:
				if (GetTradeDistance(lpChar) == FALSE)
					break;

				if (lpCurPlayer->sCharacterData.sWeight.sMin > lpCurPlayer->sCharacterData.sWeight.sMax)
				{
					cMessageBox.ShowMessageEvent("Overweighted       ");
					break;
				}
				if (!cTrade.OpenFlag)
				{
					sinRequestTrade(lpTransCommand->SParam, lpChar->sCharacterData.szName);
					if (DispEachMode == 0)
					{
						OpenEachPlayer(lpChar);
						DispEachMode = 0;
						//if (lpChar)
							//InterfaceParty.latest_Insert(lpChar->sCharacterData.szName);
					}
				}
				break;
			case 1:
				if (GetTradeDistance(lpChar) == FALSE)
					break;
				if (cShop.OpenFlag)
					break;

				if (lpCurPlayer->sCharacterData.sWeight.sMin > lpCurPlayer->sCharacterData.sWeight.sMax)
				{
					cMessageBox.ShowMessageEvent("Overweighted       ");
					break;
				}
				if (!cTrade.OpenFlag)
					SendRequestTrade(lpTransCommand->SParam, 2);
			case 2:
				if (!cTrade.OpenFlag)
				{
					cTrade.OpenFlag = TRUE;
					cInvenTory.OpenFlag = TRUE;
					cInterFace.CheckAllBox(SIN_TRADE);
					cTrade.TradeCharCode = lpTransCommand->SParam;
					TradeItemSucessFlag = 0;
					TradeRecvItemKeyFlag = 0;
					TradeSendSucessFlag = 0;
					TradeItemCancelCount = 0;
					TransLastRecvTrade.code = 0;
					memset(&sTrade, 0, sizeof(sTRADE));
					memset(&sTradeRecv, 0, sizeof(sTRADE));
					ReformTrade((void *)&sTrade);
					ReformTrade((void *)&sTradeRecv);
					lstrcpy(cTrade.szTradeCharName, lpChar->sCharacterData.szName);

					if (lpCurPlayer->MoveFlag)
					{
						CancelAttack();
						lpCurPlayer->MoveFlag = 0;
					}
					EachTradeButton = 0;
					OpenEachPlayer(lpChar);
					DispEachMode = TRUE;
					//if (lpChar)
						//InterfaceParty.latest_Insert(lpChar->sCharacterData.szName);
				}
				break;
			case 3:
				if (cTrade.OpenFlag)
				{
					if (TradeRecvItemKeyFlag)
					{
						memset(sTrade.TradeItem, 0, sizeof(ItemData)*MAX_TRADE_ITEM);
						sTrade.Money = 0;
						ReformTrade(&sTrade);
					}
					cTrade.CancelTradeItem();
				}
				break;
			}
		}
		break;
	case smTRANSCODE_CHANGEJOBLEVEL:
		CharacterClassData * psCharacterClassData;
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		sinChar->iRank = lpTransCommand->WParam;
		ChangeJobFace();
		psCharacterClassData = GetCharacterClassData(sinChar->iClass, sinChar->iRank);

		if (psCharacterClassData)
			lstrcpy(cInvenTory.JobName, psCharacterClassData->pszName);
		break;
	case smTRANSCODE_MAPLEVEL:
		smTRANS_MAP_LEVEL *lpTransMapLevel;
		lpTransMapLevel = (smTRANS_MAP_LEVEL *)psPacket;
		break;
	case smTRANSCODE_WAREHOUSE:
		TRANS_WAREHOUSE *lpTransWareHouse;

		lpTransWareHouse = (TRANS_WAREHOUSE *)psPacket;
		if (!cWareHouse.OpenFlag && !cTrade.OpenFlag && !cMyShop.OpenFlag && !cCaravan.OpenFlag)
		{
			if (LoadWareHouse(lpTransWareHouse, &cWareHouse.WareHouse) == TRUE)
			{
				cWareHouse.LoadWareHouseMoney(lpTransWareHouse->WareHouseMoney);
				cWareHouse.LoadWareHouseItemIamge();
				cWareHouse.BackUpInvenItem();
				ResetInvenItemCode();
				ResetInvenMoney();
			}
		}
		break;
	case smTRANSCODE_OPEN_WAREHOUSE:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;

		if (lpCurPlayer->sCharacterData.sWeight.sMin > lpCurPlayer->sCharacterData.sWeight.sMax)
		{
			cMessageBox.ShowMessageEvent("Overweighted      ");
			break;
		}
		if (!cWareHouse.OpenFlag && !cTrade.OpenFlag && !cCaravan.OpenFlag)
		{
			SENDPACKETL(lpTransCommand);
		}
		break;
	case smTRANSCODE_OPEN_MIXITEM:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;

		if (lpCurPlayer->sCharacterData.sWeight.sMin > lpCurPlayer->sCharacterData.sWeight.sMax)
		{
			cMessageBox.ShowMessageEvent("Overweighted      ");
			break;
		}
		if (lpTransCommand->WParam == 200)
		{
			cInterFace.CheckAllBox(SIN_CRAFTITEM);
			cCraftItem.ForceFlag = 1;
		}
		else
			cInterFace.CheckAllBox(SIN_CRAFTITEM);

		break;
	case smTRANSCODE_OPEN_COLLECT:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		if (lpTransCommand->WParam == 5)
			cSinSod2.ShowSod2MessageBox();
		else
			sinShowEventSmashingTV(lpTransCommand->LParam, lpTransCommand->SParam);
		break;
	case smTRANSCODE_OPEN_EVENTGIFT:
		if (sinChar->wVersion[1] == 1)
			cMessageBox.ShowMessage(MESSAGE_ALREADY_INITSTATE);
		else
			cMessageBox.ShowMessage3(MESSAGE_EVENT_GYUNGFUM, "");
		break;
	case smTRANSCODE_OPEN_AGING:
		// ´ò¿ª¶ÍÔì´°¿Ú
		if (lpCurPlayer->sCharacterData.sWeight.sMin > lpCurPlayer->sCharacterData.sWeight.sMax)
		{
			cMessageBox.ShowMessageEvent("Overweighted      ");
			break;
		}
		cInterFace.CheckAllBox(SIN_AGING);
		break;
		// ´ò¿ª´ò¿×ÏµÍ³
	case smTRANSCODE_OPEN_SOCKET:
		if (lpCurPlayer->sCharacterData.sWeight.sMin > lpCurPlayer->sCharacterData.sWeight.sMax)
		{
			cMessageBox.ShowMessageEvent("Overweighted      ");
			break;
		}
		cInterFace.CheckAllBox(SIN_SOCKET);
		break;
	case smTRANSCODE_OPEN_SMELTING:
		if (lpCurPlayer->sCharacterData.sWeight.sMin > lpCurPlayer->sCharacterData.sWeight.sMax)
		{
			cMessageBox.ShowMessageEvent("Overweighted      ");
			break;
		}
		cInterFace.CheckAllBox(SIN_SMELTING);
		break;
	case smTRANSCODE_OPEN_MANUFACTURE:
		if (lpCurPlayer->sCharacterData.sWeight.sMin > lpCurPlayer->sCharacterData.sWeight.sMax)
		{
			cMessageBox.ShowMessageEvent("Overweighted       ");
			break;
		}
		cInterFace.CheckAllBox(SIN_MANUFACTURE);
		break;
	case smTRANSCODE_OPEN_MIXTURE_RESET:
		if (lpCurPlayer->sCharacterData.sWeight.sMin > lpCurPlayer->sCharacterData.sWeight.sMax)
		{
			cMessageBox.ShowMessageEvent("Overweighted       ");
			break;
		}
		cInterFace.CheckAllBox(SIN_MIXTURE_RESET);
		break;
	case smTRANSCODE_OPEN_ELEMENT:
		// ´ò¿ªÉèÖÃÊôÐÔ
		if (lpCurPlayer->sCharacterData.sWeight.sMin > lpCurPlayer->sCharacterData.sWeight.sMax)
		{
			cMessageBox.ShowMessageEvent("Overweighted       ");
			break;
		}
		cInterFace.CheckAllBox(SIN_ELEMENT);
		break;
	case smTRANSCODE_OPEN_CARAVAN:
		// ´ò¿ª³èÎï²Ö¿â
		lpTransCommand = (smTRANS_COMMAND *)psPacket;

		if (lpCurPlayer->sCharacterData.sWeight.sMin > lpCurPlayer->sCharacterData.sWeight.sMax)
		{
			cMessageBox.ShowMessageEvent("Overweighted      ");
			break;
		}
		if (!cWareHouse.OpenFlag && !cTrade.OpenFlag && !cCaravan.OpenFlag)
		{
			SENDPACKETL(lpTransCommand);
			cCaravan.SetSelectType(lpTransCommand->WParam);
		}
		break;
		// ³èÎï²Ö¿â
	case smTRANSCODE_CARAVAN:
		if (!cWareHouse.OpenFlag && !cTrade.OpenFlag && !cMyShop.OpenFlag && !cCaravan.OpenFlag)
		{
			if (LoadCaravan((TRANS_CARAVAN *)psPacket, &cCaravan.sCaravan, 0) == TRUE)
			{
				cCaravan.LoadCaravanItemIamge();
				cCaravan.BackUpInvenItem();
				ResetInvenItemCode();
			}
		}
		break;
	case smTRANSCODE_SAVETHROWITEM2:
		ThrowItemToServer((smTRANS_COMMAND_EX *)psPacket);
		break;
	case smTRANSCODE_PLAYERKILLING:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		DeadPlayerExp(lpCurPlayer);
		break;
	case smTRANSCODE_SEND_DATASERVER:
		SENDPACKETL(((TRANS_SEND_DATASERVER *)psPacket)->szBuff);
		break;
	case smTRANSCODE_SEND_GAMESERVER:
		SENDPACKETG(((TRANS_SEND_DATASERVER *)psPacket)->szBuff);

		break;
	case smTRANSCODE_SEND_AREASERVER:
		SENDPACKETG(((TRANS_SEND_DATASERVER *)psPacket)->szBuff);
		break;
	case smTRANSCODE_SEND_AGAME_SERVER:
		for (int i = 0; i < SINUPKEEPITEM_MAX; i++)
		{
			if (chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::THIRD_EYES)
			{
				if (chaPremiumitem.UpKeepItem[i].IconTime[1] - chaPremiumitem.UpKeepItem[i].IconTime[0] <= 0)
					chaPremiumitem.m_ThirdEyesTime = 0;
			}

			else if (chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::EXPUP_POTION)
			{
				if (chaPremiumitem.UpKeepItem[i].IconTime[1] - chaPremiumitem.UpKeepItem[i].IconTime[0] <= 0)
					chaPremiumitem.m_ExpUpPotionTime = 0;
			}

			else if (chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::VAMPIRIC_CUS)
			{
				if (chaPremiumitem.UpKeepItem[i].IconTime[1] - chaPremiumitem.UpKeepItem[i].IconTime[0] <= 0)
					chaPremiumitem.m_VampiricCuspidTime = 0;
			}

			else if (chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::MANA_RECHAR_P)
			{
				if (chaPremiumitem.UpKeepItem[i].IconTime[1] - chaPremiumitem.UpKeepItem[i].IconTime[0] <= 0)
					chaPremiumitem.m_ManaRechargingPTime = 0;
			}
		}
		SENDPACKETG(((TRANS_SEND_DATASERVER *)psPacket)->szBuff);
		break;
	case smTRANSCODE_FUNCTION_MEM2:
		break;
	case smTRANSCODE_CARAVAN_HOPY:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		DWORD HopyTime;
		HopyTime = lpTransCommand->WParam - GetPlayTime_T();

		if (lpTransCommand->WParam && HopyTime > 0)
		{
			if (!chaPremiumitem.m_Caravan_HopyTime)
			{
				switch (lpTransCommand->LParam)
				{
				case 0:
				case 1:
					chaPremiumitem.m_Caravan_HopyTime = HopyTime;
					chaPremiumitem.SetUpKeepItem(nsPremiumItem::CARAVAN_HOPY, chaPremiumitem.m_Caravan_HopyTime, true, "Hopy Caravan");
					break;
				case 2:
					chaPremiumitem.m_Caravan_HopyTime = HopyTime;
					chaPremiumitem.SetUpKeepItem(nsPremiumItem::CARAVAN_ARMA, chaPremiumitem.m_Caravan_HopyTime, true, "Arma Caravan");
					break;
				case 3:
					chaPremiumitem.m_Caravan_HopyTime = HopyTime;
					chaPremiumitem.SetUpKeepItem(nsPremiumItem::CARAVAN_BUMA, chaPremiumitem.m_Caravan_HopyTime, true, "Buma Caravan");
					break;
				case 4:
					chaPremiumitem.m_Caravan_HopyTime = HopyTime;
					chaPremiumitem.SetUpKeepItem(nsPremiumItem::CARAVAN_CUEPY, chaPremiumitem.m_Caravan_HopyTime, true, "Cuepy Caravan");
					break;
				case 5:
					chaPremiumitem.m_Caravan_HopyTime = HopyTime;
					chaPremiumitem.SetUpKeepItem(nsPremiumItem::CARAVAN_HUNGKY, chaPremiumitem.m_Caravan_HopyTime, true, "Hungky Caravan");
					break;
				case 6:
					chaPremiumitem.m_Caravan_HopyTime = HopyTime;
					chaPremiumitem.SetUpKeepItem(nsPremiumItem::CARAVAN_RABIE, chaPremiumitem.m_Caravan_HopyTime, true, "Rabie Caravan");
					break;
				case 7:
					chaPremiumitem.m_Caravan_HopyTime = HopyTime;
					chaPremiumitem.SetUpKeepItem(nsPremiumItem::CARAVAN_TOBIE, chaPremiumitem.m_Caravan_HopyTime, true, "Tobie Caravan");
					break;
				case 8:
					chaPremiumitem.m_Caravan_HopyTime = HopyTime;
					chaPremiumitem.SetUpKeepItem(nsPremiumItem::CARAVAN_RUDOLF, chaPremiumitem.m_Caravan_HopyTime, true, "Rudolf Caravan");
					break;
				}
			}
		}
		else
		{
			for (int i = 0; i < SINUPKEEPITEM_MAX; i++)
			{
				switch (chaPremiumitem.UpKeepItem[i].TGAImageNumber)
				{
				case nsPremiumItem::CARAVAN_HOPY:
				case nsPremiumItem::CARAVAN_ARMA:
				case nsPremiumItem::CARAVAN_BUMA:
				case nsPremiumItem::CARAVAN_CUEPY:
				case nsPremiumItem::CARAVAN_HUNGKY:
				case nsPremiumItem::CARAVAN_RABIE:
				case nsPremiumItem::CARAVAN_TOBIE:
				case nsPremiumItem::CARAVAN_RUDOLF:
					chaPremiumitem.UpKeepItem[i].IconTime[0] = chaPremiumitem.UpKeepItem[i].IconTime[1];
					chaPremiumitem.m_Caravan_HopyTime = 0;
					break;
				}
			}
		}
		break;
	case smTRANSCODE_CRAFTITEM:
		if (((sCRAFTITEM_SERVER *)psPacket)->Result == TRUE)
		{
			cCraftItem.sinRecvCraftItemResult((sCRAFTITEM_SERVER *)psPacket);

			cInvenTory.DeleteInvenItemToServer(((sCRAFTITEM_SERVER *)psPacket)->DesCraftItem.sItem.sItemID.ToInt(), ((sCRAFTITEM_SERVER *)psPacket)->DesCraftItem.sItem.BackUpKey, ((sCRAFTITEM_SERVER *)psPacket)->DesCraftItem.sItem.BackUpChkSum);

			if (FindInvenItem(((sCRAFTITEM_SERVER *)psPacket)->DesCraftItem.sItem.sItemID.ToInt(), ((sCRAFTITEM_SERVER *)psPacket)->DesCraftItem.sItem.BackUpKey, ((sCRAFTITEM_SERVER *)psPacket)->DesCraftItem.sItem.BackUpChkSum) != 0)
			{
				SendInvenItemError(0, ((sCRAFTITEM_SERVER *)psPacket)->DesCraftItem.sItem.sItemID.ToInt(), ((sCRAFTITEM_SERVER *)psPacket)->DesCraftItem.sItem.BackUpKey, ((sCRAFTITEM_SERVER *)psPacket)->DesCraftItem.sItem.BackUpChkSum);
				break;
			}
			ResetInvenItemCode();
			SaveGameData();
			break;
		}
		cCraftItem.sinRecvCraftItemResult((sCRAFTITEM_SERVER *)psPacket);
		ResetInvenItemCode();
		SaveGameData();
		break;
	case smTRANSCODE_AGINGITEM:
		if (((sCRAFTITEM_SERVER *)psPacket)->Result)
		{
			cAging.sinRecvAgingItemResult((sCRAFTITEM_SERVER *)psPacket);

			cInvenTory.DeleteInvenItemToServer(((sCRAFTITEM_SERVER *)psPacket)->DesCraftItem.sItem.sItemID.ToInt(), ((sCRAFTITEM_SERVER *)psPacket)->DesCraftItem.sItem.BackUpKey, ((sCRAFTITEM_SERVER *)psPacket)->DesCraftItem.sItem.BackUpChkSum);

			if (FindInvenItem(((sCRAFTITEM_SERVER *)psPacket)->DesCraftItem.sItem.sItemID.ToInt(), ((sCRAFTITEM_SERVER *)psPacket)->DesCraftItem.sItem.BackUpKey, ((sCRAFTITEM_SERVER *)psPacket)->DesCraftItem.sItem.BackUpChkSum) != 0)
			{
				SendInvenItemError(0, ((sCRAFTITEM_SERVER *)psPacket)->DesCraftItem.sItem.sItemID.ToInt(), ((sCRAFTITEM_SERVER *)psPacket)->DesCraftItem.sItem.BackUpKey, ((sCRAFTITEM_SERVER *)psPacket)->DesCraftItem.sItem.BackUpChkSum);
				break;
			}

			ResetInvenItemCode();
			SaveGameData();
			break;
		}
		cAging.sinRecvAgingItemResult((sCRAFTITEM_SERVER *)psPacket);
		ResetInvenItemCode();
		SaveGameData();
		break;
	case smTRANSCODE_AGING_UPGRADE:
		sinRecvAgingIncreStateItem(&((TRANS_ITEMINFO *)psPacket)->sItem);
		TransAgingItemFlag = FALSE;
		ResetInvenItemCode();
		SaveGameData();

		SendCommandUser(smCOMMNAD_USER_AGINGUP, 0, 0, 0);

		if ((((TRANS_ITEMINFO *)psPacket)->sItem).sItemID.ToInt() == cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt() && cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.szItemName[0])
			sinSetCharItem(cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt(), cInvenTory.InvenItem[sInven[0].ItemIndex - 1].iVisibleItemType, TRUE);
		else
		{
			if ((((TRANS_ITEMINFO *)psPacket)->sItem).sItemID.ToInt() == cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sBaseItemID.ToInt() && cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sItem.szItemName[0])
				sinSetCharItem(cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sBaseItemID.ToInt(), cInvenTory.InvenItem[sInven[1].ItemIndex - 1].iVisibleItemType, TRUE);
		}
		break;
	case smTRANSCODE_MAKE_LINKCORE:
		cInvenTory.RecvLinkCore(&((TRANS_ITEMINFO *)psPacket)->sItem);
		ResetInvenItemCode();
		SaveGameData();
		break;
	case smTRANSCODE_USE_LINKCORE:
		SucessLinkCore((smTRANS_COMMAND_EX *)psPacket);
		break;
	case smTRANSCODE_WINGITEM:
		RecvWingItem((sCRAFTITEM_SERVER *)psPacket);
		ResetInvenItemCode();
		SaveGameData();
		break;
	case smTRANSCODE_ITEM_FORCEORB:
		RecvForceOrbItem((TRANS_ITEMINFO_GROUP2 *)psPacket);
		ResetInvenItemCode();
		SaveGameData();
		break;
	case smTRANSCODE_SHOPTITEM:
		if ((((TRANS_BUY_SHOPITEM *)psPacket)->sItem.sItem.sItemID.ToItemBase()) == (sinPM1&sinITEM_MASK1))
			ComparePotion();

		cShop.RecvBuyItemToServer(&((TRANS_BUY_SHOPITEM *)psPacket)->sItem, ((TRANS_BUY_SHOPITEM *)psPacket)->ItemCount);

		if ((((TRANS_BUY_SHOPITEM *)psPacket)->sItem.sItem.sItemID.ToItemBase()) == (sinPM1&sinITEM_MASK1))
			ResetPotion();
		ResetInvenItemCode();
		break;
	case smTRANSCODE_SHOP_SELLITEM:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;

		if (FindInvenItem(lpTransCommand->WParam, lpTransCommand->LParam, lpTransCommand->SParam) == 0)
		{
			CheckCharForm();
			sinPlusMoney(lpTransCommand->EParam);
			ReformCharForm();
			AddInvenMoney(lpTransCommand->EParam);
		}
		else
			SendInvenItemError(0, lpTransCommand->WParam, lpTransCommand->LParam, lpTransCommand->SParam);
		break;
	case smTRANSCODE_ELEMENTITEM:
		ELEMENT_ITEM_SERVER *lpElementServer;

		lpElementServer = (ELEMENT_ITEM_SERVER *)psPacket;
		if (((ELEMENT_ITEM_SERVER *)psPacket)->Result == TRUE)
		{
			cElement.RecvElementResult((ELEMENT_ITEM_SERVER *)psPacket);
			cInvenTory.DeleteInvenItemToServer(((ELEMENT_ITEM_SERVER *)psPacket)->DesItem.sItem.sItemID.ToInt(), ((ELEMENT_ITEM_SERVER *)psPacket)->DesItem.sItem.BackUpKey, ((ELEMENT_ITEM_SERVER *)psPacket)->DesItem.sItem.BackUpChkSum);
			if (FindInvenItem(((ELEMENT_ITEM_SERVER *)psPacket)->DesItem.sItem.sItemID.ToInt(), ((ELEMENT_ITEM_SERVER *)psPacket)->DesItem.sItem.BackUpKey, ((ELEMENT_ITEM_SERVER *)psPacket)->DesItem.sItem.BackUpChkSum) != 0)
			{
				SendInvenItemError(0, ((ELEMENT_ITEM_SERVER *)psPacket)->DesItem.sItem.sItemID.ToInt(), ((ELEMENT_ITEM_SERVER *)psPacket)->DesItem.sItem.BackUpKey, ((ELEMENT_ITEM_SERVER *)psPacket)->DesItem.sItem.BackUpChkSum);
				break;
			}
			ResetInvenItemCode();
			SaveGameData();
			break;
		}
		cElement.RecvElementResult((ELEMENT_ITEM_SERVER *)psPacket);
		ResetInvenItemCode();
		SaveGameData();
		break;
	case smTRANSCODE_SOCKETITEM:

		SOCKET_ITEM_SERVER *lpSocketServer;

		lpSocketServer = (SOCKET_ITEM_SERVER *)psPacket;

		if (((SOCKET_ITEM_SERVER *)psPacket)->Result == TRUE)
		{
			cSocket.RecvSocketResult((SOCKET_ITEM_SERVER *)psPacket);
			cInvenTory.DeleteInvenItemToServer(((SOCKET_ITEM_SERVER *)psPacket)->DesItem.sItem.sItemID.ToInt(), ((SOCKET_ITEM_SERVER *)psPacket)->DesItem.sItem.BackUpKey, ((SOCKET_ITEM_SERVER *)psPacket)->DesItem.sItem.BackUpChkSum);
			if (FindInvenItem(((SOCKET_ITEM_SERVER *)psPacket)->DesItem.sItem.sItemID.ToInt(), ((SOCKET_ITEM_SERVER *)psPacket)->DesItem.sItem.BackUpKey, ((SOCKET_ITEM_SERVER *)psPacket)->DesItem.sItem.BackUpChkSum) != 0)
			{
				SendInvenItemError(0, ((ELEMENT_ITEM_SERVER *)psPacket)->DesItem.sItem.sItemID.ToInt(), ((SOCKET_ITEM_SERVER *)psPacket)->DesItem.sItem.BackUpKey, ((SOCKET_ITEM_SERVER *)psPacket)->DesItem.sItem.BackUpChkSum);
				break;
			}
			ResetInvenItemCode();
			SaveGameData();
			break;
		}

		cSocket.RecvSocketResult((SOCKET_ITEM_SERVER *)psPacket);
		ResetInvenItemCode();
		SaveGameData();
		break;
	case smTRANSCODE_CHECKITEM:
	case smTRANSCODE_ERRORITEM:
	case smTRANSCODE_CLEARPOTION:
		RecvCheckItemFromServer((TRANS_ITEM_CODE *)psPacket);
		break;
	case smTRANSCODE_GETCLIENT_FUNCPOS:
		SendClientFuncPos();
		break;
	case smTRANSCODE_FUNCTION_MEM:
		break;
	case smTRANSCODE_PARTY_POTION:
		SetPartyPosion((smTRANS_COMMAND *)psPacket);
		break;
	case smTRANSCODE_HEALING:
	case smTRANSCODE_GRAND_HEALING:
		SetPartyPosion((smTRANS_COMMAND *)psPacket);
		break;
	case smTRANSCODE_SAVECLIENT:
		SaveGameData();
		break;
	case smTRANSCODE_COMMAND_USER:
		RecvCommandUser((smTRANS_COMMAND_EX *)psPacket);
		break;
	case smTRANSCODE_VAMPRIC_CUSPID:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		if (chaPremiumitem.m_VampiricCuspidTime == NULL)
		{
			chaPremiumitem.m_VampiricCuspidTime = lpTransCommand->WParam;
			chaPremiumitem.SetUpKeepItem(nsPremiumItem::VAMPIRIC_CUS, chaPremiumitem.m_VampiricCuspidTime, true, "Vampiric");
			cInvenTory.SetItemToChar();
		}
		break;
	case smTRANSCODE_MANA_RECHARGING:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		if (chaPremiumitem.m_ManaRechargingPTime == NULL)
		{
			chaPremiumitem.m_ManaRechargingPTime = lpTransCommand->WParam;
			chaPremiumitem.SetUpKeepItem(nsPremiumItem::MANA_RECHAR_P, chaPremiumitem.m_ManaRechargingPTime, true, "Mana_Rechar");
			cInvenTory.SetItemToChar();
		}
		break;
	case smTRANSCODE_NPROTECT:
		break;
	case smTRANSCODE_GAMEGUARD_AUTH:
		break;
	case smTRANSCODE_OPEN_CLANMENU:
		void CLANmenu_meetNPC();
		CLANmenu_meetNPC();
		break;
	case smTRANSCODE_COMIC_SKIN:
		DWORD BigHeadTime;
		lpTransCommand = (smTRANS_COMMAND *)psPacket;

		BigHeadTime = lpTransCommand->LParam - GetPlayTime_T();

		if (lpTransCommand->LParam && BigHeadTime > 0)
		{
			if (chaPremiumitem.m_BigHeadTime == NULL)
			{
				ChangeBigHeadMode(lpTransCommand->WParam);
				StartSkill(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, SKILL_UP1);
				SkillPlaySound(SKILL_SOUND_LEARN, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
				SetBigHeadToImage(lpTransCommand->WParam, BigHeadTime);

				cInvenTory.SetItemToChar();
			}
		}
		else
			CancelBigHeadToFunction();
		break;
	case smTRANSCODE_CLAN_SERVICE:
		RecvClanJoinService((smTRANS_CHAR_COMMAND2 *)psPacket);
		break;
	case smTRANSCODE_VIRTURAL_POTION:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;

		if (!lpTransVirtualPotion)
		{
			lpTransVirtualPotion = new smTRANS_COMMAND;
			if (lpTransVirtualPotion)
				memcpy(lpTransVirtualPotion, lpTransCommand, sizeof(smTRANS_COMMAND));
		}
		break;
	case smTRANSCODE_PROCESS_SKILL:
	case smTRANSCODE_PROCESS_SKILL2:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		RecvProcessSkill(lpTransCommand);
		break;

	case smTRANSCODE_PROCESS_CLAN_SKILL:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		chaSiege.SetClanSkill(lpTransCommand->WParam);

		SENDPACKETG(lpTransCommand);
		break;
		//ÕÙ»½¼¼ÄÜ
	case smTRANSCODE_CANCEL_SKILL:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;

		if (lpCurPlayer->sCharacterData.iClass == CHARACTERCLASS_Mechanician && lpTransCommand->WParam == SKILL_PLAY_METAL_GOLEM)
			cSkill.CancelContinueSkill(SKILL_METAL_GOLEM);
		else if (lpCurPlayer->sCharacterData.iClass == CHARACTERCLASS_Archer && lpTransCommand->WParam == SKILL_PLAY_RECALL_WOLVERIN)
			cSkill.CancelContinueSkill(SKILL_RECALL_WOLVERIN);
		else if (lpCurPlayer->sCharacterData.iClass == CHARACTERCLASS_Atalanta && lpTransCommand->WParam == SKILL_PLAY_S_ARCUDA)
			cSkill.CancelContinueSkill(SKILL_S_ARCUDA);
		else if (lpCurPlayer->sCharacterData.iClass == CHARACTERCLASS_Magician && lpTransCommand->WParam == SKILL_PLAY_FIRE_ELEMENTAL)
			cSkill.CancelContinueSkill(SKILL_FIRE_ELEMENTAL);
		else if (lpCurPlayer->sCharacterData.iClass == CHARACTERCLASS_Shaman && lpTransCommand->WParam == SKILL_PLAY_CRIMSON_KNIGHT)
			cSkill.CancelContinueSkill(SKILL_RECALL_BLOODYKNIGHT);
		else if (lpTransCommand->WParam == SKILL_CRYSTAL_ORB && lpTransCommand->LParam)
			cSkill.CancelContinueSkill(SKILL_CRYSTAL_ORB, lpTransCommand->LParam);
		break;
	case smTRANSCODE_PARTY_SKILL:
		RecvPartySkillFromServer((TRANS_PARTY_SKILL *)psPacket);
		break;
	case smTRANSCODE_CLAN_UPDATE:
		Updatecldata();
		break;
	case smTRANSCODE_QUEST_MESSAGE:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;

		if (lpTransCommand->WParam == SIN_QUEST_CODE_CHANGEJOB4)
		{
			CancelAttack();

			lpChar = FindAutoPlayer(lpTransCommand->LParam);
			if (lpChar)
			{
				OpenEachPlayer(lpChar);
				DispEachMode = TRUE;
			}

			sinBattleNpcResult(1);
		}
		else if (lpTransCommand->WParam == HAQUEST_CODE_FURYOFPHANTOM)
			chaQuest.RecvBattleNpcResult(1);
		else
			sinMorayionNpcChangeJob_Two();
		break;
	case smTRANSCODE_ATTACK_RESULT:
		if (lpCurPlayer->AttackCritcal >= 0)
			lpCurPlayer->AttackCritcal = ((smTRANS_COMMAND *)psPacket)->WParam;
		break;
	case smTRANSCODE_DISP_DAMAGE:
		LastAttackDamage = ((smTRANS_COMMAND *)psPacket)->WParam;
		break;
	case smTRANSCODE_DAMAGE_ENCODE_MEM:
		RecvDamagePacketModule((TRANS_FUNC_MEMORY *)psPacket);
		break;
	case smTRANSCODE_DAMAGE_ENCODE_MEM2:
		RecvDamagePacketModule2((TRANS_FUNC_MEMORY *)psPacket);
		break;
	case smTRANSCODE_PACKET_DYNFUNC:
		RecvDynPacketModule((TRANS_FUNC_MEMORY *)psPacket);
		break;
	case smTRANSCODE_GETPLAYERINFO:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		if (lpTransCommand->LParam != lpCurPlayer->sCharacterData.bUpdateInfo[0])
			SendSetObjectSerial(lpCurPlayer->iID);
		break;
	case smTRANSCODE_ITEM_EXPRESS:

		lpTransPostItem = (TRANS_POST_ITEM *)psPacket;

		if (lpTransPostItem->dwItemFlag)
		{
			ComparePotion();
			cInvenTory.SetInvenToItemInfo((Item *)(psPacket + sizeof(TRANS_POST_ITEM)));
			ResetInvenItemCode();

			if ((((Item *)(psPacket + sizeof(TRANS_POST_ITEM)))->sItemID.ToItemBase()) == (sinPM1&sinITEM_MASK1))
				ResetPotion2();
			SaveGameData();
		}
		if (lpCurPlayer->sCharacterData.sWeight.sMin > lpCurPlayer->sCharacterData.sWeight.sMax)
		{
			cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
			break;
		}
		if (lpTransPostItem->dwItemCode)
		{
			if (sinChar->sWeight.sMin + lpTransPostItem->Weight > sinChar->sWeight.sMax)
			{
				cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
				break;
			}
			memset(&sMessageBox_RecvItem.RecvItem, 0, sizeof(ItemData));
			sMessageBox_RecvItem.RecvItem.sBaseItemID = lpTransPostItem->dwItemCode;
			sMessageBox_RecvItem.Flag = 1;
			sMessageBox_RecvItem.szItem[0] = 0;
			cInvenTory.OpenFlag = 1;
			sMessageBox_RecvItem.Param[0] = lpTransPostItem->dwParam[0];

			if (sMessageBox_RecvItem.RecvItem.sBaseItemID.ToInt() == (sinGG1 | sin01))
			{
				cInvenTory.LoadMoneyExpImage(&sMessageBox_RecvItem.RecvItem);
				sMessageBox_RecvItem.RecvItem.iSalePrice = lpTransPostItem->dwItemJobCode;
				lstrcpy(sMessageBox_RecvItem.szDoc, lpTransPostItem->szDoc);
				break;
			}
			if (sMessageBox_RecvItem.RecvItem.sBaseItemID.ToInt() == (sinGG1 | sin02))
			{
				cInvenTory.LoadMoneyExpImage(&sMessageBox_RecvItem.RecvItem);
				sMessageBox_RecvItem.RecvItem.iOldX = lpTransPostItem->dwItemJobCode;
				lstrcpy(sMessageBox_RecvItem.szDoc, lpTransPostItem->szDoc);
				break;
			}
			if ((sMessageBox_RecvItem.RecvItem.sBaseItemID.ToInt() & sinITEM_MASK1) == 0x04000000)
			{
				sMessageBox_RecvItem.RecvItem.iPotionCount = lpTransPostItem->dwItemJobCode;
				cInvenTory.CheckInvenEmpty(&sMessageBox_RecvItem.RecvItem);
				lstrcpy(sMessageBox_RecvItem.szItem, lpTransPostItem->szItemName);
				lstrcpy(sMessageBox_RecvItem.szDoc, lpTransPostItem->szDoc);
				break;
			}
			cInvenTory.CheckInvenEmpty(&sMessageBox_RecvItem.RecvItem);
			lstrcpy(sMessageBox_RecvItem.szItem, lpTransPostItem->szItemName);
			lstrcpy(sMessageBox_RecvItem.szDoc, lpTransPostItem->szDoc);
		}
		break;
	case smTRANSCODE_SOD_RESULT:
		cSinHelp.ShowSodRanking((TRANS_SOD_RESULT *)psPacket, 1);
		break;
	case smTRANSCODE_SOD_RESULT2:
		cSinHelp.ShowSodRanking((TRANS_SOD_RESULT *)psPacket, 0);
		break;
	case smTRANSCODE_SOD_INFOMATION:
		RecvSodGameInfomation(psPacket);
		break;
	case smTRANSCODE_WING_NPC:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;

		if (lpTransCommand->LParam)
		{
			switch (lpTransCommand->LParam)
			{
			case 1:
				sinShowTeleportMap();
				break;
			case 2:
				haShowCastleTeleportMap();
				break;
			case 3:
				TeleportDungeon();
				break;
			}
		}
		switch (lpTransCommand->WParam)
		{
		case 0:
		case 1:
			cInvenTory.sinWingQuestNpc();
			break;
		case 2:
			cInvenTory.SendPuzzleNpc();
			break;
		case 3:
			cInvenTory.CheckEventItem();
			break;
		case 4:
			cInvenTory.CheckFoxEventItem();
			break;
		case 5:
			cInvenTory.CheckCristalEventItem();
			break;
		case 8:
			cInvenTory.CheckWatermelonEventItem();
			break;
		case 9:
			cInvenTory.CheckValentineEventItem();
			break;
		case 10:
			cInvenTory.CheckPristonAlphabetEventItem();
			break;
		case 11:
			cInvenTory.CheckCandydaysEventItem();
			break;
		case 12:
			cInvenTory.CheckMagicalGreenEventItem();
			break;
		case 13:
			cInvenTory.CheckTearOfKaraEventItem();
			break;
		case 14:
			cInvenTory.CheckFindinvestigatorEventItem();
			break;
		case 15:
			cInvenTory.CheckFindinvestigatorKamiuEventItem();
			break;
		case 16:
			cInvenTory.CheckFindinvestigatorEtoEventItem();
			break;
		}
		break;
	case smTRANSCODE_OPEN_STARPOINT:
		StarShopNPC();
		break;
	case smTRANSCODE_STARPOINT:
		sinStarPoint(((smTRANS_COMMAND *)psPacket)->WParam);
		break;
	case smTRANSCODE_CLANMONEY:
		sinRecvClanMoney(((smTRANS_COMMAND *)psPacket)->WParam, ((smTRANS_COMMAND *)psPacket)->LParam);
		break;
	case smTRANSCODE_OPEN_GIVEMONEY:
		cMessageBox.ShowMessage2(MESSAGE_GIVE_MONEY);
		break;
	case smTRANSCODE_CHANGE_EVENT:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		if (sBiInfo)
		{
			sBiInfo->EventPlay[0] = lpTransCommand->WParam & 0xFFFF;
			sBiInfo->EventPlay[1] = (lpTransCommand->WParam >> 16) & 0xFFFF;
			sBiInfo->PCRNo = lpTransCommand->LParam;
			cInvenTory.SetItemToChar();
		}

		if (lpTransCommand->EParam)
			GoNotice_chking = 1;
		break;
	case smTRANSCODE_CALL_MYSHOP:
		if (lpCurPlayer->dwTradeMsgCode)
			Send_MyShopItemList((smTRANS_COMMAND *)psPacket);
		break;
	case smTRANSCODE_MYSHOP_ITEM:
		Recv_MyShopItemList((TRANS_TRADEITEMS *)psPacket);
		break;
	case smTRANSCODE_MYSHOP_MESSAGE:
		lpTransChatMessage = (TRANS_CHATMESSAGE *)psPacket;

		lpChar = FindAutoPlayer(lpTransChatMessage->dwObjectSerial);
		if (lpChar && lpChar->dwTradeMsgCode)
			wsprintf(lpChar->szTradeMessage, "%s: %s", lpChar->sCharacterData.szName, lpTransChatMessage->szMessage);
		break;
	case smTRANSCODE_MYSHOP_TRADE:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;

		cMyShop.RecvMyShopItem(lpTransCommand->SParam,
			(sMYSHOP_ITEM_SERVER *)(((smTRANS_COMMAND_BUFF *)psPacket)->Buff));
		break;
	case smTRANSCODE_SUCCESS_EVATION:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		AddTimeEffect(smTRANSCODE_SUCCESS_EVATION, dwPlayTime + 500, lpTransCommand->WParam, lpTransCommand->LParam, lpTransCommand->SParam);
		break;
	case smTRANSCODE_BLESSCASTLE_INFO:
		RecvBlessCastInfo(psPacket);
		break;
	case smTRANSCODE_MEDIA_NPC:
		lpTransChatMessage = (TRANS_CHATMESSAGE *)psPacket;
		chaSiege.ShowCastlePlayMovie(lpTransChatMessage->szMessage, lpTransChatMessage->szMessage + lstrlen(lpTransChatMessage->szMessage) + 1, 0);
		break;
	case smTRANSCODE_PUBLIC_POLLING:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		cSinHelp.ShowResearchMenu(lpTransCommand->WParam, lpTransCommand->LParam);
		break;

	case smTRANSCODE_NOTICE_BOX:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		cHelp_Menu.haGuidHelpLevel_1(lpTransCommand->WParam);
		break;

	case smTRANSCODE_PCBANG_PET:
		break;
	case smTRANSCODE_PHENIX_PET:
		DWORD PhenixTime;
		lpTransCommand = (smTRANS_COMMAND *)psPacket;

		PhenixTime = lpTransCommand->WParam - GetPlayTime_T();

		if (lpTransCommand->WParam && PhenixTime > 0)
		{
			if (chaPremiumitem.m_PhenixPetTime == NULL)
			{
				chaPremiumitem.m_PhenixPetTime = PhenixTime;

				switch (lpTransCommand->LParam)
				{
				case 1:
					chaPremiumitem.SetUpKeepItem(nsPremiumItem::PHONEIX_FIRE, chaPremiumitem.m_PhenixPetTime, true, "Phoenix Pet");
					break;
				case 2:
					chaPremiumitem.SetUpKeepItem(nsPremiumItem::PHONEIX_ICE, chaPremiumitem.m_PhenixPetTime, true, "Phoenix Pet");
					break;
				case 3:
					chaPremiumitem.SetUpKeepItem(nsPremiumItem::PHONEIX_LIGHTNING, chaPremiumitem.m_PhenixPetTime, true, "Phoenix Pet");
					break;
				case 4:
					chaPremiumitem.SetUpKeepItem(nsPremiumItem::PHONEIX_HEAL, chaPremiumitem.m_PhenixPetTime, true, "Phoenix Pet");
					break;
				}
				cPCBANGPet.PetShow = TRUE;
				cPCBANGPet.PetKind = lpTransCommand->LParam;
				cPCBANGPet.ShowPet();
			}
		}
		else
		{
			for (int i = 0; i < SINUPKEEPITEM_MAX; i++)
			{
				if (chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::PHONEIX_FIRE || chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::PHONEIX_ICE || chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::PHONEIX_LIGHTNING || chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::PHONEIX_HEAL)
				{
					chaPremiumitem.UpKeepItem[i].IconTime[0] = chaPremiumitem.UpKeepItem[i].IconTime[1];
					chaPremiumitem.m_PhenixPetTime = 0;
					cPCBANGPet.ClosePet();
					break;
				}
			}
		}
		break;
	case smTRANSCODE_HELP_PET:
		break;
		//¹ûÊµ
	case smTRANSCODE_FRUIT:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		sinFruitStatus[0] = WORD(lpTransCommand->WParam);
		StartSkill(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, SKILL_UP1);
		SkillPlaySound(SKILL_SOUND_LEARN, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
		CheckCharForm();
		switch (lpTransCommand->LParam)
		{
		case 1:
			sinTempStatus[0] ++;
			sinChar->iStrength++;
			break;
		case 2:
			sinTempStatus[1] ++;
			sinChar->iSpirit++;
			break;
		case 3:
			sinTempStatus[2] ++;
			sinChar->iTalent++;
			break;
		case 4:
			sinTempStatus[3] ++;
			sinChar->iAgility++;
			break;
		case 5:
			sinTempStatus[4] ++;
			sinChar->iHealth++;
			break;
		}
		ReformCharStatePoint(sinChar, sinQuest_levelLog, sinFruitStatus[0]);
		ReformCharForm();
		cInvenTory.SetItemToChar();
		SaveGameData();
		break;
		//Á¦Á¿Ê¯Í·
	case smTRANSCODE_FORCE_ROE:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		SetForceOrbFunction(lpTransCommand->WParam, lpTransCommand->LParam);
		break;
	case smTRANSCODE_SMELTINGITEM:
		SmeltingItem.sinRecvSmeltingItemResult((sSMELTINGITEM_SERVER *)psPacket);
		ResetInvenItemCode();
		SaveGameData();
		break;
	case smTRANSCODE_MANUFACTURE:
		ManufactureItem.RecvManufactureItemResult((SManufactureItem_Server *)psPacket);
		ResetInvenItemCode();
		SaveGameData();
		break;
	case smTRANSCODE_MIXTURE_RESET_ITEM:
		cMixtureReset.sinRecvMixtureItemResetResult((sMIXTURE_RESET_ITEM_SERVER *)psPacket);
		ResetInvenItemCode();
		SaveGameData();
		break;
		// ½ÓÊÜ¹ÖÎïË®¾§Ìí¼ÓÐÅÏ¢
	case smTRANSCODE_CRYSTAL_ORB:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;

		int UseFlag;
		int ObjSerial;
		int ItemCode;
		int Time;

		sSKILL TempSkill;

		ItemCode = lpTransCommand->WParam;
		ObjSerial = lpTransCommand->LParam;
		Time = lpTransCommand->SParam;

		ZeroMemory(&TempSkill, sizeof(sSKILL));

		UseFlag = (lpTransCommand->WParam & sinITEM_MASK3) >> 8;

		if (UseFlag > 0 && UseFlag <= MAX_CRYSTAL)
		{
			char *Path = "image\\Sinimage\\skill\\CrystalOrb\\GP_0%d.tga";
			char szBuff[128];

			if (MatCrystalOrb[UseFlag - 1] == NULL)
			{
				wsprintf(szBuff, Path, UseFlag);
				MatCrystalOrb[UseFlag - 1] = CreateTextureMaterial(szBuff, 0, 0, 0, SMMAT_BLEND_ALPHA);
				// ¶ÁÈ¡ÎÆÀí
				ReadTextures();
			}
			TempSkill.CODE = SKILL_CRYSTAL_ORB;
			TempSkill.Point = UseFlag;
			TempSkill.UseTime = Time;
			TempSkill.MatIcon = MatCrystalOrb[UseFlag - 1];
			TempSkill.dwObjectSerial = ObjSerial;
			TempSkill.SkillCodeIndex = TRUE;

			sinContinueSkillSet(&TempSkill);
		}

		break;
	case smTRANSCODE_MANUFACTURE_WEIGHT_PRICE:
		ManufactureItemResultInfo((SManufacture_ResultItemInfo_Server *)psPacket);
		break;
	case smTRANSCODE_SEND_AGAME_PRIMEITEM_DATA2:
		for (int i = 0; i < SINUPKEEPITEM_MAX; i++)
		{
			if (chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::MIGHT_OF_AWELL)
			{
				if (chaPremiumitem.UpKeepItem[i].IconTime[1] - chaPremiumitem.UpKeepItem[i].IconTime[0] <= 0)
				{
					chaPremiumitem.m_MightofAwellTime = 0;
					chaPremiumitem.m_MightofAwellWeight = 0;
				}
			}

			if (chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::MANA_REDUCE_P)
			{
				if (chaPremiumitem.UpKeepItem[i].IconTime[1] - chaPremiumitem.UpKeepItem[i].IconTime[0] <= 0)
				{
					chaPremiumitem.m_ManaReducePotiontime = 0;
					chaPremiumitem.m_ManaReducePotionValue = 0;
				}
			}
			else if (chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::MIGHT_OF_AWELL)
			{
				if (chaPremiumitem.UpKeepItem[i].IconTime[1] - chaPremiumitem.UpKeepItem[i].IconTime[0] <= 0)
				{
					chaPremiumitem.m_MightofAwellTime = 0;
					chaPremiumitem.m_MightofAwellWeight = 0;
				}
			}
		}

		SENDPACKETG(((TRANS_SEND_DATASERVER *)psPacket)->szBuff);
		break;
	case smTRANSCODE_SEND_AGAME_PRIMEITEM_DATA3:
		for (int i = 0; i < SINUPKEEPITEM_MAX; i++)
		{
			switch (chaPremiumitem.UpKeepItem[i].TGAImageNumber)
			{
			case nsPremiumItem::HELP_PET_TERRY:
				if (chaPremiumitem.UpKeepItem[i].IconTime[1] - chaPremiumitem.UpKeepItem[i].IconTime[0] <= 0)
				{
					chaPremiumitem.m_TerryTime = 0;

					chaPremiumitem.m_HelpPetTime = 0;
					sinChar->GravityScroolCheck[1] = 0;
					cHelpPet.ClosePet();
				}
				break;
			case nsPremiumItem::HELP_PET_NEPSYS:
				if (chaPremiumitem.UpKeepItem[i].IconTime[1] - chaPremiumitem.UpKeepItem[i].IconTime[0] <= 0)
				{
					chaPremiumitem.m_HelpPetTime = 0;
					cHelpPet.ClosePet();
				}
				break;
			case nsPremiumItem::HELP_PET_IO:
				if (chaPremiumitem.UpKeepItem[i].IconTime[1] - chaPremiumitem.UpKeepItem[i].IconTime[0] <= 0)
				{
					chaPremiumitem.m_HelpPetTime = 0;
					cHelpPet.ClosePet();
				}
				break;
			case nsPremiumItem::HELP_PET_MUTE:
				if (chaPremiumitem.UpKeepItem[i].IconTime[1] - chaPremiumitem.UpKeepItem[i].IconTime[0] <= 0)
				{
					chaPremiumitem.m_HelpPetTime = 0;
					sinChar->GravityScroolCheck[1] = 0;
					cHelpPet.ClosePet();
				}
				break;
			case nsPremiumItem::STAMINA_REDUCE_P:
				if (chaPremiumitem.UpKeepItem[i].IconTime[1] - chaPremiumitem.UpKeepItem[i].IconTime[0] <= 0)
				{
					chaPremiumitem.m_StaminaReducePotiontime = 0;
					chaPremiumitem.m_StaminaReducePotionValue = 0;
				}
				break;
			}
		}

		SENDPACKETG(((TRANS_SEND_DATASERVER *)psPacket)->szBuff);
		break;
	case smTRANSCODE_SEND_AGAME_PRIMEITEM_DATA4:
		SENDPACKETG(((TRANS_SEND_DATASERVER *)psPacket)->szBuff);
		break;
	case smTRANSCODE_COUPLERING:
		cInvenTory.DeleteCoupleRing();
		break;
	case smTRANSCODE_PREMIUMITEM_INIT:
		lpTransCommand = (smTRANS_COMMAND *)psPacket;
		for (int i = 0; i < SINUPKEEPITEM_MAX; i++)
		{
			if (chaPremiumitem.UpKeepItem[i].TGAImageNumber == lpTransCommand->WParam)
			{
				chaPremiumitem.UpKeepItem[i].IconTime[1] = chaPremiumitem.UpKeepItem[i].IconTime[0];
				switch (lpTransCommand->WParam)
				{
				case 6:
					chaPremiumitem.m_ManaReducePotiontime = 0;
					break;
				case 7:
					chaPremiumitem.m_StaminaReducePotiontime = 0;
					break;
				case 8:
				case 9:
				case 10:
				case 11:
					cHelpPet.ClosePet();
					break;
				case 12:
					cPCBANGPet.ClosePet();
					break;
				}
			}
		}
		break;
	}

	return TRUE;
}
int rsTRANS_SERVER::Init()
{
	InitializeCriticalSection(&cServSection);

	return TRUE;
}
extern int szSpaceSorting(char *lpString);

rsTRANS_SERVER	rsMainServer;

#define SAVE_CHAT_COMMAND_MAX		16
#define SAVE_CHAT_COMMAND_MASK		15

char szSaveChatCommands[SAVE_CHAT_COMMAND_MAX][256];
int ChatCommandSaveCnt = 0;
int ChatSaveRecallCnt = 0;

int SaveChatCommand(char *szMessage)
{
	int len, cnt;
	int mcnt;
	char szBuff[256];

	len = lstrlen(szMessage);
	lstrcpy(szBuff, szMessage);

	for (cnt = 0; cnt < len; cnt++)
	{
		if (szBuff[cnt] == ' ')
		{
			szBuff[cnt] = 0;
			break;
		}
	}
	lstrcat(szBuff, " ");

	for (cnt = 0; cnt < ChatCommandSaveCnt; cnt++)
	{
		if (cnt >= SAVE_CHAT_COMMAND_MAX)
			break;
		if (lstrcmp(szSaveChatCommands[cnt], szBuff) == 0)
			return TRUE;
	}

	mcnt = ChatCommandSaveCnt & SAVE_CHAT_COMMAND_MASK;
	lstrcpy(szSaveChatCommands[mcnt], szBuff);

	ChatCommandSaveCnt++;
	ChatSaveRecallCnt = ChatCommandSaveCnt;

	return TRUE;
}
int RecallSavedChatCommand(HWND hChatWnd, int Arrow)
{
	int mcnt;
	int len;

	if (ChatCommandSaveCnt <= 0)
		return FALSE;

	if (Arrow)
	{
		ChatSaveRecallCnt--;
		if (ChatSaveRecallCnt < 0)
			ChatSaveRecallCnt = ChatCommandSaveCnt - 1;
	}
	else
	{
		ChatSaveRecallCnt++;
		if (ChatSaveRecallCnt >= ChatCommandSaveCnt)
		{
			ChatSaveRecallCnt = ChatCommandSaveCnt - 1;
			SetWindowText(hChatWnd, "");
			return TRUE;
		}
	}

	mcnt = ChatSaveRecallCnt & SAVE_CHAT_COMMAND_MASK;
	SetWindowText(hChatWnd, szSaveChatCommands[mcnt]);

	len = lstrlen(szSaveChatCommands[mcnt]);
	SendMessage(hChatWnd, EM_SETSEL, len, len);

	return TRUE;
}
int rsCompString(char *src1, char *src2)
{
	int cnt;
	int len1, len2;
	int len;

	len1 = lstrlen(src1);
	len2 = lstrlen(src2);

	if (len1 < len2)
		len = len1;
	else
		len = len2;

	if (!len)
		return NULL;

	for (cnt = 0; cnt < len1; cnt++)
	{
		if (src1[cnt] == 0)
			break;
		if (src1[cnt] != src2[cnt])
			return NULL;
	}

	return cnt;
}
char szLastChatMessage[256];
DWORD	dwLastChatTime[4] = { 0 };
DWORD	dwContiueChatCount = 0;
#include "CurseFilter.h"

char *rsGetWord(char *q, char *p);

extern int WaveCameraMode;

int SetWarningTime(int Time)
{
	int Result = FALSE;
	int Temp = FALSE;
	for (int i = 0; i < SIN_MAX_SKILL_LIST; i++)
	{
		if (ContinueSkill[i].Flag && ContinueSkill[i].CODE == SKILL_WARNING_TIME)
		{
			Temp = TRUE;
			break;
		}
	}
	if (Temp == FALSE)
	{
		char *Path = "image\\Sinimage\\skill\\keep\\warningtime.tga";
		sSKILL TempSkill;

		ZeroMemory(&TempSkill, sizeof(sSKILL));

		if (!MatWarning)
		{
			MatWarning = CreateTextureMaterial(Path, 0, 0, 0, SMMAT_BLEND_ALPHA);
			ReadTextures();
		}

		TempSkill.CODE = SKILL_WARNING_TIME;
		TempSkill.Point = TRUE;
		TempSkill.UseTime = Time;
		TempSkill.MatIcon = MatWarning;
		TempSkill.SkillCodeIndex = TRUE;

		sinContinueSkillSet(&TempSkill);

		Result = TRUE;
	}
	return Result;
}

int GetNextLineCount(char *szString, int LineMax)
{
	int cnt;
	int len;
	char *lp;

	len = lstrlen(szString);
	if (len <= LineMax)
		return 0;

	lp = szString;

	cnt = 0;

	while (1)
	{
		if (CheckCode_2Byte(lp) == 2)
		{
			cnt += 2;
			lp += 2;
		}
		else
		{
			cnt++;
			lp++;
		}

		if (cnt > (LineMax - 2)) break;
	}
	return cnt;
}

int Ts_LastSendCounter;
DWORD	dwLastSendPosiTime = 0;
DWORD	dwLastSendPlayTime = 0;

int DisconnectFarPlayer()
{
	int mx, mz, dDist;
	int cnt;
	int timeover;

	for (cnt = 0; cnt < MAX_UNITS; cnt++)
	{
		if (chrOtherPlayer[cnt].bActive)
		{
			if ((chrOtherPlayer[cnt].dwLastTransTime + DIS_TIME_OVER) < dwPlayTime)
				timeover = TRUE;
			else
				timeover = FALSE;

			mx = (lpCurPlayer->pX - chrOtherPlayer[cnt].pX) >> FLOATNS;
			mz = (lpCurPlayer->pZ - chrOtherPlayer[cnt].pZ) >> FLOATNS;
			dDist = mx * mx + mz * mz;

			if ((chrOtherPlayer[cnt].DisplayFlag && dDist > DIST_TRANSLEVEL_DISCONNECT) || timeover)
			{
				chrOtherPlayer[cnt].bActive = 0;

				EnterCriticalSection(&cSection);
				chrOtherPlayer[cnt].Close();
				LeaveCriticalSection(&cSection);
			}
		}
	}

	return TRUE;
}

DWORD	dwExtendServ_RecvTime = 0;
DWORD	dwUserServ_RecvTime = 0;
DWORD	dwMainServ_RecvTime = 0;
DWORD	dwDataServ_RecvTime = 0;


int RecvPlayData(SocketData * pcSocketData, Packet * psPacket)
{
	EnterCriticalSection(&cSection);

	rsMainServer.RecvMessage(pcSocketData, psPacket);

	LeaveCriticalSection(&cSection);

	return TRUE;
}


int LastSendCnt;

#define	NET_SENDING_WAIT_TIME		400
#define	NET_SENDING_WAIT_TIME2		1000

int NetStandCnt = 0;

DWORD	NetScoopTime = 3000;

int ThrowPutItem(ItemData *lpItem, int x, int y, int z)
{
	if ((dwRecvServerTime + 4000) < dwPlayTime || QuitSave || TransThrowItem.code)
		return FALSE;

	if (WarningHack || !SOCKETL || !SOCKETG)
		return FALSE;

	if (!SendSaveThrowItem2(&lpItem->sItem))
		return FALSE;

	TransThrowItem.code = smTRANSCODE_THROWITEM;
	TransThrowItem.size = sizeof(TRANS_ITEMINFO);
	TransThrowItem.x = x;
	TransThrowItem.y = y;
	TransThrowItem.z = z;

	memcpy(&TransThrowItem.sItem, &lpItem->sItem, sizeof(Item));

	return TRUE;
}

int ThrowPutItem2(Item *lpItem, int x, int y, int z)
{
	if ((dwRecvServerTime + 4000) < dwPlayTime || QuitSave || TransThrowItem.code)
		return FALSE;

	if (WarningHack || !SOCKETL || !SOCKETG) 
		return FALSE;

	if (!SendSaveThrowItem2(lpItem))
		return FALSE;

	TransThrowItem.code = smTRANSCODE_THROWITEM;
	TransThrowItem.size = sizeof(TRANS_ITEMINFO);
	TransThrowItem.x = x;
	TransThrowItem.y = y;
	TransThrowItem.z = z;

	memcpy(&TransThrowItem.sItem, lpItem, sizeof(Item));

	return TRUE;
}

int	ThrowPotionCount = 0;


int ThrowItemToServer(smTRANS_COMMAND_EX *lpTransCommand)
{
	smTRANS_COMMAND	smTransCommand;
	DWORD	dwItemCodeMask;

	if (TransThrowItem.code && TransThrowItem.sItem.sItemID.ToInt() == (DWORD)lpTransCommand->WParam && TransThrowItem.sItem.iChk1 == (DWORD)lpTransCommand->LParam && TransThrowItem.sItem.iChk2 == (DWORD)lpTransCommand->SParam)
	{
		if ((TransThrowItem.sItem.sItemID.ToItemBase()) != (sinPM1&sinITEM_MASK1))
		{
			cInvenTory.DeleteInvenItemToServer(TransThrowItem.sItem.sItemID.ToInt(), TransThrowItem.sItem.iChk1, TransThrowItem.sItem.iChk2);

			if (FindInvenItem(TransThrowItem.sItem.sItemID.ToInt(), TransThrowItem.sItem.iChk1, TransThrowItem.sItem.iChk2) != 0)
			{
				SendInvenItemError(0, TransThrowItem.sItem.sItemID.ToInt(), TransThrowItem.sItem.iChk1, TransThrowItem.sItem.iChk2);

				TransThrowItem.code = 0;
				return TRUE;
			}
		}
		else
		{
			if ((dwPlayTime - dwLastRecordTime) > 4000 && TransThrowItem.sItem.iPotionCount >= 10)
			{
				SaveGameData();
				ThrowPotionCount = 0;
			}
			else
			{
				ThrowPotionCount += TransThrowItem.sItem.iPotionCount;
				if (ThrowPotionCount >= 15)
				{
					ThrowPotionCount = 0;
					SaveGameData();
				}
			}
		}

		if ((TransThrowItem.sItem.sItemID.ToItemType()) == sinBC1)
		{
			if (TransThrowItem.sItem.iPotionCount == 100)
				TransThrowItem.sItem.iPotionCount = 200;

			if (TransThrowItem.sItem.sItemID.ToInt() == (sinBC1 | sin04) && TransThrowItem.sItem.iPotionCount == 200)
			{
				smTransCommand.size = sizeof(smTRANS_COMMAND);
				smTransCommand.code = smTRANSCODE_PARTY_POTION;
				smTransCommand.WParam = 3000;
				smTransCommand.LParam = 3000;
				smTransCommand.SParam = 3000;
				smTransCommand.EParam = lpCurPlayer->iID;

				SENDPACKETG(&smTransCommand);

				SetPartyPosion(&smTransCommand);

				TransThrowItem.code = 0;
				return TRUE;
			}
		}

		if (!TransThrowItem.sItem.SpecialItemFlag[0])
		{
			TransThrowItem.dwSeCode[0] = lpTransCommand->WxParam;
			TransThrowItem.dwSeCode[1] = lpTransCommand->LxParam;
			TransThrowItem.dwSeCode[2] = lpTransCommand->SxParam;
			TransThrowItem.dwSeCode[3] = lpTransCommand->ExParam;

			dwItemCodeMask = TransThrowItem.sItem.sItemID.ToItemType();

			if (((dwItemCodeMask == sinGP1 || dwItemCodeMask == sinCH1 || dwItemCodeMask == sinFO1) && TransThrowItem.sItem.iPotionCount == 100) ||
				(TransThrowItem.sItem.sItemID.ToInt() == (sinGG1 | sin01) && TransThrowItem.sItem.eCraftType == ITEMCRAFTTYPE_Event) ||
				(dwItemCodeMask == sinBC1 && TransThrowItem.sItem.iPotionCount == 200) ||
				(dwItemCodeMask == sinBI1 && TransThrowItem.sItem.iPotionCount == 300) ||
				(dwItemCodeMask == sinBI2 && TransThrowItem.sItem.iPotionCount == 300))
			{
				SENDPACKETG(&TransThrowItem);

				if (dwItemCodeMask == sinBI1 || dwItemCodeMask == sinBI2)
				{
					switch (TransThrowItem.sItem.sItemID.ToInt())
					{
					case sinBI1 | sin12:
						chaPremiumitem.m_ThirdEyesTime = PRIME_ITEM_TIME_THIRDEYES;
						break;
					case sinBI1 | sin13:
						chaPremiumitem.m_ExpUpPotionTime = PRIME_ITEM_TIME_EXPUP;
						break;
					case sinBI1 | sin14:
						chaPremiumitem.m_ThirdEyesTime = PRIME_ITEM_TIME_THIRDEYESx7;
						break;
					case sinBI1 | sin15:
						chaPremiumitem.m_ExpUpPotionTime = PRIME_ITEM_TIME_EXPUPx7;
						break;
					case sinBI1 | sin23:
					{
						GAMEUNIT->Fun();
					}
					break;
					case sinBI1 | sin24:
						chaPremiumitem.m_ExpUpPotionTime = PRIME_ITEM_TIME_EXPUP;
						break;
					case sinBI1 | sin25:
						chaPremiumitem.m_ExpUpPotionTime = PRIME_ITEM_TIME_EXPUPx7;
						break;
					case sinBI1 | sin26:
						chaPremiumitem.m_MightofAwellTime = PRIME_ITEM_TIME_EXPUPx7;
						chaPremiumitem.m_MightofAwellWeight = 300;
						break;
					case sinBI1 | sin27:
						chaPremiumitem.m_MightofAwellTime = PRIME_ITEM_TIME_6HOUR;
						chaPremiumitem.m_MightofAwellWeight = 300;
						break;
					case sinBI1 | sin28:
						chaPremiumitem.m_ManaReducePotiontime = PRIME_ITEM_TIME_EXPUP;
						chaPremiumitem.m_ManaReducePotionValue = 30;
						break;
					case sinBI1 | sin29:
						chaPremiumitem.m_ManaReducePotiontime = PRIME_ITEM_TIME_EXPUPx7;
						chaPremiumitem.m_ManaReducePotionValue = 30;
						break;
					case sinBI1 | sin30:
						chaPremiumitem.m_MightofAwellTime = PRIME_ITEM_TIME_EXPUPx7;
						chaPremiumitem.m_MightofAwellWeight = 500;
						break;
					case sinBI1 | sin31:
						chaPremiumitem.m_MightofAwellTime = PRIME_ITEM_TIME_PACKAGE4;
						chaPremiumitem.m_MightofAwellWeight = 500;
						break;
					case sinBI1 | sin43:
						chaPremiumitem.m_ExpUpPotionTime = PRIME_ITEM_TIME_EXPUP;
						break;
					case sinBI1 | sin44:
						chaPremiumitem.m_ExpUpPotionTime = PRIME_ITEM_TIME_EXPUPx7;
						break;
					case sinBI1 | sin50:
						chaPremiumitem.m_ExpUpPotionTime = PRIME_ITEM_TIME_PACKAGE4;
						break;
					case sinBI1 | sin52:
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_PACKAGE4);

						cHelpPet.PetKind = HoLowLevelPet::Type::Terry + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
						break;
					case sinBI1 | sin53:
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_PACKAGE4);

						cHelpPet.PetKind = HoLowLevelPet::Type::Nepsys + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
						break;
					case sinBI1 | sin54:
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_PACKAGE4);

						cHelpPet.PetKind = HoLowLevelPet::Type::Io + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
						break;
					case sinBI1 | sin55:
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_PACKAGE4);

						cHelpPet.PetKind = HoLowLevelPet::Type::Mute + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
						break;
					case sinBI1 | sin69:
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_PACKAGE2);

						cHelpPet.PetKind = HoLowLevelPet::Type::Terry + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
						break;
					case sinBI1 | sin70:
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_PACKAGE2);

						cHelpPet.PetKind = HoLowLevelPet::Type::Nepsys + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
						break;
					case sinBI1 | sin71:
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_PACKAGE2);

						cHelpPet.PetKind = HoLowLevelPet::Type::Io + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
						break;
					case sinBI1 | sin72:
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_PACKAGE2);

						cHelpPet.PetKind = HoLowLevelPet::Type::Mute + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
						break;
					case sinBI1 | sin80:
						chaPremiumitem.m_ExpUpPotionTime = PRIME_ITEM_TIME_PACKAGE5;
						break;
					case sinBI1 | sin65:
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_PACKAGE3);

						cHelpPet.PetKind = HoLowLevelPet::Type::Terry + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
						break;
					case sinBI1 | sin66:
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_PACKAGE3);

						cHelpPet.PetKind = HoLowLevelPet::Type::Nepsys + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
						break;
					case sinBI1 | sin67:
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_PACKAGE3);

						cHelpPet.PetKind = HoLowLevelPet::Type::Io + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
						break;
					case sinBI1 | sin68:
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_PACKAGE3);

						cHelpPet.PetKind = HoLowLevelPet::Type::Mute + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
						break;
					case sinBI1 | sin73:
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_PACKAGE5);

						cHelpPet.PetKind = HoLowLevelPet::Type::Terry + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
						break;
					case sinBI1 | sin74:
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_PACKAGE5);

						cHelpPet.PetKind = HoLowLevelPet::Type::Nepsys + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
						break;
					case sinBI1 | sin75:
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_PACKAGE5);

						cHelpPet.PetKind = HoLowLevelPet::Type::Io + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
						break;
					case sinBI1 | sin76:
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_PACKAGE5);

						cHelpPet.PetKind = HoLowLevelPet::Type::Mute + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
						break;
					case sinBI1 | sin78:
						chaPremiumitem.m_ThirdEyesTime = PRIME_ITEM_TIME_PACKAGE5;
						break;
					case sinBI1 | sin79:
						chaPremiumitem.m_ExpUpPotionTime = PRIME_ITEM_TIME_PACKAGE5;
						break;
					case sinBI1 | sin83:
						chaPremiumitem.m_ManaReducePotiontime = PRIME_ITEM_TIME_PACKAGE5;
						chaPremiumitem.m_ManaReducePotionValue = 30;
						break;
					case sinBI1 | sin91:
						chaPremiumitem.m_StaminaReducePotiontime = PRIME_ITEM_TIME_EXPUP;
						chaPremiumitem.m_StaminaReducePotionValue = 30;
						break;
					case sinBI1 | sin92:
						chaPremiumitem.m_StaminaReducePotiontime = PRIME_ITEM_TIME_EXPUPx7;
						chaPremiumitem.m_StaminaReducePotionValue = 30;
						break;
					}

					if (TransThrowItem.sItem.sItemID.ToInt() == ((sinBI2 | sin01)))
						int test = 1;

					switch (TransThrowItem.sItem.sItemID.ToInt())
					{
					case (sinBI2 | sin01):
					case (sinBI2 | sin05):
					case (sinBI2 | sin09):
					case (sinBI2 | sin23):
						chaPremiumitem.m_ThirdEyesTime = PRIME_ITEM_TIME_PACKAGE1;
						chaPremiumitem.m_ExpUpPotionTime = PRIME_ITEM_TIME_PACKAGE1;
						break;
					case (sinBI2 | sin02):
					case (sinBI2 | sin06):
					case (sinBI2 | sin10):
					case (sinBI2 | sin24):
						chaPremiumitem.m_ThirdEyesTime = PRIME_ITEM_TIME_PACKAGE2;
						chaPremiumitem.m_ExpUpPotionTime = PRIME_ITEM_TIME_PACKAGE2;
						break;
					case (sinBI2 | sin03):
					case (sinBI2 | sin07):
					case (sinBI2 | sin11):
					case (sinBI2 | sin25):
						chaPremiumitem.m_ThirdEyesTime = PRIME_ITEM_TIME_PACKAGE3;
						chaPremiumitem.m_ExpUpPotionTime = PRIME_ITEM_TIME_PACKAGE3;
						break;
					case (sinBI2 | sin04):
					case (sinBI2 | sin08):
					case (sinBI2 | sin12):
						chaPremiumitem.m_ThirdEyesTime = PRIME_ITEM_TIME_PACKAGE4;
						chaPremiumitem.m_ExpUpPotionTime = PRIME_ITEM_TIME_PACKAGE4;
						break;
					case (sinBI2 | sin26):
						chaPremiumitem.m_ExpUpPotionTime = PRIME_ITEM_TIME_PACKAGE1;
						chaPremiumitem.m_ManaReducePotiontime = PRIME_ITEM_TIME_PACKAGE1;
						chaPremiumitem.m_ManaReducePotionValue = 10;
						break;
					case (sinBI2 | sin27):
						chaPremiumitem.m_ExpUpPotionTime = PRIME_ITEM_TIME_PACKAGE2;
						chaPremiumitem.m_ManaReducePotiontime = PRIME_ITEM_TIME_PACKAGE2;
						chaPremiumitem.m_ManaReducePotionValue = 10;
						break;
					case (sinBI2 | sin28):
						chaPremiumitem.m_ExpUpPotionTime = PRIME_ITEM_TIME_PACKAGE3;
						chaPremiumitem.m_ManaReducePotiontime = PRIME_ITEM_TIME_PACKAGE3;
						chaPremiumitem.m_ManaReducePotionValue = 10;
						break;
					case (sinBI2 | sin29):
						chaPremiumitem.m_ExpUpPotionTime = PRIME_ITEM_TIME_PACKAGE1;
						chaPremiumitem.m_ManaReducePotiontime = PRIME_ITEM_TIME_PACKAGE1;
						chaPremiumitem.m_ManaReducePotionValue = 20;
						break;
					case (sinBI2 | sin30):
						chaPremiumitem.m_ExpUpPotionTime = PRIME_ITEM_TIME_PACKAGE2;
						chaPremiumitem.m_ManaReducePotiontime = PRIME_ITEM_TIME_PACKAGE2;
						chaPremiumitem.m_ManaReducePotionValue = 20;
						break;
					case (sinBI2 | sin31):
						chaPremiumitem.m_ExpUpPotionTime = PRIME_ITEM_TIME_PACKAGE3;
						chaPremiumitem.m_ManaReducePotiontime = PRIME_ITEM_TIME_PACKAGE3;
						chaPremiumitem.m_ManaReducePotionValue = 20;
						break;
					case (sinBI2 | sin32):
						chaPremiumitem.m_ExpUpPotionTime = PRIME_ITEM_TIME_PACKAGE1;
						chaPremiumitem.m_ManaReducePotiontime = PRIME_ITEM_TIME_PACKAGE1;
						chaPremiumitem.m_ManaReducePotionValue = 30;
						break;
					case (sinBI2 | sin33):
						chaPremiumitem.m_ExpUpPotionTime = PRIME_ITEM_TIME_PACKAGE2;
						chaPremiumitem.m_ManaReducePotiontime = PRIME_ITEM_TIME_PACKAGE2;
						chaPremiumitem.m_ManaReducePotionValue = 30;
						break;
					case (sinBI2 | sin34):
						chaPremiumitem.m_ExpUpPotionTime = PRIME_ITEM_TIME_PACKAGE3;
						chaPremiumitem.m_ManaReducePotiontime = PRIME_ITEM_TIME_PACKAGE3;
						chaPremiumitem.m_ManaReducePotionValue = 30;
						break;
					case (sinBI2 | sin35):
						chaPremiumitem.m_ExpUpPotionTime = PRIME_ITEM_TIME_PACKAGE1;
						chaPremiumitem.m_ManaReducePotiontime = PRIME_ITEM_TIME_PACKAGE1;
						chaPremiumitem.m_ManaReducePotionValue = 40;
						break;
					case (sinBI2 | sin36):
						chaPremiumitem.m_ExpUpPotionTime = PRIME_ITEM_TIME_PACKAGE2;
						chaPremiumitem.m_ManaReducePotiontime = PRIME_ITEM_TIME_PACKAGE2;
						chaPremiumitem.m_ManaReducePotionValue = 40;
						break;
					case (sinBI2 | sin37):
						chaPremiumitem.m_ExpUpPotionTime = PRIME_ITEM_TIME_PACKAGE3;
						chaPremiumitem.m_ManaReducePotiontime = PRIME_ITEM_TIME_PACKAGE3;
						chaPremiumitem.m_ManaReducePotionValue = 40;
						break;
					}
				}

			}
			else
				SENDPACKETG(&TransThrowItem);
		}
	}

	TransThrowItem.code = 0;
	return TRUE;
}
int SendAddStartPoint(int x, int z)
{
	smTRANS_COMMAND	TransCommand;

	TransCommand.code = smTRANSCODE_ADD_STARTPOSI;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.LParam = x;
	TransCommand.WParam = z;
	TransCommand.SParam = TRUE;

	SENDPACKETG(&TransCommand);

	return NULL;
}


int SendDeleteStartPoint(int x, int z)
{
	smTRANS_COMMAND	TransCommand;
	scITEM	*lpItem;

	TransCommand.code = smTRANSCODE_DEL_STARTPOSI;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.LParam = x;
	TransCommand.WParam = z;
	TransCommand.SParam = TRUE;


	lpItem = FindScItem(x, z);
	if (lpItem)
	{
		lpItem->Close();
	}

	SENDPACKETG(&TransCommand);

	return NULL;
}



//NPC Ä³¸¯ÅÍ Ãß°¡
int SendAdd_Npc(Unit *lpCharSample, int state)
{
	smTRNAS_PLAYERINFO	smTransPlayerInfo;

	smTransPlayerInfo.code = smTRANSCODE_ADD_NPC;
	smTransPlayerInfo.size = sizeof(smTRNAS_PLAYERINFO);
	memcpy(&smTransPlayerInfo.sCharacterData, &lpCharSample->sCharacterData, sizeof(CharacterData));
	smTransPlayerInfo.sCharacterData.iType = CHARACTERTYPE_NPC;


	lstrcpy(smTransPlayerInfo.sCharacterData.Player.szHeadModel, NpcSelectedName);

	smTransPlayerInfo.sCharacterData.sHP.sMin = 100;
	smTransPlayerInfo.sCharacterData.sMP.sMin = 100;
	smTransPlayerInfo.sCharacterData.sHP.sMax = 100;

	smTransPlayerInfo.x = lpCharSample->pX;
	smTransPlayerInfo.y = lpCharSample->pY;
	smTransPlayerInfo.z = lpCharSample->pZ;

	smTransPlayerInfo.ax = lpCharSample->Angle.x;
	smTransPlayerInfo.ay = lpCharSample->Angle.y;
	smTransPlayerInfo.az = lpCharSample->Angle.z;

	smTransPlayerInfo.state = state;

	SENDPACKETG(&smTransPlayerInfo);

	return NULL;
}
int SendDelete_Npc(Unit *lpCharSample)
{
	smTRNAS_PLAYERINFO	smTransPlayerInfo;

	smTransPlayerInfo.code = smTRANSCODE_DEL_NPC;
	smTransPlayerInfo.size = sizeof(smTRNAS_PLAYERINFO);
	memcpy(&smTransPlayerInfo.sCharacterData, &lpCharSample->sCharacterData, sizeof(CharacterData));

	smTransPlayerInfo.x = lpCharSample->pX;
	smTransPlayerInfo.y = lpCharSample->pY;
	smTransPlayerInfo.z = lpCharSample->pZ;

	smTransPlayerInfo.ax = lpCharSample->Angle.x;
	smTransPlayerInfo.ay = lpCharSample->Angle.y;
	smTransPlayerInfo.az = lpCharSample->Angle.z;

	smTransPlayerInfo.dwObjectSerial = lpCharSample->iID;

	lpCharSample->Close();

	SENDPACKETG(&smTransPlayerInfo);

	return NULL;
}


int SendGetRecordData(char *szName)
{
	smTRANS_CHAR_COMMAND	smTransCharCommand;

	smTransCharCommand.code = smTRANSCODE_GETRECORDDATA;
	smTransCharCommand.size = sizeof(smTRANS_CHAR_COMMAND);

	smTransCharCommand.WParam = dwExeCheckSum;
	smTransCharCommand.LParam = FALSE;
	smTransCharCommand.SParam = GAME_VERSION;

	lstrcpy(smTransCharCommand.szName, szName);

	dwLoadingTime = GetCurrentTime();

	SENDPACKETL(&smTransCharCommand);

	return FALSE;
}

char *szCmdOpenMonster[10] =
{
	"È©°íºí¸°",
	"È©°íºí¸°",
	"È©°íºí¸°",
	"Å·È£ÇÇ",
	"Å¸ÀÌÅº",
	0,0,0,0,0
};
int	CodeXorCharInfo()
{
	lpCurPlayer->sCharacterData.sHP.sMin ^= CodeXorLife;
	return TRUE;
}
int SaveCheckSkill()
{
	ReformSkillInfo();

	for (int j = 1; j < SIN_MAX_USE_SKILL; j++)
	{
		if (sinSkill.UseSkill[j].Flag && sinSkill.UseSkill[j].Point)
		{
			if (cSkill.CheckSkillPointForm(&sinSkill.UseSkill[j]) == FALSE)
				return FALSE;
			if (cSkill.CheckSkillMasteryForm(&sinSkill.UseSkill[j]) == FALSE)
				return FALSE;
		}
	}

	return TRUE;
}

int ReformSkillInfo()
{
	for (int j = 1; j < SIN_MAX_USE_SKILL; j++)
	{
		cSkill.ReformSkillMasteryForm(&sinSkill.UseSkill[j]);
		cSkill.ReformSkillPointForm(&sinSkill.UseSkill[j]);
	}
	return TRUE;
}
int	SaveGameData()
{
	if (SOCKETL && !rsRecorder.dwRecordTime && lpCurPlayer->sCharacterData.iClass && !cTrade.OpenFlag && !cWareHouse.OpenFlag && !cCaravan.OpenFlag && !QuitSave)
	{
		if (!WarningHack && CheckCharForm() != FALSE && SaveCheckSkill() == TRUE)
		{
			CodeXorCharInfo();
			ReformCharForm();

			rsRecorder.MakeRecordData(&lpCurPlayer->sCharacterData, cInvenTory.InvenItem, cInvenTory.InvenItemTemp, &MouseItem);
			rsRecorder.SendRecordDataToServer(NULL);
			rsRecorder.dwRecordTime = dwPlayTime;

			if (SETTINGHANDLE->Get().bDebugMode)
				CHATGAMEHANDLE->AddChatBoxText("GameSave");

			CodeXorCharInfo();
			ReformCharForm();
			CheckPlaySkill();
			return TRUE;
		}
	}
	return FALSE;
}
int GetSaveResult()
{
	if (rsRecorder.dwRecordTime)
		return FALSE;

	return TRUE;
}

smTRANS_COMMAND	smMessageCommandBuff;


int	TransUserCommand(DWORD dwCode, char *szID, char *szName)
{
	smTRANS_CHAR_COMMAND2	TransCharCommand2;

	TransCharCommand2.code = dwCode;
	TransCharCommand2.size = sizeof(smTRANS_CHAR_COMMAND2);

	if (szID)
		lstrcpy(TransCharCommand2.szId, szID);

	if (szName)
		lstrcpy(TransCharCommand2.szName, szName);

	SENDPACKETL(&TransCharCommand2);

	return TRUE;
}


int	Send_GetCharInfo(DWORD	dwObjectSerial, int ServerCode)
{
	smTRANS_COMMAND			TransCommand;

	TransCommand.code = smTRANSCODE_GETPLAYERINFO;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = dwObjectSerial;

	SENDPACKETG(&TransCommand);

	return FALSE;
}

#define DEADLOCK_CHECK_LIMIT_TIME		(30*1000)
#define DEADLOCK_CHECK_LIMIT_TIME2		(60*1000)
#define RECONNECT_LIMIT_TIME			(7*1000)


static DWORD dwCheckNetCount = 0;
static DWORD dwLastTransCheckTime = 0;
static int	ReconnectCount = 0;

int SendNetworkQuality(DWORD NetworkQuality)
{
	smTRANS_COMMAND	TransCommand;

	TransCommand.code = smTRANSCODE_NETWORK_QUALITY;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = NetworkQuality;
	TransCommand.LParam = 0;
	TransCommand.SParam = 0;

	SENDPACKETG(&TransCommand);

	return 0;
}
int SendSetObjectSerial(DWORD dwObjectSerial)
{
	smTRNAS_PLAYERINFO	TransPlayerInfo;

	memcpy(&TransPlayerInfo.sCharacterData, &lpCurPlayer->sCharacterData, sizeof(CharacterData));
	TransPlayerInfo.size = sizeof(smTRNAS_PLAYERINFO);
	TransPlayerInfo.code = smTRANSCODE_PLAYERINFO2;
	TransPlayerInfo.dwObjectSerial = lpCurPlayer->iID;

	TransPlayerInfo.x = lpCurPlayer->pX;
	TransPlayerInfo.y = lpCurPlayer->pY;
	TransPlayerInfo.z = lpCurPlayer->pZ;

	SENDPACKETG(&TransPlayerInfo);

	return TRUE;
}
int SendSetHackUser3(int Type, int LParam, int SParam)
{
	smTRANS_COMMAND	TransCommand;

	TransCommand.code = smTRANSCODE_SET_BLACKLIST2;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = Type;
	TransCommand.LParam = LParam;
	TransCommand.SParam = SParam;

	SENDPACKETL(&TransCommand);

	return TRUE;
}

//ÖÐ¶ÏÁ¬½Ó4
int SendSetHackUser(int StopGame)
{
	smTRANS_COMMAND	TransCommand;

	TransCommand.code = smTRANSCODE_SET_BLACKLIST;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = StopGame;
	TransCommand.LParam = 0;
	TransCommand.SParam = 0;

	WarningHack = StopGame;

	SENDPACKETL(&TransCommand);

	if (WarningHack)
	{
		GAMESOCKET->iDisconnectType = 4;
		GAMESOCKET->iDisconnectTime = TICKCOUNT;
	}

	return TRUE;
}
int SendSetHackUser2(int Type, int LParam)
{
	smTRANS_COMMAND	TransCommand;

	TransCommand.code = smTRANSCODE_SET_BLACKLIST;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = Type;
	TransCommand.LParam = LParam;
	TransCommand.SParam = 0;

	SENDPACKETL(&TransCommand);

	return TRUE;
}
int SendAdminMode2(DWORD AdminNum)
{
	smTRANS_COMMAND	TransCommand;

	TransCommand.code = smTRANSCODE_ADMINMODE2;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = AdminNum;
	TransCommand.LParam = 1;
	TransCommand.SParam = 0;

	SENDPACKETL(&TransCommand);

	return TRUE;
}
int SendCopyItemUser(int CopyItemCount)
{
	smTRANS_COMMAND	TransCommand;

	TransCommand.code = smTRANSCODE_SET_ITEMCOPYLIST;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = CopyItemCount;
	TransCommand.LParam = 0;
	TransCommand.SParam = 0;

	SENDPACKETL(&TransCommand);

	return TRUE;
}
int SendSaveThrowItem(Item *lpItemInfo)
{
	smTRANS_COMMAND	TransCommand;

	if ((lpItemInfo->sItemID.ToItemBase()) != (sinPM1&sinITEM_MASK1))
		return FALSE;

	TransCommand.code = smTRANSCODE_SAVETHROWITEM;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = lpItemInfo->sItemID.ToInt();
	TransCommand.LParam = lpItemInfo->iChk1;
	TransCommand.SParam = lpItemInfo->iChk2;

	if ((lpItemInfo->sItemID.ToItemBase()) == (sinPM1&sinITEM_MASK1))
		ComparePotion();

	SENDPACKETL(&TransCommand);

	return TRUE;
}
int	SendRecordTradeItems(sTRADE *lpTrade)
{
	TRANS_RECORD_TRADE_ITEMS	TransRecordTradeItems;
	int cnt;

	ZeroMemory(&TransRecordTradeItems, sizeof(TRANS_RECORD_TRADE_ITEMS));

	TransRecordTradeItems.code = smTRANSCODE_RECORD_TRADE;
	TransRecordTradeItems.Money = lpTrade->Money - 193;
	lstrcpy(TransRecordTradeItems.szTradeUserName, cTrade.szTradeCharName);

	for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++)
	{
		if (lpTrade->TradeItem[cnt].bValid && TransRecordTradeItems.ThrowItemCount < TRADE_RECV_ITEMS_MAX)
		{
			TransRecordTradeItems.Items[TransRecordTradeItems.ThrowItemCount].dwCode = lpTrade->TradeItem[cnt].sItem.sItemID.ToInt();
			TransRecordTradeItems.Items[TransRecordTradeItems.ThrowItemCount].dwHead = lpTrade->TradeItem[cnt].sItem.iChk1;
			TransRecordTradeItems.Items[TransRecordTradeItems.ThrowItemCount].dwChkSum = lpTrade->TradeItem[cnt].sItem.iChk2;
			TransRecordTradeItems.ThrowItemCount++;
		}
	}

	TransRecordTradeItems.size = TRANS_RECORD_TRADE_DEFSIZE + TransRecordTradeItems.ThrowItemCount * sizeof(_TRANS_RECORD_TRADE_ITEM);

	SENDPACKETL(&TransRecordTradeItems);

	return 1;
}
int SendSaveThrowItem2(Item *lpItemInfo)
{
	smTRANS_COMMAND_EX	TransCommand;

	TransCommand.code = smTRANSCODE_SAVETHROWITEM2;
	TransCommand.size = sizeof(smTRANS_COMMAND_EX);
	TransCommand.WParam = lpItemInfo->sItemID.ToInt();
	TransCommand.LParam = lpItemInfo->iChk1;
	TransCommand.SParam = lpItemInfo->iChk2;
	TransCommand.EParam = lpItemInfo->iPotionCount^TransCommand.SParam^TransCommand.code;

	TransCommand.WxParam = lpCurPlayer->sCharacterData.iGold;
	TransCommand.LxParam = EncodeParam(TransCommand.WxParam);
	TransCommand.SxParam = GetTotalMoney() ^ TransCommand.LxParam;
	TransCommand.ExParam = lpItemInfo->iGold;

	if ((lpItemInfo->sItemID.ToItemBase()) == (sinPM1&sinITEM_MASK1))
		ComparePotion();

	AddInvenMoney(-lpItemInfo->iGold);

	SENDPACKETL(&TransCommand);

	return 1;
}
int SendSaveMoney()
{
	smTRANS_COMMAND	TransCommand;

	//if (cWareHouse.OpenFlag && CompWareHouseMoney) 
		//return FALSE;

	TransCommand.code = smTRANSCODE_SAVETHROWMONEY;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = lpCurPlayer->sCharacterData.iGold;
	TransCommand.LParam = EncodeParam(TransCommand.WParam);
	TransCommand.SParam = GetTotalMoney() ^ TransCommand.LParam;

	SENDPACKETL(&TransCommand);

	return 1;
}
int SendPlayUpdateInfo()
{
	smTRANS_COMMAND	TransCommand;

	TransCommand.code = smTRANSCODE_UPDATE_CINFO;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = 0;
	TransCommand.LParam = lpCurPlayer->sCharacterData.iLevel;
	TransCommand.SParam = 0;
	TransCommand.EParam = 0;

	SENDPACKETG(&TransCommand);

	return 0;
}

int SendUpdateClanInfo()
{
	smTRANS_COMMAND	TransCommand;

	TransCommand.code = smTRANSCODE_UPDATE_CINFO;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = 1;
	TransCommand.LParam = lpCurPlayer->sCharacterData.iLevel;
	TransCommand.SParam = lpCurPlayer->sCharacterData.iClanID;
	TransCommand.EParam = lpCurPlayer->sCharacterData.bUpdateInfo[0];

	SENDPACKETG(&TransCommand);

	if (rsBlessCastle.dwMasterClan == GetClanCode(lpCurPlayer->sCharacterData.iClanID))
		SENDPACKETL(&TransCommand);

	return TRUE;
}
// ¼ì²â¸üÐÂVIPÐÅÏ¢
int SendUpdataVipInfo()
{
	smTRANS_COMMAND	TransCommand;
	TransCommand.code = smTRANSCODE_PLAYER_DATA_VIP;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = lpCurPlayer->dwVipBit;
	TransCommand.LParam = lpCurPlayer->dwVipTime;
	TransCommand.SParam = 0;

	SENDPACKETL(&TransCommand);

	return 0;
}

TRANS_SKIL_ATTACKDATA	Back_TransSkilAttackData;

// Ñ£ÔÎ¼¼ÄÜ
int Skill_CharRangeEffect(DWORD dwSkillCode, Unit *lpCurChar, Unit *lpCharTarget, int point)
{
	int JobCode = lpCurChar->sCharacterData.iClass;

	// Áé»êÍÌÊÉ
	if (JobCode == CHARACTERCLASS_Atalanta && dwSkillCode == SKILL_PLAY_SOUL_SUCKER)
	{
		if (lpCharTarget->sCharacterData.iMonsterType != MONSTERTYPE_Undead && ((lpCharTarget->sCharacterData.sHP.sMax * 50) / 100) < lpCharTarget->sCharacterData.sHP.sMin)
		{
			sinSkillEffect_Soul_Sucker(lpCurChar, lpCharTarget);
			return TRUE;
		}
	}
	return FALSE;
}


//Áé»êÍÌÊÉÐ§¹û
int Skil_RangeBoxEffect(Unit *lpCurChar, RECT *lpRect, DWORD dwSkillCode, int TargetState)
{
	int cnt, mCnt;
	int dx, dy, dz;
	Unit	*lpChar;

	mCnt = 0;

	for (cnt = 0; cnt < MAX_UNITS; cnt++)
	{
		if (mCnt >= SKIL_ATTACK_CHAR_MAX)
			break;
		if (chrOtherPlayer[cnt].bActive && chrOtherPlayer[cnt].sCharacterData.iType == CHARACTERTYPE_Monster && lpCurChar != &chrOtherPlayer[cnt])
		{
			lpChar = &chrOtherPlayer[cnt];

			dx = (lpChar->pX - lpCurChar->pX) >> FLOATNS;
			dy = (lpChar->pY - lpCurChar->pY) >> FLOATNS;
			dz = (lpChar->pZ - lpCurChar->pZ) >> FLOATNS;

			auto sPosition = GetMoveLocation(dx, dy, dz, 0, (-lpCurChar->Angle.y)&ANGCLIP, 0);

			if (sPosition.iX > lpRect->left && sPosition.iX < lpRect->right  && sPosition.iZ > lpRect->top && sPosition.iZ < lpRect->bottom && abs(dy) < 256)
			{
				if (Skill_CharRangeEffect(dwSkillCode, lpCurChar, &chrOtherPlayer[cnt], 0) == TRUE)
					mCnt++;
			}
		}
	}

	return mCnt;
}

//Ñ£ÔÎ¼¼ÄÜÐ§¹û
int Skil_RangeEffect(Unit *lpCurChar, int Range, DWORD dwSkillCode, int TargetState, int point)
{
	int cnt, mCnt;
	int dx, dy, dz;
	Unit	*lpChar;
	int	dRange;

	dRange = Range * Range;

	mCnt = 0;

	for (cnt = 0; cnt < MAX_UNITS; cnt++)
	{
		if (mCnt >= SKIL_ATTACK_CHAR_MAX)
			break;
		if (chrOtherPlayer[cnt].bActive && chrOtherPlayer[cnt].sCharacterData.iType == CHARACTERTYPE_Monster && lpCurChar != &chrOtherPlayer[cnt])
		{
			lpChar = &chrOtherPlayer[cnt];

			dx = (lpChar->pX - lpCurChar->pX) >> FLOATNS;
			dy = (lpChar->pY - lpCurChar->pY) >> FLOATNS;
			dz = (lpChar->pZ - lpCurChar->pZ) >> FLOATNS;

			if ((dx*dx + dy * dy + dz * dz) < dRange)
			{
				if (Skill_CharRangeEffect(dwSkillCode, lpCurChar, &chrOtherPlayer[cnt], point) == TRUE)
					mCnt++;
			}
		}
	}

	return mCnt;
}
DWORD EncodeParam(DWORD Param)
{
	return (Param + (Param << 4)) * 2002;
}

int SendRequestTrade(int dwObjectSerial, int Flag)
{
	smTRANS_COMMAND	TransCommand;

	TransCommand.code = smTRANSCODE_TRADE_REQUST;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = dwObjectSerial;
	TransCommand.LParam = Flag;
	TransCommand.SParam = lpCurPlayer->iID;

	SENDPACKETG(&TransCommand);

	return FALSE;
}
int SendTradeItem(sTRADE *lpTrade, DWORD dwSender)
{
	int cnt;
	int len;
	int	PotionError = 0;
	TRANS_TRADEITEMS TransTradeItems;
	sTRADE	sTradeBuff;

	len = 0;

	if (CheckTrade((void *)lpTrade) == FALSE)
	{
		SendRequestTrade(dwSender, 3);
		cTrade.CancelTradeItem();
		return FALSE;
	}

	memcpy(&sTradeBuff, lpTrade, sizeof(sTRADE));


	PotionError = ComparePotion();

	for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++) {
		if (!sTradeBuff.TradeItem[cnt].bValid) {
			ZeroMemory(&sTradeBuff.TradeItem[cnt], sizeof(ItemData));
		}
		else {
			sTradeBuff.TradeItem[cnt].sItem.iChk1 = 0;		//Å°°ª Áö¿ò
			if (PotionError) {
				sTradeBuff.TradeItem[cnt].sItem.iPotionCount = sTradeBuff.TradeItem[cnt].sItem.iChk1 + 1;	//¹°¾à°¹¼ö ¿À·ù½Ã ¸ðµç Æ÷¼ÇÄ«¿îÆ®¸¦ 1·Î ¹Ù²Û´Ù
			}
			len++;
		}
	}

	len = EecodeCompress((BYTE *)&sTradeBuff, TransTradeItems.TradeBuff, sizeof(sTRADE));
	if (len > TRANS_TRADE_BUFF_SIZE) return FALSE;

	TransTradeItems.code = smTRANSCODE_TRADEITEMS;
	TransTradeItems.size = len + 48;
	TransTradeItems.dwSum = 0;
	TransTradeItems.dwSender = lpCurPlayer->iID;
	TransTradeItems.dwRecver = dwSender;
	TransTradeItems.Temp[0] = 0;
	TransTradeItems.Temp[1] = 0;
	TransTradeItems.Temp[2] = 0;
	TransTradeItems.Temp[3] = 0;

	SENDPACKETG(&TransTradeItems);

	return FALSE;
}

//¾ÆÀÌÅÛ ±³È¯ Á¤º¸ ¼ö½Å 
int RecvTradeItems(TRANS_TRADEITEMS *lpTransTradeItems, sTRADE *lpTrade)
{
	//¾ÐÃà µ¥ÀÌÅ¸ ÇØµ¶ ( Z/NZ ¹æ½Ä )
	DecodeCompress(lpTransTradeItems->TradeBuff, (BYTE *)lpTrade);
	memcpy(&TransLastRecvTrade, lpTransTradeItems, lpTransTradeItems->size);		//¹ÞÀº Æ®·¹ÀÌµå µ¥ÀÌÅ¸ ÀÓ½Ã º¹»ç
	return TRUE;
}

//±³È¯Ã¢ ¾ÆÀÌÅÛ ¼Û½Å
int SendTradeItem(DWORD dwSender)
{
	return SendTradeItem(&sTrade, dwSender);
}
//±³È¯Ã¢ ¾ÆÀÌÅÛ ¼ö½Å
int RecvTradeItems(TRANS_TRADEITEMS *lpTransTradeItems)
{
	int res;

	res = RecvTradeItems(lpTransTradeItems, &sTradeRecv);
	cTrade.LoadTradeItemIamge();
	cTrade.CheckTradeButtonOk();

	ItemPickUpFlag = 1;

	if (CheckTrade(&sTradeRecv) == FALSE)
	{
		SendRequestTrade(lpTransTradeItems->dwSender, 3);
		cTrade.CancelTradeItem();
		return FALSE;
	}

	if (sTrade.CheckFlag && !sTradeRecv.CheckFlag)
	{
		sTrade.CheckFlag = 0;
		TradeItemCancelCount++;
		if (TradeItemCancelCount >= 3)
		{
			SendRequestTrade(lpTransTradeItems->dwSender, 3);
			cTrade.CancelTradeItem();
			return FALSE;
		}
		else
		{
			cMessageBox.ShowMessage(MESSAGE_MOVE_TRADE_ITEM);
			SendTradeItem(lpTransTradeItems->dwSender);
		}
	}

	return res;
}
int SendTradeSucessKey(DWORD dwSender)
{
	return SendTradeSucessKey(&sTrade, dwSender);
}
int SendTradeSucessKey(sTRADE *lpTrade, DWORD dwSender)
{
	TRANS_TRADE_ITEMKEY	TransTradeItemKey;
	int cnt;
	int	TradeOpenFlag, CancelFlag;

	if (GAMESOCKET->iDisconnectTime) return FALSE;

	TransTradeItemKey.code = smTRANSCODE_TRADE_ITEMKEY;
	TransTradeItemKey.size = sizeof(TRANS_TRADE_ITEMKEY);
	TransTradeItemKey.dwSender = lpCurPlayer->iID;;
	TransTradeItemKey.dwRecver = dwSender;
	TransTradeItemKey.Money = lpTrade->Money;


	TradeOpenFlag = cTrade.OpenFlag;
	cTrade.OpenFlag = 0;
	CancelFlag = 0;

	for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++)
	{
		if (lpTrade->TradeItem[cnt].bValid)
		{
			TransTradeItemKey.dwItemCode[cnt] = lpTrade->TradeItem[cnt].sItem.sItemID.ToInt();
			TransTradeItemKey.dwItemKey[cnt] = lpTrade->TradeItem[cnt].sItem.iChk1;
			TransTradeItemKey.dwItemSum[cnt] = lpTrade->TradeItem[cnt].sItem.iChk2;

			if (FindInvenItem(lpTrade->TradeItem[cnt].sItem.sItemID.ToInt(), lpTrade->TradeItem[cnt].sItem.iChk1, lpTrade->TradeItem[cnt].sItem.iChk2) != 0)
			{
				CancelFlag = TRUE;
				SendInvenItemError(1, lpTrade->TradeItem[cnt].sItem.sItemID.ToInt(), lpTrade->TradeItem[cnt].sItem.iChk1, lpTrade->TradeItem[cnt].sItem.iChk2);
			}

			if ((TransTradeItemKey.dwItemCode[cnt] & sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
			{
				TransTradeItemKey.dwItemSum[cnt] = lpTrade->TradeItem[cnt].sItem.iPotionCount & 0xFFFF;
				TransTradeItemKey.dwItemSum[cnt] |= (lpTrade->TradeItem[cnt].sItem.iChk2) << 16;
				TransTradeItemKey.dwItemSum[cnt] ^= (TransTradeItemKey.dwItemSum[cnt] >> 16) ^ 0x5cbc;
			}
		}
		else
		{
			TransTradeItemKey.dwItemCode[cnt] = 0;
			TransTradeItemKey.dwItemKey[cnt] = 0;
			TransTradeItemKey.dwItemSum[cnt] = 0;
		}
	}

	cTrade.OpenFlag = TradeOpenFlag;

	if (!CancelFlag)
	{
		SENDPACKETL(&TransTradeItemKey);

		memcpy(&LastTransTradeItemKey, &TransTradeItemKey, sizeof(TRANS_TRADE_ITEMKEY));
		dwLastTransTradeKeyTime = dwPlayTime;
	}

	dwTradeMaskTime = dwPlayTime + 3000;

	return TRUE;
}

int RecvTradeSucessKey(TRANS_TRADE_ITEMKEY *lpTransTradeItemKey, sTRADE *lpTrade)
{
	int cnt;
	sTRADE sChkTrade;
	DWORD	dwChkSum1, dwChkSum2;
	int	ItemFlag;

	dwTradeMaskTime = dwPlayTime + 3000;

	if (TransLastRecvTrade.code)
	{
		DecodeCompress(TransLastRecvTrade.TradeBuff, (BYTE *)&sChkTrade);
		for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++) {
			memcpy(&lpTrade->TradeItem[cnt].sItem, &sChkTrade.TradeItem[cnt].sItem, sizeof(Item));
		}
	}
	//cTrade.LoadTradeItemIamge();

	for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++) {
		if (lpTrade->TradeItem[cnt].bValid) {

			dwChkSum1 = lpTransTradeItemKey->dwItemSum[cnt];
			dwChkSum2 = lpTrade->TradeItem[cnt].sItem.iChk2;
			if ((lpTrade->TradeItem[cnt].sItem.sItemID.ToItemBase()) == (sinPM1&sinITEM_MASK1)) {
				//¹°¾àÀÎ°æ¿ì
				ItemFlag = 1;
				dwChkSum1 = dwChkSum1 >> 16;
				dwChkSum2 = dwChkSum2 & 0xFFFF;
			}
			else
				ItemFlag = 0;

			if (lpTransTradeItemKey->dwItemCode[cnt] == lpTrade->TradeItem[cnt].sItem.sItemID.ToInt() && dwChkSum1 == dwChkSum2) {
				//			lpTransTradeItemKey->dwItemSum[cnt]==lpTrade->TradeItem[cnt].sItem.iChk2 ) {

				lpTrade->TradeItem[cnt].sItem.iChk1 = lpTransTradeItemKey->dwItemKey[cnt];

				//Àß¸øµÈ ¾ÆÀÌÅÛ ¼ö½Å
				if (!lpTrade->TradeItem[cnt].sItem.iChk1)
					lpTrade->TradeItem[cnt].bValid = 0;
				else {
					if (ItemFlag == 1) {
						//¹°¾à ÀçÀÎÁõ
						ReformItem(&lpTrade->TradeItem[cnt].sItem);
					}
				}
			}
			else {
				return FALSE;
			}
		}
		else {
			if (lpTransTradeItemKey->dwItemCode[cnt])
				return FALSE;

		}
	}

	//SendRecordTradeItems( lpTrade );			//±³È¯ ³»¿ë ¼­¹ö¿¡ ±â·Ï

	return TRUE;
}

//¾ÆÀÌÅÛ ±³È¯ ³»¿ë È®ÀÎ
int SendTradeCheckItem(DWORD dwSender)
{

	TRANS_TRADE_CHECKITEM	TransTradeCheckItem;
	int cnt;

	if (GAMESOCKET->iDisconnectTime) return FALSE;

	TransTradeCheckItem.code = smTRANSCODE_TRADE_READYITEM;
	TransTradeCheckItem.size = sizeof(TRANS_TRADE_CHECKITEM);
	TransTradeCheckItem.dwSender = lpCurPlayer->iID;
	TransTradeCheckItem.dwRecver = dwSender;

	if (sTrade.Money) {
		SendSaveMoney();			//µ· ÀúÀå ( º¹»ç¹æÁö )
	}

	for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++) {
		if (sTrade.TradeItem[cnt].bValid) {
			TransTradeCheckItem.dwSendItemCode[cnt] = sTrade.TradeItem[cnt].sItem.sItemID.ToInt();
			TransTradeCheckItem.dwSendItemSum[cnt] = sTrade.TradeItem[cnt].sItem.iChk2;

			//SendSaveThrowItem( &sTrade.TradeItem[cnt].sItem );		//¾ÆÀÌÅÛ º¹»ç ¹æÁö

			//¾ÆÀÌÅÛ ÀÎÁõ È®ÀÎ
			if (CheckItemForm(&sTrade.TradeItem[cnt].sItem) == FALSE)
				return FALSE;		//Àß¸øµÈ ¾ÆÀÌÅÛ 

		}
		else {
			TransTradeCheckItem.dwSendItemCode[cnt] = 0;
			TransTradeCheckItem.dwSendItemSum[cnt] = 0;
		}
	}


	for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++) {
		if (sTradeRecv.TradeItem[cnt].bValid) {
			TransTradeCheckItem.dwRecvItemCode[cnt] = sTradeRecv.TradeItem[cnt].sItem.sItemID.ToInt();
			TransTradeCheckItem.dwRecvItemSum[cnt] = sTradeRecv.TradeItem[cnt].sItem.iChk2;
		}
		else {
			TransTradeCheckItem.dwRecvItemCode[cnt] = 0;
			TransTradeCheckItem.dwRecvItemSum[cnt] = 0;
		}
	}

	SENDPACKETG(&TransTradeCheckItem);

	dwTradeMaskTime = dwPlayTime + 3000;

	return TRUE;
}

//¾ÆÀÌÅÛ ±³È¯ ³»¿ë È®ÀÎ ¼ö½Å
int RecvTradeCheckItem(TRANS_TRADE_CHECKITEM *lpTransTradeCheckItem)
{
	int cnt;

	dwTradeMaskTime = dwPlayTime + 3000;

	if (GAMESOCKET->iDisconnectTime) return FALSE;

	for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++) {
		if (sTrade.TradeItem[cnt].bValid) {
			if (lpTransTradeCheckItem->dwRecvItemCode[cnt] != sTrade.TradeItem[cnt].sItem.sItemID.ToInt() ||
				((lpTransTradeCheckItem->dwRecvItemCode[cnt] & sinITEM_MASK1) != (sinPM1&sinITEM_MASK1) &&
					lpTransTradeCheckItem->dwRecvItemSum[cnt] != sTrade.TradeItem[cnt].sItem.iChk2)) {

				return FALSE;

			}
		}
		else {
			if (lpTransTradeCheckItem->dwRecvItemCode[cnt])
				return FALSE;
		}

		if (sTradeRecv.TradeItem[cnt].bValid) {
			if (lpTransTradeCheckItem->dwSendItemCode[cnt] != sTradeRecv.TradeItem[cnt].sItem.sItemID.ToInt() ||
				((lpTransTradeCheckItem->dwSendItemCode[cnt] & sinITEM_MASK1) != (sinPM1&sinITEM_MASK1) &&
					lpTransTradeCheckItem->dwSendItemSum[cnt] != sTradeRecv.TradeItem[cnt].sItem.iChk2)) {

				return FALSE;

			}
		}
		else {
			if (lpTransTradeCheckItem->dwSendItemCode[cnt])
				return FALSE;
		}
	}

	return TRUE;
}

int SendJoinPartyUser(DWORD dwObjectCode)
{
	smTRANS_COMMAND	TransCommand;

	TransCommand.code = smTRANSCODE_PARTY_JOIN;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = dwObjectCode;
	TransCommand.LParam = 0;
	TransCommand.SParam = 0;

	SENDPACKETG(&TransCommand);

	return 0;
}

int	PartyButton(int Num, int Button)
{
	return 0;
}
int	SetTotalSubMoney(int Money)
{
	TotalSubMoney += Money;

	return TRUE;
}

int	SetTotalAddMoney(int Money)
{
	TotalAddMoney += Money;

	return TRUE;
}

int	SetTotalAddExp(int Exp)
{
	TotalAddExp += Exp;

	return TRUE;
}

int	SetTotalSubExp(int Exp)
{
	TotalSubExp += Exp;

	return TRUE;
}

int	GetTotalMoney()
{
	int m;

	m = sServerMoney[0].InputMoney + sServerMoney[1].InputMoney + sServerMoney[2].InputMoney + WareHouseSubMoney + TotalAddMoney - TotalSubMoney;

	return m;
}

int GetTotalSubExp()
{
	int m;

	m = (sServerExp[0].InputExp + sServerExp[1].InputExp + sServerExp[2].InputExp) - (TotalAddExp - TotalSubExp);

	return m;
}

int GetTotalExp()
{
	int m;

	m = sServerExp[0].InputExp + sServerExp[1].InputExp + sServerExp[2].InputExp + TotalAddExp - TotalSubExp;

	return m;
}

// ±£´æ²Ö¿â
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

	if (!flag && CompSize > (smSOCKBUFF_SIZE - 256))
		return FALSE;

	if (flag && CompSize > (smSOCKBUFF_SIZE - 140))
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

	if (TransWareHouse.size > smSOCKBUFF_SIZE)
		TransWareHouse.size = smSOCKBUFF_SIZE;

	if (SOCKETL)
	{
		SENDPACKETL(&TransWareHouse);

		SaveGameData();
		return TRUE;
	}

	return FALSE;
}
int	SaveWareHouse(sWAREHOUSE *lpWareHouse)
{
	return SaveWareHouse(lpWareHouse, 0);
}
int	LoadWareHouse(TRANS_WAREHOUSE *lpTransWareHouse, sWAREHOUSE *lpWareHouse, int flag)
{
	sWAREHOUSE	WareHouseCheck;
	int cnt;
	DWORD	dwChkSum;
	char	*szComp;

	if (lpTransWareHouse->DataSize == 0)
	{
		ZeroMemory(lpWareHouse, sizeof(sWAREHOUSE));
		return TRUE;
	}

	DecodeCompress((BYTE *)lpTransWareHouse->Data, (BYTE *)&WareHouseCheck);

	dwChkSum = 0;

	szComp = (char *)&WareHouseCheck;

	for (cnt = 0; cnt < sizeof(sWAREHOUSE); cnt++)
		dwChkSum += szComp[cnt] * (cnt + 1);
	if (dwChkSum == lpTransWareHouse->dwChkSum)
	{
		if (!flag && dwLastWareHouseChkSum && dwLastWareHouseChkSum != lpTransWareHouse->dwChkSum && !SETTINGHANDLE->Get().bDebugMode)
			return FALSE;

		memcpy(lpWareHouse, &WareHouseCheck, sizeof(sWAREHOUSE));

		for (cnt = 0; cnt < 100; cnt++)
		{
			if (lpWareHouse->WareHouseItem[cnt].bValid)
			{
				if (!lpWareHouse->WareHouseItem[cnt].sItem.Temp0)
					lpWareHouse->WareHouseItem[cnt].sItem.Temp0 = lpWareHouse->WareHouseItem[cnt].sItem.iChk2 + lpWareHouse->WareHouseItem[cnt].sItem.sItemID.ToInt();

				if (!lpWareHouse->WareHouseItem[cnt].sItem.dwTime)
				{
					lpWareHouse->WareHouseItem[cnt].sItem.dwTime =
						(lpWareHouse->WareHouseItem[cnt].sItem.iChk1 >> 2) ^ (lpWareHouse->WareHouseItem[cnt].sItem.iChk2 << 2);
				}
				if ((lpWareHouse->WareHouseItem[cnt].sItem.sItemID.ToItemType()) == sinSP1)
				{
					if (lpWareHouse->WareHouseItem[cnt].sItem.iPotionCount > 1)
						lpWareHouse->WareHouseItem[cnt].bValid = 0;
				}
				if (DeleteEventItem_TimeOut(&lpWareHouse->WareHouseItem[cnt].sItem) == TRUE)
				{
					lpWareHouse->WareHouseItem[cnt].bValid = 0;

					CHATGAMEHANDLE->AddChatBoxTextEx(CHATCOLOR_Error, "The item was deleted by the item( %s )'s time of validity", lpWareHouse->WareHouseItem[cnt].sItem.szItemName);
				}
			}
		}
		return TRUE;
	}

	return FALSE;
}

int	LoadWareHouse(TRANS_WAREHOUSE *lpTransWareHouse, sWAREHOUSE *lpWareHouse)
{
	return LoadWareHouse(lpTransWareHouse, lpWareHouse, 0);
}
int SendCollectMoney(int Money)
{
	ItemData	sItemMoney;

	memset(&sItemMoney, 0, sizeof(ItemData));
	sItemMoney.sItem.sItemID = sinGG1 | sin01;

	ItemData * pItemData = ITEMHANDLE->GetItemDataByID(sItemMoney.sItem.sItemID.ToInt());

	if (pItemData)
	{
		memcpy(&sItemMoney, pItemData, sizeof(ItemData));
		sItemMoney.sItem.iGold = Money;
		sItemMoney.sItem.eCraftType = ITEMCRAFTTYPE_Event;
		ReformItem(&sItemMoney.sItem);
		if (sinThrowItemToFeild(&sItemMoney))
		{
			AddInvenMoney(-Money);
			return TRUE;
		}
	}

	return FALSE;
}
int PlayerKilling(DWORD dwObjectSerial)
{
	smTRANS_COMMAND	TransCommand;

	TransCommand.code = smTRANSCODE_PLAYERKILLING;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = dwObjectSerial;
	TransCommand.LParam = lpCurPlayer->iID;
	TransCommand.SParam = 0;

	SENDPACKETG(&TransCommand);

	return FALSE;
}
// ¼ÓÔØ³èÎï²Ö¿â
int LoadCaravan(TRANS_CARAVAN *lpTransCaravan, sCARAVAN *lpCaravan, int flag)
{
	sCARAVAN CaravanChk;
	int cnt;
	DWORD	dwChkSum;
	char	*szComp;

	if (lpTransCaravan->DataSize == 0)
	{
		ZeroMemory(lpCaravan, sizeof(sCARAVAN));
		return TRUE;
	}
	DecodeCompress((BYTE *)lpTransCaravan->Data, (BYTE *)&CaravanChk);

	dwChkSum = 0;

	szComp = (char *)&CaravanChk;

	for (cnt = 0; cnt < sizeof(sCARAVAN); cnt++)
		dwChkSum += szComp[cnt] * (cnt + 1);

	if (dwChkSum == lpTransCaravan->dwChkSum)
	{
		if (!flag && cCaravan.dwChkSum && cCaravan.dwChkSum != lpTransCaravan->dwChkSum && !SETTINGHANDLE->Get().bDebugMode)
			return FALSE;

		memcpy(lpCaravan, &CaravanChk, sizeof(sWAREHOUSE));

		for (cnt = 0; cnt < 100; cnt++)
		{
			if (lpCaravan->Item[cnt].bValid)
			{
				if (!lpCaravan->Item[cnt].sItem.Temp0)
					lpCaravan->Item[cnt].sItem.Temp0 = lpCaravan->Item[cnt].sItem.iChk2 + lpCaravan->Item[cnt].sItem.sItemID.ToInt();
				if (!lpCaravan->Item[cnt].sItem.dwTime)
					lpCaravan->Item[cnt].sItem.dwTime = (lpCaravan->Item[cnt].sItem.iChk1 >> 2) ^ (lpCaravan->Item[cnt].sItem.iChk2 << 2);
				if ((lpCaravan->Item[cnt].sItem.sItemID.ToItemType()) == sinSP1)
				{
					if (lpCaravan->Item[cnt].sItem.iPotionCount > 1)
						lpCaravan->Item[cnt].bValid = 0;
				}
				if (DeleteEventItem_TimeOut(&lpCaravan->Item[cnt].sItem) == TRUE)
				{
					lpCaravan->Item[cnt].bValid = 0;

					CHATGAMEHANDLE->AddChatBoxTextEx(CHATCOLOR_Error, "The item was deleted by the item( %s )'s time of validity", lpCaravan->Item[cnt].sItem.szItemName);
				}
			}
		}
		return TRUE;
	}

	return FALSE;
}
// ±£´æ³èÎï²Ö¿â
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

	if (!flag && CompSize > (smSOCKBUFF_SIZE - 256))
		return FALSE;

	if (flag && CompSize > (smSOCKBUFF_SIZE - 140))
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
	if (TransCaravan.size > smSOCKBUFF_SIZE)
		TransCaravan.size = smSOCKBUFF_SIZE;

	if (SOCKETL)
	{
		SENDPACKETL(&TransCaravan);

		SaveGameData();
		return TRUE;
	}
	return FALSE;
}
int SendSelectHopyToServer(int Kind)
{
	smTRANS_COMMAND	smTransCommand;

	smTransCommand.code = smTRANSCODE_CARAVAN_SELECT;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = Kind;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;
	smTransCommand.EParam = 0;

	SENDPACKETG(&smTransCommand);

	return FALSE;
}
//·¢ËÍºÏ³ÉÎïÆ·µ½·þÎñÆ÷
int SendCraftItemToServer(void *lpsCraftItem_Send)
{
	sCRAFTITEM_SERVER	*lpCraftItem_Send = (sCRAFTITEM_SERVER *)lpsCraftItem_Send;

	lpCraftItem_Send->size = sizeof(sCRAFTITEM_SERVER);
	lpCraftItem_Send->code = smTRANSCODE_CRAFTITEM;

	SENDPACKETL(lpCraftItem_Send);

	return FALSE;
}

//·¢ËÍWINGÎïÆ·µ½·þÎñÆ÷
int SendWingItemToServer(void *lpsCraftItem_Send)
{
	sCRAFTITEM_SERVER	*lpCraftItem_Send = (sCRAFTITEM_SERVER *)lpsCraftItem_Send;

	lpCraftItem_Send->size = sizeof(sCRAFTITEM_SERVER);
	lpCraftItem_Send->code = smTRANSCODE_WINGITEM;

	SENDPACKETL(lpCraftItem_Send);

	return FALSE;
}

// ¶ÍÔìÎïÆ··¢ËÍµ½·þÎñÆ÷
int SendAgingItemToServer(void *lpsCraftItem_Send)
{
	sCRAFTITEM_SERVER	*lpCraftItem_Send = (sCRAFTITEM_SERVER *)lpsCraftItem_Send;

	lpCraftItem_Send->size = sizeof(sCRAFTITEM_SERVER);
	lpCraftItem_Send->code = smTRANSCODE_AGINGITEM;

	SENDPACKETL(lpCraftItem_Send);

	return FALSE;
}
// ÊôÐÔÏµÍ³·¢ËÍµ½·þÎñÆ÷
int SendElementItemToServer(void *lpsItem_Send)
{
	ELEMENT_ITEM_SERVER *lpItem_Send = (ELEMENT_ITEM_SERVER *)lpsItem_Send;

	lpItem_Send->size = sizeof(ELEMENT_ITEM_SERVER);
	lpItem_Send->code = smTRANSCODE_ELEMENTITEM;

	SENDPACKETL(lpItem_Send);

	return FALSE;
}
// ´ò¿×ÏµÍ³·¢ËÍµ½·þÎñÆ÷
int SendSocketItemToServer(void *lpsItem_Send)
{
	SOCKET_ITEM_SERVER *lpItem_Send = (SOCKET_ITEM_SERVER *)lpsItem_Send;

	lpItem_Send->size = sizeof(SOCKET_ITEM_SERVER);
	lpItem_Send->code = smTRANSCODE_SOCKETITEM;

	SENDPACKETL(lpItem_Send);

	return FALSE;
}

//¸µÅ©ÄÚ¾î µî·Ï º¸³¿
int SendLinkCoreToServer(Item *lpItem)
{
	TRANS_ITEMINFO	TransItemInfo;
	int len;

	TransItemInfo.size = sizeof(TRANS_ITEMINFO);
	TransItemInfo.code = smTRANSCODE_MAKE_LINKCORE;
	memcpy(&TransItemInfo.sItem, lpItem, sizeof(Item));

	TransItemInfo.x = lpCurPlayer->pX;
	TransItemInfo.y = lpCurPlayer->pY;
	TransItemInfo.z = lpCurPlayer->pZ;

	TransItemInfo.dwSeCode[0] = 0;
	TransItemInfo.dwSeCode[1] = 0;
	TransItemInfo.dwSeCode[2] = 0;
	TransItemInfo.dwSeCode[3] = 0;

	len = lstrlen(lpItem->szItemName);
	if (lpItem->szItemName[len + 1])
	{
		TransItemInfo.code = smTRANSCODE_USE_LINKCORE;

		if (lpCurPlayer->iLoadedMapIndex >= 0 && STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapType == MAPTYPE_ChessRoom)
			return FALSE;

		SENDPACKETG(&TransItemInfo);

		return 1;
	}

	SENDPACKETL(&TransItemInfo);

	return 1;
}

int SucessLinkCore(smTRANS_COMMAND_EX *lpTransCommandEx)
{
	int cnt;

	Item	*lpItem;

	lpItem = FindInvenItem(lpTransCommandEx->WxParam, lpTransCommandEx->LxParam, lpTransCommandEx->SxParam);

	if (lpItem)
	{
		SendUseItemCodeToServer(lpItem);
		cInvenTory.DeleteInvenItemToServer(lpTransCommandEx->WxParam, lpTransCommandEx->LxParam, lpTransCommandEx->SxParam);
		ResetInvenItemCode();

		if (FindInvenItem(lpTransCommandEx->WxParam, lpTransCommandEx->LxParam, lpTransCommandEx->SxParam) != 0)
			return FALSE;
	}
	else
		return FALSE;


	CloseEachPlayer();

	GAMEMAP->WarpMap((EMapID)lpTransCommandEx->EParam, lpTransCommandEx->WParam, lpTransCommandEx->SParam);

	lpCurPlayer->SetPosi(lpTransCommandEx->WParam, lpTransCommandEx->LParam, lpTransCommandEx->SParam, 0, 0, 0);

	TraceCameraPosi.x = lpCurPlayer->pX;
	TraceCameraPosi.y = lpCurPlayer->pY;
	TraceCameraPosi.z = lpCurPlayer->pZ;
	TraceTargetPosi.x = lpCurPlayer->pX;
	TraceTargetPosi.y = lpCurPlayer->pY;
	TraceTargetPosi.z = lpCurPlayer->pZ;

	lpCurPlayer->iLoadedMapIndex = -1;
	if (smGameStage[0])
	{
		cnt = smGameStage[0]->GetFloorHeight(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, lpCurPlayer->Pattern->SizeHeight);
		lpCurPlayer->iLoadedMapIndex = 0;
	}
	if (cnt == CLIP_OUT && smGameStage[1])
		lpCurPlayer->iLoadedMapIndex = 1;

	StartEffect(lpCurPlayer->pX, lpCurPlayer->pY + 48 * fONE, lpCurPlayer->pZ, EFFECT_RETURN1);
	SkillPlaySound(SKILL_SOUND_LEARN, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
	RestartPlayCount = 350;

	return TRUE;
}
int SendAgingUpgradeItemToServer(Item *lpItem)
{
	TRANS_ITEMINFO	TransItemInfo;

	if (TransAgingItemFlag)
		return FALSE;

	TransItemInfo.code = smTRANSCODE_AGING_UPGRADE;
	TransItemInfo.size = sizeof(TRANS_ITEMINFO);
	TransItemInfo.x = 0;
	TransItemInfo.y = 0;
	TransItemInfo.z = 0;
	memcpy(&TransItemInfo.sItem, lpItem, sizeof(Item));

	SENDPACKETL(&TransItemInfo);

	TransAgingItemFlag = TRUE;

	return FALSE;
}
int ClearInvenPotionCount()
{
	int cnt;

	for (cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if (cInvenTory.InvenItem[cnt].bValid && (cInvenTory.InvenItem[cnt].sItem.sItemID.ToItemBase()) == (sinPM1&sinITEM_MASK1))
			cInvenTory.InvenItem[cnt].sItem.iPotionCount = 1;
	}

	for (cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if (cInvenTory.InvenItemTemp[cnt].bValid && (cInvenTory.InvenItemTemp[cnt].sItem.sItemID.ToItemBase()) == (sinPM1&sinITEM_MASK1))
			cInvenTory.InvenItemTemp[cnt].sItem.iPotionCount = 1;
	}

	if (cTrade.OpenFlag)
	{
		for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++)
		{
			if (sTrade.TradeItem[cnt].bValid && (sTrade.TradeItem[cnt].sItem.sItemID.ToItemBase()) == (sinPM1&sinITEM_MASK1))
				sTrade.TradeItem[cnt].sItem.iPotionCount = 1;
		}
	}

	if (MouseItem.bValid && (MouseItem.sItem.sItemID.ToItemBase()) == (sinPM1&sinITEM_MASK1))
		MouseItem.sItem.iPotionCount = 1;

	cInvenTory.ReFormPotionNum();

	SaveGameData();

	return TRUE;
}
Item *FindItemFromCode(DWORD dwItemCode)
{
	int cnt;

	for (cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if (cInvenTory.InvenItem[cnt].bValid && cInvenTory.InvenItem[cnt].sItem.sItemID.ToInt() == dwItemCode)
			return &cInvenTory.InvenItem[cnt].sItem;
	}
	for (cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if (cInvenTory.InvenItemTemp[cnt].bValid && cInvenTory.InvenItemTemp[cnt].sItem.sItemID.ToInt() == dwItemCode)
			return &cInvenTory.InvenItemTemp[cnt].sItem;
	}

	return NULL;
}



DWORD	dwLastCheckItemTime = 0;


int	SendCheckItemToServer(Item *lpItem)
{
	TRANS_ITEMINFO	TransItemInfo;

	if ((dwLastCheckItemTime + 10000) > dwPlayTime)
		return FALSE;

	TransItemInfo.code = smTRANSCODE_CHECKITEM;
	TransItemInfo.size = sizeof(TRANS_ITEMINFO);

	memcpy(&TransItemInfo.sItem, lpItem, sizeof(Item));

	TransItemInfo.x = 0;
	TransItemInfo.y = 0;
	TransItemInfo.z = 0;

	SENDPACKETL(&TransItemInfo);

	dwLastCheckItemTime = dwPlayTime;

	return TRUE;
}
int RecvCheckItemFromServer(TRANS_ITEM_CODE *lpTransItemCode)
{
	switch (lpTransItemCode->code)
	{
	case smTRANSCODE_CHECKITEM:
		break;
	case smTRANSCODE_ERRORITEM:
		cInvenTory.DeleteInvenItemToServer(lpTransItemCode->dwItemCode, lpTransItemCode->dwHead, lpTransItemCode->dwChkSum);

		if (FindInvenItem(lpTransItemCode->dwItemCode, lpTransItemCode->dwHead, lpTransItemCode->dwChkSum) == 0)
		{
			SendInvenItemError(0, lpTransItemCode->dwItemCode, lpTransItemCode->dwHead, lpTransItemCode->dwChkSum);
			ResetInvenItemCode();
		}
		break;
	case smTRANSCODE_CLEARPOTION:
		ClearInvenPotionCount();
		break;
	}

	return TRUE;
}
int	SellItemToServer(Item *lpItem, int Count)
{

	TRANS_ITEMINFO	TransItemInfo;

	TransItemInfo.code = smTRANSCODE_SHOP_SELLITEM;
	TransItemInfo.size = sizeof(TRANS_ITEMINFO);

	memcpy(&TransItemInfo.sItem, lpItem, sizeof(Item));

	TransItemInfo.x = Count;
	TransItemInfo.y = lpCurPlayer->sCharacterData.iGold;
	TransItemInfo.z = 0;

	SENDPACKETL(&TransItemInfo);

	return FALSE;
}





int Chk_InventPosCount = 1;
DWORD	dwCheckInvenItemTime = 0;


int CheckInvenItemToServer()
{
	int cnt;

	if (dwCheckInvenItemTime > dwPlayTime)
		return TRUE;

	for (cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if (cInvenTory.InvenItem[cnt].iItemSlot == Chk_InventPosCount)
			SendCheckItemToServer(&cInvenTory.InvenItem[cnt].sItem);
	}

	for (cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if (cInvenTory.InvenItemTemp[cnt].iItemSlot == Chk_InventPosCount)
			SendCheckItemToServer(&cInvenTory.InvenItemTemp[cnt].sItem);
	}

	Chk_InventPosCount++;
	dwCheckInvenItemTime = dwPlayTime + 55 * 1000;

	if (Chk_InventPosCount >= 11 || Chk_InventPosCount < 1)
		Chk_InventPosCount = 1;

	return TRUE;
}

HANDLE	hTimeCheckThread = 0;
int		TimeCheckCounter;

DWORD WINAPI TimeCheckThread(void *pInfo)
{
	HANDLE	hThread;
	DWORD	dwTime;
	DWORD	dwLastTime;
	int		cnt;

	hThread = GetCurrentThread();
	dwTime = GetCurrentTime();
	dwLastTime = dwTime;
	TimeCheckCounter = 0;

	while (1) {
		dwTime = GetCurrentTime();
		cnt = dwTime - dwLastTime;
		if (cnt > PlayTimerMax) PlayTimerMax = cnt;
		dwLastTime = dwTime;
		TimeCheckCounter++;
		Sleep(800);
	}

	ExitThread(TRUE);
	return TRUE;
}
int OpenTimeCheckThread()
{
	DWORD	dwTimeCheckThreadID;

	if (!hTimeCheckThread)
		hTimeCheckThread = CreateThread(NULL, 0, TimeCheckThread, 0, 0, &dwTimeCheckThreadID);

	return TRUE;
}

int	PlayTimerMax_SendingCount = 0;

int SendPlayTimerMax()
{
	smTRANS_COMMAND	smTransCommand;

	if (PlayTimerMax >= 10000 || (PlayTimerMax_SendingCount & 0x7) == 0) {

		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.code = smTRANSCODE_PROCESS_TIMEMAX;
		smTransCommand.WParam = PlayTimerMax;
		smTransCommand.LParam = TimeCheckCounter;
		smTransCommand.SParam = 0;
		smTransCommand.EParam = 0;

		SENDPACKETL(&smTransCommand);

		PlayTimerMax = 0;
	}

	PlayTimerMax_SendingCount++;

	return TRUE;
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
	{ (DWORD)funcCheckMemSum << 1				,	512		},
	{ (DWORD)Check_PlaySubReleaseFunc << 1	,	512		},
	{ (DWORD)PlayPat3D << 1					,	2048	},
	{ (DWORD)Check_CodeSafe << 1				,	1024	},
	{ (DWORD)AddExp << 1						,	512		},
	{ (DWORD)sinSetLife << 1					,	512		},

	{ (DWORD)E_Shield_BlockRate << 1			,	((Meteo_UseMana - E_Shield_BlockRate) + 10) },

	{ (DWORD)Code_VRamBuffOpen << 1			,	3600	},
	{ 0,0 }
};

int	SendClientFuncPos()
{
	TRANS_CLIENT_FUNPOS	TransClientFuncPos;
	int cnt;

	ZeroMemory(&TransClientFuncPos, sizeof(TRANS_CLIENT_FUNPOS));

	TransClientFuncPos.code = smTRANSCODE_CLIENT_FUNCPOS;
	TransClientFuncPos.size = sizeof(TRANS_CLIENT_FUNPOS);
	TransClientFuncPos.ClientVersion = GAME_VERSION;

	cnt = 0;
	TransClientFuncPos.dwFunc_CheckMemSum = dwFuncList[cnt][0] >> 1;
	TransClientFuncPos.dwFuncValue[cnt].dwFunc = dwFuncList[cnt][0] >> 1;
	TransClientFuncPos.dwFuncValue[cnt].dwLen = dwFuncList[cnt][1];
	TransClientFuncPos.dwFuncValue[cnt].dwChkSum = funcCheckMemSum(TransClientFuncPos.dwFuncValue[cnt].dwFunc, TransClientFuncPos.dwFuncValue[cnt].dwLen);

	while (1)
	{
		if (dwFuncList[cnt][0] == 0)
			break;
		if (cnt >= dwFUNC_VALUE_MAX)
			break;

		TransClientFuncPos.dwFuncValue[cnt].dwFunc = dwFuncList[cnt][0] >> 1;
		TransClientFuncPos.dwFuncValue[cnt].dwLen = dwFuncList[cnt][1];
		TransClientFuncPos.dwFuncValue[cnt].dwChkSum = funcCheckMemSum(TransClientFuncPos.dwFuncValue[cnt].dwFunc, TransClientFuncPos.dwFuncValue[cnt].dwLen);

		cnt++;
	}

	TransClientFuncPos.FuncCount = cnt;

	SENDPACKETL(&TransClientFuncPos);

	return FALSE;
}

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
int CheckRecvTrnsItemQue()
{
	int cnt, mCnt;

	for (cnt = RecvTransItemQue_Pop; cnt < RecvTransItemQue_Push; cnt++)
	{
		mCnt = cnt & RECV_TRANSITEM_QUE_MASK;
		if (Recv_TransItemInfo_Que[mCnt].sItem.sItemID.ToInt())
			return FALSE;
	}

	return TRUE;
}

//»ç¿ëÇÑ ¾ÆÀÌÅÛ ÄÚµå ¼­¹ö·Î º¸³¿
int SendUseItemCodeToServer(Item *lpItem)
{
	smTRANS_COMMAND_EX	smTransCommandEx;

	smTransCommandEx.code = smTRANSCODE_USEITEM_CODE;
	smTransCommandEx.size = sizeof(smTRANS_COMMAND);
	smTransCommandEx.WParam = lpItem->sItemID.ToInt();
	smTransCommandEx.LParam = lpItem->iChk1;
	smTransCommandEx.SParam = lpItem->iChk2;
	smTransCommandEx.EParam = lpItem->iPotionCount;

	smTransCommandEx.WxParam = 0;
	smTransCommandEx.LxParam = 0;
	smTransCommandEx.SxParam = 0;
	smTransCommandEx.ExParam = 0;

	SENDPACKETL(&smTransCommandEx);

	return FALSE;
}

//ÁÖº¯ Ä³¸¯ÅÍ¿ë ÀÌº¥Æ® ¸í·É ÄÚµå
int RecvCommandUser(smTRANS_COMMAND_EX *lpTransCommandEx)
{
	Unit *lpChar;
	Unit *lpChar2;

	switch (lpTransCommandEx->WParam)
	{
	case smCOMMNAD_USER_WARP:
		//¿öÇÁ ÀÌÆåÆ® Ç¥½Ã
		StartEffect(lpTransCommandEx->LParam, lpTransCommandEx->SParam, lpTransCommandEx->EParam, EFFECT_RETURN1);
		SkillPlaySound(SKILL_SOUND_LEARN, lpTransCommandEx->LParam, lpTransCommandEx->SParam, lpTransCommandEx->EParam);			//½ºÅ³ È¿°úÀ½
		break;


	case smCOMMNAD_USER_AGINGUP:
		//ÀÚµ¿ ÇÃ·¹ÀÌ¾î¸¦ Ã£´Â´Ù
		lpChar = FindChrPlayer(lpTransCommandEx->WxParam);
		if (lpChar) {
			StartEffect(lpChar->pX, lpChar->pY, lpChar->pZ, EFFECT_AGING);
			esPlaySound(7, GetDistVolume(lpChar->pX, lpChar->pY, lpChar->pZ), 1600);	//»ç¿îµå ¿¬ÁÖ
		}
		break;

	case smCOMMNAD_USER_HOLY_INCANTATION:
		lpChar = FindChrPlayer(lpTransCommandEx->LParam);
		if (lpChar) {
			AssaParticle_HolyIncantationPart(lpChar, lpTransCommandEx->SParam);
		}
		break;

	case smCOMMNAD_USER_RESURRECTION:
		lpChar = FindChrPlayer(lpTransCommandEx->LParam);
		if (lpChar) {
			AssaParticle_ResurrectionPart(lpChar);
		}
		break;

	case smCOMMNAD_USER_FORCEORB:
		/*lpChar = FindChrPlayer( lpTransCommandEx->WxParam );
		if ( lpChar )
		{
			StartSkill( lpChar->pX,lpChar->pY,lpChar->pZ, 0,0,0, SKILL_UP1 );
			SkillPlaySound( SKILL_SOUND_LEARN , lpChar->pX,lpChar->pY,lpChar->pZ );
		}*/
		break;

	case smCOMMNAD_USER_VALENTO:
		//¹ß·»Åä ¼Ò¿ï¼­Ä¿ ÀÌÆåÆ®
		lpChar = FindChrPlayer(lpTransCommandEx->LParam);
		lpChar2 = FindChrPlayer(lpTransCommandEx->SParam);
		if (lpChar && lpChar2) {
			sinSkillEffect_Soul_Sucker(lpChar, lpChar2);
		}
		break;

	case smCOMMNAD_USER_FIREFLOWER:
		lpChar = FindChrPlayer(lpTransCommandEx->WxParam);
		if (lpChar && lpChar != lpCurPlayer) {
			DWORD	dwTable = GetTableNum(lpTransCommandEx->LParam);
			AddTimeEffect(SKILL_EFFECT_FIREFLOWER, dwPlayTime + 1000, (dwTable >> 24) & 0xFF, 0, 0, lpChar);
			AddTimeEffect(SKILL_EFFECT_FIREFLOWER, dwPlayTime + 1500, (dwTable >> 16) & 0xFF, 0, 0, lpChar);
			AddTimeEffect(SKILL_EFFECT_FIREFLOWER, dwPlayTime + 2000, (dwTable >> 8) & 0xFF, 0, 0, lpChar);
			AddTimeEffect(SKILL_EFFECT_FIREFLOWER, dwPlayTime + 2500, dwTable & 0xFF, 0, 0, lpChar);
		}
		break;

	}

	return TRUE;
}
int	SendCommandUser(int wParam, int lParam, int sParam, int eParam)
{
	smTRANS_COMMAND_EX	smTransCommandEx;

	smTransCommandEx.code = smTRANSCODE_COMMAND_USER;
	smTransCommandEx.size = sizeof(smTRANS_COMMAND_EX);
	smTransCommandEx.WParam = wParam;
	smTransCommandEx.LParam = lParam;
	smTransCommandEx.SParam = sParam;
	smTransCommandEx.EParam = eParam;

	smTransCommandEx.WxParam = lpCurPlayer->iID;
	smTransCommandEx.LxParam = 0;
	smTransCommandEx.SxParam = 0;
	smTransCommandEx.ExParam = 0;

	SENDPACKETG(&smTransCommandEx);

	return FALSE;
}

//Áö¿ª¼­¹ö¿¡ ¸í·É ÄÚµå Àü¼Û
int	SendCommand_AreaServer(DWORD dwCode, int wParam, int lParam, int sParam, int eParam)
{
	smTRANS_COMMAND	smTransCommand;

	smTransCommand.code = dwCode;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = wParam;
	smTransCommand.LParam = lParam;
	smTransCommand.SParam = sParam;
	smTransCommand.EParam = eParam;

	SENDPACKETG(&smTransCommand);

	return FALSE;
}
int	SendCommand_DataServer(DWORD dwCode, int wParam, int lParam, int sParam, int eParam)
{
	smTRANS_COMMAND	smTransCommand;

	smTransCommand.code = dwCode;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = wParam;
	smTransCommand.LParam = lParam;
	smTransCommand.SParam = sParam;
	smTransCommand.EParam = eParam;

	SENDPACKETL(&smTransCommand);

	return FALSE;
}

struct	sDAMAGE_RECORD
{
	int	Damage;
	int	Count;
};

sDAMAGE_RECORD	sRecvDamage[3];
sDAMAGE_RECORD	sSendDamage[3];


int	Init_RecordDamage()
{
	ZeroMemory(sRecvDamage, sizeof(sDAMAGE_RECORD) * 3);
	ZeroMemory(sSendDamage, sizeof(sDAMAGE_RECORD) * 3);

	return TRUE;
}

int	Record_RecvDamage(SocketData * pcSocketData, int Damage)
{
	smTRANS_COMMAND	smTransCommand;

	if (SOCKETG == pcSocketData) {
		sRecvDamage[0].Damage -= Damage;
		sRecvDamage[0].Count--;

		if ((sRecvDamage[0].Count & 0x1FF) == 0) 
		{
			smTransCommand.code = smTRANSCODE_REC_DAMAGEDATA;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.WParam = sRecvDamage[0].Count;
			smTransCommand.LParam = sRecvDamage[0].Damage;
			smTransCommand.SParam = sSendDamage[0].Count;
			smTransCommand.EParam = sSendDamage[0].Damage;

			SENDPACKETG(&smTransCommand);
		}
	}
	return TRUE;
}

int	SendPartySkillToServer(DWORD dwSkillCode, int SkillLevel, int Around, int wParam, int lParam, int sParam, int eParam)
{
	int x, y, z, dist;
	int cnt;
	int PartyCount;
	TRANS_PARTY_SKILL	TransPartySkill;

	TransPartySkill.code = smTRANSCODE_PARTY_SKILL;
	TransPartySkill.dwSkillCode = dwSkillCode;
	TransPartySkill.wParam = wParam;
	TransPartySkill.lParam = lParam;
	TransPartySkill.sParam = sParam;
	TransPartySkill.eParam = eParam;

	PartyCount = 0;

	TransPartySkill.dwPartyUser[PartyCount++] = lpCurPlayer->iID;

	for (cnt = 0; cnt < MAX_UNITS; cnt++)
	{
		if (chrOtherPlayer[cnt].bActive && chrOtherPlayer[cnt].iID && chrOtherPlayer[cnt].dwExclusiveNum)
		{
			x = (lpCurPlayer->pX - chrOtherPlayer[cnt].pX) >> FLOATNS;
			y = (lpCurPlayer->pY - chrOtherPlayer[cnt].pY) >> FLOATNS;
			z = (lpCurPlayer->pZ - chrOtherPlayer[cnt].pZ) >> FLOATNS;
			dist = x * x + y * y + z * z;
			if (dist < (Around*Around))
				TransPartySkill.dwPartyUser[PartyCount++] = chrOtherPlayer[cnt].iID;
		}
	}

	TransPartySkill.PartyCount = PartyCount;
	TransPartySkill.Point = SkillLevel;
	TransPartySkill.size = sizeof(TRANS_PARTY_SKILL) - (8 - PartyCount) * 4;

	SENDPACKETG(&TransPartySkill);

	return TRUE;
}

//È¡ÏûÊ±¼ä¼¼ÄÜ
int SendCancelSkillToServer(DWORD dwSkillCode, int lParam, int sParam, int eParam)
{
	smTRANS_COMMAND smTransCommand;

	smTransCommand.code = smTRANSCODE_CANCEL_SKILL;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = dwSkillCode;
	smTransCommand.LParam = lParam;
	smTransCommand.SParam = sParam;
	smTransCommand.EParam = eParam;

	SENDPACKETG(&smTransCommand);

	return FALSE;
}

//¸üÐÂ¼¼ÄÜ
int SendUpdateSkillToServer(DWORD dwSkillCode, int lParam, int sParam, int eParam)
{
	smTRANS_COMMAND smTransCommand;

	smTransCommand.code = smTRANSCODE_UPDATEL_SKILL;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = dwSkillCode;
	smTransCommand.LParam = lParam;
	smTransCommand.SParam = sParam;
	smTransCommand.EParam = eParam;

	SENDPACKETG(&smTransCommand);

	return FALSE;
}
//¸üÐÂ¼¼ÄÜ
int SendCancelCrystalToServer(DWORD dwSkillCode, int lParam, int sParam, int eParam)
{
	smTRANS_COMMAND smTransCommand;

	smTransCommand.code = smTRANSCODE_CRYSTAL_ORB;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = dwSkillCode;
	smTransCommand.LParam = lParam;
	smTransCommand.SParam = sParam;
	smTransCommand.EParam = eParam;

	SENDPACKETG(&smTransCommand);

	return TRUE;
}
int SendDisplayDamgeToServer(int Damge, DWORD dwObjectSerial, int AttackCritical, int Element)
{
	smTRANS_COMMAND smTransCommand;

	smTransCommand.code = smTRANSCODE_DISPLAYDAMGE;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = Damge;
	smTransCommand.LParam = dwObjectSerial;
	smTransCommand.SParam = AttackCritical;
	smTransCommand.EParam = Element;

	SENDPACKETG(&smTransCommand);

	return TRUE;
}
// È¡Ïû´óÍ·Ò©Ë®
int CancelBigHeadToFunction()
{
	ChangeBigHeadMode(0);
	StartSkill(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, SKILL_UP1);
	SkillPlaySound(SKILL_SOUND_LEARN, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);

	int i = PlayerArmor;
	int j = PlayerArmorFlag;

	PlayerArmor = -1;
	PlayerArmorFlag = -1;
	SetPlayerArmor(i, j);

	if (RestartPlayCount < 350)
		RestartPlayCount = 350;

	for (i = 0; i < SINUPKEEPITEM_MAX; i++)
	{
		if (chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::BIG_HEAD ||
			chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::BIG_GIRAFFEHAT ||
			chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::BIG_MAGICIANHAT ||
			chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::BIG_WITCHHAT ||
			chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::BIG_MASKEDMAN ||
			chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::BIG_MASKEDWOMAN ||
			chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::BIG_PUMPKINHAT ||
			chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::BIG_SHEEPHAT ||
			chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::BIG_SOCCERHAT ||
			chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::BIG_GREENXMASHAT ||
			chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::BIG_REDXMASHAT ||
			chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::BIG_EASTER ||
			chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::BIG_BIRTHDAY ||
			chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::BIG_BLUEXMASHAT)
		{
			chaPremiumitem.UpKeepItem[i].IconTime[0] = chaPremiumitem.UpKeepItem[i].IconTime[1];
			chaPremiumitem.m_BigHeadTime = 0;
			cInvenTory.SetItemToChar();
			break;
		}
	}

	return TRUE;
}
// ÉèÖÃÁ¦Á¿Ê¯Í·
int SetForceOrbFunction(DWORD Code, int Time)
{
	int cnt;

	sSKILL TempSkill;

	if (Time > 0)
	{
		if (cSkill.SearchContiueSkill(SKILL_FORCE_ORB) == FALSE)
		{
			if ((Code & sinITEM_MASK2) == sinFO1)
			{
				cnt = (Code&sinITEM_MASK3) >> 8;

				cnt--;

				if (cnt >= 0 && cnt < 16)
				{
					ZeroMemory(&TempSkill, sizeof(sSKILL));

					char *Path = "image\\Sinimage\\skill\\ForceOrb\\FOS_0%d.tga";
					char szBuff[128];

					if (!MatForceOrb[cnt])
					{
						wsprintf(szBuff, Path, cnt + 1);
						MatForceOrb[cnt] = CreateTextureMaterial(szBuff, 0, 0, 0, SMMAT_BLEND_ALPHA);
						ReadTextures();
					}

					TempSkill.CODE = SKILL_FORCE_ORB;
					TempSkill.Point = cnt + 1;
					TempSkill.UseTime = Time;
					TempSkill.MatIcon = MatForceOrb[cnt];

					sinContinueSkillSet(&TempSkill);

					lpCurPlayer->dwForceOrbCode = Code;
					lpCurPlayer->dwForceOrbTime = dwPlayTime + Time * 1000;

					AssaParticle_ShelltomWeapon(lpCurPlayer, Time * 70, cnt);

					StartSkill(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, SKILL_UP1);
					SkillPlaySound(SKILL_SOUND_LEARN, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);

					cInvenTory.SetItemToChar();

					return TRUE;
				}
			}
		}
	}
	else
	{
		if (cSkill.SearchContiueSkill(SKILL_FORCE_ORB))
		{
			cSkill.CancelContinueSkill(SKILL_FORCE_ORB);

			lpCurPlayer->dwForceOrbCode = NULL;
			lpCurPlayer->dwForceOrbTime = NULL;

			StartSkill(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, SKILL_UP1);
			SkillPlaySound(SKILL_SOUND_LEARN, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);

			AssaParticle_ShelltomWeapon(lpCurPlayer, 5, 0);

			cInvenTory.SetItemToChar();

			return TRUE;
		}
	}

	return FALSE;
}
// Ê±¼ä¼¼ÄÜ
int SendProcessSKillToServer(DWORD dwSkillCode, int point, int Param1, int Param2)
{
	smTRANS_COMMAND smTransCommand;

	smTransCommand.code = smTRANSCODE_PROCESS_SKILL2;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = dwSkillCode | (point << 8);
	smTransCommand.LParam = lpCurPlayer->iID;
	smTransCommand.SParam = Param1;
	smTransCommand.EParam = Param2;

	smTransCommand.LParam = dm_GetCommandChkSum(&smTransCommand, lpCurPlayer->iID);

	SENDPACKETG(&smTransCommand);

	return FALSE;
}
int SendWareHouseMoneyToServer(int Money, BOOL Flag)
{
	smTRANS_COMMAND smTransCommand;

	ZeroMemory(&smTransCommand, sizeof(smTRANS_COMMAND));
	if (cWareHouse.OpenFlag)
	{
		smTransCommand.code = smTRANSCODE_WAREHOUSEMONEY;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = Money;
		smTransCommand.LParam = Flag;

		SENDPACKETL(&smTransCommand);
	}
	return FALSE;
}
//À´×Ô·þÎñÆ÷¶ËµÄ×é¶Ó¼¼ÄÜ
int RecvPartySkillFromServer(TRANS_PARTY_SKILL *lpTransPartySkill)
{
	int cnt, cnt2, cnt3;
	int time;
	int flag;
	int AttackSkil;


	int JobCode = lpTransPartySkill->eParam;

	int SkillCode = lpTransPartySkill->dwSkillCode & 0xFF;

	int point = lpTransPartySkill->Point;

	if (point < 1 || point > 10)
		return FALSE;

	switch (JobCode)
	{
	case CHARACTERCLASS_Mechanician:
		switch (SkillCode)
		{
			// Õ½Éñ×£¸£
		case SKILL_PLAY_P_ENHENCE:
			time = P_Enhence_Time[point - 1];
			for (cnt = 1; cnt < lpTransPartySkill->PartyCount; cnt++)
			{
				if (lpCurPlayer->iID == lpTransPartySkill->dwPartyUser[cnt])
				{
					if (cSkill.SearchContiueSkillIndex(SKILL_P_ENHENCE) == NULL)
					{
						AssaParticle_EnhenceStart(lpCurPlayer);
						AssaParticle_EnhenceEffect(lpCurPlayer, time);

						lpCurPlayer->dwP_Enhence_Time = dwPlayTime + time * 1000;

						sSKILL sSkill;
						ZeroMemory(&sSkill, sizeof(sSKILL));
						sSkill.CODE = SKILL_P_ENHENCE;
						sSkill.UseTime = time;
						sSkill.Flag = TRUE;
						sSkill.Point = point;
						sinContinueSkillSet(&sSkill);
					}
					else
					{
						for (cnt2 = 0; cnt2 < MAX_UNITS; cnt2++)
						{
							if (chrOtherPlayer[cnt2].bActive && chrOtherPlayer[cnt2].iID == lpTransPartySkill->dwPartyUser[cnt])
							{
								AssaParticle_EnhenceStart(&chrOtherPlayer[cnt2]);
								AssaParticle_EnhenceEffect(&chrOtherPlayer[cnt2], time);
							}
						}
					}
				}
			}
			break;
		}
		break;
	case CHARACTERCLASS_Knight:
		switch (SkillCode)
		{
			//ÉñÁ¦ÖØ»÷
		case SKILL_PLAY_HOLY_VALOR:
			time = Holy_Valor_Time[point - 1];
			for (cnt = 1; cnt < lpTransPartySkill->PartyCount; cnt++)
			{
				if (lpCurPlayer->iID == lpTransPartySkill->dwPartyUser[cnt])
				{
					flag = 0;

					for (cnt3 = 0; cnt3 < SIN_MAX_SKILL_LIST; cnt3++)
					{
						if (ContinueSkill[cnt].Flag)
						{
							if (ContinueSkill[cnt].CODE == SKILL_DRASTIC_SPIRIT || ContinueSkill[cnt].CODE == SKILL_HOLY_BODY)
								flag++;
						}
					}
					if (flag)
						SendCancelSkillToServer(lpTransPartySkill->dwSkillCode, 0, 0, 0);
					else
					{
						if (AssaParticle_HolyValorIsUse(lpCurPlayer) == FALSE)
						{
							AssaParticle_HolyValor_Member(lpCurPlayer, time);
							lpCurPlayer->dwHoly_Valor_Time = dwPlayTime + time * 1000;
						}

						if (cSkill.SearchContiueSkillIndex(SKILL_HOLY_VALOR) == NULL)
						{
							sSKILL sSkill;
							ZeroMemory(&sSkill, sizeof(sSKILL));
							sSkill.CODE = SKILL_HOLY_VALOR;
							sSkill.UseTime = time;
							sSkill.Flag = TRUE;
							sSkill.Point = point;
							sinContinueSkillSet(&sSkill);
						}
					}
				}
				else
				{
					for (cnt2 = 0; cnt2 < MAX_UNITS; cnt2++)
					{
						if (chrOtherPlayer[cnt2].bActive && chrOtherPlayer[cnt2].iID == lpTransPartySkill->dwPartyUser[cnt])
						{
							if (AssaParticle_HolyValorIsUse(&chrOtherPlayer[cnt2]) == FALSE)
								AssaParticle_HolyValor_Member(&chrOtherPlayer[cnt2], time);
						}
					}
				}
			}
			break;
		}
		break;
	case CHARACTERCLASS_Priestess:
		switch (SkillCode)
		{
			//Ê¥½àÖ®¹â
		case SKILL_PLAY_EXTINCTION:
			for (cnt = 0; cnt < lpTransPartySkill->PartyCount; cnt++)
			{
				for (cnt2 = 0; cnt2 < MAX_UNITS; cnt2++)
				{
					if (chrOtherPlayer[cnt2].bActive && chrOtherPlayer[cnt2].iID == lpTransPartySkill->dwPartyUser[cnt])
					{
						AssaParticle_Extinction(&chrOtherPlayer[cnt2]);
						SkillPlaySound(SKILL_SOUND_SKILL_EXTINTION, chrOtherPlayer[cnt2].pX, chrOtherPlayer[cnt2].pY, chrOtherPlayer[cnt2].pZ);
					}
				}
			}
			break;
		}
		break;
	case CHARACTERCLASS_Shaman:
		switch (SkillCode)
		{
			//Âõ¿Ë¶û
		case SKILL_PLAY_ADVENT_MIGAL:
			time = Advent_Migal_Time[point - 1];
			for (cnt = 1; cnt < lpTransPartySkill->PartyCount; cnt++)
			{
				if (lpCurPlayer->iID == lpTransPartySkill->dwPartyUser[cnt])
				{
					if (cSkill.SearchContiueSkillIndex(SKILL_ADVENT_MIGAL) == NULL)
					{
						SkillPlaySound(SKILL_SOUND_SKILL_SKILL_ADVENT_MIGAL2, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
						SkillCelestialMusPel(lpCurPlayer, (float)time, 0, SKILL_ADVENT_MIGAL);

						lpCurPlayer->dwAdvent_Migal_Time = dwPlayTime + time * 1000;

						sSKILL sSkill;
						ZeroMemory(&sSkill, sizeof(sSKILL));
						sSkill.CODE = SKILL_ADVENT_MIGAL;
						sSkill.UseTime = time;
						sSkill.Flag = TRUE;
						sSkill.Point = point;
						sinContinueSkillSet(&sSkill);
					}
				}
				else
				{
					for (cnt2 = 0; cnt2 < MAX_UNITS; cnt2++)
					{
						if (chrOtherPlayer[cnt2].bActive && chrOtherPlayer[cnt2].iID == lpTransPartySkill->dwPartyUser[cnt])
						{
							SkillPlaySound(SKILL_SOUND_SKILL_SKILL_ADVENT_MIGAL2, chrOtherPlayer[cnt2].pX, chrOtherPlayer[cnt2].pY, chrOtherPlayer[cnt2].pZ);
							SkillCelestialMusPel(&chrOtherPlayer[cnt2], (float)time, 0, SKILL_ADVENT_MIGAL);
						}
					}
				}
			}
			break;
			//Ã×µÂÀ¼´ï
		case SKILL_PLAY_ADVENT_MIDRANDA:
			time = Advent_Midranda_Time[point - 1];
			for (cnt = 1; cnt < lpTransPartySkill->PartyCount; cnt++)
			{
				if (lpCurPlayer->iID == lpTransPartySkill->dwPartyUser[cnt])
				{
					if (cSkill.SearchContiueSkillIndex(SKILL_ADVENT_MIDRANDA) == NULL)
					{
						//SkillPlaySound(SKILL_SOUND_SKILL_ADVENT_MIDRANDA2,lpCurPlayer->pX,lpCurPlayer->pY,lpCurPlayer->pZ);
						SkillCelestialMusPel(lpCurPlayer, (float)time, 0, SKILL_ADVENT_MIDRANDA);

						lpCurPlayer->dwAdvent_Midranda_Time = dwPlayTime + time * 1000;

						sSKILL sSkill;
						ZeroMemory(&sSkill, sizeof(sSKILL));
						sSkill.CODE = SKILL_ADVENT_MIDRANDA;
						sSkill.UseTime = time;
						sSkill.Flag = TRUE;
						sSkill.Point = point;
						sinContinueSkillSet(&sSkill);
					}
				}
				else
				{
					for (cnt2 = 0; cnt2 < MAX_UNITS; cnt2++)
					{
						if (chrOtherPlayer[cnt2].bActive && chrOtherPlayer[cnt2].iID == lpTransPartySkill->dwPartyUser[cnt])
						{
							//SkillPlaySound(SKILL_SOUND_SKILL_ADVENT_MIDRANDA2,chrOtherPlayer[cnt2].pX,chrOtherPlayer[cnt2].pY,chrOtherPlayer[cnt2].pZ);
							SkillCelestialMusPel(&chrOtherPlayer[cnt2], (float)time, 0, SKILL_ADVENT_MIDRANDA);
						}
					}
				}
			}
			break;
			//ÐñÈÕ¶«Éý
		case SKILL_PLAY_MOURNING_PRAY:
			for (cnt = 1; cnt < lpTransPartySkill->PartyCount; cnt++)
			{
				if (lpCurPlayer->iID == lpTransPartySkill->dwPartyUser[cnt])
				{
					//SkillPlaySound(SKILL_SOUND_SKILL_MOURNING_OF_PRAY2,lpCurPlayer->pX,lpCurPlayer->pY,lpCurPlayer->pZ);
					AssaParticle_Effect("MourningOfPreyHit", lpCurPlayer, 0);

					AttackSkil = SKILL_PLAY_MOURNING_PRAY2;
					AttackSkil |= point << 8;

					dm_SelectRange(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, Mourning_Pray_Area[point - 1], FALSE);
					dm_SendRangeDamage(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, 0, 0, AttackSkil);
				}
				else
				{
					for (cnt2 = 0; cnt2 < MAX_UNITS; cnt2++)
					{
						if (chrOtherPlayer[cnt2].bActive && chrOtherPlayer[cnt2].iID == lpTransPartySkill->dwPartyUser[cnt])
						{
							//SkillPlaySound(SKILL_SOUND_SKILL_MOURNING_OF_PRAY2,chrOtherPlayer[cnt2].pX,chrOtherPlayer[cnt2].pY,chrOtherPlayer[cnt2].pZ);
							AssaParticle_Effect("MourningOfPreyHit", &chrOtherPlayer[cnt2], 0);
						}
					}
				}
			}
			break;
		}
		break;
	}
	return TRUE;
}

DWORD	dwLastClanUserCode = 0;

int SendClanJoinService(DWORD dwMsgCode, Unit *lpChar)
{
	smTRANS_CHAR_COMMAND2	smTransCharCommand;

	if (cldata.myPosition != 101 && cldata.myPosition != 104)
		return FALSE;

	smTransCharCommand.code = smTRANSCODE_CLAN_SERVICE;
	smTransCharCommand.size = sizeof(smTRANS_CHAR_COMMAND2);
	smTransCharCommand.WParam = dwMsgCode;
	smTransCharCommand.LParam = lpChar->iID;
	smTransCharCommand.SParam = lpCurPlayer->iID;
	lstrcpy(smTransCharCommand.szName, cldata.name);
	lstrcpy(smTransCharCommand.szId, UserAccount);

	SENDPACKETG(&smTransCharCommand);

	return FALSE;
}

int SendJoinClan()
{
	smTRANS_CHAR_COMMAND2	smTransCharCommand;

	if (!dwLastClanUserCode)
		return FALSE;

	smTransCharCommand.code = smTRANSCODE_CLAN_SERVICE;
	smTransCharCommand.size = sizeof(smTRANS_CHAR_COMMAND2);
	smTransCharCommand.WParam = 2;
	smTransCharCommand.LParam = dwLastClanUserCode;
	smTransCharCommand.SParam = lpCurPlayer->iID;
	lstrcpy(smTransCharCommand.szName, lpCurPlayer->sCharacterData.szName);
	lstrcpy(smTransCharCommand.szId, UserAccount);

	SENDPACKETG(&smTransCharCommand);

	return FALSE;
}

int RecvClanJoinService(smTRANS_CHAR_COMMAND2 *lpTransCharCommand)
{
	Unit *lpChar;

	switch (lpTransCharCommand->WParam)
	{
	case 1:
		if (cldata.myPosition == 102 || cldata.myPosition == 103)
		{
			lpChar = FindAutoPlayer(lpTransCharCommand->SParam);
			if (lpChar)
			{
				ClanJoin(lpTransCharCommand->szName, lpChar->sCharacterData.szName);
				OpenEachPlayer(lpChar);
				DispEachMode = TRUE;
				dwLastClanUserCode = lpTransCharCommand->SParam;
			}
		}
		break;

	case 2:
		if (cldata.myPosition == 101 || cldata.myPosition == 104)
		{
			lpChar = FindAutoPlayer(lpTransCharCommand->SParam);
			if (lpChar)
				menu_joinOpen_Chip(1, lpTransCharCommand->szId, lpTransCharCommand->szName, lpChar->sCharacterData.iClass, lpChar->sCharacterData.iLevel);
			else
				menu_joinOpen_Chip(1, lpTransCharCommand->szId, lpTransCharCommand->szName, 0, 0);
		}
		break;
	}

	return TRUE;
}

DWORD	dwSkill_DivineLightning_Target[8];
int		DivineLightning_Target_Count = 0;
int		DivineLightning_FindCount = 0;


int SkillPlay_DivineLightning_Effect(Unit *lpChar, int SkillPoint)
{
	int cnt, TargetCount;
	int x, y, z, dist;
	int	LightningCount;
	int cCount;
	Unit *lpTarChar;

	TargetCount = 0;

	if (lpChar == lpCurPlayer) {
		for (cnt = 0; cnt < DivineLightning_Target_Count; cnt++) {
			lpTarChar = FindAutoPlayer(dwSkill_DivineLightning_Target[cnt]);
			if (lpTarChar) {
				AssaParticle_DivineLighting(lpTarChar);
				TargetCount++;
			}
		}
	}
	else {
		LightningCount = Divine_Lightning_Num[SkillPoint - 1];

		for (cnt = 0; cnt < MAX_UNITS; cnt++) {
			cCount = (DivineLightning_FindCount + cnt)&OTHER_PLAYER_MASK;
			if (chrOtherPlayer[cCount].bActive && chrOtherPlayer[cCount].iID &&
				lpChar != &chrOtherPlayer[cCount] && chrOtherPlayer[cCount].sCharacterData.iType == CHARACTERTYPE_Monster &&
				chrOtherPlayer[cCount].sCharacterData.iMonsterType != MONSTERTYPE_Friendly &&
				chrOtherPlayer[cCount].sCharacterData.sHP.sMin > 0) {

				x = (lpChar->pX - chrOtherPlayer[cCount].pX) >> FLOATNS;
				y = (lpChar->pY - chrOtherPlayer[cCount].pY) >> FLOATNS;
				z = (lpChar->pZ - chrOtherPlayer[cCount].pZ) >> FLOATNS;

				dist = x * x + y * y + z * z;

				if (dist < (160 * 160)) {
					AssaParticle_DivineLighting(&chrOtherPlayer[cCount]);
					TargetCount++;
					if (TargetCount >= LightningCount) {
						DivineLightning_FindCount = cCount;
						break;
					}
				}
			}
		}

		if (TargetCount < LightningCount && lpChar->sCharacterData.iType == CHARACTERTYPE_Monster) {
			x = (lpChar->pX - lpCurPlayer->pX) >> FLOATNS;
			y = (lpChar->pY - lpCurPlayer->pY) >> FLOATNS;
			z = (lpChar->pZ - lpCurPlayer->pZ) >> FLOATNS;

			dist = x * x + y * y + z * z;

			if (dist < (160 * 160)) {
				AssaParticle_DivineLighting(lpCurPlayer);
				TargetCount++;
			}
		}

	}


	return TargetCount;
}


//µð¹ÙÀÎ ¶óÀÌÆ®´× ½ºÅ³ ¿¬Ãâ ( ¸Ó¹Ì·Îµå )
int SkillPlay_MummyLord_Effect(Unit *lpChar, int Range)
{
	int cnt, TargetCount;
	int x, y, z, dist;
	int	dRange = Range * Range;

	TargetCount = 0;

	if (lpChar->sCharacterData.iMonsterType != MONSTERTYPE_Friendly) {
		//¸ó½ºÅÍ°¡ À¯Àú °ø°Ý
		for (cnt = 0; cnt < MAX_UNITS; cnt++) {
			if (chrOtherPlayer[cnt].bActive && chrOtherPlayer[cnt].iID &&
				lpChar != &chrOtherPlayer[cnt] && chrOtherPlayer[cnt].sCharacterData.iType == CHARACTERTYPE_Player &&
				chrOtherPlayer[cnt].sCharacterData.sHP.sMin > 0)
			{

				x = (lpChar->pX - chrOtherPlayer[cnt].pX) >> FLOATNS;
				y = (lpChar->pY - chrOtherPlayer[cnt].pY) >> FLOATNS;
				z = (lpChar->pZ - chrOtherPlayer[cnt].pZ) >> FLOATNS;

				dist = x * x + y * y + z * z;

				if (dist < dRange) {
					ParkAssaParticle_DivineLighting(&chrOtherPlayer[cnt]);
					TargetCount++;
				}

			}

		}

		if (lpChar->sCharacterData.iType == CHARACTERTYPE_Monster) {
			x = (lpChar->pX - lpCurPlayer->pX) >> FLOATNS;
			y = (lpChar->pY - lpCurPlayer->pY) >> FLOATNS;
			z = (lpChar->pZ - lpCurPlayer->pZ) >> FLOATNS;

			dist = x * x + y * y + z * z;

			if (dist < dRange) {
				ParkAssaParticle_DivineLighting(lpCurPlayer);
				TargetCount++;
			}
		}
	}
	else {
		//À¯Àú¶û °°Àº Æí ( ¸ó½ºÅÍ °ø°Ý )
		for (cnt = 0; cnt < MAX_UNITS; cnt++) {
			if (chrOtherPlayer[cnt].bActive && chrOtherPlayer[cnt].iID &&
				lpChar != &chrOtherPlayer[cnt] && chrOtherPlayer[cnt].sCharacterData.iType == CHARACTERTYPE_Monster &&
				chrOtherPlayer[cnt].sCharacterData.sHP.sMin > 0)
			{

				x = (lpChar->pX - chrOtherPlayer[cnt].pX) >> FLOATNS;
				y = (lpChar->pY - chrOtherPlayer[cnt].pY) >> FLOATNS;
				z = (lpChar->pZ - chrOtherPlayer[cnt].pZ) >> FLOATNS;

				dist = x * x + y * y + z * z;

				if (dist < dRange) {
					ParkAssaParticle_DivineLighting(&chrOtherPlayer[cnt]);
					TargetCount++;
				}

			}
		}
	}


	return TargetCount;
}


//ÁéÉßµØÇ¹
int SkillPlay_VenomSpear_Effect(Unit *lpChar, int SkillPoint)
{
	int cnt, TargetCount;
	int x, y, z, dist;
	int	LightningCount;
	int cCount;
	Unit *lpTarChar;
	int range;

	range = VenomSpear_Range[SkillPoint - 1];
	range *= range;

	TargetCount = 0;

	if (lpChar == lpCurPlayer)
	{
		for (cnt = 0; cnt < DivineLightning_Target_Count; cnt++)
		{
			lpTarChar = FindAutoPlayer(dwSkill_DivineLightning_Target[cnt]);
			if (lpTarChar)
			{
				AssaParticle_VeonmSpear(lpTarChar);
				TargetCount++;
			}
		}
	}
	else
	{
		LightningCount = VenomSpear_Num[SkillPoint - 1];

		for (cnt = 0; cnt < MAX_UNITS; cnt++)
		{
			cCount = (DivineLightning_FindCount + cnt)&OTHER_PLAYER_MASK;
			if (chrOtherPlayer[cCount].bActive && chrOtherPlayer[cCount].iID && lpChar != &chrOtherPlayer[cCount] && chrOtherPlayer[cCount].sCharacterData.iType == CHARACTERTYPE_Monster && chrOtherPlayer[cCount].sCharacterData.iMonsterType != MONSTERTYPE_Friendly && chrOtherPlayer[cCount].sCharacterData.sHP.sMin > 0)
			{
				x = (lpChar->pX - chrOtherPlayer[cCount].pX) >> FLOATNS;
				y = (lpChar->pY - chrOtherPlayer[cCount].pY) >> FLOATNS;
				z = (lpChar->pZ - chrOtherPlayer[cCount].pZ) >> FLOATNS;

				dist = x * x + y * y + z * z;

				if (dist < range)
				{
					AssaParticle_VeonmSpear(&chrOtherPlayer[cCount]);
					TargetCount++;
					if (TargetCount >= LightningCount)
					{
						DivineLightning_FindCount = cCount;
						break;
					}
				}
			}
		}
	}

	return TargetCount;
}
//µØÏ®ÆæÇ¹
int SkillPlay_Spear_Effect(Unit *lpChar, int SkillPoint)
{
	int cnt, TargetCount;
	int x, y, z, dist;
	int	LightningCount;
	int cCount;
	Unit *lpTarChar;
	int range;

	range = F_Spear_Area[SkillPoint - 1];
	range *= range;

	TargetCount = 0;

	if (lpChar == lpCurPlayer)
	{
		for (cnt = 0; cnt < DivineLightning_Target_Count; cnt++)
		{
			lpTarChar = FindAutoPlayer(dwSkill_DivineLightning_Target[cnt]);
			if (lpTarChar)
			{
				AssaParticle_Spear(lpTarChar);
				TargetCount++;
			}
		}
	}
	else
	{
		LightningCount = F_Spear_Num[SkillPoint - 1];

		for (cnt = 0; cnt < MAX_UNITS; cnt++)
		{
			cCount = (DivineLightning_FindCount + cnt)&OTHER_PLAYER_MASK;
			if (chrOtherPlayer[cCount].bActive && chrOtherPlayer[cCount].iID && lpChar != &chrOtherPlayer[cCount] && chrOtherPlayer[cCount].sCharacterData.iType == CHARACTERTYPE_Monster && chrOtherPlayer[cCount].sCharacterData.iMonsterType != MONSTERTYPE_Friendly && chrOtherPlayer[cCount].sCharacterData.sHP.sMin > 0)
			{
				x = (lpChar->pX - chrOtherPlayer[cCount].pX) >> FLOATNS;
				y = (lpChar->pY - chrOtherPlayer[cCount].pY) >> FLOATNS;
				z = (lpChar->pZ - chrOtherPlayer[cCount].pZ) >> FLOATNS;

				dist = x * x + y * y + z * z;

				if (dist < range)
				{
					AssaParticle_Spear(&chrOtherPlayer[cCount]);
					TargetCount++;
					if (TargetCount >= LightningCount)
					{
						DivineLightning_FindCount = cCount;
						break;
					}
				}
			}
		}
	}

	return TargetCount;
}

//¸ó½ºÅÍ ½ºÅ³ ÀÌÆåÆ® ½ÇÇö ( ÀÌÆåÆ® ½ÇÇö )
int SkillPlay_Monster_Effect(Unit *lpChar, int EffectKind, int Range)
{
	int cnt, TargetCount;
	int x, y, z, dist;
	int dDist = Range * Range;


	TargetCount = 0;

	x = (lpChar->pX - lpCurPlayer->pX) >> FLOATNS;
	y = (lpChar->pY - lpCurPlayer->pY) >> FLOATNS;
	z = (lpChar->pZ - lpCurPlayer->pZ) >> FLOATNS;

	dist = x * x + y * y + z * z;

	if (dist < dDist) {
		ParkAssaParticle_ChaosKaraSkill_User(lpCurPlayer);	// Ä«¿À½ºÄ«¶ó ¹ìÆÄÀÌ¾î¸¯ (À¯Àú)
		TargetCount++;
	}


	for (cnt = 0; cnt < MAX_UNITS; cnt++) {
		if (chrOtherPlayer[cnt].bActive && chrOtherPlayer[cnt].iID &&
			lpChar != &chrOtherPlayer[cnt] && chrOtherPlayer[cnt].sCharacterData.iType == CHARACTERTYPE_Player &&
			chrOtherPlayer[cnt].sCharacterData.sHP.sMin > 0)
		{
			x = (lpChar->pX - chrOtherPlayer[cnt].pX) >> FLOATNS;
			y = (lpChar->pY - chrOtherPlayer[cnt].pY) >> FLOATNS;
			z = (lpChar->pZ - chrOtherPlayer[cnt].pZ) >> FLOATNS;

			dist = x * x + y * y + z * z;

			if (dist < dDist) {
				ParkAssaParticle_ChaosKaraSkill_User(&chrOtherPlayer[cnt]);	// Ä«¿À½ºÄ«¶ó ¹ìÆÄÀÌ¾î¸¯ (À¯Àú)
				TargetCount++;
			}
		}
	}

	return TargetCount;
}




//½ÓÊÜÊ±¼ä¼¼ÄÜ
int RecvProcessSkill(smTRANS_COMMAND *lpTransCommand)
{
	int cnt;

	int dwSkillCode, point;
	Unit	*lpChar, *lpChar2;
	POINT3D	Pos1, Pos2;

	dwSkillCode = lpTransCommand->WParam & 0xFF;
	point = (lpTransCommand->WParam >> 8) & 0xF;

	int JobCode = lpTransCommand->EParam;

	//·ÀÓùµç²¨
	if (JobCode == CHARACTERCLASS_Mechanician && dwSkillCode == SKILL_PLAY_SPARK_SHIELD)
	{
		lpChar = FindChrPlayer(lpTransCommand->LParam);
		lpChar2 = FindChrPlayer(lpTransCommand->SParam);
		if (lpChar && lpChar2)
		{
			if (lpChar->HvLeftHand.PatTool)
			{
				if (lpChar->GetToolBipPoint(&lpChar->HvLeftHand, &Pos1.x, &Pos1.y, &Pos1.z))
				{
					Pos2.x = lpChar2->pX;
					Pos2.y = lpChar2->pY + 24 * fONE;
					Pos2.z = lpChar2->pZ;

					AssaParticle_SparkShieldDefence(&Pos1, &Pos2);
					SkillPlaySound(SKILL_SOUND_SKILL_SPARK2, lpChar->pX, lpChar->pY, lpChar->pZ);
				}
			}
		}
	}
	//×ÔÈ»Ö®¹â
	else if (JobCode == CHARACTERCLASS_Archer && dwSkillCode == SKILL_PLAY_FORCE_OF_NATURE)
	{
		cSkill.ForeceOfNature(Force_Of_Nature_Time[point - 1], point, 1);
		SkillSagittarionForceOfNature1(lpCurPlayer, (float)Force_Of_Nature_Time[point - 1]);
		lpCurPlayer->dwForceOfNatureTime = dwPlayTime + Force_Of_Nature_Time[point - 1] * 1000;
	}
	//Òþ°µÖ®Êõ
	else if (JobCode == CHARACTERCLASS_Pikeman && dwSkillCode == SKILL_PLAY_VANISH)
	{
		lpCurPlayer->PlayVanish = 0;
		cSkill.CancelContinueSkill(SKILL_VANISH);
		if (dwM_BlurTime)
			dwM_BlurTime = dwPlayTime;
	}
	//Õ½ÀõÅØÏø
	else if (JobCode == CHARACTERCLASS_Atalanta && dwSkillCode == SKILL_PLAY_TRIUMPH_OF_VALHALLA)
	{
		cSkill.SetT_Of_Valhalla(point, lpTransCommand->SParam);
		AssaParticle_TriumphOfValhalla(lpCurPlayer, T_Of_Valhalla_Time[point - 1]);
		lpCurPlayer->dwT_Of_Valhalla_Time = dwPlayTime + T_Of_Valhalla_Time[point - 1] * 1000;
		lpCurPlayer->ClearSkillToPlay(SKILL_HALL_OF_VALHALLA);
	}
	//Íß¶û¹þÀ­Ö®¹â
	else if (JobCode == CHARACTERCLASS_Atalanta && dwSkillCode == SKILL_PLAY_HALL_OF_VALHALLA)
	{
		int TVPoint, Lv;
		TVPoint = (lpTransCommand->SParam >> 8) & 0xFF;
		Lv = lpTransCommand->SParam & 0xFF;
		cSkill.HellOfValhalla(Hall_Of_Valhalla_Time[point - 1], point, TVPoint, Lv, 1);
		SkillValhallaHallOfValhallaHandEffect(lpCurPlayer, (float)Lv);
		lpCurPlayer->dwHallOfValhallaTime = dwPlayTime + Hall_Of_Valhalla_Time[point - 1] * 1000;
		lpCurPlayer->ClearSkillToPlay(SKILL_TRIUMPH_OF_VALHALLA);
	}
	//ÍöÁéÖ®Öä
	else if (JobCode == CHARACTERCLASS_Knight && dwSkillCode == SKILL_PLAY_H_BENEDIC)
	{
		lpChar = FindChrPlayer(lpTransCommand->SParam);
		if (lpChar)
		{
			sinEffect_Benedic(lpChar, H_Benedic_Time[point - 1]);
			lpChar->dwH_Benedic_Time = dwPlayTime + H_Benedic_Time[point - 1] * 1000;

			if (lpChar->sCharacterData.iType == CHARACTERTYPE_Player)
				cSkill.SetH_Benedic(H_Benedic_Time[point - 1], point);
		}
	}
	//ÔªËØÖ®Êõ
	else if (JobCode == CHARACTERCLASS_Magician && dwSkillCode == SKILL_PLAY_ENCHANT_WEAPON)
	{
		cnt = Enchant_Weapon_Time[point - 1];
		lpCurPlayer->EnchantEffect_Point = point;
		cSkill.SetEnchant_Weapon(cnt, point);
		switch (lpTransCommand->SParam)
		{
		case 0:
			AssaParticle_EnchantWeaponIceJang(lpCurPlayer, cnt);
			lpCurPlayer->WeaponEffect = sITEMINFO_ICE + 1;
			lpCurPlayer->dwWeaponEffectTime = dwPlayTime + cnt * 1000;
			break;
		case 1:
			AssaParticle_EnchantWeaponLightJang(lpCurPlayer, cnt);
			lpCurPlayer->WeaponEffect = sITEMINFO_LIGHTING + 1;
			lpCurPlayer->dwWeaponEffectTime = dwPlayTime + cnt * 1000;
			break;
		case 2:
			AssaParticle_EnchantWeaponFireJang(lpCurPlayer, cnt);
			lpCurPlayer->WeaponEffect = sITEMINFO_FIRE + 1;
			lpCurPlayer->dwWeaponEffectTime = dwPlayTime + cnt * 1000;
			break;
		}
	}
	//ÖÎÓúÖ®Êõ
	else if (JobCode == CHARACTERCLASS_Priestess && dwSkillCode == SKILL_PLAY_HEALING)
	{
		lpChar = FindChrPlayer(lpTransCommand->LParam);
		if (lpChar)
		{
			sinEffect_Healing2(lpChar);
			SkillPlaySound(SKILL_SOUND_SKILL_HEALING, lpChar->pX, lpChar->pY, lpChar->pZ);
		}
	}
	//ÉñÊ¥·´Éä
	else if (JobCode == CHARACTERCLASS_Priestess && dwSkillCode == SKILL_PLAY_HOLY_REFLECTION)
	{
		sinSkillEffect_Holy_Reflection_Defense(lpCurPlayer);
	}
	//»ØÉúÖ®Êõ
	else if (JobCode == CHARACTERCLASS_Priestess && dwSkillCode == SKILL_PLAY_RESURRECTION)
	{
		if (lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType == ANIMATIONTYPE_Die)
		{
			SendProcessSKillToServer(SKILL_PLAY_RESURRECTION, point, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Revive);
			StartEffect(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, EFFECT_GAME_START1);
			SetDynLight(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 100, 100, 100, 0, 200);
			CharPlaySound(lpCurPlayer);
			sinSetLife(lpCurPlayer->sCharacterData.sHP.sMax / 2);
			ResetEnergyGraph(4);
			lpCurPlayer->MoveFlag = FALSE;
			RestartPlayCount = 350;
			ReStartFlag = 0;
		}
	}
	//ÉñÊ¥Ö®¹â
	else if (JobCode == CHARACTERCLASS_Priestess && dwSkillCode == SKILL_PLAY_VIRTUAL_LIFE)
	{
		cSkill.SetVirtualLife(Virtual_Life_Time[point - 1], point);
		AssaParticle_VirtualLifeStart(lpCurPlayer);
		AssaParticle_VirtualLifeEffect(lpCurPlayer, Virtual_Life_Time[point - 1]);
		lpCurPlayer->dwVirtual_Life_Time = dwPlayTime + Virtual_Life_Time[point - 1] * 1000;
	}
	// ÖÂÃ¤
	else if (JobCode == CHARACTERCLASS_Assassin && dwSkillCode == SKILL_PLAY_BLIND)
	{
		lpCurPlayer->PlayVanish = 0;
		cSkill.CancelContinueSkill(SKILL_BLIND);

		if (dwM_BlurTime)
			dwM_BlurTime = dwPlayTime;
	}
	else if (dwSkillCode == SKILL_PLAY_LOVELY_LIFE)
	{
		if (lpTransCommand->LParam == lpCurPlayer->iID)
		{
			cSkill.SetVirtualLife(Virtual_Life_Time[point - 1], point);
			AssaParticle_VirtualLifeStart(lpCurPlayer);
			AssaParticle_VirtualLifeEffect(lpCurPlayer, Virtual_Life_Time[point - 1]);
			lpCurPlayer->dwVirtual_Life_Time = dwPlayTime + Virtual_Life_Time[point - 1] * 1000;
			SkillPlaySound(SKILL_SOUND_SKILL_VIRTUAL_LIFE, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
		}
		else
		{
			lpChar = FindChrPlayer(lpTransCommand->LParam);
			if (lpChar)
			{
				AssaParticle_VirtualLifeStart(lpChar);
				AssaParticle_VirtualLifeEffect(lpChar, Virtual_Life_Time[point - 1]);
				SkillPlaySound(SKILL_SOUND_SKILL_VIRTUAL_LIFE, lpChar->pX, lpChar->pY, lpChar->pZ);
			}
		}
	}
	else if (dwSkillCode == SKILL_PLAY_SOD_ITEM)
	{
		switch (lpTransCommand->SParam)
		{
		case 1:
			SetBellatraFontEffect(E_BL_QUAKE_SEAL);
			SetBellatraFontEffect(E_BL_FONT_QUAKE_SEAL);
			EffectWaveCamera(50, 3);
			SkillPlaySound(SKILL_SOUND_SKILL_DIASTROPHISM, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
			break;

		case 2:
			SetBellatraFontEffect(E_BL_STUN_SEAL);
			SetBellatraFontEffect(E_BL_FONT_STUN_SEAL);
			EffectWaveCamera(50, 3);
			SkillPlaySound(SKILL_SOUND_SKILL_DIASTROPHISM, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
			break;

		case 3:
			SetBellatraFontEffect(E_BL_FREEZE_SEAL);
			SetBellatraFontEffect(E_BL_FONT_FREEZE_SEAL);
			EffectWaveCamera(50, 3);
			SkillPlaySound(SKILL_SOUND_SKILL_DIASTROPHISM, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
			break;

		case 4:
			SetBellatraFontEffect(E_BL_RABBIE_SEAL);
			SetBellatraFontEffect(E_BL_FONT_RABBIE_SEAL);
			EffectWaveCamera(50, 3);
			SkillPlaySound(SKILL_SOUND_SKILL_DIASTROPHISM, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
			break;

		case 5:
			SetBellatraFontEffect(E_BL_STYGIAN_SEAL);
			SetBellatraFontEffect(E_BL_FONT_STYGIAN_SEAL);
			break;

		case 6:
			SetBellatraFontEffect(E_BL_GUARDIAN_SEAL);
			SetBellatraFontEffect(E_BL_FONT_GUARDIAN_SEAL);
			break;

		case 7:
			SetBellatraFontEffect(E_BL_POINT_SEAL);
			SetBellatraFontEffect(E_BL_FONT_POINT_SEAL);
			break;
		}
		esPlaySound(19, 360);
	}
	else if (dwSkillCode == SKILL_PLAY_BLESS_SIEGE_ITEM)
	{
		switch (lpTransCommand->SParam)
		{
		case (sinBI1 | sin05):
			lpCurPlayer->PlayInvincible = 70 * 30;
			break;
		case (sinBI1 | sin06):
			break;
		case (sinBI1 | sin07):
			break;
		case (sinBC1 | sin01):
			lpCurPlayer->PlayInvincible = 70 * 30;
			break;
		}
	}
	return TRUE;
}
int SendClanCommandUser(DWORD	dwCode, int Param1, int Param2, CLANWONLIST *lpClanUserList, int ClanUserCount)
{

	TRANS_CLAN_COMMAND_USER	TransClanUser;
	int	cnt, len;
	char *lpBuff;
	DWORD	dwSpeedSum;
	int	BuffSize;

	TransClanUser.code = dwCode;

	TransClanUser.Param[0] = Param1;
	TransClanUser.Param[1] = Param2;
	TransClanUser.Param[2] = 0;
	TransClanUser.Param[3] = 0;
	TransClanUser.UserCount = ClanUserCount;

	lpBuff = TransClanUser.szUserBuff;

	for (cnt = 0; cnt < ClanUserCount; cnt++) {
		dwSpeedSum = GetCodebyName(lpClanUserList->clanWon[cnt]);
		((DWORD *)lpBuff)[0] = dwSpeedSum;
		lpBuff += sizeof(DWORD);
		lstrcpy(lpBuff, lpClanUserList->clanWon[cnt]);
		len = lstrlen(lpClanUserList->clanWon[cnt]);
		lpBuff += len + 1;
	}

	BuffSize = lpBuff - TransClanUser.szUserBuff;
	BuffSize += 16;

	TransClanUser.size = 32 + BuffSize;

	if (ClanUserCount > 0) {

		SENDPACKETL(&TransClanUser);
	}

	return TRUE;
}

//Å¬·£¿ø Á¤º¸ ÇØµ¶
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

//¼ì²éÈÎÎñÎïÆ·
int FiltQuestItem(TRANS_ITEMINFO *lpTransItemInfo, DWORD dwPacketCode)
{
	int cnt;

	if (chaQuest.sHaQuestElementary[Quest_A].CODE == HAQUEST_CODE_ELEMENTARY_A)
	{
		if (lpTransItemInfo->sItem.sItemID.ToInt() == (sinQT1 | sin14))
		{
			cnt = cInvenTory.SearchItemCode(sinQT1 | sin14);
			if (cnt >= 1)
				return FALSE;
			return TRUE;
		}
	}
	if (chaQuest.sHaQuestElementary[Quest_B].CODE == HAQUEST_CODE_ELEMENTARY_B)
	{
		if (lpTransItemInfo->sItem.sItemID.ToInt() == (sinQT1 | sin16))
		{
			cnt = cInvenTory.SearchItemCode(sinQT1 | sin16);
			if (cnt >= 1)
				return FALSE;
			return TRUE;
		}
	}
	if (chaQuest.sHaQuestElementary[Quest_D].CODE == HAQUEST_CODE_ELEMENTARY_D)
	{
		if (lpTransItemInfo->sItem.sItemID.ToInt() == (sinQT1 | sin15))
		{
			cnt = cInvenTory.SearchItemCode(sinQT1 | sin15);
			if (cnt >= 1)
				return FALSE;
			return TRUE;
		}
	}

	if (lpTransItemInfo->sItem.sItemID.ToInt() == (sinQT1 | sin17))
	{
		cnt = cInvenTory.SearchItemCode(sinQT1 | sin17);
		if (cnt >= 1)
			return FALSE;
		return TRUE;
	}
	if (chaQuest.sHaQuestElementary[Quest_L].CODE == HAQUEST_CODE_ELEMENTARY_L)
	{
		if (lpTransItemInfo->sItem.sItemID.ToInt() == (sinQT1 | sin19))
		{
			cnt = cInvenTory.SearchItemCode(sinQT1 | sin19);
			if (cnt >= 1)
				return FALSE;
			return TRUE;
		}
	}
	if (sinQuest_ChangeJob.CODE)
	{
		if (lpTransItemInfo->sItem.sItemID.ToInt() == (sinQT1 | sin01))
		{
			cnt = cInvenTory.SearchItemCode(sinQT1 | sin01);
			if (cnt >= 1)
				return FALSE;
			return TRUE;
		}

		if (lpTransItemInfo->sItem.sItemID.ToInt() == (sinQT1 | sin02))
		{
			cnt = cInvenTory.SearchItemCode(sinQT1 | sin02);
			if (cnt >= 1)
				return FALSE;
			return TRUE;
		}

		if (lpTransItemInfo->sItem.sItemID.ToInt() == (sinQT1 | sin03))
		{
			cnt = cInvenTory.SearchItemCode(sinQT1 | sin03);
			if (cnt >= 1)
				return FALSE;
			return TRUE;
		}
	}
	switch (sinQuest_ChangeJob2.CODE)
	{
	case SIN_QUEST_CODE_CHANGEJOB2_NPC_M:
		if (lpTransItemInfo->sItem.sItemID.ToInt() == (sinMA2 | sin01))
		{
			if (!cInvenTory.SearchItemCode(sinMA1 | sin01))
				return FALSE;
			if (cInvenTory.SearchItemCode(sinQT1 | sin04))
				return FALSE;
			cnt = cInvenTory.SearchItemCode(sinMA2 | sin01);
			if (cnt >= 9)
				return FALSE;
		}
		if (lpTransItemInfo->sItem.sItemID.ToInt() == (sinMA2 | sin02))
			return FALSE;
		return TRUE;

	case SIN_QUEST_CODE_CHANGEJOB2_NPC_D:
		if (lpTransItemInfo->sItem.sItemID.ToInt() == (sinMA2 | sin02))
		{
			if (!cInvenTory.SearchItemCode(sinMA1 | sin01))
				return FALSE;
			if (cInvenTory.SearchItemCode(sinQT1 | sin05))
				return FALSE;
			cnt = cInvenTory.SearchItemCode(sinMA2 | sin02);
			if (cnt >= 7)
				return FALSE;
		}
		if (lpTransItemInfo->sItem.sItemID.ToInt() == (sinMA2 | sin01))
			return FALSE;
	}
	if (lpTransItemInfo->sItem.sItemID.ToInt() == (sinQT1 | sin06))
	{
		if (sinQuest_ChangeJob3.CODE == SIN_QUEST_CODE_CHANGEJOB3)
		{
			cnt = cInvenTory.SearchItemCode(sinQT1 | sin06);
			if (cnt >= 3)
				return FALSE;
			return TRUE;
		}
		return FALSE;
	}
	if (lpTransItemInfo->sItem.sItemID.ToInt() == (sinQT1 | sin09))
	{
		if (sinQuest_Level80_2.CODE == SIN_QUEST_CODE_LEVEL80_2)
		{
			cnt = cInvenTory.SearchItemCode(sinQT1 | sin09);
			if (cnt >= 1)
				return FALSE;
			return TRUE;
		}
		return FALSE;
	}
	if (lpTransItemInfo->sItem.sItemID.ToInt() == (sinQT1 | sin10))
	{
		if (sinQuest_Level80_2.CODE == SIN_QUEST_CODE_LEVEL80_2)
		{
			cnt = cInvenTory.SearchItemCode(sinQT1 | sin10);
			if (cnt >= 1)
				return FALSE;
			return TRUE;
		}
		return FALSE;
	}
	if (lpTransItemInfo->sItem.sItemID.ToInt() == (sinQT1 | sin11))
	{
		if (sinQuest_Level80_2.CODE == SIN_QUEST_CODE_LEVEL80_2)
		{
			cnt = cInvenTory.SearchItemCode(sinQT1 | sin11);
			if (cnt >= 1)
				return FALSE;
			return TRUE;
		}
		return FALSE;
	}
	if (lpTransItemInfo->sItem.sItemID.ToInt() == (sinQT1 | sin12))
	{
		if (sinQuest_Level80_2.CODE == SIN_QUEST_CODE_LEVEL80_2)
		{
			cnt = cInvenTory.SearchItemCode(sinQT1 | sin12);
			if (cnt >= 1)
				return FALSE;
			return TRUE;
		}
		return FALSE;
	}

	if (lpTransItemInfo->sItem.sItemID.ToInt() == (sinQT1 | sin13))
	{
		if (sinQuest_ChangeJob4.CODE == SIN_QUEST_CODE_CHANGEJOB4 && sinQuest_ChangeJob4.State == 5)
		{
			cnt = cInvenTory.SearchItemCode(sinQT1 | sin13);
			if (cnt >= 1 || CheckAttMonsterCode(sinQuest_ChangeJob4.Kind) == FALSE)
				return FALSE;
			return TRUE;
		}
		return FALSE;
	}

	if ((lpTransItemInfo->sItem.sItemID.ToItemType()) == sinMA1 ||
		(lpTransItemInfo->sItem.sItemID.ToItemType()) == sinMA2 ||
		(lpTransItemInfo->sItem.sItemID.ToItemType()) == sinQT1)
		return FALSE;

	return TRUE;
}

POINT GetProcessModule();

//¸ðµâ°Ë»ç ÇÏ¿© ¼­¹ö·Î º¸³»±â
int CheckProcessModule()
{
	return TRUE;
}
// ·¢ËÍÊôÐÔÉËº¦
int SendElementDamage(Unit *lpChar, int Kind)
{
	DWORD Point;

	Point = (1 + Kind) << 8;
	Point |= SKILL_PLAY_ELEMENT_ATTACK;

	return dm_SendTransDamage(lpChar, 0, 0, 0, 0, Point, FALSE);
}
//·¢ËÍÁÔÓ¥¹¥»÷
int SendFalconDamage(Unit *lpChar)
{
	DWORD point;
	int cnt;

	if (lpChar == lpCurPlayer && lpChar->chrAttackTarget)
	{
		point = ((SkillFalconPoint ^ ((DWORD)chrOtherPlayer^lpCurPlayer->iID)) + 1) << 8;
		point |= SKILL_PLAY_FALCON;
		cnt = dm_SendTransDamage(lpChar->chrAttackTarget, 0, 0, 0, 0, point, FALSE);
		DamageExp(lpChar->chrAttackTarget, cnt);
		return cnt;
	}
	return NULL;
}

//´í½Ì¼Òµå µ¥¹ÌÁö º¸³»±â
int SendDancingSwordDamage(Unit *lpChar)
{
	DWORD point;
	int cnt;
	int wpDamage[2];

	if (lpChar) {

		wpDamage[0] = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin;
		wpDamage[1] = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax;

		point = 1 << 8;
		point |= SKILL_PLAY_DANCING_SWORD;
		cnt = dm_SendTransDamage(lpChar, wpDamage[0], wpDamage[1], 0, 0, point, FALSE);
		DamageExp(lpChar, cnt);

		if ((rand() % 2) == 0)
			SkillPlaySound(SKILL_SOUND_SKILL_DANCING_SWORD_ATK1, lpChar->pX, lpChar->pY, lpChar->pZ);
		else
			SkillPlaySound(SKILL_SOUND_SKILL_DANCING_SWORD_ATK2, lpChar->pX, lpChar->pY, lpChar->pZ);

		return cnt;
	}
	return FALSE;
}


//¸Þ±×³×Æ½ ½ºÇÇ¾î µ¥¹ÌÁö º¸³»±â
int SendMegneticSphereDamage(Unit *lpChar)
{
	DWORD point;
	int cnt;
	int wpDamage[2];

	if (lpChar)
	{
		wpDamage[0] = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin;
		wpDamage[1] = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax;

		point = 1 << 8;
		point |= SKILL_PLAY_MAGNETIC_SPHERE;
		cnt = dm_SendTransDamage(lpChar, wpDamage[0], wpDamage[1], 0, 0, point, FALSE);
		DamageExp(lpChar, cnt);

		if ((rand() % 2) == 0)
			SkillPlaySound(SKILL_SOUND_SKILL_DANCING_SWORD_ATK1, lpChar->pX, lpChar->pY, lpChar->pZ);
		else
			SkillPlaySound(SKILL_SOUND_SKILL_DANCING_SWORD_ATK2, lpChar->pX, lpChar->pY, lpChar->pZ);

		return cnt;
	}
	return FALSE;
}

//¸Ó½ºÆç µ¥¹ÌÁö º¸³»±â
int SendMuspellDamage(Unit *lpChar)
{
	DWORD point;
	int cnt;
	int wpDamage[2];

	if (lpChar) {

		wpDamage[0] = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin;
		wpDamage[1] = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax;

		point = 1 << 8;
		point |= SKILL_PLAY_SUMMON_MUSPELL;
		cnt = dm_SendTransDamage(lpChar, wpDamage[0], wpDamage[1], 0, 0, point, FALSE);
		DamageExp(lpChar, cnt);

		if ((rand() % 2) == 0)
			SkillPlaySound(SKILL_SOUND_SKILL_DANCING_SWORD_ATK1, lpChar->pX, lpChar->pY, lpChar->pZ);
		else
			SkillPlaySound(SKILL_SOUND_SKILL_DANCING_SWORD_ATK2, lpChar->pX, lpChar->pY, lpChar->pZ);

		return cnt;
	}
	return FALSE;
}



//Àú·¦¿ë Æê µ¥¹ÌÁö
int SendLowLevelPetDamage(Unit *lpChar, int petType)
{
	DWORD point;
	int cnt;
	int wpDamage[2];

	if (lpChar)
	{
		wpDamage[0] = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin;
		wpDamage[1] = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax;

		point = (1 + petType) << 8;
		point |= SKILL_PLAY_PET_ATTACK;
		cnt = dm_SendTransDamage(lpChar, wpDamage[0], wpDamage[1], 0, 0, point, FALSE);
		DamageExp(lpChar, cnt);

		return cnt;
	}
	return FALSE;
}


//PC¹æ¿ë Æê µ¥¹ÌÁö
int SendPCBangPetDamage(Unit *lpChar, int petType)
{
	DWORD point;
	int cnt;
	int wpDamage[2];

	if (lpChar) {

		wpDamage[0] = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin;
		wpDamage[1] = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax;

		point = (1 + petType) << 8;
		point |= SKILL_PLAY_PET_ATTACK2;
		cnt = dm_SendTransDamage(lpChar, wpDamage[0], wpDamage[1], 0, 0, point, FALSE);
		DamageExp(lpChar, cnt);

		return cnt;
	}
	return FALSE;
}



//¾ÆÀÌÅÛ ÅÃ¹è ¼­ºñ½º ¼ö½Å ¿ä±¸
int	SendItemExpress(DWORD	dwItemCode, char *szPassCode)
{
	smTRANS_COMMAND	smTransCommand;

	ZeroMemory((char *)&smTransCommand, sizeof(smTRANS_COMMAND));
	smTransCommand.code = smTRANSCODE_ITEM_EXPRESS;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = dwItemCode;

	if (szPassCode)
		smTransCommand.LParam = GetCodebyName(szPassCode);

	SENDPACKETL(&smTransCommand);

	return FALSE;
}

//¾ÆÀÌÅÛ ÅÃ¹è ¼­ºñ½º ¼ö½Å ¿ä±¸
int	SendItemExpress(DWORD	dwItemCode)
{
	return	SendItemExpress(dwItemCode, 0);
}


//¾ßÈ£ ¸ð¼Ç ¼­¹ö·Î º¸³»±â
int SendClanYahooMotion()
{
	smTRANS_COMMAND	smTransCommand;

	if (lpCurPlayer->sCharacterData.iClanID) {
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.code = smTRANSCODE_YAHOO_MOTION;
		smTransCommand.WParam = dwPlayTime;
		smTransCommand.LParam = 0;
		smTransCommand.SParam = 0;
		smTransCommand.EParam = 0;

		SENDPACKETG(&smTransCommand);

		return TRUE;

	}
	return FALSE;
}

//º° Æ÷ÀÎÆ® Á¤º¸¸¦ ¼­¹ö¿¡ º¸³½´Ù
int	SendStarPointToServer(int Price, int Cash)
{
	smTRANS_COMMAND	smTransCommand;

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = smTRANSCODE_STARPOINT;
	smTransCommand.WParam = Price;
	smTransCommand.LParam = Cash;
	smTransCommand.SParam = 0;
	smTransCommand.EParam = 0;

	SENDPACKETL(&smTransCommand);

	return FALSE;
}

//±âºÎÇÑµ·À» ¼­¹ö¿¡ º¸³½´Ù
int	SendGiveMoneyToServer(int Money)
{
	smTRANS_COMMAND	smTransCommand;

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = smTRANSCODE_GIVEMONEY;
	smTransCommand.WParam = Money;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;
	smTransCommand.EParam = 0;

	SENDPACKETL(&smTransCommand);

	return FALSE;
}

//Å¬·£¸Ó´Ï Á¤º¸¸¦ ¼­¹ö¿¡ º¸³½´Ù
int	SendClanMoneyToServer(int Money, int Flag, int Kind)
{
	smTRANS_COMMAND	smTransCommand;

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = smTRANSCODE_CLANMONEY;
	smTransCommand.WParam = Money;
	smTransCommand.LParam = Flag;
	smTransCommand.SParam = Kind;
	smTransCommand.EParam = 0;

	SENDPACKETL(&smTransCommand);

	return FALSE;
}

int	SendClanMoneyToServer(int Money, int Flag)
{
	return	SendClanMoneyToServer(Money, Flag, 0);
}

//ÀÌ¿ë¿ä±Ý Á¤º¸¸¦ ¼­¹ö¿¡ º¸³½´Ù
int	SendPaymentMoneyToServer(int Money, int Flag)
{
	smTRANS_COMMAND	smTransCommand;

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = smTRANSCODE_PAYMENT_MONEY;
	smTransCommand.WParam = Flag;
	smTransCommand.LParam = Money;
	smTransCommand.SParam = 0;
	smTransCommand.EParam = 0;

	SENDPACKETL(&smTransCommand);

	return FALSE;
}

int	Send_ShowMyShopItem(Unit *lpChar)
{
	smTRANS_COMMAND	smTransCommand;

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = smTRANSCODE_CALL_MYSHOP;
	smTransCommand.WParam = 0;
	smTransCommand.LParam = lpChar->iID;
	smTransCommand.SParam = lpCurPlayer->iID;
	smTransCommand.EParam = 0;

	SENDPACKETG(&smTransCommand);

	return 0;
}
int	Send_MyShopItemList(smTRANS_COMMAND	*lpTransCommand)
{
	TransTradeItems_MyShop.dwRecver = lpTransCommand->SParam;

	SENDPACKETG(&TransTradeItems_MyShop);

	return 0;
}
int	Recv_MyShopItemList(TRANS_TRADEITEMS *lpTransTradeItems)
{
	sMYSHOP MyShopItem;
	Unit	*lpChar;

	DecodeCompress(lpTransTradeItems->TradeBuff, (BYTE *)&MyShopItem);

	cCharShop.RecvShopItem(&MyShopItem);


	lpChar = FindAutoPlayer(lpTransTradeItems->dwSender);

	if (lpChar && lpChar->DisplayFlag && lpChar->sCharacterData.szName[0])
	{
		OpenEachPlayer(lpChar);
		DispEachMode = TRUE;
	}

	return TRUE;
}
int	Send_PersonalShopItem(DWORD dwCharCode, void *lpShopItem)
{
	smTRANS_COMMAND_BUFF	smtBuff;

	smtBuff.smTransCommand.code = smTRANSCODE_MYSHOP_TRADE;
	smtBuff.smTransCommand.size = sizeof(smTRANS_COMMAND) + sizeof(sMYSHOP_ITEM_SERVER);
	smtBuff.smTransCommand.WParam = 0;
	smtBuff.smTransCommand.LParam = dwCharCode;
	smtBuff.smTransCommand.SParam = lpCurPlayer->iID;
	smtBuff.smTransCommand.EParam = 0;

	memcpy(smtBuff.Buff, lpShopItem, sizeof(sMYSHOP_ITEM_SERVER));

	SENDPACKETL(&smtBuff);

	return FALSE;
}
int	UpdateMyShopList(void *lpMyShop)
{
	sMYSHOP *lpMyShopItem = (sMYSHOP *)lpMyShop;
	int	result = 0;
	int		len;

	ZeroMemory(&TransTradeItems_MyShop, sizeof(TRANS_TRADEITEMS));

	len = EecodeCompress((BYTE *)lpMyShopItem, TransTradeItems_MyShop.TradeBuff, sizeof(sMYSHOP));
	if (len > TRANS_TRADE_BUFF_SIZE)
		return FALSE;

	TransTradeItems_MyShop.code = smTRANSCODE_MYSHOP_ITEM;
	TransTradeItems_MyShop.size = len + 48;
	TransTradeItems_MyShop.dwSum = 0;
	TransTradeItems_MyShop.dwSender = lpCurPlayer->iID;
	TransTradeItems_MyShop.dwRecver = 0;
	TransTradeItems_MyShop.Temp[0] = 0;
	TransTradeItems_MyShop.Temp[1] = 0;
	TransTradeItems_MyShop.Temp[2] = 0;
	TransTradeItems_MyShop.Temp[3] = 0;

	return TRUE;
}
int SendOpenPersonalTrade(char *szTradeMsg, void *lpPersTrade)
{
	TRANS_CHATMESSAGE	TransChatMessage;
	int	result = 0;
	DWORD	dwCode;
	sMYSHOP *lpMyShopItem = (sMYSHOP *)lpPersTrade;
	int		len;

	ZeroMemory(&TransTradeItems_MyShop, sizeof(TRANS_TRADEITEMS));

	ZeroMemory(&TransChatMessage, sizeof(TRANS_CHATMESSAGE));

	len = EecodeCompress((BYTE *)lpMyShopItem, TransTradeItems_MyShop.TradeBuff, sizeof(sMYSHOP));
	if (len > TRANS_TRADE_BUFF_SIZE)
		return FALSE;

	TransTradeItems_MyShop.code = smTRANSCODE_MYSHOP_ITEM;
	TransTradeItems_MyShop.size = len + 48;
	TransTradeItems_MyShop.dwSum = 0;
	TransTradeItems_MyShop.dwSender = lpCurPlayer->iID;
	TransTradeItems_MyShop.dwRecver = 0;
	TransTradeItems_MyShop.Temp[0] = 0;
	TransTradeItems_MyShop.Temp[1] = 0;
	TransTradeItems_MyShop.Temp[2] = 0;
	TransTradeItems_MyShop.Temp[3] = 0;


	TransChatMessage.code = smTRANSCODE_OPEN_MYSHOP;
	TransChatMessage.size = sizeof(TRANS_CHATMESSAGE);
	lstrcpy(TransChatMessage.szMessage, szTradeMsg);

	dwCode = GetCodebyName(szTradeMsg);
	TransChatMessage.dwIP = dwCode;

	SENDPACKETG(&TransChatMessage);

	if (result)
	{
		wsprintf(lpCurPlayer->szTradeMessage, "%s: %s", lpCurPlayer->sCharacterData.szName, szTradeMsg);
		lpCurPlayer->dwTradeMsgCode = dwCode;
	}

	return result;
}
int SendClosePersonalTrade()
{
	TRANS_CHATMESSAGE	TransChatMessage;
	int	result = 0;

	ZeroMemory(&TransChatMessage, sizeof(TRANS_CHATMESSAGE));

	TransChatMessage.code = smTRANSCODE_OPEN_MYSHOP;
	TransChatMessage.size = sizeof(TRANS_CHATMESSAGE);

	SENDPACKETG(&TransChatMessage);

	lpCurPlayer->dwTradeMsgCode = 0;
	lpCurPlayer->szTradeMessage[0] = 0;

	return 0;
}
int SendsServerDoc(char *szTradeMsg)
{
	TRANS_CHATMESSAGE	TransChatMessage;
	int	result = 0;


	ZeroMemory(&TransChatMessage, sizeof(TRANS_CHATMESSAGE));

	TransChatMessage.code = smTRANSCODE_ITEMDOC;
	TransChatMessage.size = sizeof(TRANS_CHATMESSAGE);
	lstrcpy(TransChatMessage.szMessage, szTradeMsg);

	SENDPACKETG(&TransChatMessage);

	return result;
}
int DeleteEventItem_TimeOut(Item	*lpsItem)
{
	if (lpsItem->sItemID.ToInt() == (sinBI1 | sin36) || lpsItem->sItemID.ToInt() == (sinBI1 | sin37) ||
		lpsItem->sItemID.ToInt() == (sinBI1 | sin38) || lpsItem->sItemID.ToInt() == (sinBI1 | sin39) ||
		lpsItem->sItemID.ToInt() == (sinBI1 | sin40) || lpsItem->sItemID.ToInt() == (sinBI1 | sin41) ||
		lpsItem->sItemID.ToInt() == (sinBI1 | sin42) || lpsItem->sItemID.ToInt() == (sinBI1 | sin43) ||
		lpsItem->sItemID.ToInt() == (sinBI1 | sin44) || lpsItem->sItemID.ToInt() == (sinBI1 | sin45) ||
		lpsItem->sItemID.ToInt() == (sinBI1 | sin46) || lpsItem->sItemID.ToInt() == (sinBI1 | sin47) ||
		lpsItem->sItemID.ToInt() == (sinBI1 | sin48) || lpsItem->sItemID.ToInt() == (sinBI1 | sin49) ||
		lpsItem->sItemID.ToInt() == (sinBI1 | sin50) || lpsItem->sItemID.ToInt() == (sinBI1 | sin52) ||
		lpsItem->sItemID.ToInt() == (sinBI1 | sin53) || lpsItem->sItemID.ToInt() == (sinBI1 | sin54) ||

		lpsItem->sItemID.ToInt() == (sinBI1 | sin65) || lpsItem->sItemID.ToInt() == (sinBI1 | sin66) ||
		lpsItem->sItemID.ToInt() == (sinBI1 | sin67) || lpsItem->sItemID.ToInt() == (sinBI1 | sin68) ||
		lpsItem->sItemID.ToInt() == (sinBI1 | sin69) || lpsItem->sItemID.ToInt() == (sinBI1 | sin70) ||
		lpsItem->sItemID.ToInt() == (sinBI1 | sin71) || lpsItem->sItemID.ToInt() == (sinBI1 | sin72) ||
		lpsItem->sItemID.ToInt() == (sinBI1 | sin55) ||
		lpsItem->sItemID.ToInt() == (sinBI1 | sin62) || lpsItem->sItemID.ToInt() == (sinBI1 | sin63) ||
		lpsItem->sItemID.ToInt() == (sinBI1 | sin64) ||
		lpsItem->sItemID.ToInt() == (sinBI1 | sin73) || lpsItem->sItemID.ToInt() == (sinBI1 | sin74) ||
		lpsItem->sItemID.ToInt() == (sinBI1 | sin75) || lpsItem->sItemID.ToInt() == (sinBI1 | sin76))
	{
		return FALSE;
	}

	struct	tm	tm;
	time_t		ttm;
	DWORD		dwCreateTime;

	DWORD		dwItemCode;

	dwItemCode = lpsItem->sItemID.ToItemType();

	DWORD NowTime = GetPlayTime_T();

	if (lpsItem->sItemID.ToInt() == (sinDB1 | sin33) || lpsItem->sItemID.ToInt() == (sinOA2 | sin33))
	{
		if (lpsItem->dwCreateTime + (60 * 60 * 24 * 1) < NowTime)
			return true;
	}

	if (lpsItem->sItemID.ToInt() == (sinDB1 | sin34) || lpsItem->sItemID.ToInt() == (sinOA2 | sin34))
	{
		if (lpsItem->dwCreateTime + (60 * 60) < NowTime)
			return true;
	}

	if (lpsItem->sItemID.ToInt() == (sinOA1 | sin33))
	{
		if (lpsItem->dwCreateTime + (60 * 60 * 24 * 7) < NowTime)
			return TRUE;
	}
	if (lpsItem->sItemID.ToInt() == (sinOA1 | sin34))
	{
		if (lpsItem->dwCreateTime + (60 * 60) < NowTime)
			return TRUE;
	}
	if (lpsItem->sItemID.ToInt() == (sinOA1 | sin35))
	{
		if (lpsItem->dwCreateTime + (60 * 60 * 24) < NowTime)
			return TRUE;
	}
	if (lpsItem->sItemID.ToInt() == (sinOA1 | sin36) || lpsItem->sItemID.ToInt() == (sinOA1 | sin37))
	{
		if (lpsItem->dwCreateTime + (60 * 60 * 24 * 7) < NowTime)
			return TRUE;
	}

	if (lpsItem->sItemID.ToInt() == (sinOA1 | sin39) ||
		lpsItem->sItemID.ToInt() == (sinOA1 | sin40) ||
		lpsItem->sItemID.ToInt() == (sinOA1 | sin41) ||
		lpsItem->sItemID.ToInt() == (sinOA1 | sin42) ||
		lpsItem->sItemID.ToInt() == (sinOA1 | sin38))
	{
		if (lpsItem->dwCreateTime + (60 * 60 * 24 * 14) < NowTime)
			return TRUE;
	}

	if (lpsItem->sItemID.ToInt() != (sinOR2 | sin01) && dwItemCode != sinPZ1 && dwItemCode != sinPZ2)
		return FALSE;


	tm.tm_year = 2004 - 1900;
	tm.tm_mon = 4 - 1;
	tm.tm_mday = 1;
	tm.tm_hour = 15;
	tm.tm_min = 30;
	tm.tm_sec = 0;
	ttm = mktime(&tm);

	dwCreateTime = (DWORD)ttm;

	if (lpsItem->dwCreateTime < dwCreateTime)
		return TRUE;

	return FALSE;
}

int RecvSodGameInfomation(void *Info)
{
	smTRANS_COMMAND_SOD	*lpTransCommand = (smTRANS_COMMAND_SOD *)Info;

	if (!BellatraEffectInitFlag)
	{
		CreateBellatraFontEffect();
		BellatraEffectInitFlag = TRUE;
	}

	switch (lpTransCommand->smTransCommand.WParam)
	{
	case 1:
		if (SoD_SetFontEffect.eBL_Type == E_BL_LODING)
			CheckBellatraFontEffect(&SoD_SetFontEffect, TRUE);

		if (lpTransCommand->smTransCommand.SParam < 0)
		{
			sSodScore.EffectStartCount = 70 * 3;
			sSodScore.EffectCode = lpTransCommand->smTransCommand.LParam + 1;
		}
		else
		{
			if (lpCurPlayer->psModelAnimation->iType == ANIMATIONTYPE_Die)
				break;

			sSodScore.SodNextStageNum = lpTransCommand->smTransCommand.SParam;
			sSodScore.dwSoD_NextStageTime = dwPlayTime + 9000;
			sSodScore.dwSoD_CloseStageTime = dwPlayTime + 5000;
			sSodScore.NextRound = lpTransCommand->smTransCommand.LParam + 1;

			StopBGM();
			esPlayContSound(14);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Yahoo);

			SetBellatraFontEffect(E_BL_FONT_STAGE);
			SetBellatraFontEffect(E_BL_FONT_COMPLETE);
			SoDGateFlag = TRUE;
		}
		break;
	case 3:
		if (lpCurPlayer->psModelAnimation->iType == ANIMATIONTYPE_Die)
			break;

		sSodScore.SodNextStageNum = -1;
		sSodScore.dwSoD_NextStageTime = dwPlayTime + 8000;
		sSodScore.dwSoD_CloseStageTime = dwPlayTime + 6000;
		sSodScore.NextRound = -1;

		StopBGM();
		esPlayContSound(15);

		SetBellatraFontEffect(E_BL_FONT_STAGE);
		SetBellatraFontEffect(E_BL_FONT_FAIL);
		SoDGateFlag = TRUE;
		break;
	case 4:
		if (lpCurPlayer->psModelAnimation->iType == ANIMATIONTYPE_Die)
			break;

		sSodScore.SodNextStageNum = lpTransCommand->smTransCommand.SParam;
		sSodScore.dwSoD_NextStageTime = dwPlayTime + 7000;
		sSodScore.NextRound = lpTransCommand->smTransCommand.LParam + 1;

		StopBGM();
		esPlayContSound(16);
		lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Yahoo);

		SetBellatraFontEffect(E_BL_FONT_CON);
		SoDGateFlag = FALSE;

		char szBuff[128];
		wsprintf(szBuff, "Congratulations! You have survived and won %d Gold", lpTransCommand->smTransCommand.EParam);
		cMessageBox.ShowMessageEvent(szBuff);
		break;
	case 2:
		if (lpTransCommand->smTransCommand.LParam)
			sSodScore.ScoreEffectCount = 255;

		if (!sSodScore.dwSoD_NextStageTime)
		{
			if (sSodScore.Round != lpTransCommand->smTransCommand.SParam)
			{
				switch (lpTransCommand->smTransCommand.SParam)
				{
				case 1:
					sSodScore.dwPlayTime = dwPlayTime;
					PlayBGM_Direct(BGM_CODE_SOD1);
					break;

				case 4:
					PlayBGM_Direct(BGM_CODE_SOD2);
					break;

				case 7:
					PlayBGM_Direct(BGM_CODE_SOD3);
					break;
				}
			}
			sSodScore.Round = lpTransCommand->smTransCommand.SParam;
		}

		sSodScore.dwDispTime = dwPlayTime + 10 * 1000;
		sSodScore.MyTeam = lpTransCommand->MyTeam;
		sSodScore.Score = lpTransCommand->MyScore;
		sSodScore.TeamScore[0] = lpTransCommand->TeamScore[0];
		sSodScore.TeamScore[1] = lpTransCommand->TeamScore[1];
		sSodScore.TeamScore[2] = lpTransCommand->TeamScore[2];
		sSodScore.TeamScore[3] = lpTransCommand->TeamScore[3];
		break;
	case smCODE_SOD_EFFECT:
		if (!BellatraEffectInitFlag)
		{
			CreateBellatraFontEffect();
			BellatraEffectInitFlag = TRUE;
		}
		SetBellatraFontEffect((EBL_FontEffectType)lpTransCommand->smTransCommand.LParam);
		break;
	}

	return TRUE;
}
int RecvForceOrbItem(TRANS_ITEMINFO_GROUP2 *lpTransItemGroup2)
{
	TRANS_ITEMINFO_GROUP	TransItemGroup;

	ZeroMemory(&TransItemGroup, sizeof(TRANS_ITEMINFO_GROUP));
	memcpy(&TransItemGroup, lpTransItemGroup2, TRANS_GROUPITEM_HEADER_SIZE);

	DecodeCompress((BYTE *)lpTransItemGroup2->szBuff, (BYTE *)TransItemGroup.sItemInfo, sizeof(Item)*TRANS_GROUPITEM_MAX);

	sinRecvForceOrb(TransItemGroup.sItemInfo, TransItemGroup.ItemCount);


	return TRUE;
}
int SendQuestCommandToServer(DWORD dwQuestCode, int Param1, int Param2, int Param3)
{
	smTRANS_COMMAND	smTransCommand;
	int	result = 0;

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = smTRANSCODE_QUEST_COMMAND;
	smTransCommand.WParam = dwQuestCode;
	smTransCommand.LParam = Param1;
	smTransCommand.SParam = Param2;
	smTransCommand.EParam = Param3;

	if (dwQuestCode >= HAQUEST_CODE_ELEMENTARY_A && dwQuestCode <= HAQUEST_CODE_FURYOFPHANTOM)
	{
		SENDPACKETL(&smTransCommand);

		return result;
	}

	SENDPACKETG(&smTransCommand);

	return result;
}
int Start_QuestArena(DWORD dwQuestCode, int Param1, int Param2)
{
	smTRANS_COMMAND	smTransCommand;
	int	result = 0;

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = smTRANSCODE_QUEST_COMMAND;
	smTransCommand.WParam = dwQuestCode;
	smTransCommand.LParam = QUEST_ARENA_FIELD;
	smTransCommand.SParam = Param1;
	smTransCommand.EParam = Param2;

	SENDPACKETG(&smTransCommand);

	GAMEMAP->LoadWarpMap(MAPID_QuestArena);

	return FALSE;
}
int	Send_GetBlessCastleTax()
{
	PacketBlessCastleTex sPacket;

	sPacket.iLength = sizeof(PacketBlessCastleTex);
	sPacket.iHeader = PKTHDR_BlessCastleTax;
	sPacket.iTax = cSinSiege.GetTaxRate();

	SENDPACKETL(&sPacket);

	return FALSE;
}
int RecvBlessShowDamage(void *lpPacket)
{
	chaSiege.ShowSiegeScore((PacketBlessCastleTopData *)lpPacket);

	return 1;
}
int RecvBlessCastInfo(void *lpPacket)
{
	chaSiege.ShowSiegeMenu((PacketBlessCastleStatusSettingsData *)lpPacket);



	return TRUE;
}
int SetBlessCastleMaster(DWORD dwClanCode, int Mode)
{
	if (!Mode && lpCurPlayer->iLoadedMapIndex >= 0 && STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == rsCASTLE_FIELD)
	{

	}
	else
	{
		if (rsBlessCastle.dwMasterClan != dwClanCode)
			UpdateCastleMasterClan(rsBlessCastle.dwMasterClan);

		rsBlessCastle.dwMasterClan = dwClanCode;
	}

	return TRUE;
}
int	SendResistanceToServer()
{
	smTRANS_RESISTANCE	smTransResistance;

	dwResistance_SendingTime = dwPlayTime;

	smTransResistance.code = smTRANSCODE_RESISTANCE;
	smTransResistance.size = sizeof(smTRANS_RESISTANCE);
	smTransResistance.Param = 0;
	memcpy(smTransResistance.Resistance, lpCurPlayer->sCharacterData.sElementalDef, sizeof(short) * 8);
	smTransResistance.Absorb = lpCurPlayer->sCharacterData.iAbsorbRating;

	SENDPACKETG(&smTransResistance);

	return FALSE;
}
int	SendPublicPollingToServer(int PollCode, int PollCnt, BYTE *bPollingData)
{
	smTRANS_COMMAND_POLLING	smTransPolling;

	ZeroMemory(&smTransPolling, sizeof(smTRANS_COMMAND_POLLING));

	smTransPolling.smTransCommand.code = smTRANSCODE_PUBLIC_POLLING;
	smTransPolling.smTransCommand.size = sizeof(smTRANS_COMMAND_POLLING);
	smTransPolling.smTransCommand.WParam = PollCode;
	smTransPolling.smTransCommand.LParam = PollCnt;
	memcpy(smTransPolling.bPolling, bPollingData, PollCnt);

	SENDPACKETL(&smTransPolling);

	return TRUE;
}


int	SendHackTrapToServer(DWORD dwTrapCode, int Param)
{
	smTRANS_COMMAND	smTransCommand;

	ZeroMemory(&smTransCommand, sizeof(smTRANS_COMMAND));

	smTransCommand.code = smTRANSCODE_HACKTRAP;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = dwTrapCode;
	smTransCommand.LParam = Param;

	if (dwTrapCode == 100)
	{
		if (lpCurPlayer->iLoadedMapIndex >= 0)
			smTransCommand.SParam = STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID;
		else
			return FALSE;
	}

	SENDPACKETL(&smTransCommand);


	return TRUE;
}

// pluto Á¦·Ã µ¥ÀÌÅ¸¸¦ ¼­¹ö·Î º¸³¿
int SendSmeltingItemToServer(void *lpsSmeltingItem_Send)
{
	sSMELTINGITEM_SERVER	*lpSmeltingItem_Send = (sSMELTINGITEM_SERVER *)lpsSmeltingItem_Send;

	lpSmeltingItem_Send->size = sizeof(sSMELTINGITEM_SERVER);
	lpSmeltingItem_Send->code = smTRANSCODE_SMELTINGITEM;

	SENDPACKETL(lpSmeltingItem_Send);

	return FALSE;
}
// pluto Á¦ÀÛ µ¥ÀÌÅ¸¸¦ ¼­¹ö·Î º¸³¿
int SendManufactureItemToServer(void *lpsManufactureItem_Send)
{
	SManufactureItem_Server *lpManufactureItem_Send = (SManufactureItem_Server *)lpsManufactureItem_Send;

	lpManufactureItem_Send->size = sizeof(SManufactureItem_Server);
	lpManufactureItem_Send->code = smTRANSCODE_MANUFACTURE;

	SENDPACKETL(lpManufactureItem_Send);

	return FALSE;
}

int SendMixtureResetItemToServer(void *lpsMixtureResetItem_Send)
{
	sMIXTURE_RESET_ITEM_SERVER *lpMixtureResetItem_Send = (sMIXTURE_RESET_ITEM_SERVER *)lpsMixtureResetItem_Send;

	lpMixtureResetItem_Send->size = sizeof(sMIXTURE_RESET_ITEM_SERVER);
	lpMixtureResetItem_Send->code = smTRANSCODE_MIXTURE_RESET_ITEM;

	SENDPACKETL(lpMixtureResetItem_Send);

	return FALSE;
}
