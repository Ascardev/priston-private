#pragma once

namespace MESSAGEBOX
{
	typedef class Model *LPMODEL;

	class Model
	{
	public:
		Model();
		virtual ~Model();

		void Init();
		void Shutdown();
		void Clear();

		void SetTitle(std::string strText);
		void SetDescription(std::string strText);
		void SetAutoClose(int iDuration);
		void AddExtraText(std::string strText, Rectangle2D sBox, BOOL bBold, UI::Color cColor);
		BOOL IsOpen() { return m_pWindow ? m_pWindow->IsOpen() : FALSE; }
		void SetEvent(std::function<void(UIEventArgs const &)> const & f);
		void Show();
		void SetBoxType(int iType);
		BOOL GetType() { return m_bType; }
		void Enjoin(UI::LPELEMENT pElement) { m_pJoinElement = pElement; }
		void Update();
		void Render();
		BOOL GetState() { return m_pWindow ? m_pWindow->IsOpen() : FALSE; }
		BOOL OnKeyPress(INPUTS::LPKEYBOARD pcKeyboard);
		void OnMouseMove(INPUTS::LPMOUSE pcMouse);
		BOOL OnMouseClick(INPUTS::LPMOUSE pcMouse);
		enum
		{
			WINDOWID_Main,
			WINDOWID_RollDice,

			//Box Type
			BOXTYPEID_YesNo,
			BOXTYPEID_OkCancel,
			BOXTYPEID_RollDice,

			BUTTONID_Yes,
			BUTTONID_No,

			TEXTID_Text,
			TEXTID_AutoClose,
			TEXTID_Title,
		};
	protected:
		void BuildWindow();
		void BuildWindowRollDice();
		void DelExtraElement();
		void OnYesButtonClick(UIEventArgs eArgs);
		void OnNoButtonClick(UIEventArgs eArgs);
		void OnRollButtonClick(UIEventArgs eArgs);
		void OnPassButtonClick(UIEventArgs eArgs);
		void OnEvent();
	private:
		int m_iElapsedTime = 0;
		int m_iBoxType = 0;
		BOOL m_bAutoClose = FALSE;
		BOOL m_bType = FALSE;
		DWORD m_dwTickTime = 0;
		UI::LPIMAGE m_pAutoCloseBar[3];
		UI::LPWINDOW m_pWindow = NULL;
		UI::LPWINDOW m_pWindowMain = NULL;
		UI::LPWINDOW m_pWindowRollDice = NULL;
		UI::LPELEMENT m_pJoinElement = NULL;
		std::vector<UI::LPELEMENT> m_vExtraElements;
		std::vector<std::function<void(UIEventArgs const &)>> m_vMsgBox;
	};
}