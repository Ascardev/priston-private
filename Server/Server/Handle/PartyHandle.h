#pragma once

class CPartyHandle
{
public:
	CPartyHandle();
	virtual ~CPartyHandle();

	void ProcessPacket(User * pcUser, PacketRequestParty * psPacket);
	void ProcessPacket(User * pcUser, PacketUpdateParty * psPacket);
	void ProcessPacket(User * pcUser, PacketUpdatePartyData * psPacket);
	void ProcessPacket(User * pcUser, PacketRequestRaid * psPacket);
	void HandlePacket(User * pcUser, PacketRequestParty * psPacket);
	void HandlePacket(User * pcUser, PacketJoinParty * psPacket);
	void HandlePacket(User * pcUser, PacketActionParty * psPacket);
	void HandlePacket(User * pcUser, PacketRequestRaid * psPacket);
	void HandlePacket(User * pcUser, PacketJoinRaid * psPacket);
	void SendChatParty(User * pcUser, std::string strMessage, EChatColor eChatColor, BOOL bSendRaid = FALSE);
	void SendChatRaid(User * pcUser, std::string strMessage, EChatColor eChatColor);
	void LeaveParty(User * pcUser, BOOL bKick = FALSE);
	void UpdatePartyData(User * pcUser, PartyInfo * psParty);
	std::vector<User *> GetPartyMembers(PartyInfo * psParty, BOOL bRaid = TRUE);
private:
	BOOL DoParty(User * pcUser, User * pcOtherUser);
	BOOL JoinParty(User * pcUser, PartyInfo * psParty);
	BOOL DeleteParty(PartyInfo * psParty);

	void DelegateParty(User * pcUser);
	void ChangePartyMode(PartyInfo * psParty);

	BOOL DoRaid(User * pcUser, User * pcOtherUser);
	BOOL JoinRaid(User * pcUser, PartyInfo * psParty);

	void ArrangePartyMembers(PartyInfo * psParty);
	void ArrangeRaidParty(PartyInfo * psParty);

	void UpdateParty(PartyInfo * psParty, BOOL bUpdateToRaid = FALSE);
};
