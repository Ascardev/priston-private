#include "StdAfx.h"
#include "DXGraphicsEngine.h"

namespace DX
{
	GraphicsEngine::GraphicsEngine()
	{
		MEMEMPTY(&m_sResolution);
		MEMEMPTY(&m_d3dPP);
		MEMEMPTY(&m_d3dCaps);
		MEMEMPTY(&m_d3dm);
	}
	GraphicsEngine::~GraphicsEngine()
	{
		RELEASE(m_pD3D);
	}
	void GraphicsEngine::Log(const char *pszFormat,...)
	{
		va_list vl;

		Logger Loger;
		char szError[16384];

		ZeroMemory(szError, sizeof(szError));

		va_start(vl,pszFormat);
		_vsnprintf_s(szError,_countof(szError),_TRUNCATE,pszFormat,vl);
		va_end(vl);

		char szMessage[4096];

		STRINGFORMAT(szMessage,"[%08X][%s] %s\r\n",m_hr,Loger.ResultToString(m_hr),szError);

		FILE *fp;

		CreateDirectoryA("save\\logs",NULL);

		if (fopen_s(&fp,"save\\logs\\init.log","a") == 0)
		{
			fputs(szMessage,fp);
			fflush(fp);
			fclose(fp);
		}
	}
	void GraphicsEngine::Error(const char *pszFormat,...)
	{
		va_list vl;

		Logger Loger;
		char szError[16384];

		va_start(vl,pszFormat);
		_vsnprintf_s(szError,_countof(szError),_TRUNCATE,pszFormat,vl);
		va_end(vl);

		char szMessage[4096];

		STRINGFORMAT(szMessage,"[%08X][%s] %s\r\n",m_hr,Loger.ResultToString(m_hr),szError);

		MessageBoxA(0,szMessage,"Graphic Engine Error!",MB_OK|MB_ICONEXCLAMATION);

		Log(szError);
	}
	BOOL GraphicsEngine::InitD3D(HWND hWnd)
	{
		// Create the Direct3D interface
		if (!CreateInterface())
			return FALSE;

		//Create a Device class
		if (!CreateDevice(hWnd))
			return FALSE;

		m_pGraphicsDevice = std::make_shared<GraphicsDevice>(m_pDevice);

		//m_pGlow = std::make_shared<Glow>(m_pGraphicsDevice);

		return TRUE;
	}
	BOOL GraphicsEngine::CreateInterface()
	{
		m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

		if (FAILED(m_hr = m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&m_d3dm)))
		{
			//Error
			Error("Create Direct3D 9 Error");
			return FALSE;
		}
		// Window mode
		BOOL bWindowed = SETTINGHANDLE->Get().bWindowed;
		// Bit Depth is 32 or 16
		DWORD dwBitDepth = SETTINGHANDLE->Get().dwBitDepth == 16 ? 16 : 32;
		// Support 32 or 16 bits BitDepth?
		if(FAILED(m_hr = m_pD3D->CheckDeviceType(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,m_d3dm.Format,dwBitDepth == 32 ? D3DFMT_X8R8G8B8 : D3DFMT_X4R4G4B4,bWindowed)))
		{
			dwBitDepth = dwBitDepth == 32 ? 16 : 32;

			if(FAILED(m_hr = m_pD3D->CheckDeviceType(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,m_d3dm.Format,dwBitDepth == 32 ? D3DFMT_X8R8G8B8 : D3DFMT_X4R4G4B4,bWindowed)))
			{
				Error("Your device must support a 16 or 32 bit Back Buffer");
				return FALSE;
			}
		}

		if (dwBitDepth == 32)
		{
			Log("32 bit Back Buffer");
			m_d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
		}
		else if (dwBitDepth == 16)
		{
			Log("16 bit Back Buffer");
			m_d3dPP.BackBufferFormat = D3DFMT_X4R4G4B4;
		}
		else
		{
			Log("Unknown Back Buffer Format");
			return FALSE;
		}

		m_d3dPP.AutoDepthStencilFormat = D3DFMT_D24S8;

		if (FAILED(m_hr = m_pD3D->CheckDeviceFormat(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,m_d3dm.Format,D3DUSAGE_DEPTHSTENCIL,D3DRTYPE_SURFACE,m_d3dPP.AutoDepthStencilFormat)))
		{
			m_d3dPP.AutoDepthStencilFormat = D3DFMT_D15S1;

			if (FAILED(m_hr = m_pD3D->CheckDeviceFormat(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,m_d3dm.Format,D3DUSAGE_DEPTHSTENCIL,D3DRTYPE_SURFACE,m_d3dPP.AutoDepthStencilFormat)))
			{
				Error("Your device must support a 16(1s) or 32(8s) bit DepthStencil Buffer");
				return FALSE;
			}
			else
				Log("D15S1 DepthStencil Buffer");
		}
		else
			Log("D24S8 DepthStencil Buffer");

		//MultiSample
		m_d3dPP.MultiSampleType		= D3DMULTISAMPLE_NONE;
		m_d3dPP.MultiSampleQuality	= 0;

		//¿¹¾â³Ý
		if (SETTINGHANDLE->Get().bAntiAliasing)
		{
			D3DMULTISAMPLE_TYPE d3daMultipleSampleType[] = {
				D3DMULTISAMPLE_16_SAMPLES,
				D3DMULTISAMPLE_15_SAMPLES,
				D3DMULTISAMPLE_14_SAMPLES,
				D3DMULTISAMPLE_13_SAMPLES,
				D3DMULTISAMPLE_12_SAMPLES,
				D3DMULTISAMPLE_11_SAMPLES,
				D3DMULTISAMPLE_10_SAMPLES,
				D3DMULTISAMPLE_9_SAMPLES,
				D3DMULTISAMPLE_8_SAMPLES,
				D3DMULTISAMPLE_7_SAMPLES,
				D3DMULTISAMPLE_6_SAMPLES,
				D3DMULTISAMPLE_5_SAMPLES,
				D3DMULTISAMPLE_4_SAMPLES,
				D3DMULTISAMPLE_3_SAMPLES,
				D3DMULTISAMPLE_2_SAMPLES,
			};

			for (int i = 0; i < _countof(d3daMultipleSampleType); i ++)
			{
				D3DMULTISAMPLE_TYPE t = d3daMultipleSampleType[i];
				DWORD q;

				if (SUCCEEDED(m_hr = m_pD3D->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,m_d3dPP.BackBufferFormat,bWindowed,t,&q)) &&
					SUCCEEDED(m_hr = m_pD3D->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,m_d3dPP.AutoDepthStencilFormat,bWindowed,t,&q)))
				{
					m_d3dPP.MultiSampleType = t;
					m_d3dPP.MultiSampleQuality = q - 1;
					break;
				}
			}
		}

		//Get Device Caps
		if (FAILED(m_hr = m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,&m_d3dCaps)))
		{
			Error("Could not get Device Capabilities");
			return FALSE;
		}

		return TRUE;
	}
	BOOL GraphicsEngine::CreateDevice(HWND hWnd)
	{
		// »ñÈ¡ÅäÖÃ

		UINT uWidth		= SETTINGHANDLE->Get().uWidth;
		UINT uHeight	= SETTINGHANDLE->Get().uHeight;
		BOOL bWindowed	= SETTINGHANDLE->Get().bWindowed;

		m_hWnd = hWnd;

		DWORD dwBehaviourFlags = D3DCREATE_FPU_PRESERVE;

		m_d3dPP.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

		if (m_d3dCaps.DevCaps & D3DDEVCAPS_PUREDEVICE)
		{
			Log("Pure Device");
			dwBehaviourFlags |= D3DCREATE_PUREDEVICE;
		}
		if ((m_d3dCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) && (m_d3dCaps.VertexProcessingCaps != 0))
		{
			Log("Hardware Vertex Processing");
			dwBehaviourFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
		}
		else
		{
			Log("Software Vertex Processing");
			dwBehaviourFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
		}

		if (m_d3dCaps.PresentationIntervals & D3DPRESENT_INTERVAL_IMMEDIATE)
		{
			Log("Presentation Interval Immediate");
			m_d3dPP.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		}

		if (SETTINGHANDLE->Get().bVSync)
		{
			if (m_d3dCaps.PresentationIntervals & D3DPRESENT_INTERVAL_ONE)
			{
				Log("Presentation Interval One");
				m_d3dPP.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
			}
		}

		m_d3dPP.Windowed				= bWindowed;
		m_d3dPP.BackBufferWidth			= uWidth;
		m_d3dPP.BackBufferHeight		= uHeight;
		m_d3dPP.SwapEffect				= D3DSWAPEFFECT_DISCARD;
		m_d3dPP.hDeviceWindow			= hWnd;
		m_d3dPP.BackBufferCount			= 1;
		m_d3dPP.EnableAutoDepthStencil	= TRUE;
		m_d3dPP.Flags					= 0;

		m_sResolution.bWindow	= bWindowed;
		m_sResolution.uWidth	= uWidth;
		m_sResolution.uHeight	= uHeight;

		if (bWindowed)
			m_d3dPP.FullScreen_RefreshRateInHz = 0;
		else
		{
			m_d3dPP.Windowed = FALSE;
			m_d3dPP.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		}

		if (FAILED(m_hr = m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,dwBehaviourFlags,&m_d3dPP,&m_pDevice)))
		{
			Error("Could not create Direct3D Device");
			return FALSE;
		}

		return TRUE;
	}
	BOOL GraphicsEngine::CheckDevice()
	{
		switch(m_hr = m_pDevice->TestCooperativeLevel())
		{
		case D3DERR_DEVICELOST:
			OnLostDevice();

			Sleep(500);

			//LOG
			Log("CheckDevice():Device Lost[0x%08X]",m_hr);

			return FALSE;
		case D3DERR_DEVICENOTRESET:
			OnLostDevice();

			if (FAILED(m_hr = m_pDevice->Reset(&m_d3dPP)))
			{
				Sleep(250);

				Log("CheckDevice(): Device Reset Failed [0x%08X]",m_hr);

				return FALSE;
			}

			OnResetDevice();
			break;
		}

		return SUCCEEDED(m_hr);
	}
	void GraphicsEngine::OnLostDevice()
	{
		m_pGraphicsDevice->OnLostDevice();

		UI::ImageRender::OnLostDevice();
	}
	void GraphicsEngine::OnResetDevice()
	{
		m_pGraphicsDevice->OnResetDevice();

		UI::ImageRender::OnResetDevice();
	}
	void GraphicsEngine::BeginScene(D3DXMATRIX mView)
	{
		// Clear Old Render and stat render
		if (SUCCEEDED(m_hr = m_pDevice->Clear(0,NULL,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL,D3DCOLOR_ARGB(255,0,0,0),1.0f,0)))
		{
			m_pDevice->SetTransform(D3DTS_VIEW,&mView);
			
			m_pDevice->BeginScene();

			//Render
		}
	}
	void GraphicsEngine::EndScene()
	{
		if (GetForegroundWindow() == m_hWnd)
			SETTINGHANDLE->OnCheckWindowState(m_hWnd);

		m_pDevice->EndScene();
		m_pDevice->Present(NULL,NULL,NULL,NULL);
	}
	BOOL GraphicsEngine::Reset(BOOL bResetWindowed,UINT uResetWidth,UINT uResetHeight)
	{
		//Mode same
		if ((bResetWindowed == m_sResolution.bWindow) &&
			(uResetWidth == m_sResolution.uWidth) &&
			(uResetHeight == m_sResolution.uHeight))
			return FALSE;

		//Save current PP
		D3DPRESENT_PARAMETERS d3dOldPP;

		CopyMemory(&d3dOldPP,&m_d3dPP,sizeof(D3DPRESENT_PARAMETERS));

		//Back Buffer
		if (FAILED(m_hr = m_pD3D->CheckDeviceType(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,m_d3dm.Format,m_d3dPP.BackBufferFormat,bResetWindowed)))
		{
			if (FAILED(m_hr = m_pD3D->CheckDeviceType(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,m_d3dm.Format,m_d3dPP.BackBufferFormat == D3DFMT_X8R8G8B8 ? D3DFMT_X4R4G4B4 : D3DFMT_X8R8G8B8,bResetWindowed)))
				return FALSE;

			m_d3dPP.BackBufferFormat = (m_d3dPP.BackBufferFormat == D3DFMT_X8R8G8B8 ? D3DFMT_X4R4G4B4 : D3DFMT_X8R8G8B8);
		}

		if (m_d3dPP.BackBufferFormat == D3DFMT_X8R8G8B8)
		{
			//32 bit Back Buffer
			Log("Reset(): 32 bit Back Buffer");
		}
		else if (m_d3dPP.BackBufferFormat == D3DFMT_X4R4G4B4)
		{
			//16 bit Back Buffer
			Log("Reset(): 16 bit Back Buffer");
		}
		else
		{
			Log("Reset(): Unknown Back Buffer Format");
			return FALSE;
		}

		//New Back Buffer Size
		m_d3dPP.BackBufferWidth = uResetWidth;
		m_d3dPP.BackBufferHeight = uResetHeight;

		//Multi Sample
		m_d3dPP.MultiSampleType = D3DMULTISAMPLE_NONE;
		m_d3dPP.MultiSampleQuality = 0;

		if (SETTINGHANDLE->Get().bAntiAliasing)
		{
			D3DMULTISAMPLE_TYPE d3daMultipleSampleType[] = {
				D3DMULTISAMPLE_16_SAMPLES,
				D3DMULTISAMPLE_15_SAMPLES,
				D3DMULTISAMPLE_14_SAMPLES,
				D3DMULTISAMPLE_13_SAMPLES,
				D3DMULTISAMPLE_12_SAMPLES,
				D3DMULTISAMPLE_11_SAMPLES,
				D3DMULTISAMPLE_10_SAMPLES,
				D3DMULTISAMPLE_9_SAMPLES,
				D3DMULTISAMPLE_8_SAMPLES,
				D3DMULTISAMPLE_7_SAMPLES,
				D3DMULTISAMPLE_6_SAMPLES,
				D3DMULTISAMPLE_5_SAMPLES,
				D3DMULTISAMPLE_4_SAMPLES,
				D3DMULTISAMPLE_3_SAMPLES,
				D3DMULTISAMPLE_2_SAMPLES,
			};

			for (int i = 0; i < _countof(d3daMultipleSampleType); i ++)
			{
				D3DMULTISAMPLE_TYPE t = d3daMultipleSampleType[i];
				DWORD q;

				if (SUCCEEDED(m_hr = m_pD3D->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,m_d3dPP.BackBufferFormat,m_sResolution.bWindow,t,&q)) &&
					SUCCEEDED(m_hr = m_pD3D->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,m_d3dPP.AutoDepthStencilFormat,m_sResolution.bWindow,t,&q)))
				{
					m_d3dPP.MultiSampleType = t;
					m_d3dPP.MultiSampleQuality = q - 1;
					break;
				}
			}
		}

		Log("Reset() : Multi Sample %d %d",m_d3dPP.MultiSampleType,m_d3dPP.MultiSampleQuality);

		//Window specific PP Settings
		if (bResetWindowed)
		{
			m_d3dPP.Windowed = TRUE;
			m_d3dPP.FullScreen_RefreshRateInHz = 0;
		}
		else
		{
			m_d3dPP.Windowed = FALSE;
			m_d3dPP.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		}

		m_d3dPP.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

		if (m_d3dCaps.PresentationIntervals & D3DPRESENT_INTERVAL_IMMEDIATE)
		{
			Log("Presentation Interval Immediate");
			m_d3dPP.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		}

		if (SETTINGHANDLE->Get().bVSync)
		{
			if (m_d3dCaps.PresentationIntervals & D3DPRESENT_INTERVAL_ONE)
			{
				Log("Presentation Interval One");
				m_d3dPP.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
			}
		}

		//Lose Device and attempt Reset on new PP
		OnLostDevice();

		if (FAILED(m_hr = m_pDevice->Reset(&m_d3dPP)))
		{
			CopyMemory(&m_d3dPP,&d3dOldPP,sizeof(D3DPRESENT_PARAMETERS));

			// Yield CPU
			Sleep(100);

			//Log
			Log("Reset(): Device Reset Failed");

			//Reset back to previous (working) PP
			OnLostDevice();

			if (FAILED(m_hr = m_pDevice->Reset(&m_d3dPP)))
			{
				//Yield CPU
				Sleep(100);

				//Log
				Log("Reset(): Device Rollback Failed");

				return FALSE;
			}
			else
			{
				//Log
				Log("Reset(): Device Rollbacked");
			}
		}
		else
		{
			//Log
			Log("Reset(): Device Reset");

			m_sResolution.bWindow	= bResetWindowed;
			m_sResolution.uWidth	= uResetWidth;
			m_sResolution.uHeight	= uResetHeight;

			//Reset Device
			OnResetDevice();
		}
		
		return TRUE;
	}

	void GraphicsEngine::ResolutionChange(BOOL bFirstTime,int iWidth,int iHeight)
	{
		MidX = iWidth >> 1;
		MidY = iHeight >> 1;

		GAME->OnResolutionChanged();

		SetDxProjection((D3DX_PI / 4.4f), iWidth, iHeight, 20.f, 4000.f);
	}

	std::string GraphicsEngine::GetVideoName()
	{
		D3DADAPTER_IDENTIFIER9 s;

		if (FAILED(m_pD3D->GetAdapterIdentifier(D3DADAPTER_DEFAULT, 0, &s)))
			return "";

		return std::string(s.Description);
	}

	void GraphicsEngine::DrawRectangle(Rectangle2D rRect, DWORD dwColor1, DWORD dwColor2)
	{
		float u1, v1, u2, v2;

		u1 = 0.0f;
		v1 = 0.0f;
		u2 = 1.0f;
		v2 = 1.0f;

		SMD::Vertex rVertex[4];

		rVertex[0] = { float(rRect.iX),float(rRect.iY),0,1,dwColor1,0,u1,v1 };
		rVertex[1] = { float(rRect.iX + rRect.iWidth),float(rRect.iY),0,1,dwColor1,0,u2,v1 };
		rVertex[2] = { float(rRect.iX),float(rRect.iY + rRect.iHeight),0,1,dwColor2,0,u1,v2 };
		rVertex[3] = { float(rRect.iX + rRect.iWidth),float(rRect.iY + rRect.iHeight),0,1,dwColor2,0,u2,v2 };

		m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

		m_pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
		m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		m_pDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
		m_pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA);

		m_pDevice->SetRenderState(D3DRS_DITHERENABLE, TRUE);
		m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

		m_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		m_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

		m_pDevice->SetTexture(0, 0);

		m_pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_SPECULAR);

		m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, (LPVOID)rVertex,sizeof(SMD::Vertex));
	}
	void GraphicsEngine::ResizeWindow()
	{
		if (!SETTINGHANDLE->Get().bWindowed)
		{
			RECT rRect;

			rRect.right = SETTINGHANDLE->Get().uWidth;
			rRect.bottom = SETTINGHANDLE->Get().uHeight;
			rRect.left = 0;
			rRect.top = 0;

			UINT uFullStyle = WS_FULLSCREEN | WS_VISIBLE;

			AdjustWindowRect(&rRect, uFullStyle, FALSE);

			int x = (GetSystemMetrics(SM_CXSCREEN) >> 1) - (rRect.right >> 1);
			int y = (GetSystemMetrics(SM_CYSCREEN) >> 1) - (rRect.bottom >> 1);

			SetWindowPos(m_hWnd, NULL, x, y, rRect.right, rRect.bottom, SWP_DRAWFRAME | SWP_NOZORDER);

			SetWindowLongA(m_hWnd, GWL_STYLE, uFullStyle);
		}
		else
		{
			RECT rRect;

			rRect.right = SETTINGHANDLE->Get().uWidth;
			rRect.bottom = SETTINGHANDLE->Get().uHeight;
			rRect.left = 0;
			rRect.top = 0;

			UINT uWindowStyle = WS_VISIBLE | WS_WINDOWED;

			AdjustWindowRect(&rRect, uWindowStyle, FALSE);

			rRect.right -= rRect.left;
			rRect.bottom -= rRect.top;

			int x = (GetSystemMetrics(SM_CXSCREEN) >> 1) - (rRect.right >> 1);
			int y = (GetSystemMetrics(SM_CYSCREEN) >> 1) - (rRect.bottom >> 1);

			SetWindowLongA(m_hWnd, GWL_STYLE, uWindowStyle);

			SetWindowPos(m_hWnd, HWND_NOTOPMOST, x, y, rRect.right, rRect.bottom, SWP_SHOWWINDOW);
		}
	}
}