
#define CHARACTER_USER_MAX			5	//建立人物最大的人数上限
#define CHARACTER_JOB_MAX			5	//职业的上限


#define CHARACTER_SELECT_STATE		0
#define RACE_SELECT_STATE			1
#define JOB_SELECT_STATE			2
#define FACE_SELECT_STATE			3
#define NAME_SELECT_STATE			4
#define COMPLETE_SELECT_STATE		5
#define START_GAME_STATE			6
#define RETURN_OPENING_STATE        7


#define TEMPSCRON					0


#define TRIBE_Tempscron 0 //坦普族
#define TRIBE_Moryon	1 //魔灵族

struct HoNewCharInfo
{
	int	  JobCode;			//职业代码
	int   Strength;			//力量
	int   Spirit;			//精神
	int   Talent;			//才能
	int   Dexterity;		//敏捷
	int   Health;			//体质


};

#define		ERROR_NONAME_NEWPLAYER		10
#define		ERROR_MAX_NEWPLAYER			20
#define		ERROR_EXHIST_NEWPLAYER		30
#define		ERROR_SELECT_CHAR			40
#define		ERROR_SELECT_RACE			50
#define		ERROR_SELECT_JOB			60
#define		ERROR_SELECT_FACE			80
#define     ERROR_DELETE_CLAN_MEMBER    90 
#define     ERROR_CLAN_SERVER_NONE     100
#define		ERROR_NAME_LENGTH		   110

#define     SUB_SELECT_NONE					0
#define		SUB_SELECT_CHARACTER_MANAGE		1
#define		SUB_SELECT_CHARACTER_USER		2
#define		SUB_SELECT_CHARACTER_NEW		3
#define		SUB_SELECT_CHARACTER_NEW_SERVER	4
#define		SUB_SELECT_BACK					5

class HoLogin
{
public:
	int						tribeNum;

	BOOL					ClanMarkUpdateSuccessFlag;

	int						MainBoxFrameImage1[4];
	int						MainBoxFrameImage2[4];
	int						TitleBoxFrameImage;
	int						TitleNameImage;

	int						TempscronMarkImage;
	int						TempscronLogoImage;

	int						MoryonMarkImage;
	int						MoryonLogoImage;

	int						TempscronTextImage;
	int						MoryonTextImage;

	int						RaceTextBoxImage[2];
	int						JobTextBoxImage[2];

	int						TempscronJobImage[CHARACTER_JOB_MAX][2];
	int						MoryonJobImage[CHARACTER_JOB_MAX][2];
	int						TempscronJobTextImage[CHARACTER_JOB_MAX];
	int						MoryonJobTextImage[CHARACTER_JOB_MAX];


	int						FaceBoxBigImage[2];
	int						FaceBoxSmallImage[3];

	BOOL					FaceSelectFirstFlag;

	int						ErrorDelayCount;
	BOOL					StartErrorDelayFlag;

private:
	smSTAGE3D				*Stage;
	POINT3D					CaAngle;
	POINT3D					TarPosi;
	int						TarDist;

	BOOL					CharacterStopFlag;
	BOOL					CharacterReturnFlag;

	int						SelectCurrentState;
	int						SelectNextState;

	int						SelectSubState;
	BOOL					FocusWndFlag; 

	int						ErrorSelect;

	HoButton				OkButton;
	HoButton				BackButton;
	HoButton				QuitButton;
	HoButton				DeleteButton;
	HoButton				NewCharButton;

	Unit					UserCharacter[CHARACTER_USER_MAX];
	int						UserCharacterCount;

	Unit					JobCharacter[CHARACTER_JOB_MAX];
	int						JobCharacterCount;

	int						NewCharacterImage;
	float					NewCharacterImageBlendCount;
	bool					NewCharacterImageBlendFlag;

	int						UserCharacterInfoImage;
	int						UserCharacterInfoBackImage;					

	int						TempFaceImage[CHARACTER_JOB_MAX][3][2];
	int						MorFaceImage[CHARACTER_JOB_MAX][3][2];

	int						MouseDownCharacterNum;
	int						MouseMoveCharacterNum;

	int						JobBodySelectNum;
	int						JobFaceSelectNum;
	char					UserCharacterNewName[256];

	smTEXTUREHANDLE *GameMapImage[2];
	int						MapBlendCount;
	BOOL					MapBlendFlag;

	HoMessage				Message;
	HoMessageBox			MessageBox;

	int						BlackBoxImage;

	int						RaceMarkBlendCount;

	int						RaceMarkScaleSize;

	int						LoginVolume;						
public:
	int		Load();
	int		Init();
	int		Close();
	int		Main();
	int		Draw();
	int		DrawTitle(int state);

	int		SetChangeJobFace(char *charFile1, char *chrFile2, int jobIndex);

	int		InitUserCharacter();
	int		DrawUserCharacter(int x, int y, int z, int ax, int ay, int az);
	int		DrawJobCharacter(int x, int y, int z, int ax, int ay, int az);
	int		DrawGameFrame();
	int		DrawLight();

	int		DrawMap(int alpha);
	int		DrawCharacterInfo();
	int		MainDefaultButton();

	void KeyFilter(char *pszValue);

	BOOL	FadeCurrentState;
	BOOL	FadeNextState;

	int		BlendValue;
	int		DrawFade();
	int		MainFade();
	int		MainFadeIn();
	int		MainFadeOut();
	void	SetFade();
	int		ReLoad();

	HoLogin();
	~HoLogin();
private:
	int		DrawSelectSubState();
	int		CameraUpDown();
	int		AddUserCharacter(char *chrFile1, char *chrFile2, int jobCode = 0);
	int		AddJobCharacter(char *chrFile1, char *chrFile2, int index = -1);
	int		GetSelectCharacter(Unit *lpChar );
	void	LoadLoadingImage(int level);

};

#define MAX_LOADING_IMAGE	29