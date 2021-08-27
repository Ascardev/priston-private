#pragma once

enum EHandle : int
{
	EHANDLE_None,
	EHANDLE_Settings,
	EHANDLE_ItemTime,
	EHANDLE_MapWarp,
	EHANDLE_MapBorder,
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

	EHandle GetID() { return m_eHandleID; }

	//virtual void Show() {}

	//virtual BOOL OnMouseClick(INPUTS::LPMOUSE pcMouse) { return FALSE; }
	//virtual BOOL OnMouseScroll(INPUTS::LPMOUSE pcMouse) { return FALSE; }
	//virtual void OnMouseMove(INPUTS::LPMOUSE pcMouse) {}

	//virtual BOOL OnKeyChar(INPUTS::LPKEYBOARD pcKeyboard) { return FALSE; }
	//virtual BOOL OnKeyPress(INPUTS::LPKEYBOARD pcKeyboard) { return FALSE; }
private:
	EHandle m_eHandleID = EHANDLE_None;
};