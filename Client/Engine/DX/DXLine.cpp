#include "StdAfx.h"
#include "DXLine.h"

namespace DX
{
	Line::Line(LPD3DXLINE pLine) : m_pLine(pLine)
	{
		ADDREF(m_pLine);
	}
	Line::~Line()
	{

	}

	void Line::OnLostDevice()
	{
		if (m_pLine)
			m_pLine->OnLostDevice();
	}
	void Line::OnResetDevice()
	{
		if (m_pLine)
			m_pLine->OnResetDevice();
	}
	void Line::Draw(Rectangle2D rRect,DWORD dwColor)
	{
		D3DXVECTOR2 vLine[2];

		if (m_pLine)
		{
			m_pLine->SetWidth((float)rRect.iWidth);
			m_pLine->SetAntialias(FALSE);
			m_pLine->SetGLLines(TRUE);

			vLine[0].x = (float)rRect.iX + (float)rRect.iWidth / 2;
			vLine[0].y = (float)rRect.iY;
			vLine[1].x = (float)rRect.iX + (float)rRect.iWidth / 2;
			vLine[1].y = (float)rRect.iY + (float)rRect.iHeight;

			m_pLine->Begin();
			m_pLine->Draw(vLine,2,dwColor);
			m_pLine->End();
		}
	}
}