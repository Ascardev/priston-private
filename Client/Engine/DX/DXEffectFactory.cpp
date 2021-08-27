#include "StdAfx.h"
#include "DXEffectFactory.h"

namespace DX
{
	EffectFactory::EffectFactory(GraphicsDevice *pGraphicsDevice) : m_pGraphicsDevice(pGraphicsDevice)
	{
		m_vEffect.reserve(25);
	}
	EffectFactory::~EffectFactory()
	{

	}
	void EffectFactory::OnLostDevice()
	{
		for (auto pEffect : m_vEffect)
		{
			if (pEffect)
				pEffect->OnLostDevice();
		}
	}
	void EffectFactory::OnResetDevice()
	{
		for (auto pEffect : m_vEffect)
		{
			if (pEffect)
				pEffect->OnResetDevice();
		}
	}
	LPEFFECT EffectFactory::FindFffect(std::string strEffectFile)
	{
		for (auto pEffect : m_vEffect)
		{
			if (pEffect && pEffect->GetFile().compare(strEffectFile) == 0)
				return pEffect;
		}

		return NULL;
	}
	LPEFFECT EffectFactory::MakeEffect(std::string strEffectFile)
	{
		auto pEffect = FindFffect(strEffectFile);

		if (!pEffect)
		{
			LPD3DXEFFECT lpEffect = CreateEffectFromFile(strEffectFile);

			pEffect = std::make_shared<Effect>(lpEffect, strEffectFile);

			m_vEffect.push_back(pEffect);

			RELEASE(lpEffect);
		}

		return pEffect;
	}
	void EffectFactory::ReloadEffects()
	{
		for (auto pEffect : m_vEffect)
		{
			if (pEffect)
			{
				LPD3DXEFFECT lpEffect = CreateEffectFromFile(pEffect->GetFile());

				pEffect->Renew(lpEffect);

				RELEASE(lpEffect);
			}
		}
	}
	LPD3DXEFFECT EffectFactory::CreateEffectFromFile(std::string strEffectFile)
	{
		DWORD dwFlags = 0;
		HRESULT hr;
		LPD3DXEFFECT lpEffect;
		LPD3DXBUFFER lpErrorBuffer = NULL;

		if(FAILED(hr = D3DXCreateEffectFromFile(m_pGraphicsDevice->Get(),strEffectFile.c_str(),NULL,NULL,dwFlags,NULL,&lpEffect,&lpErrorBuffer)))
		{
			if (lpErrorBuffer)
				RELEASE(lpErrorBuffer);
		}

		if (lpErrorBuffer)
			RELEASE(lpErrorBuffer);

		return lpEffect;
	}
}