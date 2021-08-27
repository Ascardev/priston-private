#include "StdAfx.h"
#include "MapWarp.h"

namespace MAP
{
	/*Warp::Warp()
	{

	}
	Warp::~Warp()
	{

	}
	void Warp::Init()
	{
		SetWarpPostion(Point2D(50, 45));
		BuildWindow();
		m_pcImage = UI::ImageLoader::LoadImage_("Resources\\UI\\Warp\\WG_map.tga");
		m_pcIcon = UI::ImageLoader::LoadImage_("Resources\\UI\\Warp\\WG_icon.tga");
		m_pcSelect = UI::ImageLoader::LoadImage_("Resources\\UI\\Warp\\WG_slt.tga");
	}
	void Warp::Shutdown()
	{
		m_pcWindow->Clear();

		CLEARPTR(m_pcImage);
		CLEARPTR(m_pcIcon);
		CLEARPTR(m_pcSelect);

		UI::ImageLoader::DeleteImage(m_pcImage);
		UI::ImageLoader::DeleteImage(m_pcIcon);
		UI::ImageLoader::DeleteImage(m_pcSelect);
	}
	void Warp::BuildWindow()
	{
		auto sPosition = GetWarpPosition();

		m_pcWindow = std::make_shared<UI::Window>(Rectangle2D(sPosition.iX, sPosition.iY, 320, 374));
		m_pcWindow->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Window\\Window2.png"));

		UI::LPTEXTWINDOW pTextWindow = std::make_shared<UI::TextWindow>(Rectangle2D(26, 30, 280, 304));
		pTextWindow->SetFont("Tahoma", 15, 0, FALSE, FALSE, -1);
		pTextWindow->SetID(TEXTWINDOWID);
		m_pcWindow->AddElement(pTextWindow);

		UI::LPIMAGEBOX pHeaderBG = std::make_shared<UI::ImageBox>(Rectangle2D((m_pcWindow->GetWidth() >> 1) - (181 >> 1), -13, 181, 32));
		pHeaderBG->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\window\\text\\header.png"));
		m_pcWindow->AddElement(pHeaderBG);

		//Header Title
		UI::LPIMAGEBOX pHeaderTitle = std::make_shared<UI::ImageBox>(Rectangle2D((m_pcWindow->GetWidth() >> 1) - (47 >> 1), -4, 47, 16));
		pHeaderTitle->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\window\\text\\header_teleport.png"));
		m_pcWindow->AddElement(pHeaderTitle);

		m_pcClose = std::make_shared<UI::Button>(Rectangle2D(sPosition.iX + 670, sPosition.iY - 30, 32, 47));
		m_pcClose->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Settings\\btnclose.png"));
		m_pcClose->SetActiveImage(UI::ImageLoader::LoadActiveImage("Resources\\UI\\Settings\\btnclose.png", "Resources\\UI\\Settings\\btnclose_.png"));
		m_pcClose->SetEvent(UI::Event::Build(std::bind(&Warp::OnClickClose, this, std::placeholders::_1)));

		m_pcClose->Hide();

		m_pcWindow->Hide();
	}
	void Warp::OnClickClose(UIEventArgs e)
	{
		Close();
	}
	void Warp::OnTeleport()
	{
		if (m_bActive)
		{
			if (!MESSAGEBOX->GetType())
			{
				m_bHover = FALSE;
				m_sPosition = MapWarpPosition();
			}
			else
			{
				Close();
			}
		}
	}
	void Warp::Open()
	{
		DWORD dwMask = 1;

		(cInvenTory.GetItem(sinQW1 | sin01)) ? dwMask = 1 | 2 : 0;
		(cInvenTory.GetItem(sinQW1 | sin02)) ? dwMask = 1 | 2 | 4 : 0;
		(cInvenTory.GetItem(sinQW1 | sin03)) ? dwMask = 1 | 2 | 4 | 8: 0;
		(cInvenTory.GetItem(sinQW1 | sin04)) ? dwMask = 1 | 2 | 4 | 8 | 16 : 0;
		(cInvenTory.GetItem(sinQW1 | sin05)) ? dwMask = 1 | 2 | 4 | 8 | 16 | 32 : 0;
		(cInvenTory.GetItem(sinQW1 | sin06)) ? dwMask = 1 | 2 | 4 | 8 | 16 | 32 | 64 : 0;

		(dwMask & 1) ? m_vPosition.push_back(MapWarpPosition(MAPID_RicartenTown, 96, 199, "Resources\\UI\\Warp\\Text\\Ricarten.txt")) : 0;
		(dwMask & 1) ? m_vPosition.push_back(MapWarpPosition(MAPID_PhillaiTown, 64, 21, "Resources\\UI\\Warp\\Text\\Pilai.txt")) : 0;
		(dwMask & 2) ? m_vPosition.push_back(MapWarpPosition(MAPID_LandOfDusk, 88, 84, "Resources\\UI\\Warp\\Text\\Forest2.txt")) : 0;
		(dwMask & 2) ? m_vPosition.push_back(MapWarpPosition(MAPID_BambooForest, 67, 177, "Resources\\UI\\Warp\\Text\\Forest3.txt")) : 0;
		(dwMask & 4) ? m_vPosition.push_back(MapWarpPosition(MAPID_RuinenVillage, 78, 116, "Resources\\UI\\Warp\\Text\\Ruinen.txt")) : 0;
		(dwMask & 8) ? m_vPosition.push_back(MapWarpPosition(MAPID_NaviskoTown, 150, 165, "Resources\\UI\\Warp\\Text\\Nevisco.txt")) : 0;
		(dwMask & 16) ? m_vPosition.push_back(MapWarpPosition(MAPID_ForbiddenLand, 158, 137, "Resources\\UI\\Warp\\Text\\Desert4.txt")) : 0;
		(dwMask & 32) ? m_vPosition.push_back(MapWarpPosition(MAPID_Eura, 155, 65, "Resources\\UI\\Warp\\Text\\yura.txt")) : 0;
		(dwMask & 64) ? m_vPosition.push_back(MapWarpPosition(MAPID_LandOfChaos, 140, 225, "Resources\\UI\\Warp\\Text\\chaoticpost.txt")) : 0;

		m_pcWindow->Show();
		m_pcClose->Show();

		m_bHover = FALSE;
		m_bActive = TRUE;
	}
	void Warp::Close()
	{
		m_vPosition.clear();

		m_pcWindow->Hide();
		m_pcClose->Hide();

		m_bHover = FALSE;
		m_bActive = FALSE;

		auto pcMap = lpCurPlayer->GetMap();

		pcMap ? pcMap->SetTeleport(m_sPosition.eID) : 0;

		m_sPosition = MapWarpPosition();
	}
	void Warp::Update()
	{
		!m_bHover ? LoadTextFromFile() : 0;
	}
	void Warp::Render()
	{
		if (m_bActive)
		{
			Animation();

			LINEHANDLE->MakeLine()->Draw(Rectangle2D(GetWarpPosition().iX - 20, GetWarpPosition().iY - 25, 710, 420), D3DCOLOR_ARGB(150, 0, 0, 0));

			m_pcWindow->Render(0, 0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);

			m_pcClose->Render(0, 0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);

			auto sPosition = Point2D(GetWarpPosition().iX + 422, GetWarpPosition().iY + 75);

			m_pcImage ? UI::ImageRender::Render(m_pcImage, sPosition.iX, sPosition.iY, 256, 256, -1) : 0;

			for (auto &v : m_vPosition)
			{
				m_pcIcon ? UI::ImageRender::Render(m_pcIcon, v.iX + sPosition.iX, v.iY + sPosition.iY, 16, 16, -1) : 0;
			}

			if (!m_bHover && m_sPosition.eID != MAPID_Invalid)
			{
				m_pcSelect ? UI::ImageRender::Render(m_pcSelect, m_sAniBox.iX, m_sAniBox.iY, m_sAniBox.iWidth, m_sAniBox.iHeight, D3DCOLOR_ARGB((int)(float)(m_fProcess * 255), 255, 255, 255)) : 0;
			}
		}
	}
	BOOL Warp::OnMouseClick(INPUTS::LPMOUSE pcMouse)
	{
		if (m_bActive)
		{
			m_pcWindow->OnMouseClick(pcMouse, 0, 0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);

			m_pcClose->OnMouseClick(pcMouse, 0, 0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);

			if (m_bSelected)
			{
				if (pcMouse->GetEvent() == ClickUpL)
					m_bSelected = FALSE;
			}
			else if (pcMouse->GetEvent() == ClickDownL && pcMouse->GetPosition()->Inside(Rectangle2D(GetWarpPosition().iX - 20, GetWarpPosition().iY - 25, 710, 420)) && m_sPosition.eID == MAPID_Invalid)
			{
				m_bSelected = TRUE;

				m_sPointMouse.iX = abs(pcMouse->GetPosition()->iX - GetWarpPosition().iX);
				m_sPointMouse.iY = abs(pcMouse->GetPosition()->iY - GetWarpPosition().iY);

				return TRUE;
			}

			if (pcMouse->GetEvent() == ClickUpL && !m_bHover)
			{
				if (m_sPosition.eID != MAPID_Invalid)
				{
					if (pcMouse->GetPosition()->Inside(Rectangle2D(m_sPosition.iX, m_sPosition.iY, 16, 16)))
					{
						if (MAPMODELHANDLE->GetMap(m_sPosition.eID)->GetLevel() > lpCurPlayer->smCharInfo.Level)
						{
							CTITLEBOX->SetText("No Enough Level");
						}
						else
						{
							m_bHover = TRUE;

							MESSAGEBOX->Enjoin(m_pcWindow);
							MESSAGEBOX->SetBoxType(MESSAGE::BOX::Window::BOXTYPEID_YesNo);
							MESSAGEBOX->SetTitle(MAPMODELHANDLE->GetMap(m_sPosition.eID)->GetName().c_str());
							MESSAGEBOX->SetDescription("Do you want to Teleport?");
							MESSAGEBOX->SetEvent(std::bind(&Warp::OnTeleport, this));
							MESSAGEBOX->SetAutoClose(5);
							MESSAGEBOX->Show();

							return TRUE;
						}
					}
				}
			}
		}

		return FALSE;
	}
	void Warp::OnMouseMove(INPUTS::LPMOUSE pcMouse)
	{
		if (m_bActive)
		{
			m_pcWindow->OnMouseMove(pcMouse, 0, 0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);

			m_pcClose->OnMouseMove(pcMouse, 0, 0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);

			if (!m_bHover)
			{
				auto sPosition = Point2D(GetWarpPosition().iX + 422, GetWarpPosition().iY + 75);

				m_sPosition = MapWarpPosition();

				for (auto &v : m_vPosition)
				{
					int iX = sPosition.iX + v.iX;
					int iY = sPosition.iY + v.iY;

					if (pcMouse->GetPosition()->Inside(Rectangle2D(iX, iY, 16, 16)))
					{
						m_sPosition = MapWarpPosition(v.eID, iX, iY, v.str);
						break;
					}
				}

				if (m_bSelected)
				{
					int iX = pcMouse->GetPosition()->iX - m_sPointMouse.iX;
					int iY = pcMouse->GetPosition()->iY - m_sPointMouse.iY;

					SetWarpPostion(Point2D(iX,iY));

					m_pcWindow->SetPosition(iX,iY);
					m_pcClose->SetPosition(iX + 670,iY - 30);
				}
			}
		}
	}
	void Warp::LoadTextFromFile()
	{
		if (!m_bHover)
		{
			if (m_eID != m_sPosition.eID)
			{
				auto pcTextWindow = m_pcWindow->GetElement<UI::TextWindow>(TEXTWINDOWID);
				pcTextWindow ? pcTextWindow->LoadTextFromFile(m_sPosition.str.c_str()) : 0;

				m_eID = m_sPosition.eID;
			}
		}
	}
	void Warp::Animation()
	{
		if (!m_bHover)
		{
			if (m_sPosition.eID == MAPID_Invalid)
			{
				m_bAnimation ? m_bAnimation = FALSE : 0;
			}
			if (m_sPosition.eID != MAPID_Invalid && !m_bAnimation)
			{
				if (m_pcSelect)
				{
					int iWidth = m_pcSelect->GetWidth();
					int iHeight = m_pcSelect->GetHeight();

					m_sAniBox = Rectangle2D(m_sPosition.iX - (iWidth >> 2), m_sPosition.iY - (iHeight >> 2), iWidth, iHeight);
					m_fProcess = 1.0f;

					m_bAnimation = TRUE;
				}
			}
			if (m_sPosition.eID != MAPID_Invalid && m_bAnimation)
			{
				m_sAniBox.iX--;
				m_sAniBox.iY--;
				m_sAniBox.iWidth += 2;
				m_sAniBox.iHeight += 2;

				m_fProcess -= 0.04f;
				m_fProcess < 0.0f ? m_fProcess = 0.0f : 0;
				m_fProcess == 0 ? m_bAnimation = FALSE : 0;
			}
		}
	}*/
}