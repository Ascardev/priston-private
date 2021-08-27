//Quest Bit Code
#define QUESTBIT_ELEMENTARY_A			1       //�ǰ��� â������
#define QUESTBIT_ELEMENTARY_B			2       //�ηÿ� ���
#define QUESTBIT_ELEMENTARY_C			4       //���� ���
#define QUESTBIT_ELEMENTARY_D			8       //��� ���� 
#define QUESTBIT_ELEMENTARY_E			16      //�𵥵��� ����
#define QUESTBIT_ELEMENTARY_F			32      //�ܴ����� ����
#define QUESTBIT_ELEMENTARY_G			64      //�Ҿ���� ��ġ
#define QUESTBIT_FURYOFPHANTOM          128      //ǻ���� ȯ��
#define QUESTBIT_ELEMENTARY_H			256
#define QUESTBIT_ELEMENTARY_I			512
#define QUESTBIT_ELEMENTARY_J			1024
#define QUESTBIT_ELEMENTARY_K			2048
#define QUESTBIT_ELEMENTARY_L			4096

/////����Ʈ�� ����
#define HAQUEST_CODE_ELEMENTARY_A		0x0020
#define HAQUEST_CODE_ELEMENTARY_B	    0x0021
#define HAQUEST_CODE_ELEMENTARY_C	    0x0022
#define HAQUEST_CODE_ELEMENTARY_D   	0x0023
#define HAQUEST_CODE_ELEMENTARY_E   	0x0024
#define HAQUEST_CODE_ELEMENTARY_F		0x0025
#define HAQUEST_CODE_ELEMENTARY_G		0x0026
#define HAQUEST_CODE_FURYOFPHANTOM      0x0027
#define HAQUEST_CODE_ELEMENTARY_H		0x0028
#define HAQUEST_CODE_ELEMENTARY_I		0x0029
#define HAQUEST_CODE_ELEMENTARY_J		0x0030
#define HAQUEST_CODE_ELEMENTARY_K		0x0031
#define HAQUEST_CODE_ELEMENTARY_L		0x0032

#define MAX_HAQUEST_ELEMENTARY			12
//
enum eQuestKind
{
	Quest_A,
	Quest_B,
	Quest_C,
	Quest_D,
	Quest_E,
	Quest_F,
	Quest_G,
	Quest_H,
	Quest_I,
	Quest_J,
	Quest_K,
	Quest_L,
};
/*----------------------------------------------------------------------------*
*						����ü
*-----------------------------------------------------------------------------*/	
struct sQUEST_ELEMENTARY
{ 
	DWORD CODE;
	DWORD BackUpCode;
	int   Kind;
	int   State;
	short Monster[2];
};
/*----------------------------------------------------------------------------*
*						Ŭ����
*-----------------------------------------------------------------------------*/
class cHaQuest
{
private:
	char szBuff[128];
public:
	//
	sQUEST_ELEMENTARY  sHaQuestElementary[MAX_HAQUEST_ELEMENTARY];	
	char szQuestMonsterName[64];
	int iJob_Index;
	int QuestKeyCode;
	int KindClanIndex;
	//
	cHaQuest();
	~cHaQuest();	
	//
	int HaCheckQuestElementary(int npcNum,int QuestKey=0,int KindClan=0);
	int haSetQuestTimer(int Time = 0);
	int haQuestCheck(int CODE);  //���� �ʺ�  ����Ʈ�� ����������	
	//�ʺ� ���� ����Ʈ
	int haElementaryQuest_A(int npcNum=0);  //�ǰ��� â������
	int haElementaryQuest_B(int Race = 0);			    //�η��� ��� 
	int haElementaryQuest_C();	//���� ���
	int haElementaryQuest_D(int npcNum=0);	//��� ����
	int haElementaryQuest_E();	//�𵥵��� ����
	int haElementaryQuest_F();				//�ܴ����� ����
	int haElementaryQuest_G();
	int haElementaryQuest_H();
	int haElementaryQuest_I();
	int haElementaryQuest_J();
	int haElementaryQuest_K();
	int haElementaryQuest_M();
	int CancelQuest();
public:
	//
	sQUEST_ELEMENTARY        sHaQuest100LV;	
	bool                     bFuryQuestFlag;
	int                      iFuryQuestIndex[2]; 
	char                     cItemName[32];
	bool                     FuryBattleFlag;
	//������ �̹���
	smTEXTUREHANDLE     *lpQuestItemImage[10];
	smTEXTUREHANDLE     *lpQuestButtonImage[4];


	//�ʿ��Ѱ͸� �׽�Ʈ
	void init();
	void Main();
	void Draw();
	void KeyDown(); //Ű üũ
	void LButtonDown(int x , int y);
	void LButtonUp(int x,int y);
	void DrawText();
	void ImageLoad();
	//
	int  showFuryQuest();                  //100LV ����Ʈ ȣ��
	int  showFuryQuestItem(int Kind=0);    //���� ������ 
	int  RecvBattleNpcResult(int flag);    //ǻ������ ���� ��� ��
	int  Recv100LVItem();                  //����������� �޴µ�.

	

};
/*----------------------------------------------------------------------------*
*						extern 
*-----------------------------------------------------------------------------*/	
extern cHaQuest chaQuest;
extern DWORD haElementaryQuestLog;
extern void HaCheckQuestNpc(int NpcCount);
