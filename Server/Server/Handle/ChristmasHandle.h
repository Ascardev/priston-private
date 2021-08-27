#pragma once

class CChristmasHandle
{
public:
	CChristmasHandle();
	virtual ~CChristmasHandle();

	void OnSpawnMonsterEvent(struct CharacterData * psCharacterData, Map * pcMap);
	void OnSayTime(Unit * pcUnit);
};