#include "StdAfx.h"
#include "UIList.h"

namespace UI
{
	List::List()
	{

	}
	List::List(Rectangle2D rRectangle) : Element(rRectangle)
	{

	}
	List::~List()
	{
		//Clear();
	}
	void List::Clear()
	{
		for (auto &v : m_vpWindows)
		{
			CLEARPTR(v);
			RESETPTR(v);
		}

		m_vpWindows.clear();

		if (m_pScrollBar)
			m_pScrollBar->SetPercent(0);
	}
	LPSCROLL List::MakeScrollBar(Rectangle2D sBox, std::string strScrollBarPath, std::string strScrollerPath)
	{
		m_pScrollBar = std::make_shared<Scroll>(sBox);
		m_pScrollBar->SetVertical(TRUE);
		m_pScrollBar->SetImage(UI::ImageLoader::LoadImage_(strScrollBarPath.c_str()));
		m_pScrollBar->SetScroller(UI::ImageLoader::LoadImage_(strScrollerPath.c_str()), 8, 11);

		m_bForceDown ? m_pScrollBar->SetMinMax(100, 0) : m_pScrollBar->SetMinMax(0, 100);

		return m_pScrollBar;
	}
	int List::GetListWidth()
	{
		int iReturn = 0;
		int iLastWidth = 0;

		for (size_t i = 0; i < m_vpWindows.size(); i++)
		{
			LPWINDOW pWindow = m_vpWindows[i];

			if (pWindow->IsOpen() || m_bCountAxisHidden)
			{
				//Add Element iWidth
				int iWidth = pWindow->GetWidth() + (i == 0 ? 0 : m_iPaddingSeparator);

				if (m_bNoupdatePosition)
				{
					if (iWidth > iLastWidth)
						iReturn = iWidth;
				}
				else
					iReturn += iWidth;
			}
		}

		return iReturn;
	}
	int List::GetListHeight()
	{
		int iReturn = 0;
		int iLastHeight = 0;

		for (size_t i = 0; i < m_vpWindows.size(); i++)
		{
			LPWINDOW pWindow = m_vpWindows[i];

			if (pWindow->IsOpen() || m_bCountAxisHidden)
			{
				//Add Element iHeight
				int iHeight = pWindow->GetHeight() + (i == 0 ? 0 : m_iPaddingSeparator);

				if (m_bNoupdatePosition)
				{
					if (iHeight > iLastHeight)
						iReturn = iHeight;
				}
				else
					iReturn += iHeight;
			}
		}

		return iReturn;
	}
	void List::SetForceDown(BOOL b)
	{
		m_bForceDown = b;

		if (m_bForceDown)
		{
			if (m_pScrollBar)
				m_pScrollBar->SetPercent(100);
		}
	}
	void List::AddWindow(LPWINDOW pWindow)
	{
		if (pWindow)
		{
			pWindow->SetPosition(pWindow->GetX(), pWindow->GetY());
			m_vpWindows.push_back(pWindow);
		}
	}
	LPWINDOW List::GetWindow(int iIDObject)
	{
		for (auto &v : m_vpWindows)
		{
			if (v->GetID() == iIDObject)
				return v;
		}

		return NULL;
	}
	void List::AddAxis(int iX, int iY)
	{
		m_iAddAxisX += iX;
		m_iAddAxisY += iY;
	}
	void List::SetAxis(int iX, int iY)
	{
		m_iAddAxisX = iX;
		m_iAddAxisY = iY;
	}
	void List::Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		if (!IsOpen())
			return;

		int iRenderX = GetX() + iX;
		int iRenderY = GetY() + iY;
		int iRenderWidth = low(GetWidth(), iWidth);
		int iRenderHeight = low(GetHeight(), iHeight);

		BOOL bIsForceDown = IsForceDown();

		m_iScroll = 0;

		if (m_pScrollBar)
			m_iScroll = ((GetListHeight() - GetHeight()) * (bIsForceDown ? m_pScrollBar->GetPercent() - 100 : m_pScrollBar->GetPercent())) / 100;

		if (GetListHeight() < GetHeight())
			m_iScroll = 0;

		if (m_cColorBackground.Get())
			GRAPHICENGINE->DrawRectangle(Rectangle2D(iRenderX, iRenderX, iRenderWidth, iRenderHeight), m_cColorBackground.Get(), m_cColorBackground.Get());

		RECT r = { GetX() + iX,GetY() + iY,GetWidth() + iX + GetX(),GetHeight() + iY + GetY() };

		if (!m_bNoClip)
			GRAPHICDEVICE->PushScissorRect(r);

		int iAddExtra = 0;
		for (size_t u = 0; u < m_vpWindows.size(); u++)
		{
			auto v = m_vpWindows[bIsForceDown ? m_vpWindows.size() - 1 - u : u];

			int iWindowWidth = v->GetWidth();
			int iWindowHeight = v->GetHeight();

			if (m_bNoupdatePosition)
				iAddExtra = 0;

			Rectangle2D rBox(GetX() + iX, GetY() + iY, GetWidth(), GetHeight());
			Rectangle2D rBoxWindow(GetX() + iX + m_iAddAxisX + (m_bHorizontalPadding ? iAddExtra : 0), GetY() + iY + m_iAddAxisY - m_iScroll + (!m_bHorizontalPadding ? iAddExtra : 0) + (bIsForceDown ? iRenderHeight - iWindowHeight : 0), iWindowWidth, iWindowHeight);

			if (rBox.Overlaps(&rBoxWindow))
				v->Render(rBoxWindow.iX, rBoxWindow.iY, rBoxWindow.iWidth, rBoxWindow.iHeight, iSourceX, iSourceY);

			if (m_bHorizontalPadding)
			{
				if (bIsForceDown)
					iAddExtra -= v->GetWidth() + m_iPaddingSeparator;
				else
					iAddExtra += v->GetWidth() + m_iPaddingSeparator;
			}
			else
			{
				if (bIsForceDown)
					iAddExtra -= v->GetHeight() + m_iPaddingSeparator;
				else
					iAddExtra -= v->GetHeight() + m_iPaddingSeparator;
			}
		}

		if (!m_bNoClip)
			GRAPHICDEVICE->PopScissorRect();

		if (m_pScrollBar && GetListHeight() > GetHeight())
			m_pScrollBar->Render(GetX() + iX, GetY() + iY, m_pScrollBar->GetBox().iWidth, m_pScrollBar->GetBox().iHeight, 0, 0);
	}
	void List::Update(float fTime)
	{
		for (size_t u = 0; u < m_vpWindows.size(); u++)
		{
			auto v = m_vpWindows[u];

			if (v) v->Update(fTime);
		}
	}
	BOOL List::OnMouseClick(INPUTS::LPMOUSE pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		BOOL bRet = FALSE;

		if (!IsOpen() || IsEnjoin())
			return FALSE;

		int iRenderX = GetX() + iX;
		int iRenderY = GetY() + iY;
		int iRenderWidth = low(GetWidth(), iWidth);
		int iRenderHeight = low(GetHeight(), iHeight);

		BOOL bIsForceDown = IsForceDown();

		m_iScroll = 0;

		if (m_pScrollBar)
			m_iScroll = ((GetListHeight() - GetHeight()) * (bIsForceDown ? m_pScrollBar->GetPercent() - 100 : m_pScrollBar->GetPercent())) / 100;

		if (GetListHeight() < GetHeight())
			m_iScroll = 0;

		if (m_pScrollBar)
			m_pScrollBar->OnMouseClick(pcMouse, GetX() + iX, GetY() + iY, iWidth, iHeight, iSourceX, iSourceY);

		int iAddExtra = 0;
		Rectangle2D rBox = { GetX() + iX, GetY() + iY, GetWidth(), GetHeight() };

		if (rBox.Inside(pcMouse->GetPosition()))
		{
			for (auto &v : m_vpWindows)
			{
				if (m_bNoupdatePosition)
				{
					bRet = v->OnMouseClick(pcMouse, iRenderX, iRenderY - m_iScroll, iRenderWidth, iRenderHeight + m_iScroll, 0, 0);
					continue;
				}

				Rectangle2D rBoxWindow(GetX() + iX + m_iAddAxisX + (m_bHorizontalPadding ? iAddExtra : 0), GetY() + iY + m_iAddAxisY - m_iScroll + (!m_bHorizontalPadding ? iAddExtra : 0) + (bIsForceDown ? GetHeight() - v->GetHeight() : 0), v->GetWidth(), v->GetHeight());

				if (rBoxWindow.Inside(pcMouse->GetPosition()))
				{
					for (auto &p : m_vpWindows)
					{
						p->OnMouseClick(pcMouse, 0, 0, 0, 0, iSourceX, iSourceY);
					}

					bRet = v->OnMouseClick(pcMouse, rBoxWindow.iX, rBoxWindow.iY, rBoxWindow.iWidth, rBoxWindow.iHeight, iSourceX, iSourceY);
					break;
				}

				if (m_bHorizontalPadding)
				{
					if (bIsForceDown)
						iAddExtra -= v->GetWidth() + m_iPaddingSeparator;
					else
						iAddExtra += v->GetWidth() + m_iPaddingSeparator;
				}
				else
				{
					if (bIsForceDown)
						iAddExtra -= v->GetHeight() + m_iPaddingSeparator;
					else
						iAddExtra -= v->GetHeight() + m_iPaddingSeparator;
				}
			}
		}
		else
		{
			for (auto &v : m_vpWindows)
				bRet = v->OnMouseClick(pcMouse, 0, 0, 0, 0, iSourceX, iSourceY);
		}

		return bRet;
	}
	BOOL List::OnMouseScroll(INPUTS::LPMOUSE pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		if (!IsOpen() || IsEnjoin())
			return FALSE;

		Rectangle2D rBox = { GetX() + iX,GetY() + iY,GetWidth(),GetHeight() };
		if (m_pScrollBar && rBox.Inside(pcMouse->GetPosition()) && m_bScrollFirst)
			return m_pScrollBar->OnMouseScroll(pcMouse, GetX() + iX, GetY() + iY, iWidth, iHeight, iSourceX, iSourceY);

		if (rBox.Inside(pcMouse->GetPosition()))
		{
			for (size_t u = m_vpWindows.size(); u > 0; u--)
			{
				const auto &v = m_vpWindows[u - 1];
				if (v->OnMouseScroll(pcMouse, GetX() + iX, GetY() + iY - m_iScroll, GetWidth(), GetListHeight(), iSourceX, iSourceY))
					return TRUE;
			}
		}

		if (m_pScrollBar && rBox.Inside(pcMouse->GetPosition()) && !m_bScrollFirst)
			return m_pScrollBar->OnMouseScroll(pcMouse, GetX() + iX, GetY() + iY, iWidth, iHeight, iSourceX, iSourceY);

		return FALSE;
	}
	void List::OnMouseMove(INPUTS::LPMOUSE pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		if (!IsOpen() || IsEnjoin())
			return;

		int iRenderX = GetX() + iX;
		int iRenderY = GetY() + iY;
		int iRenderWidth = low(GetWidth(), iWidth);
		int iRenderHeight = low(GetHeight(), iHeight);

		BOOL bIsForceDown = IsForceDown();

		m_iScroll = 0;

		if (m_pScrollBar)
			m_iScroll = ((GetListHeight() - GetHeight()) * (bIsForceDown ? m_pScrollBar->GetPercent() - 100 : m_pScrollBar->GetPercent())) / 100;

		if (GetListHeight() < GetHeight())
			m_iScroll = 0;

		if (m_pScrollBar)
			m_pScrollBar->OnMouseMove(pcMouse, GetX() + iX, GetY() + iY, iWidth, iHeight, iSourceX, iSourceY);

		int iAddExtra = 0;
		Rectangle2D rBox = { GetX() + iX,GetY() + iY,GetWidth(),GetHeight() };
		if (rBox.Inside(pcMouse->GetPosition()))
		{
			for (size_t u = 0; u < m_vpWindows.size(); u++)
			{
				auto v = m_vpWindows[bIsForceDown ? m_vpWindows.size() - 1 - u : u];

				int iWindowWidth = v->GetWidth();
				int iWindowHeight = v->GetHeight();

				if (m_bNoupdatePosition)
				{
					v->OnMouseMove(pcMouse, iRenderX, iRenderY - m_iScroll, iRenderWidth, iRenderHeight + m_iScroll, 0, 0);
					continue;
				}

				Rectangle2D rBoxWindow(GetX() + iX + m_iAddAxisX + (m_bHorizontalPadding ? iAddExtra : 0), GetY() + iY + m_iAddAxisY - m_iScroll + (!m_bHorizontalPadding ? iAddExtra : 0) + (bIsForceDown ? GetHeight() - v->GetHeight() : 0), v->GetWidth(), v->GetHeight());
				if (rBoxWindow.Inside(pcMouse->GetPosition()))
				{
					for (auto &p : m_vpWindows)
						p->OnMouseMove(pcMouse, 0, 0, 0, 0, iSourceX, iSourceY);

					v->OnMouseMove(pcMouse, rBoxWindow.iX, rBoxWindow.iY, rBoxWindow.iWidth, rBoxWindow.iHeight, iSourceX, iSourceY);
					break;
				}

				if (m_bHorizontalPadding)
				{
					if (bIsForceDown)
						iAddExtra -= v->GetWidth() + m_iPaddingSeparator;
					else
						iAddExtra += v->GetWidth() + m_iPaddingSeparator;
				}
				else
				{
					if (bIsForceDown)
						iAddExtra -= v->GetHeight() + m_iPaddingSeparator;
					else
						iAddExtra -= v->GetHeight() + m_iPaddingSeparator;
				}
			}
		}
		else
		{
			for (auto &v : m_vpWindows)
				v->OnMouseMove(pcMouse, 0, 0, 0, 0, iSourceX, iSourceY);
		}
	}
	BOOL List::OnKeyChar(INPUTS::LPKEYBOARD pcKeyboard)
	{
		if (!IsOpen() || IsEnjoin())
			return FALSE;

		for (size_t u = m_vpWindows.size(); u > 0; u--)
		{
			auto v = m_vpWindows[u - 1];

			if (v->OnKeyChar(pcKeyboard))
				return TRUE;
		}

		return FALSE;
	}
	BOOL List::OnKeyPress(INPUTS::LPKEYBOARD pcKeyboard)
	{
		if (!IsOpen() || IsEnjoin())
			return FALSE;

		for (size_t u = m_vpWindows.size(); u > 0; u--)
		{
			auto v = m_vpWindows[u - 1];

			if (v->OnKeyPress(pcKeyboard))
				return TRUE;
		}

		return FALSE;
	}
}