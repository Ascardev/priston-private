#pragma once

enum ELoginState
{
	LOGINSTATE_None,
	LOGINSTATE_Opening,
	LOGINSTATE_Connecting,
	LOGINSTATE_ServerSelect,
	LOGINSTATE_Finish,
};

namespace SCREEN
{
	class Login : public Screen
	{
	public:
		Login();
		~Login();

		void Init();
		void Shutdown();

		void Render2D();
		void Render3D();

		EScreen Frame();

		void OnMouseMove(INPUTS::LPMOUSE pcMouse);
		BOOL OnMouseClick(INPUTS::LPMOUSE pcMOuse);
	private:
		ELoginState m_iLoginState = LOGINSTATE_None;
	};
}