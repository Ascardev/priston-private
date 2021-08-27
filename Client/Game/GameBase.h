#pragma once

typedef class CBase *LPBASE;

enum EBaseElement : int
{
	EBASEELEMENT_None,
	EBASEELEMENT_Map,
	EBASEELEMENT_Chat,
	EBASEELEMENT_Item,
	EBASEELEMENT_Setting,
	EBASEELEMENT_MessageBox,
	EBASEELEMENT_CharacterStatus,
};

class CBase
{
public:
	CBase() {}
	virtual ~CBase() {}

	virtual void Init() {}
	virtual void Shutdown() {}
	virtual void Render() {}

	virtual BOOL OnMouseClick(INPUTS::LPMOUSE pcMouse) { return FALSE; }
	virtual BOOL OnMouseScroll(INPUTS::LPMOUSE pcMouse) { return FALSE; }
	virtual void OnMouseMove(INPUTS::LPMOUSE pcMouse) {}

	virtual BOOL OnKeyChar(INPUTS::LPKEYBOARD pcKeyboard) { return FALSE; }
	virtual BOOL OnKeyPress(INPUTS::LPKEYBOARD pcKeyboard) { return FALSE; }
};