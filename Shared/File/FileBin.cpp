#include "StdAfx.h"
#include "FileBin.h"

namespace CFILE
{
	Bin::Bin() : m_pFile(NULL)
	{

	}
	Bin::Bin(const std::string &strFile,int iMode) : m_pFile(NULL)
	{
		Open(strFile,iMode);
	}
	Bin::~Bin()
	{
		Close();
	}
	BOOL Bin::IsOpen() const
	{
		return m_pFile != NULL;
	}
	BOOL Bin::Open(const std::string &strFile,int iMode)
	{
		// Open File
		char szMode[4] = { 0 };

		switch(iMode)
		{
		case BIN_READ:
			STRINGCOPY(szMode,"rb");
			break;
		case BIN_WRITE:
			STRINGCOPY(szMode,"wb");
			break;
		case BIN_UPDATE:
			STRINGCOPY(szMode,"ab");
			break;
		}

		if (fopen_s(&m_pFile,strFile.c_str(),szMode) == 0)
			return TRUE;

		return FALSE;
	}
	void Bin::Read(void *ptr,UINT uSize)
	{
		m_pFile ? fread(ptr, uSize, 1, m_pFile) : 0;
	}
	void Bin::Read(void *ptr,size_t iElementSize,size_t iCount)
	{
		m_pFile ? fread(ptr, iElementSize, iCount, m_pFile) : 0;
	}
	void Bin::Write(void *ptr,UINT uSize)
	{
		m_pFile ? fwrite(ptr, uSize, 1, m_pFile) : 0;
	}
	void Bin::Seek(UINT uPos)
	{
		m_pFile ? fseek(m_pFile, uPos, SEEK_SET) : 0;
	}
	int Bin::GetSize()
	{
		if (m_pFile)
		{
			fseek(m_pFile,0,SEEK_END);
			int iSize = ftell(m_pFile);
			fseek(m_pFile,0,SEEK_SET);
			return iSize;
		}

		return 0;
	}
	void Bin::Close()
	{
		if (m_pFile)
		{
			fclose(m_pFile);
			m_pFile = nullptr;
		}
	}
}