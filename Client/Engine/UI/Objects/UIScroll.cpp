#include "StdAfx.h"
#include "UIScroll.h"

namespace UI
{
	Scroll::Scroll(Rectangle2D rRectangle) : Element(rRectangle)
	{
		m_pScroll = new Rectangle2D(0,0,0,0);
	}
	Scroll::~Scroll()
	{
		DELET(m_pScroll);
		//Clear();
	}

	void Scroll::Clear()
	{
		CLEARPTR(m_pImage);
		CLEARPTR(m_pImageScroll);
		CLEARPTR(m_pImageBackground);

		ImageLoader::DeleteImage(m_pImage);
		ImageLoader::DeleteImage(m_pImageScroll);
		ImageLoader::DeleteImage(m_pImageBackground);

		//DELET(m_pScroll);
	}

	void Scroll::Render(int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY)
	{
		if (IsOpen())
		{
			int iRenderX = GetX() + iX;
			int iRenderY = GetY() + iY;
			int iRenderWidth = GetWidth();
			int iRenderHeight = GetHeight();

			UI::ImageRender::Render(m_pImage,iRenderX + iSourceX,iRenderY + iSourceY,iRenderWidth,iRenderHeight,iSourceX,iSourceY,-1);

			int iPercent = m_bVertical ? m_pScroll->iY : m_pScroll->iX;

			//Background render
			if (m_pImageBackground)
			{
				int iWidthBackgound = m_bVertical ? iRenderWidth : (iPercent + (m_iWidthScroll >> 1));
				int iHeightBackgound = m_bVertical ? (iPercent + (m_iHeightScroll >> 1)) : iRenderHeight;

				UI::ImageRender::Render(m_pImageBackground,iRenderX + iSourceX,iRenderY + iSourceY,iWidthBackgound,iHeightBackgound,iSourceX,iSourceY,-1);
			}

			//Scroll Render
			if (m_pImageScroll)
			{
				int iXScroll = m_bVertical ? ((iRenderWidth >> 1) - (m_iWidthScroll >> 1)) : 0;
				int iYScroll = m_bVertical ? 0 : ((iRenderHeight >> 1) - (m_iHeightScroll >> 1));

				UI::ImageRender::Render(m_pImageScroll,iRenderX + iSourceX + iXScroll + m_pScroll->iX,iRenderY + iSourceY + iYScroll + m_pScroll->iY,m_iWidthScroll,m_iHeightScroll,iSourceX,iSourceY,-1);
			}

			UI::Element::Render(iRenderX,iRenderY,iWidth,iHeight,iSourceX,iSourceY);
		}
	}

	BOOL Scroll::OnMouseClick(INPUTS::LPMOUSE pcMouse,int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY)
	{
		if (!IsOpen() || IsEnjoin())
			return FALSE;

		EMouseEvent eEvent = pcMouse->GetEvent();

		if (ClickDownL != eEvent && ClickUpL != eEvent)
			return FALSE;

		if (eEvent == ClickUpL && m_bScrollable)
		{
			m_bScrollable = FALSE;
			return TRUE;
		}

		Point2D *psPosition = pcMouse->GetPosition();

		int iRenderX = GetX() + iX + iSourceX;
		int iRenderY = GetY() + iY + iSourceY;
		int iRenderWidth = GetWidth();
		int iRenderHeight = GetHeight();

		//Inside X
		if ((psPosition->iX >= iRenderX) && (psPosition->iX <= (iRenderX + iRenderWidth - iSourceX)))
		{
			//Inside Y
			if ((psPosition->iY >= iRenderY) && (psPosition->iY <= (iRenderY + iRenderHeight - iSourceY)))
			{
				if (eEvent == ClickDownL)
					m_bScrollable = TRUE;

				return TRUE;
			}
		}

		return FALSE;
	}

	BOOL Scroll::OnMouseScroll(INPUTS::LPMOUSE pcMouse,int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY)
	{
		if (!IsOpen() || IsEnjoin())
			return FALSE;

		if (m_bVertical)
		{
			m_pScroll->iY = m_pScroll->iY - (pcMouse->GetDistance() * 16);

			if (m_pScroll->iY > (GetHeight() - (m_iHeightScroll >> 1)))
				m_pScroll->iY = (int)((float)GetHeight() - (float)(m_iHeightScroll >> 1));
			else if (m_pScroll->iY < 0)
				m_pScroll->iY = 0;
		}

		return TRUE;
	}

	void Scroll::OnMouseMove(INPUTS::LPMOUSE pcMouse,int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY)
	{
		if (!IsOpen() || !m_bScrollable || IsEnjoin())
			return;

		Point2D *psPosition = pcMouse->GetPosition();

		int iRenderX = GetX() + iX + iSourceX;
		int iRenderY = GetY() + iY + iSourceY;

		int iXScrollBar = iRenderX + (m_iWidthScroll >> 1);
		int iYScrollBar = iRenderY + (m_iHeightScroll >> 1);

		if (m_bVertical)
		{
			m_pScroll->iY = psPosition->iY - iYScrollBar;

			if (m_pScroll->iY > (GetHeight() - (m_iHeightScroll >> 1)))
				m_pScroll->iY = (int)((float)GetHeight() - (float)(m_iHeightScroll >> 1));
			else if (m_pScroll->iY < 0)
				m_pScroll->iY = 0;
		}
		else
		{
			m_pScroll->iX = psPosition->iX - iXScrollBar;

			if (m_pScroll->iX > (GetWidth() - (m_iWidthScroll >> 1)))
				m_pScroll->iX = (int)((float)GetWidth() - (float)(m_iWidthScroll >> 1));
			else if (m_pScroll->iX < 0)
				m_pScroll->iX = 0;
		}
	}

	int Scroll::GetPercent()
	{
		float fMinMax = m_fMaxScroll - m_fMinScroll;

		float fRet = 0;

		if (m_bVertical)
			fRet = (((float)m_pScroll->iY * fMinMax) / ((float)GetHeight() - (float)(m_iHeightScroll >> 1))) + m_fMinScroll;
		else
			fRet = (((float)m_pScroll->iY * fMinMax) / ((float)GetWidth() - (float)(m_iWidthScroll >> 1))) + m_fMinScroll;

		return (int)(fRet);
	}
	void Scroll::SetPercent(int iCur)
	{
		float fMinMax = m_fMaxScroll - m_fMinScroll;

		if (iCur >= (int)m_fMinScroll && iCur <= (int)m_fMaxScroll)
		{
			m_iCurrentPercent = iCur;

			if (m_bVertical)
			{
				m_pScroll->iY = (int)(abs((((float)GetHeight() - (float)(m_iHeightScroll >> 1)) * (float)iCur) / fMinMax) + m_fMinScroll);

				if (m_pScroll->iY < 0)
					m_pScroll->iY = 0;
			}
			else
			{
				m_pScroll->iX = (int)(abs((((float)GetWidth() - (float)(m_iWidthScroll >> 1)) * (float)iCur) / fMinMax) + m_fMinScroll);

				if (m_pScroll->iX < 0)
					m_pScroll->iX = 0;
			}
		}
	}
}