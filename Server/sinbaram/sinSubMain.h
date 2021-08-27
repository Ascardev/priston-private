/*----------------------------------------------------------------------------*
*	���ϸ� :  sinSubMain.h	
*	�ϴ��� :  ���� �Լ����� �����Ѵ� 
*	�ۼ��� :  ����������Ʈ 12��
*	������ :  �ڻ� 
*-----------------------------------------------------------------------------*/	
#ifndef	_SINSUBMAIN_HEADER_

#define _SINSUBMAIN_HEADER_

/*----------------------------------------------------------------------------*
*							    DEFINES
*-----------------------------------------------------------------------------*/	

#define SIN_OPEN		1
#define SIN_CLOSE		0


#define MAX_SIN_KIND_INTER		17

#define SIN_CHARSTATUS	0
#define SIN_INVENTORY	1
#define SIN_SHOP		2
#define SIN_SKILL		3
#define SIN_TRADE		4
#define SIN_WAREHOUSE	5
#define SIN_CRAFTITEM	6
#define SIN_AGING		7
#define SIN_MYSHOP		8
#define SIN_CHARSHOP	9			
#define SIN_SMELTING	10
#define SIN_MANUFACTURE 11
#define	SIN_MIXTURE_RESET	12
#define SIN_ELEMENT		13
#define SIN_CARAVAN		14
#define SIN_SOCKET		15
#define SIN_SYSTEM		16


#define SIN_ALL_CLOSE	100


///////////����¡ Ŭ���� 
#define SIN_AGING_ATTACK			100
#define SIN_AGING_CRITICAL			101
#define SIN_AGING_BLOCK				102
#define SIN_AGING_DEFENSE_ORB		103		// ����� - ����¡ ������(�� ���� ���� ������ų��)
#define SIN_AGING_DEFENSE_ARMOR		104		// ����� - ����¡ ������(�� ���� �κ� ������ų��) 
#define SIN_AGING_DEFENSE_BOOTS		105		// ����� - ����¡ ������ �߰�(����)
#define SIN_AGING_DEFENSE_GLOVES	106		// ����� - ����¡ ������ �߰�(�尩)
#define SIN_AGING_DEFENSE_ARMLETS	107		// ����� - ����¡ ������ �߰�(�ϸ�)

/////////// IP�� Ưȭ ���� 
#define PRORATE_USER		1
#define FREE_USER			2
#define VIP_USER			4
#define BIRTHDAY_USER		8



#define SIN_WINGRESULT_CRISTAL		0x101
 

/*���� ������ ����� ���� �����Ѵ� */

int sinGetAccuracy(int desLV , int desDefense); //�� ���߷� 

int sinGetMonsterAccuracy(int MonsterLV , int MonsterAttack_Rating); //���� ���߷�  

int sinGetPVPAccuracy(int MyLevel , int MyAttack_Rating , int DesLevel , int DesDefense);//���� VS ���� ���߷�

int sinGetCritical(int desLV);//���� ũ��Ƽ�� 

int sinGetBlockRating(int desLV);//����   

 
extern int ChangeJobButonCheck2; //��ư�ٿ��� �ѹ� �ųʶٴ� �÷�(�̰͵� ���� �����̴� ����!!)


int sinSetAgingItemIncreState(Item *pItem);
int sinAgingItemInit(Item *pItem);

//����¡ �ɷ� ���� 
int sinSetDurabilityAging(Item *pItem); // �������� ����Ѵ�
int sinSetDamageAging(Item *pItem);
int sinSetDefenseAging(Item *pItem , int Percent,int Type);
int sinSetAttackRateAging(Item *pItem , int AddNum);
int sinSetAbsorbAging(Item *pItem , float Percent);
int sinSetCriticalAging(Item *pItem);
int sinSetBlockRateAging(Item *pItem);


//����¡ �ɷ� �ٿ�
int sinDownDurabilityAging(Item *pItem);
int sinDownDamageAging(Item *pItem);
int sinDownDefenseAging(Item *pItem , int Percent);
int sinDownAttackRateAging(Item *pItem , int AddNum);
int sinDownAbsorbAging(Item *pItem , float Percent);
int sinDownCriticalAging(Item *pItem);
int sinDownBlockRateAging(Item *pItem);


//����¡ �����ۿ� ���� ��ŷ�� ���´� 
int sinCheckAgingItemHack(ItemData *pItem);


//WingItem ����Ʈ
DWORD sinWingItemQuestServer(sCRAFTITEM_SERVER *pWingItem , CharacterData *pChar_Info);

int GetRace(int Class);
int GetSex(int Class);
/*----------------------------------------------------------------------------*
*							�ܺ� extern �Լ� 
*-----------------------------------------------------------------------------*/	

extern int ReformItem(Item *lpItemInfo ); //������ �����ޱ� 
extern int CheckItemForm(Item *lpItemInfo ); //������ ����Ȯ�� 

extern int CompareItems(Item *lpItemInfo1 , Item *lpItemInfo2 );//������ 2���� ���Ѵ�



/*----------------------------------------------------------------------------*
*							  extern ����  
*-----------------------------------------------------------------------------*/	

extern int sinTestFlag;      //�׽�Ʈ�� ���� �÷� 
extern int MouseButtonUpEvent;

extern int CursorClass; //Ŀ������ (default�� 1�� �ش�  �������� ���� �� CursorClass = 0�����ش� )

extern int Accuracy_Table[][2]; //���߷� ���̺��� �ͽ����Ѵ� 

extern int sinSecretFlag;  //��ȣ �÷� 


extern int ItemIndex1[3];
extern int ItemIndex2[3];

extern int ItemImageNotExitFlag;

extern int OverDay_Item_Flag;

extern int haSiegeBoardTempFlag;

#endif
