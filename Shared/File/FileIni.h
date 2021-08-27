#pragma once

namespace CFILE
{
	class Ini
	{
	public:
		Ini(std::string strFileName);
		virtual ~Ini();

		// Reader Function
		std::string ReadString(const char *pszSection,const char *pszKey);
		int ReadInt(const char *pszSection,const char *pszKey);
		BOOL ReadOnOff(const char *pszSection,const char *pszKey);
		BOOL ReadBool(const char *pszSection,const char *pszKey);

		// Write Function
		void WriteString(const char *pszSection,const char *pszKey,std::string strText);
		void WriteInt(const char *pszSection,const char *pszKey,int iValue);
		void WriteOnOff(const char *pszSection,const char *pszKey,BOOL bValue);
		void WriteBool(const char *pszSection,const char *pszKey,BOOL bValue);
	private:
		std::string m_strFileName;
	};
}