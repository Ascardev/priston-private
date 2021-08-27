#include "StdAfx.h"
#include "..\\resource.h"

#include "..\\character.h"
#include "..\\fileread.h"
#include "..\\playmain.h"
#include "onserver.h"

int	rsRegist_ItemSecCode(User *lpPlayInfo, TRANS_ITEMINFO *lpTransItemInfo, int NewItem);

void User::Init(int uIndex)
{
	ZeroMemory(this, sizeof(User));

	iMapID = MAPID_Invalid;
	dwNoticeCount = rsNoticeMessage.Counter;

	UnsaveMoney = -1;

	dwTimeLastPacket = SERVER_GAMETIME;
	dwTimeLastStatusUpdate = SERVER_GAMETIME;

	dwConnectCount = dwConnectCount;
	dwLastExpMoneyCheckTime = SERVER_GAMETIME;
	dwLastExpMoneyTransServer = SERVER_GAMETIME;

	SndItemSecCodeCount = 1;

	dwClientFunChk_NextTime = SERVER_GAMETIME + 60 * 1000 * 5;

	psCharacterFile = CHARSDATA + uIndex;
	dwRecordDataTime = SERVER_GAMETIME;
	ZeroMemory(psCharacterFile, sizeof(CharacterFile));

	dwConnectCount++;
}
