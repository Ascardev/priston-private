#include "StdAfx.h"
#include "DXSprite.h"

namespace DX
{
	Sprite::Sprite(LPD3DXSPRITE lpSprite,BOOL bSharable) : m_lpSprite(lpSprite),m_bSharable(bSharable),m_uUseCount(0)
	{
		ADDREF(m_lpSprite);
		D3DXCreateMatrixStack(0,&m_lpMatrixStack);
	}
	Sprite::Sprite(const Sprite &c) : m_lpSprite(c.m_lpSprite),m_bSharable(c.m_bSharable),m_uUseCount(0)
	{
		ADDREF(m_lpSprite);
		D3DXCreateMatrixStack(0,&m_lpMatrixStack);
	}
	Sprite::~Sprite()
	{
		RELEASE(m_lpMatrixStack);
		RELEASE(m_lpSprite);
	}
	void Sprite::OnLostDevice()
	{
		if (m_lpSprite)
			m_lpSprite->OnLostDevice();
	}
	void Sprite::OnResetDevice()
	{
		if (m_lpSprite)
			m_lpSprite->OnResetDevice();
	}
	void Sprite::Reset()
	{
		m_bStencilEnable = FALSE;
	}

	BOOL Sprite::Begin(BOOL bAlphaBlending)
	{
		BOOL bRet = FALSE;

		if (m_lpSprite)
		{
			bRet = TRUE;

			if (m_uUseCount == 0)
			{
				bRet = SUCCEEDED(m_lpSprite->Begin(bAlphaBlending ? D3DXSPRITE_ALPHABLEND : 0));

				if (bRet)
					m_uUseCount ++;

				// ÐÞ¸Ä
				if (m_bStencilEnable)
					GRAPHICDEVICE->SetRenderState(RENDERSTATE_StencilEnable,TRUE);
			}
			else
				m_uUseCount ++;
		}

		return bRet;
	}
	void Sprite::End()
	{
		if (m_lpSprite)
		{
			if (m_uUseCount > 0)
				m_uUseCount --;

			if (m_uUseCount <= 0)
				m_lpSprite->End();
			else
				m_lpSprite->Flush();
		}
	}
	void Sprite::Draw(LPTEXTURE pTexture,const Color &cColor)
	{
		if (m_lpSprite)
		{
			if (m_uUseCount > 0)
			{
				m_lpSprite->Draw(pTexture->Get(),NULL,NULL,NULL,cColor.Get());
				m_lpSprite->Flush();
			}
		}
	}
	void Sprite::Draw(LPTEXTURE pTexture,const Color &cColor,int iWidth,int iHeight)
	{
		if (m_lpSprite)
		{
			if (m_uUseCount > 0)
			{
				RECT rSourceRect;
				rSourceRect.left	= 0;
				rSourceRect.top		= 0;
				rSourceRect.right	= iWidth;
				rSourceRect.bottom	= iHeight;

				//Scale Vetor
				D3DXVECTOR2 scale(1.0f,1.0f);
				D3DXVECTOR2 trans((float)0,(float)0);
				D3DXVECTOR2 center((float)((iWidth) >> 1),(float)((iHeight) >> 1));
				D3DXMATRIX matrix;
				D3DXMatrixTransformation2D(&matrix,NULL,0,&scale,&center,0.0f,&trans);

				m_lpSprite->SetTransform(&matrix);
				m_lpSprite->Draw(pTexture->Get(),&rSourceRect,NULL,NULL,cColor.Get());
				m_lpSprite->Flush();
			}
		}
	}
	void Sprite::Draw(LPTEXTURE pTexture,const Color &cColor,const RECT &rSourceRect,int iX,int iY)
	{
		if (m_lpSprite)
		{
			if (m_uUseCount > 0)
			{
				m_lpSprite->Draw(pTexture->Get(),&rSourceRect,NULL,&D3DXVECTOR3((float)iX,(float)iY, 0.0f),cColor.Get());
				m_lpSprite->Flush();
			}
		}
	}
	void Sprite::Draw(LPRENDERTARGET pRenderTarget)
	{
		if (m_lpSprite)
		{
			if (m_uUseCount > 0)
			{
				BOOL bPopTransform = FALSE;

				if ((pRenderTarget->GetWidth() != GRAPHICDEVICE->GetRenderTargetWidth()) || (pRenderTarget->GetHeight() != GRAPHICDEVICE->GetRenderTargetHeight()))
				{
					PushScaling2DTransform(Vector2DF((float)GRAPHICDEVICE->GetRenderTargetWidth() / (float)pRenderTarget->GetWidth(), (float)GRAPHICDEVICE->GetRenderTargetHeight() / (float)pRenderTarget->GetHeight()));

					bPopTransform = TRUE;
				}

				//Scale Vetor
				D3DXVECTOR2 scale(1.0f,1.0f);
				D3DXVECTOR2 trans((float)0,(float)0);
				D3DXVECTOR2 center((float)((pRenderTarget->GetWidth()) / 2),(float)((pRenderTarget->GetHeight()) / 2));
				D3DXMATRIX matrix;
				D3DXMatrixTransformation2D(&matrix,NULL,0,&scale,&center,0.0f,&trans);
				m_lpSprite->SetTransform(&matrix);

				m_lpSprite->Draw(pRenderTarget->GetTexture(),NULL,NULL,NULL,D3DCOLOR_XRGB(255,255,255));
				m_lpSprite->Flush();

				if (bPopTransform)
					PopTransform();
			}
		}
	}
	void Sprite::Flush()
	{

	}
	void Sprite::PushScaling2DTransform(const Vector2DF &vScaling, const Vector2DF & vScalingCenter)
	{
		D3DXVECTOR2 vXScaling;
		vXScaling.x = vScaling.fX;
		vXScaling.y = vScaling.fY;

		D3DXVECTOR2 vXScalingCenter;
		vXScalingCenter.x = vScalingCenter.fX;
		vXScalingCenter.y = vScalingCenter.fY;

		D3DXMATRIX mMatrix;
		D3DXMatrixTransformation2D(&mMatrix, &vXScalingCenter,0.0f,&vXScaling,NULL,0.0f,NULL);

		PushTransform(D3DXMatrixToX3DMatrix(mMatrix));
	}

	void Sprite::PushRotation2DTransform(float fRotation, const Vector2DF &vRotationCenter)
	{
		D3DXVECTOR2 vXRotationCenter;
		vXRotationCenter.x = vRotationCenter.fX;
		vXRotationCenter.y = vRotationCenter.fY;

		D3DXMATRIX mMatrix;
		D3DXMatrixTransformation2D(&mMatrix,NULL,0.0f,NULL,&vXRotationCenter,fRotation,NULL);

		PushTransform(D3DXMatrixToX3DMatrix(mMatrix));
	}

	void Sprite::PushTranslation2DTransform(const Vector2DF & vTranslation)
	{
		D3DXVECTOR2 vXTranslation;
		vXTranslation.x = vTranslation.fX;
		vXTranslation.y = vTranslation.fY;

		D3DXMATRIX mMatrix;
		D3DXMatrixTransformation2D(&mMatrix,NULL,0.0f,NULL,NULL,0.0f,&vXTranslation);

		PushTransform(D3DXMatrixToX3DMatrix(mMatrix));
	}

	void Sprite::PushTransform(const Matrix4DF & mMatrix)
	{
		m_lpMatrixStack->Push();
		m_lpMatrixStack->MultMatrix(&X3DMatrixToD3DXMatrix(mMatrix));

		if (m_lpSprite)
			m_lpSprite->SetTransform(m_lpMatrixStack->GetTop());
	}

	void Sprite::PopTransform(int iPopCount)
	{
		for(int i = 0; i < iPopCount; i++)
			m_lpMatrixStack->Pop();

		if (m_lpSprite)
			m_lpSprite->SetTransform(m_lpMatrixStack->GetTop());
	}
}