#include "StdAfx.h"
#include "smwsock.h"
#include "character.h"
#include "playmain.h"
#include "FullZoomMap.h"


#define DMAX_fzmcp_DRAW_TYPE			2
#define DMAX_fzm_CHAR_POS				6

#define dMAX_FZM_EFFECT_SUBNUM			10
#define dMAX_NAME_EFFECT				20
#define	dMAX_FZM_CHAR_POS				6


enum EFzmcpDrawType
{
	EFZMCP_LEFT_TOP = 0,	// �������.
	EFZMCP_LEFT_BOTTOM = 1,	// �����ϴ�.
};

//
enum EFzmNameType
{
	EPilait = 1,	// �ʶ���.
	Efallfore_1 = 2,	// �ٶ��� �̲��� ��.
	Efallfore_2 = 3,	// ����� ���.
	Efallfore_3 = 4,	// Ȳȥ�� ��.
	EMcavet = 5,	// ��������.
	Efallfore_4 = 6,	// ������ ��.
	ERuin_3 = 7,	// ���̳� ������.
	Edunt = 8,	// ��� ����.
	ERuin_4 = 9,	// ���ֹ��� ��.
	ERuin_2 = 10,	// �󼺰�.
	ERuin_1 = 11,	// ������� �Ƚ�ó.
	ETcavet = 12,	// ���� ����.
	Efore_3 = 13,	// ��ī�þ� ��.
	Efore_2 = 14,	// �볪�� ��.
	Efore_1 = 15,	// ������ ����.
	ERicaT = 16,	// ��ī����.
	Ede_1 = 17,	// ������ ��.
	Ede_nv = 18,	// �׺���.
	Ede_2 = 19,	// ���ƽý�.
	Ede_3 = 20,	// ������� ����.
	Esint = 21,	// ���ֹ��� ����.
	Ede_4 = 22,	// �ݴ��� ��.
	Eiron_1 = 23,	// ȥ���� ö��.
	EDcavet = 24,	// ����� ����.
	Eiron_2 = 25,	// ����� ����.
	Eyura_1 = 26,   // ���� ������.
	EIce_1 = 27,   // ���̽� �ʵ�
	EGreedy = 28,   // �׸��� ȣ��
	EIce_2 = 29,   // ���̽� �ʵ� 2
	ELost_1 = 30,   // �ν�Ʈ ���Ϸ���
	ELost_2 = 31,	// �ν�Ʈ ����
	EFzmNameMax = 31,   // �ƽ� �ε��� 
};


//
struct SFullZoomMapInfo
{
	EFzmNameType			eNameType;
	int						iNamePosX;
	int						iNamePosY;

	EFzmcpDrawType			eFzmcpDrawType;
	int						iFzmCharPosX;
	int						iFzmCharPosY;

	int						iZoomMapIsCharPos;
	float					fRatio;
};

//
struct SFullZoomMapImage
{
	int						iCheckWideh;
	int						iCheckHeight;
	smTEXTUREHANDLE	*lpDDS_Name;

	int						iMapOffset_x;
	int						iMapOffset_y;
};

//
struct SMapStageInfo
{
	RECT			rcStageMapRect;
	int				iStageWidth;
	int				iStageHeight;
	float			fRatio;
};

//
struct SFullZoomMapEffectInfo
{
	int				MaxFrameNum;
	int				DelayTime[dMAX_FZM_EFFECT_SUBNUM];
	BYTE		    BlendNum[dMAX_FZM_EFFECT_SUBNUM];
	int				ScaleNum[dMAX_FZM_EFFECT_SUBNUM];
};

//
enum EFzmEffectType
{
	NAME_EFFECT = 1,
	CHAR_POS_EFFECT = 2,
	CHAR_POS_NAME_EFFECT = 3,
};

//
struct SFullZoomMapEffect
{
	EFzmEffectType				eEffectType;
	SFullZoomMapEffectInfo	   *lpEffectInfo;

	int				Life;
	int				FrameTime;
	int				FrameNum;
	int				EventNum;
	POINT			Pos;
	int				HalfSize;
	float			fBlendNum;
	float			fBlendStep;
	float			fScaleNum;
	float			fScaleStep;
};

//
enum ECharType
{
	USER_CHAR = 1,
	PARTY_CHAR = 2,
};

//
struct SFzmCharPos
{
	ECharType		eCharType;
	int				iXpos;
	int				iYpos;
};


//######################################################################################
//
static POINT				s_FzmcpInfo[DMAX_fzm_CHAR_POS] =
{
	{0, 0 }, {10, 0 }, {20, 0 },
	{0, 10}, {10, 10}, {20, 10},
};

//
static int					s_FzmcpIndex[DMAX_fzmcp_DRAW_TYPE][DMAX_fzm_CHAR_POS] =
{
	{0,1,2,3,4,5},
	{3,4,5,0,1,2},
};
static SFullZoomMapInfo		s_FzmInfo[EFzmNameMax] =
{
	{ EPilait    ,440, 18, EFZMCP_LEFT_TOP   ,440, 32 ,1,508.f },					// 0.  �ʶ���.
	{ Efallfore_1,412, 68, EFZMCP_LEFT_TOP	 ,466, 68 ,1,0 },						// 1.  �ٶ��� �̲��� ��.
	{ Efallfore_2,411,143, EFZMCP_LEFT_BOTTOM,411, 122,1,0 },						// 2.  ����� ���.
	{ Efallfore_3,480,177, EFZMCP_LEFT_TOP	 ,480, 191,1,0 },						// 3.  Ȳȥ�� ��.
	{ EMcavet	 ,397,191, EFZMCP_LEFT_TOP	 ,397, 205,0,0 },						// 4.  ��������.
	{ Efallfore_4,535,216, EFZMCP_LEFT_TOP	 ,535, 230,1,0 },						// 5.  ������ ��.
	{ ERuin_3	 ,456,271, EFZMCP_LEFT_TOP	 ,493, 271,1,0 },						// 6.  ���̳� ������.
	{ Edunt		 ,551,298, EFZMCP_LEFT_BOTTOM,569, 276,0,0 },						// 7.  ��� ����.
	{ ERuin_4	 ,535,327, EFZMCP_LEFT_TOP	 ,535, 341,1,0 },						// 8.  ���ֹ��� ��.
	{ ERuin_2	 ,461,336, EFZMCP_LEFT_TOP	 ,461, 350,1,0 },						// 9.  �󼺰�.
	{ ERuin_1	 ,490,392, EFZMCP_LEFT_TOP	 ,539, 392,1,0 },						// 10. ������� �Ƚ�ó.
	{ ETcavet	 ,362,386, EFZMCP_LEFT_BOTTOM,381, 365,0,0 },						// 11. ���� ����.
	{ Efore_3	 ,358,424, EFZMCP_LEFT_TOP	 ,380, 438,1,0 },						// 12. ��ī�þ� ��.
	{ Efore_2	 ,413,464, EFZMCP_LEFT_BOTTOM,436, 443,1,0 },						// 13. �볪�� ��.
	{ Efore_1	 ,505,449, EFZMCP_LEFT_TOP	 ,505, 463,1,0 },						// 14. ������ ����.
	{ ERicaT	 ,502,513, EFZMCP_LEFT_TOP	 ,502, 527,1,477.f },					// 15. ��ī����.
	{ Ede_1		 ,568,376, EFZMCP_LEFT_TOP	 ,588, 391,1,0 },						// 16. ������ ��.
	{ Ede_nv	 ,621,403, EFZMCP_LEFT_BOTTOM,640, 382,1,0 },						// 17. �׺���.
	{ Ede_2		 ,636,460, EFZMCP_LEFT_TOP	 ,636, 474,1,0 },						// 18. ���ƽý�.
	{ Ede_3		 ,678,372, EFZMCP_LEFT_TOP	 ,678, 386,1,0 },						// 19. ������� ����.
	{ Esint		 ,682,417, EFZMCP_LEFT_TOP	 ,733, 417,0,0 },						// 20. ���ֹ��� ����.
	{ Ede_4		 ,655,314, EFZMCP_LEFT_TOP	 ,710, 314,1,0 },						// 21. �ݴ��� ��.
	{ Eiron_1	 ,746,249, EFZMCP_LEFT_TOP	 ,752, 277,1,0 },						// 22. ȥ���� ö��.
	{ EDcavet	 ,367,296, EFZMCP_LEFT_TOP	 ,376, 325,1,0 },						// 23. ����� ����.
	{ Eiron_2	 ,653,248, EFZMCP_LEFT_TOP	 ,663, 270,1,352.f },					// 24. ����� ����.
	{ Eyura_1    ,588,178, EFZMCP_LEFT_TOP	 ,598, 205,1,378.f },					// 25. ���� ������.
	{ EIce_1     ,655,166, EFZMCP_LEFT_TOP	 ,659, 182,1,0 },					    // 26. ���̽� �ʵ�.
	{ EGreedy    ,565,267, EFZMCP_LEFT_TOP	 ,565, 267,1,0 },					    // 27. �׸��� ȣ��.
	{ EIce_2     ,712,97 , EFZMCP_LEFT_TOP	 ,712, 97 ,1,0 },					    // 28. ���̽� �ʵ�2.
	{ ELost_1	 ,595,530, EFZMCP_LEFT_BOTTOM,596, 533,1,0 },					    // 29. �ν�Ʈ ���Ϸ���
	{ ELost_2	 ,578,477, EFZMCP_LEFT_TOP	 ,578, 477,1,0 },					    // 30. �ν�Ʈ ���� 

};
static int s_iFzmFieldCodeInfo[] =
{
	12, // ��ī�þ� ��.
		13, // �볪�� ��.
		14, // ������ ����.
		15, // ��ī����.
		10, // ������� �Ƚ�ó.
		9,  // �󼺰�.
		6,  // ���̳� ������.
		8,  // ���ֹ��� ��.
		16, // ������ ��.
		17, // �׺���.
		18, // ���ƽý�.
		19, // ������� ����.
		21, // �ݴ��� ��.
		7,  // ��� ����. (1��)
		7,  // ��� ����. (2��)
		7,  // ��� ����. (3��)
		7,  // �����.
		5,  // ������ ��.
		3,  // Ȳȥ�� ��.
		2,  // ����� ���.
		1,  // �ٶ��� �̲��� ��.
		0,  // �ʶ���.
		20, // ���ֹ��� ����. (1��)
		20, // ���ֹ��� ����. (2��)
		11, // ���� ����.
		4,  // ��������.
		23, // ����� ����.
		22, // ȥ���� ö��.
		24,	// ����� ����.
		25, // ���� ������.	
		4,	// SOD
		26, // ���̽� �ʵ�
		4,  // ������
		4,  // �����ʵ�
		27, // �׸��� ȣ��
		28, // ���̽� �ʵ�2
		// ���� ���ġ ����.	
		4,
		29, // �ν�Ʈ ���Ϸ���			
		30, // �ν�Ʈ ����
		4,
		30, // �޾�֮��1
		30, // �޾�֮��2
		20, // ��������3
		30, // �޾�֮��3
		28,  // ���ⶴѨ
		4,	// ��ά˹�˶�Ѩ
		4,	// ��˶�Ѩ
		4,	// ��ʧ����
		4,4,4,4,	// �Ŵ�ɭ��
		4,4,4,4,	// �þ�ɳĮ
		4,	// ��·3
		4,	// ����BOSS
};

//
static char	*s_lpFzmINamePtrBuff[EFzmNameMax * 2] =			//�̴ϸ� �̸� ,�̴ϸ� �̹���
{
	// �ʶ���.
	"Pilait.bmp",
		"town_PLX-40Y-36.bmp",

		// �ٶ��� �̲��� ��.
		"fallfore-1t.bmp",
		"fallfore-1X70.bmp",

		// ����� ���.
		"fallfore-2t.bmp",
		"fallfore-2X10.bmp",

		// Ȳȥ�� ��.
		"fallfore-3t.bmp",
		"fallfore-3X5.bmp",

		// ��������.
		"_Mcavet.bmp",
		"dun.bmp",				// �ߺ�. ���� �Ѵ�.

		// ������ ��.
		"fallfore-4t.bmp",
		"fallfore-4X30.bmp",

		// ���̳� ������.
		"Ruin-3t.bmp",
		"Ruin-3Y10.bmp",

		// ��� ����.
		"_dunt.bmp",
		"@4",					// "dun.bmp"

		// ���ֹ��� ��.
		"Ruin-4t.bmp",
		"Ruin-4X40.bmp",

		// �󼺰�.
		"Ruin-2t.bmp",
		"Ruin-2X0.bmp",

		// ������� �Ƚ�ó.
		"Ruin-1t.bmp",
		"Ruin-1X10.bmp",

		// ���� ����.
		"_Tcavet.bmp",
		"@4",					// "dun.bmp"

		// ��ī�þ� ��.
		"fore-3t.bmp",
		"fore-3X2Y20.bmp",

		// �볪�� ��.
		"fore-2t.bmp",
		"fore-2Y-5.bmp",

		// ������ ����.
		"fore-1t.bmp",
		"fore-1X20.bmp",

		// ��ī����.
		"town_RicaT.bmp",
		"town_RicaX-88Y-77.bmp",

		// ������ ��.
		"de-1t.bmp",
		"de-1X30.bmp",

		// �׺���.
		"de-NVt.bmp",
		"de-NVY40.bmp",

		// ���ƽý�.
		"de-2t.bmp",
		"de-2X30.bmp",

		// ������� ����.
		"de-3t.bmp",
		"de-3Y20.bmp",

		// ���ֹ��� ����.
		"_sint.bmp",
		"@4",					// "dun.bmp"

		// �ݴ��� ��.
		"de-4t.bmp",
		"de-4Y30.bmp",

		// ȥ���� ö��.
		"iron-1t.bmp",
		"iron-1X40.bmp",

		// ����� ����.
		"_Dcavet.bmp",
		"@4",					// "dun.bmp"

		// ����� ����.
		"iron_2t.bmp",
		"iron2X-15Y14.bmp",

		// ���� ������.
		"yura_1t.bmp",
		"yuraX15Y-22.bmp",

		//���̽� �ʵ�
		"ice1-x655y166.bmp",
		"ice1_X40Y3.bmp",

		//�׸��� ȣ��
		"greedy_x565y267.bmp",
		"greedy_x-15y-28.bmp",

		//���̽��ʵ�2
		"ice2-x712y97.bmp",
		"ice2_X0Y0.bmp",

		//�ν�Ʈ ���Ϸ��� 
		"Lost-1t.bmp",
		"lost-1t_x0_y0.bmp",

		//�ν�Ʈ ���� 
		"lost-2_x579y478.bmp",
		"lost-2_x0_y0.bmp"

};

//
static int s_iFzmMapOffset[EFzmNameMax][2] =
{
	{-40, -36}, // �ʶ���.
	{ 70,   0}, // �ٶ��� �̲��� ��.
	{ 10,   0}, // ����� ���.
	{  5,   0}, // Ȳȥ�� ��.
	{  0,   0}, // ��������.
	{ 30,   0}, // ������ ��.
	{  0,  10}, // ���̳� ������.
	{  0,   0}, // ��� ����.
	{ 40,   0}, // ���ֹ��� ��.
	{  0,   0}, // �󼺰�.
	{ 10,   0}, // ������� �Ƚ�ó.
	{  0,   0}, // ���� ����.
	{  2,  20}, // ��ī�þ� ��.
	{  0,  -5}, // �볪�� ��.
	{ 20,   0}, // ������ ����.
	{-88, -77}, // ��ī����.
	{ 30,   0}, // ������ ��.
	{  0,  40}, // �׺���.
	{ 30,   0}, // ���ƽý�.
	{  0,  20}, // ������� ����.
	{  0,   0}, // ���ֹ��� ����.
	{  0,  30}, // �ݴ��� ��.
	{ 40,   0}, // ȥ���� ö��.
	{  0,   0}, // ����� ����.
	{-15,  14}, // ����� ����.
	{ 15, -22}, // ���� ������.
	{ 40,   3}, // ���̽� �ʵ�
	{ 15,  -4}, // �׸��� ȣ��
	{ 20,  -4}, // ���̽� �ʵ� 2
	{ 30,  18}, // �ν�Ʈ ���Ϸ���
	{ 7 ,  38}, // �ν�Ʈ ����
};

//
static SFullZoomMapEffectInfo   s_NameEffectDataInfo =
{
	{  3 },
	{  0,  16, 30, 0,},
	{100, 255, 20, 0,},
	{  0,  12, 24, 0,},
};

//
static SFullZoomMapEffectInfo   s_CharPosEffectDataInfo =
{
	{  4 },
	{  0,  20,  30,  30, 0, },
	{255, 255, 255, 100, 0, },
	{  0,   6,   6,   6, 0, },
};


//######################################################################################
//
extern float g_fWinSizeRatio_X;
extern float g_fWinSizeRatio_Y;

extern int MatArrow;
extern int psDrawTexImage2(smTEXTUREHANDLE *hTexHandle, float *x, float *y, float fx, float fy, float fw, float fh, int Transp, int specular);

//
static void	CreateFullZoomMap(void);
static void DestroyFullZoomMap(void);
static int  LoadZoomInMap(SFullZoomMapInfo  *lpZoomMapInfo);
static void	SetFzmEffect(EFzmEffectType eEffectType, SFullZoomMapEffectInfo *lpEffectInfo, int EventNum, int ActiveName);
static void	MainFzmEffect(void);
static void	DrawFzmEffect(void);
static void	SetMapStageInfo(void);
static void	SetFzmCharPos(void);

//
static SMapStageInfo			s_MapStageInfoBuff[256];
static SFullZoomMapImage		s_FzmImage[EFzmNameMax];

static int						s_iMouseLButtonState[2] = { -1,-1 };
static POINT					s_CurPlayerPos;
static int						s_iFzmActiveName = -1;
static int						s_iFzmFocusName = -1;
static smTEXTUREHANDLE		*s_lpDDS_FzmActiveMap;

static smTEXTUREHANDLE		*s_lpDDS_Exit;
static smTEXTUREHANDLE		*s_lpDDS_ExitImage;
static smTEXTUREHANDLE		*s_lpDDS_ExitFocusImage;
static POINT					s_ExitButtonPos;

static SFullZoomMapEffect		s_NameEffectBuff[dMAX_NAME_EFFECT];
static int						s_iFzmNameEffectMatNum;

static int						s_iFzmCharPosNameEffectTime;

static SFzmCharPos				s_FzmCharPosBuff[dMAX_FZM_CHAR_POS];
static int						s_iFzmCharPosNum;

static smTEXTUREHANDLE		*s_lpDDS_FullMapImage;
static int						s_iFzmUserLargeMatNum;
static int						s_iFzmPartyLargeMatNum;
static int						s_iFzmUserSmallMatNum;

//
int								g_iFzmCursorFocusGame;

int								g_iFzmCursorPosX;
int								g_iFzmCursorPosY;
int								g_FzmMouseButton[3];


//######################################################################################
//�� �� �� : 2004-04-08 ���� 3:27:06
//�� �� �� :
//��    �� :
//�� �� �� : �� �� ��
//######################################################################################
static void SetFzmEffect(EFzmEffectType eEffectType, SFullZoomMapEffectInfo *lpEffectInfo, int EventNum, int ActiveName)
{
	if (ActiveName < 0)
		return;

	for (int i = 0; i < dMAX_NAME_EFFECT; i++)
	{
		if (s_NameEffectBuff[i].Life == 0)
		{
			SFullZoomMapInfo  *lpZoomMapInfo = &s_FzmInfo[ActiveName];
			SFullZoomMapImage *lpZoomMapImage = &s_FzmImage[lpZoomMapInfo->eNameType - 1];

			::ZeroMemory(&s_NameEffectBuff[i], sizeof(s_NameEffectBuff[i]));
			s_NameEffectBuff[i].lpEffectInfo = lpEffectInfo;
			s_NameEffectBuff[i].eEffectType = eEffectType;

			s_NameEffectBuff[i].Life = 1;
			s_NameEffectBuff[i].EventNum = EventNum;
			s_NameEffectBuff[i].Pos.x = lpZoomMapInfo->iNamePosX + (lpZoomMapImage->iCheckWideh >> 1);
			s_NameEffectBuff[i].Pos.y = lpZoomMapInfo->iNamePosY + (lpZoomMapImage->iCheckHeight >> 1);
			s_NameEffectBuff[i].HalfSize = 8;
			s_NameEffectBuff[i].fBlendNum = float(lpEffectInfo->BlendNum[0]);
			s_NameEffectBuff[i].fScaleNum = float(lpEffectInfo->ScaleNum[0]);
			return;
		}
	}
}
static void MainFzmEffect(void)
{
	//
	static int iFieldCode;
	if (s_iFzmCharPosNameEffectTime > 160)
	{
		if (lpCurPlayer->iLoadedMapIndex >= 0)
		{
			iFieldCode = STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID;
			SetFzmEffect(CHAR_POS_NAME_EFFECT, &s_NameEffectDataInfo, 2, s_iFzmFieldCodeInfo[iFieldCode]);
		}

		s_iFzmCharPosNameEffectTime = 0;
	}
	else
		s_iFzmCharPosNameEffectTime++;

	for (int i = 0; i < dMAX_NAME_EFFECT; i++)
	{
		if (s_NameEffectBuff[i].Life)
		{
			SFullZoomMapEffect *lpNameEffect = &s_NameEffectBuff[i];
			lpNameEffect->FrameTime++;

			if (lpNameEffect->FrameTime >= lpNameEffect->lpEffectInfo->DelayTime[lpNameEffect->FrameNum])
			{
				lpNameEffect->FrameNum++;
				if (lpNameEffect->EventNum == lpNameEffect->FrameNum)
				{
					if (lpNameEffect->eEffectType == NAME_EFFECT)
						SetFzmEffect(NAME_EFFECT, &s_NameEffectDataInfo, 0, s_iFzmActiveName);
					else if (lpNameEffect->eEffectType == CHAR_POS_EFFECT)
						SetFzmEffect(CHAR_POS_EFFECT, &s_CharPosEffectDataInfo, 3, s_iFzmActiveName);
					else if (lpNameEffect->eEffectType == CHAR_POS_NAME_EFFECT)
						SetFzmEffect(CHAR_POS_NAME_EFFECT, &s_NameEffectDataInfo, 0, s_iFzmFieldCodeInfo[iFieldCode]);
				}

				if (lpNameEffect->FrameNum >= lpNameEffect->lpEffectInfo->MaxFrameNum)
					lpNameEffect->Life = 0;
				else
				{
					lpNameEffect->FrameTime = 0;
					lpNameEffect->fBlendNum = float(lpNameEffect->lpEffectInfo->BlendNum[lpNameEffect->FrameNum - 1]);
					lpNameEffect->fScaleNum = float(lpNameEffect->lpEffectInfo->ScaleNum[lpNameEffect->FrameNum - 1]);

					float fDelayTime = float(lpNameEffect->lpEffectInfo->DelayTime[lpNameEffect->FrameNum]);
					lpNameEffect->fBlendStep = (lpNameEffect->lpEffectInfo->BlendNum[lpNameEffect->FrameNum] - lpNameEffect->fBlendNum) / fDelayTime;
					lpNameEffect->fScaleStep = (lpNameEffect->lpEffectInfo->ScaleNum[lpNameEffect->FrameNum] - lpNameEffect->fScaleNum) / fDelayTime;
				}
			}
			else
			{
				lpNameEffect->fBlendNum += lpNameEffect->fBlendStep;
				lpNameEffect->fScaleNum += lpNameEffect->fScaleStep;
			}
		}
	}
}
static void DrawFzmEffect(void)
{
	for (int i = 0; i < dMAX_NAME_EFFECT; i++)
	{
		if (s_NameEffectBuff[i].Life && s_NameEffectBuff[i].eEffectType != CHAR_POS_EFFECT)
		{
			SFullZoomMapEffect *lpNameEffect = &s_NameEffectBuff[i];

			DrawFzmBackToTexture2D(smMaterial[s_iFzmNameEffectMatNum].smTexture[0], lpNameEffect->Pos.x, lpNameEffect->Pos.y, 0, lpNameEffect->HalfSize + int(lpNameEffect->fScaleNum), int(lpNameEffect->fBlendNum));
		}
	}
}
static void SetMapStageInfo(void)
{
	FILE *fp = NULL;

	fopen_s(&fp, "image\\GuideMap\\StageInfo.dat", "rb");
	if (fp)
	{
		fread(s_MapStageInfoBuff, sizeof(s_MapStageInfoBuff), 1, fp);
		fclose(fp);
	}
#ifdef _DEBUG
	else
	{
		smSTAGE3D			 MapStage;
		SFullZoomMapInfo	*lpZoomMapInfo;
		int					 Width, Height;
		float				 fRatio;

		MapStage.Init();
		for (int i = 0; i < NUM_MAPS; i++)
		{
			BaseMap * pcMap = GAMEMAP->pcaBaseMap + i;

			if (smSTAGE3D_ReadASE(pcMap->szStageFilePath, &MapStage))
			{
				::CopyMemory(&s_MapStageInfoBuff[i].rcStageMapRect, &MapStage.StageMapRect, sizeof(RECT));
				s_MapStageInfoBuff[i].iStageWidth = MapStage.StageMapRect.right - MapStage.StageMapRect.left;
				s_MapStageInfoBuff[i].iStageHeight = MapStage.StageMapRect.bottom - MapStage.StageMapRect.top;

				Width = s_MapStageInfoBuff[i].iStageWidth;
				Height = s_MapStageInfoBuff[i].iStageHeight;

				lpZoomMapInfo = &s_FzmInfo[s_iFzmFieldCodeInfo[i]];
				if (lpZoomMapInfo->fRatio)
				{
					if (Width > Height)
						fRatio = float(Width) / lpZoomMapInfo->fRatio;
					else
						fRatio = float(Height) / lpZoomMapInfo->fRatio;
				}
				else
				{
					if (Width > Height)
						fRatio = float(Width) / 320.f;
					else
						fRatio = float(Height) / 320.f;
				}

				s_MapStageInfoBuff[i].fRatio = fRatio;

				MapStage.Close();
				MapStage.Init();
			}
		}

		fopen_s(&fp, "image\\GuideMap\\StageInfo.dat", "wb");
		if (fp)
		{
			fwrite(s_MapStageInfoBuff, sizeof(s_MapStageInfoBuff), 1, fp);
			fclose(fp);
		}
	}
#endif
}
static void SetFzmCharPos(void)
{
	if (s_iFzmActiveName < 0)
		return;
	s_iFzmCharPosNum = 0;

	SFullZoomMapInfo  *lpZoomMapInfo = &s_FzmInfo[s_iFzmActiveName];
	SFullZoomMapImage *lpZoomMapImage = &s_FzmImage[lpZoomMapInfo->eNameType - 1];

	if (STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == MAPID_EndlessTowerF1 ||
		STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == MAPID_EndlessTowerF2 ||
		STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == MAPID_EndlessTowerF3 ||
		STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == MAPID_IceMineF1)
		return;
	if (lpZoomMapInfo->iZoomMapIsCharPos <= 0)
		return;

	int	   cnt;
	float  fRatio = 0;
	RECT  *lpRect = NULL;

	// User ////////////////////////////////////////////////////////////////////////
	if (lpCurPlayer->iLoadedMapIndex >= 0)
	{
		int iFieldCode = STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID;
		if (s_iFzmActiveName == s_iFzmFieldCodeInfo[iFieldCode])
		{

			lpRect = &s_MapStageInfoBuff[iFieldCode].rcStageMapRect;
			fRatio = s_MapStageInfoBuff[iFieldCode].fRatio;

			s_FzmCharPosBuff[s_iFzmCharPosNum].eCharType = USER_CHAR;

			s_FzmCharPosBuff[s_iFzmCharPosNum].iXpos = int(float(lpCurPlayer->pX - lpRect->left) / fRatio);
			s_FzmCharPosBuff[s_iFzmCharPosNum].iYpos = int(float(lpRect->bottom - lpCurPlayer->pZ) / fRatio);
			s_iFzmCharPosNum++;
		}
	}
	if (InterfaceParty.PartyMemberCount)
	{
		if (s_iFzmCharPosNum <= 0)
		{
			for (cnt = 0; cnt < NUM_MAPS; cnt++)
			{
				if (s_iFzmActiveName == s_iFzmFieldCodeInfo[cnt])
				{
					lpRect = &s_MapStageInfoBuff[cnt].rcStageMapRect;
					fRatio = s_MapStageInfoBuff[cnt].fRatio;
					break;
				}
			}
		}

		if (lpRect == NULL)
			return;

		for (cnt = 0; cnt < InterfaceParty.PartyMemberCount; cnt++)
		{
			if (InterfaceParty.PartyMember[cnt].ChrCode != lpCurPlayer->iID)
			{
				POINT3D *lpChPos = &InterfaceParty.PartyMember[cnt].CharacterPos;
				if (lpChPos->x > lpRect->left && lpChPos->x < lpRect->right &&
					lpChPos->z > lpRect->top  && lpChPos->z < lpRect->bottom)
				{
					if (s_iFzmCharPosNum >= dMAX_FZM_CHAR_POS)
						return;

					s_FzmCharPosBuff[s_iFzmCharPosNum].eCharType = PARTY_CHAR;
					s_FzmCharPosBuff[s_iFzmCharPosNum].iXpos = int(float(lpChPos->x - lpRect->left) / fRatio);
					s_FzmCharPosBuff[s_iFzmCharPosNum].iYpos = int(float(lpRect->bottom - lpChPos->z) / fRatio);
					s_iFzmCharPosNum++;
				}
			}
		}
	}
}
static void CreateFullZoomMap(void)
{
	if (g_IsDxProjectZoomIn > 0)
		return;

	char szFullName[128];
	char szDirectory[32];
	lstrcpy(szDirectory, "image\\GuideMap\\");

	CopyMemory(szFullName, szDirectory, 32);
	lstrcat(szFullName, "_AFull.bmp");
	s_lpDDS_FullMapImage = LoadDibSurfaceOffscreen(szFullName);

	CopyMemory(szFullName, szDirectory, 32);
	lstrcat(szFullName, "exit_1.bmp");
	s_lpDDS_ExitImage = LoadDibSurfaceOffscreen(szFullName);

	s_lpDDS_Exit = s_lpDDS_ExitImage;
	s_ExitButtonPos.x = 682;
	s_ExitButtonPos.y = 547;

	CopyMemory(szFullName, szDirectory, 32);
	lstrcat(szFullName, "exit_2.bmp");
	s_lpDDS_ExitFocusImage = LoadDibSurfaceOffscreen(szFullName);

	for (int i = 0; i < EFzmNameMax; i++)
	{
		CopyMemory(szFullName, szDirectory, 32);
		lstrcat(szFullName, s_lpFzmINamePtrBuff[i * 2]);
		s_FzmImage[i].lpDDS_Name = LoadDibSurfaceOffscreen(szFullName);

		if (s_FzmImage[i].lpDDS_Name)
		{
			s_FzmImage[i].iCheckWideh = s_FzmImage[i].lpDDS_Name->Width;
			s_FzmImage[i].iCheckHeight = s_FzmImage[i].lpDDS_Name->Height;
		}

		s_FzmImage[i].iMapOffset_x = s_iFzmMapOffset[i][0];
		s_FzmImage[i].iMapOffset_y = s_iFzmMapOffset[i][1];
	}

	SetMapStageInfo();
}
static void DestroyFullZoomMap(void)
{
	DELET(s_lpDDS_FullMapImage);
	DELET(s_lpDDS_ExitImage);
	DELET(s_lpDDS_ExitFocusImage);

	for (int i = 0; i < EFzmNameMax; i++)
	{
		DELET(s_FzmImage[i].lpDDS_Name);
	}

	DELET(s_lpDDS_FzmActiveMap);
}
static int LoadZoomInMap(SFullZoomMapInfo  *lpZoomMapInfo)
{
	if (lpZoomMapInfo == NULL)
		return FALSE;

	char szFullName[128] = { 0, };
	::lstrcpy(szFullName, "image\\GuideMap\\");

	int index = ((lpZoomMapInfo->eNameType - 1) << 1) + 1;
	if (*s_lpFzmINamePtrBuff[index] != '@')
		::lstrcat(szFullName, s_lpFzmINamePtrBuff[index]);
	else
	{
		index = ::atoi(s_lpFzmINamePtrBuff[index] + 1);
		::lstrcat(szFullName, s_lpFzmINamePtrBuff[(index << 1) + 1]);
	}

	smTEXTUREHANDLE *lpDDS_FzmActiveMap = LoadDibSurfaceOffscreen(szFullName);
	if (lpDDS_FzmActiveMap == NULL)
		return FALSE;

	DELET(s_lpDDS_FzmActiveMap);

	s_lpDDS_FzmActiveMap = lpDDS_FzmActiveMap;
	return TRUE;
}

void CreateBeforeFullZoomMap(void)
{
	s_iFzmNameEffectMatNum = cSinWarpGate.MatSelect;

	s_iFzmUserLargeMatNum = MatArrow;
	s_iFzmPartyLargeMatNum = CreateTextureMaterial("image\\GuideMap\\User_P.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	s_iFzmUserSmallMatNum = CreateTextureMaterial("image\\GuideMap\\User_PSR.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
}

void DrawFzmBackToSurface(int dest_x, int dest_y, smTEXTUREHANDLE *lpDDS, int x, int y, int width, int height)
{
	RECT destRect;
	destRect.left = int(dest_x * g_fWinSizeRatio_X);
	destRect.top = int(dest_y * g_fWinSizeRatio_Y);
	destRect.right = int((dest_x + width)  * g_fWinSizeRatio_X);
	destRect.bottom = int((dest_y + height) * g_fWinSizeRatio_Y);

	RECT srcRect;
	srcRect.left = x;
	srcRect.top = y;
	srcRect.right = width;
	srcRect.bottom = height;

	if (lpDDS)
		dsDrawTexImage(lpDDS, &destRect, &srcRect);
}
void DrawFzmBackToTexture2D(smTEXTUREHANDLE *hTexHandle, int X, int Y, int Angle, int HalfSize, int Blend)
{
	int ix[4], iy[4];
	ix[0] = -HalfSize; iy[0] = -HalfSize;
	ix[1] = -HalfSize; iy[1] = HalfSize;
	ix[2] = HalfSize; iy[2] = -HalfSize;
	ix[3] = HalfSize; iy[3] = HalfSize;

	int cnt;
	float fx[4], fy[4];

	if (Angle)
	{
		int sinY = GetSin[Angle & ANGCLIP];
		int cosY = GetCos[(Angle + ANGLE_180) & ANGCLIP];

		for (cnt = 0; cnt < 4; cnt++)
		{
			fx[cnt] = (float)((iy[cnt] * sinY + ix[cnt] * cosY) >> 8);
			fy[cnt] = (float)((iy[cnt] * cosY - ix[cnt] * sinY) >> 8);
			fx[cnt] /= 256;
			fy[cnt] /= 256;
			fx[cnt] += (float)X;
			fy[cnt] += (float)Y;
		}
	}
	else
	{
		for (cnt = 0; cnt < 4; cnt++)
		{
			fx[cnt] = float(ix[cnt] + X);
			fy[cnt] = float(iy[cnt] + Y);
		}
	}

	for (cnt = 0; cnt < 4; cnt++)
	{
		fx[cnt] *= g_fWinSizeRatio_X;
		fy[cnt] *= g_fWinSizeRatio_Y;
	}

	psDrawTexImage2(hTexHandle, fx, fy, 0, 0, 1, 1, Blend, 0);
}


//######################################################################################
//�� �� �� : 2004-04-08 ���� 3:31:43
//�� �� �� :
//��    �� :
//�� �� �� : �� �� ��
//######################################################################################
int SetFullZoomMap(int IsSet)
{
	if (IsSet)
	{
		SFullZoomMapInfo *lpZoomMapInfo;
		int				  iFieldCode;

		if (lpCurPlayer->iLoadedMapIndex >= 0)
		{
			iFieldCode = STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID;

			s_iFzmActiveName = s_iFzmFieldCodeInfo[iFieldCode];
			if (iFieldCode == 40 || iFieldCode == 41 || iFieldCode == 43 || iFieldCode == 44)
				lpZoomMapInfo = &s_FzmInfo[4];
			else
				lpZoomMapInfo = &s_FzmInfo[s_iFzmActiveName];

			LoadZoomInMap(lpZoomMapInfo);
		}
		else
		{
			s_iFzmActiveName = 0;
			lpZoomMapInfo = &s_FzmInfo[s_iFzmActiveName];

			LoadZoomInMap(lpZoomMapInfo);
		}

		if (g_IsDxProjectZoomIn <= 0)
		{
			CreateFullZoomMap();
			g_IsDxProjectZoomIn = 1;
			SetFzmEffect(CHAR_POS_EFFECT, &s_CharPosEffectDataInfo, 3, s_iFzmActiveName);
		}

		return 1;
	}
	else
	{
		DestroyFullZoomMap();

		g_IsDxProjectZoomIn = 0;
		s_iFzmCharPosNameEffectTime = 0;

		ZeroMemory(s_NameEffectBuff, sizeof(s_NameEffectBuff));
		s_iFzmFocusName = -1;
		s_iFzmActiveName = -1;
		g_FzmMouseButton[0] = FALSE;
		g_FzmMouseButton[1] = FALSE;
		g_FzmMouseButton[2] = FALSE;
		return 1;
	}
}

void DrawFullZoomMapCharPos(void)
{
	SFullZoomMapInfo  *lpZoomMapInfo;
	SFullZoomMapImage *lpZoomMapImage;

	if (s_iFzmCharPosNum > 0 && s_iFzmActiveName >= 0)
	{
		lpZoomMapInfo = &s_FzmInfo[s_iFzmActiveName];
		lpZoomMapImage = &s_FzmImage[lpZoomMapInfo->eNameType - 1];

		for (int cnt = 0; cnt < s_iFzmCharPosNum; cnt++)
		{
			switch (s_FzmCharPosBuff[cnt].eCharType)
			{
			case USER_CHAR:
				for (int i = 0; i < dMAX_NAME_EFFECT; i++)
				{
					if (s_NameEffectBuff[i].Life && s_NameEffectBuff[i].eEffectType == CHAR_POS_EFFECT)
					{
						SFullZoomMapEffect *lpCharPosEffect = &s_NameEffectBuff[i];

						DrawFzmBackToTexture2D(smMaterial[s_iFzmUserLargeMatNum].smTexture[0],
							30 + lpZoomMapImage->iMapOffset_x + s_FzmCharPosBuff[cnt].iXpos,
							15 + lpZoomMapImage->iMapOffset_y + s_FzmCharPosBuff[cnt].iYpos,
							lpCurPlayer->Angle.y,
							lpCharPosEffect->HalfSize + int(lpCharPosEffect->fScaleNum),
							int(lpCharPosEffect->fBlendNum));
					}
				}
				break;

			case PARTY_CHAR:
				DrawFzmBackToTexture2D(smMaterial[s_iFzmPartyLargeMatNum].smTexture[0],
					30 + lpZoomMapImage->iMapOffset_x + s_FzmCharPosBuff[cnt].iXpos,
					15 + lpZoomMapImage->iMapOffset_y + s_FzmCharPosBuff[cnt].iYpos,
					0, 8, 255);
				break;
			}
		}
	}
}

void DrawFullZoomMap(void)
{
	SFullZoomMapInfo  *lpZoomMapInfo;
	SFullZoomMapImage *lpZoomMapImage;

	if (s_lpDDS_FzmActiveMap)
		DrawFzmBackToSurface(30, 15, s_lpDDS_FzmActiveMap, 0, 0, 320, 320);

	DrawFullZoomMapCharPos();

	DrawFzmBackToSurface(0, 0, s_lpDDS_FullMapImage, 0, 0, 800, 600);

	DrawFzmBackToSurface(s_ExitButtonPos.x, s_ExitButtonPos.y, s_lpDDS_Exit, 0, 0, 64, 34);

	if (s_iFzmFocusName >= 0 && s_iFzmFocusName != s_iFzmActiveName)
	{
		lpZoomMapInfo = &s_FzmInfo[s_iFzmFocusName];
		lpZoomMapImage = &s_FzmImage[lpZoomMapInfo->eNameType - 1];

		DrawFzmBackToSurface(lpZoomMapInfo->iNamePosX - 1, lpZoomMapInfo->iNamePosY, lpZoomMapImage->lpDDS_Name, 0, 0, lpZoomMapImage->iCheckWideh, lpZoomMapImage->iCheckHeight);
	}

	if (s_iFzmActiveName >= 0)
	{
		lpZoomMapInfo = &s_FzmInfo[s_iFzmActiveName];
		lpZoomMapImage = &s_FzmImage[lpZoomMapInfo->eNameType - 1];

		DrawFzmBackToSurface(lpZoomMapInfo->iNamePosX, lpZoomMapInfo->iNamePosY, lpZoomMapImage->lpDDS_Name, 0, 0, lpZoomMapImage->iCheckWideh, lpZoomMapImage->iCheckHeight);
	}

	DrawFzmEffect();
}


//######################################################################################
//�� �� �� : 2004-04-08 ���� 3:32:13
//�� �� �� :
//��    �� :
//�� �� �� : �� �� ��
//######################################################################################
void MainFullZoomMap(void)
{
	int st_x, st_y, end_x, end_y, i;

	if (lpCurPlayer->iLoadedMapIndex >= 0)
	{
		if (lpCurPlayer->pX != s_CurPlayerPos.x || lpCurPlayer->pZ != s_CurPlayerPos.y)
		{
			if (s_iFzmActiveName != s_iFzmFieldCodeInfo[STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID])
				SetFullZoomMap(1);
		}

		s_CurPlayerPos.x = lpCurPlayer->pX;
		s_CurPlayerPos.y = lpCurPlayer->pZ;
	}

	MainFzmEffect();

	st_x = int(682 * g_fWinSizeRatio_X);
	st_y = int(547 * g_fWinSizeRatio_Y);
	end_x = int((682 + 64) * g_fWinSizeRatio_X);
	end_y = int((547 + 34) * g_fWinSizeRatio_Y);

	if (g_iFzmCursorPosX > st_x && g_iFzmCursorPosX < end_x && g_iFzmCursorPosY > st_y && g_iFzmCursorPosY < end_y)
	{
		if (s_lpDDS_Exit == s_lpDDS_ExitImage)
		{
			s_lpDDS_Exit = s_lpDDS_ExitFocusImage;

			s_iMouseLButtonState[0] = g_FzmMouseButton[0];
			s_iMouseLButtonState[1] = -1;
		}

		if (s_iMouseLButtonState[0] == 0)
		{
			if (s_iMouseLButtonState[1] == 1)
			{
				s_ExitButtonPos.x = 682 + 1;
				s_ExitButtonPos.y = 547 + 1;

				if (g_FzmMouseButton[0] == 0)
					SetFullZoomMap(0);
			}
			else
				s_iMouseLButtonState[1] = g_FzmMouseButton[0];
		}
		else
			s_iMouseLButtonState[0] = g_FzmMouseButton[0];
	}
	else
	{
		s_lpDDS_Exit = s_lpDDS_ExitImage;
		s_ExitButtonPos.x = 682;
		s_ExitButtonPos.y = 547;
	}

	SFullZoomMapInfo  *lpZoomMapInfo;
	SFullZoomMapImage *lpZoomMapImage;

	for (i = 0; i < EFzmNameMax; i++)
	{
		lpZoomMapInfo = &s_FzmInfo[i];
		lpZoomMapImage = &s_FzmImage[lpZoomMapInfo->eNameType - 1];

		st_x = int(lpZoomMapInfo->iNamePosX * g_fWinSizeRatio_X);
		st_y = int(lpZoomMapInfo->iNamePosY * g_fWinSizeRatio_Y);
		end_x = int((lpZoomMapInfo->iNamePosX + lpZoomMapImage->iCheckWideh)  * g_fWinSizeRatio_X);
		end_y = int((lpZoomMapInfo->iNamePosY + lpZoomMapImage->iCheckHeight) * g_fWinSizeRatio_Y);

		if (g_iFzmCursorPosX > st_x && g_iFzmCursorPosX < end_x && g_iFzmCursorPosY > st_y && g_iFzmCursorPosY < end_y)
		{
			if (s_iFzmFocusName == i)
			{
				if (s_iMouseLButtonState[0] == 0)
				{
					if (s_iMouseLButtonState[1] == 1)
					{
						if (g_FzmMouseButton[0] == 0)
						{
							s_iMouseLButtonState[1] = 0;

							LoadZoomInMap(lpZoomMapInfo);
							s_iFzmActiveName = i;

							SetFzmEffect(NAME_EFFECT, &s_NameEffectDataInfo, 2, s_iFzmActiveName);
						}
					}
					else
						s_iMouseLButtonState[1] = g_FzmMouseButton[0];
				}
				else
					s_iMouseLButtonState[0] = g_FzmMouseButton[0];
			}
			else
			{
				s_iFzmFocusName = i;

				s_iMouseLButtonState[0] = g_FzmMouseButton[0];
				s_iMouseLButtonState[1] = -1;
			}

			break;
		}
	}
	if (i >= EFzmNameMax)
		s_iFzmFocusName = -1;

	SetFzmCharPos();
}

int KeyFullZoomMap(WPARAM wParam)
{
	if (wParam >= 0x70 && wParam <= 0x77)
		return 1;

	if (wParam >= 0x23 && wParam <= 0x28)
		return 1;

	if (wParam == VK_CONTROL || wParam == 0x31 || wParam == 0x32 || wParam == 0x33)
		return 1;

	return 0;
}

