#pragma once

namespace EFFECT
{
	struct BloomParam
	{
		const char *pszName; //Bloom 特效名称
		float fBloomThreshold; //饱和度
		float fBlurAmount; //模糊程度
		float fBloomIntensity; // 模糊剧烈度
		float fBaseIntensity; // 原始剧烈度
		float fBloomSaturation; //模糊饱和度
		float fBaseSaturation; // 原始饱和度

		BloomParam() {}
		BloomParam(const char *pName, float fbloomThreshold, float fblurAmount, float fbloomIntensity, float fbaseIntensity, float fbloomSaturation, float fbaseSaturation) : pszName(pName),
		fBloomThreshold(fbloomThreshold),fBlurAmount(fblurAmount),fBloomIntensity(fbloomIntensity),fBaseIntensity(fbaseIntensity),fBloomSaturation(fBloomSaturation),fBaseSaturation(fbaseSaturation){}
	};

	typedef std::shared_ptr<class Bloom> LPBLOOM;

	class Bloom
	{
	public:
		Bloom(DX::LPGRAPHICSDEVICE pGraphicsDevice);
		virtual ~Bloom();

		void Init(DX::LPGRAPHICSDEVICE pGraphicsDevice);
		void Shutdown();

		void Begin();
		void End();

		void Draw();

		void SetParam(BloomParam *pParam) { m_pParam = pParam; }
		BloomParam *GetParam() { return m_pParam; }
	protected:
		void Post();
		void PostDraw(DX::LPRENDERTARGET pRenderTarget1, DX::LPRENDERTARGET pRenderTarget2, DX::LPEFFECT pEffect);
		void SetBlurEffectParam(float fx, float fy);
		float ComputeGaussian(float f);
	private:
		BloomParam *m_pParam = NULL;
		DX::LPEFFECT m_pBloomExtractEffect = NULL;
		DX::LPEFFECT m_pGaussianBlurEffect = NULL;
		DX::LPEFFECT m_pBloomCombineEffect = NULL;
		DX::LPRENDERTARGET m_pOldRendTarget = NULL;
		DX::LPRENDERTARGET m_pResolveTarget = NULL;
		DX::LPRENDERTARGET m_pRenderTarget1 = NULL;
		DX::LPRENDERTARGET m_pRenderTarget2 = NULL;
		DX::LPSPRITE m_pSprite = NULL;
		DX::LPGRAPHICSDEVICE m_pGraphicsDevice = NULL;
	};
}
