#pragma once

namespace UI
{
	typedef std::shared_ptr<class CheckBox> LPCHECKBOX;

	class CheckBox : public Element
	{
	public:
		CheckBox(Rectangle2D rRectangle);
		virtual ~CheckBox();

		void Clear();

		void SetFont(const char *pszFont, int iHeight, int iWidth, BOOL bItalic, BOOL bBold, DWORD dwColor);
		void SetText(std::string str) { m_strText = str; }
		void SetGroup(LPGROUP pGroup) { m_pGroup = pGroup; }
		void SetImage(class Image *pImage1, class Image *pImage2) { m_pImage1 = pImage1; m_pImage2 = pImage2; }
		void SetEvent(int iEvent) { m_iEventID = iEvent; }
		void SetCheck(BOOL b) { m_bSelect = b; }
		BOOL IsChecked() { return m_bSelect; }

		void Disable() { m_bDisable = TRUE; }
		void Enable() { m_bDisable = FALSE; }

		void Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);

		//Event handlers
		BOOL OnMouseClick(INPUTS::LPMOUSE pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
	private:
		class Image *m_pImage1 = NULL;
		class Image *m_pImage2 = NULL;
		int m_iEventID = -1;
		int m_iFontHeight = 0;
		BOOL m_bSelect = FALSE;
		BOOL m_bDisable = FALSE;
		BOOL m_bParentChild = TRUE;
		std::string m_strText;
		LPGROUP m_pGroup = NULL;
		DWORD m_dwColorText;
		DX::LPFONT m_pFont = NULL;
	};
}
