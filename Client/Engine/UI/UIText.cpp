#include "StdAfx.h"
#include "UIText.h"

namespace UI
{
	Text::Text(Rectangle2D rRectangle) : Element(rRectangle)
	{
		m_pFont = FONTHANDLE->MakeFont("Arial",16,0,FALSE,FALSE);
	}
	Text::Text(const std::string & strText,const Rectangle2D & rBox,BOOL bBold, const DWORD dwColor) : Element(rBox)
	{
		m_pFont = FONTHANDLE->MakeFont("Arial",16,0,FALSE,FALSE);
		SetText(strText);
		SetColor(dwColor);
	}
	Text::Text(const Rectangle2D & rBox,BOOL bBold,const DWORD dwColor) : Element(rBox)
	{
		m_pFont = FONTHANDLE->MakeFont("Arial",16,0,FALSE,FALSE);
		SetColor(dwColor);
	}
	Text::~Text()
	{

	}
	void Text::SetFont(const char *pszFont, int iHeight, int iWidth, BOOL bItalic, BOOL bBold,DWORD dwColor)
	{
		m_pFont = FONTHANDLE->MakeFont(pszFont, iHeight, iWidth, bItalic, bBold);
		m_dwColorText = dwColor;
	}
	void Text::UpdateText()
	{
		if (m_iMaxTextWidth > 0)
		{
			int iTextWidth = 0;

			for (UINT i = 0; i < m_strText.size(); i ++)
			{
				wchar_t c = m_strText[i];

				int iWidth = m_pFont ? m_pFont->GetWidthTextW(&c, 1) : 0;

				iTextWidth += iWidth;

				if (iTextWidth >= m_iMaxTextWidth)
				{
					m_strText.insert(m_strText.begin() + i, L'\n');
					iTextWidth = 0;
				}
			}

		}

		if (m_bHighlightText)
		{
			m_iHighlightTextWidth = m_pFont->GetWidthTextW(m_strHighlightText.c_str(), m_strHighlightText.length());
			m_strText = m_strText.substr(m_strHighlightText.length());
		}
	}
	void Text::SetTextEx(char *pszFormat,...)
	{
		va_list vl;

		char szText[1024 * 32];

		va_start(vl,pszFormat);
		_vsnprintf_s(szText,_countof(szText),_TRUNCATE,pszFormat,vl);
		va_end(vl);

		SetText(szText);
	}
	int Text::GetWidthText()
	{
		if (m_bHighlightText)
		{
			int iWidthText = m_pFont->GetWidthTextW(m_strText.c_str(),m_strText.find(L'\n') != std::string::npos ? m_strText.find(L'\n') : m_strText.length());

			return m_pFont->GetWidthTextW(m_strHighlightText.c_str()) + iWidthText;
		}

		return m_pFont->GetWidthTextW(m_strText.c_str(),m_strText.length());
	}
	int Text::GetHeightFont()
	{
		return m_pFont->GetHeightText();
	}
	int Text::GetHeightText()
	{
		int iRenderX = GetX();
		int iRenderY = GetY();
		int iRenderWidth = GetWidth();
		int iRenderHeight = GetHeight();

		RECT rRect;
		rRect.left = iRenderX;
		rRect.top = iRenderY;
		rRect.right = rRect.left + GetWidth();
		rRect.bottom = rRect.top + GetHeight();

		return m_pFont->GetHeightTextW(BuildFormat(), m_strText.c_str(), rRect);
	}
	void Text::Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		//Is activated Button
		int iRenderX = GetX() + iX;
		int iRenderY = GetY() + iY;
		int iRenderWidth = low(GetWidth(),iWidth);
		int iRenderHeight = low(GetHeight(),iHeight);

		DWORD dwColor = m_dwColorText;

		if (m_dwColorTextLink != 0 && m_bHover && !m_bDisable)
			dwColor = m_dwColorTextLink;

		RECT rRect;
		rRect.left	= iRenderX;
		rRect.top	= iRenderY;
		rRect.right	= rRect.left + GetWidth();
		rRect.bottom= rRect.top + GetHeight();

		if (m_bHighlightText && m_strHighlightText.length() > 0 && IsOpen() && !m_bDisable)
		{
			//vector Delimiter
			std::vector<std::string> vLines = split(UnicodeToANSI(m_strText),'\n');

			for (size_t i = 0; i < vLines.size(); i ++)
			{
				if (i == 0)
				{
					if (m_bShadow)
					{
						m_pFont->Draw(RECT{ rRect.left + m_iShadowDistance,rRect.top + m_iShadowDistance,rRect.right,rRect.bottom }, UnicodeToANSI(m_strHighlightText), BuildFormat(), m_dwColorTextShadow != -1 ? m_dwColorTextShadow : D3DCOLOR_XRGB(74, 74, 74));
						m_pFont->Draw(RECT{ rRect.left + m_iHighlightTextWidth + m_iShadowDistance,rRect.top + m_iShadowDistance,rRect.right,rRect.bottom }, vLines[i], BuildFormat(), m_dwColorTextShadow != -1 ? m_dwColorTextShadow : D3DCOLOR_XRGB(74, 74, 74));
					}
					else if (m_dwColorTextOutline)
					{
						m_pFont->Draw(RECT{ rRect.left + 1,rRect.top,rRect.right,rRect.bottom }, UnicodeToANSI(m_strHighlightText), BuildFormat(), m_dwColorTextOutline);
						m_pFont->Draw(RECT{ rRect.left + m_iHighlightTextWidth + 1,rRect.top,rRect.right,rRect.bottom }, vLines[i], BuildFormat(), m_dwColorTextOutline);

						m_pFont->Draw(RECT{ rRect.left,rRect.top + 1,rRect.right,rRect.bottom }, UnicodeToANSI(m_strHighlightText), BuildFormat(), m_dwColorTextOutline);
						m_pFont->Draw(RECT{ rRect.left + m_iHighlightTextWidth,rRect.top + 1,rRect.right,rRect.bottom }, vLines[i], BuildFormat(), m_dwColorTextOutline);

						m_pFont->Draw(RECT{ rRect.left - 1,rRect.top,rRect.right,rRect.bottom }, UnicodeToANSI(m_strHighlightText), BuildFormat(), m_dwColorTextOutline);
						m_pFont->Draw(RECT{ rRect.left + m_iHighlightTextWidth - 1,rRect.top,rRect.right,rRect.bottom }, vLines[i], BuildFormat(), m_dwColorTextOutline);

						m_pFont->Draw(RECT{ rRect.left,rRect.top - 1,rRect.right,rRect.bottom }, UnicodeToANSI(m_strHighlightText), BuildFormat(), m_dwColorTextOutline);
						m_pFont->Draw(RECT{ rRect.left + m_iHighlightTextWidth,rRect.top - 1,rRect.right,rRect.bottom }, vLines[i], BuildFormat(), m_dwColorTextOutline);
					}

					m_pFont->Draw(RECT{ rRect.left,rRect.top,rRect.right,rRect.bottom }, UnicodeToANSI(m_strHighlightText), BuildFormat(), m_dwColorTextHighlight);
					m_pFont->Draw(RECT{ rRect.left + m_iHighlightTextWidth,rRect.top,rRect.right + m_iHighlightTextWidth,rRect.bottom }, vLines[i], BuildFormat(), dwColor);
				}
				else
				{
					UINT uYLine = GetHeightFont();

					if (m_bShadow)
						m_pFont->Draw(RECT{ rRect.left + m_iShadowDistance,rRect.top + (LONG)uYLine + m_iShadowDistance,rRect.right,rRect.bottom + (LONG)uYLine }, vLines[i], BuildFormat(), m_dwColorTextShadow != -1 ? m_dwColorTextShadow : D3DCOLOR_XRGB(74, 74, 74));
					else if (m_dwColorTextOutline)
					{
						m_pFont->Draw(RECT{ rRect.left + 1,rRect.top + (LONG)uYLine,rRect.right,rRect.bottom + (LONG)uYLine }, vLines[i], BuildFormat(), m_dwColorTextOutline);
						m_pFont->Draw(RECT{ rRect.left,rRect.top + (LONG)uYLine + 1,rRect.right,rRect.bottom + (LONG)uYLine }, vLines[i], BuildFormat(), m_dwColorTextOutline);
						m_pFont->Draw(RECT{ rRect.left - 1,rRect.top + (LONG)uYLine,rRect.right,rRect.bottom + (LONG)uYLine }, vLines[i], BuildFormat(), m_dwColorTextOutline);
						m_pFont->Draw(RECT{ rRect.left,rRect.top + (LONG)uYLine - 1,rRect.right,rRect.bottom + (LONG)uYLine }, vLines[i], BuildFormat(), m_dwColorTextOutline);
					}

					m_pFont->Draw(RECT{ rRect.left,rRect.top + (LONG)uYLine,rRect.right,rRect.bottom + (LONG)uYLine }, vLines[i], BuildFormat(), dwColor);
				}
			}
		}
		else if (!m_bHighlightText && IsOpen() && !m_bDisable)
		{
			if (m_bShadow)
				m_pFont->Draw(RECT{ rRect.left + m_iShadowDistance,rRect.top + m_iShadowDistance,rRect.right,rRect.bottom }, UnicodeToANSI(m_strText), BuildFormat(), m_dwColorTextShadow != -1 ? m_dwColorTextShadow : D3DCOLOR_XRGB(74, 74, 74));
			else if (m_dwColorTextOutline)
			{
				m_pFont->Draw(RECT{ rRect.left + 1,rRect.top,rRect.right,rRect.bottom }, UnicodeToANSI(m_strText), BuildFormat(), m_dwColorTextOutline);
				m_pFont->Draw(RECT{ rRect.left,rRect.top + 1,rRect.right,rRect.bottom }, UnicodeToANSI(m_strText), BuildFormat(), m_dwColorTextOutline);

				m_pFont->Draw(RECT{ rRect.left - 1,rRect.top,rRect.right,rRect.bottom }, UnicodeToANSI(m_strText), BuildFormat(), m_dwColorTextOutline);
				m_pFont->Draw(RECT{ rRect.left,rRect.top - 1,rRect.right,rRect.bottom }, UnicodeToANSI(m_strText), BuildFormat(), m_dwColorTextOutline);
			}

			m_pFont->Draw(RECT{ rRect.left,rRect.top,rRect.right,rRect.bottom }, UnicodeToANSI(m_strText), BuildFormat(), dwColor);
		}
		else if (IsOpen() && m_bDisable)
				m_pFont->Draw(RECT{ rRect.left,rRect.top,rRect.right,rRect.bottom }, UnicodeToANSI(m_strText), BuildFormat(), D3DCOLOR_ARGB(255, 135, 135, 135));

		Element::Render(iRenderX,iRenderY,GetWidth(),GetHeight(),iSourceX,iSourceY);
	}
	UINT Text::BuildFormat() const
	{
		UINT uFormat = DT_EXPANDTABS;

		switch(m_eHorizontalAlign)
		{
		default:
		case ALIGN_Left:
			uFormat |= DT_LEFT;
			break;
		case ALIGN_Center:
			uFormat |= DT_CENTER;
			break;
		case ALIGN_Right:
			uFormat |= DT_RIGHT;
			break;
		}

		switch(m_eVerticalAlign)
		{
		default:
		case ALIGN_Top:
			uFormat |= DT_TOP;
			break;
		case ALIGN_Middle:
			uFormat |= DT_VCENTER;
			break;
		case ALIGN_Bottom:
			uFormat |= DT_BOTTOM;
			break;
		}

		if (!m_bMultiLine)
			uFormat |= DT_SINGLELINE;

		if (m_bWordWrap)
			uFormat |= DT_WORDBREAK;

		if (m_bNoClip)
			uFormat |= DT_NOCLIP;

		return uFormat;
	}
	BOOL Text::OnMouseClick(class INPUTS::Mouse *pcMouse,int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY)
	{
		if (!IsOpen() || IsLinkObject())
			return FALSE;

		EMouseEvent eEvent = pcMouse->GetEvent();

		if (eEvent != m_eMouseEvent)
			return FALSE;

		Point2D *psPosition = pcMouse->GetPosition();

		int iRenderX = GetX() + iX + iSourceX;
		int iRenderY = GetY() + iY + iSourceY;
		int iRenderWidth = m_bParentChild ? low(GetWidth(),iWidth - GetX()) : GetWidth();
		int iRenderHeight = m_bParentChild ? low(GetHeight(),iHeight - GetY()) : GetHeight();

		//Inside X
		if ((psPosition->iX >= iRenderX) && (psPosition->iX <= (iRenderX + iRenderWidth - iSourceX)))
		{
			//Inside Y
			if ((psPosition->iY >= iRenderY) && (psPosition->iY <= (iRenderY + iRenderHeight - iSourceY)))
			{
				if (m_bSelectType)
				{
					if (m_pGroup)
					{
						if (!m_bSelect)
							m_pGroup->SetIndexObject(GetID());

						m_bSelect = TRUE;
					}
					else
						m_bSelect = m_bSelect ? FALSE : TRUE;
				}

				if (m_bSelectType || m_iEventID != -1)
				{
					UI::Event::Invoke(m_iEventID);
					return TRUE;
				}
			}
		}

		return FALSE;
	}

	void Text::OnMouseMove(class INPUTS::Mouse *pcMouse,int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY)
	{
		if (!IsOpen() || IsLinkObject())
			return;

		Point2D *psPosition = pcMouse->GetPosition();

		int iRenderX = GetX() + iX + iSourceX;
		int iRenderY = GetY() + iY + iSourceY;
		int iRenderWidth = m_bParentChild ? low(GetWidth(),iWidth - GetX()) : GetWidth();
		int iRenderHeight = m_bParentChild ? low(GetHeight(),iHeight - GetY()) : GetHeight();

		BOOL bOldHover = m_bHover;

		m_bHover = FALSE;

		//Inside X
		if ((psPosition->iX >= iRenderX) && (psPosition->iX <= (iRenderX + iRenderWidth - iSourceX)))
		{
			//Inside Y
			if ((psPosition->iY - iRenderY) && (psPosition->iY <= (iRenderY + iRenderHeight - iSourceY)))
			{
				m_bHover = TRUE;

				if (m_bHover != bOldHover && m_iHoverEventID != -1)
				{
					UI::Event::Invoke(m_iHoverEventID);
				}
			}
		}
	}
}