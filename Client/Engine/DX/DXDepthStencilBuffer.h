#pragma once

namespace DX
{
	typedef std::shared_ptr<class DepthStencilBuffer>LPDEPTHSTENCILBUFFER;

	class DepthStencilBuffer:public std::enable_shared_from_this<DepthStencilBuffer>
	{
		friend class GraphicsDevice;

	public:
		DepthStencilBuffer(std::weak_ptr<GraphicsDevice> pGraphicsDevice,int iSharableID,UINT uSizeShiftRight);
		DepthStencilBuffer(std::weak_ptr<GraphicsDevice> pGraphicsDevice,int iSharableID,UINT uWidth,UINT uHeight);
		virtual ~DepthStencilBuffer();

		LPDIRECT3DSURFACE9 GetSurface() {return m_lpSurface;}
		void OnLostDevice();
		void OnResetDevice();

		int GetSharableID() {return m_iSharableID;}
		UINT GetSizeShiftRight() {return m_uSizeShiftRight;}

		UINT GetWidth() {return m_uWidth;}
		UINT GetHeight() {return m_uHeight;}
	private:
		std::weak_ptr<GraphicsDevice> m_pGraphicsDevice;
		int m_iSharableID;
		UINT m_uSizeShiftRight;
		LPDIRECT3DSURFACE9 m_lpSurface;
		UINT m_uWidth;
		UINT m_uHeight;
	};
}