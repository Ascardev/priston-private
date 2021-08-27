#pragma once

#define SENDPACKET CServerPacket::Send
#define SENDPACKETBLANK CServerPacket::SendPacketBlank
#define SENDPACKETSTAGE CServerPacket::SendPacketStage
#define SENDPACKETRANGE CServerPacket::SendPacketRange

struct PacketSyncData
{
	int							iSize;
	int							iHeader;

	struct CharacterData		CharInfo;

	ID	dwObjectID;

	int	x, y, z;
	int ax, ay, az;
	int state;
};

class CServerPacket
{
public:
	CServerPacket();
	virtual ~CServerPacket();

	BOOL AnalyzePacket(User * pcUser, PacketReceiving * p);

	static void	Send(User * pcUser, void * pPacket, BOOL bEncrypted = FALSE);
	static void	SendPacketBlank(User * pcUser, int iPacket, BOOL bEncrypted = FALSE);
	static void	SendPacketStage(void * pPacket, int iStageID, BOOL bEncrypt = FALSE);
	static void	SendPacketRange(void * pPacket, Point3D * psPos, int iDistance, BOOL bEncrypted = FALSE);
};