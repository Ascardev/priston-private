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
// ������ƷЭ��
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

// ����ˮ��Э�� ȡ��ˮ��Э��
#define smTRANSCODE_CRYSTAL_ORB				0x50326011
// ������һ������Э��
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
#define smCOMMAND_PLAY_WEATHER				0x300 //����Э��

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


//ĳ���� ���� ���� ũ��
#define	smCHAR_INFO_QUICK_SIZE		192
#define	smCHAR_INFO_QUICK_SIZE2		352

#define	THROW_ITEM_INFO_MAX		64
#define	THROW_ITEM_INFO_MASK	63
#define	INVEN_ITEM_INFO_MAX		300


//ĳ���� ��ǥ ����
struct rsPLAYPOS {
	DWORD	Area;		// Low->Wolrd High->Area	: ���� �����ϰ� �ִ� ������ ��ġ �ڵ�
	int		x,y,z;		// ��ǥ
};

//���� : �ڽ��� ��ġ�� ������ ������ ����
//��� : Ŭ���̾�Ʈ -> ����
//�ڵ� : smTRANSCODE_POSITION
//10�� �������� ������ �������� �÷��̾� ��ġ ����
struct TRANS_PLAYPOS {
	int size,code;
	
	rsPLAYPOS	rsPlayPos;
	short Hp[2];
};



//���� : ������� ���� ������ ������
//��� : Ŭ���̾�Ʈ -> ����  Ŭ���̾�Ʈ -> Ŭ���̾�Ʈ
//�ڵ� : smTRANSCODE_ATTACKDATA
struct TRANS_ATTACKDATA
{
	int size,code;

	DWORD	dwDestObjectSerial;	//�����ϴ� ĳ���� ������ȣ
	DWORD	dwTarObjectSerial;	//���ݴ�� ĳ���� ������ȣ

	int		x,y,z;			// ��ǥ
	int		AttackState;	// �Ӽ�
	int		AttackSize;		// ���� ����
	int		Power;
	int		PowerType;
	DWORD	dwChkSum;

	short	sRating[2];	//[0]-���� [1]-���߷�
	DWORD	dwDamageChkSum;
};

struct TRANS_ATTACKDATA2 {
	int size,code;

	DWORD	dwChkSum;

	DWORD	dwDestObjectSerial;	//�����ϴ� ĳ���� ������ȣ
	DWORD	dwTarObjectSerial;	//���ݴ�� ĳ���� ������ȣ

	int		x,y,z;			// ��ǥ
	int		AttackState;	// �Ӽ�
	int		AttackSize;		// ���� ����
	short	Power[2];		// ���� �Ŀ�
	short	Power2[2];		// ���� �Ŀ� ( �߰� ���� )
	short	Critical[2];	// ũ��Ƽ��
	int		SkillCode;		// ��ų�ڵ�
	DWORD	dwTime;			// Ŭ���̾�Ʈ �ð�
	int		AttackCount;	// ���� ī����
	short	MotionCount[2];	// ���� ��� ī����
	DWORD	dwWeaponCode;	// �� ���� ����
	short	Area[2];		// ����
	int		Temp[4];		// ����
};


// �庰 - ������ ��ų( 32 -> 42 )
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

	DWORD	dwDestObjectSerial;	//�����ϴ� ĳ���� ������ȣ

	DWORD	dwChkSum;

	int		x,y,z;			// ��ǥ
	int		AttackState;	// �Ӽ�
	int		AttackSize;		// ���� ����
	short	Power[2];		// ���� �Ŀ�
	short	Power2[2];		// ���� �Ŀ� ( �߰� ���� )
	short	Critical[2];	// ũ��Ƽ��
	int		SkillCode;		// ��ų�ڵ�
	DWORD	dwTime;			// Ŭ���̾�Ʈ �ð�
	int		AttackCount;	// ���� ī����
	short	MotionCount[2];	// ���� ��� ī����
	DWORD	dwWeaponCode;	// �� ���� ����
	short	Area[2];		// ����
	int		Temp[4];		// ����

	DWORD	dwMainTargetObject;		//�� Ÿ��

	int	TargetCount;
	DWORD	dwTarObjectSerial[SKIL_ATTACK_CHAR_MAX];	//���ݴ�� ĳ���� ������ȣ
};



struct TRANS_AREAINFO_HEADER {
	int		size;
	int		code;
	DWORD	dwIP;
	int		Stats;					//���� �Ϸ�� TRUE ���� �� ���� ����Ÿ�� ������ FALSE
	int		TransListCnt;			//�����ϴ� TRANS_IPLIST ����
};
struct TRANS_IPLIST {
	DWORD	dwIP;
	rsPLAYPOS	Pos;
};


#define	srPLAYBUFF_MAX		4
#define	srPLAYBUFF_MASK		3

#define	PARTY_PLAYER_MAX		6

// �庰 - �������
#define	srRECORD_DEFAULT_SIZE	16384
//#define	srRECORD_DEFAULT_SIZE	32768
#define	srRECORD_MEMORY_SIZE	24576
//#define	srRECORD_MEMORY_SIZE	49152

#define SKILL_POINT_COLUM_MAX	20

struct	TRANS_PARTY_PLAYINFO;

struct	npGAME_GUARD_AUTH_INFO {
	 DWORD	Auth_Value;		//���Ӱ��� Ȯ���ڵ� ( ���� ���� ���� )
	 DWORD	Auth_Time;		//���Ӱ��� Ȯ�νð� ( ����ó�� �ð� )
	 DWORD	Auth_Count;		//���Ӱ��� Ȯ��ī���� ( �� ���� Ƚ�� )
	 DWORD	Auth_Retry;		//���Ӱ��� Ȯ�� ��õ� ( ������ 60�� �ȿ� �ȿ��� ������� ��õ� )
};

//������ ���� ī����
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

//����� - XignCode
#define PACKET_SIZE 512


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

//���� : ä�� ���ڿ� ���� �ڵ�
//��� : Ŭ���̾�Ʈ <-> ����
//�ڵ� : smTRANSCODE_CHATMESSAGE
struct TRANS_CHATBUFF {
	int		size;
	int		code;
	DWORD	dwIP;
};
struct CHATBUFF {
	DWORD	dwIP;
	char szMessage[256];
};

struct TRANS_CHATMESSAGE 
{
	int		size;
	int		code;
	DWORD	dwIP;
	DWORD	dwObjectSerial;

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

	int	x,y,z;				//���� ��ǥ
	int ax,ay,az;			//���� ����
	int state;				//�Ӽ�

	CharacterData	sCharacterData;
};


//������ �ڸ�� ���ۿ� ����
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

	int SParam; //1
	int EParam; // 2

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



//�Ӽ� ȣ��
struct smTRANS_RESISTANCE {
	int	size;
	int code;
	int	Param;
	short Resistance[8];
	int	Absorb;
};


//����
struct smTRANS_BLESSCASTLE {
	smTRANS_COMMAND		smTransCommand;
	int				TaxRate;
	short			Tower[12];		//Ÿ������	
	unsigned char	MercenaryNum[4];	//int		MercenaryType;	//�뺴����
	int				ClanSkill;		//Ŭ����ų
	int				Price;
	DWORD			dwMasterClan;	//����Ŭ��
	int				Temp[4];
};

//���ݼ��� ��10
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

/////////////// �������� �׷����� ��� ���� /////////////////////

/*
/////������ ������ ������ ����ü 
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


//������ �׷����� ����
#define	TRANS_GROUPITEM_MAX		16
#define	TRANS_GROUPITEM_HEADER_SIZE		(14*4)

//������ Ǭ���
struct	TRANS_ITEMINFO_GROUP {
	int	size,code;

	int Index;
	int Result;
	int Money;
	int	ItemCount;

	DWORD	dwTemp[8];

	Item	sItemInfo[TRANS_GROUPITEM_MAX];
};

//��������
struct	TRANS_ITEMINFO_GROUP2 {
	int	size,code;

	int Index;
	int Result;
	int Money;
	int	ItemCount;

	DWORD	dwTemp[8];

	char	szBuff[ sizeof(Item) * TRANS_GROUPITEM_MAX ];
};


//���� ������ ����
struct TRANS_ITEMINFO {
	//------------------------------------------------------------------< _ignore_bug_fix_0x00000000_ //�ؿ�
	/*
	TRANS_ITEMINFO()  // ������
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

	DWORD	dwSeCode[4];		//���� �ڵ�
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
//����ü ��� ������
#define	TRANS_THROW_ITEMS_DEFSIZE	(sizeof(int)*4)

struct TRANS_THROW_ITEMS {
	int		size,code;
	int		ThrowItemCount;
	int		Temp;

	_TRANS_THROW_ITEM	ThrowItems[THROW_ITEMS_MAX];
};



//�ŷ��� ������ ����
struct _TRANS_RECORD_TRADE_ITEM {
	DWORD	dwCode;
	DWORD	dwHead;
	DWORD	dwChkSum;
	int		State;
};

//sinTrade.h ���� ������
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

//����ü ��� ������
#define	TRANS_RECORD_TRADE_DEFSIZE		(sizeof(int)*16)

struct TRANS_RECORD_TRADE_ITEMS {
	int		size,code;
	int		Money;
	int		ThrowItemCount;
	char	szTradeUserName[32];			//���� ĳ����
	int		Temp[4];

	_TRANS_RECORD_TRADE_ITEM	Items[TRADE_RECV_ITEMS_MAX];
};


#define TRANS_ITEM_MAX			16

//������ ����
struct smTRANS_ITEMS
{
	int size,code;

	int state;
	int Count;

	TRANS_ITEM	Items[ TRANS_ITEM_MAX ];
};

//������ ����
struct smTRANS_ACITON_ITEM
{
	int size,code;

	int state;

	int			x,y,z;
	void		*lpStgArea;
};
//���� ������ ����
struct smTRANS_SELL_ITEM {
	int size,code;
	int	ItemKind;					//���� / ��� /��Ÿ ����� ����
	int	ItemCounter;				//�Ǹ� �������� ��
	int	Ext[4];						//����
};

//������ ��ȯ â
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
	User	*lpPlayInfo;
	int			JobCode;
	int			Class;
	int			Score;
	int			Monster;
	DWORD		dwTemp[4];
};

//SoD ���� ����
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



//////// ������ Ŭ���̾�Ʈ�� ��,����ġ ��ġ ��ȸ //////////
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

//����Ÿ ������ Ŭ���̾�Ʈ ���� ����
struct	TRANS_SEND_DATASERVER {
	int size,code;
	char	szBuff[1024];
};


//������ ���Կ� ����ü
struct	TRANS_BUY_SHOPITEM {
	int	size,code;

	ItemData	sItem;			//�����ϴ� ������
	int		ItemCount;		//�����ϴ� ������ ����
};



//�ŷ��� ������ ������ ���� �������� �κ��� ���� �ϴ��� Ȯ��
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
	char	szName[32];				//�̸�
	char	szModelName[64];		//�� �̸�
	char	szModelName2[64];		//�� �̸�2

	DWORD	dwObjectSerial;			//��ü ������ȣ
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
	DWORD	dwObjectSerial;			//��ü ������ȣ
	DWORD	Level;					//�ȼ�
	short	Life[2];				//����
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
	User	*lpPlayInfo;
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

//���� ����
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

//���� ���� ����
struct rsSERVER_CONFIG	{

	DWORD	ServerCode;
	DWORD	AutoPlayer;
	DWORD	DisableParty;		//�������
	DWORD	EnablePlayerKill;	//PK�㰡
	DWORD	ConnectUserMax;		//�ִ� ���� �㰡 �ο�

	int		TestSeverMode;		//�׽�Ʈ ������

	int		UseRecorMemory;		//���嵥��Ÿ �޸� ���ۻ��
	int		PotionMonitor;		//���� ����

	int		ClientCheckSumCount;	//Ŭ���̾�Ʈ üũ�� ī����
	int		ClientCheckOut;			//���� Ŭ���̾�Ʈ ���� ����
	DWORD	dwClientCheckSum[32];	//���� ������ üũ�� ���

	int		SafeClientCodeCount;	//Ŭ���̾�Ʈ�� ���ýũ �ڵ�ī��Ʈ
	int		ClientCodeCheckOut;		//��ǹ��� Ŭ���̾�Ʈ ���� ����
	DWORD	dwSafeClientCode[32];	//Ŭ���̾�Ʈ�� ���ýũ �ڵ�

	int		LimitVersion;			//���� ������ ���� ����
	int		LimitVersionMax;		//���� ������ �ֻ� ����
	char	szAdminPassword[3][32];	//������ ���� �ο� �н�����
	char	szAdminName[32];		//������ �̸�

	char	szAdminIP[16];			//������ IP
	char	szAdminLogPassword[32];	//������ Password

	char	szServerName[64];		//���� �̸�
	int		Enable_PK;				//PK�㰡
	int		CheckProtect;			//nProtect ���÷� �˻�����
	DWORD	RemoveNProtectTime;		//�����߿� nProtect���� �ð�

	char	szDebugIP[10][32];		//����� IP
	int		DebugIP_Count;			//����� IP ī����

	char	szDebugID[32][32];		//������ ID
	int		DebugID_Count;			//������ ID ī����

	int		BlockLevel;				//ID �ӽ� ���� ����
	int		BlockLevel_LogOut;		//�α� �ƿ��ÿ��� ����( �߱��� �䱸 )
	int		ItemCodeOut;			//������ �ڵ� ������ ����

	int		ClientFuncCheckMode;	//Ŭ���̾�Ʈ ��� �˻� ���
	int		Enable_PartyItem;		//���ᰡ ȹ���� ������ ���
	int		CharLevel;				//���ý�ɫ�ȼ�
	
	int		Event_Mandoo;			//����(����) �̺�Ʈ
	int		Event_HardCore;			//�ϵ��ھ� �̺�Ʈ
	int		Event_DamageOff;		//���ݷ� Ȱ�� �̺�Ʈ

	int		Event_DefenseOff;		//���� ���� ��ȭ �̺�Ʈ
/////////////////////////////////////////////////////////////////////////////////////////
	int		Event_Child;			//��� �̺�Ʈ
	int		Event_Cristal;			//ũ����Ż �̺�Ʈ ( Ư�� �ð��뿡 ũ����Ż ���� ��ȭ )
	int		Event_Potion;			//���� �̺�Ʈ ( ���� ���ÿ� �������� ���� ���� )
	int		Event_StarPointTicket;	//������Ʈ �̺�Ʈ ( ����ǰ�� �߻� )
	int		Event_ValentineDay;		//�߷�Ÿ�� ���� �̺�Ʈ
	int		Event_WhiteDay;			//ȭ��Ʈ ���� �̺�Ʈ
	int		Event_MorifSheltom;		//������ ���� Ż�� �̺�Ʈ
	int		Event_MollyWolf;		//�����ʹ��� �̺�Ʈ
	int		Event_Ghost;			//��Ʈ �̺�Ʈ
	int		Event_SantaGoblin;		//��Ÿ��� �̺�Ʈ
	int		Event_WorldCup;			//������ �̺�Ʈ
	int		Event_ExpUp;			//����ġ�� �̺�Ʈ
	int		Event_CoupleRing;		// pluto Ŀ�ø� �̺�Ʈ
	int		Event_Watermelon;		// ����� - ���� �̺�Ʈ
	int		Event_Star;				// ����� - ���ϴ��� �ҿ��̺�Ʈ
	int		Event_Valentine;		// �庰 - �߷�Ÿ�� �̺�Ʈ
	int		Event_PristonAlphabet;	// ����� - ���ĺ� ���� �̺�Ʈ
	int		Event_WhiteContrast;	// �庰 - ȭ��Ʈ��Ʈ��Ʈ �̺�Ʈ
	int		Event_Candydays;		// �庰 - ĵ������
	int		Event_BlackSmith;		// �庰 - ���������� ȥ
	int		Event_MagicalGreen;	// �庰 - �����ñ׸�
	int		Event_TearOfKara;		// �庰 - ī���� ����
	int		Event_WarerMelonMonster;		// �庰 - ���ڸ��� �̺�Ʈ
	int		Event_Chichen_Day;		// ����� - ���� �̺�Ʈ(�Ʊ� ���� ���Ͱ� ��Ÿ����)
	int		Event_MovieBloodyBattle; // �庰 - ��ȭ ����
	int		Event_SummerChicken;	//����� �̺�Ʈ
	int		Event_GiftBox;			// pluto �������� �̺�Ʈ
	int		Event_Weath;			// ����ˢ����
	int		Event_Monster_HP;		// 	�����HP�

	sEVENT_CASTLE_EXPUP Event_Castle_Expup[10]; //�����þ���;

	int		Event_ExpUpCount;		// ��������

	int		BlessCastleMode;			//����ĳ�� ����
	short	sBlessCastle_StartTime[2];	//����ĳ�� ���� �ð� ���� [0]���� [1]�ð�

	int		Event_Fruit;				//��ʵ

	int		FieldCount;					//��ͼͳ��

	int		Record_JobChanger;		//�������� ���
	int		ForeverBlockMode;		//������ ��

	int		Permit_Exp;				//������ ����ġ
	int		Permit_Money;			//������ ��

	int		ClientProcessTimeChk;	//Ŭ���̾�Ʈ ���μ��� �ð����� �ִ�ġ
	int		ClientProcessTimeChkOut;//Ŭ���̾�Ʈ ���μ��� �ð� �ʰ��� ��������
	int		Dis_PotionError;		//���� �������� ���� ����

	int		ExpFixMode;				//���� ����ġ ����

	char	szBlockUserPath[64];	//���� �� ����Ÿ ���

	int		DispBillingTime;		//���� �����ð� ǥ��

	int		Disable_LogIn;			//�α��� ����
	int		Disable_LogQue;			//�α�ť ó�� ����
	int		Disable_CheckLogOut;	//�α׾ƿ� ť�˻� ����

	int		Disable_LogIn2;			//�α��� ����2��° �ű� �α��θ� ����
	int		Disable_PCBang;			//PC�� ���� ���

	int		ExpGameTimeMode;		//����ġ �ð��� �й�(��Ʈ��)

	int		ChageJobLevel;			// רְ�ȼ�

	int		GamePort;				// ��Ϸ�˿�

	int		ServerInventoryMode;	//������ �����κ��丮�� ������ ����

	DWORD	DisableIP[DISABLE_IP_MAX][2];		//���� ���� IP
	int		DisableIP_Count;					//���� ���� IP ���� ��

	DWORD	EnableIP[ENABLE_IP_MAX][2];			//���� ���� IP�� �㰡�Ǵ� IP
	int		EnableIP_Count;						//���� ���� IP ���� ��

	DWORD	AdminIP[ADMIN_IP_MAX][2];			//������ IP ���
	int		AdminIP_Count;						//������ IP ���� ��

	DWORD	SystemIP[SYSTEM_IP_MAX][2];			//�ý��� IP ���
	int		SystemIP_Count;						//�ý��� IP ���� ��

	DWORD	LoginServerIP[LOGIN_IP_MAX][2];		//�α伭�� IP ���
	int		LoginServerIP_Count;				//�α伭�� IP ���� ��

	char	szBackupPath[80];					//*��������̸�

	char	szClanServerIP[CLAN_SERVER_MAX][20];	//Ŭ�� ����	�ּ�
	int		ClanServerPort[CLAN_SERVER_MAX];		//Ŭ�� ���� ��Ʈ
	int		ClanServerCount;


	DWORD	Enable_ClientModule[ENABLE_MODULE_CHECK_MAX];	//Ŭ���̾�Ʈ ��ƫýũ��
	int		Enable_ClientModuleCount;						//Ŭ���̾�Ʈ ��� ýũ�� ī����

	int		Disable_DecSkillPoint;							//��ų ����Ʈ ���� ýũ ó��

	int		Disable_Quest;									//���� ����Ʈ ����

	int		CrazyPacketMode;							//���� ��Ŷ ���

	char	szNoticeURL[256];							//Notice URL ����


	TRANS_SEVER_MAP	AreaServer;							//������ ���� ����

	char	szLinkServerIP[32];							//��ũ�� ���� IP

	int		RecordAdminCommand;							//��� ��� ���

	int		FreeLevel;									//���� ����
	char	szFreeGpCode[32];							//������ GPCODE
	int		PresentLevel;								//�����ִ� ����
	int		Event_ComicBirthDay;						//���ϼ��� ��ū��
	int		Event_Puzzle;								//���� ���߱� �̺�Ʈ
	int		Event_BabelHorn;							//�ٺ����̺�Ʈ
	int		Event_NineFox;								//����ȣ�̺�Ʈ
	int		EVENT_Christmas;							//ũ�������� �̺�Ʈ
	int		EventPlay_BitMask;							//�̺�Ʈ �÷��� ��Ʈ����ũ
	int		Event_PCBangPet;							//PC�� �� �̺�Ʈ

	int		StartUser_PresentItem;						//������������ ���� �ֱ�

	int		GameGuard_Auth;								//���Ӱ��� ���� ����

	int		TT_DataServer_Count;									//��ʸ�Ʈ���� ����Ÿ ��� ����
	TT_DATA_SERVER_INFO		TT_DataServer[TT_DATA_SERVER_MAX];		//��ʸ�Ʈ���� ����Ÿ ����

	int		FixedStartField;							//���� �ʵ� ���� ������Ű��
	int		DisableThrowItem;							//������ ���� ������

	int		CheckPlayField;								//Ŭ���̾�Ʈ �� ������  �ʵ� ���� �� �˻�

	int		Enable_PKField;								// PK��� �ʵ� ��ȣ

	int		Enable_PKField_All;							// pluto PK��� �ʵ� ����

	//��Ų�� ����
	int		CheckModelFile;								//������ Ȯ�� �ɼ�

	bool	bPK_LOG;
	rsSERVER_CONFIG()
	{
		bPK_LOG = false;
	};
};

//����ġ�� ���� ��� �Ѱ�ġ ( ���Ѱ踦 �Ѿ�� ������ �ȵȴ� )
#define	TOTAL_CHECK_MONEY_MAX		52000
#define	TOTAL_CHECK_EXP_MAX			100000




/////////////////// Ŭ���̾�Ʈ ��� ��ġ ����ü ////////////////////////
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

//SOD ���� ���
struct	sSOD_SCORE {
	int		Flag;
	DWORD	dwDispTime;
	int		Score;
	int		MyTeam;
	int		TeamScore[4];
	int		Round;
	DWORD	dwPlayTime;

	/////// SOD ���� �̺�Ʈ /////////

	DWORD	dwSoD_NextStageTime;		//���� �������� �Ѿ�� �ð�
	int		SodNextStageNum;			//�Ѿ �������� ��ȣ
	int		NextRound;
	DWORD	dwSoD_CloseStageTime;		//ȭ���� �ݴ� ����Ʈ ����ð�

	///////// SOD ���� ���� //////////////
	int		EffectStartCount;			//����Ʈ ���۱����� ī����
	int		EffectCode;					//����Ʈ �ڵ�

	//////// SOD ���� ȿ�� /////////////
	int		ScoreEffectCount;				//���� ȿ��

};

class User
{
public:
	BOOL				bInUse;
	char				szServerID[32];

	char				szAccountName[32];
	char				szCharacterName[32];

	DWORD				dwHashAccountName;
	DWORD				dwHashCharacterName;

	ID					iID;
	int					iAccountID;
	int					iCharacterID;

	UINT				uSerialHD;

	BOOL				b16;
	BOOL				b32;
	BOOL				b64;

	BOOL				bEXPPotion;

	PacketPlayDataEx	pData;

	int					AdminOperMode;

	BOOL				bCheckedGameMaster;

	DWORD				dwDataError;

	int					TransInfoFlag;

	BOOL				bKeepAlive;

	int					CharLoadingCount;

	EMapID				iMapID;
	Point3D				sPosition;
	Point3D				sAngle;

	User				**lpAreaPlayInfo;

	int					SendListCnt;

	DWORD				dwDecPacketCode;
	BYTE				bPacketXor[2];
	DWORD				dwDecPacketTime;
	DWORD				dwDecPacketTime2;

	CharacterData		sCharacterData;

	int					dwVipLevel;
	DWORD				dwVipTime;

	int					CharLevelMax;
	DWORD				dwNoticeCount;

	UINT				uaUpdateCounter1[1024];		//0x6EB0
	UINT				uaUpdateCounter2[1024];		//0x6EB0 + 0x1000
	USHORT				uaUpdateCounter3[1024];		//0x6EB0 + 0x1000 + 0x1000
	USHORT				uaUpdateCounter4[1024];		//0x6EB0 + 0x1000 + 0x1000 + 0x800
	UCHAR				uaUpdateCounter5[4096];		//0x6EB0 + 0x1000 + 0x1000 + 0x800 + 0x800

	DWORD				dwaTimeUnitStatus[5];

	BYTE				baUnitStatusNew[5][0x2000];

	int					iMovingIndex;

	DropItemData		ThrowItemInfo[64];

	DropItemData		InvenItemInfo[316];
	DropItemData		WareHouseItemInfo[120];
	BOOL				bWarehouseOpen;

	int					iWarehouseError;
	int					iWarehouseGold;
	DropItemData		sWarehouseItems[420];
	DropItemData		saTradeItems[20];

	DropItemData		CaravanItemInfo[120];
	int					OpenCaravanInfoFlag;

	DWORD				dwTradePotionInfo[16];
	int					TradePotionInfoCount;

	SellItemShopData	sMyShopList[32];
	int					MyShopListCount;
	DWORD				dwMyShopTradeTime;

	int					ThrowItemCount;

	int					dwLevelQuestLogCheck;
	int					dwElementaryQuestLogCheck;

	int					UnsaveMoney;

	int					iInventoryGold;
	int					WareHouseMoney;

	DWORD				dwRecvTimePlayBuff;
	DWORD				srSendPlayBuffCnt;
	DWORD				uUnitStatusNum;

	int					ChatMsgMode;
	char				szChat[256];

	BOOL				bMuted;
	DWORD				dwChatTradeTime;

	char				szTradeMessage[128];
	DWORD				dwTradeMsgCode;

	SocketData *		pcSocketData;

	DWORD				dwTimeLastPacket;
	DWORD				dwTimeLastStatusUpdate;

	int							iPacketCounter;
	DWORD						dwTickPacketCounter;

	BOOL						bClosingSocket = FALSE;

	int							UpdateInfo_WaitCounter;	//������Ʈ ���� ��� ī����
	int							UpdateInfo_WarnigCounter;	//������Ʈ ���� ��� (�����Ǹ� ���� ���� )

	ItemBoxSlot					sItemBox;
	ItemBoxSlotEx				sItemBoxEx;

	BOOL						bCharacterExLoaded;
	CharacterDataEx				sCharacterDataEx;

	PacketCharacterRecordData *	psCharacterData; //��ʱ����
	int							iCurrentBlock;

	EGameLevel					iGameLevel;
	BOOL						bCloak;
	int							AdminIP;

	DWORD						dwConnectTime;			//������ �ð�

	int							LastTransPlayUserCount;
	int							LastTransAutoPlayCount;

	DWORD							dwConnectCount;

	int								iServerIndexID;

	BOOL							bAFK;

	int								frame;
	int								iUnitStatusCounter;

	UINT							uLethalSightLevel;
	UINT							uLethalSightRange;
	UINT							uLethalSightCritical;
	UINT							uLethalSightDamageBoost;
	DWORD							dwLethalSightTimeOut;

	UINT							uFierceWindLevel;
	DWORD							dwFierceWindTimeOut;

	UINT							uHolyConvictionLevel;
	DWORD							dwHolyConvictionTimeOut;

	UINT							uWizardTranceLevel;
	DWORD							dwWizardTranceTimeOut;

	//Skill Data
	PacketSkillStatus				sSkillStatus;
	PacketSkillStatusContainer		sSkillContainer;

	UINT							uBufferSkillPosition;

	//Unit Status
	UINT							uPriorityCounter;
	UINT							uPriority;

	//Status Send Buffers
	UINT							uBufferPosition;
	PacketUnitStatusContainer		sUnitStatusContainer;
	UINT							uBufferPositionM;
	PacketUnitStatusContainer		sUnitStatusContainerM;

	DWORD			MonTranCount;			//����/NPC ���� �غ�
	DWORD			CharTransCount;			//ĳ���� ���� �غ�

	int				HitMonsterCount;		//������ ���� ī����
	Unit			* pcLastAttack;
	DWORD			lLastAttackID;

	int				UserPacketLoop;			//���� 1���ν� ���۵� ��Ŷ ��ġ ( ������� ��ġ )
	int				BefUserPacketLoop;		//���� 1���ν� ���۵� ��Ŷ ��ġ ( ������� ��ġ )

	int				AttackCount;			//���� ī����			
	DWORD			dwAttackTime;			//���� �ð�
	DWORD			dwLastAttackTime;		//�ֱ� ���ݽð�
	int				DamagePacketCount;		//���� ��Ŷ ī����
	DWORD			dwDamagePacketTime;		//������ ��Ŷ�� ���� Ŭ���̾�Ʈ �� �ð�

	UINT			uUnitKillCounter;
	DWORD			dwLastTradeChksum;		//������ �ŷ��� ýũ��
	DWORD			dwLastTradeTime;		//������ �ŷ��� �ð�

	DWORD			dwExpTime;

	short			sLowLevel_PresentItem[2];	//������ ������ ����

	DWORD			dwStartUser_PresentItem_Time;	//�������� ������ ����
	DWORD			dwStartUser_PresentItem_Count;	//�������� ������ ����

	int				Send_AttackCount;
	int				Send_AttackDamage;
	int				Recv_AttackCount;
	int				Recv_AttackDamage;

	DWORD			dwMacroTime;
	DWORD			dwMacroAngTime;
	DWORD			dwMacroChkTime;

	DWORD			dwSendFrames[PLAYERS_MAX];

	int				CrackWarning;				//ũ�� ��� ����
	DWORD			dwTime_Disconnect;			//������� ����
	int				BadPlayer;					//���� �÷��̾� ( ��� ���� ��ȿ )
	DWORD			dwPacketAttackCount;		//������ ��Ŷ���� ���� ���� ���� 
	DWORD			dwPacketAttackTime;			//������ ��Ű���� �������� �ð�
	int				WarningCount;				//��� ī��Ʈ

	CharacterFile	*psCharacterFile;
	DWORD			dwRecordDataTime;			//�ֱ� ��Ͻð�

	DWORD			dwExclusiveNum;
	int				iBellatraScore;
	int				iBellatraKills;
	DWORD			dwEventTime;
	short			sBellatraRoomID;
	short			sZero;

	int				iTradeCoin;

	int				AreaOutCount;				//����ħ�� ī����

	int				BlockTime;					//���� ����ų �ð�

	int				Event_StarTicketLevel;		//�� ��ǰ�� �߻� ����

	User					* pcUserDataSpyoner;

	PacketSettingsData		sSettingsData;

	LARGE_INTEGER			liEXP;
	int				spMoney_Start;
	int				spLevel_Start;

	int				spExp_InOut_Total;			//����ġ ��� ��Ż
	int				spMoney_In_Total;			//�� �Ա� ��Ż
	int				spMoney_InOut_Total;		//�� ��� ��Ż

	int				spEXP_Out;					//����ġ ���
	int				spMoney_In;					//�� �Ա�
	int				iGoldOut;

	DWORD			dwLastExpMoneyCheckTime;	//���������� ����ġ �ݾ� ���� �ð�
	DWORD			dwLastExpMoneyTransServer;	//�������� ����ġ �ݾ� ��ġ ������ �ð�

	DWORD			dwDisconnectTime;

	int				Client_Version;				//������� Ŭ���̾�Ʈ�� ���� ����

	DWORD			dwLastSaveTime;				//���������� ������ �ð�

	DWORD			dwNSpriteTime;				//nSprite �˻��� �ð�

	//Ŭ���̾�Ʈ ��� ýũ
	DWORD			dwClientFuncChk_1;			//ýũ�� ���1
	DWORD			dwClientFuncChk_2;			//��ũ�� ���2
	int				FuncChkFailCount1;			//����
	int				FuncChkFailCount2;			//����
	int				FuncChkSucessCount1;		//����
	int				FuncChkSucessCount2;		//����
	DWORD			dwFuncChkErrorFlag;			//����
	int				ClientFunChk1_Count;
	int				ClientFunChk2_Count;

	DWORD			dwClientFunChk_NextTime;	//���� ýũ�� �ð�

	int				RecordWarningCount;			//���� ������ ��� ī����

	DWORD			dwClentOS;					//Ŭ���̾�Ʈ OS
	WORD			wClentOSVersion[2];			//Ŭ���̾�Ʈ ���� [0]-���� [1]-�����ȣ
	DWORD			dwClentModulChkSum;			//Ŭ���̾�Ʈ ��� ýũ��
	int				ClentModuleCount;			//Ŭ���̾�Ʈ ��ƫ ����

	DWORD			dwDamagePacketKey[2];		//������ ��Ŷ ��ȣ�� Ű ( ���ſ� )
	DWORD			dwDamagePacketKey2[2];		//������ ��Ŷ ��ȣ�� Ű ( �۽ſ� )

	//Party
	BOOL						bParty;
	PartyInfo					* psParty;

	ULONG						iClanID;
	int							iTicket;
	int							SucessCheck_ClanCode;

	//bc
	int							iBlessCastleScore;


	//////////////////// ���� ���� ���� /////////////////////////

	char	szGuid[128];			//�α��� �ĺ���
	char	szPwd[32];			//�н�����
	char	szGPCode[16];		//��ǰ�ڵ�
	time_t	DisuseDay;			//���� ��¥
	int		UsePeriod;			//�����ð� ��
	int		GpCode;				//��ǰ�ڵ�
	int		GpType;				//��ǰŸ�� ( ���� / PC�� )
	DWORD	dwPeriodTime;		//���� �ð�
	int		Bl_RNo;				//PC�� ��� ����
	int		Bl_Meter;			//������
	DWORD	dwPeriodTime2;		//������ ����ð� ( �±��̼����� ��� )


	////////////////// ������ �ۼ��� ���� �ڵ� /////////////////////

	int		SndItemSecCodeCount;			//������ ���� ���� �ڵ� ī����
	int		RcvItemSecCodeBuff[8][16];		//���� ������ ���� ī���� ���� ���� ����

	/////////////////////////////////////////////////////////////////

	short	sLimitDamage[2];				//���ݷ� ����
	short	sLimitCritical[2];				//ũ��Ƽ�� ����

	/////////////////////////////////////////////////////////////////

	int		ServerPotion[3][4];				//���హ�� Ȯ�ι���

	int		UseMonsterNum;

	DWORD	dwSkill_AutoMation_Time;
	int		dwSkill_AutoMation_Param;
	//�ƽø�����
	DWORD	dwSkill_Maximize_Time;
	int		dwSkill_Maximize_Param;
	//������
	DWORD	dwSkill_PhysicalAbsorb_Time;
	int		dwSkill_PhysicalAbsorb_Param;
	//�ͽ�Ʈ�� ����
	DWORD	dwSkill_ExtreamShield_Time;
	int		dwSkill_ExtreamShield_Param;

	//Ȧ�� �ٵ�
	DWORD	dwSkill_HolyBody_Time;
	int		dwSkill_HolyBody_Param;
	//Ȧ�� �뷯
	DWORD	dwSkill_HolyValor_Time;
	int		dwSkill_HolyValor_Param;
	//Ȧ�� ���÷���
	DWORD	dwSkill_HolyReflection_Time;
	int		dwSkill_HolyReflection_Param;
	//��þƮ ����
	DWORD	dwSkill_EnchantWeapon_Time;
	int		dwSkill_EnchantWeapon_Param;

	// ս��ף��
	DWORD	dwSkill_P_Enhence_Time;
	int		dwSkill_P_Enhence_Param;


	//��Ż�Ƹ�
	DWORD	dwSkill_MetalArmor_Time;
	int		dwSkill_MetalArmor_Param;

	//����ũ ����
	DWORD	dwSkill_SparkShield_Time;
	int		dwSkill_SparkShield_Param;

	//���� �ø���
	DWORD	dwSKill_Falcon_Time;
	short	dwSKill_Falcon_Damage[2];

	//����� ��Ȧ���̼�
	DWORD	dwSkill_DivineInhalation_Time;
	DWORD	dwSkill_DivineInhalation_Param;

	//Ʈ���̾��� ���Ҷ�
	DWORD	dwSkill_TriumphOfValhalla_Time;
	DWORD	dwSkill_TriumphOfValhalla_Param;

	//����� ������
	DWORD	dwSkill_VirtualLife_Time;
	DWORD	dwSkill_VirtualLife_Param;

	//����������
	DWORD	dwSkill_EnergyShield_Time;
	DWORD	dwSkill_EnergyShield_Param;

	//���
	DWORD	dwSkill_SpiritElemental_Time;
	DWORD	dwSkill_SpiritElemental_Param;

	//��̼ҵ�
	DWORD	dwSkill_DancingSword_Time;
	DWORD	dwSkill_DancingSword_Param;
	DWORD	dwSkill_DancingSword_DelayTime;

	//��ʥ����
	DWORD	dwSkill_T_Anima_Time;
	DWORD	dwSkill_T_Anima_Param;

	//��Ͻ�
	DWORD	dwVanishEndTime;
	short	saVanishParam[2];

	//��Ͻ�
	DWORD	dwSkill_Compulsion_Time;
	DWORD	dwSkill_Compulsion_Param;

	//���׳�ƽ���Ǿ�
	DWORD	dwSkill_MagneticSphere_Time;
	DWORD	dwSkill_MagneticSphere_Param;

	//����Ŀ
	DWORD	dwSkill_Berserker_Time;
	DWORD	dwSkill_Berserker_Param;

	//����֮ŭ
	DWORD	dwSkill_B_Berserker_Time;
	DWORD	dwSkill_B_Berserker_Param;

	//��ž���
	DWORD	dwSkill_AssassinEye_Time;
	DWORD	dwSkill_AssassinEye_Param;

	//����
	DWORD	dwSkill_Vague_Time;
	DWORD	dwSkill_Vague_Param;

	//Ǳ�ܼ���
	DWORD	dwSkill_Amplified_Time;
	DWORD	dwSkill_Amplified_Param;

	//�������������
	DWORD	dwSkill_ForceOfNature_Time;
	WORD	wSkill_ForceOfNature_Param[2];

	//���鸮 ����
	DWORD	dwSkill_GodlyShied_Time;
	DWORD	dwSkill_GodlyShied_Param;

	//��������
	DWORD	dwSkill_GodsBless_Time;
	DWORD	dwSkill_GodsBless_Param;

	//����֮��
	DWORD	dwSkill_Benedic_Time;

	//Ȧ������Ҷ�
	DWORD	dwSkill_HallOfValhalla_Time;
	WORD	wSkill_HallOfValhalla_Param[2];

	//���ν�Ʈ���
	DWORD	dwSkill_FrostJavelin_Time;
	DWORD	dwSkill_FrostJavelin_Param;

	//�����ʷ��ʵ�
	DWORD	dwSkill_RegenerationField_Time;

	//���� ������
	DWORD	dwSkill_SummonMuspell_Time;
	DWORD	dwSkill_SummonMuspell_Param;

	// ��Ůɢ��
	DWORD	dwSkill_Krishna_Time;
	DWORD	dwSkill_Krishna_Param;

	//��ä
	DWORD	dwSkill_Blind_Time;
	DWORD	dwSkill_Blind_Param;

	//���˶�
	DWORD	dwSkill_Advent_Migal_Time;
	DWORD	dwSkill_Advent_Migal_Param;

	//����ʦ
	DWORD	dwSkill_Rainmaker_Time;
	DWORD	dwSkill_Rainmaker_Param;

	DWORD	dwCurse_Attack_Time;		//���� ����
	DWORD	dwCurse_Attack_Param;		//���� ����

	DWORD	dwCurse_Defence_Time;		//��� ����
	DWORD	dwCurse_Defence_Param;		//��� ����

	BYTE	bSkillPoint[SKILL_POINT_COLUM_MAX];

	DWORD	dwForceOrb_Code;			//�������� ������ �����ڵ�
	DWORD	iForceOrbTime;			//�������� �����ð�
	DWORD	dwForceOrb_Damage;			//�������� ������
	DWORD	dwLastForceTime;

	DWORD	dwForceOrb_SaveCode;		//�������� ������ �����
	DWORD	dwForceOrb_SaveTime;		//�������� ������ �����
	DWORD	dwForceOrb_SaveDamage;		//�������� ������ �����
	DWORD	dwForceOrb_NextSetTime;		//�������� ������� ������ ����ð�

	// ����� - �ν��� ������(�����)
	DWORD	dwLifeBooster_Code;			//�ν��� ������(�����) �����ڵ�
	DWORD	dwLifeBooster_Time;			//�ν��� ������(�����) �����ð�
	DWORD	dwLifeBooster_Data;			//�ν��� ������(�����) ���� �ۼ�Ʈ

	DWORD	dwLifeBooster_SaveCode;		//�ν��� ������(�����) ������ �����
	DWORD	dwLifeBooster_SaveTime;		//�ν��� ������(�����) ������ �����
	DWORD	dwLifeBooster_SaveData;		//�ν��� ������(�����) ������ ����� ���� �ۼ�Ʈ
	DWORD	dwLifeBooster_NextSetTime;	//�ν��� ������(�����) ������� ������ ����ð�

	DWORD	dwManaBooster_Code;			//�ν��� ������(���) �����ڵ�
	DWORD	dwManaBooster_Time;			//�ν��� ������(���) �����ð�
	DWORD	dwManaBooster_Data;			//�ν��� ������(���) ���� �ۼ�Ʈ

	DWORD	dwManaBooster_SaveCode;		//�ν��� ������(���) ������ �����
	DWORD	dwManaBooster_SaveTime;		//�ν��� ������(���) ������ �����
	DWORD	dwManaBooster_SaveData;		//�ν��� ������(���) ������ ����� ���� �ۼ�Ʈ
	DWORD	dwManaBooster_NextSetTime;	//�ν��� ������(���) ������� ������ ����ð�

	DWORD	dwStaminaBooster_Code;			//�ν��� ������(�ٷ�) �����ڵ�
	DWORD	dwStaminaBooster_Time;			//�ν��� ������(�ٷ�) �����ð�
	DWORD	dwStaminaBooster_Data;			//�ν��� ������(�ٷ�) ���� �ۼ�Ʈ

	DWORD	dwStaminaBooster_SaveCode;		//�ν��� ������(�ٷ�) ������ �����
	DWORD	dwStaminaBooster_SaveTime;		//�ν��� ������(�ٷ�) ������ �����
	DWORD	dwStaminaBooster_SaveData;		//�ν��� ������(�ٷ�) ������ ����� ���� �ۼ�Ʈ
	DWORD	dwStaminaBooster_NextSetTime;	//�ν��� ������(�ٷ�) ������� ������ ����ð�

	DWORD	dwPrimeItem_NextSetTime;
	DWORD	dwTime_PrimeItem_X2;
	DWORD	dwTime_PrimeItem_ExpUp;
	DWORD	dwPrimeItem_PackageCode;	//��Ű�������� �ڵ�

	DWORD	dwTime_PrimeItem_VampCuspid;
	DWORD	dwTime_PrimeItem_ManaRecharg;
	DWORD	dwTime_PrimeItem_MightofAwell;
	DWORD	dwTime_PrimeItem_MightofAwell2;
	DWORD	dwTime_PrimeItem_ManaReduce;
	DWORD	dwTime_PrimeItem_PhenixPet;
	DWORD	dwTime_PrimeItem_HelpPet;
	DWORD	dwTime_PrimeItem_VampCuspid_EX;
	DWORD	dwTime_PrimeItem_StaminaReduce;

	PacketItemPremiumData			sPremiumData;
	DWORD							dwTimeSync;
	DWORD							dwTimeSavePremium;
	PacketItemData					sTempItem;

	DWORD	dwPCBang_Pet_AttackTime;
	DWORD	dwPCBang_Pet_NextSetTime;

	DWORD	dwHelp_Pet_AttackTime;
	DWORD	dwHelp_Pet_NextSetTime;

	DWORD	dwSkillDelay_Code;
	DWORD	dwSkillDelay_Time;
	DWORD	dwSkillDelay_Data;

	DWORD	dwSkillDelay_SaveCode;
	DWORD	dwSkillDelay_SaveTime;
	DWORD	dwSkillDelay_SaveData;
	DWORD	dwSkillDelay_NextSetTime;

	DWORD	dwPrimeItem_FruitGame;
	DWORD	dwPrimeItem_FruitData;
	BYTE	bPrimeItem_Status[8];

	Unit	*lpLinkChar[SIN_MAX_SKILL_LIST];
	DWORD	dwLinkCharCode[SIN_MAX_SKILL_LIST];

	short	sBlessCastle_Damage[2];
	short	sBlessCastle_Param[2];
	DWORD	dwCheck_MasterClanTime;

	sCASTLE_MASTER	CastleMaster;
	DWORD	dwBlessSkill_Code;
	DWORD	dwBlessSkill_Time;
	DWORD	dwBlessSkill_Param;

	DWORD	dwSiegeItem_Scroll_Time;
	DWORD	dwSiegeItem_Scroll_Code;
	DWORD	dwSiegeItem_Scroll_Param;

	DWORD	dwSiegeItem_Stone1_Time;
	DWORD	dwSiegeItem_Stone1_Code;
	DWORD	dwSiegeItem_Stone1_Param;

	DWORD	dwSiegeItem_Stone2_Time;
	DWORD	dwSiegeItem_Stone2_Code;
	DWORD	dwSiegeItem_Stone2_Param;

	// ������һ��
	Unit	*dwCaravan_Hopy;
	DWORD	dwCaravan_SetNextTime;
	DWORD	dwCaravan_Hopy_Time;
	DWORD	dwCaravan_Param;
	// ��˵�
	DWORD	dwTime_PhenixPet;
	DWORD	dwPhenixPet_SetNextTime;
	DWORD	PhenixPetType;
	DWORD	cdwTime_PhenixPet;
	DWORD	cphenixPetType;

	short	sCheckPlayField_Count[2];

	DWORD	dwHaQuestItemCount;

	// ��ͷ
	DWORD	dwTime_BigHead;
	DWORD	dwBigHead_SetNextTime;
	DWORD	BigHeadType;
	DWORD	cdwTime_BigHead;
	DWORD	cBigHeadType;


	char	szUserExpTimeID[32];
	char	szUserExpTimeName[32];
	DWORD	dwExpGameTime;
	DWORD	dwExpGameTimeCheck;

	int		iPVPKills;
	int		iPVPDeaths;
	int		iPVPKillStreak;
	BOOL	bResetKillStreak;
	int		iKillSafe;
	int		iLastKillSafeID;
	DWORD	dwKillSafeTimeOut;
	DWORD	dwLastKillIP;

	UINT uIndex;
	BOOL bNetServer;
	BOOL bDisconnectNet;

	void Init(int uIndex);
	void Start(SocketData * sd) { bInUse = TRUE; pcSocketData = sd; }
	void Stop() { bInUse = FALSE; pcSocketData = NULL; bNetServer = FALSE; };
	BOOL IsInGame() { return iID != 0 ? TRUE : FALSE; }
	BOOL IsConnected() { return pcSocketData != 0 ? TRUE : FALSE; }
	ID GetID() { return iID; }
	EMapID GetMapID() { return iMapID; }
	EGameLevel GetGameLevel() { return iGameLevel; }
	void SetGameLevel(EGameLevel eLevel) { iGameLevel = eLevel; }
	BOOL CanSee(User * pcOtherUser)
	{
		//Other User cloaked? Then cannot see other user
		if (pcOtherUser->bCloak)
			return FALSE;

		//Not in one of the two Maps that the User can see?
		EMapID eOtherMapID = pcOtherUser->GetMapID();

		if (iMapID != eOtherMapID)
			return FALSE;

		//Other User in Quest Arena?
		if (pcOtherUser->GetMapID() == MAPID_QuestArena)
		{
			//Not a GM? Then cannot see other User
			if (GetGameLevel() == GAMELEVEL_None)
				return FALSE;
		}

		return TRUE;
	}
	BOOL CanSee(Unit *pcOtherUnit);
	int	GetGold() { return iInventoryGold; };
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