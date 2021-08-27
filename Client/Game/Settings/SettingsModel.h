#pragma once

enum ELootFilter : unsigned int
{
	LOOTFILTER_None = 0x0,
	LOOTFILTER_HPPotion = 0x0002,
	LOOTFILTER_MPPotion = 0x0004,
	LOOTFILTER_SPPotion = 0x0008,
	LOOTFILTER_Gold = 0x0010,
	LOOTFILTER_Amulets = 0x0020,
	LOOTFILTER_Rings = 0x0040,
	LOOTFILTER_Sheltoms = 0x0080,
	LOOTFILTER_ForceOrbs = 0x0100,
	LOOTFILTER_Premiums = 0x0200,
	LOOTFILTER_MonsterCrystals = 0x0400,
	LOOTFILTER_DefenseItems = 0x0800,
	LOOTFILTER_OffenseItems = 0x1000,
	LOOTFILTER_Everything = 0x2000,
};

enum ELootFilterSpec : unsigned int
{
	LOOTFILTERSPEC_None = 0x0,
	LOOTFILTERSPEC_NS = 0x0002,
	LOOTFILTERSPEC_FS = 0x0004,
	LOOTFILTERSPEC_MS = 0x0008,
	LOOTFILTERSPEC_AS = 0x0010,
	LOOTFILTERSPEC_PS = 0x0020,
	LOOTFILTERSPEC_ATA = 0x0040,
	LOOTFILTERSPEC_KS = 0x0080,
	LOOTFILTERSPEC_MGS = 0x0100,
	LOOTFILTERSPEC_PRS = 0x0200,
	LOOTFILTERSPEC_ASS = 0x0400,
	LOOTFILTERSPEC_SHA = 0x0800,
};

namespace SETTING
{
	typedef class Model *LPMODEL;

	class Model
	{
	private:
		struct sSettings
		{
			BOOL bWindowed = TRUE;
			BOOL bWidescreen = TRUE;;
			BOOL bAutoAdjust = TRUE;;
			UINT uWidth = 1024;
			UINT uHeight = 768;
			BOOL bMaximized = FALSE;

			DWORD dwBitDepth = 32;
			BOOL bVSync = TRUE;
			BOOL bHightTextureQuality = TRUE;
			BOOL bAntiAliasing = TRUE;
			BOOL bNoEffects = FALSE;

			int iCameraRange = 0;
			BOOL bInvertedCamera = FALSE;

			BOOL bNoSoundEffect = FALSE;
			BOOL bNoMusic = FALSE;
			int iMusicVolume = 100;
			int iEffectVolume = 100;

			BOOL bNoTradeChat = FALSE;
			BOOL bNoWisper = FALSE;
			BOOL bNoTradeRequest = FALSE;
			BOOL bNoPartyRequest = FALSE;

			BOOL bDebugDamage = TRUE;
			BOOL bHPBarOnHead = TRUE;
			BOOL bFPS = FALSE;
			BOOL bPing = FALSE;
			BOOL bDebugKill = TRUE;

			BOOL bEnableLootFilter = TRUE;
			UINT iLootFilterFlags;
			UINT iLootFilterSpecFlags;

			BOOL bLockUI = FALSE;
			BOOL bShowPartyMembers = TRUE;
			BOOL bShowClanMembers = TRUE;
			BOOL bShowEnemies = TRUE;
			BOOL bShowNPCs = TRUE;
			BOOL bMinimapAlwaysActive = TRUE;
			BOOL bShowRaidMembers = TRUE;
			BOOL bShowNextBossTimer = TRUE;
			BOOL bShowNotice = FALSE;
			BOOL bTargetDistance = TRUE;
			BOOL bTargetHPValue = TRUE;
			BOOL bTargetHPPercent = TRUE;

			char szServerAddr[16];

			char szMacro[10][100];
			char szLastAccount[32];
		};
	public:
		Model(std::string strFileName);
		virtual ~Model();

		void Read();
		void Write();

		sSettings &Get() { return m_sSetings; }
		sSettings &GetOld() { return m_sOldSetings; }

		BOOL CanViewLoot(ELootFilter e);
		void ResetViewLoot();
		void RemoveViewLoot(ELootFilter e);
		void AddViewLoot(ELootFilter e);
		void SetViewLoot(ELootFilter e, BOOL b);

		BOOL CanViewLootSpec(ELootFilterSpec e);
		void RemoveViewLootSpec(ELootFilterSpec e);
		void AddViewLootSpec(ELootFilterSpec e);
		void SetViewLootSpec(ELootFilterSpec e, BOOL b);
		BOOL HaveViewLootSpec();

		void OnCheckWindowState(HWND hWnd);
	private:
		sSettings m_sSetings;
		sSettings m_sOldSetings;

		BOOL m_bFirstRead = FALSE;
		BOOL m_bMaximizedWindow = FALSE;

		std::string m_strFileName = "";
	};
}
