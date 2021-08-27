#pragma once

#define MAP_ID					(GAMECHARACTER->GetStageID())

class CGameCharacter
{
public:
	CGameCharacter();
	virtual ~CGameCharacter();

	BOOL IsStageVillage();

	int GetStageID();

	void HandlePacket(PacketUpdateIntegrity * psPacket);
	void HandlePacket(PacketSimple *psPacket);
	void OnConnected(SocketData * sd, PacketSimple * psPacket);
};