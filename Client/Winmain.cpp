#include "StdAfx.h"
#define _SINBARAM

#include "smwsock.h"

#include "character.h"
#include "playmain.h"
#include "srcsound\\dxwav.h"
#include "effectsnd.h"
#include "fileread.h"
#include "netplay.h"
#include "makeshadow.h"

#include "particle.h"

#include "tjboy\\clanmenu\\tjclanDEF.h"
#include "tjboy\\clanmenu\\tjclan.h"
#include "tjboy\\clanmenu\\cE_CViewClanInfo.h"

#include "playsub.h"
#include "cracker.h"
#include "SkillSub.h"

#include "resource.h"

#include "TextMessage.h"
#include "damage.h"
#include "AreaServer.h"

#include "BellatraFontEffect.h"

#include "actiongame.h"


#define WM_CALLMEMMAP				WM_USER+3  

#ifdef PARKMENU
#include "TJBOY\\\\Park\\MICVOL\\MicVolume.h"
extern BOOL bMic;
extern int vrunRuning;
extern int micInit;
#endif

#include "WinInt\\WinIntThread.h"
#include "FullZoomMap.h"
#include "FontImage.h"

char *szAppName = "PT Online";

HWND hwnd;
HWND hTextWnd;
HWND hFocusWnd;

int quit = 0;
int QuitSave = 0;

float g_fWinSizeRatio_X;
float g_fWinSizeRatio_Y;

DWORD	dwM_BlurTime = 0;


int MouseButton[3] = { 0,0,0 };
extern int TJwheel;
extern int keydownEnt;

#pragma comment(lib, "imm32.lib")

#define DLLEXPORT __declspec(dllexport)

extern "C"
{
	DLLEXPORT int _stdcall InitD3D(HWND hWnd);
	DLLEXPORT void _stdcall CloseD3d();
	DLLEXPORT void _stdcall smPlayD3D(int x, int y, int z, int ax, int ay, int az);
}

#include "ime.h"

//ImeClass IMETest;
//CStrClass sz;
LRESULT CALLBACK EditWndProc01(HWND, UINT, WPARAM, LPARAM);
WNDPROC		OldEditProc01;
char szIME_Buff[10][64];

int MouseX, MouseY;
int MousemX, MousemY;
int angX = 0;
int angY = 0;
DWORD	dwLastMouseMoveTime;
DWORD	dwLastCharMoveTime;

int xPos, yPos;

POINT3D TraceCameraPosi;
POINT3D TraceTargetPosi;
int	PlayCameraMode = 1;
int AutoCameraFlag = FALSE;

int DisplayDebug = 0;
int DispInterface = TRUE;
int	DebugPlayer = FALSE;
int	LastAttackDamage = 0;

int	HoMsgBoxMode = 0;

#define TRADEBUTTONMAIN_X		513
#define TRADEBUTTONMAIN_Y		3


#define ANX_NONE	-32768

int pX;
int pY;
int pZ;
int	dpX = 0;
int dpY = 0;
int dpZ = 0;

int whAnx = 64;
int anx = 64;
int	ViewAnx = 64;
int	ViewDist = 100;
int	PlayFloor = 0;
int any = 0;
int anz = 0;
int dist = 100;
int CaTarDist = 0;
int	CaMovAngle = 0;

int tX = 0;
int tY = 0;
int tZ = 0;

int SetMousePlay(int flag);


int WaveCameraMode = TRUE;
POINT3D WaveCameraPosi;
int	WaveCameraFactor = 0;
int	WaveCameraTimeCount = 0;
int	WaveCameraDelay = 0;
BOOL	WaveCameraFlag = FALSE;


int GameInit();

int GameClose();

int	SetChatingLine(char *szMessage);


CRITICAL_SECTION	cDrawSection;

HINSTANCE hinst;

#define IDC_TEXT	101

BYTE VRKeyBuff[256];

float GetFPS();

LONG APIENTRY WndProc(HWND, UINT, WPARAM, LPARAM);

CRITICAL_SECTION	cSection;

HIMC hImc;
HIMC hImcEdit;

extern rsRECORD_DBASE	rsRecorder;

char	szCmdLine[128];

extern int RestoreBackupData(char *szListFile, char *BackupPath);

int DIsplayLogoImage();

CGame *g_lpGame = nullptr;

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wndclass;

	ZeroMemory(&wndclass, sizeof(WNDCLASSEX));

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEFAULT_ICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEFAULT_ICON));

	return RegisterClassEx(&wndclass);
}

HWND MyCreateWindow(UINT uWidth, UINT uHeight, BOOL bWindowMode)
{
	if (bWindowMode)
	{
		RECT r = { 0,0,(int)uWidth,(int)uHeight };

		DWORD dwStyle = WS_OVERLAPPEDWINDOW | WS_POPUP | WS_EX_TOPMOST;
		AdjustWindowRectEx(&r, dwStyle, NULL, NULL);

		int iWidth = r.right - r.left;
		int iHeight = r.bottom - r.top;

		return CreateWindowEx(NULL,
			szAppName,
			szAppName,
			dwStyle,
			(GetSystemMetrics(SM_CXSCREEN) >> 1) - (iWidth >> 1),
			(GetSystemMetrics(SM_CYSCREEN) >> 1) - (iHeight >> 1),
			iWidth,
			iHeight,
			NULL,
			NULL,
			GetModuleHandle(0),
			NULL);
	}

	return CreateWindowEx(NULL,
		szAppName,
		szAppName,
		WS_VISIBLE | WS_POPUP | WS_EX_TOPMOST,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		GetSystemMetrics(SM_CXSCREEN),
		GetSystemMetrics(SM_CYSCREEN),
		NULL,
		NULL,
		GetModuleHandle(0),
		NULL);
}

void GameUpdate(double fTime)
{
	static double fTick = (1000.0f / ((double)60));
	static double fOffs = 0.0f;

	//Split time into frames
	fOffs += fTime;
	if (fOffs >= fTick)
	{
		do
		{
			GAME->Frame();

			fOffs -= fTick;
		} while (fOffs >= fTick);
	}

	//Update
	GAME->Update((float)fTime);

	if (fOffs < fTick && GAMESCREEN->GetActiveScreenType() == SCREEN_Login)
		Sleep((DWORD)(fTick - fOffs));
}
void GameRender()
{
	if (GRAPHICENGINE->CheckDevice() == FALSE)
		return;

	GRAPHICENGINE->BeginScene(CAMERAHANDLE->GetViewMatrix());

	GAME->Render3D();
	GAME->Render2D();

	GRAPHICENGINE->EndScene();
}


INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPreInst, LPSTR lpCmdLine, INT nCmdShow)
{
	MSG msg;
	hinst = hInst;

	initSinCos();

	InitializeCriticalSection(&cSection);
	InitializeCriticalSection(&cDrawSection);
	InitializeCriticalSection(&cSection_Main);

	g_lpGame = new CGame;

	SETTINGHANDLE->Read();

	InitDirectSound();

	if (!hPreInst)
	{
		if (MyRegisterClass(hInst) == 0)
			return 0;
	}

	hwnd = MyCreateWindow(SETTINGHANDLE->Get().uWidth, SETTINGHANDLE->Get().uHeight, SETTINGHANDLE->Get().bWindowed);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	ShowCursor(FALSE);

	if (InitD3D(hwnd) == NULL)
		return FALSE;

	INIT(g_lpGame);

	CINFO::LPTIME g_Time;

	g_Time = GAMETIMEHANDLE;

	InitLoadingLamp(hwnd);

	hTextWnd = CreateWindow("EDIT", "", WS_CHILD | WS_BORDER | ES_LEFT | ES_MULTILINE | ES_WANTRETURN, 10, 400, 500, 40, hwnd, (HMENU)IDC_TEXT, hInst, NULL);

	OldEditProc01 = (WNDPROC)SetWindowLong(hTextWnd, GWL_WNDPROC, (LONG)EditWndProc01);

	hImc = ImmGetContext(hwnd);
	hImcEdit = ImmGetContext(hTextWnd);

	SetIME_Mode(0);

	GAMESOCKET->Init(hwnd);

	DIsplayLogoImage();

	GAMESCREEN->ChangeScreen(SCREEN_Login);

	CharacterName1[0] = 0;
	CharacterName2[0] = 0;

	SetTimer(hwnd, 0, GAME_WORLDTIME_MIN / 4, NULL);

	while (1)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);

			if (msg.message == WM_SYSKEYDOWN || msg.message == WM_SYSKEYUP)
			{
				if (msg.wParam != 0xF4 && msg.wParam != VK_F10)
					continue;
			}

			DispatchMessage(&msg);
		}
		else
		{
			EnterCriticalSection(&cSection_Main);

			GameUpdate(g_Time->Update());
			GameRender();

			LeaveCriticalSection(&cSection_Main);
		}

		if (quit != 0 && !dwTradeMaskTime)
		{
			if (GAMESCREEN->GetActiveScreenType() != SCREEN_World)
				break;

			if (!QuitSave)
			{
				if (cTrade.OpenFlag)
				{
					SendRequestTrade(cTrade.TradeCharCode, 3);
					cTrade.CancelTradeItem();
				}

				if (cWareHouse.OpenFlag)
					cWareHouse.RestoreInvenItem();

				if (cCaravan.OpenFlag)
					cCaravan.RestoreInvenItem();

				cInvenTory.ResetMouseItem();

				SaveGameData();
				QuitSave = TRUE;
			}
			else
			{
				if (!SOCKETG || GetSaveResult() == TRUE)
					break;

				if ((dwPlayTime - rsRecorder.dwRecordTime) > 15000)
					break;
			}
		}
	}

	GAMESCREEN->ChangeScreen(SCREEN_None);

	SHUTDOWN(g_lpGame);

	CloseLoadingLamp();

	CloseBindSock();

	CloseD3d();

	DELET(g_lpGame);

	return msg.wParam;
}

int msX = 0, msY = 0;
int msXo = 0, msYo = 0;
int xPs;
int yPs;

POINT	pCursorPos;

DWORD GameWindowMessage(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam);
DWORD dwTimerCount = 0;


BOOL DisplayIME = FALSE;

int SetIME_Mode(BOOL mode)
{
	if (mode)
	{
		DisplayIME = TRUE;
		ImmSetOpenStatus(hImc, TRUE);
		ImmSetConversionStatus(hImc, IME_CMODE_NATIVE | IME_CMODE_FULLSHAPE, IME_SMODE_PHRASEPREDICT);
		ImmSetConversionStatus(hImcEdit, IME_CMODE_NATIVE | IME_CMODE_FULLSHAPE, IME_SMODE_PHRASEPREDICT);
	}
	else
	{
		ImmSetConversionStatus(hImc, IME_CMODE_ALPHANUMERIC, IME_CMODE_ALPHANUMERIC);
		ImmSetConversionStatus(hImcEdit, IME_CMODE_ALPHANUMERIC, IME_CMODE_ALPHANUMERIC);

		ImmSetOpenStatus(hImc, FALSE);
		DisplayIME = FALSE;
	}
	return TRUE;
}
int CheckCode_2Byte(char *Str)
{
	if (Str[0] < 0)
		return 2;
	return 1;
}

LRESULT CALLBACK EditWndProc01(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	wmId = LOWORD(wParam);
	wmEvent = HIWORD(wParam);

	switch (message)
	{
	case WM_KEYDOWN:
		//IMETest.GetInfoPerTime();
		break;
	}
	return CallWindowProc(OldEditProc01, hWnd, message, wParam, lParam);
}

extern void clan_Mouse(int msg, WPARAM wParam);


LONG APIENTRY WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
{
	short zDelta;
	char strBuff[256];
	char strBuff2[256];
	char *lpString;
	int	len, CrCode;

	switch (messg)
	{
	case WM_CALLMEMMAP:
		void PacketParsing();
		PacketParsing();
		break;
	case WM_CREATE:
		break;

	case WM_CLOSE:
		QuitGame();
		break;

	case WSA_ACCEPT:
		WSAMessage_Accept(wParam, lParam);
		break;

	case WSA_READ:
		WSAMessage_Read(wParam, lParam);
		break;

	//case SWM_RECVSUCCESS:
		//RecvPlayData((smTHREADSOCK *)wParam);
		//break;
	case WM_SOCKETPACKET:
		GAMESOCKET->SocketPacket((SocketData*)wParam, (PacketReceiving*)lParam);

	case SWM_MCONNECT:
		break;
	case SWM_MDISCONNECT:
		((smWINSOCK *)wParam)->CloseSocket();
		break;
	case WM_KEYDOWN:
		if (GetForegroundWindow() != hWnd)
			return 0;
		if (KEYBOARDHANDLER->OnKeyPass(wParam, TRUE))
			return 0;
		if (g_IsDxProjectZoomIn > 0)
		{
			if (KeyFullZoomMap(wParam))
			{
				VRKeyBuff[wParam] = 1;
				break;
			}
			else
			{
				SetFullZoomMap(0);
				pCursorPos.x = g_iFzmCursorPosX;
				pCursorPos.y = g_iFzmCursorPosY;

				if (wParam == VK_ESCAPE)
					break;
			}
		}

		if (wParam == 0x47)
		{
			if (vrunRuning == TRUE)
			{
				if (bMic == FALSE)
				{
					if (micInit == 0)
						micInit = cmicvol.Init();
					bMic = TRUE;
					void ParkSetMicOnOFF();
					ParkSetMicOnOFF();
				}
			}
		}
		if (wParam == VK_RETURN)
			keydownEnt = 1;

		if (wParam == VK_CONTROL)
			VRKeyBuff[wParam] = 1;

		if (!hFocusWnd)
		{
			if (!VRKeyBuff[VK_SHIFT] && VRKeyBuff[VK_CONTROL] && !sinMessageBoxShowFlag && VRKeyBuff[wParam] == 0)
			{
				if (wParam == VK_F1 || wParam == VK_F2 || wParam == VK_F3 || wParam == VK_F4 || wParam == VK_F5 || wParam == VK_F6 || wParam == VK_F7 || wParam == VK_F8 || wParam == VK_F9 || wParam == VK_F10)
					SetChatingLine("");
			}
		}
		if (hFocusWnd)
		{
			lpString = 0;
			CrCode = 0;

			if (!VRKeyBuff[VK_SHIFT] && VRKeyBuff[VK_CONTROL] && !sinMessageBoxShowFlag)
			{
				if (wParam == VK_F1 && SETTINGHANDLE->Get().szMacro[0][0])
					lpString = SETTINGHANDLE->Get().szMacro[0];
				if (wParam == VK_F2 && SETTINGHANDLE->Get().szMacro[1][0])
					lpString = SETTINGHANDLE->Get().szMacro[1];
				if (wParam == VK_F3 && SETTINGHANDLE->Get().szMacro[2][0])
					lpString = SETTINGHANDLE->Get().szMacro[2];
				if (wParam == VK_F4 && SETTINGHANDLE->Get().szMacro[3][0])
					lpString = SETTINGHANDLE->Get().szMacro[3];
				if (wParam == VK_F5 && SETTINGHANDLE->Get().szMacro[4][0])
					lpString = SETTINGHANDLE->Get().szMacro[4];
				if (wParam == VK_F6 && SETTINGHANDLE->Get().szMacro[5][0])
					lpString = SETTINGHANDLE->Get().szMacro[5];
				if (wParam == VK_F7 && SETTINGHANDLE->Get().szMacro[6][0])
					lpString = SETTINGHANDLE->Get().szMacro[6];
				if (wParam == VK_F8 && SETTINGHANDLE->Get().szMacro[7][0])
					lpString = SETTINGHANDLE->Get().szMacro[7];
				if (wParam == VK_F9 && SETTINGHANDLE->Get().szMacro[8][0])
					lpString = SETTINGHANDLE->Get().szMacro[8];
				if (wParam == VK_F10 && SETTINGHANDLE->Get().szMacro[9][0])
					lpString = SETTINGHANDLE->Get().szMacro[9];

				if (lpString)
				{
					GetWindowText(hFocusWnd, strBuff2, 90);
					len = lstrlen(strBuff2) + lstrlen(lpString);
					if (len < 80)
					{
						lstrcat(strBuff2, lpString);
						if (strBuff2[len - 1] == 0x0D)
						{
							len--;
							strBuff2[len] = 0;
							CrCode = TRUE;
						}
						SetWindowText(hFocusWnd, strBuff2);
						SendMessage(hFocusWnd, EM_SETSEL, len, len);
					}
				}
			}
			if (!sinMessageBoxShowFlag && ((wParam == VK_RETURN && VRKeyBuff[wParam] == 0 && !VRKeyBuff[VK_CONTROL]) || CrCode == TRUE))
			{
				{
					GetWindowText(hFocusWnd, strBuff2, 90);

					if (GAMESCREEN->GetActiveScreenType() == SCREEN_World)
						cHelpPet.PetOnOff(strBuff2);

					if (strBuff2[0])
					{
						if (strBuff2[0] == '/' || (SETTINGHANDLE->Get().bDebugMode && strBuff2[0] == '~') || strBuff2[0] == '`' || strBuff2[0] == '@')
							wsprintf(strBuff, "%s", strBuff2);
						else
						{

						}

						if (GAMESCREEN->GetActiveScreenType() == SCREEN_World)
						{
							if (chatlistSPEAKERflag() && lstrlen(strBuff) > LastWhisperLen)
							{
								SetClanChatting();

								if (szLastWhisperName[0])
									szLastWhisperName[0] = 0;
							}
							else
							{
								if (szLastWhisperName[0] && lstrlen(strBuff) > LastWhisperLen)
									WhisperPartyPlayer(szLastWhisperName);
								else
								{
									SetWindowText(hFocusWnd, "");
									szLastWhisperName[0] = 0;
									LastWhisperLen = 0;
									InterfaceParty.chat_WhisperPartyPlayer_close();
									chatlistSPEAKERflagChg(0);
								}
							}
						}
						else
							hFocusWnd = 0;
					}
					else
					{
						hFocusWnd = 0;

						if (GAMESCREEN->GetActiveScreenType() == SCREEN_World)
						{
							szLastWhisperName[0] = 0;
							LastWhisperLen = 0;
							InterfaceParty.chat_WhisperPartyPlayer_close();
							chatlistSPEAKERflagChg(0);
						}
					}
				}
			}
			if (GAMESCREEN->GetActiveScreenType() == SCREEN_World)
			{
				if (wParam == VK_TAB && VRKeyBuff[wParam] == 0)
				{
					IsClanChatting();
					break;
				}
				if (wParam == VK_UP && VRKeyBuff[wParam] == 0 && !LastWhisperLen)
				{
					RecallSavedChatCommand(hFocusWnd, 1);
					break;
				}
				if (wParam == VK_DOWN && VRKeyBuff[wParam] == 0 && !LastWhisperLen)
				{
					RecallSavedChatCommand(hFocusWnd, 0);
					break;
				}
				if (wParam == VK_ESCAPE && VRKeyBuff[wParam] == 0)
				{
					if (SendMessage(hTextWnd, EM_GETLIMITTEXT, 78, 0) >= 78)
					{
						hFocusWnd = 0;
						szLastWhisperName[0] = 0;
						LastWhisperLen = 0;
						InterfaceParty.chat_WhisperPartyPlayer_close();
						chatlistSPEAKERflagChg(0);
					}
				}
			}
			//SendMessage(hFocusWnd, messg, wParam, lParam);
			break;
		}

		if (wParam == VK_ESCAPE && VRKeyBuff[wParam] == 0)
		{
			if (VRKeyBuff[VK_SHIFT])
				QuitGame();
			else
			{
				if (cInvenTory.OpenFlag || cCharStatus.OpenFlag || cSkill.OpenFlag || ExitButtonClick)
					cInterFace.CheckAllBox(SIN_ALL_CLOSE);
				else
				{
					if (InterfaceParty.PartyPosState == PARTY_PROCESS)
					{
						InterfaceParty.PartyPosState = PARTY_END;
						InterfaceParty.qN_Pressf_CLEAR();
					}
					else
						ExitButtonClick = 1;
				}
			}
		}

		if (GAMESCREEN->GetActiveScreenType() == SCREEN_World)
		{
			if (GameWindowMessage(hWnd, messg, wParam, lParam) == FALSE)
				break;
		}
		if (GAMESCREEN->GetActiveScreenType() == SCREEN_World &&
			lpCurPlayer->iLoadedMapIndex >= 0 &&
			STAGE_MAP[lpCurPlayer->iLoadedMapIndex] &&
			STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapType == MAPTYPE_ChessRoom)
		{

		}
		else
		{
			if (wParam == VK_HOME && VRKeyBuff[wParam] == 0 && VRKeyBuff[VK_CONTROL])
			{
				if (GAMESCREEN->GetActiveScreenType() == SCREEN_World)
					Capture();
			}
		}

		VRKeyBuff[wParam] = 1;
		clan_Mouse(WM_KEYDOWN, wParam);
		break;
	case WM_KEYUP:
		if (GetForegroundWindow() != hWnd)
			return 0;
		if (KEYBOARDHANDLER->OnKeyPass(wParam, FALSE))
			return 0;
		if (g_IsDxProjectZoomIn > 0)
		{
			if (KeyFullZoomMap(wParam))
			{
				VRKeyBuff[wParam] = 0;
				break;
			}
		}
		if (wParam == 0x47)
		{
			if (vrunRuning == TRUE)
			{
				if (bMic == TRUE)
				{
					bMic = FALSE;
					void ParkSetMicOnOFF();
					ParkSetMicOnOFF();
				}
			}
		}
		if (hFocusWnd)
			SendMessage(hFocusWnd, messg, wParam, lParam);

		VRKeyBuff[wParam] = 0;
		clan_Mouse(WM_KEYUP, wParam);
		break;
	case WM_SYSKEYDOWN:
		if (wParam == VK_F10)
		{
			PostMessage(hWnd, WM_KEYDOWN, wParam, lParam);
			return FALSE;
		}
		if (hFocusWnd)
			SendMessage(hFocusWnd, messg, wParam, lParam);
		break;

	case WM_SYSKEYUP:
		if (GetForegroundWindow() != hWnd)
			return 0;
		if (KEYBOARDHANDLER->OnKeyPass(wParam, FALSE))
			return 0;
		if (wParam == VK_F10)
		{
			PostMessage(hWnd, WM_KEYUP, wParam, lParam);
			return FALSE;
		}
		if (hFocusWnd)
			SendMessage(hFocusWnd, messg, wParam, lParam);
		break;

	case WM_MOUSEMOVE:
		int iX;
		iX = (int)round(LOWORD(lParam));
		int iY;
		iY = (int)round(HIWORD(lParam));

		if (SETTINGHANDLE->Get().bWindowed && SETTINGHANDLE->Get().bAutoAdjust == FALSE)
		{
			RECT rc;
			rc.left = 0;
			rc.top = 0;
			rc.right = SETTINGHANDLE->GetOld().uWidth;
			rc.bottom = SETTINGHANDLE->GetOld().uHeight;
			GetWindowRect(hWnd, &rc);

			UINT uWindowStyle = GetWindowLongA(hWnd, GWL_STYLE);

			// Adjust Window
			AdjustWindowRect(&rc, uWindowStyle, FALSE);
			DWORD dwHeight = (rc.bottom + rc.top);

			WINDOWPLACEMENT wc;

			GetWindowPlacement(hWnd, &wc);

			if (wc.showCmd == SW_MAXIMIZE)
			{
				iX = (iX * SETTINGHANDLE->GetOld().uWidth) / GetSystemMetrics(SM_CXSCREEN);
				iY = (iY * SETTINGHANDLE->GetOld().uHeight) / dwHeight;
			}
		}

		MOUSEHANDLER->OnMouseMove(iX, iY);

		if (g_IsDxProjectZoomIn)
		{
			g_iFzmCursorPosX = iX;
			g_iFzmCursorPosY = iY;

			if (g_iFzmCursorPosX > 30 * g_fWinSizeRatio_X && g_iFzmCursorPosX < 350 * g_fWinSizeRatio_X && g_iFzmCursorPosY > 338 * g_fWinSizeRatio_Y && g_iFzmCursorPosY < 578 * g_fWinSizeRatio_Y)
			{
				if (g_iFzmCursorFocusGame == 0)
				{
					g_iFzmCursorFocusGame = 1;

					xPs = pCursorPos.x = msXo = int(((float)g_iFzmCursorPosX - g_fZoomInAdd_x) * g_fZoomInDiv_x);
					yPs = pCursorPos.y = msYo = int(((float)g_iFzmCursorPosY - g_fZoomInAdd_y) * g_fZoomInDiv_y);
				}

				xPs = int(((float)g_iFzmCursorPosX - g_fZoomInAdd_x) * g_fZoomInDiv_x);
				yPs = int(((float)g_iFzmCursorPosY - g_fZoomInAdd_y) * g_fZoomInDiv_y);

				pCursorPos.x = xPs;
				pCursorPos.y = yPs;

				msX = msXo - xPs;
				msY = msYo - yPs;

				msXo = xPs;
				msYo = yPs;

				if ((wParam & MK_MBUTTON))
					SetMousePlay(3);
				else
				{
					if (wParam == MK_LBUTTON || TraceMode_DblClick)
						SetMousePlay(2);
					else if (wParam == MK_RBUTTON)
						SetMousePlay(4);
				}
				dwLastMouseMoveTime = dwPlayTime;
			}
			else
				g_iFzmCursorFocusGame = 0;
		}
		else
		{
			xPs = iX;
			yPs = iY;

			g_iFzmCursorPosX = pCursorPos.x = xPs;
			g_iFzmCursorPosY = pCursorPos.y = yPs;
			msX = msXo - xPs;
			msY = msYo - yPs;

			msXo = xPs;
			msYo = yPs;

			if ((wParam&MK_MBUTTON))
				SetMousePlay(3);
			else
			{
				if (wParam == MK_LBUTTON || TraceMode_DblClick)
					SetMousePlay(2);
				else
				{
					if (wParam == MK_RBUTTON)
						SetMousePlay(4);
				}
			}
		}
		dwLastMouseMoveTime = dwPlayTime;
		break;
	case WM_LBUTTONDBLCLK:
		MouseDblClick = TRUE;
		if (GAMESCREEN->GetActiveScreenType() == SCREEN_World)
		{
			if (GetFieldMapCursor() == TRUE && cInterFace.sInterFlags.MapOnFlag)
				sinCheck_ShowHelpMap();

			sinDoubleClick();

			dsMenuCursorPos(&pCursorPos, 2);
			if (StopCharMotion(pCursorPos.x, pCursorPos.y) != TRUE)
			{
				Moving_DblClick = TRUE;
				MousePos_DblClick.x = xPs;
				MousePos_DblClick.y = yPs;
				MousePos_DblClick.z = 0;
			}
			dsMenuCursorPos(&pCursorPos, 0);
		}
		break;
	case WM_LBUTTONDOWN:
		if (GetForegroundWindow() != hWnd)
			return 0;
		if (MOUSEHANDLER->OnMouseClick(messg))
			return 0;

		if (g_IsDxProjectZoomIn <= 0 || g_iFzmCursorFocusGame)
		{
			SetMousePlay(1);
			sinLButtonDown();
			MouseButton[0] = TRUE;
			clan_Mouse(WM_LBUTTONDOWN, wParam);
		}
		else
			g_FzmMouseButton[0] = TRUE;

		if (GAMESCREEN->GetActiveScreenType() == SCREEN_World && GAMESOCKET->iDisconnectTime)
			quit = TRUE;
		break;
	case WM_LBUTTONUP:
		if (GetForegroundWindow() != hWnd)
			return 0;
		if (MOUSEHANDLER->OnMouseClick(messg))
			return 0;

		if (g_IsDxProjectZoomIn <= 0 || g_iFzmCursorFocusGame || MouseButton[0])
		{
			SetMousePlay(0);
			sinLButtonUp();

			MouseButton[0] = FALSE;
			MouseDblClick = FALSE;
			clan_Mouse(WM_LBUTTONUP, wParam);
		}
		else
		{
			MouseDblClick = FALSE;
			g_FzmMouseButton[0] = FALSE;
		}
		break;
	case WM_RBUTTONDOWN:
		if (GetForegroundWindow() != hWnd)
			return 0;
		if (MOUSEHANDLER->OnMouseClick(messg))
			return 0;
		if (g_IsDxProjectZoomIn <= 0 || g_iFzmCursorFocusGame)
		{
			SetMousePlay(11);
			MouseButton[1] = TRUE;
			clan_Mouse(WM_RBUTTONDOWN, wParam);
		}
		else
			g_FzmMouseButton[1] = TRUE;
		break;
	case WM_RBUTTONUP:
		if (GetForegroundWindow() != hWnd)
			return 0;
		if (MOUSEHANDLER->OnMouseClick(messg))
			return 0;
		if (g_IsDxProjectZoomIn <= 0 || g_iFzmCursorFocusGame)
		{
			SetMousePlay(10);
			sinRButtonUp();
			MouseButton[1] = FALSE;
			clan_Mouse(WM_RBUTTONUP, wParam);
		}
		else
			g_FzmMouseButton[1] = FALSE;
		break;
	case WM_MBUTTONDOWN:
		if (g_IsDxProjectZoomIn <= 0 || g_iFzmCursorFocusGame)
		{
			MouseButton[2] = TRUE;
			clan_Mouse(WM_MBUTTONDOWN, wParam);
		}
		else
			g_FzmMouseButton[2] = TRUE;
		break;

	case WM_MBUTTONUP:
		if (g_IsDxProjectZoomIn <= 0 || g_iFzmCursorFocusGame)
		{
			MouseButton[2] = FALSE;
			clan_Mouse(WM_MBUTTONUP, wParam);
		}
		else
			g_FzmMouseButton[2] = FALSE;
		break;
	case WM_MOUSEWHEEL:
		if (GetForegroundWindow() != hWnd)
			return 0;
		if (MOUSEHANDLER->OnMouseScroll(GET_WHEEL_DELTA_WPARAM(wParam)))
			return 0;
		if (g_IsDxProjectZoomIn <= 0 || g_iFzmCursorFocusGame)
		{
			zDelta = (short)HIWORD(wParam);

			if (cSinHelp.sinGetScrollMove(-zDelta / 16) == TRUE)
				break;
			if (TJBscrollWheel(zDelta) == TRUE)
				break;
			if (whAnx == ANX_NONE)
				whAnx = anx + zDelta;
			else
				whAnx += zDelta;

			AutoCameraFlag = FALSE;
		}
		break;

	case WM_CHAR:
		if (GetForegroundWindow() != hWnd)
			return 0;
		if (KEYBOARDHANDLER->OnKeyChar(wParam))
			return 0;
		if (wParam == 0x0D || wParam == 0x0A || (GAMESCREEN->GetActiveScreenType() == SCREEN_World && wParam == VK_TAB))
			return TRUE;

		if (!SETTINGHANDLE->Get().bDebugMode && wParam == 22 && lpCurPlayer->szMessage[0])
			return TRUE;
		//if (hFocusWnd)
			//SendMessage(hFocusWnd, messg, wParam, lParam);
	//case WM_SYSCHAR:
	case WM_IME_CHAR:
	//case WM_IME_COMPOSITION:
		if (GetForegroundWindow() != hWnd)
			return 0;
		if (KEYBOARDHANDLER->OnKeyChar(wParam))
			return 0;
		if (g_IsDxProjectZoomIn > 0)
			break;
		if (hFocusWnd)
			SendMessage(hFocusWnd, messg, wParam, lParam);
		break;

	case WM_KILLFOCUS:
		SetFocus(hWnd);
		return TRUE;

	case WM_COMMAND:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_ACTIVATE:
		break;

	case WM_NCACTIVATE:
		if (GAMESCREEN->GetActiveScreenType() == SCREEN_World && lpCurPlayer->iID)
		{
			CheckCharForm();
		}
		break;
	case WM_TIMER:
		if ((dwTimerCount & 3) == 0)
		{
			DWORD dwTime = GAMEMAP->GetGameTime();

			dwTime++;

			GAMEMAP->UpdateGameTime(dwTime);
		}

		dwTimerCount++;
		break;
	case WM_NPROTECT_EXIT_TWO:
		GAMESOCKET->iDisconnectType = 4;
		GAMESOCKET->iDisconnectTime = TICKCOUNT;
		break;
	case WM_NPROTECT_SPEEDHACK:
	case WM_NPROTECT_SH_ERROR:
	case WM_NPROTECT_SOFTICE:
		GAMESOCKET->iDisconnectType = 4;
		GAMESOCKET->iDisconnectTime = TICKCOUNT;
		quit = 1;
		break;
	default:
		return DefWindowProc(hWnd, messg, wParam, lParam);
		break;

	}
	return 0L;
}

int MoveAngle(int step, int angY)
{
	int x, z;

	x = ((pX << 16) + GetSin[angY&ANGLE_MASK] * step) >> 16;
	z = ((pZ << 16) + GetCos[angY&ANGLE_MASK] * step) >> 16;

	pX = x;
	pZ = z;

	return TRUE;
}

#define CAMERA_MOVE_STEP		(8*fONE)

int TraceCameraMain()
{
	if (TraceCameraPosi.x < TraceTargetPosi.x)
	{
		TraceCameraPosi.x += CAMERA_MOVE_STEP;

		if (TraceCameraPosi.x > TraceTargetPosi.x)
			TraceCameraPosi.x = TraceTargetPosi.x;
	}
	if (TraceCameraPosi.x > TraceTargetPosi.x)
	{
		TraceCameraPosi.x -= CAMERA_MOVE_STEP;

		if (TraceCameraPosi.x < TraceTargetPosi.x)
			TraceCameraPosi.x = TraceTargetPosi.x;
	}
	if (TraceCameraPosi.y < TraceTargetPosi.y)
	{
		TraceCameraPosi.y += CAMERA_MOVE_STEP;
		if (TraceCameraPosi.y > TraceTargetPosi.y)
			TraceCameraPosi.y = TraceTargetPosi.y;
	}
	if (TraceCameraPosi.y > TraceTargetPosi.y)
	{
		TraceCameraPosi.y -= CAMERA_MOVE_STEP / 2;

		if (TraceCameraPosi.y < TraceTargetPosi.y)
			TraceCameraPosi.y = TraceTargetPosi.y;
	}
	if (TraceCameraPosi.z < TraceTargetPosi.z)
	{
		TraceCameraPosi.z += CAMERA_MOVE_STEP;

		if (TraceCameraPosi.z > TraceTargetPosi.z)
			TraceCameraPosi.z = TraceTargetPosi.z;
	}
	if (TraceCameraPosi.z > TraceTargetPosi.z)
	{
		TraceCameraPosi.z -= CAMERA_MOVE_STEP;

		if (TraceCameraPosi.z < TraceTargetPosi.z)
			TraceCameraPosi.z = TraceTargetPosi.z;
	}

	return TRUE;
}


int RendSightPos = 0;
int RendSightOffset = 0;

int SetRendSight()
{
	if (smRender.m_GameFieldView)
	{
		ViewPointLen = 38 * SizeMAPCELL + RendSightPos;
		ccDistZMin = ViewPointLen - (20 * SizeMAPCELL + RendSightPos / 4);

		return TRUE;
	}

	return FALSE;
}

int RendSightSub(int flag)
{
	if (lpCurPlayer->iLoadedMapIndex >= 0 && STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iSight)
		RendSightOffset = STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iSight * SizeMAPCELL;
	else
	{
		RendSightOffset = smRender.m_GameFieldViewStep * SizeMAPCELL;

		if (flag)
			RendSightPos = RendSightOffset;
	}

	if (RendSightPos < RendSightOffset)
		RendSightPos += 4;
	else
		if (RendSightPos > RendSightOffset)
			RendSightPos -= 4;

	return TRUE;
}


#define	FPS_TIME		(1000/70)

//DWORD FrameSkipTimer = 0;
//int fps = 70;
//int FpsTime;

#define AC_MOVE_STEP	4
#define AC_MOVE_MIN		256


int dsCameraRotation = 0;

void PlayMain()
{
	int mv;

	if (ActionGameMode)

		ActionGameMain();

	else if (cSinHelp.sinGetHelpShowFlag() != TRUE)
	{
		if (SETTINGHANDLE->Get().bInvertedCamera)
		{
			if (VRKeyBuff[VK_RIGHT])
			{
				any += 16;
				AutoCameraFlag = FALSE;
			}
			if (VRKeyBuff[VK_LEFT])
			{
				any -= 16;
				AutoCameraFlag = FALSE;
			}
		}
		else
		{
			if (VRKeyBuff[VK_RIGHT])
			{
				any -= 16;
				AutoCameraFlag = FALSE;
			}
			if (VRKeyBuff[VK_LEFT])
			{
				any += 16;
				AutoCameraFlag = FALSE;
			}
		}
		if (VRKeyBuff[VK_CONTROL])
		{
			if (VRKeyBuff[VK_UP])
			{
				anx -= 16;
				AutoCameraFlag = FALSE;
			}
			if (VRKeyBuff[VK_DOWN])
			{
				anx += 16;
				AutoCameraFlag = FALSE;
			}
		}
		else
		{
			if (VRKeyBuff[VK_UP])
			{
				dist -= 8;

				if (dist < 100)
				{
					if (anx <= 40)
						if (dist < 40)
							dist = 40;
						else
							dist = 100;

					CaTarDist = 0;
				}
			}

			if (VRKeyBuff[VK_DOWN])
			{
				dist += 8;

				if (dist > 440)
				{
					dist = 440;
					CaTarDist = 0;
				}
			}
		}
		if (VRKeyBuff[VK_NEXT])
		{
			anx -= 16;
			AutoCameraFlag = FALSE;
		}
		if (VRKeyBuff[VK_PRIOR])
		{
			anx += 16;
			AutoCameraFlag = FALSE;
		}
	}

	if (cInterFace.sInterFlags.CameraAutoFlag != 2)
	{
		if (pCursorPos.x >= 8 && pCursorPos.x <= (int)RESOLUTION_WIDTH - 8)
			dsCameraRotation = 0;

		if (pCursorPos.x < 8)
		{
			if (!dsCameraRotation)
				dsCameraRotation = -512;

			mv = dsCameraRotation / 16;

			if (mv < -16)
				mv = -16;

			any += mv;
			dsCameraRotation++;

			if (dsCameraRotation >= 0)
			{
				dsCameraRotation = 0;
				pCursorPos.x = 8;
			}

			AutoCameraFlag = FALSE;
		}
		if (pCursorPos.x > (int)RESOLUTION_WIDTH - 8)
		{
			if (!dsCameraRotation)
				dsCameraRotation = 512;

			mv = dsCameraRotation / 16;

			if (mv > 16)
				mv = 16;

			any += mv;
			dsCameraRotation--;

			if (dsCameraRotation <= 0)
			{
				dsCameraRotation = 0;
				pCursorPos.x = (int)RESOLUTION_WIDTH - 8;
			}

			AutoCameraFlag = FALSE;
		}
	}

	if (CaTarDist)
	{
		if (dist < CaTarDist)
		{
			dist += 12;

			if (dist >= CaTarDist)
			{
				dist = CaTarDist;
				CaTarDist = 0;
			}
		}
		else
		{
			if (dist > CaTarDist)
			{
				dist -= 12;

				if (dist <= CaTarDist)
				{
					dist = CaTarDist;
					CaTarDist = 0;
				}
			}
		}
	}

	if (CaMovAngle)
	{
		mv = CaMovAngle >> 4;

		if (CaMovAngle > 0)
		{
			if (mv > 32)
				mv = 32;

			any += mv; CaMovAngle -= mv;

			if (CaMovAngle < 0)
				CaMovAngle = 0;
		}
		else
		{
			if (mv < -32)
				mv = -32;

			any += mv; CaMovAngle -= mv;

			if (CaMovAngle > 0)
				CaMovAngle = 0;
		}
		if (mv == 0)
			CaMovAngle = 0;

		if (CaMovAngle == 0)
			AutoCameraFlag = TRUE;
		else
			AutoCameraFlag = FALSE;
	}
	if (whAnx != ANX_NONE)
	{
		if (anx < whAnx)
		{
			anx += 8;

			if (anx >= whAnx)
			{
				whAnx = ANX_NONE;
				AutoCameraFlag = TRUE;
			}
		}
		else
		{
			anx -= 8;

			if (anx <= whAnx)
			{
				whAnx = ANX_NONE;
				AutoCameraFlag = TRUE;
			}
		}
	}
	if (PlayFloor > 0)
	{
		if (ViewAnx < 500)
			ViewAnx += 8;

		if (ViewDist > 250)
			ViewDist -= 8;

		PlayFloor--;
	}
	else
	{
		if (ViewAnx < anx)
		{
			ViewAnx += 8;
			if (ViewAnx > anx)
				ViewAnx = anx;
		}
		if (ViewAnx > anx)
		{
			ViewAnx -= 8;
			if (ViewAnx < anx)
				ViewAnx = anx;
		}

		if (CaTarDist)
			mv = 100;
		else
			mv = 8;

		if (ViewDist < dist)
		{
			ViewDist += mv;

			if (ViewDist > dist)
				ViewDist = dist;
		}
		if (ViewDist > dist)
		{
			ViewDist -= mv;

			if (ViewDist < dist)
				ViewDist = dist;
		}
	}

	if (DebugPlayer)
	{
		if (dpX == 0 && dpZ == 0)
		{
			dpX = lpCurPlayer->pX;
			dpY = lpCurPlayer->pY;
			dpZ = lpCurPlayer->pZ;
		}
		if (VRKeyBuff[VK_SPACE])
		{
			auto sPosition = GetMoveLocation(0, 0, fONE * 2, anx, any, 0);
			dpX += sPosition.iX;
			dpY += sPosition.iY;
			dpZ += sPosition.iZ;
		}

		if (VRKeyBuff['Z'])
			anz -= 8;
		if (VRKeyBuff['X'])
			anz += 8;

		lpCurPlayer->pX = dpX;
		lpCurPlayer->pZ = dpZ;

		anx &= ANGCLIP;

		if (anx >= ANGLE_90 && anx < ANGLE_270)
		{
			if (anx < ANGLE_180)
				anx = ANGLE_90 - 32;
			else
				anx = ANGLE_270 + 32;
		}

		ViewAnx = anx;
		whAnx = ANX_NONE;
	}
	else
	{
		if (anx >= (ANGLE_90 - 48))
		{
			anx = (ANGLE_90 - 48);
			whAnx = ANX_NONE;
		}
		if (anx < 40)
		{
			anx = 40;
			whAnx = ANX_NONE;
		}
	}

	if (anx > 40 && dist < 100)
	{
		dist = 100;
		CaTarDist = 0;
	}
	if (dist > 440)
	{
		dist = 440;
		CaTarDist = 0;
	}

	int ay;
	int astep;

	if (PlayCameraMode != cInterFace.sInterFlags.CameraAutoFlag)
	{
		if (cInterFace.sInterFlags.CameraAutoFlag == 2)
			any = ANGLE_45;
		PlayCameraMode = cInterFace.sInterFlags.CameraAutoFlag;
	}

	if (PlayCameraMode == 1 && AutoCameraFlag && any != lpCurPlayer->Angle.y && lpCurPlayer->MoveFlag)
	{
		ay = (any - lpCurPlayer->Angle.y) & ANGCLIP;

		if (ay >= ANGLE_180)
			ay = ay - ANGLE_360;

		if (abs(ay) < (ANGLE_90 + 180))
		{

			if (ay < 0)
			{
				astep = abs(ay) >> 6;

				if (astep < AC_MOVE_STEP) astep = AC_MOVE_STEP;

				if (ay < -AC_MOVE_MIN)
				{
					ay += astep;
					if (ay > 0)
						any = lpCurPlayer->Angle.y;
					else
						any = (any + astep) & ANGCLIP;
				}
			}
			else
			{
				astep = abs(ay) >> 6;

				if (astep < AC_MOVE_STEP)
					astep = AC_MOVE_STEP;

				if (ay > AC_MOVE_MIN)
				{
					ay -= astep;

					if (ay < 0)
						any = lpCurPlayer->Angle.y;
					else
						any = (any - astep) & ANGCLIP;
				}
			}
		}
	}
	GAMESOCKET->Loop();

	PlayPat3D();

	MainEffect();

	if (g_IsDxProjectZoomIn)
		MainFullZoomMap();

	dwMemError = dwMemError ^ dwPlayTime;
	dwPlayTime = GetCurrentTime();
	dwMemError = dwMemError ^ dwPlayTime;

	TraceCameraMain();

	RendSightSub(0);
}

POINT3D TargetPosi = { 0,0,0 };
POINT3D GeoResult = { 0,0,0 };

int timeg = 0;
int RenderCnt = 0;
int DispRender;
int	DispMainLoop;

//DWORD	dwLastPlayTime = 0;
//DWORD	dwLastOverSpeedCount = 0;
int		PlayTimerMax = 0;
int		MainLoopCount = 0;
DWORD	dwLastRenderTime = 0;

void PlayFrame()
{
	PlayMain();
	if (g_IsDxProjectZoomIn <= 0)
	{
		dsMenuCursorPos(&pCursorPos, 1);
		sinMain();
		dsMenuCursorPos(&pCursorPos, 0);

		MainInterfaceParty(TRADEBUTTONMAIN_X, TRADEBUTTONMAIN_Y);
	}
	else
		MainSub();

	if (BellatraEffectInitFlag)
		MainBellatraFontEffect();
}

void PlayDraw()
{
	if (!CURSORHANDLE->IsOpen())
		CURSORHANDLE->Show();

	if (PlayCameraMode == 2)
	{
		dist = 400;
		anx = ANGLE_45 - 128;
		ViewAnx = anx;
		ViewDist = dist;
	}

	any &= ANGCLIP;
	anx &= ANGCLIP;

	if (WaveCameraFlag && SETTINGHANDLE->Get().bNoCameraWave == FALSE)
	{
		WaveCameraTimeCount++;

		if ((WaveCameraTimeCount > WaveCameraDelay))
		{
			WaveCameraTimeCount = 0;
			if (WaveCameraDelay > 1 && WaveCameraFactor < 40)
				WaveCameraFactor = -int((float)WaveCameraFactor / 10.f*9.f);
			else
				WaveCameraFactor = -int((float)WaveCameraFactor / 10.f*8.f);
			ViewDist += WaveCameraFactor;
		}

		if (abs(WaveCameraFactor) < 1)
		{
			WaveCameraFlag = FALSE;
			WaveCameraTimeCount = 0;
		}
	}
	else
		WaveCameraFlag = FALSE;

	Point3D sPosition;

	sPosition = GetMoveLocation(0, 0, -(ViewDist << FLOATNS), ViewAnx&ANGCLIP, any, 0);

	if (sPosition.iX == GeoResult.x && sPosition.iY == GeoResult.y && sPosition.iZ == GeoResult.z)
	{
		pX += lpCurPlayer->pX - TargetPosi.x;
		pY += lpCurPlayer->pY - TargetPosi.y;
		pZ += lpCurPlayer->pZ - TargetPosi.z;
	}
	else
	{
		pX = lpCurPlayer->pX;
		pY = lpCurPlayer->pY;
		pZ = lpCurPlayer->pZ;

		pX += sPosition.iX;
		pY += sPosition.iY;
		pZ += sPosition.iZ;

		GeoResult.x = sPosition.iX;
		GeoResult.y = sPosition.iY;
		GeoResult.z = sPosition.iZ;
	}

	TargetPosi.x = lpCurPlayer->pX;
	TargetPosi.y = lpCurPlayer->pY;
	TargetPosi.z = lpCurPlayer->pZ;


	if (DebugPlayer)
	{
		lpCurPlayer->Angle.y = any;

		pX = dpX;
		pY = dpY;
		pZ = dpZ;

		any = lpCurPlayer->Angle.y;
	}
	else
		anz = 0;

	if (SETTINGHANDLE->Get().bDebugMode && VRKeyBuff[VK_SHIFT])
	{
		if (VRKeyBuff[VK_HOME])
			DarkLevel = 220;
		if (VRKeyBuff[VK_END])
			DarkLevel = 0;
	}

	LockSpeedProtect(lpCurPlayer);

	EnterCriticalSection(&cDrawSection);
	smEnterTextureCriticalSection();


	DWORD	dwSkilChkSum = 0;
	DWORD	dwChkSum;
	DWORD	dwLevelQuestSum;
	int		cnt, k;

	for (cnt = 0; cnt < SIN_MAX_USE_SKILL; cnt++)
	{
		k = (cnt + 5) << 2;
		dwSkilChkSum += sinSkill.UseSkill[cnt].UseSkillCount*k;
		dwSkilChkSum += sinSkill.UseSkill[cnt].Point*k;
		dwSkilChkSum += sinSkill.UseSkill[cnt].Mastery*k;
		dwSkilChkSum += sinSkill.UseSkill[cnt].GageLength*k;
		dwSkilChkSum += sinSkill.UseSkill[cnt].Skill_Info.UseStamina[0] * k;
		dwSkilChkSum += sinSkill.UseSkill[cnt].Skill_Info.UseStamina[1] * k;
	}

	dwLevelQuestSum = sinQuest_levelLog & 0x576321cc;

	smPlayD3D(pX, pY, pZ, (ViewAnx&ANGCLIP), (any&ANGCLIP), (anz&ANGCLIP));

	dwChkSum = 0;
	for (cnt = 0; cnt < SIN_MAX_USE_SKILL; cnt++)
	{
		k = (cnt + 5) << 2;
		dwChkSum += sinSkill.UseSkill[cnt].UseSkillCount*k;
		dwChkSum += sinSkill.UseSkill[cnt].Point*k;
		dwChkSum += sinSkill.UseSkill[cnt].Mastery*k;
		dwChkSum += sinSkill.UseSkill[cnt].GageLength*k;
		dwChkSum += sinSkill.UseSkill[cnt].Skill_Info.UseStamina[0] * k;
		dwChkSum += sinSkill.UseSkill[cnt].Skill_Info.UseStamina[1] * k;
	}

	if (dwSkilChkSum != dwChkSum)
		SendSetHackUser3(8540, dwSkilChkSum, dwChkSum);

	if (dwLevelQuestSum != (sinQuest_levelLog & 0x576321cc))
		SendSetHackUser3(8820, (dwLevelQuestSum & 0x576321cc), sinQuest_levelLog);

	int mapY;
	int x, z, y;

	sPosition = GetMoveLocation(0, 0, -(dist << FLOATNS), anx, any, 0);

	x = lpCurPlayer->pX + sPosition.iX;
	y = lpCurPlayer->pY + sPosition.iY;
	z = lpCurPlayer->pZ + sPosition.iZ;

	PlayFloor = 0;
	y = 0;

	if (!DebugPlayer)
	{
		if (smGameStage[0])
		{
			mapY = (smGameStage[0]->GetHeight2(x, z));
			if (mapY > CLIP_OUT)
				y++;
		}
		if (smGameStage[1])
		{
			mapY = (smGameStage[1]->GetHeight2(x, z));
			if (mapY > CLIP_OUT)
				y++;
		}
		if (!y)
			PlayFloor = 64;
	}

	smLeaveTextureCriticalSection();
	LeaveCriticalSection(&cDrawSection);

	UnlockSpeedProtect(lpCurPlayer);
}

extern int DispPolyCnt;
extern int GetMouseMapPoint(int x, int y);

extern int xframe;

int GetPlayMouseAngle()
{
	int ax, az, ay;

	ax = xPs - ((int)RESOLUTION_WIDTH >> 1);
	az = yPs - ((int)RESOLUTION_HEIGHT >> 1);
	ay = GetRadian2D(0, 0, ax, -az);

	return ay + any;
}

int GetActionGame_PlayMouseAngle()
{
	int ax, az, ay;

	ax = xPs - lpCurPlayer->RendPoint.x;
	az = yPs - lpCurPlayer->RendPoint.x;
	ay = GetRadian2D(0, 0, ax, -az);

	return ay;;
}
// 设置鼠标点击
int SetMousePlay(int flag)
{
	int ax, az, ay;
	char szBuff[256];
	int	cnt;

	if (GAMESCREEN->GetActiveScreenType() != SCREEN_World)
		return TRUE;

	if (!lpCurPlayer->psModelAnimation || GAMEMAP->IsWarpGate() || lpCurPlayer->iStunTimeLeft || lpCurPlayer->psModelAnimation->iType == ANIMATIONTYPE_Die)
		return FALSE;

	if (g_IsDxProjectZoomIn <= 0)
	{
		dsMenuCursorPos(&pCursorPos, 2);

		if (StopCharMotion(pCursorPos.x, pCursorPos.y) == TRUE)
		{
			if (lpCurPlayer->psModelAnimation->iType < 0x100 && lpCurPlayer->psModelAnimation->iType != ANIMATIONTYPE_Idle)
			{
				lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Idle);
				lpCurPlayer->MoveFlag = FALSE;
			}
			flag = 0;
		}
		dsMenuCursorPos(&pCursorPos, 0);
	}
	switch (flag)
	{
	case 1:
		if (EachTradeButton && chrEachMaster)
		{
			cnt = GetPartyTradeButtonPos(xPs, yPs);

			if (cnt >= 0)
			{
				EachTradeButton = 0;
				switch (cnt)
				{
				case 0:
					if (GetTradeDistanceFromCode(chrEachMaster->iID) == TRUE)
					{
						SendRequestTrade(chrEachMaster->iID, 0);

						CHATGAMEHANDLE->AddChatBoxTextEx(CHATCOLOR_Error, "Sent a trade request to %s", chrEachMaster->sCharacterData.szName);
					}
					else
					{
						CHATGAMEHANDLE->AddChatBoxTextEx(CHATCOLOR_Error, "%s is too far away to request a trade", chrEachMaster->sCharacterData.szName);
					}

					return TRUE;

				case 1:
					return TRUE;

				case 2:
					PARTYHANDLE->ProcessPacket(&PacketRequestParty(chrEachMaster->sCharacterData.dwObjectSerial));
					return TRUE;

				case 3:
					g_IsCheckClanMember(chrEachMaster);
					return TRUE;
				}
			}
		}
		if (GetFieldMapCursor() == TRUE && cInterFace.sInterFlags.MapOnFlag)
		{
			if (lpCurPlayer->sCharacterData.iLevel < 20)
				sinCheck_ShowHelpMap();
			break;
		}
		/*if (!ActionGameMode)
		{
			if (lpCharSelPlayer || lpSelItem)
			{
				SelMouseButton = 1;
				TraceAttackPlay();
				AutoCameraFlag = FALSE;
			}
			else
			{
				if (MsTraceMode && !lpCharSelPlayer && !lpSelItem)
				{
					if (lpCurPlayer->psModelAnimation->State != ANIMATIONTYPE_Attack && lpCurPlayer->psModelAnimation->State!=ANIMATIONTYPE_Skill)
						lpCurPlayer->SetTargetPosi(0,0);

					CancelAttack();
				}

				AutoCameraFlag = TRUE;
			}
		}
		else
			ActionMouseClick[0] = 1;*/

		if (lpCharSelPlayer || lpSelItem)
		{
			SelMouseButton = 1;
			TraceAttackPlay();
			AutoCameraFlag = FALSE;
		}
		else
		{
			if (MsTraceMode && !lpCharSelPlayer && !lpSelItem)
			{
				if (lpCurPlayer->psModelAnimation->iType != ANIMATIONTYPE_Attack && lpCurPlayer->psModelAnimation->iType != ANIMATIONTYPE_Skill)
					lpCurPlayer->SetTargetPosi(0, 0);

				CancelAttack();
			}

			AutoCameraFlag = TRUE;
		}

		if (SkillMasterFlag)
			sinSkillMasterClose();

		lpCurPlayer->MoveFlag = TRUE;
		DispEachMode = 0;

		if (hFocusWnd)
		{
			GetWindowText(hFocusWnd, szBuff, 240);
			if (szBuff[0] == 0)
			{
				hFocusWnd = 0;
				szLastWhisperName[0] = 0;
				LastWhisperLen = 0;
				InterfaceParty.chat_WhisperPartyPlayer_close();
				chatlistSPEAKERflagChg(0);
				SetIME_Mode(0);
			}
		}
		break;

	case 0:
		if (Moving_DblClick)
		{
			TraceMode_DblClick = TRUE;
			Moving_DblClick = 0;
			lpCurPlayer->MoveFlag = TRUE;
			ActionMouseClick[0] = 2;
		}
		else
		{
			if (!lpCharMsTrace && !lpMsTraceItem)
				lpCurPlayer->SetAction(0);
		}
		return TRUE;

	case 11:
		if (hFocusWnd)
		{
			GetWindowText(hFocusWnd, szBuff, 240);
			if (szBuff[0] == 0)
			{
				hFocusWnd = 0;
				SetIME_Mode(0);
			}
		}
		if (sinSkill.pRightSkill && lpCurPlayer->psModelAnimation->iType != ANIMATIONTYPE_Attack && lpCurPlayer->psModelAnimation->iType != ANIMATIONTYPE_Skill)
		{

			if (lpCurPlayer->psModelAnimation->iType != ANIMATIONTYPE_Potion)
			{
				if (OpenPlaySkill(sinSkill.pRightSkill))
					break;
			}
		}

		/*if (!ActionGameMode)
		{
			if (lpCharSelPlayer)
			{
				SelMouseButton = 2;
				TraceAttackPlay();
				AutoCameraFlag = FALSE;
				lpCurPlayer->MoveFlag = TRUE;
				DispEachMode = 0;
			}
		}
		else
			ActionMouseClick[1] = TRUE;*/

		if (lpCharSelPlayer)
		{
			SelMouseButton = 2;
			TraceAttackPlay();
			AutoCameraFlag = FALSE;
			lpCurPlayer->MoveFlag = TRUE;
			DispEachMode = 0;
		}

		break;
	case 10:
		if (!lpCharMsTrace && !lpMsTraceItem)
			lpCurPlayer->SetAction(0);
		break;
	case 3:
		ay = msY * 4;
		ax = msX * 8;

		if (ay)
		{
			if (!CaTarDist)
				CaTarDist = dist;

			CaTarDist -= ay;

			if (CaTarDist < 100)
			{
				if (anx <= 40)
				{
					if (CaTarDist < 40)
						CaTarDist = 40;
				}
				else
					CaTarDist = 100;
			}

			if (CaTarDist > 440)
				CaTarDist = 440;
		}

		if (ax)
		{
			if (SETTINGHANDLE->Get().bInvertedCamera)
				ax = -ax;

			az = ANGLE_45 >> 1;

			if (ax < -az)
				ax = -az;
			if (ax > az)
				ax = az;

			CaMovAngle += ax;
		}
		return TRUE;
	case 4:
		if (DebugPlayer)
		{
			ay = msY * 2;
			ax = msX * 2;

			any += ax;
			anx += ay;

			any &= ANGCLIP;
			anx &= ANGCLIP;
		}
		return TRUE;
	}

	if (lpCurPlayer->psModelAnimation &&
		(lpCurPlayer->psModelAnimation->iType == ANIMATIONTYPE_Attack ||
			lpCurPlayer->psModelAnimation->iType == ANIMATIONTYPE_Skill ||
			lpCurPlayer->psModelAnimation->iType == ANIMATIONTYPE_Yahoo))
		return FALSE;

	if (lpCurPlayer->MoveFlag)
	{
		if (MsTraceMode)
			lpCurPlayer->Angle.y = GetMouseSelAngle();
		else
		{
			if (ActionGameMode)
				lpCurPlayer->Angle.y = GetActionGame_PlayMouseAngle();
			else
				lpCurPlayer->Angle.y = GetPlayMouseAngle();
		}
	}

	return TRUE;
}

extern int TestTraceMatrix();

int _stdcall InitD3D(HWND hWnd)
{
	hwnd = hWnd;

	MidX = (int)SETTINGHANDLE->Get().uWidth / 2;
	MidY = (int)SETTINGHANDLE->Get().uHeight / 2;
	MidY -= 59;
	viewdistZ = (int)SETTINGHANDLE->Get().uWidth;

	if (!GRAPHICENGINE->InitD3D(hWnd))
		return FALSE;

	smRender.m_FogIsRend = TRUE;

	HBITMAP hBitmap;
	HDC	hdcBitmap;

	auto hdc = GetDC(hwnd);

	hBitmap = LoadBitmap(hinst, MAKEINTRESOURCE(IDB_LOGO));

	hdcBitmap = CreateCompatibleDC(hdc);
	SelectObject(hdcBitmap, hBitmap);

	BitBlt(hdc, ((int)RESOLUTION_WIDTH >> 1) - 250, ((int)RESOLUTION_HEIGHT >> 1) - 173, 500, 345, hdcBitmap, 0, 0, SRCCOPY);

	SetDxProjection((D3DX_PI / 4.4f), RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 20.f, 4000.f);

	smRender.CreateRenderBuff(SETTINGHANDLE->Get().iCameraRange);

	if (smRender.m_GameFieldView)
	{
		smRender.m_GameFieldViewStep = 22;
		smRender.SetGameFieldViewStep();
	}

	TestTraceMatrix();
	InitTexture();

	InitMaterial();
	smRender.SetMaterialGroup(smMaterialGroup);
	InitEffect();

	InitAssaEffect();

	Sleep(2000);

	DeleteDC(hdcBitmap);
	DeleteObject(hBitmap);
	ReleaseDC(hwnd, hdc);

	//Check_CodeSafe((DWORD)GameInit);

	InitSoundEffect(hwnd);
	InitPatterns();

	lpCurPlayer = InitRotPlayer();

	sinChar = &lpCurPlayer->sCharacterData;

	return Code_VRamBuffOpen();
}

void _stdcall CloseD3d()
{
	CloseRotPlayer();

	CloseSoundEffect();

	CloseTexture();
}

int GameInit()
{
	dwPlayTime = GetCurrentTime();
	dwMemError = dwMemError ^ dwPlayTime;

	ReformCharForm();

	InitMotionBlur();
	InitBackGround();

	//Check_CodeSafe((DWORD)CloseD3d);

	InitPat3D(InitStage());

	CreateItem2PassTexture();

	CheckCharForm();

	sinInit();

	g_fWinSizeRatio_X = float(RESOLUTION_WIDTH) / 800.f;
	g_fWinSizeRatio_Y = float(RESOLUTION_HEIGHT) / 600.f;

	CreateBeforeFullZoomMap();
	CreateFontImage();


	TraceCameraPosi.x = lpCurPlayer->pX;
	TraceCameraPosi.y = lpCurPlayer->pY;
	TraceCameraPosi.z = lpCurPlayer->pZ;

	TraceTargetPosi.x = lpCurPlayer->pX;
	TraceTargetPosi.y = lpCurPlayer->pY;
	TraceTargetPosi.z = lpCurPlayer->pZ;

	InitMessageBox();

	smRender.SMMULT_PERSPECTIVE_HEIGHT = RENDCLIP_DEFAULT_MULT_PERSPECTIVE_HEIGHT;
	MidX = (int)RESOLUTION_WIDTH / 2;
	MidY = (int)RESOLUTION_HEIGHT / 2;
	viewdistZ = (int)RESOLUTION_WIDTH;

	ReadTextures();

	CheckOftenMeshTextureSwap();

	if (STAGE_MAP[0])
		PlayBGM_Direct(STAGE_MAP[0]->iBackgroundMusicID);
	else
	{
		OpenBGM("wav\\bgm\\Field - Desert - Pilgrim.bgm");
		PlayBGM();
	}
	CharPlaySound(lpCurPlayer);
	StartEffect(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, EFFECT_GAME_START1);
	RestartPlayCount = 700;

	hFocusWnd = 0;
	szLastWhisperName[0] = 0;
	LastWhisperLen = 0;
	InterfaceParty.chat_WhisperPartyPlayer_close();
	chatlistSPEAKERflagChg(0);
	SendMessage(hTextWnd, EM_SETLIMITTEXT, 78, 0);

	MouseButton[0] = 0;
	MouseButton[1] = 0;
	MouseButton[2] = 0;

	Unit	*lpTempChar;

	lpTempChar = SelectRotPlayer(lpCurPlayer);
	if (lpTempChar)
	{
		lpCurPlayer = lpTempChar;
		sinChar = &lpCurPlayer->sCharacterData;
	}
	lpTempChar = SelectRotPlayer(lpCurPlayer);
	if (lpTempChar)
	{
		lpCurPlayer = lpTempChar;
		sinChar = &lpCurPlayer->sCharacterData;
	}

	SetIME_Mode(0);

	ReformSkillInfo();

	HoMsgBoxMode = 1;
	SetMessageFrameSelect(HoMsgBoxMode);

	CreateWinIntThread();

	return TRUE;
}
int GameClose()
{
	ClosePat3D();
	CloseBackGround();
	CloseStage();

	sinClose();

	CloseMaterial();

	DestroyWinIntThread();

	if (BellatraEffectInitFlag)
		DestroyBellatraFontEffect();

	return TRUE;
}
int DIsplayLogoImage()
{
	UI::LPIMAGE pLogoImage = UI::ImageLoader::LoadImage_("Image\\Logo.bmp");

	if (pLogoImage)
	{
		GRAPHICENGINE->BeginScene(CAMERAHANDLE->GetViewMatrix());

		UI::ImageRender::Render(pLogoImage, (int)RESOLUTION_WIDTH / 2 - 250, (int)RESOLUTION_HEIGHT / 2 - 150, 500, 300, -1);

		GRAPHICENGINE->EndScene();

		Sleep(600);

		UI::ImageLoader::DeleteImage(pLogoImage);
	}
	return TRUE;;
}

float xr = 0;

int jcnt = 0;

float brt = 1;
float bs = 0;

int ox = 0, oy = 0, oz = 0;

int GoText = 0;

char strBuff[240];
char strBuff2[256];

int RestoreFlag = 0;

int RestoreAll()
{
	VramTotal = 0;

	RestoreTextures();

	sinReload();

	return TRUE;

}
int NumPoly;
int Disp_tx, Disp_ty;
int Disp_rx, Disp_ry;

Unit	*lpCharMsgSort[MAX_UNITS];
int ChatMsgSortCnt;

extern int Debug_RecvCount1;
extern int Debug_RecvCount2;


int RestoreInterfaceTexture()
{
	int cnt;

	smRender.Color_R = 0;
	smRender.Color_G = 0;
	smRender.Color_B = 0;
	smRender.Color_A = 0;

	cnt = 0;

	GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_COLOROP, D3DTOP_MODULATE);
	GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_COLORARG2, D3DTA_CURRENT);

	GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
	GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);

	GRAPHICENGINE->GetDevice()->SetTexture(cnt, 0);

	for (cnt = 1; cnt < 8; cnt++)
	{
		GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_COLOROP, D3DTOP_DISABLE);
		GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
		GRAPHICENGINE->GetDevice()->SetTexture(cnt, 0);
	}

	return TRUE;
}
void VirtualDrawGameState(void)
{
	smRender.ClearLight();

	int BackDarkLevel;

	BackDarkLevel = DarkLevel;
	DarkLevel = 0;

	RestoreInterfaceTexture();

	if (GAMESOCKET->iDisconnectTime)
	{
		switch (GAMESOCKET->iDisconnectType)
		{
		case 0:
			CTITLEBOX->RenderTextMiddle("Connection lost with Server");break;
		case 1:
			CTITLEBOX->RenderTextMiddle("Connection lost with Server (1)");break;
		case 2:
			CTITLEBOX->RenderTextMiddle("Connection lost with Server (2)");break;
		case 3:
			CTITLEBOX->RenderTextMiddle("Connection lost with Server (3)");break;
		case 4:
			CTITLEBOX->RenderTextMiddle("Connection lost with Server (4)");break;
		}
		if (!quit && ((DWORD)GAMESOCKET->iDisconnectTime + 5000) < TICKCOUNT)
			quit = TRUE;
	}
	else
	{
		if (quit)
			CTITLEBOX->RenderTextMiddle("Quitting Game");
		else
		{
			if (dwCloseBoxTime && dwCloseBoxTime > dwPlayTime)
				CTITLEBOX->RenderTextMiddle("Please close the current window before quitting");
			else
			{
				if (dwBattleQuitTime)
				{
					if ((dwBattleQuitTime + 5000) > dwPlayTime)
						CTITLEBOX->RenderTextMiddle("Cannot quit while in combat");
					else
						dwBattleQuitTime = 0;
				}
			}
		}
	}

	DarkLevel = BackDarkLevel;
}

int DrawGameState()
{
	int i;
	int cnt2;

	int	y, DispBar, DispMaster;

	Unit	*lpChar;
	scITEM	*lpItem;
	RECT	ddRect;
	int BackDarkLevel;
	DWORD	dwColor;

	ddRect.left = 0;
	ddRect.right = 800;
	ddRect.top = 0;
	ddRect.bottom = 150;

	smRender.ClearLight();

	BackDarkLevel = DarkLevel;
	DarkLevel = 0;

	RestoreInterfaceTexture();

	if (lpCharMsTrace && lpCharMsTrace->RendSucess)
	{
		Disp_tx = lpCharMsTrace->RendPoint.x - 32;
		Disp_ty = lpCharMsTrace->RendPoint.y - 12;
	}

	if (lpCharSelPlayer && lpCharMsTrace != lpCharSelPlayer)
	{
		if (lpCharSelPlayer->RendSucess)
		{
			Disp_rx = lpCharSelPlayer->RendPoint.x - 32;
			Disp_ry = lpCharSelPlayer->RendPoint.y - 12;
		}
	}
	lpChar = 0;
	lpItem = 0;

	if (lpMsTraceItem)
		lpItem = lpMsTraceItem;
	else
		lpItem = lpSelItem;

	if (VRKeyBuff['A'])
	{
		for (int i = 0; i < DISP_ITEM_MAX; i++)
		{
			if (scItems[i].Flag && scItems[i].ItemCode != 0 && lpSelItem != &scItems[i])
			{
				if (scItems[i].RendPoint.z >= 32 * fONE && scItems[i].RendPoint.z < 64 * 12 * fONE)
					DrawCharacterMessage(scItems[i].RendPoint.x,
						scItems[i].RendPoint.y,
						scItems[i].szName,
						0, 0, 0, D3DCOLOR_XRGB(110, 110, 110));
			}
		}
	}

	if (lpSelItem && !lpCharSelPlayer && !lpCharMsTrace)
	{
		Disp_tx = MsSelPos.x;
		Disp_ty = MsSelPos.y;

		DrawCharacterMessage(Disp_tx, Disp_ty, lpSelItem->szName, 0, 0, 0, D3DCOLOR_XRGB(180, 180, 180));
	}

	int	SelFlag;

	ChatMsgSortCnt = 0;

	for (int i = 0; i < MAX_UNITS; i++)
	{
		Unit * pc = chrOtherPlayer + i;

		if (pc->bActive && pc->RendSucess && pc->sCharacterData.szName[0])
		{
			//Party Handler
			if (PARTYHANDLE->IsPartyMember(pc->iID))
				pc->dwExclusiveNum = 1;
			else if (PARTYHANDLE->IsRaidMember(pc->iID))
				pc->dwExclusiveNum = 2;
			else
				pc->dwExclusiveNum = 0;

			SelFlag = 0;
			if (pc->RendPoint.z < 12 * 64 * fONE)
			{
				if (pc->szMessage[0])
				{

					if (pc->dwMessageEndTime < dwPlayTime)
						pc->szMessage[0] = 0;
					else
					{
						if (pc->sCharacterData.iType != CHARACTERTYPE_None)
						{
							lpCharMsgSort[ChatMsgSortCnt++] = pc;
							SelFlag++;
						}
					}
				}
				// 伤害值
				if (pc->Damge)
				{
					if (pc->dwDamgeTimer < dwPlayTime)
					{
						pc->Damge = 0;
						pc->DmgBlendValue = 0;
					}
					else
					{
						if (pc->sCharacterData.iType != CHARACTERTYPE_None)
						{
							lpCharMsgSort[ChatMsgSortCnt++] = pc;
							SelFlag++;
						}
					}
				}
				if (pc->dwTradeMsgCode && !SelFlag)
				{
					lpCharMsgSort[ChatMsgSortCnt++] = pc;
					SelFlag++;
				}
			}

			if (!SelFlag)
			{
				if (lpCharMsTrace == pc ||
					lpCharSelPlayer == pc ||
					(pc->sCharacterData.iType == CHARACTERTYPE_NPC && pc->RendPoint.z < 12 * 64 * fONE) ||
					(pc->sCharacterData.sHP.sMin > 0 && pc->sCharacterData.iType == CHARACTERTYPE_Monster && pc->sCharacterData.iMonsterType == MONSTERTYPE_Friendly) ||
					(pc->sCharacterData.iClanID && pc->sCharacterData.iClanID == lpCurPlayer->sCharacterData.iClanID) ||
					(HoMsgBoxMode && pc->dwClanManageBit) || (HoMsgBoxMode && pc->dwVipBit) ||
					pc->dwExclusiveNum)
					lpCharMsgSort[ChatMsgSortCnt++] = pc;
			}
		}
	}
	if (lpCurPlayer->szMessage[0])
	{
		if (lpCurPlayer->dwMessageEndTime < dwPlayTime)
			lpCurPlayer->szMessage[0] = 0;
		else
			lpCharMsgSort[ChatMsgSortCnt++] = lpCurPlayer;
	}
	else if (lpCurPlayer->Damge)
	{
		if (lpCurPlayer->dwDamgeTimer < dwPlayTime)
		{
			lpCurPlayer->Damge = 0;
			lpCurPlayer->DmgBlendValue = 0;
		}
		else
			lpCharMsgSort[ChatMsgSortCnt++] = lpCurPlayer;
	}
	else
	{
		if (lpCurPlayer->dwTradeMsgCode)
			lpCharMsgSort[ChatMsgSortCnt++] = lpCurPlayer;
	}

	if (ChatMsgSortCnt)
	{
		for (int i = 0; i < ChatMsgSortCnt; i++)
		{
			for (cnt2 = i + 1; cnt2 < ChatMsgSortCnt; cnt2++)
			{
				if (lpCharMsgSort[i]->RendPoint.z < lpCharMsgSort[cnt2]->RendPoint.z ||
					lpCharMsgSort[i] == lpCharMsTrace ||
					lpCharMsgSort[i] == lpCharSelPlayer)
				{
					lpChar = lpCharMsgSort[i];
					lpCharMsgSort[i] = lpCharMsgSort[cnt2];
					lpCharMsgSort[cnt2] = lpChar;
				}
			}
		}
	}

	smTEXTUREHANDLE *lpDDS_clanMark = nullptr;
	char *szClanName;
	char *szBoxMsg;
	BOOL  selectedBox;

	y = 8 + (ViewAnx >> 6);

	for (int i = 0; i < ChatMsgSortCnt; i++)
	{
		dwColor = D3DCOLOR_XRGB(255, 255, 200);

		DispBar = FALSE;
		DispMaster = FALSE;
		selectedBox = FALSE;

		if (lpCharMsgSort[i]->dwExclusiveNum)
		{
			DispBar = TRUE;
			dwColor = D3DCOLOR_XRGB(220, 255, 160);
		}
		else if (lpCharMsgSort[i]->sCharacterData.iType == CHARACTERTYPE_Monster)
		{
			if (lpCharMsgSort[i]->sCharacterData.iMonsterType == MONSTERTYPE_Friendly)
			{
				dwColor = D3DCOLOR_XRGB(220, 255, 160);

				if (lpCharMsgSort[i]->sCharacterData.iOwnerID == lpCurPlayer->iID ||
					lpCharMsgSort[i]->sCharacterData.iClanID)
					DispBar = TRUE;
				else
					DispMaster = TRUE;
			}
			// 怪物血条
			else
			{
				DispBar = TRUE;
				dwColor = D3DCOLOR_XRGB(255, 210, 210);
			}
		}
		//NPC头上的字的颜色
		else if (lpCharMsgSort[i]->sCharacterData.iType == CHARACTERTYPE_NPC)
			dwColor = D3DCOLOR_XRGB(180, 180, 255);

		if (lpCharMsgSort[i] == lpCharMsTrace)
		{
			if (lpCharMsgSort[i]->sCharacterData.iType == CHARACTERTYPE_Monster && lpCharMsgSort[i]->sCharacterData.iMonsterType != MONSTERTYPE_Friendly)
				dwColor = D3DCOLOR_XRGB(255, 230, 200);
			else
				dwColor = D3DCOLOR_XRGB(255, 255, 255);

			selectedBox = TRUE;
		}
		else
		{
			if (lpCharMsgSort[i] == lpCharSelPlayer && lpCharMsgSort[i]->szMessage[0])
				selectedBox = TRUE;
		}

		lpDDS_clanMark = nullptr;
		szClanName = 0;

		DWORD dwClanMgrBit = 0;
		DWORD dwVipBit = 0;

		if (lpCharMsgSort[i]->sCharacterData.iClanID)
		{
			if (lpCharMsgSort[i] == lpCurPlayer)
			{
				lpDDS_clanMark = cldata.hClanMark16;
				szClanName = cldata.name;
			}
			else if (lpCharMsgSort[i]->iClanInfoIndex >= 0)
			{
				lpDDS_clanMark = ClanInfo[lpCharMsgSort[i]->iClanInfoIndex].hClanMark;
				szClanName = ClanInfo[lpCharMsgSort[i]->iClanInfoIndex].ClanInfoHeader.ClanName;
			}
		}

		if (((lpCharMsgSort[i]->szMessage[0] || lpCharMsgSort[i]->dwTradeMsgCode) &&
			lpCharMsgSort[i]->sCharacterData.iType != CHARACTERTYPE_None &&
			lpCharMsgSort[i]->RendPoint.z < 12 * 64 * fONE) || lpCharMsgSort[i] == lpCurPlayer)
		{
			if (szClanName && lpCharMsgSort[i] != lpCharMsTrace && lpCharMsgSort[i] != lpCharSelPlayer)
			{
				if (!lpCurPlayer->sCharacterData.iClanID ||
					lpCharMsgSort[i]->sCharacterData.iClanID != lpCurPlayer->sCharacterData.iClanID)
					szClanName = 0;
			}

			if (lpCharMsgSort[i]->szMessage[0])
				DrawCharacterMessage(lpCharMsgSort[i]->RendPoint.x, lpCharMsgSort[i]->RendRect2D.top + y, lpCharMsgSort[i]->szMessage, 30, lpDDS_clanMark, szClanName, dwColor, selectedBox);
			else
			{
				if (lpCharMsgSort[i]->szTradeMessage[0])
					DrawCharacterShopByeMessage(lpCharMsgSort[i]->RendPoint.x, lpCharMsgSort[i]->RendRect2D.top + y, lpCharMsgSort[i]->szTradeMessage, 30, lpDDS_clanMark, dwColor, selectedBox);
			}
			lpCharMsgSort[i]->ShowDamage(y);
		}
		else
		{
			if (DispMaster && !lpCharMsgSort[i]->sCharacterData.iClanID)
			{
				wsprintf(strBuff, "(%s)", lpCharMsgSort[i]->sCharacterData.Player.szHeadModel + 1);
				DrawTwoLineMessage(lpCharMsgSort[i]->RendPoint.x, lpCharMsgSort[i]->RendRect2D.top + y, lpCharMsgSort[i]->sCharacterData.szName, strBuff, dwColor, D3DCOLOR_XRGB(255, 255, 200), 0, selectedBox);
			}
			else
			{
				// 皇冠 //VIP皇冠
				if (HoMsgBoxMode)
				{
					dwClanMgrBit = lpCharMsgSort[i]->dwClanManageBit;
					dwVipBit = lpCharMsgSort[i]->dwVipBit;
				}
				else
				{
					dwClanMgrBit = 0;
					dwVipBit = 0;
				}

				if (szClanName)
				{
					if (SETTINGHANDLE->Get().bDebugMode && VRKeyBuff[VK_CONTROL])
						wsprintf(strBuff, "%d/%d", lpCharMsgSort[i]->sCharacterData.iClanID, lpCharMsgSort[i]->iClanInfoIndex);
					else
						wsprintf(strBuff, "[%s]", szClanName);

					DrawTwoLineMessage(lpCharMsgSort[i]->RendPoint.x, lpCharMsgSort[i]->RendRect2D.top + y, strBuff, lpCharMsgSort[i]->sCharacterData.szName, D3DCOLOR_XRGB(150, 255, 200), dwColor, lpDDS_clanMark, selectedBox, dwClanMgrBit, dwVipBit);
				}
				else
				{
					szBoxMsg = lpCharMsgSort[i]->sCharacterData.szName;

					DrawCharacterMessage(lpCharMsgSort[i]->RendPoint.x, lpCharMsgSort[i]->RendRect2D.top + y, szBoxMsg, 30, lpDDS_clanMark, szClanName, dwColor, selectedBox, dwClanMgrBit, dwVipBit);
				}
				// 打怪伤害显示
				lpCharMsgSort[i]->ShowDamage(y);
			}
		}

		if (DispBar)
			lpCharMsgSort[i]->DrawStateBar2(lpCharMsgSort[i]->RendPoint.x - 30, lpCharMsgSort[i]->RendRect2D.top + y - 14);
	}

	if (lpCurPlayer->AttackSkil)
	{
		//转换 凤凰
		if (((lpCurPlayer->sCharacterData.iClass == CHARACTERCLASS_Pikeman) && ((lpCurPlayer->AttackSkil & 0xFF) == SKILL_PLAY_CHARGING_STRIKE)) || ((lpCurPlayer->sCharacterData.iClass == CHARACTERCLASS_Archer) && ((lpCurPlayer->AttackSkil & 0xFF) == SKILL_PLAY_PHOENIX_SHOT)))
		{
			int iFrame = lpCurPlayer->iFrame - lpCurPlayer->psModelAnimation->StartFrame * 160;

			if (lpCurPlayer->psModelAnimation->EventFrame[0]<(DWORD)iFrame && lpCurPlayer->psModelAnimation->EventFrame[1]>(DWORD)iFrame)
			{
				iFrame -= (int)lpCurPlayer->psModelAnimation->EventFrame[0];
				cnt2 = (int)(lpCurPlayer->psModelAnimation->EventFrame[1] - lpCurPlayer->psModelAnimation->EventFrame[0]);

				lpCurPlayer->DrawChargingBar(lpCurPlayer->RendPoint.x - 30, lpCurPlayer->RendRect2D.bottom, iFrame, cnt2);
			}
		}
	}
	if (DispInterface)
	{
		if (DispEachMode)
			DrawEachPlayer(0.74f, 0.32f, 1);
		else
		{
			DrawEachPlayer(0.92f, 0.1f, 0);

			dsDrawOffset.x = RESOLUTION_WIDTH - 800;
			dsDrawOffset.y = RESOLUTION_HEIGHT - 600;
			dsDrawOffsetArray = dsARRAY_RIGHT | dsARRAY_BOTTOM;
			dsMenuCursorPos(&pCursorPos, 3);

			DrawInterfaceParty();
			dsMenuCursorPos(&pCursorPos, 0);
			dsDrawOffsetArray = dsARRAY_TOP;
			dsDrawOffset.x = 0;
			dsDrawOffset.y = 0;

			DrawInterfaceParty(TRADEBUTTONMAIN_X, TRADEBUTTONMAIN_Y);
		}

	}
	if (EachTradeButton && chrEachMaster)
		DisplayPartyTradeButton();

	DisplaySodScore();

	RestoreInterfaceTexture();

	dsDrawOffset.x = RESOLUTION_WIDTH - 800;
	dsDrawOffset.y = RESOLUTION_HEIGHT - 600;

	if (DispInterface)
		sinDraw();

	dsDrawOffset.x = 0;
	dsDrawOffset.y = 0;

	if (BellatraEffectInitFlag)
		DrawBellatraFontEffect();

	DWORD Color1 = D3DCOLOR_XRGB(255, 255, 255);
	DWORD Color2 = D3DCOLOR_XRGB(0, 0, 0);

	int	rcv1, rcv2, snd1, snd2, arcv1, brcv1, arcv2, brcv2;
	int LineY;

	if (DisplayDebug)
	{
		rcv1 = 0;
		rcv2 = 0;
		snd1 = 0;
		snd2 = 0;
		arcv1 = 0;
		brcv1 = 0;
		arcv2 = 0;
		brcv2 = 0;

		STRINGFORMAT(strBuff, "FPS = %0.3f %d(%d) %d x=%d z=%d y=%d VRAM=%d R1=%d(%d) R2=%d(%d) S1=%d S2=%d (%d/%d) (%d/%d) RcvTurb( %d )", GetFPS(), DispRender, DispMainLoop, DispPolyCnt, lpCurPlayer->pX >> (FLOATNS), lpCurPlayer->pZ >> (FLOATNS), lpCurPlayer->pY >> (FLOATNS), (VramTotal / (1024 * 1024)), rcv1, Debug_RecvCount1, rcv2, Debug_RecvCount2, snd1, snd2, brcv1, arcv1, brcv2, arcv2, smTransTurbRcvMode);

		dsTextLineOut(0, 11, 11, strBuff, lstrlen(strBuff), Color2);
		dsTextLineOut(0, 10, 10, strBuff, lstrlen(strBuff), Color1);

		STRINGFORMAT(strBuff, "Stage : %s , %s", szGameStageName[0], szGameStageName[1]);
		dsTextLineOut(0, 11, 31, strBuff, lstrlen(strBuff), Color2);
		dsTextLineOut(0, 10, 30, strBuff, lstrlen(strBuff), Color1);

		STRINGFORMAT(strBuff, "World Time (%d:%d)", GAMEMAP->GetGameHour(), GAMEMAP->GetGameMin());
		dsTextLineOut(0, ((int)RESOLUTION_WIDTH >> 1) + 1, 31, strBuff, lstrlen(strBuff), Color2);
		dsTextLineOut(0, ((int)RESOLUTION_WIDTH >> 1), 30, strBuff, lstrlen(strBuff), Color1);

		STRINGFORMAT(strBuff, "MousePosX %d", pCursorPos.x);
		dsTextLineOut(0, ((int)RESOLUTION_WIDTH >> 1) + 1, 61, strBuff, lstrlen(strBuff), Color2);
		dsTextLineOut(0, ((int)RESOLUTION_WIDTH >> 1), 60, strBuff, lstrlen(strBuff), Color1);

		STRINGFORMAT(strBuff, "MousePosY %d", pCursorPos.y);
		dsTextLineOut(0, ((int)RESOLUTION_WIDTH >> 1) + 1, 81, strBuff, lstrlen(strBuff), Color2);
		dsTextLineOut(0, ((int)RESOLUTION_WIDTH >> 1), 80, strBuff, lstrlen(strBuff), Color1);



		if (lpCurPlayer->bLoading == FALSE)
		{
			STRINGFORMAT(strBuff, "%s", lpCurPlayer->lpDinaPattern->szPatName);

			dsTextLineOut(0, ((int)RESOLUTION_WIDTH >> 1) + 1 + 120, 31, strBuff, lstrlen(strBuff), Color2);
			dsTextLineOut(0, ((int)RESOLUTION_WIDTH >> 1) + 120, 30, strBuff, lstrlen(strBuff), Color1);

			STRINGFORMAT(strBuff, "Damage : %d", LastAttackDamage);
			dsTextLineOut(0, 9, 48, strBuff, lstrlen(strBuff), Color2);
			dsTextLineOut(0, 8, 47, strBuff, lstrlen(strBuff), Color1);

			STRINGFORMAT(strBuff, "RcvDamage:(%d) [%d] %d %d", Record_TotalRecvDamageCount, Record_RecvDamageCount, Record_DefenceCount, Record_BlockCount);
			dsTextLineOut(0, 9, 62, strBuff, lstrlen(strBuff), Color2);
			dsTextLineOut(0, 8, 61, strBuff, lstrlen(strBuff), Color1);
		}

		LineY = 48;

		for (i = 0; i < MAX_UNITS; i++)
		{
			if (chrOtherPlayer[i].bActive &&
				chrOtherPlayer[i].Pattern &&
				chrOtherPlayer[i].sCharacterData.iType == CHARACTERTYPE_Player)
			{
				STRINGFORMAT(strBuff, "%s", chrOtherPlayer[i].sCharacterData.szName);
				dsTextLineOut(0, (int)RESOLUTION_WIDTH - 220, LineY + 1, strBuff, lstrlen(strBuff), Color2);
				dsTextLineOut(0, (int)RESOLUTION_WIDTH - 221, LineY, strBuff, lstrlen(strBuff), Color1);
				LineY += 16;
				if (LineY > 460)
					break;
			}
		}

		int	MonCharBuff[MAX_UNITS];
		int MonCharCnt = 0;
		int	MonCnt;

		for (i = 0; i < MAX_UNITS; i++)
		{
			if (chrOtherPlayer[i].bActive &&
				chrOtherPlayer[i].Pattern &&
				chrOtherPlayer[i].sCharacterData.iType != CHARACTERTYPE_Player)
				MonCharBuff[MonCharCnt++] = i;
		}

		LineY = 48;

		for (i = 0; i < MonCharCnt; i++)
		{
			if (MonCharBuff[i] >= 0)
			{
				MonCnt = 1;

				for (int j = i + 1; j < MonCharCnt; j++)
				{
					if (MonCharBuff[j] >= 0 && lstrcmp(chrOtherPlayer[MonCharBuff[j]].sCharacterData.szName, chrOtherPlayer[MonCharBuff[i]].sCharacterData.szName) == 0)
					{
						MonCharBuff[j] = -1;
						MonCnt++;
					}
				}

				STRINGFORMAT(strBuff, "%s x %d", chrOtherPlayer[MonCharBuff[i]].sCharacterData.szName, MonCnt);
				dsTextLineOut(0, (int)RESOLUTION_WIDTH - 380, LineY + 1, strBuff, lstrlen(strBuff), Color2);

				DWORD Color;
				if (chrOtherPlayer[MonCharBuff[i]].sCharacterData.iType == CHARACTERTYPE_NPC)
					Color = D3DCOLOR_XRGB(192, 192, 255);
				else
					Color = D3DCOLOR_XRGB(255, 192, 192);

				dsTextLineOut(0, (int)RESOLUTION_WIDTH - 381, LineY, strBuff, lstrlen(strBuff), Color);

				LineY += 16;
				if (LineY > 460)
					break;
			}
		}
	}

	if (GAMESOCKET->iDisconnectTime)
	{
		switch (GAMESOCKET->iDisconnectType)
		{
		case 0:
			CTITLEBOX->RenderTextMiddle("Connection lost with Server"); break;
		case 1:
			CTITLEBOX->RenderTextMiddle("Connection lost with Server (1)"); break;
		case 2:
			CTITLEBOX->RenderTextMiddle("Connection lost with Server (2)"); break;
		case 3:
			CTITLEBOX->RenderTextMiddle("Connection lost with Server (3)"); break;
		case 4:
			CTITLEBOX->RenderTextMiddle("Connection lost with Server (4)"); break;
		}
		if (!quit && ((DWORD)GAMESOCKET->iDisconnectTime + 5000) < TICKCOUNT)
			quit = TRUE;
	}
	else
	{
		if (quit)
			CTITLEBOX->RenderTextMiddle("Quitting Game");
		else
		{
			if (dwCloseBoxTime && dwCloseBoxTime > dwPlayTime)
				CTITLEBOX->RenderTextMiddle("Please close the current window before quitting");
			else
			{
				if (dwBattleQuitTime)
				{
					if ((dwBattleQuitTime + 5000) > dwPlayTime)
						CTITLEBOX->RenderTextMiddle("Cannot quit while in combat");
					else
						dwBattleQuitTime = 0;
				}
			}
		}
	}

	DarkLevel = BackDarkLevel;

	return TRUE;
}
void _stdcall smPlayD3D(int x, int y, int z, int ax, int ay, int az)
{
	eCAMERA_TRACE	eTrace;
	int	ap;

	DispPolyCnt = 0;

	SetRendSight();

	int Mapfl;
	int cy;
	int mapY;

	Mapfl = 0;
	cy = y + 16 * fONE;

	if (!DebugPlayer)
	{
		if (smGameStage[0])
		{
			mapY = (smGameStage[0]->GetHeight(x, z));
			if (y < mapY)
			{
				y = mapY;
				y += 8 << FLOATNS;
			}
			if (mapY > CLIP_OUT)
				Mapfl++;
		}
		if (smGameStage[1])
		{
			mapY = (smGameStage[1]->GetHeight(x, z));
			if (y < mapY)
			{
				y = mapY;
				y += 8 << FLOATNS;
			}
			if (mapY > CLIP_OUT)
				Mapfl++;
		}
	}

	Mix_CodeVram();

	smRender.Color_R = 0;
	smRender.Color_G = 0;
	smRender.Color_B = 0;
	smRender.Color_A = 0;

	smRender.Color_R = -DarkLevel + BackColor_R;
	smRender.Color_G = -DarkLevel + BackColor_G;
	smRender.Color_B = -DarkLevel + BackColor_B;

	y += (32 << FLOATNS);

	if (anx <= 40 && dist <= 100)
		y -= ((110 - dist) << FLOATNS);

	TraceTargetPosi.x = x;
	TraceTargetPosi.y = y;
	TraceTargetPosi.z = z;

	if (AutoCameraFlag)
	{
		TraceCameraMain();

		x = TraceCameraPosi.x;
		y = TraceCameraPosi.y;
		z = TraceCameraPosi.z;
	}

	int ey = lpCurPlayer->pY + (32 * fONE);

	if (anx <= 40 && dist <= 100)
		ey += ((100 - dist) * fONE);

	ActionGameMode = FALSE;

	if (lpCurPlayer && lpCurPlayer->iLoadedMapIndex >= 0 && STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapType == MAPTYPE_Distorted)
	{
		x = lpCurPlayer->pX;
		y = STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->sActionCamera.sPosition.iY + 80 * fONE;
		z = STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->sActionCamera.sPosition.iZ * fONE;

		if (x < STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->sActionCamera.iLeftX * fONE)
			x = STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->sActionCamera.iLeftX * fONE;
		else if (x > STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->sActionCamera.iRightX * fONE)
			x = STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->sActionCamera.iRightX * fONE;

		MakeTraceMatrix(&eTrace, x, y, z, x, lpCurPlayer->pY, 326711 * fONE);

		ax = eTrace.AngX;
		ay = eTrace.AngY;
		smRender.OpenCameraPosi(x, y, z, &eTrace.eRotMatrix);

		ActionGameMode = TRUE;
	}
	else if (!DebugPlayer)
	{
		MakeTraceMatrix(&eTrace, x, y, z, lpCurPlayer->pX, ey, lpCurPlayer->pZ);

		ax = eTrace.AngX;
		ay = eTrace.AngY;
		smRender.OpenCameraPosi(x, y, z, &eTrace.eRotMatrix);
	}

	smRender.ClearLight();

	if (DarkLevel > 0)
	{
		ap = DarkLevel + (DarkLevel >> 2);

		if (STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapType == MAPTYPE_Dungeon ||
			STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapType == MAPTYPE_Distorted)
		{
			DarkLightRange = 400 * fONE;		//320
			ap = DarkLevel;
		}
		else
			DarkLightRange = 260 * fONE;		//220

		if (STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapType != MAPTYPE_Town)
			smRender.AddDynamicLight(lpCurPlayer->pX, lpCurPlayer->pY + 32 * fONE, lpCurPlayer->pZ, ap, ap, ap, 0, DarkLightRange);
	}

	DynLightApply();

	DrawSky(x, y, z, ax, ay, az);

	if (smRender.m_FogIsRend && smRender.m_FogMode)
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_FOGENABLE, TRUE);

	smRender.bApplyRendObjLight = TRUE;
	DrawPat3D(x, y, z, ax, ay, az);

	smRender.bApplyRendObjLight = FALSE;
	NumPoly = DisplayStage(x, y, z, ax, ay, az);

	smRender.bApplyRendObjLight = TRUE;
	DrawPat3D_Alpha();

	EFFECTGLOW->Draw();

	smRender.ClearObjLight();

	if (smRender.m_FogIsRend && smRender.m_FogMode)
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_FOGENABLE, FALSE);

	smRender.ClearLight();
	smRender.Color_A = 0;
	smRender.Color_R = 0;
	smRender.Color_G = 0;
	smRender.Color_B = 0;

	DrawPatShadow(x, y, z, ax, ay, az);

	RestoreInterfaceTexture();

	DrawEffect(x, y, z, ax, ay, az);
	cSin3D.Draw(x, y, z, ax, ay, az);
	DrawPat2D(x, y, z, ax, ay, az);

	if (g_IsDxProjectZoomIn)
		DrawFullZoomMap();
	else
	{
		if (cInterFace.sInterFlags.MapOnFlag)
		{
			if (MINIMAPBOX && MINIMAPBOX->IsOpen() == FALSE)
				MINIMAPBOX->Show();
		}
		else
		{
			if (MINIMAPBOX && MINIMAPBOX->IsOpen() == TRUE)
				MINIMAPBOX->Hide();
		}
	}
	if ((!MsTraceMode && MouseButton[0] == 0) || lpCurPlayer->sCharacterData.sSP.sMin > (lpCurPlayer->sCharacterData.sSP.sMax >> 2))
	{
		lpCurPlayer->MoveMode = cInterFace.sInterFlags.RunFlag;

		/*if (ActionGameMode)
			lpCurPlayer->MoveMode = ActionDashMode;*/
			// 横版地图模式
	}
	else
	{
		if (lpCurPlayer->sCharacterData.sSP.sMin == 0)
			lpCurPlayer->MoveMode = FALSE;
	}

	smRender.CloseCameraPosi();

	Disp_tx = MsSelPos.x - 32;
	Disp_ty = MsSelPos.y;

	if (g_IsDxProjectZoomIn <= 0)
		DrawGameState();
	else
		VirtualDrawGameState();

	IncTextureFrame();
}

char *CompCmdStr(char *strCmdLine, char *strword)
{
	int len, len2;
	int cnt, cnt2;

	len = lstrlen(strCmdLine);
	len2 = lstrlen(strword);

	for (cnt = 0; cnt < len - len2; cnt++)
	{
		for (cnt2 = 0; cnt2 < len2; cnt2++)
		{
			if (strword[cnt2] != strCmdLine[cnt + cnt2])
				break;
		}
		if (cnt2 == len2)
			return &strCmdLine[cnt + cnt2];
	}

	return NULL;
};

int	SetChatingLine(char *szMessage)
{
	hFocusWnd = hTextWnd;
	SetWindowText(hFocusWnd, szMessage);
	SetIME_Mode(TRUE);
	return TRUE;
}

//游戏消息
DWORD GameWindowMessage(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
{
	int stm, cnt;

	switch (messg)
	{
	case WM_KEYDOWN:
		if (GAMESCREEN->GetActiveScreenType() == SCREEN_World)
		{
			if (wParam == VK_RETURN && VRKeyBuff[wParam] == 0 && !sinMessageBoxShowFlag && !VRKeyBuff[VK_CONTROL])
				SetChatingLine("");

			if (wParam == VK_BACK && VRKeyBuff[wParam] == 0)
				SetMessageFrameSelect(TRUE);

			if (wParam == 'M' && VRKeyBuff[wParam] == 0)
				sinCheck_ShowHelpMap();

			if (dwYahooTime > dwPlayTime && dwYahooTime < (dwPlayTime + 60 * 1000))
			{
				if (wParam == VK_SPACE && VRKeyBuff[wParam] == 0)
				{
					if (lpCurPlayer && lpCurPlayer->psModelAnimation)
					{
						stm = sinGetStamina();
						cnt = (lpCurPlayer->sCharacterData.sSP.sMax * 3) / 100;

						if (lpCurPlayer->psModelAnimation->iType < 0x100 && stm>cnt)
						{
							if (lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Yahoo))
							{
								if (cnt > 0)
									sinSetStamina(stm - cnt);
							}
						}
					}
					VRKeyBuff[wParam] = 1;
					return FALSE;
				}
			}
			if (smRender.m_GameFieldView && !VRKeyBuff[wParam])
			{
				if (wParam == VK_ADD)
				{
					if (smRender.m_GameFieldViewStep < 22)
					{
						smRender.m_GameFieldViewStep++;
						RendSightSub(1);
					}
				}
				else if (wParam == VK_SUBTRACT)
				{
					if (smRender.m_GameFieldViewStep > 1)
					{
						smRender.m_GameFieldViewStep--;
						RendSightSub(1);
					}
				}
			}
			if (wParam == VK_F10 && VRKeyBuff[VK_F10] == 0)
			{
				SETTINGWINDOW->Show();
			}
			if (wParam == 'F' && VRKeyBuff['F'] == 0)
			{
				if (lpCurPlayer && lpCurPlayer->sCharacterData.iClass == CHARACTERCLASS_Assassin)
				{
					CHATGAMEHANDLE->AddChatBoxText(lpCurPlayer->SetShootingMode() ?
						"> Range Mode activated" : "> Melee Mode activated");
				}
			}
			if (SETTINGHANDLE->Get().bDebugMode)
			{
				if (wParam == VK_F9 && VRKeyBuff[VK_F9] == 0)
				{
					if (DisplayDebug)
						DisplayDebug = FALSE;
					else
						DisplayDebug = TRUE;
				}

				if (VRKeyBuff[VK_CONTROL] && wParam == 'E' && VRKeyBuff['E'] == 0)
				{
					lstrcpy(szSOD_String, "Score up 5000 pts");
					bSOD_StringColor[0] = 128;
					bSOD_StringColor[1] = 255;
					bSOD_StringColor[2] = 128;

					SOD_StringCount = 256;
				}

				if (wParam == VK_F11 && VRKeyBuff[wParam] == 0)
				{
					if (DispInterface == 0)
						DispInterface = TRUE;
					else
						DispInterface = FALSE;
				}

				if (wParam == VK_INSERT && VRKeyBuff[wParam] == 0 && VRKeyBuff[VK_CONTROL])
					SendAddStartPoint(lpCurPlayer->pX, lpCurPlayer->pZ);

				else if (wParam == VK_DELETE && VRKeyBuff[wParam] == 0 && VRKeyBuff[VK_CONTROL])
				{
					if (lpSelItem)
						SendDeleteStartPoint(lpSelItem->pX, lpSelItem->pZ);
				}
			}
		}
		break;
	}
	return TRUE;
}

#include "sinbaram\\HaQuestBoard.h"


int	StartQuest_Code(DWORD wCode)
{
	SetQuestBoard();

	if (InterfaceParty.PartyPosState == PARTY_NONE)
	{
		ShowQuest();
		InterfaceParty.quest_Sel_Progress();
	}

	return TRUE;
}

int EndQuest_Code(DWORD wCode)
{
	Record_LastQuest((WORD)wCode);
	SetQuestBoard();

	return TRUE;
}

float GetFPS()
{
	static float fps = 0.0f;
	static int frameCount = 0;
	static float currentTime = 0.0f;
	static float lastTime = 0.0f;

	frameCount++;

	currentTime = timeGetTime() * 0.001f;

	if (currentTime - lastTime > 1.0f)
	{
		fps = float(frameCount / (currentTime - lastTime));

		lastTime = currentTime;

		frameCount = 0;
	}

	return fps;
}
