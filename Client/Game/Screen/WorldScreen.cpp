#include "StdAfx.h"
#include "WorldScreen.h"

CWorldScreen::CWorldScreen() : CScreen()
{
	CGameCore::AddWindow(new CHAT::Window(EWINDOW_Chat));
	CGameCore::AddWindow(new PARTY::Window(EWINDOW_Party));
	CGameCore::AddWindow(new MINIMAP::Window(EWINDOW_MiniMap));
}
CWorldScreen::~CWorldScreen()
{

}
BOOL CWorldScreen::Init()
{
	INIT(CHATBOX);
	INIT(PARTYBOX);
	INIT(MINIMAPBOX);

	UpdateObjectsSettings();

	return GameInit();
}
void CWorldScreen::Shutdown()
{
	GameClose();
}
void CWorldScreen::Render3D()
{
	PlayDraw();
}
void CWorldScreen::Render2D()
{
	
}
EScreen CWorldScreen::Frame()
{
	PlayFrame();
	return SCREEN_World;
}
void CWorldScreen::OnMouseMove(class INPUTS::Mouse *pcMouse)
{

}
BOOL CWorldScreen::OnMouseClick(class INPUTS::Mouse *pcMouse)
{
	return FALSE;
}
void CWorldScreen::UpdateObjectsSettings()
{
	PARTYBOX->GetWindowParty()->SetCanMove(!SETTINGHANDLE->Get().bLockUI);
	PARTYBOX->GetWindowRaid()->SetCanMove(!SETTINGHANDLE->Get().bLockUI);

	CHATBOX->GetWindow()->SetCanMove(!SETTINGHANDLE->Get().bLockUI);
	CHATBOX->ToggleNotice(SETTINGHANDLE->Get().bShowNotice);
}