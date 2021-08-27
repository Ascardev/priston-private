#include "StdAfx.h"
#include "GameWindow.h"

LPCGAMEWINDOW CGAMEWINDOW::m_pcInstance;

CGAMEWINDOW::CGAMEWINDOW() : CWINDOW(),m_uTimerID(0), m_iWindowInactiveFrameSleepTime(0)
{
	CGAMEWINDOW::m_pcInstance = this;
	m_pcGame = new CGAME;
}
CGAMEWINDOW::~CGAMEWINDOW()
{
	DELET(m_pcGame);
}
UINT CGAMEWINDOW::Init()
{
	CMODEL::LPSETTINGS p = SETTINGSHANDLER->GetModel();

	p->Read();

	if (!Register(GAME_NAME,CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS,111,(HBRUSH)(GetStockObject(BLACK_BRUSH))))
	{
		ERRORBOX("Register() failed!\n\nGetLastError returned %d", GetLastError());
		return 0;
	}

	if (!MakeWindow(GAME_NAME,FALSE,p->Get().bWindowed,FALSE,p->Get().uWidth,p->Get().uHeight))
	{
		ERRORBOX("MakeWindow() failed!\n\nGetLastError returned %d", GetLastError());
		return 0;
	}

	if (!GRAPHICENGINE->InitD3D(m_hWnd))
	{
		return 0;
	}

	m_bExit		= FALSE;
	m_bRuning	= FALSE;

	m_pcTimer	= GAMETIME;

	m_iWindowInactiveFrameSleepTime = GetApplication()->GetSystem()->ComputeFrameDelayTime();

	m_pcTimer->SetMultiCore(GetApplication()->GetSystem()->IsMultiCore());
	m_pcTimer->Update();

	if (GetApplication()->GetSystem()->IsMultiCore())
	{
		DWORD_PTR dw = (1 << GetApplication()->GetSystem()->GetNumberOfCores()) - 1;
	}

	return 1;
}
void CGAMEWINDOW::Shutdown()
{
	Unregister();
}
BOOL CGAMEWINDOW::Run()
{
	CMODEL::LPSETTINGS p = SETTINGSHANDLER->GetModel();

	if (p->Get().bMaximized)
		ShowWindow(m_hWnd,SW_MAXIMIZE);
	else
		ShowWindow(m_hWnd,SW_SHOWNORMAL);

	SetProcessDEPPolicy(0);

	m_bExit = FALSE;
	m_bRuning = TRUE;

	while(PumpWindowMessage())
	{
		//Game Loop
		Loop();
		if (!IsActive())
			Sleep(m_iWindowInactiveFrameSleepTime);
	}

	m_bRuning = FALSE;
	m_bExit = TRUE;

	return TRUE;
}
LRESULT CGAMEWINDOW::WndProc(UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SETCURSOR:
		if ((HWND)(wParam) == m_hWnd)
			MOUSEHANDLER->GetModel()->SetCursorGame();
		break;
	case WM_KILLFOCUS:
		SetFocus(m_hWnd);
		break;
	case WM_MOUSEMOVE:
		int iX,iY;
		iX = (int)(LOWORD(lParam));
		iY = (int)(HIWORD(lParam));

		CMODEL::LPSETTINGS p;
		
		p = SETTINGSHANDLER->GetModel();

		if (p->Get().bWindowed && !p->Get().bAutoAdjust)
		{
			RECT rc;
			rc.left = rc.top = 0;
			rc.right = p->GetOld().uWidth;
			rc.bottom = p->GetOld().uHeight;

			UINT uWindowstyle = GetWindowLongA(GAMEWINDOW->GetHandle(),GWL_STYLE);

			//Adjust Window
			AdjustWindowRect(&rc,uWindowstyle,FALSE);

			UINT uHeight = rc.bottom + rc.top;

			WINDOWPLACEMENT wc;

			GetWindowPlacement(GAMEWINDOW->GetHandle(),&wc);

			if (wc.showCmd == SW_MAXIMIZE)
			{
				iX = (iX * p->GetOld().uWidth) / GetSystemMetrics(SM_CXSCREEN);
				iY = (iY * p->GetOld().uHeight) / uHeight;
			}
		}

		MOUSEHANDLER->GetModel()->OnMouseMove(iX,iY);
		break;
	case WM_MOUSEWHEEL:
		MOUSEHANDLER->GetModel()->OnMouseScroll(GET_WHEEL_DELTA_WPARAM(wParam));
		break;
	case WM_LBUTTONDOWN:
		if (GetForegroundWindow() == m_hWnd)
		{
			MOUSEHANDLER->GetModel()->OnMouseClick(uMsg);
		}
		break;
	case WM_LBUTTONUP:
		if (GetForegroundWindow() == m_hWnd)
		{
			MOUSEHANDLER->GetModel()->OnMouseClick(uMsg);
		}
		break;
	case WM_RBUTTONDOWN:
		if (GetForegroundWindow() == m_hWnd)
		{
			MOUSEHANDLER->GetModel()->OnMouseClick(uMsg);
		}
		break;
	case WM_RBUTTONUP:
		if (GetForegroundWindow() == m_hWnd)
		{
			MOUSEHANDLER->GetModel()->OnMouseClick(uMsg);
		}
		break;
	case WM_CHAR:
		if (GetForegroundWindow() == m_hWnd)
		{
			KEYBOARDHANDLER->GetModel()->OnKeyChar(wParam);
		}
		break;
	case WM_KEYDOWN:
		if (GetForegroundWindow() == m_hWnd)
		{
			KEYBOARDHANDLER->GetModel()->OnKeyPass(wParam,TRUE);
		}
		break;
	case WM_KEYUP:
		if (GetForegroundWindow() == m_hWnd)
		{
			KEYBOARDHANDLER->GetModel()->OnKeyPass(wParam,FALSE);
		}
		break;
	default:
		return DefWindowProc(m_hWnd,uMsg,wParam,lParam);
	}

	return FALSE;
}
void CGAMEWINDOW::Loop()
{
	Update(m_pcTimer->Update());

	Render();

	if (Quit())
		m_bExit = TRUE;
}
void CGAMEWINDOW::Update(double fTime)
{
	static double fTick = (1000.0f / ((double)60));
	static double fOffs = 0.0f;

	fOffs += fTime;

	if (fOffs >= fTick)
	{
		do 
		{
			fOffs -= fTick;
		} 
		while (fOffs >= fTick);
	}

	if (fOffs < fTick)
		Sleep((DWORD)(fTick - fOffs));
}
void CGAMEWINDOW::Render()
{
	if (GRAPHICENGINE->CheckDevice())
	{
		GRAPHICENGINE->BeginScene(CAMERAHANDLE->GetViewMatrix());

		GRAPHICENGINE->EndScene();
	}
}
BOOL CGAMEWINDOW::Quit()
{
	return FALSE;
}