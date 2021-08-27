/*----------------------------------------------------------------------------*
*	파일명 :  YameEffect
*	하는일 :  새로운 이펙트
*	작성일 :  최종업데이트 2003년 6월
*	적성자 :  박상열
*-----------------------------------------------------------------------------*/
#ifndef _YAMEEFFECT_HEADER_

#define _YAMEEFFECT_HEADER_

#define YAMEEFFECT_MAX		5000

/*----------------------------------------------------------------------------*
*							FADE OPTION
*-----------------------------------------------------------------------------*/
#define YAME_DEFAULT_FADE	0x00000000
#define YAME_SMOOTH_FADE	0x00000001
#define YAME_NOT_FADEIN		0x00000010
#define YAME_NOT_FADEOUT	0x00000100


/*----------------------------------------------------------------------------*
*							FACE KIND
*-----------------------------------------------------------------------------*/
#define YAMEFACE_BILLBOARD	0
#define YAMEFACE_WORLD		1
#define YAMEFACE_SCALE		2
#define YAMEFACE_TRACE		3

/*----------------------------------------------------------------------------*
*							YAME STRUCT
*-----------------------------------------------------------------------------*/
// 애니메이션
struct sYAME_ANI {
	int		Cnt;
	int		DelayTime;
	int		MaxCnt;
	int		MatIndex[10];   //애니메이션이 될 메트리얼 번호 인덱스 
	int		Reverse;		//애니메이션 역순플렉 ( 1바른차순 2 역순 ) 

};

// 알파 블렌딩
struct sYAME_FADE {
	DWORD   FADE_CODE;
	int     MaxAlpha; //임의 알파값을 정한다 
	int     NowAlpha; //임의 알파값을 정한다 
	float   AlphaAmount;
	int		AlphaStartTime;

};

// 회전 
struct sYAME_ROTATE {
	int		RAngle;
	int		RAngleSpeed;
	POINT3D RPosi;
	POINT3D CenterPosi; //회전중심좌표
};

// Angle 회전 
struct sYAME_ANGLE_ROTATE {
	POINT3D	ARotate;
	POINT3D	ARotateSpeed;
	int     FACEY;

};

// 색 
struct sYAME_COLOR {
	int r;
	int g;
	int b;
	int a;

};

// 스케일 
struct sYAME_SCALE {
	POINT3D ScalePosi;
	POINT3D ScaleSpeed;
	int     CenterFlag;

};

struct sYAME_BILLBOARD {
	int FaceY;
	int ZposiFlag;

};




class cYAMEEFFECT;

/*----------------------------------------------------------------------------*
*						  YAMEEFFECT 메인 클래스
*-----------------------------------------------------------------------------*/
class  cYAMEEFFECT {
public:

	DWORD   CODE;				//이펙트 고유 코드 
	DWORD	MOVECODE;			//기본 움직임 
	int		Time;
	int		Max_Time;
	int		Bone;

	///////////// 종류
	smFACE2D	Face;
	smPAT3D		*PatMesh;
	///////////// 소팅
	int		Index;
	int		ZDepth;

	///////////// 좌표 설정
	POINT3D	Posi;			//좌표
	POINT3D	DesPosi;		//설정된 위치 좌표
	POINT3D	Angle;			//앵글

	int		AddHeight;		//보정된 좌표

	///////////// 움직임
	POINT3D	MoveSpeed;

	///////////// 캐릭터
	Unit	*pChar;			//자신
	Unit	*desChar;		//선택된 캐릭터

	/////////////FACE TYPE
	int FACE_TYPE;
	int FACE_POSI;
	///////////// Size
	int w;
	int h;

	///////////// 애니메이션
	sYAME_ANI	Ani;

	///////////// 페이드 
	sYAME_FADE  Fade;

	///////////// 회전  
	sYAME_ROTATE Rotate;

	///////////// Angle 회전 
	sYAME_ANGLE_ROTATE Angle_Rotate;

	///////////// 컬러 
	sYAME_COLOR	Color;

	///////////// 스케일 
	sYAME_SCALE	Scale;

	///////////// 빌보드 
	sYAME_BILLBOARD BillBoard;

	///////////// FACE 연결리스트 
	cASSATrace *cAssaTrace;



public:
	cYAMEEFFECT()
	{
		memset(this, 0, sizeof(cASSAEFFECT));
		cASSATrace *pAssaTrace = new cASSATrace; //Face 연결리스트 
		cAssaTrace = pAssaTrace;

	}
	virtual ~cYAMEEFFECT()
	{
		if (cAssaTrace)delete cAssaTrace;
	}
	virtual	void Main() {}
	virtual void Draw(POINT3D *pPosi, POINT3D *pAngle) {}

	//캐릭의 현제 상태를 체크한다 (바뀐포인다 , 죽었거나 , 마을에 들어섰을경우)
	//int AssaReSetCharPointer(); AssaEffect에서사용했다 

};

/*----------------------------------------------------------------------------*
*						  YAMEEFFECT FACE 클래스
*-----------------------------------------------------------------------------*/
class cYAMEFACE : public cYAMEEFFECT
{
public:

	void Main()
	{
		Face.x = Posi.x;	//좌표 셋팅
		Face.y = Posi.y;
		Face.z = Posi.z;
		Face.width = w;	//크기 셋팅 
		Face.height = h;
		if (!Face.height) {
			h = w;
			Face.height = Face.width; //크기보정
		}
		if (!Fade.MaxAlpha)Fade.MaxAlpha = 255;

		switch (Fade.FADE_CODE)
		{
		case YAME_DEFAULT_FADE:

			break;
		case YAME_SMOOTH_FADE:

			break;
		case YAME_NOT_FADEIN:

			break;
		case YAME_NOT_FADEOUT:

			break;
		}
	}
	void Draw(POINT3D *pPosi, POINT3D *pAngle)
	{
		if (Face.MatNum)
		{
			GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

			GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_DITHERENABLE, TRUE);

			GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_SPECULARENABLE, TRUE);

			GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

			GRAPHICENGINE->GetDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
			GRAPHICENGINE->GetDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

			smRender.Init();

			smMaterialGroup->smMaterial[Face.MatNum].TwoSide = TRUE;

			smRender.SetMaterialGroup(smMaterialGroup);

			smMaterialGroup->SetMaterialAnimFrame(&smMaterial[Face.MatNum], 2);

			smRender.SetCameraPosi(pPosi->x, pPosi->y, pPosi->z, pAngle->x, pAngle->y, pAngle->z);

			switch (FACE_TYPE)
			{
			case YAMEFACE_BILLBOARD:
				if (!AssaAddFace2D(&Face, BillBoard.ZposiFlag, BillBoard.FaceY))
					return;
				break;
			case YAMEFACE_WORLD:
				break;
			case YAMEFACE_SCALE:
				break;
			case YAMEFACE_TRACE:
				break;
			}

			smRender.SetClipStates(SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM);
			smRender.ClipRendFace();
			smRender.GeomVertex2D(FALSE);
			smRender.RenderD3D();
		}
	}
};

/*----------------------------------------------------------------------------*
*						  YAMEEFFECT MESH 클래스
*-----------------------------------------------------------------------------*/
class cYAMEMESH : public cYAMEEFFECT
{
public:

};

/*----------------------------------------------------------------------------*
*						  AssaEffect 기본 함수
*-----------------------------------------------------------------------------*/
void InitYameEffect();

void DrawYameEffect(POINT3D *pPosi, POINT3D *pAngle);

void MainYameEffect();

void MoveYameEffect(cASSAEFFECT *pEffect);

void CloseYameEffect();

void StopYameEffect(cASSAEFFECT *pEffect);

void YameEffectKeyDown();

/*----------------------------------------------------------------------------*
*							  Setting 함수
*-----------------------------------------------------------------------------*/
//AssaEffect셋팅
int  SetYameEffect(int MaxTime, char *FileName, Unit *pChar, POINT3D *pPosi, int AddHeight = 0, int BlendType = 0);

extern int Yame;  //인덱스 
extern cYAMEEFFECT *cYameEffect[YAMEEFFECT_MAX]; //이펙트 버퍼 
#endif
