#pragma once

class CPriestess
{
public:
	CPriestess();
	virtual ~CPriestess();

	void RestoreHPPacketParty(User * pcUser, PacketRestoreHP * psPacket);
};