#pragma once

class RollDiceRankingUser
{
public:
	char			szCharacterName[32];
	UINT			uNumber;

	RollDiceRankingUser(char * pszCharacterName, UINT _uNumber) { STRINGCOPY(szCharacterName, pszCharacterName); uNumber = _uNumber; }
};
struct PacketRollDiceRanking : Packet
{
	char			szCharacterName[32];
	UINT			uNumber;
};