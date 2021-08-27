#pragma once

namespace UI
{
	struct ActionKeyboard
	{
		DWORD dwKey;
		int iEventID;

		ActionKeyboard(DWORD _dwKey, int _iEventID) { dwKey = _dwKey; iEventID = _iEventID; }
	};

	typedef std::shared_ptr<class InputField> LPINPUTFIELD;

	class InputField : public Element
	{
	public:
		InputField(Rectangle2D rRectangle);
		virtual ~InputField();

		void Clear();

		std::string GetText();

		LPGROUP GetGroup() { return m_pGroup; }
		void SetGroup(LPGROUP pGroup) { m_pGroup = pGroup; }
		void SetTextAlign(EALIGN eHorizontal, EALIGN eVertical) { m_eHorizontal = eHorizontal; m_eVerticalAlign = eVertical; }
		void SetImage(class Image *pImage) { m_pImage = pImage; }
		void SetParentChild(BOOL b) { m_bParentChild = b; }
		void SetMaxLength(int iLen) { m_iTextLength = iLen; }
		void SetSelect(BOOL b) { m_bSelectType = b; }
		void ClearInput();
		void SetPasswordMode(BOOL b) { m_bPassword = b; }
		void SetCanScroll(BOOL b) { m_bCanScroll = b; }
		BOOL GetCanScroll() { return m_bCanScroll; }
		BOOL IsParentChild() { return m_bParentChild; }
		void SetFont(const char *pszFont, int iHeight, int iWidth, BOOL bItalic, BOOL bBold, DWORD dwColor);
		void SetText(std::string str) { m_strText = ANSIToUnicode(str); m_iCurrPosition = m_strText.length(); }
		void SetAllowCharacters(std::string str) { m_strAllowed = ANSIToUnicode(str); m_bAllowedRule = TRUE; }
		BOOL IsSelected() { return m_bSelect; }
		void SetSelected(BOOL b) { m_bSelect = b; if (m_pGroup && b) m_pGroup->SetIndexObject(GetID()); }
		void SetIsNumber(BOOL b, int iMin, int iMax);
		void BlindActiveKeyboard(ActionKeyboard s) { m_vBindActiveKeyboard.push_back(s); }
		void AddInput(std::string str);
		void SetRegex(const char *pszRegex) { m_strRegex = pszRegex; m_bRegex = TRUE; }
		void Update(float fTime);
		BOOL IsHover() { return m_bHover; }

		void BindActionKeyboard(ActionKeyboard s) { m_vBindActiveKeyboard.push_back(s); };

		void Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);

		void OnMouseMove(class INPUTS::Mouse *pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
		BOOL OnMouseClick(class INPUTS::Mouse *pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
		BOOL OnMouseScroll(class INPUTS::Mouse *pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
		BOOL OnKeyChar(class INPUTS::KeyBoard *pcKeyboard);
		BOOL OnKeyPress(class INPUTS::KeyBoard *pcKeyboard);
	protected:
		void UndoAction();
		UINT BuildFormat() const;
	private:
		std::wstring m_strText;
		std::wstring m_strAllowed;
		std::wstring m_strPassword;
		std::string m_strRegex;
		class Image *m_pImage;
		int m_iFontheight = 0;
		int m_iTextLength;
		int m_iMinNum = 0;
		int m_iMaxNum = 100;
		int m_iCurrPosition = 0;
		int m_iBarTextTime = 166;
		int m_iSelectedTextLength = 0;
		int m_iSelectedTextPos = 0;
		DWORD m_dwColorText = -1;
		DWORD m_dwTimeBarText = 0;
		BOOL m_bHover = FALSE;
		BOOL m_bAllowedRule = FALSE;
		BOOL m_bParentChild = TRUE;
		BOOL m_bCanScroll = FALSE;
		BOOL m_bSelect = FALSE;
		BOOL m_bSelectType = FALSE;
		BOOL m_bIsNumber = FALSE;
		BOOL m_bBarTextShow = FALSE;
		BOOL m_bSelectingText = FALSE;
		BOOL m_bPassword = FALSE;
		BOOL m_bRegex = FALSE;
		EALIGN m_eHorizontal = ALIGN_Left;
		EALIGN m_eVerticalAlign = ALIGN_Top;
		LPGROUP m_pGroup = NULL;
		DX::LPFONT m_pFont = NULL;
		Rectangle2D m_sSelectedTextBox = Rectangle2D();
		std::vector<std::wstring> m_vInputActives;
		std::vector<ActionKeyboard> m_vBindActiveKeyboard;
	};
}