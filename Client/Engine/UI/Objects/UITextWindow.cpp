#include "StdAfx.h"
#include "UITextWindow.h"

namespace UI
{
	TextWindow::TextWindow(Rectangle2D rRectangle) : Element(rRectangle)
	{

	}
	TextWindow::~TextWindow()
	{
		Clear();
	}
	void TextWindow::Clear()
	{
		for (auto &v : m_vpParams)
		{
			DELET(v);
		}

		m_vpParams.clear();
	}
	void TextWindow::SetFont(const char *pszFont, int iHeight, int iWidth, BOOL bItalic, BOOL bBold, DWORD dwColor)
	{
		m_pFont = FONTHANDLE->MakeFont(pszFont, iHeight, iWidth, bItalic, bBold);
		m_dwColorText = dwColor;
	}
	void TextWindow::SetBox(Rectangle2D sBox)
	{
		m_rRect = sBox;
	}
	void TextWindow::Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		int iRenderX = GetX() + iX;
		int iRenderY = GetY() + iY;

		std::string str = m_strText;

		for (const auto &v : m_vpParams)
		{
			std::size_t pos = str.find(v->strParam);

			if (pos != std::string::npos)
				str.replace(str.begin() + pos, str.begin() + pos + v->strParam.length(), v->strValue.begin(), v->strValue.end());
		}

		RECT rRect{ iRenderX,iRenderY,iRenderX + m_rRect.iWidth,iRenderY + m_rRect.iHeight };
		
		if (m_pFont)
			m_pFont->Draw(rRect, str, DT_WORDBREAK, m_dwColorText);
	}
	void TextWindow::SetParam(std::string strParam, std::string strValue)
	{
		for (const auto &v : m_vpParams)
		{
			if (v->strParam.compare(strParam) == 0)
			{
				v->strValue = strValue;
				return;
			}
		}

		LPPARAMSWINDOW pParam = new ParamsWindow;

		pParam->strParam = strParam;
		pParam->strValue = strValue;

		m_vpParams.push_back(pParam);
	}

	void TextWindow::LoadTextFromFile(const char *pszFile)
	{
		CFILE::Bin cFile;
		static char szBuffer[1024 * 8];

		STRINGEMPTY(szBuffer);

		if (cFile.Open(pszFile, BIN_READ))
		{
			int iSize = cFile.GetSize();

			if (iSize > 1024 * 8)
				iSize = 1024 * 8;

			cFile.Read(szBuffer, iSize);
			cFile.Close();
		}

		m_strText = szBuffer;
	}
}