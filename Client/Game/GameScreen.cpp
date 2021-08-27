#include "StdAfx.h"
#include "GameScreen.h"

CGameScreen::CGameScreen()
{

}
CGameScreen::~CGameScreen()
{

}
void CGameScreen::Init()
{

}
void CGameScreen::Shutdown()
{

}
void CGameScreen::Frame()
{
	if (m_bActiveScreen)
	{
		EScreen iNewActiveScreen = m_pcActiveScreen->Frame();

		if (iNewActiveScreen != m_iActiveScreen)
			ChangeScreen(iNewActiveScreen);
	}
}
void CGameScreen::Update(float fTime)
{
	if (m_bActiveScreen)
		m_pcActiveScreen->Update(fTime);
}
void CGameScreen::Render3D()
{
	if (m_bActiveScreen)
		m_pcActiveScreen->Render3D();
}
void CGameScreen::Render2D()
{
	if (m_bActiveScreen)
		m_pcActiveScreen->Render2D();
}
void CGameScreen::OnMouseMove(class INPUTS::Mouse *pcMouse)
{
	if (m_bActiveScreen)
		m_pcActiveScreen->OnMouseMove(pcMouse);
}
BOOL CGameScreen::OnMouseClick(class INPUTS::Mouse *pcMouse)
{
	if (m_bActiveScreen)
		return m_pcActiveScreen->OnMouseClick(pcMouse);

	return FALSE;
}
BOOL CGameScreen::OnMouseScroll(class INPUTS::Mouse *pcMouse)
{
	if (m_bActiveScreen)
		return m_pcActiveScreen->OnMouseScroll(pcMouse);

	return FALSE;
}
BOOL CGameScreen::OnKeyPress(class INPUTS::KeyBoard *pcKeyboard)
{
	if (m_bActiveScreen)
		return m_pcActiveScreen->OnKeyPress(pcKeyboard);

	return FALSE;
}
BOOL CGameScreen::OnKeyChar(class INPUTS::KeyBoard *pcKeyboard)
{
	if (m_bActiveScreen)
		return m_pcActiveScreen->OnKeyChar(pcKeyboard);

	return FALSE;
}
void CGameScreen::OnResolutionChanged()
{
	if (m_bActiveScreen)
		m_pcActiveScreen->OnResolutionChanged();
}
void CGameScreen::UpdateObjectsSettings()
{
	if (m_bActiveScreen)
		m_pcActiveScreen->UpdateObjectsSettings();
}
void CGameScreen::ChangeScreen(EScreen iNewScreen)
{
	m_bActiveScreen = FALSE;

	m_iActiveScreen = iNewScreen;

	SHUTDOWN(m_pcActiveScreen);
	DELET(m_pcActiveScreen);

	switch (iNewScreen)
	{
	case SCREEN_Login:
		m_pcActiveScreen = new CLoginScreen;
		break;
	case SCREEN_Character:
		m_pcActiveScreen = new CCharacterScreen;
		break;
	case SCREEN_World:
		m_pcActiveScreen = new CWorldScreen;
		break;
	default:
		m_pcActiveScreen = nullptr;
	}

	if (m_pcActiveScreen)
		m_bActiveScreen = m_pcActiveScreen->Init();
}