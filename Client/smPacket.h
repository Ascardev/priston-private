#ifndef	_SMPACKET_HEADER

#define _SMPACKET_HEADER

#include	"sinbaram\\sinitem.h"
#include	<atltime.h>

#define	smTRANSCODE_OPENLIVE				0x38000000

#define	smTRANSCODE_SYSTEM					0x48400000

#define	smTRANSCODE_CONNECTED				0x48470080
#define smTRANSCODE_RECORDDATA				0x48470081
#define smTRANSCODE_GETRECORDDATA			0x48470082
#define smTRANSCODE_FAILRECORDDATA			0x48470083
#define smTRANSCODE_RECORDRESULT			0x48470084
#define smTRANSCODE_ID_SETUSERINFO			0x48470086
#define smTRANSCODE_ISRECORDDATA			0x48470089

#define smTRANSCODE_VERSION					0x4847008A
#define smTRANSCODE_CHECK_NETSTATE			0x4847008B
#define smTRANSCODE_ADMINMODE				0x4847008C
#define smTRANSCODE_SET_OBJSERIAL			0x4847008D
#define smTRANSCODE_CHECK_NETSTATE2			0x4847008E
#define smTRANSCODE_CHECK_NETSTATE3			0x4847008F
#define smTRANSCODE_CHECK_NETSTATE4			0x48470090
#define smTRANSCODE_CHECK_NETSTATE5			0x48470091
#define smTRANSCODE_IPLIST					0x48471000
#define smTRANSCODE_CHATMESSAGE				0x48471001
#define smTRANSCODE_POSITION				0x48471002
#define smTRANSCODE_PLAYLIST				0x48471003
#define smTRANSCODE_CONTINUEDATA			0x48471004
#define smTRANSCODE_WHISPERMESSAGE			0x48471005
#define smTRANSCODE_COUPLERING				0x48471006
#define smTRANSCODE_DISPLAYDAMGE			0x48471007
#define smTRANSCODE_PLAYDATA1				0x48470010
#define smTRANSCODE_PLAYDATA2				0x48470011
#define smTRANSCODE_PLAYDATA3				0x48470012
#define smTRANSCODE_TRANSPLAYDATA			0x48470013
#define smTRANSCODE_PLAYDATAGROUP			0x48470014
#define smTRANSCODE_PLAY_COMMAND			0x48470018
#define smTRANSCODE_PARTY_CHATMSG			0x48471015
#define smTRANSCODE_ADDEXP_PARTY			0x48470029
#define smTRANSCODE_ATTACKDATA				0x48470030
#define smTRANSCODE_ADDEXP					0x48470031
#define smTRANSCODE_PLAYERINFO2				0x48470032
#define smTRANSCODE_SET_BLACKLIST			0x48470033
#define smTRANSCODE_SET_ITEMCOPYLIST		0x48470034
#define smTRANSCODE_SKIL_ATTACKDATA			0x48470035
#define smTRANSCODE_FINDCRACK				0x48470036
#define smTRANSCODE_MODULE_WARNIG			0x48470037
#define smTRANSCODE_UPDATE_CINFO			0x48470038
#define smTRANSCODE_OPENMONSTER				0x48470039
#define smTRANSCODE_WARPFIELD				0x48470040
#define smTRANSCODE_TRADEITEMS				0x48470041
#define smTRANSCODE_TRADE_REQUST			0x48470042
#define smTRANSCODE_TRADE_ITEMKEY			0x48470043
#define smTRANSCODE_TRADE_READYITEM			0x48470044
#define smTRANSCODE_SKILL_MENU				0x48470045
#define smTRANSCODE_FINDCRACK2				0x48470046
#define smTRANSCODE_WAREHOUSE				0x48470047
#define smTRANSCODE_OPEN_WAREHOUSE			0x48470048
#define smTRANSCODE_OPEN_MIXITEM			0x48470049
#define smTRANSCODE_OPEN_COLLECT			0x4847004A
#define smTRANSCODE_COLLECTMONEY			0x4847004B
#define	smTRANSCODE_PLAYERINFO_Q			0x4847004C
#define smTRANSCODE_OPEN_AGING				0x4847004D
#define smTRANSCODE_SKIL_ATTACKUSER			0x4847004E
#define smTRANSCODE_OPEN_EVENTGIFT			0x4847004F
#define smTRANSCODE_PLAYERINFO				0x48470020
#define smTRANSCODE_GETPLAYERINFO			0x48470021
#define smTRANSCODE_FAILCONNECT				0x48470023
#define smTRANSCODE_OPEN_SOCKET				0x48470024
#define smTRANSCODE_PLAYITEM				0x48470050
#define smTRANSCODE_DELITEM					0x48470051
#define smTRANSCODE_PUTITEM					0x48470052
#define smTRANSCODE_THROWITEM				0x48470053
#define smTRANSCODE_SHOP_ITEMLIST			0x48470054
#define smTRANSCODE_SAVETHROWITEM			0x48470055
#define smTRANSCODE_SAVETHROWMONEY			0x48470056
#define smTRANSCODE_SAVETHROWITEM2			0x48470057
#define smTRANSCODE_SAVETHROWITEMS			0x48470058
#define smTRANSCODE_PLAYERKILLING			0x48470059
#define smTRANSCODE_GETITEM					0x4847005A
#define smTRANSCODE_USEITEM_CODE			0x4847005B
#define smTRANSCODE_COMMAND_USER			0x4847005C
#define smTRANSCODE_WING_NPC				0x4847005D
#define smTRANSCODE_PAYMENT_MONEY			0x4847005E
#define smTRANSCODE_MEDIA_NPC				0x4847005F
#define smTRANSCODE_ADD_STARTPOSI			0x48470060
#define smTRANSCODE_DEL_STARTPOSI			0x48470061
#define smTRANSCODE_ADMIN_COPYCHAR			0x48470062
#define smTRANSCODE_ADD_NPC					0x48470070
#define smTRANSCODE_DEL_NPC					0x48470071
#define smTRANSOCDE_SET_EXPUP				0x48470072
#define smTRANSOCDE_SET_PLAYINFO_EXP		0x48470073
#define smTRANSOCDE_SET_PLAYSIZE			0x48470074
#define	smTRANSCODE_PARTY_UPDATE			0x484700A0
#define	smTRANSCODE_PARTY_REQUEST			0x484700A1
#define	smTRANSCODE_PARTY_JOIN				0x484700A2
#define	smTRANSCODE_PARTY_PLAYUPDATE		0x484700A3
#define	smTRANSCODE_PARTY_RELEASE			0x484700A4
#define	smTRANSCODE_PARTY_COMMAND			0x484700A5
#define smTRANSCODE_OPEN_MIXTURE_RESET		0x484700A6
#define smTRANSCODE_OPEN_ELEMENT			0x484700A9
#define smTRANSCODE_OPEN_CARAVAN			0x484700AA
#define smTRANSCODE_CARAVAN					0x484700AB
#define smTRANSCODE_PCBANG_PET				0x484700B0
#define smTRANSCODE_PHENIX_PET				0x484700B1
#define smTRANSCODE_HELP_PET				0x484700B2
#define smTRANSCODE_FRUIT					0x484700B3
#define smTRANSCODE_CANCEL_BIGHEAD			0x484700B4
#define smTRANSCODE_FORCE_ROE				0x484700B5
#define smTRANSCODE_CANCEL_FORCE			0x484700B6
#define smTRANSCODE_WAREHOUSEMONEY			0x484700B7
#define smTRANSCODE_CHANGEJOBLEVEL			0x484700B8
#define smTRANSCODE_MAPLEVEL				0x484700B9
#define smTRANSCODE_CANCEL_CARAVAN			0x484700BA
#define	smTRANSCODE_SERVER_INFO				0x484700C0
#define	smTRANSCODE_PARTY_POTION			0x484700D0
#define	smTRANSCODE_HEALING					0x484700D2
#define	smTRANSCODE_HOLYMIND				0x484700D3
#define	smTRANSCODE_GRAND_HEALING			0x484700D4
#define	smTRANSCODE_VAMPRIC_CUSPID			0x484700D6
#define	smTRANSCODE_VAMPRIC_CUSPID_EX		0x484700D7
#define	smTRANSCODE_MANA_RECHARGING			0x484700D8
#define	smTRANSCODE_RECORD_TRADE			0x48480010
#define smTRANSCODE_NETWORK_QUALITY			0x484700E0
#define smTRANSCODE_PROCESSINFO				0x484700E4
#define	smTRANSCODE_CLOSECLIENT				0x484700E6
#define smTRANSCODE_CHECKIP					0x484700E7
#define	smTRANSCODE_SAVECLIENT				0x484700E8
#define smTRANSCODE_EFFECT_ITEM				0x48478000
#define smTRANSCODE_EFFECT_ELEMENT			0x48478001
#define smTRANSCODE_EFFECT_WEAPON			0x48478002
#define smTRANSCODE_EFFECT_STUN				0x48478004
#define smTRANSCODE_EFFECT_CURSE			0x48478006
#define smTRANSCODE_EFFECT_ICE				0x48478008
#define smTRANSCODE_EFFECT_POISION			0x4847800A
#define smTRANSCODE_EFFECT_FIRE				0x4847800B
#define smTRANSCODE_EFFECT_VANISH			0x4847800C
#define smTRANSCODE_EFFECT_PERSHOP			0x4847800E
#define smTRANSCODE_EFFECT_LOWPET			0x4847800F
#define smTRANSCODE_EFFECT_CLANMGR			0x48479000
#define smTRANSCODE_EFFECT_FORCEORB			0x48479010
#define smTRANSCODE_EFFECT_CURSE_QUEST		0x48479011
#define smTRANSCODE_EFFECT_BLESS_SCORE		0x48479012
#define smTRANSCODE_EFFECT_KEEPSKILL		0x48479020
#define smTRANSCODE_EFFECT_VIPER			0x48479030
#define smTRANSCODE_EFFECT_WING				0x48479040
#define smTRANSCODE_EFFECT_LEVEL			0x48479050
#define smTRANSCODE_CONT_OBJSERIAL			0x48478010
#define smTRANSCODE_MESSAGEBOX				0x48478100
#define	smTRANSCODE_FUNCERROR				0x48478200
#define smTRANSCODE_FUNCTION_MEM2			0x48478300
#define	smTRANSCODE_SET_BLACKLIST2			0x48478400
#define smTRANSCODE_SET_BLACKLIST3			0x48478500
#define	smTRANSCODE_BAD_PLAYER				0x48478600
#define	smTRANSCODE_FIX_ATTACK				0x48478700
#define	smTRANSCODE_DEAD_PLAYER				0x48478800
#define smTRANSCODE_CLIENT_ERROR			0x48478900
#define	smTRANSCODE_INVEN_ERR_ITEM			0x48478910
#define	smTRANSCODE_INVEN_ERR_MONEY			0x48478920
#define	smTRANSCODE_INVEN_POSITION			0x48478930
#define	smTRANSCODE_INVEN_POSITION2			0x48478931
#define smTRANSCODE_ENCODE_PACKET			0x80010000
#define smTRANSCODE_ENCODE_PACKET2			0x90010000
#define smTRANSCODE_OPEN_CLANMENU			0x48478A00
#define smTRANSCODE_OPEN_STARPOINT			0x48478A10
#define smTRANSCODE_STARPOINT				0x48478A12
#define smTRANSCODE_OPEN_GIVEMONEY			0x48478A14
#define smTRANSCODE_GIVEMONEY				0x48478A16
#define smTRANSCODE_CLANMONEY				0x48478A18
#define smTRANSCODE_ITEM_EXPRESS			0x48478A80
#define smTRANSCODE_OPEN_MYSHOP				0x48478A90
#define smTRANSCODE_CALL_MYSHOP				0x48478AA0
#define	smTRANSCODE_MYSHOP_ITEM				0x48478AB0
#define	smTRANSCODE_MYSHOP_MESSAGE			0x48478AC0
#define	smTRANSCODE_MYSHOP_TRADE			0x48478AD0
#define smTRANSCODE_EFFECT_PCBANGPET		0x48478AE0
#define smTRANSCODE_ADMINMODE2				0x5047108C
#define smTRANSCODE_CHECK_NETSTATE20		0x5047008E
#define smTRANSCODE_CHECK_EXPMONEY			0x50320010
#define smTRANSCODE_FORCEORB_DATA			0x50320030
#define smTRANSCODE_PRIMEITEM_DATA			0x50320031
#define smTRANSCODE_PRIMEITEM_DATA2			0x50320032
#define smTRANSCODE_PRIMEITEM_DATA3			0x50320033
#define smTRANSCODE_PRIMEITEM_DATA4			0x50320036
#define smTRANSCODE_BOOSTER_DATA			0x50320034
#define smTRANSCODE_AGING_DATA				0x50320035
#define smTRANSCODE_SKILLDELAY_DATA			0x50320036
#define smTRANSCODE_SEND_DATASERVER			0x50320100
#define smTRANSCODE_SEND_GAMESERVER			0x50320110
#define smTRANSCODE_SEND_AREASERVER			0x50320120
#define smTRANSCODE_SEND_AGAME_SERVER		0x50320130

#define smTRANSCODE_SEND_AGAME_PRIMEITEM_DATA2	0x50320140
#define smTRANSCODE_SEND_AGAME_PRIMEITEM_DATA3	0x50320150
#define smTRANSCODE_SEND_AGAME_PRIMEITEM_DATA4	0x50320160


#define smTRANSCODE_CRAFTITEM				0x50320200
// ¶ÍÔìÎïÆ·Ð­Òé
#define smTRANSCODE_AGINGITEM				0x50320202
#define	smTRANSCODE_AGING_UPGRADE			0x50320204
#define	smTRANSCODE_MAKE_LINKCORE			0x50320205
#define	smTRANSCODE_USE_LINKCORE			0x50320206
#define smTRANSCODE_WINGITEM				0x50320208
#define smTRANSCODE_SHOPTITEM				0x50320210
#define smTRANSCODE_SHOP_SELLITEM			0x50320212
#define	smTRANSCODE_ITEM_FORCEORB			0x50320214
#define smTRANSCODE_ELEMENTITEM				0x50320216
#define smTRANSCODE_SOCKETITEM				0x50320217	
#define	smTRANSCODE_QUEST_COMMAND			0x50320220
#define smTRANSCODE_CHECKITEM				0x50320300
#define smTRANSCODE_ERRORITEM				0x50320310
#define smTRANSCODE_CLEARPOTION				0x50320320

#ifdef _CHECK_MESH
#define smTRANSCODE_CHECK_ITEMMESH			0x50320330
#endif

#define smTRANSCODE_CLIENT_FUNCPOS			0x50320400
#define smTRANSCODE_GETCLIENT_FUNCPOS		0x50320410
#define smTRANSCODE_FUNCTION_MEM			0x50320420
#define smTRANSCODE_FUNCTON_RESULT			0x50320430
#define smTRANSCODE_PROCESS_TIMEMAX			0x50320500
#define smTRANSCODE_NSPRITE					0x50320600
#define smTRANSCODE_NPROTECT				0x50320700
#define smTRANSCODE_GAMEGUARD_AUTH			0x50320710
#define	smTRANSCODE_REC_DAMAGEDATA			0x50320800

#define	smTRANSCODE_SOD_RESULT				0x50320900
#define	smTRANSCODE_SOD_RESULT2				0x50320901

#define	smTRANSCODE_PARTY_SKILL				0x50320A00

#define	smTRANSCODE_CANCEL_SKILL			0x50320A10
#define	smTRANSCODE_PROCESS_SKILL			0x50320A20
#define smTRANSCODE_PROCESS_SKILL2			0x50320A30
#define smTRANSCODE_PROCESS_CLAN_SKILL		0x50320A35
#define	smTRANSCODE_UPDATEL_SKILL			0x50320A40
#define	smTRANSCODE_SUCCESS_EVATION			0x50320A50
#define	smTRANSCODE_RESISTANCE				0x50320A60
#define	smTRANSCODE_PUBLIC_POLLING			0x50320A70
#define	smTRANSCODE_NOTICE_BOX				0x50320A80
#define	smTRANSCODE_HACKTRAP				0x50320A90

#define	smTRANSCODE_VIRTURAL_POTION			0x50320B00
#define	smTRANSCODE_CLAN_SERVICE			0x50320C00
#define	smTRANSCODE_CLAN_UPDATE				0x50320C10
#define	smTRANSCODE_QUEST_MESSAGE			0x50320D00
#define	smTRANSCODE_DEAD_USER				0x50320E00
#define	smTRANSCODE_DEAD_EXP				0x50320E02
#define	smTRANSCODE_YAHOO_MOTION			0x50320E10
#define	smTRANSCODE_CHANGE_EVENT			0x50320F00
#define	smTRANSCODE_CLIENTINFO				0x50321000
#define	smTRANSCODE_WARNING_BLINK_ATT		0x50321010
#define smTRANSCODE_ATTACK_DAMAGE			0x50322000
#define smTRANSCODE_RANGE_DAMAGE			0x50322010
#define smTRANSCODE_ATTACK_RESULT			0x50322020
#define smTRANSCODE_DISP_DAMAGE				0x50322030
#define smTRANSCODE_ATTACKDATA2				0x50322040
#define smTRANSCODE_LIMIT_DAMAGE			0x50322050
#define smTRANSCODE_WARNING_CLIENT			0x50322060
#define smTRANSCODE_WARNING_SKILL			0x50322080
#define smTRANSCODE_COMIC_SKIN				0x50322070
#define	smTRANSCODE_REC_ADMIN_COMMAND		0x50322090
#define smTRANSCODE_CHECK_ADMINMODE			0x503220A0
#define smTRANSCODE_SOD_INFOMATION			0x503220B0
#define smTRANSCODE_BLESSCASTLE_INFO		0x503220C0
#define smTRANSCODE_BLESSCASTLE_TAX			0x503220D0
#define smTRANSCODE_ATTACK_SLASH_LIST		0x503220E0
#define smTRANSCODE_UPDATE_SERVER_PARAM		0x503220F0
#define smUPDATE_PARAM_LOWUSER_PRESENT		0x100
#define smTRANSCODE_USER_ID					0x50322100
#define smTRANSCODE_DAMAGE_ENCODE_MEM		0x50322F00
#define smTRANSCODE_DAMAGE_ENCODE_MEM2		0x50322EC0
#define	smTRANSCODE_PACKET_DYNFUNC			0x50323000
#define	smTRANSCODE_AREA_SERVER_MAP			0x50324000
#define smTRANSCODE_OPEN_SMELTING			0x50325000
#define smTRANSCODE_SMELTINGITEM			0x50325001
#define smTRANSCODE_OPEN_MANUFACTURE		0x50326000
#define smTRANSCODE_MANUFACTURE				0x50326001
#define smTRANSCODE_MANUFACTURE_WEIGHT_PRICE 0x50326002
#define smTRANSCODE_GIFTBOX_MONEY			0x50326003
#define smTRANSCODE_PREMIUMITEM_INIT		0x50326004
#define smTRANSCODE_MIXTURE_RESET_ITEM		0x50326006
#define smTRANSCODE_PLAYER_DATA_VIP			0x50326009
#define smTRANSCODE_PLAYER_GAME_VIP			0x50326010

// ¹ÖÎïË®¾§Ð­Òé È¡ÏûË®¾§Ð­Òé
#define smTRANSCODE_CRYSTAL_ORB				0x50326011
// ¶À½ÇÊÞÒ»¼ÒÊý¾ÝÐ­Òé
#define smTRANSCODE_CARAVAN_HOPY			0x50326012
#define smTRANSCODE_CARAVAN_SELECT			0x50326013
#define	rsHARDCORE_EVENT_FLAG				0x100
#define smCODE_SOD_EFFECT					100
#define smTRANSCODE_EVENT_GAME				0x50326007
#define smCODE_EVENT_STATE_INIT				100

#define smTRANSCODE_ITEMDOC					0x50326008


#define TRANS_BUFF_SIZE						4096

#define	smCHAR_STATE_NPC					0
#define	smCHAR_STATE_ENEMY					1
#define	smCHAR_STATE_USER					0x80

#define	smCHAR_MONSTER_NATURAL				0x80
#define	smCHAR_MONSTER_GOOD					0x81
#define	smCHAR_MONSTER_EVIL					0x82

#define	smCOMMNAD_USER_WARP					0x100
#define	smCOMMNAD_USER_AGINGUP				0x110
#define	smCOMMNAD_USER_HOLY_INCANTATION		0x120
#define	smCOMMNAD_USER_RESURRECTION			0x130
#define	smCOMMNAD_USER_FORCEORB				0x140
#define	smCOMMNAD_USER_VALENTO				0x150
#define	smCOMMNAD_USER_FIREFLOWER			0x160

#define	smCOMMAND_PLAY_BABEL				0x200
#define	smCOMMAND_PLAY_BELSS_CASTLE			0x210
#define	smCOMMAND_PLAY_PK_FIELD				0x220
#define	smCOMMAND_PLAY_KELVEZU				0x230
#define smCOMMAND_PLAY_WEATHER				0x300 //ÏÂÓêÐ­Òé

class	Unit;

class	rsRECORD_DBASE;

#define	FALLITEM_MAX						200
#define	FALLITEM2_MAX						3

struct _FALLITEM{
	DWORD	dwItemCode;
	int		Percentage;
	short	sPrice[2];
};

#define	NPC_MESSAGE_MAX		20

//Ä³¸¯ÅÍ Á¤º¸ ´ÜÃà Å©±â
#define	smCHAR_INFO_QUICK_SIZE		192
#define	smCHAR_INFO_QUICK_SIZE2		352

#define	THROW_ITEM_INFO_MAX		64
#define	THROW_ITEM_INFO_MASK	63
#define	INVEN_ITEM_INFO_MAX		300


//Ä³¸¯ÅÍ ÁÂÇ¥ ±¸Á¶
struct rsPLAYPOS {
	DWORD	Area;		// Low->Wolrd High->Area	: ÇöÀç Á¸ÀçÇÏ°í ÀÖ´Â Áö¿ªÀÇ À§Ä¡ ÄÚµå
	int		x,y,z;		// ÁÂÇ¥
};

//³»¿ë : ÀÚ½ÅÀÇ À§Ä¡¹× Á¤º¸¸¦ ¼­¹ö¿¡ Àü¼Û
//´ë»ó : Å¬¶óÀÌ¾ðÆ® -> ¼­¹ö
//ÄÚµå : smTRANSCODE_POSITION
//10ÃÊ °£°ÝÀ¸·Î ¼­¹ö¿¡ º¸³»Áö´Â ÇÃ·¹ÀÌ¾î À§Ä¡ Á¤º¸
struct TRANS_PLAYPOS {
	int size,code;
	
	rsPLAYPOS	rsPlayPos;
	short Hp[2];
};



//³»¿ë : »ó´ëÇÑÅ× °ø°Ý Á¤º¸¸¦ º¸³½´Ù
//´ë»ó : Å¬¶óÀÌ¾ðÆ® -> ¼­¹ö  Å¬¶óÀÌ¾ðÆ® -> Å¬¶óÀÌ¾ðÆ®
//ÄÚµå : smTRANSCODE_ATTACKDATA
struct TRANS_ATTACKDATA
{
	int size,code;

	DWORD	dwDestObjectSerial;	//°ø°ÝÇÏ´Â Ä³¸¯ÅÍ °íÀ¯¹øÈ£
	DWORD	dwTarObjectSerial;	//°ø°Ý´ë»ó Ä³¸¯ÅÍ °íÀ¯¹øÈ£

	int		x,y,z;			// ÁÂÇ¥
	int		AttackState;	// ¼Ó¼º
	int		AttackSize;		// °ø°Ý ¹üÀ§
	int		Power;
	int		PowerType;
	DWORD	dwChkSum;

	short	sRating[2];	//[0]-·¹º§ [1]-¸íÁß·Â
	DWORD	dwDamageChkSum;
};

struct TRANS_ATTACKDATA2 {
	int size,code;

	DWORD	dwChkSum;

	DWORD	dwDestObjectSerial;	//°ø°ÝÇÏ´Â Ä³¸¯ÅÍ °íÀ¯¹øÈ£
	DWORD	dwTarObjectSerial;	//°ø°Ý´ë»ó Ä³¸¯ÅÍ °íÀ¯¹øÈ£

	int		x,y,z;			// ÁÂÇ¥
	int		AttackState;	// ¼Ó¼º
	int		AttackSize;		// °ø°Ý ¹üÀ§
	short	Power[2];		// °ø°Ý ÆÄ¿ö
	short	Power2[2];		// °ø°Ý ÆÄ¿ö ( Ãß°¡ °ø°Ý )
	short	Critical[2];	// Å©¸®Æ¼ÄÃ
	int		SkillCode;		// ½ºÅ³ÄÚµå
	DWORD	dwTime;			// Å¬¶óÀÌ¾ðÆ® ½Ã°£
	int		AttackCount;	// °ø°Ý Ä«¿îÅÍ
	short	MotionCount[2];	// °ø°Ý ¸ð¼Ç Ä«¿îÅÍ
	DWORD	dwWeaponCode;	// ÁÖ °ø°Ý ¹«±â
	short	Area[2];		// Áö¿ª
	int		Temp[4];		// ¿¹ºñ
};


// Àåº° - ¹üÀ§Çü ½ºÅ³( 32 -> 42 )
#define SKIL_ATTACK_CHAR_MAX		42

struct TRANS_SKIL_ATTACKDATA
{
	int size,code;

	DWORD	dwDestObjectSerial;

	int x,y,z;
	int AttackState;
	int AttackSize;
	int Power;

	DWORD	dwChkSum;

	int	TargetCount;
	DWORD	dwTarObjectSerial[SKIL_ATTACK_CHAR_MAX];
};

struct TRANS_SKIL_ATTACKDATA2
{
	int size,code;

	DWORD	dwDestObjectSerial;	//°ø°ÝÇÏ´Â Ä³¸¯ÅÍ °íÀ¯¹øÈ£

	DWORD	dwChkSum;

	int		x,y,z;			// ÁÂÇ¥
	int		AttackState;	// ¼Ó¼º
	int		AttackSize;		// °ø°Ý ¹üÀ§
	short	Power[2];		// °ø°Ý ÆÄ¿ö
	short	Power2[2];		// °ø°Ý ÆÄ¿ö ( Ãß°¡ °ø°Ý )
	short	Critical[2];	// Å©¸®Æ¼ÄÃ
	int		SkillCode;		// ½ºÅ³ÄÚµå
	DWORD	dwTime;			// Å¬¶óÀÌ¾ðÆ® ½Ã°£
	int		AttackCount;	// °ø°Ý Ä«¿îÅÍ
	short	MotionCount[2];	// °ø°Ý ¸ð¼Ç Ä«¿îÅÍ
	DWORD	dwWeaponCode;	// ÁÖ °ø°Ý ¹«±â
	short	Area[2];		// Áö¿ª
	int		Temp[4];		// ¿¹ºñ

	DWORD	dwMainTargetObject;		//ÁÖ Å¸°Ù

	int	TargetCount;
	DWORD	dwTarObjectSerial[SKIL_ATTACK_CHAR_MAX];	//°ø°Ý´ë»ó Ä³¸¯ÅÍ °íÀ¯¹øÈ£
};



//³»¿ë : Áö¿ª¿¡ Á¸ÀçÇÏ´Â ´Ù¸¥ ÇÃ·¹ÀÌ¾î Á¤º¸ ¸ñ·Ï Àü¼Û
//´ë»ó : ¼­¹ö -> Å¬¶óÀÌ¾ðÆ®
//ÄÚµå : smTRANSCODE_IPLIST
struct TRANS_AREAINFO_HEADER {
	int		size;
	int		code;
	DWORD	dwIP;
	int		Stats;					//Àü¼Û ¿Ï·á¸é TRUE ¾ÆÁ÷ ´õ º¸³¾ µ¥ÀÌÅ¸°¡ ÀÖÀ¸¸é FALSE
	int		TransListCnt;			//Àü¼ÛÇÏ´Â TRANS_IPLIST °¹¼ö
};
struct TRANS_IPLIST {
	DWORD	dwIP;
	rsPLAYPOS	Pos;
};

/////////////// ¾ÆÀÌÅÛ ÅÃ¹è ¼­ºñ½º /////////////////
#define	POST_ITEM_MAX				500

struct _POST_BOX_ITEM {
	int		Flag;
	char	szCharName[32];
	char	szItemCode[32];
	char	szSpeJob[32];
	char	szDoc[128];
	char	szFormCode[64];
	char	szPassCode[16];

	DWORD	dwItemCode;
	DWORD	dwJobCode;
	DWORD	dwFormCode;
	DWORD	dwPassCode;
	DWORD	dwParam[4];
};

struct	rsPOST_BOX_ITEM {
	DWORD	dwHead;
	int		ItemCounter;

	_POST_BOX_ITEM	PostItem[POST_ITEM_MAX];
};

struct	TRANS_POST_ITEM {
	int		size,code;

	char	szItemName[32];
	char	szDoc[128];
	DWORD	dwItemCode;
	DWORD	dwItemJobCode;
	DWORD	dwParam[4];

	DWORD	dwItemFlag;
	int		Weight;			// pluto ÇØ¿Ü ºô¸µ ¾ÆÀÌÅÛ ¹«°Ô
};
//	sITEM_INFO	sItemInfo;


///////////////////////////////////////////////////////


#define	srPLAYBUFF_MAX		4
#define	srPLAYBUFF_MASK		3

#define	PARTY_PLAYER_MAX		6

// Àåº° - ¿¹ºñ¹öÆÛ
#define	srRECORD_DEFAULT_SIZE	16384
//#define	srRECORD_DEFAULT_SIZE	32768
#define	srRECORD_MEMORY_SIZE	24576
//#define	srRECORD_MEMORY_SIZE	49152

#define SKILL_POINT_COLUM_MAX	20

struct	TRANS_PARTY_PLAYINFO;

struct	npGAME_GUARD_AUTH_INFO {
	 DWORD	Auth_Value;		//°ÔÀÓ°¡µå È®ÀÎÄÚµå ( °ªÀ» ¸®ÅÏ ¹ÞÀ½ )
	 DWORD	Auth_Time;		//°ÔÀÓ°¡µå È®ÀÎ½Ã°£ ( ´ÙÀ½Ã³¸® ½Ã°£ )
	 DWORD	Auth_Count;		//°ÔÀÓ°¡µå È®ÀÎÄ«¿îÅÍ ( ÃÑ º¸³½ È½¼ö )
	 DWORD	Auth_Retry;		//°ÔÀÓ°¡µå È®ÀÎ Àç½Ãµµ ( ÀÀ´äÀÌ 60ÃÊ ¾È¿¡ ¾È¿À¸é ¸î¹ø±îÁö Àç½Ãµµ )
};

//¾ÆÀÌÅÛ ±¸¸Å Ä«¿îÅÍ
struct	sMYSHOP_SELL_INFO {
	DWORD	dwCode;
	DWORD	dwHead;
	DWORD	dwChkSum;
	int		Price;
};

#define	MYSHOP_LIST_MAX		32
#define	MYSHOP_LIST_MASK	31


struct	sCASTLE_MASTER {
	int		Flag;
	DWORD	dwCheckTime;
	int		SelectSkill;
};

#define	rsDATA_ERROR_WAREHOUSE	1
#define rsDATA_ERROR_CARAVAN	2


struct smTRANS_COMMAND
{
	int	size;
	int code;

	int LParam;
	int WParam;
	int SParam;
	int EParam;
};

//¹ÚÀç¿ø - XignCode
#define PACKET_SIZE 512


//¹ÚÀç¿ø - XignCode
typedef struct _XIGNCODE_PACKET {
	int size;
	int code;
	BYTE data[PACKET_SIZE]; //¹ÚÀç¿ø - XignCode
} XIGNCODE_PACKET;

typedef struct _XIGNCODE_TempData{
	BOOL m_type;
	BOOL m_ceComplete;
	DWORD	dwWaitTime_NC;
	DWORD	dwWaitTime_CE;
	BOOL   dwClientReady;
	HANDLE xigncode_handle;
	int m_pcount;
} XIGNCODE_TempData;

//¹ÚÀç¿ø - XignCode
#define smTRANSCODE_XIGNCODE_PACKET		0x48470400
#define smTRANSCODE_XIGNCODE_START		0x48470500


typedef struct _WSABUF {
	u_long      len;     
	char FAR *  buf;     
} WSABUF, FAR * LPWSABUF;

#define BILLING_GPTYPE_DAY		0
#define BILLING_GPTYPE_TIME		1
#define BILLING_GPTYPE_FREE		2
#define BILLING_GPTYPE_POTAL	3

#define BILLING_PGTYPE_PERSONAL	0
#define BILLING_PGTYPE_PCROOM	0




/////////////////////////////////////////////////////////////////////////////////////////

//³»¿ë : Ã¤ÆÃ ¹®ÀÚ¿­ Àü¼Û ÄÚµå
//´ë»ó : Å¬¶óÀÌ¾ðÆ® <-> ¼­¹ö
//ÄÚµå : smTRANSCODE_CHATMESSAGE
struct TRANS_CHATBUFF {
	int		size;
	int		code;
	DWORD	dwIP;
};
struct CHATBUFF {
	DWORD	dwIP;
	char szMessage[256];
};

struct TRANS_CHATMESSAGE {
	int		size;
	int		code;
	DWORD	dwIP;
	DWORD	dwObjectSerial;	//°´Ã¼ÀÇ °íÀ¯°ª

	char szMessage[256];
};


struct smPLAYDATA_GROUP {
	int		size,code;
	int		PlayDataCnt;
	DWORD	dwSendCode;
};


#define smPLAYBUFF_FRAME_NONE			0xFFFF0000

#define	smPLAYBUFF_ITEM_BODY			0
#define	smPLAYBUFF_ITEM_LEFT			1
#define	smPLAYBUFF_ITEM_RIGHT			2
#define	smPLAYBUFF_ITEM_SKIL			3
#define TRANS_PLAYDATA_EVENT_LEVEL		0
#define TRANS_PLAYDATA_EVENT_POTION		1
#define TRANS_PLAYDATA_EVENT_SKIL		2
#define TRANS_PLAYDATA_EVENT_EXT		3

struct smTRANS_CHAR_COMMAND
{
	int	size;
	int code;

	int LParam;
	int WParam;
	int SParam;

	char	szName[32];
};

struct smTRANS_CHAR_COMMAND2
{
	int	size;
	int code;

	int LParam;
	int WParam;
	int SParam;

	char	szId[32];
	char	szName[32];
};

struct smTRANS_MAP_LEVEL
{
	int size;
	int code;

	int MapLevel[MAX_FIELD];
};

struct smTRNAS_PLAYERINFO
{
	int	size;
	int code;

	CharacterData	sCharacterData;

	DWORD	dwObjectSerial;

	int	x,y,z;
	int ax,ay,az;
	int state;
};

struct smTRNAS_PLAYERINFO_QUICK
{
	int	size;
	int code;

	DWORD	dwObjectSerial;

	int	x,y,z;				//ÃÖÃÊ ÁÂÇ¥
	int ax,ay,az;			//ÃÖÃÊ °¢µµ
	int state;				//¼Ó¼º

	CharacterData	sCharacterData;
};


//°£´ÜÇÑ ÄÚ¸àµå Àü¼Û¿ë ±¸Á¶
struct smTRANS_COMMAND_DWORD
{
	int	size;
	int code;

	DWORD LParam;
	DWORD WParam;
	DWORD SParam;
	DWORD EParam;
};

struct smTRANS_COMMAND_EX
{
	int	size;
	int code;

	int LParam;
	int WParam;
	int SParam;
	int EParam;

	int LxParam;
	int WxParam;
	int SxParam;
	int ExParam;

};


struct smTRANS_COMMAND_BUFF {
	smTRANS_COMMAND		smTransCommand;
	char	*Buff[256];
};

struct smTRANS_COMMAND_SOD {
	smTRANS_COMMAND		smTransCommand;
	int		MyScore;
	int		MyTeam;
	int		TeamScore[4];
	int		Temp[4];
};

struct smTRANS_COMMAND_POLLING {
	smTRANS_COMMAND		smTransCommand;
	BYTE	bPolling[10];
};



//¼Ó¼º È£Ãâ
struct smTRANS_RESISTANCE {
	int	size;
	int code;
	int	Param;
	short Resistance[8];
	int	Absorb;
};


//°ø¼º
struct smTRANS_BLESSCASTLE {
	smTRANS_COMMAND		smTransCommand;
	int				TaxRate;
	short			Tower[12];		//Å¸¿ö¼³Á¤	
	unsigned char	MercenaryNum[4];	//int		MercenaryType;	//¿ëº´¼³Á¤
	int				ClanSkill;		//Å¬·£½ºÅ³
	int				Price;
	DWORD			dwMasterClan;	//¼ºÁÖÅ¬·£
	int				Temp[4];
};

//°ø°Ý¼øÀ§ Åé10
struct	rsUSER_LIST_TOP10 {
	//SYSTEM HEADER
	int		size,code;

	int		tCode;
	DWORD	dwObjectSerial;
	DWORD	dwNameCode;
	int		x,y,z;

	//BODY

	DWORD	dwCharCode;
	DWORD	dwUpdateTime;
	DWORD	dwTotalDamage;
	char	bCrystalTowerCount[4];
	DWORD	dwTemp[2];

	DWORD	dwUserCode[10];
	int		Damage[10];
	int		Counter[10];
};

/////////////// ¾ÆÀÌÅÛÀ» ±×·ìÀ¸·Î ¹­¾î¼­ Àü¼Û /////////////////////

/*
/////¼­¹ö·Î º¸³»Áú ¾ÆÀÌÅÛ ±¸Á¶Ã¼ 
struct sCRAFTITEM_SERVER{
	int size, code;
	int DocIndex;
	int Result;
	sITEM DesCraftItem;
	DWORD SheltomCode[12];
	DWORD Head[12];
	DWORD CheckSum[12];
	int Index;
	int Money;
};
*/


//¾ÆÀÌÅÛ ±×·ìÀ¸·Î Àü¼Û
#define	TRANS_GROUPITEM_MAX		16
#define	TRANS_GROUPITEM_HEADER_SIZE		(14*4)

//¾ÐÃàÀ» Ç¬°æ¿ì
struct	TRANS_ITEMINFO_GROUP {
	int	size,code;

	int Index;
	int Result;
	int Money;
	int	ItemCount;

	DWORD	dwTemp[8];

	Item	sItemInfo[TRANS_GROUPITEM_MAX];
};

//¾ÐÃàÆ÷¸Ë
struct	TRANS_ITEMINFO_GROUP2 {
	int	size,code;

	int Index;
	int Result;
	int Money;
	int	ItemCount;

	DWORD	dwTemp[8];

	char	szBuff[ sizeof(Item) * TRANS_GROUPITEM_MAX ];
};


//´ÜÀÏ ¾ÆÀÌÅÛ Àü¼Û
struct TRANS_ITEMINFO {
	//------------------------------------------------------------------< _ignore_bug_fix_0x00000000_ //ÇØ¿Ü
	/*
	TRANS_ITEMINFO()  // »ý¼ºÀÚ
	{
		size = 0,code = 0;x=0,y=0,z=0,
		ZeroMemory(&Item,sizeof(Item));
		for(int i=0;i<4;i++)
		{
			dwSeCode[i] = 0;
		}
		
	};
	*/
	//------------------------------------------------------------------  _ignore_bug_fix_0x00000000_ >
	int	size,code;

	//char	szItemName[32];
	//DWORD	ItemCode;

	Item	sItem;

	int x,y,z;

	DWORD	dwSeCode[4];		//º¸¾È ÄÚµå
};


struct	TRANS_ITEM_CODE {
	int size,code;

	DWORD	dwFlag;

	DWORD	dwItemCode;
	DWORD	dwHead;
	DWORD	dwChkSum;
	DWORD	dwTime;
};


struct TRANS_ITEM {
	int			state;

	int			type;
	int			ItemCode;

	int			x,y,z;
	char		szName[64];
	void		*lpStgArea;
	//char szModelName[64];
};


struct _TRANS_THROW_ITEM {
	DWORD	dwCode;
	DWORD	dwHead;
	DWORD	dwChkSum;
};

#define	THROW_ITEMS_MAX				32
//±¸Á¶Ã¼ Çì´õ »çÀÌÁî
#define	TRANS_THROW_ITEMS_DEFSIZE	(sizeof(int)*4)

struct TRANS_THROW_ITEMS {
	int		size,code;
	int		ThrowItemCount;
	int		Temp;

	_TRANS_THROW_ITEM	ThrowItems[THROW_ITEMS_MAX];
};



//°Å·¡ÈÄ ¾ÆÀÌÅÛ º¸°í
struct _TRANS_RECORD_TRADE_ITEM {
	DWORD	dwCode;
	DWORD	dwHead;
	DWORD	dwChkSum;
	int		State;
};

//sinTrade.h ¿¡¼­ ÀçÁ¤ÀÇ
#define _MAX_TRADE_ITEM			20

struct TRANS_TRADE_ITEMKEY	{
	int size,code;
	DWORD	dwSender;
	DWORD	dwRecver;
	DWORD	dwSum;

	DWORD	dwItemCode[_MAX_TRADE_ITEM];
	DWORD	dwItemKey[_MAX_TRADE_ITEM];
	DWORD	dwItemSum[_MAX_TRADE_ITEM];

	int		Money;
};


#define	TRADE_RECV_ITEMS_MAX				32

//±¸Á¶Ã¼ Çì´õ »çÀÌÁî
#define	TRANS_RECORD_TRADE_DEFSIZE		(sizeof(int)*16)

struct TRANS_RECORD_TRADE_ITEMS {
	int		size,code;
	int		Money;
	int		ThrowItemCount;
	char	szTradeUserName[32];			//»ó´ë¹æ Ä³¸¯¸í
	int		Temp[4];

	_TRANS_RECORD_TRADE_ITEM	Items[TRADE_RECV_ITEMS_MAX];
};


#define TRANS_ITEM_MAX			16

//¾ÆÀÌÅÛ Á¤º¸
struct smTRANS_ITEMS
{
	int size,code;

	int state;
	int Count;

	TRANS_ITEM	Items[ TRANS_ITEM_MAX ];
};

//¾ÆÀÌÅÛ Á¤º¸
struct smTRANS_ACITON_ITEM
{
	int size,code;

	int state;

	int			x,y,z;
	void		*lpStgArea;
};
//»óÁ¡ ¾ÆÀÌÅÛ Á¤º¸
struct smTRANS_SELL_ITEM {
	int size,code;
	int	ItemKind;					//°ø°Ý / ¹æ¾î /±âÅ¸ µîµîÀÇ ±¸ºÐ
	int	ItemCounter;				//ÆÇ¸Å ¾ÆÀÌÅÛÀÇ ¼ö
	int	Ext[4];						//¿¹ºñ
};

//¾ÆÀÌÅÛ ±³È¯ Ã¢
#define TRANS_TRADE_BUFF_SIZE		4000
struct TRANS_TRADEITEMS {
	int size,code;
	DWORD	dwSender;
	DWORD	dwRecver;
	DWORD	dwSum;
	DWORD	Temp[4];

	BYTE	TradeBuff[TRANS_TRADE_BUFF_SIZE];
};

#define	SOD_RESULT_MAX	32

struct	_SOD_RESULT {
	char		szName[32];
	void	*lpPlayInfo;
	int			JobCode;
	int			Class;
	int			Score;
	int			Monster;
	DWORD		dwTemp[4];
};

//SoD ¼øÀ§ Á¤º¸
struct	TRANS_SOD_RESULT {
	int	size,code;

	DWORD	dwGameCode;
	DWORD	dwGameTime;
	DWORD	dwDisplayMode;
	short	TeamRound[2];

	DWORD	dwTemp[15];

	int		ResultCount;

	_SOD_RESULT	Result[SOD_RESULT_MAX];
};



//////// ¼­¹ö¿Í Å¬¶óÀÌ¾ðÆ®ÀÇ µ·,°æÇèÄ¡ ¼öÄ¡ Á¶È¸ //////////
struct	sSERVER_MONEY {
	int	InputMoney;
	int	Counter;
	int	TotalX;
	int	TotalY;
	int	TotalZ;
};

struct sSERVER_EXP {
	int	Counter;
	int	InputExp;
	int	Total1;
	int	Total2;
};

struct TRANS_TOTAL_EXPMONEY {
	int	size,code;

	sSERVER_MONEY	sServerMoney;
	sSERVER_EXP		sServerExp;
};

//µ¥ÀÌÅ¸ ¼­¹ö·Î Å¬¶óÀÌ¾ðÆ® °æÀ¯ Àü¼Û
struct	TRANS_SEND_DATASERVER {
	int size,code;
	char	szBuff[1024];
};


//¾ÆÀÌÅÛ ±¸ÀÔ¿ë ±¸Á¶Ã¼
struct	TRANS_BUY_SHOPITEM {
	int	size,code;

	ItemData	sItem;			//±¸ÀÔÇÏ´Â ¾ÆÀÌÅÛ
	int		ItemCount;		//±¸ÀÔÇÏ´Â ¾ÆÀÌÅÛ °¹¼ö
};



//°Å·¡½Ã ¾ÆÀÌÅÛ º¸³½ÈÄ º¸³½ ¾ÆÀÌÅÛÀÌ ÀÎº¥¿¡ Á¸Àç ÇÏ´ÂÁö È®ÀÎ
struct	_TRANS_USINGITEM {
	DWORD	dwCode;
	short	Performance[8];
};

struct	TRANS_USINGITEM {
	int	size,code;
	int	ItemListCount;
	_TRANS_USINGITEM	ItemList[16];
};


#define	PARTY_STATE_NONE		0
#define	PARTY_STATE_MASTER		1
#define	PARTY_STATE_MEMBER		2


struct _PARTY_USER 
{
	char	szName[32];				//ÀÌ¸§
	char	szModelName[64];		//¸ðµ¨ ÀÌ¸§
	char	szModelName2[64];		//¸ðµ¨ ÀÌ¸§2

	DWORD	dwObjectSerial;			//°´Ã¼ °íÀ¯¹øÈ£
	DWORD	Level;
	short	Life[2];
	DWORD	Class;
	int		x,z;
};

struct TRANS_PARTY_USERS {
	int		size,code;

	DWORD	dwObjectSerial;
	DWORD	dwTemp[8];

	int		PartyUserCount;

	_PARTY_USER		PartyUser[PARTY_PLAYER_MAX];
};

struct _PARTY_PLAYINFO
{
	DWORD	dwObjectSerial;			//°´Ã¼ °íÀ¯¹øÈ£
	DWORD	Level;					//µÈ¼¶
	short	Life[2];				//ÉúÃü
	DWORD	Class;
	int		x,z;
};

struct	TRANS_PARTY_PLAYINFO 
{
	int		size,code;

	DWORD	dwObjectSerial;
	DWORD	dwTemp;

	int		PartyUserCount;

	_PARTY_PLAYINFO	PlayInfo[PARTY_PLAYER_MAX];
};

struct	TRANS_PARTY_SKILL {
	int		size,code;
	DWORD	dwSkillCode;
	int		Point;
	int		wParam;
	int		lParam;
	int		sParam;
	int		eParam;
	int		PartyCount;
	DWORD	dwPartyUser[8];
};

struct TRANS_CLAN_COMMAND_USER {
	int size,code;
	int	Param[4];
	int	UserCount;

	char	szUserBuff[2048];
};

#define	CLAN_USER_MAX	64

struct _CLAN_USER_INFO {
	char		szName[32];
	DWORD		dwSpeedSum;
	DWORD		dwObjectSerial;
	void	*lpPlayInfo;
};

struct	rsCLAN_INFOMATION {
	DWORD	dwClanCode;
	DWORD	dwTemp[32];

	_CLAN_USER_INFO	ClanUserInfo[CLAN_USER_MAX];
};
struct	TRANS_WAREHOUSE 
{
	int size,code;

	DWORD	dwChkSum;
	WORD	wVersion[2];
	int		WareHouseMoney;
	DWORD	dwTemp[5];

	int		DataSize;
	BYTE	Data[sizeof(ItemData)*100+256];
};
struct TRANS_CARAVAN
{
	int		size,code;
	DWORD	dwChkSum;
	WORD	wVersion[2];

	int		DataSize;
	BYTE	Data[sizeof(ItemData) * 100 + 256];
};

#define	TRANS_SERVER_MAX		8

//¼­¹ö Á¤º¸
struct _TRANS_SERVER_INFO {
	char	szServerName[32];
	char	szServerIp1[20];
	char	szServerIp2[20];
	char	szServerIp3[20];

	DWORD	dwServerPort1;
	DWORD	dwServerPort2;
	DWORD	dwServerPort3;

	DWORD	ConnState;
};

struct TRANS_SERVER_LIST
{
	int size,code;

	char szServerName[16];

	DWORD dwServerTime_t;
	int		ClanTicket;
	int	dwTemp[1];
	int	ClanServerCount;
	int	ServerCount;
	_TRANS_SERVER_INFO ServerInfo[TRANS_SERVER_MAX];
};

#define	SERVER_MAP_MAX		64

struct	TRANS_SEVER_MAP {
	int size,code;

	DWORD	dwTemp[30];

	int		IP_Count;
	DWORD	dwIP[SERVER_MAP_MAX];
};

struct	TT_DATA_SERVER_INFO {
	char	szServerID[16];
	char	szServerPath[128];
};

struct sEVENT_CASTLE_EXPUP
{
	int MinLevel;
	int MaxLevel;
	int TimeDelay;
};

#define	SYSTEM_IP_MAX			32
#define	LOGIN_IP_MAX			16
#define	DISABLE_IP_MAX			500
#define	ENABLE_IP_MAX			100
#define	ADMIN_IP_MAX			16
#define CLAN_SERVER_MAX			3
#define ENABLE_MODULE_CHECK_MAX	64	
#define	TT_DATA_SERVER_MAX		16

//¼­¹ö ¼³Á¤ ±¸Á¶
struct rsSERVER_CONFIG	{

	DWORD	ServerCode;
	DWORD	AutoPlayer;
	DWORD	DisableParty;		//µ¿·á±ÝÁö
	DWORD	EnablePlayerKill;	//PKÇã°¡
	DWORD	ConnectUserMax;		//ÃÖ´ë Á¢¼Ó Çã°¡ ÀÎ¿ø

	int		TestSeverMode;		//Å×½ºÆ® ¼­¹ö¿ë

	int		UseRecorMemory;		//ÀúÀåµ¥ÀÌÅ¸ ¸Þ¸ð¸® ¹öÆÛ»ç¿ë
	int		PotionMonitor;		//¹°¾à °¨½Ã

	int		ClientCheckSumCount;	//Å¬¶óÀÌ¾ðÆ® Ã¼Å©¼¶ Ä«¿îÅÍ
	int		ClientCheckOut;			//¹®Á¦ Å¬¶óÀÌ¾ðÆ® Á¢¼Ó Á¾·á
	DWORD	dwClientCheckSum[32];	//Á¢¼Ó °¡´ÉÇÑ Ã¼Å©¼¶ ¸ñ·Ï

	int		SafeClientCodeCount;	//Å¬¶óÀÌ¾ðÆ®ÀÇ Æã¼ÇÃ½Å© ÄÚµåÄ«¿îÆ®
	int		ClientCodeCheckOut;		//Æã¼Ç¹®Á¦ Å¬¶óÀÌ¾ðÆ® Á¢¼Ó Á¾·á
	DWORD	dwSafeClientCode[32];	//Å¬¶óÀÌ¾ðÆ®ÀÇ Æã¼ÇÃ½Å© ÄÚµå

	int		LimitVersion;			//Á¢¼Ó °¡´ÉÇÑ ÃÖÇÏ ¹öÀü
	int		LimitVersionMax;		//Á¢¼Ó °¡´ÉÇÑ ÃÖ»ó ¹öÀü
	char	szAdminPassword[3][32];	//°ü¸®ÀÚ ±ÇÇÑ ºÎ¿© ÆÐ½º¿öµå
	char	szAdminName[32];		//°ü¸®ÀÚ ÀÌ¸§

	char	szAdminIP[16];			//°ü¸®ÀÚ IP
	char	szAdminLogPassword[32];	//°ü¸®ÀÚ Password

	char	szServerName[64];		//¼­¹ö ÀÌ¸§
	int		Enable_PK;				//PKÇã°¡
	int		CheckProtect;			//nProtect ¼ö½Ã·Î °Ë»çÀ¯¹«
	DWORD	RemoveNProtectTime;		//°ÔÀÓÁß¿¡ nProtectÁ¦°Å ½Ã°£

	char	szDebugIP[10][32];		//µðºñ±ë¿ë IP
	int		DebugIP_Count;			//µð¹ö±ë IP Ä«¿îÅÍ

	char	szDebugID[32][32];		//µð¹ö±ë¿ë ID
	int		DebugID_Count;			//µð¹ö±ë¿ë ID Ä«¿îÅÍ

	int		BlockLevel;				//ID ÀÓ½Ã ºí·°ÀÇ ·¹º§
	int		BlockLevel_LogOut;		//·Î±× ¾Æ¿ô½Ã¿¡¸¸ Àû¿ë( Áß±¹Ãø ¿ä±¸ )
	int		ItemCodeOut;			//¾ÆÀÌÅÛ ÄÚµå ¿À·ù½Ã Á¾·á

	int		ClientFuncCheckMode;	//Å¬¶óÀÌ¾ðÆ® Æã¼Ç °Ë»ç ¸ðµå
	int		Enable_PartyItem;		//µ¿·á°¡ È¹µæÇÑ ¾ÆÀÌÅÛ Ãâ·Â
	int		CharLevel;				//ÉèÖÃ½ÇÉ«µÈ¼¶
	
	int		Event_Mandoo;			//¸¸µÎ(¼ÛÆí) ÀÌº¥Æ®
	int		Event_HardCore;			//ÇÏµåÄÚ¾î ÀÌº¥Æ®
	int		Event_DamageOff;		//°ø°Ý·Â È°ÀÎ ÀÌº¥Æ®

	int		Event_DefenseOff;		//¸ó½ºÅÍ ¹æ¾î·Â ¾àÈ­ ÀÌº¥Æ®
/////////////////////////////////////////////////////////////////////////////////////////
	int		Event_Child;			//¾î¸°ÀÌ ÀÌº¥Æ®
	int		Event_Cristal;			//Å©¸®½ºÅ» ÀÌº¥Æ® ( Æ¯Á¤ ½Ã°£´ë¿¡ Å©¸®½ºÅ» ¸ó½ºÅÍ °­È­ )
	int		Event_Potion;			//¹°¾à ÀÌº¥Æ® ( ¹°¾à µ¿½Ã¿¡ ¶³¾îÁö´Â °¹¼ö Áõ°¡ )
	int		Event_StarPointTicket;	//º°Æ÷ÀÎÆ® ÀÌº¥Æ® ( º°»óÇ°±Ç ¹ß»ý )
	int		Event_ValentineDay;		//¹ß·»Å¸ÀÎ µ¥ÀÌ ÀÌº¥Æ®
	int		Event_WhiteDay;			//È­ÀÌÆ® µ¥ÀÌ ÀÌº¥Æ®
	int		Event_MorifSheltom;		//¸ð¸®ÇÁÀÇ ½©ÅÒ Å»Ãë ÀÌº¥Æ®
	int		Event_MollyWolf;		//¸ô¸®¿Í´Á´ë ÀÌº¥Æ®
	int		Event_Ghost;			//°í½ºÆ® ÀÌº¥Æ®
	int		Event_SantaGoblin;		//»êÅ¸°íºí¸° ÀÌº¥Æ®
	int		Event_WorldCup;			//¿ùµåÄÅ ÀÌº¥Æ®
	int		Event_ExpUp;			//°æÇèÄ¡¾÷ ÀÌº¥Æ®
	int		Event_CoupleRing;		// pluto Ä¿ÇÃ¸µ ÀÌº¥Æ®
	int		Event_Watermelon;		// ¹ÚÀç¿ø - ¼ö¹Ú ÀÌº¥Æ®
	int		Event_Star;				// ¹ÚÀç¿ø - ¹ãÇÏ´ÃÀÇ ¼Ò¿øÀÌº¥Æ®
	int		Event_Valentine;		// Àåº° - ¹ß·»Å¸ÀÎ ÀÌº¥Æ®
	int		Event_PristonAlphabet;	// ¹ÚÀç¿ø - ¾ËÆÄºª Á¶ÇÕ ÀÌº¥Æ®
	int		Event_WhiteContrast;	// Àåº° - È­ÀÌÆ®ÄÜÆ®¶ó½ºÆ® ÀÌº¥Æ®
	int		Event_Candydays;		// Àåº° - Äµµðµ¥ÀÌÁî
	int		Event_BlackSmith;		// Àåº° - ´ëÀåÀåÀÌÀÇ È¥
	int		Event_MagicalGreen;	// Àåº° - ¸ÅÁöÄÃ±×¸°
	int		Event_TearOfKara;		// Àåº° - Ä«¶óÀÇ ´«¹°
	int		Event_WarerMelonMonster;		// Àåº° - ¼ö¹Ú¸ó½ºÅÍ ÀÌº¥Æ®
	int		Event_Chichen_Day;		// ¹ÚÀç¿ø - º¹³¯ ÀÌº¥Æ®(¾Æ±â ²¿°í ¸ó½ºÅÍ°¡ ³ªÅ¸³­´Ù)
	int		Event_MovieBloodyBattle; // Àåº° - ¿µÈ­ Ç÷Åõ
	int		Event_SummerChicken;	//»ï°èÅÁ ÀÌº¥Æ®
	int		Event_GiftBox;			// pluto ¼±¹°»óÀÚ ÀÌº¥Æ®
	int		Event_Weath;			// ÏÂÓêË¢¹ÖÎï
	int		Event_Monster_HP;		// 	¹ÖÎïµÄHP»î¶¯

	sEVENT_CASTLE_EXPUP Event_Castle_Expup[10]; //³ÇÀï»ñµÃ¾­Ñé;

	int		Event_ExpUpCount;		// ×ÜÊý±äÁ¿

	int		BlessCastleMode;			//ºí·¹½ºÄ³½½ ¼³Á¤
	short	sBlessCastle_StartTime[2];	//ºí·¹½ºÄ³½½ ½ÃÀÛ ½Ã°£ ¿¹¾à [0]¿äÀÏ [1]½Ã°£

	int		Event_Fruit;				//¹ûÊµ

	int		FieldCount;					//µØÍ¼Í³¼Æ

	int		Record_JobChanger;		//Àü¾÷ÇÑÀÚ ±â·Ï
	int		ForeverBlockMode;		//¿µ¿øÇÑ ºí·°

	int		Permit_Exp;				//Çã¿ë¿ÀÂ÷ °æÇèÄ¡
	int		Permit_Money;			//Çã¿ë¿ÀÂ÷ µ·

	int		ClientProcessTimeChk;	//Å¬¶óÀÌ¾ðÆ® ÇÁ·Î¼¼½º ½Ã°£°¨½Ã ÃÖ´ëÄ¡
	int		ClientProcessTimeChkOut;//Å¬¶óÀÌ¾ðÆ® ÇÁ·Î¼¼½º ½Ã°£ ÃÊ°ú½Ã ¿¬°áÁ¾·á
	int		Dis_PotionError;		//Æ÷¼Ç ¿¡·¯³ª¸é ¿¬°á ²öÀ½

	int		ExpFixMode;				//¿À·ù °æÇèÄ¡ º¸Á¤

	char	szBlockUserPath[64];	//À¯Àú ºí·° µ¥ÀÌÅ¸ °æ·Î

	int		DispBillingTime;		//ºô¸µ ³²Àº½Ã°£ Ç¥½Ã

	int		Disable_LogIn;			//·Î±×ÀÎ ±ÝÁö
	int		Disable_LogQue;			//·Î±×Å¥ Ã³¸® ±ÝÁö
	int		Disable_CheckLogOut;	//·Î±×¾Æ¿ô Å¥°Ë»ç ±ÝÁö

	int		Disable_LogIn2;			//·Î±×ÀÎ ±ÝÁö2¹øÂ° ½Å±Ô ·Î±×ÀÎ¸¸ ±ÝÁö
	int		Disable_PCBang;			//PC¹æ ±ÝÁö ¸ðµå

	int		ExpGameTimeMode;		//°æÇèÄ¡ ½Ã°£º° ºÐ¹è(º£Æ®³²)

	int		ChageJobLevel;			// ×¨Ö°µÈ¼¶

	int		GamePort;				// ÓÎÏ·¶Ë¿Ú

	int		ServerInventoryMode;	//¼­¹öÀÇ °¡»óÀÎº¥Åä¸®·Î ¾ÆÀÌÅÛ °ü¸®

	DWORD	DisableIP[DISABLE_IP_MAX][2];		//Á¢±Ù Á¦ÇÑ IP
	int		DisableIP_Count;					//Á¢±Ù Á¦ÇÑ IP ¼³Á¤ ¼ö

	DWORD	EnableIP[ENABLE_IP_MAX][2];			//Á¢±Ù Á¦ÇÑ IPÁß Çã°¡µÇ´Â IP
	int		EnableIP_Count;						//Á¢±Ù Á¦ÇÑ IP ¼³Á¤ ¼ö

	DWORD	AdminIP[ADMIN_IP_MAX][2];			//°ü¸®ÀÚ IP ¸ñ·Ï
	int		AdminIP_Count;						//°ü¸®ÀÚ IP ¼³Á¤ ¼ö

	DWORD	SystemIP[SYSTEM_IP_MAX][2];			//½Ã½ºÅÛ IP ¸ñ·Ï
	int		SystemIP_Count;						//½Ã½ºÅÛ IP ¼³Á¤ ¼ö

	DWORD	LoginServerIP[LOGIN_IP_MAX][2];		//·Î±ä¼­¹ö IP ¸ñ·Ï
	int		LoginServerIP_Count;				//·Î±ä¼­¹ö IP ¼³Á¤ ¼ö

	char	szBackupPath[80];					//*¹é¾÷Æú´õÀÌ¸§

	char	szClanServerIP[CLAN_SERVER_MAX][20];	//Å¬·£ ¼­¹ö	ÁÖ¼Ò
	int		ClanServerPort[CLAN_SERVER_MAX];		//Å¬·£ ¼­¹ö Æ÷Æ®
	int		ClanServerCount;


	DWORD	Enable_ClientModule[ENABLE_MODULE_CHECK_MAX];	//Å¬¶óÀÌ¾ðÆ® ¸ðÆ«Ã½Å©¼¶
	int		Enable_ClientModuleCount;						//Å¬¶óÀÌ¾ðÆ® ¸ðµâ Ã½Å©¼¶ Ä«¿îÅÍ

	int		Disable_DecSkillPoint;							//½ºÅ³ Æ÷ÀÎÆ® °¨¼Ò Ã½Å© Ã³¸®

	int		Disable_Quest;									//±ÝÁö Äù½ºÆ® ¼³Á¤

	int		CrazyPacketMode;							//º¸¾È ÆÐÅ¶ ¸ðµå

	char	szNoticeURL[256];							//Notice URL ¼³Á¤


	TRANS_SEVER_MAP	AreaServer;							//Áö¿ªº° ¼­¹ö ¸ÅÇÎ

	char	szLinkServerIP[32];							//¸µÅ©µÈ ¼­¹ö IP

	int		RecordAdminCommand;							//¿î¿µÀÚ ¸í·É ±â·Ï

	int		FreeLevel;									//¹«·á ·¹º§
	char	szFreeGpCode[32];							//¹«·á»ç¿ë GPCODE
	int		PresentLevel;								//¼±¹°ÁÖ´Â ·¹º§
	int		Event_ComicBirthDay;						//»ýÀÏ¼±¹° ¾óÅ«ÀÌ
	int		Event_Puzzle;								//ÆÛÁñ ¸ÂÃß±â ÀÌº¥Æ®
	int		Event_BabelHorn;							//¹Ùº§»ÔÀÌº¥Æ®
	int		Event_NineFox;								//±¸¹ÌÈ£ÀÌº¥Æ®
	int		EVENT_Christmas;							//Å©¸®½º¸¶½º ÀÌº¥Æ®
	int		EventPlay_BitMask;							//ÀÌº¥Æ® ÇÃ·¹ÀÌ ºñÆ®¸¶½ºÅ©
	int		Event_PCBangPet;							//PC¹æ Æê ÀÌº¥Æ®

	int		StartUser_PresentItem;						//½ÃÀÛÀ¯Àú¿¡°Ô ¼±¹° ÁÖ±â

	int		GameGuard_Auth;								//°ÔÀÓ°¡µå º¸¾È ¼³Á¤

#ifdef _XTRAP_GUARD_4_
	int		XTRAP_Timer;								//XTRAP °Ë»çÁÖ±â		XTRAP_GUARD
	int		XTRAP_MaxDealy;								//XTRAP °Ë»çÁöÃ¼ Á¦ÇÑÄ¡  XTRAP_GUARD
#endif

	//Åä³Ê¸ÕÆ®¼­¹ö °èÁ¤ °ü¸®
	int		TT_DataServer_Count;									//Åä³Ê¸ÕÆ®¼­¹ö µ¥ÀÌÅ¸ °æ·Î °¹¼ö
	TT_DATA_SERVER_INFO		TT_DataServer[TT_DATA_SERVER_MAX];		//Åä³Ê¸ÕÆ®¼­¹ö µ¥ÀÌÅ¸ Á¤º¸

	int		FixedStartField;							//½ÃÀÛ ÇÊµå °­Á¦ °íÁ¤½ÃÅ°±â
	int		DisableThrowItem;							//¾ÆÀÌÅÛ ¶¥¿¡ ¸ø¹ö¸²

	int		CheckPlayField;								//Å¬¶óÀÌ¾ðÆ® ¿Í ¼­¹öÀÇ  ÇÊµå ÁöÇü ºñ±³ °Ë»ç

	int		Enable_PKField;								// PKÇã¿ë ÇÊµå ¹øÈ£

	int		Enable_PKField_All;							// pluto PKÇã¿ë ÇÊµå ÀüºÎ

	//½ºÅ²ÇÙ ¹æÁö
	int		CheckModelFile;								//¸ðµ¨ÆÄÀÏ È®ÀÎ ¿É¼Ç

	bool	bPK_LOG;
	rsSERVER_CONFIG()
	{
		bPK_LOG = false;
	};
};

//¼­¹ö ±âµ¿ 
extern int	ServerMode;

Unit *Serv_CheckOtherPlayPosi( int x, int y, int z );

//°æÇèÄ¡¿Í µ·ÀÇ °á°ú ÇÑ°èÄ¡ ( ÀÌÇÑ°è¸¦ ³Ñ¾î°¡¸é ÀúÀåÀÌ ¾ÈµÈ´Ù )
#define	TOTAL_CHECK_MONEY_MAX		52000
#define	TOTAL_CHECK_EXP_MAX			100000




/////////////////// Å¬¶óÀÌ¾ðÆ® Æã¼Ç À§Ä¡ ±¸Á¶Ã¼ ////////////////////////
#define	dwFUNC_VALUE_MAX	64

struct	sFUNC_VALUE {
	DWORD	dwFunc;
	DWORD	dwLen;
	DWORD	dwChkSum;
};

struct	TRANS_CLIENT_FUNPOS {
	int	size,code;

	int	ClientVersion;

	DWORD	dwFunc_CheckMemSum;
	int		FuncCount;

	sFUNC_VALUE	dwFuncValue[dwFUNC_VALUE_MAX];
};


struct	TRANS_FUNC_MEMORY	{
	int		size,code;
	int		Param[8];
	char	szData[6000];
};


struct	sCHK_POTION_COUNT  {
	int	Ps101;
	int	Ps102;
	int	Ps103;
	int	Ps104;

	int	Pm101;
	int	Pm102;
	int	Pm103;
	int	Pm104;

	int	Pl101;
	int	Pl102;
	int	Pl103;
	int	Pl104;
};

//SOD Á¡¼ö Ãâ·Â
struct	sSOD_SCORE {
	int		Flag;
	DWORD	dwDispTime;
	int		Score;
	int		MyTeam;
	int		TeamScore[4];
	int		Round;
	DWORD	dwPlayTime;

	/////// SOD ¿¬Ãâ ÀÌº¥Æ® /////////

	DWORD	dwSoD_NextStageTime;		//´ÙÀ½ ½ºÅ×ÀÌÁö ³Ñ¾î°¡´Â ½Ã°£
	int		SodNextStageNum;			//³Ñ¾î°¥ ½ºÅ×ÀÌÁö ¹øÈ£
	int		NextRound;
	DWORD	dwSoD_CloseStageTime;		//È­¸éÀº ´Ý´Â ÀÌÆåÆ® Àû¿ë½Ã°£

	///////// SOD ¿¹¾à ¿¬Ãâ //////////////
	int		EffectStartCount;			//ÀÌÆåÆ® ½ÃÀÛ±îÁöÀÇ Ä«¿îÅÍ
	int		EffectCode;					//ÀÌÆåÆ® ÄÚµå

	//////// SOD µæÁ¡ È¿°ú /////////////
	int		ScoreEffectCount;				//µæÁ¡ È¿°ú

};



#define	CHAR_EVENT_STARPOINT		300

#define	ITEM_UNIQUE_CODE_NORMAL		1
#define	ITEM_UNIQUE_CODE_QUEST		2


#define BIMASK_PRORATE_USER			1
#define BIMASK_FREE_USER			2
#define BIMASK_VIP_USER				4
#define BIMASK_BIRTHDAY_USER		8
#define BIMASK_TIMELEVEL_USER		16
#define BIMASK_ADULT_USER			32


#define	MONSTER_CLASS_NORMAL		0
#define	MONSTER_CLASS_BOSS			1
#define	MONSTER_CLASS_HAMMER		200
#define	MONSTER_CLASS_GHOST			300

#endif