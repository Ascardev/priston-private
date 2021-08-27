#pragma once

namespace CHAT
{
	class Game : public Chat
	{
	public:
		static void AddChatBoxText(char * pszText, EChatColor iColor = CHATCOLOR_Error);
	};
}