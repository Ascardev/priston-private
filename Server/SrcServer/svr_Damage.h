//공격 수신 받음
int rsRecvAttackData_Old(User *lpPlayInfo , TRANS_ATTACKDATA *lpTransAttackData , Unit *lpTargetChar , int Type );
//공격 범위형 수신
int rsRecvRangeAttackData_Old(User *lpPlayInfo , TRANS_SKIL_ATTACKDATA *lpTransSkilAttackData , int Type );
//공격 범위형 유저 수신
int rsRecvRangeAttackUserData_Old(User *lpPlayInfo , TRANS_SKIL_ATTACKDATA *lpTransSkilAttackData );
DWORD	dm_GetDamgeChkSum_S2V(TRANS_ATTACKDATA *lpTransAttackData);

//공격 수신 받음
int rsRecvAttackData(User *lpPlayInfo , TRANS_ATTACKDATA2 *lpTransAttackData );
//범위공격 수신 받음
int rsRecvRangeAttackData(User *lpPlayInfo , TRANS_SKIL_ATTACKDATA2 *lpTransRangeAttackData );;

//범위 공격 첵크섬
DWORD	dm_GetRangeDamgeChkSum( TRANS_SKIL_ATTACKDATA2 *lpTransSkilAttackData2 );
//범위 공격 첵크섬
DWORD	dm_GetDamgeChkSum( TRANS_ATTACKDATA2 *lpTransAttackData2 );
//코맨드 첵크섬
DWORD	dm_GetCommandChkSum( smTRANS_COMMAND *lpTransCommand , DWORD dwObjectSerial );

//레벨로 정상적인 스킬 코드인지 검사
int rsCheckSkillLevel(User *lpPlayInfo , DWORD dwSkillCode );

//데미지 데이타 오류를 군서버 로그에 기록
int rsRecordDamageError(User *lpPlayInfo , smTRANS_COMMAND *lpTransCommand );
