#include <d3d9.h>
#include <d3dx9.h>
#include <Shlwapi.h>

// 安全恢复
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
// 安全删除
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }

extern int smFlipCount;


typedef struct {
	float r, g, b, a;
} COLORVALUE, *LPCOLORVALUE;

typedef struct {
	float	x, y, z;
} VECTOR, *LPVECTOR;

typedef struct {
    float   tu, tv;
} TVERTEX, *LPTVERTEX;


#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "Msimg32.lib")

#define EFFECT_MAX 2

class DXGraphicEngine
{
public:
	DXGraphicEngine();
	~DXGraphicEngine();
public:
	BOOL CreateDevice(int width,int height,BOOL windowed,int Anti,int vsync);
	BOOL LoadEffect(char *szFxFileName);
	void ReleaseDevice();
	void InitRender();
	void BeginRender();
	void EndRender();
	void RestoreDevice();
	BOOL ResetDevice(int width,int height,BOOL windowed,int Anti,int vsync);
protected:
	void InvalidateDevice();
	void RestoredataDevice();
	BOOL CheckDevice();
public:
	LPDIRECT3D9			lpD3D;
	LPDIRECT3DDEVICE9	lpD3DDevice;
	LPD3DXSPRITE		lpD3DSprite;
	LPD3DXFONT			lpD3DFont;
	LPD3DXFONT			lpD3DBoldFont;
	LPD3DXEFFECT		lpD3DEffect[EFFECT_MAX];
private:
	int m_width;
	int m_height;
	BOOL m_Anti;
	DWORD m_vsync;
	BOOL m_windowed;
	BOOL m_isLost;
	D3DPRESENT_PARAMETERS m_d3dpp;
};

extern DXGraphicEngine cDXGraphic;