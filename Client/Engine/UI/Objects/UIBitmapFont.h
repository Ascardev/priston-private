#pragma once

namespace UI
{
	struct LetterData
	{
		int iID;
		Rectangle2D sBox;
		int iPaddingX,iPaddingY;
	};
	struct FontData
	{
		int iLineHeight;
		int iLettersCount;
		int iBaseY;

		std::vector<LetterData> vLetters;

		void Add(LetterData d) { vLetters.push_back(d); }
		void Clear() { vLetters.clear(); }
		LetterData Find(int iID)
		{
			for (auto &v : vLetters)
			{
				if (v.iID == iID)
					return v;
			}

			return vLetters[0];
		}
	};

	typedef std::shared_ptr<class BitmapFont> LPBITMAPFONT;

	class BitmapFont : public Element
	{
	public:
		BitmapFont(Rectangle2D rRectangle);
		virtual ~BitmapFont();

		int GetTextWidth();
		void ReadFontData(const char *pszFile);
		void SetFontImage(LPIMAGE p) { m_pImageFont = p; }
		void SetText(std::string str) { m_iWidthText = -1; m_strText = str; }
		void SetColor(DWORD d) { m_dwColor = d; }
		void SetScale(float f) { m_fScale = f; }
		void SetHorizontalAlign(EALIGN e) { m_eHorizontalAlign = e; }
		void Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
	private:
		DWORD m_dwColor = -1;
		int m_iWidthText = -1;
		EALIGN m_eHorizontalAlign = ALIGN_Left;
		float m_fScale = 1.0f;
		LPIMAGE m_pImageFont = NULL;
		std::string m_strText;
		FontData m_sFont;
	};
}
