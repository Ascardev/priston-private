#pragma once

#define SOCKETL			(GAMESOCKET->pcSocketLogin)
#define SOCKETG			(GAMESOCKET->pcSocketGame)
#define SENDPACKETL		(GAMESOCKET->SendLoginServer)
#define SENDPACKETG		(GAMESOCKET->SendGameServer)
#define SENDPACKETALL	(GAMESOCKET->SendAllServer)

class CGameSocket
{
public:
	CGameSocket();
	virtual ~CGameSocket();
	void Init(HWND hwnd);
	void Shutdown();
	HWND GetHWND() { return m_hWnd; }
	BOOL IsActive() { return m_bActive; }

	void SetIPPort(const char * pszIP, int iPort);

	BOOL ConnectLogin(const char *pszIP, int iPort);
	BOOL ConnectGame(const char *pszIP, int iPort);

	void DisconnectFull();

	SocketData *GetFreeSocketData();
	SocketData *GetSocketData(const char *pszIP, int iPort);
	SocketData *Connect(const char *pszIP, int iPort);

	void SocketClose(SocketData *sd);
	void SocketPacket(SocketData *sd, struct PacketReceiving *p);

	void SendLoginServer(void * pData, BOOL bEncrypt = FALSE);
	void SendGameServer(void * pData, BOOL bEncrypt = FALSE);
	void SendAllServer(void * pData, BOOL bEncrypt = FALSE);

	void Connected();

	void PingConnections();

	void HandlePacket(SocketData * sd, PacketPing * psPacket);

	void Loop();

	static DWORD WINAPI Receiver(SocketData * sd);
	static DWORD WINAPI	Sender(SocketData * sd);
	static BOOL WINAPI CheckConnection();

	DWORD dwLastTickLogin = 0;
	DWORD dwLastTickGame = 0;

	int iReconnectLCOUNT = 0;
	int iReconnectGCOUNT = 0;

	BOOL bLoginServerReconnect = FALSE;
	BOOL bGameServerReconnect = FALSE;

	char szLoginIP[32] = { 0 };
	int iLoginPort = 0;

	char szGameIP[32] = { 0 };
	int iGamePort = 0;

	SocketData *pcSocketLogin = nullptr;
	SocketData *pcSocketGame = nullptr;

	int iDisconnectType = 0;
	int iDisconnectTime = 0;

	static struct PacketReceiving *psaPacketReceiving[100];
	static int iNextReceiver;
private:
	HWND m_hWnd = nullptr;
	int m_iMaxConnections = 0;
	BOOL m_bActive = FALSE;
	BOOL m_bSetFull = FALSE;
	BOOL m_bCanCheckConnection = FALSE;
	BOOL m_bInit = FALSE;
	SocketData *m_pcaSocketData = nullptr;
	CMutex *m_pcMutex = nullptr;
};
