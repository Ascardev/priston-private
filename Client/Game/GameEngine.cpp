#include "StdAfx.h"
#include "GameEngine.h"

CGameEngine::CGameEngine()
{
	m_pcGraphicsEngine = new DX::GraphicsEngine;
	m_pcInputEngine = new INPUTS::Engine;
	m_pcEffectEngine = new EFFECT::Engine;
}
CGameEngine::~CGameEngine()
{
	DELET(m_pcEffectEngine);
	DELET(m_pcInputEngine);
	DELET(m_pcGraphicsEngine);
}
void CGameEngine::Init()
{
	INIT(m_pcEffectEngine);
}
void CGameEngine::Shutdown()
{
	SHUTDOWN(m_pcEffectEngine);
}
void CGameEngine::Update(float fTime)
{

}