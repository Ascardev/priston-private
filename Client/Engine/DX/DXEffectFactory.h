#pragma once

namespace DX
{
	class GraphicsDevice;

	typedef std::shared_ptr<class EffectFactory> LPEFFECTFACTORY;

	class EffectFactory
	{
	public:
		EffectFactory(GraphicsDevice *pGraphicsDevice);
		virtual ~EffectFactory();

		void OnLostDevice();
		void OnResetDevice();
		LPEFFECT FindFffect(std::string strEffectFile);
		LPEFFECT MakeEffect(std::string strEffectFile);
		void ReloadEffects();
		LPD3DXEFFECT CreateEffectFromFile(std::string strEffectFile);
	private:
		GraphicsDevice *m_pGraphicsDevice;
		std::vector<LPEFFECT> m_vEffect;
	};
}