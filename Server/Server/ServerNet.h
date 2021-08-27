#pragma once

struct NetConnection
{
	class SocketData		* pcSocketData;
	int						iServerType;
	char					szIP[32];
	int						iPort;
};

class CServerNet
{
public:
	CServerNet();
	virtual ~CServerNet();

	void Init();
	void Tick();

	void ConnectAll();
	void Connect(NetConnection * nc);
	void DisconnectAll();
	void Disconnect(NetConnection *nc);
	void DisconnectUser(SocketData *pcSocketData);
	void SendPacket(class SocketData * pcSocketData, void * packet);
	void AddConnection(char * pszIP, int iPort, int iServerType);
	NetConnection * AddNetConnection(class SocketData *pcSocketData);

	BOOL Disconnected(class SocketData *sd);
	NetConnection * GetLoginServerConnection();
	NetConnection * GetNetConnectionBySocketData(SocketData *sd);
	void SendPacketGameServers(void *packet);
	void OnReceiveServer(User * pcUserDataServer, void * pPacket);
	void OnReceiveClient(User * pcUserDataServer, void * pPacket);
	void SendExp(User *pcUser, INT64 iExp);
	void GiveEXP(User *pcUser, INT64 iExp);
	void GiveGold(User *pcUser, int iGold);
	void SendExpLogin(User *pcUser, INT64 iExp);
	void SendForceOrb(User * pcUser, BOOL bCity);
	void SendEXPPotion(User * pcUser, BOOL bEXPPotion);
	void SendEXPEventLogin(int iPercent);
	void SendClan(User *pcUser);
	void SendSyncChar(User *pcUser);
	void DisconnectUser(User *pcUser);
	void OnUnloadUser(User * pcUser);
	void SendGameMaster(User * pcUser);
	void GetGameMaster(User * pcUser);
	void GetExp(User * pcUser);
	void SendVersion(int iVersion);
	void SendPremium(User * pcUser, ItemPremium * psItem);
	void SendBlessCastleOwnerClanID(DWORD iClanID);

	void OnReceivePacket(User * pcUser, void * pPacket);
private:
	std::vector<NetConnection *> m_vpNetConnections;

	BOOL m_bInit = FALSE;
	WORD m_wTimeMinute = 0;
};
