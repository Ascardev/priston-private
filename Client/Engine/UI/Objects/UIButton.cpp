#include "StdAfx.h"
#include "UIButton.h"

namespace UI
{
	Button::Button(Rectangle2D rRectangle) : Element(rRectangle)
	{

	}
	Button::~Button()
	{
		//Clear();
	}
	void Button::Clear()
	{
		CLEARPTR(m_pImage);
		CLEARPTR(m_pImageActive);
		CLEARPTR(m_pImageDisable);
		CLEARPTR(m_pImageAnimate);

		UI::ImageLoader::DeleteImage(m_pImage);
		UI::ImageLoader::DeleteImage(m_pImageActive);
		UI::ImageLoader::DeleteImage(m_pImageDisable);
		UI::ImageLoader::DeleteImage(m_pImageAnimate);
	}

	void Button::SetActiveImage(std::pair<class Image *,class Image *> pPair)
	{
		m_pImage = pPair.first;
		m_pImageActive = pPair.second;
	}
	void Button::Animate()
	{
		if (m_bAnimate)
		{
			if (m_pImageAnimate)
			{
				m_fProgress -= 0.03f;
				m_sAnimateBox += Rectangle2D(-1, -1, 2, 2);

				m_fProgress = m_fProgress <= 0.0f ? 0.0f : m_fProgress;
			}
			else
			{
				if (!m_bAnimateFade)
				{
					m_fProgress -= 0.03f;

					if (m_fProgress < 0.0f)
					{
						m_fProgress = 0.0f;
						m_bAnimateFade = TRUE;
					}
				}
				else
				{
					m_fProgress += 0.03f;

					if (m_fProgress > 1.0f)
					{
						m_fProgress = 1.0f;
						m_bAnimateFade = FALSE;
					}
				}
			}		
		}
	}
	void Button::Render(int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY)
	{
		if (IsOpen())
		{
			if (iWidth - GetX() <= 0)
				return;

			if (iHeight - GetY() <= 0)
				return;

			int iRenderX = GetX() + iX;
			int iRenderY = GetY() + iY;
			int iRenderWidth = low(GetWidth(),iWidth - GetX());
			int iRenderHeight = low(GetHeight(),iHeight - GetY());

			if (m_bDisable)
			{
				UI::ImageRender::Render(m_pImageDisable, iRenderX, iRenderY, iRenderWidth, iRenderHeight, iSourceX, iSourceY, -1);
				m_bHover = FALSE;
				m_bSelect = FALSE;
				return;
			}
			if (m_bCanHold && m_bHolding)
				UI::Event::Invoke(m_iEvent_ClickID);

			if (m_bHover || m_bSelect)
			{
				if (m_pGroup)
				{
					if (m_pGroup->GetIndexObject() != GetID())
						m_bSelect = FALSE;
				}

				if (m_pImageAnimate && m_bAnimate)
				{
					int iAnimateRenderX = iRenderX + ((GetWidth() >> 1) - (m_pImageAnimate->GetWidth() >> 1));
					int iAnimateRenderY = iRenderY + ((GetHeight() >> 1) - (m_pImageAnimate->GetHeight() >> 1));
					int iAnimateRenderWidth = m_pImageAnimate->GetWidth();
					int iAnimateRenderHeight = m_pImageAnimate->GetHeight();

					//Init Animate ?
					if (m_fProgress == 1.0f)
						m_sAnimateBox = Rectangle2D(iAnimateRenderX, iAnimateRenderY, iAnimateRenderWidth, iAnimateRenderHeight);

					if (m_fProgress == 0.0f)
					{
						m_sAnimateBox = Rectangle2D(iAnimateRenderX, iAnimateRenderY, iAnimateRenderWidth, iAnimateRenderHeight);
						m_fProgress = 1.0f;
					}

					Animate();

					UI::ImageRender::Render(m_pImageAnimate, m_sAnimateBox.iX, m_sAnimateBox.iY, m_sAnimateBox.iWidth, m_sAnimateBox.iHeight, D3DCOLOR_ARGB((int)(float)(m_fProgress * 255), 255, 255, 255));

					UI::ImageRender::Render(m_pImageActive, iRenderX, iRenderY, iRenderWidth, iRenderHeight, iSourceX, iSourceY, -1);
				}
				else
				{
					Animate();

					UI::ImageRender::Render(m_pImageActive, iRenderX, iRenderY, iRenderWidth, iRenderHeight, iSourceX, iSourceY, m_bAnimate ? D3DCOLOR_ARGB((int)(float)(m_fProgress * 255), 255, 255, 255) : -1);
				}
			}
			else
				UI::ImageRender::Render(m_pImage, iRenderX, iRenderY, iRenderWidth, iRenderHeight, iSourceX, iSourceY, -1);

			Element::Render(iRenderX, iRenderY, iRenderWidth, iRenderHeight, iSourceX, iSourceY);
		}
	}

	BOOL Button::OnMouseClick(INPUTS::LPMOUSE pcMouse,int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY)
	{
		if (!IsOpen() || m_bDisable || IsEnjoin())
			return FALSE;

		Point2D *psPosition = pcMouse->GetPosition();

		int iRenderX = GetX() + iX + iSourceX;
		int iRenderY = GetY() + iY + iSourceY;
		int iRenderWidth = low(GetWidth(),iWidth);
		int iRenderHeight = low(GetHeight(),iHeight);

		if (m_bCanHold && m_bHolding && (pcMouse->GetEvent() == ClickDownL || pcMouse->GetEvent() == ClickDownR))
			m_bHolding = FALSE;

		//Inside X
		if ((psPosition->iX >= iRenderX) && (psPosition->iX <= (iRenderX + iRenderWidth - iSourceX)))
		{
			//Inside Y
			if ((psPosition->iY >= iRenderY) && (psPosition->iY <= (iRenderY + iRenderHeight - iSourceY)))
			{
				//Menu
				if (m_pMenu && !m_pMenu->IsOpen() && m_pMenu->GetMouseEvent() == pcMouse->GetEvent())
				{
					m_pMenu->Open();
					return TRUE;
				}
				else if (m_pMenu && m_pMenu->IsOpen() && m_pMenu->GetMouseEvent() == pcMouse->GetEvent())
				{
					m_pMenu->Close();
					return TRUE;
				}

				if (m_bSelectType)
				{
					if (m_pGroup)
					{
						if (!m_bSelect)
							m_pGroup->SetIndexObject(GetID());

						m_bSelect = TRUE;
					}
					else
						m_bSelect = m_bSelect ? FALSE : TRUE;
				}

				if (m_iEvent_ClickID && m_eMouseEvent == pcMouse->GetEvent() || m_bHolding)
				{
					if (m_bCanHold)
						m_bHolding = TRUE;

					UI::Event::Invoke(m_iEvent_ClickID);
					return TRUE;
				}
			}
		}

		return FALSE;
	}

	void Button::OnMouseMove(INPUTS::LPMOUSE pcMouse,int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY)
	{
		if (!IsOpen() || m_bDisable || IsEnjoin())
			return;

		Point2D *psPosition = pcMouse->GetPosition();

		int iRenderX = GetX() + iX + iSourceX;
		int iRenderY = GetY() + iY + iSourceY;
		int iRenderWidth = low(GetWidth(),iWidth);
		int iRenderHeight = low(GetHeight(),iHeight);

		// Inside X and Inside Y
		if (((psPosition->iX >= iRenderX) && (psPosition->iX <= (iRenderX + iRenderWidth - iSourceX))) &&
			((psPosition->iY >= iRenderY) && (psPosition->iY <= (iRenderY + iRenderHeight - iSourceY))))
		{
			if (!m_bHover)
			{
				m_bHover = TRUE;

				if (m_bAnimate)
					m_fProgress = 1.0f;

				if (m_iEvent_MoveInID)
					UI::Event::Invoke(m_iEvent_MoveInID);
			}
		}
		else
		{
			if (m_bHover)
			{
				m_bHover = FALSE;

				if (m_iEvent_MoveOutID)
					UI::Event::Invoke(m_iEvent_MoveOutID);
			}
		}
	}
}