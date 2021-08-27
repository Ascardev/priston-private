#include "StdAfx.h"
#include "Game.h"

CGame::CGame()
{
	m_pcGameTimer = new CGameTime;
	m_pcGameSystem = new CGameSystem;
	m_pcGameEngine = new CGameEngine;
	m_pcGameScreen = new CGameScreen;
	m_pcGameCore = new CGameCore;
	m_pcGameSocket = new CGameSocket;
	m_pcGameUnit = new CGameUnit;
	m_pcGameCharacter = new CGameCharacter;
	m_pcGameMap = new CGameMap;
	m_pcGamePacket = new CGamePacket;
}
CGame::~CGame()
{
	DELET(m_pcGamePacket);
	DELET(m_pcGameMap);
	DELET(m_pcGameCharacter);
	DELET(m_pcGameUnit);
	DELET(m_pcGameSocket);
	DELET(m_pcGameCore);
	DELET(m_pcGameScreen);
	DELET(m_pcGameEngine);
	DELET(m_pcGameSystem);
	DELET(m_pcGameTimer);
}
void CGame::Init()
{
	INIT(m_pcGameMap);
	INIT(m_pcGameTimer);
	INIT(m_pcGameEngine);
	INIT(m_pcGameScreen);
	INIT(m_pcGameCore);
}
void CGame::Shutdown()
{
	SHUTDOWN(m_pcGameCore);
	SHUTDOWN(m_pcGameScreen);
	SHUTDOWN(m_pcGameEngine);
	SHUTDOWN(m_pcGameTimer);
	SHUTDOWN(m_pcGameMap);
}
void CGame::Frame()
{
	m_pcGameScreen->Frame();
	m_pcGameCore->Frame();
}
void CGame::Update(float fTime)
{
	m_pcGameScreen->Update(fTime);
	m_pcGameCore->Update(fTime);
}
void CGame::Render2D()
{
	m_pcGameScreen->Render2D();
	m_pcGameCore->Render2D();
}
void CGame::Render3D()
{
	m_pcGameScreen->Render3D();
	m_pcGameCore->Render3D();
}
BOOL CGame::OnKeyPress(class INPUTS::KeyBoard *pcKeyboard)
{
	if (m_pcGameScreen->OnKeyPress(pcKeyboard))
		return TRUE;
	if (m_pcGameCore->OnKeyPress(pcKeyboard))
		return TRUE;

	return FALSE;
}
BOOL CGame::OnKeyChar(class INPUTS::KeyBoard *pcKeyboard)
{
	if (m_pcGameScreen->OnKeyChar(pcKeyboard))
		return TRUE;
	if (m_pcGameCore->OnKeyChar(pcKeyboard))
		return TRUE;

	return FALSE;
}
void CGame::OnMouseMove(class INPUTS::Mouse *pcMouse)
{
	m_pcGameScreen->OnMouseMove(pcMouse);
	m_pcGameCore->OnMouseMove(pcMouse);
}
BOOL CGame::OnMouseClick(class INPUTS::Mouse *pcMouse)
{
	if (m_pcGameScreen->OnMouseClick(pcMouse))
		return TRUE;
	if (m_pcGameCore->OnMouseClick(pcMouse))
		return TRUE;

	return FALSE;
}
BOOL CGame::OnMouseScroll(class INPUTS::Mouse *pcMouse)
{
	if (m_pcGameScreen->OnMouseScroll(pcMouse))
		return TRUE;
	if (m_pcGameCore->OnMouseScroll(pcMouse))
		return TRUE;

	return FALSE;
}
void CGame::OnResolutionChanged()
{
	m_pcGameScreen->OnResolutionChanged();
	m_pcGameCore->OnResolutionChanged();
}
void CGame::Begin()
{

}
void CGame::End()
{

}