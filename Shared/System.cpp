#include "StdAfx.h"
#include "System.h"

#pragma warning(disable: 4996)

namespace CINFO
{
	System::System()
	{
		m_os_version_info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		GetVersionEx((LPOSVERSIONINFO)&m_os_version_info);

		m_os_version_info_ex.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
		GetVersionEx((LPOSVERSIONINFO)&m_os_version_info_ex);

		m_lang_id = GetUserDefaultLangID();
	}
	ESystemOS System::GetSystemOS()
	{
		OSVERSIONINFO * v = &m_os_version_info;
		OSVERSIONINFOEX *e = &m_os_version_info_ex;

		if (v->dwMajorVersion == 5 && v->dwMinorVersion == 0)
			return SYSTEMOS_Windows2000;

		if (v->dwMajorVersion == 5 && v->dwMinorVersion == 1)
			return SYSTEMOS_WindowsXP;

		if (v->dwMajorVersion == 5 && v->dwMinorVersion == 2)
		{
			if (GetSystemMetrics(SM_SERVERR2) != 0)
				return SYSTEMOS_Windows2003R2;

			return SYSTEMOS_Windows2003;
		}

		if (v->dwMajorVersion == 6 && v->dwMinorVersion == 0)
		{
			if (e->wProductType != VER_NT_WORKSTATION)
				return SYSTEMOS_Windows2008;

			return SYSTEMOS_WindowsVista;
		}

		if (v->dwMajorVersion == 6 && v->dwMinorVersion == 1)
		{
			if (e->wProductType != VER_NT_WORKSTATION)
				return SYSTEMOS_Windows2008R2;

			return SYSTEMOS_Windows7;
		}

		if (v->dwMajorVersion == 6 && v->dwMinorVersion == 2)
		{
			if (e->wProductType != VER_NT_WORKSTATION)
				return SYSTEMOS_Windows2012;

			return SYSTEMOS_Windows8;
		}

		if (v->dwMajorVersion == 6 && v->dwMinorVersion == 3)
		{
			if (e->wProductType != VER_NT_WORKSTATION)
				return SYSTEMOS_Windows2012R2;

			return SYSTEMOS_Windows8_1;
		}

		if (v->dwMajorVersion == 10 && v->dwMinorVersion == 0)
		{
			if (e->wProductType != VER_NT_WORKSTATION)
				return SYSTEMOS_Windows2016;

			return SYSTEMOS_Windows10;
		}

		return SYSTEMOS_Unknown;
	}

	ESystemLanguage System::GetSystemLanguage()
	{
		switch (m_lang_id)
		{
		case 0x0412:
			return SYSTEMLANGUAGE_Korean;
		case 0x0C04:
		case 0x1404:
		case 0x1004:
		case 0x0004:
		case 0x7C04:
			return SYSTEMLANGUAGE_ChineseSimplified;
		case 0x0411:
			return SYSTEMLANGUAGE_Japanese;
		case 0x41E:
			return SYSTEMLANGUAGE_Thai;
		}

		return SYSTEMLANGUAGE_English;
	}
	BOOL System::IsMultiCore()
	{
		return (m_sys_info.dwNumberOfProcessors > 1);
	}
	int System::GetNumberOfCores()
	{
		return m_sys_info.dwNumberOfProcessors;
	}
	UINT System::GetRAMAmount()
	{
		MEMORYSTATUSEX sMemoryStatus;

		sMemoryStatus.dwLength = sizeof(MEMORYSTATUSEX);
		if (GlobalMemoryStatusEx(&sMemoryStatus))
			return (UINT)(sMemoryStatus.ullTotalPhys / 1024000);

		return 0;
	}
	int System::ComputeFrameDelayTime()
	{
		int iNumberOfCores = GetNumberOfCores();

		if (iNumberOfCores > 2)
			return 50;

		if (iNumberOfCores == 2)
			return 100;

		return 250;
	}
	// 判断是否是Vista系统
	BOOL System::IsVistaOrLater()
	{
		if (m_os_version_info_ex.dwPlatformId == VER_PLATFORM_WIN32_NT &&
			m_os_version_info_ex.dwMajorVersion >= 6)
			return TRUE;

		return FALSE;
	}
	BOOL System::IsElevated()
	{
		HANDLE hToken;
		TOKEN_ELEVATION te = { 0 };
		DWORD dwReturnLength = 0;
		BOOL bElevated = TRUE;

		if (IsVistaOrLater())
		{
			if (OpenProcessToken(GetCurrentProcess(),TOKEN_QUERY,&hToken))
			{
				if (GetTokenInformation(hToken,TokenElevation,&te,sizeof(te),&dwReturnLength))
					bElevated = te.TokenIsElevated ? TRUE : FALSE;

				CloseHandle(hToken);
			}
		}

		return bElevated;
	}
	BOOL System::openURL(char *pszURL)
	{
		UINT iSE;

		if (pszURL != NULL)
		{
			if (pszURL[0] == 'h' && pszURL[1] == 't' && pszURL[2] == 't' && pszURL[3] == 'p')
			{
				iSE = (UINT)ShellExecuteA(NULL,"open",pszURL,NULL,NULL,SW_SHOWNORMAL);

				if (iSE > 32)
					return TRUE;
			}
		}

		return FALSE;
	}
	BOOL System::openURLEx(char *pszFormatURL,...)
	{
		va_list vl;
		char szURL[MAX_PATH];

		va_start(vl,pszFormatURL);
		_vsnprintf_s(szURL,_countof(szURL),_TRUNCATE,pszFormatURL,vl);
		va_end(vl);

		return openURL(szURL);
	}
}