#pragma once

#define USERSDATA		(SERVERUSER->pcaUser)
#define CHARSDATA		(SERVERUSER->pcaCharacterFile)
#define USERS_ONLINE	(SERVERUSER->uUsersInGame)

class CServerUser
{
public:
	CServerUser();
	virtual ~CServerUser();

	User *pcaUser = nullptr;
	User **pcaUserInGame = nullptr;
	int uUsersInGame = 0;

	CharacterFile *pcaCharacterFile = nullptr;

	User *GetFreeUser();
	void AddReconnectUser(User * pcUser);
	BOOL DeleteReconnectUser(const char * pszAccountName);
	void ReconnectUser(User * pcUser, struct PacketReconnectUser * psPacket);
	BOOL SetUserID(User * pcUser);
	void UpdateID(User * pcUser);

	void OnLoadUser(User * pcUser);
	void OnUnLoadUser(User * pcUser);

	void Update();
	void UpdateUnitStatus(User * pcUser);
	void UpdateSkillStatus(User * pcUser);

	void Loop();
	void LoopUsers(User * pcUser);
	void LoopUnits(User * pcUser);

	void SendUnitStatus(User * pcUser, Packet * psPacket, BOOL bIncrementAmount = TRUE);
	void SendUnitStatusM(User * pcUser, Packet * psPacket, BOOL bIncrementAmount = TRUE);
	void SendSkillStatus(User * pcUser, PacketSkillStatus * psPacket);

	void ClearUnitStatus(User * pcUser);
	void ClearUnitStatusM(User * pcUser);
	void ClearSkillStatus(User * pcUser);

	void HandlePacket(User *pcUser, PacketPlayData * psPacket);
	void OnUserSyncData(User *pcUser, PacketPlayInfo *psPacket);

	void ResetSkills(User *pcUser);

	void SettingsDataSet(User * pcUser, PacketSettingsData * psPacket);

	void DisconnectUser(User * pcUser);

	DWORD AllowPacket(User * pcUser);

	void SaveDropItem(User *pcUser);
	void SaveDropItemOver(User *pcUser, ItemID sItemID, int iChk1, int iChk2);
	void SaveDropItem(User *pcUser, ItemID sItemID, int iChk1, int iChk2);
	void CheckMapLevel(User *pcUser);

	BOOL InventoryServerCheck(User *pcUser, int iUnused = 0);

	User *GetUser(int iID);
	User *GetUser(const char *pszCharacterName);
	User *GetUserByAccount(const char * pszAccountName);

	void OnKilled(User * pcUser, PacketDeadCharacter * psPacket);

	void AddServerUserGold(User * pcUser, int iGold, EWhereAction eWhere);
	void SubServerUserGold(User * pcUser, int iGold, EWhereAction eWhere);
	void SetServerUserGold(User * pcUser, int iGold, EWhereAction eWhere);

	int SQLGetAccountID(const char * pszAccountName);
	char * SQLGetAccountByCharacterName(const char * pszCharacterName);

	void CancelForceOrb(User * pcUser);

	BOOL GetClanLeaderAccount(int iClanID, char szLeaderAccount[32]);
	BOOL GetClanName(int iClanID, char szName[32]);
	BOOL IsClanID(User * pcUser, int iID);
};
