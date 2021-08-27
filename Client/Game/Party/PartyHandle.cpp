#include "StdAfx.h"
#include "PartyHandle.h"

namespace PARTY
{
	Handle::Handle() : CBaseHandle()
	{

	}
	Handle::Handle(EHandle eID) : CBaseHandle(eID)
	{

	}
	Handle::~Handle()
	{

	}
	void Handle::HandlePacket(PacketUpdateParty * psPacket)
	{
		if (psPacket)
		{
			UpdateSafeMembers(FALSE);

			//Setting Party Data
			ZeroMemory(&m_sPartyData, sizeof(CPartyData));
			m_sPartyData.iMembersCount = (int)psPacket->cMembersCount;
			m_sPartyData.eMode = (EPartyMode)psPacket->cPartyMode;

			//Deleted Party
			if (m_sPartyData.iMembersCount < 1)
			{
				if (PARTYBOX)
					PARTYBOX->LeaveParty();
				return;
			}

			//Add Party Members to Party Data
			for (char i = 0; i < psPacket->cMembersCount; i++)
				CopyMemory(&m_sPartyData.saMembers[i], &psPacket->saMembers[i], sizeof(PartyMember));

			//Party it's in a Raid
			if (psPacket->cRaidCount > 0)
			{
				m_sPartyData.iRaidCount = (int)psPacket->cRaidCount;

				for (size_t i = 0; i < MAX_RAID - 1; i++)
				{
					m_sPartyData.saRaid[i].cRaidID = psPacket->saRaid[i].cRaidID;

					for (size_t j = 0; j < MAX_PARTY_MEMBERS; j++)
					{
						if (psPacket->saRaid[i].saMembers[j].sData.iID)
							CopyMemory(&m_sPartyData.saRaid[i].saMembers[j], &psPacket->saRaid[i].saMembers[j], sizeof(PartyRaidMember));
					}
				}
			}

			//Update Party Window
			if (m_sPartyData.iMembersCount > 1)
			{
				if (PARTYBOX)
					PARTYBOX->UpdateParty(&m_sPartyData);
			}

			UpdateSafeMembers(TRUE);
		}
	}

	void Handle::HandlePacket(PacketRequestParty * psPacket)
	{
		if (psPacket)
		{
			if (psPacket->eState == PARTYSTATE_Success || psPacket->eState == PARTYSTATE_RequestInvite)
			{
				if (PARTYBOX)
					PARTYBOX->ShowPartyNotification(psPacket->szCharacterName, psPacket->eState == PARTYSTATE_Success ? 1 : 2);
			}

			CopyMemory(&m_sPacketRequestParty, psPacket, sizeof(PacketRequestParty));
		}
	}

	void Handle::HandlePacket(PacketUpdatePartyData * psPacket)
	{
		if (psPacket)
		{
			UpdateSafeMembers(FALSE);

			//Find a Party member on PartyData of Client side to update the data
			if (psPacket->cMembersCount > 0)
				for (char i = 0; i < psPacket->cMembersCount; i++)
					for (size_t j = 0; j < MAX_PARTY_MEMBERS; j++)
						if (m_sPartyData.saMembers[j].sData.iID == psPacket->saMembers[i].iID)
							CopyMemory(&m_sPartyData.saMembers[j].sData, &psPacket->saMembers[i], sizeof(PartyMemberData));

			//Find a Raid Party Member on PartyData of Client side to update the data
			for (size_t i = 0; i < MAX_RAID - 1; i++)
				for (size_t j = 0; j < MAX_PARTY_MEMBERS; j++)
					if (psPacket->saRaidMember[i][j].iID != 0)
						for (size_t k = 0; k < MAX_RAID - 1; k++)
							for (size_t l = 0; l < MAX_PARTY_MEMBERS; l++)
								if (m_sPartyData.saRaid[k].saMembers[l].sData.iID == psPacket->saRaidMember[i][j].iID)
									CopyMemory(&m_sPartyData.saRaid[k].saMembers[l].sData, &psPacket->saRaidMember[i][j], sizeof(PartyRaidMemberData));

			UpdateSafeMembers(TRUE);
		}
	}
	void Handle::HandlePacket(PacketRequestRaid * psPacket)
	{
		if (psPacket)
		{
			if (psPacket->eState == PARTYSTATE_Success)
			{
				if (PARTYBOX)
					PARTYBOX->ShowRaidNotification(psPacket->szCharacterName);
			}

			CopyMemory(&m_sPacketRequestRaid, psPacket, sizeof(PacketRequestRaid));
		}
	}
	void Handle::ProcessPacket(PacketJoinParty * psPacket)
	{
		psPacket->iLength = sizeof(PacketJoinParty);
		psPacket->iHeader = PKTHDR_JoinParty;
		SENDPACKETG(psPacket);

		ZeroMemory(&m_sPacketRequestParty, sizeof(PacketRequestParty));
	}
	void Handle::ProcessPacket(PacketJoinRaid * psPacket)
	{
		psPacket->iLength = sizeof(PacketJoinRaid);
		psPacket->iHeader = PKTHDR_JoinRaid;
		SENDPACKETG(psPacket);

		ZeroMemory(&m_sPacketRequestRaid, sizeof(PacketRequestParty));
	}
	void Handle::ProcessPacket(PacketRequestParty * psPacket)
	{
		psPacket->iLength = sizeof(PacketRequestParty);
		psPacket->iHeader = PKTHDR_RequestParty;
		SENDPACKETG(psPacket);

		ZeroMemory(&m_sPacketRequestParty, sizeof(PacketRequestParty));
	}
	void Handle::ProcessPacket(PacketRequestRaid * psPacket)
	{
		psPacket->iLength = sizeof(PacketRequestRaid);
		psPacket->iHeader = PKTHDR_RequestRaid;
		SENDPACKETG(psPacket);

		ZeroMemory(&m_sPacketRequestRaid, sizeof(PacketRequestRaid));
	}
	void Handle::ProcessPacket(PacketActionParty * psPacket)
	{
		psPacket->iLength = sizeof(PacketActionParty);
		psPacket->iHeader = PKTHDR_ActionParty;
		SENDPACKETG(psPacket);
	}
	void Handle::Init()
	{
		ZeroMemory(&m_sPartyData, sizeof(CPartyData));
	}
	void Handle::Shutdown()
	{
		
	}
	void Handle::Render()
	{
		if (PARTYBOX)
			PARTYBOX->Render();
	}
	void Handle::Update(float fTime)
	{
		UNIT->bPartyLeader = FALSE;

		for (int i = 0; i < m_sPartyData.iMembersCount; i++)
		{
			Unit * p = GAMEUNIT->GetUnitByID(m_sPartyData.saMembers[i].sData.iID);

			if (p && p->bActive)
			{
				m_sPartyData.saMembers[i].sData.sHP = p->sCharacterData.sHP;
				m_sPartyData.saMembers[i].sData.sLevel = p->sCharacterData.iLevel;
				m_sPartyData.saMembers[i].sData.sMP = p->sCharacterData.sMP;
				m_sPartyData.saMembers[i].sData.sPosition = p->sPosition;

				//Leader?
				if (p->iID == UNIT->iID && i == 0)
					UNIT->bPartyLeader = TRUE;
			}
		}

		for (int i = 0; i < m_sPartyData.iRaidCount; i++)
		{
			for (size_t j = 0; j < MAX_PARTY_MEMBERS; j++)
			{
				Unit * p = GAMEUNIT->GetUnitByID(m_sPartyData.saRaid[i].saMembers[j].sData.iID);

				if (p && p->bActive)
				{
					m_sPartyData.saRaid[i].saMembers[j].sData.sHP = p->sCharacterData.sHP;
					m_sPartyData.saRaid[i].saMembers[j].sData.sPosition = p->sPosition;
					continue;
				}
			}
		}

		UpdateSafeMembers(TRUE);

		if (PARTYBOX)
			PARTYBOX->Update(fTime);
	}
	void Handle::OnMouseMove(class INPUTS::Mouse * pcMouse)
	{
		if (PARTYBOX)
			PARTYBOX->OnMouseMove(pcMouse);
	}
	BOOL Handle::OnMouseClick(class INPUTS::Mouse * pcMouse)
	{
		BOOL bRet = FALSE;

		if (PARTYBOX)
			bRet = PARTYBOX->OnMouseClick(pcMouse);

		return bRet;
	}
	void Handle::AcceptPartyRequest()
	{
		m_sPacketRequestParty.eState = PARTYSTATE_Success;
		ProcessPacket(&m_sPacketRequestParty);
	}
	void Handle::JoinPartyRequest()
	{
		PacketJoinParty p;
		p.iID = m_sPacketRequestParty.iID;
		ProcessPacket(&p);
	}
	void Handle::JoinRaidRequest()
	{
		PacketJoinRaid p;
		p.iID = m_sPacketRequestRaid.iID;
		ProcessPacket(&p);
	}
	BOOL Handle::IsPartyMember(int iID)
	{
		for (int i = 0; i < m_sPartyData.iMembersCount; i++)
			if (m_sPartyData.saMembers[i].sData.iID == iID)
				return TRUE;

		return FALSE;
	}
	BOOL Handle::IsRaidMember(int iID)
	{
		for (int i = 0; i < m_sPartyData.iRaidCount; i++)
			for (size_t j = 0; j < MAX_PARTY_MEMBERS; j++)
				if (m_sPartyData.saRaid[i].saMembers[j].sData.iID == iID)
					return TRUE;

		return FALSE;
	}
	std::vector<Unit*> Handle::GetPartyMembers(BOOL bRaid)
	{
		std::vector<Unit*> v;

		if (m_sPartyData.iMembersCount > 0)
		{
			for (int i = 0; i < MAX_PARTY_MEMBERS; i++)
				if (m_sPartyData.saMembers[i].sData.iID)
					v.push_back(GAMEUNIT->GetUnitByID(m_sPartyData.saMembers[i].sData.iID));

			if (bRaid)
			{
				for (int i = 0; i < MAX_RAID - 1; i++)
					for (size_t j = 0; j < MAX_PARTY_MEMBERS; j++)
						if (m_sPartyData.saRaid[i].saMembers[j].sData.iID != 0 && m_sPartyData.saRaid[i].saMembers[j].szCharacterName[0] != 0)
							v.push_back(GAMEUNIT->GetUnitByID(m_sPartyData.saRaid[i].saMembers[j].sData.iID));
			}
		}

		return v;
	}
	void Handle::UpdateSafeMembers(BOOL bSafe)
	{
		std::vector<Unit *> vMembers = GetPartyMembers();

		for (auto & v : vMembers)
		{
			if (v && v != UNIT)
			{
				if (bSafe)
				{
					if (IsPartyMember(v->iID))
						v->dwExclusiveNum = 1;
					else if (IsRaidMember(v->iID))
						v->dwExclusiveNum = 2;
				}
				else
					v->dwExclusiveNum = 0;
			}
		}
	}
}