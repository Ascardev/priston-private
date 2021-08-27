#pragma once

class Unit;

#define UNIT									lpCurPlayer
#define UPDATE_CHARACTER_CHECKSUM				GAMEUNIT->ChecksumUpdate(UNIT)

class CGameUnit
{
public:
	CGameUnit();
	virtual ~CGameUnit();

	void ClearFarUnits();

	Unit *pcaUnit = nullptr;

	void AddExp(INT64 iExp);
	INT64 GetExp(Unit *pcUnit);

	void ChecksumUpdate(Unit *pcUnit);
	void ChecksumCheck(Unit *pcUnit);

	BOOL OnLoseEXP();
	void Fun();
	void SendUnitDataEx();

	Unit *GetUnitByID(ID lID);
protected:
	int GetLevelFromExp(INT64 iExp);
	INT64 GetExpFromLevel(int iLevel);
	void SetExp(Unit *pcUnit, INT64 iExp);
};
