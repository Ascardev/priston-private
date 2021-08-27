#pragma once

class CServerAccount
{
public:
	CServerAccount();
	virtual ~CServerAccount();

	void DisconnectUser(User* pcUser);
	void LogAccountLogin(User * pcUser, AccountLogin & al, ELogAccount eLogAccount);
	BOOL IsOnlineAccount(User * pcUser, const char * pszUserID);
	BOOL IsIPAccept(const char * pszIP);
	BOOL IsMacBanned(const char * pszMacAddress);
	BOOL IsSerialHDBanned(const char * pszSerialHD);
	BOOL IsComputerNameBanned(const char * pszPCName);
	BOOL IsAccountAccept(const char * pszAccountName);
	BOOL IsAdminMacAddress(const char * pszMacAddress, UINT uSerialHD);

	void SQLUserOnline(char * pszAccountName, char * pszCharacterName, char * pszIP, int iTicket, int iAction, int iCharacterClass, int iCharacterLevel);
	void SQLCharacterSave(User * pcUser);
	void PHAccountLogin(User * pcUser, PacketLoginUser * psPacket);

	BOOL AddAccountLogin(User * pcUser, AccountLogin & al);
	static EAccountFlag SQLAccountGetFlag(char * pszAccountName);
	static BOOL SQLUnbanAccount(char * pszAccountName);
	static EGameLevel SQLGetGameMaster(char * pszAccountName);

	void OnGameMasterCheck(User * pcUser);


	static int SQLGetBanStatus(char * pszAccountName, SYSTEMTIME * psBanTime);

	static EAccountLogin SQLAccountLogin(char * pszAccountName, char * pszPassword, char * pszIP, EAccountFlag iAccountFlag, SYSTEMTIME & sUnbanDate);
	static void ProcessAccountLogin(AccountLogin & al);
	static DWORD WINAPI ProcessAccountLoginQueue();

	std::vector<std::string> SQLGetAccountNotification(const char * pszAccountName);

	BOOL OnLoginSuccess(User * pcUser);

	void DeleteCharacter(User * pcUser, PacketDeleteCharacter * psPacket);
	void CharacterCreate(User * pcUser, PacketCreateCharacter * psPacket);

	BOOL OnSelectSuccess(User * pcUser, const char *pszName, PacketCharacterRecordData *psPacketData);
	void SelectCharacter(User * pcUser, PacketSelectCharacter * psPacket);

	UINT OnSaveSuccess(User *pcUser, PacketSaveData *psPacket);
	void SaveCharacter(User *pcUser, PacketSaveData *psPacket);

	BOOL SaveFile(User *pcUser, const char *pszName, PacketCharacterRecordData *psPacketData);

	void SQLUpdateCharacter(char * pszCharacterName, int iCharacterClass, int iCharacterLevel, INT64 iCharacterExperience, int iCharacterGold,int iStageID);
public:
	static BOOL bActive;
	static int iWaitingAccountLogins;
	static AccountLogin saAccountLogin[MAX_ACCOUNTLOGINQUEUE];
	static CMutex * pcMutex;
private:
	PacketUserInfo m_sPacketUserInfoLogin;
	PacketCharacterRecordData m_sPacketCharacterDataLogin;
};