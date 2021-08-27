#pragma once

class Unit;

class CServerItem
{
public:
	CServerItem();
	virtual ~CServerItem();

	void Init();
	void Shutdown();

	void OnLoadUser(User * pcUser);
	void OnUnLoadUser(User * pcUser);
	void UpdateItemTimer(User * pcUser);

	DefinitionItem * FindItemDefByCode(DWORD dwCode, int iUnique = 0);
	DefinitionItem * FindItemDefByCode(const char * pszCode, int iUnique = 0);
	DefinitionItem * FindItemDefByLevelBase(int iItemBase, int iLevel);

	void CreateItem(Item * psItem, DefinitionItem *psDefItem, int iSpeck = 0, BOOL IsPerfect = FALSE);
	void CreateItem(User * pcUser, DWORD iItem, int iCount = 1);
	void CreateItem(User * pcUser, DWORD iItem, int iClass, int iUnique);
	void CreatePerfectItem(Item * psOut, DefinitionItem * psIn, int iSpeck = 0);
	void UpgradeNewItem(Item * psItemOld, Item * psItemNew);
	BOOL CreateItemByName(LootItem *psItem, const char *pszCode, int iCount = 1);

	BOOL T2ItemCheck(User *pcUser, int iRank);

	void SendItemData(User *pcUser, Item *psItem, BOOL bNewItem = TRUE);
	//void ValidateItem(Item * psItem);
	BOOL ValidateItem(Item * psItem, BOOL iCheck = FALSE);
	void RegisterItemSecCode(User * pcUser, PacketItem * psPacket,BOOL bNew = TRUE);
	BOOL ValiSecCode(User * pcUser, int iItemID, int iChk1, int iChk2, int iGold, DWORD dwSecCode[4], int &iPotionCount);

	void AddPremiumUse(User * pcUser, ItemPremium * psItem);
	ItemPremium * GetPremiumUse(User * pcUser, EItemTimerType eType);
	ItemPremium * GetPremiumUse(User * pcUser, EItemID eID);

	void ProcessIntegrity(User * pcUser, EIntegrityUpdate eUpdate);

	void MakeInvenItem(User *pcUser, PacketCharacterRecordData *paPacket);
	BOOL CheckInvenItem(PacketCharacterRecordData *paPacket);
	void DecodeItemsData(BYTE *pItemData, BYTE *pItemDest, int iSize);

	BOOL GetDropPotion(User * pcUser, int iItemID);

	int AddPotion(User *pcUser, DWORD dwCode, int iPotionCount);
	void ComparePotion(User *pcUser, CharacterSave *pCharacterSave);
	void SavePotion(User *pcUser, CharacterSave *pCharacterSave);

	void SaveForce(User *pcUser, CharacterSave *pCharacterSave);
	void LoadForce(User *pcUser, CharacterSave *pCharacterSave);

	BOOL SaveItemData(Item * psItem);
	BOOL OnLoadItemData(ItemLoadData * psItem, const char * pszCode);

	void HandlePacket(User * pcUser, PacketNewItemTimer * psPacket);
	void HandlePacket(User * pcUser, PacketCancelItemTimer * psPacket);
	void HandlePacket(User * pcUser, PacketOldHeadUse * psPacket);
	void HandlePacket(User * pcUser, PacketSlotItemHandle * psPacket);
	void HandlePacket(User * pcUser, PacketGetItem * psPacket);
	void HandlePacket(User * pcUser, PacketUseItem * psPacket);
	void HandlePacket(User * pcUser, PacketPutItem * psPacket);

	BOOL AddItemInventory(User * pcUser, int iItemID, int iChk1, int iChk2);
	BOOL DeleteItemInventory(User *pcUser, DWORD dwCode, DWORD dwHead, DWORD dwChkSum);
	BOOL IsItemInventory(User * pcUser, EItemID iItemID);
	BOOL IsItemInventory(User * pcUser, DWORD dwCode, DWORD dwHead, DWORD dwChkSum);

	void SetLowerItem(DefinitionItem *lpDefItem);
	void OnSetItem(Item * pItem, BOOL IsPerfect = FALSE);

	BOOL FindItemName(UINT uCode, char * szBufName);
	BOOL FindItemName(char * pszCode, char * szBufName);

	ItemData * FindItemPointerTable(const char * szCode);
	ItemData * GetItemDataByID(UINT uID);

	int GetItemIDByItemCode(char * pszCode);

	void OnUseCrystal(User * pcUser, Unit * pcUnit, DWORD dwItemID, DWORD dwTime = 0);
	void OnUseCrystalDie(User * pcUser, Unit * pcUnit);

	CharacterClassData * GetItemSpecClassJob(int iClass, DefinitionItem * psDefItem);
protected:
	BOOL SQLAddItemTimer(User * pcUser, int iType, EItemID iItemID, DWORD dwTimeTotal);
	BOOL SQLGetItemTimer(User * pcUser, int iType, EItemID & iItemID, DWORD & dwTimeLeft, DWORD & dwTimeTotal);
	void SQLDeleteItemTimer(User * pcUser, int iItemID);
	void SQLUpdateItemTimer(User * pcUser, int iType, DWORD dwTimeLeft);
	void Load();
	DWORD RegistEnterKey(DWORD dwCode, int iv);
private:
	BOOL m_bFirstRead = FALSE;
	std::vector<DefinitionItem *> m_vItemTable;
	std::vector<ItemData *> m_vAllocItemTable;
};