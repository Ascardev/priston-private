#include "StdAfx.h"
#include "DXRenderTarget.h"

namespace DX
{
	RenderTarget::RenderTarget(std::weak_ptr<GraphicsDevice> pGraphicsDevice,int iSharableID,UINT uSizeShiftRight) : m_pGraphicsDevice(pGraphicsDevice),m_uSizeShiftRight(uSizeShiftRight),m_uWidth(0),m_uHeight(0)
	{
		m_lpTexture = NULL;
		m_lpSurface = NULL;
	}
	RenderTarget::RenderTarget(std::weak_ptr<GraphicsDevice> pGraphicsDevice,int iSharableID,UINT uWidth,UINT uHeight) : m_pGraphicsDevice(pGraphicsDevice),m_uSizeShiftRight(0),m_uWidth(uWidth),m_uHeight(uHeight)
	{
		m_lpTexture = NULL;
		m_lpSurface = NULL;
	}
	RenderTarget::~RenderTarget()
	{
		RELEASE(m_lpTexture);
		RELEASE(m_lpSurface);
	}
	void RenderTarget::OnLostDevice()
	{
		RELEASE(m_lpTexture);
		RELEASE(m_lpSurface);
	}
	void RenderTarget::OnResetDevice()
	{
		m_pGraphicsDevice.lock()->BuildRenderTarget(shared_from_this());
	}
}