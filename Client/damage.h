
//���� ���� ýũ��
DWORD	dm_GetRangeDamgeChkSum( TRANS_SKIL_ATTACKDATA2 *lpTransSkilAttackData2 );
//���� ���� ýũ��
DWORD	dm_GetDamgeChkSum( TRANS_ATTACKDATA2 *lpTransAttackData2 );
//S2C ���� ýũ��
DWORD	dm_GetDamgeChkSum_S2V( TRANS_ATTACKDATA *lpTransAttackData );
//�ڸǵ� ýũ��
DWORD	dm_GetCommandChkSum( smTRANS_COMMAND *lpTransCommand , DWORD dwObjectSerial );

int dm_SendTransDamage(Unit *lpChar , int PowParam1, int PowParam2, int AttackState, int Resistance, DWORD dwSkillCode , int UseAccuracy);


//������ ���� ���� ���� (��)
int dm_SelectRange( int x, int y, int z , int range , int UseAttackRating , int SelCount );
//������ ���� ���� ���� (��)
int dm_SelectRange( int x, int y, int z , int range , int UseAttackRating );
//������ ���� ���� ���� (�ڽ�)
int dm_SelectRangeBox(Unit *lpCurChar , RECT *lpRect , int UseAttackRating );
//������ ���� ���� ���� (����� ����Ʈ��)
int dm_SelectDamageCount(Unit *lpCurChar , int SelCount , int Size );
//������ ���� ���� ���� (ü�ζ���Ʈ��)
int dm_SelectDamageCount(Unit *lpCurChar , Unit *lpTragetChar, int SelCount , int Size );
//������ ���� ���� ���� (ü�ζ���Ʈ��)
int dm_SelectDamageChainCount(Unit *lpCurChar , Unit *lpTragetChar, int SelCount , int Size );

//���õ� �������� ��Ͽ� ĳ�� ���� �߰�
int dm_AddRangeDamage(Unit *lpChar );

//�������� ������ ����
int dm_SendRangeDamage( int x, int y, int z, Unit *lpMainTraget ,int PowParam1, int PowParam2, int AttackState , int Registance ,  DWORD dwSkillCode );

//������ ��ȣȭ ��� ����
int RecvDamagePacketModule( TRANS_FUNC_MEMORY *lpTransFuncModule );
int RecvDamagePacketModule2( TRANS_FUNC_MEMORY *lpTransFuncModule );
//��Ŷ ���� ��ȣȭ ��� ����
int RecvDynPacketModule( TRANS_FUNC_MEMORY *lpTransFuncModule );

extern DWORD	dmAttackCount;

extern Unit	*lpSelected_Char[SKIL_ATTACK_CHAR_MAX];
extern int	dmSelected_CharCnt;


int CheckMaxDamage();

//�ӵ� ���� Lock
int	LockSpeedProtect(Unit *lpChar );
//�ӵ� ���� UnLock
int UnlockSpeedProtect(Unit *lpChar );
