#ifndef	_SINITEM_HEADER_

#define _SINITEM_HEADER_

#define MAX_ITEM					1382	
			
#define ITEMSIZE					22

#define CHECK_COPY_ITEM				1
#define CHECK_GIVE_ITEM				2

#define ITEM_WEAPONCLASS_NOT_SHOOTING	1
#define ITEM_WEAPONCLASS_SHOOTING		2
#define ITEM_WEAPONCLASS_CASTING		3


#define sinWA1			0x01010000
#define sinWC1			0x01020000
#define sinWH1			0x01030000
#define sinWM1			0x01040000
#define sinWP1			0x01050000
#define sinWS1			0x01060000
#define sinWS2			0x01070000
#define sinWT1			0x01080000
#define sinWD1			0x01090000
#define sinWN1			0x010A0000
#define sinTW1			0x010B0000

/*---------------------------------------------*
*			(방어구)1차 카테고리 					    
*----------------------------------------------*/

#define sinDA1			0x02010000	//Armor
#define sinDB1			0x02020000	//Boots
#define sinDG1			0x02030000	//Gloves
#define sinDS1			0x02040000	//Shields
#define sinDA2			0x02050000	//Armor
#define sinCA1			0x02060000  //景喝廛솖
#define sinCW1			0x02070000	//녁곪


/*---------------------------------------------*
*			(장신구류)1차 카테고리 					    
*----------------------------------------------*/

#define sinOA1			0x03010000	//Amulet
#define sinOA2			0x03020000	//Armlet
#define sinOM1			0x03030000	//Magicial Stuffs
#define sinOR1			0x03040000	//Ring
#define sinOR2			0x03050000	//Ring2
#define sinOS1			0x02350000	//Sheltom
#define sinFO1			0x03060000  //Force Orb
#define sinSE1			0x03070000  //Seel
#define sinPR1			0x03080000  // 광석 pluto
#define sinPR2			0x03090000  // 수정 pluto
#define sinPR3			0x03100000  // 룬(A) pluto
#define sinPR4			0x03110000  // 룬(B) pluto
/*---------------------------------------------*
*			(물약)1차 카테고리 					    
*----------------------------------------------*/
#define sinPM1			0x04010000  //Mana
#define sinPL1			0x04020000  //Life
#define sinPS1			0x04030000  //Stamina

/*---------------------------------------------*
*			(돈)1차 카테고리 					    
*----------------------------------------------*/
#define sinGG1			0x05010000 //Gold
#define sinBS1			0x05020000 //벨라토스톤

/*---------------------------------------------*
*			(귀환)1차 카테고리 					    
*----------------------------------------------*/
#define sinEC1			0x06010000

/*---------------------------------------------*
*			  퀘스트 아이템 
*----------------------------------------------*/

#define sinQT1			0x07010000


/*---------------------------------------------*
*			  이벤트 아이템 
*----------------------------------------------*/
#define sinSP1			0x08010000 
#define sinGP1			0x08020000		//0x09010000 으로하니 문제이네 그려.. (& sinITEM_MASK2 가 안먹음)
#define sinQW1			0x08030000		//워프게이트 윙
#define sinGF1			0x08040000		//별상품권
#define sinPZ1			0x08060000		//아처 퍼즐
#define sinPZ2			0x08070000		//킹호피 퍼즐
#define sinCH1			0x08080000		//발렌타인데이 초콜렛
#define sinSD2			0x08090000		//Sod2 발생 아이템
#define sinBC1          0x080A0000      //공성전 발생 아이템
#define sinBI1          0x080B0000      //유료구매 아이템  
#define sinBI2          0x080C0000      //유료구매 아이템(패키지 캐쉬 아이템 )  
#define sinGP2			0x080D0000		// 장별 - 소울스톤


#define sinMA1			0x09010000 
#define sinMA2			0x09020000

#define sinSS1			0x09030000
#define sinES1			0x09040000
#define sinSR1			0x09050000
#define sinSR2			0x09060000


#define sinWR1			0x0A010000
#define sinDR1			0x0A020000

#define EXTREME_RECIPE		1		// 잊혀진 레시피
#define ANCIENT_RECIPE		2		// 고대의 레시피
#define	MINOTAUR_RECIPE		3		// 대지의 레시피
#define DOOM_RECIPE			4		// 어둠의 레시피
#define SALAMANDER_RECIPE	5		// 화명의 레시피
#define WYVERN_RECIPE		6		// 바람의 레시피
#define PHOENIX_RECIPE		7		// 태양의 레시피
#define FRENZY_RECIPE		8		// 광포한 레시피
#define HEAVENS_RECIPE		9		// 천상의 레시피 
#define SNOW_RECIPE			10		// 포설의 레시피
#define MEMORY_RECIPE		11		// 기억의 레시피 // 장별 - 대장장이의 혼


#define sin00			0x00000000	
#define sin01			0x00000100	
#define sin02			0x00000200
#define sin03			0x00000300
#define sin04			0x00000400
#define sin05			0x00000500
#define sin06			0x00000600
#define sin07			0x00000700
#define sin08			0x00000800
#define sin09			0x00000900
#define sin10			0x00000A00
#define sin11			0x00000B00
#define sin12			0x00000C00
#define sin13			0x00000D00
#define sin14			0x00000E00
#define sin15			0x00000F00
#define sin16			0x00001000
#define sin17			0x00001100
#define sin18			0x00001200
#define sin19			0x00001300
#define sin20			0x00001400
#define sin21			0x00001500
#define sin22			0x00001600
#define sin23			0x00001700
#define sin24			0x00001800
#define sin25			0x00001900
#define sin26			0x00002A00
#define sin27			0x00002B00
#define sin28			0x00002C00
#define sin29			0x00002D00
#define sin30			0x00002E00
#define sin31			0x00002F00
#define sin32			0x00003000
#define sin33			0x00003100
#define sin34			0x00003200
#define sin35			0x00003300
#define sin36			0x00003400
#define sin37			0x00003500
#define sin38			0x00003600
#define sin39			0x00003700
#define sin40			0x00003800
#define sin41			0x00003900
#define sin42			0x00003A00
#define sin43			0x00003B00
#define sin44			0x00003C00
#define sin45			0x00003D00
#define sin46			0x00003E00
#define sin47			0x00003F00
#define sin48			0x00004000
#define sin49			0x00004100
#define sin50			0x00004200
#define sin51			0x00004300
#define sin52			0x00004400
#define sin53			0x00004500
#define sin54			0x00004600
#define sin55			0x00004700
#define sin56			0x00004800
#define sin57			0x00004900
#define sin58			0x00004A00
#define sin59			0x00004B00
#define sin60			0x00004C00
#define sin61			0x00004D00
#define sin62			0x00004E00
#define sin63			0x00004F00
#define sin64			0x00005000
#define sin65			0x00005100
#define sin66			0x00005200
#define sin67			0x00005300
#define sin68			0x00005400
#define sin69			0x00005500
#define sin70			0x00005600
#define sin71			0x00005700
#define sin72			0x00005800
#define sin73			0x00005900 
#define sin74			0x00005A00 
#define sin75			0x00005B00 
#define sin76			0x00005C00 
#define sin77			0x00005D00 
#define sin78			0x00005E00 
#define sin79			0x00005F00 
#define sin80			0x00006000 
#define sin81			0x00006100
#define sin82			0x00006200
#define sin83			0x00006300
#define sin84			0x00006400
#define sin85			0x00006500
#define sin86			0x00006600 
#define sin87			0x00006700 
#define sin88			0x00006800 
#define sin89			0x00006900 
#define sin90			0x00006A00 
#define sin91			0x00006B00 
#define sin92			0x00006C00 
#define sin93			0x00006D00 
#define sin94			0x00006E00 
#define sin95			0x00006F00 
#define sin96			0x00007000 
#define sin97			0x00007100 
#define sin98			0x00007200
#define sin99			0x00007300

#define		SIN_SOUND_AXES				1
#define		SIN_SOUND_CLAWS				2
#define		SIN_SOUND_HAMMER			3
#define		SIN_SOUND_MAGICIAL		 	4
#define		SIN_SOUND_POLES				5
#define		SIN_SOUND_SHOOTERS			6
#define		SIN_SOUND_SWORDS			7
#define		SIN_SOUND_DAGGER			7
#define		SIN_SOUND_THROWING			8
#define		SIN_SOUND_ARMOR				9
#define		SIN_SOUND_BOOTS				10
#define		SIN_SOUND_GLOVES			11
#define		SIN_SOUND_SHIELDS			12
#define		SIN_SOUND_AMULET			13
#define		SIN_SOUND_Armlet			14
#define		SIN_SOUND_RING				15
#define     SIN_SOUND_SHELTOM			16
#define     SIN_SOUND_POTION			17
#define     SIN_SOUND_COIN				18
#define     SIN_SOUND_STAFF				19
#define		SIN_SOUND_EAT_POTION		20
#define		SIN_SOUND_SHOW_INTER		21
#define		SIN_SOUND_REPAIR_ITEM		22
#define		SIN_SOUND_FAILD_MIXITEM		23
#define		SIN_SOUND_ARMOR2			24
#define		SIN_SOUND_EAT_POTION2		25


#define	sITEMINFO_BIONIC		0
#define	sITEMINFO_EARTH			1
#define sITEMINFO_FIRE			2
#define	sITEMINFO_ICE			3
#define sITEMINFO_LIGHTING		4
#define sITEMINFO_POISON		5
#define sITEMINFO_WATER			6
#define sITEMINFO_WIND			7
#define	sITEMINFO_NONE			8

//페儉묑샌橄昑
#define sITEMINFO_STUN			9	//杞仝
#define sITEMINFO_SPEED			10	//숑醵
#define sITEMINFO_MOVESPEED		11  //鍵鬼


#define   SIN_ADD_FIRE				0x00000001
#define   SIN_ADD_ICE				0x00000002
#define   SIN_ADD_LIGHTNING			0x00000004
#define   SIN_ADD_POISON			0x00000008
#define   SIN_ADD_BIO				0x00000010
#define   SIN_ADD_CRITICAL			0x00000020
#define   SIN_ADD_ATTACK_RATE		0x00000040
#define   SIN_ADD_DAMAGE_MIN		0x00000080
#define   SIN_ADD_DAMAGE_MAX		0x00000100
#define   SIN_ADD_ATTACK_SPEED		0x00000200
#define   SIN_ADD_ABSORB			0x00000400
#define   SIN_ADD_DEFENCE			0x00000800
#define   SIN_ADD_BLOCK_RATE		0x00001000
#define   SIN_ADD_MOVE_SPEED		0x00002000
#define   SIN_ADD_LIFE				0x00004000
#define   SIN_ADD_MANA				0x00008000
#define   SIN_ADD_STAMINA			0x00010000
#define   SIN_ADD_LIFEREGEN			0x00020000
#define   SIN_ADD_MANAREGEN			0x00040000
#define   SIN_ADD_STAMINAREGEN		0x00080000

struct sITEMPRICE{
	int PureSellPrice;
	int SellPrice;
	int RepairCost;

};

//아이템 요구치 플랙 
struct sITEMREQUIRE{

	int     rLevel;				//레벨 
	int     rStrength;			//힘 	
	int     rSpirit;			//정신력 
	int     rTalent;			//재능 
	int     rDexterity;			//민첩성 
	int     rHealth;			//건강 

};
/*----------------------------------------------------------------------------*
*						    class   아이템
*-----------------------------------------------------------------------------*/
class cITEM
{	

public:

	char *DropItemPath;
	char *CharSetItemPath;

	int MatItemInfoBox;

	int MatItemInfoBox_TopLeft;
	int MatItemInfoBox_TopRight;
	int MatItemInfoBox_TopCenter;

	int MatItemInfoBox_BottomLeft;
	int MatItemInfoBox_BottomRight;
	int MatItemInfoBox_BottomCenter;

	int MatItemInfoBox_Left;
	int MatItemInfoBox_Right;
	int MatItemInfoBox_Center;


	smTEXTUREHANDLE	*AgingBar;
	smTEXTUREHANDLE	*AgingGage;
	smTEXTUREHANDLE	*AgingBar2;

public:
	cITEM();
	~cITEM();

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
	int ShowItemInfo(ItemData *pItem , int Flag,int Index=0);
	int ShowItemInfo2(ItemData *pItem ,int Flag,int Index=0);
	int DrawItemText();
	POINT SetTextXY(int x , int y, int len);
	int SearchSpecialItemJob(DWORD SpecialJob_CODE);
	int GetInfoBoxSize(ItemData *pItem ,int Col);
	int CheckItemTable();
	int GetItemLimitTime(ItemData *pItem);
	void GetMousePos(int *MouseX , int *MouseY);
	void SetItemInfo(char *Buff);
};

extern cITEM cItem;	 
//extern ItemData sItem[MAX_ITEM];

extern ItemData TempItem;
extern ItemData MouseItem;

extern int sinShowItemInfoFlag;
extern DWORD sinItemTime;

extern int NotSell_Item_CODECnt;
extern int NotSell_Item_MASKCnt;
extern int NotSell_Item_KINDCnt;

extern int NotDrow_Item_CODECnt;
extern int NotDrow_Item_MASKCnt;
extern int NotDrow_Item_KINDCnt;

extern int NotSet_Item_CODECnt;
extern int NotSet_Item_MASKCnt;
extern int NotSet_Item_KINDCnt;

extern DWORD NotSell_Item_CODE[];
extern DWORD NotSell_Item_MASK[];
extern DWORD NotSell_Item_KIND[];

extern DWORD NotDrow_Item_CODE[];
extern DWORD NotDrow_Item_MASK[];
extern DWORD NotDrow_Item_KIND[];

extern DWORD NotSet_Item_CODE[];
extern DWORD NotSet_Item_MASK[];
extern DWORD NotSet_Item_KIND[];


#endif