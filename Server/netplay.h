
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


int ClearAttMonsterCode();
int	AddAttMonsterCode( DWORD dwCode );
int	CheckAttMonsterCode( DWORD dwCode );


int RecallSavedChatCommand( HWND hChatWnd , int Arrow );
DWORD EncodeParam( DWORD Param );
int ThrowPutItem(ItemData *lpItem , int x, int y , int z );
int ThrowPutItem2(Item *lpItem , int x, int y , int z );
int SendAdd_Npc(Unit *lpCharSample , int state );
int SendDelete_Npc(Unit *lpCharSample );
int SendGetRecordData( char *szName );

struct sWAREHOUSE;
int	SaveWareHouse(sWAREHOUSE *lpWareHouse,TRANS_WAREHOUSE *lpTransWareHouse);
int	SaveWareHouse(sWAREHOUSE *lpWareHouse);

/////////////////////// PK ////////////////////////////////////

struct sCARAVAN;
// �������ֿ�
int SaveCaravan(sCARAVAN *lpCaravan,TRANS_CARAVAN *lpTransCaravan);

extern	int	ReconnDataServer;
extern	int	ReconnServer;


extern int	DisconnectFlag;
extern int	DisconnectServerCode;

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
extern PK_FIELD_STATE	PK_FieldState;		//Pk �ʵ� ���� ����ü


//���� �ð� �ʰ� ĳ���� ����
#define DIS_TIME_OVER		30000
//���� �ð� �ʰ� ĳ���� ��ǥ��
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


extern DWORD	dwLastCheckItemTime;

//�������� �޸� ���� ���ؼ� ��������
DWORD funcCheckMemSum( DWORD FuncPoint , int count );


#define	CLANMONEY_KIND_SOD		0
#define	CLANMONEY_KIND_CASTLE	1

int	RecvClanCommand(TRANS_CLAN_COMMAND_USER *lpTransClanUser, _CLAN_USER_INFO *ClanUserInfo);


// ���VIP��Ϣ
int SendUpdataVipInfo();
int SendQuestCommandToServer( DWORD dwQuestCode , int Param1, int Param2, int Param3 );

//���� ýũ�� NPC��� ������ ������ �˻��뺸
int HackTrap_CheckOpenFlag();


#endif