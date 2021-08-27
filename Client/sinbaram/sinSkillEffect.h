/*----------------------------------------------------------------------------*
*	ÆÄÀÏ¸í :  sinSkillEffect.h	
*	ÇÏ´ÂÀÏ :  ÀÌÆåÆ® °ü·Ã ÀÛ¾÷ (°¢°¢ÀÇ ÀÌÆåÆ® )
*	ÀÛ¼ºÀÏ :  ÃÖÁ¾¾÷µ¥ÀÌÆ® 2002³â 6¿ù
*	Àû¼ºÀÚ :  ¹Ú»ó¿­ 
*-----------------------------------------------------------------------------*/	

int sinSkillTestKey(); //½ºÅ³ Å×½ºÆ® Key

/*----------------------------------------------------------------------------*
*							½Ã½ºÅÛ
*-----------------------------------------------------------------------------*/	
void sinInitSkillEffect();
void sinSkillEffectMove(cSINEFFECT2 *pEffect);	//Move
void sinProcess7();
extern int Index2;
/*----------------------------------------------------------------------------*
*						¸ð¶óÀÌ¿Â ½ºÅ³ 
*-----------------------------------------------------------------------------*/	
//////////// ³ªÀÌÆ®
int sinEffect_Sword_Blast_Particle(POINT3D *pPosi);
int sinEffect_Sword_Blast(Unit *pChar , Unit *desChar);
int sinEffect_Holy_Body(Unit *pChar);
int sinEffect_Holy_Body_Cross(Unit *pChar );
int sinEffect_Holy_Body_Particle(POINT3D *pPosi);	


//////////// ¾ÆÆ²¶õÅ¸ 
int sinEffect_Farina(Unit *pChar , Unit *desChar);
int sinEffect_Farina_Particle(POINT3D *pPosi);
int sinEffect_VigorSpear(Unit *pChar , Unit *desChar);
int sinEffect_VigorSpear_Particle(POINT3D *pPosi);
int sinEffect_Shield_Strike(POINT3D *pPosi);
int sinEffect_Shield_Strike_Particle(POINT3D *pPosi);

//////////// ÇÁ¸®½ºÆ® 
//int MultiSpark_Effect(Unit *pChar , Unit *desChar);
int sinEffect_MultiSpark_Particle(POINT3D *pPosi);
int sinEffect_MultiSpark_Particle2(POINT3D *pPosi);
int sinEffect_MultiSpark(Unit *pChar , Unit *desChar , int Num);
int sinEffect_HolyMind(Unit *pChar , int Time);
int sinEffect_HolyMind_Particle(POINT3D *pPosi);
int sinEffect_SilraphimEffect(POINT3D *pPosi);
int sinEffect_TenusEffect(POINT3D *pPosi);
int sinEffect_Healing(Unit *pChar);
int sinEffect_Healing_Particle(POINT3D *pPosi);
int sinEffect_Healing_Particle2(POINT3D *pPosi);
int sinEffect_HealParticle3(POINT3D *pPosi ,int Mat ,int Num , int Size , int Time , int Gravity );

//Å×½ºÆ® 
int sinEffect_Healing2(Unit *pChar);

//////////// ¸ÞÁö¼Ç
int sinEffect_Agony(Unit *pChar);
int sinEffect_Agony_Particle(POINT3D *pPosi);
int sinEffect_Zenith(Unit *pChar,int Time,int Flag = 0);
int sinEffect_Zenith_Particle(POINT3D *pPosi , int R , int G , int B);
int sinEffect_FireBolt(Unit *pChar , Unit *desChar);
int sinEffect_FireBolt_Particle(POINT3D *pPosi);
int sinEffect_FireBolt_Particle2(POINT3D *pPosi); //¾îÄÉÇÏ´Ùº¸´Ï ÀÏÄÉ‰ç´Ù µÈÀå!

//////////// °ø¿ë ÄÚµå
int sinEffect_Bomb6(POINT3D *pPosi); //ÆøÆÈ
int sinEffect_Bomb6_Particle(POINT3D *pPosi);
int sinEffect_SkillHit(DWORD CODE , POINT3D *pPosi); //½ºÅ³ Hit ÀÌÆåÆ® 
int sinEffect_SetCharPosi(cSINEFFECT2 *pEffect); //ÁÂÇ¥ ¼ÂÆÃ
int sinEfect_CheckCrash(cSINEFFECT2 *pEffect);

int sinEffect_StartMagic2(POINT3D *pPosi,int CharFlag);
int sinEffect_StartMagic(POINT3D *pPosi , int CharFlag,int Type = 0);

int AddCodeEffectTime(Unit *pChar,int Code);

//Á÷ÐÇ»ðÓê
int sinEffect_Silraphim(Unit *pChar);
//ËõÐ¡Ö®Êõ
int sinEffect_Tenus(Unit *pChar);
//ÉñÊ¥Ï´Àñ
int sinEffect_Anima(Unit *pChar,int Time,int Flag);
extern int MatFireBolt[3];
