#pragma once

enum ELoginState
{
	LOGINSTATE_None,
	LOGINSTATE_Opening,
	LOGINSTATE_Connecting,
	LOGINSTATE_ServerSelect,
	LOGINSTATE_Finish,
};
enum ELoginFade
{
	LOGINFADE_In,
	LOGINFADE_Out,
};

class smSTAGE3D;
class smPAT3D;
class smOBJ3D;
class HoOpening;

class CLoginScreen : public CScreen
{
public:
	CLoginScreen();
	virtual ~CLoginScreen();

	BOOL Init();
	void Shutdown();

	void Render3D();
	void Render2D();

	EScreen Frame();

	void OnMouseMove(class INPUTS::Mouse *pcMouse);
	BOOL OnMouseClick(class INPUTS::Mouse *pcMouse);
	void OnResolutionChanged();
protected:
	BOOL BuildStage();
	BOOL BuildWindow();
private:
	HoOpening *m_pLogin = nullptr;
};
