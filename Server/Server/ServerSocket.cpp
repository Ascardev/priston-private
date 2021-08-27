#include "StdAfx.h"
#include "ServerSocket.h"

CServerSocket::CServerSocket()
{
	ZeroMemory(m_pcaReconnectedUsers, sizeof(User *) * _countof(m_pcaReconnectedUsers));
	m_pcMutex = new CMutex();
	m_pcAcceptMutex = new CMutex();
	m_pcCloseMutex = new CMutex();
}
CServerSocket::~CServerSocket()
{
	DELET(m_pcMutex);
	DELET(m_pcAcceptMutex);
	DELET(m_pcCloseMutex);
}
void CServerSocket::Init(HWND hwnd)
{
	m_hWnd = hwnd;
	SetPacketObfuscatorByte(SERVER_PORT);

	Listen(SERVER_PORT);
}
void CServerSocket::Listen(int iPort)
{
	if ((m_sListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) != INVALID_SOCKET)
	{
		sockaddr_in sin;
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = INADDR_ANY;
		sin.sin_port = htons(iPort);

		if (::bind(m_sListenSocket, (SOCKADDR *)&sin, sizeof(sin)) != SOCKET_ERROR)
		{
			if (listen(m_sListenSocket, SOMAXCONN) == SOCKET_ERROR)
			{
				WRITEDBG("SocketServer::Init()listen():: %d", WSAGetLastError());
				closesocket(m_sListenSocket);
				m_sListenSocket = INVALID_SOCKET;
				return;
			}
		}
		else
		{
			WRITEDBG("SocketServer::Init()bind():: %d", WSAGetLastError());
			closesocket(m_sListenSocket);
			m_sListenSocket = INVALID_SOCKET;
			return;
		}
	}
	else
	{
		WRITEDBG("SocketServer::Init()socket():: %d", WSAGetLastError());
		return;
	}

	m_bActive = TRUE;

	// Success
	m_hListener = CreateThread(NULL, 16384, (LPTHREAD_START_ROUTINE)Listener, &m_sListenSocket, STACK_SIZE_PARAM_IS_A_RESERVATION, NULL);
	CreateThread(NULL, 16384, (LPTHREAD_START_ROUTINE)DeniedSocketsHandler, NULL, STACK_SIZE_PARAM_IS_A_RESERVATION, NULL);
	Load();
}
SocketData *CServerSocket::GetFreeSocketData()
{
	for (int i = 0; i < m_iMaxConnections; i++)
	{
		SocketData *sd = m_pcaSocketData + i;

		if (!sd->bInUse)
		{
			sd->Init();
			return sd;
		}
	}

	return nullptr;
}
SocketData *CServerSocket::GetSocketData(const char * pszIP, int iPort)
{
	for (int i = 0; i < m_iMaxConnections; i++)
	{
		SocketData *sd = m_pcaSocketData + i;

		if (sd->bInUse && sd->bConnected && STRINGCOMPARE(sd->szIP, pszIP) && sd->iPort == iPort)
			return sd;
	}

	return nullptr;
}
SocketData *CServerSocket::Connect(const char * pszIP, int iPort)
{
	WRITEDBG("Connect %s:%d", pszIP, iPort);

	SocketData *sd = nullptr;

	if ((sd = SERVERSOCKET->GetSocketData(pszIP, iPort)) == nullptr)
	{
		sd = SERVERSOCKET->GetFreeSocketData();

		if (sd)
		{
			if (!sd->Connect(pszIP, iPort))
			{
				sd->UnInit();

				return nullptr;
			}

			if ((sd->u = SERVERUSER->GetFreeUser()) != NULL)
			{
				sd->u->Start(sd);
			}
		}
	}

	return sd;
}
DWORD WINAPI CServerSocket::Listener(SOCKET * ls)
{
	SOCKET s = *ls;
	CServerSocket * pc = SERVERSOCKET;

	sockaddr_in * sout = new sockaddr_in;
	int len = sizeof(sockaddr_in);

	while (pc->IsActive())
	{
		SOCKET n = INVALID_SOCKET;
		if ((n = accept(s, (SOCKADDR *)sout, &len)) != INVALID_SOCKET)
		{
			//Send Accept Message
			SendMessageA(pc->GetHWND(), WM_SOCKETACCEPT, n, (LPARAM)sout);
		}
	}
	delete sout;

	return TRUE;
}

void CServerSocket::Load()
{
	m_iMaxConnections = 400;

	m_pcaSocketData = new SocketData[m_iMaxConnections];

	m_hEventSocket = CreateEvent(NULL, FALSE, FALSE, NULL);

	for (int i = 0; i < MAX_DENYCONNECTIONS; i++)
		m_saSocket[i] = INVALID_SOCKET;

	m_iNextSocket = 0;

	for (int i = 0; i < m_iMaxConnections; i++)
	{
		SocketData * sd = m_pcaSocketData + i;
		sd->pcThis = sd;
		sd->bInUse = FALSE;
		sd->Prepare(64, 64);
		sd->hReceiveThread = CreateThread(NULL, 16384, (LPTHREAD_START_ROUTINE)&CServerSocket::Receiver, sd, STACK_SIZE_PARAM_IS_A_RESERVATION, NULL);
		sd->hSendThread = CreateThread(NULL, 16384, (LPTHREAD_START_ROUTINE)&CServerSocket::Sender, sd, STACK_SIZE_PARAM_IS_A_RESERVATION, NULL);
	}
	m_bActive = TRUE;
}
void CServerSocket::HandleReconnectedUsers()
{
	for (int i = 0; i < MAX_RECONNECTCONNECTIONS; i++)
	{
		if (m_pcaReconnectedUsers[i])
		{
			SENDPACKETBLANK(m_pcaReconnectedUsers[i], LOGIN_SERVER ? PKTHDR_ReconnectLogin : PKTHDR_Reconnect);
			m_pcaReconnectedUsers[i] = NULL;
		}
	}
}
void CServerSocket::HandleDeniedSockets()
{
	SOCKET arr[MAX_DENYCONNECTIONS];
	int iNumSockets = 0;

	m_pcMutex->Lock(6100);

	for (int i = 0; i < m_iNextSocket; i++)
	{
		SOCKET s = m_saSocket[i];

		if (s != INVALID_SOCKET)
		{
			arr[iNumSockets] = s;
			iNumSockets++;
		}

		m_saSocket[i] = INVALID_SOCKET;
	}
	m_iNextSocket = 0;

	m_pcMutex->UnLock();

	for (int i = 0; i < iNumSockets; i++)
	{
		SOCKET s = arr[i];

		if (s != INVALID_SOCKET)
		{
			LINGER l;
			l.l_onoff = TRUE;
			l.l_linger = 30;
			setsockopt(s, SOL_SOCKET, SO_LINGER, (char*)&l, sizeof(l));

			// Send Version
			PacketVersion sPacket;
			sPacket.iLength = sizeof(PacketVersion);
			sPacket.iHeader = PKTHDR_Version;
			sPacket.bServerFull = TRUE;
			sPacket.iUnk2 = 0;
			sPacket.iVersion = SERVER_VERSION;

			send(s, (char*)&sPacket, sPacket.iLength, 0);
			closesocket(s);
		}
	}
}
void CServerSocket::HandleBanFirewall()
{
	m_pcMutex->Lock(6101);

	char szIP[32] = { 0 };

	for (int i = 0; i < MAX_BANCONNECTIONS; i++)
	{
		if (m_dwaIPListBan[i] != 0)
		{
			DWORD dwIP = m_dwaIPListBan[i];
			STRINGFORMAT(szIP, "%d.%d.%d.%d", dwIP & 0xFF, (dwIP >> 8) & 0xFF, (dwIP >> 16) & 0xFF, (dwIP >> 24) & 0xFF);
			SERVERLOG->AddFirewallBan(szIP);
			m_dwaIPListBan[i] = 0;
		}
	}

	m_pcMutex->UnLock();
}
void CServerSocket::SocketAccept(SOCKET s, sockaddr_in * addr)
{
	// Mutex Area
	m_pcAcceptMutex->Lock();

	SocketData * sd = NULL;
	BOOL bAccepted = FALSE;

	if (IsFull() == FALSE)
	{
		BOOL bPass = TRUE;

		if (bPass)
		{
			if ((sd = GetFreeSocketData()) && USERS_ONLINE < MAX_USERS)
			{
				sd->u = SERVERUSER->GetFreeUser();
				sd->u->Start(sd);
				sd->Open(s, addr);

				bAccepted = TRUE;
			}
		}
	}

	if (bAccepted)
	{
		//Send the Byte Encryption Set
		sd->SendKeySet(GetPacketObfuscatorByte());

		// Send Version
		PacketVersion sPacket;
		sPacket.iLength = sizeof(PacketVersion);
		sPacket.iHeader = PKTHDR_Version;
		sPacket.bServerFull = FALSE;
		sPacket.iUnk2 = 0;
		sPacket.iVersion = SERVER_VERSION;
		sd->SendPacket(&sPacket, FALSE);
	}
	else
	{
		if (sd)
		{
			sd->UnInit();

			sd = NULL;
		}

		if (!AddDeniedSocket(s))
			closesocket(s);
	}

	m_pcAcceptMutex->UnLock();
}
void CServerSocket::SocketPacket(SocketData * sd, PacketReceiving * p)
{
	m_pcMutex->Lock(5000);

	if (sd)
	{
		User * pcUser = sd->u;

		if ((pcUser) && (pcUser->pcSocketData))
		{
			DWORD dwTickCount;

			if ((dwTickCount = SERVERUSER->AllowPacket(pcUser)) != 0)
			{
				SERVERPACKET->AnalyzePacket(pcUser, p);
				sd->dwTimeLastPacketReceived = dwTickCount;
			}
			else
			{
				SERVERLOG->LogSocketClose(sd, "SocketServer::SocketPacket()::AllowPacket", _ReturnAddress());
				WNDPROC_SOCKETCLOSE(m_hWnd, sd);
			}
		}
		else
		{
			SERVERLOG->LogSocketClose(sd, "SocketServer::SocketPacket()::NotUserData", _ReturnAddress());
			WNDPROC_SOCKETCLOSE(m_hWnd, sd);
		}

		sd->FreePacketReceiving(p);
	}
	if (m_pcMutex->UnLock())
	{
		//	WRITEDBG( "Socket Packet [%d][0x%08X]", p->sPacket.iLength, p->sPacket.iHeader );
	}
}
void CServerSocket::SocketClose(SocketData * sd)
{
	m_pcCloseMutex->Lock(5005);

	if (sd && sd->bInUse)
	{
		User * pcUser = sd->u;

		if (pcUser)
		{
			if (pcUser->bClosingSocket == TRUE)
			{
				m_pcCloseMutex->UnLock();
				return;
			}

			pcUser->bClosingSocket = TRUE;

			if (!pcUser->bNetServer)
			{
				CharacterFile * cf = sd->u->psCharacterFile;

				if (cf && pcUser->szAccountName[0] && pcUser->szCharacterName[0] && cf->iLength > 0)
				{
					CharacterData * ch = (CharacterData*)&cf->sCharInfo;
					ch->szName[31] = 0;

					if (STRINGCOMPAREI(ch->szName, pcUser->szCharacterName))
					{
						SERVERUSER->SaveDropItem(pcUser);

						BOOL bsafeCheck = SERVERACCOUNT->SaveFile(pcUser, pcUser->szCharacterName, (PacketCharacterRecordData *)cf);

						if (bsafeCheck != TRUE)
							WRITEDBG("ERR: Save Failed %s", pcUser->szCharacterName);

						cf->iLength = 0;
					}
				}

				SERVERUSER->OnUnLoadUser(pcUser);

				DELET(pcUser->psCharacterData);

				SERVERACCOUNT->DisconnectUser(pcUser);
			}

			SERVERLOG->LogSocketClose(sd, "SocketServer::SocketClose()", _ReturnAddress());

			if (SERVERNET->Disconnected(sd))
				WRITEDBG("NET SERVER DC");

			if (GAME_SERVER)
				PARTYHANDLE->LeaveParty(pcUser);

			pcUser->Stop();
		}

		sd->Close();
		sd->UnInit();
	}

	m_pcCloseMutex->UnLock();
}
DWORD WINAPI CServerSocket::DeniedSocketsHandler()
{
	CServerSocket * m = SERVERSOCKET;

	do
	{
		m->HandleReconnectedUsers();

		m->HandleDeniedSockets();

		m->HandleBanFirewall();

		//WaitForSingleObject(m->GetHandleEventSocket(), 2500);
		MsgWaitForMultipleObjects(1, &m->m_hEventSocket, FALSE, 2500, QS_ALLINPUT);
	} while (m->IsActive());

	return 0;
}
DWORD WINAPI CServerSocket::Sender(SocketData * sd)
{
	CServerSocket * m = SERVERSOCKET;

	HWND hWnd = m->GetHWND();

	do
	{
		WaitForSingleObject(sd->hSendThreadSignal, INFINITE);

		if (!m->IsActive())
			break;

		PacketSending * p;
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

DWORD WINAPI CServerSocket::Receiver(SocketData * sd)
{
	CServerSocket * m = SERVERSOCKET;

	HWND hWnd = m->GetHWND();

	do
	{
		WaitForSingleObject(sd->hReceiveThreadSignal, INFINITE);

		if (!m->IsActive())
			break;

		PacketReceiving * p;
		while ((p = sd->ReceivePacket()) != NULL)
		{
			PostMessageA(m->GetHWND(), WM_SOCKETPACKET, (WPARAM)sd, (LPARAM)p);
		}

		sd->bBlockSend = TRUE;

		if (m->IsActive())
		{
			if (sd->bConnected)
			{
				if (sd->u && sd->u->iID)
					SERVERUSER->AddReconnectUser(sd->u);

				//Anti-DDoS
				if (sd->iRecvEC == 0x6A6A)
				{
					m->AddBanIP(sd->lIP);
				}
				else
				{
					static char szLogDC[64] = { 0 };
					STRINGFORMAT(szLogDC, "SocketServer::Receiver() [%d]", sd->iRecvEC);
					SERVERLOG->LogSocketClose(sd, szLogDC, _ReturnAddress());
				}
				WNDPROC_SOCKETCLOSE(m->GetHWND(), sd);
			}
		}

	} while (m->IsActive());

	return TRUE;
}
BOOL CServerSocket::AddDeniedSocket(SOCKET s)
{
	BOOL bRet = FALSE;

	m_pcMutex->Lock(6000);

	if (m_iNextSocket < MAX_DENYCONNECTIONS)
	{
		m_saSocket[m_iNextSocket] = s;
		m_iNextSocket++;

		bRet = TRUE;
	}

	m_pcMutex->UnLock();

	return bRet;
}
BOOL CServerSocket::AddBanIP(DWORD dwIP)
{
	m_pcMutex->Lock(6101);

	int iIndex = -1;

	for (int i = 0; i < MAX_BANCONNECTIONS; i++)
	{
		if (m_dwaIPListBan[i] != 0)
		{
			if (m_dwaIPListBan[i] == dwIP)
				return TRUE;
		}
		else
			iIndex = i;
	}

	if (iIndex >= 0)
		m_dwaIPListBan[iIndex] = dwIP;

	m_pcMutex->UnLock();

	return TRUE;
}
BOOL CServerSocket::AddReconnectedUser(User * pcUser)
{
	for (int i = 0; i < MAX_RECONNECTCONNECTIONS; i++)
	{
		if (m_pcaReconnectedUsers[i] == NULL)
		{
			m_pcaReconnectedUsers[i] = pcUser;
			return TRUE;
		}
	}

	return FALSE;
}