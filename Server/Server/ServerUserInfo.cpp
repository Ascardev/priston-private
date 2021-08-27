#include "StdAfx.h"
#include "ServerUserInfo.h"
#include "SrcServer/onserver.h"

CServerUserInfo::CServerUserInfo()
{

}
CServerUserInfo::~CServerUserInfo()
{

}
void CServerUserInfo::Init()
{
	CreateItemMemoryTable();
	CreateUnitEnemyData();

	m_bFirstRead = TRUE;
}
void CServerUserInfo::Shutdown()
{
	FreeUnit();
	FreeItem();
}
void CServerUserInfo::CreateItemMemoryTable()
{
	
}
void CServerUserInfo::CreateUnitEnemyData()
{
	
}
void CServerUserInfo::FreeItem()
{
	
}

void CServerUserInfo::FreeUnit()
{
	
}
void CServerUserInfo::ReadDropItem()
{
	
}
void CServerUserInfo::ReadUnitNpcData(CharacterData * pCharInfo, UnitInfo *pMonInfo, char *pDialogMessage)
{
	
}
EMonsterEffectID CServerUserInfo::GetEnemyEffect(char * pszEffect)
{
	for (auto f : saCharacterSoundEffect)
	{
		if (STRINGCOMPAREI(f.szCodeName, pszEffect))
			return f.iMonsterEffectID;
	}
	return MONSTEREFFECTID_None;
}

const char *CServerUserInfo::SetNpcMessage(const char *pDialogMessage)
{
	DWORD dwCode = GetCodebyName((char *)pDialogMessage);

	for (auto s : m_sMessage)
	{
		if (dwCode == s.first && STRINGCOMPAREI(pDialogMessage, s.second.c_str()))
			return pDialogMessage;
	}

	m_sMessage.insert(make_pair(dwCode, pDialogMessage));

	return pDialogMessage;
}
