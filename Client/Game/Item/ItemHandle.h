#pragma once

class CItemHandle
{
public:
	CItemHandle();
	virtual ~CItemHandle();

	void Init();
	void Shutdown();

	BOOL IsBeginnerSet(ItemData * pcItemData);
	DWORD GetItemPlayTime(EItemID eID);
	BOOL IsExpiredItemTime(Item * psItemInfo);
	BOOL GetItemPrice(class ItemData * pcItemData, PriceItem * psSellData);
	int GetItemNumberFromID(UINT uID);
	ItemData * GetItemDataByID(UINT uID);
	ItemData * GetItemDataByName(char *pszName);
	ItemData * GetItemDataByNumber(int iNumber);
	BOOL IsItemDataByID(int iFindNumber, UINT uID);

	std::vector<ItemData *> GetItemTable() { return m_vpItemTable; }
private:
	std::vector<ItemData *> m_vpItemTable;
};