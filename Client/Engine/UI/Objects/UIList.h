#pragma once

namespace UI
{
	typedef std::shared_ptr<class List> LPLIST;

	class List : public Element
	{
	public:
		List();
		List(Rectangle2D rRectangle);
		virtual ~List();

		void Clear();
		LPSCROLL MakeScrollBar(Rectangle2D sBox, std::string strScrollBarPath, std::string strScrollerPath);

		int GetCountItemsList() { return m_vpWindows.size(); }
		int GetListWidth();
		int GetListHeight();
		int GetPaddingSeparator() { return m_iPaddingSeparator; }
		void SetPaddingSaparator(int i) { m_iPaddingSeparator = i; }

		void SetCountAxisHidden(BOOL b) { m_bCountAxisHidden = b; }
		void SetForceDown(BOOL b);
		void SetNoUpdatePosition(BOOL b) { m_bNoupdatePosition = b; }

		void SetHorizontal(BOOL b) { m_bHorizontalPadding = b; }

		void SetNoClip(BOOL b) { m_bNoClip = b; }

		void AddWindow(LPWINDOW pWindow);
		LPWINDOW GetWindow(int iIDObject);
		void SetScrollBar(LPSCROLL p) { m_pScrollBar = p; }
		LPSCROLL GetScrollBar() { return m_pScrollBar; }
		void SetScrollFirst(BOOL b) { m_bScrollFirst = b; }
		void SetColorBackground(Color c) { m_cColorBackground = c; }
		std::deque<LPWINDOW> &GetWindowList() { return m_vpWindows; }

		void AddAxis(int iX, int iY);
		void SetAxis(int iX, int iY);

		void Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
		void Update(float fTime);

		BOOL OnMouseClick(INPUTS::LPMOUSE pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
		BOOL OnMouseScroll(INPUTS::LPMOUSE pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
		void OnMouseMove(INPUTS::LPMOUSE pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
		BOOL OnKeyChar(INPUTS::LPKEYBOARD pcKeyboard);
		BOOL OnKeyPress(INPUTS::LPKEYBOARD pcKeyboard);
	protected:
		BOOL IsForceDown() { return ((m_bForceDown == TRUE) && (m_bHorizontalPadding == FALSE)) ? TRUE : FALSE; }
	private:
		int m_iPaddingSeparator = 0;
		int m_iAddAxisX = 0;
		int m_iAddAxisY = 0;
		int m_iScroll = 0;
		BOOL m_bCountAxisHidden = FALSE;
		BOOL m_bNoupdatePosition = FALSE;
		BOOL m_bHorizontalPadding = FALSE;
		BOOL m_bNoClip = FALSE;
		BOOL m_bScrollFirst = FALSE;
		BOOL m_bForceDown = FALSE;
		Color m_cColorBackground = 0;
		LPSCROLL m_pScrollBar = NULL;
		std::deque<LPWINDOW> m_vpWindows;
	};
}
