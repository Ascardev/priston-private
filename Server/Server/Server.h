#pragma once

#define SERVER_MUTEX				(GSERVER->GetMutex())
#define SERVERINFO					(GSERVER->GetServerInfo())
#define SERVERSOCKET				(GSERVER->GetServerSocket())
#define SERVERUSER					(GSERVER->GetServerUser())
#define SERVERCHARACTER				(GSERVER->GetServerCharacter())
#define SERVERUNIT					(GSERVER->GetServerUnit())
#define SERVERMAP					(GSERVER->GetServerMap())
#define SERVERCHAT					(GSERVER->GetServerChat())
#define SERVERITEM					(GSERVER->GetServerItem())
#define SERVERNET					(GSERVER->GetServerNet())
#define SERVERPACKET				(GSERVER->GetServerPacket())
#define SERVERPVP					(GSERVER->GetServerPvP())
#define SERVERACCOUNT				(GSERVER->GetServerAccount())
#define SERVERLOG					(GSERVER->GetServerLog())
#define SERVERCOMMAND				(GSERVER->GetServerCommand())
#define SERVERUSERINFO				(GSERVER->GetServerUserInfo())
#define SERVERBLLATRA				(GSERVER->GetServerBellatra())
#define SERVERBLESSCASTLE			(GSERVER->GetServerBlessCastle())

class CServer : public CServerCore
{
public:
	CServer();
	virtual ~CServer();

	void CreateSQLConnection(EDatabaseID eID);
	void CloseSQLConnection(EDatabaseID eID);

	void Init(HWND hwnd);
	void Shutdown();
	void Load();
	void Update(double fTime);
	void Tick(ETickType iTickType);
	void Loop();
	void Begin();
	void End();

	CServerInfo *GetServerInfo() { return m_pcServerInfo; }
	CServerSocket *GetServerSocket() { return m_pcServerSocket; }
	CServerUser *GetServerUser() { return m_pcServerUser; }
	CServerCharacter *GetServerCharacter() { return m_pcServerCharacter; }
	CServerUnit *GetServerUnit() { return m_pcServerUnit; }
	CServerMap * GetServerMap() { return m_pcServerMap; }
	CServerChat * GetServerChat() { return m_pcServerChat; }
	CServerItem * GetServerItem() { return m_pcServerItem; }
	CServerNet * GetServerNet() { return m_pcServerNet; }
	CServerPacket * GetServerPacket() { return m_pcServerPacket; }
	CServerPvP * GetServerPvP() { return m_pcServerPvP; }
	CServerAccount * GetServerAccount() { return m_pcServerAccount; }
	CServerLog * GetServerLog() { return m_pcServerLog; }
	CServerCommand * GetServerCommand() { return m_pcServerCommand; }
	CServerUserInfo * GetServerUserInfo() { return m_pcServerUserInfo; }
	CServerBellatra * GetServerBellatra() { return m_pcServerBellatra; }
	CServerBlessCastle * GetServerBlessCastle() { return m_pcServerBlessCastle; }

	void StartMaintenanceCountdown(int iSeconds);
	void StopMaintenanceCountdown();

	BOOL GetMaintenance() { return m_bMaintenance; }
	void SetMaintenance(BOOL bOn) { m_bMaintenance = bOn; }

	CMutex *GetMutex() { return m_pcMutex; }
protected:
	void AnnounceMaintenanceCountdown();
	void LoadSQL();
	void ClearSQL();
private:
	CServerInfo * m_pcServerInfo = nullptr;
	CServerSocket *m_pcServerSocket = nullptr;
	CServerUser *m_pcServerUser = nullptr;
	CServerCharacter *m_pcServerCharacter = nullptr;
	CServerUnit *m_pcServerUnit = nullptr;
	CServerMap *m_pcServerMap = nullptr;
	CServerChat * m_pcServerChat = nullptr;
	CServerItem * m_pcServerItem = nullptr;
	CServerNet *m_pcServerNet = nullptr;
	CServerPacket * m_pcServerPacket = nullptr;
	CServerPvP *m_pcServerPvP = nullptr;
	CServerAccount * m_pcServerAccount = nullptr;
	CServerLog * m_pcServerLog = nullptr;
	CServerCommand * m_pcServerCommand = nullptr;
	CServerUserInfo * m_pcServerUserInfo = nullptr;
	CServerBellatra * m_pcServerBellatra = nullptr;
	CServerBlessCastle * m_pcServerBlessCastle = nullptr;
private:
	HWND m_hWnd = nullptr;
	BOOL m_bMaintenanceCountdown = FALSE;
	int  m_iMaintenanceCountdown = 0;
	CMutex *m_pcMutex = nullptr;
	BOOL m_bMaintenance = FALSE;
};