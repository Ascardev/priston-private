#include "StdAfx.h"
#include "Window.h"

CWindow::CWindow() : m_bRegisterSucess(FALSE),m_hWnd(NULL),m_dwUpdateTimeInterval(0),m_bExit(FALSE),m_bRuning(FALSE),m_bMinimized(FALSE)
{
	
}
CWindow::~CWindow()
{

}
void CWindow::LoadWindowMessage()
{
	MSG msg;

	if (m_bRuning)
	{
		while(PeekMessageA(&msg,NULL,0,0,PM_REMOVE))
		{
			if (ProcessMessage(msg))
			{
				if ((msg.message != WM_SYSKEYUP) && msg.message != WM_SYSKEYDOWN)
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
		}
	}
}

void CWindow::AddDialog(CDialog *pcDialog)
{
	if (pcDialog)
		m_vDialogs.push_back(pcDialog);
}

void CWindow::RemoveDialog(CDialog *pcDialog)
{
	if (pcDialog)
	{
		for (std::vector<CDialog *>::iterator it = m_vDialogs.begin(); it != m_vDialogs.end(); it ++)
		{
			CDialog *pcCur = *it;

			if (pcCur == pcDialog)
			{
				SHUTDOWN(pcDialog);
				DELET(pcDialog);

				m_vDialogs.erase(it);
				break;
			}
		}
	}
}

BOOL CWindow::Register(const char *pszClassName,UINT uStyle,UINT uIncon,HBRUSH hbrBackground)
{
	WNDCLASSEXA wcex = { 0 };

	wcex.cbSize = sizeof(WNDCLASSEXA);
	wcex.style = uStyle;
	wcex.lpfnWndProc = (WNDPROC)StaticWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_pcApplication->GetProcess()->GetInstanceHandle();
	wcex.hIcon = LoadIcon(wcex.hInstance,MAKEINTRESOURCE(uIncon));
	wcex.hbrBackground = hbrBackground;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = pszClassName;
	wcex.hIconSm = LoadIcon(wcex.hInstance,MAKEINTRESOURCE(uIncon));

	m_bRegisterSucess = RegisterClassExA(&wcex) != 0;

	if (m_bRegisterSucess)
		STRINGCOPY(m_szClassName,pszClassName);

	return m_bRegisterSucess;
}
void CWindow::Unregister()
{
	if (m_bRegisterSucess)
	{
		//UnregisterClassA(m_szClassName,m_pcApplication->GetProcess()->GetInstanceHandle());
		m_bRegisterSucess = FALSE;
	}
}
BOOL CWindow::MakeWindow(LPCSTR lpszTitle, BOOL bServer,BOOL bWindowed,BOOL bMaximized,int iWidth,int iHeight)
{
	HINSTANCE hInstance;

	hInstance = m_pcApplication->GetProcess()->GetInstanceHandle();

	if (m_hWnd)
		RemoveWindow();

	if (bServer)
		m_hWnd = CreateWindowEx(WS_EX_SERVER, "Server", lpszTitle, WS_SERVER, CW_USEDEFAULT, 0, iWidth, iHeight, NULL, NULL, hInstance, this);
	else
	{
		if (bWindowed)
		{
			//Window´°¿Ú
			SIZE sz;
			RECT rc;

			rc.top = rc.left = 0;
			rc.right = iWidth;
			rc.bottom = iHeight;

			AdjustWindowRect(&rc, WS_WINDOWED, FALSE);
			sz.cx = rc.right - rc.left;
			sz.cy = rc.bottom - rc.top;

			SIZE ps;
			if (!bMaximized)
			{
				ps.cx = (GetSystemMetrics(SM_CXSCREEN) >> 1) - (sz.cx >> 1);
				ps.cy = (GetSystemMetrics(SM_CYSCREEN) >> 1) - (sz.cy >> 1);
			}
			else
			{
				ps.cx = CW_USEDEFAULT;
				ps.cy = 0;
			}

			m_hWnd = CreateWindowEx(WS_EX_WINDOWED, lpszTitle, lpszTitle, WS_WINDOWED, ps.cx, ps.cy, sz.cx, sz.cy, NULL, NULL, hInstance, this);
		}
		else
			m_hWnd = CreateWindowEx(WS_EX_FULLSCREEN, lpszTitle, lpszTitle, WS_FULLSCREEN, CW_USEDEFAULT, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), NULL, NULL, hInstance, this);
	}

	return m_hWnd != NULL;
}

BOOL CWindow::PumpWindowMessage()
{
	if (!m_bExit)
	{
		MSG msg;

		while(PeekMessageA(&msg,NULL,0,0,PM_REMOVE))
		{
			if (ProcessMessage(msg))
			{
				if (msg.message == WM_QUIT)
				{
					m_bExit = TRUE;
					break;
				}

				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}

	return !m_bExit;
}
void CWindow::LoopWindowMessage()
{
	HANDLE hThread = CreateThread(NULL,KB2,(LPTHREAD_START_ROUTINE)UpdaterThread,this,STACK_SIZE_PARAM_IS_A_RESERVATION,NULL);

	MSG msg;

	while(GetMessageA(&msg,NULL,0,0))
	{
		if (ProcessMessage(msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	m_bExit = TRUE;

	WaitForSingleObject(hThread,INFINITE);

	CloseHandle(hThread);
}
BOOL CWindow::IsActive(BOOL bIncludeDialog)
{
	HWND hWndForeground = GetForegroundWindow();

	if (m_hWnd == hWndForeground)
		return TRUE;

	if (bIncludeDialog)
	{
		for (vector<CDialog*>::iterator it = m_vDialogs.begin(); it != m_vDialogs.end(); it ++)
		{
			CDialog *pcDialog = *it;

			if (pcDialog->GetWindowHandle() == m_hWnd)
				return TRUE;
		}
	}

	return FALSE;
}

BOOL CWindow::IsDialog(HWND hWnd)
{
	for (vector<CDialog *>::iterator it = m_vDialogs.begin(); it != m_vDialogs.end(); it ++)
	{
		CDialog *pcDialog = *it;

		if (pcDialog->GetWindowHandle() == hWnd)
			return TRUE;
	}

	return FALSE;
}

BOOL CWindow::ProcessMessage(MSG &msg)
{
	for (vector<CDialog *>::iterator it = m_vDialogs.begin(); it != m_vDialogs.end(); it ++)
	{
		CDialog *pcDialog = *it;

		if (IsDialogMessage(pcDialog->GetWindowHandle(),&msg))
			return FALSE;
	}

	return TRUE;
}
LRESULT CALLBACK CWindow::StaticWndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	CWindow *pcParent = NULL;

	if (uMsg == WM_CREATE)
	{
		pcParent = (CWindow *)((LPCREATESTRUCT)lParam)->lpCreateParams;
		pcParent->m_hWnd = hWnd;

		SetWindowLong(hWnd,GWL_USERDATA,(LONG)pcParent);
	}

	if (pcParent == NULL)
		pcParent = (CWindow *)GetWindowLongPtr(hWnd,GWL_USERDATA);

	if (pcParent == NULL)
		return DefWindowProc(hWnd,uMsg,wParam,lParam);

	return pcParent->WndProc(uMsg,wParam,lParam);
}

DWORD WINAPI CWindow::UpdaterThread(CWindow *pThis)
{
	HWND hWnd = pThis->m_hWnd;
	DWORD dwUpdateTimeInterval = pThis->m_dwUpdateTimeInterval;
	BOOL *ex = &pThis->m_bExit;
	BOOL bMultiCore = pThis->GetApplication()->GetSystem()->IsMultiCore();

	LARGE_INTEGER liFrequency,liLastTick,liNewTick;
	double *fTime = new double;

	QueryPerformanceFrequency(&liFrequency);

	double dFrequency = (double)liFrequency.QuadPart;

	if (bMultiCore)
		SetThreadAffinityMask(GetCurrentThread(),1);

	QueryPerformanceCounter(&liLastTick);

	while((*ex) == FALSE)
	{
		Sleep(dwUpdateTimeInterval);

		QueryPerformanceCounter(&liNewTick);
		(*fTime) = (((double)(liNewTick.QuadPart - liLastTick.QuadPart)) * 1000.0f) / dFrequency;
		liLastTick = liNewTick;

		SendMessageA(hWnd,WM_UPDATE,(WPARAM)fTime,(LPARAM)NULL);
	}

	delete fTime;

	return TRUE;
}
void CWindow::RemoveDialogs()
{
	for (vector<CDialog *>::iterator it = m_vDialogs.begin(); it != m_vDialogs.end(); it ++)
	{
		CDialog *pcDialog = *it;

		SHUTDOWN(pcDialog);
		DELET(pcDialog);
	}

	m_vDialogs.clear();
}

void CWindow::RemoveWindow()
{
	RemoveDialogs();

	if (IsWindow(m_hWnd))
		DestroyWindow(m_hWnd);

	m_hWnd = NULL;
}