#include "StdAfx.h"
#include "DXFont.h"

namespace DX
{
	Font::Font(LPD3DXFONT hFont) : m_hFont(hFont)
	{
		ADDREF(m_hFont);

		LoadFontScript();
	}

	void Font::OnLostDevice()
	{
		if (m_hFont)
			m_hFont->OnLostDevice();
	}

	void Font::OnResetDevice()
	{
		if (m_hFont)
			m_hFont->OnResetDevice();
	}
	void Font::Draw(int x,int y,const std::string &strText,UINT uFormat,D3DCOLOR Color)
	{
		int iWidth = GRAPHICENGINE->GetBackWidth() + x;
		int iHeight = GRAPHICENGINE->GetBackHeight() + y;

		RECT Rect = {x,y,iWidth,iHeight};

		Draw(Rect,strText.c_str(),strText.length(),uFormat,Color);
	}
	void Font::Draw(RECT &rRect,const std::string &strText,UINT uFormat,D3DCOLOR Color)
	{
		Draw(rRect, strText.c_str(), strText.length(), uFormat, Color);
	}
	void Font::Draw(RECT &rRect,LPCTSTR pText,int iCount,UINT uFormat,D3DCOLOR Color)
	{
		if (iCount <= 0)
			iCount = STRLEN(pText);

		static char szBuf[2048];

		STRINGEMPTY(szBuf);
		STRINGCOPY(szBuf,pText);

		if (m_hFont)
			m_hFont->DrawTextA(NULL,szBuf,iCount,&rRect,uFormat,Color);
	}
	int Font::GetWidthText(const char *pszText,int iSize)
	{
		/*std::string strText(pszText);
		int iWidthText = 0;

		for (int i = 0; i < iSize; i++)
		{
			if (strText[i] == 0x20)
				iWidthText += m_iWhitespace;
			else
			{
				RECT rRect = { 0,0,0,0 };

				m_hFont->DrawTextA(NULL, &strText[i], 1, &rRect, DT_CALCRECT, -1);
				iWidthText += rRect.right - rRect.left;
			}
		}

		return iWidthText;*/

		return  GetSizeText(pszText, iSize).cx;
	}
	int Font::GetWidthTextW(const wchar_t *pszText, int iSize)
	{
		int iWidthText = 0;

		for (int i = 0; i < iSize; i++)
		{
			if (pszText[i] == L' ')
			{
				iWidthText += m_iWhitespace;
			}
			else
			{
				RECT rRect = { 0,0,0,0 };

				m_hFont->DrawTextW(NULL, &pszText[i], 1, &rRect, DT_CALCRECT, -1);
				iWidthText += rRect.right - rRect.left;
			}
		}

		return iWidthText;
	}
	int Font::GetHeightTextW(const wchar_t *pszText, RECT rRect)
	{
		m_hFont->DrawTextW(NULL, pszText, lstrlenW(pszText), &rRect, DT_WORDBREAK | DT_CALCRECT, D3DCOLOR_XRGB(0, 0, 0));
		return rRect.bottom - rRect.top;
	}
	int Font::GetHeightTextW(UINT uFormat, const wchar_t *pszText, RECT rRect)
	{
		m_hFont->DrawTextW(NULL, pszText, lstrlenW(pszText), &rRect, uFormat | DT_CALCRECT, D3DCOLOR_XRGB(0, 0, 0));
		return rRect.bottom - rRect.top;
	}
	int Font::GetHeightText(const char *pszText,int iSize)
	{
		return  GetSizeText(pszText,iSize).cy;
	}
	int Font::GetHeightText()
	{
		return GetSizeText("-",1).cy;
	}
	SIZE Font:: GetSizeText(const char *pszText,int iSize)
	{
		SIZE Size = { 0 };

		if (iSize < 0 || iSize > STRLEN(pszText))
			iSize = STRLEN(pszText);

		if (m_hFont)
			GetTextExtentPoint(m_hFont->GetDC(), pszText,iSize,&Size);

		return Size;
	}
	void Font::LoadFontScript()
	{
		if (m_hFont)
		{
			int iWidthUnderline;

			m_hFont->GetDescA(&m_d3dFontDesc);

			RECT rRect;

			rRect = { 0,0,0,0 };

			m_hFont->DrawTextA(NULL, "_", 1, &rRect, DT_CALCRECT, -1);
			iWidthUnderline = rRect.right - rRect.left;

			rRect = { 0,0,0,0 };

			m_hFont->DrawTextA(NULL, " _", 2, &rRect, DT_CALCRECT, -1);
			m_iWhitespace = (rRect.right - rRect.left) - iWidthUnderline;
		}
	}
}