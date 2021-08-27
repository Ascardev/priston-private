#pragma once

class CHUDController
{
	enum EWindow1
	{
		WINDOWID_Main,
		BUTTONID_LockItem,
		IMAGEID_LockItemView,
	};
	enum ETargetWindow1
	{
		IMAGEID_LifeBar,
		IMAGEID_Type,
		IMAGEID_TargetInfo,
		IMAGEID_ClanIcon,

		TEXTID_Name,
		TEXTID_TargetInfo,
		TEXTID_ClanInfo,
		TEXTID_Life,
		TEXTID_Level,
		TEXTID_LifePercent,
		TEXTID_Range,

		BUTTONID_More,

		DROPDOWNMENU_More,

		TOOLTIP_TargetType,

		WINDOWID_TargetInfo,
		WINDOWID_CharacterInfo,
	};
	enum ETargetType
	{
		TARGETTYPE_Demon,
		TARGETTYPE_Mechanic,
		TARGETTYPE_Mutant,
		TARGETTYPE_Normal,
		TARGETTYPE_Undead,
		TARGETTYPE_NPC,
		TARGETTYPE_Player,
	};
	enum ERollDiceRanking
	{
		LISTID_RankingLeft,
		LISTID_RankingRight,

		WINDOWID_Player1,
		WINDOWID_Player2,
		WINDOWID_Player3,
		WINDOWID_Player4,
		WINDOWID_Player5,

		TEXTID_CharacterNick1,
		TEXTID_CharacterNick2,
		TEXTID_CharacterNick3,
		TEXTID_CharacterNick4,
		TEXTID_CharacterNick5,

		TEXTID_Number1,
		TEXTID_Number2,
		TEXTID_Number3,
		TEXTID_Number4,
		TEXTID_Number5,
	};
public:
	CHUDController();
	virtual ~CHUDController();

	BOOL OnMouseClick(class INPUTS::Mouse * pcMouse);
	void OnMouseMove(class INPUTS::Mouse * pcMouse);
	BOOL OnKeyPress(class INPUTS::KeyBoard * pcKeyboard);
	BOOL OnMouseScroll(class INPUTS::Mouse * pcMouse);
	BOOL OnKeyChar(class INPUTS::KeyBoard * pcKeyboard);

	void OnResolutionChanged();
	void RenderFriendStatus();

	void Init();
	void Update(float fTime);

	void Render();

	BOOL IsLockItems();

	void RenderHPCrystalTower(int iX, int iY, int iMin, int iMax);
	void UpdateObjectsSettings();

	void OnAcceptTradeRequest(int iTargetID);

	BOOL IsWindowOldHUDOpen();

	int GetTargetID() { return m_iTargetID; }

	BOOL UpdateTargetInfo(Unit * pcUnit);

	void SetRenderTarget(BOOL b);
	Unit * GetTargetUnitData() { return m_pcLastUnitDataTarget; }

	UI::LPIMAGE GetTargetTypeImage(int iIndex) { return m_pcaImageTargetType[iIndex]; }

	//Dice Roll	Ranking
	void OpenDiceRollRanking() { if (m_pWindowRollDiceRanking) m_pWindowRollDiceRanking->Show(); }
	void CloseDiceRollRanking() { if (m_pWindowRollDiceRanking)m_pWindowRollDiceRanking->Hide(); }

	void HandlePacket(PacketRollDiceRanking * psPacket);
	void ClearRollDiceRanking(BOOL bResetVetor = FALSE);
	void UpdateRollDice() { m_dwLastUpdateRollDice = GetTickCount(); }

	//Getters
	UI::LPWINDOW GetTargetWindow() { return m_pWindowTarget; }
protected:
	void OnSelectTargetMenu();

	void BuildTargetWindow1();

	//Display
	void BuildDisplayWindow1();
	int GetShortcutSkill(int iShortcut);

	//Dice Roll Ranking
	void BuildDiceRollRankingWindow1();
private:
	DX::LPFONT m_pFont;

	UI::LPWINDOW m_pWindowInventory = NULL;
	UI::LPWINDOW m_pWindowTarget = NULL;
	UI::LPWINDOW m_pWindowDisplay = NULL;
	UI::LPWINDOW m_pWindowRollDiceRanking = NULL;

	BOOL m_baFriendStatus[101];
	BOOL m_bRenderTarget;
	int m_iTargetID;
	Unit * m_pcLastUnitDataTarget = NULL;
	BOOL m_bLoadClan16 = FALSE;
	BOOL m_bLoadClan32 = FALSE;

	//CChatBox								  * pcChatBox = NULL;
	//CPartyHandler							  * pcPartyHandler = NULL;
	//CInventory								  * pcInventory = NULL;
	//CMiniMapHandler							  * pcMiniMapHandler = NULL;

	UI::LPTOOLTIP m_pcTooltipWorldTime;

	UI::LPTOOLTIP m_pcTooltipBars[3];

	UI::LPIMAGE m_pcaImageCrystalTowerHPBar[2];
	UI::LPIMAGE	m_pcaImageSkillsIcon[2][20];

	//Target
	UI::LPIMAGE	m_pcaImageTargetType[7];

	//Dice Roll Ranking
	std::vector<RollDiceRankingUser> m_vRollDiceRanking;
	DWORD m_dwLastUpdateRollDice = -1;
};
