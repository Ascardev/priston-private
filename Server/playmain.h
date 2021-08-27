#define OTHER_PLAYER_MAX		1024
#define OTHER_PLAYER_MASK		1023


#define	SHADOW_PAT_MAX		4

//######################################################################################
//작 성 자 : 오 영 석
#define	ICE_FOOT_PAT_MAX		2
extern	smPAT3D *PatIceFoot[ ICE_FOOT_PAT_MAX ];
//######################################################################################

//월드시분 의 실제의 시간
#define	GAME_WORLDTIME_MIN		800
//#define	GAME_WORLDTIME_MIN		200

//게임내 에서의 밤낮 변화 시간
#define GAME_HOUR_DAY			4
#define GAME_HOUR_GLOW			22
#define GAME_HOUR_DARKNESS		23
#define GAME_HOUR_NIGHT			24


extern DWORD	dwBattleTime;				//최근 전투 시간
extern DWORD	dwBattleQuitTime;			//전투중 종료 하려 할때
extern DWORD	dwCloseBoxTime;				//창 종료 하려 할때

extern int	PkMode;							//PK모드
extern int	DispApp_SkillPoint ;			//설정된 시간적용 스킬 포인트

extern int		Moving_DblClick;			//마우스 이동 첵크 더블 클릭
extern POINT3D	MousePos_DblClick;

extern POINT3D	TracePos_DblClick;
extern int TraceMode_DblClick;


extern	int	ActionGameMode;				//액션게임모드

extern smPAT3D  *PatShadow[SHADOW_PAT_MAX];			//그림자
extern smPAT3D  *PatArrow;							//화살
extern smPAT3D	*PatEffectShield;					//방패 이펙트
extern smPAT3D	*PatSparkShield;					//스파크쉴드 이펙트
extern smPAT3D	*PatDivineShield;					//디바인인할레이션
extern smPAT3D	*PatGodlyShield;					//가들리쉴드
extern smPAT3D	*PatCrown;							//블레스캐슬 왕관

extern Unit	chrOtherPlayer[OTHER_PLAYER_MAX];
extern char PlayerName[64];

extern	int	RecordFailCount;				//저장 실피 카운터


//무대 세트 클래스
extern smSTAGE3D *smStage;
extern int PlayCounter;

//extern DWORD	dwPlayTime;					//현재의 윈도우 시간 ( 플레이 용 )
extern DWORD	dwMemError;					//메모리 에러 확인 코드

extern int	BackColor_R ;				//배경색 R
extern int	BackColor_G ;				//배경색 G
extern int	BackColor_B ;				//배경색 B

extern int	BackColor_mR;				//배경색 변경값 R
extern int	BackColor_mG;				//배경색 변경값 G
extern int	BackColor_mB;				//배경색 변경값 B

extern int	DarkLevel_Fix;				//어둠 값 고정

extern int DarkLevel;					//어둠 값
extern int DarkLightRange;			//어두울때 조명 범위
extern DWORD	dwGameWorldTime;	//게임의 월드시간
extern DWORD	dwGameHour;			//게임의 시
extern DWORD	dwGameMin;			//게임의 분
extern DWORD	dwGameTimeOffset;

extern DWORD	UseEtherCoreCode;	//에티르 코어 사용


extern int MatBlood[2];			//피튀기는 메트리얼

extern int MatEnergyBox[2];
extern int MatEnergyBoxNew[2];

extern	int WeatherMode;		//날씨

extern int		MsTraceCount;
extern int		MsTraceMode;

extern	RECT	MsSelRect;
extern	POINT	MsSelPos;

extern	int		SelMouseButton;			//사용 선택된 마우스

extern  int		AttCancel;						//공격 취소
extern  int		AttAutoCont;					//자동 공격


extern  Unit	*lpCharSelPlayer;
extern	Unit	*lpCharMsTrace;			//이동 목표 캐릭터

extern	int		RestartPlayCount;			//재시작 무적 시작 카운트


//공격 받았을때 회피 카운터
extern int	Record_BlockCount;
extern int	Record_DefenceCount;
extern int	Record_RecvDamageCount;
extern int  Record_TotalRecvDamageCount;

extern DWORD SkillFalconPoint;					//팔콘 스킬 포인트 저장용


//오토 마우스 감지용
extern	DWORD	AutoMouse_LastCheckTime;
extern	DWORD	AutoMouse_StartCheckTime;
extern	int		AutoMouse_WM_Count;
extern	int 	AutoMouse_Distance;
extern	int		AutoMouse_Attack_Count;


//마우스로 찍은 플레이어로의 각도를 구해준다
int GetMouseSelAngle( );

extern char *NpcSelectedName;			//선택된 NPC 이름


extern int QuitSave;


//신바람 마스크
#define	sinITEM_WEAPON	0x01000000
#define	sinITEM_DEFENCE	0x02000000
#define	sinITEM_MASK1	0xFF000000
#define	sinITEM_MASK2	0xFFFF0000
#define	sinITEM_MASK3	0x0000FFFF


//코멘드 라인 ( winmain.cpp )
extern char szCmdLine[128];
extern int QuitSave;
extern DWORD	dwLastMouseMoveTime;
extern DWORD	dwLastCharMoveTime;


//////////////// 박철호 동영상 플레이어 /////////////
extern int ParkPlayMode;		//-플립금지 0-일반 +슬립시간(최대 1000)
extern int ParkPlaying;			//동영상 플레이중

