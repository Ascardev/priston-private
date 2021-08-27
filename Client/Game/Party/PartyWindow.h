#pragma once

namespace PARTY
{
	class Window : public CBaseWindow
	{
		enum EWindow1
		{
			WINDOWID_Member1,
			WINDOWID_Member2,
			WINDOWID_Member3,
			WINDOWID_Member4,
			WINDOWID_Member5,
			WINDOWID_Member6,

			LISTID_PartyMembers		= 10,
			LISTID_PartyRaid		= 11,

			TEXTID_Name				= 18,
			TEXTID_CharacterLevel	= 19,

			IMAGEID_Background		= 20,
			IMAGEID_Icon			= 21,
			IMAGEID_LifeBar			= 22,
			IMAGEID_ManaBar			= 23,
			IMAGEID_Class			= 24,
			IMAGEID_IconLeader		= 25,
			IMAGEID_PartyType		= 26,

			DROPDOWNMENUID_Options	= 30, //up to 70

			TOOLTIPID_PartyType,
		};
		enum ENotificationWindow
		{
			TEXTID_CharacterName	= 10,
		};
	public:
		Window();
		Window(EWindow eID);
		virtual ~Window();

		void Init();
		void Shutdown();

		void Render();

		void Update(float fTime);

		void OnMouseMove(class INPUTS::Mouse *pcMouse);
		BOOL OnMouseClick(class INPUTS::Mouse *pcMouse);

		void ShowPartyNotification(char * pszCharacterName, int iType);
		void ShowRaidNotification(char * pszCharacterName);

		void UpdateParty(CPartyData * pcParty);
		void UpdatePartyData(CPartyData * pcParty);

		UI::LPWINDOW GetWindowParty() { return m_pWindowParty; }
		UI::LPWINDOW GetWindowRaid() { return m_pWindowRaid; }

		void LeaveParty();
		void ToggleWindow();
	protected:
		void BuildWindowParty();
		void BuildWindowRaid();
		void ShowMessageBox(int iType, int iIndex = -1);
		void OnSelectMenuParty(int iIndex = -1);

		void OnAcceptPartyButtonClick();
		void OnAcceptRaidButtonClick();
		void OnDelegatePartyButtonClick(int iIndex);
		void OnKickPartyButtonClick(int iIndex);
		void OnLeavePartyButtonClick();
		void OnDisbandPartyButtonClick();
		void OnChangePartyModeButtonClick();
	private:
		UI::LPWINDOW m_pWindowParty;
		UI::LPWINDOW m_pWindowRaid;
		UI::LPIMAGE m_pImagePartyMode[3];
		int m_iPartyRequestType = 0;
	};
}