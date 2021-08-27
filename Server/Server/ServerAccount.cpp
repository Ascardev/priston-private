#include "StdAfx.h"
#include "ServerAccount.h"
#include "SrcServer/onserver.h"


BOOL CServerAccount::bActive;
int CServerAccount::iWaitingAccountLogins;
CMutex * CServerAccount::pcMutex;
AccountLogin CServerAccount::saAccountLogin[MAX_ACCOUNTLOGINQUEUE];

CServerAccount::CServerAccount()
{
	pcMutex = new CMutex("Account Server");

	ZeroMemory(&saAccountLogin, sizeof(saAccountLogin));
	iWaitingAccountLogins = 0;
	bActive = true;
}
CServerAccount::~CServerAccount()
{
	bActive = false;
	iWaitingAccountLogins = 0;
	ZeroMemory(&saAccountLogin, sizeof(saAccountLogin));

	DELET(pcMutex);
}
void CServerAccount::DisconnectUser(User* pcUser)
{
	if (pcUser)
	{
		if (!GAME_SERVER)
		{
			SERVERUSER->SetUserID(pcUser);
			SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);
			if (pcDB->Open())
			{
				if (pcDB->Prepare("UPDATE CharacterInfo SET IsOnline=0 WHERE AccountName=?"))
				{
					pcDB->BindParameterInput(1, PARAMTYPE_String, pcUser->szAccountName, _countof(pcUser->szAccountName));
					pcDB->Execute();
				}
				pcDB->Close();
			}
		}
		else
		{
			SERVERUSER->SetUserID(pcUser);
			SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);
			if (pcDB->Open())
			{
				if (pcDB->Prepare("UPDATE CharacterInfo SET LastSeenDate=GETDATE() WHERE Name=?"))
				{
					pcDB->BindParameterInput(1, PARAMTYPE_String, SERVERCHARACTER->GetCharacterName(pcUser), 32);
					pcDB->Execute();
				}
				pcDB->Close();
			}
		}
	}
}
void CServerAccount::LogAccountLogin(User * pcUser, AccountLogin & al, ELogAccount eLogAccount)
{
	char * pszSystemOS = "Unknown";

	switch ((ESystemOS)al.iSystemOS)
	{
	case SYSTEMOS_Windows2000:
		pszSystemOS = "Windows 2000";
		break;
	case SYSTEMOS_WindowsXP:
		pszSystemOS = "Windows XP";
		break;
	case SYSTEMOS_Windows2003:
		pszSystemOS = "Windows Server 2003";
		break;
	case SYSTEMOS_Windows2003R2:
		pszSystemOS = "Windows Server 2003 R2";
		break;
	case SYSTEMOS_WindowsVista:
		pszSystemOS = "Windows Vista";
		break;
	case SYSTEMOS_Windows2008:
		pszSystemOS = "Windows Server 2008";
		break;
	case SYSTEMOS_Windows2008R2:
		pszSystemOS = "Windows Server 2008 R2";
		break;
	case SYSTEMOS_Windows7:
		pszSystemOS = "Windows 7";
		break;
	case SYSTEMOS_Windows2012:
		pszSystemOS = "Windows Server 2012";
		break;
	case SYSTEMOS_Windows8:
		pszSystemOS = "Windows 8";
		break;
	case SYSTEMOS_Windows2012R2:
		pszSystemOS = "Windows Server 2012 R2";
		break;
	case SYSTEMOS_Windows8_1:
		pszSystemOS = "Windows 8.1";
		break;
	case SYSTEMOS_Windows2016:
		pszSystemOS = "Windows Server 2016";
		break;
	case SYSTEMOS_Windows10:
		pszSystemOS = "Windows 10";
		break;
	}

	char *pszIP = NULL;

	if (pcUser && pcUser->pcSocketData)
		pszIP = pcUser->pcSocketData->szIP;

	char szLogDescription[512] = { 0 };

	switch (eLogAccount)
	{
	case ACCLOGID_LoginSuccess:
		STRINGFORMAT(szLogDescription, "[%s] (Login Success) -> Password[%s] MacAddr[%s] PCName[%s] SerialHD[%d] VideoName[%s] Width[%d] Height[%d] SystemOS[%s]",
			al.szAccountName, al.szPassword, al.szMacAddress, al.szPCName, al.uSerialHD, al.szVideoName, al.uWidthScreen, al.uHeightScreen, pszSystemOS);
		break;

	case ACCLOGID_IncorrectAccount:
		STRINGFORMAT(szLogDescription, "Unknown_Account (Incorrect Account) -> AccountName[%s] Password[%s] MacAddr[%s] PCName[%s] SerialHD[%d] VideoName[%s]",
			al.szAccountName, al.szPassword, al.szMacAddress, al.szPCName, al.uSerialHD, al.szVideoName);
		break;

	case ACCLOGID_IncorrectPassword:
		STRINGFORMAT(szLogDescription, "%s (Incorrect Password) -> Password \"%s\"",
			al.szAccountName, al.szPassword);
		break;

	case ACCLOGID_BlockedAccount:
		STRINGFORMAT(szLogDescription, "%s (Account is banned) -> Password \"%s\"",
			al.szAccountName, al.szPassword);
		break;

	case ACCLOGID_UnblockedAccount:
		STRINGFORMAT(szLogDescription, "%s (Account is unbanned) -> Password \"%s\"",
			al.szAccountName, al.szPassword);
		break;

	case ACCLOGID_NotActivatedAccount:
		STRINGFORMAT(szLogDescription, "%s (Account not activated) -> Password \"%s\"",
			al.szAccountName, al.szPassword);
		break;

	case ACCLOGID_CharacterSelectSend:
		STRINGFORMAT(szLogDescription, "%s (Character Select Time)",
			al.szAccountName);
		break;

	case ACCLOGID_TempBanAccount:
		STRINGFORMAT(szLogDescription, "[%s] (Temporarily Banned) -> Password[%s] MacAddr[%s] PCName[%s] SerialHD[%d] VideoName[%s]",
			al.szAccountName, al.szPassword, al.szMacAddress, al.szPCName, al.uSerialHD, al.szVideoName);
		break;

	default:
		break;
	}

	const char *pszDataTime = GetDateTime();

	BOOL bServer = GAME_SERVER;

	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_LogDB);

	if (pcDB->Open())
	{
		if (pcDB->Prepare("INSERT INTO AccountLog VALUES (?,?,?,?,?,?)"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_String, pszIP);
			pcDB->BindParameterInput(2, PARAMTYPE_String, (void*)al.szAccountName);
			pcDB->BindParameterInput(3, PARAMTYPE_Integer, &eLogAccount);
			pcDB->BindParameterInput(4, PARAMTYPE_String, szLogDescription, 512);
			pcDB->BindParameterInput(5, PARAMTYPE_String, (void *)pszDataTime);
			pcDB->BindParameterInput(6, PARAMTYPE_Integer, &bServer);
			pcDB->Execute();
		}
		pcDB->Close();
	}
}
BOOL CServerAccount::IsOnlineAccount(User * pcUser, const char * pszUserID)
{
	for (int i = 0; i < PLAYERS_MAX; i++)
	{
		User *u = USERSDATA + i;

		if (u != pcUser && u->pcSocketData)
		{
			if (lstrcmpiA(u->szAccountName, pszUserID) == 0)
			{
				if (u->dwHashAccountName == pcUser->dwHashAccountName)
				{
					if (u->pcSocketData->bConnected == FALSE)
					{
						SERVERLOG->LogSocketClose(USERSDATA[i].pcSocketData, "AccountServer::IsOnlineAccount", _ReturnAddress());
						WNDPROC_SOCKETCLOSE(SERVERSOCKET->GetHWND(), u->pcSocketData);

						SERVERUSER->DeleteReconnectUser(pszUserID);

						return FALSE;
					}

					return TRUE;
				}
			}
		}
	}

	SERVERUSER->DeleteReconnectUser(pszUserID);

	return FALSE;
}
BOOL CServerAccount::IsIPAccept(const char * pszIP)
{
	BOOL bRet = FALSE;

	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_ServerDB);
	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT Corno FROM Maintenance WHERE (Mode=1) AND (IP=?)"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_String, (void*)pszIP);

			if (pcDB->Execute() && pcDB->Fetch())
			{
				bRet = TRUE;
			}
		}
		pcDB->Close();
	}

	return bRet;
}
BOOL CServerAccount::IsMacBanned(const char * pszMacAddress)
{
	BOOL bRet = FALSE;

	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_ServerDB);

	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT Corno FROM Maintenance WHERE (Mode=4) AND (IP=?)"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_String, (void*)pszMacAddress);

			if (pcDB->Execute() && pcDB->Fetch())
			{
				bRet = TRUE;
			}
		}
		pcDB->Close();
	}

	if (bRet == FALSE)
	{
		//Mac Address of VM Ware
		if (std::string(pszMacAddress).find("00-50-56-", 0, 9) != std::string::npos)
			bRet = TRUE;

		//Mac Address of VM Ware 2
		if (std::string(pszMacAddress).find("00-0C-29-", 0, 9) != std::string::npos)
			bRet = TRUE;

		//Mac Address of VM Ware 3
		if (std::string(pszMacAddress).find("00-05-69-", 0, 9) != std::string::npos)
			bRet = TRUE;

		//Mac Address of Virtual Box
		if (std::string(pszMacAddress).find("08-00-27-", 0, 9) != std::string::npos)
			bRet = TRUE;

		//Mac Address of Virtual PC
		if (std::string(pszMacAddress).find("00-03-FF-", 0, 9) != std::string::npos)
			bRet = TRUE;
	}

	return bRet;
}
BOOL CServerAccount::IsSerialHDBanned(const char * pszSerialHD)
{
	BOOL bRet = FALSE;

	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_ServerDB);

	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT Corno FROM Maintenance WHERE (Mode=5) AND (IP=?)"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_String, (void*)pszSerialHD);

			if (pcDB->Execute() && pcDB->Fetch())
			{
				bRet = TRUE;
			}
		}
		pcDB->Close();
	}
	return bRet;
}
BOOL CServerAccount::IsComputerNameBanned(const char * pszPCName)
{
	BOOL bRet = FALSE;

	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_ServerDB);

	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT Corno FROM Maintenance WHERE (Mode=6) AND (IP=?)"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_String, (void*)pszPCName);

			if (pcDB->Execute() && pcDB->Fetch())
			{
				bRet = TRUE;
			}
		}
		pcDB->Close();
	}

	return bRet;
}
BOOL CServerAccount::IsAccountAccept(const char * pszAccountName)
{
	BOOL bRet = FALSE;

	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_ServerDB);
	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT Corno FROM Maintenance WHERE (Mode=7) AND (IP=?)"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_String, (void*)pszAccountName);

			if (pcDB->Execute() && pcDB->Fetch())
			{
				bRet = TRUE;
			}
		}
		pcDB->Close();
	}

	return bRet;
}

BOOL CServerAccount::IsAdminMacAddress(const char * pszMacAddress, UINT uSerialHD)
{
	return FALSE;
}

void CServerAccount::SQLUserOnline(char * pszAccountName, char * pszCharacterName, char * pszIP, int iTicket, int iAction, int iCharacterClass, int iCharacterLevel)
{
	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_ServerDB);

	if (pcDB->Open() != FALSE)
	{
		switch (iAction)
		{
		case 0:
			if (pcDB->Prepare("INSERT INTO UsersOnline ([AccountName],[CharacterName],[IP],[CharacterClass],[CharacterLevel],[Ticket],[LoginTime]) VALUES (?,?,?,?,?,?,GETDATE())"))
			{
				pcDB->BindParameterInput(1, PARAMTYPE_String, pszAccountName);
				pcDB->BindParameterInput(2, PARAMTYPE_String, pszCharacterName);
				pcDB->BindParameterInput(3, PARAMTYPE_String, pszIP);
				pcDB->BindParameterInput(4, PARAMTYPE_Integer, &iCharacterClass);
				pcDB->BindParameterInput(5, PARAMTYPE_Integer, &iCharacterLevel);
				pcDB->BindParameterInput(6, PARAMTYPE_Integer, &iTicket);

				pcDB->Execute();

			}
			break;
		case 1:

			if (pcDB->Prepare("DELETE FROM UsersOnline WHERE AccountName=?"))
			{
				pcDB->BindParameterInput(1, PARAMTYPE_String, pszAccountName);

				pcDB->Execute();
			}
			break;

		case 2:

			if (pcDB->Prepare("DELETE FROM UsersOnline"))
			{
				pcDB->Execute();
			}
			break;

		default:
			break;
		}

		pcDB->Close();
	}
}

void CServerAccount::SQLCharacterSave(User * pcUser)
{
	char szLogDescription[512] = { 0 };
	char * pszIP = NULL;

	const char * pszDataTime = GetDateTime();

	if (pcUser && pcUser->pcSocketData)
	{
		pszIP = pcUser->pcSocketData->szIP;
	}

	int iLogID = ACCLOGID_CharacterSave;

	BOOL bServer = GAME_SERVER;

	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_LogDB);

	std::string str = FormatNumber((INT64)pcUser->iInventoryGold);

	STRINGFORMAT(szLogDescription, "Character[%s] Save EXP[%s] Gold[%s]", SERVERCHARACTER->GetCharacterName(pcUser),
		FormatNumber(pcUser->liEXP.QuadPart), str.c_str());

	if (pcDB->Open())
	{
		if (pcDB->Prepare("INSERT INTO CharacterLog VALUES (?,?,?,?,?,?)"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_String, pszIP);
			pcDB->BindParameterInput(2, PARAMTYPE_String, pcUser->szAccountName);
			pcDB->BindParameterInput(3, PARAMTYPE_Integer, &iLogID);
			pcDB->BindParameterInput(4, PARAMTYPE_String, szLogDescription, 512);
			pcDB->BindParameterInput(5, PARAMTYPE_String, (void *)pszDataTime);
			pcDB->BindParameterInput(6, PARAMTYPE_Integer, &bServer);
			pcDB->Execute();
		}
		pcDB->Close();
	}
}
void CServerAccount::PHAccountLogin(User * pcUser, PacketLoginUser * psPacket)
{
	if (!LOGIN_SERVER)
		return;

	AccountLogin al;
	al.pcUser = pcUser;
	al.pcSocketData = pcUser->pcSocketData;
	al.uSerialHD = psPacket->dwSerialHD;
	al.uWidthScreen = psPacket->uWidthScreen;
	al.uHeightScreen = psPacket->uHeightScreen;
	al.iSystemOS = psPacket->iSystemOS;
	STRINGCOPY(al.szAccountName, psPacket->szUserID);
	STRINGCOPY(al.szPassword, psPacket->szPassword);
	STRINGCOPY(al.szIP, pcUser->pcSocketData->szIP);
	STRINGCOPY(al.szMacAddress, psPacket->szMacAddr);
	STRINGCOPY(al.szPCName, psPacket->szPCName);
	STRINGCOPY(al.szVideoName, psPacket->szVideoName);

	EAccountLogin iCode = ACCOUNTLOGIN_Success;

	if (!AddAccountLogin(pcUser, al))
	{
		//Connection Failed
		iCode = ACCOUNTLOGIN_ConnectionFailed;
	}

	if ((iCode != ACCOUNTLOGIN_Success) && (iCode != ACCOUNTLOGIN_WrongVersion))
	{
		PacketAccountLoginCode s;
		s.iLength = sizeof(s);
		s.iHeader = PKTHDR_AccountLoginCode;
		s.dwReserved = 0;
		s.iCode = iCode;
		s.iFailCode = 1;
		SENDPACKET(pcUser, &s);
	}
}
BOOL CServerAccount::AddAccountLogin(User * pcUser, AccountLogin & al)
{
	BOOL bRet = FALSE;

	pcMutex->Lock(4000);

	if (iWaitingAccountLogins < MAX_ACCOUNTLOGINQUEUE)
	{
		CopyMemory(&saAccountLogin[iWaitingAccountLogins], &al, sizeof(AccountLogin));

		iWaitingAccountLogins++;

		bRet = TRUE;
	}

	pcMutex->UnLock();

	return bRet;
}
EAccountFlag CServerAccount::SQLAccountGetFlag(char * pszAccountName)
{
	EAccountFlag iRet = ACCOUNTFLAG_NotExist;

	SQLConnection * cDB;

	cDB = SQLCONNECTION(DATABASEID_UserDB);

	if (cDB->Open() != FALSE)
	{
		if (cDB->Prepare("SELECT Flag FROM UserInfo WHERE AccountName=?"))
		{
			cDB->BindParameterInput(1, PARAMTYPE_String, pszAccountName, 32);

			if (cDB->Execute())
				if (cDB->Fetch())
					cDB->GetData(1, PARAMTYPE_Integer, &iRet);
		}

		cDB->Close();
	}

	return iRet;
}
EGameLevel CServerAccount::SQLGetGameMaster(char * pszAccountName)
{
	EGameLevel iGameLevel = GAMELEVEL_None;
	int iGameType = 0;

	SQLConnection * cDB = SQLCONNECTION(DATABASEID_UserDB);

	if (cDB->Open() != FALSE)
	{
		if (cDB->Prepare("SELECT GameMasterType, GameMasterLevel FROM UserInfo WHERE AccountName=?"))
		{
			cDB->BindParameterInput(1, PARAMTYPE_String, pszAccountName, 32);
			if (cDB->Execute() && cDB->Fetch())
			{
				cDB->GetData(1, PARAMTYPE_Integer, &iGameType);
				cDB->GetData(2, PARAMTYPE_Integer, &iGameLevel);
			}
		}

		cDB->Close();
	}

	if (iGameType && iGameLevel)
	{
		return (iGameLevel < 0 || iGameLevel > 4) ? GAMELEVEL_None : iGameLevel;
	}

	return GAMELEVEL_None;
}
void CServerAccount::OnGameMasterCheck(User * pcUser)
{
	if (pcUser->szAccountName && pcUser->szAccountName[0])
	{
		EGameLevel iGameLevel = SQLGetGameMaster(pcUser->szAccountName);

		if (iGameLevel == GAMELEVEL_None)
			SERVERUSER->DisconnectUser(pcUser);
	}
}
BOOL CServerAccount::SQLUnbanAccount(char * pszAccountName)
{
	BOOL bRet = FALSE;

	SQLConnection * cDB;

	cDB = SQLCONNECTION(DATABASEID_UserDB);

	if (cDB->Open() != FALSE)
	{
		if (cDB->Prepare("UPDATE UserInfo SET BanStatus=0,UnbanDate=NULL WHERE AccountName=?"))
		{
			cDB->BindParameterInput(1, PARAMTYPE_String, pszAccountName, 32);

			if (cDB->Execute())
				bRet = TRUE;
		}

		cDB->Close();
	}

	return bRet;
}

int CServerAccount::SQLGetBanStatus(char * pszAccountName, SYSTEMTIME * psBanTime)
{
	int			iRet = BANSTATUS_Error;
	SYSTEMTIME	sCurrentTime, sUnbanDate;
	GetLocalTime(&sCurrentTime);

	SQLConnection * cDB;

	cDB = SQLCONNECTION(DATABASEID_UserDB);

	if (cDB->Open() != FALSE)
	{
		if (cDB->Prepare("SELECT BanStatus,UnbanDate FROM UserInfo WHERE AccountName=?"))
		{
			cDB->BindParameterInput(1, PARAMTYPE_String, pszAccountName, 32);

			if (cDB->Execute())
			{
				if (cDB->Fetch())
				{
					cDB->GetData(1, PARAMTYPE_Integer, &iRet);
					cDB->GetData(2, PARAMTYPE_Time, &sUnbanDate);

					if (iRet == BANSTATUS_TempBanned)
					{
						if (psBanTime)
							CopyMemory(psBanTime, &sUnbanDate, sizeof(SYSTEMTIME));

						if (sCurrentTime.wYear > sUnbanDate.wYear)
							iRet = BANSTATUS_BanExpired;
						else if (sCurrentTime.wYear == sUnbanDate.wYear)
						{
							if (sCurrentTime.wMonth > sUnbanDate.wMonth)
								iRet = BANSTATUS_BanExpired;
							else if (sCurrentTime.wMonth == sUnbanDate.wMonth)
							{
								if (sCurrentTime.wDay > sUnbanDate.wDay)
									iRet = BANSTATUS_BanExpired;
								else if (sCurrentTime.wDay == sUnbanDate.wDay)
								{
									if (sCurrentTime.wHour > sUnbanDate.wHour)
										iRet = BANSTATUS_BanExpired;
									else if (sCurrentTime.wHour == sUnbanDate.wHour)
									{
										if (sCurrentTime.wMinute >= sUnbanDate.wMinute)
											iRet = BANSTATUS_BanExpired;
									}
								}
							}
						}
					}
				}
				else
					iRet = BANSTATUS_NotBanned;
			}
		}

		cDB->Close();
	}

	if (iRet == BANSTATUS_BanExpired)
		if (SQLUnbanAccount(pszAccountName))
		{
			iRet = BANSTATUS_NotBanned;
		}

	return iRet;
}

EAccountLogin CServerAccount::SQLAccountLogin(char * pszAccountName, char * pszPassword, char * pszIP, EAccountFlag iAccountFlag, SYSTEMTIME & sUnbanDate)
{
	if (iAccountFlag == ACCOUNTFLAG_NotExist)
		return ACCOUNTLOGIN_IncorrectName;

	if (!(ACCOUNTFLAG_Activated & iAccountFlag))
		return ACCOUNTLOGIN_AccountNotActive;
	else if (!(ACCOUNTFLAG_AcceptedLatestTOA & iAccountFlag))
		return ACCOUNTLOGIN_AccountNotActive;
	else if (!(ACCOUNTFLAG_Approved & iAccountFlag))
		return ACCOUNTLOGIN_AccountNotActive;
	else if (ACCOUNTFLAG_MustConfirm & iAccountFlag)
		return ACCOUNTLOGIN_AccountNotActive;

	int iBanStatus;
	if ((iBanStatus = SQLGetBanStatus(pszAccountName, &sUnbanDate)) != BANSTATUS_NotBanned)
		return (iBanStatus == BANSTATUS_TempBanned ? ACCOUNTLOGIN_TempBanned : (iBanStatus == BANSTATUS_Banned ? ACCOUNTLOGIN_Banned : ACCOUNTLOGIN_ConnectionFailed));

	char szPassword[128];
	EAccountLogin iRet = ACCOUNTLOGIN_ConnectionFailed;

	SQLConnection * cDB;

	cDB = SQLCONNECTION(DATABASEID_UserDB);

	if (cDB->Open())
	{
		if (cDB->Prepare("SELECT Password FROM UserInfo WHERE AccountName=?"))
		{
			cDB->BindParameterInput(1, PARAMTYPE_String, pszAccountName, 32);

			if (cDB->Execute())
			{
				if (cDB->Fetch())
				{
					cDB->GetData(1, PARAMTYPE_String, szPassword, _countof(szPassword));

					if (STRINGCOMPARE(pszPassword, szPassword))
						iRet = ACCOUNTLOGIN_Success;
					else
						iRet = ACCOUNTLOGIN_IncorrectPassword;
				}
				else
					iRet = ACCOUNTLOGIN_IncorrectName;
			}
		}

		cDB->Close();
	}

	SecureZeroMemory(szPassword, sizeof(szPassword));

	return iRet;
}
void CServerAccount::ProcessAccountLogin(AccountLogin & al)
{
	User * pcUser = al.pcUser;
	SocketData * pcSocketData = al.pcSocketData;
	char * pszAccountName = al.szAccountName;
	char * pszPassword = al.szPassword;
	char * pszIP = al.szIP;

	SYSTEMTIME sUnbanDate;

	BOOL bContinue = FALSE;

	if (pcUser && pcSocketData && pszAccountName && pszPassword && pszIP)
	{
		if (pcUser->pcSocketData == pcSocketData)
		{
			if (lstrcmpiA(pcSocketData->szIP, pszIP) == 0)
			{
				bContinue = TRUE;
			}
		}
	}

	if (bContinue)
	{
		pcUser->SetGameLevel(GAMELEVEL_None);

		EAccountLogin iCode = ACCOUNTLOGIN_ConnectionFailed;

		if (pszAccountName[0] == 0)
		{
			//User did not fill in Account Name
			iCode = ACCOUNTLOGIN_IncorrectName;
		}
		else if (pszPassword[0] == 0)
		{
			//User did not fill in Password
			iCode = ACCOUNTLOGIN_IncorrectPassword;
		}

		if (iCode == ACCOUNTLOGIN_ConnectionFailed)
		{
			EAccountFlag eAccountFlag = SQLAccountGetFlag(pszAccountName);

			EGameLevel iGameLevel = SQLGetGameMaster(pszAccountName);

			//GetGameLevel;
			pcUser->SetGameLevel(iGameLevel);

			//Event GM?
			if (ACCOUNTFLAG_EventGM & eAccountFlag)
			{
				//Set GM Level to 2 (Event GM) if not already a GM
				if (pcUser->GetGameLevel() < GAMELEVEL_Two)
					pcUser->SetGameLevel(GAMELEVEL_Two);
			}

			//Admin?
			if (SERVERACCOUNT->IsAdminMacAddress(al.szMacAddress, al.uSerialHD))
			{
				pcUser->SetGameLevel(GAMELEVEL_Four);

				iCode = ACCOUNTLOGIN_ConnectionFailed;
			}

			if (GSERVER->GetMaintenance())
			{
				//If Server is in Maintenance then access is denied for non-GMs
				if (pcUser->GetGameLevel() == GAMELEVEL_None)
					iCode = ACCOUNTLOGIN_Maintenance;

				//Can connect?
				if (SERVERACCOUNT->IsIPAccept(pszIP))
				{
					iCode = ACCOUNTLOGIN_ConnectionFailed;
				}
				else if (SERVERACCOUNT->IsAccountAccept(pszAccountName))
				{
					iCode = ACCOUNTLOGIN_ConnectionFailed;
				}
			}

			if (eAccountFlag == ACCOUNTFLAG_NotExist)
				iCode = ACCOUNTLOGIN_IncorrectName;

			if (iCode == ACCOUNTLOGIN_ConnectionFailed)
			{
				pcUser->uSerialHD = al.uSerialHD;

				if (pcUser->GetGameLevel() >= GAMELEVEL_Four)
				{
					iCode = ACCOUNTLOGIN_Success;

					User * pcOtherUser = NULL;
					if ((pcOtherUser = SERVERUSER->GetUserByAccount(pszAccountName)) != NULL)
					{
						iCode = ACCOUNTLOGIN_LoggedIn;

						//DC other User
						SENDPACKETBLANK(pcOtherUser, PKTHDR_SaveAndClose, FALSE);
					}
				}

				if (SERVERACCOUNT->IsMacBanned(al.szMacAddress))
				{
					SERVERACCOUNT->LogAccountLogin(pcUser, al, ACCLOGID_IncorrectAccount);

					iCode = ACCOUNTLOGIN_YouAreBanned;
				}

				char szSerialHD[32] = { 0 };
				STRINGFORMAT(szSerialHD, "%d", al.uSerialHD);

				if (SERVERACCOUNT->IsSerialHDBanned(szSerialHD))
				{
					SERVERACCOUNT->LogAccountLogin(pcUser, al, ACCLOGID_IncorrectAccount);

					iCode = ACCOUNTLOGIN_YouAreBanned;
				}

				if (SERVERACCOUNT->IsComputerNameBanned(al.szPCName))
				{
					SERVERACCOUNT->LogAccountLogin(pcUser, al, ACCLOGID_IncorrectAccount);

					iCode = ACCOUNTLOGIN_YouAreBanned;
				}
			}

			if (iCode == ACCOUNTLOGIN_ConnectionFailed)
				iCode = SQLAccountLogin(pszAccountName, pszPassword, pszIP, eAccountFlag, sUnbanDate);
		}

		if (iCode == ACCOUNTLOGIN_Success)
		{
			//Bind Account Name and Account ID to User
			STRINGCOPY(pcUser->szAccountName, pszAccountName);
			pcUser->iAccountID = SERVERUSER->SQLGetAccountID(pszAccountName);

			//Send List of Characters
			SERVERACCOUNT->OnLoginSuccess(pcUser);

			//Set Random Ticket Number
			pcUser->iTicket = RandomI(1, 1000);

			//Send Server Liset and Tick Number
			SERVERINFO->PHServerList(pcSocketData, pcUser->iTicket);

			SERVERACCOUNT->LogAccountLogin(pcUser, al, ACCLOGID_LoginSuccess);
		}
		else
		{
			PacketAccountLoginCode s;
			ZeroMemory(&s, sizeof(PacketAccountLoginCode));

			if ((iCode == ACCOUNTLOGIN_Banned) || (iCode == ACCOUNTLOGIN_IPBanned) || (iCode == ACCOUNTLOGIN_YouAreBanned) ||
				(iCode == ACCOUNTLOGIN_TempBanned))
			{
				if (iCode == ACCOUNTLOGIN_Banned)
					STRINGCOPY(s.szMessage, "Account is Banned");
				else if (iCode == ACCOUNTLOGIN_IPBanned)
					STRINGCOPY(s.szMessage, "Your IP is Banned");
				else if (iCode == ACCOUNTLOGIN_YouAreBanned)
					STRINGCOPY(s.szMessage, "You are Banned");
				else if (iCode == ACCOUNTLOGIN_TempBanned)
					STRINGFORMAT(s.szMessage, "Account is banned until %02d/%02d/%04d %02d:%02d:%02d GMT",
						sUnbanDate.wMonth, sUnbanDate.wDay, sUnbanDate.wYear, sUnbanDate.wHour, sUnbanDate.wMinute, sUnbanDate.wSecond);

				iCode = ACCOUNTLOGIN_Banned;
			}


			//Send Login Failed Packet
			s.iLength = sizeof(s);
			s.iHeader = PKTHDR_AccountLoginCode;
			s.dwReserved = 0;
			s.iCode = iCode;
			s.iFailCode = 2;
			pcSocketData->SendPacket(&s);
		}
	}

	ZeroMemory(&al, sizeof(AccountLogin));
}
DWORD WINAPI CServerAccount::ProcessAccountLoginQueue()
{
	while (bActive)
	{
		int iProcessAccountLogins = 0;
		AccountLogin saProcessAccountLogin[MAX_ACCOUNTLOGINQUEUE];

		//Place all the pending Account Logins in the process queue
		pcMutex->Lock(4000);

		if (iWaitingAccountLogins > 0)
		{
			if (iWaitingAccountLogins > MAX_ACCOUNTLOGINQUEUE)
			{
				//For Safety, should not happen
				iWaitingAccountLogins = MAX_ACCOUNTLOGINQUEUE;
			}

			for (int i = 0; i < iWaitingAccountLogins; i++)
			{
				CopyMemory(&saProcessAccountLogin[iProcessAccountLogins], &saAccountLogin[i], sizeof(AccountLogin));

				iProcessAccountLogins++;
			}

			iWaitingAccountLogins = 0;
		}

		pcMutex->UnLock();

		//Now process the ones ready to login
		if (iProcessAccountLogins > 0)
		{
			SERVER_MUTEX->Lock(9000);

			for (int i = 0; i < iProcessAccountLogins; i++)
			{
				//Process the Login
				ProcessAccountLogin(saProcessAccountLogin[i]);
			}

			SERVER_MUTEX->UnLock();

			for (int i = 0; i < iProcessAccountLogins; i++)
			{
				//Clean it
				SecureZeroMemory(&saProcessAccountLogin[i], sizeof(AccountLogin));
			}

			iProcessAccountLogins = 0;
		}

		Sleep(1024);
	}

	return TRUE;
}
std::vector<std::string> CServerAccount::SQLGetAccountNotification(const char * pszAccountName)
{
	std::vector<std::string> vNotification;

	if ((pszAccountName != NULL) && (pszAccountName[0] != 0))
	{
		SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);
		if (pcDB->Open())
		{
			if (pcDB->Prepare("SELECT Message FROM NotificationData WHERE (AccountName=?) AND (Checked=0) ORDER BY ID ASC"))
			{
				pcDB->BindParameterInput(1, PARAMTYPE_String, (void*)pszAccountName, STRLEN(pszAccountName));
				if (pcDB->Execute())
				{
					while (pcDB->Fetch())
					{
						char szMessage[100] = { 0 };
						pcDB->GetData(1, PARAMTYPE_String, szMessage, _countof(szMessage));
						vNotification.push_back(szMessage);
					}

					pcDB->Clear();
					if (pcDB->Prepare("UPDATE NotificationData SET Checked=1 WHERE AccountName=?"))
					{
						pcDB->BindParameterInput(1, PARAMTYPE_String, (void*)pszAccountName, STRLEN(pszAccountName));
						pcDB->Execute();
					}
				}
			}

			pcDB->Close();
		}
	}

	return vNotification;
}
BOOL CServerAccount::OnLoginSuccess(User * pcUser)
{
	ZeroMemory(&m_sPacketUserInfoLogin, sizeof(PacketUserInfo));
	m_sPacketUserInfoLogin.iLength = sizeof(PacketUserInfo);
	m_sPacketUserInfoLogin.iHeader = PKTHDR_UserInfo;
	STRINGCOPY(m_sPacketUserInfoLogin.szUserID, pcUser->szAccountName);

	int iCount = 0;
	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);
	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT TOP 6 * FROM CharacterInfo WHERE AccountName=? ORDER BY Experience DESC"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_String, pcUser->szAccountName);
			if (pcDB->Execute() && pcDB->Fetch())
			{
				// Get Data in SQL
				for (int i = 0; i < 6; i++)
				{
					char szPathBuffer[256] = { 0 };
					char szCharname[32] = { 0 };

					// Get Character Data file path
					pcDB->GetData(3, PARAMTYPE_String, szCharname, 32);
					STRINGFORMAT(szPathBuffer, "Data\\Character\\%s.chr", szCharname);

					FILE * pFile = NULL;
					fopen_s(&pFile, szPathBuffer, "rb");

					// Character Data open?
					if (pFile)
					{
						// Read .chr File

						ZeroMemory(&m_sPacketCharacterDataLogin, sizeof(PacketCharacterRecordData));
						fseek(pFile, 0, SEEK_SET);
						fread(&m_sPacketCharacterDataLogin, sizeof(PacketCharacterRecordData), 1, pFile);
						fclose(pFile);

						// Packet Structure
						{
							STRINGCOPY(m_sPacketUserInfoLogin.sCharacterData[iCount].szName, m_sPacketCharacterDataLogin.sCharacterData.szName);
							STRINGCOPY(m_sPacketUserInfoLogin.sCharacterData[iCount].szModelName, m_sPacketCharacterDataLogin.sCharacterData.Player.szBodyModel);
							STRINGCOPY(m_sPacketUserInfoLogin.sCharacterData[iCount].szModelName2, m_sPacketCharacterDataLogin.sCharacterData.Player.szHeadModel);
							m_sPacketUserInfoLogin.sCharacterData[iCount].Level = m_sPacketCharacterDataLogin.sCharacterData.iLevel;
							m_sPacketUserInfoLogin.sCharacterData[iCount].JOB_CODE = m_sPacketCharacterDataLogin.sCharacterData.iClass;
							m_sPacketUserInfoLogin.sCharacterData[iCount].dwArmorCode = 0;
							m_sPacketUserInfoLogin.sCharacterData[iCount].Brood = m_sPacketCharacterDataLogin.sCharacterData.iMonsterType;
							m_sPacketUserInfoLogin.sCharacterData[iCount].StartField = m_sPacketCharacterDataLogin.sCharacterSaveData.iMapID;
							m_sPacketUserInfoLogin.sCharacterData[iCount].PosX = m_sPacketCharacterDataLogin.sCharacterSaveData.iCameraPositionX;
							m_sPacketUserInfoLogin.sCharacterData[iCount].PosZ = m_sPacketCharacterDataLogin.sCharacterSaveData.iCameraPositionZ;

							// Is in Sod?
							if (m_sPacketUserInfoLogin.sCharacterData[iCount].StartField == MAPID_Bellatra)
								m_sPacketUserInfoLogin.sCharacterData[iCount].StartField = MAPID_NaviskoTown;

							// Is in Fury Arena ( Quest )?
							else if (m_sPacketUserInfoLogin.sCharacterData[iCount].StartField == MAPID_QuestArena)
							{
								ECharacterRace iRace = GetCharacterRace(m_sPacketCharacterDataLogin.sCharacterData.iClass);

								m_sPacketUserInfoLogin.sCharacterData[iCount].StartField = iRace == CHARACTERRACE_Tempskron ?
									MAPID_RicartenTown : MAPID_PhillaiTown;
							}
						}
						iCount++;
					}
					if (!pcDB->Fetch())
						break;
				}
			}
		}
		pcDB->Close();
	}
	m_sPacketUserInfoLogin.CharCount = iCount;
	SENDPACKET(pcUser, &m_sPacketUserInfoLogin);

	AccountLogin al;
	STRINGCOPY(al.szAccountName, pcUser->szAccountName);

	// Log data
	if (pcUser)
		LogAccountLogin(pcUser, al, ACCLOGID_CharacterSelectSend);

	return TRUE;
}
void CServerAccount::DeleteCharacter(User * pcUser, PacketDeleteCharacter * psPacket)
{
	// Create Folder
	CreateDirectoryA("Data\\CharacterDelete", NULL);

	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);

	// User alive?
	if (pcUser)
	{
		// Mismatch UserID and not SQL Inject code?
		if (STRINGCOMPARE(pcUser->szAccountName, psPacket->szUserID))
		{
			// Old Character
			char szFilePath[128] = { 0 };
			STRINGFORMAT(szFilePath, "Data\\CharacterDelete\\%s.chr", psPacket->szCharname);

			// File exists? Delete
			if (FILEEXIST(szFilePath))
				DeleteFileA(szFilePath);

			// Move data to deleted folder ( backup if player delete acidentally )
			char szNewFilePath[128] = { 0 };

			ZeroMemory(szFilePath, 128);
			STRINGFORMAT(szFilePath, "Data\\Character\\%s.chr", psPacket->szCharname);
			STRINGFORMAT(szNewFilePath, "Data\\CharacterDelete\\%s.chr", psPacket->szCharname);

			// Success?
			if (MoveFileA(szFilePath, szNewFilePath))
			{
				// Move Row to deleted table characters and Delete from CharacterInfo
				if (pcDB->Open())
				{
					if (pcDB->Prepare("INSERT INTO CharacterInfoDelete SELECT * FROM CharacterInfo WHERE Name=?"))
					{
						pcDB->BindParameterInput(1, PARAMTYPE_String, psPacket->szCharname);
						pcDB->Execute();
					}
					pcDB->Close();
				}
				// Delete Character Info from Database
				if (pcDB->Open())
				{
					if (pcDB->Prepare("DELETE FROM CharacterInfo WHERE Name=?"))
					{
						pcDB->BindParameterInput(1, PARAMTYPE_String, psPacket->szCharname);
						pcDB->Execute();
					}
					pcDB->Close();
				}
				// Delete Premium Items from Database
				if (pcDB->Open())
				{
					if (pcDB->Prepare("DELETE FROM CharacterItemTimer WHERE CharacterName=?"))
					{
						pcDB->BindParameterInput(1, PARAMTYPE_String, psPacket->szCharname);
						pcDB->Execute();
					}
					pcDB->Close();
				}
			}
		}
	}
}
void CServerAccount::CharacterCreate(User * pcUser, PacketCreateCharacter * psPacket)
{
	// Is Userdata?
	if (pcUser)
	{
		char szDataPath[256] = { 0 };
		STRINGFORMAT(szDataPath, "Data\\Character\\%s.chr", psPacket->szCharname);
		psPacket->iCode = FALSE;

		int iLength = 0;

		iLength = STRLEN(psPacket->szUserID);

		if (iLength < 0 || iLength > 32)
			return;

		iLength = STRLEN(psPacket->szCharname);

		if (iLength < 0 || iLength > 32)
			return;

		// Character not exists?
		if (!FILEEXIST(szDataPath))
		{
			psPacket->iCode = TRUE;
			pcUser->dwHashCharacterName = GetCodebyName(psPacket->szCharname);
			STRINGCOPY(pcUser->szCharacterName, psPacket->szCharname);

			const char *pszDataTime = GetDateTime();

			// SQL Data
			{
				SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);
				if (pcDB->Open())
				{
					if (pcDB->Prepare("INSERT INTO CharacterInfo VALUES (?, ?, ?, 1, 0, 0, 0, 0, 0, 0, GETDATE(), 0, 0, 0, 1)"))
					{
						char szNull[2] = { 0,0 };
						pcDB->BindParameterInput(1, PARAMTYPE_String, psPacket->szUserID);
						pcDB->BindParameterInput(2, PARAMTYPE_String, psPacket->szCharname);
						pcDB->BindParameterInput(3, PARAMTYPE_String, szNull);
						pcDB->Execute();
					}
					pcDB->Close();
				}
			}

			// Log
			{
				char szLog[256] = { 0 };
				char * pszIP = NULL;

				if (pcUser->pcSocketData)
					pszIP = pcUser->pcSocketData->szIP;

				BOOL bServer = GAME_SERVER;

				STRINGFORMAT(szLog, "%s (New Character Created) -> Name \"%s\"",
					pcUser->szAccountName, psPacket->szCharname);

				SQLConnection * pcDB = SQLCONNECTION(DATABASEID_LogDB);

				if (pcDB->Open())
				{
					if (pcDB->Prepare("INSERT INTO AccountLog VALUES (?,?,?,?,?,?)"))
					{
						int iLogID = ACCLOGID_CharacterCreated;
						pcDB->BindParameterInput(1, PARAMTYPE_String, pszIP);
						pcDB->BindParameterInput(2, PARAMTYPE_String, pcUser->szAccountName);
						pcDB->BindParameterInput(3, PARAMTYPE_Integer, &iLogID);
						pcDB->BindParameterInput(4, PARAMTYPE_String, szLog);
						pcDB->BindParameterInput(5, PARAMTYPE_String, (void *)pszDataTime);
						pcDB->BindParameterInput(6, PARAMTYPE_Integer, &bServer);

						pcDB->Execute();
					}
					pcDB->Close();
				}

			}
		}

		SENDPACKET(pcUser, psPacket);
	}
}
BOOL CServerAccount::OnSelectSuccess(User * pcUser, const char *pszName, PacketCharacterRecordData *psPacketData)
{
	if (pcUser)
	{
		char szDataPath[256] = { 0 };
		STRINGFORMAT(szDataPath, "Data\\Character\\%s.chr", pszName);

		FILE * pFile = NULL;

		fopen_s(&pFile, szDataPath, "rb");

		// Character Data open?
		if (pFile)
		{
			// Read .chr File
			fseek(pFile, 0, SEEK_SET);
			fread(psPacketData, sizeof(PacketCharacterRecordData), 1, pFile);
			fclose(pFile);

			//Check Packet
			{
				INT64 iExp = psPacketData->sCharacterData.iExp;

				if (iExp < 0)
					psPacketData->sCharacterData.iExp = 0;

				psPacketData->sCharacterData.iLevel = SERVERCHARACTER->GetLevelFromExp(iExp);

				SERVERCHARACTER->CheckCharacterStatePoint(&psPacketData->sCharacterData,
					psPacketData->sCharacterSaveData.dwLevelQuestLog);

				psPacketData->sCharacterData.iClanID = 0;

				//iRank ?
				if (psPacketData->sCharacterData.iLevel < 20 && psPacketData->sCharacterData.iRank != 0)
					psPacketData->sCharacterData.iRank = 0;

				psPacketData->sCharacterSaveData.sPotionUpdate[1] = 1;

				BlessCastleStatusData * psBC = SERVERBLESSCASTLE->GetBlessCastleStatusData();

				psPacketData->sCharacterSaveData.BlessCastleTax = psBC->iTax;
				psPacketData->sCharacterSaveData.dwBlessCastleMaster = psBC->iClanID;
				psPacketData->sCharacterSaveData.TT_ServerID = pcUser->szServerID[0] ? ((DWORD *)pcUser->szServerID)[0] : 0;

				// Is in Sod?
				if (psPacketData->sCharacterSaveData.iMapID == MAPID_Bellatra)
					psPacketData->sCharacterSaveData.iMapID = MAPID_NaviskoTown;

				// Is in Fury Arena ( Quest )?
				if (psPacketData->sCharacterSaveData.iMapID == MAPID_Bellatra)
				{
					ECharacterRace iRace = GetCharacterRace(psPacketData->sCharacterData.iClass);
					
					psPacketData->sCharacterSaveData.iMapID = iRace == CHARACTERRACE_Tempskron ?
						MAPID_RicartenTown : MAPID_PhillaiTown;
				}

				psPacketData->sCharacterData.iID = SERVERUNIT->CreateID();

				// Is Player?
				if (psPacketData->sCharacterData.iMonsterEffectID != MONSTEREFFECTID_None ||
					psPacketData->sCharacterData.iType != CHARACTERTYPE_Player)
				{
					psPacketData->sCharacterData.iMonsterEffectID = MONSTEREFFECTID_None;
					psPacketData->sCharacterData.iType = CHARACTERTYPE_Player;
				}

				ReformCharForm(&psPacketData->sCharacterData);

				psPacketData->sCharacterSaveData.dwChecksum = GetCodeFromCharacterData(&psPacketData->sCharacterData);

				char *pData = (char *)psPacketData;

				//Total Size of Buffer
				UINT uSize = psPacketData->iLength;

				//Buffer Position
				UINT uBufferPosition = 0;

				int iTotalPage = (uSize / 0x1FE0);
				if ((uSize % 0x1FE0) > 0 && (uSize > 0x1FE0))
					iTotalPage++;

				int iCurrentPage = 0;

				//Create Packets
				do
				{
					//Write Encrypted Buffer into Packet Block
					PacketSaveData sPacket;
					ZeroMemory(&sPacket, sizeof(PacketSaveData));

					//Size of Block
					UINT uDataSize = uSize - uBufferPosition;
					if (uDataSize > 0x1FE0)
						uDataSize = 0x1FE0;

					//Packet Header
					sPacket.iLength = uDataSize + 20;
					sPacket.iHeader = PKTHDR_SaveData;
					sPacket.iCurrentPage = iCurrentPage++;
					sPacket.iTotalPage = iTotalPage;
					sPacket.iDataSize = uDataSize;

					//Copy into Packet
					CopyMemory(sPacket.szData, pData + uBufferPosition, uDataSize);

					SENDPACKET(pcUser, &sPacket);

					//Next Buffer
					uBufferPosition += uDataSize;
				}
				while (uBufferPosition < uSize);

				return TRUE;
			}
		}
	}

	return FALSE;
}
void CServerAccount::SelectCharacter(User * pcUser, PacketSelectCharacter * psPacket)
{
	if (!LOGIN_SERVER)
		return;

	if (pcUser)
	{
		// AcouunNma or id = null
		if (pcUser->szAccountName[0] && pcUser->iID == NULL)
		{
			// No Ban or GM
			if (pcUser->iGameLevel != GAMELEVEL_None || pcUser->BlockTime == NULL)
			{
				// on success
				BOOL bRet = TRUE; 

				for (int i = 0; i < PLAYERS_MAX; i++)
				{
					User * u = USERSDATA + i;

					if (u->pcSocketData && u->szAccountName[0] && pcUser != u)
					{
						if ((pcUser->dwHashAccountName == u->dwHashAccountName && STRINGCOMPAREI(pcUser->szAccountName, u->szAccountName)) ||
							(STRINGCOMPAREI(psPacket->szCharName, u->szCharacterName)))
						{
							// black
							SERVERNET->DisconnectUser(pcUser->pcSocketData);
							SERVERNET->DisconnectUser(u->pcSocketData);
							bRet = FALSE;
							break;
						}
					}
				}

				//In line
				if (bRet)
				{
					PacketCharacterRecordData *psPacketData = new PacketCharacterRecordData;

					ZeroMemory(psPacketData, sizeof(PacketCharacterRecordData));

					if (OnSelectSuccess(pcUser, psPacket->szCharName, psPacketData))
					{
						// Select Character
						STRINGCOPY(pcUser->szCharacterName, psPacket->szCharName);
						pcUser->dwHashCharacterName = GetCodebyName(pcUser->szCharacterName);

						//DropItem
						if (psPacketData->iDropItemCount > 0)
						{
							if (psPacketData->iDropItemCount > 64)
								psPacketData->iDropItemCount = 64;

							pcUser->ThrowItemCount = psPacketData->iDropItemCount;

							CopyMemory(pcUser->ThrowItemInfo, psPacketData->sDropItemData,
								sizeof(DropItemData) * pcUser->ThrowItemCount);
						}
						//Gold
						if (psPacketData->sCharacterSaveData.iLastGold > 0)
							pcUser->UnsaveMoney = psPacketData->sCharacterSaveData.iLastGold - 1;

						pcUser->dwElementaryQuestLogCheck = psPacketData->sCharacterSaveData.dwElementaryQuestLog;
						memcpy(pcUser->bSkillPoint, psPacketData->sCharacterSaveData.sSkillInfo.bSkillPoint, SKILL_POINT_COLUM_MAX);

						pcUser->sCharacterData.iLevel = psPacketData->sCharacterData.iLevel;
						pcUser->sCharacterData.iExp = psPacketData->sCharacterData.iExp;
						STRINGCOPY(pcUser->sCharacterData.szName, psPacketData->sCharacterData.szName);
						pcUser->sCharacterData.iClass = psPacketData->sCharacterData.iClass;
						pcUser->sCharacterData.iGold = psPacketData->sCharacterData.iGold;
						pcUser->liEXP.QuadPart = psPacketData->sCharacterData.iExp;
						pcUser->sCharacterData.iRank = psPacketData->sCharacterData.iRank;
						pcUser->sCharacterData.iClanID = psPacketData->sCharacterData.iClanID;
						pcUser->iID = psPacketData->sCharacterData.iID;

						int iGold = psPacketData->sCharacterSaveData.iLastGold > 0 ?
							psPacketData->sCharacterSaveData.iLastGold - 1 :
							psPacketData->sCharacterData.iGold;

						SERVERUSER->SetServerUserGold(pcUser, iGold, WHEREID_LoadPlayer);

						if (pcUser->psCharacterFile)
						{
							SERVERITEM->MakeInvenItem(pcUser,psPacketData);

							if (psPacketData->iLength <= 0x6000)
								memcpy(pcUser->psCharacterFile, psPacketData, psPacketData->iLength);

							SERVERITEM->ComparePotion(pcUser, &psPacketData->sCharacterSaveData);
							SERVERITEM->LoadForce(pcUser, &psPacketData->sCharacterSaveData);
						}

						if (psPacketData->sCharacterData.iLevel > UNIT_LEVEL_MAX)
						{
							//LOG
							// Level very Height
							SERVERNET->DisconnectUser(pcUser->pcSocketData);
						}
					}
					else
					{
						//new Character
						PacketSimple sPacket;

						ZeroMemory(&sPacket, sizeof(PacketSimple));

						pcUser->iID = SERVERUNIT->CreateID();

						sPacket.iLength = sizeof(PacketSimple);
						sPacket.iHeader = PKTHDR_NewCharacter;
						sPacket.iUnk2 = pcUser->iID;

						SENDPACKET(pcUser, &sPacket);

						pcUser->sCharacterData.iID = pcUser->iID;
						pcUser->sCharacterData.iRank = 0;
						ZeroMemory(pcUser->bSkillPoint, SKILL_POINT_COLUM_MAX);

						SENDPACKETBLANK(pcUser, PKTHDR_Save);
					}

					DELET(psPacketData);

					SERVERUSER->OnLoadUser(pcUser);
				}
			}
		}
	}
}
UINT CServerAccount::OnSaveSuccess(User *pcUser, PacketSaveData *psPacket)
{
	if (pcUser)
	{
		PacketCharacterRecordData *psCharacterData = pcUser->psCharacterData;

		if (psPacket->iDataSize > 0x1FE0)
			psPacket->iDataSize = 0x1FE0;

		BYTE *baData = (BYTE *)psCharacterData;

		memcpy(baData + psPacket->iCurrentPage * 0x1FE0, psPacket->szData, psPacket->iDataSize);

		if (psPacket->iCurrentPage > pcUser->iCurrentBlock)
		{
			//LOG Error
			return -1;
		}
		else
			pcUser->iCurrentBlock++;

		if (psPacket->iCurrentPage >= psPacket->iTotalPage - 1 && psCharacterData->iHeader == PKTHDR_SaveData)
		{
			psCharacterData->sCharacterSaveData.iSaveTime = (DWORD)SERVER_LOCATIME;

			//CharacterData vail
			if (CheckCharForm(&psCharacterData->sCharacterData) == FALSE)
			{
				PacketLogCheat sPacket;
				sPacket.iCheatID = CHEATLOGID_CharInfoSaveError;
				sPacket.iLParam = -1;
				SERVERLOG->LogCheat(pcUser, &sPacket);
				return -1;
			}
			//CheckCharacterName
			if (pcUser->iGameLevel < GAMELEVEL_Three && lstrcmp(psCharacterData->sCharacterData.szName, pcUser->szCharacterName) != 0)
			{
				PacketLogCheat sPacket;
				sPacket.iCheatID = CHEATLOGID_WrongSavingCharacterName;
				sPacket.iLParam = -1;
				SERVERLOG->LogCheat(pcUser, &sPacket);
				return -1;
			}
			//CheckLevel
			if (psCharacterData->sCharacterData.iLevel < pcUser->sCharacterData.iLevel)
			{
				//LOG Error
				return -1;
			}
			//CheckItem
			if (SERVERITEM->CheckInvenItem(psCharacterData) == FALSE)
			{
				//LOG Error
				return -1;
			}
			//Check StatePoint
			if (SERVERCHARACTER->CheckCharacterStatePoint(&psCharacterData->sCharacterData, 
				psCharacterData->sCharacterSaveData.dwLevelQuestLog) == FALSE)
			{
				//LOG Error
				return -1;
			}
			//Check Exp
			if (psCharacterData->sCharacterData.iExp > pcUser->liEXP.QuadPart)
			{
				psCharacterData->sCharacterData.iExp = pcUser->liEXP.QuadPart;
			}
			//Check SkillPoint
			if (SERVERCHARACTER->CheckCharacterSkillPoint(psCharacterData->sCharacterData.iLevel,
				&psCharacterData->sCharacterSaveData.
				sSkillInfo, psCharacterData->sCharacterSaveData.dwLevelQuestLog) == FALSE)
			{
				//LOG Error
				return -1;
			}

			CopyMemory(pcUser->bSkillPoint, psCharacterData->sCharacterSaveData.sSkillInfo.bSkillPoint, SKILL_POINT_COLUM_MAX);

			//Check Wight
			if (psCharacterData->sCharacterData.sWeight.sMin < 0 ||
				psCharacterData->sCharacterData.sWeight.sMin > psCharacterData->sCharacterData.sWeight.sMax + 2000)
			{
				//LOG Error
				return -1;
			}

			if (pcUser->sCharacterData.iClass == 0)
				pcUser->sCharacterData.iClass = psCharacterData->sCharacterData.iClass;

			if (pcUser->iGameLevel < GAMELEVEL_Two && pcUser->sCharacterData.iClass != psCharacterData->sCharacterData.iClass)
			{
				//LOG Error
				return -1;
			}
			//Check Map Level
			int iMapID = psCharacterData->sCharacterSaveData.iMapID;

			if (iMapID < 0 || iMapID > _countof(iaMapsLevel) || iaMapsLevel[iMapID] > psCharacterData->sCharacterData.iLevel)
			{
				//LOG Error
				return -1;
			}

			pcUser->iMapID = (EMapID)iMapID;

			if (psCharacterData->sCharacterData.sHP.sMin == 0)
			{
				psCharacterData->sCharacterData.sHP.sMin = psCharacterData->sCharacterData.sHP.sMax / 2;

				int iRace = GetCharacterRace(psCharacterData->sCharacterData.iClass);

				if (iRace == CHARACTERRACE_Tempskron)
				{
					psCharacterData->sCharacterSaveData.iMapID = MAPID_RicartenTown;
					psCharacterData->sCharacterSaveData.iCameraPositionX = 746752;
					psCharacterData->sCharacterSaveData.iCameraPositionZ = -4464384;
				}
				else if (iRace == CHARACTERRACE_Morion)
				{
					psCharacterData->sCharacterSaveData.iMapID = MAPID_PhillaiTown;
					psCharacterData->sCharacterSaveData.iCameraPositionX = 505344;
					psCharacterData->sCharacterSaveData.iCameraPositionZ = 18948864;
				}
			}

			STRINGCOPY(psCharacterData->sCharacterSaveData.szMasterID, pcUser->szAccountName);

			int uSize = psCharacterData->iLength;

			if (uSize < 0x4000)
				uSize = 0x4000;

			if (pcUser->psCharacterFile && uSize <= 0x6000)
				CopyMemory(pcUser->psCharacterFile, psCharacterData, sizeof(CharacterFile));
			else
			{
				char szDataPath[256] = { 0 };

				STRINGFORMAT(szDataPath, "Data\\Character\\%s.chr", pcUser->szCharacterName);

				char szDataBackupPath[256] = { 0 };

				STRINGFORMAT(szDataBackupPath, "Data\\CharacterBackup\\%s.chr", pcUser->szCharacterName);

				CopyFile(szDataPath, szDataBackupPath, FALSE);

				CharacterFile *pCharacterFile = pcUser->psCharacterFile;

				pcUser->psCharacterFile = (CharacterFile *)psCharacterData;

				SERVERUSER->SaveDropItem(pcUser);

				SERVERUSER->InventoryServerCheck(pcUser);

				FILE * pFile = NULL;

				fopen_s(&pFile, szDataPath, "wb");

				if (pFile)
				{
					fseek(pFile, 0, SEEK_SET);
					fwrite(psCharacterData, uSize, 1, pFile);
					fclose(pFile);
				}

				pcUser->psCharacterFile = pCharacterFile;
				pcUser->psCharacterFile->iLength = 0;
			}

			return 1;
		}
	}
	
	return 0;
}
void CServerAccount::SaveCharacter(User *pcUser, PacketSaveData *psPacket)
{
	if (pcUser->szAccountName[0] && pcUser->dwDisconnectTime == 0)
	{
		if (pcUser->psCharacterData == NULL)
		{
			pcUser->psCharacterData = new PacketCharacterRecordData;
			pcUser->iCurrentBlock = 0;
		}
		int iVaild = OnSaveSuccess(pcUser, psPacket);

		if (iVaild > 0)
		{
			pcUser->iCurrentBlock = 0;
			pcUser->TradePotionInfoCount = 0;
			pcUser->sCharacterData.iLevel = pcUser->psCharacterData->sCharacterData.iLevel;
			pcUser->sCharacterData.iExp = pcUser->psCharacterData->sCharacterData.iExp;
			pcUser->sCharacterData.iGold = pcUser->psCharacterData->sCharacterData.iGold;

			if (pcUser->psCharacterData->sCharacterData.iClanID)
				pcUser->sCharacterData.iClanID = pcUser->psCharacterData->sCharacterData.iClanID;

			if (pcUser->sCharacterData.iRank != pcUser->psCharacterData->sCharacterData.iRank)
			{
				SERVERITEM->T2ItemCheck(pcUser, pcUser->psCharacterData->sCharacterData.iRank);
				pcUser->sCharacterData.iRank = pcUser->psCharacterData->sCharacterData.iRank;
			}

			SQLUpdateCharacter(pcUser->szCharacterName, pcUser->sCharacterData.iClass, pcUser->sCharacterData.iLevel, pcUser->liEXP.QuadPart, pcUser->GetGold(), pcUser->GetMapID());

			if (abs(int(SERVER_GAMETIME - pcUser->dwRecordDataTime)) > 30 * 60 * 1000)
			{
				if (pcUser->psCharacterFile && pcUser->psCharacterFile->iLength > 0)
				{
					if (SaveFile(pcUser, pcUser->psCharacterData->sCharacterData.szName, (PacketCharacterRecordData *)pcUser->psCharacterFile))
					{
						pcUser->dwRecordDataTime = SERVER_GAMETIME;
					}
					else
					{
						//LOG Error
					}
				}
			}

			pcUser->ThrowItemCount = 0;
			pcUser->UnsaveMoney = -1;
			pcUser->dwLastSaveTime = SERVER_GAMETIME;

			BlessCastleStatusData * psBC = SERVERBLESSCASTLE->GetBlessCastleStatusData();

			PacketSaveResult sPacket;

			ZeroMemory(&sPacket, sizeof(PacketSaveResult));

			sPacket.iLength = sizeof(PacketSaveResult);
			sPacket.iHeader = PKTHDR_SaveResult;
			sPacket.bResult = TRUE;
			sPacket.iTex = psBC->iTax;
			sPacket.iClanID = psBC->iClanID;

			SENDPACKET(pcUser, &sPacket);

			DELET(pcUser->psCharacterData);

			SERVERBLESSCASTLE->SendBlessCastleSkill(pcUser);
		}
		else if (iVaild < 0)
		{
			PacketSaveResult sPacket;

			BlessCastleStatusData * psBC = SERVERBLESSCASTLE->GetBlessCastleStatusData();

			ZeroMemory(&sPacket, sizeof(PacketSaveResult));

			sPacket.iLength = sizeof(PacketSaveResult);
			sPacket.iHeader = PKTHDR_SaveResult;
			sPacket.bResult = FALSE;
			sPacket.iTex = psBC->iTax;
			sPacket.iClanID = psBC->iClanID;

			SENDPACKET(pcUser, &sPacket);

			DELET(pcUser->psCharacterData);

			pcUser->dwDisconnectTime = SERVER_GAMETIME + 3000;
		}
	}
}
BOOL CServerAccount::SaveFile(User *pcUser, const char *pszName, PacketCharacterRecordData *psPacketData)
{
	if (pcUser && pszName[0])
	{
		if (psPacketData && psPacketData->iLength > 0)
		{
			char szDataPath[256] = { 0 };

			char * pszCharacterName = pcUser->szCharacterName;

			STRINGFORMAT(szDataPath, "Data\\Character\\%s.chr", pszCharacterName);

			char szDataBackupPath[256] = { 0 };

			STRINGFORMAT(szDataBackupPath, "Data\\CharacterBackup\\%s.chr", pszCharacterName);

			CopyFile(szDataPath, szDataBackupPath, FALSE);

			int uSize = psPacketData->iLength;

			if (uSize < 0x4000)
				uSize = 0x4000;

			SERVERITEM->SavePotion(pcUser, &psPacketData->sCharacterSaveData);
			SERVERITEM->SaveForce(pcUser, &psPacketData->sCharacterSaveData);

			SQLUpdateCharacter(pszCharacterName, pcUser->sCharacterData.iClass, pcUser->sCharacterData.iLevel, pcUser->liEXP.QuadPart, pcUser->GetGold(), pcUser->GetMapID());

			FILE * pFile = NULL;

			fopen_s(&pFile, szDataPath, "wb");

			if (pFile)
			{
				fseek(pFile, 0, SEEK_SET);
				fwrite(psPacketData, uSize, 1, pFile);
				fclose(pFile);

				return TRUE;
			}
		}
	}

	return FALSE;
}
void CServerAccount::SQLUpdateCharacter(char * pszCharacterName, int iCharacterClass, int iCharacterLevel, INT64 iCharacterExperience, int iCharacterGold, int iStageID)
{
	if (LOGIN_SERVER)
	{
		SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);
		if (pcDB->Open())
		{
			if (pcDB->Prepare("UPDATE CharacterInfo SET Level=?, JobCode=?, Experience=?, Gold=?, LastStage=? WHERE Name=?"))
			{
				pcDB->BindParameterInput(1, PARAMTYPE_Integer, &iCharacterLevel);
				pcDB->BindParameterInput(2, PARAMTYPE_Integer, &iCharacterClass);
				pcDB->BindParameterInput(3, PARAMTYPE_Int64, &iCharacterExperience);
				pcDB->BindParameterInput(4, PARAMTYPE_Integer, &iCharacterGold);
				pcDB->BindParameterInput(5, PARAMTYPE_Integer, &iStageID);
				pcDB->BindParameterInput(6, PARAMTYPE_String, pszCharacterName);
				pcDB->Execute();
			}
			pcDB->Close();
		}
	}
}