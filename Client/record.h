#ifndef	_RECORD_HEADER

#define _RECORD_HEADER

#define RECORD_ITEM_MAX		200
#define	TRANS_RECORD_LEN	(smSOCKBUFF_SIZE-32)


#define	PRIME_ITEM_PACKAGE_NONE			0
#define	PRIME_ITEM_PACKAGE_BRONZE		1
#define	PRIME_ITEM_PACKAGE_SILVER		2
#define	PRIME_ITEM_PACKAGE_GOLD			3
#define	PRIME_ITEM_PACKAGE_ULTRA		4
// pluto ��Ű��2
#define	PRIME_ITEM_PACKAGE_BRONZE2		5
#define	PRIME_ITEM_PACKAGE_SILVER2		6
#define	PRIME_ITEM_PACKAGE_GOLD2		7
#define	PRIME_ITEM_PACKAGE_ULTRA2		8
#define	PRIME_ITEM_PACKAGE_NONE_50_EXPUP		 9 // ����� - ����ġ���� ����(50%) ������ ���� 
#define	PRIME_ITEM_PACKAGE_NONE_100_EXPUP		10 // ����� - ����ġ���� ����(100%) ������ ���� 

#define	LAST_QUEST_MAX		32
#define	LAST_QUEST_MASK		31

extern LastQuestSave	RecordLastQuestInfo;			//���� ����Ʈ ����

//����� ���� ��Ʈ
struct	TRANS_RECORD_DATAS {
	int	size,code;
	int	Count , Total;
	int	TransSize;

	char	szData[TRANS_RECORD_LEN];
};
#define sPLAY_CHAR_MAX		6

//�̸� , ���� , ���� , ���� 


struct	sPLAY_USER_DATA {
	char	szHeader[16];						//���� ���
	char	szID[32];							//ID

	char	szCharName[sPLAY_CHAR_MAX][32];		//ĳ���� �̸�
};

struct	TRANS_USERCHAR_INFO {
	int		size,code;

	char	szID[32];
	int		PlayUserCount;						//ĳ���� ����ŭ ī��Ʈ

	_TRANS_CHAR_INFO	CharInfo[sPLAY_CHAR_MAX];
};


class	rsRECORD_DBASE {
public:
	CharacterFile	TransRecordData;
	int	TransLastPartCount;
	BYTE	TransDataBlock[64];
	DWORD	dwRecordTime;				//����õ� �ð�
	DWORD	dwNextRecordTime;			//���� ���� �ð�

	//������ ����Ÿ�� �����Ͽ� ����
	int MakeRecordData(CharacterData *lpCharInfo , ItemData *lpItems , ItemData *lpItems2 , ItemData *lpMouseItem=0 );
	//�ҷ��� ����Ÿ ������ �ش� ��ġ�� ����
	int	ResotrRecordData(CharacterData *lpCharInfo , ItemData *lpItems , ItemData *lpItems2 , ItemData *lpMouseItem=0 );

	//Ŭ���̾�Ʈ ��
	//������ ����Ÿ�� �����Ͽ� ������ ����
	int SendRecordDataToServer( smWINSOCK *lpsmSock );
	//������ ����Ÿ�� �����Ͽ� ���� ( ���� �Ϸ�Ǹ� TRUE ��ȯ )
	int RecvRecordDataFromServer( TRANS_RECORD_DATAS *lpTransRecord );
	int IsData( char *szName );
	//�ش� ID�� �ش��ϴ� ĳ���� ����Ÿ�� Ŭ���̾�Ʈ�� ������
	int SendUserDataToClient( char *szID , smWINSOCK *lpsmSock , char *szServerID );
};

int GetUserDataFile(char *szName,char *szFileName,int MaxSize);


//����Ÿ ���弭�� ���丮 ����
int CreateDataServerDirectory();

//����� ����Ʈ ��� �߰�
int Record_LastQuest( WORD	wQuestCode );
//���� ����Ʈ �˻�
int FindLastQuestCode( WORD wQuestCode );

//��⼼�ܵ�
int	CheckSkillPoint(int Level, RecordSkill *lpRecordSkill,int *spTotal,DWORD dwLevelQuestLog);

//����ID ���ϱ�
int SetServerID( char *szID , char *szServerID );

//////////////////////////////////////////////////
//�ð� Ȯ���Ͽ� ����õ�
int rsTimeRecData();
//����DB�Լ� �ʱ�ȭ
int rsInitDataBase();
//����DB�Լ� ����ȭ
int rsCloseDataBase();
/////////////////////////////////////////////////

//����Ʈ�� ȹ���� ��ų ����Ʈ
int GetSkillPoint_LevelQuest( int Level , DWORD dwLevelQuestLog );
//����Ʈ�� ȹ���� ���� ����Ʈ
int GetStatePoint_LevelQuest( int Level , DWORD dwLevelQuestLog );
//ĳ���� ���� ����Ʈ Ȯ�� �� �缳��
int ReformCharStatePoint(CharacterData *lpCharInfo , DWORD dwLevelQuestLog,DWORD Point);



extern int	Permit_CheckMoney ;
extern int	Permit_CheckExp ;


struct	sBILLING_INFO {
	int	PCRNo;
	int	EventPlay[2];
};

extern sBILLING_INFO	*sBiInfo;


#endif