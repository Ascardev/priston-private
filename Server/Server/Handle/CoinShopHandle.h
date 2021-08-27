#pragma once

static char * pszaNotAllowedNamesChangeNick[]
{
	"[gm]",
	"[adm]",
	"sandurr",
	"realmpt",
	"gm-",
	"adm-",
	"gamemaster"
};

class CCoinShopHandle
{
public:
	CCoinShopHandle();
	virtual ~CCoinShopHandle();

	void Init();

	void SQLCoinLog(char * pszAccountName, char * pszDescription);
	void LoadCoinShop(int iCoinShopID = -1);

	int GetCoinAmount(char * pszAccountName);
	int GetCoinTradeAmount(char * pszAccountName);

	int GetBulkValue(CCoinShopItem * pcItem, int iQuantity);

	int UseCoin(char * pszAccountName, int iCoinAmount);

	void AddTradeCoin(char * pszAccountName, int iCoinAmount);

	int AddCoin(char * pszAccountName, int iCoinAmount);
	int HasCoinAmount(char * pszAccountName, int iCoinAmount);

	BOOL PerfectizeItem(User * pcUser,PacketCoinServiceBuy * psPacket);
	BOOL ItemSwapper(User * pcUser, PacketCoinServiceBuy * psPacket);
	BOOL ChangeNick(User * pcUser, PacketCoinServiceBuy * psPacket);
	BOOL AgingRecovery(User * pcUser, PacketCoinServiceBuy * psPacket);
	BOOL ChangeClass(User * pcUser, PacketCoinServiceBuy * psPacket);

	void ProcessPacket(User * pcUser, PacketCoinServiceBuy * psPacket);
	void ProcessPacket(User * pcUser, PacketCoinShopNPC * psPacket);
	void ProcessPacket(User * pcUser, PacketCoinAmount * psPacket);
	void ProcessPacket(User * pcUser, PacketCoinOpenTab * psPacket);
	void ProcessPacket(User * pcUser, PacketCoinTab * psPacket);
	void ProcessPacket(User * pcUser, PacketCoinItemData * psPacket);

	void HandlePacket(User * pcUser, PacketCoinShopNPC * psPacket);
	void HandlePacket(User * pcUser, PacketCoinOpenTab * psPacket);
	void HandlePacket(User * pcUser, PacketCoinAmount * psPacket);
	void HandlePacket(User * pcUser, PacketCoinOpenItemData * psPacket);
	void HandlePacket(User * pcUser, PacketCoinBuy * psPacket);
	void HandlePacket(User * pcUser, PacketCoinServiceBuy * psPacket);
	void HandlePacket(User * pcUser, PacketTradeCoinSet * psPacket);
private:
	CCoinShop * m_pcCoinShop = NULL;
	int m_iChangeNickPrice = 0;
	int m_iAgingRecoveryPrice = 0;
};