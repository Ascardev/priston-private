#include "StdAfx.h"
#include "EffectPostProcess.h"

namespace EFFECT
{
	PostProcess::PostProcess()
	{
		
	}
	PostProcess::~PostProcess()
	{

	}
	void PostProcess::Init(DX::LPGRAPHICSDEVICE pGraphicsDevice)
	{
		m_pGraphicsDevice = pGraphicsDevice;

		m_pEffect = m_pGraphicsDevice->GetEffectFactory()->MakeEffect("Resources\\Shaders\\PostProcess.fx");
		m_pRenderTarget = m_pGraphicsDevice->MakeRenderTarget(0, 0);
		m_pSprite = m_pGraphicsDevice->GetSpriteFactory()->MakeSprite(TRUE);

		m_bPostProcess = TRUE;
	}
	void PostProcess::Shutdown()
	{
		m_pSprite = nullptr;
		m_pRenderTarget = nullptr;
		m_pEffect = nullptr;
	}
	void PostProcess::Begin()
	{
		if (m_bPostProcess)
		{
			if (m_pEffect && m_pRenderTarget && m_pSprite)
			{
				if (m_pGraphicsDevice->SetRenderTarget(m_pRenderTarget))
				{
					m_pGraphicsDevice->Clear(TRUE, FALSE, FALSE);
				}
			}
		}
	}
	void PostProcess::End()
	{
		if (m_bPostProcess)
		{
			if (m_pEffect && m_pRenderTarget && m_pSprite)
			{
				m_pGraphicsDevice->Clear(FALSE, FALSE, TRUE);

				m_pGraphicsDevice->UnsetRenderTarget();

				Draw();
			}
		}
	}
	void PostProcess::Draw()
	{
		if (m_bPostProcess)
		{
			if (m_pEffect && m_pRenderTarget && m_pSprite)
			{
				SetTechnique();

				if (m_pEffect->Begin() >= 0)
				{
					m_pEffect->SetFloat("Time", 1.0f);
					m_pEffect->SetFloat("DeadIntensity", m_fDeadIntensity);

					m_fDeadIntensity += 0.007f;
					if (m_fDeadIntensity >= 1.0f)
						m_fDeadIntensity = 1.0f;

					if (m_pSprite->Begin(TRUE))
					{
						if (m_pEffect->BeginPass(0))
						{
							m_pSprite->Draw(m_pRenderTarget);

							m_pEffect->EndPass();
						}

						m_pSprite->End();
					}

					m_pEffect->End();
				}
			}
		}
	}
	void PostProcess::SetTechnique()
	{
		if (m_pEffect)
		{
			switch (m_eTechnique)
			{
			case POSTPROCESSID_Dead:
				m_pEffect->SetTechnique("Dead");
				break;
			case POSTPROCESSID_Poison:
				m_pEffect->SetTechnique("Poison");
				break;
			}
		}
	}
}