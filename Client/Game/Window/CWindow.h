#pragma once

enum EWindow : int
{
	EWINDOW_None,
	EWINDOW_Setting,
	EWINDOW_Chat,
	EWINDOW_CharacterStatus,
	EWINDOW_MessageBox,
	EWINDOW_MessageTitle,
	EWINDOW_WarpGate,
	EWINDOW_ExpUp,
	EWINDOW_ThirdEye,
	EWINDOW_PhoenixFire,
	EWINDOW_PhoenixIce,
	EWINDOW_PhoenixLightning,
	EWINDOW_PhoenixHeal,
	EWINDOW_MPDown,
	EWINDOW_SPDown,
	EWINDOW_HPUp,
	EWINDOW_MPUp,
	EWINDOW_BigHead,
	EWINDOW_Gravity,
	EWINDOW_MagicianHat,
	EWINDOW_WitchHat,
	EWINDOW_SheepHat,
	EWINDOW_GiraffeHat,
	EWINDOW_SoccerHat,
	EWINDOW_XmasHat,
	EWINDOW_TopPvp,
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

	virtual void Update(float fTime) {}
	virtual void Tick() {}

	EWindow GetID() { return m_eWindowID; }

	virtual void Show() {}

	virtual BOOL OnMouseClick(INPUTS::LPMOUSE pcMouse) { return FALSE; }
	virtual BOOL OnMouseScroll(INPUTS::LPMOUSE pcMouse) { return FALSE; }
	virtual void OnMouseMove(INPUTS::LPMOUSE pcMouse) {}

	virtual BOOL OnKeyChar(INPUTS::LPKEYBOARD pcKeyboard) { return FALSE; }
	virtual BOOL OnKeyPress(INPUTS::LPKEYBOARD pcKeyboard) { return FALSE; }
private:
	EWindow m_eWindowID = EWINDOW_None;
};