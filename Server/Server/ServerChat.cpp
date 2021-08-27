#include "StdAfx.h"
#include "ServerChat.h"

CServerChat::CServerChat()
{

}
CServerChat::~CServerChat()
{

}
void CServerChat::SendDebugChat(User * pcUser, EChatColor eColor, const char * pszFormat, ...)
{
	if (pcUser)
	{
		if (pcUser->iGameLevel > GAMELEVEL_One)
		{
			va_list ap;

			PacketChatBoxMessage sPacket;
			ZeroMemory(&sPacket, sizeof(PacketChatBoxMessage));
			sPacket.iLength = sizeof(PacketChatBoxMessage);
			sPacket.iHeader = PKTHDR_ChatMessage;
			sPacket.iChatColor = eColor;

			va_start(ap, pszFormat);
			vsnprintf_s(sPacket.szChatBoxMessage, 255, pszFormat, ap);
			va_end(ap);

			SENDPACKET(pcUser, &sPacket);
		}
	}
}
void CServerChat::SendChatAllUsersInStage(int iStage, EChatColor eColor, const char * pszFormat, ...)
{
	va_list ap;

	PacketChatBoxMessage sPacket;
	ZeroMemory(&sPacket, sizeof(PacketChatBoxMessage));
	sPacket.iLength = sizeof(PacketChatBoxMessage);
	sPacket.iHeader = PKTHDR_ChatMessage;
	sPacket.iChatColor = eColor;

	va_start(ap, pszFormat);
	vsnprintf_s(sPacket.szChatBoxMessage, 255, pszFormat, ap);
	va_end(ap);

	for (int i = 0; i < PLAYERS_MAX; i++)
	{
		if (USERSDATA[i].pcSocketData)
		{
			if (USERSDATA[i].iMapID == iStage)
				SENDPACKET(&USERSDATA[i], &sPacket);
		}
	}
}
void CServerChat::SendChatAll(EChatColor eColor, const char * pszText)
{
	PacketChatBoxMessage sPacket;
	ZeroMemory(&sPacket, sizeof(PacketChatBoxMessage));
	sPacket.iLength = sizeof(PacketChatBoxMessage);
	sPacket.iHeader = PKTHDR_ChatMessage;
	sPacket.iChatColor = eColor;

	STRINGCOPY(sPacket.szChatBoxMessage, pszText);

	for (int i = 0; i < PLAYERS_MAX; i++)
	{
		if (USERSDATA[i].pcSocketData)
		{
			SENDPACKET(&USERSDATA[i], &sPacket);
		}
	}
}
void CServerChat::SendChatAllEx(EChatColor eColor, const char * pszFormat, ...)
{
	va_list ap;

	PacketChatBoxMessage sPacket;
	ZeroMemory(&sPacket, sizeof(PacketChatBoxMessage));
	sPacket.iLength = sizeof(PacketChatBoxMessage);
	sPacket.iHeader = PKTHDR_ChatMessage;
	sPacket.iChatColor = eColor;

	va_start(ap, pszFormat);
	vsnprintf_s(sPacket.szChatBoxMessage, 255, pszFormat, ap);
	va_end(ap);

	for (int i = 0; i < PLAYERS_MAX; i++)
	{
		if (USERSDATA[i].pcSocketData)
		{
			SENDPACKET(&USERSDATA[i], &sPacket);
		}
	}
}
void CServerChat::SendChatAllUsersInRange(int iX, int iZ, int iRange, EChatColor eColor, const char * pszFormat, ...)
{
	va_list ap;

	PacketChatBoxMessage sPacket;
	ZeroMemory(&sPacket, sizeof(PacketChatBoxMessage));
	sPacket.iLength = sizeof(PacketChatBoxMessage);
	sPacket.iHeader = PKTHDR_ChatMessage;
	sPacket.iChatColor = eColor;

	va_start(ap, pszFormat);
	vsnprintf_s(sPacket.szChatBoxMessage, 255, pszFormat, ap);
	va_end(ap);

	for (int i = 0; i < PLAYERS_MAX; i++)
	{
		if (USERSDATA[i].pcSocketData)
		{
			int iXP = (iX - USERSDATA[i].sPosition.iX) >> 8;
			int iZP = (iZ - USERSDATA[i].sPosition.iZ) >> 8;
			int iDist = iXP * iXP + iZP * iZP;
			if (iDist < iRange && abs(iXP) < 4096 && abs(iZP) < 4096)
				SENDPACKET(&USERSDATA[i], &sPacket);
		}
	}
}
void CServerChat::SendChatAllUsersInClan(User * pcUser, EChatColor eColor, const char * pszFormat, ...)
{
	if (pcUser && pcUser->pcSocketData)
	{
		va_list ap;

		PacketChatBoxMessage sPacket;
		ZeroMemory(&sPacket, sizeof(PacketChatBoxMessage));
		sPacket.iLength = sizeof(PacketChatBoxMessage);
		sPacket.iHeader = PKTHDR_ChatMessage;
		sPacket.iChatColor = eColor;

		va_start(ap, pszFormat);
		vsnprintf_s(sPacket.szChatBoxMessage, 256, pszFormat, ap);
		va_end(ap);

		for (int i = 0; i < PLAYERS_MAX; i++)
		{
			if (USERSDATA[i].pcSocketData)
			{
				if (USERSDATA[i].iClanID == pcUser->iClanID && USERSDATA[i].pcSocketData != pcUser->pcSocketData)
					SENDPACKET(&USERSDATA[i], &sPacket);
			}
		}
	}
}
void CServerChat::SendChat(User * pcUser, EChatColor eColor, const char * pszText)
{
	if (pcUser)
	{
		PacketChatBoxMessage sPacket;
		ZeroMemory(&sPacket, sizeof(PacketChatBoxMessage));
		sPacket.iHeader = PKTHDR_ChatMessage;
		sPacket.iChatColor = eColor;

		STRINGCOPY(sPacket.szChatBoxMessage, pszText);

		sPacket.iLength = 16 + lstrlenA(sPacket.szChatBoxMessage) + 12;

		SENDPACKET(pcUser, &sPacket);
	}
}
void CServerChat::SendChatEx(User * pcUser, EChatColor eColor, const char * pszFormat, ...)
{
	if (pcUser)
	{
		va_list ap;

		PacketChatBoxMessage sPacket;
		ZeroMemory(&sPacket, sizeof(PacketChatBoxMessage));
		sPacket.iHeader = PKTHDR_ChatMessage;
		sPacket.iChatColor = eColor;

		va_start(ap, pszFormat);
		vsnprintf_s(sPacket.szChatBoxMessage, 255, pszFormat, ap);
		va_end(ap);

		sPacket.iLength = 16 + STRLEN(sPacket.szChatBoxMessage) + 12;

		SENDPACKET(pcUser, &sPacket);
	}
}
void CServerChat::SendPersonalShopChat(User * pcUser, DWORD dwObjectID, const char * pszFormat, ...)
{
	if (pcUser)
	{
		va_list ap;

		PacketChatBoxMessage sPacket;
		ZeroMemory(&sPacket, sizeof(PacketChatBoxMessage));
		sPacket.iHeader = PKTHDR_PersonalShopMessage;
		sPacket.iChatColor = CHATCOLOR_Error;
		sPacket.lID = dwObjectID;

		va_start(ap, pszFormat);
		vsnprintf_s(sPacket.szChatBoxMessage, 255, pszFormat, ap);
		va_end(ap);

		sPacket.iLength = 16 + lstrlenA(sPacket.szChatBoxMessage) + 12;

		SENDPACKET(pcUser, &sPacket);
	}
}
void CServerChat::SendUserBoxChat(User * pcUser, DWORD dwObjectID, const char * pszFormat, ...)
{
	if (pcUser)
	{
		va_list ap;

		PacketChatBoxMessage sPacket;
		ZeroMemory(&sPacket, sizeof(PacketChatBoxMessage));
		sPacket.iHeader = PKTHDR_ChatMessage;
		sPacket.iChatColor = CHATCOLOR_Error;
		sPacket.lID = dwObjectID;

		va_start(ap, pszFormat);
		vsnprintf_s(sPacket.szChatBoxMessage, 255, pszFormat, ap);
		va_end(ap);

		sPacket.iLength = 16 + lstrlenA(sPacket.szChatBoxMessage) + 12;

		SENDPACKET(pcUser, &sPacket);
	}
}
void CServerChat::SendUserBoxChatRange(int iX, int iZ, int iRange, DWORD dwObjectID, const char * pszFormat, ...)
{
	va_list ap;

	PacketChatBoxMessage sPacket;
	ZeroMemory(&sPacket, sizeof(PacketChatBoxMessage));
	sPacket.iHeader = PKTHDR_ChatMessage;
	sPacket.iChatColor = CHATCOLOR_Error;
	sPacket.lID = dwObjectID;

	va_start(ap, pszFormat);
	vsnprintf_s(sPacket.szChatBoxMessage, 255, pszFormat, ap);
	va_end(ap);

	sPacket.iLength = 16 + lstrlenA(sPacket.szChatBoxMessage) + 12;

	for (int i = 0; i < PLAYERS_MAX; i++)
	{
		if (USERSDATA[i].pcSocketData)
		{
			int iXP = (iX - USERSDATA[i].sPosition.iX) >> 8;
			int iZP = (iZ - USERSDATA[i].sPosition.iZ) >> 8;
			int iDist = iXP * iXP + iZP * iZP;
			int im = iRange / 1000;
			if (iDist < iRange && abs(iXP) < 4096 && abs(iZP) < 4096)
				SENDPACKET(&USERSDATA[i], &sPacket);
		}
	}
}
void CServerChat::SendChatMessageBox(User * pcUser, const char * pszFormat, ...)
{
	if (pcUser)
	{
		va_list ap;

		PacketChatBoxMessage sPacket;
		ZeroMemory(&sPacket, sizeof(PacketChatBoxMessage));
		sPacket.iHeader = PKTHDR_ChatMessageBox;
		sPacket.iChatColor = CHATCOLOR_Error;

		va_start(ap, pszFormat);
		vsnprintf_s(sPacket.szChatBoxMessage, 255, pszFormat, ap);
		va_end(ap);
		sPacket.iLength = 16 + lstrlenA(sPacket.szChatBoxMessage) + 12;

		SENDPACKET(pcUser, &sPacket);
	}
}
void CServerChat::SendChatSpyMember(User * pcUser, void * pPacket)
{
	SENDPACKET(pcUser, pPacket);
	if (pcUser && pcUser->pcUserDataSpyoner)
	{
		SendChatEx(pcUser, EChatColor::CHATCOLOR_Error, "> [%s User]", pcUser->sCharacterData.szName);
		SENDPACKET(pcUser->pcUserDataSpyoner, pPacket);
	}
}
void CServerChat::SendChatTrade(User * pcUser, std::string strMessage)
{
	if (pcUser)
	{
		if (CanSendMessage(pcUser, strMessage, CHATCOLOR_Trade))
		{
			strMessage.erase(0, 7);
			SendChatAll(CHATCOLOR_Trade, FormatString("[%c]%s: %s", SERVERINFO->GetServerName(pcUser->iServerIndexID)[0], SERVERCHARACTER->GetCharacterName(pcUser), strMessage.c_str()));
			pcUser->dwChatTradeTime = GetCurrentTime() + ((2 * 60) * 1000);
		}
	}
}
void CServerChat::SendWhisperItemLink(User * pcUserSender, User * pcUserReceiver, PacketItemLinkChat * psPacket)
{
	if (!pcUserReceiver->sSettingsData.bNoWhisper)
	{
		std::string strMessage = psPacket->szMessage;

		if (strMessage.length() == 0)
			strMessage = psPacket->cItemData.sItem.szItemName;

		if (strMessage.find("<item>") != std::string::npos)
			strMessage.replace(strMessage.find("<item>"), STRLEN("<item>"), psPacket->cItemData.sItem.szItemName);

		//To Receiver
		STRINGCOPY(psPacket->szMessage, GetFormatWhisper(pcUserSender, strMessage.c_str(), TRUE).c_str());
		SENDPACKET(pcUserReceiver, psPacket);

		//To Sender
		STRINGCOPY(psPacket->szMessage, GetFormatWhisper(pcUserReceiver, strMessage.c_str(), FALSE).c_str());
		SENDPACKET(pcUserSender, psPacket);
	}
	else
		SERVERCHAT->SendChatEx(pcUserSender, CHATCOLOR_Error, "%s disabled private message!", SERVERCHARACTER->GetCharacterName(pcUserReceiver));
}
void CServerChat::HandlePacket(User * pcUser, PacketItemLinkChat * psPacket)
{
	psPacket->cItemData.sItem.iChk1 += RandomI(1000, 20000);
	psPacket->cItemData.sItem.iChk2 += RandomI(2000, 10000);

	if (psPacket->szCharacterName[0] != 0)
	{
		User * pcUserReceiver = SERVERUSER->GetUser(psPacket->szCharacterName);

		if (pcUserReceiver)
			SendWhisperItemLink(pcUser, pcUserReceiver, psPacket);
		else
			SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Error, "> %s is offline or not found!", psPacket->szCharacterName);
	}
	else
	{
		std::string strMessage = GetMessageString(psPacket->szMessage, psPacket->eChatColor);

		if (strMessage.length() == 0)
			strMessage = psPacket->cItemData.sItem.szItemName;

		if (strMessage.find("<item>") != std::string::npos)
			strMessage.replace(strMessage.find("<item>"), STRLEN("<item>"), psPacket->cItemData.sItem.szItemName);

		if (psPacket->eChatColor == CHATCOLOR_Normal)
		{
			STRINGFORMAT(psPacket->szMessage, "%s: %s", SERVERCHARACTER->GetCharacterName(pcUser), strMessage.c_str());

			for (int i = 0; i < SERVERUSER->uUsersInGame; i++)
			{
				User * pcUserReceiver = SERVERUSER->pcaUserInGame[i];

				if (pcUserReceiver && (pcUserReceiver->bNetServer == FALSE) && (pcUser != pcUserReceiver))
				{
					if (pcUser->sPosition.WithinPTDistance(&pcUserReceiver->sPosition, USER_TALKRANGE))
						SENDPACKET(pcUserReceiver, psPacket);
				}
			}

			SENDPACKET(pcUser, psPacket);
		}
		else if (psPacket->eChatColor == CHATCOLOR_Trade)
		{
			if (CanSendMessage(pcUser, psPacket->szMessage, psPacket->eChatColor))
			{
				STRINGFORMAT(psPacket->szMessage, "[%c]%s: %s", SERVERINFO->GetServerName(pcUser->iServerIndexID)[0], SERVERCHARACTER->GetCharacterName(pcUser), strMessage.c_str());

				for (int i = 0; i < SERVERUSER->uUsersInGame; i++)
				{
					User * pcUserReceiver = SERVERUSER->pcaUserInGame[i];

					if (pcUserReceiver && (pcUserReceiver->bNetServer == FALSE) && (pcUser != pcUserReceiver))
					{
						if (pcUser->sPosition.WithinPTDistance(&pcUserReceiver->sPosition, USER_TALKRANGE))
							SENDPACKET(pcUserReceiver, psPacket);
					}
				}

				pcUser->dwChatTradeTime = GetCurrentTime() + ((2 * 60) * 1000);

				SENDPACKET(pcUser, psPacket);
			}
		}
		else if ((psPacket->eChatColor == CHATCOLOR_Party) || (psPacket->eChatColor == CHATCOLOR_Raid))
		{
			STRINGFORMAT(psPacket->szMessage, "[%c]%s: %s", SERVERINFO->GetServerName(pcUser->iServerIndexID)[0], SERVERCHARACTER->GetCharacterName(pcUser), strMessage.c_str());

			if (CanSendMessage(pcUser, psPacket->szMessage, psPacket->eChatColor))
			{
				if (pcUser->bParty && pcUser->psParty)
				{
					std::vector<User*> vUsers = PARTYHANDLE->GetPartyMembers(pcUser->psParty, (psPacket->eChatColor == CHATCOLOR_Raid) ? TRUE : FALSE);

					for (auto &v : vUsers)
					{
						if (v != pcUser)
							SENDPACKET(v, psPacket);
					}
				}

				SENDPACKET(pcUser, psPacket);
			}
		}
		else if (psPacket->eChatColor == CHATCOLOR_Clan)
		{
			if (SERVERCHARACTER->IsCharacterLeader(pcUser))
				psPacket->eChatColor = CHATCOLOR_ClanLeader;

			STRINGFORMAT(psPacket->szMessage, "[%c]%s: %s", SERVERINFO->GetServerName(pcUser->iServerIndexID)[0], SERVERCHARACTER->GetCharacterName(pcUser), strMessage.c_str());

			if (pcUser->iClanID)
			{
				for (int i = 0; i < SERVERUSER->uUsersInGame; i++)
				{
					User * pcUserReceiver = SERVERUSER->pcaUserInGame[i];

					if (pcUserReceiver && (pcUserReceiver->bNetServer == FALSE) && (pcUser != pcUserReceiver))
					{
						if (pcUserReceiver->iClanID && (pcUser->iClanID == pcUserReceiver->iClanID))
							SENDPACKET(pcUserReceiver, psPacket);
					}
				}

				SENDPACKET(pcUser, psPacket);
			}
		}
	}
}
void CServerChat::AddMute(const char *pszName)
{
	m_vMutedNames.push_back(pszName);
}
void CServerChat::ClearMute()
{
	m_vMutedNames.clear();
}

std::string CServerChat::GetFormatWhisper(User * pcUser, const char * pszMessage, BOOL bReceiverTime)
{
	return FormatString("%s> %s: %s", bReceiverTime ? "From" : "To", SERVERCHARACTER->GetCharacterName(pcUser), pszMessage);
}

void CServerChat::SendWhisper(User * pcUserSender, User * pcUserReceiver, const char * pszMessage)
{
	if (pszMessage[0] != 0)
	{
		if (!pcUserReceiver->sSettingsData.bNoWhisper)
		{
			//To Receiver
			SERVERCHAT->SendChat(pcUserReceiver, CHATCOLOR_Blue, GetFormatWhisper(pcUserSender, pszMessage, TRUE).c_str());

			//To Sender
			SERVERCHAT->SendChat(pcUserSender, CHATCOLOR_Blue, GetFormatWhisper(pcUserReceiver, pszMessage, FALSE).c_str());
		}
		else
			SERVERCHAT->SendChatEx(pcUserSender, CHATCOLOR_Error, "%s disabled private message!", SERVERCHARACTER->GetCharacterName(pcUserReceiver));
	}
	else
		SERVERCHAT->SendChatEx(pcUserSender, CHATCOLOR_Error, "%s is online at %s%s", SERVERCHARACTER->GetCharacterName(pcUserReceiver), SERVERINFO->GetServerName(pcUserReceiver->iServerIndexID), pcUserReceiver->sSettingsData.bNoWhisper ? "(No Whisper)" : "");
}

std::string CServerChat::GetMessageString(std::string strMessage, int iChatColor)
{
	std::string str = strMessage;

	if (iChatColor == CHATCOLOR_Trade)
	{
		if (strMessage.length() >= 7)
		{
			if (strMessage.find("TRADE>") != std::string::npos)
			{
				str = strMessage.substr(strMessage.find_first_of(">") + 1);
				str = trim(str);
			}
		}
	}
	else if (iChatColor == CHATCOLOR_Clan)
	{
		if (strMessage.length() >= 6)
		{
			if (strMessage.find("CLAN>") != std::string::npos)
			{
				str = strMessage.substr(strMessage.find_first_of(">") + 1);
				str = trim(str);
			}
		}
	}
	else if ((iChatColor == CHATCOLOR_Party) || (iChatColor == CHATCOLOR_Raid))
	{
		if ((strMessage.length() >= 1) && ((strMessage[0] == '@') || (strMessage[0] == '#')))
		{
			str = strMessage.substr(1);
			str = trim(str);
		}
	}

	return str;
}

BOOL CServerChat::CanSendMessage(User * pcUser, std::string strMessage, int iChatColor)
{
	BOOL bRet = TRUE;

	if (iChatColor == CHATCOLOR_Trade)
	{
		if (strMessage.length() >= 7)
		{
			strMessage = strMessage.substr(strMessage.find_first_of(">") + 1);
			strMessage = trim(strMessage);

			std::string strFind = strMessage;

			if (strMessage.length() > 0)
			{
				//Can talk?
				if (pcUser->bMuted == FALSE)
				{
					BOOL bMutedPlayer = FALSE;
					for (const auto v : m_vMutedNames)
					{
						if (STRINGCOMPAREI(SERVERCHARACTER->GetCharacterName(pcUser), v.c_str()))
						{
							bMutedPlayer = TRUE;
							bRet = FALSE;
							break;
						}
					}

					if (bMutedPlayer == FALSE)
					{
						//To lower
						for (UINT i = 0; i < strMessage.length(); i++)
							strFind[i] = tolower(strFind[i]);

						char cFirstLetter = strMessage[0];
						char cSecondLetter = strMessage[1];

						BOOL bFreeTrade = TRUE;

						//Not GM and on time delay?
						if (pcUser->iGameLevel == GAMELEVEL_None && pcUser->dwChatTradeTime > GetCurrentTime())
						{
							if (!FREE_TRADECHAT)
							{
								//Warning user
								SendChatEx(pcUser, CHATCOLOR_Error, "> Wait %d seconds to write again", (pcUser->dwChatTradeTime - GetCurrentTime()) / 1000);
								bFreeTrade = FALSE;
								bRet = FALSE;
							}
						}

						/*if (bFreeTrade)
						{
							//Not correct first letters?
							if ((cFirstLetter != 'S' && cFirstLetter != 'C' && cFirstLetter != 'B' && cFirstLetter != 'P' && cFirstLetter != 'T') || cSecondLetter != '>')
							{
								//Notify Users
								SendChat(pcUser, CHATCOLOR_Error, "> You can only start your phrase with");
								SendChat(pcUser, CHATCOLOR_Error, "S> For selling");
								SendChat(pcUser, CHATCOLOR_Error, "B> For buying");
								SendChat(pcUser, CHATCOLOR_Error, "T> For trading");
								SendChat(pcUser, CHATCOLOR_Error, "P> Looking for party");
								SendChat(pcUser, CHATCOLOR_Error, "C> Looking for clan");
								SendChat(pcUser, CHATCOLOR_Error, "Example: P> Need party in Iron2");
								bRet = FALSE;
							}
						}*/

						if (bRet)
						{
							for (int i = 0; i < _countof(pszaWordsTrade); i++)
							{
								//Is found words? don't write in chat
								if (strstr(strFind.c_str(), pszaWordsTrade[i]))
								{
									bRet = FALSE;
									break;
								}
							}
						}
					}
				}
			}
		}
		else
			bRet = FALSE;
	}

	return bRet;
}