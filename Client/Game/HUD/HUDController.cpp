#include "StdAfx.h"
#include "HUDController.h"
#include "tjboy\\clanmenu\\tjclan.h"
#include "tjboy\\clanmenu\\cE_CViewClanInfo.h"

bool RollNumberIsGreater(RollDiceRankingUser & pcRollUser1, RollDiceRankingUser & pcRollUser2) { return pcRollUser1.uNumber > pcRollUser2.uNumber; }

CHUDController::CHUDController()
{
	m_bRenderTarget = FALSE;
	m_pWindowTarget = std::make_shared<UI::Window>(Rectangle2D(0, 0, 425, 80));
	m_pWindowDisplay = std::make_shared<UI::Window>(Rectangle2D(0, 0, 370, 150));
	m_pWindowRollDiceRanking = std::make_shared<UI::Window>(Rectangle2D(0, 0, 379, 124));
	m_pcTooltipWorldTime = std::make_shared<UI::ToolTip>(Rectangle2D());
	m_pFont = FONTHANDLE->MakeFont("Arial", 15, 0, FALSE, FALSE);

	for (int i = 0; i < 3; i++)
		m_pcTooltipBars[i] = std::make_shared<UI::ToolTip>(Rectangle2D());
}
CHUDController::~CHUDController()
{

}
void CHUDController::OnSelectTargetMenu()
{
	auto pMenu = m_pWindowTarget->GetElement<UI::Menu>(DROPDOWNMENU_More);

	if (pMenu)
	{
		int iMenuID = pMenu->GetOptionID();

		if (iMenuID == 1)
		{
			// Request Trade
		}
		else if (iMenuID == 2)
		{
			// Add Friend
		}
		else if (iMenuID == 3)
		{
			// Request party
		}
		else if (iMenuID == 4)
		{
			// Request Raid
		}
		else if (iMenuID == 5)
		{
			// Invite Clan
		}
	}
}
BOOL CHUDController::IsLockItems()
{
	return m_pWindowInventory->GetElement<UI::Button>(BUTTONID_LockItem)->IsSelected();
}

void CHUDController::RenderHPCrystalTower(int iX, int iY, int iMin, int iMax)
{
	if (m_pcaImageCrystalTowerHPBar[0] && m_pcaImageCrystalTowerHPBar[1])
	{
		UI::Image * pc = m_pcaImageCrystalTowerHPBar[0];
		UI::Image * pc1 = m_pcaImageCrystalTowerHPBar[1];

		int iWidth = (iMin * pc->GetWidth()) / iMax;

		UI::ImageRender::Render(pc1, iX - (pc->GetWidth() >> 1) + 60, iY, pc1->GetWidth(), pc1->GetHeight(), 0, 0, -1, 0.75f);
		UI::ImageRender::Render(pc, iX - (pc->GetWidth() >> 1) + 60, iY, iWidth, pc->GetHeight(), 0, 0, -1, 0.75f);

		char szHP[64] = { 0 };
		STRINGFORMAT(szHP, "%d/%d", iMin, iMax);
		int iWidthText = m_pFont->GetWidthText(szHP, STRLEN(szHP));

		m_pFont->Draw((iX)-(iWidthText >> 1) + 18, iY + 1, szHP, DT_WORDBREAK, -1);
	}
}
void CHUDController::UpdateObjectsSettings()
{
	if (m_pWindowTarget)
	{
		m_pWindowTarget->SetCanMove(!SETTINGHANDLE->Get().bLockUI);

		auto pTargetDistance = m_pWindowTarget->GetElement<UI::Text>(TEXTID_Range);

		if (pTargetDistance)
		{
			if (SETTINGHANDLE->Get().bTargetDistance)
				pTargetDistance->Show();
			else
				pTargetDistance->Hide();
		}

		auto pTargetHPValue = m_pWindowTarget->GetElement<UI::Text>(TEXTID_Life);

		if (pTargetHPValue)
		{
			if (SETTINGHANDLE->Get().bTargetHPValue)
				pTargetHPValue->Show();
			else
				pTargetHPValue->Hide();
		}

		auto pTargetHPPercent = m_pWindowTarget->GetElement<UI::Text>(TEXTID_LifePercent);

		if (pTargetHPPercent)
		{
			if (SETTINGHANDLE->Get().bTargetHPPercent)
				pTargetHPPercent->Show();
			else
				pTargetHPPercent->Hide();
		}
	}
}
BOOL CHUDController::UpdateTargetInfo(Unit * pcUnit)
{
	if (!pcUnit)
		return FALSE;

	//Update Everytime the Life
	auto pImageLifeBar = m_pWindowTarget->GetElement<UI::ImageBox>(IMAGEID_LifeBar);
	if (pImageLifeBar)
		pImageLifeBar->SetWidth((pcUnit->sCharacterData.sHP.sMin * 208) / (pcUnit->sCharacterData.sHP.sMax == 0 ? 1 : pcUnit->sCharacterData.sHP.sMax));

	//Update Range Text
	auto pTextRange = m_pWindowTarget->GetElement<UI::Text>(TEXTID_Range);
	if (pTextRange)
	{
		int iDistanceA = 0, iDistanceB = 0, iDistanceC = 0;
		pcUnit->sPosition.GetPTDistanceXZ(&UNIT->sPosition, iDistanceA, iDistanceB, iDistanceC);
		pTextRange->SetTextEx("%d (%dm)", (int)sqrt(iDistanceA), (int)sqrt(iDistanceA) / 27);
	}

	auto pTextLife = m_pWindowTarget->GetElement<UI::Text>(TEXTID_Life);
	if (pTextLife)
	{
		pTextLife->SetTextEx("%d/%d", pcUnit->sHPLong.iMin, pcUnit->sHPLong.iMax);

		//Percent
		auto pTextLifePercent = m_pWindowTarget->GetElement<UI::Text>(TEXTID_LifePercent);
		if (pTextLifePercent)
		{
			if (pcUnit->sHPLong.iMax > 0)
			{
				int iPercent = (pcUnit->sHPLong.iMin * 100) / pcUnit->sHPLong.iMax;
				pTextLifePercent->SetTextEx("%d%%", iPercent);
			}
		}

		if (pcUnit->sHPLong.iMin <= 0 || pcUnit->sCharacterData.sHP.sMin <= 0)
		{
			m_pcLastUnitDataTarget = NULL;
			m_iTargetID = 0;
			return FALSE;
		}
	}

	BOOL bSameTarget = FALSE;
	//Same Target? So don't update it
	if ((((pcUnit->sCharacterData.iType == CHARACTERTYPE_Player || pcUnit->iCharacterType == CHARACTERTYPE_Player) || pcUnit->sCharacterData.iType == CHARACTERTYPE_NPC) && m_iTargetID == pcUnit->iID) ||
		(pcUnit->iCharacterType != CHARACTERTYPE_Player && pcUnit->sCharacterData.iType == CHARACTERTYPE_Monster && m_iTargetID == pcUnit->sCharacterData.iMonsterEffectID))
		bSameTarget = TRUE;

	//ClanInfo * psClanInfo = (ClanInfo*)0x03AA4608;
	CLANINFO * psClanInfo =  ClanInfo;

	if (bSameTarget == FALSE)
	{
		m_bLoadClan16 = FALSE;
		m_bLoadClan32 = FALSE;
	}

	//Clan Name and Icon
	auto pWindowTargetInfo = m_pWindowTarget->GetElement<UI::Window>(WINDOWID_TargetInfo);
	if (pcUnit->sCharacterData.iClanID && pcUnit->iClanInfoIndex > 0 && pWindowTargetInfo && (m_bLoadClan16 == FALSE))
	{
		pWindowTargetInfo->Show();

		//Clan Name
		auto pTextTargetInfo = pWindowTargetInfo->GetElement<UI::Text>(TEXTID_TargetInfo);
		if (pTextTargetInfo)
			pTextTargetInfo->SetText(psClanInfo[pcUnit->iClanInfoIndex].ClanInfoHeader.ClanName);

		//Clan Icon
		auto pImageClanIcon = pWindowTargetInfo->GetElement<UI::ImageBox>(IMAGEID_ClanIcon);
		if (pImageClanIcon)
		{
			if (psClanInfo[pcUnit->iClanInfoIndex].hClanMark)
			{
				if (FILEEXIST(psClanInfo[pcUnit->iClanInfoIndex].hClanMark->Name))
				{
					if (pImageClanIcon->GetImage())
						UI::ImageLoader::DeleteImage(pImageClanIcon->GetImage());

					pImageClanIcon->SetImage(UI::ImageLoader::LoadImage_(psClanInfo[pcUnit->iClanInfoIndex].hClanMark->Name));

					m_bLoadClan16 = TRUE;
				}
			}
		}
	}
	else if (pWindowTargetInfo)
		pWindowTargetInfo->Hide();

	//Clan Info
	auto pCharacterInfoWindow = m_pWindowTarget->GetElement<UI::Window>(WINDOWID_CharacterInfo);
	if (pCharacterInfoWindow && (m_bLoadClan32 == FALSE))
	{
		auto pImageClanIcon = pCharacterInfoWindow->GetElement<UI::ImageBox>(IMAGEID_ClanIcon);
		if (pImageClanIcon)
		{
			if (psClanInfo[pcUnit->iClanInfoIndex].hClanMark32)
			{
				if (FILEEXIST(psClanInfo[pcUnit->iClanInfoIndex].hClanMark32->Name))
				{
					if (pImageClanIcon->GetImage())
						UI::ImageLoader::DeleteImage(pImageClanIcon->GetImage());

					pImageClanIcon->SetImage(UI::ImageLoader::LoadImage_(psClanInfo[pcUnit->iClanInfoIndex].hClanMark32->Name));

					m_bLoadClan32 = TRUE;
				}
			}
		}

		auto pTextClanInfo = pCharacterInfoWindow->GetElement<UI::Text>(TEXTID_ClanInfo);
		if (pTextClanInfo)
			pTextClanInfo->SetText(trim(std::string(psClanInfo[pcUnit->iClanInfoIndex].ClanInfoHeader.ClanReport)));
	}

	//Same Target? So don't update it
	if (bSameTarget)
		return FALSE;

	//Update Target Name
	auto pTextName = m_pWindowTarget->GetElement<UI::Text>(TEXTID_Name);
	if (pTextName)
		pTextName->SetText(pcUnit->sCharacterData.szName);

	//Update Target Level
	auto pTextLevel = m_pWindowTarget->GetElement<UI::Text>(TEXTID_Level);
	if (pTextLevel)
	{
		std::string strLevel = std::to_string(pcUnit->sCharacterData.iLevel);
		bool bLevelType = strLevel.size() > 1 ? true : false;

		if (pcUnit->sCharacterData.iType == CHARACTERTYPE_Player || pcUnit->iCharacterType == CHARACTERTYPE_Player)
			pTextLevel->SetTextEx("%s%c", bLevelType ? strLevel.substr(0, strLevel.size() - 1).c_str() : strLevel.c_str(), bLevelType ? 'x' : NULL);
		else
			pTextLevel->SetTextEx("%s", strLevel.c_str());
	}

	//Show button more if it's a Player
	auto pButtonMore = m_pWindowTarget->GetElement<UI::Button>(BUTTONID_More);
	if (pButtonMore)
	{
		if (pcUnit->sCharacterData.iType == CHARACTERTYPE_Player || pcUnit->iCharacterType == CHARACTERTYPE_Player)
			pButtonMore->Show();
		else
			pButtonMore->Hide();
	}

	//Update Dropdown Menu
	auto pDropdownMenu = m_pWindowTarget->GetElement<UI::Menu>(DROPDOWNMENU_More);
	if (pDropdownMenu)
	{
		if (pcUnit->iID != m_iTargetID)
			pDropdownMenu->Close();

		pDropdownMenu->Clear();

		//Enemy 
		if (pcUnit->sCharacterData.iType != CHARACTERTYPE_Monster)
			pDropdownMenu->AddOption(pDropdownMenu->MakeOption("Trade", Rectangle2D(13, 5, 77, 18), FALSE, -1, D3DCOLOR_XRGB(230, 180, 150)), FALSE, 1);

		//Others Options
		pDropdownMenu->AddOption(pDropdownMenu->MakeOption("Add Friend", Rectangle2D(13, 5, 77, 18), FALSE, -1, D3DCOLOR_XRGB(230, 180, 150)), FALSE, 2);
		pDropdownMenu->AddOption(pDropdownMenu->MakeOption("Party", Rectangle2D(13, 5, 77, 18), FALSE, -1, D3DCOLOR_XRGB(230, 180, 150)), FALSE, 3);

		//Raid
		if (pcUnit && pcUnit->bPartyLeader)
		{
			if (UNIT->bPartyLeader && pcUnit->bPartyLeader)
				pDropdownMenu->AddOption(pDropdownMenu->MakeOption("Raid", Rectangle2D(13, 5, 77, 18), FALSE, -1, D3DCOLOR_XRGB(230, 180, 150)), FALSE, 4);
		}
		//It's a Clan Leader? So show the option to invite for clan
		if ((cldata.myPosition == 101 || cldata.myPosition == 104) && !pcUnit->sCharacterData.iClanID)
			pDropdownMenu->AddOption(pDropdownMenu->MakeOption("Clan", Rectangle2D(13, 5, 77, 18), FALSE, -1, D3DCOLOR_XRGB(230, 180, 150)), FALSE, 5);
	}

	//Update Tooltip of Unit type
	auto pTooltipType = m_pWindowTarget->GetElement<UI::ToolTip>(TOOLTIP_TargetType);
	auto pImageType = m_pWindowTarget->GetElement<UI::ImageBox>(IMAGEID_Type);
	if (pImageType && pTooltipType)
	{
		if (pcUnit->sCharacterData.iType == CHARACTERTYPE_Monster)
		{
			if (pcUnit->sCharacterData.iMonsterType == MONSTERTYPE_Demon)
			{
				pImageType->SetImage(m_pcaImageTargetType[TARGETTYPE_Demon]);
				pTooltipType->SetText("Demon");
			}
			else if (pcUnit->sCharacterData.iMonsterType == MONSTERTYPE_Mechanic)
			{
				pImageType->SetImage(m_pcaImageTargetType[TARGETTYPE_Mechanic]);
				pTooltipType->SetText("Mechanic");
			}
			else if (pcUnit->sCharacterData.iMonsterType == MONSTERTYPE_Mutant)
			{
				pImageType->SetImage(m_pcaImageTargetType[TARGETTYPE_Mutant]);
				pTooltipType->SetText("Mutant");
			}
			else if (pcUnit->sCharacterData.iMonsterType == MONSTERTYPE_Undead)
			{
				pImageType->SetImage(m_pcaImageTargetType[TARGETTYPE_Undead]);
				pTooltipType->SetText("Undead");
			}
			else if (pcUnit->sCharacterData.iMonsterType == MONSTERTYPE_Normal)
			{
				pImageType->SetImage(m_pcaImageTargetType[TARGETTYPE_Normal]);
				pTooltipType->SetText("Normal");
			}
		}
		else if (pcUnit->sCharacterData.iMonsterType == MONSTERTYPE_Friendly)
		{
			pImageType->SetImage(m_pcaImageTargetType[TARGETTYPE_NPC]);
			pTooltipType->SetText("Friendly");
		}
		else if (pcUnit->sCharacterData.iType == CHARACTERTYPE_NPC)
		{
			pImageType->SetImage(m_pcaImageTargetType[TARGETTYPE_NPC]);
			pTooltipType->SetText("NPC");
		}
		else if (pcUnit->sCharacterData.iType == CHARACTERTYPE_Player || pcUnit->iCharacterType == CHARACTERTYPE_Player)
		{
			pImageType->SetImage(m_pcaImageTargetType[TARGETTYPE_Player]);
			pTooltipType->SetText("Player");
		}
	}

	//Update Last Target
	m_iTargetID = pcUnit->iCharacterType == CHARACTERTYPE_Monster ? pcUnit->sCharacterData.iMonsterEffectID : pcUnit->iID;
	m_pcLastUnitDataTarget = pcUnit;

	return FALSE;
}
void CHUDController::SetRenderTarget(BOOL b)
{
	m_bRenderTarget = b;
	if (b == FALSE)
		m_pcLastUnitDataTarget = NULL;
}
void CHUDController::HandlePacket(PacketRollDiceRanking * psPacket)
{
	if (!psPacket)
		return;

	if (psPacket->szCharacterName[0] != 0)
	{
		m_vRollDiceRanking.push_back(RollDiceRankingUser(psPacket->szCharacterName, psPacket->uNumber));
		std::sort(m_vRollDiceRanking.begin(), m_vRollDiceRanking.end(), RollNumberIsGreater);

		auto pListRankingLeft = m_pWindowRollDiceRanking->GetElement<UI::List>(LISTID_RankingLeft);
		auto pListRankingRight = m_pWindowRollDiceRanking->GetElement<UI::List>(LISTID_RankingRight);

		if (pListRankingLeft && pListRankingRight)
		{
			ClearRollDiceRanking();

			for (size_t i = 0; i < m_vRollDiceRanking.size(); i++)
			{
				auto pWindowPlayer = i < 5 ? pListRankingLeft->GetWindow(WINDOWID_Player1 + i) : pListRankingRight->GetWindow(WINDOWID_Player1 + (i - 5));

				if (pWindowPlayer)
				{
					auto pTextCharacterName = i < 5 ? pWindowPlayer->GetElement<UI::Text>(TEXTID_CharacterNick1 + i) : pWindowPlayer->GetElement<UI::Text>(TEXTID_CharacterNick1 + i - 5);
					auto pTextNumber = i < 5 ? pWindowPlayer->GetElement<UI::Text>(TEXTID_Number1 + i) : pWindowPlayer->GetElement<UI::Text>(TEXTID_Number1 + i - 5);

					if (pTextCharacterName && pTextNumber)
					{
						pTextCharacterName->SetText(m_vRollDiceRanking[i].szCharacterName);
						pTextNumber->SetTextEx("%d", m_vRollDiceRanking[i].uNumber);
					}
				}
			}
		}
	}
}
void CHUDController::ClearRollDiceRanking(BOOL bResetVetor)
{
	if (bResetVetor)
		m_vRollDiceRanking.clear();

	auto pListRankingLeft = m_pWindowRollDiceRanking->GetElement<UI::List>(LISTID_RankingLeft);
	auto pListRankingRight = m_pWindowRollDiceRanking->GetElement<UI::List>(LISTID_RankingRight);

	if (pListRankingLeft && pListRankingRight)
	{
		for (size_t i = 0; i < 10; i++)
		{
			auto pWindowPlayer = i < 5 ? pListRankingLeft->GetWindow(WINDOWID_Player1 + i) : pListRankingRight->GetWindow(WINDOWID_Player1 + (i - 5));

			if (pWindowPlayer)
			{
				auto pTextCharacterName = i < 5 ? pWindowPlayer->GetElement<UI::Text>(TEXTID_CharacterNick1 + i) : pWindowPlayer->GetElement<UI::Text>(TEXTID_CharacterNick1 + i - 5);
				auto pTextNumber = i < 5 ? pWindowPlayer->GetElement<UI::Text>(TEXTID_Number1 + i) : pWindowPlayer->GetElement<UI::Text>(TEXTID_Number1 + i - 5);

				if (pTextCharacterName && pTextNumber)
				{
					pTextCharacterName->SetText("");
					pTextNumber->SetText("");
				}
			}
		}
	}
}
void CHUDController::BuildTargetWindow1()
{
	m_pWindowTarget->SetMoveBox(m_pWindowTarget->GetBox());
	m_pWindowTarget->SetCanMove(!SETTINGHANDLE->Get().bLockUI);

	//Dropdown Menu
	UI::LPMENU pDropdownMenu = std::make_shared<UI::Menu>(Rectangle2D(301, 16, 94, 24));
	pDropdownMenu->SetID(DROPDOWNMENU_More);
	pDropdownMenu->SetMenuPosition(UI::EMENUPOSITION_Left);
	pDropdownMenu->SetEvent(UI::Event::Build(std::bind(&CHUDController::OnSelectTargetMenu, this)));
	pDropdownMenu->SetBackground("Resources\\UI\\menu\\topleft.png", "Resources\\UI\\menu\\middle.png", "Resources\\UI\\menu\\bottom.png", "Resources\\UI\\menu\\main.png");
	m_pWindowTarget->AddElement(pDropdownMenu);

	//Background Target Info
	UI::LPWINDOW pWindowTargetInfo = std::make_shared<UI::Window>(Rectangle2D(41, 52, 229, 22));
	pWindowTargetInfo->SetID(WINDOWID_TargetInfo);
	{
		UI::LPIMAGEBOX pImageBackgroundTargetInfo = std::make_shared<UI::ImageBox>(Rectangle2D(0, 0, 229, 22));
		pImageBackgroundTargetInfo->SetID(IMAGEID_TargetInfo);
		pImageBackgroundTargetInfo->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\hud\\target\\targetinfo.png"));
		pWindowTargetInfo->AddElement(pImageBackgroundTargetInfo);

		UI::LPTEXT pTextTargetInfo = std::make_shared<UI::Text>(Rectangle2D(65, 4, 150, 18));
		pTextTargetInfo->SetFont("Arial", 15, 0, FALSE, FALSE, D3DCOLOR_XRGB(180, 180, 125));
		pTextTargetInfo->SetID(TEXTID_TargetInfo);
		pTextTargetInfo->SetDropdownShadow(TRUE);
		pTextTargetInfo->SetDropdownColor(D3DCOLOR_XRGB(0, 0, 0));
		pTextTargetInfo->SetNoClip(TRUE);
		pWindowTargetInfo->AddElement(pTextTargetInfo);

		UI::LPIMAGEBOX pImageIconClan = std::make_shared<UI::ImageBox>(Rectangle2D(45, 4, 16, 16));
		pImageIconClan->SetID(IMAGEID_ClanIcon);
		pWindowTargetInfo->AddElement(pImageIconClan);
	}

	pWindowTargetInfo->Hide();
	m_pWindowTarget->AddElement(pWindowTargetInfo);

	//Character Info
	UI::LPWINDOW pWindowCharacterInfo = std::make_shared<UI::Window>(Rectangle2D(52, 76, 210, 59));
	pWindowCharacterInfo->SetID(WINDOWID_CharacterInfo);
	pWindowCharacterInfo->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\hud\\target\\infobackground.png"));
	{
		UI::LPIMAGEBOX pImageIconClan = std::make_shared<UI::ImageBox>(Rectangle2D(13, 15, 32, 32));
		pImageIconClan->SetID(IMAGEID_ClanIcon);
		pWindowCharacterInfo->AddElement(pImageIconClan);

		UI::LPTEXT pTextClanInfo = std::make_shared<UI::Text>(Rectangle2D(55, 16, 140, 32));
		pTextClanInfo->SetFont("Arial", 15, 0, FALSE, FALSE, -1);
		pTextClanInfo->SetID(TEXTID_ClanInfo);
		pTextClanInfo->SetMultiLine(TRUE);
		pTextClanInfo->SetWordWrap(TRUE);
		pTextClanInfo->SetNoClip(TRUE);
		pWindowCharacterInfo->AddElement(pTextClanInfo);
	}
	pWindowCharacterInfo->Hide();
	m_pWindowTarget->AddElement(pWindowCharacterInfo);

	//Background Image
	UI::LPIMAGEBOX pImageBackgroundHead = std::make_shared<UI::ImageBox>(Rectangle2D(7, 11, 59, 59));
	pImageBackgroundHead->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\hud\\target\\targetbackground.png"));
	m_pWindowTarget->AddElement(pImageBackgroundHead);

	//Overlay
	UI::LPIMAGEBOX pImageOverlayTarget = std::make_shared<UI::ImageBox>(Rectangle2D(0, 0, 301, 80));
	pImageOverlayTarget->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\hud\\target\\targetoverlay.png"));
	m_pWindowTarget->AddElement(pImageOverlayTarget);

	//Life
	UI::LPIMAGEBOX pImageLifeBar = std::make_shared<UI::ImageBox>(Rectangle2D(82, 39, 208, 12));
	pImageLifeBar->SetID(IMAGEID_LifeBar);
	pImageLifeBar->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\hud\\target\\targethp.png"));
	m_pWindowTarget->AddElement(pImageLifeBar);

	//Type
	UI::LPIMAGEBOX pImageType = std::make_shared<UI::ImageBox>(Rectangle2D(62, 34, 16, 16));
	pImageType->SetID(IMAGEID_Type);
	pImageType->SetImage(m_pcaImageTargetType[TARGETTYPE_NPC]);
	m_pWindowTarget->AddElement(pImageType);

	//Name of Unit
	UI::LPTEXT pTextName = std::make_shared<UI::Text>(Rectangle2D(88, 21, 195, 18));
	pTextName->SetFont("Arial", 15, 0, FALSE, FALSE, -1);
	pTextName->SetID(TEXTID_Name);
	pTextName->SetHorizontalAlign(ALIGN_Center);
	pTextName->SetDropdownShadow(TRUE);
	pTextName->SetDropdownColor(D3DCOLOR_XRGB(0, 0, 0));
	pTextName->SetNoClip(TRUE);
	m_pWindowTarget->AddElement(pTextName);

	//Life of Unit
	UI::LPTEXT pTextLife = std::make_shared<UI::Text>(Rectangle2D(84, 38, 204, 14));
	pTextLife->SetFont("Arial", 13, 0, FALSE, FALSE, -1);
	pTextLife->SetID(TEXTID_Life);
	pTextLife->SetHorizontalAlign(ALIGN_Center);
	pTextLife->SetNoClip(TRUE);
	m_pWindowTarget->AddElement(pTextLife);

	//Level of Unit
	UI::LPTEXT pTextLevel = std::make_shared<UI::Text>(Rectangle2D(10, 29, 52, 30));
	pTextLevel->SetFont("Frutiger LT 55 Roman", 26, 0, FALSE, TRUE, -1);
	pTextLevel->SetID(TEXTID_Level);
	pTextLevel->SetColor(D3DCOLOR_XRGB(227, 191, 152));
	pTextLevel->SetHorizontalAlign(ALIGN_Center);
	pTextLevel->SetNoClip(TRUE);
	m_pWindowTarget->AddElement(pTextLevel);

	//Life Percent
	UI::LPTEXT pTextLifePercent = std::make_shared<UI::Text>(Rectangle2D(0, 37, 288, 20));
	pTextLifePercent->SetFont("Arial", 14, 0, FALSE, FALSE, -1);
	pTextLifePercent->SetID(TEXTID_LifePercent);
	pTextLifePercent->SetHorizontalAlign(ALIGN_Right);
	pTextLifePercent->SetNoClip(TRUE);
	m_pWindowTarget->AddElement(pTextLifePercent);

	//Range
	UI::LPTEXT pTextRange = std::make_shared<UI::Text>(Rectangle2D(0, 56, 293, 20));
	pTextRange->SetFont("Arial", 16, 0, FALSE, FALSE, -1);
	pTextRange->SetID(TEXTID_Range);
	pTextRange->SetHorizontalAlign(ALIGN_Right);
	pTextRange->SetNoClip(TRUE);
	m_pWindowTarget->AddElement(pTextRange);

	//More Button
	UI::LPBUTTON pButtonMore = std::make_shared<UI::Button>(Rectangle2D(262, 16, 25, 25));
	pButtonMore->SetID(BUTTONID_More);
	pButtonMore->SetActiveImage(UI::ImageLoader::LoadActiveImage("Resources\\UI\\hud\\target\\more.png", "game\\images\\UI\\hud\\target\\more_.png"));
	pButtonMore->SetMenu(pDropdownMenu);
	m_pWindowTarget->AddElement(pButtonMore);

	//Tooltip of Target Type
	UI::LPTOOLTIP pTooltipType = std::make_shared<UI::ToolTip>(Rectangle2D());
	pTooltipType->Init();
	pTooltipType->SetID(TOOLTIP_TargetType);
	pTooltipType->SetLinkObject(pImageType);
	pTooltipType->SetFont("Arial", 16, -1);
	pTooltipType->SetPosition(TOOLTIPPOSITION_Top);
	pTooltipType->SetFollowMouse(FALSE);
	m_pWindowTarget->AddElement(pTooltipType);
}
void CHUDController::BuildDisplayWindow1()
{
	m_pWindowDisplay->SetMoveBox(m_pWindowDisplay->GetBox());
	m_pWindowDisplay->SetCanMove(TRUE);

	UI::LPIMAGEBOX pImageLeftSkill = std::make_shared<UI::ImageBox>(Rectangle2D(145, 0, 35, 35));
	pImageLeftSkill->SetID(1);
	m_pWindowDisplay->AddElement(pImageLeftSkill);

	for (size_t i = 0; i < 8; i++)
	{
		UI::LPIMAGEBOX pImageSkill = std::make_shared<UI::ImageBox>(Rectangle2D((i == 4 ? 230 : 0) + (35 * i), 0, 35, 35));
		pImageSkill->SetID(2 + i);
		m_pWindowDisplay->AddElement(pImageSkill);
	}

	m_pWindowDisplay->Hide();
}
void CHUDController::BuildDiceRollRankingWindow1()
{
	m_pWindowRollDiceRanking->SetImage(UI::ImageLoader::LoadImage_("Resources\\diceroll\\background.png"));

	UI::LPIMAGEBOX pDivRankingImage = std::make_shared<UI::ImageBox>(Rectangle2D(7, 23, 365, 95));
	pDivRankingImage->SetImage(UI::ImageLoader::LoadImage_("Resources\\diceroll\\div.png"));
	m_pWindowRollDiceRanking->AddElement(pDivRankingImage);

	UI::LPTEXT pTextLabel = std::make_shared<UI::Text>(Rectangle2D(0, 4, 379, 23));
	pTextLabel->SetText("TOP ROLLS");
	pTextLabel->SetFont("Arial", 15, 0, FALSE, TRUE, D3DCOLOR_XRGB(200, 190, 150));
	pTextLabel->SetNoClip(TRUE);
	pTextLabel->SetHorizontalAlign(ALIGN_Center);
	m_pWindowRollDiceRanking->AddElement(pTextLabel);

	//Labels Ranking
	for (size_t i = 0; i < 2; i++)
	{
		UI::LPTEXT pTextID = std::make_shared<UI::Text>(Rectangle2D(7 + (192 * i), 24, 20, 15));
		pTextID->SetText("#");
		pTextID->SetFont("Arial", 13, 0, FALSE, TRUE, -1);
		pTextID->SetNoClip(TRUE);
		pTextID->SetHorizontalAlign(ALIGN_Center);
		m_pWindowRollDiceRanking->AddElement(pTextID);

		UI::LPTEXT pTextCharacterNick = std::make_shared<UI::Text>(Rectangle2D(33 + (192 * i), 24, 0, 0));
		pTextCharacterNick->SetText("Character Name");
		pTextCharacterNick->SetFont("Arial", 13, 0, FALSE, TRUE, -1);
		pTextCharacterNick->SetNoClip(TRUE);
		m_pWindowRollDiceRanking->AddElement(pTextCharacterNick);

		UI::LPTEXT pTextNumber = std::make_shared<UI::Text>(Rectangle2D(134 + (192 * i), 24, 0, 0));
		pTextNumber->SetText("Number");
		pTextNumber->SetFont("Arial", 13, 0, FALSE, TRUE, -1);
		pTextNumber->SetNoClip(TRUE);
		m_pWindowRollDiceRanking->AddElement(pTextNumber);
	}

	UI::LPLIST pRankingListLeft = std::make_shared<UI::List>(Rectangle2D(7, 38, 173, 95));
	pRankingListLeft->SetID(LISTID_RankingLeft);
	pRankingListLeft->SetPaddingSeparator(1);
	m_pWindowRollDiceRanking->AddElement(pRankingListLeft);

	UI::LPLIST pRankingListRight = std::make_shared<UI::List>(Rectangle2D(199, 38, 173, 95));
	pRankingListRight->SetID(LISTID_RankingRight);
	pRankingListRight->SetPaddingSeparator(1);
	m_pWindowRollDiceRanking->AddElement(pRankingListRight);

	//Ranking Player
	for (size_t i = 0; i < 5; i++)
	{
		UI::LPWINDOW pWindowPlayer = std::make_shared<UI::Window>(Rectangle2D(0, 0, 174, 15));
		pWindowPlayer->SetID(WINDOWID_Player1 + i);

		UI::LPTEXT pTextID = std::make_shared<UI::Text>(Rectangle2D(0, 1, 20, 15));
		pTextID->SetText(std::to_string(i + 1));
		pTextID->SetFont("Arial", 13, 0, FALSE, TRUE, D3DCOLOR_XRGB(192, 144, 97));
		pTextID->SetNoClip(TRUE);
		pTextID->SetHorizontalAlign(ALIGN_Center);
		pWindowPlayer->AddElement(pTextID);

		UI::LPTEXT pTextCharacterNick = std::make_shared<UI::Text>(Rectangle2D(26, 1, 0, 0));
		pTextCharacterNick->SetID(TEXTID_CharacterNick1 + i);
		pTextCharacterNick->SetText("");
		pTextCharacterNick->SetFont("Arial", 13, 0, FALSE, TRUE, D3DCOLOR_XRGB(192, 144, 97));
		pTextCharacterNick->SetNoClip(TRUE);
		pWindowPlayer->AddElement(pTextCharacterNick);

		UI::LPTEXT pTextNumber = std::make_shared<UI::Text>(Rectangle2D(127, 1, 0, 0));
		pTextNumber->SetID(TEXTID_Number1 + i);
		pTextNumber->SetText("");
		pTextNumber->SetFont("Arial", 13, 0, FALSE, TRUE, D3DCOLOR_XRGB(192, 144, 97));
		pTextNumber->SetNoClip(TRUE);
		pWindowPlayer->AddElement(pTextNumber);

		pRankingListLeft->AddWindow(pWindowPlayer);
	}

	//Ranking Player
	for (size_t i = 0; i < 5; i++)
	{
		UI::LPWINDOW pWindowPlayer = std::make_shared<UI::Window>(Rectangle2D(0, 0, 174, 15));
		pWindowPlayer->SetID(WINDOWID_Player1 + i);

		UI::LPTEXT pTextID = std::make_shared<UI::Text>(Rectangle2D(0, 1, 20, 15));
		pTextID->SetText(std::to_string(i + 6));
		pTextID->SetFont("Arial", 13, 0, FALSE, TRUE, D3DCOLOR_XRGB(192, 144, 97));
		pTextID->SetNoClip(TRUE);
		pTextID->SetHorizontalAlign(ALIGN_Center);
		pWindowPlayer->AddElement(pTextID);

		UI::LPTEXT pTextCharacterNick = std::make_shared<UI::Text>(Rectangle2D(26, 1, 0, 0));
		pTextCharacterNick->SetID(TEXTID_CharacterNick1 + i);
		pTextCharacterNick->SetText("");
		pTextCharacterNick->SetFont("Arial", 13, 0, FALSE, TRUE, D3DCOLOR_XRGB(192, 144, 97));
		pTextCharacterNick->SetNoClip(TRUE);
		pWindowPlayer->AddElement(pTextCharacterNick);

		UI::LPTEXT pTextNumber = std::make_shared<UI::Text>(Rectangle2D(127, 1, 0, 0));
		pTextNumber->SetID(TEXTID_Number1 + i);
		pTextNumber->SetText("");
		pTextNumber->SetFont("Arial", 13, 0, FALSE, TRUE, D3DCOLOR_XRGB(192, 144, 97));
		pTextNumber->SetNoClip(TRUE);
		pWindowPlayer->AddElement(pTextNumber);

		pRankingListRight->AddWindow(pWindowPlayer);
	}

	UI::LPTEXT pTextClose = std::make_shared<UI::Text>(Rectangle2D(360, 4, 16, 16));
	pTextClose->SetText("X");
	pTextClose->SetFont("Arial", 15, 0, FALSE, TRUE, UI::Color(255, 175, 175, 175).Get());
	pTextClose->SetEvent(UI::Event::Build(std::bind(&CHUDController::CloseDiceRollRanking, this)));
	pTextClose->SetColorHover(-1);
	pTextClose->SetNoClip(TRUE);
	m_pWindowRollDiceRanking->AddElement(pTextClose);
}

void CHUDController::OnAcceptTradeRequest(int iTargetID)
{
	if (MESSAGEBOX->GetType())
		SendRequestTrade(iTargetID, 1);
}
BOOL CHUDController::IsWindowOldHUDOpen()
{
	if (cWareHouse.OpenFlag ||
		cTrade.OpenFlag ||
		cShop.OpenFlag ||
		cAging.OpenFlag ||
		cCraftItem.OpenFlag ||
		sSinWarpGate.ShowFlag ||
		cSinHelp.NPCTeleportFlag ||
		isDrawClanMenu ||
		haMovieFlag ||
		SmeltingItem.OpenFlag ||
		ManufactureItem.m_OpenFlag ||
		cMixtureReset.OpenFlag ||
		cElement.OpenFlag ||
		cCaravan.OpenFlag ||
		cSocket.OpenFlag)
		return TRUE;

	return FALSE;
}