#include "StdAfx.h"
#include "ServerQuest.h"

CServerQuest::CServerQuest()
{

}
CServerQuest::~CServerQuest()
{

}
BOOL CServerQuest::SQLMultpleQuest(int iQuestID)
{
	BOOL bRet = FALSE;

	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_GameDB_2);

	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT Multiple FROM QuestList WHERE ID=?"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_Integer, &iQuestID);

			if (pcDB->Execute() && pcDB->Fetch())
			{
				pcDB->GetData(1, PARAMTYPE_Integer, &bRet);
			}
		}

		pcDB->Close();
	}


	return bRet;
}