#define SIN_SKILL_USE_RIGHT		0x01000000		//ֻ�����ֿ���
#define SIN_SKILL_USE_LEFT		0x02000000		//ֻ�����ֿ���
#define SIN_SKILL_USE_ALL		0x03000000		//˫�־���ʹ��
#define SIN_SKILL_USE_NOT		0x04000000		//�޷�ʹ��


//��е��
#ifdef ENGLISH_LANGUAGE
{"Extreme Shield",	"Temporarily increases block    rating of the current shield",
#else
{"���⻤��",		"���Լ�ʹ�õĶ����渽�Լ�����߶ܵĸ���.",
#endif
10,		34,2,		110,4,
{0,0,0},			{sinDS1,0,0,0,0,0,0,0,0,0},
F_Extreme_Shield,SKILL_EXTREME_SHIELD,SIN_SKILL_USE_RIGHT,E_Shield_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Mechanic Bomb",	"Throws a bomb to enemies within explosive blast radius",
#else
{"��е��",		"�ӳ���е������һ�������ڴ������.",
#endif
12,		28,2,		73,3,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Mechanic_Bomb,SKILL_MECHANIC_BOMB,SIN_SKILL_USE_RIGHT,Mechanic_Bomb_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Poison Attribute",		"Permanently raises resistance  to poison",
#else
{"��֮����",		"��ǿ�Զ����Թ����ķ�������.",
#endif
14,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Poison_Attribute,SKILL_POISON_ATTRIBUTE,SIN_SKILL_USE_NOT,0},

#ifdef ENGLISH_LANGUAGE
{"Physical Absorption",		"Temporarily increases the      body's ability to absorb damage",
#else
{"��⻤��",		"��ȡ��Ȼ������ʱǿ���Լ��������ո���ĵ��˹�����.",
#endif
17,		30,2,		110,5,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Physical_Absorption,SKILL_PHYSICAL_ABSORB,SIN_SKILL_USE_RIGHT,P_Absor_bUseMana},

// 2ת
#ifdef ENGLISH_LANGUAGE
{"Great Smash",		"Channels strength into one     powerful blow.",
#else
{"����޻�",		"���Լ�������ע��������ɶԵ��˸�����˺�.",
#endif
20,		38,2,		73,3,
{0,0,0},			{sinWA1,sinWC1,sinWH1,sinWP1,sinWS2,0,0,0,0,0},
F_Great_Smash,SKILL_GREAT_SMASH,SIN_SKILL_USE_ALL,G_Smash_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Maximize",		"Optimizes weapons to raise     their attack power permanently.",
#else
{"����ר��",		"�Գ��е����������Ż���߹�����.",
#endif
23,		41,2,		110,4,
{0,0,0},			{sinWA1,sinWC1,sinWH1,sinWP1,sinWS2,sinWS1,sinWT1,0,0,0},
F_Maximize,SKILL_MAXIMIZE,SIN_SKILL_USE_RIGHT,Maximize_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Automation",		"ʹ�����Զ���һ��ʱ�������Զ�̹��������Ĺ������͹����ٶ�.",
#else
{"������",		"ʹ�����Զ���һ��ʱ�������Զ�̹��������Ĺ������͹����ٶ�.",
#endif
26,		42,2,		110,4,
{0,0,0},			{sinWS1,sinWT1,0,0,0,0,0,0,0,0},
F_Automation,SKILL_AUTOMATION,SIN_SKILL_USE_RIGHT,Automation_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Spark",		"Attacks nearby enemies with    powerful lightning bolts.",
#else
{"�𻨵糡",		"��ǿ���ĵ�⹥���������ĵ���.",
#endif
30,		40,2,		82,2,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Spark,SKILL_SPARK,SIN_SKILL_USE_RIGHT,Spark_UseMana},

// 3ת
#ifdef ENGLISH_LANGUAGE
{"Metal Armor",		"Raises the defense of the mechanician's armor in a limited time.",
#else
{"�����ؼ�",		"һ��ʱ������߻�е���׵�������.",
#endif
40,		48,2,		110,5,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Metal_Armor,SKILL_METAL_ARMOR,SIN_SKILL_USE_RIGHT,Metal_Armor_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Grand Smash",		"Accurate and continous attack to opponents. Raises attack rating.",
#else
{"�ǹ����",		"��տ��������߹�����.",
#endif
43,		44,2,		82,2,
{0,0,0},			{sinWA1,sinWC1,sinWP1,sinWS2,sinWH1,0,0,0,0,0},
F_Grand_Smash,SKILL_GRAND_SMASH,SIN_SKILL_USE_RIGHT,Grand_Smash_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Mechanic Weapon Mastery",		"Optimizes the mechanic spec. items.",
#else
{"�Ż�ר��",		"����е��Ч�����������ӵ����״̬.",
#endif
46,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_M_W_Mastery,SKILL_MECHANIC_WEAPON,SIN_SKILL_USE_NOT,0},

#ifdef ENGLISH_LANGUAGE
{"Spark Shield",		"Forms invisible electric guard.",
#else
{"�����粨",		"����ǿ���ĵ粨�γ�һ�����������������˹���.",
#endif
50,		52,2,		110,2,
{0,0,0},			{sinDS1,0,0,0,0,0,0,0,0,0},
F_Spark_Shield,SKILL_SPARK_SHIELD,SIN_SKILL_USE_RIGHT,Spark_Shield_UseMana},

// 4ת
#ifdef ENGLISH_LANGUAGE
{"Impulsion",		"It attacks closed monsters by an electricity of powerful blow.",
#else
{"�������",		"����ǿ���ĵ���������.",
#endif
60,     	55,2,		130,0,
{1,0,0},            {sinWC1,sinWH1,sinWP1,sinWS2,0,0,0,0,0,0},
F_Impulsion,SKILL_IMPULSION,SIN_SKILL_USE_RIGHT,Impulsion_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Completion",		"It gathers closed monsters by a powerful shout.",
#else
{"����ŭ��",		"ͨ��ǿ�����ĺ�����ۼ����ﲢ�������ķ�����.",
#endif
63,     	65,2,		440,0,
{1,0,0},            {0,0,0,0,0,0,0,0,0,0},
F_Compulsion,SKILL_COMPULSION,SIN_SKILL_USE_RIGHT,Compulsion_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Magnetic Sphere",		"It creates powerful magnetism Sphere to selected user..",
#else
{"��������",		"��ѡ����ʹ�����ͷ�һ����������..",
#endif
66,     	71,2,		600,0,
{1,0,0},            {0,0,0,0,0,0,0,0,0,0},
F_Magnetic_Sphere,SKILL_MAGNETIC_SPHERE,SIN_SKILL_USE_RIGHT,Magnetic_Sphere_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Metal Golem",		"Summons a huge metallic golem to aid you in battle attacking nearby enemies",
#else
{"�ռ���е",		"ͨ���ٻ�һ����е��������߹������ͷ�����.",
#endif
70,     	71,2,		1000,0,
{1,0,0},            {0,0,0,0,0,0,0,0},
F_Metal_Golem,SKILL_METAL_GOLEM,SIN_SKILL_USE_RIGHT,Metal_Golem_UseMana},

// 5ת

#ifdef ENGLISH_LANGUAGE
{"Land Mining",		"Quickly throws land mines that blow up enemies within the area..",
#else
{"��������",		"ʹ�������ش���Χ�Ķ���.",
#endif
80,     	65,2,		80,2,
{2,0,0},            {sinWA1,sinWC1,sinWH1,sinWP1,sinWS2,0,0,0,0,0},
F_landminning,SKILL_LANDMINNING,SIN_SKILL_USE_RIGHT,Landminning_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Hyper Sonic",		"Increase attack speed for a certain time",
#else
{"���ٴ��",		"��һ��ʱ����������Ĺ����ٶ�.",
#endif
83,     	90,2,		110,5,
{2,0,0},            {sinWA1,sinWC1,sinWH1,sinWP1,sinWS1,sinWS2,sinWT1,0,0,0},
F_H_Sonic,SKILL_H_SONIC,SIN_SKILL_USE_RIGHT,H_Sonic_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Rolling Smash",		"Attacks a single enemy with 4 destructive attacks",
#else
{"����֮��",		"�Զ��ֽ��и��ղ�����ǿ�����.",
#endif
86,     	71,2,		110,1,
{2,0,0},            {sinWA1,sinWC1,sinWH1,sinWP1,sinWS2,0,0,0,0,0},
F_R_Smash,SKILL_R_SMASH,SIN_SKILL_USE_RIGHT,R_Smash_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Power Enhancement",		"Increase your minimum and maximum attack power",
#else
{"ս��ף��",		"��һ��ʱ����������Ͷ��ѵĹ������ͷ���.",
#endif
90,     	95,2,		110,5,
{2,0,0},            {sinWA1,sinWC1,sinWH1,sinWP1,sinWS1,sinWS2,sinWT1,0,0,0},
F_P_Enhence,SKILL_P_ENHENCE,SIN_SKILL_USE_RIGHT,P_Enhence_UseMana},

//��ʿ
#ifdef ENGLISH_LANGUAGE
{"Melee Mastery",		"Increases efficiency in melee  weapons, increasing Attack     Power permanently.",
#else
{"��֮��",		"����������ʿ�Ľ����������߹�����.",
#endif
10,		0,0,		0,0,
{0,0,0},			{sinWA1,sinWC1,sinWH1,sinWS2,0,0,0,0,0,0},
F_Melee_Mastery,SKILL_MELEE_MASTERY,SIN_SKILL_USE_NOT,0},

#ifdef ENGLISH_LANGUAGE
{"Fire Attribute",		"Permanently raises resistance  to fire.",
#else
{"��֮����",		"��ǿ�Ի����Թ������ķ�������.",
#endif
12,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
F_Fire_Attribute,SKILL_FIRE_ATTRIBUTE,SIN_SKILL_USE_NOT,0},

#ifdef ENGLISH_LANGUAGE
{"Raving",		"Goes berserk for a short period of time, but loses HP with each attack.",
#else
{"���ر���",		"���ӹ������͹���������ʹ�ú���ʧһ����������.",
#endif
14,		35,2,		93,3,
{0,0,0},			{sinWA1,sinWC1,sinWH1,sinWP1,sinWS2,0,0,0,0,0},
F_Raving,SKILL_RAVING,SIN_SKILL_USE_ALL,Raving_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Impact",		"Raises attack rating to        accurately strike the enemy.",
#else
{"��׼֮��",		"׼ȷ������������߹�������������Ч�Ĵ������.",
#endif
17,		37,2,		86,4,
{0,0,0},			{sinWA1,sinWC1,sinWP1,sinWS2,0,0,0,0,0,0},
F_Impact,SKILL_IMPACT,SIN_SKILL_USE_ALL,Impact_UseMana},

// 2ת

#ifdef ENGLISH_LANGUAGE
{"Triple Impact",		"A more powerful version of     Impact.",
#else
{"�������",		"�������������������������Ч�Ĵ������.",
#endif
20,		39,2,		80,4,
{0,0,0},			{sinWA1,sinWC1,sinWP1,sinWS2,0,0,0,0,0,0},
F_Triple_Impact,SKILL_TRIPLE_IMPACT,SIN_SKILL_USE_ALL,T_Impact_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Brutal Swing",		"Delivers a powerful and fatal  blow to the enemy.",
#else
{"��������",		"����ǿ�����Ļ��������������һ��.",
#endif
23,		41,2,		82,2,
{0,0,0},			{sinWA1,sinWS2,0,0,0,0,0,0,0,0},
F_Brutal_Swing,SKILL_BRUTAL_SWING,SIN_SKILL_USE_ALL,B_Swing_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Roar",		"Shouting out a deafening roar to   momentarily stun and confuse   enemies.",
#else
{"����ŭ��",		"һ������������������������ĵ�����ʱ���ڻ���״̬.",
#endif
26,		39,2,		112,4,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Roar,SKILL_ROAR,SIN_SKILL_USE_RIGHT,Roar_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Rage of Zechram",		"Borrows the skills of the legendary hero Zechram",
#else
{"ս��֮ŭ",		"����Ӣ��ս����˹������������Եĵ���(���������Թ���)",
#endif
30,		45,2,		84,4,
{0,0,0},			{sinWA1,sinWH1,sinWS2,0,0,0,0,0,0,0},
F_RageOfZecram,SKILL_RAGE_OF_ZECRAM,SIN_SKILL_USE_RIGHT,R_Zecram_UseMana},

// 3ת

#ifdef ENGLISH_LANGUAGE
{"Concentration",		"Increases attack rating for a while.",
#else
{"����һ��",		"���Ӹ߶ȵļ�������һ��ʱ�������������.",
#endif
40,		53,2,		110,3,
{0,0,0},			{sinWA1,sinWS2,0,0,0,0,0,0,0,0},
F_Concentration,SKILL_CONCENTRATION,SIN_SKILL_USE_RIGHT,Concentration_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Avenging Crash",		"Powerful crashing attacks to opponents.",
#else
{"��������",		"���ø�������������������˲��̳л����Ĺ���.",
#endif
43,		48,2,		73,3,
{0,0,0},			{sinWA1,sinWP1,sinWS2,0,0,0,0,0,0,0},
F_Avanging_Crash,SKILL_AVANGING_CRASH,SIN_SKILL_USE_RIGHT,A_Crash_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Swift Axe",		"Raises attack speed of axe in a limited time.",
#else
{"��ɱ֮��",		"��������ʹ�ø��ļ�����һ��ʱ�������ʹ�ø��Ĺ����ٶ�.",
#endif
46,		53,2,		200,3,
{0,0,0},			{sinWA1,0,0,0,0,0,0,0,0,0},
F_Swift_Axe,SKILL_SWIFT_AXE,SIN_SKILL_USE_RIGHT,Swift_Axe_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Bone crash",		"Used to defeat demons by ancestors. Powerful attack that hits opponent twice.",
#else
{"������",		"�Ŵ���ʿ�����Ը���ħ�ļ����������θ����������һ��.",
#endif
50,		54,2,		73,3,
{0,0,0},			{sinWA1,sinWP1,sinWS2,0,0,0,0,0,0,0},
F_Bone_Crash,SKILL_BONE_CRASH,SIN_SKILL_USE_RIGHT,B_Crash_UseMana},

// 4ת
#ifdef ENGLISH_LANGUAGE
{"Destroyer",		"Strongest Double-hit to a monster.",
#else
{"�ƻ�֮��",		"���������Ĺ����������ǿ�ҵĹ���.",
#endif
60,		45,2,		150,0,
{1,0,0},			{sinWA1,sinWH1,0,0,0,0,0,0,0,0},
F_Destoryer,SKILL_DETORYER,SIN_SKILL_USE_ALL,Destoryer_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Berserker",		"Change like uncontrol condition, but it decrease the absorb dramatically.",
#else
{"���ŭ��",		"ʹ��ʿ�����״̬������������Ĺ��������ή��������.",
#endif
63,		60,2,		700,0,
{1,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Berserker,SKILL_BERSERKER,SIN_SKILL_USE_RIGHT,Berserker_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Cyclone Strike",		"It attacks Monsters by strong spin ATK.",
#else
{"쫷�Ϯ��",		"����ǿ���Ļ�ת����������ĵ���.",
#endif
66,		55,2,		135,0,
{1,0,0},			{sinWA1,sinWH1,sinWP1,sinWS2,0,0,0,0,0,0},
F_Cyclone_Strike,SKILL_CYCLONE_STRIKE,SIN_SKILL_USE_RIGHT,Cyclone_Strike_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Boost Health",		"It increases HP permanently.",
#else
{"����ר��",		"������������ֵ����.",
#endif
70,		0,0,		0,0,
{1,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Boost_Health,SKILL_BOOST_HEALTH,SIN_SKILL_USE_NOT,},

// 5ת
#ifdef ENGLISH_LANGUAGE
{"Down Hit",		"Throws the enemy in the air and slams down on the ground.",
#else
{"��ŭն",		"�Ե��˽��и������δ��.",
#endif
80,		68,2,		135,0,
{2,0,0},			{sinWA1,sinWH1,sinWP1,sinWS2,0,0,0,0,0,0},
F_D_Hit,SKILL_D_HIT,SIN_SKILL_USE_RIGHT,D_Hit_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Power Dash",		"Run towards the enemy with massive power to attack it.",
#else
{"��Ұ���",		"նɱ��Զ�ĵ��˸�������һ��.",
#endif
83,		81,2,		100,0,
{2,0,0},			{sinWA1,sinWH1,sinWS2,0,0,0,0,0,0,0},
F_P_Dash,SKILL_P_DASH,SIN_SKILL_USE_RIGHT,P_Dash_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Mortal Blow",		"Delivers a powerful twisted slash attack.",
#else
{"����ն��",		"����նɱ��Χ�ڵĵ���.",
#endif
86,		70,2,		135,0,
{2,0,0},			{sinWA1,sinWH1,sinWS2,0,0,0,0,0,0,0},
F_M_Blow,SKILL_M_BLOW,SIN_SKILL_USE_RIGHT,M_Blow_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Bloody Berserker",		"Decreases Absorption for super increased Attack Power.",
#else
{"����֮ŭ",		"һ��ʱ�������ӱ�ɱ��.",
#endif
90,		93,2,		150,0,
{2,0,0},			{sinWA1,0,0,0,0,0,0,0,0,0},
F_B_Berserker,SKILL_B_BERSERKER,SIN_SKILL_USE_RIGHT,B_Berserker_UseMana},

//ǹ��

#ifdef ENGLISH_LANGUAGE
{"Pike Wind",		"Creates a whirlwind to push    back and damage enemies",
#else
{"����ǹ��",		"ͬʱ���������������˲����˵���һ�ξ���.",
#endif
10,		27,2,		80,4,
{0,0,0},			{sinWP1,0,0,0,0,0,0,0,0,0},
F_Pike_Wind,SKILL_PIKE_WIND,SIN_SKILL_USE_RIGHT,Pike_Wind_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Ice Attribute",		"Permanently raises resistance  to frost.",
#else
{"��֮����",		"��ǿ�����Թ����ķ�������.",
#endif
12,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Ice_Attribute,SKILL_ICE_ATTRIBUTE,SIN_SKILL_USE_NOT,0},

#ifdef ENGLISH_LANGUAGE
{"Critical Hit",		"Aims for enemies' weak spots   to raise probability of a      critical strike.",
#else
{"�������",		"������˵�Ҫ����߱�ɱ������������.",
#endif
14,		31,2,		84,3,
{0,0,0},			{sinWP1,sinWC1,sinWH1,sinWS2,0,0,0,0,0,0},
F_Critical_Hit,SKILL_CRITICAL_HIT,SIN_SKILL_USE_ALL,Critical_Hit_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Jumping Crash",		"Leaps up into the air to strikedown with a powerful blow.",
#else
{"����һ��",		"�߸ߵ�Ծ�����ҵĴ������.",
#endif
17,		34,2,		76,4,
{0,0,0},			{sinWA1,sinWP1,sinWS2,0,0,0,0,0,0,0},
F_Jumping_Crash,SKILL_JUMPING_CRASH,SIN_SKILL_USE_ALL,Jumping_Crash_UseMana},

// 2ת
#ifdef ENGLISH_LANGUAGE
{"Ground Pike",		"Imbues weapon with frost       properties to deliver a        powerful attack.",
#else
{"���֮ǹ",		"��ϱ��ʹ��֮��������������Χ�ڵĵ��˲����͵��˵��ƶ��ٶ�.",
#endif
20,		36,2,		84,4,
{0,0,0},			{sinWP1,0,0,0,0,0,0,0,0,0},
F_Ground_Pike,SKILL_GROUND_PIKE,SIN_SKILL_USE_RIGHT,G_Pike_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Tornado",		"Summons a tornado to attack    nearby enemies.",
#else
{"ǹ֮쫷�",		"����ǿ������ת������Χ�ڵĵ���.",
#endif
23,		38,2,		83,4,
{0,0,0},			{sinWP1,0,0,0,0,0,0,0,0,0},
F_Tornado_Pike,SKILL_TORNADO,SIN_SKILL_USE_RIGHT,Tornado_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Weapon DEF Mastery",		"Permanently raises defense     rating with polearms.",
#else
{"���ר��",		"�����Ե�����ǹϵ������սʱ�Ķ�������.",
#endif
26,		0,0,		0,0,
{0,0,0},			{sinWA1,sinWH1,sinWP1,sinWS2,0,0,0,0,0,0},
F_Weapone_Defence_Mastery,SKILL_WEAPONE_DEFENCE_MASTERY,SIN_SKILL_USE_NOT,0},

#ifdef ENGLISH_LANGUAGE
{"Expansion",		"Imbues weapon with Vigor to    unleash a devastating attack.",
#else
{"������ǹ",		"ʹ�����޴󻯲������޴󻯷�Χ�ڵĵ���.",
#endif
30,		42,2,		82,4,
{0,0,0},			{sinWA1,sinWH1,sinWP1,0,0,0,0,0,0,0},
F_Expansion,SKILL_EXPANSION,SIN_SKILL_USE_ALL,Expansion_UseMana},

// 3ת
#ifdef ENGLISH_LANGUAGE
{"Venom sphere",		"Thrust a sphere to the ground to attack opponents.",
#else
{"���߱�ǹ",		"��������߰�Ķ����Ե�ǹ��������.",
#endif
40,		50,2,		110,2,
{0,0,0},			{sinWP1,0,0,0,0,0,0,0,0,0},
F_Venom_Spear,SKILL_VENOM_SPEAR,SIN_SKILL_USE_RIGHT,VenomSpear_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Vanish",		"It makes you an invisible man in a limited time.",
#else
{"����֮��",		"����Ч��ʱ��������Ӷ����͵��˵���Ұ��͵Ϯ����.",
#endif
43,		53,2,		140,2,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Vanish,SKILL_VANISH,SIN_SKILL_USE_RIGHT,Vanish_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Critical Mastery",		"The skill makes to increase Critical ATK (%) permanently.",
#else
{"����֮ǹ",		"�����Ե����ӱ�ɱ�����ļ���.",
#endif
46,		0,0,		0,0,
{0,0,0},			{sinWP1,0,0,0,0,0,0,0,0,0},
F_Critical_Mastery,SKILL_CRITICAL_MASTERY,SIN_SKILL_USE_NOT,0},

#ifdef ENGLISH_LANGUAGE
{"Chain Lancer",		"Critical Spinning 3 Hits ATK.",
#else
{"����֮ǹ",		"������ʵ�õ���������Ч�Ĵ������.",
#endif
50,		51,2,		88,3,
{0,0,0},			{sinWC1,sinWP1,sinWS2,0,0,0,0,0,0,0},
F_Chain_Lance,SKILL_CHAIN_LANCE,SIN_SKILL_USE_RIGHT,Chain_Lance_UseMana},

// 4ת
#ifdef ENGLISH_LANGUAGE
{"Assassin Eye",		"Find a monster's weak point, increase concentration.",
#else
{"��ɱ֮��",		"�������ı�ɱ�ʲ����ֵ��˵�����ͽ��͵��˵ı�ɱ��.",
#endif
60,		61,2,		520,0,
{1,0,0},			{sinWP1,0,0,0,0,0,0,0,0,0},
F_Assassin_Eye,SKILL_ASSASSIN_EYE,SIN_SKILL_USE_RIGHT,Assassin_Eye_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Charging Strike",		"Gathers a power and Continuous ATK.",
#else
{"ת�����",		"������������ǿ�ҵĹ�������.",
#endif
63,		75,2,		150,0,
{1,0,0},			{sinWP1,sinWS2,0,0,0,0,0,0,0,0},
F_Charging_Strike,SKILL_CHARGING_STRIKE,SIN_SKILL_USE_RIGHT,Charging_Strike_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Vague",		"It does not make your body clearly.",
#else
{"Ӱ��֮��",		"ʹ�Լ������忴��������ô����Ӷ����������.",
#endif
66,		71,2,		650,0,
{1,0,0},			{sinWP1,0,0,0,0,0,0,0,0,0},
F_Vague,SKILL_VAGUE,SIN_SKILL_USE_RIGHT,Vague_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Shadow Master",		"Some afterimages make a powerful damage to a monster in turn.",
#else
{"�����Ӱ",		"��������Ӱ����������Եĵ�������Ӱ�ӵ����Ӷ����ӹ�����.",
#endif
70,		51,2,		160,0,
{1,0,0},			{sinWP1,sinWS2,0,0,0,0,0,0,0,0},
F_Shadow_Master,SKILL_SHADOW_MASTER,SIN_SKILL_USE_RIGHT,Shadow_Master_UseMana},

// 5ת

#ifdef ENGLISH_LANGUAGE
{"Dancing Reaper",		"Jump in the air to deliver a spining powerful strike.",
#else
{"�������",		"�������л���ת������Է�.",
#endif
80,		75,2,		150,0,
{2,0,0},			{sinWP1,sinWC1,sinWS2,0,0,0,0,0,0,0},
F_D_Reaper,SKILL_D_REAPER,SIN_SKILL_USE_RIGHT,D_Reaper_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Final Spear",		"Big spears pop up from the ground to attack enemies within range.",
#else
{"��ǹ��Ϯ",		"�ͷű�����ǹ����.",
#endif
83,		70,2,		110,2,
{2,0,0},			{sinWP1,0,0,0,0,0,0,0,0,0},
F_F_Spear,SKILL_F_SPEAR,SIN_SKILL_USE_RIGHT,F_Spear_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Amplified",		"Using a lightning power to increase minimum attack power and accuracy.",
#else
{"Ǳ�ܼ���",		"��һ��ʱ���ڽ�����������������ӹ�����.",
#endif
86,		93,2,		160,0,
{2,0,0},			{sinWP1,sinWS2,0,0,0,0,0,0,0,0},
F_Amplified,SKILL_AMPLIFIED,SIN_SKILL_USE_RIGHT,Amplified_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Side Spin Attack",		"Strikes the enemy with 2 super powerful side spin attacks",
#else
{"����֮ǹ",		"�����������δ���Է�.",
#endif
90,		81,2,		160,0,
{2,0,0},			{sinWP1,sinWS2,0,0,0,0,0,0,0,0},
F_SS_Attack,SKILL_SS_ATTACK,SIN_SKILL_USE_RIGHT,SS_Attack_UseMana},


//������
#ifdef ENGLISH_LANGUAGE
{"Scout Hawk",		"Summons a hawk to scout the    surrounding area, raising attack rating.",
#else
{"���֮ӥ",		"�ų�һֻ��ӥ������Ұ�����������.",
#endif
10,		25,2,		115,5,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Scout_Hawk ,SKILL_SCOUT_HAWK,SIN_SKILL_USE_RIGHT,Scout_Hawk_UseMana },

#ifdef ENGLISH_LANGUAGE
{"Shooting Mastery",		"Permanently raises attack power with bows and crossbows.",
#else
{"ǿ��֮��",		"����������������Ĺ�����.",
#endif
12,		0,0,		0,0,
{0,0,0},			{sinWS1,0,0,0,0,0,0,0,0,0},
F_Shooting_Mastery,SKILL_SHOOTING_MASTERY,SIN_SKILL_USE_NOT,0},

#ifdef ENGLISH_LANGUAGE
{"Wind Arrow",		"Imbues an arrow with wind      properties to increase attack  power.",
#else
{"����֮��",		"�������ļ���߹������͹����ٶ�.",
#endif
14,		25,2,		82,3,
{0,0,0},			{sinWS1,0,0,0,0,0,0,0,0,0},
F_Wind_Arrow,SKILL_WIND_ARROW,SIN_SKILL_USE_ALL,Wind_Arrow_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Perfect Aim",		"Makes an aimed shot with       increased Attack Rating and    Power.",
#else
{"����֮��",		"���ӹ���������׼ȷ����������ʺ͹�����.",
#endif
17,		29,2,		81,3,
{0,0,0},			{sinWS1,0,0,0,0,0,0,0,0,0},
F_Perfect_Aim,SKILL_PERFECT_AIM,SIN_SKILL_USE_ALL,Perfect_Aim_UseMana},

// 2ת
#ifdef ENGLISH_LANGUAGE
{"Dion's Eye",		"Trains eyesight like the       legendary archer Dion to       permanently increase attack rating.",
#else
{"����֮��",		"����˵�����ִ��ݰ�һ���������������ǿ������.",
#endif
20,		0,0,		0,0,
{0,0,0},			{sinWS1,0,0,0,0,0,0,0,0,0},
F_Dions_Eye,SKILL_DIONS_EYE,SIN_SKILL_USE_NOT,0},

#ifdef ENGLISH_LANGUAGE
{"Falcon",		"Summons a fierce falcon to     attack nearby enemies.",
#else
{"���֮ӥ",		"�����֮ӥӵ�и�ǿ�󹥻����Ĺ�����ӥ.",
#endif
23,		36,2,		115,4,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Falcon ,SKILL_FALCON,SIN_SKILL_USE_RIGHT,Falcon_UseMana },

#ifdef ENGLISH_LANGUAGE
{"Arrow of Rage",		"Shoots an arrow over a desired area which explodes and rains  down fire on enemies.",
#else
{"�񱩻��",		"��ָ����Ŀ�귢�����.",
#endif
26,		38,2,		82,4,
{0,0,0},			{sinWS1,0,0,0,0,0,0,0,0,0},
F_Arrow_of_Rage,SKILL_ARROW_OF_RAGE,SIN_SKILL_USE_RIGHT,A_Rage_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Avalanche",		"Unleashes a barrage of piercing arrows on a single target.",
#else
{"ѩ��֮��",		"��ָ����Ŀ�귢����ѩ����Ĺ���.",
#endif
30,		41,2,		103,2,
{0,0,0},			{sinWS1,0,0,0,0,0,0,0,0,0},
F_Avalanche,SKILL_AVALANCHE,SIN_SKILL_USE_RIGHT,Avalanche_UseMana},

// 3ת
#ifdef ENGLISH_LANGUAGE
{"Elemental Shot",		"Continuous elememtal attack to opponents.",
#else
{"Ԫ�ع���",		"ʹ�������Ի�����ԵĹ������η��乥������.",
#endif
40,		43,2,		82,2,
{0,0,0},			{sinWS1,0,0,0,0,0,0,0,0,0},
F_E_Shot,SKILL_ELEMENTAL_SHOT,SIN_SKILL_USE_RIGHT,Elemental_Shot_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Golden Falcon",		"Summons a falcon to attack opponents.",
#else
{"�ƽ���ӥ",		"�ٻ�һֻ������ǿ���Ҷ�ʹ���߱����������ظ�����ӥ.",
#endif
43,		52,2,		120,4,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_G_Falcon,SKILL_GOLDEN_FALCON,SIN_SKILL_USE_RIGHT,Golden_Falcon_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Bum shot",		"Fires explosive arrows twice. Splash damages opponents.",
#else
{"����֮��",		"�������η��䱬ը�ԵĹ������������Ѿ���Χ�ڵĵ���.",
#endif
46,		46,2,		87,3,
{0,0,0},			{sinWS1,0,0,0,0,0,0,0,0,0},
F_B_Shot,SKILL_BOMB_SHOT,SIN_SKILL_USE_RIGHT,BombShot_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Perforation",		"Accurate and continuous attack that perforates opponents.",
#else
{"�ߴ�֮��",		"׼ȷ��ǿ���ķ���ߴ��ԵĹ�������һ����Χ�ڵĵ���.",
#endif
50,		48,2,		82,2,
{0,0,0},			{sinWS1,0,0,0,0,0,0,0,0,0},
F_Perforation,SKILL_PERFORATION,SIN_SKILL_USE_RIGHT,Perforation_UseMana},

// 4ת
#ifdef ENGLISH_LANGUAGE
{"Recall Wolverine",		"Summons Wolverine.",
#else
{"�ٻ�ѩ��",		"�ٻ�ѩ����Э���Լ�����.",
#endif
60,		58,2,		900,0,
{1,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Recall_Wolverin,SKILL_RECALL_WOLVERIN,SIN_SKILL_USE_RIGHT,Recall_Wolverin_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Evasion Mastery",		"It avoids an enemy attack effectively.",
#else
{"��ܴ�ʦ",		"������߶�������.",
#endif
63,		0,0,		0,0,
{1,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Evasion_Mastery,SKILL_EVASION_MASTERY,SIN_SKILL_USE_NOT,0},

#ifdef ENGLISH_LANGUAGE
{"Phoenix Shot",		"It gives wide ATK with Energy of Phoenix.",
#else
{"系˾���",		"�ѹ�����Ϊ���˵Ĺߴ�����.",
#endif
66,		55,2,		100,0,
{1,0,0},			{sinWS1,0,0,0,0,0,0,0,0,0},
F_Phoenix_Shot,SKILL_PHOENIX_SHOT,SIN_SKILL_USE_RIGHT,Phoenix_Shot_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Force of Nature",		"It improves your ability by natural assimilation perfectly.",
#else
{"��Ȼ֮��",		"�������ֱ���Ĺ�����������.",
#endif
70,		56,2,		900,0,
{1,0,0},			{sinWS1,0,0,0,0,0,0,0,0,0},
F_Force_Of_Nature,SKILL_FORCE_OF_NATURE,SIN_SKILL_USE_RIGHT,Force_Of_Nature_UseMana},

// 5ת

#ifdef ENGLISH_LANGUAGE
{"Evade Shot",		"Jump away to shoot arrow to enemy below",
#else
{"����֮��",		"��Ծ�����зų�ǿ��һ��.",
#endif
80,		52,2,		80,2,
{2,0,0},			{sinWS1,0,0,0,0,0,0,0,0,0},
F_S_Shot,SKILL_E_SHOT,SIN_SKILL_USE_RIGHT,E_Shot_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Thunder Roop",		"Using lightning for a powerful attack",
#else
{"����֮��",		"�������ֱ���Ĺ�����������.",
#endif
83,		52,2,		80,2,
{2,0,0},			{sinWS1,0,0,0,0,0,0,0,0,0},
F_S_Rope,SKILL_S_ROPE,SIN_SKILL_USE_RIGHT,S_Rope_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Nature Splash",		"Shoots an arrow with energy from the nature",
#else
{"쫷�֮��",		"�������ֱ���Ĺ�����������.",
#endif
86,		57,2,		80,2,
{2,0,0},			{sinWS1,0,0,0,0,0,0,0,0,0},
F_N_Splash,SKILL_N_SPLASH,SIN_SKILL_USE_RIGHT,N_Splash_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Circle Trap",		"Capture the enemy weakness and slows down the enemy's speed",
#else
{"�������",		"�������ֱ���Ĺ�����������.",
#endif
90,		95,2,		90,2,
{2,0,0},			{sinWS1,0,0,0,0,0,0,0,0,0},
F_C_Trap,SKILL_C_TRAP,SIN_SKILL_USE_RIGHT,C_Trap_UseMana},

//����
#ifdef ENGLISH_LANGUAGE
{"Sword Blast",			"Throws a devastating sword to attack enemies",
#else
{"ħ��",			"�ͷ������Ľ�������������.",
#endif
10,		22,2,		82,2,
{0,0,0},			{sinWS2,0,0,0,0,0,0,0,0,0},
F_Sword_Blast,SKILL_SWORD_BLAST,SIN_SKILL_USE_ALL,Sword_Blast_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Holy Body",		"Become holy for a period of time to increase absorb rating against undead enemies",
#else
{"ʥ�⻤��",		"ʹ�����Ϊʥ�������ӶԲ���ϵ���﹥��������.",
#endif
12,		28,2,		110,3,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_HolyBody ,SKILL_HOLY_BODY,SIN_SKILL_USE_RIGHT,HolyBody_UseMana },

#ifdef ENGLISH_LANGUAGE
{"Physical Training",		"Physical Training increases stamina permanently",
#else
{"������ѵ",		"ͨ��������ѵ���õ���������ֵ.",
#endif
14,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Physical_Traning,SKILL_PHYSICAL_TRANING,SIN_SKILL_USE_NOT,0},

#ifdef ENGLISH_LANGUAGE
{"Double Crash",		"Strikes twice with a consecutive attack",
#else
{"˫�ر���",		"���������ͷų��ػ�.",
#endif
17,		35,2,		82,2,
{0,0,0},			{sinWA1,sinWC1,sinWS2,0,0,0,0,0,0,0},
F_Double_Crash,SKILL_DOUBLE_CRASH,SIN_SKILL_USE_RIGHT,D_Crash_UseMana},

// 2ת
#ifdef ENGLISH_LANGUAGE
{"Holy Valor",		"Increases attack power of the party against the Undead",
#else
{"�����ػ�",		"����Ӣ�µ�������ǿ�Բ���ϵ���﹥��.",
#endif
20,		36,2,		100,3,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Holy_Valor,SKILL_HOLY_VALOR,SIN_SKILL_USE_RIGHT,Holy_Valor_Mana},

#ifdef ENGLISH_LANGUAGE
{"Brandish",		"Damaging all enemies within the splash range",
#else
{"�������",		"��Ч����뾶�ڵ����е���.",
#endif
23,		38,2,		82,2,
{0,0,0},			{sinWP1,sinWS2,0,0,0,0,0,0,0,0},
F_Brandish,SKILL_BRANDISH,SIN_SKILL_USE_ALL,Brandish_Mana},

#ifdef ENGLISH_LANGUAGE
{"Piercing",			"Pierces a sword through the targeted enemy with a powerful attack",
#else
{"һ����",			"����ǿ��Ĺ������ߴ�������Χ�ڵĵ���.",
#endif
26,		41,2,		82,2,
{0,0,0},			{sinWS2,0,0,0,0,0,0,0,0,0},
F_Piercing,SKILL_PIERCING,SIN_SKILL_USE_ALL,Piercing_Mana},

#ifdef ENGLISH_LANGUAGE
{"Drastic Spirit",		"Increases Defense Rating",
#else
{"��������",		"һ��ʱ�����������ķ�����.",
#endif
30,		44,2,		100,2,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Drastic_Spirit,SKILL_DRASTIC_SPIRIT,SIN_SKILL_USE_RIGHT,Drastic_Spirit_Mana},

// 3ת
#ifdef ENGLISH_LANGUAGE
{"Sword Mastery",		"Increases attack power on swords permanently",
#else
{"����֮��",		"�������ӽ��Ĺ�����.",
#endif
40,		0,0,		0,0,
{0,0,0},			{sinWS2,0,0,0,0,0,0,0,0,0},
F_S_Mastery,SKILL_SWORD_MASTERY,SIN_SKILL_USE_NOT,0},

#ifdef ENGLISH_LANGUAGE
{"Divine Shield",		"Increases block and converts blocked undead damage into HP",
#else
{"ʥ��֮��",		"������ʥ�Ķ��ưѲ���ϵ�Ĺ���ת��Ϊ�����������չ�����.",
#endif
43,		46,2,		130,1,
{0,0,0},			{sinDS1,0,0,0,0,0,0,0,0,0},
F_D_Inhalation,SKILL_DIVINE_INHALATION,SIN_SKILL_USE_RIGHT,D_Inhalation_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Holy Incantation",		"Transforms the targeted monster into a pet that will fight for you in battle",
#else
{"ʥ��֮��",		"������ʥ�Ĺ�â�Ѳ���ϵ�Ĺ����ٻ�Ϊ�Լ��ĳ���.",
#endif
46,		50,2,		120,1,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Holy_Incantation,SKILL_HOLY_INCANTATION,SIN_SKILL_USE_RIGHT,H_Incantation_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Grand cross",		"Attacks the enemy with a deadly cross",
#else
{"ʥ��ʮ��",		"�������κ��й�������һ��ʮ���ش����˶Բ���ϵ��������Ч.",
#endif
50,		45,2,		82,2,
{0,0,0},			{sinWH1,sinWS2,0,0,0,0,0,0,0,0},
F_Grand_Cross,SKILL_GRAND_CROSS,SIN_SKILL_USE_RIGHT,Grand_Cross_UseMana},

// 4ת

#ifdef ENGLISH_LANGUAGE
{"Sword of Justice",		"Strikes the enemy with several powerful hits",
#else
{"��ħ��",		"�ͷų�ǿ�����Ľ�����������Χ�ڵĵ���.",
#endif
60,		53,2,		250,0,
{1,0,0},			{sinWS2,0,0,0,0,0,0,0,0,0},
F_Sword_Of_Justice,SKILL_SWORD_OF_JUSTICE,SIN_SKILL_USE_RIGHT,Sword_Of_Justice_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Godly Shield",		"Forms a Holy Shield blessed by God",
#else
{"����֮��",		"һ���ܵ��ϵ�ף��������һ�����չ������Ķ�.",
#endif
63,		50,2,		400,0,
{1,0,0},			{sinDS1,0,0,0,0,0,0,0,0,0},
F_Godly_Shield,SKILL_GODLY_SHIELD,SIN_SKILL_USE_RIGHT,Godly_Shield_UseMana},

#ifdef ENGLISH_LANGUAGE
{"God Bless",		"Increases your attack power by the name of God",
#else
{"�ϵ�ף��",		"���ϵ۵����帳�轣ʥǿ�������.",
#endif
66,		51,2,		330,0,
{1,0,0},			{sinWA1,sinWC1,sinWH1,sinWP1,sinWS2,sinWS1,sinWT1,0,0,0},
F_God_Bless,SKILL_GOD_BLESS,SIN_SKILL_USE_RIGHT,God_Bless_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Divine Piercing",		"Attacks the enemy with the help of God's power to unleash a devastating strike",
#else
{"ɲ�����",		"�����ϵ�֮������һ�ν�������������.",
#endif
70,		51,2,		160,0,
{1,0,0},			{sinWS2,0,0,0,0,0,0,0,0,0},
F_Divine_Piercing,SKILL_DIVINE_PIERCING,SIN_SKILL_USE_RIGHT,Divine_Piercing_UseMana},

//5ת

#ifdef ENGLISH_LANGUAGE
{"Soul Breaker",		"Powerful attack into the enemy's soul",
#else
{"�������",		"����ǿ�����������Է�.",
#endif
80,		69,2,		150,0,
{2,0,0},			{sinWS2,0,0,0,0,0,0,0,0,0},
F_S_Breaker,SKILL_S_BREAKER,SIN_SKILL_USE_RIGHT,S_Breaker_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Crescent Moon",		"Attacks the enemy with a close instant attack",
#else
{"�����ػ�",		"˲�乥��Զ���ĵ���.",
#endif
83,		70,2,		110,0,
{2,0,0},			{sinWS2,0,0,0,0,0,0,0,0,0},
F_C_Moon,SKILL_C_MOON,SIN_SKILL_USE_RIGHT,C_Moon_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Saint Blade",		"Summoning divine power to your sword to attack the enemy",
#else
{"�ϵ��ػ�",		"���ϵ۵�������Ծ�����й����Է�.",
#endif
86,		75,2,		82,2,
{2,0,0},			{sinWS2,sinWH1,0,0,0,0,0,0,0,0},
F_S_Blade,SKILL_S_BLADE,SIN_SKILL_USE_RIGHT,S_Blade_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Holy Benedic",		"Change the attribute of the monster to undead",
#else
{"��������",		"һ�����������ĵ���ʱ,��ʱ�䵽�˵�ʱ���������.",
#endif
90,		93,2,		400,0,
{2,0,0},			{sinWA1,sinWC1,sinWH1,sinWP1,sinWS2,sinWS1,sinWT1,0,0,0},
F_H_Benedic,SKILL_H_BENEDIC,SIN_SKILL_USE_RIGHT,H_Benedic_UseMana},

// ħǹ��

#ifdef ENGLISH_LANGUAGE
{"Shield Strike",		"hurls a shield to attack enemies.",
#else
{"����ɯ��",		"Ͷ�����Ƹ�����˹ߴ��Թ���.",
#endif
10,		23,2,		82,2,
{0,0,0},			{sinDS1,0,0,0,0,0,0,0,0,0},
F_S_Strike ,SKILL_SHIELD_STRIKE,SIN_SKILL_USE_RIGHT,S_Strike_UseMana },

#ifdef ENGLISH_LANGUAGE
{"Farina",		"Throws a spear that creates illusions",
#else
{"��ɳ��Ӱ",		"����Ͷ����ǹ������������.",
#endif
12,		26,2,		82,2,
{0,0,0},			{sinWT1,0,0,0,0,0,0,0,0,0},
F_Farina,SKILL_FARINA,SIN_SKILL_USE_ALL,Farina_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Throwing Mastery",		"Trains Javelin attacks to increase damage permenantly using Javelins",
#else
{"ħ����ǹ",		"����������ǹ�Ĺ�����.",
#endif
14,		0,0,		0,0,
{0,0,0},			{sinWT1,0,0,0,0,0,0,0,0,0},
F_D_Mastery,SKILL_THROWING_MASTERY,SIN_SKILL_USE_NOT,0},

#ifdef ENGLISH_LANGUAGE
{"Bigger Spear",		"Attacks the targeted enemy with a holy Javelin",
#else
{"����֮ǹ",		"���ħ����Ͷǹ����.",
#endif
17,		32,2,		82,2,
{0,0,0},			{sinWP1,sinWT1,0,0,0,0,0,0,0,0},
F_V_Spear,SKILL_VIGOR_SPEAR,SIN_SKILL_USE_ALL,V_Spear_UseMana},

// 2ת

#ifdef ENGLISH_LANGUAGE
{"Windy",		"Increases range and attack rating of Javelins",
#else
{"׷������",		"����ǹͶ���ĸ�Զ�����������.",
#endif
20,		34,2,		100,2,
{0,0,0},			{sinWT1,0,0,0,0,0,0,0,0,0},
F_Windy,SKILL_WINDY,SIN_SKILL_USE_RIGHT,Windy_Mana},

#ifdef ENGLISH_LANGUAGE
{"Twist Javelin",		"Increase attack rating and attack power with using a twisting tactic",
#else
{"�����ɱ�",		"ͨ����ת�ɱ�����߹�������������.",
#endif
23,		36,2,		82,2,
{0,0,0},			{sinWT1,0,0,0,0,0,0,0,0,0},
F_Twist_Javelin,SKILL_TWIST_JAVELIN,SIN_SKILL_USE_RIGHT,Twist_Javelin_Mana},

#ifdef ENGLISH_LANGUAGE
{"Soul Sucker",		"Absorbs the HP of enemies within attack range that have more than 50 percent HP",
#else
{"�������",		"��һ���ĳɹ��������չ��������ֵ.",
#endif
26,		42,2,		110,2,
{0,0,0},			{sinDS1,0,0,0,0,0,0,0,0,0},
F_Soul_Sucker,SKILL_SOUL_SUCKER,SIN_SKILL_USE_RIGHT,Soul_Sucker_Mana},

#ifdef ENGLISH_LANGUAGE
{"Fire Javelin",		"Attacks the enemy with power of fire",
#else
{"������ǹ",		"���û����Եı�ǹ��������.",
#endif
30,		40,2,		82,2,
{0,0,0},			{sinWT1,0,0,0,0,0,0,0,0,0},
F_Fire_Javelin,SKILL_FIRE_JAVELIN,SIN_SKILL_USE_ALL,Fire_Javelin_Mana},

// 3ת

#ifdef ENGLISH_LANGUAGE
{"Split Javelin",		"Attacks the enemy with several powerful strikes at very fast speed",
#else
{"׷��֮ǹ",		"���������ٶ�����ɢ���Թ���.",
#endif
40,		43,2,		115,1,
{0,0,0},			{sinWT1,0,0,0,0,0,0,0,0,0},
F_Split_Javelin,SKILL_SPLIT_JAVELIN,SIN_SKILL_USE_RIGHT,Split_Javelin_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Triumph of Valhalla",		"Increases attack power of all party members",
#else
{"ս������",		"����ǿ�����ĺ�����ǿ���ѵ����Ʋ���߹�����.",
#endif
43,		50,2,		120,1,
{0,0,0},			{sinWT1,sinWS2,sinWS1,sinWP1,sinWH1,sinWA1,sinWC1,sinWM1,0,0},
F_T_Of_Valhalla,SKILL_TRIUMPH_OF_VALHALLA,SIN_SKILL_USE_RIGHT,T_Of_Valhalla_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Lightning Javelin",		"Increases the lightning attribute of the Javelin",
#else
{"����֮ǹ",		"���������Եı�ǹ����������.",
#endif
46,		46,2,		82,2,
{0,0,0},			{sinWT1,0,0,0,0,0,0,0},
F_Lightning_Javelin,SKILL_LIGHTNING_JAVELIN,SIN_SKILL_USE_ALL,Lightning_Javelin_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Storm Javelin",	    "Attacks the enemy with a strong tornado tactic",
#else
{"������",	    "�Ա���������ת��ǹ����Ͷ����ǹ.",
#endif
50,		48,2,		82,2,
{0,0,0},			{sinWT1,0,0,0,0,0,0,0,0,0},
F_Storm_Javelin,SKILL_STORM_JAVELIN,SIN_SKILL_USE_RIGHT,Storm_Javelin_UseMana},

// 4ת

#ifdef ENGLISH_LANGUAGE
{"Hall of Valhalla",	"Creates a space to unleash the Power of Valhalla",
#else
{"�߶�����֮��",	"�����߶�����֮�����������һ���ռ�.",
#endif
60,		52,2,		750,0,
{1,0,0},			{sinWA1,sinWC1,sinWH1,sinWP1,sinWS1,sinWT1,0,0,0,0},
F_Hall_Of_Valhalla,SKILL_HALL_OF_VALHALLA,SIN_SKILL_USE_RIGHT,Hall_Of_Valhalla_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Extreme Rage",		"Attacks the enemy with Power of Anger",
#else
{"ʮ��ŭ��",		"���÷�ŭ����Ծ������Χ�ڵĵ���.",
#endif
63,		48,2,		210,0,
{1,0,0},			{sinWT1,0,0,0,0,0,0,0,0,0},
F_X_Rage,SKILL_X_RAGE,SIN_SKILL_USE_RIGHT,X_Rage_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Frost Javelin",		"Increases ice attribute for a period of time",
#else
{"˪����ǹ",		"�Ǳ�ǹ��һ��ʱ����ά�ֱ����Բ����б����Թ���.",
#endif
66,		50,2,		720,0,
{1,0,0},			{sinWT1,0,0,0,0,0,0,0,0,0},
F_Frost_Javelin,SKILL_FROST_JAVELIN,SIN_SKILL_USE_RIGHT,Frost_Javelin_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Vengeance",		"Attacks the enemy with several fast and powerful attacks",
#else
{"��籬��",		"���ٵ�������Ͷ����ǹ.",
#endif
70,		45,2,		100,0,
{1,0,0},			{sinWT1,0,0,0,0,0,0,0,0,0},
F_Vengeance,SKILL_VENGEANCE,SIN_SKILL_USE_RIGHT,Vengeance_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Talaria",		"Increases your running speed",
#else
{"�������",		"�����Լ��Ͷ��ѵ��ƶ��ٶ�.",
#endif
80,		68,2,		720,0,
{2,0,0},			{sinWT1,0,0,0,0,0,0,0,0,0},
F_Talaria,SKILL_TALARIA,SIN_SKILL_USE_RIGHT,Talaria_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Galaxy Coup",		"Summoning javelins in the air and throw them on the floor causing damage to enemies within range",
#else
{"�����ǹ",		"�ٻ������ǹЭ���Լ�����.",
#endif
83,		52,2,		120,0,
{2,0,0},			{sinWT1,0,0,0,0,0,0,0,0,0},
F_G_Coup,SKILL_G_COUP,SIN_SKILL_USE_RIGHT,G_Coup_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Recall Arcuda",			"Summons Arcuda to support you in the battle",
#else
{"������",			"�ٻ���������Э���Լ�����.",
#endif
86,		95,2,		720,0,
{2,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_S_Arcuda,SKILL_S_ARCUDA,SIN_SKILL_USE_RIGHT,S_Arcuda_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Snippy Fear",		"Throws 2 javelins on the enemy with massive critical damage",
#else
{"����ͻϮ",		"���ٵ�������Ͷ����ǹ����߱�ɱ.",
#endif
90,		57,2,		100,0,
{2,0,0},			{sinWT1,0,0,0,0,0,0,0,0,0},
F_S_Fear,SKILL_S_FEAR,SIN_SKILL_USE_RIGHT,S_Fear_UseMana},

// ��˾

#ifdef ENGLISH_LANGUAGE
{"Healing",		"heals life with its holy magic.",
#else
{"����֮��",		"ͨ����ʥ��ħ���ظ�����������Լ���������������������Բ���ϵ����������Ч��.",
#endif
10,		15,1,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Healing,SKILL_HEALING,SIN_SKILL_USE_RIGHT,Healing_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Holy Bolt",		"hurls a holy bolt to enemies.",
#else
{"ʥ�����",		"ͨ��ħ�����䲨��״����������������(�Բ�����ϵ��������Ч).",
#endif
12,		11,1,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_HolyBolt,SKILL_HOLY_BOLT,SIN_SKILL_USE_ALL,HolyBolt_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Multi Spark",		"Releases magical sparks to attack enemies.",
#else
{"��â����",		"ͨ��ħ��������״��������������.",
#endif
14,		14,1,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_M_Spark,SKILL_MULTISPARK,SIN_SKILL_USE_RIGHT,M_Spark_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Holy Mind",		"It weakens enemy's attack in a given time.",
#else
{"����֮��",		"ͨ��ħ���������͹���Ĺ�������������Ч.",
#endif
17,		19,1,		100,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_HolyMind,SKILL_HOLY_MIND,SIN_SKILL_USE_RIGHT,HolyMind_UseMana},

// 2ת

#ifdef ENGLISH_LANGUAGE
{"Meditation",		"Increase mana recovery permanently.",
#else
{"���ҫ��",		"��������ħ���Ļظ�����.",
#endif
20,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Meditation,SKILL_MEDITATION,SIN_SKILL_USE_NOT,0},

#ifdef ENGLISH_LANGUAGE
{"Divine Lightning",		"Attack enemies with holy lightning.",
#else
{"��֮�׵�",		"������ʥ���׵���������������.",
#endif
23,		21,1,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Divine_Lightning,SKILL_DIVINE_LIGHTNING,SIN_SKILL_USE_RIGHT,Divine_Lightning_Mana},

#ifdef ENGLISH_LANGUAGE
{"Holy Reflection",		"Reflect attacks from undead by creating holy magical shield.",
#else
{"��ʥ����",		"ͨ����ʥ��ħ���������䲻��ϵ����Ĺ���.",
#endif
26,		23,1,		120,1,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Holy_Reflection,SKILL_HOLY_REFLECTION,SIN_SKILL_USE_RIGHT,Holy_Reflection_Mana},

#ifdef ENGLISH_LANGUAGE
{"Grand Healing",		"Heal life of a party member.",
#else
{"ʥ��֮��",		"�ظ���Ч�뾶�ڶ����ж��ѵ�����.",
#endif
30,		27,1,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Grand_Healing,SKILL_GRAND_HEALING,SIN_SKILL_USE_RIGHT,Grand_Healing_Mana},

// 3ת

#ifdef ENGLISH_LANGUAGE
{"Vigor ball",		"Fires vigor ball twice to opponents.",
#else
{"��Ӱ˫��",		"�������η�����ħ�������ħ����.",
#endif
40,		24,1,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Vigor_Ball,SKILL_VIGOR_BALL,SIN_SKILL_USE_ALL,Vigor_Ball_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Resurrection",		"Revives a dead party member.",
#else
{"����֮��",		"����ʹ�����еĶ�����ԭ�ظ���.",
#endif
43,		31,1,		130,1,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Resurrection,SKILL_RESURRECTION,SIN_SKILL_USE_RIGHT,Resurrection_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Extinction",		"lethal incantation to undead monsters. Permanent damage to undead units.",
#else
{"ʥ��֮��",		"����ʥ��������һ�������ò���ϵ�Ĺ����ܵ���������.",
#endif
46,		28,1,		120,1,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Extinction,SKILL_EXTINCTION,SIN_SKILL_USE_RIGHT,Extinction_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Virtual life",		"Increases party members' life for a while.",
#else
{"��ʥ֮��",		"һ��ʱ������������ֵ����.",
#endif
50,		31,1,		134,1,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Virtual_Life,SKILL_VIRTUAL_LIFE,SIN_SKILL_USE_RIGHT,Virtual_Life_UseMana},

// 4ת

#ifdef ENGLISH_LANGUAGE
{"Glacial Spike",		"Huge ice block released to attack enemies.",
#else
{"��˪����",		"�ͷž޴�ı������������.",
#endif
60,		35,1,		120,0,
{1,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Glacial_Spike,SKILL_GLACIAL_SPIKE,SIN_SKILL_USE_RIGHT,Glacial_Spike_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Regeneration Field",		"After your sacrifice, it recoveries your company continuously.",
#else
{"��������",		"�����ڷ�Χ��ͬ��Ļظ�����.",
#endif
63,		41,1,		950,0,
{1,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Regeneration_Field,SKILL_REGENERATION_FIELD,SIN_SKILL_USE_RIGHT,Regeneration_Field_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Chain Lightning",		"It attacks powerful thunder ATK to Monsters.",
#else
{"����֮ŭ",		"�ٻ�����������ʥ��ǿ������������������Χ�ڵĵ���.",
#endif
66,		41,1,		120,0,
{1,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Chain_Lightning,SKILL_CHAIN_LIGHTNING,SIN_SKILL_USE_RIGHT,Chain_Lightning_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Summon Muspell",		"It absorbs undead monster's ATK, resurrects HP and has summoner's ability.",
#else
{"��ʥ��ʹ",		"�ٻ�����ʹ��Э���Լ�����.",
#endif
70,		47,1,		800,0,
{1,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Summon_Muspell,SKILL_SUMMON_MUSPELL,SIN_SKILL_USE_RIGHT,Summon_Muspell_UseMana},

// 5ת

#ifdef ENGLISH_LANGUAGE
{"Spirit Impact",		"Power shockwave attack on your enemy..",
#else
{"��ʥ�粨",		"ͨ��ħ������ǿ���ĳ����.",
#endif
80,		45,2,		120,0,
{2,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_S_Impact,SKILL_S_IMPACT,SIN_SKILL_USE_RIGHT,S_Impact_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Piercing Ice",		"Summons magical powers to attack with sharp ice spears..",
#else
{"��ʥ����",		"ͨ��ħ���ٻ����д���Է�.",
#endif
83,		50,2,		110,0,
{2,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_P_Ice,SKILL_P_ICE,SIN_SKILL_USE_RIGHT,P_Ice_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Ice Meteorite",		"Calls in an ice cold meteorite storm which will damage and freeze opponents near the strike area of each meteorite.",
#else
{"�󱩷�ѩ",		"�ٻ���֮��ʯ����Է�����������Ч��.",
#endif
86,		88,3,		120,0,
{2,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_S_Ramiel,SKILL_S_PRMIEL,SIN_SKILL_USE_RIGHT,S_Ramiel_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Blessing Krishna",		"Increases your defense and absorb by grace of god.",
#else
{"��Ůɢ��",		"������������ܺ�����.",
#endif
90,		60,2,		950,0,
{2,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_B_Krishna,SKILL_B_KRISHNA,SIN_SKILL_USE_RIGHT,B_Krishna_UseMana},


// ħ��ʦ

#ifdef ENGLISH_LANGUAGE
{"Agony",		"Sacrifice oneself to increase spirit.",
#else
{"ħ��ת��",		"���Լ���������ת�����Լ���ħ������.",
#endif
10,		12,1,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Agony,SKILL_AGONY,SIN_SKILL_USE_RIGHT,Agony_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Fire Bolt",		"Calls down small fireballs to attack enemies",
#else
{"���֮��",		"�ͷų�Ѥ���Ļ������������.",
#endif
12,		11,1,		84,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_FireBolt,SKILL_FIRE_BOLT,SIN_SKILL_USE_ALL,FireBolt_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Zenith",		"Increase element features with strong spirit for a given time.",
#else
{"����֮��",		"����ħ��������һ��ʱ������������ֵ.",
#endif
14,		15,1,		100,3,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Zenith,SKILL_ZENITH,SIN_SKILL_USE_RIGHT,Zenith_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Fire Ball",		"Calls down huge fireballs to attack enemies.",
#else
{"����֮��",		"ʹ�þ޴�Ļ��������е���.",
#endif
17,		19,1,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_FireBall,SKILL_FIRE_BALL,SIN_SKILL_USE_RIGHT,FireBall_UseMana},

// 2ת

#ifdef ENGLISH_LANGUAGE
{"Mental Mastery",		"Increases maximum mana.",
#else
{"��������",		"����ħ��ֵ���������.",
#endif
20,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Mental_Mastery,SKILL_MENTAL_MASTERY,SIN_SKILL_USE_NOT,0},

#ifdef ENGLISH_LANGUAGE
{"Watornado",		"A pilar of water strikes enemies.",
#else
{"������",		"�ͷų����������ˮ���Ե��˽��й���.",
#endif
23,		21,1,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Watornado,SKILL_WATORNADO,SIN_SKILL_USE_RIGHT,Watornado_Mana},

#ifdef ENGLISH_LANGUAGE
{"Enchant Weapon",		"Enhance the attacking element in weapon of party member.",
#else
{"Ԫ��֮��",		"�������еĶ�Ա�����׻���������Ը��ӹ�����.",
#endif
26,		28,1,		104,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Enchant_Weapon,SKILL_ENCHANT_WEAPON,SIN_SKILL_USE_RIGHT,Enchant_Weapon_Mana},

#ifdef ENGLISH_LANGUAGE
{"Death Ray",		"Fire Powerful ray from palms.",
#else
{"ڤ��֮��",		"�������ͷų��������������.",
#endif
30,		26,1,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Dead_Ray,SKILL_DEAD_RAY,SIN_SKILL_USE_ALL,Dead_Ray_Mana},

// 3ת

#ifdef ENGLISH_LANGUAGE
{"Energy shield",		"Forms a magical shield around the body.",
#else
{"ħ���ػ�",		"��������Χ�γ�һ�������ħ������.",
#endif
40,		40,1,		150,1,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Energy_Shield,SKILL_ENERGY_SHIELD,SIN_SKILL_USE_RIGHT,Energy_Shield_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Diastrophism",		"Strong geographical attack to opponents within range.",
#else
{"���ѳ��",		"�ڵ��淢��ǿ�ҵ��𶯶Է�Χ�ڵ����е��˸����˺�.",
#endif
43,		33,1,		106,1,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Diastrophism,SKILL_DIASTROPHISM,SIN_SKILL_USE_RIGHT,Diastrophism_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Spirit elemental",		"Summons a ghost to increase magical damage.",
#else
{"����ٻ�",		"�ٻ�С��������ǿħ��������.",
#endif
46,		35,1,		150,1,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Spirit_Elemental,SKILL_SPIRIT_ELEMENTAL,SIN_SKILL_USE_RIGHT,Spirit_Elemental_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Dancing sword",		"A phantom of sword appears and uses the power of element to attack enemies.",
#else
{"Ԫ��֮��",		"����ħ������һ�������Ի�����ԵĽ�������.",
#endif
50,		30,1,		150,1,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_D_Sword,SKILL_DANCING_SWORD,SIN_SKILL_USE_RIGHT,Dancing_Sword_UseMana},

// 4ת

#ifdef ENGLISH_LANGUAGE
{"Fire Elemental",		"The skill summons a strong elemental made with fire.",
#else
{"��������",		"�ٻ�������Э���Լ�����.",
#endif
60,		120,2,		900,0,
{1,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Fire_Elemental,SKILL_FIRE_ELEMENTAL,SIN_SKILL_USE_RIGHT,Fire_Elemental_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Flame Wave",		"It attacks the front monsters with powerful fire flame.",
#else
{"���沨��",		"����ǿ�����Ļ�������Եĵ���.",
#endif
63,		32,1,		124,0,
{1,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Flame_Wave,SKILL_FLAME_WAVE,SIN_SKILL_USE_RIGHT,Flame_Wave_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Distortion",		"It takes down a monster's ability with Distortion of Space.",
#else
{"�ռ�Ť��",		"ʹ�ռ�Ť�������͵��˵�����.",
#endif
66,		43,1,		460,0,
{1,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Distortion,SKILL_DISTORTION,SIN_SKILL_USE_RIGHT,Distortion_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Meteorite",		"It attacks nearby monsters with summoned meteorites.",
#else
{"��ʯ�ٻ�",		"�ٻ���ʯ��������Χ�ڵĵ���.",
#endif
70,		39,1,		190,0,
{1,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Meteo,SKILL_M_METEO,SIN_SKILL_USE_RIGHT,Meteo_UseMana},

// 5ת

#ifdef ENGLISH_LANGUAGE
{"Silraphim",		"Summoning the power of Silraphim to attack the enemy.",
#else
{"���ǻ���",		"����������ǿ��Է�.",
#endif
80,		45,2,		120,0,
{2,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Silraphim,SKILL_SILRAPHIM,SIN_SKILL_USE_RIGHT,Silraphim_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Vis Tenus",		"Shrinks the enmy and reduces their movement.",
#else
{"����֮��",		"���ͶԷ����ƶ��ٶ�.",
#endif
83,		50,2,		460,0,
{2,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_V_Tenus,SKILL_V_TENUS,SIN_SKILL_USE_RIGHT,V_Tenus_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Prima Ignis",		"Summons a power explosion for a powerful attack",
#else
{"��ʥϴ��",		"��ڤ��Ļ������Է�ǿ�����.",
#endif
89,		54,2,		120,0,
{2,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_P_Ignis,SKILL_P_IGNIS,SIN_SKILL_USE_RIGHT,P_Ignis_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Third Anima",		"Decreases your max strength to raise attack power",
#else
{"��ʥ����",		"����ħ��ֵ������ħ��������.",
#endif
90,		60,2,		150,1,
{2,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_T_Anima,SKILL_T_ANIMA,SIN_SKILL_USE_RIGHT,T_Anima_UseMana},

// �̿�

#ifdef ENGLISH_LANGUAGE
{"Stinger",			"Runs straight towards the enemy and hits the enemy with two quick attacks",
#else
{"�̻�",			"���ݵ��Զ������������й���.",
#endif
10,		22,2,		80,2,
{0,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Stringer,SKILL_STRINGER,SIN_SKILL_USE_ALL,Stinger_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Double Blow",			"Deals continuous damage to the enemy while spinning.",
#else
{"����",			"�����ƶ���������ǰ��������Ե���������.",
#endif
12,		27,2,		80,2,
{0,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Running,SKILL_RUNNING_HIT,SIN_SKILL_USE_RIGHT,Running_Hit_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Dual Wield Mastery",		"Increases your Attack Power permanently when using daggers",
#else
{"ǿ������",		"ʹ�þ���֮���������ӹ�����.",
#endif
14,		0,0,		0,0,
{0,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Sword_Mastery,SKILL_SWORDMASTERY,SIN_SKILL_USE_NOT,0},

#ifdef ENGLISH_LANGUAGE
{"Wisp",		"Reduces enemies Attack Power for a period of time",
#else
{"���㹥��",		"ռ���ٽ����˵�����,һ��ʱ���ڼ��ٹ�����.",
#endif
17,		34,2,		110,1,
{0,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Wisp,SKILL_WISP,SIN_SKILL_USE_RIGHT,Wisp_UseMana},

// 2ת

#ifdef ENGLISH_LANGUAGE
{"Venom Thorn",		"Attacks the enemy twice rapidly with poisoned daggers",
#else
{"��������",		"��Ĩ�Ŷ������������˿��ٶ�����.",
#endif
20,		18,2,		110,1,
{0,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Verom_Thorn,SKILL_VENOM_THORN,SIN_SKILL_USE_RIGHT,Verom_Thorn_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Alas",		"Distributes dexterity of an Assassin and increases Evasion of all party members",
#else
{"����֮��",		"�����Ա�̿͵�����,�������ر���.",
#endif
23,		38,2,		110,1,
{0,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Ales,SKILL_ALAS,SIN_SKILL_USE_RIGHT,Ales_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Soul Shock",		"Performs a hard hit to the ground and stun all enemies around",
#else
{"�����",		"ʹһ����Χ�ڵĵ��������������.",
#endif
26,		39,2,		110,1,
{0,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Soul_Shock,SKILL_SOUL_SHOCK,SIN_SKILL_USE_RIGHT,Soul_Shock_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Blade Mastery",		"Increases your Attack Power and Evasion permanently when using daggers",
#else
{"������ʦ",		"�����ͻر�����������.",
#endif
30,		0,0,		0,0,
{0,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Blade_Mastery,SKILL_ATTACK_MASTERY,SIN_SKILL_USE_NOT,0},

// 3ת

#ifdef ENGLISH_LANGUAGE
{"Finishing Blow",		"Deals repeated damage to the enemy. Finishing Blow effect will apply on the first hit",
#else
{"�ɽ�֮��",		"�����˴�ȥ���������������.",
#endif
40,		50,2,		80,2,
{0,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Finishing_Blow,SKILL_SORE_SWORD,SIN_SKILL_USE_ALL,Finishing_Blow_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Gust Slash",			"Jumps towards the enemy and attacks repeatedly to deal massive damage to the enemy and anyone nearby",
#else
{"��ն",			"������������������������.",
#endif
43,		53,2,		110,1,
{0,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Gust_Shash,SKILL_BEAT_UP,SIN_SKILL_USE_RIGHT,Gust_Shash_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Inpes",		"Increases your Attack Speed temporarily",
#else
{"���ݴ�ʦ",		"�Ը߶ȵļ������ۼ�����߹����ٶ�.",
#endif
46,		48,2,		120,2,
{0,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Inpes,SKILL_INPES,SIN_SKILL_USE_RIGHT,Inpes_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Deception",			"Hides into your own shadow which turn you invisible to enemies eyes for a short duration until you attack",
#else
{"��ä",			"�����Լ���Ӱ��,�������ǿ��������.",
#endif
50,		53,2,		120,2,
{0,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Deception,SKILL_BLIND,SIN_SKILL_USE_RIGHT,Deception_UseMana},

// 4ת

#ifdef ENGLISH_LANGUAGE
{"Frost Wind",		"Moves quickly to deal repeated fatal damage to the enemy",
#else
{"����֮��",		"���ݵ��ƶ�������������������õ����������.",
#endif
60,		61,2,		120,0,
{1,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Frost_Wind,SKILL_FROST_WIND,SIN_SKILL_USE_RIGHT,Frost_Wind_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Fatal Mastery",		"Increases your Critical chance when permanently when using daggers",
#else
{"��������",		"����֮�����õı�ɱ������.",
#endif
63,		0,0,		0,0,
{1,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Fatal_Mastery,SKILL_FATAL_MASTERY,SIN_SKILL_USE_NOT,0},

#ifdef ENGLISH_LANGUAGE
{"Pollute",		"Poisons all nearby enemies and decreases their health for a duration",
#else
{"����֮��",		"����Χ�ĵ��˴�ȥ�����Թ���.",
#endif
66,		55,2,		120,0,
{1,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Pollute,SKILL_POLLUTED,SIN_SKILL_USE_RIGHT,Pollute_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Ninja Shadow",		"Moves fast to deal continuous damage to the enemy with shadows",
#else
{"Ӱ������",		"�����ƶ�,���Լ���Ӱ���������Թ���.",
#endif
70,		51,2,		120,0,
{1,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Shadow,SKILL_PASTING_SHADOW,SIN_SKILL_USE_RIGHT,Shadow_UseMana},

// 5ת

#ifdef ENGLISH_LANGUAGE
{"Shadow Bomb",		"Hides in the shadow and deals damage in an area by throwing a fire bomb on the ground",
#else
{"Ӱ�ӻ���",		"ʹ�û������Χ�ĵ�������˺�.",
#endif
80,		65,2,		80,2,
{2,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Shadow_Bomb,SKILL_SHADOW_BOMB,SIN_SKILL_USE_RIGHT,Shadow_Bomb_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Rising Slash",			"Jumps on the spot and uses gravitational energy to perform a big slash to the enemy",
#else
{"����ն",			"ʹ�������ý��Ե����������.",
#endif
83,		71,2,		110,1,
{2,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Rising_Shash,SKILL_RISING_SHASH,SIN_SKILL_USE_RIGHT,Rising_Shash_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Violent Stub",		"A distracting kick quickly followed by a powerful blade stab",
#else
{"������β",		"ʹ�ý���������������ɾ޴��˺�.",
#endif
86,		90,2,		110,1,
{2,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Violent_Stub,SKILL_VIOLENCE_STAB,SIN_SKILL_USE_RIGHT,Violent_Stub_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Shadow Storm",		"Summons a storm to deal massive damage",
#else
{"�籩֮��",		"�ɵ����жԵ��˼����������˺�.",
#endif
90,		100,2,		120,1,
{2,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Shadow_Storm,SKILL_STORM,SIN_SKILL_USE_RIGHT,Shadow_Storm_UseMana},

// ����

#ifdef ENGLISH_LANGUAGE
{"Dark Bolt",		"Hits the enemy with an almighty bolt of dark magic created with sorcery",
#else
{"��������",		"�����������ɵ�С���Ź�������.",
#endif
10,		8,1,		80,2,
{0,0,0},			{sinWN1,0,0,0,0,0,0,0,0,0},
F_Dark_Bolt,SKILL_DARK_BOLT,SIN_SKILL_USE_ALL,Dark_Bolt_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Dark Wave",		"Performs a consecutive attack with almighty bolts of dark magic",
#else
{"���ڲ���",		"��Է�Ͷ�������ħ������й���.",
#endif
12,		19,1,		80,2,
{0,0,0},			{sinWN1,0,0,0,0,0,0,0,0,0},
F_Dark_Wave,SKILL_DARK_WAVE,SIN_SKILL_USE_ALL,Dark_Wave_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Inertia",		"Throws a curse onto the enemy to slow down the enemy",
#else
{"�����׻�",		"ʹ������������öԷ���������.",
#endif
14,		20,1,		110,2,
{0,0,0},			{sinWN1,0,0,0,0,0,0,0,0,0},
F_Inertia,SKILL_CURSE_LAZY,SIN_SKILL_USE_RIGHT,Inertia_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Inner Peace",		"Through mental training your maximum Mana capacity is increased permanently",
#else
{"����ƽ��",		"�̳�ǿ��ľ���Ԫ����������ħ��.",
#endif
17,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Inner_Peace,SKILL_INNER_PEACE,SIN_SKILL_USE_NOT,0},

// 2ת

#ifdef ENGLISH_LANGUAGE
{"Spiritual Flare",		"Uses powerful sorcery to deal damage to all enemies nearby in the area",
#else
{"��������",		"��ǿ�������������Է�.",
#endif
20,		21,1,		80,2,
{0,0,0},			{sinWN1,0,0,0,0,0,0,0,0,0},
F_Spiritual_Flare,SKILL_SPIRITUAL_FLARE,SIN_SKILL_USE_RIGHT,Spiritual_Flare_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Spiritual Manacle",		"Binds the target's soul with sorcery that results in a stun of the target",
#else
{"������",		"�����������������Է�������.",
#endif
23,		21,1,		110,2,
{0,0,0},			{sinWN1,0,0,0,0,0,0,0,0,0},
F_Spiritual_Manacle,SKILL_SPIRITUAL_MANACLE,SIN_SKILL_USE_RIGHT,Spiritual_Manacle_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Chasing Hunt",			"Increases your sight and gatherers nearby enemies close by pulling them towards you",
#else
{"��ȡ",			"���޶���Χ�ڵĶ�����������.",
#endif
26,		27,1,		110,2,
{0,0,0},			{sinWN1,0,0,0,0,0,0,0,0,0},
F_Chasing_Hunt,SKILL_CHASING_HUNT,SIN_SKILL_USE_RIGHT,Chasing_Hunt_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Advent Migal",			"Calls forth Migal to temporarily increase the Attack Power of you and your party members",
#else
{"���˶�",			"�ٻ����˶�֮����������Ͷ�ż�Ĺ�����.",
#endif
30,		28,1,		300,2,
{0,0,0},			{sinWN1,0,0,0,0,0,0,0,0,0},
F_Advent_Migal,SKILL_ADVENT_MIGAL,SIN_SKILL_USE_RIGHT,Advent_Migal_UseMana},

// 3ת

#ifdef ENGLISH_LANGUAGE
{"Rainmaker",			"Invokes the God of rain to temporarily increase your Absorption and Attack Rating",
#else
{"����ʦ",			"����ħ��������������.",
#endif
40,		31,1,		300,2,
{0,0,0},			{sinWN1,0,0,0,0,0,0,0,0,0},
F_Rainmaker,SKILL_RAIN_MAKER,SIN_SKILL_USE_RIGHT,Rainmaker_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Phantom Call",		"Calls a Cursed Phantom to deal massive damage to enemies nearby",
#else
{"½�����",		"ʹ���յ�����ķ������Χ�ĵ�������˺�.",
#endif
43,		33,1,		80,2,
{0,0,0},			{sinWN1,0,0,0,0,0,0,0,0,0},
F_Phantom_Call,SKILL_LAND_OF_GHOST,SIN_SKILL_USE_RIGHT,Phantom_Call_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Haunt",		"With help of the Phantom's strength a forceful blow damages the enemy and absorbs damage into health",
#else
{"����ػ�",		"�������������ʹ�Է��յ�������ȡ������.",
#endif
46,		35,1,		110,2,
{0,0,0},			{sinWN1,0,0,0,0,0,0,0,0,0},
F_Haunt,SKILL_HAUNT,SIN_SKILL_USE_RIGHT,Haunt_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Scratch",			"Deals damage through a fiercely scratch by a summoned Phantom Nail",
#else
{"ץ��",			"�÷���֮��ʹ�Է��յ�����������.",
#endif
50,		32,1,		110,2,
{0,0,0},			{sinWN1,0,0,0,0,0,0,0,0,0},
F_Scratch,SKILL_SCRATCH,SIN_SKILL_USE_RIGHT,Scratch_UseMana},

// 4ת

#ifdef ENGLISH_LANGUAGE
{"Crimson Knight",		"Through black magic and use of sorcery the Crimson Knight is summoned",
#else
{"��Ѫ֮ҹ",		"ʹ�������ٻ���Ѫ֮ҹ.",
#endif
60,		41,1,		320,0,
{1,0,0},			{sinWN1,0,0,0,0,0,0,0,0,0},
F_Crimson_Knight,SKILL_RECALL_BLOODYKNIGHT,SIN_SKILL_USE_RIGHT,Crimson_Knight_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Judgement",			"Deals a large potion of damage by shooting a powerful energy beam of darkness at the enemy",
#else
{"����",			"��ɢ����֮�⹥���Է�.",
#endif
63,		41,1,		120,0,
{1,0,0},			{sinWN1,0,0,0,0,0,0,0,0,0},
F_Judgement,SKILL_JUDGEMENT,SIN_SKILL_USE_RIGHT,Judgement_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Advent Midranda",		"Invokes Midranda to temporarily increase the Attack Speed of you and your party members",
#else
{"�׵�����",		"����������Ա�Ĺ����ٶ�.",
#endif
66,		39,1,		320,0,
{1,0,0},			{sinWN1,0,0,0,0,0,0,0,0,0},
F_Advent_Midranda,SKILL_ADVENT_MIDRANDA,SIN_SKILL_USE_RIGHT,Advent_Midranda_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Mourning Pray",		"By using the sacred powers of Miranda and Migal you damage all nearby enemies",
#else
{"���ն���",		"�ܵ����˶����׵�����ĹⲨ������Ч��������Χ����.",
#endif
70,		47,1,		100,0,
{1,0,0},			{sinWN1,0,0,0,0,0,0,0,0,0},
F_Mourning_pray,SKILL_MOURNING_OF_PRAY,SIN_SKILL_USE_RIGHT,Mourning_Pray_UseMana},

// 5ת

#ifdef ENGLISH_LANGUAGE
{"Creed",		"By the use of powerful sorcery you grant extra Mana and Stamina",
#else
{"��������",		"��ǿ��������ʹ����,ħ��,��������.",
#endif
80,		43,2,		320,0,
{2,0,0},			{sinWN1,0,0,0,0,0,0,0,0,0},
F_Creed,SKILL_CREED,SIN_SKILL_USE_RIGHT,Creed_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Press of Deity",		"Unleashes a hidden power that throws cursed damage to nearby enemies",
#else
{"����֮��",		"�ܵ�������ٻ���ʯ����Χ�ĵ�������˺�.",
#endif
83,		47,2,		100,0,
{2,0,0},			{sinWN1,0,0,0,0,0,0,0,0,0},
F_Press,SKILL_PRESS_OF_DEITY,SIN_SKILL_USE_RIGHT,Press_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Phantom Nail",		"Calls upon the spirit of the earth to attack nearby enemies",
#else
{"����֮צ",		"�ٻ���˯�Ĵ��֮צ����������.",
#endif
89,		54,2,		100,0,
{2,0,0},			{sinWN1,0,0,0,0,0,0,0,0,0},
F_Phantom_Nail,SKILL_CHOSTY_NAIL,SIN_SKILL_USE_RIGHT,Phantom_Nail_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Occult Life",		"Permanently increases your maximum health with the power of sorcery",
#else
{"�߼�����",		"��ǿ����������������ֵ.",
#endif
90,		0,0,		0,0,
{2,0,0},			{sinWN1,0,0,0,0,0,0,0,0,0},
F_Occult_Life,SKILL_HIGH_REGENERATION,SIN_SKILL_USE_NOT,0},

#ifdef ENGLISH_LANGUAGE
{"Force Orb",			"Force Orb's give you the ability to upgrade your Attack Power",
#else
{"֮��",			"ʹ�ú����ӹ�����",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,SKILL_FORCE_ORB,0,0},

#ifdef ENGLISH_LANGUAGE
{"Crystal",			"Summoned Pet that supports you in Battle",
#else
{"ˮ��",			"�ٻ�ˮ����Э���Լ�����",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,SKILL_CRYSTAL_ORB,0,0},

#ifdef ENGLISH_LANGUAGE
{"Trade Chat Timer",	"Time till you can announce another Trade message",
#else
{"ʱ���ʱ��",		"��ʱ�䵽�˲ſ����н���һ���¼�",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,SKILL_WARNING_TIME,0,0},

#ifdef ENGLISH_LANGUAGE
{"Quest",			"Hunt monsters!",
#else
{"����",			"��ɱ����!",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,CHANGE_JOB3_QUEST,0,0},

#ifdef ENGLISH_LANGUAGE
{"Quest",			"Hunt monsters!",
#else
{"����",			"��ɱ����!",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,CHANGE_ELEMENTARY_QUEST,0,0},

#ifdef ENGLISH_LANGUAGE
{"Absorption of Glory",		"+10 Absorb",
#else
{"ף��ʥ��",		"��һ����������������+20.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,CLANSKILL_ABSORB,0,0},

#ifdef ENGLISH_LANGUAGE
{"Power Siege",		"+10% Attack Power",
#else
{"ף��ʥ��",		"��һ������������15%�Ĺ�����.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,CLANSKILL_ATTACK,0,0},

#ifdef ENGLISH_LANGUAGE
{"Evasion Adaption",		"+10% Evasion",
#else
{"ף��ʥ��",		"��һ���������������� 20%.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,CLANSKILL_EVASION,0,0},

#ifdef ENGLISH_LANGUAGE
{"Atanasia",		"Makes you invincible for a while, but decrease your Attack Power by half",
#else
{"���������",		"��˲�����޵й���������Ϊԭ����1/2.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,SCROLL_INVULNERABILITY,0,0},

#ifdef ENGLISH_LANGUAGE
{"Deadly Edge",		"Increase Critical by 5%",
#else
{"��ɱ����",		"������ɱ������5%.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,SCROLL_CRITICAL,0,0},

#ifdef ENGLISH_LANGUAGE
{"Avail of Evasion",		"Increase Evasion by 5%",
#else
{"��������",		"��������������5%.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,SCROLL_EVASION,0,0},

#ifdef ENGLISH_LANGUAGE
{"Defiance Stone",		"Increases absorption rate of Fire Crystal attacks",
#else
{"ˮ������",		"���ջ�ˮ���������� 50%���˺�.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,STONE_R_FIRECRYTAL,0,0},

#ifdef ENGLISH_LANGUAGE
{"Defiance Stone",		"Increases absorption rate of Ice Crystal attacks",
#else
{"ˮ������",		"���ձ�ˮ����������50%���˺�.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,STONE_R_ICECRYTAL,0,0},

#ifdef ENGLISH_LANGUAGE
{"Defiance Stone",		"Increases absorption rate of Lightning Crystal attacks",
#else
{"ˮ������",		"������ˮ����������50%���˺�.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,STONE_R_LINGHTINGCRYTAL,0,0},

#ifdef ENGLISH_LANGUAGE
{"Animosity Potion",	"+5% Damage Boost against Fighter",
#else
{"��������",		"����ʿ����5%�Ĺ����˺�.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,STONE_A_FIGHTER,0,0},

#ifdef ENGLISH_LANGUAGE
{"Animosity Potion",	"+5% Damage Boost against Mechanician",
#else
{"��������",		"�Ի�е������5%�Ĺ����˺�.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,STONE_A_MECHANICIAN,0,0},

#ifdef ENGLISH_LANGUAGE
{"Animosity Potion",	"+5% Damage Boost against Pikeman",
#else
{"��������",		"��ǹ������5%�Ĺ����˺�.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,STONE_A_PIKEMAN,0,0},

#ifdef ENGLISH_LANGUAGE
{"Animosity Potion",	"+5% Damage Boost against Archer",
#else
{"��������",		"�Թ���������5%�Ĺ����˺�.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,STONE_A_ARCHER,0,0},

#ifdef ENGLISH_LANGUAGE
{"Animosity Potion",	"+5% Damage Boost against Knight",
#else
{"��������",		"����������5%�Ĺ����˺�.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,STONE_A_KNIGHT,0,0},

#ifdef ENGLISH_LANGUAGE
{"Animosity Potion",	"+5% Damage Boost against Atalanta",
#else
{"��������",		"��ħǹ������5%�Ĺ����˺�.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,STONE_A_ATALANTA,0,0},

#ifdef ENGLISH_LANGUAGE
{"Animosity Potion",	"+5% Damage Boost against Magician",
#else
{"��������",		"��ħ��ʦ����5%�Ĺ����˺�.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,STONE_A_MAGICIAN,0,0},

#ifdef ENGLISH_LANGUAGE
{"Animosity Potion",	"+5% Damage Boost against Priestess",
#else
{"��������",		"�Լ�˾����5%�Ĺ����˺�.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,STONE_A_PRIESTESS,0,0},

#ifdef ENGLISH_LANGUAGE
{"Animosity Potion",	"+5% Damage Boost against Assassin",
#else
{"��������",		"�Դ̿�����5%�Ĺ����˺�.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,STONE_A_ASSASSIN,0,0},

#ifdef ENGLISH_LANGUAGE
{"Animosity Potion",	"+5% Damage Boost against Shaman",
#else
{"��������",		"����������5%�Ĺ����˺�.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,STONE_A_SAMAN,0,0},

#ifdef ENGLISH_LANGUAGE
{"Eternal Life",	"Makes your invincible for a while, decreases your attack power by half",
#else
{"��������",		"˲���Ϊ�޵�״̬ ����������Ϊԭ����1/2.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,SCROLL_P_INVULNERABILITY,0,0},

#ifdef ENGLISH_LANGUAGE
{"Fatal Edge",		"Increases your Critical Attack rating by 5%.",
#else
{"��ŭ����",		"������ɱ������15%.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,SCROLL_P_CRITICAL,0,0},

#ifdef ENGLISH_LANGUAGE
{"Avert Scroll",		"Increases your Evade Chance by 15%.",
#else
{"���ܾ���",		"��������������15%.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,SCROLL_P_EVASION,0,0},

#ifdef ENGLISH_LANGUAGE
{"Booster life",	"+15% bonus Health",
#else
{"��������",		"��� 15%��������",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,BOOSTER_ITEM_LIFE,0,0},

#ifdef ENGLISH_LANGUAGE
{"Mana Booster",	"+15% bonus Mana",
#else
{"ħ������",		"��� 15%ħ������",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,BOOSTER_ITEM_MANA,0,0},

#ifdef ENGLISH_LANGUAGE
{"Stamina Booster",	"+15% bonus Stamina",
#else
{"��������",		"��� 15%��������",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,BOOSTER_ITEM_STAMINA,0,0},