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


extern Unit	*lpCurPlayer;							//���ΰ�
extern Unit	chrOtherPlayer[MAX_UNITS];
extern char PlayerName[64];

extern	int	RecordFailCount;				//���� ���� ī����


//���� ��Ʈ Ŭ����
extern smSTAGE3D *smStage;
extern int PlayCounter;
extern smSTAGE3D *smGameStage[2];
extern smSTAGE3D *smGameStageWall[2];
extern DWORD	dwPlayTime;					//������ ������ �ð� ( �÷��� �� )
extern DWORD	dwMemError;					//�޸� ���� Ȯ�� �ڵ�

extern char szGameStageName[2][64];			//���� ��� �̸�

extern int	BackColor_R ;				//���� R
extern int	BackColor_G ;				//���� G
extern int	BackColor_B ;				//���� B

extern int	BackColor_mR;				//���� ���氪 R
extern int	BackColor_mG;				//���� ���氪 G
extern int	BackColor_mB;				//���� ���氪 B

extern int	DarkLevel_Fix;				//��� �� ����

extern int DarkLevel;					//��� ��
extern int DarkLightRange;			//��οﶧ ���� ����

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

extern	scITEM	*lpSelItem;
extern	scITEM	*lpMsTraceItem;

extern	int		RestartPlayCount;			//����� ���� ���� ī��Ʈ

#define DISP_ITEM_MAX	128
extern scITEM	scItems[ DISP_ITEM_MAX ];			//ITEM


//���� �޾����� ȸ�� ī����
extern int	Record_BlockCount;
extern int	Record_DefenceCount;
extern int	Record_RecvDamageCount;
extern int  Record_TotalRecvDamageCount;

extern DWORD SkillFalconPoint;					//���� ��ų ����Ʈ �����


//���� ����
int TraceAttackPlay();
//���� ���
int CancelAttack();
//���콺�� ���� �÷��̾���� ������ �����ش�
int GetMouseSelAngle( );
//2���� �÷��̾��� ������ �����ش�
int GetCharAngle(Unit *lpChar1 , Unit *lpChar2 );
//���� ��� �ٲٱ�
int SetChrArmor(Unit *lpChar , int ItemNum );

//��� �δ� �ʱ�ȭ
void InitStageLoader();

Point3D InitStage();
void CloseStage();
int DisplayStage(int x , int y, int z, int angX, int angY, int angZ );



int InitPat3D(Point3D sPosition);
int ClosePat3D();
int PlayObj3D( smOBJ3D *obj3d , int x, int y, int z, int ax, int ay, int az );
int PlayPat3D();
int DrawPat3D_Alpha();
int DrawPat3D( int x, int y, int z, int ax, int ay, int az );
int DrawPat2D( int x, int y, int z, int ax, int ay, int az );

//�׸��� �׸���
int DrawPatShadow(int x, int y, int z, int ax, int ay, int az );

int InitBackGround();
int CloseBackGround();

//�׸��� ũ��Ƽ�� ����
extern CRITICAL_SECTION	cDrawSection;

extern char *NpcSelectedName;			//���õ� NPC �̸�

//��Ƽ �ŷ� ��û ��ư ��ġ�� ����
int GetPartyTradeButtonPos( int x, int y );
//��Ƽ Ʈ���̵� ��û ��Ʈ Ŭ��
int DisplayPartyTradeButton();

//�������� ���� ����ġ ���
int	DamageExp(Unit *lpChar , int AttackDamage );


// WINMAIN ���� �Լ�
extern POINT3D TraceCameraPosi;
extern POINT3D TraceTargetPosi;
extern int QuitSave;

extern int	DebugPlayer;				//����� ī�޶� �÷��̾�

extern int DispEachMode;
extern int		EachTradeButton;
extern int		EachTradeButtonMode;
extern RECT		RectTradeButton;
extern Unit	chrEachPlayer;
extern Unit	*chrEachMaster;

int SetIME_Mode( BOOL mode );

int DrawEachPlayer( float fx , float fy , int SizeMode );	//Ȯ�� ĳ���� �׸���
int EachPlayerMain();					//Ȯ�� ĳ���� ����
int CloseEachPlayer();					//Ȯ�� ĳ���� �ݱ�
int OpenEachPlayer(Unit *lpChar );	//Ȯ�� ĳ���� ����

int GetPlayMouseAngle();				//���콺�� ���� ���Ⱚ ���ϱ�
int SetMousePlay( int flag );			//���콺 �����ӿ� ���� ���� �÷��� ����


void SetPlayerBodyPattern( char *szBodyFile );		//�� ���� �ٲٱ�
void SetPlayerPattern( char *szFile );				//�� �ٲٱ�

//2����Ʈ �ڵ� Ȯ��
int CheckCode_2Byte( char *Str );		//�ڵ� Ȯ��

int SetPartyPosion( smTRANS_COMMAND *lpTransCommand );	//���� ȸ�� ����


//����Ʈ ����
int	StartQuest_Code( DWORD wCode );
//����Ʈ �Ϸ�
int EndQuest_Code( DWORD wCode );
//����Ʈ���� ���忡 ����
int SetQuestBoard();

//Ŭ���̾�Ʈ �α� ���� ���
int Record_ClinetLogFile( char *szMessage );

extern int DisplayDebug;				//����� ���� ǥ��
extern int LastAttackDamage;			//�ֱ� ���� ������

//�Źٶ� ����ũ
#define	sinITEM_WEAPON	0x01000000
#define	sinITEM_DEFENCE	0x02000000
#define	sinITEM_MASK1	0xFF000000
#define	sinITEM_MASK2	0xFFFF0000
#define	sinITEM_MASK3	0x0000FFFF

//���� ���� ( playsub.cpp )
int QuitGame();
int SetIME_Mode( BOOL mode );

//�ڸ�� ���� ( winmain.cpp )
extern char szCmdLine[128];
extern int QuitSave;
extern DWORD	dwLastMouseMoveTime;
extern DWORD	dwLastCharMoveTime;

extern int	PlayTimerMax;			//�� �������� �ɸ� �ð� ýũ

extern DWORD dwM_BlurTime;


//////////////// ��öȣ ������ �÷��̾� /////////////
extern int ParkPlayMode;		//-�ø����� 0-�Ϲ� +�����ð�(�ִ� 1000)
extern int ParkPlaying;			//������ �÷�����

int Init_ParkPlayer();			//�÷��̾� �ʱ�ȭ
int Stop_ParkPlayer();			//�÷��̾� ����
int Play_ParkPlayer( char *szPath , int x, int y, int w, int h , int PlayMode );		//�÷��̾� ���

