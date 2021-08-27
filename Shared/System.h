#pragma once

enum ESystemOS
{
	SYSTEMOS_Unknown		= 0,

	SYSTEMOS_Windows2000	= 1,
	SYSTEMOS_WindowsXP		= 2,
	SYSTEMOS_Windows2003	= 3,
	SYSTEMOS_Windows2003R2	= 4,
	SYSTEMOS_WindowsVista	= 5,
	SYSTEMOS_Windows2008	= 6,
	SYSTEMOS_Windows2008R2	= 7,
	SYSTEMOS_Windows7		= 8,
	SYSTEMOS_Windows2012	= 9,
	SYSTEMOS_Windows8		= 10,
	SYSTEMOS_Windows2012R2	= 11,
	SYSTEMOS_Windows8_1		= 12,
	SYSTEMOS_Windows2016	= 13,
	SYSTEMOS_Windows10		= 14,
};

enum ESystemLanguage
{
	SYSTEMLANGUAGE_English,
	SYSTEMLANGUAGE_Korean,
	SYSTEMLANGUAGE_ChineseSimplified,
	SYSTEMLANGUAGE_Japanese,
	SYSTEMLANGUAGE_Thai,
};
namespace CINFO
{
	typedef class System *LPSYSTEM;

	class System
	{
	public:
		System();
		virtual ~System(){}
		ESystemOS GetSystemOS();
		ESystemLanguage GetSystemLanguage();
		BOOL IsMultiCore();
		int GetNumberOfCores();
		UINT GetRAMAmount();
		int ComputeFrameDelayTime();
		BOOL IsVistaOrLater();
		BOOL IsElevated();
		BOOL openURL(char *pszURL);
		BOOL openURLEx(char *pszFormatURL,...);
	protected:
		OSVERSIONINFO m_os_version_info;
		OSVERSIONINFOEX m_os_version_info_ex;
		SYSTEM_INFO m_sys_info;
		LANGID m_lang_id;
	};
}