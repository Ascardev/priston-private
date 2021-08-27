#include "StdAfx.h"
#include "cipher.h"

BOOL DecryptBMP(char *pBuffer,UINT uBufferSize)
{
	if (uBufferSize < 14)
		return FALSE;

	if ((pBuffer[0] != 'B') || (pBuffer[1] != 'M'))
	{
		pBuffer[0] = 'B';
		pBuffer[1] = 'M';

		for (unsigned char c = 2; c < 14; c ++)
			pBuffer[c] -= (c * c);
	}

	pBuffer[2] = 0;
	pBuffer[3] = 0;
	pBuffer[4] = 0;
	pBuffer[5] = 0;

	return TRUE;
}
BOOL DecryptTGA(char *pBuffer,UINT uBufferSize)
{
	if (uBufferSize < 18)
		return FALSE;

	if ((pBuffer[0] == 'G') && (pBuffer[1] == '8'))
	{
		pBuffer[0] = 0;
		pBuffer[1] = 0;

		for (unsigned char c = 2; c < 18; c ++)
			pBuffer[c] -= (c * c);
	}

	return TRUE;
}
UINT CalSpeedSum(const char *pszText)
{
	unsigned int uSum1,uSum2;

	uSum1 = uSum2 = 0;

	int ilen = STRLEN(pszText);

	for (int i = 0; i < ilen; i ++)
	{
		char c = (char)pszText[i];

		if (c >= 'a' && c <= 'z')
		{
			uSum1 += (c - 0x20) * (i + 1);
			uSum2 += (c - 0x20) * (i * i);
		}
		else
		{
			uSum1 += c * (i + 1);
			uSum2 += c * (i * i);
		}
	}

	return (uSum2 << 24)|((UINT)ilen << 16)|uSum1;
}