#pragma once

enum EScreen
{
	SCREEN_None = 0,
	SCREEN_Login = 1,
	SCREEN_Character = 2,
	SCREEN_World = 3,
};

class CScreen
{
public:
	CScreen() {}
	virtual ~CScreen() {}

	virtual BOOL Init() = 0;
	virtual void Shutdown() = 0;

	virtual void Render2D() = 0;
	virtual void Render3D() = 0;

	virtual EScreen Frame() = 0;
	virtual void Update(float fTime) {}
	virtual void OnMouseMove(class INPUTS::Mouse *pcMouse) {}
	virtual BOOL OnMouseClick(class INPUTS::Mouse *pcMouse) { return FALSE; }
	virtual BOOL OnMouseScroll(class INPUTS::Mouse *pcMouse) { return FALSE; }
	virtual BOOL OnKeyPress(class INPUTS::KeyBoard *pcKeyboard) { return FALSE; }
	virtual BOOL OnKeyChar(class INPUTS::KeyBoard *pcKeyboard) { return FALSE; }
	virtual void OnResolutionChanged() {}
	virtual void UpdateObjectsSettings() {}
};