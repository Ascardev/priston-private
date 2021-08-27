#include "StdAfx.h"
#include "character.h"
#include "playmain.h"
#include "fileread.h"
#include "netplay.h"
#include "effectsnd.h"

#include "record.h"
#include "playsub.h"
#include "skillsub.h"

#include "cracker.h"
#include "AreaServer.h"

#include "srcserver\onserver.h"

extern HWND hwnd;
extern int MouseButton[3];


//무대 세트 클래스다!
smSTAGE3D		*smStage = 0;

//DWORD			dwPlayTime = 0;					//현재의 윈도우 시간 ( 플레이 용 )
DWORD			dwMemError = 8080;				//메모리 에러 확인 코드

int	smStageCount = 0;

int invPlayerArmor = 0;

DWORD	dwBattleTime = 0;				//최근 전투 시간
DWORD	dwBattleQuitTime = 0;			//전투중 종료 하려 할때
DWORD	dwCloseBoxTime = 0;				//작업창 종료 메세지

int		RestartPlayCount = 0;					//재시작 무적 시작 카운트

DWORD SkillFalconPoint;					//팔콘 스킬 포인트 저장용

int InvArmorFileCode[] =
{ 0 ,9,1, 5 };

int	DarkLevel = 0;					//어둠 값
int	BackColor_R = 0;				//배경색 R
int	BackColor_G = 0;				//배경색 G
int	BackColor_B = 0;				//배경색 B

int	BackColor_mR = 0;				//배경색 변경값 R
int	BackColor_mG = 0;				//배경색 변경값 G
int	BackColor_mB = 0;				//배경색 변경값 B

int	DarkLevel_Fix = 0;				//어둠 값 고정

int	DarkLightRange = 180 * fONE;		//어두울때 조명 범위

DWORD	dwGameWorldTime = 0;			//게임의 월드시간
DWORD	dwGameHour = 12;					//게임의 시
DWORD	dwGameMin = 0;					//게임의 분
DWORD	dwGameTimeOffset = 0;

int DarkLight = 0;

//날씨 관련
int WeatherMode = 0;
int Thunder = 0;

//PK모드
int	PkMode = 0;

int DispApp_SkillPoint = 0;			//설정된 시간적용 스킬 포인트

int rcnt2;

int modelX = 255;
int modelZ = 512;
int wflag = 0;
int wrad = 0;

DWORD	UseEtherCoreCode = 0;			//에티르 코어 사용

int	RecordFailCount = 0;				//저장 실피 카운터

//공격 받았을때 회피 카운터
int	Record_BlockCount = 0;
int	Record_DefenceCount = 0;
int Record_RecvDamageCount = 0;
int Record_TotalRecvDamageCount = 0;


//오토 마우스 감지용
DWORD	AutoMouse_LastCheckTime = 0;
DWORD	AutoMouse_StartCheckTime = 0;
int		AutoMouse_WM_Count = 0;
int 	AutoMouse_Distance = 0;
int		AutoMouse_Attack_Count = 0;

//화살
//smPAT3D *PatTest;

//화살
smPAT3D *PatArrow;
//방패 이펙트
smPAT3D *PatEffectShield = 0;
//스파크쉴드 이펙트
smPAT3D *PatSparkShield = 0;
//디바인인할레이션
smPAT3D *PatDivineShield = 0;
//가들리 쉴드
smPAT3D *PatGodlyShield = 0;
//블레스캐슬 왕관
smPAT3D *PatCrown = 0;

//그림자
smPAT3D *PatShadow[SHADOW_PAT_MAX] = { 0,0,0,0 };

smPAT3D *PatIceFoot[ICE_FOOT_PAT_MAX];


int	Moving_DblClick = 0;
POINT3D	MousePos_DblClick;

POINT3D	TracePos_DblClick;
int TraceMode_DblClick = 0;

int	ActionGameMode = 0;

DWORD	dwRotPlayDelayTime = 0;

Unit	chrOtherPlayer[OTHER_PLAYER_MAX];

CharacterData	sCharacterData_Back;			//NPC 설치시 기본 데이타 임시 저장


int	MatEachBox;
int	MatEachMenuBox;
int MatEnergyBox[2];
int MatEnergyBoxNew[2];
int MatLight[4];

int	MatEachTradeButton[2];	//메뉴 아이템 교환 버튼 
int MatMonBroodImage[8];	//몬스터 종족 이미지


int PlayCounter = 0;

char PlayerName[64] = { 0,0,0,0 };


struct _DRAW_LIGHTLIST {
	smLIGHT3D	*smLight;
	int			x, y, z;
};


_DRAW_LIGHTLIST	DrawLight[64];
_DRAW_LIGHTLIST	DrawLightSmall[64];
int DrawLightCnt;
int DrawLightSmallCnt;



int doop = 0;

//캐릭터 파일 리스트
static char szDataDirectory[256];
char szCharFileList[256][256];
int CharFileCnt;
int CharPlayCnt = 0;

//파일 이름으로 부터 디렉토리를 찾아 설정
static char *SetDirectoryFromFile(char *filename)
{
	int len;
	int cnt;

	lstrcpy(szDataDirectory, filename);

	len = lstrlen(szDataDirectory);

	for (cnt = len; cnt >= 0; cnt--)
		if (szDataDirectory[cnt] == '\\') break;

	szDataDirectory[cnt + 1] = NULL;

	return szDataDirectory;
}


char szNpcFileList[64][64];
int NpcFileCnt;
int NpcPlayCnt = 0;

char *NpcSelectedName = 0;






char szPlayerCode[32];
int CharacterJob = 0;			//직업 코드 넘겨줌


extern	char *szNpcInfoPath;

DWORD	dwSoD_ResultTime = 0;		//SoD 상황창 갱신 시간


sBILLING_INFO	*sBiInfo = 0;


int PartCnt = 0;



//int LoadTest = 0;


int		MsTraceCount = 0;
int		MsTraceMode = 0;
RECT	MsSelRect;
POINT	MsSelPos;

int		SelMouseButton = 0;			//사용 선택된 마우스 버튼

Unit	*lpCharSelPlayer = 0;		//선택 캐릭터
Unit	*lpCharMsTrace = 0;			//이동 목표 캐릭터

int AttFlag = 0;
int	AttCancel;						//공격 취소
int	AttAutoCont = 0;				//연속 공격 모드


#define AUTO_DEAD_COUNT		(70*60*8)
int AutoDeathCounter = 0;
int FixedWidth = 200;
DWORD	dwClassDelayTime = 0;

extern int RestoreTexFlag;
extern POINT	pCursorPos;


int testframe = 0;
int	LastRendSucessCount = 0;
int	DispCharLimitMode = 0;

#define	DISP_CHAR_LIMIT			20
#define	DISP_CHAR_LIMIT_MAX		30
#define	DISP_CHAR_NEAR_DIST		( (10*64)*(10*64) )

extern BYTE VRKeyBuff[256];

int Draw2DCounter = 0;

extern int ViewPointLen;

extern DWORD smBackColor;


Unit	chrEachPlayer;
Unit *chrEachMaster = 0;
int		EachTradeButton = 0;
int		EachTradeButtonMode = 0;
RECT	RectTradeButton;

POINT3D EachCameraPos;
int	DispEachMode = 0;


int ParkPlayInit = 0;
int ParkPlayMode = 0;
int ParkPlaying = 0;
RECT ParkPlayRect;
