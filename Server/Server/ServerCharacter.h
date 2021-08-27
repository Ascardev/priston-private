#pragma once


class CServerCharacter
{
public:
	CServerCharacter();
	virtual ~CServerCharacter();

	char * GetServerName(User * pcUser);
	char * GetCharacterName(User * pcUser);
	BOOL CharacterInCityStage(User * pcUser);
	int SQLGetCharacterClass(char * pszCharacterName);
	int SQLGetCharacterID(char * pszName);
	int SQLGetCharacterClanID(char * pszCharacterName);

	BOOL IsCharacterLeader(User * pcUser);

	void SetExp(User * pcUser, INT64 iExp);
	void GiveEXP(User * pcUser, INT64 iExp);
	INT64 GetExpFromLevel(int iLevel);
	INT64 GetExp(User * pcUser);
	int GetLevelFromExp(INT64 iExp);
	int GetStatePointFromQuestLevel(int iLevel, DWORD dwQuestLevel);
	int GetSkillPointFromQuestLevel(int iLevel, DWORD dwQuestLevel);
	BOOL CheckCharacterStatePoint(CharacterData *psCharacterData, DWORD dwQuestLevel);
	BOOL CheckCharacterSkillPoint(int iLevel, RecordSkill *pSkill, DWORD dwQuestLevel);
	void OnLoseExp(User * pcUser, PacketLoseExperience * psPacket);
	void SetPositionWarp(User * pcUser, int iX, int iZ, int iStageID);
	void GiveGold(User * pcUser, int iGold, EWhereAction eWhere = WHEREID_GiveMoney);
	void OnCharacterSyncData(User * pcUser);
	void OnCharacterSyncDataEx(User * pcUser, PacketPlayDataEx * psPacket);

	void UpdateForceOrb(User * pcUser);
	void UpdatePremiumTimer(User * pcUser);
	void CheckGold(User * pcUser);

	void GiveGameMaster(User * pcUser, int iGameLevel);

	void OnCharacterDataExSave(User * pcUser);

	void HandlePacket(User * pcUser, PacketCharacterDataEx * psPacket);
	void SendCharacterDataEx(User * pcUser);
};