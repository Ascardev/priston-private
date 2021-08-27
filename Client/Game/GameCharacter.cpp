#include "StdAfx.h"
#include "GameCharacter.h"

CGameCharacter::CGameCharacter()
{

}
CGameCharacter::~CGameCharacter()
{

}
BOOL CGameCharacter::IsStageVillage()
{
	int iLoadedMapIndex = UNIT->iLoadedMapIndex;

	if (iLoadedMapIndex >= 0)
	{
		if (STAGE_MAP[iLoadedMapIndex] && STAGE_MAP[iLoadedMapIndex]->iMapType == MAPTYPE_Town)
		{
			return TRUE;
		}
	}

	return FALSE;
}
int CGameCharacter::GetStageID()
{
	int iLoadedMapIndex = UNIT->iLoadedMapIndex;

	if (iLoadedMapIndex >= 0)
	{
		if (STAGE_MAP[iLoadedMapIndex])
		{
			return STAGE_MAP[iLoadedMapIndex]->iMapID;
		}
	}

	return MAPID_Invalid;
}
void CGameCharacter::HandlePacket(PacketUpdateIntegrity * psPacket)
{
	UINT uIntegrityDecrease = 0;

	switch (psPacket->eUpdate)
	{
	case INTEGRITYUPDATE_KilledMonster:
		uIntegrityDecrease = 10;
		break;
	case INTEGRITYUPDATE_KilledUser:
		uIntegrityDecrease = 5;
		break;
	}

	INVENTROYHANDLE->UpdateIntegrity(uIntegrityDecrease);
}
void CGameCharacter::HandlePacket(PacketSimple *psPacket)
{
	if (UNIT->psModelAnimation->iType != ANIMATIONTYPE_Die)
	{
		UNIT->SetMotionFromCode(ANIMATIONTYPE_Die);
		sinSetLife(0);
		UPDATE_CHARACTER_CHECKSUM;
		CharPlaySound(UNIT);
		DeadPlayerExp(UNIT);
		sinCheckQuest85Die();
		SaveGameData();
		ResetEnergyGraph(0);
	}
}
void CGameCharacter::OnConnected(SocketData * sd, PacketSimple * psPacket)
{
	SaveCheckSkill();

	UNIT->iID = UNIT->sCharacterData.dwObjectSerial;

	ReformSkillInfo();

	if (sd == SOCKETG)
	{
		GAMEMAP->SetGameTime(psPacket->iUnk);

		SendProcessInfo();
	}
}