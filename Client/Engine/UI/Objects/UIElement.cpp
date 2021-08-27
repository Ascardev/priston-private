#include "StdAfx.h"
#include "UIElement.h"

namespace UI
{
	Element::Element()
	{

	}
	Element::Element(Rectangle2D rRectangle) : m_rRect(rRectangle)
	{

	}
	Element::~Element()
	{

	}
	void Element::Render(int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY)
	{
		if (m_bDebug)
		{
			auto pLine = LINEHANDLE->MakeLine();

			DWORD dwColor = -1;

			pLine->Draw(Rectangle2D(iX, iY, iWidth, 1), dwColor);
			pLine->Draw(Rectangle2D(iX, iY + iHeight - 1, iWidth, 1), dwColor);
			pLine->Draw(Rectangle2D(iX, iY, 1, iHeight), dwColor);
			pLine->Draw(Rectangle2D(iX + iWidth - 1, iY, 1, iHeight), dwColor);
		}
	}
}