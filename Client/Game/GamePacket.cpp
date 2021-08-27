#include "StdAfx.h"
#include "GamePacket.h"

CGamePacket::CGamePacket()
{

}
CGamePacket::~CGamePacket()
{

}
BOOL CGamePacket::AnalyzePacket(SocketData * pcSocketData, Packet * psPacket)
{
	switch (psPacket->iHeader)
	{
		//Party
	case PKTHDR_RequestParty:
		PARTYHANDLE->HandlePacket((PacketRequestParty*)psPacket);
		break;
	case PKTHDR_UpdateParty:
		PARTYHANDLE->HandlePacket((PacketUpdateParty*)psPacket);
		break;
	case PKTHDR_UpdatePartyData:
		PARTYHANDLE->HandlePacket((PacketUpdatePartyData*)psPacket);
		break;
	case PKTHDR_RequestRaid:
		PARTYHANDLE->HandlePacket((PacketRequestRaid*)psPacket);
		break;

	case PKTHDR_Ping:
		GAMESOCKET->HandlePacket(pcSocketData, (PacketPing *)psPacket);
		GAMESOCKET->Connected();
		break;
	case PKTHDR_Reconnect:
		CHATGAMEHANDLE->AddChatBoxText("> Reconnected to Game Server!");
		GAMESOCKET->bGameServerReconnect = FALSE;
		GAMESOCKET->iReconnectGCOUNT = 0;
		break;
	case PKTHDR_ReconnectLogin:
		CHATGAMEHANDLE->AddChatBoxText("> Reconnected to Login Server!");

		GAMESOCKET->bLoginServerReconnect = FALSE;
		GAMESOCKET->iReconnectLCOUNT = 0;
		break;
	case PKTHDR_AddExp:
		GAMEUNIT->AddExp(((PacketExperience *)psPacket)->iAddExp);
		break;
	case PKTHDR_PacketFun:
		GAMEUNIT->Fun();
		break;
	case PKTHDR_SetGold:
		UNIT->sCharacterData.iGold = ((PacketSetCharacterGold*)psPacket)->dwGold;
		UPDATE_CHARACTER_CHECKSUM;
		sinPlaySound(SIN_SOUND_COIN);
		break;
	case PKTHDR_TheDeath:
		GAMECHARACTER->HandlePacket((PacketSimple *)psPacket);
		break;
	case PKTHDR_DisableGM:
		SETTINGHANDLE->Get().bDebugMode = FALSE;
		SENDPACKETG(psPacket);
		break;
	case PKTHDR_Disconnect:
		GAMESOCKET->iDisconnectType = pcSocketData == SOCKETL ? 3 : 2;
		GAMESOCKET->iDisconnectTime = TICKCOUNT;
		break;
	case PKTHDR_IntegrityUpdateItem:
		GAMECHARACTER->HandlePacket((PacketUpdateIntegrity *)psPacket);
		break;
	case PKTHDR_Connected:
		GAMECHARACTER->OnConnected(pcSocketData, (PacketSimple *)psPacket);
		break;
	case PKTHDR_BlessCastleShowDamage:
		RecvBlessShowDamage(psPacket);
		break;
	}

	RecvPlayData(pcSocketData, psPacket);
	return FALSE;
}