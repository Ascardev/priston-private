#pragma once

namespace DX
{
	typedef std::shared_ptr<class RenderTarget> LPRENDERTARGET;

	class RenderTarget : public std::enable_shared_from_this<RenderTarget>
	{
		friend class GraphicsDevice;

	public:
		RenderTarget(std::weak_ptr<GraphicsDevice> pGraphicsDevice,int iSharableID,UINT uSizeShiftRight);
		RenderTarget(std::weak_ptr<GraphicsDevice> pGraphicsDevice,int iSharableID,UINT uWidth,UINT uHeight);
		virtual ~RenderTarget();

		void OnLostDevice();
		void OnResetDevice();

		LPDIRECT3DTEXTURE9 GetTexture() {return m_lpTexture;}
		LPDIRECT3DSURFACE9 GetSurface() {return m_lpSurface;}

		BOOL GetSharableID() {return m_iSharableID;}
		UINT GetSizeShiftRight() {return m_uSizeShiftRight;}

		UINT GetWidth() {return m_uWidth;}
		UINT GetHeight() {return m_uHeight;}
	private:
		std::weak_ptr<GraphicsDevice> m_pGraphicsDevice;
		int m_iSharableID;
		UINT m_uSizeShiftRight;

		UINT m_uWidth;
		UINT m_uHeight;

		LPDIRECT3DTEXTURE9 m_lpTexture;
		LPDIRECT3DSURFACE9 m_lpSurface;
	};
}