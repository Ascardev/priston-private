#include "StdAfx.h"
#include "smPacket.h"
#include "cracker.h"
#include "netplay.h"
#include "tlhelp32.h"

static char szWindowName[71];
static char szClassName[31];
static char szAddString[101];

DWORD	dwExeCheckSum = 0;				//실행파일 체크섬
char	szProcessPath[256] = { 0 };		//실행파일 경로


//////////NPROTECT 관련/////////////

//extern int DisconnectServerCode;
extern	int quit;

int	CrDebug = 1;

BOOL GetDebugPriv()
{
	HANDLE hToken;
	LUID sedebugnameValue;
	TOKEN_PRIVILEGES tkp;
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
	{
		return FALSE;
	}

	if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &sedebugnameValue))
	{
		CloseHandle(hToken);
		return FALSE;
	}
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = sedebugnameValue;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof tkp, NULL, NULL))
	{
		CloseHandle(hToken);
		return FALSE;
	}
	return TRUE;
}
long _stdcall CheckErrorToLog(_EXCEPTION_POINTERS *excp)
{
	char buf[1024];
	wsprintf(buf, "Error Addess %x\r\n CPU register:\r\n EAX %x ECX %x EDX %x EBX %x ESP %x EBP %x ESI %x EDI %x EIP %x\r\n", excp->ExceptionRecord->ExceptionAddress, excp->ContextRecord->Eax, excp->ContextRecord->Ecx, excp->ContextRecord->Edx, excp->ContextRecord->Ebx, excp->ContextRecord->Esp, excp->ContextRecord->Ebp, excp->ContextRecord->Esi, excp->ContextRecord->Edi, excp->ContextRecord->Eip);
	//MESSAGE(buf);
	return EXCEPTION_EXECUTE_HANDLER;
}
int CloseProcess(char *ProcName)
{
	PROCESSENTRY32 pe = { 0 };

	pe.dwSize = sizeof(PROCESSENTRY32);

	if (!GetDebugPriv())
		return FALSE;

	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hSnap != INVALID_HANDLE_VALUE)
	{
		BOOL bMore = Process32First(hSnap, &pe);
		while (bMore)
		{
			if (lstrcmpi(pe.szExeFile, ProcName) == 0)
			{
				HANDLE h = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe.th32ProcessID);
				TerminateProcess(h, 0);
				break;
			}
			bMore = Process32Next(hSnap, &pe);
		}
		CloseHandle(hSnap);
	}
	//else
		//MESSAGE("CreateToolhelp32Snapshot fail");
	return TRUE;
}
int GetWindowVersion()
{
	LANGID LangID = GetSystemDefaultLangID();

	return (PRIMARYLANGID(LangID));
}

extern HWND	hwnd;

HWND hWnd_CrackFocus = 0;
DWORD	dwTime_CrackFocus = 0;

#include "tlhelp32.h"

#define	CR_NAME		-9

char CrackProcess[][16] = {
	{ 'a' + CR_NAME,'r' + CR_NAME,'t' + CR_NAME,'m' + CR_NAME,'o' + CR_NAME,'n' + CR_NAME,'e' + CR_NAME, 0 },
	{ 'p' + CR_NAME,'a' + CR_NAME,'t' + CR_NAME,'c' + CR_NAME,'h' + CR_NAME, 0 },
	{ 0,0 }
};

char MyProcess[16] = {
	'.' + CR_NAME,'e' + CR_NAME,'x' + CR_NAME,'e' + CR_NAME, 0
};

char MyProcessName[64];

int CheckProcess(char *szProcessName)
{
	char szBuff1[64];
	int nCnt = 0;
	int cnt, len;

	lstrcpy(szBuff1, szProcessName);
	CharLower(szBuff1);
	len = lstrlen(szBuff1);
	for (cnt = 0; cnt < len; cnt++)
		szBuff1[cnt] += CR_NAME;

	while (1) {
		if (!CrackProcess[nCnt][0]) break;
		if (strstr(szBuff1, CrackProcess[nCnt]) != 0) {
			return TRUE;
		}
		nCnt++;
	}

	return NULL;
}

int CheckMyProcess(char *szProcessName)
{
	int nCnt = 0;
	int cnt, len;

	lstrcpy(MyProcessName, MyProcess);

	len = lstrlen(MyProcessName);
	for (cnt = 0; cnt < len; cnt++)
		MyProcessName[cnt] -= CR_NAME;

	return TRUE;

}

int MyEnumModule98(int pid);


//DWORD Check_CodeSafe(DWORD dwStartFunc);
//DWORD Check_CodeSafe2();

int CheckCrackProcess(int Flag)
{
	DWORD	ProcessID;
	int FindFlag = 0;

	ProcessID = GetCurrentProcessId();


	CheckMyProcess("game.exe");

	if (Flag)
		MyEnumModule98(ProcessID);

	return FindFlag;
}

// pid 프로세스의 모듈 목록을 구한다.
int MyEnumModule98(int pid)
{
	HANDLE hSnap;
	MODULEENTRY32 me;
	char str[256];

	str[0] = 0;

	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
	if (hSnap == (HANDLE)-1)
		return FALSE;

	me.dwSize = sizeof(MODULEENTRY32);
	if (Module32First(hSnap, &me))
	{
		do
		{
			CharLower(me.szExePath);
			if (strstr(me.szExePath, MyProcessName) != 0)
				lstrcpy(str, me.szExePath);
		} while (Module32Next(hSnap, &me));
	}
	CloseHandle(hSnap);

	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	DWORD	*szFileBuff;
	int		cnt;
	int		dCnt;

	if (str[0])
	{
		dwExeCheckSum = 0;
		hFile = CreateFile(str, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile != INVALID_HANDLE_VALUE)
		{
			FileLength = GetFileSize(hFile, NULL);
			szFileBuff = new DWORD[(FileLength / 4) + 256];
			ReadFile(hFile, szFileBuff, FileLength, &dwAcess, NULL);
			CloseHandle(hFile);

			dCnt = FileLength - 0x8000;
			dCnt /= 4;

			for (cnt = 0x1000; cnt < dCnt; cnt++)
			{
				dwExeCheckSum += szFileBuff[cnt] | (cnt*cnt*szFileBuff[cnt]);
				dwExeCheckSum += (szFileBuff[cnt] >> 16) + (szFileBuff[cnt] << 16);
			}
			if (!dwExeCheckSum) dwExeCheckSum = 1;
			delete[] szFileBuff;
		}
	}
	lstrcpy(szProcessPath, str);

	return TRUE;
}

DWORD	GetModuleCheckSum(char *szModule)
{
	DWORD	ProcessID;


	HANDLE hSnap;
	MODULEENTRY32 me;
	int cnt, len;
	DWORD ChkSum = 0;
	DWORD *lpBuff;

	ProcessID = GetCurrentProcessId();

	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, ProcessID);
	if (hSnap == (HANDLE)-1)
		return FALSE;

	me.dwSize = sizeof(MODULEENTRY32);
	if (Module32First(hSnap, &me)) {
		do {
			if (lstrcmpi(me.szModule, szModule) == 0) {

				lpBuff = (DWORD *)me.modBaseAddr;
				len = me.modBaseSize / sizeof(DWORD);
				for (cnt = 0; cnt < len; cnt++) {
					ChkSum += lpBuff[cnt] * (cnt & 0xFFFF);
				}
			}
		} while (Module32Next(hSnap, &me));
	}
	CloseHandle(hSnap);


	//GetSystemDirectory(

	return ChkSum;
}

int npAuth(DWORD dwAuthValue)
{
	return TRUE;

}