#pragma once

class Unit;

#define UNITSDATA		(SERVERUNIT->pcaUnit)

class CServerUnit
{
public:
	CServerUnit();
	virtual ~CServerUnit();

	Unit *pcaUnit = nullptr;
	Unit **pcaUnitInGame = nullptr;

	int uUnitsInGame = 0;
	int iActiveWheel = 0;

	BOOL bFreeExpEvent = FALSE;
	int iExpFreeExp = 50;

	void Init();
	void Shutdown();

	void LoadUnit();
	void LoadUnitEnemyData();

	void Update();
	void UpdateUnit(Unit *pcUnit);
	BOOL UpdateUnitData(Unit * pcUnit);
	BOOL HandleKill(Unit * pcUnit, User * pcUser);

	BOOL OnUnitNpcClick(User * pcUser, Unit * pcUnit);

	void OnSetDrop(User * pcUser, Unit * pcUnit);
	void OnSendExp(User * pcUser, Unit * pcUnit);

	void ProcessPacketKillUnitID(User * pcUser, int iID);
	void ProcessPacketEffectWarp(User * pcUser, Point3D sPosition);
	void ProcessPacketEffectResurrection(User * pcUser, int iID);
	void ProcessPacketEffectValento(User * pcUser, int iMonsterID, int iUserID);
	void ProcessPacketEffectHolyIncAntation(User * pcUser, int iID, int iTime);

	void HandlePacket(User * pcUser, PacketUserEffect * psPacket);
	void HandlePacket(User * pcUser, PacketUseGold * psPacket);

	INT64 GetExpLevelDiference(int iLevel1, int iLevel2, INT64 iExp);

	std::vector<CharacterData *> GetMonsterTable() { return m_vMonsterTable; }

	Unit * GetUnitFromPosition(int iX, int iY, int iZ);

	BOOL IsMultiplyHPMonter(Unit * pcUnit, BOOL bMulit = FALSE);

	Unit * GetEmptyUnit();
	Unit * GetUnit(UINT iID, EMapID iMapID = MAPID_Invalid);

	Unit * GetPetUnit(Unit *pcMasterUnit);

	int GetTotalHP(Unit * pcUnit);
	int IsFreezedUnitFollow(Unit * pcUnit);

	ID CreateID();

	CharacterData * GetCharacterDataByEffect(DWORD dwEffect, int iClass = 0);
	CharacterData * GetCharacterDataByName(const char * pszName);

	Unit *CreateUnitEnemy(const char * pszName, int iX, int iY, int iZ, User * pcUser = NULL);
	BOOL OnUnitChanger(Unit * pcUnit);

	void UnitSwapper(Unit *pcUnit, CharacterData *psCharacterData, UnitInfo *psUnitInfo);

	void CreateEventUnit(UINT uCode);
	void FreeEventUnit(UINT uCode);
	void ReadUnitNpcData(CharacterData * pCharInfo, UnitInfo *pMonInfo, char *pDialogMessage);
protected:
	BOOL IsPet(Unit *pcUnit);
	BOOL IsSafeStuckUnit(Unit * pcUnit);
	BOOL IsEventItem(DWORD iItemID, User *pcUser, Unit *pcUnit);
	EMonsterEffectID GetEnemyEffect(char * pszEffect);
	void ReadDropItem();
	BOOL EnemyDataItem(UnitInfo * pMonsterInfo, const char * pszItems, int iChance, int iGoldMin, int iGoldMax);
	const char *SetNpcMessage(const char *pDialogMessage);
private:
	Unit *m_pcUnit = nullptr;
	std::vector<CharacterData *> m_vMonsterTable;
	std::map<int, std::string> m_sMessage;
};