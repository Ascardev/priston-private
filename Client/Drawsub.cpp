#include "StdAfx.h"
#include "Drawsub.h"

int	dsDrawOffsetArray = 0;
POINT dsDrawOffset = { 0 };

int dsTextLineOut(int iFont, int x, int y, LPCTSTR String, int nCount, DWORD Color, int Flag)
{
	if (Flag == 1)
	{
		if (dsDrawOffset.x || dsDrawOffset.y)
		{
			if (dsDrawOffsetArray & dsARRAY_RIGHT)
				x += dsDrawOffset.x;

			if (dsDrawOffsetArray & dsARRAY_BOTTOM)
				y += dsDrawOffset.y;
		}
	}

	DX::LPFONT pFont = FONTHANDLE->MakeFont("Tahoma", 15, 0, FALSE, iFont == 0 ? FALSE : TRUE);

	pFont->Draw(x, y, String, DT_LEFT, Color);

	return TRUE;
}
int dsTextLineOut(int iFont, LPCTSTR String, int nCount, RECT *pRect, DWORD Color)
{
	DX::LPFONT pFont = FONTHANDLE->MakeFont("Tahoma", 15, 0, FALSE, iFont == 0 ? FALSE : TRUE);

	pFont->Draw(*pRect, String, DT_RIGHT, Color);

	return TRUE;
}
int dsGetDrawOffset(int *sx, int *sy)
{
	if (dsDrawOffset.x == 0 && dsDrawOffset.y == 0)
		return TRUE;

	if (dsDrawOffsetArray & dsARRAY_RIGHT)
		*sx += dsDrawOffset.x;

	if (dsDrawOffsetArray & dsARRAY_BOTTOM)
		*sy += dsDrawOffset.y;

	return TRUE;
}

int GetTextWidth(int iFont,char *lpString)
{
	auto pFont = FONTHANDLE->MakeFont("Tahoma", 15, 0, FALSE, iFont == 0 ? FALSE : TRUE);

	return pFont ? pFont->GetWidthText(lpString, STRLEN(lpString)) : 0;
}
int GetTextHeight(int iFont, char *lpString)
{
	auto pFont = FONTHANDLE->MakeFont("Tahoma", 15, 0, FALSE, iFont == 0 ? FALSE : TRUE);

	return pFont ? pFont->GetHeightText(lpString, STRLEN(lpString)) : 0;
}

static POINT BackCursorPos;

void psSetRenderState(int SamplerState)
{
	GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ZENABLE, TRUE);
	GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_DITHERENABLE, TRUE);

	GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_SPECULARENABLE, TRUE);

	GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	GRAPHICENGINE->GetDevice()->SetTexture(1, NULL);
	GRAPHICENGINE->GetDevice()->SetTexture(2, NULL);
	GRAPHICENGINE->GetDevice()->SetTexture(3, NULL);
	GRAPHICENGINE->GetDevice()->SetTexture(4, NULL);
	GRAPHICENGINE->GetDevice()->SetTexture(5, NULL);
	GRAPHICENGINE->GetDevice()->SetTexture(6, NULL);
	GRAPHICENGINE->GetDevice()->SetTexture(7, NULL);

	smRender.AlphaTestDepth = ALPHATESTDEPTH;

	if (SamplerState == 0)
	{
		GRAPHICENGINE->GetDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
		GRAPHICENGINE->GetDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	}
	else
	{
		GRAPHICENGINE->GetDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		GRAPHICENGINE->GetDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	}
}
void psDraw2DImage(LPDIRECT3DTEXTURE9 lpTexture, D3DTLVERTEX9 *tlVertex)
{
	GRAPHICENGINE->GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	GRAPHICENGINE->GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	GRAPHICENGINE->GetDevice()->SetTexture(0, lpTexture);
	GRAPHICENGINE->GetDevice()->SetFVF(D3DFVF_TLVERTEX);
	GRAPHICENGINE->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, tlVertex, sizeof(D3DTLVERTEX9));

	GRAPHICENGINE->GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	GRAPHICENGINE->GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
}
void psDraw2DImage2(LPDIRECT3DTEXTURE9 lpTexture, D3DTLVERTEX9 *tlVertex)
{
	GRAPHICENGINE->GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	GRAPHICENGINE->GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	GRAPHICENGINE->GetDevice()->SetTexture(0, lpTexture);
	GRAPHICENGINE->GetDevice()->SetFVF(D3DFVF_TLVERTEX);
	GRAPHICENGINE->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, tlVertex, sizeof(D3DTLVERTEX9));
}
int dsMenuCursorPos(POINT *lpCursorPos, int Mode)
{
	int x, y;

	if (Mode)
	{
		BackCursorPos.x = lpCursorPos->x;
		BackCursorPos.y = lpCursorPos->y;

		x = RESOLUTION_WIDTH - 800;
		y = RESOLUTION_HEIGHT - 600;

		if (x > 0)
		{
			if (lpCursorPos->x >= 600 && lpCursorPos->y <= y + 420 && (!sSinWarpGate.ShowFlag || Mode != 1))
			{
				if (MouseItem.bValid)
				{
					lpCursorPos->x = 0;
					return TRUE;
				}
				lpCursorPos->x -= x;
				lpCursorPos->y -= y;
				if (lpCursorPos->x < 600)
					lpCursorPos->x = 0;
			}
			else
			{
				if (lpCursorPos->y > 400)
				{
					lpCursorPos->y -= y;

					if (lpCursorPos->y < 300)
						lpCursorPos->y = 0;
				}
			}
		}
	}
	else
	{
		lpCursorPos->x = BackCursorPos.x;
		lpCursorPos->y = BackCursorPos.y;
	}

	return TRUE;
}

int dsDrawColorBoxFloat(DWORD Color, float x, float y, float sizeX, float sizeY)
{
	D3DTLVERTEX9 tlVertex[16];
	int cnt;

	for (cnt = 0; cnt < 4; cnt++)
	{
		tlVertex[cnt].rhw = 1;
		tlVertex[cnt].color = Color;
		tlVertex[cnt].specular = D3DCOLOR_RGBA(0, 0, 0, 0);
		tlVertex[cnt].sz = 0;
	}

	tlVertex[0].sx = x;
	tlVertex[0].sy = y;
	tlVertex[0].tu = 0;
	tlVertex[0].tv = 0;

	tlVertex[1].sx = x;
	tlVertex[1].sy = (y + sizeY);
	tlVertex[1].tu = 0;
	tlVertex[1].tv = 1;

	tlVertex[2].sx = (x + sizeX);
	tlVertex[2].sy = y;
	tlVertex[2].tu = 1;
	tlVertex[2].tv = 0;

	tlVertex[3].sx = (x + sizeX);
	tlVertex[3].sy = (y + sizeY);
	tlVertex[3].tu = 1;
	tlVertex[3].tv = 1;

	psDraw2DImage(NULL, tlVertex);

	return TRUE;
}

int dsDrawColorBox(DWORD Color, int x, int y, int sizeX, int sizeY)
{

	dsGetDrawOffset(&x, &y);

	return dsDrawColorBoxFloat(Color, (float)x, (float)y, (float)sizeX, (float)sizeY);
}

int dsDrawTexImage(int Mat, int x, int y, int w, int h, DWORD Transp, int specular)
{
	dsGetDrawOffset(&x, &y);

	return dsDrawTexImageFloat(Mat, (float)x, (float)y, (float)w, (float)h, Transp, specular);

}
int dsDrawTexImage(int Mat, int x, int y, int w, int h, float surW, float surH, float tLeft, float tTop, float tRight, float tBottom, int Transp)
{
	return dsDrawTexImageFloat(Mat, (float)x, (float)y, (float)w, (float)h, surW, surH, tLeft, tTop, tRight, tBottom, Transp);
}

int dsDrawTexImageFloat(int Mat, float x, float y, float w, float h, float surW, float surH, float tLeft, float tTop, float tRight, float tBottom, int Transp)
{
	D3DTLVERTEX9 tlVertex[4];
	int cnt;

	for (cnt = 0; cnt < 4; cnt++)
	{
		tlVertex[cnt].rhw = 1;
		tlVertex[cnt].color = D3DCOLOR_RGBA(255, 255, 255, Transp);
		tlVertex[cnt].specular = D3DCOLOR_RGBA(0, 0, 0, 0);
		tlVertex[cnt].sz = 0;
	}

	tlVertex[0].sx = x;
	tlVertex[0].sy = y;
	tlVertex[0].tu = 1 * (tLeft / surW);
	tlVertex[0].tv = 1 * (tTop / surH);

	tlVertex[1].sx = x;
	tlVertex[1].sy = (y + h);
	tlVertex[1].tu = 1 * (tLeft / surW);
	tlVertex[1].tv = 1 * ((tBottom + 1) / surH);

	tlVertex[2].sx = (x + w);
	tlVertex[2].sy = y;
	tlVertex[2].tu = 1 * ((tRight + 1) / surW);
	tlVertex[2].tv = 1 * (tTop / surH);

	tlVertex[3].sx = (x + w);
	tlVertex[3].sy = (y + h);
	tlVertex[3].tu = 1 * ((tRight + 1) / surW);
	tlVertex[3].tv = 1 * ((tBottom + 1) / surH);

	psSetRenderState(0);

	if (smMaterial[Mat].smTexture[0] != NULL && smMaterial[Mat].smTexture[0]->m_pTexture != NULL)
		psDraw2DImage(smMaterial[Mat].smTexture[0]->m_pTexture, tlVertex);

	return TRUE;
}
int dsDrawTexImageFloat(int Mat, float x, float y, float w, float h, DWORD dwColor, int specular)
{
	int clipLeft;
	int clipTop;
	int clipRight;
	int clipBottom;
	DWORD dwClr;

	clipLeft = 0;
	clipTop = 0;
	clipRight = RESOLUTION_WIDTH;
	clipBottom = RESOLUTION_HEIGHT;

	if ((x >= clipRight) || (y >= clipBottom) || ((x + w) <= clipLeft) || ((y + h) <= clipTop))
		return FALSE;

	float x1 = x;
	float y1 = y;
	float x2 = (x + w);
	float y2 = (y + h);

	D3DTLVERTEX9 tlVertex[4];
	int cnt;

	if (dwColor < 256)
		dwClr = D3DCOLOR_RGBA(255, 255, 255, dwColor);
	else
		dwClr = dwColor;

	for (cnt = 0; cnt < 4; cnt++)
	{
		tlVertex[cnt].rhw = 1.f;
		tlVertex[cnt].color = dwClr;
		tlVertex[cnt].specular = D3DCOLOR_RGBA(specular, specular, specular, 0);
		tlVertex[cnt].sz = 0;
	}

	tlVertex[0].sx = x1;
	tlVertex[0].sy = y1;
	tlVertex[0].tu = 0.0f;
	tlVertex[0].tv = 0.0f;

	tlVertex[1].sx = x1;
	tlVertex[1].sy = y2;
	tlVertex[1].tu = 0.0f;
	tlVertex[1].tv = 1.0f;

	tlVertex[2].sx = x2;
	tlVertex[2].sy = y1;
	tlVertex[2].tu = 1.0f;
	tlVertex[2].tv = 0.0f;

	tlVertex[3].sx = x2;
	tlVertex[3].sy = y2;
	tlVertex[3].tu = 1.0f;
	tlVertex[3].tv = 1.0f;

	psSetRenderState(0);

	if (smMaterial[Mat].smTexture[0] != NULL && smMaterial[Mat].smTexture[0]->m_pTexture != NULL)
		psDraw2DImage(smMaterial[Mat].smTexture[0]->m_pTexture, tlVertex);

	return TRUE;
}

int dsDrawTexImageFloatColor(int Mat, float x, float y, float w, float h, float surW, float surH, float tLeft, float tTop, float tRight, float tBottom, DWORD dwColor)
{
	D3DTLVERTEX9 tlVertex[4];
	int cnt;

	for (cnt = 0; cnt < 4; cnt++)
	{
		tlVertex[cnt].rhw = 1;
		tlVertex[cnt].color = dwColor;
		tlVertex[cnt].specular = D3DCOLOR_RGBA(0, 0, 0, 0);
		tlVertex[cnt].sz = 0;
	}

	tlVertex[0].sx = x;
	tlVertex[0].sy = y;
	tlVertex[0].tu = 1 * (tLeft / surW);
	tlVertex[0].tv = 1 * (tTop / surH);

	tlVertex[1].sx = x;
	tlVertex[1].sy = (y + h);
	tlVertex[1].tu = 1 * (tLeft / surW);
	tlVertex[1].tv = 1 * ((tBottom + 1) / surH);

	tlVertex[2].sx = (x + w);
	tlVertex[2].sy = y;
	tlVertex[2].tu = 1 * ((tRight + 1) / surW);
	tlVertex[2].tv = 1 * (tTop / surH);

	tlVertex[3].sx = (x + w);
	tlVertex[3].sy = (y + h);
	tlVertex[3].tu = 1 * ((tRight + 1) / surW);
	tlVertex[3].tv = 1 * ((tBottom + 1) / surH);

	psSetRenderState(0);

	if (smMaterial[Mat].smTexture[0] != NULL && smMaterial[Mat].smTexture[0]->m_pTexture != NULL)
		psDraw2DImage(smMaterial[Mat].smTexture[0]->m_pTexture, tlVertex);

	return TRUE;
}
//äÖÈ¾BMPÍ¼Æ¬
int dsDrawTexImage(smTEXTUREHANDLE *lpTexture, RECT *DestRect, RECT *SrcRect)
{
	int clipLeft;
	int clipTop;
	int clipRight;
	int clipBottom;

	if (!lpTexture)
		return 0;

	clipLeft = 0;
	clipTop = 0;
	clipRight = RESOLUTION_WIDTH;
	clipBottom = RESOLUTION_HEIGHT;

	if ((DestRect->left >= clipRight) || (DestRect->top >= clipBottom) || (DestRect->right <= clipLeft) || (DestRect->bottom <= clipTop))
		return FALSE;

	float x1 = float(DestRect->left) - 0.5f;
	float y1 = float(DestRect->top) - 0.5f;
	float x2 = float(DestRect->right);
	float y2 = float(DestRect->bottom);

	float texSizeWidth = float(lpTexture->Width);
	float texSizeHeight = float(lpTexture->Height);

	float u1 = float(SrcRect->left) / texSizeWidth;
	float v1 = float(SrcRect->top) / texSizeHeight;
	float u2 = float(SrcRect->right) / texSizeWidth;
	float v2 = float(SrcRect->bottom) / texSizeHeight;

	D3DTLVERTEX9 tlVertex[4];

	for (int i = 0; i < 4; i++)
	{
		tlVertex[i].rhw = 1.f;
		tlVertex[i].color = D3DCOLOR_RGBA(255, 255, 255, 255);
		tlVertex[i].specular = D3DCOLOR_RGBA(0, 0, 0, 255);
		tlVertex[i].sz = 0;
	}

	tlVertex[0].sx = x1;
	tlVertex[0].sy = y1;
	tlVertex[0].tu = u1;
	tlVertex[0].tv = v1;

	tlVertex[1].sx = x1;
	tlVertex[1].sy = y2;
	tlVertex[1].tu = u1;
	tlVertex[1].tv = v2;

	tlVertex[2].sx = x2;
	tlVertex[2].sy = y1;
	tlVertex[2].tu = u2;
	tlVertex[2].tv = v1;

	tlVertex[3].sx = x2;
	tlVertex[3].sy = y2;
	tlVertex[3].tu = u2;
	tlVertex[3].tv = v2;

	psSetRenderState(0);
	psDraw2DImage(lpTexture->m_pTexture, tlVertex);

	return TRUE;
}

int dsDrawTexImage2(smTEXTUREHANDLE *lpTexture, float x, float y, float w, float h, DWORD dwColor)
{
	D3DTLVERTEX9 tlVertex[4];
	int cnt;

	float surW, surH;

	float tLeft, tTop, tRight, tBottom;

	if (!lpTexture)
		return 0;

	tLeft = x;
	tTop = y;
	tRight = w;
	tBottom = h;

	for (cnt = 0; cnt < 4; cnt++)
	{
		tlVertex[cnt].rhw = 1;
		tlVertex[cnt].color = D3DCOLOR_RGBA(255, 255, 255, dwColor);
		tlVertex[cnt].specular = D3DCOLOR_RGBA(0, 0, 0, 255);
		tlVertex[cnt].sz = 0;
	}

	surW = float(lpTexture->Width);
	surH = float(lpTexture->Height);

	tlVertex[0].sx = x;
	tlVertex[0].sy = y;
	tlVertex[0].tu = 1 * (tLeft / surW);
	tlVertex[0].tv = 1 * (tTop / surH);

	tlVertex[1].sx = x;
	tlVertex[1].sy = (y + h);
	tlVertex[1].tu = 1 * (tLeft / surW);
	tlVertex[1].tv = 1 * ((tBottom + 1) / surH);

	tlVertex[2].sx = (x + w);
	tlVertex[2].sy = y;
	tlVertex[2].tu = 1 * ((tRight + 1) / surW);
	tlVertex[2].tv = 1 * (tTop / surH);

	tlVertex[3].sx = (x + w);
	tlVertex[3].sy = (y + h);
	tlVertex[3].tu = 1 * ((tRight + 1) / surW);
	tlVertex[3].tv = 1 * ((tBottom + 1) / surH);

	psSetRenderState(0);
	psDraw2DImage2(lpTexture->m_pTexture, tlVertex);

	return TRUE;
}