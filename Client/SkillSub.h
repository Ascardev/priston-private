
//스킬을 오픈한다
int OpenPlaySkill( sSKILL *lpSkill );
//스킬 공격을 시도
int PlaySkillAttack( sSKILL *lpSkill , Unit *lpChar );
//스킬 적용 거리를 구한다
int GetSkillDistRange( sSKILL *lpSkill , int AttackRange , int AttackMode );
//스킬 공격을 시도
int PlaySkillLoop( int SkillCode , Unit *lpChar );

//잔상용 스킬색상 선택
int SetSkillMotionBlurColor(int dwSkillCode, Unit *lpChar);
//범위 스킬 확인
int GetSkillPower(Unit *lpChar , Unit *lpChar2 , int dx, int dy, int dz );
//스킬 습득 이펙트
int	LearnSkillEffect(Unit *lpChar=0 );
//스킬감시
int CheckPlaySkill();

void MasterSkill();
