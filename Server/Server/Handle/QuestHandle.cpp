#include "StdAfx.h"
#include "QuestHandle.h"

CQuestHandler::CQuestHandler()
{

}
CQuestHandler::~CQuestHandler()
{

}
BOOL CQuestHandler::OnUnitKilled(User * pcUser, Unit * pcUnit, BOOL bDamageUsers)
{
	return FALSE;
}