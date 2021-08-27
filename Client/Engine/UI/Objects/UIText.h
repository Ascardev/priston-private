#pragma once

enum EALIGN
{
	ALIGN_Left		= 0,
	ALIGN_Center	= 1,
	ALIGN_Right		= 2,

	ALIGN_Top		= 0,
	ALIGN_Middle	= 1,
	ALIGN_Bottom	= 2,
};

namespace UI
{
	typedef std::shared_ptr<class Text> LPTEXT;

	class Text : public Element
	{
	public:
		Text(class Rectangle2D rRectangle);
		Text(const std::string & strText,const Rectangle2D & rBox,BOOL bBold, const DWORD dwColor);
		Text(const Rectangle2D & rBox,BOOL bBold,const DWORD dwColor);
		virtual ~Text();

		void Clear() {}

		void SetText(std::string str) { m_strText = ANSIToUnicode(str); UpdateText(); }
		void SetTextEx(char *pszFormat,...);

		void SetMaxTextWidth(int i) {m_iMaxTextWidth = i;}

		void PrependText(std::string str) { m_strText.insert(0, ANSIToUnicode(str)); }
		void AppendText(std::string str) { m_strText.append(ANSIToUnicode(str)); }

		void SetEvent(int iEvent) {m_iEventID = iEvent;}
		void SetHoverEvent(int iEvent) {m_iHoverEventID = iEvent;}
		void SetSelectType(BOOL b) {m_bSelectType = b;}

		void SetDisabled(BOOL b) {m_bDisable = b;}
		BOOL GetDisabled() {return m_bDisable;}

		void SetColor(DWORD dwColor) {m_dwColorText = dwColor;}
		DWORD GetColor() {return m_dwColorText;}

		void SetDropdownColor(DWORD dwColor) { m_dwColorTextShadow = dwColor; }
		void SetOutlineColor(DWORD dwColor) { m_dwColorTextOutline = dwColor; }
		void SetDropdownShadowDistance(int iDistance) { m_iShadowDistance = iDistance; }

		void SetColorHover(DWORD dwColor) { m_dwColorTextLink = dwColor; }
		void SetDropdownShadow(BOOL b) { m_bShadow = b; }

		void SetMultiLine(BOOL b) { m_bMultiLine = b; }
		BOOL GetMultiLine() { return m_bMultiLine; }

		void SetWordWrap(BOOL b) { m_bWordWrap = b; }
		BOOL GetWordWrap() { return m_bWordWrap; }

		void SetNoClip(BOOL b) { m_bNoClip = b; }
		BOOL GetNoClip() { return m_bNoClip; }

		void SetHorizontalAlign(EALIGN e) { m_eHorizontalAlign = e; }
		EALIGN GetHorizontalAlign() const { return m_eHorizontalAlign; }

		void SetVerticalAlign(EALIGN e) { m_eVerticalAlign = e; }
		EALIGN GetVerticalAlign() const { return m_eVerticalAlign; }

		void SetHighlightText(BOOL b) { m_bHighlightText = b; }
		void SetHighlightText(std::string str) { m_strHighlightText = ANSIToUnicode(str); }
		void SetHighlightTextColor(DWORD dwColor) { m_dwColorTextHighlight = dwColor; }

		void UpdateText();

		void SetFont(const char *pszFont, int iHeight, int iWidth, BOOL bItalic, BOOL bBold,DWORD dwColor);

		std::string GetText() { return UnicodeToANSI(m_strText); }

		int GetWidthText();

		int GetHeightFont();
		int GetHeightText();

		void Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);

		UINT BuildFormat() const;

		BOOL OnMouseClick(INPUTS::LPMOUSE pcMouse,int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY);
		void OnMouseMove(INPUTS::LPMOUSE pcMouse,int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY);
	private:
		DX::LPFONT m_pFont;

		EMouseEvent m_eMouseEvent = ClickDownL;

		DWORD m_dwColorText = -1;
		DWORD m_dwColorTextLink = 0;
		DWORD m_dwColorTextHighlight;
		DWORD m_dwColorTextShadow = -1;
		DWORD m_dwColorTextOutline = 0;

		std::wstring m_strText;
		std::wstring m_strHighlightText;

		int m_iMaxTextWidth = -1;
		int m_iHighlightTextWidth = -1;

		int m_iShadowDistance = 1;

		int m_iEventID = -1;
		int m_iHoverEventID = -1;

		std::shared_ptr<class Group> m_pGroup = NULL;

		BOOL m_bSelectType = FALSE;
		BOOL m_bSelect = FALSE;
		BOOL m_bParentChild = TRUE;

		BOOL m_bHighlightText = FALSE;
		BOOL m_bShadow = FALSE;

		BOOL m_bHover = FALSE;

		BOOL m_bDisable = FALSE;

		BOOL m_bMultiLine = FALSE;
		BOOL m_bWordWrap = FALSE;
		BOOL m_bNoClip = TRUE;

		EALIGN m_eHorizontalAlign = ALIGN_Left;
		EALIGN m_eVerticalAlign = ALIGN_Top;
	};
}