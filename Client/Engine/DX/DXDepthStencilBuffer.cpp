#include "StdAfx.h"
#include "DXDepthStencilBuffer.h"

namespace DX
{
	DepthStencilBuffer::DepthStencilBuffer(std::weak_ptr<GraphicsDevice> pGraphicsDevice,int iSharableID,UINT uSizeShiftRight):m_pGraphicsDevice(pGraphicsDevice),m_iSharableID(iSharableID),m_uSizeShiftRight(uSizeShiftRight)
	{
		m_lpSurface = NULL;
	}
	DepthStencilBuffer::DepthStencilBuffer(std::weak_ptr<GraphicsDevice> pGraphicsDevice,int iSharableID,UINT uWidth,UINT uHeight) : m_pGraphicsDevice(pGraphicsDevice),m_iSharableID(iSharableID),m_uWidth(uWidth),m_uHeight(uHeight)
	{
		//m_lpSurface = NULL;
	}
	DepthStencilBuffer::~DepthStencilBuffer()
	{
		RELEASE(m_lpSurface);
	}
	void DepthStencilBuffer::OnLostDevice()
	{
		RELEASE(m_lpSurface);
	}
	void DepthStencilBuffer::OnResetDevice()
	{
		m_pGraphicsDevice.lock()->BuildDepthStencilBuffer(shared_from_this());
	}
}