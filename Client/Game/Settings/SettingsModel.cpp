#include "StdAfx.h"
#include "SettingsModel.h"

namespace SETTING
{
	Model::Model(std::string strFileName) : m_strFileName(strFileName)
	{

	}
	Model::~Model()
	{
		
	}
	void Model::Read()
	{
		CFILE::Ini cReader(m_strFileName);

		if (m_bFirstRead)
			CopyMemory(&m_sOldSetings, &m_sSetings, sizeof(sSettings));

		//Screen

		m_sSetings.bWindowed = cReader.ReadBool("Screen", "Windowed");
		m_sSetings.bAutoAdjust = cReader.ReadBool("Screen", "AutoAdjust");
		m_sSetings.uWidth = cReader.ReadInt("Screen", "Width");
		m_sSetings.uHeight = cReader.ReadInt("Screen", "Height");
		m_sSetings.bMaximized = cReader.ReadBool("Screen", "Maximized");

		if (STRINGCOMPARE(cReader.ReadString("Screen", "Ratio").c_str(), "4:3"))
			m_sSetings.bWidescreen = FALSE;
		else
			m_sSetings.bWidescreen = TRUE;

		//Graphics

		m_sSetings.dwBitDepth = cReader.ReadInt("Graphics", "BitDepth");
		m_sSetings.bHightTextureQuality = cReader.ReadBool("Graphics", "HighTextureQuality");
		m_sSetings.bVSync = cReader.ReadBool("Graphics", "VSync");
		m_sSetings.bAntiAliasing = cReader.ReadBool("Graphics", "AntiAliasing");
		m_sSetings.bNoEffects = cReader.ReadBool("Graphics", "NoEffects");

		//Camera

		m_sSetings.iCameraRange = cReader.ReadInt("Camera", "CameraRange");
		m_sSetings.bInvertedCamera = cReader.ReadBool("Camera", "InvertedCamera");

		//Audio

		m_sSetings.bNoSoundEffect = cReader.ReadBool("Audio", "NoEffects");
		m_sSetings.bNoMusic = cReader.ReadBool("Audio", "NoMusic");
		m_sSetings.iEffectVolume = cReader.ReadInt("Audio", "MusicVolume");
		m_sSetings.iMusicVolume = cReader.ReadInt("Audio", "EffectVolume");

		//Game
		m_sSetings.bNoWisper = cReader.ReadBool("Game", "NoWhisper");
		m_sSetings.bNoTradeChat = cReader.ReadBool("Game", "NoTradeChat");
		m_sSetings.bNoPartyRequest = cReader.ReadBool("Game", "NoPartyRequest");
		m_sSetings.bNoTradeRequest = cReader.ReadBool("Game", "NoTradeRequest");

		STRINGCOPY(m_sSetings.szLastAccount, cReader.ReadString("Game", "LastAccount").c_str());

		//Copy Macros

		char szMacro[16] = { 0 };

		for (int i = 0; i < 10; i++)
		{
			STRINGFORMAT(szMacro, "Macro%d", i + 1);
			STRINGCOPY(m_sSetings.szMacro[i], cReader.ReadString("Game", szMacro).c_str());
		}

		m_sSetings.bEnableLootFilter = cReader.ReadBool("Game", "EnableLootFilter");
		m_sSetings.iLootFilterFlags = cReader.ReadInt("Game", "LootFilterFlags");
		m_sSetings.iLootFilterSpecFlags = cReader.ReadInt("Game", "LootFilterSpecFlags");

		//Personlization
		m_sSetings.bDebugDamage = cReader.ReadBool("Personalization", "DebugDamage");
		m_sSetings.bHPBarOnHead = cReader.ReadBool("Personalization", "HPBarOnHead");
		m_sSetings.bFPS = cReader.ReadBool("Personalization", "FPS");
		m_sSetings.bPing = cReader.ReadBool("Personalization", "Ping");
		m_sSetings.bDebugKill = cReader.ReadBool("Personalization", "KillInfo");

		m_sSetings.bLockUI = cReader.ReadBool("UI", "Lock");
		m_sSetings.bShowPartyMembers = cReader.ReadBool("UI", "ShowPartyMembers");
		m_sSetings.bShowRaidMembers = cReader.ReadBool("UI", "ShowRaidMembers");
		m_sSetings.bShowClanMembers = cReader.ReadBool("UI", "ShowClanMembers");
		m_sSetings.bShowEnemies = cReader.ReadBool("UI", "ShowEnemies");
		m_sSetings.bShowNPCs = cReader.ReadBool("UI", "ShowNPCS");
		m_sSetings.bMinimapAlwaysActive = cReader.ReadBool("UI", "MinimapAlwaysActive");
		m_sSetings.bShowNextBossTimer = cReader.ReadBool("UI", "ShowNextBossTimer");
		m_sSetings.bShowNotice = cReader.ReadBool("UI", "ShowNotice");
		m_sSetings.bTargetDistance = cReader.ReadBool("UI", "TargetDistance");
		m_sSetings.bTargetHPValue = cReader.ReadBool("UI", "TargetHPValue");
		m_sSetings.bTargetHPPercent = cReader.ReadBool("UI", "TargetHPPercent");

		if (!m_bFirstRead)
		{
			CopyMemory(&m_sOldSetings, &m_sSetings, sizeof(sSettings));
			m_bFirstRead = TRUE;
		}
	}
	void Model::Write()
	{
		CFILE::Ini cWrite(m_strFileName);

		//Screen
		cWrite.WriteBool("Screen", "Windowed", m_sSetings.bWindowed);
		cWrite.WriteBool("Screen", "AutoAdjust", m_sSetings.bAutoAdjust);
		cWrite.WriteInt("Screen", "Width", m_sSetings.uWidth);
		cWrite.WriteInt("Screen", "Height", m_sSetings.uHeight);
		cWrite.WriteBool("Screen", "Maximized", m_sSetings.bMaximized);

		if (m_sSetings.bWidescreen)
			cWrite.WriteString("Screen", "Ratio", "16:9");
		else
			cWrite.WriteString("Screen", "Ratio", "4:3");

		//Graphics

		cWrite.WriteInt("Graphics", "BitDepth", m_sSetings.dwBitDepth);
		cWrite.WriteBool("Graphics", "HighTextureQuality", m_sSetings.bHightTextureQuality);
		cWrite.WriteBool("Graphics", "VSync", m_sSetings.bVSync);
		cWrite.WriteBool("Graphics", "AntiAliasing", m_sSetings.bVSync);
		cWrite.WriteBool("Graphics", "NoEffects", m_sSetings.bNoEffects);

		//Camera

		cWrite.WriteInt("Camera", "CameraRange", m_sSetings.iCameraRange);
		cWrite.WriteOnOff("Camera", "InvertedCamera", m_sSetings.bInvertedCamera);

		//Audio

		cWrite.WriteBool("Audio", "NoEffects", m_sSetings.bNoSoundEffect);
		cWrite.WriteBool("Audio", "NoMusic", m_sSetings.bNoMusic);
		cWrite.WriteInt("Audio", "MusicVolume", m_sSetings.iMusicVolume);
		cWrite.WriteInt("Audio", "EffectVolume", m_sSetings.iEffectVolume);

		//Game
		cWrite.WriteBool("Game", "NoWhisper", m_sSetings.bNoWisper);
		cWrite.WriteBool("Game", "NoTradeChat", m_sSetings.bNoTradeChat);
		cWrite.WriteBool("Game", "NoPartyRequest", m_sSetings.bNoPartyRequest);
		cWrite.WriteBool("Game", "NoTradeRequest", m_sSetings.bNoTradeRequest);

		cWrite.WriteString("Game", "LastAccount", m_sSetings.szLastAccount);

		char szMacro[16] = { 0 };

		for (int i = 0; i < 10; i++)
		{
			STRINGFORMAT(szMacro, "Macro%d", i + 1);
			cWrite.WriteString("Game", szMacro, m_sSetings.szMacro[i]);
		}

		//Loot
		cWrite.WriteBool("Game", "EnableLootFilter", m_sSetings.bEnableLootFilter);
		cWrite.WriteInt("Game", "LootFilterFlags", m_sSetings.iLootFilterFlags);
		cWrite.WriteInt("Game", "LootFilterSpecFlags", m_sSetings.iLootFilterSpecFlags);

		//Personlization
		cWrite.WriteBool("Personalization", "DebugDamage", m_sSetings.bDebugDamage);
		cWrite.WriteBool("Personalization", "HPBarOnHead", m_sSetings.bHPBarOnHead);
		cWrite.WriteBool("Personalization", "FPS", m_sSetings.bFPS);
		cWrite.WriteBool("Personalization", "Ping", m_sSetings.bPing);
		cWrite.WriteBool("Personalization", "KillInfo", m_sSetings.bDebugKill);

		cWrite.WriteBool("UI", "Lock", m_sSetings.bLockUI);
		cWrite.WriteBool("UI", "ShowPartyMembers", m_sSetings.bShowPartyMembers);
		cWrite.WriteBool("UI", "ShowRaidMembers", m_sSetings.bShowRaidMembers);
		cWrite.WriteBool("UI", "ShowClanMembers", m_sSetings.bShowClanMembers);
		cWrite.WriteBool("UI", "ShowEnemies", m_sSetings.bShowEnemies);
		cWrite.WriteBool("UI", "ShowNPCS", m_sSetings.bShowNPCs);
		cWrite.WriteBool("UI", "MinimapAlwaysActive", m_sSetings.bMinimapAlwaysActive);
		cWrite.WriteBool("UI", "ShowNextBossTimer", m_sSetings.bShowNextBossTimer);
		cWrite.WriteBool("UI", "ShowNotice", m_sSetings.bShowNotice);
		cWrite.WriteBool("UI", "TargetDistance", m_sSetings.bTargetDistance);
		cWrite.WriteBool("UI", "TargetHPValue", m_sSetings.bTargetHPValue);
		cWrite.WriteBool("UI", "TargetHPPercent", m_sSetings.bTargetHPPercent);
	}
	BOOL Model::CanViewLoot(ELootFilter e)
	{
		return m_sSetings.iLootFilterFlags & e ? TRUE : FALSE;
	}
	void Model::ResetViewLoot()
	{
		m_sSetings.iLootFilterFlags = LOOTFILTER_None;
	}
	void Model::RemoveViewLoot(ELootFilter e)
	{
		if (CanViewLoot(e))
			m_sSetings.iLootFilterFlags -= e;
	}
	void Model::AddViewLoot(ELootFilter e)
	{
		if (!CanViewLoot(e))
			m_sSetings.iLootFilterFlags |= e;
	}
	void Model::SetViewLoot(ELootFilter e, BOOL b)
	{
		b ? AddViewLoot(e) : RemoveViewLoot(e);
	}
	BOOL Model::CanViewLootSpec(ELootFilterSpec e)
	{
		return m_sSetings.iLootFilterSpecFlags & e ? TRUE : FALSE;
	}
	void Model::RemoveViewLootSpec(ELootFilterSpec e)
	{
		if (CanViewLootSpec(e))
			m_sSetings.iLootFilterSpecFlags -= e;
	}
	void Model::AddViewLootSpec(ELootFilterSpec e)
	{
		if (!CanViewLootSpec(e))
			m_sSetings.iLootFilterSpecFlags |= e;
	}
	void Model::SetViewLootSpec(ELootFilterSpec e, BOOL b)
	{
		b ? AddViewLootSpec(e) : RemoveViewLootSpec(e);
	}
	BOOL Model::HaveViewLootSpec()
	{
		return m_sSetings.iLootFilterSpecFlags > 0 ? TRUE : FALSE;
	}
	void Model::OnCheckWindowState(HWND hWnd)
	{
		//Get Window State
		WINDOWPLACEMENT wc;

		UINT uWidth = GetSystemMetrics(SM_CXSCREEN);
		UINT uHeight = GetSystemMetrics(SM_CYSCREEN);

		GetWindowPlacement(hWnd, &wc);

		// If window is maximizing adjust it
		SETTING::LPMODEL p = SETTINGSHANDLE->GetModel();

		BOOL bAdjust = p->Get().bAutoAdjust;

		if ((wc.showCmd == SW_MAXIMIZE) && !m_bMaximizedWindow && p->Get().bWindowed)
		{
			if (bAdjust)
			{
				RECT rc;

				rc.left = rc.top = 0;
				rc.right = p->GetOld().uWidth;
				rc.bottom = p->GetOld().uHeight;

				GetWindowRect(hWnd, &rc);

				UINT uWindowSytle = GetWindowLongA(hWnd, GWL_STYLE);

				//Adjust Window
				AdjustWindowRect(&rc, uWindowSytle, FALSE);

				uHeight = rc.bottom + rc.top;

				GRAPHICENGINE->Reset(p->Get().bWindowed, uWidth, uHeight);
				GRAPHICENGINE->ResolutionChange(FALSE, uWidth, uHeight);

				m_bMaximizedWindow = TRUE;
			}
		}
		else if ((wc.showCmd != SW_MAXIMIZE) && (wc.showCmd != SW_MINIMIZE) && m_bMaximizedWindow && p->Get().bWindowed)
		{
			GRAPHICENGINE->Reset(p->Get().bWindowed, p->Get().uWidth, p->Get().uHeight);
			GRAPHICENGINE->ResolutionChange(FALSE, p->Get().uWidth, p->Get().uHeight);

			m_bMaximizedWindow = FALSE;
		}
	}
}