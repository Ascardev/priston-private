#pragma once

#define MAX_CHATLENGTH			100
#define MAX_CHATMESSAGES		320

enum EChatColor
{
	CHATCOLOR_Error = 0,
	CHATCOLOR_Whisper = 1,
	CHATCOLOR_Blue = 2,
	CHATCOLOR_Global = 3,
	CHATCOLOR_Party = 4,
	CHATCOLOR_Clan = 5,
	CHATCOLOR_Trade = 6,
	CHATCOLOR_Notice = 9,
	CHATCOLOR_ClanLeader = 10,
	CHATCOLOR_Normal = 11,
	CHATCOLOR_Raid = 12,
};

struct ChatBoxMessage
{
	EChatColor iColor;
	char szMessage[256];
};

namespace CHAT
{
	class Chat
	{
	public:
		static unsigned int	ChatCommand(char * pszCommand, char * pszChat);
	};
}