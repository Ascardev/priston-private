#pragma once

#define NUM_RESERVED_SLOTS								10

#define MAX_DENYCONNECTIONS								256
#define MAX_BANCONNECTIONS								1024
#define MAX_RECONNECTCONNECTIONS						128

#define SOCKETACCEPT(s,a)			SERVERSOCKET->SocketAccept(s,a);
#define SOCKETPACKET(s,p)			SERVERSOCKET->SocketPacket(s,p);
#define SOCKETCLOSE(s)				SERVERSOCKET->SocketClose(s);

class CServerSocket
{
public:
	CServerSocket();
	virtual ~CServerSocket();

	void Init(HWND hwnd);
	void Listen(int iPort);
	SocketData *GetFreeSocketData();
	SocketData *GetSocketData(const char * pszIP, int iPort);
	SocketData *Connect(const char * pszIP, int iPort);

	static DWORD WINAPI Listener(SOCKET * ls);
	static DWORD WINAPI	Sender(SocketData * sd);
	static DWORD WINAPI	Receiver(SocketData * sd);
	static DWORD WINAPI DeniedSocketsHandler();

	BOOL AddDeniedSocket(SOCKET s);
	BOOL AddBanIP(DWORD dwIP);
	BOOL AddReconnectedUser(User * pcUser);
	void Load();
	void HandleReconnectedUsers();
	void HandleDeniedSockets();
	void HandleBanFirewall();
	void SocketAccept(SOCKET s, sockaddr_in * addr);
	void SocketPacket(SocketData * sd, PacketReceiving * p);
	void SocketClose(SocketData * sd);
	void SetPacketObfuscatorByte(BYTE b) { m_bPacketObfuscatorByte = b; }
	BYTE GetPacketObfuscatorByte() { return m_bPacketObfuscatorByte; }
	BOOL IsActive() { return m_bActive; }
	HWND GetHWND() { return m_hWnd; }
	HANDLE GetHandleEventSocket() { return m_hEventSocket; }
	BOOL IsFull() { return m_bSetFull; }
	void SetFull(BOOL b) { m_bSetFull = b; };
private:
	HWND m_hWnd;
	HANDLE m_hListener;
	BOOL m_bPacketObfuscatorByte;
	BOOL m_bActive = FALSE;
	BOOL m_bSetFull = FALSE;
	int m_iMaxConnections;
	int m_iNextSocket;
	SocketData *m_pcaSocketData = nullptr;
	HANDLE m_hEventSocket;
	CMutex *m_pcMutex = NULL;
	CMutex *m_pcAcceptMutex = NULL;
	CMutex *m_pcCloseMutex = NULL;
	SOCKET m_saSocket[MAX_DENYCONNECTIONS];
	SOCKET m_sListenSocket = INVALID_SOCKET;
	DWORD m_dwaIPListBan[MAX_BANCONNECTIONS];
	User *m_pcaReconnectedUsers[MAX_RECONNECTCONNECTIONS];
};