#pragma once

class CGameScreen
{
public:
	CGameScreen();
	virtual ~CGameScreen();

	void Init();
	void Shutdown();

	void Frame();
	void Update(float fTime);

	void Render3D();
	void Render2D();

	void OnMouseMove(class INPUTS::Mouse *pcMouse);
	BOOL OnMouseClick(class INPUTS::Mouse *pcMouse);
	BOOL OnMouseScroll(class INPUTS::Mouse *pcMouse);
	BOOL OnKeyPress(class INPUTS::KeyBoard *pcKeyboard);
	BOOL OnKeyChar(class INPUTS::KeyBoard *pcKeyboard);
	void OnResolutionChanged();

	void ChangeScreen(EScreen iNewScreen);

	void UpdateObjectsSettings();

	EScreen GetActiveScreenType() { return m_iActiveScreen; }
private:
	BOOL m_bActiveScreen = FALSE;
	EScreen	m_iActiveScreen = SCREEN_None;
	CScreen *m_pcActiveScreen = nullptr;
};
