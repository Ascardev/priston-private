#include "StdAfx.h"
#include "InputMouse.h"

namespace INPUTS
{
	Mouse::Mouse()
	{
		m_Position.iX = 0;
		m_Position.iY = 0;
	}
	Mouse::~Mouse()
	{

	}
	EMouseEvent Mouse::GetEvent(DWORD dwKey)
	{
		switch (dwKey)
		{
		case WM_LBUTTONDOWN:
			return ClickDownL;
		case WM_LBUTTONUP:
			return ClickUpL;
		case WM_RBUTTONDOWN:
			return ClickDownR;
		case WM_RBUTTONUP:
			return ClickUpR;
		}

		return (EMouseEvent)-1;
	}
	void Mouse::OnMouseMove(int iX, int iY)
	{
		if (GAMECOREHANDLE->IsInit())
		{
			m_Position.iX = iX;
			m_Position.iY = iY;

			GAME->OnMouseMove(this);
		}
	}
	BOOL Mouse::OnMouseScroll(short sDistance)
	{
		if (GAMECOREHANDLE->IsInit())
		{
			m_sDistance = sDistance / WHEEL_DELTA;

			if (sDistance < 0)
				m_eEventMouse = ScrollUp;
			else
				m_eEventMouse = ScrollDown;

			return GAME->OnMouseScroll(this);
		}

		return FALSE;
	}
	BOOL Mouse::OnMouseClick(DWORD dwKey)
	{
		if (GAMECOREHANDLE->IsInit())
		{
			if (m_bEndNoMove)
			{
				m_bEndNoMove = FALSE;
				IsNoMove(FALSE);
			}
			m_eEventMouse = GetEvent(dwKey);

			return GAME->OnMouseClick(this);
		}

		return FALSE;
	}
	void Mouse::IsNoMove(BOOL b)
	{
		m_bNoMove = b;

		if (m_bNoMove)
			m_bEndNoMove = FALSE;
	}
	void Mouse::BlockMouse()
	{
		m_iBlockedRefCount++;

		IsNoMove(TRUE);
	}
	void Mouse::UnblockMouse()
	{
		if (m_iBlockedRefCount > 0)
		{
			m_iBlockedRefCount--;

			if (m_iBlockedRefCount == 0)
				m_bEndNoMove = TRUE;
		}
	}
}