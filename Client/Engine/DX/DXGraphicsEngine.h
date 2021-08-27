#pragma once

#define GRAPHICDEVICE		(GRAPHICENGINE->GetGraphicDevice())
#define RESOLUTION_WIDTH	(GRAPHICENGINE->GetBackWidth())
#define RESOLUTION_HEIGHT	(GRAPHICENGINE->GetBackHeight())

struct RESOLUTIONSTRUCT
{
	UINT uWidth;
	UINT uHeight;
	BOOL bWindow;
};

namespace DX
{
	typedef class GraphicsEngine *LPGRAPHICSENGINE;

	class GraphicsEngine
	{
	public:
		GraphicsEngine();
		virtual ~GraphicsEngine();

		BOOL InitD3D(HWND hWnd);
		BOOL CreateInterface();
		BOOL CreateDevice(HWND hWnd);

		BOOL CheckDevice();

		void OnLostDevice();
		void OnResetDevice();

		void BeginScene(D3DXMATRIX mView);
		void EndScene();

		BOOL Reset(BOOL bResetWindowed,UINT uResetWidth,UINT uResetHeight);
		void ResolutionChange(BOOL bFirstTime,int iWidth,int iHeight);

		std::string GetVideoName();

		LPDIRECT3DDEVICE9 GetDevice() {return m_pDevice;}

		LPGRAPHICSDEVICE GetGraphicDevice() { return m_pGraphicsDevice; }
		D3DPRESENT_PARAMETERS Get3DPP() { return m_d3dPP; }

		int GetBackWidth() { return (int)m_sResolution.uWidth; }
		int GetBackHeight() { return (int)m_sResolution.uHeight; }

		void DrawRectangle(Rectangle2D rRect, DWORD dwColor1, DWORD dwColor2);
		void ResizeWindow();
		void Log(const char *pszFormat,...);
		void Error(const char *pszFormat,...);
	private:
		HRESULT m_hr;
		HWND m_hWnd;
		RESOLUTIONSTRUCT m_sResolution;
		D3DPRESENT_PARAMETERS m_d3dPP;
		D3DDISPLAYMODE m_d3dm;
		D3DCAPS9 m_d3dCaps;
		LPDIRECT3D9 m_pD3D = NULL;
		LPDIRECT3DDEVICE9 m_pDevice = NULL;
		LPGRAPHICSDEVICE m_pGraphicsDevice;
		//LPGLOW m_pGlow;
	};
}