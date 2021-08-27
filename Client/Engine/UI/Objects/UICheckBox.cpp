#include "StdAfx.h"
#include "UICheckBox.h"

namespace UI
{
	CheckBox::CheckBox(Rectangle2D rRectangle) : Element(rRectangle)
	{

	}
	CheckBox::~CheckBox()
	{
		//Clear();
	}
	void CheckBox::Clear()
	{
		CLEARPTR(m_pImage1);
		CLEARPTR(m_pImage2);

		UI::ImageLoader::DeleteImage(m_pImage1);
		UI::ImageLoader::DeleteImage(m_pImage2);
	}
	void CheckBox::SetFont(const char *pszFont, int iHeight, int iWidth, BOOL bItalic, BOOL bBold, DWORD dwColor)
	{
		m_pFont = FONTHANDLE->MakeFont(pszFont, iHeight, iWidth, bItalic, bBold);
		m_dwColorText = dwColor;
		m_iFontHeight = iHeight;
	}
	void CheckBox::Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		if (IsOpen())
		{
			if (m_pGroup)
			{
				if (!m_pGroup->IsOpen())
					return;

				if (m_pGroup->GetIndexObject() != GetID())
					m_bSelect = FALSE;
				else
					m_bSelect = TRUE;
			}

			int iRenderX = GetX() + iX;
			int iRenderY = GetY() + iY;
			
			UI::ImageRender::Render(m_pImage1, iRenderX, iRenderY, GetWidth(), GetHeight(), -1);

			if (m_bSelect)
				UI::ImageRender::Render(m_pImage2, iRenderX, iRenderY, GetWidth(), GetHeight(), -1);

			m_pFont->Draw(iRenderX + GetWidth() + 5, iRenderY + ((GetHeight() >> 1) - (m_iFontHeight >> 1)), m_strText, DT_WORDBREAK, m_dwColorText);

			Element::Render(iRenderX, iRenderY, GetWidth(), GetHeight(), iSourceX, iSourceY);
		}
	}

	BOOL CheckBox::OnMouseClick(INPUTS::LPMOUSE pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		if (!IsOpen() || m_bDisable || IsEnjoin())
			return FALSE;

		if (m_pGroup)
		{
			if (!m_pGroup->IsOpen())
				return FALSE;
		}

		if (pcMouse->GetEvent() != ClickDownL)
			return FALSE;

		Point2D *psPosition = pcMouse->GetPosition();

		int iRenderX = GetX() + iX + iSourceX;
		int iRenderY = GetY() + iY + iSourceY;
		int iRenderWidth = m_bParentChild ? low(GetWidth(), iWidth - GetX()) : GetWidth();
		int iRenderHeight = m_bParentChild ? low(GetHeight(), iHeight - GetY()) : GetHeight();

		int iTextWidth = m_pFont ? m_pFont->GetWidthText(m_strText.c_str()) : 0;

		//Inside X
		if ((psPosition->iX >= iRenderX) && (psPosition->iX <= (iRenderX + iTextWidth + iRenderWidth - iSourceX)))
		{
			//Inside Y
			if ((psPosition->iY >= iRenderY) && (psPosition->iY <= (iRenderY + iRenderHeight - iSourceY)))
			{
				if (m_pGroup)
				{
					if (!m_bSelect)
						m_pGroup->SetIndexObject(GetID());

					m_bSelect = TRUE;
				}
				else
					m_bSelect = m_bSelect ? FALSE : TRUE;

				UI::Event::Invoke(m_iEventID);

				return TRUE;
			}
		}

		return FALSE;
	}
}