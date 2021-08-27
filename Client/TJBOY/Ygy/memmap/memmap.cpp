#include "StdAfx.h"
#include "memmap.h"
#define __MEMDEBUG

CMemMap::CMemMap()
{
	m_cMemMapPtr = NULL;
	m_hMemMap = NULL;
	m_nMemMapSize = 0;
	m_bIsMemMap = FALSE;
	
}

CMemMap::~CMemMap()
{
}

VOID CMemMap::Clear()
{
	if((m_cMemMapPtr != NULL) &&m_bIsMemMap)
		UnmapViewOfFile(m_cMemMapPtr);
	if(m_hMemMap != NULL)
		CloseHandle(m_hMemMap);
}

VOID CMemMap::SetName(char* name)
{
	ZeroMemory(m_szMemMapName, sizeof(m_szMemMapName) );
	STRINGCOPY(m_szMemMapName,name);
}

VOID CMemMap::SetMemMapSize(int size)
{
	m_nMemMapSize = size;
}
BOOL CMemMap::InitMemoryMap()
{
	if((m_nMemMapSize > 0) &&(m_szMemMapName[0] != 0))
	{
		m_hMemMap = CreateFileMapping(
			INVALID_HANDLE_VALUE,		//0xffffffff���� ����
			NULL,						//���ȼӼ� : ���� NULL
			PAGE_READWRITE,				//�б�, ����, �б�+����
			0,							//�Ҵ�޸��� �ִ�ũ���� ���� 32��Ʈ��(64��Ʈ������ ���������ϱ⶧��)
			m_nMemMapSize,				//�Ҵ�޸��� ���� 32��Ʈ
			m_szMemMapName);		//���� �̸�

		if(m_hMemMap == NULL)
		{
			return FALSE;
		}	

		m_cMemMapPtr =(char *)MapViewOfFile(m_hMemMap, FILE_MAP_ALL_ACCESS,0,0, m_nMemMapSize);

		if(m_cMemMapPtr == NULL)
		{
			return FALSE;
		}
	}
	else
		return FALSE;

	m_bIsMemMap = TRUE;

	return TRUE;
}

VOID CMemMap::WriteMemoryMap(char *data)
{
	if(m_nMemMapSize <=0) 
		return;
	ZeroMemory(m_cMemMapPtr, m_nMemMapSize);

#ifdef __MEMDEBUG
	char szTemp[1024];
	memcpy(szTemp,data,1024);

#endif
	memcpy(m_cMemMapPtr, data, m_nMemMapSize);
}
VOID CMemMap::WriteMemoryMap(char *data, int size)
{
	if(m_nMemMapSize <=0) 
		return;
	ZeroMemory(m_cMemMapPtr, m_nMemMapSize);

	memcpy(m_cMemMapPtr, data, size);
}
VOID CMemMap::ReadMemoryMap(char* data)
{
	ZeroMemory(data, m_nMemMapSize);
	memcpy(data,m_cMemMapPtr, m_nMemMapSize);
}