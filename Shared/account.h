#pragma once

#define _REQUIREACCOUNTVALIDATION

#define MAX_ACCOUNTNAMELEN			32
#define MAX_PASSWORDLEN				32
#define MAX_ACCOUNTLOGINQUEUE		100
#define MAX_CHARACTERSPERACCOUNT	5

enum EBanStatus
{
	BANSTATUS_Error = -1,
	BANSTATUS_NotBanned = 0,
	BANSTATUS_Banned = 1,
	BANSTATUS_TempBanned = 2,
	BANSTATUS_BanExpired = 3,
};

enum EAccountLogin
{
	ACCOUNTLOGIN_Success = 1,	//[Successful]
	ACCOUNTLOGIN_ConnectionFailed = 0,	//Connecting failed
	ACCOUNTLOGIN_IncorrectName = -1,	//Account does not exist in the selected world
	ACCOUNTLOGIN_IncorrectPassword = -2,	//Incorrect Password
	ACCOUNTLOGIN_Banned = -3,	//Account is banned
	ACCOUNTLOGIN_LoggedIn = -4,	//Account is already logged in
	ACCOUNTLOGIN_IPBanned = -5,	//Your IP is banned
	ACCOUNTLOGIN_YouAreBanned = -6,	//Your IP is banned
	ACCOUNTLOGIN_TryAgain = -7,	//[Game will automatically retry]
	ACCOUNTLOGIN_Maintenance = -8,	//Server is in Maintenance
	ACCOUNTLOGIN_AccountNotActive = -16,	//Account not active, see User Management Panel
	ACCOUNTLOGIN_WrongVersion = -17,	//Version does not Match
	ACCOUNTLOGIN_TempBanned = -18,	//Temporarily Banned
};



enum EAccountFlag
{
	ACCOUNTFLAG_NotExist = -1,
	ACCOUNTFLAG_Invalid = 0,
	ACCOUNTFLAG_Mule = 1,
	ACCOUNTFLAG_Activated = 2,
	ACCOUNTFLAG_EventGM = 4,
	ACCOUNTFLAG_Supporter = 8,
	ACCOUNTFLAG_GameMaster = 16,
	ACCOUNTFLAG_AcceptedLatestTOA = 32,
	ACCOUNTFLAG_Approved = 64,
	ACCOUNTFLAG_MustConfirm = 128,
	ACCOUNTFLAG_GMIPRequired = 256,
};

enum ECharacterLog
{
	CHARACTERLOG_Create = 1,
	CHARACTERLOG_Delete = 2,
	CHARACTERLOG_Update = 3,
};

const int iLogAccountBase = 500;

enum
{
	MSGLOGINID_UnauthorizedMaintenanceLogin = 0,
	MSGLOGINID_Maintenance = -8,
	MSGLOGINID_UnknownErrorLogin = 0,
	MSGLOGINID_IncorrectPassword = -2,
	MSGLOGINID_IncorrectAccount = -1,
	MSGLOGINID_BlockedAccount = -3,
	MSGLOGINID_LoggedAccount = -4,
	MSGLOGINID_YouAreBanned = -6,
	MSGLOGINID_TempBanned = -18,
	MSGLOGINID_NotActivatedAccount = -16,
};

enum ELogAccount
{
	ACCLOGID_LoginSuccess			= iLogAccountBase + 1,
	ACCLOGID_IncorrectAccount		= iLogAccountBase + 2,
	ACCLOGID_IncorrectPassword		= iLogAccountBase + 3,
	ACCLOGID_BlockedAccount			= iLogAccountBase + 4,
	ACCLOGID_NotActivatedAccount	= iLogAccountBase + 5,
	ACCLOGID_CharacterSelectSend	= iLogAccountBase + 6,
	ACCLOGID_CharacterCreated		= iLogAccountBase + 7,
	ACCLOGID_CharacterDeleted		= iLogAccountBase + 9,
	ACCLOGID_UnblockedAccount		= iLogAccountBase + 10,
	ACCLOGID_CharacterSave			= iLogAccountBase + 11,
	ACCLOGID_CharacterExpLose		= iLogAccountBase + 12,
	ACCLOGID_TempBanAccount			= iLogAccountBase + 13,
	ACCLOGID_CharacterQuestGot		= iLogAccountBase + 301,
	ACCLOGID_CharacterQuestCancel	= iLogAccountBase + 302,
	ACCLOGID_CharacterQuestFinished = iLogAccountBase + 303,
	ACCLOGID_CharacterQuestEXP		= iLogAccountBase + 304,
	ACCLOGID_CharacterQuestEXPLose	= iLogAccountBase + 305,

	// PostBox
	ACCLOGID_ReceivedPostBox		= iLogAccountBase + 8,

};

struct AccountFileData
{
	char	  szHeader[16];
	char	  szAccountName[32];
	char	  szCharacterName[MAX_CHARACTERSPERACCOUNT + 1][32];
};

struct PacketAccountLoginCode : Packet
{
	DWORD			  dwReserved;
	EAccountLogin	  iCode;
	int				  iFailCode;

	char			  szMessage[256];
};

struct PacketAccountID : Packet
{
	ID				  lAccountID;
};

struct AccountLogin
{
	User				* pcUser;
	SocketData			* pcSocketData;

	char				szAccountName[32];
	char				szPassword[32];
	char				szIP[20];
	char				szMacAddress[20];

	UINT				uSerialHD;
	char				szPCName[32];
	char				szVideoName[256];

	UINT				uWidthScreen;
	UINT				uHeightScreen;
	int					iSystemOS;
};