#include "StdAfx.h"
#include "Priestess.h"

CPriestess::CPriestess()
{

}
CPriestess::~CPriestess()
{

}
void CPriestess::RestoreHPPacketParty(User * pcUser, PacketRestoreHP * psPacket)
{
	PacketRestoreHP sPacket;
	CopyMemory(&sPacket, psPacket, sizeof(PacketRestoreHP));

	if (pcUser)
	{
		if (pcUser->bParty && pcUser->psParty)
		{
			std::vector<User*> vUsers = PARTYHANDLE->GetPartyMembers(pcUser->psParty);
			for (auto &p : vUsers)
			{
				if (p && p != pcUser)
				{
					if (pcUser->dwSkill_VirtualLife_Time && pcUser->dwSkill_VirtualLife_Time > TICKCOUNT)
					{
						sPacket.hpboost = psPacket->hpboost;
						sPacket.hpboost -= (psPacket->hpboost * pcUser->dwSkill_VirtualLife_Param) / 100;
						SENDPACKET(p, &sPacket);
					}
					else
						SENDPACKET(p, psPacket);
				}
			}

			if (pcUser->dwSkill_VirtualLife_Time && pcUser->dwSkill_VirtualLife_Time > TICKCOUNT)
			{
				sPacket.hpboost = psPacket->hpboost;
				sPacket.hpboost -= (psPacket->hpboost * pcUser->dwSkill_VirtualLife_Param) / 100;
				SENDPACKET(pcUser, &sPacket);
			}
			else
				SENDPACKET(pcUser, psPacket);
		}
	}
}