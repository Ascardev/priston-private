#pragma once

class CServerMap
{
public:
	CServerMap();
	virtual ~CServerMap();

	EMapID eBabelMapID;
	DWORD  dwBabelEndTime;

	void Init();
	void Shutdown();

	void Load();

	void Update();
	void UpdateMap(Map * pcMap);

	std::vector<Map *> GetMapTable() { return m_vpMap; }

	Map * GetMap(EMapID iMapID);

	BOOL IsValidMap(Map *pcMap);

	void SendItemStageNearUsers(Map * pcMap, MapLoot * psItemStage);
	void SendItemStageUser(Map * pcMap, User * pcUser, MapLoot * psItemStage);
	void SendStageSpawn(Map * pcMap, User * pcUser);
	void SendStageItem(Map * pcMap, User * pcUser);
	MapLoot * FindItemStage(Map * pcMap, Point3D sPosition);
	MapLoot * AddItem(Map * pcMap, LootItem * psItem, Point3D sPosition, BOOL bNewItem = FALSE);
	void DelItem(Map * pcMap, MapLoot * psItem);

	BOOL IsEXPMap(int iMapID);
	BOOL IsPVPMap(int iMapID);
	BOOL IsTownMap(int iMapID);

	BOOL IsNight() { return m_bNight; }
	int GetTime() { return m_iTime; }
	int GetBossTimeMin() { return m_iBossTime; }

	Map *GetMapByXZ(int iX, int iZ);
	void SpawnMonsterBoss(Map * pcMap, BossMonster *psBoss);

	BOOL SetBossPosition(Map * pcMap, CharacterData * psCharacterData, Point3D &sPosition);
	BOOL AddMonsterSpawn(Map * pcMap, Unit * pcUnit);
	BOOL DelMonsterSpawn(Map * pcMap, Unit * pcUnit);
	BOOL SetSpawnMonster(Map * pcMap, Unit * pcUnit);
	BOOL SetSpawnMonster(Map * pcMap, Unit * pcUnit, Point3D sPosition);
	void SetSpawnMonster(Map * pcMap);

	BOOL SpawnMonsterBC(Map * pcMap, CharacterData * psCharacterData, Point3D sPosition, int iClanID);

	void AddFlagPoint(User * pcUser, const char * pszDescription);
	void DeleteFlagPoint(User * pcUser, PacketDeleteFlagPoint * psPacket);
	
	void AddMapSpawnData(Map * pcMap, const char * pszName, int iID, int iX, int iZ);
	void DelMapSpawnData(Map * pcMap, int iX, int iZ);

	Unit *CreateUnit(Map * pcMap, CharacterData * psCharacterData, int iGroup = 0);
	void SpawnNPC(Map * pcMap, PacketUnitInfo * psPacket);

	BOOL SpawnCrystal(EItemID iItemID, int iX, int iY, int iZ, User * pcUser);

	Unit * CreateUnitByID(ESkillPlayID iID, int iX, int iY, int iZ, User * pcUser, Unit * pcUnit);
	BOOL HandleUnitQuestMap(Map * pcMap, Unit * pcUnit);
	void HandlePacket(User * pcUser, PacketBossTimeUpdate * psPacket);

	void OnSendDebugDamage(User * pcUser, PacketDebugDamageInfo * psPacket);
	void OnSendDebugDamageUnit(Unit * pcUnit, int iDamage, EDamageInfo eTypeAction);
protected:
	int GetEmptyIndexUnit(Map * pcMap);
	void UpdateTime();
	void UpdateUserBossTime(User * pcUser, int iMapID);
	void UpdateUsersBossTime();
	int GetGameTime();
	void SendFlagPoint(Map *pcMap);
	void ReadUnitSpawnData(Map * pcMap);
	void ReadUnitNpcStand(Map * pcMap);
	void ReadUnitEnemyStage(SpawnSetting * pMonsterStageList);
private:
	BOOL m_bNight = FALSE;
	int m_iTime = 0;
	int m_iBossTime = 0;
	int m_iDay = -1;

	std::vector<Map *> m_vpMap;

	UINT m_uCurrentStageUnitSpawn = 0;
	UINT m_uCurrentStageUnitStand = 0;
	UINT m_uCurrentStageUnitEnemy = 0;
};