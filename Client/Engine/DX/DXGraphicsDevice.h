#pragma once

#define FONTHANDLE		(GRAPHICDEVICE->GetFontFactory())
#define CAMERAHANDLE	(GRAPHICDEVICE->GetCamera())
#define LINEHANDLE		(GRAPHICDEVICE->GetLineFactory())
#define SPRITEHANDLE	(GRAPHICDEVICE->GetSpriteFactory())

namespace DX
{
	enum RenderState
	{
		RENDERSTATE_ScissorTest,

		RENDERSTATE_StencilEnable,
		RENDERSTATE_StencilFail,
		RENDERSTATE_StencilZFail,
		RENDERSTATE_StencilPass,
		RENDERSTATE_StencilFunc,
		RENDERSTATE_StencilRef,
		RENDERSTATE_StencilMask,
		RENDERSTATE_StencilWriteMask,
	};

	typedef std::shared_ptr<class GraphicsDevice>LPGRAPHICSDEVICE;

	class GraphicsDevice : public std::enable_shared_from_this<GraphicsDevice>
	{
	private:
		struct Info
		{
			UINT uBackBufferWidth;
			UINT uBackBufferHeight;
			D3DFORMAT d3dBackBufferFormat;

			UINT uDepthStencilBufferWidth;
			UINT uDepthStencilBufferHeight;
			D3DFORMAT d3dDepthStencilBufferFormat;

			UINT uRenderTargetWidth;
			UINT uRenderTargetHeight;
			D3DFORMAT d3dRenderTargetFormat;
		};
	public:
		GraphicsDevice(LPDIRECT3DDEVICE9 pDevice);
		virtual ~GraphicsDevice();

		LPDIRECT3DDEVICE9 Get() {return m_pD3DDevice;}
		
		void OnLostDevice();
		void OnResetDevice();
		ViewPort GetViewport() const;
		BOOL SetViewport(const ViewPort &vViewport);

		BOOL Clear(BOOL bTarget,BOOL bZBuffer,BOOL bStencil);

		BOOL Begin();
		BOOL End();

		void SetRenderState(RenderState eState,DWORD dwValue);

		BOOL SetRenderTarget(LPRENDERTARGET pRenderTarget);
		void UnsetRenderTarget();
		void UpdateRenderTargetInfo();

		BOOL SetDepthStencilBuffer(LPDEPTHSTENCILBUFFER pDepthStencilBuffer);
		void UnsetDepthStencilBuffer();

		//BOOL SetRenderTarget()
		BOOL BuildRenderTarget(LPRENDERTARGET pRenderTarget);
		BOOL BuildDepthStencilBuffer(LPDEPTHSTENCILBUFFER pDepthStencilBuffer);

		LPDEPTHSTENCILBUFFER MakeDepthStencilBuffer(int iSharableID,UINT uSizeShiftRight);
		LPDEPTHSTENCILBUFFER MakeDepthStencilBuffer(int iSharableID,UINT uWidth,UINT uHeight);

		LPRENDERTARGET MakeRenderTarget(int iSharableID,UINT uSizeShiftRight);
		LPRENDERTARGET MakeRenderTarget(int iSharableID,UINT uWidth,UINT uHeight);

		UINT GetBackBufferWidth() const {return m_sInfo.uBackBufferWidth;}
		UINT GetBackBufferHeight() const {return m_sInfo.uBackBufferHeight;}

		UINT GetRenderTargetWidth() const {return m_sInfo.uRenderTargetWidth;}
		UINT GetRenderTargetHeight() const {return m_sInfo.uRenderTargetHeight;}

		const Info &GetInfo() const {return m_sInfo;}

		void PushScissorRect(const RECT &rRect);
		void PopScissorRect();

		BOOL HaveScissorRect() { return (m_vpScissorRect.size() > 0); }

		LPRECT GetScissorRect();
		void SetScissorRect(const RECT &rRect);
		void GetScissorRectInside(RECT &rRect);

		LPEFFECTFACTORY GetEffectFactory() const {return m_pEffectFactory;}
		LPTEXTUREFACTORY GetTextureFactory() const {return m_pTextureFactory;}
		LPSPRITEFACTORY GetSpriteFactory() const {return m_pSpriteFactory;}
		LPFONTFACTORY GetFontFactory() const {return m_pFontFactory;}
		LPCAMERA GetCamera() const {return m_pCamera;}
		LPLINEFACTORY GetLineFactory() const {return m_pLineFactory;}
	protected:
		LPDEPTHSTENCILBUFFER FindDepthStencilBuffer(int iSharableID,UINT uSizeShiftRight);
		LPDEPTHSTENCILBUFFER FindDepthStencilBuffer(int iSharableID,UINT uWidth,UINT uHeight);

		LPRENDERTARGET FindRenderTarget(int iSharableID,UINT uSizeShiftRight);
		LPRENDERTARGET FindRenderTarget(int iSharableID,UINT uWidth,UINT uHeight);

		void PushDepthStencilBuffer();
		void PopDepthStencilBuffer();

		void PushRenderTarget();
		void PopRenderTarget();
		void Setup();
	private:
		LPDIRECT3DDEVICE9 m_pD3DDevice;
		Info m_sInfo;

		LPTEXTUREFACTORY m_pTextureFactory;
		LPEFFECTFACTORY m_pEffectFactory;
		LPSPRITEFACTORY m_pSpriteFactory;
		LPFONTFACTORY	m_pFontFactory;
		LPCAMERA		m_pCamera;
		LPLINEFACTORY	m_pLineFactory;

		std::vector<LPDEPTHSTENCILBUFFER> m_vDepthStencilBuffers;
		std::vector<LPRENDERTARGET> m_vRenderTargets;

		std::stack<LPDIRECT3DSURFACE9> m_sRenderTargets;
		std::stack<LPDIRECT3DSURFACE9> m_sDepthStencilBuffers;

		std::vector<LPRECT> m_vpScissorRect;
	};
}