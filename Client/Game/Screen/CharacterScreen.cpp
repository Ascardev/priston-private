#include "StdAfx.h"
#include "CharacterScreen.h"

CCharacterScreen::CCharacterScreen() : CScreen()
{
	m_pSelectCharacter = new HoLogin;
}
CCharacterScreen::~CCharacterScreen()
{
	DELET(m_pSelectCharacter);
}
BOOL CCharacterScreen::Init()
{
	return m_pSelectCharacter->Init() == 0 ? FALSE : TRUE;
}
void CCharacterScreen::Shutdown()
{
	m_pSelectCharacter->Close();
}
void CCharacterScreen::Render3D()
{
	m_pSelectCharacter->Draw();
}
void CCharacterScreen::Render2D()
{

}
EScreen CCharacterScreen::Frame()
{
	GAMESOCKET->PingConnections();

	int i = m_pSelectCharacter->Main();

	if (i == 3)
		return SCREEN_World;
	else if (i == 2)
		return SCREEN_Login;

	return SCREEN_Character;
}
void CCharacterScreen::OnMouseMove(class INPUTS::Mouse *pcMouse)
{

}
BOOL CCharacterScreen::OnMouseClick(class INPUTS::Mouse *pcMouse)
{
	return FALSE;
}