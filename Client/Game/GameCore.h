#pragma once

#define SETTINGHANDLE		(GAMECOREHANDLE->GetSettingsHandle())
#define SETTINGWINDOW		(GAMECOREHANDLE->GetSettingsWindow())
#define MESSAGEBOX			(GAMECOREHANDLE->GetMessageBox())
#define CTITLEBOX			(GAMECOREHANDLE->GetMessageTitle())
#define CURSORHANDLE		(GAMECOREHANDLE->GetCursorWindow())
#define CHATGAMEHANDLE		(GAMECOREHANDLE->GetChatHandle())
#define CHATBOX				(GAMECOREHANDLE->GetChatWindow())
#define ITEMTIMEBOX			(GAMECOREHANDLE->GetItemTimeWindow())
#define INVENTROYHANDLE		(GAMECOREHANDLE->GetInventroyHandle())
#define PARTYHANDLE			(GAMECOREHANDLE->GetPartyHandle())
#define PARTYBOX			(GAMECOREHANDLE->GetPartyWindow())
#define MINIMAPBOX			(GAMECOREHANDLE->GetMiniMapWindow())
#define ITEMHANDLE			(GAMECOREHANDLE->GetItemHandle())


class CGameCore
{
public:
	CGameCore();
	virtual ~CGameCore();

	void Init();
	void Shutdown();

	void Frame();
	void Update(float fTime);

	void Render2D();
	void Render3D();

	BOOL IsInit() { return m_bInit; }

	BOOL OnMouseClick(class INPUTS::Mouse *pcMouse);
	BOOL OnMouseScroll(class INPUTS::Mouse *pcMouse);
	void OnMouseMove(class INPUTS::Mouse *pcMouse);

	BOOL OnKeyChar(class INPUTS::KeyBoard *pcKeyboard);
	BOOL OnKeyPress(class INPUTS::KeyBoard *pcKeyboard);

	void OnResolutionChanged();

	SETTING::Handle *GetSettingsHandle() { return static_cast<SETTING::Handle *>(GetHandle(EHANDLE_Settings)); }
	SETTING::Window *GetSettingsWindow() { return static_cast<SETTING::Window *>(GetWindow(EWINDOW_Setting)); }
	MESSAGE::BOX::Window *GetMessageBox() { return static_cast<MESSAGE::BOX::Window *>(GetWindow(EWINDOW_MessageBox)); }
	MESSAGE::TITLE::Window *GetMessageTitle() { return static_cast<MESSAGE::TITLE::Window *>(GetWindow(EWINDOW_MessageTitle)); }
	CHAT::Window *GetChatWindow() { return static_cast<CHAT::Window *>(GetWindow(EWINDOW_Chat)); }
	CHAT::Handle *GetChatHandle() { return static_cast<CHAT::Handle *>(GetHandle(EHANDLE_Chat)); }

	PARTY::Window *GetPartyWindow() { return static_cast<PARTY::Window *>(GetWindow(EWINDOW_Party)); }
	PARTY::Handle *GetPartyHandle() { return static_cast<PARTY::Handle *>(GetHandle(EHANDLE_Party)); }

	MINIMAP::Window * GetMiniMapWindow() { return static_cast<MINIMAP::Window *>(GetWindow(EWINDOW_MiniMap)); }

	INVENTROY::Handle *GetInventroyHandle() { return static_cast<INVENTROY::Handle *>(GetHandle(EHANDLE_Inventory)); }
	ITEMTIME::Window *GetItemTimeWindow() { return static_cast<ITEMTIME::Window *>(GetWindow(EWINDOW_Premium)); }
	CURSOR::Window *GetCursorWindow() { return static_cast<CURSOR::Window *>(GetWindow(EWINDOW_Cursor)); }

	CItemHandle * GetItemHandle() { return m_pcItemHandle; }

	static void SetFocus(CBaseWindow *pWindow);
	static CBaseHandle *GetHandle(EHandle eID);
	static CBaseWindow *GetWindow(EWindow eID);
	static CBaseWindow *AddWindow(CBaseWindow *pWindow);
	static CBaseHandle *AddHandle(CBaseHandle *pHandle);
	static void DelWindow(CBaseWindow *pWindow);
	static void DelHandle(CBaseHandle *pHandle);
private:
	BOOL m_bInit = FALSE;

	CItemHandle * m_pcItemHandle = nullptr;
};