#include "StdAfx.h"
#include "UITooltip.h"

namespace UI
{
	ToolTip::ToolTip(Rectangle2D rRectangle) : Element(rRectangle)
	{
		m_sObjectBox = Rectangle2D();

		SetType(TYPE_Tooltip);
	}
	ToolTip::~ToolTip()
	{

	}
	void ToolTip::Init()
	{
		m_pBorderImages[0] = ImageLoader::LoadImage_("Resources\\UI\\Tooltip\\bottomleft.png");
		m_pBorderImages[1] = ImageLoader::LoadImage_("Resources\\UI\\Tooltip\\bottomright.png");
		m_pBorderImages[2] = ImageLoader::LoadImage_("Resources\\UI\\Tooltip\\left.png");
		m_pBorderImages[3] = ImageLoader::LoadImage_("Resources\\UI\\Tooltip\\top.png");
		m_pBorderImages[4] = ImageLoader::LoadImage_("Resources\\UI\\Tooltip\\topleft.png");
		m_pBorderImages[5] = ImageLoader::LoadImage_("Resources\\UI\\Tooltip\\topright.png");
	}
	void ToolTip::Clear()
	{
		for (auto &v : m_pBorderImages)
		{
			CLEARPTR(v);
			ImageLoader::DeleteImage(v);
		}
	}
	void ToolTip::SetFont(const char *pszFontName, int iFontSize, DWORD dwColor)
	{
		m_pText = std::make_shared<UI::Text>(Rectangle2D(0, 0, m_rRect.iWidth, m_rRect.iHeight));

		m_pText->SetFont(pszFontName, iFontSize, 0, FALSE, FALSE, dwColor);
		m_pText->SetMultiLine(TRUE);
		m_pText->SetWordWrap(TRUE);
	}
	void ToolTip::SetText(std::string strText)
	{
		if (m_pText)
		{
			m_pText->SetText(strText);
			m_iWidthText = m_pText->GetWidthText();
			m_iHeightText = m_pText->GetHeightFont();
		}
	}
	void ToolTip::Open()
	{
		m_bTransition = TRUE;
		m_fProgress = 1.0f;
		m_iFadeType = 1;
	}
	void ToolTip::Close()
	{
		m_bTransition = TRUE;
		m_fProgress = 0.0f;
		m_iFadeType = 2;
	}
	void ToolTip::Update(float fTime)
	{
		/*if( bTransition )
		{
			if( iFadeType == 1 )
			{
				fProgress += fTime;

				if( fProgress > 1.0f )
				{
					fProgress = 1.0f;
					iFadeType = 0;
					bTransition = FALSE;
				}
			}
			else
			{
				fProgress -= fTime;

				if( fProgress < 0.0f )
				{
					fProgress = 0.0f;
					iFadeType = 0;
					bTransition = FALSE;
				}
			}
		}*/
	}
	void ToolTip::Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		int iRenderX = GetX() + iX + (m_pLinkObject ? m_pLinkObject->GetX() : 0);
		int iRenderY = GetY() + iY + (m_pLinkObject ? m_pLinkObject->GetY() : 0);
		int iRenderWidth = low((m_pLinkObject ? m_pLinkObject->GetWidth() : GetWidth()), iWidth - GetX());
		int iRenderHeight = low((m_pLinkObject ? m_pLinkObject->GetHeight() : GetHeight()), iHeight - GetY());

		m_sObjectBox = Rectangle2D(iRenderX, iRenderY, iRenderWidth, iRenderHeight);

		if (!m_bHover)
			return;

		int iAddX = 0;
		int iAddY = 0;

		switch (m_ePosition)
		{
		case TOOLTIPPOSITION_Top:
			iAddY -= m_iHeightText + 8;
			iAddX = (iRenderWidth >> 1) - (m_iWidthText >> 1);
			break;
		case TOOLTIPPOSITION_Right:
			iAddX = iRenderWidth + 2;
			break;
		case TOOLTIPPOSITION_Bottom:
			iAddY = iRenderHeight;
			iAddX = (iRenderWidth >> 1) - (m_iWidthText >> 1);
			break;
		}

		if (m_pText)
		{
			if (m_bFollowMouse)
			{
				LINEHANDLE->MakeLine()->Draw(Rectangle2D(MOUSEHANDLER->GetPosition()->iX - (m_iWidthText >> 1), MOUSEHANDLER->GetPosition()->iY + (iAddY * (int)m_fProgress), m_iWidthText, m_iHeightText), D3DCOLOR_ARGB(200, 0, 0, 0));
				m_pText->Render(MOUSEHANDLER->GetPosition()->iX - (m_iWidthText >> 1), MOUSEHANDLER->GetPosition()->iY + (iAddY * (int)m_fProgress), iWidth, iHeight, 0, 0);
			}
			else
			{
				int iX = m_sObjectBox.iX + iAddX;
				int iY = m_sObjectBox.iY + (iAddY * (int)m_fProgress);

				(iX <= 0) ? iX = 2 : iX;
				(iY <= 0) ? iY = 2 : iY;

				m_pBorderImages[0] ? UI::ImageRender::Render(m_pBorderImages[0], iX - m_pBorderImages[0]->GetWidth(), iY + m_iHeightText, m_pBorderImages[0]->GetWidth(), m_pBorderImages[0]->GetHeight(), -1) : 0;
				m_pBorderImages[1] ? UI::ImageRender::Render(m_pBorderImages[1], iX + m_iWidthText, iY + m_iHeightText, m_pBorderImages[1]->GetWidth(), m_pBorderImages[1]->GetHeight(), -1) : 0;
				m_pBorderImages[2] ? UI::ImageRender::Render(m_pBorderImages[2], iX - m_pBorderImages[2]->GetWidth(), iY, m_pBorderImages[2]->GetWidth(), m_iHeightText, -1) : 0;
				m_pBorderImages[2] ? UI::ImageRender::Render(m_pBorderImages[2], iX + m_iWidthText, iY, m_pBorderImages[2]->GetWidth(), m_iHeightText, -1) : 0;
				m_pBorderImages[3] ? UI::ImageRender::Render(m_pBorderImages[3], iX, iY - m_pBorderImages[3]->GetHeight(), m_iWidthText, m_pBorderImages[3]->GetHeight(), -1) : 0;
				m_pBorderImages[3] ? UI::ImageRender::Render(m_pBorderImages[3], iX, iY + m_iHeightText, m_iWidthText, m_pBorderImages[3]->GetHeight(), -1) : 0;
				m_pBorderImages[4] ? UI::ImageRender::Render(m_pBorderImages[4], iX - m_pBorderImages[4]->GetWidth(), iY - m_pBorderImages[4]->GetHeight(), m_pBorderImages[4]->GetWidth(), m_pBorderImages[4]->GetHeight(), -1) : 0;
				m_pBorderImages[5] ? UI::ImageRender::Render(m_pBorderImages[5], iX + m_iWidthText, iY - m_pBorderImages[5]->GetHeight(), m_pBorderImages[5]->GetWidth(), m_pBorderImages[5]->GetHeight(), -1) : 0;

				LINEHANDLE->MakeLine()->Draw(Rectangle2D(iX - 1, iY - 1, m_iWidthText + 1, m_iHeightText + 1), D3DCOLOR_ARGB(200, 0, 0, 0));
				m_pText->Render(iX, iY, iWidth, iHeight, 0, 0);
			}
		}
	}
	BOOL ToolTip::OnMouseClick(class INPUTS::Mouse *pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		return FALSE;
	}
	void ToolTip::OnMouseMove(class INPUTS::Mouse *pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		if (m_sObjectBox.Inside(pcMouse->GetPosition()))
		{
			m_bHover = TRUE;

			if (m_fProgress == 0.0f)
				Open();

			return;
		}

		if (m_fProgress == 1.0f)
			Close();

		if (m_fProgress == 0.0f)
			m_bHover = FALSE;
	}
}