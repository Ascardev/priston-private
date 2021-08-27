/*----------------------------------------------------------------------------*
*	���ϸ� :  sinInterFace.h	
*	�ϴ��� :  �������̽��� ���� ���� �����Ѵ� 
*	�ۼ��� :  ����������Ʈ 12��
*	������ :  �ڻ� 
*-----------------------------------------------------------------------------*/	

//////////����� ��ȯ 
#define		RESTART_FEILD		1
#define		RESTART_TOWN		2
#define		RESTART_EXIT		3

/////////��ų ���� �������̽� ǥ��
#define     HA_DEFANCE			1
#define     HA_BLOCK			2
#define     HA_EVASION			3

/*----------------------------------------------------------------------------*
*						(�������̽�  )class
*-----------------------------------------------------------------------------*/	
struct sRUNCAMERAMAP{ //��ư ��� �÷� 

	int RunFlag;			 //�ȱ� �޸��� �÷� 
	int CameraAutoFlag;		 //ī�޶� �ڵ� �÷� 
	int MapOnFlag;			 //�ʺ��� �÷� 

	//�̰��� �������̽����� �Ͼ�� ��� �̺�Ʈ ��ư�� �߰���ų ���� 

};

////// ������ ���� ���׹̳� �ܻ�ȿ�� 
struct sSHADOWSTATE{
	int Flag;
	int Time;
	POINT Posi;
	POINT Size;
	DWORD Color;

};


class cINTERFACE
{
public:

	sRUNCAMERAMAP	sInterFlags;

	int MatMain;					    //��� �������̽� 
	int MatMenu[2];						//�޴�  
	int MatExitMenu;					//������ �޴� 
	int MatComPass;						//��ħ�� ���� 	

	int MatLife;						//������   �ܻ�ȿ��
	int MatMana;						//����     �ܻ�ȿ��
	int MatStamina;						//���׹̳� �ܻ�ȿ��

	smTEXTUREHANDLE *lpEXP;      //����ġ  
	smTEXTUREHANDLE *lpMP;		//����  	
	smTEXTUREHANDLE *lpLIFE;     //������ 
	smTEXTUREHANDLE *lpSTM;      //���׹̳� 
	smTEXTUREHANDLE *lpANGER;    //�г������ 

	smTEXTUREHANDLE *lpLIFESpot;     //������ 
	smTEXTUREHANDLE *lpSTMSpot;      //���׹̳� 
	smTEXTUREHANDLE *lpMANASpot;     //����

	smTEXTUREHANDLE *lpButton[6];//��ư ������ 
	smTEXTUREHANDLE *lpButton2[6];//��ư ������2 

	smTEXTUREHANDLE *lpMenuButton[3];//�޴� ��ư 

	smTEXTUREHANDLE *lpInfoBox[6]; //ǳ�� ���� 
	smTEXTUREHANDLE *lpWalk;		  //�ȱ� 

	smTEXTUREHANDLE *lpRunInfo;    //�ٱ�ǳ�� ���� 
	smTEXTUREHANDLE *lpWalkInfo;   //�ȱ�ǳ�� ���� 

	smTEXTUREHANDLE *lpCameraAutoInfo;   //�ڵ� ī�޶� ǳ�� ���� 
	smTEXTUREHANDLE *lpCameraHandInfo;   //���� ī�޶� ǳ�� ���� 
	smTEXTUREHANDLE *lpCameraFixInfo;   //���� ī�޶� ǳ�� ���� 

	smTEXTUREHANDLE *lpMapOnInfo;   //�ڵ� ī�޶� ǳ�� ���� 
	smTEXTUREHANDLE *lpMapOffInfo;   //���� ī�޶� ǳ�� ���� 

	smTEXTUREHANDLE *lpChatShowButton;	//ūä��â

	smTEXTUREHANDLE *lpSun;	//��
	smTEXTUREHANDLE *lpMoon;	//��

	smTEXTUREHANDLE *lpGage[2]; //0��ü  1������ 

	smTEXTUREHANDLE *lpBar_Anger;
	smTEXTUREHANDLE *lpBar_Time;
	smTEXTUREHANDLE *lpBar_Exp;
	smTEXTUREHANDLE *lpBar_ExpWon;

	smTEXTUREHANDLE *lpButton_Anger;

	smTEXTUREHANDLE *lpMapOnImage;
	smTEXTUREHANDLE *lpCameraImage[2]; //0���� 1 ���� 

	smTEXTUREHANDLE *lpReStartMain; //�ٽý��� 
	smTEXTUREHANDLE *lpReStartButton[3]; //�ٽý��� 

	smTEXTUREHANDLE *lpSelectSkill_Main[2];		//��ų ���� 0 �׷��� 1 Ȱ�� 
	smTEXTUREHANDLE *lpSelectChangeJob[2];   //����        0 �׷��� 2 Ȱ�� 

	smTEXTUREHANDLE *lpGrowInterLeft;
	smTEXTUREHANDLE *lpGrowInterMiddle;
	smTEXTUREHANDLE *lpGrowInterRight;


	int MatClock; //�ð� 
	int DayNightFlag;

public:
	cINTERFACE();
	~cINTERFACE();

	void Init();
	void Load();
	void Release();
	void Close();
	void Draw();
	void Main();
	void LButtonDown(int x , int y);
	void LButtonUp(int x , int y);
	void RButtonDown(int x , int y);
	void RButtonUp(int x, int y);
	void KeyDown(); 

	void InitState();		//����� , ��� , �ٷ� �� �ʱ�ȭ�Ѵ� 
	void CheckingState();	//����� , ��� , �ٷ� �� ��ȭ�� ���� Bmp�� ũ�⸦ ��ȭ ��Ų��
	void ShowParaState();   //����� ��� �ٷ� ����ġ ��ġ�� ǥ���Ѵ� 

	void DrawInterText();   //�������̽��� �� �ؽ�Ʈ�� ǥ���Ѵ� 

	void CheckAllBox(int ButtonFlag); //�ڽ��� �ϳ��� �����ش� 

	int GetWordTimeDisplay();

	void ShowExpPercent(); //����ġ�� �����ش�

	int  SetStringEffect(int); //����Ʈ���ڸ� �����ش� 

};

extern cINTERFACE	cInterFace;

extern POINT InfoMessageBoxPos;  //�ؽ��� ǥ���� ��ǥ 

extern int sinFireShow;           //���� �����ش� 
extern int ExitButtonClick;

extern int ReStartFlag;			  //���� ������ �ٽý��� �������̽��� �����ش� 
extern int ReStartOptionIndex;	  //�ٽý��� ���� �ε��� 	

extern int SkillNpcFlag;			  //���� ��ų ���� �������̽��� �����ش� 
extern int SkillMasterOptionIndex;

extern int RestartCheckExp;		  //�ٽý����Ҽ��ִ� ����ġ�� �ֳ� ���� 


extern int psDrawTexImage2( smTEXTUREHANDLE *hTexHandle , float *x, float *y, float fx, float fy, float fw, float fh, int Transp , int specular);

extern int NotUseSkillEffect[3];

extern int ChangeJobButtonclick;

extern int  ResetQuset3Flag;

extern int ReStartFlag;
extern POINT ReStartMainXY;
extern int ReStartIndex;
extern POINT ReStartTextXY;
extern char szReStartMsg[128];
extern char szReStartMsg2[128];


