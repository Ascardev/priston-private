//Quest Bit Code
#define QUESTBIT_ELEMENTARY_A			1       //피곤한 창고지기
#define QUESTBIT_ELEMENTARY_B			2       //두련운 기운
#define QUESTBIT_ELEMENTARY_C			4       //사탕 배달
#define QUESTBIT_ELEMENTARY_D			8       //고블린 동산 
#define QUESTBIT_ELEMENTARY_E			16      //언데드의 위협
#define QUESTBIT_ELEMENTARY_F			32      //외눈박이 괴물
#define QUESTBIT_ELEMENTARY_G			64      //잃어버린 망치
#define QUESTBIT_FURYOFPHANTOM          128      //퓨리의 환영
#define QUESTBIT_ELEMENTARY_H			256
#define QUESTBIT_ELEMENTARY_I			512
#define QUESTBIT_ELEMENTARY_J			1024
#define QUESTBIT_ELEMENTARY_K			2048
#define QUESTBIT_ELEMENTARY_L			4096

/////퀘스트의 종류
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
*						구조체
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
*						클래스
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
	int haQuestCheck(int CODE);  //현재 초보  퀘스트가 진행중인지	
	//초보 진행 퀘스트
	int haElementaryQuest_A(int npcNum=0);  //피곤한 창고지기
	int haElementaryQuest_B(int Race = 0);			    //두려운 기운 
	int haElementaryQuest_C();	//사탕 배달
	int haElementaryQuest_D(int npcNum=0);	//고블린 동산
	int haElementaryQuest_E();	//언데드의 위협
	int haElementaryQuest_F();				//외눈박이 괴물
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
	//아이템 이미지
	smTEXTUREHANDLE     *lpQuestItemImage[10];
	smTEXTUREHANDLE     *lpQuestButtonImage[4];


	//필요한것만 테스트
	void init();
	void Main();
	void Draw();
	void KeyDown(); //키 체크
	void LButtonDown(int x , int y);
	void LButtonUp(int x,int y);
	void DrawText();
	void ImageLoad();
	//
	int  showFuryQuest();                  //100LV 퀘스트 호출
	int  showFuryQuestItem(int Kind=0);    //보상 아이템 
	int  RecvBattleNpcResult(int flag);    //퓨리와의 대전 결과 값
	int  Recv100LVItem();                  //보상아이템을 받는디.

	

};
/*----------------------------------------------------------------------------*
*						extern 
*-----------------------------------------------------------------------------*/	
extern cHaQuest chaQuest;
extern DWORD haElementaryQuestLog;
extern void HaCheckQuestNpc(int NpcCount);
