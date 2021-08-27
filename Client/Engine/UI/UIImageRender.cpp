#include "StdAfx.h"
#include "UIImageRender.h"

namespace UI
{
	DX::LPEFFECT ImageRender::m_pEffect;

	LPD3DXSPRITE ImageRender::m_pSpriteUIImage;

	ImageRender::ImageRender()
	{

	}
	ImageRender::~ImageRender()
	{

	}
	DX::LPEFFECT ImageRender::GetEffect()
	{
		return ImageRender::m_pEffect;
	}
	void ImageRender::SetEffect(DX::LPEFFECT p)
	{
		ImageRender::m_pEffect = p;
	}
	void ImageRender::Render(LPDIRECT3DTEXTURE9 lpTexture,int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY,DWORD dwColor,float fScaleX,float fScaleY,float fRotation)
	{
		if (!lpTexture)
			return;

		//Create Sprite
		if (m_pSpriteUIImage == nullptr)
			D3DXCreateSprite(GRAPHICENGINE->GetDevice(),&m_pSpriteUIImage);

		//Sprite Transformation
		D3DXVECTOR2 scale(fScaleX,fScaleY);
		D3DXVECTOR2 trans((float)iX,(float)iY);
		D3DXVECTOR2 center((float)(iWidth >> 1) * fScaleX,(float)(iHeight >> 1) * fScaleY);

		fRotation = D3DXToRadian(fRotation);

		D3DXMATRIX matrix;

		D3DXMatrixTransformation2D(&matrix,NULL,0.0f,&scale,&center,fRotation,&trans);

		//Sprite Rectangle
		RECT rSourceRect;
		rSourceRect.left = iSourceX;
		rSourceRect.top = iSourceY;
		rSourceRect.right = rSourceRect.left + iWidth;
		rSourceRect.bottom = rSourceRect.top + iHeight;

		//Draw Sprite
		UINT uPasses = ImageRender::GetEffect() ? ImageRender::GetEffect()->GetPasses() : 1;

		for (UINT u = 0; u < uPasses; u ++)
		{
			if (SUCCEEDED(m_pSpriteUIImage->Begin(D3DXSPRITE_ALPHABLEND)))
			{
				if (ImageRender::GetEffect())
					ImageRender::GetEffect()->BeginPass(u);

				LPDIRECT3DBASETEXTURE9 lpOld;

				GRAPHICENGINE->GetDevice()->GetTexture(0,&lpOld);
				GRAPHICENGINE->GetDevice()->SetTexture(0,lpTexture);

				m_pSpriteUIImage->SetTransform(&matrix);
				m_pSpriteUIImage->Draw(lpTexture,&rSourceRect,NULL,NULL,dwColor);

				if (ImageRender::GetEffect())
					ImageRender::GetEffect()->EndPass();

				m_pSpriteUIImage->End();

				GRAPHICENGINE->GetDevice()->SetTexture(0,lpOld);
			}
		}
	}

	void ImageRender::Render(LPDIRECT3DTEXTURE9 lpTexture,int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY,DWORD dwColor,float fScale,float fRotation)
	{
		if (!lpTexture)
			return;

		//Create Sprite
		if (m_pSpriteUIImage == nullptr)
			D3DXCreateSprite(GRAPHICENGINE->GetDevice(),&m_pSpriteUIImage);

		//Sprite Transformation
		D3DXVECTOR2 scale(fScale,fScale);
		D3DXVECTOR2 trans((float)iX,(float)iY);
		D3DXVECTOR2 center((float)(iWidth >> 1) * fScale,(float)(iHeight >> 1) * fScale);

		fRotation = D3DXToRadian(fRotation);

		D3DXMATRIX matrix;

		D3DXMatrixTransformation2D(&matrix,NULL,fScale,&scale,&center,fRotation,&trans);

		//Sprite Rectangle
		RECT rSourceRect;
		rSourceRect.left = iSourceX;
		rSourceRect.top = iSourceY;
		rSourceRect.right = rSourceRect.left + iWidth;
		rSourceRect.bottom = rSourceRect.top + iHeight;

		//Draw Sprite
		UINT uPasses = ImageRender::GetEffect() ? ImageRender::GetEffect()->GetPasses() : 1;

		for (UINT u = 0; u < uPasses; u ++)
		{
			if (SUCCEEDED(m_pSpriteUIImage->Begin(D3DXSPRITE_ALPHABLEND)))
			{
				if (ImageRender::GetEffect())
					ImageRender::GetEffect()->BeginPass(u);

				LPDIRECT3DBASETEXTURE9 lpOld;

				GRAPHICENGINE->GetDevice()->GetTexture(0,&lpOld);
				GRAPHICENGINE->GetDevice()->SetTexture(0,lpTexture);

				m_pSpriteUIImage->SetTransform(&matrix);
				m_pSpriteUIImage->Draw(lpTexture,&rSourceRect,NULL,NULL,dwColor);

				if (ImageRender::GetEffect())
					ImageRender::GetEffect()->EndPass();

				m_pSpriteUIImage->End();

				GRAPHICENGINE->GetDevice()->SetTexture(0,lpOld);
			}
		}
	}
	void ImageRender::Render(LPDIRECT3DTEXTURE9 lpTexture,int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY,DWORD dwColor,float fScale,float fRotation,Point2D sRotationPoint,DWORD dwFlags)
	{
		if (!lpTexture)
			return;

		//Create Sprite
		if (m_pSpriteUIImage == nullptr)
			D3DXCreateSprite(GRAPHICENGINE->GetDevice(),&m_pSpriteUIImage);

		//Sprite Transformation
		D3DXVECTOR2 scale(fScale,fScale);
		D3DXVECTOR2 trans((float)iX,(float)iY);
		D3DXVECTOR2 center((float)(iWidth >> 1) * fScale,(float)(iHeight >> 1) * fScale);

		fRotation = D3DXToRadian(fRotation);

		D3DXMATRIX matrix;

		D3DXMatrixTransformation2D(&matrix,NULL,fScale,&scale,&center,fRotation,&trans);

		//Sprite Rectangle
		RECT rSourceRect;
		rSourceRect.left = iSourceX;
		rSourceRect.top = iSourceY;
		rSourceRect.right = rSourceRect.left + iWidth;
		rSourceRect.bottom = rSourceRect.top + iHeight;

		//Draw Sprite
		UINT uPasses = ImageRender::GetEffect() ? ImageRender::GetEffect()->GetPasses() : 1;

		for (UINT u = 0; u < uPasses; u ++)
		{
			if (SUCCEEDED(m_pSpriteUIImage->Begin(dwFlags)))
			{
				if (ImageRender::GetEffect())
					ImageRender::GetEffect()->BeginPass(u);

				LPDIRECT3DBASETEXTURE9 lpOld;

				GRAPHICENGINE->GetDevice()->GetTexture(0,&lpOld);
				GRAPHICENGINE->GetDevice()->SetTexture(0,lpTexture);

				m_pSpriteUIImage->SetTransform(&matrix);
				m_pSpriteUIImage->Draw(lpTexture,&rSourceRect,NULL,NULL,dwColor);

				if (ImageRender::GetEffect())
					ImageRender::GetEffect()->EndPass();

				m_pSpriteUIImage->End();

				GRAPHICENGINE->GetDevice()->SetTexture(0,lpOld);
			}
		}
	}

	void ImageRender::Render(LPDIRECT3DTEXTURE9 lpTexture,int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY,DWORD dwColor,BOOL bScaleResolution)
	{
		if (!lpTexture)
			return;

		//Create Sprite
		if (m_pSpriteUIImage == nullptr)
			D3DXCreateSprite(GRAPHICENGINE->GetDevice(),&m_pSpriteUIImage);

		//Sprite Transformation
		D3DXVECTOR2 scale(1.0f,1.0f);

		if (bScaleResolution)
		{
			scale.x = (float)GRAPHICENGINE->GetBackWidth() / (float)iWidth;
			scale.y = (float)GRAPHICENGINE->GetBackHeight() / (float)iHeight;
		}
		D3DXVECTOR2 trans((float)iX,(float)iY);
		D3DXVECTOR2 center((float)(iWidth >> 1),(float)(iHeight >> 1));

		float fRotation = D3DXToRadian(0.0f);

		D3DXMATRIX matrix;

		D3DXMatrixTransformation2D(&matrix,NULL,0.0f,&scale,&center,fRotation,&trans);

		//Sprite Rectangle
		RECT rSourceRect;
		rSourceRect.left = iSourceX;
		rSourceRect.top = iSourceY;
		rSourceRect.right = rSourceRect.left + iWidth;
		rSourceRect.bottom = rSourceRect.top + iHeight;

		//Draw Sprite
		UINT uPasses = ImageRender::GetEffect() ? ImageRender::GetEffect()->GetPasses() : 1;

		for (UINT u = 0; u < uPasses; u ++)
		{
			if (SUCCEEDED(m_pSpriteUIImage->Begin(D3DXSPRITE_ALPHABLEND)))
			{
				if (ImageRender::GetEffect())
					ImageRender::GetEffect()->BeginPass(u);

				LPDIRECT3DBASETEXTURE9 lpOld;

				GRAPHICENGINE->GetDevice()->GetTexture(0,&lpOld);
				GRAPHICENGINE->GetDevice()->SetTexture(0,lpTexture);

				m_pSpriteUIImage->SetTransform(&matrix);
				m_pSpriteUIImage->Draw(lpTexture, &rSourceRect, NULL, NULL, dwColor);

				if (ImageRender::GetEffect())
					ImageRender::GetEffect()->EndPass();

				m_pSpriteUIImage->End();

				GRAPHICENGINE->GetDevice()->SetTexture(0, lpOld);
			}
		}
	}

	void ImageRender::Render(class Image *pImage,int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY,DWORD dwColor,float fScale,float fRotation,DWORD dwFlags)
	{
		if (!pImage)
			return;

		//Create Sprite
		if (m_pSpriteUIImage == nullptr)
			D3DXCreateSprite(GRAPHICENGINE->GetDevice(),&m_pSpriteUIImage);

		//Sprite Transformation
		D3DXVECTOR2 scale(fScale,fScale);
		D3DXVECTOR2 trans((float)iX,(float)iY);
		D3DXVECTOR2 center((float)(iWidth >> 1) * fScale,(float)(iHeight >> 1) * fScale);

		fRotation = D3DXToRadian(fRotation);

		D3DXMATRIX matrix;

		D3DXMatrixTransformation2D(&matrix,NULL,0.0f,&scale,&center,fRotation,&trans);

		//Sprite Rectangle
		RECT rSourceRect;
		rSourceRect.left = iSourceX;
		rSourceRect.top = iSourceY;
		rSourceRect.right = rSourceRect.left + iWidth;
		rSourceRect.bottom = rSourceRect.top + iHeight;

		//Draw Sprite
		UINT uPasses = ImageRender::GetEffect() ? ImageRender::GetEffect()->GetPasses() : 1;

		auto lpTexture = pImage->GetTexture();

		for (UINT u = 0; u < uPasses; u ++)
		{
			if (SUCCEEDED(m_pSpriteUIImage->Begin(dwFlags)))
			{
				if (ImageRender::GetEffect())
					ImageRender::GetEffect()->BeginPass(u);

				LPDIRECT3DBASETEXTURE9 lpOld;

				GRAPHICENGINE->GetDevice()->GetTexture(0,&lpOld);
				GRAPHICENGINE->GetDevice()->SetTexture(0,lpTexture);

				m_pSpriteUIImage->SetTransform(&matrix);
				m_pSpriteUIImage->Draw(lpTexture,&rSourceRect,NULL,NULL,dwColor);

				if (ImageRender::GetEffect())
					ImageRender::GetEffect()->EndPass();

				m_pSpriteUIImage->End();

				GRAPHICENGINE->GetDevice()->SetTexture(0,lpOld);
			}
		}
	}

	void ImageRender::Render(class Image *pImage,int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY,DWORD dwColor,float fScale,float fRotation,Point2D sRotationPoint)
	{
		if (!pImage)
			return;

		//Create Sprite
		if (m_pSpriteUIImage == nullptr)
			D3DXCreateSprite(GRAPHICENGINE->GetDevice(),&m_pSpriteUIImage);

		//Sprite Transformation
		D3DXVECTOR2 scale(fScale,fScale);
		D3DXVECTOR2 trans((float)iX,(float)iY);
		D3DXVECTOR2 center((float)(iWidth >> 1),(float)(iHeight >> 1));

		fRotation = D3DXToRadian(fRotation);

		D3DXMATRIX matrix;

		D3DXMatrixTransformation2D(&matrix,NULL,0.0f,&scale,&center,fRotation,&trans);

		//Sprite Rectangle
		RECT rSourceRect;
		rSourceRect.left = iSourceX;
		rSourceRect.top = iSourceY;
		rSourceRect.right = rSourceRect.left + iWidth;
		rSourceRect.bottom = rSourceRect.top + iHeight;

		//Draw Sprite
		UINT uPasses = ImageRender::GetEffect() ? ImageRender::GetEffect()->GetPasses() : 1;

		auto lpTexture = pImage->GetTexture();

		for (UINT u = 0; u < uPasses; u ++)
		{
			if (SUCCEEDED(m_pSpriteUIImage->Begin(D3DXSPRITE_ALPHABLEND)))
			{
				if (ImageRender::GetEffect())
					ImageRender::GetEffect()->BeginPass(u);

				LPDIRECT3DBASETEXTURE9 lpOld;

				GRAPHICENGINE->GetDevice()->GetTexture(0,&lpOld);
				GRAPHICENGINE->GetDevice()->SetTexture(0,lpTexture);

				m_pSpriteUIImage->SetTransform(&matrix);
				m_pSpriteUIImage->Draw(lpTexture,&rSourceRect,NULL,NULL,dwColor);

				if (ImageRender::GetEffect())
					ImageRender::GetEffect()->EndPass();

				m_pSpriteUIImage->End();

				GRAPHICENGINE->GetDevice()->SetTexture(0,lpOld);
			}
		}
	}

	void ImageRender::Render(class Image *pImage,int iX,int iY,int iWidth,int iHeight,DWORD dwColor)
	{
		if (!pImage)
			return;

		//Create Sprite
		if (m_pSpriteUIImage == nullptr)
			D3DXCreateSprite(GRAPHICENGINE->GetDevice(),&m_pSpriteUIImage);

		//Viewport
		D3DVIEWPORT9 sViewPort;
		GRAPHICENGINE->GetDevice()->GetViewport(&sViewPort);

		D3DXVECTOR3 pos((float)iX + sViewPort.X,(float)iY + sViewPort.Y,0.0f);

		//Sprite Transformation
		D3DXVECTOR2 scale(1.0f,1.0f);
		ImageLoader::SetScale(pImage,iWidth,iHeight,&scale);
		D3DXVECTOR2 trans((float)iX,(float)iY);
		D3DXVECTOR2 center((float)(iWidth >> 1),(float)(iHeight >> 1));

		D3DXMATRIX matrix;

		D3DXMatrixTransformation2D(&matrix, NULL, 0.0f, &scale, &center, 0.0f, &trans);

		//Draw Sprite
		UINT uPasses = ImageRender::GetEffect() ? ImageRender::GetEffect()->GetPasses() : 1;

		auto lpTexture = pImage->GetTexture();

		for (UINT u = 0; u < uPasses; u ++)
		{
			if (SUCCEEDED(m_pSpriteUIImage->Begin(D3DXSPRITE_ALPHABLEND)))
			{
				if (ImageRender::GetEffect())
					ImageRender::GetEffect()->BeginPass(u);

				LPDIRECT3DBASETEXTURE9 lpOld;

				GRAPHICENGINE->GetDevice()->GetTexture(0,&lpOld);
				GRAPHICENGINE->GetDevice()->SetTexture(0,lpTexture);

				m_pSpriteUIImage->SetTransform(&matrix);
				m_pSpriteUIImage->Draw(lpTexture,NULL,NULL,NULL,dwColor);

				if (ImageRender::GetEffect())
					ImageRender::GetEffect()->EndPass();

				m_pSpriteUIImage->End();

				GRAPHICENGINE->GetDevice()->SetTexture(0,lpOld);
			}
		}
	}
	void ImageRender::RenderQuad(class Image *pImage,int iX,int iY,int iWidth,int iHeight,DWORD dwColor)
	{
		float u1,v1,u2,v2;

		//Compute texture coordinates .it ' easy
		u1 = 0.0f;
		v1 = 0.0f;
		u2 = 1.0f;
		v2 = 1.0f;

		//SMD::VEERTEX rVertex[4];
		SMD::Vertex rVertex[4];

		float fRenderX = float(iX) - 0.5f;
		float fRenderY = float(iY) - 0.5f;
		float fRenderWidth = fRenderX + float(iWidth);
		float fRenderHeight = fRenderY + float(iHeight);

		rVertex[0] = { fRenderX		,fRenderY		,0,1,D3DCOLOR_XRGB(255,255,255),0,u1,v1 };
		rVertex[1] = { fRenderWidth	,fRenderY		,0,1,D3DCOLOR_XRGB(255,255,255),0,u2,v1 };
		rVertex[2] = { fRenderX		,fRenderHeight	,0,1,D3DCOLOR_XRGB(255,255,255),0,u1,v2 };
		rVertex[3] = { fRenderWidth	,fRenderHeight	,0,1,D3DCOLOR_XRGB(255,255,255),0,u2,v2 };

		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);

		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ZENABLE,TRUE);
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);

		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_LIGHTING,FALSE);
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
		GRAPHICENGINE->GetDevice()->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);

		//Texture Stage States
		GRAPHICENGINE->GetDevice()->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
		GRAPHICENGINE->GetDevice()->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);

		GRAPHICENGINE->GetDevice()->SetTexture(0,pImage->GetTexture());

		GRAPHICENGINE->GetDevice()->SetFVF(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_SPECULAR|D3DFVF_TEX1);
		GRAPHICENGINE->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,(LPVOID)rVertex,sizeof(SMD::Vertex));
	}
	void ImageRender::RenderQuad(class Image *pImage, int iX, int iY, int iWidth, int iHeight, Rectangle2DF fRect, DWORD dwColor)
	{
		float u1, v1, u2, v2;

		//Compute texture coordinates .it ' easy
		u1 = fRect.fX;
		v1 = fRect.fY;
		u2 = fRect.fWidth;
		v2 = fRect.fHeight;

		//SMD::VEERTEX rVertex[4];
		SMD::Vertex rVertex[4];

		float fRenderX = float(iX) - 0.5f;
		float fRenderY = float(iY) - 0.5f;
		float fRenderWidth = fRenderX + float(iWidth);
		float fRenderHeight = fRenderY + float(iHeight);

		rVertex[0] = { fRenderX		,fRenderY		,0,1,D3DCOLOR_XRGB(255,255,255),0,u1,v1 };
		rVertex[1] = { fRenderWidth	,fRenderY		,0,1,D3DCOLOR_XRGB(255,255,255),0,u2,v1 };
		rVertex[2] = { fRenderX		,fRenderHeight	,0,1,D3DCOLOR_XRGB(255,255,255),0,u1,v2 };
		rVertex[3] = { fRenderWidth	,fRenderHeight	,0,1,D3DCOLOR_XRGB(255,255,255),0,u2,v2 };

		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ZENABLE, TRUE);
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		GRAPHICENGINE->GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

		//Texture Stage States
		GRAPHICENGINE->GetDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		GRAPHICENGINE->GetDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

		GRAPHICENGINE->GetDevice()->SetTexture(0, pImage->GetTexture());

		GRAPHICENGINE->GetDevice()->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX1);
		GRAPHICENGINE->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, (LPVOID)rVertex, sizeof(SMD::Vertex));
	}
	void ImageRender::OnLostDevice()
	{
		if (m_pSpriteUIImage)
			m_pSpriteUIImage->OnLostDevice();
	}
	void ImageRender::OnResetDevice()
	{
		if (m_pSpriteUIImage)
			m_pSpriteUIImage->OnResetDevice();
	}
}