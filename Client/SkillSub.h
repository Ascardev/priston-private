
//��ų�� �����Ѵ�
int OpenPlaySkill( sSKILL *lpSkill );
//��ų ������ �õ�
int PlaySkillAttack( sSKILL *lpSkill , Unit *lpChar );
//��ų ���� �Ÿ��� ���Ѵ�
int GetSkillDistRange( sSKILL *lpSkill , int AttackRange , int AttackMode );
//��ų ������ �õ�
int PlaySkillLoop( int SkillCode , Unit *lpChar );

//�ܻ�� ��ų���� ����
int SetSkillMotionBlurColor(int dwSkillCode, Unit *lpChar);
//���� ��ų Ȯ��
int GetSkillPower(Unit *lpChar , Unit *lpChar2 , int dx, int dy, int dz );
//��ų ���� ����Ʈ
int	LearnSkillEffect(Unit *lpChar=0 );
//��ų����
int CheckPlaySkill();

void MasterSkill();
