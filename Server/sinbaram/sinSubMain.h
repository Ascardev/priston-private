/*----------------------------------------------------------------------------*
*	파일명 :  sinSubMain.h	
*	하는일 :  각종 함수들을 관리한다 
*	작성일 :  최종업데이트 12월
*	적성자 :  박상열 
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


///////////에이징 클래스 
#define SIN_AGING_ATTACK			100
#define SIN_AGING_CRITICAL			101
#define SIN_AGING_BLOCK				102
#define SIN_AGING_DEFENSE_ORB		103		// 박재원 - 에이징 마스터(방어구 오브 비즈 숙성시킬때)
#define SIN_AGING_DEFENSE_ARMOR		104		// 박재원 - 에이징 마스터(방어구 갑옷 로브 숙성시킬때) 
#define SIN_AGING_DEFENSE_BOOTS		105		// 박재원 - 에이징 아이템 추가(부츠)
#define SIN_AGING_DEFENSE_GLOVES	106		// 박재원 - 에이징 아이템 추가(장갑)
#define SIN_AGING_DEFENSE_ARMLETS	107		// 박재원 - 에이징 아이템 추가(암릿)

/////////// IP별 특화 제도 
#define PRORATE_USER		1
#define FREE_USER			2
#define VIP_USER			4
#define BIRTHDAY_USER		8



#define SIN_WINGRESULT_CRISTAL		0x101
 

/*각종 공식을 계산후 값을 리턴한다 */

int sinGetAccuracy(int desLV , int desDefense); //내 명중률 

int sinGetMonsterAccuracy(int MonsterLV , int MonsterAttack_Rating); //몬스터 명중률  

int sinGetPVPAccuracy(int MyLevel , int MyAttack_Rating , int DesLevel , int DesDefense);//몬스터 VS 몬스터 명중률

int sinGetCritical(int desLV);//실제 크리티컬 

int sinGetBlockRating(int desLV);//블럭율   

 
extern int ChangeJobButonCheck2; //버튼다운을 한번 거너뛰는 플랙(이것두 역시 땡빵이다 씨바!!)


int sinSetAgingItemIncreState(Item *pItem);
int sinAgingItemInit(Item *pItem);

//에이징 능력 증가 
int sinSetDurabilityAging(Item *pItem); // 내구력을 계산한다
int sinSetDamageAging(Item *pItem);
int sinSetDefenseAging(Item *pItem , int Percent,int Type);
int sinSetAttackRateAging(Item *pItem , int AddNum);
int sinSetAbsorbAging(Item *pItem , float Percent);
int sinSetCriticalAging(Item *pItem);
int sinSetBlockRateAging(Item *pItem);


//에이징 능력 다운
int sinDownDurabilityAging(Item *pItem);
int sinDownDamageAging(Item *pItem);
int sinDownDefenseAging(Item *pItem , int Percent);
int sinDownAttackRateAging(Item *pItem , int AddNum);
int sinDownAbsorbAging(Item *pItem , float Percent);
int sinDownCriticalAging(Item *pItem);
int sinDownBlockRateAging(Item *pItem);


//에이징 아이템에 대한 해킹을 막는다 
int sinCheckAgingItemHack(ItemData *pItem);


//WingItem 퀘스트
DWORD sinWingItemQuestServer(sCRAFTITEM_SERVER *pWingItem , CharacterData *pChar_Info);

int GetRace(int Class);
int GetSex(int Class);
/*----------------------------------------------------------------------------*
*							외부 extern 함수 
*-----------------------------------------------------------------------------*/	

extern int ReformItem(Item *lpItemInfo ); //아이템 인증받기 
extern int CheckItemForm(Item *lpItemInfo ); //아이템 인증확인 

extern int CompareItems(Item *lpItemInfo1 , Item *lpItemInfo2 );//아이템 2개를 비교한다



/*----------------------------------------------------------------------------*
*							  extern 변수  
*-----------------------------------------------------------------------------*/	

extern int sinTestFlag;      //테스트시 사용될 플랙 
extern int MouseButtonUpEvent;

extern int CursorClass; //커서종류 (default로 1을 준다  아이템을 집을 때 CursorClass = 0으로준다 )

extern int Accuracy_Table[][2]; //명중률 테이블을 익스턴한다 

extern int sinSecretFlag;  //암호 플랙 


extern int ItemIndex1[3];
extern int ItemIndex2[3];

extern int ItemImageNotExitFlag;

extern int OverDay_Item_Flag;

extern int haSiegeBoardTempFlag;

#endif
