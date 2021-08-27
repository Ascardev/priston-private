#include "StdAfx.h"
#include "..\\HoBaram\\HoTextFile.h"
#include "..\\HoBaram\\HoMinMax.h"
#include "..\\HoBaram\\HoNewParticle.h"
#include "..\\HoBaram\\HoNewParticleMgr.h"

#include "..\\tjboy\\clanmenu\\tjclanDEF.h"
#include "..\\tjboy\\clanmenu\\tjclan.h"
#include "..\\CurseFilter.h"

int  CharacterPosX = 0;
int  CharacterPosZ = 0;

int  MouseDblClick;

char SelectCharacterName1[3][500];
char SelectCharacterName2[3][500];

char JobSelectCharacterName1[4][500];
char JobSelectCharacterName2[4][500];


static int UserCharacterPos[5][2] =
{
	{ 0 ,-110 },
	{ -35 ,-90 },
	{  35 ,-90 },
	{ -70 ,-60 },
	{ 70 ,-60 }
};

static int JobCharacterPos[5][2] =
{
	{ -81, -320},
	{ -41, -325},
	{ -1 , -330},
	{ 39 , -325},
	{ 79 , -320}
};
static char *szTempFighterBodyName = "char\\tmABCD\\b001.ini";
static char *szTempMechBodyName = "char\\tmABCD\\a001.ini";
static char *szTempArcherBodyName = "char\\tmABCD\\d001.ini";
static char *szTempPikeBodyName = "char\\tmABCD\\c001.ini";
static char *szTempAssaBodyName = "char\\tmABCD\\e001.ini";

static char *szMorMechBodyName = "char\\tmABCD\\ma001.ini";
static char *szMorFighterBodyName = "char\\tmABCD\\mb001.ini";
static char *szMorPikeBodyName = "char\\tmABCD\\mc001.ini";
static char *szMorArcherBodyName = "char\\tmABCD\\md001.ini";
static char *szMorAssaBodyName = "char\\tmABCD\\me001.ini";

char *szTempMechFaceName[3] = { "char\\tmABCD\\tmh-a01.inf" ,"char\\tmABCD\\tmh-a02.inf" ,"char\\tmABCD\\tmh-a03.inf" };
char *szTempFighterFaceName[3] = { "char\\tmABCD\\tmh-b01.inf" ,"char\\tmABCD\\tmh-b02.inf" ,"char\\tmABCD\\tmh-b03.inf" };
char *szTempPikeFaceName[3] = { "char\\tmABCD\\tmh-c01.inf" ,"char\\tmABCD\\tmh-c02.inf" ,"char\\tmABCD\\tmh-c03.inf" };
char *szTempArcherFaceName[3] = { "char\\tmABCD\\tfh-D01.inf" ,"char\\tmABCD\\tfh-d02.inf" ,"char\\tmABCD\\tfh-d03.inf" };
char *szTempAssaFaceName[3] = { "char\\tmABCD\\tfh-E01.inf" ,"char\\tmABCD\\tfh-E02.inf" ,"char\\tmABCD\\tfh-E03.inf" };

char *szMorMechFaceName[3] = { "char\\tmABCD\\Mmh-A01.inf" ,"char\\tmABCD\\Mmh-A02.inf" ,"char\\tmABCD\\Mmh-A03.inf" };
char *szMorFighterFaceName[3] = { "char\\tmABCD\\Mfh-B01.inf" ,"char\\tmABCD\\Mfh-B02.inf" ,"char\\tmABCD\\Mfh-B03.inf" };
char *szMorPikeFaceName[3] = { "char\\tmABCD\\Mfh-C01.inf" ,"char\\tmABCD\\Mfh-C02.inf" ,"char\\tmABCD\\Mfh-C03.inf" };
char *szMorArcherFaceName[3] = { "char\\tmABCD\\Mmh-D01.inf" ,"char\\tmABCD\\Mmh-D02.inf" ,"char\\tmABCD\\Mmh-D03.inf" };
char *szMorAssaFaceName[3] = { "char\\tmABCD\\Mmh-E01.inf" ,"char\\tmABCD\\Mmh-E02.inf" ,"char\\tmABCD\\Mmh-E03.inf" };


static int TempFaceCount[5] = { 3, 3, 3, 3, 3 };

static int	TempFacePos[5][4] =
{
	{400 - 64 - 128,400 - 64,400 - 64 + 128,-1},
	{400 - 64 - 128,400 - 64,400 - 64 + 128,-1},
	{400 - 64 - 128,400 - 64,400 - 64 + 128,-1},
	{400 - 64 - 128,400 - 64,400 - 64 + 128,-1},
	{400 - 64 - 128,400 - 64,400 - 64 + 128,-1}
};

int TempNewCharacterInit[5][6] =
{
	//JobCode, Strentch, Sprit, Talent, Defence, Health
	{2,        24,       8,     25,     18,      24}, //机械
	{1,        28,       6,     21,     17,      27}, //武士
	{4,        26,       9,     20,     19,      25}, //枪兵
	{3,        17,      11,     21,     27,      23},  //弓手
	{9,        25,      10,     22,     20,      22}  //刺客
};

int MorNewCharacterInit[5][6] =
{
	//JobCode, Strentch, Sprit, Talent, Defence, Health
	{6,        26,       13,     17,     19,      24}, //游侠
	{5,        23,       15,     19,     19,      23}, //魔枪
	{8,        15,       28,     21,     15,      20}, //祭司
	{7,        16,       29,     19,     14,      21},  //法师
	{10,       15,       27,     20,     15,      22}  //法师
};

HoNewCharInfo	NewCharInfo;

static int GetSelRectChar(Unit *lpChar);

static int GetSelRectJobChar(Unit *lpChar);
static int CameraZPos[5] = { fONE * 300, fONE * 300 + fONE * 70, fONE * 300 + fONE * 250, fONE * 300 + fONE * 420, fONE * 300 + fONE * 400 };

HoLogin::HoLogin()
{
	ErrorSelect = ERROR_NONE;
	SelectCurrentState = CHARACTER_SELECT_STATE;
	SelectNextState = CHARACTER_SELECT_STATE;

	UserCharacterCount = 0;
	JobCharacterCount = 0;

	TempscronMarkImage = -1;
	TempscronLogoImage = -1;

	GameMapImage[0] = NULL;
	GameMapImage[1] = NULL;

	MoryonMarkImage = -1;
	MoryonLogoImage = -1;

	Stage = nullptr;
}

HoLogin::~HoLogin()
{
	
}

extern Unit chrPlayer;

int HoLogin::Init()
{
	if (Load() == 0)
		return 0;

	StartErrorDelayFlag = FALSE;
	ClanMarkUpdateSuccessFlag = FALSE;
	g_NewParticleMgr.Init();
	//InitAssaEffect();

	FocusWndFlag = FALSE;
	CharacterStopFlag = FALSE;
	CharacterReturnFlag = FALSE;

	NewCharacterImageBlendCount = 50;
	NewCharacterImageBlendFlag = false;

	MapBlendCount = 0;
	MapBlendFlag = FALSE;
	ZeroMemory(UserCharacterNewName, sizeof(UserCharacterNewName));

	smRender.SMMULT_PERSPECTIVE_HEIGHT = RENDCLIP_WIDE_MULT_PERSPECTIVE_HEIGHT;
	MidX = (int)RESOLUTION_WIDTH / 2;
	MidY = (int)RESOLUTION_HEIGHT / 2;

	FadeCurrentState = FADE_OUT;
	FadeNextState = FADE_OUT;

	SelectCurrentState = CHARACTER_SELECT_STATE;
	SelectNextState = CHARACTER_SELECT_STATE;
	SelectSubState = SUB_SELECT_NONE;

	TarDist = CameraZPos[SelectCurrentState];
	CaAngle.x = 90;
	CaAngle.y = 0;
	CaAngle.z = 0;
	TarPosi.x = 0;
	TarPosi.y = 16 * fONE;
	TarPosi.z = 0;

	smRender.SMMULT_PERSPECTIVE_HEIGHT = RENDCLIP_DEFAULT_MULT_PERSPECTIVE_HEIGHT;
	MidX = RESOLUTION_WIDTH >> 1;
	MidY = RESOLUTION_HEIGHT >> 1;

	MouseDownCharacterNum = -1;
	MouseMoveCharacterNum = -1;
	JobBodySelectNum = -1;
	JobFaceSelectNum = -1;

	RaceMarkBlendCount = 0;

	FadeCurrentState = FADE_OUT;
	FadeNextState = FADE_OUT;

	StopBGM();
	OpenBGM("StartImage\\Login\\CharacterSelect.wav");
	PlayBGM();

	PlayWav2(9 - 1, 1);
	PlayWav2(10 - 1, 1);
	PlayWav2(11 - 1, 1);

	SetVolumeBGM(0);
	PlayWav_VolChange(9 - 1, 0);
	PlayWav_VolChange(10 - 1, 0);
	PlayWav_VolChange(11 - 1, 0);

	SetFade();
	smInitColorZClip(0, 0, 0);
	smRender.Color_R = 0;
	smRender.Color_G = 0;
	smRender.Color_B = 0;
	smRender.Color_A = 0;

	void InitSelectCha();
	InitSelectCha();

	void web_DB_start();
	web_DB_start();

	void clanMENU_INIT(int setN);
	clanMENU_INIT(0);

	void ClearSelectCha();
	ClearSelectCha();

	int HONG_GetChaClanName(char* id, char* chaname);

	if (DownUserCharacterCount > 0)
	{
		for (int index = 0; index < DownUserCharacterCount; index++)
		{
			AddUserCharacter(DownUserCharacterInfo[index].BodyName, DownUserCharacterInfo[index].FaceName, DownUserCharacterInfo[index].Job);
			HONG_GetChaClanName(UserAccount, DownUserCharacterInfo[index].Name);
		}
	}

	ReadTextures();

	return TRUE;
}

extern int MatEachBox;

int HoLogin::Load()
{
	Stage = smSTAGE3D_ReadASE("cSelect\\Login.ASE", smStage);

	if (Stage)
		Stage->Head = TRUE;
	else
		return 0;

	OkButton.Init("StartImage\\Login\\CharSelect\\Bt_select.tga", 128, 32);
	OkButton.InitCrashRect(10, 0, 110, 32);

	BackButton.Init("StartImage\\Login\\CharSelect\\Bt_back.tga", 128, 32);
	BackButton.InitCrashRect(20, 0, 103, 32);

	NewCharButton.Init("StartImage\\Login\\CharSelect\\bt-NewChar.tga", 128, 32);
	NewCharButton.InitCrashRect(10, 0, 110, 32);

	QuitButton.Init("StartImage\\Login\\CharSelect\\Bt_exit.tga", 128, 32);
	QuitButton.InitCrashRect(15, 0, 108, 32);

	DeleteButton.Init("StartImage\\Login\\CharSelect\\Bt_delet.tga", 128, 32);
	DeleteButton.InitCrashRect(10, 0, 108, 32);

	UserCharacterInfoBackImage = CreateTextureMaterial("StartImage\\Login\\UserCharacterInfo.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	UserCharacterInfoImage = CreateTextureMaterial("StartImage\\Login\\CharacterInfo.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	TempscronMarkImage = CreateTextureMaterial("StartImage\\Login\\CharSelect\\mark_T.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempscronLogoImage = CreateTextureMaterial("StartImage\\Login\\CharSelect\\T-tempscron.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	MoryonMarkImage = CreateTextureMaterial("StartImage\\Login\\CharSelect\\mark_M.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MoryonLogoImage = CreateTextureMaterial("StartImage\\Login\\CharSelect\\T-Morion.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	//机械
	TempFaceImage[0][0][0] = CreateTextureMaterial("StartImage\\Login\\TmA01-01.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[0][0][1] = CreateTextureMaterial("StartImage\\Login\\TmA01-02.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[0][1][0] = CreateTextureMaterial("StartImage\\Login\\TmA02-01.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[0][1][1] = CreateTextureMaterial("StartImage\\Login\\TmA02-02.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[0][2][0] = CreateTextureMaterial("StartImage\\Login\\TmA03-01.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[0][2][1] = CreateTextureMaterial("StartImage\\Login\\TmA03-02.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	//武士
	TempFaceImage[1][0][0] = CreateTextureMaterial("StartImage\\Login\\TmB01-01.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[1][0][1] = CreateTextureMaterial("StartImage\\Login\\TmB01-02.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[1][1][0] = CreateTextureMaterial("StartImage\\Login\\TmB02-01.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[1][1][1] = CreateTextureMaterial("StartImage\\Login\\TmB02-02.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[1][2][0] = CreateTextureMaterial("StartImage\\Login\\TmB03-01.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[1][2][1] = CreateTextureMaterial("StartImage\\Login\\TmB03-02.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	//枪兵
	TempFaceImage[2][0][0] = CreateTextureMaterial("StartImage\\Login\\TmC01-01.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[2][0][1] = CreateTextureMaterial("StartImage\\Login\\TmC01-02.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[2][1][0] = CreateTextureMaterial("StartImage\\Login\\TmC02-01.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[2][1][1] = CreateTextureMaterial("StartImage\\Login\\TmC02-02.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[2][2][0] = CreateTextureMaterial("StartImage\\Login\\TmC03-01.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[2][2][1] = CreateTextureMaterial("StartImage\\Login\\TmC03-02.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	//弓手
	TempFaceImage[3][0][0] = CreateTextureMaterial("StartImage\\Login\\TfD01-01.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[3][0][1] = CreateTextureMaterial("StartImage\\Login\\TfD01-02.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[3][1][0] = CreateTextureMaterial("StartImage\\Login\\TfD02-01.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[3][1][1] = CreateTextureMaterial("StartImage\\Login\\TfD02-02.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[3][2][0] = CreateTextureMaterial("StartImage\\Login\\TfD03-01.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[3][2][1] = CreateTextureMaterial("StartImage\\Login\\TfD03-02.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	//刺客
	TempFaceImage[4][0][0] = CreateTextureMaterial("StartImage\\Login\\TfE01-a.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[4][0][1] = CreateTextureMaterial("StartImage\\Login\\TfE01-b.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[4][1][0] = CreateTextureMaterial("StartImage\\Login\\TfE02-a.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[4][1][1] = CreateTextureMaterial("StartImage\\Login\\TfE02-b.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[4][2][0] = CreateTextureMaterial("StartImage\\Login\\TfE03-a.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[4][2][1] = CreateTextureMaterial("StartImage\\Login\\TfE03-b.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	//游侠
	MorFaceImage[0][0][0] = CreateTextureMaterial("StartImage\\Login\\Moryon\\MmA01-a.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[0][0][1] = CreateTextureMaterial("StartImage\\Login\\Moryon\\MmA01-b.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[0][1][0] = CreateTextureMaterial("StartImage\\Login\\Moryon\\MmA02-a.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[0][1][1] = CreateTextureMaterial("StartImage\\Login\\Moryon\\MmA02-b.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[0][2][0] = CreateTextureMaterial("StartImage\\Login\\Moryon\\MmA03-a.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[0][2][1] = CreateTextureMaterial("StartImage\\Login\\Moryon\\MmA03-b.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	//魔枪
	MorFaceImage[1][0][0] = CreateTextureMaterial("StartImage\\Login\\Moryon\\MfB02-a.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[1][0][1] = CreateTextureMaterial("StartImage\\Login\\Moryon\\MfB02-b.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[1][1][0] = CreateTextureMaterial("StartImage\\Login\\Moryon\\MfB01-a.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[1][1][1] = CreateTextureMaterial("StartImage\\Login\\Moryon\\MfB01-b.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[1][2][0] = CreateTextureMaterial("StartImage\\Login\\Moryon\\MfB03-a.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[1][2][1] = CreateTextureMaterial("StartImage\\Login\\Moryon\\MfB03-b.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	//祭司
	MorFaceImage[2][0][0] = CreateTextureMaterial("StartImage\\Login\\Moryon\\Mfc01-a.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[2][0][1] = CreateTextureMaterial("StartImage\\Login\\Moryon\\Mfc01-b.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[2][1][0] = CreateTextureMaterial("StartImage\\Login\\Moryon\\Mfc02-a.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[2][1][1] = CreateTextureMaterial("StartImage\\Login\\Moryon\\Mfc02-b.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[2][2][0] = CreateTextureMaterial("StartImage\\Login\\Moryon\\Mfc03-a.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[2][2][1] = CreateTextureMaterial("StartImage\\Login\\Moryon\\Mfc03-b.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	//法师 
	MorFaceImage[3][0][0] = CreateTextureMaterial("StartImage\\Login\\Moryon\\Mmd01-a.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[3][0][1] = CreateTextureMaterial("StartImage\\Login\\Moryon\\Mmd01-b.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[3][1][0] = CreateTextureMaterial("StartImage\\Login\\Moryon\\Mmd02-a.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[3][1][1] = CreateTextureMaterial("StartImage\\Login\\Moryon\\Mmd02-b.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[3][2][0] = CreateTextureMaterial("StartImage\\Login\\Moryon\\Mmd03-a.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[3][2][1] = CreateTextureMaterial("StartImage\\Login\\Moryon\\Mmd03-b.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	//萨满
	MorFaceImage[4][0][0] = CreateTextureMaterial("StartImage\\Login\\Moryon\\MmE01-a.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[4][0][1] = CreateTextureMaterial("StartImage\\Login\\Moryon\\MmE01-b.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[4][1][0] = CreateTextureMaterial("StartImage\\Login\\Moryon\\MmE02-a.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[4][1][1] = CreateTextureMaterial("StartImage\\Login\\Moryon\\MmE02-b.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[4][2][0] = CreateTextureMaterial("StartImage\\Login\\Moryon\\MmE03-a.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[4][2][1] = CreateTextureMaterial("StartImage\\Login\\Moryon\\MmE03-b.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	MatEachBox = -1;

	BlackBoxImage = CreateTextureMaterial("StartImage\\Login\\BlackBox.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);

	Message.Init();
	MessageBox.Init();
	InitMessageBox();

	MainBoxFrameImage1[0] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\mainbox_L.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);
	MainBoxFrameImage1[1] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\mainbox_T.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);
	MainBoxFrameImage1[2] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\mainbox_R.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);
	MainBoxFrameImage1[3] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\mainbox_D.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);

	MainBoxFrameImage2[0] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\mainbox_CN1.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);
	MainBoxFrameImage2[1] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\mainbox_CN2.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);
	MainBoxFrameImage2[2] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\mainbox_CN3.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);
	MainBoxFrameImage2[3] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\mainbox_CN4.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);

	TitleBoxFrameImage = CreateTextureMaterial("StartImage\\Login\\CharSelect\\title-box.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);
	TitleNameImage = CreateTextureMaterial("StartImage\\Login\\CharSelect\\title-txt30.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);

	TempscronTextImage = CreateTextureMaterial("StartImage\\Login\\CharSelect\\T-ex_tscr.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);
	MoryonTextImage = CreateTextureMaterial("StartImage\\Login\\CharSelect\\T-ex_mrin.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);

	RaceTextBoxImage[0] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\mark_box1.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);
	RaceTextBoxImage[1] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\mark_box2.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);

	JobTextBoxImage[0] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\T_cls-box1.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);
	JobTextBoxImage[1] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\T_cls-box2.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);

	TempscronJobImage[0][0] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\T_cls-meca_.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempscronJobImage[1][0] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\T_cls-ft_.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempscronJobImage[2][0] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\T_cls-pkm_.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempscronJobImage[3][0] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\T_cls-ac_.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempscronJobImage[4][0] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\T_cls-assa_.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	TempscronJobImage[0][1] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\T_cls-meca.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempscronJobImage[1][1] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\T_cls-ft.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempscronJobImage[2][1] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\T_cls-pkm.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempscronJobImage[3][1] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\T_cls-ac.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempscronJobImage[4][1] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\T_cls-assa.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	MoryonJobImage[0][0] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\T-cls-knt_.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MoryonJobImage[1][0] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\T_cls-atlt_.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MoryonJobImage[2][0] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\T_cls-prts_.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MoryonJobImage[3][0] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\T_cls-mgc_.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MoryonJobImage[4][0] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\T_cls-sha_.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	MoryonJobImage[0][1] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\T-cls-knt.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MoryonJobImage[1][1] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\T_cls-atlt.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MoryonJobImage[2][1] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\T_cls-prts.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MoryonJobImage[3][1] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\T_cls-mgc.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MoryonJobImage[4][1] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\T_cls-sha.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	TempscronJobTextImage[0] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\T_chr-meca.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempscronJobTextImage[1] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\T_chr-ft.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempscronJobTextImage[2] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\T_chr-pkm.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempscronJobTextImage[3] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\T_chr-ac.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempscronJobTextImage[4] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\T_chr-assa.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	MoryonJobTextImage[0] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\T_chr-knt.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MoryonJobTextImage[1] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\T_chr-atlt.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MoryonJobTextImage[2] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\T_chr-prts.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MoryonJobTextImage[3] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\T_chr-mgc.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MoryonJobTextImage[4] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\T_chr-sha.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	FaceBoxBigImage[0] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\face_bigbox1.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	FaceBoxBigImage[1] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\face_bigbox2.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	FaceBoxSmallImage[0] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\face_box_.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	FaceBoxSmallImage[1] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\face_box.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	FaceBoxSmallImage[2] = CreateTextureMaterial("StartImage\\Login\\CharSelect\\face_box2.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	NewCharacterImage = CreateTextureMaterial("StartImage\\Login\\CharSelect\\New_char.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	//ReadTextures();

	return TRUE;
}

char *LoadingImageName[MAX_LOADING_IMAGE] =
{
	"ancientdungeon",
	"ancientweapon1",
	"ancientweapon2",
	"atlantistown",
	"battlearena",
	"battletown",
	"bellatra",
	"boatsystem",
	"cursedtemple3",
	"deathcave",
	"deathisland",
	"endlesstower",
	"forgottentemple",
	"hellsgate",
	"icemine1",
	"ironcore",
	"morion",
	"mysterydeserts",
	"mysteryfields",
	"mysteryforests",
	"naviskotown",
	"partyquests",
	"phillaitown",
	"ricartentown",
	"siegewar",
	"t5quest",
	"tempskron",
	"wastelands",
	"worldmap"
};

void HoLogin::LoadLoadingImage(int level)
{
	char Buffer[128];

	int i = rand() % MAX_LOADING_IMAGE;

	wsprintf(Buffer, "%s%s%s", "StartImage\\Login\\Loading\\", LoadingImageName[i], ".png");

	GameMapImage[0] = LoadDibSurfaceOffscreen(Buffer);

	wsprintf(Buffer, "%s%s%s%s", "StartImage\\Login\\Loading\\", LoadingImageName[i], "_pattern", ".png");

	GameMapImage[1] = LoadDibSurfaceOffscreen(Buffer);
}

int	HoLogin::AddUserCharacter(char *chrFile1, char *chrFile2, int jobCode)
{
	for (int index = 0; index < CHARACTER_USER_MAX; index++)
	{
		if (UserCharacter[index].DisplayFlag == FALSE)
		{
			UserCharacter[index].Init();
			UserCharacter[index].lpStage = Stage;
			SetLoadPattern(&UserCharacter[index], chrFile1, chrFile2, 0, 0);
			UserCharacter[index].SetPosi(UserCharacterPos[index][0] * fONE, Stage->GetHeight(UserCharacterPos[index][0] * fONE, UserCharacterPos[index][1] * fONE), UserCharacterPos[index][1] * fONE, 0, ANGLE_180, 0);
			UserCharacter[index].ActionPattern = 0;
			UserCharacter[index].ChangeMotion(10);
			UserCharacterCount++;
			ReadTextures();

			break;
		}
	}

	return TRUE;
}


int HoLogin::AddJobCharacter(char *chrFile1, char *chrFile2, int index)
{
	if (index == -1)
	{
		JobCharacter[JobCharacterCount].Init();
		JobCharacter[JobCharacterCount].lpStage = Stage;
		JobCharacter[JobCharacterCount].sCharacterData.wPlayerKilling[0] = 0;

		SetLoadPattern(&JobCharacter[JobCharacterCount], chrFile1, chrFile2, 0, 0);

		JobCharacter[JobCharacterCount].SetPosi(JobCharacterPos[JobCharacterCount][0] * fONE,
			Stage->GetHeight(JobCharacterPos[JobCharacterCount][0] * fONE, JobCharacterPos[JobCharacterCount][1] * fONE),
			JobCharacterPos[JobCharacterCount][1] * fONE, 0, ANGLE_180, 0);
		JobCharacter[JobCharacterCount].ActionPattern = 0;
		memset(JobCharacter[JobCharacterCount].szMessage, 0, sizeof(JobCharacter[JobCharacterCount].szMessage));
		memset(JobCharacter[JobCharacterCount].sCharacterData.szName, 0, sizeof(JobCharacter[JobCharacterCount].sCharacterData.szName));

		JobCharacter[JobCharacterCount].ChangeMotion(10);

		JobCharacterCount++;
		ReadTextures();

		JobCharacter[JobCharacterCount].sCharacterData.sSP.sMin = 100;
		JobCharacter[JobCharacterCount].sCharacterData.sSP.sMax = 100;

	}
	else
	{
		if (index >= 0 && index < CHARACTER_JOB_MAX)
		{
			JobCharacter[index].Init();
			JobCharacter[index].lpStage = Stage;
			JobCharacter[index].sCharacterData.wPlayerKilling[0] = 0;

			SetLoadPattern(&JobCharacter[index], chrFile1, chrFile2, 0, 0);
			JobCharacter[index].SetPosi(JobCharacterPos[index][0] * fONE,
				Stage->GetHeight(JobCharacterPos[index][0] * fONE, JobCharacterPos[index][1] * fONE)
				, JobCharacterPos[index][1] * fONE, 0, ANGLE_180, 0);
			JobCharacter[index].ActionPattern = 0;
			memset(JobCharacter[index].szMessage, 0, sizeof(JobCharacter[JobCharacterCount].szMessage));
			memset(JobCharacter[index].sCharacterData.szName, 0, sizeof(JobCharacter[JobCharacterCount].sCharacterData.szName));

			ReadTextures();

			JobCharacter[index].sCharacterData.sSP.sMin = 100;
			JobCharacter[index].sCharacterData.sSP.sMax = 100;
		}
		else
			return FALSE;
	}
	return TRUE;
}
int HoLogin::GetSelectCharacter(Unit *lpChar)
{
	if (lpChar == NULL)
		return FALSE;
	if (lpChar->DisplayFlag == FALSE)
		return FALSE;

	RECT rect;
	POINT	sPos;
	int sez;
	int SelZ = 65536 * 16384;

	if (lpChar)
	{
		int x, y, z;
		int anx, any;

		anx = CaAngle.x;
		any = CaAngle.y;

		any &= ANGCLIP;
		anx &= ANGCLIP;

		auto sPosition = GetMoveLocation(0, 0, -TarDist, anx, any, 0);
		x = TarPosi.x + sPosition.iX;
		y = TarPosi.y + sPosition.iY;
		z = TarPosi.z + sPosition.iZ;

		smRender.SetCameraPosi(x, y, z, anx, any, 0);

		sez = smRender.GetRect2D(lpChar->pX, lpChar->pY + (32 * fONE), lpChar->pZ, 24 * fONE, 32 * fONE, &rect, &sPos);

		if (sez > 0 && sez < SelZ && rect.left<pCursorPos.x && rect.right>pCursorPos.x && rect.top<pCursorPos.y && rect.bottom>pCursorPos.y)
		{
			if (MouseButton[0])
				return 2;

			return 1;
		}
	}
	return FALSE;
}

int HoLogin::SetChangeJobFace(char *charFile1, char *chrFile2, int jobIndex)
{
	int PosX, PosZ;
	PosX = JobCharacter[jobIndex].pX;
	PosZ = JobCharacter[jobIndex].pZ;
	AddJobCharacter(charFile1, chrFile2, jobIndex);
	JobCharacter[jobIndex].SetPosi(PosX, 10, PosZ, 0, ANGLE_180, 0);
	ReadTextures();
	return TRUE;
}
int HoLogin::Close()
{
	int index;

	CloseEachPlayer();

	DELET(Stage);

	for (index = 0; index < UserCharacterCount; index++)
		UserCharacter[index].Init();

	for (index = 0; index < JobCharacterCount; index++)
		JobCharacter[index].Init();

	DELET(GameMapImage[0]);
	DELET(GameMapImage[1]);

	void ClearSelectCha();
	ClearSelectCha();

	return TRUE;
}

extern Unit *chrEachMaster;

int HoLogin::CameraUpDown()
{
	static int	cameraUpDown = 0;

	if (cameraUpDown < 80)
		TarPosi.y += 4;

	if (cameraUpDown >= 80 && cameraUpDown < 160)
		TarPosi.y -= 4;

	cameraUpDown++;

	if (cameraUpDown >= 160)
		cameraUpDown = 0;

	if (SelectCurrentState == CHARACTER_SELECT_STATE)
	{
		if (NewCharacterImageBlendFlag)
			NewCharacterImageBlendCount -= 1.25f;
		else
			NewCharacterImageBlendCount += 1.25f;

		if (NewCharacterImageBlendCount >= 255.f)
		{
			NewCharacterImageBlendFlag = true;
			NewCharacterImageBlendCount = 255.f;
		}
		if (NewCharacterImageBlendCount < 100.f)
		{
			NewCharacterImageBlendFlag = false;
			NewCharacterImageBlendCount = 100.f;
		}
	}

	return TRUE;
}
int HoLogin::Main()
{
	if (ErrorSelect != ERROR_NONE)
	{
		if (StartErrorDelayFlag == FALSE)
		{
			StartErrorDelayFlag = TRUE;
			ErrorDelayCount = 0;
		}
		else
			ErrorDelayCount++;

		if (ErrorDelayCount > 100)
		{
			if (ErrorSelect == ERROR_NONAME_NEWPLAYER)
			{
				hFocusWnd = hTextWnd;
				FocusWndFlag = TRUE;
			}
			ErrorSelect = ERROR_NONE;
			MouseButton[0] = FALSE;
			MouseDblClick = FALSE;

			StartErrorDelayFlag = FALSE;
		}
	}

	void ktj_imsi_clanMENU_Main();
	ktj_imsi_clanMENU_Main();


	int  main_chaC();

	if (main_chaC() && ClanMarkUpdateSuccessFlag == FALSE)
	{
		for (int m = 0; m < 5; m++)
		{
			if (lstrlen(chacldata[m].ChaName) >= 1)
			{
				for (int n = 0; n < DownUserCharacterCount; n++)
				{
					if (lstrcmpi(chacldata[m].ChaName, DownUserCharacterInfo[n].Name) == 0 && DownUserCharacterInfo[n].ClanFlag == FALSE)
					{
						lstrcpy(DownUserCharacterInfo[n].ClanName, chacldata[m].name);
						DownUserCharacterInfo[n].ClanFlag = TRUE;
						if (chacldata[m].hClanMark16)
							DownUserCharacterInfo[n].ClanMark = chacldata[m].hClanMark16;
					}
				}
			}
		}
		ClanMarkUpdateSuccessFlag = TRUE;
	}

	MainEffect();
	CameraUpDown();

	if (SelectCurrentState == START_GAME_STATE && FadeCurrentState == FADE_IN)
	{
		switch (SelectSubState)
		{
		case SUB_SELECT_CHARACTER_USER:
		{
			if (MouseDownCharacterNum != -1)
			{
				memcpy(CharacterName1, DownUserCharacterInfo[MouseDownCharacterNum].BodyName, sizeof(CharacterName1));
				memcpy(CharacterName2, DownUserCharacterInfo[MouseDownCharacterNum].FaceName, sizeof(CharacterName2));
				memset(PlayerName, 0, sizeof(PlayerName));
				memcpy(PlayerName, DownUserCharacterInfo[MouseDownCharacterNum].Name, sizeof(PlayerName));
				CharacterJob = DownUserCharacterInfo[MouseDownCharacterNum].Job;
				GameStartField = DownUserCharacterInfo[MouseDownCharacterNum].StartField;

				CharacterPosX = DownUserCharacterInfo[MouseDownCharacterNum].PosX;
				CharacterPosZ = DownUserCharacterInfo[MouseDownCharacterNum].PosZ;
			}

			SelectSubState = SUB_SELECT_NONE;

			StopAllWav();
			StopBGM();

			return 3;
			break;
		}

		case SUB_SELECT_CHARACTER_NEW_SERVER:
		{
			SelectSubState = SUB_SELECT_NONE;
			ZeroMemory(CharacterName1, sizeof(CharacterName1));
			ZeroMemory(CharacterName2, sizeof(CharacterName2));

			switch (tribeNum)
			{
			case TRIBE_Tempscron:
				switch (JobBodySelectNum)
				{
				case 0:
					// 机械
					memcpy(CharacterName1, szTempMechBodyName, sizeof(CharacterName1));
					memcpy(CharacterName2, szTempMechFaceName[JobFaceSelectNum], sizeof(CharacterName2));
					break;
				case 1:
					// 武士
					memcpy(CharacterName1, szTempFighterBodyName, sizeof(CharacterName1));
					memcpy(CharacterName2, szTempFighterFaceName[JobFaceSelectNum], sizeof(CharacterName2));
					break;
				case 2:
					// 枪兵
					memcpy(CharacterName1, szTempPikeBodyName, sizeof(CharacterName1));
					memcpy(CharacterName2, szTempPikeFaceName[JobFaceSelectNum], sizeof(CharacterName2));
					break;
				case 3:
					// 弓手
					memcpy(CharacterName1, szTempArcherBodyName, sizeof(CharacterName1));
					memcpy(CharacterName2, szTempArcherFaceName[JobFaceSelectNum], sizeof(CharacterName2));
					break;
				case 4:
					// 刺客
					memcpy(CharacterName1, szTempAssaBodyName, sizeof(CharacterName1));
					memcpy(CharacterName2, szTempAssaFaceName[JobFaceSelectNum], sizeof(CharacterName2));
					break;
				}
				NewCharInfo.JobCode = TempNewCharacterInit[JobBodySelectNum][0];
				NewCharInfo.Strength = TempNewCharacterInit[JobBodySelectNum][1];
				NewCharInfo.Spirit = TempNewCharacterInit[JobBodySelectNum][2];
				NewCharInfo.Talent = TempNewCharacterInit[JobBodySelectNum][3];
				NewCharInfo.Dexterity = TempNewCharacterInit[JobBodySelectNum][4];
				NewCharInfo.Health = TempNewCharacterInit[JobBodySelectNum][5];
				break;
			case TRIBE_Moryon:
				switch (JobBodySelectNum)
				{
				case 0:
					// 游侠
					memcpy(CharacterName1, szMorMechBodyName, sizeof(CharacterName1));
					memcpy(CharacterName2, szMorMechFaceName[JobFaceSelectNum], sizeof(CharacterName2));
					break;
				case 1:
					// 魔枪
					memcpy(CharacterName1, szMorFighterBodyName, sizeof(CharacterName1));
					memcpy(CharacterName2, szMorFighterFaceName[JobFaceSelectNum], sizeof(CharacterName2));
					break;
				case 2:
					// 祭司
					memcpy(CharacterName1, szMorPikeBodyName, sizeof(CharacterName1));
					memcpy(CharacterName2, szMorPikeFaceName[JobFaceSelectNum], sizeof(CharacterName2));
					break;
				case 3:
					// 法师
					memcpy(CharacterName1, szMorArcherBodyName, sizeof(CharacterName1));
					memcpy(CharacterName2, szMorArcherFaceName[JobFaceSelectNum], sizeof(CharacterName2));
					break;
				case 4:
					// 萨满
					memcpy(CharacterName1, szMorAssaBodyName, sizeof(CharacterName1));
					memcpy(CharacterName2, szMorAssaFaceName[JobFaceSelectNum], sizeof(CharacterName2));
					break;
				}
				NewCharInfo.JobCode = MorNewCharacterInit[JobBodySelectNum][0];
				NewCharInfo.Strength = MorNewCharacterInit[JobBodySelectNum][1];
				NewCharInfo.Spirit = MorNewCharacterInit[JobBodySelectNum][2];
				NewCharInfo.Talent = MorNewCharacterInit[JobBodySelectNum][3];
				NewCharInfo.Dexterity = MorNewCharacterInit[JobBodySelectNum][4];
				NewCharInfo.Health = MorNewCharacterInit[JobBodySelectNum][5];
				break;
			}
			return 3;
			break;
		}
		}
	}

	if (SelectCurrentState != COMPLETE_SELECT_STATE && SelectCurrentState != START_GAME_STATE)
	{
		for (int index = 0; index < UserCharacterCount; index++)
		{
			if (UserCharacter[index].DisplayFlag)
				UserCharacter[index].Main();
		}
		for (int index = 0; index < JobCharacterCount; index++)
			JobCharacter[index].Main();
	}

	if (SelectCurrentState == SelectNextState)
	{
		if (SelectCurrentState == RACE_SELECT_STATE)
		{
			if (RaceMarkBlendCount < 200)
				RaceMarkBlendCount += 4;
		}
		else if (SelectCurrentState == JOB_SELECT_STATE)
		{
			if (CharacterReturnFlag)
			{
				CharacterStopFlag = FALSE;
				CharacterReturnFlag = FALSE;
				for (int index = 0; index < JobCharacterCount; index++)
				{
					JobCharacter[index].SetPosi(JobCharacterPos[index][0] * fONE, Stage->GetHeight(JobCharacterPos[index][0] * fONE, JobCharacterPos[index][1] * fONE), JobCharacterPos[index][1] * fONE, 0, ANGLE_180, 0);
					JobCharacter[index].ChangeMotion(10);
				}
			}
		}
		else if (SelectCurrentState == FACE_SELECT_STATE)
		{
			if (chrEachMaster != NULL)
				chrEachMaster->bActive = TRUE;
			EachPlayerMain();
		}
		else if (SelectCurrentState == COMPLETE_SELECT_STATE)
		{
			if (FadeCurrentState == FADE_OUT)
			{
				SelectNextState = START_GAME_STATE;
				SetFade();
			}
			if (MouseButton[0] || MouseDblClick || MapBlendCount >= 255)
				SelectNextState = START_GAME_STATE;
		}
	}

	if (FadeCurrentState == FADE_OUT && FadeNextState == FADE_OUT && SelectNextState == RETURN_OPENING_STATE)
	{
		if (SOCKETL != NULL)
			GAMESOCKET->DisconnectFull();

		InitUserCharacter();
		return 2;
	}
	if (SelectCurrentState != SelectNextState)
	{
		if (SelectCurrentState != COMPLETE_SELECT_STATE && SelectNextState != COMPLETE_SELECT_STATE && SelectCurrentState != START_GAME_STATE && SelectNextState != START_GAME_STATE)
		{
			if ((SelectCurrentState == RACE_SELECT_STATE) && (SelectNextState == JOB_SELECT_STATE))
				RaceMarkScaleSize--;

			MouseDownCharacterNum = -1;
			MouseMoveCharacterNum = -1;
			RaceMarkBlendCount = 0;

			static int step = 1000;
			if (SelectNextState >= 0 && SelectNextState < COMPLETE_SELECT_STATE && SelectCurrentState >= 0 && SelectCurrentState < COMPLETE_SELECT_STATE)
			{
				if (SelectNextState > SelectCurrentState)
				{
					TarDist += step;
					if (TarDist > CameraZPos[SelectNextState] + 800)
					{
						TarDist = CameraZPos[SelectNextState];
						SelectCurrentState = SelectNextState;
						step = 1000;
					}

					if ((CameraZPos[SelectNextState] - CameraZPos[SelectCurrentState]) / 16 * 15 + CameraZPos[SelectCurrentState] < TarDist)
						step = 100;
				}
				else if (SelectNextState < SelectCurrentState)
				{
					TarDist -= step;
					if (TarDist < CameraZPos[SelectNextState] - 800)
					{
						TarDist = CameraZPos[SelectNextState];
						SelectCurrentState = SelectNextState;
						step = 1000;
					}

					if ((CameraZPos[SelectCurrentState] - CameraZPos[SelectNextState]) / 16 + CameraZPos[SelectNextState] > TarDist)
						step = 100;
				}
			}
		}

		if (SelectNextState == COMPLETE_SELECT_STATE)
		{
			if (FadeCurrentState == FadeNextState)
				SelectCurrentState = COMPLETE_SELECT_STATE;
		}

		if (SelectNextState == START_GAME_STATE)
			SelectCurrentState = START_GAME_STATE;

		if (SelectCurrentState == FACE_SELECT_STATE && SelectNextState == JOB_SELECT_STATE)
		{
			JobBodySelectNum = -1;
			JobFaceSelectNum = -1;
			memset(UserCharacterNewName, 0, sizeof(UserCharacterNewName));
			SetWindowText(hTextWnd, 0);
			hFocusWnd = NULL;
		}
		if (SelectCurrentState == JOB_SELECT_STATE && SelectNextState == FACE_SELECT_STATE)
		{
			if (JobFaceSelectNum == -1)
			{
				JobFaceSelectNum = 1;
				hFocusWnd = hTextWnd;
				FocusWndFlag = TRUE;

				FaceSelectFirstFlag = FALSE;
			}
		}
	}

	if (SelectNextState == FACE_SELECT_STATE)
	{
		if (JobCharacter[JobBodySelectNum].pZ < -415 * fONE && CharacterStopFlag == FALSE)
		{
			JobCharacter[JobBodySelectNum].MoveFlag = FALSE;
			JobCharacter[JobBodySelectNum].Angle.x = 0;
			JobCharacter[JobBodySelectNum].Angle.y = ANGLE_180;
			JobCharacter[JobBodySelectNum].Angle.z = 0;
			JobCharacter[JobBodySelectNum].ActionPattern = 0;
			JobCharacter[JobBodySelectNum].pZ = -429 * fONE;

			CharacterStopFlag = TRUE;
		}
	}

	return TRUE;

}

int HoLogin::MainDefaultButton()
{
	if (SelectSubState != SUB_SELECT_NONE || ErrorSelect != ERROR_NONE)
		return FALSE;

	if (SelectCurrentState == SelectNextState && SelectCurrentState == CHARACTER_SELECT_STATE)
	{
		if (MouseDownCharacterNum != -1)
		{
			if (DeleteButton.Main(pCursorPos.x, pCursorPos.y, MouseButton[0]))
			{
				SelectSubState = SUB_SELECT_CHARACTER_MANAGE;
				MessageBox.Flag = TRUE;
				PlayWav2(4 - 1);
			}
		}

		int userCount = 0;

		for (int index = 0; index < DownUserCharacterCount; index++)
		{
			if (UserCharacter[index].DisplayFlag)
				userCount++;
		}

		if (userCount == 0)
		{
			if (NewCharButton.Main(pCursorPos.x, pCursorPos.y, MouseButton[0]))
			{
				if (userCount == 0)
				{
					SelectNextState = RACE_SELECT_STATE;
					PlayWav2(5 - 1);
				}
			}
		}
	}

	if (OkButton.Main(pCursorPos.x, pCursorPos.y, MouseButton[0]))
	{
		PlayWav(4 - 1);

		if (SelectCurrentState == CHARACTER_SELECT_STATE)
		{
			if (MouseDownCharacterNum != -1)
			{
				MessageBox.Flag = TRUE;
				SelectSubState = SUB_SELECT_CHARACTER_USER;
			}

			if (MouseDownCharacterNum == -1)
				ErrorSelect = ERROR_SELECT_CHAR;
		}
		else if (SelectCurrentState == RACE_SELECT_STATE)
			ErrorSelect = ERROR_SELECT_RACE;

		else if (SelectCurrentState == JOB_SELECT_STATE)
		{
			if (MouseDownCharacterNum != -1)
			{
				SelectNextState = FACE_SELECT_STATE;
				JobCharacter[JobBodySelectNum].SetTargetPosi(0, (-420 * fONE) >> FLOATNS);
				JobCharacter[JobBodySelectNum].MoveMode = TRUE;

				JobCharacter[JobBodySelectNum].sCharacterData.sWeight.sMin = 0;
				JobCharacter[JobBodySelectNum].sCharacterData.sWeight.sMax = 1000;
				JobCharacter[JobBodySelectNum].sCharacterData.sSP.sMin = 1000;

				JobCharacter[JobBodySelectNum].sCharacterData.sViewBoxZoom = MinMax(0, 0);

				JobCharacter[JobBodySelectNum].bActive = TRUE;
				OpenEachPlayer(&JobCharacter[JobBodySelectNum]);
				MouseDownCharacterNum = -1;
				CharacterReturnFlag = TRUE;
			}

			if (JobBodySelectNum == -1)
				ErrorSelect = ERROR_SELECT_JOB;

		}
		else if (SelectCurrentState == FACE_SELECT_STATE)
		{
			if (JobBodySelectNum != -1 && JobFaceSelectNum != -1)
			{
				hFocusWnd = NULL;
				if (lstrlen(UserCharacterNewName) > 0)
				{
					MessageBox.Flag = TRUE;
					SelectSubState = SUB_SELECT_CHARACTER_NEW;
				}
				else
					ErrorSelect = ERROR_NONAME_NEWPLAYER;
			}

			if (JobFaceSelectNum == -1)
			{
				hFocusWnd = NULL;
				ErrorSelect = ERROR_SELECT_FACE;
			}
		}

	}

	if (QuitButton.Main(pCursorPos.x, pCursorPos.y, MouseButton[0]))
	{
		PlayWav(4 - 1);
		SelectSubState = SUB_SELECT_BACK;
	}

	if (BackButton.Main(pCursorPos.x, pCursorPos.y, MouseButton[0]) && SelectCurrentState != CHARACTER_SELECT_STATE)
	{
		PlayWav(7 - 1);
		SelectNextState = SelectCurrentState - 1;
	}

	return TRUE;
}


int HoLogin::InitUserCharacter()
{
	for (int index = 0; index < CHARACTER_USER_MAX; index++)
	{
		if (UserCharacter[index].DisplayFlag != FALSE)
			UserCharacter[index].Init();
	}
	UserCharacterCount = 0;

	return TRUE;
}
int HoLogin::DrawJobCharacter(int x, int y, int z, int ax, int ay, int az)
{
	smCHAR_SetCameraPosi(x, y, z, ax, ay, az);
	int index;
	BOOL mouseDownFlag = FALSE;
	for (index = 0; index < JobCharacterCount; index++)
	{
		if (SelectCurrentState == JOB_SELECT_STATE && ErrorSelect == ERROR_NONE && SelectCurrentState == SelectNextState)
		{
			smRender.Color_R = 0;
			smRender.Color_G = 0;
			smRender.Color_B = 0;

			if (GetSelectCharacter(&JobCharacter[index]) == 1)
			{
				MouseMoveCharacterNum = index;
				smRender.Color_R = 50;
				smRender.Color_G = 50;
				smRender.Color_B = 50;
			}
			else if (GetSelectCharacter(&JobCharacter[index]) == 2)
			{
				PlayWav(8 - 1);
				MouseDownCharacterNum = index;
				mouseDownFlag = TRUE;
			}

			if (mouseDownFlag == FALSE && MouseButton[0] && pCursorPos.x > 0 && pCursorPos.x < (int)RESOLUTION_WIDTH && pCursorPos.y > 70 && pCursorPos.y < (RESOLUTION_HEIGHT - 50))
				MouseDownCharacterNum = -1;

			if (MouseDownCharacterNum == index)
			{
				JobBodySelectNum = index;
				smRender.Color_R = 80;
				smRender.Color_G = 80;
				smRender.Color_B = 80;

				if (MouseDblClick)
				{
					SelectNextState = FACE_SELECT_STATE;

					JobCharacter[JobBodySelectNum].sCharacterData.sSP.sMin = 100;
					JobCharacter[JobBodySelectNum].sCharacterData.sSP.sMax = 100;

					JobCharacter[JobBodySelectNum].SetTargetPosi(0, (-420 * fONE) >> FLOATNS);
					JobCharacter[JobBodySelectNum].MoveMode = TRUE;
					CharacterReturnFlag = TRUE;

					JobCharacter[JobBodySelectNum].sCharacterData.sWeight.sMin = 0;
					JobCharacter[JobBodySelectNum].sCharacterData.sWeight.sMax = 1000;
					JobCharacter[JobBodySelectNum].sCharacterData.sSP.sMin = 1000;

					JobCharacter[JobBodySelectNum].sCharacterData.sViewBoxZoom = MinMax(0, 0);

					JobCharacter[JobBodySelectNum].bActive = TRUE;

					OpenEachPlayer(&JobCharacter[JobBodySelectNum]);
					MouseDblClick = FALSE;
					MouseButton[0] = FALSE;
				}
			}
		}
		JobCharacter[index].Draw();
		smRender.Color_R = 0;
		smRender.Color_G = 0;
		smRender.Color_B = 0;
	}

	return TRUE;
}
int HoLogin::DrawUserCharacter(int x, int y, int z, int ax, int ay, int az)
{
	smCHAR_SetCameraPosi(x, y, z, ax, ay, az);

	BOOL mouseDownFlag = FALSE;
	MouseMoveCharacterNum = -1;

	for (int index = 0; index < CHARACTER_USER_MAX; index++)
	{
		if (SelectCurrentState == CHARACTER_SELECT_STATE && ErrorSelect == ERROR_NONE)
		{
			smRender.Color_R = 0;
			smRender.Color_G = 0;
			smRender.Color_B = 0;

			if (SelectSubState == SUB_SELECT_NONE)
			{
				if (GetSelectCharacter(&UserCharacter[index]) == 1 && SelectNextState == CHARACTER_SELECT_STATE)
				{
					MouseMoveCharacterNum = index;
					smRender.Color_R = 50;
					smRender.Color_G = 50;
					smRender.Color_B = 50;
				}
				else if (GetSelectCharacter(&UserCharacter[index]) == 2 && SelectNextState == CHARACTER_SELECT_STATE)
				{
					PlayWav(8 - 1);
					MouseMoveCharacterNum = index;
					mouseDownFlag = TRUE;
					MouseDownCharacterNum = index;
				}

				if (mouseDownFlag == FALSE && MouseButton[0] && pCursorPos.x > 0 && pCursorPos.x < (int)RESOLUTION_WIDTH && pCursorPos.y > 60 && pCursorPos.y < (RESOLUTION_HEIGHT - 60))
					MouseDownCharacterNum = -1;
			}

			if (MouseDownCharacterNum == index)
			{
				smRender.Color_R = 80;
				smRender.Color_G = 80;
				smRender.Color_B = 80;
			}
		}

		if (UserCharacter[index].DisplayFlag)
			UserCharacter[index].Draw();

		smRender.Color_R = 0;
		smRender.Color_G = 0;
		smRender.Color_B = 0;
	}

	if (SelectCurrentState == CHARACTER_SELECT_STATE)
	{
		if (MouseDownCharacterNum != -1 && MouseDblClick && pCursorPos.y < RESOLUTION_HEIGHT - 50)
		{
			MessageBox.Flag = TRUE;
			SelectSubState = SUB_SELECT_CHARACTER_USER;
		}
	}
	return TRUE;
}

int HoLogin::DrawTitle(int state)
{
	dsDrawTexImage(TitleBoxFrameImage, (int)RESOLUTION_WIDTH / 2 - 256 / 2, 0, 256, 128, 255);
	switch (state)
	{
	case CHARACTER_SELECT_STATE:
		HoDrawTexImage(TitleNameImage, float((int)RESOLUTION_WIDTH / 2 - 64), 53.f, 128.f, 30.f, 0.f, 0.f, 128.f, 30.f, 255);
		break;
	case RACE_SELECT_STATE:
		HoDrawTexImage(TitleNameImage, float((int)RESOLUTION_WIDTH / 2 - 64), 53.f, 128.f, 30.f, 0.f, 30.f, 128.f, 30.f, 255);
		break;
	case JOB_SELECT_STATE:
		HoDrawTexImage(TitleNameImage, float((int)RESOLUTION_WIDTH / 2 - 64), 53.f, 128.f, 30.f, 0.f, 60.f, 128.f, 30.f, 255);
		break;
	case FACE_SELECT_STATE:
		HoDrawTexImage(TitleNameImage, float((int)RESOLUTION_WIDTH / 2 - 64), 53.f, 128.f, 30.f, 0.f, 90.f, 128.f, 30.f, 255);
		break;
	}
	return TRUE;
}

int HoLogin::DrawGameFrame()
{
	if (SelectNextState != START_GAME_STATE)
	{
		dsDrawTexImage(BlackBoxImage, 0, 0, RESOLUTION_WIDTH, 70, 150);
		dsDrawTexImage(BlackBoxImage, 0, RESOLUTION_HEIGHT - 50, RESOLUTION_WIDTH, 70, 150);

		int frameViewportWidth = RESOLUTION_WIDTH;
		int frameViewportHeight = RESOLUTION_HEIGHT - 140;

		int lineWidthCount = frameViewportWidth / 64;
		int lineWidthRemain = frameViewportWidth % 64;
		int lineHeightCount = frameViewportHeight / 64;
		int lineHeightRemain = frameViewportHeight % 64;

		int index;

		for (index = 0; index < lineWidthCount; index++)
		{
			dsDrawTexImage(MainBoxFrameImage1[1], 4 + 64 * index, 68, 64, 8, 255);
			dsDrawTexImage(MainBoxFrameImage1[3], 4 + 64 * index, RESOLUTION_HEIGHT - 54, 64, 8, 255);
		}

		HoDrawTexImage(MainBoxFrameImage1[1], float(4 + (index * 64)), 68.f, (float)lineWidthRemain, 8.f, 0.f, 0.f, (float)lineWidthRemain, 8.f, 255);
		HoDrawTexImage(MainBoxFrameImage1[3], float(4 + (index * 64)), float(RESOLUTION_HEIGHT - 74), (float)lineWidthRemain, 8.f, 0.f, 0.f, (float)lineWidthRemain, 8.f, 255);

		for (index = 0; index < lineHeightCount; index++)
		{
			dsDrawTexImage(MainBoxFrameImage1[0], 0, 70 + 64 * index, 8, 64, 255);
			dsDrawTexImage(MainBoxFrameImage1[2], RESOLUTION_WIDTH - 8, 70 + 64 * index, 8, 64, 255);
		}
		if (lineHeightRemain > 0)
		{
			HoDrawTexImage(MainBoxFrameImage1[0], 0.f, float(70 + (index * 64)), 8.f, (float)lineHeightRemain, 0.f, 0.f, 8.f, (float)lineHeightRemain, 255);
			HoDrawTexImage(MainBoxFrameImage1[2], float(RESOLUTION_WIDTH - 8), float(70 + (index * 64)), 8.f, (float)lineHeightRemain, 0.f, 0.f, 8.f, (float)lineHeightRemain, 255);
		}

		dsDrawTexImage(MainBoxFrameImage2[0], 0, 68, 130, 64, 255);
		dsDrawTexImage(MainBoxFrameImage2[1], RESOLUTION_WIDTH - 130, 68, 130, 64, 255);
		dsDrawTexImage(MainBoxFrameImage2[2], 0, RESOLUTION_HEIGHT - (64 + 48), 130, 64, 255);
		dsDrawTexImage(MainBoxFrameImage2[3], RESOLUTION_WIDTH - 130, RESOLUTION_HEIGHT - (64 + 48), 130, 64, 255);
	}

	return TRUE;
}

int HoLogin::DrawLight()
{
	static BOOL flag = TRUE;
	static int tt = 0;
	smRender.ClearLight();

	if (FadeCurrentState == FadeNextState && SelectCurrentState != COMPLETE_SELECT_STATE)
	{
		smRender.AddDynamicLight(-200 * fONE + tt * fONE, 0, -300 * fONE, 80, 30, 0, 255, 40000 + tt * fONE);
		smRender.AddDynamicLight(200 * fONE - tt * fONE, 0, -300 * fONE, 80, 30, 0, 255, 40000 + tt * fONE);

		if (SelectCurrentState == FACE_SELECT_STATE)
			smRender.AddDynamicLight(0, 0, -430 * fONE, 110, 40, 0, 255, 10000 + tt * fONE);

		if (tt == 40)
			flag = TRUE;
		else if (tt == 0)
			flag = FALSE;
		if (flag)
			tt--;
		else tt++;
	}

	return TRUE;
}

int HoLogin::DrawMap(int alpha)
{
	if (GameMapImage[1])
		dsDrawTexImage2(GameMapImage[1], 0, 0, (float)RESOLUTION_WIDTH, (float)RESOLUTION_HEIGHT, 255);

	if (GameMapImage[0])
		DrawSprite(((int)RESOLUTION_WIDTH / 2 - 800 / 2), (RESOLUTION_HEIGHT / 2 - 600 / 2), GameMapImage[0], 0, 0, 800, 600);

	return TRUE;
}

int HoLogin::DrawCharacterInfo()
{
	if (ErrorSelect != ERROR_NONE)
		return FALSE;

	if (SelectCurrentState == CHARACTER_SELECT_STATE && MouseMoveCharacterNum != -1 && SelectCurrentState == SelectNextState && FadeCurrentState == FadeNextState && ErrorSelect == ERROR_NONE)
	{
		dsDrawTexImage(UserCharacterInfoBackImage, RESOLUTION_WIDTH / 2 - 128, RESOLUTION_HEIGHT / 2 + RESOLUTION_HEIGHT / 5, 256, 128, 255);
		if (DownUserCharacterInfo[MouseMoveCharacterNum].ClanFlag)
			dsDrawTexImage(UserCharacterInfoImage, RESOLUTION_WIDTH / 2 - 128, RESOLUTION_HEIGHT / 2 + RESOLUTION_HEIGHT / 5, 256, 128, 255);
		else
			HoDrawTexImage(UserCharacterInfoImage, RESOLUTION_WIDTH / 2 - 128, RESOLUTION_HEIGHT / 2 + RESOLUTION_HEIGHT / 5 + 13, 0, 33, 256, 128 - 33, 255);
	}

	int textX = RESOLUTION_WIDTH / 2 - 128 + 102;
	int textY = RESOLUTION_HEIGHT / 2 + RESOLUTION_HEIGHT / 5;

	if (DownUserCharacterInfo[MouseMoveCharacterNum].ClanFlag == TRUE)
		textY += 20;

	if (DownUserCharacterInfo[MouseMoveCharacterNum].ClanFlag)
		dsTextLineOut(0, textX + 17, textY, DownUserCharacterInfo[MouseMoveCharacterNum].ClanName, lstrlen(DownUserCharacterInfo[MouseMoveCharacterNum].ClanName), D3DCOLOR_XRGB(230, 240, 255));

	char buffer[256];
	memset(buffer, 0, sizeof(buffer));
	wsprintf(buffer, "%d", DownUserCharacterInfo[MouseMoveCharacterNum].Level);

	dsTextLineOut(0, textX, textY + 40, buffer, lstrlen(buffer), D3DCOLOR_XRGB(255, 220, 100));
	dsTextLineOut(0, textX, textY + 20, DownUserCharacterInfo[MouseMoveCharacterNum].Name, lstrlen(DownUserCharacterInfo[MouseMoveCharacterNum].Name), D3DCOLOR_XRGB(230, 240, 255));

	int jobCode = DownUserCharacterInfo[MouseMoveCharacterNum].Job;
	jobCode = jobCode & 0xFFFF;
	ZeroMemory(buffer, sizeof(buffer));

	int Race = GetRace(jobCode);

	switch (Race)
	{
	case BROOD_CODE_TEMPSKRON:
		wsprintf(buffer, "%s", "Tempskron");
		break;
	case BROOD_CODE_MORAYION:
		wsprintf(buffer, "%s", "Morion");
		break;
	}

	dsTextLineOut(0, textX, textY + 60, buffer, lstrlen(buffer), D3DCOLOR_XRGB(255, 250, 235));

	auto ps = GetCharacterClassData(DownUserCharacterInfo[MouseMoveCharacterNum].Job, 0);

	if (ps)
		dsTextLineOut(0, textX, textY + 80, ps->pszName, lstrlen(ps->pszName), D3DCOLOR_XRGB(255, 250, 235));

	if (DownUserCharacterInfo[MouseMoveCharacterNum].ClanFlag)
	{
		if (DownUserCharacterInfo[MouseMoveCharacterNum].ClanMark != NULL)
			DrawSprite(textX - 3, textY - 3, DownUserCharacterInfo[MouseMoveCharacterNum].ClanMark, 0, 0, 16, 16, 777);
	}

	return TRUE;
}

int HoLogin::DrawSelectSubState()
{
	if (SelectNextState == COMPLETE_SELECT_STATE || SelectNextState == START_GAME_STATE)
		return FALSE;

	int flag = 0;
	switch (SelectSubState)
	{
	case SUB_SELECT_CHARACTER_MANAGE:
	{
		flag = MessageBox.Main(pCursorPos.x, pCursorPos.y, MouseButton[0]);

		if (flag == 1)
		{
			PlayWav2(4 - 1);

			int isDELETE_character(char *charName);
			int chk = isDELETE_character(DownUserCharacterInfo[MouseDownCharacterNum].Name);

			if (chk == 102 || chk == 1)
			{
				PlayWav2(6 - 1);
				UserCharacter[MouseDownCharacterNum].Init();
				UserCharacterCount--;

				PacketDeleteCharacter sPacket;

				sPacket.iLength = sizeof(PacketDeleteCharacter);
				sPacket.iHeader = PKTHDR_DeleteCharacter;
				STRINGCOPY(sPacket.szUserID, UserAccount);
				STRINGCOPY(sPacket.szCharname, DownUserCharacterInfo[MouseDownCharacterNum].Name);

				SENDPACKETL(&sPacket);

				MouseDownCharacterNum = -1;
				SelectSubState = SUB_SELECT_NONE;
			}
			else if (chk == 101 || chk == 100)
			{
				ErrorSelect = ERROR_DELETE_CLAN_MEMBER;
				SelectSubState = SUB_SELECT_NONE;
			}
			else if (chk == 103)
			{
				ErrorSelect = ERROR_CLAN_SERVER_NONE;
				SelectSubState = SUB_SELECT_NONE;
			}
			else
			{
				ErrorSelect = ERROR_CLAN_SERVER_NONE;
				SelectSubState = SUB_SELECT_NONE;
			}

		}
		else if (flag == 2)
		{
			PlayWav2(4 - 1);
			SelectSubState = SUB_SELECT_NONE;
		}

		break;
	}

	case SUB_SELECT_CHARACTER_USER:
	{
		flag = MessageBox.Main(pCursorPos.x, pCursorPos.y, MouseButton[0]);
		if (flag == 1 || VRKeyBuff[VK_RETURN]) //OK
		{
			PlayWav2(12 - 1);
			SelectNextState = COMPLETE_SELECT_STATE;
			MessageBox.Flag = FALSE;

			LoadLoadingImage(DownUserCharacterInfo[MouseDownCharacterNum].Level);
			SetFade();
		}
		else if (flag == 2) //Cancel
		{
			PlayWav2(4 - 1);
			SelectSubState = SUB_SELECT_NONE;
			MessageBox.Flag = FALSE;
		}
		break;
	}

	case SUB_SELECT_CHARACTER_NEW:
	{
		flag = MessageBox.Main(pCursorPos.x, pCursorPos.y, MouseButton[0]); //TRUE
		if (flag == 1 || VRKeyBuff[VK_RETURN]) //OK
		{
			PlayWav2(12 - 1);
			ServerReturn = NULL;

			PacketCreateCharacter sPacket;

			sPacket.iLength = sizeof(PacketCreateCharacter);
			sPacket.iHeader = PKTHDR_CreateCharacter;
			STRINGCOPY(sPacket.szCharname, UserCharacterNewName);
			STRINGCOPY(sPacket.szUserID, UserAccount);

			SENDPACKETL(&sPacket);

			SelectSubState = SUB_SELECT_CHARACTER_NEW_SERVER;
			LoadLoadingImage(0);
		}
		else if (flag == 2) //Cancel
		{
			PlayWav2(4 - 1);
			SelectSubState = SUB_SELECT_NONE;
			hFocusWnd = hTextWnd;
			FocusWndFlag = TRUE;
		}
		break;
	}

	case SUB_SELECT_CHARACTER_NEW_SERVER:
	{
		if (ServerReturn != NULL)
		{
			if (ServerReturn->WParam == 1)
			{
				SelectNextState = COMPLETE_SELECT_STATE;
				SetFade();
				memset(PlayerName, 0, sizeof(PlayerName));
				memcpy(PlayerName, UserCharacterNewName, sizeof(PlayerName));
			}
			else
			{
				memset(UserCharacterNewName, 0, sizeof(UserCharacterNewName));
				ErrorSelect = ERROR_EXHIST_NEWPLAYER;
				SelectSubState = SUB_SELECT_NONE;
			}
		}
		break;
	}

	case SUB_SELECT_BACK:
	{
		SetFade();
		SelectSubState = SUB_SELECT_NONE;
		SelectNextState = RETURN_OPENING_STATE;
		break;
	}
	}

	return TRUE;
}

void HoLogin::KeyFilter(char *pszValue)
{
	int len;

	if (pszValue != NULL && hFocusWnd != NULL)
	{
		len = strlen(pszValue);

		if (len >= 31 && pszValue[30] != '\t')
		{
			pszValue[30] = '\0';
			SetWindowText(hFocusWnd, NULL);

			SetWindowText(hFocusWnd, pszValue);
			SendMessage(hFocusWnd, EM_SETSEL, strlen(pszValue) + 1, strlen(pszValue) + 1);
		}

		for (int i = 0; i < len; i++)
		{
			if (pszValue[i] == ' ' || pszValue[i] == '@' || pszValue[i] == '#' || pszValue[i] == '$' || pszValue[i] == '%' || pszValue[i] == '^' || pszValue[i] == '&' || pszValue[i] == '*')
			{
				pszValue[i] = '\0';
				SetWindowText(hFocusWnd, pszValue);
				SendMessage(hTextWnd, EM_SETSEL, strlen(pszValue) + 1, strlen(pszValue) + 1);
				break;
			}
		}
	}
}

int		CaretCounta = 0;

int HoLogin::Draw()
{
	MainFade();

	if (ErrorSelect != ERROR_NONE)
	{
		if (MouseButton[0] || MouseDblClick)
		{
			if (ErrorSelect == ERROR_NONAME_NEWPLAYER)
			{
				hFocusWnd = hTextWnd;
				FocusWndFlag = TRUE;
			}
			ErrorSelect = ERROR_NONE;
			MouseButton[0] = FALSE;
			MouseDblClick = FALSE;

			StartErrorDelayFlag = FALSE;
		}

		for (int index = 0; index < 256; index++)
		{
			if (VRKeyBuff[index] == TRUE)
			{
				if (ErrorSelect == ERROR_NONAME_NEWPLAYER)
				{
					hFocusWnd = hTextWnd;
					FocusWndFlag = TRUE;
				}

				ErrorSelect = ERROR_NONE;
				StartErrorDelayFlag = FALSE;
				break;
			}
		}
	}

	DrawSelectSubState();

	int x, y, z;
	int anx, any;

	anx = CaAngle.x;
	any = CaAngle.y;

	any &= ANGCLIP;
	anx &= ANGCLIP;

	auto sPosition = GetMoveLocation(0, 0, -TarDist, anx, any, 0);
	x = TarPosi.x + sPosition.iX;
	y = TarPosi.y + sPosition.iY;
	z = TarPosi.z + sPosition.iZ;

	smRender.SetCameraPosi(x, y, z, anx, any, 0);

	if (Stage)
		Stage->DrawStage(x, y, z, anx, any, 0);

	DrawUserCharacter(x, y, z, anx, any, 0);
	DrawJobCharacter(x, y, z, anx, any, 0);

	DrawLight(); //渲染灯光

	DrawEffect(x, y, z, anx, any, 0);

	DrawGameFrame();
	DrawTitle(SelectCurrentState);

	int twoButtonStartPos =RESOLUTION_WIDTH / 2 - 120;
	int threeButtonStartPos = RESOLUTION_WIDTH / 2 - 150;
	int screenWidthHalf = RESOLUTION_WIDTH / 2;
	int screenHeightHalf = RESOLUTION_HEIGHT / 2;

	if (SelectCurrentState == SelectNextState && FadeCurrentState == FadeNextState)
	{
		MainDefaultButton();

		if (SelectCurrentState == CHARACTER_SELECT_STATE)
		{
			int userCount = 0;
			for (int index = 0; index < DownUserCharacterCount; index++)
			{
				if (UserCharacter[index].DisplayFlag)
					userCount++;
			}

			if (pCursorPos.x > (screenWidthHalf - 128) && pCursorPos.x < (screenWidthHalf + 128) && pCursorPos.y >(screenHeightHalf / 2 - 80) && pCursorPos.y < (screenHeightHalf / 2 + 130) && SelectSubState == SUB_SELECT_NONE && ErrorSelect == ERROR_NONE)
			{
				dsDrawTexImage(NewCharacterImage, (int)RESOLUTION_WIDTH / 2 - 128, 150, 256, 64, 255);

				if (MouseButton[0])
				{
					if (UserCharacterCount < CHARACTER_USER_MAX)
					{
						SelectNextState = RACE_SELECT_STATE;
						PlayWav2(5 - 1);
					}
					else
					{
						MouseButton[0] = FALSE;
						MouseDblClick = FALSE;
						ErrorSelect = ERROR_MAX_NEWPLAYER;
					}
				}
			}
			else
			{
				if (userCount == 0)
					dsDrawTexImage(NewCharacterImage, (int)RESOLUTION_WIDTH / 2 - 128, 150, 256, 64, (int)NewCharacterImageBlendCount);
			}

			if (MouseDownCharacterNum != -1)
				DeleteButton.Draw(0, RESOLUTION_HEIGHT - 40);

			if (userCount == 0)
				NewCharButton.Draw(twoButtonStartPos, RESOLUTION_HEIGHT - 40);
			else
				OkButton.Draw(twoButtonStartPos, RESOLUTION_HEIGHT - 40);
			QuitButton.Draw(twoButtonStartPos + 110, RESOLUTION_HEIGHT - 40);
		}
		else if (SelectCurrentState == RACE_SELECT_STATE)
		{
			OkButton.Draw(threeButtonStartPos, RESOLUTION_HEIGHT - 40);
			BackButton.Draw(threeButtonStartPos + 100, RESOLUTION_HEIGHT - 40);
			QuitButton.Draw(threeButtonStartPos + 200, RESOLUTION_HEIGHT - 40);

			if (pCursorPos.x > (RESOLUTION_WIDTH / 2 - 140) && pCursorPos.x < (RESOLUTION_WIDTH / 2 - 140 + 130) && pCursorPos.y >(RESOLUTION_HEIGHT / 5) && pCursorPos.y < (RESOLUTION_HEIGHT / 5 + 130) && RaceMarkBlendCount >= 200 && ErrorSelect == ERROR_NONE)
			{
				dsDrawTexImage(TempscronMarkImage, RESOLUTION_WIDTH / 2 - 140, RESOLUTION_HEIGHT / 5, 128, 128, 255);
				dsDrawTexImage(TempscronLogoImage, RESOLUTION_WIDTH / 2 - 140 - 6, RESOLUTION_HEIGHT / 5 + 118, 128, 32, 255);

				dsDrawTexImage(RaceTextBoxImage[0], RESOLUTION_WIDTH / 2 - 140 - 175, RESOLUTION_HEIGHT / 5 + 150, 256, 256, 255);
				dsDrawTexImage(RaceTextBoxImage[1], RESOLUTION_WIDTH / 2 - 140 + 256 - 175, RESOLUTION_HEIGHT / 5 + 150, 32, 256, 255);
				dsDrawTexImage(TempscronTextImage, RESOLUTION_WIDTH / 2 - 140 - 175 + 19, RESOLUTION_HEIGHT / 5 + 150 + 12, 256, 128, 255);


				if (MouseButton[0])
				{
					tribeNum = TRIBE_Tempscron;

					JobCharacter[0].Close();
					JobCharacter[1].Close();
					JobCharacter[2].Close();
					JobCharacter[3].Close();
					JobCharacter[4].Close();

					PlayWav2(5 - 1);
					SelectNextState = JOB_SELECT_STATE;
					RaceMarkScaleSize = 128;

					JobCharacterCount = 0;

					JobCharacter[JobCharacterCount].sCharacterData.iClass = CHARACTERCLASS_Mechanician;
					AddJobCharacter(szTempMechBodyName, szTempMechFaceName[0]);

					JobCharacter[JobCharacterCount].sCharacterData.iClass = CHARACTERCLASS_Fighter;
					AddJobCharacter(szTempFighterBodyName, szTempFighterFaceName[0]);

					JobCharacter[JobCharacterCount].sCharacterData.iClass = CHARACTERCLASS_Pikeman;
					AddJobCharacter(szTempPikeBodyName, szTempPikeFaceName[0]);

					JobCharacter[JobCharacterCount].sCharacterData.iClass = CHARACTERCLASS_Archer;
					AddJobCharacter(szTempArcherBodyName, szTempArcherFaceName[0]);

					JobCharacter[JobCharacterCount].sCharacterData.iClass = CHARACTERCLASS_Assassin;
					AddJobCharacter(szTempAssaBodyName, szTempAssaFaceName[0]);

					ReadTextures();
				}
			}
			else
			{
				dsDrawTexImage(TempscronMarkImage, RESOLUTION_WIDTH / 2 - 140, RESOLUTION_HEIGHT / 5, 128, 128, RaceMarkBlendCount);
				dsDrawTexImage(TempscronLogoImage, RESOLUTION_WIDTH / 2 - 140 - 6, RESOLUTION_HEIGHT / 5 + 118, 128, 32, RaceMarkBlendCount);
			}
			if (((int)RESOLUTION_WIDTH / 2 + 12) < pCursorPos.x  && pCursorPos.x < (RESOLUTION_WIDTH / 2 + 12 + 130) && (RESOLUTION_HEIGHT / 5) < pCursorPos.y  && pCursorPos.y < (RESOLUTION_HEIGHT / 5 + 130) && RaceMarkBlendCount >= 200 && ErrorSelect == ERROR_NONE)
			{
				dsDrawTexImage(MoryonMarkImage, RESOLUTION_WIDTH / 2 + 12, RESOLUTION_HEIGHT / 5, 128, 128, 255);
				dsDrawTexImage(MoryonLogoImage, RESOLUTION_WIDTH / 2 + 12 - 6, RESOLUTION_HEIGHT / 5 + 118, 128, 32, 255);

				dsDrawTexImage(RaceTextBoxImage[0], RESOLUTION_WIDTH / 2 + 12, RESOLUTION_HEIGHT / 5 + 150, 256, 256, 255);
				dsDrawTexImage(RaceTextBoxImage[1], RESOLUTION_WIDTH / 2 + 12 + 256, RESOLUTION_HEIGHT / 5 + 150, 32, 256, 255);
				dsDrawTexImage(MoryonTextImage, RESOLUTION_WIDTH / 2 + 12 + 19, RESOLUTION_HEIGHT / 5 + 150 + 12, 256, 256, 255);

				if (MouseButton[0])
				{
					tribeNum = TRIBE_Moryon;

					JobCharacter[0].Close();
					JobCharacter[1].Close();
					JobCharacter[2].Close();
					JobCharacter[3].Close();
					JobCharacter[4].Close();

					PlayWav2(5 - 1);
					SelectNextState = JOB_SELECT_STATE;
					RaceMarkScaleSize = 128;

					JobCharacterCount = 0;

					JobCharacter[JobCharacterCount].sCharacterData.iClass = CHARACTERCLASS_Knight;
					AddJobCharacter(szMorMechBodyName, szMorMechFaceName[0]);

					JobCharacter[JobCharacterCount].sCharacterData.iClass = CHARACTERCLASS_Atalanta;
					AddJobCharacter(szMorFighterBodyName, szMorFighterFaceName[0]);

					JobCharacter[JobCharacterCount].sCharacterData.iClass = CHARACTERCLASS_Priestess;
					AddJobCharacter(szMorPikeBodyName, szMorPikeFaceName[0]);

					JobCharacter[JobCharacterCount].sCharacterData.iClass = CHARACTERCLASS_Magician;
					AddJobCharacter(szMorArcherBodyName, szMorArcherFaceName[0]);

					JobCharacter[JobCharacterCount].sCharacterData.iClass = CHARACTERCLASS_Shaman;
					AddJobCharacter(szMorAssaBodyName, szMorAssaFaceName[0]);
					ReadTextures();
				}
			}
			else
			{
				dsDrawTexImage(MoryonMarkImage, RESOLUTION_WIDTH / 2 + 12, RESOLUTION_HEIGHT / 5, 128, 128, RaceMarkBlendCount);
				dsDrawTexImage(MoryonLogoImage, RESOLUTION_WIDTH / 2 + 12 - 6, RESOLUTION_HEIGHT / 5 + 118, 128, 32, RaceMarkBlendCount);
			}
		}
		else if (SelectCurrentState == JOB_SELECT_STATE)
		{
			OkButton.Draw(threeButtonStartPos, RESOLUTION_HEIGHT - 40);
			BackButton.Draw(threeButtonStartPos + 100, RESOLUTION_HEIGHT - 40);
			QuitButton.Draw(threeButtonStartPos + 200, RESOLUTION_HEIGHT - 40);

			RECT rect;
			POINT sPos;
			smRender.SetCameraPosi(x, y, z, anx, any, 0);

			for (int index = 0; index < JobCharacterCount; index++)
			{
				smRender.GetRect2D(JobCharacter[index].pX, JobCharacter[index].pY + (32 * fONE), JobCharacter[index].pZ, 32 * fONE, 32 * fONE, &rect, &sPos);

				switch (tribeNum)
				{
				case TRIBE_Tempscron:
					if (MouseMoveCharacterNum == index || MouseDownCharacterNum == index)
					{
						dsDrawTexImage(TempscronJobImage[index][1], rect.left - 10, rect.top - 15, 128, 32, 255);

						if (MouseDownCharacterNum != index)
						{
							dsDrawTexImage(JobTextBoxImage[0], RESOLUTION_WIDTH / 2 - 140, RESOLUTION_HEIGHT / 5, 256, 256, 255);
							dsDrawTexImage(JobTextBoxImage[1], RESOLUTION_WIDTH / 2 - 140 + 256, RESOLUTION_HEIGHT / 5, 32, 256, 255);
							dsDrawTexImage(TempscronJobTextImage[index], (int)RESOLUTION_WIDTH / 2 - 140 + 10, RESOLUTION_HEIGHT / 5 + 4, 256, 256, 255);
						}
					}
					else
						dsDrawTexImage(TempscronJobImage[index][0], rect.left - 10, rect.top - 15, 128, 32, 255);
					break;
				case TRIBE_Moryon:
					if (MouseMoveCharacterNum == index || MouseDownCharacterNum == index)
					{
						dsDrawTexImage(MoryonJobImage[index][1], rect.left - 10, rect.top - 15, 128, 32, 255);

						if (MouseDownCharacterNum != index)
						{
							dsDrawTexImage(JobTextBoxImage[0], RESOLUTION_WIDTH / 2 - 140, RESOLUTION_HEIGHT / 5, 256, 256, 255);
							dsDrawTexImage(JobTextBoxImage[1], RESOLUTION_WIDTH / 2 - 140 + 256, RESOLUTION_HEIGHT / 5, 32, 256, 255);
							dsDrawTexImage(MoryonJobTextImage[index], RESOLUTION_WIDTH / 2 - 140 + 10, RESOLUTION_HEIGHT / 5 + 4, 256, 256, 255);
						}
					}
					else
						dsDrawTexImage(MoryonJobImage[index][0], rect.left - 10, rect.top - 15, 128, 32, 255);
					break;

				}
			}
		}
		else if (SelectCurrentState == FACE_SELECT_STATE)
		{
			OkButton.Draw(threeButtonStartPos, RESOLUTION_HEIGHT - 40);
			BackButton.Draw(threeButtonStartPos + 100, RESOLUTION_HEIGHT - 40);
			QuitButton.Draw(threeButtonStartPos + 200, RESOLUTION_HEIGHT - 40);

			dsDrawTexImage(BlackBoxImage, 150, 410, 500, 128 + 10, 20);
		}

	}

	if ((SelectCurrentState == RACE_SELECT_STATE) && (SelectNextState == JOB_SELECT_STATE))
	{
		if (tribeNum == TRIBE_Tempscron)
			dsDrawTexImage(TempscronMarkImage, (int)RESOLUTION_WIDTH / 2 - RaceMarkScaleSize / 2, RESOLUTION_HEIGHT / 3 - RaceMarkScaleSize / 2 - 40, RaceMarkScaleSize, RaceMarkScaleSize, RaceMarkScaleSize);

		if (tribeNum == TRIBE_Moryon)
			dsDrawTexImage(MoryonMarkImage, (int)RESOLUTION_WIDTH / 2 - RaceMarkScaleSize / 2, RESOLUTION_HEIGHT / 3 - RaceMarkScaleSize / 2 - 40, RaceMarkScaleSize, RaceMarkScaleSize, RaceMarkScaleSize);

	}

	IncTextureFrame();

	if (SelectCurrentState == SelectNextState && FadeCurrentState == FadeNextState)
	{
		if (SelectCurrentState == CHARACTER_SELECT_STATE)
		{
			if (MouseMoveCharacterNum != -1)
				DrawCharacterInfo();

			if (SelectSubState == SUB_SELECT_CHARACTER_MANAGE)
				MessageBox.Draw(RESOLUTION_WIDTH / 2 - 128, RESOLUTION_HEIGHT / 2 + RESOLUTION_HEIGHT / 6, " Do you wish to delete? ", D3DCOLOR_XRGB(255, 0, 0));

			if (SelectSubState == SUB_SELECT_CHARACTER_USER)
				MessageBox.Draw(RESOLUTION_WIDTH / 2 - 128, RESOLUTION_HEIGHT / 2 + RESOLUTION_HEIGHT / 6, " Continue this Tale? ");
			if (ErrorSelect == ERROR_MAX_NEWPLAYER)
				Message.Draw(RESOLUTION_WIDTH / 2 - 128, RESOLUTION_HEIGHT / 2 + RESOLUTION_HEIGHT / 6, " Character limit exceeded. ");
		}
		else if (SelectCurrentState == FACE_SELECT_STATE)
		{
			if (FaceSelectFirstFlag == FALSE && JobFaceSelectNum != -1)
			{
				FaceSelectFirstFlag = TRUE;
				switch (tribeNum)
				{
				case TRIBE_Tempscron:
					switch (JobBodySelectNum)
					{
					case 0:
						// 机械
						SetChangeJobFace(szTempMechBodyName, szTempMechFaceName[JobFaceSelectNum], JobBodySelectNum);
						break;
					case 1:
						// 武士
						SetChangeJobFace(szTempFighterBodyName, szTempFighterFaceName[JobFaceSelectNum], JobBodySelectNum);
						break;
					case 2:
						// 枪兵
						SetChangeJobFace(szTempPikeBodyName, szTempPikeFaceName[JobFaceSelectNum], JobBodySelectNum);
						break;
					case 3:
						// 弓手
						SetChangeJobFace(szTempArcherBodyName, szTempArcherFaceName[JobFaceSelectNum], JobBodySelectNum);
						break;
					case 4:
						// 刺客
						SetChangeJobFace(szTempAssaBodyName, szTempAssaFaceName[JobFaceSelectNum], JobBodySelectNum);
						break;
					}
					break;
				case TRIBE_Moryon:
					switch (JobBodySelectNum)
					{
					case 0:
						// 游侠
						SetChangeJobFace(szMorMechBodyName, szMorMechFaceName[JobFaceSelectNum], JobBodySelectNum);
						break;
					case 1:
						// 魔枪
						SetChangeJobFace(szMorFighterBodyName, szMorFighterFaceName[JobFaceSelectNum], JobBodySelectNum);
						break;
					case 2:
						// 祭司
						SetChangeJobFace(szMorPikeBodyName, szMorPikeFaceName[JobFaceSelectNum], JobBodySelectNum);
						break;
					case 3:
						// 法师
						SetChangeJobFace(szMorArcherBodyName, szMorArcherFaceName[JobFaceSelectNum], JobBodySelectNum);
						break;
					case 4:
						// 萨满
						SetChangeJobFace(szMorAssaBodyName, szMorAssaFaceName[JobFaceSelectNum], JobBodySelectNum);
						break;
					}
					break;
				}
				JobCharacter[JobBodySelectNum].bActive = TRUE;
				OpenEachPlayer(&JobCharacter[JobBodySelectNum]);
			}
			int addX = (int)RESOLUTION_WIDTH / 2 - 800 / 2;


			int newPosX = int(((float)RESOLUTION_WIDTH * 272.f) / 800.f);
			int newPosY = int(((float)RESOLUTION_HEIGHT * 82.f) / 600.f);
			if (RESOLUTION_WIDTH == 1280 && RESOLUTION_HEIGHT == 1024)
				newPosY = int((float)RESOLUTION_HEIGHT * (100.f / 600.f));
			int newWidth = int(((float)RESOLUTION_WIDTH * 256.f) / 800.f);
			int newHeight = int(((float)RESOLUTION_HEIGHT * 128.f) / 600.f);


			int addY = RESOLUTION_HEIGHT / 2 - 600 / 2;

			dsDrawTexImage(FaceBoxBigImage[0], newPosX, newPosY, newWidth, newWidth, 255);
			dsDrawTexImage(FaceBoxBigImage[1], newPosX, newPosY + newWidth, newWidth, newHeight, 255);

			DrawEachPlayer(0.5f, 0.4f, 1);

			int    mouseMoveFace = -1;
			bool   selectFaceFlag = false;

			if (JobBodySelectNum >= 0)
			{
				for (int index = 0; index < TempFaceCount[JobBodySelectNum]; index++)
				{
					if (pCursorPos.x > (TempFacePos[JobBodySelectNum][index] + addX) && pCursorPos.x < (TempFacePos[JobBodySelectNum][index] + 128 + addX) && pCursorPos.y >(RESOLUTION_HEIGHT - (70 + 128)) && pCursorPos.y < (RESOLUTION_HEIGHT - (70 + 128) + 128) && ErrorSelect == ERROR_NONE && SelectSubState == SUB_SELECT_NONE)
					{
						mouseMoveFace = index;

						if (MouseButton[0])
						{
							selectFaceFlag = true;
							if (JobFaceSelectNum != index)
							{
								switch (tribeNum)
								{
								case TRIBE_Tempscron:
									switch (JobBodySelectNum)
									{
									case 0:
										// 机械
										SetChangeJobFace(szTempMechBodyName, szTempMechFaceName[index], JobBodySelectNum);
										break;
									case 1:
										// 武士
										SetChangeJobFace(szTempFighterBodyName, szTempFighterFaceName[index], JobBodySelectNum);
										break;
									case 2:
										// 枪兵
										SetChangeJobFace(szTempPikeBodyName, szTempPikeFaceName[index], JobBodySelectNum);
										break;
									case 3:
										// 弓手
										SetChangeJobFace(szTempArcherBodyName, szTempArcherFaceName[index], JobBodySelectNum);
										break;
									case 4:
										// 刺客
										SetChangeJobFace(szTempAssaBodyName, szTempAssaFaceName[index], JobBodySelectNum);
										break;
									}
									break;
								case TRIBE_Moryon:
									switch (JobBodySelectNum)
									{
									case 0:
										// 游侠
										SetChangeJobFace(szMorMechBodyName, szMorMechFaceName[index], JobBodySelectNum);
										break;
									case 1:
										// 魔枪
										SetChangeJobFace(szMorFighterBodyName, szMorFighterFaceName[index], JobBodySelectNum);
										break;
									case 2:
										// 祭司
										SetChangeJobFace(szMorPikeBodyName, szMorPikeFaceName[index], JobBodySelectNum);
										break;
									case 3:
										// 法师
										SetChangeJobFace(szMorArcherBodyName, szMorArcherFaceName[index], JobBodySelectNum);
										break;
									case 4:
										// 萨满
										SetChangeJobFace(szMorAssaBodyName, szMorAssaFaceName[index], JobBodySelectNum);
										break;
									}
									break;
								}

								JobFaceSelectNum = index;

								JobCharacter[JobBodySelectNum].bActive = TRUE;
								OpenEachPlayer(&JobCharacter[JobBodySelectNum]);
							}
							if (JobBodySelectNum != -1)
							{
								if (SelectSubState == SUB_SELECT_NONE)
								{
									hFocusWnd = hTextWnd;
									FocusWndFlag = TRUE;
								}
							}
						}
					}
					if (JobFaceSelectNum == index)
					{
						dsDrawTexImage(FaceBoxSmallImage[1], TempFacePos[JobBodySelectNum][JobFaceSelectNum] + addX, RESOLUTION_HEIGHT - (50 + 128), 128, 128, 255);

						switch (tribeNum)
						{
						case TRIBE_Tempscron:
							dsDrawTexImage(TempFaceImage[JobBodySelectNum][JobFaceSelectNum][1], TempFacePos[JobBodySelectNum][JobFaceSelectNum] + addX, RESOLUTION_HEIGHT - (50 + 128) + 4, 128, 128, 255);
							break;
						case TRIBE_Moryon:
							dsDrawTexImage(MorFaceImage[JobBodySelectNum][JobFaceSelectNum][1], TempFacePos[JobBodySelectNum][JobFaceSelectNum] + addX, RESOLUTION_HEIGHT - (50 + 128), 128, 128, 255);
							break;
						}
					}
					else
					{
						if (mouseMoveFace != -1 && mouseMoveFace == index)
						{
							dsDrawTexImage(FaceBoxSmallImage[1], TempFacePos[JobBodySelectNum][index] + addX, RESOLUTION_HEIGHT - (50 + 128), 128, 128, 180);

							switch (tribeNum)
							{
							case TRIBE_Tempscron:
								dsDrawTexImage(TempFaceImage[JobBodySelectNum][index][0], TempFacePos[JobBodySelectNum][index] + addX, RESOLUTION_HEIGHT - (50 + 128) + 4, 128, 128, 200);
								break;
							case TRIBE_Moryon:
								dsDrawTexImage(MorFaceImage[JobBodySelectNum][index][0], TempFacePos[JobBodySelectNum][index] + addX, RESOLUTION_HEIGHT - (50 + 128), 128, 128, 200);
								break;
							}
						}
						else
						{
							dsDrawTexImage(FaceBoxSmallImage[0], TempFacePos[JobBodySelectNum][index] + addX, RESOLUTION_HEIGHT - (50 + 128), 128, 128, 255);

							switch (tribeNum)
							{
							case TRIBE_Tempscron:
								dsDrawTexImage(TempFaceImage[JobBodySelectNum][index][0], TempFacePos[JobBodySelectNum][index] + addX, RESOLUTION_HEIGHT - (50 + 128) + 4, 128, 128, 150);
								break;
							case TRIBE_Moryon:
								dsDrawTexImage(MorFaceImage[JobBodySelectNum][index][0], TempFacePos[JobBodySelectNum][index] + addX, RESOLUTION_HEIGHT - (50 + 128), 128, 128, 150);
								break;
							}
						}
					}
				}

				dsDrawTexImage(FaceBoxSmallImage[2], 305 + addX, RESOLUTION_HEIGHT - (66), 64, 16, 255);
				dsDrawTexImage(FaceBoxSmallImage[2], 305 + 128 + addX, RESOLUTION_HEIGHT - (66), 64, 16, 255);
			}


			if (selectFaceFlag == false && MouseButton[0] && SelectSubState == SUB_SELECT_NONE && pCursorPos.x > 0 && pCursorPos.x < 800 && pCursorPos.y > 0 && pCursorPos.y < 546)
				JobFaceSelectNum = -1;

			if (JobBodySelectNum != -1 && JobFaceSelectNum != -1 && SelectSubState == SUB_SELECT_NONE && ErrorSelect == ERROR_NONE)
			{
				if (MouseDblClick || (hFocusWnd == NULL && FocusWndFlag))
				{
					FocusWndFlag = FALSE;
					hFocusWnd = NULL;

					if (lstrlen(UserCharacterNewName) > 0)
					{
						if (lstrlen(UserCharacterNewName) >= 4 && lstrlen(UserCharacterNewName) <= 18)
						{
							MessageBox.Flag = TRUE;
							SelectSubState = SUB_SELECT_CHARACTER_NEW;
						}
						else
						{
							MouseDblClick = FALSE;
							MouseButton[0] = FALSE;
							ErrorSelect = ERROR_NAME_LENGTH;
						}
					}
					else
					{
						MouseDblClick = FALSE;
						MouseButton[0] = FALSE;
						ErrorSelect = ERROR_NONAME_NEWPLAYER;
					}
				}
			}

			int newTexPosX = int(((float)RESOLUTION_WIDTH * 358.f) / 800.f);
			int newTexPosY = int(((float)RESOLUTION_HEIGHT * 398.f) / 600.f);

			if (hFocusWnd != NULL && JobFaceSelectNum != -1 && hTextWnd != NULL)
			{
				GetWindowText(hFocusWnd, UserCharacterNewName, sizeof(UserCharacterNewName));

				KeyFilter(UserCharacterNewName);

				if (CaretCounta < 16)
				{
					int len = GetTextWidth(0,(char *)UserCharacterNewName);

					dsTextLineOut(0, newTexPosX + len + 1, newTexPosY, "|", 1, -1);
				}

				CaretCounta++;

				if (CaretCounta > 32)
					CaretCounta = 0;

				dsTextLineOut(1, newTexPosX - 40, newTexPosY, "Name", STRLEN("Name"), D3DCOLOR_RGBA(210, 210, 180, 255));
			}

			dsTextLineOut(0, newTexPosX, newTexPosY, UserCharacterNewName, lstrlen(UserCharacterNewName), D3DCOLOR_XRGB(255, 255, 255));

			KeyFilter(UserCharacterNewName);

			if ((GetKeyState(VK_CONTROL) < 0))
			{
				if ((GetKeyState(118) < 0) || (GetKeyState(86) < 0))
				{
					for (int i = 0; i <= 255; i++)
					{
						UserCharacterNewName[i] = 0;
						SetWindowText(hFocusWnd, 0);
						SetWindowText(hFocusWnd, UserCharacterNewName);
					}
				}
			}
			if (GetKeyState(VK_SHIFT) < 0)
			{
				if (GetKeyState(VK_INSERT) < 0)
				{
					for (int i = 0; i <= 255; i++)
					{
						UserCharacterNewName[i] = 0;
						SetWindowText(hFocusWnd, 0);
						SetWindowText(hFocusWnd, UserCharacterNewName);
					}
				}
			}
		}
	}
	if (SelectSubState == SUB_SELECT_CHARACTER_NEW)
		MessageBox.Draw(RESOLUTION_WIDTH / 2 - 150, RESOLUTION_HEIGHT / 2 + RESOLUTION_HEIGHT / 6, " Creation complete. Confirm? ");

	switch (ErrorSelect)
	{
	case ERROR_NONAME_NEWPLAYER:
		Message.Draw(RESOLUTION_WIDTH / 2 - 100, RESOLUTION_HEIGHT / 2 + RESOLUTION_HEIGHT / 6, " Enter character's name ");
		break;
	case ERROR_EXHIST_NEWPLAYER:
		Message.Draw(RESOLUTION_WIDTH / 2 - 128, RESOLUTION_HEIGHT / 2 + RESOLUTION_HEIGHT / 6, " Name already exsists ");
		break;
	case ERROR_SELECT_CHAR:
		Message.Draw(RESOLUTION_WIDTH / 2 - 100, RESOLUTION_HEIGHT / 2 + RESOLUTION_HEIGHT / 6, "  Select a character   ");
		break;
	case ERROR_SELECT_RACE:
		Message.Draw(RESOLUTION_WIDTH / 2 - 100, RESOLUTION_HEIGHT / 2 + RESOLUTION_HEIGHT / 6, "    Select a Tribe     ");
		break;
	case ERROR_SELECT_JOB:
		Message.Draw(RESOLUTION_WIDTH / 2 - 100, RESOLUTION_HEIGHT / 2 + RESOLUTION_HEIGHT / 6, "    Select a Class     ");
		break;
	case ERROR_SELECT_FACE:
		Message.Draw(RESOLUTION_WIDTH / 2 - 100, RESOLUTION_HEIGHT / 2 + RESOLUTION_HEIGHT / 6, "     Select a face     ");
		break;
	case ERROR_DELETE_CLAN_MEMBER:
		Message.Draw(RESOLUTION_WIDTH / 2 - 128, RESOLUTION_HEIGHT / 2 + RESOLUTION_HEIGHT / 6, "Unable to delete clan master");
		break;
	case ERROR_CLAN_SERVER_NONE:
		Message.Draw(RESOLUTION_WIDTH / 2 - 128, RESOLUTION_HEIGHT / 2 + RESOLUTION_HEIGHT / 6, "Unable to delete clan master");
		break;
	case ERROR_NAME_LENGTH:
		Message.Draw(RESOLUTION_WIDTH / 2 - 100, RESOLUTION_HEIGHT / 2 + RESOLUTION_HEIGHT / 6, " Please enter 4 - 18 char ");
		break;
	}

	if (MessageBox.Flag)
		dsDrawTexImage(BlackBoxImage, 0, RESOLUTION_HEIGHT - 47, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 120);

	if (SelectCurrentState == COMPLETE_SELECT_STATE || SelectCurrentState == START_GAME_STATE)
		DrawMap(MapBlendCount);
	DrawFade();

	return TRUE;
}

int HoLogin::DrawFade()
{
	if (FadeCurrentState == FADE_IN && FadeNextState == FADE_IN)
		return FALSE;

	bool fastBlendFlag = false;

	for (int index = 0; index < 256; index++)
	{
		if (VRKeyBuff[index] == TRUE)
		{
			fastBlendFlag = true;
			break;
		}
	}
	if (MouseButton[0])
	{
		fastBlendFlag = true;
		MouseButton[0] = FALSE;
	}
	if (fastBlendFlag)
	{
		if (FadeNextState == FADE_IN)
		{
			BlendValue = 0;
			FadeCurrentState = FADE_IN;
			LoginVolume = GetVolumeBGM(SETTINGHANDLE->Get().iMusicVolume);
		}
		else if (FadeNextState == FADE_OUT)
		{
			BlendValue = 255;
			FadeCurrentState = FADE_OUT;
			LoginVolume = 0;
		}
	}
	if (SelectCurrentState != COMPLETE_SELECT_STATE && SelectCurrentState != START_GAME_STATE)
	{
		SetVolumeBGM(LoginVolume);
		PlayWav_VolChange(9 - 1, LoginVolume);
		PlayWav_VolChange(10 - 1, LoginVolume + 50);
		PlayWav_VolChange(11 - 1, LoginVolume + 50);
	}

	if (BlendValue > 0 && BlendValue <= 255)
		dsDrawTexImage(BlackBoxImage, 0, 0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, BlendValue);

	return TRUE;
}

int HoLogin::MainFade()
{
	if (FadeCurrentState != FadeNextState)
	{
		if (FadeNextState == FADE_IN)
			MainFadeIn();
		else
			MainFadeOut();
	}

	return TRUE;
}

int HoLogin::MainFadeIn()
{
	if (BlendValue > 0)
	{
		BlendValue -= 6;
		if (SelectCurrentState != COMPLETE_SELECT_STATE && SelectCurrentState != START_GAME_STATE)
		{
			LoginVolume += 10;

			int v = GetVolumeBGM(SETTINGHANDLE->Get().iMusicVolume);

			if (LoginVolume > v)
				LoginVolume = v;
		}
	}

	if (BlendValue <= 0)
	{
		BlendValue = 0;
		FadeCurrentState = FADE_IN;
		FadeNextState = FADE_IN;
	}
	return TRUE;
}

int HoLogin::MainFadeOut()
{
	if (BlendValue < 255)
	{
		BlendValue += 8;

		if (SelectCurrentState != COMPLETE_SELECT_STATE && SelectCurrentState != START_GAME_STATE)
		{
			LoginVolume -= 10;
			if (LoginVolume < 0)
				LoginVolume = 0;
		}
	}

	if (BlendValue >= 255)
	{
		BlendValue = 255;
		LoginVolume = 0;
		FadeCurrentState = FADE_OUT;
		FadeNextState = FADE_OUT;
	}
	return TRUE;
}

void HoLogin::SetFade()
{
	if (FadeCurrentState == FADE_OUT)
	{
		FadeNextState = FADE_IN;
		BlendValue = 255;
		LoginVolume = 0;
	}
	else
	{
		FadeNextState = FADE_OUT;
		BlendValue = 0;
		LoginVolume = GetVolumeBGM(SETTINGHANDLE->Get().iMusicVolume);
	}
}

int HoLogin::ReLoad()
{
	if (GameMapImage[0])
	{
		DELET(GameMapImage[0]);
		GameMapImage[0] = LoadDibSurfaceOffscreen("StartImage\\Login\\Map.bmp");
	}
	return TRUE;
}
int GetSelRectChar(Unit *lpChar)
{
	RECT rect;
	POINT	sPos;
	int sez;
	int SelZ = 65536 * 16384;

	if (lpChar)
	{
		sez = smRender.GetRect2D(lpChar->pX, lpChar->pY + (32 * fONE), lpChar->pZ, 24 * fONE, 32 * fONE, &rect, &sPos);

		if (sez > 0 && sez < SelZ && rect.left<pCursorPos.x && rect.right>pCursorPos.x && rect.top<pCursorPos.y && rect.bottom>pCursorPos.y)
		{
			if (MouseButton[0])
				return 2;
			return 1;
		}
	}

	return FALSE;
}


int GetSelRectJobChar(Unit *lpChar)
{
	RECT rect;
	POINT	sPos;
	int sez;
	int SelZ = 65536 * 16384;

	if (lpChar)
	{
		sez = smRender.GetRect2D(lpChar->pX, lpChar->pY + (32 * fONE), lpChar->pZ, 24 * fONE, 32 * fONE, &rect, &sPos);

		if (sez > 0 && sez < SelZ && rect.left<pCursorPos.x && rect.right>pCursorPos.x &&rect.top<pCursorPos.y && rect.bottom>pCursorPos.y)
		{
			if (MouseButton[0])
				return 2;

			return 1;
		}
	}
	return FALSE;
}