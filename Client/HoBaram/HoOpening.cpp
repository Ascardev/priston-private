#include "StdAfx.h"
#include "..\\HoBaram\\HoTextFile.h"
#include "..\\HoBaram\\HoMinMax.h"
#include "..\\HoBaram\\HoNewParticle.h"
#include "..\\HoBaram\\HoNewParticleMgr.h"

extern char    Server_Name[64];

char	UserAccount[256];
char	UserPassword[256];

HoOpening::HoOpening()
{
	Stage = NULL;
	PatCamera = NULL;
	ObjCamera = NULL;

	LogoBlendValue = 0;
	LoginBlendValue = 0;

	StartConnectServerFlag = FALSE;
	WorkState = STATE_OPENING;

	MouseDownServerIndex = -1;
	CameraFrame = 0;
}
HoOpening::~HoOpening()
{
	//Close();
}

int HoOpening::Init()
{
	GameErrorValue = -1;
	ConnectErrorCount = 0;
	FocusWndFlag = FALSE;
	SetWindowText(hTextWnd, "");
	SendMessage( hTextWnd , EM_SETLIMITTEXT , 31, 0 );

	if (Load() == 0)
		return 0;

	LoginInputState = 0;
	ConnectError = ERROR_NONE;
	ServerWaitTimeCount = 0;
	StartQuitFlag = FALSE;

	WorkState = STATE_OPENING;
	StartConnectServerFlag = FALSE;
	ConnectServerSucessFlag = FALSE;

	FadeCurrentState = FADE_OUT;
	FadeNextState = FADE_OUT;

	LogoBlendValue = 0;
	LoginBlendValue = 0;
	ServerSelectBlendValue = 0;

	MidX = RESOLUTION_WIDTH >> 1;
	MidY = RESOLUTION_HEIGHT >> 1;

	smRender.SMMULT_PERSPECTIVE_HEIGHT = RENDCLIP_WIDE_MULT_PERSPECTIVE_HEIGHT;

	memset(UserAccount, 0, sizeof(UserAccount));
	memset(UserPassword, 0, sizeof(UserPassword));

	if (SETTINGHANDLE->Get().szLastAccount[0])
	{
		STRINGCOPY(UserAccount, SETTINGHANDLE->Get().szLastAccount);
		LoginInputState = 1;
	}

	TarDist = 400 * fONE;

	CaAngle.x = 100;
	CaAngle.y = 0;
	CaAngle.z = 0;

	SetFade();

	smInitColorZClip(0,0,0);

	smRender.Color_R = 40;
	smRender.Color_G = 0;
	smRender.Color_B = -30;
	smRender.Color_A = 0;
	smRender.ClearLight();

	CurrentWorkState = STATE_OPENING;
	NextWorkState    = STATE_OPENING;
	MouseDownServerIndex = -1;
	MouseDownFlag = FALSE;

	CameraFrame = 160;
	ChangeSky(MAPSKY_Forest_Morning);
	ChangeSky(MAPSKY_Forest_Noon);

	m_IsDrawOpening		     = TRUE;
	m_AutoCameraFrameTime	 = 50;
	m_ParticleSpawnTimeCount = 0;

	SetSize();

	startLogoAddX = 32;
	startAccountAddX = 140;
	startAccountAddY = 205;

	POINT3D pos;

	ZeroMemory(&pos,sizeof(POINT3D));

	g_NewParticleMgr.Start("Opening",pos);

	StopBGM();
	OpenBGM("StartImage\\Opening\\Intro.wav");
	PlayBGM();

	SetVolumeBGM(OpeningBgmVolume);

	return TRUE;
}
int HoOpening::Load()
{
	Stage = smSTAGE3D_ReadASE("StartImage\\Opening\\map\\stage.ASE");

	if(Stage != NULL)
	{
		Stage->Head = TRUE;

		PatCamera = smASE_Read("StartImage\\Opening\\king.ase");

		if (PatCamera)
			ObjCamera = PatCamera->GetObjectFromName("Box01");

		Stage->StageObject->AddObjectFile("StartImage\\Opening\\map\\st-ani01.ASE");
		Stage->StageObject->AddObjectFile("StartImage\\Opening\\map\\st-ani02.ASE");
		Stage->StageObject->AddObjectFile("StartImage\\Opening\\map\\st-ani03.ASE");
	}

	if(Stage == NULL || PatCamera == NULL) 
		return FALSE;

	GameLogo				= CreateTextureMaterial( "StartImage\\Opening\\window.tga"		, 0, 0, 0, SMMAT_BLEND_ALPHA );

	LoginBox				= CreateTextureMaterial( "StartImage\\Opening\\login_box.tga"	, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ServerSelect			= CreateTextureMaterial( "StartImage\\Opening\\serverselect.tga", 0, 0, 0, SMMAT_BLEND_ALPHA );

	ButtonLoginImage[0]		= CreateTextureMaterial( "StartImage\\Opening\\blogin_.tga"		, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ButtonLoginImage[1]		= CreateTextureMaterial( "StartImage\\Opening\\blogin.tga"		, 0, 0, 0, SMMAT_BLEND_ALPHA );

	ButtonSetingImage[0]	= CreateTextureMaterial( "StartImage\\Opening\\settings_.tga"	, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ButtonSetingImage[1]	= CreateTextureMaterial( "StartImage\\Opening\\settings.tga"	, 0, 0, 0, SMMAT_BLEND_ALPHA );

	ButtonQuitImage[0]		= CreateTextureMaterial( "StartImage\\Opening\\bexit_.tga"		, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ButtonQuitImage[1]		= CreateTextureMaterial( "StartImage\\Opening\\bexit.tga"		, 0, 0, 0, SMMAT_BLEND_ALPHA );

	PristonLogoImage		= CreateTextureMaterial( "StartImage\\Opening\\priston_txt.tga" , 0, 0, 0, SMMAT_BLEND_ALPHA );

	BlackBoxImage			= CreateTextureMaterial( "StartImage\\Login\\BlackBox.tga"		, 0	, TRUE ,FALSE , SMMAT_BLEND_ALPHA);
	WhiteBoxImage			= CreateTextureMaterial( "StartImage\\Login\\WhiteBox.tga"		, 0 , TRUE ,FALSE , SMMAT_BLEND_ALPHA);

	Message.Init();
	MessageBox.Init();

	ReadTextures();

	return TRUE; 
}

int		CaretCount = 0;
DWORD	End = 0;

#define	DISP_LOGIN_LEN		15

int HoOpening::Draw()
{
	FastFade();

	int x,y,z;
	int anx,any;

	anx = CaAngle.x & 0xFFF;
	any = CaAngle.y & 0xFFF;

	auto sPosition = GetMoveLocation(0, 0, -(TarDist), anx, any, 0);

	x = PatCameraWorldPos.x + sPosition.iX;

	y = PatCameraWorldPos.y + sPosition.iY;

	z = PatCameraWorldPos.z + sPosition.iZ;

	DrawOpeningSky(x, y, z, anx, any, 0);

	Stage->DrawStage(x,y,z,anx,any,0);

	DrawEffect(0, 0, 0, anx, any, 0);

	smRender.CloseCameraPosi();

	IncTextureFrame();

	if(NextWorkState == STATE_LOGIN_INPUT || NextWorkState == STATE_SERVER_SELECT|| NextWorkState == STATE_OPTION || NextWorkState == STATE_END)
	{
		dsDrawTexImage(GameLogo, startLogoX, startLogoY, 402, 440, LogoBlendValue);
		//dsDrawTexImage( PristonLogoImage,	423+startLogoX, 114+startLogoY, 128, 32,	LogoBlendValue);
	}

	if(NextWorkState == STATE_LOGIN_INPUT || CurrentWorkState == STATE_LOGIN_INPUT || NextWorkState == STATE_OPTION || (NextWorkState == STATE_SERVER_SELECT && CurrentWorkState != STATE_SERVER_SELECT))
	{
		dsDrawTexImage( LoginBox, startLogoX + 137 ,startLogoY + 205,128,99,LogoBlendValue);

		if(pCursorPos.x > startLogoX+ 147 && pCursorPos.y > startLogoY + 314 && pCursorPos.x < startLogoX+ 147 + 108 && pCursorPos.y < startLogoY + 314 + 36)
			dsDrawTexImage( ButtonLoginImage[1], startLogoX+ 147 ,startLogoY + 314,108,36,LogoBlendValue);
		else
			dsDrawTexImage( ButtonLoginImage[0], startLogoX+ 147 ,startLogoY + 314,108,36,LogoBlendValue);

		if(pCursorPos.x > startLogoX + 131 && pCursorPos.y > 20 && pCursorPos.x < startLogoX + 131 + 140 && pCursorPos.y < 20 + 40 )
			dsDrawTexImage( ButtonSetingImage[1], startLogoX + 131,20,140, 39, LogoBlendValue);
		else
			dsDrawTexImage( ButtonSetingImage[0], startLogoX + 131,20,140, 39, LogoBlendValue);


		if(pCursorPos.x > startLogoX+ 147 && pCursorPos.y > startLogoY + 352 && pCursorPos.x < startLogoX+ 147 + 108 && pCursorPos.y < startLogoY + 352 + 60)
			dsDrawTexImage( ButtonQuitImage[1], startLogoX+ 147 ,startLogoY + 352,108, 60, LogoBlendValue);
		else
			dsDrawTexImage( ButtonQuitImage[0], startLogoX+ 147 ,startLogoY + 352,108, 60, LogoBlendValue);
	}
	if (NextWorkState == STATE_OPTION || CurrentWorkState == STATE_OPTION)
	{

	}

	if(NextWorkState == STATE_SERVER_SELECT || NextWorkState == STATE_END || (CurrentWorkState == STATE_SERVER_SELECT && NextWorkState == STATE_LOGIN_INPUT))
	{
		dsDrawTexImage( ServerSelect , startLogoX + 161,startLogoY + 205,80,11,LogoBlendValue);

		if(pCursorPos.x > startLogoX+ 147 && pCursorPos.y > startLogoY + 352 && pCursorPos.x < startLogoX+ 147 + 108 && pCursorPos.y < startLogoY + 352 + 60)
			dsDrawTexImage( ButtonQuitImage[1], startLogoX+ 147 ,startLogoY + 352,108, 60, LogoBlendValue);
		else
			dsDrawTexImage( ButtonQuitImage[0], startLogoX+ 147 ,startLogoY + 352,108, 60, LogoBlendValue);

		char buffer[256];
		memset(buffer, 0, sizeof(buffer));

		DWORD Color;

		int selectHeight;
		int selectStartPosX;
		int selectStartPosY;

		if(UserServerListInfoCount != 0)
			selectHeight = 90/UserServerListInfoCount;

		selectStartPosX = 140 + startLogoX;
		selectStartPosY = 240 + startLogoY+(selectHeight-12)/2;

		for(int index = 0; index < UserServerListInfoCount; index++)
		{
			STRINGFORMAT(buffer,"%s", UserServerListInfo[index].szServerName);

			POINT startServerText;

			if(MouseDownServerIndex != index)
			{
				startServerText.x = selectStartPosX+65-(lstrlen(buffer)*6/2);
				startServerText.y = selectStartPosY+index*selectHeight;
			}
			else
			{
				startServerText.x = selectStartPosX+65-(lstrlen(buffer)*6/2);
				startServerText.y = selectStartPosY+index*selectHeight;
			}
			dsTextLineOut(0,startServerText.x+1,startServerText.y+1,buffer,lstrlen(buffer),D3DCOLOR_XRGB(0,0,0));

			if(MouseDownServerIndex == -1)
			{
				if(pCursorPos.x > selectStartPosX && (pCursorPos.y > selectStartPosY+index*selectHeight) && pCursorPos.x < (selectStartPosX + 140)  && (pCursorPos.y < (selectStartPosY+index*selectHeight+12)) && ConnectError == ERROR_NONE && !StartConnectServerFlag)
					Color = D3DCOLOR_XRGB(250,200,0);
				else
					Color = D3DCOLOR_XRGB(190,190,190);
			}
			else
			{
				if(MouseDownServerIndex == index)
					Color = D3DCOLOR_XRGB(250,200,0);
				else
					Color = D3DCOLOR_XRGB(190,190,190);
			}
			dsTextLineOut(0,startServerText.x,startServerText.y,buffer,lstrlen(buffer),Color);
		}
	}
	DrawFade();

	char buffer[256];
	ZeroMemory(buffer,sizeof(buffer));

	if (GAME_VERSION < 1000)
	{
		float Version = (float)GAME_VERSION / 100;
		STRINGFORMAT(buffer,"%s%2.2f%s", "Ver: ",Version,"b");
	}
	else 
	{
		STRINGFORMAT(buffer,"Game Version: %d", GAME_VERSION);
	}

	dsTextLineOut(0, RESOLUTION_WIDTH - 120,20,buffer,lstrlen(buffer),D3DCOLOR_XRGB(255,255,255));

	if(CurrentWorkState == STATE_LOGIN_INPUT && NextWorkState == STATE_LOGIN_INPUT && ScreenBlendValue <= 100)
	{
		if(LoginBlendValue >= 255)
		{
			if(FocusWndFlag == FALSE)
			{
				FocusWndFlag = TRUE;
				hFocusWnd = hTextWnd;
			}

			if(StartConnectServerFlag == FALSE && ConnectError == ERROR_NONE)
			{
				if(pCursorPos.x > (startLogoX+startAccountAddX+10) && pCursorPos.x < (startLogoX+startAccountAddX+10+95) && pCursorPos.y > (startLogoY+startAccountAddY+20) && pCursorPos.y < (startLogoY+startAccountAddY+23+14) && MouseButton[0])
				{
					if(LoginInputState == 1)
					{
						LoginInputState = 0;
						SetWindowText(hFocusWnd, UserAccount);
						SendMessage(hTextWnd, EM_SETSEL, lstrlen(UserAccount), lstrlen(UserAccount)+1);
					}
				}
				if(pCursorPos.x > (startLogoX+startAccountAddX+10) && pCursorPos.x < (startLogoX+startAccountAddX+10+95) && pCursorPos.y > (startLogoY+startAccountAddY+70) && pCursorPos.y < (startLogoY+startAccountAddY+73+14) && MouseButton[0])
				{
					if(LoginInputState == 0)
					{
						LoginInputState = 1;
						SetWindowText(hFocusWnd, UserPassword);
						SendMessage(hTextWnd, EM_SETSEL, lstrlen(UserPassword), lstrlen(UserPassword)+1);
					}
				}
			}
			if(hFocusWnd && ConnectError == ERROR_NONE && StartConnectServerFlag==FALSE)
			{
				if(LoginInputState == 0)
				{
					GetWindowText(hFocusWnd, UserAccount, sizeof(UserAccount));
					KeyFilter(UserAccount);

				}	
				else if(LoginInputState == 1)
				{
					GetWindowText(hFocusWnd, UserPassword, sizeof(UserPassword));
					KeyFilter(UserPassword);
				}
			}

			if(hFocusWnd)
				SendMessage(hFocusWnd, EM_GETSEL, NULL, (LPARAM)&End);

			DWORD Color = D3DCOLOR_XRGB(255,255,255);

			if(hFocusWnd)
			{
				if(CaretCount < 16)
				{
					if (End>DISP_LOGIN_LEN) 
						End=DISP_LOGIN_LEN;

					if(LoginInputState == 0)
						dsTextLineOut(0,startLogoX+startAccountAddX+11+End*6+1,startLogoY+startAccountAddY+23, "|", 1,Color);
					else if(LoginInputState == 1)
						dsTextLineOut(0,startLogoX+startAccountAddX+11+End*6+1,startLogoY+startAccountAddY+73, "|", 1,Color);
				}

				CaretCount++;
				if(CaretCount > 32)
					CaretCount = 0;
			}			

			int sp,len;

			sp = 0;
			len = lstrlen(UserAccount);
			if ( len>DISP_LOGIN_LEN )
			{
				sp = len-DISP_LOGIN_LEN;
				len -= sp;
			}
			dsTextLineOut(0,startLogoX+startAccountAddX+12, startLogoY+startAccountAddY+23, UserAccount+sp,len,Color);
			len = lstrlen(UserPassword);
			if (len > DISP_LOGIN_LEN)
				len = DISP_LOGIN_LEN;

			for(int count = 0; count < len; count++)
				dsTextLineOut(0,startLogoX+startAccountAddX+12+count*6, startLogoY+startAccountAddY+73, "*", 1,Color);
		}
	}
	if(StartConnectServerFlag && ConnectError == ERROR_NONE)
		CTITLEBOX->RenderTextMiddle("Establishing Connection....");

	if(ConnectError == ERROR_CONNECT)
	{
		StartConnectServerFlag = FALSE;
		CTITLEBOX->RenderTextMiddle("Unable to connect to Server");
	}
	else if(ConnectError == ERROR_NO_ACCOUNT)
		CTITLEBOX->RenderTextMiddle("     Please re-enter ID    ");
	else if(ConnectError == ERROR_NO_PASSWORD)
		CTITLEBOX->RenderTextMiddle(" Please re-enter Password  ");
	else if(ConnectError == ERROR_NO_BETA_TESTER)
		CTITLEBOX->RenderTextMiddle(" Blocked ID, please contact our support ");
	else if(ConnectError == ERROR_NO_ACCOUNT_IN)
		CTITLEBOX->RenderTextMiddle("  ID is already logged in  ");
	else if(ConnectError == ERROR_NO_VERSION)
		CTITLEBOX->RenderTextMiddle( "  Version does not match   ");
	else if(ConnectError == ERROR_NO_LIMIT)
		CTITLEBOX->RenderTextMiddle("      Server is full       ");
	else if(ConnectError == ERROR_NO_SERVER_CONNECT)
		CTITLEBOX->RenderTextMiddle("Connection lost with Server");
	else if(ConnectError == ERROR_NO_USE_DATE_OVER)
		CTITLEBOX->RenderTextMiddle("   Available time expired  ");
	else if(ConnectError == ERROR_NO_USE_TIME_OVER)
		CTITLEBOX->RenderTextMiddle("   Available time expired  ");
	else if(ConnectError == ERROR_DELETE_ACCOUNT_NOTIFY)
		CTITLEBOX->RenderTextMiddle(" Deleting account on server ");
	else if(ConnectError == ERROR_SERVER_TRAFFIC_BUSY)
		CTITLEBOX->RenderTextMiddle("Server overload, please try again later.");
	else if(ConnectError == ERROR_SERVER_WAIT_MOMNENT)
		CTITLEBOX->RenderTextMiddle("Server overload, please try again later.");
	else if(ConnectError == ERROR_THIRD_CONNECT)
		CTITLEBOX->RenderTextMiddle("     Account has been stopped, please contact the wizard customer service    ");
	else if(ConnectError == ERROR_HAN_PASSWORD)
		CTITLEBOX->RenderTextMiddle("Personality characters are not allowed in the password.");
	else if(ConnectError == ERROR_12YEARS)
		CTITLEBOX->RenderTextMiddle("Users under 12 years of age can not play the game.");
	else if(ConnectError == ERROR_HOMEAGREE)
		CTITLEBOX->RenderTextMiddle("Agree with the wizard of the wizard can play the game.");

	return TRUE;
}


HANDLE	hHoLoginThread =0;

DWORD WINAPI HoLoginThreadProc( void *pInfo )
{
	HoOpening	*lpHoOpening = (HoOpening *)pInfo;

	if (SOCKETL == NULL)
	{
		GAMESOCKET->ConnectLogin(SETTINGHANDLE->Get().szDataServerIP, SETTINGHANDLE->Get().dwDataServerPort);

		if(SOCKETL)
		{
			ServerUserCharacterInfo = NULL;
			DownServerListInfo = NULL;
			ServerLoginError = NULL;
			lpHoOpening->ServerWaitTimeCount = 0;

			PacketLoginUser sPacket;
			sPacket.iLength = sizeof(PacketLoginUser);
			sPacket.iHeader = PKTHDR_LoginUser;
			sPacket.dwUnk[0] = sPacket.dwUnk[1] = sPacket.dwUnk[2] = 0;
			STRINGCOPY(sPacket.szUserID, UserAccount);
			STRINGCOPY(sPacket.szPassword, UserPassword);

			sPacket.uWidthScreen = GetSystemMetrics(SM_CXSCREEN);
			sPacket.uHeightScreen = GetSystemMetrics(SM_CYSCREEN);

			sPacket.iSystemOS = GAMESYSTEMHANDLE->GetSystemOS();

			//PC Name
			sPacket.szPCName[0] = 0;
			DWORD dwSize = 32;
			GetComputerNameA(sPacket.szPCName, &dwSize);

			// Mac Address
			{
				UUID uuid;

				// Ask OS to create UUID
				UuidCreateSequential(&uuid);

				// Bytes 2 through 7 inclusive 
				STRINGFORMAT(sPacket.szMacAddr, "%02X-%02X-%02X-%02X-%02X-%02X",
					uuid.Data4[2], uuid.Data4[3], uuid.Data4[4], uuid.Data4[5], uuid.Data4[6], uuid.Data4[7]);
			}

			//HD Serial
			{
				char szHD[4];

				szHD[0] = 'C';
				szHD[1] = ':';
				szHD[2] = '\\';
				szHD[3] = 0;

				GetVolumeInformationA(szHD, NULL, 0, &sPacket.dwSerialHD, NULL, NULL, NULL, 0);

				//Video Name
				STRINGCOPY(sPacket.szVideoName, GRAPHICENGINE->GetVideoName().c_str());
			}

			SENDPACKETL(&sPacket);
		}
		else
		{
			lpHoOpening->ConnectError = ERROR_CONNECT;
			lpHoOpening->StartConnectServerFlag = FALSE;
		}
	}

	hHoLoginThread = 0;

	ExitThread( TRUE );
	return TRUE;
}

int HoOpening::LoginDataServer()
{
	DWORD dwHoLoginThreadId;

	if (!hHoLoginThread)
	{
		hHoLoginThread = CreateThread(NULL , 0, HoLoginThreadProc , this , 0, &dwHoLoginThreadId);

		PlayWav2(13-1);
		StartConnectServerFlag = TRUE;
		return TRUE;
	}
	return FALSE;
}

int HoOpening::LoginGameServer(int serverIndex)
{
	PlayWav2(13-1);

	BOOL bConnect = GAMESOCKET->ConnectGame(UserServerListInfo[serverIndex].szServerIp1, UserServerListInfo[serverIndex].dwServerPort1);

	if (bConnect)
	{
		lstrcpy(Server_Name, UserServerListInfo[serverIndex].szServerName);
		StartConnectServerFlag = TRUE;
	}
	else
	{
		ConnectError = ERROR_CONNECT;
	}

	return TRUE;
}

// ¹ýÂË×Ö·û
int HoOpening::KeyFilter(char *message)
{
	if(message == NULL || hFocusWnd == NULL)
		return FALSE;

	if(lstrlen(message) >= 31 && message[30] != '\t')
	{
		message[30] = 0;
		SetWindowText(hFocusWnd, 0);
		SetWindowText(hFocusWnd, message);
		SendMessage(hFocusWnd, EM_SETSEL, lstrlen(message)+1, lstrlen(message)+1);
	}

	for(int index = 0; index < lstrlen(message); index++)
	{
		if(message[index] =='\t')
		{
			message[index] = 0;
			SetWindowText(hFocusWnd, 0);

			if(LoginInputState == 0)
			{
				LoginInputState = 1;
				SetWindowText(hFocusWnd, UserPassword);
				SendMessage(hTextWnd, EM_SETSEL, lstrlen(UserPassword)+1, lstrlen(UserPassword)+1);
			}
			else if(LoginInputState == 1)
			{
				LoginInputState = 0;
				SetWindowText(hFocusWnd, UserAccount);
				SendMessage(hTextWnd, EM_SETSEL, lstrlen(UserAccount)+1, lstrlen(UserAccount)+1);
			}
		}
		if(message[index] == ' ' || message[index] == '@'|| message[index] == '#' || message[index] == '$' || message[index] == '%' || message[index] == '^' || message[index] == '&' || message[index] == '*')
		{
			message[index] = 0;
			SetWindowText(hFocusWnd, message);
			SendMessage(hTextWnd, EM_SETSEL, lstrlen(message)+1, lstrlen(message)+1);
			break;
		}
	}
	return TRUE;
};
int HoOpening::MainFadeIn()
{
	if(FadeNextState == FADE_IN)
	{
		ScreenBlendValue -= 2;
		if(ScreenBlendValue < 0)
			ScreenBlendValue = 0;

		if(ScreenBlendValue <= 0 )
		{
			ScreenBlendValue = 0;
			FadeCurrentState = FADE_IN;
			FadeNextState = FADE_IN;
		}
	}
	return TRUE;
}
int HoOpening::MainFadeOut()
{
	if(FadeNextState == FADE_OUT)
	{
		if(ScreenBlendValue < 255)
		{
			OpeningBgmVolume -= 2;
			if(OpeningBgmVolume < 0)
				OpeningBgmVolume = 0;
			ScreenBlendValue += 3;
		}

		if(ScreenBlendValue >= 255)
		{
			ScreenBlendValue = 255;
			LogoBlendValue = 255;
			LoginBlendValue = 255;
			FadeCurrentState = FADE_OUT;
			FadeNextState = FADE_OUT;
		}
	}
	return TRUE;
}

int HoOpening::FastFade()
{
	if((FadeNextState == FADE_IN && LoginBlendValue < 255) || (FadeNextState == FADE_OUT && LoginBlendValue > 0))
	{

		static bool fastBlendFlag = false;
		for(int index = 0; index < 256; index++)
		{
			if(VRKeyBuff[index] == TRUE)
			{
				fastBlendFlag = true;
				break;
			}
		}

		if(MouseDownFlag == FALSE)
		{
			if(MouseButton[0] && fastBlendFlag == false)
			{
				fastBlendFlag = true;
				MouseDownFlag = TRUE;
			}
		}

		if(fastBlendFlag)
		{
			if(FadeNextState == FADE_IN)
			{
				if( (CurrentWorkState == STATE_OPENING && NextWorkState == STATE_OPENING) || (CurrentWorkState == STATE_OPENING && NextWorkState == STATE_LOGIN_INPUT) )
				{
					LogoBlendValue = 255;
					ScreenBlendValue = 0;
					FadeCurrentState = FADE_IN;

					LoginBlendValue = 255;
					CurrentWorkState = STATE_LOGIN_INPUT;
					NextWorkState = STATE_LOGIN_INPUT;
				}				
			}
			else if(FadeNextState == FADE_OUT)
			{
				LogoBlendValue = 0;
				LoginBlendValue = 0;
				ScreenBlendValue = 255;
				OpeningBgmVolume = 0;
				FadeCurrentState = FADE_OUT;

			}
			fastBlendFlag = false;
		}
	}
	return TRUE;
}

int HoOpening::DrawFade()
{
	if(ScreenBlendValue >= 0 && ScreenBlendValue <= 255)
		dsDrawTexImage(BlackBoxImage,0, 0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, ScreenBlendValue);

	return TRUE;
}

int HoOpening::MainFade()
{
	if((FadeNextState == FADE_IN) || (FadeNextState == FADE_OUT))
	{
		if(FadeCurrentState != FadeNextState)
		{
			if(FadeNextState == FADE_IN)
				MainFadeIn();
			else
			{
				SetVolumeBGM(OpeningBgmVolume);
				MainFadeOut();
			}
		}
	}
	return TRUE;
}

void HoOpening::SetFade()
{
	if(FadeCurrentState == FADE_OUT)
	{
		FadeNextState = FADE_IN;
		ScreenBlendValue = 254;
		OpeningBgmVolume = GetVolumeBGM(SETTINGHANDLE->Get().iMusicVolume);
	}
	else
	{
		FadeNextState = FADE_OUT;
		ScreenBlendValue = 1;
	}
}


void HoOpening::Close()
{
	DELET(Stage);
	DELET(PatCamera);

	BackColor_R = 0;
	BackColor_G = 0;
	BackColor_B = 0;

	BackColor_mR = 0;
	BackColor_mG = 0;
	BackColor_mB = 0;

	InitSky();
}

int HoOpening::Main()
{
	if(MouseButton[0] == FALSE)
		MouseDownFlag = FALSE;

	MainEffect();

	MainSky();

	CameraFrame += 10;

	if (CameraFrame >= PatCamera->MaxFrame)
		CameraFrame = 0;

	smMATRIX *mWorld;

	mWorld = &ObjCamera->mWorld;

	AnimObjectTree(ObjCamera, CameraFrame, 0, 0, 0);

	PatCameraWorldPos.x = mWorld->_41;
	PatCameraWorldPos.z = mWorld->_42;
	PatCameraWorldPos.y = mWorld->_43;

	if(ConnectError != ERROR_NONE)
	{
		if(ConnectErrorCount >= 160)
		{
			MouseDownServerIndex = -1;
			bool errorEndFlag = false;

			if(MouseButton[0] || MouseDblClick)
				errorEndFlag = true;

			for(int index = 0; index < 256; index++)
			{
				if(VRKeyBuff[index] == TRUE)
				{
					errorEndFlag = true;
					break;
				}
			}
			if(ConnectErrorCount >= 250)
				errorEndFlag = true;

			if(errorEndFlag)
			{
				ConnectError = ERROR_NONE;
				FocusWndFlag = FALSE;
				ConnectErrorCount = 0;
			}
		}
		ConnectErrorCount++;
	}

	MainFade();

	if(CurrentWorkState == STATE_OPENING && NextWorkState == STATE_OPENING)
	{
		if(CameraFrame == 35000)
			NextWorkState = STATE_LOGIN_INPUT;
	}
	if(CurrentWorkState == STATE_OPENING && NextWorkState == STATE_LOGIN_INPUT)
	{
		if(FadeNextState == FADE_IN)
		{
			LogoBlendValue += 1;
			if(LogoBlendValue >= 255)
				LogoBlendValue = 255;

			if(LogoBlendValue >= 255)
			{
				LoginBlendValue += 1;
				if (LoginBlendValue >= 255)
				{
					LoginBlendValue = 255;
					CurrentWorkState = STATE_LOGIN_INPUT;
				}
			}
		}
	}
	if (CurrentWorkState == STATE_OPTION && NextWorkState == STATE_OPTION)
	{
		if (!SETTINGWINDOW->IsOpen())
		{
			CurrentWorkState = STATE_LOGIN_INPUT;
			NextWorkState    = STATE_LOGIN_INPUT;
		}
	}
	if(CurrentWorkState == STATE_LOGIN_INPUT && NextWorkState == STATE_LOGIN_INPUT && (LoginBlendValue >= 255) && (ScreenBlendValue <= 0) && StartConnectServerFlag == FALSE && ConnectError == ERROR_NONE)
	{
		if(FocusWndFlag && hFocusWnd == NULL && ConnectServerSucessFlag == FALSE && ConnectError == ERROR_NONE)
			LoginDataServer();

		int downFlag = -1;

		if(MouseDownFlag == FALSE)
		{
			if(MouseButton[0])
			{
				// µÇÂ¼°´Å¥
				if(pCursorPos.x > startLogoX+ 147 && pCursorPos.y > startLogoY + 314 && pCursorPos.x < startLogoX+ 147 + 108 && pCursorPos.y < startLogoY + 314 + 36)
				{
					MouseDownFlag = TRUE;
					hFocusWnd = NULL;
				}
				// ÉèÖÃ°´Å¥
				else if(pCursorPos.x > startLogoX + 131 && pCursorPos.y > 20 && pCursorPos.x < startLogoX + 131 + 140 && pCursorPos.y < 20 + 40 )
				{
					MouseDownFlag = TRUE;
					PlayWav2(4-1);

					CurrentWorkState	= STATE_OPTION;
					NextWorkState		= STATE_OPTION;

					SETTINGWINDOW->Show();
					

				}
				// ÍË³ö°´Å¥
				else if(pCursorPos.x > startLogoX+ 147 &&  pCursorPos.y > startLogoY + 352 && pCursorPos.x < startLogoX+ 147 + 108 && pCursorPos.y < startLogoY + 352 + 60)
				{
					MouseDownFlag = TRUE;
					StartQuitFlag = TRUE;
					SetFade();
					PlayWav2(4-1);
				}
			}
		}
	}
	if( CurrentWorkState == STATE_SERVER_SELECT && NextWorkState == STATE_SERVER_SELECT)
	{
		int selectHeight;
		int selectStartPosX;
		int selectStartPosY;

		if(UserServerListInfoCount != 0)
			selectHeight = 90/UserServerListInfoCount;

		selectStartPosX = 140 + startLogoX;
		selectStartPosY = 240 + startLogoY+(selectHeight-12)/2;

		for(int index = 0; index < UserServerListInfoCount; index++)
		{
			if( pCursorPos.x > (selectStartPosX) && (pCursorPos.y > selectStartPosY+index*selectHeight) && pCursorPos.x < (selectStartPosX+140)  && (pCursorPos.y < (selectStartPosY+index*selectHeight+12)) && ConnectError == ERROR_NONE && !StartConnectServerFlag)
			{
				if(MouseButton[0] && MouseDownFlag == FALSE)
				{
					MouseDownFlag = TRUE;
					MouseDownServerIndex = index;
					LoginGameServer(index);
				}
			}
		}
	}

	if(CurrentWorkState == STATE_SERVER_SELECT && NextWorkState == STATE_SERVER_SELECT)
	{
		BOOL flag=FALSE;
		if(ConnectError == ERROR_NONE && !StartConnectServerFlag && StartQuitFlag == FALSE)
		{
			if(MouseDownFlag == FALSE)
			{
				if(MouseButton[0])
				{
					if(pCursorPos.x > startLogoX+ 147 && pCursorPos.y > startLogoY + 352 && pCursorPos.x < startLogoX+ 147 + 108 && pCursorPos.y < startLogoY + 352 + 60)
					{
						flag = TRUE;
						MouseDownFlag = TRUE;
					}
				}
			}
		}

		if(!SOCKETL && GameErrorValue == 0)
		{
			NextWorkState = STATE_LOGIN_INPUT;
			ConnectServerSucessFlag = FALSE;
			GAMESOCKET->DisconnectFull();
			ConnectError = ERROR_NO_SERVER_CONNECT;
		}
		if(flag)
		{
			PlayWav2(4-1);

			FocusWndFlag = FALSE;
			NextWorkState = STATE_LOGIN_INPUT;
			CurrentWorkState = STATE_LOGIN_INPUT;
			ConnectServerSucessFlag = FALSE;
			GAMESOCKET->DisconnectFull();
		}
	}

	if(StartConnectServerFlag)
	{
		if(ConnectError != ERROR_NONE)
		{
			StartConnectServerFlag = FALSE;
			ServerWaitTimeCount = 0;
		}

		if(ServerLoginError)
		{
			if (CurrentWorkState == STATE_LOGIN_INPUT
				&& NextWorkState == STATE_LOGIN_INPUT)
				GAMESOCKET->DisconnectFull();

			if (CurrentWorkState == STATE_SERVER_SELECT
				&& NextWorkState == STATE_SERVER_SELECT)
				GAMESOCKET->SocketClose(SOCKETG);


			if(ServerLoginError->WParam == 0)
				ConnectError = ERROR_CONNECT;
			else if(ServerLoginError->WParam == -1)
				ConnectError = ERROR_NO_ACCOUNT;
			else if(ServerLoginError->WParam == -2)
				ConnectError = ERROR_NO_PASSWORD;
			else if(ServerLoginError->WParam == -3)
				ConnectError = ERROR_NO_BETA_TESTER;
			else if(ServerLoginError->WParam == -4)
				ConnectError = ERROR_NO_ACCOUNT_IN;
			else if(ServerLoginError->WParam == -5)
				ConnectError = ERROR_NO_USE_DATE_OVER;
			else if(ServerLoginError->WParam == -6)
				ConnectError = ERROR_NO_USE_TIME_OVER;
			else if(ServerLoginError->WParam == -8)
				ConnectError = ERROR_DELETE_ACCOUNT_NOTIFY;
			else if(ServerLoginError->WParam == -16)
				ConnectError = ERROR_SERVER_TRAFFIC_BUSY;
			else if(ServerLoginError->WParam == -17)
				ConnectError = ERROR_SERVER_WAIT_MOMNENT;
			else if(ServerLoginError->WParam == -18)
				ConnectError = ERROR_THIRD_CONNECT;
			else if(ServerLoginError->WParam == -19)
				ConnectError = ERROR_HAN_PASSWORD;
			else if(ServerLoginError->WParam == -12)
				ConnectError = ERROR_12YEARS;
			else if(ServerLoginError->WParam == -13)
				ConnectError = ERROR_HOMEAGREE;

			StartConnectServerFlag = FALSE;
			ServerWaitTimeCount = 0;
			ServerLoginError = NULL;
		}

		ServerWaitTimeCount++;
		if(ServerWaitTimeCount >= 3000)
		{
			ServerWaitTimeCount = 0;
			ConnectError = ERROR_CONNECT;
			StartConnectServerFlag = FALSE;
			ConnectServerSucessFlag = FALSE;
		}

		if( CurrentWorkState == STATE_LOGIN_INPUT && NextWorkState == STATE_LOGIN_INPUT)
		{
			if( ServerUserCharacterInfo && DownServerListInfo && ConnectError == ERROR_NONE && GameErrorValue == 0)
			{
				StartConnectServerFlag = FALSE;
				ConnectServerSucessFlag = TRUE;
				CurrentWorkState = STATE_SERVER_SELECT;
				NextWorkState = STATE_SERVER_SELECT;
				GameErrorValue = -1;
			}
		}

		if( CurrentWorkState == STATE_SERVER_SELECT && NextWorkState == STATE_SERVER_SELECT) 
		{
			if( ConnectError == ERROR_NONE && GameErrorValue == 0)
			{
				StartConnectServerFlag = FALSE;
				SetFade();
				NextWorkState = STATE_END;
				GameErrorValue = -1;
			}
		}

		if(GameErrorValue != 0)
		{
			if(GameErrorValue == 1)
			{
				GAMESOCKET->DisconnectFull();
				ConnectError = ERROR_NO_VERSION;
				StartConnectServerFlag = FALSE;
				GameErrorValue = -1;
			}

			if(GameErrorValue == 2)
			{
				if(CurrentWorkState == STATE_LOGIN_INPUT && NextWorkState == STATE_LOGIN_INPUT)
					GAMESOCKET->DisconnectFull();

				if (CurrentWorkState == STATE_SERVER_SELECT && NextWorkState == STATE_SERVER_SELECT)
					GAMESOCKET->SocketClose(SOCKETG);

				ConnectError = ERROR_NO_LIMIT;
				StartConnectServerFlag = FALSE;
				GameErrorValue = -1;
			}
		}
	}

	if(ConnectServerSucessFlag)
	{
		if(FadeCurrentState == FADE_OUT && FadeNextState == FADE_OUT)
		{
			STRINGCOPY(SETTINGHANDLE->Get().szLastAccount, UserAccount);
			SETTINGHANDLE->Write();

			SetWindowText(hTextWnd, NULL);
			SendMessage(hTextWnd , EM_SETLIMITTEXT , 80, 0 );

			StopBGM();
			return 2;
		}
	}
	if(StartQuitFlag)
	{
		if(FadeCurrentState == FADE_OUT && FadeNextState == FADE_OUT)
			quit = 1;
	}

	return 1;	
}
void HoOpening::SetSize()
{
	m_AddWidth  = (RESOLUTION_WIDTH - 800)>>1;
	m_AddHeight = (RESOLUTION_HEIGHT - 600)>>1;

	startLogoX = 200 + m_AddWidth;
	startLogoY = 100  + m_AddHeight;
}