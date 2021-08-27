#pragma once

class CServerQuest
{
public:
	CServerQuest();
	virtual ~CServerQuest();

	BOOL SQLMultpleQuest(int iQuestID);
};