/*----------------------------------------------------------------------------*
*	ÆÄÀÏ¸í :  AssaParticle
*	ÇÏ´ÂÀÏ :  ÀÌÆåÆ® 
*	ÀÛ¼ºÀÏ :  ÃÖÁ¾¾÷µ¥ÀÌÆ® 2002³â 12¿ù
*	Àû¼ºÀÚ :  È«È£µ¿
*-----------------------------------------------------------------------------*/	

#ifndef _ASSA_PARTICLE_
#define _ASSA_PARTICLE_

#define ASSA_SHOT_LASER		100
#define ASSA_SHOT_SPARK		120
#define ASSA_SHOT_WATER		130
#define ASSA_SHOT_FIRE		140
#define ASSA_SHOT_ICE		150
#define ASSA_SHOT_BIGFIRE1	160
#define ASSA_SHOT_SPARK1    170

#define ASSA_SHOT_LASER2	180
#define ASSA_SHOT_LASER3	190
#define ASSA_SHOT_PARKSPARK		200

#define ASSA_SHOT_LASER4	210
#define ASSA_SHOT_LASER5	220

#define	MAX_WEAPON_POS	20

class cASSAPARTSHOT : public cASSAEFFECT
{
public:
	cASSAPARTSHOT();
	~cASSAPARTSHOT();
	
	void Main();
	void Draw(POINT3D *pPosi , POINT3D *pAngle);
	void Start(POINT3D *pCurPosi, POINT3D *pDestPosi, int type);
	void Start(POINT3D *pCurPosi, POINT3D *pDestPosi, cASSAEFFECT *pEffect,int type = ASSA_SHOT_WATER);
	void Start(Unit *pChar, POINT3D *pDestPosi, int type);
	void SetChainLighting(Unit **pCharList, int count);
public:
	
	int		WidthStep;   //·¹ÀÌÀú ½î±âÀÇ ³ÐÀÌ..
	int		State;		 //ÀÛ¾÷¿ë »óÅÂ...
	int		EffectType;		 //ÆÄÆ¼Å¬ Type...
	int		TimeCount;   //ÀÌº¥Æ® ½Ã°£ Ã¼Å©¿ë..
	
	cASSAEFFECT  *Effect; //ÀÌÆåÆ®ÀÇ Á¤º¸¸¦ ¾Ë°í ÀÖ¾î¾ß ÇÒ°æ¿ì..
	int			 PartNum;
	D3DVECTOR	Velocity;


	POINT3D     LocalPos;   //LocalÀ§Ä¡..
	POINT3D   LocalAngle; //ÇöÀç¿ùµå»ó¿¡¼­ ¾²´Â °¢µµ..
	POINT3D    DestAngle;  //¸ñÀû ¹æÇâÀ¸·Î ÀüÃ¼ÀûÀ¸·Î µ¹¸±¶§ ¾²´Â °¢µµ..
	POINT3D    ShootingAngle;

	bool	ChainLightingFlag;
	Unit *CharList[20];
	int		CharCount;
};


//Àü±â¿ë..(Æ¢±â´Â°Å)
class cASSAPARTSPARK : public cASSAEFFECT
{
public:
	cASSAPARTSPARK();
	~cASSAPARTSPARK();

	void Main();
	void Start(POINT3D *pCurPosi);
	void Start(POINT3D *pCurPosi, char *fileName);

	void Draw(POINT3D *pPosi, POINT3D *pAngle);

public:
	D3DVECTOR Velocity;
};

struct WEAPON_PART_POS
{
	POINT3D pos[4];
	int		posCount;
};

#define	ENCHANT_WEAPON					80
#define ENCHANT_WEAPON_FIRE				100
#define ENCHANT_WEAPON_ICE				200
#define ENCHANT_WEAPON_LIGHT			300
#define ENCHANT_MEMBER_JIN				400
#define IMPULSION_LIGHT                 500

#define HOLY_ACTION						700
#define DRASTIC_ACTION					750
#define HOLY_VALOR_JANG					800
#define HOLY_VALOR_MEMBER				900
#define DRASTIC_SPIRIT_JANG				1000
#define DRASTIC_SPIRIT_MEMBER			1100
#define WINDY_ACTION					1200
#define HOLY_MIND_ATTACK				1300

#define STOP_PART_FLAG					1399
#define AGING_BODY						1400
#define FURY_EYE1						1401
#define CLAN_MONSTER_PART1				1402
#define PIGON_HAND_FIRE					1403
#define CLASS_UP_PART1					1404
#define IRON_MONSTER_CHAINGOLEM1		1405

#define IRON_MONSTER_RUNIC_GUARDIAN_HAND1 1406
#define SHELLTOM_WEAPON					  1407

#define ICE_MONSTER_CHAOSKARA_STAFF		1408
#define ICE_MONSTER_VALENTO_BODY		1409
#define MONSTER_SPIDERTROOPER			1410
#define EFFECT_FIRECRACKER				1411
#define MONSTER_KELVEZU_CIRCLE			1412
#define EFFECT_ELEMENT					1413
#define DRAXOS_MONSTER_STAFF			1414
#define GREEDY_MONSTER_STAFF			1415
#define MIDRANDA_MONSTER_STAFF			1416
#define FAUGN_MONSTER_STAFF				1417
#define YAGDITHA_MONSTER_STAFF			1418
#define CLASS_LEVEL_EFFECT				1419

/////////////////

//Ä³¸¯ÅÍ¸¦ µû¶ó ´Ù´Ï´Â ÀÌÆåÆ®µé..
class cASSAChar : public cASSAEFFECT
{
public:
	cASSAChar();
	~cASSAChar();

	void Main();
	void Start(Unit *pChar, int code, int maxTime = 0, float delay = 0.f);
	void StopEffect();

	int			PartNum;
	int			PartNumExt1;
	
	int			EnchantPartNum[3];
	DWORD       ItemCode;
	bool        MyCharacterFlag;

	int			State;//»óÅÂ¿ë..

	int			EffectType;
	bool        FadeStopFlag;

	BOOL        FlagShow;
};


//Ä³¸¯ÅÍ ¾ÆÀÌÅÛ À¯Áö ÀÌÆåÆ®µé..
class cASSAItem : public cASSAEFFECT
{
public:
	cASSAItem();
	~cASSAItem();

	void Main();
	void Start(Unit *character, int code);
	int  PartNum;
	void StopEffect();
	bool        MyCharacterFlag;
	BOOL        FlagShow;
	int			EffectType;

};

//Pat¿¡ ÀÖ´Â Æ¯Á¤ ¸Þ½Ã¸¦ µû¶ó°¡´Â ÆÄÆ¼Å¬..
class cAssaTracePatMeshParticle : public cASSAEFFECT
{
public:
	cAssaTracePatMeshParticle();
	~cAssaTracePatMeshParticle();

	void Main();
	void Start(Unit *character, smPAT3D *pat, smOBJ3D *searchObj, char *particleName, int liveTime = 10);

private:
	BOOL	FlagShow;
	int		PartNum;
	smPAT3D *PatObj;
	smOBJ3D *SearchObj;
	BOOL	AttachFlag;

	int		LiveTime;
	int		TimeCount;
};

//Ä³¸¯ÅÍÀÇ Æ²Á¤ ¸Þ½Ã¸¦ µû¶ó°¡´Â ÆÄÆ¼Å¬
//»óÅÂ Á¾·á Á¶°Ç: Ä³¸¯ÅÍ°¡ Á×¾úÀ» °æ¿ì¿¡ ¾ø¾îÁö°í °è¼Ó µû¶ó´Ù´Ï´Â ÆÄÆ¼Å¬
//È­¸é ·»´õ »óÅÂ: Ä³¸¯ÅÍ°¡ ¾Èº¸ÀÏ°æ¿ì È­¸é¿¡ ·»´õ¸¦ ÇÏÁö ¾Ê´Â´Ù.
//ÇöÀç ÆÄÆ¼Å¬Àº Ä³¸¯ÅÍ¸¦ °è¼Ó µû¶ó°£´Ù.
class cAssaTraceCharMeshParticle : public cASSAEFFECT
{
public:
	cAssaTraceCharMeshParticle();
	~cAssaTraceCharMeshParticle();

	void Main();
	void Start(Unit *character, char *meshName, char *particleName, bool attachFlag = true, int liveTime = -1);
	void SetPosLength(int length)
	{
		Length = length;	//À§Ä¡ º¸Á¤¿ë..
	}
	
	void SetScale(float scale)
	{
		Scale = scale;
	}
	
	
private:
	BOOL		FlagShow;
	int			PartNum;
	smOBJ3D		*SearchObj;

	BOOL		MyCharacterFlag;
	bool		AttachFlag;

	int			Length;
	float		Scale;

	int			LiveTime;
	int			TimeCount;
	
};


//Æ¯Á¤ ÁöÁ¡À¸·Î ³¯¶ó°¡´Â ¿ÀºêÁ§Æ®¿¡ µû¶ó°¡´Â ÆÄÆ¼Å¬
//¿¡´Ï°¡ µÇ´Â Æ¯Á¤ ¸Þ½Ã¸¦ ÆÄÆ¼Å¬ÀÌ ¦i¾Æ °¡´Ù°¡ destPos À§Ä¡ ±ÙÃ³¿¡ °¡¸é ¾ø¾îÁö´Â ÆÄÆ¼Å¬..
class cAssaTraceMeshDestParticle : public cASSAEFFECT
{
public:
	cAssaTraceMeshDestParticle();
	~cAssaTraceMeshDestParticle();

	void Main();
	void Draw(POINT3D *pPosi, POINT3D *pAngle);
	void Start(smPAT3D *pat, char *meshName, POINT3D *curPos, POINT3D *destPos, char *particleName);

	void SetRenderMesh(BOOL flag)
	{
		MeshRenderFlag = flag;
	}

private:
	int	PartNum;
	smOBJ3D *SearchObj;
	smPAT3D *PatMesh;
	int CurFrame;

	POINT3D LocalPos;

	BOOL	MeshRenderFlag;
};


//Æ¯Á¤ 2ÁöÁ¡À» ÀÕ´Â ÀÜ»óÀ» ±×¸°´Ù.
class cAssaMotionBlur : public cASSAEFFECT
{
public:
	cAssaMotionBlur();
	~cAssaMotionBlur();

	void Main();
	void Draw(POINT3D *pPosi , POINT3D *pAngle);

	void Start(Unit *character, char *meshName1, char *meshName2, int liveTime = 140);
	void SetDelay(int startDelay)
	{
		StartDelay = startDelay;
	}
	void SetAlpha(int alpha)
	{
		Alpha = alpha;
	}
	smOBJ3D		*SearchObj1;
	smOBJ3D     *SearchObj2;
	BOOL		MyCharacterFlag;

	int			LiveTime;
	int			TimeCount;

	int			StartDelay;
	float		Scale;

	int			Alpha;
	void SetScale(float scale)
	{
		Scale = scale;
	}

};

//Æ¯Á¤ 2ÁöÁ¡ÀÇ ÆäÀÌ½º ¿¡´Ï¸ÞÀÌ¼Ç
class cAssaTwoPointAni : public cASSAFACE
{
public:
	cAssaTwoPointAni();
	~cAssaTwoPointAni();

	void Main();
	//void Draw(POINT3D *pPosi, POINT3D *pAngle);

	void Start(Unit *character, char *meshName1, char *meshName2);

	smOBJ3D		*SearchObj1;
	smOBJ3D     *SearchObj2;
	BOOL		MyCharacterFlag;

	int			LiveTime;
	int			TimeCount;

	int			StartDelay;
};

//Fighter 3Â÷ ½ºÅ³
class AssaSkill3Concentration : public cASSAEFFECT
{
public:
	AssaSkill3Concentration();
	~AssaSkill3Concentration();
	void Start(Unit* character, int liveCount,int light = TRUE);
	void Main();
private:
	int			ParticleID;
	BOOL		MyCharacterFlag;
	BOOL		EndFlag;
	int			Light;
};


class AssaSkill3SwiftAxe : public cASSAEFFECT
{
public:
	AssaSkill3SwiftAxe();
	~AssaSkill3SwiftAxe();
	void Start(Unit* character, int liveCount, int light = TRUE);
	void Main();

private:
	int			ParticleID;
	BOOL		MyCharacterFlag;
	BOOL		EndFlag;
	int			Light;
};

class AssaSkillWeaponMotionBlur : public cASSAEFFECT
{
public:
	AssaSkillWeaponMotionBlur();
	~AssaSkillWeaponMotionBlur();

	void Main();
	void Draw(POINT3D *pPosi , POINT3D *pAngle);

	void Start(Unit *character, int liveTime = 140,int Flag = 0);
	void SetDelay(int startDelay)
	{
		StartDelay = startDelay;
	}
	BOOL		MyCharacterFlag;

	int			LiveTime;
	int			TimeCount;

	int			StartDelay;
};



//Archer 3Â÷ ½ºÅ³
class AssaSkill3BombShotExplision : public cASSAEFFECT
{
public:
	AssaSkill3BombShotExplision();
	~AssaSkill3BombShotExplision();
	void Start(POINT3D *pPosi, D3DVECTOR *Velocity, D3DVECTOR *Gravity);
	void Start(POINT3D *pPosi, D3DVECTOR *Velocity, D3DVECTOR *Gravity, char *particleName);

	void Main();

private:

	D3DVECTOR   Pos;
	D3DVECTOR	Velocity;
	D3DVECTOR   Gravity;
	
	int			ParticleID;
};

enum
{
	ELEMENTAL_FIRE = 0,
	ELEMENTAL_LIGHTING
};

class AssaSkill3ElementalShot : public cASSAEFFECT
{
public:
	AssaSkill3ElementalShot();
	~AssaSkill3ElementalShot();
	
	
	void Start(POINT3D* pCur, POINT3D* pDest, int type);
	void Main();

private:
	//D3DVECTOR	Velocity;
	int			ParticleID;
	POINT3D		ShootingAngle;
	int			Type;

};

class AssaSkill3BombShot : public cASSAEFFECT
{
public:
	AssaSkill3BombShot();
	~AssaSkill3BombShot();

		
	void Draw(POINT3D *pPosi , POINT3D *pAngle);	
	void Start(POINT3D* pCur, POINT3D* pDest);
	void Main();

private:
	int			ParticleID;
	POINT3D     ShootingAngle;
	smPAT3D     *PatMesh;
};

class AssaSkill3Perforation : public cASSAEFFECT
{
public:
	AssaSkill3Perforation();
	~AssaSkill3Perforation();

	void Start(POINT3D* pCur, POINT3D* pDest);
	void Draw(POINT3D *pPosi , POINT3D *pAngle);

	void Main();
private:
	D3DVECTOR	Velocity;
	POINT3D		ShootingAngle;
	int			State;
	int			ParticleID;

	smPAT3D*	PatMesh;
	int			State1TimeCount;
};


//Mechanic 3Â÷ ½ºÅ³
class AssaSkill3MetalArmor : public cASSAEFFECT
{
public:
	AssaSkill3MetalArmor();
	~AssaSkill3MetalArmor();
	void Start(Unit* character, int liveCount);
	void Main();
	void Draw(POINT3D *pPosi , POINT3D *pAngle);

private:
	int			ParticleID;
	BOOL		MyCharacterFlag;

	smPAT3D*	PatMesh;
	int			CurrentFrame;
	
	BOOL		EndFlag;
	int			MeshBlendStep;
};

class AssaSkill3SparkShield : public cASSAEFFECT
{
public:
	AssaSkill3SparkShield();
	~AssaSkill3SparkShield();

	void Start(Unit* character,int liveCount);
	void Main();
private:
	int		ParticleID;
	BOOL	MyCharacterFlag;
	BOOL    EndFlag;
	smOBJ3D		*SearchObj;
};



class AssaSkill3Vanish : public cASSAEFFECT
{
public:
	AssaSkill3Vanish();
	~AssaSkill3Vanish();
	void Start(Unit* character);
	void Main();

private:
	int			ParticleID;
	BOOL		MyCharacterFlag;
	BOOL		EndFlag;
};



//Magician 3Â÷ ½ºÅ³
class AssaSkill3EnergyShield : public cASSAEFFECT
{
public:
	AssaSkill3EnergyShield();
	~AssaSkill3EnergyShield();

	void Start(Unit* character,int liveCount);
	void Main();
	void Draw(POINT3D *pPosi, POINT3D *pAngle);
private:
	int		ParticleID;
	BOOL	MyCharacterFlag;
	BOOL    EndFlag;

	smPAT3D	*PatMesh;
	int		CurrentFrame;
	int		MeshBlendStep;
};

class AssaSkill3EnergyShieldDefence : public cASSAEFFECT
{
public:
	AssaSkill3EnergyShieldDefence();
	~AssaSkill3EnergyShieldDefence();

	void Start(Unit* character);
	void Main();
private:
	int		ParticleID;
	BOOL	MyCharacterFlag;
	BOOL    EndFlag;
};


class AssaSkill3SpiritElemental : public cASSAEFFECT
{
public:
	AssaSkill3SpiritElemental();
	~AssaSkill3SpiritElemental();
	void Start(Unit* character, int liveCount);
	void Main();
	void Draw(POINT3D *pPosi , POINT3D *pAngle);


private:
	smPAT3D		*PatMesh;		//¿¡´Ï¸ÞÀÌ¼Ç
	int			ParticleID;

	int			MaxFrame;
	int			CurrentFrame;
	smOBJ3D		*ObjBip;
	
	
	
	int		ParticleIDExt1;
	BOOL	MyCharacterFlag;
	BOOL    EndFlag;
};

enum
{
	DANCING_MAINTAIN = 1,		//À¯Áö »óÅÂ
	DANCING_ATTACK_START1,	    //°ø°Ý ¸í·ÉÀÌ µé¾î ¿ÔÀ» °æ¿ì.
	DANCING_ATTACK_START2,      //°ø°Ý À§Ä¡¿¡ Ä®ÀÌ À§Ä¡ ÇßÀ» °æ¿ì.
	DANCING_ATTACK_PROCESS,	    //°ø°Ý »óÅÂ
	DANCING_ATTACK_HIT,         //°ø°Ý Å¸°Ý	
	DANCING_RETURN			    //¸®ÅÏ »óÅÂ
};

class AssaSkill3DancingSword : public cASSAEFFECT
{
public:
	AssaSkill3DancingSword();
	~AssaSkill3DancingSword();
	void Start(Unit* character, int type,int liveCount, int level);
	void Main();
	void Draw(POINT3D *pPosi , POINT3D *pAngle);

private:
	smPAT3D		*PatMesh;		//¿¡´Ï¸ÞÀÌ¼Ç
	int			ParticleID1;
	int			ParticleID2;
	int			ParticleID3;
	int			ParticleID4;

	smOBJ3D		*ObjBip1;
	smOBJ3D		*ObjBip2;
	smOBJ3D		*ObjBip3;
	smOBJ3D		*ObjBip4;

	BOOL		MyCharacterFlag;
	int			CurrentFrame;

	int			State;

	POINT3D		AttackDest;
	POINT3D		AttackLocalPosi;
	POINT3D		AttackAngle;

	float		DetectionLength;


	int			Type;
	BOOL        EndFlag;

	int			AttackTime;	//°ø°ÝÇÒ Å¸ÀÓ ½ºÅÛÇÁ
	Unit		*AttackMonster;

	int			FrameSpeed;
	BOOL		FrameSpeedFlag;
};



//Night 3Â÷ ½ºÅ³
class AssaSkill3DivineInhalation : public cASSAEFFECT
{
public:
	AssaSkill3DivineInhalation();
	~AssaSkill3DivineInhalation();

	void Start(Unit* character,int liveCount);
	void Main();
private:
	int		ParticleID;
	BOOL	MyCharacterFlag;
	BOOL    EndFlag;
	smOBJ3D		*SearchObj;
};



class AssaSkill3HolyIncantationShot : public cASSAEFFECT
{
public:
	AssaSkill3HolyIncantationShot();
	~AssaSkill3HolyIncantationShot();
	
	
	void Start(Unit *character);
	void Main();

private:
	int		ParticleID;
	BOOL	MyCharacterFlag;
};

//Night À¯Áö ÆÄÆ¼Å¬
//¸ó½ºÅÍ ¸Ó¸®¿¡ »ý±â´Â ÆÄÆ¼Å¬
class AssaSkill3HolyIncantationPart : public cASSAEFFECT
{
public:
	AssaSkill3HolyIncantationPart();
	~AssaSkill3HolyIncantationPart();
	
	void Start(Unit* character, int liveCount);
	void Main();

private:
	int			ParticleID;
	BOOL		MyCharacterFlag;
	BOOL		EndFlag;
};



//Night 3Â÷ ½ºÅ³
class AssaSkill3HolyIncantationPartHand : public cASSAEFFECT
{
public:
	AssaSkill3HolyIncantationPartHand();
	~AssaSkill3HolyIncantationPartHand();

	void Start(Unit* character,int liveCount);
	void Main();
private:
	int		ParticleID;
	int		ParticleIDExt;
	BOOL	MyCharacterFlag;
	BOOL    EndFlag;
	smOBJ3D		*SearchObj;
};

class AssaSkill3FlameBrandish : public cASSAEFFECT
{
public:
	AssaSkill3FlameBrandish();
	~AssaSkill3FlameBrandish();
	void Start(Unit* character);
	void Main();
	void Draw(POINT3D *pPosi , POINT3D *pAngle);


private:
	smPAT3D		*PatMesh;		//¿¡´Ï¸ÞÀÌ¼Ç
	int			ParticleID[7];
	
	int			MaxFrame;
	int			CurrentFrame;
	smOBJ3D		*ObjBip[7];
};
	

//Priestess ½ºÅ³
class AssaSkill3VigorBall : public cASSAEFFECT
{
public:
	AssaSkill3VigorBall();
	~AssaSkill3VigorBall();

	void Start(POINT3D* pCur, Unit* destChar, D3DVECTOR* velocity, int delay);
	void Main();

private:
	int			ParticleID;
	int			ParticleIDExt1;
	D3DVECTOR	Velocity;
	Unit		*DestChar;
	D3DVECTOR   Pos;
};

class AssaSkill3ResurrectionShot : public cASSAEFFECT
{
public:
	AssaSkill3ResurrectionShot();
	~AssaSkill3ResurrectionShot();
	void Start(Unit* character, int delay);
	void Main();
	void Draw(POINT3D *pPosi , POINT3D *pAngle);


private:
	smPAT3D		*PatMesh;		//¿¡´Ï¸ÞÀÌ¼Ç
	int			ParticleID;
	int			ParticleIDExt1;

	int			MaxFrame;
	int			CurrentFrame;

	smOBJ3D		*ObjBip;
	int			Delay;			//µô·¹ÀÌ ÇÒ½Ã°£..
	int			TimeCount;		//ÃÑ Èå¸¥ ½Ã°£..
	
	BOOL		MyCharacterFlag;
	BOOL		EndFlag;
	int			MeshBlendStep;
};

class AssaSkill3ResurrectionPart : public cASSAEFFECT
{
public:
	AssaSkill3ResurrectionPart();
	~AssaSkill3ResurrectionPart();
	
	void Start(Unit* character, int liveCount);
	void Main();

private:
	int			ParticleID;
	BOOL		MyCharacterFlag;
	BOOL		EndFlag;
};


class AssaSkill3Extinction : public cASSAEFFECT
{
public:
	AssaSkill3Extinction();
	~AssaSkill3Extinction();
	
	void Start(Unit* character);
	void Main();

private:
	int			ParticleID;
	BOOL		MyCharacterFlag;
};


class AssaSkillVirtualLifeMember : public cASSAEFFECT
{
public:
	AssaSkillVirtualLifeMember();
	~AssaSkillVirtualLifeMember();
	void Start(Unit* character, int liveCount);
	void Main();
	


private:
	int			ParticleID;
	BOOL		MyCharacterFlag;
	
	BOOL		EndFlag;
};

//Atalanta
class AssaSkillTriumphOfValhallaPart : public cASSAEFFECT
{
public:
	AssaSkillTriumphOfValhallaPart();
	~AssaSkillTriumphOfValhallaPart();
	void Start(Unit* character, int liveCount);
	void StartHallOfValhalla(Unit* character, int liveCount);
	void Main();

private:
	int			ParticleID;
	int			ParticleIDExt;
	BOOL		MyCharacterFlag;

	smOBJ3D		*ObjBip;
	smOBJ3D		*ObjBipExt;
	BOOL		EndFlag;
};

class AssaSkillTriumphOfValhallaShot : public cASSAEFFECT
{
public:
	AssaSkillTriumphOfValhallaShot();
	~AssaSkillTriumphOfValhallaShot();

	void Start(Unit* curChar, Unit* destChar, D3DVECTOR* velocity, int liveCount);
	void Draw(POINT3D *pPosi , POINT3D *pAngle);
	void Main();

private:
	int			ParticleID;
	//int			ParticleIDExt1;
	D3DVECTOR	Velocity;
	Unit		*DestChar;
	D3DVECTOR   Pos;
	int			LiveCount;

	smOBJ3D     *SearchObj;
};


class AssaSkill3LightingJavelin : public cASSAEFFECT
{
public:
	AssaSkill3LightingJavelin();
	~AssaSkill3LightingJavelin();

private:
	int			AnimationID[4];
	int			AniDelay;
	int			AniIndex;

	POINT3D		ShootingAngle;
	int			ParticleID;

public:
	void StartShort(POINT3D *pCur, POINT3D *pDest);
	void StartRope(POINT3D *pCur,POINT3D *pDest);
	void Start(POINT3D* pCur, POINT3D* pDest);
	void Main();
	void Draw(POINT3D *pPosi , POINT3D *pAngle);
};

class AssaSkill3StormJavelin : public cASSAEFFECT
{
public:
	AssaSkill3StormJavelin();
	~AssaSkill3StormJavelin();

private:
	int			TextureID[6];
	int			TextureIDExt1;		

	int			AniDelay;
	int			AniIndex;

	POINT3D		ShootingAngle;
	int			ParticleID;
	
	smPAT3D*	PatMesh;
public:
	void Start(POINT3D* pCur, POINT3D* pDest);
	void Main();
	void Draw(POINT3D *pPosi , POINT3D *pAngle);
	int			BlendStep;


	POINT3D		ScalePosExt;
	D3DVECTOR   ScalePosExtStep;
};



class AssaSkill3SplitJavelin : public cASSAEFFECT
{
public:
	AssaSkill3SplitJavelin();
	~AssaSkill3SplitJavelin();

private:
	smPAT3D*	PatMesh;
	POINT3D		ShootingAngle;
	int			CurrentFrame;
	int			Delay;
	int			BlendStep;


public:
	void Start(POINT3D* pCur, POINT3D* pDest, int delay);
	void Main();
	void Draw(POINT3D* pPosi, POINT3D *pAngle);
};






//Àü¾÷ ¹«±â ÆÄÆ¼Å¬
class AssaClassUpWeapon : public cASSAEFFECT
{
public:
	AssaClassUpWeapon();
	~AssaClassUpWeapon();
	
	void Start(Unit* character);
	void Main();
	void RespawnParticle();
	void StopParticle();
	void StopParticleID();
private:
	
	int			ParticleIDGroup[4];
	BOOL		MyCharacterFlag;
	BOOL		EndFlag;

	POINT3D		LocalPos;
	int			LocalAngle;

	BOOL		LocalPosTransFlag;
};
class AssaElementWeapon :public cASSAEFFECT
{
public:
	AssaElementWeapon();
	~AssaElementWeapon();
	void Start(Unit *character ,int Kind,int iHand);
	void Main();
	void StopParticle();
	void StopParticleID();
private:
	int			ParticleIDGroup[MAX_WEAPON_POS];
	BOOL		MyCharacterFlag;
	BOOL		EndFlag;
	
	int			Width;
	BOOL		ScaleFlag;
	int			ScaleWidth;

	int			WeaponPosCount;
	POINT3D		WeaponPos[MAX_WEAPON_POS];

	int			GlowWidth;
	int			GlowPosIndex;
	BOOL		GlowFlag;
	smFACE2D	GlowFace;
};


//Fighter 3Â÷ ½ºÅ³
class AssaNatureSnow : public cASSAEFFECT
{
public:
	AssaNatureSnow();
	~AssaNatureSnow();
	void Start();
	void Main();
private:
	int			ParticleID;
	BOOL		MyCharacterFlag;
	BOOL		EndFlag;
};


//Runic Guardian ÀÌÆåÆ®
class AssaRunicGuardianShot : public cASSAEFFECT
{
public:
	AssaRunicGuardianShot();
	~AssaRunicGuardianShot();
	void Start(POINT3D *pCur, POINT3D *pDest);
	void Main();

private:
	int			ParticleID;
	POINT3D     ShootingAngle;
};


class AssaRunicGuardianBossSkill : public cASSAEFFECT
{
public:
	AssaRunicGuardianBossSkill();
	~AssaRunicGuardianBossSkill();
	void Start(Unit* character, int liveCount);
	void Main();

private:
	int			ParticleID;
	BOOL		MyCharacterFlag;
	BOOL		EndFlag;
	int			ShotBlendType;
};


class AssaRunicGuardianBossShot : public cASSAEFFECT
{
public:
	AssaRunicGuardianBossShot();
	~AssaRunicGuardianBossShot();
	
	void Start(POINT3D *pShotPos, POINT3D *pAttackPos, D3DVECTOR* velocity, int BlendType = SMMAT_BLEND_INVSHADOW);
	void Draw(POINT3D *pPosi , POINT3D *pAngle);
	void Main();
	
	void SetHitFlag(bool flag) { HitEffectFlag = flag; }
private:
	int			ParticleID;
	
	D3DVECTOR	Velocity;
	int			LiveCount;
	
	D3DVECTOR	CurPos;
	D3DVECTOR   AttackPos;
	bool		HitEffectFlag;
};

class AssaRunicGuardianBossHit : public cASSAEFFECT
{
public:
	AssaRunicGuardianBossHit();
	~AssaRunicGuardianBossHit();

	void Start(POINT3D* pCur, Unit* destChar, D3DVECTOR* velocity, int delay, Unit **charList = NULL, int charCount = 0);
	void Main();
    
private:
	int			ParticleID;
	int			ParticleIDExt1;
	D3DVECTOR	Velocity;
	Unit		*DestChar;
	D3DVECTOR   Pos;

	Unit      *CharList[100];
	int			CharCount;
    int			TempMyIndex;


};


class AssaSkyParticle : public cASSAEFFECT
{
public:
	AssaSkyParticle();
	~AssaSkyParticle();

	void Start(POINT3D* pCur, POINT3D* pDest, int delay = 0,int SkillCode = 0);
	void Main();
	void SetDelay(int delay);
private:
	int			ParticleID;
	D3DVECTOR   Pos;
    D3DVECTOR   Velocity;
	int			TimeCount;

	int			Delay;
	bool		ParticleSpawnFlag;
};


class AssaRunicGuardianLight : public cASSAEFFECT
{
public:
	AssaRunicGuardianLight();
	~AssaRunicGuardianLight();

private:
	int			AnimationID[3];
	int			AniDelay;
	int			AniIndex;
	
	int			ParticleID1;
	int         ParticleID2;

	Unit		*pCurChar;
	Unit      *pDestChar;

	bool		CurMyCharacterFlag;
	bool		DestMyCharacterFlag;

	smOBJ3D		*ObjBip1;

	POINT3D     CurPos;
	POINT3D     DesPos;
    bool		StopFlag;

public:
	void Start(Unit* pCurChar, Unit* pDesChar, bool ObjectFlag = false, bool firstPartFlag = false, bool secondPartFlag = false);
	void Main();
	void Draw(POINT3D *pPosi , POINT3D *pAngle);
	bool AddFace2DLine(POINT3D *curPos, POINT3D *desPos, int width, int matNum);
};


class AssaShelltomShot : public cASSAEFFECT
{
public:
	AssaShelltomShot();
	~AssaShelltomShot();

	void Start(POINT3D* pCur, POINT3D* pDest, int shellType = 0);
	void Draw(POINT3D *pPosi , POINT3D *pAngle);

	void Main();
private:
	int			ParticleID;
	POINT3D     ShootingAngle;
	smPAT3D     *PatMesh;
	int			m_ShellType;
	float		VelocityY;
};


class AssaShelltomUpWeapon : public cASSAEFFECT
{
public:
	AssaShelltomUpWeapon();
	~AssaShelltomUpWeapon();

	void	Start(Unit *pCharacter, int timeCount);
	void	Main();
	
	BOOL	AddFace2DLine(POINT3D *curPos, POINT3D *desPos, int width, int matNum);
    
private:
	BOOL	MyCharacterFlag;
	BOOL	EndFlag;
	
	int		ZPos[2];
	int		ParticleID[2];
	int		TimeCount;

};

class AssaShelltomUpWeapon1 : public cASSAEFFECT
{
public:
	AssaShelltomUpWeapon1();
	~AssaShelltomUpWeapon1();

	void	Start(Unit *pCharacter, int timeCount);
	void	Main();
	void	Draw(POINT3D *pPosi , POINT3D *pAngle);

private:
	BOOL	MyCharacterFlag;
	BOOL	EndFlag;

	int		TimeCount;
	int		MaterialNum;
	
	POINT3D		LocalPos;	//È¸ÀüÀÌ ½ÃÀÛµÉ LocalÀÇ À§Ä¡
	int			LocalAngle;

	BOOL		LocalPosTransFlag;

};
class AssaShelltomUpWeapon2 : public cASSAEFFECT
{
public:
	AssaShelltomUpWeapon2();
	~AssaShelltomUpWeapon2();

	void	Start(Unit *pCharacter, int timeCount, int shellTomCode);
	void	Main();
	void	Draw(POINT3D *pPosi, POINT3D *pAngle);

private:
	BOOL	EndFlag;
	BOOL	MyCharacterFlag;
	int		MaterialNum;
	
	int		Width;
	BOOL	ScaleFlag;
	int		ScaleWidth;

	int		WeaponPosCount;
	int		WeaponPosCount2;

	POINT3D	WeaponPos[MAX_WEAPON_POS];
	POINT3D WeaponPos2[MAX_WEAPON_POS];

	int			GlowWidth;
	int			GlowPosIndex;
	BOOL		GlowFlag;
	smFACE2D	GlowFace;
};


// ¹ÚÃ¶È£
class ParkAssaChaosKaraMeteo : public cASSAEFFECT
{
public:
	ParkAssaChaosKaraMeteo();
	~ParkAssaChaosKaraMeteo();

	void Start(POINT3D* pCur, POINT3D* pDest, int delay = 0);
	void Main();
	void SetDelay(int delay);
private:
	int			ParticleID;
	D3DVECTOR   Pos;
    D3DVECTOR   Velocity;
	int			TimeCount;

	int			Delay;
	bool		ParticleSpawnFlag;
};

// ¹ÚÃ¶È£	(¸®ÀÚµåÆ÷Å©)
class ParkAssaLizardfolk : public cASSAEFFECT
{
public:
	ParkAssaLizardfolk();
	~ParkAssaLizardfolk();

private:
	smPAT3D*	PatMesh;
	POINT3D		ShootingAngle;
	int			CurrentFrame;
	int			Delay;
	int			BlendStep;


public:
	void Start(POINT3D* pCur, POINT3D* pDest, int delay);
	void Main();
	void Draw(POINT3D* pPosi, POINT3D *pAngle);
};

// ¹ÚÃ¶È£  (¸ÞÅ×¿À ¹ü¿ëÀûÀÎ°Å)
class AssaSkyMeteoParticle : public cASSAEFFECT
{
public:
	AssaSkyMeteoParticle();
	~AssaSkyMeteoParticle();

	void Start(POINT3D* pCur, POINT3D* pDest, int delay = 0, int nType = 0);
	void Main();
	void SetDelay(int delay);
private:
	int			ParticleID;
	D3DVECTOR   Pos;
    D3DVECTOR   Velocity;
	int			TimeCount;

	int			Delay;
	bool		ParticleSpawnFlag;
	int			nEffectType;
};
// ¼¼ÄÜÉèÖÃ
class AssaSkillNormal :public cASSAEFFECT
{
public:
	AssaSkillNormal();
	~AssaSkillNormal();

	void Start(char *pFileName, Unit *character,int Time,int SkillCode);
	void Main();
private:
	int		ParticleID;
	BOOL	MyCharacterFlag;
	BOOL	EndFlag;
};
class AssaDarkSkill :public cASSAEFFECT
{
public:
	AssaDarkSkill();
	~AssaDarkSkill();

	void Start(POINT3D *pCur, Unit *destChar,D3DVECTOR *velocity, int delay,char *pFileName1,char *pFileName2,int SkillCode);
	void Main();
private:
	int			ParticleID;
	int			ParticleIDExt1;
	D3DVECTOR	Velocity;
	Unit		*DestChar;
	D3DVECTOR   Pos;
};
// 5×ª¼¼ÄÜ
class AssaSkill5Normal :public cASSAEFFECT
{
public:
	AssaSkill5Normal();
	~AssaSkill5Normal();

	void Start(Unit* character, int liveCount,char *ParicleName1,char *ParicleName2,int iCode = 0);
	void Main();
private:
	int			ParticleID;
	int			ParticleIDEx;
	BOOL		MyCharacterFlag;
	BOOL		EndFlag;
	smOBJ3D     *ObjBip;
};
// ¿ìËÙ´ò»÷Ð§¹û
class AssaSkillHyperSonic :public cASSAEFFECT
{
public:
	AssaSkillHyperSonic();
	~AssaSkillHyperSonic();

	void Start(Unit *character,int liveCount);
	void Main();
	void StopParticle();
	void StopParticleID();
private:

	int			ParticleIDGroup[4];
	BOOL		MyCharacterFlag;
	BOOL		EndFlag;

	POINT3D		LocalPos;
	int			LocalAngle;

	BOOL		LocalPosTransFlag;
};
//º®±ùÖ®¼ý
class AssaSkillCircleTrap :public cASSAEFFECT
{
public:
	AssaSkillCircleTrap();
	~AssaSkillCircleTrap();

	void Start(POINT3D *curPos,POINT3D *desPos,int level);
	void Main();
private:
	int			ParticleID;
	POINT3D     ShootingAngle;
	int			m_ShellType;
	float		VelocityY;
};
class AssaSkillKrishna :public cASSAEFFECT
{
public:
	AssaSkillKrishna();
	~AssaSkillKrishna();

	void Start(Unit *character,int LiveCount);
	void Main();
private:
	int			ParticleID;
	BOOL		MyCharacterFlag;
	BOOL		EndFlag;
};
class AssaSkillBenedic :public cASSAEFFECT
{
public:
	AssaSkillBenedic();
	~AssaSkillBenedic();

	void Start(Unit *character);
	void Main();
private:
	int		ParticleID;
	BOOL	MyCharacterFlag;
};
class AssaSkillBenedicEffect :public cASSAEFFECT
{
public:
	AssaSkillBenedicEffect();
	~AssaSkillBenedicEffect();

	void Start(Unit *character,int LiveCount);
	void Main();
private:
	int			ParticleID;
	BOOL		MyCharacterFlag;
	BOOL		EndFlag;
};
class AssaSkillCoupEffect : public cASSAEFFECT
{
public:
	AssaSkillCoupEffect();
	~AssaSkillCoupEffect();
private:
	smPAT3D*	PatMesh;
	POINT3D		ShootingAngle;
	int			CurrentFrame;
	int			Delay;
	int			BlendStep;
public:
	void Start(POINT3D* pCur, POINT3D* pDest, int delay);
	void Main();
	void Draw(POINT3D* pPosi, POINT3D *pAngle);
};
class AssaSkillTalaria :public cASSAEFFECT
{
public:
	AssaSkillTalaria();
	~AssaSkillTalaria();

	void Start(Unit *character,int LiveCount);
	void Main();
private:
	int			ParticleID;
	BOOL		MyCharacterFlag;
	BOOL		EndFlag;
};
class AssaLevelEffect :public cASSAEFFECT
{
public:
	AssaLevelEffect();
	~AssaLevelEffect();

	void Start(Unit *character);
	void Main();
private:
	int			ParticleID;
	BOOL		MyCharacterFlag;
	BOOL		EndFlag;
};
#endif


