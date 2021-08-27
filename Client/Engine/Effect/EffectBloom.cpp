#include "StdAfx.h"
#include "EffectBloom.h"

namespace EFFECT
{
	Bloom::Bloom(DX::LPGRAPHICSDEVICE pGraphicsDevice)
	{
		Init(pGraphicsDevice);
	}
	Bloom::~Bloom()
	{

	}
	void Bloom::Init(DX::LPGRAPHICSDEVICE pGraphicsDevice)
	{
		m_pGraphicsDevice = pGraphicsDevice;
		m_pBloomExtractEffect = m_pGraphicsDevice->GetEffectFactory()->MakeEffect("Resources\\Shaders\\BloomExtract.fx");
		m_pGaussianBlurEffect = m_pGraphicsDevice->GetEffectFactory()->MakeEffect("Resources\\Shaders\\BloomCombine.fx");
		m_pBloomCombineEffect = m_pGraphicsDevice->GetEffectFactory()->MakeEffect("Resources\\Shaders\\GaussianBlur.fx");

		m_pOldRendTarget = m_pGraphicsDevice->MakeRenderTarget(0, 0);
		m_pResolveTarget = m_pGraphicsDevice->MakeRenderTarget(1, 0);
		m_pRenderTarget1 = m_pGraphicsDevice->MakeRenderTarget(2, 0);
		m_pRenderTarget2 = m_pGraphicsDevice->MakeRenderTarget(4, 0);
		m_pSprite = m_pGraphicsDevice->GetSpriteFactory()->MakeSprite(TRUE);
	}
	void Bloom::Shutdown()
	{

	}
	void Bloom::Begin()
	{
		if (m_pGraphicsDevice->SetRenderTarget(m_pOldRendTarget))
		{
			m_pGraphicsDevice->Clear(TRUE, FALSE, FALSE);
		}
	}
	void Bloom::End()
	{

		//m_pGraphicsDevice->Clear(FALSE, FALSE, TRUE);

		//m_pGraphicsDevice->UnsetRenderTarget();

		Post();
	}
	void Bloom::Post()
	{
		if (m_pBloomExtractEffect && m_pParam)
		{
			m_pBloomExtractEffect->SetFloat("BloomThreshold", m_pParam->fBloomThreshold);
			PostDraw(m_pResolveTarget, m_pRenderTarget1, m_pBloomExtractEffect);

			SetBlurEffectParam(1.0f / (float)(GRAPHICENGINE->GetBackWidth()), 0.0f);
			PostDraw(m_pRenderTarget1, m_pRenderTarget2, m_pGaussianBlurEffect);

			SetBlurEffectParam(0.0f, 1.0f / (float)(GRAPHICENGINE->GetBackHeight()));
			PostDraw(m_pRenderTarget2, m_pRenderTarget1, m_pGaussianBlurEffect);
		}
	}
	void Bloom::PostDraw(DX::LPRENDERTARGET pRenderTarget1, DX::LPRENDERTARGET pRenderTarget2, DX::LPEFFECT pEffect)
	{
		if (pRenderTarget1  && pRenderTarget2  && pEffect)
		{
			if (pEffect->Begin() > 0)
			{
				if (m_pGraphicsDevice->SetRenderTarget(pRenderTarget1))
				{
					m_pGraphicsDevice->Clear(TRUE, FALSE, FALSE);

					if (m_pSprite->Begin(TRUE))
					{
						if (pEffect->BeginPass(0))
						{
							m_pSprite->Draw(pRenderTarget2);

							pEffect->EndPass();
						}

						m_pSprite->End();
					}

					m_pGraphicsDevice->UnsetRenderTarget();
				}

				pEffect->End();
			}
		}
	}
	void Bloom::Draw()
	{
		if (m_pParam && m_pBloomCombineEffect && m_pResolveTarget && m_pRenderTarget1)
		{
			if (m_pBloomCombineEffect->Begin() >= 0)
			{
				m_pBloomCombineEffect->SetFloat("BloomIntensity", m_pParam->fBloomIntensity);
				m_pBloomCombineEffect->SetFloat("BaseIntensity", m_pParam->fBaseIntensity);
				m_pBloomCombineEffect->SetFloat("BloomSaturation", m_pParam->fBloomSaturation);
				m_pBloomCombineEffect->SetFloat("BaseSaturation", m_pParam->fBaseSaturation);

				m_pBloomCombineEffect->SetTexture("BaseTexture", m_pResolveTarget->GetTexture());

				if (m_pSprite->Begin(TRUE))
				{
					if (m_pBloomCombineEffect->BeginPass(0))
					{
						m_pSprite->Draw(m_pRenderTarget1);

						m_pBloomCombineEffect->EndPass();
					}

					m_pSprite->End();
				}

				m_pBloomCombineEffect->End();
			}
		}
	}
	void Bloom::SetBlurEffectParam(float fx, float fy)
	{
		if (m_pGaussianBlurEffect)
		{
			D3DXHANDLE d3dWeightsParameter, d3dOffsetsParameter;
			int iSampleCount = 15;

			d3dWeightsParameter = m_pGaussianBlurEffect->Get()->GetParameterByName(0, "SampleWeights");
			d3dOffsetsParameter = m_pGaussianBlurEffect->Get()->GetParameterByName(0, "SampleOffsets");

			float fSampleWeights[15];
			float fSampleOffsets[30];

			fSampleWeights[0] = ComputeGaussian(0.0f);
			fSampleOffsets[0] = 0.0f;
			fSampleOffsets[1] = 0.0f;

			float fTotalWeights = fSampleWeights[0];

			for (int i = 0; i < iSampleCount / 2; i++)
			{
				float fWeight = ComputeGaussian((float)(i + 1));

				fSampleWeights[i * 2 + 1] = fWeight;
				fSampleWeights[i * 2 + 2] = fWeight;
				fTotalWeights += fWeight * 2;

				float fOffset = (float)(i * 2 + 1.5f);

				D3DXVECTOR2 delta = D3DXVECTOR2(fx, fy) * fOffset;

				fSampleOffsets[i * 4 + 1] = +delta.x;
				fSampleOffsets[i * 4 + 2] = +delta.y;
				fSampleOffsets[i * 4 + 3] = -delta.x;
				fSampleOffsets[i * 4 + 4] = -delta.y;
			}

			for (int i = 0; i < iSampleCount; i++)
			{
				fSampleWeights[i] /= fTotalWeights;
			}

			m_pGaussianBlurEffect->Get()->SetFloatArray(d3dWeightsParameter, fSampleWeights, iSampleCount);
			m_pGaussianBlurEffect->Get()->SetFloatArray(d3dOffsetsParameter, fSampleOffsets, iSampleCount);
		}
	}
	float Bloom::ComputeGaussian(float f)
	{
		// 高斯模糊计算公式
		float fe = m_pParam->fBlurAmount;

		return (float)((1.0 / sqrt(2 * D3DX_PI * fe)) * exp(-(f * f) / (2 * fe * fe)));
	}
}