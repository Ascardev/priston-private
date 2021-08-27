#pragma once

enum ELogItem
{
	ITEMLOGID_Get						= 0,
	ITEMLOGID_Put						= 6,
	ITEMLOGID_Mixing					= 9,
	ITEMLOGID_MixLost					= 3,
	ITEMLOGID_Aging						= 4,
	ITEMLOGID_AgingLost					= 10,
	ITEMLOGID_AgingUp					= 12,
	ITEMLOGID_BuyShop					= 5,
	ITEMLOGID_SellShop					= 7,
	ITEMLOGID_Trade						= 8,
	ITEMLOGID_Used						= 11,
	ITEMLOGID_Express					= 13,
	ITEMLOGID_GetWing					= 14,
	ITEMLOGID_WingLost					= 15,
	ITEMLOGID_BuyStar					= 16,

	ITEMLOGID_Aging2Up					= 17,
	ITEMLOGID_Aging2Down				= 18,
	ITEMLOGID_Aging1Down				= 19,
	ITEMLOGID_AgingKeep					= 20,

	ITEMLOGID_Present					= 21,
	ITEMLOGID_PersonalShop				= 22,

	ITEMLOGID_UseAlchmy					= 24,
	ITEMLOGID_LostAlchmy				= 25,
	ITEMLOGID_GetAlchmy					= 26,

	ITEMLOGID_GetRecon					= 27,
	ITEMLOGID_LostRecon					= 28,
	ITEMLOGID_SmeltingLost				= 29,
	ITEMLOGID_SmeltingGet				= 30,
	ITEMLOGID_ManufactureLost			= 31,
	ITEMLOGID_ManufactureGet			= 32,
	ITEMLOGID_ManufactureFail			= 33,
	ITEMLOGID_MixtureResetLost			= 34,
	ITEMLOGID_MixtureResetFail			= 35,
	ITEMLOGID_MixtureResetGet			= 36,
	ITEMLOGID_PremiumTimerOver			= 1001,
	ITEMLOGID_TradeItems				= 1002,
	ITEMLOGID_TradeItemsRemove			= 1003,
	ITEMLOGID_RewardEasterGet			= 1004,
	ITEMLOGID_RewardXmasRudolphGet		= 1005,
	ITEMLOGID_TradeItemSuccess			= 1006,
	ITEMLOGID_TradeItemSuccessReceive	= 1007,
	ITEMLOGID_GetPerfectize				= 1008,
	ITEMLOGID_PutPerfectize				= 1009,
	ITEMLOGID_GetSwap					= 1010,
	ITEMLOGID_PutSwap					= 1011,
	ITEMLOGID_PerfectizedItem			= 1050,
	ITEMLOGID_SwappedItem				= 1051,
	ITEMLOGID_RollDiceJoin				= 1060,
	ITEMLOGID_RollDiceWon				= 1061,
};

struct LogItem
{
	struct Header
	{
		DWORD dwCode;
		DWORD iChk1;
		DWORD iChk2;
	};
	int			iLength;
	char		szUserID[32];
	char		szCharacterName[24];
	int			iIP;
	ELogItem	eLogItem;
	int			iItemCount;
	Header		sItem[32];
};

class CServerLog
{
	enum ELogServerType
	{
		LOGTYPEID_Unknown,
		LOGTYPEID_Aging,
		LOGTYPEID_Mixtrue,
		LOGTYPEID_HackUser,
		LOGTYPEID_Item,
		LOGTYPEID_ClanMoney,
		LOGTYPEID_BlessCastle,
		LOGTYPEID_LogItem = 1,
		LOGTYPEID_LogItemTrade = 2,
		LOGTYPEID_LogItemExpress = 3,
	};
public:
	CServerLog();
	virtual ~CServerLog();

	const char * SetLogString(ELogItem eType);

	void LogCheat(User * pcUser, PacketLogCheat * psPacket);
	void LogSocketClose(SocketData * pcSocketData, char * pszLocation, void * p);
	void OnLogItem(int eType, int iSize, void * psLogItem);
	void OnLogItem(User * pcUser, int iID, int iChk1, int iChk2, ELogItem eLogItem);
	void AddFirewallBan(const char * pszIP);
	void OnLogItemEx(User * pcUser, int iLogID, const char * pszLog, ...);
protected:
	void OnLogItemData(LogItem * psLog);
};