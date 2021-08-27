#pragma once

#define STRINGSAFE(str)						str[_countof(str)-1] = 0

#define STRLEN(str)							lstrlenA(str)
#define STRLENW(str)						lstrlenW(str)

#define STRINGEMPTY(dest)					ZeroMemory(dest,sizeof(dest))

#define STRINGCOPY(dest,src)				strcpy_s(dest,_countof(dest),src)
#define STRINGCAT(dest,src)					strcat_s(dest,_countof(dest),src)

#define STRINGCOPYLEN( dest, len, src )			strcpy_s( dest, len, src )

#define STRINGFORMAT( dest, fmt, ... )			sprintf_s( dest, _countof( dest ), fmt, ##__VA_ARGS__ )

#define STRINGCOMPARE( str1, str2 )				(lstrcmpA( str1, str2 ) == 0)
#define STRINGCOMPAREI( str1, str2 )			(lstrcmpiA( str1, str2 ) == 0)

int low(int a,int b);
int high(int a,int b);
std::string & trim(std::string & s);
const char *FormatNumber(INT64 iNumber);
const char *FormatString(const char *pszFormat, ...);
std::vector<std::string> split(const std::string & s, char delim);
std::string GetFileExtension(const std::string &strFilePath);
std::string ReplaceExtensionName(const std::string &strFilePath,const std::string &strExtension);
std::string GetPathFileName(const std::string strFilePath,BOOL bExt = TRUE);
UINT GetFileLevel(const std::string &strTextureFile);
std::string MakeUpper(std::string s);
std::string MakeLower(std::string s);
std::wstring ANSIToUnicode(const std::string &str);
std::string UnicodeToANSI(const std::wstring &wstr);
std::wstring UTF8ToUnicode(const std::string &str);
std::string UnicodeToUTF8(const std::wstring &wstr);
std::string ANSIToUTF8(const std::string &str);
std::string UTF8ToANSI(const std::string &str);

unsigned int ChatCommand(char * pszCommand, char * pszChat);
int GetParameterString(const char * Command, int Arg, char buf[256]);