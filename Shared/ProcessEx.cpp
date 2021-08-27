#include "StdAfx.h"
#include "ProcessEx.h"

namespace CINFO
{
	ProcessEx::ProcessEx()
	{
		WSADATA	wsaData;
		WSAStartup(MAKEWORD(2,2),&wsaData);

		srand(GetTickCount());
	}
	ProcessEx::~ProcessEx()
	{
		WSACleanup();
	}
	void ProcessEx::ForceExit(UINT uExitCode)
	{
		ExitProcess(uExitCode);
	}
}