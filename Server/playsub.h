#define CHAR_CHANGE_JOB_LEVEL 4

#define sinNPC_SHOP				0x00000001
#define sinNPC_MIX				0x00000002
#define sinNPC_AGING			0x00000004
#define sinNPC_WARE				0x00000008
#define sinNPC_SKILL			0x00000010
#define sinNPC_FORCE			0x00000020
#define sinNPC_SMELTING			0x00000030
#define sinNPC_MANUFACTURE		0x00000040
#define sinNPC_MIXTURE_RESET	0x00000080

#define MAX_JOBNUM				10

#define RIGHTHAND	0
#define LEFTHAND	1


extern DWORD	dwFuncChkTime;

DWORD Check_CodeSafe( DWORD dwStartFunc );		//ÄÚµåº¸È£
DWORD Check_CodeSafe2();						//ÄÚµåº¸È£2
DWORD	GetSafeCode();							//º¸È£ ÄÚµå ±¸ÇÏ±â
DWORD	GetSafeCode2();
int Code_VRamBuffOpen();

extern char	szLastWhisperName[32];				//¸¶Áö¸· ±Ó¸»Àü¼ÛÇÑ »ç¶÷
extern int	LastWhisperLen;
extern int	PlayerArmor;
extern int	PlayerArmorFlag;

extern int	PlayUsed_Resurrection;

char *GetFaceHairSkin(Unit *lpChar );		//¾ó±¼ º¹±¸ // ¾óÅ«ÀÌ ¿À·ù ¼öÁ¤

/*
//////////////////////////////////////////////////////////////////////
//¸Ş¸ğ¸® ÀüÃ¼ Ã½Å©
int	CheckKeepMemFull();
//¸Ş¸ğ¸® Ã½Å©
int	CheckKeepMem(DWORD ChkCount );
//¸Ş¸ğ¸® Ã½Å© Á¾·á
int CloseKeepMem();
//¸Ş¸ğ¸® Ã½Å© ÃÊ±âÈ­
int	InitKeepMemFunc();
//////////////////////////////////////////////////////////////////////
*/
//////////////////////////// ¹°¾à Ã½Å© ////////////////////////////////


//¹°¾à °¹¼ö »õ·Î ¼³Á¤
int	ResetPotion();
//¹°¾à °¹¼ö »õ·Î ¼³Á¤
int	ResetPotion2();
//¹°¾à°¹¼ö ºñ±³
int	ComparePotion();
//¹°¾à°¹¼ö ±â·Ï ¹İÀü
int	XorCheckPotion( sCHK_POTION_COUNT *ChkPotion );

//´ÙÀ½ °æÇèÄ¡ ±¸ÇÏ±â
INT64 GetNextExp( int Level );
//·¹º§°ú °æÇèÄ¡°¡ ¸Â´ÂÁö È®ÀÎ
int	CheckLevelExp( int Level , INT64 Exp );
//°æÇèÄ¡·Î ·¹º§ Ãß»ê
int	GetLevelFromExp( INT64 Exp );
//¹æ¾îÀ² °è»ê
int GetPlayDefence(CharacterData *lpAttackCharInfo , CharacterData *lpDefenceCharInfo );

//³ªÀÌ³ª¹Í ÆĞÅÏ »èÁ¦ Ãß°¡
int AddRemoveDynPattern( smDPAT *lpDinaPattern );

//·Îµù ·¥ÇÁ Á¦°Å
int CloseLoadingLamp();
//·Îµù·¥ÇÁ
int InitLoadingLamp( HWND hWnd );

//ÀÚÁÖ¾²´Â ¸Ş½Ã ·Îµå
int	LoadOftenMeshPattern( char *szFileName );
//ÀÚÁÖ¾²´Â °©¿Ê ¹Ì¸® ·Îµù
int LoadOftenArmor();
//NPC ¹Ì¸® ·Îµù
int LoadOftenNpc();
//¾ó±¼ÆÄÀÏ ¹Ì¸® ·Îµù
int LoadOftenFace();



//ÇÊµå ¸Ê ±×¸®±â
int MainFieldMap();
//ÇÊµå ¸Ê ±×¸®±â
int DrawFieldMap();

int GetFieldMapCursor();		//¹Ì´Ï¸Ê À§Ä¡¿¡ ¸¶¿ì½º À¯¹«


//µ¥ÀÌÅ¸ ¾ĞÃà ( Z/NZ ¹æ½Ä )
int EecodeCompress( BYTE *lpSrcData , BYTE *lpDestData , int size );
//¾ĞÃàµ¥ÀÌÅ¸ ÇØµ¶ ( Z/NZ ¹æ½Ä )
int DecodeCompress( BYTE *lpSrcData , BYTE *lpDestData );
//¾ĞÃàµ¥ÀÌÅ¸ ÇØµ¶ ( Z/NZ ¹æ½Ä )
int DecodeCompress( BYTE *lpSrcData , BYTE *lpDestData , int dCount );
//µ¥ÀÌÅ¸ ¾ĞÃà ( Z/NZ ¹æ½Ä )
int EecodeCompress( BYTE *lpSrcData , BYTE *lpDestData , int size , int DestSize );

//¾ĞÃàµ¥ÀÌÅ¸ ¼­¹ö ¾ÆÀÌÅÛ ÇØµ¶¿ë ( Z/NZ ¹æ½Ä )
int DecodeCompress_ItemPotion(User *lpPlayInfo , BYTE *lpSrcData , BYTE *lpDestData , int deCount , void *lpTransRecdata );


//´Ù¸¥ Ä³¸¯ÅÍ¿ÍÀÇ À§Ä¡ °ãÄ¡´ÂÁö È®ÀÎ
Unit *CheckOtherPlayPosi( int x, int y, int z );

//¾ÆÀÌÅÛ ÀÎÁõ ¹Ş±â
int ReformItem(Item *lpItemInfo );
//¾ÆÀÌÅÛ ÀÎÁõ ¹Ş±â ( »ı¼º½Ã°£ º¸Á¤ )
int ReformItem_AdjustTime(Item *lpItemInfo , int TimeAdjust );

//¾ÆÀÌÅÛ ÀÎÁõ È®ÀÎ
int CheckItemForm(Item *lpItemInfo );
//¾ÆÀÌÅÛ 2°³¸¦ ºñ±³ÇÑ´Ù
int CompareItems(Item *lpItemInfo1 , Item *lpItemInfo2 );
//¾ÆÀÌÅÛ ¼­¹ö ÀÎÁõ¸¸ ¹Ş±â
int	rsReformItem_Server(Item *lpItemInfo );
//Ä³¸¯ÅÍ Á¤º¸ ÀÎÁõ ¹Ş±â
int ReformCharForm(CharacterData *lpCharInfo );
//Ä³¸¯ÅÍ Á¤º¸ ÀÎÁõ È®ÀÎ
int CheckCharForm(CharacterData *lpCharInfo );
//Æ®·¹ÀÌµå Á¤º¸ ÀÎÁõ ¹Ş±â
int ReformTrade( void *lpTrade );
//Æ®·¹ÀÌµåÅÍ Á¤º¸ ÀÎÁõ È®ÀÎ
int CheckTrade( void *lpTrade );

//¾ÆÀÌÅÛ ¿¡ÀÌÂ¡ ÀÎÁõ ¹Ş±â
int ReformMixItem(Item *lpItemInfo );
//¾ÆÀÌÅÛ ¿¡ÀÌÂ¡ ÀÎÁõ È®ÀÎ
int CheckMixItem(Item *lpItemInfo );

//Èí¼ö·Â º¸Á¤ÇÏ¿© ±¸ÇÏ±â
float GetItemAbsorb(Item *lpItemInfo );

//Ä³¸¯ÅÍ Á¤º¸¸¦ Ä³½Ãµ¥ÀÌÅ¸¿¡ ÀúÀå
int SaveCharInfoCache( smTRNAS_PLAYERINFO *lpTransPlayInfo );

extern Unit	chrPartyPlayer;


//°ø°İ ºñÀ² Ã½Å©
int	CheckPlayAttackCount();
//°ø°İ ¹ŞÀº ¸ğ¼Ç Ä«¿îÅÍ
int AttackMotionCountUp();
//°ø°İ ¹ŞÀº ÆĞÅ¶ Ä«¿îÅÍ
int	AttackRecvCountUp();
//µî·ÏµÈ ºÒ·® ¾ÆÀÌÅÛ °Ë»ç
int	CheckCopyItem(Item *lpItem );


//PLAYSUB Æã¼Ç·çÆ¾ Ã½Å©
int Check_PlaySubReleaseFunc();

//¸ğµ¨ÀÌ ¸Â´ÂÁö È®ÀÎ
int	CheckUserModel(CharacterData *lpCharInfo );

//ÀÌº¥Åä¸® ¾ÆÀÌÅÛ ÄÚµå ÃÊ±âÈ­
int	ResetInvenItemCode();
//ÀÌº¥Åä¸® ¾ÆÀÌÅÛ ÄÚµå¿¡¼­ Æ¯Á¤ ¾ÆÀÌÅÛ Á¦°Å
int SubInvenItemCode(Item *lpItem );

//ÉèÖÃ´óÍ·µ½Í¼Æ¬
int SetBigHeadToImage(int Kind,int Time);

//ÀÎº¥Åä¸®ÀÇ ÀåÂø ¾ÆÀÌÅÛ Á¤º¸ ¼­¹ö¿¡ º¸³»±â
//ÀÎº¥Åä¸®ÀÇ ÀåÂø ¾ÆÀÌÅÛ Á¤º¸ ¼­¹ö¿¡ º¸³»±â


//ÀÌº¥Åä¸® µ· °Ë»ç ÃÊ±âÈ­
int	ResetInvenMoney();
//ÀÎº¥Åä¸® °Ë»ç¿ëµ· Ãß°¡
int	AddInvenMoney( int Money );


//°ø°İ¼Óµµ¸¦ ÇÁ·¹ÀÓ¼Óµµ·Î º¯È¯
int GetAttackSpeedMainFrame( int AttackSpeed );
int	GetAttackSpeedFrame( int AttackSpeed , int AddSpeed );
int	GetAttackSpeedFrame( int AttackSpeed );


extern int DispLoading;			//·Îµù »óÅÂ Ç¥½Ã À¯¹«
extern int MessageLoading;		//·ÎµùÁß ¸Ş¼¼Áö Ã³¸®

//¿¡Æ¼¸£ÄÚ¾î Æ÷¼Ç ·Î±× ÄÚµå
#define POTION_ETHERCORE		0x40

extern int	CodeXorLife;				//»ı¸í·Â ¼û±èÄÚµå
extern int	CodeXorMana;				//±â·Â ¼û±èÄÚµå
extern int	CodeXorStamina;				//±Ù·Â ¼û±èÄÚµå
extern int	CodeXorMoney;				//µ· ¼û±èÄÚµå


extern char	szSOD_String[64];
extern BYTE	bSOD_StringColor[4];
extern int	SOD_StringCount;

extern sSOD_SCORE	sSodScore;
extern int		SoDGateFlag;



