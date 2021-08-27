#include "StdAfx.h"
#include "EffectEngine.h"

namespace EFFECT
{
	Engine::Engine()
	{
		m_pcGlow = std::make_shared<EFFECT::Glow>();
		m_pcProcess = std::make_shared<EFFECT::PostProcess>();
	}
	Engine::~Engine()
	{

	}
	void Engine::Init()
	{
		m_pcGlow->Init(GRAPHICENGINE->GetGraphicDevice());
		m_pcProcess->Init(GRAPHICENGINE->GetGraphicDevice());
	}
	void Engine::Shutdown()
	{
		SHUTDOWN(m_pcGlow);
		SHUTDOWN(m_pcProcess);
	}
}