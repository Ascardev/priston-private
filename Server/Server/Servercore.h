#pragma once

#define  MAX_SERVERINFO		5

enum EServerType
{
	SERVERTYPE_Unknown	= 0,
	SERVERTYPE_Login	= 1,
	SERVERTYPE_Game		= 2,
	SERVERTYPE_Multi	= 3,
};

enum EUsersOnline
{
	USERSONLINE_Insert		= 0,
	USERSONLINE_Delete		= 1,
	USERSONLINE_DeleteAll	= 2
};

struct ServerInfo
{
	EServerType		iType;
	char			szName[32];
	in_addr			lIP;
	char			szIP[32];
	in_addr			lIP2;
	char			szIP2[32];
	in_addr			lIP3;
	char			szIP3[32];
	in_addr			lNetIP;
	char			szNetIP[32];
	int				iPort;
	int				iMaxUsers;
};
struct ServerEvent
{
	int iRate_Exp;
	int iEvent_Exp;

	int iEvent_BlessCastle;
	int iEvent_BlessCastle_Day;
	int iEvent_BlessCastle_Hour;

	int iEvent_Bellatra;
	int iEvent_Bellatra_DivScore;
	int iEvent_Bellatra_Tax;
	char szEvent_Bellatra_Text;

	int iEvent_WantedWolf;
	int iEvent_WantedWolf_ExpMap;

	int iEvent_WantedMoriph;
	int iEvent_WantedMoriph_ExpMap;

	int iEvent_Easter;
	int iEvent_Easter_Rate;
	int iEvent_Easter_Rate_ExpMap;

	int iEvent_Reduce_Damagemon;
	int iEvent_Reduce_Damagemon_Live;

	int iEvent_Halloween;

	int iEvent_XMas;
	int iEvent_XMas_Rate;
	int iEvent_XMas_ExpMap;

	int iEvent_TheGrandFury;

	int iEvent_Pvp;
	int iEvent_Pvp_Map;
};

struct ServerSQL
{
	char szHost[64];
	char szUser[64];
	char szPassword[64];
};

class CServerCore
{
public:
	static DWORD *				pdwTickCount;

	static inline DWORD			GetTickCounts()
	{
		return (*pdwTickCount);
	}
	static inline void			SetTickCounts(DWORD dw)
	{
		(*pdwTickCount) = dw;
	}
};
