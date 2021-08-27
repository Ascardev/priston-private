#ifndef	_DRAWSUB_HEADER

#define _DRAWSUB_HEADER

#define	dsARRAY_LEFT	0
#define	dsARRAY_TOP		0
#define	dsARRAY_RIGHT	1
#define	dsARRAY_BOTTOM	2

extern int	dsDrawOffsetArray;

extern POINT dsDrawOffset;

int GetTextWidth(int iFont, char *lpString);
int GetTextHeight(int iFont, char *lpString);
int dsTextLineOut(int iFont,int x,int y,LPCTSTR String,int nCount,DWORD Color,int Flag = 1);
int dsTextLineOut(int iFont,LPCTSTR String,int nCount,RECT *pRect,DWORD Color);
int dsGetDrawOffset( int *sx , int *sy );
int dsMenuCursorPos( POINT *lpCursorPos , int Mode );

int dsDrawColorBox( DWORD Color ,int x, int y, int sizeX, int sizeY );
int dsDrawColorBoxFloat( DWORD Color ,float x, float y, float sizeX, float sizeY );

void psSetRenderState(int SamplerState);
void psDraw2DImage(LPDIRECT3DTEXTURE9 lpTexture,D3DTLVERTEX9 *tlVertex);

void psDraw2DImage2(LPDIRECT3DTEXTURE9 lpTexture,D3DTLVERTEX9 *tlVertex);

//‰÷»æBMPÕº∆¨
int dsDrawTexImage(smTEXTUREHANDLE *lpTexture,RECT *DestRect,RECT *SrcRect);

int dsDrawTexImage( int Mat , int x, int y, int w, int h , DWORD Transp , int specular = 0);

int dsDrawTexImageFloat( int Mat , float x, float y, float w, float h , DWORD dwColor , int specular =0 );

int dsDrawTexImage( int Mat, int x, int y, int w, int h, float surW, float surH, float tLeft, float tTop, float tRight, float tBottom, int Transp);
int dsDrawTexImageFloat( int Mat, float x, float y, float w, float h, float surW, float surH, float tLeft, float tTop, float tRight, float tBottom, int Transp);

int dsDrawTexImageFloatColor( int Mat, float x, float y, float w, float h, float surW, float surH, float tLeft, float tTop, float tRight, float tBottom, DWORD dwColor );

int dsDrawTexImage2(smTEXTUREHANDLE *lpTexture, float x, float y, float w, float h, DWORD dwColor);

#endif