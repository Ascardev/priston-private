int sinAssaSkillEffectKeyDown();

int sinAssaSkillEffectProcess(cASSAEFFECT *pEffect);

int sinSkillEffect_Brandish(Unit *pChar);
int sinSkillEffect_Piercing(Unit *pChar);
int sinSkillEffect_Piercing_Attack(Unit *pChar);
int sinSkillEffect_DrasticSpirit(Unit *pChar);

int sinSkillEffect_Energy_Shelter(Unit *pChar);

int sinSkillEffect_Great_Healing(Unit *pChar);
int sinSkillEffect_Great_Healing_Party(Unit *pChar);
int sinSkillEffect_Holy_Reflection(Unit *pChar,int Time);
// ��ʥ����
int sinSkillEffect_Holy_ReflectionEffect(Unit *pChar,int Time);
int sinSkillEffect_Holy_Reflection_Defense(Unit *pChar);
int sinSkillEffect_HolyMind(Unit *pChar,int Time);

//�������
int sinSkillEffect_Breaker(Unit *curChar, Unit *desChar);
int sinSkillEffect_Breaker2(Unit *pChar);
//�����ػ�
int sinSkillEffect_Moon(Unit *pChar);
//�ϵ��ػ�
int sinSkillEffect_Blade(Unit *pChar);
//��ʥϴ��
int sinSkillEffect_Anima(Unit *pChar);

int sinSkillEffect_Soul_Sucker(Unit *pChar , Unit *DesChar);
int sinSkillEffect_Windy(Unit *pChar);
int sinSkillEffect_Windy_Gather(Unit *pChar);
// ��Ұ���
int sinSkillEffect_P_Dash(Unit *pChar);