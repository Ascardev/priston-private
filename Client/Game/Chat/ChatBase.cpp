#include "StdAfx.h"
#include "ChatBase.h"

namespace CHAT
{
	unsigned int Chat::ChatCommand(char * pszCommand, char * pszChat)
	{
		int iLen = STRLEN(pszCommand);

		for (int i = 0; i < iLen; i++)
		{
			if (pszChat[i] != pszCommand[i])
			{
				if ((pszChat[i] >= 0x41) && (pszChat[i] <= 0x5A))
				{
					if ((pszChat[i] + 0x20) == pszCommand[i])
						continue;
				}

				if ((pszCommand[i] >= 0x41) && (pszCommand[i] <= 0x5A))
				{
					if ((pszCommand[i] + 0x20) == pszChat[i])
						continue;
				}

				return 0;
			}
		}

		unsigned char cLastCharacter = pszChat[iLen];
		if ((cLastCharacter != 0x00) && (cLastCharacter != 0x09) && (cLastCharacter != 0x20))
			return 0;

		return iLen;
	}
}