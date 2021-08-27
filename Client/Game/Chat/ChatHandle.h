#pragma once

namespace CHAT
{
	class Handle : public CBaseHandle
	{
	public:
		Handle();
		Handle(EHandle eID);
		virtual ~Handle();

		void Init();
		void Shutdown();
		void SendChat(BOOL bLoginServer, const char * pszChat);
		BOOL AnalyzeChat(char * pszBuff);
		static void AddChatBoxText(char * pszText, EChatColor iColor = CHATCOLOR_Error);
		static void AddChatBoxTextEx(EChatColor iColor, char * pszText, ...);
	};
}