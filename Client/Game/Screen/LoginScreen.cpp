#include "StdAfx.h"
#include "LoginScreen.h"

CLoginScreen::CLoginScreen() : CScreen()
{
	m_pLogin = new HoOpening;
}
CLoginScreen::~CLoginScreen()
{
	DELET(m_pLogin);
}
BOOL CLoginScreen::Init()
{
	return m_pLogin->Init() == 0 ? FALSE : TRUE;
}
void CLoginScreen::Shutdown()
{
	m_pLogin->Close();
}
void CLoginScreen::Render3D()
{
	m_pLogin->Draw();
}
void CLoginScreen::Render2D()
{

}
EScreen CLoginScreen::Frame()
{
	GAMESOCKET->PingConnections();

	return m_pLogin->Main() == 1 ? SCREEN_Login : SCREEN_Character;
}
void CLoginScreen::OnMouseMove(class INPUTS::Mouse *pcMouse)
{

}
BOOL CLoginScreen::OnMouseClick(class INPUTS::Mouse *pcMouse)
{
	return FALSE;
}
void CLoginScreen::OnResolutionChanged()
{
	m_pLogin->SetSize();
}
BOOL CLoginScreen::BuildStage()
{
	return FALSE;
}
BOOL CLoginScreen::BuildWindow()
{
	return FALSE;
}