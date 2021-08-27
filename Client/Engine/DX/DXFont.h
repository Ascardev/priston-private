#pragma once

namespace DX
{
	typedef std::shared_ptr<class Font> LPFONT;
	class Font
	{
	public:
		Font(LPD3DXFONT hFont);
		virtual ~Font(){}

		void OnLostDevice();
		void OnResetDevice();

		void Draw(int x,int y,const std::string &strText,UINT uFormat,D3DCOLOR Color);
		void Draw(RECT &rRect,const std::string &strText,UINT uFormat,D3DCOLOR Color);

		int GetWidthText(const char *pszText,int iSize = -1);
		int GetWidthTextW(const wchar_t *pszText, int iSize = -1);
		int GetHeightTextW(const wchar_t *pszText, RECT rRect);
		int GetHeightTextW(UINT uFormat, const wchar_t *pszText, RECT rRect);
		//int GetHeightTextW(const wchar_t *pszText, int iSize = -1);
		int GetHeightText(const char *pszText,int iSize = -1);
		int GetHeightText();

		D3DXFONT_DESCA GetFontDesc(){return m_d3dFontDesc;}

	protected:
		SIZE GetSizeText(const char *pszText,int iSize);
		void Draw(RECT &rRect,LPCTSTR pText,int iCount,UINT uFormat,D3DCOLOR Color);
		void LoadFontScript();
	private:
		LPD3DXFONT m_hFont;
		D3DXFONT_DESCA m_d3dFontDesc;
		int m_iWhitespace = 0;
	};
}