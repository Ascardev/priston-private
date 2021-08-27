#include "StdAfx.h"
#include "DXSpriteFactory.h"

namespace DX
{
	SpriteFactory::SpriteFactory(GraphicsDevice *pGraphicsDevice) : m_pGraphicsDevice(pGraphicsDevice)
	{
		m_vSprite.reserve(10);
	}
	SpriteFactory::~SpriteFactory()
	{

	}
	void SpriteFactory::OnLostDevice()
	{
		for (auto pSprite : m_vSprite)
		{
			if (pSprite)
				pSprite->OnLostDevice();
		}
	}
	void SpriteFactory::OnResetDevice()
	{
		for (auto pSprite : m_vSprite)
		{
			if (pSprite)
				pSprite->OnResetDevice();
		}
	}
	LPSPRITE SpriteFactory::FindSprite(BOOL bSharable)
	{
		if (bSharable)
		{
			for (auto pSprite : m_vSprite)
			{
				// Also Sharable Sprite
				if (pSprite && pSprite->IsSharable())
				{
					return pSprite;
				}
			}
		}

		return NULL;
	}
	LPSPRITE SpriteFactory::MakeSprite(BOOL bSharable)
	{
		auto pSprite = FindSprite(bSharable);

		if (pSprite)
			return pSprite;

		LPD3DXSPRITE lpSprite;
		//Load Sprite
		if (FAILED(D3DXCreateSprite(m_pGraphicsDevice->Get(),&lpSprite)))
			return NULL;

		//New Sprite
		pSprite = std::make_shared<Sprite>(lpSprite,bSharable);

		m_vSprite.push_back(pSprite);

		//Release Sprite (New Sprite took Possession of a Reference)
		RELEASE(lpSprite);

		return pSprite;
	}
}