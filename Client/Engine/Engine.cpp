#include "StdAfx.h"
#include "Engine.h"

CEngine::CEngine()
{
	m_pcGraphicsEngine = new DX::GraphicsEngine;
	m_pcKeyboard = new INPUTS::KeyBoard;
	m_pcMouse = new INPUTS::Mouse;
}
CEngine::~CEngine()
{
	DELET(m_pcGraphicsEngine);
	DELET(m_pcKeyboard);
	DELET(m_pcMouse);
}
void CEngine::Init()
{
	m_pcGlow = std::make_shared<EFFECT::Glow>();
	m_pcPostProcess = std::make_shared<EFFECT::PostProcess>();

	m_pcGlow->Init(m_pcGraphicsEngine->GetGraphicDevice());
	m_pcPostProcess->Init(m_pcGraphicsEngine->GetGraphicDevice());
}
void CEngine::Shutdown()
{
	SHUTDOWN(m_pcGlow);
	SHUTDOWN(m_pcPostProcess);
}
void CEngine::Update(float fTime)
{

}