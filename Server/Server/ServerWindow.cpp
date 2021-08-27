#include "StdAfx.h"
#include "ServerWindow.h"

CServerWindow::CServerWindow() : CWindow()
{
	m_pcServer = new CServer;
	m_pcHandle = new CServerHandle;
}
CServerWindow::~CServerWindow()
{
	DELET(m_pcHandle);
	DELET(m_pcServer);
}
UINT CServerWindow::Init()
{
	if (!Register("Server", CS_HREDRAW | CS_VREDRAW, IDI_SERVER_ICON, (HBRUSH)(COLOR_WINDOW)))
	{
		WRITEDBG("Register() failed!\n\nGetLastError returned %d", GetLastError());
		return 0;
	}
	if (!MakeWindow("PT OnLine Server", TRUE, FALSE, FALSE, WINDOW_WIDTH, WINDOW_HEIGHT))
	{
		WRITEDBG("MakeWindow() failed!");
		return 0;
	}

	m_pcServer->Init(m_hWnd);
	m_pcServer->Load();
	m_pcHandle->Init();

	m_pcServer->Begin();

	m_bExit = FALSE;

	m_dwUpdateTimeInterval = 100;

	return 1;
}
void CServerWindow::Shutdown()
{
	m_bExit = TRUE;

	m_pcServer->End();

	m_pcServer->Shutdown();
	m_pcHandle->Shutdown();

	RemoveWindow();
	Unregister();
}
BOOL CServerWindow::Run()
{
	LoopWindowMessage();

	m_bExit = TRUE;

	return TRUE;
}
LRESULT CServerWindow::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		/* System Defined Message */
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_PAINT:
		Render();
		break;

		/* User Defined Messages */
	case WM_UPDATE:
		Update(*(double*)wParam);
		break;

	case WM_SOCKETACCEPT:
		SOCKETACCEPT((SOCKET)wParam, (sockaddr_in *)lParam);
		break;

	case WM_SOCKETPACKET:
		SOCKETPACKET((SocketData *)wParam, (PacketReceiving *)lParam);
		break;

	case WM_SOCKETCLOSE:
		SOCKETCLOSE((SocketData *)wParam);
		break;

		/* Unhandled Messages */
	default:
		return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
		break;
	}

	return FALSE;
}
void CServerWindow::Update(double fTime)
{
	static double fTick = (1000.0f / ((double)64));
	static double fOffs = 0.0f;

	SERVER_MUTEX->Lock(3000);

	//Split time into frames
	fOffs += fTime;
	if (fOffs >= fTick)
	{
		do
		{
			GSERVER->Loop();

			fOffs -= fTick;
		} while (fOffs >= fTick);
	}

	GSERVER->Update(fTime);

	SERVER_MUTEX->UnLock();
}
void CServerWindow::Render()
{
	static HFONT hFont = NULL;

	PAINTSTRUCT sPS;
	HDC hDC;
	RECT sRect;

	hDC = BeginPaint(m_hWnd, &sPS);

	if (hFont == NULL)
		hFont = CreateFontA(18, 0, 0, 0, FW_ULTRALIGHT, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FIXED_PITCH, "Arial");

	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(0, 0, 0));
	SelectObject(hDC, (HGDIOBJ)hFont);

	switch (SERVER_TYPE)
	{
	case SERVERTYPE_Login:
		sRect.left = 4;
		sRect.top = 6;
		sRect.right = WINDOW_WIDTH;
		sRect.bottom = sRect.top + 20;
		DrawTextA(hDC, "[Login Server] ONLINE!", -1, &sRect, DT_LEFT);
		break;
	case SERVERTYPE_Game:
		sRect.left = 4;
		sRect.top = 6;
		sRect.right = WINDOW_WIDTH;
		sRect.bottom = sRect.top + 20;
		DrawTextA(hDC, "[Game Server] ONLINE!", -1, &sRect, DT_LEFT);
		break;
	case SERVERTYPE_Multi:
		sRect.left = 4;
		sRect.top = 6;
		sRect.right = WINDOW_WIDTH;
		sRect.bottom = sRect.top + 20;
		DrawTextA(hDC, "[Multi Server] ONLINE!", -1, &sRect, DT_LEFT);
		break;
	default:
		sRect.left = 4;
		sRect.top = 6;
		sRect.right = WINDOW_WIDTH;
		sRect.bottom = sRect.top + 20;
		DrawTextA(hDC, "Loading Server...", -1, &sRect, DT_LEFT);
		break;
	};

	EndPaint(m_hWnd, &sPS);
}