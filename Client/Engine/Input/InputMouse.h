#pragma once

enum EMouseEvent
{
	None,
	ClickDownL,
	ClickUpL,
	ClickDownR,
	ClickUpR,
	DoubleClickL,
	DoubleClickR,
	ScrollUp,
	ScrollDown,
};

namespace INPUTS
{
	class Mouse
	{
	public:
		Mouse();
		virtual ~Mouse();

		EMouseEvent GetEvent(DWORD dwKey);
		EMouseEvent GetEvent() { return m_eEventMouse; }

		void OnMouseMove(int iX, int iY);
		BOOL OnMouseScroll(short sDistance);
		BOOL OnMouseClick(DWORD dwKey);

		Point2D *GetPosition() { return &m_Position; }
		short GetDistance() { return m_sDistance; }

		void IsNoMove(BOOL b);
		BOOL IsNoMove() { return m_bNoMove; }

		void BlockMouse();
		void UnblockMouse();
	private:
		Point2D m_Position;
		int m_iLastCursorID = 0;
		int m_iCursorID = 0;
		short m_sDistance = 0;
		int m_iBlockedRefCount = 0;
		BOOL m_bNoMove = FALSE;
		BOOL m_bEndNoMove = FALSE;
		EMouseEvent m_eEventMouse = (EMouseEvent)-1;
	};
}
