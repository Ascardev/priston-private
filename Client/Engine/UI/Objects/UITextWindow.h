#pragma once

namespace UI
{
	typedef struct ParamsWindow *LPPARAMSWINDOW;

	struct ParamsWindow
	{
		std::string strParam;
		std::string strValue;
	};
	typedef std::shared_ptr<class TextWindow> LPTEXTWINDOW;

	class TextWindow : public Element
	{
	public:
		TextWindow(Rectangle2D rRectangle);
		virtual ~TextWindow();

		void Clear();
		std::string GetText() { return m_strText; }
		void SetText(std::string str) { m_strText = str; }
		void SetFont(const char *pszFont, int iHeight, int iWidth, BOOL bItalic, BOOL bBold, DWORD dwColor);
		void SetParam(std::string strParam, std::string strValue);
		void SetParentChild(BOOL b) { m_bParentChild = b; }
		BOOL IsParentChild() { return m_bParentChild; }
		void SetBox(Rectangle2D sBox);

		//int GetHeightText();

		void Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
		void LoadTextFromFile(const char *pszFile);

		void Append(std::string str) { m_strText.append(str); }
	private:
		std::string m_strText;
		BOOL m_bParentChild = TRUE;
		DWORD m_dwColorText = -1;
		DX::LPFONT m_pFont = NULL;
		std::vector< LPPARAMSWINDOW> m_vpParams;
	};
}