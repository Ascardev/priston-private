#include "StdAfx.h"
#include "ServerNet.h"

CServerNet::CServerNet()
{

}
CServerNet::~CServerNet()
{

}
void CServerNet::Init()
{
	if (!m_bInit)
	{
		ConnectAll();
		m_bInit = TRUE;
	}
}
void CServerNet::Tick()
{
	if (GAME_SERVER)
	{
		SYSTEMTIME * ps = SERVERINFO->GetServerTime();

		if (m_wTimeMinute != ps->wMinute)
		{
			PacketNetUsersOnline s;
			s.iLength = sizeof(PacketNetUsersOnline);
			s.iHeader = PKTHDR_NetUsersOnline;
			s.iID = SERVER_CODE - 1;
			s.iUsersOnline = USERS_ONLINE;

			NetConnection * nc = GetLoginServerConnection();
			if (nc)
				SendPacket(nc->pcSocketData, &s);

			m_wTimeMinute = ps->wMinute;
		}
	}
}
void CServerNet::ConnectAll()
{
	for (auto &nc : m_vpNetConnections)
	{
		Connect(nc);
	}
}

void CServerNet::Connect(NetConnection * nc)
{
	nc->pcSocketData = SERVERSOCKET->Connect(nc->szIP, nc->iPort);

	if (nc->pcSocketData)
	{
		User * u = nc->pcSocketData->u;

		if (u)
		{
			u->bNetServer = TRUE;
			nc->pcSocketData->bKeepAlive = TRUE;
		}

		PacketNetIdentifier sPacket;
		sPacket.iLength = sizeof(PacketNetIdentifier);
		sPacket.iHeader = PKTHDR_NetIdentifier;
		sPacket.iServerID = SERVER_CODE;
		sPacket.iPort = SERVER_PORT;
		sPacket.uPasswordNUM = 0x33445566;

		SendPacket(nc->pcSocketData, &sPacket);
	}
}
void CServerNet::DisconnectAll()
{
	for (auto &nc : m_vpNetConnections)
	{
		Disconnect(nc);
	}
}
void CServerNet::Disconnect(NetConnection *nc)
{ 
	if (nc && nc->pcSocketData)
	{
		DisconnectUser(nc->pcSocketData);
	}
}
void CServerNet::DisconnectUser(SocketData *pcSocketData)
{
	if (pcSocketData)
	{
		if (pcSocketData->u && pcSocketData->u->bNetServer)
		{
			WRITEDBG("NET SERVER TRIED DC %p", _ReturnAddress());
			return;
		}
		if (SERVERNET->GetNetConnectionBySocketData(pcSocketData) != NULL)
		{
			WRITEDBG("NET SERVER TRIED DC %p", _ReturnAddress());
			return;
		}
		WNDPROC_SOCKETCLOSE(SERVERSOCKET->GetHWND(), pcSocketData);
	}
}
void CServerNet::SendPacket(class SocketData * pcSocketData, void * packet)
{
	if (pcSocketData)
		pcSocketData->SendPacket((Packet *)packet, FALSE);
}
void CServerNet::AddConnection(char * pszIP, int iPort, int iServerType)
{
	NetConnection *psClient = new NetConnection;

	STRINGCOPY(psClient->szIP, pszIP);
	psClient->iPort = iPort;
	psClient->iServerType = iServerType;
	psClient->pcSocketData = NULL;

	m_vpNetConnections.push_back(psClient);
}
NetConnection * CServerNet::AddNetConnection(class SocketData *pcSocketData)
{
	NetConnection *psClient = new NetConnection;

	STRINGCOPY(psClient->szIP,pcSocketData->szIP);
	psClient->iPort = 0;
	psClient->iServerType = GAME_SERVER == TRUE ? 0 : -1;
	psClient->pcSocketData = pcSocketData;

	m_vpNetConnections.push_back(psClient);

	return psClient;
}
BOOL CServerNet::Disconnected(class SocketData *sd)
{
	for (auto &nc : m_vpNetConnections)
	{
		if (nc->pcSocketData == sd)
		{
			nc->pcSocketData = nullptr;

			Connect(nc);

			return TRUE;
		}
	}

	return FALSE;
}
NetConnection *CServerNet::GetLoginServerConnection()
{
	for (auto &nc : m_vpNetConnections)
	{
		if (nc->iServerType == 0)
			return nc;
	}

	return nullptr;
}
NetConnection * CServerNet::GetNetConnectionBySocketData(SocketData *sd)
{
	for (auto &nc : m_vpNetConnections)
	{
		if (nc->pcSocketData == sd)
			return nc;
	}

	return NULL;
}
void CServerNet::SendPacketGameServers(void *packet)
{
	for (auto &nc : m_vpNetConnections)
	{
		if (nc->iServerType != 0 && nc->iServerType != -1)
			SendPacket(nc->pcSocketData, packet);
	}
}

//Login Server receive from gameserver
void CServerNet::OnReceiveServer(User * pcUserDataServer, void * pPacket)
{
	NetConnection *nc = nullptr;

	if (pcUserDataServer)
	{
		nc = GetNetConnectionBySocketData(pcUserDataServer->pcSocketData);

		if (nc == nullptr)
			nc = AddNetConnection(pcUserDataServer->pcSocketData);

		if (nc == nullptr)
			return;
	}

	int iPacketID = ((Packet *)pPacket)->iHeader;

	if (iPacketID == PKTHDR_NetIdentifier)
	{
		PacketNetIdentifier *pPackets = (PacketNetIdentifier *)pPacket;
		for (auto &ncit : m_vpNetConnections)
		{
			if ((ncit->iServerType == pPackets->iServerID) && (pPackets->uPasswordNUM == 0x33445566))
			{
				nc->iPort = pPackets->iPort;
				ncit->pcSocketData = nc->pcSocketData;
				pcUserDataServer->bNetServer = TRUE;
				pcUserDataServer->pcSocketData->bKeepAlive = TRUE;
				m_vpNetConnections.pop_back();
				return;
			}
		}

		nc->iServerType = pPackets->iServerID;
		nc->iPort = pPackets->iPort;
		pcUserDataServer->bNetServer = TRUE;
		pcUserDataServer->bKeepAlive = TRUE;
		return;
	}

	switch (iPacketID)
	{
		// BC
	case PKTHDR_NetBCStatusReq:
		SERVERBLESSCASTLE->NetSendBlessCastleStatus(nc);
		break;
	case PKTHDR_NetBCStatusSnd:
		SERVERBLESSCASTLE->NetRecvBlessCastleStatus((PacketNetBCStatus*)pPacket);
		break;
	case PKTHDR_NetBCNewOwnerClanID:
		SERVERBLESSCASTLE->SetBlessCastleOwnerClanID(((PacketNetBCNewOwnerClanID*)pPacket)->dwNewClanID);
		break;

		//Experience
	case PKTHDR_NetExp:
	{
		PacketNetExp *pPackets = (PacketNetExp *)pPacket;

		User * pcUser = SERVERUSER->GetUser(pPackets->uObjectID);

		if (pcUser)
		{
			SERVERCHARACTER->SetExp(pcUser, pPackets->iExp);
		}
	}
		break;
	case PKTHDR_NetGiveExp:
	{
		PacketNetExp *pPackets = (PacketNetExp *)pPacket;

		User * pcUser = SERVERUSER->GetUser(pPackets->uObjectID);

		if (pcUser)
		{
			SERVERCHARACTER->GiveEXP(pcUser, pPackets->iExp);
		}
	}
		break;
	case PKTHDR_NetGameMaster:
	{
		PacketNetGameMaster *pPackets = (PacketNetGameMaster *)pPacket;

		User *pcUser = SERVERUSER->GetUser(pPackets->uObjectID);

		if (pcUser)
		{
			pcUser->iGameLevel = (EGameLevel)pPackets->iGameMasterLevel;

			SERVERCHARACTER->GiveGameMaster(pcUser, pcUser->iGameLevel);

			SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Error, "> GM Level [%d] Activated!", pcUser->iGameLevel);
		}
	}
		break;

	case PKTHDR_NetGetGameMaster:
	{
		PacketNetGetGameMaster *pPackets = (PacketNetGetGameMaster *)pPacket;

		User *pcUser = SERVERUSER->GetUser(pPackets->szName);

		if (pcUser)
		{
			pPackets->iGameMasterLevel = pcUser->iGameLevel;

			SendPacket(nc->pcSocketData, pPacket);
		}
	}
		break;

	case PKTHDR_NetDisconnectUser:
	{
		PacketNetGameMaster *pPackets = (PacketNetGameMaster *)pPacket;

		User *pcUser = SERVERUSER->GetUser(pPackets->uObjectID);

		if (pcUser && pcUser->pcSocketData)
		{
			if (pcUser->iID)
				SERVERUSER->AddReconnectUser(pcUser);

			SERVERACCOUNT->DisconnectUser(pcUser);
			SERVERLOG->LogSocketClose(pcUser->pcSocketData, "NetServer::OnReceiveServer(PKTHDR_NetDisconnectUser)", _ReturnAddress());

			WNDPROC_SOCKETCLOSE(SERVERSOCKET->GetHWND(), pcUser->pcSocketData);
		}
	}
		break;

	case PKTHDR_NetForceOrb:
	{
		PacketNetForceOrbTime *pPackets = (PacketNetForceOrbTime *)pPacket;

		User *pcUser = SERVERUSER->GetUser(pPackets->dwObjectID);

		if (pcUser && pcUser->pcSocketData)
		{
			pcUser->dwForceOrb_SaveTime = pPackets->dwTime;
		}
	}
		break;
	case PKTHDR_NetPremiumEXP:
	{
		PacketNetEXPPotion *pPackets = (PacketNetEXPPotion *)pPacket;

		User *pcUser = SERVERUSER->GetUser(pPackets->dwObjectID);

		if (pcUser && pcUser->pcSocketData)
		{
			pcUser->bEXPPotion = pPackets->bExp;
		}

	}
		break;
	case PKTHDR_NetCharacterSync:
	{
		PacketNetCharacterSync *pPackets = (PacketNetCharacterSync *)pPacket;

		User *pcUser = SERVERUSER->GetUser(pPackets->dwObjectID);

		if (pcUser && pcUser->pcSocketData)
		{
			STRINGCOPY(pcUser->szCharacterName, pPackets->szCharName);
		}
	}
		break;
	case PKTHDR_NetGiveGold:
	{
		PacketNetGold *pPackets = (PacketNetGold *)pPacket;

		User * pcUser = SERVERUSER->GetUser(pPackets->uObjectID);

		if (pcUser)
		{
			SERVERCHARACTER->GiveGold(pcUser, pPackets->iGold);
		}
	}
		break;
	}
}
void CServerNet::OnReceiveClient(User * pcUserDataServer, void * pPacket)
{
	NetConnection *nc = nullptr;

	if (pcUserDataServer)
	{
		nc = GetNetConnectionBySocketData(pcUserDataServer->pcSocketData);

		if (nc == nullptr)
			nc = AddNetConnection(pcUserDataServer->pcSocketData);

		if (nc == nullptr)
			return;
	}

	int iPacketID = ((Packet *)pPacket)->iHeader;

	if (iPacketID == PKTHDR_NetIdentifier)
	{
		PacketNetIdentifier *pPackets = (PacketNetIdentifier *)pPacket;
		for (auto &ncit : m_vpNetConnections)
		{
			if ((ncit->iServerType == pPackets->iServerID) && (pPackets->uPasswordNUM == 0x33445566))
			{
				nc->iPort = pPackets->iPort;
				ncit->pcSocketData = nc->pcSocketData;
				pcUserDataServer->bNetServer = TRUE;
				pcUserDataServer->pcSocketData->bKeepAlive = TRUE;
				m_vpNetConnections.pop_back();
				return;
			}
		}

		nc->iServerType = pPackets->iServerID;
		nc->iPort = pPackets->iPort;
		pcUserDataServer->bNetServer = TRUE;
		pcUserDataServer->bKeepAlive = TRUE;
		return;
	}

	switch (iPacketID)
	{
		//Bless Castle
	case PKTHDR_NetBCStatusReq:
		SERVERBLESSCASTLE->NetSendBlessCastleStatus(nc);
		break;
	case PKTHDR_NetBCStatusSnd:
		SERVERBLESSCASTLE->NetRecvBlessCastleStatus((PacketNetBCStatus*)pPacket);
		break;
	case PKTHDR_NetBCNewOwnerClanID:
		SERVERBLESSCASTLE->SetBlessCastleOwnerClanID(((PacketNetBCNewOwnerClanID*)pPacket)->dwNewClanID);
		break;
	case PKTHDR_NetDisconnectUser:
	{
		PacketNetGameMaster *pPackets = (PacketNetGameMaster *)pPacket;

		User *pcUser = SERVERUSER->GetUser(pPackets->uObjectID);

		if (pcUser)
		{
			pcUser->bDisconnectNet = TRUE;

			if (pcUser->iID)
				SERVERUSER->AddReconnectUser(pcUser);

			SERVERACCOUNT->DisconnectUser(pcUser);
			SERVERLOG->LogSocketClose(pcUser->pcSocketData, "NetServer::OnReceiveServer(PKTHDR_NetDisconnectUser)", _ReturnAddress());

			WNDPROC_SOCKETCLOSE(SERVERSOCKET->GetHWND(), pcUser->pcSocketData);
		}
	}
		break;
	case PKTHDR_NetGetExp:
	{
		PacketNetGetExp *pPackets = (PacketNetGetExp *)pPacket;

		User *pcUser = SERVERUSER->GetUser(pPackets->uObjectID);

		if (pcUser)
		{
			SERVERNET->SendExp(pcUser, SERVERCHARACTER->GetExp(pcUser));
			SERVERNET->SendClan(pcUser);
		}
	}
		break;
	case PKTHDR_NetExp:
	{
		PacketNetExp *pPackets = (PacketNetExp *)pPacket;

		User *pcUser = SERVERUSER->GetUser(pPackets->uObjectID);

		if (pcUser)
		{
			SERVERCHARACTER->SetExp(pcUser, pPackets->iExp);
		}
	}
		break;
	case PKTHDR_NetGetGameMaster:
	{
		PacketNetGetGameMaster *pPackets = (PacketNetGetGameMaster *)pPacket;

		User *pcUser = SERVERUSER->GetUser(pPackets->szName);

		if (pcUser)
		{
			pcUser->iGameLevel = (EGameLevel)pPackets->iGameMasterLevel;

			if (pcUser->iGameLevel > GAMELEVEL_None)
				SERVERCHAT->SendChatEx(pcUser, CHATCOLOR_Error, "> GM Level Sync [%d] Activated!", pcUser->iGameLevel);

			SERVERCHARACTER->GiveGameMaster(pcUser, pcUser->iGameLevel);
		}
	}
		break;
	case PKTHDR_NetUnloadUser:
	{
		PacketNetUnloadUser *pPackets = (PacketNetUnloadUser *)pPacket;

		User *pcUser = SERVERUSER->GetUser(pPackets->dwObjectID);

		if (pcUser)
		{
			SERVERUSER->OnUnLoadUser(pcUser);
		}
	}
		break;
	case PKTHDR_NetPremium:
	{
		PacketNetPremium *pPackets = (PacketNetPremium *)pPacket;

		User *pcUser = SERVERUSER->GetUser(pPackets->uObjectID);

		if (pcUser)
		{
			SERVERITEM->AddPremiumUse(pcUser, &pPackets->sItem);
		}
	}
		break;
	}
}
void CServerNet::OnReceivePacket(User * pcUser, void * pPacket)
{
	int iPacketID = ((Packet*)pPacket)->iHeader;

	if ((iPacketID & 0xFF000000) == 0x7F000000)
	{
		if (!GAME_SERVER)
			OnReceiveServer(pcUser, pPacket);
		else
			OnReceiveClient(pcUser, pPacket);
	}
}
void CServerNet::SendExp(User *pcUser, INT64 iExp)
{
	if (pcUser && GAME_SERVER)
	{
		PacketNetExp sPacket;
		sPacket.iLength = sizeof(PacketNetExp);
		sPacket.iHeader = PKTHDR_NetExp;
		sPacket.uObjectID = pcUser->iID;
		sPacket.iExp = iExp;
		NetConnection * nc = GetLoginServerConnection();
		if (nc)
			SendPacket(nc->pcSocketData, &sPacket);
	}
}
void CServerNet::GiveEXP(User *pcUser, INT64 iExp)
{
	if (pcUser && GAME_SERVER)
	{
		PacketNetExp sPacket;
		sPacket.iLength = sizeof(PacketNetExp);
		sPacket.iHeader = PKTHDR_NetGiveExp;
		sPacket.uObjectID = pcUser->iID;
		sPacket.iExp = iExp;
		NetConnection * nc = GetLoginServerConnection();
		if (nc)
			SendPacket(nc->pcSocketData, &sPacket);
	}
}
void CServerNet::GiveGold(User *pcUser, int iGold)
{
	if (pcUser && GAME_SERVER)
	{
		PacketNetGold sPacket;
		sPacket.iLength = sizeof(PacketNetGold);
		sPacket.iHeader = PKTHDR_NetGiveGold;
		sPacket.uObjectID = pcUser->iID;
		sPacket.iGold = iGold;
		NetConnection * nc = GetLoginServerConnection();
		if (nc)
			SendPacket(nc->pcSocketData, &sPacket);
	}
}
void CServerNet::SendExpLogin(User *pcUser, INT64 iExp)
{
	if (pcUser)
	{
		PacketNetExp sPacket;
		sPacket.iLength = sizeof(PacketNetExp);
		sPacket.iHeader = PKTHDR_NetExp;
		sPacket.uObjectID = pcUser->iID;
		sPacket.iExp = iExp;
		SendPacketGameServers(&sPacket);
	}
}
void CServerNet::SendForceOrb(User * pcUser, BOOL bCity)
{
	if (pcUser && GAME_SERVER)
	{
		PacketNetForceOrbTime sPacket;
		sPacket.iLength = sizeof(PacketNetForceOrbTime);
		sPacket.iHeader = PKTHDR_NetForceOrb;
		sPacket.dwObjectID = pcUser->iID;
		sPacket.bUpdate = bCity;
		sPacket.dwTime = pcUser->iForceOrbTime;
		NetConnection * nc = GetLoginServerConnection();
		if (nc)
			SendPacket(nc->pcSocketData, &sPacket);
	}
}
void CServerNet::SendEXPPotion(User * pcUser, BOOL bEXPPotion)
{
	if (pcUser && GAME_SERVER)
	{
		PacketNetEXPPotion sPacket;
		sPacket.iLength = sizeof(PacketNetEXPPotion);
		sPacket.iHeader = PKTHDR_NetPremiumEXP;
		sPacket.dwObjectID = pcUser->iID;
		sPacket.bExp = bEXPPotion;
		NetConnection * nc = GetLoginServerConnection();
		if (nc)
			SendPacket(nc->pcSocketData, &sPacket);
	}
}
void CServerNet::SendEXPEventLogin(int iPercent)
{
	PacketNetExpEvent s;
	s.iLength = sizeof(PacketNetExpEvent);
	s.iHeader = PKTHDR_NetEXPEvent;
	s.iPercent = iPercent;
	SendPacketGameServers(&s);
}
void CServerNet::SendClan(User *pcUser)
{
	if (pcUser && GAME_SERVER)
	{
		PacketNetClan sPacket;
		sPacket.iLength = sizeof(PacketNetClan);
		sPacket.iHeader = PKTHDR_NetClan;
		sPacket.uObjectID = pcUser->iID;
		sPacket.dwClan = pcUser->iClanID;
		NetConnection * nc = GetLoginServerConnection();
		if (nc)
			SendPacket(nc->pcSocketData, &sPacket);
	}
}
void CServerNet::SendSyncChar(User *pcUser)
{
	if (pcUser && GAME_SERVER)
	{
		PacketNetCharacterSync sPacket;
		sPacket.iLength = sizeof(PacketNetCharacterSync);
		sPacket.iHeader = PKTHDR_NetCharacterSync;
		sPacket.dwObjectID = pcUser->iID;
		STRINGCOPY(sPacket.szCharName, pcUser->sCharacterData.szName);
		NetConnection * nc = GetLoginServerConnection();
		if (nc)
			SendPacket(nc->pcSocketData, &sPacket);
	}
}
void CServerNet::DisconnectUser(User *pcUser)
{
	if (pcUser)
	{
		PacketNetDisconnectUser sPacket;
		sPacket.iLength = sizeof(PacketNetDisconnectUser);
		sPacket.iHeader = PKTHDR_NetDisconnectUser;
		sPacket.dwObjectID = pcUser->iID;
		if (GAME_SERVER)
		{
			NetConnection * nc = GetLoginServerConnection();
			if (nc)
				SendPacket(nc->pcSocketData, &sPacket);
		}
		else
			SendPacketGameServers(&sPacket);
	}
}
void CServerNet::OnUnloadUser(User * pcUser)
{
	if (pcUser && !GAME_SERVER)
	{
		PacketNetUnloadUser sPacket;
		sPacket.iLength = sizeof(PacketNetUnloadUser);
		sPacket.iHeader = PKTHDR_NetUnloadUser;
		sPacket.dwObjectID = pcUser->iID;
		SendPacketGameServers(&sPacket);
	}
}
void CServerNet::SendGameMaster(User * pcUser)
{
	if (pcUser)
	{
		PacketNetGameMaster sPacket;
		sPacket.iLength = sizeof(PacketNetGameMaster);
		sPacket.iHeader = PKTHDR_NetGameMaster;
		sPacket.uObjectID = pcUser->iID;
		sPacket.iGameMasterLevel = pcUser->iGameLevel;
		NetConnection * nc = GetLoginServerConnection();
		if (nc)
			SendPacket(nc->pcSocketData, &sPacket);
	}
}
void CServerNet::GetGameMaster(User * pcUser)
{
	if (pcUser && GAME_SERVER)
	{
		PacketNetGetGameMaster sPacket;
		sPacket.iLength = sizeof(PacketNetGetGameMaster);
		sPacket.iHeader = PKTHDR_NetGetGameMaster;
		sPacket.uObjectID = pcUser->iID;
		sPacket.iGameMasterLevel = pcUser->iGameLevel;
		STRINGCOPY(sPacket.szName, pcUser->sCharacterData.szName);
		NetConnection * nc = GetLoginServerConnection();
		if (nc)
			SendPacket(nc->pcSocketData, &sPacket);
	}
}
void CServerNet::GetExp(User * pcUser)
{
	PacketNetGetExp sPacket;
	sPacket.iLength = sizeof(PacketNetGetExp);
	sPacket.iHeader = PKTHDR_NetGetExp;
	sPacket.uObjectID = pcUser->iID;
	SendPacketGameServers(&sPacket);
}
void CServerNet::SendVersion(int iVersion)
{
	PacketNetVersion sPacket;
	sPacket.iLength = sizeof(PacketNetVersion);
	sPacket.iHeader = PKTHDR_NetVersion;
	sPacket.iVersion = iVersion;
	SendPacketGameServers(&sPacket);
}
void CServerNet::SendPremium(User * pcUser, ItemPremium * psItem)
{
	PacketNetPremium sPacket;
	sPacket.iLength = sizeof(PacketNetPremium);
	sPacket.iHeader = PKTHDR_NetPremium;
	sPacket.uObjectID = pcUser->iID;
	CopyMemory(&sPacket.sItem, psItem, sizeof(ItemPremium));
	SendPacketGameServers(&sPacket);
}
void CServerNet::SendBlessCastleOwnerClanID(DWORD iClanID)
{
	if (GAME_SERVER)
	{
		PacketNetBCNewOwnerClanID sPacketNet;
		sPacketNet.iLength = sizeof(sPacketNet);
		sPacketNet.iHeader = PKTHDR_NetBCNewOwnerClanID;
		sPacketNet.dwNewClanID = iClanID;

		NetConnection * nc = GetLoginServerConnection();
		if (nc)
			SendPacket(nc->pcSocketData, &sPacketNet);
	}
}