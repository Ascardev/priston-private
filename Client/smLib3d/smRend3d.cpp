#include "StdAfx.h"

#define SM_DIST_NEARZ				16
#define SMFLOAT_DIST_NEARZ			(SM_DIST_NEARZ<<FLOATNS)

#define SM_DIST_FARZ				64*25
#define SMFLOAT_DIST_FARZ			(SM_DIST_FARZ<<FLOATNS)

#define SM_DIST_TEXCLIP				64*8
#define SMFLOAT_DIST_TEXCLIP		(SM_DIST_TEXCLIP<<FLOATNS)


#define smCLIP_DETAIL			(fONE*8)
#define smCLIP_DETAIL_SHIFT		(FLOATNS+3)

#define FLOATS_EM				(FLOATNS+3)

static POINT3D	pLight = { fONE / 4 , fONE / 2, -fONE };

extern smCONFIG smConfig;

extern int ReStartFlag;


#define MAX_ITEM2PASS_TEX		16
static  smTEXTUREHANDLE			*s_Item2PassTexHandleBuff[MAX_ITEM2PASS_TEX];
static  char					*s_Item2PassTexName[MAX_ITEM2PASS_TEX] =
{
	"mixS_01.bmp"	,"mixS_02.bmp"	,"mixS_03.bmp"	,"mixS_04.bmp"	,"mixS_05.bmp"	,
	"mixM_01.bmp"	,"mixM_02.bmp"	,"mixM_03.bmp"	,"mixM_04.bmp"	,"mixM_05.bmp"	,"mixM_06.bmp"	,"mixM_07.bmp"	,"mixM_08.bmp"	,"mixM_09.bmp"	,"mixM_10.bmp"	,"mixM_11.bmp"	,
};

int CreateItem2PassTexture(void)
{
	char szImagePath[64] = { 0, };
	for (int i = 0; i < MAX_ITEM2PASS_TEX; i++)
	{
		wsprintf(szImagePath, "Image\\sinImage\\Items\\DropItem\\%s", s_Item2PassTexName[i]);
		s_Item2PassTexHandleBuff[i] = smTexture.Add(szImagePath);

		if (s_Item2PassTexHandleBuff[i] == NULL)
			return FALSE;
	}

	return TRUE;
}

static  int						s_Item2PassTexFormState;
static  smTEXTUREHANDLE			*s_lpItem2PassTexHandle;

void SetItem2PassTexture(int TexHandleNum, int TexFormState)
{
	if (TexHandleNum < 0 || TexHandleNum >= MAX_ITEM2PASS_TEX || s_Item2PassTexHandleBuff[TexHandleNum] == NULL)
	{
		s_lpItem2PassTexHandle = NULL;
		return;
	}

	s_lpItem2PassTexHandle = s_Item2PassTexHandleBuff[TexHandleNum];
	s_Item2PassTexFormState = TexFormState;
}
extern DWORD dwPlayTime;
static void SetBlinkColor(short sColors[4], smFCOLOR BlinkCol, int BlinkStep)
{
	int r = int(BlinkCol.r * 255);
	int g = int(BlinkCol.g * 255);
	int b = int(BlinkCol.b * 255);

	int BlinkTime = 1 << BlinkStep;
	int BlinkMsk = BlinkTime - 1;
	int bTime = dwPlayTime & BlinkMsk;

	if ((dwPlayTime & BlinkTime) == 0)
		bTime = BlinkMsk - bTime;

	sColors[SMC_R] = (bTime * r) >> BlinkStep;
	sColors[SMC_G] = (bTime * g) >> BlinkStep;
	sColors[SMC_B] = (bTime * b) >> BlinkStep;
	sColors[SMC_A] = 0;
}
static int SetBlinkColorVertex(smRENDVERTEX *rv, short sColors[4], BYTE Color[4], BYTE Specular[4])
{
	short BlinkColor[4] = { 0, };
	::CopyMemory(BlinkColor, sColors, sizeof(BlinkColor));

	int z = rv->tz >> FLOATNS;
	if (z > ccDistZMin)
	{
		int lev = ((z - ccDistZMin) << (13 - ShiftMAPCELL_MULT)) >> 8;
		if (lev >= 256)
			return FALSE;

		BlinkColor[SMC_R] -= ((sColors[SMC_R] * lev) >> 8);
		BlinkColor[SMC_G] -= ((sColors[SMC_G] * lev) >> 8);
		BlinkColor[SMC_B] -= ((sColors[SMC_B] * lev) >> 8);
		BlinkColor[SMC_A] -= ((sColors[SMC_A] * lev) >> 8);
	}

	for (int cnt = 0; cnt < 4; cnt++)
	{
		BlinkColor[cnt] += rv->bCol[cnt];
		if (BlinkColor[cnt] > 255)
		{
			short spe = rv->bSpe[cnt] + (BlinkColor[cnt] - 256);
			Color[cnt] = 255;
			if (spe > 255)
				Specular[cnt] = 255;
			else
				Specular[cnt] = (BYTE)spe;
		}
		else
		{
			Color[cnt] = (BYTE)BlinkColor[cnt];
			Specular[cnt] = rv->bSpe[cnt];
		}
	}

	return TRUE;
}
static float s_DxProjection_w;
static float s_DxProjection_h;
static float s_DxProjection_q1;
static float s_DxProjection_q2;
static int   s_CenterX;
static int   s_CenterY;

int			 g_IsDxProjectZoomIn;

float		 g_fZoomInAdd_x;
float		 g_fZoomInAdd_y;
float		 g_fZoomInDiv_x;
float		 g_fZoomInDiv_y;


void SetDxProjection(float radians, int SizeX, int SizeY, float near_z, float far_z)
{
	s_DxProjection_h = float(1.f / tan(radians / 2.f));
	s_DxProjection_w = s_DxProjection_h / (float(SizeX) / float(SizeY));
	s_DxProjection_q1 = far_z / (far_z - near_z);
	s_DxProjection_q2 = -near_z * s_DxProjection_q1;

	s_CenterX = SizeX >> 1;
	s_CenterY = SizeY >> 1;

	float fWinSizeOffset_X = float(SizeX) / 800.f;
	float fWinSizeOffset_Y = float(SizeY) / 600.f;

	g_fZoomInAdd_x = (30.f  * fWinSizeOffset_X);
	g_fZoomInAdd_y = (337.f * fWinSizeOffset_Y);
	g_fZoomInDiv_x = (float(SizeX) / (320.f * fWinSizeOffset_X));
	g_fZoomInDiv_y = (float(SizeY) / (240.f * fWinSizeOffset_Y));
}
void DxProjectionWork(smRENDVERTEX *lpRendVer)
{
	float fx, fy, fz;
	fx = float(lpRendVer->tx) / fONE;
	fy = float(lpRendVer->ty) / fONE;
	fz = float(lpRendVer->tz) / fONE;

	float fx_p, fy_p, fz_p, fw_p;
	fx_p = s_DxProjection_w * fx;
	fy_p = s_DxProjection_h * fy;
	fz_p = (s_DxProjection_q1 * fz) + s_DxProjection_q2;
	fw_p = fz;

	lpRendVer->xy[0] = (1.0f + (fx_p / fw_p)) * s_CenterX;
	lpRendVer->xy[1] = (1.0f - (fy_p / fw_p)) * s_CenterY;
	lpRendVer->zb = fz_p / fw_p;
	lpRendVer->rhw = 1 / fw_p;

	if (g_IsDxProjectZoomIn)
	{
		if (lpRendVer->xy[0] < 0)
			lpRendVer->xy[0] = 0;
		else if (lpRendVer->xy[0] > (s_CenterX << 1))
			lpRendVer->xy[0] = float(s_CenterX << 1);

		if (lpRendVer->xy[1] < 0)
			lpRendVer->xy[1] = 0;
		else if (lpRendVer->xy[1] > (s_CenterY << 1))
			lpRendVer->xy[1] = float(s_CenterY << 1);

		lpRendVer->xy[0] /= g_fZoomInDiv_x;
		lpRendVer->xy[1] /= g_fZoomInDiv_y;
		lpRendVer->xy[0] += g_fZoomInAdd_x;
		lpRendVer->xy[1] += g_fZoomInAdd_y;
	}
	else
	{
		lpRendVer->xy[0] -= (s_CenterX - MidX);
		lpRendVer->xy[1] -= (s_CenterY - MidY);
	}
}
smRENDER3D	smRender;

D3DVALUE	RendBuff[64 * 16384];

DWORD D3DFVF_TEXTURE[9] =
{
	D3DFVF_TLVERTEX0 ,
		D3DFVF_TLVERTEX1 ,
		D3DFVF_TLVERTEX2 ,
		D3DFVF_TLVERTEX3 ,
		D3DFVF_TLVERTEX4 ,
		D3DFVF_TLVERTEX5 ,
		D3DFVF_TLVERTEX6 ,
		D3DFVF_TLVERTEX7 ,
		D3DFVF_TLVERTEX8
};

DWORD D3DTLVERTEX_SIZE[9] =
{
	D3DFVF_TLVERTEX0_SIZE,
		D3DFVF_TLVERTEX1_SIZE,
		D3DFVF_TLVERTEX2_SIZE,
		D3DFVF_TLVERTEX3_SIZE,
		D3DFVF_TLVERTEX4_SIZE,
		D3DFVF_TLVERTEX5_SIZE,
		D3DFVF_TLVERTEX6_SIZE,
		D3DFVF_TLVERTEX7_SIZE,
		D3DFVF_TLVERTEX8_SIZE
};

smRENDER3D::smRENDER3D()
{
	m_dwRenderType = 0;

	m_FogIsRend = FALSE;
	m_FogMode = FALSE;
	m_fFogStNum = 400.f;
	m_fFogEndNum = 3000.f;
	m_dwFogColor = 0xC0C0C0C0;

	nRendObjLight = 0;

	CameraPosiMask = FALSE;
	nRendLight = 0;

	SMSHIFT_PERSPECTIVE_WIDTH = RENDCLIP_DEFAULT_SHIFT_PERSPECTIVE_WIDTH;
	SMMULT_PERSPECTIVE_HEIGHT = RENDCLIP_DEFAULT_MULT_PERSPECTIVE_HEIGHT;

	ObjectVertexScale = 0;
	DistortionMesh = 0;

	m_GameFieldView = 0;
	m_GameFieldViewStep = 0;

	RendVertex = NULL;
	RendFace = NULL;

}

smRENDER3D::~smRENDER3D()
{
	if (RendVertex)
	{
		delete[] RendVertex;
		RendVertex = NULL;
	}

	if (RendFace)
	{
		delete[] RendFace;
		RendFace = NULL;
	}
}
void smRENDER3D::CreateRenderBuff(int FieldViewType)
{
	if (RendVertex)
	{
		delete[] RendVertex;
		RendVertex = NULL;
	}

	if (RendFace)
	{
		delete[] RendFace;
		RendFace = NULL;
	}
	m_GameFieldView = FieldViewType;
	if (m_GameFieldView)
	{
		RendVertex = new smRENDVERTEX[RENDER_VERTEX_MAX * 2];
		ZeroMemory(RendVertex, sizeof(smRENDVERTEX) * RENDER_VERTEX_MAX * 2);

		RendFace = new smRENDFACE[RENDER_VERTEX_MAX * 2];
		ZeroMemory(RendFace, sizeof(smRENDFACE) * RENDER_VERTEX_MAX * 2);
	}
	else
	{
		RendVertex = new smRENDVERTEX[RENDER_VERTEX_MAX];
		ZeroMemory(RendVertex, sizeof(smRENDVERTEX) * RENDER_VERTEX_MAX);

		RendFace = new smRENDFACE[RENDER_FACE_MAX];
		ZeroMemory(RendFace, sizeof(smRENDFACE) * RENDER_FACE_MAX);
	}
}


void smRENDER3D::SetGameFieldViewStep(void)
{
	if (m_GameFieldView != 0)
	{
		ViewPointLen = (38 + m_GameFieldViewStep) * SizeMAPCELL;
		ccDistZMin = ViewPointLen - (20 + (m_GameFieldViewStep / 4)) * SizeMAPCELL;
	}
}
// ��ȡ3D��Ӧ��2Dͼ������
int smRENDER3D::GetRect2D(int x, int y, int z, int width, int height, RECT *Rect, POINT *Pos)
{
	int w, h;
	int cnt;
	POINT3D p[3];

	auto sPosition = Point3D(x, y, z);

	GetCameraCoord64(sPosition);

	w = width >> 1;
	h = height >> 1;

	p[0].x = sPosition.iX - w;
	p[1].x = sPosition.iX + w;
	p[0].y = sPosition.iY - h;
	p[1].y = sPosition.iY + h;
	p[0].z = sPosition.iZ;
	p[1].z = sPosition.iZ;

	p[2].x = sPosition.iX;
	p[2].y = sPosition.iY;
	p[2].z = sPosition.iZ;

	if (sPosition.iZ <= 0)
		return NULL;

	int mviewdistZ = (int)RESOLUTION_HEIGHT * 4 / 3;

	for (cnt = 0; cnt < 3; cnt++)
	{
		p[cnt].x = MidX + (p[cnt].x * mviewdistZ) / sPosition.iZ;
		p[cnt].y = MidY - (p[cnt].y * mviewdistZ) / sPosition.iZ;

	}

	Rect->top = p[1].y;
	Rect->bottom = p[0].y;

	Rect->left = p[0].x;
	Rect->right = p[1].x;

	if (Pos)
	{
		Pos->x = p[2].x;
		Pos->y = p[2].y;
	}

	return sPosition.iZ;
}

int smRENDER3D::GetDepthZ(int x, int y, int z)
{
	int rz;

	x -= m_sCameraPosition.iX;
	y -= m_sCameraPosition.iY;
	z -= m_sCameraPosition.iZ;

	rz = x * mCamera._13 +
		y * mCamera._23 +
		z * mCamera._33;

	return (rz >> FLOATS_EM);
}
int smRENDER3D::SetCameraPosi(int x, int y, int z, int angX, int angY, int angZ)
{
	smEMATRIX	rX, rY, rZ, tm1;

	m_sCameraPosition = Point3D(x, y, z);

	CameraAngX = angX;
	CameraAngY = angY;
	CameraAngZ = angZ;

	if (CameraPosiMask)
		return FALSE;

	smEIdentityMatrix(rX);
	smEIdentityMatrix(rY);
	smEIdentityMatrix(rZ);

	smERotateXMatrix(rX, -angX & ANGCLIP);
	smERotateYMatrix(rY, -angY & ANGCLIP);
	smERotateZMatrix(rZ, -angZ & ANGCLIP);

	smEMatrixMult(tm1, rY, rX);
	smEMatrixMult((smEMATRIX &)mCamera, tm1, rZ);

	smMatrixShift(mCamera, 4);


	return TRUE;
}
int smRENDER3D::SetCameraPosi(int x, int y, int z, smEMATRIX *lpeMatrix)
{
	m_sCameraPosition = Point3D(x, y, z);

	if (CameraPosiMask)
		return FALSE;

	memcpy((smEMATRIX *)&mCamera, lpeMatrix, sizeof(smEMATRIX));
	smMatrixShift(mCamera, 4);


	return TRUE;
}

int	smRENDER3D::AddDynamicLight(int type, int x, int y, int z, int r, int g, int b, int a, int Range)
{
	if (type & SMLIGHT_TYPE_OBJ)
	{
		if (nRendObjLight < REND_LIGHT_MAX)
		{
			smRendObjLight[nRendObjLight].x = x;
			smRendObjLight[nRendObjLight].y = y;
			smRendObjLight[nRendObjLight].z = z;

			smRendObjLight[nRendObjLight].r = r;
			smRendObjLight[nRendObjLight].g = g;
			smRendObjLight[nRendObjLight].b = b;
			smRendObjLight[nRendObjLight].a = a;

			smRendObjLight[nRendObjLight].Range = Range;
			smRendObjLight[nRendObjLight].dRange = (Range >> 8) * (Range >> 8);

			auto sPosition = Point3D(x, y, z);

			GetCameraCoord64(sPosition);

			smRendObjLight[nRendObjLight].rx = sPosition.iX;
			smRendObjLight[nRendObjLight].ry = sPosition.iY;
			smRendObjLight[nRendObjLight].rz = sPosition.iZ;

			nRendObjLight++;

			return TRUE;
		}
	}
	else
	{
		if (nRendLight < REND_LIGHT_MAX)
		{
			smRendLight[nRendLight].x = x;
			smRendLight[nRendLight].y = y;
			smRendLight[nRendLight].z = z;

			smRendLight[nRendLight].r = r;
			smRendLight[nRendLight].g = g;
			smRendLight[nRendLight].b = b;
			smRendLight[nRendLight].a = a;

			smRendLight[nRendLight].Range = Range;
			smRendLight[nRendLight].dRange = (Range >> 8) * (Range >> 8);

			auto sPosition = Point3D(x, y, z);

			GetCameraCoord64(sPosition);

			smRendLight[nRendLight].rx = sPosition.iX;
			smRendLight[nRendLight].ry = sPosition.iY;
			smRendLight[nRendLight].rz = sPosition.iZ;

			nRendLight++;

			return TRUE;
		}
	}

	return FALSE;
}

int smRENDER3D::ClearObjLight()
{
	bApplyRendObjLight = 0;
	nRendObjLight = 0;
	return TRUE;
}

int	smRENDER3D::AddDynamicLight(int x, int y, int z, int r, int g, int b, int a, int Range)
{
	int dRange;

	if (nRendLight < REND_LIGHT_MAX)
	{
		smRendLight[nRendLight].x = x;
		smRendLight[nRendLight].y = y;
		smRendLight[nRendLight].z = z;

		smRendLight[nRendLight].r = r;
		smRendLight[nRendLight].g = g;
		smRendLight[nRendLight].b = b;
		smRendLight[nRendLight].a = a;

		smRendLight[nRendLight].Range = Range;
		dRange = Range >> FLOATNS;
		smRendLight[nRendLight].dRange = dRange * dRange;

		auto sPosition = Point3D(x, y, z);

		GetCameraCoord64(sPosition);

		smRendLight[nRendLight].rx = sPosition.iX;
		smRendLight[nRendLight].ry = sPosition.iY;
		smRendLight[nRendLight].rz = sPosition.iZ;

		nRendLight++;

		return TRUE;
	}

	return FALSE;
}
int smRENDER3D::ClearLight()
{
	nRendLight = 0;

	return TRUE;
}
int smRENDER3D::OpenCameraPosi(int x, int y, int z, smEMATRIX *lpeMatrix)
{
	memcpy((smEMATRIX *)&mCamera, lpeMatrix, sizeof(smEMATRIX));
	smMatrixShift(mCamera, 4);

	m_sCameraPosition = Point3D(x, y, z);

	CameraPosiMask = TRUE;

	return TRUE;
}
int smRENDER3D::CloseCameraPosi()
{
	CameraPosiMask = FALSE;
	return TRUE;
}

int smRENDER3D::InitStageMesh(smSTAGE_VERTEX *StageVertex, DWORD sum)
{
	nTempTexLink = 0;

	nRendVertex = 0;							//������ �� ���ؽ� ��
	nRendFace = 0;							//������ �� ���̽� ��

	RMatListCnt = 0;							//��Ʈ���� ���� ī���� �ʱ�ȭ
	RMatListRearCnt = nMaterial - 1;					//��Ʈ���� ���� ī���� �ʱ�ȭ


	Vertex = StageVertex;							//StageVertex ������

	ClipStates = (SMCLIP_NEARZ | SMCLIP_FARZ | SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM);

	SumCount = sum;

	ZeroMemory(RendMatrial, sizeof(smRENDMATRIAL) * nMaterial);

	RendStatTime = GetCurrentTime();

	return TRUE;
}

int smRENDER3D::Init()
{
	return InitStageMesh(0, 0);
}
BOOL smRENDER3D::GetCameraCoord(Point3D &sPosition, BOOL b)
{
	sPosition.iX -= m_sCameraPosition.iX;
	sPosition.iY -= m_sCameraPosition.iY;
	sPosition.iZ -= m_sCameraPosition.iZ;

	int iX = (sPosition.iX * mCamera._11 + sPosition.iY * mCamera._21 + sPosition.iZ * mCamera._31) >> FLOATS_EM;
	int iY = (sPosition.iX * mCamera._12 + sPosition.iY * mCamera._22 + sPosition.iZ * mCamera._32) >> FLOATS_EM;
	int iZ = (sPosition.iX * mCamera._13 + sPosition.iY * mCamera._23 + sPosition.iZ * mCamera._33) >> FLOATS_EM;

	sPosition = Point3D(iX, iY, iZ);

	b ? sPosition.iZ -= 24 * 256 : 0;

	return sPosition.iZ < SMFLOAT_DIST_NEARZ ? FALSE : TRUE;
}
BOOL smRENDER3D::GetCameraCoord64(Point3D &sPosition, BOOL b)
{
	sPosition -= m_sCameraPosition;

	INT64 iX_ = sPosition.iX;
	INT64 iY_ = sPosition.iY;
	INT64 iZ_ = sPosition.iZ;

	INT64 iX = ((iX_ * mCamera._11) >> FLOATS_EM) + ((iY_ * mCamera._21) >> FLOATS_EM) + ((iZ_ * mCamera._31) >> FLOATS_EM);
	INT64 iY = ((iX_ * mCamera._12) >> FLOATS_EM) + ((iY_ * mCamera._22) >> FLOATS_EM) + ((iZ_ * mCamera._32) >> FLOATS_EM);
	INT64 iZ = ((iX_ * mCamera._13) >> FLOATS_EM) + ((iY_ * mCamera._23) >> FLOATS_EM) + ((iZ_ * mCamera._33) >> FLOATS_EM);

	sPosition = Point3D((int)iX, (int)iY, (int)iZ);

	b ? sPosition.iZ -= 24 * 256 : 0;

	return sPosition.iZ >= SMFLOAT_DIST_NEARZ ? TRUE : FALSE;
}
DWORD smRENDER3D::GetClipStatus(Point3D sPosition)
{
	DWORD dwClip = 0;

	dwClip |= sPosition.iZ < SMFLOAT_DIST_NEARZ ? SMCLIP_NEARZ : 0;
	dwClip |= sPosition.iZ > SMFLOAT_DIST_FARZ ? SMCLIP_FARZ : 0;

	int iX = abs(sPosition.iX) << SMSHIFT_PERSPECTIVE_WIDTH;

	if (sPosition.iX < 0)
	{
		dwClip |= sPosition.iZ < iX ? SMCLIP_LEFT : 0;
	}
	else
	{
		dwClip |= sPosition.iZ < iX ? SMCLIP_RIGHT : 0;
	}

	int iY = (abs(sPosition.iY) * SMMULT_PERSPECTIVE_HEIGHT) >> FLOATNS;

	if (sPosition.iY < 0)
	{
		dwClip |= sPosition.iZ < iY ? SMCLIP_BOTTOM : 0;
	}
	else
	{
		dwClip |= sPosition.iZ < iY ? SMCLIP_TOP : 0;
	}

	return dwClip;
}
int smRENDER3D::SetClipStates(DWORD States)
{
	ClipStates = States;
	return TRUE;
}
int smRENDER3D::SetMaterialGroup(smMATERIAL_GROUP *MatGroup)
{
	smRendMaterial = MatGroup->smMaterial;
	nMaterial = MatGroup->MaxMaterial;
	RMatListRearCnt = nMaterial - 1;

	return TRUE;
}
int smRENDER3D::AddRendTempTexLink(smRENDFACE *lpRendFace, DWORD *hTex, float u0, float v0, float u1, float v1, float u2, float v2)
{
	int cnt;
	smTEXLINK	*tl;

	TempTexLink[nTempTexLink].u[0] = u0;
	TempTexLink[nTempTexLink].v[0] = v0;
	TempTexLink[nTempTexLink].u[1] = u1;
	TempTexLink[nTempTexLink].v[1] = v1;
	TempTexLink[nTempTexLink].u[2] = u2;
	TempTexLink[nTempTexLink].v[2] = v2;
	TempTexLink[nTempTexLink].hTexture = 0;
	TempTexLink[nTempTexLink].NextTex = 0;

	if (!lpRendFace->lpTexLink) {
		//������ �ؽ�����ǥ�� ���
		lpRendFace->lpTexLink = &TempTexLink[nTempTexLink];
	}
	else {
		//�̹� ������ִ� ��ǥ�� �ִ°��
		tl = lpRendFace->lpTexLink;

		for (cnt = 0; cnt < 8; cnt++) {
			if (!tl->NextTex) {
				//���������� ����� ��ǥ�� ã�� ����
				tl->NextTex = &TempTexLink[nTempTexLink];
				break;
			}
			else {
				//���� ��ǥ�� �ѱ�
				tl = tl->NextTex;
			}

		}
	}

	nTempTexLink++;

	return nTempTexLink - 1;
}


//�������� ���ؽ��� ������ ���ؽ� �߰� ( ���� ��ǥ �ҽ� ��� )
smRENDVERTEX *smRENDER3D::AddStageVertex(smSTAGE_VERTEX *sv, smMATERIAL *lpMaterial)
{
	int rx, rz; //,ry 
	int x, y, z;
	int ShiftMesh;

	DWORD *dwColor, *dwDefColor;


	int ttCnt, ttFlag;

	if (lpMaterial->WindMeshBottom && (lpMaterial->UseState & sMATS_SCRIPT_BLINK_COLOR) == 0)
	{
		switch (lpMaterial->WindMeshBottom & 0x7FF)
		{

		case sMATS_SCRIPT_WINDX1:
			ttCnt = (RendStatTime >> 2) & 0xFF;
			ttFlag = (RendStatTime >> 10) & 1;

			if (!ttFlag) ttCnt = 255 - ttCnt;
			ShiftMesh = (GetCos[ttCnt + 256]) >> 5;

			x = (sv->x - ShiftMesh);
			y = sv->y;
			z = sv->z;
			break;

		case sMATS_SCRIPT_WINDZ1:
			ttCnt = (RendStatTime >> 2) & 0xFF;
			ttFlag = (RendStatTime >> 10) & 1;

			if (!ttFlag)
				ttCnt = 255 - ttCnt;
			ShiftMesh = (GetCos[ttCnt + 256]) >> 5;

			x = sv->x;
			y = sv->y;
			z = (sv->z - ShiftMesh);
			break;

		case sMATS_SCRIPT_WINDX2:
			ttCnt = (RendStatTime >> 2) & 0xFF;
			ttFlag = (RendStatTime >> 10) & 1;

			if (!ttFlag)
				ttCnt = 255 - ttCnt;
			ShiftMesh = (GetCos[ttCnt + 256]) >> 3;

			x = (sv->x - ShiftMesh);
			y = sv->y;
			z = sv->z;
			break;

		case sMATS_SCRIPT_WINDZ2:
			ttCnt = (RendStatTime >> 2) & 0xFF;
			ttFlag = (RendStatTime >> 10) & 1;

			if (!ttFlag)
				ttCnt = 255 - ttCnt;
			ShiftMesh = (GetCos[ttCnt + 256]) >> 3;

			x = sv->x;
			y = sv->y;
			z = (sv->z - ShiftMesh);
			break;

		case sMATS_SCRIPT_WATER:
			x = sv->x;
			y = sv->y;
			z = sv->z;

			rx = (((x << 3) + RendStatTime) >> 1);
			rz = (((z << 3) + RendStatTime) >> 1);

			rx = GetSin[rx&ANGCLIP];
			rz = GetSin[rz&ANGCLIP];

			x += rx >> 4;
			z += rz >> 4;
			break;
		}
	}
	else
	{
		x = sv->x;
		y = sv->y;
		z = sv->z;
	}

	auto sPosition = Point3D(x, y, z);

	GetCameraCoord64(sPosition);

	RendVertex[nRendVertex].tx = sPosition.iX;
	RendVertex[nRendVertex].ty = sPosition.iY;
	RendVertex[nRendVertex].tz = sPosition.iZ;
	RendVertex[nRendVertex].lpSourceVertex = sv;
	RendVertex[nRendVertex].ClipStatus = GetClipStatus(sPosition);

	dwColor = (DWORD*)RendVertex[nRendVertex].sLight;
	dwDefColor = (DWORD *)sv->sDef_Color;

	*dwColor++ = *dwDefColor++;
	*dwColor = *dwDefColor;

	nRendVertex++;

	return &RendVertex[nRendVertex - 1];
}


//�������� ���̽��� ������ ���̽� �߰�
smRENDFACE *smRENDER3D::AddStageFace(smSTAGE_FACE *face)
{
	int cnt;
	smSTAGE_VERTEX *sv;
	DWORD ClipStatus;
	smMATERIAL *lpMaterial;

	if (SumCount != face->sum)
	{
		ClipStatus = 0;
		lpMaterial = &smRendMaterial[face->Vertex[3]];
		face->sum = SumCount;

		if (lpMaterial->UseState & dwMatDispMask)
			return NULL;

		for (cnt = 0; cnt < 3; cnt++)
		{
			sv = &Vertex[face->Vertex[cnt]];
			if (sv->sum != SumCount)
			{
				sv->sum = SumCount;
				sv->lpRendVertex = AddStageVertex(sv, lpMaterial);
			}
			RendFace[nRendFace].lpRendVertex[cnt] = sv->lpRendVertex;
			ClipStatus |= sv->lpRendVertex->ClipStatus;			//Ŭ���� ���� ����
		}

		RendFace[nRendFace].Matrial = face->Vertex[3];
		RendFace[nRendFace].lpTexLink = face->lpTexLink;
		RendFace[nRendFace].ClipStatus = ClipStatus;

		nRendFace++;
		return &RendFace[nRendFace - 1];
	}

	return NULL;
}

smRENDVERTEX *smRENDER3D::AddObjectVertex(smVERTEX *sv, DWORD dwObjHead)
{
	auto sPosition = Point3D(sv->x, sv->y, sv->z);

	if (ObjectVertexScale)
	{
		sPosition = sPosition * ObjectVertexScale / 256;
	}

	GetCameraCoord64(sPosition);

	if (DistortionMesh)
	{
		int iX = GetSin[((sPosition.iX >> 1) + RendStatTime) & ANGCLIP];
		int iY = GetSin[((sPosition.iY >> 1) + RendStatTime) & ANGCLIP];
		int iZ = GetCos[((sPosition.iZ >> 1) + RendStatTime) & ANGCLIP];

		sPosition += Point3D(iX, iY, iZ) >> 7;
	}

	RendVertex[nRendVertex].tx = sPosition.iX;
	RendVertex[nRendVertex].ty = sPosition.iY;
	RendVertex[nRendVertex].tz = sPosition.iZ;
	RendVertex[nRendVertex].ClipStatus = GetClipStatus(sPosition);


	int gShade;
	DWORD r, g, b;
	short *sColor;

	if (dwObjHead & OBJ_HEAD_TYPE_NEW_NORMAL)
	{
		sPosition = Point3D(sv->nx, sv->ny, sv->nz);

		if (ObjectVertexScale)
		{
			sPosition = sPosition * ObjectVertexScale / 256;
		}

		GetCameraCoord64(sPosition);

		RendVertex[nRendVertex].nx = sPosition.iX;
		RendVertex[nRendVertex].ny = sPosition.iY;
		RendVertex[nRendVertex].nz = sPosition.iZ;
	}
	else
	{
		RendVertex[nRendVertex].nx = 0;
		RendVertex[nRendVertex].ny = 0;
		RendVertex[nRendVertex].nz = 0;
	}

	if (dwObjHead & OBJ_HEAD_TYPE_NEW_NORMAL)
	{
		sPosition = Point3D(sv->nx, sv->ny, sv->nz) - Point3D(sv->x, sv->y, sv->z);

		gShade = ((sPosition.iX * pLight.x) + (sPosition.iY * pLight.y) + (sPosition.iZ * pLight.z)) >> FLOATNS;

		gShade = abs(gShade);
		gShade = gShade / 140;												//CONTRAST
		r = g = b = DEFAULT_BRIGHT - 50;										// BRIGHT

		r += gShade;
		g += int(gShade * 0.93f);
		b += int(gShade * 0.84f);
	}
	else
	{
		gShade = ((sv->nx * pLight.x) + (sv->ny * pLight.y) + (sv->nz * pLight.z)) >> FLOATNS;
		gShade /= DEFAULT_CONTRAST + 64;										//CONTRAST
		gShade += DEFAULT_BRIGHT + 48;										//BRIGHT

		r = g = b = gShade;
	}

	sColor = RendVertex[nRendVertex].sLight;
	*sColor++ = (short)r;
	*sColor++ = (short)g;
	*sColor++ = (short)b;
	*sColor = 255;

	nRendVertex++;

	return &RendVertex[nRendVertex - 1];
}

//������Ʈ ���̽��� ������ ���̽� �߰�
smRENDFACE *smRENDER3D::AddObjectFace(smFACE *face)
{
	int cnt;
	smRENDVERTEX *sv;
	DWORD ClipStatus;

	ClipStatus = 0;

	for (cnt = 0; cnt < 3; cnt++)
	{
		sv = &RendVertex[face->v[cnt]];
		RendFace[nRendFace].lpRendVertex[cnt] = sv;
		ClipStatus |= sv->ClipStatus;					//Ŭ���� ���� ����
	}

	RendFace[nRendFace].Matrial = face->v[3];		//��Ʈ���� ����
	RendFace[nRendFace].lpTexLink = face->lpTexLink;	//�ؽ�����ǥ���� ������ ����
	RendFace[nRendFace].ClipStatus = ClipStatus;

	nRendFace++;
	return &RendFace[nRendFace - 1];

	return NULL;
}



//2D �̹��� ������Ʈ �߰�
smRENDFACE *smRENDER3D::AddFace2D(smFACE2D *face)
{
	//int x, y, z;
	int width, height;

	smRENDVERTEX *v[4];
	smRENDFACE	 *rf;
	short		sColor[4];

	sColor[SMC_A] = face->Transparency;
	sColor[SMC_R] = face->r;
	sColor[SMC_G] = face->g;
	sColor[SMC_B] = face->b;

	auto sPosition = Point3D(face->x, face->y, face->z);

	if (!GetCameraCoord64(sPosition, TRUE))
		return nullptr;

	width = face->width >> 1;
	height = face->height >> 1;

	//������ ���ؽ� �߰� ( ��ǥ ���� �Է� )

	v[0] = AddRendVertex(sPosition.iX - width, sPosition.iY - height, sPosition.iZ, sColor);
	v[1] = AddRendVertex(sPosition.iX + width, sPosition.iY - height, sPosition.iZ, sColor);
	v[2] = AddRendVertex(sPosition.iX - width, sPosition.iY + height, sPosition.iZ, sColor);
	v[3] = AddRendVertex(sPosition.iX + width, sPosition.iY + height, sPosition.iZ, sColor);

	//ù��° ������ ( 1 - 2 - 3 );
	rf = &RendFace[nRendFace++];
	rf->lpRendVertex[0] = v[0];
	rf->lpRendVertex[1] = v[1];
	rf->lpRendVertex[2] = v[2];
	rf->Matrial = face->MatNum;		//��Ʈ���� ����
	rf->ClipStatus = v[0]->ClipStatus | v[1]->ClipStatus | v[2]->ClipStatus;
	rf->lpTexLink = 0;

	//�ؽ��� ����
	AddRendTempTexLink(rf, 0, face->TexRect.left, face->TexRect.bottom,
		face->TexRect.right, face->TexRect.bottom,
		face->TexRect.left, face->TexRect.top);


	//�ι�° ������ ( 2 - 4 - 3 );
	rf = &RendFace[nRendFace++];
	rf->lpRendVertex[0] = v[1];
	rf->lpRendVertex[1] = v[3];
	rf->lpRendVertex[2] = v[2];
	rf->Matrial = face->MatNum;		//��Ʈ���� ����
	rf->ClipStatus = v[1]->ClipStatus | v[2]->ClipStatus | v[3]->ClipStatus;
	rf->lpTexLink = 0;

	//�ؽ��� ����
	AddRendTempTexLink(rf, 0, face->TexRect.right, face->TexRect.bottom,
		face->TexRect.right, face->TexRect.top,
		face->TexRect.left, face->TexRect.top);

	return &RendFace[nRendFace - 1];
}

smRENDFACE *smRENDER3D::AddFace2D(smFACE2D *face, int angle)
{
	//int x, y, z;

	int width, height;

	smRENDVERTEX *v[4];
	smRENDFACE	 *rf;
	short		sColor[4];

	sColor[SMC_A] = face->Transparency;
	sColor[SMC_R] = face->r;
	sColor[SMC_G] = face->g;
	sColor[SMC_B] = face->b;

	auto sPosition = Point3D(face->x, face->y, face->z);

	if (!GetCameraCoord64(sPosition, TRUE))
		return nullptr;

	width = face->width >> 1;
	height = face->height >> 1;


	//ȸ�� ����
	int		ex[4], ey[4];
	int		mx, my;
	int		sin, cos;

	sin = GetSin[angle&ANGCLIP] >> FLOATNS;
	cos = GetCos[angle&ANGCLIP] >> FLOATNS;

	mx = -width;	my = -height;
	ex[0] = (mx * cos - my * sin) >> FLOATNS;
	ey[0] = (mx * sin + my * cos) >> FLOATNS;

	mx = width;	my = -height;
	ex[1] = (mx * cos - my * sin) >> FLOATNS;
	ey[1] = (mx * sin + my * cos) >> FLOATNS;

	mx = -width;	my = +height;
	ex[2] = (mx * cos - my * sin) >> FLOATNS;
	ey[2] = (mx * sin + my * cos) >> FLOATNS;

	mx = width;	my = height;
	ex[3] = (mx * cos - my * sin) >> FLOATNS;
	ey[3] = (mx * sin + my * cos) >> FLOATNS;


	//������ ���ؽ� �߰� ( ��ǥ ���� �Է� )
	v[0] = AddRendVertex(sPosition.iX + ex[0], sPosition.iY + ey[0], sPosition.iZ, sColor);
	v[1] = AddRendVertex(sPosition.iX + ex[1], sPosition.iY + ey[1], sPosition.iZ, sColor);
	v[2] = AddRendVertex(sPosition.iX + ex[2], sPosition.iY + ey[2], sPosition.iZ, sColor);
	v[3] = AddRendVertex(sPosition.iX + ex[3], sPosition.iY + ey[3], sPosition.iZ, sColor);

	//ù��° ������ ( 1 - 2 - 3 );
	rf = &RendFace[nRendFace++];
	rf->lpRendVertex[0] = v[0];
	rf->lpRendVertex[1] = v[1];
	rf->lpRendVertex[2] = v[2];
	rf->Matrial = face->MatNum;		//��Ʈ���� ����
	rf->ClipStatus = v[0]->ClipStatus | v[1]->ClipStatus | v[2]->ClipStatus;
	rf->lpTexLink = 0;

	//�ؽ��� ����
	AddRendTempTexLink(rf, 0, face->TexRect.left, face->TexRect.bottom,
		face->TexRect.right, face->TexRect.bottom,
		face->TexRect.left, face->TexRect.top);


	//�ι�° ������ ( 2 - 4 - 3 );
	rf = &RendFace[nRendFace++];
	rf->lpRendVertex[0] = v[1];
	rf->lpRendVertex[1] = v[3];
	rf->lpRendVertex[2] = v[2];
	rf->Matrial = face->MatNum;		//��Ʈ���� ����
	rf->ClipStatus = v[1]->ClipStatus | v[2]->ClipStatus | v[3]->ClipStatus;
	rf->lpTexLink = 0;

	//�ؽ��� ����
	AddRendTempTexLink(rf, 0, face->TexRect.right, face->TexRect.bottom,
		face->TexRect.right, face->TexRect.top,
		face->TexRect.left, face->TexRect.top);


	return &RendFace[nRendFace - 1];
}


//2D �̹��� ������Ʈ �߰� ( ȭ����ǥ�� ���� �׸��� )
smRENDFACE *smRENDER3D::AddFace2D_Direct(smFACE2D *face)
{
	int cnt;
	int x1, x2, y1, y2;

	smRENDVERTEX *v[4];
	smRENDFACE	 *rf;
	DWORD		dwColor;

	dwColor = 0xFFFFFFFF;
	((BYTE *)&dwColor)[SMC_A] = face->Transparency;

	for (cnt = 0; cnt < 4; cnt++)
	{
		v[cnt] = &RendVertex[nRendVertex++];
		v[cnt]->zb = smConvZ3D(float(face->z));
		v[cnt]->rhw = 1;
		v[cnt]->ClipStatus = 0;
		((DWORD *)v[cnt]->bCol)[0] = dwColor;
		((DWORD *)v[cnt]->bSpe)[0] = 0;
	}

	x1 = face->x; x2 = x1 + face->width;
	y1 = face->y; y2 = y1 + face->height;

	v[0]->xy[0] = (float)x1;
	v[0]->xy[1] = (float)y1;
	v[1]->xy[0] = (float)x2;
	v[1]->xy[1] = (float)y1;
	v[2]->xy[0] = (float)x1;
	v[2]->xy[1] = (float)y2;
	v[3]->xy[0] = (float)x2;
	v[3]->xy[1] = (float)y2;

	//ù��° ������ ( 1 - 2 - 3 );
	rf = &RendFace[nRendFace++];
	rf->lpRendVertex[0] = v[0];
	rf->lpRendVertex[1] = v[1];
	rf->lpRendVertex[2] = v[2];
	rf->Matrial = face->MatNum;		//��Ʈ���� ����
	rf->ClipStatus = 0;
	rf->lpTexLink = 0;

	//�ؽ��� ����
	AddRendTempTexLink(rf, 0, face->TexRect.left, face->TexRect.top,
		face->TexRect.right, face->TexRect.top,
		face->TexRect.left, face->TexRect.bottom);


	//�ι�° ������ ( 2 - 4 - 3 );
	rf = &RendFace[nRendFace++];
	rf->lpRendVertex[0] = v[1];
	rf->lpRendVertex[1] = v[3];
	rf->lpRendVertex[2] = v[2];
	rf->Matrial = face->MatNum;		//��Ʈ���� ����
	rf->ClipStatus = 0;
	rf->lpTexLink = 0;

	//�ؽ��� ����
	AddRendTempTexLink(rf, 0, face->TexRect.right, face->TexRect.top,
		face->TexRect.right, face->TexRect.bottom,
		face->TexRect.left, face->TexRect.bottom);


	return &RendFace[nRendFace - 1];
}


smRENDVERTEX *smRENDER3D::AddRendVertex(int x, int y, int z, short *pLight, int nx, int ny, int nz)
{
	RendVertex[nRendVertex].tx = x;
	RendVertex[nRendVertex].ty = y;
	RendVertex[nRendVertex].tz = z;

	RendVertex[nRendVertex].nx = nx;
	RendVertex[nRendVertex].ny = ny;
	RendVertex[nRendVertex].nz = nz;

	RendVertex[nRendVertex].ClipStatus = GetClipStatus(Point3D(x, y, z));

	DWORD *dwLight, *dwpLight;

	dwLight = (DWORD *)RendVertex[nRendVertex].sLight;
	dwpLight = (DWORD *)pLight;

	*dwLight++ = *dwpLight++;
	*dwLight = *dwpLight;

	nRendVertex++;

	return &RendVertex[nRendVertex - 1];
}


//������ ���̽� �߰� ( ���ؽ� ������ ���� �Է� )
smRENDFACE *smRENDER3D::AddRendFace(smRENDVERTEX *v0, smRENDVERTEX *v1, smRENDVERTEX *v2, DWORD matrial, smTEXLINK *lpTexLink)
{
	RendFace[nRendFace].lpRendVertex[0] = v0;
	RendFace[nRendFace].lpRendVertex[1] = v1;
	RendFace[nRendFace].lpRendVertex[2] = v2;

	RendFace[nRendFace].Matrial = matrial;			//��Ʈ���� ����
	RendFace[nRendFace].lpTexLink = lpTexLink;		//�ؽ�����ǥ���� ������ ����

	RendFace[nRendFace].ClipStatus = v0->ClipStatus | v1->ClipStatus | v2->ClipStatus;

	nRendFace++;
	return &RendFace[nRendFace - 1];
}

//���̽� ���̵尪 ���� ( DotProduct )
int smRENDER3D::GetFaceSide(smRENDFACE *rendface)
{
	smRENDVERTEX	*v0;
	smRENDVERTEX	*v1;
	smRENDVERTEX	*v2;

	v0 = rendface->lpRendVertex[0];
	v1 = rendface->lpRendVertex[1];
	v2 = rendface->lpRendVertex[2];

	int temp1, temp2, temp3;
	int tempX, tempY, tempZ;
	int tempA, tempB, tempC;

	tempX = v1->tx - v0->tx;
	tempY = v1->ty - v0->ty;
	tempZ = v1->tz - v0->tz;

	tempA = v2->tx - v0->tx;
	tempB = v2->ty - v0->ty;
	tempC = v2->tz - v0->tz;

	temp1 = ((tempY * tempC) - (tempZ * tempB)) >> FLOATNS;
	temp2 = ((tempX * tempC) - (tempZ * tempA)) >> FLOATNS;
	temp3 = ((tempX * tempB) - (tempY * tempA)) >> FLOATNS;

	return temp3;
}



// ������ ���̽��� Ŭ���� ( dwClipMode�� SMCLIP_[����] ) 
int smRENDER3D::AddRendFaceClip(smRENDFACE *rendface, DWORD dwClipMode)
{

	smRENDVERTEX *v[3];
	smRENDVERTEX *cv[2];			//���� ���ؽ�
	float		 fMultPoint[2];
	float		 u0, v0, u1, v1;

	int cnt;
	int StatsClips[3];
	int midcnt, nexcnt, lascnt;

	smTEXLINK	*texLink;
	smRENDFACE	*rFace[2];

	rendface->ClipStatus |= SMCLIP_DISPLAYOUT;

	StatsClips[0] = rendface->lpRendVertex[0]->ClipStatus & dwClipMode;
	StatsClips[1] = rendface->lpRendVertex[1]->ClipStatus & dwClipMode;
	StatsClips[2] = rendface->lpRendVertex[2]->ClipStatus & dwClipMode;

	if (StatsClips[0] && StatsClips[1] && StatsClips[2])
		return NULL;

	v[0] = rendface->lpRendVertex[0];
	v[1] = rendface->lpRendVertex[1];
	v[2] = rendface->lpRendVertex[2];

	for (midcnt = 0; midcnt < 3; midcnt++)
	{
		nexcnt = midcnt + 1;
		if (nexcnt == 3)
			nexcnt = 0;
		if (StatsClips[midcnt] == 0 && StatsClips[nexcnt] != 0)
			break;
	}

	lascnt = midcnt - 1;
	if (lascnt < 0) lascnt = 2;

	if (!StatsClips[lascnt])
	{
		switch (dwClipMode)
		{
		case SMCLIP_LEFT:
			cv[0] = AddRendVertex_ClipLeft(rendface, midcnt, nexcnt, &fMultPoint[0]);
			cv[1] = AddRendVertex_ClipLeft(rendface, lascnt, nexcnt, &fMultPoint[1]);
			break;
		case SMCLIP_RIGHT:
			cv[0] = AddRendVertex_ClipRight(rendface, midcnt, nexcnt, &fMultPoint[0]);
			cv[1] = AddRendVertex_ClipRight(rendface, lascnt, nexcnt, &fMultPoint[1]);
			break;
		case SMCLIP_TOP:
			cv[0] = AddRendVertex_ClipTop(rendface, midcnt, nexcnt, &fMultPoint[0]);
			cv[1] = AddRendVertex_ClipTop(rendface, lascnt, nexcnt, &fMultPoint[1]);
			break;
		case SMCLIP_BOTTOM:
			cv[0] = AddRendVertex_ClipBottom(rendface, midcnt, nexcnt, &fMultPoint[0]);
			cv[1] = AddRendVertex_ClipBottom(rendface, lascnt, nexcnt, &fMultPoint[1]);
			break;
		case SMCLIP_NEARZ:
			cv[0] = AddRendVertex_ClipNearZ(rendface, midcnt, nexcnt, &fMultPoint[0]);
			cv[1] = AddRendVertex_ClipNearZ(rendface, lascnt, nexcnt, &fMultPoint[1]);
			break;
		case SMCLIP_FARZ:
			cv[0] = AddRendVertex_ClipFarZ(rendface, midcnt, nexcnt, &fMultPoint[0]);
			cv[1] = AddRendVertex_ClipFarZ(rendface, lascnt, nexcnt, &fMultPoint[1]);
			break;
		}

		rFace[0] = AddRendFace(v[midcnt], cv[0], v[lascnt], rendface->Matrial, NULL);
		rFace[1] = AddRendFace(cv[0], cv[1], v[lascnt], rendface->Matrial, NULL);

		texLink = rendface->lpTexLink;
		for (cnt = 0; cnt < 8; cnt++)
		{
			if (!texLink)
				break;
			u0 = texLink->u[midcnt] + (texLink->u[nexcnt] - texLink->u[midcnt]) * fMultPoint[0];
			v0 = texLink->v[midcnt] + (texLink->v[nexcnt] - texLink->v[midcnt]) * fMultPoint[0];
			u1 = texLink->u[lascnt] + (texLink->u[nexcnt] - texLink->u[lascnt]) * fMultPoint[1];
			v1 = texLink->v[lascnt] + (texLink->v[nexcnt] - texLink->v[lascnt]) * fMultPoint[1];

			AddRendTempTexLink(rFace[0], texLink->hTexture, texLink->u[midcnt], texLink->v[midcnt], u0, v0, texLink->u[lascnt], texLink->v[lascnt]);

			AddRendTempTexLink(rFace[1], texLink->hTexture, u0, v0, u1, v1, texLink->u[lascnt], texLink->v[lascnt]);

			texLink = texLink->NextTex;
		}

	}
	else
	{
		switch (dwClipMode)
		{
		case SMCLIP_LEFT:
			cv[0] = AddRendVertex_ClipLeft(rendface, midcnt, nexcnt, &fMultPoint[0]);
			cv[1] = AddRendVertex_ClipLeft(rendface, midcnt, lascnt, &fMultPoint[1]);
			break;
		case SMCLIP_RIGHT:
			cv[0] = AddRendVertex_ClipRight(rendface, midcnt, nexcnt, &fMultPoint[0]);
			cv[1] = AddRendVertex_ClipRight(rendface, midcnt, lascnt, &fMultPoint[1]);
			break;
		case SMCLIP_TOP:
			cv[0] = AddRendVertex_ClipTop(rendface, midcnt, nexcnt, &fMultPoint[0]);
			cv[1] = AddRendVertex_ClipTop(rendface, midcnt, lascnt, &fMultPoint[1]);
			break;
		case SMCLIP_BOTTOM:
			cv[0] = AddRendVertex_ClipBottom(rendface, midcnt, nexcnt, &fMultPoint[0]);
			cv[1] = AddRendVertex_ClipBottom(rendface, midcnt, lascnt, &fMultPoint[1]);
			break;
		case SMCLIP_NEARZ:
			cv[0] = AddRendVertex_ClipNearZ(rendface, midcnt, nexcnt, &fMultPoint[0]);
			cv[1] = AddRendVertex_ClipNearZ(rendface, midcnt, lascnt, &fMultPoint[1]);
			break;
		case SMCLIP_FARZ:
			cv[0] = AddRendVertex_ClipFarZ(rendface, midcnt, nexcnt, &fMultPoint[0]);
			cv[1] = AddRendVertex_ClipFarZ(rendface, midcnt, lascnt, &fMultPoint[1]);
			break;
		}
		rFace[0] = AddRendFace(v[midcnt], cv[0], cv[1], rendface->Matrial, NULL);

		texLink = rendface->lpTexLink;
		for (cnt = 0; cnt < 8; cnt++)
		{
			if (!texLink)
				break;
			u0 = texLink->u[midcnt] + (texLink->u[nexcnt] - texLink->u[midcnt]) * fMultPoint[0];
			v0 = texLink->v[midcnt] + (texLink->v[nexcnt] - texLink->v[midcnt]) * fMultPoint[0];
			u1 = texLink->u[midcnt] + (texLink->u[lascnt] - texLink->u[midcnt]) * fMultPoint[1];
			v1 = texLink->v[midcnt] + (texLink->v[lascnt] - texLink->v[midcnt]) * fMultPoint[1];

			AddRendTempTexLink(rFace[0], texLink->hTexture, texLink->u[midcnt], texLink->v[midcnt], u0, v0, u1, v1);

			texLink = texLink->NextTex;
		}
	}

	return TRUE;
}




// ������ ���̽��� �ؽ��� Ŭ���� 
int smRENDER3D::AddRendFaceTextureClip(smRENDFACE *rendface)
{

	smRENDVERTEX *v[3];
	smRENDVERTEX *cv[2];			//���� ���ؽ�
	float		 fMultPoint[2];
	float		 u0, v0, u1, v1;
	int cnt;
	int StatsClips[3];
	int midcnt, nexcnt, lascnt;

	smTEXLINK	*texLink;
	smRENDFACE	*rFace[3];

	StatsClips[0] = rendface->lpRendVertex[0]->ClipStatus & SMCLIP_TEXTURE;
	StatsClips[1] = rendface->lpRendVertex[1]->ClipStatus & SMCLIP_TEXTURE;
	StatsClips[2] = rendface->lpRendVertex[2]->ClipStatus & SMCLIP_TEXTURE;

	//��� ���ؽ��� ȭ�� �ۿ� ��ġ �ϸ� ǥ������ ���� ( NULL ���� �����ְ� ���� ���� )
	if (StatsClips[0] && StatsClips[1] && StatsClips[2]) return NULL;

	//���� ���̽��� ������� �ʴ´�
	rendface->ClipStatus |= SMCLIP_DISPLAYOUT;

	v[0] = rendface->lpRendVertex[0];
	v[1] = rendface->lpRendVertex[1];
	v[2] = rendface->lpRendVertex[2];

	for (midcnt = 0; midcnt < 3; midcnt++)
	{
		nexcnt = midcnt + 1;

		if (nexcnt == 3)
			nexcnt = 0;
		if (StatsClips[midcnt] == 0 && StatsClips[nexcnt] != 0)
			break;
	}

	lascnt = midcnt - 1;
	if (lascnt < 0) lascnt = 2;

	if (!StatsClips[lascnt])
	{
		cv[0] = AddRendVertex_ClipTexture(rendface, midcnt, nexcnt, &fMultPoint[0]);
		cv[1] = AddRendVertex_ClipTexture(rendface, lascnt, nexcnt, &fMultPoint[1]);

		rFace[0] = AddRendFace(v[midcnt], cv[0], v[lascnt], rendface->Matrial, NULL);
		rFace[1] = AddRendFace(cv[0], cv[1], v[lascnt], rendface->Matrial, NULL);
		rFace[2] = AddRendFace(cv[0], v[nexcnt], cv[1], rendface->Matrial, NULL);

		texLink = rendface->lpTexLink;

		for (cnt = 0; cnt < 8; cnt++)
		{
			if (!texLink)
				break;
			u0 = texLink->u[midcnt] + (texLink->u[nexcnt] - texLink->u[midcnt]) * fMultPoint[0];
			v0 = texLink->v[midcnt] + (texLink->v[nexcnt] - texLink->v[midcnt]) * fMultPoint[0];
			u1 = texLink->u[lascnt] + (texLink->u[nexcnt] - texLink->u[lascnt]) * fMultPoint[1];
			v1 = texLink->v[lascnt] + (texLink->v[nexcnt] - texLink->v[lascnt]) * fMultPoint[1];

			AddRendTempTexLink(rFace[0], texLink->hTexture, texLink->u[midcnt], texLink->v[midcnt], u0, v0, texLink->u[lascnt], texLink->v[lascnt]);

			AddRendTempTexLink(rFace[1], texLink->hTexture, u0, v0, u1, v1, texLink->u[lascnt], texLink->v[lascnt]);

			AddRendTempTexLink(rFace[2], texLink->hTexture, u0, v0, texLink->u[nexcnt], texLink->v[nexcnt], u1, v1);

			texLink = texLink->NextTex;
		}
	}
	else
	{
		cv[0] = AddRendVertex_ClipTexture(rendface, midcnt, nexcnt, &fMultPoint[0]);
		cv[1] = AddRendVertex_ClipTexture(rendface, midcnt, lascnt, &fMultPoint[1]);

		rFace[0] = AddRendFace(v[midcnt], cv[0], cv[1], rendface->Matrial, NULL);
		rFace[1] = AddRendFace(cv[0], v[nexcnt], v[lascnt], rendface->Matrial, NULL);
		rFace[2] = AddRendFace(cv[0], v[lascnt], cv[1], rendface->Matrial, NULL);

		texLink = rendface->lpTexLink;

		for (cnt = 0; cnt < 8; cnt++)
		{
			if (!texLink)
				break;
			u0 = texLink->u[midcnt] + (texLink->u[nexcnt] - texLink->u[midcnt]) * fMultPoint[0];
			v0 = texLink->v[midcnt] + (texLink->v[nexcnt] - texLink->v[midcnt]) * fMultPoint[0];
			u1 = texLink->u[midcnt] + (texLink->u[lascnt] - texLink->u[midcnt]) * fMultPoint[1];
			v1 = texLink->v[midcnt] + (texLink->v[lascnt] - texLink->v[midcnt]) * fMultPoint[1];

			// ( v[midcnt] ) -> cv[0] -> cv[1]
			AddRendTempTexLink(rFace[0], texLink->hTexture,
				texLink->u[midcnt], texLink->v[midcnt], u0, v0, u1, v1);

			// cv[0] -> v[nexcnt] -> v[lascnt]
			AddRendTempTexLink(rFace[1], texLink->hTexture,
				u0, v0, texLink->u[nexcnt], texLink->v[nexcnt], texLink->u[lascnt], texLink->v[lascnt]);

			// cv[0] -> v[lascnt] -> cv[1]
			AddRendTempTexLink(rFace[2], texLink->hTexture,
				u0, v0, texLink->u[lascnt], texLink->v[lascnt], u1, v1);

			texLink = texLink->NextTex;
		}
	}

	return TRUE;
}

int smRENDER3D::SetDynamicObjLight(smRENDVERTEX *sv, int z)
{
	int cnt;

	int sx, sy, sz;
	int dist;
	int range, drange;
	int power;
	int r, g, b, a;
	int drg;

	if (z < ccDistZMin + (6 * 64))
	{
		for (cnt = 0; cnt < nRendObjLight; cnt++)
		{
			sx = abs(sv->tx - smRendObjLight[cnt].rx);
			sy = abs(sv->ty - smRendObjLight[cnt].ry);
			sz = abs(sv->tz - smRendObjLight[cnt].rz);
			range = smRendObjLight[cnt].Range;
			drange = smRendObjLight[cnt].dRange;

			if (sx < range && sy < range && sz < range)
			{
				sx >>= FLOATNS;
				sy >>= FLOATNS;
				sz >>= FLOATNS;

				dist = sx * sx + sz * sz + sy * sy;
				if (dist < drange)
				{
					drg = (drange >> FLOATNS);
					if (drg == 0)
						drg = 1;

					power = (drange - dist) / drg;
					r = (smRendObjLight[cnt].r * power) >> FLOATNS;
					g = (smRendObjLight[cnt].g * power) >> FLOATNS;
					b = (smRendObjLight[cnt].b * power) >> FLOATNS;
					a = (smRendObjLight[cnt].a * power) >> FLOATNS;
					AddLight(sv, r, g, b, a);

					if (sv->sLight[SMC_R] > 540) sv->sLight[SMC_R] = 540;
					if (sv->sLight[SMC_G] > 540) sv->sLight[SMC_G] = 540;
					if (sv->sLight[SMC_B] > 540) sv->sLight[SMC_B] = 540;
				}
			}
		}
	}

	return TRUE;
}

int smRENDER3D::SetDynamicLight(smRENDVERTEX *sv, int z)
{
	int cnt;

	int sx, sy, sz;
	int dist;
	int range, drange;
	int power;
	int r, g, b, a;
	int drg;


	if (z < ccDistZMin + (6 * 64)) {
		for (cnt = 0; cnt < nRendLight; cnt++) {
			sx = abs(sv->tx - smRendLight[cnt].rx);
			sy = abs(sv->ty - smRendLight[cnt].ry);
			sz = abs(sv->tz - smRendLight[cnt].rz);
			range = smRendLight[cnt].Range;
			drange = smRendLight[cnt].dRange;

			if (sx < range && sy < range && sz < range) {
				sx >>= FLOATNS;
				sy >>= FLOATNS;
				sz >>= FLOATNS;

				dist = sx * sx + sz * sz + sy * sy;
				if (dist < drange) {
					drg = (drange >> FLOATNS);
					if (drg == 0) drg = 1;
					power = (drange - dist) / drg;
					r = (smRendLight[cnt].r * power) >> FLOATNS;
					g = (smRendLight[cnt].g * power) >> FLOATNS;
					b = (smRendLight[cnt].b * power) >> FLOATNS;
					a = (smRendLight[cnt].a * power) >> FLOATNS;
					AddLight(sv, r, g, b, a);

					if (sv->sLight[SMC_R] > 540) sv->sLight[SMC_R] = 540;
					if (sv->sLight[SMC_G] > 540) sv->sLight[SMC_G] = 540;
					if (sv->sLight[SMC_B] > 540) sv->sLight[SMC_B] = 540;

				}
			}
		}
	}

	return TRUE;
}

// Z ���� ���� ����ġ�� BackColor���� �������� �����Ѵ� 
int smRENDER3D::SetColorZclip(smRENDVERTEX *sv, int z)
{
	if (z > ccDistZMin) {
		int result;
		int lev;

		lev = (z - ccDistZMin) << (13 - ShiftMAPCELL_MULT);
		result = ShiftLight(sv, lev >> 8, ccBackColor.r >> 8, ccBackColor.g >> 8, ccBackColor.b >> 8, 0);
		return result;
	}

	return FALSE;
}

// ���ؽ��� ������ �־��� ���� �������� �ܰ������� ����
int smRENDER3D::ShiftLight(smRENDVERTEX *sv, int lev, int r, int g, int b, int a)
{
	int cFlag;
	int dlev;

	int col, spe;

	if (lev >= 256) {
		lev = 255;
		cFlag = 1;
	}
	else
		cFlag = 0;

	dlev = lev;

	// RED
	col = sv->bCol[0];
	spe = sv->bSpe[0];
	col -= (col * dlev) >> 8;
	spe += ((r - spe) * dlev) >> 8;
	sv->bCol[0] = col;
	sv->bSpe[0] = spe;

	// GREEN
	col = sv->bCol[1];
	spe = sv->bSpe[1];
	col -= (col * dlev) >> 8;
	spe += ((g - spe) * dlev) >> 8;
	sv->bCol[1] = col;
	sv->bSpe[1] = spe;

	// BLUE
	col = sv->bCol[2];
	spe = sv->bSpe[2];
	col -= (col * dlev) >> 8;
	spe += ((b - spe) * dlev) >> 8;
	sv->bCol[2] = col;
	sv->bSpe[2] = spe;

	// ALPHA
	col = sv->bCol[3];
	spe = sv->bSpe[3];
	col -= (col * dlev) >> 8;
	spe += ((a - spe) * dlev) >> 8;
	sv->bCol[3] = col;
	sv->bSpe[3] = spe;

	if (cFlag) return TRUE;

	return FALSE;
}

int smRENDER3D::AddLight(smRENDVERTEX *sv, int r, int g, int b, int a)
{

	sv->sLight[SMC_R] += r;
	sv->sLight[SMC_G] += g;
	sv->sLight[SMC_B] += b;
	sv->sLight[SMC_A] += a;

	return TRUE;
}
int smRENDER3D::SetRendColor(smRENDVERTEX *sv)
{
	int col, spe;
	int cnt;

	for (cnt = 0; cnt < 4; cnt++) {
		col = sv->sLight[cnt];
		spe = 0;
		if (col < 0) { col = 0; spe = 0; }
		if (col > 255) { spe = col - 256; col = 255; }
		if (spe > 255)  spe = 255;
		sv->bCol[cnt] = col;
		sv->bSpe[cnt] = spe;
	}

	return TRUE;
}

int smRENDER3D::AddRendMaterialList(int MatNum)
{
	if (!RendMatrial[MatNum].RegistRendList)
	{
		if (smRendMaterial[MatNum].MapOpacity == TRUE || smRendMaterial[MatNum].Transparency != 0)
			RendMatrialList[RMatListRearCnt--] = MatNum;
		else
			RendMatrialList[RMatListCnt++] = MatNum;

		RendMatrial[MatNum].RegistRendList = TRUE;
	}

	return TRUE;

}
int smRENDER3D::ClipRendFace()
{
	int cnt;
	DWORD ClipStatus;
	smRENDMATRIAL	*rmat;
	int nrface;

	int ClipCnt;
	DWORD ClipValue;
	smTEXTUREHANDLE	*smTex;

	ClipValue = 1;

	for (ClipCnt = 0; ClipCnt < 6; ClipCnt++)
	{
		if (ClipStates&ClipValue)
		{
			for (cnt = 0; cnt < nRendFace; cnt++)
			{
				ClipStatus = RendFace[cnt].ClipStatus;
				if (!(ClipStatus&SMCLIP_DISPLAYOUT) && (ClipStatus&ClipValue))
					AddRendFaceClip(&RendFace[cnt], ClipValue);
			}
		}
		ClipValue <<= 1;

		if (ClipValue == SMCLIP_FARZ)
		{
			if (m_GameFieldView == 0 || m_GameFieldViewStep == 1)
			{
				for (cnt = 0; cnt < nRendFace; cnt++)
				{
					smTex = smRendMaterial[RendFace[cnt].Matrial].smTexture[0];
					if (smTex && smTex->NameA[0])
					{
						ClipStatus = RendFace[cnt].ClipStatus;
						if (!(ClipStatus&SMCLIP_DISPLAYOUT) && (ClipStatus&ClipValue))
							AddRendFaceClip(&RendFace[cnt], ClipValue);
					}
				}
			}
			ClipValue <<= 1;
			ClipCnt++;
		}
	}


	nrface = nRendFace;

	int MatNum;

	for (cnt = 0; cnt < nRendFace; cnt++)
	{
		ClipStatus = RendFace[cnt].ClipStatus;
		if (!(ClipStatus&SMCLIP_DISPLAYOUT))
		{
			MatNum = RendFace[cnt].Matrial;
			rmat = &RendMatrial[MatNum];
			{
				rmat->MatrialCounter++;
				if (!rmat->LastLinkFace)
				{
					rmat->StartFace = &RendFace[cnt];
					rmat->LastLinkFace = &RendFace[cnt];
					AddRendMaterialList(MatNum);
				}
				else
				{
					rmat->LastLinkFace->NexRendFace = &RendFace[cnt];
					rmat->LastLinkFace = &RendFace[cnt];
				}
			}

			RendFace[cnt].lpRendVertex[0]->ClipStatus |= SMCLIP_DISPLAYIN;
			RendFace[cnt].lpRendVertex[1]->ClipStatus |= SMCLIP_DISPLAYIN;
			RendFace[cnt].lpRendVertex[2]->ClipStatus |= SMCLIP_DISPLAYIN;
		}
	}


	return TRUE;
}


int smRENDER3D::GeomVertex2D(int ColorEffect)
{
	int				 cnt, z;
	smRENDVERTEX	*rv;

	if (ColorEffect == TRUE)
	{
		for (cnt = 0; cnt < nRendVertex; cnt++)
		{
			rv = &RendVertex[cnt];

			if (rv->ClipStatus & SMCLIP_DISPLAYIN)
			{
				z = int(float(rv->tz) / fONE);
				DxProjectionWork(rv);

				if (bApplyRendObjLight && nRendObjLight)
					SetDynamicObjLight(rv, z);

				if (nRendLight)
					SetDynamicLight(rv, z);

				AddLight(rv, Color_R, Color_G, Color_B, Color_A);
				SetRendColor(rv);

				SetColorZclip(rv, z);
			}
		}
	}
	else
	{
		for (cnt = 0; cnt < nRendVertex; cnt++)
		{
			rv = &RendVertex[cnt];

			if (rv->ClipStatus & SMCLIP_DISPLAYIN)
			{
				z = int(float(rv->tz) / fONE);
				DxProjectionWork(rv);

				if (bApplyRendObjLight && nRendObjLight)
					SetDynamicObjLight(rv, z);

				if (nRendLight)
					SetDynamicLight(rv, z);

				AddLight(rv, Color_R, Color_G, Color_B, Color_A);
				SetRendColor(rv);
			}
		}
	}

	return TRUE;
}

smRENDVERTEX * smRENDER3D::AddRendVertex_ClipLeft(smRENDFACE *rendface, int a, int b, float *fMultPoint)
{
	int		x1, x2;
	int		z1, z2;
	int		s1, s2;
	float	fMult;
	int		Mult;
	int		cnt;

	int		x, y, z;
	short	sCol[4];

	smRENDVERTEX *t1;
	smRENDVERTEX *t2;


	t1 = rendface->lpRendVertex[a];
	t2 = rendface->lpRendVertex[b];

	x1 = t1->tx;
	z1 = -(x1 << SMSHIFT_PERSPECTIVE_WIDTH);
	x2 = t2->tx;
	z2 = -(x2 << SMSHIFT_PERSPECTIVE_WIDTH);

	s1 = abs(t1->tz - z1);
	s2 = abs(t2->tz - z2);


	fMult = (float)((1 / ((double)(s2 + s1)))*(double)s1);
	Mult = (int)(fMult * smCLIP_DETAIL);


	x = t1->tx + (((t2->tx - t1->tx) * Mult) >> smCLIP_DETAIL_SHIFT);
	y = t1->ty + (((t2->ty - t1->ty) * Mult) >> smCLIP_DETAIL_SHIFT);
	z = (-x) << SMSHIFT_PERSPECTIVE_WIDTH;


	for (cnt = 0; cnt < 4; cnt++)
	{
		sCol[cnt] = (short)((int)t1->sLight[cnt] + ((((int)t2->sLight[cnt] - (int)t1->sLight[cnt]) * Mult) >> smCLIP_DETAIL_SHIFT));
	}


	*fMultPoint = fMult;

	int nx = t2->nx - t2->tx;
	int ny = t2->ny - t2->ty;
	int nz = t2->nz - t2->tz;
	return AddRendVertex(x, y, z, sCol, x + nx, y + ny, z + nz);

}

smRENDVERTEX * smRENDER3D::AddRendVertex_ClipRight(smRENDFACE *rendface, int a, int b, float *fMultPoint)
{
	int		x1, x2;
	int		z1, z2;
	int		s1, s2;
	float	fMult;
	int		Mult;
	int		cnt;

	int		x, y, z;
	short	sCol[4];

	smRENDVERTEX *t1;
	smRENDVERTEX *t2;


	t1 = rendface->lpRendVertex[a];
	t2 = rendface->lpRendVertex[b];

	x1 = t1->tx;
	z1 = (x1 << SMSHIFT_PERSPECTIVE_WIDTH);
	x2 = t2->tx;
	z2 = (x2 << SMSHIFT_PERSPECTIVE_WIDTH);

	s1 = abs(t1->tz - z1);
	s2 = abs(t2->tz - z2);


	fMult = (float)((1 / ((double)(s2 + s1)))*(double)s1);
	Mult = (int)(fMult * smCLIP_DETAIL);


	x = t1->tx + (((t2->tx - t1->tx) * Mult) >> smCLIP_DETAIL_SHIFT);
	y = t1->ty + (((t2->ty - t1->ty) * Mult) >> smCLIP_DETAIL_SHIFT);
	z = x << SMSHIFT_PERSPECTIVE_WIDTH;

	for (cnt = 0; cnt < 4; cnt++)
		sCol[cnt] = (short)((int)t1->sLight[cnt] + ((((int)t2->sLight[cnt] - (int)t1->sLight[cnt]) * Mult) >> smCLIP_DETAIL_SHIFT));


	*fMultPoint = fMult;

	int nx = t2->nx - t2->tx;
	int ny = t2->ny - t2->ty;
	int nz = t2->nz - t2->tz;
	return AddRendVertex(x, y, z, sCol, x + nx, y + ny, z + nz);
}

smRENDVERTEX * smRENDER3D::AddRendVertex_ClipBottom(smRENDFACE *rendface, int a, int b, float *fMultPoint)
{
	int		y1, y2;
	int		z1, z2;
	int		s1, s2;
	float	fMult;
	int		Mult;
	int		cnt;

	int		x, y, z;
	short	sCol[4];

	smRENDVERTEX *t1;
	smRENDVERTEX *t2;


	t1 = rendface->lpRendVertex[a];
	t2 = rendface->lpRendVertex[b];

	y1 = t1->ty;
	z1 = -((y1 * SMMULT_PERSPECTIVE_HEIGHT) >> FLOATNS);
	y2 = t2->ty;
	z2 = -((y2 * SMMULT_PERSPECTIVE_HEIGHT) >> FLOATNS);

	s1 = abs(t1->tz - z1);
	s2 = abs(t2->tz - z2);

	fMult = (float)((1 / ((double)(s2 + s1)))*(double)s1);

	Mult = (int)(fMult * smCLIP_DETAIL);

	x = t1->tx + (((t2->tx - t1->tx) * Mult) >> smCLIP_DETAIL_SHIFT);
	y = t1->ty + (((t2->ty - t1->ty) * Mult) >> smCLIP_DETAIL_SHIFT);
	z = ((-y) * SMMULT_PERSPECTIVE_HEIGHT) >> FLOATNS;

	for (cnt = 0; cnt < 4; cnt++)
		sCol[cnt] = (short)((int)t1->sLight[cnt] + ((((int)t2->sLight[cnt] - (int)t1->sLight[cnt]) * Mult) >> smCLIP_DETAIL_SHIFT));

	*fMultPoint = fMult;


	int nx = t2->nx - t2->tx;
	int ny = t2->ny - t2->ty;
	int nz = t2->nz - t2->tz;
	return AddRendVertex(x, y, z, sCol, x + nx, y + ny, z + nz);
}

smRENDVERTEX * smRENDER3D::AddRendVertex_ClipTop(smRENDFACE *rendface, int a, int b, float *fMultPoint)
{
	int		y1, y2;
	int		z1, z2;
	int		s1, s2;
	float	fMult;
	int		Mult;
	int		cnt;

	int		x, y, z;
	short	sCol[4];

	smRENDVERTEX *t1;
	smRENDVERTEX *t2;

	t1 = rendface->lpRendVertex[a];
	t2 = rendface->lpRendVertex[b];

	y1 = t1->ty;
	z1 = ((y1 * SMMULT_PERSPECTIVE_HEIGHT) >> FLOATNS);
	y2 = t2->ty;
	z2 = ((y2 * SMMULT_PERSPECTIVE_HEIGHT) >> FLOATNS);

	s1 = abs(t1->tz - z1);
	s2 = abs(t2->tz - z2);

	fMult = (float)((1 / ((double)(s2 + s1)))*(double)s1);

	Mult = (int)(fMult * smCLIP_DETAIL);

	x = t1->tx + (((t2->tx - t1->tx) * Mult) >> smCLIP_DETAIL_SHIFT);
	y = t1->ty + (((t2->ty - t1->ty) * Mult) >> smCLIP_DETAIL_SHIFT);
	z = y << SMSHIFT_PERSPECTIVE_WIDTH;
	z = (y * SMMULT_PERSPECTIVE_HEIGHT) >> FLOATNS;


	for (cnt = 0; cnt < 4; cnt++)
		sCol[cnt] = (short)((int)t1->sLight[cnt] + ((((int)t2->sLight[cnt] - (int)t1->sLight[cnt]) * Mult) >> smCLIP_DETAIL_SHIFT));

	*fMultPoint = fMult;

	int nx = t2->nx - t2->tx;
	int ny = t2->ny - t2->ty;
	int nz = t2->nz - t2->tz;
	return AddRendVertex(x, y, z, sCol, x + nx, y + ny, z + nz);
}

smRENDVERTEX * smRENDER3D::AddRendVertex_ClipNearZ(smRENDFACE *rendface, int a, int b, float *fMultPoint)
{
	int		s1, s2;
	float	fMult;
	int		Mult;
	int		cnt;

	int		x, y, z;
	short	sCol[4];

	smRENDVERTEX *t1;
	smRENDVERTEX *t2;

	t1 = rendface->lpRendVertex[a];
	t2 = rendface->lpRendVertex[b];

	s1 = abs(t1->tz - SMFLOAT_DIST_NEARZ);
	s2 = abs(t2->tz - SMFLOAT_DIST_NEARZ);

	fMult = (float)((1 / ((double)(s2 + s1)))*(double)s1);
	Mult = (int)(fMult * smCLIP_DETAIL);

	x = t1->tx + (((t2->tx - t1->tx) * Mult) >> smCLIP_DETAIL_SHIFT);
	y = t1->ty + (((t2->ty - t1->ty) * Mult) >> smCLIP_DETAIL_SHIFT);
	z = SMFLOAT_DIST_NEARZ;

	for (cnt = 0; cnt < 4; cnt++)
		sCol[cnt] = (short)((int)t1->sLight[cnt] + ((((int)t2->sLight[cnt] - (int)t1->sLight[cnt]) * Mult) >> smCLIP_DETAIL_SHIFT));

	*fMultPoint = fMult;

	int nx = t2->nx - t2->tx;
	int ny = t2->ny - t2->ty;
	int nz = t2->nz - t2->tz;
	return AddRendVertex(x, y, z, sCol, x + nx, y + ny, z + nz);
}

smRENDVERTEX * smRENDER3D::AddRendVertex_ClipFarZ(smRENDFACE *rendface, int a, int b, float *fMultPoint)
{
	int		s1, s2;
	float	fMult;
	int		Mult;
	int		cnt;

	int		x, y, z;
	short	sCol[4];

	smRENDVERTEX *t1;
	smRENDVERTEX *t2;


	t1 = rendface->lpRendVertex[a];
	t2 = rendface->lpRendVertex[b];

	s1 = abs(t1->tz - SMFLOAT_DIST_FARZ);
	s2 = abs(t2->tz - SMFLOAT_DIST_FARZ);

	fMult = (float)((1 / ((double)(s2 + s1)))*(double)s1);
	Mult = (int)(fMult * smCLIP_DETAIL);

	x = t1->tx + (((t2->tx - t1->tx) * Mult) >> smCLIP_DETAIL_SHIFT);
	y = t1->ty + (((t2->ty - t1->ty) * Mult) >> smCLIP_DETAIL_SHIFT);
	z = SMFLOAT_DIST_FARZ;

	for (cnt = 0; cnt < 4; cnt++)
		sCol[cnt] = (short)((int)t1->sLight[cnt] + ((((int)t2->sLight[cnt] - (int)t1->sLight[cnt]) * Mult) >> smCLIP_DETAIL_SHIFT));

	*fMultPoint = fMult;

	int nx = t2->nx - t2->tx;
	int ny = t2->ny - t2->ty;
	int nz = t2->nz - t2->tz;
	return AddRendVertex(x, y, z, sCol, x + nx, y + ny, z + nz);
}
smRENDVERTEX * smRENDER3D::AddRendVertex_ClipTexture(smRENDFACE *rendface, int a, int b, float *fMultPoint)
{
	int		s1, s2;
	float	fMult;
	int		Mult;
	int		cnt;

	int		x, y, z;
	short	sCol[4];

	smRENDVERTEX *t1;
	smRENDVERTEX *t2;

	t1 = rendface->lpRendVertex[a];
	t2 = rendface->lpRendVertex[b];

	s1 = abs(t1->tz - SMFLOAT_DIST_TEXCLIP);
	s2 = abs(t2->tz - SMFLOAT_DIST_TEXCLIP);

	fMult = (float)((1 / ((double)(s2 + s1)))*(double)s1);
	Mult = (int)(fMult * smCLIP_DETAIL);


	x = t1->tx + (((t2->tx - t1->tx) * Mult) >> smCLIP_DETAIL_SHIFT);
	y = t1->ty + (((t2->ty - t1->ty) * Mult) >> smCLIP_DETAIL_SHIFT);
	z = SMFLOAT_DIST_TEXCLIP;

	for (cnt = 0; cnt < 4; cnt++)
		sCol[cnt] = (short)((int)t1->sLight[cnt] + ((((int)t2->sLight[cnt] - (int)t1->sLight[cnt]) * Mult) >> smCLIP_DETAIL_SHIFT));

	*fMultPoint = fMult;

	return AddRendVertex(x, y, z, sCol);

}
int smRENDER3D::SetD3DRendBuff(D3DVALUE *RenderBuff, int matrial, int TexClip)
{
	smRENDFACE *rendface;
	smRENDVERTEX *rv;
	smTEXLINK *tl;
	int cnt;
	int vcnt, tcnt, mcnt;
	int rendcnt;

	BYTE	dwSpecular[4];
	BYTE	dwColor[4];

	int wtime = (RendStatTime >> 6) & 0xFF;
	float fwtime = (float)wtime / 256;

	if (TexClip == TRUE)
	{
		rendface = RendMatrial[matrial].TexClip_StartFace;
		mcnt = RendMatrial[matrial].TexClip_MatrialCounter;
	}
	else
	{
		rendface = RendMatrial[matrial].StartFace;
		mcnt = RendMatrial[matrial].MatrialCounter;
	}

	rendcnt = 0;

	for (cnt = 0; cnt < mcnt; cnt++)
	{
		if (!(rendface->ClipStatus&SMCLIP_DISPLAYOUT))
		{
			for (vcnt = 0; vcnt < 3; vcnt++)
			{
				rv = rendface->lpRendVertex[vcnt];

				*(RenderBuff++) = (D3DVALUE)rv->xy[0];
				*(RenderBuff++) = (D3DVALUE)rv->xy[1];
				*(RenderBuff++) = (D3DVALUE)rv->zb;
				*(RenderBuff++) = (D3DVALUE)rv->rhw;

				if (RendAlphaFlag && rv->tz > (ccDistZMin << FLOATNS))
				{
					*((DWORD *)dwColor) = *((DWORD *)rv->bCol);
					*((DWORD *)dwSpecular) = *((DWORD *)rv->bSpe);
					dwSpecular[3] = dwSpecular[3] / 2 + dwSpecular[3] / 3;
					dwColor[3] = dwColor[3] / 2 + dwColor[3] / 3;

					*((DWORD *)(RenderBuff++)) = *((DWORD *)dwColor);
					*((DWORD *)(RenderBuff++)) = *((DWORD *)dwSpecular);
				}
				else
				{
					*((DWORD *)(RenderBuff++)) = *((DWORD *)rv->bCol);
					*((DWORD *)(RenderBuff++)) = *((DWORD *)rv->bSpe);
				}
				tl = rendface->lpTexLink;
				for (tcnt = 0; tcnt < 8; tcnt++)
				{
					if (tl == NULL)
					{
						if (tcnt == 1 && s_lpItem2PassTexHandle)
							tl = rendface->lpTexLink;
						else
							break;
					}
					if (TextureFormState[tcnt])
					{
						switch (TextureFormState[tcnt])
						{
						case smTEXSTATE_FS_FORMX:
						case smTEXSTATE_FS_FORMY:
						case smTEXSTATE_FS_FORMZ:
						case smTEXSTATE_FS_NONE:
							*(RenderBuff++) = (D3DVALUE)tl->u[vcnt];
							*(RenderBuff++) = (D3DVALUE)tl->v[vcnt];
							break;

						case smTEXSTATE_FS_SCROLL:
							*(RenderBuff++) = (D3DVALUE)(tl->u[vcnt] + fwtime);
							*(RenderBuff++) = (D3DVALUE)(tl->v[vcnt]);
							break;

						case smTEXSTATE_FS_REFLEX:
						{
							float fEx = float(rv->tx) / fONE;
							float fEy = float(rv->ty) / fONE;
							float fEz = float(rv->tz) / fONE;
							float fLen = (float)sqrt((fEx*fEx) + (fEy*fEy) + (fEz*fEz));
							fEx /= fLen;
							fEy /= fLen;
							fEz /= fLen;

							float fNx = float(rv->nx - rv->tx) / 32767.f;
							float fNy = float(rv->ny - rv->ty) / 32767.f;
							float fNz = float(rv->nz - rv->tz) / 32767.f;

							float fDotNum = (fEx*fNx) + (fEy*fNy) + (fEz*fNz);
							float fx = fEx - (fDotNum * fNx * 2);
							float fy = fEy - (fDotNum * fNy * 2);

							*(RenderBuff++) = (fx * 0.5f) + 0.5f;
							*(RenderBuff++) = (-fy * 0.5f) + 0.5f;
						}
						break;
						}

						if (TextureFormState[tcnt] >= smTEXSTATE_FS_SCROLL2 && TextureFormState[tcnt] <= smTEXSTATE_FS_SCROLL10)
						{
							*(RenderBuff++) = (D3DVALUE)(tl->u[vcnt] + fwtime * (TextureFormState[tcnt] - (smTEXSTATE_FS_SCROLL2 - 2)));
							*(RenderBuff++) = (D3DVALUE)(tl->v[vcnt]);
						}
						else if (TextureFormState[tcnt] >= smTEXSTATE_FS_SCROLLSLOW1 && TextureFormState[tcnt] <= smTEXSTATE_FS_SCROLLSLOW4)
						{
							int factor = smTEXSTATE_FS_SCROLLSLOW4 - TextureFormState[tcnt] + 4;
							wtime = (RendStatTime >> 6) & (0xFFFF >> factor);

							fwtime = float(wtime) / float(0xFFFF >> factor);
							*(RenderBuff++) = (D3DVALUE)(tl->u[vcnt] + fwtime);
							*(RenderBuff++) = (D3DVALUE)(tl->v[vcnt]);
						}
					}
					else
					{
						*(RenderBuff++) = (D3DVALUE)tl->u[vcnt];
						*(RenderBuff++) = (D3DVALUE)tl->v[vcnt];
					}

					tl = tl->NextTex;
				}
			}
			rendcnt++;
		}
		rendface = rendface->NexRendFace;
	}

	return rendcnt;
}


// D3D �������� ���� ���۰� ����
int smRENDER3D::SetD3DRendBuff2(D3DVALUE *RenderBuff, int matrial, int TexClip)
{
	smRENDFACE *rendface;
	smRENDVERTEX *rv;
	smTEXLINK *tl;
	int cnt;
	int vcnt, tcnt, mcnt;
	int rendcnt;

	int wtime = (RendStatTime >> 6) & 0xFF;
	float fwtime = (float)wtime / 256;


	if (TexClip == TRUE)
	{
		rendface = RendMatrial[matrial].TexClip_StartFace;
		mcnt = RendMatrial[matrial].TexClip_MatrialCounter;
	}
	else
	{
		rendface = RendMatrial[matrial].StartFace;
		mcnt = RendMatrial[matrial].MatrialCounter;
	}

	rendcnt = 0;

	for (cnt = 0; cnt < mcnt; cnt++)
	{
		if (!(rendface->ClipStatus&SMCLIP_DISPLAYOUT))
		{
			for (vcnt = 0; vcnt < 3; vcnt++)
			{
				rv = rendface->lpRendVertex[vcnt];

				*(RenderBuff++) = (D3DVALUE)rv->xy[0];
				*(RenderBuff++) = (D3DVALUE)rv->xy[1];
				*(RenderBuff++) = (D3DVALUE)rv->zb;
				*(RenderBuff++) = (D3DVALUE)rv->rhw;

				*((DWORD *)(RenderBuff++)) = (*((DWORD *)rv->bCol)) | 0x00FFFFFF;
				*((DWORD *)(RenderBuff++)) = 0x00000000;

				tl = rendface->lpTexLink;
				for (tcnt = 0; tcnt < 8; tcnt++)
				{
					if (tl == NULL)
					{
						if (tcnt == 1 && s_lpItem2PassTexHandle)
							tl = rendface->lpTexLink;
						else
							break;
					}
					if (TextureFormState[tcnt])
					{
						switch (TextureFormState[tcnt])
						{
						case smTEXSTATE_FS_FORMX:
						case smTEXSTATE_FS_FORMY:
						case smTEXSTATE_FS_FORMZ:
						case smTEXSTATE_FS_NONE:
							*(RenderBuff++) = (D3DVALUE)tl->u[vcnt];
							*(RenderBuff++) = (D3DVALUE)tl->v[vcnt];
							break;

						case smTEXSTATE_FS_SCROLL:
							*(RenderBuff++) = (D3DVALUE)(tl->u[vcnt] + fwtime);
							*(RenderBuff++) = (D3DVALUE)(tl->v[vcnt]);
							break;

						case smTEXSTATE_FS_REFLEX:
						{
							float fEx = float(rv->tx) / fONE;
							float fEy = float(rv->ty) / fONE;
							float fEz = float(rv->tz) / fONE;
							float fLen = (float)sqrt((fEx*fEx) + (fEy*fEy) + (fEz*fEz));
							fEx /= fLen;
							fEy /= fLen;
							fEz /= fLen;

							float fNx = float(rv->nx - rv->tx) / 32767.f;
							float fNy = float(rv->ny - rv->ty) / 32767.f;
							float fNz = float(rv->nz - rv->tz) / 32767.f;

							float fDotNum = (fEx*fNx) + (fEy*fNy) + (fEz*fNz);
							float fx = fEx - (fDotNum * fNx * 2);
							float fy = fEy - (fDotNum * fNy * 2);

							*(RenderBuff++) = (fx * 0.5f) + 0.5f;
							*(RenderBuff++) = (-fy * 0.5f) + 0.5f;
						}
						break;
						}

						if (TextureFormState[tcnt] >= smTEXSTATE_FS_SCROLL2 && TextureFormState[tcnt] <= smTEXSTATE_FS_SCROLL10)
						{
							*(RenderBuff++) = (D3DVALUE)(tl->u[vcnt] + fwtime * (TextureFormState[tcnt] - (smTEXSTATE_FS_SCROLL2 - 2)));
							*(RenderBuff++) = (D3DVALUE)(tl->v[vcnt]);
						}
						else if (TextureFormState[tcnt] >= smTEXSTATE_FS_SCROLLSLOW1 && TextureFormState[tcnt] <= smTEXSTATE_FS_SCROLLSLOW4)
						{
							int factor = smTEXSTATE_FS_SCROLLSLOW4 - TextureFormState[tcnt] + 4;
							wtime = (RendStatTime >> 6) & (0xFFFF >> factor);

							fwtime = float(wtime) / float(0xFFFF >> factor);
							*(RenderBuff++) = (D3DVALUE)(tl->u[vcnt] + fwtime);
							*(RenderBuff++) = (D3DVALUE)(tl->v[vcnt]);
						}
					}
					else
					{
						*(RenderBuff++) = (D3DVALUE)tl->u[vcnt];
						*(RenderBuff++) = (D3DVALUE)tl->v[vcnt];
					}

					tl = tl->NextTex;
				}
			}
			rendcnt++;
		}
		rendface = rendface->NexRendFace;
	}

	return rendcnt;
}
int smRENDER3D::SetD3DRendBuff3(D3DVALUE *RenderBuff, int matrial, int TexClip, short sColors[4])
{
	smRENDFACE *rendface;
	smRENDVERTEX *rv;
	smTEXLINK *tl;
	int cnt;
	int vcnt, tcnt, mcnt;
	int rendcnt;

	BYTE	dwSpecular[4];
	BYTE	dwColor[4];

	int wtime = (RendStatTime >> 6) & 0xFF;
	float fwtime = (float)wtime / 256;

	if (TexClip == TRUE)
	{
		rendface = RendMatrial[matrial].TexClip_StartFace;
		mcnt = RendMatrial[matrial].TexClip_MatrialCounter;
	}
	else
	{
		rendface = RendMatrial[matrial].StartFace;
		mcnt = RendMatrial[matrial].MatrialCounter;
	}

	rendcnt = 0;

	for (cnt = 0; cnt < mcnt; cnt++)
	{
		if (!(rendface->ClipStatus&SMCLIP_DISPLAYOUT))
		{
			for (vcnt = 0; vcnt < 3; vcnt++)
			{
				rv = rendface->lpRendVertex[vcnt];

				*(RenderBuff++) = (D3DVALUE)rv->xy[0];
				*(RenderBuff++) = (D3DVALUE)rv->xy[1];
				*(RenderBuff++) = (D3DVALUE)rv->zb;
				*(RenderBuff++) = (D3DVALUE)rv->rhw;

				if (RendAlphaFlag && rv->tz > (ccDistZMin << FLOATNS))
				{
					*((DWORD *)dwColor) = *((DWORD *)rv->bCol);
					*((DWORD *)dwSpecular) = *((DWORD *)rv->bSpe);
					dwSpecular[3] = dwSpecular[3] / 2 + dwSpecular[3] / 3;
					dwColor[3] = dwColor[3] / 2 + dwColor[3] / 3;

					*((DWORD *)(RenderBuff++)) = *((DWORD *)dwColor);
					*((DWORD *)(RenderBuff++)) = *((DWORD *)dwSpecular);
				}
				else
				{
					if (SetBlinkColorVertex(rv, sColors, dwColor, dwSpecular))
					{
						*((DWORD *)(RenderBuff++)) = *((DWORD *)dwColor);
						*((DWORD *)(RenderBuff++)) = *((DWORD *)dwSpecular);
					}
					else
					{
						*((DWORD *)(RenderBuff++)) = *((DWORD *)rv->bCol);
						*((DWORD *)(RenderBuff++)) = *((DWORD *)rv->bSpe);
					}
				}

				tl = rendface->lpTexLink;
				for (tcnt = 0; tcnt < 8; tcnt++)
				{
					if (!tl) break;
					if (TextureFormState[tcnt])
					{
						switch (TextureFormState[tcnt])
						{
						case smTEXSTATE_FS_FORMX:
						case smTEXSTATE_FS_FORMY:
						case smTEXSTATE_FS_FORMZ:
						case smTEXSTATE_FS_NONE:
							*(RenderBuff++) = (D3DVALUE)tl->u[vcnt];
							*(RenderBuff++) = (D3DVALUE)tl->v[vcnt];
							break;

						case smTEXSTATE_FS_SCROLL:
							*(RenderBuff++) = (D3DVALUE)(tl->u[vcnt] + fwtime);
							*(RenderBuff++) = (D3DVALUE)(tl->v[vcnt]);
							break;

						case smTEXSTATE_FS_REFLEX:
							*(RenderBuff++) = (D3DVALUE)(tl->u[vcnt] + ((float)(rv->tx >> 1) / 65536));
							*(RenderBuff++) = (D3DVALUE)(tl->v[vcnt] + ((float)(rv->ty >> 2) / 65536));
							break;

						}

						if (TextureFormState[tcnt] >= smTEXSTATE_FS_SCROLL2 && TextureFormState[tcnt] <= smTEXSTATE_FS_SCROLL10)
						{
							*(RenderBuff++) = (D3DVALUE)(tl->u[vcnt] + fwtime * (TextureFormState[tcnt] - (smTEXSTATE_FS_SCROLL2 - 2)));
							*(RenderBuff++) = (D3DVALUE)(tl->v[vcnt]);
						}
						else if (TextureFormState[tcnt] >= smTEXSTATE_FS_SCROLLSLOW1 && TextureFormState[tcnt] <= smTEXSTATE_FS_SCROLLSLOW4)
						{
							int factor = smTEXSTATE_FS_SCROLLSLOW4 - TextureFormState[tcnt] + 4;
							wtime = (RendStatTime >> 6) & (0xFFFF >> factor);

							fwtime = float(wtime) / float(0xFFFF >> factor);
							*(RenderBuff++) = (D3DVALUE)(tl->u[vcnt] + fwtime);
							*(RenderBuff++) = (D3DVALUE)(tl->v[vcnt]);
						}
					}
					else
					{
						*(RenderBuff++) = (D3DVALUE)tl->u[vcnt];
						*(RenderBuff++) = (D3DVALUE)tl->v[vcnt];
					}

					tl = tl->NextTex;
				}
			}
			rendcnt++;
		}
		rendface = rendface->NexRendFace;
	}

	return rendcnt;
}
void smRENDER3D::RenderType(int Type)
{
	switch (Type)
	{
	case SMMAT_BLEND_NONE:
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		break;
	case SMMAT_BLEND_ALPHA:
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		break;
	case SMMAT_BLEND_COLOR:
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);
		break;

	case SMMAT_BLEND_ADDCOLOR:
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);
		break;

	case SMMAT_BLEND_SHADOW:
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
		break;

	case SMMAT_BLEND_LAMP:
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;

	case SMMAT_BLEND_INVSHADOW:
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
		break;
	}
}
int smRENDER3D::SetItem2PassD3DRendState(smMATERIAL *lpMaterial)
{
	DWORD cnt;
	int	MapOpacity;
	int MapDualRend;

	MapOpacity = 0;
	MapDualRend = 0;

	if (lpMaterial->TextureType == SMTEX_TYPE_MULTIMIX)
	{
		for (cnt = 0; cnt < 2; cnt++)
		{
			if (cnt == 0)
				TextureFormState[cnt] = lpMaterial->TextureFormState[cnt];
			else
				TextureFormState[cnt] = s_Item2PassTexFormState;

			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_TEXCOORDINDEX, cnt);

			if (cnt == 0)
				GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_COLOROP, D3DTOP_MODULATE);
			else
				GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_COLOROP, D3DTOP_ADD);

			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_COLORARG1, D3DTA_TEXTURE);
			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_COLORARG2, D3DTA_CURRENT);
			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
			GRAPHICENGINE->GetDevice()->SetSamplerState(cnt, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
			GRAPHICENGINE->GetDevice()->SetSamplerState(cnt, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

			if (cnt == 0)
				GRAPHICENGINE->GetDevice()->SetTexture(cnt, lpMaterial->smTexture[cnt]->m_pTexture);
			else
				GRAPHICENGINE->GetDevice()->SetTexture(cnt, s_lpItem2PassTexHandle->m_pTexture);

			if (cnt == 0)
			{
				if (lpMaterial->smTexture[cnt]->iTransparency)
					MapOpacity += lpMaterial->smTexture[cnt]->iTransparency;
			}
		}

		for (cnt = 2; cnt < 8; cnt++)
		{
			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_TEXCOORDINDEX, 0);
			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_COLOROP, D3DTOP_DISABLE);
			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_COLORARG1, D3DTA_TEXTURE);
			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_COLORARG2, D3DTA_CURRENT);
			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
			GRAPHICENGINE->GetDevice()->SetSamplerState(cnt, D3DSAMP_MINFILTER, D3DTEXF_POINT);
			GRAPHICENGINE->GetDevice()->SetSamplerState(cnt, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
			GRAPHICENGINE->GetDevice()->SetTexture(cnt, 0);
		}
	}
	else
	{
		for (cnt = 0; cnt < 8; cnt++)
		{
			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_TEXCOORDINDEX, 0);
			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_COLOROP, D3DTOP_DISABLE);
			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_COLORARG1, D3DTA_TEXTURE);
			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_COLORARG2, D3DTA_CURRENT);
			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
			GRAPHICENGINE->GetDevice()->SetSamplerState(cnt, D3DSAMP_MINFILTER, D3DTEXF_POINT);
			GRAPHICENGINE->GetDevice()->SetSamplerState(cnt, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
			GRAPHICENGINE->GetDevice()->SetTexture(cnt, 0);
		}
	}

	RenderType(lpMaterial->BlendType);

	if (lpMaterial->TwoSide)
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	else
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	if (MapOpacity)
	{
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ALPHAREF, AlphaTestDepth);
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	}
	else
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	if (ZWriteAuto)
	{
		if (lpMaterial->Transparency > 0.2f)
			GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		else
			GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	}

	return MapDualRend;
}

int smRENDER3D::SetD3DRendState(smMATERIAL *lpMaterial, int TexClip)
{
	DWORD cnt;
	int	MapOpacity;
	int MapDualRend;

	MapOpacity = 0;
	MapDualRend = 0;

	switch (lpMaterial->TextureType)
	{
	case SMTEX_TYPE_MULTIMIX:

		for (cnt = 0; cnt < lpMaterial->TextureCounter; cnt++)
		{
			TextureFormState[cnt] = lpMaterial->TextureFormState[cnt];

			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_TEXCOORDINDEX, cnt);

			if (lpMaterial->TextureStageState[cnt])
				GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_COLOROP, lpMaterial->TextureStageState[cnt]);
			else
				GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_COLOROP, D3DTOP_MODULATE);

			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_COLORARG1, D3DTA_TEXTURE);
			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_COLORARG2, D3DTA_CURRENT);

			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);

			GRAPHICENGINE->GetDevice()->SetSamplerState(cnt, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
			GRAPHICENGINE->GetDevice()->SetSamplerState(cnt, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

			GRAPHICENGINE->GetDevice()->SetTexture(cnt, lpMaterial->smTexture[cnt]->m_pTexture);

			if (lpMaterial->smTexture[cnt]->iTransparency)
			{
				MapOpacity += lpMaterial->smTexture[cnt]->iTransparency;
				if (cnt > 0)
				{
					GRAPHICENGINE->GetDevice()->SetTexture(cnt, 0);
					MapDualRend = TRUE;
				}
			}
		}

		for (cnt = lpMaterial->TextureCounter; cnt < 8; cnt++)
		{
			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_TEXCOORDINDEX, 0);

			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_COLOROP, D3DTOP_DISABLE);
			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_COLORARG1, D3DTA_TEXTURE);
			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_COLORARG2, D3DTA_CURRENT);

			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

			GRAPHICENGINE->GetDevice()->SetSamplerState(cnt, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
			GRAPHICENGINE->GetDevice()->SetSamplerState(cnt, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

			GRAPHICENGINE->GetDevice()->SetTexture(cnt, 0);
		}

		break;

	case SMTEX_TYPE_ANIMATION:

		cnt = 0;

		GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_TEXCOORDINDEX, cnt);

		GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_COLOROP, D3DTOP_MODULATE);
		GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_COLORARG2, D3DTA_CURRENT);

		GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
		GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);

		GRAPHICENGINE->GetDevice()->SetSamplerState(cnt, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		GRAPHICENGINE->GetDevice()->SetSamplerState(cnt, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

		if (lpMaterial->AnimationFrame == SMTEX_AUTOANIMATION)
			cnt = (RendStatTime >> lpMaterial->Shift_FrameSpeed)&lpMaterial->FrameMask;
		else
			cnt = lpMaterial->AnimationFrame;

		GRAPHICENGINE->GetDevice()->SetTexture(0, lpMaterial->smAnimTexture[cnt]->m_pTexture);
		MapOpacity += lpMaterial->smAnimTexture[cnt]->iTransparency;

		for (cnt = 1; cnt < 8; cnt++)
		{
			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_TEXCOORDINDEX, 0);

			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_COLOROP, D3DTOP_DISABLE);
			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_COLORARG1, D3DTA_TEXTURE);
			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_COLORARG2, D3DTA_CURRENT);

			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
			GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

			GRAPHICENGINE->GetDevice()->SetSamplerState(cnt, D3DSAMP_MINFILTER, D3DTEXF_POINT);
			GRAPHICENGINE->GetDevice()->SetSamplerState(cnt, D3DSAMP_MAGFILTER, D3DTEXF_POINT);

			GRAPHICENGINE->GetDevice()->SetTexture(cnt, 0);
		}
		break;
	}

	RenderType(lpMaterial->BlendType);

	if (lpMaterial->TwoSide)
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	else
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	if (MapOpacity)
	{
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ALPHAREF, AlphaTestDepth);
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	}
	else
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	if (ZWriteAuto)
	{
		if (lpMaterial->Transparency > 0.2f)
			GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		else
			GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	}

	return MapDualRend;
}

int smRENDER3D::SetD3DRendStateOnlyAlpha(smMATERIAL *lpMaterial, int TexClip)
{
	DWORD cnt;
	DWORD MapCnt;

	MapCnt = 0;

	for (cnt = 0; cnt < lpMaterial->TextureCounter; cnt++)
	{
		if (lpMaterial->smTexture[cnt]->iTransparency)
		{
			GRAPHICENGINE->GetDevice()->SetTextureStageState(MapCnt, D3DTSS_TEXCOORDINDEX, cnt);

			GRAPHICENGINE->GetDevice()->SetTextureStageState(MapCnt, D3DTSS_COLOROP, D3DTOP_MODULATE);
			GRAPHICENGINE->GetDevice()->SetTextureStageState(MapCnt, D3DTSS_COLORARG1, D3DTA_TEXTURE);
			GRAPHICENGINE->GetDevice()->SetTextureStageState(MapCnt, D3DTSS_COLORARG2, D3DTA_CURRENT);

			GRAPHICENGINE->GetDevice()->SetTextureStageState(MapCnt, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
			GRAPHICENGINE->GetDevice()->SetTextureStageState(MapCnt, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
			GRAPHICENGINE->GetDevice()->SetTextureStageState(MapCnt, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);

			GRAPHICENGINE->GetDevice()->SetSamplerState(MapCnt, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
			GRAPHICENGINE->GetDevice()->SetSamplerState(MapCnt, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

			GRAPHICENGINE->GetDevice()->SetTexture(MapCnt, lpMaterial->smTexture[cnt]->m_pTexture);

			MapCnt++;

			break;
		}
	}

	for (cnt = MapCnt; cnt < 8; cnt++)
	{
		GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_TEXCOORDINDEX, 0);

		GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_COLOROP, D3DTOP_DISABLE);
		GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_COLORARG2, D3DTA_CURRENT);

		GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
		GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		GRAPHICENGINE->GetDevice()->SetTextureStageState(cnt, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

		GRAPHICENGINE->GetDevice()->SetSamplerState(cnt, D3DSAMP_MINFILTER, D3DTEXF_POINT);
		GRAPHICENGINE->GetDevice()->SetSamplerState(cnt, D3DSAMP_MAGFILTER, D3DTEXF_POINT);

		GRAPHICENGINE->GetDevice()->SetTexture(cnt, 0);
	}

	GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	if (lpMaterial->TwoSide)
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	else
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	return TRUE;
}
int smRENDER3D::RenderD3D(int MatNum)
{
	int rendcnt;

	if (smRendMaterial[MatNum].TextureCounter == 0 && smRendMaterial[MatNum].AnimTexCounter == 0)
		return FALSE;

	short sColors[4] = { 0, };
	if (smRendMaterial[MatNum].UseState & sMATS_SCRIPT_BLINK_COLOR)
		SetBlinkColor(sColors, smRendMaterial[MatNum].Diffuse, smRendMaterial[MatNum].WindMeshBottom);
	if (RendMatrial[MatNum].MatrialCounter)
	{
		int TexCnt = 0;

		if (s_lpItem2PassTexHandle)
		{
			RendAlphaFlag = SetItem2PassD3DRendState(&smRendMaterial[MatNum]);
			TexCnt = 1;
		}
		else
			RendAlphaFlag = SetD3DRendState(&smRendMaterial[MatNum], FALSE);

		if (smRendMaterial[MatNum].SelfIllum != 0)
			rendcnt = SetD3DRendBuff2(RendBuff, MatNum, FALSE);

		else if (smRendMaterial[MatNum].UseState & sMATS_SCRIPT_BLINK_COLOR)
			rendcnt = SetD3DRendBuff3(RendBuff, MatNum, FALSE, sColors);
		else
			rendcnt = SetD3DRendBuff(RendBuff, MatNum, FALSE);

		GRAPHICENGINE->GetDevice()->SetFVF(D3DFVF_TEXTURE[smRendMaterial[MatNum].TextureCounter + TexCnt]);
		GRAPHICENGINE->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLELIST, rendcnt, (LPVOID)RendBuff, D3DTLVERTEX_SIZE[smRendMaterial[MatNum].TextureCounter + TexCnt]);

		if (RendAlphaFlag)
		{
			SetD3DRendStateOnlyAlpha(&smRendMaterial[MatNum], FALSE);
			GRAPHICENGINE->GetDevice()->SetFVF(D3DFVF_TEXTURE[smRendMaterial[MatNum].TextureCounter + TexCnt]);
			GRAPHICENGINE->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLELIST, rendcnt, (LPVOID)RendBuff, D3DTLVERTEX_SIZE[smRendMaterial[MatNum].TextureCounter + TexCnt]);
		}
	}
	if (RendMatrial[MatNum].TexClip_MatrialCounter)
	{
		RendAlphaFlag = SetD3DRendState(&smRendMaterial[MatNum], TRUE);
		if (smRendMaterial[MatNum].SelfIllum != 0)
			rendcnt = SetD3DRendBuff2(RendBuff, MatNum, TRUE);

		else if (smRendMaterial[MatNum].UseState & sMATS_SCRIPT_BLINK_COLOR)
			rendcnt = SetD3DRendBuff3(RendBuff, MatNum, TRUE, sColors);
		else
			rendcnt = SetD3DRendBuff(RendBuff, MatNum, TRUE);

		GRAPHICENGINE->GetDevice()->SetFVF(D3DFVF_TEXTURE[smRendMaterial[MatNum].TextureCounter]);
		GRAPHICENGINE->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLELIST, rendcnt, (LPVOID)RendBuff, D3DTLVERTEX_SIZE[smRendMaterial[MatNum].TextureCounter]);

		if (RendAlphaFlag)
		{
			SetD3DRendStateOnlyAlpha(&smRendMaterial[MatNum], TRUE);
			GRAPHICENGINE->GetDevice()->SetFVF(D3DFVF_TEXTURE[smRendMaterial[MatNum].TextureCounter]);
			GRAPHICENGINE->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLELIST, rendcnt, (LPVOID)RendBuff, D3DTLVERTEX_SIZE[smRendMaterial[MatNum].TextureCounter]);
		}
	}

	return rendcnt;
}


int smRENDER3D::RenderD3D()
{
	int cnt;
	int TotalRendCnt;
	int	MatCnt;

	int	RendLatterCount;
	int	RendLatterBuff[1024];

	RendLatterCount = 0;

	TotalRendCnt = 0;

	for (cnt = 0; cnt < RMatListCnt; cnt++)
	{
		MatCnt = RendMatrialList[cnt];
		if ((smRendMaterial[MatCnt].MeshState&sMATS_SCRIPT_RENDLATTER) == 0)
			TotalRendCnt += RenderD3D(MatCnt);
		else
		{
			if (RendLatterCount < 1024)
				RendLatterBuff[RendLatterCount++] = MatCnt;
			else
				TotalRendCnt += RenderD3D(MatCnt);
		}
	}

	for (cnt = RMatListRearCnt + 1; cnt < nMaterial; cnt++)
	{
		MatCnt = RendMatrialList[cnt];
		if ((smRendMaterial[MatCnt].MeshState&sMATS_SCRIPT_RENDLATTER) == 0)
			TotalRendCnt += RenderD3D(MatCnt);
		else
		{
			if (RendLatterCount < 1024)
				RendLatterBuff[RendLatterCount++] = MatCnt;
			else
				TotalRendCnt += RenderD3D(MatCnt);
		}
	}

	for (cnt = 0; cnt < RendLatterCount; cnt++)
		TotalRendCnt += RenderD3D(RendLatterBuff[cnt]);

	if (ZWriteAuto)
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	return TotalRendCnt;
}
void smSetRendLightVect(int x, int y, int z)
{
	pLight.x = x;
	pLight.y = y;
	pLight.z = z;
}