
//범위 공격 첵크섬
DWORD	dm_GetRangeDamgeChkSum( TRANS_SKIL_ATTACKDATA2 *lpTransSkilAttackData2 );
//범위 공격 첵크섬
DWORD	dm_GetDamgeChkSum( TRANS_ATTACKDATA2 *lpTransAttackData2 );
//S2C 공격 첵크섬
DWORD	dm_GetDamgeChkSum_S2V( TRANS_ATTACKDATA *lpTransAttackData );
//코맨드 첵크섬
DWORD	dm_GetCommandChkSum( smTRANS_COMMAND *lpTransCommand , DWORD dwObjectSerial );

int dm_SendTransDamage(Unit *lpChar , int PowParam1, int PowParam2, int AttackState, int Resistance, DWORD dwSkillCode , int UseAccuracy);


//범위형 공격 범위 선정 (원)
int dm_SelectRange( int x, int y, int z , int range , int UseAttackRating , int SelCount );
//범위형 공격 범위 선정 (원)
int dm_SelectRange( int x, int y, int z , int range , int UseAttackRating );
//범위형 공격 범위 선정 (박스)
int dm_SelectRangeBox(Unit *lpCurChar , RECT *lpRect , int UseAttackRating );
//범위형 공격 범위 선정 (디바인 라이트닝)
int dm_SelectDamageCount(Unit *lpCurChar , int SelCount , int Size );
//범위형 공격 범위 선정 (체인라이트닝)
int dm_SelectDamageCount(Unit *lpCurChar , Unit *lpTragetChar, int SelCount , int Size );
//범위형 공격 범위 선정 (체인라이트닝)
int dm_SelectDamageChainCount(Unit *lpCurChar , Unit *lpTragetChar, int SelCount , int Size );

//선택된 범위공격 목록에 캐릭 강제 추가
int dm_AddRangeDamage(Unit *lpChar );

//범위공격 설정후 전송
int dm_SendRangeDamage( int x, int y, int z, Unit *lpMainTraget ,int PowParam1, int PowParam2, int AttackState , int Registance ,  DWORD dwSkillCode );

//데미지 암호화 모듈 수신
int RecvDamagePacketModule( TRANS_FUNC_MEMORY *lpTransFuncModule );
int RecvDamagePacketModule2( TRANS_FUNC_MEMORY *lpTransFuncModule );
//패킷 동적 암호화 모듈 수신
int RecvDynPacketModule( TRANS_FUNC_MEMORY *lpTransFuncModule );

extern DWORD	dmAttackCount;

extern Unit	*lpSelected_Char[SKIL_ATTACK_CHAR_MAX];
extern int	dmSelected_CharCnt;


int CheckMaxDamage();

//속도 변수 Lock
int	LockSpeedProtect(Unit *lpChar );
//속도 변수 UnLock
int UnlockSpeedProtect(Unit *lpChar );
