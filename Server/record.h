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

extern LastQuestSave RecordLastQuestInfo;			//지난 퀘스트 정보

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

	//불러온 아이템 목록을 유저정보에 저장
	int MakeRecordItemList(User *lpPlayInfo );


	//서버측 데이타 컨트롤
	//캐릭터 데이타 삭제
	int DeleteCharData( char *szID , char *szName );
	//캐릭터 데이타 정보 삽입
	int InsertCharData( char *szID , char *szName , int Mode=0 );

	//캑릭터 데이타가 존재하는지 확인
	int IsData( char *szName );
	
	int SendUserDataToClient(char *szID, User *pcUser, char *szServerID);

	//버려진 아이템 데이타 저장
	int SaveThrowData( char *szName , DropItemData *lpThrowItemList , int Count , int SaveMoney );

};

int GetUserDataFile(char *szName,char *szFileName,int MaxSize);


int rsSaveWareHouseData(User *lpPlayInfo,TRANS_WAREHOUSE *lpTransWareHouse);
//속潼꾑욋
int rsLoadWareHouseData(User *lpPlayInfo);
// 괏닸녘膠꾑욋
int rsSaveCaravanData(char *szName,TRANS_CARAVAN *lpTransCaravan);
//속潼녘膠꾑욋
int rsLoadCaravanData(User *lpPlayInfo);

int rsCheckAccountChar( char *szID , char *szName );
//창고 열기 (관리용)
int rsLoadWareHouseData_Admin(User *lpPlayInfo , char *szID , int Day );

//포스오브 사용 설정
int rsLoadServerForce(User *lpPlayInfo , CharacterSave *lpGameSaveInfo );
//포스오브 사용 저장
int rsSaveServerForce(User *lpPlayInfo , CharacterSave *lpGameSaveInfo );
//서버 포션 저장
int rsSaveServerPotion(User *lpPlayInfo , CharacterSave *lpGameSaveInfo );
//물약 보유량 비교
int rsCompareServerPotion(User *lpPlayInfo , CharacterSave *lpGameSaveInfo );


//데이타 저장서버 디렉토리 생성
int CreateDataServerDirectory();

//종료된 퀘스트 기록 추가
int Record_LastQuest( WORD	wQuestCode );
//지난 퀘스트 검사
int FindLastQuestCode( WORD wQuestCode );

//쇱꿎세콘듐
int	CheckSkillPoint(int Level, RecordSkill *lpRecordSkill,int *spTotal,DWORD dwLevelQuestLog);
int	rsAddPostBox_Present(User *lpPlayInfo );

//별 포인트 이벤트 티켓 발생 설정
int	OpenStarPointEvent(User *lpPlayInfo , CharacterData *lpCharInfo );

//다른 서버에서 파일을 불러와 저장
int ImportTTServerUser( char *szID , char *szServerID );
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