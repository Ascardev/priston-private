#pragma once

namespace EFFECT
{
	class Engine
	{
	public:
		Engine();
		virtual ~Engine();
		void Init();
		void Shutdown();
		EFFECT::LPGLOW GetEffectGlow() { return m_pcGlow; }
		EFFECT::LPPOSTPROCESS GetEffectProcess() { return m_pcProcess; }
	private:
		LPGLOW m_pcGlow = nullptr;
		LPPOSTPROCESS m_pcProcess = nullptr;
	};
}