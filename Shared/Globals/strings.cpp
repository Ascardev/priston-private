#include "StdAfx.h"
#include "strings.h"

char & lower(char & c)
{
	c = tolower(c);
	return c;
}

char * lower(char * s)
{
	for(int i = 0; s[i] != 0; i ++)
		lower(s[i]);

	return s;
}

std::string & ltrim(std::string & s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

std::string & rtrim(std::string & s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

std::string & trim(std::string & s)
{
	return ltrim(rtrim(s));
}

std::string ToLower(const std::string & s)
{
	std::string r;
	r.reserve(s.length());

	for (unsigned int i = 0; i < s.length(); i ++)
	{
		char c = s.at(i);
		r.push_back(lower(c));
	}

	return r;
}

int low(int a,int b)
{
	if (a < b)
		return a;

	return b;
}

int high(int a,int b)
{
	if (a > b)
		return a;

	return b;
}

void FormatNumber(INT64 iNumber,char *pszBufferOut,int iBufferOutLen)
{
	if (iBufferOutLen <= 0)
		return;

	BOOL bNegative = FALSE;

	if (iNumber < 0)
		bNegative = TRUE;

	iNumber = abs(iNumber);

	ZeroMemory(pszBufferOut,iBufferOutLen);

	char szBuffer[256];

	STRINGFORMAT(szBuffer,"%I64d",iNumber);

	while(iNumber >= 1000)
		iNumber /= 1000;

	int iFirstSeperatorIndex = 1;

	while(iNumber >= 10)
	{
		iNumber /= 10;
		
		iFirstSeperatorIndex ++;
	}

	int iLen = STRLEN(szBuffer);

	for (int i = 0, j = 0; i < iLen; i ++)
	{
		if (j >= (iBufferOutLen - 1))
		{
			CopyMemory(pszBufferOut,"ERROR BUFFER LENGTH",iBufferOutLen);
			return;
		}

		if ((i != 0) && (((i - iFirstSeperatorIndex) % 3) == 0))
			pszBufferOut[j ++] = ',';

		pszBufferOut[j ++] = szBuffer[i];
	}

	if (bNegative)
	{
		int j = STRLEN(pszBufferOut);

		if (j >= iBufferOutLen)
		{
			CopyMemory(pszBufferOut,"ERROR BUFFER LENGTH",iBufferOutLen);
			return;
		}

		for (int i = j; i > 0; i --)
			pszBufferOut[i] = pszBufferOut[i - 1];

		pszBufferOut[0] = '-';
	}
}
const char *FormatNumber(INT64 iNumber)
{
	static char szValue[128] = { 0 };

	STRINGEMPTY(szValue);
	FormatNumber(iNumber,szValue,_countof(szValue));

	return szValue;
}
const char *FormatString(const char *pszFormat, ...)
{
	va_list vl;

	static char szString[4096];
	va_start(vl, pszFormat);
	_vsnprintf_s(szString, _countof(szString),_TRUNCATE,pszFormat,vl);
	va_end(vl);

	return szString;
}
std::vector<std::string> split(const std::string & s, char delim)
{
	std::stringstream ss(s);
	std::string item;

	std::vector<std::string> tokens;

	while(getline(ss,item,delim))
		tokens.push_back(item);

	return tokens;
}
std::string GetFileExtension(const std::string &strFilePath)
{
	auto stDotIndex = strFilePath.rfind('.');

	if (stDotIndex != std::string::npos)
	{
		auto stSlashIndex = strFilePath.rfind('/');

		if (stSlashIndex != std::string::npos)
		{
			if (stSlashIndex > stDotIndex)
				return "";
		}

		auto stBackSlashIndex = strFilePath.rfind('\\');

		if (stBackSlashIndex != std::string::npos)
		{
			if (stBackSlashIndex > stDotIndex)
				return "";
		}

		char szFileExtension[MAX_PATH] = { 0 };

		STRINGCOPY(szFileExtension,strFilePath.substr(stDotIndex + 1).c_str());

		return rtrim(MakeLower(szFileExtension));
	}

	return "";
}
std::string ReplaceExtensionName(const std::string &strFilePath,const std::string &strExtension)
{
	auto stDotIndex = strFilePath.rfind('.');

	if (stDotIndex != std::string::npos)
	{
		auto stSlashIndex = strFilePath.rfind('/');

		if (stSlashIndex != std::string::npos)
		{
			if (stSlashIndex > stDotIndex)
				return "";
		}

		auto stBackSlashIndex = strFilePath.rfind('\\');

		if (stBackSlashIndex != std::string::npos)
		{
			if (stBackSlashIndex > stDotIndex)
				return "";
		}

		std::string strFile = strFilePath;

		return strFile.replace(stDotIndex + 1,strFilePath.length() - stDotIndex,strExtension);
	}

	return "";
}
std::string GetPathFileName(const std::string strFilePath, BOOL bExt)
{
	auto stDoIndex = strFilePath.find_last_of('\\');

	if (stDoIndex != std::string::npos)
	{
		std::string s = bExt ? strFilePath.substr(stDoIndex + 1) : strFilePath.substr(stDoIndex + 1, strFilePath.rfind('.') - stDoIndex - 1);

		return s;
	}

	auto stSlashIndex = strFilePath.rfind('/');

	if (stSlashIndex != std::string::npos)
	{
		std::string s = bExt ? strFilePath.substr(stSlashIndex + 1) : strFilePath.substr(stSlashIndex + 1, strFilePath.rfind('.') - stSlashIndex - 1);

		return s;
	}

	return "";
}

UINT GetFileLevel(const std::string &strTextureFile)
{
	UINT uLevels = 0;

	char szFilePath[MAX_PATH] = { 0 };
	STRINGCOPY(szFilePath,strTextureFile.c_str());

	const char *iDot = strchr(szFilePath,'.');

	if (iDot != NULL)
	{
		char szBaseFile[MAX_PATH],szFileExtension[MAX_PATH];

		int iLenToDot = iDot - szFilePath;

		//Get Base File
		STRINGCOPY(szBaseFile,szFilePath);
		szBaseFile[iLenToDot] = 0;

		//Get File Extension
		STRINGCOPY(szFileExtension,szBaseFile + iLenToDot + 1);

		//Find Mip Levels
		for (int i = 1; i <= 4; i ++)
		{
			char szBuffer[MAX_PATH];
			STRINGFORMAT(szBuffer,"%s_mm%d.%s",szBaseFile,i,szFileExtension);

			uLevels += PathFileExistsA(szBuffer) ? 1: 0;
		}
	}

	return uLevels;
}
std::string MakeUpper(std::string s)
{
	std::transform(s.begin(), s.end(), s.begin(), ::toupper);

	return s;
}
std::string MakeLower(std::string s)
{
	std::transform(s.begin(), s.end(), s.begin(), ::tolower);

	return s;
}
// 转换为UNICODE
std::wstring ANSIToUnicode(const std::string &str)
{
	if (str.length() <= 0)
		return L"";

	int ilen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	wchar_t *pwszstr = new wchar_t[ilen + 1];

	ZeroMemory(pwszstr, sizeof(wchar_t) * (ilen + 1));

	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, pwszstr, ilen);

	std::wstring wstr(pwszstr);

	DELETA(pwszstr);

	return wstr;
}
//转换为ANSI
std::string UnicodeToANSI(const std::wstring &wstr)
{
	if (wstr.length() <= 0)
		return "";

	int ilen = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);

	char *pszstr = new char[ilen + 1];

	ZeroMemory(pszstr, sizeof(char) * (ilen + 1));

	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, pszstr, ilen, NULL, NULL);

	static std::string str;

	str = pszstr;

	DELETA(pszstr);

	return str;
}
// 转换为UNICODE
std::wstring UTF8ToUnicode(const std::string &str)
{
	if (str.length() <= 0)
		return L"";

	int ilen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);

	wchar_t *pwszstr = new wchar_t[ilen + 1];

	ZeroMemory(pwszstr, sizeof(wchar_t) * (ilen + 1));

	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, pwszstr, ilen);

	std::wstring wstr(pwszstr);

	DELETA(pwszstr);

	return wstr;
}
//转换为ANSI
std::string UnicodeToUTF8(const std::wstring &wstr)
{
	if (wstr.length() <= 0)
		return "";

	int ilen = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);

	char *pszstr = new char[ilen + 1];

	ZeroMemory(pszstr, sizeof(char) * (ilen + 1));

	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, pszstr, ilen, NULL, NULL);

	std::string str(pszstr);

	DELETA(pszstr);

	return str;
}
std::string ANSIToUTF8(const std::string &str)
{
	return UnicodeToUTF8(ANSIToUnicode(str));
}
std::string UTF8ToANSI(const std::string &str)
{
	return UnicodeToANSI(UTF8ToUnicode(str));
}
unsigned int ChatCommand(char * pszCommand, char * pszChat)
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

	//unsigned char cLastCharacter = pszChat[iLen];
	//if ((cLastCharacter != 0x00) && (cLastCharacter != 0x09) && (cLastCharacter != 0x20))
		//return 0;

	return iLen;
}
int GetParameterString(const char * Command, int Arg, char buf[256])
{
	int iStringSize = lstrlenA(Command);
	if (iStringSize <= 0)
		return 0;

	int nCountSpaces = 0;

	int i = 0;

	bool bSpaceArg = false;

	while (i < iStringSize)
	{
		if (Command[i] == ' ')
		{
			if (bSpaceArg == false)
				nCountSpaces++;

			if ((i + 1) < iStringSize)
			{
				if (Command[i + 1] != ' ')
				{
					if (Command[i + 1] == '\"')
					{
						if (bSpaceArg == true)
							bSpaceArg = false;
						else
							bSpaceArg = true;
					}

					if (nCountSpaces == Arg)
					{
						bool bFirstCh = false;

						if (Command[i + 1] == '\"')
						{
							if (buf != 0)
							{
								strcpy_s(buf, 256, &Command[i + 2]);
								for (int j = 0; j < lstrlenA(buf); j++)
								{
									if (buf[j] == '\"')
									{
										buf[j] = 0;
										break;
									}

								}
							}
						}
						else
						{
							if (buf != 0)
							{
								strcpy_s(buf, 256, &Command[i + 1]);
								for (int j = 0; j < lstrlenA(buf); j++)
								{
									if (buf[j] == ' ')
									{
										buf[j] = 0;
										break;
									}

								}
							}
						}
						return i + 1;
					}
				}
				if (Command[i + 1] == ' ')
					nCountSpaces--;
			}
		}
		else
			if (Command[i + 1] == '\"')
			{
				if (bSpaceArg == true)
					bSpaceArg = false;
			}
		i++;
	}
	return 0;
}
