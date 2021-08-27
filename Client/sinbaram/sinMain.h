/*----------------------------------------------------------------------------*
*	���ϸ� :  sinMain.h
*	�ϴ��� :  �Źٶ� ���� 
*	�ۼ��� :  ����������Ʈ 12��
*	������ :  �ڻ� 
*-----------------------------------------------------------------------------*/	

#define		 SINLBUTTONDOWN			10
#define		 SINLBUTTONUP 			11
#define		 SINRBUTTONDOWN			110
#define		 SINRBUTTONUP 			111

#define		 SINMOUSEMOVE			2
#define		 SINKEYDOWN				3

#define      SIN_CHAR_FIGHTER		1
#define      SIN_CHAR_MECANICIAN	2
#define      SIN_CHAR_ARCHER		3
#define      SIN_CHAR_PIKEMAN		4
#define		 SIN_CHAR_KNIGHT		6
#define		 SIN_CHAR_ATALANTA		5
#define		 SIN_CHAR_PRIESTESS		8
#define		 SIN_CHAR_MAGICIAN		7

/*----------------------------------------------------------------------------*
*							�Լ� 

*-----------------------------------------------------------------------------*/	

void sinInit();

void sinMain();

void sinDraw();

void sinDrawText();


void sinClose();

void sinProc(int Message);

int GetSinTime(DWORD dwTime,smTIME *smTime);
int GetSinTime2(DWORD dwTime ,smTIME *smTime);


/*----------------------------------------------------------------------------*
*							   class 
*-----------------------------------------------------------------------------*/	
class cSINBARAM_UI{ //Ŭ������ �⺻�� �ȴ�

public:
	int OpenFlag;       //������ �� �����ϱ� ������ ��ġ�� ����� �ٲ�� �ȵȴ� 

public:
	cSINBARAM_UI();
	~cSINBARAM_UI();

	void Init(); //Ŭ���� �ʱ�ȭ
	void Load();
	void Release();
	void Draw();
	void Close();//Ŭ���� ���� 
	void Main();
	void LButtonDown(int x , int y);
	void LButtonUp(int x , int y);
	void RButtonDown(int x , int y);
	void RButtonUp(int x, int y);
	void KeyDown(); //Ű üũ 
};
/*----------------------------------------------------------------------------*
*							extern ���� 
*-----------------------------------------------------------------------------*/	
extern int	 quit;
extern int	 MouseButton[3];	//���콺 �迭 
extern BYTE  VRKeyBuff[256];    //Ű�Է� ����  
extern POINT pCursorPos;		//���콺 ��ǥ 	

extern HWND  hFocusWnd; //ä�� ��Ŀ�� 

extern HWND hwnd;

extern CharacterData *sinChar;		//ĳ���� ���� ����ü 
extern CharacterData sinCharDisplay; //ĳ���� ���� ����ü (��ŷ������ ���)
extern int sinbaram_Stop;