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
	{"��ͨ���� "		,SKILL_NORMAL_ATTACK			,"Skill_Normal"		,						},

	//////////////��е����
{"���⻤��"			,SKILL_EXTREME_SHIELD			,"TM10 Ex_shield"	,"Mc1_E_SHIELD.tga"		},
{"��е��"			,SKILL_MECHANIC_BOMB			,"TM12 M_bomb"								},
{"��֮����"			,SKILL_POISON_ATTRIBUTE			,"TM14 P_attribute"							},
{"��⻤��"			,SKILL_PHYSICAL_ABSORB			,"TM17 Ph_absorb"	,"Mc1_P_ABSORB.tga"		},

{"����޻�"			,SKILL_GREAT_SMASH				,"TM20 G_Smash"								},
{"����ר�� "		,SKILL_MAXIMIZE					,"TM23 Maximize"	,"Mc2_MAXIMIZE.tga"		},
{"������"			,SKILL_AUTOMATION				,"TM26 Automation"	,"Mc2_AUTOMATION.tga"	},
{"�𻨵糡"			,SKILL_SPARK					,"TM30 Spark"},

{"�����ؼ�"			,SKILL_METAL_ARMOR				,"TM40 M_Armor"		,"Mc3_M_ARMOR.tga"		},
{"�ǹ����"			,SKILL_GRAND_SMASH				,"TM43 Grand_Smash"							},
{"�Ż�ר��"			,SKILL_MECHANIC_WEAPON			,"TM44 M_Weapon"							},
{"�����粨"			,SKILL_SPARK_SHIELD				,"TM50 S_Shield"	,"Mc3_S_SHIELD.tga"		},

{"�������"			,SKILL_IMPULSION				,"TM60 Impulsion"							},
{"����ŭ��"			,SKILL_COMPULSION				,"TM63 Compulsion"	,"Mc4_COMPULSION.tga"	},
{"��������"			,SKILL_MAGNETIC_SPHERE			,"TM66 M_Sphere"	,"Mc4_M_SPHERE.tga"		},
{"�ռ���е"			,SKILL_METAL_GOLEM				,"TM70 M_Golem"		,"Mc4_M_GOLEM.tga"		},

{"��������"			,SKILL_LANDMINNING				,"TM80 landminning"							},
{"���ٴ��"			,SKILL_H_SONIC					,"TM83 H_Sonic"		,"Me5_H_Sonic.tga"		},
{"����֮��"			,SKILL_R_SMASH					,"TM86 R_Smash"								},
{"ս��ף��"			,SKILL_P_ENHENCE				,"TM90 P_Enhence"	,"Me5_P_Enhence.tga"	},

////////////// ��ʿ����
{"��֮��"			,SKILL_MELEE_MASTERY			,"TF10 M_mastery"							},
{"��֮����"			,SKILL_FIRE_ATTRIBUTE			,"TF12 F_attribute"							},
{"���ر���"			,SKILL_RAVING					,"TF14 raving"								},
{"��׼֮��"			,SKILL_IMPACT					,"TF17 impact"								},

{"�������"			,SKILL_TRIPLE_IMPACT			,"TF20 T_Impact"							},
{"��������"			,SKILL_BRUTAL_SWING				,"TF23 B_Swing"								},
{"����ŭ��"			,SKILL_ROAR						,"TF26 Roar"								},
{"ս��֮ŭ"			,SKILL_RAGE_OF_ZECRAM			,"TF30 R_Zecram"							},

{"����һ��"			,SKILL_CONCENTRATION			,"TF40 Concentration","Ft3_CONCENTRATION.tga"},
{"��������"			,SKILL_AVANGING_CRASH			,"TF43 A_Crash"								},
{"��ɱ֮��"			,SKILL_SWIFT_AXE				,"TF46 S_Axe"		,"Ft3_S_AXE.tga"		},
{"������"			,SKILL_BONE_CRASH				,"TF50 B_Crash"								},

{"�ƻ�֮��"			,SKILL_DETORYER					,"TF60 Destoryer"							},
{"���ŭ��"		    ,SKILL_BERSERKER				,"TF63 Berserker"	,"Ft4_BERSERKER.tga"	},
{"쫷�Ϯ��"			,SKILL_CYCLONE_STRIKE			,"TF66 C_Strike"							},
{"����ר��"			,SKILL_BOOST_HEALTH				,"TF70 B_Health"							},

{"��ŭն"			,SKILL_D_HIT					,"TF80 D_Hit"								},
{"��Ұ���"		    ,SKILL_P_DASH					,"TF83 P_Dash"								},
{"����ն��"			,SKILL_M_BLOW					,"TF86 M_Blow"								},
{"����֮ŭ"			,SKILL_B_BERSERKER				,"TF90 B_Berserker"	,"Ft5_B_Berserker.tga"	},

////////////// ǹ������
{"����ǹ��"   		,SKILL_PIKE_WIND				,"TP10 P_wind"								},
{"��֮����"			,SKILL_ICE_ATTRIBUTE			,"TP12 I_attribute"							},
{"�������"			,SKILL_CRITICAL_HIT				,"TP14 Cri_hit"								},
{"����һ��"			,SKILL_JUMPING_CRASH			,"TP17 J_Crash"								},

{"���֮ǹ"			,SKILL_GROUND_PIKE				,"TP20 G_Pike"								},
{"ǹ֮쫷�"			,SKILL_TORNADO					,"TP23 Tornado"								},
{"���ר��"			,SKILL_WEAPONE_DEFENCE_MASTERY	,"TP26 W_D_Mastery"							},
{"������ǹ" 		,SKILL_EXPANSION				,"TP30 Expasion"							},

{"���߱�ǹ"			,SKILL_VENOM_SPEAR				,"TP40 V_Spear"								},
{"����֮��"			,SKILL_VANISH					,"TP43 Vanish"		,"Pk3_VANISH.tga"		},
{"����֮ǹ"			,SKILL_CRITICAL_MASTERY			,"TP46 C_Mastery"							},
{"����֮ǹ" 		,SKILL_CHAIN_LANCE				,"TP50 C_Lance"								},

{"��ɱ֮��"			,SKILL_ASSASSIN_EYE				,"TP60 A_Eye"		,"Pk4_A_EYE.tga"		},
{"ת�����"			,SKILL_CHARGING_STRIKE			,"TP63 C_Strike"							},
{"Ӱ��֮��"         ,SKILL_VAGUE					,"TP66 Vague"		,"Pk4_VAGUE.tga"		},
{"�����Ӱ"			,SKILL_SHADOW_MASTER			,"TP70 S_Master"							},

{"�������"			,SKILL_D_REAPER					,"TP80 D_Reaper"							},
{"��ǹ��Ϯ"			,SKILL_F_SPEAR					,"TP83 F_Spear"								},
{"Ǳ�ܼ���"         ,SKILL_AMPLIFIED				,"TP86 Amplified"	,"Pk5_Amplified.tga"	},
{"����֮ǹ"			,SKILL_SS_ATTACK				,"TP90 SS_Attack"							},

////////////// ���� ����
{"���֮ӥ"			,SKILL_SCOUT_HAWK				,"TA10 S_hawk"		,"Ac1_S_HAWK.tga"		},
{"ǿ��֮��"			,SKILL_SHOOTING_MASTERY			,"TA12 S_mastery"							},
{"����֮��"			,SKILL_WIND_ARROW				,"TA14 W_arrow"								},
{"����֮��"			,SKILL_PERFECT_AIM				,"TA17 P_aim"								},

{"����֮��"			,SKILL_DIONS_EYE				,"TA20 D_Eye"								},
{"���֮ӥ"			,SKILL_FALCON					,"TA23 Falcon"		,"Ac2_FALCON.tga"		},
{"�񱩻��"			,SKILL_ARROW_OF_RAGE			,"TA26 A_Rage"								},
{"ѩ��֮��"			,SKILL_AVALANCHE				,"TA30 Avalanchie"							},

{"Ԫ�ع���"			,SKILL_ELEMENTAL_SHOT			,"TA40 E_Shot"								},
{"�ƽ���ӥ"			,SKILL_GOLDEN_FALCON			,"TA43 G_Falcon"	,"Ac3_G_FALCON.tga"		},
{"����֮��"			,SKILL_BOMB_SHOT				,"TA46 B_Shot"								},
{"�ߴ�֮��"			,SKILL_PERFORATION				,"TA50 Perforation"							},

{"�ٻ�ѩ��"			,SKILL_RECALL_WOLVERIN			,"TA60 R_Wolverin"	,"Ac4_R_WOLVERIN.tga"	},
{"��ܴ�ʦ"			,SKILL_EVASION_MASTERY			,"TA63 E_Mastery"							},
{"系˾���"         ,SKILL_PHOENIX_SHOT				,"TA66 P_Shot"								},
{"��Ȼ֮��"			,SKILL_FORCE_OF_NATURE			,"TA70 F_O_Nature"	,"Ac4_F_O_NATURE.tga"	},

{"����֮��"			,SKILL_E_SHOT					,"TA80 E_Shot"								},
{"����֮��"			,SKILL_S_ROPE					,"TA83 S_Rope"								},
{"쫷�֮��"         ,SKILL_N_SPLASH					,"TA86 N_Splash"							},
{"�������"			,SKILL_C_TRAP					,"TA90 C_Trap"								},

///////////////// ��������
{"ħ��"			,SKILL_SWORD_BLAST				,"MN10 S_Blast"								},
{"ʥ�⻤��"			,SKILL_HOLY_BODY				,"MN12 H_Body"		,"Kt1_H_BODY.tga"		},
{"������ѵ"			,SKILL_PHYSICAL_TRANING			,"MN14 P_Traning"							},
{"˫�ر���"		 	,SKILL_DOUBLE_CRASH				,"MN17 D_Crash"								},

{"�����ػ�"			,SKILL_HOLY_VALOR				,"MN20 H_Valor"		,"Kt2_H_VALOR.tga"		},
{"�������"	        ,SKILL_BRANDISH					,"MN23 Brandish"							},
{"һ����"	        ,SKILL_PIERCING					,"MN26 Piercing"							},
{"��������"			,SKILL_DRASTIC_SPIRIT			,"MN30 D_Spirit"	,"Kt2_D_SPIRIT.tga"		},

{"����֮��"			,SKILL_SWORD_MASTERY			,"MN40 S_Mastery"							},
{"ʥ��֮��"			,SKILL_DIVINE_INHALATION		,"MN43 D_Inhalation","Kt3_D_INHALATION.tga"	},
{"ʥ��֮��"			,SKILL_HOLY_INCANTATION			,"MN46 H_Incantation"						},
{"ʥ��ʮ��"			,SKILL_GRAND_CROSS				,"MN50 G_Cross"								},

{"��ħ��"			,SKILL_SWORD_OF_JUSTICE			,"MN60 S_O_Justice"							},
{"����֮��"			,SKILL_GODLY_SHIELD				,"MN63 G_Shield"	,"Kt4_G_SHIELD.tga"		},
{"�ϵ�ף��"			,SKILL_GOD_BLESS				,"MN66 G_Bless"		,"Kt4_G_BLESS.tga"		},
{"ɲ�����"			,SKILL_DIVINE_PIERCING			,"MN70 D_Piercing"							},

{"�������"			,SKILL_S_BREAKER				,"MN80 S_Breaker"							},
{"�����ػ�"			,SKILL_C_MOON					,"MN83 C_Moon"								},
{"�ϵ��ػ�"			,SKILL_S_BLADE					,"MN86 S_Blade"								},
{"��������"			,SKILL_H_BENEDIC				,"MN90 H_Benedic"	,"Kn5_H_Benedic.tga"	},

///////////////// ħǹ�ּ���
{"����ɯ��"			,SKILL_SHIELD_STRIKE			,"MA10 S_Strike"							},
{"��ɳ��Ӱ "		,SKILL_FARINA					,"MA12 Farina"								},
{"ħ����ǹ"			,SKILL_THROWING_MASTERY			,"MA14 T_Mastery"							},
{"����֮ǹ"			,SKILL_VIGOR_SPEAR				,"MA17 V_Spear"								},

{"׷������"			,SKILL_WINDY					,"MA20 Windy"		,"At2_WINDY.tga"		},
{"�����ɱ�"			,SKILL_TWIST_JAVELIN			,"MA23 T_Javelin"							},
{"�������"			,SKILL_SOUL_SUCKER				,"MA26 S_Sucker"							},
{"������ǹ"			,SKILL_FIRE_JAVELIN				,"MA30 F_Javelin"							},

{"׷��֮ǹ"			,SKILL_SPLIT_JAVELIN			,"MA40 Split_Javelin"						},
{"ս������"			,SKILL_TRIUMPH_OF_VALHALLA		,"MA43 T_Of_Valhalla","At3_T_O_VALHALLA.tga"},
{"����֮ǹ"			,SKILL_LIGHTNING_JAVELIN		,"MA46 L_Javelin"							},
{"������"			,SKILL_STORM_JAVELIN			,"MA50 Storm_Javelin"						},

{"�߶�����֮��"		,SKILL_HALL_OF_VALHALLA			,"MA60 H_O_Valhalla","At4_H_O_VALHALLA.tga"	},
{"ʮ��ŭ��"			,SKILL_X_RAGE					,"MA63 X_Rage"								},
{"˪����ǹ"			,SKILL_FROST_JAVELIN			,"MA66 F_Javelin"	,"At4_F_JAVELIN.tga"	},
{"��籬��"			,SKILL_VENGEANCE				,"MA70 Vengeance"							},

{"�������"			,SKILL_TALARIA					,"MA80 Talaria"		,"At5_TALARIA.tga"		},
{"�����ǹ"			,SKILL_G_COUP					,"MA83 G_Coup"								},
{"������"			,SKILL_S_ARCUDA					,"MA86 S_Arcuda"	,"At5_S_ARCUDA.tga"		},
{"����ͻϮ"			,SKILL_S_FEAR					,"MA90 S_Fear"								},


///////////////// ��˾����
{"����֮��"			,SKILL_HEALING					,"MP10 Healing"								},
{"ʥ�����"			,SKILL_HOLY_BOLT				,"MP12 HolyBolt"							},
{"��â����"			,SKILL_MULTISPARK				,"MP14 M_Spark"								},
{"����֮��"			,SKILL_HOLY_MIND				,"MP17 HolyMind"							},

{"���ҫ��"			,SKILL_MEDITATION				,"MP20 Meditation"							},
{"��֮�׵�"			,SKILL_DIVINE_LIGHTNING			,"MP23 D_Lightning"							},
{"��ʥ����"			,SKILL_HOLY_REFLECTION			,"MP26 H_Reflection","Pr2_H_REFLECTION.tga"	},
{"ʥ��֮��"			,SKILL_GRAND_HEALING			,"MP30 G_Healing"							},

{"��Ӱ˫��"		    ,SKILL_VIGOR_BALL				,"MP40 V_Ball"								},
{"����֮��"			,SKILL_RESURRECTION				,"MP43 Resurrection"						},
{"ʥ��֮��"			,SKILL_EXTINCTION				,"MP46 Extinction"							},
{"��ʥ֮��"			,SKILL_VIRTUAL_LIFE				,"MP50 V_Life"		,"Pr3_V_LIFE.tga"		},

{"��˪����"			,SKILL_GLACIAL_SPIKE			,"MP60 G_Spike"								},
{"��������"			,SKILL_REGENERATION_FIELD		,"MP63 R_Field"		,"Pr4_R_FIELD.tga"		},
{"����֮ŭ"			,SKILL_CHAIN_LIGHTNING			,"MP66 C_Lightning"							},
{"��ʥ��ʹ"			,SKILL_SUMMON_MUSPELL			,"MP70 S_Muspell"	,"Pr4_S_MUSPELL.tga"	},

{"��ʥ�粨"			,SKILL_S_IMPACT					,"MP80 S_Impact"							},
{"��֮����"			,SKILL_P_ICE					,"MP83 P_Ice"								},
{"������ʹ"			,SKILL_S_PRMIEL					,"MP86 S_Meteo"								},
{"��Ůɢ��"			,SKILL_B_KRISHNA				,"MP90 B_Krishna"	,"Pr5_B_Krishna.tga"	},

//ħ��ʦ����
{"ħ��ת��"			,SKILL_AGONY					,"MM10 Agony"								},
{"���֮��"			,SKILL_FIRE_BOLT				,"MM12 FireBolt"							},
{"����֮��"			,SKILL_ZENITH					,"MM14 Zenith"		,"Mg1_ZENITH.tga"		},
{"����֮��"			,SKILL_FIRE_BALL				,"MM17 FireBall"							},

{"��������"			,SKILL_MENTAL_MASTERY			,"MM20 M_Mastery"							},
{"������"			,SKILL_WATORNADO				,"MM23 Watornado"							},
{"Ԫ��֮��"			,SKILL_ENCHANT_WEAPON			,"MM26 E_Weapon"	,"Mg2_E_WEAPON.tga"		},
{"ڤ��֮��"			,SKILL_DEAD_RAY  				,"MM30 D_Ray"},

{"ħ���ػ�"			,SKILL_ENERGY_SHIELD			,"MM40 E_Shield"	,"Mg3_E_SHIELD.tga"		},
{"���ѳ��"			,SKILL_DIASTROPHISM				,"MM43 Diastrophism"						},
{"����ٻ�"			,SKILL_SPIRIT_ELEMENTAL			,"MM46 S_Elemental"	,"Mg3_S_ELEMENTAL.tga"	},
{"Ԫ��֮��"			,SKILL_DANCING_SWORD  			,"MM50 D_Sword"		,"Mg3_D_SWORD.tga"		},

{"��������"			,SKILL_FIRE_ELEMENTAL			,"MM60 F_Elemental"	,"Mg4_F_ELEMENTAL.tga"	},
{"���沨��"			,SKILL_FLAME_WAVE				,"MM63 F_Wave"},
{"�ռ�Ť��"			,SKILL_DISTORTION				,"MM66 Distortion"	,"Mg4_DISTORTION.tga"	},
{"��ʯ�ٻ�"		    ,SKILL_M_METEO					,"MM70 Meteo"},

{"���ǻ���"			,SKILL_SILRAPHIM				,"MM80 Silraphim"							},
{"��С֮��"			,SKILL_V_TENUS					,"MM83 V_Tenus"								},
{"��ʥϴ��"			,SKILL_P_IGNIS					,"MM86 P_Ignis"								},
{"ʥ�ⷨ��"		    ,SKILL_T_ANIMA					,"MM90 T_Anima"		,"Ma5_T_Anima.tga"		},

//�̿ͼ���
{"�̻�"				,SKILL_STRINGER 				,"TA10 Stingger"							},
{"����"				,SKILL_RUNNING_HIT				,"TA12 R_Hit"								},
{"ǿ������"			,SKILL_SWORDMASTERY				,"TA14 D_Mastery"							},
{"���㹥��"			,SKILL_WISP						,"TA17 Wisp"		,"As1_WISP.tga"			},

{"��������"			,SKILL_VENOM_THORN				,"TA20 V_Throne"							},
{"����֮��"			,SKILL_ALAS						,"TA23 Alas"		,"As2_ALAS.tga"			},
{"�����"			,SKILL_SOUL_SHOCK				,"TA26 S_Shock"								},
{"������ʦ"			,SKILL_ATTACK_MASTERY  			,"TA30 A_Mastery"							},

{"�ɽ�֮��"			,SKILL_SORE_SWORD				,"TA40 S_Sword"								},
{"��ն"				,SKILL_BEAT_UP					,"TA43 B_Up"								},
{"���ݴ�ʦ"			,SKILL_INPES					,"TA46 Inpes"		,"As3_INPES.tga"		},
{"��ä"				,SKILL_BLIND  					,"TA50 Blind"		,"As3_BLIND.tga"		},

{"����֮��"			,SKILL_FROST_WIND				,"TA60 F_Wind"								},
{"��������"			,SKILL_FATAL_MASTERY			,"TA63 F_Mastery"							},
{"����֮��"			,SKILL_POLLUTED					,"TA66 Polluted"							},
{"Ӱ������"		    ,SKILL_PASTING_SHADOW			,"TA70 P_Shadow"							},

{"Ӱ�ӻ���"			,SKILL_SHADOW_BOMB				,"TS80 J_Bomb"								},
{"����ն"			,SKILL_RISING_SHASH				,"TS83 R_Slash"								},
{"������β"			,SKILL_VIOLENCE_STAB			,"TS86 V_Stab"								},
{"�籩֮��"		    ,SKILL_STORM					,"TS90 Storm"								},

//��������
{"��������"			,SKILL_DARK_BOLT				,"MS10 Darkbolt"							},
{"���ڲ���"			,SKILL_DARK_WAVE				,"MS12 Darkwave"							},
{"�����׻�"			,SKILL_CURSE_LAZY				,"MS14 Curselazy"							},
{"����ƽ��"			,SKILL_INNER_PEACE				,"MS17 I_peace"								},

{"��������"			,SKILL_SPIRITUAL_FLARE			,"MS20 S_Flare"								},
{"������"			,SKILL_SPIRITUAL_MANACLE		,"MS23 S_Manacle"							},
{"��ȡ"				,SKILL_CHASING_HUNT				,"MS26 C_Hunt"		,"Sh2_C_HUNT.tga"		},
{"���˶�"			,SKILL_ADVENT_MIGAL				,"MS30 A_Migal"		,"Sh2_A_MIGAL.tga"		},

{"����ʦ"			,SKILL_RAIN_MAKER				,"MS40 R_Maker"		,"Sh3_R_MAKER.tga"		},
{"½�����"			,SKILL_LAND_OF_GHOST			,"MS43 L_Ghost"								},
{"����ػ�"			,SKILL_HAUNT					,"MS46 Haunt"								},
{"ץ��"				,SKILL_SCRATCH  				,"MS50 Scratch"								},

{"��Ѫ֮ҹ"			,SKILL_RECALL_BLOODYKNIGHT		,"MS60 R_Knight"	,"Sh4_R_KNIGHT.tga"		},
{"����"				,SKILL_JUDGEMENT				,"MS63 Judge"								},
{"�׵�����"			,SKILL_ADVENT_MIDRANDA			,"MS66 A_Midranda"	,"Sh4_A_MIDRANDA.tga"	},
{"���ն���"		    ,SKILL_MOURNING_OF_PRAY			,"MS70 M_pray"								},

{"��������"			,SKILL_CREED					,"MS80 Creed"		,"Sh5_CREED.tga"		},
{"����֮��"			,SKILL_PRESS_OF_DEITY			,"MS83 P_Deity"								},
{"����֮צ"			,SKILL_CHOSTY_NAIL				,"MS86 G_Nail"								},
{"�߼�����"		    ,SKILL_HIGH_REGENERATION		,"MS90 H_Regene"							},

{"ף��ʥ��"			,CLANSKILL_ABSORB				,""					,"wa1-1.tga"			},
{"ף��ʥ��"			,CLANSKILL_ATTACK				,""					,"wa1-3.tga"			},
{"ף��ʥ��"			,CLANSKILL_EVASION				,""					,"wa1-2.tga"			},

{"��Ÿ���þ�"		,SCROLL_INVULNERABILITY			,""					,"S_Ath.tga"			},
{"���鸮 ����"		,SCROLL_CRITICAL				,""					,"S_Dea.tga"			},
{"��� ���� "		,SCROLL_EVASION					,""					,"S_Eva.tga"			},
{"�����̾� ����"	,STONE_R_FIRECRYTAL				,""					,"F_C_M.tga"			},
{"�����̾� ����"	,STONE_R_ICECRYTAL				,""					,"I_C_M.tga"			},
{"�����̾� ����"	,STONE_R_LINGHTINGCRYTAL		,""					,"L_C_M.tga"			},
{"����Ʈ ����"		,STONE_A_FIGHTER				,""					,"Ft_R.tga"				},
{"����Ʈ ����"		,STONE_A_MECHANICIAN			,""					,"Mc_R.tga"				},
{"����Ʈ ����"		,STONE_A_PIKEMAN				,""					,"Pk_R.tga"				},
{"����Ʈ ����"		,STONE_A_ARCHER					,""					,"Ac_R.tga"				},
{"����Ʈ ����"		,STONE_A_KNIGHT					,""					,"Kt_R.tga"				},
{"����Ʈ ����"		,STONE_A_ATALANTA				,""					,"At_R.tga"				},
{"����Ʈ ����"		,STONE_A_MAGICIAN				,""					,"Mg_R.tga"				},
{"����Ʈ ����"		,STONE_A_PRIESTESS				,""					,"Pt_R.tga"				},
{"����Ʈ ����"		,STONE_A_ASSASSIN				,""					,"As_R.tga"				},
{"����Ʈ ����"		,STONE_A_SAMAN					,""					,"Sh_R.tga"				},

{"���ͳ� ������"	,SCROLL_P_INVULNERABILITY		,""					,"S_Ath.tga"			},
{"����Ʋ ����"		,SCROLL_P_CRITICAL				,""					,"S_Dea.tga"			},
{"���Ʈ ��ũ��"	,SCROLL_P_EVASION				,""					,"S_Eva.tga"			},

{"��������"			,BOOSTER_ITEM_LIFE				,""					,"Booster_01.tga"		},
{"ħ������"			,BOOSTER_ITEM_MANA				,""					,"Booster_02.tga"		},
{"��������"			,BOOSTER_ITEM_STAMINA			,""					,"Booster_03.tga"		},

{"�����ٶ�"			,SKILLDELAY_ITEM_LIFE			,""					,"Booster_01.tga"		},
};


sSKILLBOX	sSkillBox[SIN_MAX_SKILLBOX] =
{
	{{142		,537	,142 + 49		,537 + 46}},												//��ͨ

	{{27 - 10		,502	,27 + 49 - 10	,502 + 46},{27 + 47 - 10	,502 + 5	,27 + 47 + 5 - 10		,502 + 40}},	// 1ת
	{{67 - 10		,546	,67 + 49 - 10	,546 + 46},{67 + 47 - 10	,546 + 5	,67 + 47 + 5 - 10		,546 + 40}},
	{{77 - 10		,466	,77 + 49 - 10	,466 + 46},{77 + 47 - 10	,466 + 5	,77 + 47 + 5 - 10		,466 + 40}},
	{{137 - 10	,476	,137 + 49 - 10	,476 + 46},{137 + 47 - 10	,476 + 5	,137 + 47 + 5 - 10	,476 + 40}},

	{{212 - 15	,466	,212 + 49 - 15	,466 + 46},{212 + 47 - 15	,466 + 5	,212 + 47 + 5 - 15	,466 + 40}},	// 2ת
	{{232 - 15	,516	,232 + 49 - 15	,516 + 46},{232 + 47 - 15	,516 + 5	,232 + 47 + 5 - 15	,516 + 40}},
	{{272 - 15	,466	,272 + 49 - 15	,466 + 46},{272 + 47 - 15	,466 + 5	,272 + 47 + 5 - 15	,466 + 40}},
	{{332		,466	,332 + 49		,466 + 46},{332 + 47	,466 + 5	,332 + 47 + 5		,466 + 40}},

	{{402		,476	,402 + 49		,476 + 46},{402 + 47	,476 + 5	,402 + 47 + 5		,476 + 40}},	// 3ת
	{{472		,456	,472 + 49		,456 + 46},{472 + 47	,456 + 5	,472 + 47 + 5		,456 + 40}},
	{{512		,506	,512 + 49		,506 + 46},{512 + 47	,506 + 5	,512 + 47 + 5		,506 + 40}},
	{{532		,456	,532 + 49		,456 + 46},{532 + 47	,456 + 5	,532 + 47 + 5		,456 + 40}},

	{{602		,481	,602 + 49		,481 + 46},{602 + 47	,481 + 5	,602 + 47 + 5		,481 + 40}},	// 4ת
	{{662		,511	,662 + 49		,511 + 46},{662 + 47	,511 + 5	,662 + 47 + 5		,511 + 40}},
	{{681		,461	,681 + 49		,461 + 46},{681 + 47	,461 + 5	,681 + 47 + 5		,461 + 40}},
	{{722		,511	,722 + 49		,511 + 46},{722 + 47	,511 + 5	,722 + 47 + 5		,511 + 40}},

	{{27 - 10		,502	,27 + 49 - 10	,502 + 46},{27 + 47 - 10	,502 + 5	,27 + 47 + 5 - 10		,502 + 40}},	// 5ת
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



//���߾�������� �����Ѵ�
int AddVirtualLife[2] = { 0,0 };
int sinVirtualLifeTime = 0;
int sinVirtualLifePercent = 0;

// ����� - �ν��� ������(�����)
int AddBoosterLife = 0;
int BoosterLifeTime = 0;
int BoosterLifePercent = 0;
int LifeFlag = 0;
short tempLife[2] = { 0,0 };

// ����� - �ν��� ������(���)
int AddVirtualMana[2] = { 0,0 };
int sinVirtualManaTime = 0;
int sinVirtualManaPercent = 0;
int ManaFlag = 0;
short tempMana[2] = { 0,0 };

// ����� - �ν��� ������(�ٷ�)
int AddVirtualStamina[2] = { 0,0 };
int sinVirtualStaminaTime = 0;
int sinVirtualStaminaPercent = 0;
int StaminaFlag = 0;
short tempStamina[2] = { 0,0 };

// �庰 - ��ų ������
int sinAddSkillDelay = 0;
int sinSkillDelayTime = 0;
int SkillDelayFlag = 0;
