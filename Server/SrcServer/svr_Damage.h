//���� ���� ����
int rsRecvAttackData_Old(User *lpPlayInfo , TRANS_ATTACKDATA *lpTransAttackData , Unit *lpTargetChar , int Type );
//���� ������ ����
int rsRecvRangeAttackData_Old(User *lpPlayInfo , TRANS_SKIL_ATTACKDATA *lpTransSkilAttackData , int Type );
//���� ������ ���� ����
int rsRecvRangeAttackUserData_Old(User *lpPlayInfo , TRANS_SKIL_ATTACKDATA *lpTransSkilAttackData );
DWORD	dm_GetDamgeChkSum_S2V(TRANS_ATTACKDATA *lpTransAttackData);

//���� ���� ����
int rsRecvAttackData(User *lpPlayInfo , TRANS_ATTACKDATA2 *lpTransAttackData );
//�������� ���� ����
int rsRecvRangeAttackData(User *lpPlayInfo , TRANS_SKIL_ATTACKDATA2 *lpTransRangeAttackData );;

//���� ���� ýũ��
DWORD	dm_GetRangeDamgeChkSum( TRANS_SKIL_ATTACKDATA2 *lpTransSkilAttackData2 );
//���� ���� ýũ��
DWORD	dm_GetDamgeChkSum( TRANS_ATTACKDATA2 *lpTransAttackData2 );
//�ڸǵ� ýũ��
DWORD	dm_GetCommandChkSum( smTRANS_COMMAND *lpTransCommand , DWORD dwObjectSerial );

//������ �������� ��ų �ڵ����� �˻�
int rsCheckSkillLevel(User *lpPlayInfo , DWORD dwSkillCode );

//������ ����Ÿ ������ ������ �α׿� ���
int rsRecordDamageError(User *lpPlayInfo , smTRANS_COMMAND *lpTransCommand );
