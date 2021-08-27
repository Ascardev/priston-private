#pragma once

#include "CoinShopTab.h"

class CCoinShop
{
protected:
	int													iID;
	char												szName[32];
	char												szMessage[128];
	int													iDiscount;

	std::vector<CCoinShopTab*>							vTabs;

public:
	CCoinShop(int iID) { this->iID = iID; }
	~CCoinShop();
	std::vector<CCoinShopTab*>							GetTabs() { return vTabs; }
	std::vector<CCoinShopTab*>							GetAllTabs();
	CCoinShopTab										* GetTabByID(int iID);

	int													GetID() { return iID; };
	char												* GetName() { return szName; }
	char												* GetMessage() { return szMessage; }
	int													GetDiscount() { return iDiscount; }

	void												SetName(char * pszName) { STRINGCOPY(szName,  pszName); }
	void												SetMessage(char * pszMessage) { STRINGCOPY(szMessage,  pszMessage); }
	void												SetDiscount(int iDiscount) { this->iDiscount = iDiscount; }

	void												AddTab(CCoinShopTab * pcTab) { vTabs.push_back(pcTab); }
};