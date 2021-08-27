#pragma once

class CServerUserInfo
{
public:
	CServerUserInfo();
	virtual ~CServerUserInfo();

	void Init();
	void Shutdown();

	void CreateItemMemoryTable();
	void CreateUnitEnemyData();

	void FreeItem();
	void FreeUnit();
	
	void ReadDropItem();
	EMonsterEffectID GetEnemyEffect(char * pszEffect);

	void ReadUnitNpcData(CharacterData * pCharInfo, UnitInfo *pMonInfo, char *pDialogMessage);

	std::vector<ItemData *> GetAllowcItemTable() { return m_vAllocItemTable; }
	std::vector<DefinitionItem *> GetItemTable() { return m_vItemTable; }

	std::vector<CharacterData *> GetMonsterTable() { return m_vMonsterTable; }

protected:
	const char *SetNpcMessage(const char *pDialogMessage);
private:
	std::vector<CharacterData *> m_vMonsterTable;

	std::vector<DefinitionItem *> m_vItemTable;
	std::vector<ItemData *> m_vAllocItemTable;

	std::map<int, std::string> m_sMessage;

	BOOL m_bFirstRead = FALSE;
};