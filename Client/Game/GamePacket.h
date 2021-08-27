#pragma once

class CGamePacket
{
public:
	CGamePacket();
	virtual ~CGamePacket();

	BOOL AnalyzePacket(SocketData * pcSocketData, Packet * psPacket);
};
