/*----------------------------------------------------------------------------*
*	���ϸ� :  sinShop.h	
*	�ϴ��� :  ������ �����Ѵ� 
*	�ۼ��� :  ����������Ʈ 12��
*	������ :  �ڻ� 
*-----------------------------------------------------------------------------*/	

#define     MAX_SHOP_CLASS_ITEM	30  //�� Ŭ������ 30��

#define     SHOP_ROW			9  //�ӽ� ���� ������ ���� 
#define     SHOP_COL			9
	
#define 	SINALLREPAIR		1 
#define 	SINREPAIR			2    
#define 	SINSELL				3      
#define 	SINBUY				4       
#define 	SINRIGHTARROW		5
#define 	SINLEFTARROW		6  
#define     SINSHOPEXIT			7

#define 	SIN_WEAPON			1 
#define 	SIN_DEFENSE			2 
#define 	SIN_ETC				3 


struct	sMYSHOP_ITEM
{
	Item	sItem;
	int			Price;
	short       Posi[2];
	DWORD		dwTemp[3];
};

struct sMYSHOP
{
	DWORD			CHAR_CODE;
	DWORD			dwTemp[6];
	sMYSHOP_ITEM	sMyShopItem[30];
};

struct sMYSHOP_ITEM_SERVER
{
	DWORD CODE;
	DWORD CkSum;
	DWORD Head;
	DWORD sTime;
	DWORD Price;
	DWORD SendFlag;
	DWORD Buyer;

	DWORD Temp[4];

};

class cSHOP
{

public:

	int OpenFlag;
	int UseItemFlag;

	int PosX;
	int PosY;

	int MatShop[10];

	int SelectShop;

	int ShopIconPosi;

	ItemData ShowShopItem[30];
	ItemData ShopItem[60];
	
	int RevWeaponCnt;
	int RevDefenseCnt;
	int RevEtcCnt;
	int MatMyShop_Button;
	
	smTEXTUREHANDLE *lpGoldEdit;

	smTEXTUREHANDLE *lpAllRepair;
	smTEXTUREHANDLE *lpRepair;

	smTEXTUREHANDLE *lpSell;
	smTEXTUREHANDLE *lpBuy;

	smTEXTUREHANDLE *lpAllRepair_D;
	smTEXTUREHANDLE *lpRepair_D;

	smTEXTUREHANDLE *lpSell_D;
	smTEXTUREHANDLE *lpBuy_D;

	smTEXTUREHANDLE *lpArrow[4];

	smTEXTUREHANDLE *lpTabAttack;
	smTEXTUREHANDLE *lpTabDefense;
	smTEXTUREHANDLE *lpTabEtc;

	smTEXTUREHANDLE *lpTabAttack_D;
	smTEXTUREHANDLE *lpTabDefense_D;
	smTEXTUREHANDLE *lpTabEtc_D;

	smTEXTUREHANDLE *lpExit;
	smTEXTUREHANDLE *lpGrid;

	smTEXTUREHANDLE *lpRepairAllInfo;
	smTEXTUREHANDLE *lpRepairInfo;
	smTEXTUREHANDLE *lpDefaultRepairAll;
	smTEXTUREHANDLE *lpDefaultRepair;

	smTEXTUREHANDLE *lpSellInfo;
	smTEXTUREHANDLE *lpBuyInfo;

	smTEXTUREHANDLE *lpTitle_Attack;
	smTEXTUREHANDLE *lpTitle_Etc;
	smTEXTUREHANDLE *lpTitle_Trade;
	smTEXTUREHANDLE *lpTitle_WareHouse;

	smTEXTUREHANDLE *lpWeightEdit;

	smTEXTUREHANDLE *lpNoUseBox;

	smTEXTUREHANDLE *lpCraftItemMain;
	smTEXTUREHANDLE *lpCraftItemButton;
	smTEXTUREHANDLE *lpCraftItemButtonInfo;
	smTEXTUREHANDLE *lpTitle_CraftItem;

	smTEXTUREHANDLE *lpSmeltingItemMain;
	smTEXTUREHANDLE *lpTitle_SmeltingItem;
	smTEXTUREHANDLE *lpSmeltingItemButtonInfo;

	smTEXTUREHANDLE *lpManufactureItemMain;
	smTEXTUREHANDLE *lpTitle_ManufactureItem;
	smTEXTUREHANDLE *lpManufactureItemButtonInfo;

	smTEXTUREHANDLE *lpMResetTitle;
	smTEXTUREHANDLE *lpMResetMain;
	smTEXTUREHANDLE *lpMResetButton;
	smTEXTUREHANDLE *lpMResetButtonInfo;

	smTEXTUREHANDLE *lpElementTitle;
	smTEXTUREHANDLE *lpElementMain;
	smTEXTUREHANDLE *lpElementButton;
	smTEXTUREHANDLE *lpElementButtonInfo;

	smTEXTUREHANDLE *lpSocketTitle;
	smTEXTUREHANDLE *lpSocketMain;
	smTEXTUREHANDLE *lpSocketButton;
	smTEXTUREHANDLE *lpSocketButtonInfo;

	smTEXTUREHANDLE *lpCaravanMain[7];
	smTEXTUREHANDLE *lpCaravanStart[2];
	smTEXTUREHANDLE *lpCaravanStop[2];
	smTEXTUREHANDLE *lpCaravanRename[2];
	
	smTEXTUREHANDLE *lpTitle_Aging;
	smTEXTUREHANDLE *lpAging_Info;
	
	smTEXTUREHANDLE *lpShopMain;
	smTEXTUREHANDLE *lpShopMain2;

	smTEXTUREHANDLE *lpMyShopExp;
	smTEXTUREHANDLE *lpMyShopExp_;
	smTEXTUREHANDLE *lpMyShopExp_T;
	smTEXTUREHANDLE *lpMyShopNoSale;
	smTEXTUREHANDLE *lpMyShopNoSale_;
	smTEXTUREHANDLE *lpMyShopNoSale_T;
	smTEXTUREHANDLE *lpMyShopSale;
	smTEXTUREHANDLE *lpMyShopSale_;
	smTEXTUREHANDLE *lpMyShopSale_T;
	smTEXTUREHANDLE *lpTitle_MyShop;
	smTEXTUREHANDLE *lpImage_MyShop;
	smTEXTUREHANDLE *lpMyShop_T;
	
public:
	cSHOP();
	~cSHOP();

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

	void CheckShopNpcState();

	void CopyShopItemToShow(int Index,int Kind=0);
	int GetShopItemXY(ItemData *pItem);
	void DrawShopText();
	int RecvBuyItemToServer(ItemData *pItem ,int ItemCount=1);
	int SellItemToShop(ItemData *pItem,int ItemCount=1);
	int SendBuyItemToServer(ItemData *pItem , int ItemCount=1 );
	void DeleteShopItem();
	int CheckHighRankItem(ItemData *pItem);
	int haBuyMoneyCheck(int BuyMoney);
	int haShopItemPrice(int Money);
};

class cMYSHOP
{
public:
	int OpenFlag;	
	ItemData MyShopItem[30];

	char szDoc[128];
	char szSendDoc[128];

public:
	
	//���ó��۵���Ʒ
	int SetMyShopItem(ItemData *pItem,int Kind = 0);

	//�����Ѵ�
	int LastSetMyShopItem(ItemData *pItem);

	//�κ��������� ����Ѵ�
	int SetShopItemToInven(ItemData *pItem);

	//������ ����� �������� ã�´�
	int SearchShopItemToInven(ItemData *pItem);

	//�������� ������ ������ 
	int SendMyShopItem(); 

	//�������� ���ſ�û�� ���� �������� �޴´�
	int RecvMyShopItem( DWORD dwCharCode , sMYSHOP_ITEM_SERVER *lpShopItem );

	//�ڽ��� ������ �ִ� �ݾ��� �����Ѵ�
	int GetLimitMoney(int Money);

	//������ ���ȸ��� ������ �ݴ´�
	int AutoCloseShop();

	//���λ����� ���� ���ؿ´�
	int GetTotalMyShopItemMoney();

};
/*----------------------------------------------------------------------------*
*								���λ��� Ŭ���� 
*-----------------------------------------------------------------------------*/
class cCHARSHOP{
public:
	int OpenFlag;	

public:
	ItemData CharShopItem[30];
	
	//�������� �޴´�
	int RecvShopItem(sMYSHOP *sMyShop);

	//���� �������� ã�´�
	int SearchMyShopItem(DWORD CODE ,DWORD Head , DWORD CheckSum);

	//���λ��������� �������� �κ��丮�� �����Ѵ�
	int SetCharShopItemToInven(Item *pItem_Info);

	//���λ������� �������� ���
	int BuyItem(int Index);

};

extern cSHOP cShop;

extern int sinShopKind;  //���� ������ ����  1  ���� 2 ��� 3 ���� (defalt �� ����)

extern int TalkNpcState; //���� ���� NPC�� �Բ� ������� 

extern int ShopGoldEdit[2][4];

extern int ShopArrowPosi; //���� ȭ��ǥ ���� 

extern int BuyItemServerFlag; //�������� ������ �춧 �޼����� ���������� ������� 

extern cMYSHOP cMyShop;
extern cCHARSHOP cCharShop;

extern sMYSHOP     sMyShop;       //������ MyShop ����ü
extern sMYSHOP     sRecvMyShop;   //�޴� MyShop ����ü
extern int MyShopSendButton;

extern int MyShopExpBox;
extern int MyShopItemSellMoney2;
extern sMYSHOP_ITEM_SERVER sMyShop_Server;
extern Item MyShopPotion;
extern int MyShopItemCancelIndex[2];
