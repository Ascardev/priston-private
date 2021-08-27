#include "StdAfx.h"
#include "UIImageBox.h"

namespace UI
{
	ImageBox::ImageBox(class Rectangle2D rRectangle) : Element(rRectangle)
	{

	}
	ImageBox::~ImageBox()
	{
		//Clear();
	}
	void ImageBox::Clear()
	{
		CLEARPTR(m_pImage);

		UI::ImageLoader::DeleteImage(m_pImage);

		if (m_pImageActive1 != m_pImage)
		{
			CLEARPTR(m_pImageActive1);
			UI::ImageLoader::DeleteImage(m_pImageActive1);
		}

		if (m_pImageActive2 != m_pImage)
		{
			CLEARPTR(m_pImageActive2);
			UI::ImageLoader::DeleteImage(m_pImageActive2);
		}
	}

	void ImageBox::SetImage(Image *pImage)
	{
		m_pImage = pImage;
	}

	void ImageBox::SetActiveImage(std::pair<class Image *,class Image *> pPair)
	{
		m_pImageActive1 = pPair.first;
		m_pImageActive2 = pPair.second;

		m_pImage = m_pImageActive1;
	}
	void ImageBox::SetGroup(std::shared_ptr<Group> pGroup)
	{
		m_pGroup = pGroup;
	}
	void ImageBox::Swap()
	{
		m_pImage = (m_pImage == m_pImageActive1) ? m_pImageActive2 : m_pImageActive1;
	}
	void ImageBox::Swap(BOOL bActiveImage)
	{
		m_pImage = bActiveImage ? m_pImageActive2 : m_pImageActive1;
	}
	void ImageBox::Render(int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY)
	{
		if (IsOpen())
		{
			int iRenderX = GetX() + iX + m_iLeft;
			int iRenderY = GetY() + iY + m_iTop;
			int iRenderWidth = low(GetWidth(),iWidth) - m_iLeft;
			int iRenderHeight = low(GetHeight(),iHeight) - m_iTop;

			if (m_fScale != 1.0f)
			{
				iRenderWidth = GetWidth();
				iRenderHeight = GetHeight();
			}

			if (m_iLeft)
				iSourceX = m_iLeft;

			if (m_iTop)
				iSourceY = m_iTop;

			if (m_pTexture)
				ImageRender::Render(m_pTexture, iRenderX, iRenderY, iRenderWidth, iRenderHeight, iSourceX, iSourceY, m_dwColor, m_fScale);
			else
				ImageRender::Render(m_pImage, iRenderX, iRenderY, iRenderWidth, iRenderHeight, iSourceX, iSourceY, m_dwColor, m_fScale);

			Element::Render(iRenderX,iRenderY,iRenderWidth,iRenderHeight,iSourceX,iSourceY);
		}
	}
	void ImageBox::OnMouseMove(class INPUTS::Mouse *pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		if (!IsOpen())
			return;

		Point2D *psPosition = pcMouse->GetPosition();

		int iRenderX = GetX() + iX + iSourceX;
		int iRenderY = GetY() + iY + iSourceY;
		int iRenderWidth = low(GetWidth(), iWidth);
		int iRenderHeight = low(GetHeight(), iHeight);

		// Inside X and Inside Y
		if (((psPosition->iX >= iRenderX) && (psPosition->iX <= (iRenderX + iRenderWidth - iSourceX))) &&
			((psPosition->iY >= iRenderY) && (psPosition->iY <= (iRenderY + iRenderHeight - iSourceY))))
		{
			if (!m_bHover)
			{
				m_bHover = TRUE;

				if (m_iEvent_MoveID)
					UI::Event::Invoke(m_iEvent_MoveID);
			}
		}
		else
		{
			if (m_bHover)
			{
				m_bHover = FALSE;
			}
		}
	}
}