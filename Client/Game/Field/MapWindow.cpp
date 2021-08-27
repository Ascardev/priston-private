#include "StdAfx.h"
#include "MapWindow.h"

namespace MAP
{
	Window::Window()
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

		m_pcWindow->Hide();
	}
	void Window::Shutdown()
	{
		m_pcWindow->Clear();
	}
	/*void Window::Update(float fTime)
	{

	}*/
	void Window::Render()
	{
		m_pcWindow->Render(0, 0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);
	}
	BOOL Window::OnMouseClick(INPUTS::LPMOUSE pcMouse)
	{
		return m_pcWindow->OnMouseClick(pcMouse, 0, 0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);
	}
	void Window::OnMouseMove(INPUTS::LPMOUSE pcMouse)
	{
		m_pcWindow->OnMouseMove(pcMouse, 0, 0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);
	}
	void Window::BuildWindow()
	{
		m_pcWindow = std::make_shared<UI::Window>(Rectangle2D(0, 0, 710, 420));
		m_pcWindow->SetPosition(RESOLUTION_WIDTH / 2 - m_pcWindow->GetWidth() / 2, RESOLUTION_HEIGHT / 2 - m_pcWindow->GetHeight() / 2);

		UI::LPLIST pListMain = std::make_shared<UI::List>(Rectangle2D(0, 0, m_pcWindow->GetWidth(), m_pcWindow->GetHeight()));
		pListMain->SetID(LISTID_Main);
		pListMain->SetNoUpdatePosition(TRUE);

		m_pcWindow->AddElement(pListMain);

		m_pcWindow->SetCanMove(TRUE);
		m_pcWindow->SetMoveBox(Rectangle2D(0, 0, m_pcWindow->GetWidth(), m_pcWindow->GetHeight()));
	}
	void Window::BuildInfo()
	{
		auto pWindowInfo = std::make_shared<UI::Window>(Rectangle2D(0, 0, 320, 374 + 20));
		pWindowInfo->SetID(WINDOWID_Info);

		UI::LPIMAGEBOX pWindowImage = std::make_shared<UI::ImageBox>(Rectangle2D(0, 20, 320, 374));
		pWindowImage->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Window\\Window2.png"));
		pWindowInfo->AddElement(pWindowImage);

		UI::LPTEXTWINDOW pTextWindow = std::make_shared<UI::TextWindow>(Rectangle2D(26, 30 + 20, 280, 304));
		pTextWindow->SetFont("Tahoma", 15, 0, FALSE, FALSE, -1);
		pTextWindow->SetID(TEXTWINDOWID);

		pWindowInfo->AddElement(pTextWindow);

		UI::LPIMAGEBOX pImageBoxHeaderBG = std::make_shared<UI::ImageBox>(Rectangle2D((320 >> 1) - (181 >> 1), -13 + 20, 181, 32));
		pImageBoxHeaderBG->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\window\\text\\header.png"));

		pWindowInfo->AddElement(pImageBoxHeaderBG);

		//Header Title
		UI::LPIMAGEBOX pImageBoxHeaderTitle = std::make_shared<UI::ImageBox>(Rectangle2D((320 >> 1) - (47 >> 1), -4 + 20, 47, 16));
		pImageBoxHeaderTitle->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\window\\text\\header_teleport.png"));

		pWindowInfo->AddElement(pImageBoxHeaderTitle);

		UI::LPBUTTON pButtonClose = std::make_shared<UI::Button>(Rectangle2D((320 >> 1) - (93 >> 1), 346 + 20, 93, 23));
		pButtonClose->SetActiveImage(UI::ImageLoader::LoadActiveImage("Resources\\UI\\window\\btnclose.png", "Resources\\UI\\window\\btnclose_.png"));

		pWindowInfo->AddElement(pButtonClose);

		m_pcWindow->GetElement<UI::List>(LISTID_Main)->AddWindow(pWindowInfo);
	}
	void Window::BuildMap()
	{
		auto pWindowMap = std::make_shared<UI::Window>(Rectangle2D(470, 120, 256, 256));
		pWindowMap->SetID(WINDOWID_Map);

		// 背景图片
		UI::LPIMAGEBOX pImageBox = std::make_shared<UI::ImageBox>(Rectangle2D(0, 0, 256, 256));
		pImageBox->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Warp\\WG_map.tga"));

		pWindowMap->AddElement(pImageBox);

		// 理查凳传送点
		UI::LPBUTTON pButtonRicartenTown = std::make_shared<UI::Button>(Rectangle2D(96, 199, 16, 16));
		pButtonRicartenTown->SetID(BUTTONID_RicartenTown);
		pButtonRicartenTown->SetEvent(UI::Event::Build(std::bind(&Window::OnButtonMouseMoveIn, this, BUTTONID_RicartenTown)), EVENT_MoveIn);
		pButtonRicartenTown->SetEvent(UI::Event::Build(std::bind(&Window::OnButtonMouseMoveOut, this)), EVENT_MoveOut);
		pButtonRicartenTown->SetActiveImage(UI::ImageLoader::LoadActiveImage("Resources\\UI\\Warp\\WG_icon.tga", "Resources\\UI\\Warp\\WG_icon.tga"));
		pButtonRicartenTown->SetAnimateImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Warp\\WG_slt.tga"));
		pButtonRicartenTown->SetAnimation(TRUE);

		pWindowMap->AddElement(pButtonRicartenTown);

		// 菲儿拉传送点
		UI::LPBUTTON pButtonPhillaiTown = std::make_shared<UI::Button>(Rectangle2D(64, 21, 16, 16));
		pButtonPhillaiTown->SetID(BUTTONID_PhillaiTown);
		pButtonPhillaiTown->SetEvent(UI::Event::Build(std::bind(&Window::OnButtonMouseMoveIn, this, BUTTONID_PhillaiTown)), EVENT_MoveIn);
		pButtonPhillaiTown->SetEvent(UI::Event::Build(std::bind(&Window::OnButtonMouseMoveOut, this)), EVENT_MoveOut);
		pButtonPhillaiTown->SetActiveImage(UI::ImageLoader::LoadActiveImage("Resources\\UI\\Warp\\WG_icon.tga", "Resources\\UI\\Warp\\WG_icon.tga"));
		pButtonPhillaiTown->SetAnimateImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Warp\\WG_icon.tga"));
		pButtonPhillaiTown->SetAnimation(TRUE);

		pWindowMap->AddElement(pButtonPhillaiTown);

		// 心情森林传送点
		UI::LPBUTTON pButtonLandOfDusk = std::make_shared<UI::Button>(Rectangle2D(88, 84, 16, 16));
		pButtonLandOfDusk->SetID(BUTTONID_LandOfDusk);
		pButtonLandOfDusk->SetEvent(UI::Event::Build(std::bind(&Window::OnButtonMouseMoveIn, this, BUTTONID_LandOfDusk)), EVENT_MoveIn);
		pButtonLandOfDusk->SetEvent(UI::Event::Build(std::bind(&Window::OnButtonMouseMoveOut, this)), EVENT_MoveOut);
		pButtonLandOfDusk->SetActiveImage(UI::ImageLoader::LoadActiveImage("Resources\\UI\\Warp\\WG_icon.tga", "Resources\\UI\\Warp\\WG_icon.tga"));
		pButtonLandOfDusk->SetAnimateImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Warp\\WG_icon.tga"));
		pButtonLandOfDusk->SetAnimation(TRUE);

		pWindowMap->AddElement(pButtonLandOfDusk);

		// 竹之林传送点
		UI::LPBUTTON pButtonBambooForest = std::make_shared<UI::Button>(Rectangle2D(67, 177, 16, 16));
		pButtonBambooForest->SetID(BUTTONID_BambooForest);
		pButtonBambooForest->SetEvent(UI::Event::Build(std::bind(&Window::OnButtonMouseMoveIn, this, BUTTONID_BambooForest)), EVENT_MoveIn);
		pButtonBambooForest->SetEvent(UI::Event::Build(std::bind(&Window::OnButtonMouseMoveOut, this)), EVENT_MoveOut);
		pButtonBambooForest->SetActiveImage(UI::ImageLoader::LoadActiveImage("Resources\\UI\\Warp\\WG_icon.tga", "Resources\\UI\\Warp\\WG_icon.tga"));
		pButtonBambooForest->SetAnimateImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Warp\\WG_icon.tga"));
		pButtonBambooForest->SetAnimation(TRUE);

		pWindowMap->AddElement(pButtonBambooForest);

		// 废墟村庄传送点
		UI::LPBUTTON pButtonRuinenVillage = std::make_shared<UI::Button>(Rectangle2D(78, 116, 16, 16));
		pButtonRuinenVillage->SetID(BUTTONID_RuinenVillage);
		pButtonRuinenVillage->SetEvent(UI::Event::Build(std::bind(&Window::OnButtonMouseMoveIn, this, BUTTONID_RuinenVillage)), EVENT_MoveIn);
		pButtonRuinenVillage->SetEvent(UI::Event::Build(std::bind(&Window::OnButtonMouseMoveOut, this)), EVENT_MoveOut);
		pButtonRuinenVillage->SetActiveImage(UI::ImageLoader::LoadActiveImage("Resources\\UI\\Warp\\WG_icon.tga", "Resources\\UI\\Warp\\WG_icon.tga"));
		pButtonRuinenVillage->SetAnimateImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Warp\\WG_icon.tga"));
		pButtonRuinenVillage->SetAnimation(TRUE);

		pWindowMap->AddElement(pButtonRuinenVillage);

		// 内威斯克传送点
		UI::LPBUTTON pButtonNaviskoTown = std::make_shared<UI::Button>(Rectangle2D(150, 165, 16, 16));
		pButtonNaviskoTown->SetID(BUTTONID_NaviskoTown);
		pButtonNaviskoTown->SetEvent(UI::Event::Build(std::bind(&Window::OnButtonMouseMoveIn, this, BUTTONID_NaviskoTown)), EVENT_MoveIn);
		pButtonNaviskoTown->SetEvent(UI::Event::Build(std::bind(&Window::OnButtonMouseMoveOut, this)), EVENT_MoveOut);
		pButtonNaviskoTown->SetActiveImage(UI::ImageLoader::LoadActiveImage("Resources\\UI\\Warp\\WG_icon.tga", "Resources\\UI\\Warp\\WG_icon.tga"));
		pButtonNaviskoTown->SetAnimateImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Warp\\WG_icon.tga"));
		pButtonNaviskoTown->SetAnimation(TRUE);

		pWindowMap->AddElement(pButtonNaviskoTown);

		// 封印之地传送点
		UI::LPBUTTON pButtonForbiddenLand = std::make_shared<UI::Button>(Rectangle2D(158, 137, 16, 16));
		pButtonForbiddenLand->SetID(BUTTONID_ForbiddenLand);
		pButtonForbiddenLand->SetEvent(UI::Event::Build(std::bind(&Window::OnButtonMouseMoveIn, this, BUTTONID_ForbiddenLand)), EVENT_MoveIn);
		pButtonForbiddenLand->SetEvent(UI::Event::Build(std::bind(&Window::OnButtonMouseMoveOut, this)), EVENT_MoveOut);
		pButtonForbiddenLand->SetActiveImage(UI::ImageLoader::LoadActiveImage("Resources\\UI\\Warp\\WG_icon.tga", "Resources\\UI\\Warp\\WG_icon.tga"));
		pButtonForbiddenLand->SetAnimateImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Warp\\WG_icon.tga"));
		pButtonForbiddenLand->SetAnimation(TRUE);

		pWindowMap->AddElement(pButtonForbiddenLand);

		// 幽拉村庄传送点
		UI::LPBUTTON pButtonEura = std::make_shared<UI::Button>(Rectangle2D(155, 65, 16, 16));
		pButtonEura->SetID(BUTTONID_Eura);
		pButtonEura->SetEvent(UI::Event::Build(std::bind(&Window::OnButtonMouseMoveIn, this, BUTTONID_Eura)), EVENT_MoveIn);
		pButtonEura->SetEvent(UI::Event::Build(std::bind(&Window::OnButtonMouseMoveOut, this)), EVENT_MoveOut);
		pButtonEura->SetActiveImage(UI::ImageLoader::LoadActiveImage("Resources\\UI\\Warp\\WG_icon.tga", "Resources\\UI\\Warp\\WG_icon.tga"));
		pButtonEura->SetAnimateImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Warp\\WG_icon.tga"));
		pButtonEura->SetAnimation(TRUE);

		pWindowMap->AddElement(pButtonEura);

		// 迷失之地传送点
		UI::LPBUTTON pButtonLandOfChaos = std::make_shared<UI::Button>(Rectangle2D(140, 225, 16, 16));
		pButtonLandOfChaos->SetID(BUTTONID_LandOfChaos);
		pButtonLandOfChaos->SetEvent(UI::Event::Build(std::bind(&Window::OnButtonMouseMoveIn, this, BUTTONID_LandOfChaos)), EVENT_MoveIn);
		pButtonLandOfChaos->SetEvent(UI::Event::Build(std::bind(&Window::OnButtonMouseMoveOut, this)), EVENT_MoveOut);
		pButtonLandOfChaos->SetActiveImage(UI::ImageLoader::LoadActiveImage("Resources\\UI\\Warp\\WG_icon.tga", "Resources\\UI\\Warp\\WG_icon.tga"));
		pButtonLandOfChaos->SetAnimateImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Warp\\WG_icon.tga"));
		pButtonLandOfChaos->SetAnimation(TRUE);

		pWindowMap->AddElement(pButtonLandOfChaos);

		m_pcWindow->GetElement<UI::List>(LISTID_Main)->AddWindow(pWindowMap);
	}
	void Window::OnButtonMouseMoveIn(int iID)
	{
		auto pList = m_pcWindow->GetElement<UI::List>(LISTID_Main);
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
	}
	void Window::OnButtonMouseMoveOut()
	{
		auto pList = m_pcWindow->GetElement<UI::List>(LISTID_Main);
		auto pWindowInfo = pList->GetWindow(WINDOWID_Info);

		pWindowInfo->GetElement<UI::TextWindow>(TEXTWINDOWID)->LoadTextFromFile("Resources\\UI\\Warp\\Text\\Default.txt");
	}
}