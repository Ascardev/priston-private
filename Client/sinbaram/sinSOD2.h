/*----------------------------------------------------------------------------*
*	���ϸ� :  sinSOD2.h
*	�ϴ��� :  ���� Test������ ���̰� �ִ�
*	�ۼ��� :  ����������Ʈ 5�� 
*	������ :  �ڻ� 
*-----------------------------------------------------------------------------*/	

#ifndef _SINSOD2_HEADER_

#define _SINSOD2_HEADER_
#include <vector>
#include <string>
#include <algorithm>

#define SIN_CLANSKILL_ABSORB			1
#define SIN_CLANSKILL_DAMAGE			2
#define SIN_CLANSKILL_EVASION			3

#define SIN_GURAD_CRISTAL_ICE		    1
#define SIN_GURAD_CRISTAL_LIGHTNING		2
#define SIN_GURAD_CRISTAL_FIRE			3

#define SIN_CASTLEITEMSKILL_S_INVU         1    //���� ��ũ��
#define SIN_CASTLEITEMSKILL_S_CRITICAL     2    //ũ��Ƽ�ý�ũ��
#define SIN_CASTLEITEMSKILL_S_EVASION      3    //�߰� ȸ�� ��ũ��
#define SIN_CASTLEITEMSKILL_S_P_LIFE       4    
#define SIN_CASTLEITEMSKILL_S_RES          5    

#define SIN_CASTLEITEMSKILL_R_FIRE_C       6    //���̾� ũ����Ż ���׼�
#define SIN_CASTLEITEMSKILL_R_ICE_C        7    //���̽� ũ����Ż ��Ȳ��
#define SIN_CASTLEITEMSKILL_R_LIGHTING_C   8    //����Ʈ�� ũ����Ż ���׼�
#define SIN_CASTLEITEMSKILL_A_FIGHTER      9    //�������� ���ݷ� ��ȭ��
#define SIN_CASTLEITEMSKILL_A_MECHANICIAN  10   //���ī�ϼ� ���ݷ� ��ȭ��
#define SIN_CASTLEITEMSKILL_A_PIKEMAN      11   //������ũ�ǰ��ݷ� ��ȭ��
#define SIN_CASTLEITEMSKILL_A_ARCHER       12   //����� ���ݷ� ��ȭ��
#define SIN_CASTLEITEMSKILL_A_KNIGHT       13   //�볪��Ʈ ���ݷ� ��ȭ��
#define SIN_CASTLEITEMSKILL_A_ATALANTA     14   //���Ʋ��Ÿ ���ݷ� ��ȭ��
#define SIN_CASTLEITEMSKILL_A_MAGICIAN     15   //������� ���ݷ� ��ȭ��
#define SIN_CASTLEITEMSKILL_A_PRIESTESS    16   //��������Ƽ�� ���ݷ� ��ȭ��
#define SIN_CASTLEITEMSKILL_A_ASSASSIN	   17
#define SIN_CASTLEITEMSKILL_A_SHAMAN       18

/*----------------------------------------------------------------------------*
*							������ Ŭ���޴�
*-----------------------------------------------------------------------------*/	
class cSINSIEGE{
//private:
public:
	int            TaxRate;				    //����
	int            TotalTax;				//���� ���� //�ؿܼ���
	int			   ExpectedTotalTax;		//����� ���� ���Ǵ� ���� //�ؿ�
	int            Price;					//���� �ݾ�����
public:
	short		   TowerType[6];			//Ÿ�� Ÿ��
	int			   ClanSkill;				//Ŭ�� ��ų
	unsigned char  MercenaryNum[4];			//�뺴 ���� 0 -> 255
	int            TowerTypeDraw[6][2];	    //������
	int            MercenaryNumDraw;		//�뺴���� 


public:
	cSINSIEGE(){};
	~cSINSIEGE(){};

	int GetTaxRate();				    //���� ��������
	int	SetTaxRate(int TempTaxRate);	//���� ����

	int GetTotalTax();						//������� �Ⱦ���� ��������
	int cSINSIEGE::GetTaxMoney(int Money );	//�ݾ��� ã�´�


}; 

/*----------------------------------------------------------------------------*
*							MessageBox
*-----------------------------------------------------------------------------*/	
struct sinMESSAGEBOX_NEW
{
	int Flag;
	int PosiX;
	int PosiY;
	int SizeW;
	int SizeH;

	int ButtonIndex;
	int ButtonNum;
	int ButtonintPosiX[3];
	int ButtonintPosiY[3];
	RECT ButtonRect[3];

};	
class cSINSOD2
{

public:
	int UserType;
	int BoxIndex;
	char sinSod2Buff[65536];

	int Matbltr_Paper291;
	int Matbltr_Paper291_Text;
	int Matbltr_Logo;
	int Matbltr_ClanRank_KindBar;

	smTEXTUREHANDLE *ClanMark[10];
	smTEXTUREHANDLE *ClanMark_32;
	smTEXTUREHANDLE *lpbltr_clanN;
	smTEXTUREHANDLE *lpbltr_clanB;
	smTEXTUREHANDLE *lpbltr_ButtonBox;
	smTEXTUREHANDLE *lpbltr_Button_Clan;
	smTEXTUREHANDLE *lpbltr_Button_Clan_G;
	smTEXTUREHANDLE *lpbltr_Button_Prize;
	smTEXTUREHANDLE *lpbltr_Button_Prize_G;
	smTEXTUREHANDLE *lpbltr_Button_OK;
	smTEXTUREHANDLE *lpbltr_Button_OK_G;
	smTEXTUREHANDLE *lpbltr_ClanRank_Title;
	smTEXTUREHANDLE *Matbltr_ClanRank_ListLine;
	int  ClanMark_32Time;
	int  ClanMark_32Index;
	int  ClanMarkNum[10];
	int  ClanMarkIndex[10];
	int  ClanMarkLoadTime[10];
	int  TotalEMoney;
	int  Tax;
	int  TotalMoney;
	int  ClanImageNum;
	vector<string> sinClanRank;
	char szClanName[32];
	vector<string> sinClanMessage;

	int SendClanMoneyFlag;
	int RecvRemainMoney;
	char szClanMaster[24];
	int ClanMasterMessageBoxFlag;
	int ClanRankFlag;

	DWORD ClanMoney;
public:
	cSINSOD2(){};
	~cSINSOD2(){};

	void Init(); //Ŭ���� �ʱ�ȭ
	void Load();
	void Release();
	void Draw();
	void Draw(POINT3D *pPosi , POINT3D *pAngle);
	void DrawText();
	void Close();//Ŭ���� ���� 
	void Main();
	void LButtonDown(int x , int y);
	void LButtonUp(int x , int y);
	void RButtonDown(int x , int y);
	void RButtonUp(int x, int y);
	void KeyDown(); //Ű üũ 

	///////
	void ShowSod2MessageBox(); //�޼��� �ڽ� �����ֱ�

	void CloseSod2MessageBox(); //�޼��� �ڽ� �ݱ�

	void RecvWebDaTa();

	void RecvClanRank(char *szBuff);

	//Space�������� String�� ����
	vector<string> Split_ClanRankDaTa(const string& s);

	//String�� ���̸� �������� String�� ����
	vector<string> Split_ClanMessage(const string& s , const int Len[]);

	//�� DB���� �޼����� �޴´�
	int RecvWebData(int Index ,const string& s); //1���� 2 Ŭ������Ʈ

	//�� DB���� ���� ����Ÿ�� �����Ѵ�
	vector<string> cSINSOD2::Split_Sod2DaTa(const string& s);

};

//�޼��� �ڽ�
int ShowSinMessageBox_New(int PosiX , int PosiY , int SizeW , int SizeH , RECT *rect ,int ButtonNum=3);

//�������� ���� �޴´�
int sinRecvClanMoney(int RemainMoney , int GetMoney);



//////////////////// ������ //////////////////////////////
int sinShowSeigeMessageBox();
int RecvSeigeWebData(int Index , char *string);



#define HASIEGE_TAXRATES    1
#define HASIEGE_DEFENSE     2


//Ŭ�� ����
#define HACLAN_MAX    10   //Ŭ������

//Ŭ�� ������ ���� ����ü
struct sHACLANDATA{
	int		Flag;         //Ŭ�� �÷�
	int		Score;        //Ŭ�� ����
	int     ClanInfoNum;  //���忡 ǥ�õ� ��ǥ   
	char    ClanName[40]; //Ŭ���̸�

	DWORD   CLANCODE;     //Ŭ�� �ڵ�

	smTEXTUREHANDLE *lpClanMark;  //Ŭ�� ��ũ	   
};

class cHASIEGE{

public:
    /*---�������� ȣ��Ŵ� �Լ���----*/
	int   ShowSiegeMenu(PacketBlessCastleStatusSettingsData * psPacket);    //�����޴��� ����.
	int   ShowSiegeScore(PacketBlessCastleTopData * psPacket);     //���� Ŭ������ ������ ǥ���Ѵ�
	int   ShowExitMessage();         //���� �޼���
	int   ShowPlayTime(int);        //���� �޼���

	/*---Ŭ�� ��ų-----*/
	int   SetClanSkill(int);			  //Ŭ����ų�� ������ �����Ѵ�.
	int   SetCastleItemSkill(int);	      //������ ������ ��뽺ų

	int   SendServerSiegeData();          //������ ����Ÿ�� ������.
	int   SetCastleInit();				  //�ʱ�ȭ �Ѵ�.   
	int   SetCastleMenuInit();            //�ʱ�ȭ �Ұ��� ���⿡�� �� ó�����ش�.  

	int	  ShowPickUserKillPoint(int x,int y,int KillCount);

	//�������� �����Ű��.
	int   ShowCastlePlayMovie(char *szPath,char *TitleName,int Option);


public:
	
	cHASIEGE();
	~cHASIEGE();
	//�ʿ��Ѱ͸� �׽�Ʈ
	void init();
	void Main();
	void Draw();
	void KeyDown(); //Ű üũ
	void Release();
	void LButtonDown(int x , int y);
	void LButtonUp(int x,int y);
	void DrawText();
	void ImageLoad();
	
public:
	smTEXTUREHANDLE *lpSiegeTax;             //��������
	smTEXTUREHANDLE *lpSiegeDefense;         //������
	smTEXTUREHANDLE *lpCastleButton;         //������
	smTEXTUREHANDLE *lpMercenary;            //�뺴����


	smTEXTUREHANDLE *lpDefenseButton[2];     //��/�뺴���� ��ư
	smTEXTUREHANDLE *lpTax_Ok[2];            //��ã�� Ȯ�ι�ư
	
	smTEXTUREHANDLE *lpSiegeDefeseIcon_[3];     //���� ���� ������ �׷���
	smTEXTUREHANDLE *lpSiegeMercenaryIcon_[3];  //�뺴 ������ �׷���


	smTEXTUREHANDLE *lpSiegeDefeseIcon[3];    //���� ���� ������
	smTEXTUREHANDLE *lpSiegeClanskillIcon[3]; //Ŭ�� ��ų ������
	smTEXTUREHANDLE *lpSiegeMercenaryIcon[3]; //�뺴������

	smTEXTUREHANDLE *lpSiegeTaxButton;        //�������� ���ι�ư
	smTEXTUREHANDLE *lpSiegeDefenseButton;    //���� ���ι�ư
	smTEXTUREHANDLE *lpSiegeOkButton;         //Ȯ�� ��ư 
	smTEXTUREHANDLE *lpSiegeCancelButton;     //��ҹ�ư

	smTEXTUREHANDLE *lpCastleIcon[6];         //���� ���� Ȱ��ȭ ��ư
	smTEXTUREHANDLE *lpTaxScroll[2];          //��ũ�� ��ư
	smTEXTUREHANDLE *lpTaxGraph;              //��ũ��
	smTEXTUREHANDLE *lpDefenseRect[6];        //���� Ȱ��ȭ

	smTEXTUREHANDLE *lpTwoerImage;

	smTEXTUREHANDLE *haPlayerButton_G[3];
	smTEXTUREHANDLE *haPlayerButton[3];
	smTEXTUREHANDLE *haPlayerButtonBox[3];
	smTEXTUREHANDLE *haPlayerButtonDown[3];
};



//extern ���� ����
extern cHASIEGE chaSiege;
extern int haSiegeMenuFlag;        //�޴� �÷�
extern int haMercenrayIndex;       //�뺴 ������ �ε���
extern int HaTestMoney;            //�ӽ� �����Ѿ�
extern int haMercenrayMoney[3];    //�뺴���� �Ӵ�
extern int haSiegeBoardFlag;    
extern int haSendTowerIndex;      
extern int haTowerMoney; 
extern int haMovieFlag;

//////////////////// ������  end //////////////////////////////
extern cSINSOD2 cSinSod2;
extern sinMESSAGEBOX_NEW sinMessageBox_New;
extern LPDIRECT3DTEXTURE9	lpbltr_Button_OK;
extern LPDIRECT3DTEXTURE9	lpbltr_Button_OK_G;
extern int haCastleSkillUseFlag;
extern cSINSIEGE cSinSiege;

#endif

