
#ifndef _NET_PLAY_HEADER

#define	_NET_PLAY_HEADER

extern int BellatraEffectInitFlag;

extern char	szConnServerName[16];

extern int	Version_WareHouse;
extern int	Version_CharInfo;
extern int	Version_Caravan;

extern smTRANS_COMMAND	*lpTransVirtualPotion;

extern DWORD	dwTime_ServerT;
extern DWORD	dwTime_ConnectMS;
extern DWORD	dwTime_ServerGMT;

extern int		InitClanMode;

extern DWORD	dwYahooTime;


extern DWORD	dwSkill_DivineLightning_Target[8];
extern int		DivineLightning_Target_Count;
extern int		DivineLightning_FindCount;



Unit *FindAutoPlayer( DWORD dwObjectSerial );
Unit *FindChrPlayer( DWORD dwObjectSerial );
Unit *FindDeadPartyUser();
Unit *FindNearMonster(Unit *lpCurChar );
int ClearAttMonsterCode();
int	AddAttMonsterCode( DWORD dwCode );
int	CheckAttMonsterCode( DWORD dwCode );


int RecvPlayData(SocketData * pcSocketData, Packet * psPacket);

int RecallSavedChatCommand( HWND hChatWnd , int Arrow );

DWORD EncodeParam( DWORD Param );
int ThrowPutItem(ItemData *lpItem , int x, int y , int z );
int ThrowPutItem2(Item *lpItem , int x, int y , int z );
int SendDeleteStartPoint( int x, int z );
int SendAddStartPoint( int x, int z );
int SendAdd_Npc(Unit *lpCharSample , int state );
int SendDelete_Npc(Unit *lpCharSample );
int SendGetRecordData( char *szName );

int	SendTotalExpMoney();
int CheckMaxDamage();
int	SaveGameData();
int GetSaveResult();
int	TransUserCommand ( DWORD dwCode , char *szID , char *szName );
int	Send_GetCharInfo( DWORD	dwObjectSerial , int ServerCode );
int SendAdminMode2( DWORD AdminNum );
int SendNetworkQuality( DWORD NetworkQuality );
int SendProcessInfo();
int SendSetObjectSerial( DWORD dwObjectSerial );
int SendSaveThrowItem(Item *lpItemInfo );
int SendSaveThrowItem2(Item *lpItemInfo );
int SendSaveMoney();
int SendSetHackUser( int StopGame );
int SendSetHackUser2( int Type , int LParam );
int SendSetHackUser3( int Type , int LParam , int SParam );
int SendCopyItemUser( int CopyItemCount );
int SendPlayUpdateInfo();
int SendUpdateClanInfo();
int SendRequestTrade( int dwObjectSerial , int Flag );
int SendTradeItem( DWORD dwSender );
int RecvTradeItems( TRANS_TRADEITEMS *lpTransTradeItems );
int SendTradeSucessKey( DWORD dwSender);
int SendTradeCheckItem( DWORD dwSender );
int GetTradeDistanceFromCode( DWORD dwObjectSerial );
int GetTradeDistance(Unit *lpChar );

int Skil_RangeBoxEffect(Unit *lpCurChar , RECT *lpRect , DWORD dwSkillCode , int TargetState );
int Skil_RangeEffect(Unit *lpCurChar , int Range , DWORD dwSkillCode , int TargetState , int point );


int SendJoinPartyUser( DWORD dwObjectCode );

struct sWAREHOUSE;
int	SaveWareHouse(sWAREHOUSE *lpWareHouse,TRANS_WAREHOUSE *lpTransWareHouse);
int	SaveWareHouse(sWAREHOUSE *lpWareHouse);

int	LoadWareHouse(TRANS_WAREHOUSE *lpTransWareHouse,sWAREHOUSE *lpWareHouse,int flag);
int	LoadWareHouse(TRANS_WAREHOUSE *lpTransWareHouse,sWAREHOUSE *lpWareHouse );


int SendCollectMoney( int Money );

/////////////////////// PK ////////////////////////////////////
//PK´çÇØ¼­ Á×À½
int PlayerKilling( DWORD dwObjectSerial );

struct sCARAVAN;
// ¼ÓÔØ³èÎï²Ö¿â
int LoadCaravan(TRANS_CARAVAN *lpTransCaravan,sCARAVAN *lpCaravan,int flag);
// ±£´æ³èÎï²Ö¿â
int SaveCaravan(sCARAVAN *lpCaravan,TRANS_CARAVAN *lpTransCaravan);



int DisconnectServerFull();


extern	int	ReconnDataServer;
extern	int	ReconnServer;

extern int	WarningHack;


extern int TradeSendSucessFlag;
extern DWORD	dwTradeMaskTime;
extern int	TradeItemSucessFlag;

extern	DWORD	dwLastRecvGameServerTime;
extern	DWORD	dwLastRecvGameServerTime2;
extern	DWORD	dwLastRecvGameServerTime3;
extern	DWORD	dwLastRecvGameServerTime4;



struct	PK_FIELD_STATE {
	DWORD	dwPlay_FieldTime;
	int		FieldCode;
};
extern PK_FIELD_STATE	PK_FieldState;		//Pk ÇÊµå ±¸Á¶ Á¤º¸Ã¼


//¼ö½Å ½Ã°£ ÃÊ°ú Ä³¸¯ÅÍ Á¾·á
#define DIS_TIME_OVER		30000
//¼ö½Å ½Ã°£ ÃÊ°ú Ä³¸¯ÅÍ ºñÇ¥½Ã
#define DISPLAY_TRANS_TIME_OVER		7000
#define DISPLAY_TRANS_TIME_OVER_FAR	4000

#define PLAY_SERVER_CODE_MAIN		1
#define PLAY_SERVER_CODE_USER		2
#define PLAY_SERVER_CODE_EXTEND		3
#define PLAY_SERVER_CODE_AREA1		11
#define PLAY_SERVER_CODE_AREA2		12


extern char *szNetLogFile;

extern TRANS_SKIL_ATTACKDATA	Back_TransSkilAttackData;


extern TRANS_ITEMINFO	TransRecvItem;


//°æÇèÄ¡¿Í µ· °Å·¡ ±İ¾×À» ÅäÅ»¿¡ ±â·ÏÇÑ´Ù
int	SetTotalAddMoney( int Money );
int	SetTotalSubMoney( int Money );
int	SetTotalAddExp( int Exp );
int	SetTotalSubExp( int Exp );
int GetTotalExp();
int	GetTotalMoney();
int GetTotalSubExp();


// pluto Á¦·Ã µ¥ÀÌÅ¸¸¦ ¼­¹ö·Î º¸³¿
int SendSmeltingItemToServer( void *lpsSmeltingItem_Send);
// pluto Á¦ÀÛ µ¥ÀÌÅ¸¸¦ ¼­¹ö·Î º¸³¿
int SendManufactureItemToServer( void *lpsManufactureItem_Send);
// ¼®Áö¿ë - ¹Í½ºÃÄ ¸®¼Â ¾ÆÀÌÅÛÀ» ¼­¹ö·Î Àü¼ÛÇÑ´Ù.
int SendMixtureResetItemToServer( void *lpsMixtureResetItem_Send);

//·¢ËÍºÏ³ÉÎïÆ·µ½·şÎñÆ÷Ğ­Òé
int SendCraftItemToServer(void *lpsCraftItem_Send);
// ·¢ËÍ¶ÍÔìÎïÆ·µ½·şÎñÆ÷
int SendAgingItemToServer( void *lpsCraftItem_Send );
// ·¢ËÍÊôĞÔÎïÆ·µ½·şÎñÆ÷
int SendElementItemToServer(void *lpsItem_Send);

// ·¢ËÍ´ò¿×ÎïÆ·µ½·şÎñÆ÷¶Ë
int SendSocketItemToServer(void *lpsItem_Send);
// ·¢ËÍHOPYÊÇ·ñ×ß¶¯·¢ËÍµ½·şÎñÆ÷
int SendSelectHopyToServer(int Kind);
//¿¡ÀÌÂ¡ ¿Ï·áµÈ ¾ÆÀÌÅÛÀ» ¼­¹ö·Î º¸³¿
int SendAgingUpgradeItemToServer(Item *lpItem );
//¸µÅ©ÄÚ¾î µî·Ï º¸³¿
int SendLinkCoreToServer(Item *lpItem );
//À§ÇÁ¿ë À® ¾ÆÀÌÅÛ µ¥ÀÌÅ¸¸¦ ¼­¹ö·Î º¸³¿
int SendWingItemToServer( void *lpsCraftItem_Send );

//ÆÇ¸ÅÇÒ ¾ÆÀÌÅÛÀ» ¼­¹ö·Î º¸³¿
int	SellItemToServer(Item *lpItem , int Count );

extern DWORD	dwLastCheckItemTime;
//¾ÆÀÌÅÛÀ» ¼­¹ö¿¡ º¸³»¼­ È®ÀÎ
int	SendCheckItemToServer(Item *lpItem );
//ÀÎº¥Åä¸®ÀÇ ÀåÂøµÈ ¾ÆÀÌÅÛÀ» ¼­¹ö·Î º¸³»¼­ °Ë»ç
int CheckInvenItemToServer();

//¼­¹ö¿¡¼­ ¸Ş¸ğ¸® °ªÀ» Á¤ÇØ¼­ °¡Á®°£´Ù
DWORD funcCheckMemSum( DWORD FuncPoint , int count );

//ÀÓ½ÃÀúÀåµÈ ¾ÆÀÌÅÛ Å¥¿¡ ¾ÆÀÌÅÛ ´ë±âÁßÀÎÁö °Ë»ç
int CheckRecvTrnsItemQue();
//»ç¿ëÇÑ ¾ÆÀÌÅÛ ÄÚµå ¼­¹ö·Î º¸³¿
int SendUseItemCodeToServer(Item *lpItem );

//ÁÖº¯ Ä³¸¯ÅÍ¿¡ ÀÌº¥Æ® ¸í·É ÄÚµå º¸³»±â
int	SendCommandUser( int wParam , int lParam , int sParam , int eParam );
//ÁÖº¯ Ä³¸¯ÅÍ¿ë ÀÌº¥Æ® ¸í·É ÄÚµå
int RecvCommandUser( smTRANS_COMMAND_EX *lpTransCommandEx );

//Áö¿ª¼­¹ö¿¡ ¸í·É ÄÚµå Àü¼Û
int	SendCommand_AreaServer( DWORD dwCode , int wParam , int lParam , int sParam , int eParam );
//µ¥ÀÌÅ¸¼­¹ö¿¡ ¸í·É ÄÚµå Àü¼Û
int	SendCommand_DataServer( DWORD dwCode , int wParam , int lParam , int sParam , int eParam );

//°ø°İ·Â ±â·Ï Æ÷±âÈ­
int	Init_RecordDamage();
int	Record_RecvDamage(SocketData * pcSocketData, int Damage );

//ÆÄÆ¼¿ø¿¡°Ô ½ºÅ³ »ç¿ë Á¤º¸ º¸³»±â
int	SendPartySkillToServer( DWORD dwSkillCode , int SkillLevel , int Around , int wParam , int lParam , int sParam , int eParam );
//½ºÅ³ Ãë¼Ò
int SendCancelSkillToServer( DWORD dwSkillCode , int lParam , int sParam , int eParam );
//¼­¹ö¿¡ ½ºÅ³¼öÇà º¸³¿
int SendProcessSKillToServer( DWORD dwSkillCode , int point , int Param1, int Param2 );
//½ºÅ³ º¯°æ
int SendUpdateSkillToServer( DWORD dwSkillCode , int lParam , int sParam , int eParam );
// È¡ÏûË®¾§µ½·şÎñÆ÷
int SendCancelCrystalToServer(DWORD dwSkillCode,int lParam,int sParam,int eParam);
// È¡Ïû´óÍ·Ò©Ë®µ½³ÌĞò
int CancelBigHeadToFunction();
// Á¦Á¿Ê¯Í·³ÌĞò
int SetForceOrbFunction(DWORD Code,int Time);

// ·¢ËÍÏÔÊ¾ÉËº¦µ½·şÎñÆ÷
int SendDisplayDamgeToServer(int Damge,DWORD dwObjectSerial,int AttackCritical,int Element);

//Å¬·£ ¸Ş¼¼Áö ¹Ş±â
int RecvClanJoinService( smTRANS_CHAR_COMMAND2 *lpTransCharCommand );
//Å¬·£ ¸Ş¼¼Áö º¸³»±â
int SendClanJoinService( DWORD dwMsgCode , Unit *lpChar  );
//Å¬·£ °¡ÀÔ ½ÂÀÎ ¸Ş¼¼Áö º¸³»±â
int SendJoinClan();
//µğ¹ÙÀÎ ¶óÀÌÆ®´× ½ºÅ³ ¿¬Ãâ ( ÀÌÆåÆ® ½ÇÇö )
int SkillPlay_DivineLightning_Effect(Unit *lpChar , int SkillPoint );
int SkillPlay_VenomSpear_Effect(Unit *lpChar , int SkillPoint);
//¸ó½ºÅÍ ½ºÅ³ ÀÌÆåÆ® ½ÇÇö ( ÀÌÆåÆ® ½ÇÇö )
int SkillPlay_Monster_Effect(Unit *lpChar , int EffectKind , int Range );
//µğ¹ÙÀÎ ¶óÀÌÆ®´× ½ºÅ³ ¿¬Ãâ ( ¸Ó¹Ì·Îµå )
int SkillPlay_MummyLord_Effect(Unit *lpChar , int Range );

//¼ì²éÊÇ·ñ×¨Ö°
int CheckChangeJob(CharacterData *pCharInfo);

DWORD GetPlayTime_T();
int	ChangeBigHeadMode(int Mode);

int	RecvClanCommand( TRANS_CLAN_COMMAND_USER *lpTransClanUser , _CLAN_USER_INFO *ClanUserInfo );
// Element¹¥»÷Ğ§¹û
int SendElementDamage(Unit *lpChar, int Kind);
//»Æ½ğÁÔÓ¥
int SendFalconDamage(Unit *lpChar );
//´í½Ì¼Òµå µ¥¹ÌÁö º¸³»±â
int SendDancingSwordDamage(Unit *lpChar );
//Àú·¦¿ë Æê µ¥¹ÌÁö
int SendLowLevelPetDamage(Unit *lpChar , int petType );
//PC¹æ¿ë Æê µ¥¹ÌÁö
int SendPCBangPetDamage(Unit *lpChar , int petType );

//¸Ş±×³×Æ½ ½ºÇÇ¾î µ¥¹ÌÁö º¸³»±â
int SendMegneticSphereDamage(Unit *lpChar );
//¸Ó½ºÆç µ¥¹ÌÁö º¸³»±â
int SendMuspellDamage(Unit *lpChar );
//ÃÖ´ë µ¥¹ÌÁö È®ÀÎ
int	SendMaxDamageToServer( WORD MinDamage , WORD MaxDamage , WORD Critical );
//ÃÖ´ë µ¥¹ÌÁö Á¤º¸±¸Á¶Ã¼¿¡ ¼³Á¤
int SetMaxDamage(CharacterData *lpCharInfo );

//½ºÅ³º¸È£°ª ÀüºÎ ÃÊ±âÈ­
int ReformSkillInfo();
//½ºÅ³°ª ÀüºÎ È®ÀÎ
int SaveCheckSkill();

//¾ÆÀÌÅÛ ÅÃ¹è ¼­ºñ½º ¼ö½Å ¿ä±¸
int	SendItemExpress( DWORD	dwItemCode , char *szPassCode );
//¾ÆÀÌÅÛ ÅÃ¹è ¼­ºñ½º ¼ö½Å ¿ä±¸
int	SendItemExpress( DWORD	dwItemCode );

//¾ßÈ£ ¸ğ¼Ç ¼­¹ö·Î º¸³»±â
int SendClanYahooMotion();
//º° Æ÷ÀÎÆ® Á¤º¸¸¦ ¼­¹ö¿¡ º¸³½´Ù
int	SendStarPointToServer( int Price , int Cash );
//±âºÎÇÑµ·À» ¼­¹ö¿¡ º¸³½´Ù
int	SendGiveMoneyToServer( int Money );

//µØÏ®ÆæÇ¹
int SkillPlay_Spear_Effect(Unit *lpChar,int SkillPoint);


#define	CLANMONEY_KIND_SOD		0
#define	CLANMONEY_KIND_CASTLE	1

int	SendClanMoneyToServer( int Money , int Flag , int Kind );
int	SendClanMoneyToServer( int Money , int Flag );
int	SendPaymentMoneyToServer( int Money , int Flag );
int SendOpenPersonalTrade( char *szTradeMsg , void *lpPersTrade );	//°³ÀÎ »óÁ¡ ¿ÀÇÂ
int SendClosePersonalTrade();										//»óÁ¡ ´İ±â
int	Send_ShowMyShopItem(Unit *lpChar );							//°³ÀÎ»óÁ¡ ¾ÆÀÌÅÛ ³»¿ë ¿ä±¸
int	Send_MyShopItemList( smTRANS_COMMAND	*lpTransCommand );		//°³ÀÎ»óÁ¡ ¾ÆÀÌÅÛ ³»¿ë »ó´ë¹æ¿¡ º¸³»±â
int	Recv_MyShopItemList( TRANS_TRADEITEMS *lpTransTradeItems );		//°³ÀÎ»óÁ¡ ¾ÆÀÌÅÛ ³»¿ë ¹ŞÀ½
int	Send_PersonalShopItem( DWORD dwCharCode , void *lpShopItem );	//°³ÀÎ »óÁ¡ ¹°°Ç ±¸ÀÔ
int	UpdateMyShopList( void *lpMyShop );								//°³ÀÎ »óÁ¡ ¾ÆÀÌÅÛ Á¤º¸ ¾÷µ¥ÀÌÆ®
int SendsServerDoc(char *szTradeMsg );

int SendWareHouseMoneyToServer(int Money,BOOL Flag);

// ¼ì²âVIPĞÅÏ¢
int SendUpdataVipInfo();
int DeleteEventItem_TimeOut(Item	*lpsItem );
int SendQuestCommandToServer( DWORD dwQuestCode , int Param1, int Param2, int Param3 );
int Start_QuestArena( DWORD dwQuestCode , int Param1, int Param2 );
int RecvBlessCastInfo( void *lpPacket );
int RecvBlessShowDamage(void *lpPacket);
int	Send_GetBlessCastleTax();
int SetBlessCastleMaster( DWORD dwClanCode , int Mode );
int	SendResistanceToServer();
Item *FindItemFromCode( DWORD dwItemCode );

//¼³¹®Á¶»ç °á°ú ¼­¹ö¿¡ º¸³»±â
int	SendPublicPollingToServer( int PollCode , int PollCnt , BYTE *bPollingData );

//ÇÙÅø Ã½Å©¿ë NPC±â´É ±¸Çö½Ã ¼­¹ö¿¡ °Ë»çÅëº¸
int HackTrap_CheckOpenFlag();
//ÇÙÅø Ã½Å©¿ë ÇÔÁ¤
int	SendHackTrapToServer( DWORD dwTrapCode , int Param );

#endif