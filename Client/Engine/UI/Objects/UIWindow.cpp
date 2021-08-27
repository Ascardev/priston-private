#include "StdAfx.h"
#include "UIWindow.h"

namespace UI
{
	Window::Window(Rectangle2D rRectangle) : Element(rRectangle)
	{

	}

	Window::~Window()
	{
		//Clear();
	}

	void Window::Clear()
	{
		for (auto &p : m_vElementChild)
		{
			p->Clear();
			p.reset();
		}

		m_vElementChild.clear();

		CLEARPTR(m_pImage);

		UI::ImageLoader::DeleteImage(m_pImage);
	}
	void Window::SetBox(Rectangle2D sBox)
	{
		m_rRectViewPort = sBox;
		m_rRect = sBox;
	}
	BOOL Window::IsHover()
	{
		if (!IsOpen())
			m_bIsHover = FALSE;

		return m_bIsHover;
	}
	void Window::Update(float fTime)
	{
		if (IsOpen())
		{
			//Render Objects
			for (auto &v : m_vElementChild)
				v->Update(fTime);
		}
	}
	void Window::Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY, int iSourceWidth, int iSourceHeight)
	{
		if (IsOpen())
		{
			//Fix Source iWidth and iHeight
			if (iSourceWidth == -1)
				iSourceWidth = GetWidth();
			if (iSourceHeight == -1)
				iSourceHeight = GetHeight();

			if (iWidth <= 0 || iHeight <= 0)
				return;

			int iRenderX = GetX() + iX;
			int iRenderY = GetY() + iY;
			int iRendWidth = low(GetWidth(), iWidth);
			int iRendHeight = low(GetHeight(), iHeight);

			if (m_cColorBackground.Get() != 0)
				GRAPHICENGINE->DrawRectangle(Rectangle2D(iRenderX, iRenderY, iRendWidth, iRendHeight), m_cColorBackground.Get(), m_cColorBackground.Get());

			if (m_pImage)
				UI::ImageRender::Render(m_pImage, iRenderX, iRenderY, m_pImage->GetWidth(), m_pImage->GetHeight(), iSourceX, iSourceY, -1);

			//Rend Objects
			for (const auto &v : m_vElementChild)
			{
				if (v->IsParentChild())
				{
					if (v->GetType() == TYPE_Window)
						v->Render(iRenderX, iRenderY, iRendWidth, iRendHeight, iSourceX, iSourceY, iSourceWidth, iSourceHeight);
					else
						v->Render(iRenderX, iRenderY, iRendWidth, iRendHeight, iSourceX, iSourceY);
				}
				else
				{
					if (v->GetType() == TYPE_Window)
						v->Render(iRenderX, iRenderY, iRendWidth, iRendHeight, 0, 0, iSourceWidth, iSourceHeight);
					else
						v->Render(iRenderX, iRenderY, iRendWidth, iRendHeight, 0, 0);
				}
			}

			//Scroll
			if (m_pScroll)
				m_pScroll->Render(iRenderX, iRenderY, iRendWidth, iRendHeight, iSourceX, iSourceY);

			Element::Render(iRenderX, iRenderY, iRendWidth, iRendHeight, iSourceX, iSourceY);
		}
	}

	BOOL Window::OnMouseClick(INPUTS::LPMOUSE pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		if (!IsOpen() || IsEnjoin())
			return FALSE;

		Point2D *psPosition = pcMouse->GetPosition();

		BOOL bRet = FALSE;

		if (IsHover() && m_bFocusWindow)
			bRet = TRUE;

		int iRenderX = GetX() + iX;
		int iRenderY = GetY() + iY;
		int iRenderWidth = low(GetWidth(), iWidth);
		int iRenderHeight = low(GetHeight(), iHeight);

		Rectangle2D rBox = { iRenderX,iRenderY,iRenderWidth,iRenderHeight };
		Rectangle2D rSelBox = { iRenderX + m_rRectSelectMove.iX,iRenderY + m_rRectSelectMove.iY,m_rRectSelectMove.iWidth,m_rRectSelectMove.iHeight };

		//Event
		if (pcMouse->GetEvent() == m_eMouseEvent && rBox.Inside(psPosition))
			UI::Event::Invoke(m_iEventID);

		for (UINT u = m_vElementChild.size(); u > 0; u--)
		{
			const auto &v = m_vElementChild[u - 1];

			if (v->OnMouseClick(pcMouse, iRenderX, iRenderY, iRenderWidth, iRenderHeight, 0, 0))
			{
				bRet = TRUE;
				break;
			}
		}

		if (m_pScroll)
			bRet = m_pScroll->OnMouseClick(pcMouse, iRenderX, iRenderY, iWidth, iHeight, 0, 0);

		if (m_bCanMove)
		{
			if (m_bSelected)
			{
				if (pcMouse->GetEvent() == ClickUpL)
					m_bSelected = FALSE;
			}
			else if (rSelBox.Inside(psPosition))
			{
				if (pcMouse->GetEvent() == ClickDownL)
				{
					m_bSelected = TRUE;
					m_sPointMouse.iX = abs(pcMouse->GetPosition()->iX - GetX());
					m_sPointMouse.iY = abs(pcMouse->GetPosition()->iY - GetY());

					bRet = TRUE;
				}
			}
		}

		return bRet;
	}

	BOOL Window::OnMouseScroll(INPUTS::LPMOUSE pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		if (!IsOpen() || IsEnjoin())
			return FALSE;

		//Compute iWidth and iHeight
		iWidth -= GetX();
		iHeight -= GetY();

		int iRenderX = GetX() + iX;
		int iRenderY = GetY() + iY;
		int iRenderWidth = low(GetWidth(), iWidth);
		int iRenderHeight = low(GetHeight(), iHeight);

		for (UINT u = m_vElementChild.size(); u > 0; u--)
		{
			const auto &v = m_vElementChild[u - 1];

			if (v->OnMouseScroll(pcMouse, iRenderX + iSourceX, iRenderY + iSourceY, iRenderWidth - iSourceX, iRenderHeight - iSourceY, iSourceX, iSourceY))
				return TRUE;
		}

		return FALSE;
	}

	void Window::OnMouseMove(INPUTS::LPMOUSE pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		if (!IsOpen() || IsEnjoin())
			return;

		//Compute iWidth and iHeight
		iWidth -= GetX();
		iHeight -= GetY();

		int iRenderX = GetX() + iX;
		int iRenderY = GetY() + iY;
		int iRenderWidth = low(GetWidth(), iWidth);
		int iRenderHeight = low(GetHeight(), iHeight);

		BOOL bOldHover = m_bIsHover;

		if (Rectangle2D(iRenderX, iRenderY, iRenderWidth, iRenderHeight).Inside(pcMouse->GetPosition()))
			m_bIsHover = TRUE;
		else
			m_bIsHover = FALSE;

		for (UINT u = m_vElementChild.size(); u > 0; u--)
		{
			const auto &v = m_vElementChild[u - 1];

			if (v->IsParentChild())
				v->OnMouseMove(pcMouse, iRenderX + iSourceX, iRenderY + iSourceY, iRenderWidth - iSourceX, iRenderHeight - iSourceY, iSourceX, iSourceY);
			else
				v->OnMouseMove(pcMouse, iRenderX, iRenderY, iWidth, iHeight, 0, 0);
		}

		if (m_pScroll)
			m_pScroll->OnMouseMove(pcMouse, iRenderX, iRenderY, iWidth, iHeight, 0, 0);

		if (m_bSelected)
		{
			int iX = pcMouse->GetPosition()->iX - m_sPointMouse.iX;
			int iY = pcMouse->GetPosition()->iY - m_sPointMouse.iY;

			SetPosition(iX < 0 ? 0 : iX, iY < 0 ? 0 : iY);
		}

		if (m_bIsHover != bOldHover && (m_iHoverEventID != -1))
			UI::Event::Invoke(m_iHoverEventID);
	}

	BOOL Window::OnKeyChar(INPUTS::LPKEYBOARD pcKeyboard)
	{
		if (!IsOpen() || IsEnjoin())
			return FALSE;

		for (UINT u = m_vElementChild.size(); u > 0; u--)
		{
			const auto &v = m_vElementChild[u - 1];

			if (v->OnKeyChar(pcKeyboard))
				return TRUE;
		}

		return FALSE;
	}
	
	BOOL Window::OnKeyPress(INPUTS::LPKEYBOARD pcKeyboard)
	{
		if (!IsOpen() || IsEnjoin())
			return FALSE;

		BOOL bRet = FALSE;

		for (UINT u = m_vElementChild.size(); u > 0; u--)
		{
			const auto &v = m_vElementChild[u - 1];

			if (v->OnKeyPress(pcKeyboard))
				bRet = TRUE;
		}

		return bRet;
	}

	void Window::AddElement(LPELEMENT pElement)
	{
		m_vElementChild.push_back(pElement);
	}
	
	BOOL Window::DelElement(LPELEMENT pElement)
	{
		for (std::vector<LPELEMENT>::iterator it = m_vElementChild.begin(); it != m_vElementChild.end();)
		{
			LPELEMENT p = *it;

			if (p == pElement)
			{
				p->Clear();
				p.reset();
				it = m_vElementChild.erase(it);
				return TRUE;
			}
			else
				it++;
		}

		return FALSE;
	}
}