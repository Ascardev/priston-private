#pragma once

#define MAX_TIME_KILLSAFE		80

class CServerPvP
{
private:
	struct PvPClassData
	{
		char szCharacterName[10][32];
	};
public:
	CServerPvP();
	virtual ~CServerPvP();

	void OnKilled(User * pcKiller, User * pcVictim);
	void ProcessPvPKill(User * pcKiller, User * pcVictim, int iType);
	void ProcessPvPData(User * pcUser, int iID, BOOL bKill);
	
	void OnLoadUser(User * pcUser);
	void OnUnLoadUser(User * pcUser);

	void Update();

	void ResetTick() { m_dwTick = 0; m_sLastDay = 0; }
protected:
	BOOL SQLSelectCharacterPvP(User * pcUser);
	BOOL SQLGetTopPvP(PvPClassData & s);
	void SQLSetTopPvP(PvPClassData & s);

	void ResetPvPBuffer();
private:
	DWORD m_dwTick = 0;
	WORD m_sLastDay = 0;
};