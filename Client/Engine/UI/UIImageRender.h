#pragma once

namespace UI
{
	class ImageRender
	{
	public:
		ImageRender();
		virtual ~ImageRender();

		static DX::LPEFFECT GetEffect();
		static void SetEffect(DX::LPEFFECT p);

		static void Render(LPDIRECT3DTEXTURE9 lpTexture,int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY,DWORD dwColor,float fScaleX,float fScaleY,float fRotation = 0.0f);
		static void Render(LPDIRECT3DTEXTURE9 lpTexture,int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY,DWORD dwColor,float fScale = 1.0f,float fRotation = 0.0f);
		static void Render(LPDIRECT3DTEXTURE9 lpTexture,int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY,DWORD dwColor,float fScale,float fRotation,Point2D sRotationPoint,DWORD dwFlags = D3DXSPRITE_ALPHABLEND);
		static void Render(LPDIRECT3DTEXTURE9 lpTexture,int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY,DWORD dwColor,BOOL bScaleResolution);
		static void Render(class Image *pImage,int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY,DWORD dwColor,float fScale = 1.0f,float fRotation = 0.0f,DWORD dwFlags = D3DXSPRITE_ALPHABLEND);
		static void Render(class Image *pImage,int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY,DWORD dwColor,float fScale,float fRotation,Point2D sRotationPoint);
		static void Render(class Image *pImage,int iX,int iY,int iWidth,int iHeight,DWORD dwColor);
		static void RenderQuad(class Image *pImage,int iX,int iY,int iWidth,int iHeight,DWORD dwColor);
		static void RenderQuad(class Image *pImage, int iX, int iY, int iWidth, int iHeight, Rectangle2DF fRect, DWORD dwColor);
		static void OnResetDevice();
		static void OnLostDevice();
	private:
		static DX::LPEFFECT m_pEffect;
		static LPD3DXSPRITE m_pSpriteUIImage;
	};
}