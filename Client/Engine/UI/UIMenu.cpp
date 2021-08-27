#include "StdAfx.h"
#include "UIMenu.h"

namespace UI
{
	Menu::Menu()
	{

	}
	Menu::Menu(Rectangle2D sBox) : Element(sBox)
	{
		m_bShow = FALSE;
	}
	Menu::~Menu()
	{
		//Clear();
	}
	void Menu::Open()
	{
		m_bAnimate = TRUE;
		m_bOpen = TRUE;
		m_bClose = FALSE;
		m_fProgress = 0.0f;
		m_bShow = TRUE;

		if (m_pGroup)
			m_pGroup->SetIndexObject(GetID());

		if (m_ePosition == EMENUPOSITION_Left)
			m_sAniatebox = Point2D(-GetWidth(),0);
	}
	void Menu::Close()
	{
		m_bAnimate = TRUE;
		m_bOpen = FALSE;
		m_bClose = TRUE;
		m_fProgress = 1.0f;
	}
	void Menu::Clear()
	{
		for (size_t i = 0; i < m_vOptions.size(); i ++)
		{
			m_vOptions[i].pText->Clear();
			m_vOptions[i].pText.reset();
		}

		m_vOptions.clear();
		m_iHeightMenu = 0;

		CLEARPTR(m_pImageTop);
		CLEARPTR(m_pImageMiddle);
		CLEARPTR(m_pImageBottom);
		CLEARPTR(m_pImageMain);

		UI::ImageLoader::DeleteImage(m_pImageTop);
		UI::ImageLoader::DeleteImage(m_pImageMiddle);
		UI::ImageLoader::DeleteImage(m_pImageBottom);
		UI::ImageLoader::DeleteImage(m_pImageMain);
	}

	void Menu::SetBackground(std::string strImageTop,std::string strImageMiddle,std::string strImageBottom,std::string strImageMain)
	{
		m_pImageTop = UI::ImageLoader::LoadImage_(strImageTop.c_str());
		m_pImageMiddle = UI::ImageLoader::LoadImage_(strImageMiddle.c_str());
		m_pImageBottom = UI::ImageLoader::LoadImage_(strImageBottom.c_str());
		m_pImageMain = UI::ImageLoader::LoadImage_(strImageMain.c_str());
	}
	LPTEXT Menu::MakeOption(const std::string &strText,const Rectangle2D &rBox,BOOL bBold,const DWORD dwColor,const DWORD dwHoverColor)
	{
		LPTEXT pText = std::make_shared<Text>(strText,rBox,bBold,dwColor);

		pText->SetNoClip(TRUE);
		pText->SetColorHover(dwHoverColor);
		pText->SetSelectType(TRUE);

		return pText;
	}
	void Menu::AddOption(LPTEXT p,BOOL bChild)
	{
		p->SetBox(Rectangle2D(p->GetX(),p->GetY() + m_iHeightMenu,p->GetWidth(),p->GetHeight()));
		p->SetID(m_vOptions.size() + 1);
		p->SetHorizontalAlign(ALIGN_Center);
		p->SetVerticalAlign(ALIGN_Middle);

		OPTION sOption;

		sOption.bChild = bChild;
		sOption.pText = p;

		m_vOptions.push_back(sOption);

		m_iHeightMenu += p->GetHeight();
	}

	void Menu::AddOption(LPTEXT p,BOOL bChild,int iID)
	{
		p->SetBox(Rectangle2D(p->GetX(),p->GetY() + m_iHeightMenu,p->GetWidth(),p->GetHeight()));
		p->SetID(iID);
		p->SetHorizontalAlign(ALIGN_Center);
		p->SetVerticalAlign(ALIGN_Middle);

		OPTION sOption;

		sOption.bChild = bChild;
		sOption.pText = p;

		m_vOptions.push_back(sOption);

		m_iHeightMenu += p->GetHeight();
	}

	void Menu::RemoveOption(int iID)
	{
		for (size_t i = 0; i < m_vOptions.size(); i ++)
		{
			if (m_vOptions[i].pText->GetID() == iID)
			{
				m_iHeightMenu -= m_vOptions[i].pText->GetHeight();
				m_vOptions[i].pText->Clear();
				m_vOptions[i].pText.reset();

				m_vOptions.erase(m_vOptions.begin() + i);
				break;
			}
		}
	}
	void Menu::Animate()
	{
		if (m_bAnimate)
		{
			if (m_bOpen)
			{
				if (m_ePosition == EMENUPOSITION_Left)
					m_sAniatebox.iX += 5;

				if (m_sAniatebox.iX > 0 || m_sAniatebox.iY > 0)
				{
					m_bAnimate = FALSE;
					m_bOpen = TRUE;
					m_bClose = FALSE;
				}

				m_fProgress += 0.05f;

				if (m_fProgress > 1.0f)
					m_fProgress = 1.0f;
			}
			else if (m_bClose)
			{
				if (m_ePosition == EMENUPOSITION_Left)
					m_sAniatebox.iX -= 5;

				if (m_sAniatebox.iX < -GetWidth())
				{
					m_bAnimate = FALSE;
					m_bOpen = FALSE;
					m_bClose = FALSE;
					m_bShow = FALSE;
				}

				m_fProgress -= 0.05f;

				if (m_fProgress < 0.0f)
					m_fProgress = 0.0f;
			}
		}
	}
	void Menu::Render(int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY)
	{
		int iRenderX = GetX() + iX;
		int iRenderY = GetY() + iY;
		int iRenderWidth = low(GetWidth(),iWidth);
		int iRenderHeight = low(GetHeight(),iHeight);

		if (m_pImageTop && m_pImageMiddle && m_pImageBottom && m_pImageMain && IsOpen() && m_vOptions.size() > 0)
		{
			Animate();

			if (m_vOptions.size() == 1)
				UI::ImageRender::Render(m_pImageMain,iRenderX + m_sAniatebox.iX,iRenderY + m_sAniatebox.iY,m_pImageMain->GetWidth(),m_pImageMain->GetHeight(),iSourceX,iSourceY,D3DCOLOR_ARGB((int)(float)(m_fProgress * 255),255,255,255));
			else
			{
				UI::ImageRender::Render(m_pImageTop,iRenderX + m_sAniatebox.iX,iRenderY + m_sAniatebox.iY,iRenderWidth,iRenderHeight,iSourceX,iSourceY,D3DCOLOR_ARGB((int)(float)(m_fProgress * 255),255,255,255));
				UI::ImageRender::Render(m_pImageMiddle,iRenderX + m_sAniatebox.iX,iRenderY + m_sAniatebox.iY + iRenderHeight,iRenderWidth,m_iHeightMenu - iRenderHeight + m_vOptions[0].pText->GetY() + 7 - m_pImageBottom->GetHeight(),iSourceX,iSourceY,D3DCOLOR_ARGB((int)(float)(m_fProgress * 255),255,255,255));
				UI::ImageRender::Render(m_pImageBottom,iRenderX + m_sAniatebox.iX,iRenderY + m_sAniatebox.iY + m_iHeightMenu - iRenderHeight + m_vOptions[0].pText->GetY() + 7,iRenderWidth,iRenderHeight,iSourceX,iSourceY,D3DCOLOR_ARGB((int)(float)(m_fProgress * 255),255,255,255));
			}

			for (auto &v : m_vOptions)
			{
				D3DXCOLOR c = v.pText->GetColor();

				c.a = m_fProgress;

				v.pText->SetColor(c);
				v.pText->Render(iRenderX + m_sAniatebox.iX, iRenderY + m_sAniatebox.iY, iWidth, iHeight, iSourceX, iSourceY);
			}
		}
	}

	void Menu::Update(float fTime)
	{
		if (m_bShow && m_bOpen && !m_bClose && !m_bAnimate)
		{
			if (m_pGroup)
			{
				if (m_pGroup->GetIndexObject() != GetID())
					Close();
			}
		}
	}
	BOOL Menu::OnMouseClick(class INPUTS::Mouse *pcMouse,int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY)
	{
		if (!IsOpen() || IsLinkObject())
			return FALSE;

		EMouseEvent eEvent = pcMouse->GetEvent();

		if (eEvent != ClickDownL && eEvent != ClickDownR)
			return FALSE;

		int iRenderX = GetX() + iX;
		int iRenderY = GetY() + iY;
		int iRenderWidth = low(GetWidth(),iWidth);
		int iRenderHeight = low(GetHeight(),iHeight);

		for (std::vector<OPTION>::iterator it = m_vOptions.begin(); it != m_vOptions.end(); it ++)
		{
			auto v = *it;

			if (v.pText->OnMouseClick(pcMouse,iRenderX,iRenderY,iWidth,iHeight,iSourceX,iSourceY))
			{
				SetOptionID(v.pText->GetID());
				UI::Event::Invoke(m_iEventID);
				SetOptionID(-1);

				if (m_iEventID)
					Close();

				return TRUE;
			}
		}

		if (m_bShow && m_bOpen && !m_bClose && m_bAnimate)
		{
			Close();
			return TRUE;
		}

		return FALSE;
	}
	void Menu::OnMouseMove(class INPUTS::Mouse *pcMouse,int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY)
	{
		if (!IsOpen() || IsLinkObject())
			return;

		int iRenderX = GetX() + iX;
		int iRenderY = GetY() + iY;
		int iRenderWidth = low(GetWidth(),iWidth);
		int iRenderHeight = low(GetHeight(),iHeight);

		for (std::vector<OPTION>::iterator it = m_vOptions.begin(); it != m_vOptions.end(); it ++)
		{
			auto v = *it;

			v.pText->OnMouseMove(pcMouse,iRenderX,iRenderY,iWidth,iHeight,iSourceX,iSourceY);
		}
	}
}