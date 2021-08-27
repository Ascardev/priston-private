#define SIN_SKILL_USE_RIGHT		0x01000000		//只有右手可用
#define SIN_SKILL_USE_LEFT		0x02000000		//只有左手可用
#define SIN_SKILL_USE_ALL		0x03000000		//双手均可使用
#define SIN_SKILL_USE_NOT		0x04000000		//无法使用


//机械兵
#ifdef ENGLISH_LANGUAGE
{"Extreme Shield",	"Temporarily increases block    rating of the current shield",
#else
{"极光护盾",		"在自己使用的盾上面附以极光提高盾的格档率.",
#endif
10,		34,2,		110,4,
{0,0,0},			{sinDS1,0,0,0,0,0,0,0,0,0},
F_Extreme_Shield,SKILL_EXTREME_SHIELD,SIN_SKILL_USE_RIGHT,E_Shield_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Mechanic Bomb",	"Throws a bomb to enemies within explosive blast radius",
#else
{"机械榴弹",		"扔出机械手榴弹在一定距离内打击敌人.",
#endif
12,		28,2,		73,3,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Mechanic_Bomb,SKILL_MECHANIC_BOMB,SIN_SKILL_USE_RIGHT,Mechanic_Bomb_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Poison Attribute",		"Permanently raises resistance  to poison",
#else
{"毒之防御",		"增强对毒属性攻击的防御能力.",
#endif
14,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Poison_Attribute,SKILL_POISON_ATTRIBUTE,SIN_SKILL_USE_NOT,0},

#ifdef ENGLISH_LANGUAGE
{"Physical Absorption",		"Temporarily increases the      body's ability to absorb damage",
#else
{"灵光护体",		"滠取自然灵气暂时强化自己身体吸收更多的敌人攻击力.",
#endif
17,		30,2,		110,5,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Physical_Absorption,SKILL_PHYSICAL_ABSORB,SIN_SKILL_USE_RIGHT,P_Absor_bUseMana},

// 2转
#ifdef ENGLISH_LANGUAGE
{"Great Smash",		"Channels strength into one     powerful blow.",
#else
{"破碎巨击",		"将自己的力量注入武器造成对敌人更大的伤害.",
#endif
20,		38,2,		73,3,
{0,0,0},			{sinWA1,sinWC1,sinWH1,sinWP1,sinWS2,0,0,0,0,0},
F_Great_Smash,SKILL_GREAT_SMASH,SIN_SKILL_USE_ALL,G_Smash_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Maximize",		"Optimizes weapons to raise     their attack power permanently.",
#else
{"改良专家",		"对持有的武器进行优化提高攻击力.",
#endif
23,		41,2,		110,4,
{0,0,0},			{sinWA1,sinWC1,sinWH1,sinWP1,sinWS2,sinWS1,sinWT1,0,0,0},
F_Maximize,SKILL_MAXIMIZE,SIN_SKILL_USE_RIGHT,Maximize_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Automation",		"使武器自动化一定时间内提高远程攻击武器的攻击力和攻击速度.",
#else
{"灵光飞扬",		"使武器自动化一定时间内提高远程攻击武器的攻击力和攻击速度.",
#endif
26,		42,2,		110,4,
{0,0,0},			{sinWS1,sinWT1,0,0,0,0,0,0,0,0},
F_Automation,SKILL_AUTOMATION,SIN_SKILL_USE_RIGHT,Automation_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Spark",		"Attacks nearby enemies with    powerful lightning bolts.",
#else
{"火花电场",		"用强力的电光攻击自身附近的敌人.",
#endif
30,		40,2,		82,2,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Spark,SKILL_SPARK,SIN_SKILL_USE_RIGHT,Spark_UseMana},

// 3转
#ifdef ENGLISH_LANGUAGE
{"Metal Armor",		"Raises the defense of the mechanician's armor in a limited time.",
#else
{"金属重甲",		"一定时间内提高机械铠甲的吸收力.",
#endif
40,		48,2,		110,5,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Metal_Armor,SKILL_METAL_ARMOR,SIN_SKILL_USE_RIGHT,Metal_Armor_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Grand Smash",		"Accurate and continous attack to opponents. Raises attack rating.",
#else
{"星光灭绝",		"精湛的连击提高攻击力.",
#endif
43,		44,2,		82,2,
{0,0,0},			{sinWA1,sinWC1,sinWP1,sinWS2,sinWH1,0,0,0,0,0},
F_Grand_Smash,SKILL_GRAND_SMASH,SIN_SKILL_USE_RIGHT,Grand_Smash_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Mechanic Weapon Mastery",		"Optimizes the mechanic spec. items.",
#else
{"优化专家",		"将机械特效化的武器发挥到最佳状态.",
#endif
46,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_M_W_Mastery,SKILL_MECHANIC_WEAPON,SIN_SKILL_USE_NOT,0},

#ifdef ENGLISH_LANGUAGE
{"Spark Shield",		"Forms invisible electric guard.",
#else
{"防御电波",		"利用强力的电波形成一个保护力场防御敌人攻击.",
#endif
50,		52,2,		110,2,
{0,0,0},			{sinDS1,0,0,0,0,0,0,0,0,0},
F_Spark_Shield,SKILL_SPARK_SHIELD,SIN_SKILL_USE_RIGHT,Spark_Shield_UseMana},

// 4转
#ifdef ENGLISH_LANGUAGE
{"Impulsion",		"It attacks closed monsters by an electricity of powerful blow.",
#else
{"雷霆冲击",		"利用强力的电击打击敌人.",
#endif
60,     	55,2,		130,0,
{1,0,0},            {sinWC1,sinWH1,sinWP1,sinWS2,0,0,0,0,0,0},
F_Impulsion,SKILL_IMPULSION,SIN_SKILL_USE_RIGHT,Impulsion_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Completion",		"It gathers closed monsters by a powerful shout.",
#else
{"威慑怒吼",		"通过强有力的吼叫来聚集怪物并提高自身的防御力.",
#endif
63,     	65,2,		440,0,
{1,0,0},            {0,0,0,0,0,0,0,0,0,0},
F_Compulsion,SKILL_COMPULSION,SIN_SKILL_USE_RIGHT,Compulsion_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Magnetic Sphere",		"It creates powerful magnetism Sphere to selected user..",
#else
{"磁性球体",		"向选定的使用者释放一个磁性球体..",
#endif
66,     	71,2,		600,0,
{1,0,0},            {0,0,0,0,0,0,0,0,0,0},
F_Magnetic_Sphere,SKILL_MAGNETIC_SPHERE,SIN_SKILL_USE_RIGHT,Magnetic_Sphere_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Metal Golem",		"Summons a huge metallic golem to aid you in battle attacking nearby enemies",
#else
{"终极机械",		"通过召唤一个机械金属来提高攻击力和防御力.",
#endif
70,     	71,2,		1000,0,
{1,0,0},            {0,0,0,0,0,0,0,0},
F_Metal_Golem,SKILL_METAL_GOLEM,SIN_SKILL_USE_RIGHT,Metal_Golem_UseMana},

// 5转

#ifdef ENGLISH_LANGUAGE
{"Land Mining",		"Quickly throws land mines that blow up enemies within the area..",
#else
{"霹雳旋风",		"使用手雷重创周围的对手.",
#endif
80,     	65,2,		80,2,
{2,0,0},            {sinWA1,sinWC1,sinWH1,sinWP1,sinWS2,0,0,0,0,0},
F_landminning,SKILL_LANDMINNING,SIN_SKILL_USE_RIGHT,Landminning_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Hyper Sonic",		"Increase attack speed for a certain time",
#else
{"快速打击",		"在一定时间提升自身的攻击速度.",
#endif
83,     	90,2,		110,5,
{2,0,0},            {sinWA1,sinWC1,sinWH1,sinWP1,sinWS1,sinWS2,sinWT1,0,0,0},
F_H_Sonic,SKILL_H_SONIC,SIN_SKILL_USE_RIGHT,H_Sonic_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Rolling Smash",		"Attacks a single enemy with 4 destructive attacks",
#else
{"究极之刃",		"对对手进行浮空并进行强力打击.",
#endif
86,     	71,2,		110,1,
{2,0,0},            {sinWA1,sinWC1,sinWH1,sinWP1,sinWS2,0,0,0,0,0},
F_R_Smash,SKILL_R_SMASH,SIN_SKILL_USE_RIGHT,R_Smash_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Power Enhancement",		"Increase your minimum and maximum attack power",
#else
{"战神祝福",		"在一定时间提升自身和队友的攻击力和防御.",
#endif
90,     	95,2,		110,5,
{2,0,0},            {sinWA1,sinWC1,sinWH1,sinWP1,sinWS1,sinWS2,sinWT1,0,0,0},
F_P_Enhence,SKILL_P_ENHENCE,SIN_SKILL_USE_RIGHT,P_Enhence_UseMana},

//武士
#ifdef ENGLISH_LANGUAGE
{"Melee Mastery",		"Increases efficiency in melee  weapons, increasing Attack     Power permanently.",
#else
{"格斗之术",		"永久提升武士的近身格斗能力提高攻击力.",
#endif
10,		0,0,		0,0,
{0,0,0},			{sinWA1,sinWC1,sinWH1,sinWS2,0,0,0,0,0,0},
F_Melee_Mastery,SKILL_MELEE_MASTERY,SIN_SKILL_USE_NOT,0},

#ifdef ENGLISH_LANGUAGE
{"Fire Attribute",		"Permanently raises resistance  to fire.",
#else
{"火之防御",		"增强对火属性攻击力的防御能力.",
#endif
12,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
F_Fire_Attribute,SKILL_FIRE_ATTRIBUTE,SIN_SKILL_USE_NOT,0},

#ifdef ENGLISH_LANGUAGE
{"Raving",		"Goes berserk for a short period of time, but loses HP with each attack.",
#else
{"绝地暴走",		"增加攻击力和攻击次数但使用后损失一定量的生命.",
#endif
14,		35,2,		93,3,
{0,0,0},			{sinWA1,sinWC1,sinWH1,sinWP1,sinWS2,0,0,0,0,0},
F_Raving,SKILL_RAVING,SIN_SKILL_USE_ALL,Raving_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Impact",		"Raises attack rating to        accurately strike the enemy.",
#else
{"精准之击",		"准确的连击两次提高攻击和命中力有效的打击敌人.",
#endif
17,		37,2,		86,4,
{0,0,0},			{sinWA1,sinWC1,sinWP1,sinWS2,0,0,0,0,0,0},
F_Impact,SKILL_IMPACT,SIN_SKILL_USE_ALL,Impact_UseMana},

// 2转

#ifdef ENGLISH_LANGUAGE
{"Triple Impact",		"A more powerful version of     Impact.",
#else
{"威力冲击",		"提高连击次数和提升攻击力有效的打击敌人.",
#endif
20,		39,2,		80,4,
{0,0,0},			{sinWA1,sinWC1,sinWP1,sinWS2,0,0,0,0,0,0},
F_Triple_Impact,SKILL_TRIPLE_IMPACT,SIN_SKILL_USE_ALL,T_Impact_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Brutal Swing",		"Delivers a powerful and fatal  blow to the enemy.",
#else
{"致命回旋",		"利用强有力的回旋给予敌人致命一击.",
#endif
23,		41,2,		82,2,
{0,0,0},			{sinWA1,sinWS2,0,0,0,0,0,0,0,0},
F_Brutal_Swing,SKILL_BRUTAL_SWING,SIN_SKILL_USE_ALL,B_Swing_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Roar",		"Shouting out a deafening roar to   momentarily stun and confuse   enemies.",
#else
{"极地怒吼",		"一声震耳欲聋的声音让自身附近的敌人暂时处于昏迷状态.",
#endif
26,		39,2,		112,4,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Roar,SKILL_ROAR,SIN_SKILL_USE_RIGHT,Roar_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Rage of Zechram",		"Borrows the skills of the legendary hero Zechram",
#else
{"战神之怒",		"借助英雄战神阿瑞斯的力量攻击面对的敌人(附带火属性攻击)",
#endif
30,		45,2,		84,4,
{0,0,0},			{sinWA1,sinWH1,sinWS2,0,0,0,0,0,0,0},
F_RageOfZecram,SKILL_RAGE_OF_ZECRAM,SIN_SKILL_USE_RIGHT,R_Zecram_UseMana},

// 3转

#ifdef ENGLISH_LANGUAGE
{"Concentration",		"Increases attack rating for a while.",
#else
{"会心一击",		"发挥高度的集中力在一定时间内提高命中率.",
#endif
40,		53,2,		110,3,
{0,0,0},			{sinWA1,sinWS2,0,0,0,0,0,0,0,0},
F_Concentration,SKILL_CONCENTRATION,SIN_SKILL_USE_RIGHT,Concentration_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Avenging Crash",		"Powerful crashing attacks to opponents.",
#else
{"复仇连击",		"利用复仇的力量两次连击敌人并继承回旋的攻击.",
#endif
43,		48,2,		73,3,
{0,0,0},			{sinWA1,sinWP1,sinWS2,0,0,0,0,0,0,0},
F_Avanging_Crash,SKILL_AVANGING_CRASH,SIN_SKILL_USE_RIGHT,A_Crash_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Swift Axe",		"Raises attack speed of axe in a limited time.",
#else
{"刺杀之斧",		"熟练掌握使用斧的技能在一定时间内提高使用斧的攻击速度.",
#endif
46,		53,2,		200,3,
{0,0,0},			{sinWA1,0,0,0,0,0,0,0,0,0},
F_Swift_Axe,SKILL_SWIFT_AXE,SIN_SKILL_USE_RIGHT,Swift_Axe_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Bone crash",		"Used to defeat demons by ancestors. Powerful attack that hits opponent twice.",
#else
{"挫骨扬灰",		"古代勇士用来对付恶魔的技能连续两次给予敌人致命一击.",
#endif
50,		54,2,		73,3,
{0,0,0},			{sinWA1,sinWP1,sinWS2,0,0,0,0,0,0,0},
F_Bone_Crash,SKILL_BONE_CRASH,SIN_SKILL_USE_RIGHT,B_Crash_UseMana},

// 4转
#ifdef ENGLISH_LANGUAGE
{"Destroyer",		"Strongest Double-hit to a monster.",
#else
{"破坏之击",		"利用连续的攻击给予敌人强烈的攻击.",
#endif
60,		45,2,		150,0,
{1,0,0},			{sinWA1,sinWH1,0,0,0,0,0,0,0,0},
F_Destoryer,SKILL_DETORYER,SIN_SKILL_USE_ALL,Destoryer_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Berserker",		"Change like uncontrol condition, but it decrease the absorb dramatically.",
#else
{"疯狂怒吼",		"使武士进入狂暴状态大幅度提高自身的攻击力但会降低吸收力.",
#endif
63,		60,2,		700,0,
{1,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Berserker,SKILL_BERSERKER,SIN_SKILL_USE_RIGHT,Berserker_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Cyclone Strike",		"It attacks Monsters by strong spin ATK.",
#else
{"飓风袭击",		"利用强力的回转打击自身附近的敌人.",
#endif
66,		55,2,		135,0,
{1,0,0},			{sinWA1,sinWH1,sinWP1,sinWS2,0,0,0,0,0,0},
F_Cyclone_Strike,SKILL_CYCLONE_STRIKE,SIN_SKILL_USE_RIGHT,Cyclone_Strike_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Boost Health",		"It increases HP permanently.",
#else
{"健康专家",		"永久增加生命值上限.",
#endif
70,		0,0,		0,0,
{1,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Boost_Health,SKILL_BOOST_HEALTH,SIN_SKILL_USE_NOT,},

// 5转
#ifdef ENGLISH_LANGUAGE
{"Down Hit",		"Throws the enemy in the air and slams down on the ground.",
#else
{"狂暴怒斩",		"对敌人进行浮空三次打击.",
#endif
80,		68,2,		135,0,
{2,0,0},			{sinWA1,sinWH1,sinWP1,sinWS2,0,0,0,0,0,0},
F_D_Hit,SKILL_D_HIT,SIN_SKILL_USE_RIGHT,D_Hit_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Power Dash",		"Run towards the enemy with massive power to attack it.",
#else
{"狂野冲击",		"斩杀较远的敌人给予致命一击.",
#endif
83,		81,2,		100,0,
{2,0,0},			{sinWA1,sinWH1,sinWS2,0,0,0,0,0,0,0},
F_P_Dash,SKILL_P_DASH,SIN_SKILL_USE_RIGHT,P_Dash_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Mortal Blow",		"Delivers a powerful twisted slash attack.",
#else
{"回旋斩击",		"回旋斩杀范围内的敌人.",
#endif
86,		70,2,		135,0,
{2,0,0},			{sinWA1,sinWH1,sinWS2,0,0,0,0,0,0,0},
F_M_Blow,SKILL_M_BLOW,SIN_SKILL_USE_RIGHT,M_Blow_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Bloody Berserker",		"Decreases Absorption for super increased Attack Power.",
#else
{"众神之怒",		"一定时间内增加必杀率.",
#endif
90,		93,2,		150,0,
{2,0,0},			{sinWA1,0,0,0,0,0,0,0,0,0},
F_B_Berserker,SKILL_B_BERSERKER,SIN_SKILL_USE_RIGHT,B_Berserker_UseMana},

//枪兵

#ifdef ENGLISH_LANGUAGE
{"Pike Wind",		"Creates a whirlwind to push    back and damage enemies",
#else
{"龙卷枪风",		"同时打击自身附近多个敌人并击退敌人一段距离.",
#endif
10,		27,2,		80,4,
{0,0,0},			{sinWP1,0,0,0,0,0,0,0,0,0},
F_Pike_Wind,SKILL_PIKE_WIND,SIN_SKILL_USE_RIGHT,Pike_Wind_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Ice Attribute",		"Permanently raises resistance  to frost.",
#else
{"冰之防御",		"增强冰属性攻击的防御能力.",
#endif
12,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Ice_Attribute,SKILL_ICE_ATTRIBUTE,SIN_SKILL_USE_NOT,0},

#ifdef ENGLISH_LANGUAGE
{"Critical Hit",		"Aims for enemies' weak spots   to raise probability of a      critical strike.",
#else
{"致命打击",		"打击敌人的要害提高必杀攻击的命中率.",
#endif
14,		31,2,		84,3,
{0,0,0},			{sinWP1,sinWC1,sinWH1,sinWS2,0,0,0,0,0,0},
F_Critical_Hit,SKILL_CRITICAL_HIT,SIN_SKILL_USE_ALL,Critical_Hit_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Jumping Crash",		"Leaps up into the air to strikedown with a powerful blow.",
#else
{"霹雳一击",		"高高的跃起猛烈的打击敌人.",
#endif
17,		34,2,		76,4,
{0,0,0},			{sinWA1,sinWP1,sinWS2,0,0,0,0,0,0,0},
F_Jumping_Crash,SKILL_JUMPING_CRASH,SIN_SKILL_USE_ALL,Jumping_Crash_UseMana},

// 2转
#ifdef ENGLISH_LANGUAGE
{"Ground Pike",		"Imbues weapon with frost       properties to deliver a        powerful attack.",
#else
{"大地之枪",		"结合冰和大地之气的力量攻击范围内的敌人并降低敌人的移动速度.",
#endif
20,		36,2,		84,4,
{0,0,0},			{sinWP1,0,0,0,0,0,0,0,0,0},
F_Ground_Pike,SKILL_GROUND_PIKE,SIN_SKILL_USE_RIGHT,G_Pike_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Tornado",		"Summons a tornado to attack    nearby enemies.",
#else
{"枪之飓风",		"利用强力的旋转攻击范围内的敌人.",
#endif
23,		38,2,		83,4,
{0,0,0},			{sinWP1,0,0,0,0,0,0,0,0,0},
F_Tornado_Pike,SKILL_TORNADO,SIN_SKILL_USE_RIGHT,Tornado_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Weapon DEF Mastery",		"Permanently raises defense     rating with polearms.",
#else
{"躲避专家",		"永久性的增加枪系武器交战时的躲闪能力.",
#endif
26,		0,0,		0,0,
{0,0,0},			{sinWA1,sinWH1,sinWP1,sinWS2,0,0,0,0,0,0},
F_Weapone_Defence_Mastery,SKILL_WEAPONE_DEFENCE_MASTERY,SIN_SKILL_USE_NOT,0},

#ifdef ENGLISH_LANGUAGE
{"Expansion",		"Imbues weapon with Vigor to    unleash a devastating attack.",
#else
{"无限力枪",		"使武器巨大化并攻击巨大化范围内的敌人.",
#endif
30,		42,2,		82,4,
{0,0,0},			{sinWA1,sinWH1,sinWP1,0,0,0,0,0,0,0},
F_Expansion,SKILL_EXPANSION,SIN_SKILL_USE_ALL,Expansion_UseMana},

// 3转
#ifdef ENGLISH_LANGUAGE
{"Venom sphere",		"Thrust a sphere to the ground to attack opponents.",
#else
{"灵蛇标枪",		"制造出毒蛇般的毒属性地枪攻击敌人.",
#endif
40,		50,2,		110,2,
{0,0,0},			{sinWP1,0,0,0,0,0,0,0,0,0},
F_Venom_Spear,SKILL_VENOM_SPEAR,SIN_SKILL_USE_RIGHT,VenomSpear_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Vanish",		"It makes you an invisible man in a limited time.",
#else
{"隐暗之术",		"在有效的时间内隐身从而降低敌人的视野并偷袭敌人.",
#endif
43,		53,2,		140,2,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Vanish,SKILL_VANISH,SIN_SKILL_USE_RIGHT,Vanish_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Critical Mastery",		"The skill makes to increase Critical ATK (%) permanently.",
#else
{"会心之枪",		"永久性的增加必杀攻击的几率.",
#endif
46,		0,0,		0,0,
{0,0,0},			{sinWP1,0,0,0,0,0,0,0,0,0},
F_Critical_Mastery,SKILL_CRITICAL_MASTERY,SIN_SKILL_USE_NOT,0},

#ifdef ENGLISH_LANGUAGE
{"Chain Lancer",		"Critical Spinning 3 Hits ATK.",
#else
{"链骑之枪",		"华丽而实用的三连击有效的打击敌人.",
#endif
50,		51,2,		88,3,
{0,0,0},			{sinWC1,sinWP1,sinWS2,0,0,0,0,0,0,0},
F_Chain_Lance,SKILL_CHAIN_LANCE,SIN_SKILL_USE_RIGHT,Chain_Lance_UseMana},

// 4转
#ifdef ENGLISH_LANGUAGE
{"Assassin Eye",		"Find a monster's weak point, increase concentration.",
#else
{"暗杀之眼",		"提高自身的必杀率并发现敌人的弱点和降低敌人的必杀率.",
#endif
60,		61,2,		520,0,
{1,0,0},			{sinWP1,0,0,0,0,0,0,0,0,0},
F_Assassin_Eye,SKILL_ASSASSIN_EYE,SIN_SKILL_USE_RIGHT,Assassin_Eye_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Charging Strike",		"Gathers a power and Continuous ATK.",
#else
{"转换打击",		"利用蓄力攻击强烈的攻击敌人.",
#endif
63,		75,2,		150,0,
{1,0,0},			{sinWP1,sinWS2,0,0,0,0,0,0,0,0},
F_Charging_Strike,SKILL_CHARGING_STRIKE,SIN_SKILL_USE_RIGHT,Charging_Strike_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Vague",		"It does not make your body clearly.",
#else
{"影隐之遁",		"使自己的身体看起来不那么清楚从而提高闪避率.",
#endif
66,		71,2,		650,0,
{1,0,0},			{sinWP1,0,0,0,0,0,0,0,0,0},
F_Vague,SKILL_VAGUE,SIN_SKILL_USE_RIGHT,Vague_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Shadow Master",		"Some afterimages make a powerful damage to a monster in turn.",
#else
{"宇宙幻影",		"制造出多个影子来攻击面对的敌人随着影子的增加而增加攻击力.",
#endif
70,		51,2,		160,0,
{1,0,0},			{sinWP1,sinWS2,0,0,0,0,0,0,0,0},
F_Shadow_Master,SKILL_SHADOW_MASTER,SIN_SKILL_USE_RIGHT,Shadow_Master_UseMana},

// 5转

#ifdef ENGLISH_LANGUAGE
{"Dancing Reaper",		"Jump in the air to deliver a spining powerful strike.",
#else
{"回旋打击",		"跳到空中回旋转动打击对方.",
#endif
80,		75,2,		150,0,
{2,0,0},			{sinWP1,sinWC1,sinWS2,0,0,0,0,0,0,0},
F_D_Reaper,SKILL_D_REAPER,SIN_SKILL_USE_RIGHT,D_Reaper_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Final Spear",		"Big spears pop up from the ground to attack enemies within range.",
#else
{"地枪奇袭",		"释放冰属性枪攻击.",
#endif
83,		70,2,		110,2,
{2,0,0},			{sinWP1,0,0,0,0,0,0,0,0,0},
F_F_Spear,SKILL_F_SPEAR,SIN_SKILL_USE_RIGHT,F_Spear_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Amplified",		"Using a lightning power to increase minimum attack power and accuracy.",
#else
{"潜能激发",		"在一定时间内降低自身的吸收来增加攻击力.",
#endif
86,		93,2,		160,0,
{2,0,0},			{sinWP1,sinWS2,0,0,0,0,0,0,0,0},
F_Amplified,SKILL_AMPLIFIED,SIN_SKILL_USE_RIGHT,Amplified_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Side Spin Attack",		"Strikes the enemy with 2 super powerful side spin attacks",
#else
{"旋风之枪",		"连续回旋两次打击对方.",
#endif
90,		81,2,		160,0,
{2,0,0},			{sinWP1,sinWS2,0,0,0,0,0,0,0,0},
F_SS_Attack,SKILL_SS_ATTACK,SIN_SKILL_USE_RIGHT,SS_Attack_UseMana},


//弓箭手
#ifdef ENGLISH_LANGUAGE
{"Scout Hawk",		"Summons a hawk to scout the    surrounding area, raising attack rating.",
#else
{"侦察之鹰",		"放出一只猎鹰开阔视野并提高命中率.",
#endif
10,		25,2,		115,5,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Scout_Hawk ,SKILL_SCOUT_HAWK,SIN_SKILL_USE_RIGHT,Scout_Hawk_UseMana },

#ifdef ENGLISH_LANGUAGE
{"Shooting Mastery",		"Permanently raises attack power with bows and crossbows.",
#else
{"强力之箭",		"永久提升弓箭射击的攻击力.",
#endif
12,		0,0,		0,0,
{0,0,0},			{sinWS1,0,0,0,0,0,0,0,0,0},
F_Shooting_Mastery,SKILL_SHOOTING_MASTERY,SIN_SKILL_USE_NOT,0},

#ifdef ENGLISH_LANGUAGE
{"Wind Arrow",		"Imbues an arrow with wind      properties to increase attack  power.",
#else
{"疾风之箭",		"射出如风般的箭提高攻击力和攻击速度.",
#endif
14,		25,2,		82,3,
{0,0,0},			{sinWS1,0,0,0,0,0,0,0,0,0},
F_Wind_Arrow,SKILL_WIND_ARROW,SIN_SKILL_USE_ALL,Wind_Arrow_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Perfect Aim",		"Makes an aimed shot with       increased Attack Rating and    Power.",
#else
{"夺命之箭",		"增加弓箭攻击的准确性提高命中率和攻击力.",
#endif
17,		29,2,		81,3,
{0,0,0},			{sinWS1,0,0,0,0,0,0,0,0,0},
F_Perfect_Aim,SKILL_PERFECT_AIM,SIN_SKILL_USE_ALL,Perfect_Aim_UseMana},

// 2转
#ifdef ENGLISH_LANGUAGE
{"Dion's Eye",		"Trains eyesight like the       legendary archer Dion to       permanently increase attack rating.",
#else
{"射神之眼",		"就像传说的射手戴妮奥一样提高视力永久增强命中率.",
#endif
20,		0,0,		0,0,
{0,0,0},			{sinWS1,0,0,0,0,0,0,0,0,0},
F_Dions_Eye,SKILL_DIONS_EYE,SIN_SKILL_USE_NOT,0},

#ifdef ENGLISH_LANGUAGE
{"Falcon",		"Summons a fierce falcon to     attack nearby enemies.",
#else
{"灵魂之鹰",		"比侦察之鹰拥有更强大攻击力的攻击性鹰.",
#endif
23,		36,2,		115,4,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Falcon ,SKILL_FALCON,SIN_SKILL_USE_RIGHT,Falcon_UseMana },

#ifdef ENGLISH_LANGUAGE
{"Arrow of Rage",		"Shoots an arrow over a desired area which explodes and rains  down fire on enemies.",
#else
{"狂暴火箭",		"向指定的目标发射箭雨.",
#endif
26,		38,2,		82,4,
{0,0,0},			{sinWS1,0,0,0,0,0,0,0,0,0},
F_Arrow_of_Rage,SKILL_ARROW_OF_RAGE,SIN_SKILL_USE_RIGHT,A_Rage_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Avalanche",		"Unleashes a barrage of piercing arrows on a single target.",
#else
{"雪崩之箭",		"向指定的目标发射如雪崩般的攻击.",
#endif
30,		41,2,		103,2,
{0,0,0},			{sinWS1,0,0,0,0,0,0,0,0,0},
F_Avalanche,SKILL_AVALANCHE,SIN_SKILL_USE_RIGHT,Avalanche_UseMana},

// 3转
#ifdef ENGLISH_LANGUAGE
{"Elemental Shot",		"Continuous elememtal attack to opponents.",
#else
{"元素攻击",		"使用雷属性或火属性的弓箭两次发射攻击敌人.",
#endif
40,		43,2,		82,2,
{0,0,0},			{sinWS1,0,0,0,0,0,0,0,0,0},
F_E_Shot,SKILL_ELEMENTAL_SHOT,SIN_SKILL_USE_RIGHT,Elemental_Shot_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Golden Falcon",		"Summons a falcon to attack opponents.",
#else
{"黄金猎鹰",		"召唤一只攻击力强大并且对使用者本身有生命回复的猎鹰.",
#endif
43,		52,2,		120,4,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_G_Falcon,SKILL_GOLDEN_FALCON,SIN_SKILL_USE_RIGHT,Golden_Falcon_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Bum shot",		"Fires explosive arrows twice. Splash damages opponents.",
#else
{"爆裂之箭",		"连续两次发射爆炸性的弓箭攻击敌人已经范围内的敌人.",
#endif
46,		46,2,		87,3,
{0,0,0},			{sinWS1,0,0,0,0,0,0,0,0,0},
F_B_Shot,SKILL_BOMB_SHOT,SIN_SKILL_USE_RIGHT,BombShot_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Perforation",		"Accurate and continuous attack that perforates opponents.",
#else
{"惯穿之箭",		"准确而强力的发射惯穿性的弓箭攻击一定范围内的敌人.",
#endif
50,		48,2,		82,2,
{0,0,0},			{sinWS1,0,0,0,0,0,0,0,0,0},
F_Perforation,SKILL_PERFORATION,SIN_SKILL_USE_RIGHT,Perforation_UseMana},

// 4转
#ifdef ENGLISH_LANGUAGE
{"Recall Wolverine",		"Summons Wolverine.",
#else
{"召唤雪狼",		"召唤雪狼来协助自己攻击.",
#endif
60,		58,2,		900,0,
{1,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Recall_Wolverin,SKILL_RECALL_WOLVERIN,SIN_SKILL_USE_RIGHT,Recall_Wolverin_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Evasion Mastery",		"It avoids an enemy attack effectively.",
#else
{"躲避大师",		"永久提高躲闪能力.",
#endif
63,		0,0,		0,0,
{1,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Evasion_Mastery,SKILL_EVASION_MASTERY,SIN_SKILL_USE_NOT,0},

#ifdef ENGLISH_LANGUAGE
{"Phoenix Shot",		"It gives wide ATK with Energy of Phoenix.",
#else
{"绯凰绝炎",		"把弓箭变为火凤凰的惯穿攻击.",
#endif
66,		55,2,		100,0,
{1,0,0},			{sinWS1,0,0,0,0,0,0,0,0,0},
F_Phoenix_Shot,SKILL_PHOENIX_SHOT,SIN_SKILL_USE_RIGHT,Phoenix_Shot_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Force of Nature",		"It improves your ability by natural assimilation perfectly.",
#else
{"自然之光",		"提身弓箭手本身的攻击力和命中.",
#endif
70,		56,2,		900,0,
{1,0,0},			{sinWS1,0,0,0,0,0,0,0,0,0},
F_Force_Of_Nature,SKILL_FORCE_OF_NATURE,SIN_SKILL_USE_RIGHT,Force_Of_Nature_UseMana},

// 5转

#ifdef ENGLISH_LANGUAGE
{"Evade Shot",		"Jump away to shoot arrow to enemy below",
#else
{"回旋之舞",		"跳跃到空中放出强力一箭.",
#endif
80,		52,2,		80,2,
{2,0,0},			{sinWS1,0,0,0,0,0,0,0,0,0},
F_S_Shot,SKILL_E_SHOT,SIN_SKILL_USE_RIGHT,E_Shot_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Thunder Roop",		"Using lightning for a powerful attack",
#else
{"玄光之箭",		"提身弓箭手本身的攻击力和命中.",
#endif
83,		52,2,		80,2,
{2,0,0},			{sinWS1,0,0,0,0,0,0,0,0,0},
F_S_Rope,SKILL_S_ROPE,SIN_SKILL_USE_RIGHT,S_Rope_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Nature Splash",		"Shoots an arrow with energy from the nature",
#else
{"飓风之箭",		"提身弓箭手本身的攻击力和命中.",
#endif
86,		57,2,		80,2,
{2,0,0},			{sinWS1,0,0,0,0,0,0,0,0,0},
F_N_Splash,SKILL_N_SPLASH,SIN_SKILL_USE_RIGHT,N_Splash_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Circle Trap",		"Capture the enemy weakness and slows down the enemy's speed",
#else
{"复仇箭雨",		"提身弓箭手本身的攻击力和命中.",
#endif
90,		95,2,		90,2,
{2,0,0},			{sinWS1,0,0,0,0,0,0,0,0,0},
F_C_Trap,SKILL_C_TRAP,SIN_SKILL_USE_RIGHT,C_Trap_UseMana},

//游侠
#ifdef ENGLISH_LANGUAGE
{"Sword Blast",			"Throws a devastating sword to attack enemies",
#else
{"魔神剑",			"释放如狂风般的剑气来攻击敌人.",
#endif
10,		22,2,		82,2,
{0,0,0},			{sinWS2,0,0,0,0,0,0,0,0,0},
F_Sword_Blast,SKILL_SWORD_BLAST,SIN_SKILL_USE_ALL,Sword_Blast_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Holy Body",		"Become holy for a period of time to increase absorb rating against undead enemies",
#else
{"圣光护体",		"使身体变为圣属性增加对不死系怪物攻击的吸收.",
#endif
12,		28,2,		110,3,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_HolyBody ,SKILL_HOLY_BODY,SIN_SKILL_USE_RIGHT,HolyBody_UseMana },

#ifdef ENGLISH_LANGUAGE
{"Physical Training",		"Physical Training increases stamina permanently",
#else
{"超能体训",		"通过死亡特训永久的增加耐力值.",
#endif
14,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Physical_Traning,SKILL_PHYSICAL_TRANING,SIN_SKILL_USE_NOT,0},

#ifdef ENGLISH_LANGUAGE
{"Double Crash",		"Strikes twice with a consecutive attack",
#else
{"双重爆击",		"连续两次释放出重击.",
#endif
17,		35,2,		82,2,
{0,0,0},			{sinWA1,sinWC1,sinWS2,0,0,0,0,0,0,0},
F_Double_Crash,SKILL_DOUBLE_CRASH,SIN_SKILL_USE_RIGHT,D_Crash_UseMana},

// 2转
#ifdef ENGLISH_LANGUAGE
{"Holy Valor",		"Increases attack power of the party against the Undead",
#else
{"神力重击",		"利用英勇的力量加强对不死系怪物攻击.",
#endif
20,		36,2,		100,3,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Holy_Valor,SKILL_HOLY_VALOR,SIN_SKILL_USE_RIGHT,Holy_Valor_Mana},

#ifdef ENGLISH_LANGUAGE
{"Brandish",		"Damaging all enemies within the splash range",
#else
{"狂躁挥舞",		"有效打击半径内的所有敌人.",
#endif
23,		38,2,		82,2,
{0,0,0},			{sinWP1,sinWS2,0,0,0,0,0,0,0,0},
F_Brandish,SKILL_BRANDISH,SIN_SKILL_USE_ALL,Brandish_Mana},

#ifdef ENGLISH_LANGUAGE
{"Piercing",			"Pierces a sword through the targeted enemy with a powerful attack",
#else
{"一雾银",			"利用强大的攻击力惯穿攻击范围内的敌人.",
#endif
26,		41,2,		82,2,
{0,0,0},			{sinWS2,0,0,0,0,0,0,0,0,0},
F_Piercing,SKILL_PIERCING,SIN_SKILL_USE_ALL,Piercing_Mana},

#ifdef ENGLISH_LANGUAGE
{"Drastic Spirit",		"Increases Defense Rating",
#else
{"天佑神铠",		"一定时间内提高自身的防御力.",
#endif
30,		44,2,		100,2,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Drastic_Spirit,SKILL_DRASTIC_SPIRIT,SIN_SKILL_USE_RIGHT,Drastic_Spirit_Mana},

// 3转
#ifdef ENGLISH_LANGUAGE
{"Sword Mastery",		"Increases attack power on swords permanently",
#else
{"精剑之术",		"永久增加剑的攻击力.",
#endif
40,		0,0,		0,0,
{0,0,0},			{sinWS2,0,0,0,0,0,0,0,0,0},
F_S_Mastery,SKILL_SWORD_MASTERY,SIN_SKILL_USE_NOT,0},

#ifdef ENGLISH_LANGUAGE
{"Divine Shield",		"Increases block and converts blocked undead damage into HP",
#else
{"圣灵之吸",		"利用神圣的盾牌把不死系的攻击转换为生命力并吸收攻击力.",
#endif
43,		46,2,		130,1,
{0,0,0},			{sinDS1,0,0,0,0,0,0,0,0,0},
F_D_Inhalation,SKILL_DIVINE_INHALATION,SIN_SKILL_USE_RIGHT,D_Inhalation_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Holy Incantation",		"Transforms the targeted monster into a pet that will fight for you in battle",
#else
{"圣剡之光",		"利用神圣的光芒把不死系的怪物召唤为自己的宠物.",
#endif
46,		50,2,		120,1,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Holy_Incantation,SKILL_HOLY_INCANTATION,SIN_SKILL_USE_RIGHT,H_Incantation_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Grand cross",		"Attacks the enemy with a deadly cross",
#else
{"圣光十字",		"利用两次横切攻击产生一个十字重创敌人对不死系敌人有特效.",
#endif
50,		45,2,		82,2,
{0,0,0},			{sinWH1,sinWS2,0,0,0,0,0,0,0,0},
F_Grand_Cross,SKILL_GRAND_CROSS,SIN_SKILL_USE_RIGHT,Grand_Cross_UseMana},

// 4转

#ifdef ENGLISH_LANGUAGE
{"Sword of Justice",		"Strikes the enemy with several powerful hits",
#else
{"真魔神剑",		"释放出强有力的剑气来攻击范围内的敌人.",
#endif
60,		53,2,		250,0,
{1,0,0},			{sinWS2,0,0,0,0,0,0,0,0,0},
F_Sword_Of_Justice,SKILL_SWORD_OF_JUSTICE,SIN_SKILL_USE_RIGHT,Sword_Of_Justice_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Godly Shield",		"Forms a Holy Shield blessed by God",
#else
{"敬神之盾",		"一个受到上帝祝福而产生一个吸收攻击力的盾.",
#endif
63,		50,2,		400,0,
{1,0,0},			{sinDS1,0,0,0,0,0,0,0,0,0},
F_Godly_Shield,SKILL_GODLY_SHIELD,SIN_SKILL_USE_RIGHT,Godly_Shield_UseMana},

#ifdef ENGLISH_LANGUAGE
{"God Bless",		"Increases your attack power by the name of God",
#else
{"上帝祝福",		"以上帝的名义赋予剑圣强大的力量.",
#endif
66,		51,2,		330,0,
{1,0,0},			{sinWA1,sinWC1,sinWH1,sinWP1,sinWS2,sinWS1,sinWT1,0,0,0},
F_God_Bless,SKILL_GOD_BLESS,SIN_SKILL_USE_RIGHT,God_Bless_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Divine Piercing",		"Attacks the enemy with the help of God's power to unleash a devastating strike",
#else
{"刹剧荒舞",		"借助上帝之力挥舞一段剑舞来攻击敌人.",
#endif
70,		51,2,		160,0,
{1,0,0},			{sinWS2,0,0,0,0,0,0,0,0,0},
F_Divine_Piercing,SKILL_DIVINE_PIERCING,SIN_SKILL_USE_RIGHT,Divine_Piercing_UseMana},

//5转

#ifdef ENGLISH_LANGUAGE
{"Soul Breaker",		"Powerful attack into the enemy's soul",
#else
{"神力冲刺",		"利用强大的神力冲击对方.",
#endif
80,		69,2,		150,0,
{2,0,0},			{sinWS2,0,0,0,0,0,0,0,0,0},
F_S_Breaker,SKILL_S_BREAKER,SIN_SKILL_USE_RIGHT,S_Breaker_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Crescent Moon",		"Attacks the enemy with a close instant attack",
#else
{"升龙重击",		"瞬间攻击远处的敌人.",
#endif
83,		70,2,		110,0,
{2,0,0},			{sinWS2,0,0,0,0,0,0,0,0,0},
F_C_Moon,SKILL_C_MOON,SIN_SKILL_USE_RIGHT,C_Moon_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Saint Blade",		"Summoning divine power to your sword to attack the enemy",
#else
{"上帝重击",		"以上帝的名义跳跃到空中攻击对方.",
#endif
86,		75,2,		82,2,
{2,0,0},			{sinWS2,sinWH1,0,0,0,0,0,0,0,0},
F_S_Blade,SKILL_S_BLADE,SIN_SKILL_USE_RIGHT,S_Blade_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Holy Benedic",		"Change the attribute of the monster to undead",
#else
{"死亡宣告",		"一个宣告死亡的倒计时,当时间到了的时候就死定了.",
#endif
90,		93,2,		400,0,
{2,0,0},			{sinWA1,sinWC1,sinWH1,sinWP1,sinWS2,sinWS1,sinWT1,0,0,0},
F_H_Benedic,SKILL_H_BENEDIC,SIN_SKILL_USE_RIGHT,H_Benedic_UseMana},

// 魔枪手

#ifdef ENGLISH_LANGUAGE
{"Shield Strike",		"hurls a shield to attack enemies.",
#else
{"美杜莎盾",		"投掷盾牌给予敌人惯穿性攻击.",
#endif
10,		23,2,		82,2,
{0,0,0},			{sinDS1,0,0,0,0,0,0,0,0,0},
F_S_Strike ,SKILL_SHIELD_STRIKE,SIN_SKILL_USE_RIGHT,S_Strike_UseMana },

#ifdef ENGLISH_LANGUAGE
{"Farina",		"Throws a spear that creates illusions",
#else
{"含沙射影",		"快速投掷标枪可以连续敌人.",
#endif
12,		26,2,		82,2,
{0,0,0},			{sinWT1,0,0,0,0,0,0,0,0,0},
F_Farina,SKILL_FARINA,SIN_SKILL_USE_ALL,Farina_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Throwing Mastery",		"Trains Javelin attacks to increase damage permenantly using Javelins",
#else
{"魔力神枪",		"永久提升标枪的攻击力.",
#endif
14,		0,0,		0,0,
{0,0,0},			{sinWT1,0,0,0,0,0,0,0,0,0},
F_D_Mastery,SKILL_THROWING_MASTERY,SIN_SKILL_USE_NOT,0},

#ifdef ENGLISH_LANGUAGE
{"Bigger Spear",		"Attacks the targeted enemy with a holy Javelin",
#else
{"精神之枪",		"结合魔力的投枪技术.",
#endif
17,		32,2,		82,2,
{0,0,0},			{sinWP1,sinWT1,0,0,0,0,0,0,0,0},
F_V_Spear,SKILL_VIGOR_SPEAR,SIN_SKILL_USE_ALL,V_Spear_UseMana},

// 2转

#ifdef ENGLISH_LANGUAGE
{"Windy",		"Increases range and attack rating of Javelins",
#else
{"追命劲风",		"将标枪投掷的更远并提高命中率.",
#endif
20,		34,2,		100,2,
{0,0,0},			{sinWT1,0,0,0,0,0,0,0,0,0},
F_Windy,SKILL_WINDY,SIN_SKILL_USE_RIGHT,Windy_Mana},

#ifdef ENGLISH_LANGUAGE
{"Twist Javelin",		"Increase attack rating and attack power with using a twisting tactic",
#else
{"螺旋飞标",		"通过旋转飞标来提高攻击力和命中率.",
#endif
23,		36,2,		82,2,
{0,0,0},			{sinWT1,0,0,0,0,0,0,0,0,0},
F_Twist_Javelin,SKILL_TWIST_JAVELIN,SIN_SKILL_USE_RIGHT,Twist_Javelin_Mana},

#ifdef ENGLISH_LANGUAGE
{"Soul Sucker",		"Absorbs the HP of enemies within attack range that have more than 50 percent HP",
#else
{"灵魂吞噬",		"有一定的成功几率吸收怪物的生命值.",
#endif
26,		42,2,		110,2,
{0,0,0},			{sinDS1,0,0,0,0,0,0,0,0,0},
F_Soul_Sucker,SKILL_SOUL_SUCKER,SIN_SKILL_USE_RIGHT,Soul_Sucker_Mana},

#ifdef ENGLISH_LANGUAGE
{"Fire Javelin",		"Attacks the enemy with power of fire",
#else
{"火焰烈枪",		"利用火属性的标枪攻击敌人.",
#endif
30,		40,2,		82,2,
{0,0,0},			{sinWT1,0,0,0,0,0,0,0,0,0},
F_Fire_Javelin,SKILL_FIRE_JAVELIN,SIN_SKILL_USE_ALL,Fire_Javelin_Mana},

// 3转

#ifdef ENGLISH_LANGUAGE
{"Split Javelin",		"Attacks the enemy with several powerful strikes at very fast speed",
#else
{"追风之枪",		"利用最快的速度连续散发性攻击.",
#endif
40,		43,2,		115,1,
{0,0,0},			{sinWT1,0,0,0,0,0,0,0,0,0},
F_Split_Javelin,SKILL_SPLIT_JAVELIN,SIN_SKILL_USE_RIGHT,Split_Javelin_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Triumph of Valhalla",		"Increases attack power of all party members",
#else
{"战栗咆哮",		"利用强有力的吼声加强队友的气势并提高攻击力.",
#endif
43,		50,2,		120,1,
{0,0,0},			{sinWT1,sinWS2,sinWS1,sinWP1,sinWH1,sinWA1,sinWC1,sinWM1,0,0},
F_T_Of_Valhalla,SKILL_TRIUMPH_OF_VALHALLA,SIN_SKILL_USE_RIGHT,T_Of_Valhalla_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Lightning Javelin",		"Increases the lightning attribute of the Javelin",
#else
{"光猎之枪",		"利用雷属性的标枪来攻击敌人.",
#endif
46,		46,2,		82,2,
{0,0,0},			{sinWT1,0,0,0,0,0,0,0},
F_Lightning_Javelin,SKILL_LIGHTNING_JAVELIN,SIN_SKILL_USE_ALL,Lightning_Javelin_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Storm Javelin",	    "Attacks the enemy with a strong tornado tactic",
#else
{"暴风狂标",	    "以暴风雨般的旋转标枪连续投掷标枪.",
#endif
50,		48,2,		82,2,
{0,0,0},			{sinWT1,0,0,0,0,0,0,0,0,0},
F_Storm_Javelin,SKILL_STORM_JAVELIN,SIN_SKILL_USE_RIGHT,Storm_Javelin_UseMana},

// 4转

#ifdef ENGLISH_LANGUAGE
{"Hall of Valhalla",	"Creates a space to unleash the Power of Valhalla",
#else
{"瓦尔哈拉之光",	"利用瓦尔哈拉之光的力量制造一个空间.",
#endif
60,		52,2,		750,0,
{1,0,0},			{sinWA1,sinWC1,sinWH1,sinWP1,sinWS1,sinWT1,0,0,0,0},
F_Hall_Of_Valhalla,SKILL_HALL_OF_VALHALLA,SIN_SKILL_USE_RIGHT,Hall_Of_Valhalla_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Extreme Rage",		"Attacks the enemy with Power of Anger",
#else
{"十字怒击",		"利用愤怒的跳跃攻击范围内的敌人.",
#endif
63,		48,2,		210,0,
{1,0,0},			{sinWT1,0,0,0,0,0,0,0,0,0},
F_X_Rage,SKILL_X_RAGE,SIN_SKILL_USE_RIGHT,X_Rage_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Frost Javelin",		"Increases ice attribute for a period of time",
#else
{"霜冻标枪",		"是标枪在一定时间内维持冰属性并带有冰属性攻击.",
#endif
66,		50,2,		720,0,
{1,0,0},			{sinWT1,0,0,0,0,0,0,0,0,0},
F_Frost_Javelin,SKILL_FROST_JAVELIN,SIN_SKILL_USE_RIGHT,Frost_Javelin_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Vengeance",		"Attacks the enemy with several fast and powerful attacks",
#else
{"狂风爆裂",		"快速的连续的投掷标枪.",
#endif
70,		45,2,		100,0,
{1,0,0},			{sinWT1,0,0,0,0,0,0,0,0,0},
F_Vengeance,SKILL_VENGEANCE,SIN_SKILL_USE_RIGHT,Vengeance_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Talaria",		"Increases your running speed",
#else
{"轻舞飞扬",		"增加自己和队友的移动速度.",
#endif
80,		68,2,		720,0,
{2,0,0},			{sinWT1,0,0,0,0,0,0,0,0,0},
F_Talaria,SKILL_TALARIA,SIN_SKILL_USE_RIGHT,Talaria_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Galaxy Coup",		"Summoning javelins in the air and throw them on the floor causing damage to enemies within range",
#else
{"星雨标枪",		"召唤星雨标枪协助自己攻击.",
#endif
83,		52,2,		120,0,
{2,0,0},			{sinWT1,0,0,0,0,0,0,0,0,0},
F_G_Coup,SKILL_G_COUP,SIN_SKILL_USE_RIGHT,G_Coup_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Recall Arcuda",			"Summons Arcuda to support you in the battle",
#else
{"笨笨熊",			"召唤笨笨熊来协助自己攻击.",
#endif
86,		95,2,		720,0,
{2,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_S_Arcuda,SKILL_S_ARCUDA,SIN_SKILL_USE_RIGHT,S_Arcuda_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Snippy Fear",		"Throws 2 javelins on the enemy with massive critical damage",
#else
{"烈焰突袭",		"快速的连续的投掷标枪并提高必杀.",
#endif
90,		57,2,		100,0,
{2,0,0},			{sinWT1,0,0,0,0,0,0,0,0,0},
F_S_Fear,SKILL_S_FEAR,SIN_SKILL_USE_RIGHT,S_Fear_UseMana},

// 祭司

#ifdef ENGLISH_LANGUAGE
{"Healing",		"heals life with its holy magic.",
#else
{"治愈之术",		"通过神圣的魔法回复自身的生命以及其他生命生物的生命力对不死系怪物有奇特效果.",
#endif
10,		15,1,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Healing,SKILL_HEALING,SIN_SKILL_USE_RIGHT,Healing_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Holy Bolt",		"hurls a holy bolt to enemies.",
#else
{"圣光电球",		"通过魔法发射波球状的气流来攻击敌人(对不死死系怪物有特效).",
#endif
12,		11,1,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_HolyBolt,SKILL_HOLY_BOLT,SIN_SKILL_USE_ALL,HolyBolt_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Multi Spark",		"Releases magical sparks to attack enemies.",
#else
{"光芒四射",		"通过魔法产生星状气流来攻击敌人.",
#endif
14,		14,1,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_M_Spark,SKILL_MULTISPARK,SIN_SKILL_USE_RIGHT,M_Spark_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Holy Mind",		"It weakens enemy's attack in a given time.",
#else
{"意念之术",		"通过魔法能力降低怪物的攻击力但对人无效.",
#endif
17,		19,1,		100,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_HolyMind,SKILL_HOLY_MIND,SIN_SKILL_USE_RIGHT,HolyMind_UseMana},

// 2转

#ifdef ENGLISH_LANGUAGE
{"Meditation",		"Increase mana recovery permanently.",
#else
{"曙光耀灵",		"永久提升魔法的回复能力.",
#endif
20,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Meditation,SKILL_MEDITATION,SIN_SKILL_USE_NOT,0},

#ifdef ENGLISH_LANGUAGE
{"Divine Lightning",		"Attack enemies with holy lightning.",
#else
{"神之雷电",		"利用神圣的雷电力量来攻击敌人.",
#endif
23,		21,1,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Divine_Lightning,SKILL_DIVINE_LIGHTNING,SIN_SKILL_USE_RIGHT,Divine_Lightning_Mana},

#ifdef ENGLISH_LANGUAGE
{"Holy Reflection",		"Reflect attacks from undead by creating holy magical shield.",
#else
{"神圣反射",		"通过神圣的魔法盾来反射不死系怪物的攻击.",
#endif
26,		23,1,		120,1,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Holy_Reflection,SKILL_HOLY_REFLECTION,SIN_SKILL_USE_RIGHT,Holy_Reflection_Mana},

#ifdef ENGLISH_LANGUAGE
{"Grand Healing",		"Heal life of a party member.",
#else
{"圣洁之光",		"回复有效半径内队伍中队友的生命.",
#endif
30,		27,1,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Grand_Healing,SKILL_GRAND_HEALING,SIN_SKILL_USE_RIGHT,Grand_Healing_Mana},

// 3转

#ifdef ENGLISH_LANGUAGE
{"Vigor ball",		"Fires vigor ball twice to opponents.",
#else
{"火影双重",		"连续两次发射用魔法制造的魔法球.",
#endif
40,		24,1,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Vigor_Ball,SKILL_VIGOR_BALL,SIN_SKILL_USE_ALL,Vigor_Ball_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Resurrection",		"Revives a dead party member.",
#else
{"回生之术",		"可以使队伍中的队友在原地复活.",
#endif
43,		31,1,		130,1,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Resurrection,SKILL_RESURRECTION,SIN_SKILL_USE_RIGHT,Resurrection_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Extinction",		"lethal incantation to undead monsters. Permanent damage to undead units.",
#else
{"圣光之咒",		"用神圣的咒语有一定几率让不死系的怪物受到致命创伤.",
#endif
46,		28,1,		120,1,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Extinction,SKILL_EXTINCTION,SIN_SKILL_USE_RIGHT,Extinction_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Virtual life",		"Increases party members' life for a while.",
#else
{"神圣之光",		"一定时间内增加生命值上限.",
#endif
50,		31,1,		134,1,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Virtual_Life,SKILL_VIRTUAL_LIFE,SIN_SKILL_USE_RIGHT,Virtual_Life_UseMana},

// 4转

#ifdef ENGLISH_LANGUAGE
{"Glacial Spike",		"Huge ice block released to attack enemies.",
#else
{"冰霜噬月",		"释放巨大的冰块来打击敌人.",
#endif
60,		35,1,		120,0,
{1,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Glacial_Spike,SKILL_GLACIAL_SPIKE,SIN_SKILL_USE_RIGHT,Glacial_Spike_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Regeneration Field",		"After your sacrifice, it recoveries your company continuously.",
#else
{"再生领域",		"加速在范围内同伴的回复能力.",
#endif
63,		41,1,		950,0,
{1,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Regeneration_Field,SKILL_REGENERATION_FIELD,SIN_SKILL_USE_RIGHT,Regeneration_Field_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Chain Lightning",		"It attacks powerful thunder ATK to Monsters.",
#else
{"天雷之怒",		"召唤天雷利用神圣的强有力的闪电来攻击范围内的敌人.",
#endif
66,		41,1,		120,0,
{1,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Chain_Lightning,SKILL_CHAIN_LIGHTNING,SIN_SKILL_USE_RIGHT,Chain_Lightning_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Summon Muspell",		"It absorbs undead monster's ATK, resurrects HP and has summoner's ability.",
#else
{"神圣天使",		"召唤大天使来协助自己攻击.",
#endif
70,		47,1,		800,0,
{1,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Summon_Muspell,SKILL_SUMMON_MUSPELL,SIN_SKILL_USE_RIGHT,Summon_Muspell_UseMana},

// 5转

#ifdef ENGLISH_LANGUAGE
{"Spirit Impact",		"Power shockwave attack on your enemy..",
#else
{"神圣电波",		"通过魔法产生强力的冲击波.",
#endif
80,		45,2,		120,0,
{2,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_S_Impact,SKILL_S_IMPACT,SIN_SKILL_USE_RIGHT,S_Impact_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Piercing Ice",		"Summons magical powers to attack with sharp ice spears..",
#else
{"神圣兵刃",		"通过魔法召唤冰刃打击对方.",
#endif
83,		50,2,		110,0,
{2,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_P_Ice,SKILL_P_ICE,SIN_SKILL_USE_RIGHT,P_Ice_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Ice Meteorite",		"Calls in an ice cold meteorite storm which will damage and freeze opponents near the strike area of each meteorite.",
#else
{"大暴风雪",		"召唤冰之陨石打击对方并产生冻结效果.",
#endif
86,		88,3,		120,0,
{2,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_S_Ramiel,SKILL_S_PRMIEL,SIN_SKILL_USE_RIGHT,S_Ramiel_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Blessing Krishna",		"Increases your defense and absorb by grace of god.",
#else
{"天女散花",		"增加自身的闪避和吸收.",
#endif
90,		60,2,		950,0,
{2,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_B_Krishna,SKILL_B_KRISHNA,SIN_SKILL_USE_RIGHT,B_Krishna_UseMana},


// 魔法师

#ifdef ENGLISH_LANGUAGE
{"Agony",		"Sacrifice oneself to increase spirit.",
#else
{"魔力转化",		"把自己的生命力转换成自己的魔法能力.",
#endif
10,		12,1,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Agony,SKILL_AGONY,SIN_SKILL_USE_RIGHT,Agony_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Fire Bolt",		"Calls down small fireballs to attack enemies",
#else
{"火箭之术",		"释放出绚丽的火箭来攻击敌人.",
#endif
12,		11,1,		84,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_FireBolt,SKILL_FIRE_BOLT,SIN_SKILL_USE_ALL,FireBolt_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Zenith",		"Increase element features with strong spirit for a given time.",
#else
{"集合之术",		"利用魔法能力在一定时间内提升属性值.",
#endif
14,		15,1,		100,3,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Zenith,SKILL_ZENITH,SIN_SKILL_USE_RIGHT,Zenith_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Fire Ball",		"Calls down huge fireballs to attack enemies.",
#else
{"火球之术",		"使用巨大的火球来进行敌人.",
#endif
17,		19,1,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_FireBall,SKILL_FIRE_BALL,SIN_SKILL_USE_RIGHT,FireBall_UseMana},

// 2转

#ifdef ENGLISH_LANGUAGE
{"Mental Mastery",		"Increases maximum mana.",
#else
{"控制意念",		"增加魔法值的最大上限.",
#endif
20,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Mental_Mastery,SKILL_MENTAL_MASTERY,SIN_SKILL_USE_NOT,0},

#ifdef ENGLISH_LANGUAGE
{"Watornado",		"A pilar of water strikes enemies.",
#else
{"龙卷海风",		"释放出如龙卷风般的水柱对敌人进行攻击.",
#endif
23,		21,1,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Watornado,SKILL_WATORNADO,SIN_SKILL_USE_RIGHT,Watornado_Mana},

#ifdef ENGLISH_LANGUAGE
{"Enchant Weapon",		"Enhance the attacking element in weapon of party member.",
#else
{"元素之术",		"给队伍中的队员附加雷火冰三种属性附加攻击力.",
#endif
26,		28,1,		104,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Enchant_Weapon,SKILL_ENCHANT_WEAPON,SIN_SKILL_USE_RIGHT,Enchant_Weapon_Mana},

#ifdef ENGLISH_LANGUAGE
{"Death Ray",		"Fire Powerful ray from palms.",
#else
{"冥亡之光",		"从掌心释放出激光来打击敌人.",
#endif
30,		26,1,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Dead_Ray,SKILL_DEAD_RAY,SIN_SKILL_USE_ALL,Dead_Ray_Mana},

// 3转

#ifdef ENGLISH_LANGUAGE
{"Energy shield",		"Forms a magical shield around the body.",
#else
{"魔法守护",		"在身体周围形成一个球体的魔法护体.",
#endif
40,		40,1,		150,1,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Energy_Shield,SKILL_ENERGY_SHIELD,SIN_SKILL_USE_RIGHT,Energy_Shield_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Diastrophism",		"Strong geographical attack to opponents within range.",
#else
{"地裂冲击",		"在地面发生强烈的震动对范围内的所有敌人给予伤害.",
#endif
43,		33,1,		106,1,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Diastrophism,SKILL_DIASTROPHISM,SIN_SKILL_USE_RIGHT,Diastrophism_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Spirit elemental",		"Summons a ghost to increase magical damage.",
#else
{"灵魂召唤",		"召唤小精灵来增强魔法攻击力.",
#endif
46,		35,1,		150,1,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Spirit_Elemental,SKILL_SPIRIT_ELEMENTAL,SIN_SKILL_USE_RIGHT,Spirit_Elemental_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Dancing sword",		"A phantom of sword appears and uses the power of element to attack enemies.",
#else
{"元素之剑",		"利用魔法制造一个火属性或冰属性的剑来攻击.",
#endif
50,		30,1,		150,1,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_D_Sword,SKILL_DANCING_SWORD,SIN_SKILL_USE_RIGHT,Dancing_Sword_UseMana},

// 4转

#ifdef ENGLISH_LANGUAGE
{"Fire Elemental",		"The skill summons a strong elemental made with fire.",
#else
{"伊夫列特",		"召唤火精灵来协助自己攻击.",
#endif
60,		120,2,		900,0,
{1,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Fire_Elemental,SKILL_FIRE_ELEMENTAL,SIN_SKILL_USE_RIGHT,Fire_Elemental_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Flame Wave",		"It attacks the front monsters with powerful fire flame.",
#else
{"火焰波动",		"利用强有力的火焰冲击面对的敌人.",
#endif
63,		32,1,		124,0,
{1,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Flame_Wave,SKILL_FLAME_WAVE,SIN_SKILL_USE_RIGHT,Flame_Wave_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Distortion",		"It takes down a monster's ability with Distortion of Space.",
#else
{"空间扭曲",		"使空间扭曲并降低敌人的能力.",
#endif
66,		43,1,		460,0,
{1,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Distortion,SKILL_DISTORTION,SIN_SKILL_USE_RIGHT,Distortion_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Meteorite",		"It attacks nearby monsters with summoned meteorites.",
#else
{"陨石召唤",		"召唤陨石来攻击范围内的敌人.",
#endif
70,		39,1,		190,0,
{1,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Meteo,SKILL_M_METEO,SIN_SKILL_USE_RIGHT,Meteo_UseMana},

// 5转

#ifdef ENGLISH_LANGUAGE
{"Silraphim",		"Summoning the power of Silraphim to attack the enemy.",
#else
{"流星火雨",		"借它的力量强打对方.",
#endif
80,		45,2,		120,0,
{2,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_Silraphim,SKILL_SILRAPHIM,SIN_SKILL_USE_RIGHT,Silraphim_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Vis Tenus",		"Shrinks the enmy and reduces their movement.",
#else
{"蛛网之术",		"降低对方的移动速度.",
#endif
83,		50,2,		460,0,
{2,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_V_Tenus,SKILL_V_TENUS,SIN_SKILL_USE_RIGHT,V_Tenus_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Prima Ignis",		"Summons a power explosion for a powerful attack",
#else
{"神圣洗礼",		"用冥界的火焰给予对方强力打击.",
#endif
89,		54,2,		120,0,
{2,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_P_Ignis,SKILL_P_IGNIS,SIN_SKILL_USE_RIGHT,P_Ignis_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Third Anima",		"Decreases your max strength to raise attack power",
#else
{"神圣法阵",		"减少魔法值来增加魔法攻击力.",
#endif
90,		60,2,		150,1,
{2,0,0},			{sinWM1,0,0,0,0,0,0,0,0,0},
F_T_Anima,SKILL_T_ANIMA,SIN_SKILL_USE_RIGHT,T_Anima_UseMana},

// 刺客

#ifdef ENGLISH_LANGUAGE
{"Stinger",			"Runs straight towards the enemy and hits the enemy with two quick attacks",
#else
{"刺击",			"敏捷的以毒属性武器进行攻击.",
#endif
10,		22,2,		80,2,
{0,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Stringer,SKILL_STRINGER,SIN_SKILL_USE_ALL,Stinger_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Double Blow",			"Deals continuous damage to the enemy while spinning.",
#else
{"闪击",			"快速移动到敌人面前造成致命性的连续损伤.",
#endif
12,		27,2,		80,2,
{0,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Running,SKILL_RUNNING_HIT,SIN_SKILL_USE_RIGHT,Running_Hit_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Dual Wield Mastery",		"Increases your Attack Power permanently when using daggers",
#else
{"强化攻击",		"使用决斗之剑永久增加攻击力.",
#endif
14,		0,0,		0,0,
{0,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Sword_Mastery,SKILL_SWORDMASTERY,SIN_SKILL_USE_NOT,0},

#ifdef ENGLISH_LANGUAGE
{"Wisp",		"Reduces enemies Attack Power for a period of time",
#else
{"弱点攻击",		"占用临近敌人的弱点,一定时间内减少攻击力.",
#endif
17,		34,2,		110,1,
{0,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Wisp,SKILL_WISP,SIN_SKILL_USE_RIGHT,Wisp_UseMana},

// 2转

#ifdef ENGLISH_LANGUAGE
{"Venom Thorn",		"Attacks the enemy twice rapidly with poisoned daggers",
#else
{"毒牙连击",		"以抹着毒的武器朝敌人快速二连击.",
#endif
20,		18,2,		110,1,
{0,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Verom_Thorn,SKILL_VENOM_THORN,SIN_SKILL_USE_RIGHT,Verom_Thorn_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Alas",		"Distributes dexterity of an Assassin and increases Evasion of all party members",
#else
{"敏捷之力",		"赋予队员刺客的敏捷,并提升回避率.",
#endif
23,		38,2,		110,1,
{0,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Ales,SKILL_ALAS,SIN_SKILL_USE_RIGHT,Ales_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Soul Shock",		"Performs a hard hit to the ground and stun all enemies around",
#else
{"灵魂震撼",		"使一定范围内的敌人气绝陷入混乱.",
#endif
26,		39,2,		110,1,
{0,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Soul_Shock,SKILL_SOUL_SHOCK,SIN_SKILL_USE_RIGHT,Soul_Shock_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Blade Mastery",		"Increases your Attack Power and Evasion permanently when using daggers",
#else
{"攻击大师",		"攻击和回避率永久上升.",
#endif
30,		0,0,		0,0,
{0,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Blade_Mastery,SKILL_ATTACK_MASTERY,SIN_SKILL_USE_NOT,0},

// 3转

#ifdef ENGLISH_LANGUAGE
{"Finishing Blow",		"Deals repeated damage to the enemy. Finishing Blow effect will apply on the first hit",
#else
{"飞剑之舞",		"给敌人带去连续的敏锐的损伤.",
#endif
40,		50,2,		80,2,
{0,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Finishing_Blow,SKILL_SORE_SWORD,SIN_SKILL_USE_ALL,Finishing_Blow_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Gust Slash",			"Jumps towards the enemy and attacks repeatedly to deal massive damage to the enemy and anyone nearby",
#else
{"跳斩",			"快速跳起给予敌人致命的损伤.",
#endif
43,		53,2,		110,1,
{0,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Gust_Shash,SKILL_BEAT_UP,SIN_SKILL_USE_RIGHT,Gust_Shash_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Inpes",		"Increases your Attack Speed temporarily",
#else
{"敏捷大师",		"以高度的集中力聚集气提高攻击速度.",
#endif
46,		48,2,		120,2,
{0,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Inpes,SKILL_INPES,SIN_SKILL_USE_RIGHT,Inpes_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Deception",			"Hides into your own shadow which turn you invisible to enemies eyes for a short duration until you attack",
#else
{"致盲",			"隐藏自己的影子,给予敌人强力的损伤.",
#endif
50,		53,2,		120,2,
{0,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Deception,SKILL_BLIND,SIN_SKILL_USE_RIGHT,Deception_UseMana},

// 4转

#ifdef ENGLISH_LANGUAGE
{"Frost Wind",		"Moves quickly to deal repeated fatal damage to the enemy",
#else
{"冰冻之刃",		"敏捷的移动身体造成连续的损伤让敌人陷入混乱.",
#endif
60,		61,2,		120,0,
{1,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Frost_Wind,SKILL_FROST_WIND,SIN_SKILL_USE_RIGHT,Frost_Wind_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Fatal Mastery",		"Increases your Critical chance when permanently when using daggers",
#else
{"致命艺术",		"决斗之剑永久的必杀率增加.",
#endif
63,		0,0,		0,0,
{1,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Fatal_Mastery,SKILL_FATAL_MASTERY,SIN_SKILL_USE_NOT,0},

#ifdef ENGLISH_LANGUAGE
{"Pollute",		"Poisons all nearby enemies and decreases their health for a duration",
#else
{"瘟疫之刃",		"对周围的敌人带去毒属性攻击.",
#endif
66,		55,2,		120,0,
{1,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Pollute,SKILL_POLLUTED,SIN_SKILL_USE_RIGHT,Pollute_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Ninja Shadow",		"Moves fast to deal continuous damage to the enemy with shadows",
#else
{"影子闪击",		"快速移动,用自己的影子连续加以攻击.",
#endif
70,		51,2,		120,0,
{1,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Shadow,SKILL_PASTING_SHADOW,SIN_SKILL_USE_RIGHT,Shadow_UseMana},

// 5转

#ifdef ENGLISH_LANGUAGE
{"Shadow Bomb",		"Hides in the shadow and deals damage in an area by throwing a fire bomb on the ground",
#else
{"影子火焰",		"使用火焰对周围的敌人造成伤害.",
#endif
80,		65,2,		80,2,
{2,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Shadow_Bomb,SKILL_SHADOW_BOMB,SIN_SKILL_USE_RIGHT,Shadow_Bomb_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Rising Slash",			"Jumps on the spot and uses gravitational energy to perform a big slash to the enemy",
#else
{"地裂斩",			"使用两手拿剑对敌人造成损伤.",
#endif
83,		71,2,		110,1,
{2,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Rising_Shash,SKILL_RISING_SHASH,SIN_SKILL_USE_RIGHT,Rising_Shash_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Violent Stub",		"A distracting kick quickly followed by a powerful blade stab",
#else
{"猛龙摆尾",		"使用脚连续攻击敌人造成巨大伤害.",
#endif
86,		90,2,		110,1,
{2,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Violent_Stub,SKILL_VIOLENCE_STAB,SIN_SKILL_USE_RIGHT,Violent_Stub_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Shadow Storm",		"Summons a storm to deal massive damage",
#else
{"风暴之刃",		"飞到空中对敌人加以致命的伤害.",
#endif
90,		100,2,		120,1,
{2,0,0},			{sinWD1,0,0,0,0,0,0,0,0,0},
F_Shadow_Storm,SKILL_STORM,SIN_SKILL_USE_RIGHT,Shadow_Storm_UseMana},

// 萨满

#ifdef ENGLISH_LANGUAGE
{"Dark Bolt",		"Hits the enemy with an almighty bolt of dark magic created with sorcery",
#else
{"暗黑闪电",		"用以咒术生成的小黑团攻击敌人.",
#endif
10,		8,1,		80,2,
{0,0,0},			{sinWN1,0,0,0,0,0,0,0,0,0},
F_Dark_Bolt,SKILL_DARK_BOLT,SIN_SKILL_USE_ALL,Dark_Bolt_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Dark Wave",		"Performs a consecutive attack with almighty bolts of dark magic",
#else
{"暗黑波浪",		"向对方投出多个黑魔法球进行攻击.",
#endif
12,		19,1,		80,2,
{0,0,0},			{sinWN1,0,0,0,0,0,0,0,0,0},
F_Dark_Wave,SKILL_DARK_WAVE,SIN_SKILL_USE_ALL,Dark_Wave_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Inertia",		"Throws a curse onto the enemy to slow down the enemy",
#else
{"诅咒雷击",		"使用诅咒的力量让对方动作缓慢.",
#endif
14,		20,1,		110,2,
{0,0,0},			{sinWN1,0,0,0,0,0,0,0,0,0},
F_Inertia,SKILL_CURSE_LAZY,SIN_SKILL_USE_RIGHT,Inertia_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Inner Peace",		"Through mental training your maximum Mana capacity is increased permanently",
#else
{"内心平和",		"继承强大的精神元素永久提升魔法.",
#endif
17,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
F_Inner_Peace,SKILL_INNER_PEACE,SIN_SKILL_USE_NOT,0},

// 2转

#ifdef ENGLISH_LANGUAGE
{"Spiritual Flare",		"Uses powerful sorcery to deal damage to all enemies nearby in the area",
#else
{"精神咒术",		"以强力的咒术攻击对方.",
#endif
20,		21,1,		80,2,
{0,0,0},			{sinWN1,0,0,0,0,0,0,0,0,0},
F_Spiritual_Flare,SKILL_SPIRITUAL_FLARE,SIN_SKILL_USE_RIGHT,Spiritual_Flare_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Spiritual Manacle",		"Binds the target's soul with sorcery that results in a stun of the target",
#else
{"灵魂枷锁",		"以咒术的力量束缚对方的力量.",
#endif
23,		21,1,		110,2,
{0,0,0},			{sinWN1,0,0,0,0,0,0,0,0,0},
F_Spiritual_Manacle,SKILL_SPIRITUAL_MANACLE,SIN_SKILL_USE_RIGHT,Spiritual_Manacle_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Chasing Hunt",			"Increases your sight and gatherers nearby enemies close by pulling them towards you",
#else
{"猎取",			"把限定范围内的对象吸引过来.",
#endif
26,		27,1,		110,2,
{0,0,0},			{sinWN1,0,0,0,0,0,0,0,0,0},
F_Chasing_Hunt,SKILL_CHASING_HUNT,SIN_SKILL_USE_RIGHT,Chasing_Hunt_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Advent Migal",			"Calls forth Migal to temporarily increase the Attack Power of you and your party members",
#else
{"迈克尔",			"召唤迈克尔之神提升自身和对偶的攻击力.",
#endif
30,		28,1,		300,2,
{0,0,0},			{sinWN1,0,0,0,0,0,0,0,0,0},
F_Advent_Migal,SKILL_ADVENT_MIGAL,SIN_SKILL_USE_RIGHT,Advent_Migal_UseMana},

// 3转

#ifdef ENGLISH_LANGUAGE
{"Rainmaker",			"Invokes the God of rain to temporarily increase your Absorption and Attack Rating",
#else
{"祈雨师",			"减少魔法提升吸收能力.",
#endif
40,		31,1,		300,2,
{0,0,0},			{sinWN1,0,0,0,0,0,0,0,0,0},
F_Rainmaker,SKILL_RAIN_MAKER,SIN_SKILL_USE_RIGHT,Rainmaker_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Phantom Call",		"Calls a Cursed Phantom to deal massive damage to enemies nearby",
#else
{"陆地灵魂",		"使用收到诅咒的法珠对周围的敌人造成伤害.",
#endif
43,		33,1,		80,2,
{0,0,0},			{sinWN1,0,0,0,0,0,0,0,0,0},
F_Phantom_Call,SKILL_LAND_OF_GHOST,SIN_SKILL_USE_RIGHT,Phantom_Call_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Haunt",		"With help of the Phantom's strength a forceful blow damages the enemy and absorbs damage into health",
#else
{"鬼魂重回",		"借助法珠的力量使对方收到损伤吸取生命力.",
#endif
46,		35,1,		110,2,
{0,0,0},			{sinWN1,0,0,0,0,0,0,0,0,0},
F_Haunt,SKILL_HAUNT,SIN_SKILL_USE_RIGHT,Haunt_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Scratch",			"Deals damage through a fiercely scratch by a summoned Phantom Nail",
#else
{"抓破",			"用法珠之手使对方收到锋利的损伤.",
#endif
50,		32,1,		110,2,
{0,0,0},			{sinWN1,0,0,0,0,0,0,0,0,0},
F_Scratch,SKILL_SCRATCH,SIN_SKILL_USE_RIGHT,Scratch_UseMana},

// 4转

#ifdef ENGLISH_LANGUAGE
{"Crimson Knight",		"Through black magic and use of sorcery the Crimson Knight is summoned",
#else
{"嗜血之夜",		"使用咒术召唤嗜血之夜.",
#endif
60,		41,1,		320,0,
{1,0,0},			{sinWN1,0,0,0,0,0,0,0,0,0},
F_Crimson_Knight,SKILL_RECALL_BLOODYKNIGHT,SIN_SKILL_USE_RIGHT,Crimson_Knight_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Judgement",			"Deals a large potion of damage by shooting a powerful energy beam of darkness at the enemy",
#else
{"审判",			"发散暗黑之光攻击对方.",
#endif
63,		41,1,		120,0,
{1,0,0},			{sinWN1,0,0,0,0,0,0,0,0,0},
F_Judgement,SKILL_JUDGEMENT,SIN_SKILL_USE_RIGHT,Judgement_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Advent Midranda",		"Invokes Midranda to temporarily increase the Attack Speed of you and your party members",
#else
{"米德兰达",		"可以提升队员的攻击速度.",
#endif
66,		39,1,		320,0,
{1,0,0},			{sinWN1,0,0,0,0,0,0,0,0,0},
F_Advent_Midranda,SKILL_ADVENT_MIDRANDA,SIN_SKILL_USE_RIGHT,Advent_Midranda_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Mourning Pray",		"By using the sacred powers of Miranda and Migal you damage all nearby enemies",
#else
{"旭日东升",		"受到迈克尔和米德兰达的光波的特殊效果攻击周围对象.",
#endif
70,		47,1,		100,0,
{1,0,0},			{sinWN1,0,0,0,0,0,0,0,0,0},
F_Mourning_pray,SKILL_MOURNING_OF_PRAY,SIN_SKILL_USE_RIGHT,Mourning_Pray_UseMana},

// 5转

#ifdef ENGLISH_LANGUAGE
{"Creed",		"By the use of powerful sorcery you grant extra Mana and Stamina",
#else
{"咒术信仰",		"以强力的咒术使生命,魔法,耐力提升.",
#endif
80,		43,2,		320,0,
{2,0,0},			{sinWN1,0,0,0,0,0,0,0,0,0},
F_Creed,SKILL_CREED,SIN_SKILL_USE_RIGHT,Creed_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Press of Deity",		"Unleashes a hidden power that throws cursed damage to nearby enemies",
#else
{"诅咒之力",		"受到诅咒的召唤陨石对周围的敌人造成伤害.",
#endif
83,		47,2,		100,0,
{2,0,0},			{sinWN1,0,0,0,0,0,0,0,0,0},
F_Press,SKILL_PRESS_OF_DEITY,SIN_SKILL_USE_RIGHT,Press_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Phantom Nail",		"Calls upon the spirit of the earth to attack nearby enemies",
#else
{"死亡之爪",		"召唤沉睡的大地之爪来攻击敌人.",
#endif
89,		54,2,		100,0,
{2,0,0},			{sinWN1,0,0,0,0,0,0,0,0,0},
F_Phantom_Nail,SKILL_CHOSTY_NAIL,SIN_SKILL_USE_RIGHT,Phantom_Nail_UseMana},

#ifdef ENGLISH_LANGUAGE
{"Occult Life",		"Permanently increases your maximum health with the power of sorcery",
#else
{"高级再升",		"以强力的咒术增加生命值.",
#endif
90,		0,0,		0,0,
{2,0,0},			{sinWN1,0,0,0,0,0,0,0,0,0},
F_Occult_Life,SKILL_HIGH_REGENERATION,SIN_SKILL_USE_NOT,0},

#ifdef ENGLISH_LANGUAGE
{"Force Orb",			"Force Orb's give you the ability to upgrade your Attack Power",
#else
{"之力",			"使用后增加攻击力",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,SKILL_FORCE_ORB,0,0},

#ifdef ENGLISH_LANGUAGE
{"Crystal",			"Summoned Pet that supports you in Battle",
#else
{"水晶",			"召唤水晶来协助自己攻击",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,SKILL_CRYSTAL_ORB,0,0},

#ifdef ENGLISH_LANGUAGE
{"Trade Chat Timer",	"Time till you can announce another Trade message",
#else
{"时间计时器",		"当时间到了才可以行进另一个事件",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,SKILL_WARNING_TIME,0,0},

#ifdef ENGLISH_LANGUAGE
{"Quest",			"Hunt monsters!",
#else
{"任务",			"猎杀怪物!",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,CHANGE_JOB3_QUEST,0,0},

#ifdef ENGLISH_LANGUAGE
{"Quest",			"Hunt monsters!",
#else
{"任务",			"猎杀怪物!",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,CHANGE_ELEMENTARY_QUEST,0,0},

#ifdef ENGLISH_LANGUAGE
{"Absorption of Glory",		"+10 Absorb",
#else
{"祝福圣盾",		"在一个星期内增加吸收+20.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,CLANSKILL_ABSORB,0,0},

#ifdef ENGLISH_LANGUAGE
{"Power Siege",		"+10% Attack Power",
#else
{"祝福圣剑",		"在一个星期内增加15%的攻击力.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,CLANSKILL_ATTACK,0,0},

#ifdef ENGLISH_LANGUAGE
{"Evasion Adaption",		"+10% Evasion",
#else
{"祝福圣衣",		"在一个星期内增加闪避 20%.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,CLANSKILL_EVASION,0,0},

#ifdef ENGLISH_LANGUAGE
{"Atanasia",		"Makes you invincible for a while, but decrease your Attack Power by half",
#else
{"阿塔纳西娅",		"在瞬间内无敌攻击力降低为原来的1/2.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,SCROLL_INVULNERABILITY,0,0},

#ifdef ENGLISH_LANGUAGE
{"Deadly Edge",		"Increase Critical by 5%",
#else
{"必杀卷轴",		"攻击必杀率增加5%.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,SCROLL_CRITICAL,0,0},

#ifdef ENGLISH_LANGUAGE
{"Avail of Evasion",		"Increase Evasion by 5%",
#else
{"躲闪卷轴",		"额外闪避率增加5%.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,SCROLL_EVASION,0,0},

#ifdef ENGLISH_LANGUAGE
{"Defiance Stone",		"Increases absorption rate of Fire Crystal attacks",
#else
{"水晶纹章",		"吸收火水晶塔攻击力 50%的伤害.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,STONE_R_FIRECRYTAL,0,0},

#ifdef ENGLISH_LANGUAGE
{"Defiance Stone",		"Increases absorption rate of Ice Crystal attacks",
#else
{"水晶纹章",		"吸收冰水晶塔攻击力50%的伤害.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,STONE_R_ICECRYTAL,0,0},

#ifdef ENGLISH_LANGUAGE
{"Defiance Stone",		"Increases absorption rate of Lightning Crystal attacks",
#else
{"水晶纹章",		"吸收雷水晶塔攻击力50%的伤害.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,STONE_R_LINGHTINGCRYTAL,0,0},

#ifdef ENGLISH_LANGUAGE
{"Animosity Potion",	"+5% Damage Boost against Fighter",
#else
{"攻击纹章",		"对武士增加5%的攻击伤害.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,STONE_A_FIGHTER,0,0},

#ifdef ENGLISH_LANGUAGE
{"Animosity Potion",	"+5% Damage Boost against Mechanician",
#else
{"攻击纹章",		"对机械兵增加5%的攻击伤害.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,STONE_A_MECHANICIAN,0,0},

#ifdef ENGLISH_LANGUAGE
{"Animosity Potion",	"+5% Damage Boost against Pikeman",
#else
{"攻击纹章",		"对枪兵增加5%的攻击伤害.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,STONE_A_PIKEMAN,0,0},

#ifdef ENGLISH_LANGUAGE
{"Animosity Potion",	"+5% Damage Boost against Archer",
#else
{"攻击纹章",		"对弓箭手增加5%的攻击伤害.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,STONE_A_ARCHER,0,0},

#ifdef ENGLISH_LANGUAGE
{"Animosity Potion",	"+5% Damage Boost against Knight",
#else
{"攻击纹章",		"对游侠增加5%的攻击伤害.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,STONE_A_KNIGHT,0,0},

#ifdef ENGLISH_LANGUAGE
{"Animosity Potion",	"+5% Damage Boost against Atalanta",
#else
{"攻击纹章",		"对魔枪手增加5%的攻击伤害.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,STONE_A_ATALANTA,0,0},

#ifdef ENGLISH_LANGUAGE
{"Animosity Potion",	"+5% Damage Boost against Magician",
#else
{"攻击纹章",		"对魔法师增加5%的攻击伤害.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,STONE_A_MAGICIAN,0,0},

#ifdef ENGLISH_LANGUAGE
{"Animosity Potion",	"+5% Damage Boost against Priestess",
#else
{"攻击纹章",		"对祭司增加5%的攻击伤害.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,STONE_A_PRIESTESS,0,0},

#ifdef ENGLISH_LANGUAGE
{"Animosity Potion",	"+5% Damage Boost against Assassin",
#else
{"攻击纹章",		"对刺客增加5%的攻击伤害.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,STONE_A_ASSASSIN,0,0},

#ifdef ENGLISH_LANGUAGE
{"Animosity Potion",	"+5% Damage Boost against Shaman",
#else
{"攻击纹章",		"对萨满增加5%的攻击伤害.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,STONE_A_SAMAN,0,0},

#ifdef ENGLISH_LANGUAGE
{"Eternal Life",	"Makes your invincible for a while, decreases your attack power by half",
#else
{"永恒生命",		"瞬间成为无敌状态 攻击力降低为原来的1/2.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,SCROLL_P_INVULNERABILITY,0,0},

#ifdef ENGLISH_LANGUAGE
{"Fatal Edge",		"Increases your Critical Attack rating by 5%.",
#else
{"暴怒卷轴",		"攻击必杀率增加15%.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,SCROLL_P_CRITICAL,0,0},

#ifdef ENGLISH_LANGUAGE
{"Avert Scroll",		"Increases your Evade Chance by 15%.",
#else
{"闪避卷轴",		"额外闪避率增加15%.",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,SCROLL_P_EVASION,0,0},

#ifdef ENGLISH_LANGUAGE
{"Booster life",	"+15% bonus Health",
#else
{"生命上限",		"提高 15%生命上限",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,BOOSTER_ITEM_LIFE,0,0},

#ifdef ENGLISH_LANGUAGE
{"Mana Booster",	"+15% bonus Mana",
#else
{"魔法上限",		"提高 15%魔法上限",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,BOOSTER_ITEM_MANA,0,0},

#ifdef ENGLISH_LANGUAGE
{"Stamina Booster",	"+15% bonus Stamina",
#else
{"耐力上限",		"提高 15%耐力上限",
#endif
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0,0,0},
NULL,BOOSTER_ITEM_STAMINA,0,0},