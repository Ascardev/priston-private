#include "StdAfx.h"
#include "ChatWindow.h"

namespace CHAT
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

		m_sFriendlyCommands.insert(FriendlyCommands::value_type("/sweat", "e1"));
		m_sFriendlyCommands.insert(FriendlyCommands::value_type("/love", "e2"));
		m_sFriendlyCommands.insert(FriendlyCommands::value_type("/angry", "e3"));
		m_sFriendlyCommands.insert(FriendlyCommands::value_type("/bigeye", "e4"));
		m_sFriendlyCommands.insert(FriendlyCommands::value_type("/sad", "e5"));
		m_sFriendlyCommands.insert(FriendlyCommands::value_type("/cry", "e6"));
		m_sFriendlyCommands.insert(FriendlyCommands::value_type("/ops", "e7"));
		m_sFriendlyCommands.insert(FriendlyCommands::value_type("/nerd", "e8"));
		m_sFriendlyCommands.insert(FriendlyCommands::value_type("/craving", "e9"));
		m_sFriendlyCommands.insert(FriendlyCommands::value_type("/hurt", "e10"));
		m_sFriendlyCommands.insert(FriendlyCommands::value_type("/silence", "e11"));
		m_sFriendlyCommands.insert(FriendlyCommands::value_type("/crazy", "e12"));
		m_sFriendlyCommands.insert(FriendlyCommands::value_type("/hello", "e13"));
		m_sFriendlyCommands.insert(FriendlyCommands::value_type("/tired", "e14"));
		m_sFriendlyCommands.insert(FriendlyCommands::value_type("/shame", "e15"));
		m_sFriendlyCommands.insert(FriendlyCommands::value_type("/brokeheart", "e16"));
		m_sFriendlyCommands.insert(FriendlyCommands::value_type("/abused", "e17"));
		m_sFriendlyCommands.insert(FriendlyCommands::value_type("/kappa", "e18"));
		m_sFriendlyCommands.insert(FriendlyCommands::value_type("/kappapride", "e19"));
		m_sFriendlyCommands.insert(FriendlyCommands::value_type("/pogchamp", "e20"));
	}
	void Window::Shutdown()
	{
		m_pcWindow->Clear();
	}
	void Window::Render()
	{
		m_pcWindow->Render(0, 0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);

		CheckCollideWindow(FALSE);
	}
	void Window::Update(float fTime)
	{
		//CheckCollideWindow(FALSE);
	}
	void Window::OnMouseMove(class INPUTS::Mouse *pcMouse)
	{
		m_pcWindow->OnMouseMove(pcMouse, 0, 0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);
	}
	BOOL Window::OnMouseClick(class INPUTS::Mouse *pcMouse)
	{
		auto pcInputField = m_pcWindow->GetElement<UI::InputField>(INPUTFIELDID_Message);

		if (pcInputField)
		{
			if (!pcInputField->IsHover() && pcInputField->IsSelected() && !pcInputField->GetText().length())
			{
				pcInputField->SetSelected(FALSE);
				//pcInputField->SetSelect(FALSE);
			}
		}

		return m_pcWindow->OnMouseClick(pcMouse, 0, 0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0) ? TRUE : FALSE;
	}
	BOOL Window::OnMouseScroll(class INPUTS::Mouse *pcMouse)
	{
		return m_pcWindow->OnMouseScroll(pcMouse, 0, 0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0) ? TRUE : FALSE;
	}
	BOOL Window::OnKeyPress(class INPUTS::KeyBoard *pcKeyboard)
	{
		if (pcKeyboard->GetEvent() == KeyDown && pcKeyboard->GetKey() == VK_ESCAPE && !pcKeyboard->IsKeyDown(VK_SHIFT) && m_pcWindow->IsOpen())
		{
			auto pInputField = m_pcWindow->GetElement<UI::InputField>(INPUTFIELDID_Message);

			if (pInputField)
			{
				pInputField->SetSelected(FALSE);
				pInputField->ClearInput();
			}

			m_pcWindow->Hide();
			return TRUE;
		}
		if (pcKeyboard->GetEvent() == KeyDown && pcKeyboard->GetKey() == VK_RETURN && !m_pcWindow->IsOpen() && !MESSAGEBOX->IsOpen())
		{
			OnEnableChatBox();
			m_pcWindow->Show();
			CGameCore::SetFocus(this);
			return TRUE;
		}
		if (pcKeyboard->GetEvent() == KeyDown && pcKeyboard->GetKey() == VK_RETURN && !IsInputFieldActive() && !MESSAGEBOX->IsOpen())
		{
			OnEnableChatBox();
			return TRUE;
		}
		if (pcKeyboard->GetEvent() == KeyDown && pcKeyboard->GetKey() == VK_TAB && IsInputFieldActive())
		{
			auto pInputField = m_pcWindow->GetElement<UI::InputField>(INPUTFIELDID_Message);
			if (pInputField)
			{
				pInputField->ClearInput();
				pInputField->AddInput("/CLAN> ");
			}
			return TRUE;
		}
		if (pcKeyboard->GetEvent() == KeyDown && pcKeyboard->GetKey() == VK_UP && IsInputFieldActive())
		{
			auto pInputField = m_pcWindow->GetElement<UI::InputField>(INPUTFIELDID_Message);
			if (pInputField)
			{
				pInputField->ClearInput();
				pInputField->AddInput(GetSaveCommand(TRUE));
			}
			return TRUE;
		}
		if (pcKeyboard->GetEvent() == KeyDown && pcKeyboard->GetKey() == VK_DOWN && IsInputFieldActive())
		{
			auto pInputField = m_pcWindow->GetElement<UI::InputField>(INPUTFIELDID_Message);
			if (pInputField)
			{
				pInputField->ClearInput();
				pInputField->AddInput(GetSaveCommand(FALSE));
			}
			return TRUE;
		}
		if (pcKeyboard->GetEvent() == KeyDown && pcKeyboard->GetKey() == VK_PRIOR && IsInputFieldActive())
		{
			for (size_t i = 0; i < 6; i++)
			{
				auto pListChat = m_pcWindow->GetElement<UI::List>(LISTID_ChatAll + i);
				if (pListChat)
				{
					if (pListChat->IsOpen())
					{
						auto pScroll = pListChat->GetScrollBar();
						if (pScroll)
						{
							int iPercent = pScroll->GetPercent() - 5;
							if (iPercent < 0)
								iPercent = 0;

							pScroll->SetPercent(iPercent);
						}
						break;
					}
				}
			}

			return TRUE;
		}
		if (pcKeyboard->GetEvent() == KeyDown && pcKeyboard->GetKey() == VK_NEXT && IsInputFieldActive())
		{
			for (size_t i = 0; i < 6; i++)
			{
				auto pListChat = m_pcWindow->GetElement<UI::List>(LISTID_ChatAll + i);
				if (pListChat)
				{
					if (pListChat->IsOpen())
					{
						auto pScroll = pListChat->GetScrollBar();
						if (pScroll)
						{
							int iPercent = pScroll->GetPercent() + 5;
							if (iPercent > 100)
								iPercent = 100;

							pScroll->SetPercent(iPercent);
						}
						break;
					}
				}
			}

			return TRUE;
		}
		if (pcKeyboard->GetEvent() == KeyDown && pcKeyboard->IsKeyDown(VK_CONTROL) && (pcKeyboard->GetKey() >= VK_F1 && pcKeyboard->GetKey() <= VK_F10))
		{
			char * pszMacroText = SETTINGHANDLE->Get().szMacro[(pcKeyboard->GetKey() & 0x0F)];

			if (pszMacroText[0] != NULL)
			{
				OnEnableChatBox();
				auto pInputField = m_pcWindow->GetElement<UI::InputField>(INPUTFIELDID_Message);
				if (pInputField)
					pInputField->AddInput(SETTINGHANDLE->Get().szMacro[(pcKeyboard->GetKey() & 0x0F)]);

				m_pcWindow->Show();
				return TRUE;
			}
		}
		if (m_pcWindow->OnKeyPress(pcKeyboard))
			return TRUE;

		return FALSE;
	}
	BOOL Window::OnKeyChar(class INPUTS::KeyBoard *pcKeyboard)
	{
		return m_pcWindow->OnKeyChar(pcKeyboard);
	}
	void Window::OnResolutionChanged()
	{
		m_pcWindow->SetPosition(4, RESOLUTION_HEIGHT - m_pcWindow->GetHeight() - 4);

		CheckCollideWindow(TRUE);
	}
	BOOL Window::IsInputFieldActive()
	{
		auto pInputField = m_pcWindow->GetElement<UI::InputField>(INPUTFIELDID_Message);

		return pInputField ? pInputField->IsSelected() : FALSE;
	}
	void Window::SetInputFieldText(std::string strText)
	{
		auto pInputField = m_pcWindow->GetElement<UI::InputField>(INPUTFIELDID_Message);

		pInputField ? pInputField->AddInput(strText) : 0;
	}
	void Window::BuidWindow()
	{
		m_pcWindow = std::make_shared<UI::Window>(Rectangle2D(0, 0, 295, 218));
		m_pcWindow->SetPosition(4, RESOLUTION_HEIGHT - m_pcWindow->GetHeight() - 4);

		m_pcWindow->SetMoveBox(Rectangle2D(0, 0, m_pcWindow->GetWidth() - 15, m_pcWindow->GetHeight() - 40));
		m_pcWindow->SetCanMove(!SETTINGHANDLE->Get().bLockUI);

		m_pcWindow->SetColorBackground(UI::Color(70, 0, 0, 0));

		UI::LPIMAGEBOX pImageChatBoxBar = std::make_shared<UI::ImageBox>(Rectangle2D(0, 66, 295, 3));
		pImageChatBoxBar->SetID(IMAGEID_ChatBoxBar);
		pImageChatBoxBar->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Chatbox\\chatbar.png"));
		m_pcWindow->AddElement(pImageChatBoxBar);

		for (size_t i = 0; i < 6; i++)
		{
			UI::LPLIST pListChat = std::make_shared<UI::List>(Rectangle2D(0, 74, 280, 100));
			pListChat->SetID(LISTID_ChatAll + i);
			pListChat->MakeScrollBar(Rectangle2D(285, 0, 6, 105), "Resources\\UI\\Scroll\\barbg_v.png", "Resources\\UI\\Scroll\\icon_2.png");
			pListChat->SetForceDown(TRUE);
			pListChat->SetScrollFirst(TRUE);

			pListChat->GetID() != LISTID_ChatAll ? pListChat->Hide() : 0;

			m_iTabID = CHATBOXTABID_All;

			m_pcWindow->AddElement(pListChat);
		}

		UI::LPLIST pListChatNotice = std::make_shared<UI::List>(Rectangle2D(0, 2, 280, 62));
		pListChatNotice->SetID(LISTID_ChatNotice);
		pListChatNotice->MakeScrollBar(Rectangle2D(285, 2, 6, 54), "Resources\\UI\\Scroll\\barbg_v.png", "Resources\\UI\\Scroll\\icon_2.png");
		pListChatNotice->SetForceDown(TRUE);
		m_pcWindow->AddElement(pListChatNotice);

		UI::LPGROUP p = std::make_shared<UI::Group>();
		m_pcWindow->AddElement(p);

		//Chat Tabs

		UI::LPGROUP pGroupTabs = std::make_shared<UI::Group>();
		m_pcWindow->AddElement(pGroupTabs);

		int iBaseX = 3;
		int iBaseY = 177;

		UI::LPBUTTON pButtonTabAll = std::make_shared<UI::Button>(Rectangle2D(iBaseX, iBaseY, 43, 15));
		pButtonTabAll->SetGroup(pGroupTabs);
		pButtonTabAll->SetID(BUTTONID_TabAll);
		pButtonTabAll->SetActiveImage(UI::ImageLoader::LoadActiveImage("Resources\\UI\\Chatbox\\all.png", "Resources\\UI\\Chatbox\\all_.png"));
		pButtonTabAll->SetEvent(UI::Event::Build(std::bind(&Window::OnSelectChatBoxTab, this, pButtonTabAll->GetID())));
		pButtonTabAll->SetAnimation(TRUE);
		pButtonTabAll->SetSelect(TRUE);
		pButtonTabAll->SetSelected(TRUE);
		m_pcWindow->AddElement(pButtonTabAll);

		UI::LPBUTTON pButtonTabClan = std::make_shared<UI::Button>(Rectangle2D(iBaseX + 45, iBaseY, 43, 15));
		pButtonTabClan->SetGroup(pGroupTabs);
		pButtonTabClan->SetID(BUTTONID_TabClan);
		pButtonTabClan->SetActiveImage(UI::ImageLoader::LoadActiveImage("Resources\\UI\\Chatbox\\clan.png", "Resources\\UI\\Chatbox\\clan_.png"));
		pButtonTabClan->SetEvent(UI::Event::Build(std::bind(&Window::OnSelectChatBoxTab, this, pButtonTabClan->GetID())));
		pButtonTabClan->SetAnimation(TRUE);
		pButtonTabClan->SetSelect(TRUE);
		m_pcWindow->AddElement(pButtonTabClan);

		UI::LPBUTTON pButtonTabParty = std::make_shared<UI::Button>(Rectangle2D(iBaseX + 90, iBaseY, 43, 15));
		pButtonTabParty->SetGroup(pGroupTabs);
		pButtonTabParty->SetID(BUTTONID_TabParty);
		pButtonTabParty->SetActiveImage(UI::ImageLoader::LoadActiveImage("Resources\\UI\\Chatbox\\party.png", "Resources\\UI\\Chatbox\\party_.png"));
		pButtonTabParty->SetEvent(UI::Event::Build(std::bind(&Window::OnSelectChatBoxTab, this, pButtonTabParty->GetID())));
		pButtonTabParty->SetAnimation(TRUE);
		pButtonTabParty->SetSelect(TRUE);
		m_pcWindow->AddElement(pButtonTabParty);

		UI::LPBUTTON pButtonTabRaid = std::make_shared<UI::Button>(Rectangle2D(iBaseX + 135, iBaseY, 43, 15));
		pButtonTabRaid->SetGroup(pGroupTabs);
		pButtonTabRaid->SetID(BUTTONID_TabRaid);
		pButtonTabRaid->SetActiveImage(UI::ImageLoader::LoadActiveImage("Resources\\UI\\Chatbox\\raid.png", "Resources\\UI\\Chatbox\\raid_.png"));
		pButtonTabRaid->SetEvent(UI::Event::Build(std::bind(&Window::OnSelectChatBoxTab, this, pButtonTabRaid->GetID())));
		pButtonTabRaid->SetAnimation(TRUE);
		pButtonTabRaid->SetSelect(TRUE);
		m_pcWindow->AddElement(pButtonTabRaid);

		UI::LPBUTTON pButtonTabTrade = std::make_shared<UI::Button>(Rectangle2D(iBaseX + 180, iBaseY, 43, 15));
		pButtonTabTrade->SetGroup(pGroupTabs);
		pButtonTabTrade->SetID(BUTTONID_TabTrade);
		pButtonTabTrade->SetActiveImage(UI::ImageLoader::LoadActiveImage("Resources\\UI\\Chatbox\\trade.png", "Resources\\UI\\Chatbox\\trade_.png"));
		pButtonTabTrade->SetEvent(UI::Event::Build(std::bind(&Window::OnSelectChatBoxTab, this, pButtonTabTrade->GetID())));
		pButtonTabTrade->SetAnimation(TRUE);
		pButtonTabTrade->SetSelect(TRUE);
		m_pcWindow->AddElement(pButtonTabTrade);

		UI::LPBUTTON pButtonTabPM = std::make_shared<UI::Button>(Rectangle2D(iBaseX + 225, iBaseY, 43, 15));
		pButtonTabPM->SetGroup(pGroupTabs);
		pButtonTabPM->SetID(BUTTONID_TabPM);
		pButtonTabPM->SetActiveImage(UI::ImageLoader::LoadActiveImage("Resources\\UI\\Chatbox\\pm.png", "Resources\\UI\\Chatbox\\pm_.png"));
		pButtonTabPM->SetEvent(UI::Event::Build(std::bind(&Window::OnSelectChatBoxTab, this, pButtonTabPM->GetID())));
		pButtonTabPM->SetAnimation(TRUE);
		pButtonTabPM->SetSelect(TRUE);
		m_pcWindow->AddElement(pButtonTabPM);

		UI::LPINPUTFIELD pInputMessage = std::make_shared<UI::InputField>(Rectangle2D(0, 195, 270, 23));
		pInputMessage->SetID(INPUTFIELDID_Message);
		pInputMessage->SetGroup(p);
		pInputMessage->SetFont("Noto Sans", 16, 0, FALSE, FALSE, -1);
		pInputMessage->SetText("");
		pInputMessage->SetSelect(TRUE);
		pInputMessage->SetMaxLength(MAX_CHATLENGTH);
		pInputMessage->SetTextAlign(EALIGN::ALIGN_Left, EALIGN::ALIGN_Middle);
		pInputMessage->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Chatbox\\input.png"));
		pInputMessage->BindActionKeyboard(UI::ActionKeyboard(VK_RETURN, UI::Event::Build(std::bind(&Window::OnEnterKeyPressed, this, std::placeholders::_1))));
		m_pcWindow->AddElement(pInputMessage);

		UI::LPBUTTON pButtonSendMessage = std::make_shared<UI::Button>(Rectangle2D(270, 195, 25, 23));
		pButtonSendMessage->SetID(BUTTONID_SendMessage);
		pButtonSendMessage->SetActiveImage(UI::ImageLoader::LoadActiveImage("Resources\\UI\\Chatbox\\send.png", "Resources\\UI\\Chatbox\\send_.png"));
		pButtonSendMessage->SetEvent(UI::Event::Build(std::bind(&Window::OnEnterKeyPressed, this, std::placeholders::_1)));
		pButtonSendMessage->SetSelect(TRUE);
		m_pcWindow->AddElement(pButtonSendMessage);
	}
	void Window::OnSelectChatBoxTab(int iID)
	{
		for (size_t i = 0; i < 6; i++)
		{
			auto pListChat = m_pcWindow->GetElement<UI::List>(LISTID_ChatAll + i);
			if (pListChat)
			{
				pListChat->Hide();

				auto pScroll = pListChat->GetScrollBar();
				if (pScroll)
					pScroll->SetPercent(100);
			}
		}

		auto pListChat = m_pcWindow->GetElement<UI::List>(LISTID_ChatAll + (iID - BUTTONID_TabAll));
		if (pListChat)
		{
			m_iTabID = iID - BUTTONID_TabAll;
			pListChat->Show();
		}
	}
	void Window::OnEnableChatBox()
	{
		auto pInputField = m_pcWindow->GetElement<UI::InputField>(INPUTFIELDID_Message);

		if (pInputField)
		{
			pInputField->SetSelected(TRUE);
			pInputField->SetSelect(TRUE);
			pInputField->ClearInput();
		}
	}
	void Window::OnEnterKeyPressed(UIEventArgs eArgs)
	{
		auto pInputField = m_pcWindow->GetElement<UI::InputField>(INPUTFIELDID_Message);

		if (pInputField)
		{
			if (pInputField->GetText().length() > 0)
			{
				AddSaveCommand(pInputField->GetText());
				SendMessageChat(pInputField->GetText());

				//PM?
				if ((pInputField->GetText().length() > 2) && (pInputField->GetText()[0] == '/') && ((pInputField->GetText()[1] == ':') || (pInputField->GetText()[1] == ';')))
				{
					//Set Name
					if (pInputField->GetText().find(' ') != std::string::npos)
					{
						BOOL bAddBack = (pInputField->GetText().find(' ') + 1) == pInputField->GetText().length() ? FALSE : TRUE;

						std::string str = pInputField->GetText().substr(0, pInputField->GetText().find(' ') + 1);

						//Add it back
						pInputField->ClearInput();
						if (bAddBack)
							pInputField->AddInput(str);

						return;
					}
				}

				if ((pInputField->GetText().length() > 7) && (pInputField->GetText()[0] == '/' && pInputField->GetText()[5] == '>') && pInputField->GetText().find("/CLAN>") != std::string::npos)
				{
					pInputField->ClearInput();
					pInputField->AddInput("/CLAN> ");
					return;
				}
			}
			else
				pInputField->SetSelected(FALSE);

			pInputField->ClearInput();
		}
	}
	void Window::AddMessage(std::string strMessage, EChatColor eChatColor, std::string strLighText)
	{
		if (!m_pcWindow)
			return;

		std::vector<UI::LPLIST> vListToAdd;

		if (eChatColor != CHATCOLOR_Notice)
			vListToAdd.push_back(m_pcWindow->GetElement<UI::List>(LISTID_ChatAll));
		else if (eChatColor == CHATCOLOR_Notice)
			vListToAdd.push_back(m_pcWindow->GetElement<UI::List>(LISTID_ChatNotice));

		if (eChatColor == CHATCOLOR_Party)
			vListToAdd.push_back(m_pcWindow->GetElement<UI::List>(LISTID_ChatParty));
		else if (eChatColor == CHATCOLOR_Trade)
			vListToAdd.push_back(m_pcWindow->GetElement<UI::List>(LISTID_ChatTrade));
		else if (eChatColor == CHATCOLOR_Clan || eChatColor == CHATCOLOR_ClanLeader)
			vListToAdd.push_back(m_pcWindow->GetElement<UI::List>(LISTID_ChatClan));
		else if (eChatColor == CHATCOLOR_Whisper || eChatColor == CHATCOLOR_Blue || eChatColor == CHATCOLOR_Error)
			vListToAdd.push_back(m_pcWindow->GetElement<UI::List>(LISTID_ChatPM));
		else if (eChatColor == CHATCOLOR_Raid)
			vListToAdd.push_back(m_pcWindow->GetElement<UI::List>(LISTID_ChatRaid));

		if (vListToAdd.size() > 0)
		{
			for (auto &v : vListToAdd)
			{
				if (v)
				{
					UI::LPWINDOW pBaseWindow = std::make_shared <UI::Window>(Rectangle2D(5, 0, 275, 0));
					UI::LPTEXT pTextMessage = std::make_shared<UI::Text>(Rectangle2D(0, 0, 0, 0));

					if (!strLighText.empty())
					{
						pTextMessage->SetHighlightText(TRUE);
						pTextMessage->SetHighlightText(strLighText);
						pTextMessage->SetHighlightTextColor(D3DCOLOR_XRGB(100, 255, 50));
					}

					pTextMessage->SetFont("Noto Sans", 16, 0, FALSE, FALSE, -1);
					pTextMessage->SetColor(GetMessageColorFromType(eChatColor));

					pTextMessage->SetDropdownShadow(TRUE);
					pTextMessage->SetDropdownColor(UI::Color(150, 0, 0, 0).Get());
					pTextMessage->SetMultiLine(TRUE);
					pTextMessage->SetMaxTextWidth(275);
					pTextMessage->SetText(strMessage);
					pTextMessage->SetNoClip(TRUE);
					pBaseWindow->SetBox(Rectangle2D(5, 0, 275, pTextMessage->GetHeightText()));

					pBaseWindow->AddElement(pTextMessage);

					v->AddWindow(pBaseWindow);

					//Analyze
					if (eChatColor == CHATCOLOR_Blue)
					{
						AddRecentPlayer(strMessage);
					}

					if (v->GetCountItemsList() > MAX_CHATTEXTLIST)
					{
						//Get Window
						auto pTextWindow = v->GetWindowList()[0];

						//Old Position
						int iHeight = pTextWindow->GetHeight();

						//Clear and delete it
						CLEARPTR(pTextWindow);
						RESETPTR(pTextWindow);

						//Clear window in the vector
						v->GetWindowList().pop_front();
					}
				}
			}
		}
	}
	DWORD Window::GetMessageColorFromType(EChatColor eType)
	{
		switch (eType)
		{
		case CHATCOLOR_Error:
			return D3DCOLOR_ARGB(255, 255, 128, 96);
		case CHATCOLOR_Whisper:
			return D3DCOLOR_ARGB(255, 150, 190, 255);
		case CHATCOLOR_Blue:
			return D3DCOLOR_ARGB(255, 150, 190, 255);
		case CHATCOLOR_Global:
			return D3DCOLOR_ARGB(255, 230, 160, 255);
		case CHATCOLOR_Party:
			return D3DCOLOR_ARGB(255, 200, 255, 0);
		case CHATCOLOR_Clan:
			return D3DCOLOR_ARGB(255, 255, 255, 80);
		case CHATCOLOR_Trade:
			return D3DCOLOR_ARGB(255, 200, 255, 255);
		case CHATCOLOR_Notice:
			return D3DCOLOR_ARGB(255, 200, 128, 128);
		case CHATCOLOR_ClanLeader:
			return D3DCOLOR_ARGB(255, 255, 180, 70);
		case CHATCOLOR_Normal:
			return D3DCOLOR_ARGB(255, 255, 255, 128);
		case CHATCOLOR_Raid:
			return D3DCOLOR_ARGB(255, 40, 240, 230);
		}

		return D3DCOLOR_XRGB(255, 255, 255);
	}
	void Window::SendMessageChat(std::string strMessage)
	{
		if (strMessage.size() > 0)
		{
			BOOL bSendToLoginServer = FALSE;

			std::string strEmote = strMessage;
			BOOL bEmote = OnEmoteCommand(strEmote);

			if (m_iTabID == CHATBOXTABID_All)
			{
				if (bEmote)
				{
					AddMessage(FormatString("%s: %s", lpCurPlayer->sCharacterData.szName, strMessage.c_str()), CHATCOLOR_Normal);
					CHATGAMEHANDLE->SendChat(FALSE, strEmote.c_str());
					return;
				}
			}

			BOOL iRetChat = CHATGAMEHANDLE->AnalyzeChat((char*)strMessage.c_str());

			BOOL bContinue = TRUE;

			if (strMessage[0] == '/' || strMessage[0] == '@' || strMessage[0] == '#' || strMessage[0] == '$')
			{
				bContinue = FALSE;

				if (bEmote)
					bContinue = TRUE;

				if (strMessage[0] == '/' && (strMessage[1] == ';' || strMessage[1] == ':'))
				{
					strMessage = trim(strMessage);
					bSendToLoginServer = TRUE;
				}
				else if (strMessage.size() > 1 && strMessage[1] == '!')
					bSendToLoginServer = TRUE;
				else if ((strMessage.compare(0, 7, "/TRADE>") == 0 && strMessage.length() > 8) || (strMessage[0] == '$' && strMessage.length() > 2))
				{
					if (strMessage[0] == '$')
					{
						strMessage.erase(0, 1);
						strMessage.insert(0, "/TRADE>");
					}

					bSendToLoginServer = TRUE;
				}
			}

			if (bContinue)
			{
				switch (m_iTabID)
				{
				case CHATBOXTABID_All:
				case CHATBOXTABID_PM:
					if (iRetChat == 0)
						break;

					if (true)
					{
						int iLastMessageTick = (TICKCOUNT - m_dwLastMessageTick);
						if (m_dwLastMessageTick && iLastMessageTick < 2000)
						{
							m_iTotalMessages++;

							if (m_iTotalMessages > 10)
							{
								if (iLastMessageTick > 0)
								{
									STRINGCOPY(lpCurPlayer->szMessage, FormatString("%s: %s", lpCurPlayer->sCharacterData.szName, "My tongue froze because I talk too much -_-"));
									lpCurPlayer->dwMessageEndTime = TICKCOUNT + 1000 * 7;
									m_dwLastMessageTick = TICKCOUNT + 1000 * 7;

									OnEmoteCommand(std::string("e6"), lpCurPlayer);
								}

								return;
							}
						}
						else if (iLastMessageTick > 2000)
							m_iTotalMessages = 0;

						m_dwLastMessageTick = TICKCOUNT;
					}

					strMessage = FormatString("%s: %s", lpCurPlayer->sCharacterData.szName, strMessage.c_str());
					STRINGCOPY(lpCurPlayer->szMessage, strMessage.c_str());
					lpCurPlayer->dwMessageEndTime = TICKCOUNT + 1000 * 7;
					AddMessage(strMessage, CHATCOLOR_Normal, lpCurPlayer->sCharacterData.szName);
					break;
				case CHATBOXTABID_Clan:
					strMessage = FormatString("/CLAN> %s", strMessage.c_str());
					break;
				case CHATBOXTABID_Party:
					strMessage = FormatString("@%s", strMessage.c_str());
					break;
				case CHATBOXTABID_Raid:
					strMessage = FormatString("#%s", strMessage.c_str());
					break;
				case CHATBOXTABID_Trade:
					strMessage = FormatString("/TRADE>%s", strMessage.c_str());
					bSendToLoginServer = TRUE;
					break;
				}
			}

			if (iRetChat)
			{
				CHATGAMEHANDLE->SendChat(bSendToLoginServer, strMessage.c_str());
			}
		}
	}
	std::string Window::GetSaveCommand(BOOL bUP)
	{
		std::string str = "";

		if (m_vSaveCommand.size() > 0)
		{
			if (bUP == FALSE)
				str = m_vSaveCommand[(m_uSaveCommandWheel--) % m_vSaveCommand.size()];
			else
				str = m_vSaveCommand[(m_uSaveCommandWheel++) % m_vSaveCommand.size()];

			str.insert(str.length(), " ");
		}
		return str;
	}
	void Window::AddSaveCommand(std::string strMessage)
	{
		if ((strMessage.length() > 2) && (strMessage[0] == '/'))
		{
			std::string str = strMessage.substr(0, strMessage.find(' '));

			BOOL bFound = FALSE;

			for (auto &v : m_vSaveCommand)
			{
				if (v.compare(str.c_str()) == 0)
				{
					bFound = TRUE;
					break;
				}
			}

			if (bFound == FALSE)
			{
				m_vSaveCommand.push_back(str);
				if (m_vSaveCommand.size() > MAX_SAVECOMMANDSCHAT)
					m_vSaveCommand.erase(m_vSaveCommand.begin());
			}
		}
	}
	BOOL Window::OnEmoteCommand(std::string & strMessage, Unit * pcUnit)
	{
		BOOL bRet = FALSE;
		//std::string strEffectPath;
		int iEmoteIndex = 0;

		for (std::map<std::string, std::string>::iterator it = m_sFriendlyCommands.begin(); it != m_sFriendlyCommands.end(); it++)
		{
			if (STRINGCOMPAREI(it->first.c_str(), strMessage.c_str()))
			{
				strMessage = it->second;
				break;
			}
		}

		size_t uPos = strMessage.find_first_of(":");
		if (uPos != std::string::npos)
			if (uPos + 1 <= strMessage.length())
				strMessage = trim(strMessage.substr(strMessage.find_first_of(":") + 1));

		if ((strMessage.length() <= 3) && (strMessage.length() > 0))
		{
			iEmoteIndex = atoi(strMessage.substr(1).c_str());

			if (strMessage[0] == 'e' && isdigit(strMessage[1]) && iEmoteIndex > 0 && iEmoteIndex <= MAX_EMOTELIST)
			{
				bRet = TRUE;
				//strEffectPath = FormatString("game\\scripts\\particles\\Emote%d.luac", iEmoteIndex);
			}
		}

		/*if (pcUnit && bRet)
		{
			CParticleScript * pc = PARTICLEFACTORY->LoadScript(strEffectPath, 0, TRUE);

			if (pc)
			{
				pc->SetID(iEmoteIndex + 1000);
				Engine::ObjectOwnerUnit * pcOwner = new Engine::ObjectOwnerUnit(UNITDATATOUNIT(pcUnit));
				pcOwner->AddAnimationTypeLostCondition(ANIMATIONTYPE_Die);
				pc->SetOwner(pcOwner);
				PARTICLEENGINE->AddScript(pc);
			}
		}*/

		return bRet;
	}
	void Window::ToggleNotice(BOOL bOpen)
	{
		int iY = 0;
		int iHeight = 0;

		auto pImageBoxChatBar = m_pcWindow->GetElement<UI::ImageBox>(IMAGEID_ChatBoxBar);
		auto pListChatNotice = m_pcWindow->GetElement<UI::List>(LISTID_ChatNotice);
		if (!pImageBoxChatBar || !pListChatNotice)
			return;

		if (bOpen)
		{
			iY = 74;
			iHeight = 100;
			pImageBoxChatBar->Show();
			pListChatNotice->Show();
		}
		else
		{
			iY = 8;
			iHeight = 166;
			pImageBoxChatBar->Hide();
			pListChatNotice->Hide();
		}

		for (size_t i = 0; i < 6; i++)
		{
			auto pListChat = m_pcWindow->GetElement<UI::List>(LISTID_ChatAll + i);
			if (pListChat)
			{
				pListChat->SetBox(Rectangle2D(pListChat->GetX(), iY, pListChat->GetWidth(), iHeight));
				pListChat->GetScrollBar()->SetHeight(iHeight + 5);
				pListChat->GetScrollBar()->SetPercent(100);
			}
		}
	}
	void Window::CheckCollideWindow(BOOL bResolutionChanged)
	{
		if (((m_pcWindow->GetY() + m_pcWindow->GetHeight() > RESOLUTION_HEIGHT - 175) && (m_pcWindow->GetX() < 800)) || bResolutionChanged)
		{
			//Open Inventory/Skills/Character Info Window
			if (cInvenTory.OpenFlag && sinMoveKindInter[SIN_INVENTORY] > 0 && (sinMoveKindInter[SIN_INVENTORY] != 256 || bResolutionChanged))
				m_pcWindow->SetPosition(m_pcWindow->GetX(), (205 + (256 - sinMoveKindInter[SIN_INVENTORY])) + (RESOLUTION_HEIGHT - 600));

			if (cSkill.OpenFlag && sinMoveKindInter[SIN_SKILL] > 0 && (sinMoveKindInter[SIN_SKILL] != 256 || bResolutionChanged))
				m_pcWindow->SetPosition(m_pcWindow->GetX(), (205 + (256 - sinMoveKindInter[SIN_SKILL])) + (RESOLUTION_HEIGHT - 600));

			if (cCharStatus.OpenFlag && sinMoveKindInter[SIN_CHARSTATUS] > 0 && (sinMoveKindInter[SIN_CHARSTATUS] != 256 || bResolutionChanged))
				m_pcWindow->SetPosition(m_pcWindow->GetX(), (205 + (256 - sinMoveKindInter[SIN_CHARSTATUS])) + (RESOLUTION_HEIGHT - 600));
		}

		//Closing
		if (!cInvenTory.OpenFlag && !cSkill.OpenFlag && !cCharStatus.OpenFlag)
		{
			if (m_pcWindow->GetY() + m_pcWindow->GetHeight() > RESOLUTION_HEIGHT - 180 && m_pcWindow->GetX() + m_pcWindow->GetWidth() < 300)
			{
				if (sinMoveKindInter[SIN_INVENTORY] > 0 && sinMoveKindInter[SIN_INVENTORY] < 256)
					m_pcWindow->SetPosition(m_pcWindow->GetX(), RESOLUTION_HEIGHT - m_pcWindow->GetHeight() - 4);

				if (sinMoveKindInter[SIN_SKILL] > 0 && sinMoveKindInter[SIN_SKILL] < 256)
					m_pcWindow->SetPosition(m_pcWindow->GetX(), RESOLUTION_HEIGHT - m_pcWindow->GetHeight() - 4);

				if (sinMoveKindInter[SIN_CHARSTATUS] > 0 && sinMoveKindInter[SIN_CHARSTATUS] < 256)
					m_pcWindow->SetPosition(m_pcWindow->GetX(), RESOLUTION_HEIGHT - m_pcWindow->GetHeight() - 4);
			}
		}
	}
	void Window::AddRecentPlayer(std::string strMessage)
	{
		std::string strName = "";

		if (strMessage.find("From> ") == 0)
			strName = strMessage.substr(STRLEN("From> "), strMessage.find(':') - STRLEN("From> "));
		else if (strMessage.find("To> ") == 0)
			strName = strMessage.substr(STRLEN("To> "), strMessage.find(':') - STRLEN("To> "));
		else
		{
			if (strMessage.length() > 2)
			{
				size_t iFind = strMessage.find(' ');

				if ((strMessage[0] == '/') && ((strMessage[1] == ':') || (strMessage[1] == ';')))
					strName = strMessage.substr(2, iFind != std::string::npos ? (iFind - 2) : 0);
			}
		}

		if (strName.length() > 0)
		{
			InterfaceParty.latest_Insert((char *)strName.c_str());
		}
	}
	void Window::HandlePacket(PacketChatBoxMessage * psPacket)
	{
		Unit * pcUnit = NULL;

		BOOL bEmote = FALSE;

		if (psPacket->lID)
			pcUnit = FindAutoPlayer(psPacket->lID);

		if (pcUnit)
			bEmote = OnEmoteCommand(std::string(psPacket->szChatBoxMessage), pcUnit);

		if (((pcUnit && (pcUnit->sCharacterData.iType == CHARACTERTYPE_Player || pcUnit->iCharacterType == CHARACTERTYPE_Player)) || psPacket->lID == 0))
			AddMessage(psPacket->szChatBoxMessage, psPacket->lID ? CHATCOLOR_Normal : psPacket->iChatColor);

		if (pcUnit && (psPacket->iChatColor != CHATCOLOR_Party))
		{
			if (bEmote == FALSE)
			{
				STRINGCOPY(pcUnit->szMessage, psPacket->szChatBoxMessage);
				pcUnit->dwMessageEndTime = TICKCOUNT + 5000;
			}
		}
	}
}