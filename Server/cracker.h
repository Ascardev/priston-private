
extern DWORD	dwExeCheckSum;		//실행파일 체크섬
extern char		szProcessPath[256];	//실행파일 경로



HWND WinFocusCrack();
// 실행중인 프로세스의 목록을 구한다.
int CheckCrackProcess( int Flag=0 );

//해당 모듈을 검사하여 첵크섬 반환
DWORD	GetModuleCheckSum( char *szModule );

long _stdcall CheckErrorToLog(_EXCEPTION_POINTERS *excp);

int CloseProcess(char *ProcName);

int GetWindowVersion();

// 게임에서 NPMON.EXE로 보내주는 자동종료 메시지 (게임종료시 적용)
#define WM_NPROTECT_FORCEEXIT		(WM_USER + 10010)

//////////////////////Npmon.exe가 게임으로 보내는 메시지/////////////////////////////////
#define WM_NPROTECT_EXIT_TWO		(WM_USER + 10001)

//- 게임중 스피드핵을 사용할 경우 (구버젼(SPEEDER)의 버그 진단가능)
//게임의 캡션명을 참조하여 윈도우 메시지 전송. (npmon 4.10.0.35 부터 적용됨)
#define WM_NPROTECT_SPEEDHACK		(WM_USER + 10011) //사용자에게 보여지는 메시지 : 스피드핵이 발견되었습니다.
#define WM_NPROTECT_SH_ERROR		(WM_USER + 10012) //관리자 계정으로 로그인하여 게임을 실행하시기 바랍니다.

//- 게임중 소프트 아이스를 사용할 경우
//게임의 캡션명을 참조하여 윈도우 메시지 전송. (npmon 4.10.0.35 부터 적용됨)
#define WM_NPROTECT_SOFTICE			(WM_USER + 10111) //소프트 아이스가 발견 되었습니다.
///////////////////////////////////////////////////////////////////////////////////////////////






