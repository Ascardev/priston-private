/*----------------------------------------------------------------------------*
*	���ϸ� :  YameEffect
*	�ϴ��� :  ���ο� ����Ʈ
*	�ۼ��� :  ����������Ʈ 2003�� 6��
*	������ :  �ڻ�
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
// �ִϸ��̼�
struct sYAME_ANI {
	int		Cnt;
	int		DelayTime;
	int		MaxCnt;
	int		MatIndex[10];   //�ִϸ��̼��� �� ��Ʈ���� ��ȣ �ε��� 
	int		Reverse;		//�ִϸ��̼� �����÷� ( 1�ٸ����� 2 ���� ) 

};

// ���� ����
struct sYAME_FADE {
	DWORD   FADE_CODE;
	int     MaxAlpha; //���� ���İ��� ���Ѵ� 
	int     NowAlpha; //���� ���İ��� ���Ѵ� 
	float   AlphaAmount;
	int		AlphaStartTime;

};

// ȸ�� 
struct sYAME_ROTATE {
	int		RAngle;
	int		RAngleSpeed;
	POINT3D RPosi;
	POINT3D CenterPosi; //ȸ���߽���ǥ
};

// Angle ȸ�� 
struct sYAME_ANGLE_ROTATE {
	POINT3D	ARotate;
	POINT3D	ARotateSpeed;
	int     FACEY;

};

// �� 
struct sYAME_COLOR {
	int r;
	int g;
	int b;
	int a;

};

// ������ 
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
*						  YAMEEFFECT ���� Ŭ����
*-----------------------------------------------------------------------------*/
class  cYAMEEFFECT {
public:

	DWORD   CODE;				//����Ʈ ���� �ڵ� 
	DWORD	MOVECODE;			//�⺻ ������ 
	int		Time;
	int		Max_Time;
	int		Bone;

	///////////// ����
	smFACE2D	Face;
	smPAT3D		*PatMesh;
	///////////// ����
	int		Index;
	int		ZDepth;

	///////////// ��ǥ ����
	POINT3D	Posi;			//��ǥ
	POINT3D	DesPosi;		//������ ��ġ ��ǥ
	POINT3D	Angle;			//�ޱ�

	int		AddHeight;		//������ ��ǥ

	///////////// ������
	POINT3D	MoveSpeed;

	///////////// ĳ����
	Unit	*pChar;			//�ڽ�
	Unit	*desChar;		//���õ� ĳ����

	/////////////FACE TYPE
	int FACE_TYPE;
	int FACE_POSI;
	///////////// Size
	int w;
	int h;

	///////////// �ִϸ��̼�
	sYAME_ANI	Ani;

	///////////// ���̵� 
	sYAME_FADE  Fade;

	///////////// ȸ��  
	sYAME_ROTATE Rotate;

	///////////// Angle ȸ�� 
	sYAME_ANGLE_ROTATE Angle_Rotate;

	///////////// �÷� 
	sYAME_COLOR	Color;

	///////////// ������ 
	sYAME_SCALE	Scale;

	///////////// ������ 
	sYAME_BILLBOARD BillBoard;

	///////////// FACE ���Ḯ��Ʈ 
	cASSATrace *cAssaTrace;



public:
	cYAMEEFFECT()
	{
		memset(this, 0, sizeof(cASSAEFFECT));
		cASSATrace *pAssaTrace = new cASSATrace; //Face ���Ḯ��Ʈ 
		cAssaTrace = pAssaTrace;

	}
	virtual ~cYAMEEFFECT()
	{
		if (cAssaTrace)delete cAssaTrace;
	}
	virtual	void Main() {}
	virtual void Draw(POINT3D *pPosi, POINT3D *pAngle) {}

	//ĳ���� ���� ���¸� üũ�Ѵ� (�ٲ����δ� , �׾��ų� , ������ �������)
	//int AssaReSetCharPointer(); AssaEffect��������ߴ� 

};

/*----------------------------------------------------------------------------*
*						  YAMEEFFECT FACE Ŭ����
*-----------------------------------------------------------------------------*/
class cYAMEFACE : public cYAMEEFFECT
{
public:

	void Main()
	{
		Face.x = Posi.x;	//��ǥ ����
		Face.y = Posi.y;
		Face.z = Posi.z;
		Face.width = w;	//ũ�� ���� 
		Face.height = h;
		if (!Face.height) {
			h = w;
			Face.height = Face.width; //ũ�⺸��
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
*						  YAMEEFFECT MESH Ŭ����
*-----------------------------------------------------------------------------*/
class cYAMEMESH : public cYAMEEFFECT
{
public:

};

/*----------------------------------------------------------------------------*
*						  AssaEffect �⺻ �Լ�
*-----------------------------------------------------------------------------*/
void InitYameEffect();

void DrawYameEffect(POINT3D *pPosi, POINT3D *pAngle);

void MainYameEffect();

void MoveYameEffect(cASSAEFFECT *pEffect);

void CloseYameEffect();

void StopYameEffect(cASSAEFFECT *pEffect);

void YameEffectKeyDown();

/*----------------------------------------------------------------------------*
*							  Setting �Լ�
*-----------------------------------------------------------------------------*/
//AssaEffect����
int  SetYameEffect(int MaxTime, char *FileName, Unit *pChar, POINT3D *pPosi, int AddHeight = 0, int BlendType = 0);

extern int Yame;  //�ε��� 
extern cYAMEEFFECT *cYameEffect[YAMEEFFECT_MAX]; //����Ʈ ���� 
#endif
