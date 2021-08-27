#include "StdAfx.h"
#include "MessageBoxWindow.h"

namespace MESSAGE
{
	namespace BOX
	{
		Window::Window() : CBaseWindow()
		{

		}
		Window::Window(EWindow eID) : CBaseWindow(eID)
		{
			SetWindowLevel(8);
		}
		Window::~Window()
		{
			
		}
		void Window::Init()
		{
			BuildWindow();
			BuildWindowRollDice();

			m_pAutoCloseBar[0] = UI::ImageLoader::LoadImage_("Resources\\UI\\MessageBox\\autoclosebar.png");
			m_pAutoCloseBar[1] = UI::ImageLoader::LoadImage_("Resources\\UI\\MessageBox\\autoclosebar_.png");
			m_pAutoCloseBar[2] = UI::ImageLoader::LoadImage_("Resources\\UI\\MessageBox\\autoclosediv.png");
		}
		void Window::Shutdown()
		{
			Clear();
		}
		void Window::Clear()
		{
			m_pWindowMain ? m_pWindowMain->Clear() : 0;
			m_pWindowRollDice ? m_pWindowRollDice->Clear() : 0;

			for (auto &v : m_pAutoCloseBar)
			{
				CLEARPTR(v);
				UI::ImageLoader::DeleteImage(v);
			}
		}
		void Window::SetEvent(std::function<void(UIEventArgs const &)> const & f)
		{
			m_vMsgBox.clear();
			m_vMsgBox.push_back(f);
		}
		void Window::SetTitle(std::string strText)
		{
			std::transform(strText.begin(), strText.end(), strText.begin(), ::toupper);

			m_pWindow ? m_pWindow->GetElement<UI::BitmapFont>(TEXTID_Title)->SetText(strText) : 0;
		}
		void Window::SetDescription(std::string strText)
		{
			m_pWindow ? m_pWindow->GetElement<UI::Text>(TEXTID_Text)->SetText(strText) : 0;
		}
		void Window::SetAutoClose(int iDuration)
		{
			if (m_pWindow)
			{
				m_iElapsedTime = iDuration;
				m_dwTickTime = TICKCOUNT + (iDuration * 1000);
				m_bAutoClose = TRUE;

				auto pTextAutoClose = m_pWindow->GetElement<UI::Text>(TEXTID_AutoClose);

				if (pTextAutoClose)
				{
					pTextAutoClose->SetTextEx("Automatically closes in %d sec...", m_iElapsedTime);
					pTextAutoClose->Show();
				}
			}
		}
		void Window::Show()
		{
			if (m_pWindow && !m_pWindow->IsOpen())
			{
				m_pWindow->Show();

				m_pLinkElement ? m_pLinkElement->OnLinkObject() : 0;
				MOUSEHANDLER->BlockMouse();
			}
		}
		void Window::AddExtraText(std::string strText, Rectangle2D sBox, BOOL bBold, UI::Color cColor)
		{
			UI::LPTEXT pText = std::make_shared<UI::Text>(strText, sBox, bBold, cColor.Get());
			pText->SetFont("Arial", 14, 0, FALSE, bBold, cColor.Get());
			pText->SetWordWrap(TRUE);
			pText->SetMultiLine(TRUE);
			pText->SetHorizontalAlign(ALIGN_Center);
			pText->SetVerticalAlign(ALIGN_Middle);

			m_pWindow ? m_pWindow->AddElement(pText) : 0;

			m_vExtraElements.push_back(pText);
		}
		void Window::SetBoxType(int iType)
		{
			m_iBoxType = iType;

			m_pWindow ? m_pWindow->GetElement<UI::Text>(TEXTID_AutoClose)->Hide() : 0;

			if (m_iBoxType == BOXTYPEID_YesNo)
			{
				m_pWindow = m_pWindowMain;

				if (m_pWindow)
				{
					m_pWindow->GetElement<UI::Button>(BUTTONID_Yes)->SetActiveImage(UI::ImageLoader::LoadActiveImage("Resources\\UI\\MessageBox\\Btnyes.png", "Resources\\UI\\MessageBox\\Btnyes_.png"));
					m_pWindow->GetElement<UI::Button>(BUTTONID_No)->SetActiveImage(UI::ImageLoader::LoadActiveImage("Resources\\UI\\MessageBox\\Btnno.png", "Resources\\UI\\MessageBox\\Btnno_.png"));
				}
			}
			else if (m_iBoxType == BOXTYPEID_OkCancel)
			{
				m_pWindow = m_pWindowMain;

				if (m_pWindow)
				{
					m_pWindow->GetElement<UI::Button>(BUTTONID_Yes)->SetActiveImage(UI::ImageLoader::LoadActiveImage("Resources\\UI\\MessageBox\\Btnok.png", "Resources\\UI\\MessageBox\\Btnok_.png"));
					m_pWindow->GetElement<UI::Button>(BUTTONID_No)->SetActiveImage(UI::ImageLoader::LoadActiveImage("Resources\\UI\\MessageBox\\Btncancel.png", "Resources\\UI\\MessageBox\\Btncancel_.png"));
				}
			}
			else if (m_iBoxType == BOXTYPEID_RollDice)
			{
				m_pWindow = m_pWindowRollDice;

				if (m_pWindow)
				{
					m_pWindow->GetElement<UI::Button>(BUTTONID_Yes)->Enable();
					m_pWindow->GetElement<UI::Button>(BUTTONID_No)->Enable();
				}
			}
		}
		void Window::Update(float fTime)
		{
			if (m_pWindow && m_pWindow->IsOpen() && m_bAutoClose)
			{
				m_iElapsedTime--;

				auto pTextAutoClose = m_pWindow->GetElement<UI::Text>(TEXTID_AutoClose);
				pTextAutoClose->SetTextEx("Automatically closes in %d sec...", m_iElapsedTime);

				if (m_iElapsedTime <= 0)
					OnNoButtonClick(UIEventArgs{});
			}
		}
		void Window::Render()
		{
			if (m_pWindow && m_pWindow->IsOpen())
			{
				int iBaseX = (GRAPHICENGINE->GetBackWidth() >> 1) - (m_pWindow->GetWidth() >> 1);
				int iBaseY = (GRAPHICENGINE->GetBackHeight() >> 1) - (m_pWindow->GetHeight() >> 1);

				m_pWindow->SetPosition(iBaseX, iBaseY);
				m_pWindow->Render(0, 0, GRAPHICENGINE->GetBackWidth(), GRAPHICENGINE->GetBackHeight(), 0, 0);

				if (m_iBoxType == BOXTYPEID_RollDice)
				{
					if (m_pAutoCloseBar[0] && m_pAutoCloseBar[1] && m_pAutoCloseBar[2])
					{
						UI::ImageRender::Render(m_pAutoCloseBar[0], iBaseX + 122, iBaseY + 87, m_pAutoCloseBar[0]->GetWidth(), m_pAutoCloseBar[0]->GetHeight(), -1);

						int iWidth = ((m_dwTickTime - TICKCOUNT) * m_pAutoCloseBar[1]->GetWidth()) / (MAX_ROLLDICEDROP_TIME * 1000);
						UI::ImageRender::Render(m_pAutoCloseBar[1], iBaseX + 123, iBaseY + 88, iWidth, m_pAutoCloseBar[1]->GetHeight(), iBaseX + 123, 0, -1);

						int iAlpha = ((m_dwTickTime - TICKCOUNT) % 65) + 190;
						UI::ImageRender::Render(m_pAutoCloseBar[2], iBaseX + 122 + iWidth - (m_pAutoCloseBar[2]->GetWidth() >> 2), iBaseY + 86 - (m_pAutoCloseBar[2]->GetHeight() >> 2), m_pAutoCloseBar[2]->GetWidth(), m_pAutoCloseBar[2]->GetHeight(), D3DCOLOR_ARGB(iAlpha, 255, 255, 255));
					}
				}
			}
		}
		BOOL Window::OnKeyPress(class INPUTS::KeyBoard *pcKeyboard)
		{
			if (m_iBoxType == BOXTYPEID_RollDice)
				return FALSE;

			if (m_pWindow && m_pWindow->IsOpen())
			{
				if (pcKeyboard->GetKey() == VK_RETURN)
				{
					OnYesButtonClick(UIEventArgs{});
					return TRUE;
				}
				else if (pcKeyboard->GetKey() == VK_ESCAPE)
				{
					OnNoButtonClick(UIEventArgs{});
					return TRUE;
				}

				if (m_pWindow->OnKeyPress(pcKeyboard))
					return TRUE;
			}

			return FALSE;
		}
		void Window::OnMouseMove(class INPUTS::Mouse *pcMouse)
		{
			m_pWindow ? m_pWindow->OnMouseMove(pcMouse, 0, 0, GRAPHICENGINE->GetBackWidth(), GRAPHICENGINE->GetBackHeight(), 0, 0) : 0;
		}
		BOOL Window::OnMouseClick(class INPUTS::Mouse *pcMouse)
		{
			return m_pWindow ? m_pWindow->OnMouseClick(pcMouse, 0, 0, GRAPHICENGINE->GetBackWidth(), GRAPHICENGINE->GetBackHeight(), 0, 0) : FALSE;
		}
		void Window::DelExtraElement()
		{
			for (auto &v : m_vExtraElements)
			{
				m_pWindow ? m_pWindow->DelElement(v) : 0;
			}

			m_vExtraElements.clear();
		}
		void Window::OnEvent()
		{
			if (m_vMsgBox.size() > 0)
				m_vMsgBox[0](UIEventArgs{});

			m_vMsgBox.clear();
		}
		void Window::OnYesButtonClick(UIEventArgs eArgs)
		{
			MOUSEHANDLER->UnblockMouse();

			m_bType = TRUE;

			m_pLinkElement ? m_pLinkElement->UnLinkObject() : 0;

			OnEvent();

			m_bAutoClose = FALSE;
			m_iElapsedTime = 0;

			DelExtraElement();

			m_pWindow ? m_pWindow->Hide() : 0;
		}
		void Window::OnNoButtonClick(UIEventArgs eArgs)
		{
			MOUSEHANDLER->UnblockMouse();

			m_bType = FALSE;

			m_pLinkElement ? m_pLinkElement->UnLinkObject() : 0;

			OnEvent();

			m_bAutoClose = FALSE;
			m_iElapsedTime = 0;

			DelExtraElement();

			m_pWindow ? m_pWindow->Hide() : 0;
		}
		void Window::OnRollButtonClick(UIEventArgs eArgs)
		{
			OnEvent();

			m_pWindowRollDice->GetElement<UI::Button>(BUTTONID_Yes)->Disable();
			m_pWindowRollDice->GetElement<UI::Button>(BUTTONID_No)->Disable();

			m_bType = TRUE;
		}
		void Window::OnPassButtonClick(UIEventArgs eArgs)
		{
			OnEvent();

			m_pWindowRollDice->GetElement<UI::Button>(BUTTONID_Yes)->Disable();
			m_pWindowRollDice->GetElement<UI::Button>(BUTTONID_No)->Disable();

			m_bType = FALSE;
		}
		void Window::BuildWindow()
		{
			m_pWindowMain = std::make_shared<UI::Window>(Rectangle2D(0, 0, 230, 161));

			m_pWindowMain->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\MessageBox\\Background_normal.png"));
			m_pWindowMain->SetID(WINDOWID_Main);

			auto pButtonYes = std::make_shared<UI::Button>(Rectangle2D(26, 116, 88, 35));
			pButtonYes->SetID(BUTTONID_Yes);
			pButtonYes->SetEvent(UI::Event::Build(std::bind(&Window::OnYesButtonClick, this, std::placeholders::_1)));
			pButtonYes->SetActiveImage(UI::ImageLoader::LoadActiveImage("Resources\\UI\\MessageBox\\Btnyes.png", "Resources\\UI\\MessageBox\\Btnyes_.png"));
			m_pWindowMain->AddElement(pButtonYes);

			auto pButtonNo = std::make_shared<UI::Button>(Rectangle2D(115, 116, 88, 35));
			pButtonNo->SetID(BUTTONID_No);
			pButtonNo->SetEvent(UI::Event::Build(std::bind(&Window::OnNoButtonClick, this, std::placeholders::_1)));
			pButtonNo->SetActiveImage(UI::ImageLoader::LoadActiveImage("Resources\\UI\\MessageBox\\Btnno.png", "Resources\\UI\\MessageBox\\Btnno_.png"));
			m_pWindowMain->AddElement(pButtonNo);

			//Text
			UI::LPTEXT pTextDescription = std::make_shared<UI::Text>(Rectangle2D(35, 50, 160, 0));
			pTextDescription->SetID(TEXTID_Text);
			pTextDescription->SetFont("Noto Sans", 16, 0, FALSE, FALSE, D3DCOLOR_XRGB(228, 218, 212));
			pTextDescription->SetText("");
			pTextDescription->SetDropdownShadow(TRUE);
			pTextDescription->SetHorizontalAlign(ALIGN_Center);
			pTextDescription->SetMultiLine(TRUE);
			pTextDescription->SetDropdownColor(D3DCOLOR_ARGB(100, 0, 0, 0));
			pTextDescription->SetWordWrap(TRUE);
			m_pWindowMain->AddElement(pTextDescription);

			UI::LPTEXT pTextAutoClose = std::make_shared<UI::Text>(Rectangle2D(10, 95, 210, 0));
			pTextAutoClose->SetID(TEXTID_AutoClose);
			pTextAutoClose->SetFont("Arial", 14, 0, FALSE, FALSE, D3DCOLOR_XRGB(180, 180, 180));
			pTextAutoClose->SetText("");
			pTextAutoClose->SetHorizontalAlign(ALIGN_Center);
			m_pWindowMain->AddElement(pTextAutoClose);

			UI::LPBITMAPFONT pTextTitle = std::make_shared<UI::BitmapFont>(Rectangle2D(12, 16, 207, 0));
			pTextTitle->SetID(TEXTID_Title);
			pTextTitle->SetHorizontalAlign(ALIGN_Center);
			pTextTitle->ReadFontData("Resources\\Fonts\\Messagebox.dat");
			pTextTitle->SetFontImage(UI::ImageLoader::LoadImage_("Resources\\Fonts\\Messagebox.png"));
			m_pWindowMain->AddElement(pTextTitle);
			m_pWindowMain->Hide();
		}
		void Window::BuildWindowRollDice()
		{
			m_pWindowRollDice = std::make_shared<UI::Window>(Rectangle2D(0, 0, 295, 161));

			m_pWindowRollDice->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\MessageBox\\Background_diceroll.png"));
			m_pWindowRollDice->SetID(WINDOWID_RollDice);

			UI::LPIMAGEBOX pRollDiceIcon = std::make_shared<UI::ImageBox>(Rectangle2D(128, 12, 39, 30));
			pRollDiceIcon->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\diceroll\\icon.png"));
			m_pWindowRollDice->AddElement(pRollDiceIcon);

			UI::LPBUTTON pButtonYes = std::make_shared<UI::Button>(Rectangle2D(109, 116, 88, 35));
			pButtonYes->SetID(BUTTONID_Yes);
			pButtonYes->SetActiveImage(UI::ImageLoader::LoadActiveImage("Resources\\UI\\MessageBox\\Btnroll.png", "Resources\\UI\\MessageBox\\Btnroll_.png"));
			pButtonYes->SetDisabledImage(UI::ImageLoader::LoadImage_("Resources\\UI\\MessageBox\\Btnroll.png"));
			m_pWindowRollDice->AddElement(pButtonYes);

			UI::LPBUTTON pButtonNo = std::make_shared<UI::Button>(Rectangle2D(198, 116, 88, 35));
			pButtonNo->SetID(BUTTONID_No);
			pButtonNo->SetActiveImage(UI::ImageLoader::LoadActiveImage("game\\images\\UI\\messagebox\\btnpass.png", "game\\images\\UI\\messagebox\\btnpass_.png"));
			pButtonNo->SetDisabledImage(UI::ImageLoader::LoadImage_("Resources\\UI\\MessageBox\\Btnpass.png"));
			m_pWindowRollDice->AddElement(pButtonNo);

			UI::LPTEXT pTextDescription = std::make_shared<UI::Text>(Rectangle2D(118, 45, 160, 44));
			pTextDescription->SetID(TEXTID_Text);
			pTextDescription->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_XRGB(228, 218, 212));
			pTextDescription->SetText("");
			pTextDescription->SetDropdownShadow(TRUE);
			pTextDescription->SetHorizontalAlign(ALIGN_Center);
			pTextDescription->SetMultiLine(TRUE);
			pTextDescription->SetDropdownColor(D3DCOLOR_ARGB(100, 0, 0, 0));
			pTextDescription->SetWordWrap(TRUE);
			m_pWindowRollDice->AddElement(pTextDescription);

			UI::LPTEXT pTextAutoClose = std::make_shared<UI::Text>(Rectangle2D(112, 100, 170, 60));
			pTextAutoClose->SetID(TEXTID_AutoClose);
			pTextAutoClose->SetFont("Arial", 14, 0, FALSE, FALSE, D3DCOLOR_XRGB(180, 180, 180));
			pTextAutoClose->SetText("");
			pTextAutoClose->SetHorizontalAlign(ALIGN_Center);
			m_pWindowRollDice->AddElement(pTextAutoClose);

			UI::LPBITMAPFONT pTextTitle = std::make_shared<UI::BitmapFont>(Rectangle2D(176, 22, 207, 0));
			pTextTitle->SetID(TEXTID_Title);
			pTextTitle->ReadFontData("Resources\\Fonts\\Messagebox.dat");
			pTextTitle->SetFontImage(UI::ImageLoader::LoadImage_("Resources\\Fonts\\Messagebox.png"));
			m_pWindowRollDice->AddElement(pTextTitle);
			m_pWindowRollDice->Hide();
		}
	}
}