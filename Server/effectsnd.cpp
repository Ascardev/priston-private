#include "StdAfx.h"
#include "smwsock.h"

#include "character.h"
#include "srcsound\\dxwav.h"
#include "particle.h"
#include "fileread.h"
#include "playmain.h"
#include "netplay.h"
#include "effectsnd.h"
#include "field.h"

extern char sangJuWav[NUM_SOUNDS][64];
extern char *sangJuWav2[NUM_SOUNDS];
extern int  sangJuWav_F[NUM_SOUNDS];

struct	snFIND_EFFECT
{
	char	*lpStringCode;
	DWORD	CharSoundCode;
};


struct	snEFFECT
{
	DWORD	RealSoundNum;
	DWORD	CharSoundCode;
	DWORD	MotionState;
	DWORD	WeaponState;
};

#define	snFIND_EFFECT_MAX			232

snFIND_EFFECT	snFindEffects[snFIND_EFFECT_MAX] =
{
	{ "wav\\Effects\\monster\\cyclops\\"	,	snCHAR_SOUND_CYCLOPS		},
	{ "wav\\Effects\\monster\\hob goblin\\"	,	snCHAR_SOUND_HOBGOBLIN		},
	{ "wav\\Effects\\monster\\Imp\\"		,	snCHAR_SOUND_IMP			},
	{ "wav\\Effects\\monster\\miniG\\"		,	snCHAR_SOUND_MINIG			},
	{ "wav\\Effects\\monster\\plant\\"		,	snCHAR_SOUND_PLANT			},
	{ "wav\\Effects\\monster\\skeleton\\"	,	snCHAR_SOUND_SKELETON		},
	{ "wav\\Effects\\monster\\zombi\\"		,	snCHAR_SOUND_ZOMBI			},
	{ "wav\\Effects\\monster\\obit\\"		,	snCHAR_SOUND_OBIT			},

	{ "wav\\Effects\\monster\\hopt\\"		,	snCHAR_SOUND_HOPT			},
	{ "wav\\Effects\\monster\\bargon\\"		,	snCHAR_SOUND_BARGON			},
	{ "wav\\Effects\\monster\\leech\\"		,	snCHAR_SOUND_LEECH			},
	{ "wav\\Effects\\monster\\mushroom\\"	,	snCHAR_SOUND_MUSHROOM		},

	{ "wav\\Effects\\monster\\Arma\\"		,	snCHAR_SOUND_ARMA			},
	{ "wav\\Effects\\monster\\scorpion\\"	,	snCHAR_SOUND_SCORPION		},

	{ "wav\\Effects\\monster\\HeadCutter\\"	,	snCHAR_SOUND_HEADCUTTER		},
	{ "wav\\Effects\\monster\\Sandlem\\"	,	snCHAR_SOUND_SANDLEM		},
	{ "wav\\Effects\\monster\\Web\\"		,	snCHAR_SOUND_WEB			},
	{ "wav\\Effects\\monster\\HopyKing\\"	,	snCHAR_SOUND_HOPYKING		},
	{ "wav\\Effects\\monster\\Crip\\"		,	snCHAR_SOUND_CRIP			},
	{ "wav\\Effects\\monster\\Buma\\"		,	snCHAR_SOUND_BUMA			},
	{ "wav\\Effects\\monster\\Decoy\\"		,	snCHAR_SOUND_DECOY			},
	{ "wav\\Effects\\monster\\Doral\\"		,	snCHAR_SOUND_DORAL			},
	{ "wav\\Effects\\monster\\Figon\\"		,	snCHAR_SOUND_FIGON			},
	{ "wav\\Effects\\monster\\StoneGiant\\"	,	snCHAR_SOUND_STONEGIANT		},
	{ "wav\\Effects\\monster\\Greven\\"		,	snCHAR_SOUND_GREVEN			},
	{ "wav\\Effects\\monster\\illusionknight\\" ,snCHAR_SOUND_ILLUSIONKNIGHT},
	{ "wav\\Effects\\monster\\SkeletonRange\\"	,	snCHAR_SOUND_SKELETONRANGE},
	{ "wav\\Effects\\monster\\SkeletonMelee\\"	,	snCHAR_SOUND_SKELETONMELEE},
	{ "wav\\Effects\\monster\\wolverin\\"		,	snCHAR_SOUND_WOLVERLIN	},

	{ "wav\\Effects\\monster\\Rabie\\"		,	snCHAR_SOUND_RABIE			},
	{ "wav\\Effects\\monster\\Mudy\\"		,	snCHAR_SOUND_MUDY			},
	{ "wav\\Effects\\monster\\Sen\\"		,	snCHAR_SOUND_SEN			},
	{ "wav\\Effects\\monster\\Egan\\"		,	snCHAR_SOUND_EGAN			},
	{ "wav\\Effects\\monster\\BeeDog\\"		,	snCHAR_SOUND_BEEDOG			},
	{ "wav\\Effects\\monster\\MutantPlant\\",	snCHAR_SOUND_MUTANTPLANT	},
	{ "wav\\Effects\\monster\\MutantRabie\\",	snCHAR_SOUND_MUTANTRABIE	},
	{ "wav\\Effects\\monster\\MutantTree\\"	,	snCHAR_SOUND_MUTANTTREE		},
	{ "wav\\Effects\\monster\\Avelisk\\"	,	snCHAR_SOUND_AVELISK		},
	{ "wav\\Effects\\monster\\Naz\\"		,	snCHAR_SOUND_NAZ			},
	{ "wav\\Effects\\monster\\Mummy\\"		,	snCHAR_SOUND_MUMMY			},
	{ "wav\\Effects\\monster\\Hulk\\"		,	snCHAR_SOUND_HULK			},
	{ "wav\\Effects\\monster\\Hungky\\"		,	snCHAR_SOUND_HUNGKY	},
	{ "wav\\Effects\\monster\\Succubus\\"	,	snCHAR_SOUND_SUCCUBUS		},
	{ "wav\\Effects\\monster\\Dawlin\\"		,	snCHAR_SOUND_DAWLIN			},
	{ "wav\\Effects\\monster\\Shadow\\"		,	snCHAR_SOUND_SHADOW			},
	{ "wav\\Effects\\monster\\Berserker\\"	,	snCHAR_SOUND_BERSERKER		},
	{ "wav\\Effects\\monster\\IronGuard\\"	,	snCHAR_SOUND_IRONGUARD		},
	{ "wav\\Effects\\monster\\Fury\\"		,	snCHAR_SOUND_FURY			},
	{ "wav\\Effects\\monster\\Sliver\\"		,	snCHAR_SOUND_SLIVER			},
	{ "wav\\Effects\\monster\\Ratoo\\"		,	snCHAR_SOUND_RATOO			},
	{ "wav\\Effects\\monster\\Stygianlord\\",	snCHAR_SOUND_STYGIANLORD	},
	{ "wav\\Effects\\monster\\Omicron\\"	,	snCHAR_SOUND_OMICRON		},
	{ "wav\\Effects\\monster\\D-Machine\\"	,	snCHAR_SOUND_DMACHINE		},
	{ "wav\\Effects\\monster\\Metron\\"		,	snCHAR_SOUND_METRON			},
	{ "wav\\Effects\\monster\\MrGhost\\"	,	snCHAR_SOUND_MRGHOST		},


	{ "wav\\Effects\\monster\\VAMPIRICBAT\\",	snCHAR_SOUND_VAMPIRICBAT	},
	{ "wav\\Effects\\monster\\MIREKEEPER\\"	,	snCHAR_SOUND_MIREKEEPER		},
	{ "wav\\Effects\\monster\\MUFFIN\\"		,	snCHAR_SOUND_MUFFIN			},
	{ "wav\\Effects\\monster\\SOLIDSNAIL\\"	,	snCHAR_SOUND_SOLIDSNAIL		},
	{ "wav\\Effects\\monster\\BEEVIL\\"		,	snCHAR_SOUND_BEEVIL			},
	{ "wav\\Effects\\monster\\NIGHTMARE\\"	,	snCHAR_SOUND_NIGHTMARE		},
	{ "wav\\Effects\\monster\\STONEGOLEM\\"	,	snCHAR_SOUND_STONEGOLEM		},
	{ "wav\\Effects\\monster\\THORNCRAWLER\\",	snCHAR_SOUND_THORNCRAWLER	},
	{ "wav\\Effects\\monster\\HEAVYGOBLIN\\",	snCHAR_SOUND_HEAVYGOBLIN	},
	{ "wav\\Effects\\monster\\EVILPLANT\\"	,	snCHAR_SOUND_EVILPLANT		},
	{ "wav\\Effects\\monster\\HAUNTINGPLANT\\",	snCHAR_SOUND_HAUNTINGPLANT	},
	{ "wav\\Effects\\monster\\DARKKNIGHT\\"	,	snCHAR_SOUND_DARKKNIGHT		},
	{ "wav\\Effects\\monster\\Guardian-Saint\\",snCHAR_SOUND_GUARDIAN_SAINT	},

	{ "wav\\Effects\\monster\\ChainGolem\\"	,	snCHAR_SOUND_CHAINGOLEM		},
	{ "wav\\Effects\\monster\\DeadZone\\"	,	snCHAR_SOUND_DEADZONE		},
	{ "wav\\Effects\\monster\\Grotesque\\"	,	snCHAR_SOUND_GROTESQUE		},
	{ "wav\\Effects\\monster\\Hypermachine\\",	snCHAR_SOUND_HYPERMACHINE	},
	{ "wav\\Effects\\monster\\IronFist\\"	,	snCHAR_SOUND_IRONFIST		},
	{ "wav\\Effects\\monster\\Morgon\\"		,	snCHAR_SOUND_MORGON			},
	{ "wav\\Effects\\monster\\Mountain\\"	,	snCHAR_SOUND_MOUNTAIN		},
	{ "wav\\Effects\\monster\\Rampage\\"	,	snCHAR_SOUND_RAMPAGE		},
	{ "wav\\Effects\\monster\\RunicGuardian\\",	snCHAR_SOUND_RUNICGUARDIAN	},
	{ "wav\\Effects\\monster\\Sadness\\"	,	snCHAR_SOUND_SADNESS		},
	{ "wav\\Effects\\monster\\TowerGolem\\"	,	snCHAR_SOUND_TOWERGOLEM		},
	{ "wav\\Effects\\monster\\VampiricBee\\",	snCHAR_SOUND_VAMPRICBEE		},
	{ "wav\\Effects\\monster\\VampiricMachine\\",snCHAR_SOUND_VAMPRICMACHINE},
	{ "wav\\Effects\\monster\\Omu\\",			snCHAR_SOUND_OMU			},
	{ "wav\\Effects\\monster\\AvelinArcher\\",	snCHAR_SOUND_AVELIN_ARCHER	},
	{ "wav\\Effects\\monster\\AvelinQueen\\",	snCHAR_SOUND_AVELIN_QUEEN	},
	{ "wav\\Effects\\monster\\Babel\\",			snCHAR_SOUND_BABEL			},

	{ "wav\\Effects\\monster\\Mystic\\",		snCHAR_SOUND_MYSTIC			},
	{ "wav\\Effects\\monster\\HEAVYGOBLIN\\",	snCHAR_SOUND_ICEGOBLIN		},
	{ "wav\\Effects\\monster\\ColdEye\\",		snCHAR_SOUND_COLDEYE		},
	{ "wav\\Effects\\monster\\Frozen\\",		snCHAR_SOUND_FROZEN			},
	{ "wav\\Effects\\monster\\STONEGOLEM\\",	snCHAR_SOUND_ICEGOLEM		},
	{ "wav\\Effects\\monster\\Frost\\",			snCHAR_SOUND_FROST			},
	{ "wav\\Effects\\monster\\ChaosCara\\",		snCHAR_SOUND_CHAOSCARA		},
	{ "wav\\Effects\\monster\\DeathKnight\\",	snCHAR_SOUND_DEATHKNIGHT	},

	{ "wav\\Effects\\monster\\GreateGreven\\",	snCHAR_SOUND_GREATE_GREVEN	},
	{ "wav\\Effects\\monster\\LizardFolk\\",	snCHAR_SOUND_LIZARDFOLK		},
	{ "wav\\Effects\\monster\\M_Lord\\",		snCHAR_SOUND_M_LORD			},
	{ "wav\\Effects\\monster\\Spider\\",		snCHAR_SOUND_SPIDER			},
	{ "wav\\Effects\\monster\\Stingray\\",		snCHAR_SOUND_STINGRAY		},
	{ "wav\\Effects\\monster\\Strider\\",		snCHAR_SOUND_STRIDER		},

	{ "wav\\Effects\\monster\\TurtleCannon\\",	snCHAR_SOUND_TURTLE_CANNON	},
	{ "wav\\Effects\\monster\\DevilBird\\",		snCHAR_SOUND_DEVIL_BIRD		},
	{ "wav\\Effects\\monster\\BlizzardGiant\\",	snCHAR_SOUND_BLIZZARD_GIANT	},
	{ "wav\\Effects\\monster\\Kelvezu\\",		snCHAR_SOUND_KELVEZU		},

	{ "wav\\Effects\\monster\\DarkPhalanx\\",	snCHAR_SOUND_DARKPHALANX	},
	{ "wav\\Effects\\monster\\BloodyKnight\\",	snCHAR_SOUND_BLOODYKNIGHT	},
	{ "wav\\Effects\\monster\\Chimera\\",		snCHAR_SOUND_CHIMERA		},
	{ "wav\\Effects\\monster\\FireWorm\\",		snCHAR_SOUND_FIREWORM		},
	{ "wav\\Effects\\monster\\HellHound\\",		snCHAR_SOUND_HELLHOUND		},
	{ "wav\\Effects\\monster\\DarkGuard\\",		snCHAR_SOUND_DARKGUARD		},
	{ "wav\\Effects\\monster\\DarkMage\\",		snCHAR_SOUND_DARKMAGE		},

	{ "wav\\Effects\\monster\\MonMokova\\",		snCHAR_SOUND_MOKOVA			},
	{ "wav\\Effects\\monster\\MonTempleguard\\",snCHAR_SOUND_TEMPLEGUARD	},
	{ "wav\\Effects\\monster\\MonSeto\\",		snCHAR_SOUND_SETO			},
	{ "wav\\Effects\\monster\\MonKingSpider\\",	snCHAR_SOUND_KINGSPIDER		},

	{ "wav\\Effects\\monster\\d_kn\\",			snCHAR_SOUND_REVIVED_KNIGHT	},
	{ "wav\\Effects\\monster\\d_magi\\",		snCHAR_SOUND_REVIVED_MAGICIAN},
	{ "wav\\Effects\\monster\\d_atal\\",		snCHAR_SOUND_REVIVED_ATALANTA},
	{ "wav\\Effects\\monster\\d_fi\\",			snCHAR_SOUND_REVIVED_FIGTHER},
	{ "wav\\Effects\\monster\\d_ar\\",			snCHAR_SOUND_REVIVED_ARCHER	},
	{ "wav\\Effects\\monster\\d_meca\\",		snCHAR_SOUND_REVIVED_MECANICIAN},
	{ "wav\\Effects\\monster\\d_pa\\",			snCHAR_SOUND_REVIVED_PIKEMAN},
	{ "wav\\Effects\\monster\\d_pr\\",			snCHAR_SOUND_REVIVED_PRIESTESS},
	{ "wav\\Effects\\monster\\deadhopt\\",		snCHAR_SOUND_DEADHOPT		},
	{ "wav\\Effects\\monster\\deadkinghopy\\",	snCHAR_SOUND_DEADKINGHOPY	},
	{ "wav\\Effects\\monster\\gorgon\\",		snCHAR_SOUND_GORGON			},
	{ "wav\\Effects\\monster\\hobogolem\\",		snCHAR_SOUND_HOBOGOLEM		},

	// ��������
	{ "wav\\Effects\\monster\\Niken\\",			snCHAR_SOUND_NIKEN			},
	{ "wav\\Effects\\monster\\Mimic\\",			snCHAR_SOUND_MIMIC			},
	{ "wav\\Effects\\monster\\KingBat\\",		snCHAR_SOUND_KINGBAT		},
	{ "wav\\Effects\\monster\\GoblinShaman\\",	snCHAR_SOUND_GOBLINSHAMAN	},
	{ "wav\\Effects\\monster\\Hest\\",			snCHAR_SOUND_HEST			},

	// �޾�֮��
	{ "wav\\Effects\\monster\\Ruca\\",			snCHAR_SOUND_RUCA			},
	{ "wav\\Effects\\monster\\NazSenior\\",		snCHAR_SOUND_NAZSENIOR		},
	{ "wav\\Effects\\monster\\Igolation\\",		snCHAR_SOUND_IGOLATION		},
	{ "wav\\Effects\\monster\\Kakoa\\",			snCHAR_SOUND_KAKOA			},
	{ "wav\\Effects\\monster\\Sprin\\",			snCHAR_SOUND_SPRIN			},
	{ "wav\\Effects\\monster\\UndeadMaple\\",	snCHAR_SOUND_UNDEADMAPLE	},
	{ "wav\\Effects\\monster\\Xetan\\",			snCHAR_SOUND_XETAN			},

	{ "wav\\Effects\\monster\\Bebechick\\",		snCHAR_SOUND_BEBECHICK		},
	{ "wav\\Effects\\monster\\PaPachick\\",		snCHAR_SOUND_PAPACHICK		},

	{ "wav\\Effects\\monster\\watermelon\\",	snCHAR_SOUND_WATERMELON		},
	{ "wav\\Effects\\monster\\Bear\\",			snCHAR_SOUND_BEAR			},
	{ "wav\\Effects\\monster\\PumpkinGhost\\",	snCHAR_SOUND_PUMPKINGHOST	},
	{ "wav\\Effects\\monster\\Snowman\\",		snCHAR_SOUND_SNOWMAN		},
	{ "wav\\Effects\\monster\\DevilShy\\",		snCHAR_SOUND_DEVILSHY		},
	{ "wav\\Effects\\monster\\sakura\\",		snCHAR_SOUND_SAKURA			},

	{ "wav\\Effects\\monster\\Coma\\",			snCHAR_SOUND_COMA			},
	{ "wav\\Effects\\monster\\Brazilbear\\",	snCHAR_SOUND_BRAZILBEAR		},

	// ����ɯ
	{ "wav\\Effects\\monster\\Boitata\\",		snCHAR_SOUND_BOITATA		},
	// �����
	{ "wav\\Effects\\monster\\IceSerpent\\",	smCHAR_SOUND_ICESERPENT		},
	{ "wav\\Effects\\monster\\IceWorm\\",		smCHAR_SOUND_ICEWORM		},
	{ "wav\\Effects\\monster\\Minebat\\",		smCHAR_SOUND_MINEBAT		},
	{ "wav\\Effects\\monster\\MineGolem\\",		smCHAR_SOUND_MINEGOLEM		},
	{ "wav\\Effects\\monster\\SealCrasher\\",	smCHAR_SOUND_SEALCRASHER	},
	{ "wav\\Effects\\monster\\Tarantulika\\",	smCHAR_SOUND_TARANTULIKA	},
	{ "wav\\Effects\\monster\\Tulla\\",			smCHAR_SOUND_TULLA			},
	{ "wav\\Effects\\monster\\UndeadManager\\",	smChAR_SOUND_UNDEADMANAGER	},
	{ "wav\\Effects\\monster\\UndeadMiner\\",	smCHAR_SOUND_UNDEADMINER	},

	// ������ͼ
	{ "wav\\Effects\\monster\\Billy\\",			smCHAR_SOUND_BILLY			},
	{ "wav\\Effects\\monster\\Hound\\",			smCHAR_SOUND_HOUND			},
	{ "wav\\Effects\\monster\\Lena\\",			smCHAR_SOUND_LENA			},
	{ "wav\\Effects\\monster\\marionette\\",	smCHAR_SOUND_MARIONETTE		},
	{ "wav\\Effects\\monster\\UndeadStalker\\",	smCHAR_SOUND_UNDEADSTALKER	},

	// ��ά˹�˿�
	{ "wav\\Effects\\monster\\ITechnician\\",	smCHAR_SOUND_ITECHNICIAN	},
	{ "wav\\Effects\\monster\\LTechnician\\",	smCHAR_SOUND_LTECHNICIAN	},
	{ "wav\\Effects\\monster\\LEngineer\\",		smCHAR_SOUND_LENGINEER		},
	{ "wav\\Effects\\monster\\ISoldier\\",		smCHAR_SOUND_ISOLDIER		},
	{ "wav\\Effects\\monster\\IBomber\\",		smCHAR_SOUND_IBOMBER		},
	{ "wav\\Effects\\monster\\LGuardian\\",		smCHAR_SOUND_LGUARDIAN		},
	{ "wav\\Effects\\monster\\IElite\\",		smCHAR_SOUND_IELITE			},
	{ "wav\\Effects\\monster\\Draxos\\",		smCHAR_SOUND_DRAXOS			},

	{ "wav\\Effects\\monster\\Lizard_Bigmama\\",	smCHAR_SOUND_LIZARD_BIGMAMA		},
	{ "wav\\Effects\\monster\\Lizard_Commander\\",	smCHAR_SOUND_LIZADR_COMMANDER	},
	{ "wav\\Effects\\monster\\Lizard_Doctor\\",		smCHAR_SOUND_LIZADR_DOCTOR		},
	{ "wav\\Effects\\monster\\Lizard_Elder\\",		smCHAR_SOUND_LIZADR_ELDER		},
	{ "wav\\Effects\\monster\\Lizard_Papa\\",		smCHAR_SOUND_LIZADR_PAPA		},
	{ "wav\\Effects\\monster\\Lizard_Soldier\\",	smCHAR_SOUND_LIZADR_SOLDIER		},

	//��˶�Ѩ����
	{ "wav\\Effects\\monster\\Nihil\\",			smCHAR_SOUND_NIHIL			},
	{ "wav\\Effects\\monster\\Acero\\",			smCHAR_SOUND_ACERO			},
	{ "wav\\Effects\\monster\\Chalybs\\",		smCHAR_SOUND_CHALYBS		},
	{ "wav\\Effects\\monster\\Greedy\\",		smCHAR_SOUND_GREEDY			},
	{ "wav\\Effects\\monster\\Inferno\\",		smCHAR_SOUND_INFERNO		},
	{ "wav\\Effects\\monster\\RGuard\\",		smCHAR_SOUND_RGUARD			},
	{ "wav\\Effects\\monster\\DMystery\\",		smCHAR_SOUND_DMYSTERY		},
	{ "wav\\Effects\\monster\\Ignis\\",			smCHAR_SOUND_IGNIS			},
	{ "wav\\Effects\\monster\\Najan\\",			smCHAR_SOUND_NAJAN			},
	{ "wav\\Effects\\monster\\Crios\\",			smCHAR_SOUND_CRIOS			},
	{ "wav\\Effects\\monster\\WLord\\",			smCHAR_SOUND_WLORD			},
	{ "wav\\Effects\\monster\\Midranda\\",		smCHAR_SOUND_MIDRANDA		},
	{ "wav\\Effects\\monster\\Dey\\",			smCHAR_SOUND_DEY			},
	{ "wav\\Effects\\monster\\Gurkob\\",		smCHAR_SOUND_GURKOB			},
	{ "wav\\Effects\\monster\\Shogoth\\",		smCHAR_SOUND_SHOGOTH		},
	{ "wav\\Effects\\monster\\Arhdyra\\",		smCHAR_SOUND_ARHDYRA		},
	{ "wav\\Effects\\monster\\Sathla\\",		smCHAR_SOUND_SATHLA			},
	{ "wav\\Effects\\monster\\Faugn\\",			smCHAR_SOUND_FAUGN			},
	{ "wav\\Effects\\monster\\Koon\\",			smCHAR_SOUND_KOON			},
	{ "wav\\Effects\\monster\\Yagditha\\",		smCHAR_SOUND_YAGDITHA		},

	{ "wav\\Effects\\monster\\Cstone\\",		smCHAR_SOUND_CSTONE			},
	{ "wav\\Effects\\monster\\Mountain\\",		smCHAR_SOUND_BLUEMOUNTAIN	},
	{ "wav\\Effects\\monster\\Morgon\\",		smCHAR_SOUND_MORGONIA		},
	{ "wav\\Effects\\monster\\ColdEye\\",		smCHAR_SOUND_REDEYE			},
	{ "wav\\Effects\\monster\\TurtleCannon\\",	smCHAR_SOUND_TURTLEDRAGON	},
	{ "wav\\Effects\\monster\\hellhound\\",		smCHAR_SOUND_BONEHOUND		},
	{ "wav\\Effects\\monster\\Hestian\\",		smCHAR_SOUND_HESTIAN		},


	//////////////////////// NPC //////////////////////////////////
	{ "wav\\Effects\\npc\\morif\\",				snCHAR_SOUND_NPC_MORIF		},
	{ "wav\\Effects\\npc\\mollywolf\\",			snCHAR_SOUND_NPC_MOLLYWOLF	},
	{ "wav\\Effects\\npc\\SkillMaster\\",		snCHAR_SOUND_NPC_SKILLMASTER},
	{ "wav\\Effects\\npc\\MagicMaster\\",		snCHAR_SOUND_NPC_MAGICMASTER},
	{ "wav\\Effects\\npc\\worldcup\\",			snCHAR_SOUND_WORLDCUP		},

	///////////////////////// ������ //////////////////////////////
	{ "wav\\Effects\\npc\\castledoor\\",	snCHAR_SOUND_CASTLE_DOOR		},
	{ "wav\\Effects\\npc\\crystal_r\\",		snCHAR_SOUND_CASTLE_CRYSTAL_R	},
	{ "wav\\Effects\\npc\\crystal_g\\",		snCHAR_SOUND_CASTLE_CRYSTAL_G	},
	{ "wav\\Effects\\npc\\crystal_b\\",		snCHAR_SOUND_CASTLE_CRYSTAL_B	},
	{ "wav\\Effects\\npc\\crystal_n\\",		snCHAR_SOUND_CASTLE_CRYSTAL_N	},
	{ "wav\\Effects\\npc\\tower-b\\",		snCHAR_SOUND_CASTLE_TOWER_B		},

	{ "wav\\Effects\\npc\\Soldier_A\\",		snCHAR_SOUND_CASTLE_SOLDER_A	},
	{ "wav\\Effects\\npc\\Soldier_B\\",		snCHAR_SOUND_CASTLE_SOLDER_B	},
	{ "wav\\Effects\\npc\\Soldier_C\\",		snCHAR_SOUND_CASTLE_SOLDER_C	},

	/////////////////////// 4����ų ��ȯ�� /////////////////////////

	{ "wav\\Effects\\monster\\wolverin\\"	,	snCHAR_SOUND_S_WOLVERLIN	},
	{ "wav\\Effects\\monster\\MetalGolem\\"	,	snCHAR_SOUND_S_METALGOLEM	},
	{ "wav\\Effects\\monster\\Figon\\"		,	snCHAR_SOUND_S_F_ELEMENTAL	},
	{ "wav\\Effects\\monster\\Arcuda\\"		,	snCHAR_SOUND_S_ARCUDA		},


	//////////////////////// ̹���� //////////////////////////////////
	{ "wav\\Effects\\player\\fighter\\"		,	snCHAR_SOUND_FIGHTER		},
	{ "wav\\Effects\\player\\Mechanician\\"	,	snCHAR_SOUND_MECHANICAN		},
	{ "wav\\Effects\\player\\archer\\"		,	snCHAR_SOUND_ARCHER			},
	{ "wav\\Effects\\player\\pikeman\\"		,	snCHAR_SOUND_PIKEMAN		},
	{ "wav\\Effects\\player\\Assassin\\"	,	snCHAR_SOUND_ASSASSIN		},

	//////////////////////// ħ���� //////////////////////////////////
	{ "wav\\Effects\\player\\Knight\\"		,	snCHAR_SOUND_KNIGHT			},
	{ "wav\\Effects\\player\\Atalanta\\"	,	snCHAR_SOUND_ATALANTA		},
	{ "wav\\Effects\\player\\Priestess\\"	,	snCHAR_SOUND_PRIESTESS		},
	{ "wav\\Effects\\player\\Magician\\"	,	snCHAR_SOUND_MAGICIAN		},
	{ "wav\\Effects\\player\\Shaman\\"		,	snCHAR_SOUND_SHAMAN			}
};


char *szSndWeaponPath = "wav\\Effects\\weapon\\";

#define	snFIND_EFFECT_MOTION_MAX	9
#define	snFIND_EFFECT_WEAPON_MAX	18

snFIND_EFFECT	snFindEffectsMotion[snFIND_EFFECT_MOTION_MAX] =
{
	{	"attack"		,		CHRMOTION_STATE_ATTACK	},
	{	"damage"		,		CHRMOTION_STATE_DAMAGE	},
	{	"dead"			,		CHRMOTION_STATE_DEAD	},
	{	"neutral"		,		CHRMOTION_STATE_STAND	},
	{	"move"			,		CHRMOTION_STATE_WALK	},
	{	"disappear"		,		CHRMOTION_STATE_WARP	},
	{	"change"		,		CHRMOTION_STATE_WARP	},
	{	"skill"			,		CHRMOTION_STATE_SKILL	},
	{	"hammer"		,		CHRMOTION_STATE_HAMMER	}
};

snFIND_EFFECT	snFindEffectsWeapon[snFIND_EFFECT_WEAPON_MAX] =
{
	{	"one hand swing axe"		,		1	},
	{	"two hand swing axe"		,		2	},
	{	"one hand swing sword"		,		3	},
	{	"two hand swing sword"		,		4	},
	{	"one hand swing spear"		,		5	},
	{	"two hand swing spear"		,		6	},

	{	"one hand scratch"			,		7	},
	{	"bow shoot"					,		8	},
	{	"one hand swing blunt"		,		9	},
	{	"two hand swing blunt"		,		10	},
	{	"throwing"					,		11	},
	{	"one hand miss"				,		12	},
	{	"two hand miss"				,		13	},
	{	"punch hit"					,		14	},
	{	"one hand small swing"		,		15	},
	{	"critical hit"				,		16	},

	{	"one hand casting"			,		17	},
	{	"two hand casting"			,		18	}
};


int	CompareHeadString(char *szCodeString, char *szString)
{
	int cnt;
	int	len;
	char ch;

	len = lstrlen(szCodeString);

	for (cnt = 0; cnt < len; cnt++)
	{
		ch = szString[cnt];
		if (ch == 0)
			return FALSE;
		if (szCodeString[cnt] != ch)
		{
			if (ch<'A' && ch>'Z')
				return FALSE;
			if (szCodeString[cnt] != (ch + 0x20))
				return FALSE;
		}
	}

	return TRUE;
}

DWORD FindMotionState(char *szFile)
{
	int cnt;

	for (cnt = 0; cnt < snFIND_EFFECT_MOTION_MAX; cnt++) {
		if (CompareHeadString(snFindEffectsMotion[cnt].lpStringCode, szFile) == TRUE) {
			return snFindEffectsMotion[cnt].CharSoundCode;
		}
	}

	return NULL;
}

DWORD FindWeaponState(char *szFile)
{
	int cnt;

	for (cnt = 0; cnt < snFIND_EFFECT_WEAPON_MAX; cnt++) {
		if (CompareHeadString(snFindEffectsWeapon[cnt].lpStringCode, szFile) == TRUE) {
			return snFindEffectsWeapon[cnt].CharSoundCode;
		}
	}

	return NULL;
}


#define snEFFECT_MAX	1816

int	LoadSoundNum;

snEFFECT	snEffect[snEFFECT_MAX];
int	snEffectCnt;

snEFFECT	snEffectWeapon[snEFFECT_MAX];
int	snEffectWeaponCnt;



int sinSoundNum = 0;
extern char *sinSoundWav[];


char *esSoundWav[] = {
	"wav\\Effects\\FootSteps\\step01.wav",
	"wav\\Effects\\FootSteps\\step02.wav",
	"wav\\Effects\\FootSteps\\stonerun1.wav",
	"wav\\Effects\\FootSteps\\stonerun2.wav",
	"wav\\Effects\\FootSteps\\stonerun3.wav",
	"wav\\Ambient\\stone-mill.wav",						//5 ���� ȿ����
	"wav\\Effects\\event\\fieldstart.wav",				//6
	"wav\\Effects\\event\\level UP.wav",				//7
	"wav\\Effects\\event\\hosound.wav",					//8
	"wav\\Ambient\\tempskron-town.wav",					//AMBIENT_SOUND_NUM ��� ȿ���� 9

	"wav\\Effects\\monster\\Figon\\impact 1.wav",		//10	���̰� ��
	"wav\\Effects\\FootSteps\\stone-dun1.wav",			//11	���� �߼Ҹ�
	"wav\\Effects\\FootSteps\\stone-dun2.wav",			//12	���� �߼Ҹ�
	"wav\\Effects\\FootSteps\\stone-dun3.wav",			//13	���� �߼Ҹ�

	"wav\\Effects\\FootSteps\\inwater 1.wav",			//14	�� �߼Ҹ�
	"wav\\Effects\\FootSteps\\inwater 2.wav",			//15	�� �߼Ҹ�
	"wav\\Effects\\FootSteps\\inwater 3.wav",			//16	�� �߼Ҹ�

	"wav\\Effects\\FootSteps\\inwater 3.wav",			//17	CONTINUE_SOUND_NUM ���� ����	
	"wav\\Sod\\turn.wav",								//18

	"wav\\Sod\\SOD-item.wav",							//19	SOD������ ���

	"wav\\Effects\\Menu\\Event\\meteo 1.wav",			//20	���� ������
	"wav\\Effects\\Menu\\Event\\meteo 2.wav",			//21	���� ������
	"wav\\Effects\\Event\\sheltom_b.wav",				//22	���ұ����� �Ҹ�
	"wav\\Effects\\Event\\firecracker01.wav",			//23	���׼Ҹ�1
	"wav\\Effects\\Event\\firecracker02.wav",			//24	���׼Ҹ�1
	"wav\\Effects\\Event\\firecracker03.wav",			//25	���׼Ҹ�1

	0
};


int esSoundNum = 0;


#define	AMBIENT_SOUND_NUM		9
#define	AMBIENT_SOUND_NUM2		5
#define	CONTINUE_SOUND_NUM		17

int	AmbientSound = -1;
int	AmbientSound2 = -1;
int	AmbientSoundNum = 0;
int	AmbientSoundNum2 = 0;
int	ContinueSoundNum = 0;
int	AmbientObjectSound = 0;

int	ContSoundCount = 0;

//��� ȿ����
char *szAmbientSound[] = {
	"wav\\Ambient\\tempskron-town.wav",
	"wav\\Ambient\\forest-day.wav",
	"wav\\Ambient\\forest-night.wav",
	"wav\\Ambient\\ruin wind.wav",
	"wav\\Ambient\\desert wind.wav",
	"wav\\Ambient\\dungeon.wav",

	"wav\\Ambient\\temple_amb.wav",
	"wav\\Ambient\\cave_amb.wav",
	"wav\\Ambient\\darksanc_amb.wav",

	"wav\\Ambient\\iron_amb.wav",
	"wav\\Ambient\\iron_amb2.wav",
	"wav\\Ambient\\Babel Approach.wav",
	"wav\\Ambient\\icewind.wav",

	0
};

struct	sSKILL_SOUND_FILE {
	char	*szFile;
	DWORD	dwCode;
};

int	SkillSoundNum = 0;

sSKILL_SOUND_FILE	SkillSoundWav[] =
{
	{	"wav\\Effects\\Skill\\Learn_Skill.wav",							SKILL_SOUND_LEARN					},

	{	"wav\\Effects\\Skill\\Tempskron\\Extreme_Shield 01.wav",		SKILL_SOUND_EXTREME_SHIELD			},
	{	"wav\\Effects\\Skill\\Tempskron\\Jumping_Crash 01.wav",			SKILL_SOUND_JUMPING_CRASH1			},
	{	"wav\\Effects\\Skill\\Tempskron\\Jumping_Crash 02.wav",			SKILL_SOUND_JUMPING_CRASH2			},
	{	"wav\\Effects\\Skill\\Tempskron\\Mechanic_Bomb 01.wav",			SKILL_SOUND_MECHANIC_BOMB1			},
	{	"wav\\Effects\\Skill\\Tempskron\\Mechanic_Bomb 02.wav",			SKILL_SOUND_MECHANIC_BOMB2			},
	{	"wav\\Effects\\Skill\\Tempskron\\Perfect Aim 01.wav",			SKILL_SOUND_PERFECT_AIM				},
	{	"wav\\Effects\\Skill\\Tempskron\\Physical_Absorption 01.wav",	SKILL_SOUND_PHYSICAL_ABSORB1		},
	{	"wav\\Effects\\Skill\\Tempskron\\Physical_Absorption 02.wav",	SKILL_SOUND_PHYSICAL_ABSORB2		},
	{	"wav\\Effects\\Skill\\Tempskron\\Physical_Absorption 03.wav",	SKILL_SOUND_PHYSICAL_ABSORB3		},

	{	"wav\\Effects\\Skill\\Tempskron\\Pike_Wind 01.wav",				SKILL_SOUND_PIKE_WIND				},
	{	"wav\\Effects\\Skill\\Tempskron\\Scout_Hawk 01.wav",			SKILL_SOUND_SCOUT_HAWK1				},
	{	"wav\\Effects\\Skill\\Tempskron\\Scout_Hawk 02.wav",			SKILL_SOUND_SCOUT_HAWK2				},
	{	"wav\\Effects\\Skill\\Tempskron\\Wind_Arrow 01.wav",			SKILL_SOUND_WIND_ARROW				},

	{	"wav\\Effects\\Skill\\bow_skill_hit 01.wav",					SKILL_SOUND_ARROW_HIT1				},
	{	"wav\\Effects\\Skill\\bow_skill_hit 02.wav",					SKILL_SOUND_ARROW_HIT2				},

	{	"wav\\Effects\\Skill\\Skill_Swing 01.wav",						SKILL_SOUND_SKILL_SWING1			},
	{	"wav\\Effects\\Skill\\Skill_Swing 02.wav",						SKILL_SOUND_SKILL_SWING2			},

	{	"wav\\Effects\\Skill\\Tempskron\\Automation 01.wav",			SKILL_SOUND_SKILL_AUTOMATION1		},
	{	"wav\\Effects\\Skill\\Tempskron\\Automation 02.wav",			SKILL_SOUND_SKILL_AUTOMATION2		},
	{	"wav\\Effects\\Skill\\Tempskron\\Automation 03.wav",			SKILL_SOUND_SKILL_AUTOMATION3		},

	{	"wav\\Effects\\Skill\\Tempskron\\Maximize 01.wav",				SKILL_SOUND_SKILL_MAXIMIZE1			},
	{	"wav\\Effects\\Skill\\Tempskron\\Maximize 01.wav",				SKILL_SOUND_SKILL_MAXIMIZE2			},
	{	"wav\\Effects\\Skill\\Tempskron\\Maximize 01.wav",				SKILL_SOUND_SKILL_MAXIMIZE3			},

	{	"wav\\Effects\\Skill\\Tempskron\\Spark 01.wav",					SKILL_SOUND_SKILL_SPARK1			},
	{	"wav\\Effects\\Skill\\Tempskron\\Spark 02.wav",					SKILL_SOUND_SKILL_SPARK2			},
	{	"wav\\Effects\\Skill\\Tempskron\\Spark 03.wav",					SKILL_SOUND_SKILL_SPARK3			},

	{	"wav\\Effects\\Skill\\Tempskron\\Ground Pike 01.wav",			SKILL_SOUND_SKILL_GROUND_PIKE		},
	{	"wav\\Effects\\Skill\\Tempskron\\Tornado 01.wav",				SKILL_SOUND_SKILL_TORNADO1			},

	{	"wav\\Effects\\Skill\\Tempskron\\Falcon 02.wav",				SKILL_SOUND_SKILL_FALCON			},
	{	"wav\\Effects\\Skill\\Tempskron\\Falcon Attack 01.wav",			SKILL_SOUND_SKILL_FALCON_ATTACK1	},
	{	"wav\\Effects\\Skill\\Tempskron\\Falcon Attack 02.wav",			SKILL_SOUND_SKILL_FALCON_ATTACK2	},

	{	"wav\\Effects\\Skill\\Tempskron\\Avalanche 01.wav",				SKILL_SOUND_SKILL_AVALANCHE1		},
	{	"wav\\Effects\\Skill\\Tempskron\\Avalanche 02.wav",				SKILL_SOUND_SKILL_AVALANCHE2		},
	{	"wav\\Effects\\Skill\\Tempskron\\Avalanche 03.wav",				SKILL_SOUND_SKILL_AVALANCHE3		},

	{	"wav\\Effects\\Skill\\Tempskron\\Expansion 01.wav",				SKILL_SOUND_SKILL_EXPANSION1		},
	{	"wav\\Effects\\Skill\\Tempskron\\Expansion 02.wav",				SKILL_SOUND_SKILL_EXPANSION2		},

	{	"wav\\Effects\\Skill\\Tempskron\\RoZ 01.wav",					SKILL_SOUND_SKILL_RAGE_OF_ZECRAM1	},
	{	"wav\\Effects\\Skill\\Tempskron\\RoZ 02.wav",					SKILL_SOUND_SKILL_RAGE_OF_ZECRAM2	},
	{	"wav\\Effects\\Skill\\Tempskron\\RoZ 04.wav",					SKILL_SOUND_SKILL_RAGE_OF_ZECRAM3	},

	{	"wav\\Effects\\Skill\\Tempskron\\Roar 01.wav",					SKILL_SOUND_SKILL_ROAR1				},
	{	"wav\\Effects\\Skill\\Tempskron\\Roar 02.wav",					SKILL_SOUND_SKILL_ROAR2				},

	{	"wav\\Effects\\Skill\\Tempskron\\AofR 01.wav",					SKILL_SOUND_SKILL_ARROW_OF_RANGE	},

	///////////////////////////////// ����̿� ////////////////////////////////
	{	"wav\\Effects\\Skill\\Morion\\Casting_M.wav",					SKILL_SOUND_SKILL_CASTING_MAGICIAN	},
	{	"wav\\Effects\\Skill\\Morion\\Casting_P.wav",					SKILL_SOUND_SKILL_CASTING_PRIEST	},

	{	"wav\\Effects\\Skill\\Morion\\Agony 1.wav",						SKILL_SOUND_SKILL_AGONY				},
	{	"wav\\Effects\\Skill\\Morion\\Farina 1.wav",					SKILL_SOUND_SKILL_FARINA			},
	{	"wav\\Effects\\Skill\\Morion\\FireBall 1.wav",					SKILL_SOUND_SKILL_FIREBALL1			},
	{	"wav\\Effects\\Skill\\Morion\\FireBall 2.wav",					SKILL_SOUND_SKILL_FIREBALL2			},
	{	"wav\\Effects\\Skill\\Morion\\FireBolt 1.wav",					SKILL_SOUND_SKILL_FIREBOLT1			},
	{	"wav\\Effects\\Skill\\Morion\\FireBolt 2.wav",					SKILL_SOUND_SKILL_FIREBOLT2			},

	{	"wav\\Effects\\Skill\\Morion\\Healing 1.wav",					SKILL_SOUND_SKILL_HEALING			},
	{	"wav\\Effects\\Skill\\Morion\\HolyBody 1.wav",					SKILL_SOUND_SKILL_HOLYBODY			},
	{	"wav\\Effects\\Skill\\Morion\\HolyBolt 1.wav",					SKILL_SOUND_SKILL_HOLYBOLT			},
	{	"wav\\Effects\\Skill\\Morion\\HolyMind 1.wav",					SKILL_SOUND_SKILL_HOLYMIND			},
	{	"wav\\Effects\\Skill\\Morion\\MultiSpark 1.wav",				SKILL_SOUND_SKILL_MULTISPARK		},
	{	"wav\\Effects\\Skill\\Morion\\ShieldSpake 1.wav",				SKILL_SOUND_SKILL_SHIELDSTRIKE		},
	{	"wav\\Effects\\Skill\\Morion\\SwordBlast 1.wav",				SKILL_SOUND_SKILL_SWORDBLAST1		},
	{	"wav\\Effects\\Skill\\Morion\\SwordBlast 2.wav",				SKILL_SOUND_SKILL_SWORDBLAST2		},
	{	"wav\\Effects\\Skill\\Morion\\VigorSpear 1.wav",				SKILL_SOUND_SKILL_VIGORSPEAR		},
	{	"wav\\Effects\\Skill\\Morion\\Zenith 1.wav",					SKILL_SOUND_SKILL_ZENITH			},

	{	"wav\\Effects\\Skill\\Morion\\HolyValor 1.wav",					SKILL_SOUND_SKILL_HOLY_VALOR1		},
	{	"wav\\Effects\\Skill\\Morion\\HolyValor 3.wav",					SKILL_SOUND_SKILL_HOLY_VALOR3		},

	{	"wav\\Effects\\Skill\\Morion\\Brandish 1.wav",					SKILL_SOUND_SKILL_BLANDISH1			},
	{	"wav\\Effects\\Skill\\Morion\\Brandish 2.wav",					SKILL_SOUND_SKILL_BLANDISH2			},

	{	"wav\\Effects\\Skill\\Morion\\Piercing 2.wav",					SKILL_SOUND_SKILL_PIERCING			},

	{	"wav\\Effects\\Skill\\Morion\\DrasticSpirit 1.wav",				SKILL_SOUND_SKILL_DRASTICSPIRIT1	},
	{	"wav\\Effects\\Skill\\Morion\\DrasticSpirit 3.wav",				SKILL_SOUND_SKILL_DRASTICSPIRIT3	},

	{	"wav\\Effects\\Skill\\Morion\\Windy 1.wav",						SKILL_SOUND_SKILL_WINDY1			},
	{	"wav\\Effects\\Skill\\Morion\\Windy 3.wav",						SKILL_SOUND_SKILL_WINDY3			},

	{	"wav\\Effects\\Skill\\Morion\\TwistJavelin.wav",				SKILL_SOUND_SKILL_TWISTJAVELIN		},

	{	"wav\\Effects\\Skill\\Morion\\SoulSucker 2.wav",				SKILL_SOUND_SKILL_SOULSUCKER2		},
	{	"wav\\Effects\\Skill\\Morion\\SoulSucker 3.wav",				SKILL_SOUND_SKILL_SOULSUCKER3		},
	{	"wav\\Effects\\Skill\\Morion\\SoulSucker 4.wav",				SKILL_SOUND_SKILL_SOULSUCKER4		},
	{	"wav\\Effects\\Skill\\Morion\\FireJavelin 1.wav",				SKILL_SOUND_SKILL_FIREJAVELIN		},


	{	"wav\\Effects\\Skill\\Morion\\DivineLightning 1.wav",			SKILL_SOUND_SKILL_DIVINELIGHTNING1	},
	{	"wav\\Effects\\Skill\\Morion\\DivineLightning 2.wav",			SKILL_SOUND_SKILL_DIVINELIGHTNING2	},
	{	"wav\\Effects\\Skill\\Morion\\DivineLightning 3.wav",			SKILL_SOUND_SKILL_DIVINELIGHTNING3	},

	{	"wav\\Effects\\Skill\\Morion\\HolyReflection 1.wav",			SKILL_SOUND_SKILL_HOLYREFLECTION1	},
	{	"wav\\Effects\\Skill\\Morion\\HolyReflection 2.wav",			SKILL_SOUND_SKILL_HOLYREFLECTION2	},

	{	"wav\\Effects\\Skill\\Morion\\GrandHealing 1.wav",				SKILL_SOUND_SKILL_GRANDHEALING		},


	{	"wav\\Effects\\Skill\\Morion\\Watornado 1.wav",					SKILL_SOUND_SKILL_WATORNADO1		},
	{	"wav\\Effects\\Skill\\Morion\\Watornado 2.wav",					SKILL_SOUND_SKILL_WATORNADO2		},


	{	"wav\\Effects\\Skill\\Morion\\EnchantWpn_add_C 1.wav",			SKILL_SOUND_SKILL_ENCHANTWEAPON_ICE1},
	{	"wav\\Effects\\Skill\\Morion\\EnchantWpn_add_C 2.wav",			SKILL_SOUND_SKILL_ENCHANTWEAPON_ICE2},

	{	"wav\\Effects\\Skill\\Morion\\EnchantWpn_add_F 1.wav",			SKILL_SOUND_SKILL_ENCHANTWEAPON_FIRE1			},
	{	"wav\\Effects\\Skill\\Morion\\EnchantWpn_add_F 2.wav",			SKILL_SOUND_SKILL_ENCHANTWEAPON_FIRE2			},

	{	"wav\\Effects\\Skill\\Morion\\EnchantWpn_add_L 1.wav",			SKILL_SOUND_SKILL_ENCHANTWEAPON_LIGHTNING1		},
	{	"wav\\Effects\\Skill\\Morion\\EnchantWpn_add_L 2.wav",			SKILL_SOUND_SKILL_ENCHANTWEAPON_LIGHTNING2		},

	{	"wav\\Effects\\Skill\\Morion\\EnchantWpn_cast.wav",				SKILL_SOUND_SKILL_ENCHANTWEAPON_CAST			},

	{	"wav\\Effects\\Skill\\Morion\\EnchantWpn_magic_L 1.wav",		SKILL_SOUND_SKILL_ENCHANTWEAPON_MAGIC_LIGHTNING1},
	{	"wav\\Effects\\Skill\\Morion\\EnchantWpn_magic_L 2.wav",		SKILL_SOUND_SKILL_ENCHANTWEAPON_MAGIC_LIGHTNING2},

	{	"wav\\Effects\\Skill\\Morion\\EnchantWpn_magic_C 1.wav",		SKILL_SOUND_SKILL_ENCHANTWEAPON_MAGIC_ICE1		},
	{	"wav\\Effects\\Skill\\Morion\\EnchantWpn_magic_C 2.wav",		SKILL_SOUND_SKILL_ENCHANTWEAPON_MAGIC_ICE2		},


	{	"wav\\Effects\\Skill\\Morion\\DeathRay 1.wav",					SKILL_SOUND_SKILL_DEATHRAY			},


	///////////////////////////////////// 3�� ��ų /////////////////////////////////

	{	"wav\\Effects\\Skill\\Tempskron\\AvengingCrash 01.wav",			SKILL_SOUND_SKILL_AVANGING_CRASH	},
	{	"wav\\Effects\\Skill\\Tempskron\\ElementalShot 01.wav",			SKILL_SOUND_SKILL_ELEMENTAL_SHOT	},
	{	"wav\\Effects\\Skill\\Tempskron\\BombShot 01.wav",				SKILL_SOUND_SKILL_BOMB_SHOT1		},
	{	"wav\\Effects\\Skill\\Tempskron\\BombShot 02.wav",				SKILL_SOUND_SKILL_BOMB_SHOT2		},
	{	"wav\\Effects\\Skill\\Tempskron\\BoneCrash 01.wav",				SKILL_SOUND_SKILL_BONE_CRASH1		},
	{	"wav\\Effects\\Skill\\Tempskron\\ChainLance 01.wav",			SKILL_SOUND_SKILL_CHAIN_LANCE1		},
	{	"wav\\Effects\\Skill\\Tempskron\\ChainLance 02.wav",			SKILL_SOUND_SKILL_CHAIN_LANCE2		},
	{	"wav\\Effects\\Skill\\Tempskron\\ChainLance 03.wav",			SKILL_SOUND_SKILL_CHAIN_LANCE3		},
	{	"wav\\Effects\\Skill\\Tempskron\\Concentration 01.wav",			SKILL_SOUND_SKILL_CONCENTRATION1	},
	{	"wav\\Effects\\Skill\\Tempskron\\Concentration 02.wav",			SKILL_SOUND_SKILL_CONCENTRATION2	},
	{	"wav\\Effects\\Skill\\Tempskron\\GoldFalcon 02.wav",			SKILL_SOUND_SKILL_GOLDEN_FALCON		},
	{	"wav\\Effects\\Skill\\Tempskron\\MetalArmor 01.wav",			SKILL_SOUND_SKILL_METAL_ARMOR		},
	{	"wav\\Effects\\Skill\\Tempskron\\Perforation 01.wav",			SKILL_SOUND_SKILL_PERFORATION		},
	{	"wav\\Effects\\Skill\\Tempskron\\SparkShield 02.wav",			SKILL_SOUND_SKILL_SPARK_SHIELD		},
	{	"wav\\Effects\\Skill\\Tempskron\\SwiftAxe 01.wav",				SKILL_SOUND_SKILL_SWIFT_AXE1		},
	{	"wav\\Effects\\Skill\\Tempskron\\SwiftAxe 02.wav",				SKILL_SOUND_SKILL_SWIFT_AXE2		},
	{	"wav\\Effects\\Skill\\Tempskron\\VenomSpear 01.wav",			SKILL_SOUND_SKILL_VENOM_SPEAR1		},
	{	"wav\\Effects\\Skill\\Tempskron\\VenomSpear 02.wav",			SKILL_SOUND_SKILL_VENOM_SPEAR2		},
	{	"wav\\Effects\\Skill\\Tempskron\\vanish 01.wav",				SKILL_SOUND_SKILL_VANISH1			},
	{	"wav\\Effects\\Skill\\Tempskron\\vanish 02.wav",				SKILL_SOUND_SKILL_VANISH2			},



	{	"wav\\Effects\\Skill\\Morion\\DancingSword 1.wav",				SKILL_SOUND_SKILL_DANCING_SWORD		},
	{	"wav\\Effects\\Skill\\Morion\\DancingSword_atk_1.wav",			SKILL_SOUND_SKILL_DANCING_SWORD_ATK1},
	{	"wav\\Effects\\Skill\\Morion\\DancingSword_atk_2.wav",			SKILL_SOUND_SKILL_DANCING_SWORD_ATK2},
	{	"wav\\Effects\\Skill\\Morion\\Diastrophism 2.wav",				SKILL_SOUND_SKILL_DIASTROPHISM		},
	{	"wav\\Effects\\Skill\\Morion\\DivineInhalation 1.wav",			SKILL_SOUND_SKILL_DIVINE_INHALATION	},
	{	"wav\\Effects\\Skill\\Morion\\EnergyShield 1.wav",				SKILL_SOUND_SKILL_ENERGY_SHIELD		},
	{	"wav\\Effects\\Skill\\Morion\\Extinct 1.wav",					SKILL_SOUND_SKILL_EXTINTION			},
	{	"wav\\Effects\\Skill\\Morion\\FlameBrandish 2.wav",				SKILL_SOUND_SKILL_FLAME_BRANDISH	},
	{	"wav\\Effects\\Skill\\Morion\\GrandCross 2.wav",				SKILL_SOUND_SKILL_GRAND_CROSS		},
	{	"wav\\Effects\\Skill\\Morion\\Holy Incantation 1.wav",			SKILL_SOUND_SKILL_HOLY_INCANTATION	},
	{	"wav\\Effects\\Skill\\Morion\\LightningJavelin 1.wav",			SKILL_SOUND_SKILL_LIGHTNING_JAVELIN1},
	{	"wav\\Effects\\Skill\\Morion\\LightningJavelin 2.wav",			SKILL_SOUND_SKILL_LIGHTNING_JAVELIN2},
	{	"wav\\Effects\\Skill\\Morion\\Resurrection 2.wav",				SKILL_SOUND_SKILL_RESURRECTION		},
	{	"wav\\Effects\\Skill\\Morion\\SpiritElemental 1.wav",			SKILL_SOUND_SKILL_SPIRIT_ELEMENTAL	},
	{	"wav\\Effects\\Skill\\Morion\\SplitJavelin 1.wav",				SKILL_SOUND_SKILL_SPLIT_JAVELIN1	},
	{	"wav\\Effects\\Skill\\Morion\\SplitJavelin 2.wav",				SKILL_SOUND_SKILL_SPLIT_JAVELIN2	},
	{	"wav\\Effects\\Skill\\Morion\\StormJavelin 1.wav",				SKILL_SOUND_SKILL_STORM_JAVELIN1	},
	{	"wav\\Effects\\Skill\\Morion\\StormJavelin 2.wav",				SKILL_SOUND_SKILL_STORM_JAVELIN2	},
	{	"wav\\Effects\\Skill\\Morion\\TriumphofValhalla 1.wav",			SKILL_SOUND_SKILL_TRIUMPH_OF_VALHALLA1	},
	{	"wav\\Effects\\Skill\\Morion\\TriumphofValhalla 3.wav",			SKILL_SOUND_SKILL_TRIUMPH_OF_VALHALLA2  },
	{	"wav\\Effects\\Skill\\Morion\\VigorBall 1.wav",					SKILL_SOUND_SKILL_VIGOR_BALL1		},
	{	"wav\\Effects\\Skill\\Morion\\VigorBall 2.wav",					SKILL_SOUND_SKILL_VIGOR_BALL2		},
	{	"wav\\Effects\\Skill\\Morion\\VirtualLife 1.wav",				SKILL_SOUND_SKILL_VIRTUAL_LIFE		},

	{	"wav\\Effects\\Skill\\Tempskron\\AssassinEye 01.wav",			SKILL_SOUND_SKILL_ASSASSIN_EYE		},
	{	"wav\\Effects\\Skill\\Tempskron\\Berserker 01.wav",				SKILL_SOUND_SKILL_BERSERKER			},
	{	"wav\\Effects\\Skill\\Tempskron\\Charging 01.wav",				SKILL_SOUND_SKILL_CHARGING			},
	{	"wav\\Effects\\Skill\\Tempskron\\ChargingStrike 03.wav",		SKILL_SOUND_SKILL_CHARGING_STRIKE	},
	{	"wav\\Effects\\Skill\\Tempskron\\Compulsion 01.wav",			SKILL_SOUND_SKILL_COMPULSION1		},
	{	"wav\\Effects\\Skill\\Tempskron\\Compulsion 05.wav",			SKILL_SOUND_SKILL_COMPULSION2		},
	{	"wav\\Effects\\Skill\\Tempskron\\Compulsion 06.wav",			SKILL_SOUND_SKILL_COMPULSION3		},
	{	"wav\\Effects\\Skill\\Tempskron\\CycloneStrike 01.wav",			SKILL_SOUND_SKILL_CYCLONE_STRIKE	},
	{	"wav\\Effects\\Skill\\Tempskron\\ForceOfNature 01.wav",			SKILL_SOUND_SKILL_FORCE_OF_NATURE	},
	{	"wav\\Effects\\Skill\\Tempskron\\GodsBless 01.wav",				SKILL_SOUND_SKILL_GODS_BLESS		},
	{	"wav\\Effects\\Skill\\Tempskron\\GodlyShield 01.wav",			SKILL_SOUND_SKILL_GODLY_SHIELD		},
	{	"wav\\Effects\\Skill\\Tempskron\\impulsion 02.wav",				SKILL_SOUND_SKILL_IMPULSION			},
	{	"wav\\Effects\\Skill\\Tempskron\\MetalGolem 01.wav",			SKILL_SOUND_SKILL_METAL_GOLEM		},
	{	"wav\\Effects\\Skill\\Tempskron\\PhoenixShot 01.wav",			SKILL_SOUND_SKILL_PHOENIX_SHOT		},
	{	"wav\\Effects\\Skill\\Tempskron\\ReCallWolverin 01.wav",		SKILL_SOUND_SKILL_RECALL_WOLVERIN	},
	{	"wav\\Effects\\Skill\\Tempskron\\ShadowStrike 01.wav",			SKILL_SOUND_SKILL_SHADOW_STRIKE1	},
	{	"wav\\Effects\\Skill\\Tempskron\\ShadowStrike 02.wav",			SKILL_SOUND_SKILL_SHADOW_STRIKE2	},
	{	"wav\\Effects\\Skill\\Tempskron\\ShadowStrike 03.wav",			SKILL_SOUND_SKILL_SHADOW_STRIKE3	},
	{	"wav\\Effects\\Skill\\Tempskron\\ShadowStrikeFinish 01.wav",	SKILL_SOUND_SKILL_SHADOW_STRIKE4	},
	{	"wav\\Effects\\Skill\\Tempskron\\vague 01.wav",					SKILL_SOUND_SKILL_VAGUE				},

	{	"wav\\Effects\\Skill\\Morion\\ChainLightning 01.wav",			SKILL_SOUND_SKILL_CHAIN_LIGHTNING1	},
	{	"wav\\Effects\\Skill\\Morion\\ChainLightning 02.wav",			SKILL_SOUND_SKILL_CHAIN_LIGHTNING2	},
	{	"wav\\Effects\\Skill\\Morion\\Distortion 01.wav",				SKILL_SOUND_SKILL_DISTORTION		},
	{	"wav\\Effects\\Skill\\Morion\\DIvinePiercing 07.wav",			SKILL_SOUND_SKILL_DVINE_PIERCING	},
	{	"wav\\Effects\\Skill\\Morion\\eXtremeRage 01.wav",				SKILL_SOUND_SKILL_EXTREM_RAGE1		},
	{	"wav\\Effects\\Skill\\Morion\\eXtremeRage 02.wav",				SKILL_SOUND_SKILL_EXTREM_RAGE2		},
	{	"wav\\Effects\\Skill\\Morion\\eXtremeRage 03.wav",				SKILL_SOUND_SKILL_EXTREM_RAGE3		},
	{	"wav\\Effects\\Skill\\Morion\\FireElemental 01.wav",			SKILL_SOUND_SKILL_FIRE_ELEMENTAL	},
	{	"wav\\Effects\\Skill\\Morion\\FlameWave 01.wav",				SKILL_SOUND_SKILL_FLAME_WAVE1		},
	{	"wav\\Effects\\Skill\\Morion\\FlameWave 02.wav",				SKILL_SOUND_SKILL_FLAME_WAVE2		},
	{	"wav\\Effects\\Skill\\Morion\\FlameWaveA 01.wav",				SKILL_SOUND_SKILL_FLAME_WAVE3		},
	{	"wav\\Effects\\Skill\\Morion\\FrostJavelin 01.wav",				SKILL_SOUND_SKILL_FROST_JAVELIN		},
	{	"wav\\Effects\\Skill\\Morion\\GlacialSpike 01.wav",				SKILL_SOUND_SKILL_GLACIAL_SPIKE1	},
	{	"wav\\Effects\\Skill\\Morion\\GlacialSpike 02.wav",				SKILL_SOUND_SKILL_GLACIAL_SPIKE2	},
	{	"wav\\Effects\\Skill\\Morion\\HallOfValhalla 01.wav",			SKILL_SOUND_SKILL_HALL_OF_VALHALLA	},
	{	"wav\\Effects\\Skill\\Morion\\Meteo 01.wav",					SKILL_SOUND_SKILL_METEO1			},
	{	"wav\\Effects\\Skill\\Morion\\Meteo 02.wav",					SKILL_SOUND_SKILL_METEO2			},
	{	"wav\\Effects\\Skill\\Morion\\Meteo 03.wav",					SKILL_SOUND_SKILL_METEO3			},
	{	"wav\\Effects\\Skill\\Morion\\Muspell 01.wav",					SKILL_SOUND_SKILL_MUSPELL1			},
	{	"wav\\Effects\\Skill\\Morion\\Muspell 02.wav",					SKILL_SOUND_SKILL_MUSPELL2			},
	{	"wav\\Effects\\Skill\\Morion\\RegenField 01.wav",				SKILL_SOUND_SKILL_REGEN_FIELD1		},
	{	"wav\\Effects\\Skill\\Morion\\RegenField 02.wav",				SKILL_SOUND_SKILL_REGEN_FIELD2		},
	{	"wav\\Effects\\Skill\\Morion\\SwordofJustice 01.wav",			SKILL_SOUND_SKILL_SWORD_OF_JUSTICE	},
	{	"wav\\Effects\\Skill\\Morion\\Vengeance 01.wav",				SKILL_SOUND_SKILL_VENGEANCE1		},
	{	"wav\\Effects\\Skill\\Morion\\Vengeance 02.wav",				SKILL_SOUND_SKILL_VENGEANCE2		},

	// �̿�

	{	"wav\\Effects\\Skill\\Tempskron\\Stinger 01.wav",				SKILL_SOUND_SKILL_STRINGER			},
	{	"wav\\Effects\\Skill\\Tempskron\\RunningHit 01.wav",			SKILL_SOUND_SKILL_RUNNING_HIT		},
	{	"wav\\Effects\\Skill\\Tempskron\\Wisp 01.wav",					SKILL_SOUND_SKILL_WISP				},
	{	"wav\\Effects\\Skill\\Tempskron\\VenomThorn 01.wav",			SKILL_SOUND_SKILL_VENOM_THORN		},
	{	"wav\\Effects\\Skill\\Tempskron\\Alas 01.wav",					SKILL_SOUND_SKILL_ALAS				},
	{	"wav\\Effects\\Skill\\Tempskron\\SoulShork 01.wav",				SKILL_SOUND_SKILL_SOUL_SHOCK		},
	{	"wav\\Effects\\Skill\\Tempskron\\SoreSword 01.wav",				SKILL_SOUND_SKILL_SORE_SWORD		},
	{	"wav\\Effects\\Skill\\Tempskron\\BeatUp 01.wav",				SKILL_SOUND_SKILL_BEAT_UP			},
	{	"wav\\Effects\\Skill\\Tempskron\\Infes 01.wav",					SKILL_SOUND_SKILL_INPES				},
	{	"wav\\Effects\\Skill\\Tempskron\\Blind 01.wav",					SKILL_SOUND_SKILL_BLIND				},
	{	"wav\\Effects\\Skill\\Tempskron\\FrostWind 01.wav",				SKILL_SOUND_SKILL_FROST_WIND		},
	{	"wav\\Effects\\Skill\\Tempskron\\Polluted 01.wav",				SKILL_SOUND_SKILL_POLLUTED			},
	{	"wav\\Effects\\Skill\\Tempskron\\FastingShadow 01.wav",			SKILL_SOUND_SKILL_PASTING_SHADOW	},
	{	"wav\\Effects\\Skill\\Tempskron\\ShadowBomb 01.wav",			SKILL_SOUND_SKILL_SHADOW_BOMB		},
	{	"wav\\Effects\\Skill\\Tempskron\\RisingSlash 01.wav",			SKILL_SOUND_SKILL_RISING_SHASH		},
	{	"wav\\Effects\\Skill\\Tempskron\\ViolenceStep 01.wav",			SKILL_SOUND_SKILL_VIOLENCE_STAB		},
	{	"wav\\Effects\\Skill\\Tempskron\\Storm 01.wav",					SKILL_SOUND_SKILL_STORM				},

	// ����
	{	"wav\\Effects\\Skill\\Morion\\Darkbolt01.wav",					SKILL_SOUND_SKILL_DARK_BOLT			},
	{	"wav\\Effects\\Skill\\Morion\\Darkbolt02.wav",					SKILL_SOUND_SKILL_DARK_BOLT_HIT		},
	{	"wav\\Effects\\Skill\\Morion\\Darkwave01.wav",					SKILL_SOUND_SKILL_DARK_WAVE			},
	{	"wav\\Effects\\Skill\\Morion\\Darkwave02.wav",					SKILL_SOUND_SKILL_DARK_WAVE_HIT		},
	{	"wav\\Effects\\Skill\\Morion\\Curselazy01.wav",					SKILL_SOUND_SKILL_CURSE_LAZY1		},
	{	"wav\\Effects\\Skill\\Morion\\Curselazy02.wav",					SKILL_SOUND_SKILL_CURSE_LAZY2		},
	{	"wav\\Effects\\Skill\\Morion\\SFlare01.wav",					SKILL_SOUND_SKILL_SPIRITUAL_FLARE1	},
	{	"wav\\Effects\\Skill\\Morion\\SFlare02.wav",					SKILL_SOUND_SKILL_SPIRITUAL_FLARE2	},
	{	"wav\\Effects\\Skill\\Morion\\SManacle01.wav",					SKILL_SOUND_SKILL_SPIRITUAL_MANACLE1},
	{	"wav\\Effects\\Skill\\Morion\\SManacle02.wav",					SKILL_SOUND_SKILL_SPIRITUAL_MANACLE2},
	{	"wav\\Effects\\Skill\\Morion\\CHunt01.wav",						SKILL_SOUND_SKILL_CHASING_HUNT1		},
	{	"wav\\Effects\\Skill\\Morion\\CHunt02.wav",						SKILL_SOUND_SKILL_CHASING_HUNT2		},
	{	"wav\\Effects\\Skill\\Morion\\AMichal01.wav",					SKILL_SOUND_SKILL_SKILL_ADVENT_MIGAL1},
	{	"wav\\Effects\\Skill\\Morion\\AMichal02.wav",					SKILL_SOUND_SKILL_SKILL_ADVENT_MIGAL2},
	{	"wav\\Effects\\Skill\\Morion\\Rainmaker01.wav",					SKILL_SOUND_SKILL_SKILL_RAIN_MAKER1	},
	{	"wav\\Effects\\Skill\\Morion\\Rainmaker02.wav",					SKILL_SOUND_SKILL_SKILL_RAIN_MAKER2	},
	{	"wav\\Effects\\Skill\\Morion\\LOGhost01.wav",					SKILL_SOUND_SKILL_LAND_OF_GHOST1	},
	{	"wav\\Effects\\Skill\\Morion\\LOGhost02.wav",					SKILL_SOUND_SKILL_LAND_OF_GHOST2	},
	{	"wav\\Effects\\Skill\\Morion\\Haunt01.wav",						SKILL_SOUND_SKILL_HAUNT1			},
	{	"wav\\Effects\\Skill\\Morion\\Haunt02.wav",						SKILL_SOUND_SKILL_HAUNT2			},
	{	"wav\\Effects\\Skill\\Morion\\Scratch01.wav",					SKILL_SOUND_SKILL_SCRATCH1			},
	{	"wav\\Effects\\Skill\\Morion\\Scratch02.wav",					SKILL_SOUND_SKILL_SCRATCH2			},
	{	"wav\\Effects\\Skill\\Morion\\BloodyKinght01.wav",				SKILL_SOUND_SKILL_RECALL_BLOODYKNIGHT1	},
	{	"wav\\Effects\\Skill\\Morion\\BloodyKinght02.wav",				SKILL_SOUND_SKILL_RECALL_BLOODYKNIGHT2	},
	{	"wav\\Effects\\Skill\\Morion\\Judgement01.wav",					SKILL_SOUND_SKILL_JUDGEMENT1		},
	{	"wav\\Effects\\Skill\\Morion\\Judgement02.wav",					SKILL_SOUND_SKILL_JUDGEMENT2		},
	{	"wav\\Effects\\Skill\\Morion\\AMidranda01.wav",					SKILL_SOUND_SKILL_ADVENT_MIDRANDA1	},
	{	"wav\\Effects\\Skill\\Morion\\AMidranda02.wav",					SKILL_SOUND_SKILL_ADVENT_MIDRANDA2	},
	{	"wav\\Effects\\Skill\\Morion\\MOPray01.wav",					SKILL_SOUND_SKILL_MOURNING_OF_PRAY1	},
	{	"wav\\Effects\\Skill\\Morion\\MOPray02.wav",					SKILL_SOUND_SKILL_MOURNING_OF_PRAY2	},
	{	"wav\\Effects\\Skill\\Morion\\Creed01.wav",						SKILL_SOUND_SKILL_CREED				},
	{	"wav\\Effects\\Skill\\Morion\\PODeity01.wav",					SKILL_SOUND_SKILL_PRESS_OF_DEITY	},
	{	"wav\\Effects\\Skill\\Morion\\GNail01.wav",						SKILL_SOUND_SKILL_CHOSTY_NAIL1		},
	{	"wav\\Effects\\Skill\\Morion\\GNail02.wav",						SKILL_SOUND_SKILL_CHOSTY_NAIL2		},

	{	0,0 }
};

int	InitSoundEffect(HWND hWnd)
{
	int	cnt;
	HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;
	char	szFindPath[64];

	LoadSoundNum = 0;

	for (cnt = 0; cnt < NUM_SOUNDS; cnt++)
		sangJuWav_F[cnt] = 1;

	while (1)
	{
		if (sangJuWav2[LoadSoundNum] == NULL)
			break;
		lstrcpy(sangJuWav[LoadSoundNum], sangJuWav2[LoadSoundNum]);
		LoadSoundNum++;
	}

	snEffectCnt = 0;

	for (cnt = 0; cnt < snFIND_EFFECT_MAX; cnt++)
	{
		lstrcpy(szFindPath, snFindEffects[cnt].lpStringCode);
		lstrcat(szFindPath, "*.wav");

		hFindHandle = FindFirstFile(szFindPath, &fd);
		if (hFindHandle != INVALID_HANDLE_VALUE)
		{
			while (1)
			{
				lstrcpy(sangJuWav[LoadSoundNum], snFindEffects[cnt].lpStringCode);
				lstrcat(sangJuWav[LoadSoundNum], fd.cFileName);

				if (snFindEffects[cnt].CharSoundCode >= 0x1000)
					sangJuWav_F[LoadSoundNum] = 0;

				snEffect[snEffectCnt].RealSoundNum = LoadSoundNum + 1;
				snEffect[snEffectCnt].CharSoundCode = snFindEffects[cnt].CharSoundCode;
				snEffect[snEffectCnt].MotionState = FindMotionState(fd.cFileName);

				snEffectCnt++;
				LoadSoundNum++;

				if (FindNextFile(hFindHandle, &fd) == FALSE)
					break;
				if (snEffectCnt >= snEFFECT_MAX)
					break;
			}
		}
		else
			snEffectCnt = snEffectCnt;

		FindClose(hFindHandle);
	}

	snEffectWeaponCnt = 0;

	lstrcpy(szFindPath, szSndWeaponPath);
	lstrcat(szFindPath, "*.wav");

	hFindHandle = FindFirstFile(szFindPath, &fd);
	if (hFindHandle != INVALID_HANDLE_VALUE)
	{
		while (1)
		{
			lstrcpy(sangJuWav[LoadSoundNum], szSndWeaponPath);
			lstrcat(sangJuWav[LoadSoundNum], fd.cFileName);

			snEffectWeapon[snEffectWeaponCnt].RealSoundNum = LoadSoundNum + 1;
			snEffectWeapon[snEffectWeaponCnt].WeaponState = FindWeaponState(fd.cFileName);

			snEffectWeaponCnt++;
			LoadSoundNum++;

			if (FindNextFile(hFindHandle, &fd) == FALSE)
				break;
			if (snEffectWeaponCnt >= snEFFECT_MAX)
				break;

		}
		FindClose(hFindHandle);
	}

	sinSoundNum = LoadSoundNum + 1;
	cnt = 0;
	while (sinSoundWav[cnt] != NULL)
	{
		lstrcpy(sangJuWav[LoadSoundNum], sinSoundWav[cnt++]);
		LoadSoundNum++;
	}

	esSoundNum = LoadSoundNum + 1;
	cnt = 0;
	while (esSoundWav[cnt] != NULL)
	{
		lstrcpy(sangJuWav[LoadSoundNum], esSoundWav[cnt++]);
		LoadSoundNum++;
	}

	SkillSoundNum = LoadSoundNum + 1;
	cnt = 0;
	while (SkillSoundWav[cnt].szFile != NULL)
	{
		lstrcpy(sangJuWav[LoadSoundNum], SkillSoundWav[cnt++].szFile);
		LoadSoundNum++;
	}

	AmbientSoundNum = esSoundNum + AMBIENT_SOUND_NUM;
	AmbientSoundNum2 = esSoundNum + AMBIENT_SOUND_NUM2;
	ContinueSoundNum = esSoundNum + CONTINUE_SOUND_NUM;

	sangJuWav[LoadSoundNum][0] = 0;

	InitDX_Wav2(hWnd);

	return TRUE;
}
int CloseSoundEffect()
{
	TermDX_Wav2();

	return TRUE;
}
int	sinPlaySound(int Num, int Volume)
{
	PlayWav2(sinSoundNum + Num, 0, Volume, 2205);

	return TRUE;
}
int	esPlaySound(int Num, int Volume)
{
	PlayWav2(esSoundNum + Num, 0, Volume, 2205);

	return TRUE;
}
int	esPlaySound(int Num, int Volume, int SampleRate)
{

	PlayWav2(esSoundNum + Num, 0, Volume, SampleRate);

	return TRUE;
}


int	esObjectSoundNum = 0;
int esObjectVolume = 0;


int esPlayObjectSound(int Num, int x, int y, int z)
{
	int vol;
	int OldSound;
	int SoundNum;

	if (Num < 0)
	{
		if (esObjectSoundNum)
		{
			StopWav(esObjectSoundNum + esSoundNum);
			esObjectSoundNum = 0;
		}
		return TRUE;
	}

	SoundNum = esSoundNum + Num;
	vol = GetDistVolume(x, y, z) + 100;
	if (vol > 400)
		vol = 400;

	OldSound = esObjectSoundNum;

	if (Num == esObjectSoundNum && vol == esObjectVolume)
		return TRUE;

	if (vol)
	{
		if (esObjectSoundNum == Num)
			PlayWav_VolChange(SoundNum, vol);
		else
		{
			PlayWav2(SoundNum, 1, vol, 2205);
			esObjectSoundNum = Num;
			if (OldSound)
				StopWav(OldSound + Num);
		}
	}
	else
	{
		if (OldSound)
			StopWav(OldSound + Num);
	}

	esObjectVolume = vol;

	return TRUE;
}
char *szAmbientSound2[] =
{
	"wav\\Ambient\\stone-mill.wav",				// 0 

	"wav\\Ambient\\dungeon_pumping_b.wav",		// 1
	"wav\\Ambient\\dungeon_pumping_l.wav",		// 2	���� ����
	"wav\\Ambient\\dungeon_spin_b.wav",			// 3
	"wav\\Ambient\\lake 1.wav",					// 4 ���� ��
	"wav\\Ambient\\mystic 1.wav",				// 5 �ź�
	"wav\\Ambient\\mystic 2.wav",				// 6 �ź� 2
	"wav\\Ambient\\ship_swaing_l.wav",			// 7	�ڷ���Ʈ ��
	"wav\\Ambient\\stream.wav",					// 8	���� ū ���Ҹ�
	"wav\\Ambient\\town_bell 1.wav",			// 9	��
	"wav\\Ambient\\town_bell 2.wav",			// 10   �� 2
	"wav\\Ambient\\town_spin_b.wav",			// 11
	"wav\\Ambient\\town_spin_l.wav",			// 12	ū �ٶ�����
	"wav\\Ambient\\waterfall.wav",				// 13   ����
	"wav\\Ambient\\stone-mill2.wav",			// 14	���� �������� �Ҹ�

	"wav\\Ambient\\watermill 1.wav",			// 15	������� �Ҹ�
	"wav\\Ambient\\windmill 1.wav",				// 16	ǳ��
	"wav\\Ambient\\windmill 2.wav",				// 17	ǳ��	- ����
	"wav\\Ambient\\windmill 3.wav",				// 18	ǳ��	- �ʵ� �Ϲ�
	"wav\\Ambient\\windmill 4.wav",				// 19	ǳ��	- ���� ǳ��
	"wav\\Ambient\\owl 1.wav",					// 20	�ξ�

	"wav\\Ambient\\dungeon_big-bolt 1.wav",		// 21	
	"wav\\Ambient\\dungeon_stonepole.wav",		// 22	
	"wav\\Ambient\\zombiemill 1.wav",			// 23	���� ����
	"wav\\Ambient\\dungeon_weight.wav",			// 24	��
	"wav\\Ambient\\dungeon_device_side.wav",	// 25	���ư��� Į
	"wav\\Ambient\\dungeon_device_axe.wav",		// 26	
	"wav\\Ambient\\dungeon_cage 1.wav",			// 27	����

	0
};

char *szSodSound[] =
{
	"wav\\Sod\\start.wav",				// 0	Start
	"wav\\Sod\\round1.wav",				// 1	1
	"wav\\Sod\\round2.wav",				// 2	1
	"wav\\Sod\\round3.wav",				// 3	1
	"wav\\Sod\\round4.wav",				// 4	1
	"wav\\Sod\\round5.wav",				// 5	1
	"wav\\Sod\\round6.wav",				// 6	1
	"wav\\Sod\\round7.wav",				// 7	1
	"wav\\Sod\\round8.wav",				// 8	1
	"wav\\Sod\\round9.wav",				// 9	1
	"wav\\Sod\\stage.wav",				// 10	Stage
	"wav\\Sod\\complete.wav",			// 11	complete
	"wav\\Sod\\fail.wav",				// 12	fail.wav
	"wav\\Sod\\congratulation.wav",		// 13	congratulation


	"wav\\Sod\\BGM\\Stage_Complete.wav",//	14
	"wav\\Sod\\BGM\\Stage_Fail.wav",	//	15
	"wav\\Sod\\BGM\\Ending.wav",		//	16

	0
};

#define	CONT_SOUND_MAX	8
#define	CONT_SOUND_MASK	7

int	ContSoundBuff[CONT_SOUND_MAX] = { -1, };
int	ContSoundPush = 0;
int	ContSoundPop = 0;
int	ContSoundNum = -1;

static int	LastVolumeDist = 0xFFFF;
static int  AmbientFlag = 0;

//������ ���� �Ÿ��� �ʱ�ȭ�� ���� ��ȯ
int ResetLastVolumeDist()
{
	int cnt;

	cnt = LastVolumeDist;
	LastVolumeDist = 0xFFFF;
	AmbientFlag = 0;

	return cnt;
}


//�Ÿ��� ���� ������ ���� ( �ݰ��� ���� )
int GetDistVolume2(int dx, int dy, int dz, int round)
{
	int vol;
	int x, y, z;

	x = (lpCurPlayer->pX - dx) >> FLOATNS;
	y = (lpCurPlayer->pY - dy) >> FLOATNS;
	z = (lpCurPlayer->pZ - dz) >> FLOATNS;

	if (abs(x) < 256 * fONE && abs(y) < 256 * fONE && abs(z) < 256 * fONE)
	{
		vol = x * x + z * z + y * y - round * round;
		vol /= 1100;
	}
	else
		vol = 0xFFFF;

	if (LastVolumeDist > vol)
		LastVolumeDist = vol;

	if (vol > 400)
		vol = 400;

	vol = 400 - vol;

	return vol;
}
int esPlayObjectSound2(int AmbNum, int round, int x, int y, int z)
{
	int vol;

	if (AmbNum < 0)
	{
		if (AmbientSound2 >= 0)
		{
			StopWav(AmbientSoundNum2);
			AmbientSound2 = -1;
		}
		return TRUE;
	}

	vol = GetDistVolume2(x, y, z, round);

	if (vol > 100)
	{
		vol += 100;
		if (vol > 399)
			vol = 399;

		if (AmbNum != AmbientSound2 && !AmbientFlag)
		{
			if (CreateBufferFromWaveFile2(szAmbientSound2[AmbNum], AmbientSoundNum2) == FALSE)
				return FALSE;
			PlayWav2(AmbientSoundNum2, 1, vol, 2205);
			AmbientSound2 = AmbNum;
		}
		else
			PlayWav_VolChange(AmbientSoundNum2, vol);
		AmbientFlag++;
	}

	return TRUE;
}

int esContSound()
{
	int cnt;

	ContSoundCount++;

	if ((ContSoundCount & 0x7) != 0)
		return FALSE;

	if (ContSoundNum >= 0)
	{
		if (IsPlayWav(ContinueSoundNum) == TRUE)
			return FALSE;

		ContSoundNum = -1;
	}

	if (ContSoundPush > ContSoundPop)
	{
		cnt = ContSoundPop & CONT_SOUND_MASK;
		ContSoundNum = ContSoundBuff[cnt];

		if (CreateBufferFromWaveFile2(szSodSound[ContSoundNum], ContinueSoundNum) == FALSE)
			return FALSE;

		PlayWav2(ContinueSoundNum, 0, 360, 2205);

		ContSoundPop++;

		return TRUE;
	}

	return FALSE;
}
int esPlayContSound(int SoundNum)
{
	int cnt;

	if ((ContSoundPush - ContSoundPop) >= CONT_SOUND_MAX)
		return FALSE;

	cnt = ContSoundPush & CONT_SOUND_MASK;
	ContSoundBuff[cnt] = SoundNum;
	ContSoundPush++;

	return TRUE;
}

int	SkillPlaySound(int Num, int Volume, int Loop)
{
	PlayWav2(SkillSoundNum + Num, Loop, Volume, 2205);

	return TRUE;
}
int	SkillPlaySound(DWORD dwCode, int x, int y, int z, int Flag)
{
	int cnt;

	cnt = 0;
	while (1)
	{
		if (!SkillSoundWav[cnt].szFile)
			break;
		if (SkillSoundWav[cnt].dwCode == dwCode)
			return SkillPlaySound(cnt, GetDistVolume(x, y, z), Flag);
		cnt++;
	}

	return FALSE;
}

//��ų ���� ����
int	SkillStopSound(DWORD dwCode)
{
	int cnt;

	cnt = 0;
	while (1)
	{
		if (!SkillSoundWav[cnt].szFile)
			break;
		if (SkillSoundWav[cnt].dwCode == dwCode)

			return StopWav(SkillSoundNum + cnt);
		cnt++;
	}

	return FALSE;
}

int	esPlayEffectBgm(int Num)
{
	if (Num < 0)
	{
		if (AmbientSound >= 0)
		{
			StopWav(AmbientSoundNum);
			AmbientSound = Num;
		}
		return TRUE;
	}

	if (AmbientSound != Num)
	{
		if (CreateBufferFromWaveFile2(szAmbientSound[Num], AmbientSoundNum) == FALSE)
			return FALSE;

		PlayWav2(AmbientSoundNum, 1, 400, 2205);
		AmbientSound = Num;
	}

	return TRUE;
}


static int	FootStepCount = 0;

//���ڱ� �Ҹ�
int PlayFootStep(UnitData *lpChar)
{
	int floor;
	int cnt;


	FootStepCount++;

	if (lpChar->OnStageField >= 0) {
		floor = StageField[lpChar->OnStageField]->State;

		if (lpChar->WaterHeight != CLIP_OUT &&
			lpChar->WaterHeight > lpChar->pY && lpChar->WaterHeight < (lpChar->pY + 32 * fONE)) {

			if (FootStepCount & 1) {
				//�� �߼Ҹ�
				cnt = 14;
				esPlaySound(cnt + ((FootStepCount >> 1) % 3), 400);
				//esPlaySound( cnt+(rand()%3) , 400 );
			}
			return TRUE;
		}

		switch (floor) {
		case FIELD_STATE_VILLAGE:
		case FIELD_STATE_RUIN:
			//������ �߼Ҹ�
			cnt = 2;
			esPlaySound(cnt + (rand() % 3), 400);
			break;

		case FIELD_STATE_FOREST:
		case FIELD_STATE_DESERT:
			//�ε巯�� �߼Ҹ�
			cnt = 0;
			esPlaySound(cnt + (rand() % 2), 400);
			break;

		case FIELD_STATE_DUNGEON:
			//�ε巯�� �߼Ҹ�
			cnt = 11;
			esPlaySound(cnt + (rand() % 3), 400);
			break;
		}
	}

	return TRUE;
}


//ĳ���� ����
int	CharPlaySound(UnitData *lpChar)
{
	int cnt;

	DWORD	dwMotionCode;
	DWORD	dwCharSoundCode;
	int	vol;
	int x, y, z;

	int	CodeBuff[32];
	int	CodeBuffCnt = 0;

	x = (lpChar->pX - lpCurPlayer->pX) >> FLOATNS;
	z = (lpChar->pZ - lpCurPlayer->pZ) >> FLOATNS;
	y = (lpChar->pY - lpCurPlayer->pY) >> FLOATNS;

	vol = x * x + z * z + y * y;
	vol /= 1100;

	if (vol > 400) vol = 400;
	if (vol < 0) return TRUE;

	vol = 400 - vol;


	if (lpChar->sCharacterData.iType == CHARACTERTYPE_Player)
		dwCharSoundCode = lpChar->sCharacterData.JOB_CODE;
	else
		dwCharSoundCode = lpChar->sCharacterData.dwCharSoundCode;

	if (!lpChar->MotionInfo)
		return FALSE;

	dwMotionCode = lpChar->MotionInfo->State;

	if (dwMotionCode == CHRMOTION_STATE_RESTART)
	{
		esPlaySound(6, vol);
		return TRUE;
	}
	if (dwMotionCode == CHRMOTION_STATE_WALK || dwMotionCode == CHRMOTION_STATE_RUN)
	{
		if (vol < 300)
			return TRUE;

		dwMotionCode = CHRMOTION_STATE_WALK;
	}

	if (lpChar->sCharacterData.wPlayClass[0] == MONSTER_CLASS_HAMMER && dwMotionCode == CHRMOTION_STATE_ATTACK)
		dwMotionCode = CHRMOTION_STATE_HAMMER;

	for (cnt = 0; cnt < snEffectCnt; cnt++)
	{
		if (snEffect[cnt].CharSoundCode == dwCharSoundCode && snEffect[cnt].MotionState == dwMotionCode)
			CodeBuff[CodeBuffCnt++] = cnt;
	}

	if (CodeBuffCnt)
	{
		int	Feq;
		Feq = 2205;
		if (lpChar->sCharacterData.wPlayClass[1] && lpChar->sCharacterData.Brood != smCHAR_MONSTER_USER)
		{
			if (lpChar->sCharacterData.wPlayClass[1] < fONE)
				Feq = 3600;
			if (lpChar->sCharacterData.wPlayClass[1] > fONE * 2)
				Feq = 1400;
		}
		if (lpChar->sCharacterData.iType == CHARACTERTYPE_Player && lpChar->sCharacterData.SizeLevel >= 0x1000)
			Feq = 2800;

		PlayWav2(snEffect[CodeBuff[rand() % CodeBuffCnt]].RealSoundNum, 0, vol, Feq);
		return TRUE;
	}


	return FALSE;
}


//��������
int	WeaponPlaySound(UnitData *lpChar)
{
	int cnt;

	DWORD	dwCode;

	int	vol;
	int x, y, z;
	int	ItemNum;
	int HandType;

	int	CodeBuff[32];
	int	CodeBuffCnt = 0;

	if (lpChar != lpCurPlayer)
	{
		x = (lpChar->pX - lpCurPlayer->pX) >> FLOATNS;
		z = (lpChar->pZ - lpCurPlayer->pZ) >> FLOATNS;
		y = (lpChar->pY - lpCurPlayer->pY) >> FLOATNS;

		vol = x * x + z * z + y * y;
		vol /= 1100;

		if (vol > 400) vol = 400;
		if (vol < 0) return TRUE;

		vol = 400 - vol;
	}
	else
		vol = 400;

	for (cnt = 0; cnt < MAX_ITEM; cnt++)
	{
		if (sItem[cnt].CODE == lpChar->dwActionItemCode)
		{
			ItemNum = cnt;
			HandType = sItem[cnt].Class;
			break;
		}
	}
	if (cnt == MAX_ITEM)
		return FALSE;

	if (lpChar->AttackCritcal < 0)
	{
		if (HandType == ITEM_CLASS_WEAPON_ONE)
			dwCode = 12;
		else
			dwCode = 13;
	}
	else
	{
		dwCode = 14;

		switch (lpChar->dwActionItemCode&sinITEM_MASK2)
		{
		case sinWA1:
			if (HandType == ITEM_CLASS_WEAPON_ONE)
				dwCode = 1;
			else
				dwCode = 2;
			break;
		case sinWS2:
			if ((lpChar->dwActionItemCode&sinITEM_MASK3) <= sin03)
			{
				dwCode = 15;
				break;
			}
			if (HandType == ITEM_CLASS_WEAPON_ONE)
				dwCode = 3;
			else
				dwCode = 4;
			break;
		case sinWP1:
			if (HandType == ITEM_CLASS_WEAPON_ONE)
				dwCode = 5;
			else
				dwCode = 6;
			break;
		case sinWC1:
			dwCode = 7;
			break;
		case sinWS1:
			dwCode = 8;
			break;
		case sinWM1:
			if (lpChar->sCharacterData.JOB_CODE == JOBCODE_PRIESTESS || lpChar->sCharacterData.JOB_CODE == JOBCODE_MAGICIAN)
			{
				if (lpChar->WeaponEffect)
					return TRUE;
				if (HandType == ITEM_CLASS_WEAPON_ONE)
					dwCode = 17;
				else
					dwCode = 18;
			}
			else
			{
				if (HandType == ITEM_CLASS_WEAPON_ONE)
					dwCode = 9;
				else
					dwCode = 10;
			}
			break;
		case sinWH1:
			if (HandType == ITEM_CLASS_WEAPON_ONE)
				dwCode = 9;
			else
				dwCode = 10;
			break;
		case sinWT1:
			dwCode = 11;
			break;
		case sinWD1:
			dwCode = 3;
			break;
		case sinWN1:
			if (lpChar->sCharacterData.JOB_CODE == JOBCODE_SHAMAN)
			{
				if (lpChar->WeaponEffect)
					return TRUE;
				else
					dwCode = 17;
			}
			else
				dwCode = 14;
			break;
		}
	}

	for (cnt = 0; cnt < snEffectWeaponCnt; cnt++)
	{
		if (snEffectWeapon[cnt].WeaponState == dwCode)
			CodeBuff[CodeBuffCnt++] = cnt;
	}
	// ��������
	if (CodeBuffCnt)
	{
		PlayWav2(snEffectWeapon[CodeBuff[rand() % CodeBuffCnt]].RealSoundNum, 0, vol, 2205);

		if ((lpChar->AttackCritcal > 0 || (lpChar->AttackCritcal >= 0 && lpChar->AttackEffect)) && lpChar->dwActionItemCode)
		{
			dwCode = 16;
			CodeBuffCnt = 0;
			for (cnt = 0; cnt < snEffectWeaponCnt; cnt++)
			{
				if (snEffectWeapon[cnt].WeaponState == dwCode)
					CodeBuff[CodeBuffCnt++] = cnt;
			}
			if (CodeBuffCnt)
				PlayWav2(snEffectWeapon[CodeBuff[rand() % CodeBuffCnt]].RealSoundNum, 0, vol, 2205);
		}
		return TRUE;
	}

	return FALSE;
}
int PlayWaponSoundDirect(int x, int y, int z, DWORD dwCode)
{
	int cnt;
	int	vol;

	int	CodeBuff[32];
	int	CodeBuffCnt = 0;

	CodeBuffCnt = 0;
	for (cnt = 0; cnt < snEffectWeaponCnt; cnt++)
	{
		if (snEffectWeapon[cnt].WeaponState == dwCode)
			CodeBuff[CodeBuffCnt++] = cnt;
	}

	vol = GetDistVolume(x, y, z);

	if (CodeBuffCnt && vol > 10)
		PlayWav2(snEffectWeapon[CodeBuff[rand() % CodeBuffCnt]].RealSoundNum, 0, vol, 2205);


	return TRUE;
}


//int PlayBackMusic( int Num )

char *szMusicFile[] =
{
	"wav\\bgm\\Field - Desert - Pilgrim.bgm",
	"wav\\bgm\\Town - Tempskron_Stronghold.bgm",
	"wav\\bgm\\Town 1 - Tempskron_Ricarten - When wind comes-o.bgm",
	"wav\\bgm\\wind loop.bgm",
	"wav\\bgm\\Field - Forest - DarkWood.bgm",
	"wav\\bgm\\Dungeon - Gloomy Heart.bgm",
	"wav\\bgm\\Town 2 - Morion_Philliy - Voyage above the Clouds.bgm",

	//SoD ����
	"wav\\Sod\\BGM\\Stage_Play1.bgm",
	"wav\\Sod\\BGM\\Stage_Play1.bgm",
	"wav\\Sod\\BGM\\Stage_Play3.bgm",
	"wav\\bgm\\Field - Desert - Pilgrim.bgm",
	"wav\\bgm\\Ice 1.bgm",

	"wav\\bgm\\AncientWeapon.bgm",
	"wav\\bgm\\atlantis.bgm",
	"wav\\bgm\\battletown.bgm",
	"wav\\bgm\\Creepy1.bgm",
	"wav\\bgm\\Creepy2.bgm",
	"wav\\bgm\\DeathCave.bgm",
	"wav\\bgm\\Mystery1.bgm",
	"wav\\bgm\\Mystery2.bgm",
	"wav\\bgm\\MysteryDesert.bgm",
	"wav\\bgm\\MysteryForest.bgm",

	NULL
};


int	NextMusicNum;
DWORD	dwFadeStartTime = 0;
int LastMusicVolume;
int	PlayingBgmNum = -1;


int PlayBGM_Direct(int MusicNum)
{

	
	return TRUE;
}

int ChangeBGM(int MusicNum)
{
	

	return TRUE;
}

int BGM_Main()
{
	

	return TRUE;
}

int GetDistVolume(int dx, int dy, int dz)
{
	int vol;
	int x, y, z;

	x = (lpCurPlayer->pX - dx) >> FLOATNS;
	y = (lpCurPlayer->pY - dy) >> FLOATNS;
	z = (lpCurPlayer->pZ - dz) >> FLOATNS;

	vol = x * x + z * z + y * y;
	vol /= 1100;

	if (vol > 400) vol = 400;

	vol = 400 - vol;

	return vol;
}

const char *TALK_SOUND_DIRECOTRY = { "wav\\Talk\\" };

char		g_szTalkSoundFullName[128];
char		g_szTalkSoundName[64];
DWORD		g_TalkSoundSum;

char		g_szPlayTalkSoundName[64];
DWORD		g_PlayTalkSoundSum;

static int  s_TalkSoundBuffNum;
static int  s_TalkSoundIsPlay;

int FindTalkSound(char *lpSrcMessage)
{
	g_TalkSoundSum = GetSpeedSum(lpSrcMessage);
	_ui64toa_s(g_TalkSoundSum, g_szTalkSoundName, sizeof(g_szTalkSoundName), 10);
	lstrcat(g_szTalkSoundName, ".wav");

	lstrcpy(g_szTalkSoundFullName, TALK_SOUND_DIRECOTRY);
	lstrcat(g_szTalkSoundFullName, g_szTalkSoundName);

	FILE *fp;
	fopen_s(&fp,g_szTalkSoundFullName, "rb");
	if (fp == NULL)
		return FALSE;

	return TRUE;
}

extern int isPlaying(int i);
int IsPlayTalkSound(void)
{
	if (s_TalkSoundBuffNum && s_TalkSoundIsPlay)
	{
		s_TalkSoundIsPlay = isPlaying(s_TalkSoundBuffNum);
		return s_TalkSoundIsPlay;
	}

	return 0;
}
void PlayTalkSound(void)
{
	if (s_TalkSoundBuffNum == 0)
	{
		s_TalkSoundBuffNum = LoadSoundNum;
		sangJuWav_F[s_TalkSoundBuffNum] = 0;
		LoadSoundNum++;
	}

	if (CreateBufferFromWaveFile2(g_szTalkSoundFullName, s_TalkSoundBuffNum) == FALSE)
		return;

	PlayWav2(s_TalkSoundBuffNum, 0, 400, 2205);

	lstrcpy(g_szPlayTalkSoundName, g_szTalkSoundName);
	g_PlayTalkSoundSum = g_TalkSoundSum;
	s_TalkSoundIsPlay = 1;
}
void StopTalkSound(void)
{
	if (s_TalkSoundBuffNum)
		StopWav(s_TalkSoundBuffNum);

	s_TalkSoundIsPlay = 0;
}