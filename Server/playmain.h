#define OTHER_PLAYER_MAX		1024
#define OTHER_PLAYER_MASK		1023


#define	SHADOW_PAT_MAX		4

//######################################################################################
//�� �� �� : �� �� ��
#define	ICE_FOOT_PAT_MAX		2
extern	smPAT3D *PatIceFoot[ ICE_FOOT_PAT_MAX ];
//######################################################################################

//����ú� �� ������ �ð�
#define	GAME_WORLDTIME_MIN		800
//#define	GAME_WORLDTIME_MIN		200

//���ӳ� ������ �㳷 ��ȭ �ð�
#define GAME_HOUR_DAY			4
#define GAME_HOUR_GLOW			22
#define GAME_HOUR_DARKNESS		23
#define GAME_HOUR_NIGHT			24


extern DWORD	dwBattleTime;				//�ֱ� ���� �ð�
extern DWORD	dwBattleQuitTime;			//������ ���� �Ϸ� �Ҷ�
extern DWORD	dwCloseBoxTime;				//â ���� �Ϸ� �Ҷ�

extern int	PkMode;							//PK���
extern int	DispApp_SkillPoint ;			//������ �ð����� ��ų ����Ʈ

extern int		Moving_DblClick;			//���콺 �̵� ýũ ���� Ŭ��
extern POINT3D	MousePos_DblClick;

extern POINT3D	TracePos_DblClick;
extern int TraceMode_DblClick;


extern	int	ActionGameMode;				//�׼ǰ��Ӹ��

extern smPAT3D  *PatShadow[SHADOW_PAT_MAX];			//�׸���
extern smPAT3D  *PatArrow;							//ȭ��
extern smPAT3D	*PatEffectShield;					//���� ����Ʈ
extern smPAT3D	*PatSparkShield;					//����ũ���� ����Ʈ
extern smPAT3D	*PatDivineShield;					//��������ҷ��̼�
extern smPAT3D	*PatGodlyShield;					//���鸮����
extern smPAT3D	*PatCrown;							//����ĳ�� �հ�

extern Unit	chrOtherPlayer[OTHER_PLAYER_MAX];
extern char PlayerName[64];

extern	int	RecordFailCount;				//���� ���� ī����


//���� ��Ʈ Ŭ����
extern smSTAGE3D *smStage;
extern int PlayCounter;

//extern DWORD	dwPlayTime;					//������ ������ �ð� ( �÷��� �� )
extern DWORD	dwMemError;					//�޸� ���� Ȯ�� �ڵ�

extern int	BackColor_R ;				//���� R
extern int	BackColor_G ;				//���� G
extern int	BackColor_B ;				//���� B

extern int	BackColor_mR;				//���� ���氪 R
extern int	BackColor_mG;				//���� ���氪 G
extern int	BackColor_mB;				//���� ���氪 B

extern int	DarkLevel_Fix;				//��� �� ����

extern int DarkLevel;					//��� ��
extern int DarkLightRange;			//��οﶧ ���� ����
extern DWORD	dwGameWorldTime;	//������ ����ð�
extern DWORD	dwGameHour;			//������ ��
extern DWORD	dwGameMin;			//������ ��
extern DWORD	dwGameTimeOffset;

extern DWORD	UseEtherCoreCode;	//��Ƽ�� �ھ� ���


extern int MatBlood[2];			//��Ƣ��� ��Ʈ����

extern int MatEnergyBox[2];
extern int MatEnergyBoxNew[2];

extern	int WeatherMode;		//����

extern int		MsTraceCount;
extern int		MsTraceMode;

extern	RECT	MsSelRect;
extern	POINT	MsSelPos;

extern	int		SelMouseButton;			//��� ���õ� ���콺

extern  int		AttCancel;						//���� ���
extern  int		AttAutoCont;					//�ڵ� ����


extern  Unit	*lpCharSelPlayer;
extern	Unit	*lpCharMsTrace;			//�̵� ��ǥ ĳ����

extern	int		RestartPlayCount;			//����� ���� ���� ī��Ʈ


//���� �޾����� ȸ�� ī����
extern int	Record_BlockCount;
extern int	Record_DefenceCount;
extern int	Record_RecvDamageCount;
extern int  Record_TotalRecvDamageCount;

extern DWORD SkillFalconPoint;					//���� ��ų ����Ʈ �����


//���� ���콺 ������
extern	DWORD	AutoMouse_LastCheckTime;
extern	DWORD	AutoMouse_StartCheckTime;
extern	int		AutoMouse_WM_Count;
extern	int 	AutoMouse_Distance;
extern	int		AutoMouse_Attack_Count;


//���콺�� ���� �÷��̾���� ������ �����ش�
int GetMouseSelAngle( );

extern char *NpcSelectedName;			//���õ� NPC �̸�


extern int QuitSave;


//�Źٶ� ����ũ
#define	sinITEM_WEAPON	0x01000000
#define	sinITEM_DEFENCE	0x02000000
#define	sinITEM_MASK1	0xFF000000
#define	sinITEM_MASK2	0xFFFF0000
#define	sinITEM_MASK3	0x0000FFFF


//�ڸ�� ���� ( winmain.cpp )
extern char szCmdLine[128];
extern int QuitSave;
extern DWORD	dwLastMouseMoveTime;
extern DWORD	dwLastCharMoveTime;


//////////////// ��öȣ ������ �÷��̾� /////////////
extern int ParkPlayMode;		//-�ø����� 0-�Ϲ� +�����ð�(�ִ� 1000)
extern int ParkPlaying;			//������ �÷�����

