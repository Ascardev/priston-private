#include "StdAfx.h"
#include "DXLineFactory.h"

namespace DX
{
	LineFactory::LineFactory(GraphicsDevice *pGraphicsDevice) : m_pGraphicsDevice(pGraphicsDevice)
	{

	}
	LineFactory::~LineFactory()
	{

	}
	void LineFactory::OnLostDevice()
	{
		for (auto pLine : m_vpLine)
		{
			if (pLine)
				pLine->OnLostDevice();
		}
	}
	void LineFactory::OnResetDevice()
	{
		for (auto pLine : m_vpLine)
		{
			if (pLine)
				pLine->OnResetDevice();
		}
	}
	LPLINE LineFactory::FindLine()
	{
		for (auto pLine : m_vpLine)
		{
			if (pLine)
				return pLine;
		}

		return nullptr;
	}
	LPLINE LineFactory::MakeLine()
	{
		//D3DXCreateLine(m_pGraphicsDevice->Get(),&m_pLine);

		auto pLine = FindLine();

		if (pLine)
			return pLine;

		LPD3DXLINE lpLine;

		if (FAILED(D3DXCreateLine(m_pGraphicsDevice->Get(),&lpLine)))
			return NULL;

		//New Line;
		pLine = std::make_shared<Line>(lpLine);

		m_vpLine.push_back(pLine);

		RELEASE(lpLine);

		return pLine;
	}
}