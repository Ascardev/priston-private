#include "StdAfx.h"
#include "WarpWindow.h"

namespace MAP
{
	namespace WARP
	{
		/*Window::Window() : CBaseWindow()
		{

		}
		Window::Window(EWindow eID) : CBaseWindow(eID)
		{

		}
		Window::~Window()
		{

		}
		void Window::Init()
		{
			BuildWindow();
			BuildInfo();
			BuildMap();

			m_pWindow->Hide();
		}
		void Window::Shutdown()
		{
			m_pWindow->Clear();
		}
		void Window::Render()
		{
			m_pWindow->Render(0, 0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);
		}
		BOOL Window::OnMouseClick(INPUTS::LPMOUSE pcMouse)
		{
			return m_pWindow->OnMouseClick(pcMouse, 0, 0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);
		}
		void Window::OnMouseMove(INPUTS::LPMOUSE pcMouse)
		{
			m_pWindow->OnMouseMove(pcMouse, 0, 0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);
		}
		void Window::Show()
		{
			DWORD dwMask = 1;

			(cInvenTory.GetItem(sinQW1 | sin01)) ? dwMask = 1 | 2 : 0;
			(cInvenTory.GetItem(sinQW1 | sin02)) ? dwMask = 1 | 2 | 4 : 0;
			(cInvenTory.GetItem(sinQW1 | sin03)) ? dwMask = 1 | 2 | 4 | 8 : 0;
			(cInvenTory.GetItem(sinQW1 | sin04)) ? dwMask = 1 | 2 | 4 | 8 | 16 : 0;
			(cInvenTory.GetItem(sinQW1 | sin05)) ? dwMask = 1 | 2 | 4 | 8 | 16 | 32 : 0;
			(cInvenTory.GetItem(sinQW1 | sin06)) ? dwMask = 1 | 2 | 4 | 8 | 16 | 32 | 64 : 0;

			auto pWindow = m_pWindow->GetElement<UI::List>(LISTID_Main)->GetWindow(WINDOWID_Map);

			(dwMask & 1) ? pWindow->GetElement<UI::Button>(BUTTONID_RicartenTown)->Enable() : 0;
			(dwMask & 1) ? pWindow->GetElement<UI::Button>(BUTTONID_PhillaiTown)->Enable() : 0;
			(dwMask & 2) ? pWindow->GetElement<UI::Button>(BUTTONID_LandOfDusk)->Enable() : 0;
			(dwMask & 2) ? pWindow->GetElement<UI::Button>(BUTTONID_BambooForest)->Enable() : 0;
			(dwMask & 4) ? pWindow->GetElement<UI::Button>(BUTTONID_RuinenVillage)->Enable() : 0;
			(dwMask & 8) ? pWindow->GetElement<UI::Button>(BUTTONID_NaviskoTown)->Enable() : 0;
			(dwMask & 16) ? pWindow->GetElement<UI::Button>(BUTTONID_ForbiddenLand)->Enable() : 0;
			(dwMask & 32) ? pWindow->GetElement<UI::Button>(BUTTONID_Eura)->Enable() : 0;
			(dwMask & 64) ? pWindow->GetElement<UI::Button>(BUTTONID_LandOfChaos)->Enable() : 0;

			CGameCore::SetFocus(this);

			m_pWindow->Show();
		}
		void Window::BuildWindow()
		{
			m_pWindow = std::make_shared<UI::Window>(Rectangle2D(0, 0, 710, 420));
			m_pWindow->SetPosition(RESOLUTION_WIDTH / 2 - m_pWindow->GetWidth() / 2, RESOLUTION_HEIGHT / 2 - m_pWindow->GetHeight() / 2);

			UI::LPLIST pListMain = std::make_shared<UI::List>(Rectangle2D(0, 0, m_pWindow->GetWidth(), m_pWindow->GetHeight()));
			pListMain->SetID(LISTID_Main);
			pListMain->SetNoUpdatePosition(TRUE);

			m_pWindow->AddElement(pListMain);

			m_pWindow->SetCanMove(TRUE);
			m_pWindow->SetMoveBox(Rectangle2D(0, 0, m_pWindow->GetWidth(), m_pWindow->GetHeight()));
		}
		void Window::BuildInfo()
		{
			auto pWindowInfo = std::make_shared<UI::Window>(Rectangle2D(0, 0, 320, 374 + 20));
			pWindowInfo->SetID(WINDOWID_Info);

			UI::LPIMAGEBOX pWindowImage = std::make_shared<UI::ImageBox>(Rectangle2D(0, 20, 320, 374));
			pWindowImage->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Window\\Window2.png"));
			pWindowInfo->AddElement(pWindowImage);

			UI::LPTEXTWINDOW pTextWindow = std::make_shared<UI::TextWindow>(Rectangle2D(26, 30 + 20, 280, 304));
			pTextWindow->SetFont("Tahoma", 16, 0, FALSE, FALSE, -1);
			pTextWindow->SetID(TEXTWINDOWID);

			BuildText(pTextWindow);

			pWindowInfo->AddElement(pTextWindow);

			UI::LPIMAGEBOX pImageBoxHeaderBG = std::make_shared<UI::ImageBox>(Rectangle2D((320 >> 1) - (181 >> 1), -13 + 20, 181, 32));
			pImageBoxHeaderBG->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\window\\text\\header.png"));

			pWindowInfo->AddElement(pImageBoxHeaderBG);

			//Header Title
			UI::LPIMAGEBOX pImageBoxHeaderTitle = std::make_shared<UI::ImageBox>(Rectangle2D((320 >> 1) - (47 >> 1), -4 + 20, 47, 16));
			pImageBoxHeaderTitle->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\window\\text\\header_teleport.png"));

			pWindowInfo->AddElement(pImageBoxHeaderTitle);

			UI::LPBUTTON pButtonClose = std::make_shared<UI::Button>(Rectangle2D((320 >> 1) - (93 >> 1), 344 + 20, 93, 23));
			pButtonClose->SetActiveImage(UI::ImageLoader::LoadActiveImage("Resources\\UI\\window\\btnclose.png", "Resources\\UI\\window\\btnclose_.png"));
			pButtonClose->SetEvent(UI::Event::Build(std::bind(&Window::OnButtonClose, this)));

			pWindowInfo->AddElement(pButtonClose);

			m_pWindow->GetElement<UI::List>(LISTID_Main)->AddWindow(pWindowInfo);
		}
		void Window::BuildMap()
		{
			auto pWindowMap = std::make_shared<UI::Window>(Rectangle2D(470, 120, 256, 256));
			pWindowMap->SetID(WINDOWID_Map);

			// BackImageBox
			UI::LPIMAGEBOX pImageBackBox = std::make_shared<UI::ImageBox>(Rectangle2D(0, 0, 256, 256));
			pImageBackBox->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Warp\\WG_map.tga"));

			pWindowMap->AddElement(pImageBackBox);

			// 理查凳传送点
			pWindowMap->AddElement(AddButton(BUTTONID_RicartenTown, 96, 199, MAPID_RicartenTown));

			// 菲儿拉传送点
			pWindowMap->AddElement(AddButton(BUTTONID_PhillaiTown, 64, 21, MAPID_PhillaiTown));

			// 心情森林传送点
			pWindowMap->AddElement(AddButton(BUTTONID_LandOfDusk, 88, 84, MAPID_LandOfDusk));

			// 竹之林传送点
			pWindowMap->AddElement(AddButton(BUTTONID_BambooForest, 67, 177, MAPID_BambooForest));

			// 废墟村庄传送点
			pWindowMap->AddElement(AddButton(BUTTONID_RuinenVillage, 78, 116, MAPID_RuinenVillage));

			// 内威斯克传送点
			pWindowMap->AddElement(AddButton(BUTTONID_NaviskoTown, 150, 165, MAPID_NaviskoTown));

			// 封印之地传送点
			pWindowMap->AddElement(AddButton(BUTTONID_ForbiddenLand, 158, 137, MAPID_ForbiddenLand));

			// 幽拉村庄传送点
			pWindowMap->AddElement(AddButton(BUTTONID_Eura, 155, 65, MAPID_Eura));

			// 迷失之地传送点
			pWindowMap->AddElement(AddButton(BUTTONID_LandOfChaos, 140, 225, MAPID_LandOfChaos));

			// 祝福城堡传送点
			pWindowMap->AddElement(AddButton(BUTTONID_BlessCastle, 69, 207, MAPID_BlessCastle));

			m_pWindow->GetElement<UI::List>(LISTID_Main)->AddWindow(pWindowMap);
		}
		void Window::BuildText(UI::LPTEXTWINDOW pTextWindow)
		{
			pTextWindow->LoadTextFromFile("Resources\\UI\\Warp\\Text\\Default.txt");

			pTextWindow->Append("Metal Wing:                       1000 Gold\n");
			pTextWindow->Append("Silver Wing:                       1000 Gold\n");
			pTextWindow->Append("Gold Wing:                        1000 Gold\n");
			pTextWindow->Append("Diamond Wing:                  1000 Gold\n");
			pTextWindow->Append("Chaos Wing:                      1000 Gold\n");
			pTextWindow->Append("Imperial Wing:                    1000 Gold\n");
		}
		UI::LPBUTTON Window::AddButton(int iID, int iX, int iY, EMapID eID)
		{
			UI::LPBUTTON pButton = std::make_shared<UI::Button>(Rectangle2D(iX, iY, 16, 16));
			pButton->SetID(iID);
			pButton->SetEvent(UI::Event::Build(std::bind(&Window::OnButtonMouseMoveIn, this, iID)), EVENT_MoveIn);
			pButton->SetEvent(UI::Event::Build(std::bind(&Window::OnButtonMouseMoveOut, this)), EVENT_MoveOut);
			pButton->SetEvent(UI::Event::Build(std::bind(&Window::OnButtonWarpGate, this, eID)));
			pButton->SetActiveImage(UI::ImageLoader::LoadActiveImage("Resources\\UI\\Warp\\WG_icon.tga", "Resources\\UI\\Warp\\WG_icon.tga"));
			pButton->SetAnimateImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Warp\\WG_slt.tga"));
			pButton->SetAnimation(TRUE);
			pButton->Disable();

			return pButton;
		}
		void Window::OnButtonMouseMoveIn(int iID)
		{
			auto pList = m_pWindow->GetElement<UI::List>(LISTID_Main);
			auto pWindowInfo = pList->GetWindow(WINDOWID_Info);
			auto pTextWindow = pWindowInfo->GetElement<UI::TextWindow>(TEXTWINDOWID);

			if (iID == BUTTONID_RicartenTown)
				pTextWindow->LoadTextFromFile("Resources\\UI\\Warp\\Text\\Ricarten.txt");
			else if (iID == BUTTONID_PhillaiTown)
				pTextWindow->LoadTextFromFile("Resources\\UI\\Warp\\Text\\Pilai.txt");
			else if (iID == BUTTONID_LandOfDusk)
				pTextWindow->LoadTextFromFile("Resources\\UI\\Warp\\Text\\Ruinen.txt");
			else if (iID == BUTTONID_BambooForest)
				pTextWindow->LoadTextFromFile("Resources\\UI\\Warp\\Text\\Forest3.txt");
			else if (iID == BUTTONID_RuinenVillage)
				pTextWindow->LoadTextFromFile("Resources\\UI\\Warp\\Text\\Ruinen.txt");
			else if (iID == BUTTONID_NaviskoTown)
				pTextWindow->LoadTextFromFile("Resources\\UI\\Warp\\Text\\Nevisco.txt");
			else if (iID == BUTTONID_ForbiddenLand)
				pTextWindow->LoadTextFromFile("Resources\\UI\\Warp\\Text\\Desert4.txt");
			else if (iID == BUTTONID_Eura)
				pTextWindow->LoadTextFromFile("Resources\\UI\\Warp\\Text\\yura.txt");
			else if (iID == BUTTONID_LandOfChaos)
				pTextWindow->LoadTextFromFile("Resources\\UI\\Warp\\Text\\chaoticpost.txt");
			else if (iID == BUTTONID_BlessCastle)
				pTextWindow->LoadTextFromFile("Resources\\UI\\Warp\\Text\\B_Castle.txt");
		}
		void Window::OnButtonMouseMoveOut()
		{
			auto pList = m_pWindow->GetElement<UI::List>(LISTID_Main);
			auto pWindowInfo = pList->GetWindow(WINDOWID_Info);

			BuildText(pWindowInfo->GetElement<UI::TextWindow>(TEXTWINDOWID));
		}
		void Window::OnButtonClose()
		{
			//Close ?
			m_pWindow->Hide();
			WarpGate(MAPID_Invalid);
		}
		void Window::OnButtonWarpGate(int iID)
		{
			int iLevel = lpCurPlayer->smCharInfo.Level;

			if (MAPMODELHANDLE->GetMap((EMapID)iID)->GetLevel() > iLevel)
			{
				CTITLEBOX->SetText("No Enough Level");
			}
			else
			{
				MESSAGEBOX->Enjoin(m_pWindow);
				MESSAGEBOX->SetBoxType(MESSAGE::BOX::Window::BOXTYPEID_YesNo);
				MESSAGEBOX->SetTitle(MAPMODELHANDLE->GetMap((EMapID)iID)->GetName().c_str());
				MESSAGEBOX->SetDescription("Do you want to Teleport?");
				MESSAGEBOX->SetEvent(std::bind(&Window::OnWarpGate, this, iID));
				MESSAGEBOX->SetAutoClose(5);
				MESSAGEBOX->Show();
			}
		}
		void Window::OnWarpGate(int iID)
		{
			// iButton is No
			if (!MESSAGEBOX->GetType())
			{
				// No WarpGate ?
				return;
			}

			m_pWindow->Hide();
			WarpGate((EMapID)iID);
		}
		void Window::WarpGate(EMapID eID)
		{
			m_pWindow->Hide();

			static_cast<Handle *>(CGameCore::GetHandle(EHANDLE_MapWarp))->SetWarpGate(eID);
		}*/
	}
}