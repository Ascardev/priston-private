#pragma once

namespace EFFECT
{
	typedef std::shared_ptr<class Glow> LPGLOW;

	class Glow
	{
	public:
		Glow();
		virtual ~Glow();

		void Init(DX::LPGRAPHICSDEVICE pGraphicsDevice);
		void Shutdown();

		BOOL Begin(D3DCOLOR d3dColor, BOOL bSmallPass);
		void End(BOOL bSmallPass);

		void Draw();

		BOOL IsDisabled() { return m_bDisabled; }
		void SetDisabled(BOOL bValue) { m_bDisabled = bValue; }

		DX::LPEFFECT GetEffect() { return m_pEffect; }

		float *GetOffset() { return m_faOffset; }
		float *GetWeight() { return m_faWeight; }

	protected:
		void GaussianFunc();
		float Gaussian(float x);
	private:
		DX::LPGRAPHICSDEVICE m_pGraphicsDevice;
		DX::LPEFFECT m_pEffect;
		DX::LPDEPTHSTENCILBUFFER m_pDepthStencilBuffer;
		DX::LPRENDERTARGET m_pRenderTarget1;
		DX::LPRENDERTARGET m_pRenderTarget2;

		DX::LPTEXTURE m_pTexture;
		DX::LPSPRITE m_pSprite;

		float m_faOffset[15];
		float m_faWeight[15];

		DX::Color m_cColor;

		BOOL m_bGotSomething = FALSE;
		BOOL m_bFirstTime = TRUE;
		BOOL m_bDisabled = FALSE;

		DX::ViewPort m_vOldViewport;
	};
}
