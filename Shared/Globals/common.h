#pragma once

enum ETickType
{
	TICKTYPE_None,
	TICKTYPE_100MilliSecond,
	TICKTYPE_500MilliSecond,
	TICKTYPE_1Second,
	TICKTYPE_1Minute,
	TICKTYPE_1Hour,
};

#define KB1				(1ull * 1024ull)
#define KB2				(2ull * 1024ull)
#define KB4				(4ull * 1024ull)
#define KB8				(8ull * 1024ull)
#define KB16			(16ull * 1024ull)
#define KB32			(32ull * 1024ull)
#define KB64			(64ull * 1024ull)
#define KB128			(128ull * 1024ull)
#define KB192			(192ull * 1024ull)
#define KB256			(256ull * 1024ull)
#define KB512			(512ull * 1024ull)
#define MB1				(1ull * KB1 * KB1)
#define MB2				(2ull * KB1 * KB1)
#define MB4				(4ull * KB1 * KB1)
#define MB8				(8ull * KB1 * KB1)
#define GB1				(1ull * KB1 * MB1)
#define GB2				(2ull * KB1 * MB1)
#define GB4				(4ull * KB1 * MB1)
#define GB8				(8ull * KB1 * MB1)

#define ALPHA_LOW		0x00
#define ALPHA_HIGH		0xFF
#define ID				DWORD
#define ITEMCHECKSUM	DWORD

#define FILEEXIST		FileExist
#define REGEX			RegExMatch		

short RandomS(short l, short h, BOOL bUseTime = FALSE);
int RandomI(int l, int h, BOOL bUseTime = FALSE);
UINT RandomU(UINT l, UINT h, BOOL bUseTime = FALSE);
float RandomF(float l, float h);
double RandomD(double l, double h);
BOOL IsNull(const char * pszString);
BOOL IsNull(int iValue);
BOOL FileExist(const std::string& name);
const char * GetDateTime();
BOOL RegExMatch(const char *s, std::string &strText);
DWORD GetCodebyName(char *szName);
void SetClipboardText(char *szText);
std::string GetClipboardText();
int		GetDaysCountMonth(int iMonth, int iYear);
DWORD	SystemTimeToDWORD(SYSTEMTIME * ps);

struct CurMax
{
	short	  sMin;
	short	  sMax;

	short RandomValue() const { return RandomS(sMin, sMax, false); }

	bool operator ==(const CurMax &o) { return (sMin == o.sMin) && (sMax == o.sMax); }
	bool operator !=(const CurMax &o) { return !(*this == o); }
};

struct MinMax
{
	short	  sMin;
	short	  sMax;

	MinMax() {}
	MinMax(int sMin, int sMax) : sMin(sMin), sMax(sMax) {}

	short RandomValue() const { return RandomS(sMin, sMax, false); }

	bool operator ==(const MinMax &o) { return (sMin == o.sMin) && (sMax == o.sMax); }
	bool operator !=(const MinMax &o) { return !(*this == o); }
};
struct IMinMax
{
	int	  iMin;
	int	  iMax;

	IMinMax() {}
	IMinMax(int _iMin, int _iMax) : iMin(_iMin), iMax(_iMax) {}

	int RandomValue() const { return RandomI(iMin, iMax, false); }

	bool operator ==(const IMinMax &o) { return (iMin == o.iMin) && (iMax == o.iMax); }
	bool operator !=(const IMinMax &o) { return !(*this == o); }
};
struct UMinMax
{
	USHORT	  sMin;
	USHORT	  sMax;

	UMinMax() {}
	UMinMax(int sMin, int sMax) : sMin(sMin), sMax(sMax) {}
};