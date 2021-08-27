#pragma once

#include "DXTexture.h"
#include "DXRenderTarget.h"

namespace DX
{
	typedef std::shared_ptr<class Sprite> LPSPRITE;

	class Sprite
	{
	public:
		Sprite(LPD3DXSPRITE lpSprite,BOOL bSharable);
		Sprite(const Sprite &c);
		virtual ~Sprite();

		LPD3DXSPRITE Get() {return m_lpSprite;}

		void OnLostDevice();
		void OnResetDevice();

		void Reset();

		BOOL Begin(BOOL bAlphaBlending);
		void End();

		void Draw(LPTEXTURE pTexture,const Color &cColor);
		void Draw(LPTEXTURE pTexture,const Color &cColor,int iWidth,int iHeight);
		void Draw(LPTEXTURE pTexture,const Color &cColor,const RECT &rSourceRect,int iX,int iY);
		void Draw(LPRENDERTARGET pRenderTarget);

		void Flush();

		void PushScaling2DTransform(const Vector2DF & vScaling,const Vector2DF & vScalingCenter = Vector2DF(0.0f,0.0f));
		void PushRotation2DTransform(float fRotation, const Vector2DF & vRotationCenter = Vector2DF(0.0f,0.0f));
		void PushTranslation2DTransform(const Vector2DF & vTranslation);

		void PushTransform(const Matrix4DF & mMatrix);
		void PopTransform(int iPopCount = 1);

		BOOL IsSharable() {return m_bSharable;}
		void SetStencilEnable(BOOL b) { m_bStencilEnable = b; }
	private:
		LPD3DXSPRITE m_lpSprite;
		BOOL m_bSharable;
		UINT m_uUseCount = 0;
		BOOL m_bStencilEnable = FALSE;
		LPD3DXMATRIXSTACK m_lpMatrixStack;
	};
}