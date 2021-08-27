#pragma once

enum ESQLServerCommand
{
	SQLSERVERCOMMAND_ChangeCharacterName	= 10,
	SQLSERVERCOMMAND_ChangeCharacterLevel	= 11,
	SQLSERVERCOMMAND_ChangeCharacterAccount = 12,
	SQLSERVERCOMMAND_ChangeCharacterClass	= 13,

	SQLSERVERCOMMAND_ChangeAccountName		= 20,

	SQLSERVERCOMMAND_KickAccountName		= 30,
	SQLSERVERCOMMAND_KickCharacterName		= 31,

	SQLSERVERCOMMAND_LoadCoinShop			= 101,
	SQLSERVERCOMMAND_LoadCheatList			= 111,
	SQLSERVERCOMMAND_LoadMixFormula			= 121,
};

struct SQLServerCommand
{
	ESQLServerCommand	iType;
	char				szOperator[32];
	char				szParameter1[64];
	char				szParameter2[64];
	char				szParameter3[64];
	SYSTEMTIME			sDateSubmitted;
	SYSTEMTIME			sDateProcessed;
};

class CServerCommand
{
public:
	CServerCommand();
	virtual ~CServerCommand();

	void CheckUserOnline(User * pcUser, PacketUserOnline * psPacket);
	void OnActivateGameMaster(User * pcUser);
	BOOL OnGameMasterCommand(User * pcUser, char * pszBuff);
	void OnGameMasterEventCommand(User * pcUser, char * pszBuff);
	void OnGameMasterAdminCommand(User * pcUser, char * pszBuff);
	BOOL OnPlayerCommand(User * pcUser, char * pszBuff);
	void OnReceiveChat(User * pcUser, PacketChat * psPacket);
	void AddCommand(int iCommandID, char * pszParameter1, char * pszParameter2, char * pszParameter3);
	BOOL SQLReadFromCharacter(const char * pszCharacterName, ESQLServerCommand iCommand, SQLServerCommand & s);
};