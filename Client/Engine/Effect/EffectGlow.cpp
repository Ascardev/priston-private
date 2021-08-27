#include "StdAfx.h"
#include "EffectGlow.h"

namespace EFFECT
{
	Glow::Glow()
	{

	}
	Glow::~Glow()
	{

	}
	void Glow::Init(DX::LPGRAPHICSDEVICE pGraphicsDevice)
	{
		m_pGraphicsDevice = pGraphicsDevice;

		m_pEffect = m_pGraphicsDevice->GetEffectFactory()->MakeEffect("Resources\\Shaders\\SelectGlow.fx");
		m_pDepthStencilBuffer = m_pGraphicsDevice->MakeDepthStencilBuffer(0, 0);
		m_pRenderTarget1 = m_pGraphicsDevice->MakeRenderTarget(0, 0);
		m_pRenderTarget2 = m_pGraphicsDevice->MakeRenderTarget(1, 0);

		m_pTexture = m_pGraphicsDevice->GetTextureFactory()->MakeBlankTexutre();
		m_pSprite = m_pGraphicsDevice->GetSpriteFactory()->MakeSprite(TRUE);

		GaussianFunc();

		m_bGotSomething = FALSE;
		m_bFirstTime = TRUE;
	}
	void Glow::Shutdown()
	{
		m_pSprite = nullptr;
		m_pTexture = nullptr;

		m_pRenderTarget1 = nullptr;
		m_pRenderTarget2 = nullptr;

		m_pDepthStencilBuffer = nullptr;

		m_pEffect = nullptr;
	}
	BOOL Glow::Begin(D3DCOLOR d3dColor, BOOL bSmallPass)
	{
		//Select Glow Disabled;
		if (m_bDisabled)
			return FALSE;
		//Is Everything There
		if (!m_pEffect || !m_pDepthStencilBuffer || !m_pRenderTarget1 || !m_pRenderTarget2 || !m_pTexture || !m_pSprite)
			return FALSE;

		if (bSmallPass)
		{
			m_vOldViewport = m_pGraphicsDevice->GetViewport();

			if (!m_pGraphicsDevice->SetViewport(DX::ViewPort(0, 0, m_pRenderTarget1->GetWidth() - 1, m_pRenderTarget1->GetHeight() - 1, 0.0f, 1.0f)))
				return FALSE;

			if (!m_pGraphicsDevice->SetRenderTarget(m_pRenderTarget1))
			{
				m_pGraphicsDevice->SetViewport(m_vOldViewport);
				return FALSE;
			}

			if (!m_pGraphicsDevice->SetDepthStencilBuffer(m_pDepthStencilBuffer))
			{
				m_pGraphicsDevice->UnsetRenderTarget();
				m_pGraphicsDevice->SetViewport(m_vOldViewport);
				return FALSE;
			}
			if (m_bFirstTime)
			{
				m_pGraphicsDevice->Clear(FALSE, FALSE, TRUE);
				m_bFirstTime = FALSE;
			}
		}

		m_cColor = DX::Color(d3dColor);
		m_cColor.SetAlpha(255);

		m_pGraphicsDevice->Get()->SetRenderState(D3DRS_STENCILENABLE, TRUE);
		m_pGraphicsDevice->Get()->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_INCRSAT);
		m_pGraphicsDevice->Get()->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_INCRSAT);
		m_pGraphicsDevice->Get()->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCRSAT);
		m_pGraphicsDevice->Get()->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
		m_pGraphicsDevice->Get()->SetRenderState(D3DRS_STENCILWRITEMASK, 0xFFFFFFFF);

		m_pGraphicsDevice->Get()->SetRenderState(D3DRS_COLORWRITEENABLE, 0);
		m_pGraphicsDevice->Get()->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		m_pGraphicsDevice->Get()->SetRenderState(D3DRS_ZENABLE, FALSE);

		return TRUE;
	}

	void Glow::End(BOOL bSmallPass)
	{
		m_pGraphicsDevice->Get()->SetRenderState(D3DRS_ZENABLE, TRUE);
		m_pGraphicsDevice->Get()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		m_pGraphicsDevice->Get()->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_ALPHA | D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_RED);

		m_pGraphicsDevice->Get()->SetRenderState(D3DRS_STENCILENABLE, FALSE);

		if (bSmallPass)
		{
			m_pGraphicsDevice->UnsetDepthStencilBuffer();
			m_pGraphicsDevice->UnsetRenderTarget();
			m_pGraphicsDevice->SetViewport(m_vOldViewport);
		}

		m_bGotSomething = TRUE;
	}
	void Glow::Draw()
	{
		if (m_bGotSomething)
		{
			m_bGotSomething = FALSE;

			//Is everything there
			if (m_pEffect && m_pDepthStencilBuffer && m_pRenderTarget1 && m_pRenderTarget2 && m_pTexture && m_pSprite)
			{
				BOOL bRenderOK = FALSE;

				//Resize Viewport to our Render Target
				m_vOldViewport = m_pGraphicsDevice->GetViewport();

				if (m_pGraphicsDevice->SetViewport(DX::ViewPort(0, 0, m_pRenderTarget1->GetWidth(), m_pRenderTarget1->GetHeight(), 0.0f, 1.0f)))
				{
					//Set small Depth Stencil Buffer
					if (m_pGraphicsDevice->SetDepthStencilBuffer(m_pDepthStencilBuffer))
					{
						//Compute Texel Size
						float faTexelSize[2] = { 0.0f,0.0f };

						if (m_pRenderTarget1)
						{
							faTexelSize[0] = 1.0f / (float)m_pRenderTarget1->GetWidth();
							faTexelSize[1] = 1.0f / (float)m_pRenderTarget1->GetHeight();
						}

						//Draw Blank Texture to Render Target 1 and only color the parts marked in the low resolution Stencil Buffer
						if (m_pGraphicsDevice->SetRenderTarget(m_pRenderTarget1))
						{
							//Clear Render Target
							m_pGraphicsDevice->Clear(TRUE, FALSE, FALSE);

							if (m_pSprite->Begin(TRUE))
							{
								m_pGraphicsDevice->Get()->SetRenderState(D3DRS_STENCILENABLE, TRUE);
								m_pGraphicsDevice->Get()->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
								m_pGraphicsDevice->Get()->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
								m_pGraphicsDevice->Get()->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
								m_pGraphicsDevice->Get()->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_LESS);
								m_pGraphicsDevice->Get()->SetRenderState(D3DRS_STENCILREF, 0);
								m_pGraphicsDevice->Get()->SetRenderState(D3DRS_STENCILMASK, 0xFFFFFFFF);
								m_pGraphicsDevice->Get()->SetRenderState(D3DRS_STENCILWRITEMASK, 0xFFFFFFFF);

								m_pSprite->Draw(m_pTexture, m_cColor, m_pRenderTarget1->GetWidth(), m_pRenderTarget1->GetHeight());

								m_pGraphicsDevice->Get()->SetRenderState(D3DRS_STENCILENABLE, FALSE);

								m_pSprite->End();
							}

							// Clear low resoluteion Stencil Buffer
							m_pGraphicsDevice->Clear(FALSE, FALSE, TRUE);

							m_pGraphicsDevice->UnsetRenderTarget();
						}

						//Effect;

						//Glow Technique
						m_pEffect->SetTechnique("Glow");

						//Begin Effect
						if (m_pEffect->Begin() >= 0)
						{
							m_pEffect->SetFloatArray("texelSize", faTexelSize, _countof(faTexelSize));
							m_pEffect->SetFloatArray("offsets", m_faOffset, _countof(m_faOffset));
							m_pEffect->SetFloatArray("weights", m_faWeight, _countof(m_faWeight));

							//Blur Horizontally the first Render Target (silhouette becomes horizontally blurred)
							if (m_pGraphicsDevice->SetRenderTarget(m_pRenderTarget2))
							{
								//Clear Render Target
								m_pGraphicsDevice->Clear(TRUE, FALSE, FALSE);

								if (m_pSprite->Begin(TRUE))
								{
									if (m_pEffect->BeginPass(0))
									{
										m_pSprite->Draw(m_pRenderTarget1);

										m_pEffect->EndPass();
									}

									m_pSprite->End();
								}

								m_pGraphicsDevice->UnsetRenderTarget();
							}

							//Blur Vertically the second Render Target (horizontally blurred silhouette becomes fully blurred)
							if (m_pGraphicsDevice->SetRenderTarget(m_pRenderTarget1))
							{
								//Clear Render Target
								m_pGraphicsDevice->Clear(TRUE, FALSE, FALSE);

								if (m_pSprite->Begin(TRUE))
								{
									if (m_pEffect->BeginPass(1))
									{
										m_pSprite->Draw(m_pRenderTarget2);

										m_pEffect->EndPass();

										//Mark Done
										bRenderOK = TRUE;
									}

									m_pSprite->End();
								}

								m_pGraphicsDevice->UnsetRenderTarget();
							}

							m_pEffect->End();
						}

						//Unset small Depth Stencil Buffer
						m_pGraphicsDevice->UnsetDepthStencilBuffer();
					}

					//Use normal Viewport
					m_pGraphicsDevice->SetViewport(m_vOldViewport);
				}

				//Render Ok
				if (bRenderOK)
				{
					//Stretch Render the blurred Render Target to the Back Buffer, mask out the silhouette that resides in the high resolution Stencil Buffer of the target
					if (m_pSprite->Begin(TRUE))
					{
						m_pGraphicsDevice->Get()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

						m_pGraphicsDevice->Get()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
						m_pGraphicsDevice->Get()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

						m_pGraphicsDevice->Get()->SetRenderState(D3DRS_STENCILENABLE, TRUE);
						m_pGraphicsDevice->Get()->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
						m_pGraphicsDevice->Get()->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
						m_pGraphicsDevice->Get()->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
						m_pGraphicsDevice->Get()->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_GREATEREQUAL);
						m_pGraphicsDevice->Get()->SetRenderState(D3DRS_STENCILREF, 0);
						m_pGraphicsDevice->Get()->SetRenderState(D3DRS_STENCILMASK, 0xFFFFFFFF);
						m_pGraphicsDevice->Get()->SetRenderState(D3DRS_STENCILWRITEMASK, 0xFFFFFFFF);

						m_pSprite->Draw(m_pRenderTarget1);

						m_pGraphicsDevice->Get()->SetRenderState(D3DRS_STENCILENABLE, FALSE);

						m_pSprite->End();
					}
				}

				m_bFirstTime = TRUE;
			}
		}
	}
	void Glow::GaussianFunc()
	{
		m_faWeight[0] = Gaussian(0.0f);
		m_faOffset[0] = 0.0f;

		float totalWeight = m_faWeight[0];

		for (int i = 0; i < _countof(m_faWeight) / 2; i++)
		{
			float weight = Gaussian((float)(i + 1));

			m_faWeight[(i * 2) + 1] = weight;
			m_faWeight[(i * 2) + 2] = weight;
			totalWeight += weight * 2.0f;

			float offset = ((float)i * 2.0f) + 1.5f;

			m_faOffset[(i * 2) + 1] = +offset;
			m_faOffset[(i * 2) + 2] = -offset;
		}

		for (int i = 0; i < _countof(m_faWeight); i++)
			m_faWeight[i] /= totalWeight;
	}

	float Glow::Gaussian(float x)
	{
		float blur2 = 4;
		float invSq = 1.0f / (float)sqrt(D3DX_PI * blur2);
		float exp2 = (float)exp(-(x * x) / blur2);
		return invSq * exp2;
	}
}