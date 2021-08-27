/*----------------------------------------------------------------------------*
*	ÆÄÀÏ¸í :  AssaParticle
*	ÇÏ´ÂÀÏ :  ¾Æ½Î! ÆÄÆ¼Å¬
*	ÀÛ¼ºÀÏ :  ÃÖÁ¾¾÷µ¥ÀÌÆ® 2002³â 12¿ù
*	Àû¼ºÀÚ :  ¹Ú»ó¿­ 
*-----------------------------------------------------------------------------*/	
#ifndef _ASSAPARTICLE_HEADER_

#define _ASSAPARTICLE_HEADER_

#define ASSA_COLOR_CODE_YELLOW		0x00000001
#define ASSA_COLOR_CODE_BLUE		0x00000002
#define ASSA_COLOR_CODE_GREEN		0x00000003
#define ASSA_COLOR_CODE_VIOLET		0x00000004
#define ASSA_COLOR_CODE_RED			0x00000005


//¿¹¿Ü ÀÌÆåÆ® ÄÚµå 
#define ASSA_PARTICLE_UNIONCORE		0x70000001
#define ASSA_EFFECT_RATOO3			0x70000002

/*----------------------------------------------------------------------------*
*								ÇÔ¼ö 
*-----------------------------------------------------------------------------*/	
void sinAssaParticleProcess(cASSAEFFECT *pEffect); 
int  sinAssaParticleKeyDown();


/*----------------------------------------------------------------------------*
*							Particle	ÇÔ¼ö 
*-----------------------------------------------------------------------------*/	

// ½ºÅÏ 
int AssaParticle_Stune(Unit *pChar , int Time);

// ¿ø ¸¸µé±â 
int AssaMakeCircle(POINT3D *pPosi , char *FileName , int Radius);

// º§Æ® ¿Ã¸®±â
int AssaParticle_RisingBelt(POINT3D *pPosi ,char *FileName,int ContinueTime , int SpeedY );

//»ó½ÂÇü ÆÄÆ¼Å¬ 
int AssaParticle_RisingParticle(POINT3D *pPosi , char *FileName ,int Size ,  int ContinueTime , int Range , int Count , int SpeedY);

//»ó½ÂÇü ¶óÀÎ
int AssaParticle_RisingLine(POINT3D *pPosi , char *FileName , int Size, int ContinueTime , int Range , int Count , int SpeedY);

//»ó½Â °î¼±Çü ¶óÀÎ 
int AssaParticle_RisingRotateLine(POINT3D *pPosi , char *FileName , int ContinueTime , int Range , int Count , int SpeedY);

//»ó½Â °î¼±Çü Á»´õ ½ë³ð
int AssaParticle_RisingRotateLinePower(POINT3D *pPosi , char *FileName,int Range ,int Speed );

//¹°°áÇü ÆÄÆ¼Å¬ 
int AssaParticle_Wave(POINT3D *pPosi , char *FileName ,int Size);

//Light
int AssaParticle_Light(POINT3D *pPosi , char *FileName ,int Size , int Height , int Time);

//ºÐÃâÇü ÆÄÆ¼Å¬ 
int AssaParticle_Spread(POINT3D *pPosi , char *FileName );

//±×³É ³Ð¾îÁö´Â ÀÌ¹ÌÁö ÆÄÆ¼Å¬ 
int AssaParticle_WideFace(POINT3D *pPosi , char *FileName , int Size);

//¸ðÀÌ´Â ÆÄÆ¼Å¬
int AssaParticle_Gather(POINT3D *pPosi , char *FileName ,int Range , int Speed ,int Num);

//µ¹¸é¼­ ¸ðÀÌ´Â ÆÄÆ¼Å¬ 
int AssaParticle_RotateGather(POINT3D *pPosi , char *FileName , int Num);

//±¸¸ð¾ç¿¡ ºûÀ» ¸ðÀº´Ù 
int AssaParticle_BALLLIGHT_GATHER(POINT3D *pPosi , char *FileName );

//±¸¸ð¾ç¿¡ ºûÀ» µ¹¸°´Ù 
int AssaParticle_BALLLIGHT_ROTATE(POINT3D *pPosi , char *FileName ,int Range , int Speed);

//ÀÛÀº¹üÀ§ÀÇ ¶óÀÌÂ¡ ÆÄÆ¼Å¬ 
int AssaParticle_RisingParticleContinue(POINT3D *pPosi , char *FileName ,int Size ,int Range , int SpeedY);

//µ¹¸é¼­ ÆÛÁö´Â ÆÄÆ¼Å¬ 
int AssaParticle_RotateWide(POINT3D *pPosi , char *FileName ,int Range , int SpeedY );

//ÆÛÁö´Â ÆÄÆ¼Å¬ 
int AssaParticle_Wide(POINT3D *pPosi , char *FileName ,int Num , int Time);

//ÅÍÁ³´Ù°¡ ¸ðÀÎ´Ù 
int AssaParticle_BombGather(cASSAEFFECT *pEffect);

//ÁÖº¯Áö¿ªÀÇ ÆÄÆ¼Å¬ 
int AssaParticle_Area_Particle(POINT3D *Posi , char *FileName , int Range , int Time);

//½ºÆä¼È Hit
int AssaParticle_SpecialHit(POINT3D *pPosi , int Time); 

//³¯Ä¡±â ÀÜ»ó 
int AssaParticle_After_Image(POINT3D *Posi , char *FileName , int Range , int Time);

//ÇÇ¾î½Ì ÆÄÆ¼Å¬
int AssaParticle_Piercing(cASSAEFFECT *pEffect);

//ÇÇ¾î½Ì Ä® ÁÖº¯ ÀÜ»ó 
int AssaParticle_Piercing_Aura(cASSAEFFECT *pEffect);

//Å¸°Ý ÆÄÆ¼Å¬ (Brandish¿¡¼­ »ç¿ë)
int AssaParticle_SpecialHit2(POINT3D *pPosi , int Time,int Kind=0);

//À©µð¿ë ÆÄÆ¼Å¬ 
int AssaParticle_Windy2(Unit *pChar);

//È¦¸® ¸®ÇÃ·º¼ÇÇü ÆÄÆ¼Å¬ 
int AssaParticle_Holy_Reflection(cASSAEFFECT *pEffect);

//È¦¸® ¸¶ÀÎµå 
int AssaParticle_HolyMind(POINT3D *pPosi , int Flag=0);

//Light
int AssaParticle_Char_Light(Unit *pChar ,  DWORD ColorCODE , int Time ,int MaxAlpha, int  SizeW ,int SizeH=0 );

//Light2
int AssaParticle_Char_Light2(Unit *pChar ,  DWORD ColorCODE , int Time );

//UnionCore
int sinAssaUnionCoreEffect(Unit *pChar);

int sinEffect_Ratoo_Aura(Unit *pChar);

int sinEffect_Ratoo_Aura2(Unit *pChar);

//ÉñÁ¦³å´Ì
int sinEffect_Benedic3(Unit *pChar);
#endif
