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

/*----------------------------------------------------------------------------*
*							�����Լ� 
*-----------------------------------------------------------------------------*/	
void InitSub();     //������� �ʱ�ȭ 

void MainSub();	    //������� ���� 

void DrawSub();     //������� �׸��� 

void CloseSub();    //������� ���� 

int sinRecvMessage( DWORD dwCode , void *RecvBuff ); //�������� Data�� �޾ƿ´� 

void DrawSprite(int winX ,int winY,smTEXTUREHANDLE *pdds,int x, int y, int width , int height,int Bltflag=1);
void DrawRotSprite(int winX,int winY,LPDIRECT3DTEXTURE9 lpTexture,int x,int y,int width,int height);

int sinGetItemInfo(DWORD CODE , char *szImagePath); //�������� ����(ASE)�� ���ؿͼ� ������(*szImagePath)�� �����Ѵ� 

int sinUsePotion(); //����� ���������� ������ ����Ѵ� 

int sinSetInvenItem(Item *sItemInfo ); //�κ��丮�� �������� �����Ѵ� 

/*���� ������ ����� ���� �����Ѵ� */

int sinGetAccuracy(int desLV , int desDefense); //�� ���߷� 

int sinGetMonsterAccuracy(int MonsterLV , int MonsterAttack_Rating); //���� ���߷�  

int sinGetPVPAccuracy(int MyLevel , int MyAttack_Rating , int DesLevel , int DesDefense);//���� VS ���� ���߷�

int sinGetCritical(int desLV);//���� ũ��Ƽ�� 

int sinGetBlockRating(int desLV);//���� 

int sinGetAbsorb(int Type=0); //�����

/*���� �������� */
void sinRegen();
void sinUseStamina();
void sinSetRegen();   


/*Ű��ư �� ���콺 �Լ� */

void sinLButtonUp();

void sinLButtonDown();

void sinRButtonUp();

int StopCharMotion(int x ,int y); //�������� ������� ã�´� 

void sinReload(); //�׷��� ����Ÿ���� �ٽ÷ε��Ѵ� 

/*���콺 & Key �Է� */
int sinGetMouseButton(int num);//���콺 Ŭ���� ���� 
void sinMouseMain();

int sinGetKeyClick(int num); //Ű�Է���  ����
void sinKeyClickMain();

void ShowInterFace(); //���� �������̽��� �����ش� 

extern int CheckEditSize(int x , int lx , char *String); //Text�� ���� ��ġ�� �����Ѵ� 


/* ������ ���� */

int LoadItemImage(Item *sItemInfo , ItemData *TempItem); //�������� �̹����� �ε��Ѵ� 

int sinUsePotion(); //����� ���������� ������ ����Ѵ� 

int StopCharMotion(int x ,int y); //�������� ������� ã�´� 

/* ���� ���� */
int sinSetShopItem(Item *pItem,int ItemCount, int ItemKind); //������ ���� ������ �������� �޴´� 


/*�׽�Ʈ ���� */
void sinTestDrawText();

/* TEST */
void sinTestKey(); //�׽�ƮŰ ���� 

/*Ʈ���̵� ���� */
int sinRequestTrade(DWORD CODE , char *CharName);


/*  ��ų */
int sinSkillMaster(int ChangeJob=0); //��ų�� ���� ������ �Ѵ� 

int sinSkillMasterClose();//��ų ���⸦ ��ģ�� 

/* ��Ƽ */
int ShowParty();

/*����Ʈ */
int ShowQuest();



/*������ ���� ���׹̳� �ڵ�ȭ */
short sinGetLife();		//�������� �о�´� 
short sinGetMana();		//������ ���´� 
short sinGetStamina();	//���׹̳��� ���´� 

void sinSetLife(short Life);	//�������� �����Ѵ� 
void sinSetMana(short Mana);	//������ �����Ѵ� 
void sinSetStamina(short Stamina);//���׹̳��� �����Ѵ� 

/* ����¡ */
int sinCheckAgingLevel(int Kind, bool bBillingUse);	//������ üũ���� ����¡�Ѵ� // ����� - ����¡ ������ ��뿩�θ� �߰� bBillingUse



/* ����Ʈ */
int sinSetQuestItem(Item *sItemInfo ); //����Ʈ �������ϰ��
extern int ChangeJobButonCheck2; //��ư�ٿ��� �ѹ� �ųʶٴ� �÷�(�̰͵� ���� �����̴� ����!!)

//��ŷ������ ���ؼ� ���� �Ѱ����� �����Ѵ� 
int sinMinusMoney(int Money,int Kind=0);
int sinPlusMoney(int Money);

int sinMinusMoney2(int Money);
int sinPlusMoney2(int Money);

int sinGetElement(Unit *pChar); //���ҼӼ��� ���Ѵ� 


/* ����¡ */
int sinRecvAgingIncreStateItem(Item *pItem);



//����¡ �����ۿ� ���� ��ŷ�� ���´� 
int sinCheckAgingItemHack(ItemData *pItem);
int SendWingQuestItem(); //�������� ����Ʈ 
int RecvWingItem(sCRAFTITEM_SERVER *pWingItem);
int AgingRing();//���� ����¡ �Ѵ�

//�κ��丮�� ����ó���ؾߵ� ����Ⱦ������� ����Ѵ�
int sinSetSpecialItemCode(Item *pItemInfo);

//���ڰ� �޸����� �����Ѵ�
int NumLineComa(int Num , char *pBuff);

//������ ������ �����Ѵ�
int sinSaveGame(DWORD CODE , int Count);

//��¥������ �������� �����ش�
int OverDay_Item_Delete(ItemData *pItem);

//��� �������̽��� �ݴ´�
int sinCloseInterFace();

//�������� ���ɼ��ִ��� üũ���ش�
int sinCheck_ShowHelpMap();

//ForceOrb �������� �޴´�
int sinRecvForceOrb(Item *pItemInfo , int Count);

//����Ŭ���̺�Ʈ�� �޴´�
int sinDoubleClick();

int GetRace(int Class);
int GetSex(int Class);
/*----------------------------------------------------------------------------*
*							�ܺ� extern �Լ� 
*-----------------------------------------------------------------------------*/	

extern int ReformItem(Item *lpItemInfo ); //������ �����ޱ� 
extern int CheckItemForm(Item *lpItemInfo ); //������ ����Ȯ�� 

extern int ReformCharForm(); //������ 
extern int CheckCharForm(); //���� 

extern int sinSetCharItem(DWORD CODE , DWORD Posi , BOOL SetFlag ); //ĳ���Ϳ� �������� �����Ѵ� 

extern int sinThrowItemToFeild(ItemData *pItem); //�������� �ʵ忡 ������ 

extern int sinActionPotion(); //���� ����� 

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
