#ifndef	_RECORD_HEADER

#define _RECORD_HEADER

#define RECORD_ITEM_MAX		200
#define	TRANS_RECORD_LEN	(smSOCKBUFF_SIZE-32)


#define	PRIME_ITEM_PACKAGE_NONE			0
#define	PRIME_ITEM_PACKAGE_BRONZE		1
#define	PRIME_ITEM_PACKAGE_SILVER		2
#define	PRIME_ITEM_PACKAGE_GOLD			3
#define	PRIME_ITEM_PACKAGE_ULTRA		4
// pluto 패키지2
#define	PRIME_ITEM_PACKAGE_BRONZE2		5
#define	PRIME_ITEM_PACKAGE_SILVER2		6
#define	PRIME_ITEM_PACKAGE_GOLD2		7
#define	PRIME_ITEM_PACKAGE_ULTRA2		8
#define	PRIME_ITEM_PACKAGE_NONE_50_EXPUP		 9 // 박재원 - 경험치증가 포션(50%) 아이템 전용 
#define	PRIME_ITEM_PACKAGE_NONE_100_EXPUP		10 // 박재원 - 경험치증가 포션(100%) 아이템 전용 

#define	LAST_QUEST_MAX		32
#define	LAST_QUEST_MASK		31

extern LastQuestSave	RecordLastQuestInfo;			//지난 퀘스트 정보

//저장될 구조 파트
struct	TRANS_RECORD_DATAS {
	int	size,code;
	int	Count , Total;
	int	TransSize;

	char	szData[TRANS_RECORD_LEN];
};
#define sPLAY_CHAR_MAX		6

//이름 , 레벨 , 종족 , 직업 


struct	sPLAY_USER_DATA {
	char	szHeader[16];						//구분 헤더
	char	szID[32];							//ID

	char	szCharName[sPLAY_CHAR_MAX][32];		//캐릭터 이름
};

struct	TRANS_USERCHAR_INFO {
	int		size,code;

	char	szID[32];
	int		PlayUserCount;						//캐릭터 수만큼 카운트

	_TRANS_CHAR_INFO	CharInfo[sPLAY_CHAR_MAX];
};


class	rsRECORD_DBASE {
public:
	CharacterFile	TransRecordData;
	int	TransLastPartCount;
	BYTE	TransDataBlock[64];
	DWORD	dwRecordTime;				//저장시도 시간
	DWORD	dwNextRecordTime;			//다음 저장 시간

	//저장할 데이타를 정리하여 제작
	int MakeRecordData(CharacterData *lpCharInfo , ItemData *lpItems , ItemData *lpItems2 , ItemData *lpMouseItem=0 );
	//불러온 데이타 정보를 해당 위치에 설정
	int	ResotrRecordData(CharacterData *lpCharInfo , ItemData *lpItems , ItemData *lpItems2 , ItemData *lpMouseItem=0 );

	//클라이언트 측
	//저장할 데이타를 분할하여 서버로 전송
	int SendRecordDataToServer( smWINSOCK *lpsmSock );
	//저장할 데이타를 분할하여 받음 ( 저장 완료되면 TRUE 반환 )
	int RecvRecordDataFromServer( TRANS_RECORD_DATAS *lpTransRecord );
	int IsData( char *szName );
	//해당 ID에 해당하는 캐릭터 데이타를 클라이언트로 전송함
	int SendUserDataToClient( char *szID , smWINSOCK *lpsmSock , char *szServerID );
};

int GetUserDataFile(char *szName,char *szFileName,int MaxSize);


//데이타 저장서버 디렉토리 생성
int CreateDataServerDirectory();

//종료된 퀘스트 기록 추가
int Record_LastQuest( WORD	wQuestCode );
//지난 퀘스트 검사
int FindLastQuestCode( WORD wQuestCode );

//쇱꿎세콘듐
int	CheckSkillPoint(int Level, RecordSkill *lpRecordSkill,int *spTotal,DWORD dwLevelQuestLog);

//서버ID 구하기
int SetServerID( char *szID , char *szServerID );

//////////////////////////////////////////////////
//시간 확인하여 저장시도
int rsTimeRecData();
//서버DB함수 초기화
int rsInitDataBase();
//서버DB함수 말기화
int rsCloseDataBase();
/////////////////////////////////////////////////

//퀘스트로 획득한 스킬 포인트
int GetSkillPoint_LevelQuest( int Level , DWORD dwLevelQuestLog );
//퀘스트로 획득한 스텟 포인트
int GetStatePoint_LevelQuest( int Level , DWORD dwLevelQuestLog );
//캐릭터 스텟 포인트 확인 및 재설정
int ReformCharStatePoint(CharacterData *lpCharInfo , DWORD dwLevelQuestLog,DWORD Point);



extern int	Permit_CheckMoney ;
extern int	Permit_CheckExp ;


struct	sBILLING_INFO {
	int	PCRNo;
	int	EventPlay[2];
};

extern sBILLING_INFO	*sBiInfo;


#endif