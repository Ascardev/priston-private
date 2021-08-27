#include "StdAfx.h"
#include "ChristmasHandle.h"
#include "SrcServer/onserver.h"

CChristmasHandle::CChristmasHandle()
{

}
CChristmasHandle::~CChristmasHandle()
{

}
void CChristmasHandle::OnSpawnMonsterEvent(struct CharacterData * psCharacterData, Map * pcMap)
{
	if (GAME_SERVER && EVENT_XMAS)
	{
		int iRate = RATE_XMAS;
		if (SERVERMAP->IsEXPMap(pcMap->pcBaseMap->GetID()))
			iRate = RATE_XMAS_EXPMAP;


		int iRand = (rand() | TICKCOUNT) % 1000;
		if (iRand < iRate)
		{
			CharacterData * psChar = SERVERUNIT->GetCharacterDataByName("Santa Skeleton");
			if (psChar)
			{
				CopyMemory(psCharacterData, psChar, sizeof(CharacterData));
			}
		}
		iRand = ((rand() + iRand) | TICKCOUNT) % 1000;
		if (iRand < iRate)
		{
			CharacterData * psChar = SERVERUNIT->GetCharacterDataByName("Santa Goblin");
			if (psChar)
			{
				CopyMemory(psCharacterData, psChar, sizeof(CharacterData));
			}
		}
	}
}
void CChristmasHandle::OnSayTime(Unit * pcUnit)
{
	if (pcUnit->dwMessageEndTime < TICKCOUNT)
	{
		if (STRINGCOMPAREI(pcUnit->sCharacterData.szName, "Santa Skeleton"))
		{
			if (pcUnit->GetAnimation() == ANIMATIONTYPE_Die)
			{
				char * pszaSkeletonXMASPhrase[6]
				{
					"I Kidnaped Santa Claus and smashed him with a stick, hahaha",
					"You will be killed this XMas! muahahahaha",
						"See you in the next life (:",
						"I know that I'm a computed data turned into a monster!",
						"GM-Prog's PC can't handle me! buggy pc",
						"Merry XMas in hell ((:",
				};
				int iRand = rand() % 6;
				pcUnit->dwMessageEndTime = TICKCOUNT + 60000;
				SERVERCHAT->SendUserBoxChatRange(pcUnit->sPosition.iX, pcUnit->sPosition.iZ, 0x4B000, pcUnit->iID, "%s: %s", pcUnit->sCharacterData.szName, pszaSkeletonXMASPhrase[iRand]);
			}
		}
		else if (pcUnit->sCharacterData.iMonsterEffectID == MONSTEREFFECTID_HOBGOBLIN && pcUnit->sCharacterData.iLevel == 60)
		{
			if (pcUnit->GetAnimation() == ANIMATIONTYPE_Die)
			{
				char * pszaSantaGoblinPhrase[6]
				{
						"",
						"I'm your father! Merry XMas (;",
						"Turn back on musics of XMas, have something for you! HEHEHE",
						"Do you like Christmas? I like to kill you!",
						"Are you a good boy? hehehehe 666",
						"Your parents are liers, Santa Claus doesn't exist!",
				};
				int iRand = rand() % 6;
				pcUnit->dwMessageEndTime = TICKCOUNT + 60000;

				if (iRand == 0)
				{
					if (pcUnit->pcKillerData)
						SERVERCHAT->SendUserBoxChatRange(pcUnit->sPosition.iX, pcUnit->sPosition.iZ, 0x4B000, pcUnit->iID, "%s: %s, I will catch you this night! MUAHAHA", pcUnit->sCharacterData.szName, SERVERCHARACTER->GetCharacterName(pcUnit->pcKillerData));
				}
				else
					SERVERCHAT->SendUserBoxChatRange(pcUnit->sPosition.iX, pcUnit->sPosition.iZ, 0x4B000, pcUnit->iID, "%s: %s", pcUnit->sCharacterData.szName, pszaSantaGoblinPhrase[iRand]);
			}
		}
	}
}