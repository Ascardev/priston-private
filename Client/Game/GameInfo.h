#pragma once

enum EHandle : int
{
	EHANDLE_None,
	EHANDLE_Settings,
	EHANDLE_Chat,
	EHANDLE_Party,
	EHANDLE_Inventory,
};
enum EWindow : int
{
	EWINDOW_None,
	EWINDOW_Setting,
	EWINDOW_Chat,
	EWINDOW_Party,
	EWINDOW_MiniMap,
	EWINDOW_CharacterStatus,
	EWINDOW_MessageBox,
	EWINDOW_MessageTitle,
	EWINDOW_WarpGate,
	EWINDOW_Premium,
	EWINDOW_Cursor,
};

class CBaseHandle
{
public:
	CBaseHandle() {}
	CBaseHandle(EHandle eID) : m_eHandleID(eID) {}
	virtual ~CBaseHandle() {}

	virtual void Init() {}
	virtual void Shutdown() {}
	virtual void Render() {}

	virtual void Update(float fTime) {}
	virtual void Tick() {}

	EHandle GetHandleId() { return m_eHandleID; }

private:
	EHandle m_eHandleID = EHANDLE_None;
};
class CBaseWindow
{
public:
	CBaseWindow() {}
	CBaseWindow(EWindow eID) : m_eWindowID(eID) {}
	virtual ~CBaseWindow() {}

	virtual void Init() {}
	virtual void Shutdown() {}
	virtual void Render() {}

	EWindow GetWindowId() { return m_eWindowID; }

	int GetWindowLevel() { return m_iWindowLevel; }
	void SetWindowLevel(int iLevel) { m_iWindowLevel = iLevel; }

	virtual void Show() {}

	virtual BOOL OnMouseClick(class INPUTS::Mouse *pcMouse) { return FALSE; }
	virtual BOOL OnMouseScroll(class INPUTS::Mouse *pcMouse) { return FALSE; }
	virtual void OnMouseMove(class INPUTS::Mouse *pcMouse) {}

	virtual BOOL OnKeyChar(class INPUTS::KeyBoard *pcKeyboard) { return FALSE; }
	virtual BOOL OnKeyPress(class INPUTS::KeyBoard *pcKeyboard) { return FALSE; }

	virtual void OnResolutionChanged() {}
private:
	EWindow m_eWindowID = EWINDOW_None;
	int m_iWindowLevel = 0;
};