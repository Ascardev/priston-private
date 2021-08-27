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

extern LastQuestSave RecordLastQuestInfo;			//���� ����Ʈ ����

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

	//�ҷ��� ������ ����� ���������� ����
	int MakeRecordItemList(User *lpPlayInfo );


	//������ ����Ÿ ��Ʈ��
	//ĳ���� ����Ÿ ����
	int DeleteCharData( char *szID , char *szName );
	//ĳ���� ����Ÿ ���� ����
	int InsertCharData( char *szID , char *szName , int Mode=0 );

	//Ĵ���� ����Ÿ�� �����ϴ��� Ȯ��
	int IsData( char *szName );
	
	int SendUserDataToClient(char *szID, User *pcUser, char *szServerID);

	//������ ������ ����Ÿ ����
	int SaveThrowData( char *szName , DropItemData *lpThrowItemList , int Count , int SaveMoney );

};

int GetUserDataFile(char *szName,char *szFileName,int MaxSize);


int rsSaveWareHouseData(User *lpPlayInfo,TRANS_WAREHOUSE *lpTransWareHouse);
//���زֿ�
int rsLoadWareHouseData(User *lpPlayInfo);
// �������ֿ�
int rsSaveCaravanData(char *szName,TRANS_CARAVAN *lpTransCaravan);
//���س���ֿ�
int rsLoadCaravanData(User *lpPlayInfo);

int rsCheckAccountChar( char *szID , char *szName );
//â�� ���� (������)
int rsLoadWareHouseData_Admin(User *lpPlayInfo , char *szID , int Day );

//�������� ��� ����
int rsLoadServerForce(User *lpPlayInfo , CharacterSave *lpGameSaveInfo );
//�������� ��� ����
int rsSaveServerForce(User *lpPlayInfo , CharacterSave *lpGameSaveInfo );
//���� ���� ����
int rsSaveServerPotion(User *lpPlayInfo , CharacterSave *lpGameSaveInfo );
//���� ������ ��
int rsCompareServerPotion(User *lpPlayInfo , CharacterSave *lpGameSaveInfo );


//����Ÿ ���弭�� ���丮 ����
int CreateDataServerDirectory();

//����� ����Ʈ ��� �߰�
int Record_LastQuest( WORD	wQuestCode );
//���� ����Ʈ �˻�
int FindLastQuestCode( WORD wQuestCode );

//��⼼�ܵ�
int	CheckSkillPoint(int Level, RecordSkill *lpRecordSkill,int *spTotal,DWORD dwLevelQuestLog);
int	rsAddPostBox_Present(User *lpPlayInfo );

//�� ����Ʈ �̺�Ʈ Ƽ�� �߻� ����
int	OpenStarPointEvent(User *lpPlayInfo , CharacterData *lpCharInfo );

//�ٸ� �������� ������ �ҷ��� ����
int ImportTTServerUser( char *szID , char *szServerID );
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