#include "StdAfx.h"
#include "DXGraphicsDevice.h"

namespace DX
{
	GraphicsDevice::GraphicsDevice(LPDIRECT3DDEVICE9 lpD3DDevice) : m_pD3DDevice(lpD3DDevice)
	{
		ADDREF(m_pD3DDevice);

		m_pTextureFactory = std::make_shared<TextureFactory>(this);
		m_pEffectFactory = std::make_shared<EffectFactory>(this);
		m_pSpriteFactory = std::make_shared<SpriteFactory>(this);
		m_pFontFactory = std::make_shared<FontFactory>(this);
		m_pCamera = std::make_shared<Camera>(this);
		m_pLineFactory = std::make_shared<LineFactory>(this);

		Setup();
	}
	GraphicsDevice::~GraphicsDevice()
	{
		m_vDepthStencilBuffers.clear();
		m_vRenderTargets.clear();

		m_pTextureFactory = nullptr;
		m_pEffectFactory = nullptr;
		m_pSpriteFactory = nullptr;
		m_pFontFactory = nullptr;
		m_pCamera = nullptr;
		m_pLineFactory = nullptr;

		RELEASE(m_pD3DDevice);
	}
	void GraphicsDevice::OnLostDevice()
	{
		m_pTextureFactory->OnLostDevice();
		m_pEffectFactory->OnLostDevice();
		m_pSpriteFactory->OnLostDevice();
		m_pFontFactory->OnLostDevice();
		m_pLineFactory->OnLostDevice();

		for (auto pRenderTarget : m_vRenderTargets)
		{
			if (pRenderTarget)
				pRenderTarget->OnLostDevice();
		}

		for (auto pDepthStencilBuffer : m_vDepthStencilBuffers)
		{
			if (pDepthStencilBuffer)
				pDepthStencilBuffer->OnLostDevice();
		}
	}
	void GraphicsDevice::OnResetDevice()
	{
		Setup();

		m_pTextureFactory->OnResetDevice();
		m_pEffectFactory->OnResetDevice();
		m_pSpriteFactory->OnResetDevice();
		m_pFontFactory->OnResetDevice();
		m_pLineFactory->OnResetDevice();

		for (auto pRenderTarget : m_vRenderTargets)
		{
			if (pRenderTarget)
				pRenderTarget->OnResetDevice();
		}

		for (auto pDepthStencilBuffer : m_vDepthStencilBuffers)
		{
			if (pDepthStencilBuffer)
				pDepthStencilBuffer->OnResetDevice();
		}
	}
	ViewPort GraphicsDevice::GetViewport() const
	{
		ViewPort vViewport;

		vViewport.m_dwX			= 0;
		vViewport.m_dwY			= 0;
		vViewport.m_dwWidth		= GetBackBufferWidth();
		vViewport.m_dwHeight	= GetBackBufferHeight();
		vViewport.m_fMinZ		= 0.0f;
		vViewport.m_fMaxZ		= 1.0f;

		D3DVIEWPORT9 d3dViewport;

		if (FAILED(m_pD3DDevice->GetViewport(&d3dViewport)))
		{
			return vViewport;
		}

		vViewport.m_dwX			= d3dViewport.X;
		vViewport.m_dwY			= d3dViewport.Y;
		vViewport.m_dwWidth		= d3dViewport.Width;
		vViewport.m_dwHeight	= d3dViewport.Height;
		vViewport.m_fMinZ		= d3dViewport.MinZ;
		vViewport.m_fMaxZ		= d3dViewport.MaxZ;

		return vViewport;
	}
	BOOL GraphicsDevice::SetViewport(const ViewPort &vViewport)
	{
		D3DVIEWPORT9 d3dViewport;

		d3dViewport.X		= vViewport.m_dwX;
		d3dViewport.Y		= vViewport.m_dwY;
		d3dViewport.Width	= vViewport.m_dwWidth;
		d3dViewport.Height	= vViewport.m_dwHeight;
		d3dViewport.MinZ	= vViewport.m_fMinZ;
		d3dViewport.MaxZ	= vViewport.m_fMaxZ;

		if (FAILED(m_pD3DDevice->SetViewport(&d3dViewport)))
			return FALSE;

		return TRUE;
	}
	BOOL GraphicsDevice::Clear(BOOL bTarget,BOOL bZBuffer,BOOL bStencil)
	{
		DWORD dwFlags = 0;

		if (bTarget)
			dwFlags |= D3DCLEAR_TARGET;

		if (bZBuffer)
			dwFlags |= D3DCLEAR_ZBUFFER;

		if (bStencil)
			dwFlags |= D3DCLEAR_STENCIL;

		if (FAILED(Get()->Clear(0,NULL,dwFlags,D3DCOLOR_ARGB(0,0,0,0),1.0f,0)))
			return FALSE;

		return TRUE;
	}
	BOOL GraphicsDevice::Begin()
	{
		return SUCCEEDED(m_pD3DDevice->BeginScene());
	}
	BOOL GraphicsDevice::End()
	{
		if (FAILED(m_pD3DDevice->EndScene()))
			return FALSE;

		return SUCCEEDED(m_pD3DDevice->Present(NULL,NULL,NULL,NULL));
	}
	void GraphicsDevice::SetRenderState(RenderState eState,DWORD dwValue)
	{
		switch(eState)
		{
		case RENDERSTATE_ScissorTest:
			m_pD3DDevice->SetRenderState(D3DRS_SCISSORTESTENABLE,dwValue);
			break;
		case RENDERSTATE_StencilEnable:
			m_pD3DDevice->SetRenderState(D3DRS_STENCILENABLE,dwValue);
			break;
		}
	}

	BOOL GraphicsDevice::SetRenderTarget(LPRENDERTARGET pRenderTarget)
	{
		if (pRenderTarget)
		{
			auto lpSurface = pRenderTarget->GetSurface();

			if (lpSurface)
			{
				// Push Render Target to stack
				PushRenderTarget();

				//Set Render Target
				if (FAILED(m_pD3DDevice->SetRenderTarget(0,lpSurface)))
				{
					//Pop Render Target back from stack
					PopRenderTarget();

					return FALSE;
				}

				UpdateRenderTargetInfo();

				return TRUE;
			}
		}

		return FALSE;
	}
	void GraphicsDevice::UnsetRenderTarget()
	{
		PopRenderTarget();

		//Render Target
		UpdateRenderTargetInfo();
	}
	void GraphicsDevice::PushRenderTarget()
	{
		LPDIRECT3DSURFACE9 lpSurface;

		m_pD3DDevice->GetRenderTarget(0,&lpSurface);

		m_sRenderTargets.push(lpSurface);
	}
	void GraphicsDevice::PopRenderTarget()
	{
		auto lpSurface = m_sRenderTargets.top();

		m_pD3DDevice->SetRenderTarget(0,lpSurface);
		lpSurface->Release();

		m_sRenderTargets.pop();
	}
	void GraphicsDevice::UpdateRenderTargetInfo()
	{
		LPDIRECT3DSURFACE9 lpSurface;

		if (SUCCEEDED(m_pD3DDevice->GetRenderTarget(0,&lpSurface)))
		{
			D3DSURFACE_DESC d3dSurfaceDesc;

			if (SUCCEEDED(lpSurface->GetDesc(&d3dSurfaceDesc)))
			{
				m_sInfo.uRenderTargetWidth		= d3dSurfaceDesc.Width;
				m_sInfo.uRenderTargetHeight		= d3dSurfaceDesc.Height;
				m_sInfo.d3dRenderTargetFormat	= d3dSurfaceDesc.Format;
			}

			lpSurface->Release();
		}
	}
	BOOL GraphicsDevice::SetDepthStencilBuffer(LPDEPTHSTENCILBUFFER pDepthStencilBuffer)
	{
		if (pDepthStencilBuffer)
		{
			auto lpSurface = pDepthStencilBuffer->GetSurface();

			if (lpSurface)
			{
				// Push Render Target to stack
				PushDepthStencilBuffer();

				//Set Depth Stencil Buffer
				if (FAILED(m_pD3DDevice->SetDepthStencilSurface(lpSurface)))
				{
					//Pop Render Target back from stack
					PopDepthStencilBuffer();

					return FALSE;
				}

				return TRUE;
			}
		}

		return FALSE;
	}
	void GraphicsDevice::UnsetDepthStencilBuffer()
	{
		//Pop Depth Stencil Buffer from stack
		PopDepthStencilBuffer();
	}
	void GraphicsDevice::PushDepthStencilBuffer()
	{
		LPDIRECT3DSURFACE9 lpSurface;

		m_pD3DDevice->GetDepthStencilSurface(&lpSurface);

		m_sDepthStencilBuffers.push(lpSurface);
	}
	void GraphicsDevice::PopDepthStencilBuffer()
	{
		auto lpSurface = m_sDepthStencilBuffers.top();

		m_pD3DDevice->SetDepthStencilSurface(lpSurface);

		lpSurface->Release();

		m_sDepthStencilBuffers.pop();
	}
	BOOL GraphicsDevice::BuildRenderTarget(LPRENDERTARGET pRenderTarget)
	{
		UINT uWidth			= pRenderTarget->GetWidth() ? pRenderTarget->GetWidth() : m_sInfo.uBackBufferWidth;
		UINT uHeight		= pRenderTarget->GetHeight() ? pRenderTarget->GetHeight() : m_sInfo.uBackBufferHeight;
		D3DFORMAT d3dFormat = m_sInfo.d3dBackBufferFormat == D3DFMT_X4R4G4B4 ? D3DFMT_A4R4G4B4 : D3DFMT_A8R8G8B8;

		//Reduce size
		if (pRenderTarget->GetSizeShiftRight() > 0)
		{
			uWidth >>= pRenderTarget->GetSizeShiftRight();
			uHeight>>= pRenderTarget->GetSizeShiftRight();
		}

		//Create Render Target Texture
		LPDIRECT3DTEXTURE9 lpTexture;
		if (FAILED(m_pD3DDevice->CreateTexture(uWidth,uHeight,1,D3DUSAGE_RENDERTARGET,d3dFormat,D3DPOOL_DEFAULT,&lpTexture,NULL)))
		{
			WRITEDBG("Could not create Render Target Texture");
			return FALSE;
		}

		//Create Render Target Surface
		LPDIRECT3DSURFACE9 lpSurface;
		if (FAILED(lpTexture->GetSurfaceLevel(0,&lpSurface)))
		{
			RELEASE(lpTexture);
			WRITEDBG("Could not create Render Target Surface");
			return FALSE;
		}

		pRenderTarget->m_lpTexture	= lpTexture;
		pRenderTarget->m_lpSurface	= lpSurface;

		pRenderTarget->m_uWidth		= uWidth;
		pRenderTarget->m_uHeight	= uHeight;

		return TRUE;
	}
	LPRENDERTARGET GraphicsDevice::FindRenderTarget(int iSharableID,UINT uSizeShiftRight)
	{
		if (iSharableID != -1)
		{
			for (auto pRenderTarget : m_vRenderTargets)
			{
				if (pRenderTarget)
				{
					if ((pRenderTarget->GetSharableID() == iSharableID) && (pRenderTarget->GetSizeShiftRight() == uSizeShiftRight))
					{
						return pRenderTarget;
					}
				}
			}
		}

		return NULL;
	}
	LPRENDERTARGET GraphicsDevice::FindRenderTarget(int iSharableID,UINT uWidth,UINT uHeight)
	{
		if (iSharableID != -1)
		{
			for (auto pRenderTarget : m_vRenderTargets)
			{
				if (pRenderTarget)
				{
					if ((pRenderTarget->GetSharableID() == iSharableID) && (pRenderTarget->GetWidth() == uWidth) && (pRenderTarget->GetHeight() == uHeight))
					{
						return pRenderTarget;
					}
				}
			}
		}

		return NULL;
	}
	LPRENDERTARGET GraphicsDevice::MakeRenderTarget(int iSharableID,UINT uSizeShiftRight)
	{
		// Find Render Target
		auto pRenderTarget = FindRenderTarget(iSharableID,uSizeShiftRight);

		if (pRenderTarget)
			return pRenderTarget;

		//New Render Target
		pRenderTarget = std::make_shared<RenderTarget>(shared_from_this(),iSharableID,uSizeShiftRight);

		//Build Render Target
		if (!BuildRenderTarget(pRenderTarget))
			return NULL;

		//Remember Render Target
		m_vRenderTargets.push_back(pRenderTarget);

		return pRenderTarget;
	}
	LPRENDERTARGET GraphicsDevice::MakeRenderTarget(int iSharableID,UINT uWidth,UINT uHeight)
	{
		// Find Render Target
		auto pRenderTarget = FindRenderTarget(iSharableID,uWidth,uHeight);

		if (pRenderTarget)
			return pRenderTarget;

		//New Render Target
		pRenderTarget = std::make_shared<RenderTarget>(shared_from_this(),iSharableID,uWidth,uHeight);

		//Build Render Target
		if (!BuildRenderTarget(pRenderTarget))
			return NULL;

		//Remember Render Target
		m_vRenderTargets.push_back(pRenderTarget);

		return pRenderTarget;
	}
	BOOL GraphicsDevice::BuildDepthStencilBuffer(LPDEPTHSTENCILBUFFER pDepthStencilBuffer)
	{
		UINT uWidth			= m_sInfo.uDepthStencilBufferWidth;
		UINT uHeight		= m_sInfo.uDepthStencilBufferHeight;
		D3DFORMAT d3dFormat = m_sInfo.d3dDepthStencilBufferFormat;

		if (pDepthStencilBuffer->GetSizeShiftRight() > 0)
		{
			uWidth  >>= pDepthStencilBuffer->GetSizeShiftRight();
			uHeight >>= pDepthStencilBuffer->GetSizeShiftRight();
		}

		LPDIRECT3DSURFACE9 lpSurface;

		if (FAILED(m_pD3DDevice->CreateDepthStencilSurface(uWidth,uHeight,d3dFormat,D3DMULTISAMPLE_NONE,0,FALSE,&lpSurface,NULL)))
		{
			WRITEDBG( "Could not create Depth Stencil Buffer Surface" );

			return FALSE;
		}

		pDepthStencilBuffer->m_lpSurface	= lpSurface;
		pDepthStencilBuffer->m_uWidth		= uWidth;
		pDepthStencilBuffer->m_uHeight		= uHeight;

		return TRUE;
	}
	LPDEPTHSTENCILBUFFER GraphicsDevice::FindDepthStencilBuffer(int iSharableID,UINT uSizeShiftRight)
	{
		if (iSharableID != -1)
		{
			for (auto pDepthStencilBuffer : m_vDepthStencilBuffers)
			{
				if (pDepthStencilBuffer)
				{
					if ((pDepthStencilBuffer->GetSharableID() == iSharableID) && (pDepthStencilBuffer->GetSizeShiftRight() == uSizeShiftRight))
					{
						return pDepthStencilBuffer;
					}
				}
			}
		}

		return NULL;
	}
	LPDEPTHSTENCILBUFFER GraphicsDevice::FindDepthStencilBuffer(int iSharableID,UINT uWidth,UINT uHeight)
	{
		if (iSharableID != -1)
		{
			for (auto pDepthStencilBuffer : m_vDepthStencilBuffers)
			{
				if (pDepthStencilBuffer)
				{
					if ((pDepthStencilBuffer->GetSharableID() == iSharableID) && (pDepthStencilBuffer->GetWidth() == uWidth) && (pDepthStencilBuffer->GetHeight() == uHeight))
					{
						return pDepthStencilBuffer;
					}
				}
			}
		}

		return NULL;
	}
	LPDEPTHSTENCILBUFFER GraphicsDevice::MakeDepthStencilBuffer(int iSharableID,UINT uSizeShiftRight)
	{
		auto pDepthStencilBuffer = FindDepthStencilBuffer(iSharableID,uSizeShiftRight);

		if (pDepthStencilBuffer)
			return pDepthStencilBuffer;

		pDepthStencilBuffer = std::make_shared<DepthStencilBuffer>(shared_from_this(),iSharableID,uSizeShiftRight);

		if (!BuildDepthStencilBuffer(pDepthStencilBuffer))
			return NULL;

		m_vDepthStencilBuffers.push_back(pDepthStencilBuffer);

		return pDepthStencilBuffer;
	}
	LPDEPTHSTENCILBUFFER GraphicsDevice::MakeDepthStencilBuffer(int iSharableID,UINT uWidth,UINT uHeight)
	{
		auto pDepthStencilBuffer = FindDepthStencilBuffer(iSharableID,uWidth,uHeight);

		if (pDepthStencilBuffer)
			return pDepthStencilBuffer;

		pDepthStencilBuffer = std::make_shared<DepthStencilBuffer>(shared_from_this(),iSharableID,uWidth,uHeight);

		if (!BuildDepthStencilBuffer(pDepthStencilBuffer))
			return NULL;

		m_vDepthStencilBuffers.push_back(pDepthStencilBuffer);

		return pDepthStencilBuffer;
	}
	void GraphicsDevice::Setup()
	{
		LPDIRECT3DSURFACE9 lpSurface;
		D3DSURFACE_DESC d3dSurfaceDesc;
		//Clear Info
		STRINGEMPTY(&m_sInfo);

		// Back Buffer
		if (SUCCEEDED(Get()->GetRenderTarget(0,&lpSurface)))
		{
			D3DSURFACE_DESC d3dSurfaceDesc;
			if (SUCCEEDED(lpSurface->GetDesc(&d3dSurfaceDesc)))
			{
				m_sInfo.uBackBufferWidth	= d3dSurfaceDesc.Width;
				m_sInfo.uBackBufferHeight	= d3dSurfaceDesc.Height;
				m_sInfo.d3dBackBufferFormat = d3dSurfaceDesc.Format;
			}

			lpSurface->Release();
		}

		// Depth Stencil Buffer
		if (SUCCEEDED(m_pD3DDevice->GetDepthStencilSurface(&lpSurface)))
		{
			if (SUCCEEDED(lpSurface->GetDesc(&d3dSurfaceDesc)))
			{
				m_sInfo.uDepthStencilBufferWidth	= d3dSurfaceDesc.Width;
				m_sInfo.uDepthStencilBufferHeight	= d3dSurfaceDesc.Height;
				m_sInfo.d3dDepthStencilBufferFormat = d3dSurfaceDesc.Format;
			}

			lpSurface->Release();
		}

		//Render Target
		UpdateRenderTargetInfo();
	}

	void GraphicsDevice::PushScissorRect(const RECT &rRect)
	{
		SetRenderState(RENDERSTATE_ScissorTest, TRUE);

		LPRECT pRect = new RECT;
		CopyMemory(pRect, &rRect, sizeof(RECT));
		m_vpScissorRect.push_back(pRect);

		m_pD3DDevice->SetScissorRect(&rRect);
	}

	void GraphicsDevice::PopScissorRect()
	{
		if (m_vpScissorRect.size() > 0)
		{
			DELET(m_vpScissorRect[m_vpScissorRect.size() - 1]);

			m_vpScissorRect.pop_back();

			if (m_vpScissorRect.size() == 0)
				SetRenderState(RENDERSTATE_ScissorTest, FALSE);
			else
				m_pD3DDevice->SetScissorRect(m_vpScissorRect[m_vpScissorRect.size() - 1]);
		}
	}
	LPRECT GraphicsDevice::GetScissorRect()
	{
		if (m_vpScissorRect.size() > 0)
			return m_vpScissorRect[m_vpScissorRect.size() - 1];

		return nullptr;
	}

	void GraphicsDevice::SetScissorRect(const RECT &rRect)
	{
		//Set Clipping Rect
		m_pD3DDevice->SetScissorRect(&rRect);
	}

	void GraphicsDevice::GetScissorRectInside(RECT &rRect)
	{
		if (HaveScissorRect())
		{
			LPRECT p = GetScissorRect();

			if (rRect.top < p->bottom)
			{
				if (rRect.bottom > p->bottom)
					rRect.bottom = (p->bottom - rRect.top) + rRect.top;
			}
			else
			{
				rRect.top		= p->bottom;
				rRect.bottom	= p->bottom;
			}
			if (rRect.left < p->right)
			{
				if (rRect.right > p->right)
					rRect.right = (p->right - rRect.left) + rRect.left;
			}
			else
			{
				rRect.left	= p->right;
				rRect.right = p->right;
			}
		}
	}
}