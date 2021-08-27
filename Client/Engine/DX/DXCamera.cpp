#include "StdAfx.h"
#include "DXCamera.h"

namespace DX
{
	Camera::Camera(GraphicsDevice *pGraphicsDevice) : m_pGraphicsDevice(pGraphicsDevice)
	{
		D3DXMatrixIdentity(&m_matView);
	}
}