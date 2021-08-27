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
int MatCrystalOrb[MAX_CRYSTAL] = { 0 };
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

DWORD sinSkillBoxColor = D3DCOLOR_RGBA(0, 0, 132, 128);

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

sSKILL_INFO sSkill_Info[SIN_MAX_SKILL] =
{
#include "sinSkill_Info.h"
};

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
void cSKILL::Init()
{
	char *FilePath = "Image\\SinImage\\skill\\keep\\";
	char szFilePath[128];
	for (int j = 0; j < SIN_MAX_SKILL; j++)
	{
		if (sSkill[j].IconName)
		{
			wsprintf(szFilePath, "%s%s", FilePath, sSkill[j].IconName);
			sSkill[j].MatIcon = CreateTextureMaterial(szFilePath, 0, 0, 0, SMMAT_BLEND_ALPHA);
		}
	}
	MatCircleIcon = CreateTextureMaterial("Image\\SinImage\\Skill\\keep\\GA_Mon.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);;
	MatSkillIconBackGround = CreateTextureMaterial("Image\\SinImage\\Skill\\keep\\GA_.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);;

	SearchUseSkill();
	Load();

	sinSkill.pLeftSkill = &sinSkill.UseSkill[0];
	sinSkill.UseSkill[0].MousePosi = 1;
	sinSkill.pLeftSkill->Position = 1;
}
void cSKILL::Load()
{
	int i = 0;
	char ShortKeyDirPath[128];
	char WeaponIconPath[128];

	lpSkillDown = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\skilldown.bmp");

	lpSkillMain = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\Skil24.bmp");
	lpSkillMain2 = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\Skil25.bmp");

	lpSkillMainLeftB = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\LeftArrow.bmp");
	lpSkillMainRightB = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\RightArrow.bmp");

	lpSkillGage[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\Gage.bmp");
	lpSkillGage[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\Gage2.bmp");
	lpSkillGage2[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\Gage-2.bmp");
	lpSkillGage2[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\Gage-22.bmp");
	lpSkillGage3 = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\Gage-3.bmp");
	lpSkillGage4 = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\Gage-4.bmp");
	lpSkillGage5 = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\Gage-5.bmp");

	lpMasteryInfo = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\MasteryInfo.bmp");

	lpSelectSkill = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\SelectSkill.bmp");
	lpSkillBoxBack = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\BOX4040.bmp");

	for (i = 0; i < 8; i++)
	{
		wsprintf(ShortKeyDirPath, "Image\\SinImage\\skill\\ShortKey\\f%d.bmp", i + 1);
		lpShortKey[i] = LoadDibSurfaceOffscreen(ShortKeyDirPath);
	}
	for (i = 0; i < 12; i++)
	{
		wsprintf(WeaponIconPath, "Image\\SinImage\\skill\\WeaponIcon\\%d.bmp", i + 1);
		lpWeaponIcon[i] = LoadDibSurfaceOffscreen(WeaponIconPath);
	}
}

//加载技能图片
void cSKILL::LoadUseSkillImage()
{
	int i = 0;
	char TempDirPath[128];
	char TempTitleDirPath[128];
	char ButtonImageDirPath[128];

	TempDirPath[0] = 0;
	switch (UseSkillBox)
	{
	case GROUP_MECHANICIAN:
		lstrcpy(TempDirPath, "Image\\SinImage\\Skill\\Mecha\\");
		break;
	case GROUP_FIGHTER:
		lstrcpy(TempDirPath, "Image\\SinImage\\Skill\\Fighter\\");
		break;
	case GROUP_PIKEMAN:
		lstrcpy(TempDirPath, "Image\\SinImage\\Skill\\Pikeman\\");
		break;
	case GROUP_ARCHER:
		lstrcpy(TempDirPath, "Image\\SinImage\\Skill\\Archer\\");
		break;
	case GROUP_ATALANTA:
		lstrcpy(TempDirPath, "Image\\SinImage\\Skill\\Atalanta\\");
		break;
	case GROUP_KNIGHT:
		lstrcpy(TempDirPath, "Image\\SinImage\\Skill\\Knight\\");
		break;
	case GROUP_MAGICIAN:
		lstrcpy(TempDirPath, "Image\\SinImage\\Skill\\Magician\\");
		break;
	case GROUP_PRIESTESS:
		lstrcpy(TempDirPath, "Image\\SinImage\\Skill\\Priestess\\");
		break;
	case GROUP_ASSASSIN:
		lstrcpy(TempDirPath, "Image\\SinImage\\Skill\\Assassin\\");
		break;
	case GROUP_SHAMAN:
		lstrcpy(TempDirPath, "Image\\SinImage\\Skill\\Shaman\\");
		break;
	}
	if (!TempDirPath[0])
		return;

	lpSkillButton[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\Skill\\Skill_Normal.bmp");
	lpSkillButton_Gray[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\Skill\\Skill_Normal.bmp");
	for (i = 0; i < SIN_MAX_SKILL_TITLE; i++)
	{
		wsprintf(TempTitleDirPath, "%s%s%d%s", TempDirPath, "JobTitle\\", i + 1, ".bmp");
		lpSkillTitle[i] = LoadDibSurfaceOffscreen(TempTitleDirPath);
	}
	for (i = 1; i < SIN_MAX_USE_SKILL; i++)
	{
		if (sinSkill.UseSkill[i].Flag)
		{
			if (sinSkill.UseSkill[i].FileName[0])
			{
				wsprintf(ButtonImageDirPath, "%s%s%s%s", TempDirPath, "Button\\", sinSkill.UseSkill[i].FileName, ".bmp");
				lpSkillButton[i] = LoadDibSurfaceOffscreen(ButtonImageDirPath);
				wsprintf(ButtonImageDirPath, "%s%s%s%s%s", TempDirPath, "Button\\", sinSkill.UseSkill[i].FileName, "_", ".bmp");
				lpSkillButton_Gray[i] = LoadDibSurfaceOffscreen(ButtonImageDirPath);
			}
		}
	}
}
void cSKILL::Release()
{
	DELET(lpSkillGage[0]);
	DELET(lpSkillGage[1]);
	DELET(lpSelectSkill);
	DELET(lpSkillMain);
	DELET(lpSkillMain2);
	DELET(lpSkillMainLeftB);
	DELET(lpSkillMainRightB);

	for (int i = 0; i < SIN_MAX_SKILL_TITLE; i++)
		DELET(lpSkillTitle[i]);

	for (int i = 0; i < SIN_MAX_USE_SKILL; i++)
	{
		DELET(lpSkillButton[i]);
		DELET(lpSkillButton_Gray[i]);
	}
	for (int i = 0; i < 8; i++)
		DELET(lpShortKey[i]);

	for (int i = 0; i < 12; i++)
		DELET(lpWeaponIcon[i]);
}

int CheckVirtualLifeTime = 0;
int CheckBoosterLifeTime = 0;
int CheckVirtualManaTime = 0;
int CheckVirtualStaminaTime = 0;
int CheckSkillDelayTime = 0;
void cSKILL::DrawUp()
{
	for (int i = 0; i < SIN_MAX_SKILL_LIST; i++)
	{
		if (TempContinueSkill[i].Flag)
		{
			if (TempContinueSkill[i].MatIcon)
			{
				if (!TempContinueSkill[i].IconFlag)
				{
					dsDrawTexImage(MatSkillIconBackGround, 10 + TempContinueSkill[i].IconPosiX, 10, 32, 32, TempContinueSkill[i].IconAlpha);
					SkillBarDraw(&TempContinueSkill[i], 10 + 16 + TempContinueSkill[i].IconPosiX, 10 + 16, TempContinueSkill[i].IconAlpha);
					dsDrawTexImage(TempContinueSkill[i].MatIcon, 10 + TempContinueSkill[i].IconPosiX, 10, 32, 32, TempContinueSkill[i].IconAlpha);
				}
			}
		}
	}
}
void cSKILL::Draw()
{
	int i = 0;

	if (SkillMain2OpenFlag)
	{
		DrawSprite(0, 600 - sinMoveKindInter[SIN_SKILL] + 56, lpSkillMain2, 0, 0, 800, 200);
		if (SkillMain2ButtonFlag[0])
			DrawSprite(13, 600 + 83 - sinMoveKindInter[SIN_SKILL] + 56, lpSkillMainLeftB, 0, 0, 20, 20);
	}
	if (!SkillMain2OpenFlag)
	{
		DrawSprite(0, 600 - sinMoveKindInter[SIN_SKILL] + 56, lpSkillMain, 0, 0, 800, 200);
		if (SkillMain2ButtonFlag[1])
			DrawSprite(766, 600 + 83 - sinMoveKindInter[SIN_SKILL] + 56, lpSkillMainRightB, 0, 0, 20, 20);
	}
	int CharacterJob = (int)sinChar->iRank;
	int ChangeJobSkillPlusTemp = ChangeJobSkillPlus;

	if (OpenFlag)
	{
		if (!SkillMain2OpenFlag)
		{
			if (CharacterJob > 3)
				CharacterJob = 3;

			for (i = 0; i < CharacterJob + 1; i++)
				DrawSprite(SkillTitle[i][0], SkillTitle[i][1] + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillTitle[i], 0, 0, 100, 20);

			if (ChangeJobSkillPlusTemp > 17)
				ChangeJobSkillPlusTemp = 17;

			for (i = 1; i < ChangeJobSkillPlusTemp; i++)
			{
				if (sinSkill.UseSkill[i].Flag && sinSkill.UseSkill[i].Use && SkillMasterFlag)
				{
					if (lpSkillButton[i])
						DrawSprite(sinSkill.SkillBox[i].BoxRect.left, sinSkill.SkillBox[i].BoxRect.top + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillButton[i], 0, 0, 49, 46);
				}
				if (sinSkill.UseSkill[i].Flag && !sinSkill.UseSkill[i].Use && SkillMasterFlag)
				{
					if (lpSkillButton_Gray[i])
						DrawSprite(sinSkill.SkillBox[i].BoxRect.left, sinSkill.SkillBox[i].BoxRect.top + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillButton_Gray[i], 0, 0, 49, 46);
				}
				if (sinSkill.UseSkill[i].Flag && SkillMasterFlag && sinSkill.UseSkill[i].Point >= 10)
				{
					if (lpSkillButton_Gray[i])
						DrawSprite(sinSkill.SkillBox[i].BoxRect.left, sinSkill.SkillBox[i].BoxRect.top + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillButton_Gray[i], 0, 0, 49, 46);
				}
				if (!SkillMasterFlag)
				{
					if (sinSkill.UseSkill[i].Flag && sinSkill.UseSkill[i].Point)
					{
						if (lpSkillButton[i])
							DrawSprite(sinSkill.SkillBox[i].BoxRect.left, sinSkill.SkillBox[i].BoxRect.top + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillButton[i], 0, 0, 49, 46);
					}
					if (sinSkill.UseSkill[i].Flag && !sinSkill.UseSkill[i].Point)
					{
						if (lpSkillButton_Gray[i])
							DrawSprite(sinSkill.SkillBox[i].BoxRect.left, sinSkill.SkillBox[i].BoxRect.top + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillButton_Gray[i], 0, 0, 49, 46);
					}
				}
				if (sinSkill.UseSkill[i].Flag && sinSkill.UseSkill[i].Skill_Info.USECODE == SIN_SKILL_USE_NOT)
					DrawSprite(sinSkill.SkillBox[i].GageRect.left, sinSkill.SkillBox[i].GageRect.top + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillGage4, 0, 0, 5, 35);

				if (sinSkill.UseSkill[i].Flag && (sinSkill.UseSkill[i].Skill_Info.USECODE != SIN_SKILL_USE_NOT || sinSkill.UseSkill[i].Skill_Info.Element[0]))
				{
					DrawSprite(sinSkill.SkillBox[i].GageRect.left, sinSkill.SkillBox[i].GageRect.top + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillGage3, 0, 0, 5, 35);
					DrawSprite(sinSkill.SkillBox[i].GageRect.left, sinSkill.SkillBox[i].GageRect.top + (35 - sinSkill.UseSkill[i].UseSkillMasteryGage) + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillGage2[0], 0, 35 - sinSkill.UseSkill[i].UseSkillMasteryGage, 5, 35);
					if (sinSkill.UseSkill[i].UseSkillMasteryGage >= 3)
						DrawSprite(sinSkill.SkillBox[i].GageRect.left, sinSkill.SkillBox[i].GageRect.top + (35 - sinSkill.UseSkill[i].UseSkillMasteryGage) + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillGage2[1], 0, 0, 5, 3);
				}
				if (sinSkill.UseSkill[i].Flag)
				{
					DrawSprite(sinSkill.SkillBox[i].GageRect.right + 1, sinSkill.SkillBox[i].GageRect.top + (35 - sinSkill.UseSkill[i].GageLength) + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillGage[0], 0, 35 - sinSkill.UseSkill[i].GageLength, 5, 35);
					if (sinSkill.UseSkill[i].GageLength >= 3)
						DrawSprite(sinSkill.SkillBox[i].GageRect.right + 1, sinSkill.SkillBox[i].GageRect.top + (35 - sinSkill.UseSkill[i].GageLength) + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillGage[0], 0, 0, 5, 3);
				}
				if (sinSkill.UseSkill[i].Flag && sinSkill.UseSkill[i].Skill_Info.Element[0])
					DrawSprite(sinSkill.SkillBox[i].GageRect.left, sinSkill.SkillBox[i].GageRect.top + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillGage5, 0, 0, 5, 35);
			}
			if (DownButtonIndex)
				DrawSprite(sinSkill.SkillBox[DownButtonIndex - 1].BoxRect.left + 1, sinSkill.SkillBox[DownButtonIndex - 1].BoxRect.top + 1 + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillButton[DownButtonIndex - 1], 0, 0, 49, 46);

			if (SkillButtonIndex)
			{
				if (sinSkill.UseSkill[SkillButtonIndex - 1].Flag)
				{
					if (DownButtonIndex)
						DrawSprite(sinSkill.SkillBox[SkillButtonIndex - 1].BoxRect.left + 1, sinSkill.SkillBox[SkillButtonIndex - 1].BoxRect.top + 1 + (256 - sinMoveKindInter[SIN_SKILL]), lpSelectSkill, 0, 0, 49, 46);
					else
						DrawSprite(sinSkill.SkillBox[SkillButtonIndex - 1].BoxRect.left, sinSkill.SkillBox[SkillButtonIndex - 1].BoxRect.top + (256 - sinMoveKindInter[SIN_SKILL]), lpSelectSkill, 0, 0, 49, 46);
				}
			}
			for (i = 0; i < ChangeJobSkillPlusTemp; i++)
			{
				if (sinSkill.UseSkill[i].Flag)
				{
					if (sinSkill.UseSkill[i].ShortKey)
						DrawSprite(sinSkill.SkillBox[i].BoxRect.left + 9, sinSkill.SkillBox[i].BoxRect.top - 6 + (256 - sinMoveKindInter[SIN_SKILL]), lpShortKey[sinSkill.UseSkill[i].ShortKey - 1], 0, 0, 16, 16);
				}
			}
		}
		else
		{
			for (i = 4; i < (int)sinChar->iRank + 1; i++)
				DrawSprite(SkillTitle[i][0], SkillTitle[i][1] + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillTitle[i], 0, 0, 100, 20);

			for (i = 17; i < ChangeJobSkillPlus; i++)
			{
				if (sinSkill.UseSkill[i].Flag && sinSkill.UseSkill[i].Use && SkillMasterFlag)
				{
					if (lpSkillButton[i])
						DrawSprite(sinSkill.SkillBox[i].BoxRect.left, sinSkill.SkillBox[i].BoxRect.top + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillButton[i], 0, 0, 49, 46);
				}
				if (sinSkill.UseSkill[i].Flag && !sinSkill.UseSkill[i].Use && SkillMasterFlag)
				{
					if (lpSkillButton_Gray[i])
						DrawSprite(sinSkill.SkillBox[i].BoxRect.left, sinSkill.SkillBox[i].BoxRect.top + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillButton_Gray[i], 0, 0, 49, 46);
				}
				if (sinSkill.UseSkill[i].Flag && SkillMasterFlag && sinSkill.UseSkill[i].Point >= 10)
				{
					if (lpSkillButton_Gray[i])
						DrawSprite(sinSkill.SkillBox[i].BoxRect.left, sinSkill.SkillBox[i].BoxRect.top + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillButton_Gray[i], 0, 0, 49, 46);
				}
				if (!SkillMasterFlag)
				{
					if (sinSkill.UseSkill[i].Flag && sinSkill.UseSkill[i].Point)
					{
						if (lpSkillButton[i])
							DrawSprite(sinSkill.SkillBox[i].BoxRect.left, sinSkill.SkillBox[i].BoxRect.top + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillButton[i], 0, 0, 49, 46);
					}
					if (sinSkill.UseSkill[i].Flag && !sinSkill.UseSkill[i].Point)
					{
						if (lpSkillButton_Gray[i])
							DrawSprite(sinSkill.SkillBox[i].BoxRect.left, sinSkill.SkillBox[i].BoxRect.top + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillButton_Gray[i], 0, 0, 49, 46);
					}
				}
				if (sinSkill.UseSkill[i].Flag && sinSkill.UseSkill[i].Skill_Info.USECODE == SIN_SKILL_USE_NOT)
					DrawSprite(sinSkill.SkillBox[i].GageRect.left, sinSkill.SkillBox[i].GageRect.top + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillGage4, 0, 0, 5, 35);

				if (sinSkill.UseSkill[i].Flag && (sinSkill.UseSkill[i].Skill_Info.USECODE != SIN_SKILL_USE_NOT || sinSkill.UseSkill[i].Skill_Info.Element[0]))
				{
					DrawSprite(sinSkill.SkillBox[i].GageRect.left, sinSkill.SkillBox[i].GageRect.top + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillGage3, 0, 0, 5, 35);
					DrawSprite(sinSkill.SkillBox[i].GageRect.left, sinSkill.SkillBox[i].GageRect.top + (35 - sinSkill.UseSkill[i].UseSkillMasteryGage) + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillGage2[0], 0, 35 - sinSkill.UseSkill[i].UseSkillMasteryGage, 5, 35);
					if (sinSkill.UseSkill[i].UseSkillMasteryGage >= 3)
						DrawSprite(sinSkill.SkillBox[i].GageRect.left, sinSkill.SkillBox[i].GageRect.top + (35 - sinSkill.UseSkill[i].UseSkillMasteryGage) + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillGage2[1], 0, 0, 5, 3);
				}
				if (sinSkill.UseSkill[i].Flag)
				{
					DrawSprite(sinSkill.SkillBox[i].GageRect.right + 1, sinSkill.SkillBox[i].GageRect.top + (35 - sinSkill.UseSkill[i].GageLength) + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillGage[0], 0, 35 - sinSkill.UseSkill[i].GageLength, 5, 35);
					if (sinSkill.UseSkill[i].GageLength >= 3)
						DrawSprite(sinSkill.SkillBox[i].GageRect.right + 1, sinSkill.SkillBox[i].GageRect.top + (35 - sinSkill.UseSkill[i].GageLength) + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillGage[0], 0, 0, 5, 3);
				}
				if (sinSkill.UseSkill[i].Flag && sinSkill.UseSkill[i].Skill_Info.Element[0])
					DrawSprite(sinSkill.SkillBox[i].GageRect.left, sinSkill.SkillBox[i].GageRect.top + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillGage5, 0, 0, 5, 35);
			}
			if (DownButtonIndex)
				DrawSprite(sinSkill.SkillBox[DownButtonIndex - 1].BoxRect.left + 1, sinSkill.SkillBox[DownButtonIndex - 1].BoxRect.top + 1 + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillButton[DownButtonIndex - 1], 0, 0, 49, 46);

			if (SkillButtonIndex)
			{
				if (sinSkill.UseSkill[SkillButtonIndex - 1].Flag)
				{
					if (DownButtonIndex)
						DrawSprite(sinSkill.SkillBox[SkillButtonIndex - 1].BoxRect.left + 1, sinSkill.SkillBox[SkillButtonIndex - 1].BoxRect.top + 1 + (256 - sinMoveKindInter[SIN_SKILL]), lpSelectSkill, 0, 0, 49, 46);
					else
						DrawSprite(sinSkill.SkillBox[SkillButtonIndex - 1].BoxRect.left, sinSkill.SkillBox[SkillButtonIndex - 1].BoxRect.top + (256 - sinMoveKindInter[SIN_SKILL]), lpSelectSkill, 0, 0, 49, 46);
				}
			}
			for (i = 17; i < ChangeJobSkillPlus; i++)
			{
				if (sinSkill.UseSkill[i].Flag)
				{
					if (sinSkill.UseSkill[i].ShortKey)
						DrawSprite(sinSkill.SkillBox[i].BoxRect.left + 9, sinSkill.SkillBox[i].BoxRect.top - 6 + (256 - sinMoveKindInter[SIN_SKILL]), lpShortKey[sinSkill.UseSkill[i].ShortKey - 1], 0, 0, 16, 16);
				}
			}
		}
	}
	if (SkillMasteryShowFlag)
		DrawSprite(UseSkillMasteryPosi.x, UseSkillMasteryPosi.y + (256 - sinMoveKindInter[SIN_SKILL]), lpMasteryInfo, 0, 0, 39, 27);

	if (sinSkill.pLeftSkill)
	{
		if (sinSkill.pLeftSkill->UseSkillFlag)
			DrawSprite(sLeftRightSkill[0].BoxRect.left, sLeftRightSkill[0].BoxRect.top, lpSkillButton[sinSkill.pLeftSkill->Position - 1], 0, 0, 49, 46);
		else
			DrawSprite(sLeftRightSkill[0].BoxRect.left, sLeftRightSkill[0].BoxRect.top, lpSkillButton_Gray[sinSkill.pLeftSkill->Position - 1], 0, 0, 49, 46);
	}
	else
		DrawSprite(sLeftRightSkill[0].BoxRect.left, sLeftRightSkill[0].BoxRect.top, lpSkillBoxBack, 0, 0, 49, 46);

	if (sinSkill.pRightSkill)
	{
		if (sinSkill.pRightSkill->UseSkillFlag)
			DrawSprite(sLeftRightSkill[1].BoxRect.left, sLeftRightSkill[1].BoxRect.top, lpSkillButton[sinSkill.pRightSkill->Position - 1], 0, 0, 49, 46);
		else
			DrawSprite(sLeftRightSkill[1].BoxRect.left, sLeftRightSkill[1].BoxRect.top, lpSkillButton_Gray[sinSkill.pRightSkill->Position - 1], 0, 0, 49, 46);
	}
	else
		DrawSprite(sLeftRightSkill[1].BoxRect.left, sLeftRightSkill[1].BoxRect.top, lpSkillBoxBack, 0, 0, 49, 46);
}
void cSKILL::Main()
{
	int i = 0, j = 0;
	int k = 0, Num = 0;

	sSKILL  TempSkillData;
	CheckContinueIcon();
	memset(TempContinueSkill, 0, sizeof(sSKILL)*SIN_MAX_SKILL_LIST);

	for (k = 0; k < SIN_MAX_SKILL_LIST; k++)
	{
		if (ContinueSkill[k].Flag)
		{
			if (ContinueSkill[k].MatIcon)
			{
				if (Num * 32 > ContinueSkill[k].IconPosiX)
					ContinueSkill[k].IconPosiX += 2;

				else if (Num * 32 < ContinueSkill[k].IconPosiX)
					ContinueSkill[k].IconPosiX -= 2;

				if (ContinueSkill[k].CheckTime < 255)
					ContinueSkill[k].IconAlpha++;

				if (ContinueSkill[k].CheckTime >= 255)
					ContinueSkill[k].IconAlpha = 255;

				if (((ContinueSkill[k].UseTime * 70) - ContinueSkill[k].CheckTime) < 180)
					ContinueSkill[k].IconAlpha--;

				if (ContinueSkill[k].IconAlpha > 255)
					ContinueSkill[k].IconAlpha = 255;

				if (ContinueSkill[k].IconAlpha < 0)
					ContinueSkill[k].IconAlpha = 0;

				if (ContinueSkill[k].CheckTime > (ContinueSkill[k].UseTime - 4) * 70)
				{
					ContinueSkill[k].IconTime++;
					if (ContinueSkill[k].IconTime > 30)
					{
						ContinueSkill[k].IconTime = 0;
						ContinueSkill[k].IconFlag ^= 1;
					}
				}
				memcpy(&TempContinueSkill[Num], &ContinueSkill[k], sizeof(sSKILL));
				Num++;
			}
		}
	}

	int TempXPosi = 0;
	for (i = Num; i > 0; i--)
	{
		for (j = 0; j < i; j++)
		{
			if (TempContinueSkill[j].CheckTime < TempContinueSkill[j + 1].CheckTime)
			{
				if (TempContinueSkill[j].CheckTime != 0)
				{
					TempSkillData = TempContinueSkill[j + 1];
					TempXPosi = TempContinueSkill[j + 1].IconPosiX;
					TempContinueSkill[j + 1] = TempContinueSkill[j];
					TempContinueSkill[j + 1].IconPosiX = TempXPosi;
					TempXPosi = TempContinueSkill[j].IconPosiX;
					TempContinueSkill[j] = TempSkillData;
					TempContinueSkill[j].IconPosiX = TempXPosi;
				}
			}
		}
	}
	if (AddVirtualLife[1])
	{
		CheckVirtualLifeTime++;
		if (CheckVirtualLifeTime >= sinVirtualLifeTime * 70)
		{
			CheckVirtualLifeTime = 0;
			AddVirtualLife[0] = 0;
			AddVirtualLife[1] = 0;
			sinVirtualLifePercent = 0;
		}
	}
	if (AddBoosterLife)
	{
		CheckBoosterLifeTime++;
		if (CheckBoosterLifeTime >= BoosterLifeTime * 70)
		{
			CheckBoosterLifeTime = 0;
			AddBoosterLife = 0;
			BoosterLifePercent = 0;
			tempLife[0] = 0;
			LifeFlag = 0;
		}
	}
	if (AddVirtualLife[1] && !AddBoosterLife)
	{
		for (i = 0; i < SIN_MAX_SKILL_LIST; i++)
		{
			if (ContinueSkill[i].Flag)
			{
				if (ContinueSkill[i].CODE == SKILL_VIRTUAL_LIFE)
				{
					AddVirtualLife[1] = ((int)sinChar->sHP.sMax * Virtual_Life_Percent[ContinueSkill[i].Point - 1]) / 100;
					break;
				}
			}
		}
	}
	if (AddVirtualMana[1])
	{
		CheckVirtualManaTime++;
		if (CheckVirtualManaTime >= sinVirtualManaTime * 70)
		{
			CheckVirtualManaTime = 0;
			AddVirtualMana[0] = 0;
			AddVirtualMana[1] = 0;
			sinVirtualManaPercent = 0;
			tempMana[0] = 0;
			ManaFlag = 0;
		}
	}
	if (AddVirtualStamina[1])
	{
		CheckVirtualStaminaTime++;
		if (CheckVirtualStaminaTime >= sinVirtualStaminaTime * 70)
		{
			CheckVirtualStaminaTime = 0;
			AddVirtualStamina[0] = 0;
			AddVirtualStamina[1] = 0;
			sinVirtualStaminaPercent = 0;
			tempStamina[0] = 0;
			StaminaFlag = 0;
		}
	}
	if (sinAddSkillDelay)
	{
		CheckSkillDelayTime++;
		if (CheckSkillDelayTime >= sinSkillDelayTime * 70)
		{
			CheckSkillDelayTime = 0;
			sinAddSkillDelay = 0;
			sinSkillDelayTime = 0;
			SkillDelayFlag = 0;
		}
	}
	sinCheckContinueSkill();
	CheckSkillData();
	if (!ClearSkillCODE || !cSkill.OpenFlag || pCursorPos.y < 400)
	{
		ClearSkillCODE = 0;
		SkillInfoShowFlag = 0;
	}

	SkillMasteryShowFlag = 0;
	SelectInterSkill = 0;
	CheckingNowSkillState();

	sinCheckChageJob();

	ShowSkillClose = 0;
	SkillButtonIndex = 0;

	int Space = 0;
	sSKILLBOX TempSkillBox;
	ContinueSkillMouseIndex = 0;
	for (i = 0; i < SIN_MAX_SKILL_LIST; i++)
	{
		if (TempContinueSkill[i].Flag)
		{
			if (TempContinueSkill[i].MatIcon)
			{
				if (10 + (Space * 32) < pCursorPos.x && 10 + (Space * 32) + 32 > pCursorPos.x && 10 < pCursorPos.y && 10 + 32 > pCursorPos.y)
				{
					TempSkillBox.BoxRect.left = 10 + (Space * 32);
					TempSkillBox.BoxRect.top = 10 + 32;
					SkillInfoShowFlag = 2;
					ContinueSkillMouseIndex = i + 1;
					ShowSkillInfo(&TempContinueSkill[i], &TempSkillBox, 1);
				}
				Space++;
			}
		}
	}
	if (269 < pCursorPos.x && 287 > pCursorPos.x && 571 < pCursorPos.y && 590 > pCursorPos.y)
		ShowSkillClose = 1;

	int ChangeJobSkillPlusTemp = ChangeJobSkillPlus;

	if (OpenFlag)
	{
		if (!SkillMain2OpenFlag)
		{
			if (ChangeJobSkillPlusTemp > 17)
				ChangeJobSkillPlusTemp = 17;

			for (int i = 0; i < ChangeJobSkillPlusTemp; i++)
			{
				if (sinSkill.UseSkill[i].Flag)
				{
					if (sinSkill.SkillBox[i].BoxRect.left < pCursorPos.x && sinSkill.SkillBox[i].BoxRect.right > pCursorPos.x && sinSkill.SkillBox[i].BoxRect.top < pCursorPos.y && sinSkill.SkillBox[i].BoxRect.bottom > pCursorPos.y)
					{
						SkillButtonIndex = i + 1;

						sinSkill.UseSkill[i].Position = i + 1;
						ShowSkillInfo(&sinSkill.UseSkill[i], &sinSkill.SkillBox[i]);
						SkillInfoShowFlag = 1;

						if (sinSkill.UseSkill[i].Point && SkillMasterFlag)
							SearchClearSkillPoint(sinSkill.UseSkill[i].CODE);
					}
					if (sinSkill.SkillBox[i].GageRect.left < pCursorPos.x && sinSkill.SkillBox[i].GageRect.right > pCursorPos.x && sinSkill.SkillBox[i].GageRect.top < pCursorPos.y && sinSkill.SkillBox[i].GageRect.bottom > pCursorPos.y)
					{
						if (sinSkill.UseSkill[i].Skill_Info.USECODE != SIN_SKILL_USE_NOT)
						{
							GetSkillMastery(&sinSkill.UseSkill[i], &sinSkill.SkillBox[i]);
							SkillMasteryShowFlag = 1;
						}
					}
				}
			}
		}
		else
		{
			for (int i = 17; i < ChangeJobSkillPlus; i++)
			{
				if (sinSkill.UseSkill[i].Flag)
				{
					if (sinSkill.SkillBox[i].BoxRect.left < pCursorPos.x && sinSkill.SkillBox[i].BoxRect.right > pCursorPos.x && sinSkill.SkillBox[i].BoxRect.top < pCursorPos.y && sinSkill.SkillBox[i].BoxRect.bottom > pCursorPos.y)
					{
						SkillButtonIndex = i + 1;

						sinSkill.UseSkill[i].Position = i + 1;
						ShowSkillInfo(&sinSkill.UseSkill[i], &sinSkill.SkillBox[i]);
						SkillInfoShowFlag = 1;

						if (sinSkill.UseSkill[i].Point && SkillMasterFlag)
							SearchClearSkillPoint(sinSkill.UseSkill[i].CODE);
					}
					if (sinSkill.SkillBox[i].GageRect.left < pCursorPos.x && sinSkill.SkillBox[i].GageRect.right > pCursorPos.x && sinSkill.SkillBox[i].GageRect.top < pCursorPos.y && sinSkill.SkillBox[i].GageRect.bottom > pCursorPos.y)
					{
						if (sinSkill.UseSkill[i].Skill_Info.USECODE != SIN_SKILL_USE_NOT)
						{
							GetSkillMastery(&sinSkill.UseSkill[i], &sinSkill.SkillBox[i]);
							SkillMasteryShowFlag = 1;
						}
					}
				}
			}
		}
	}
	for (i = 0; i < 2; i++)
	{
		if (sLeftRightSkill[i].BoxRect.left < pCursorPos.x && sLeftRightSkill[i].BoxRect.right > pCursorPos.x && sLeftRightSkill[i].BoxRect.top < pCursorPos.y && sLeftRightSkill[i].BoxRect.bottom > pCursorPos.y)
		{
			if (i == 0 && sinSkill.pLeftSkill)
			{
				cHelpPet.PetMessage("*LeftSkill", 0);
				ShowSkillInfo(sinSkill.pLeftSkill, &sLeftRightSkill[i]);
				SkillInfoShowFlag = 1;
				SelectInterSkill = 1;
			}
			if (i == 1 && sinSkill.pRightSkill)
			{
				cHelpPet.PetMessage("*RightSkill", 0);
				ShowSkillInfo(sinSkill.pRightSkill, &sLeftRightSkill[i]);
				SkillInfoShowFlag = 1;
				SelectInterSkill = 2;
			}
		}
	}
	if (OpenFlag && SkillMain2OpenFlag)
	{
		if (12 < pCursorPos.x && 12 + 20 > pCursorPos.x && 482 < pCursorPos.y && 482 + 20 > pCursorPos.y)
			SkillMain2ButtonFlag[0] = 1;
		else
			SkillMain2ButtonFlag[0] = 0;
	}
	if (OpenFlag && !SkillMain2OpenFlag)
	{
		if (765 < pCursorPos.x && 765 + 20 > pCursorPos.x && 482 < pCursorPos.y && 482 + 20 > pCursorPos.y)
			SkillMain2ButtonFlag[1] = 1;
		else
			SkillMain2ButtonFlag[1] = 0;
	}
}
void cSKILL::Close()
{

}
void cSKILL::LButtonDown(int x, int y)
{
	for (int i = 0; i < 2; i++)
	{
		if (sLeftRightSkill[i].BoxRect.left < pCursorPos.x && sLeftRightSkill[i].BoxRect.right > pCursorPos.x && sLeftRightSkill[i].BoxRect.top < pCursorPos.y && sLeftRightSkill[i].BoxRect.bottom > pCursorPos.y)
		{
			if (i == 0 && sinSkill.pLeftSkill)
				cHelpPet.PetMessage("*LeftSkill", 1);
			if (i == 1 && sinSkill.pRightSkill)
				cHelpPet.PetMessage("*RightSkill", 1);
		}
	}
	if (ClearSkillButtonPosi.x  < pCursorPos.x  && ClearSkillButtonPosi.x + 45 > pCursorPos.x  && ClearSkillButtonPosi.y <  pCursorPos.y  && ClearSkillButtonPosi.y + 45 > pCursorPos.y)
		ClearSkillPointSection();

	DownButtonUseShorKey = 0;
	LDownButtonIndex = 0;
	if (ShowSkillClose)
		OpenFlag = 0;

	if (SkillButtonIndex)
	{
		if (sinSkill.UseSkill[SkillButtonIndex - 1].Flag)
			LDownButtonIndex = SkillButtonIndex;
	}

	DownButtonIndex = 0;
	if (ShowSkillClose)
		OpenFlag = 0;

	if (SkillButtonIndex <= 13 && SkillMasterFlag == 1 && sinSkill.SkillPoint)
	{
		if (sinSkill.UseSkill[SkillButtonIndex - 1].Flag && sinSkill.UseSkill[SkillButtonIndex - 1].Use && sinSkill.UseSkill[SkillButtonIndex - 1].Point < 10)
		{
			DownButtonIndex = SkillButtonIndex;
			Skill4ButtonIndex = SkillButtonIndex;
		}
	}
	if (SkillButtonIndex > 13 && SkillMasterFlag == 1 && sinSkill.SkillPoint4)
	{
		if (sinSkill.UseSkill[SkillButtonIndex - 1].Flag && sinSkill.UseSkill[SkillButtonIndex - 1].Use && sinSkill.UseSkill[SkillButtonIndex - 1].Point < 10)
		{
			DownButtonIndex = SkillButtonIndex;
			Skill4ButtonIndex = SkillButtonIndex;
		}
	}
	if (SelectInterSkill)
	{
		if (cSkill.OpenFlag == SIN_CLOSE)
			cSkill.OpenFlag = SIN_OPEN;
		else
			cSkill.OpenFlag = SIN_CLOSE;
		cInterFace.CheckAllBox(SIN_SKILL);
		if (cSkill.OpenFlag)
		{
			if (!sinFireShow)
			{
				StartMenuFlame(0, 350);
				sinPlaySound(0);
			}
			else
				sinPlaySound(SIN_SOUND_SHOW_INTER);
			sinFireShow = 1;
		}
	}
	if (SkillMain2ButtonFlag[1])
	{
		SkillMain2ButtonFlag[1] = 0;
		SkillMain2OpenFlag = 1;
	}
	if (SkillMain2ButtonFlag[0])
	{
		SkillMain2ButtonFlag[0] = 0;
		SkillMain2OpenFlag = 0;
	}
}
void cSKILL::LButtonUp(int x, int y)
{
	DownButtonIndex = 0;
	LDownButtonIndex = 0;
	if (SkillButtonIndex && !DownButtonUseShorKey)
	{
		if ((sinSkill.UseSkill[SkillButtonIndex - 1].Skill_Info.USECODE == SIN_SKILL_USE_LEFT || sinSkill.UseSkill[SkillButtonIndex - 1].Skill_Info.USECODE == SIN_SKILL_USE_ALL) && !SkillMasterFlag &&sinSkill.UseSkill[SkillButtonIndex - 1].Point)
			sinSkill.pLeftSkill = &sinSkill.UseSkill[SkillButtonIndex - 1];
	}
	if (SkillButtonIndex != 1 && SkillMasterFlag == 1)
	{
		if (SkillButtonIndex > 13 && sinSkill.SkillPoint4 > 0)
		{
			if (sinSkill.UseSkill[SkillButtonIndex - 1].Flag && sinSkill.UseSkill[SkillButtonIndex - 1].Use)
			{
				if (sinSkill.UseSkill[SkillButtonIndex - 1].Point < MAX_USE_SKILL_POINT)
				{
					pMasterSkill = &sinSkill.UseSkill[SkillButtonIndex - 1];
					//cMessageBox.ShowMessage3(MESSAGE_MASTER_SKILL,sinSkill.UseSkill[SkillButtonIndex-1].Skill_Info.SkillName);
					ShowSkillUpInfo = 1;
					MasterSkill();
					ShowSkillUpInfo = 0;
					//ShowSkillUpInfo = 1;
				}
			}
		}
		if (SkillButtonIndex <= 13 && sinSkill.SkillPoint > 0)
		{
			if (sinSkill.UseSkill[SkillButtonIndex - 1].Flag && sinSkill.UseSkill[SkillButtonIndex - 1].Use)
			{
				if (sinSkill.UseSkill[SkillButtonIndex - 1].Point < MAX_USE_SKILL_POINT)
				{
					pMasterSkill = &sinSkill.UseSkill[SkillButtonIndex - 1];
					//cMessageBox.ShowMessage3(MESSAGE_MASTER_SKILL,sinSkill.UseSkill[SkillButtonIndex-1].Skill_Info.SkillName);
					ShowSkillUpInfo = 1;
					MasterSkill();
					ShowSkillUpInfo = 0;
					//ShowSkillUpInfo = 1;
				}
			}
		}
	}
}
void cSKILL::RButtonDown(int x, int y)
{
	for (int i = 0; i < 2; i++)
	{
		if (sLeftRightSkill[i].BoxRect.left < pCursorPos.x && sLeftRightSkill[i].BoxRect.right > pCursorPos.x && sLeftRightSkill[i].BoxRect.top < pCursorPos.y && sLeftRightSkill[i].BoxRect.bottom > pCursorPos.y)
		{
			if (i == 0 && sinSkill.pLeftSkill)
				cHelpPet.PetMessage("*LeftSkill", 2);
			if (i == 1 && sinSkill.pRightSkill)
				cHelpPet.PetMessage("*RightSkill", 2);
		}
	}
	DownButtonUseShorKey = 0;
	if (SkillButtonIndex)
	{
		if (sinSkill.UseSkill[SkillButtonIndex - 1].Flag)
			RDownButtonIndex = SkillButtonIndex;
	}
}
void cSKILL::RButtonUp(int x, int y)
{
	RDownButtonIndex = 0;
	LDownButtonIndex = 0;
	if (SkillButtonIndex && !DownButtonUseShorKey)
	{
		if ((sinSkill.UseSkill[SkillButtonIndex - 1].Skill_Info.USECODE == SIN_SKILL_USE_RIGHT || sinSkill.UseSkill[SkillButtonIndex - 1].Skill_Info.USECODE == SIN_SKILL_USE_ALL) && !SkillMasterFlag && sinSkill.UseSkill[SkillButtonIndex - 1].Point)
			sinSkill.pRightSkill = &sinSkill.UseSkill[SkillButtonIndex - 1];
	}
}
void cSKILL::KeyDown()
{
	int i = 0;
	char szKeyBuff[8] = { VK_F1,VK_F2,VK_F3,VK_F4,VK_F5,VK_F6,VK_F7,VK_F8 };
	for (i = 0; i < 8; i++)
	{
		if (sinGetKeyClick(szKeyBuff[i]))
		{
			if (SkillButtonIndex)
			{
				if (LDownButtonIndex)
				{
					if (sinSkill.UseSkill[SkillButtonIndex - 1].Skill_Info.USECODE == SIN_SKILL_USE_LEFT || sinSkill.UseSkill[SkillButtonIndex - 1].Skill_Info.USECODE == SIN_SKILL_USE_ALL && sinSkill.UseSkill[SkillButtonIndex - 1].Point && !SkillMasterFlag)
					{
						sinSkill.UseSkill[SkillButtonIndex - 1].ShortKey = i + 1;
						sinSkill.UseSkill[SkillButtonIndex - 1].MousePosi = SIN_MOUSE_POSI_LEFT;
						DownButtonUseShorKey = 1;
					}
				}
				else
				{
					if (RDownButtonIndex)
					{
						if (sinSkill.UseSkill[SkillButtonIndex - 1].Skill_Info.USECODE == SIN_SKILL_USE_RIGHT || sinSkill.UseSkill[SkillButtonIndex - 1].Skill_Info.USECODE == SIN_SKILL_USE_ALL && sinSkill.UseSkill[SkillButtonIndex - 1].Point && !SkillMasterFlag)
						{
							sinSkill.UseSkill[SkillButtonIndex - 1].ShortKey = i + 1;
							sinSkill.UseSkill[SkillButtonIndex - 1].MousePosi = SIN_MOUSE_POSI_RIGHT;
							DownButtonUseShorKey = 1;
						}
					}
				}
				for (int j = 0; j < SIN_MAX_USE_SKILL; j++)
				{
					if (j == SkillButtonIndex - 1)continue;
					if (sinSkill.UseSkill[SkillButtonIndex - 1].ShortKey == sinSkill.UseSkill[j].ShortKey)
						sinSkill.UseSkill[j].ShortKey = 0;
				}
			}
			else
			{
				for (int j = 0; j < SIN_MAX_USE_SKILL; j++)
				{
					if (i == sinSkill.UseSkill[j].ShortKey - 1)
					{
						if (sinSkill.UseSkill[j].Point)
						{
							if (sinSkill.UseSkill[j].MousePosi == SIN_MOUSE_POSI_LEFT)
								sinSkill.pLeftSkill = &sinSkill.UseSkill[j];
							if (sinSkill.UseSkill[j].MousePosi == SIN_MOUSE_POSI_RIGHT)
								sinSkill.pRightSkill = &sinSkill.UseSkill[j];
						}
					}
				}
			}
		}
	}
	if (sinGetKeyClick('S'))
	{
		cHelpPet.PetMessage("*Skill", 3);
		if (cSkill.OpenFlag)
			cSkill.OpenFlag = SIN_CLOSE;
		else
			cSkill.OpenFlag = SIN_OPEN;
		cInterFace.CheckAllBox(SIN_SKILL);
		if (cSkill.OpenFlag)
		{
			if (!sinFireShow)
			{
				StartMenuFlame(0, 350);
				sinPlaySound(0);
			}
			else
				sinPlaySound(SIN_SOUND_SHOW_INTER);
			sinFireShow = 1;
		}
	}
	else if (sinGetKeyClick('P'))
	{
		if (SkillMain2OpenFlag)
			SkillMain2OpenFlag = SIN_CLOSE;
		else
			SkillMain2OpenFlag = SIN_OPEN;
	}
}

int cSKILL::SearchUseSkill()
{
	switch (sinChar->iClass)
	{
	case CHARACTERCLASS_Fighter:
		UseSkillBox = GROUP_FIGHTER;
		break;
	case CHARACTERCLASS_Mechanician:
		UseSkillBox = GROUP_MECHANICIAN;
		break;
	case CHARACTERCLASS_Archer:
		UseSkillBox = GROUP_ARCHER;
		break;
	case CHARACTERCLASS_Pikeman:
		UseSkillBox = GROUP_PIKEMAN;
		break;
	case CHARACTERCLASS_Atalanta:
		UseSkillBox = GROUP_ATALANTA;
		break;
	case CHARACTERCLASS_Knight:
		UseSkillBox = GROUP_KNIGHT;
		break;
	case CHARACTERCLASS_Magician:
		UseSkillBox = GROUP_MAGICIAN;
		break;
	case CHARACTERCLASS_Priestess:
		UseSkillBox = GROUP_PRIESTESS;
		break;
	case CHARACTERCLASS_Assassin:
		UseSkillBox = GROUP_ASSASSIN;
		break;
	case CHARACTERCLASS_Shaman:
		UseSkillBox = GROUP_SHAMAN;
		break;
	}
	if (!UseSkillBox)
		return FALSE;

	int Index = 0;
	memcpy(&sinSkill.UseSkill[0], &sSkill[0], sizeof(sSKILL));
	sinSkill.UseSkill[0].Flag = 1;
	sinSkill.UseSkill[0].Use = 1;
	sinSkill.UseSkill[0].Skill_Info.USECODE = SIN_SKILL_USE_ALL;
	sinSkill.UseSkill[0].Point = 1;

	for (int i = 0; i < SIN_MAX_SKILL; i++)
	{
		if ((sSkill[i].CODE & sinSKILL_MASK1) == UseSkillBox)
		{
			for (int j = 1; j < SIN_MAX_USE_SKILL; j++)
			{
				if (!sinSkill.UseSkill[j].Flag)
				{
					memcpy(&sinSkill.UseSkill[j], &sSkill[i], sizeof(sSKILL));
					for (int k = 0; k < SIN_MAX_SKILL; k++)
					{
						if (sinSkill.UseSkill[j].CODE == sSkill_Info[k].CODE)
						{
							memcpy(&sinSkill.UseSkill[j].Skill_Info, &sSkill_Info[k], sizeof(sSKILL_INFO));
							sinSkill.UseSkill[j].Skill_Info.SkillNum = j - 1;
							break;
						}
					}
					sinSkill.UseSkill[j].Flag = 1;
					break;
				}
			}
		}
	}
	memcpy(&sinSkill.SkillBox, &sSkillBox, sizeof(sSKILLBOX)*SIN_MAX_USE_SKILL);

	LoadUseSkillImage();

	sinSkill.UseSkill[0].Use = 1;
	sinSkill.UseSkill[0].Skill_Info.USECODE = SIN_SKILL_USE_ALL;
	sinSkill.UseSkill[0].Point = 1;
	ReFormCharSkillInfo();
	return FALSE;
}

void cSKILL::DrawSkillText()
{
	if (SkillInfoShowFlag || sinMoveKindInter[SIN_SKILL])
	{
		int BoldFlag = 0;
		int MasteryLen = 0;
		int MasteryShowX = 0;

		char strBuff[128];
		memset(strBuff, 0, sizeof(strBuff));

		DWORD Color = D3DCOLOR_XRGB(255, 255, 255);

		if (OpenFlag)
		{
			if (sinSkill.SkillPoint >= 0 || sinSkill.SkillPoint4 >= 0)
			{
				wsprintf(strBuff, "%d", sinSkill.SkillPoint);
				dsTextLineOut(0, CheckEditSize(165, 253, strBuff), 578 + (256 - sinMoveKindInter[SIN_SKILL]), strBuff, lstrlen(strBuff), Color);

				wsprintf(strBuff, "%d", sinSkill.SkillPoint4);
				dsTextLineOut(0, CheckEditSize(250, 253, strBuff), 578 + (256 - sinMoveKindInter[SIN_SKILL]), strBuff, lstrlen(strBuff), Color);
			}

			if (SkillMasteryShowFlag)
			{
				MasteryLen = lstrlen(szUseSkillMastery);
				lstrcpy(strBuff, szUseSkillMastery);
				MasteryShowX = UseSkillMasteryPosi.x + (12 / MasteryLen);

				if (MasteryLen <= 2)
					MasteryShowX += 4;
				dsTextLineOut(0, MasteryShowX, UseSkillMasteryPosi.y + 6 + (256 - sinMoveKindInter[SIN_SKILL]), strBuff, lstrlen(strBuff), Color);
			}
		}

		int SetTextXposi = 0, SetTextXposi2 = 0;
		char *pSkillInfo[40];
		char *pSkillInfo2[40];
		int len = 0, len2 = 0;
		int Count = 0;
		int Textlen = 0, Textlen2 = 0;
		int TempCnt = 0, TempCnt2 = 0;

		char szSkillInfoBuffBack[5000];
		char szSkillInfoBuff2Back[5000];

		lstrcpy(szSkillInfoBuffBack, szSkillInfoBuff);
		lstrcpy(szSkillInfoBuff2Back, szSkillInfoBuff2);

		len = lstrlen(szSkillInfoBuff);
		len2 = lstrlen(szSkillInfoBuff2);

		Color = D3DCOLOR_XRGB(255, 255, 255);

		if (SkillInfoShowFlag && !ShowSkillUpInfo)
		{
			if (SkillInfoShowFlag == 2)
				dsDrawOffsetArray = dsARRAY_TOP;
			for (int i = 0; i < len; i++)
			{
				for (int j = 0; j < len2; j++)
				{
					if (szSkillInfoBuffBack[i] == '\r')
					{
						if (szSkillInfoBuff2Back[j] == '\r')
						{
							pSkillInfo[Count] = &szSkillInfoBuffBack[TempCnt];
							pSkillInfo2[Count] = &szSkillInfoBuff2Back[TempCnt2];
							TempCnt = i + 1;
							TempCnt2 = j + 1;
							szSkillInfoBuffBack[i] = 0;
							szSkillInfoBuff2Back[j] = 0;

							Textlen = lstrlen(pSkillInfo[Count]);
							Textlen2 = lstrlen(pSkillInfo2[Count]);

							//SetTextXposi = (SkillInfoBoxPosi.x + 120) - ((Textlen/2)*11);

							SetTextXposi = (SkillInfoBoxPosi.x + 25);
							//SetTextXposi2 = (SkillInfoBoxPosi.x + 120)+10;

							SetTextXposi2 = (SkillInfoBoxPosi.x + GetTextWidth(0, pSkillInfo[Count]) + 25);

							if (Textlen2 > 0)
							{
								if (Textlen > 8)
									SetTextXposi--;
								if (Textlen > 10)
									SetTextXposi -= 2;
							}
							if (Textlen2 < 1)
								SetTextXposi = (SkillInfoBoxPosi.x) + (((SkillBoxSize.x * 16) - ((Textlen / 2) * 11)) / 2) - 10;

							if (Textlen2 > 12)
							{
								SetTextXposi -= 12;
								SetTextXposi2 -= 12;
							}
							Color = D3DCOLOR_XRGB(239, 190, 109);
							BoldFlag = 0;
							if (Count + 1 == 1)
							{
								dsTextLineOut(1, SetTextXposi, SkillInfoBoxPosi.y + 27 + ((Count - 1) * 14), pSkillInfo[Count], Textlen, D3DCOLOR_XRGB(222, 231, 255));
								BoldFlag = 1;
							}

							for (int t = 0; t < 6; t++)
							{
								if (Count + 1 == SkillDocLineCnt[t])
									Color = D3DCOLOR_XRGB(255, 255, 255);
							}
							if (Count + 1 == NextSkillLevelLine)
								Color = D3DCOLOR_XRGB(255, 220, 0);

							if (Count + 1 == SkillUseWeaponClass)
								Color = D3DCOLOR_XRGB(164, 199, 41);

							if (SkillMasterFlag == 1)
							{
								if (Count == SkillInfoLineCnt - 1)
									Color = D3DCOLOR_XRGB(247, 243, 193);
							}
							if (MonsterDamageLine && Count + 1 == MonsterDamageLine)
								Color = D3DCOLOR_XRGB(220, 120, 255);

							if (ChainDamageLine && Count + 1 == ChainDamageLine)
								Color = D3DCOLOR_XRGB(170, 170, 255);

							if (!BoldFlag)
							{
								dsTextLineOut(0, SetTextXposi, SkillInfoBoxPosi.y + 28 + ((Count - 1) * 15), pSkillInfo[Count], Textlen, Color);
								dsTextLineOut(0, SetTextXposi2, SkillInfoBoxPosi.y + 28 + ((Count - 1) * 15), pSkillInfo2[Count], Textlen2, Color);
								dsTextLineOut(0, SetTextXposi2 + 1, SkillInfoBoxPosi.y + 28 + ((Count - 1) * 15), pSkillInfo2[Count], Textlen2, Color);
							}
							Count++;
							break;
						}
					}
				}
			}
		}

		SetTextXposi = 0;
		SetTextXposi2 = 0;

		Count = 0;
		Textlen = 0;
		Textlen2 = 0;
		TempCnt = 0;
		TempCnt2 = 0;
		char *pSkillMasterInfo[40];
		char *pSkillMasterInfo2[40];

		char TempSkillInfo[5000];
		char TempSkillInfo2[5000];


		Color = D3DCOLOR_XRGB(255, 255, 255);
		lstrcpy(TempSkillInfo, szSkillMasterInfoBuff);
		lstrcpy(TempSkillInfo2, szSkillMasterInfoBuff2);

		len = lstrlen(szSkillMasterInfoBuff);
		len2 = lstrlen(szSkillMasterInfoBuff2);

		int dsDrawOffsetArrayBackup = dsDrawOffsetArray;

		if (ShowSkillUpInfo)
		{
			dsDrawOffsetArray = dsARRAY_TOP;
			for (int i = 0; i < len; i++)
			{
				for (int j = 0; j < len2; j++)
				{
					if (TempSkillInfo[i] == '\r')
					{
						if (TempSkillInfo2[j] == '\r')
						{
							pSkillMasterInfo[Count] = &TempSkillInfo[TempCnt];
							pSkillMasterInfo2[Count] = &TempSkillInfo2[TempCnt2];

							TempCnt = i + 1;
							TempCnt2 = j + 1;

							TempSkillInfo[i] = 0;
							TempSkillInfo2[j] = 0;
							Textlen = lstrlen(pSkillMasterInfo[Count]);
							Textlen2 = lstrlen(pSkillMasterInfo2[Count]);

							SetTextXposi = (SkillUpInfoPosi.x + 120) - ((Textlen / 2) * 11);
							SetTextXposi2 = (SkillUpInfoPosi.x + 120) + 10;

							if (Textlen2 > 0)
							{
								if (Textlen > 8)
									SetTextXposi--;
								if (Textlen > 10)
									SetTextXposi -= 2;
							}
							if (Textlen2 < 1)
								SetTextXposi = (SkillUpInfoPosi.x) + (((SkillUpInfo.x * 16) - ((Textlen / 2) * 11)) / 2) - 10;

							Color = D3DCOLOR_XRGB(239, 190, 109);

							BoldFlag = 0;
							if (Count + 1 == 1)
							{
								dsTextLineOut(1, SetTextXposi, SkillUpInfoPosi.y + 27 + ((Count - 1) * 14), pSkillMasterInfo[Count], Textlen, D3DCOLOR_XRGB(222, 231, 255));
								BoldFlag = 1;
							}

							for (int t = 0; t < 6; t++)
							{
								if (Count + 1 == SkillDocLineCnt[t])
									Color = D3DCOLOR_XRGB(255, 255, 255);
							}
							if (Count + 1 == NextSkillLevelLine)
								Color = D3DCOLOR_XRGB(255, 220, 0);

							if (Count + 1 == SkillUseWeaponClass)
								Color = D3DCOLOR_XRGB(164, 199, 41);

							if (SkillMasterFlag == 1)
							{
								if (Count == SkillInfoLineCnt - 1)
									Color = D3DCOLOR_XRGB(247, 243, 193);
							}

							if (!BoldFlag)
							{
								dsTextLineOut(0, SetTextXposi, SkillUpInfoPosi.y + 28 + ((Count - 1) * 15), pSkillMasterInfo[Count], Textlen, Color);
								dsTextLineOut(0, SetTextXposi2, SkillUpInfoPosi.y + 28 + ((Count - 1) * 15), pSkillMasterInfo2[Count], Textlen2, Color);
								dsTextLineOut(0, SetTextXposi2 + 1, SkillUpInfoPosi.y + 28 + ((Count - 1) * 15), pSkillMasterInfo2[Count], Textlen2, Color);
							}
							Count++;
							break;
						}
					}
				}
			}
			dsDrawOffsetArray = dsDrawOffsetArrayBackup;
		}
	}
}

int JobSkillTemp = 0;

void cSKILL::CheckingNowSkillState()
{
	switch (sinChar->iRank)
	{
	case 0:
		ChangeJobSkillPlus = 5;
		break;
	case 1:
		ChangeJobSkillPlus = 9;
		break;
	case 2:
		ChangeJobSkillPlus = 13;
		break;
	case 3:
		ChangeJobSkillPlus = 17;
		break;
	case 4:
		ChangeJobSkillPlus = 21;
		break;
	}
	if (JobSkillTemp != ChangeJobSkillPlus)
	{
		JobSkillTemp = ChangeJobSkillPlus;
		cInvenTory.SetItemToChar();
	}

	for (int j = 0; j < ChangeJobSkillPlus; j++)
	{
		if (j > 12)
		{
			if (sinSkill.SkillPoint4)
			{
				sinSkill.UseSkill[j].Flag = 1;

				if (sinSkill.UseSkill[j].Point <= MAX_USE_SKILL_POINT)
				{
					if (sinSkill.UseSkill[j - 1].Point)
					{
						if (sinSkill.UseSkill[j].Skill_Info.RequireLevel + (sinSkill.UseSkill[j].Point * 2) <= sinChar->iLevel)
							sinSkill.UseSkill[j].Use = 1;
						else
							sinSkill.UseSkill[j].Use = 0;
					}
				}
			}
			else
				sinSkill.UseSkill[j].Use = 0;
			continue;
		}
		if (sinSkill.SkillPoint)
		{
			sinSkill.UseSkill[j].Flag = 1;
			if (sinSkill.UseSkill[j].Point <= MAX_USE_SKILL_POINT)
			{
				if (j == 0)continue;

				if (sinSkill.UseSkill[j - 1].Point)
				{
					if (sinSkill.UseSkill[j].Skill_Info.RequireLevel + (sinSkill.UseSkill[j].Point * 2) <= sinChar->iLevel)
						sinSkill.UseSkill[j].Use = 1;
					else
						sinSkill.UseSkill[j].Use = 0;
				}
			}
		}
		else
			sinSkill.UseSkill[j].Use = 0;
	}
}
void cSKILL::CheckSkillMastery()
{
	int TempLenght = 0;

	int TempTalent = 0;

	if (sinSkill.pLeftSkill)
	{
		if (!sinSkill.pLeftSkill->Point)
			sinSkill.pLeftSkill->UseSkillFlag = 0;
	}
	if (sinSkill.pRightSkill)
	{
		if (!sinSkill.pRightSkill->Point)
			sinSkill.pRightSkill->UseSkillFlag = 0;
	}

	for (int j = 1; j < SIN_MAX_USE_SKILL; j++)
	{
		if (sinSkill.UseSkill[j].Flag && sinSkill.UseSkill[j].Point)
		{
			CheckSkillMasteryForm(0, j);

			if (sinSkill.UseSkill[j].Mastery == 0)
			{
				sinSkill.UseSkill[j].GageLength = 0;
				sinSkill.UseSkill[j].GageLength2 = 0;
				SkillCountTime2[j] = 0;
			}

			TempTalent = (int)(sinChar->iTalent / 3) + (int)sinAdd_fMagic_Mastery;
			if (TempTalent > 50)
				TempTalent = 50;

			sinSkill.UseSkill[j].UseSkillMastery = (int)(TempTalent * 100) + sinSkill.UseSkill[j].UseSkillCount;

			if (sinSkill.UseSkill[j].Skill_Info.Element[0])
				sinSkill.UseSkill[j].UseSkillMastery = 10000;

			if (sinSkill.UseSkill[j].UseSkillMastery >= 10000)
				sinSkill.UseSkill[j].UseSkillMastery = 10000;
			if (sinSkill.UseSkill[j].UseSkillMastery)
			{
				sinSkill.UseSkill[j].UseSkillMasteryGage = (int)((35 * ((float)sinSkill.UseSkill[j].UseSkillMastery / 10000)));
				if (sinSkill.UseSkill[j].UseSkillMasteryGage > 35)
					sinSkill.UseSkill[j].UseSkillMasteryGage = 35;
			}

			sinSkill.UseSkill[j].Mastery = (sinSkill.UseSkill[j].Skill_Info.RequireMastery[0] + (sinSkill.UseSkill[j].Skill_Info.RequireMastery[1] * sinSkill.UseSkill[j].Point) - (sinSkill.UseSkill[j].UseSkillMastery / 100));
			if (sinSkill.UseSkill[j].Mastery <= 0)
				sinSkill.UseSkill[j].Mastery = 1;
			if (sinSkill.UseSkill[j].Mastery > 70)
				sinSkill.UseSkill[j].Mastery = 70;

			if (sinAddSkillDelay)
				sinSkill.UseSkill[j].Mastery = 1;
			else
			{
				sinSkill.UseSkill[j].Mastery = (sinSkill.UseSkill[j].Skill_Info.RequireMastery[0] + (sinSkill.UseSkill[j].Skill_Info.RequireMastery[1] * sinSkill.UseSkill[j].Point) - (sinSkill.UseSkill[j].UseSkillMastery / 100));

				if (sinSkill.UseSkill[j].Mastery <= 0)
					sinSkill.UseSkill[j].Mastery = 1;
				if (sinSkill.UseSkill[j].Mastery > 70)
					sinSkill.UseSkill[j].Mastery = 70;
			}

			TempLenght = (int)(35 / ((float)sinSkill.UseSkill[j].Mastery / 2));

			sinSkill.UseSkill[j].GageLength2 += TempLenght;

			if (sinSkill.UseSkill[j].GageLength < sinSkill.UseSkill[j].GageLength2)
			{
				SkillCountTime2[j]++;
				if (SkillCountTime2[j] >= (int)(35 / (float)TempLenght))
				{
					sinSkill.UseSkill[j].GageLength++;
					SkillCountTime2[j] = 0;
				}
			}

			if (sinSkill.UseSkill[j].GageLength >= 35)
			{
				sinSkill.UseSkill[j].GageLength = 35;
				sinSkill.UseSkill[j].GageLength2 = 35;
				sinSkill.UseSkill[j].UseSkillFlag = 1;
				CheckUseSkillState(&sinSkill.UseSkill[j]);
			}
			else
				sinSkill.UseSkill[j].UseSkillFlag = 0;

			ReformSkillMasteryForm(0, j);
		}
	}
}

DWORD UseSkillItemInfo[12] = { 0,sinWA1,sinWM1,sinWH1,sinDS1,sinWP1,sinWS2,sinWC1,sinWS1,sinWT1,sinWD1,sinWN1 };

//技能信息显示
int cSKILL::ShowSkillInfo(sSKILL *pSkill, sSKILLBOX *pSkillBox, int Icon)
{
	if (ShowSkillUpInfo)
		return TRUE;

	int PlusMinD = 0;
	int PlusMaxD = 0;

	int DivideMin = 8;
	int DivideMax = 4;

	int sinTemp1 = 0;
	int sinTemp2 = 0;
	int LeftSpot = 0;
	int RightSpot = 0;

	int TempPoint = 0;
	int TempPoint2 = 0;

	int i = 0;
	int j = 0;
	int p = 0;

	int TempLife = 0, TempMana = 0;

	int LineCount = 0;
	int Minute = 0;
	int Sec = 0;

	for (p = 0; p < 6; p++)
		SkillDocLineCnt[p] = 0;
	for (p = 0; p < 10; p++)
		SkillIconIndex[p] = 0;
	int CopyCount = 0;
	int	SkillDoclen = 0;
	NextSkillLevelLine = 0;
	SkillUseWeaponClass = 0;
	SkillInconCnt = 0;
	char szTempSkillDoc[256];
	char szTempSkillDoc2[256];

	char *szTemp = "\r";

	memset(&szTempSkillDoc, 0, sizeof(szTempSkillDoc));
	memset(&szTempSkillDoc2, 0, sizeof(szTempSkillDoc2));
	memset(&szSkillInfoBuff, 0, sizeof(szSkillInfoBuff));
	memset(&szSkillInfoBuff2, 0, sizeof(szSkillInfoBuff2));

	if (pSkill->CODE == SKILL_NORMAL_ATTACK)
	{
		wsprintf(szSkillInfoBuff, "%s\r", "Default Attack"); // 普通攻击
		lstrcpy(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		GetInfoBoxSize(pSkillBox, LineCount);
		return TRUE;
	}

	if (pSkill->Point)
	{
		if (pSkill->CODE == SKILL_FORCE_ORB || pSkill->CODE == SKILL_CRYSTAL_ORB || pSkill->CODE == SKILL_WARNING_TIME || pSkill->CODE == CHANGE_JOB3_QUEST || pSkill->CODE == CHANGE_ELEMENTARY_QUEST)
			wsprintf(szSkillInfoBuff, "%s\r", pSkill->Skill_Info.SkillName);
		else
			wsprintf(szSkillInfoBuff, "%s LV:%d\r", pSkill->Skill_Info.SkillName, pSkill->Point);

		lstrcpy(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;

		if (pSkill->Point < 10)
		{
			if (!Icon)
			{
				wsprintf(szTempSkillDoc2, "(Req. LVL:%d)\r", pSkill->Skill_Info.RequireLevel + (pSkill->Point * 2));
				lstrcat(szSkillInfoBuff, szTempSkillDoc2);
				lstrcpy(szTempSkillDoc2, "\r");
				lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
				LineCount++;
			}
		}
	}
	else
	{
		if (pSkill->CODE == CLANSKILL_ABSORB || pSkill->CODE == CLANSKILL_EVASION || pSkill->CODE == CLANSKILL_ATTACK ||
			pSkill->CODE == SCROLL_INVULNERABILITY || pSkill->CODE == SCROLL_CRITICAL || pSkill->CODE == SCROLL_EVASION ||
			pSkill->CODE == STONE_R_FIRECRYTAL || pSkill->CODE == STONE_R_ICECRYTAL || pSkill->CODE == STONE_R_LINGHTINGCRYTAL ||
			pSkill->CODE == STONE_A_FIGHTER || pSkill->CODE == STONE_A_MECHANICIAN || pSkill->CODE == STONE_A_PIKEMAN || pSkill->CODE == STONE_A_ARCHER ||
			pSkill->CODE == STONE_A_KNIGHT || pSkill->CODE == STONE_A_ATALANTA || pSkill->CODE == STONE_A_MAGICIAN || pSkill->CODE == STONE_A_PRIESTESS || pSkill->CODE == STONE_A_ASSASSIN || pSkill->CODE == STONE_A_SAMAN ||
			pSkill->CODE == SCROLL_P_INVULNERABILITY || pSkill->CODE == SCROLL_P_CRITICAL || pSkill->CODE == SCROLL_P_EVASION ||
			pSkill->CODE == BOOSTER_ITEM_LIFE || pSkill->CODE == BOOSTER_ITEM_MANA || pSkill->CODE == BOOSTER_ITEM_STAMINA)
			wsprintf(szSkillInfoBuff, "%s\r", pSkill->Skill_Info.SkillName);
		else
			wsprintf(szSkillInfoBuff, "%s (Required Level:%d)\r", pSkill->Skill_Info.SkillName, pSkill->Skill_Info.RequireLevel + (pSkill->Point * 2));

		lstrcpy(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
	}

	SkillDoclen = lstrlen(pSkill->Skill_Info.SkillDoc);

	BYTE ch;
	int StrCnt;
	int cnt, cnt2;

	cnt2 = 0;
	StrCnt = 0;

	for (cnt = 0; cnt < SkillDoclen; cnt++)
	{
		ch = (BYTE)pSkill->Skill_Info.SkillDoc[cnt];

		if (ch >= 0x80)
		{
			szTempSkillDoc[cnt2++] = pSkill->Skill_Info.SkillDoc[cnt++];
			szTempSkillDoc[cnt2++] = pSkill->Skill_Info.SkillDoc[cnt];
			StrCnt += 2;
		}
		else
		{
			szTempSkillDoc[cnt2++] = pSkill->Skill_Info.SkillDoc[cnt];
			StrCnt++;
		}
		if (StrCnt > 30)
		{
			StrCnt = 0;
			szTempSkillDoc[cnt2++] = '\r';
			lstrcpy(szTempSkillDoc2, "\r");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			SkillDocLineCnt[LineCount - 2] = LineCount;
		}
	}
	SkillDocLineCnt[LineCount + 1 - 2] = LineCount + 1;
	lstrcat(szSkillInfoBuff, szTempSkillDoc);
	lstrcat(szSkillInfoBuff, szTemp);
	lstrcpy(szTempSkillDoc2, "\r");
	lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
	LineCount++;

	if (pSkill->CODE == SCROLL_P_CRITICAL || pSkill->CODE == SCROLL_P_EVASION)
	{
		lstrcpy(szTempSkillDoc, "Duration:\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		wsprintf(szTempSkillDoc2, "%d%s\r", 3600, "secs");
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
	}
	else if (pSkill->CODE == BOOSTER_ITEM_LIFE || pSkill->CODE == BOOSTER_ITEM_MANA || pSkill->CODE == BOOSTER_ITEM_STAMINA)
	{
		lstrcpy(szTempSkillDoc, "Duration:\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		wsprintf(szTempSkillDoc2, "%d%s\r", pSkill->UseTime, "secs");
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
	}

	lstrcat(szSkillInfoBuff, "\r");
	lstrcpy(szTempSkillDoc2, "\r");
	lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
	LineCount++;

	if (pSkill->Skill_Info.UseWeaponCode[0])
	{
		lstrcpy(szTempSkillDoc, "Compatible Item Group\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcpy(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		SkillUseWeaponClass = LineCount;
		for (i = 0; i < 10; i++)
		{
			if (pSkill->Skill_Info.UseWeaponCode[i])
			{
				for (int j = 0; j < 12; j++)
				{
					if (pSkill->Skill_Info.UseWeaponCode[i] == UseSkillItemInfo[j])
					{
						SkillIconIndex[i] = j;
						SkillIconPosi.y = (LineCount * 17) + 2;
						SkillInconCnt++;
					}
				}
			}
		}
	}
	if (SkillInconCnt)
	{
		SkillIconPosi.x = ((14 * 16) - (SkillInconCnt * 18)) / 2;
		lstrcat(szSkillInfoBuff, "\r");
		lstrcpy(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		lstrcat(szSkillInfoBuff, "\r");
		lstrcpy(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
	}

	MonsterDamageLine = 0;
	ChainDamageLine = 0;

	switch (pSkill->CODE)
	{
		//机械榴弹
	case SKILL_MECHANIC_BOMB:
		wsprintf(szTempSkillDoc, "(%s.%s VS %d%s %s", "Mutant", "Mechanic", 500, "%", "add extra damage)\r");
		lstrcpy(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		MonsterDamageLine = LineCount;
		break;
		//灵光飞扬
	case SKILL_SPARK:
		wsprintf(szTempSkillDoc, "(%s VS %d%s %s", "Mechanic", 50, "%", "add extra damage)\r");
		lstrcpy(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		MonsterDamageLine = LineCount;
		break;
		//金属装甲
	case SKILL_METAL_ARMOR:
		wsprintf(szTempSkillDoc, "(%s %d%s %s", "PhysicalAbsorb", 200, "%", "ChainDamage)\r");
		lstrcpy(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		ChainDamageLine = LineCount;
		break;
		//防御电波
	case SKILL_SPARK_SHIELD:
		wsprintf(szTempSkillDoc, "(%s VS %d%s %s", "Mechanic", 50, "%", "add extra damage)\r");
		lstrcpy(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		MonsterDamageLine = LineCount;
		break;
		//雷霆冲击
	case SKILL_IMPULSION:
		wsprintf(szTempSkillDoc, "(%s VS %d%s %s", "Mechanic", 50, "%", "add extra damage)\r");
		lstrcpy(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		MonsterDamageLine = LineCount;
		break;
		//磁性电球
	case SKILL_MAGNETIC_SPHERE:
		wsprintf(szTempSkillDoc, "(%s VS %d%s %s", "Mechanic", 30, "%", "add extra damage)\r");
		lstrcpy(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		MonsterDamageLine = LineCount;
		break;
		//究极之刃
	case SKILL_R_SMASH:
		wsprintf(szTempSkillDoc, "(%s %d%s %s", "Grand Smash of Rating ", 100, "%", "ChainDamage)\r");
		lstrcpy(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		ChainDamageLine = LineCount;
		break;
		//致命回旋
	case SKILL_BRUTAL_SWING:
		wsprintf(szTempSkillDoc, "(%s VS %d%s %s", "Demon", 40, "%", "add extra damage)\r");
		lstrcpy(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		MonsterDamageLine = LineCount;
		break;
		//复仇连击
	case SKILL_AVANGING_CRASH:
		wsprintf(szTempSkillDoc, "(%s %d%s %s", "BrutalSwingCritical", 50, "%", "ChainDamage)\r");
		lstrcpy(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		ChainDamageLine = LineCount;
		break;
		//破坏连击
	case SKILL_DETORYER:
		wsprintf(szTempSkillDoc, "(%s VS %d%s %s", "Demon", 30, "%", "add extra damage)\r");
		lstrcpy(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		MonsterDamageLine = LineCount;
		break;
		//霹雳一击
	case SKILL_JUMPING_CRASH:
		wsprintf(szTempSkillDoc, "(%s VS %d%s %s", "Demon", 30, "%", "add extra damage)\r");
		lstrcpy(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		MonsterDamageLine = LineCount;
		break;
		//无限力枪
	case SKILL_EXPANSION:
		wsprintf(szTempSkillDoc, "(%s VS %d%s %s", "Mutant", 30, "%", "add extra damage)\r");
		lstrcpy(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		MonsterDamageLine = LineCount;
		break;
		//疾风之箭
	case SKILL_WIND_ARROW:
		wsprintf(szTempSkillDoc, "(%s VS %d%s %s", "Normal", 30, "%", "add extra damage)\r");
		lstrcpy(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		MonsterDamageLine = LineCount;
		break;
		//夺命之箭
	case SKILL_PERFECT_AIM:
		wsprintf(szTempSkillDoc, "(%s VS %d%s %s", "Demon", 30, "%", "add extra damage)\r");
		lstrcpy(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		MonsterDamageLine = LineCount;
		break;
		//魔神剑
	case SKILL_SWORD_BLAST:
		wsprintf(szTempSkillDoc, "(%s.%s VS %d%s %s", "Normal", "Mutant", 30, "%", "add extra damage)\r");
		lstrcpy(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		MonsterDamageLine = LineCount;
		break;
		//一雾银
	case SKILL_PIERCING:
		wsprintf(szTempSkillDoc, "(%s VS %d%s %s", "Mutant", 30, "%", "add extra damage)\r");
		lstrcpy(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		MonsterDamageLine = LineCount;
		break;
		//敬神之盾
	case SKILL_GODLY_SHIELD:
		wsprintf(szTempSkillDoc, "(%s %d%s %s", "Blocking rate of divine shiled", 100, "%", "ChainDamage)\r");
		lstrcpy(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		ChainDamageLine = LineCount;
		break;
		//螺旋飞标
	case SKILL_TWIST_JAVELIN:
		wsprintf(szTempSkillDoc, "(%s VS %d%s %s", "Demon", 30, "%", "add extra damage)\r");
		lstrcpy(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		MonsterDamageLine = LineCount;
		break;
		//火焰烈枪
	case SKILL_FIRE_JAVELIN:
		wsprintf(szTempSkillDoc, "(%s VS %d%s %s", "Mutant", 50, "%", "add fire element damage)\r");
		lstrcpy(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		MonsterDamageLine = LineCount;
		break;
		//光猎之枪
	case SKILL_LIGHTNING_JAVELIN:
		wsprintf(szTempSkillDoc, "(%s VS %d%s %s", "Undead", 50, "%", "add extra damage)\r");
		lstrcpy(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		MonsterDamageLine = LineCount;
		break;
		//瓦尔哈拉之光
	case SKILL_HALL_OF_VALHALLA:
		wsprintf(szTempSkillDoc, "(%s %d%s %s", "Triumph", 100, "%", "ChainDamage)\r");
		lstrcpy(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		ChainDamageLine = LineCount;
		break;
		//神圣法阵
	case SKILL_T_ANIMA:
		wsprintf(szTempSkillDoc, "(%s %d%s %s", "Spirit Elemental", 100, "%", "ChainDamage)\r");
		lstrcpy(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		ChainDamageLine = LineCount;
		break;
	}
	for (i = 0; i < 2; i++)
	{
		if (i == 1 && Icon)
			break;
		if (i == 1 && pSkill->Point == MAX_USE_SKILL_POINT)
			break;
		if (i == 0 && !pSkill->Point)
			continue;
		if (i == 1)
		{
			lstrcat(szSkillInfoBuff, "Next Level\r");
			lstrcpy(szTempSkillDoc2, "\r");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			NextSkillLevelLine = LineCount;
		}
		switch (pSkill->CODE)
		{
			//极光护盾
		case SKILL_EXTREME_SHIELD:
			lstrcpy(szTempSkillDoc, "Block Rating Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", E_Shield_BlockRate[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", E_Shield_UseTime[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//机械榴弹
		case SKILL_MECHANIC_BOMB:
			lstrcpy(szTempSkillDoc, "Attack Power:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d\r", Mechanic_Bomb_Damage[pSkill->Point + i - 1][0], Mechanic_Bomb_Damage[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Mechanic_Bomb_Attack_Range[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			// 毒之防御
		case SKILL_POISON_ATTRIBUTE:
			lstrcpy(szTempSkillDoc, "Poison Type:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", PlusPoison[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcat(szSkillInfoBuff, "\r");
			lstrcpy(szTempSkillDoc2, "\r");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//灵光护体
		case SKILL_PHYSICAL_ABSORB:
			lstrcpy(szTempSkillDoc, "Absorb Rating Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", P_Absorb[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", P_Absorb_UseTime[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			// 破碎巨击
		case SKILL_GREAT_SMASH:
			lstrcpy(szTempSkillDoc, "Attack Rating Increases:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", G_Smash_Attack_Rate[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Increased maximum damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d\r", G_Smash_Attack_Rage[pSkill->Point + i - 1], G_Smash_Attack_Rage[pSkill->Point + i - 1] + sinChar->iStrength / 5);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", G_Smash_Attack_Rage[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			// 改良专家
		case SKILL_MAXIMIZE:
			lstrcpy(szTempSkillDoc, "Max Damage Boost");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Maximize_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Maximize_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//灵光飞扬
		case SKILL_AUTOMATION:
			lstrcpy(szTempSkillDoc, "Damage Boost");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Automation_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Attack Speed:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Automation_Speed[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Automation_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//火花电场
		case SKILL_SPARK:
			lstrcpy(szTempSkillDoc, "Spark Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d+(LV × 4)\r", Spark_Damage[pSkill->Point + i - 1][0], Spark_Damage[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Area Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Spark_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//金属重甲
		case SKILL_METAL_ARMOR:
			lstrcpy(szTempSkillDoc, "Armor Defense Rating Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Metal_Armor_Defense[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Metal_Armor_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//星光灭绝
		case SKILL_GRAND_SMASH:
			lstrcpy(szTempSkillDoc, "Added Attack Rating:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Grand_Smash_AttackRate[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Grand_Smash_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//优化专家
		case SKILL_MECHANIC_WEAPON:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", M_Weapon_Mastey[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcat(szSkillInfoBuff, "\r");
			lstrcpy(szTempSkillDoc2, "\r");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//防御电波
		case SKILL_SPARK_SHIELD:
			lstrcpy(szTempSkillDoc, "Reflect Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Spark_Shield_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Defense Rating:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Spark_Shield_Defense[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Spark_Shield_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//雷霆冲击
		case SKILL_IMPULSION:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Impulsion_LightingDamage[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Impulsion_Range[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Number of Sparks:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Impulsion_LightingNum[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//威慑怒吼
		case SKILL_COMPULSION:
			lstrcpy(szTempSkillDoc, "Extra Absorb:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Compulsion_AddAbsorb[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Magnetic Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Compulsion_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Compulsion_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//磁性球体
		case SKILL_MAGNETIC_SPHERE:
			lstrcpy(szTempSkillDoc, "Sphere Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d\r", Magnetic_Sphere_AddDamage[pSkill->Point + i - 1][0], Magnetic_Sphere_AddDamage[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Magnetic_Sphere_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Attack Interval:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Magnetic_Sphere_AttackDelay[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Magnetic_Sphere_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//终极机械
		case SKILL_METAL_GOLEM:
			lstrcpy(szTempSkillDoc, "Attack Type:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			lstrcpy(szTempSkillDoc2, sinAttackType2[pSkill->SkillCodeIndex]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Attack Power:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d\r", Metal_Golem_Damage[pSkill->Point + i - 1][0], Metal_Golem_Damage[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Attack Rating:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Metal_Golem_Hit[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Health:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d+(%d)\r", Metal_Golem_Life[pSkill->Point + i - 1], (sinChar->iStrength * 2));
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Defense:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Metal_Golem_Defense[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", 360, "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//霹雳旋风
		case SKILL_LANDMINNING:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Landminning_AddDamage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Attack Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Landminning_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Max Hits:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Landminning_Num[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//快速打击
		case SKILL_H_SONIC:
			lstrcpy(szTempSkillDoc, "Attack Speed Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", H_Sonic_Speed[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", H_Sonic_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//究极之刃
		case SKILL_R_SMASH:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", R_Smash_AddDamage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//战神祝福
		case SKILL_P_ENHENCE:
			lstrcpy(szTempSkillDoc, "Attack Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s-%d%s\r", P_Enhence_AddDamage[pSkill->Point + i - 1][0], "%", P_Enhence_AddDamage[pSkill->Point + i - 1][1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Defense Rating:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", P_Enhence_Defanse[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", P_Enhence_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//武士
			//格斗之术
		case SKILL_MELEE_MASTERY:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Melee_Mastery_DamagePercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcat(szSkillInfoBuff, "\r");
			lstrcpy(szTempSkillDoc2, "\r");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//火之防御
		case SKILL_FIRE_ATTRIBUTE:
			lstrcpy(szTempSkillDoc, "Fire Type:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", PlusFire[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcat(szSkillInfoBuff, "\r");
			lstrcpy(szTempSkillDoc2, "\r");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//绝地暴走
		case SKILL_RAVING:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Raving_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Number of Hits:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Ravind_Speed[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "HP Reduction:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			sinTemp1 = (int)(Raving_UseLife[pSkill->Point + i - 1] * 10);
			RightSpot = sinTemp1 % 10;
			LeftSpot = (sinTemp1 - RightSpot) / 10;
			wsprintf(szTempSkillDoc2, "%d.%d%s\r", LeftSpot, RightSpot, "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//精准之击
		case SKILL_IMPACT:
			lstrcpy(szTempSkillDoc, "Added Attack Rating:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Impact_Attack_Rating[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Impact_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//威力冲击
		case SKILL_TRIPLE_IMPACT:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", T_Impact_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Number of Hits:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", T_Impact_Hit[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//致命回旋
		case SKILL_BRUTAL_SWING:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", B_Swing_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Added Critical:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", B_Swing_Critical[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//极地怒吼
		case SKILL_ROAR:
			lstrcpy(szTempSkillDoc, "Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Roar_Range[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Stun Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Roar_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//战神之怒
		case SKILL_RAGE_OF_ZECRAM:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", R_Zecram_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", R_Zecram_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//会心一击
		case SKILL_CONCENTRATION:
			lstrcpy(szTempSkillDoc, "Added Attack Rating:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Concentration_AttackRate[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Concentration_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//复仇连击
		case SKILL_AVANGING_CRASH:
			lstrcpy(szTempSkillDoc, "Attack Rating Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", A_Crash_AttackRate[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", A_Crash_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//刺杀之斧
		case SKILL_SWIFT_AXE:
			lstrcpy(szTempSkillDoc, "Weapon Speed Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Swift_Axe_Speed[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Swift_Axe_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//挫骨扬灰
		case SKILL_BONE_CRASH:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", B_Crash_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Damage Boost VS. Demons:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", B_Crash_DemonDamage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//破坏之击
		case SKILL_DETORYER:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Destoryer_DamagePercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Added Critical:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Destoryer_AddCritical[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//疯狂怒吼
		case SKILL_BERSERKER:
			lstrcpy(szTempSkillDoc, "Added Attack Power:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Berserker_AddAttack[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Absorption:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Berserker_SubAbsorb[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Berserker_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//飓风袭击
		case SKILL_CYCLONE_STRIKE:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Cyclone_Strike_DamagePercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Enemies:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Cyclone_Strike_AttackNum[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Attack Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Cyclone_Strike_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//健康专家
		case SKILL_BOOST_HEALTH:
			lstrcpy(szTempSkillDoc, "Added HP:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Boost_Health_Life[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcat(szSkillInfoBuff, "\r");
			lstrcpy(szTempSkillDoc2, "\r");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//狂暴怒斩
		case SKILL_D_HIT:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", D_Hit_AddDamage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//狂野冲击
		case SKILL_P_DASH:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", P_Dash_AddDamage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Attack Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", P_Dash_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//回旋斩击
		case SKILL_M_BLOW:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", M_Blow_AddDamage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Max Hits:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", M_Blow_AttackNum[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Attack Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", M_Blow_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//众神之怒
		case SKILL_B_BERSERKER:
			lstrcpy(szTempSkillDoc, "Added Critical:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", B_Berserker_AddDamage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", B_Berserker_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//龙卷枪风
		case SKILL_PIKE_WIND:
			lstrcpy(szTempSkillDoc, "Attack Power:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d\r", Pike_Wind_Damage[pSkill->Point + i - 1][0], Pike_Wind_Damage[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Push back length:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Pike_Wind_Push_Lenght[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//冰之防御
		case SKILL_ICE_ATTRIBUTE:
			lstrcpy(szTempSkillDoc, "Frost Attribute:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", PlusIce[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcat(szSkillInfoBuff, "\r");
			lstrcpy(szTempSkillDoc2, "\r");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//致命打击
		case SKILL_CRITICAL_HIT:
			lstrcpy(szTempSkillDoc, "Critical:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Critical_Hit_Critical[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//霹雳一击
		case SKILL_JUMPING_CRASH:
			lstrcpy(szTempSkillDoc, "Attack Rating Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Jumping_Crash_Attack_Rating[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Jumping_Crash_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//大地之枪
		case SKILL_GROUND_PIKE:
			lstrcpy(szTempSkillDoc, "Freeze Time:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", G_Pike_Time[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Frost Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d\r", G_Pike_Damage[pSkill->Point + i - 1][0], G_Pike_Damage[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", G_Pike_Range[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//枪之飓风
		case SKILL_TORNADO:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Tornado_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Tornado_Range[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//躲避专家
		case SKILL_WEAPONE_DEFENCE_MASTERY:
			lstrcpy(szTempSkillDoc, "Block Rating:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", W_D_Mastery_Block[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcat(szSkillInfoBuff, "\r");
			lstrcpy(szTempSkillDoc2, "\r");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//无限力枪
		case SKILL_EXPANSION:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Expansion_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Weapon Size:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Expansion_Size[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//灵蛇标枪
		case SKILL_VENOM_SPEAR:
			lstrcpy(szTempSkillDoc, "Poison:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", VenomSpear_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Number of spears:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s", VenomSpear_Num[pSkill->Point + i - 1], "spears");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Poison Tim:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", VenomSpear_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", VenomSpear_Range[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//隐暗之术
		case SKILL_VANISH:
			lstrcpy(szTempSkillDoc, "After Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Vanish_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Visibility:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Vanish_Range[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Vanish_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//会心之枪
		case SKILL_CRITICAL_MASTERY:
			lstrcpy(szTempSkillDoc, "Added Critical:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Critical_Mastery_Critical[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcat(szSkillInfoBuff, "\r");
			lstrcpy(szTempSkillDoc2, "\r");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//链骑之枪
		case SKILL_CHAIN_LANCE:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Chain_Lance_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//暗杀之眼
		case SKILL_ASSASSIN_EYE:
			lstrcpy(szTempSkillDoc, "Critical Increase:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Assassin_Eye_AddCritical[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Monster Critical:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Assassin_Eye_M_SubCritical[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Assassin_Eye_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//转换打击
		case SKILL_CHARGING_STRIKE:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Charging_Strike_DamagePercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Added Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Charging_Strike_CharingDamagePercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Raise Speed:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			if ((pSkill->Point + i) == 1)
				wsprintf(szTempSkillDoc2, "%d%s\r", 0, "%");
			else
				wsprintf(szTempSkillDoc2, "%d%s\r", Charging_Strike_Time[(pSkill->Point + i - 1) - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//影隐之遁
		case SKILL_VAGUE:
			lstrcpy(szTempSkillDoc, "Evasion Increase:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Vague_EvasionPercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Vague_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//宇宙幻影
		case SKILL_SHADOW_MASTER:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Shadow_Master_DamagePercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Number of Hits:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Shadow_Master_ShadowNum[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//回旋打击
		case SKILL_D_REAPER:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", D_Reaper_AddDamage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//地枪奇袭
		case SKILL_F_SPEAR:
			lstrcpy(szTempSkillDoc, "Damage Boost: \r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", F_Spear_AddDamage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Number of spears:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s", F_Spear_Num[pSkill->Point + i - 1], "spears");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", F_Spear_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//潜能激发
		case SKILL_AMPLIFIED:
			lstrcpy(szTempSkillDoc, "Decrease Absorption:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Amplified_SubAbs[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Accuracy:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Amplified_AddHit[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Increase min.Attack Power:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Amplified_MinAddDamage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Amplified_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//旋风之枪
		case SKILL_SS_ATTACK:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", SS_Attack_AddDamage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//侦察之鹰
		case SKILL_SCOUT_HAWK:
			lstrcpy(szTempSkillDoc, "Add Attack Rating:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Scout_Hawk_Attack_Rate[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Hawk Rotation:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Scout_Hawk_UseTime[pSkill->Point + i - 1], "RND");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//强力之箭
		case SKILL_SHOOTING_MASTERY:
			lstrcpy(szTempSkillDoc, "Added Weapon Attack Power:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", S_Mastery_DamagePercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcat(szSkillInfoBuff, "\r");
			lstrcpy(szTempSkillDoc2, "\r");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//疾风之箭
		case SKILL_WIND_ARROW:
			lstrcpy(szTempSkillDoc, "Added Attack Speed:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Wind_Arrow_Speed[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Wind_Arrow_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//夺命之箭
		case SKILL_PERFECT_AIM:
			lstrcpy(szTempSkillDoc, "Weapon Attack Rating Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Perfect_Aim_Attack_Rate[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Added Atk Power:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d+(LV/%d)\r", Perfect_Aim_Damage[pSkill->Point + i - 1], Perfect_Aim_Damage_LV[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//射神之眼
		case SKILL_DIONS_EYE:
			lstrcpy(szTempSkillDoc, "Weapon Attack Rating Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", D_Eye_Attack_Rate[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcat(szSkillInfoBuff, "\r");
			lstrcpy(szTempSkillDoc2, "\r");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//灵魂之鹰
		case SKILL_FALCON:
			lstrcpy(szTempSkillDoc, "Falcon Attack Power:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d\r", Falcon_Damage[pSkill->Point + i - 1][0], Falcon_Damage[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Falcon_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//狂暴火箭
		case SKILL_ARROW_OF_RAGE:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			if (pSkill->Point + i - 1 > 5)
				wsprintf(szTempSkillDoc2, "LVx%d\r", A_Rage_Damage[pSkill->Point + i - 1]);
			else
				wsprintf(szTempSkillDoc2, "LV/%d\r", A_Rage_Damage[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Area:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", A_Rage_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//雪崩之箭
		case SKILL_AVALANCHE:
			lstrcpy(szTempSkillDoc, "Speed Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Avalanche_Speed[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Avalanche_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Number of Arrows:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Avalanche_ArrowNum[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//元素攻击
		case SKILL_ELEMENTAL_SHOT:
			lstrcpy(szTempSkillDoc, "Fire Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d\r", Elemental_Shot_Fire[pSkill->Point + i - 1][0], Elemental_Shot_Fire[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Lightning Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d\r", Elemental_Shot_Lightning[pSkill->Point + i - 1][0], Elemental_Shot_Lightning[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//黄金猎鹰
		case SKILL_GOLDEN_FALCON:
			lstrcpy(szTempSkillDoc, "Damage of Falcon:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Golden_Falcon_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "HP Recovery:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			sinTemp1 = (int)(Golden_Falcon_LifeRegen[pSkill->Point + i - 1] * 10);
			RightSpot = sinTemp1 % 10;
			LeftSpot = (sinTemp1 - RightSpot) / 10;
			wsprintf(szTempSkillDoc2, "%d.%d\r", LeftSpot, RightSpot);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Golden_Falcon_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//爆裂之箭
		case SKILL_BOMB_SHOT:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", BombShot_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Damage Boost VS Demons:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", BombShot_DemonDamage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Splash Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d\r", BombShot_AddDamage[pSkill->Point + i - 1][0], BombShot_AddDamage[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Area:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", BombShot_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//惯穿之箭
		case SKILL_PERFORATION:
			lstrcpy(szTempSkillDoc, "Attack Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Perforation_Attack_Range[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Perforation_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Added Critical:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Perforation_Critical[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//召唤雪狼
		case SKILL_RECALL_WOLVERIN:
			lstrcpy(szTempSkillDoc, "Attack Type:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			lstrcpy(szTempSkillDoc2, sinAttackType2[pSkill->SkillCodeIndex]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Attack Power:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d\r", Recall_Wolverin_Damage[pSkill->Point + i - 1][0], Recall_Wolverin_Damage[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Attack Rating:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Recall_Wolverin_Hit[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Health:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Recall_Wolverin_Life[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			lstrcpy(szTempSkillDoc, "Defense:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d+(%d)\r", Recall_Wolverin_Defense[pSkill->Point + i - 1], (sinChar->iAgility * 2));
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", 360, "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//躲避大师
		case SKILL_EVASION_MASTERY:
			lstrcpy(szTempSkillDoc, "Evasion Rating Increase:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Evasion_Mastery_AddPercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcat(szSkillInfoBuff, "\r");
			lstrcpy(szTempSkillDoc2, "\r");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//绯凰绝炎
		case SKILL_PHOENIX_SHOT:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Phoenix_Shot_DamagePercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Reduced Charging Time:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			sinTemp1 = (int)((Phoenix_Shot_Time[pSkill->Point + i - 1] + 0.001f) * 10);
			RightSpot = sinTemp1 % 10;
			LeftSpot = (sinTemp1 - RightSpot) / 10;
			wsprintf(szTempSkillDoc2, "%d.%d%s\r", LeftSpot, RightSpot, "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//自然之光
		case SKILL_FORCE_OF_NATURE:
			lstrcpy(szTempSkillDoc, "Attack Power:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Force_Of_Nature_AddDamage[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Attack Rating:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Force_Of_Nature_AddHit[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Falcon Damge:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Force_Of_Nature_FalconAddDamage[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Force_Of_Nature_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//回旋之舞
		case SKILL_E_SHOT:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", E_Shot_Damge[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", E_Shot_Range[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//玄光之箭
		case SKILL_S_ROPE:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", S_Rope_Damge[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Accuracy:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", S_Rope_AddRange[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//飓风之箭
		case SKILL_N_SPLASH:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", N_Splash_Damge[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Attack Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", N_Splash_Range[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//复仇箭雨
		case SKILL_C_TRAP:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", C_Trap_Dmage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", C_Trap_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//魔神剑
		case SKILL_SWORD_BLAST:
			lstrcpy(szTempSkillDoc, "Attack Power:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d(+LV x 4)\r", Sword_Blast_Damage[pSkill->Point + i - 1][0], Sword_Blast_Damage[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Attack Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Sword_Blast_ShootingRange[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//圣光护体
		case SKILL_HOLY_BODY:
			lstrcpy(szTempSkillDoc, "Absorption Boost VS. Undead:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", HolyBody_Absorb[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", HolyBody_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//超能体训
		case SKILL_PHYSICAL_TRANING:
			lstrcpy(szTempSkillDoc, "Stamina Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", P_Traning_Stamina[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcat(szSkillInfoBuff, "\r");
			lstrcpy(szTempSkillDoc2, "\r");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//双重爆击
		case SKILL_DOUBLE_CRASH:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", D_Crash_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Added Critical:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", D_Crash_Critical[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//神力重击
		case SKILL_HOLY_VALOR:
			lstrcpy(szTempSkillDoc, "Party Defense:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", 300);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Holy_Valor_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Holy_Valor_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//狂躁挥舞
		case SKILL_BRANDISH:
			lstrcpy(szTempSkillDoc, "Area:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Brandish_Range[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Brandish_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//一雾银
		case SKILL_PIERCING:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Piercing_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Piercing Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Piercing_Range[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//天佑神铠
		case SKILL_DRASTIC_SPIRIT:
			lstrcpy(szTempSkillDoc, "Defense Rating Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Drastic_Spirit_Defense[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Drastic_Spirit_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//精剑之术
		case SKILL_SWORD_MASTERY:
			lstrcpy(szTempSkillDoc, "Weapon Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Sword_Mastery_DamagePercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//圣灵之吸
		case SKILL_DIVINE_INHALATION:
			lstrcpy(szTempSkillDoc, "Block Rating:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", D_Inhalation_Block[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Damage to HP Conversion:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", D_Inhalation_Life[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", D_Inhalation_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//圣剡之光
		case SKILL_HOLY_INCANTATION:
			lstrcpy(szTempSkillDoc, "Success Rate:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", H_Incantation_Success[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Increase Undead HP:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", H_Incantation_AddLife[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", H_Incantation_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//圣光十字
		case SKILL_GRAND_CROSS:
			lstrcpy(szTempSkillDoc, "Attack Rating:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Grand_Cross_AttackRate[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Grand_Cross_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Damage Boost VS. Undead:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Grand_Cross_UndeadDamage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//真魔神剑
		case SKILL_SWORD_OF_JUSTICE:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Sword_Of_Justice_DamagePercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Attack Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Sword_Of_Justice_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//敬神之盾
		case SKILL_GODLY_SHIELD:
			lstrcpy(szTempSkillDoc, "Added Absorption Rating:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Godly_Shield_AbsorbPercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Godly_Shield_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//上帝祝福
		case SKILL_GOD_BLESS:
			lstrcpy(szTempSkillDoc, "Added Attack Power:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", God_Bless_AddDamage[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", God_Bless_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//刹剧荒舞
		case SKILL_DIVINE_PIERCING:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Divine_Piercing_DamagePercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Number of Hits:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Divine_Piercing_AttackNum[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//神力冲刺
		case SKILL_S_BREAKER:
			lstrcpy(szTempSkillDoc, "Increased Attack Rating:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", S_Breaker_AddHit[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", S_Breaker_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//升龙重击
		case SKILL_C_MOON:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", C_Moon_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Attack Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", C_Moon_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//上帝重击
		case SKILL_S_BLADE:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", S_Blade_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Damage Boost VS.Undead:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", S_Blade_UndeadDamage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//亡灵之咒
		case SKILL_H_BENEDIC:
			lstrcpy(szTempSkillDoc, "Death Rate:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", H_Benedic_Hit[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", H_Benedic_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//美杜莎盾
		case SKILL_SHIELD_STRIKE:
			lstrcpy(szTempSkillDoc, "Penetration attack\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			lstrcpy(szTempSkillDoc2, "\r");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Attack Power:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d(+LV/5)\r", S_Strike_Damage[pSkill->Point + i - 1][0], S_Strike_Damage[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//含沙射影
		case SKILL_FARINA:
			lstrcpy(szTempSkillDoc, "Added Weapon Speed:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Farina_Speed[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Added Attack Rating:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Farina_AttackRate[pSkill->Point + i - 1], "(+LV)");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//魔力神枪
		case SKILL_THROWING_MASTERY:
			lstrcpy(szTempSkillDoc, "Weapon Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", T_Mastery_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcat(szSkillInfoBuff, "\r");
			lstrcpy(szTempSkillDoc2, "\r");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//精神之枪
		case SKILL_VIGOR_SPEAR:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d+(LV/2)\r", V_Spear_Damage[pSkill->Point + i - 1][0], V_Spear_Damage[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//追命劲风
		case SKILL_WINDY:
			lstrcpy(szTempSkillDoc, "Increased Attack Rating:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Windy_Attack_Rating[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Added Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", 30);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Windy_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//螺旋飞标
		case SKILL_TWIST_JAVELIN:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Twist_Javelin_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Attack Rating Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Twist_Javelin_Attack_Rating[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//灵魂吞噬
		case SKILL_SOUL_SUCKER:
			lstrcpy(szTempSkillDoc, "Enemy HP Absorption:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Soul_Sucker_Absorb[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//火焰烈枪
		case SKILL_FIRE_JAVELIN:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d+(LV/3)\r", Fire_Javelin_Damage[pSkill->Point + i - 1][0], Fire_Javelin_Damage[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//追风之枪
		case SKILL_SPLIT_JAVELIN:
			lstrcpy(szTempSkillDoc, "Number of Hits:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Split_Javelin_AttackNum[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Split_Javelin_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Attack Rating:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Split_Javelin_AttackRate[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//战栗咆哮
		case SKILL_TRIUMPH_OF_VALHALLA:
			lstrcpy(szTempSkillDoc, "Added Maximum Attack Power:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d+(LV/1)\r", T_Of_Valhalla_Damage[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", T_Of_Valhalla_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//光猎之枪
		case SKILL_LIGHTNING_JAVELIN:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d+(LV/3)\r", Lightning_Javelin_Damage[pSkill->Point + i - 1][0], Lightning_Javelin_Damage[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//暴风狂标
		case SKILL_STORM_JAVELIN:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Storm_Javelin_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//瓦尔哈拉之光
		case SKILL_HALL_OF_VALHALLA:
			lstrcpy(szTempSkillDoc, "Added Evasion Rating:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Hall_Of_Valhalla_AddEvation[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Hall_Of_Valhalla_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//十字怒击
		case SKILL_X_RAGE:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", X_Rage_DamagePercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Attack Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", X_Rage_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//霜冻标枪
		case SKILL_FROST_JAVELIN:
			lstrcpy(szTempSkillDoc, "Ice Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d\r", Frost_Javelin_IceAddDamage[pSkill->Point + i - 1][0], Frost_Javelin_IceAddDamage[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Enemy Speed Reduction:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Frost_Javelin_SpeedSubPercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Freeze Time:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Frost_Javelin_IceTime[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Frost_Javelin_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//狂风爆裂
		case SKILL_VENGEANCE:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Vengeance_DamagePercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Added Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Vengeance_Range[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//轻舞飞扬
		case SKILL_TALARIA:
			lstrcpy(szTempSkillDoc, "Added Running Speed:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Talaria_MoveSpeed[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Talaria_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//星雨标枪
		case SKILL_G_COUP:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", G_Coup_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Number of Javelins:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", G_Coup_Hit[pSkill->Point + i - 1], "Javelins");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//笨笨熊
		case SKILL_S_ARCUDA:
			lstrcpy(szTempSkillDoc, "Attack Type:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			lstrcpy(szTempSkillDoc2, sinAttackType2[pSkill->SkillCodeIndex]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Attack Power:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d\r", S_Arcuda_Damage[pSkill->Point + i - 1][0], S_Arcuda_Damage[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Attack Rating:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Vengeance_Range[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Health:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", S_Arcuda_PetHp[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Defense:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d+(%d)\r", S_Arcuda_Defanse[pSkill->Point + i - 1], (sinChar->iStrength * 2));
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", 360, "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//烈焰突袭
		case SKILL_S_FEAR:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", S_Fear_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Added Critical:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", S_Fear_AddCritical[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//治愈之术
		case SKILL_HEALING:
			PlusMinD = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin;
			PlusMaxD = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax;
			lstrcpy(szTempSkillDoc, "HP Restored:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d(+%d)-%d(+%d)\r", Healing_Heal[pSkill->Point + i - 1][0], PlusMinD, Healing_Heal[pSkill->Point + i - 1][1], PlusMaxD);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//圣光电球
		case SKILL_HOLY_BOLT:
			PlusMinD = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin * 4;
			PlusMaxD = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax * 4;
			wsprintf(szTempSkillDoc, "%s", "Holy Bolt Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d(+%d)-%d(+%d)\r", HolyBolt_Damage[pSkill->Point + i - 1][0], PlusMinD, HolyBolt_Damage[pSkill->Point + i - 1][1], PlusMaxD);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//光芒四射
		case SKILL_MULTISPARK:
			PlusMinD = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin * 2;
			PlusMaxD = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax * 2;
			lstrcpy(szTempSkillDoc, "Damage by each Spark:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d(+%d)-%d(+%d)\r", M_Spark_Damage[pSkill->Point + i - 1][0], PlusMinD, M_Spark_Damage[pSkill->Point + i - 1][1], PlusMaxD);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Sparks:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d%s", (M_Spark_Num[pSkill->Point + i - 1] / 2) + 1, M_Spark_Num[pSkill->Point + i - 1], "Sparks");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//意念之术
		case SKILL_HOLY_MIND:
			lstrcpy(szTempSkillDoc, "Reduce Monster Attack Power:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", HolyMind_DecDamage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "15%s\r", "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//曙光耀灵
		case SKILL_MEDITATION:
			lstrcpy(szTempSkillDoc, "Added MP Recovery:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			sinTemp1 = (int)(Meditation_Regen[pSkill->Point + i - 1] * 10);
			RightSpot = sinTemp1 % 10;
			LeftSpot = (sinTemp1 - RightSpot) / 10;
			wsprintf(szTempSkillDoc2, "%d.%d\r", LeftSpot, RightSpot);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcat(szSkillInfoBuff, "\r");
			lstrcpy(szTempSkillDoc2, "\r");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//神之雷电
		case SKILL_DIVINE_LIGHTNING:
			PlusMinD = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin * 2 + sinChar->iSpirit / 2;
			PlusMaxD = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax * 2 + sinChar->iSpirit;
			lstrcpy(szTempSkillDoc, "Lightning Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d(+%d)-%d(+%d)\r", Divine_Lightning_Damage[pSkill->Point + i - 1][0], PlusMinD, Divine_Lightning_Damage[pSkill->Point + i - 1][1], PlusMaxD);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", 180);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Bolts:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Divine_Lightning_Num[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//神圣反射
		case SKILL_HOLY_REFLECTION:
			lstrcpy(szTempSkillDoc, "Reflect:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Holy_Reflection_Return_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Holy_Reflection_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//圣洁之光
		case SKILL_GRAND_HEALING:
			PlusMinD = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin * 2;
			PlusMaxD = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax * 2;
			lstrcpy(szTempSkillDoc, "HP Restored:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d(+%d)-%d(+%d)\r", Grand_Healing[pSkill->Point + i - 1][0], PlusMinD, Grand_Healing[pSkill->Point + i - 1][1], PlusMaxD);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Party Range;\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Grand_Healing_Range[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//火影双重
		case SKILL_VIGOR_BALL:
			PlusMinD = sinTemp1 + cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin * 2 + sinChar->iSpirit * 2;
			PlusMaxD = sinTemp1 + cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax * 2 + sinChar->iSpirit * 2;
			wsprintf(szTempSkillDoc, "%s", "Vigor Ball Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d(+%d)-%d(+%d)\r", Vigor_Ball_Damage[pSkill->Point + i - 1][0], PlusMinD, Vigor_Ball_Damage[pSkill->Point + i - 1][1], PlusMaxD);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//回生之术
		case SKILL_RESURRECTION:
			lstrcpy(szTempSkillDoc, "Success Rate:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Resurrection_Percent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//圣光之咒
		case SKILL_EXTINCTION:
			lstrcpy(szTempSkillDoc, "Success Rate:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d+(LV/5)%s\r", Extinction_Percent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "HP Reduction VS. Undead:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Extinction_Amount[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//神圣之光
		case SKILL_VIRTUAL_LIFE:
			lstrcpy(szTempSkillDoc, "HP Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Virtual_Life_Percent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Virtual_Life_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//冰霜噬月
		case SKILL_GLACIAL_SPIKE:
			PlusMinD = sinTemp1 + cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin * 2 + sinChar->iSpirit / 2;
			PlusMaxD = sinTemp1 + cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax * 2 + sinChar->iSpirit / 2;
			lstrcpy(szTempSkillDoc, "Glacial Spike Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d(+%d)-%d(+%d)\r", Glacial_Spike_Damage[pSkill->Point + i - 1][0], PlusMinD, Glacial_Spike_Damage[pSkill->Point + i - 1][1], PlusMaxD);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Attack Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Glacial_Spike_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//再生领域
		case SKILL_REGENERATION_FIELD:
			lstrcpy(szTempSkillDoc, "HP Recovery:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			TempLife = (int)(Regeneration_Field_LifeRegen[pSkill->Point + i - 1] * 10 + 0.001f);
			RightSpot = TempLife % 10;
			LeftSpot = (TempLife - RightSpot) / 10;
			wsprintf(szTempSkillDoc2, "%d.%d\r", LeftSpot, RightSpot);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "MP Recovery:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			TempMana = (int)(Regeneration_Field_ManaRegen[pSkill->Point + i - 1] * 10 + 0.001f);
			RightSpot = TempMana % 10;
			LeftSpot = (TempMana - RightSpot) / 10;
			wsprintf(szTempSkillDoc2, "%d.%d\r", LeftSpot, RightSpot);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Regeneration_Field_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Regeneration_Field_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//天雷之怒
		case SKILL_CHAIN_LIGHTNING:
			PlusMinD = sinTemp1 + cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin * 2 + sinChar->iSpirit / 2;
			PlusMaxD = sinTemp1 + cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax * 2 + sinChar->iSpirit;
			lstrcpy(szTempSkillDoc, "Lightning Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d(+%d)-%d(+%d)\r", Chain_Lightning_Damage[pSkill->Point + i - 1][0], PlusMinD, Chain_Lightning_Damage[pSkill->Point + i - 1][1], PlusMaxD);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Bolts:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Chain_Lightning_Num[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Range;\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Chain_Lightning_Range[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//神圣天使
		case SKILL_SUMMON_MUSPELL:
			lstrcpy(szTempSkillDoc, "Attack Power:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d\r", Summon_Muspell_Damage[pSkill->Point + i - 1][0], Summon_Muspell_Damage[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Attack Interval:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Summon_Muspell_Attack_Delay[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Absorbs Undead Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Summon_Muspell_UndeadAbsorbPercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Added Evasion:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Summon_Muspell_BlockPercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Summon_Muspell_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//神圣电波
		case SKILL_S_IMPACT:
			PlusMinD = sinTemp1 + cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin * 2 + sinChar->iSpirit / 2;
			PlusMaxD = sinTemp1 + cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax * 2 + sinChar->iSpirit;
			lstrcpy(szTempSkillDoc, "Spirit Impact Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d(+%d)-%d(+%d)\r", S_Impact_Damage[pSkill->Point + i - 1][0], PlusMinD, S_Impact_Damage[pSkill->Point + i - 1][1], PlusMaxD);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Attack Range;\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Chain_Lightning_Range[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//神圣兵刃
		case SKILL_P_ICE:
			PlusMinD = sinTemp1 + cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin * 2 + sinChar->iSpirit / 2;
			PlusMaxD = sinTemp1 + cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax * 2 + sinChar->iSpirit;
			lstrcpy(szTempSkillDoc, "Piercing Ice Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d(+%d)-%d(+%d)\r", P_Ice_Damge[pSkill->Point + i - 1][0], PlusMinD, P_Ice_Damge[pSkill->Point + i - 1][1], PlusMaxD);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Frozen Time:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", P_Ice_Frozen[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//暴风雪
		case SKILL_S_PRMIEL:
			PlusMinD = sinTemp1 + cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin * 2 + sinChar->iSpirit / 2;
			PlusMaxD = sinTemp1 + cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax * 2 + sinChar->iSpirit;
			lstrcpy(szTempSkillDoc, "Storm damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d(+%d)-%d(+%d)\r", S_Ramiel_Damage[pSkill->Point + i - 1][0], PlusMinD, S_Ramiel_Damage[pSkill->Point + i - 1][1], PlusMaxD);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Number of meteorites:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", S_Ramiel_Num[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", S_Ramiel_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//天女散花
		case SKILL_B_KRISHNA:
			lstrcpy(szTempSkillDoc, "Evasion rate:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", B_Krishna_Evasion[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Added Absorb;\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", B_Krishna_Abs[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//魔力转化
		case SKILL_AGONY:
			lstrcpy(szTempSkillDoc, "Converted:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Agony_ConvLife[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//火箭之术
		case SKILL_FIRE_BOLT:
			PlusMinD = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin * 4;
			PlusMaxD = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax * 4;
			TempPoint = SearchContiueSkill(SKILL_SPIRIT_ELEMENTAL);
			if (TempPoint)
			{
				PlusMinD += (FireBolt_Damage[pSkill->Point - 1][0] * Spirit_Elemental_Damage[TempPoint - 1]) / 100;
				PlusMaxD += (FireBolt_Damage[pSkill->Point - 1][1] * Spirit_Elemental_Damage[TempPoint - 1]) / 100;
			}
			TempPoint = SearchContiueSkill(SKILL_T_ANIMA);
			if (TempPoint)
			{
				TempPoint2 = GetSkillPoint(SKILL_SPIRIT_ELEMENTAL);

				if (TempPoint2)
				{
					PlusMinD += (FireBolt_Damage[pSkill->Point - 1][0] * (Spirit_Elemental_Damage[TempPoint - 1] + T_Anima_Dmage[TempPoint2 - 1])) / 100;
					PlusMaxD += (FireBolt_Damage[pSkill->Point - 1][1] * (Spirit_Elemental_Damage[TempPoint - 1] + T_Anima_Dmage[TempPoint2 - 1])) / 100;
				}
				else
				{
					PlusMinD += (FireBolt_Damage[pSkill->Point - 1][0] * T_Anima_Dmage[TempPoint - 1]) / 100;
					PlusMaxD += (FireBolt_Damage[pSkill->Point - 1][1] * T_Anima_Dmage[TempPoint - 1]) / 100;
				}
			}
			wsprintf(szTempSkillDoc, "%s", "Fire Bolt Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d(+%d)-%d(+%d)\r", FireBolt_Damage[pSkill->Point + i - 1][0], PlusMinD, FireBolt_Damage[pSkill->Point + i - 1][1], PlusMaxD);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", 200);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//集合之术
		case SKILL_ZENITH:
			lstrcpy(szTempSkillDoc, "Added Elemental Resistance:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Zenith_Element[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Zenith_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//火球之术
		case SKILL_FIRE_BALL:
			PlusMinD = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin + sinChar->iSpirit / 8;
			PlusMaxD = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax + sinChar->iSpirit / 4;
			TempPoint = SearchContiueSkill(SKILL_SPIRIT_ELEMENTAL);
			if (TempPoint)
			{
				PlusMinD += (FireBall_Damage[pSkill->Point - 1][0] * Spirit_Elemental_Damage[TempPoint - 1]) / 100;
				PlusMaxD += (FireBall_Damage[pSkill->Point - 1][1] * Spirit_Elemental_Damage[TempPoint - 1]) / 100;
			}
			TempPoint = SearchContiueSkill(SKILL_T_ANIMA);
			if (TempPoint)
			{
				TempPoint2 = GetSkillPoint(SKILL_SPIRIT_ELEMENTAL);

				if (TempPoint2)
				{
					PlusMinD += (FireBall_Damage[pSkill->Point - 1][0] * (Spirit_Elemental_Damage[TempPoint - 1] + T_Anima_Dmage[TempPoint2 - 1])) / 100;
					PlusMaxD += (FireBall_Damage[pSkill->Point - 1][1] * (Spirit_Elemental_Damage[TempPoint - 1] + T_Anima_Dmage[TempPoint2 - 1])) / 100;
				}
				else
				{
					PlusMinD += (FireBall_Damage[pSkill->Point - 1][0] * T_Anima_Dmage[TempPoint - 1]) / 100;
					PlusMaxD += (FireBall_Damage[pSkill->Point - 1][1] * T_Anima_Dmage[TempPoint - 1]) / 100;
				}
			}
			lstrcpy(szTempSkillDoc, "Fire Ball Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d(+%d)-%d(+%d)\r", FireBall_Damage[pSkill->Point + i - 1][0], PlusMinD, FireBall_Damage[pSkill->Point + i - 1][1], PlusMaxD);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", FireBall_Range[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Area:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", FireBall_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//控制意念
		case SKILL_MENTAL_MASTERY:
			lstrcpy(szTempSkillDoc, "MP Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Mental_Mastery_Mana[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcat(szSkillInfoBuff, "\r");
			lstrcpy(szTempSkillDoc2, "\r");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//龙卷海风
		case SKILL_WATORNADO:
			PlusMinD = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin + sinChar->iSpirit / 2;
			PlusMaxD = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax + sinChar->iSpirit;
			TempPoint = SearchContiueSkill(SKILL_SPIRIT_ELEMENTAL);
			if (TempPoint)
			{
				PlusMinD += (Watornado_Damage[pSkill->Point - 1][0] * Spirit_Elemental_Damage[TempPoint - 1]) / 100;
				PlusMaxD += (Watornado_Damage[pSkill->Point - 1][1] * Spirit_Elemental_Damage[TempPoint - 1]) / 100;
			}
			TempPoint = SearchContiueSkill(SKILL_T_ANIMA);
			if (TempPoint)
			{
				TempPoint2 = GetSkillPoint(SKILL_SPIRIT_ELEMENTAL);

				if (TempPoint2)
				{
					PlusMinD += (Watornado_Damage[pSkill->Point - 1][0] * (Spirit_Elemental_Damage[TempPoint - 1] + T_Anima_Dmage[TempPoint2 - 1])) / 100;
					PlusMaxD += (Watornado_Damage[pSkill->Point - 1][1] * (Spirit_Elemental_Damage[TempPoint - 1] + T_Anima_Dmage[TempPoint2 - 1])) / 100;
				}
				else
				{
					PlusMinD += (Watornado_Damage[pSkill->Point - 1][0] * T_Anima_Dmage[TempPoint - 1]) / 100;
					PlusMaxD += (Watornado_Damage[pSkill->Point - 1][1] * T_Anima_Dmage[TempPoint - 1]) / 100;
				}
			}
			lstrcpy(szTempSkillDoc, "Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d(+%d)-%d(+%d)\r", Watornado_Damage[pSkill->Point + i - 1][0], PlusMinD, Watornado_Damage[pSkill->Point + i - 1][1], PlusMaxD);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Watornado_Range[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Area:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Watornado_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//元素之术
		case SKILL_ENCHANT_WEAPON:
			lstrcpy(szTempSkillDoc, "Fire Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d\r", Enchant_Weapon_Damage_Fire[pSkill->Point + i - 1][0], Enchant_Weapon_Damage_Fire[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Ice Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d\r", Enchant_Weapon_Damage_Ice[pSkill->Point + i - 1][0], Enchant_Weapon_Damage_Ice[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Lightning Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d\r", Enchant_Weapon_Damage_Lightning[pSkill->Point + i - 1][0], Enchant_Weapon_Damage_Lightning[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Enchant_Weapon_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//冥亡之光
		case SKILL_DEAD_RAY:
			PlusMinD = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin * 4 + sinChar->iSpirit / 2;
			PlusMaxD = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax * 4 + sinChar->iSpirit;
			TempPoint = SearchContiueSkill(SKILL_SPIRIT_ELEMENTAL);
			if (TempPoint)
			{
				PlusMinD += (Dead_Ray_Damage[pSkill->Point - 1][0] * Spirit_Elemental_Damage[TempPoint - 1]) / 100;
				PlusMaxD += (Dead_Ray_Damage[pSkill->Point - 1][1] * Spirit_Elemental_Damage[TempPoint - 1]) / 100;
			}
			TempPoint = SearchContiueSkill(SKILL_T_ANIMA);
			if (TempPoint)
			{
				TempPoint2 = GetSkillPoint(SKILL_SPIRIT_ELEMENTAL);

				if (TempPoint2)
				{
					PlusMinD += (Dead_Ray_Damage[pSkill->Point - 1][0] * (Spirit_Elemental_Damage[TempPoint - 1] + T_Anima_Dmage[TempPoint2 - 1])) / 100;
					PlusMaxD += (Dead_Ray_Damage[pSkill->Point - 1][1] * (Spirit_Elemental_Damage[TempPoint - 1] + T_Anima_Dmage[TempPoint2 - 1])) / 100;
				}
				else
				{
					PlusMinD += (Dead_Ray_Damage[pSkill->Point - 1][0] * T_Anima_Dmage[TempPoint - 1]) / 100;
					PlusMaxD += (Dead_Ray_Damage[pSkill->Point - 1][1] * T_Anima_Dmage[TempPoint - 1]) / 100;
				}
			}
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d(+%d)-%d(+%d)\r", Dead_Ray_Damage[pSkill->Point + i - 1][0], PlusMinD, Dead_Ray_Damage[pSkill->Point + i - 1][1], PlusMaxD);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Dead_Ray_Range[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//魔法守护
		case SKILL_ENERGY_SHIELD:
			lstrcpy(szTempSkillDoc, "Reduced Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Energy_Shield_DecDamage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Energy_Shield_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//地裂冲击
		case SKILL_DIASTROPHISM:
			PlusMinD = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin * 2 + sinChar->iSpirit / 2;
			PlusMaxD = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax * 2 + sinChar->iSpirit;
			TempPoint = SearchContiueSkill(SKILL_SPIRIT_ELEMENTAL);
			if (TempPoint)
			{
				PlusMinD += (Diastrophism_Damage[pSkill->Point - 1][0] * Spirit_Elemental_Damage[TempPoint - 1]) / 100;
				PlusMaxD += (Diastrophism_Damage[pSkill->Point - 1][1] * Spirit_Elemental_Damage[TempPoint - 1]) / 100;
			}
			TempPoint = SearchContiueSkill(SKILL_T_ANIMA);
			if (TempPoint)
			{
				TempPoint2 = GetSkillPoint(SKILL_SPIRIT_ELEMENTAL);

				if (TempPoint2)
				{
					PlusMinD += (Diastrophism_Damage[pSkill->Point - 1][0] * (Spirit_Elemental_Damage[TempPoint - 1] + T_Anima_Dmage[TempPoint2 - 1])) / 100;
					PlusMaxD += (Diastrophism_Damage[pSkill->Point - 1][1] * (Spirit_Elemental_Damage[TempPoint - 1] + T_Anima_Dmage[TempPoint2 - 1])) / 100;
				}
				else
				{
					PlusMinD += (Diastrophism_Damage[pSkill->Point - 1][0] * T_Anima_Dmage[TempPoint - 1]) / 100;
					PlusMaxD += (Diastrophism_Damage[pSkill->Point - 1][1] * T_Anima_Dmage[TempPoint - 1]) / 100;
				}
			}
			lstrcpy(szTempSkillDoc, "Diastrophism Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d(+%d)-%d(+%d)\r", Diastrophism_Damage[pSkill->Point + i - 1][0], PlusMinD, Diastrophism_Damage[pSkill->Point + i - 1][1], PlusMaxD);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Area:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Diastrophism_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//灵魂召唤
		case SKILL_SPIRIT_ELEMENTAL:
			lstrcpy(szTempSkillDoc, "Increased Magic Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Spirit_Elemental_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Spirit_Elemental_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//元素之剑
		case SKILL_DANCING_SWORD:
			PlusMinD += cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin;
			PlusMaxD += cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax;
			lstrcpy(szTempSkillDoc, "Fire Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d(+%d)-%d(+%d)\r", Dancing_Sword_FireDamage[pSkill->Point + i - 1][0], PlusMinD, Dancing_Sword_FireDamage[pSkill->Point + i - 1][1], PlusMaxD);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Ice Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d(+%d)-%d(+%d)\r", Dancing_Sword_IceDamage[pSkill->Point + i - 1][0], PlusMinD, Dancing_Sword_IceDamage[pSkill->Point + i - 1][1], PlusMaxD);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Attack Interval:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Dancing_Sword_AttackDelay[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Dancing_Sword_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//伊夫列特
		case SKILL_FIRE_ELEMENTAL:
			lstrcpy(szTempSkillDoc, "Attack Type:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			lstrcpy(szTempSkillDoc2, sinAttackType2[pSkill->SkillCodeIndex]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Attack Power:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d\r", Fire_Elemental_Damage[pSkill->Point + i - 1][0], Fire_Elemental_Damage[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Attack Rating:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Fire_Elemental_Hit[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Health:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", (Fire_Elemental_Life[pSkill->Point + i - 1]));
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", 360, "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//火焰波动
		case SKILL_FLAME_WAVE:
			PlusMinD = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin * 2 + sinChar->iSpirit / 2;
			PlusMaxD = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax * 2 + sinChar->iSpirit;
			TempPoint = SearchContiueSkill(SKILL_SPIRIT_ELEMENTAL);
			if (TempPoint)
			{
				PlusMinD += (Flame_Wave_FireDamage[pSkill->Point - 1][0] * Spirit_Elemental_Damage[TempPoint - 1]) / 100;
				PlusMaxD += (Flame_Wave_FireDamage[pSkill->Point - 1][1] * Spirit_Elemental_Damage[TempPoint - 1]) / 100;
			}
			TempPoint = SearchContiueSkill(SKILL_T_ANIMA);
			if (TempPoint)
			{
				TempPoint2 = GetSkillPoint(SKILL_SPIRIT_ELEMENTAL);

				if (TempPoint2)
				{
					PlusMinD += (Flame_Wave_FireDamage[pSkill->Point - 1][0] * (Spirit_Elemental_Damage[TempPoint - 1] + T_Anima_Dmage[TempPoint2 - 1])) / 100;
					PlusMaxD += (Flame_Wave_FireDamage[pSkill->Point - 1][1] * (Spirit_Elemental_Damage[TempPoint - 1] + T_Anima_Dmage[TempPoint2 - 1])) / 100;
				}
				else
				{
					PlusMinD += (Flame_Wave_FireDamage[pSkill->Point - 1][0] * T_Anima_Dmage[TempPoint - 1]) / 100;
					PlusMaxD += (Flame_Wave_FireDamage[pSkill->Point - 1][1] * T_Anima_Dmage[TempPoint - 1]) / 100;
				}
			}
			lstrcpy(szTempSkillDoc, "Flame Wave Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d(+%d)-%d(+%d)\r", Flame_Wave_FireDamage[pSkill->Point + i - 1][0], PlusMinD, Flame_Wave_FireDamage[pSkill->Point + i - 1][1], PlusMaxD);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Flame_Wave_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//空间扭曲
		case SKILL_DISTORTION:
			lstrcpy(szTempSkillDoc, "Speed Reduction:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Distortion_SpeedSubPercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Attack Reduction:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Distortion_DamageSubPercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Distortion_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Distortion_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//陨石召唤
		case SKILL_M_METEO:
			PlusMinD = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin * 2 + sinChar->iSpirit / 2;
			PlusMaxD = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax * 2 + sinChar->iSpirit;
			TempPoint = SearchContiueSkill(SKILL_SPIRIT_ELEMENTAL);
			if (TempPoint)
			{
				PlusMinD += (Meteo_Damage[pSkill->Point - 1][0] * Spirit_Elemental_Damage[TempPoint - 1]) / 100;
				PlusMaxD += (Meteo_Damage[pSkill->Point - 1][1] * Spirit_Elemental_Damage[TempPoint - 1]) / 100;
			}
			TempPoint = SearchContiueSkill(SKILL_T_ANIMA);
			if (TempPoint)
			{
				TempPoint2 = GetSkillPoint(SKILL_SPIRIT_ELEMENTAL);

				if (TempPoint2)
				{
					PlusMinD += (Meteo_Damage[pSkill->Point - 1][0] * (Spirit_Elemental_Damage[TempPoint - 1] + T_Anima_Dmage[TempPoint2 - 1])) / 100;
					PlusMaxD += (Meteo_Damage[pSkill->Point - 1][1] * (Spirit_Elemental_Damage[TempPoint - 1] + T_Anima_Dmage[TempPoint2 - 1])) / 100;
				}
				else
				{
					PlusMinD += (Meteo_Damage[pSkill->Point - 1][0] * T_Anima_Dmage[TempPoint - 1]) / 100;
					PlusMaxD += (Meteo_Damage[pSkill->Point - 1][1] * T_Anima_Dmage[TempPoint - 1]) / 100;
				}
			}
			lstrcpy(szTempSkillDoc, "Meteorite Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d(+%d)-%d(+%d)\r", Meteo_Damage[pSkill->Point + i - 1][0], PlusMinD, Meteo_Damage[pSkill->Point + i - 1][1], PlusMaxD);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Meteo_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//流星火雨
		case SKILL_SILRAPHIM:
			PlusMinD = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin * 2 + sinChar->iSpirit / 2;
			PlusMaxD = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax * 2 + sinChar->iSpirit;
			TempPoint = SearchContiueSkill(SKILL_SPIRIT_ELEMENTAL);
			if (TempPoint)
			{
				PlusMinD += (Silraphim_Damage[pSkill->Point - 1][0] * Spirit_Elemental_Damage[TempPoint - 1]) / 100;
				PlusMaxD += (Silraphim_Damage[pSkill->Point - 1][1] * Spirit_Elemental_Damage[TempPoint - 1]) / 100;
			}
			TempPoint = SearchContiueSkill(SKILL_T_ANIMA);
			if (TempPoint)
			{
				TempPoint2 = GetSkillPoint(SKILL_SPIRIT_ELEMENTAL);

				if (TempPoint2)
				{
					PlusMinD += (Silraphim_Damage[pSkill->Point - 1][0] * (Spirit_Elemental_Damage[TempPoint - 1] + T_Anima_Dmage[TempPoint2 - 1])) / 100;
					PlusMaxD += (Silraphim_Damage[pSkill->Point - 1][1] * (Spirit_Elemental_Damage[TempPoint - 1] + T_Anima_Dmage[TempPoint2 - 1])) / 100;
				}
				else
				{
					PlusMinD += (Silraphim_Damage[pSkill->Point - 1][0] * T_Anima_Dmage[TempPoint - 1]) / 100;
					PlusMaxD += (Silraphim_Damage[pSkill->Point - 1][1] * T_Anima_Dmage[TempPoint - 1]) / 100;
				}
			}
			lstrcpy(szTempSkillDoc, "Silraphim Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d(+%d)-%d(+%d)\r", Silraphim_Damage[pSkill->Point + i - 1][0], PlusMinD, Silraphim_Damage[pSkill->Point + i - 1][1], PlusMaxD);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Attack Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Silraphim_Range[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//缩小之术
		case SKILL_V_TENUS:
			lstrcpy(szTempSkillDoc, "Reduce Speed:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", V_Tenus_SubSpeed[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Attack Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", V_Tenus_Range[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", V_Tenus_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//神圣洗礼
		case SKILL_P_IGNIS:
			PlusMinD = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin * 2 + sinChar->iSpirit / 2;
			PlusMaxD = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax * 2 + sinChar->iSpirit;
			TempPoint = SearchContiueSkill(SKILL_SPIRIT_ELEMENTAL);
			if (TempPoint)
			{
				PlusMinD += (P_Ignis_Dmage[pSkill->Point - 1][0] * Spirit_Elemental_Damage[TempPoint - 1]) / 100;
				PlusMaxD += (P_Ignis_Dmage[pSkill->Point - 1][1] * Spirit_Elemental_Damage[TempPoint - 1]) / 100;
			}
			TempPoint = SearchContiueSkill(SKILL_T_ANIMA);
			if (TempPoint)
			{
				TempPoint2 = GetSkillPoint(SKILL_SPIRIT_ELEMENTAL);

				if (TempPoint2)
				{
					PlusMinD += (P_Ignis_Dmage[pSkill->Point - 1][0] * (Spirit_Elemental_Damage[TempPoint - 1] + T_Anima_Dmage[TempPoint2 - 1])) / 100;
					PlusMaxD += (P_Ignis_Dmage[pSkill->Point - 1][1] * (Spirit_Elemental_Damage[TempPoint - 1] + T_Anima_Dmage[TempPoint2 - 1])) / 100;
				}
				else
				{
					PlusMinD += (P_Ignis_Dmage[pSkill->Point - 1][0] * T_Anima_Dmage[TempPoint - 1]) / 100;
					PlusMaxD += (P_Ignis_Dmage[pSkill->Point - 1][1] * T_Anima_Dmage[TempPoint - 1]) / 100;
				}
			}
			lstrcpy(szTempSkillDoc, "Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d(+%d)-%d(+%d)\r", P_Ignis_Dmage[pSkill->Point + i - 1][0], PlusMinD, P_Ignis_Dmage[pSkill->Point + i - 1][1], PlusMaxD);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Area:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", P_Ignis_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Number:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", P_Ignis_Hit[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//神圣法阵
		case SKILL_T_ANIMA:
			lstrcpy(szTempSkillDoc, "Increased Magic Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", T_Anima_Dmage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", T_Anima_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			// 刺客
			//刺击
		case SKILL_STRINGER:
			lstrcpy(szTempSkillDoc, "Attack Power:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Stinger_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//闪击
		case SKILL_RUNNING_HIT:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Running_Hit_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//强化攻击
		case SKILL_SWORDMASTERY:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Sword_Mastery_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcat(szSkillInfoBuff, "\r");
			lstrcpy(szTempSkillDoc2, "\r");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//弱点攻击
		case SKILL_WISP:
			lstrcpy(szTempSkillDoc, "Attack Reduction:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Wisp_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Wisp_Range[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Wisp_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//毒牙连击
		case SKILL_VENOM_THORN:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Venom_Thorn_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Poison Rato:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Venom_Thorn_Ratio[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Verom_Thorn_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//敏捷之力
		case SKILL_ALAS:
			lstrcpy(szTempSkillDoc, "Evasion Increase:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Alas_Eavsion[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Alas_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Alas_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//灵魂震撼
		case SKILL_SOUL_SHOCK:
			lstrcpy(szTempSkillDoc, "Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Soul_Shock_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Soul_Shock_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//攻击大师
		case SKILL_ATTACK_MASTERY:
			lstrcpy(szTempSkillDoc, "Added Attack Power:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Blade_Mastery_Attack[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Evasion Increase:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Blade_Mastery_Evasion[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//飞剑之舞
		case SKILL_SORE_SWORD:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Finishing_Blow_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//跳斩
		case SKILL_BEAT_UP:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Gust_Slash_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//敏捷大师
		case SKILL_INPES:
			lstrcpy(szTempSkillDoc, "Added Attack Speed:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Inpes_Atk_Speed[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Inpes_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//致盲
		case SKILL_BLIND:
			lstrcpy(szTempSkillDoc, "After Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Deception_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Visibility:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Deception_Visibility[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Deception_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//冰冻之刃
		case SKILL_FROST_WIND:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Frost_Wind_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//致命艺术
		case SKILL_FATAL_MASTERY:
			lstrcpy(szTempSkillDoc, "Added Critical:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Fatal_Mastery_Critical[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcat(szSkillInfoBuff, "\r");
			lstrcpy(szTempSkillDoc2, "\r");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//瘟疫之刃
		case SKILL_POLLUTED:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Pollute_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Area:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Pollute_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Rate:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Pollute_Ratio[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Pollute_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//影子闪击
		case SKILL_PASTING_SHADOW:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Shadow_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//影子火焰
		case SKILL_SHADOW_BOMB:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Shadow_Bomb_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Attack Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Shadow_Bomb_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Burning rate:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Shadow_Bomb_Ratio[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Shadow_Bomb_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//地裂斩
		case SKILL_RISING_SHASH:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Rising_Slash_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//猛龙摆尾
		case SKILL_VIOLENCE_STAB:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Violent_Stub_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//风暴之刃
		case SKILL_STORM:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Shadow_Storm_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Area:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Shadow_Storm_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Shadow_Storm_Range[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Push Back Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Shadow_Storm_PushRange[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//萨满
			//暗黑闪电
		case SKILL_DARK_BOLT:
			lstrcpy(szTempSkillDoc, "Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Dark_Bolt_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//暗黑波浪
		case SKILL_DARK_WAVE:
			lstrcpy(szTempSkillDoc, "Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Dark_Wave_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//诅咒雷击
		case SKILL_CURSE_LAZY:
			lstrcpy(szTempSkillDoc, "Reduced Moving Speed:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Inertia_Speed[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Reduced Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Inertia_Atk[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Inertia_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Inertia_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//内心平和
		case SKILL_INNER_PEACE:
			lstrcpy(szTempSkillDoc, "Increased Magic Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Inner_Peace_AddMana[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcat(szSkillInfoBuff, "\r");
			lstrcpy(szTempSkillDoc2, "\r");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//精神咒术
		case SKILL_SPIRITUAL_FLARE:
			lstrcpy(szTempSkillDoc, "Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Spiritual_Flare_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Spiritual_Flare_Rnage[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Attack Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Spiritual_Flare_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//灵魂枷锁
		case SKILL_SPIRITUAL_MANACLE:
			lstrcpy(szTempSkillDoc, "Stun Rate:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Spiritual_Manacle_Ratio[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Spiritual_Manacle_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//猎取
		case SKILL_CHASING_HUNT:
			lstrcpy(szTempSkillDoc, "Increased Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Chasing_Hunt_Sight[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Chasing_Hunt_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//迈克尔
		case SKILL_ADVENT_MIGAL:
			lstrcpy(szTempSkillDoc, "Added Attack Power:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Advent_Migal_Atk[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Advent_Migal_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//祈雨师
		case SKILL_RAIN_MAKER:
			lstrcpy(szTempSkillDoc, "Attack Rating:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Rainmaker_AtkRating[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Absorption:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Rainmaker_Abs[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Rainmaker_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//陆地灵魂
		case SKILL_LAND_OF_GHOST:
			lstrcpy(szTempSkillDoc, "Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Phantom_Call_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Area:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Phantom_Call_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//鬼混重回
		case SKILL_HAUNT:
			lstrcpy(szTempSkillDoc, "Damage (WP):\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Haunt_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Enemy HP Absorption:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Haunt_Abs[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//抓破
		case SKILL_SCRATCH:
			lstrcpy(szTempSkillDoc, "Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Scratch_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//嗜血之夜
		case SKILL_RECALL_BLOODYKNIGHT:
			lstrcpy(szTempSkillDoc, "Attack Type:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			lstrcpy(szTempSkillDoc2, sinAttackType2[pSkill->SkillCodeIndex]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Attack Power:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d\r", Crimson_Knight_Atk[pSkill->Point + i - 1][0], Crimson_Knight_Atk[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Attack Rating:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Crimson_Knight_AtkRating[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Health:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Crimson_Knight_PetHp[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Defense:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Crimson_Knight_Defanse[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", 360, "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//审判
		case SKILL_JUDGEMENT:
			lstrcpy(szTempSkillDoc, "Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Judgement_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//米德兰达
		case SKILL_ADVENT_MIDRANDA:
			lstrcpy(szTempSkillDoc, "Attack Speed Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Advent_Midranda_Speed[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Area:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Advent_Midranda_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Advent_Midranda_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//旭日东升
		case SKILL_MOURNING_OF_PRAY:
			lstrcpy(szTempSkillDoc, "Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Mourning_Pray_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Attack Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Mourning_Pray_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//咒术信仰
		case SKILL_CREED:
			lstrcpy(szTempSkillDoc, "MP Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Creed_AddMP[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "STM Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Creed_AddSP[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Creed_Time[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//诅咒之力
		case SKILL_PRESS_OF_DEITY:
			lstrcpy(szTempSkillDoc, "Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Press_Deity_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Attack Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Press_Deity_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//死亡之爪
		case SKILL_CHOSTY_NAIL:
			lstrcpy(szTempSkillDoc, "Damage:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Phantom_Nail_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Attack Range:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Phantom_Nail_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			//高级再升
		case SKILL_HIGH_REGENERATION:
			lstrcpy(szTempSkillDoc, "HP Increase:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Occult_Lift_HP[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcat(szSkillInfoBuff, "\r");
			lstrcpy(szTempSkillDoc2, "\r");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
		case SKILL_FORCE_ORB:
			lstrcpy(szTempSkillDoc, "Damage Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", ForceOrbDamage[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Weapon Boost:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", 10, "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", ForceOrbUseTime[pSkill->Point + i - 1], "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
		case SKILL_CRYSTAL_ORB:
			lstrcpy(szTempSkillDoc, "Attack Type:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			lstrcpy(szTempSkillDoc2, sinAttackType2[pSkill->SkillCodeIndex]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			lstrcpy(szTempSkillDoc, "Duration:\r");
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", pSkill->UseTime, "sec");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
		case CHANGE_JOB3_QUEST:
			switch (Quest_Flag)
			{
			case SIN_QUEST_CODE_CHANGEJOB:
				wsprintf(szTempSkillDoc, "%s\r", "Golden Wolverine");
				lstrcat(szSkillInfoBuff, szTempSkillDoc);
				lstrcpy(szTempSkillDoc2, "(--/--)\r");
				lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
				LineCount++;
				wsprintf(szTempSkillDoc, "%s\r", "Silver Wolverine");
				lstrcat(szSkillInfoBuff, szTempSkillDoc);
				lstrcpy(szTempSkillDoc2, "(--/--)\r");
				lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
				LineCount++;
				wsprintf(szTempSkillDoc, "%s\r", "Bronze Wolverine");
				lstrcat(szSkillInfoBuff, szTempSkillDoc);
				lstrcpy(szTempSkillDoc2, "(--/--)\r");
				lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
				LineCount++;
				break;
			case SIN_QUEST_CODE_LEVEL30:
				wsprintf(szTempSkillDoc, "%s:\r", szQuestMonsterName);
				lstrcat(szSkillInfoBuff, szTempSkillDoc);
				wsprintf(szTempSkillDoc2, "(%d/%d)\r", sinQuest_Level30.Monster[0], sinQuest_Level30.Monster[1]);
				lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
				LineCount++;
				break;
			case SIN_QUEST_CODE_LEVEL55:
				wsprintf(szTempSkillDoc, "%s:\r", szQuestMonsterName);
				lstrcat(szSkillInfoBuff, szTempSkillDoc);
				wsprintf(szTempSkillDoc2, "(%d/%d)\r", sinQuest_Level55.Monster[0], sinQuest_Level55.Monster[1]);
				lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
				LineCount++;
				break;
			case SIN_QUEST_CODE_LEVEL55_2:
				wsprintf(szTempSkillDoc, "%s:\r", szQuestMonsterName);
				lstrcat(szSkillInfoBuff, szTempSkillDoc);
				wsprintf(szTempSkillDoc2, "(%d/%d)\r", sinQuest_Level55_2.Monster[0], sinQuest_Level55_2.Monster[1]);
				lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
				LineCount++;
				break;
			case SIN_QUEST_CODE_LEVEL70:
				wsprintf(szTempSkillDoc, "%s:\r", szQuestMonsterName);
				lstrcat(szSkillInfoBuff, szTempSkillDoc);
				wsprintf(szTempSkillDoc2, "(%d/%d)\r", sinQuest_Level70.Monster[0], sinQuest_Level70.Monster[1]);
				lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
				LineCount++;
				break;
			case SIN_QUEST_CODE_LEVEL80:
				wsprintf(szTempSkillDoc, "%s:\r", szQuestMonsterName);
				lstrcat(szSkillInfoBuff, szTempSkillDoc);
				wsprintf(szTempSkillDoc2, "(%d/%d)\r", sinQuest_Level80.Monster[0], sinQuest_Level80.Monster[1]);
				lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
				LineCount++;
				break;
			case SIN_QUEST_CODE_LEVEL80_2:
				wsprintf(szTempSkillDoc, "%s:\r", szQuestMonsterName);
				lstrcat(szSkillInfoBuff, szTempSkillDoc);
				wsprintf(szTempSkillDoc2, "--/--\r");
				lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
				LineCount++;
				break;
			case SIN_QUEST_CODE_LEVEL85:
				wsprintf(szTempSkillDoc, "%s:\r", szQuestMonsterName);
				lstrcat(szSkillInfoBuff, szTempSkillDoc);
				wsprintf(szTempSkillDoc2, "(%d/%d)\r", sinQuest_Level85.Monster[0], sinQuest_Level85.Monster[1]);
				lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
				LineCount++;
				break;
			case SIN_QUEST_CODE_LEVEL90:
				wsprintf(szTempSkillDoc, "%s:\r", szQuestMonsterName);
				lstrcat(szSkillInfoBuff, szTempSkillDoc);
				wsprintf(szTempSkillDoc2, "(%d/%d)\r", sinQuest_Level90.Monster[0], sinQuest_Level90.Monster[1]);
				lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
				LineCount++;
				break;
			case SIN_QUEST_CODE_LEVEL90_2:
				wsprintf(szTempSkillDoc, "%s:\r", szQuestMonsterName);
				lstrcat(szSkillInfoBuff, szTempSkillDoc);
				wsprintf(szTempSkillDoc2, "(%d/%d)\r", sinQuest_Level90_2.Monster[0], sinQuest_Level90_2.Monster[1]);
				break;
			case SIN_QUEST_CODE_CHANGEJOB4:
				lstrcpy(szTempSkillDoc, "Time Limit:\r");
				lstrcat(szSkillInfoBuff, szTempSkillDoc);
				wsprintf(szTempSkillDoc2, "%d%s\r", 70, "Min");
				lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
				LineCount++;
				wsprintf(szTempSkillDoc, "%s:\r", szQuestMonsterName);
				lstrcat(szSkillInfoBuff, szTempSkillDoc);
				wsprintf(szTempSkillDoc2, "(%d/%d)\r", sinQuest_ChangeJob4.Monster[0], sinQuest_ChangeJob4.Monster[1]);
				lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
				LineCount++;
				break;
			}
			break;
		case CHANGE_ELEMENTARY_QUEST:
			if (chaQuest.sHaQuest100LV.CODE)
			{
				wsprintf(szTempSkillDoc, "%s:\r", chaQuest.szQuestMonsterName);
				lstrcat(szSkillInfoBuff, szTempSkillDoc);
				wsprintf(szTempSkillDoc2, "(%d/%d)\r", chaQuest.sHaQuest100LV.Monster[0], chaQuest.sHaQuest100LV.Monster[1]);
				lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
				LineCount++;
			}
			else
			{
				if (chaQuest.szQuestMonsterName[0])
				{
					wsprintf(szTempSkillDoc, "%s:\r", chaQuest.szQuestMonsterName);
					lstrcat(szSkillInfoBuff, szTempSkillDoc);
					if (chaQuest.sHaQuestElementary[chaQuest.QuestKeyCode].Monster[1] == 0)
						wsprintf(szTempSkillDoc2, "--/--\r");
					else
						wsprintf(szTempSkillDoc2, "(%d/%d)\r", chaQuest.sHaQuestElementary[chaQuest.QuestKeyCode].Monster[0], chaQuest.sHaQuestElementary[chaQuest.QuestKeyCode].Monster[1]);
					lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
					LineCount++;
				}
			}
			break;
		}
		if (Icon)
		{
			if (pSkill->CODE == SKILL_FORCE_ORB)
			{
				lstrcpy(szTempSkillDoc, "Time left:\r");
				lstrcat(szSkillInfoBuff, szTempSkillDoc);
				smTIME smTime;
				GetSinTime(lpCurPlayer->dwForceOrbTime, &smTime);
				if (smTime.Hour > 0)
					STRINGFORMAT(szTempSkillDoc2, "%02d:%02d:%02d\r", smTime.Hour, smTime.Minute, smTime.Sec);
				else
					STRINGFORMAT(szTempSkillDoc2, "%02d:%02d\r", smTime.Minute, smTime.Sec);
				lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
				LineCount++;
			}
			else
			{
				DWORD dwTime = pSkill->PlayTime;

				if (dwTime != 0)
				{
					lstrcpy(szTempSkillDoc, "Time left:\r");
					lstrcat(szSkillInfoBuff, szTempSkillDoc);
					smTIME smTime;
					GetSinTime(dwTime, &smTime);
					STRINGFORMAT(szTempSkillDoc2, "%02d:%02d\r", smTime.Minute, smTime.Sec);
					lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
					LineCount++;
				}
			}
		}
		if (!Icon)
		{
			if (pSkill->Skill_Info.UseMana)
			{
				lstrcpy(szTempSkillDoc, "Mana Usage:\r");
				lstrcat(szSkillInfoBuff, szTempSkillDoc);
				if (chaPremiumitem.m_ManaReducePotiontime > 0 && chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
					wsprintf(szTempSkillDoc2, "%d(-%d)\r", pSkill->Skill_Info.UseMana[pSkill->Point + i - 1], (pSkill->Skill_Info.UseMana[pSkill->Point + i - 1] * chaPremiumitem.m_ManaReducePotionValue / 100) + (pSkill->Skill_Info.UseMana[pSkill->Point + i - 1] * 20 / 100));
				else if (chaPremiumitem.m_ManaReducePotiontime > 0)
					wsprintf(szTempSkillDoc2, "%d(-%d)\r", pSkill->Skill_Info.UseMana[pSkill->Point + i - 1], (pSkill->Skill_Info.UseMana[pSkill->Point + i - 1] * chaPremiumitem.m_ManaReducePotionValue / 100));
				else if (chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
					wsprintf(szTempSkillDoc2, "%d(-%d)\r", pSkill->Skill_Info.UseMana[pSkill->Point + i - 1], (pSkill->Skill_Info.UseMana[pSkill->Point + i - 1] * 20 / 100));
				else
					wsprintf(szTempSkillDoc2, "%d\r", pSkill->Skill_Info.UseMana[pSkill->Point + i - 1]);

				lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
				LineCount++;
			}
			if (i == 0)
			{
				if (pSkill->Skill_Info.UseStamina[0])
				{
					lstrcpy(szTempSkillDoc, "Stamina Usage:\r");
					lstrcat(szSkillInfoBuff, szTempSkillDoc);
					if (chaPremiumitem.m_StaminaReducePotiontime > 0)
						wsprintf(szTempSkillDoc2, "%d(-%d)\r", pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1)), ((pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1))) * chaPremiumitem.m_StaminaReducePotionValue / 100));
					else
						wsprintf(szTempSkillDoc2, "%d\r", pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1)));
					lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
					LineCount++;
					lstrcat(szSkillInfoBuff, "\r");
					lstrcpy(szTempSkillDoc2, "\r");
					lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
					LineCount++;
				}
			}
			if (i == 1)
			{
				if (pSkill->Skill_Info.UseStamina[0])
				{
					lstrcpy(szTempSkillDoc, "Stamina Usage:\r");
					lstrcat(szSkillInfoBuff, szTempSkillDoc);
					if (chaPremiumitem.m_StaminaReducePotiontime > 0)
						wsprintf(szTempSkillDoc2, "%d(-%d)\r", pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point)), ((pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point))) * chaPremiumitem.m_StaminaReducePotionValue / 100));
					else
						wsprintf(szTempSkillDoc2, "%d\r", pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point)));
					lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
					LineCount++;
				}
			}
		}
	}

	if (SkillMasterFlag == 1 && pSkill->Point < 10)
	{
		lstrcpy(szTempSkillDoc, "Skill Cost:\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);

		wsprintf(szTempSkillDoc2, "%d\r", cShop.haShopItemPrice(sinMasterSkill_Money[pSkill->Skill_Info.SkillNum] + (sinMasterSkill_PlusMoney[pSkill->Skill_Info.SkillNum] * (pSkill->Point))));

		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
	}
	if (!ShowSkillUpInfo)
	{
		lstrcpy(szSkillMasterInfoBuff, szSkillInfoBuff);
		lstrcpy(szSkillMasterInfoBuff2, szSkillInfoBuff2);
	}
	SkillInfoLineCnt = LineCount;
	GetInfoBoxSize(pSkillBox, LineCount, Icon);

	return TRUE;
}

int cSKILL::GetInfoBoxSize(sSKILLBOX *pSkillBox, int Col, int Icon)
{
	int ty, tx;

	SkillBoxSize.x = 14;
	SkillBoxSize.y = Col + 1;

	SkillInfoBoxPosi.x = (pSkillBox->BoxRect.left - 112) + 20;
	SkillInfoBoxPosi.y = pSkillBox->BoxRect.top - (SkillBoxSize.y * 16);

	if (Icon)
	{
		SkillInfoBoxPosi.x = pSkillBox->BoxRect.left;
		SkillInfoBoxPosi.y = pSkillBox->BoxRect.top;
	}

	ty = SkillInfoBoxPosi.y + (SkillBoxSize.y * 16);
	tx = SkillInfoBoxPosi.x + (SkillBoxSize.x * 16);

	if (SkillInfoBoxPosi.y < 0)
		SkillInfoBoxPosi.y = 0;
	if (SkillInfoBoxPosi.x < 0)
		SkillInfoBoxPosi.x = 0;

	if (ty > 600)
		SkillInfoBoxPosi.y -= (ty - 600);
	if (tx > 800)
		SkillInfoBoxPosi.x -= (tx - 800);

	return TRUE;
}
int cSKILL::GetSkillMastery(sSKILL *pSkill, sSKILLBOX *pSkillBox)
{
	int SkillMasteryTemp = 0;
	SkillMasteryTemp = ((int)pSkill->UseSkillMastery / 100);
	wsprintf(szUseSkillMastery, "%d", SkillMasteryTemp);

	UseSkillMasteryPosi.x = pSkillBox->GageRect.left - (34 / 2);
	UseSkillMasteryPosi.y = pSkillBox->GageRect.top - 29;

	return TRUE;
}
int cSKILL::CheckUseSkillState(sSKILL *pSkill)
{
	if (pSkill->Skill_Info.UseMana)
	{
		if (chaPremiumitem.m_ManaReducePotiontime > 0 && chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1 && chaPremiumitem.m_StaminaReducePotiontime > 0)
		{
			if (sinGetMana() >= pSkill->Skill_Info.UseMana[pSkill->Point - 1] - ((pSkill->Skill_Info.UseMana[pSkill->Point - 1] * chaPremiumitem.m_ManaReducePotionValue / 100) + (pSkill->Skill_Info.UseMana[pSkill->Point - 1] * 20 / 100)) && sinGetStamina() >= (pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1))) - ((pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1))) * chaPremiumitem.m_StaminaReducePotionValue / 100))
				pSkill->UseSkillFlag = 1;
			else
				pSkill->UseSkillFlag = 0;
		}
		else if (chaPremiumitem.m_ManaReducePotiontime > 0 && chaPremiumitem.m_StaminaReducePotiontime > 0)
		{
			if (sinGetMana() >= pSkill->Skill_Info.UseMana[pSkill->Point - 1] - (pSkill->Skill_Info.UseMana[pSkill->Point - 1] * chaPremiumitem.m_ManaReducePotionValue / 100) && sinGetStamina() >= (pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1))) - ((pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1))) * chaPremiumitem.m_StaminaReducePotionValue / 100))
				pSkill->UseSkillFlag = 1;
			else
				pSkill->UseSkillFlag = 0;
		}
		else if (chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1 && chaPremiumitem.m_StaminaReducePotiontime > 0)
		{
			if (sinGetMana() >= pSkill->Skill_Info.UseMana[pSkill->Point - 1] - (pSkill->Skill_Info.UseMana[pSkill->Point - 1] * 20 / 100) && sinGetStamina() >= (pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1))) - ((pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1))) * chaPremiumitem.m_StaminaReducePotionValue / 100))
				pSkill->UseSkillFlag = 1;
			else
				pSkill->UseSkillFlag = 0;
		}
		else if (chaPremiumitem.m_ManaReducePotiontime > 0)
		{
			if (sinGetMana() >= pSkill->Skill_Info.UseMana[pSkill->Point - 1] - (pSkill->Skill_Info.UseMana[pSkill->Point - 1] * chaPremiumitem.m_ManaReducePotionValue / 100) && sinGetStamina() >= pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1)))
				pSkill->UseSkillFlag = 1;
			else
				pSkill->UseSkillFlag = 0;
		}
		else if (chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		{
			if (sinGetMana() >= pSkill->Skill_Info.UseMana[pSkill->Point - 1] - (pSkill->Skill_Info.UseMana[pSkill->Point - 1] * 20 / 100) && sinGetStamina() >= pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1)))
				pSkill->UseSkillFlag = 1;
			else
				pSkill->UseSkillFlag = 0;
		}
		else if (chaPremiumitem.m_StaminaReducePotiontime > 0)
		{
			if (sinGetMana() >= pSkill->Skill_Info.UseMana[pSkill->Point - 1] && sinGetStamina() >= (pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1))) - ((pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1))) * chaPremiumitem.m_StaminaReducePotionValue / 100))
				pSkill->UseSkillFlag = 1;
			else
				pSkill->UseSkillFlag = 0;
		}
		else
		{
			if (sinGetMana() >= pSkill->Skill_Info.UseMana[pSkill->Point - 1] && sinGetStamina() >= pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1)))
				pSkill->UseSkillFlag = 1;
			else
				pSkill->UseSkillFlag = 0;
		}
	}
	return TRUE;
}


int SkillDataCheckDelayTime = 0;
int SkillDataCheckFlag2 = 0;
//胶懦 单捞鸥甫 犬牢茄促 
int cSKILL::CheckSkillData()
{
	int i;
	int k;

	SkillDataCheckDelayTime++;
	if (SkillDataCheckDelayTime < 70 * 10)
		return FALSE;
	SkillDataCheckDelayTime = 0;

	unsigned int SkillDataCheckSum = 0;

	unsigned int SkillInfoDataCheckSum = 0;

	for (i = 0; i < 10; i++)
	{
		k = i + 1;
		// 极光护盾
		SkillDataCheckSum += k * E_Shield_BlockRate[i];
		SkillDataCheckSum += k * E_Shield_UseTime[i];
		SkillDataCheckSum += k * E_Shield_UseMana[i];

		//机械榴弹
		SkillDataCheckSum += k * Mechanic_Bomb_Damage[i][0];
		SkillDataCheckSum += k * Mechanic_Bomb_Damage[i][1];
		SkillDataCheckSum += k * Mechanic_Bomb_Attack_Range[i];
		SkillDataCheckSum += k * Mechanic_Bomb_UseMana[i];

		//毒之防御
		SkillDataCheckSum += k * PlusPoison[i];

		////灵光护体
		SkillDataCheckSum += k * P_Absorb[i];
		SkillDataCheckSum += k * P_Absorb_UseTime[i];
		SkillDataCheckSum += k * P_Absor_bUseMana[i];

		//破碎巨击
		SkillDataCheckSum += k * G_Smash_Attack_Rate[i];
		SkillDataCheckSum += k * G_Smash_Attack_Rage[i];
		SkillDataCheckSum += k * G_Smash_UseMana[i];

		//改良专家
		SkillDataCheckSum += k * Maximize_Damage[i];
		SkillDataCheckSum += k * Maximize_Time[i];
		SkillDataCheckSum += k * Maximize_UseMana[i];

		//灵光飞扬
		SkillDataCheckSum += k * Automation_Damage[i];
		SkillDataCheckSum += k * Automation_Speed[i];
		SkillDataCheckSum += k * Automation_Time[i];
		SkillDataCheckSum += k * Automation_UseMana[i];

		//火花电场
		SkillDataCheckSum += k * Spark_Damage[i][0];
		SkillDataCheckSum += k * Spark_Damage[i][1];
		SkillDataCheckSum += k * Spark_Area[i];
		SkillDataCheckSum += k * Spark_UseMana[i];

		//金属重甲
		SkillDataCheckSum += k * Metal_Armor_Defense[i];
		SkillDataCheckSum += k * Metal_Armor_Time[i];
		SkillDataCheckSum += k * Metal_Armor_UseMana[i];

		//星光灭绝
		SkillDataCheckSum += k * Grand_Smash_AttackRate[i];
		SkillDataCheckSum += k * Grand_Smash_Damage[i];
		SkillDataCheckSum += k * Grand_Smash_UseMana[i];

		//优化专家
		SkillDataCheckSum += k * M_Weapon_Mastey[i];

		//防御电波
		SkillDataCheckSum += k * Spark_Shield_Damage[i];
		SkillDataCheckSum += k * Spark_Shield_Defense[i];
		SkillDataCheckSum += k * Spark_Shield_Time[i];
		SkillDataCheckSum += k * Spark_Shield_UseMana[i];

		//雷霆冲击
		SkillDataCheckSum += k * Impulsion_LightingDamage[i];
		SkillDataCheckSum += k * Impulsion_Range[i];
		SkillDataCheckSum += k * Impulsion_LightingNum[i];
		SkillDataCheckSum += k * Impulsion_UseMana[i];

		//威慑怒吼
		SkillDataCheckSum += k * Compulsion_AddAbsorb[i];
		SkillDataCheckSum += k * Compulsion_Area[i];
		SkillDataCheckSum += k * Compulsion_Time[i];
		SkillDataCheckSum += k * Compulsion_UseMana[i];

		//磁性球体
		SkillDataCheckSum += k * Magnetic_Sphere_AddDamage[i][0];
		SkillDataCheckSum += k * Magnetic_Sphere_AddDamage[i][1];
		SkillDataCheckSum += k * Magnetic_Sphere_Area[i];
		SkillDataCheckSum += k * Magnetic_Sphere_AttackDelay[i];
		SkillDataCheckSum += k * Magnetic_Sphere_Time[i];
		SkillDataCheckSum += k * Magnetic_Sphere_UseMana[i];

		//终极机械
		SkillDataCheckSum += k * Metal_Golem_Damage[i][0];
		SkillDataCheckSum += k * Metal_Golem_Damage[i][1];
		SkillDataCheckSum += k * Metal_Golem_Hit[i];
		SkillDataCheckSum += k * Metal_Golem_Defense[i];
		SkillDataCheckSum += k * Metal_Golem_Life[i];
		SkillDataCheckSum += k * Metal_Golem_UseMana[i];

		//霹雳旋风
		SkillDataCheckSum += k * Landminning_AddDamage[i];
		SkillDataCheckSum += k * Landminning_Area[i];
		SkillDataCheckSum += k * Landminning_Num[i];
		SkillDataCheckSum += k * Landminning_UseMana[i];

		//快速打击
		SkillDataCheckSum += k * H_Sonic_Speed[i];
		SkillDataCheckSum += k * H_Sonic_Time[i];
		SkillDataCheckSum += k * H_Sonic_UseMana[i];

		//究极之刃
		SkillDataCheckSum += k * R_Smash_AddDamage[i];
		SkillDataCheckSum += k * R_Smash_UseMana[i];

		//战神祝福
		SkillDataCheckSum += k * P_Enhence_AddDamage[i][0];
		SkillDataCheckSum += k * P_Enhence_AddDamage[i][1];
		SkillDataCheckSum += k * P_Enhence_Defanse[i];
		SkillDataCheckSum += k * P_Enhence_Time[i];
		SkillDataCheckSum += k * P_Enhence_UseMana[i];

		//格斗之术
		SkillDataCheckSum += (int)(k*Melee_Mastery_DamagePercent[i]);

		//火之防御
		SkillDataCheckSum += k * PlusFire[i];

		//绝地暴走
		SkillDataCheckSum += k * Raving_Damage[i];
		SkillDataCheckSum += k * Ravind_Speed[i];
		SkillDataCheckSum += (int)(k*Raving_UseLife[i]);
		SkillDataCheckSum += k * Raving_UseMana[i];

		//精准之击
		SkillDataCheckSum += k * Impact_Attack_Rating[i];
		SkillDataCheckSum += k * Impact_Damage[i];
		SkillDataCheckSum += k * Impact_UseMana[i];

		//威力冲击
		SkillDataCheckSum += k * T_Impact_Damage[i];
		SkillDataCheckSum += k * T_Impact_Hit[i];
		SkillDataCheckSum += k * T_Impact_UseMana[i];

		//致命回旋
		SkillDataCheckSum += k * B_Swing_Damage[i];
		SkillDataCheckSum += k * B_Swing_Critical[i];
		SkillDataCheckSum += k * B_Swing_UseMana[i];

		//极地怒吼
		SkillDataCheckSum += k * Roar_Range[i];
		SkillDataCheckSum += k * Roar_Time[i];
		SkillDataCheckSum += k * Roar_UseMana[i];

		//战神之怒
		SkillDataCheckSum += k * R_Zecram_Damage[i];
		SkillDataCheckSum += k * R_Zecram_Area[i];
		SkillDataCheckSum += k * R_Zecram_UseMana[i];

		//会心一击
		SkillDataCheckSum += k * Concentration_AttackRate[i];
		SkillDataCheckSum += k * Concentration_Time[i];
		SkillDataCheckSum += k * Concentration_UseMana[i];

		//复仇连击
		SkillDataCheckSum += k * A_Crash_Damage[i];
		SkillDataCheckSum += k * A_Crash_AttackRate[i];
		SkillDataCheckSum += k * A_Crash_UseMana[i];

		//刺杀之斧
		SkillDataCheckSum += k * Swift_Axe_Speed[i];
		SkillDataCheckSum += k * Swift_Axe_Time[i];
		SkillDataCheckSum += k * Swift_Axe_UseMana[i];

		//挫骨扬灰
		SkillDataCheckSum += k * B_Crash_Damage[i];
		SkillDataCheckSum += k * B_Crash_DemonDamage[i];
		SkillDataCheckSum += k * B_Crash_UseMana[i];

		//破坏之击
		SkillDataCheckSum += k * Destoryer_DamagePercent[i];
		SkillDataCheckSum += k * Destoryer_AddCritical[i];
		SkillDataCheckSum += k * Destoryer_UseMana[i];

		//疯狂怒吼
		SkillDataCheckSum += k * Berserker_AddAttack[i];
		SkillDataCheckSum += k * Berserker_SubAbsorb[i];
		SkillDataCheckSum += k * Berserker_Time[i];
		SkillDataCheckSum += k * Berserker_UseMana[i];

		//飓风袭击
		SkillDataCheckSum += k * Cyclone_Strike_DamagePercent[i];
		SkillDataCheckSum += k * Cyclone_Strike_AttackNum[i];
		SkillDataCheckSum += k * Cyclone_Strike_Area[i];
		SkillDataCheckSum += k * Cyclone_Strike_UseMana[i];

		//健康专家
		SkillDataCheckSum += k * Boost_Health_Life[i];

		//狂暴怒斩
		SkillDataCheckSum += k * D_Hit_AddDamage[i];
		SkillDataCheckSum += k * D_Hit_UseMana[i];

		//狂野冲击
		SkillDataCheckSum += k * P_Dash_AddDamage[i];
		SkillDataCheckSum += k * P_Dash_Area[i];
		SkillDataCheckSum += k * P_Dash_Time[i];
		SkillDataCheckSum += k * P_Dash_UseMana[i];

		//回旋斩击
		SkillDataCheckSum += k * M_Blow_AddDamage[i];
		SkillDataCheckSum += k * M_Blow_AttackNum[i];
		SkillDataCheckSum += k * M_Blow_Area[i];
		SkillDataCheckSum += k * M_Blow_UseMana[i];

		//众神之怒
		SkillDataCheckSum += k * B_Berserker_AddDamage[i];
		SkillDataCheckSum += k * B_Berserker_Time[i];
		SkillDataCheckSum += k * B_Berserker_UseMana[i];

		//龙卷枪风
		SkillDataCheckSum += k * Pike_Wind_Throw_Height[i];
		SkillDataCheckSum += k * Pike_Wind_Damage[i][0];
		SkillDataCheckSum += k * Pike_Wind_Damage[i][1];
		SkillDataCheckSum += k * Pike_Wind_Push_Lenght[i];
		SkillDataCheckSum += k * Pike_Wind_UseMana[i];

		//冰之防御
		SkillDataCheckSum += k * PlusIce[i];

		//致命打击
		SkillDataCheckSum += k * Critical_Hit_Critical[i];
		SkillDataCheckSum += k * Critical_Hit_UseMana[i];

		//霹雳一击
		SkillDataCheckSum += k * Jumping_Crash_UseMana[i];
		SkillDataCheckSum += k * Jumping_Crash_Attack_Rating[i];
		SkillDataCheckSum += k * Jumping_Crash_Damage[i];

		//大地之枪
		SkillDataCheckSum += k * G_Pike_Damage[i][0];
		SkillDataCheckSum += k * G_Pike_Damage[i][1];
		SkillDataCheckSum += k * G_Pike_Range[i];
		SkillDataCheckSum += k * G_Pike_UseMana[i];
		SkillDataCheckSum += k * G_Pike_Time[i];

		//枪之飓风
		SkillDataCheckSum += k * Tornado_Damage[i];
		SkillDataCheckSum += k * Tornado_Stun[i];
		SkillDataCheckSum += k * Tornado_Range[i];
		SkillDataCheckSum += k * Tornado_UseMana[i];

		//躲避专家
		SkillDataCheckSum += k * W_D_Mastery_Block[i];

		//无限力枪
		SkillDataCheckSum += k * Expansion_Damage[i];
		SkillDataCheckSum += k * Expansion_Size[i];
		SkillDataCheckSum += k * Expansion_UseMana[i];

		//灵蛇标枪
		SkillDataCheckSum += k * VenomSpear_Damage[i];
		SkillDataCheckSum += k * VenomSpear_Num[i];
		SkillDataCheckSum += k * VenomSpear_Time[i];
		SkillDataCheckSum += k * VenomSpear_Range[i];
		SkillDataCheckSum += k * VenomSpear_UseMana[i];

		//隐暗之术
		SkillDataCheckSum += k * (int)Vanish_Speed[i];
		SkillDataCheckSum += k * Vanish_Damage[i];
		SkillDataCheckSum += k * Vanish_Range[i];
		SkillDataCheckSum += k * Vanish_Time[i];
		SkillDataCheckSum += k * Vanish_UseMana[i];

		//会心之枪
		SkillDataCheckSum += k * Critical_Mastery_Critical[i];

		//链骑之枪
		SkillDataCheckSum += k * Chain_Lance_Damage[i];
		SkillDataCheckSum += k * Chain_Lance_UseMana[i];

		//暗杀之眼
		SkillDataCheckSum += k * Assassin_Eye_AddCritical[i];
		SkillDataCheckSum += k * Assassin_Eye_M_SubCritical[i];
		SkillDataCheckSum += k * Assassin_Eye_Time[i];
		SkillDataCheckSum += k * Assassin_Eye_UseMana[i];
		//转换
		SkillDataCheckSum += k * Charging_Strike_DamagePercent[i];
		SkillDataCheckSum += k * Charging_Strike_CharingDamagePercent[i];
		SkillDataCheckSum += k * (int)Charging_Strike_Time[i];
		SkillDataCheckSum += k * Charging_Strike_UseMana[i];
		//影盾
		SkillDataCheckSum += k * Vague_EvasionPercent[i];
		SkillDataCheckSum += k * Vague_Time[i];
		SkillDataCheckSum += k * Vague_UseMana[i];

		//宇宙幻影
		SkillDataCheckSum += k * Shadow_Master_DamagePercent[i];
		SkillDataCheckSum += k * Shadow_Master_AddHit[i];
		SkillDataCheckSum += k * Shadow_Master_ShadowNum[i];
		SkillDataCheckSum += k * Shadow_Master_UseMana[i];

		//回旋打击
		SkillDataCheckSum += k * D_Reaper_AddDamage[i];
		SkillDataCheckSum += k * D_Reaper_UseMana[i];

		//地枪奇袭
		SkillDataCheckSum += k * F_Spear_AddDamage[i];
		SkillDataCheckSum += k * F_Spear_Area[i];
		SkillDataCheckSum += k * F_Spear_Num[i];
		SkillDataCheckSum += k * F_Spear_UseMana[i];

		//潜能激发
		SkillDataCheckSum += k * Amplified_SubAbs[i];
		SkillDataCheckSum += k * Amplified_AddHit[i];
		SkillDataCheckSum += k * Amplified_MinAddDamage[i];
		SkillDataCheckSum += k * Amplified_Time[i];
		SkillDataCheckSum += k * Amplified_UseMana[i];

		//旋风之枪
		SkillDataCheckSum += k * SS_Attack_AddDamage[i];
		SkillDataCheckSum += k * SS_Attack_UseMana[i];

		//侦查之鹰
		SkillDataCheckSum += k * Scout_Hawk_Attack_Rate[i];
		SkillDataCheckSum += k * Scout_Hawk_UseTime[i];
		SkillDataCheckSum += k * Scout_Hawk_UseMana[i];

		//强力之箭
		SkillDataCheckSum += k * S_Mastery_DamagePercent[i];

		//疾风之箭
		SkillDataCheckSum += k * Wind_Arrow_Speed[i];
		SkillDataCheckSum += k * Wind_Arrow_Damage[i];
		SkillDataCheckSum += k * Wind_Arrow_UseMana[i];

		//夺命之箭
		SkillDataCheckSum += k * Perfect_Aim_Attack_Rate[i];
		SkillDataCheckSum += k * Perfect_Aim_Damage[i];
		SkillDataCheckSum += k * Perfect_Aim_Damage_LV[i];
		SkillDataCheckSum += k * Perfect_Aim_UseMana[i];

		//射神之眼
		SkillDataCheckSum += k * D_Eye_Attack_Rate[i];

		//灵魂之鹰
		SkillDataCheckSum += k * Falcon_Damage[i][0];
		SkillDataCheckSum += k * Falcon_Damage[i][1];
		SkillDataCheckSum += k * Falcon_Time[i];
		SkillDataCheckSum += k * Falcon_UseMana[i];

		//狂暴火箭
		SkillDataCheckSum += k * A_Rage_ArrowNum[i];
		SkillDataCheckSum += k * A_Rage_Damage[i];
		SkillDataCheckSum += k * A_Rage_Area[i];
		SkillDataCheckSum += k * A_Rage_UseMana[i];

		//雪崩之箭
		SkillDataCheckSum += k * Avalanche_Speed[i];
		SkillDataCheckSum += k * Avalanche_Damage[i];
		SkillDataCheckSum += k * Avalanche_ArrowNum[i];
		SkillDataCheckSum += k * Avalanche_UseMana[i];

		//元素攻击
		SkillDataCheckSum += k * Elemental_Shot_Ice[i][0];
		SkillDataCheckSum += k * Elemental_Shot_Ice[i][1];
		SkillDataCheckSum += k * Elemental_Shot_Fire[i][0];
		SkillDataCheckSum += k * Elemental_Shot_Fire[i][1];
		SkillDataCheckSum += k * Elemental_Shot_Lightning[i][0];
		SkillDataCheckSum += k * Elemental_Shot_Lightning[i][1];
		SkillDataCheckSum += k * Elemental_Shot_UseMana[i];

		//黄金猎鹰
		SkillDataCheckSum += k * Golden_Falcon_Damage[i];
		SkillDataCheckSum += k * (int)Golden_Falcon_LifeRegen[i];
		SkillDataCheckSum += k * Golden_Falcon_Time[i];
		SkillDataCheckSum += k * Golden_Falcon_UseMana[i];

		//爆裂之箭
		SkillDataCheckSum += k * BombShot_Damage[i];
		SkillDataCheckSum += k * BombShot_DemonDamage[i];
		SkillDataCheckSum += k * BombShot_AddDamage[i][0];
		SkillDataCheckSum += k * BombShot_AddDamage[i][1];
		SkillDataCheckSum += k * BombShot_Area[i];
		SkillDataCheckSum += k * BombShot_UseMana[i];

		//惯穿之箭
		SkillDataCheckSum += k * Perforation_Damage[i];
		SkillDataCheckSum += k * Perforation_Critical[i];
		SkillDataCheckSum += k * Perforation_UseMana[i];
		SkillDataCheckSum += k * Perforation_Attack_Range[i];

		//雪狼
		SkillDataCheckSum += k * Recall_Wolverin_Damage[i][0];
		SkillDataCheckSum += k * Recall_Wolverin_Damage[i][1];
		SkillDataCheckSum += k * Recall_Wolverin_Hit[i];
		SkillDataCheckSum += k * Recall_Wolverin_Defense[i];
		SkillDataCheckSum += k * Recall_Wolverin_Life[i];
		SkillDataCheckSum += k * Recall_Wolverin_UseMana[i];
		//躲避大师
		SkillDataCheckSum += k * Evasion_Mastery_AddPercent[i];
		//绯凰绝炎
		SkillDataCheckSum += k * Phoenix_Shot_DamagePercent[i];
		SkillDataCheckSum += k * (int)Phoenix_Shot_Time[i];
		SkillDataCheckSum += k * Phoenix_Shot_UseMana[i];
		//自然之光
		SkillDataCheckSum += k * Force_Of_Nature_AddDamage[i];
		SkillDataCheckSum += k * Force_Of_Nature_AddHit[i];
		SkillDataCheckSum += k * Force_Of_Nature_FalconAddDamage[i];
		SkillDataCheckSum += k * Force_Of_Nature_Time[i];
		SkillDataCheckSum += k * Force_Of_Nature_UseMana[i];

		//回旋之舞
		SkillDataCheckSum += k * E_Shot_Damge[i];
		SkillDataCheckSum += k * E_Shot_Range[i];
		SkillDataCheckSum += k * E_Shot_UseMana[i];

		//玄光之箭
		SkillDataCheckSum += k * S_Rope_Damge[i];
		SkillDataCheckSum += k * S_Rope_AddRange[i];
		SkillDataCheckSum += k * S_Rope_UseMana[i];

		//飓风之箭
		SkillDataCheckSum += k * N_Splash_Damge[i];
		SkillDataCheckSum += k * N_Splash_Range[i];
		SkillDataCheckSum += k * N_Splash_UseMana[i];

		//复仇箭雨
		SkillDataCheckSum += k * C_Trap_Dmage[i];
		SkillDataCheckSum += k * C_Trap_Area[i];
		SkillDataCheckSum += k * C_Trap_UseMana[i];

		//魔神剑
		SkillDataCheckSum += k * Sword_Blast_UseMana[i];
		SkillDataCheckSum += k * Sword_Blast_Damage[i][0];
		SkillDataCheckSum += k * Sword_Blast_Damage[i][1];
		SkillDataCheckSum += k * Sword_Blast_ShootingRange[i];

		//圣光护体
		SkillDataCheckSum += k * HolyBody_UseMana[i];
		SkillDataCheckSum += k * HolyBody_Absorb[i];
		SkillDataCheckSum += k * HolyBody_Time[i];

		//超能体训
		SkillDataCheckSum += k * P_Traning_Stamina[i];

		//双重爆击
		SkillDataCheckSum += k * D_Crash_UseMana[i];
		SkillDataCheckSum += k * D_Crash_Damage[i];
		SkillDataCheckSum += k * D_Crash_Critical[i];

		//神力重击
		SkillDataCheckSum += k * Holy_Valor_Damage[i];
		SkillDataCheckSum += k * Holy_Valor_Time[i];
		SkillDataCheckSum += k * Holy_Valor_Mana[i];

		//狂躁挥舞
		SkillDataCheckSum += k * Brandish_Range[i];
		SkillDataCheckSum += k * Brandish_Damage[i];
		SkillDataCheckSum += k * Brandish_Mana[i];

		//一雾银
		SkillDataCheckSum += k * Piercing_Damage[i];
		SkillDataCheckSum += k * Piercing_Range[i];
		SkillDataCheckSum += k * Piercing_Mana[i];

		//天佑神铠
		SkillDataCheckSum += k * Drastic_Spirit_Defense[i];
		SkillDataCheckSum += k * Drastic_Spirit_Time[i];
		SkillDataCheckSum += k * Drastic_Spirit_Mana[i];

		//精剑之术
		SkillDataCheckSum += k * Sword_Mastery_DamagePercent[i];

		//圣灵之吸
		SkillDataCheckSum += k * D_Inhalation_Life[i];
		SkillDataCheckSum += k * D_Inhalation_Block[i];
		SkillDataCheckSum += k * D_Inhalation_Time[i];
		SkillDataCheckSum += k * D_Inhalation_UseMana[i];

		//圣剡之光
		SkillDataCheckSum += k * H_Incantation_Success[i];
		SkillDataCheckSum += k * H_Incantation_AddLife[i];
		SkillDataCheckSum += k * H_Incantation_Time[i];
		SkillDataCheckSum += k * H_Incantation_UseMana[i];

		//圣光十字
		SkillDataCheckSum += k * Grand_Cross_Damage[i];
		SkillDataCheckSum += k * Grand_Cross_AttackRate[i];
		SkillDataCheckSum += k * Grand_Cross_UndeadDamage[i];
		SkillDataCheckSum += k * Grand_Cross_UseMana[i];

		//真魔神剑
		SkillDataCheckSum += k * Sword_Of_Justice_DamagePercent[i];
		SkillDataCheckSum += k * Sword_Of_Justice_Area[i];
		SkillDataCheckSum += k * Sword_Of_Justice_UseMana[i];

		//敬神之盾
		SkillDataCheckSum += k * Godly_Shield_AbsorbPercent[i];
		SkillDataCheckSum += k * Godly_Shield_Time[i];
		SkillDataCheckSum += k * Godly_Shield_UseMana[i];

		//上帝祝福
		SkillDataCheckSum += k * God_Bless_AddDamage[i];
		SkillDataCheckSum += k * God_Bless_Time[i];
		SkillDataCheckSum += k * God_Bless_UseMana[i];

		//刹剧荒舞
		SkillDataCheckSum += k * Divine_Piercing_DamagePercent[i];
		SkillDataCheckSum += k * Divine_Piercing_AddHit[i];
		SkillDataCheckSum += k * Divine_Piercing_AttackNum[i];
		SkillDataCheckSum += k * Divine_Piercing_UseMana[i];

		//神力冲刺
		SkillDataCheckSum += k * S_Breaker_Damage[i];
		SkillDataCheckSum += k * S_Breaker_AddHit[i];
		SkillDataCheckSum += k * S_Breaker_UseMana[i];

		//升龙重击
		SkillDataCheckSum += k * C_Moon_Damage[i];
		SkillDataCheckSum += k * C_Moon_Area[i];
		SkillDataCheckSum += k * C_Moon_UseMana[i];

		//上帝重击
		SkillDataCheckSum += k * S_Blade_Damage[i];
		SkillDataCheckSum += k * S_Blade_UndeadDamage[i];
		SkillDataCheckSum += k * S_Blade_UseMana[i];

		//亡灵之咒
		SkillDataCheckSum += k * H_Benedic_Hit[i];
		SkillDataCheckSum += k * H_Benedic_Time[i];
		SkillDataCheckSum += k * H_Benedic_UseMana[i];

		//美杜莎盾
		SkillDataCheckSum += k * S_Strike_UseMana[i];
		SkillDataCheckSum += k * S_Strike_Damage[i][0];
		SkillDataCheckSum += k * S_Strike_Damage[i][1];

		//含沙射影
		SkillDataCheckSum += k * Farina_UseMana[i];
		SkillDataCheckSum += k * Farina_Speed[i];
		SkillDataCheckSum += k * Farina_AttackRate[i];

		//魔力神枪
		SkillDataCheckSum += k * T_Mastery_Damage[i];

		//精神之枪
		SkillDataCheckSum += k * V_Spear_UseMana[i];
		SkillDataCheckSum += k * V_Spear_Damage[i][0];
		SkillDataCheckSum += k * V_Spear_Damage[i][1];

		//追命劲风
		SkillDataCheckSum += k * Windy_Attack_Rating[i];
		SkillDataCheckSum += k * Windy_Time[i];
		SkillDataCheckSum += k * Windy_Mana[i];
		SkillDataCheckSum += k * Twist_Javelin_Damage[i];

		//螺旋飞标
		SkillDataCheckSum += k * Twist_Javelin_Attack_Rating[i];
		SkillDataCheckSum += k * Twist_Javelin_Mana[i];

		//灵魂吞噬
		SkillDataCheckSum += k * Soul_Sucker_Absorb[i];
		SkillDataCheckSum += k * Soul_Sucker_Mana[i];

		//火焰烈枪
		SkillDataCheckSum += k * Fire_Javelin_Damage[i][0];
		SkillDataCheckSum += k * Fire_Javelin_Damage[i][1];
		SkillDataCheckSum += k * Fire_Javelin_Mana[i];

		//追风之枪
		SkillDataCheckSum += k * Split_Javelin_AttackNum[i];
		SkillDataCheckSum += k * Split_Javelin_Damage[i];
		SkillDataCheckSum += k * Split_Javelin_AttackRate[i];
		SkillDataCheckSum += k * Split_Javelin_UseMana[i];

		//战栗咆哮
		SkillDataCheckSum += k * T_Of_Valhalla_Damage[i];
		SkillDataCheckSum += k * T_Of_Valhalla_Time[i];
		SkillDataCheckSum += k * T_Of_Valhalla_UseMana[i];

		//光猎之枪
		SkillDataCheckSum += k * Lightning_Javelin_Damage[i][0];
		SkillDataCheckSum += k * Lightning_Javelin_Damage[i][1];
		SkillDataCheckSum += k * Lightning_Javelin_UseMana[i];

		//暴风狂标
		SkillDataCheckSum += k * Storm_Javelin_Damage[i];
		SkillDataCheckSum += k * Storm_Javelin_UseMana[i];

		//瓦尔哈拉之光
		SkillDataCheckSum += k * Hall_Of_Valhalla_AddEvation[i];
		SkillDataCheckSum += k * Hall_Of_Valhalla_Time[i];
		SkillDataCheckSum += k * Hall_Of_Valhalla_UseMana[i];

		//十字怒击
		SkillDataCheckSum += k * X_Rage_DamagePercent[i];
		SkillDataCheckSum += k * X_Rage_Area[i];
		SkillDataCheckSum += k * X_Rage_UseMana[i];

		//霜冻标枪
		SkillDataCheckSum += k * Frost_Javelin_IceAddDamage[i][0];
		SkillDataCheckSum += k * Frost_Javelin_IceAddDamage[i][1];
		SkillDataCheckSum += k * Frost_Javelin_SpeedSubPercent[i];
		SkillDataCheckSum += k * Frost_Javelin_IceTime[i];
		SkillDataCheckSum += k * Frost_Javelin_Time[i];
		SkillDataCheckSum += k * Frost_Javelin_UseMana[i];

		//狂风爆裂
		SkillDataCheckSum += k * Vengeance_DamagePercent[i];
		SkillDataCheckSum += k * Vengeance_Range[i];
		SkillDataCheckSum += k * Vengeance_UseMana[i];

		//轻舞飞扬
		SkillDataCheckSum += k * Talaria_MoveSpeed[i];
		SkillDataCheckSum += k * Talaria_Time[i];
		SkillDataCheckSum += k * Talaria_UseMana[i];

		//星雨标枪
		SkillDataCheckSum += k * G_Coup_Damage[i];
		SkillDataCheckSum += k * G_Coup_Hit[i];
		SkillDataCheckSum += k * G_Coup_UseMana[i];

		//笨笨熊
		SkillDataCheckSum += k * S_Arcuda_Damage[i][0];
		SkillDataCheckSum += k * S_Arcuda_Damage[i][1];
		SkillDataCheckSum += k * S_Arcuda_AtkRating[i];
		SkillDataCheckSum += k * S_Arcuda_PetHp[i];
		SkillDataCheckSum += k * S_Arcuda_Defanse[i];
		SkillDataCheckSum += k * S_Arcuda_UseMana[i];

		//烈焰突袭
		SkillDataCheckSum += k * S_Fear_Damage[i];
		SkillDataCheckSum += k * S_Fear_AddCritical[i];
		SkillDataCheckSum += k * S_Fear_UseMana[i];

		//治愈之术
		SkillDataCheckSum += k * Healing_UseMana[i];
		SkillDataCheckSum += k * Healing_Heal[i][0];
		SkillDataCheckSum += k * Healing_Heal[i][1];

		//圣光电球
		SkillDataCheckSum += k * HolyBolt_UseMana[i];
		SkillDataCheckSum += k * HolyBolt_Damage[i][0];
		SkillDataCheckSum += k * HolyBolt_Damage[i][1];

		//光芒四射
		SkillDataCheckSum += k * M_Spark_UseMana[i];
		SkillDataCheckSum += k * M_Spark_Damage[i][0];
		SkillDataCheckSum += k * M_Spark_Damage[i][1];
		SkillDataCheckSum += k * M_Spark_Num[i];

		//意念之术
		SkillDataCheckSum += k * HolyMind_UseMana[i];
		SkillDataCheckSum += k * HolyMind_DecDamage[i];
		SkillDataCheckSum += k * HolyMind_Time[i];

		//曙光耀灵
		SkillDataCheckSum += k * (int)Meditation_Regen[i];

		//神之雷电
		SkillDataCheckSum += k * Divine_Lightning_Damage[i][0];
		SkillDataCheckSum += k * Divine_Lightning_Damage[i][1];
		SkillDataCheckSum += k * Divine_Lightning_Num[i];
		SkillDataCheckSum += k * Divine_Lightning_Mana[i];

		//神圣反射
		SkillDataCheckSum += k * Holy_Reflection_Return_Damage[i];
		SkillDataCheckSum += k * Holy_Reflection_Time[i];
		SkillDataCheckSum += k * Holy_Reflection_Mana[i];

		//圣洁之光
		SkillDataCheckSum += k * Grand_Healing[i][0];
		SkillDataCheckSum += k * Grand_Healing[i][1];
		SkillDataCheckSum += k * Grand_Healing_Range[i];
		SkillDataCheckSum += k * Grand_Healing_Mana[i];

		//火影双重
		SkillDataCheckSum += k * Vigor_Ball_Damage[i][0];
		SkillDataCheckSum += k * Vigor_Ball_Damage[i][1];
		SkillDataCheckSum += k * Vigor_Ball_UseMana[i];

		//回生之术
		SkillDataCheckSum += k * Resurrection_Percent[i];
		SkillDataCheckSum += k * Resurrection_Exp[i];
		SkillDataCheckSum += k * Resurrection_UseMana[i];

		//圣光之咒
		SkillDataCheckSum += k * Extinction_Percent[i];
		SkillDataCheckSum += k * Extinction_Amount[i];
		SkillDataCheckSum += k * Extinction_UseMana[i];

		//神圣之光
		SkillDataCheckSum += k * Virtual_Life_Percent[i];
		SkillDataCheckSum += k * Virtual_Life_Time[i];
		SkillDataCheckSum += k * Virtual_Life_UseMana[i];

		//冰霜噬月
		SkillDataCheckSum += k * Glacial_Spike_Damage[i][0];
		SkillDataCheckSum += k * Glacial_Spike_Damage[i][1];
		SkillDataCheckSum += k * Glacial_Spike_Area[i];
		SkillDataCheckSum += k * Glacial_Spike_UseMana[i];

		//再生领域
		SkillDataCheckSum += k * (int)Regeneration_Field_LifeRegen[i];
		SkillDataCheckSum += k * (int)Regeneration_Field_ManaRegen[i];
		SkillDataCheckSum += k * Regeneration_Field_Time[i];
		SkillDataCheckSum += k * Regeneration_Field_Area[i];
		SkillDataCheckSum += k * Regeneration_Field_UseMana[i];

		//天雷之怒
		SkillDataCheckSum += k * Chain_Lightning_Damage[i][0];
		SkillDataCheckSum += k * Chain_Lightning_Damage[i][1];
		SkillDataCheckSum += k * Chain_Lightning_Num[i];
		SkillDataCheckSum += k * Chain_Lightning_Range[i];
		SkillDataCheckSum += k * Chain_Lightning_UseMana[i];

		//神圣天使
		SkillDataCheckSum += k * Summon_Muspell_Damage[i][0];
		SkillDataCheckSum += k * Summon_Muspell_Damage[i][1];
		SkillDataCheckSum += k * Summon_Muspell_Attack_Delay[i];
		SkillDataCheckSum += k * Summon_Muspell_UndeadAbsorbPercent[i];
		SkillDataCheckSum += k * Summon_Muspell_BlockPercent[i];
		SkillDataCheckSum += k * Summon_Muspell_Time[i];
		SkillDataCheckSum += k * Summon_Muspell_UseMana[i];

		//神圣电波
		SkillDataCheckSum += k * S_Impact_Damage[i][0];
		SkillDataCheckSum += k * S_Impact_Damage[i][1];
		SkillDataCheckSum += k * S_Impact_Range[i];
		SkillDataCheckSum += k * S_Impact_UseMana[i];

		//神之冰刃
		SkillDataCheckSum += k * P_Ice_Damge[i][0];
		SkillDataCheckSum += k * P_Ice_Damge[i][1];
		SkillDataCheckSum += k * P_Ice_Frozen[i];
		SkillDataCheckSum += k * P_Ice_UseMana[i];

		//暴风雪
		SkillDataCheckSum += k * S_Ramiel_Damage[i][0];
		SkillDataCheckSum += k * S_Ramiel_Damage[i][1];
		SkillDataCheckSum += k * S_Ramiel_Area[i];
		SkillDataCheckSum += k * S_Ramiel_Num[i];
		SkillDataCheckSum += k * S_Ramiel_UseMana[i];

		//天女散花
		SkillDataCheckSum += k * B_Krishna_Evasion[i];
		SkillDataCheckSum += k * B_Krishna_Abs[i];
		SkillDataCheckSum += k * B_Krishna_Time[i];
		SkillDataCheckSum += k * B_Krishna_UseMana[i];

		//魔力转化
		SkillDataCheckSum += k * Agony_UseMana[i];
		SkillDataCheckSum += k * Agony_ConvLife[i];

		//火箭之术
		SkillDataCheckSum += k * FireBolt_UseMana[i];
		SkillDataCheckSum += k * FireBolt_Damage[i][0];
		SkillDataCheckSum += k * FireBolt_Damage[i][1];

		//集合之术
		SkillDataCheckSum += k * Zenith_UseMana[i];
		SkillDataCheckSum += k * Zenith_Element[i];
		SkillDataCheckSum += k * Zenith_Time[i];

		//火球之术
		SkillDataCheckSum += k * FireBall_UseMana[i];
		SkillDataCheckSum += k * FireBall_Damage[i][0];
		SkillDataCheckSum += k * FireBall_Damage[i][1];
		SkillDataCheckSum += k * FireBall_Range[i];

		//控制意念
		SkillDataCheckSum += k * Mental_Mastery_Mana[i];

		//龙卷海风
		SkillDataCheckSum += k * Watornado_Damage[i][0];
		SkillDataCheckSum += k * Watornado_Damage[i][1];
		SkillDataCheckSum += k * Watornado_Area[i];
		SkillDataCheckSum += k * Watornado_Range[i];
		SkillDataCheckSum += k * Watornado_Mana[i];

		//元素之术
		SkillDataCheckSum += k * Enchant_Weapon_Damage_Ice[i][0];
		SkillDataCheckSum += k * Enchant_Weapon_Damage_Ice[i][1];
		SkillDataCheckSum += k * Enchant_Weapon_Damage_Fire[i][0];
		SkillDataCheckSum += k * Enchant_Weapon_Damage_Fire[i][1];
		SkillDataCheckSum += k * Enchant_Weapon_Damage_Lightning[i][0];
		SkillDataCheckSum += k * Enchant_Weapon_Damage_Lightning[i][1];
		SkillDataCheckSum += k * Enchant_Weapon_Time[i];
		SkillDataCheckSum += k * Enchant_Weapon_Mana[i];

		//冥亡之光
		SkillDataCheckSum += k * Dead_Ray_Damage[i][0];
		SkillDataCheckSum += k * Dead_Ray_Damage[i][1];
		SkillDataCheckSum += k * Dead_Ray_Range[i];
		SkillDataCheckSum += k * Dead_Ray_Mana[i];

		//魔法守护
		SkillDataCheckSum += k * Energy_Shield_DecDamage[i];
		SkillDataCheckSum += k * Energy_Shield_Time[i];
		SkillDataCheckSum += k * Energy_Shield_UseMana[i];

		//地裂冲击
		SkillDataCheckSum += k * Diastrophism_Damage[i][0];
		SkillDataCheckSum += k * Diastrophism_Damage[i][1];
		SkillDataCheckSum += k * Diastrophism_Area[i];
		SkillDataCheckSum += k * Diastrophism_UseMana[i];

		//灵魂召唤
		SkillDataCheckSum += k * (int)Spirit_Elemental_RegenMana[i];
		SkillDataCheckSum += k * Spirit_Elemental_Damage[i];
		SkillDataCheckSum += k * Spirit_Elemental_Time[i];
		SkillDataCheckSum += k * Spirit_Elemental_UseMana[i];

		//元素之剑
		SkillDataCheckSum += k * Dancing_Sword_IceDamage[i][0];
		SkillDataCheckSum += k * Dancing_Sword_IceDamage[i][1];
		SkillDataCheckSum += k * Dancing_Sword_FireDamage[i][0];
		SkillDataCheckSum += k * Dancing_Sword_FireDamage[i][1];
		SkillDataCheckSum += k * Dancing_Sword_AttackDelay[i];
		SkillDataCheckSum += k * Dancing_Sword_Time[i];
		SkillDataCheckSum += k * Dancing_Sword_UseMana[i];

		//伊夫列特
		SkillDataCheckSum += k * Fire_Elemental_Damage[i][0];
		SkillDataCheckSum += k * Fire_Elemental_Damage[i][1];
		SkillDataCheckSum += k * Fire_Elemental_Hit[i];
		SkillDataCheckSum += k * Fire_Elemental_Life[i];
		SkillDataCheckSum += k * Fire_Elemental_UseMana[i];

		//火焰波动
		SkillDataCheckSum += k * Flame_Wave_FireDamage[i][0];
		SkillDataCheckSum += k * Flame_Wave_FireDamage[i][1];
		SkillDataCheckSum += k * Flame_Wave_Area[i];
		SkillDataCheckSum += k * Flame_Wave_UseMana[i];

		//空间扭曲
		SkillDataCheckSum += k * Distortion_SpeedSubPercent[i];
		SkillDataCheckSum += k * Distortion_DamageSubPercent[i];
		SkillDataCheckSum += k * Distortion_Area[i];
		SkillDataCheckSum += k * Distortion_Time[i];
		SkillDataCheckSum += k * Distortion_UseMana[i];

		//招呼陨石
		SkillDataCheckSum += k * Meteo_Damage[i][0];
		SkillDataCheckSum += k * Meteo_Damage[i][1];
		SkillDataCheckSum += k * Meteo_Area[i];
		SkillDataCheckSum += k * Meteo_UseMana[i];

		//流星火雨
		SkillDataCheckSum += k * Silraphim_Damage[i][0];
		SkillDataCheckSum += k * Silraphim_Damage[i][1];
		SkillDataCheckSum += k * Silraphim_Range[i];
		SkillDataCheckSum += k * Silraphim_UseMana[i];

		//缩小之术
		SkillDataCheckSum += k * V_Tenus_SubSpeed[i];
		SkillDataCheckSum += k * V_Tenus_Time[i];
		SkillDataCheckSum += k * V_Tenus_Range[i];
		SkillDataCheckSum += k * V_Tenus_UseMana[i];

		//神圣洗礼
		SkillDataCheckSum += k * P_Ignis_Dmage[i][0];
		SkillDataCheckSum += k * P_Ignis_Dmage[i][1];
		SkillDataCheckSum += k * P_Ignis_Area[i];
		SkillDataCheckSum += k * P_Ignis_Hit[i];
		SkillDataCheckSum += k * P_Ignis_UseMana[i];

		//神圣法阵
		SkillDataCheckSum += k * T_Anima_Dmage[i];
		SkillDataCheckSum += k * T_Anima_Time[i];
		SkillDataCheckSum += k * T_Anima_UseMana[i];

		//刺击
		SkillDataCheckSum += k * Stinger_Damage[i];
		SkillDataCheckSum += k * Stinger_UseMana[i];

		//闪击
		SkillDataCheckSum += k * Running_Hit_Damage[i];
		SkillDataCheckSum += k * Running_Hit_UseMana[i];

		//强化攻击
		SkillDataCheckSum += k * Sword_Mastery_Damage[i];

		//弱点攻击
		SkillDataCheckSum += k * Wisp_Damage[i];
		SkillDataCheckSum += k * Wisp_Range[i];
		SkillDataCheckSum += k * Wisp_Time[i];
		SkillDataCheckSum += k * Wisp_UseMana[i];

		//毒牙连击
		SkillDataCheckSum += k * Venom_Thorn_Damage[i];
		SkillDataCheckSum += k * Venom_Thorn_Ratio[i];
		SkillDataCheckSum += k * Verom_Thorn_Time[i];
		SkillDataCheckSum += k * Verom_Thorn_UseMana[i];

		//敏捷之力
		SkillDataCheckSum += k * Alas_Eavsion[i];
		SkillDataCheckSum += k * Alas_Area[i];
		SkillDataCheckSum += k * Alas_Time[i];
		SkillDataCheckSum += k * Ales_UseMana[i];

		//灵魂震撼
		SkillDataCheckSum += k * Soul_Shock_Area[i];
		SkillDataCheckSum += k * Soul_Shock_Time[i];
		SkillDataCheckSum += k * Soul_Shock_UseMana[i];

		//攻击大师
		SkillDataCheckSum += k * Blade_Mastery_Attack[i];
		SkillDataCheckSum += k * Blade_Mastery_Evasion[i];

		//飞剑之舞
		SkillDataCheckSum += k * Finishing_Blow_Damage[i];
		SkillDataCheckSum += k * Finishing_Blow_UseMana[i];

		//跳斩
		SkillDataCheckSum += k * Gust_Slash_Damage[i];
		SkillDataCheckSum += k * Gust_Slash_Area[i];
		SkillDataCheckSum += k * Gust_Shash_UseMana[i];

		//敏捷大师
		SkillDataCheckSum += k * Inpes_Atk_Speed[i];
		SkillDataCheckSum += k * Inpes_Time[i];
		SkillDataCheckSum += k * Inpes_UseMana[i];

		//致盲
		SkillDataCheckSum += k * Deception_Damage[i];
		SkillDataCheckSum += k * Deception_Visibility[i];
		SkillDataCheckSum += k * Deception_Time[i];
		SkillDataCheckSum += k * Deception_UseMana[i];

		//冰冻之刃
		SkillDataCheckSum += k * Frost_Wind_Damage[i];
		SkillDataCheckSum += k * Frost_Wind_UseMana[i];

		//致盲
		SkillDataCheckSum += k * Fatal_Mastery_Critical[i];

		//瘟疫之刃
		SkillDataCheckSum += k * Pollute_Damage[i];
		SkillDataCheckSum += k * Pollute_Area[i];
		SkillDataCheckSum += k * Pollute_Ratio[i];
		SkillDataCheckSum += k * Pollute_Time[i];
		SkillDataCheckSum += k * Pollute_UseMana[i];

		//影子闪击
		SkillDataCheckSum += k * Shadow_Damage[i];
		SkillDataCheckSum += k * Shadow_UseMana[i];

		//影子火焰
		SkillDataCheckSum += k * Shadow_Bomb_Damage[i];
		SkillDataCheckSum += k * Shadow_Bomb_Area[i];
		SkillDataCheckSum += k * Shadow_Bomb_Ratio[i];
		SkillDataCheckSum += k * Shadow_Bomb_Time[i];
		SkillDataCheckSum += k * Shadow_Bomb_UseMana[i];

		//地裂斩
		SkillDataCheckSum += k * Rising_Slash_Damage[i];
		SkillDataCheckSum += k * Rising_Shash_UseMana[i];

		//猛龙摆尾
		SkillDataCheckSum += k * Violent_Stub_Damage[i];
		SkillDataCheckSum += k * Violent_Stub_UseMana[i];

		//风暴之刃
		SkillDataCheckSum += k * Shadow_Storm_Damage[i];
		SkillDataCheckSum += k * Shadow_Storm_Area[i];
		SkillDataCheckSum += k * Shadow_Storm_Range[i];
		SkillDataCheckSum += k * Shadow_Storm_PushRange[i];
		SkillDataCheckSum += k * Shadow_Storm_UseMana[i];

		//暗黑闪电
		SkillDataCheckSum += k * Dark_Bolt_Damage[i];
		SkillDataCheckSum += k * Dark_Bolt_UseMana[i];

		//暗黑波浪
		SkillDataCheckSum += k * Dark_Wave_Damage[i];
		SkillDataCheckSum += k * Dark_Wave_UseMana[i];

		//诅咒雷击
		SkillDataCheckSum += k * Inertia_Speed[i];
		SkillDataCheckSum += k * Inertia_Atk[i];
		SkillDataCheckSum += k * Inertia_Area[i];
		SkillDataCheckSum += k * Inertia_Time[i];
		SkillDataCheckSum += k * Inertia_UseMana[i];

		//内心平和
		SkillDataCheckSum += k * Inner_Peace_AddMana[i];

		//精神咒术
		SkillDataCheckSum += k * Spiritual_Flare_Damage[i];
		SkillDataCheckSum += k * Spiritual_Flare_Rnage[i];
		SkillDataCheckSum += k * Spiritual_Flare_Area[i];
		SkillDataCheckSum += k * Spiritual_Flare_UseMana[i];

		//灵魂枷锁
		SkillDataCheckSum += k * Spiritual_Manacle_Ratio[i];
		SkillDataCheckSum += k * Spiritual_Manacle_Time[i];
		SkillDataCheckSum += k * Spiritual_Manacle_UseMana[i];

		//猎取
		SkillDataCheckSum += k * Chasing_Hunt_Sight[i];
		SkillDataCheckSum += k * Chasing_Hunt_Time[i];
		SkillDataCheckSum += k * Chasing_Hunt_UseMana[i];

		//迈克尔
		SkillDataCheckSum += k * Advent_Migal_Atk[i];
		SkillDataCheckSum += k * Advent_Migal_Time[i];
		SkillDataCheckSum += k * Advent_Migal_UseMana[i];

		//祈雨师
		SkillDataCheckSum += k * Rainmaker_Abs[i];
		SkillDataCheckSum += k * Rainmaker_AtkRating[i];
		SkillDataCheckSum += k * Rainmaker_Time[i];
		SkillDataCheckSum += k * Rainmaker_UseMana[i];

		//陆地灵魂
		SkillDataCheckSum += k * Phantom_Call_Damage[i];
		SkillDataCheckSum += k * Phantom_Call_Area[i];
		SkillDataCheckSum += k * Phantom_Call_UseMana[i];

		//鬼魂重回
		SkillDataCheckSum += k * Haunt_Damage[i];
		SkillDataCheckSum += k * Haunt_Abs[i];
		SkillDataCheckSum += k * Haunt_UseMana[i];

		//抓破
		SkillDataCheckSum += k * Scratch_Damage[i];
		SkillDataCheckSum += k * Scratch_UseMana[i];

		//嗜血之夜
		SkillDataCheckSum += k * Crimson_Knight_Atk[i][0];
		SkillDataCheckSum += k * Crimson_Knight_Atk[i][1];
		SkillDataCheckSum += k * Crimson_Knight_AtkRating[i];
		SkillDataCheckSum += k * Crimson_Knight_PetHp[i];
		SkillDataCheckSum += k * Crimson_Knight_Defanse[i];
		SkillDataCheckSum += k * Crimson_Knight_UseMana[i];

		//鬼魂重回
		SkillDataCheckSum += k * Judgement_Damage[i];
		SkillDataCheckSum += k * Judgement_UseMana[i];

		//米德兰达
		SkillDataCheckSum += k * Advent_Midranda_Speed[i];
		SkillDataCheckSum += k * Advent_Midranda_Area[i];
		SkillDataCheckSum += k * Advent_Midranda_Time[i];
		SkillDataCheckSum += k * Advent_Midranda_UseMana[i];

		//旭日东升
		SkillDataCheckSum += k * Mourning_Pray_Damage[i];
		SkillDataCheckSum += k * Mourning_Pray_Area[i];
		SkillDataCheckSum += k * Mourning_Pray_UseMana[i];

		//咒术信仰
		SkillDataCheckSum += k * Creed_AddMP[i];
		SkillDataCheckSum += k * Creed_AddSP[i];
		SkillDataCheckSum += k * Creed_Time[i];
		SkillDataCheckSum += k * Creed_UseMana[i];

		//诅咒之力
		SkillDataCheckSum += k * Press_Deity_Damage[i];
		SkillDataCheckSum += k * Press_Deity_Area[i];
		SkillDataCheckSum += k * Press_UseMana[i];

		//死亡之爪
		SkillDataCheckSum += k * Phantom_Nail_Damage[i];
		SkillDataCheckSum += k * Phantom_Nail_Area[i];
		SkillDataCheckSum += k * Phantom_Nail_UseMana[i];

		//高级再升
		SkillDataCheckSum += k * Occult_Lift_HP[i];
	}

	unsigned int sinSKillInfoData = 5105831;
	unsigned int sinSKillData = 10330138;


	if (sinSKillData != SkillDataCheckSum)
		SendSetHackUser(5);

	for (i = 0; i < SIN_MAX_SKILL; i++)
	{
		k = i + 1;
		SkillInfoDataCheckSum += k * sSkill_Info[i].RequireLevel;
		SkillInfoDataCheckSum += k * sSkill_Info[i].UseStamina[0];
		SkillInfoDataCheckSum += k * sSkill_Info[i].UseStamina[1];
		SkillInfoDataCheckSum += k * sSkill_Info[i].RequireMastery[0];
		SkillInfoDataCheckSum += k * sSkill_Info[i].RequireMastery[1];
	}

	//技能中断
	if (sinSKillInfoData != SkillInfoDataCheckSum)
		SendSetHackUser(5);

	for (int j = 1; j < SIN_MAX_USE_SKILL; j++)
	{
		if (sinSkill.UseSkill[j].Flag)
		{
			if (!SkillDataCheckFlag2)
				ReformSkillPointForm(&sinSkill.UseSkill[j]);

			if (!CheckSkillPointForm(&sinSkill.UseSkill[j]))
				return FALSE;
			if (!CheckSkillMasteryForm(&sinSkill.UseSkill[j]))
				return FALSE;
		}
	}
	SkillDataCheckFlag2 = 1;


	return TRUE;
}


//初始化技能点
int cSKILL::InitSkillPoint(int kind)
{
	switch (kind)
	{
	case 0:
		if (!sinInitPointPassFlag)
		{
			if (sinChar->wVersion[1] == 1)
			{
				cMessageBox.ShowMessage(MESSAGE_ALREADY_INITSTATE);
				return FALSE;
			}
		}
		break;
	}
	sinInitPointPassFlag = 0;

	CheckingNowSkillState();
	CheckCharForm();
	int Count = 0;
	int Count2 = 0;

	for (int j = 1; j < ChangeJobSkillPlus; j++)
	{
		if (j > 12)
		{
			if (sinSkill.UseSkill[j].Point > 0)
				Count2 += sinSkill.UseSkill[j].Point;
		}
		else
		{
			if (sinSkill.UseSkill[j].Point > 0)
				Count += sinSkill.UseSkill[j].Point;
		}

		cSkill.CheckSkillMasteryForm(0, j);
		CheckSkillPointForm(&sinSkill.UseSkill[j]);
		sinSkill.UseSkill[j].Point = 0;
		sinSkill.UseSkill[j].GageLength = 0;
		sinSkill.UseSkill[j].GageLength2 = 0;
		sinSkill.UseSkill[j].Mastery = 0;
		sinSkill.UseSkill[j].UseSKillIncreCount = 0;
		sinSkill.UseSkill[j].UseSkillCount = 0;
		sinSkill.UseSkill[j].UseSkillMastery = 0;
		sinSkill.UseSkill[j].UseSkillMasteryGage = 0;
		sinSkill.UseSkill[j].Use = 0;
		ReformSkillPointForm(&sinSkill.UseSkill[j]);
		ReformSkillMasteryForm(0, j);

	}
	sinSkill.SkillPoint += Count;
	sinSkill.SkillPoint4 += Count2;
	sinChar->wVersion[1] = 1;
	ReformCharForm();
	cMessageBox.ShowMessage(MESSAGE_GYUNGFUM_OK);
	cInvenTory.SetItemToChar();

	return TRUE;
}


DWORD ClearSkillPointCODE[10] = { 0,0,0,0,0,0,0,0,0,0 };

int cSKILL::SearchClearSkillPoint(DWORD CODE)
{

	for (int i = 0; i < 10; i++)
	{
		if (ClearSkillPointCODE[i] == CODE)
		{
			ClearSkillCODE = ClearSkillPointCODE[i];
			return TRUE;
		}
		else
			ClearSkillCODE = 0;
	}

	return FALSE;

}
int cSKILL::ShowClearSkillPointButton(int x, int y)
{
	ClearSkillButtonPosi.x = -50;
	ClearSkillButtonPosi.y = -50;

	if (ClearSkillCODE && !sinMessageBoxShowFlag)
	{
		ClearSkillButtonPosi.x = x - 57;
		ClearSkillButtonPosi.y = y - 51;
		DrawSprite(ClearSkillButtonPosi.x, ClearSkillButtonPosi.y, lpSkillDown, 0, 0, 50, 44);
	}

	return TRUE;
}

//清除技能点
int cSKILL::ClearSkillPointSection()
{
	CheckingNowSkillState();
	CheckCharForm();

	int Count = 0;

	for (int j = 1; j < ChangeJobSkillPlus; j++)
	{
		if (sinSkill.UseSkill[j].Flag && sinSkill.UseSkill[j].Point > 1)
		{
			for (int i = 0; i < 10; i++)
			{
				if (sinSkill.UseSkill[j].CODE == ClearSkillPointCODE[i])
				{
					cSkill.CheckSkillMasteryForm(0, j);
					CheckSkillPointForm(&sinSkill.UseSkill[j]);
					sinSkill.UseSkill[j].Point--;
					sinSkill.UseSkill[j].GageLength = 0;
					sinSkill.UseSkill[j].GageLength2 = 0;
					sinSkill.UseSkill[j].Mastery = 0;
					sinSkill.UseSkill[j].UseSKillIncreCount = 0;
					sinSkill.UseSkill[j].UseSkillCount = 0;
					sinSkill.UseSkill[j].UseSkillMastery = 0;
					sinSkill.UseSkill[j].UseSkillMasteryGage = 0;
					sinSkill.UseSkill[j].Use = 0;
					ReformSkillPointForm(&sinSkill.UseSkill[j]);
					ReformSkillMasteryForm(0, j);
					sinSkill.SkillPoint++;
					ClearSkillCODE = 0;
					LearnSkillEffect(0);
					ReformCharForm();
					return TRUE;
				}
			}
		}
	}
	return TRUE;
}


unsigned int CharSkillInfoData[10] = { 0, };
int   ChangeJob = -1;

int cSKILL::ReFormCharSkillInfo()
{
	int   i = 0, j = 0, k = 0;
	int   CharNum = 0;

	int   CharCode[10] = { CHARACTERCLASS_Mechanician,CHARACTERCLASS_Fighter,SIN_CHAR_ARCHER,CHARACTERCLASS_Pikeman,CHARACTERCLASS_Knight,CHARACTERCLASS_Atalanta,CHARACTERCLASS_Priestess,CHARACTERCLASS_Magician,CHARACTERCLASS_Assassin,CHARACTERCLASS_Shaman };

	for (i = 0; i < 10; i++)
	{
		if (sinChar->iClass == CharCode[i])
		{
			CharNum = i;
			break;
		}
	}

	if (ChangeJob != sinChar->iRank)
	{
		ChangeJob = sinChar->iRank;
		CharSkillInfoData[CharNum] = 0;

		for (j = 1; j < SIN_MAX_USE_SKILL; j++)
		{
			if (sinSkill.UseSkill[j].Flag)
			{
				k = j + 1;
				CharSkillInfoData[CharNum] += k * sinSkill.UseSkill[j].Skill_Info.RequireLevel;
				CharSkillInfoData[CharNum] += k * sinSkill.UseSkill[j].Skill_Info.UseStamina[0];
				CharSkillInfoData[CharNum] += k * sinSkill.UseSkill[j].Skill_Info.UseStamina[1];
			}
		}
	}
	return TRUE;
}

//检测技能信息
int cSKILL::CheckCharSkillInfo()
{
	int   i = 0, j = 0, k = 0;
	int   CharNum = 0;
	int   CharCode[10] = { CHARACTERCLASS_Mechanician,CHARACTERCLASS_Fighter,SIN_CHAR_ARCHER,CHARACTERCLASS_Pikeman,CHARACTERCLASS_Knight,CHARACTERCLASS_Atalanta,CHARACTERCLASS_Priestess,CHARACTERCLASS_Magician,CHARACTERCLASS_Assassin,CHARACTERCLASS_Shaman };

	unsigned int CharSkillInfoDataCheckSum[10] = { 0, };

	for (i = 0; i < 10; i++)
	{
		if (sinChar->iClass == CharCode[i])
		{
			CharNum = i;
			break;
		}
	}

	for (j = 1; j < SIN_MAX_USE_SKILL; j++)
	{
		if (sinSkill.UseSkill[j].Flag)
		{
			k = j + 1;
			CharSkillInfoDataCheckSum[CharNum] += k * sinSkill.UseSkill[j].Skill_Info.RequireLevel;
			CharSkillInfoDataCheckSum[CharNum] += k * sinSkill.UseSkill[j].Skill_Info.UseStamina[0];
			CharSkillInfoDataCheckSum[CharNum] += k * sinSkill.UseSkill[j].Skill_Info.UseStamina[1];

			if (!sinSkill.UseSkill[j].UseSkillCount)
				continue;

			if (!CheckSkillMasteyData[j])
				CheckSkillMasteyData[j] = sinSkill.UseSkill[j].UseSkillCount;
			if (CheckSkillMasteyData[j] < (sinSkill.UseSkill[j].UseSkillCount) - 200)
			{
				SendSetHackUser3(55, CheckSkillMasteyData[j], sinSkill.UseSkill[j].UseSkillCount);
				return FALSE;
			}
			else
				CheckSkillMasteyData[j] = sinSkill.UseSkill[j].UseSkillCount;
		}
	}
	if (CharSkillInfoDataCheckSum[CharNum] != CharSkillInfoData[CharNum])
	{
		SendSetHackUser3(51, CharSkillInfoDataCheckSum[CharNum], CharSkillInfoData[CharNum]);
		return FALSE;
	}
	return TRUE;
}

int cSKILL::CheckSkillMasteryForm(sSKILL *pSkill, int Index)
{
	if (pSkill)
	{
		for (int j = 1; j < SIN_MAX_USE_SKILL; j++)
		{
			if (sinSkill.UseSkill[j].Flag)
			{
				if (pSkill->CODE == sinSkill.UseSkill[j].CODE)
				{
					Index = j;
					break;
				}
			}
		}
	}


	int CheckMasteryDataSum = lpCurPlayer->iID + sinSkill.UseSkill[Index].CODE;

	CheckMasteryDataSum += (sinSkill.UseSkill[Index].GageLength*Index);
	CheckMasteryDataSum += (sinSkill.UseSkill[Index].GageLength2*Index);
	CheckMasteryDataSum += (sinSkill.UseSkill[Index].Mastery*Index);

	if (CheckMasteryData[Index] != CheckMasteryDataSum)
	{
		SendSetHackUser3(52, CheckMasteryData[Index], CheckMasteryDataSum);
		return FALSE;
	}

	return TRUE;
}
int cSKILL::ReformSkillMasteryForm(sSKILL *pSkill, int Index)
{

	if (pSkill)
	{
		for (int j = 1; j < SIN_MAX_USE_SKILL; j++)
		{
			if (sinSkill.UseSkill[j].Flag)
			{
				if (pSkill->CODE == sinSkill.UseSkill[j].CODE)
				{
					Index = j;
				}
			}
		}
	}

	CheckMasteryData[Index] = lpCurPlayer->iID + sinSkill.UseSkill[Index].CODE;
	CheckMasteryData[Index] += (sinSkill.UseSkill[Index].GageLength*Index);
	CheckMasteryData[Index] += (sinSkill.UseSkill[Index].GageLength2*Index);
	CheckMasteryData[Index] += (sinSkill.UseSkill[Index].Mastery*Index);

	return TRUE;
}

int cSKILL::CheckSkillPointForm(sSKILL *pSkill)
{
	DWORD	dwXorKey = lpCurPlayer->iID & 0x5F;

	for (int j = 1; j < SIN_MAX_USE_SKILL; j++)
	{
		if (sinSkill.UseSkill[j].Flag &&sinSkill.UseSkill[j].Use &&sinSkill.UseSkill[j].Point)
		{
			if (pSkill->CODE == sinSkill.UseSkill[j].CODE)
			{
				if (CheckSkillPointData[j] != (sinSkill.UseSkill[j].Point^dwXorKey))
				{
					SendSetHackUser3(54, CheckSkillPointData[j], sinSkill.UseSkill[j].Point);
					return FALSE;
				}
			}
		}
	}

	return TRUE;
}

int cSKILL::ReformSkillPointForm(sSKILL *pSkill)
{
	DWORD	dwXorKey = lpCurPlayer->iID & 0x5F;

	for (int j = 1; j < SIN_MAX_USE_SKILL; j++)
	{
		if (sinSkill.UseSkill[j].Flag)
		{
			if (pSkill->CODE == sinSkill.UseSkill[j].CODE)
			{
				CheckSkillPointData[j] = (sinSkill.UseSkill[j].Point^dwXorKey);
				break;
			}
		}
	}
	return TRUE;
}

int cSKILL::InitReformSkillPointForm()
{
	return TRUE;
}

// 获得技能点
int cSKILL::GetSkillPoint(DWORD CODE)
{
	for (int j = 1; j < SIN_MAX_USE_SKILL; j++)
	{
		if (sinSkill.UseSkill[j].Flag)
		{
			if (CODE == sinSkill.UseSkill[j].CODE)
				return sinSkill.UseSkill[j].Point;
		}
	}

	return 0;
}
int cSKILL::SearchContiueSkill(DWORD CODE)
{
	for (int k = 0; k < SIN_MAX_SKILL_LIST; k++)
	{
		if (ContinueSkill[k].Flag)
		{
			if (ContinueSkill[k].CODE == CODE)
				return ContinueSkill[k].Point;
		}
	}
	return 0;
}
int cSKILL::SearchContiueSkillIndex(DWORD CODE)
{
	for (int k = 0; k < SIN_MAX_SKILL_LIST; k++)
	{
		if (ContinueSkill[k].Flag)
		{
			if (ContinueSkill[k].CODE == CODE)
				return k + 1;
		}
	}
	return 0;
}
int cSKILL::SearchContiueSkillCODE(DWORD CODE)
{
	for (int k = 0; k < SIN_MAX_SKILL_LIST; k++)
	{
		if (ContinueSkill[k].Flag)
		{
			if (ContinueSkill[k].CODE == CODE)
				return ContinueSkill[k].CODE;
		}
	}
	return 0;
}

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

int cSKILL::SetVirtualLife(int Time, int Point)
{
	for (int i = 0; i < SIN_MAX_SKILL_LIST; i++)
	{
		if (ContinueSkill[i].Flag)
		{
			if (ContinueSkill[i].CODE == SKILL_VIRTUAL_LIFE)
			{
				return FALSE;
			}
		}
	}

	for (int i = 0; i < SIN_MAX_SKILL_LIST; i++)
	{
		if (!ContinueSkill[i].Flag)
		{
			ContinueSkill[i].Flag = 1;
			ContinueSkill[i].CODE = SKILL_VIRTUAL_LIFE;
			ContinueSkill[i].UseTime = Time;
			ContinueSkill[i].Point = Point;
			ContinueSkill[i].PlayTime = ContinueSkill[i].UseTime * 1000 + dwPlayTime;
			SearchSkillDoc(&ContinueSkill[i]);
			break;
		}
	}

	AddVirtualLife[1] = ((int)sinChar->sHP.sMax * Virtual_Life_Percent[Point - 1]) / 100;
	sinVirtualLifeTime = Time;
	sinVirtualLifePercent = Virtual_Life_Percent[Point - 1];
	CheckVirtualLifeTime = 0;
	cInvenTory.SetItemToChar();
	return TRUE;
}
int cSKILL::SetH_Benedic(int Time, int Point)
{
	for (int i = 0; i < SIN_MAX_SKILL_LIST; i++)
	{
		if (ContinueSkill[i].Flag)
		{
			if (ContinueSkill[i].CODE == SKILL_H_BENEDIC)
				return FALSE;
		}
	}
	for (int i = 0; i < SIN_MAX_SKILL_LIST; i++)
	{
		if (!ContinueSkill[i].Flag)
		{
			ContinueSkill[i].Flag = 1;
			ContinueSkill[i].CODE = SKILL_H_BENEDIC;
			ContinueSkill[i].UseTime = Time;
			ContinueSkill[i].Point = Point;
			ContinueSkill[i].PlayTime = ContinueSkill[i].UseTime * 1000 + dwPlayTime;
			SearchSkillDoc(&ContinueSkill[i]);
			break;
		}
	}
	return TRUE;
}

// 冠犁盔 - 何胶磐 酒捞袍
int cSKILL::UseBoosterItem(ItemData *pItem)
{
	if (lpCurPlayer->iLoadedMapIndex >= 0 && STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapType == MAPTYPE_Town)
		return FALSE; //付阑俊辑绰 给荤侩茄促

	DWORD BoosterCODE;
	DWORD ItemMask;
	int BoosterTime = 0;
	int cnt = 0;

	ItemMask = pItem->sBaseItemID.ToInt() & sinITEM_MASK3;
	if (ItemMask == sin21 || ItemMask == sin24 || ItemMask == sin27) cnt = 0;
	if (ItemMask == sin22 || ItemMask == sin25 || ItemMask == sin28) cnt = 1;
	if (ItemMask == sin23 || ItemMask == sin26 || ItemMask == sin29) cnt = 2;

	switch (ItemMask) {
	case sin21: // 积疙仿 - 1矫埃
	case sin22: // 积疙仿 - 3矫埃
	case sin23: // 积疙仿 - 1老
		BoosterCODE = BOOSTER_ITEM_LIFE;
		BoosterTime = BoosterItem_UseTime[cnt];

		AddBoosterLife = ((int)sinChar->sHP.sMax * BoosterItem_DataPercent[0]) / 100;
		BoosterLifeTime = BoosterTime;
		BoosterLifePercent = BoosterItem_DataPercent[0];
		CheckBoosterLifeTime = 0; //眉农矫埃檬扁拳
		break;
	case sin24: // 扁仿 - 1矫埃
	case sin25: // 扁仿 - 3矫埃
	case sin26: // 扁仿 - 1老
		BoosterCODE = BOOSTER_ITEM_MANA;
		BoosterTime = BoosterItem_UseTime[cnt];

		// 冠犁盔 - 何胶磐 酒捞袍(扁仿)
		AddVirtualMana[1] = ((int)sinChar->sMP.sMax * BoosterItem_DataPercent[1]) / 100;
		sinVirtualManaTime = BoosterTime;
		sinVirtualManaPercent = BoosterItem_DataPercent[1];
		CheckVirtualManaTime = 0; //眉农矫埃檬扁拳
		break;
	case sin27: // 辟仿 - 1矫埃
	case sin28: // 辟仿 - 3矫埃
	case sin29: // 辟仿 - 1老
		BoosterCODE = BOOSTER_ITEM_STAMINA;
		BoosterTime = BoosterItem_UseTime[cnt];

		// 冠犁盔 - 何胶磐 酒捞袍(辟仿)
		AddVirtualStamina[1] = ((int)sinChar->sSP.sMax * BoosterItem_DataPercent[2]) / 100;
		sinVirtualStaminaTime = BoosterTime;
		sinVirtualStaminaPercent = BoosterItem_DataPercent[2];
		CheckVirtualStaminaTime = 0; //眉农矫埃檬扁拳
		break;
	}
	sSKILL TempSkill;

	if (cSkill.SearchContiueSkillCODE(BoosterCODE) == BoosterCODE && BoosterCODE != 0)
	{
		cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
		haCastleSkillUseFlag = 0;
		return TRUE;
	}
	haCastleSkillUseFlag = 1;

	for (int j = 0; j < SIN_MAX_SKILL; j++)
	{
		if (sSkill[j].CODE == BoosterCODE)
		{
			memcpy(&TempSkill, &sSkill[j], sizeof(sSKILL));
			TempSkill.UseTime = BoosterTime;
			sinContinueSkillSet(&TempSkill);
			SwitchSkill(&TempSkill);
			break;
		}
	}

	tempLife[1] = sinChar->iLevel;
	tempMana[1] = sinChar->iLevel;
	tempStamina[1] = sinChar->iLevel;

	sinPlaySound(SIN_SOUND_EAT_POTION2);//措冠 荤款靛
	cInvenTory.SetItemToChar();
	return TRUE;
}

// 冠犁盔 - 单固瘤 何胶磐甫 悸泼茄促
int cSKILL::SetBoosterItem(DWORD ItemCODE, int Time)
{
	int UseFlag = 0;
	sSKILL TempSkill;
	memset(&TempSkill, 0, sizeof(sSKILL));
	char *Path;

	DWORD ItemMask;
	int cnt = 0;

	ItemMask = ItemCODE & sinITEM_MASK3;

	if (ItemMask == sin21 || ItemMask == sin24 || ItemMask == sin27) cnt = 0; // 1矫埃
	if (ItemMask == sin22 || ItemMask == sin25 || ItemMask == sin28) cnt = 1; // 3矫埃
	if (ItemMask == sin23 || ItemMask == sin26 || ItemMask == sin29) cnt = 2; // 1老

	switch (ItemMask)
	{
		// 积疙仿 何胶磐
	case sin21:
	case sin22:
	case sin23:
		UseFlag = 0;
		Path = "image\\Sinimage\\skill\\keep\\Booster_01.tga";
		TempSkill.CODE = BOOSTER_ITEM_LIFE;
		TempSkill.Point = 0; // 何胶磐 酒捞袍篮 饭骇捞 绝促.
		TempSkill.UseTime = BoosterItem_UseTime[cnt];
		TempSkill.CheckTime = (BoosterItem_UseTime[cnt] * 70) - (Time * 70);
		TempSkill.MatIcon = Mat_BoosterItem[UseFlag];
		break;

		// 扁仿 何胶磐
	case sin24:
	case sin25:
	case sin26:
		UseFlag = 1;
		Path = "image\\Sinimage\\skill\\keep\\Booster_02.tga";
		TempSkill.CODE = BOOSTER_ITEM_MANA;
		TempSkill.Point = 0; // 何胶磐 酒捞袍篮 饭骇捞 绝促.
		TempSkill.UseTime = BoosterItem_UseTime[cnt];
		TempSkill.CheckTime = (BoosterItem_UseTime[cnt] * 70) - (Time * 70);
		TempSkill.MatIcon = Mat_BoosterItem[UseFlag];
		break;

		// 辟仿 何胶磐
	case sin27:
	case sin28:
	case sin29:
		UseFlag = 2;
		Path = "image\\Sinimage\\skill\\keep\\Booster_03.tga";
		TempSkill.CODE = BOOSTER_ITEM_STAMINA;
		TempSkill.Point = 0; // 何胶磐 酒捞袍篮 饭骇捞 绝促.
		TempSkill.UseTime = BoosterItem_UseTime[cnt];
		TempSkill.CheckTime = (BoosterItem_UseTime[cnt] * 70) - (Time * 70);
		TempSkill.MatIcon = Mat_BoosterItem[UseFlag];
		break;
	}

	char szBuff[128];
	if (!Mat_BoosterItem[UseFlag]) {
		wsprintf(szBuff, Path, UseFlag);
		Mat_BoosterItem[UseFlag] = CreateTextureMaterial(szBuff, 0, 0, 0, SMMAT_BLEND_ALPHA);
		ReadTextures();	//咆胶媚 肺爹
	}

	sinContinueSkillSet(&TempSkill);

	if (UseFlag == 0)
	{
		// 冠犁盔 - 何胶磐 酒捞袍(积疙仿)
		AddBoosterLife = ((int)sinChar->sHP.sMax * BoosterItem_DataPercent[UseFlag]) / 100;
		BoosterLifeTime = Time;
		BoosterLifePercent = BoosterItem_DataPercent[UseFlag];
		CheckBoosterLifeTime = 0; //眉农矫埃檬扁拳
	}
	else if (UseFlag == 1)
	{
		// 冠犁盔 - 何胶磐 酒捞袍(扁仿)
		AddVirtualMana[1] = ((int)sinChar->sMP.sMax * BoosterItem_DataPercent[UseFlag]) / 100;
		sinVirtualManaTime = Time;
		sinVirtualManaPercent = BoosterItem_DataPercent[UseFlag];
		CheckVirtualManaTime = 0; //眉农矫埃檬扁拳
	}
	else if (UseFlag == 2)
	{
		// 冠犁盔 - 何胶磐 酒捞袍(辟仿)
		AddVirtualStamina[1] = ((int)sinChar->sSP.sMax * BoosterItem_DataPercent[UseFlag]) / 100;
		sinVirtualStaminaTime = Time;
		sinVirtualStaminaPercent = BoosterItem_DataPercent[UseFlag];
		CheckVirtualStaminaTime = 0; //眉农矫埃檬扁拳
	}

	cInvenTory.SetItemToChar();

	return TRUE;
}

// 厘喊 - 胶懦 掉饭捞
int cSKILL::SetSkillDelayItem(DWORD ItemCODE, int Time)
{
	int UseFlag = 0;
	sSKILL TempSkill;
	memset(&TempSkill, 0, sizeof(sSKILL));
	char *Path;

	DWORD ItemMask;
	int cnt = 0;

	ItemMask = ItemCODE & sinITEM_MASK3;

	if (ItemMask == sin30 || ItemMask == sin33 || ItemMask == sin36) cnt = 0;
	if (ItemMask == sin31 || ItemMask == sin34 || ItemMask == sin37) cnt = 1;
	if (ItemMask == sin32 || ItemMask == sin35 || ItemMask == sin38) cnt = 2;

	switch (ItemMask)
	{
		// 积疙仿 何胶磐
	case sin30:
	case sin31:
	case sin32:
		UseFlag = 0;
		Path = "image\\Sinimage\\skill\\keep\\Booster_01.tga";
		TempSkill.CODE = SKILLDELAY_ITEM_LIFE;
		TempSkill.Point = 0;
		TempSkill.UseTime = nSkillDelay_UseTime[cnt];
		TempSkill.CheckTime = (nSkillDelay_UseTime[cnt] * 70) - (Time * 70);
		TempSkill.MatIcon = nMat_SkillDelayItem[UseFlag];
		break;
	}


	char szBuff[128];
	if (!nMat_SkillDelayItem[UseFlag]) {
		wsprintf(szBuff, Path, UseFlag);
		nMat_SkillDelayItem[UseFlag] = CreateTextureMaterial(szBuff, 0, 0, 0, SMMAT_BLEND_ALPHA);
		ReadTextures();	//咆胶媚 肺爹
	}

	sinContinueSkillSet(&TempSkill);

	if (UseFlag == 0)
	{
		sinAddSkillDelay = 10;
		sinSkillDelayTime = Time;
		BoosterLifePercent = BoosterItem_DataPercent[UseFlag];
		CheckSkillDelayTime = 0; //眉农矫埃檬扁拳
	}


	cInvenTory.SetItemToChar();

	return TRUE;
}


// 厘喊 - 胶懦 掉饭捞
int cSKILL::UseSkillDelayItem(ItemData *pItem)
{
	DWORD SkillDelayCODE;
	DWORD ItemMask;
	int SkillDelayTime = 0;
	int cnt = 0;

	ItemMask = pItem->sBaseItemID.ToInt() & sinITEM_MASK3;
	if (ItemMask == sin30 || ItemMask == sin33 || ItemMask == sin36) cnt = 0;
	if (ItemMask == sin31 || ItemMask == sin34 || ItemMask == sin37) cnt = 1;
	if (ItemMask == sin32 || ItemMask == sin35 || ItemMask == sin38) cnt = 2;

	switch (ItemMask) {
	case sin30: // 1矫埃
	case sin31: // 3矫埃
	case sin32: // 1老
		SkillDelayCODE = SKILLDELAY_ITEM_LIFE;
		SkillDelayTime = nSkillDelay_UseTime[cnt];

		sinAddSkillDelay = 10;
		sinSkillDelayTime = SkillDelayTime;
		CheckSkillDelayTime = 0; //眉农矫埃檬扁拳
		break;
	}
	//秦寸 蹬绰 酒捞袍捞 嘎栏搁 酒捞袍胶懦阑 技泼茄促.
	sSKILL TempSkill;

	if (cSkill.SearchContiueSkillCODE(SkillDelayCODE) == SkillDelayCODE && SkillDelayCODE != 0) {
		cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
		haCastleSkillUseFlag = 0;
		return TRUE;
	}
	haCastleSkillUseFlag = 1;

	for (int j = 0; j < SIN_MAX_SKILL; j++)
	{
		if (sSkill[j].CODE == SkillDelayCODE)
		{
			memcpy(&TempSkill, &sSkill[j], sizeof(sSKILL));
			TempSkill.UseTime = SkillDelayTime;
			sinContinueSkillSet(&TempSkill);
			SwitchSkill(&TempSkill);
			break;
		}
	}

	sinPlaySound(SIN_SOUND_EAT_POTION2);
	cInvenTory.SetItemToChar();
	return TRUE;
}


int cSKILL::SetT_Of_Valhalla(int Point, int LV)
{
	for (int i = 0; i < SIN_MAX_SKILL_LIST; i++)
	{
		if (ContinueSkill[i].Flag)
		{
			if (ContinueSkill[i].CODE == SKILL_TRIUMPH_OF_VALHALLA || ContinueSkill[i].CODE == SKILL_HALL_OF_VALHALLA)
				return FALSE;
		}
	}

	for (int i = 0; i < SIN_MAX_SKILL_LIST; i++)
	{
		if (!ContinueSkill[i].Flag)
		{
			ContinueSkill[i].Flag = 1;
			ContinueSkill[i].CODE = SKILL_TRIUMPH_OF_VALHALLA;
			ContinueSkill[i].UseTime = T_Of_Valhalla_Time[Point - 1];
			ContinueSkill[i].Point = Point;
			SearchSkillDoc(&ContinueSkill[i]);
			break;
		}
	}

	SetT_Of_ValhallaLV = LV;

	if (SetT_Of_ValhallaFlag2)
	{
		SetT_Of_ValhallaFlag2 = 0;
		SetT_Of_ValhallaFlag = 0;
	}
	else
		SetT_Of_ValhallaFlag = 1;

	cInvenTory.SetItemToChar();
	return TRUE;
}
int cSKILL::SetEnchant_Weapon(int Time, int Point)
{
	for (int i = 0; i < SIN_MAX_SKILL_LIST; i++)
	{
		if (ContinueSkill[i].Flag)
		{
			if (ContinueSkill[i].CODE == SKILL_ENCHANT_WEAPON)
			{
				return FALSE;
			}
		}
	}

	for (int i = 0; i < SIN_MAX_SKILL_LIST; i++)
	{
		if (!ContinueSkill[i].Flag)
		{
			ContinueSkill[i].Flag = 1;
			ContinueSkill[i].CODE = SKILL_ENCHANT_WEAPON;
			ContinueSkill[i].UseTime = Time;
			ContinueSkill[i].Point = Point;
			SearchSkillDoc(&ContinueSkill[i]);
			break;
		}
	}
	cInvenTory.SetItemToChar();
	return TRUE;
}
int cSKILL::ForeceOfNature(int Time, int Point, int Party)
{
	for (int i = 0; i < SIN_MAX_SKILL_LIST; i++)
	{
		if (ContinueSkill[i].Flag)
		{
			if (ContinueSkill[i].CODE == SKILL_FORCE_OF_NATURE)
			{
				if (ContinueSkill[i].Flag == 2 && !Party)
				{
					ZeroMemory(&ContinueSkill[i], sizeof(sSKILL));
					break;
				}
				else
					return FALSE;
			}
		}
	}

	for (int i = 0; i < SIN_MAX_SKILL_LIST; i++)
	{
		if (!ContinueSkill[i].Flag)
		{
			ContinueSkill[i].Flag = Party + 1;
			ContinueSkill[i].CODE = SKILL_FORCE_OF_NATURE;
			ContinueSkill[i].UseTime = Time;
			ContinueSkill[i].Point = Point;
			SearchSkillDoc(&ContinueSkill[i]);
			break;
		}
	}
	cInvenTory.SetItemToChar();
	return TRUE;
}
int cSKILL::HellOfValhalla(int Time, int Point, int TVPoint, int LV, int Party)
{
	for (int i = 0; i < SIN_MAX_SKILL_LIST; i++)
	{
		if (ContinueSkill[i].Flag)
		{
			if (ContinueSkill[i].CODE == SKILL_HALL_OF_VALHALLA)
			{
				if (ContinueSkill[i].Flag == 2 && !Party)
				{
					memset(&ContinueSkill[i], 0, sizeof(sSKILL));
					break;
				}
				else return FALSE;
			}
		}
	}

	for (int i = 0; i < SIN_MAX_SKILL_LIST; i++)
	{
		if (!ContinueSkill[i].Flag)
		{
			ContinueSkill[i].Flag = Party + 1;
			ContinueSkill[i].CODE = SKILL_HALL_OF_VALHALLA;
			ContinueSkill[i].UseTime = Time;
			ContinueSkill[i].Point = Point;
			SearchSkillDoc(&ContinueSkill[i]);
			break;
		}
	}
	SetT_Of_ValhallaPOINT = TVPoint;
	SetH_Of_ValhallaLV = LV;
	cInvenTory.SetItemToChar();
	return TRUE;
}
int cSKILL::Regeneration_Field(int Time, int Point, int Party)
{
	for (int i = 0; i < SIN_MAX_SKILL_LIST; i++)
	{
		if (ContinueSkill[i].Flag)
		{
			if (ContinueSkill[i].CODE == SKILL_REGENERATION_FIELD)
			{
				if (ContinueSkill[i].UseTime > Time)return FALSE;
				ContinueSkill[i].UseTime = Time;
				return TRUE;
			}
		}
	}

	for (int i = 0; i < SIN_MAX_SKILL_LIST; i++)
	{
		if (!ContinueSkill[i].Flag)
		{
			ContinueSkill[i].Flag = 1 + Party;
			ContinueSkill[i].CODE = SKILL_REGENERATION_FIELD;
			ContinueSkill[i].UseTime = Time;
			ContinueSkill[i].Point = Point;
			SearchSkillDoc(&ContinueSkill[i]);
			break;
		}
	}
	cInvenTory.SetItemToChar();
	return TRUE;
}
int cSKILL::SearchSkillDoc(sSKILL *pSkill)
{
	for (int i = 0; i < SIN_MAX_SKILL; i++)
	{
		if (pSkill->CODE == sSkill_Info[i].CODE)
		{
			switch (pSkill->CODE)
			{
			case SKILL_FORCE_ORB:
				wsprintf(pSkill->Skill_Info.SkillName, "%s %s", SheltomName2[pSkill->Point - 1], sSkill_Info[i].SkillName);
				lstrcpy(pSkill->Skill_Info.SkillDoc, sSkill_Info[i].SkillDoc);
				break;
			case SKILL_CRYSTAL_ORB:
				wsprintf(pSkill->Skill_Info.SkillName, "%s %s", CrystalName2[pSkill->Point - 1], sSkill_Info[i].SkillName);
				lstrcpy(pSkill->Skill_Info.SkillDoc, sSkill_Info[i].SkillDoc);
				break;
			case CHANGE_ELEMENTARY_QUEST:
				if (chaQuest.szQuestMonsterName[0] == '\0')
				{
#ifdef ENGLISH_LANGUAGE
					lstrcpy(pSkill->Skill_Info.SkillName, "Quest");
					lstrcpy(pSkill->Skill_Info.SkillDoc, "Deliver the Cake!");
#else
					lstrcpy(pSkill->Skill_Info.SkillDoc, "任务");
					lstrcpy(pSkill->Skill_Info.SkillDoc, "去蛋糕!");
#endif
				}
				else
				{
					lstrcpy(pSkill->Skill_Info.SkillName, sSkill_Info[i].SkillName);
					lstrcpy(pSkill->Skill_Info.SkillDoc, sSkill_Info[i].SkillDoc);
				}

				//lstrcpy(pSkill->Skill_Info.SkillName,sSkill_Info[i].SkillName);
				//lstrcpy(pSkill->Skill_Info.SkillDoc,sSkill_Info[i].SkillDoc);
				break;
			default:
				lstrcpy(pSkill->Skill_Info.SkillName, sSkill_Info[i].SkillName);
				lstrcpy(pSkill->Skill_Info.SkillDoc, sSkill_Info[i].SkillDoc);
				break;
			}
			break;
		}
	}
	return TRUE;
}
int cSKILL::SkillBarDraw(sSKILL *pSkill, int x, int y, int Alpha)
{
	D3DTLVERTEX9 tlVertex[73];

	int Time = 0;

	Time = (int)(((float)pSkill->CheckTime / ((float)pSkill->UseTime*70.0f))*72.0f);

	if (Time < 0)
		Time = 0;

	if (Time > 72)
		Time = 72;

	float fx, fy = 0;

	int i = 0, j = 0;
	int sinY, cosY;
	tlVertex[0].rhw = 1;
	tlVertex[0].color = D3DCOLOR_RGBA(0, Alpha, Alpha, Alpha);
	tlVertex[0].specular = D3DCOLOR_RGBA(0, 0, 0, 0);
	tlVertex[0].sz = 0;

	tlVertex[0].sx = float(x);
	tlVertex[0].sy = float(y);
	tlVertex[0].tu = 0.5;
	tlVertex[0].tv = 0.5f;

	for (i = 1; i < Time + 1; i++)
	{
		tlVertex[i].rhw = 1;
		if (pSkill->CODE == SKILL_FORCE_ORB)
			tlVertex[i].color = D3DCOLOR_RGBA(255, 190, 30, Alpha);
		else
			tlVertex[i].color = D3DCOLOR_RGBA(0, 255, 200, Alpha);

		tlVertex[i].specular = D3DCOLOR_RGBA(0, 0, 0, 0);
		tlVertex[i].sz = 0;

		sinY = GetSin[(1024 / 2) + (i * 56)&ANGCLIP];
		cosY = GetCos[(1024 / 2) + ((i * 56) + ANGLE_180)&ANGCLIP];

		fx = (float)((10 * sinY + 10 * cosY) >> 8);
		fy = (float)((10 * cosY - 10 * sinY) >> 8);
		fx /= 256;
		fy /= 256;

		tlVertex[i].sx = (float)(fx + x);
		tlVertex[i].sy = (float)(fy + y);
		tlVertex[i].tu = 0.5f;
		tlVertex[i].tv = 0.5f;

	}
	if (i > 3)
	{
		GRAPHICENGINE->GetDevice()->SetTexture(0, 0);
		GRAPHICENGINE->GetDevice()->SetFVF(D3DFVF_TLVERTEX);
		GRAPHICENGINE->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, i - 3, tlVertex, sizeof(D3DTLVERTEX9));
	}

	return TRUE;
}

int cSKILL::CheckContinueIcon()
{
	for (int i = 0; i < SIN_MAX_SKILL_LIST; i++)
	{
		if (ContinueSkill[i].Flag)
		{
			if (!ContinueSkill[i].MatIcon)
			{
				for (int j = 0; j < SIN_MAX_SKILL; j++)
				{
					if (ContinueSkill[i].CODE == sSkill[j].CODE)
					{
						if (sSkill[j].MatIcon)
						{
							ContinueSkill[i].MatIcon = sSkill[j].MatIcon;
							return TRUE;
						}
					}
				}
			}
		}
	}
	return FALSE;
}
int cSKILL::CancelContinueSkill(DWORD CODE)
{
	for (int i = 0; i < SIN_MAX_SKILL_LIST; i++)
	{
		if (ContinueSkill[i].Flag)
		{
			if (ContinueSkill[i].CODE == CODE)
			{
				memset(&ContinueSkill[i], 0, sizeof(sSKILL));
				cInvenTory.SetItemToChar();
				break;
			}
		}
	}
	return FALSE;
}
int cSKILL::CancelContinueSkill(DWORD CODE, int dwObjectSerial)
{
	for (int i = 0; i < SIN_MAX_SKILL_LIST; i++)
	{
		if (ContinueSkill[i].Flag)
		{
			if (ContinueSkill[i].CODE == CODE && ContinueSkill[i].dwObjectSerial == dwObjectSerial)
			{
				memset(&ContinueSkill[i], 0, sizeof(sSKILL));
				cInvenTory.SetItemToChar();
				break;
			}
		}
	}
	return FALSE;
}
int cSKILL::SkillShortKeyInit()
{
	for (int j = 1; j < SIN_MAX_USE_SKILL; j++)
	{
		sinSkill.UseSkill[j].ShortKey = 0;
	}
	return TRUE;
}
int cSKILL::CheckMaturedSkill(int ChangeJob)
{
	int matured_skill_count = 0;

	switch (ChangeJob)
	{
	case 1:
		for (int j = 1; j < 5; j++)
		{
			if (sinSkill.UseSkill[j].UseSkillCount < 10000 && sinSkill.UseSkill[j].Skill_Info.USECODE != SIN_SKILL_USE_NOT && sinSkill.UseSkill[j].UseSkillMastery)
				matured_skill_count++;
		}
		break;
	case 2:
		for (int j = 5; j < 9; j++)
		{
			if (sinSkill.UseSkill[j].UseSkillCount < 10000 && sinSkill.UseSkill[j].Skill_Info.USECODE != SIN_SKILL_USE_NOT && sinSkill.UseSkill[j].UseSkillMastery)
				matured_skill_count++;
		}
		break;
	case 3:
		for (int j = 9; j < 13; j++)
		{
			if (sinSkill.UseSkill[j].UseSkillCount < 10000 && sinSkill.UseSkill[j].Skill_Info.USECODE != SIN_SKILL_USE_NOT && sinSkill.UseSkill[j].UseSkillMastery)
				matured_skill_count++;
		}
		break;
	}

	if (matured_skill_count <= 4 && matured_skill_count > 0)
		return TRUE;
	return FALSE;
}
