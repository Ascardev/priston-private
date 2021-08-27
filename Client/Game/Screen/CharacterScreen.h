#pragma once

class HoLogin;

class CCharacterScreen : public CScreen
{
public:
	CCharacterScreen();
	virtual ~CCharacterScreen();

	BOOL Init();
	void Shutdown();

	void Render3D();
	void Render2D();

	EScreen Frame();

	void OnMouseMove(class INPUTS::Mouse *pcMouse);
	BOOL OnMouseClick(class INPUTS::Mouse *pcMouse);
private:
	HoLogin *m_pSelectCharacter = nullptr;
};
