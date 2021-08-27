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


//���� ��Ʈ Ŭ������!
smSTAGE3D		*smStage = 0;

//DWORD			dwPlayTime = 0;					//������ ������ �ð� ( �÷��� �� )
DWORD			dwMemError = 8080;				//�޸� ���� Ȯ�� �ڵ�

int	smStageCount = 0;

int invPlayerArmor = 0;

DWORD	dwBattleTime = 0;				//�ֱ� ���� �ð�
DWORD	dwBattleQuitTime = 0;			//������ ���� �Ϸ� �Ҷ�
DWORD	dwCloseBoxTime = 0;				//�۾�â ���� �޼���

int		RestartPlayCount = 0;					//����� ���� ���� ī��Ʈ

DWORD SkillFalconPoint;					//���� ��ų ����Ʈ �����

int InvArmorFileCode[] =
{ 0 ,9,1, 5 };

int	DarkLevel = 0;					//��� ��
int	BackColor_R = 0;				//���� R
int	BackColor_G = 0;				//���� G
int	BackColor_B = 0;				//���� B

int	BackColor_mR = 0;				//���� ���氪 R
int	BackColor_mG = 0;				//���� ���氪 G
int	BackColor_mB = 0;				//���� ���氪 B

int	DarkLevel_Fix = 0;				//��� �� ����

int	DarkLightRange = 180 * fONE;		//��οﶧ ���� ����

DWORD	dwGameWorldTime = 0;			//������ ����ð�
DWORD	dwGameHour = 12;					//������ ��
DWORD	dwGameMin = 0;					//������ ��
DWORD	dwGameTimeOffset = 0;

int DarkLight = 0;

//���� ����
int WeatherMode = 0;
int Thunder = 0;

//PK���
int	PkMode = 0;

int DispApp_SkillPoint = 0;			//������ �ð����� ��ų ����Ʈ

int rcnt2;

int modelX = 255;
int modelZ = 512;
int wflag = 0;
int wrad = 0;

DWORD	UseEtherCoreCode = 0;			//��Ƽ�� �ھ� ���

int	RecordFailCount = 0;				//���� ���� ī����

//���� �޾����� ȸ�� ī����
int	Record_BlockCount = 0;
int	Record_DefenceCount = 0;
int Record_RecvDamageCount = 0;
int Record_TotalRecvDamageCount = 0;


//���� ���콺 ������
DWORD	AutoMouse_LastCheckTime = 0;
DWORD	AutoMouse_StartCheckTime = 0;
int		AutoMouse_WM_Count = 0;
int 	AutoMouse_Distance = 0;
int		AutoMouse_Attack_Count = 0;

//ȭ��
//smPAT3D *PatTest;

//ȭ��
smPAT3D *PatArrow;
//���� ����Ʈ
smPAT3D *PatEffectShield = 0;
//����ũ���� ����Ʈ
smPAT3D *PatSparkShield = 0;
//��������ҷ��̼�
smPAT3D *PatDivineShield = 0;
//���鸮 ����
smPAT3D *PatGodlyShield = 0;
//����ĳ�� �հ�
smPAT3D *PatCrown = 0;

//�׸���
smPAT3D *PatShadow[SHADOW_PAT_MAX] = { 0,0,0,0 };

smPAT3D *PatIceFoot[ICE_FOOT_PAT_MAX];


int	Moving_DblClick = 0;
POINT3D	MousePos_DblClick;

POINT3D	TracePos_DblClick;
int TraceMode_DblClick = 0;

int	ActionGameMode = 0;

DWORD	dwRotPlayDelayTime = 0;

Unit	chrOtherPlayer[OTHER_PLAYER_MAX];

CharacterData	sCharacterData_Back;			//NPC ��ġ�� �⺻ ����Ÿ �ӽ� ����


int	MatEachBox;
int	MatEachMenuBox;
int MatEnergyBox[2];
int MatEnergyBoxNew[2];
int MatLight[4];

int	MatEachTradeButton[2];	//�޴� ������ ��ȯ ��ư 
int MatMonBroodImage[8];	//���� ���� �̹���


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

//ĳ���� ���� ����Ʈ
static char szDataDirectory[256];
char szCharFileList[256][256];
int CharFileCnt;
int CharPlayCnt = 0;

//���� �̸����� ���� ���丮�� ã�� ����
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
int CharacterJob = 0;			//���� �ڵ� �Ѱ���


extern	char *szNpcInfoPath;

DWORD	dwSoD_ResultTime = 0;		//SoD ��Ȳâ ���� �ð�


sBILLING_INFO	*sBiInfo = 0;


int PartCnt = 0;



//int LoadTest = 0;


int		MsTraceCount = 0;
int		MsTraceMode = 0;
RECT	MsSelRect;
POINT	MsSelPos;

int		SelMouseButton = 0;			//��� ���õ� ���콺 ��ư

Unit	*lpCharSelPlayer = 0;		//���� ĳ����
Unit	*lpCharMsTrace = 0;			//�̵� ��ǥ ĳ����

int AttFlag = 0;
int	AttCancel;						//���� ���
int	AttAutoCont = 0;				//���� ���� ���


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
