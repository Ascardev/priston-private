/*----------------------------------------------------------------------------*
*	���ϸ� :  Morayion.h	
*	�ϴ��� :  ����̿��� ��ų ���
*	�ۼ��� :  ����������Ʈ 9��
*	������ :  �ڻ� 
*-----------------------------------------------------------------------------*/	
#define MAX_CONTINUE_SKILL		10

//////////////// ��������κ�
int sinCheckSkillUseOk(sSKILL *lpSkill);
int sinUseManaStamina(sSKILL *lpSkill);
int sinContinueSkillSet(sSKILL *lpSkill,int Flag = 0);
int sinCheckContinueSkill();
int sinSwitchSkill(sSKILL *pSkill);

//����
int F_Sword_Blast();
int F_HolyBody();	
int F_Physical_Traning();
int F_Double_Crash();	

int F_Holy_Valor();
int F_Brandish();
int F_Piercing();
int F_Drastic_Spirit();

int F_S_Mastery();
int F_D_Inhalation();
int F_Holy_Incantation();
int F_Grand_Cross();

int F_Divine_Piercing();
int F_Godly_Shield();
int F_God_Bless();
int F_Sword_Of_Justice();

int F_S_Breaker();
int F_C_Moon();
int F_S_Blade();
int F_H_Benedic();

//ħǹ��
int F_S_Strike();
int F_Farina();
int F_D_Mastery();
int F_V_Spear();

int F_Windy();
int F_Twist_Javelin();
int F_Soul_Sucker();
int F_Fire_Javelin();

int F_Split_Javelin();
int F_T_Of_Valhalla();
int F_Lightning_Javelin();
int F_Storm_Javelin();

int F_Hall_Of_Valhalla();
int F_X_Rage();
int F_Frost_Javelin();
int F_Vengeance();

int F_Talaria();
int F_G_Coup();
int F_S_Arcuda();
int F_S_Fear();

//��˾
int F_Healing();
int F_HolyBolt();
int F_M_Spark();
int F_HolyMind();

int F_Meditation();
int F_Divine_Lightning();
int F_Holy_Reflection();
int F_Grand_Healing();

int F_Vigor_Ball();
int F_Resurrection();
int F_Extinction();
int F_Virtual_Life();

int F_Glacial_Spike();
int F_Regeneration_Field();
int F_Chain_Lightning();
int F_Summon_Muspell();

int F_S_Impact();
int F_P_Ice();
int F_S_Ramiel();
int F_B_Krishna();

//ħ��ʦ
int F_Agony();
int F_FireBolt();
int F_Zenith();
int F_ZenithFromServer(int Time);
int F_FireBall();

int F_Mental_Mastery();
int F_Watornado();
int F_Enchant_Weapon();
int F_Dead_Ray();

int F_Energy_Shield();
int F_Diastrophism();
int F_Spirit_Elemental();
int F_D_Sword();

int F_Fire_Elemental();
int F_Flame_Wave();
int F_Distortion();
int F_Meteo();

int F_Silraphim();
int F_V_Tenus();
int F_P_Ignis();
int F_T_Anima();

//����
int F_Dark_Bolt();
int F_Dark_Wave();
int F_Inertia();
int F_Inner_Peace();
int F_Spiritual_Flare();
int F_Spiritual_Manacle();
int F_Chasing_Hunt();
int F_Advent_Migal();
int F_Rainmaker();
int F_Phantom_Call();
int F_Haunt();
int F_Scratch();
int F_Crimson_Knight();
int F_Judgement();
int F_Advent_Midranda();
int F_Mourning_pray();
int F_Creed();
int F_Press();
int F_Phantom_Nail();
int F_Occult_Life();

/////////////// ����Ʈ
//������ ����Ʈ
extern int Sword_Blast_UseMana[10];
extern int Sword_Blast_Damage[10][2];
extern int Sword_Blast_ShootingRange[10];

//Ȧ�� �ٵ�
extern int HolyBody_UseMana[10];
extern int HolyBody_Absorb[10];
extern int HolyBody_Time[10];

//������ Ʈ���̴�
extern int P_Traning_Stamina[10];

//���� ũ����
extern int D_Crash_UseMana[10];
extern int D_Crash_Damage[10];
extern int D_Crash_Critical[10];

//Ȧ�� ���� 
extern int Holy_Valor_Damage[10];
extern int Holy_Valor_Time[10];
extern int Holy_Valor_Mana[10];

//�귻��
extern int Brandish_Range[10];
extern int Brandish_Damage[10];
extern int Brandish_Mana[10];

//�Ǿ��
extern int Piercing_Damage[10];
extern int Piercing_Range[10];
extern int Piercing_Mana[10];

//�巹��ƽ ���Ǹ�
extern int Drastic_Spirit_Defense[10];
extern int Drastic_Spirit_Time[10];
extern int Drastic_Spirit_Mana[10];

//������ �����͸�
//extern int Flame_Brandish_Damage[10][2];
//extern int Flame_Brandish_UseMana[10];
extern int Sword_Mastery_DamagePercent[10];

//����� ��Ȧ���̼�
extern int D_Inhalation_Life[10];
extern int D_Inhalation_Block[10];
extern int D_Inhalation_Time[10];
extern int D_Inhalation_UseMana[10];

//Ȧ�� �������̼�
extern int H_Incantation_Success[10];
extern int H_Incantation_AddLife[10];
extern int H_Incantation_Time[10];
extern int H_Incantation_UseMana[10];

//�׷��� ũ�ν�
extern int Grand_Cross_Damage[10];
extern int Grand_Cross_AttackRate[10];
extern int Grand_Cross_UndeadDamage[10];
extern int Grand_Cross_UseMana[10];

//4�� ��ų
//����� �Ǿ��
extern int  Divine_Piercing_DamagePercent[10];
extern int  Divine_Piercing_AddHit[10];
extern int	Divine_Piercing_AttackNum[10];
extern int  Divine_Piercing_UseMana[10];

//���� ����
extern int Godly_Shield_AbsorbPercent[10];
extern int Godly_Shield_Time[10];
extern int Godly_Shield_UseMana[10];

//�� ����
extern int God_Bless_AddDamage[10];
extern int God_Bless_Time[10];
extern int God_Bless_UseMana[10];

//������ ���� ����ƽ��
extern int Sword_Of_Justice_DamagePercent[10];
extern int Sword_Of_Justice_Area[10];
extern int Sword_Of_Justice_UseMana[10];


/////////// ��Ʋ��Ÿ
//���� ��Ʈ����ũ
extern int S_Strike_UseMana[10];
extern int S_Strike_Damage[10][2];
//extern int S_Strike_Stun[10]; ���� �̻��

//�ĸ���
extern int Farina_UseMana[10];
extern int Farina_Speed[10];
extern int Farina_AttackRate[10];

//����������͸�
extern int T_Mastery_Damage[10];

//��� ���Ǿ�
extern int V_Spear_UseMana[10];
extern int V_Spear_Damage[10][2];

//����
extern int Windy_Attack_Rating[10];
extern int Windy_Time[10];      
extern int Windy_Mana[10];     

//Ʈ����Ʈ ���
extern int Twist_Javelin_Damage[10];
extern int Twist_Javelin_Attack_Rating[10];
extern int Twist_Javelin_Mana[10];      

//�ҿ� ��Ŀ
extern int Soul_Sucker_Absorb[10];  
extern int Soul_Sucker_Mana[10];    

//���̾� ���
extern int Fire_Javelin_Damage[10][2];
extern int Fire_Javelin_Mana[10];

//���ø� ���
extern int Split_Javelin_AttackNum[10];
extern int Split_Javelin_Damage[10];
extern int Split_Javelin_AttackRate[10];
extern int Split_Javelin_UseMana[10];

//Ʈ���̾��� ���� ���Ҷ�
extern int T_Of_Valhalla_Damage[10];
extern int T_Of_Valhalla_Time[10];
extern int T_Of_Valhalla_UseMana[10];

//����Ʈ�� �ں���
extern int Lightning_Javelin_Damage[10][2];
extern int Lightning_Javelin_UseMana[10];

//���� �ں���
extern int Storm_Javelin_Damage[10];
extern int Storm_Javelin_UseMana[10];

//4�� ��ų
//����� ���Ҷ�
extern int Hall_Of_Valhalla_AddEvation[10];  //�߰� ȸ�Ƿ� ���
extern int Hall_Of_Valhalla_Time[10];        //�����ð�
extern int Hall_Of_Valhalla_UseMana[10];

//���� ����
extern int X_Rage_DamagePercent[10];   //���ݷ� ����
extern int X_Rage_Area[10];            //���� ����
extern int X_Rage_UseMana[10];

//���ν�Ʈ ���
extern int Frost_Javelin_IceAddDamage[10][2];
extern int Frost_Javelin_SpeedSubPercent[10];
extern int Frost_Javelin_IceTime[10];
extern int Frost_Javelin_Time[10];
extern int Frost_Javelin_UseMana[10];


//��þ��
extern int Vengeance_DamagePercent[10];
extern int Vengeance_AddCritical[10];
extern int Vengeance_Range[10];
extern int Vengeance_UseMana[10];

// �������
extern int Talaria_MoveSpeed[10];
extern int Talaria_Time[10];
extern int Talaria_UseMana[10];
// �����ǹ
extern int G_Coup_Damage[10];
extern int G_Coup_Hit[10];
extern int G_Coup_UseMana[10];
// ������
extern int S_Arcuda_Damage[10][2];
extern int S_Arcuda_AtkRating[10];
extern int S_Arcuda_PetHp[10];
extern int S_Arcuda_Defanse[10];
extern int S_Arcuda_UseMana[10];
// ����ͻϮ
extern int S_Fear_Damage[10];
extern int S_Fear_AddCritical[10];
extern int S_Fear_UseMana[10];


////////////������Ƽ��
//����
extern int Healing_UseMana[10];
extern int Healing_Heal[10][2];

//Ȧ�� ��Ʈ
extern int HolyBolt_UseMana[10];
extern int HolyBolt_Damage[10][2];

//��Ƽ����ũ
extern int M_Spark_UseMana[10];
extern int M_Spark_Damage[10][2];
extern int M_Spark_Num[10];


//Ȧ�� ���ε�
extern int HolyMind_UseMana[10];
extern int HolyMind_DecDamage[10];
extern int HolyMind_Time[10];

//�޵����̼�
extern float Meditation_Regen[10];

//����� ����Ʈ��
extern int Divine_Lightning_Damage[10][2];
extern int Divine_Lightning_Num[10];
extern int Divine_Lightning_Mana[10];

//Ȧ�� ���÷���
extern int Holy_Reflection_Return_Damage[10];
extern int Holy_Reflection_Time[10];
extern int Holy_Reflection_Mana[10];

//�׷��� ����
extern int Grand_Healing[10][2];
extern int Grand_Healing_Range[10];
extern int Grand_Healing_Mana[10];

//��� ��
extern int Vigor_Ball_Damage[10][2];
extern int Vigor_Ball_UseMana[10];

//��������
extern int Resurrection_Percent[10];
extern int Resurrection_Exp[10];
extern int Resurrection_UseMana[10];

//�ͽ��ü�
extern int Extinction_Percent[10];
extern int Extinction_Amount[10];
extern int Extinction_UseMana[10];

//���߾� ������
extern int Virtual_Life_Percent[10];
extern int Virtual_Life_Time[10];
extern int Virtual_Life_UseMana[10];

//4�� ��ų
//�۷��̼� ��Ʈ����ũ
extern int Glacial_Spike_Damage[10][2];       //���ݷ�
extern int Glacial_Spike_Area[10];            //���� ����      
extern int Glacial_Spike_UseMana[10]; 

//�����ʷ��̼� �ʵ�
extern float Regeneration_Field_LifeRegen[10];   //ü�� ����� �߰�
extern float Regeneration_Field_ManaRegen[10];   //��� ����� �߰�
extern int   Regeneration_Field_Time[10];        //���ӽð�
extern int   Regeneration_Field_Area[10];        //��ȿ����
extern int   Regeneration_Field_UseMana[10];

//ü�ζ���Ʈ��
extern int Chain_Lightning_Damage[10][2];           //���ݷ�
extern int Chain_Lightning_Num[10];                 //���� ����
extern int Chain_Lightning_Range[10];               //���� �Ÿ�
extern int Chain_Lightning_UseMana[10];

//���� �½���
extern int Summon_Muspell_Damage[10][2];
extern int Summon_Muspell_Attack_Delay[10];			// ���ݵ�����
extern int Summon_Muspell_UndeadAbsorbPercent[10];  //�𵥵��� ���ݷ� ���ġ
extern int Summon_Muspell_BlockPercent[10];         //���� �����
extern int Summon_Muspell_Time[10];					//�����ð�
extern int Summon_Muspell_UseMana[10];   

/////////////������
//����
extern int Agony_UseMana[10];
extern int Agony_ConvLife[10];

//���̾� ��Ʈ
extern int FireBolt_UseMana[10];
extern int FireBolt_Damage[10][2];

//���Ͼ�
extern int Zenith_UseMana[10];
extern int Zenith_Element[10];
extern int Zenith_Time[10];


//���̾� ��
extern int FireBall_UseMana[10];
extern int FireBall_Damage[10][2];
extern int FireBall_Range[10];
extern int FireBall_Area[10];

//������ ����
extern int Mental_Mastery_Mana[10];
//extern int Energy_Shelter_Down_Damage[10];
//extern int Energy_Shelter_Time[10];
//extern int Energy_Shelter_Mana[10];

//���������
extern int Watornado_Damage[10][2];
extern int Watornado_Range[10];
extern int Watornado_Mana[10];
extern int Watornado_Area[10];

//��� ����
extern int Enchant_Weapon_Damage_Ice[10][2];
extern int Enchant_Weapon_Damage_Fire[10][2];
extern int Enchant_Weapon_Damage_Lightning[10][2];
extern int Enchant_Weapon_Time[10];
extern int Enchant_Weapon_Mana[10];

//���� ����
extern int Dead_Ray_Damage[10][2];
extern int Dead_Ray_Range[10];
extern int Dead_Ray_Mana[10];

//������ ����
extern int Energy_Shield_DecDamage[10];
extern int Energy_Shield_Time[10];
extern int Energy_Shield_UseMana[10];

//���̿� ��Ʈ������
extern int Diastrophism_Damage[10][2];
extern int Diastrophism_Area[10];
extern int Diastrophism_UseMana[10];

//���Ǹ� ������Ż
extern float Spirit_Elemental_RegenMana[10];
extern int Spirit_Elemental_Damage[10];
extern int Spirit_Elemental_Time[10];
extern int Spirit_Elemental_UseMana[10];

//��� ������
extern int Dancing_Sword_IceDamage[10][2];
extern int Dancing_Sword_FireDamage[10][2];
extern int Dancing_Sword_AttackDelay[10];
extern int Dancing_Sword_Time[10];
extern int Dancing_Sword_UseMana[10];

//**4�� ��ų

//���̾� ������Ż 
extern int Fire_Elemental_Damage[10][2];  //������Ÿ ���ݷ�
extern int Fire_Elemental_Hit[10];        //���߷�
extern int Fire_Elemental_Life[10];       //�����
extern int Fire_Elemental_UseMana[10];

//�÷��� ���̺�
extern int Flame_Wave_FireDamage[10][2];	  //�� ���ݷ�
extern int Flame_Wave_Area[10];			      //���� ����
extern int Flame_Wave_UseMana[10];

//��Ʈ�ϼ�
extern int Distortion_SpeedSubPercent[10];    //�ӵ� ���� 
extern int Distortion_DamageSubPercent[10];   //���ݷ� ����
extern int Distortion_Area[10];     
extern int Distortion_Time[10];
extern int Distortion_UseMana[10];   

//�ٻ���ʯ
extern int Meteo_Damage[10][2];
extern int Meteo_Area[10];
extern int Meteo_UseMana[10];

// ���ǻ���
extern int Silraphim_Damage[10][2];
extern int Silraphim_Range[10];
extern int Silraphim_UseMana[10];
//��С֮��
extern int V_Tenus_SubSpeed[10];
extern int V_Tenus_Time[10];
extern int V_Tenus_Range[10];
extern int V_Tenus_UseMana[10];
// ��ʥϴ��
extern int P_Ignis_Dmage[10][2];
extern int P_Ignis_Area[10];
extern int P_Ignis_Hit[10];
extern int P_Ignis_UseMana[10];
//��ʥ����
extern int T_Anima_Dmage[10];
extern int T_Anima_Time[10];
extern int T_Anima_UseMana[10];

//�������
extern int S_Breaker_Damage[10];
extern int S_Breaker_AddHit[10];
extern int S_Breaker_UseMana[10];
//�����ػ�
extern int C_Moon_Damage[10];
extern int C_Moon_Area[10];
extern int C_Moon_UseMana[10];
//�ϵ��ػ�
extern int S_Blade_Damage[10];
extern int S_Blade_UndeadDamage[10];
extern int S_Blade_UseMana[10];
//����֮��
extern int H_Benedic_Hit[10];
extern int H_Benedic_Time[10];
extern int H_Benedic_UseMana[10];


// �������
extern int Talaria_Time[10];
extern int Talaria_UseMana[10];
// �����ǹ
extern int G_Coup_UseMana[10];
// ������
extern int S_Arcuda_UseMana[10];
// ����ͻϮ
extern int S_Fear_UseMana[10];


// ��ʥ�粨
extern int S_Impact_Damage[10][2];
extern int S_Impact_Range[10];
extern int S_Impact_UseMana[10];
// ��֮����
extern int P_Ice_Damge[10][2];
extern int P_Ice_Frozen[10];
extern int P_Ice_UseMana[10];
// ����ѩ
extern int S_Ramiel_Damage[10][2];
extern int S_Ramiel_Area[10];
extern int S_Ramiel_Num[10];
extern int S_Ramiel_UseMana[10];
// ��Ůɢ��
extern int B_Krishna_Evasion[10];
extern int B_Krishna_Abs[10];
extern int B_Krishna_Time[10];
extern int B_Krishna_UseMana[10];


// ���ǻ���
extern int Silraphim_UseMana[10];
// ��С֮��
extern int V_Tenus_UseMana[10];
// ��ʥϴ��
extern int P_Ignis_UseMana[10];
// ��ʥ����
extern int T_Anima_Time[10];
extern int T_Anima_UseMana[10];

//��������
extern int Dark_Bolt_Damage[10];
extern int Dark_Bolt_UseMana[10];

//���ڲ���
extern int Dark_Wave_Damage[10];
extern int Dark_Wave_UseMana[10];

//�����׻�
extern int Inertia_Speed[10];
extern int Inertia_Atk[10];
extern int Inertia_Area[10];
extern int Inertia_Time[10];
extern int Inertia_UseMana[10];

//����ƽ��
extern int Inner_Peace_AddMana[10];

//��������
extern int Spiritual_Flare_Damage[10];
extern int Spiritual_Flare_Rnage[10];
extern int Spiritual_Flare_Area[10];
extern int Spiritual_Flare_UseMana[10];

//������
extern int Spiritual_Manacle_Ratio[10];
extern int Spiritual_Manacle_Time[10];
extern int Spiritual_Manacle_UseMana[10];

//��ȡ
extern int Chasing_Hunt_Sight[10];
extern int Chasing_Hunt_Time[10];
extern int Chasing_Hunt_UseMana[10];

//���˶�
extern int Advent_Migal_Atk[10];
extern int Advent_Migal_Time[10];
extern int Advent_Migal_UseMana[10];

//����ʦ
extern int Rainmaker_Abs[10];
extern int Rainmaker_AtkRating[10];
extern int Rainmaker_Time[10];
extern int Rainmaker_UseMana[10];

//½�����
extern int Phantom_Call_Damage[10];
extern int Phantom_Call_Area[10];
extern int Phantom_Call_UseMana[10];

//����ػ�
extern int Haunt_Damage[10];
extern int Haunt_Abs[10];
extern int Haunt_UseMana[10];

//ץ��
extern int Scratch_Damage[10];
extern int Scratch_UseMana[10];

//��Ѫ֮ҹ
extern int Crimson_Knight_Atk[10][2];
extern int Crimson_Knight_AtkRating[10];
extern int Crimson_Knight_PetHp[10];
extern int Crimson_Knight_Defanse[10];
extern int Crimson_Knight_UseMana[10];

//����
extern int Judgement_Damage[10];
extern int Judgement_UseMana[10];

//�׵�����
extern int Advent_Midranda_Speed[10];
extern int Advent_Midranda_Area[10];
extern int Advent_Midranda_Time[10];
extern int Advent_Midranda_UseMana[10];

//���ն���
extern int Mourning_Pray_Damage[10];
extern int Mourning_Pray_Area[10];
extern int Mourning_Pray_UseMana[10];

//��������
extern int Creed_AddMP[10];
extern int Creed_AddSP[10];
extern int Creed_Time[10];
extern int Creed_UseMana[10];

//����֮��
extern int Press_Deity_Damage[10];
extern int Press_Deity_Area[10];
extern int Press_UseMana[10];

//����֮צ
extern int Phantom_Nail_Damage[10];
extern int Phantom_Nail_Area[10];
extern int Phantom_Nail_UseMana[10];

//�߼�����
extern int Occult_Lift_HP[10];
