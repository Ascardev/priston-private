#include "StdAfx.h"
#include "DXViewport.h"

namespace DX
{
	ViewPort::ViewPort() : m_dwX(0),m_dwY(0),m_dwWidth(800),m_dwHeight(600),m_fMinZ(0.0f),m_fMaxZ(1.0f)
	{

	}
	ViewPort::ViewPort(DWORD dwX,DWORD dwY,DWORD dwWidth,DWORD dwHeight,float fMinZ,float fMaxZ) : m_dwX(dwX),m_dwY(dwY),m_dwWidth(dwWidth),m_dwHeight(dwHeight),m_fMinZ(fMinZ),m_fMaxZ(fMaxZ)
	{

	}
	ViewPort::~ViewPort()
	{

	}
}