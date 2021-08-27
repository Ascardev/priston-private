//���� �ڵ�
#define MONSTER_BAGON				1
#define MONSTER_SKELETON_WARRIOR	2
#define MONSTER_HEAD_CUTTER			3 // ħ��ʿ
#define MONSTER_ARMORED_BETTLE		4
#define MONSTER_SKELETON_RANGER		5
#define MONSTER_TITAN				6
#define MONSTER_MURPIN				7
#define MONSTER_DIREBEE				8
#define MONSTER_TYPOON				9
#define MONSTER_RATOO				10
#define MONSTER_GROTESQUE			11
#define MONSTER_IRONFIST			12
#define MONSTER_OMEGA				13
#define MONSTER_D_MACHINE			14
#define MONSTER_MOUNTAIN			15

//ù��° ����
#define MONSTER_SKELETON_KNIGHT     16 //���̷��� ����Ʈ
#define MONSTER_SOLID_SNAIL         17 //�ָ��� ������
#define MONSTER_THORN_CROWLER       18 //�� ũ�ο﷯
#define MONSTER_MUMMY               19 //�ӹ�
#define MONSTER_DOOM_GUARD          20 //�� ����
#define MONSTER_FIGON               21 //���̰�
#define MONSTER_STONE_GIANT         22 //���� ���̾�Ʈ
#define MONSTER_STONE_COLEM         23 //���� ��
#define MONSTER_IRON_GUARD          24 //���̾� ����
#define MONSTER_AVELLRIN            25 //�ƺ���
//�ι��� ����
#define MONSTER_AVELRISK_L          26 //�ƺ�����ũ-L
#define MONSTER_BEEBUL              27 //���
#define MONSTER_ILLUSION_KNIGHT     28 //�Ϸ�������Ʈ
#define MONSTER_NIGHT_MARE          29 //����Ʈ �޾�
#define MONSTER_WITCH               30 //��ġ
#define MONSTER_HEAVY_GOBLIN        31 //��� ���
#define MONSTER_DAWLIN              32 //�ٿ츰
#define MONSTER_STYGIAN             33 //��Ƽ����
#define MONSTER_INCUBUS             34 //��ť����
#define MONSTER_CHAIN_GOLEM         35 //ü�� ��
#define MONSTER_DARK_SPECTOR	    36 //��ũ ������
#define MONSTER_METRON              37 //��Ʈ��
//������ ����
#define MONSTER_AVELRISK_LOAD       38 //�ƺ�����ũ �ε�
#define MONSTER_DUSK                39 //����ũ
#define MONSTER_SADNESS             40 //���帮��

//�ű� ����Ʈ ���� �߰� 
#define MONSTER_HOPY                41 //������
#define MONSTER_RABIE               42 //����
#define MONSTER_NORTHGOBLIN         43 //��ħ��
#define MONSTER_HOBGOBLIN           44 //ħ�ޱ�
#define MONSTER_CORRUPT             45 //������
#define MONSTER_SKELETON            46 //���̷���Cyclops
#define MONSTER_CYCLOPS             47 //����Ŭ�ӽ�
//100LV ����Ʈ ����
#define MONSTER_FERRUMHEART         48 //����� ����
#define MONSTER_ICE                 49 //����Ŭ�ӽ�
#define MONSTER_ZOBI				50 //��ʬ
#define MONSTER_LEECH				51 //�����
#define MONSTER_OASIS				52 //���޹���
#define MONSTER_DUN2				53 //����2�����
#define MONSTER_DARKNESS			54 //����ʥ�����
#define MONSTER_DUN5				55 //��������2��
#define MONSTER_IRON2				56 //��·2�Ĺ���
#define MONSTER_BABEL				57 //�ͱ���





//Quest Bit Code
#define QUESTBIT_LEVEL_30			1
#define QUESTBIT_LEVEL_55			2
#define QUESTBIT_LEVEL_70			4
#define QUESTBIT_LEVEL_80			8
#define QUESTBIT_LEVEL_85			16
#define QUESTBIT_LEVEL_90			32
#define QUESTBIT_LEVEL_80_2			64
#define QUESTBIT_LEVEL_90_2			128





/////����Ʈ�� ����
#define SIN_QUEST_CODE_CHANGEJOB		0x0001
#define SIN_QUEST_CODE_CHANGEJOB2_NPC_M	0x0002
#define SIN_QUEST_CODE_CHANGEJOB2_NPC_D	0x0003
#define SIN_QUEST_CODE_CHANGEJOB3   	0x0004
#define SIN_QUEST_CODE_CHANGEJOB4   	0x0010

//���� ����Ʈ
#define SIN_QUEST_CODE_LEVEL30			0x0005
#define SIN_QUEST_CODE_LEVEL55			0x0006
#define SIN_QUEST_CODE_LEVEL55_2		0x0007
#define SIN_QUEST_CODE_LEVEL70			0x0008
#define SIN_QUEST_CODE_LEVEL80			0x0009
#define SIN_QUEST_CODE_LEVEL85			0x000A
#define SIN_QUEST_CODE_LEVEL90			0x000B


#define SIN_QUEST_CODE_LEVEL80_2		0x000C
#define SIN_QUEST_CODE_LEVEL90_2		0x000D


/////����Ʈ�� ������� 
#define SIN_QUEST_PROGRESS				1
#define SIN_QUEST_COMPLETE				2

/*----------------------------------------------------------------------------*
*						Quest ����
*-----------------------------------------------------------------------------*/	
struct sQUEST_CHANGEJOB{ //�۽�ũ�� ����̿� 2������
	DWORD CODE;
	DWORD BackUpCode;
	int Kind;
	int State;

};

struct sQUEST_CHANGEJOB3{ //�۽�ũ�� ����̿� 3������
	DWORD CODE;
	DWORD BackUpCode;
	int   Kind;
	int   State;        //���� Count
	short Monster[2];   //0 ���� ���� 1 ���� ī��Ʈ
	int   StartLevel;   //�������۽� ����
	int   AgingCount;   //���翡��¡ ����

};

/*----------------------------------------------------------------------------*
*						Wing Item Quest
*-----------------------------------------------------------------------------*/	
struct sQUEST_WINGITEM{
	DWORD CODE;
	int Kind;
	int State;

};
int SetChangeJob3QuestItem(Item *pItem , int Down = 0);


/*----------------------------------------------------------------------------*
*						extern 
*-----------------------------------------------------------------------------*/	
extern POINT QuestMessageBoxPosi2;
extern POINT QuestMessageBoxSize2;
extern int sinChangeJobButtonShow;
extern int sinChangeJobButtonShow2; //����̿� ����
extern int sinChangeJobButtonShow3; //3������
extern int sinChangeJobButtonShow4; //4������

extern char *QuestFilePath[];
extern char *QuestFilePath3[];
extern int CheckQuestComplete;	//������ �������

extern int CheckQuestButtonShow1;
extern int CheckQuestButtonShow2;
extern int CheckQuestButtonShow3;

extern int Quest_Flag;

extern sQUEST_CHANGEJOB	sinQuest_ChangeJob; //�۽�ũ�� 2������	
extern sQUEST_CHANGEJOB	sinQuest_ChangeJob2;//����̿� 2������
extern sQUEST_CHANGEJOB3   sinQuest_ChangeJob3;//�۽�ũ�� ����̿� 3�� ��������Ʈ 
extern sQUEST_CHANGEJOB3   sinQuest_ChangeJob4;//�۽�ũ�� ����̿� 4�� ��������Ʈ 

extern char *WingQuestFilePath_a[];
extern char *WingQuestFilePath_b[];
extern char *WarpGateDoc[];
extern char *WarningInitPoint[];
extern char *HaWarpGateDoc[];

extern ItemData TempQuestItem;
extern int CheckQuestItemDownFlag;

extern char *BabelEventDoc;
extern char *NineTailFoxDoc;
extern char *StarDustDoc;		 //ũ�������� �̺�Ʈ
extern char *CristalEventDoc;//�ϰ����� ũ����Ż�� ����
extern char *WatermelonDoc;//���� ��ƿ��� �̺�Ʈ
extern char *PumpkinDoc;//ȣ�� ��ƿ��� �̺�Ʈ
extern char *StarDoc;
extern char *ValentineDoc;
extern char *PristonAlphabetDoc; // ����� - ���ĺ� ���� �̺�Ʈ
extern char *CandydaysDoc;
extern char *MagicalGreenDoc;
extern char *TearOfKaraDoc;
extern char *Findinvestigator1_1Doc;
extern char *Findinvestigator1_2Doc;
extern char *Findinvestigator1_3Doc;
extern char *Findinvestigator2_1Doc;
extern char *Findinvestigator2_2Doc;
extern char *Findinvestigator3_1Doc;
extern char *Findinvestigator3_2Doc;

extern sQUEST_CHANGEJOB3   sinQuest_Level30;
extern sQUEST_CHANGEJOB3   sinQuest_Level55;
extern sQUEST_CHANGEJOB3   sinQuest_Level55_2;
extern sQUEST_CHANGEJOB3   sinQuest_Level70;
extern sQUEST_CHANGEJOB3   sinQuest_Level80;
extern sQUEST_CHANGEJOB3   sinQuest_Level85;
extern sQUEST_CHANGEJOB3   sinQuest_Level90;
extern DWORD sinQuest_levelLog;
extern WORD sinFruitStatus[2];
extern BYTE sinTempStatus[8];
extern sQUEST_CHANGEJOB3   sinQuest_Level80_2;
extern sQUEST_CHANGEJOB3   sinQuest_Level90_2;
extern char *QuestFilePath4[];
extern char szQuestMonsterName[64];
