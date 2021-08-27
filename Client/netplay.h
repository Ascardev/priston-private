
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
//PK���ؼ� ����
int PlayerKilling( DWORD dwObjectSerial );

struct sCARAVAN;
// ���س���ֿ�
int LoadCaravan(TRANS_CARAVAN *lpTransCaravan,sCARAVAN *lpCaravan,int flag);
// �������ֿ�
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


//����ġ�� �� �ŷ� �ݾ��� ��Ż�� ����Ѵ�
int	SetTotalAddMoney( int Money );
int	SetTotalSubMoney( int Money );
int	SetTotalAddExp( int Exp );
int	SetTotalSubExp( int Exp );
int GetTotalExp();
int	GetTotalMoney();
int GetTotalSubExp();


// pluto ���� ����Ÿ�� ������ ����
int SendSmeltingItemToServer( void *lpsSmeltingItem_Send);
// pluto ���� ����Ÿ�� ������ ����
int SendManufactureItemToServer( void *lpsManufactureItem_Send);
// ������ - �ͽ��� ���� �������� ������ �����Ѵ�.
int SendMixtureResetItemToServer( void *lpsMixtureResetItem_Send);

//���ͺϳ���Ʒ��������Э��
int SendCraftItemToServer(void *lpsCraftItem_Send);
// ���Ͷ�����Ʒ��������
int SendAgingItemToServer( void *lpsCraftItem_Send );
// ����������Ʒ��������
int SendElementItemToServer(void *lpsItem_Send);

// ���ʹ����Ʒ����������
int SendSocketItemToServer(void *lpsItem_Send);
// ����HOPY�Ƿ��߶����͵�������
int SendSelectHopyToServer(int Kind);
//����¡ �Ϸ�� �������� ������ ����
int SendAgingUpgradeItemToServer(Item *lpItem );
//��ũ�ھ� ��� ����
int SendLinkCoreToServer(Item *lpItem );
//������ �� ������ ����Ÿ�� ������ ����
int SendWingItemToServer( void *lpsCraftItem_Send );

//�Ǹ��� �������� ������ ����
int	SellItemToServer(Item *lpItem , int Count );

extern DWORD	dwLastCheckItemTime;
//�������� ������ ������ Ȯ��
int	SendCheckItemToServer(Item *lpItem );
//�κ��丮�� ������ �������� ������ ������ �˻�
int CheckInvenItemToServer();

//�������� �޸� ���� ���ؼ� ��������
DWORD funcCheckMemSum( DWORD FuncPoint , int count );

//�ӽ������ ������ ť�� ������ ��������� �˻�
int CheckRecvTrnsItemQue();
//����� ������ �ڵ� ������ ����
int SendUseItemCodeToServer(Item *lpItem );

//�ֺ� ĳ���Ϳ� �̺�Ʈ ��� �ڵ� ������
int	SendCommandUser( int wParam , int lParam , int sParam , int eParam );
//�ֺ� ĳ���Ϳ� �̺�Ʈ ��� �ڵ�
int RecvCommandUser( smTRANS_COMMAND_EX *lpTransCommandEx );

//���������� ��� �ڵ� ����
int	SendCommand_AreaServer( DWORD dwCode , int wParam , int lParam , int sParam , int eParam );
//����Ÿ������ ��� �ڵ� ����
int	SendCommand_DataServer( DWORD dwCode , int wParam , int lParam , int sParam , int eParam );

//���ݷ� ��� ����ȭ
int	Init_RecordDamage();
int	Record_RecvDamage(SocketData * pcSocketData, int Damage );

//��Ƽ������ ��ų ��� ���� ������
int	SendPartySkillToServer( DWORD dwSkillCode , int SkillLevel , int Around , int wParam , int lParam , int sParam , int eParam );
//��ų ���
int SendCancelSkillToServer( DWORD dwSkillCode , int lParam , int sParam , int eParam );
//������ ��ų���� ����
int SendProcessSKillToServer( DWORD dwSkillCode , int point , int Param1, int Param2 );
//��ų ����
int SendUpdateSkillToServer( DWORD dwSkillCode , int lParam , int sParam , int eParam );
// ȡ��ˮ����������
int SendCancelCrystalToServer(DWORD dwSkillCode,int lParam,int sParam,int eParam);
// ȡ����ͷҩˮ������
int CancelBigHeadToFunction();
// ����ʯͷ����
int SetForceOrbFunction(DWORD Code,int Time);

// ������ʾ�˺���������
int SendDisplayDamgeToServer(int Damge,DWORD dwObjectSerial,int AttackCritical,int Element);

//Ŭ�� �޼��� �ޱ�
int RecvClanJoinService( smTRANS_CHAR_COMMAND2 *lpTransCharCommand );
//Ŭ�� �޼��� ������
int SendClanJoinService( DWORD dwMsgCode , Unit *lpChar  );
//Ŭ�� ���� ���� �޼��� ������
int SendJoinClan();
//����� ����Ʈ�� ��ų ���� ( ����Ʈ ���� )
int SkillPlay_DivineLightning_Effect(Unit *lpChar , int SkillPoint );
int SkillPlay_VenomSpear_Effect(Unit *lpChar , int SkillPoint);
//���� ��ų ����Ʈ ���� ( ����Ʈ ���� )
int SkillPlay_Monster_Effect(Unit *lpChar , int EffectKind , int Range );
//����� ����Ʈ�� ��ų ���� ( �ӹ̷ε� )
int SkillPlay_MummyLord_Effect(Unit *lpChar , int Range );

//����Ƿ�רְ
int CheckChangeJob(CharacterData *pCharInfo);

DWORD GetPlayTime_T();
int	ChangeBigHeadMode(int Mode);

int	RecvClanCommand( TRANS_CLAN_COMMAND_USER *lpTransClanUser , _CLAN_USER_INFO *ClanUserInfo );
// Element����Ч��
int SendElementDamage(Unit *lpChar, int Kind);
//�ƽ���ӥ
int SendFalconDamage(Unit *lpChar );
//��̼ҵ� ������ ������
int SendDancingSwordDamage(Unit *lpChar );
//������ �� ������
int SendLowLevelPetDamage(Unit *lpChar , int petType );
//PC��� �� ������
int SendPCBangPetDamage(Unit *lpChar , int petType );

//�ޱ׳�ƽ ���Ǿ� ������ ������
int SendMegneticSphereDamage(Unit *lpChar );
//�ӽ��� ������ ������
int SendMuspellDamage(Unit *lpChar );
//�ִ� ������ Ȯ��
int	SendMaxDamageToServer( WORD MinDamage , WORD MaxDamage , WORD Critical );
//�ִ� ������ ��������ü�� ����
int SetMaxDamage(CharacterData *lpCharInfo );

//��ų��ȣ�� ���� �ʱ�ȭ
int ReformSkillInfo();
//��ų�� ���� Ȯ��
int SaveCheckSkill();

//������ �ù� ���� ���� �䱸
int	SendItemExpress( DWORD	dwItemCode , char *szPassCode );
//������ �ù� ���� ���� �䱸
int	SendItemExpress( DWORD	dwItemCode );

//��ȣ ��� ������ ������
int SendClanYahooMotion();
//�� ����Ʈ ������ ������ ������
int	SendStarPointToServer( int Price , int Cash );
//����ѵ��� ������ ������
int	SendGiveMoneyToServer( int Money );

//��Ϯ��ǹ
int SkillPlay_Spear_Effect(Unit *lpChar,int SkillPoint);


#define	CLANMONEY_KIND_SOD		0
#define	CLANMONEY_KIND_CASTLE	1

int	SendClanMoneyToServer( int Money , int Flag , int Kind );
int	SendClanMoneyToServer( int Money , int Flag );
int	SendPaymentMoneyToServer( int Money , int Flag );
int SendOpenPersonalTrade( char *szTradeMsg , void *lpPersTrade );	//���� ���� ����
int SendClosePersonalTrade();										//���� �ݱ�
int	Send_ShowMyShopItem(Unit *lpChar );							//���λ��� ������ ���� �䱸
int	Send_MyShopItemList( smTRANS_COMMAND	*lpTransCommand );		//���λ��� ������ ���� ���濡 ������
int	Recv_MyShopItemList( TRANS_TRADEITEMS *lpTransTradeItems );		//���λ��� ������ ���� ����
int	Send_PersonalShopItem( DWORD dwCharCode , void *lpShopItem );	//���� ���� ���� ����
int	UpdateMyShopList( void *lpMyShop );								//���� ���� ������ ���� ������Ʈ
int SendsServerDoc(char *szTradeMsg );

int SendWareHouseMoneyToServer(int Money,BOOL Flag);

// ���VIP��Ϣ
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

//�������� ��� ������ ������
int	SendPublicPollingToServer( int PollCode , int PollCnt , BYTE *bPollingData );

//���� ýũ�� NPC��� ������ ������ �˻��뺸
int HackTrap_CheckOpenFlag();
//���� ýũ�� ����
int	SendHackTrapToServer( DWORD dwTrapCode , int Param );

#endif