#pragma once

#define SERVER_NAME				(SERVERINFO->GetServerInfo()->szName)
#define SERVER_PORT				(SERVERINFO->GetServerInfo()->iPort)
#define MAX_USERS				(SERVERINFO->GetServerInfo()->iMaxUsers)
#define LOGIN_SERVER			(SERVERINFO->GetLoginServer())
#define GAME_SERVER				(SERVERINFO->GetGameServer())
#define SERVER_TYPE				(SERVERINFO->GetServerType())
#define SERVER_VERSION			(SERVERINFO->GetVersion())
#define SERVER_CODE				(SERVERINFO->GetServerCode())
#define SERVER_GAMETIME			(SERVERINFO->GetTime())
#define SERVER_LOCATIME			(SERVERINFO->GetSystemTime())

//Event

//Exp
#define RATE_EXP				(SERVERINFO->GetEvent()->iRate_Exp)
//Bless Castle
#define EVENT_BLESSCASTLE		(SERVERINFO->GetEvent()->iEvent_BlessCastle)
#define EVENT_BLESSCASTLE_DAY	(SERVERINFO->GetEvent()->iEvent_BlessCastle_Day)
#define EVENT_BLESSCASTLE_HOUR	(SERVERINFO->GetEvent()->iEvent_BlessCastle_Hour)
//Xmas
#define EVENT_XMAS				(SERVERINFO->GetEvent()->iEvent_XMas)
#define RATE_XMAS				(SERVERINFO->GetEvent()->iEvent_XMas_Rate)
#define RATE_XMAS_EXPMAP		(SERVERINFO->GetEvent()->iEvent_XMas_ExpMap)

//PVP
#define EVENT_PVP				(SERVERINFO->GetEvent()->iEvent_Pvp)


class CServerInfo
{
public:
	CServerInfo();
	virtual ~CServerInfo();

	void Init();
	void Load();

	void PHServerList(SocketData * pcSocketData, int iTicket);

	void Update();

	std::string GetConfigFile() { return m_strFileName; }

	int GetVersion() { return m_iGameVersion; }
	int GetServerCode() { return m_iServerCode; }

	inline EServerType GetServerType() { return m_iServerType; }

	ServerInfo *GetServerInfo() { return m_psServerInfo; }
	BOOL GetLoginServer() { return m_bLoginServer; }
	BOOL GetGameServer() { return m_bGameServer; }

	char *GetServerName(int iIndex);

	ServerEvent *GetEvent() { return &m_saServerEvent; }

	ServerSQL *GetSQL() { return &m_saServerSQL; }

	SYSTEMTIME *GetServerTime();

	__time32_t GetSystemTime() { return m_tTime; }

	void UpdateSystemTime();

	DWORD GetTime() { return m_dwTimeServer; }
protected:
	void LoadServerInfo(ServerInfo *si, EServerType eServerType, const char *pszSection);
	void LoadServerEvent();
	void LoadServerSQL();
	void LoadGameMaster();
private:
	std::string m_strFileName;

	EServerType m_iServerType;

	int m_iGameVersion = 0;
	int m_iServerVersion = 0;

	int m_iServers = 1;
	int m_iServerCode = 0;

	BOOL m_bLoginServer = FALSE;
	BOOL m_bGameServer = FALSE;

	ServerInfo m_saServerInfo[MAX_SERVERINFO];
	ServerInfo *m_psServerInfo;

	ServerEvent m_saServerEvent;
	ServerSQL m_saServerSQL;

	PacketServerList m_sPacketServerList;

	SYSTEMTIME m_sLocalTimeServer;
	DWORD m_dwTimeServer;

	__time32_t m_tTime;
};
