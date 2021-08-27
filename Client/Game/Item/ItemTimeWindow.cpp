#include "StdAfx.h"
#include "ItemTimeWindow.h"

namespace ITEMTIME
{
	ItemTimer::ItemTimer(EItemTimerType eType, const char *pszTitle, const char *pszDescript) : m_eType(eType), m_strTitle(pszTitle), m_strDescription(pszDescript)
	{
		m_sPosition = Rectangle2D(RESOLUTION_WIDTH, POS_ITMTMRBASEY, ITEMTIMER_WIDTH, ITEMTIMER_HEIGHT);
		m_sMoveTo = Rectangle2D(0, 0, ITEMTIMER_WIDTH, ITEMTIMER_HEIGHT);
	}
	ItemTimer::ItemTimer(ItemTimer *pItemTimer, DWORD dwTimeLeft, DWORD dwTimeTotal)
	{
		m_eType = pItemTimer->m_eType;
		m_iFade = pItemTimer->m_iFade;

		m_dwTimeLeft = dwTimeLeft;
		m_dwTimeTotal = dwTimeTotal;

		m_strTitle = pItemTimer->m_strTitle;
		m_strDescription = pItemTimer->m_strDescription;

		m_pcImage = pItemTimer->m_pcImage;
		m_pcImageBackground = pItemTimer->m_pcImageBackground;

		m_sPosition = Rectangle2D(RESOLUTION_WIDTH, POS_ITMTMRBASEY, ITEMTIMER_WIDTH, ITEMTIMER_HEIGHT);
		m_sMoveTo = Rectangle2D(0, 0, ITEMTIMER_WIDTH, ITEMTIMER_HEIGHT);

		m_bView = FALSE;
		m_bFreeze = FALSE;
		m_bAlive = TRUE;
		m_iFade = 0;

		m_vFreezeMaps.swap(pItemTimer->m_vFreezeMaps);
	}
	ItemTimer::~ItemTimer()
	{
		m_vFreezeMaps.clear();
	}
	void ItemTimer::Clear()
	{
		CLEARPTR(m_pcImageBackground);
		CLEARPTR(m_pcImage);

		UI::ImageLoader::DeleteImage(m_pcImageBackground);
		UI::ImageLoader::DeleteImage(m_pcImage);
	}
	void ItemTimer::Render()
	{
		UI::ImageRender::Render(m_pcImageBackground, m_sPosition.iX, m_sPosition.iY, ITEMTIMER_WIDTH, ITEMTIMER_HEIGHT, D3DCOLOR_ARGB(m_iFade, 255, 255, 255));

		float fTimePast = (float)(m_dwTimeTotal - m_dwTimeLeft);
		int iTop = int((fTimePast * ITEMTIMER_HEIGHT) / (float)m_dwTimeTotal);

		if (iTop < ITEMTIMER_HEIGHT)
			UI::ImageRender::Render(m_pcImage, m_sPosition.iX, m_sPosition.iY + iTop, ITEMTIMER_WIDTH, ITEMTIMER_HEIGHT - iTop, 0, iTop, D3DCOLOR_ARGB(m_iFade, 255, 255, 255));
	}
	void ItemTimer::Loop()
	{
		if (m_iFade < ALPHA_HIGH)
			m_iFade++;

		if (m_sMoveTo.iX > m_sPosition.iX)
			m_sPosition.iX++;
		else if (m_sMoveTo.iX < m_sPosition.iX)
			m_sPosition.iX--;

		if (m_sMoveTo.iY > m_sPosition.iY)
			m_sPosition.iY++;
		else if (m_sMoveTo.iY < m_sPosition.iY)
			m_sPosition.iY--;
	}
	void ItemTimer::Tick()
	{
		if (m_dwTimeLeft != 0)
		{
			if (m_bFreeze == FALSE && m_bAlive == TRUE)
			{
				if ((m_dwTimeLeft--) == 0)
					m_bAlive = FALSE;
			}
		}
		else
			m_bAlive = FALSE;
	}
	void ItemTimer::OnMouseMove(class INPUTS::Mouse *pcMouse)
	{
		if (m_sPosition.Equals(&m_sMoveTo) && m_sMoveTo.Inside(pcMouse->GetPosition()))
		{
			if (!m_bView)
			{
				m_bView = TRUE;
			}
		}
		else
		{
			if (m_bView)
			{
				m_bView = FALSE;
			}
		}
	}

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
		ItemTimer * pcEXP = AddTimer(new ItemTimer(ITEMTIMERTYPE_ExpUp, "EXP Potion", "30% Additional Experience"));
		ItemTimer * pcTHE = AddTimer(new ItemTimer(ITEMTIMERTYPE_ThirdEye,  "Third Eye", "One Additional Drop"));
		ItemTimer * pcPH1 = AddTimer(new ItemTimer(ITEMTIMERTYPE_PhoenixFire,  "Phoenix Pet", "Fire Element"));
		ItemTimer * pcPH2 = AddTimer(new ItemTimer(ITEMTIMERTYPE_PhoenixIce,  "Phoenix Pet", "Ice Element"));
		ItemTimer * pcPH3 = AddTimer(new ItemTimer(ITEMTIMERTYPE_PhoenixLightning,  "Phoenix Pet", "Lightning Element"));
		ItemTimer * pcPH4 = AddTimer(new ItemTimer(ITEMTIMERTYPE_PhoenixHeal,  "Phoenix Pet", "Heal Element"));
		ItemTimer * pcMPD = AddTimer(new ItemTimer(ITEMTIMERTYPE_MPDown,  "Mana Down", "Reduces 25% Mana Usage"));
		ItemTimer * pcSPD = AddTimer(new ItemTimer(ITEMTIMERTYPE_SPDown,  "Stamina Down", "Reduces 25% Stamina Usage"));
		ItemTimer * pcHPU = AddTimer(new ItemTimer(ITEMTIMERTYPE_HPUp,  "Vampire Teeth", "+10 HP Regen"));
		ItemTimer * pcMPU = AddTimer(new ItemTimer(ITEMTIMERTYPE_MPUp,  "Mana Aura", "+10 MP Regen"));
		ItemTimer * pcBHN = AddTimer(new ItemTimer(ITEMTIMERTYPE_BigHead,  "Big Head", " "));
		ItemTimer * pcWGS = AddTimer(new ItemTimer(ITEMTIMERTYPE_WeightStone,  "Weight Stone", "+1000 Additional Weight"));
		ItemTimer * pcMTS = AddTimer(new ItemTimer(ITEMTIMERTYPE_MatureStone,  "Mature Stone", " "));
		ItemTimer * pcSKS = AddTimer(new ItemTimer(ITEMTIMERTYPE_SkillStone,  "Skill Stone", " "));
		ItemTimer * pcCLH = AddTimer(new ItemTimer(ITEMTIMERTYPE_CartolaHat,  "Magician Hat", "+10 HP Regen +10 Add HP"));
		ItemTimer * pcWTH = AddTimer(new ItemTimer(ITEMTIMERTYPE_WitchHat,  "Witch Hat", "+10 HP Regen +10 Add HP"));
		ItemTimer * pcSHH = AddTimer(new ItemTimer(ITEMTIMERTYPE_SheepHat,  "Sheep Hat", "Cutie *-* +150 Defense"));
		ItemTimer * pcGFH = AddTimer(new ItemTimer(ITEMTIMERTYPE_GiraffeHat,  "Giraffe Hat", "+75 Attack Rating"));
		ItemTimer * pcSCH = AddTimer(new ItemTimer(ITEMTIMERTYPE_SoccerHat,  "Soccer Hat", "+2 Move Speed"));
		ItemTimer * pcXMG = AddTimer(new ItemTimer(ITEMTIMERTYPE_XMasGreenHat,  "XMas Green Hat", "+2 Move Speed"));
		ItemTimer * pcXMR = AddTimer(new ItemTimer(ITEMTIMERTYPE_XMasRedHat,  "XMas Red Hat", "+50 MP and STM"));
		ItemTimer * pcBHH = AddTimer(new ItemTimer(ITEMTIMERTYPE_BigHeadHappiness,  "Big Head of Happiness", "+50 Attack Rating"));
		ItemTimer * pcBHL = AddTimer(new ItemTimer(ITEMTIMERTYPE_BigHeadLove,  "Big Head of Love", "+10 HP Regen +10 HP"));
		ItemTimer * pcBSD = AddTimer(new ItemTimer(ITEMTIMERTYPE_BigHeadSadness,  "Big Head of Sadness", "+10 MP Regen +10 MP"));
		ItemTimer * pcBSY = AddTimer(new ItemTimer(ITEMTIMERTYPE_BigHeadShyness,  "Big Head of Shyness", "+100 Defense"));
		ItemTimer * pcBHA = AddTimer(new ItemTimer(ITEMTIMERTYPE_BigHeadAngry,  "Big Head of Angry", "+50 HP/MP/STM"));
		ItemTimer * pcBSU = AddTimer(new ItemTimer(ITEMTIMERTYPE_BigHeadSurprised,  "Big Head of Surprised", "+2% Block"));
		ItemTimer * pcBSN = AddTimer(new ItemTimer(ITEMTIMERTYPE_BigHeadSensual,  "Big Head of Sensual", "+2% Critical"));
		ItemTimer * pcBCB = AddTimer(new ItemTimer(ITEMTIMERTYPE_BCBuff,  "PvP Honor", "+100 HP"));

		pcEXP->FreezeMap(MAPID_RicartenTown);
		pcEXP->FreezeMap(MAPID_PhillaiTown);
		pcEXP->FreezeMap(MAPID_Eura);
		pcEXP->FreezeMap(MAPID_BattleTown);
		pcEXP->FreezeMap(MAPID_Atlantis);
		pcEXP->FreezeMap(MAPID_BlessCastle);
		pcEXP->m_pcImage = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\EXP.png");
		pcEXP->m_pcImageBackground = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\EXP_.png");

		pcTHE->FreezeMap(MAPID_RicartenTown);
		pcTHE->FreezeMap(MAPID_PhillaiTown);
		pcTHE->FreezeMap(MAPID_Eura);
		pcTHE->FreezeMap(MAPID_BattleTown);
		pcTHE->FreezeMap(MAPID_Atlantis);
		pcTHE->FreezeMap(MAPID_BlessCastle);
		pcTHE->m_pcImage = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\ThirdEye.png");
		pcTHE->m_pcImageBackground = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\ThirdEye_.png");

		pcPH1->FreezeMap(MAPID_RicartenTown);
		pcPH1->FreezeMap(MAPID_PhillaiTown);
		pcPH1->FreezeMap(MAPID_Eura);
		pcPH1->FreezeMap(MAPID_BattleTown);
		pcPH1->FreezeMap(MAPID_Atlantis);
		pcPH1->FreezeMap(MAPID_BlessCastle);
		pcPH1->m_pcImage = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\PhoenixFire.png");
		pcPH1->m_pcImageBackground = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\PhoenixFire_.png");

		pcPH2->FreezeMap(MAPID_RicartenTown);
		pcPH2->FreezeMap(MAPID_PhillaiTown);
		pcPH2->FreezeMap(MAPID_Eura);
		pcPH2->FreezeMap(MAPID_BattleTown);
		pcPH2->FreezeMap(MAPID_Atlantis);
		pcPH2->FreezeMap(MAPID_BlessCastle);
		pcPH2->m_pcImage = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\PhoenixIce.png");
		pcPH2->m_pcImageBackground = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\PhoenixIce_.png");

		pcPH3->FreezeMap(MAPID_RicartenTown);
		pcPH3->FreezeMap(MAPID_PhillaiTown);
		pcPH3->FreezeMap(MAPID_Eura);
		pcPH3->FreezeMap(MAPID_BattleTown);
		pcPH3->FreezeMap(MAPID_Atlantis);
		pcPH3->FreezeMap(MAPID_BlessCastle);
		pcPH3->m_pcImage = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\PhoenixLightning.png");
		pcPH3->m_pcImageBackground = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\PhoenixLightning_.png");

		pcPH4->FreezeMap(MAPID_RicartenTown);
		pcPH4->FreezeMap(MAPID_PhillaiTown);
		pcPH4->FreezeMap(MAPID_Eura);
		pcPH4->FreezeMap(MAPID_BattleTown);
		pcPH4->FreezeMap(MAPID_Atlantis);
		pcPH4->FreezeMap(MAPID_BlessCastle);
		pcPH4->m_pcImage = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\PhoenixHeal.png");
		pcPH4->m_pcImageBackground = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\PhoenixHeal_.png");

		pcMPD->FreezeMap(MAPID_RicartenTown);
		pcMPD->FreezeMap(MAPID_PhillaiTown);
		pcMPD->FreezeMap(MAPID_Atlantis);
		pcMPD->m_pcImage = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\MPDown.png");
		pcMPD->m_pcImageBackground = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\MPDown_.png");

		pcSPD->FreezeMap(MAPID_RicartenTown);
		pcSPD->FreezeMap(MAPID_PhillaiTown);
		pcSPD->FreezeMap(MAPID_Atlantis);
		pcSPD->m_pcImage = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\SPDown.png");
		pcSPD->m_pcImageBackground = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\SPDown_.png");

		pcHPU->FreezeMap(MAPID_RicartenTown);
		pcHPU->FreezeMap(MAPID_PhillaiTown);
		pcHPU->FreezeMap(MAPID_Atlantis);
		pcHPU->m_pcImage = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\HPUp.png");
		pcHPU->m_pcImageBackground = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\HPUp_.png");

		pcMPU->FreezeMap(MAPID_RicartenTown);
		pcMPU->FreezeMap(MAPID_PhillaiTown);
		pcMPU->FreezeMap(MAPID_Atlantis);
		pcMPU->m_pcImage = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\MPUp.png");
		pcMPU->m_pcImageBackground = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\MPUp_.png");

		pcBHN->FreezeMap(MAPID_RicartenTown);
		pcBHN->FreezeMap(MAPID_PhillaiTown);
		pcBHN->FreezeMap(MAPID_Atlantis);
		pcBHN->m_pcImage = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\BigHead.png");
		pcBHN->m_pcImageBackground = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\BigHead_.png");

		pcWGS->FreezeMap(MAPID_RicartenTown);
		pcWGS->FreezeMap(MAPID_PhillaiTown);
		pcWGS->FreezeMap(MAPID_Atlantis);
		pcWGS->m_pcImage = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\Gravity.png");
		pcWGS->m_pcImageBackground = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\Gravity_.png");

		pcMTS->FreezeMap(MAPID_RicartenTown);
		pcMTS->FreezeMap(MAPID_PhillaiTown);
		pcMTS->FreezeMap(MAPID_Atlantis);
		pcMTS->m_pcImage = NULL;
		pcMTS->m_pcImageBackground = NULL;

		pcSKS->FreezeMap(MAPID_RicartenTown);
		pcSKS->FreezeMap(MAPID_PhillaiTown);
		pcSKS->FreezeMap(MAPID_Atlantis);
		pcSKS->m_pcImage = NULL;
		pcSKS->m_pcImageBackground = NULL;

		pcCLH->FreezeMap(MAPID_RicartenTown);
		pcCLH->FreezeMap(MAPID_PhillaiTown);
		pcCLH->FreezeMap(MAPID_Atlantis);
		pcCLH->m_pcImage = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\MagicianHat.png");
		pcCLH->m_pcImageBackground = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\MagicianHat.png");

		pcWTH->FreezeMap(MAPID_RicartenTown);
		pcWTH->FreezeMap(MAPID_PhillaiTown);
		pcWTH->FreezeMap(MAPID_Atlantis);
		pcWTH->m_pcImage = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\WitchHat.png");
		pcWTH->m_pcImageBackground = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\WitchHat_.png");

		pcSHH->FreezeMap(MAPID_RicartenTown);
		pcSHH->FreezeMap(MAPID_PhillaiTown);
		pcSHH->FreezeMap(MAPID_Atlantis);
		pcSHH->m_pcImage = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\SheepHat.png");
		pcSHH->m_pcImageBackground = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\SheepHat_.png");

		pcGFH->FreezeMap(MAPID_RicartenTown);
		pcGFH->FreezeMap(MAPID_PhillaiTown);
		pcGFH->FreezeMap(MAPID_Atlantis);
		pcGFH->m_pcImage = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\GiraffeHat.png");
		pcGFH->m_pcImageBackground = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\GiraffeHat_.png");

		pcSCH->FreezeMap(MAPID_RicartenTown);
		pcSCH->FreezeMap(MAPID_PhillaiTown);
		pcSCH->FreezeMap(MAPID_Atlantis);
		pcSCH->m_pcImage = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\SoccerHat.png");
		pcSCH->m_pcImageBackground = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\SoccerHat_.png");

		pcXMG->FreezeMap(MAPID_RicartenTown);
		pcXMG->FreezeMap(MAPID_PhillaiTown);
		pcXMG->FreezeMap(MAPID_Atlantis);
		pcXMG->m_pcImage = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\XmasHat.png");
		pcXMG->m_pcImageBackground = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\XmasHat_.png");

		pcXMR->FreezeMap(MAPID_RicartenTown);
		pcXMR->FreezeMap(MAPID_PhillaiTown);
		pcXMR->FreezeMap(MAPID_Atlantis);
		pcXMR->m_pcImage = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\XmasHat.png");
		pcXMR->m_pcImageBackground = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\XmasHat_.png");

		pcBHH->FreezeMap(MAPID_RicartenTown);
		pcBHH->FreezeMap(MAPID_PhillaiTown);
		pcBHH->FreezeMap(MAPID_Atlantis);
		pcBHH->m_pcImage = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\BigHead.png");
		pcBHH->m_pcImageBackground = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\BigHead_.png");

		pcBHL->FreezeMap(MAPID_RicartenTown);
		pcBHL->FreezeMap(MAPID_PhillaiTown);
		pcBHL->FreezeMap(MAPID_Atlantis);
		pcBHL->m_pcImage = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\BigHead.png");
		pcBHL->m_pcImageBackground = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\BigHead_.png");

		pcBSD->FreezeMap(MAPID_RicartenTown);
		pcBSD->FreezeMap(MAPID_PhillaiTown);
		pcBSD->FreezeMap(MAPID_Atlantis);
		pcBSD->m_pcImage = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\BigHead.png");
		pcBSD->m_pcImageBackground = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\BigHead_.png");

		pcBSY->FreezeMap(MAPID_RicartenTown);
		pcBSY->FreezeMap(MAPID_PhillaiTown);
		pcBSY->FreezeMap(MAPID_Atlantis);
		pcBSY->m_pcImage = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\BigHead.png");
		pcBSY->m_pcImageBackground = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\BigHead_.png");

		pcBHA->FreezeMap(MAPID_RicartenTown);
		pcBHA->FreezeMap(MAPID_PhillaiTown);
		pcBHA->FreezeMap(MAPID_Atlantis);
		pcBHA->m_pcImage = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\BigHead.png");
		pcBHA->m_pcImageBackground = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\BigHead_.png");

		pcBSU->FreezeMap(MAPID_RicartenTown);
		pcBSU->FreezeMap(MAPID_PhillaiTown);
		pcBSU->FreezeMap(MAPID_Atlantis);
		pcBSU->m_pcImage = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\BigHead.png");
		pcBSU->m_pcImageBackground = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\BigHead_.png");

		pcBSN->FreezeMap(MAPID_RicartenTown);
		pcBSN->FreezeMap(MAPID_PhillaiTown);
		pcBSN->FreezeMap(MAPID_Atlantis);
		pcBSN->m_pcImage = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\BigHead.png");
		pcBSN->m_pcImageBackground = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\BigHead_.png");

		pcBCB->FreezeMap(MAPID_RicartenTown);
		pcBCB->FreezeMap(MAPID_PhillaiTown);
		pcBCB->FreezeMap(MAPID_Atlantis);
		pcBCB->m_pcImage = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\TopPvp.png");
		pcBCB->m_pcImageBackground = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\TopPvp_.png");

		m_pcFont = FONTHANDLE->MakeFont("Tahoma", 15, 0, FALSE, FALSE);
		m_pcImageBox = UI::ImageLoader::LoadImage_("Resources\\Items\\premium\\box.png");
	}
	void Window::Shutdown()
	{
		for (auto &v : m_pcaItemTimer)
		{
			CLEARPTR(v);
			DELET(v);
		}

		m_pcaItemTimer.clear();

		for (auto &v : m_pcaItemTimerPrefab)
		{
			CLEARPTR(v);
			DELET(v);
		}

		m_pcaItemTimerPrefab.clear();

		CLEARPTR(m_pcImageBox);

		UI::ImageLoader::DeleteImage(m_pcImageBox);
	}
	BOOL Window::AddTimer(EItemTimerType eType, DWORD dwTimeLeft, DWORD dwTimeTotal)
	{
		int iFreeSlot = m_pcaItemTimer.size();

		int iColumn = iFreeSlot / DEFAULT_ITEMS_PER_COLUMN;
		int iRow = iFreeSlot % DEFAULT_ITEMS_PER_COLUMN;

		auto pcTimer = GetItemTimer(eType);

		if (pcTimer)
		{
			if (ItemTimerCanStack(pcTimer->m_eType))
			{
				RemoveTimer(pcTimer);

				int iFreeSlot = m_pcaItemTimer.size();

				int iColumn = iFreeSlot / DEFAULT_ITEMS_PER_COLUMN;
				int iRow = iFreeSlot % DEFAULT_ITEMS_PER_COLUMN;
			}
		}

		if ((pcTimer == NULL) && (ItemTimerIsHead(eType) == TRUE))
			pcTimer = GetHead();

		if (pcTimer == nullptr)
		{
			ItemTimer * pcPrefab = GetPrefab(eType);

			if (pcPrefab)
			{
				ItemTimer *pcItemTimer = new ItemTimer(pcPrefab, dwTimeLeft, dwTimeTotal);

				pcItemTimer->m_iColumn = iColumn;
				pcItemTimer->m_sMoveTo.iX = (RESOLUTION_WIDTH - POS_ITMTMRBASEX) - (iColumn * TMR_SPACEX) - ITEMTIMER_WIDTH;
				pcItemTimer->m_sMoveTo.iY = POS_ITMTMRBASEY + (iRow * TMR_SPACEY);

				m_pcaItemTimer.push_back(pcItemTimer);

				return TRUE;
			}
			else
				CTITLEBOX->SetText("You are already using an item of this type!");
		}

		return FALSE;
	}
	void Window::Loop()
	{
		for (auto &v : m_pcaItemTimer)
		{
			v->Loop();
		}
	}
	void Window::Tick()
	{
		for (auto &v : m_pcaItemTimer)
		{
			v->Tick();

			if (v->m_bAlive == FALSE)
				RemoveTimer(v);
		}
	}
	void Window::Render()
	{
		for (auto &v : m_pcaItemTimer)
		{
			v->Render();

			if (v->m_bView)
			{
				UI::ImageRender::Render(m_pcImageBox, v->m_sMoveTo.iX - m_pcImageBox->GetWidth(), v->m_sMoveTo.iY, m_pcImageBox->GetWidth(), m_pcImageBox->GetHeight(), -1);

				m_pcFont->Draw(v->m_sMoveTo.iX - m_pcImageBox->GetWidth() + 8, v->m_sMoveTo.iY + 6, v->m_strTitle, 0, -1);
				m_pcFont->Draw(v->m_sMoveTo.iX - m_pcImageBox->GetWidth() + 8, v->m_sMoveTo.iY + 22, v->m_strDescription, 0, D3DCOLOR_ARGB(255, 255, 180, 100));

				int iHour = (v->m_dwTimeLeft / 3600);
				int iMinutes = (v->m_dwTimeLeft / 60) % 60;
				int iSeconds = (v->m_dwTimeLeft % 60);

				m_pcFont->Draw(v->m_sMoveTo.iX - m_pcImageBox->GetWidth() + 8, v->m_sMoveTo.iY + 51, FormatString("Time Left: %02d:%02d:%02d", iHour, iMinutes, iSeconds), 0, D3DCOLOR_ARGB(255, 50, 205, 50));
			}
		}
	}
	void Window::OnMouseMove(class INPUTS::Mouse *pcMouse)
	{
		BOOL bRet = FALSE;
		for (auto &v : m_pcaItemTimer)
		{
			v->OnMouseMove(pcMouse);

			if (v->m_bView == TRUE && bRet == FALSE)
			{
				MOUSEHANDLER->BlockMouse();
				bRet = TRUE;
			}
			else if (v->m_bView == FALSE && bRet == TRUE)
			{
				MOUSEHANDLER->UnblockMouse();
				bRet = FALSE;
			}
		}
	}
	BOOL Window::OnMouseClick(class INPUTS::Mouse *pcMouse)
	{
		for (auto &v : m_pcaItemTimer)
		{
			if (v->m_bView == TRUE)
			{
				if (pcMouse->GetEvent() == ClickDownR)
				{
					MESSAGEBOX->SetBoxType(MESSAGE::BOX::Window::BOXTYPEID_YesNo);
					MESSAGEBOX->SetTitle("Are you sure?");
					MESSAGEBOX->SetDescription(FormatString("Do you want to cancel the %s?", v->m_strTitle.c_str()));
					MESSAGEBOX->SetEvent(std::bind(&Window::OnClickCancelOK, this, v, std::placeholders::_1));
					MESSAGEBOX->Show();
					return TRUE;
				}
				else if (pcMouse->GetEvent() == ClickDownL)
				{
					return TRUE;
				}
			}
		}

		return FALSE;
	}
	void Window::OnClickCancelOK(ItemTimer *pcTimer, UIEventArgs eArgs)
	{
		if (MESSAGEBOX->GetType())
		{
			MOUSEHANDLER->UnblockMouse();

			RemoveTimer(pcTimer);
		}
	}
	void Window::RemoveTimer(ItemTimer *pcTimer)
	{
		for (auto it = m_pcaItemTimer.begin(); it != m_pcaItemTimer.end(); it++)
		{
			if (*it == pcTimer)
			{
				DELET(pcTimer);
				m_pcaItemTimer.erase(it);
				break;
			}
		}

		for (int t = 0; t < (int)m_pcaItemTimer.size(); t++)
		{
			int iColumn = t / DEFAULT_ITEMS_PER_COLUMN;
			int iRow = t % DEFAULT_ITEMS_PER_COLUMN;

			m_pcaItemTimer[t]->m_sMoveTo.iX = (RESOLUTION_WIDTH - POS_ITMTMRBASEX) - (iColumn * TMR_SPACEX) - ITEMTIMER_WIDTH;
			m_pcaItemTimer[t]->m_sMoveTo.iY = POS_ITMTMRBASEY + (iRow * TMR_SPACEY);
		}
	}
	void Window::OnResolutionChanged()
	{
		for (auto &v : m_pcaItemTimer)
		{
			v->m_sPosition.iX = (RESOLUTION_WIDTH - POS_ITMTMRBASEX) - (v->m_iColumn * TMR_SPACEX) - ITEMTIMER_WIDTH;
			v->m_sMoveTo.iX = (RESOLUTION_WIDTH - POS_ITMTMRBASEX) - (v->m_iColumn * TMR_SPACEX) - ITEMTIMER_WIDTH;
		}
	}
	ItemTimer *Window::GetItemTimer(EItemTimerType eType)
	{
		for (auto &v : m_pcaItemTimer)
		{
			if (v->m_eType == eType || ItemTimerIsSame(v->m_eType, eType) == TRUE)
				return v;
		}

		return nullptr;
	}
	ItemTimer *Window::GetPrefab(EItemTimerType eType)
	{
		for (auto &v : m_pcaItemTimerPrefab)
		{
			if (v->m_eType == eType)
				return v;
		}

		return nullptr;
	}
	ItemTimer *Window::AddTimer(ItemTimer *pcTimer)
	{
		m_pcaItemTimerPrefab.push_back(pcTimer);

		return pcTimer;
	}
	ItemTimer *Window::GetHead()
	{
		for (auto &v : m_pcaItemTimer)
		{
			if (ItemTimerIsHead(v->m_eType))
				return v;
		}

		return nullptr;
	}
}