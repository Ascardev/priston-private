#pragma once

namespace SETTING
{
	class Window : public CBaseWindow
	{
	private:
		enum
		{
			//Windows
			WINDOWID_Main,

			//Child Windows
			WINDOWID_Video,
			WINDOWID_Audio,
			WINDOWID_General,
			WINDOWID_Interface,

			WINDOWID_Screen,
			WINDOWID_Graphics,
			WINDOWID_Camera,

			LISTID_Main,

			//Buttons
			BUTTONID_Video,
			BUTTONID_Audio,
			BUTTONID_General,
			BUTTONID_Interface,

			//Groups
			GROUPID_Menu,

			GROUPID_Display,
			GROUPID_Ratio,
			GROUPID_Resolutions4_3,
			GROUPID_Resolutions16_9,
			GROUPID_TextureQuality,
			GROUPID_AntiAliasing,
			GROUPID_VSync,
			GROUPID_BitDepth,
			GROUPID_Effects,
			GROUPID_CameraSight,
			GROUPID_InvertedCamera,
			GROUPID_DamageDebug,
			GROUPID_HPBar,
			GROUPID_FPS,
			GROUPID_Ping,
			GROUPID_KillInfo,
			GROUPID_Macro,

			//Checkbox
			CHECKBOXID_Fullscreen,
			CHECKBOXID_Windowed,
			CHECKBOXID_StartMaximized,
			CHECKBOXID_AutoAdjust,
			CHECKBOXID_Ratio4_3,
			CHECKBOXID_Ratio16_9,

			CHECKBOXID_1024x768,
			CHECKBOXID_1280x960,
			CHECKBOXID_1400x1050,

			CHECKBOXID_1280x720,
			CHECKBOXID_1366x768,
			CHECKBOXID_1600x900,
			CHECKBOXID_1920x1080,

			CHECKBOXID_TextureHigh,
			CHECKBOXID_TextureLow,

			CHECKBOXID_AntiAliasingON,
			CHECKBOXID_AntiAliasingOFF,

			CHECKBOXID_VSyncON,
			CHECKBOXID_VSyncOFF,

			CHECKBOXID_32BPP,
			CHECKBOXID_16BPP,

			CHECKBOXID_EffectsON,
			CHECKBOXID_EffectsOFF,

			CHECKBOXID_Full,
			CHECKBOXID_Far,
			CHECKBOXID_Short,

			CHECKBOXID_CameraON,
			CHECKBOXID_CameraOFF,

			CHECKBOXID_NoMusic,
			CHECKBOXID_NoEffects,

			CHECKBOXID_DisableParty,
			CHECKBOXID_DisableTrade,
			CHECKBOXID_NoWhisper,
			CHECKBOXID_NoTrade,

			CHECKBOXID_DamageDebugON,
			CHECKBOXID_DamageDebugOFF,

			CHECKBOXID_HPBarON,
			CHECKBOXID_HPBarOFF,

			CHECKBOXID_FPSON,
			CHECKBOXID_FPSOFF,

			CHECKBOXID_PingON,
			CHECKBOXID_PingOFF,

			CHECKBOXID_KillInfoON,
			CHECKBOXID_KillInfoOFF,

			CHECKBOXID_LockUI,
			CHECKBOXID_ShowPartyMembers,
			CHECKBOXID_ShowRaidMembers,
			CHECKBOXID_ShowClanMembers,
			CHECKBOXID_ShowEnemies,
			CHECKBOXID_ShowNPCs,
			CHECKBOXID_ShowNextBossTimer,
			CHECKBOXID_AlwaysActive,
			CHECKBOXID_ShowNotice,
			CHECKBOXID_TargetDistance,
			CHECKBOXID_TargetHPValue,
			CHECKBOXID_TargetHPPercent,

			CHECKBOXID_LootFilterEnable,
			CHECKBOXID_LootHPPotion,
			CHECKBOXID_LootMPPotion,
			CHECKBOXID_LootSPPotion,
			CHECKBOXID_LootGold,
			CHECKBOXID_LootAmulets,
			CHECKBOXID_LootRings,
			CHECKBOXID_LootSheltoms,
			CHECKBOXID_LootForceOrbs,
			CHECKBOXID_LootPremiums,
			CHECKBOXID_LootMonsterCrystals,
			CHECKBOXID_LootDefenseItems,
			CHECKBOXID_LootOffenseItems,
			CHECKBOXID_LootEverything,
			CHECKBOXID_LootSpecNS,
			CHECKBOXID_LootSpecFS,
			CHECKBOXID_LootSpecMS,
			CHECKBOXID_LootSpecAS,
			CHECKBOXID_LootSpecPS,
			CHECKBOXID_LootSpecATA,
			CHECKBOXID_LootSpecKS,
			CHECKBOXID_LootSpecMGS,
			CHECKBOXID_LootSpecPRS,
			CHECKBOXID_LootSpecASS,
			CHECKBOXID_LootSpecSHA,

			SCROLLID_BGMusic,
			SCROLLID_EffectSound,

			InputFieldID_Macro1,
			InputFieldID_Macro2,
			InputFieldID_Macro3,
			InputFieldID_Macro4,
			InputFieldID_Macro5,
			InputFieldID_Macro6,
			InputFieldID_Macro7,
			InputFieldID_Macro8,
			InputFieldID_Macro9,
			InputFieldID_Macro10,
		};
	public:
		Window();
		Window(EWindow eID);
		virtual ~Window();

		void Init();
		void Shutdown();

		void Show();

		void Render();

		BOOL IsOpen() { return m_pWindowMain->IsOpen(); }

		BOOL OnKeyPress(class INPUTS::KeyBoard *pcKeyboard);
		BOOL OnKeyChar(class INPUTS::KeyBoard *pcKeyboard);
		void OnMouseMove(class INPUTS::Mouse *pcMouse);
		BOOL OnMouseClick(class INPUTS::Mouse *pcMouse);
		BOOL OnMouseScroll(class INPUTS::Mouse *pcMouse);

		void OnResolutionChanged();
	protected:
		void BuildWindow();
		void BuildVideo();
		void BuildAudio();
		void BuildGeneral();
		void BuildInterface();
		UI::LPLIST GetListMain();
		UI::LPWINDOW GetWindow(int iID);
		void OnResetButtonClick(UIEventArgs eArgs);
		void OnSaveButtonClick(UIEventArgs eArgs);
		void OnCloseButtonClick(UIEventArgs eArgs);
		void OnMenuButtonClick(int iID, UIEventArgs eArgs);
		void OnCheckBoxRatioClick(int iID, UIEventArgs eArgs);

		void SetResolutionSettings();
		int GetResolutionCheckBox();
		void SetResolutionCheckBox();
		void Load();
		void Save();
	private:
		UI::LPWINDOW m_pWindowMain = NULL;
	};
}