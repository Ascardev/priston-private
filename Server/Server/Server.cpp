#include "StdAfx.h"
#include "server.h"
#include "SrcServer/onserver.h"

CServer::CServer()
{
	m_pcMutex = new CMutex("Server");

	m_pcServerInfo = new CServerInfo;
	m_pcServerSocket = new CServerSocket;
	m_pcServerUser = new CServerUser;
	m_pcServerCharacter = new CServerCharacter;
	m_pcServerUnit = new CServerUnit;
	m_pcServerMap = new CServerMap;
	m_pcServerChat = new CServerChat;
	m_pcServerItem = new CServerItem;
	m_pcServerNet = new CServerNet;
	m_pcServerPvP = new CServerPvP;
	m_pcServerAccount = new CServerAccount;
	m_pcServerLog = new CServerLog;
	m_pcServerCommand = new CServerCommand;
	m_pcServerUserInfo = new CServerUserInfo;
	m_pcServerBellatra = new CServerBellatra;
	m_pcServerBlessCastle = new CServerBlessCastle;
}
CServer::~CServer()
{
	DELET(m_pcServerBlessCastle);
	DELET(m_pcServerBellatra);
	DELET(m_pcServerUserInfo);
	DELET(m_pcServerCommand);
	DELET(m_pcServerLog);
	DELET(m_pcServerAccount);
	DELET(m_pcServerPvP);
	DELET(m_pcServerNet);
	DELET(m_pcServerItem);
	DELET(m_pcServerChat);
	DELET(m_pcServerMap);
	DELET(m_pcServerUnit);
	DELET(m_pcServerCharacter);
	DELET(m_pcServerUser);
	DELET(m_pcServerSocket);
	DELET(m_pcServerInfo);

	DELET(m_pcMutex);
}
void CServer::CreateSQLConnection(EDatabaseID eID)
{
	SQLConnection * pcSQL = new SQLConnection;

	ServerSQL *psaSQL = SERVERINFO->GetSQL();
	pcSQL->Init(eID, psaSQL->szHost, psaSQL->szUser, psaSQL->szPassword);
}
void CServer::CloseSQLConnection(EDatabaseID eID)
{
	SQLConnection * pcSQL = SQLConnection::GetConnection(eID);

	if (pcSQL)
	{
		pcSQL->Shutdown();

		DELET(pcSQL);
	}
}
void CServer::Init(HWND hwnd)
{
	m_hWnd = hwnd;

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);
}
void CServer::Shutdown()
{
	RemoveAll();
	SHUTDOWN(m_pcServerMap);
	SHUTDOWN(m_pcServerUnit);
	SHUTDOWN(m_pcServerItem);
	ClearSQL();
}
void CServer::Load()
{
	SERVERINFO->Load();

	SERVERSOCKET->Init(m_hWnd);

	LoadSQL();

	InitAll();

	INIT(m_pcServerItem);
	INIT(m_pcServerUnit);
	INIT(m_pcServerMap);

	if (GAME_SERVER)
	{
		SERVERNET->Init();
	}

	SERVERBLESSCASTLE->SQLReadBlessCastleStatus();

	SERVERBLLATRA->Init();
}
void CServer::Update(double fTime)
{
	static double fCount_500MS = 0.0f; static double f500MS = 500.0f;
	static double fCount_1SECO = 0.0f; static double f1SECO = 1000.0f;
	static double fCount_1MINU = 0.0f; static double f1MINU = 60000.0f;
	static double fCount_1HOUR = 0.0f; static double f1HOUR = 3600000.0f;

	fCount_500MS += fTime;
	fCount_1SECO += fTime;
	fCount_1MINU += fTime;
	fCount_1HOUR += fTime;

	while (fCount_500MS >= f500MS)
	{
		Tick(TICKTYPE_500MilliSecond);

		fCount_500MS -= f500MS;
	}

	while (fCount_1SECO >= f1SECO)
	{
		Tick(TICKTYPE_1Second);

		fCount_1SECO -= f1SECO;
	}

	while (fCount_1MINU >= f1MINU)
	{
		Tick(TICKTYPE_1Minute);

		fCount_1MINU -= f1MINU;
	}

	while (fCount_1HOUR >= f1HOUR)
	{
		fCount_1HOUR -= f1HOUR;
	}
}
void CServer::Tick(ETickType iTickType)
{
	switch (iTickType)
	{
	case TICKTYPE_500MilliSecond:
		EventMonsterTime();
		SERVERBLESSCASTLE->OnTime();
		SERVERINFO->UpdateSystemTime();
		break;
	case TICKTYPE_1Second:
		AnnounceMaintenanceCountdown();

		for (int i = 0; i < PLAYERS_MAX; i++)
		{
			User * pcUser = USERSDATA + i;
			if (pcUser->pcSocketData)
			{
				SERVERCHARACTER->UpdateForceOrb(pcUser);
				SERVERCHARACTER->UpdatePremiumTimer(pcUser);
			}
		}
		break;
	case TICKTYPE_1Minute:
		break;
	case TICKTYPE_1Hour:
		break;
	default:
		break;
	}
}
void CServer::Loop()
{
	SERVERINFO->Update();
	//Update Users
	SERVERUSER->Update();

	//Update Units
	SERVERUNIT->Update();

	//Update Map
	SERVERMAP->Update();

	//Update Alive Users
	SERVERUSER->Loop();
}
void CServer::Begin()
{
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	InvalidateRect(m_hWnd, NULL, TRUE);
	UpdateWindow(m_hWnd);

	if (LOGIN_SERVER)
		CreateThread(NULL, KB256, (LPTHREAD_START_ROUTINE)CServerAccount::ProcessAccountLoginQueue, NULL, STACK_SIZE_PARAM_IS_A_RESERVATION, NULL);
}
void CServer::End()
{
	InvalidateRect(m_hWnd, NULL, TRUE);
	UpdateWindow(m_hWnd);

	ShowWindow(m_hWnd, SW_HIDE);
	UpdateWindow(m_hWnd);
}
void CServer::StartMaintenanceCountdown(int iSeconds)
{
	m_bMaintenanceCountdown = TRUE;
	m_iMaintenanceCountdown = iSeconds;

	AnnounceMaintenanceCountdown();

	SetMaintenance(TRUE);
}
void CServer::StopMaintenanceCountdown()
{
	m_bMaintenanceCountdown = FALSE;

	SERVERCHAT->SendChatAll(CHATCOLOR_Global, "Maintenance Countdown Cancelled");

	SetMaintenance(FALSE);
}

void CServer::AnnounceMaintenanceCountdown()
{
	if (m_bMaintenanceCountdown)
	{
		m_iMaintenanceCountdown--;

		if (m_iMaintenanceCountdown > 0)
		{
			int iMinutes = m_iMaintenanceCountdown / 60;
			int iSeconds = m_iMaintenanceCountdown - (iMinutes * 60);

			if (m_iMaintenanceCountdown == 10)
			{
				for (int i = 0; i < PLAYERS_MAX; i++)
				{
					User * pcUser = USERSDATA + i;

					if ((pcUser->pcSocketData != NULL) && pcUser->iID)
						WNDPROC_SOCKETCLOSE(SERVERSOCKET->GetHWND(), pcUser->pcSocketData);
				}
			}

			BOOL bAnnounce = FALSE;

			if (m_iMaintenanceCountdown <= 5)
			{
				bAnnounce = true;
			}
			else if (m_iMaintenanceCountdown <= 15)
			{
				if ((m_iMaintenanceCountdown % 2) == 0)
				{
					bAnnounce = true;
				}
			}
			else if (m_iMaintenanceCountdown <= 60)
			{
				if ((m_iMaintenanceCountdown % 10) == 0)
				{
					bAnnounce = true;
				}
			}
			else if (m_iMaintenanceCountdown <= 120)
			{
				if ((m_iMaintenanceCountdown % 20) == 0)
				{
					bAnnounce = true;
				}
			}
			else
			{
				if ((m_iMaintenanceCountdown % 30) == 0)
				{
					bAnnounce = true;
				}
			}

			if (bAnnounce)
				SERVERCHAT->SendChatAllEx(CHATCOLOR_Global, "Maintenance Countdown> %dmin %dsec", iMinutes, iSeconds);
		}
		else
		{
			for (int i = 0; i < PLAYERS_MAX; i++)
			{
				User * pcUser = USERSDATA + i;

				if ((pcUser->pcSocketData != NULL) && (pcUser->iGameLevel < GAMELEVEL_Two))
					WNDPROC_SOCKETCLOSE(SERVERSOCKET->GetHWND(), pcUser->pcSocketData);
			}

			m_bMaintenanceCountdown = TRUE;
		}
	}
}
void CServer::LoadSQL()
{
	CreateSQLConnection(DATABASEID_GameDB);
	CreateSQLConnection(DATABASEID_GameDB_2);
	CreateSQLConnection(DATABASEID_GameDB_3);
	CreateSQLConnection(DATABASEID_UserDB);
	CreateSQLConnection(DATABASEID_UserDB_2);
	CreateSQLConnection(DATABASEID_ServerDB);
	CreateSQLConnection(DATABASEID_LogDB);
	CreateSQLConnection(DATABASEID_SkillDB);
	CreateSQLConnection(DATABASEID_EventDB);
	CreateSQLConnection(DATABASEID_ClanDB);
	CreateSQLConnection(DATABASEID_ClanDB_2);
	CreateSQLConnection(DATABASEID_ClanDB_3);
	CreateSQLConnection(DATABASEID_ClanDB_4);
}
void CServer::ClearSQL()
{
	CloseSQLConnection(DATABASEID_ClanDB_4);
	CloseSQLConnection(DATABASEID_ClanDB_3);
	CloseSQLConnection(DATABASEID_ClanDB_2);
	CloseSQLConnection(DATABASEID_ClanDB);
	CloseSQLConnection(DATABASEID_EventDB);
	CloseSQLConnection(DATABASEID_SkillDB);
	CloseSQLConnection(DATABASEID_LogDB);
	CloseSQLConnection(DATABASEID_ServerDB);
	CloseSQLConnection(DATABASEID_UserDB_2);
	CloseSQLConnection(DATABASEID_UserDB);
	CloseSQLConnection(DATABASEID_GameDB_3);
	CloseSQLConnection(DATABASEID_GameDB_2);
	CloseSQLConnection(DATABASEID_GameDB);
}