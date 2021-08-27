#include "StdAfx.h"
#include "SettingsWindow.h"

namespace SETTING
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
		BuildWindow();
		BuildVideo();
		BuildAudio();
		BuildGeneral();
		BuildInterface();
		m_pWindowMain->Hide();
	}
	void Window::Shutdown()
	{
		m_pWindowMain->Clear();
	}
	void Window::Show()
	{
		MOUSEHANDLER->BlockMouse();
		Load();
		m_pWindowMain->Show();
	}
	void Window::OnResetButtonClick(UIEventArgs eArgs)
	{
		auto pWindowVideo = GetWindow(WINDOWID_Video);
		//video
		//Screen;
		{
			pWindowVideo->GetElement<UI::CheckBox>(CHECKBOXID_AutoAdjust)->SetCheck(TRUE);
			pWindowVideo->GetElement<UI::CheckBox>(CHECKBOXID_StartMaximized)->SetCheck(FALSE);
			pWindowVideo->GetElement<UI::Group>(GROUPID_Display)->SetIndexObject(CHECKBOXID_Windowed);

			pWindowVideo->GetElement<UI::Group>(GROUPID_Ratio)->SetIndexObject(CHECKBOXID_Ratio4_3);
			pWindowVideo->GetElement<UI::Group>(GROUPID_Resolutions16_9)->Hide();
			pWindowVideo->GetElement<UI::Group>(GROUPID_Resolutions4_3)->SetIndexObject(CHECKBOXID_1024x768);
			pWindowVideo->GetElement<UI::Group>(GROUPID_Resolutions4_3)->Show();
		}
		//Graphics
		{
			pWindowVideo->GetElement<UI::Group>(GROUPID_TextureQuality)->SetIndexObject(CHECKBOXID_TextureHigh);
			pWindowVideo->GetElement<UI::Group>(GROUPID_BitDepth)->SetIndexObject(CHECKBOXID_32BPP);
			pWindowVideo->GetElement<UI::Group>(GROUPID_VSync)->SetIndexObject(CHECKBOXID_VSyncON);
			pWindowVideo->GetElement<UI::Group>(GROUPID_Effects)->SetIndexObject(CHECKBOXID_EffectsON);
			pWindowVideo->GetElement<UI::Group>(GROUPID_AntiAliasing)->SetIndexObject(CHECKBOXID_AntiAliasingON);
		}
		//Camera
		{
			pWindowVideo->GetElement<UI::Group>(GROUPID_CameraSight)->SetIndexObject(CHECKBOXID_Far);
			pWindowVideo->GetElement<UI::Group>(GROUPID_InvertedCamera)->SetIndexObject(CHECKBOXID_CameraOFF);
		}

		auto pWindowAudio = GetWindow(WINDOWID_Audio);
		//Audio
		// BG Music
		{
			pWindowAudio->GetElement<UI::Scroll>(SCROLLID_BGMusic)->SetPercent(100);
			pWindowAudio->GetElement<UI::CheckBox>(CHECKBOXID_NoMusic)->SetCheck(FALSE);
		}
		// Effect iSound
		{
			pWindowAudio->GetElement<UI::Scroll>(SCROLLID_EffectSound)->SetPercent(100);
			pWindowAudio->GetElement<UI::CheckBox>(CHECKBOXID_NoEffects)->SetCheck(FALSE);
		}
		//Personalization
		auto pWindowGeneral = GetWindow(WINDOWID_General);
		{
			pWindowGeneral->GetElement<UI::Group>(GROUPID_DamageDebug)->SetIndexObject(CHECKBOXID_DamageDebugON);
			pWindowGeneral->GetElement<UI::Group>(GROUPID_HPBar)->SetIndexObject(CHECKBOXID_HPBarON);
			pWindowGeneral->GetElement<UI::Group>(GROUPID_FPS)->SetIndexObject(CHECKBOXID_FPSOFF);
			pWindowGeneral->GetElement<UI::Group>(GROUPID_Ping)->SetIndexObject(CHECKBOXID_PingOFF);
			pWindowGeneral->GetElement<UI::Group>(GROUPID_KillInfo)->SetIndexObject(CHECKBOXID_KillInfoON);
		}
		{
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootFilterEnable)->SetCheck(TRUE);
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootHPPotion)->SetCheck(TRUE);
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootMPPotion)->SetCheck(TRUE);
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSPPotion)->SetCheck(TRUE);
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootGold)->SetCheck(TRUE);
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootAmulets)->SetCheck(TRUE);
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootRings)->SetCheck(TRUE);
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSheltoms)->SetCheck(TRUE);
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootForceOrbs)->SetCheck(TRUE);
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootPremiums)->SetCheck(TRUE);
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootMonsterCrystals)->SetCheck(TRUE);
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootDefenseItems)->SetCheck(TRUE);
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootOffenseItems)->SetCheck(TRUE);
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootEverything)->SetCheck(TRUE);

			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSpecNS)->SetCheck(TRUE);
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSpecFS)->SetCheck(TRUE);
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSpecMS)->SetCheck(TRUE);
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSpecAS)->SetCheck(TRUE);
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSpecPS)->SetCheck(TRUE);
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSpecATA)->SetCheck(TRUE);
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSpecKS)->SetCheck(TRUE);
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSpecMGS)->SetCheck(TRUE);
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSpecPRS)->SetCheck(TRUE);
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSpecASS)->SetCheck(TRUE);
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSpecSHA)->SetCheck(TRUE);
		}
		//Interface
		auto pWindowInterface = GetWindow(WINDOWID_Interface);
		{
			pWindowInterface->GetElement<UI::CheckBox>(CHECKBOXID_LockUI)->SetCheck(FALSE);
			pWindowInterface->GetElement<UI::CheckBox>(CHECKBOXID_ShowPartyMembers)->SetCheck(TRUE);
			pWindowInterface->GetElement<UI::CheckBox>(CHECKBOXID_ShowRaidMembers)->SetCheck(TRUE);
			pWindowInterface->GetElement<UI::CheckBox>(CHECKBOXID_ShowClanMembers)->SetCheck(TRUE);
			pWindowInterface->GetElement<UI::CheckBox>(CHECKBOXID_ShowEnemies)->SetCheck(TRUE);
			pWindowInterface->GetElement<UI::CheckBox>(CHECKBOXID_ShowNPCs)->SetCheck(TRUE);
			pWindowInterface->GetElement<UI::CheckBox>(CHECKBOXID_AlwaysActive)->SetCheck(TRUE);
			pWindowInterface->GetElement<UI::CheckBox>(CHECKBOXID_ShowNextBossTimer)->SetCheck(TRUE);
			pWindowInterface->GetElement<UI::CheckBox>(CHECKBOXID_ShowNotice)->SetCheck(FALSE);
			pWindowInterface->GetElement<UI::CheckBox>(CHECKBOXID_TargetDistance)->SetCheck(TRUE);
			pWindowInterface->GetElement<UI::CheckBox>(CHECKBOXID_TargetHPValue)->SetCheck(TRUE);
			pWindowInterface->GetElement<UI::CheckBox>(CHECKBOXID_TargetHPPercent)->SetCheck(TRUE);
		}
	}
	void Window::OnSaveButtonClick(UIEventArgs eArgs)
	{
		ITEMTIMEBOX->AddTimer(ITEMTIMERTYPE_ExpUp, ITEMTIMERTIME_1H, ITEMTIMERTIME_1H);
		MESSAGEBOX->LinkObject(m_pWindowMain);
		MESSAGEBOX->SetBoxType(MESSAGE::BOX::Window::BOXTYPEID_YesNo);
		MESSAGEBOX->SetTitle("Save Settings");
		MESSAGEBOX->SetDescription("Do you want to save the changes?");
		MESSAGEBOX->SetEvent(std::bind(&Window::Save, this));
		MESSAGEBOX->SetAutoClose(5);
		MESSAGEBOX->Show();
	}
	void Window::OnCloseButtonClick(UIEventArgs eArgs)
	{
		m_pWindowMain->Hide();
		MOUSEHANDLER->UnblockMouse();
	}
	void Window::OnMenuButtonClick(int iID, UIEventArgs eArgs)
	{
		auto pWindowVideo = GetWindow(WINDOWID_Video);
		auto pWindowAudio = GetWindow(WINDOWID_Audio);
		auto pWindowGeneral = GetWindow(WINDOWID_General);
		auto pWindowInterface = GetWindow(WINDOWID_Interface);

		if (iID == BUTTONID_Video)
		{
			pWindowVideo->Show();
			pWindowAudio->Hide();
			pWindowGeneral->Hide();
			pWindowInterface->Hide();
		}
		else if (iID == BUTTONID_Audio)
		{
			pWindowVideo->Hide();
			pWindowAudio->Show();
			pWindowGeneral->Hide();
			pWindowInterface->Hide();
		}
		else if (iID == BUTTONID_General)
		{
			pWindowVideo->Hide();
			pWindowAudio->Hide();
			pWindowGeneral->Show();
			pWindowInterface->Hide();
		}
		else if (iID == BUTTONID_Interface)
		{
			pWindowVideo->Hide();
			pWindowAudio->Hide();
			pWindowGeneral->Hide();
			pWindowInterface->Show();
		}
	}
	void Window::OnCheckBoxRatioClick(int iID, UIEventArgs eArgs)
	{
		auto pWindowVideo = GetWindow(WINDOWID_Video);
		auto pGroupRatio = pWindowVideo->GetElement<UI::Group>(GROUPID_Ratio);
		auto pGroupResolution4_3 = pWindowVideo->GetElement<UI::Group>(GROUPID_Resolutions4_3);
		auto pGroupResolution16_9 = pWindowVideo->GetElement<UI::Group>(GROUPID_Resolutions16_9);

		if (iID == CHECKBOXID_Ratio4_3)
		{
			pGroupRatio->SetIndexObject(iID);
			pGroupResolution4_3->SetIndexObject(GetResolutionCheckBox());
			pGroupResolution4_3->Show();
			pGroupResolution16_9->Hide();
		}
		else
		{
			pGroupRatio->SetIndexObject(iID);
			pGroupResolution16_9->SetIndexObject(GetResolutionCheckBox());
			pGroupResolution4_3->Hide();
			pGroupResolution16_9->Show();
		}
	}
	void Window::Render()
	{
		m_pWindowMain->Render(0, 0, GRAPHICENGINE->GetBackWidth(), GRAPHICENGINE->GetBackHeight(), 0, 0);
	}
	BOOL Window::OnKeyPress(class INPUTS::KeyBoard *pcKeyboard)
	{
		if (pcKeyboard->GetEvent() == KeyDown && pcKeyboard->GetKey() == VK_TAB)
		{
			auto pWindowGeneral = GetWindow(WINDOWID_General);

			for (int i = 0; i < 10; i++)
			{
				int t = (i + 1) >= 10 ? 0 : i + 1;

				if (pWindowGeneral->GetElement<UI::InputField>(InputFieldID_Macro1 + i)->IsSelected())
				{
					pWindowGeneral->GetElement<UI::InputField>(InputFieldID_Macro1 + t)->SetSelected(TRUE);
					break;
				}
			}
		}

		return m_pWindowMain->OnKeyPress(pcKeyboard);
	}
	BOOL Window::OnKeyChar(class INPUTS::KeyBoard *pcKeyboard)
	{
		return m_pWindowMain->OnKeyChar(pcKeyboard);
	}
	void Window::OnMouseMove(class INPUTS::Mouse *pcMouse)
	{
		m_pWindowMain->OnMouseMove(pcMouse, 0, 0, GRAPHICENGINE->GetBackWidth(), GRAPHICENGINE->GetBackHeight(), 0, 0);
	}
	BOOL Window::OnMouseClick(class INPUTS::Mouse *pcMouse)
	{
		return m_pWindowMain->OnMouseClick(pcMouse, 0, 0, GRAPHICENGINE->GetBackWidth(), GRAPHICENGINE->GetBackHeight(), 0, 0);
	}
	BOOL Window::OnMouseScroll(class INPUTS::Mouse *pcMouse)
	{
		return m_pWindowMain->OnMouseScroll(pcMouse, 0, 0, GRAPHICENGINE->GetBackWidth(), GRAPHICENGINE->GetBackHeight(), 0, 0);
	}
	void Window::OnResolutionChanged()
	{
		m_pWindowMain->SetPosition((RESOLUTION_WIDTH >> 1) - (m_pWindowMain->GetWidth() >> 1), (RESOLUTION_HEIGHT >> 1) - (m_pWindowMain->GetHeight() >> 1));
	}
	int Window::GetResolutionCheckBox()
	{
		UINT uWidth = SETTINGHANDLE->Get().uWidth;
		UINT uHeight = SETTINGHANDLE->Get().uHeight;

		//4 : 3
		if (uWidth == 1024 && uHeight == 768)
			return CHECKBOXID_1024x768;
		if (uWidth == 1280 && uHeight == 960)
			return CHECKBOXID_1280x960;
		if (uWidth == 1400 && uHeight == 1050)
			return CHECKBOXID_1400x1050;

		//16 : 9
		if (uWidth == 1280 && uHeight == 720)
			return CHECKBOXID_1280x720;
		if (uWidth == 1366 && uHeight == 768)
			return CHECKBOXID_1366x768;
		if (uWidth == 1600 && uHeight == 900)
			return CHECKBOXID_1600x900;
		if (uWidth == 1920 && uHeight == 1080)
			return CHECKBOXID_1920x1080;

		return -1;
	}
	void Window::SetResolutionSettings()
	{
		auto pWindowVideo = GetWindow(WINDOWID_Video);
		auto pGroupRatio = pWindowVideo->GetElement<UI::Group>(GROUPID_Ratio);
		auto pGroupResolution16_9 = pWindowVideo->GetElement<UI::Group>(GROUPID_Resolutions16_9);
		auto pGroupResolution4_3 = pWindowVideo->GetElement <UI::Group>(GROUPID_Resolutions4_3);

		if (pGroupRatio->GetIndexObject() == CHECKBOXID_Ratio4_3)
		{
			int iNum = pGroupResolution4_3->GetIndexObject();

			if (iNum == CHECKBOXID_1024x768)
			{
				SETTINGHANDLE->Get().uWidth = 1024;
				SETTINGHANDLE->Get().uHeight = 768;
			}
			else if (iNum == CHECKBOXID_1280x960)
			{
				SETTINGHANDLE->Get().uWidth = 1280;
				SETTINGHANDLE->Get().uHeight = 960;
			}
			else if (iNum == CHECKBOXID_1400x1050)
			{
				SETTINGHANDLE->Get().uWidth = 1400;
				SETTINGHANDLE->Get().uHeight = 1050;
			}
			else
			{
				SETTINGHANDLE->Get().uWidth = 800;
				SETTINGHANDLE->Get().uHeight = 600;
			}
		}
		else
		{
			int iNum = pGroupResolution16_9->GetIndexObject();

			if (iNum == CHECKBOXID_1280x720)
			{
				SETTINGHANDLE->Get().uWidth = 1280;
				SETTINGHANDLE->Get().uHeight = 720;
			}
			else if (iNum == CHECKBOXID_1366x768)
			{
				SETTINGHANDLE->Get().uWidth = 1366;
				SETTINGHANDLE->Get().uHeight = 768;
			}
			else if (iNum == CHECKBOXID_1600x900)
			{
				SETTINGHANDLE->Get().uWidth = 1600;
				SETTINGHANDLE->Get().uHeight = 900;
			}
			else if (iNum == CHECKBOXID_1920x1080)
			{
				SETTINGHANDLE->Get().uWidth = 1920;
				SETTINGHANDLE->Get().uHeight = 1080;
			}
			else
			{
				SETTINGHANDLE->Get().uWidth = 800;
				SETTINGHANDLE->Get().uHeight = 600;
			}
		}
	}
	void Window::SetResolutionCheckBox()
	{
		auto pWindowVideo = GetWindow(WINDOWID_Video);
		auto pGroupRatio = pWindowVideo->GetElement<UI::Group>(GROUPID_Ratio);

		auto pGroupResolution16_9 = pWindowVideo->GetElement<UI::Group>(GROUPID_Resolutions16_9);
		auto pGroupResolution4_3 = pWindowVideo->GetElement<UI::Group>(GROUPID_Resolutions4_3);

		if (!SETTINGHANDLE->Get().bWidescreen)
		{
			pGroupRatio->SetIndexObject(CHECKBOXID_Ratio4_3);
			pGroupResolution4_3->SetIndexObject(GetResolutionCheckBox());
			pGroupResolution4_3->Show();
			pGroupResolution16_9->Hide();
		}
		else
		{
			pGroupRatio->SetIndexObject(CHECKBOXID_Ratio16_9);
			pGroupResolution16_9->SetIndexObject(GetResolutionCheckBox());
			pGroupResolution4_3->Hide();
			pGroupResolution16_9->Show();
		}
	}
	void Window::Load()
	{
		auto pWindowVideo = GetWindow(WINDOWID_Video);
		auto pWindowAudio = GetWindow(WINDOWID_Audio);
		auto pWindowGeneral = GetWindow(WINDOWID_General);
		auto pWindowInterface = GetWindow(WINDOWID_Interface);

		auto pButtonVideo = m_pWindowMain->GetElement<UI::Button>(BUTTONID_Video);
		auto pButtonAudio = m_pWindowMain->GetElement<UI::Button>(BUTTONID_Audio);
		auto pButtonGeneral = m_pWindowMain->GetElement<UI::Button>(BUTTONID_General);
		auto pButtonInterface = m_pWindowMain->GetElement<UI::Button>(BUTTONID_Interface);
		auto pGroupMenu = m_pWindowMain->GetElement<UI::Group>(GROUPID_Menu);

		if (pWindowVideo->IsOpen())
		{
			pButtonVideo->SetSelected(TRUE);
			pGroupMenu->SetIndexObject(BUTTONID_Video);
		}
		else if (pWindowAudio->IsOpen())
		{
			pButtonAudio->SetSelected(TRUE);
			pGroupMenu->SetIndexObject(BUTTONID_Audio);
		}
		else if (pWindowGeneral->IsOpen())
		{
			pButtonGeneral->SetSelected(TRUE);
			pGroupMenu->SetIndexObject(BUTTONID_General);
		}
		else if (pWindowInterface->IsOpen())
		{
			pButtonInterface->SetSelected(TRUE);
			pGroupMenu->SetIndexObject(BUTTONID_Interface);
		}

		//Video Screen
		{
			pWindowVideo->GetElement<UI::CheckBox>(CHECKBOXID_AutoAdjust)->SetCheck(SETTINGHANDLE->Get().bAutoAdjust);
			pWindowVideo->GetElement<UI::CheckBox>(CHECKBOXID_StartMaximized)->SetCheck(SETTINGHANDLE->Get().bMaximized);

			auto pGroupDisplay = pWindowVideo->GetElement<UI::Group>(GROUPID_Display);
			SETTINGHANDLE->Get().bWindowed ? pGroupDisplay->SetIndexObject(CHECKBOXID_Windowed) : pGroupDisplay->SetIndexObject(CHECKBOXID_Fullscreen);

			SetResolutionCheckBox();
		}

		//Graphics
		{
			auto pGroupTexture = pWindowVideo->GetElement<UI::Group>(GROUPID_TextureQuality);
			SETTINGHANDLE->Get().bHightTextureQuality ? pGroupTexture->SetIndexObject(CHECKBOXID_TextureHigh) : pGroupTexture->SetIndexObject(CHECKBOXID_TextureLow);

			auto pGroupBitDepth = pWindowVideo->GetElement<UI::Group>(GROUPID_BitDepth);
			SETTINGHANDLE->Get().dwBitDepth == 16 ? pGroupBitDepth->SetIndexObject(CHECKBOXID_16BPP) : pGroupBitDepth->SetIndexObject(CHECKBOXID_32BPP);

			auto pGroupVSync = pWindowVideo->GetElement<UI::Group>(GROUPID_VSync);
			SETTINGHANDLE->Get().bVSync ? pGroupVSync->SetIndexObject(CHECKBOXID_VSyncON) : pGroupVSync->SetIndexObject(CHECKBOXID_VSyncOFF);

			auto pGroupAntiAliasing = pWindowVideo->GetElement<UI::Group>(GROUPID_AntiAliasing);
			SETTINGHANDLE->Get().bAntiAliasing ? pGroupAntiAliasing->SetIndexObject(CHECKBOXID_AntiAliasingON) : pGroupAntiAliasing->SetIndexObject(CHECKBOXID_AntiAliasingOFF);

			auto pGroupEffects = pWindowVideo->GetElement<UI::Group>(GROUPID_Effects);
			SETTINGHANDLE->Get().bNoEffects ? pGroupEffects->SetIndexObject(CHECKBOXID_EffectsOFF) : pGroupEffects->SetIndexObject(CHECKBOXID_EffectsON);
		}

		//Camera
		{
			auto pGroupCameraSight = pWindowVideo->GetElement<UI::Group>(GROUPID_CameraSight);
			if (SETTINGHANDLE->Get().iCameraRange == 0)
				pGroupCameraSight->SetIndexObject(CHECKBOXID_Short);
			else if (SETTINGHANDLE->Get().iCameraRange == 1)
				pGroupCameraSight->SetIndexObject(CHECKBOXID_Far);
			else if (SETTINGHANDLE->Get().iCameraRange == 2)
				pGroupCameraSight->SetIndexObject(CHECKBOXID_Full);

			auto pGroupCameraInvert = pWindowVideo->GetElement<UI::Group>(GROUPID_InvertedCamera);
			SETTINGHANDLE->Get().bInvertedCamera ? pGroupCameraInvert->SetIndexObject(CHECKBOXID_CameraON) : pGroupCameraInvert->SetIndexObject(CHECKBOXID_CameraOFF);
		}

		//Audio
		{
			pWindowAudio->GetElement<UI::CheckBox>(CHECKBOXID_NoMusic)->SetCheck(SETTINGHANDLE->Get().bNoMusic);
			pWindowAudio->GetElement<UI::Scroll>(SCROLLID_BGMusic)->SetPercent(SETTINGHANDLE->Get().iMusicVolume);

			//Effect iSound
			pWindowAudio->GetElement<UI::CheckBox>(CHECKBOXID_NoEffects)->SetCheck(SETTINGHANDLE->Get().bNoEffects);
			pWindowAudio->GetElement<UI::Scroll>(SCROLLID_EffectSound)->SetPercent(SETTINGHANDLE->Get().iEffectVolume);
		}

		//General
		//Game
		{
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_NoWhisper)->SetCheck(SETTINGHANDLE->Get().bNoWisper);
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_NoTrade)->SetCheck(SETTINGHANDLE->Get().bNoTradeChat);
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_DisableParty)->SetCheck(SETTINGHANDLE->Get().bNoPartyRequest);
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_DisableTrade)->SetCheck(SETTINGHANDLE->Get().bNoTradeRequest);

			for (int i = 0; i < 10; i++)
			{
				pWindowGeneral->GetElement<UI::InputField>(InputFieldID_Macro1 + i)->SetText(SETTINGHANDLE->Get().szMacro[i]);
			}
		}

		//Personalization
		{
			auto pGroupDebugDemage = pWindowGeneral->GetElement<UI::Group>(GROUPID_DamageDebug);
			SETTINGHANDLE->Get().bDebugDamage ? pGroupDebugDemage->SetIndexObject(CHECKBOXID_DamageDebugON) : pGroupDebugDemage->SetIndexObject(CHECKBOXID_DamageDebugOFF);

			auto pGroupHPBar = pWindowGeneral->GetElement<UI::Group>(GROUPID_HPBar);
			SETTINGHANDLE->Get().bHPBarOnHead ? pGroupHPBar->SetIndexObject(CHECKBOXID_HPBarON) : pGroupHPBar->SetIndexObject(CHECKBOXID_HPBarOFF);

			auto pGroupFPS = pWindowGeneral->GetElement<UI::Group>(GROUPID_FPS);
			SETTINGHANDLE->Get().bFPS ? pGroupFPS->SetIndexObject(CHECKBOXID_HPBarON) : pGroupFPS->SetIndexObject(CHECKBOXID_HPBarOFF);

			auto pGroupPing = pWindowGeneral->GetElement<UI::Group>(GROUPID_Ping);
			SETTINGHANDLE->Get().bPing ? pGroupPing->SetIndexObject(CHECKBOXID_PingON) : pGroupPing->SetIndexObject(CHECKBOXID_PingOFF);

			auto pGroupKillInfo = pWindowGeneral->GetElement<UI::Group>(GROUPID_KillInfo);
			SETTINGHANDLE->Get().bDebugKill ? pGroupKillInfo->SetIndexObject(CHECKBOXID_KillInfoON) : pGroupKillInfo->SetIndexObject(CHECKBOXID_KillInfoOFF);
		}
		//loot
		{
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootFilterEnable)->SetCheck(SETTINGHANDLE->Get().bEnableLootFilter);
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootHPPotion)->SetCheck(SETTINGHANDLE->CanViewLoot(LOOTFILTER_HPPotion));
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootMPPotion)->SetCheck(SETTINGHANDLE->CanViewLoot(LOOTFILTER_MPPotion));
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSPPotion)->SetCheck(SETTINGHANDLE->CanViewLoot(LOOTFILTER_SPPotion));
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootGold)->SetCheck(SETTINGHANDLE->CanViewLoot(LOOTFILTER_Gold));
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootAmulets)->SetCheck(SETTINGHANDLE->CanViewLoot(LOOTFILTER_Amulets));
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootRings)->SetCheck(SETTINGHANDLE->CanViewLoot(LOOTFILTER_Rings));
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSheltoms)->SetCheck(SETTINGHANDLE->CanViewLoot(LOOTFILTER_Sheltoms));
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootForceOrbs)->SetCheck(SETTINGHANDLE->CanViewLoot(LOOTFILTER_ForceOrbs));
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootPremiums)->SetCheck(SETTINGHANDLE->CanViewLoot(LOOTFILTER_Premiums));
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootMonsterCrystals)->SetCheck(SETTINGHANDLE->CanViewLoot(LOOTFILTER_MonsterCrystals));
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootDefenseItems)->SetCheck(SETTINGHANDLE->CanViewLoot(LOOTFILTER_DefenseItems));
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootOffenseItems)->SetCheck(SETTINGHANDLE->CanViewLoot(LOOTFILTER_OffenseItems));
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootEverything)->SetCheck(SETTINGHANDLE->CanViewLoot(LOOTFILTER_Everything));

			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSpecNS)->SetCheck(SETTINGHANDLE->CanViewLootSpec(LOOTFILTERSPEC_NS));
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSpecFS)->SetCheck(SETTINGHANDLE->CanViewLootSpec(LOOTFILTERSPEC_FS));
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSpecMS)->SetCheck(SETTINGHANDLE->CanViewLootSpec(LOOTFILTERSPEC_MS));
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSpecAS)->SetCheck(SETTINGHANDLE->CanViewLootSpec(LOOTFILTERSPEC_AS));
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSpecPS)->SetCheck(SETTINGHANDLE->CanViewLootSpec(LOOTFILTERSPEC_PS));
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSpecATA)->SetCheck(SETTINGHANDLE->CanViewLootSpec(LOOTFILTERSPEC_ATA));
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSpecKS)->SetCheck(SETTINGHANDLE->CanViewLootSpec(LOOTFILTERSPEC_KS));
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSpecMGS)->SetCheck(SETTINGHANDLE->CanViewLootSpec(LOOTFILTERSPEC_MGS));
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSpecPRS)->SetCheck(SETTINGHANDLE->CanViewLootSpec(LOOTFILTERSPEC_PRS));
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSpecASS)->SetCheck(SETTINGHANDLE->CanViewLootSpec(LOOTFILTERSPEC_ASS));
			pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSpecSHA)->SetCheck(SETTINGHANDLE->CanViewLootSpec(LOOTFILTERSPEC_SHA));
		}
		//Interface
		{
			pWindowInterface->GetElement<UI::CheckBox>(CHECKBOXID_LockUI)->SetCheck(SETTINGHANDLE->Get().bLockUI);
			pWindowInterface->GetElement<UI::CheckBox>(CHECKBOXID_ShowPartyMembers)->SetCheck(SETTINGHANDLE->Get().bShowPartyMembers);
			pWindowInterface->GetElement<UI::CheckBox>(CHECKBOXID_ShowRaidMembers)->SetCheck(SETTINGHANDLE->Get().bShowRaidMembers);
			pWindowInterface->GetElement<UI::CheckBox>(CHECKBOXID_ShowClanMembers)->SetCheck(SETTINGHANDLE->Get().bShowClanMembers);
			pWindowInterface->GetElement<UI::CheckBox>(CHECKBOXID_ShowEnemies)->SetCheck(SETTINGHANDLE->Get().bShowEnemies);
			pWindowInterface->GetElement<UI::CheckBox>(CHECKBOXID_ShowNPCs)->SetCheck(SETTINGHANDLE->Get().bShowNPCs);
			pWindowInterface->GetElement<UI::CheckBox>(CHECKBOXID_AlwaysActive)->SetCheck(SETTINGHANDLE->Get().bMinimapAlwaysActive);
			pWindowInterface->GetElement<UI::CheckBox>(CHECKBOXID_ShowNextBossTimer)->SetCheck(SETTINGHANDLE->Get().bShowNextBossTimer);
			pWindowInterface->GetElement<UI::CheckBox>(CHECKBOXID_ShowNotice)->SetCheck(SETTINGHANDLE->Get().bShowNotice);
			pWindowInterface->GetElement<UI::CheckBox>(CHECKBOXID_TargetDistance)->SetCheck(SETTINGHANDLE->Get().bTargetDistance);
			pWindowInterface->GetElement<UI::CheckBox>(CHECKBOXID_TargetHPValue)->SetCheck(SETTINGHANDLE->Get().bTargetHPValue);
			pWindowInterface->GetElement<UI::CheckBox>(CHECKBOXID_TargetHPPercent)->SetCheck(SETTINGHANDLE->Get().bTargetHPPercent);
		}
	}
	void Window::Save()
	{
		// iButton is No
		if (!MESSAGEBOX->GetType())
		{
			m_pWindowMain->Show();
			return;
		}

		SetResolutionSettings();

		auto pWindowVideo = GetWindow(WINDOWID_Video);

		//Video
		//Screen;
		{
			SETTINGHANDLE->Get().bAutoAdjust = pWindowVideo->GetElement<UI::CheckBox>(CHECKBOXID_AutoAdjust)->IsChecked();
			SETTINGHANDLE->Get().bMaximized = pWindowVideo->GetElement<UI::CheckBox>(CHECKBOXID_StartMaximized)->IsChecked();
			SETTINGHANDLE->Get().bWindowed = pWindowVideo->GetElement<UI::Group>(GROUPID_Display)->GetIndexObject() == CHECKBOXID_Windowed ? TRUE : FALSE;
			SETTINGHANDLE->Get().bWidescreen = pWindowVideo->GetElement<UI::Group>(GROUPID_Ratio)->GetIndexObject() == CHECKBOXID_Ratio16_9 ? TRUE : FALSE;
		}
		//Graphics
		{
			SETTINGHANDLE->Get().bHightTextureQuality = pWindowVideo->GetElement<UI::Group>(GROUPID_TextureQuality)->GetIndexObject() == CHECKBOXID_TextureHigh ? TRUE : FALSE;
			SETTINGHANDLE->Get().dwBitDepth = pWindowVideo->GetElement<UI::Group>(GROUPID_BitDepth)->GetIndexObject() == CHECKBOXID_16BPP ? 16 : 32;
			SETTINGHANDLE->Get().bNoEffects = pWindowVideo->GetElement<UI::Group>(GROUPID_Effects)->GetIndexObject() == CHECKBOXID_EffectsOFF ? TRUE : FALSE;
			SETTINGHANDLE->Get().bVSync = pWindowVideo->GetElement<UI::Group>(GROUPID_VSync)->GetIndexObject() == CHECKBOXID_VSyncON ? TRUE : FALSE;
			SETTINGHANDLE->Get().bAntiAliasing = pWindowVideo->GetElement<UI::Group>(GROUPID_AntiAliasing)->GetIndexObject() == CHECKBOXID_AntiAliasingON ? TRUE : FALSE;
		}
		//Camera
		{
			auto pGroupCameraSight = pWindowVideo->GetElement<UI::Group>(GROUPID_CameraSight);
			if (pGroupCameraSight->GetIndexObject() == CHECKBOXID_Short)
				SETTINGHANDLE->Get().iCameraRange = 0;
			else if (pGroupCameraSight->GetIndexObject() == CHECKBOXID_Far)
				SETTINGHANDLE->Get().iCameraRange = 1;
			else if (pGroupCameraSight->GetIndexObject() == CHECKBOXID_Full)
				SETTINGHANDLE->Get().iCameraRange = 2;

			SETTINGHANDLE->Get().bInvertedCamera = pWindowVideo->GetElement<UI::Group>(GROUPID_InvertedCamera)->GetIndexObject() == CHECKBOXID_CameraON ? TRUE : FALSE;
		}

		auto pWindowAudio = GetWindow(WINDOWID_Audio);
		//Audio
		// BG Music Effect iSound
		{
			SETTINGHANDLE->Get().bNoMusic = pWindowAudio->GetElement<UI::CheckBox>(CHECKBOXID_NoMusic)->IsChecked();
			SETTINGHANDLE->Get().iMusicVolume = pWindowAudio->GetElement<UI::Scroll>(SCROLLID_BGMusic)->GetPercent();

			SETTINGHANDLE->Get().bNoSoundEffect = pWindowAudio->GetElement<UI::CheckBox>(CHECKBOXID_NoEffects)->IsChecked();
			SETTINGHANDLE->Get().iEffectVolume = pWindowAudio->GetElement<UI::Scroll>(SCROLLID_EffectSound)->GetPercent();
		}
		auto pWindowGeneral = GetWindow(WINDOWID_General);
		//General
		//Personalization
		{
			SETTINGHANDLE->Get().bDebugDamage = pWindowGeneral->GetElement<UI::Group>(GROUPID_DamageDebug)->GetIndexObject() == CHECKBOXID_DamageDebugON ? TRUE : FALSE;
			SETTINGHANDLE->Get().bHPBarOnHead = pWindowGeneral->GetElement<UI::Group>(GROUPID_HPBar)->GetIndexObject() == CHECKBOXID_HPBarON ? TRUE : FALSE;
			SETTINGHANDLE->Get().bFPS = pWindowGeneral->GetElement<UI::Group>(GROUPID_FPS)->GetIndexObject() == CHECKBOXID_FPSON ? TRUE : FALSE;
			SETTINGHANDLE->Get().bPing = pWindowGeneral->GetElement<UI::Group>(GROUPID_Ping)->GetIndexObject() == CHECKBOXID_PingON ? TRUE : FALSE;
			SETTINGHANDLE->Get().bDebugKill = pWindowGeneral->GetElement<UI::Group>(GROUPID_KillInfo)->GetIndexObject() == CHECKBOXID_KillInfoON ? TRUE : FALSE;
		}
		//Loot
		{
			SETTINGHANDLE->Get().bEnableLootFilter = pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootFilterEnable)->IsChecked();
			SETTINGHANDLE->SetViewLoot(LOOTFILTER_HPPotion, pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootHPPotion)->IsChecked());
			SETTINGHANDLE->SetViewLoot(LOOTFILTER_MPPotion, pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootMPPotion)->IsChecked());
			SETTINGHANDLE->SetViewLoot(LOOTFILTER_SPPotion, pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSPPotion)->IsChecked());
			SETTINGHANDLE->SetViewLoot(LOOTFILTER_Gold, pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootGold)->IsChecked());
			SETTINGHANDLE->SetViewLoot(LOOTFILTER_Amulets, pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootAmulets)->IsChecked());
			SETTINGHANDLE->SetViewLoot(LOOTFILTER_Rings, pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootRings)->IsChecked());
			SETTINGHANDLE->SetViewLoot(LOOTFILTER_Sheltoms, pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSheltoms)->IsChecked());
			SETTINGHANDLE->SetViewLoot(LOOTFILTER_ForceOrbs, pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootForceOrbs)->IsChecked());
			SETTINGHANDLE->SetViewLoot(LOOTFILTER_Premiums, pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootPremiums)->IsChecked());
			SETTINGHANDLE->SetViewLoot(LOOTFILTER_MonsterCrystals, pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootMonsterCrystals)->IsChecked());
			SETTINGHANDLE->SetViewLoot(LOOTFILTER_DefenseItems, pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootDefenseItems)->IsChecked());
			SETTINGHANDLE->SetViewLoot(LOOTFILTER_OffenseItems, pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootOffenseItems)->IsChecked());
			SETTINGHANDLE->SetViewLoot(LOOTFILTER_Everything, pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootEverything)->IsChecked());

			SETTINGHANDLE->SetViewLootSpec(LOOTFILTERSPEC_NS, pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSpecNS)->IsChecked());
			SETTINGHANDLE->SetViewLootSpec(LOOTFILTERSPEC_FS, pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSpecFS)->IsChecked());
			SETTINGHANDLE->SetViewLootSpec(LOOTFILTERSPEC_MS, pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSpecMS)->IsChecked());
			SETTINGHANDLE->SetViewLootSpec(LOOTFILTERSPEC_AS, pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSpecAS)->IsChecked());
			SETTINGHANDLE->SetViewLootSpec(LOOTFILTERSPEC_PS, pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSpecPS)->IsChecked());
			SETTINGHANDLE->SetViewLootSpec(LOOTFILTERSPEC_ATA, pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSpecATA)->IsChecked());
			SETTINGHANDLE->SetViewLootSpec(LOOTFILTERSPEC_KS, pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSpecKS)->IsChecked());
			SETTINGHANDLE->SetViewLootSpec(LOOTFILTERSPEC_MGS, pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSpecMGS)->IsChecked());
			SETTINGHANDLE->SetViewLootSpec(LOOTFILTERSPEC_PRS, pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSpecPRS)->IsChecked());
			SETTINGHANDLE->SetViewLootSpec(LOOTFILTERSPEC_ASS, pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSpecASS)->IsChecked());
			SETTINGHANDLE->SetViewLootSpec(LOOTFILTERSPEC_SHA, pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_LootSpecSHA)->IsChecked());
		}
		// General Settings
		{
			for (int i = 0; i < 10; i++)
			{
				auto pInputField = pWindowGeneral->GetElement<UI::InputField>(InputFieldID_Macro1 + i);
				STRINGCOPY(SETTINGHANDLE->Get().szMacro[i], pInputField->GetText().c_str());
			}

			SETTINGHANDLE->Get().bNoWisper = pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_NoWhisper)->IsChecked();
			SETTINGHANDLE->Get().bNoTradeChat = pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_NoTrade)->IsChecked();
			SETTINGHANDLE->Get().bNoTradeRequest = pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_DisableTrade)->IsChecked();
			SETTINGHANDLE->Get().bNoPartyRequest = pWindowGeneral->GetElement<UI::CheckBox>(CHECKBOXID_DisableParty)->IsChecked();
		}

		//Interface
		auto pWindowInterface = GetWindow(WINDOWID_Interface);
		{
			SETTINGHANDLE->Get().bLockUI = pWindowInterface->GetElement<UI::CheckBox>(CHECKBOXID_LockUI)->IsChecked();
			SETTINGHANDLE->Get().bShowPartyMembers = pWindowInterface->GetElement<UI::CheckBox>(CHECKBOXID_ShowPartyMembers)->IsChecked();
			SETTINGHANDLE->Get().bShowRaidMembers = pWindowInterface->GetElement<UI::CheckBox>(CHECKBOXID_ShowRaidMembers)->IsChecked();
			SETTINGHANDLE->Get().bShowClanMembers = pWindowInterface->GetElement<UI::CheckBox>(CHECKBOXID_ShowClanMembers)->IsChecked();
			SETTINGHANDLE->Get().bShowNPCs = pWindowInterface->GetElement<UI::CheckBox>(CHECKBOXID_ShowEnemies)->IsChecked();
			SETTINGHANDLE->Get().bShowEnemies = pWindowInterface->GetElement<UI::CheckBox>(CHECKBOXID_ShowNPCs)->IsChecked();
			SETTINGHANDLE->Get().bMinimapAlwaysActive = pWindowInterface->GetElement<UI::CheckBox>(CHECKBOXID_AlwaysActive)->IsChecked();
			SETTINGHANDLE->Get().bShowNextBossTimer = pWindowInterface->GetElement<UI::CheckBox>(CHECKBOXID_ShowNextBossTimer)->IsChecked();
			SETTINGHANDLE->Get().bShowNotice = pWindowInterface->GetElement<UI::CheckBox>(CHECKBOXID_ShowNotice)->IsChecked();
			SETTINGHANDLE->Get().bTargetDistance = pWindowInterface->GetElement<UI::CheckBox>(CHECKBOXID_TargetDistance)->IsChecked();
			SETTINGHANDLE->Get().bTargetHPValue = pWindowInterface->GetElement<UI::CheckBox>(CHECKBOXID_TargetHPValue)->IsChecked();
			SETTINGHANDLE->Get().bTargetHPPercent = pWindowInterface->GetElement<UI::CheckBox>(CHECKBOXID_TargetHPPercent)->IsChecked();
		}

		SETTINGHANDLE->Write();

		GRAPHICENGINE->Reset(SETTINGHANDLE->Get().bWindowed, SETTINGHANDLE->Get().uWidth, SETTINGHANDLE->Get().uHeight);
		GRAPHICENGINE->ResolutionChange(FALSE, SETTINGHANDLE->Get().uWidth, SETTINGHANDLE->Get().uHeight);

		GRAPHICENGINE->ResizeWindow();

		SETTINGHANDLE->Read();

		GAMESCREEN->UpdateObjectsSettings();

		m_pWindowMain->Hide();

		MOUSEHANDLER->UnblockMouse();
	}
	void Window::BuildWindow()
	{
		m_pWindowMain = std::make_shared<UI::Window>(Rectangle2D((GRAPHICENGINE->GetBackWidth() >> 1) - (560 >> 1), (GRAPHICENGINE->GetBackHeight() >> 1) - (450 >> 1), 572, 450));
		m_pWindowMain->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Settings\\Window.png"));
		m_pWindowMain->SetID(WINDOWID_Main);

		auto pListMain = std::make_shared<UI::List>(Rectangle2D(135, 40, 410, 395));
		pListMain->SetID(LISTID_Main);
		pListMain->SetNoUpdatePosition(TRUE);
		pListMain->MakeScrollBar(Rectangle2D(401, (395 >> 1) - (385 >> 1), 6, 385), "Resources\\UI\\Settings\\Scrollbar.png", "Resources\\UI\\Scroll\\Icon_2.png");
		pListMain->SetScrollFirst(TRUE);
		m_pWindowMain->AddElement(pListMain);

		//Menu Settings
		auto pGroupMenu = std::make_shared<UI::Group>();
		pGroupMenu->SetID(GROUPID_Menu);
		m_pWindowMain->AddElement(pGroupMenu);

		auto pButtonVideo = std::make_shared<UI::Button>(Rectangle2D(14, 50, 121, 29));
		pButtonVideo->SetID(BUTTONID_Video);
		pButtonVideo->SetGroup(pGroupMenu);
		pButtonVideo->SetActiveImage(UI::ImageLoader::LoadActiveImage("Resources\\UI\\Settings\\Video.png", "Resources\\UI\\Settings\\Video_.png"));
		pButtonVideo->SetSelect(TRUE);
		pButtonVideo->SetEvent(UI::Event::Build(std::bind(&Window::OnMenuButtonClick, this, BUTTONID_Video, std::placeholders::_1)));
		m_pWindowMain->AddElement(pButtonVideo);

		auto pButtonAudio = std::make_shared<UI::Button>(Rectangle2D(14, 50 + 29, 121, 29));
		pButtonAudio->SetID(BUTTONID_Audio);
		pButtonAudio->SetGroup(pGroupMenu);
		pButtonAudio->SetActiveImage(UI::ImageLoader::LoadActiveImage("Resources\\UI\\Settings\\Audio.png", "Resources\\UI\\Settings\\Audio_.png"));
		pButtonAudio->SetSelect(TRUE);
		pButtonAudio->SetEvent(UI::Event::Build(std::bind(&Window::OnMenuButtonClick, this, BUTTONID_Audio, std::placeholders::_1)));
		m_pWindowMain->AddElement(pButtonAudio);

		auto pButtonGeneral = std::make_shared<UI::Button>(Rectangle2D(14, 50 + (29 * 2), 121, 29));
		pButtonGeneral->SetID(BUTTONID_General);
		pButtonGeneral->SetGroup(pGroupMenu);
		pButtonGeneral->SetActiveImage(UI::ImageLoader::LoadActiveImage("Resources\\UI\\Settings\\General.png", "Resources\\UI\\Settings\\General_.png"));
		pButtonGeneral->SetSelect(TRUE);
		pButtonGeneral->SetEvent(UI::Event::Build(std::bind(&Window::OnMenuButtonClick, this, BUTTONID_General, std::placeholders::_1)));
		m_pWindowMain->AddElement(pButtonGeneral);

		auto pButtonInterface = std::make_shared<UI::Button>(Rectangle2D(14, 50 + (29 * 3), 121, 29));
		pButtonInterface->SetID(BUTTONID_Interface);
		pButtonInterface->SetGroup(pGroupMenu);
		pButtonInterface->SetActiveImage(UI::ImageLoader::LoadActiveImage("Resources\\UI\\Settings\\ui.png", "Resources\\UI\\Settings\\ui_.png"));
		pButtonInterface->SetSelect(TRUE);
		pButtonInterface->SetEvent(UI::Event::Build(std::bind(&Window::OnMenuButtonClick, this, BUTTONID_Interface, std::placeholders::_1)));
		m_pWindowMain->AddElement(pButtonInterface);

		auto pButtonReset = std::make_shared<UI::Button>(Rectangle2D(28, 374, 93, 23));
		pButtonReset->SetActiveImage(UI::ImageLoader::LoadActiveImage("Resources\\UI\\Settings\\BtnReset.png", "Resources\\UI\\Settings\\BtnReset_.png"));
		pButtonReset->SetEvent(UI::Event::Build(std::bind(&Window::OnResetButtonClick, this, std::placeholders::_1)));
		m_pWindowMain->AddElement(pButtonReset);

		auto pButtonSave = std::make_shared<UI::Button>(Rectangle2D(28, 374 + 26, 93, 23));
		pButtonSave->SetActiveImage(UI::ImageLoader::LoadActiveImage("Resources\\UI\\Settings\\BtnSave.png", "Resources\\UI\\Settings\\BtnSave_.png"));
		pButtonSave->SetEvent(UI::Event::Build(std::bind(&Window::OnSaveButtonClick, this, std::placeholders::_1)));
		m_pWindowMain->AddElement(pButtonSave);

		auto pButtonClose = std::make_shared<UI::Button>(Rectangle2D(536, 4, 32, 47));
		pButtonClose->SetActiveImage(UI::ImageLoader::LoadActiveImage("Resources\\UI\\Settings\\BtnClose.png", "Resources\\UI\\Settings\\BtnClose_.png"));
		pButtonClose->SetEvent(UI::Event::Build(std::bind(&Window::OnCloseButtonClick, this, std::placeholders::_1)));
		m_pWindowMain->AddElement(pButtonClose);

		m_pWindowMain->SetMoveBox(Rectangle2D(0, 0, m_pWindowMain->GetWidth() - 40, 40));
		m_pWindowMain->SetCanMove(TRUE);
	}
	void Window::BuildVideo()
	{
		UI::LPWINDOW pWindowVideo = std::make_shared<UI::Window>(Rectangle2D(0, 0, 400, 470));
		pWindowVideo->SetID(WINDOWID_Video);

		//Title Screen
		UI::LPIMAGEBOX pScreenBar = std::make_shared<UI::ImageBox>(Rectangle2D(34, 11, 339, 23));
		pScreenBar->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Settings\\Title.png"));
		pWindowVideo->AddElement(pScreenBar);

		UI::LPIMAGEBOX pScreenTitle = std::make_shared<UI::ImageBox>(Rectangle2D(130, 16, 150, 14));
		pScreenTitle->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Settings\\Screen.png"));
		pWindowVideo->AddElement(pScreenTitle);

		//Text Display
		UI::LPTEXT pTextDisplay = std::make_shared<UI::Text>(Rectangle2D(24, 47, 0, 0));
		pTextDisplay->SetFont("Arial", 16, 0, FALSE, TRUE, -1);
		pTextDisplay->SetText("Display:");
		pWindowVideo->AddElement(pTextDisplay);

		//Group Display
		UI::LPGROUP pGroupDisplay = std::make_shared<UI::Group>();
		pGroupDisplay->SetID(GROUPID_Display);
		pWindowVideo->AddElement(pGroupDisplay);

		//全屏
		UI::LPCHECKBOX pCheckBoxFullScreen = std::make_shared<UI::CheckBox>(Rectangle2D(24, 67, 13, 13));
		pCheckBoxFullScreen->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxFullScreen->SetText("Fullscreen");
		pCheckBoxFullScreen->SetGroup(pGroupDisplay);
		pCheckBoxFullScreen->SetID(CHECKBOXID_Fullscreen);
		pCheckBoxFullScreen->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowVideo->AddElement(pCheckBoxFullScreen);

		//窗口化
		UI::LPCHECKBOX pCheckBoxWindowed = std::make_shared<UI::CheckBox>(Rectangle2D(150, 67, 13, 13));
		pCheckBoxWindowed->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxWindowed->SetText("Windowed");
		pCheckBoxWindowed->SetGroup(pGroupDisplay);
		pCheckBoxWindowed->SetID(CHECKBOXID_Windowed);
		pCheckBoxWindowed->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowVideo->AddElement(pCheckBoxWindowed);

		//开始最大化
		UI::LPCHECKBOX pCheckBoxStartMaximized = std::make_shared<UI::CheckBox>(Rectangle2D(270, 85, 13, 13));
		pCheckBoxStartMaximized->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxStartMaximized->SetText("Start Maximized");
		pCheckBoxStartMaximized->SetID(CHECKBOXID_StartMaximized);
		pCheckBoxStartMaximized->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowVideo->AddElement(pCheckBoxStartMaximized);

		//自动适应
		UI::LPCHECKBOX pCheckBoxAutoAdjust = std::make_shared<UI::CheckBox>(Rectangle2D(270, 67, 13, 13));
		pCheckBoxAutoAdjust->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxAutoAdjust->SetText("Auto Adjust");
		pCheckBoxAutoAdjust->SetID(CHECKBOXID_AutoAdjust);
		pCheckBoxAutoAdjust->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowVideo->AddElement(pCheckBoxAutoAdjust);

		UI::LPGROUP pGroupRatio = std::make_shared<UI::Group>();
		pGroupRatio->SetID(GROUPID_Ratio);
		pWindowVideo->AddElement(pGroupRatio);

		UI::LPTEXT pTextRatio = std::make_shared<UI::Text>(Rectangle2D(24, 90, 0, 0));
		pTextRatio->SetFont("Arial", 16, 0, FALSE, TRUE, -1);
		pTextRatio->SetText("Ratio:");
		pWindowVideo->AddElement(pTextRatio);

		//4:3
		UI::LPCHECKBOX pCheckBox4_3 = std::make_shared<UI::CheckBox>(Rectangle2D(24, 110, 13, 13));
		pCheckBox4_3->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBox4_3->SetText("4:3");
		pCheckBox4_3->SetGroup(pGroupRatio);
		pCheckBox4_3->SetID(CHECKBOXID_Ratio4_3);
		pCheckBox4_3->SetEvent(UI::Event::Build(std::bind(&Window::OnCheckBoxRatioClick, this, CHECKBOXID_Ratio4_3, std::placeholders::_1)));
		pCheckBox4_3->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowVideo->AddElement(pCheckBox4_3);

		//16:9
		UI::LPCHECKBOX pCheckBox16_9 = std::make_shared<UI::CheckBox>(Rectangle2D(150, 110, 13, 13));
		pCheckBox16_9->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBox16_9->SetText("16:9");
		pCheckBox16_9->SetGroup(pGroupRatio);
		pCheckBox16_9->SetID(CHECKBOXID_Ratio16_9);
		pCheckBox16_9->SetEvent(UI::Event::Build(std::bind(&Window::OnCheckBoxRatioClick, this, CHECKBOXID_Ratio16_9, std::placeholders::_1)));
		pCheckBox16_9->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowVideo->AddElement(pCheckBox16_9);

		//Text Resolutions
		UI::LPTEXT pTextResolutions = std::make_shared<UI::Text>(Rectangle2D(24, 134, 0, 0));
		pTextResolutions->SetFont("Arial", 16, 0, FALSE, TRUE, -1);
		pTextResolutions->SetText("Resolutions:");
		pWindowVideo->AddElement(pTextResolutions);

		UI::LPGROUP pGroupResolution4_3 = std::make_shared<UI::Group>();
		pGroupResolution4_3->SetID(GROUPID_Resolutions4_3);
		pWindowVideo->AddElement(pGroupResolution4_3);

		//1024 * 768
		UI::LPCHECKBOX pCheckBox1024x768 = std::make_shared<UI::CheckBox>(Rectangle2D(24, 154, 13, 13));
		pCheckBox1024x768->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBox1024x768->SetText("1024x768");
		pCheckBox1024x768->SetGroup(pGroupResolution4_3);
		pCheckBox1024x768->SetID(CHECKBOXID_1024x768);
		pCheckBox1024x768->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowVideo->AddElement(pCheckBox1024x768);

		//1280 * 960
		UI::LPCHECKBOX pCheckBox1280x960 = std::make_shared<UI::CheckBox>(Rectangle2D(24, 174, 13, 13));
		pCheckBox1280x960->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBox1280x960->SetText("1280x960");
		pCheckBox1280x960->SetGroup(pGroupResolution4_3);
		pCheckBox1280x960->SetID(CHECKBOXID_1280x960);
		pCheckBox1280x960->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowVideo->AddElement(pCheckBox1280x960);

		//1400 * 1050
		UI::LPCHECKBOX pCheckBox1400x1050 = std::make_shared<UI::CheckBox>(Rectangle2D(150, 154, 13, 13));
		pCheckBox1400x1050->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBox1400x1050->SetText("1400x1050");
		pCheckBox1400x1050->SetGroup(pGroupResolution4_3);
		pCheckBox1400x1050->SetID(CHECKBOXID_1400x1050);
		pCheckBox1400x1050->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowVideo->AddElement(pCheckBox1400x1050);

		//Group Resolutions 16:9
		UI::LPGROUP pGroupResolutions16_9 = std::make_shared<UI::Group>();
		pGroupResolutions16_9->SetID(GROUPID_Resolutions16_9);
		pWindowVideo->AddElement(pGroupResolutions16_9);

		//1280 * 720
		UI::LPCHECKBOX pCheckBox1280x720 = std::make_shared<UI::CheckBox>(Rectangle2D(24, 154, 13, 13));
		pCheckBox1280x720->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBox1280x720->SetText("1280x720");
		pCheckBox1280x720->SetGroup(pGroupResolutions16_9);
		pCheckBox1280x720->SetID(CHECKBOXID_1280x720);
		pCheckBox1280x720->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowVideo->AddElement(pCheckBox1280x720);

		//1366 * 768
		UI::LPCHECKBOX pCheckBox1366x768 = std::make_shared<UI::CheckBox>(Rectangle2D(24, 174, 13, 13));
		pCheckBox1366x768->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBox1366x768->SetText("1366x768");
		pCheckBox1366x768->SetGroup(pGroupResolutions16_9);
		pCheckBox1366x768->SetID(CHECKBOXID_1366x768);
		pCheckBox1366x768->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowVideo->AddElement(pCheckBox1366x768);

		//1366 * 768
		UI::LPCHECKBOX pCheckBox1600x900 = std::make_shared<UI::CheckBox>(Rectangle2D(150, 154, 13, 13));
		pCheckBox1600x900->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBox1600x900->SetText("1600x900");
		pCheckBox1600x900->SetGroup(pGroupResolutions16_9);
		pCheckBox1600x900->SetID(CHECKBOXID_1600x900);
		pCheckBox1600x900->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowVideo->AddElement(pCheckBox1600x900);

		//1920 * 1080
		UI::LPCHECKBOX pCheckBox1920x1080 = std::make_shared<UI::CheckBox>(Rectangle2D(150, 174, 13, 13));
		pCheckBox1920x1080->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBox1920x1080->SetText("1920x1080");
		pCheckBox1920x1080->SetGroup(pGroupResolutions16_9);
		pCheckBox1920x1080->SetID(CHECKBOXID_1920x1080);
		pCheckBox1920x1080->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowVideo->AddElement(pCheckBox1920x1080);

		//Title Graphics
		UI::LPIMAGEBOX pGraphicsBar = std::make_shared<UI::ImageBox>(Rectangle2D(34, 202, 339, 23));
		pGraphicsBar->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Settings\\Title.png"));
		pWindowVideo->AddElement(pGraphicsBar);

		UI::LPIMAGEBOX pGraphicsTitle = std::make_shared<UI::ImageBox>(Rectangle2D(130, 207, 150, 14));
		pGraphicsTitle->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Settings\\Graphics.png"));
		pWindowVideo->AddElement(pGraphicsTitle);

		//Text Texture Quality
		UI::LPTEXT pTextTextureQuality = std::make_shared<UI::Text>(Rectangle2D(24, 238, 0, 0));
		pTextTextureQuality->SetFont("Arial", 16, 0, FALSE, TRUE, -1);
		pTextTextureQuality->SetText("Texture Quality:");
		pWindowVideo->AddElement(pTextTextureQuality);

		//Group Texture Quality
		UI::LPGROUP pGroupTextureQuality = std::make_shared<UI::Group>();
		pGroupTextureQuality->SetID(GROUPID_TextureQuality);
		pWindowVideo->AddElement(pGroupTextureQuality);

		UI::LPCHECKBOX pCheckBoxTextureHigh = std::make_shared<UI::CheckBox>(Rectangle2D(24, 258, 13, 13));
		pCheckBoxTextureHigh->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxTextureHigh->SetText("High");
		pCheckBoxTextureHigh->SetGroup(pGroupTextureQuality);
		pCheckBoxTextureHigh->SetID(CHECKBOXID_TextureHigh);
		pCheckBoxTextureHigh->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowVideo->AddElement(pCheckBoxTextureHigh);

		UI::LPCHECKBOX pCheckBoxTextureLow = std::make_shared<UI::CheckBox>(Rectangle2D(112, 258, 13, 13));
		pCheckBoxTextureLow->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxTextureLow->SetText("Low");
		pCheckBoxTextureLow->SetGroup(pGroupTextureQuality);
		pCheckBoxTextureLow->SetID(CHECKBOXID_TextureLow);
		pCheckBoxTextureLow->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowVideo->AddElement(pCheckBoxTextureLow);

		//Text Anti Aliasing
		UI::LPTEXT pTextAntiAliasing = std::make_shared<UI::Text>(Rectangle2D(24, 318, 0, 0));
		pTextAntiAliasing->SetFont("Arial", 16, 0, FALSE, TRUE, -1);
		pTextAntiAliasing->SetText("Anti Aliasing:");
		pWindowVideo->AddElement(pTextAntiAliasing);

		//Group Anti Aliasing
		UI::LPGROUP pGroupAntiAliasing = std::make_shared<UI::Group>();
		pGroupAntiAliasing->SetID(GROUPID_AntiAliasing);
		pWindowVideo->AddElement(pGroupAntiAliasing);

		UI::LPCHECKBOX pCheckBoxAntiAliasingON = std::make_shared<UI::CheckBox>(Rectangle2D(24, 338, 13, 13));
		pCheckBoxAntiAliasingON->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxAntiAliasingON->SetText("ON");
		pCheckBoxAntiAliasingON->SetGroup(pGroupAntiAliasing);
		pCheckBoxAntiAliasingON->SetID(CHECKBOXID_AntiAliasingON);
		pCheckBoxAntiAliasingON->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowVideo->AddElement(pCheckBoxAntiAliasingON);

		UI::LPCHECKBOX pCheckBoxAntiAliasingOFF = std::make_shared<UI::CheckBox>(Rectangle2D(112, 338, 13, 13));
		pCheckBoxAntiAliasingOFF->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxAntiAliasingOFF->SetText("OFF");
		pCheckBoxAntiAliasingOFF->SetGroup(pGroupAntiAliasing);
		pCheckBoxAntiAliasingOFF->SetID(CHECKBOXID_AntiAliasingOFF);
		pCheckBoxAntiAliasingOFF->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowVideo->AddElement(pCheckBoxAntiAliasingOFF);

		//Text V - Sync
		UI::LPTEXT pTextVSync = std::make_shared<UI::Text>(Rectangle2D(24, 278, 0, 0));
		pTextVSync->SetFont("Arial", 16, 0, FALSE, TRUE, -1);
		pTextVSync->SetText("V-Sync:");
		pWindowVideo->AddElement(pTextVSync);

		//Group V - Sync
		UI::LPGROUP pGroupVSync = std::make_shared<UI::Group>();
		pGroupVSync->SetID(GROUPID_VSync);
		pWindowVideo->AddElement(pGroupVSync);

		UI::LPCHECKBOX pCheckBoxVSyncON = std::make_shared<UI::CheckBox>(Rectangle2D(24, 298, 13, 13));
		pCheckBoxVSyncON->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxVSyncON->SetText("ON");
		pCheckBoxVSyncON->SetGroup(pGroupVSync);
		pCheckBoxVSyncON->SetID(CHECKBOXID_VSyncON);
		pCheckBoxVSyncON->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowVideo->AddElement(pCheckBoxVSyncON);

		UI::LPCHECKBOX pCheckBoxVSyncOFF = std::make_shared<UI::CheckBox>(Rectangle2D(112, 298, 13, 13));
		pCheckBoxVSyncOFF->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxVSyncOFF->SetText("OFF");
		pCheckBoxVSyncOFF->SetGroup(pGroupVSync);
		pCheckBoxVSyncOFF->SetID(CHECKBOXID_VSyncOFF);
		pCheckBoxVSyncOFF->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowVideo->AddElement(pCheckBoxVSyncOFF);

		//Text Bit Depth
		UI::LPTEXT pTextBitDepth = std::make_shared<UI::Text>(Rectangle2D(204, 238, 0, 0));
		pTextBitDepth->SetFont("Arial", 16, 0, FALSE, TRUE, -1);
		pTextBitDepth->SetText("Bit Depth:");
		pWindowVideo->AddElement(pTextBitDepth);

		//Group Bit Depth
		UI::LPGROUP pGroupBitDepth = std::make_shared<UI::Group>();
		pGroupBitDepth->SetID(GROUPID_BitDepth);
		pWindowVideo->AddElement(pGroupBitDepth);

		UI::LPCHECKBOX pCheckBox32BPP = std::make_shared<UI::CheckBox>(Rectangle2D(204, 258, 13, 13));
		pCheckBox32BPP->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBox32BPP->SetText("32 bit");
		pCheckBox32BPP->SetGroup(pGroupBitDepth);
		pCheckBox32BPP->SetID(CHECKBOXID_32BPP);
		pCheckBox32BPP->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowVideo->AddElement(pCheckBox32BPP);

		UI::LPCHECKBOX pCheckBox16BPP = std::make_shared<UI::CheckBox>(Rectangle2D(292, 258, 13, 13));
		pCheckBox16BPP->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBox16BPP->SetText("16 bit");
		pCheckBox16BPP->SetGroup(pGroupBitDepth);
		pCheckBox16BPP->SetID(CHECKBOXID_16BPP);
		pCheckBox16BPP->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowVideo->AddElement(pCheckBox16BPP);

		//Text Effects
		UI::LPTEXT pTextEffects = std::make_shared<UI::Text>(Rectangle2D(204, 278, 0, 0));
		pTextEffects->SetFont("Arial", 16, 0, FALSE, TRUE, -1);
		pTextEffects->SetText("Effects:");
		pWindowVideo->AddElement(pTextEffects);

		//Group Effects
		UI::LPGROUP pGroupEffects = std::make_shared<UI::Group>();
		pGroupEffects->SetID(GROUPID_Effects);
		pWindowVideo->AddElement(pGroupEffects);

		UI::LPCHECKBOX pCheckBoxEffectsON = std::make_shared<UI::CheckBox>(Rectangle2D(204, 298, 13, 13));
		pCheckBoxEffectsON->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxEffectsON->SetText("ON");
		pCheckBoxEffectsON->SetGroup(pGroupEffects);
		pCheckBoxEffectsON->SetID(CHECKBOXID_EffectsON);
		pCheckBoxEffectsON->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowVideo->AddElement(pCheckBoxEffectsON);

		UI::LPCHECKBOX pCheckBoxEffectsOFF = std::make_shared<UI::CheckBox>(Rectangle2D(292, 298, 13, 13));
		pCheckBoxEffectsOFF->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxEffectsOFF->SetText("OFF");
		pCheckBoxEffectsOFF->SetGroup(pGroupEffects);
		pCheckBoxEffectsOFF->SetID(CHECKBOXID_EffectsOFF);
		pCheckBoxEffectsOFF->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowVideo->AddElement(pCheckBoxEffectsOFF);

		//Title Camera
		UI::LPIMAGEBOX pCameraBar = std::make_shared<UI::ImageBox>(Rectangle2D(34, 365, 339, 23));
		pCameraBar->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Settings\\Title.png"));
		pWindowVideo->AddElement(pCameraBar);

		UI::LPIMAGEBOX pCameraTitle = std::make_shared<UI::ImageBox>(Rectangle2D(130, 370, 150, 14));
		pCameraTitle->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Settings\\Camera.png"));
		pWindowVideo->AddElement(pCameraTitle);

		//Text Camera iSight
		UI::LPTEXT pTextCameraSight = std::make_shared<UI::Text>(Rectangle2D(24, 401, 0, 0));
		pTextCameraSight->SetFont("Arial", 16, 0, FALSE, TRUE, -1);
		pTextCameraSight->SetText("Camera Range:");
		pWindowVideo->AddElement(pTextCameraSight);

		//Group CameraSight
		UI::LPGROUP pGroupCameraSight = std::make_shared<UI::Group>();
		pGroupCameraSight->SetID(GROUPID_CameraSight);
		pWindowVideo->AddElement(pGroupCameraSight);

		UI::LPCHECKBOX pCheckBoxCameraFull = std::make_shared<UI::CheckBox>(Rectangle2D(24, 421, 13, 13));
		pCheckBoxCameraFull->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxCameraFull->SetText("Full");
		pCheckBoxCameraFull->SetGroup(pGroupCameraSight);
		pCheckBoxCameraFull->SetID(CHECKBOXID_Full);
		pCheckBoxCameraFull->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowVideo->AddElement(pCheckBoxCameraFull);

		UI::LPCHECKBOX pCheckBoxCameraFar = std::make_shared<UI::CheckBox>(Rectangle2D(112, 421, 13, 13));
		pCheckBoxCameraFar->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxCameraFar->SetText("Far");
		pCheckBoxCameraFar->SetGroup(pGroupCameraSight);
		pCheckBoxCameraFar->SetID(CHECKBOXID_Far);
		pCheckBoxCameraFar->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowVideo->AddElement(pCheckBoxCameraFar);

		UI::LPCHECKBOX pCheckBoxCameraShort = std::make_shared<UI::CheckBox>(Rectangle2D(24, 441, 13, 13));
		pCheckBoxCameraShort->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxCameraShort->SetText("Short");
		pCheckBoxCameraShort->SetGroup(pGroupCameraSight);
		pCheckBoxCameraShort->SetID(CHECKBOXID_Short);
		pCheckBoxCameraShort->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowVideo->AddElement(pCheckBoxCameraShort);

		//Text Camera Inverted
		UI::LPTEXT pTextInvertCamera = std::make_shared<UI::Text>(Rectangle2D(204, 401, 0, 0));
		pTextInvertCamera->SetFont("Arial", 16, 0, FALSE, TRUE, -1);
		pTextInvertCamera->SetText("Inverted Camera:");
		pWindowVideo->AddElement(pTextInvertCamera);

		//Group CameraSight
		UI::LPGROUP pGroupInvertedCamera = std::make_shared<UI::Group>();
		pGroupInvertedCamera->SetID(GROUPID_InvertedCamera);
		pWindowVideo->AddElement(pGroupInvertedCamera);

		UI::LPCHECKBOX pCheckBoxCameraON = std::make_shared<UI::CheckBox>(Rectangle2D(204, 421, 13, 13));
		pCheckBoxCameraON->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxCameraON->SetText("ON");
		pCheckBoxCameraON->SetGroup(pGroupInvertedCamera);
		pCheckBoxCameraON->SetID(CHECKBOXID_CameraON);
		pCheckBoxCameraON->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowVideo->AddElement(pCheckBoxCameraON);

		UI::LPCHECKBOX pCheckBoxCameraOFF = std::make_shared<UI::CheckBox>(Rectangle2D(292, 421, 13, 13));
		pCheckBoxCameraOFF->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxCameraOFF->SetText("OFF");
		pCheckBoxCameraOFF->SetGroup(pGroupInvertedCamera);
		pCheckBoxCameraOFF->SetID(CHECKBOXID_CameraOFF);
		pCheckBoxCameraOFF->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowVideo->AddElement(pCheckBoxCameraOFF);

		GetListMain()->AddWindow(pWindowVideo);
	}
	void Window::BuildAudio()
	{
		UI::LPWINDOW pWindowAudio = std::make_shared<UI::Window>(Rectangle2D(0, 0, 400, 395));
		pWindowAudio->SetID(WINDOWID_Audio);

		//Title Backgound Music
		UI::LPIMAGEBOX pBackgroundMusicBar = std::make_shared<UI::ImageBox>(Rectangle2D(34, 11, 339, 23));
		pBackgroundMusicBar->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Settings\\Title.png"));
		pWindowAudio->AddElement(pBackgroundMusicBar);

		UI::LPIMAGEBOX pBackgroundMusicTitle = std::make_shared<UI::ImageBox>(Rectangle2D(130, 16, 150, 14));
		pBackgroundMusicTitle->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Settings\\BGMusic.png"));
		pWindowAudio->AddElement(pBackgroundMusicTitle);

		//Text Backgound Music
		UI::LPTEXT pTextBackgroundMusic = std::make_shared<UI::Text>(Rectangle2D(24, 47, 0, 0));
		pTextBackgroundMusic->SetFont("Arial", 16, 0, FALSE, TRUE, -1);
		pTextBackgroundMusic->SetText("Background Music:");
		pWindowAudio->AddElement(pTextBackgroundMusic);

		//Background Controller
		UI::LPIMAGEBOX pBackgroundControllMusic = std::make_shared<UI::ImageBox>(Rectangle2D(13, 70, 386, 56));
		pBackgroundControllMusic->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Settings\\BGController.png"));
		pWindowAudio->AddElement(pBackgroundControllMusic);

		//Scroller Background
		UI::LPSCROLL pScrollBackgroundMusic = std::make_shared<UI::Scroll>(Rectangle2D(110, 95, 265, 8));
		pScrollBackgroundMusic->SetVertical(FALSE);
		pScrollBackgroundMusic->SetMinMax(0, 100);
		pScrollBackgroundMusic->SetID(SCROLLID_BGMusic);
		pScrollBackgroundMusic->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Scroll\\Barbg.png"));
		pScrollBackgroundMusic->SetImageBackground(UI::ImageLoader::LoadImage_("Resources\\UI\\Scroll\\Bar.png"));
		pScrollBackgroundMusic->SetScroller(UI::ImageLoader::LoadImage_("Resources\\UI\\Scroll\\Icon.png"), 20, 20);
		pWindowAudio->AddElement(pScrollBackgroundMusic);

		//Checkbox No iSound
		UI::LPCHECKBOX pCheckBoxNoMusic = std::make_shared<UI::CheckBox>(Rectangle2D(23, 93, 13, 13));
		pCheckBoxNoMusic->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxNoMusic->SetText("ON Music");
		pCheckBoxNoMusic->SetID(CHECKBOXID_NoMusic);
		pCheckBoxNoMusic->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowAudio->AddElement(pCheckBoxNoMusic);

		//Title iSound Effects
		UI::LPIMAGEBOX pSoundEffectsBar = std::make_shared<UI::ImageBox>(Rectangle2D(34, 145, 339, 23));
		pSoundEffectsBar->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Settings\\Title.png"));
		pWindowAudio->AddElement(pSoundEffectsBar);

		UI::LPIMAGEBOX pSoundEffectsTitle = std::make_shared<UI::ImageBox>(Rectangle2D(130, 150, 150, 14));
		pSoundEffectsTitle->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Settings\\BGMusic.png"));
		pWindowAudio->AddElement(pSoundEffectsTitle);

		//Text iSound Effects
		UI::LPTEXT pTextSoundEffects = std::make_shared<UI::Text>(Rectangle2D(24, 181, 0, 0));
		pTextSoundEffects->SetFont("Arial", 16, 0, FALSE, TRUE, -1);
		pTextSoundEffects->SetText("Sound Effects:");
		pWindowAudio->AddElement(pTextSoundEffects);

		//Background Controller
		UI::LPIMAGEBOX pBackgroundControllerSound = std::make_shared<UI::ImageBox>(Rectangle2D(13, 204, 386, 56));
		pBackgroundControllerSound->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Settings\\BGController.png"));
		pWindowAudio->AddElement(pBackgroundControllerSound);

		//Scroller Background
		UI::LPSCROLL pScrollEffectSound = std::make_shared<UI::Scroll>(Rectangle2D(110, 230, 265, 8));
		pScrollEffectSound->SetVertical(FALSE);
		pScrollEffectSound->SetMinMax(0, 100);
		pScrollEffectSound->SetID(SCROLLID_EffectSound);
		pScrollEffectSound->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Scroll\\Barbg.png"));
		pScrollEffectSound->SetImageBackground(UI::ImageLoader::LoadImage_("Resources\\UI\\Scroll\\Bar.png"));
		pScrollEffectSound->SetScroller(UI::ImageLoader::LoadImage_("Resources\\UI\\Scroll\\Icon.png"), 20, 20);
		pWindowAudio->AddElement(pScrollEffectSound);

		//Checkbox No iSound
		UI::LPCHECKBOX pCheckBoxNoEffects = std::make_shared<UI::CheckBox>(Rectangle2D(23, 228, 13, 13));
		pCheckBoxNoEffects->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxNoEffects->SetText("ON Effects");
		pCheckBoxNoEffects->SetID(CHECKBOXID_NoEffects);
		pCheckBoxNoEffects->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowAudio->AddElement(pCheckBoxNoEffects);

		pWindowAudio->Hide();

		GetListMain()->AddWindow(pWindowAudio);
	}
	void Window::BuildGeneral()
	{
		UI::LPWINDOW pWindowGeneral = std::make_shared<UI::Window>(Rectangle2D(0, 0, 400, 860));
		pWindowGeneral->SetID(WINDOWID_General);

		//Title social
		UI::LPIMAGEBOX pSocialBar = std::make_shared<UI::ImageBox>(Rectangle2D(34, 11, 339, 23));
		pSocialBar->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Settings\\Title.png"));
		pWindowGeneral->AddElement(pSocialBar);


		UI::LPIMAGEBOX pSocialTitle = std::make_shared<UI::ImageBox>(Rectangle2D(130, 16, 150, 14));
		pSocialTitle->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Settings\\Social.png"));
		pWindowGeneral->AddElement(pSocialTitle);

		//Disable Party Requests
		UI::LPCHECKBOX pCheckBoxDisableParty = std::make_shared<UI::CheckBox>(Rectangle2D(24, 47, 13, 13));
		pCheckBoxDisableParty->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxDisableParty->SetText("Disable Party Requests");
		pCheckBoxDisableParty->SetID(CHECKBOXID_DisableParty);
		pCheckBoxDisableParty->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowGeneral->AddElement(pCheckBoxDisableParty);

		//Disable Trade Requests
		UI::LPCHECKBOX pCheckBoxDisableTrade = std::make_shared<UI::CheckBox>(Rectangle2D(24, 67, 13, 13));
		pCheckBoxDisableTrade->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxDisableTrade->SetText("Disable Trade Requests");
		pCheckBoxDisableTrade->SetID(CHECKBOXID_DisableTrade);
		pCheckBoxDisableTrade->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowGeneral->AddElement(pCheckBoxDisableTrade);

		//No Whisper
		UI::LPCHECKBOX pCheckBoxNoWhisper = std::make_shared<UI::CheckBox>(Rectangle2D(24, 87, 13, 13));
		pCheckBoxNoWhisper->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxNoWhisper->SetText("No Whisper");
		pCheckBoxNoWhisper->SetID(CHECKBOXID_NoWhisper);
		pCheckBoxNoWhisper->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowGeneral->AddElement(pCheckBoxNoWhisper);

		//No Trade chat in All
		UI::LPCHECKBOX pCheckBoxNoTrade = std::make_shared<UI::CheckBox>(Rectangle2D(24, 107, 13, 13));
		pCheckBoxNoTrade->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxNoTrade->SetText("No Trade Chat in All");
		pCheckBoxNoTrade->SetID(CHECKBOXID_NoTrade);
		pCheckBoxNoTrade->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowGeneral->AddElement(pCheckBoxNoTrade);

		//Title Keyboard
		UI::LPIMAGEBOX pPersonalizationBar = std::make_shared<UI::ImageBox>(Rectangle2D(34, 130, 339, 23));
		pPersonalizationBar->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Settings\\Title.png"));
		pWindowGeneral->AddElement(pPersonalizationBar);

		UI::LPIMAGEBOX pPersonalizationTitle = std::make_shared<UI::ImageBox>(Rectangle2D(130, 135, 150, 14));
		pPersonalizationTitle->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Settings\\Personalization.png"));
		pWindowGeneral->AddElement(pPersonalizationTitle);

		//Text
		UI::LPTEXT pTextDamageDebug = std::make_shared<UI::Text>(Rectangle2D(24, 167, 0, 0));
		pTextDamageDebug->SetFont("Arial", 16, 0, FALSE, TRUE, -1);
		pTextDamageDebug->SetText("Damage Debug:");
		pWindowGeneral->AddElement(pTextDamageDebug);

		//Group
		UI::LPGROUP pGroupDamageDebug = std::make_shared<UI::Group>();
		pGroupDamageDebug->SetID(GROUPID_DamageDebug);
		pWindowGeneral->AddElement(pGroupDamageDebug);

		UI::LPCHECKBOX pCheckBoxDamageDebugON = std::make_shared<UI::CheckBox>(Rectangle2D(24, 187, 13, 13));
		pCheckBoxDamageDebugON->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxDamageDebugON->SetText("ON");
		pCheckBoxDamageDebugON->SetGroup(pGroupDamageDebug);
		pCheckBoxDamageDebugON->SetID(CHECKBOXID_DamageDebugON);
		pCheckBoxDamageDebugON->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowGeneral->AddElement(pCheckBoxDamageDebugON);

		UI::LPCHECKBOX pCheckBoxDamageDebugOFF = std::make_shared<UI::CheckBox>(Rectangle2D(112, 187, 13, 13));
		pCheckBoxDamageDebugOFF->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxDamageDebugOFF->SetText("ON");
		pCheckBoxDamageDebugOFF->SetGroup(pGroupDamageDebug);
		pCheckBoxDamageDebugOFF->SetID(CHECKBOXID_DamageDebugOFF);
		pCheckBoxDamageDebugOFF->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowGeneral->AddElement(pCheckBoxDamageDebugOFF);

		//Text
		UI::LPTEXT pTextHPBar = std::make_shared<UI::Text>(Rectangle2D(204, 167, 0, 0));
		pTextHPBar->SetFont("Arial", 16, 0, FALSE, TRUE, -1);
		pTextHPBar->SetText("HP Bar on Head:");
		pWindowGeneral->AddElement(pTextHPBar);

		//Group
		UI::LPGROUP pGroupHPBar = std::make_shared<UI::Group>();
		pGroupHPBar->SetID(GROUPID_HPBar);
		pWindowGeneral->AddElement(pGroupHPBar);

		UI::LPCHECKBOX pCheckBoxHPBarON = std::make_shared<UI::CheckBox>(Rectangle2D(204, 187, 13, 13));
		pCheckBoxHPBarON->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxHPBarON->SetText("ON");
		pCheckBoxHPBarON->SetGroup(pGroupHPBar);
		pCheckBoxHPBarON->SetID(CHECKBOXID_HPBarON);
		pCheckBoxHPBarON->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowGeneral->AddElement(pCheckBoxHPBarON);

		UI::LPCHECKBOX pCheckBoxHPBarOFF = std::make_shared<UI::CheckBox>(Rectangle2D(294, 187, 13, 13));
		pCheckBoxHPBarOFF->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxHPBarOFF->SetText("OFF");
		pCheckBoxHPBarOFF->SetGroup(pGroupHPBar);
		pCheckBoxHPBarOFF->SetID(CHECKBOXID_HPBarOFF);
		pCheckBoxHPBarOFF->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowGeneral->AddElement(pCheckBoxHPBarOFF);

		//Text
		UI::LPTEXT pTextFPS = std::make_shared<UI::Text>(Rectangle2D(24, 207, 0, 0));
		pTextFPS->SetFont("Arial", 16, 0, FALSE, TRUE, -1);
		pTextFPS->SetText("FPS:");
		pWindowGeneral->AddElement(pTextFPS);

		//Group
		UI::LPGROUP pGroupFPS = std::make_shared<UI::Group>();
		pGroupFPS->SetID(GROUPID_FPS);
		pWindowGeneral->AddElement(pGroupFPS);

		UI::LPCHECKBOX pCheckBoxFPSON = std::make_shared<UI::CheckBox>(Rectangle2D(24, 227, 13, 13));
		pCheckBoxFPSON->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxFPSON->SetText("ON");
		pCheckBoxFPSON->SetGroup(pGroupFPS);
		pCheckBoxFPSON->SetID(CHECKBOXID_FPSON);
		pCheckBoxFPSON->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowGeneral->AddElement(pCheckBoxFPSON);

		UI::LPCHECKBOX pCheckBoxFPSOFF = std::make_shared<UI::CheckBox>(Rectangle2D(112, 227, 13, 13));
		pCheckBoxFPSOFF->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxFPSOFF->SetText("OFF");
		pCheckBoxFPSOFF->SetGroup(pGroupFPS);
		pCheckBoxFPSOFF->SetID(CHECKBOXID_FPSOFF);
		pCheckBoxFPSOFF->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowGeneral->AddElement(pCheckBoxFPSOFF);

		//Text
		UI::LPTEXT pTextPing = std::make_shared<UI::Text>(Rectangle2D(204, 207, 0, 0));
		pTextPing->SetFont("Arial", 16, 0, FALSE, TRUE, -1);
		pTextPing->SetText("Ping:");
		pWindowGeneral->AddElement(pTextPing);

		//Group
		UI::LPGROUP pGroupPing = std::make_shared<UI::Group>();
		pGroupPing->SetID(GROUPID_Ping);
		pWindowGeneral->AddElement(pGroupPing);

		UI::LPCHECKBOX pCheckBoxPingON = std::make_shared<UI::CheckBox>(Rectangle2D(204, 227, 13, 13));
		pCheckBoxPingON->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxPingON->SetText("ON");
		pCheckBoxPingON->SetGroup(pGroupPing);
		pCheckBoxPingON->SetID(CHECKBOXID_PingON);
		pCheckBoxPingON->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowGeneral->AddElement(pCheckBoxPingON);

		UI::LPCHECKBOX pCheckBoxPingOFF = std::make_shared<UI::CheckBox>(Rectangle2D(292, 227, 13, 13));
		pCheckBoxPingOFF->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxPingOFF->SetText("OFF");
		pCheckBoxPingOFF->SetGroup(pGroupPing);
		pCheckBoxPingOFF->SetID(CHECKBOXID_PingOFF);
		pCheckBoxPingOFF->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowGeneral->AddElement(pCheckBoxPingOFF);

		//Text
		UI::LPTEXT pTextKillInfo = std::make_shared<UI::Text>(Rectangle2D(24, 247, 0, 0));
		pTextKillInfo->SetFont("Arial", 16, 0, FALSE, TRUE, -1);
		pTextKillInfo->SetText("KillInfo:");
		pWindowGeneral->AddElement(pTextKillInfo);

		//Group
		UI::LPGROUP pGroupKillInfo = std::make_shared<UI::Group>();
		pGroupKillInfo->SetID(GROUPID_KillInfo);
		pWindowGeneral->AddElement(pGroupKillInfo);

		UI::LPCHECKBOX pCheckBoxKillInfoON = std::make_shared<UI::CheckBox>(Rectangle2D(24, 267, 13, 13));
		pCheckBoxKillInfoON->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxKillInfoON->SetText("ON");
		pCheckBoxKillInfoON->SetGroup(pGroupKillInfo);
		pCheckBoxKillInfoON->SetID(CHECKBOXID_KillInfoON);
		pCheckBoxKillInfoON->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowGeneral->AddElement(pCheckBoxKillInfoON);

		UI::LPCHECKBOX pCheckBoxKillInfoOFF = std::make_shared<UI::CheckBox>(Rectangle2D(112, 267, 13, 13));
		pCheckBoxKillInfoOFF->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxKillInfoOFF->SetText("OFF");
		pCheckBoxKillInfoOFF->SetGroup(pGroupKillInfo);
		pCheckBoxKillInfoOFF->SetID(CHECKBOXID_KillInfoOFF);
		pCheckBoxKillInfoOFF->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pWindowGeneral->AddElement(pCheckBoxKillInfoOFF);

		int iY = 0;

		iY += 296;

		UI::LPTEXT pTextLootFilter = std::make_shared<UI::Text>(Rectangle2D(24, iY, 0, 0));
		pTextLootFilter->SetFont("Arial", 16, 0, FALSE, TRUE, -1);
		pTextLootFilter->SetText("Loot Filter:");
		pWindowGeneral->AddElement(pTextLootFilter);

		iY += 20;

		//Loot
		{
			UI::LPCHECKBOX pCheckBoxLoot = std::make_shared<UI::CheckBox>(Rectangle2D(24, iY, 13, 13));
			pCheckBoxLoot->SetFont("Arial", 16, 6, FALSE, TRUE, -1);
			pCheckBoxLoot->SetText("Enable Loot Filter");
			pCheckBoxLoot->SetID(CHECKBOXID_LootFilterEnable);
			pCheckBoxLoot->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
			pWindowGeneral->AddElement(pCheckBoxLoot);
			iY += 30;

			int iYLootSpec = iY;

			pCheckBoxLoot = std::make_shared<UI::CheckBox>(Rectangle2D(24, iY, 13, 13));
			pCheckBoxLoot->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
			pCheckBoxLoot->SetText("HP Potion");
			pCheckBoxLoot->SetID(CHECKBOXID_LootHPPotion);
			pCheckBoxLoot->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
			pWindowGeneral->AddElement(pCheckBoxLoot);
			iY += 20;

			pCheckBoxLoot = std::make_shared<UI::CheckBox>(Rectangle2D(24, iY, 13, 13));
			pCheckBoxLoot->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
			pCheckBoxLoot->SetText("MP Potion");
			pCheckBoxLoot->SetID(CHECKBOXID_LootMPPotion);
			pCheckBoxLoot->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
			pWindowGeneral->AddElement(pCheckBoxLoot);
			iY += 20;

			pCheckBoxLoot = std::make_shared<UI::CheckBox>(Rectangle2D(24, iY, 13, 13));
			pCheckBoxLoot->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
			pCheckBoxLoot->SetText("SP Potion");
			pCheckBoxLoot->SetID(CHECKBOXID_LootSPPotion);
			pCheckBoxLoot->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
			pWindowGeneral->AddElement(pCheckBoxLoot);
			iY += 20;

			pCheckBoxLoot = std::make_shared<UI::CheckBox>(Rectangle2D(24, iY, 13, 13));
			pCheckBoxLoot->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
			pCheckBoxLoot->SetText("Gold");
			pCheckBoxLoot->SetID(CHECKBOXID_LootGold);
			pCheckBoxLoot->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
			pWindowGeneral->AddElement(pCheckBoxLoot);
			iY += 20;

			pCheckBoxLoot = std::make_shared<UI::CheckBox>(Rectangle2D(24, iY, 13, 13));
			pCheckBoxLoot->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
			pCheckBoxLoot->SetText("Amulets");
			pCheckBoxLoot->SetID(CHECKBOXID_LootAmulets);
			pCheckBoxLoot->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
			pWindowGeneral->AddElement(pCheckBoxLoot);
			iY += 20;

			pCheckBoxLoot = std::make_shared<UI::CheckBox>(Rectangle2D(24, iY, 13, 13));
			pCheckBoxLoot->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
			pCheckBoxLoot->SetText("Rings");
			pCheckBoxLoot->SetID(CHECKBOXID_LootRings);
			pCheckBoxLoot->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
			pWindowGeneral->AddElement(pCheckBoxLoot);
			iY += 20;

			pCheckBoxLoot = std::make_shared<UI::CheckBox>(Rectangle2D(24, iY, 13, 13));
			pCheckBoxLoot->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
			pCheckBoxLoot->SetText("Sheltoms");
			pCheckBoxLoot->SetID(CHECKBOXID_LootSheltoms);
			pCheckBoxLoot->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
			pWindowGeneral->AddElement(pCheckBoxLoot);
			iY += 20;

			pCheckBoxLoot = std::make_shared<UI::CheckBox>(Rectangle2D(24, iY, 13, 13));
			pCheckBoxLoot->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
			pCheckBoxLoot->SetText("Force Orbs");
			pCheckBoxLoot->SetID(CHECKBOXID_LootForceOrbs);
			pCheckBoxLoot->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
			pWindowGeneral->AddElement(pCheckBoxLoot);
			iY += 20;

			pCheckBoxLoot = std::make_shared<UI::CheckBox>(Rectangle2D(24, iY, 13, 13));
			pCheckBoxLoot->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
			pCheckBoxLoot->SetText("Premiums");
			pCheckBoxLoot->SetID(CHECKBOXID_LootPremiums);
			pCheckBoxLoot->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
			pWindowGeneral->AddElement(pCheckBoxLoot);
			iY += 20;

			pCheckBoxLoot = std::make_shared<UI::CheckBox>(Rectangle2D(24, iY, 13, 13));
			pCheckBoxLoot->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
			pCheckBoxLoot->SetText("Monster Crystals");
			pCheckBoxLoot->SetID(CHECKBOXID_LootMonsterCrystals);
			pCheckBoxLoot->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
			pWindowGeneral->AddElement(pCheckBoxLoot);
			iY += 20;

			pCheckBoxLoot = std::make_shared<UI::CheckBox>(Rectangle2D(24, iY, 13, 13));
			pCheckBoxLoot->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
			pCheckBoxLoot->SetText("Defense Items");
			pCheckBoxLoot->SetID(CHECKBOXID_LootDefenseItems);
			pCheckBoxLoot->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
			pWindowGeneral->AddElement(pCheckBoxLoot);
			iY += 20;

			pCheckBoxLoot = std::make_shared<UI::CheckBox>(Rectangle2D(24, iY, 13, 13));
			pCheckBoxLoot->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
			pCheckBoxLoot->SetText("Offense Items");
			pCheckBoxLoot->SetID(CHECKBOXID_LootOffenseItems);
			pCheckBoxLoot->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
			pWindowGeneral->AddElement(pCheckBoxLoot);
			iY += 20;

			pCheckBoxLoot = std::make_shared<UI::CheckBox>(Rectangle2D(24, iY, 13, 13));
			pCheckBoxLoot->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
			pCheckBoxLoot->SetText("Everything Else");
			pCheckBoxLoot->SetID(CHECKBOXID_LootEverything);
			pCheckBoxLoot->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
			pWindowGeneral->AddElement(pCheckBoxLoot);
			iY += 20;

			int iOldY = iY;

			//Spec Loot
			iY = iYLootSpec;
			pCheckBoxLoot = std::make_shared<UI::CheckBox>(Rectangle2D(204, iY, 13, 13));
			pCheckBoxLoot->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
			pCheckBoxLoot->SetText("Non Spec");
			pCheckBoxLoot->SetID(CHECKBOXID_LootSpecNS);
			pCheckBoxLoot->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
			pWindowGeneral->AddElement(pCheckBoxLoot);
			iY += 20;

			pCheckBoxLoot = std::make_shared<UI::CheckBox>(Rectangle2D(204, iY, 13, 13));
			pCheckBoxLoot->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
			pCheckBoxLoot->SetText("Fighter");
			pCheckBoxLoot->SetID(CHECKBOXID_LootSpecFS);
			pCheckBoxLoot->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
			pWindowGeneral->AddElement(pCheckBoxLoot);
			iY += 20;

			pCheckBoxLoot = std::make_shared<UI::CheckBox>(Rectangle2D(204, iY, 13, 13));
			pCheckBoxLoot->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
			pCheckBoxLoot->SetText("Mechanician");
			pCheckBoxLoot->SetID(CHECKBOXID_LootSpecMS);
			pCheckBoxLoot->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
			pWindowGeneral->AddElement(pCheckBoxLoot);
			iY += 20;

			pCheckBoxLoot = std::make_shared<UI::CheckBox>(Rectangle2D(204, iY, 13, 13));
			pCheckBoxLoot->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
			pCheckBoxLoot->SetText("Archer");
			pCheckBoxLoot->SetID(CHECKBOXID_LootSpecAS);
			pCheckBoxLoot->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
			pWindowGeneral->AddElement(pCheckBoxLoot);
			iY += 20;

			pCheckBoxLoot = std::make_shared<UI::CheckBox>(Rectangle2D(204, iY, 13, 13));
			pCheckBoxLoot->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
			pCheckBoxLoot->SetText("Pikeman");
			pCheckBoxLoot->SetID(CHECKBOXID_LootSpecPS);
			pCheckBoxLoot->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
			pWindowGeneral->AddElement(pCheckBoxLoot);
			iY += 20;

			pCheckBoxLoot = std::make_shared<UI::CheckBox>(Rectangle2D(204, iY, 13, 13));
			pCheckBoxLoot->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
			pCheckBoxLoot->SetText("Atalanta");
			pCheckBoxLoot->SetID(CHECKBOXID_LootSpecATA);
			pCheckBoxLoot->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
			pWindowGeneral->AddElement(pCheckBoxLoot);
			iY += 20;

			pCheckBoxLoot = std::make_shared<UI::CheckBox>(Rectangle2D(204, iY, 13, 13));
			pCheckBoxLoot->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
			pCheckBoxLoot->SetText("Knight");
			pCheckBoxLoot->SetID(CHECKBOXID_LootSpecKS);
			pCheckBoxLoot->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
			pWindowGeneral->AddElement(pCheckBoxLoot);
			iY += 20;

			pCheckBoxLoot = std::make_shared<UI::CheckBox>(Rectangle2D(204, iY, 13, 13));
			pCheckBoxLoot->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
			pCheckBoxLoot->SetText("Magician");
			pCheckBoxLoot->SetID(CHECKBOXID_LootSpecMGS);
			pCheckBoxLoot->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
			pWindowGeneral->AddElement(pCheckBoxLoot);
			iY += 20;

			pCheckBoxLoot = std::make_shared<UI::CheckBox>(Rectangle2D(204, iY, 13, 13));
			pCheckBoxLoot->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
			pCheckBoxLoot->SetText("Priestess");
			pCheckBoxLoot->SetID(CHECKBOXID_LootSpecPRS);
			pCheckBoxLoot->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
			pWindowGeneral->AddElement(pCheckBoxLoot);
			iY += 20;

			pCheckBoxLoot = std::make_shared<UI::CheckBox>(Rectangle2D(204, iY, 13, 13));
			pCheckBoxLoot->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
			pCheckBoxLoot->SetText("Assassin");
			pCheckBoxLoot->SetID(CHECKBOXID_LootSpecASS);
			pCheckBoxLoot->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
			pWindowGeneral->AddElement(pCheckBoxLoot);
			iY += 20;

			pCheckBoxLoot = std::make_shared<UI::CheckBox>(Rectangle2D(204, iY, 13, 13));
			pCheckBoxLoot->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
			pCheckBoxLoot->SetText("Shaman");
			pCheckBoxLoot->SetID(CHECKBOXID_LootSpecSHA);
			pCheckBoxLoot->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
			pWindowGeneral->AddElement(pCheckBoxLoot);
			iY += 20;

			iY = iOldY;
		}

		//Title Keyboard
		UI::LPIMAGEBOX pKeyboardBar = std::make_shared<UI::ImageBox>(Rectangle2D(34, iY, 339, 23));
		pKeyboardBar->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Settings\\Title.png"));
		pWindowGeneral->AddElement(pKeyboardBar);

		UI::LPIMAGEBOX pKeyboardTitle = std::make_shared<UI::ImageBox>(Rectangle2D(130, iY + 5, 150, 14));
		pKeyboardTitle->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Settings\\Keyboard.png"));
		pWindowGeneral->AddElement(pKeyboardTitle);

		//Group
		UI::LPGROUP pGroupMacro = std::make_shared<UI::Group>();
		pGroupMacro->SetID(GROUPID_Macro);
		pWindowGeneral->AddElement(pGroupMacro);

		iY += 36;

		for (int i = 0; i < 10; i++)
		{
			//Text
			UI::LPTEXT pTextMacro = std::make_shared<UI::Text>(Rectangle2D(24, (i * 20) + iY, 0, 0));
			pTextMacro->SetFont("Arial", 16, 0, FALSE, FALSE, -1);
			pTextMacro->SetText(FormatString("CTRL+F%d", i + 1));
			pWindowGeneral->AddElement(pTextMacro);

			//InputField
			UI::LPINPUTFIELD pInputField = std::make_shared<UI::InputField>(Rectangle2D(88, (i * 20) + iY, 290, 18));
			pInputField->SetID(InputFieldID_Macro1 + i);
			pInputField->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Settings\\Textbox.png"));
			pInputField->SetFont("Tahoma", 15, 0, FALSE, FALSE, -1);
			pInputField->SetText("");
			pInputField->SetMaxLength(32);
			pInputField->SetSelect(TRUE);
			//pInputField->SetRegex("[0-9a-zA-Z]{1,}");
			//pInputField->SetPasswordMode(TRUE);
			pInputField->SetGroup(pGroupMacro);
			pWindowGeneral->AddElement(pInputField);
		}

		pWindowGeneral->Hide();

		GetListMain()->AddWindow(pWindowGeneral);
	}
	void Window::BuildInterface()
	{
		UI::LPWINDOW pWindowInterface = std::make_shared<UI::Window>(Rectangle2D(0, 0, 400, 500));
		pWindowInterface->SetID(WINDOWID_Interface);

		//Title General
		UI::LPIMAGEBOX pGeneralBar = std::make_shared<UI::ImageBox>(Rectangle2D(34, 11, 339, 23));
		pGeneralBar->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Settings\\title.png"));
		pWindowInterface->AddElement(pGeneralBar);

		UI::LPIMAGEBOX pGeneralTitle = std::make_shared<UI::ImageBox>(Rectangle2D(130, 16, 150, 14));
		pGeneralTitle->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\Settings\\generalt.png"));
		pWindowInterface->AddElement(pGeneralTitle);

		//Lock User Interface
		UI::LPCHECKBOX pCheckBoxLockUI = std::make_shared<UI::CheckBox>(Rectangle2D(24, 48, 13, 13));
		pCheckBoxLockUI->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxLockUI->SetText("Lock User Interface");
		pCheckBoxLockUI->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pCheckBoxLockUI->SetID(CHECKBOXID_LockUI);
		pWindowInterface->AddElement(pCheckBoxLockUI);

		//Title Minimap
		UI::LPIMAGEBOX pMinimapBar = std::make_shared<UI::ImageBox>(Rectangle2D(34, 72, 339, 23));
		pMinimapBar->SetImage(UI::ImageLoader::LoadImage_("Resources\\settings\\title.png"));
		pWindowInterface->AddElement(pMinimapBar);

		UI::LPIMAGEBOX pMinimapTitle = std::make_shared<UI::ImageBox>(Rectangle2D(130, 77, 150, 14));
		pMinimapTitle->SetImage(UI::ImageLoader::LoadImage_("Resources\\settings\\minimap.png"));
		pWindowInterface->AddElement(pMinimapTitle);

		//Show Party Members
		UI::LPCHECKBOX pCheckBoxShowParty = std::make_shared<UI::CheckBox>(Rectangle2D(24, 112, 13, 13));
		pCheckBoxShowParty->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxShowParty->SetText("Show Party Members");
		pCheckBoxShowParty->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pCheckBoxShowParty->SetID(CHECKBOXID_ShowPartyMembers);
		pWindowInterface->AddElement(pCheckBoxShowParty);

		//Show Party Members
		UI::LPCHECKBOX pCheckBoxShowRaid = std::make_shared<UI::CheckBox>(Rectangle2D(24, 132, 13, 13));
		pCheckBoxShowRaid->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxShowRaid->SetText("Show Raid Members");
		pCheckBoxShowRaid->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pCheckBoxShowRaid->SetID(CHECKBOXID_ShowRaidMembers);
		pWindowInterface->AddElement(pCheckBoxShowRaid);

		//Show Clan Members
		UI::LPCHECKBOX pCheckBoxShowClan = std::make_shared<UI::CheckBox>(Rectangle2D(24, 152, 13, 13));
		pCheckBoxShowClan->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxShowClan->SetText("Show Clan Members");
		pCheckBoxShowClan->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pCheckBoxShowClan->SetID(CHECKBOXID_ShowClanMembers);
		pWindowInterface->AddElement(pCheckBoxShowClan);

		//Show Enemies
		UI::LPCHECKBOX pCheckBoxShowEnemies = std::make_shared<UI::CheckBox>(Rectangle2D(24, 172, 13, 13));
		pCheckBoxShowEnemies->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxShowEnemies->SetText("Show Enemies at Bless Castle");
		pCheckBoxShowEnemies->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pCheckBoxShowEnemies->SetID(CHECKBOXID_ShowEnemies);
		pWindowInterface->AddElement(pCheckBoxShowEnemies);

		//Show NPCs
		UI::LPCHECKBOX pCheckBoxShowNPCs = std::make_shared<UI::CheckBox>(Rectangle2D(24, 192, 13, 13));
		pCheckBoxShowNPCs->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxShowNPCs->SetText("Show NPCs");
		pCheckBoxShowNPCs->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pCheckBoxShowNPCs->SetID(CHECKBOXID_ShowNPCs);
		pWindowInterface->AddElement(pCheckBoxShowNPCs);

		//Show Next Boss Timer
		UI::LPCHECKBOX pCheckBoxShowBossTimer = std::make_shared<UI::CheckBox>(Rectangle2D(24, 212, 13, 13));
		pCheckBoxShowBossTimer->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxShowBossTimer->SetText("Show Next Boss Timer");
		pCheckBoxShowBossTimer->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pCheckBoxShowBossTimer->SetID(CHECKBOXID_ShowNextBossTimer);
		pWindowInterface->AddElement(pCheckBoxShowBossTimer);

		//Minimap Active
		UI::LPCHECKBOX pCheckBoxMinimapActive = std::make_shared<UI::CheckBox>(Rectangle2D(24, 232, 13, 13));
		pCheckBoxMinimapActive->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxMinimapActive->SetText("Always Active");
		pCheckBoxMinimapActive->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pCheckBoxMinimapActive->SetID(CHECKBOXID_AlwaysActive);
		pWindowInterface->AddElement(pCheckBoxMinimapActive);

		//Title Chat Box
		UI::LPIMAGEBOX pChatboxBar = std::make_shared<UI::ImageBox>(Rectangle2D(34, 260, 339, 23));
		pChatboxBar->SetImage(UI::ImageLoader::LoadImage_("Resources\\settings\\title.png"));
		pWindowInterface->AddElement(pChatboxBar);

		UI::LPIMAGEBOX pChatboxTitle = std::make_shared<UI::ImageBox>(Rectangle2D(130, 265, 150, 14));
		pChatboxTitle->SetImage(UI::ImageLoader::LoadImage_("Resources\\settings\\chatbox.png"));
		pWindowInterface->AddElement(pChatboxTitle);

		//Hide Notices
		UI::LPCHECKBOX pCheckBoxHideNotices = std::make_shared<UI::CheckBox>(Rectangle2D(24, 300, 13, 13));
		pCheckBoxHideNotices->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxHideNotices->SetText("Show 'Notice' info in Chatbox");
		pCheckBoxHideNotices->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pCheckBoxHideNotices->SetID(CHECKBOXID_ShowNotice);
		pWindowInterface->AddElement(pCheckBoxHideNotices);

		//Title Target
		UI::LPIMAGEBOX pTargetBar = std::make_shared<UI::ImageBox>(Rectangle2D(34, 324, 339, 23));
		pTargetBar->SetImage(UI::ImageLoader::LoadImage_("Resources\\settings\\title.png"));
		pWindowInterface->AddElement(pTargetBar);

		UI::LPIMAGEBOX pTargetTitle = std::make_shared<UI::ImageBox>(Rectangle2D(130, 329, 150, 14));
		pTargetTitle->SetImage(UI::ImageLoader::LoadImage_("Resources\\settings\\target.png"));
		pWindowInterface->AddElement(pTargetTitle);

		//Target Distance
		UI::LPCHECKBOX pCheckBoxTargetDistance = std::make_shared<UI::CheckBox>(Rectangle2D(24, 358, 13, 13));
		pCheckBoxTargetDistance->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxTargetDistance->SetText("Show Target Distance");
		pCheckBoxTargetDistance->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pCheckBoxTargetDistance->SetID(CHECKBOXID_TargetDistance);
		pWindowInterface->AddElement(pCheckBoxTargetDistance);

		//Target HP Value
		UI::LPCHECKBOX pCheckBoxTargetHPValue = std::make_shared<UI::CheckBox>(Rectangle2D(24, 378, 13, 13));
		pCheckBoxTargetHPValue->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxTargetHPValue->SetText("Show Target HP Value");
		pCheckBoxTargetHPValue->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pCheckBoxTargetHPValue->SetID(CHECKBOXID_TargetHPValue);
		pWindowInterface->AddElement(pCheckBoxTargetHPValue);

		//Target HP in percentage
		UI::LPCHECKBOX pCheckBoxTargetHPPercent = std::make_shared<UI::CheckBox>(Rectangle2D(24, 398, 13, 13));
		pCheckBoxTargetHPPercent->SetFont("Arial", 16, 6, FALSE, FALSE, -1);
		pCheckBoxTargetHPPercent->SetText("Show Target HP in %"); 
		pCheckBoxTargetHPPercent->SetImage(UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox.png"), UI::ImageLoader::LoadImage_("Resources\\UI\\CheckBox\\CheckBox_.png"));
		pCheckBoxTargetHPPercent->SetID(CHECKBOXID_TargetHPPercent);
		pWindowInterface->AddElement(pCheckBoxTargetHPPercent);

		pWindowInterface->Hide();

		GetListMain()->AddWindow(pWindowInterface);
	}
	UI::LPLIST Window::GetListMain()
	{
		return m_pWindowMain->GetElement<UI::List>(LISTID_Main);
	}
	UI::LPWINDOW Window::GetWindow(int iID)
	{
		return GetListMain()->GetWindow(iID);
	}
}