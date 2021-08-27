#pragma once

namespace PARTY
{
	class Handle : public CBaseHandle
	{
	public:
		Handle();
		Handle(EHandle eID);
		virtual ~Handle();

		void HandlePacket(PacketUpdateParty * psPacket);
		void HandlePacket(PacketRequestParty * psPacket);
		void HandlePacket(PacketUpdatePartyData * psPacket);
		void HandlePacket(PacketRequestRaid * psPacket);

		void ProcessPacket(PacketJoinParty  * psPacket);
		void ProcessPacket(PacketJoinRaid * psPacket);
		void ProcessPacket(PacketRequestParty  * psPacket);
		void ProcessPacket(PacketRequestRaid  * psPacket);
		void ProcessPacket(PacketActionParty * psPacket);

		void Init();
		void Shutdown();

		void Render();

		void Update(float fTime);

		void OnMouseMove(class INPUTS::Mouse *pcMouse);
		BOOL OnMouseClick(class INPUTS::Mouse *pcMouse);

		void AcceptPartyRequest();
		void JoinPartyRequest();
		void JoinRaidRequest();

		BOOL IsPartyMember(int iID);
		BOOL IsRaidMember(int iID);

		CPartyData GetPartyData() { return m_sPartyData; }

		std::vector<Unit*> GetPartyMembers(BOOL bRaid = TRUE);
	protected:
		void UpdateSafeMembers(BOOL bSafe);
	private:
		CPartyData					m_sPartyData;

		PacketRequestParty			m_sPacketRequestParty;
		PacketRequestRaid			m_sPacketRequestRaid;
	};
}