#include "StdAfx.h"
#include "CharacterStatusWindow.h"

namespace CHARACTER
{
	namespace STATUS
	{
		Window::Window() : CBaseWindow()
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
			BuidWindow();

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
		void Window::Update(float fTime)
		{
			m_pWindow->Update(fTime);
		}
		void Window::Tick()
		{
			if (m_pWindow->IsOpen())
			{
				Load();
			}
		}
		void Window::Show()
		{
			Load();
			m_pWindow->Show();

			CGameCore::SetFocus(this);
		}
		BOOL Window::OnMouseClick(INPUTS::LPMOUSE pcMouse)
		{
			return m_pWindow->OnMouseClick(pcMouse, 0, 0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);
		}
		BOOL Window::OnMouseScroll(INPUTS::LPMOUSE pcMouse)
		{
			return m_pWindow->OnMouseScroll(pcMouse, 0, 0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);
		}
		void Window::OnMouseMove(INPUTS::LPMOUSE pcMouse)
		{
			m_pWindow->OnMouseMove(pcMouse, 0, 0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);
		}
		void Window::BuidWindow()
		{
			m_pWindow = std::make_shared<UI::Window>(Rectangle2D(0, 0, 314, 505));
			m_pWindow->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Status\\window.png"));
			m_pWindow->SetPosition(RESOLUTION_WIDTH / 2 - m_pWindow->GetWidth() / 2, RESOLUTION_HEIGHT / 2 - m_pWindow->GetHeight() / 2);

			m_pWindow->SetMoveBox(Rectangle2D(0, 0, m_pWindow->GetWidth(), 34));
			m_pWindow->SetCanMove(!SETTINGHANDLE->Get().bLockUI);

			UI::LPIMAGEBOX pImageCharacter = std::make_shared<UI::ImageBox>(Rectangle2D(16, 51, 282, 58));

			pImageCharacter->SetID(IMAGEBOXID_Character);
			m_pWindow->AddElement(pImageCharacter);

			UI::LPBUTTON pButtonClose = std::make_shared<UI::Button>(Rectangle2D(275, 10, 30, 28));
			pButtonClose->SetActiveImage(UI::ImageLoader::LoadActiveImage("Resources\\UI\\Status\\closebtn.png", "Resources\\UI\\Status\\closebtn_.png"));
			pButtonClose->SetEvent(UI::Event::Build(std::bind(&Window::OnClose, this, std::placeholders::_1)));
			pButtonClose->SetSelect(TRUE);
			m_pWindow->AddElement(pButtonClose);

			//Text Character Name
			UI::LPTEXT pTextName = std::make_shared<UI::Text>(Rectangle2D(34, 120, 0, 0));
			pTextName->SetFont("Tahoma", 16, 0, FALSE, TRUE, D3DCOLOR_ARGB(255, 255, 245, 215));
			pTextName->SetID(TEXTID_Name);
			m_pWindow->AddElement(pTextName);

			UI::LPTEXT pTextTitle = std::make_shared<UI::Text>(Rectangle2D(34, 138, 0, 0));
			pTextTitle->SetFont("Tahoma", 16, 0, FALSE, TRUE, D3DCOLOR_ARGB(255, 255, 245, 215));
			pTextTitle->SetID(TEXTID_Title);
			m_pWindow->AddElement(pTextTitle);

			UI::LPTEXT pTextClan = std::make_shared<UI::Text>(Rectangle2D(178, 120, 0, 0));
			pTextClan->SetFont("Arial", 16, 0, FALSE, TRUE, D3DCOLOR_ARGB(255, 255, 245, 215));
			pTextClan->SetID(TEXTID_Clan);
			m_pWindow->AddElement(pTextClan);

			UI::LPTEXT pTextLevel = std::make_shared<UI::Text>(Rectangle2D(178, 138, 0, 0));
			pTextLevel->SetFont("Tahoma", 16, 0, FALSE, TRUE, D3DCOLOR_ARGB(255, 255, 245, 215));
			pTextLevel->SetID(TEXTID_Level);
			m_pWindow->AddElement(pTextLevel);

			UI::LPIMAGEBOX pImageBarHP = std::make_shared<UI::ImageBox>(Rectangle2D(50, 178, 51, 51));

			pImageBarHP->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Status\\hp.png"));
			m_pWindow->AddElement(pImageBarHP);

			UI::LPTEXT pTextBarHP = std::make_shared<UI::Text>(Rectangle2D(50, 178, 51, 51));
			pTextBarHP->SetFont("Tahoma", 18, 0, FALSE, TRUE, D3DCOLOR_ARGB(255, 255, 245, 215));
			pTextBarHP->SetID(TEXTID_HP);
			m_pWindow->AddElement(pTextBarHP);

			UI::LPIMAGEBOX pImageBarMP = std::make_shared<UI::ImageBox>(Rectangle2D(130, 178, 51, 51));

			pImageBarMP->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Status\\mp.png"));
			m_pWindow->AddElement(pImageBarMP);

			UI::LPTEXT pTextBarMP = std::make_shared<UI::Text>(Rectangle2D(130, 178, 51, 51));
			pTextBarMP->SetFont("Tahoma", 18, 0, FALSE, TRUE, D3DCOLOR_ARGB(255, 255, 245, 215));
			pTextBarMP->SetID(TEXTID_MP);
			m_pWindow->AddElement(pTextBarMP);

			UI::LPIMAGEBOX pImageBarSP = std::make_shared<UI::ImageBox>(Rectangle2D(210, 178, 51, 51));

			pImageBarSP->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Status\\sp.png"));
			m_pWindow->AddElement(pImageBarSP);

			UI::LPTEXT pTextBarSP = std::make_shared<UI::Text>(Rectangle2D(210, 178, 51, 51));
			pTextBarSP->SetFont("Tahoma", 18, 0, FALSE, TRUE, D3DCOLOR_ARGB(255, 255, 245, 215));
			pTextBarSP->SetID(TEXTID_SP);
			m_pWindow->AddElement(pTextBarSP);

			UI::LPCHECKBOX pCheckBoxFastAdd = std::make_shared<UI::CheckBox>(Rectangle2D(28, 240, 13, 13));
			pCheckBoxFastAdd->SetFont("Tahoma", 14, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 255, 245, 215));
			pCheckBoxFastAdd->SetID(CHECKBOXID_FastAdd);
			pCheckBoxFastAdd->SetText("Fast Add");
			pCheckBoxFastAdd->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
			m_pWindow->AddElement(pCheckBoxFastAdd);

			UI::LPTEXT pTextStatusremain = std::make_shared<UI::Text>(Rectangle2D(285, 240, 0, 0));

			pTextStatusremain->SetFont("Tahoma", 14, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 255, 245, 215));
			pTextStatusremain->SetHorizontalAlign(ALIGN_Right);
			pTextStatusremain->SetID(TEXTID_StatsPoint);
			m_pWindow->AddElement(pTextStatusremain);

			int iY = 258;

			UI::LPIMAGEBOX pImageBarSTR = std::make_shared<UI::ImageBox>(Rectangle2D(28,iY, 45, 45));

			pImageBarSTR->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Status\\str.png"));
			m_pWindow->AddElement(pImageBarSTR);

			UI::LPTEXT pTextBarSTR = std::make_shared<UI::Text>(Rectangle2D(28, iY - 8, 45, 45));
			pTextBarSTR->SetFont("Tahoma", 18, 0, FALSE, TRUE, -1);
			pTextBarSTR->SetID(TEXTID_Str),
			m_pWindow->AddElement(pTextBarSTR);

			UI::LPIMAGEBOX pImageBarSPI = std::make_shared<UI::ImageBox>(Rectangle2D(28 + 53 * 1, iY, 45, 45));

			pImageBarSPI->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Status\\spi.png"));
			m_pWindow->AddElement(pImageBarSPI);

			UI::LPTEXT pTextBarSPI = std::make_shared<UI::Text>(Rectangle2D(28 + 53 * 1, iY - 8, 45, 45));
			pTextBarSPI->SetFont("Tahoma", 18, 0, FALSE, TRUE, -1);
			pTextBarSPI->SetID(TEXTID_Spi),
			m_pWindow->AddElement(pTextBarSPI);

			UI::LPIMAGEBOX pImageBarTAL = std::make_shared<UI::ImageBox>(Rectangle2D(28 + 53 * 2, iY, 45, 45));

			pImageBarTAL->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Status\\tal.png"));
			m_pWindow->AddElement(pImageBarTAL);

			UI::LPTEXT pTextBarTAL = std::make_shared<UI::Text>(Rectangle2D(28 + 53 * 2, iY - 8, 45, 45));
			pTextBarTAL->SetFont("Tahoma", 18, 0, FALSE, TRUE, -1);
			pTextBarTAL->SetID(TEXTID_Tal);
			m_pWindow->AddElement(pTextBarTAL);

			UI::LPIMAGEBOX pImageBarAGI = std::make_shared<UI::ImageBox>(Rectangle2D(28 + 53 * 3, iY, 45, 45));

			pImageBarAGI->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Status\\agi.png"));
			m_pWindow->AddElement(pImageBarAGI);

			UI::LPTEXT pTextBarAGI = std::make_shared<UI::Text>(Rectangle2D(28 + 53 * 3, iY - 8, 45, 45));
			pTextBarAGI->SetFont("Tahoma", 18, 0, FALSE, TRUE, -1);
			pTextBarAGI->SetID(TEXTID_Agi);
			m_pWindow->AddElement(pTextBarAGI);

			UI::LPIMAGEBOX pImageBarVIT = std::make_shared<UI::ImageBox>(Rectangle2D(28 + 53 * 4, iY, 45, 45));

			pImageBarVIT->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Status\\vit.png"));
			m_pWindow->AddElement(pImageBarVIT);

			UI::LPTEXT pTextBarVIT = std::make_shared<UI::Text>(Rectangle2D(28 + 53 * 4, iY - 8, 45, 45));
			pTextBarVIT->SetFont("Tahoma", 18, 0, FALSE, TRUE, -1);
			pTextBarVIT->SetID(TEXTID_Vit);
			m_pWindow->AddElement(pTextBarVIT);

			for (int i = 0; i < 5; i++)
			{
				UI::LPBUTTON pButtonUp = std::make_shared<UI::Button>(Rectangle2D(28 + 53 * i, iY + 47, 45, 8));

				pButtonUp->SetActiveImage(UI::ImageLoader::LoadActiveImage("", "Resources\\UI\\Status\\up.png"));
				pButtonUp->SetID(BUTTONID_Str + i);
				pButtonUp->SetEvent(UI::Event::Build(std::bind(&Window::OnUpdateStatus, this, pButtonUp->GetID())));
				pButtonUp->SetSelect(TRUE);
				m_pWindow->AddElement(pButtonUp);
			}

			UI::LPLIST pListStatus = std::make_shared<UI::List>(Rectangle2D(28, iY + 64, 257, 125));
			pListStatus->SetID(LISTID_WindowBox);
			pListStatus->MakeScrollBar(Rectangle2D(252, 0, 6, 125), "Resources\\UI\\Scroll\\barbg_v.png", "Resources\\UI\\Scroll\\icon_2.png");
			pListStatus->SetScrollFirst(TRUE);

			// add list
			{
				UI::LPWINDOW pWindowStatus = std::make_shared<UI::Window>(Rectangle2D(0, 0, 257, 36 + 16 * 7));
				pWindowStatus->SetID(WINDOWID_Box);
				pWindowStatus->SetColorBackground(UI::Color(200, 0, 0, 0));

				UI::LPTEXT pTextAttackPower = std::make_shared<UI::Text>(Rectangle2D(10, 10, 0, 0));
				pTextAttackPower->SetFont("Tahoma", 16, 0, FALSE, FALSE, -1);
				pTextAttackPower->SetID(TEXTID_AttackPower);
				pWindowStatus->AddElement(pTextAttackPower);

				UI::LPTEXT pTextAttackRating = std::make_shared<UI::Text>(Rectangle2D(10, 10 + 16 * 1, 0, 0));
				pTextAttackRating->SetFont("Tahoma", 16, 0, FALSE, FALSE, -1);
				pTextAttackRating->SetID(TEXTID_AttackRating);
				pWindowStatus->AddElement(pTextAttackRating);

				UI::LPTEXT pTextDefense = std::make_shared<UI::Text>(Rectangle2D(10, 10 + 16 * 2, 0, 0));
				pTextDefense->SetFont("Tahoma", 16, 0, FALSE, FALSE, -1);
				pTextDefense->SetID(TEXTID_Defense);
				pWindowStatus->AddElement(pTextDefense);

				UI::LPTEXT pTextAbsorption = std::make_shared<UI::Text>(Rectangle2D(10, 10 + 16 * 3, 0, 0));
				pTextAbsorption->SetFont("Tahoma", 16, 0, FALSE, FALSE, -1);
				pTextAbsorption->SetID(TEXTID_Absorption);
				pWindowStatus->AddElement(pTextAbsorption);

				UI::LPTEXT pTextMoveSpeed = std::make_shared<UI::Text>(Rectangle2D(10, 10 + 16 * 4, 0, 0));
				pTextMoveSpeed->SetFont("Tahoma", 16, 0, FALSE, FALSE, -1);
				pTextMoveSpeed->SetID(TEXTID_MoveSpeed);
				pWindowStatus->AddElement(pTextMoveSpeed);

				UI::LPTEXT pTextCriticalRate = std::make_shared<UI::Text>(Rectangle2D(10, 10 + 16 * 5, 0, 0));
				pTextCriticalRate->SetFont("Tahoma", 16, 0, FALSE, FALSE, -1);
				pTextCriticalRate->SetID(TEXTID_Critical);
				pWindowStatus->AddElement(pTextCriticalRate);

				UI::LPTEXT pTextBlock = std::make_shared<UI::Text>(Rectangle2D(10, 10 + 16 * 6, 0, 0));
				pTextBlock->SetFont("Tahoma", 16, 0, FALSE, FALSE, -1);
				pTextBlock->SetID(TEXTID_Block);
				pWindowStatus->AddElement(pTextBlock);

				UI::LPTEXT pTextEvade = std::make_shared<UI::Text>(Rectangle2D(10, 10 + 16 * 7, 0, 0));
				pTextEvade->SetFont("Tahoma", 16, 0, FALSE, FALSE, -1);
				pTextEvade->SetID(TEXTID_Evade);
				pWindowStatus->AddElement(pTextEvade);

				pListStatus->AddWindow(pWindowStatus);
			}

			m_pWindow->AddElement(pListStatus);

			UI::LPIMAGEBOX pImageOrganic = std::make_shared<UI::ImageBox>(Rectangle2D(28, 456, 22, 22));
			pImageOrganic->SetID(IMAGEBOXID_Organic);
			pImageOrganic->SetEvent(UI::Event::Build(std::bind(&Window::OnImageBoxMouseMove, this, IMAGEBOXID_Organic)));
			pImageOrganic->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Status\\info\\organic.png"));

			m_pWindow->AddElement(pImageOrganic);

			UI::LPTEXT pTextOrganic = std::make_shared<UI::Text>(Rectangle2D(58, 459, 22, 22));

			pTextOrganic->SetFont("Tahoma", 16, 0, FALSE, FALSE, -1);
			pTextOrganic->SetID(TEXTID_Organic);
			m_pWindow->AddElement(pTextOrganic);

			UI::LPIMAGEBOX pImagePosion = std::make_shared<UI::ImageBox>(Rectangle2D(28 + 52 * 1, 456, 22, 22));
			pImagePosion->SetID(IMAGEBOXID_Posion);
			pImagePosion->SetEvent(UI::Event::Build(std::bind(&Window::OnImageBoxMouseMove, this, IMAGEBOXID_Posion)));
			pImagePosion->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Status\\info\\posion.png"));

			m_pWindow->AddElement(pImagePosion);

			UI::LPTEXT pTextPosion = std::make_shared<UI::Text>(Rectangle2D(58 + 52 * 1, 459, 22, 22));

			pTextPosion->SetFont("Tahoma", 16, 0, FALSE, FALSE, -1);
			pTextPosion->SetID(TEXTID_Posion);
			m_pWindow->AddElement(pTextPosion);

			UI::LPIMAGEBOX pImageFire = std::make_shared<UI::ImageBox>(Rectangle2D(28 + 52 * 2, 456, 22, 22));
			pImageFire->SetID(IMAGEBOXID_Fire);
			pImageFire->SetEvent(UI::Event::Build(std::bind(&Window::OnImageBoxMouseMove, this, IMAGEBOXID_Fire)));
			pImageFire->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Status\\info\\fire.png"));

			m_pWindow->AddElement(pImageFire);

			UI::LPTEXT pTextFire = std::make_shared<UI::Text>(Rectangle2D(58 + 52 * 2, 459, 22, 22));

			pTextFire->SetFont("Tahoma", 16, 0, FALSE, FALSE, -1);
			pTextFire->SetID(TEXTID_Fire);

			m_pWindow->AddElement(pTextFire);

			UI::LPIMAGEBOX pImageLightning = std::make_shared<UI::ImageBox>(Rectangle2D(28 + 52 * 3, 456, 22, 22));
			pImageLightning->SetID(IMAGEBOXID_Lightning);
			pImageLightning->SetEvent(UI::Event::Build(std::bind(&Window::OnImageBoxMouseMove, this, IMAGEBOXID_Lightning)));
			pImageLightning->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Status\\info\\lightning.png"));

			m_pWindow->AddElement(pImageLightning);

			UI::LPTEXT pTextLightning = std::make_shared<UI::Text>(Rectangle2D(58 + 52 * 3, 459, 22, 22));

			pTextLightning->SetFont("Tahoma", 16, 0, FALSE, FALSE, -1);
			pTextLightning->SetID(TEXTID_Lightning);
			m_pWindow->AddElement(pTextLightning);

			UI::LPIMAGEBOX pImageFrost = std::make_shared<UI::ImageBox>(Rectangle2D(28 + 52 * 4, 456, 22, 22));
			pImageFrost->SetID(IMAGEBOXID_Frost);
			pImageFrost->SetEvent(UI::Event::Build(std::bind(&Window::OnImageBoxMouseMove, this, IMAGEBOXID_Frost)));
			pImageFrost->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Status\\info\\frost.png"));

			m_pWindow->AddElement(pImageFrost);

			UI::LPTEXT pTextFrost = std::make_shared<UI::Text>(Rectangle2D(58 + 52 * 4, 459, 22, 22));

			pTextFrost->SetFont("Tahoma", 16, 0, FALSE, FALSE, -1);
			pTextFrost->SetID(TEXTID_Frost);
			m_pWindow->AddElement(pTextFrost);

			UI::LPTOOLTIP pTooltip = std::make_shared<UI::ToolTip>(Rectangle2D());
			pTooltip->Init();
			pTooltip->SetFont("Tahoma", 16, -1);
			pTooltip->SetPosition(TOOLTIPPOSITION_Top);
			pTooltip->SetFollowMouse(FALSE);
			pTooltip->SetID(TOOLID_Tip);

			m_pWindow->AddElement(pTooltip);
		}
		void Window::Load()
		{
			/*auto sInfo = lpCurPlayer->m_sInfo;

			auto pImageCharacter = m_pWindow->GetElement<UI::ImageBox>(IMAGEBOXID_Character);

			switch (sInfo.eClass)
			{
			case CHARACTERCLASS_Fighter:
				pImageCharacter->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Status\\Character\\fs.png"));
				break;
			case CHARACTERCLASS_Mechanican:
				pImageCharacter->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Status\\Character\\ms.png"));
				break;
			case CHARACTERCLASS_Archer:
				pImageCharacter->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Status\\Character\\as.png"));
				break;
			case CHARACTERCLASS_Pikenman:
				pImageCharacter->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Status\\Character\\ps.png"));
				break;
			case CHARACTERCLASS_Atalanta:
				pImageCharacter->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Status\\Character\\ata.png"));
				break;
			case CHARACTERCLASS_Knight:
				pImageCharacter->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Status\\Character\\ks.png"));
				break;
			case CHARACTERCLASS_Magician:
				pImageCharacter->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Status\\Character\\mgs.png"));
				break;
			case CHARACTERCLASS_Priestess:
				pImageCharacter->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Status\\Character\\prs.png"));
				break;
			case CHARACTERCLASS_Assassin:
				pImageCharacter->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Status\\Character\\ass.png"));
				break;
			case CHARACTERCLASS_Shaman:
				pImageCharacter->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Status\\Character\\shm.png"));
				break;
			default:
				pImageCharacter->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Status\\Character\\as.png"));
				break;
			}

			auto pTextName = m_pWindow->GetElement<UI::Text>(TEXTID_Name);
			pTextName->SetHighlightText(TRUE);
			pTextName->SetHighlightText("Name");
			pTextName->SetHighlightTextColor(D3DCOLOR_ARGB(255, 245, 250, 190));
			pTextName->SetText(FormatString("%s%s", "Name:", sInfo.strName.c_str()));

			auto pTextTitle = m_pWindow->GetElement<UI::Text>(TEXTID_Title);
			pTextTitle->SetHighlightText(TRUE);
			pTextTitle->SetHighlightText("Title");
			pTextTitle->SetHighlightTextColor(D3DCOLOR_ARGB(255, 245, 250, 190));
			pTextTitle->SetText(FormatString("%s%s", "Title:", ""));

			auto pTextClan = m_pWindow->GetElement<UI::Text>(TEXTID_Clan);
			pTextClan->SetHighlightText(TRUE);
			pTextClan->SetHighlightText("Clan");
			pTextClan->SetHighlightTextColor(D3DCOLOR_ARGB(255, 245, 250, 190));
			pTextClan->SetText(FormatString("%s%s", "Clan:", ""));

			auto pTextLevel = m_pWindow->GetElement<UI::Text>(TEXTID_Level);
			pTextLevel->SetHighlightText(TRUE);
			pTextLevel->SetHighlightText("Level");
			pTextLevel->SetHighlightTextColor(D3DCOLOR_ARGB(255, 245, 250, 190));
			pTextLevel->SetText(FormatString("%s%d", "Level:", sInfo.iLevel));

			auto pTextBarHP = m_pWindow->GetElement<UI::Text>(TEXTID_HP);
			pTextBarHP->SetHorizontalAlign(ALIGN_Center);
			pTextBarHP->SetVerticalAlign(ALIGN_Middle);
			pTextBarHP->SetText(FormatString("%d", sInfo.HP.iMax));

			auto pTextBarMP = m_pWindow->GetElement<UI::Text>(TEXTID_MP);
			pTextBarMP->SetHorizontalAlign(ALIGN_Center);
			pTextBarMP->SetVerticalAlign(ALIGN_Middle);
			pTextBarMP->SetText(FormatString("%d", sInfo.MP.iMax));

			auto pTextBarSP = m_pWindow->GetElement<UI::Text>(TEXTID_SP);
			pTextBarSP->SetHorizontalAlign(ALIGN_Center);
			pTextBarSP->SetVerticalAlign(ALIGN_Middle);
			pTextBarSP->SetText(FormatString("%d", sInfo.SP.iMax));

			auto pCheckBoxFastAdd = m_pWindow->GetElement<UI::CheckBox>(CHECKBOXID_FastAdd);

			sInfo.iStatsPoint ? pCheckBoxFastAdd->Show() : pCheckBoxFastAdd->Hide();

			auto pTextStatusremain = m_pWindow->GetElement<UI::Text>(TEXTID_StatsPoint);

			if (sInfo.iStatsPoint)
			{
				pTextStatusremain->SetText(FormatString("Stats remaining:%d", sInfo.iStatsPoint));
				pTextStatusremain->Show();
			}
			else
			{
				pTextStatusremain->Hide();
			}

			auto pTextBarSTR = m_pWindow->GetElement<UI::Text>(TEXTID_Str);
			pTextBarSTR->SetHorizontalAlign(ALIGN_Center);
			pTextBarSTR->SetVerticalAlign(ALIGN_Middle);
			pTextBarSTR->SetText(FormatString("%d", sInfo.iStrength));

			auto pTextBarSPI = m_pWindow->GetElement<UI::Text>(TEXTID_Spi);
			pTextBarSPI->SetHorizontalAlign(ALIGN_Center);
			pTextBarSPI->SetVerticalAlign(ALIGN_Middle);
			pTextBarSPI->SetText(FormatString("%d", sInfo.iSpirit));

			auto pTextBarTAL = m_pWindow->GetElement<UI::Text>(TEXTID_Tal);
			pTextBarTAL->SetHorizontalAlign(ALIGN_Center);
			pTextBarTAL->SetVerticalAlign(ALIGN_Middle);
			pTextBarTAL->SetText(FormatString("%d", sInfo.iTalent));

			auto pTextBarAGI = m_pWindow->GetElement<UI::Text>(TEXTID_Agi);
			pTextBarAGI->SetHorizontalAlign(ALIGN_Center);
			pTextBarAGI->SetVerticalAlign(ALIGN_Middle);
			pTextBarAGI->SetText(FormatString("%d", sInfo.iAgile));

			auto pTextBarVIT = m_pWindow->GetElement<UI::Text>(TEXTID_Vit);
			pTextBarVIT->SetHorizontalAlign(ALIGN_Center);
			pTextBarVIT->SetVerticalAlign(ALIGN_Middle);
			pTextBarVIT->SetText(FormatString("%d", sInfo.iHealth));

			auto pButtonStr = m_pWindow->GetElement<UI::Button>(BUTTONID_Str);
			auto pButtonSpi = m_pWindow->GetElement<UI::Button>(BUTTONID_Spi);
			auto pButtonTal = m_pWindow->GetElement<UI::Button>(BUTTONID_Tal);
			auto pButtonAgi = m_pWindow->GetElement<UI::Button>(BUTTONID_Agi);
			auto pButtonVit = m_pWindow->GetElement<UI::Button>(BUTTONID_Vit);

			sInfo.iStatsPoint ? pButtonStr->Show() : pButtonStr->Hide();
			sInfo.iStatsPoint ? pButtonSpi->Show() : pButtonSpi->Hide();
			sInfo.iStatsPoint ? pButtonTal->Show() : pButtonTal->Hide();
			sInfo.iStatsPoint ? pButtonAgi->Show() : pButtonAgi->Hide();
			sInfo.iStatsPoint ? pButtonVit->Show() : pButtonVit->Hide();

			auto pList = m_pWindow->GetElement<UI::List>(LISTID_WindowBox);

			auto pWindow = pList->GetWindow(WINDOWID_Box);

			auto pTextAttackPower = pWindow->GetElement<UI::Text>(TEXTID_AttackPower);
			pTextAttackPower->SetText(FormatString("Attack Power:%d-%d", sInfo.sAttackDamage));

			auto pTextAttackRating = pWindow->GetElement<UI::Text>(TEXTID_AttackRating);
			pTextAttackRating->SetText(FormatString("Attack Rating:%d", sInfo.iAttackRating));

			auto pTextDefense = pWindow->GetElement<UI::Text>(TEXTID_Defense);
			pTextDefense->SetText(FormatString("Defense:%d", sInfo.iDefence));

			auto pTextAbsorption = pWindow->GetElement<UI::Text>(TEXTID_Absorption);
			pTextAbsorption->SetText(FormatString("Absorption:%d", sInfo.iAbsorption));

			auto pTextMoveSpeed = pWindow->GetElement<UI::Text>(TEXTID_MoveSpeed);
			pTextMoveSpeed->SetText(FormatString("Movement Speed:%d", sInfo.iMoveSpeed));

			auto pTextCriticalRate = pWindow->GetElement<UI::Text>(TEXTID_Critical);
			pTextCriticalRate->SetText(FormatString("Critical Rate:%d", sInfo.iCriticalHit));

			auto pTextBlock = pWindow->GetElement<UI::Text>(TEXTID_Block);
			pTextBlock->SetText(FormatString("Block:%d", sInfo.iBlock));

			auto pTextEvade = pWindow->GetElement<UI::Text>(TEXTID_Evade);
			pTextEvade->SetText(FormatString("Evade:%d", sInfo.iEvade));

			auto pTextOrganic = m_pWindow->GetElement<UI::Text>(TEXTID_Organic);
			pTextOrganic->SetText(FormatString("%d", sInfo.DefenseResistance[0]));

			auto pTextPosion = m_pWindow->GetElement<UI::Text>(TEXTID_Posion);
			pTextPosion->SetText(FormatString("%d", sInfo.DefenseResistance[5]));

			auto pTextFire = m_pWindow->GetElement<UI::Text>(TEXTID_Fire);
			pTextFire->SetText(FormatString("%d", sInfo.DefenseResistance[2]));

			auto pTextLightning = m_pWindow->GetElement<UI::Text>(TEXTID_Lightning);
			pTextLightning->SetText(FormatString("%d", sInfo.DefenseResistance[4]));

			auto pTextFrost = m_pWindow->GetElement<UI::Text>(TEXTID_Frost);
			pTextFrost->SetText(FormatString("%d", sInfo.DefenseResistance[3]));*/
		}
		void Window::OnClose(UIEventArgs eArgs)
		{
			m_pWindow->Hide();
		}
		void Window::OnUpdateStatus(int iID)
		{

		}
		void Window::OnImageBoxMouseMove(int iID)
		{
			auto pImageBox = m_pWindow->GetElement<UI::ImageBox>(iID);

			if (pImageBox)
			{
				std::string strText = "";

				if (iID == IMAGEBOXID_Organic)
					strText = "Organic";
				else if (iID == IMAGEBOXID_Posion)
					strText = "Posion";
				else if (iID == IMAGEBOXID_Fire)
					strText = "Fire";
				else if (iID == IMAGEBOXID_Lightning)
					strText = "Lightning";
				else if (iID == IMAGEBOXID_Frost)
					strText = "Frost";

				auto pTooltip = m_pWindow->GetElement<UI::ToolTip>(TOOLID_Tip);

				pTooltip->SetLinkObject(pImageBox);
				pTooltip->SetText(strText);
			}
		}
	}
}