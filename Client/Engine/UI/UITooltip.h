#pragma once

enum ETooltipPosition
{
	TOOLTIPPOSITION_None,

	TOOLTIPPOSITION_Top,
	TOOLTIPPOSITION_Right,
	TOOLTIPPOSITION_Left,
	TOOLTIPPOSITION_Bottom,
};

namespace UI
{
	typedef std::shared_ptr<class ToolTip> LPTOOLTIP;

	class ToolTip : public Element
	{
	public:
		ToolTip(Rectangle2D rRectangle);
		virtual ~ToolTip();

		void Init();
		void Clear();

		void SetLinkObject(LPELEMENT pObject) { m_pLinkObject = pObject; }
		void SetFont(const char *pszFontName, int iFontSize, DWORD dwColor);
		void SetText(std::string strText);
		void SetTextColor(Color c) { m_pText ? m_pText->SetColor(c.Get()) : 0; }

		ETooltipPosition GetPosition() { return m_ePosition; }
		void SetPosition(ETooltipPosition e) { m_ePosition = e; }

		BOOL GetFollowMouse() { return m_bFollowMouse; }
		void SetFollowMouse(BOOL b) { m_bFollowMouse = b; }

		BOOL IsHover() { return m_bHover; }
		void SetHover(BOOL b) { m_bHover = b; }

		void Open();
		void Close();

		void Update(float fTime);
		void Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);

		BOOL OnMouseClick(class INPUTS::Mouse *pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
		void OnMouseMove(class INPUTS::Mouse *pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
	private:
		ETooltipPosition m_ePosition = TOOLTIPPOSITION_None;
		LPELEMENT m_pLinkObject = NULL;
		int m_iWidthText = -1;
		int m_iHeightText = -1;
		int m_iFadeType = 0;
		float m_fProgress = 0.0f;
		Rectangle2D m_sObjectBox;
		LPTEXT m_pText = NULL;
		BOOL m_bTransition = FALSE;
		BOOL m_bHover = FALSE;
		BOOL m_bFollowMouse = FALSE;
		LPIMAGE m_pBorderImages[6];
	};
}