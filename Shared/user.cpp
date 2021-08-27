#include "StdAfx.h"
#include "SrcServer/onserver.h"

BOOL User::CanSee(Unit *pcOtherUnit)
{
	//In Quest Arena?
	if (iMapID == MAPID_QuestArena)
	{
		//Monster is not for this User?
		if (pcOtherUnit->lExclusiveTargetID != iID)
		{
			//Not a GM?
			if (GetGameLevel() == GAMELEVEL_None)
			{
				//Not a Pet? Then probably someone else's Monster
				if (pcOtherUnit->sCharacterData.iMonsterType != MONSTERTYPE_Friendly)
					return FALSE;

				//Not your Pet? Then probably someone else's Pet
				if (pcOtherUnit->pcOwner != this)
					return FALSE;
			}
		}
	}

	//Not in one of the two Maps that the User can see?
	//EMapID eOtherMapID = pcOtherUnit->pcMap->lpField->FieldCode;

	EMapID eOtherMapID = pcOtherUnit->GetMap();

	if (iMapID != eOtherMapID)
		return FALSE;

	//Is NPC?
	if (pcOtherUnit->sCharacterData.iType == CHARACTERTYPE_NPC)
	{
		//Is Hidden NPC?
		if ((pcOtherUnit->sCharacterData.iLevel & 2))
		{
			//User not a GM? then NPC stays hidden
			if (GetGameLevel() == GAMELEVEL_None)
				return FALSE;
		}
	}

	return TRUE;
}