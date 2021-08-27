#include "StdAfx.h"
#include "GameSocket.h"
#include "netplay.h"

CGameSocket::CGameSocket()
{
	WSADATA	wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	srand(GetTickCount());
}
CGameSocket::~CGameSocket()
{
	for (int i = 0; i < m_iMaxConnections; i++)
	{
		SocketData * sd = m_pcaSocketData + i;
		TerminateThread(sd->hReceiveThread, 0);
		TerminateThread(sd->hSendThread, 0);
	}
	DELETA(m_pcaSocketData);

	WSACleanup();
}
void CGameSocket::Init(HWND hwnd)
{
	m_hWnd = hwnd;
	m_pcMutex = new CMutex("Socket Game");
	m_iMaxConnections = 8;
	m_pcaSocketData = new SocketData[m_iMaxConnections];

	for (int i = 0; i < m_iMaxConnections; i++)
	{
		SocketData *sd = m_pcaSocketData + i;
		sd->pcThis = sd;
		sd->bInUse = false;
		sd->Prepare(500, 500);
		sd->hReceiveThread = CreateThread(NULL, KB16, (LPTHREAD_START_ROUTINE)&CGameSocket::Receiver, sd, STACK_SIZE_PARAM_IS_A_RESERVATION, NULL);
		sd->hSendThread = CreateThread(NULL, KB16, (LPTHREAD_START_ROUTINE)&CGameSocket::Sender, sd, STACK_SIZE_PARAM_IS_A_RESERVATION, NULL);
	}

	m_bActive = TRUE;
}
void CGameSocket::Shutdown()
{
	m_bActive = FALSE;
}
SocketData * CGameSocket::GetFreeSocketData()
{
	for (int i = 0; i < m_iMaxConnections; i++)
	{
		SocketData * sd = m_pcaSocketData + i;
		if (!sd->bInUse)
		{
			sd->Init();
			return sd;
		}
	}
	return nullptr;
}
SocketData *CGameSocket::GetSocketData(const char * pszIP, int iPort)
{
	for (int i = 0; i < m_iMaxConnections; i++)
	{
		SocketData * sd = m_pcaSocketData + i;
		if (sd->bInUse && STRINGCOMPARE(sd->szIP, pszIP) && sd->iPort == iPort)
		{
			return sd;
		}
	}

	return NULL;
}
BOOL CGameSocket::ConnectLogin(const char *pszIP, int iPort)
{
	SOCKETL = Connect(pszIP, iPort);

	return SOCKETL ? TRUE : FALSE;
}
BOOL CGameSocket::ConnectGame(const char *pszIP, int iPort)
{
	if (SOCKETG)
	{
		SocketClose(SOCKETG);
	}

	SOCKETG = Connect(pszIP, iPort);

	return SOCKETG ? TRUE : FALSE;
}
void CGameSocket::DisconnectFull()
{
	if (SOCKETG)
	{
		SocketClose(SOCKETG);
	}
	if (SOCKETL)
	{
		SocketClose(SOCKETL);
	}
}
SocketData *CGameSocket::Connect(const char * pszIP, int iPort)
{
	SocketData * sd = NULL;
	if ((sd = GAMESOCKET->GetSocketData(pszIP, iPort)) == NULL)
	{
		sd = GAMESOCKET->GetFreeSocketData();
		if (sd)
		{
			if (!sd->Connect(pszIP, iPort))
			{
				sd->UnInit();
				return NULL;
			}
		}
	}
	else
	{
		PacketReceiving * p = new PacketReceiving;
		p->bInUse = TRUE;
		p->bDelete = TRUE;
		//Connection already Confirmed
		PacketVersion sPacket;
		sPacket.iLength = sizeof(PacketVersion);
		sPacket.iHeader = PKTHDR_Version;
		sPacket.bServerFull = FALSE;
		sPacket.iUnk2 = 0;
		sPacket.iVersion = GAME_VERSION;
		CopyMemory(p->baPacket, &sPacket, sizeof(PacketVersion));
		GAMESOCKET->SocketPacket(sd, p);
	}
	return sd;
}
void CGameSocket::Connected()
{
	m_bCanCheckConnection = TRUE;
}
void CGameSocket::PingConnections()
{
	static DWORD dwTick = 0;

	if ((TICKCOUNT - dwTick) >= 150)
	{
		if (SOCKETG)
		{
			PacketPing s;
			s.iLength = sizeof(PacketPing);
			s.iHeader = PKTHDR_Ping;
			dwLastTickGame = TICKCOUNT;
			SENDPACKETG(&s);
		}

		if (SOCKETL)
		{
			PacketPing s;
			s.iLength = sizeof(PacketPing);
			s.iHeader = PKTHDR_Ping;
			dwLastTickLogin = TICKCOUNT;
			SENDPACKETL(&s);
		}

		dwTick = TICKCOUNT;
	}
}
void CGameSocket::HandlePacket(SocketData * sd, PacketPing * psPacket)
{
	DWORD dwTime1 = GAMEMAP->SystemTimeToGameTime(psPacket->dwTick);
	DWORD dwTime2 = GAMEMAP->GetGameTime();

	if (sd == SOCKETG)
	{
		if (abs((int)(dwTime2 - dwTime1)) > 10)
			dwTime2 = dwTime1;
	}

	DWORD dwTime = TICKCOUNT - (sd == SOCKETL ? dwLastTickLogin : dwLastTickGame);

	sd->iPing = dwTime;
}
void CGameSocket::Loop()
{
	if (GAMESCREEN->GetActiveScreenType() == SCREEN_World)
	{
		if (!m_bInit)
		{
			if (SOCKETL && SOCKETG)
			{
				PacketSelectCharacter s;

				s.iLength = sizeof(PacketSelectCharacter);
				s.iHeader = PKTHDR_SelectCharacter;
				s.dwReserved1 = 0;
				s.dwReserved2 = 0;
				s.dwReserved3 = 0;
				STRINGCOPY(s.szCharName, UNIT->sCharacterData.szName);
				SENDPACKETL(&s);
			}

			m_bInit = TRUE;
		}
		else
		{
			static DWORD dwLastPositionTime = 0;
			static DWORD dwLastSendGameTime = 0;

			if (dwLastPositionTime == 0)
				dwLastPositionTime = TICKCOUNT;

			if ((TICKCOUNT - dwLastPositionTime) > 1000)
			{
				// Close Far Monst
				GAMEUNIT->ClearFarUnits();
				dwLastPositionTime = TICKCOUNT;
			}

			if (dwLastSendGameTime == 0)
				dwLastSendGameTime = TICKCOUNT;

			DWORD dwTime = TICKCOUNT - dwLastSendGameTime;

			if ((lpCurPlayer->iPlayBuffCount & 0x3F) == 0 && lpCurPlayer->iID && dwTime > 300)
			{
				lpCurPlayer->HandleUnitDataBuffer((char *)lpCurPlayer->baUnitBufferNew, 0x40,1);

				SENDPACKETG(lpCurPlayer->baUnitBufferNew);

				dwLastSendGameTime = TICKCOUNT;
			}

			if (m_bCanCheckConnection)
				GAMESOCKET->CheckConnection();

			PingConnections();

			if (GAMESOCKET->iDisconnectType != (-2))
			{
				if (SOCKETL == NULL)
				{
					if (GAMESOCKET->iDisconnectType == -1)
					{
						GAMESOCKET->iDisconnectType = 1;
						CHATGAMEHANDLE->AddChatBoxTextEx(CHATCOLOR_Error, "Connection lost with %s", "Login Server");
					}
				}
				else if (SOCKETG == NULL)
				{
					if (GAMESOCKET->iDisconnectType == -1)
					{
						GAMESOCKET->iDisconnectType = 2;
						CHATGAMEHANDLE->AddChatBoxTextEx(CHATCOLOR_Error, "Connection lost with %s", "Game Server");
					}
				}
			}
		}
	}
}
DWORD WINAPI CGameSocket::Receiver(SocketData * sd)
{
	CGameSocket * m = GAMESOCKET;
	HWND hWnd = m->GetHWND();
	PacketReceiving * p;
	do
	{
		WaitForSingleObject(sd->hReceiveThreadSignal, INFINITE);
		if (!m->IsActive())
			break;
		while ((p = sd->ReceivePacket()) != NULL)
		{
			PostMessageA(hWnd, WM_SOCKETPACKET, (WPARAM)sd, (LPARAM)p);
		}
		sd->bBlockSend = TRUE;
		if (m->IsActive())
		{
			if (sd->bConnected)
			{
				WNDPROC_SOCKETCLOSE(hWnd, sd);
			}
		}
	} while (m->IsActive());
	return TRUE;
}
DWORD WINAPI CGameSocket::Sender(SocketData * sd)
{
	CGameSocket * m = GAMESOCKET;
	HWND hWnd = m->GetHWND();
	PacketSending * p;
	do
	{
		WaitForSingleObject(sd->hSendThreadSignal, INFINITE);
		if (!m->IsActive())
			break;
		while ((p = sd->NextPacketSending()) != NULL)
		{
			//Post Packet Message
			if (!sd->Send(p))
			{
				sd->FreePacketSending(p);
				break;
			}
			sd->FreePacketSending(p);
		}
	} while (m->IsActive());
	return TRUE;
}
BOOL WINAPI CGameSocket::CheckConnection()
{
	static DWORD dwTimeCheckL = 0;
	static DWORD dwTimeCheckG = 0;
	//Login Server
	if (GAMESOCKET)
	{
		SocketData * sd = SOCKETL;
		if (sd)
		{
			if (GAMESOCKET->szLoginIP[0] == 0)
			{
				STRINGCOPY(GAMESOCKET->szLoginIP, sd->szIP);
				GAMESOCKET->iLoginPort = sd->iPort;
			}
			if ((sd->dwTimeLastPacketReceived + 20000) < TICKCOUNT)
			{
				GAMESOCKET->bLoginServerReconnect = TRUE;
			}
		}
		else
			GAMESOCKET->bLoginServerReconnect = TRUE;
	}
	//Game Server
	if (GAMESOCKET)
	{
		SocketData * sd = SOCKETG;
		if (sd)
		{
			if (GAMESOCKET->szGameIP[0] == 0)
			{
				STRINGCOPY(GAMESOCKET->szGameIP, sd->szIP);
				GAMESOCKET->iGamePort = sd->iPort;
			}
			if ((sd->dwTimeLastPacketReceived + 20000) < TICKCOUNT)
			{
				GAMESOCKET->bGameServerReconnect = TRUE;
			}
		}
		else
			GAMESOCKET->bGameServerReconnect = TRUE;
	}
	if (GAMESOCKET->bLoginServerReconnect)
	{
		if (dwTimeCheckL < TICKCOUNT)
		{
			if (SOCKETL)
			{
				if (SOCKETL->bConnected)
					GAMESOCKET->SocketClose(SOCKETL);
				SOCKETL = NULL;
			}
			GAMESOCKET->iReconnectLCOUNT++;
			if (GAMESOCKET->iReconnectLCOUNT > 10)
			{
				GAMESOCKET->iDisconnectType = -1;
				GAMESOCKET->iDisconnectTime = TICKCOUNT;
			}
			else
			{
				CHATGAMEHANDLE->AddChatBoxTextEx(EChatColor::CHATCOLOR_Error, "> Reconnecting to Login Server (%d/10)", GAMESOCKET->iReconnectLCOUNT);
				SocketData * sd = GAMESOCKET->Connect(GAMESOCKET->szLoginIP, GAMESOCKET->iLoginPort);
				SOCKETL = sd;
				if (sd)
				{
					//Send Reconnect Packet
					PacketReconnectUser s;
					s.iLength = sizeof(PacketReconnectUser);
					s.iHeader = PKTHDR_Reconnect;
					s.dwObjectID = UNIT->iID;
					s.iUnk = 0;
					STRINGCOPY(s.szUserID, UNIT->sCharacterData.szName);
					SENDPACKETL(&s);
				}
			}
			dwTimeCheckL = TICKCOUNT + 5000;
		}
	}
	if (GAMESOCKET->bGameServerReconnect)
	{
		if (dwTimeCheckG < TICKCOUNT)
		{
			if (SOCKETG)
			{
				if (SOCKETG->bConnected)
					GAMESOCKET->SocketClose(SOCKETG);
				SOCKETG = NULL;
			}
			GAMESOCKET->iReconnectGCOUNT++;
			if (GAMESOCKET->iReconnectGCOUNT > 10)
			{
				GAMESOCKET->iDisconnectType = -1;
				GAMESOCKET->iDisconnectTime = TICKCOUNT;
			}
			else
			{
				CHATGAMEHANDLE->AddChatBoxTextEx(EChatColor::CHATCOLOR_Error, "> Reconnecting to Game Server (%d/10)", GAMESOCKET->iReconnectGCOUNT);
				SocketData * sd = GAMESOCKET->Connect(GAMESOCKET->szGameIP, GAMESOCKET->iGamePort);
				SOCKETG = sd;
				if (sd)
				{
					//Send Reconnect Packet
					PacketReconnectUser s;
					s.iLength = sizeof(PacketReconnectUser);
					s.iHeader = PKTHDR_Reconnect;
					s.dwObjectID = UNIT->iID;
					s.iUnk = 0;
					STRINGCOPY(s.szUserID, UNIT->sCharacterData.szName);
					SENDPACKETG(&s);
				}
			}
			dwTimeCheckG = TICKCOUNT + 5000;
		}

		SendTotalExpMoney();

		CheckMaxDamage();
	}
	return TRUE;
}
void CGameSocket::SocketClose(SocketData * sd)
{
	if ((sd) && (sd->bInUse))
	{
		if (sd == SOCKETL)
			SOCKETL = NULL;
		if (sd == SOCKETG)
			SOCKETG = NULL;
		while (sd->bConnecting)
			Sleep(2500);
		sd->Close();
		sd->UnInit();
	}
}
void CGameSocket::SocketPacket(SocketData * sd, PacketReceiving * p)
{
	m_pcMutex->Lock(5000);
	Packet * psPacket = (Packet*)p->baPacket;
	int len = psPacket->iLength;
	if (len > 0x2000)
		return;

	GAMEPACKET->AnalyzePacket(sd, psPacket);

	sd->dwTimeLastPacketReceived = TICKCOUNT;
	sd->FreePacketReceiving(p);
	m_pcMutex->UnLock();
}
void CGameSocket::SendLoginServer(void * pData, BOOL bEncrypt)
{
	if (SOCKETL)
		SOCKETL->SendPacket((Packet*)pData, bEncrypt);
}
void CGameSocket::SendGameServer(void * pData, BOOL bEncrypt)
{
	if (SOCKETG)
		SOCKETG->SendPacket((Packet*)pData, bEncrypt);
}
void CGameSocket::SendAllServer(void * pData, BOOL bEncrypt)
{
	if (SOCKETG && SOCKETL)
	{
		SOCKETG->SendPacket((Packet*)pData, bEncrypt);
		SOCKETL->SendPacket((Packet*)pData, bEncrypt);
	}	
}