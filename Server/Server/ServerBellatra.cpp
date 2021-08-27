#include "StdAfx.h"
#include "ServerBellatra.h"
#include "SrcServer/onserver.h"

CServerBellatra::CServerBellatra()
{

}
CServerBellatra::~CServerBellatra()
{

}
void CServerBellatra::Init()
{
	rsInitHardCoreEvent();
}
void CServerBellatra::Shutdown()
{

}
void CServerBellatra::UnitKilled(Unit * pcUnit)
{
	m_iaRoomScore[pcUnit->iBellatraRoom]--;

	//3%
	if (RandomI(0, 1000) < 10)
	{
		LootItem sLootItem;

		//Get Item Data
		DefinitionItem * ps = SERVERITEM->FindItemDefByCode(ITEMID_BrilliantStone);

		if (ps)
		{
			//Create Item with non-spec
			SERVERITEM->CreateItem(&sLootItem.sItem, ps, 0);

			//Get Map Data from Unit
			Map * psMap = pcUnit->pcMap;

			if (psMap)
			{
				//Add Item to Map
				MapLoot * psItemD = SERVERMAP->AddItem(psMap, &sLootItem, pcUnit->sPosition >> 8, TRUE);

				//Added? Send It to near users...
				if (psItemD)
					SERVERMAP->SendItemStageNearUsers(psMap, psItemD);
			}
		}
	}
}
BOOL CServerBellatra::AddRoomScore(int iRoomID, int iScore)
{
	if (iRoomID >= 0 && iRoomID < 8)
	{
		m_iaRoomScore[iRoomID] += iScore;
		return TRUE;
	}

	return FALSE;
}
void CServerBellatra::UpdateBellatraUserScore(User *pcUser)
{

}