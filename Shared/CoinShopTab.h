#pragma once

#include "CoinShopItem.h"
/* Max Items = MAXCOINSHOPITEMS, but can be send MAXCOINSHOPITEMS*2 ( divide in 2 packets send ) */

class CCoinShopTab : Base::Coin
{
protected:
	int													iID;
	int													iParentTabID;
	char												szName[32];
	int													iDiscount;
	int													iBulk;
	int													iMaxBulk;


	std::vector<CCoinShopItem*>							vItems;
	std::vector<CCoinShopTab*>							vTabs;

public:
	CCoinShopTab(int iID, char szName[32], int iParentID, int iBulk, int iMaxBulk) { this->iID = iID; this->iParentTabID = iParentID; this->iBulk = iBulk; this->iMaxBulk = iMaxBulk; STRINGCOPY(this->szName, szName); }

	std::vector<CCoinShopItem*>							GetItems() { return vItems; };
	std::vector<CCoinShopTab*>							GetChildTabs() { return vTabs; };

	CCoinShopItem										* GetItemByID(int i);


	int													GetID() { return iID; }
	int													GetParentTabID() { return iParentTabID; }
	char												* GetName() { return szName; }
	int													GetDiscount() { return iDiscount; }
	int													GetBulk() { return iBulk; };
	int													GetMaxBulk() { return iMaxBulk; };


	void												AddChildTab(CCoinShopTab * pcTab);

	void												SetDiscount(int iValue) { iDiscount = iValue; }
	void												SetBulk(int i) { iBulk = i; };
	void												SetMaxBulk(int i) { iMaxBulk = i; };

	void												AddItem(CCoinShopItem * pcItem);
	void												DeleteItem(int iID) {}; // TODO

	void												ClearItems();
	void												ClearTabs();
	void												Clear();
};