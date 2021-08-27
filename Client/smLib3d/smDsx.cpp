#include "StdAfx.h"

#include "..\\NetType.hpp"

extern HWND hwnd;
extern smCONFIG smConfig;

int smFlipCount = 0;

int GetWindowVersion();

DXGraphicEngine cDXGraphic;

/*int MESSAGE(char *t)
{
	FILE *fp;

	fp = fopen("error.log", "wb");

	if (fp != NULL)
	{
		fwrite(t, lstrlen(t), 1, fp);
		fclose(fp);
	}

	return NULL;
}*/

DXGraphicEngine::DXGraphicEngine()
{
	m_width = 0;
	m_height = 0;
	m_windowed = FALSE;
	m_isLost = FALSE;
	m_vsync = FALSE;
	lpD3D = NULL;
	lpD3DDevice = NULL;
	lpD3DSprite = NULL;
	lpD3DFont = NULL;
	lpD3DBoldFont = NULL;
	for (int i = 0; i < EFFECT_MAX; i++)
		lpD3DEffect[i] = NULL;
	ZeroMemory(&m_d3dpp, sizeof(D3DPRESENT_PARAMETERS));
}
DXGraphicEngine::~DXGraphicEngine()
{
	//ReleaseDevice();
}
BOOL DXGraphicEngine::CreateDevice(int width, int height, BOOL windowed, BOOL Anti, int vsync)
{
	lpD3D = Direct3DCreate9(D3D_SDK_VERSION);

	m_width = width;
	m_height = height;
	m_windowed = windowed;
	m_Anti = Anti;
	m_vsync = vsync;

	if (lpD3D != NULL)
	{
		if (CheckDevice() == TRUE)
		{
			D3DCAPS9 Caps;
			int vp = 0;

			if (SUCCEEDED(lpD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &Caps)))
			{
				if (Caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
					vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
				else
					vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

				if (SUCCEEDED(lpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, vp, &m_d3dpp, &lpD3DDevice)))
				{
					if (FAILED(D3DXCreateSprite(lpD3DDevice, &lpD3DSprite)))
					{
						//MESSAGE("Could not create D3DSprite");
						return FALSE;
					}

					if (FAILED(D3DXCreateFont(lpD3DDevice, 15, 0, FW_NORMAL, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, "Tahoma", &lpD3DFont)))
					{
						//MESSAGE("Could not create D3DFont");
						return FALSE;
					}
					if (FAILED(D3DXCreateFont(lpD3DDevice, 15, 0, FW_ULTRABOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, "Tahoma", &lpD3DBoldFont)))
					{
						//MESSAGE("Could not create D3DFont");
						return FALSE;
					}

					return TRUE;
				}
				//else
					//MESSAGE("Could not create Direct3D Device");
			}
			//else
				//MESSAGE("Could not get Device Capabilities");
		}
		//else
			//MESSAGE("Check Device Mode fail");
	}
	//else
		//MESSAGE("Could not Create Direct3D9 Driver");

	return FALSE;
}
void DXGraphicEngine::ReleaseDevice()
{
	for (int i = 0; i < EFFECT_MAX; i++)
		SAFE_RELEASE(lpD3DEffect[i]);
	SAFE_RELEASE(lpD3DFont);
	SAFE_RELEASE(lpD3DBoldFont);
	SAFE_RELEASE(lpD3DSprite);
	SAFE_RELEASE(lpD3DDevice);
	SAFE_RELEASE(lpD3D);
}
void DXGraphicEngine::InitRender()
{
	lpD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	lpD3DDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	lpD3DDevice->SetRenderState(D3DRS_DITHERENABLE, TRUE);

	lpD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);

	lpD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	lpD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	smRender.AlphaTestDepth = ALPHATESTDEPTH;
	smRender.dwMatDispMask = sMATS_SCRIPT_NOTVIEW;
	smRender.DeviceRendMode = TRUE;
	smRender.ZWriteAuto = FALSE;
}
void DXGraphicEngine::InvalidateDevice()
{
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (lpD3DEffect[i])
			lpD3DEffect[i]->OnLostDevice();
	}
	if (lpD3DFont)
		lpD3DFont->OnLostDevice();
	if (lpD3DBoldFont)
		lpD3DBoldFont->OnLostDevice();
	if (lpD3DSprite)
		lpD3DSprite->OnLostDevice();
}
void DXGraphicEngine::RestoredataDevice()
{
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (lpD3DEffect[i])
			lpD3DEffect[i]->OnResetDevice();
	}
	if (lpD3DFont)
		lpD3DFont->OnResetDevice();
	if (lpD3DBoldFont)
		lpD3DBoldFont->OnResetDevice();
	if (lpD3DSprite)
		lpD3DSprite->OnResetDevice();
}
void DXGraphicEngine::BeginRender()
{
	if (lpD3DDevice)
	{
		lpD3DDevice->Clear(0, NULL, D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		lpD3DDevice->BeginScene();
	}
}
void DXGraphicEngine::EndRender()
{
	if (lpD3DDevice)
	{
		lpD3DDevice->EndScene();
		if (lpD3DDevice->Present(NULL, NULL, NULL, NULL) == D3DERR_DEVICELOST)
			m_isLost = TRUE;
	}
}
void DXGraphicEngine::RestoreDevice()
{
	HRESULT hr;
	if (m_isLost)
	{
		Sleep(100);

		if (FAILED(hr = lpD3DDevice->TestCooperativeLevel()))
		{
			switch (hr)
			{
			case D3DERR_DEVICELOST:
				return;
			case D3DERR_DEVICENOTRESET:
				InvalidateDevice();
				if (SUCCEEDED(lpD3DDevice->Reset(&m_d3dpp)))
				{
					InitRender();
					RestoredataDevice();
					return;
				}
				else
					return;
			}
		}
		m_isLost = FALSE;
	}
}
BOOL DXGraphicEngine::CheckDevice()
{
	D3DDISPLAYMODE d3ddm;

	if (SUCCEEDED(lpD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		D3DFORMAT BackBufferFormat;
		BackBufferFormat = D3DFMT_X8R8G8B8;

		if (FAILED(lpD3D->CheckDeviceType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3ddm.Format, BackBufferFormat = BackBufferFormat, m_windowed)))
		{
			BackBufferFormat = D3DFMT_X4R4G4B4;

			if (FAILED(lpD3D->CheckDeviceType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3ddm.Format, BackBufferFormat = BackBufferFormat, m_windowed)))
			{
				//MESSAGE("Your device does not support a 16-bit or 32-bit Back Buffer");
				return FALSE;
			}
		}

		D3DFORMAT checkFormat;

		checkFormat = D3DFMT_D24S8;
		if (FAILED(lpD3D->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3ddm.Format, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, checkFormat)))
		{
			checkFormat = D3DFMT_D15S1;

			if (FAILED(lpD3D->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3ddm.Format, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, checkFormat)))
			{
				//MESSAGE("Your device must support a 16-bit Z Buffer");
				return FALSE;
			}
		}

		D3DMULTISAMPLE_TYPE sample;
		sample = D3DMULTISAMPLE_NONE;

		if (m_Anti)
		{
			if (SUCCEEDED(lpD3D->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3ddm.Format, m_windowed, D3DMULTISAMPLE_4_SAMPLES, NULL)))
				sample = D3DMULTISAMPLE_4_SAMPLES;
			//else
				//MESSAGE("Your device not support 2X Anti aliasing");
		}

		m_d3dpp.BackBufferWidth = m_width;
		m_d3dpp.BackBufferHeight = m_height;
		m_d3dpp.BackBufferFormat = BackBufferFormat;
		m_d3dpp.BackBufferCount = 1;
		m_d3dpp.MultiSampleType = sample;
		m_d3dpp.MultiSampleQuality = 0;
		m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		m_d3dpp.hDeviceWindow = hwnd;
		m_d3dpp.Windowed = m_windowed;
		m_d3dpp.EnableAutoDepthStencil = TRUE;
		m_d3dpp.AutoDepthStencilFormat = checkFormat;
		m_d3dpp.PresentationInterval = (m_vsync) ? D3DPRESENT_INTERVAL_ONE : D3DPRESENT_INTERVAL_IMMEDIATE;

		return TRUE;
	}
	//else
		//MESSAGE("Could not get Adapter Display Mode");

	return FALSE;
}
BOOL DXGraphicEngine::ResetDevice(int width, int height, BOOL windowed, BOOL Anti, int vsync)
{
	m_width = width;
	m_height = height;
	m_windowed = windowed;
	m_Anti = Anti;
	m_vsync = vsync;

	if (lpD3D)
	{
		if (CheckDevice() == TRUE)
		{
			InvalidateDevice();
			if (SUCCEEDED(lpD3DDevice->Reset(&m_d3dpp)))
			{
				InitRender();
				RestoredataDevice();
				return TRUE;
			}
			//else
				//MESSAGE("Reset Device fail");
		}
		//else
			//MESSAGE("Check Device Mode fail");
	}

	return FALSE;
}
BOOL DXGraphicEngine::LoadEffect(char *szFxFileName)
{
	LPD3DXBUFFER ErrorBuffer = NULL;

	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (lpD3DEffect[i] == NULL)
		{
			if (SUCCEEDED(D3DXCreateEffectFromFile(lpD3DDevice, szFxFileName, 0, 0, D3DXSHADER_DEBUG, 0, &lpD3DEffect[i], &ErrorBuffer)))
				return TRUE;
			//else
				//MESSAGE("D3XCreateEffectfromFile is faild");
			return FALSE;
		}
	}
	return FALSE;
}