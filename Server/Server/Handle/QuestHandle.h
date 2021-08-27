#pragma once

class CQuestHandler
{
public:
	CQuestHandler();
	virtual ~CQuestHandler();
	BOOL OnUnitKilled(User * pcUser, Unit * pcUnit, BOOL bDamageUsers);
};
