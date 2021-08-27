#include "StdAfx.h"
#include "..\\skillsub.h"

cSKILL	cSkill;
sUSESKILL sinSkill;
sSKILL  *pUseSkill;
sSKILL  ContinueSkill[SIN_MAX_SKILL_LIST];
sSKILL  TempContinueSkill[SIN_MAX_SKILL_LIST];
int SkillCountTime2[SIN_MAX_USE_SKILL] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
int ContinueSkillMouseIndex = 0;

sSKILL *pMasterSkill;

sSKILLPASSIVE sSkillPassive;

int ShowSkillUpInfo = 0;
int  SkillMasterOkFlag[2] = { 0,0 };
int  SkillMasterFlag = 0;

int SkillMasteryShowFlag = 0;
char szUseSkillMastery[32];
POINT UseSkillMasteryPosi = { 0,0 };

int MatForceOrb[16] = { 0 };
//int MatCrystalOrb[MAX_CRYSTAL] = { 0 };
int MatBillingMagicForceOrb[3] = { 0 };
int Mat_BoosterItem[9] = { 0 };
int nMat_SkillDelayItem[3] = { 0 };
int MatQuestTimer = 0;
int MatWarning = 0;

POINT SkillUpInfo = { 13,21 };
POINT SkillUpInfoPosi = { 90,100 };

int     SkillInfoLineCnt = 0;

int     SkillInfoShowFlag = 0;
POINT	SkillInfoBoxPosi = { 0,0 };
POINT   SkillInfoTextPosi = { 0,0 };
POINT   SkillBoxSize = { 0,0 };


char    szSkillInfoBuff[5000];
char    szSkillMasterInfoBuff[5000];

char    szSkillInfoBuff2[5000];
char    szSkillMasterInfoBuff2[5000];

int     SkillDocLineCnt[6] = { 0,0,0,0,0,0 };
int     SkillUseWeaponClass = 0;
int     NextSkillLevelLine = 0;

int ShowSkillClose = 0;
int SkillButtonIndex = 0;
int Skill4ButtonIndex = 0;

int DownButtonUseShorKey = 0;

int DownButtonIndex = 0;
int LDownButtonIndex = 0;
int RDownButtonIndex = 0;

DWORD sinSkillBoxColor = 0;

int ChangeJobSkillPlus = 0;
int UseSkillIndex[2] = { 0,0 };
int SelectInterSkill = 0;

#define	NORMAL_SKILL_INDEX		14
#define MAX_USE_SKILL_POINT		10

#define SIN_MOUSE_POSI_LEFT		1
#define SIN_MOUSE_POSI_RIGHT	2


int   SkillIconIndex[10] = { 0,0,0,0,0,0,0,0,0,0 };
POINT SkillIconPosi = { 0,0 };
int   SkillInconCnt = 0;


int GageLenght[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

DWORD ClearSkillCODE = 0;
POINT ClearSkillButtonPosi = { 0,0 };

int SetT_Of_ValhallaFlag = 0;
int SetT_Of_ValhallaFlag2 = 0;
int SetT_Of_ValhallaLV = 0;

int SetH_Of_ValhallaLV = 0;
int SetT_Of_ValhallaPOINT = 0;

int MatCircleIcon = 0;

sSKILL sSkill[SIN_MAX_SKILL] =
{
	{"普通攻击 "		,SKILL_NORMAL_ATTACK			,"Skill_Normal"		,						},

	//////////////机械技能
{"极光护盾"			,SKILL_EXTREME_SHIELD			,"TM10 Ex_shield"	,"Mc1_E_SHIELD.tga"		},
{"机械榴弹"			,SKILL_MECHANIC_BOMB			,"TM12 M_bomb"								},
{"毒之防御"			,SKILL_POISON_ATTRIBUTE			,"TM14 P_attribute"							},
{"灵光护体"			,SKILL_PHYSICAL_ABSORB			,"TM17 Ph_absorb"	,"Mc1_P_ABSORB.tga"		},

{"破碎巨击"			,SKILL_GREAT_SMASH				,"TM20 G_Smash"								},
{"改良专家 "		,SKILL_MAXIMIZE					,"TM23 Maximize"	,"Mc2_MAXIMIZE.tga"		},
{"灵光飞扬"			,SKILL_AUTOMATION				,"TM26 Automation"	,"Mc2_AUTOMATION.tga"	},
{"火花电场"			,SKILL_SPARK					,"TM30 Spark"},

{"金属重甲"			,SKILL_METAL_ARMOR				,"TM40 M_Armor"		,"Mc3_M_ARMOR.tga"		},
{"星光灭绝"			,SKILL_GRAND_SMASH				,"TM43 Grand_Smash"							},
{"优化专家"			,SKILL_MECHANIC_WEAPON			,"TM44 M_Weapon"							},
{"防御电波"			,SKILL_SPARK_SHIELD				,"TM50 S_Shield"	,"Mc3_S_SHIELD.tga"		},

{"雷霆冲击"			,SKILL_IMPULSION				,"TM60 Impulsion"							},
{"威慑怒吼"			,SKILL_COMPULSION				,"TM63 Compulsion"	,"Mc4_COMPULSION.tga"	},
{"磁性球体"			,SKILL_MAGNETIC_SPHERE			,"TM66 M_Sphere"	,"Mc4_M_SPHERE.tga"		},
{"终极机械"			,SKILL_METAL_GOLEM				,"TM70 M_Golem"		,"Mc4_M_GOLEM.tga"		},

{"霹雳旋风"			,SKILL_LANDMINNING				,"TM80 landminning"							},
{"快速打击"			,SKILL_H_SONIC					,"TM83 H_Sonic"		,"Me5_H_Sonic.tga"		},
{"究极之刃"			,SKILL_R_SMASH					,"TM86 R_Smash"								},
{"战神祝福"			,SKILL_P_ENHENCE				,"TM90 P_Enhence"	,"Me5_P_Enhence.tga"	},

////////////// 武士技能
{"格斗之术"			,SKILL_MELEE_MASTERY			,"TF10 M_mastery"							},
{"火之防御"			,SKILL_FIRE_ATTRIBUTE			,"TF12 F_attribute"							},
{"绝地暴走"			,SKILL_RAVING					,"TF14 raving"								},
{"精准之击"			,SKILL_IMPACT					,"TF17 impact"								},

{"威力冲击"			,SKILL_TRIPLE_IMPACT			,"TF20 T_Impact"							},
{"致命回旋"			,SKILL_BRUTAL_SWING				,"TF23 B_Swing"								},
{"极地怒吼"			,SKILL_ROAR						,"TF26 Roar"								},
{"战神之怒"			,SKILL_RAGE_OF_ZECRAM			,"TF30 R_Zecram"							},

{"会心一击"			,SKILL_CONCENTRATION			,"TF40 Concentration","Ft3_CONCENTRATION.tga"},
{"复仇连击"			,SKILL_AVANGING_CRASH			,"TF43 A_Crash"								},
{"刺杀之斧"			,SKILL_SWIFT_AXE				,"TF46 S_Axe"		,"Ft3_S_AXE.tga"		},
{"挫骨扬灰"			,SKILL_BONE_CRASH				,"TF50 B_Crash"								},

{"破坏之击"			,SKILL_DETORYER					,"TF60 Destoryer"							},
{"疯狂怒吼"		    ,SKILL_BERSERKER				,"TF63 Berserker"	,"Ft4_BERSERKER.tga"	},
{"飓风袭击"			,SKILL_CYCLONE_STRIKE			,"TF66 C_Strike"							},
{"健康专家"			,SKILL_BOOST_HEALTH				,"TF70 B_Health"							},

{"狂暴怒斩"			,SKILL_D_HIT					,"TF80 D_Hit"								},
{"狂野冲击"		    ,SKILL_P_DASH					,"TF83 P_Dash"								},
{"回旋斩击"			,SKILL_M_BLOW					,"TF86 M_Blow"								},
{"众神之怒"			,SKILL_B_BERSERKER				,"TF90 B_Berserker"	,"Ft5_B_Berserker.tga"	},

////////////// 枪兵技能
{"龙卷枪风"   		,SKILL_PIKE_WIND				,"TP10 P_wind"								},
{"冰之防御"			,SKILL_ICE_ATTRIBUTE			,"TP12 I_attribute"							},
{"致命打击"			,SKILL_CRITICAL_HIT				,"TP14 Cri_hit"								},
{"霹雳一击"			,SKILL_JUMPING_CRASH			,"TP17 J_Crash"								},

{"大地之枪"			,SKILL_GROUND_PIKE				,"TP20 G_Pike"								},
{"枪之飓风"			,SKILL_TORNADO					,"TP23 Tornado"								},
{"躲避专家"			,SKILL_WEAPONE_DEFENCE_MASTERY	,"TP26 W_D_Mastery"							},
{"无限力枪" 		,SKILL_EXPANSION				,"TP30 Expasion"							},

{"灵蛇标枪"			,SKILL_VENOM_SPEAR				,"TP40 V_Spear"								},
{"隐暗之术"			,SKILL_VANISH					,"TP43 Vanish"		,"Pk3_VANISH.tga"		},
{"会心之枪"			,SKILL_CRITICAL_MASTERY			,"TP46 C_Mastery"							},
{"链骑之枪" 		,SKILL_CHAIN_LANCE				,"TP50 C_Lance"								},

{"暗杀之眼"			,SKILL_ASSASSIN_EYE				,"TP60 A_Eye"		,"Pk4_A_EYE.tga"		},
{"转换打击"			,SKILL_CHARGING_STRIKE			,"TP63 C_Strike"							},
{"影隐之遁"         ,SKILL_VAGUE					,"TP66 Vague"		,"Pk4_VAGUE.tga"		},
{"宇宙幻影"			,SKILL_SHADOW_MASTER			,"TP70 S_Master"							},

{"回旋打击"			,SKILL_D_REAPER					,"TP80 D_Reaper"							},
{"地枪奇袭"			,SKILL_F_SPEAR					,"TP83 F_Spear"								},
{"潜能激发"         ,SKILL_AMPLIFIED				,"TP86 Amplified"	,"Pk5_Amplified.tga"	},
{"旋风之枪"			,SKILL_SS_ATTACK				,"TP90 SS_Attack"							},

////////////// 弓手 技能
{"侦察之鹰"			,SKILL_SCOUT_HAWK				,"TA10 S_hawk"		,"Ac1_S_HAWK.tga"		},
{"强力之箭"			,SKILL_SHOOTING_MASTERY			,"TA12 S_mastery"							},
{"疾风之箭"			,SKILL_WIND_ARROW				,"TA14 W_arrow"								},
{"夺命之箭"			,SKILL_PERFECT_AIM				,"TA17 P_aim"								},

{"射神之眼"			,SKILL_DIONS_EYE				,"TA20 D_Eye"								},
{"灵魂之鹰"			,SKILL_FALCON					,"TA23 Falcon"		,"Ac2_FALCON.tga"		},
{"狂暴火箭"			,SKILL_ARROW_OF_RAGE			,"TA26 A_Rage"								},
{"雪崩之箭"			,SKILL_AVALANCHE				,"TA30 Avalanchie"							},

{"元素攻击"			,SKILL_ELEMENTAL_SHOT			,"TA40 E_Shot"								},
{"黄金猎鹰"			,SKILL_GOLDEN_FALCON			,"TA43 G_Falcon"	,"Ac3_G_FALCON.tga"		},
{"爆裂之箭"			,SKILL_BOMB_SHOT				,"TA46 B_Shot"								},
{"惯穿之箭"			,SKILL_PERFORATION				,"TA50 Perforation"							},

{"召唤雪狼"			,SKILL_RECALL_WOLVERIN			,"TA60 R_Wolverin"	,"Ac4_R_WOLVERIN.tga"	},
{"躲避大师"			,SKILL_EVASION_MASTERY			,"TA63 E_Mastery"							},
{"绯凰绝炎"         ,SKILL_PHOENIX_SHOT				,"TA66 P_Shot"								},
{"自然之光"			,SKILL_FORCE_OF_NATURE			,"TA70 F_O_Nature"	,"Ac4_F_O_NATURE.tga"	},

{"回旋之舞"			,SKILL_E_SHOT					,"TA80 E_Shot"								},
{"玄光之箭"			,SKILL_S_ROPE					,"TA83 S_Rope"								},
{"飓风之箭"         ,SKILL_N_SPLASH					,"TA86 N_Splash"							},
{"复仇箭雨"			,SKILL_C_TRAP					,"TA90 C_Trap"								},

///////////////// 游侠技能
{"魔神剑"			,SKILL_SWORD_BLAST				,"MN10 S_Blast"								},
{"圣光护体"			,SKILL_HOLY_BODY				,"MN12 H_Body"		,"Kt1_H_BODY.tga"		},
{"超能体训"			,SKILL_PHYSICAL_TRANING			,"MN14 P_Traning"							},
{"双重爆击"		 	,SKILL_DOUBLE_CRASH				,"MN17 D_Crash"								},

{"神力重击"			,SKILL_HOLY_VALOR				,"MN20 H_Valor"		,"Kt2_H_VALOR.tga"		},
{"狂躁挥舞"	        ,SKILL_BRANDISH					,"MN23 Brandish"							},
{"一雾银"	        ,SKILL_PIERCING					,"MN26 Piercing"							},
{"天佑神铠"			,SKILL_DRASTIC_SPIRIT			,"MN30 D_Spirit"	,"Kt2_D_SPIRIT.tga"		},

{"精剑之术"			,SKILL_SWORD_MASTERY			,"MN40 S_Mastery"							},
{"圣灵之吸"			,SKILL_DIVINE_INHALATION		,"MN43 D_Inhalation","Kt3_D_INHALATION.tga"	},
{"圣剡之光"			,SKILL_HOLY_INCANTATION			,"MN46 H_Incantation"						},
{"圣光十字"			,SKILL_GRAND_CROSS				,"MN50 G_Cross"								},

{"真魔神剑"			,SKILL_SWORD_OF_JUSTICE			,"MN60 S_O_Justice"							},
{"敬神之盾"			,SKILL_GODLY_SHIELD				,"MN63 G_Shield"	,"Kt4_G_SHIELD.tga"		},
{"上帝祝福"			,SKILL_GOD_BLESS				,"MN66 G_Bless"		,"Kt4_G_BLESS.tga"		},
{"刹剧荒舞"			,SKILL_DIVINE_PIERCING			,"MN70 D_Piercing"							},

{"神力冲刺"			,SKILL_S_BREAKER				,"MN80 S_Breaker"							},
{"升龙重击"			,SKILL_C_MOON					,"MN83 C_Moon"								},
{"上帝重击"			,SKILL_S_BLADE					,"MN86 S_Blade"								},
{"死亡宣告"			,SKILL_H_BENEDIC				,"MN90 H_Benedic"	,"Kn5_H_Benedic.tga"	},

///////////////// 魔枪手技能
{"美杜莎盾"			,SKILL_SHIELD_STRIKE			,"MA10 S_Strike"							},
{"含沙射影 "		,SKILL_FARINA					,"MA12 Farina"								},
{"魔力神枪"			,SKILL_THROWING_MASTERY			,"MA14 T_Mastery"							},
{"精神之枪"			,SKILL_VIGOR_SPEAR				,"MA17 V_Spear"								},

{"追命劲风"			,SKILL_WINDY					,"MA20 Windy"		,"At2_WINDY.tga"		},
{"螺旋飞标"			,SKILL_TWIST_JAVELIN			,"MA23 T_Javelin"							},
{"灵魂吞噬"			,SKILL_SOUL_SUCKER				,"MA26 S_Sucker"							},
{"火焰烈枪"			,SKILL_FIRE_JAVELIN				,"MA30 F_Javelin"							},

{"追风之枪"			,SKILL_SPLIT_JAVELIN			,"MA40 Split_Javelin"						},
{"战栗咆哮"			,SKILL_TRIUMPH_OF_VALHALLA		,"MA43 T_Of_Valhalla","At3_T_O_VALHALLA.tga"},
{"光猎之枪"			,SKILL_LIGHTNING_JAVELIN		,"MA46 L_Javelin"							},
{"暴风狂标"			,SKILL_STORM_JAVELIN			,"MA50 Storm_Javelin"						},

{"瓦尔哈拉之光"		,SKILL_HALL_OF_VALHALLA			,"MA60 H_O_Valhalla","At4_H_O_VALHALLA.tga"	},
{"十字怒击"			,SKILL_X_RAGE					,"MA63 X_Rage"								},
{"霜冻标枪"			,SKILL_FROST_JAVELIN			,"MA66 F_Javelin"	,"At4_F_JAVELIN.tga"	},
{"狂风爆裂"			,SKILL_VENGEANCE				,"MA70 Vengeance"							},

{"轻舞飞扬"			,SKILL_TALARIA					,"MA80 Talaria"		,"At5_TALARIA.tga"		},
{"星雨标枪"			,SKILL_G_COUP					,"MA83 G_Coup"								},
{"笨笨熊"			,SKILL_S_ARCUDA					,"MA86 S_Arcuda"	,"At5_S_ARCUDA.tga"		},
{"烈焰突袭"			,SKILL_S_FEAR					,"MA90 S_Fear"								},


///////////////// 祭司技能
{"治愈之术"			,SKILL_HEALING					,"MP10 Healing"								},
{"圣光电球"			,SKILL_HOLY_BOLT				,"MP12 HolyBolt"							},
{"光芒四射"			,SKILL_MULTISPARK				,"MP14 M_Spark"								},
{"意念之术"			,SKILL_HOLY_MIND				,"MP17 HolyMind"							},

{"曙光耀灵"			,SKILL_MEDITATION				,"MP20 Meditation"							},
{"神之雷电"			,SKILL_DIVINE_LIGHTNING			,"MP23 D_Lightning"							},
{"神圣反射"			,SKILL_HOLY_REFLECTION			,"MP26 H_Reflection","Pr2_H_REFLECTION.tga"	},
{"圣洁之光"			,SKILL_GRAND_HEALING			,"MP30 G_Healing"							},

{"火影双重"		    ,SKILL_VIGOR_BALL				,"MP40 V_Ball"								},
{"回生之术"			,SKILL_RESURRECTION				,"MP43 Resurrection"						},
{"圣光之咒"			,SKILL_EXTINCTION				,"MP46 Extinction"							},
{"神圣之光"			,SKILL_VIRTUAL_LIFE				,"MP50 V_Life"		,"Pr3_V_LIFE.tga"		},

{"冰霜噬月"			,SKILL_GLACIAL_SPIKE			,"MP60 G_Spike"								},
{"再生领域"			,SKILL_REGENERATION_FIELD		,"MP63 R_Field"		,"Pr4_R_FIELD.tga"		},
{"天雷之怒"			,SKILL_CHAIN_LIGHTNING			,"MP66 C_Lightning"							},
{"神圣天使"			,SKILL_SUMMON_MUSPELL			,"MP70 S_Muspell"	,"Pr4_S_MUSPELL.tga"	},

{"神圣电波"			,SKILL_S_IMPACT					,"MP80 S_Impact"							},
{"神之冰刃"			,SKILL_P_ICE					,"MP83 P_Ice"								},
{"光明天使"			,SKILL_S_PRMIEL					,"MP86 S_Meteo"								},
{"仙女散花"			,SKILL_B_KRISHNA				,"MP90 B_Krishna"	,"Pr5_B_Krishna.tga"	},

//魔法师技能
{"魔力转化"			,SKILL_AGONY					,"MM10 Agony"								},
{"火箭之术"			,SKILL_FIRE_BOLT				,"MM12 FireBolt"							},
{"集合之术"			,SKILL_ZENITH					,"MM14 Zenith"		,"Mg1_ZENITH.tga"		},
{"火球之术"			,SKILL_FIRE_BALL				,"MM17 FireBall"							},

{"控制意念"			,SKILL_MENTAL_MASTERY			,"MM20 M_Mastery"							},
{"龙卷海风"			,SKILL_WATORNADO				,"MM23 Watornado"							},
{"元素之术"			,SKILL_ENCHANT_WEAPON			,"MM26 E_Weapon"	,"Mg2_E_WEAPON.tga"		},
{"冥亡之光"			,SKILL_DEAD_RAY  				,"MM30 D_Ray"},

{"魔法守护"			,SKILL_ENERGY_SHIELD			,"MM40 E_Shield"	,"Mg3_E_SHIELD.tga"		},
{"地裂冲击"			,SKILL_DIASTROPHISM				,"MM43 Diastrophism"						},
{"灵魂召唤"			,SKILL_SPIRIT_ELEMENTAL			,"MM46 S_Elemental"	,"Mg3_S_ELEMENTAL.tga"	},
{"元素之剑"			,SKILL_DANCING_SWORD  			,"MM50 D_Sword"		,"Mg3_D_SWORD.tga"		},

{"伊夫列特"			,SKILL_FIRE_ELEMENTAL			,"MM60 F_Elemental"	,"Mg4_F_ELEMENTAL.tga"	},
{"火焰波动"			,SKILL_FLAME_WAVE				,"MM63 F_Wave"},
{"空间扭曲"			,SKILL_DISTORTION				,"MM66 Distortion"	,"Mg4_DISTORTION.tga"	},
{"陨石召唤"		    ,SKILL_M_METEO					,"MM70 Meteo"},

{"流星火雨"			,SKILL_SILRAPHIM				,"MM80 Silraphim"							},
{"缩小之术"			,SKILL_V_TENUS					,"MM83 V_Tenus"								},
{"神圣洗礼"			,SKILL_P_IGNIS					,"MM86 P_Ignis"								},
{"圣光法阵"		    ,SKILL_T_ANIMA					,"MM90 T_Anima"		,"Ma5_T_Anima.tga"		},

//刺客技能
{"刺击"				,SKILL_STRINGER 				,"TA10 Stingger"							},
{"闪击"				,SKILL_RUNNING_HIT				,"TA12 R_Hit"								},
{"强化攻击"			,SKILL_SWORDMASTERY				,"TA14 D_Mastery"							},
{"弱点攻击"			,SKILL_WISP						,"TA17 Wisp"		,"As1_WISP.tga"			},

{"毒牙连击"			,SKILL_VENOM_THORN				,"TA20 V_Throne"							},
{"敏捷之力"			,SKILL_ALAS						,"TA23 Alas"		,"As2_ALAS.tga"			},
{"灵魂震撼"			,SKILL_SOUL_SHOCK				,"TA26 S_Shock"								},
{"攻击大师"			,SKILL_ATTACK_MASTERY  			,"TA30 A_Mastery"							},

{"飞剑之舞"			,SKILL_SORE_SWORD				,"TA40 S_Sword"								},
{"跳斩"				,SKILL_BEAT_UP					,"TA43 B_Up"								},
{"敏捷大师"			,SKILL_INPES					,"TA46 Inpes"		,"As3_INPES.tga"		},
{"致盲"				,SKILL_BLIND  					,"TA50 Blind"		,"As3_BLIND.tga"		},

{"冰冻之刃"			,SKILL_FROST_WIND				,"TA60 F_Wind"								},
{"致命艺术"			,SKILL_FATAL_MASTERY			,"TA63 F_Mastery"							},
{"瘟疫之刃"			,SKILL_POLLUTED					,"TA66 Polluted"							},
{"影子闪击"		    ,SKILL_PASTING_SHADOW			,"TA70 P_Shadow"							},

{"影子火焰"			,SKILL_SHADOW_BOMB				,"TS80 J_Bomb"								},
{"地裂斩"			,SKILL_RISING_SHASH				,"TS83 R_Slash"								},
{"猛龙摆尾"			,SKILL_VIOLENCE_STAB			,"TS86 V_Stab"								},
{"风暴之刃"		    ,SKILL_STORM					,"TS90 Storm"								},

//萨满技能
{"暗黑闪电"			,SKILL_DARK_BOLT				,"MS10 Darkbolt"							},
{"暗黑波浪"			,SKILL_DARK_WAVE				,"MS12 Darkwave"							},
{"诅咒雷击"			,SKILL_CURSE_LAZY				,"MS14 Curselazy"							},
{"内心平和"			,SKILL_INNER_PEACE				,"MS17 I_peace"								},

{"精神咒术"			,SKILL_SPIRITUAL_FLARE			,"MS20 S_Flare"								},
{"灵魂枷锁"			,SKILL_SPIRITUAL_MANACLE		,"MS23 S_Manacle"							},
{"猎取"				,SKILL_CHASING_HUNT				,"MS26 C_Hunt"		,"Sh2_C_HUNT.tga"		},
{"迈克尔"			,SKILL_ADVENT_MIGAL				,"MS30 A_Migal"		,"Sh2_A_MIGAL.tga"		},

{"祈雨师"			,SKILL_RAIN_MAKER				,"MS40 R_Maker"		,"Sh3_R_MAKER.tga"		},
{"陆地灵魂"			,SKILL_LAND_OF_GHOST			,"MS43 L_Ghost"								},
{"鬼魂重回"			,SKILL_HAUNT					,"MS46 Haunt"								},
{"抓破"				,SKILL_SCRATCH  				,"MS50 Scratch"								},

{"嗜血之夜"			,SKILL_RECALL_BLOODYKNIGHT		,"MS60 R_Knight"	,"Sh4_R_KNIGHT.tga"		},
{"审判"				,SKILL_JUDGEMENT				,"MS63 Judge"								},
{"米德兰达"			,SKILL_ADVENT_MIDRANDA			,"MS66 A_Midranda"	,"Sh4_A_MIDRANDA.tga"	},
{"旭日东升"		    ,SKILL_MOURNING_OF_PRAY			,"MS70 M_pray"								},

{"咒术信仰"			,SKILL_CREED					,"MS80 Creed"		,"Sh5_CREED.tga"		},
{"诅咒之力"			,SKILL_PRESS_OF_DEITY			,"MS83 P_Deity"								},
{"死亡之爪"			,SKILL_CHOSTY_NAIL				,"MS86 G_Nail"								},
{"高级再升"		    ,SKILL_HIGH_REGENERATION		,"MS90 H_Regene"							},

{"祝福圣盾"			,CLANSKILL_ABSORB				,""					,"wa1-1.tga"			},
{"祝福圣剑"			,CLANSKILL_ATTACK				,""					,"wa1-3.tga"			},
{"祝福圣衣"			,CLANSKILL_EVASION				,""					,"wa1-2.tga"			},

{"酒鸥唱矫酒"		,SCROLL_INVULNERABILITY			,""					,"S_Ath.tga"			},
{"单甸府 俊瘤"		,SCROLL_CRITICAL				,""					,"S_Dea.tga"			},
{"绢海老 坷宏 "		,SCROLL_EVASION					,""					,"S_Eva.tga"			},
{"叼颇捞攫胶 胶沛"	,STONE_R_FIRECRYTAL				,""					,"F_C_M.tga"			},
{"叼颇捞攫胶 胶沛"	,STONE_R_ICECRYTAL				,""					,"I_C_M.tga"			},
{"叼颇捞攫胶 胶沛"	,STONE_R_LINGHTINGCRYTAL		,""					,"L_C_M.tga"			},
{"付捞飘 胶沛"		,STONE_A_FIGHTER				,""					,"Ft_R.tga"				},
{"付捞飘 胶沛"		,STONE_A_MECHANICIAN			,""					,"Mc_R.tga"				},
{"付捞飘 胶沛"		,STONE_A_PIKEMAN				,""					,"Pk_R.tga"				},
{"付捞飘 胶沛"		,STONE_A_ARCHER					,""					,"Ac_R.tga"				},
{"付捞飘 胶沛"		,STONE_A_KNIGHT					,""					,"Kt_R.tga"				},
{"付捞飘 胶沛"		,STONE_A_ATALANTA				,""					,"At_R.tga"				},
{"付捞飘 胶沛"		,STONE_A_MAGICIAN				,""					,"Mg_R.tga"				},
{"付捞飘 胶沛"		,STONE_A_PRIESTESS				,""					,"Pt_R.tga"				},
{"付捞飘 胶沛"		,STONE_A_ASSASSIN				,""					,"As_R.tga"				},
{"付捞飘 胶沛"		,STONE_A_SAMAN					,""					,"Sh_R.tga"				},

{"捞磐澄 扼捞橇"	,SCROLL_P_INVULNERABILITY		,""					,"S_Ath.tga"			},
{"其捞撇 俊瘤"		,SCROLL_P_CRITICAL				,""					,"S_Dea.tga"			},
{"绢滚飘 胶农费"	,SCROLL_P_EVASION				,""					,"S_Eva.tga"			},

{"生命上限"			,BOOSTER_ITEM_LIFE				,""					,"Booster_01.tga"		},
{"魔法上限"			,BOOSTER_ITEM_MANA				,""					,"Booster_02.tga"		},
{"耐力上限"			,BOOSTER_ITEM_STAMINA			,""					,"Booster_03.tga"		},

{"技能速度"			,SKILLDELAY_ITEM_LIFE			,""					,"Booster_01.tga"		},
};


sSKILLBOX	sSkillBox[SIN_MAX_SKILLBOX] =
{
	{{142		,537	,142 + 49		,537 + 46}},												//普通

	{{27 - 10		,502	,27 + 49 - 10	,502 + 46},{27 + 47 - 10	,502 + 5	,27 + 47 + 5 - 10		,502 + 40}},	// 1转
	{{67 - 10		,546	,67 + 49 - 10	,546 + 46},{67 + 47 - 10	,546 + 5	,67 + 47 + 5 - 10		,546 + 40}},
	{{77 - 10		,466	,77 + 49 - 10	,466 + 46},{77 + 47 - 10	,466 + 5	,77 + 47 + 5 - 10		,466 + 40}},
	{{137 - 10	,476	,137 + 49 - 10	,476 + 46},{137 + 47 - 10	,476 + 5	,137 + 47 + 5 - 10	,476 + 40}},

	{{212 - 15	,466	,212 + 49 - 15	,466 + 46},{212 + 47 - 15	,466 + 5	,212 + 47 + 5 - 15	,466 + 40}},	// 2转
	{{232 - 15	,516	,232 + 49 - 15	,516 + 46},{232 + 47 - 15	,516 + 5	,232 + 47 + 5 - 15	,516 + 40}},
	{{272 - 15	,466	,272 + 49 - 15	,466 + 46},{272 + 47 - 15	,466 + 5	,272 + 47 + 5 - 15	,466 + 40}},
	{{332		,466	,332 + 49		,466 + 46},{332 + 47	,466 + 5	,332 + 47 + 5		,466 + 40}},

	{{402		,476	,402 + 49		,476 + 46},{402 + 47	,476 + 5	,402 + 47 + 5		,476 + 40}},	// 3转
	{{472		,456	,472 + 49		,456 + 46},{472 + 47	,456 + 5	,472 + 47 + 5		,456 + 40}},
	{{512		,506	,512 + 49		,506 + 46},{512 + 47	,506 + 5	,512 + 47 + 5		,506 + 40}},
	{{532		,456	,532 + 49		,456 + 46},{532 + 47	,456 + 5	,532 + 47 + 5		,456 + 40}},

	{{602		,481	,602 + 49		,481 + 46},{602 + 47	,481 + 5	,602 + 47 + 5		,481 + 40}},	// 4转
	{{662		,511	,662 + 49		,511 + 46},{662 + 47	,511 + 5	,662 + 47 + 5		,511 + 40}},
	{{681		,461	,681 + 49		,461 + 46},{681 + 47	,461 + 5	,681 + 47 + 5		,461 + 40}},
	{{722		,511	,722 + 49		,511 + 46},{722 + 47	,511 + 5	,722 + 47 + 5		,511 + 40}},

	{{27 - 10		,502	,27 + 49 - 10	,502 + 46},{27 + 47 - 10	,502 + 5	,27 + 47 + 5 - 10		,502 + 40}},	// 5转
	{{67 - 10		,546	,67 + 49 - 10	,546 + 46},{67 + 47 - 10	,546 + 5	,67 + 47 + 5 - 10		,546 + 40}},
	{{77 - 10		,466	,77 + 49 - 10	,466 + 46},{77 + 47 - 10	,466 + 5	,77 + 47 + 5 - 10		,466 + 40}},
	{{137 - 10	,476	,137 + 49 - 10	,476 + 46},{137 + 47 - 10	,476 + 5	,137 + 47 + 5 - 10	,476 + 40}},
};


sSKILLBOX sLeftRightSkill[2] =
{
	{{349	,541,349 + 49,541 + 46},{349,558,349 + 5,558 + 35}},
	{{401 + 2	,541,401 + 49,541 + 46},{446,558,446 + 5,558 + 35}},

};

int SkillTitle[5][2] =
{
	{85	,438 - 4},
	{280,438 - 4},
	{470,438 - 9},
	{675,438 - 4},
	{85	,438 - 4},

};

int SkillMain2OpenFlag = 0;
int SkillMain2ButtonFlag[2] = { 0,0 };

int Skill4MasterFlag = 0;

int MonsterDamageLine = 0;
int ChainDamageLine = 0;
int MatSkillIconBackGround = 0;

cSKILL::cSKILL()
{
	memset(&ContinueSkill, 0, sizeof(sSKILL)*SIN_MAX_SKILL_LIST);
}
cSKILL::~cSKILL()
{

}


int CheckVirtualLifeTime = 0;
int CheckBoosterLifeTime = 0;
int CheckVirtualManaTime = 0;
int CheckVirtualStaminaTime = 0;
int CheckSkillDelayTime = 0;




int JobSkillTemp = 0;


DWORD UseSkillItemInfo[12] = { 0,sinWA1,sinWM1,sinWH1,sinDS1,sinWP1,sinWS2,sinWC1,sinWS1,sinWT1,sinWD1,sinWN1 };



int SkillDataCheckDelayTime = 0;
int SkillDataCheckFlag2 = 0;




DWORD ClearSkillPointCODE[10] = { 0,0,0,0,0,0,0,0,0,0 };



unsigned int CharSkillInfoData[10] = { 0, };
int   ChangeJob = -1;



//滚眠倔扼捞橇甫 悸泼茄促
int AddVirtualLife[2] = { 0,0 };
int sinVirtualLifeTime = 0;
int sinVirtualLifePercent = 0;

// 冠犁盔 - 何胶磐 酒捞袍(积疙仿)
int AddBoosterLife = 0;
int BoosterLifeTime = 0;
int BoosterLifePercent = 0;
int LifeFlag = 0;
short tempLife[2] = { 0,0 };

// 冠犁盔 - 何胶磐 酒捞袍(扁仿)
int AddVirtualMana[2] = { 0,0 };
int sinVirtualManaTime = 0;
int sinVirtualManaPercent = 0;
int ManaFlag = 0;
short tempMana[2] = { 0,0 };

// 冠犁盔 - 何胶磐 酒捞袍(辟仿)
int AddVirtualStamina[2] = { 0,0 };
int sinVirtualStaminaTime = 0;
int sinVirtualStaminaPercent = 0;
int StaminaFlag = 0;
short tempStamina[2] = { 0,0 };

// 厘喊 - 胶懦 掉饭捞
int sinAddSkillDelay = 0;
int sinSkillDelayTime = 0;
int SkillDelayFlag = 0;
