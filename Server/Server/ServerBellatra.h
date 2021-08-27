#pragma once

class CServerBellatra
{
public:
	CServerBellatra();
	virtual ~CServerBellatra();

	void Init();
	void Shutdown();

	void UnitKilled(Unit * pcUnit);
	BOOL AddRoomScore(int iRoomID, int iScore);
	void UpdateBellatraUserScore(User *pcUser);
private:
	int m_iaRoomScore[4];
};
