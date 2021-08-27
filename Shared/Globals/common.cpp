#include "StdAfx.h"
#include "common.h"

short RandomS(short l, short h, BOOL bUseTime)
{
	if (l == h)
		return l;

	if (bUseTime)
		srand(GetCurrentTime() << 8 | rand());

	return (short)(rand() % (h - l)) + l;
}
int RandomI(int l, int h, BOOL bUseTime)
{
	if (l == h)
		return l;

	if (bUseTime)
		srand(GetCurrentTime() << 8 | rand());

	int i = rand();

	i += i << 16;

	return (i % (h - l)) + l;
}
UINT RandomU(UINT l, UINT h, BOOL bUseTime)
{
	if (l == h)
		return l;

	h -= l;

	if (bUseTime)
		srand(GetCurrentTime() << 8 | rand());

	USHORT sh1 = RandomI(0, RAND_MAX + 1) + RandomI(0, RAND_MAX + 1);
	USHORT sh2 = RandomI(0, RAND_MAX + 1) + RandomI(0, RAND_MAX + 1);

	UINT i = sh1 | (sh2 << 16);

	return (i % (h - l)) + l;
}
float RandomF(float l, float h)
{
	if (l == h)
		return l;

	return ((((float)rand()) / ((float)RAND_MAX)) * (h - l)) + l;
}
double RandomD(double l, double h)
{
	if (l == h)
		return l;

	return ((((double)rand()) / ((double)RAND_MAX)) * (h - l)) + l;
}

BOOL IsNull(const char * pszString)
{
	if (STRLEN(pszString) <= 0)
		return TRUE;

	if (STRINGCOMPARE(pszString, "NULL"))
		return TRUE;

	return FALSE;
}

BOOL IsNull(int iValue)
{
	if (!iValue)
		return TRUE;

	return FALSE;
}

BOOL FileExist(const std::string& name)
{
	FILE * fp = NULL;
	fopen_s(&fp, name.c_str(), "rb");
	if (fp)
	{
		fclose(fp);
		return TRUE;
	}
	return FALSE;
}

const char * GetDateTime()
{
	char szDate[9] = { 0 };
	char szTime[9] = { 0 };

	_strdate_s(szDate, 9);
	_strtime_s(szTime, 9);

	return FormatString("%s %s", szDate, szTime);
}
BOOL RegExMatch(const char *s, std::string &strText)
{
	std::regex e(s);

	if (std::regex_match(strText.begin(), strText.end(), e) == FALSE)
	{
		strText = "";
		return FALSE;
	}

	return TRUE;
}

DWORD GetCodebyName(char *szName)
{
	int iChk1 = 0;
	int iChk2 = 0;

	int iLength = STRLEN(szName);

	for (int i = 0; i < iLength; i++)
	{
		char ch = szName[i];

		if (ch >= 'a' && ch <= 'z')
		{
			iChk1 += (ch - 0x20)*(i + 1);
			iChk2 += (ch - 0x20)*(i * i);
		}
		else
		{
			iChk1 += ch * (i + 1);
			iChk2 += ch * (i * i);
		}
	}

	return (iChk2 << 24) | (iLength << 16) | iChk1;
}

void SetClipboardText(char *szText)
{
	HGLOBAL x;
	char *y;

	x = GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE, 0x64);
	y = (char *)GlobalLock(x);

	strcpy_s(y, 0x64, szText);
	GlobalUnlock(x);

	OpenClipboard(NULL);
	EmptyClipboard();
	
	SetClipboardData(CF_TEXT, x);
	CloseClipboard();
}

std::string GetClipboardText()
{
	//Try opening the clipboard
	if (!OpenClipboard(nullptr))
		return "";

	//Get handle of clipboard object for ANSI text
	HANDLE hData = GetClipboardData(CF_TEXT);

	if (hData == nullptr)
		return "";

	//Lock the handle to get the actual text pointer
	char *pszText = static_cast<char *>(GlobalLock(hData));

	if (pszText == nullptr)
		return "";

	//Save text in a string class instance
	std::string strtext(pszText);

	//Release the lock
	GlobalUnlock(hData);

	//Release the clipboard
	CloseClipboard();

	return strtext;
}
int GetDaysCountMonth(int iMonth, int iYear)
{
	if ((iMonth == 4) || (iMonth == 6) || (iMonth == 9) || (iMonth == 11))
		return 30;
	else if (iMonth == 2)
	{
		if (((iYear % 400) == 0) || (((iYear % 4) == 0) && ((iYear % 100) != 0)))
			return 29;
		else
			return 28;
	}

	return 31;
}
DWORD SystemTimeToDWORD(SYSTEMTIME * ps)
{
	if (ps == NULL)
		return NULL;

	DWORD dw;
	int iDM = GetDaysCountMonth(ps->wMonth, ps->wYear);

	dw = ps->wSecond + (ps->wMinute * 60) + (ps->wHour * 60 * 60) + (ps->wDay * 60 * 60 * 24) + (ps->wMonth * 60 * 60 * 24 * iDM);

	return dw;
}