#define INVENTORY_MAXITEM		100
#define INVENTORY_BOX_SIZE		22
#define INVENTORY_BOX_COL		6
#define INVENTORY_BOX_ROW		12

#define INVENTORY_MAX_POS		16
#define MAX_WINGQUEST			10
#define MAX_CRYSTAL				54


#define		NO_BOX_COLOR				0
#define		SET_ITEM_CHECK_COLOR		1
#define		OVERLAP_ITEM_COLOR			2
#define		NOT_SETTING_COLOR			3
#define		OVERLAP_BOX_COLOR           4
#define		SELECT_ITEM_COLOR			5
#define     NOT_USE_COLOR				6
#define		NOT_AGING_ITEM				7
#define     NOT_ENOUGH_MONEY			8

#define     MAX_USESKILL                21 

struct sINVENTORY
{
	DWORD  Position;
	RECT   Rect;
	int    ItemIndex;
	int    WeaponClass;

};

#define		MAX_INVEN_PARTICLE		200

#define		SIN_EFFECT_SHOW_INVEN		1
#define		SIN_EFFECT_SHOW_WAREHOUSE	2
#define		SIN_EFFECT_SHOW_TRADE		3
#define		SIN_EFFECT_SHOW_GYUNGFUM	10

struct sELEMENT_ATTACK
{
	int Bio[2];
	int Fire[2];
	int Ice[2];
	int Lighting[2];
	int Posion[2];
};
struct sINVENTORY_EFFECT
{
	smFACE2D InvenFace;
	int Time;
	int Max_Time;
	POINT Speed;
	int Direction;
	int AniCount;
	int FadeType;
	int Kind;
	int Flag;
	POINT DesPosi;
	POINT Posi;
};
struct sUNIONCORE_EFFECT
{
	int Flag;
	int Time;
	int Max_Time;
	int MatNum;
	int x;
	int y;
	int Alpha;
	int w;
	int h;
};

struct sWINGQUEST
{
	DWORD NeedItemCode[6];
	int   Money;
	DWORD ChangeItemCode;
};

class cINVENTORY
{
public:
	int OpenFlag;

	ItemData InvenItem[INVENTORY_MAXITEM];

	ItemData InvenItemTemp[INVENTORY_MAXITEM];
	ItemData BackUpInvenItemTemp[INVENTORY_MAXITEM];

	char JobName[32];

	smTEXTUREHANDLE	*lpInvenArrow[3];
	smTEXTUREHANDLE	*lpCoverSmall;
	smTEXTUREHANDLE	*lpCoverMiddle;
	smTEXTUREHANDLE	*lpCoverLarge;
	smTEXTUREHANDLE	*lpMyShopIcon;
	smTEXTUREHANDLE	*lpMyShopIcon_T;

	smTEXTUREHANDLE	*lpPotionBack;
	smTEXTUREHANDLE	*lpChangeABInfo[2];
	smTEXTUREHANDLE	*lpConstmeInfo;
	smTEXTUREHANDLE	*lpExitInfo;
	smTEXTUREHANDLE	*lpWeightInfo;
	smTEXTUREHANDLE	*lpItemABInfo[2];

	smTEXTUREHANDLE	*lpShowWeaponClass[4];
	smTEXTUREHANDLE	*lpItemElementClass[3];

	smTEXTUREHANDLE	*lpIndiShopIcon;

	smTEXTUREHANDLE	*lpPuzzleInven;
	smTEXTUREHANDLE	*lpPuzzlewidth;
	smTEXTUREHANDLE	*lpPuzzleHeight;

	smTEXTUREHANDLE	*lpInvenMain[2];

	smTEXTUREHANDLE	*lpUnionCoreEffect[4];

	smTEXTUREHANDLE	*lpSpecialItem[2];
	smTEXTUREHANDLE	*lpSpecialItemInfo[2];
	smTEXTUREHANDLE	*lpSpecialInven;
	smTEXTUREHANDLE	*lpCostumeUI;

	smTEXTUREHANDLE	*lpGold7;
	smTEXTUREHANDLE	*lpExp7;

	int MatInven[4];   
	int MatInvenParticle[5];

	DWORD InvenDataCheckSum;
	DWORD dwLastTime[2];

	int iEventBuyItemKind;
	
public:
	cINVENTORY();
	~cINVENTORY();

	void Init();
	void Load();
	void Release();
	void Draw();
	void Close();
	void Main();
	void LButtonDown(int x , int y);
	void LButtonUp(int x , int y);
	void RButtonDown(int x , int y);
	void RButtonUp(int x, int y);
	void KeyDown();
	int LoadItemInfo();
	int AutoSetInvenItem(ItemData *pItem , int PostBox=0);
	int InvenEmptyAearCheck(ItemData *pItem);
	int SetItemToChar(int CheckHackFlag=0);
	int LastSetInvenItem(ItemData *pItem, int AutoSet=0);
	int PickUpInvenItem(int x , int y, int PickUpFlag=0);
	int ChangeInvenItem(ItemData *pItem);
	int CrashInvenItem(RECT &desRect ,int PassItemIndex=0 );
	void InvenItemLoad();
	void InvenItemRelease();
	int CheckRequireItem();
	void CheckWeight();
	int CheckRequireItemToSet(ItemData *pItem);
	int InvenNotOpenCheck(ItemData *pItem);
	int SetTwoHandItem(ItemData *pItem);
	int PickUpTwoHandItem(ItemData *pItem);
	int OverlapTwoHandItem(ItemData *pItem);
	int OverlapTwoHandSwitch(ItemData *pItem);
	int ClearTwoHandPosiAndItem(ItemData *pItem);
	int AutoSetPotion(ItemData *pItem);
	int MouseSetPotion(ItemData *pItem);
	int AutoSetPotionToBox(ItemData *pItem);
	int cINVENTORY::ReSettingPotion();
	int UsePotion(int x , int y);
	int CheckOverlapItem(ItemData *pItem, int PassItemIndex);
	int SearchJobAndSetting();
	void LoadCharState();
	int ChangeABItem(int Posi);
	int DrawInvenText();
	int SetInvenItemAreaCheck(ItemData *pItem);
	int InitColorRect();
	int CheckInvenPos(int x , int y , int lx ,int ly , RECT &rect);
	int ThrowInvenItemToField(ItemData *pItem);
	int NoSettingThrowItem(ItemData *pItem ,int Flag= 0);
	sITEMPRICE GetInvenItemPrice(ItemData *pItem);
	int RepairInvenItem(ItemData *pItem , int RepairCost);
	
	int CheckSetOk(ItemData *pItem,int AutoFlag=0);
	int CopyItemClear(ItemData *pItem);
	int ImsiCheckItemImageSize();
	int ReSetPotionXY(ItemData *pItem,int kind=0);
	int UseEcore(ItemData *pItem);
	int ResetMouseItem();
	int CheckInvenItemForm();
	int ReFormInvenItem();
	int CheckMoneyLimit(int Money);
	int CheckPotionNumForm();
	int ReFormPotionNum();
	int CheckSpecialItem(ItemData *pItem);
	int ShowInvenEffectParticle();
	int SetInvenParticle(int x , int y , int Kind );
	int sinDrawInvenTexImage(smFACE2D *Face);
	int MoveInvenParticle();
	int CheckSetEmptyArea(ItemData *pItem);
	int ResetInvenItemToServer(DWORD CODE ,DWORD Head , DWORD CheckSum , DWORD Time );
	int DeleteInvenItemToServer(DWORD CODE ,DWORD Head , DWORD CheckSum);
	int EatSongPyeun(ItemData *pItem);
	int CharOnlySetItem(ItemData *pItem);
	int HackCharStateCheck(CharacterData *pChar_Info , CharacterData *desChar_Info);
	int CheckResetInvenItem();
	int SearchItemCode(DWORD CODE , int KindFlag=0);
	int CheckDamage();
	int ClearQuestItem();
	int RecvLinkCore(Item *pItem);
	int CheckMousePotionNumForm();
	int ReFormMousePotionNum();
	int SetUnionCoreEffect(int x , int y);
	int UnionCoreParticleProcess();
	int UnionCoreParticle(int x , int y);
	int UnionCoreParticle2(int x , int y , int Flag = 0);
	int CheckInvenEmpty(ItemData *pItem);
	int SetInvenToItemInfo(Item *pItemInfo);
	int LoadMoneyExpImage(ItemData *pItem);
	int sinWingQuestNpc(); 
	int SendWingQuestItem(int Index);
	int CheckRequireItemToSet2(ItemData *pItem);
	int SetSpecialItem(ItemData *pItem);
	int ChangeSpecialItem(int Flag = 0);
	int CheckSpecialItemPosi();
	int SearchItemIndex(DWORD CODE , int KindFlag);
	int ChangePuzzle(ItemData *pItem);
	int CheckPuzzle();
	int CheckSendPuzzle();
	int SendPuzzleNpc();
	int SendEventItem();
	int CheckEventItem();
	int DrawForceOrbEffect(int x , int y);
	int UseForceOrb(ItemData *pItem , int Flag = 0);
	int SetForceOrb(DWORD ItemCODE , int Time);
	int UseCapsuleItem(ItemData *pItem);
	int CheckFoxEventItem();
	int SendFoxEventItem();
	int CheckChristMasEventItem();
	int SendChristmasEventItem();
	int ReSetQuestItemPosi();
	int CheckCristalEventItem();
	int SendCristalEventItem();
	int CheckWatermelonEventItem();
	int SendWatermelonEventItem();
	int CheckItemCount(DWORD CODE);
	int CheckValentineEventItem();
	int SendValentineEventItem();
	int CheckValentineItemCount(DWORD CODE);
	int CheckPristonAlphabetEventItem();
	int SendPristonAlphabetEventItem();
	int CheckCandydaysEventItem();
	int SendCandydaysEventItem();
	int CheckCandyItemCount(DWORD CODE);
	int CheckMagicalGreenEventItem();
	int SendMagicalGreenEventItem();
	int SendMagicalGreenEmeraldEventItem();
	int CheckMagicalGreenItemCount(DWORD CODE);
	int CheckMagicalGreenItemEmeraldCount(DWORD CODE);
	int CheckTearOfKaraEventItem();
	int SendTearOfKaraEventItem();
	int CheckTearOfKaraItemCount(DWORD CODE);
	int UseSoccerBallPotionItem(ItemData *pItem);
	int CheckFindinvestigatorEventItem();
	int CheckFindinvestigatorKamiuEventItem();
	int CheckFindinvestigatorEtoEventItem();
	int SendFindinvestigatorNineEventItem();
	int SendFindinvestigatorTaleEventItem();
	int SendFindinvestigatorTaleEtoEventItem();
	int CheckFindinvestigatorNineItemCount(DWORD CODE);
	int CheckFindinvestigatorTaleItemCount(DWORD CODE);
	int DeleteCoupleRing();
	int SetDelayTime(int Time,int Kind);

	char szDoc[128];
	char szSendDoc[128];
};

extern cINVENTORY	cInvenTory;

extern sINVENTORY sInven[INVENTORY_MAX_POS];

extern DWORD sinInvenColor[7];

extern ItemData *pUsePotion; //����� ������ ������ 

extern int sinLoadOK; //�ε� �Ϸ�� ���� ���� 

extern int LbuttonUpCheckFlag;

extern int sinChangeSetFlag; //���� ���� ü���� �÷� 

extern int SelectInvenItemIndex;

extern int CrashItemIndex[2];

extern int 	AutoSetItemIndex;

extern int SelectPotionIndex;

extern int ArrowState[2];

extern int InvenArrowPosi;

extern int sinButtonFlag;

extern sINVENTORY_EFFECT	sInven_Effect[MAX_INVEN_PARTICLE];

extern int ArrowState[2];

extern int InvenArrowPosi;

extern int sinUndeadAbsorb;

extern float   sinAdd_fMagic_Mastery;
extern int	   sinInterHeight2;

extern sELEMENT_ATTACK	sElement_Attack;
extern int sinTempDamage2[2];
extern int sinTempAbsorb;
extern int sinTempBlock;
///////////�ӽ� Extern ���߿� �����
extern int SendCheckItemToServer(Item *lpItem);

extern Item TempLinkCoreItem;

extern POINT UnionCorePosi;

extern sWINGQUEST sWingQuest[MAX_WINGQUEST];
extern int   sinOverWeightCnt;

extern int SpecialItemShowFlag;
extern ItemData MyShopMouseItem;
extern int sinMyShopItemPass;
extern int NotChangeSetItemFlag;
extern int MatInterEffectAging[5];
extern int MatInterEffectAging2[4];
extern int MatSuccessEffectAging;
extern int ForceOrbUseTime[];
extern int ForceOrbDamage[];
extern int ForceOrbUseLevel[][2];

extern int BoosterItem_UseTime[]; // ����� - �ν��� ������(�����, ���, �ٷ�) 
extern int BoosterItem_DataPercent[]; // ����� - �ν��� ������(�����, ���, �ٷ�) ���� �ۼ�Ʈ

extern int nSkillDelay_UseTime[]; // �庰 - ��ų ������

// �庰 - �Է�â
extern int nName;

//�ϰ����� ����
extern DWORD CristalEventCODE[12];

//����� - ���� ��ƿ���
extern DWORD WatermelonEventCODE;

//�庰 - �߷�Ÿ�� ���ݸ� ��ƿ���
extern DWORD ValentineEventCODE;

// ����� - ���ĺ� ���� �̺�Ʈ
extern DWORD PristonAlphabetEventCODE[7];

// �庰 - ĵ������ ĵ�� ��ƿ���
extern DWORD CandydaysEventCODE;

// �庰 - �����ñ׸�
extern DWORD MagicalGreenEventCODE[2];

// �庰 - ī���� ���� ��ƿ���
extern DWORD TeatOfKaraEventCODE;

// �庰 - ������� ã�ƶ� 
extern DWORD FindinvestigatorEventCODE[2];

//������ ������ 
extern DWORD dwCastlItemCODE[];
extern DWORD dwPremiumItemCode[];

// ����� - �ν��� ������
extern DWORD dwBoosterItemCode[];

// �庰 - ��ų ������
extern DWORD dwSkillDelayItemCode[];
