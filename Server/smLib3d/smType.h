
#define MAP_SIZE			256
#define MAP_CLIP			0xFF
#define MAX_CELL			4096
#define MAPTEXTURE_SIZE		64
#define RAYCLIP_ANGLE		ANGLE_45+ANGLE_1

#define RAYCLIP_ADD			5

#define ANGCLIP				ANGLE_MASK
#define CLIP_OUT			-32767
#define SMFLAG_NONE			0xFFFFFFFF

#define	fONE		256
#define FLOATNS		8
#define FLOATDS		8

#define wfONE		32768
#define wFLOATS		15
#define wSHIFT_FLOAT	(wFLOATS-FLOATNS)

#define SizeMAPCELL			64
#define ShiftMAPCELL_MULT	6
#define ShiftMAPCELL_DIV	6

#define SHIFT_MAPHEIGHT		(ShiftMAPCELL_MULT-3)
#define AND_SizeMAPCELL		(SizeMAPCELL-1)
#define OR_SizeMAPCELL		(0xFFFFFFFF-AND_SizeMAPCELL)

#define DEFAULT_CONTRAST			300
#define DEFAULT_BRIGHT				160

#define SMCLIP_NEARZ		0x00000001
#define SMCLIP_FARZ			0x00000002
#define SMCLIP_LEFT			0x00000004
#define SMCLIP_RIGHT		0x00000008
#define SMCLIP_TOP			0x00000010
#define SMCLIP_BOTTOM		0x00000020
#define SMCLIP_TEXTURE		0x00000040
#define SMCLIP_DISPLAYOUT	0x00000080
#define SMCLIP_DISPLAYIN	0x00000100

#define SMCLIP_VIEWPORT		( SMCLIP_NEARZ | SMCLIP_FARZ | SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM | SMCLIP_DISPLAYOUT )

#define SMC_A				3
#define SMC_R				2
#define SMC_G				1
#define SMC_B				0

#include "..\\nettype.hpp"
#ifdef _W_SERVER
#define MAX_TEXTURE		8000
#else
#define MAX_TEXTURE		5000
#endif

#define ALPHATESTDEPTH 60

#define D3DFVF_TLVERTEX0_SIZE 24
#define D3DFVF_TLVERTEX1_SIZE 32
#define D3DFVF_TLVERTEX2_SIZE 40
#define D3DFVF_TLVERTEX3_SIZE 48
#define D3DFVF_TLVERTEX4_SIZE 56
#define D3DFVF_TLVERTEX5_SIZE 64
#define D3DFVF_TLVERTEX6_SIZE 72
#define D3DFVF_TLVERTEX7_SIZE 80
#define D3DFVF_TLVERTEX8_SIZE 88

#define D3DFVF_TLVERTEX ( D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_SPECULAR|D3DFVF_TEX1)

#define SIN_MAX_SKILL_LIST		10

#define ELEMENT_FIRE			1
#define ELEMENT_ICE				2
#define ELEMENT_THUNDER			3


#define CHATBUFF_MAX		1024
#define CHATBUFF_MASK		1023

#define SENDWAREHOUSEMONEY 1
#define RECVWAREHOUSEMONEY 2

#define MAX_FIELD	64

typedef float D3DVALUE;

struct smMATRIX
{
	int _11, _12, _13, _14;
	int _21, _22, _23, _24;
	int _31, _32, _33, _34;
	int _41, _42, _43, _44;
};

//���� �Ҽ��� ���2
struct smEMATRIX {
	int _11, _12, _13, _14;
	int _21, _22, _23, _24;
	int _31, _32, _33, _34;
	int _41, _42, _43, _44;
};


//�ε� �Ҽ� Double �� ���
struct smDMATRIX {
	double _11, _12, _13, _14;
	double _21, _22, _23, _24;
	double _31, _32, _33, _34;
	double _41, _42, _43, _44;
};

//�ε� �Ҽ� float �� ���
struct smFMATRIX {
	float _11, _12, _13, _14;
	float _21, _22, _23, _24;
	float _31, _32, _33, _34;
	float _41, _42, _43, _44;
};

struct smRGB {
	DWORD r, g, b;
};
struct smLIGHTLEVEL {
	BYTE		cr, cg, cb;
	BYTE		sr, sg, sb;
};

struct smLIGHT3D {
	int type;
	int x, y, z;
	int Range;
	short r, g, b;

};

#define	smLIGHT_TYPE_NIGHT		0x00001
#define	smLIGHT_TYPE_LENS		0x00002
#define	smLIGHT_TYPE_PULSE2		0x00004				// ���̴� ���� ����. ???
#define	SMLIGHT_TYPE_OBJ		0x00008
#define	smLIGHT_TYPE_DYNAMIC	0x80000


struct smTIME
{
	DWORD Day, Hour, Minute, Sec;
};
struct POINT3D {
	int x, y, z;
};

struct TPOINT3D {
	int x, y, z;
	float u, v;
	float zb;
	BYTE	bCol[4];
	BYTE	bSpe[4];
};

struct smLINE3D {
	POINT3D sp;
	POINT3D ep;
};

struct smTRECT {
	float u0, v0;
	float u1, v1;
	float u2, v2;
	float u3, v3;
};

struct smTPOINT {
	int u, v;
};

struct smFTPOINT {
	float u, v;
};



// 3�� �������� �ؽ��� ��ǥ �� ���� ����Ʈ
struct smTEXLINK {
	float	u[3], v[3];
	DWORD	*hTexture;
	smTEXLINK	*NextTex;
};

struct smVERTEX {
	int x, y, z;
	int nx, ny, nz;
};

struct smFACE {
	WORD v[4];			// a,b,c , matrial
	smFTPOINT t[3];		// �ؽ��� ����Ʈ

	smTEXLINK	*lpTexLink;		// �ؽ��� ���� ��ǥ 

};

struct smTM_ROT {
	int frame;
	float x, y, z, w;
};
struct smDTM_ROT {
	int frame;
	double x, y, z, w;
};


struct smTM_POS {
	int   frame;
	float x, y, z;
};


struct smTM_SCALE {
	int frame;
	int x, y, z;
};


// �������� ���� ���ؽ�
struct smRENDVERTEX
{
	int		tx, ty, tz;			// Transrate ī�޶� ��ǥ
	DWORD	ClipStatus;			// Ŭ���� �䱸 ����

	float	xy[2];				// 2D ��ȯ ��ǥ
	float	zb;					// Z Buffer ����
	float	rhw;				// rhw


	int		nx, ny, nz;

	short	sLight[4];			// ����� ���� (RGBA)

	BYTE	bCol[4];			// ���ؽ� ���� (RGBA)
	BYTE	bSpe[4];			// ���ؽ� Specular (RGBA)

	void	*lpSourceVertex;	//���� ���ؽ� ������
};

// �������� ���� ���̽�
struct smRENDFACE {

	smRENDVERTEX	*lpRendVertex[3];	// a,b,c
	DWORD			Matrial;			// ��Ʈ����
	smTEXLINK		*lpTexLink;			// �ؽ��� ���� ��ǥ 
	DWORD			ClipStatus;			// Ŭ���� �䱸 ����
	smRENDFACE		*NexRendFace;		// ���� ���������̽� ������

};

//�������� �� ����ü
struct smRENDLIGHT {
	int type;
	int x, y, z;
	int rx, ry, rz;
	int Range;
	int dRange;
	int r, g, b, a;
};


//��Ʈ���� ������ ���̽��� ����ü
struct smRENDMATRIAL {

	int RegistRendList;					// ������ ����Ʈ�� ��� ���� ǥ��

	// �Ϲ���
	DWORD		MatrialCounter;			// �������� ���̽��� �� ( ��Ʈ���� �� )
	smRENDFACE	*StartFace;				// �������� ���� ���̽� ������
	smRENDFACE	*LastLinkFace;			// ���������� ������ ���̽�

	// �ؽ��� Ŭ����
	DWORD		TexClip_MatrialCounter;	// �������� ���̽��� �� ( ��Ʈ���� �� )
	smRENDFACE	*TexClip_StartFace;		// �������� ���� ���̽� ������
	smRENDFACE	*TexClip_LastLinkFace;	// ���������� ������ ���̽�
};

//�ؽ��� ����
struct smTEXRECT {
	float	left, right;
	float	top, bottom;
};

//2D �̹��� ���̽�
struct smFACE2D {
	int			x, y, z;			// ��ǥ
	int			width, height;		// �̹��� ũ��
	smTEXRECT	TexRect;			// �ؽ��� ����
	int			MatNum;				// ��Ʈ���� ��ȣ
	int			Transparency;		// ����
	int			r, g, b;
};


// ���ؽ�
struct smSTAGE_VERTEX {
	DWORD			sum;				// �ֱ� ���� ��ȣ 
	smRENDVERTEX	*lpRendVertex;		// �������� ���� ���ؽ� ������

	int				x, y, z;				// ���� ��ǥ

	short			sDef_Color[4];		// �⺻ ���� ( RGBA )

};	// ���� ũ�� 28 ����Ʈ


// ���̽�
struct smSTAGE_FACE {
	DWORD	sum;				// �ֱ� ���� ��ȣ
	int		CalcSum;			// ��Ÿ ���� ��ȣ

	WORD	Vertex[4];			// a,b,c,Matrial

	smTEXLINK	*lpTexLink;		// �ؽ��� ���� ��ǥ 

	short	VectNormal[4];			// Cross����( Normal )  ( nx , ny , nz , [0,1,0]���� Y ); 
};




#define		CONFIG_KEY_MONSTER_MAX		5

struct smCONFIG
{
	int		WinMode;
	POINT	ScreenSize;
	DWORD	ScreenColorBit;
	BOOL	AutoAdjust;
	int		Ratio;

	int		Anti;
	int		Vsync;

	int		TextureQuality;
	int		Music;
	int		MusicVolume;
	int		Sound;
	int		SoundVolume;
	int		NetworkQuality;
	int		WeatherSwitch;

	BOOL	DisableParty;
	BOOL	DisableWhisper;
	BOOL	DisableCameraWave;
	BOOL	EnableRLogin;
	BOOL	DisableShowDamage;

	int		GamePort;

	char	szFile_BackGround[2][64];
	char	szFile_Menu[64];
	char	szFile_Player[64];
	POINT	Posi_Player;
	char	szFile_Enemy[64];
	POINT	Posi_Enemy;

	char	szFile_Stage[64];
	POINT	Posi_Stage;
	char	szFile_StageObject[100][64];
	int		StageObjCnt;

	int		IsStageAniObject[100];

	int		CameraInvRot;
	int		IsFilterEffect;
	int		CameraSight;

	int		MapBright;
	int		MapContrast;
	POINT3D	MapLightVector;

	char	szServerIP[32];
	DWORD	dwServerPort;
	char	szDataServerIP[32];
	DWORD	dwDataServerPort;
	char	szUserServerIP[32];
	DWORD	dwUserServerPort;
	char	szExtendServerIP[32];
	DWORD	dwExtendServerPort;

	DWORD	DebugMode;

	char	szCmdOpenMonster[CONFIG_KEY_MONSTER_MAX][32];
	int		CmdMonsterCount;

	char szLastAccount[32];

	char szMessage[10][128];

	smCONFIG();
	~smCONFIG();
};




#define MOTION_LIST_MAX			32
#define MOTION_INFO_MAX			512
#define	MOTION_TOOL_MAX			52
#define	MOTION_SKIL_MAX			8

#define NPC_MOTION_INFO_MAX		 30
#define TALK_MOTION_INFO_MAX	 30

#define TALK_MOTION_FILE_MAX	 2
#define TALK_MOTION_FILE		 0
#define FACIAL_MOTION_FILE		 1

struct _MODELGROUP {
	int ModelNameCnt;
	char szModelName[4][16];
};

struct smMODELINFO
{

	char	szModelFile[64];
	char	szMotionFile[64];
	char	szSubModelFile[64];

	_MODELGROUP	HighModel;
	_MODELGROUP	DefaultModel;
	_MODELGROUP	LowModel;

	ModelAnimation	MotionInfo[MOTION_INFO_MAX];
	DWORD	MotionCount;


	DWORD			FileTypeKeyWord;
	DWORD			LinkFileKeyWord;

	char			szLinkFile[64];

	char			szTalkLinkFile[64];
	char			szTalkMotionFile[64];
	ModelAnimation	TalkMotionInfo[TALK_MOTION_INFO_MAX];
	DWORD			TalkMotionCount;

	int				NpcMotionRate[NPC_MOTION_INFO_MAX];
	int				NpcMotionRateCnt[100];

	int				TalkMotionRate[TALK_MOTION_INFO_MAX];
	int				TalkMotionRateCnt[TALK_MOTION_FILE_MAX][100];
};




extern BYTE VRKeyBuff[256];





struct smTEXPOINT {
	float	u, v;
	DWORD	hTexture;
};

struct smFCOLOR {
	float	r, g, b;
};

//�ؽ��� �� ������ ��ǥ �Ӽ�
#define smTEXSTATE_FS_NONE		0
#define smTEXSTATE_FS_FORMX		1
#define smTEXSTATE_FS_FORMY		2
#define smTEXSTATE_FS_FORMZ		3
#define smTEXSTATE_FS_SCROLL	4
#define smTEXSTATE_FS_REFLEX	5

#define smTEXSTATE_FS_SCROLL2	6
#define smTEXSTATE_FS_SCROLL3	7
#define smTEXSTATE_FS_SCROLL4	8
#define smTEXSTATE_FS_SCROLL5	9
#define smTEXSTATE_FS_SCROLL6	10
#define smTEXSTATE_FS_SCROLL7	11
#define smTEXSTATE_FS_SCROLL8	12
#define smTEXSTATE_FS_SCROLL9	13
#define smTEXSTATE_FS_SCROLL10	14

#define smTEXSTATE_FS_SCROLLSLOW1	15
#define smTEXSTATE_FS_SCROLLSLOW2	16
#define smTEXSTATE_FS_SCROLLSLOW3	17
#define smTEXSTATE_FS_SCROLLSLOW4	18

#define smTEXTATE_MIXNON		-1
#define smTEXTATE_MIXS01		0
#define smTEXTATE_MIXS02		1
#define smTEXTATE_MIXS03		2
#define smTEXTATE_MIXS04		3
#define smTEXTATE_MIXS05		4
#define smTEXTATE_MIXM01		5
#define smTEXTATE_MIXM02		6
#define smTEXTATE_MIXM03		7
#define smTEXTATE_MIXM04		8
#define smTEXTATE_MIXM05		9
#define smTEXTATE_MIXM06		10
#define smTEXTATE_MIXM07		11
#define smTEXTATE_MIXM08		12
#define smTEXTATE_MIXM09		13
#define smTEXTATE_MIXM10		14
#define smTEXTATE_MIXM11		15



struct smTEXTUREHANDLE
{
	char Name[64];
	char NameA[64];

	void *m_pTexture;

	int Width, Height;
	int UsedTime;

	int UseCounter;

	int iTransparency;

	BOOL bSwap;

	smTEXTUREHANDLE *TexChild;

	BOOL LoadTexture(char *FileName, BOOL bMipmap, BOOL _bSwap);
};


/////////////////////////// ASE ���� �о� ���� ��Ʈ���� //////////////////////////
struct ASE_MATERIAL {
	int			Regist;						//smMATERIAL �� ��� ����
	int			RegistNum;					//smMATERIAL �� ��ϵ� ��ȣ

	int			TextureCounter;				//��Ʈ�� ��� ����
	DWORD		UseCounter;					//��� ī���� ( ������ 0 �̸� ���� ���� )

	smFCOLOR	Diffuse;					// Diffuse ����
	float		Transparency;				// ����
	float		SelfIllum;					// ��ü �߱�
	DWORD		TwoSide;					// ��� ǥ�� ��� ( �������� ǥ�� ���� )
	DWORD		ScriptState;				// ��ũ��Ʈ�� ���� �Ӽ�


	char		BITMAP[8][64];				// Bitmap �̸�

	DWORD		BitmapStateState[8];		// ��Ʈ�� �������� �Ӽ�
	DWORD		BitmapFormState[8];			// ��Ʈ�� �� �Ӽ�

	char		MAP_OPACITY[64];			// ������ �� �̸�

	float		UVW_U_OFFSET[8];			// �� OFFSET
	float		UVW_V_OFFSET[8];			//
	float		UVW_U_TILING[8];			// �� TILING
	float		UVW_V_TILING[8];
	float		UVW_ANGLE[8];				// �� ANGLE

	int			SubPoint;					// ���� ��Ʈ���� ��ȣ

	int			BlendType;					//���� Ÿ��

};



//////////////////////////////// ��Ʈ����  //////////////////////////////
struct smMATERIAL {
	DWORD			InUse;						//��Ʈ���� ��� ����
	DWORD			TextureCounter;				//�ؽ��� ī����
	smTEXTUREHANDLE	*smTexture[8];				//�ؽ��� �ڵ� ����Ʈ

	DWORD			TextureStageState[8];		//�׸��� �Ӽ� 
	DWORD			TextureFormState[8];		//�� �Ӽ�  
	int				ReformTexture;				//�ؽ��� �����Ӽ� Ȯ��

	int				MapOpacity;					//�� ���ǽ�Ƽ ���� ( TRUE , FALSE )

	DWORD			TextureType;				//�ؽ��� Ÿ�� ( ��Ƽ�ͽ� / �ִϸ��̼� )
	DWORD			BlendType;					//�귣�� ���� ( SMMAT_BLEND_XXXX )

	DWORD			Shade;						//���̵� ��� ( �뽦�̵� / �׷ν��̵� )
	DWORD			TwoSide;					//��� ��� ����
	DWORD			SerialNum;					//��Ʈ���� ���� ���� ��ȣ

	smFCOLOR		Diffuse;					// Diffuse ����
	float			Transparency;				// ����
	float			SelfIllum;					// ��ü �߱�

	int				TextureSwap;				// �ؽ��� ������
	int				MatFrame;					// ��������� ( ���� ���⸦ ���߱� ���� )
	int				TextureClip;				// �����ο� �ؽ��� Ŭ������ ( TRUE �� �ؽ��� Ŭ���� �㰡 )

	int				UseState;					// �뵵 ( ��� �Ӽ� )
	int				MeshState;					// MESH�� ���� �Ӽ��� 

	int				WindMeshBottom;				// �ٶ��ұ� �޽� ���� ���� ��

	smTEXTUREHANDLE	*smAnimTexture[32];			//�ִϸ��̼� �ؽ��� �ڵ� ����Ʈ
	DWORD			AnimTexCounter;				//�ֹ̳��̼� �ؽ��� ī����
	DWORD			FrameMask;					//�ִϸ��̼ǿ� ������ ����ũ
	DWORD			Shift_FrameSpeed;			//������ ���� �ӵ� ( Ÿ�̸Ӹ� Shift �Ͽ� ��� )
	DWORD			AnimationFrame;				//������ ��ȣ ( ������ ��� �����Ӱ� / SMTEX_AUTOANIMATION �� �ڵ� )


};

#define SMTEX_TYPE_MULTIMIX		0x0000
#define SMTEX_TYPE_ANIMATION	0x0001

#define SMTEX_AUTOANIMATION		0x100


#define SMMAT_STAT_CHECK_FACE	0x00000001

#define SMMAT_BLEND_NONE		0x00
#define SMMAT_BLEND_ALPHA		0x01
#define SMMAT_BLEND_COLOR		0x02
#define SMMAT_BLEND_SHADOW		0x03
#define SMMAT_BLEND_LAMP		0x04
#define SMMAT_BLEND_ADDCOLOR	0x05
#define SMMAT_BLEND_INVSHADOW	0x06



struct smASE_LIGHT {

	int	x, y, z;
	int r, g, b;

	int Size;
	int Range;
	int	Dist;
	int Type;
};


//ī�޶� ���� ��ǥ
struct eCAMERA_TRACE {
	int x, y, z;					//���� ī�޶� ��ǥ
	int tx, ty, tz;				//��ǥ�� ��ǥ

	smEMATRIX	eRotMatrix;		//ȸ�� ���� ���
	int AngX, AngY;				//������ ���� ( ���� ����ŭ )
};


