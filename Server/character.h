#ifndef	_CHARACTER_HEADER

#define	_CHARACTER_HEADER


#include "smPacket.h"

#define PLAYBUFF_SIZE		256
#define PLAYBUFF_MASK		255

#define PLAYCOUNT_PER_SECOND		70

#define DIST_TRANSLEVEL_NEAR	0x12000
#define DIST_TRANSLEVEL_HIGH	0x48000
#define DIST_TRANSLEVEL_MHIGH	0xC8000
#define DIST_TRANSLEVEL_MID		0x120000
#define DIST_TRANSLEVEL_LOW		0x320000

#define DIST_TRANSLEVEL_DISCONNECT	0x320000
#define DIST_TRANSLEVEL_CONNECT		0x120000


#define	PARTY_GETTING_DIST		(18*64*18*64)
#define	PARTY_GETTING_DIST2		(17*64*17*64)


#define PLAYSERVER_SENDCOUNTER		(70*1)				//1ÃÊ´Ù

#define	ICE_FOOT_COUNT_MAX		20
#define	ICE_FOOT_LIFE_TIME		5000
#define	ICE_FOOT_ALPHA_STEP		(200.f / float(ICE_FOOT_LIFE_TIME))

#define STATE_BAR_WIDTH_NEW		426
#define STATE_BAR_HEIGHT_NEW	31
#define STATE_BAR_SIZE_NEW		300

struct SIceFootInfo
{
	int     Life;
	int     TypeNum;
	DWORD   dwPlayTime;
	POINT3D FootPos;
	POINT3D FootAngle;
};

#define DPAT_MAX		2048 * 4

struct smDPAT 
{
	smDPAT	*lpTalkLink;

	smDPAT	*smDinaLink;
	smPAT3D	*Pat;

	char	szPatName[64];
	int		UseCount;
	DWORD	dwSpeedFindSum;

	smMODELINFO	*lpModelInfo;

	DWORD	LastUsedTime;
};


class smPATTERN {
public:

	smPATTERN *BipPattern;

	smDPAT	DinaPat[ DPAT_MAX ];
	smPATTERN(void);
	~smPATTERN(void);

	void Init();
	int	Close();

	int GetNew();
	int FindFromName( char *szName );
	int FindFromCode( DWORD dwCode );
	smDPAT *LoadCharactor( char *szFileName ) ;
	smDPAT *LoadBipPattern( char *szFileName ) ;

};



#define	DISP_MODE_PATMAIN	1
#define	DISP_MODE_PATSUB	2
#define	DISP_MODE_PATTALK	4

#define CHAR_FRAME_MASK		0x00FFFFFF
#define CHAR_FRAME_SELSHIFT	24	

struct smCHARTOOL
{
	smOBJ3D *ObjBip;
	smPAT3D *PatTool;
	DWORD	dwItemCode;

	int	SizeMax,SizeMin;

	int		ColorBlink;
	short	sColors[4];
	DWORD	ColorEffect;
	int		BlinkScale;
	int		EffectKind;
	DWORD	ElementEffect;

	int		TexMixCode,TexScroll;
};



//////////// »úÐµ±í¼¼ÄÜ±àºÅ //////////////
#define SKILL_PLAY_EXTREME_SHIELD	0x1A //¼«¹â»¤¶Ü
#define SKILL_PLAY_MECHANIC_BOMB	0x1B
#define	SKILL_PLAY_PHYSICAL_ABSORB	0x1C //Áé¹â»¤Ìå
#define	SKILL_PLAY_POISON_ATTRIBUTE	0x1D

#define	SKILL_PLAY_GREAT_SMASH		0x2A
#define	SKILL_PLAY_MAXIMIZE			0x2B //¸ÄÁ¼×¨¼Ò
#define	SKILL_PLAY_AUTOMATION		0x2C //Áé¹â·ÉÑï
#define	SKILL_PLAY_SPARK			0x2D

#define	SKILL_PLAY_METAL_ARMOR		0x3A //½ðÊôÖØ¼×
#define	SKILL_PLAY_GRAND_SMASH		0x3B //ÐÇ¹âÃð¾ø
#define	SKILL_PLAY_SPARK_SHIELD		0x3C //·ÀÓùµç²¨

#define	SKILL_PLAY_IMPULSION		0x4A
#define	SKILL_PLAY_COMPULSION		0x4B
#define	SKILL_PLAY_MAGNETIC_SPHERE	0x4C //´ÅÐÔÇòÌå
#define	SKILL_PLAY_METAL_GOLEM		0x4D //ÖÕ¼«»úÐµ

#define	SKILL_PLAY_LANDMINNING		0x5A //Åùö¨Ðý·ç
#define	SKILL_PLAY_H_SONIC			0x5B //¿ìËÙ´ò»÷
#define	SKILL_PLAY_R_SMASH			0x5C //¾¿¼«Ö®ÈÐ
#define	SKILL_PLAY_P_ENHENCE		0x5D //Õ½Éñ×£¸£


//////////// ÎäÊ¿¼¼ÄÜ±àºÅ //////////////
#define SKILL_PLAY_RAVING			0x1A //¾øµØ±©×ß
#define SKILL_PLAY_IMPACT			0x1B //¾«×¼Ö®»÷

#define SKILL_PLAY_TRIPLE_IMPACT	0x2A //ÍþÁ¦³å»÷
#define SKILL_PLAY_BRUTAL_SWING		0x2B //ÖÂÃü»ØÐý
#define SKILL_PLAY_ROAR				0x2C //¼«µØÅ­ºð
#define SKILL_PLAY_RAGEOF_ZECRAM	0x2D //

#define SKILL_PLAY_CONCENTRATION	0x3A
#define SKILL_PLAY_AVANGING_CRASH	0x3B
#define SKILL_PLAY_SWIFT_AXE		0x3C
#define SKILL_PLAY_BONE_SMASH		0x3D

#define SKILL_PLAY_DESTROYER		0x4A
#define SKILL_PLAY_BERSERKER		0x4B //·è¿ñÅ­ºð
#define SKILL_PLAY_CYCLONE_STRIKE	0x4C

#define	SKILL_PLAY_D_HIT			0x5A
#define	SKILL_PLAY_P_DASH			0x5B //¿ñÒ°³å»÷
#define	SKILL_PLAY_M_BLOW			0x5C //»ØÐýÕ¶»÷
#define	SKILL_PLAY_B_BERSERKER		0x5D //ÖÚÉñÖ®Å­

//////////// Ç¹±ø¼¼ÄÜ //////////////
#define SKILL_PLAY_PIKEWIND			0x1A
#define SKILL_PLAY_CRITICAL_HIT		0x1B //ÖÂÃü´ò»÷
#define SKILL_PLAY_JUMPING_CRASH	0x1C

#define SKILL_PLAY_GROUND_PIKE		0x2A
#define SKILL_PLAY_TORNADO			0x2B
#define SKILL_PLAY_EXPANSION		0x2C

#define SKILL_PLAY_VENOM_SPEAR		0x3A
#define SKILL_PLAY_VANISH			0x3B //Òþ°µÖ®Êõ
#define SKILL_PLAY_CHAIN_LANCE		0x3C //Á´ÆïÖ®Ç¹

#define SKILL_PLAY_ASSASSIN_EYE		0x4A //°µÉ±Ö®ÑÛ
#define SKILL_PLAY_CHARGING_STRIKE	0x4B
#define SKILL_PLAY_VAGUE			0x4C //Ó°ÒþÖ®¶Ý
#define SKILL_PLAY_SHADOW_MASTER	0x4D

#define	SKILL_PLAY_D_REAPER			0x5A //»ØÐý´ò»÷
#define	SKILL_PLAY_F_SPEAR			0x5B //µØÇ¹ÆæÏ®
#define	SKILL_PLAY_AMPLIFIED		0x5C //Ç±ÄÜ¼¤·¢
#define	SKILL_PLAY_SS_ATTACK		0x5D


//////////// ¹­ÊÖ¼¼ÄÜ±àºÅ //////////////

#define SKILL_PLAY_SCOUT_HAWK		0x1A
#define SKILL_PLAY_WIND_ARROW		0x1B
#define SKILL_PLAY_PERFECT_AIM		0x1C

#define SKILL_PLAY_FALCON			0x2A //Áé»êÖ®Ó¥
#define SKILL_PLAY_ARROWOF_RAGE		0x2B
#define SKILL_PLAY_AVALANCHE		0x2C //Ñ©±ÀÖ®¼ý

#define SKILL_PLAY_ELEMENTAL_SHOT	0x3A //ÔªËØ¹¥»÷
#define SKILL_PLAY_GOLDEN_FALCON	0x3B //»Æ½ðÁÔÓ¥
#define SKILL_PLAY_BOMB_SHOT		0x3C //±¬ÁÑÖ®¼ý
#define SKILL_PLAY_PERFORATION		0x3D

#define SKILL_PLAY_RECALL_WOLVERIN	0x4A //ÕÙ»½Ñ©ÀÇ
#define SKILL_PLAY_PHOENIX_SHOT		0x4B
#define SKILL_PLAY_FORCE_OF_NATURE	0x4C //×ÔÈ»Ö®¹â

#define	SKILL_PLAY_E_SHOT			0x5A //»ØÐýÖ®Îè
#define	SKILL_PLAY_S_ROPE			0x5B //Ðþ¹âÖ®Îè
#define	SKILL_PLAY_N_SPLASH			0x5C
#define	SKILL_PLAY_C_TRAP			0x5D //º®±ùÖ®¼ý


////////////// ÓÎÏÀ¼¼ÄÜ±àºÅ //////////////
#define SKILL_PLAY_SWORD_BLAST		0x1A
#define SKILL_PLAY_HOLY_BODY		0x1B //Ê¥¹â»¤Ìå
#define SKILL_PLAY_DOUBLE_CRASH		0x1C

#define SKILL_PLAY_HOLY_VALOR		0x2A
#define SKILL_PLAY_BRANDISH			0x2B
#define SKILL_PLAY_PIERCING			0x2C
#define SKILL_PLAY_DRASTIC_SPIRIT	0x2D

#define SKILL_PLAY_DIVINE_INHALATION	0x3A //Ê¥ÁéÖ®Îü
#define SKILL_PLAY_HOLY_INCANTATION		0x3B
#define SKILL_PLAY_GRAND_CROSS			0x3C

#define SKILL_PLAY_DIVINE_PIERCING		0x4D
#define SKILL_PLAY_GODLY_SHIELD			0x4B //¾´ÉñÖ®¶Ü
#define SKILL_PLAY_GODS_BLESS			0x4C //ÉÏµÛ×£¸£
#define SKILL_PLAY_SWORD_OF_JUSTICE		0x4A

#define	SKILL_PLAY_S_BREAKER		0x5A //ÉñÁ¦³å´Ì
#define	SKILL_PLAY_C_MOON			0x5B //ÉýÁúÖØ»÷
#define	SKILL_PLAY_S_BLADE			0x5C //ÉÏµÛÖØ»÷
#define	SKILL_PLAY_H_BENEDIC		0x5D //ÍöÁéÖ®Öä


////////////// Ä§Ç¹ÊÖ¼¼ÄÜ±àºÅ ///////////////
#define SKILL_PLAY_SHIELD_STRIKE	0x1A
#define SKILL_PLAY_FARINA			0x1B
#define SKILL_PLAY_VIGOR_SPEAR		0x1C

#define SKILL_PLAY_WINDY			0x2A
#define SKILL_PLAY_TWIST_JAVELIN	0x2B
#define SKILL_PLAY_SOUL_SUCKER		0x2C
#define SKILL_PLAY_FIRE_JAVELIN		0x2D

#define SKILL_PLAY_SPLIT_JAVELIN		0x3A
#define SKILL_PLAY_TRIUMPH_OF_VALHALLA	0x3B //Õ½ÀõÅØÏø
#define SKILL_PLAY_LIGHTNING_JAVELIN	0x3C
#define SKILL_PLAY_STORM_JAVELIN		0x3D //±©·ç¿ñ±ê

#define SKILL_PLAY_HALL_OF_VALHALLA		0x4A //Íß¶û¹þÀ­Ö®¹â
#define SKILL_PLAY_X_RAGE				0x4B
#define SKILL_PLAY_FROST_JAVELIN		0x4C //Ëª¶³±êÇ¹
#define SKILL_PLAY_VENGEANCE			0x4D

#define	SKILL_PLAY_TALARIA			0x5A //ÇáÎè·ÉÑï
#define	SKILL_PLAY_G_COUP			0x5B //ÐÇÔÆ±êÇ¹
#define	SKILL_PLAY_S_ARCUDA			0x5C //±¿±¿ÐÜ
#define	SKILL_PLAY_S_FEAR			0x5D //ÁÒÑæÍ»Ï®


////////////// ¼ÀË¾¼¼ÄÜ±àºÅ ///////////////
#define SKILL_PLAY_HEALING			0x1A
#define SKILL_PLAY_HOLY_BOLT		0x1B
#define SKILL_PLAY_MULTI_SPARK		0x1C
#define SKILL_PLAY_HOLY_MIND		0x1D

#define	SKILL_PLAY_DIVINE_LIGHTNING	0x2A
#define	SKILL_PLAY_HOLY_REFLECTION	0x2B //ÉñÊ¥·´Éä
#define	SKILL_PLAY_GREAT_HEALING	0x2C

#define	SKILL_PLAY_VIGOR_BALL		0x3A
#define	SKILL_PLAY_RESURRECTION		0x3B //»ØÉúÖ®Êõ
#define	SKILL_PLAY_EXTINCTION		0x3C //Ê¥¹âÖ®Öä
#define	SKILL_PLAY_VIRTUAL_LIFE		0x3D //ÉñÊ¥Ö®¹â

#define	SKILL_PLAY_GLACIAL_SPIKE	0x4A
#define	SKILL_PLAY_REGENERATION_FIELD	0x4B //ÔÙÉúÁìÓò
#define	SKILL_PLAY_CHAIN_LIGHTNING	0x4C
#define	SKILL_PLAY_SUMMON_MUSPELL	0x4D //ÉñÊ¥ÌìÊ¹

#define	SKILL_PLAY_S_IMPACT			0x5A //ÉñÊ¥µç²¨
#define	SKILL_PLAY_P_ICE			0x5B
#define	SKILL_PLAY_S_PRMIEL			0x5C //±©·çÑ©
#define	SKILL_PLAY_B_KRISHNA		0x5D //ÏÉÅ®É¢»¨


////////////// Ä§·¨Ê¦¼¼ÄÜ±àºÅ ///////////////
#define SKILL_PLAY_AGONY			0x1A
#define SKILL_PLAY_FIRE_BOLT		0x1B
#define SKILL_PLAY_ZENITH			0x1C //¼¯ºÏÖ®Êõ
#define SKILL_PLAY_FIRE_BALL		0x1D

#define SKILL_PLAY_COLUMN_OF_WATER	0x2A
#define SKILL_PLAY_ENCHANT_WEAPON	0x2B //ÔªËØÖ®Êõ
#define SKILL_PLAY_DEAD_RAY			0x2C

#define SKILL_PLAY_ENERGY_SHIELD	0x3A //Ä§·¨ÊØ»¤
#define SKILL_PLAY_DIASTROPHISM		0x3B
#define SKILL_PLAY_SPIRIT_ELEMENTAL	0x3C //Áé»êÕÙ»½
#define SKILL_PLAY_DANCING_SWORD	0x3D //ÔªËØÖ®½£

#define SKILL_PLAY_FIRE_ELEMENTAL	0x4A //ÒÁ·òÁÐÌØ
#define SKILL_PLAY_FLAME_WAVE		0x4B
#define SKILL_PLAY_DISTORTION		0x4C
#define SKILL_PLAY_METEO			0x4D //ÔÉÊ¯ÕÙ»½

#define	SKILL_PLAY_SILRAPHIM		0x5A //Á÷ÐÇ»ðÓê
#define	SKILL_PLAY_V_TENUS			0x5B //ËõÐ¡Ö®Êõ
#define	SKILL_PLAY_P_IGNIS			0x5C //ÉñÊ¥Ï´Àñ
#define	SKILL_PLAY_T_ANIMA			0x5D //Ê¥¹â·¨Õó

////////////// ´Ì¿Í¼¼ÄÜ±àºÅ ///////////////
#define SKILL_PLAY_STRINGER			0x1A //´Ì»÷
#define SKILL_PLAY_RUNNING_HIT		0x1B //ÉÁ»÷
#define SKILL_PLAY_WIELD_MASTERY	0x1C //Ç¿»¯¹¥»÷
#define SKILL_PLAY_WISP				0x1D //Èõµã¹¥»÷

#define SKILL_PLAY_VENOM_THORN		0x2A //¶¾ÑÀÁ¬»÷
#define SKILL_PLAY_ALAS				0x2B //Ãô½ÝÖ®Á¦
#define SKILL_PLAY_SOUL_SHOCK		0x2C //Áé»êÕðº³
#define SKILL_PLAY_BLADE_MASTERY	0x2D //¹¥»÷´óÊ¦

#define SKILL_PLAY_SORE_SWORD		0x3A //·É½£Ö®Îè
#define SKILL_PLAY_BEAT_UP			0x3B //ÌøÕ¶
#define SKILL_PLAY_INPES			0x3C //Ãô½Ý´óÊ¦
#define SKILL_PLAY_BLIND			0x3D //ÖÂÃ¤

#define SKILL_PLAY_FROST_WIND		0x4A //±ù¶³Ö®ÈÐ
#define SKILL_PLAY_FATAL_MASTERY	0x4B //ÖÂÃüÒÕÊõ
#define SKILL_PLAY_POLLUTE			0x4C //ÎÁÒßÖ®ÈÐ
#define SKILL_PLAY_PASTING_SHADOW	0x4D //Ó°×ÓÉÁ»÷

#define SKILL_PLAY_SHADOW_BOMB		0x5A //Ó°×Ó»ðÑæ
#define SKILL_PLAY_RISING_SLASH		0x5B //µØÁÑÕ¶
#define SKILL_PLAY_VIOLENT_STUB		0x5C //ÃÍÁú°ÚÎ²
#define SKILL_PLAY_SHADOW_STORM		0x5D //·ç±©Ö®ÈÐ

////////////// ÈøÂú¼¼ÄÜ±àºÅ ///////////////
#define SKILL_PLAY_DARK_BOLT		0x1A //°µºÚÉÁµç
#define SKILL_PLAY_DARK_WAVE		0x1B //°µºÚ²¨ÀË
#define SKILL_PLAY_INERTIA			0x1C //×çÖäÀ×»÷
#define SKILL_PLAY_INNER_PEACE		0x1D //ÄÚÐÄÆ½ºÍ

#define SKILL_PLAY_SPIRITUAL_FLARE	0x2A //¾«ÉñÖäÊõ
#define SKILL_PLAY_SPIRITUAL_MANACLE 0x2B //Áé»ê¼ÏËø
#define SKILL_PLAY_CHASING_HUNT		0x2C //ÁÔÈ¡
#define SKILL_PLAY_ADVENT_MIGAL		0x2D //Âõ¿Ë¶û

#define SKILL_PLAY_RAINMAKER		0x3A //ÆíÓêÊ¦
#define SKILL_PLAY_LAND_OF_GHOST	0x3B //Â½µØÁé»ê
#define SKILL_PLAY_HAUNT			0x3C //¹í»ìÖØ»Ø
#define SKILL_PLAY_SCRATCH			0x3D //×¥ÆÆ

#define SKILL_PLAY_CRIMSON_KNIGHT	0x4A //ÊÈÑªÖ®Ò¹
#define SKILL_PLAY_JUDGEMENT		0x4B //ÉóÅÐ
#define SKILL_PLAY_ADVENT_MIDRANDA	0x4C //Ã×µÂÀ¼´ï
#define SKILL_PLAY_MOURNING_PRAY	0x4D //ÐñÈÕ¶«Éý

#define SKILL_PLAY_CREED			0x5A //ÖäÊõÐÅÑö
#define SKILL_PLAY_PRESS_DEITY		0x5B //×çÖäÖ®Á¦
#define SKILL_PLAY_PHANTOM_NAIL		0x5C //ËÀÍöÖ®×¦
#define SKILL_PLAY_OCCULT_LIFE		0x5D //¸ß¼¶ÔÙÉý

///////////// ¸ð¼Ç È®Àå //////////////////
#define SKILL_PLAY_DIVINE_PIERCING2		0x90
#define SKILL_PLAY_DIVINE_PIERCING3		0x91


////////////////////////////////////////////

#define SKILL_PLAY_BLESS_ABSORB			0xA0
#define SKILL_PLAY_BLESS_DAMAGE			0xA1
#define SKILL_PLAY_BLESS_EVADE			0xA2
#define SKILL_PLAY_BLESS_SIEGE_ITEM		0xA8

#define SKILL_PLAY_FIRE_CRYSTAL			0xB0
#define SKILL_PLAY_LIGHTNING_CRYSTAL	0xB1
#define SKILL_PLAY_ICE_CRYSTAL			0xB2
#define SKILL_PLAY_CHAOSCARA_VAMP		0xB8

#define SKILL_PLAY_PET_ATTACK		0xC0
#define SKILL_PLAY_PET_ATTACK2		0xC1

#define SKILL_PLAY_SOD_ITEM			0xD0
#define SKILL_PLAY_SPEACIAL			0xF0
#define	SKILL_PLAY_LOVELY_LIFE		0xF1

#define SKILL_PLAY_ELEMENT_ATTACK	0xE0
#define SKILL_PLAY_MOURNING_PRAY2	0xE1

#define	SKILL_EFFECT_FIREFLOWER		0x12000010

#define	SKILL_APPMASK_EXTREME_SHIELD		0x0001
#define	SKILL_APPMASK_PHYSICAL_ABSORB		0x0002
#define	SKILL_APPMASK_AUTOMATION			0x0004
#define	SKILL_APPMASK_ANGER					0x0008
#define	SKILL_APPMASK_SPARK_SHIELD			0x0010
#define	SKILL_APPMASK_GODLY_SHIELD			0x0020


#define	SKILL_APPMASK_HOLY_BODY				0x00010000

#define	ATTACK_DAMAGE_LIST_MAX			100

class Unit
{
	DWORD	Head;

public:

	int uIndex;
	int		DisplayFlag;
	int		DisplayTools;

	smSTAGE3D	*lpStage;
	ID			iID;
	int			AutoPlayer;
	UINT		uLastUpdate;
	smPAT3D	*Pattern;
	smPAT3D	*Pattern2;			//¸Ó¸® ÆÐÅÏ
	smPAT3D *AnimPattern;

	smPAT3D *TalkPattern;		// Ç¥Á¤ ÆÐÅÏ. ( ´ÙÀÌ³ª¹Í ÆÐÅÏÀº ini ¿¡ µû¶ó¼­ lpDinaPattern ¶Ç´Â lpDinaPattern2 )

	smDPAT  *lpDinaPattern;		//´ÙÀÌ³ª¹Í ÆÐÅÏ Æ÷ÀÎÅÍ (ÆÐÅÏÀÇ °ü¸®ÀÚ)
	smDPAT  *lpDinaPattern2;	//´ÙÀÌ³ª¹Í ÆÐÅÏ Æ÷ÀÎÅÍ ¸Ó¸®(ÆÐÅÏÀÇ °ü¸®ÀÚ)

	smDPAT  *lpDinaLeftPattern;		//¿ÞÂÊ ¹«±â
	smDPAT  *lpDinaRightPattern;	//¿À¸¥ÂÊ ¹«±â

	smCHARTOOL	HvLeftHand;		//¿Þ¼Õ¿¡ Âø¿ë µµ±¸
	smCHARTOOL	HvRightHand;	//¿À¸¥¼Õ¿¡ Âø¿ë µµ±¸

	smMATRIX	HvLeftHand_Matrix;	//¿Þ¼Õ ¹«±â Çà·Ä º¹»ç
	smMATRIX	HvRightHand_Matrix; //¿À¸¥¼Õ ¹«±â Çà·Ä º¹»ç

	int		Rend_HvLeftHand;		//¹«±â ·»´õ¸µ À¯¹«
	int		Rend_HvRightHand;		//¹«±â ·»´õ¸µ À¯¹«


	smOBJ3D	*BackObjBip[5];		//µîÂÊ ¹«±â Âø¿ë
	smOBJ3D	*AttackObjBip;		//°ø°Ý ÆÐµå ¿ÀºêÁ§Æ®
	smOBJ3D	*ShieldObjBip;		//¹æÆÐ ÆÐµå ¿ÀºêÁ§Æ®
	smOBJ3D *DaggerObjBip;

	int		AttackToolRange;	//°ø°Ý »çÁ¤°Å¸®
	int		AttackAnger;
	int		AttackIce;			//¾óÀ½ °ø°Ý ¹ÞÀ½


	BOOL	bActive;

	union
	{
		struct
		{
			int pX;
			int pY;
			int pZ;
		};

		Point3D sPosition;
	};
	int		AttackX,AttackY,AttackZ;
	int		PHeight;
	int		FallHeight;
	int		iLoadedMapIndex;
	int		OnStageFieldState;

	BOOL	bLoading;

	int		PatWidth;		//Ä³¸¯ÅÍ ³ÐÀÌ
	int		PatHeight;		//Ä³¸¯ÅÍ ³ôÀÌ

	int		PatSizeLevel;	//Ä³¸¯ÅÍ Å©±â ´Ü°è ( 0 ~ 3 )

	int		OverLapPosi;	//´Ù¸¥ Ä³¸¯ÅÍ¿Í À§Ä¡°¡ °ãÄ§
	int		OverLapPosi2;	//´Ù¸¥ Ä³¸¯ÅÍ¿Í À§Ä¡°¡ °ãÄ§
	Unit	*lpCharOverLap;	//°ãÄ£ Ä³¸¯ÅÍÀÇ Æ÷ÀÎÆ®

	POINT3D Posi;

	union
	{
		struct
		{
			POINT3D Angle;
		};

		Point3D sAngle;
	};

	int		MoveMode;	//ÀÌµ¿ ¸ðµå ( 0 - °È±â 1-´Þ¸®±â )
	int		MoveFlag;
	int		MoveCnt;	// Åë½Å½Ã ¹ÞÀº µ¥ÀÌÅ¸°¡ ¾øÀ»°æ¿ì ÀÚµ¿ ÀÌµ¿ÇÒ¶§ °Å¸® Á¦ÇÑ Ä«¿îÅÍ
	int		tx,tz;		// ¸ñÇ¥ ÀÌµ¿ ÁÂÇ¥
	int		TargetMoveCount;	//¸ñÇ¥ ÀÌµ¿ ÁÂÇ¥ Ä«¿îÅÍ
	int		WaterHeight;		//¹° ³ôÀÌ

	DWORD	dwActionItemCode;	//ÁÖ ¿òÁ÷ÀÓ¿¡ °ü·ÃµÈ ÄÚµå
	DWORD	dwItemSetting;		//¾ÆÀÌÅÛ ¼¼ÆÃ ¹æ¹ý( 0-±¸ºÐ ¾øÀ½ 1-¸¶À»ÇÊµå ±¸ºÐ )
	DWORD	dwActionItemTwoHand;	//¾ç¼Õ ¹«±â Ã½Å©

	short	wStickItems[4];		//ÀåÂø ¾ÆÀÌÅÛ ¹øÈ£

	int		ShootingMode;	//¹ß»çÇü °ø°Ý ¸ðµå ( TRUE )
	int		ShootingFlag;	//ÇöÀç ¹ß»ç‰ç´ÂÁö ¿©ºÎ
	int		ShootingKind;	//¹ß»ç ±¸ºÐ
	POINT3D	ShootingPosi;	//¹ß»ç À§Ä¡

	POINT3D	ShootingAngle;	//¹ß»ç ¹æÇâ
	int		ShootingCount;	//¹ß»ç Ä«¿îÅÍ

	Unit	*chrAttackTarget;	//°ø°Ý ¸ñÇ¥ Ä³¸¯ÅÍ
	int		AttackCritcal;		//Å©¸®Æ¼ÄÃ °ø°Ý À¯¹«
	int		AttackCriticalCount;//Å©¸®Æ¼ÄÃ °ø°Ý Ä«¿îÅÍ ( ¿¬¼Ó °ø°Ý½Ã )
	int		AttackExp;			//°ø°Ý½Ã °æÇèÄ¡
	int		AttackSkil;			//½ºÅ³ °ø°Ý ÄÚµå
	int		AttackEffect;		//°ø°Ý½Ã Æ¯¼ö ÀÌÆåÆ® Ç¥½Ã
	int		LastSkillParam;		//ÃÖ±Ù ½ºÅ³°ø°Ý ±¸ºÐ ÄÚµå ( Ä«¿À½ºÄ«¶ó ¶«¿¡ ¶«»§¿ëÀ¸·Î Ãß°¡ ) 

	int		RecvExp;			//°æÇèÄ¡ ºÎ¿© ¹ÞÀ½

	POINT3D	ptNextTarget;	//´ÙÀ½ ÀÌµ¿ ¸ñÇ¥
	Point3D		sSpawnPosition;
	int		iLureDistance;
	int		TragetTraceMode;	//ÃßÀû ¸ðµå °ª (¼­¹ö»ç¿ë )

	POINT3D	PosBeginMove;		//ÀÌµ¿ ½ÃÀÛ½ÃÀÇ ÁÂÇ¥
	DWORD	PosBeginCount;

	DWORD	dwNextMotionCode;	//´ÙÀ½ µ¿ÀÛ ¿¹¾à

	int		ChargingFlag;		//Â÷Â¡ ÇÃ·¢

	DWORD	TalkFrame;		// Ç¥Á¤ ÇÁ·¹ÀÓ
	DWORD	TalkSoundSum;

	SMotionStEndInfo	FrameInfo;

	int			action;
	UINT		iFrame;
	int			FrameCnt;
	int			FrameStep;		//ÇÁ·¹ÀÓ ¹Ù²ñ °ª
	int			MoveSpeed;		//ÀÌµ¿ ¿òÁ÷ÀÓ °ª
	int			AttackSpeed;	//°ø°Ý ¼Óµµ

	int		ActionPattern;	// ¿òÁ÷ÀÓ ÆÐÅÏ

	DWORD	dwEventFrameExt[4];	//ÀÌº¥Æ® ÇÁ·¹ÀÓ È®Àå

	int		iAliveCounter;
	int		iDeathCounter;
	int		AutoMoveStep;	//ÀÚµ¿ ÀÌµ¿½Ã ½ºÅÜ Ä«¿îÅÍ
	short	sMoveStepCount[2];		//ÀÌµ¿ ½ºÅÜ ·çÇÁ °¡¿îÅÍ

	int		Counter;
	int		iFrameTimer;

	int		RendSucess;				//È­¸é»óÀÇ ·»´õ¸µ ¼º°ø ¿©ºÎ
	RECT	RendRect2D;				//·»´õ¸µµÈ 2D ÁÂÇ¥ ¿µ¿ª
	POINT3D	RendPoint;				//·»´õ¸µµÈ 2D ÁÂÇ¥ ( x,y,z )
	int		FlagShow;				//È­¸éÇ¥½Ã ÇÃ·¢ ( 0 - È­¸é Ãâ·Â ºÒÇã )

	//Ã¤ÆÃ
	char	szMessage[256];		//Ã¤ÆÃ ¹®ÀÚ¿­
	DWORD	dwMessageEndTime;		//Ã¤ÆÃ ¹®ÀÚ¸¦ Ç¥½Ã Á¾·á½Ã°£ ±â·Ï

	//»óÁ¡
	char	szTradeMessage[128];	//»óÁ¡ ¸Þ¼¼Áö ¹®ÀÚ¿­
	DWORD	dwTradeMsgCode;			//»óÁ¡ ¸Þ¼¼Áö ÄÚµå

	int		Damge;					//ÏÔÊ¾µÄÉËº¦Öµ
	DWORD	dwDamgeTimer;			//ÉËº¦µÄÏÔÊ¾µÄÊ±¼ä
	int		DmgBlendValue;			//µ­³öÖµ
	short	DmgType[2];				//¹¥»÷ÀàÐÍ0 ÑÕÉ«,1ÊÇ·ñ±©»÷


	BYTE	baUnitBufferNew[0x2000];
	int		uUnitInfoSize;

	//Åë½Å °ü·Ã
	int		ServerCode;				//ÇØ´ç Ä³¸¯ÅÍ ¼­¹ö ÄÚµå

	PlayBuffer	sPlayBuff[PLAYBUFF_SIZE];
	int			iPlayBuffCount;
	int			PlayBuffPosi_End;

	DWORD		dwLastActiveTime;
	int			LastPlayDataType;

	CharacterData sCharacterData;				//À¯Àú Á¤º¸
	UnitInfo	sUnitInfo;

	int		AnimDispMode;			//µ¿ÀÛ Ç¥½Ã ¸ðµå ( 0-¸ðµÎ Ç¥½Ã 1-ÇÑ°³¾¿ Ç¥½Ã)
	int		PatDispMode;			//ÆÐÅÏ Ç¥½Ã ¸ðµå ( 0-ºñÇ¥½Ã 1-¸ÞÀÎ 2-¼­ºê¸¸ 3-¸ðµÎ )

	int		MotionSelectFrame;		//ÇöÀçÀÇ ÇÁ·¹ÀÓÀÇ ¸ð¼ÇÀÇ ¹øÈ£ ( 0 , 1 ) 

	smMODELINFO		*smMotionInfo;	//¸ðµ¨ÀÇ µ¿ÀÛº° ÇÁ·¹ÀÓ°ú Á¤º¸
	smMODELINFO		*smMotionInfo2;	//¸ðµ¨ÀÌ 2°³ÀÏ °æ¿ì 1Â÷¸ðµ¨¿¡¼­ µ¥ÀÌÅ¸°¡ ¾ø´Â°æ¿ì 2Â÷¸ðµ¨ÀÇ µ¥ÀÌÅ¸¸¦ Ãâ·Â 
	ModelAnimation	*psModelAnimation;

	smMODELINFO		*lpTalkModelParent;
	ModelAnimation	*lpTalkMotionInfo;


	DWORD			OldMotionState;			//ÀÌÀüÀÇ ¸ð¼Ç ¼Ó¼º Á¤º¸
	DWORD			dwTarget;				//»ó´ë¹æÀÌ ÁÖÀÎ°øÀ» °Ü³ÉÇÑ ¾×¼ÇÀÏ°æ¿ì 

	User			* pcOwner;

	int				nCheckChar;

	User			* pcFocusTarget;
	Unit			* pcAttackTarget;
	int				AttackUserFlag;
	DWORD			dwIgnoreOthersTime;

	ID				lExclusiveTargetID;
	User			* lpLinkPlayInfo;		//¿¬°áµÈ ÇÃ·¹ÀÌ¾î
	Unit			* pcExclusiveUnitTarget;

	User			* pcLastAttacker;
	int				iDamageLastAttacker;
	DWORD			dwExpAttackTime;
	TRANS_ATTACKDATA AttackTrans;			//°ø°Ý µ¥ÀÌÅ¸ ¹öÆÛ
	DWORD			dwAttackPlayTime;		//°ø°Ý Àû¿ë ½Ã°£

	int				PotionLog;				//Æ÷¼Ç »ç¿ë ±â·Ï
	int				LevelLog;				//·¹º§ º¯È­ ±â·Ï
	int				CriticalLog;			//Å©¸®Æ¼ÄÃ ·Î±×

	int				EnableStateBar;			//Ã¼·Â¹Ù ±×¸®±â ¿É¼Ç
	int				MotionRecordCount;		//¸ð¼Ç Á¤º¸ ±â·Ï Ä«¿îÅÍ
	int				iSpawnPointIndex; // ·þÎñÆ÷¶ËÊ¹ÓÃ ¹ÖÎïµÄÊä³öµã

	int				DisplayAlpha;			//¹ÝÅõ¸íµµ ( ÀÓ½Ã ¹ÝÅõ¸í Ãâ·Â )
	int				RendAlpha;				//¹ÝÅõ¸íµµ ( ¿ø·¡ ¹ÝÅõ¸í Ä³¸¯ÅÍ )
	int				RenderLatter;			//·»´õ¸µ ³ªÁß¿¡

	DWORD			dwDispAppSkill;			//½ºÅ³ Àû¿ëÇ¥½Ã
	DWORD			dwDispAppSkillMask;		//½ºÅ³ Àû¿ëÇ¥½Ã ¸¶½ºÅ© ( µ¿±â¸¦ ¸ÂÃß±â À§ÇÔ )
	int				HideWeapon;				//¹«±â ¼û±è
	int				MotionLoop;				//¹Ýº¹ ¸ð¼Ç È½¼ö
	int				MotionLoopSpeed;		//¹Ýº¹ ¸ð¼Ç¿ë ÇÁ·¹ÀÓ ¼Óµµ
	int				MotionEvent;			//¸ð¼Ç ÀÌº¥Æ® ÇÃ·¢
	int				WeaponEffect;			//¹«±â¿ë ¼Ó¼º ÀÌÆåÆ®
	DWORD			dwWeaponEffectTime;		//¹«±â¿ë ¼Ó¼º ÀÌÆåÆ® Ä«¿îÅÍ
	int				EnchantEffect_Point;	//½ºÅ³ EnchantWeapon ÀÇ ½ºÅ³ Æ÷ÀÎÆ®

	User			* pcHookedTarget;
	DWORD			dwHookedTargetEndTime;

	DWORD			dwAssassinEyeTime;		//¾î¼¼½Å¾ÆÀÌ Àû¿ë ¸ó½ºÅÍ
	int 			AssassinEyeParam;		//¾î¼¼½Å¾ÆÀÌ Àû¿ë ¸ó½ºÅÍ


	////////////////////// Å¬·£ //////////////////////////
	int				ClanInfoNum;			//Å¬·£ Á¤º¸ ¹øÈ£
	DWORD			dwClanInfoTime;					//Å¬·£ Á¤º¸ ¹ÞÀº ½Ã°£

	int				iBellatraCrown;
	BOOL			bBlessCastleCrown;


	int				dwVipBit;
	DWORD			dwVipTime;

	Map				* pcMap;
	User			* pcKillerData;
	Unit			* pcBellatraKiller;
	Map				* pcMapSpawn;

	POINT3D			HoSkillPos;				//½ºÅ³ °ü·Ã ÁÂÇ¥
	int				iPetID;
	int				bAggressive;

	Unit			* pcFocusingTarget;
	int				iFocusingLastID;

	int				dwExclusiveNum;				//ÆÄÆ¼ ÇÃ·¢
	int				iBellatraRoom;				//ÆÄÆ¼ ÆÄ¶ó¸ÞÅÍ

	int				CaravanSerial;			// ¶À½ÇÊÞÒ»¼ÒµÄOBJÖµ
	DWORD			CaravanTime;			// ¶À½ÇÊÞÒ»¼ÒµÄÊ±¼ä
	int				CaravanMode;			// ¶À½ÇÊÞÊÇ·ñ¸úËæ
	DWORD			HoSkillDeathTime;		// ÍöÁéÖ®ÖäÊ±¼ä

	int				PlaySlowCount;		//´À·ÁÁö´Â °ø°Ý ¹ÞÀ½
	int				PlaySlowSpeed;		//´À·ÁÁö´Â ¼Óµµ
	int				iStunTimeLeft;
	int				PlayStopCount;		//¿òÁ÷ÀÓÀÌ ¸ØÃã Ä«¿îÅÍ
	short			PlayHolyMind[2];	//µ¥¹ÌÁö ¾àÈ­ ±â´É ( [0] °¨¼ÒµÈ µ¥¹ÌÁö% [1] À¯Áö½Ã°£ )
	short			PlayHolyPower[2];	//µ¥¹ÌÁö °­È­ ±â´É ( [0] °­È­µÈ µ¥¹ÌÁö% [1] À¯Áö½Ã°£ )
	short			PlayPoison[2];		//µ¶¿¡ °ø°Ý ( [0] °¨¼ÒµÉ µ¥¹ÌÁö [1] ÇØµ¶½Ã°£ )
	short			PlayFire[2];
	short			PlayHolyIncantation[2];	//¸ó½ºÅÍ ÇöÈ¤ ½ºÅ³ ( [0] ÀÓ½Ã [1] À¯Áö½Ã°£ )
	int				PlayVanish;			//¹è´Ï½¬ ½ºÅ³Àû¿ë
	int				PlayCurseQuest;		//ÀúÁÖ Äù½ºÆ® ¸ðµå
	int				PlayVague;			//º¸±× ½ºÅ³Àû¿ë

	int				iDistortion;
	int				PlayInvincible;		//¹«Àû ¾ÆÀÌÅÛ
	int				PlayWeb;			//Ö©ÖëÍø
	int				PlayDarkBoss;		//ÊÇ·ñ½øÈëBOSSµØÍ¼

	BOOL			CheckFlagIce;		//¾ÆÀÌ½º ¼Ó¼º ÇÃ·¡±×°ª

	int				DispPoison;			//µ¶°¨¿° Ç¥½Ã
	int				DispFire;			//»ðÉËº¦

	DWORD			dwConcentrationTime;	//»áÐÄÒ»»÷
	DWORD			dwSwiftAxeTime;			//´ÌÉ±Ö®¸«
	DWORD			dwBetserkerTime;		//·è¿ñÅ­ºð
	DWORD			dwB_Berserker_Time;		//ÖÚÉñÖ®Å­
	DWORD			dwE_Shield_UseTime;		//¼«¹â»¤¶Ü
	DWORD			dwP_Absorb_UseTime;		//Áé¹â»¤Ìå
	DWORD			dwAutomation_Time;		//Áé¹â·ÉÑï
	DWORD			dwMetal_Armor_Time;		//½ðÊôÖØ¼×
	DWORD			dwSpark_Shield_Time;	//·ÀÓùµç²¨
	DWORD			dwMagnetic_Sphere_Time;	//´ÅÐÔÇòÌå
	DWORD			dwH_Sonic_Time;			//¿ìËÙ´ò»÷
	DWORD			dwP_Enhence_Time;		//Õ½Éñ×£¸£
	DWORD			dwFalcon_Time;			//Áé»êÖ®Ó¥
	DWORD			dwGolden_Falcon_Time;	//»Æ½ðÁÔÓ¥
	DWORD			dwForceOfNatureTime;	//×ÔÈ»Ö®¹â
	DWORD			dwAmplified_Time;		//Ç±ÄÜ¼¤·¢
	DWORD			dwWindy_Time;			//×·Ãü¾¢·ç
	DWORD			dwT_Of_Valhalla_Time;	//Õ½ÀõÅØÏø
	DWORD			dwHallOfValhallaTime;	//Íß¶û¹þÀ­Ö®¹â
	DWORD			dwFrost_Javelin_Time;	//±ùËª±êÇ¹
	DWORD			dwTalaria_Time;			//ÇáÎè·ÉÑï
	DWORD			dwHolyBody_Time;		//Ê¥¹â»¤Ìå
	DWORD			dwHoly_Valor_Time;		//ÉñÁ¦ÖØ»÷
	DWORD			dwDrastic_Spirit_Time;	//ÌìÓÓÉñîø
	DWORD			dwD_Inhalation_Time;	//Ê¥ÁéÖ®Îü
	DWORD			dwGodly_Shield_Time;	//¾´ÉñÖ®¶Ü
	DWORD			dwGod_Bless_Time;		//ÉÏµÛ×£¸£
	DWORD			dwH_Benedic_Time;		//ÍöÁéÖ®Öä
	DWORD			dwZenith_Time;			//¼¯ºÏÖ®Êõ
	DWORD			dwEnergy_Shield_Time;	//Ä§·¨ÊØ»¤
	DWORD			dwSpirit_Elemental_Time;//Áé»êÕÙ»½
	DWORD			dwDancing_Sword_Time;	//ÔªËØÖ®½£
	DWORD			dwT_Anima_Time;			//Ê¥¹â·¨Õó
	DWORD			dwDancing_Sword_Param;	
	DWORD			dwHoly_Reflection_Time;	//ÉñÊ¥·´Éä
	DWORD			dwVirtual_Life_Time;	//ÉñÊ¥Ö®¹â
	DWORD			dwSummon_Muspell_Time;	//ÉñÊ¥ÌìÊ¹
	DWORD			dwB_Krishna_Time;		//ÌìÅ®É¢»¨
	DWORD			dwAlasTime;				//¾«ÉñÖ®Á¦
	DWORD			dwInpesTime;			//Ãô½Ý´óÊ¦
	DWORD			dwAdvent_Migal_Time;	//Âõ¿Ë¶û
	DWORD			dwRainmaker_Time;		//ÆíÓêÊ¦
	DWORD			dwAdvent_Midranda_Time;	//Ã×µÂÀ¼´ï
	DWORD			dwCreed_Time;			//ÖäÊõÐÅÑö

	DWORD			dwWingEffectCode;		//³á°òÐ§¹û´úÂë

	int				iAreaDamageArea;

	int				EventAttackCount;		//ÀÌº¥Æ® °ø°Ý Ä«¿îÅÍ ( »Ð¸ÁÄ¡ µî )
	DWORD			dwEventAttackParam;

	short			sAddColorEffect[4];		//»ö»óÃß°¡
	int				DispLifeBar;			//»ý¸í¹Ù Ç¥½Ã

	DWORD			dwLastUpdateTime;
	DWORD			dwLastRecvAttackTime;	//¸¶Áö¸· °ø°Ý ¹ÞÀº ½Ã°£

	int				TryAttackCount;			//°ø°Ý½Ãµµ È½¼ö

	///////////////// Force Orb ////////////////////
	DWORD			dwForceOrbCode;			//Æ÷½º¿Àºê Àû¿ë ÄÚµå
	DWORD			dwForceOrbTime;			//Æ÷½º¿Àºê À¯Áö½Ã°£

	// ¹ÚÀç¿ø - µ¥¹ÌÁö ºÎ½ºÅÍ(»ý¸í·Â)
	DWORD			dwLifeBoosterCode; // ¹ÚÀç¿ø - ºÎ½ºÅÍ ¾ÆÀÌÅÛ(»ý¸í·Â) ÄÚµå
	DWORD			dwLifeBoosterTime; // ¹ÚÀç¿ø - ºÎ½ºÅÍ ¾ÆÀÌÅÛ(»ý¸í·Â) À¯Áö½Ã°£
	// ¹ÚÀç¿ø - µ¥¹ÌÁö ºÎ½ºÅÍ(±â·Â)
	DWORD			dwManaBoosterCode; // ¹ÚÀç¿ø - ºÎ½ºÅÍ ¾ÆÀÌÅÛ(±â·Â) ÄÚµå
	DWORD			dwManaBoosterTime; // ¹ÚÀç¿ø - ºÎ½ºÅÍ ¾ÆÀÌÅÛ(±â·Â) À¯Áö½Ã°£
	// ¹ÚÀç¿ø - µ¥¹ÌÁö ºÎ½ºÅÍ(±Ù·Â)
	DWORD			dwStaminaBoosterCode; // ¹ÚÀç¿ø - ºÎ½ºÅÍ ¾ÆÀÌÅÛ(±Ù·Â) ÄÚµå
	DWORD			dwStaminaBoosterTime; // ¹ÚÀç¿ø - ºÎ½ºÅÍ ¾ÆÀÌÅÛ(±Ù·Â) À¯Áö½Ã°£

	//¹ÚÀç¿ø - ÀÌÅÍ³Î ¶óÀÌÇÁ, ÆäÀÌÆ² ¿¡Áö, ¾î¹öÆ® ½ºÅ©·Ñ(°ø¼º ¾ÆÀÌÅÛ ½ºÅ©·Ñ)
	DWORD			dwSiegeItem_ScrollCode_Eternal;			// ÀÌÅÍ³Î ¶óÀÌÇÁ
	DWORD			dwSiegeItem_ScrollTime_Eternal;			
	DWORD			dwSiegeItem_ScrollCode_Fatal;			//ÆäÀÌÆ² ¿¡Áö
	DWORD			dwSiegeItem_ScrollTime_Fatal;		
	DWORD			dwSiegeItem_ScrollCode_Avert;			//¾î¹öÆ® ½ºÅ©·Ñ
	DWORD			dwSiegeItem_ScrollTime_Avert;	

	// Àåº° - ½ºÅ³ µô·¹ÀÌ
	DWORD			dwSkillDelayCode;
	DWORD			dwSkillDelayTime;

	////////////// °ø¼º¸ðµå State ¹é¾÷ //////////////

	ECharacterType	iCharacterType;
	int				iSpecialType;
	DWORD			iClanID;

	int				iHPBlocks;
	CurMax			sHPBlocks;
	CurMax			sVirtualHP;

	IMinMax			sHPLong;

	short			sBlessCastle_Damage[2];
	short			sBlessCastle_Param[2];
	SIceFootInfo	m_IceFootInfo[ICE_FOOT_COUNT_MAX];

	AttackDamageData	* psaDamageUsersData;
	AttackDamageData	* psaSiegeWarDataList;

	Unit();
	~Unit();
	void Init();
	int Close();
	EAnimationType GetAnimation() { return psModelAnimation ? psModelAnimation->iType : ANIMATIONTYPE_None; }
	BOOL IsDead() { return (GetAnimation() == ANIMATIONTYPE_Die); }
	int SetPosi( int x, int y, int z , int angX, int angY, int angZ );
	int SetTargetPosi( int x, int z );
	int SetTargetPosi2( int x, int z );
	int SetNextTarget( int x, int y, int z );
	int MoveAngle( int step );
	int MoveAngle2( int step );
	int ChangeMoveMode();
	int SetAction(int nAction);
	int ChangeMotion(int Motion , int DpMode=0);
	int AutoChangeTalkMotion( int TalkModeType);
	int FindActionFromFrame( int sframe);
	int SetDinaPattern(smDPAT	*lpDPat);
	int SetDinaPattern2(smDPAT	*lpDPat);
	int SetPattern(smPAT3D *pat);
	int SetPattern2(smPAT3D *pat);
	int SavePlayBuff();
	int SavePlayBuff2();
	int Main();
	int CheckShootingTest(Unit *lpChrTarget);
	int SetLoadPattern( char *szName );
	void HandleUnitDataBuffer(char * pBuffer, int iDelayTime, int iSleep);
	int SetMotionFromCode(DWORD MotionCode);
	int FindMotionCountFromCode(DWORD MotionCode);
	int SendTransAttack(Unit *lpChar , User *pcUser , int AttackCode , int Add_Damage=0 , int Resistance=0);
	int PlayAttackFromPosi( int ex, int ey, int ez, int Dist ,int attack=TRUE );
	int ClearSkillToPlay(DWORD SkillCode);
	EMapID GetMap();
};


#define CHRMOTION_EXT		10

#define hvPOSI_RHAND	0x0001
#define hvPOSI_LHAND	0x0002


#define CHRMOTION_STATE_SOMETIME	0x130


#define CHRMOTION_STATE_TALK_AR			0x400
#define CHRMOTION_STATE_TALK_E			0x410
#define CHRMOTION_STATE_TALK_OH			0x420
#define CHRMOTION_STATE_TALK_EYE		0x430
#define CHRMOTION_STATE_TALK_BLANK		0
#define CHRMOTION_STATE_TALK_SMILE		0x440
#define CHRMOTION_STATE_TALK_GRUMBLE	0x450
#define CHRMOTION_STATE_TALK_SORROW		0x460
#define CHRMOTION_STATE_TALK_STARTLED	0x470
#define CHRMOTION_STATE_TALK_NATURE		0x480
#define CHRMOTION_STATE_TALK_SPECIAL	0x490


//Å©¸®Æ¼ÄÃ ¼½¼Ç
extern CRITICAL_SECTION	cLoadSection;

//Á¦°Å
int smDPAT_Delete( smDPAT *dPat );


//ÆÐÅÏ¹öÆÛ¸¦ ÃÊ±âÈ­
int InitPatterns();
//ÆÐÅÏ¹öÆÛ¸¦ ¸»±âÈ­
int ClosePatterns();
//Ä³¸¯ÅÍ¿¡ ÆÐÅÏÀ» ¼³Á¤
int SetLoadPattern(Unit *smChar , char *szName , POINT3D *Posi , POINT3D *Angle );
//Ä³¸¯ÅÍ¿¡ ÆÐÅÏÀ» ¼³Á¤2
int SetLoadPattern(Unit *smChar , char *szName , char *szName2 , POINT3D *Posi , POINT3D *Angle );

int	AddLoaderPattern(Unit *lpChar , char *szName , char *szName2=0 );
//¹è°æÀ» »õ ¾²·¹µå¿¡ ÅëÇÏ¿© ·Îµå ÇÑ´Ù
int AddLoaderStage( smSTAGE3D *lpStage , char *szName );

class scITEM {

public:
	DWORD	Head;

	int		DisplayFlag;		//È­¸é Ãâ·Â ¿©ºÎ

	int		Flag;
	int		pX,pY,pZ;

	char	szModelName[64];
	char	szName[64];

	void	*lpStgArea;			//Á¸ÀçÇÏ´Â ±¸¿ª

	smPAT3D	*Pattern;
	smDPAT  *lpDinaPattern;		//´ÙÀÌ³ª¹Í ÆÐÅÏ Æ÷ÀÎÅÍ (ÆÐÅÏÀÇ °ü¸®ÀÚ)

	int		PatLoading;

	int		ItemCode;

	DWORD	dwLastTransTime;		// ¸¶Áö¸·À¸·Î Àü¼ÛµÈ ½Ã°£

	int		ServerCode;				//ÇØ´ç Ä³¸¯ÅÍ ¼­¹ö ÄÚµå

	POINT3D	RendPoint;				//·»´õ¸µµÈ 2D ÁÂÇ¥ ( x,y,z )


	POINT3D Posi;
	POINT3D Angle;

};

int	AddLoaderItem( scITEM *lpItem , char *szName );

extern smPATTERN smBipPattern;
extern smPATTERN smPattern;

extern int	SkillChargingFlag;			//½ºÅ³ Â÷Â¡ ÇÃ·¢

extern TRANS_SKIL_ATTACKDATA	Trans_SplashCharList;		//ÆÃ°Ü¼­ ¸Â´Â °ø°Ý µ¥ÀÌÅ¸ ÀÓ½ÃÀúÀå


extern int CastleBattleZone_LineZ;
extern int CastleBattleZone_DoorLineZ;		//¼º¹® ÀÔ±¸
extern int CastleBattleZone_DoorLineX[2];	//¼º¹® ÀÔ±¸
extern int CastleBattleZone_BridgeZ;		//´Ù¸® ÀÔ±¸
extern int CastleSoulFountain_Area[4];		//¿µÈ¥ÀÇ»ùÅÍ


#endif