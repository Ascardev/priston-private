#pragma once

namespace nsPremiumItem
{
	enum _Item
	{
		THIRD_EYES			= 1,
		EXPUP_POTION		= 2,
		VAMPIRIC_CUS		= 3,
		MANA_RECHAR_P		= 4,
		MIGHT_OF_AWELL		= 5,
		MANA_REDUCE_P		= 6,
		HELP_PET_TERRY		= 7,
		HELP_PET_NEPSYS		= 8,
		HELP_PET_IO			= 9,
		HELP_PET_MUTE		= 10,
		STM_RECHAR_P		= 11,
		STAMINA_REDUCE_P	= 12,
		VIP_INFO			= 13,
		CARAVAN_HOPY		= 14,
		BIG_HEAD			= 15,
		BIG_GIRAFFEHAT		= 16,
		BIG_MAGICIANHAT		= 17,
		BIG_WITCHHAT		= 18,
		BIG_MASKEDMAN		= 19,
		BIG_MASKEDWOMAN		= 20,
		BIG_PUMPKINHAT		= 21,
		BIG_SHEEPHAT		= 22,
		BIG_SOCCERHAT		= 23,
		BIG_GREENXMASHAT	= 24,
		BIG_REDXMASHAT		= 25,
		PHONEIX_FIRE		= 26,
		PHONEIX_ICE			= 27,
		PHONEIX_LIGHTNING	= 28,
		PHONEIX_HEAL		= 29,
		BIG_EASTER			= 30,
		CARAVAN_ARMA		= 31,
		CARAVAN_BUMA		= 32,
		CARAVAN_CUEPY		= 33,
		CARAVAN_HUNGKY		= 34,
		CARAVAN_RABIE		= 35,
		CARAVAN_TOBIE		= 36,
		BIG_BIRTHDAY		= 37,
		BIG_BLUEXMASHAT		= 38,
		CARAVAN_RUDOLF		= 39,
	};
}
using namespace nsPremiumItem;

#define		SINUPKEEPITEM_MAX       39

const DWORD SINITEM_TIME_5MINUTE    = (15*60*1);	   //10分钟
const DWORD SINITEM_TIME_10MINUTE   = (30*60*1);	   //30分钟
const DWORD SINITEM_TIME_3HOURS		= (3*60*60*1); 	   //3小时
const DWORD SINITEM_TIME_ONEDAY     = (24*60*60*1);    //1天
const DWORD SINITEM_TIME_SEVENDAY   = (7*24*60*60*1);  //7天
const DWORD SINITEM_TIME_30DAY		= (30*24*60*60*1); //30天
const DWORD SINITEM_TIME_1HOURS		= (1*60*60*1);	   //1小时

struct sTelePortCore
{
	short   FieldIndex[2];
	bool    PageButtonFlag[2]; 
	short   PageIndex;
	short   ItemIndex;
	char    FieldName[64]; 
};

struct sUpKeepItem
{
	int     TGAImageNumber;
	bool    Visible;
	bool    Infoflag;
	char    Id[32];		
	int		PosiX;
	int		PosiY;
	DWORD	IconTime[2];
	short   Alpha;
	short   Alphakind;
	int		Per;
};

class cHaPremiumItem
{
public:
	smTEXTUREHANDLE	  *lpUpKeepItemBackImage[SINUPKEEPITEM_MAX];
	sTelePortCore		  TelePortCore;	
	sUpKeepItem           UpKeepItem[SINUPKEEPITEM_MAX];
	int                   Using_ItemKind;
	int                   UpKeepItemTGAImage[SINUPKEEPITEM_MAX];
	bool                  haItemUseDelayFlag;
	int					  Using_SelectInvenItemIndex;

	DWORD                 m_ThirdEyesTime;
	DWORD                 m_ExpUpPotionTime;
	DWORD                 m_VampiricCuspidTime;
	DWORD                 m_ManaRechargingPTime;
	DWORD				  m_ManaReducePotiontime;
	int					  m_ManaReducePotionValue;
	DWORD				  m_MightofAwellTime;
	int					  m_MightofAwellWeight;
	DWORD				  m_HelpPetTime;
	DWORD				  m_StmaReducePotionTime;
	DWORD				  m_StaminaReducePotiontime;
	int					  m_StaminaReducePotionValue;

	DWORD				  m_VipInfoTime;
	DWORD				  m_Caravan_HopyTime;
	DWORD				  m_BigHeadTime;
	DWORD				  m_PhenixPetTime;

	DWORD				  m_TerryTime;
  
public:
	cHaPremiumItem();
	~cHaPremiumItem();

	void init();
	void Main();
	void Draw();
	void DrawUp();
	void KeyDown();
	void LButtonDown(int x , int y);
	void LButtonUp(int x,int y);
	int  DrawText();
	
	int UsePremiumItem(int kind=0);
	int SetPremiumItemSkill(int kind=0);
	int UseTeleportScrollItem(short ItemIndex);
	int UseChangeJobItem();
	int UseFruitItem();
	int CheckWindowOpen();
	int CheckUpKeepItem();	
	void InfoBox(int PoisX,int PosiY,int Width,int Height);
	int SetUpKeepItem(int kind,DWORD dwTime,bool visible,char* id,int Percent = 0,short ItemType=0);
	int cHaPremiumItem::CheckTime(DWORD CurrentTime);		

	void SetHelpPetTimeTime(DWORD Time){ m_TerryTime = m_HelpPetTime = Time; };
	int  UseHairtintPotion(int ItemKind);
	int	UseAgingMaster(int ItemKind);
	int UseSkillMaster(int ItemKind);
	int UseMoveShop();
};
extern cHaPremiumItem  chaPremiumitem;