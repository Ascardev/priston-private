#pragma once

class CDistributorHandle
{
public:
	CDistributorHandle();
	virtual ~CDistributorHandle();

	void OpenDistributorItem(User * pcUser);
	void AcceptDistributorItem(User * pcUser);
	void DeleteDistributorItem(User * pcUser);
	void HandlePacket(User * pcUser, PacketItemBoxSend * psPacket);

	int SQLItemBoxCount(User * pcUser);

	BOOL AddItemOpenBox(User * pcUser, char * pszItemName, int iSpec = 0, int iQuantity = 1);
	BOOL AddItemOpenBox(char * pszAccountName, char * pszItemName, int iSpec = 0, int iQuantity = 1);

	BOOL AddItemOpenBoxEx(char * pszAccountName, char * pszCharName1, char * pszCharName2, Item * psItem);
protected:
	BOOL SQLLoadItemBox(User * pcUser);
	BOOL SQLLoadItemBoxEx(User * pcUser);
	void SQLUpdateItemBox(int iID);
	void SQLUpdateItemBoxEx(int iID);
};