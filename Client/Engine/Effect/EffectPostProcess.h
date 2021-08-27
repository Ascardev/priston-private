#pragma once

enum EPostEffects
{
	POSTPROCESSID_None,
	POSTPROCESSID_Dead,
	POSTPROCESSID_Poison,
	POSTPROCESSID_ControlColor,
};

namespace EFFECT
{
	typedef std::shared_ptr<class PostProcess> LPPOSTPROCESS;

	class PostProcess
	{
	public:
		PostProcess();
		virtual ~PostProcess();

		void Init(DX::LPGRAPHICSDEVICE pGraphicsDevice);
		void Shutdown();

		void Begin();
		void End();

		void Draw();

		void SetTechnique(EPostEffects eTechnique) { m_eTechnique = eTechnique; }

		void Enable() { m_bPostProcess = TRUE; m_fDeadIntensity = 0.1f; }
		void Disable() { m_bPostProcess = FALSE; m_fDeadIntensity = 0.1f; }

	protected:
		void SetTechnique();
	private:
		float m_fDeadIntensity = 0.1f;
		BOOL m_bPostProcess = FALSE;
		EPostEffects m_eTechnique = POSTPROCESSID_None;
		DX::LPGRAPHICSDEVICE m_pGraphicsDevice = NULL;
		DX::LPEFFECT m_pEffect = NULL;
		DX::LPRENDERTARGET m_pRenderTarget = NULL;
		DX::LPSPRITE m_pSprite = NULL;
	};
}