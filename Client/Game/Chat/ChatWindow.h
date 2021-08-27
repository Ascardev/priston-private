#pragma once

#define MAX_CHATTEXTLIST			32

#define MAX_SAVECOMMANDSCHAT		10

#define MAX_EMOTELIST			20

class	Unit;

typedef std::map<std::string, std::string> FriendlyCommands;

namespace CHAT
{
	class Window : public CBaseWindow
	{
		enum EChatBoxTabID
		{
			CHATBOXTABID_All,
			CHATBOXTABID_Clan,
			CHATBOXTABID_Party,
			CHATBOXTABID_Raid,
			CHATBOXTABID_Trade,
			CHATBOXTABID_PM,
		};
		enum EElementsID
		{
			//Windows
			WINDOWID_Main,

			//Lists
			LISTID_ChatAll,
			LISTID_ChatClan,
			LISTID_ChatParty,
			LISTID_ChatRaid,
			LISTID_ChatTrade,
			LISTID_ChatPM,
			LISTID_ChatNotice,

			//Button
			BUTTONID_TabAll,
			BUTTONID_TabClan,
			BUTTONID_TabParty,
			BUTTONID_TabRaid,
			BUTTONID_TabTrade,
			BUTTONID_TabPM,
			BUTTONID_SendMessage,

			//Images
			IMAGEID_ChatBoxBar,

			//Input Field
			INPUTFIELDID_Message,
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
		BOOL OnMouseScroll(class INPUTS::Mouse *pcMouse);

		BOOL OnKeyPress(class INPUTS::KeyBoard *pcKeyboard);
		BOOL OnKeyChar(class INPUTS::KeyBoard *pcKeyboard);

		void OnResolutionChanged();

		BOOL IsInputFieldActive();
		void SetInputFieldText(std::string strText);
		void AddMessage(std::string strMessage, EChatColor eChatColor = CHATCOLOR_Error, std::string strLighText = "");
		void ToggleNotice(BOOL bOpen);

		void HandlePacket(PacketChatBoxMessage * psPacket);

		UI::LPWINDOW GetWindow() { return m_pcWindow; }
	protected:
		void BuidWindow();
		void OnSelectChatBoxTab(int iID);
		void OnEnableChatBox();
		void OnEnterKeyPressed(UIEventArgs eArgs);
		DWORD GetMessageColorFromType(EChatColor eType);
		void SendMessageChat(std::string strMessage);
		std::string GetSaveCommand(BOOL bUP);
		void AddSaveCommand(std::string strMessage);
		BOOL OnEmoteCommand(std::string & strMessage, Unit *pcUnit = NULL);
		void CheckCollideWindow(BOOL bResolutionChanged);
		void AddRecentPlayer(std::string strMessage);
	private:
		UI::LPWINDOW m_pcWindow = nullptr;
		int m_iTabID = 0;

		DWORD m_dwLastMessageTick = 0;
		int m_iTotalMessages = 0;

		FriendlyCommands m_sFriendlyCommands;

		std::vector<std::string> m_vSaveCommand;
		UINT m_uSaveCommandWheel = 0;
	};
}