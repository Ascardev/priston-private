#include "StdAfx.h"
#include "ServerInfo.h"

CServerInfo::CServerInfo()
{
	m_strFileName = "server.ini";
}
CServerInfo::~CServerInfo()
{

}
void CServerInfo::Init()
{
	m_dwTimeServer = TICKCOUNT;
}
void CServerInfo::Load()
{
	CFILE::Ini cConfigReader(m_strFileName);

	m_iGameVersion = cConfigReader.ReadInt("Server", "Version");
	m_iServerVersion = cConfigReader.ReadInt("Server", "Version");

	m_iServers = cConfigReader.ReadInt("Server", "GameServers") + 1;

	std::string strType = cConfigReader.ReadString("Server", "Type");

	int  iID = cConfigReader.ReadInt(strType.c_str(), "ID");

	m_iServerCode = iID;

	if (iID >= 0)
	{
		LoadServerInfo(m_saServerInfo + 0, SERVERTYPE_Login, "LoginServer");

		for (int i = 1; i < m_iServers; i++)
		{
			LoadServerInfo(m_saServerInfo + i, SERVERTYPE_Game, FormatString("GameServer%d", i));
		}
	}
	else
	{
		m_iServerCode = iID = 0;

		LoadServerInfo(m_saServerInfo + 0, SERVERTYPE_Multi, "LoginServer");

		for (int i = 1; i < m_iServers; i++)
		{
			LoadServerInfo(m_saServerInfo + i, SERVERTYPE_Game, FormatString("GameServer%d", i));
		}
	}

	for (int i = 0; i < m_iServers; i++)
	{
		ServerInfo *p = m_saServerInfo + i;

		if (i != iID)
		{
			SERVERNET->AddConnection(p->szNetIP, p->iPort, i);
		}
	}

	m_psServerInfo = m_saServerInfo + iID;
	m_iServerType = m_psServerInfo->iType;

	switch (m_iServerType)
	{
	case SERVERTYPE_Login:
		m_bLoginServer = TRUE;
		m_bGameServer = FALSE;
		break;
	case SERVERTYPE_Game:
		m_bLoginServer = FALSE;
		m_bGameServer = TRUE;
		break;
	case SERVERTYPE_Multi:
		m_bLoginServer = TRUE;
		m_bGameServer = TRUE;
		break;
	}

	LoadServerEvent();

	LoadServerSQL();
}

void CServerInfo::LoadServerInfo(ServerInfo *si, EServerType eServerType, const char *pszSection)
{
	CFILE::Ini cConfigReader(m_strFileName);

	//Server Type
	si->iType = eServerType;

	//Name
	STRINGCOPY(si->szName, cConfigReader.ReadString(pszSection, "Name").c_str());

	//IP1
	si->lIP.S_un.S_addr = inet_addr(cConfigReader.ReadString(pszSection, "IP").c_str());
	STRINGCOPY(si->szIP, inet_ntoa(si->lIP));

	//IP2
	si->lIP2.S_un.S_addr = inet_addr(cConfigReader.ReadString(pszSection, "IP2").c_str());
	STRINGCOPY(si->szIP2, inet_ntoa(si->lIP2));

	//IP3
	si->lIP3.S_un.S_addr = inet_addr(cConfigReader.ReadString(pszSection, "IP3").c_str());
	STRINGCOPY(si->szIP3, inet_ntoa(si->lIP3));

	//IP Net
	si->lNetIP.S_un.S_addr = inet_addr(cConfigReader.ReadString(pszSection, "NetIP").c_str());
	STRINGCOPY(si->szNetIP, inet_ntoa(si->lNetIP));

	//port
	si->iPort = cConfigReader.ReadInt(pszSection, "Port");

	si->iMaxUsers = cConfigReader.ReadInt(pszSection, "MaxUsers");
}
void CServerInfo::LoadServerEvent()
{
	if (GAME_SERVER)
	{
		CFILE::Ini cConfigReader(m_strFileName);

		ZeroMemory(&m_saServerEvent, sizeof(ServerEvent));

		m_saServerEvent.iRate_Exp = cConfigReader.ReadInt("Event", "RateExp");

		//Bless Castle
		if (cConfigReader.ReadOnOff("Event", "SiegeWar"))
		{
			m_saServerEvent.iEvent_BlessCastle = 1;
			m_saServerEvent.iEvent_BlessCastle_Day = cConfigReader.ReadInt("Event", "SiegeWarDay");
			m_saServerEvent.iEvent_BlessCastle_Hour = cConfigReader.ReadInt("Event", "SiegeWarHour");
		}

		//Xmas
		if (cConfigReader.ReadOnOff("Event", "Xmas"))
		{
			m_saServerEvent.iEvent_XMas = TRUE;
			m_saServerEvent.iEvent_XMas_Rate = cConfigReader.ReadInt("Event", "XmasPercent");
			m_saServerEvent.iEvent_XMas_ExpMap = cConfigReader.ReadInt("Event", "XmasEXPMapPercent");
		}
		//PVP
		if (cConfigReader.ReadOnOff("Event", "Pvp"))
		{
			m_saServerEvent.iEvent_Pvp = TRUE;
		}
	}
}
void CServerInfo::LoadServerSQL()
{
	CFILE::Ini cConfigReader(m_strFileName);

	STRINGCOPY(m_saServerSQL.szHost, cConfigReader.ReadString("Database", "Host").c_str());
	STRINGCOPY(m_saServerSQL.szUser, cConfigReader.ReadString("Database", "User").c_str());
	STRINGCOPY(m_saServerSQL.szPassword, cConfigReader.ReadString("Database", "Password").c_str());
}
void CServerInfo::LoadGameMaster()
{

}
void CServerInfo::PHServerList(SocketData * pcSocketData, int iTicket)
{
	if (m_sPacketServerList.iHeader != PKTHDR_ServerList)
	{
		m_sPacketServerList.iLength = sizeof(Packet) + sizeof(PacketServerList::Header);
		m_sPacketServerList.iHeader = PKTHDR_ServerList;

		STRINGCOPY(m_sPacketServerList.sHeader.szServerName, m_psServerInfo->szName);

		int j = 0;
		for (int i = 0; (i < m_iServers) && (j < (_countof(m_sPacketServerList.sServers) - 1)); i++)
		{
			ServerInfo * p = m_saServerInfo + i;

			if (p->iType == SERVERTYPE_Game)
			{
				STRINGCOPY(m_sPacketServerList.sServers[j].szName,  p->szName);

				STRINGCOPY(m_sPacketServerList.sServers[j].szaIP[0],  p->szIP);
				STRINGCOPY(m_sPacketServerList.sServers[j].szaIP[1],  p->szIP2);
				STRINGCOPY(m_sPacketServerList.sServers[j].szaIP[2],  p->szIP3);

				m_sPacketServerList.sServers[j].iaPort[0] = p->iPort;
				m_sPacketServerList.sServers[j].iaPort[1] = p->iPort;
				m_sPacketServerList.sServers[j].iaPort[2] = p->iPort;
				m_sPacketServerList.sServers[j].iaPort[3] = 0;

				j++;
			}
		}

		m_sPacketServerList.sHeader.iGameServers = j;
		m_sPacketServerList.sHeader.iClanServerIndex = j;

		STRINGCOPY(m_sPacketServerList.sServers[j].szName, "clan");

		STRINGCOPY(m_sPacketServerList.sServers[j].szaIP[0], m_saServerInfo[0].szIP);
		STRINGCOPY(m_sPacketServerList.sServers[j].szaIP[1], m_saServerInfo[0].szIP2);
		STRINGCOPY(m_sPacketServerList.sServers[j].szaIP[2], m_saServerInfo[0].szIP3);

		m_sPacketServerList.sServers[j].iaPort[0] = 80;
		m_sPacketServerList.sServers[j].iaPort[1] = m_saServerInfo[0].iPort;
		m_sPacketServerList.sServers[j].iaPort[2] = m_saServerInfo[0].iPort;
		m_sPacketServerList.sServers[j].iaPort[3] = 0;

		m_sPacketServerList.iLength += ((sizeof(PacketServerList::Server) * m_sPacketServerList.sHeader.iGameServers) + (sizeof(PacketServerList::Server) * (m_sPacketServerList.sHeader.iClanServerIndex != 0 ? 1 : 0)));
	}

	m_sPacketServerList.sHeader.iTicket = iTicket;

	m_sPacketServerList.sHeader.dwTime = (DWORD)(SERVER_LOCATIME);
	m_sPacketServerList.sHeader.dwUnknown = GetGMTime(SERVER_LOCATIME);

	pcSocketData->SendPacket(&m_sPacketServerList);
}
char *CServerInfo::GetServerName(int iIndex)
{
	if ((iIndex >= 0) && (iIndex < MAX_SERVERINFO))
		return m_saServerInfo[iIndex].szName;

	return "";
}

SYSTEMTIME *CServerInfo::GetServerTime()
{
	GetLocalTime(&m_sLocalTimeServer);

	return &m_sLocalTimeServer;
}
void CServerInfo::Update()
{
	m_dwTimeServer = TICKCOUNT;
}
void CServerInfo::UpdateSystemTime()
{
	_time32(&m_tTime);
}