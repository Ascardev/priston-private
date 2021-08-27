#include "StdAfx.h"
#include "ChatHandle.h"

namespace CHAT
{
	Handle::Handle() : CBaseHandle()
	{

	}
	Handle::Handle(EHandle eID) : CBaseHandle(eID)
	{

	}
	Handle::~Handle()
	{
		
	}
	void Handle::Init()
	{
		
	}
	void Handle::Shutdown()
	{
		
	}
	void Handle::SendChat(BOOL bLoginServer, const char * pszChat)
	{
		int iChatLen = STRLEN(pszChat);

		if ((iChatLen < MAX_CHATLENGTH) && (iChatLen > 0))
		{
			PacketChat sPacket;
			sPacket.iLength = sizeof(Packet) + iChatLen + 1;
			sPacket.iHeader = PKTHDR_ChatGame;
			STRINGCOPY(sPacket.szChat, pszChat);

			bLoginServer ? SENDPACKETL(&sPacket) : SENDPACKETG(&sPacket);
		}
	}
	BOOL Handle::AnalyzeChat(char * pszBuff)
	{
		char szChatCommandParam1[256] = { 0 };
		char szChatCommandParam2[256] = { 0 };
		char szChatCommandParam3[256] = { 0 };
		char szChatCommandParam4[256] = { 0 };
		char szChatCommandParam5[256] = { 0 };

		BOOL bRetChat = TRUE;

		if (ChatCommand("/camera_wave_off", pszBuff))
		{
			SETTINGHANDLE->Get().bNoCameraWave = TRUE;
			AddChatBoxText("> Camera Shake disabled");

			bRetChat = FALSE;
		}
		else if (ChatCommand("/camera_wave_on", pszBuff))
		{
			SETTINGHANDLE->Get().bNoCameraWave = FALSE;
			AddChatBoxText("> Camera Shake enabled");

			bRetChat = FALSE;
		}
		else if (ChatCommand("yahoo", pszBuff) || ChatCommand("Yes!", pszBuff))
		{
			dwYahooTime = TICKCOUNT + 60 * 1000;

			if (lpCurPlayer->psModelAnimation)
			{
				if (lpCurPlayer->psModelAnimation->iType < ANIMATIONTYPE_Attack)
					lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Yahoo);
			}

			bRetChat = FALSE;
		}

		if (SETTINGHANDLE->Get().bDebugMode)
		{
			if (ChatCommand("/SetDarkLevel", pszBuff))
			{
				GetParameterString(pszBuff, 1, szChatCommandParam1);

				DarkLevel_Fix = atoi(szChatCommandParam1);

				AddChatBoxTextEx(CHATCOLOR_Error, "> Dark setted to %d", DarkLevel_Fix);
			}
			else if (ChatCommand("/color", pszBuff))
			{
				GetParameterString(pszBuff, 1, szChatCommandParam1);
				GetParameterString(pszBuff, 2, szChatCommandParam2);
				GetParameterString(pszBuff, 3, szChatCommandParam3);

				int iR = atoi(szChatCommandParam1);
				int iG = atoi(szChatCommandParam2);
				int iB = atoi(szChatCommandParam3);

				BackColor_mR = iR;
				BackColor_mG = iG;
				BackColor_mB = iB;

				AddChatBoxTextEx(CHATCOLOR_Error, "> Enviroment Color %d %d %d!", iR, iG, iB);
			}
			else if (ChatCommand("/field", pszBuff))
			{
				GetParameterString(pszBuff, 1, szChatCommandParam1);

				GAMEMAP->LoadWarpMap((EMapID)atoi(szChatCommandParam1));
			}
		}

		return bRetChat;
	}
	void Handle::AddChatBoxText(char * pszText, EChatColor iColor)
	{
		if (GAMESCREEN->GetActiveScreenType() == SCREEN_World)
			CHATBOX->AddMessage(pszText, iColor);
	}
	void Handle::AddChatBoxTextEx(EChatColor iColor, char * pszText, ...)
	{
		va_list vl;

		char szText[128];

		va_start(vl, pszText);
		_vsnprintf_s(szText, _countof(szText), _TRUNCATE, pszText, vl);
		va_end(vl);

		AddChatBoxText(szText, iColor);
	}
}