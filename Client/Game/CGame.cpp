#include "StdAfx.h"
#include "CGame.h"

CGame::CGame()
{
	m_pcGameTimer = new CGameTime;
	m_pcEngine = new CEngine;
	m_pcGameCore = new CGameCore;
}
CGame::~CGame()
{
	DELET(m_pcGameTimer);
	DELET(m_pcEngine);
	DELET(m_pcGameCore);
}
void CGame::Init()
{
	INIT(m_pcGameTimer);
	INIT(m_pcEngine);
	INIT(m_pcGameCore);
}
void CGame::Shutdown()
{
	SHUTDOWN(m_pcGameTimer);
	SHUTDOWN(m_pcEngine);
	SHUTDOWN(m_pcGameCore);
}
void CGame::Frame()
{
	m_pcGameCore->Frame();
}
void CGame::Update(float fTime)
{
	m_pcGameCore->Update(fTime);
}
void CGame::Render2D()
{
	m_pcGameCore->Render2D();
}
void CGame::Render3D()
{
	m_pcGameCore->Render3D();
}
BOOL CGame::OnKeyPress(INPUTS::LPKEYBOARD pcKeyboard)
{
	return m_pcGameCore->OnKeyPress(pcKeyboard);
}
BOOL CGame::OnKeyChar(INPUTS::LPKEYBOARD pcKeyboard)
{
	return m_pcGameCore->OnKeyChar(pcKeyboard);
}
void CGame::OnMouseMove(INPUTS::LPMOUSE pcMouse)
{
	m_pcGameCore->OnMouseMove(pcMouse);
}
BOOL CGame::OnMouseClick(INPUTS::LPMOUSE pcMouse)
{
	return m_pcGameCore->OnMouseClick(pcMouse);
}
BOOL CGame::OnMouseScroll(INPUTS::LPMOUSE pcMouse)
{
	return m_pcGameCore->OnMouseScroll(pcMouse);
}
void CGame::Begin()
{

}
void CGame::End()
{

}