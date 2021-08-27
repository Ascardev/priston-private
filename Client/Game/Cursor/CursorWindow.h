#pragma once

enum ECursorIcon
{
	ECURSORICON_None,
	ECURSORICON_Default,
	ECURSORICON_Sell,
	ECURSORICON_Buy,
	ECURSORICON_Repair,
	ECURSORICON_RepairAll,
	ECURSORICON_Attack,
	ECURSORICON_GetItem1,
	ECURSORICON_GetItem2,
	ECURSORICON_Talk,
};

namespace CURSOR
{
	class Window : public CBaseWindow
	{
	public:
		Window();
		Window(EWindow eID);
		virtual ~Window();

		void Init();
		void Shutdown();
		void Render();
		void SetMouseCursor(ECursorIcon eID) { m_eID = eID; }
		ECursorIcon GetMouseCurosr() { return m_eID; }
		BOOL IsOpen() { return m_bShow; }
		void Show() { m_bShow = TRUE; }
		void Hide() { m_bShow = FALSE; }
	protected:
		UI::LPIMAGEBOX Load(ECursorIcon iID, const char* pszFile);
		void BuildWindow();
	private:
		UI::LPWINDOW m_pWindowMain = NULL;
		ECursorIcon m_eID = ECURSORICON_Default;
		BOOL m_bShow = TRUE;
	};
}