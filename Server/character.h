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


#define PLAYSERVER_SENDCOUNTER		(70*1)				//1�ʴ�

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



//////////// ��е���ܱ�� //////////////
#define SKILL_PLAY_EXTREME_SHIELD	0x1A //���⻤��
#define SKILL_PLAY_MECHANIC_BOMB	0x1B
#define	SKILL_PLAY_PHYSICAL_ABSORB	0x1C //��⻤��
#define	SKILL_PLAY_POISON_ATTRIBUTE	0x1D

#define	SKILL_PLAY_GREAT_SMASH		0x2A
#define	SKILL_PLAY_MAXIMIZE			0x2B //����ר��
#define	SKILL_PLAY_AUTOMATION		0x2C //������
#define	SKILL_PLAY_SPARK			0x2D

#define	SKILL_PLAY_METAL_ARMOR		0x3A //�����ؼ�
#define	SKILL_PLAY_GRAND_SMASH		0x3B //�ǹ����
#define	SKILL_PLAY_SPARK_SHIELD		0x3C //�����粨

#define	SKILL_PLAY_IMPULSION		0x4A
#define	SKILL_PLAY_COMPULSION		0x4B
#define	SKILL_PLAY_MAGNETIC_SPHERE	0x4C //��������
#define	SKILL_PLAY_METAL_GOLEM		0x4D //�ռ���е

#define	SKILL_PLAY_LANDMINNING		0x5A //��������
#define	SKILL_PLAY_H_SONIC			0x5B //���ٴ��
#define	SKILL_PLAY_R_SMASH			0x5C //����֮��
#define	SKILL_PLAY_P_ENHENCE		0x5D //ս��ף��


//////////// ��ʿ���ܱ�� //////////////
#define SKILL_PLAY_RAVING			0x1A //���ر���
#define SKILL_PLAY_IMPACT			0x1B //��׼֮��

#define SKILL_PLAY_TRIPLE_IMPACT	0x2A //�������
#define SKILL_PLAY_BRUTAL_SWING		0x2B //��������
#define SKILL_PLAY_ROAR				0x2C //����ŭ��
#define SKILL_PLAY_RAGEOF_ZECRAM	0x2D //

#define SKILL_PLAY_CONCENTRATION	0x3A
#define SKILL_PLAY_AVANGING_CRASH	0x3B
#define SKILL_PLAY_SWIFT_AXE		0x3C
#define SKILL_PLAY_BONE_SMASH		0x3D

#define SKILL_PLAY_DESTROYER		0x4A
#define SKILL_PLAY_BERSERKER		0x4B //���ŭ��
#define SKILL_PLAY_CYCLONE_STRIKE	0x4C

#define	SKILL_PLAY_D_HIT			0x5A
#define	SKILL_PLAY_P_DASH			0x5B //��Ұ���
#define	SKILL_PLAY_M_BLOW			0x5C //����ն��
#define	SKILL_PLAY_B_BERSERKER		0x5D //����֮ŭ

//////////// ǹ������ //////////////
#define SKILL_PLAY_PIKEWIND			0x1A
#define SKILL_PLAY_CRITICAL_HIT		0x1B //�������
#define SKILL_PLAY_JUMPING_CRASH	0x1C

#define SKILL_PLAY_GROUND_PIKE		0x2A
#define SKILL_PLAY_TORNADO			0x2B
#define SKILL_PLAY_EXPANSION		0x2C

#define SKILL_PLAY_VENOM_SPEAR		0x3A
#define SKILL_PLAY_VANISH			0x3B //����֮��
#define SKILL_PLAY_CHAIN_LANCE		0x3C //����֮ǹ

#define SKILL_PLAY_ASSASSIN_EYE		0x4A //��ɱ֮��
#define SKILL_PLAY_CHARGING_STRIKE	0x4B
#define SKILL_PLAY_VAGUE			0x4C //Ӱ��֮��
#define SKILL_PLAY_SHADOW_MASTER	0x4D

#define	SKILL_PLAY_D_REAPER			0x5A //�������
#define	SKILL_PLAY_F_SPEAR			0x5B //��ǹ��Ϯ
#define	SKILL_PLAY_AMPLIFIED		0x5C //Ǳ�ܼ���
#define	SKILL_PLAY_SS_ATTACK		0x5D


//////////// ���ּ��ܱ�� //////////////

#define SKILL_PLAY_SCOUT_HAWK		0x1A
#define SKILL_PLAY_WIND_ARROW		0x1B
#define SKILL_PLAY_PERFECT_AIM		0x1C

#define SKILL_PLAY_FALCON			0x2A //���֮ӥ
#define SKILL_PLAY_ARROWOF_RAGE		0x2B
#define SKILL_PLAY_AVALANCHE		0x2C //ѩ��֮��

#define SKILL_PLAY_ELEMENTAL_SHOT	0x3A //Ԫ�ع���
#define SKILL_PLAY_GOLDEN_FALCON	0x3B //�ƽ���ӥ
#define SKILL_PLAY_BOMB_SHOT		0x3C //����֮��
#define SKILL_PLAY_PERFORATION		0x3D

#define SKILL_PLAY_RECALL_WOLVERIN	0x4A //�ٻ�ѩ��
#define SKILL_PLAY_PHOENIX_SHOT		0x4B
#define SKILL_PLAY_FORCE_OF_NATURE	0x4C //��Ȼ֮��

#define	SKILL_PLAY_E_SHOT			0x5A //����֮��
#define	SKILL_PLAY_S_ROPE			0x5B //����֮��
#define	SKILL_PLAY_N_SPLASH			0x5C
#define	SKILL_PLAY_C_TRAP			0x5D //����֮��


////////////// �������ܱ�� //////////////
#define SKILL_PLAY_SWORD_BLAST		0x1A
#define SKILL_PLAY_HOLY_BODY		0x1B //ʥ�⻤��
#define SKILL_PLAY_DOUBLE_CRASH		0x1C

#define SKILL_PLAY_HOLY_VALOR		0x2A
#define SKILL_PLAY_BRANDISH			0x2B
#define SKILL_PLAY_PIERCING			0x2C
#define SKILL_PLAY_DRASTIC_SPIRIT	0x2D

#define SKILL_PLAY_DIVINE_INHALATION	0x3A //ʥ��֮��
#define SKILL_PLAY_HOLY_INCANTATION		0x3B
#define SKILL_PLAY_GRAND_CROSS			0x3C

#define SKILL_PLAY_DIVINE_PIERCING		0x4D
#define SKILL_PLAY_GODLY_SHIELD			0x4B //����֮��
#define SKILL_PLAY_GODS_BLESS			0x4C //�ϵ�ף��
#define SKILL_PLAY_SWORD_OF_JUSTICE		0x4A

#define	SKILL_PLAY_S_BREAKER		0x5A //�������
#define	SKILL_PLAY_C_MOON			0x5B //�����ػ�
#define	SKILL_PLAY_S_BLADE			0x5C //�ϵ��ػ�
#define	SKILL_PLAY_H_BENEDIC		0x5D //����֮��


////////////// ħǹ�ּ��ܱ�� ///////////////
#define SKILL_PLAY_SHIELD_STRIKE	0x1A
#define SKILL_PLAY_FARINA			0x1B
#define SKILL_PLAY_VIGOR_SPEAR		0x1C

#define SKILL_PLAY_WINDY			0x2A
#define SKILL_PLAY_TWIST_JAVELIN	0x2B
#define SKILL_PLAY_SOUL_SUCKER		0x2C
#define SKILL_PLAY_FIRE_JAVELIN		0x2D

#define SKILL_PLAY_SPLIT_JAVELIN		0x3A
#define SKILL_PLAY_TRIUMPH_OF_VALHALLA	0x3B //ս������
#define SKILL_PLAY_LIGHTNING_JAVELIN	0x3C
#define SKILL_PLAY_STORM_JAVELIN		0x3D //������

#define SKILL_PLAY_HALL_OF_VALHALLA		0x4A //�߶�����֮��
#define SKILL_PLAY_X_RAGE				0x4B
#define SKILL_PLAY_FROST_JAVELIN		0x4C //˪����ǹ
#define SKILL_PLAY_VENGEANCE			0x4D

#define	SKILL_PLAY_TALARIA			0x5A //�������
#define	SKILL_PLAY_G_COUP			0x5B //���Ʊ�ǹ
#define	SKILL_PLAY_S_ARCUDA			0x5C //������
#define	SKILL_PLAY_S_FEAR			0x5D //����ͻϮ


////////////// ��˾���ܱ�� ///////////////
#define SKILL_PLAY_HEALING			0x1A
#define SKILL_PLAY_HOLY_BOLT		0x1B
#define SKILL_PLAY_MULTI_SPARK		0x1C
#define SKILL_PLAY_HOLY_MIND		0x1D

#define	SKILL_PLAY_DIVINE_LIGHTNING	0x2A
#define	SKILL_PLAY_HOLY_REFLECTION	0x2B //��ʥ����
#define	SKILL_PLAY_GREAT_HEALING	0x2C

#define	SKILL_PLAY_VIGOR_BALL		0x3A
#define	SKILL_PLAY_RESURRECTION		0x3B //����֮��
#define	SKILL_PLAY_EXTINCTION		0x3C //ʥ��֮��
#define	SKILL_PLAY_VIRTUAL_LIFE		0x3D //��ʥ֮��

#define	SKILL_PLAY_GLACIAL_SPIKE	0x4A
#define	SKILL_PLAY_REGENERATION_FIELD	0x4B //��������
#define	SKILL_PLAY_CHAIN_LIGHTNING	0x4C
#define	SKILL_PLAY_SUMMON_MUSPELL	0x4D //��ʥ��ʹ

#define	SKILL_PLAY_S_IMPACT			0x5A //��ʥ�粨
#define	SKILL_PLAY_P_ICE			0x5B
#define	SKILL_PLAY_S_PRMIEL			0x5C //����ѩ
#define	SKILL_PLAY_B_KRISHNA		0x5D //��Ůɢ��


////////////// ħ��ʦ���ܱ�� ///////////////
#define SKILL_PLAY_AGONY			0x1A
#define SKILL_PLAY_FIRE_BOLT		0x1B
#define SKILL_PLAY_ZENITH			0x1C //����֮��
#define SKILL_PLAY_FIRE_BALL		0x1D

#define SKILL_PLAY_COLUMN_OF_WATER	0x2A
#define SKILL_PLAY_ENCHANT_WEAPON	0x2B //Ԫ��֮��
#define SKILL_PLAY_DEAD_RAY			0x2C

#define SKILL_PLAY_ENERGY_SHIELD	0x3A //ħ���ػ�
#define SKILL_PLAY_DIASTROPHISM		0x3B
#define SKILL_PLAY_SPIRIT_ELEMENTAL	0x3C //����ٻ�
#define SKILL_PLAY_DANCING_SWORD	0x3D //Ԫ��֮��

#define SKILL_PLAY_FIRE_ELEMENTAL	0x4A //��������
#define SKILL_PLAY_FLAME_WAVE		0x4B
#define SKILL_PLAY_DISTORTION		0x4C
#define SKILL_PLAY_METEO			0x4D //��ʯ�ٻ�

#define	SKILL_PLAY_SILRAPHIM		0x5A //���ǻ���
#define	SKILL_PLAY_V_TENUS			0x5B //��С֮��
#define	SKILL_PLAY_P_IGNIS			0x5C //��ʥϴ��
#define	SKILL_PLAY_T_ANIMA			0x5D //ʥ�ⷨ��

////////////// �̿ͼ��ܱ�� ///////////////
#define SKILL_PLAY_STRINGER			0x1A //�̻�
#define SKILL_PLAY_RUNNING_HIT		0x1B //����
#define SKILL_PLAY_WIELD_MASTERY	0x1C //ǿ������
#define SKILL_PLAY_WISP				0x1D //���㹥��

#define SKILL_PLAY_VENOM_THORN		0x2A //��������
#define SKILL_PLAY_ALAS				0x2B //����֮��
#define SKILL_PLAY_SOUL_SHOCK		0x2C //�����
#define SKILL_PLAY_BLADE_MASTERY	0x2D //������ʦ

#define SKILL_PLAY_SORE_SWORD		0x3A //�ɽ�֮��
#define SKILL_PLAY_BEAT_UP			0x3B //��ն
#define SKILL_PLAY_INPES			0x3C //���ݴ�ʦ
#define SKILL_PLAY_BLIND			0x3D //��ä

#define SKILL_PLAY_FROST_WIND		0x4A //����֮��
#define SKILL_PLAY_FATAL_MASTERY	0x4B //��������
#define SKILL_PLAY_POLLUTE			0x4C //����֮��
#define SKILL_PLAY_PASTING_SHADOW	0x4D //Ӱ������

#define SKILL_PLAY_SHADOW_BOMB		0x5A //Ӱ�ӻ���
#define SKILL_PLAY_RISING_SLASH		0x5B //����ն
#define SKILL_PLAY_VIOLENT_STUB		0x5C //������β
#define SKILL_PLAY_SHADOW_STORM		0x5D //�籩֮��

////////////// �������ܱ�� ///////////////
#define SKILL_PLAY_DARK_BOLT		0x1A //��������
#define SKILL_PLAY_DARK_WAVE		0x1B //���ڲ���
#define SKILL_PLAY_INERTIA			0x1C //�����׻�
#define SKILL_PLAY_INNER_PEACE		0x1D //����ƽ��

#define SKILL_PLAY_SPIRITUAL_FLARE	0x2A //��������
#define SKILL_PLAY_SPIRITUAL_MANACLE 0x2B //������
#define SKILL_PLAY_CHASING_HUNT		0x2C //��ȡ
#define SKILL_PLAY_ADVENT_MIGAL		0x2D //���˶�

#define SKILL_PLAY_RAINMAKER		0x3A //����ʦ
#define SKILL_PLAY_LAND_OF_GHOST	0x3B //½�����
#define SKILL_PLAY_HAUNT			0x3C //����ػ�
#define SKILL_PLAY_SCRATCH			0x3D //ץ��

#define SKILL_PLAY_CRIMSON_KNIGHT	0x4A //��Ѫ֮ҹ
#define SKILL_PLAY_JUDGEMENT		0x4B //����
#define SKILL_PLAY_ADVENT_MIDRANDA	0x4C //�׵�����
#define SKILL_PLAY_MOURNING_PRAY	0x4D //���ն���

#define SKILL_PLAY_CREED			0x5A //��������
#define SKILL_PLAY_PRESS_DEITY		0x5B //����֮��
#define SKILL_PLAY_PHANTOM_NAIL		0x5C //����֮צ
#define SKILL_PLAY_OCCULT_LIFE		0x5D //�߼�����

///////////// ��� Ȯ�� //////////////////
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
	smPAT3D	*Pattern2;			//�Ӹ� ����
	smPAT3D *AnimPattern;

	smPAT3D *TalkPattern;		// ǥ�� ����. ( ���̳��� ������ ini �� ���� lpDinaPattern �Ǵ� lpDinaPattern2 )

	smDPAT  *lpDinaPattern;		//���̳��� ���� ������ (������ ������)
	smDPAT  *lpDinaPattern2;	//���̳��� ���� ������ �Ӹ�(������ ������)

	smDPAT  *lpDinaLeftPattern;		//���� ����
	smDPAT  *lpDinaRightPattern;	//������ ����

	smCHARTOOL	HvLeftHand;		//�޼տ� ���� ����
	smCHARTOOL	HvRightHand;	//�����տ� ���� ����

	smMATRIX	HvLeftHand_Matrix;	//�޼� ���� ��� ����
	smMATRIX	HvRightHand_Matrix; //������ ���� ��� ����

	int		Rend_HvLeftHand;		//���� ������ ����
	int		Rend_HvRightHand;		//���� ������ ����


	smOBJ3D	*BackObjBip[5];		//���� ���� ����
	smOBJ3D	*AttackObjBip;		//���� �е� ������Ʈ
	smOBJ3D	*ShieldObjBip;		//���� �е� ������Ʈ
	smOBJ3D *DaggerObjBip;

	int		AttackToolRange;	//���� �����Ÿ�
	int		AttackAnger;
	int		AttackIce;			//���� ���� ����


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

	int		PatWidth;		//ĳ���� ����
	int		PatHeight;		//ĳ���� ����

	int		PatSizeLevel;	//ĳ���� ũ�� �ܰ� ( 0 ~ 3 )

	int		OverLapPosi;	//�ٸ� ĳ���Ϳ� ��ġ�� ��ħ
	int		OverLapPosi2;	//�ٸ� ĳ���Ϳ� ��ġ�� ��ħ
	Unit	*lpCharOverLap;	//��ģ ĳ������ ����Ʈ

	POINT3D Posi;

	union
	{
		struct
		{
			POINT3D Angle;
		};

		Point3D sAngle;
	};

	int		MoveMode;	//�̵� ��� ( 0 - �ȱ� 1-�޸��� )
	int		MoveFlag;
	int		MoveCnt;	// ��Ž� ���� ����Ÿ�� ������� �ڵ� �̵��Ҷ� �Ÿ� ���� ī����
	int		tx,tz;		// ��ǥ �̵� ��ǥ
	int		TargetMoveCount;	//��ǥ �̵� ��ǥ ī����
	int		WaterHeight;		//�� ����

	DWORD	dwActionItemCode;	//�� �����ӿ� ���õ� �ڵ�
	DWORD	dwItemSetting;		//������ ���� ���( 0-���� ���� 1-�����ʵ� ���� )
	DWORD	dwActionItemTwoHand;	//��� ���� ýũ

	short	wStickItems[4];		//���� ������ ��ȣ

	int		ShootingMode;	//�߻��� ���� ��� ( TRUE )
	int		ShootingFlag;	//���� �߻����� ����
	int		ShootingKind;	//�߻� ����
	POINT3D	ShootingPosi;	//�߻� ��ġ

	POINT3D	ShootingAngle;	//�߻� ����
	int		ShootingCount;	//�߻� ī����

	Unit	*chrAttackTarget;	//���� ��ǥ ĳ����
	int		AttackCritcal;		//ũ��Ƽ�� ���� ����
	int		AttackCriticalCount;//ũ��Ƽ�� ���� ī���� ( ���� ���ݽ� )
	int		AttackExp;			//���ݽ� ����ġ
	int		AttackSkil;			//��ų ���� �ڵ�
	int		AttackEffect;		//���ݽ� Ư�� ����Ʈ ǥ��
	int		LastSkillParam;		//�ֱ� ��ų���� ���� �ڵ� ( ī����ī�� ���� ���������� �߰� ) 

	int		RecvExp;			//����ġ �ο� ����

	POINT3D	ptNextTarget;	//���� �̵� ��ǥ
	Point3D		sSpawnPosition;
	int		iLureDistance;
	int		TragetTraceMode;	//���� ��� �� (������� )

	POINT3D	PosBeginMove;		//�̵� ���۽��� ��ǥ
	DWORD	PosBeginCount;

	DWORD	dwNextMotionCode;	//���� ���� ����

	int		ChargingFlag;		//��¡ �÷�

	DWORD	TalkFrame;		// ǥ�� ������
	DWORD	TalkSoundSum;

	SMotionStEndInfo	FrameInfo;

	int			action;
	UINT		iFrame;
	int			FrameCnt;
	int			FrameStep;		//������ �ٲ� ��
	int			MoveSpeed;		//�̵� ������ ��
	int			AttackSpeed;	//���� �ӵ�

	int		ActionPattern;	// ������ ����

	DWORD	dwEventFrameExt[4];	//�̺�Ʈ ������ Ȯ��

	int		iAliveCounter;
	int		iDeathCounter;
	int		AutoMoveStep;	//�ڵ� �̵��� ���� ī����
	short	sMoveStepCount[2];		//�̵� ���� ���� ������

	int		Counter;
	int		iFrameTimer;

	int		RendSucess;				//ȭ����� ������ ���� ����
	RECT	RendRect2D;				//�������� 2D ��ǥ ����
	POINT3D	RendPoint;				//�������� 2D ��ǥ ( x,y,z )
	int		FlagShow;				//ȭ��ǥ�� �÷� ( 0 - ȭ�� ��� ���� )

	//ä��
	char	szMessage[256];		//ä�� ���ڿ�
	DWORD	dwMessageEndTime;		//ä�� ���ڸ� ǥ�� ����ð� ���

	//����
	char	szTradeMessage[128];	//���� �޼��� ���ڿ�
	DWORD	dwTradeMsgCode;			//���� �޼��� �ڵ�

	int		Damge;					//��ʾ���˺�ֵ
	DWORD	dwDamgeTimer;			//�˺�����ʾ��ʱ��
	int		DmgBlendValue;			//����ֵ
	short	DmgType[2];				//��������0 ��ɫ,1�Ƿ񱩻�


	BYTE	baUnitBufferNew[0x2000];
	int		uUnitInfoSize;

	//��� ����
	int		ServerCode;				//�ش� ĳ���� ���� �ڵ�

	PlayBuffer	sPlayBuff[PLAYBUFF_SIZE];
	int			iPlayBuffCount;
	int			PlayBuffPosi_End;

	DWORD		dwLastActiveTime;
	int			LastPlayDataType;

	CharacterData sCharacterData;				//���� ����
	UnitInfo	sUnitInfo;

	int		AnimDispMode;			//���� ǥ�� ��� ( 0-��� ǥ�� 1-�Ѱ��� ǥ��)
	int		PatDispMode;			//���� ǥ�� ��� ( 0-��ǥ�� 1-���� 2-���길 3-��� )

	int		MotionSelectFrame;		//������ �������� ����� ��ȣ ( 0 , 1 ) 

	smMODELINFO		*smMotionInfo;	//���� ���ۺ� �����Ӱ� ����
	smMODELINFO		*smMotionInfo2;	//���� 2���� ��� 1���𵨿��� ����Ÿ�� ���°�� 2������ ����Ÿ�� ��� 
	ModelAnimation	*psModelAnimation;

	smMODELINFO		*lpTalkModelParent;
	ModelAnimation	*lpTalkMotionInfo;


	DWORD			OldMotionState;			//������ ��� �Ӽ� ����
	DWORD			dwTarget;				//������ ���ΰ��� �ܳ��� �׼��ϰ�� 

	User			* pcOwner;

	int				nCheckChar;

	User			* pcFocusTarget;
	Unit			* pcAttackTarget;
	int				AttackUserFlag;
	DWORD			dwIgnoreOthersTime;

	ID				lExclusiveTargetID;
	User			* lpLinkPlayInfo;		//����� �÷��̾�
	Unit			* pcExclusiveUnitTarget;

	User			* pcLastAttacker;
	int				iDamageLastAttacker;
	DWORD			dwExpAttackTime;
	TRANS_ATTACKDATA AttackTrans;			//���� ����Ÿ ����
	DWORD			dwAttackPlayTime;		//���� ���� �ð�

	int				PotionLog;				//���� ��� ���
	int				LevelLog;				//���� ��ȭ ���
	int				CriticalLog;			//ũ��Ƽ�� �α�

	int				EnableStateBar;			//ü�¹� �׸��� �ɼ�
	int				MotionRecordCount;		//��� ���� ��� ī����
	int				iSpawnPointIndex; // ��������ʹ�� ����������

	int				DisplayAlpha;			//������ ( �ӽ� ������ ��� )
	int				RendAlpha;				//������ ( ���� ������ ĳ���� )
	int				RenderLatter;			//������ ���߿�

	DWORD			dwDispAppSkill;			//��ų ����ǥ��
	DWORD			dwDispAppSkillMask;		//��ų ����ǥ�� ����ũ ( ���⸦ ���߱� ���� )
	int				HideWeapon;				//���� ����
	int				MotionLoop;				//�ݺ� ��� Ƚ��
	int				MotionLoopSpeed;		//�ݺ� ��ǿ� ������ �ӵ�
	int				MotionEvent;			//��� �̺�Ʈ �÷�
	int				WeaponEffect;			//����� �Ӽ� ����Ʈ
	DWORD			dwWeaponEffectTime;		//����� �Ӽ� ����Ʈ ī����
	int				EnchantEffect_Point;	//��ų EnchantWeapon �� ��ų ����Ʈ

	User			* pcHookedTarget;
	DWORD			dwHookedTargetEndTime;

	DWORD			dwAssassinEyeTime;		//��ž��� ���� ����
	int 			AssassinEyeParam;		//��ž��� ���� ����


	////////////////////// Ŭ�� //////////////////////////
	int				ClanInfoNum;			//Ŭ�� ���� ��ȣ
	DWORD			dwClanInfoTime;					//Ŭ�� ���� ���� �ð�

	int				iBellatraCrown;
	BOOL			bBlessCastleCrown;


	int				dwVipBit;
	DWORD			dwVipTime;

	Map				* pcMap;
	User			* pcKillerData;
	Unit			* pcBellatraKiller;
	Map				* pcMapSpawn;

	POINT3D			HoSkillPos;				//��ų ���� ��ǥ
	int				iPetID;
	int				bAggressive;

	Unit			* pcFocusingTarget;
	int				iFocusingLastID;

	int				dwExclusiveNum;				//��Ƽ �÷�
	int				iBellatraRoom;				//��Ƽ �Ķ����

	int				CaravanSerial;			// ������һ�ҵ�OBJֵ
	DWORD			CaravanTime;			// ������һ�ҵ�ʱ��
	int				CaravanMode;			// �������Ƿ����
	DWORD			HoSkillDeathTime;		// ����֮��ʱ��

	int				PlaySlowCount;		//�������� ���� ����
	int				PlaySlowSpeed;		//�������� �ӵ�
	int				iStunTimeLeft;
	int				PlayStopCount;		//�������� ���� ī����
	short			PlayHolyMind[2];	//������ ��ȭ ��� ( [0] ���ҵ� ������% [1] �����ð� )
	short			PlayHolyPower[2];	//������ ��ȭ ��� ( [0] ��ȭ�� ������% [1] �����ð� )
	short			PlayPoison[2];		//���� ���� ( [0] ���ҵ� ������ [1] �ص��ð� )
	short			PlayFire[2];
	short			PlayHolyIncantation[2];	//���� ��Ȥ ��ų ( [0] �ӽ� [1] �����ð� )
	int				PlayVanish;			//��Ͻ� ��ų����
	int				PlayCurseQuest;		//���� ����Ʈ ���
	int				PlayVague;			//���� ��ų����

	int				iDistortion;
	int				PlayInvincible;		//���� ������
	int				PlayWeb;			//֩����
	int				PlayDarkBoss;		//�Ƿ����BOSS��ͼ

	BOOL			CheckFlagIce;		//���̽� �Ӽ� �÷��װ�

	int				DispPoison;			//������ ǥ��
	int				DispFire;			//���˺�

	DWORD			dwConcentrationTime;	//����һ��
	DWORD			dwSwiftAxeTime;			//��ɱ֮��
	DWORD			dwBetserkerTime;		//���ŭ��
	DWORD			dwB_Berserker_Time;		//����֮ŭ
	DWORD			dwE_Shield_UseTime;		//���⻤��
	DWORD			dwP_Absorb_UseTime;		//��⻤��
	DWORD			dwAutomation_Time;		//������
	DWORD			dwMetal_Armor_Time;		//�����ؼ�
	DWORD			dwSpark_Shield_Time;	//�����粨
	DWORD			dwMagnetic_Sphere_Time;	//��������
	DWORD			dwH_Sonic_Time;			//���ٴ��
	DWORD			dwP_Enhence_Time;		//ս��ף��
	DWORD			dwFalcon_Time;			//���֮ӥ
	DWORD			dwGolden_Falcon_Time;	//�ƽ���ӥ
	DWORD			dwForceOfNatureTime;	//��Ȼ֮��
	DWORD			dwAmplified_Time;		//Ǳ�ܼ���
	DWORD			dwWindy_Time;			//׷������
	DWORD			dwT_Of_Valhalla_Time;	//ս������
	DWORD			dwHallOfValhallaTime;	//�߶�����֮��
	DWORD			dwFrost_Javelin_Time;	//��˪��ǹ
	DWORD			dwTalaria_Time;			//�������
	DWORD			dwHolyBody_Time;		//ʥ�⻤��
	DWORD			dwHoly_Valor_Time;		//�����ػ�
	DWORD			dwDrastic_Spirit_Time;	//��������
	DWORD			dwD_Inhalation_Time;	//ʥ��֮��
	DWORD			dwGodly_Shield_Time;	//����֮��
	DWORD			dwGod_Bless_Time;		//�ϵ�ף��
	DWORD			dwH_Benedic_Time;		//����֮��
	DWORD			dwZenith_Time;			//����֮��
	DWORD			dwEnergy_Shield_Time;	//ħ���ػ�
	DWORD			dwSpirit_Elemental_Time;//����ٻ�
	DWORD			dwDancing_Sword_Time;	//Ԫ��֮��
	DWORD			dwT_Anima_Time;			//ʥ�ⷨ��
	DWORD			dwDancing_Sword_Param;	
	DWORD			dwHoly_Reflection_Time;	//��ʥ����
	DWORD			dwVirtual_Life_Time;	//��ʥ֮��
	DWORD			dwSummon_Muspell_Time;	//��ʥ��ʹ
	DWORD			dwB_Krishna_Time;		//��Ůɢ��
	DWORD			dwAlasTime;				//����֮��
	DWORD			dwInpesTime;			//���ݴ�ʦ
	DWORD			dwAdvent_Migal_Time;	//���˶�
	DWORD			dwRainmaker_Time;		//����ʦ
	DWORD			dwAdvent_Midranda_Time;	//�׵�����
	DWORD			dwCreed_Time;			//��������

	DWORD			dwWingEffectCode;		//���Ч������

	int				iAreaDamageArea;

	int				EventAttackCount;		//�̺�Ʈ ���� ī���� ( �и�ġ �� )
	DWORD			dwEventAttackParam;

	short			sAddColorEffect[4];		//�����߰�
	int				DispLifeBar;			//����� ǥ��

	DWORD			dwLastUpdateTime;
	DWORD			dwLastRecvAttackTime;	//������ ���� ���� �ð�

	int				TryAttackCount;			//���ݽõ� Ƚ��

	///////////////// Force Orb ////////////////////
	DWORD			dwForceOrbCode;			//�������� ���� �ڵ�
	DWORD			dwForceOrbTime;			//�������� �����ð�

	// ����� - ������ �ν���(�����)
	DWORD			dwLifeBoosterCode; // ����� - �ν��� ������(�����) �ڵ�
	DWORD			dwLifeBoosterTime; // ����� - �ν��� ������(�����) �����ð�
	// ����� - ������ �ν���(���)
	DWORD			dwManaBoosterCode; // ����� - �ν��� ������(���) �ڵ�
	DWORD			dwManaBoosterTime; // ����� - �ν��� ������(���) �����ð�
	// ����� - ������ �ν���(�ٷ�)
	DWORD			dwStaminaBoosterCode; // ����� - �ν��� ������(�ٷ�) �ڵ�
	DWORD			dwStaminaBoosterTime; // ����� - �ν��� ������(�ٷ�) �����ð�

	//����� - ���ͳ� ������, ����Ʋ ����, ���Ʈ ��ũ��(���� ������ ��ũ��)
	DWORD			dwSiegeItem_ScrollCode_Eternal;			// ���ͳ� ������
	DWORD			dwSiegeItem_ScrollTime_Eternal;			
	DWORD			dwSiegeItem_ScrollCode_Fatal;			//����Ʋ ����
	DWORD			dwSiegeItem_ScrollTime_Fatal;		
	DWORD			dwSiegeItem_ScrollCode_Avert;			//���Ʈ ��ũ��
	DWORD			dwSiegeItem_ScrollTime_Avert;	

	// �庰 - ��ų ������
	DWORD			dwSkillDelayCode;
	DWORD			dwSkillDelayTime;

	////////////// ������� State ��� //////////////

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


//ũ��Ƽ�� ����
extern CRITICAL_SECTION	cLoadSection;

//����
int smDPAT_Delete( smDPAT *dPat );


//���Ϲ��۸� �ʱ�ȭ
int InitPatterns();
//���Ϲ��۸� ����ȭ
int ClosePatterns();
//ĳ���Ϳ� ������ ����
int SetLoadPattern(Unit *smChar , char *szName , POINT3D *Posi , POINT3D *Angle );
//ĳ���Ϳ� ������ ����2
int SetLoadPattern(Unit *smChar , char *szName , char *szName2 , POINT3D *Posi , POINT3D *Angle );

int	AddLoaderPattern(Unit *lpChar , char *szName , char *szName2=0 );
//����� �� �����忡 ���Ͽ� �ε� �Ѵ�
int AddLoaderStage( smSTAGE3D *lpStage , char *szName );

class scITEM {

public:
	DWORD	Head;

	int		DisplayFlag;		//ȭ�� ��� ����

	int		Flag;
	int		pX,pY,pZ;

	char	szModelName[64];
	char	szName[64];

	void	*lpStgArea;			//�����ϴ� ����

	smPAT3D	*Pattern;
	smDPAT  *lpDinaPattern;		//���̳��� ���� ������ (������ ������)

	int		PatLoading;

	int		ItemCode;

	DWORD	dwLastTransTime;		// ���������� ���۵� �ð�

	int		ServerCode;				//�ش� ĳ���� ���� �ڵ�

	POINT3D	RendPoint;				//�������� 2D ��ǥ ( x,y,z )


	POINT3D Posi;
	POINT3D Angle;

};

int	AddLoaderItem( scITEM *lpItem , char *szName );

extern smPATTERN smBipPattern;
extern smPATTERN smPattern;

extern int	SkillChargingFlag;			//��ų ��¡ �÷�

extern TRANS_SKIL_ATTACKDATA	Trans_SplashCharList;		//�ðܼ� �´� ���� ����Ÿ �ӽ�����


extern int CastleBattleZone_LineZ;
extern int CastleBattleZone_DoorLineZ;		//���� �Ա�
extern int CastleBattleZone_DoorLineX[2];	//���� �Ա�
extern int CastleBattleZone_BridgeZ;		//�ٸ� �Ա�
extern int CastleSoulFountain_Area[4];		//��ȥ�ǻ���


#endif