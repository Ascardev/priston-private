
extern DWORD	dwExeCheckSum;		//�������� üũ��
extern char		szProcessPath[256];	//�������� ���



HWND WinFocusCrack();
// �������� ���μ����� ����� ���Ѵ�.
int CheckCrackProcess( int Flag=0 );

//�ش� ����� �˻��Ͽ� ýũ�� ��ȯ
DWORD	GetModuleCheckSum( char *szModule );

long _stdcall CheckErrorToLog(_EXCEPTION_POINTERS *excp);

int CloseProcess(char *ProcName);

int GetWindowVersion();

// ���ӿ��� NPMON.EXE�� �����ִ� �ڵ����� �޽��� (��������� ����)
#define WM_NPROTECT_FORCEEXIT		(WM_USER + 10010)

//////////////////////Npmon.exe�� �������� ������ �޽���/////////////////////////////////
#define WM_NPROTECT_EXIT_TWO		(WM_USER + 10001)

//- ������ ���ǵ����� ����� ��� (������(SPEEDER)�� ���� ���ܰ���)
//������ ĸ�Ǹ��� �����Ͽ� ������ �޽��� ����. (npmon 4.10.0.35 ���� �����)
#define WM_NPROTECT_SPEEDHACK		(WM_USER + 10011) //����ڿ��� �������� �޽��� : ���ǵ����� �߰ߵǾ����ϴ�.
#define WM_NPROTECT_SH_ERROR		(WM_USER + 10012) //������ �������� �α����Ͽ� ������ �����Ͻñ� �ٶ��ϴ�.

//- ������ ����Ʈ ���̽��� ����� ���
//������ ĸ�Ǹ��� �����Ͽ� ������ �޽��� ����. (npmon 4.10.0.35 ���� �����)
#define WM_NPROTECT_SOFTICE			(WM_USER + 10111) //����Ʈ ���̽��� �߰� �Ǿ����ϴ�.
///////////////////////////////////////////////////////////////////////////////////////////////






