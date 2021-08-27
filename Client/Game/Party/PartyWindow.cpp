#include "StdAfx.h"
#include "PartyWindow.h"

namespace PARTY
{
	Window::Window() : CBaseWindow()
	{
		
	}
	Window::Window(EWindow eID) : CBaseWindow(eID)
	{
		SetWindowLevel(7);
	}
	Window::~Window()
	{

	}
	void Window::Init()
	{
		m_pWindowParty = std::make_shared<UI::Window>(Rectangle2D(0, 0, 290, 345));
		m_pWindowRaid = std::make_shared<UI::Window>(Rectangle2D(0, 0, 115, 185));

		m_pImagePartyMode[0] = UI::ImageLoader::LoadImage_("Resources\\UI\\party\\normalmode.png");
		m_pImagePartyMode[1] = UI::ImageLoader::LoadImage_("Resources\\UI\\party\\expmode.png");
		m_pImagePartyMode[2] = UI::ImageLoader::LoadImage_("Resources\\UI\\party\\huntmode.png");

		BuildWindowParty();
		BuildWindowRaid();
	}
	void Window::Shutdown()
	{
		m_pWindowParty->Clear();
		m_pWindowRaid->Clear();
	}
	void Window::Render()
	{
		m_pWindowRaid->Render(0, 0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);
		m_pWindowParty->Render(0, 0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);
	}
	void Window::Update(float fTime)
	{
		UpdatePartyData(&PARTYHANDLE->GetPartyData());

		m_pWindowParty->Update(fTime);
		m_pWindowRaid->Update(fTime);
	}
	void Window::OnMouseMove(class INPUTS::Mouse * pcMouse)
	{
		m_pWindowParty->OnMouseMove(pcMouse, 0, 0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);
		m_pWindowRaid->OnMouseMove(pcMouse, 0, 0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);
	}
	BOOL Window::OnMouseClick(class INPUTS::Mouse * pcMouse)
	{
		if (m_pWindowParty->OnMouseClick(pcMouse, 0, 0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0))
			return TRUE;

		if (m_pWindowRaid->OnMouseClick(pcMouse, 0, 0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0))
			return TRUE;

		return FALSE;
	}
	void Window::ShowPartyNotification(char * pszCharacterName, int iType)
	{
		m_iPartyRequestType = iType;

		MESSAGEBOX->SetBoxType(MESSAGE::BOX::Window::BOXTYPEID_YesNo);
		MESSAGEBOX->SetTitle("Party Request");
		MESSAGEBOX->SetDescription(FormatString("Do you want to accept %s's Party Request?", pszCharacterName));
		MESSAGEBOX->SetEvent(std::bind(&Window::OnAcceptPartyButtonClick, this));
		MESSAGEBOX->SetAutoClose(10);
		MESSAGEBOX->Show();
	}
	void Window::ShowRaidNotification(char * pszCharacterName)
	{
		MESSAGEBOX->SetBoxType(MESSAGE::BOX::Window::BOXTYPEID_YesNo);
		MESSAGEBOX->SetTitle("Raid Request");
		MESSAGEBOX->SetDescription(FormatString("Do you want to accept %s's Raid Request?", pszCharacterName));
		MESSAGEBOX->SetEvent(std::bind(&Window::OnAcceptRaidButtonClick, this));
		MESSAGEBOX->SetAutoClose(10);
		MESSAGEBOX->Show();
	}
	void Window::UpdateParty(CPartyData * pcParty)
	{
		BOOL bPartyIsRaidLeader = FALSE;

		m_pWindowParty->Hide();

		auto pImageParty = m_pWindowParty->GetElement<UI::ImageBox>(IMAGEID_PartyType);
		auto pTooltipParty = m_pWindowParty->GetElement<UI::ToolTip>(TOOLTIPID_PartyType);

		if (pImageParty && pTooltipParty)
		{
			pImageParty->SetImage(m_pImagePartyMode[pcParty->eMode]);
			pTooltipParty->SetText(GetPartyMode(pcParty->eMode));
		}

		for (size_t i = 0; i < MAX_RAID - 1; i++)
		{
			auto pListPartyRaid = m_pWindowRaid->GetElement<UI::List>(LISTID_PartyRaid + i);
			if (pListPartyRaid)
			{
				pListPartyRaid->Clear();
				pListPartyRaid->Hide();
				m_pWindowRaid->Hide();

				if (pcParty->iRaidCount > 0)
				{
					bPartyIsRaidLeader = true;

					PartyRaid * pPartyRaid = &pcParty->saRaid[i];
					UI::LPWINDOW p = std::make_shared<UI::Window>(Rectangle2D(0, 0, 115, 16));

					UI::LPTEXT pText = std::make_shared<UI::Text>(FormatString("Party #%d", (int)pPartyRaid->cRaidID), Rectangle2D(0, 0, 110, 20), TRUE, UI::Color(255, 0, 180, 255).Get());
					pText->SetFont("Noto Sans", 16, 0, FALSE, FALSE, UI::Color(255, 0, 180, 255).Get());
					pText->SetDropdownShadow(TRUE);
					pText->SetNoClip(TRUE);
					p->AddElement(pText);

					pListPartyRaid->AddWindow(p);

					if (pPartyRaid->cRaidID == 1)
						bPartyIsRaidLeader = false;

					for (size_t j = 0; j < MAX_PARTY_MEMBERS; j++)
					{
						PartyRaidMember * pMemberRaid = &pPartyRaid->saMembers[j];

						if (pMemberRaid->sData.iID)
						{
							UI::LPWINDOW pWindowRaidMember = std::make_shared<UI::Window>(Rectangle2D(0, 0, 115, 20));
							pWindowRaidMember->SetID(WINDOWID_Member1 + j);

							//Character Name
							UI::LPTEXT pTextCharacterName = std::make_shared<UI::Text>(pPartyRaid->saMembers[j].szCharacterName, Rectangle2D(0, 0, 110, 15), TRUE, -1);
							pTextCharacterName->SetID(TEXTID_Name);
							pTextCharacterName->SetFont("Noto Sans", 14, 0, FALSE, FALSE, -1);
							pTextCharacterName->SetDropdownShadow(TRUE);
							pTextCharacterName->SetNoClip(TRUE);
							pWindowRaidMember->AddElement(pTextCharacterName);

							//Image of Life Bar
							UI::LPIMAGEBOX pImageLifeBar = std::make_shared<UI::ImageBox>(Rectangle2D(0, 14, 89, 4));
							pImageLifeBar->SetID(IMAGEID_Background);
							pImageLifeBar->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\party\\minilifebar.png"));
							pWindowRaidMember->AddElement(pImageLifeBar);

							UI::LPIMAGEBOX pImageLifeBarActive = std::make_shared<UI::ImageBox>(Rectangle2D(0, 14, 89, 4));
							pImageLifeBarActive->SetID(IMAGEID_LifeBar);
							pImageLifeBarActive->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\party\\minilifebar_.png"));
							pWindowRaidMember->AddElement(pImageLifeBarActive);

							pListPartyRaid->AddWindow(pWindowRaidMember);
						}
					}

					if (!SETTINGHANDLE->Get().bLockUI)
					{
						m_pWindowRaid->SetMoveBox(Rectangle2D(0, 0, 175, 15 + pListPartyRaid->GetListHeight()));
						m_pWindowRaid->SetCanMove(TRUE);
					}
					else
						m_pWindowRaid->SetCanMove(FALSE);

					pListPartyRaid->Show();
					m_pWindowRaid->Show();
				}
			}
		}

		auto pListPartyMembers = m_pWindowParty->GetElement<UI::List>(LISTID_PartyMembers);
		if (pListPartyMembers)
		{
			pListPartyMembers->Clear();

			UI::LPGROUP pGroupDropdown = std::make_shared<UI::Group>();
			m_pWindowParty->AddElement(pGroupDropdown);

			//Clear Dropdown
			for (int i = 0; i < MAX_PARTY_MEMBERS; i++)
			{
				auto p = m_pWindowParty->GetElement<UI::Menu>(DROPDOWNMENUID_Options + (i * 6));
				if (p)
					m_pWindowParty->DelElement(p);
			}

			//Add Party Members
			for (size_t i = 0; i < MAX_PARTY_MEMBERS; i++)
			{
				PartyMember sPartyMember = pcParty->saMembers[i];

				if (sPartyMember.sData.iID)
				{
					UI::LPWINDOW p = std::make_shared<UI::Window>(Rectangle2D(0, 0, 290, 49));
					p->SetID(WINDOWID_Member1 + i);

					UI::LPIMAGEBOX pImageBackground = std::make_shared<UI::ImageBox>(Rectangle2D(0, 0, 173, 49));
					pImageBackground->SetID(IMAGEID_Background);
					pImageBackground->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\party\\background.png"));
					p->AddElement(pImageBackground);

					//Icon of Member Party
					UI::LPIMAGEBOX pImageIconPartyMember = std::make_shared<UI::ImageBox>(Rectangle2D(34, 40, 9, 9));
					pImageIconPartyMember->SetID(IMAGEID_Icon);
					pImageIconPartyMember->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\party\\member%d.png", i + 1));
					p->AddElement(pImageIconPartyMember);

					//Text Character Name
					UI::LPTEXT pTextCharacterName = std::make_shared<UI::Text>(sPartyMember.szCharacterName, Rectangle2D(70, 7, 220, 20), TRUE, -1);
					pTextCharacterName->SetID(TEXTID_Name);
					pTextCharacterName->SetFont("Noto Sans", 15, 0, FALSE, FALSE, -1);
					pTextCharacterName->SetDropdownShadow(TRUE);
					pTextCharacterName->SetNoClip(TRUE);
					p->AddElement(pTextCharacterName);

					//Text Character Level
					UI::LPTEXT pTextCharacterLevel = std::make_shared<UI::Text>("", Rectangle2D(43, 10, 20, 12), TRUE, D3DCOLOR_XRGB(255, 238, 100));
					pTextCharacterLevel->SetID(TEXTID_CharacterLevel);
					pTextCharacterLevel->SetFont("Arial", 12, 0, FALSE, FALSE, D3DCOLOR_XRGB(255, 238, 100));
					pTextCharacterLevel->SetDropdownShadow(TRUE);
					pTextCharacterLevel->SetDropdownColor(D3DCOLOR_XRGB(30, 30, 30));
					pTextCharacterLevel->SetNoClip(TRUE);
					pTextCharacterLevel->SetHorizontalAlign(ALIGN_Center);
					p->AddElement(pTextCharacterLevel);

					//Image of Character Class
					const char * pszClass = GetCharacterClassByFlag(CharacterClassToClassFlag((ECharacterClass)sPartyMember.cCharacterClass));

					char szClassPath1[64] = { 0 };
					char szClassPath2[64] = { 0 };

					STRINGFORMAT(szClassPath1, "Resources\\UI\\party\\%s.png", pszClass);
					STRINGFORMAT(szClassPath2, "Resources\\UI\\party\\%s_.png", pszClass);

					UI::LPIMAGEBOX pImageCharacterClass = std::make_shared<UI::ImageBox>(Rectangle2D(6, 8, 34, 34));
					pImageCharacterClass->SetID(IMAGEID_Class);
					pImageCharacterClass->SetActiveImage(UI::ImageLoader::LoadActiveImage(szClassPath1, szClassPath2));
					p->AddElement(pImageCharacterClass);

					//Image of Life Bar
					UI::LPIMAGEBOX pImageLifeBar = std::make_shared<UI::ImageBox>(Rectangle2D(46, 25, 119, 6));
					pImageLifeBar->SetID(IMAGEID_LifeBar);
					pImageLifeBar->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\party\\lifebar.png"));
					p->AddElement(pImageLifeBar);

					//Image of Mana Bar
					UI::LPIMAGEBOX pImageManaBar = std::make_shared<UI::ImageBox>(Rectangle2D(42, 37, 123, 3));
					pImageManaBar->SetID(IMAGEID_ManaBar);
					pImageManaBar->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\party\\manabar.png"));
					p->AddElement(pImageManaBar);

					//Dropdown Menu
					UI::LPMENU pDropdownMenu = std::make_shared<UI::Menu>(Rectangle2D(175, 60 + pListPartyMembers->GetListHeight(), 94, 24));
					pDropdownMenu->SetID(DROPDOWNMENUID_Options + (i * 6));
					pDropdownMenu->SetGroup(pGroupDropdown);
					pDropdownMenu->SetMenuPosition(UI::EMENUPOSITION_Left);
					pDropdownMenu->SetMouseEvent(ClickDownR);
					pDropdownMenu->SetEvent(UI::Event::Build(std::bind(&Window::OnSelectMenuParty, this, i)));
					pDropdownMenu->SetBackground("Resources\\UI\\menu\\topleft.png", "Resources\\UI\\menu\\middle.png", "Resources\\UI\\menu\\bottom.png", "Resources\\UI\\menu\\main.png");

					//Indicate it's a Party Leader
					if (i == 0)
					{
						if (bPartyIsRaidLeader)
						{
							UI::LPIMAGEBOX pImageIconRaidLeader = std::make_shared<UI::ImageBox>(Rectangle2D(5, -18, 37, 30));
							pImageIconRaidLeader->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\party\\raidleader.png"));
							p->AddElement(pImageIconRaidLeader);
						}

						UI::LPIMAGEBOX pImageIconLeader = std::make_shared<UI::ImageBox>(Rectangle2D(13, -10, 21, 14));
						pImageIconLeader->SetID(IMAGEID_IconLeader);
						pImageIconLeader->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\party\\leader.png"));
						p->AddElement(pImageIconLeader);
					}

					//Party Leader
					if (pcParty->saMembers[0].sData.iID == UNIT->iID)
					{
						if (i != 0)
						{
							//Options
							pDropdownMenu->AddOption(pDropdownMenu->MakeOption("Delegate", Rectangle2D(13, 5, 77, 18), FALSE, -1, D3DCOLOR_XRGB(230, 180, 150)), FALSE, 1);
							pDropdownMenu->AddOption(pDropdownMenu->MakeOption("Kick", Rectangle2D(13, 5, 77, 18), FALSE, -1, D3DCOLOR_XRGB(230, 180, 150)), FALSE, 2);
						}
						else
						{
							//Options
							pDropdownMenu->AddOption(pDropdownMenu->MakeOption("Disband", Rectangle2D(13, 5, 77, 18), FALSE, -1, D3DCOLOR_XRGB(230, 180, 150)), FALSE, 3);
							pDropdownMenu->AddOption(pDropdownMenu->MakeOption("Leave", Rectangle2D(13, 5, 77, 18), FALSE, -1, D3DCOLOR_XRGB(230, 180, 150)), FALSE, 4);
							pDropdownMenu->AddOption(pDropdownMenu->MakeOption("Change Mode", Rectangle2D(13, 5, 77, 18), FALSE, -1, D3DCOLOR_XRGB(230, 180, 150)), FALSE, 5);
						}
					}
					else
					{
						if (sPartyMember.sData.iID == UNIT->iID)
						{
							//Options
							pDropdownMenu->AddOption(pDropdownMenu->MakeOption("Leave", Rectangle2D(13, 5, 77, 18), FALSE, -1, D3DCOLOR_XRGB(230, 180, 150)), FALSE, 6);
						}
					}

					m_pWindowParty->AddElement(pDropdownMenu);

					//Button to open Dropdown Menu
					UI::LPBUTTON pButtonDropdownMenu = std::make_shared<UI::Button>(Rectangle2D(0, 0, 173, 49));
					pButtonDropdownMenu->SetMouseEvent(ClickDownR);
					pButtonDropdownMenu->SetMenu(pDropdownMenu);
					p->AddElement(pButtonDropdownMenu);

					pListPartyMembers->AddWindow(p);
				}
			}

			if (!SETTINGHANDLE->Get().bLockUI)
			{
				m_pWindowParty->SetMoveBox(Rectangle2D(0, 0, 175, 50 + pListPartyMembers->GetListHeight()));
				m_pWindowParty->SetCanMove(TRUE);
			}
			else
				m_pWindowParty->SetCanMove(FALSE);

			m_pWindowParty->Show();
		}
	}
	void Window::UpdatePartyData(CPartyData * pcParty)
	{
		if (pcParty->iRaidCount > 0)
		{
			for (size_t i = 0; i < MAX_RAID - 1; i++)
			{
				auto pListPartyRaid = m_pWindowRaid->GetElement<UI::List>(LISTID_PartyRaid + i);
				if (pListPartyRaid)
				{
					for (size_t j = 0; j < MAX_PARTY_MEMBERS; j++)
					{
						PartyRaidMember psMember = pcParty->saRaid[i].saMembers[j];
						auto pWindowMember = pListPartyRaid->GetWindow(WINDOWID_Member1 + j);
						if (pWindowMember)
						{
							BOOL bDead = psMember.sData.sHP.sMin <= 0 ? TRUE : FALSE;
							BOOL bFar = !psMember.sData.sPosition.WithinPTDistance(&UNIT->sPosition, DISTANCE_UNIT_PARTY_MAX);

							auto pBackgroundImage = pWindowMember->GetElement<UI::ImageBox>(IMAGEID_Background);
							if (pBackgroundImage)
								pBackgroundImage->SetColor(bFar ? D3DCOLOR_ARGB(120, 255, 255, 255) : -1);

							auto pLifeBarImage = pWindowMember->GetElement<UI::ImageBox>(IMAGEID_LifeBar);
							if (pLifeBarImage)
							{
								if (psMember.sData.sHP.sMax > 0)
									pLifeBarImage->SetWidth((psMember.sData.sHP.sMin * 89) / psMember.sData.sHP.sMax);

								pLifeBarImage->SetColor(bFar ? D3DCOLOR_ARGB(120, 255, 255, 255) : -1);
							}

							auto pTextCharacterName = pWindowMember->GetElement<UI::Text>(TEXTID_Name);
							if (pTextCharacterName)
							{
								if (bDead)
									pTextCharacterName->SetColor(D3DCOLOR_XRGB(255, 45, 45));
								else if (bFar)
									pTextCharacterName->SetColor(D3DCOLOR_XRGB(185, 175, 155));
								else
									pTextCharacterName->SetColor(-1);
							}
						}
					}

				}
			}
		}

		auto pListPartyMembers = m_pWindowParty->GetElement<UI::List>(LISTID_PartyMembers);
		if (pListPartyMembers)
		{
			for (int i = 0; i < pcParty->iMembersCount; i++)
			{
				PartyMember psMember = pcParty->saMembers[i];

				auto pWindowMember = pListPartyMembers->GetWindow(WINDOWID_Member1 + i);
				if (pWindowMember)
				{
					BOOL bDead = psMember.sData.sHP.sMin <= 0 ? TRUE : FALSE;
					BOOL bFar = !psMember.sData.sPosition.WithinPTDistance(&UNIT->sPosition, DISTANCE_UNIT_PARTY_MAX);

					auto pBackgroundImage = pWindowMember->GetElement<UI::ImageBox>(IMAGEID_Background);
					if (pBackgroundImage)
						pBackgroundImage->SetColor(bFar ? D3DCOLOR_ARGB(150, 255, 255, 255) : -1);

					auto pIconImage = pWindowMember->GetElement<UI::ImageBox>(IMAGEID_Icon);
					if (pIconImage)
						pIconImage->SetColor(bFar ? D3DCOLOR_ARGB(150, 255, 255, 255) : -1);

					auto pLifeBarImage = pWindowMember->GetElement<UI::ImageBox>(IMAGEID_LifeBar);
					if (pLifeBarImage)
					{
						if (psMember.sData.sHP.sMax > 0)
							pLifeBarImage->SetWidth((psMember.sData.sHP.sMin * 119) / psMember.sData.sHP.sMax);

						pLifeBarImage->SetColor(bFar ? D3DCOLOR_ARGB(150, 255, 255, 255) : -1);
					}

					auto pManaBarImage = pWindowMember->GetElement<UI::ImageBox>(IMAGEID_ManaBar);
					if (pManaBarImage)
					{
						if (psMember.sData.sMP.sMax > 0)
							pManaBarImage->SetWidth((psMember.sData.sMP.sMin * 123) / psMember.sData.sMP.sMax);

						pManaBarImage->SetColor(bFar ? D3DCOLOR_ARGB(150, 255, 255, 255) : -1);
					}

					auto pTextCharacterLevel = pWindowMember->GetElement<UI::Text>(TEXTID_CharacterLevel);
					if (pTextCharacterLevel)
					{
						int iLevel = psMember.sData.sLevel;
						if (psMember.sData.iID == UNIT->iID)
							iLevel = UNIT->sCharacterData.iLevel;

						pTextCharacterLevel->SetText(FormatString("%d", iLevel));
					}

					auto pCharacterClassImage = pWindowMember->GetElement<UI::ImageBox>(IMAGEID_Class);
					if (pCharacterClassImage)
					{
						pCharacterClassImage->Swap(bDead ? TRUE : FALSE);
						pCharacterClassImage->SetColor(bFar ? D3DCOLOR_ARGB(150, 255, 255, 255) : -1);
					}

					auto pLeaderIconImage = pWindowMember->GetElement<UI::ImageBox>(IMAGEID_IconLeader);
					if (pLeaderIconImage)
						pLeaderIconImage->SetColor(bFar ? D3DCOLOR_ARGB(150, 255, 255, 255) : -1);

					auto pTextCharacterName = pWindowMember->GetElement<UI::Text>(TEXTID_Name);
					if (pTextCharacterName)
					{
						if (bDead)
							pTextCharacterName->SetColor(D3DCOLOR_XRGB(255, 45, 45));
						else if (bFar)
							pTextCharacterName->SetColor(D3DCOLOR_XRGB(185, 175, 155));
						else
							pTextCharacterName->SetColor(-1);
					}
				}
			}
		}
	}
	void Window::LeaveParty()
	{
		auto pListPartyMembers = m_pWindowParty->GetElement<UI::List>(LISTID_PartyMembers);
		if (pListPartyMembers)
		{
			pListPartyMembers->Clear();
			m_pWindowParty->Hide();
			m_pWindowRaid->Hide();
		}
	}
	void Window::ToggleWindow()
	{
		auto pListPartyMembers = m_pWindowParty->GetElement<UI::List>(LISTID_PartyMembers);
		if (pListPartyMembers)
		{
			if (pListPartyMembers->IsOpen())
			{
				pListPartyMembers->Hide();
				m_pWindowParty->SetHeight(15);
				m_pWindowParty->SetCanMove(FALSE);
				m_pWindowRaid->Hide();
			}
			else
			{
				pListPartyMembers->Show();
				m_pWindowParty->SetHeight(50 + pListPartyMembers->GetListHeight());
				m_pWindowParty->SetCanMove(!SETTINGHANDLE->Get().bLockUI);
				m_pWindowParty->SetMoveBox(Rectangle2D(0, 0, m_pWindowParty->GetWidth(), m_pWindowParty->GetHeight()));
				m_pWindowRaid->Show();
			}
		}
	}
	void Window::BuildWindowParty()
	{
		m_pWindowParty->SetPosition(0, (RESOLUTION_HEIGHT >> 1) - (345 >> 1));

		UI::LPBUTTON pToggleParty = std::make_shared<UI::Button>(Rectangle2D(14, 0, 18, 14));
		pToggleParty->SetActiveImage(UI::ImageLoader::LoadActiveImage("Resources\\UI\\party\\expand.png", "Resources\\UI\\party\\expand_.png"));
		pToggleParty->SetEvent(UI::Event::Build(std::bind(&Window::ToggleWindow, this)));
		m_pWindowParty->AddElement(pToggleParty);

		UI::LPIMAGEBOX pImageParty = std::make_shared<UI::ImageBox>(Rectangle2D(36, 0, 15, 15));
		pImageParty->SetID(IMAGEID_PartyType);
		pImageParty->SetImage(m_pImagePartyMode[0]);
		pImageParty->SetColor(UI::Color(220, 255, 255, 255).Get());
		m_pWindowParty->AddElement(pImageParty);

		UI::LPLIST pListPartyMembers = std::make_shared<UI::List>(Rectangle2D(0, 40, 290, 345));
		pListPartyMembers->SetNoClip(TRUE);
		pListPartyMembers->SetID(LISTID_PartyMembers);
		m_pWindowParty->AddElement(pListPartyMembers);

		UI::LPTOOLTIP pTooltipHideParty = std::make_shared<UI::ToolTip>(Rectangle2D());
		pTooltipHideParty->Init();
		pTooltipHideParty->SetFont("Arial", 16, -1);
		pTooltipHideParty->SetText("Hide/Show Party");
		pTooltipHideParty->SetLinkObject(pToggleParty);
		pTooltipHideParty->SetPosition(TOOLTIPPOSITION_Top);
		pTooltipHideParty->SetFollowMouse(FALSE);
		m_pWindowParty->AddElement(pTooltipHideParty);

		//Tooltip of Party Mode
		UI::LPTOOLTIP pTooltipPartyType = std::make_shared<UI::ToolTip>(Rectangle2D());
		pTooltipPartyType->Init();
		pTooltipPartyType->SetID(TOOLTIPID_PartyType);
		pTooltipPartyType->SetLinkObject(pImageParty);
		pTooltipPartyType->SetFont("Arial", 16, -1);
		pTooltipPartyType->SetPosition(TOOLTIPPOSITION_Top);
		pTooltipPartyType->SetFollowMouse(FALSE);
		m_pWindowParty->AddElement(pTooltipPartyType);

		m_pWindowParty->Hide();
	}
	void Window::BuildWindowRaid()
	{
		m_pWindowRaid->SetPosition(180, (RESOLUTION_HEIGHT >> 1) - (345 >> 1));

		for (size_t i = 0; i < MAX_RAID - 1; i++)
		{
			UI::LPLIST pListPartyRaid = std::make_shared<UI::List>(Rectangle2D(0, 0, 115, 180));
			pListPartyRaid->SetID(LISTID_PartyRaid + i);
			m_pWindowRaid->AddElement(pListPartyRaid);
		}

		m_pWindowRaid->Hide();
	}
	void Window::ShowMessageBox(int iType, int iIndex)
	{
		MESSAGEBOX->SetBoxType(MESSAGE::BOX::Window::BOXTYPEID_YesNo);
		MESSAGEBOX->SetTitle("Are you sure?");

		if (iType == 1)
		{
			MESSAGEBOX->SetDescription("Do you want to disband the Party?");
			MESSAGEBOX->SetEvent(std::bind(&Window::OnDisbandPartyButtonClick, this));
		}
		else if (iType == 2)
		{
			MESSAGEBOX->SetDescription(FormatString("Do you want  to expel %s?", PARTYHANDLE->GetPartyData().saMembers[iIndex].szCharacterName));
			MESSAGEBOX->SetEvent(std::bind(&Window::OnKickPartyButtonClick, this, iIndex));
		}
		else if (iType == 3)
		{
			MESSAGEBOX->SetDescription("Do you want to leave the party?");
			MESSAGEBOX->SetEvent(std::bind(&Window::OnLeavePartyButtonClick, this));
		}
		else if (iType == 4)
		{
			MESSAGEBOX->SetDescription(FormatString("Do you want to delegate %s as party leader?", PARTYHANDLE->GetPartyData().saMembers[iIndex].szCharacterName));
			MESSAGEBOX->SetEvent(std::bind(&Window::OnDelegatePartyButtonClick, this, iIndex));
		}
		else if (iType == 5)
		{
			MESSAGEBOX->SetDescription(FormatString("Do you want to change Party to %s?", GetPartyMode((EPartyMode)((PARTYHANDLE->GetPartyData().eMode + 1) % 3))));
			MESSAGEBOX->SetEvent(std::bind(&Window::OnChangePartyModeButtonClick, this));
		}

		MESSAGEBOX->Show();
	}
	void Window::OnSelectMenuParty(int iIndex)
	{
		auto pListPartyMembers = m_pWindowParty->GetElement<UI::List>(LISTID_PartyMembers);
		if (pListPartyMembers)
		{
			auto pWindowMember = pListPartyMembers->GetWindow(WINDOWID_Member1 + iIndex);
			if (pWindowMember)
			{
				UI::LPMENU pDropdownMenu = m_pWindowParty->GetElement<UI::Menu>(DROPDOWNMENUID_Options + (iIndex * 6));

				if (pDropdownMenu)
				{
					int iOptionID = pDropdownMenu->GetOptionID();
					if (iOptionID == 1)
						ShowMessageBox(4, iIndex);
					else if (iOptionID == 2)
						ShowMessageBox(2, iIndex);
					else if (iOptionID == 3)
						ShowMessageBox(1, iIndex);
					else if (iOptionID == 4)
						ShowMessageBox(3, iIndex);
					else if (iOptionID == 5)
						ShowMessageBox(5, iIndex);
					else if (iOptionID == 6)
						ShowMessageBox(3, iIndex);
				}
			}
		}
	}
	void Window::OnAcceptPartyButtonClick()
	{
		if (MESSAGEBOX->GetType())
		{
			if (m_iPartyRequestType > 0)
			{
				if (m_iPartyRequestType == 1)
					PARTYHANDLE->JoinPartyRequest();
				else if (m_iPartyRequestType == 2)
					PARTYHANDLE->AcceptPartyRequest();
			}
		}
	}
	void Window::OnAcceptRaidButtonClick()
	{
		if (MESSAGEBOX->GetType())
			PARTYHANDLE->JoinRaidRequest();
	}
	void Window::OnDelegatePartyButtonClick(int iIndex)
	{
		if (MESSAGEBOX->GetType())
			PARTYHANDLE->ProcessPacket(&PacketActionParty(PARTYACTION_Delegate, PARTYHANDLE->GetPartyData().saMembers[iIndex].sData.iID));
	}
	void Window::OnKickPartyButtonClick(int iIndex)
	{
		if (MESSAGEBOX->GetType())
			PARTYHANDLE->ProcessPacket(&PacketActionParty(PARTYACTION_Kick, PARTYHANDLE->GetPartyData().saMembers[iIndex].sData.iID));
	}
	void Window::OnLeavePartyButtonClick()
	{
		if (MESSAGEBOX->GetType())
			PARTYHANDLE->ProcessPacket(&PacketActionParty(PARTYACTION_Leave));
	}
	void Window::OnDisbandPartyButtonClick()
	{
		if (MESSAGEBOX->GetType())
			PARTYHANDLE->ProcessPacket(&PacketActionParty(PARTYACTION_Disband));
	}
	void Window::OnChangePartyModeButtonClick()
	{
		if (MESSAGEBOX->GetType())
			PARTYHANDLE->ProcessPacket(&PacketActionParty(PARTYACTION_ChangeMode));
	}
}