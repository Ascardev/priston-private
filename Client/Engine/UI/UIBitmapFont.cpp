#include "StdAfx.h"
#include "UIBitmapFont.h"

namespace UI
{
	BitmapFont::BitmapFont(Rectangle2D rRectangle) : Element(rRectangle)
	{

	}
	BitmapFont::~BitmapFont()
	{
		m_sFont.Clear();
	}
	void BitmapFont::Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		int iRenderX = GetX() + iX;
		int iRenderY = GetY() + iY;

		if (m_eHorizontalAlign == ALIGN_Center)
			iRenderX += (m_rRect.iWidth >> 1) - (GetTextWidth() >> 1);

		if (m_pImageFont)
		{
			int iPaddingX = 0;

			for (UINT i = 0; i < m_strText.size(); i++)
			{
				int iLetterID = m_strText[i];
				LetterData * p = &m_sFont.Find(iLetterID);
				int iExtraY = p->iPaddingY - m_sFont.iBaseY;

				UI::ImageRender::Render(m_pImageFont, iRenderX + iPaddingX, iRenderY + iExtraY, p->sBox.iWidth, p->sBox.iHeight, p->sBox.iX, p->sBox.iY, m_dwColor, m_fScale);

				if (p->sBox.iWidth)
				{
					int iDifference = abs(p->iPaddingX - p->sBox.iWidth);
					iPaddingX += (int)((float)(p->sBox.iWidth - iDifference) * m_fScale);
				}
				else
					iPaddingX += p->iPaddingX;
			}
		}
	}
	int BitmapFont::GetTextWidth()
	{
		if (m_iWidthText == -1)
		{
			if (m_strText.size() > 0)
			{
				m_iWidthText = 0;

				for (UINT i = 0; i < m_strText.size(); i++)
				{
					int iLetterID = m_strText[i];
					LetterData * p = &m_sFont.Find(iLetterID);

					if (p->sBox.iWidth)
					{
						int iDifference = abs(p->iPaddingX - p->sBox.iWidth);
						m_iWidthText += (int)((float)(p->sBox.iWidth - iDifference) * m_fScale);
					}
					else
						m_iWidthText += p->iPaddingX;
				}
			}
		}

		return m_iWidthText;
	}
	void BitmapFont::ReadFontData(const char *pszFile)
	{
		CFILE::Ini cReader(pszFile);

		m_sFont.iLineHeight = cReader.ReadInt("Font", "LineHeight");
		m_sFont.iLettersCount = cReader.ReadInt("Font", "Count");
		m_sFont.iBaseY = cReader.ReadInt("Font", "BaseY");

		for (int i = 0; i < m_sFont.iLettersCount; i++)
		{
			LetterData sLetterWrapper;
			sLetterWrapper.iID = cReader.ReadInt(FormatString("Letter%d", i), "ID");
			sLetterWrapper.sBox.iX = cReader.ReadInt(FormatString("Letter%d", i), "X");
			sLetterWrapper.sBox.iY = cReader.ReadInt(FormatString("Letter%d", i), "Y");
			sLetterWrapper.sBox.iWidth = cReader.ReadInt(FormatString("Letter%d", i), "WidthSource");
			sLetterWrapper.sBox.iHeight = cReader.ReadInt(FormatString("Letter%d", i), "HeightSource");
			sLetterWrapper.iPaddingY = cReader.ReadInt(FormatString("Letter%d", i), "PaddingY");
			sLetterWrapper.iPaddingX = cReader.ReadInt(FormatString("Letter%d", i), "PaddingX");

			m_sFont.Add(sLetterWrapper);
		}
	}
}