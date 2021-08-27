#include "StdAfx.h"
#include "..\\SinBaram\\AssaEffect.h"
#include "hoAssaParticleEffect.h"

#include "HoNewParticleLinkHeader.h"
#include "AssaParticle.h"


int AssaParticle_LineIn(POINT3D *pPosi, char *texName, int continueTime, int speed)
{
	POINT3D curPos;
	POINT3D rand;
   	for(int index = 0; index < continueTime*4; index++)
	{
		//ÆÄÆ¼Å¬ÀÌ ³ª¿Ã ¿µ¿ª.. 
        rand.x = GetRandomPos(-18000/1000, 18000/1000);
		rand.y = GetRandomPos(-18000/1000, 18000/1000);
		rand.z = GetRandomPos(-18000/1000, 18000/1000);
		
		double length = sqrt((float)rand.x*(float)rand.x+
			                 (float)rand.y*(float)rand.y+
  	 						 (float)rand.z*(float)rand.z);
		
	 	int range = GetRandomPos(20000, 21000);
 		curPos.x = int(((float)rand.x/length)*(float)range+(float)pPosi->x);
		curPos.y = int(((float)rand.y/length)*(float)range+(float)pPosi->y);
		curPos.z = int(((float)rand.z/length)*(float)range+(float)pPosi->z);

     	if(texName == NULL)
			Assa = SetAssaEffect( int(float(range)/(400.f+(float)speed)), "flare.tga", 0, &curPos, 0);
		else
			Assa = SetAssaEffect( int(float(range)/(400.f+(float)speed)), texName, 0, &curPos, 0);

		
		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE;
		
		length =  sqrt((double)((rand.x)*(rand.x)+
					   (rand.y)*(rand.y)+
  				       (rand.z)*(rand.z)));
		
  		if(length == 0)
			length = 1;
 		
        cAssaEffect[Assa]->MOVECODE = ASSA_MOVE;
 		cAssaEffect[Assa]->Face.r = 50;
		cAssaEffect[Assa]->Face.g = 100;
		cAssaEffect[Assa]->Face.b = 255;
		cAssaEffect[Assa]->Face.Transparency = 255;
 		cAssaEffect[Assa]->Time = -(index/2);
  	 	cAssaEffect[Assa]->MoveSpeed.x = -int(float(rand.x)/length*(400.f+(float)speed));
		cAssaEffect[Assa]->MoveSpeed.y = -int(float(rand.y)/length*(400.f+(float)speed));

		cAssaEffect[Assa]->MoveSpeed.z = -int(float(rand.z)/length*(400.f+(float)speed));
		
		//ÆÄÆ¼Å¬ÀÇ ³ÐÀÌ..
 		cAssaEffect[Assa]->Size.w = 500;

		//ÆÄÆ¼Å¬ÀÇ ±æÀÌ..
		POINT3D inScale;
  		inScale.x = int((rand.x)/(float)length*8000.f);
		inScale.y = int((rand.y)/(float)length*8000.f);
		inScale.z = int((rand.z)/(float)length*8000.f);
		
		cAssaEffect[Assa]->ScalePosi.x = -inScale.x;
		cAssaEffect[Assa]->ScalePosi.y = -inScale.y;
		cAssaEffect[Assa]->ScalePosi.z = -inScale.z;
	}

	return TRUE;
}


/*----------------------------------------------------------------------------*
* LineÆÄÆ¼Å¬ÀÌ ³ª°¡´Â ÇÔ¼ö.
* pPosi: ÆÄÆ¼Å¬ÀÌ ³ª¿Ã À§Ä¡.
* texName: ÆÄÆ¼Å¬ ÅØ½ºÃÄ.
* continueTime: ÆÄÆ¼Å¬ÀÌ ³ª¿Ã ½Ã°£..
* speed; ÆÄÆ¼Å¬ÀÇ ¼Óµµ..
*-----------------------------------------------------------------------------*/	
int AssaParticle_LineOut(POINT3D *pPosi , char *texName, int continueTime, int speed)
{
    int delay = 20;
	POINT3D curPos;
	POINT3D rand;
	for(int index = 0; index < continueTime*4; index++)
	{
		//ÆÄÆ¼Å¬ÀÌ ³ª¿Ã ¿µ¿ª..
 		rand.x = GetRandomPos(-10000, 10000)/100;
		rand.y = GetRandomPos(-10000, 10000)/100;
		rand.z = GetRandomPos(-10000, 10000)/100;
		
		double length = sqrt((float)rand.x*(float)rand.x+
			                 (float)rand.y*(float)rand.y+
							 (float)rand.z*(float)rand.z);
		
 		int range = GetRandomPos(5000,7000);
     	curPos.x = int(float(rand.x)/length*(float)range+(float)pPosi->x);
		curPos.y = int(float(rand.y)/length*(float)range+(float)pPosi->y);
		curPos.z = int(float(rand.z)/length*(float)range+(float)pPosi->z);
		
 		if(texName == NULL)
			Assa = SetAssaEffect(150-(speed/2),"flare.tga",0,&curPos,0);                
		else
			Assa = SetAssaEffect(150-(speed/2),texName,0,&curPos,0);                
		
  		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE;
  		cAssaEffect[Assa]->Time = GetRandomPos(-2,0)-delay;
		
		if(length == 0)
			length = 1;
 		
  		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE;
  	 	cAssaEffect[Assa]->MoveSpeed.x = int(float(rand.x)/length*(200.f+speed*3));
		cAssaEffect[Assa]->MoveSpeed.y = int(float(rand.y)/length*(200.f+speed*3));
		cAssaEffect[Assa]->MoveSpeed.z = int(float(rand.z)/length*(200.f+speed*3));
		
		//ÆÄÆ¼Å¬ÀÇ ³ÐÀÌ..
 		cAssaEffect[Assa]->Size.w = 1000;
		cAssaEffect[Assa]->Face.r = 50;
		cAssaEffect[Assa]->Face.g = 100;
		cAssaEffect[Assa]->Face.b = 255;

		//ÆÄÆ¼Å¬ÀÇ ±æÀÌ..
		POINT3D destPos;
  		destPos.x = int(float(rand.x)/length*10000.f);
		destPos.y = int(float(rand.y)/length*10000.f);
		destPos.z = int(float(rand.z)/length*10000.f);
		
		cAssaEffect[Assa]->ScalePosi.x = -destPos.x;
		cAssaEffect[Assa]->ScalePosi.y = -destPos.y;
		cAssaEffect[Assa]->ScalePosi.z = -destPos.z;
	}
	
	return TRUE;
}

void SkillGodBless(Unit *pChar)
{
	POINT3D pos;
	memcpy(&pos, &pChar->Posi, sizeof(POINT3D));
   	g_NewParticleMgr.Start("GodlyShield", pos, 0.3f);
	pos.y += 8000;
	
	POINT3D curPos;
	POINT3D rand;

    for(int index = 0; index < 20; index++)
	{
        rand.x = GetRandomPos(-18, 18);
		rand.y = GetRandomPos(-18, 18);
		rand.z = GetRandomPos(-18, 18);
		
		double length = sqrt((float)rand.x*(float)rand.x+(float)rand.y*(float)rand.y+(float)rand.z*(float)rand.z);
		
		if(length == 0)
			length = 1;
	 	int range = GetRandomPos(19000, 20000);
 		curPos.x = int(((float)rand.x/length)*(float)range+(float)pos.x);
		curPos.y = int(((float)rand.y/length)*(float)range+(float)pos.y);
		curPos.z = int(((float)rand.z/length)*(float)range+(float)pos.z);
		
		Assa = SetAssaEffect( 80, "flare.tga", 0, &curPos, 0);
		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE;
		
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE;
		
 		cAssaEffect[Assa]->Face.r = 100;
		cAssaEffect[Assa]->Face.g = 180;
		cAssaEffect[Assa]->Face.b = 230;
		cAssaEffect[Assa]->Face.Transparency = 255;
 		cAssaEffect[Assa]->Time = -(index/2);
  	 	cAssaEffect[Assa]->MoveSpeed.x = -int(float(rand.x)/length*400.f);
		cAssaEffect[Assa]->MoveSpeed.y = -int(float(rand.y)/length*400.f);
		cAssaEffect[Assa]->MoveSpeed.z = -int(float(rand.z)/length*400.f);
		
 		cAssaEffect[Assa]->Size.w = 400;

		POINT3D inScale;
  		inScale.x = int((rand.x)/(float)length*8000.f);
		inScale.y = int((rand.y)/(float)length*8000.f);
		inScale.z = int((rand.z)/(float)length*8000.f);
		
		cAssaEffect[Assa]->ScalePosi.x = -inScale.x;
		cAssaEffect[Assa]->ScalePosi.y = -inScale.y;
		cAssaEffect[Assa]->ScalePosi.z = -inScale.z;
	}
	
    for(int index = 0; index < 40; index++)
	{
   		rand.x = GetRandomPos(-100, 100);
		rand.y = GetRandomPos(-100, 100);
		rand.z = GetRandomPos(-100, 100);
		
		double length = sqrt((float)rand.x*(float)rand.x+(float)rand.y*(float)rand.y+(float)rand.z*(float)rand.z);
		
		if(length == 0)
			length = 1;
		
 		int range = GetRandomPos(5000,7000);
     	curPos.x = int(float(rand.x)/length*(float)range+(float)pos.x);
		curPos.y = int(float(rand.y)/length*(float)range+(float)pos.y);
		curPos.z = int(float(rand.z)/length*(float)range+(float)pos.z);
		
		Assa = SetAssaEffect(200,"flare.tga",0,&curPos,0);                
		
 		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE;
   		cAssaEffect[Assa]->Time = -(15+index/2);
		
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE;
  	 	cAssaEffect[Assa]->MoveSpeed.x = int(float(rand.x)/length*(150.f));
		cAssaEffect[Assa]->MoveSpeed.y = int(float(rand.y)/length*(150.f));
		cAssaEffect[Assa]->MoveSpeed.z = int(float(rand.z)/length*(150.f));
		
		//ÆÄÆ¼Å¬ÀÇ ³ÐÀÌ..
 		cAssaEffect[Assa]->Size.w = 500;
		cAssaEffect[Assa]->Face.r = 100;
		cAssaEffect[Assa]->Face.g = 180;
		cAssaEffect[Assa]->Face.b = 230;
		cAssaEffect[Assa]->Face.Transparency = 255;

		//ÆÄÆ¼Å¬ÀÇ ±æÀÌ..
		POINT3D destPos;
   		destPos.x = int(float(rand.x)/length*12000.f);
		destPos.y = int(float(rand.y)/length*12000.f);
		destPos.z = int(float(rand.z)/length*12000.f);
		
		cAssaEffect[Assa]->ScalePosi.x = -destPos.x;
		cAssaEffect[Assa]->ScalePosi.y = -destPos.y;
		cAssaEffect[Assa]->ScalePosi.z = -destPos.z;
	}

}

int AssaParticle_HolyValor_Jang(Unit *pChar)
{
	if(GetAssaCodeEffect(pChar, DRASTIC_ACTION))
		return FALSE;

	POINT3D pos;
	memcpy(&pos, &pChar->Posi, sizeof(POINT3D));
   	pos.y += 8000;
	
	POINT3D curPos;
	POINT3D rand;

    for(int index = 0; index < 20; index++)
	{
        rand.x = GetRandomPos(-18, 18);
		rand.y = GetRandomPos(-18, 18);
		rand.z = GetRandomPos(-18, 18);
		
		double length = sqrt((float)rand.x*(float)rand.x+(float)rand.y*(float)rand.y+(float)rand.z*(float)rand.z);
		
		if(length == 0)
			length = 1;
	 	int range = GetRandomPos(19000, 20000);
 		curPos.x = int(((float)rand.x/length)*(float)range+(float)pos.x);
		curPos.y = int(((float)rand.y/length)*(float)range+(float)pos.y);
		curPos.z = int(((float)rand.z/length)*(float)range+(float)pos.z);
		
		Assa = SetAssaEffect( 80, "flare.tga", 0, &curPos, 0);
		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE;
		
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE;
		

 		cAssaEffect[Assa]->Face.r = 100;
		cAssaEffect[Assa]->Face.g = 180;
		cAssaEffect[Assa]->Face.b = 230;
		cAssaEffect[Assa]->Face.Transparency = 255;
 		cAssaEffect[Assa]->Time = -(index/2);
  	 	cAssaEffect[Assa]->MoveSpeed.x = -int(float(rand.x)/length*400.f);
		cAssaEffect[Assa]->MoveSpeed.y = -int(float(rand.y)/length*400.f);
		cAssaEffect[Assa]->MoveSpeed.z = -int(float(rand.z)/length*400.f);
		
 		cAssaEffect[Assa]->Size.w = 400;

		POINT3D inScale;
  		inScale.x = int((rand.x)/(float)length*8000.f);
		inScale.y = int((rand.y)/(float)length*8000.f);
		inScale.z = int((rand.z)/(float)length*8000.f);
		
		cAssaEffect[Assa]->ScalePosi.x = -inScale.x;
		cAssaEffect[Assa]->ScalePosi.y = -inScale.y;
		cAssaEffect[Assa]->ScalePosi.z = -inScale.z;
	}

    for(int index = 0; index < 40; index++)
	{
   		rand.x = GetRandomPos(-100, 100);
		rand.y = GetRandomPos(-100, 100);
		rand.z = GetRandomPos(-100, 100);
		
		double length = sqrt((float)rand.x*(float)rand.x+(float)rand.y*(float)rand.y+(float)rand.z*(float)rand.z);
		
		if(length == 0)
			length = 1;
		
 		int range = GetRandomPos(5000,7000);
     	curPos.x = int(float(rand.x)/length*(float)range+(float)pos.x);
		curPos.y = int(float(rand.y)/length*(float)range+(float)pos.y);
		curPos.z = int(float(rand.z)/length*(float)range+(float)pos.z);
		
		Assa = SetAssaEffect(200,"flare.tga",0,&curPos,0);                
		
 		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE;
   		cAssaEffect[Assa]->Time = -(15+index/2);
		
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE;
  	 	cAssaEffect[Assa]->MoveSpeed.x = int(float(rand.x)/length*(150.f));
		cAssaEffect[Assa]->MoveSpeed.y = int(float(rand.y)/length*(150.f));
		cAssaEffect[Assa]->MoveSpeed.z = int(float(rand.z)/length*(150.f));
		
 		cAssaEffect[Assa]->Size.w = 500;
		cAssaEffect[Assa]->Face.r = 100;
		cAssaEffect[Assa]->Face.g = 180;
		cAssaEffect[Assa]->Face.b = 230;
		cAssaEffect[Assa]->Face.Transparency = 255;

		POINT3D destPos;
   		destPos.x = int(float(rand.x)/length*12000.f);
		destPos.y = int(float(rand.y)/length*12000.f);
		destPos.z = int(float(rand.z)/length*12000.f);
		
		cAssaEffect[Assa]->ScalePosi.x = -destPos.x;
		cAssaEffect[Assa]->ScalePosi.y = -destPos.y;
		cAssaEffect[Assa]->ScalePosi.z = -destPos.z;
	}
	
	return TRUE;
}
int AssaParticle_HolyValorIsUse(Unit *pChar)
{
	return GetAssaUseEffect(pChar,HOLY_ACTION);
}
int AssaParticle_HolyValor_JangEffect(Unit *pChar, int maxTime)
{
	int SkillTime = maxTime * 70;

	if (AddAssaCodeEffectTime(pChar,HOLY_ACTION,SkillTime) == 0)
	{
		int i = GetAssaEffect();
		cASSAChar *partChar = new cASSAChar;
		partChar->Start(pChar, HOLY_VALOR_JANG, SkillTime);
		cAssaEffect[i] = partChar;

		return TRUE;
	}

	return FALSE;
}

int AssaParticle_HolyValor_Member(Unit *pChar, int maxTime)
{
	if(GetAssaCodeEffect(pChar, DRASTIC_ACTION))
		return FALSE;

	int SkillTime = maxTime * 70;

 	if (AddAssaCodeEffectTime(pChar,HOLY_ACTION,SkillTime) == 0)
	{
		int i = GetAssaEffect();
		cASSAChar *partChar = new cASSAChar;
		partChar->Start(pChar, HOLY_VALOR_MEMBER, SkillTime);
		cAssaEffect[i] = partChar;
		return TRUE;
	}
	return FALSE;
}

int AssaParticle_DrasticSpirit_Jang(Unit *pChar)
{
	POINT3D pos;
    memcpy(&pos,&pChar->Posi,sizeof(POINT3D));

 	pos.y += 7000;
	POINT3D curPos;
	POINT3D rand;

    for(int index = 0; index < 20; index++)
	{
        rand.x = GetRandomPos(-18, 18);
		rand.y = GetRandomPos(-18, 18);
		rand.z = GetRandomPos(-18, 18);
		
		double length = sqrt((float)rand.x*(float)rand.x+(float)rand.y*(float)rand.y+(float)rand.z*(float)rand.z);
		
		if(length == 0)
			length = 1;
	 	int range = GetRandomPos(19000, 20000);
 		curPos.x = int(((float)rand.x/length)*(float)range+(float)pos.x);
		curPos.y = int(((float)rand.y/length)*(float)range+(float)pos.y);
		curPos.z = int(((float)rand.z/length)*(float)range+(float)pos.z);
		
		Assa = SetAssaEffect( 80, "flare.tga", 0, &curPos, 0);
		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE;
		
 		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE;
  		cAssaEffect[Assa]->Face.r = 130;
		cAssaEffect[Assa]->Face.g = 100;
		cAssaEffect[Assa]->Face.b = 220;
		cAssaEffect[Assa]->Face.Transparency = 200;
 		cAssaEffect[Assa]->Time = -(index/2);
  	 	cAssaEffect[Assa]->MoveSpeed.x = -int(float(rand.x)/length*400.f);
		cAssaEffect[Assa]->MoveSpeed.y = -int(float(rand.y)/length*400.f);
		cAssaEffect[Assa]->MoveSpeed.z = -int(float(rand.z)/length*400.f);
 		cAssaEffect[Assa]->Size.w = 400;

		POINT3D inScale;
  		inScale.x = int((rand.x)/(float)length*8000.f);
		inScale.y = int((rand.y)/(float)length*8000.f);
		inScale.z = int((rand.z)/(float)length*8000.f);
		
		cAssaEffect[Assa]->ScalePosi.x = -inScale.x;
		cAssaEffect[Assa]->ScalePosi.y = -inScale.y;
		cAssaEffect[Assa]->ScalePosi.z = -inScale.z;
	}
	
    for(int index = 0; index < 40; index++)
	{
  		rand.x = GetRandomPos(-100, 100);
		rand.y = GetRandomPos(-100, 100);
		rand.z = GetRandomPos(-100, 100);
		
		double length = sqrt((float)rand.x*(float)rand.x+(float)rand.y*(float)rand.y+(float)rand.z*(float)rand.z);
		
		if(length == 0)
			length = 1;
		
		int range = GetRandomPos(5000,7000);
     	curPos.x = int(float(rand.x)/length*(float)range+(float)pos.x);
		curPos.y = int(float(rand.y)/length*(float)range+(float)pos.y);
		curPos.z = int(float(rand.z)/length*(float)range+(float)pos.z);
		
		Assa = SetAssaEffect(200,"flare.tga",0,&curPos,0);                
		
		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE;
  		cAssaEffect[Assa]->Time = -(15+index/2);
		
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE;
  	 	cAssaEffect[Assa]->MoveSpeed.x = int(float(rand.x)/length*(150.f));
		cAssaEffect[Assa]->MoveSpeed.y = int(float(rand.y)/length*(150.f));
		cAssaEffect[Assa]->MoveSpeed.z = int(float(rand.z)/length*(150.f));
		
    	cAssaEffect[Assa]->Size.w = 500;
 		cAssaEffect[Assa]->Face.r = 140;
		cAssaEffect[Assa]->Face.g = 100;
		cAssaEffect[Assa]->Face.b = 220;
		cAssaEffect[Assa]->Face.Transparency = 255;

		POINT3D destPos;
   		destPos.x = int(float(rand.x)/length*12000.f);
		destPos.y = int(float(rand.y)/length*12000.f);
		destPos.z = int(float(rand.z)/length*12000.f);
		
		cAssaEffect[Assa]->ScalePosi.x = -destPos.x;
		cAssaEffect[Assa]->ScalePosi.y = -destPos.y;
		cAssaEffect[Assa]->ScalePosi.z = -destPos.z;
	}
	
	return TRUE;
}
int AssaParticle_DrasticSpirit_JangEffect(Unit *pChar,int maxTime)
{
	if(GetAssaCodeEffect(pChar,HOLY_ACTION))
		return FALSE;

	int SkillTime = maxTime * 70;

	if (AddAssaCodeEffectTime(pChar,DRASTIC_ACTION,SkillTime) == 0)
	{
		int i = GetAssaEffect();
		cASSAChar *partChar = new cASSAChar;
		partChar->Start(pChar, DRASTIC_SPIRIT_JANG,SkillTime);
		cAssaEffect[i] = partChar;
		return TRUE;
	}
	return FALSE;
}
int AssaParticle_DrasticSpirit_Member(Unit *pChar, int maxTime)
{
	//°°Àº Ä³¸¯ÅÍ°¡ À¯Áö ½ºÅ³À» ¾²¸é ¾ø¾ÖÁØ´Ù.
 	StopAssaCodeEffect(pChar, DRASTIC_ACTION);
	StopAssaCodeEffect(pChar, HOLY_ACTION);
	
	//½ÇÁ¦·Î À¯ÁöµÇ´Â ÆÄÆ¼Å¬ È£Ãâ..
 	int i = GetAssaEffect();
 	cASSAChar *partChar = new cASSAChar;
	partChar->Start(pChar, DRASTIC_SPIRIT_MEMBER, maxTime*70);
	cAssaEffect[i] = partChar;
	return TRUE;
}

int AssaParticle_Windy(Unit *pChar, int maxTime)
{
   	//StopAssaCodeEffect(pChar, WINDY_ACTION, 3);

	int SkillTime = maxTime*70;

	if (AddAssaCodeEffectTime(pChar,WINDY_ACTION,SkillTime) == 0)
	{
		int i = GetAssaEffect();
		cASSAChar *partChar = new cASSAChar;
		partChar->Start(pChar, WINDY_ACTION, maxTime*70);
		cAssaEffect[i] = partChar;
		return TRUE;
	}
	return FALSE;
}

void SkillParticle_FrostJavelin(Unit *pChar, float time)
{
	float SkillTime = time * 70;

	if (AddAssaCodeEffectTime(pChar,SKILL_FROST_JAVELIN,int(SkillTime)) == 0)
	{
		int i = GetAssaEffect();
		cASSAChar *partChar = new cASSAChar;
		partChar->Start(pChar, SKILL_FROST_JAVELIN, int(time*70.f));
		cAssaEffect[i] = partChar;
	}
}

int AssaParticle_TwistJavelinShot(POINT3D *pPosi, POINT3D *pDesti)
{
  	Assa = SetAssaEffect(0,"TwistJavelin2.ASE",0,pPosi,0);
	
	cAssaEffect[Assa]->Time = 0;
	cAssaEffect[Assa]->AniMaxCount = 60;
	cAssaEffect[Assa]->AniDelayTime = 4;
 	cAssaEffect[Assa]->MOVECODE = ASSA_ANGLE_ROTATE;
	cAssaEffect[Assa]->Angle.y = ANGLE_180;

	auto sPosition = GetRadian3D( pPosi->x, pPosi->y, pPosi->z, pDesti->x, pDesti->y, pDesti->z);
	cAssaEffect[Assa]->Angle.x =  sPosition.iX;
	cAssaEffect[Assa]->Angle.y =  sPosition.iY;
	cAssaEffect[Assa]->Angle.z =  sPosition.iZ;
	
	cAssaEffect[Assa]->Angle.y = (-sPosition.iY + ANGLE_180)&ANGCLIP;
	cAssaEffect[Assa]->NotFadeIn = TRUE;
	cAssaEffect[Assa]->ARotateSpeed.z = 200;
	int i = GetAssaEffect();
	cASSAPARTSHOT *partShot = new cASSAPARTSHOT;
	partShot->Start(pPosi, pDesti, cAssaEffect[Assa], SKILL_TWIST_JAVELIN);
	cAssaEffect[i] = partShot;

	return TRUE;
}

int AssaParticle_FireJavelin(POINT3D *pPosi, POINT3D *pDesti)
{
    int i = GetAssaEffect();
	cASSAPARTSHOT *partShot = new cASSAPARTSHOT;
	partShot->Start(pPosi, pDesti, SKILL_FIRE_JAVELIN);
	cAssaEffect[i] = partShot;

	return TRUE;
}

int AssaParticle_FireJavelin(Unit *pChar, POINT3D *pDesti)
{
     int i = GetAssaEffect();
	cASSAPARTSHOT *partShot = new cASSAPARTSHOT;

	partShot->Start(pChar, pDesti, SKILL_FIRE_JAVELIN);
	cAssaEffect[i] = partShot;

	return TRUE;
}

int AssaParticle_Star(POINT3D *pPosi)
{
	POINT3D curPos;
   	for(int index = 0; index < 40; index++)
	{
	 	curPos.x = rand()%10000-5000+pPosi->x;
 		curPos.y = rand()%10000-5000+pPosi->y;
		curPos.z = rand()%10000-5000+pPosi->z;
		
		Assa = SetAssaEffect(50,"star04B_01.bmp",0,&curPos,0);
		AssaGetAniFileMat(cAssaEffect[Assa]);
		int temp = rand()%4000-2000;
 		cAssaEffect[Assa]->Size.w = 4000+temp;
		cAssaEffect[Assa]->Size.h = 4000+temp;
		cAssaEffect[Assa]->AniDelayTime = 10;
		cAssaEffect[Assa]->Time = -index*2-30;
		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_BILLBOARD;
	}
	g_NewParticleMgr.Start("HolyValor", *pPosi);
	return TRUE;
}

int AssaParticle_DivineLighting(Unit *pChar)
{
	int i = GetAssaEffect();
	cASSAPARTSHOT *partShot = new cASSAPARTSHOT;
	
	POINT3D curPos;
	POINT3D desPos;
	curPos.x = pChar->pX;
	curPos.y = pChar->pY+100000;
	curPos.z = pChar->pZ;

	desPos.x = pChar->pX;
	desPos.y = pChar->pY+5000;
	desPos.z = pChar->pZ;
	partShot->Start(&curPos, &desPos, ASSA_SHOT_SPARK);
	cAssaEffect[i] = partShot;
	
	return TRUE;
}

void SkillCelestialChainLighting(Unit **pCharList, int charCount)
{
	//if(charCount < 2)
		//return;
	int i = GetAssaEffect();
	cASSAPARTSHOT *partShot = new cASSAPARTSHOT;
	
	POINT3D curPos;
	POINT3D desPos;
	curPos.x = pCharList[0]->pX;
	curPos.y = pCharList[0]->pY+100000;
	curPos.z = pCharList[0]->pZ;

	desPos.x = pCharList[0]->pX;
	desPos.y = pCharList[0]->pY+5000;
	desPos.z = pCharList[0]->pZ;
	partShot->Start(&curPos, &desPos, ASSA_SHOT_SPARK);
	partShot->SetChainLighting(pCharList, charCount);
	cAssaEffect[i] = partShot;
}

int AssaParticle_Sprak(POINT3D *pPosi)
{
	for(int index = 0; index < 5; index++)
	{
		int i = GetAssaEffect();
		cASSAPARTSPARK *partSpark = new cASSAPARTSPARK;
		
		partSpark->Start(pPosi);
		partSpark->Time = GetRandomPos(0,20);
		cAssaEffect[i] = partSpark;
	}
	
	SetDynLight( pPosi->x, pPosi->y, pPosi->z, 255, 255, 255, 255, 100, 2);
	g_NewParticleMgr.Start("DivineLightning", *pPosi);
	return TRUE;
}

int AssaParticle_ColumnOfWater(POINT3D *pPosi, POINT3D *pDesti, int level)
{
   	if(level < 1 || level > 10)
		return false;
	
	if(level == 1 || level == 2 || level == 3)
		Assa = SetAssaEffect(0,"ColumnOfWaterLV_123.ASE",0,pPosi,0);
	else if(level == 4 || level == 5 || level == 6)
		Assa = SetAssaEffect(0,"ColumnOfWaterLV_456.ASE",0,pPosi,0);
	else if(level == 7 || level == 8 || level == 9)
		Assa = SetAssaEffect(0,"ColumnOfWaterLV_789.ASE",0,pPosi,0);
	else if(level == 10)
		Assa = SetAssaEffect(0,"ColumnOfWaterLV_10.ASE",0,pPosi,0);
	else 
		return false;
	
	cAssaEffect[Assa]->AniMaxCount = 20;
	cAssaEffect[Assa]->AniDelayTime = 4;
	cAssaEffect[Assa]->MOVECODE = ASSA_ANGLE_ROTATE;
 	cAssaEffect[Assa]->ARotateSpeed.y = -50;
	
	
	int i = GetAssaEffect();
	cASSAPARTSHOT *partShot = new cASSAPARTSHOT;
	partShot->Start(pPosi, pDesti, cAssaEffect[Assa]);
	cAssaEffect[i] = partShot;
	
	return TRUE;
}

int AssaParticle_ColumnOfWaterHit(POINT3D *pPosi)
{
    Assa = SetAssaEffect(0,"ColumnOfWaterHit.ASE",0,pPosi,0);                 
	cAssaEffect[Assa]->AniMaxCount = 20;
	cAssaEffect[Assa]->AniDelayTime = 4;
	g_NewParticleMgr.Start("ColumnOfWater2", *pPosi);
	return TRUE;
}

int AssaParticle_EnchantWeaponIceJang(Unit *pChar, int maxTime)
{
    StopAssaCodeEffect(pChar, ENCHANT_WEAPON, 3);
	int i = GetAssaEffect();
  	cASSAChar *partChar = new cASSAChar;
	partChar->Start(pChar, ENCHANT_WEAPON_ICE, maxTime*70, 1.0f);
	cAssaEffect[i] = partChar;
	
	POINT3D pos;
	pos.x = pChar->pX;
	pos.y = pChar->pY+2000;
	pos.z = pChar->pZ;
	g_NewParticleMgr.Start("EnchantWeaponJang", pos);
	return TRUE;
}

void SkillImpulsionLight(Unit *pChar, float time)
{
	StopAssaCodeEffect(pChar, IMPULSION_LIGHT, 3);
	int i = GetAssaEffect();
  	cASSAChar *partChar = new cASSAChar;
	partChar->Start(pChar, IMPULSION_LIGHT, int(time * 70.f), 1.0f);
	cAssaEffect[i] = partChar;
}

void SkillImpulsionLightHit(POINT3D *pos)
{
	StartSkill(pos->x, pos->y, pos->z, 0, 0, 0, SKILL_GRAND_SMASH);
	SetDynLight( pos->x,pos->y,pos->z, 0,100,50,0, 250 , 5);
	g_NewParticleMgr.Start("Skill4ImpulsionHit1", *pos);
}

int AssaParticle_EnchantWeaponFireJang(Unit *pChar, int maxTime)
{
  	StopAssaCodeEffect(pChar,ENCHANT_WEAPON,3);

    int i = GetAssaEffect();
 	cASSAChar *partChar = new cASSAChar;
	partChar->Start(pChar, ENCHANT_WEAPON_FIRE, maxTime*70, 1.0f);
	cAssaEffect[i] = partChar;
	
	POINT3D pos;
	pos.x = pChar->pX;
	pos.y = pChar->pY+2000;
	pos.z = pChar->pZ;
	g_NewParticleMgr.Start("EnchantWeaponJang", pos);

	return TRUE;
}

int AssaParticle_EnchantWeaponLightJang(Unit *pChar, int maxTime)
{
 	StopAssaCodeEffect(pChar, ENCHANT_WEAPON, 3);

    int i = GetAssaEffect();
 	cASSAChar *partChar = new cASSAChar;
	partChar->Start(pChar, ENCHANT_WEAPON_LIGHT, maxTime*70, 1.0f);
	cAssaEffect[i] = partChar;
	
	POINT3D pos;
	pos.x = pChar->pX;
	pos.y = pChar->pY+2000;
	pos.z = pChar->pZ;
	g_NewParticleMgr.Start("EnchantWeaponJang", pos);

	return TRUE;
}

int AssaParticle_EnchantWeaponJinMember(Unit *pChar)
{
	int i = GetAssaEffect();
  	cASSAChar *partChar = new cASSAChar;
	partChar->Start(pChar, ENCHANT_MEMBER_JIN, 140);
	cAssaEffect[i] = partChar;

	return TRUE;
}

int AssaParticle_EnchantWeaponIceMember(Unit *pChar, int maxTime)
{
 	StopAssaCodeEffect(pChar, ENCHANT_WEAPON, 3);

	int i = GetAssaEffect();
  	cASSAChar *partChar = new cASSAChar;
	partChar->Start(pChar, ENCHANT_WEAPON_ICE, maxTime*70);
	cAssaEffect[i] = partChar;
	
	return TRUE;
}

int AssaParticle_EnchantWeaponFireMember(Unit *pChar, int maxTime)
{
 	StopAssaCodeEffect(pChar, ENCHANT_WEAPON, 3);
    
	int i = GetAssaEffect();
 	cASSAChar *partChar = new cASSAChar;
	partChar->Start(pChar, ENCHANT_WEAPON_FIRE, maxTime*70);
	cAssaEffect[i] = partChar;
	
	return TRUE;
}
int AssaParticle_EnchantWeaponLightMember(Unit *pChar, int maxTime)
{
	StopAssaCodeEffect(pChar, ENCHANT_WEAPON, 3);

    int i = GetAssaEffect();
 	cASSAChar *partChar = new cASSAChar;
	partChar->Start(pChar, ENCHANT_WEAPON_LIGHT, maxTime*70);
	cAssaEffect[i] = partChar;
	return TRUE;
}
int AssaParticle_DeadLay(POINT3D *pPosi, POINT3D *pDesti)
{
 	int i = GetAssaEffect();
	cASSAPARTSHOT *partShot = new cASSAPARTSHOT;
	partShot->Start(pPosi, pDesti, 100);
	cAssaEffect[i] = partShot;
	g_NewParticleMgr.Start("DeadLayStart1", *pPosi);
	g_NewParticleMgr.Start("DeadLayHit1", *pDesti);
	
	return TRUE;
}
int ParkAssaParticle_ColdEye(POINT3D *pPosi, POINT3D *pDesti)
{
 	int i = GetAssaEffect();
	cASSAPARTSHOT *partShot = new cASSAPARTSHOT;
	partShot->Start(pPosi, pDesti, ASSA_SHOT_LASER2);
	cAssaEffect[i] = partShot;
	
	g_NewParticleMgr.Start("IceColdEyeStart1", *pPosi);
	g_NewParticleMgr.Start("IceColdEyeHit1", *pDesti);
	
	return TRUE;
}
int ParkAssaParticle_RedEye(POINT3D *pPosi,POINT3D *pDesti)
{
	int i = GetAssaEffect();
	cASSAPARTSHOT *partShot = new cASSAPARTSHOT;
	partShot->Start(pPosi, pDesti, ASSA_SHOT_LASER2);
	cAssaEffect[i] = partShot;

	g_NewParticleMgr.Start("RedEyeHit3", *pPosi);
	g_NewParticleMgr.Start("RedEyeHit1", *pDesti);

	return TRUE;
}
int ParkAssaParticle_Judgement(POINT3D *pPosi,POINT3D *pDesti)
{
	int i = GetAssaEffect();
	cASSAPARTSHOT *partShot = new cASSAPARTSHOT;
	partShot->Start(pPosi, pDesti, ASSA_SHOT_LASER5);
	cAssaEffect[i] = partShot;

	g_NewParticleMgr.Start("JudgementStart",*pPosi);
	g_NewParticleMgr.Start("JudgementHit",*pDesti);
	return TRUE;
}

//ColdEye ½ºÅ³°ø°Ý
int ParkParticle_ColdEyeSkill(Unit *pChar)
{
	POINT3D pos;
	pos.x = pChar->pX;
	pos.y = pChar->pY;
	pos.z = pChar->pZ;

	StartEffectMonster(pos.x, pos.y, pos.z, MONSTER_COLDEYE_SKILL);
	return TRUE;
}
int ParkParticle_RedEyeSkill(Unit *pChar)
{
	POINT3D pos;
	pos.x = pChar->pX;
	pos.y = pChar->pY;
	pos.z = pChar->pZ;

	StartEffectMonster(pos.x, pos.y, pos.z, MONSTER_REDEYE_SKILL);
	return TRUE;
}

// ±ùË®¾§Ð§¹û
int ParkAssaParticle_MisticSpinel(Unit *pChar)
{
	POINT3D pos;
    pos.x = pChar->pX;
	pos.y = pChar->pY + 7500;
	pos.z = pChar->pZ;

 	g_NewParticleMgr.Start("IceMisticSpinelSkill1", pos);
	
	return TRUE;
}
// ¿óÉ½¾§Ê¯
int ParkAssaParticle_SealCrasherl(Unit *pChar)
{
	POINT3D pos;
	pos.x = pChar->pX;
	pos.y = pChar->pY + 7500;
	pos.z = pChar->pZ;

	g_NewParticleMgr.Start("SealCrasherlSkill1", pos);

	return TRUE;
}
// ±ù¼×¶¾ÖëÐ§¹û
int ParkAssaParticle_Tarantulika(Unit *pChar)
{
	POINT3D pos;

	auto sPosition = GetMoveLocation(45 * fONE, 0, 0, 0, (pChar->Angle.y - 1024) & 0x0FFF, 0);
	pos.x = pChar->pX + sPosition.iX;
	pos.y = pChar->pY + 7000;
	pos.z = pChar->pZ + sPosition.iZ;

	int ParticleID = g_NewParticleMgr.Start("TarantulikaHit", pos);

	if (ParticleID != -1)
	{
		pos.x = 0;
		pos.y = pChar->Angle.y;
		pos.z = 0;

		g_NewParticleMgr.SetAngle(ParticleID,pos);
	}

	return TRUE;
}

// ÇÁ·Î½ºÆ® ¿¡ÀÌ¼ÇÆ® µð¾Æ ÀÌÆåÆ®
int ParkAssaParticle_AcientDia(Unit *pChar)
{
	POINT3D charPos;
    charPos.x = pChar->pX;
	charPos.y = pChar->pY+1000;
	charPos.z = pChar->pZ;

	Assa = SetAssaEffect(0,"Monster_Diastrophism.ASE",0,&charPos,0, 0);
	
	cAssaEffect[Assa]->AniMaxCount = 24;
	cAssaEffect[Assa]->AniDelayTime = 3;
	cAssaEffect[Assa]->StartPosi.x = 256*8*6;
	
	cAssaEffect[Assa]->StartPosi.z = -256*8*3;
	cAssaEffect[Assa]->Angle.y = ((pChar->Angle.y&ANGCLIP)+ANGLE_270)&ANGCLIP;

	AssaSetStartPosi(cAssaEffect[Assa]);
	cAssaEffect[Assa]->Angle.y =  -((pChar->Angle.y&ANGCLIP))&ANGCLIP;

	cAssaEffect[Assa]->Posi.y = cAssaEffect[Assa]->Posi.y + 1000;;
	

	SetDynLight( cAssaEffect[Assa]->Posi.x , cAssaEffect[Assa]->Posi.y , cAssaEffect[Assa]->Posi.z,-150, -150, -255, 255, 250, 2);

	g_NewParticleMgr.Start("IceAceintSkill2", cAssaEffect[Assa]->Posi);
	
	return TRUE;
}

int AssaParticle_NoWeaPon_AcientPiercing(cASSAEFFECT *pEffect)
{
	POINT3D TempPosi;
	cAssaEffect[Assa]->Face.MatNum = g_NewParticleMgr.Start("Piercing1", pEffect->Posi); //È£¹Ù¶÷ ÆÄÆ¼Å¬À» ºÙÀÎ´Ù 
	
	//³¯¾Æ°¥°÷ ÁöÁ¡À» ±¸ÇÑ´Ù 
	auto sPosition = GetMoveLocation(0, 0, 256 * 64, pEffect->Angle.x, ((pEffect->pChar->Angle.y&ANGCLIP) + ANGLE_180)&ANGCLIP, 0);
	TempPosi.x = pEffect->Posi.x + sPosition.iX + 1;
	TempPosi.y = pEffect->Posi.y;
	TempPosi.z = pEffect->Posi.z + sPosition.iZ;

	pEffect->MOVECODE = ASSA_MOVE;
	pEffect->MoveSpeed.x = (pEffect->Posi.x - TempPosi.x)/20;
	pEffect->MoveSpeed.z = (pEffect->Posi.z - TempPosi.z)/20;
	pEffect->CODE = 0x50000004; 


	return TRUE;
}

int sinSkillEffect_NoWeaponPiercing(Unit *pChar)
{
	POINT3D TempPosi = {pChar->pX,pChar->pY,pChar->pZ}; 	        	  
	int TempIndex = 0 ,Temp4 = 0;
	
	SetDynLight( pChar->pX , pChar->pY , pChar->pZ ,0, 150, 255, 255, 130 ,1);

	return TRUE;
}

int ParksinSkillEffect_AcientPiercing(Unit *pChar)
{
	POINT3D pTmp={pChar->pX, pChar->pY, pChar->pZ};

	sinSkillEffect_NoWeaponPiercing(pChar);

	Assa = SetAssaEffect(30,"Piercing.ASE",pChar,0,15500);    
	cAssaEffect[Assa]->NotFadeIn = 1;

	cAssaEffect[Assa]->StartPosi.x = 512*8*6;
 	cAssaEffect[Assa]->Angle.y =  ((pChar->Angle.y&ANGCLIP)+ANGLE_270)&ANGCLIP;
	AssaSetStartPosi(cAssaEffect[Assa]);
	cAssaEffect[Assa]->Angle.y =  (-(pChar->Angle.y&ANGCLIP)+ANGLE_180)&ANGCLIP;

	AssaParticle_NoWeaPon_AcientPiercing(cAssaEffect[Assa]); //µÎ°³Âï¾îÁØ´Ù

	return TRUE;
}



// ±ù¼×¸ç²¼ÁÖ
int ParkAssaParticle_IceGolemShot(Unit *pChar)
{
	POINT3D pos;
    pos.x = pChar->pX;
	pos.y = pChar->pY;
	pos.z = pChar->pZ;
	
	auto sPosition = GetMoveLocation(0, 0, -30 * fONE, pChar->Angle.x, pChar->Angle.y, 0);
	pos.x += sPosition.iX;
	pos.z += sPosition.iZ;
    
	Assa = SetAssaEffect(0,"m_IceGolem.ASE",0,&pos,0, 1);
	cAssaEffect[Assa]->AniMaxCount = 30;
	cAssaEffect[Assa]->AniDelayTime = 2;
	cAssaEffect[Assa]->Angle.y = (-pChar->Angle.y+ANGLE_180)&ANGCLIP;
	cAssaEffect[Assa]->NotFadeIn = TRUE;
	
	pos.x = pos.x;
	pos.y = pos.y+1500;
	pos.z = pos.z;
	
	sPosition = GetMoveLocation(0, 0, 120 * fONE, pChar->Angle.x, pChar->Angle.y, 0);
	pos.x += sPosition.iX;
	pos.z += sPosition.iZ;
	
	g_NewParticleMgr.Start("IceGolemHit1", pos);

	return TRUE;
}

// ¾ÆÀÌ½º °íºí¸°
int ParkAssaParticle_IceGoblinHit1(Unit *pChar)
{

	int i = GetAssaEffect();

 	cAssaTraceCharMeshParticle *traceMeshParticle = new cAssaTraceCharMeshParticle;
 	traceMeshParticle->Start(pChar, "Bip-hammer", "IceGoblin", false, 130);
	cAssaEffect[i] = traceMeshParticle;

	POINT3D pos;
 	pos.x = pChar->pX;
	pos.y = pChar->pY;
	pos.z = pChar->pZ;

  
    auto sPosition = GetMoveLocation( 0, 0, 100*fONE, pChar->Angle.x, pChar->Angle.y, 0);

	pos.x += sPosition.iX;
	pos.z += sPosition.iZ;
	pos.y += fONE * 10;

	g_NewParticleMgr.Start("IceGoblinHit1", pos, 1.2f);

	return TRUE;
}

// ÇÁ·ÎÁð ¹Ì½ºÆ®	±âº»°ø°Ý
int ParkAssaParticle_MistIceBolt(Unit* pChar, Unit* pDestChar)
{
	auto sPosition = GetMoveLocation(0, 60 * fONE, 20 * fONE, 0, pChar->Angle.y, 0);
	POINT3D curPos;
	POINT3D desPos;
	curPos.x = pChar->pX + sPosition.iX;
	curPos.y = pChar->pY + sPosition.iY;
	curPos.z = pChar->pZ + sPosition.iZ;
	
	desPos.x = pDestChar->pX;
	desPos.y = pDestChar->pY + 24 * fONE;
	desPos.z = pDestChar->pZ;

	StartEffectMonsterDest(curPos.x, curPos.y, curPos.z, desPos.x, desPos.y, desPos.z, MONSTER_FORZENMIST_SHOT1 );
    
	return TRUE;
}
// ÇÁ·ÎÁð ¹Ì½ºÆ®	½ºÅ³°ø°Ý
int ParkAssaParticle_MistIceBall(Unit* pChar, Unit* pDestChar)
{
	auto sPosition = GetMoveLocation(0, 60 * fONE, 20 * fONE, 0, pChar->Angle.y, 0);
	POINT3D curPos;
	POINT3D desPos;
	curPos.x = pChar->pX + sPosition.iX;
	curPos.y = pChar->pY + sPosition.iY;
	curPos.z = pChar->pZ + sPosition.iZ;
	
	desPos.x = pDestChar->pX;
	desPos.y = pDestChar->pY+24*fONE;
	desPos.z = pDestChar->pZ;


	StartEffectMonsterDest(curPos.x, curPos.y, curPos.z, desPos.x, desPos.y, desPos.z, MONSTER_FORZENMIST_SHOT2 );
	return TRUE;
}
// ¶ñÄ§²®¾ôÐ§¹û
void ParksinSkillEffect_TullaPiercing(Unit* pChar)
{
	SetDynLight(pChar->pX,pChar->pY,pChar->pZ,0,150,255,255,130,1);
	Assa = SetAssaEffect(30,"Piercing.ASE",pChar,0,15500);

	cAssaEffect[Assa]->NotFadeIn	= 1;
	cAssaEffect[Assa]->StartPosi.x	= 96 * fONE;
	cAssaEffect[Assa]->StartPosi.z	= -48 * fONE;

	cAssaEffect[Assa]->Angle.y =  ((pChar->Angle.y&ANGCLIP)+ANGLE_270)&ANGCLIP;
	AssaSetStartPosi(cAssaEffect[Assa]);
	cAssaEffect[Assa]->Angle.y =  (-(pChar->Angle.y&ANGCLIP)+ANGLE_180)&ANGCLIP;

	POINT3D pos;

	cAssaEffect[Assa]->Face.MatNum = g_NewParticleMgr.Start("IceValentoPiercing",cAssaEffect[Assa]->Posi);
	auto sPosition = GetMoveLocation(0, 0, 128 * fONE + 2000, cAssaEffect[Assa]->Angle.x, ((cAssaEffect[Assa]->pChar->Angle.y&ANGCLIP) + ANGLE_180)&ANGCLIP, 0);

	pos.x = cAssaEffect[Assa]->Posi.x + sPosition.iX;
	pos.y = cAssaEffect[Assa]->Posi.y;
	pos.z = cAssaEffect[Assa]->Posi.z + sPosition.iZ;

	cAssaEffect[Assa]->MOVECODE = ASSA_MOVE;
	cAssaEffect[Assa]->MoveSpeed.x = (cAssaEffect[Assa]->Posi.x - pos.x)/20;
	cAssaEffect[Assa]->MoveSpeed.z = (cAssaEffect[Assa]->Posi.z - pos.z)/20;
	cAssaEffect[Assa]->CODE = 0x50000004; 
}

int Assa_Piercing(cASSAEFFECT *pEffect)
{
	POINT3D TempPosi;
	AssaSearchWeaponPos(pEffect->pChar,&pEffect->Posi,1);            
	cAssaEffect[Assa]->Face.MatNum = g_NewParticleMgr.Start("Piercing1", pEffect->Posi); //È£¹Ù¶÷ ÆÄÆ¼Å¬À» ºÙÀÎ´Ù 

	//³¯¾Æ°¥°÷ ÁöÁ¡À» ±¸ÇÑ´Ù 
	auto sPosition = GetMoveLocation(0, 0, 256 * 128, pEffect->Angle.x, ((pEffect->pChar->Angle.y&ANGCLIP) + ANGLE_180)&ANGCLIP, 0);
	TempPosi.x = pEffect->Posi.x + sPosition.iX;
	TempPosi.y = pEffect->Posi.y;
	TempPosi.z = pEffect->Posi.z + sPosition.iZ;

	pEffect->MOVECODE = ASSA_MOVE;
	pEffect->MoveSpeed.x = (pEffect->Posi.x - TempPosi.x)/20;
	pEffect->MoveSpeed.z = (pEffect->Posi.z - TempPosi.z)/20;
	pEffect->CODE = 0x50000004; 


	return TRUE;
}
// ¹ß·»Åä ÇÇ¾î½Ì
int AssaParticle_NoWeaPon_ValentoPiercing(cASSAEFFECT *pEffect)
{
	POINT3D TempPosi;
	cAssaEffect[Assa]->Face.MatNum = g_NewParticleMgr.Start("IceValentoPiercing", pEffect->Posi); //È£¹Ù¶÷ ÆÄÆ¼Å¬À» ºÙÀÎ´Ù 

	
	//³¯¾Æ°¥°÷ ÁöÁ¡À» ±¸ÇÑ´Ù 
	auto sPosition = GetMoveLocation(0, 0, 256 * 128 + 2000, pEffect->Angle.x, ((pEffect->pChar->Angle.y&ANGCLIP) + ANGLE_180)&ANGCLIP, 0);
	TempPosi.x = pEffect->Posi.x + sPosition.iX + 1;
	TempPosi.y = pEffect->Posi.y;
	TempPosi.z = pEffect->Posi.z + sPosition.iZ;

	pEffect->MOVECODE = ASSA_MOVE;
	pEffect->MoveSpeed.x = (pEffect->Posi.x - TempPosi.x)/20;
	pEffect->MoveSpeed.z = (pEffect->Posi.z - TempPosi.z)/20;
	pEffect->CODE = 0x50000004; 


	return TRUE;
}

// ¹ß·»Åä ÇÇ¾î½Ì
void ParksinSkillEffect_ValentoPiercing(Unit* pChar)
{
	POINT3D pTmp={pChar->pX, pChar->pY, pChar->pZ};
	pChar->pY = pTmp.y;

	sinSkillEffect_NoWeaponPiercing(pChar);

	Assa = SetAssaEffect(30,"Piercing.ASE",pChar,0,15500);    
	cAssaEffect[Assa]->NotFadeIn = 1;

	cAssaEffect[Assa]->StartPosi.x = 512*8*6;
	cAssaEffect[Assa]->StartPosi.z = -256*8*6;
 	cAssaEffect[Assa]->Angle.y =  ((pChar->Angle.y&ANGCLIP)+ANGLE_270)&ANGCLIP;
	AssaSetStartPosi(cAssaEffect[Assa]);
	cAssaEffect[Assa]->Angle.y =  (-(pChar->Angle.y&ANGCLIP)+ANGLE_180)&ANGCLIP;

	AssaParticle_NoWeaPon_ValentoPiercing(cAssaEffect[Assa]); //µÎ°³Âï¾îÁØ´Ù

}
int ParkAssaParticle_ValentoBran(Unit* pChar)
{
	POINT3D pos;
 	pos.x = pChar->pX;
	pos.y = pChar->pY;
	pos.z = pChar->pZ;

	auto sPosition = GetMoveLocation(0, 0, 100 * fONE, pChar->Angle.x, pChar->Angle.y, 1);
	pos.x += sPosition.iX;
	pos.z += sPosition.iZ;

  	Assa = SetAssaEffect(0,"m_ratoo.ASE",0,&pos,0);
	cAssaEffect[Assa]->Time = -4;
	cAssaEffect[Assa]->AniMaxCount = 20;
	cAssaEffect[Assa]->AniDelayTime = 5;
	cAssaEffect[Assa]->Angle.y = (-pChar->Angle.y+ANGLE_180)&ANGCLIP;


	POINT3D partPos;
  	partPos.x = cAssaEffect[Assa]->Posi.x;
	partPos.y = cAssaEffect[Assa]->Posi.y + 2000;
	partPos.z = cAssaEffect[Assa]->Posi.z;
	g_NewParticleMgr.Start("IceValentoBrandish",partPos);

	return TRUE;

}

void ParkValentSwordShow(Unit* pValento, int nTime)
{
	if(pValento)
	{
		int i = GetAssaEffect();
		cAssaMotionBlur *motionBlur = new cAssaMotionBlur;
		motionBlur->Start(pValento, "Bip01gho01", "Bip01gho02", nTime);
		motionBlur->Color.R = 200;
		motionBlur->Color.G = 100;
		motionBlur->Color.B = 200;
		motionBlur->Color.A = 100;
		cAssaEffect[i] = motionBlur;
	}
}

// µ¥½º³ªÀÌÆ® ºê·£µð½¬
int ParkAssaParticle_Valento1(Unit* pValento)
{
	if(pValento)
	{
        ParkAssaParticle_ValentoBran(pValento);
	}
	return TRUE;
}
// µ¥½º³ªÀÌÆ® ÇÇ¾î½Ì ( ¹ö¼­Ä¿ )
int ParkAssaParticle_Valento2_1(Unit* pValento)
{
	if(pValento)
	{
		Valento_PowerUp(pValento);

	}

	return TRUE;
}

// µ¥½º³ªÀÌÆ® ÇÇ¾î½Ì (  ÇÇ¾î½Ì )
int ParkAssaParticle_Valento2_2(Unit* pValento)
{
	if(pValento)
	{
		// ÇÇ¾î½Ì
		//ParkValentSwordShow(pChar, 70);
		ParksinSkillEffect_ValentoPiercing(pValento);

	}

	return TRUE;
}


int ParkAssaParticle_Valento3_1(Unit* pValento)
{
	if(pValento)
	{
		//ParkValentSwordShow(pChar, 140);
		//¼Òµå¿ÀºêÀú½ºÆ¼½º
		for(int i = 0; i <2 ; i++){

		Assa = SetAssaEffect(0,"Nt_4-4.ASE",pValento,0,0);
		cAssaEffect[Assa]->AniMaxCount = 16; 
		cAssaEffect[Assa]->AniDelayTime = 2;
		cAssaEffect[Assa]->StartPosi.x = 512*8*6;
	 	cAssaEffect[Assa]->Angle.y =  ((pValento->Angle.y&ANGCLIP)+ANGLE_270)&ANGCLIP;
		AssaSetStartPosi(cAssaEffect[Assa]);
		cAssaEffect[Assa]->Angle.y =  (-(pValento->Angle.y&ANGCLIP)+ANGLE_180)&ANGCLIP;

		Assa = SetAssaEffect(0,"Nt_4-41.ASE",pValento,0,0);
		cAssaEffect[Assa]->AniMaxCount = 18; 
		cAssaEffect[Assa]->AniDelayTime = 3;
		cAssaEffect[Assa]->StartPosi.x = 512*8*6;
	 	cAssaEffect[Assa]->Angle.y =  ((pValento->Angle.y&ANGCLIP)+ANGLE_270)&ANGCLIP;
		AssaSetStartPosi(cAssaEffect[Assa]);
		cAssaEffect[Assa]->Angle.y =  (-(pValento->Angle.y&ANGCLIP)+ANGLE_180)&ANGCLIP;

		Assa = SetAssaEffect(0,"Nt_4-42.ASE",pValento,0,0);
		cAssaEffect[Assa]->AniMaxCount = 20; 
		cAssaEffect[Assa]->AniDelayTime = 4;
		cAssaEffect[Assa]->StartPosi.x = 512*8*6;
	 	cAssaEffect[Assa]->Angle.y =  ((pValento->Angle.y&ANGCLIP)+ANGLE_270)&ANGCLIP;
		AssaSetStartPosi(cAssaEffect[Assa]);
		cAssaEffect[Assa]->Angle.y =  (-(pValento->Angle.y&ANGCLIP)+ANGLE_180)&ANGCLIP;


		}

		Valento_Justice(pValento);

	}
	return TRUE;
}


void ParkAssaParticle_Normal1_1(Unit *pDest)
{
	POINT3D charPos;
    charPos.x = pDest->pX;
	charPos.y = pDest->pY+500;
	charPos.z = pDest->pZ;
	
  	g_NewParticleMgr.Start("ChaosKaraNormal1_1", charPos);
	
	Assa = SetAssaEffect(0,"chao_glacial.ASE",0,&charPos,0, 0);
	cAssaEffect[Assa]->AniMaxCount = 25;
	cAssaEffect[Assa]->AniDelayTime = 2;

	charPos.x = charPos.x;
	charPos.y = charPos.y+1000;
	charPos.z = charPos.z;

	g_NewParticleMgr.Start("ChaosKaraNormal1_2", charPos, 0.3f);
}


int ParkAssaParticle_Skill(Unit *pChar)
{
 	POINT3D posi;
	posi.x = pChar->pX;
	posi.y = pChar->pY+2500;
	posi.z = pChar->pZ;
	
 	g_NewParticleMgr.Start("ChaosKaraSkill", posi);


	return TRUE;

}

int ParkAssaParticle_SkilltoUser(Unit *pDestChar)
{
 	POINT3D posi;
	posi.x = pDestChar->pX;
	posi.y = pDestChar->pY+2500;
	posi.z = pDestChar->pZ;

  	g_NewParticleMgr.Start("ChaosKaraSkillUser",posi, 0.1f);

	return TRUE;

}

void ParkAssaParticle_ChaosKaraTerrainFire(POINT3D *pCur, POINT3D *pDest, int delay=0)
{
	int i = GetAssaEffect();
	ParkAssaChaosKaraMeteo *skyParticle = new ParkAssaChaosKaraMeteo;
	skyParticle->Start(pCur, pDest, delay);
	cAssaEffect[i] = skyParticle;
}

void ChaosKaraMeteo(POINT3D *desPos)
{
	POINT3D curPos;
	POINT3D attackPos;
     attackPos.x = desPos->x;
	attackPos.y = desPos->y;
	attackPos.z = desPos->z+10000;
	curPos.x = attackPos.x;
	curPos.y = attackPos.y+130000;
	curPos.z = attackPos.z+50000;
	ParkAssaParticle_ChaosKaraTerrainFire(&curPos, &attackPos);
	
	attackPos.x = desPos->x;
	attackPos.y = desPos->y;
	attackPos.z = desPos->z-10000;
	curPos.x = attackPos.x;
	curPos.y = attackPos.y+130000;
	curPos.z = attackPos.z+50000;
	ParkAssaParticle_ChaosKaraTerrainFire(&curPos, &attackPos, 30);

	attackPos.x = desPos->x+10000;
	attackPos.y = desPos->y;
	attackPos.z = desPos->z;
	curPos.x = attackPos.x;
	curPos.y = attackPos.y+130000;
	curPos.z = attackPos.z+50000;
	ParkAssaParticle_ChaosKaraTerrainFire(&curPos, &attackPos, 60);

	attackPos.x = desPos->x-10000;
	attackPos.y = desPos->y;
	attackPos.z = desPos->z;
	curPos.x = attackPos.x;
	curPos.y = attackPos.y+130000;
	curPos.z = attackPos.z+50000;
	ParkAssaParticle_ChaosKaraTerrainFire(&curPos, &attackPos, 90);
}

// Ä«¿À½º Ä«¶ó ÀÏ¹Ý°ø°Ý (º£³ð ½ºÇÇ¾î)
int ParkAssaParticle_ChaosKara1(Unit* pChar)
{
	if(pChar)
	{
		ParkAssaParticle_Normal1_1(pChar);
	}
	return TRUE;
}

// Ä«¿À½º Ä«¶ó ¾ÆÀÌ½º ¹ÌÆ¼¾î (¹ÌÆ¼¾î ¾ÆÀÌ½º)
int ParkAssaParticle_ChaosKara2(Unit* pChar)
{
	if(pChar)
	{
		//ParkAssaParticle_MonsterIceChaosKara(pChar);	// ½ºÅÂÇÁ¿¡ ºÙ´Â ÆÄÆ¼Å¬
		ChaosKaraMeteo(&pChar->Posi);  // ÀÌ°ÍÀÌ ÁøÂ¥ ¹ÌÆ¼¾î ¾ÆÀÌ½º
	}
	return TRUE;
}

// Ä«¿À½º Ä«¶ó ¹ìÆÄÀÌ¾î¸¯ (¹ýÁø)
int ParkAssaParticle_ChaosKaraSkill_Monster(Unit* pMonster)
{
	if(pMonster)
	{
		ParkAssaParticle_Skill(pMonster);
	}
	return TRUE;
}

// Ä«¿À½º Ä«¶ó ¹ìÆÄÀÌ¾î¸¯ ( ¼Ò¿ï ¼­Ä¿ )
int ParkAssaParticle_ChaosKaraSkill_User(Unit* pUser)
{
	ParkAssaParticle_SkilltoUser(pUser);

	return TRUE;

}


// ºí¸®ÀÚµå ÀÚÀÌ¾ðÆ®
void ParkBlizzardGiantSkillToTarget(Unit *pTarget)
{
	POINT3D charPos;
	if(pTarget)
	{
		auto sPosition = GetMoveLocation(5 * fONE, 30 * fONE, 0, 0, (pTarget->Angle.y - ANGLE_90)&ANGCLIP, 0);
		charPos.x = pTarget->pX + sPosition.iX;
		charPos.y = pTarget->pY + sPosition.iY;
		charPos.z = pTarget->pZ + sPosition.iZ;

		g_NewParticleMgr.Start("DevilBirdNormal", charPos);
	}
	
}

// µ¥ºí ¹öµå °ø°Ýµ¿ÀÛ 2¹ø Å¸°ÝÀÌÆåÆ®
void ParkDevilBirdAttackNormal(Unit *pTarget)
{
	POINT3D charPos;
	if(pTarget)
	{
		auto sPosition = GetMoveLocation(5 * fONE, 30 * fONE, 0, 0, (pTarget->Angle.y - ANGLE_90)&ANGCLIP, 0);
		charPos.x = pTarget->pX + sPosition.iX;
		charPos.y = pTarget->pY + sPosition.iY;
		charPos.z = pTarget->pZ + sPosition.iZ;

		g_NewParticleMgr.Start("IceHIt1", charPos);
	}	
}

void ParkDevilBirdBlur(Unit* pDevilBird, int nType)
{
	int i = GetAssaEffect();
	if(pDevilBird)
	{
		cAssaMotionBlur *motionBlur = new cAssaMotionBlur;
		
		switch(nType)
		{
		case 0:
			motionBlur->Start(pDevilBird, "Bip01 handbone01", "Bip01 handbone02", 30);
			break;

		case 1:
			motionBlur->Start(pDevilBird, "Bip01 wingbong01", "Bip01 wingbong03", 30);
			break;

		case 2:
			motionBlur->Start(pDevilBird, "Bip01 wingbong02", "Bip01 wingbong04", 30);
			break;
		}

		motionBlur->Color.R = 200;
		motionBlur->Color.G = 100;
		motionBlur->Color.B = 200;
		motionBlur->Color.A = 100;
		cAssaEffect[i] = motionBlur;
	}
}
// µ¥ºí ¹öµå °ø°Ýµ¿ÀÛ 2¹ø ³¯°³Áþ ÀÌÆå (³¯°³¿Í ÁÖ¸Ô¿¡ µé¾î°¥ ¸ð¼Ç ºí·¯)
void ParkDevilBirdAttackBlur(Unit* pDevilBird)
{
	if(pDevilBird)
	{
		ParkDevilBirdBlur(pDevilBird, 0);
		ParkDevilBirdBlur(pDevilBird, 1);
		ParkDevilBirdBlur(pDevilBird, 2);

	}
}
// µ¥ºí ¹öµå ±â¼úµ¿ÀÛ Å¸°Ý ÀÌÆåÆ®
void ParkDevilBirdSkillToTarget(Unit *pTarget)
{
	POINT3D charPos;
	if(pTarget)
	{
		auto sPosition = GetMoveLocation(5 * fONE, 40 * fONE, 0, 0, (pTarget->Angle.y - ANGLE_90)&ANGCLIP, 0);

		charPos.x = pTarget->pX + sPosition.iX;
		charPos.y = pTarget->pY + sPosition.iY;
		charPos.z = pTarget->pZ + sPosition.iZ;

  		g_NewParticleMgr.Start("DevilBirdSkillHit", charPos);
		

		charPos.x = charPos.x;
		charPos.y = charPos.y - 6000;
		charPos.z = charPos.z;

		g_NewParticleMgr.Start("DevilBirdSkillHit", charPos, 0.15f);

		charPos.x = charPos.x;
		charPos.y = charPos.y + 4500;
		charPos.z = charPos.z;

		g_NewParticleMgr.Start("DevilBirdSkillHit", charPos, 0.3f);
	}
}



// ½ºÆÄÀÌ´õ Æ®·çÆÛ µ¶°¡½º »Õ¾î³»±â
void ParkAssaParticle_SpiderTrooperHit1(Unit *pChar)
{
	auto sPosition = GetMoveLocation(45 * fONE, 0, 0, 0, (pChar->Angle.y - ANGLE_90)&ANGCLIP, 0);
	
	
	int num = -1;
 	POINT3D pos;
	pos.x = pChar->pX + sPosition.iX;
	pos.y = pChar->pY + 14000;
	pos.z = pChar->pZ + sPosition.iZ;
	

	D3DVECTOR  velocity;
	D3DVECTOR  gravity;
   	int i = GetAssaEffect(); 
	velocity.x = float((float)sPosition.iX / 15.f);
	velocity.y = 0.f;
	velocity.z = float((float)sPosition.iZ / 15.f);

  	gravity.x = 0.f;
 	gravity.y = 0.f;
	gravity.z = 0.f;	
	
	num = g_NewParticleMgr.Start("ParkSpiderTrooper", pos);
	if(num != -1)
	{
		POINT3D angle;
		angle.x = 0;
		angle.y = pChar->Angle.y;
		angle.z = 0;
		g_NewParticleMgr.SetAngle(num, angle);
	}
	
}


int ParkAssaParticle_DivineLighting(Unit *pChar)
{
	int i = GetAssaEffect();
	cASSAPARTSHOT *partShot = new cASSAPARTSHOT;
	
	POINT3D curPos;
	POINT3D desPos;
	curPos.x = pChar->pX;
	curPos.y = pChar->pY + 100000;
	curPos.z = pChar->pZ;

	desPos.x = pChar->pX;
	desPos.y = pChar->pY + 5000;
	desPos.z = pChar->pZ;
	partShot->Start(&curPos, &desPos, ASSA_SHOT_PARKSPARK);
	cAssaEffect[i] = partShot;
	
	return TRUE;
}

int ParkAssaParticle_Sprak1(POINT3D *pPosi)
{
	for(int index = 0; index < 5; index++)
	{
		int i = GetAssaEffect();
		cASSAPARTSPARK *partSpark = new cASSAPARTSPARK;
		
		partSpark->Start(pPosi, "spark04_01.bmp");
		partSpark->Time = GetRandomPos(0,20);
		cAssaEffect[i] = partSpark;
	}
	
	SetDynLight( pPosi->x, pPosi->y, pPosi->z, 255, 255, 255, 255, 100, 2);
	g_NewParticleMgr.Start("DivineLightning", *pPosi);
	return TRUE;
}


//µð¹ÙÀÎ ¶óÀÌÆ®´× ½ºÅ³ ¿¬Ãâ ( ÀÌÆåÆ® ½ÇÇö ) ÃÖ´ë 10°³
int ParkDivineLight_Effect(Unit *lpChar )
{
	int cnt,TargetCount;
	int x,y,z,dist;
	int	LightningCount;
	int cCount;
	Unit *lpTarChar;

	TargetCount = 0;

	if ( lpChar==lpCurPlayer ) {
		for( cnt=0;cnt<DivineLightning_Target_Count;cnt++ ) {
			lpTarChar = FindAutoPlayer( dwSkill_DivineLightning_Target[cnt] );
			if ( lpTarChar ) {
				ParkAssaParticle_DivineLighting( lpTarChar );
				TargetCount++;
			}
		}
	}
	else {
		LightningCount = 10;

		for( cnt=0;cnt< MAX_UNITS;cnt++ )
		{
			cCount = (DivineLightning_FindCount+cnt)&OTHER_PLAYER_MASK;
			if (chrOtherPlayer[cCount].bActive && chrOtherPlayer[cCount].iID && lpChar!=&chrOtherPlayer[cCount] && chrOtherPlayer[cCount].sCharacterData.iType == CHARACTERTYPE_Monster && chrOtherPlayer[cCount].sCharacterData.iMonsterType != MONSTERTYPE_Friendly && chrOtherPlayer[cCount].sCharacterData.sHP.sMin >0 )
			{
				x = (lpChar->pX - chrOtherPlayer[cCount].pX)>>FLOATNS;
				y = (lpChar->pY - chrOtherPlayer[cCount].pY)>>FLOATNS;
				z = (lpChar->pZ - chrOtherPlayer[cCount].pZ)>>FLOATNS;

				dist = x*x+y*y+z*z;

				if (dist<(160*160))
				{
					ParkAssaParticle_DivineLighting(&chrOtherPlayer[cCount]);
					TargetCount++;
					if (TargetCount>=LightningCount)
					{
						DivineLightning_FindCount = cCount;
						break;
					}
				}
			}
		}

		if (TargetCount<LightningCount && lpChar->sCharacterData.iType == CHARACTERTYPE_Monster)
		{
			x = (lpChar->pX - lpCurPlayer->pX )>>FLOATNS;
			y = (lpChar->pY - lpCurPlayer->pY )>>FLOATNS;
			z = (lpChar->pZ - lpCurPlayer->pZ )>>FLOATNS;

			dist = x*x+y*y+z*z;

			if (dist<(160*160))
			{
				ParkAssaParticle_DivineLighting( lpCurPlayer );
				TargetCount++;
			}
		}
	}

	return TargetCount;
}
void ParkAssaParticle_StingRay(Unit *pChar)
{
	auto sPosition = GetMoveLocation(45 * fONE, 0, 0, 0, (pChar->Angle.y - ANGLE_90)&ANGCLIP, 0);

	int num = -1;
 	POINT3D pos;
	pos.x = pChar->pX + sPosition.iX;
	pos.y = pChar->pY + 8000;
	pos.z = pChar->pZ + sPosition.iZ;
	
	D3DVECTOR  velocity;
	D3DVECTOR  gravity;
   	int i = GetAssaEffect(); 
	velocity.x = float((float)sPosition.iX / 15.f);
	velocity.y = 0.f;
	velocity.z = float((float)sPosition.iZ / 15.f);

  	gravity.x = 0.f;
 	gravity.y = 0.f;
	gravity.z = 0.f;

	
	num = g_NewParticleMgr.Start("ParkStingRay", pos);
	if(num != -1)
	{
		POINT3D angle;
		angle.x = 0;
		angle.y = pChar->Angle.y;
		angle.z = 0;
		g_NewParticleMgr.SetAngle(num, angle);
	}
}
// ¶¾Ð§¹û
int ParkAssaParticle_Posion(Unit *pChar, int liveCount)
{
	if(!AddAssaCodeEffectTime(pChar, MONSTER_POSION_STATE1, liveCount*70))
 	{
		int i = GetAssaEffect();
		cASSAChar *partChar = new cASSAChar;
		partChar->Start(pChar, MONSTER_POSION_STATE1, liveCount*70);
		cAssaEffect[i] = partChar;
	}

	return TRUE;
}
void ParkAssaParticle_MummyShot(Unit *pChar, Unit *pDestChar)
{
	auto sPosition = GetMoveLocation(0, 30 * fONE, 20 * fONE, 0, pChar->Angle.y, 0);
	POINT3D curPos;
	POINT3D desPos;
	curPos.x = pChar->pX + sPosition.iX;
	curPos.y = pChar->pY + sPosition.iY;
	curPos.z = pChar->pZ + sPosition.iZ;
	
	desPos.x = pDestChar->pX;
	desPos.y = pDestChar->pY+24*fONE;
	desPos.z = pDestChar->pZ;
	
	StartEffectMonsterDest(curPos.x, curPos.y, curPos.z, desPos.x, desPos.y, desPos.z, MONSTER_MUMMY_SHOT );

}



// ÔÉÊ¯Ð§¹û
void ParkAssaParticle_TerrainFire(POINT3D *pCur, POINT3D *pDest, int delay, int nType)
{
	int i = GetAssaEffect();
	AssaSkyMeteoParticle *skyParticle = new AssaSkyMeteoParticle;
	skyParticle->Start(pCur, pDest, delay, nType);
	cAssaEffect[i] = skyParticle;
}
void ParkAssaParticle_TerrainFireHit(POINT3D *pCur, int nType)
{
    D3DVECTOR vector;
    vector.x = float(pCur->x - lpCurPlayer->pX)/fONE;
	vector.y = float(pCur->y - lpCurPlayer->pY)/fONE;
	vector.z = float(pCur->z - lpCurPlayer->pZ)/fONE;
	
	float length;
 	length = (float)sqrt(vector.x*vector.x+vector.y*vector.y+vector.z*vector.z);
	if(length == 0)
		length = 1;

    SetDynLight( pCur->x, pCur->y, pCur->z, 255, 200, 100, 255, 250, 2);

	switch(nType)
	{
	case 0:
		g_NewParticleMgr.Start("FireBigHit1", *pCur);
		break;
	case 1:
		g_NewParticleMgr.Start("IronMonsterBombHit1", *pCur);
		break;
	case 2:
		g_NewParticleMgr.Start("IceWormHIt1", *pCur);
		break;
	case 3:
		g_NewParticleMgr.Start("IceWormHIt2", *pCur);
		break;
	case 4:
		g_NewParticleMgr.Start("Skill5_Priestess_Meteo1", *pCur);
		break;
	}

    EffectWaveCamera(int((500.f - length)/15.f), 2);
}

// Dark Phalanx ±â¼ú µ¿ÀÛ ÀÌÆåÆ® (Ã¢À¸·Î Âî¸¦¶§ Ã¢ÀÌ ÆÄ°íµå´Â ´À³¦ÀÇ ÀÌÆåÆ® - ÇÇ¾î½ÌÀ¸·Î Ã³¸®)
void ParkAssaParticle_DarkPhalanx(Unit *pDarkPhalanx)
{
	if(pDarkPhalanx)
	{
		sinSkillEffect_NoWeaponPiercing(pDarkPhalanx);

		Assa = SetAssaEffect(30,"Piercing.ASE",pDarkPhalanx,0,15500);    
		cAssaEffect[Assa]->NotFadeIn = 1;

		//cAssaEffect[Assa]->StartPosi.x = -512*8*6;
		cAssaEffect[Assa]->StartPosi.z = -64*8*6;
		cAssaEffect[Assa]->StartPosi.y = -128*8*6;
 		cAssaEffect[Assa]->Angle.y =  ((pDarkPhalanx->Angle.y&ANGCLIP)+ANGLE_270)&ANGCLIP;
		AssaSetStartPosi(cAssaEffect[Assa]);
		cAssaEffect[Assa]->Angle.y =  (-(pDarkPhalanx->Angle.y&ANGCLIP)+ANGLE_180)&ANGCLIP;

		AssaParticle_NoWeaPon_ValentoPiercing(cAssaEffect[Assa]); //µÎ°³Âï¾îÁØ´Ù

	}
}

void ParkAssaParticle_FireWorm(Unit* pTarget, BOOL bSkill)	// ÆÄÀÌ¾î ¿ú °ø°Ý
{
	POINT3D curPos;
	POINT3D attackPos;

	attackPos.x = pTarget->pX;
 	attackPos.y = pTarget->pY;
	attackPos.z = pTarget->pZ+1000;

	curPos.x = attackPos.x;
	curPos.y = attackPos.y+130000;
	curPos.z = attackPos.z+50000;
	if ( !bSkill )
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 0, 1);
	else
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 0, 0);
}
void ParkAssaParticle_IceWorm(Unit* pTarget, BOOL bSkill)	// ±ùÔÉÊ¯¹¥»÷
{
	POINT3D curPos;
	POINT3D attackPos;

	attackPos.x = pTarget->pX;
	attackPos.y = pTarget->pY;
	attackPos.z = pTarget->pZ+1000;

	curPos.x = attackPos.x;
	curPos.y = attackPos.y+130000;
	curPos.z = attackPos.z+50000;
	if (!bSkill)
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 0, 2);
	else
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 0, 3);
}

// Å°¸Þ¶ó ÀÏ¹Ý°ø°Ý ( ¹ßÅé ºí·¯ )
void ParkAssaParticle_ChimeraNormal(Unit *pChimera)
{
	int nTime = 70;
	if(pChimera)
	{
		int i = GetAssaEffect();
		cAssaMotionBlur *motionBlur = new cAssaMotionBlur;
		motionBlur->Start(pChimera, "Bip01 asw", "Bip01 asw01", nTime);
		motionBlur->Color.R = 200;
		motionBlur->Color.G = 100;
		motionBlur->Color.B = 200;
		motionBlur->Color.A = 100;
		cAssaEffect[i] = motionBlur;
	}
}

// Å°¸Þ¶ó ½ºÅ³°ø°Ý (Çìµù - ¸Ó¸®¿¡ ÀÍ½ºÆ®¸²½Çµå)
void ParkAssaParticle_ChimeraSkill(Unit *pChar)
{
	auto sPosition = GetMoveLocation(0, 0, 0, 0, pChar->Angle.y, 0);
	
 	POINT3D pos;
	pos.x = pChar->pX + sPosition.iX;
	pos.y = pChar->pY + 7000;
	pos.z = pChar->pZ + sPosition.iZ;
	
	//GetMoveLocation( 0, 0, 30*fONE, 0, pHellHound->Angle.y, 0);

	
	StartSkill( pos.x, pos.y, pos.z, 0,0,0, EFFECT_CHIMERA_SKILL );
}

// Bloody Knight ½ºÅ³ °ø°Ý (·Î¾î)
void ParkAssaParticle_BloodySkill(Unit *pBloodKnight)
{
	StartSkill( pBloodKnight->pX, pBloodKnight->pY, pBloodKnight->pZ, 0,0,0, EFFECT_BLOODKNIGHT_SKILL, 10 );
}

// Bloody Knight ½ºÅ³ °ø°Ý ÇÇ°Ý (½ºÅÏ)
void ParkAssaParticle_BloodySkillStun(Unit *pChar)
{
	sinSetEffect_Stun(pChar , 90 );
}

// Çï ÇÏ¿îµå ³ë¸»°ø°Ý (µÎ¹ßÀ» µé¾î ´ë»óÀ» ³»·ÁÂïÀ½)
void ParkAssaParticle_HellHoundNormal(Unit *pChar)
{
	POINT3D pos;

	auto sPosition = GetMoveLocation(0, 0, 0, 0, pChar->Angle.y, 0);

	pos.x = pChar->pX + sPosition.iX;
	pos.y = pChar->pY + 1000;
	pos.z = pChar->pZ + sPosition.iZ;
	
 	g_NewParticleMgr.Start("LostMonsterHellHoundAttack", pos);
}
// Çï ÇÏ¿îµå ½ºÅ³°ø°Ý (ÀÔ¿¡¼­ ºÒ³ª°¨)
void ParkAssaParticle_HellHoundSkillAttack(Unit *pHellHound)
{
	auto sPosition = GetMoveLocation(0, 0, 50 * fONE, 0, pHellHound->Angle.y, 0);
	
	int num = -1;
 	POINT3D pos;
	pos.x = pHellHound->pX + sPosition.iX;
	pos.y = pHellHound->pY + 10000;
	pos.z = pHellHound->pZ + sPosition.iZ;
	
	GetMoveLocation( 0, 0, 30*fONE, 0, pHellHound->Angle.y, 0);

	//Å×½ºÆ®¿ë.
	D3DVECTOR  velocity;
	D3DVECTOR  gravity;
   	int i = GetAssaEffect(); 
	velocity.x = float((float)sPosition.iX / 15.f);
	velocity.y = 0.f;
	velocity.z = float((float)sPosition.iZ / 15.f);

  	gravity.x = 0.f;
 	gravity.y = 0.f;
	gravity.z = 0.f;
	
	AssaSkill3BombShotExplision *explision = new AssaSkill3BombShotExplision;
	explision->Start(&pos, &velocity, &gravity, "IronMonsterBombHit2");
	cAssaEffect[i] = explision;
	
	
	num = g_NewParticleMgr.Start("MonsterIron1", pos);
	if(num != -1)
	{
		POINT3D angle;
		angle.x = 0;
		angle.y = pHellHound->Angle.y;
		angle.z = 0;
		g_NewParticleMgr.SetAngle(num, angle);
	}
}

// Çï ÇÏ¿îµå ½ºÅ³°ø°ÝÀÇ ÇÇ°Ý½Ã (È­¿°¿¡ ÈÛ½ÎÀÎµíÇÑ ÀÌÆåÆ®)
void ParkAssaParticle_HellHoundSkillTaget(Unit *pChar)
{
	POINT3D pos;

	auto sPosition = GetMoveLocation(0, 0, 0, 0, pChar->Angle.y, 0);

	pos.x = pChar->pX + sPosition.iX;
	pos.y = pChar->pY + 3000;
	pos.z = pChar->pZ + sPosition.iZ;
	
 	g_NewParticleMgr.Start("LostMonsterDarkMageHit1", pos);
}

// ´ÙÅ© °¡µå ±âº»°ø°Ý ÇÇ°Ý½Ã
void ParkAssaParticle_DarkGuardTaget(Unit *pChar)
{

}

// ´ÙÅ© °¡µå ½ºÅ³°ø°Ý
void ParkAssaParticle_DarkGuardSkill(Unit *pDarkGuard, Unit *pChar)
{
	Point3D sPosition;

	sPosition = GetMoveLocation(0, 30 * fONE, 0, 0, pDarkGuard->Angle.y, 0);
	POINT3D pCur, pDest;
	pCur.x = pDarkGuard->pX + sPosition.iX;
	pCur.y = pDarkGuard->pY + sPosition.iY;
	pCur.z = pDarkGuard->pZ + sPosition.iZ;

	sPosition = GetMoveLocation(0, 30 * fONE, 0, 0, pChar->Angle.y, 0);
	pDest.x = pChar->pX + sPosition.iX;
	pDest.y = pChar->pY + sPosition.iY;
	pDest.z = pChar->pZ + sPosition.iZ;

	Assa = SetAssaEffect(0,"arrow.ASE",0, &pCur,0);
	
	cAssaEffect[Assa]->Time = 0;
	cAssaEffect[Assa]->AniMaxCount = 60;
	cAssaEffect[Assa]->AniDelayTime = 4;
 	cAssaEffect[Assa]->MOVECODE = ASSA_ANGLE_ROTATE;
	cAssaEffect[Assa]->Angle.y = ANGLE_1;
	cAssaEffect[Assa]->ScalePosi.x = 5;
	cAssaEffect[Assa]->ScalePosi.y = 5;
	cAssaEffect[Assa]->ScalePosi.z = 5;

	sPosition = GetRadian3D(pCur.x, pCur.y, pCur.z, pDest.x, pDest.y, pDest.z);

	cAssaEffect[Assa]->Angle.x = sPosition.iX;
	cAssaEffect[Assa]->Angle.y = sPosition.iY;
	cAssaEffect[Assa]->Angle.z = sPosition.iZ;
	
	cAssaEffect[Assa]->Angle.y = (-sPosition.iY + ANGLE_1)&ANGCLIP;
	cAssaEffect[Assa]->NotFadeIn = TRUE;
	cAssaEffect[Assa]->ARotateSpeed.z = 100;
	int i = GetAssaEffect();
	cASSAPARTSHOT *partShot = new cASSAPARTSHOT;
	partShot->Start(&pCur, &pDest, cAssaEffect[Assa], SKILL_TWIST_JAVELIN);
	cAssaEffect[i] = partShot;
}

// ´ÙÅ© ¸ÞÀÌÁö ±âº»°ø°Ý
void ParkAssaParticle_DarkMageNormal(Unit *pDarkMage, Unit *pChar)
{
	auto sPosition = GetMoveLocation(0, 30 * fONE, 20 * fONE, 0, pDarkMage->Angle.y, 0);
	POINT3D curPos;
	POINT3D desPos;
	curPos.x = pDarkMage->pX + sPosition.iX;
	curPos.y = pDarkMage->pY + sPosition.iY;
	curPos.z = pDarkMage->pZ + sPosition.iZ;
	
	desPos.x = pChar->pX;
	desPos.y = pChar->pY + 24 * fONE;
	desPos.z = pChar->pZ;

	StartEffectMonsterDest(curPos.x, curPos.y, curPos.z, desPos.x, desPos.y, desPos.z, MONSTER_PIGON_SHOT1 );
}

// ´ÙÅ© ¸ÞÀÌÁö ½ºÅ³°ø°Ý
void ParkAssaParticle_DarkMageSkill(Unit *pChar)
{
	ParkAssaParticle_FireWorm(pChar, 1);
}

// ´ÙÅ© ¸ÞÀÌÁö Á×À»¶§
void ParkAssaParticle_DarkMageDead(Unit *pDarkMage)
{
	auto sPosition = GetMoveLocation(0, 0, 0, 0, pDarkMage->Angle.y, 0);
	POINT3D pos;

	pos.x = pDarkMage->pX + sPosition.iX;
	pos.y = pDarkMage->pY + 3000;
	pos.z = pDarkMage->pZ + sPosition.iZ;
	
 	g_NewParticleMgr.Start("LostMonsterDarkMageDead", pos);
}


int AssaParticle_LightShot(POINT3D *pPosi, POINT3D *pDesti)
{
    g_NewParticleMgr.Start("LightStart1", *pPosi);	
	g_NewParticleMgr.Start("LightHit1", *pDesti);
	
	SetDynLight( pDesti->x, pDesti->y, pDesti->z, 255, 255, 255, 255, 150, 2);

    Assa = SetAssaEffect(100,"spark01_01.bmp",0,pPosi,0);
	AssaGetAniFileMat(cAssaEffect[Assa]);
	cAssaEffect[Assa]->AniDelayTime = 3;
	cAssaEffect[Assa]->Face.r = 255;
	cAssaEffect[Assa]->Face.g = 255;
	cAssaEffect[Assa]->Face.b = 255;
	cAssaEffect[Assa]->Face.Transparency = 255;
	cAssaEffect[Assa]->Size.w = 5000;
	cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE; 
	
	cAssaEffect[Assa]->ScalePosi.x = pDesti->x - pPosi->x;
	cAssaEffect[Assa]->ScalePosi.y = pDesti->y - pPosi->y;
	cAssaEffect[Assa]->ScalePosi.z = pDesti->z - pPosi->z;

	Assa = SetAssaEffect(100,"spark01_01.bmp",0,pPosi,0);
	AssaGetAniFileMat(cAssaEffect[Assa]);
	cAssaEffect[Assa]->AniDelayTime = 3;
	cAssaEffect[Assa]->Face.r = 255;
	cAssaEffect[Assa]->Face.g = 255;
	cAssaEffect[Assa]->Face.b = 255;
	cAssaEffect[Assa]->Face.Transparency = 255;
	cAssaEffect[Assa]->Size.w = 5000;
	cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE; 
	
	cAssaEffect[Assa]->ScalePosi.x = pDesti->x - pPosi->x;
	cAssaEffect[Assa]->ScalePosi.y = pDesti->y - pPosi->y;
	cAssaEffect[Assa]->ScalePosi.z = pDesti->z - pPosi->z;
	return true;
}

int AssaParticle_FireShot(POINT3D *pPosi, POINT3D *pDesti)
{
 	int i = GetAssaEffect();
	cASSAPARTSHOT *partShot = new cASSAPARTSHOT;
	partShot->Start(pPosi, pDesti, ASSA_SHOT_FIRE);
	cAssaEffect[i] = partShot;

	return TRUE;
}

int AssaParticle_IceShot(POINT3D *pPosi, POINT3D *pDesti)
{
	int i = GetAssaEffect();
	cASSAPARTSHOT *partShot = new cASSAPARTSHOT;
	partShot->Start(pPosi, pDesti, ASSA_SHOT_ICE);
	cAssaEffect[i] = partShot;

	return TRUE;
}

int AssaParticle_LightHit1(POINT3D *pPosi)
{
	SetDynLight( pPosi->x, pPosi->y, pPosi->z, 255, 255, 255, 255, 150, 2);
	g_NewParticleMgr.Start("LightHit1", *pPosi);
	return TRUE;
}

int AssaParticle_IceHit1(POINT3D *pPosi)
{
 	SetDynLight( pPosi->x, pPosi->y, pPosi->z, 150, 150, 255, 255, 120, 2);
	Assa = SetAssaEffect(0,"EW-ice.ASE",0,pPosi,0);                 
	cAssaEffect[Assa]->AniMaxCount = 20;
	cAssaEffect[Assa]->AniDelayTime = 1;
	
	g_NewParticleMgr.Start("IceHit1", *pPosi);
	return TRUE;
}

int AssaParticle_FireHit1(POINT3D *pPosi)
{
  	SetDynLight( pPosi->x, pPosi->y, pPosi->z, 255, 200, 100, 255, 120, 2);
	g_NewParticleMgr.Start("FireHit1", *pPosi);
	return TRUE;
}

int AssaParticle_FireHit2(POINT3D *pPosi)
{
	POINT3D pos;
	pos.x = pPosi->x;
	pos.y = pPosi->y;
	pos.z = pPosi->z;

	g_NewParticleMgr.Start("FireHIt2", pos);
	return TRUE;
}

int AssaParticle_BigFireHit1(POINT3D *pPosi)
{
   	SetDynLight( pPosi->x, pPosi->y, pPosi->z, 255, 200, 100, 255, 200, 2);
	g_NewParticleMgr.Start("FireBigHit1", *pPosi);
	return TRUE;
}



int AssaParticle_HolyMind_Attack(Unit *pChar, int liveCount)
{
     StartEffectMonster(pChar->pX, pChar->pY, pChar->pZ, MONSTER_SERQBUS_MAGIC3);
	 if(!AddAssaCodeEffectTime(pChar, HOLY_MIND_ATTACK, liveCount*70))
	 {
		//StopAssaCodeEffect(pChar, HOLY_MIND_ATTACK);
		//½ÇÁ¦·Î À¯ÁöµÇ´Â ÆÄÆ¼Å¬ È£Ãâ..
		int i = GetAssaEffect();
		cASSAChar *partChar = new cASSAChar;
		partChar->Start(pChar, HOLY_MIND_ATTACK, liveCount*70);
		cAssaEffect[i] = partChar;
	 }
	 return TRUE;
}

/*
int AssaParticle_AgingBody(Unit *pChar)
{
	int i = GetAssaEffect();
	cASSAItem *partItem = new cASSAItem;
	partItem->Start(pChar, AGING_BODY);
	cAssaEffect[i] = partItem;
	
	return TRUE;
}
*/

int AssaParticle_Fury_Eye(Unit *pChar)
{
	if(GetAssaCodeEffect(pChar, FURY_EYE1) == FALSE)
	{
  		int i = GetAssaEffect();
		cAssaTraceCharMeshParticle *traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pChar, "Bip EyeT01", "FuryEye");
		traceMeshParticle->SetScale(float(pChar->sCharacterData.sSize)/256.f);
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = FURY_EYE1;
		

 		i = GetAssaEffect();
		traceMeshParticle = NULL;
		traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pChar, "Bip EyeT02", "FuryEye");
		traceMeshParticle->SetScale(float(pChar->sCharacterData.sSize)/256.f);
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = FURY_EYE1;
	}

	return TRUE;
}

int AssaParticle_Fury_ShotFire(Unit *pChar, POINT3D *destPos)
{
 	smOBJ3D *searchObj = pChar->AnimPattern->GetObjectFromName("Bip MouthT"); //¿ÀºêÁ§Æ®¸¦ ÀÐ´Â´Ù
	POINT3D curPos;
	if(AssaSearchObjPos(pChar, searchObj, &curPos))
	{
		int i = GetAssaEffect();
		cASSAPARTSHOT *partShot = new cASSAPARTSHOT;
		partShot->Start(&curPos, destPos, ASSA_SHOT_BIGFIRE1);
		cAssaEffect[i] = partShot;
	}
	//AssaParticle_FireShot(&curPos, destPos);

	return TRUE;
}

int AssaParticle_Fury_RespawnBody(Unit *pChar)
{
  	int i = GetAssaEffect();
	cAssaTraceCharMeshParticle *traceMeshParticle = new cAssaTraceCharMeshParticle;
 	traceMeshParticle->Start(pChar, "Bip MouthT", "FuryRespawnMouse");
	cAssaEffect[i] = traceMeshParticle;
	
	POINT3D pos;
	pos.x = pChar->pX;
	pos.y = pChar->pY+2000;
	pos.z = pChar->pZ;

	g_NewParticleMgr.Start("FuryRespawnDown", pos);
	return TRUE;
}

int AssaParticle_Fury_RespawnMonster(POINT3D *pPosi)
{
	g_NewParticleMgr.Start("FuryRespawn", *pPosi);
	Assa = SetAssaEffect(0,"m_fury.ASE",0,pPosi,0);
	cAssaEffect[Assa]->Time = 0;
	cAssaEffect[Assa]->AniMaxCount = 20;
	cAssaEffect[Assa]->AniDelayTime = 5;
	
	
	return TRUE;
}


int AssaParticle_Fury_Skill1(POINT3D *pPosi, POINT3D *pAngle)
{
	POINT3D posi;
	POINT3D floorPosi;
    posi.x = pPosi->x;
	posi.y = pPosi->y;
	posi.z = pPosi->z;
	
 	floorPosi.x = pPosi->x;
	floorPosi.y = pPosi->y+2500;
	floorPosi.z = pPosi->z;
	
 	g_NewParticleMgr.Start("FuryHit1", posi);
	g_NewParticleMgr.Start("FuryHit2", floorPosi);

    Assa = SetAssaEffect(0,"m_furyhead.ASE",0,&posi,0);
	cAssaEffect[Assa]->Time = -2;
	cAssaEffect[Assa]->AniMaxCount = 30;
	cAssaEffect[Assa]->AniDelayTime = 3;
	cAssaEffect[Assa]->Angle.y = (-pAngle->y+ANGLE_180)&ANGCLIP;

	Assa = SetAssaEffect(0,"m_furyhead.ASE",0,&posi,0);
	cAssaEffect[Assa]->Time = -8;
	cAssaEffect[Assa]->AniMaxCount = 30;
	cAssaEffect[Assa]->AniDelayTime = 4;
	cAssaEffect[Assa]->Angle.y = (-pAngle->y+ANGLE_180)&ANGCLIP;
	
	Assa = SetAssaEffect(0,"m_fury-jin.ASE",0,&posi,0);
	cAssaEffect[Assa]->Time = -2;
	cAssaEffect[Assa]->AniMaxCount = 30;
	cAssaEffect[Assa]->AniDelayTime = 4;
	cAssaEffect[Assa]->Angle.y = (-pAngle->y+ANGLE_180)&ANGCLIP;

	return TRUE;
}

int AssaParticle_Fury_Skill1(Unit *pChar)
{
	POINT3D posi;
	POINT3D floorPosi;
    posi.x = pChar->pX;
	posi.y = pChar->pY;
	posi.z = pChar->pZ;
	
 	floorPosi.x = pChar->pX;
	floorPosi.y = pChar->pY+2500;
	floorPosi.z = pChar->pZ;
	
 	g_NewParticleMgr.Start("FuryHit1", posi);
	g_NewParticleMgr.Start("FuryHit2", floorPosi);

    Assa = SetAssaEffect(0,"m_furyhead.ASE",0,&posi,0);
	cAssaEffect[Assa]->Time = -2;
	cAssaEffect[Assa]->AniMaxCount = 30;
	cAssaEffect[Assa]->AniDelayTime = 3;
	cAssaEffect[Assa]->Angle.y = (-pChar->Angle.y+ANGLE_180)&ANGCLIP;

	Assa = SetAssaEffect(0,"m_furyhead.ASE",0,&posi,0);
	cAssaEffect[Assa]->Time = -8;
	cAssaEffect[Assa]->AniMaxCount = 30;
	cAssaEffect[Assa]->AniDelayTime = 4;
	cAssaEffect[Assa]->Angle.y = (-pChar->Angle.y+ANGLE_180)&ANGCLIP;
	
	Assa = SetAssaEffect(0,"m_fury-jin.ASE",0,&posi,0);
	cAssaEffect[Assa]->Time = -2;
	cAssaEffect[Assa]->AniMaxCount = 30;
	cAssaEffect[Assa]->AniDelayTime = 4;
	cAssaEffect[Assa]->Angle.y = (-pChar->Angle.y+ANGLE_180)&ANGCLIP;

	return TRUE;
}

void AssaParticle_CastleRed(Unit *pChar)
{
	POINT3D posi;
	POINT3D floorPosi;
    posi.x = pChar->pX;
	posi.y = pChar->pY;
	posi.z = pChar->pZ;
	
 	floorPosi.x = pChar->pX;
	floorPosi.y = pChar->pY+2500;
	floorPosi.z = pChar->pZ;
	
 	g_NewParticleMgr.Start("FuryHit1", posi);
	g_NewParticleMgr.Start("FuryHit2", floorPosi);

	Assa = SetAssaEffect(0,"m_fury-jin.ASE",0,&posi,0);
	cAssaEffect[Assa]->Time = -2;
	cAssaEffect[Assa]->AniMaxCount = 30;
	cAssaEffect[Assa]->AniDelayTime = 4;
	cAssaEffect[Assa]->Angle.y = (-pChar->Angle.y+ANGLE_180)&ANGCLIP;
}

void AssaParticle_CastleGreen(Unit *pChar)
{
	POINT3D posi;
	POINT3D floorPosi;
    posi.x = pChar->pX;
	posi.y = pChar->pY;
	posi.z = pChar->pZ;
	
 	floorPosi.x = pChar->pX;
	floorPosi.y = pChar->pY+2500;
	floorPosi.z = pChar->pZ;
	
 	g_NewParticleMgr.Start("FuryHit1_g", posi);
	g_NewParticleMgr.Start("FuryHit2_g", floorPosi);

	Assa = SetAssaEffect(0,"m_fury-jin_g.ASE",0,&posi,0);
	cAssaEffect[Assa]->Time = -2;
	cAssaEffect[Assa]->AniMaxCount = 30;
	cAssaEffect[Assa]->AniDelayTime = 4;
	cAssaEffect[Assa]->Angle.y = (-pChar->Angle.y+ANGLE_180)&ANGCLIP;
}

void AssaParticle_CastleBlue(Unit *pChar)
{
	POINT3D posi;
	POINT3D floorPosi;
    posi.x = pChar->pX;
	posi.y = pChar->pY;
	posi.z = pChar->pZ;
	
 	floorPosi.x = pChar->pX;
	floorPosi.y = pChar->pY+2500;
	floorPosi.z = pChar->pZ;
	
 	g_NewParticleMgr.Start("FuryHit1_b", posi);
	g_NewParticleMgr.Start("FuryHit2_b", floorPosi);

	Assa = SetAssaEffect(0,"m_fury-jin_b.ASE",0,&posi,0);
	cAssaEffect[Assa]->Time = -2;
	cAssaEffect[Assa]->AniMaxCount = 30;
	cAssaEffect[Assa]->AniDelayTime = 4;
	cAssaEffect[Assa]->Angle.y = (-pChar->Angle.y+ANGLE_180)&ANGCLIP;
}


int StartEffect_Serqbus_Skill1(Unit *pChar, int liveCount)
{
	if(!AddAssaCodeEffectTime(pChar, MONSTER_SERQBUS_STATE1, liveCount*70))
 	{
		int i = GetAssaEffect();
		cASSAChar *partChar = new cASSAChar;
		partChar->Start(pChar, MONSTER_SERQBUS_STATE1, liveCount*70);
		cAssaEffect[i] = partChar;
	}

	return TRUE;
}

int StartEffect_Serqbus_Skill2(Unit *pChar, int liveCount)
{
	if(!AddAssaCodeEffectTime(pChar, MONSTER_SERQBUS_STATE2, liveCount*70))
	{
		int i = GetAssaEffect();
		cASSAChar *partChar = new cASSAChar;
		partChar->Start(pChar, MONSTER_SERQBUS_STATE2, liveCount*70);
		cAssaEffect[i] = partChar;
 	}
	return TRUE;
}

int StartEffect_Serqbus_Skill3(Unit *pChar, int liveCount)
{
	if(!AddAssaCodeEffectTime(pChar, MONSTER_SERQBUS_STATE3, liveCount*70))
	{
		int i = GetAssaEffect();
		cASSAChar *partChar = new cASSAChar;
		partChar->Start(pChar, MONSTER_SERQBUS_STATE3, liveCount*70);
		cAssaEffect[i] = partChar;
	}
	return TRUE;
}

int AssaParticle_EvilMapleShot(Unit *pChar)
{
	POINT3D posi;
  	posi.x = pChar->pX;
	posi.y = pChar->pY+ 8000;
	posi.z = pChar->pZ;

  	Assa = SetAssaEffect(0,"m_EvilMaple.ASE",0,&posi,0);
	cAssaEffect[Assa]->AniMaxCount = 30;
	cAssaEffect[Assa]->AniDelayTime = 3;
	cAssaEffect[Assa]->Angle.x = (ANGLE_90)&ANGCLIP;
	cAssaEffect[Assa]->Angle.y = (-pChar->Angle.y+ANGLE_180)&ANGCLIP;
	
	auto sPosition = GetMoveLocation(0, 0, 25 * fONE, 0, pChar->Angle.y, 0);
	posi.x += sPosition.iX;
	posi.z += sPosition.iZ;
	g_NewParticleMgr.Start("EvilMaple", posi);

	return TRUE;
}

int AssaParticle_EvilPlantShot(Unit *pChar)
{
	POINT3D posi;
    posi.x = pChar->pX;
	posi.y = pChar->pY+8000;
	posi.z = pChar->pZ;
	
	Assa = SetAssaEffect(0,"m_EvilPlant.ASE",0,&posi,0,5);
	
 	cAssaEffect[Assa]->AniMaxCount = 30;
	cAssaEffect[Assa]->AniDelayTime = 3;
	cAssaEffect[Assa]->Angle.x = (ANGLE_90)&ANGCLIP;
	cAssaEffect[Assa]->Angle.y = (-pChar->Angle.y+ANGLE_180)&ANGCLIP;
	
	Assa = SetAssaEffect(0,"m_EvilPlant2.ASE",0,&posi,0, 5);
	cAssaEffect[Assa]->AniMaxCount = 30;
	cAssaEffect[Assa]->AniDelayTime = 3;
	cAssaEffect[Assa]->Angle.x = (ANGLE_90)&ANGCLIP;
	cAssaEffect[Assa]->Angle.y = (-pChar->Angle.y+ANGLE_180)&ANGCLIP;
	
	auto sPosition = GetMoveLocation(0, 0, 25 * fONE, 0, pChar->Angle.y, 0);
	posi.x += sPosition.iX;
	posi.z += sPosition.iZ;
	g_NewParticleMgr.Start("EvilPlant", posi);
	return TRUE;
}
void AssaParticle_IceserpentSkill(Unit *pChar)
{
	POINT3D posi;

	if (pChar)
	{
		auto sPosition = GetMoveLocation(0, 0, 54 * fONE, 0, pChar->Angle.y, 0);

		posi.x = pChar->pX + sPosition.iX;
		posi.y = pChar->pY + 54 *fONE;
		posi.z = pChar->pZ + sPosition.iZ;

		Assa = SetAssaEffect(0,"m_EvilMaple.ASE",0,&posi,0);
		cAssaEffect[Assa]->AniMaxCount = 30;
		cAssaEffect[Assa]->AniDelayTime = 3;
		cAssaEffect[Assa]->Angle.x = (ANGLE_90|ANGLE_45)&ANGCLIP;
		cAssaEffect[Assa]->Angle.y = (-pChar->Angle.y+ANGLE_180)&ANGCLIP;

		sPosition = GetMoveLocation(0, 0, 25 * fONE, 0, pChar->Angle.y, 0);
		posi.x += sPosition.iX;
		posi.z += sPosition.iZ;
		g_NewParticleMgr.Start("EvilMaple", posi);
	}
}
void AssaParticle_IceserpentHit(Unit *pChar)
{
	POINT3D posi;

	if (pChar)
	{
		auto sPosition = GetMoveLocation(0, 0, 54 * fONE, 0, pChar->Angle.y, 0);

		posi.x = pChar->pX + sPosition.iX;
		posi.y = pChar->pY + 54 * fONE;
		posi.z = pChar->pZ + sPosition.iZ;

		Assa = SetAssaEffect(0,"m_EvilPlant.ASE",0,&posi,0,5);

		cAssaEffect[Assa]->AniMaxCount = 30;
		cAssaEffect[Assa]->AniDelayTime = 3;
		cAssaEffect[Assa]->Angle.x = (ANGLE_90|ANGLE_45)&ANGCLIP;
		cAssaEffect[Assa]->Angle.y = (-pChar->Angle.y+ANGLE_180)&ANGCLIP;

		Assa = SetAssaEffect(0,"m_EvilPlant2.ASE",0,&posi,0, 5);
		cAssaEffect[Assa]->AniMaxCount = 30;
		cAssaEffect[Assa]->AniDelayTime = 3;
		cAssaEffect[Assa]->Angle.x = (ANGLE_90|ANGLE_45)&ANGCLIP;
		cAssaEffect[Assa]->Angle.y = (-pChar->Angle.y+ANGLE_180)&ANGCLIP;

		sPosition = GetMoveLocation(0, 0, 25 * fONE, 0, pChar->Angle.y, 0);
		posi.x += sPosition.iX;
		posi.z += sPosition.iZ;
		g_NewParticleMgr.Start("EvilPlant", posi);
	}
}
int AssaParticle_ThornCrawlerShot(Unit *pChar, POINT3D *destPos)
{
 	smPAT3D *pat = (smPAT3D *)AssaSearchRes("m_thorncrowler.ase", SMMAT_BLEND_LAMP);
	if(pat == NULL)
		return FALSE;
	
	POINT3D curPos;
	curPos.x = pChar->pX;
	curPos.y = pChar->pY+9000;
	curPos.z = pChar->pZ;
	
	D3DVECTOR term;
	term.x = (float)(destPos->x - curPos.x)/(float)fONE;
	term.y = (float)(destPos->y - curPos.y)/(float)fONE;
	term.z = (float)(destPos->z - curPos.z)/(float)fONE;
	
	float length;
 	length = (float)sqrt(term.x*term.x+term.y*term.y+term.z*term.z);
	
	int curLength;
	curLength = (int)(length*fONE);
	
 	if(curLength > 50000)
	{
		destPos->x = pChar->pX;
		destPos->y = pChar->pY;
		destPos->z = pChar->pZ;
		
		auto sPosition = GetMoveLocation(0, 0, 50000, pChar->Angle.x, pChar->Angle.y, 0);
		destPos->x += sPosition.iX;
		destPos->z += sPosition.iZ;
	}
	
	if(curLength < 40000)
	{
		destPos->x = pChar->pX;
		destPos->y = pChar->pY;
		destPos->z = pChar->pZ;
		
		auto sPosition = GetMoveLocation(0, 0, 40000, pChar->Angle.x, pChar->Angle.y, 0);
		destPos->x += sPosition.iX;
		destPos->z += sPosition.iZ;
	}

	int i = GetAssaEffect();
 	cAssaTraceMeshDestParticle *traceMeshDestParticle = new cAssaTraceMeshDestParticle;
 	traceMeshDestParticle->Start(pat,"Box01", &curPos, destPos, "ThornCrawler");
	cAssaEffect[i] = traceMeshDestParticle;
	
	return TRUE;
}

int AssaParticle_StoneGolemShot(Unit *pChar)
{
	POINT3D pos;
    pos.x = pChar->pX;
	pos.y = pChar->pY;
	pos.z = pChar->pZ;
	
	auto sPosition = GetMoveLocation(0, 0, -30 * fONE, pChar->Angle.x, pChar->Angle.y, 0);
	pos.x += sPosition.iX;
	pos.z += sPosition.iZ;
    
	Assa = SetAssaEffect(0,"m_StoneGolem.ASE",0,&pos,0, 1);
	cAssaEffect[Assa]->AniMaxCount = 30;
	cAssaEffect[Assa]->AniDelayTime = 2;
	cAssaEffect[Assa]->Angle.y = (-pChar->Angle.y+ANGLE_180)&ANGCLIP;
	cAssaEffect[Assa]->NotFadeIn = TRUE;
	
	pos.x = pos.x;
	pos.y = pos.y+1500;
	pos.z = pos.z;
	
	sPosition = GetMoveLocation(0, 0, 120 * fONE, pChar->Angle.x, pChar->Angle.y, 0);
	pos.x += sPosition.iX;
	pos.z += sPosition.iZ;
	g_NewParticleMgr.Start("StoneGolemHit1", pos);
	

	return TRUE;
}

int AssaParticle_HeavyGoblinHit1(Unit *pChar)
{
    int i = GetAssaEffect();
 	cAssaTraceCharMeshParticle *traceMeshParticle = new cAssaTraceCharMeshParticle;
 	traceMeshParticle->Start(pChar, "Bip-hammer", "HeavyGoblin", false, 130);
	cAssaEffect[i] = traceMeshParticle;

	POINT3D pos;
 	pos.x = pChar->pX;
	pos.y = pChar->pY;
	pos.z = pChar->pZ;

	auto sPosition = GetMoveLocation(0, 0, 50 * fONE, pChar->Angle.x, pChar->Angle.y, 0);
	pos.x += sPosition.iX;
	pos.z += sPosition.iZ;
	pos.y += fONE * 10;
	g_NewParticleMgr.Start("HeavyGoblinHit1", pos, 1.2f);

	return TRUE;
}

int AssaParticle_HeavyGoblinHit2(Unit *pChar)
{
    int i = GetAssaEffect();
 	cAssaTraceCharMeshParticle *traceMeshParticle = new cAssaTraceCharMeshParticle;
 	traceMeshParticle->Start(pChar, "Bip-hammer", "HeavyGoblin", false, 90);
	cAssaEffect[i] = traceMeshParticle;

	POINT3D pos;
 	pos.x = pChar->pX;
	pos.y = pChar->pY;
	pos.z = pChar->pZ;

  
	auto sPosition = GetMoveLocation(0, 0, 50 * fONE, pChar->Angle.x, pChar->Angle.y, 0);
	pos.x += sPosition.iX;
	pos.z += sPosition.iZ;
	pos.y += fONE*10;
	g_NewParticleMgr.Start("HeavyGoblinHit1", pos, 0.2f);

	return TRUE;
}
void AssParticle_UnDeadManger(Unit *pChar,int nSkill)
{
	POINT3D pos;

	pos.x = pChar->pX;
	pos.y = pChar->pY;
	pos.z = pChar->pZ;

	auto sPosition = GetMoveLocation(0, 0, 60 * fONE, pChar->Angle.x, pChar->Angle.y, 0);

	pos.x += sPosition.iX;
	pos.z += sPosition.iZ;
	pos.y += fONE * 30;

	switch(nSkill)
	{
	case 1:
		g_NewParticleMgr.Start("HulkHit2", pos, 0);
		break;
	case 2:
		g_NewParticleMgr.Start("UndeadMinerHit", pos, 0.2f);
		break;
	}
}
void AssaParticle_Arcuda(Unit *pChar)
{
	POINT3D pos;

	Point3D sPosition;

	if (!pChar->sCharacterData.sSize)
		sPosition = GetMoveLocation(0, 0, 54 * fONE, 0, pChar->Angle.y, 0);
	else
		sPosition = GetMoveLocation(0, 0, 54 * pChar->sCharacterData.sSize, 0, pChar->Angle.y, 0);

	pos.x = pChar->pX + sPosition.iX;
	pos.y = pChar->pY + 128 * fONE;
	pos.z = pChar->pZ + sPosition.iZ;

	g_NewParticleMgr.Start("MonsterHit1",pos);
}
// ¾¿¼«Ö®ÈÐ
void AssaParticle_RollingSmashHit(int x,int y,int z)
{
	POINT3D pos;

	pos.x = x;
	pos.y = y;
	pos.z = z;

	g_NewParticleMgr.Start("Skill5_Meca_RollingSmash_Hit",pos);
}
// ¾¿¼«Ö®ÈÐ
void AssaParticle_RollingSmashDown(int x,int y,int z)
{
	POINT3D pos;

	pos.x = x;
	pos.y = y;
	pos.z = z;

	g_NewParticleMgr.Start("Skill5_Meca_RollingSmash_Down",pos);
}
void AssaParticle_Effect(char *szName, Unit *pChar,int Kind)
{
	POINT3D pos;
	pos.x = pChar->pX;
	pos.y = pChar->pY + 10 * fONE;
	pos.z = pChar->pZ;

	if (Kind == SKILL_SOUL_SHOCK)
	{
		auto sPosition = GetMoveLocation(0, 10 * fONE, 24 * fONE, 0, pChar->Angle.y, 0);
		pos.x = pChar->pX + sPosition.iX;
		pos.y = pChar->pY + sPosition.iY;
		pos.z = pChar->pZ + sPosition.iZ;
	}

	g_NewParticleMgr.Start(szName,pos);
}
int AssaParticle_DoomGuardHit1(Unit *pChar)
{
 	int   iScale = pChar->sCharacterData.sSize;
	float fScale = float(pChar->sCharacterData.sSize)/256.f;
	
	if(iScale <= 1)
		iScale = 0;
	if(fScale <= 1.f)
		fScale = 1.f;

	int i = GetAssaEffect();
  	cAssaTraceCharMeshParticle *traceMeshParticle = new cAssaTraceCharMeshParticle;
	if(fScale <= 1.f)
  		traceMeshParticle->Start(pChar, "Bip-skill01", "DoomGuard", false, 140);
	else
		traceMeshParticle->Start(pChar, "Bip-skill01", "DoomGuardBig", false, 140);
	
	traceMeshParticle->SetScale(fScale);
 	cAssaEffect[i] = traceMeshParticle;
	
	i = GetAssaEffect();
	cAssaMotionBlur *motionBlur = new cAssaMotionBlur;
	motionBlur->Start(pChar, "Bip-skill01", "Bip-skill", 50);
	motionBlur->SetScale(fScale);
	cAssaEffect[i] = motionBlur;
	
	POINT3D pos;
 	pos.x = pChar->pX;
	pos.y = pChar->pY;
	pos.z = pChar->pZ;
	
	auto sPosition = GetMoveLocation(0, 0, 50 * fONE + iScale, pChar->Angle.x, pChar->Angle.y, 0);
	pos.x += sPosition.iX;
	pos.z += sPosition.iZ;
	pos.y += fONE*10;
	
	if(fScale <= 1.f)
   		g_NewParticleMgr.Start("MonsterHit1", pos, 0.5f);
	else 
		g_NewParticleMgr.Start("DoomGuardBigHit", pos, 0.5f);

	return TRUE;
}
void AssaParticle_BlueMountainHit(Unit *pChar)
{
	POINT3D pos;
	if (pChar)
	{
		auto sPosition = GetMoveLocation(0, 0, 100 * fONE, 0, pChar->Angle.y, 0);
		pos.x = pChar->pX + sPosition.iX;
		pos.y = pChar->pY + 2000;
		pos.z = pChar->pZ + sPosition.iZ;

		g_NewParticleMgr.Start("BlueMountainHit1",pos);
	}
}
void AssaParticle_BlueMountainSkill(Unit *pChar)
{
	POINT3D pos;
	if (pChar)
	{
		auto sPosition = GetMoveLocation(0, 0, 130 * fONE, 0, pChar->Angle.y - 170, 0);

		pos.x = pChar->pX + sPosition.iX;
		pos.y = pChar->pY + 1000;
		pos.z = pChar->pZ + sPosition.iZ;

		g_NewParticleMgr.Start("BlueMountainHit1",pos);
	}
}
void AssaParticle_MorgoniaHit(Unit *pChar)
{
	POINT3D pos;
	if (pChar)
	{
		auto sPosition = GetMoveLocation(0, 0, 54 * fONE, 0, pChar->Angle.y, 0);
		pos.x = pChar->pX + sPosition.iX;
		pos.y = pChar->pY + sPosition.iY + 32 * fONE;
		pos.z = pChar->pZ + sPosition.iZ;

		g_NewParticleMgr.Start("MorgoniaHit1",pos);
	}
}
void AssaParticle_BoneHoundSkill(Unit *pChar)
{
	POINT3D pos;

	if (pChar)
	{
		auto sPosition = GetMoveLocation(0, 0, 0, 0, pChar->Angle.y, 0);
		pos.x = pChar->pX + sPosition.iX;
		pos.y = pChar->pY + 1000;
		pos.z = pChar->pZ + sPosition.iZ;

		g_NewParticleMgr.Start("BonehoundSkill2",pos);
	}
}
void AssaParticle_BoneHoundSkillHit(Unit *pChar)
{
	POINT3D pos;

	if (pChar)
	{
		auto sPosition = GetMoveLocation(0, 0, 0, 0, pChar->Angle.y, 0);
		pos.x = pChar->pX + sPosition.iX;
		pos.y = pChar->pY + 3000;
		pos.z = pChar->pZ + sPosition.iZ;

		g_NewParticleMgr.Start("BonehoundSkill1",pos);
	}
}
void AssaParticle_MorgoniaSkill(Unit *pChar)
{
	POINT3D pos;

	if (pChar)
	{
		auto sPosition = GetMoveLocation(0, 0, 30 * fONE, pChar->Angle.x, pChar->Angle.y, 0);
		pos.x = pChar->pX + sPosition.iX;
		pos.y = pChar->pY;
		pos.z = pChar->pZ + sPosition.iZ;

		g_NewParticleMgr.Start("MorgoniaSkill1",pos);
	}
}
void AssaMotionBlur(Unit *pChar, char *meshName1, char *meshName2, int timeCount)
{
	int i = GetAssaEffect();
	cAssaMotionBlur *motionBlur = new cAssaMotionBlur;
	motionBlur->Start(pChar, meshName1, meshName2, timeCount);
	cAssaEffect[i] = motionBlur;
}

int AssaParticle_DoomGuardHit2(Unit *pChar)
{
	int   iScale = pChar->sCharacterData.sSize;
	float fScale = float(pChar->sCharacterData.sSize)/256.f;

	if(iScale <= 1)
		iScale = 0;
	if(fScale <= 1.f)
		fScale = 1.f;

 	int i = GetAssaEffect();
	cAssaTraceCharMeshParticle *traceMeshParticle = new cAssaTraceCharMeshParticle;
 	if(fScale <= 1.f)
		traceMeshParticle->Start(pChar, "Bip-skill01", "DoomGuard", false, 160);
	else
		traceMeshParticle->Start(pChar, "Bip-skill01", "DoomGuardBig", false, 160);
	
	traceMeshParticle->SetScale(fScale);
 	
	cAssaEffect[i] = traceMeshParticle;
	
	i = GetAssaEffect();
	cAssaMotionBlur *motionBlur = new cAssaMotionBlur;
	motionBlur->Start(pChar, "Bip-skill01", "Bip-skill", 150);
	motionBlur->SetScale(fScale);
	cAssaEffect[i] = motionBlur;
	
	POINT3D pos;
 	pos.x = pChar->pX;
	pos.y = pChar->pY;
	pos.z = pChar->pZ;
	
	auto sPosition = GetMoveLocation(0, 0, 70 * fONE + iScale, pChar->Angle.x, pChar->Angle.y, 0);
	pos.x += sPosition.iX;
	pos.z += sPosition.iZ;
	pos.y += fONE*20;
	
	if(fScale <= 1.f)
	{
		g_NewParticleMgr.Start("MonsterHit1", pos, 0.3f);
		g_NewParticleMgr.Start("MonsterHit1", pos, 1.f);
	}
	else
	{
		g_NewParticleMgr.Start("DoomGuardBigHit", pos, 0.3f);
		g_NewParticleMgr.Start("DoomGuardBigHit", pos, 1.f);
	}
	return TRUE;
}


void AssaParticle_MonsterIronFist(Unit *pChar)
{
    int i = GetAssaEffect();
	cAssaMotionBlur *motionBlur = new cAssaMotionBlur;
	//motionBlur->Start(pChar, "Bip01 L Hand", "Bip01 Box05", 60);
 	motionBlur->Start(pChar, "Bip01 Box05", "Bip01 L Hand",45);
	motionBlur->SetDelay(15);
	motionBlur->SetAlpha(-180);
	cAssaEffect[i] = motionBlur;
    
	i = GetAssaEffect();
	motionBlur = new cAssaMotionBlur;
	//motionBlur->Start(pChar, "Bip01 R Hand", "Bip01 Box08", 60);
	motionBlur->Start(pChar, "Bip01 Box08", "Bip01 R Hand", 45);
	motionBlur->SetDelay(15);
	motionBlur->SetAlpha(-180);
	cAssaEffect[i] = motionBlur;
}

void AssaParticle_MonsterIronMorgonHit(Unit *pChar)
{
	POINT3D pos;
  	pos.x = pChar->pX;
	pos.y = pChar->pY;
	pos.z = pChar->pZ;
	
   	//GetMoveLocation( 0, 0,20*fONE, 0, pChar->Angle.y, 0);
	auto sPosition = GetMoveLocation(0, 0, 30 * fONE, pChar->Angle.x, pChar->Angle.y, 0);

	pos.x += sPosition.iX;
	pos.z += sPosition.iZ;

	g_NewParticleMgr.Start("IronMonsterMorgon", pos);
}

int AssaParticle_Hit1(POINT3D *destPos)
{
	g_NewParticleMgr.Start("MonsterHit1", *destPos);
	return TRUE;
}

int AssaParticle_SnailShot(Unit *pChar, POINT3D *destPos)
{
    smPAT3D *pat = (smPAT3D *)AssaSearchRes("m_snail.ase", SMMAT_BLEND_LAMP);
	if(pat == NULL)
		return FALSE;
	
	POINT3D curPos;
	curPos.x = pChar->pX;
	curPos.y = pChar->pY+5000;
	curPos.z = pChar->pZ;
	
	auto sPosition = GetMoveLocation(0, 0, -5 * fONE, pChar->Angle.x, pChar->Angle.y, 0);
	curPos.x += sPosition.iX;
	curPos.z += sPosition.iZ;
	
	
	D3DVECTOR term;
	term.x = (float)(destPos->x - curPos.x)/(float)fONE;
	term.y = (float)(destPos->y - curPos.y)/(float)fONE;
	term.z = (float)(destPos->z - curPos.z)/(float)fONE;
	
	float length;
 	length = (float)sqrt(term.x*term.x+term.y*term.y+term.z*term.z);
	
	int curLength;
	curLength = (int)(length*fONE);
	
 	if(curLength > 50000)
	{
		destPos->x = pChar->pX;
		destPos->y = pChar->pY;
		destPos->z = pChar->pZ;
		
		auto sPosition = GetMoveLocation(0, 0, 50000, pChar->Angle.x, pChar->Angle.y, 0);
		destPos->x += sPosition.iX;
		destPos->z += sPosition.iZ;
	}
	
	if(curLength < 40000)
	{
		destPos->x = pChar->pX;
		destPos->y = pChar->pY;
		destPos->z = pChar->pZ;
		
		auto sPosition = GetMoveLocation(0, 0, 40000, pChar->Angle.x, pChar->Angle.y, 0);
		destPos->x += sPosition.iX;
		destPos->z += sPosition.iZ;
	}

	int i = GetAssaEffect();
 	cAssaTraceMeshDestParticle *traceMeshDestParticle = new cAssaTraceMeshDestParticle;
 	traceMeshDestParticle->Start(pat,"GeoSphere01", &curPos, destPos, "Snail");
	traceMeshDestParticle->SetRenderMesh(false);
	cAssaEffect[i] = traceMeshDestParticle;
	
	return TRUE;
}


int AssaParticle_NightMare(Unit *pChar)
{
	POINT3D posi;

    posi.x = pChar->pX;
	posi.y = pChar->pY+10000;
 	posi.z = pChar->pZ;

    Assa = SetAssaEffect(0,"m_CaveMummy.ASE",0,&posi,0);

	cAssaEffect[Assa]->AniMaxCount = 30;
	cAssaEffect[Assa]->AniDelayTime = 1;
	cAssaEffect[Assa]->Angle.y = (-pChar->Angle.y+ANGLE_180)&ANGCLIP;
	
 	POINT3D posi2;
 	posi2.x = pChar->pX;
	posi2.y = pChar->pY+12000;
 	posi2.z = pChar->pZ;
	
	Assa = SetAssaEffect(0,"m_CaveMummy1.ASE",0,&posi2,0);
	cAssaEffect[Assa]->AniMaxCount = 30;
	cAssaEffect[Assa]->AniDelayTime = 2;
	cAssaEffect[Assa]->Angle.y = (-pChar->Angle.y+ANGLE_180)&ANGCLIP;
	
	
	auto sPosition = GetMoveLocation(0, 0, 50 * fONE, pChar->Angle.x, pChar->Angle.y, 0);
	posi.x += sPosition.iX;
	posi.z += sPosition.iZ;
	posi.y -= fONE*20;
	g_NewParticleMgr.Start("CaveMummy", posi);

	return TRUE;
}

int AssaParticle_RatooHit1(Unit *pChar)
{
	
    int i = GetAssaEffect();
 	cAssaTraceCharMeshParticle *traceMeshParticle = new cAssaTraceCharMeshParticle;
 	traceMeshParticle->Start(pChar, "Bip-skill-02", "Ratoo", false, 60);
  	traceMeshParticle->SetPosLength(-20*fONE);
 	cAssaEffect[i] = traceMeshParticle;
	
	i = GetAssaEffect();
 	traceMeshParticle = new cAssaTraceCharMeshParticle;
 	traceMeshParticle->Start(pChar, "Bip-skill-02", "Ratoo", false, 50);
  	traceMeshParticle->SetPosLength(-45*fONE);
 	cAssaEffect[i] = traceMeshParticle;

	i = GetAssaEffect();
 	traceMeshParticle = new cAssaTraceCharMeshParticle;
 	traceMeshParticle->Start(pChar, "Bip-skill-02", "Ratoo", false, 40);
  	traceMeshParticle->SetPosLength(-70*fONE);
 	cAssaEffect[i] = traceMeshParticle;
	
	
	i = GetAssaEffect();
	cAssaMotionBlur *motionBlur = new cAssaMotionBlur;
	motionBlur->Start(pChar, "Bip-skill-01", "Bip-skill-02", 20);
	motionBlur->SetDelay(2);
	cAssaEffect[i] = motionBlur;


	POINT3D pos;
 	pos.x = pChar->pX;
	pos.y = pChar->pY;
	pos.z = pChar->pZ;

  
	auto sPosition = GetMoveLocation(0, 0, 150 * fONE, pChar->Angle.x, pChar->Angle.y, 1);
	pos.x += sPosition.iX;
	pos.z += sPosition.iZ;
	pos.y += fONE*20;
	g_NewParticleMgr.Start("RatooHit1", pos, 0);
	
     pos.y -= fONE*20;
  	Assa = SetAssaEffect(0,"m_ratoo.ASE",0,&pos,0);
	cAssaEffect[Assa]->Time = -4;
	cAssaEffect[Assa]->AniMaxCount = 20;
	cAssaEffect[Assa]->AniDelayTime = 5;
	cAssaEffect[Assa]->Angle.y = (-pChar->Angle.y+ANGLE_180)&ANGCLIP;
	
    SetDynLight( pos.x, pos.y, pos.z, 100, 150, 200, 255, 350, 5);
	
	return TRUE;
}

int AssaParticleSpiderSkill1(Unit *pChar)
{
	POINT3D posi;
    posi.x = pChar->pX;
	posi.y = pChar->pY;
	posi.z = pChar->pZ;
	
	Assa = SetAssaEffect(0,"m_Spider.ASE",0,&posi,0, 1);
 	cAssaEffect[Assa]->AniMaxCount = 110;
	cAssaEffect[Assa]->AniDelayTime = 2;
	cAssaEffect[Assa]->Angle.y = (-pChar->Angle.y+ANGLE_180)&ANGCLIP;
	
	return TRUE;
}

int AssaParticleClanMonster(Unit *pChar)
{
  	if(GetAssaCodeEffect(pChar, CLAN_MONSTER_PART1) == FALSE)
	{
    	int i = GetAssaEffect();
		cAssaTraceCharMeshParticle *traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pChar, "Bip01 center", "ClanMonster1");
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = CLAN_MONSTER_PART1;

		i = GetAssaEffect();
		traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pChar, "Bip01 center01", "ClanMonster2");
		
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = CLAN_MONSTER_PART1;

		i = GetAssaEffect();
		traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pChar, "Bip01 center02", "ClanMonster2");
		
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = CLAN_MONSTER_PART1;

		i = GetAssaEffect();
		cAssaTwoPointAni *twoPointAni = new cAssaTwoPointAni;
		twoPointAni->Start(pChar, "bip01 s01", "bip01 s02");

		cAssaEffect[i] = twoPointAni;
		cAssaEffect[i]->CODE = CLAN_MONSTER_PART1;
	}

 	return TRUE;
}
int AssaParticleTulla(Unit *pChar)
{
	if(GetAssaCodeEffect(pChar, ICE_MONSTER_CHAOSKARA_STAFF) == FALSE)
	{
		int i = GetAssaEffect();
		cAssaTraceCharMeshParticle *traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pChar, "Bip01 L Finger1", "ChaosKaraStaff");
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = ICE_MONSTER_CHAOSKARA_STAFF;

		i = GetAssaEffect();
		traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pChar, "Bip01 R Finger1", "ChaosKaraStaff");
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = ICE_MONSTER_CHAOSKARA_STAFF;

		i = GetAssaEffect();
		traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pChar, "Bip01 Neck", "ClanMonster1");
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = CLAN_MONSTER_PART1;

		i = GetAssaEffect();
		traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pChar, "Bip01Skirt03", "ClanMonster2");
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = CLAN_MONSTER_PART1;

		i = GetAssaEffect();
		traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pChar, "Bip01Skirt04", "ClanMonster2");
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = CLAN_MONSTER_PART1;

		i = GetAssaEffect();
		traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pChar, "Bip01Skirt07", "ClanMonster2");
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = CLAN_MONSTER_PART1;

		i = GetAssaEffect();
		traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pChar, "Bip01Skirt08", "ClanMonster2");
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = CLAN_MONSTER_PART1;

		i = GetAssaEffect();
		traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pChar, "Bip01Skirt11", "ClanMonster2");
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = CLAN_MONSTER_PART1;

		i = GetAssaEffect();
		traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pChar, "Bip01Skirt12", "ClanMonster2");
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = CLAN_MONSTER_PART1;

		i = GetAssaEffect();
		traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pChar, "Bip01Skirt15", "ClanMonster2");
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = CLAN_MONSTER_PART1;

		i = GetAssaEffect();
		traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pChar, "Bip01Skirt16", "ClanMonster2");
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = CLAN_MONSTER_PART1;
	}
	return TRUE;
}
int AssaParticleClanMonsterHit1(Unit *pChar)
{
 	
	if(pChar->AnimPattern == NULL)
		return FALSE;
	
 	smOBJ3D *SearchObj1 = pChar->AnimPattern->GetObjectFromName("bip01 s01"); //¿ÀºêÁ§Æ®¸¦ ÀÐ´Â´Ù
	if(SearchObj1 == NULL)
		return FALSE;
	POINT3D pos;

	smMATRIX *mWorld;
	mWorld = &SearchObj1->mWorld;
	POINT3D angle;
	memcpy( &angle, &pChar->Angle , sizeof( POINT3D ) );
 	angle.y = (-angle.y+ANGLE_180)&ANGCLIP;
	
	AnimObjectTree( SearchObj1, 198400, angle.x, angle.y, angle.z);
	
	pos.x = pChar->pX + mWorld->_41;
	pos.z = pChar->pZ + mWorld->_42;
	pos.y = pChar->pY + mWorld->_43;

	//AssaSearchObjPos(pChar, SearchObj1, &pos);
	
 	pos.y = pChar->pY;

	int i = GetAssaEffect();
	cASSAPARTSHOT *partShot = new cASSAPARTSHOT;
	
	POINT3D curPos;
	POINT3D desPos;
	curPos.x = pos.x;
	curPos.y = pos.y+50000;
	curPos.z = pos.z;

	desPos.x = pos.x;
	desPos.y = pos.y+5000;
	desPos.z = pos.z-20000;
 	partShot->Start(&curPos, &desPos, ASSA_SHOT_SPARK1);
	cAssaEffect[i] = partShot;

    i = GetAssaEffect();
	partShot = new cASSAPARTSHOT;
	
	
	curPos.x = pos.x;
	curPos.y = pos.y+50000;
	curPos.z = pos.z;

	desPos.x = pos.x;
	desPos.y = pos.y+5000;
	desPos.z = pos.z+20000;
	partShot->Start(&curPos, &desPos, ASSA_SHOT_SPARK1);
	cAssaEffect[i] = partShot;


	i = GetAssaEffect();
	partShot = new cASSAPARTSHOT;
	curPos.x = pos.x;
	curPos.y = pos.y+50000;
	curPos.z = pos.z;

	desPos.x = pos.x+20000;
	desPos.y = pos.y+5000;
	desPos.z = pos.z;
	partShot->Start(&curPos, &desPos, ASSA_SHOT_SPARK1);
	cAssaEffect[i] = partShot;


	i = GetAssaEffect();
	partShot = new cASSAPARTSHOT;
	curPos.x = pos.x;
	curPos.y = pos.y+50000;
	curPos.z = pos.z;

	desPos.x = pos.x-20000;
	desPos.y = pos.y+5000;
	desPos.z = pos.z;

	partShot->Start(&curPos, &desPos, ASSA_SHOT_SPARK1);
	cAssaEffect[i] = partShot;
	

	 return TRUE;
}


int AssaParticleClanMonsterHit2(Unit *pChar)
{
  	int i = GetAssaEffect();
    cAssaTraceCharMeshParticle *traceMeshParticle = new cAssaTraceCharMeshParticle;
   	traceMeshParticle->Start(pChar, "bip01 s01", "DoomGuard", false, 50);
   	//traceMeshParticle->SetPosLength(10*fONE);
	
	cAssaEffect[i] = traceMeshParticle;
	i = GetAssaEffect();
	cAssaMotionBlur *motionBlur = new cAssaMotionBlur;
   	motionBlur->Start(pChar, "bip01 s01", "bip01 s02", 25);
	cAssaEffect[i] = motionBlur;
	
	return TRUE;
}

int AssaParticle_Sprak1(POINT3D *pPosi)
{
    for(int index = 0; index < 4; index++)
	{
		int i = GetAssaEffect();
		cASSAPARTSPARK *partSpark = new cASSAPARTSPARK;
		
		partSpark->Start(pPosi, "spark01_01.bmp");
		partSpark->Time = GetRandomPos(0,15);
		cAssaEffect[i] = partSpark;
	}
	SetDynLight( pPosi->x, pPosi->y, pPosi->z, 200, 255, 255, 200, 100, 2);
	
 	g_NewParticleMgr.Start("ClanMonster4", *pPosi);
	//g_NewParticleMgr.Start("ClanMonster4", *pPosi);
	//g_NewParticleMgr.Start("DivineLightning", *pPosi);
	
	return TRUE;
}
void AssaParticle_ConcentrationStart(Unit *pChar)
{
	StopAssaCodeEffect(pChar, SKILL_CONCENTRATION);
	POINT3D pos;
 	memcpy(&pos, &pChar->Posi, sizeof(POINT3D));
   	pos.y += 8000;
	
	POINT3D curPos;
	POINT3D rand;

    for(int index = 0; index < 20; index++)
	{
        rand.x = GetRandomPos(-18, 18);
		rand.y = GetRandomPos(-18, 18);
		rand.z = GetRandomPos(-18, 18);
		
		double length = sqrt((float)rand.x*(float)rand.x+(float)rand.y*(float)rand.y+(float)rand.z*(float)rand.z);
		
		if(length == 0)
			length = 1;
	 	int range = GetRandomPos(19000, 20000);
 		curPos.x = int(((float)rand.x/length)*(float)range+(float)pos.x);
		curPos.y = int(((float)rand.y/length)*(float)range+(float)pos.y);
		curPos.z = int(((float)rand.z/length)*(float)range+(float)pos.z);
		
		Assa = SetAssaEffect( 80, "flare.tga", 0, &curPos, 0);
		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE;
		
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE;

 		cAssaEffect[Assa]->Face.r = 255;
		cAssaEffect[Assa]->Face.g = 150;
		cAssaEffect[Assa]->Face.b = 50;
		cAssaEffect[Assa]->Face.Transparency = 255;
 		cAssaEffect[Assa]->Time = -(index/2);
  	 	cAssaEffect[Assa]->MoveSpeed.x = -int(float(rand.x)/length*400.f);
		cAssaEffect[Assa]->MoveSpeed.y = -int(float(rand.y)/length*400.f);
		cAssaEffect[Assa]->MoveSpeed.z = -int(float(rand.z)/length*400.f);
		
 		cAssaEffect[Assa]->Size.w = 400;

		POINT3D inScale;
  		inScale.x = int((rand.x)/(float)length*8000.f);
		inScale.y = int((rand.y)/(float)length*8000.f);
		inScale.z = int((rand.z)/(float)length*8000.f);
		
		cAssaEffect[Assa]->ScalePosi.x = -inScale.x;
		cAssaEffect[Assa]->ScalePosi.y = -inScale.y;
		cAssaEffect[Assa]->ScalePosi.z = -inScale.z;
	}
	
    for(int index = 0; index < 40; index++)
	{
   		rand.x = GetRandomPos(-100, 100);
		rand.y = GetRandomPos(-100, 100);
		rand.z = GetRandomPos(-100, 100);
		
		double length = sqrt((float)rand.x*(float)rand.x+(float)rand.y*(float)rand.y+(float)rand.z*(float)rand.z);
		
		if(length == 0)
			length = 1;
		
 		int range = GetRandomPos(5000,7000);
     	curPos.x = int(float(rand.x)/length*(float)range+(float)pos.x);
		curPos.y = int(float(rand.y)/length*(float)range+(float)pos.y);
		curPos.z = int(float(rand.z)/length*(float)range+(float)pos.z);
		
		Assa = SetAssaEffect(200,"flare.tga",0,&curPos,0);                
		
 		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE;
   		cAssaEffect[Assa]->Time = -(15+index/2);
		
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE;
  	 	cAssaEffect[Assa]->MoveSpeed.x = int(float(rand.x)/length*(150.f));
		cAssaEffect[Assa]->MoveSpeed.y = int(float(rand.y)/length*(150.f));
		cAssaEffect[Assa]->MoveSpeed.z = int(float(rand.z)/length*(150.f));
		
 		cAssaEffect[Assa]->Size.w = 500;
		cAssaEffect[Assa]->Face.r = 255;
		cAssaEffect[Assa]->Face.g = 150;
		cAssaEffect[Assa]->Face.b = 50;
		cAssaEffect[Assa]->Face.Transparency = 255;

		POINT3D destPos;
   		destPos.x = int(float(rand.x)/length*12000.f);
		destPos.y = int(float(rand.y)/length*12000.f);
		destPos.z = int(float(rand.z)/length*12000.f);
		
		cAssaEffect[Assa]->ScalePosi.x = -destPos.x;
		cAssaEffect[Assa]->ScalePosi.y = -destPos.y;
		cAssaEffect[Assa]->ScalePosi.z = -destPos.z;
	}
}
void AssaParticle_ConcentrationEffect(Unit *pChar,int liveCount,int SkillCode,int Light)
{
	int SkillTime = liveCount*70+140;

	if (AddAssaCodeEffectTime(pChar,SkillCode,SkillTime) == 0)
	{
		int i = GetAssaEffect();
		AssaSkill3Concentration *concentration = new AssaSkill3Concentration;
		concentration->Start(pChar, liveCount,Light);
		cAssaEffect[i] = concentration;
	}
}
void AssaParticle_AvangingCrash(Unit* pChar)
{
 	POINT3D pos;
	if(pChar->GetAttackPoint(&pos.x, &pos.y, &pos.z) == TRUE)
	{
		
   		SetDynLight( pos.x, pChar->pY, pos.z, 255, 100, 50,0, 190, 3);
	 	
		g_NewParticleMgr.Start("Skill3Hit1", pos);
	}
}

void AssaParticle_BoneSmash1(Unit* pChar)
{
	if(pChar == NULL)
		return;
 	int motionEvent = pChar->MotionEvent;
	
  	int i = GetAssaEffect();
 	AssaSkillWeaponMotionBlur *motionBlur = new AssaSkillWeaponMotionBlur;
	if(motionEvent == 1)
		motionBlur->Start(pChar, 12);
	else
		motionBlur->Start(pChar, 15);

  	cAssaEffect[i] = motionBlur;
	
	POINT3D pos;
     if ( pChar->GetAttackPoint( &pos.x,&pos.y,&pos.z)==TRUE )
	{
		pos.y += 3000;
		
		g_NewParticleMgr.Start("Skill3Hit6", pos);

		if(motionEvent == 1)
			SetDynLight( pos.x, pChar->pY, pos.z, 255, 100, 50,0, 140, 3);
		else
		{
			pos.y = pChar->pY+2000;
			SetDynLight( pos.x, pChar->pY, pos.z, 255, 100, 50,0, 200, 3);
			g_NewParticleMgr.Start("Skill3FighterBoneSmash1", pos);
		}
	}
}


void AssaParticle_SwiftAxeStart(Unit *pChar)
{
	StopAssaCodeEffect(pChar,SKILL_SWIFT_AXE);

	POINT3D pos;
 	memcpy(&pos, &pChar->Posi, sizeof(POINT3D));
   	pos.y += 8000;
	
	POINT3D curPos;
	POINT3D rand;

    for(int index = 0; index < 20; index++)
	{
        rand.x = GetRandomPos(-18, 18);
		rand.y = GetRandomPos(-18, 18);
		rand.z = GetRandomPos(-18, 18);
		
		double length = sqrt((float)rand.x*(float)rand.x+(float)rand.y*(float)rand.y+(float)rand.z*(float)rand.z);
		
		if(length == 0)
			length = 1;
	 	int range = GetRandomPos(19000, 20000);
 		curPos.x = int(((float)rand.x/length)*(float)range+(float)pos.x);
		curPos.y = int(((float)rand.y/length)*(float)range+(float)pos.y);
		curPos.z = int(((float)rand.z/length)*(float)range+(float)pos.z);
		
		Assa = SetAssaEffect( 80, "flare.tga", 0, &curPos, 0);
		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE;
		
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE;
		

 		cAssaEffect[Assa]->Face.r = 50;
		cAssaEffect[Assa]->Face.g = 80;
		cAssaEffect[Assa]->Face.b = 255;
		cAssaEffect[Assa]->Face.Transparency = 255;
 		cAssaEffect[Assa]->Time = -(index/2);
  	 	cAssaEffect[Assa]->MoveSpeed.x = -int(float(rand.x)/length*400.f);
		cAssaEffect[Assa]->MoveSpeed.y = -int(float(rand.y)/length*400.f);
		cAssaEffect[Assa]->MoveSpeed.z = -int(float(rand.z)/length*400.f);
		
 		cAssaEffect[Assa]->Size.w = 400;

		POINT3D inScale;
  		inScale.x = int((rand.x)/(float)length*8000.f);
		inScale.y = int((rand.y)/(float)length*8000.f);
		inScale.z = int((rand.z)/(float)length*8000.f);
		
		cAssaEffect[Assa]->ScalePosi.x = -inScale.x;
		cAssaEffect[Assa]->ScalePosi.y = -inScale.y;
		cAssaEffect[Assa]->ScalePosi.z = -inScale.z;
	}
    for(int index = 0; index < 40; index++)
	{
   		rand.x = GetRandomPos(-100, 100);
		rand.y = GetRandomPos(-100, 100);
		rand.z = GetRandomPos(-100, 100);
		
		double length = sqrt((float)rand.x*(float)rand.x+(float)rand.y*(float)rand.y+(float)rand.z*(float)rand.z);
		
		if(length == 0)
			length = 1;
		
 		int range = GetRandomPos(5000,7000);
     	curPos.x = int(float(rand.x)/length*(float)range+(float)pos.x);
		curPos.y = int(float(rand.y)/length*(float)range+(float)pos.y);
		curPos.z = int(float(rand.z)/length*(float)range+(float)pos.z);
		
		Assa = SetAssaEffect(200,"flare.tga",0,&curPos,0);                
		
 		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE;
   		cAssaEffect[Assa]->Time = -(15+index/2);
		
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE;
  	 	cAssaEffect[Assa]->MoveSpeed.x = int(float(rand.x)/length*(150.f));
		cAssaEffect[Assa]->MoveSpeed.y = int(float(rand.y)/length*(150.f));
		cAssaEffect[Assa]->MoveSpeed.z = int(float(rand.z)/length*(150.f));
		
 		cAssaEffect[Assa]->Size.w = 500;
		cAssaEffect[Assa]->Face.r = 50;
		cAssaEffect[Assa]->Face.g = 80;
		cAssaEffect[Assa]->Face.b = 255;
		cAssaEffect[Assa]->Face.Transparency = 255;

		POINT3D destPos;
   		destPos.x = int(float(rand.x)/length*12000.f);
		destPos.y = int(float(rand.y)/length*12000.f);
		destPos.z = int(float(rand.z)/length*12000.f);
		
		cAssaEffect[Assa]->ScalePosi.x = -destPos.x;
		cAssaEffect[Assa]->ScalePosi.y = -destPos.y;
		cAssaEffect[Assa]->ScalePosi.z = -destPos.z;
	}
}
void AssaParticle_SwiftAxeEffect(Unit *pChar,int liveCount,int SkillCode,int Light)
{
	int SkillTime = liveCount*70+140;

	if (AddAssaCodeEffectTime(pChar,SkillCode,SkillTime) == 0)
	{
		int i = GetAssaEffect();
		AssaSkill3SwiftAxe *swiftAxe = new AssaSkill3SwiftAxe;
		swiftAxe->Start(pChar, liveCount,Light);
		cAssaEffect[i] = swiftAxe;
	}
}
//°£¿ËË¹Ð§¹û
void AssaParticle_Draxos(Unit *pChar)
{
	if (GetAssaCodeEffect(pChar,DRAXOS_MONSTER_STAFF) == FALSE)
	{
		int i = GetAssaEffect();
		cAssaTraceCharMeshParticle *traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pChar,"Bip01 Spine","DraxosBody");
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = DRAXOS_MONSTER_STAFF;
	}
}
void AssParticle_Greedy(Unit *pChar)
{
	if (GetAssaCodeEffect(pChar,GREEDY_MONSTER_STAFF) == FALSE)
	{
		int i = 0;
		cAssaTraceCharMeshParticle *traceMeshParticle = NULL;

		i = GetAssaEffect();
		traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pChar,"Bip01 L Finger1","GreedyBody");
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = GREEDY_MONSTER_STAFF;

		i = GetAssaEffect();
		traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pChar,"Bip01 R Finger1","GreedyBody");
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = GREEDY_MONSTER_STAFF;
	}
}
void AssParticle_Midranda(Unit *pChar)
{
	if (GetAssaCodeEffect(pChar,MIDRANDA_MONSTER_STAFF) == FALSE)
	{
		int i = 0;
		cAssaTraceCharMeshParticle *traceMeshParticle = NULL;
		i = GetAssaEffect();
		traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pChar,"Bip01 L UpperArm","MonsterMidrandaUpperArm");
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = MIDRANDA_MONSTER_STAFF;

		i = GetAssaEffect();
		traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pChar,"Bip01 R UpperArm","MonsterMidrandaUpperArm");
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = MIDRANDA_MONSTER_STAFF;

		i = GetAssaEffect();
		traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pChar,"Bip01 Pelvis","MonsterMidrandaPelvis");
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = MIDRANDA_MONSTER_STAFF;

		i = GetAssaEffect();
		traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pChar,"Bip01 L Finger1","MonsterMidrandaHand");
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = MIDRANDA_MONSTER_STAFF;

		i = GetAssaEffect();
		traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pChar,"Bip01 R Finger1","MonsterMidrandaHand");
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = MIDRANDA_MONSTER_STAFF;
	}
}
void AssParticle_Faugn(Unit *pChar)
{
	if (GetAssaCodeEffect(pChar,FAUGN_MONSTER_STAFF) == FALSE)
	{
		int i = GetAssaEffect();
		cAssaTraceCharMeshParticle *traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pChar,"Bip01 Faugn01","FaugnBody");
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = FAUGN_MONSTER_STAFF;
	}
}
void AssParticle_Yagditha(Unit *pChar)
{
	if (GetAssaCodeEffect(pChar,YAGDITHA_MONSTER_STAFF) == FALSE)
	{
		int i = GetAssaEffect();
		cAssaTraceCharMeshParticle *traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pChar,"Bip01 Spine","YagdithaBody");
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = YAGDITHA_MONSTER_STAFF;
	}
}
void AssaParticle_BoneSmash2(Unit* pChar)
{
	int i = GetAssaEffect();
	AssaSkillWeaponMotionBlur *motionBlur = new AssaSkillWeaponMotionBlur;
	motionBlur->Start(pChar, 20);
	cAssaEffect[i] = motionBlur;
}
//Á´ÆïÖ®Ç¹
void AssaParticle_ChainLance(POINT3D *pPosi)
{
	
 	pPosi->y += 3000;
	int partID = g_NewParticleMgr.Start("Skill3Hit3", *pPosi);

	POINT3D angle;
	angle.x = rand()%ANGLE_45;
	angle.y = rand()%ANGLE_360;
	angle.z = rand()%ANGLE_45;
	g_NewParticleMgr.SetAngle(partID, angle); 
   	SetDynLight( pPosi->x, pPosi->y, pPosi->z, 100,50,0,0, 250 , 5);
}

void SkillShadowMasterHit(POINT3D *pos)
{
	AssaParticle_ChainLance(pos);
}
//»ØÐý´ò»÷
void AssaParticle_Reaper(POINT3D *pos)
{
	pos->y += 3000;
	int partID = g_NewParticleMgr.Start("Skill3Hit7", *pos);

	POINT3D angle;
	angle.x = rand()%ANGLE_45;
	angle.y = rand()%ANGLE_360;
	angle.z = rand()%ANGLE_45;
	g_NewParticleMgr.SetAngle(partID, angle); 
	SetDynLight(pos->x,pos->y,pos->z,50,50,200,0,250,10);
}
//ÁéÉßµØÇ¹
void AssaParticle_VeonmSpear(Unit *pDest)
{
	POINT3D charPos;
    charPos.x = pDest->pX;
	charPos.y = pDest->pY;
	charPos.z = pDest->pZ;
	
    float delayTime = float(rand()%3);
 	delayTime = delayTime / 3.f;
  	g_NewParticleMgr.Start("Skill3PikeManVenomSpear",charPos,delayTime);
	
	Assa = SetAssaEffect(0,"pk3_Venom24-2.ASE",0,&charPos,0,0);
 	cAssaEffect[Assa]->AniMaxCount	= 24;
	cAssaEffect[Assa]->AniDelayTime = 3;
	cAssaEffect[Assa]->Time			= -int(delayTime*70);
}
//µØÏ®ÆæÇ¹
void AssaParticle_Spear(Unit *pDest)
{
	POINT3D charPos;
	charPos.x = pDest->pX;
	charPos.y = pDest->pY;
	charPos.z = pDest->pZ;

	float delayTime = float(rand()%3);
	delayTime = delayTime / 3.f;

	g_NewParticleMgr.Start("Skill5_PikeMan_FinalSpear3",charPos,delayTime);

	Assa = SetAssaEffect(0,"pk5_FinalSpear.ASE",0,&charPos,0,0);
	cAssaEffect[Assa]->AniMaxCount	= 24;
	cAssaEffect[Assa]->AniDelayTime = 3;
	cAssaEffect[Assa]->Time			= -int(delayTime*70);

	charPos.x = pDest->Posi.x;
	charPos.y = pDest->Posi.y;
	charPos.z = pDest->Posi.z;

	g_NewParticleMgr.Start("Skill5_PikeMan_FinalSpear4",charPos);
}

void AssaParticle_VeonmSpearPike(Unit *pChar)
{
	auto sPosition = GetMoveLocation(0, 0, 25 * fONE, 0, pChar->Angle.y, 0);
 	POINT3D charPos;
	charPos.x = pChar->pX + sPosition.iX;
	charPos.y = pChar->pY + 1000;
	charPos.z = pChar->pZ + sPosition.iZ;
	
  	g_NewParticleMgr.Start("Skill3PikeManVenomSpear1", charPos, 1.f);
}

void AssaParticle_Vanish(Unit *pChar)
{
	POINT3D pos;
  	pos.x = pChar->pX;
	pos.y = pChar->pY+1000;
	pos.z = pChar->pZ;
	
	int i = GetAssaEffect();
	AssaSkill3Vanish *vanish = new AssaSkill3Vanish;
	vanish->Start(pChar);
	cAssaEffect[i] = vanish;
	
	
	
	POINT3D rand;
	POINT3D curPos;
 	pos.y += 5000;

     for(int index = 0; index < 100; index++)
	{
		//ÆÄÆ¼Å¬ÀÌ ³ª¿Ã ¿µ¿ª.. 
		rand.x = GetRandomPos(-20, 20);
		rand.y = GetRandomPos(-20, 20);
		rand.z = GetRandomPos(-20, 20);
		
 		double length = sqrt((float)rand.x*(float)rand.x+(float)rand.y*(float)rand.y+(float)rand.z*(float)rand.z);
		
		if(length == 0)
			length = 1;
	 	int range = GetRandomPos(19000, 20000);
 		curPos.x = int(((float)rand.x/length)*(float)range+(float)pos.x);
		curPos.y = int(((float)rand.y/length)*(float)range+(float)pos.y);
		curPos.z = int(((float)rand.z/length)*(float)range+(float)pos.z);
		
  		Assa = SetAssaEffect( 50, "flare.tga", 0, &curPos, 0);
		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_BILLBOARD;
		
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE;
		

        cAssaEffect[Assa]->Face.r = 150;
		cAssaEffect[Assa]->Face.g = 150;
		cAssaEffect[Assa]->Face.b = 255;
		cAssaEffect[Assa]->Face.Transparency = 220;
 		cAssaEffect[Assa]->Time = -(index);
   	 	cAssaEffect[Assa]->MoveSpeed.x = -int(float(rand.x)/length*610.f);
 		cAssaEffect[Assa]->MoveSpeed.y = -int(float(rand.y)/length*610.f);
 		cAssaEffect[Assa]->MoveSpeed.z = -int(float(rand.z)/length*610.f);
		
		//ÆÄÆ¼Å¬ÀÇ ³ÐÀÌ..
   		cAssaEffect[Assa]->Size.w = 1200+GetRandomPos(0,500);
	}

}



void AssaParticle_ElementalShotFire(POINT3D* pCur, POINT3D* pDest)
{
	int i = GetAssaEffect(); 
 	AssaSkill3ElementalShot *elementalShot = new AssaSkill3ElementalShot;
 	elementalShot->Start(pCur, pDest, ELEMENTAL_FIRE);
	cAssaEffect[i] = elementalShot;
}

void AssaParticle_ElementalShotLighting(POINT3D* pCur, POINT3D* pDest)
{
	int i = GetAssaEffect(); 
	AssaSkill3LightingJavelin *lightingJavelin = new AssaSkill3LightingJavelin;
	lightingJavelin->StartShort(pCur, pDest);
	cAssaEffect[i] = lightingJavelin;
}


void AssaParticle_GoldenFalcon(Unit *pChar, int liveCount)
{
	StartSkill(pChar->pX, pChar->pY, pChar->pZ, 0, 0, 0, pChar, SKILL_GOLDEN_FALCON, liveCount);
}


void AssaParticle_BombShot(POINT3D* pCur, POINT3D* pDest)
{
	int i = GetAssaEffect(); 
 	AssaSkill3BombShot *bombShot = new AssaSkill3BombShot;
 	bombShot->Start(pCur, pDest);
	cAssaEffect[i] = bombShot;
}


void AssaParticle_BombHit1(POINT3D *pPosi)
{
	POINT3D pos;
	memcpy(&pos, pPosi, sizeof(POINT3D));
	D3DVECTOR velocity;
 	D3DVECTOR gravity;
	
    
 	for(int index = 0; index < 3; index++)
  	{
		int i = GetAssaEffect(); 
		velocity.x = float(rand()%2400-1200);
		velocity.y = float(rand()%500+800);
		velocity.z = float(rand()%2400-1200);

  		gravity.x = 0;
 		gravity.y = float((rand()%500-670));
		gravity.z = 0;
		
		AssaSkill3BombShotExplision *explision = new AssaSkill3BombShotExplision;
		explision->Start(&pos, &velocity, &gravity);
		cAssaEffect[i] = explision;
	}

	g_NewParticleMgr.Start("Skill3ArcherBombShotHit1", pos);
 	SetDynLight( pos.x, pos.y, pos.z, 255, 150, 50, 255, 200, 2);

}

void AssaParticle_Perforation(POINT3D* pCur, POINT3D* pDest)
{
	int i = GetAssaEffect(); 
	AssaSkill3Perforation *perforation = new AssaSkill3Perforation;
	perforation->Start(pCur, pDest);
	cAssaEffect[i] = perforation;
}

void AssaParticle_PerforationHit(Unit* monster, Unit* character, float delay)
{
	POINT3D pos;
 	pos.x = monster->pX;
	pos.y = monster->pY+2000;
	pos.z = monster->pZ;

	int num = -1;
	if(delay == 0.f)
		num = g_NewParticleMgr.Start("TwistJavelin2", pos, 0.f);
	else
		num = g_NewParticleMgr.Start("TwistJavelin2", pos, delay);

	POINT3D angle;
	angle.x = 0;
	angle.y = character->Angle.y;
	angle.z = 0;
    g_NewParticleMgr.SetAngle(num, angle);
}


void AssaParticle_GrandSmash(Unit *pChar)//(POINT3D *pPosi)
{
	/*
 	pPosi->y += 3000;
	int partID = g_NewParticleMgr.Start("Skill3Hit2", *pPosi);

	POINT3D angle;
	angle.x = rand()%ANGLE_90;
	angle.y = rand()%ANGLE_360;
	angle.z = rand()%ANGLE_90;
	g_NewParticleMgr.SetAngle(partID, angle); 
	*/

 	if(pChar == NULL)
		return;
 	int motionEvent = pChar->MotionEvent;
	
  	int i = GetAssaEffect();
 	AssaSkillWeaponMotionBlur *motionBlur = new AssaSkillWeaponMotionBlur;
	if(motionEvent == 1)
		motionBlur->Start(pChar, 12);
	else
		motionBlur->Start(pChar, 15);
	

     cAssaEffect[i] = motionBlur;
	
	POINT3D pos;
    if ( pChar->GetAttackPoint( &pos.x,&pos.y,&pos.z)==TRUE )
	{
 		pos.y += 3000;
		g_NewParticleMgr.Start("Skill3Hit2", pos);
		StartSkill(pos.x, pos.y, pos.z, 0, 0, 0, SKILL_GRAND_SMASH);
		SetDynLight( pos.x,pos.y,pos.z, 0,100,50,0, 250 , 5);
	}

}

void AssaParticle_MetalArmorStart(Unit *pChar)
{
	StopAssaCodeEffect(pChar,SKILL_METAL_ARMOR);

	POINT3D charPos;
	charPos.x = pChar->pX;
	charPos.y = pChar->pY;
	charPos.z = pChar->pZ;
	StartSkill(charPos.x,charPos.y,charPos.z, 0, 0, 0, SKILL_METALARMOR);
}
void AssaParticle_MetalArmorEffect(Unit *pChar, int liveCount)
{
	int SkillTime = liveCount*70+150;

	if (AddAssaCodeEffectTime(pChar,SKILL_METAL_ARMOR,SkillTime) == 0)
	{
		int i = GetAssaEffect();
		AssaSkill3MetalArmor *metalArmor = new AssaSkill3MetalArmor;
		metalArmor->Start(pChar, liveCount);
		cAssaEffect[i] = metalArmor;
	}
}

void AssaParticle_SparkShieldDefence(POINT3D *pPosi, POINT3D *pDesti)
{
	g_NewParticleMgr.Start("LightStart1", *pPosi);	
	g_NewParticleMgr.Start("LightHit1", *pDesti);
	
	SetDynLight( pDesti->x, pDesti->y, pDesti->z, 255, 255, 255, 255, 150, 2);

	Assa = SetAssaEffect(100,"spark01_01.bmp",0,pPosi,0);
	AssaGetAniFileMat(cAssaEffect[Assa]);
	cAssaEffect[Assa]->AniDelayTime = 3;
	cAssaEffect[Assa]->Face.r = 150;
	cAssaEffect[Assa]->Face.g = 255;
	cAssaEffect[Assa]->Face.b = 150;
	cAssaEffect[Assa]->Face.Transparency = 255;
	cAssaEffect[Assa]->Size.w = 5000;
	cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE; 
	
	cAssaEffect[Assa]->ScalePosi.x = pDesti->x - pPosi->x;
	cAssaEffect[Assa]->ScalePosi.y = pDesti->y - pPosi->y;
	cAssaEffect[Assa]->ScalePosi.z = pDesti->z - pPosi->z;

	Assa = SetAssaEffect(100,"spark01_01.bmp",0,pPosi,0);
	AssaGetAniFileMat(cAssaEffect[Assa]);
	cAssaEffect[Assa]->AniDelayTime = 3;
	cAssaEffect[Assa]->Face.r = 150;
	cAssaEffect[Assa]->Face.g = 255;
	cAssaEffect[Assa]->Face.b = 150;
	cAssaEffect[Assa]->Face.Transparency = 255;
	cAssaEffect[Assa]->Size.w = 5000;
	cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE; 
	
	cAssaEffect[Assa]->ScalePosi.x = pDesti->x - pPosi->x;
	cAssaEffect[Assa]->ScalePosi.y = pDesti->y - pPosi->y;
	cAssaEffect[Assa]->ScalePosi.z = pDesti->z - pPosi->z;
}

void AssaParticle_SparkShieldStart(Unit *pChar)
{
 	StopAssaCodeEffect(pChar, SKILL_SPARK_SHIELD);
	
	auto sPosition = GetMoveLocation(0, 0, 10 * fONE, 0, pChar->Angle.y, 0);
	POINT3D curPos;
	curPos.x = pChar->pX + sPosition.iX;
	curPos.y = pChar->pY + 8000;
	curPos.z = pChar->pZ + sPosition.iZ;
	

	g_NewParticleMgr.Start("Skill3MechanicianSparkShield", curPos, 0.2f);
	POINT3D destPos;
	destPos.x = curPos.x + 30000;
	destPos.y = curPos.y + 80000;
	destPos.z = curPos.z + 30000;
	
   	Assa = SetAssaEffect(90,"spark01_01.bmp",0,&curPos,0);
	AssaGetAniFileMat(cAssaEffect[Assa]);
	cAssaEffect[Assa]->AniDelayTime = 3;
	cAssaEffect[Assa]->Face.r = 150;
	cAssaEffect[Assa]->Face.g = 255;
	cAssaEffect[Assa]->Face.b = 150;
	cAssaEffect[Assa]->Face.Transparency = 200;
	cAssaEffect[Assa]->Size.w = 5000;
	cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE; 
	
	cAssaEffect[Assa]->ScalePosi.x = destPos.x - curPos.x;
	cAssaEffect[Assa]->ScalePosi.y = destPos.y - curPos.y;
	cAssaEffect[Assa]->ScalePosi.z = destPos.z - curPos.z;

	destPos.x = curPos.x + 22000;
	destPos.y = curPos.y + 75000;
	destPos.z = curPos.z + 22000;
	
  	Assa = SetAssaEffect(100,"spark01_01.bmp",0,&curPos,0);
	AssaGetAniFileMat(cAssaEffect[Assa]);
	cAssaEffect[Assa]->AniDelayTime = 3;
	cAssaEffect[Assa]->Face.r = 150;
	cAssaEffect[Assa]->Face.g = 255;
	cAssaEffect[Assa]->Face.b = 150;
	cAssaEffect[Assa]->Face.Transparency = 200;
	cAssaEffect[Assa]->Size.w = 5000;
	cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE; 
	
	cAssaEffect[Assa]->ScalePosi.x = destPos.x - curPos.x;
	cAssaEffect[Assa]->ScalePosi.y = destPos.y - curPos.y;
	cAssaEffect[Assa]->ScalePosi.z = destPos.z - curPos.z;

	
	destPos.x = curPos.x-30000;
	destPos.y = curPos.y+80000;
	destPos.z = curPos.z-30000;

 	Assa = SetAssaEffect(80,"spark01_01.bmp",0,&curPos,0);
	AssaGetAniFileMat(cAssaEffect[Assa]);
	cAssaEffect[Assa]->AniDelayTime = 3;
	cAssaEffect[Assa]->Face.r = 150;
	cAssaEffect[Assa]->Face.g = 255;
	cAssaEffect[Assa]->Face.b = 150;
	cAssaEffect[Assa]->Face.Transparency = 200;
	cAssaEffect[Assa]->Size.w = 5000;
	cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE; 
	
	cAssaEffect[Assa]->ScalePosi.x = destPos.x - curPos.x;
	cAssaEffect[Assa]->ScalePosi.y = destPos.y - curPos.y;
	cAssaEffect[Assa]->ScalePosi.z = destPos.z - curPos.z;

	destPos.x = curPos.x-22000;
	destPos.y = curPos.y+75000;
	destPos.z = curPos.z-22000;

   	Assa = SetAssaEffect(85,"spark01_01.bmp",0,&curPos,0);
	AssaGetAniFileMat(cAssaEffect[Assa]);
	cAssaEffect[Assa]->AniDelayTime = 3;
	cAssaEffect[Assa]->Face.r = 150;
	cAssaEffect[Assa]->Face.g = 255;
	cAssaEffect[Assa]->Face.b = 150;
	cAssaEffect[Assa]->Face.Transparency = 200;
	cAssaEffect[Assa]->Size.w = 5000;
	cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE; 
	
	cAssaEffect[Assa]->ScalePosi.x = destPos.x - curPos.x;
	cAssaEffect[Assa]->ScalePosi.y = destPos.y - curPos.y;
	cAssaEffect[Assa]->ScalePosi.z = destPos.z - curPos.z;

	SetDynLight(pChar->pX, pChar->pY, pChar->pZ, 150,255,150,255,  150, 3);
}

void AssaParticle_SparkShieldEffect(Unit *pChar, int liveCount)
{
	int SkillTime = liveCount*70+140;

	if (AddAssaCodeEffectTime(pChar,SKILL_SPARK_SHIELD,SkillTime) == 0)
	{
		int i = GetAssaEffect();
		AssaSkill3SparkShield *sparkShield = new AssaSkill3SparkShield;
		sparkShield->Start(pChar, liveCount);
		cAssaEffect[i] = sparkShield;
	}
}

void AssaParticle_EnergyShield(Unit *pChar,int liveCount)
{
	//StopAssaCodeEffect(pChar, SKILL_ENERGY_SHIELD);

	int SkillTime = liveCount*70+150;

	if (AddAssaCodeEffectTime(pChar,SKILL_ENERGY_SHIELD,SkillTime) == 0)
	{
		int i = GetAssaEffect();
		AssaSkill3EnergyShield *energyShield = new AssaSkill3EnergyShield;
		energyShield->Start(pChar, liveCount);
		cAssaEffect[i] = energyShield;
	}
}

void AssaParticle_EnergyShieldDefence(Unit *pChar)
{
	int i = GetAssaEffect();
	AssaSkill3EnergyShieldDefence *shieldDefence = new AssaSkill3EnergyShieldDefence;
	shieldDefence->Start(pChar);
	cAssaEffect[i] = shieldDefence;
}

void AssaParticle_SpiritElemental(Unit *pChar, int liveCount)
{
	//StopAssaCodeEffect(pChar, SKILL_SPIRIT_ELEMENTAL);

	int SkillTime = liveCount*70+150;

	if (AddAssaCodeEffectTime(pChar,SKILL_SPIRIT_ELEMENTAL,SkillTime) == 0)
	{
		int i = GetAssaEffect();
		AssaSkill3SpiritElemental *spiritElemental = new AssaSkill3SpiritElemental;
		spiritElemental->Start(pChar, liveCount);
		cAssaEffect[i] = spiritElemental;
	}
}


void AssaParticle_DancingSwordFire(Unit *pChar, int liveCount, int level)
{
	//StopAssaCodeEffect(pChar, SKILL_DANCING_SWORD);

	int SkillTime = liveCount*70+150;

	if (AddAssaCodeEffectTime(pChar,SKILL_DANCING_SWORD,SkillTime) == 0)
	{
		int i = GetAssaEffect();
		AssaSkill3DancingSword * dancingSword = new AssaSkill3DancingSword;
		dancingSword->Start(pChar, 0, liveCount, level);
		cAssaEffect[i] = dancingSword;
	}
}
void AssaParticle_DancingSwordIce(Unit *pChar,int liveCount, int level)
{
	int SkillTime = liveCount*70+150;

	if (AddAssaCodeEffectTime(pChar,SKILL_DANCING_SWORD,SkillTime) == 0)
	{
		int i = GetAssaEffect();
		AssaSkill3DancingSword * dancingSword = new AssaSkill3DancingSword;
		dancingSword->Start(pChar, 1, liveCount, level);
		cAssaEffect[i] = dancingSword;
	}
}
void AssaParticle_DiastrophismPart(Unit *pChar)
{
	POINT3D pos;
	pos.x = pChar->pX;
	pos.y = pChar->pY;
	pos.z = pChar->pZ;

     Assa = SetAssaEffect(100,"Mg3_Dia2.ASE",pChar,&pos,pChar->PatHeight+2000);
  	cAssaEffect[Assa]->AniMaxCount = 20;
	cAssaEffect[Assa]->AniDelayTime = 4;
	cAssaEffect[Assa]->MOVECODE = ASSA_CHAR_POSI;
}

void AssaParticle_Diastrophism(Unit *pChar)
{
	POINT3D charPos;
    charPos.x = pChar->pX;
	charPos.y = pChar->pY;
	charPos.z = pChar->pZ;
	
	SetDynLight( charPos.x, charPos.y, charPos.z,-150, -150, -255, 255, 300, 2);
   	Assa = SetAssaEffect(0,"Mg3_Diastrophism24.ASE",0,&charPos,0, 0);
	cAssaEffect[Assa]->AniMaxCount = 24;
	cAssaEffect[Assa]->AniDelayTime = 3;
  	g_NewParticleMgr.Start("Skill3MagicianDiastrophism1",charPos);

    if(lpCurPlayer == pChar)
   		EffectWaveCamera(160,1);
}

void AssaParticle_HolyIncantationShot(Unit* pDestChar)
{
	int i = GetAssaEffect(); 
	AssaSkill3HolyIncantationShot *incantationShot = new AssaSkill3HolyIncantationShot;
	incantationShot->Start(pDestChar);
	cAssaEffect[i] = incantationShot;
}

void AssaParticle_HolyIncantationPart(Unit* pDestChar, int liveCount)
 {
	StopAssaCodeEffect(pDestChar, SKILL_HOLY_INCANTATION);
	
	int i = GetAssaEffect(); 
	AssaSkill3HolyIncantationPart *incantationPart = new AssaSkill3HolyIncantationPart;
	incantationPart->Start(pDestChar, liveCount);
	cAssaEffect[i] = incantationPart;
}

void AssaParticle_HolyIncantationHand(Unit* pDestChar)
{
 	int i = GetAssaEffect(); 
	AssaSkill3HolyIncantationPartHand *incantationPartHand = new AssaSkill3HolyIncantationPartHand;
	incantationPartHand->Start(pDestChar, 3);
	cAssaEffect[i] = incantationPartHand;
}

void AssaParticle_GrandCrossHorz(POINT3D* pPosi, int angleY)
{
   	SetDynLight( pPosi->x, pPosi->y, pPosi->z, 50, 100, 255, 0, 200, 4);
	pPosi->y += 3000;

 	int partID = g_NewParticleMgr.Start("Skill3Hit4", *pPosi);
	
	POINT3D angle;
 	angle.x = 0;
    	angle.y = angleY;
	angle.z = 0;
    g_NewParticleMgr.SetAngle(partID, angle); 
	
}

void AssaParticle_GrandCrossVert(POINT3D* pPosi, int angleY)
{
	SetDynLight( pPosi->x, pPosi->y, pPosi->z, 50, 100, 255, 0, 200, 4);
	pPosi->y += 4000;
	int partID = g_NewParticleMgr.Start("Skill3Hit5", *pPosi);
	
	POINT3D angle;
	angle.x = 0;
	angle.y = angleY;
	angle.z = 0;

	g_NewParticleMgr.SetAngle(partID, angle); 
	
	pPosi->y += 1000;
	Assa = SetAssaEffect(0,"Nt3_GrandCross20.ASE",0,pPosi,0, 0);
 	cAssaEffect[Assa]->AniMaxCount = 20;
	cAssaEffect[Assa]->AniDelayTime = 3;
 	cAssaEffect[Assa]->Angle.y = (-angleY)&ANGCLIP;
}

void AssaParticle_FlameBrandish(Unit *pChar)
{
	for(int i = 0; i <2 ; i++)
	{    
		Assa = SetAssaEffect(0,"Brabdish.ASE",pChar,0,0);                              
		cAssaEffect[Assa]->AniMaxCount = 20; 
		cAssaEffect[Assa]->AniDelayTime = 2;
		cAssaEffect[Assa]->StartPosi.x = 256*8*6;
		cAssaEffect[Assa]->Angle.y =  ((pChar->Angle.y&ANGCLIP)+ANGLE_270)&ANGCLIP;
		AssaSetStartPosi(cAssaEffect[Assa]);
		cAssaEffect[Assa]->Angle.y =  -((pChar->Angle.y&ANGCLIP))&ANGCLIP;
		//AssaParticle_SpecialHit2(&cAssaEffect[Assa]->Posi,0);
	}

	POINT3D partPos;
  	partPos.x = cAssaEffect[Assa]->Posi.x;
	partPos.y = cAssaEffect[Assa]->Posi.y+2000;
	partPos.z = cAssaEffect[Assa]->Posi.z;
  	g_NewParticleMgr.Start("Skill3KnightFlameBrandish1",partPos, 0.1f);

	SetDynLight( cAssaEffect[Assa]->Posi.x , cAssaEffect[Assa]->Posi.y , cAssaEffect[Assa]->Posi.z ,255, 120, 0, 255, 200 ,1);
	
    int t = GetAssaEffect(); 
	AssaSkill3FlameBrandish *flameBrandish = new AssaSkill3FlameBrandish;
	flameBrandish->Start(pChar);
	cAssaEffect[t] = flameBrandish;
}


void AssaParticle_FlameBrandishHit1(Unit *pChar)
{
	POINT3D pos;
	pos.x = pChar->pX;
	pos.y = pChar->pY;
	pos.z = pChar->pZ;

	AssaParticle_FireHit2(&pos);
}

void AssaParticle_DivineInhalationStart(Unit* pChar)
{
 	StopAssaCodeEffect(pChar, SKILL_DIVINE_INHALATION);

	POINT3D pos;
	POINT3D curPos;
	POINT3D rand;
	if(pChar->AnimPattern)
	{
		smOBJ3D *searchObj = pChar->AnimPattern->GetObjectFromName("Bip01 L Hand");
		smMATRIX *mWorld;
		AnimObjectTree( searchObj, pChar->iFrame, 0, (-pChar->Angle.y+ANGLE_180)&ANGCLIP, 0);
		mWorld = &searchObj->mWorld;


		pos.x = pChar->pX+mWorld->_41;
		pos.y = pChar->pY+mWorld->_43;
		pos.z = pChar->pZ+mWorld->_42;
	}
	else
	{
		pos.x = pChar->pX;
		pos.y = pChar->pY+10000;
		pos.z = pChar->pZ;
	}
	SetDynLight( pos.x, pos.y, pos.z, 50, 100, 255, 0, 250, 2);

	for(int index = 0; index < 30; index++)
	{
		rand.x = GetRandomPos(-100, 100);
		rand.y = GetRandomPos(-100, 100);
		rand.z = GetRandomPos(-100, 100);

		double length = sqrt((float)rand.x*(float)rand.x+(float)rand.y*(float)rand.y+(float)rand.z*(float)rand.z);

		if(length == 0)
			length = 1;

		int range = GetRandomPos(5000,7000);
		curPos.x = int(float(rand.x)/length*(float)range+(float)pos.x);
		curPos.y = int(float(rand.y)/length*(float)range+(float)pos.y);
		curPos.z = int(float(rand.z)/length*(float)range+(float)pos.z);

		Assa = SetAssaEffect(130+index,"flare.bmp",0,&curPos,0);                

		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE;
		cAssaEffect[Assa]->Time = -(index/2);

		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE;
		cAssaEffect[Assa]->MoveSpeed.x = int(float(rand.x)/length*(150.f));
		cAssaEffect[Assa]->MoveSpeed.y = int(float(rand.y)/length*(150.f));
		cAssaEffect[Assa]->MoveSpeed.z = int(float(rand.z)/length*(150.f));

		cAssaEffect[Assa]->Size.w = 500;
		cAssaEffect[Assa]->Face.r = 100;
		cAssaEffect[Assa]->Face.g = 255;
		cAssaEffect[Assa]->Face.b = 255;
		cAssaEffect[Assa]->Face.Transparency = 255;

		POINT3D destPos;
		destPos.x = int(float(rand.x)/length*12000.f);
		destPos.y = int(float(rand.y)/length*12000.f);
		destPos.z = int(float(rand.z)/length*12000.f);

		cAssaEffect[Assa]->ScalePosi.x = -destPos.x;
		cAssaEffect[Assa]->ScalePosi.y = -destPos.y;
		cAssaEffect[Assa]->ScalePosi.z = -destPos.z;
	}

	g_NewParticleMgr.Start("Skill3KnightDivineInhalation1", pos);
}

void SkillSaintGodlyShieldStart(Unit *pChar)
{
	StopAssaCodeEffect(pChar,SKILL_GODLY_SHIELD);

	POINT3D pos;
	POINT3D curPos;
	POINT3D rand;
 	if(pChar->AnimPattern)
	{
		smOBJ3D *searchObj = pChar->AnimPattern->GetObjectFromName("Bip01 L Hand");
		smMATRIX *mWorld;
		AnimObjectTree( searchObj, pChar->iFrame, 0, (-pChar->Angle.y+ANGLE_180)&ANGCLIP, 0);
		mWorld = &searchObj->mWorld;
		
		
		pos.x = pChar->pX+mWorld->_41;
		pos.y = pChar->pY+mWorld->_43;
		pos.z = pChar->pZ+mWorld->_42;
	}
	else
	{
		pos.x = pChar->pX;
		pos.y = pChar->pY+10000;
		pos.z = pChar->pZ;
	}
   	SetDynLight( pos.x, pos.y, pos.z, 50, 100, 255, 0, 250, 2);

   	for(int index = 0; index < 30; index++)
	{
   		rand.x = GetRandomPos(-100, 100);
		rand.y = GetRandomPos(-100, 100);
		rand.z = GetRandomPos(-100, 100);
		
		double length = sqrt((float)rand.x*(float)rand.x+(float)rand.y*(float)rand.y+(float)rand.z*(float)rand.z);
		
		if(length == 0)
			length = 1;
		
  		int range = GetRandomPos(5000,7000);
     	curPos.x = int(float(rand.x)/length*(float)range+(float)pos.x);
		curPos.y = int(float(rand.y)/length*(float)range+(float)pos.y);
 		curPos.z = int(float(rand.z)/length*(float)range+(float)pos.z);
		
   		Assa = SetAssaEffect(130+index,"flare.bmp",0,&curPos,0);                
		
  		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE;
   		cAssaEffect[Assa]->Time = -(index/2);
		
    	cAssaEffect[Assa]->MOVECODE = ASSA_MOVE;
  		cAssaEffect[Assa]->MoveSpeed.x = int(float(rand.x)/length*(150.f));
		cAssaEffect[Assa]->MoveSpeed.y = int(float(rand.y)/length*(150.f));
		cAssaEffect[Assa]->MoveSpeed.z = int(float(rand.z)/length*(150.f));
		
    	cAssaEffect[Assa]->Size.w = 500;
		cAssaEffect[Assa]->Face.r = 100;
		cAssaEffect[Assa]->Face.g = 255;
		cAssaEffect[Assa]->Face.b = 255;
		cAssaEffect[Assa]->Face.Transparency = 255;

		POINT3D destPos;
   		destPos.x = int(float(rand.x)/length*12000.f);
		destPos.y = int(float(rand.y)/length*12000.f);
		destPos.z = int(float(rand.z)/length*12000.f);
		
		cAssaEffect[Assa]->ScalePosi.x = -destPos.x;
		cAssaEffect[Assa]->ScalePosi.y = -destPos.y;
		cAssaEffect[Assa]->ScalePosi.z = -destPos.z;
	}
	
   	g_NewParticleMgr.Start("Skill3KnightDivineInhalation1", pos);
}

void AssaParticle_DivineInhalationPart(Unit* pChar, int liveCount)
{
	int SkillTime = liveCount*70+140;

	if (AddAssaCodeEffectTime(pChar,SKILL_DIVINE_INHALATION,SkillTime) == 0)
	{
		int i = GetAssaEffect(); 
		AssaSkill3DivineInhalation *divineInhalation = new AssaSkill3DivineInhalation;
		divineInhalation->Start(pChar, liveCount);
		cAssaEffect[i] = divineInhalation;
	}
}


void AssaParticle_DivineInhalationDefence(POINT3D *pDest)
{
	StartEffect( pDest->x, pDest->y, pDest->z, EFFECT_PHYSICAL_ABSORB_DAMAGE );
}

void AssaParticle_VigorBall(Unit* pCurChar, Unit* pDestChar)
{
	POINT3D curPos;
   	curPos.x = pCurChar->pX;
	curPos.y = pCurChar->pY+5000;
	curPos.z = pCurChar->pZ;

	D3DVECTOR velocity;
	memset(&velocity, 0, sizeof(velocity));

	int motionEvent = pCurChar->MotionEvent;
	int i  = 0;
	if(motionEvent == 1)
	{
 		i = GetAssaEffect(); 
		AssaSkill3VigorBall *vigorBall = new AssaSkill3VigorBall;
		
		velocity.x = 0.f;
		velocity.y = 0.f;
		velocity.z = 0.f;

		auto sPosition = GetMoveLocation(0, 0, 3 * fONE + rand() % (2 * fONE) - fONE, 0, pCurChar->Angle.y - ANGLE_45, 0);
		velocity.x += ((float)sPosition.iX*2.f / 256.f);
		velocity.z += ((float)sPosition.iZ*2.f / 256.f);
		vigorBall->Start(&curPos, pDestChar, &velocity, 0);
		cAssaEffect[i] = vigorBall;
	}
	else
	{
		i = GetAssaEffect(); 
		AssaSkill3VigorBall *vigorBall = new AssaSkill3VigorBall;
	
		velocity.x = 0.f;
		velocity.y = 0.f;
		velocity.z = 0.f;

		auto sPosition = GetMoveLocation(0, 0, 3 * fONE + rand() % (2 * fONE) - fONE, 0, pCurChar->Angle.y + ANGLE_45, 0);
		velocity.x += ((float)sPosition.iX*2.f / 256.f);
		velocity.z += ((float)sPosition.iZ*2.f / 256.f);
		vigorBall->Start(&curPos, pDestChar, &velocity, 0);
		cAssaEffect[i] = vigorBall;
	}

}

void AssaParticle_Extinction(Unit* pDestChar)
{
	int i = GetAssaEffect(); 
	AssaSkill3Extinction *extinction = new AssaSkill3Extinction;
	extinction->Start(pDestChar);
	cAssaEffect[i] = extinction;
}
void AssaParticle_VirtualLifeStart(Unit *pDestChar)
{
	POINT3D charPos;
	charPos.x = pDestChar->pX;
	charPos.y = pDestChar->pY;
	charPos.z = pDestChar->pZ;

	Assa = SetAssaEffect(0,"Pt3_VirtualLife20.ASE",0,&charPos,0, 0);

	if (Assa < cASSAEFFECT_MAX)
	{
		cAssaEffect[Assa]->Time				= -60;
		cAssaEffect[Assa]->AniMaxCount		= 20;
		cAssaEffect[Assa]->AniDelayTime		= 6;
		cAssaEffect[Assa]->MOVECODE			= ASSA_CHAR_POSI;
		cAssaEffect[Assa]->pChar			= pDestChar;

		cAssaEffect[Assa]->Temp[8]			= 1;
		cAssaEffect[Assa]->TempPosi.x		= 0;
		cAssaEffect[Assa]->TempPosi.y		= 1000;
		cAssaEffect[Assa]->TempPosi.z		= 0;
	}
}
void AssaParticle_VirtualLifeEffect(Unit* pDestChar,int liveCount)
{
	if (AddAssaCodeEffectTime(pDestChar, SKILL_VIRTUAL_LIFE, liveCount*70+140) == false)
	{
		int i = GetAssaEffect(); 
		AssaSkillVirtualLifeMember *virtualLifeMember = new AssaSkillVirtualLifeMember;
		virtualLifeMember->Start(pDestChar, liveCount);
		cAssaEffect[i] = virtualLifeMember;
	}
}

void AssaParticle_ResurrectionShot(Unit* pDestChar)
{
	int i = GetAssaEffect(); 
	AssaSkill3ResurrectionShot *ressurectionShot = new AssaSkill3ResurrectionShot;
	ressurectionShot->Start(pDestChar, 65);
	cAssaEffect[i] = ressurectionShot;
}

void AssaParticle_ResurrectionPart(Unit* pDestChar)
{
	int i = GetAssaEffect(); 
	AssaSkill3ResurrectionPart *resurrectionPart = new AssaSkill3ResurrectionPart;
	resurrectionPart->Start(pDestChar, 10);
	cAssaEffect[i] = resurrectionPart;
}


void AssaParticle_LightingJavelin(POINT3D* pCur, POINT3D* pDest)
{
	int i = GetAssaEffect(); 
	AssaSkill3LightingJavelin *lightingJavelin = new AssaSkill3LightingJavelin;
	lightingJavelin->Start(pCur, pDest);
	cAssaEffect[i] = lightingJavelin;
}

void AssaParticle_StormJavelin(POINT3D* pCur, POINT3D* pDest)
{
	int i = GetAssaEffect(); 
	AssaSkill3StormJavelin *stormJavelin = new AssaSkill3StormJavelin;
	stormJavelin->Start(pCur, pDest);
	cAssaEffect[i] = stormJavelin;
}

void AssaParticle_StormJavelinHit(Unit* monster, Unit* character, float delay)
{
	POINT3D pos;
 	pos.x = monster->pX;
	pos.y = monster->pY+2000;
	pos.z = monster->pZ;

	int num = -1;
	if(delay == 0.f)
		num = g_NewParticleMgr.Start("TwistJavelin2", pos, 0.f);
	else
		num = g_NewParticleMgr.Start("TwistJavelin2", pos, delay);

	POINT3D angle;
	angle.x = 0;
	angle.y = character->Angle.y;
	angle.z = 0;
    g_NewParticleMgr.SetAngle(num, angle);

}

void AssaParticle_TriumphOfValhalla(Unit *pDestChar, int liveCount)
{
	//StopAssaCodeEffect(pDestChar, SKILL_TRIUMPH_OF_VALHALLA);

	int SkillTime = liveCount * 70 + 150;

	if (AddAssaCodeEffectTime(pDestChar,SKILL_TRIUMPH_OF_VALHALLA,SkillTime) == 0)
	{
		int i = GetAssaEffect(); 
		AssaSkillTriumphOfValhallaPart *triumphOfValhallaPart = new AssaSkillTriumphOfValhallaPart;
		triumphOfValhallaPart->Start(pDestChar, liveCount);
		cAssaEffect[i] = triumphOfValhallaPart;
	}
}

void AssaParticle_TriumphOfValhallaMember(Unit *pCurChar, Unit *pDestChar, int liveCount)
{
	int i = GetAssaEffect(); 
	AssaSkillTriumphOfValhallaShot *triumphOfValhallaShot = new AssaSkillTriumphOfValhallaShot;
	
	D3DVECTOR velocity;
	velocity.x = 0.f;
	velocity.y = 7.0f;
	velocity.z = 0.f;
	triumphOfValhallaShot->Start(pCurChar, pDestChar, &velocity, liveCount);
	
	cAssaEffect[i] = triumphOfValhallaShot;
}

void SkillValhallaHallOfValhallaHandEffect(Unit *pChar, float time)
{
	if(!AddAssaCodeEffectTime(pChar, SKILL_HALL_OF_VALHALLA, (int)(time*70.f)))
	{
		int i = GetAssaEffect();
		AssaSkillTriumphOfValhallaPart *triumphOfValhallaPart = new AssaSkillTriumphOfValhallaPart;
		triumphOfValhallaPart->StartHallOfValhalla(pChar, int(time));
		cAssaEffect[i] = triumphOfValhallaPart;
	}
}

//count; È­»ìÀÇ °¹¼ö
void AssaParticle_SplitJavelin(POINT3D* pCur, POINT3D* pDest, int count)
{
  	for(int index = 0; index < count; index++)
	{
		POINT3D worldPos;
		auto sPosition = GetMoveLocation(0, 5 * fONE, 0, 0, 0, ANGLE_360 / count * index);
		memcpy(&worldPos, pCur, sizeof(POINT3D));
		worldPos.x += sPosition.iX;
		worldPos.y += sPosition.iY;
		worldPos.z += sPosition.iZ;

		pDest->x += sPosition.iX;
		pDest->y += sPosition.iY;
		pDest->z += sPosition.iZ;

		int i = GetAssaEffect(); 
  		AssaSkill3SplitJavelin *splitJavelin = new AssaSkill3SplitJavelin;
 		splitJavelin->Start(&worldPos, pDest, index*10);
 		cAssaEffect[i] = splitJavelin;
	}
}

void AssaParticle_MonsterPigonHand(Unit* pChar)
{
	if(GetAssaCodeEffect(pChar, PIGON_HAND_FIRE) == FALSE)
	{
  		int i = GetAssaEffect();
		cAssaTraceCharMeshParticle *traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pChar, "Bip01 L Finger1", "MonsterPigonFire1", FALSE);
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = PIGON_HAND_FIRE;
		

 		i = GetAssaEffect();
		traceMeshParticle = NULL;
		traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pChar, "Bip01 R Finger1", "MonsterPigonFire1", FALSE);
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = PIGON_HAND_FIRE;
		
		i = GetAssaEffect();
		traceMeshParticle = NULL;
		traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pChar, "Bip01 Tail", "MonsterPigonFireTail", FALSE);
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = PIGON_HAND_FIRE;
	}
}
int AssaParticle_StopElementUpWeapon(Unit *pChar,int Kind,int Hand)
{
	int Result = FALSE;
	for (int i =0; i < cASSAEFFECT_MAX; i ++)
	{
		if (cAssaEffect[i])
		{
			if (cAssaEffect[i]->CODE == EFFECT_ELEMENT)
			{
				if (cAssaEffect[i]->pChar == pChar)
				{
					if (pChar->dwActionItemTwoHand)
					{
						if (cAssaEffect[i]->Type == Kind)
							Result = TRUE;
						else
							cAssaEffect[i]->Time = cAssaEffect[i]->Max_Time;
					}
					else
					{
						if (cAssaEffect[i]->Hand == Hand)
						{
							if (cAssaEffect[i]->Type == Kind)
								Result = TRUE;
							else
								cAssaEffect[i]->Time = cAssaEffect[i]->Max_Time;
						}
					}
				}
			}
		}
	}
	return Result;
}
void AssaParticle_ElementWeapon(Unit *pChar,int Kind,int Hand)
{
	if (AssaParticle_StopElementUpWeapon(pChar,Kind,Hand) == TRUE)
		return;

	if ((pChar->HvRightHand.dwItemCode && pChar->HvRightHand.ElementEffect) || (pChar->HvLeftHand.dwItemCode && pChar->HvLeftHand.ElementEffect))
	{
		int i = GetAssaEffect();
		AssaElementWeapon *classElementWeapon = new AssaElementWeapon;
		classElementWeapon->Start(pChar,Kind,Hand);
		cAssaEffect[i] = classElementWeapon;
	}
}
void AssaParticle_ElementHit(Unit *pChar,int Kind,POINT3D *pos)
{
	switch(Kind)
	{
	case 1:
		AssaParticle_FireHit1(pos);
		SetDynLight(pos->x,pos->y,pos->z,100,0,0,0,200,10);
		if ((rand()%2)==0) 
			SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_FIRE1,pChar->pX,pChar->pY,pChar->pZ);
		else
			SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_FIRE2,pChar->pX,pChar->pY,pChar->pZ);
		break;
	case 2:
		AssaParticle_IceHit1(pos);
		SetDynLight(pos->x,pos->y,pos->z,0,0,100,0,200,10);
		if ((rand()%2)==0)
			SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_ICE1,pChar->pX,pChar->pY,pChar->pZ);
		else
			SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_ICE1,pChar->pX,pChar->pY,pChar->pZ);
		break;
	case 3:
		AssaParticle_LightHit1(pos);
		SetDynLight(pos->x,pos->y,pos->z,0,0,100,0,200,10);
		if ((rand()%2)==0)
			SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_LIGHTNING1,pChar->pX,pChar->pY,pChar->pZ);
		else
			SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_LIGHTNING2,pChar->pX,pChar->pY,pChar->pZ);
		break;
	}
}
void AssaParticle_ClassUpWeapon(Unit* pChar)
{
	if(GetAssaCodeEffect(pChar,CLASS_UP_PART1) == FALSE)
	{
		if( (pChar->HvRightHand.dwItemCode && pChar->HvRightHand.ColorEffect == 1) || (pChar->HvLeftHand.dwItemCode  && pChar->HvLeftHand.ColorEffect == 1))
		{
			int i = GetAssaEffect();
  			AssaClassUpWeapon *classUpWeapon = new AssaClassUpWeapon;
 			classUpWeapon->Start(pChar);
 			cAssaEffect[i] = classUpWeapon;
		}
	}
}

void AssaParticle_StopClassUpWeapon(Unit* pChar)
{
	for(int i = 0; i < cASSAEFFECT_MAX; i++)
	{
		if(cAssaEffect[i])
		{
			if(cAssaEffect[i]->CODE == CLASS_UP_PART1)
			{
				if(cAssaEffect[i]->pChar == pChar)
					cAssaEffect[i]->Type = STOP_PART_FLAG;
			}
		}
   	}
}

void AssaParticle_AgingBody(Unit* pChar, int num)
{
	if(num < 4 || num > 11)
		return;
	int i = GetAssaEffect();
	cAssaTraceCharMeshParticle *traceMeshParticle = new cAssaTraceCharMeshParticle;
	char nameBuffer[64];
	wsprintf(nameBuffer, "%s%d", "AgingBody", num);
	traceMeshParticle->Start(pChar, "Bip01 Spine1", nameBuffer);
	cAssaEffect[i] = traceMeshParticle;
}


void AssaParticle_MonsterIronSadNessHit1(Unit *pChar)
{
	Point3D sPosition;

	sPosition = GetMoveLocation(0, 0, 30 * fONE, 0, pChar->Angle.y - ANGLE_45, 0);
	
	int num = -1;
 	POINT3D pos;
	pos.x = pChar->pX + sPosition.iX;
	pos.y = pChar->pY + 10000;
	pos.z = pChar->pZ + sPosition.iZ;
	
	sPosition = GetMoveLocation(0, 0, 30 * fONE, 0, pChar->Angle.y, 0);

	D3DVECTOR  velocity;
	D3DVECTOR  gravity;
   	int i = GetAssaEffect(); 
	velocity.x = float((float)sPosition.iX / 15.f);
	velocity.y = 0.f;
	velocity.z = float((float)sPosition.iZ / 15.f);

  	gravity.x = 0.f;
 	gravity.y = 0.f;
	gravity.z = 0.f;
	
	AssaSkill3BombShotExplision *explision = new AssaSkill3BombShotExplision;
	explision->Start(&pos, &velocity, &gravity, "IronMonsterBombHit2");
	cAssaEffect[i] = explision;
	
	num = g_NewParticleMgr.Start("MonsterIron1", pos);
	if(num != -1)
	{
		POINT3D angle;
		angle.x = 0;
		angle.y = pChar->Angle.y;
		angle.z = 0;
		g_NewParticleMgr.SetAngle(num, angle);
	}
	num = -1;
	
	sPosition = GetMoveLocation(0, 0, 30 * fONE, 0, pChar->Angle.y + ANGLE_45, 0);
	pos.x = pChar->pX + sPosition.iX;
	pos.y = pChar->pY + 10000;
	pos.z = pChar->pZ + sPosition.iZ;
	
	sPosition = GetMoveLocation(0, 0, 30 * fONE, 0, pChar->Angle.y, 0);
	
	i = GetAssaEffect(); 
	velocity.x = float((float)sPosition.iX / 15.f);
	velocity.y = 0.f;
	velocity.z = float((float)sPosition.iZ / 15.f);

  	gravity.x = 0.f;
 	gravity.y = 0.f;
	gravity.z = 0.f;
	
	explision = new AssaSkill3BombShotExplision;
	explision->Start(&pos, &velocity, &gravity, "IronMonsterBombHit2");
	cAssaEffect[i] = explision;
	
	num = g_NewParticleMgr.Start("MonsterIron1", pos);
	if(num != -1)
	{
		POINT3D angle;
		angle.x = 0;
		angle.y = pChar->Angle.y;
		angle.z = 0;
		g_NewParticleMgr.SetAngle(num, angle);
	}
}
void AssParticle_AdvEffect(Unit *pChar)
{
	if (GetAssaCodeEffect(pChar,CLASS_LEVEL_EFFECT) == FALSE)
	{
		int i = GetAssaEffect();
		AssaLevelEffect *Motion = new AssaLevelEffect;
		Motion->Start(pChar);
		cAssaEffect[i] = Motion;
	}
}
void AssaParticle_MonsterIronSadNessSkill1(Unit *pChar)
{
	Point3D sPosition;

	sPosition = GetMoveLocation(0, 0, 0, 0, 0, 0);
	
 	int num = -1;
 	POINT3D pos;
	pos.x = pChar->pX + sPosition.iX;
	pos.y = pChar->pY + 10000;
	pos.z = pChar->pZ + sPosition.iZ;
	
	sPosition = GetMoveLocation(0, 0, 30 * fONE, 0, pChar->Angle.y, 0);
	
	D3DVECTOR  velocity;
	D3DVECTOR  gravity;
   	int i = GetAssaEffect(); 
	velocity.x = float((float)sPosition.iX / 8.f);
	velocity.y = 0.f;
	velocity.z = float((float)sPosition.iZ / 8.f);

  	gravity.x = 0.f;
 	gravity.y = 0.f;
	gravity.z = 0.f;
	
 	AssaSkill3BombShotExplision *explision = new AssaSkill3BombShotExplision;
	explision->Start(&pos, &velocity,&gravity,"IronMonsterSadnessShot");
	cAssaEffect[i] = explision;
}

void SkillArchMageFlameWave(Unit *pChar)
{
	Point3D sPosition;

 	int factor = ANGLE_45+ANGLE_45/3;

	int num = -1;
	sPosition = GetMoveLocation(0, 0, 30 * fONE, 0, pChar->Angle.y, 0);

  	POINT3D pos;
	pos.x = pChar->pX + sPosition.iX;
	pos.y = pChar->pY + 10000;
	pos.z = pChar->pZ + sPosition.iZ;
	
	sPosition = GetMoveLocation(0, 0, 30 * fONE, 0, pChar->Angle.y - factor / 2, 0);
	
	D3DVECTOR  velocity;
	D3DVECTOR  gravity;
   	int i = GetAssaEffect(); 
	velocity.x = float((float)sPosition.iX / 6.f);
	velocity.y = 0.f;
	velocity.z = float((float)sPosition.iZ / 6.f);

  	gravity.x = 0.f;
 	gravity.y = 0.f;
	gravity.z = 0.f;
	
 	AssaSkill3BombShotExplision *explision = new AssaSkill3BombShotExplision;
	explision->Start(&pos, &velocity, &gravity, "IronMonsterSadnessShot");
	cAssaEffect[i] = explision;
	
	sPosition = GetMoveLocation(0, 0, 30 * fONE, 0, pChar->Angle.y - factor / 3, 0);
	i = GetAssaEffect(); 
	velocity.x = float((float)sPosition.iX / 6.f);
	velocity.y = 0.f;
	velocity.z = float((float)sPosition.iZ / 6.f);

  	gravity.x = 0.f;
 	gravity.y = 0.f;
	gravity.z = 0.f;
	
 	explision = new AssaSkill3BombShotExplision;
	explision->Start(&pos, &velocity, &gravity, "IronMonsterSadnessShot");
	cAssaEffect[i] = explision;

	sPosition = GetMoveLocation(0, 0, 30 * fONE, 0, pChar->Angle.y, 0);
	i = GetAssaEffect(); 
	velocity.x = float((float)sPosition.iX / 6.f);
	velocity.y = 0.f;
	velocity.z = float((float)sPosition.iZ / 6.f);

  	gravity.x = 0.f;
 	gravity.y = 0.f;
	gravity.z = 0.f;
	
 	explision = new AssaSkill3BombShotExplision;
	explision->Start(&pos, &velocity, &gravity, "IronMonsterSadnessShot");
	cAssaEffect[i] = explision;

	sPosition = GetMoveLocation(0, 0, 30 * fONE, 0, pChar->Angle.y + factor / 2, 0);
	i = GetAssaEffect(); 
	velocity.x = float((float)sPosition.iX / 6.f);
	velocity.y = 0.f;
	velocity.z = float((float)sPosition.iZ / 6.f);

  	gravity.x = 0.f;
 	gravity.y = 0.f;
	gravity.z = 0.f;
	
 	explision = new AssaSkill3BombShotExplision;
	explision->Start(&pos, &velocity, &gravity, "IronMonsterSadnessShot");
	cAssaEffect[i] = explision;

	sPosition = GetMoveLocation(0, 0, 30 * fONE, 0, pChar->Angle.y + factor / 3, 0);
	i = GetAssaEffect(); 
	velocity.x = float((float)sPosition.iX / 6.f);
	velocity.y = 0.f;
	velocity.z = float((float)sPosition.iZ / 6.f);

  	gravity.x = 0.f;
 	gravity.y = 0.f;
	gravity.z = 0.f;
	
 	explision = new AssaSkill3BombShotExplision;
	explision->Start(&pos, &velocity, &gravity, "IronMonsterSadnessShot");
	cAssaEffect[i] = explision;
}

void AssaParticle_MonsterIronHyperHit1(Unit *pChar, POINT3D* pDest)
{
    auto sPosition = GetMoveLocation(0, 0, 50*fONE, 0, pChar->Angle.y, 0);

	POINT3D pos;
	pos.x = pChar->pX + sPosition.iX;
	pos.y = pChar->pY + 12000;
	pos.z = pChar->pZ + sPosition.iZ;

 	StartEffectMonsterDest(pos.x, pos.y, pos.z, pDest->x, pDest->y, pDest->z, MONSTER_DMACHINE_MISSILE1);
}

void AssaParticle_MonsterIronHyperSkill1(Unit *pChar, POINT3D* pDest)
{
	auto sPosition = GetMoveLocation(0, 0, 50 * fONE, 0, pChar->Angle.y, 0);

	POINT3D pos;
	pos.x = pChar->pX + sPosition.iX;
	pos.y = pChar->pY + 12000;
	pos.z = pChar->pZ + sPosition.iZ;

 	StartEffectMonsterDest(pos.x, pos.y, pos.z, pDest->x, pDest->y, pDest->z, MONSTER_DMACHINE_MISSILE1);
}

//////////////////////////////////////////////////////////////////////////////

void ParkKelvezuHit(Unit *pChar)		// ÄÌº£Áê °ø°Ý½Ã Ä³¸¯ÅÍ ÇÇ°ÝÀÌÆåÆ® (¹øÂ½ÀÌ´Â)
{
 	POINT3D pos;
	auto sPosition = GetMoveLocation(0, 0, 0, 0, pChar->Angle.y, 0);

	pos.x = pChar->pX + sPosition.iX;
	pos.y = pChar->pY + 7000;
	pos.z = pChar->pZ + sPosition.iZ;
	
 	g_NewParticleMgr.Start("IceKelvezuHit", pos);
}

void ParkKelvezuSkillHit(Unit *pChar)	// ÄÌº£Áê °ø°Ý½Ã Ä³¸¯ÅÍ ÇÇ°ÝÀÌÆåÆ®
{
	POINT3D pos;

	auto sPosition = GetMoveLocation(0, 0, 0, 0, pChar->Angle.y, 0);

	pos.x = pChar->pX + sPosition.iX;
	pos.y = pChar->pY + 1000;
	pos.z = pChar->pZ + sPosition.iZ;
	
 	g_NewParticleMgr.Start("IceKelvezuNormal2", pos);
}

void ParkKelvezuNormal1(Unit *pChar)	// ÄÌº£Áê ³ë¸»°ø°Ý1 »ç¿ë½Ã Ä³¸¯ÅÍ ÇÇ°ÝÀÌÆåÆ®
{
 	POINT3D pos;
	auto sPosition = GetMoveLocation(0, 0, 0, 0, pChar->Angle.y, 0);

	pos.x = pChar->pX + sPosition.iX;
	pos.y = pChar->pY + 1000;
	pos.z = pChar->pZ + sPosition.iZ;
	
 	g_NewParticleMgr.Start("IceKelvezuNormal1", pos);
}

void ParkKelvezuNormal2(Unit *pKelvezu)	// ÄÌº£Áê ³ë¸»°ø°Ý2 »ç¿ë½Ã Ä³¸¯ÅÍ ÇÇ°ÝÀÌÆåÆ®
{
 	POINT3D pos;

 	pos.x = pKelvezu->pX;
	pos.y = pKelvezu->pY;
	pos.z = pKelvezu->pZ;
  
	auto sPosition = GetMoveLocation(10 * fONE, 0, 250 * fONE, pKelvezu->Angle.x, pKelvezu->Angle.y, 1);
	pos.x += sPosition.iX;
	pos.z += sPosition.iZ;
	pos.y += sPosition.iY;
	
  	Assa = SetAssaEffect(0,"m_ratoo.ASE",0,&pos,0);
	cAssaEffect[Assa]->Time = -4;
	cAssaEffect[Assa]->AniMaxCount = 20;
	cAssaEffect[Assa]->AniDelayTime = 5;
	cAssaEffect[Assa]->Angle.y = (-pKelvezu->Angle.y+ANGLE_180)&ANGCLIP;

	POINT3D partPos;
  	partPos.x = cAssaEffect[Assa]->Posi.x;
	partPos.y = cAssaEffect[Assa]->Posi.y+2000;
	partPos.z = cAssaEffect[Assa]->Posi.z;
	g_NewParticleMgr.Start("IceKelvezuNormal3",partPos);

	//sinSkillEffect_Brandish(pChar);
}

void ParkKelvezuSkill1(Unit *pKelvezu)	// ÄÌº£Áê ½ºÅ³°ø°Ý1 »ç¿ë½Ã Ä³¸¯ÅÍ ÇÇ°ÝÀÌÆåÆ®
{
 	int factor = ANGLE_45+ANGLE_45/3;

	float fVelocity = 0.2f;

	int num = -1;
	auto sPosition = GetMoveLocation(0, 0, 160 * fONE, pKelvezu->Angle.x, pKelvezu->Angle.y, 1);

  	POINT3D pos;
	pos.x = pKelvezu->pX + sPosition.iX;
	pos.y = pKelvezu->pY + 23000;
	pos.z = pKelvezu->pZ + sPosition.iZ;
	
	sPosition = GetMoveLocation(0, 0, fONE, 0, pKelvezu->Angle.y - factor, 1);
	//Å×½ºÆ®¿ë.
	D3DVECTOR  velocity;
	D3DVECTOR  gravity;
   	int i = GetAssaEffect(); 
	velocity.x = float((float)sPosition.iX / fVelocity);
	velocity.y = -1000;
	velocity.z = float((float)sPosition.iZ / fVelocity);

  	gravity.x = 0;
 	gravity.y = 0;
	gravity.z = 0;
	
 	AssaSkill3BombShotExplision *explision = new AssaSkill3BombShotExplision;
	explision->Start(&pos, &velocity, &gravity, "IronMonsterSadnessShot");
	cAssaEffect[i] = explision;
	cAssaEffect[i]->Gravity = 10000;

	sPosition = GetMoveLocation(0, 0, fONE, 0, pKelvezu->Angle.y - factor / 2, 1);
   	i = GetAssaEffect(); 
	velocity.x = float((float)sPosition.iX / fVelocity);
	velocity.y = -1000;
	velocity.z = float((float)sPosition.iZ / fVelocity);

  	gravity.x = 0;
 	gravity.y = 0;
	gravity.z = 0;
	
 	explision = new AssaSkill3BombShotExplision;
	explision->Start(&pos, &velocity, &gravity, "IronMonsterSadnessShot");
	cAssaEffect[i] = explision;
	cAssaEffect[i]->Gravity = 10000;
	
	sPosition = GetMoveLocation(0, 0, fONE, 0, pKelvezu->Angle.y - factor / 3, 1);
	i = GetAssaEffect(); 
	velocity.x = float((float)sPosition.iX / fVelocity);
	velocity.y = -1000;
	velocity.z = float((float)sPosition.iZ / fVelocity);

  	gravity.x = 0;
 	gravity.y = 0;
	gravity.z = 0;
	
 	explision = new AssaSkill3BombShotExplision;
	explision->Start(&pos, &velocity, &gravity, "IronMonsterSadnessShot");
	cAssaEffect[i] = explision;
	cAssaEffect[i]->Gravity = 10000;

	sPosition = GetMoveLocation(0, 0, fONE, 0, pKelvezu->Angle.y, 1);
	i = GetAssaEffect(); 
	velocity.x = float((float)sPosition.iX / fVelocity);
	velocity.y = -1000.f;
	velocity.z = float((float)sPosition.iZ / fVelocity);

  	gravity.x = 0.f;
 	gravity.y = 0.f;
	gravity.z = 0.f;
	
 	explision = new AssaSkill3BombShotExplision;
	explision->Start(&pos, &velocity, &gravity, "IronMonsterSadnessShot");
	cAssaEffect[i] = explision;
	cAssaEffect[i]->Gravity = 10000;

	sPosition = GetMoveLocation(0, 0, fONE, 0, pKelvezu->Angle.y + factor / 2, 1);
	i = GetAssaEffect(); 
	velocity.x = float((float)sPosition.iX / fVelocity);
	velocity.y = -1000.f;
	velocity.z = float((float)sPosition.iZ / fVelocity);

  	gravity.x = 0.f;
 	gravity.y = 0.f;
	gravity.z = 0.f;
	
 	explision = new AssaSkill3BombShotExplision;
	explision->Start(&pos, &velocity, &gravity, "IronMonsterSadnessShot");
	cAssaEffect[i] = explision;
	cAssaEffect[i]->Gravity = 10000;

	sPosition = GetMoveLocation(0, 0, fONE, 0, pKelvezu->Angle.y + factor / 3, 1);
	i = GetAssaEffect(); 
	velocity.x = float((float)sPosition.iX / fVelocity);
	velocity.y = -1000.f;
	velocity.z = float((float)sPosition.iZ / fVelocity);

  	gravity.x = 0.f;
 	gravity.y = 0.f;
	gravity.z = 0.f;
	
 	explision = new AssaSkill3BombShotExplision;
	explision->Start(&pos, &velocity, &gravity, "IronMonsterSadnessShot");
	cAssaEffect[i] = explision;
	cAssaEffect[i]->Gravity = 10000;

	sPosition = GetMoveLocation(0, 0, fONE, 0, pKelvezu->Angle.y + factor, 1);
	i = GetAssaEffect(); 
	velocity.x = float((float)sPosition.iX / fVelocity);
	velocity.y = -1000.f;
	velocity.z = float((float)sPosition.iZ / fVelocity);

  	gravity.x = 0.f;
 	gravity.y = 0.f;
	gravity.z = 0.f;
	
 	explision = new AssaSkill3BombShotExplision;
	explision->Start(&pos, &velocity, &gravity, "IronMonsterSadnessShot");
	cAssaEffect[i] = explision;
	cAssaEffect[i]->Gravity = 10000;
	
}

void ParkKelvezuSkill2(Unit *pKelvezu)	// ÄÌº£Áê ½ºÅ³°ø°Ý1 »ç¿ë½Ã Ä³¸¯ÅÍ ÇÇ°ÝÀÌÆåÆ®
{
	POINT3D curPos;
	POINT3D attackPos;
	auto sPosition = GetMoveLocation(0, 0, 260 * fONE, pKelvezu->Angle.x, pKelvezu->Angle.y, 1);

	attackPos.x = pKelvezu->pX + sPosition.iX;
	attackPos.y = pKelvezu->pY + sPosition.iY;
	attackPos.z = pKelvezu->pZ + sPosition.iZ;

	curPos.x = pKelvezu->pX;
	curPos.y = pKelvezu->pY+130000;
	curPos.z = pKelvezu->pZ+50000;
	AssaParticle_TerrainFire(&curPos, &attackPos);

	sPosition = GetMoveLocation(0, 0, 210 * fONE, pKelvezu->Angle.x, pKelvezu->Angle.y + ANGLE_45, 1);

	attackPos.x = pKelvezu->pX + sPosition.iX;
	attackPos.y = pKelvezu->pY + sPosition.iY;
	attackPos.z = pKelvezu->pZ + sPosition.iZ;

	curPos.x = pKelvezu->pX;
	curPos.y = pKelvezu->pY+130000;
	curPos.z = pKelvezu->pZ+50000;
	AssaParticle_TerrainFire(&curPos, &attackPos, 10);

	sPosition = GetMoveLocation(0, 0, 160 * fONE, pKelvezu->Angle.x, pKelvezu->Angle.y + ANGLE_90, 1);

	attackPos.x = pKelvezu->pX + sPosition.iX;
	attackPos.y = pKelvezu->pY + sPosition.iY;
	attackPos.z = pKelvezu->pZ + sPosition.iZ;

	curPos.x = pKelvezu->pX;
	curPos.y = pKelvezu->pY+130000;
	curPos.z = pKelvezu->pZ+50000;
	AssaParticle_TerrainFire(&curPos, &attackPos, 20);

	sPosition = GetMoveLocation(0, 0, 210 * fONE, pKelvezu->Angle.x, pKelvezu->Angle.y + ANGLE_45 + ANGLE_90, 1);

	attackPos.x = pKelvezu->pX + sPosition.iX;
	attackPos.y = pKelvezu->pY + sPosition.iY;
	attackPos.z = pKelvezu->pZ + sPosition.iZ;

	curPos.x = pKelvezu->pX;
	curPos.y = pKelvezu->pY+130000;
	curPos.z = pKelvezu->pZ+50000;
	AssaParticle_TerrainFire(&curPos, &attackPos, 30);

	sPosition = GetMoveLocation(0, 0, 260 * fONE, pKelvezu->Angle.x, pKelvezu->Angle.y + ANGLE_180, 1);

	attackPos.x = pKelvezu->pX + sPosition.iX;
	attackPos.y = pKelvezu->pY + sPosition.iY;
	attackPos.z = pKelvezu->pZ + sPosition.iZ;

	curPos.x = pKelvezu->pX;
	curPos.y = pKelvezu->pY+130000;
	curPos.z = pKelvezu->pZ+50000;
	AssaParticle_TerrainFire(&curPos, &attackPos, 40);

	sPosition = GetMoveLocation(0, 0, 210 * fONE, pKelvezu->Angle.x, pKelvezu->Angle.y + ANGLE_180 + ANGLE_45, 1);

	attackPos.x = pKelvezu->pX + sPosition.iX;
	attackPos.y = pKelvezu->pY + sPosition.iY;
	attackPos.z = pKelvezu->pZ + sPosition.iZ;

	curPos.x = pKelvezu->pX;
	curPos.y = pKelvezu->pY+130000;
	curPos.z = pKelvezu->pZ+50000;
	AssaParticle_TerrainFire(&curPos, &attackPos, 50);

	sPosition = GetMoveLocation(0, 0, 160 * fONE, pKelvezu->Angle.x, pKelvezu->Angle.y + ANGLE_180 + ANGLE_90, 1);

	attackPos.x = pKelvezu->pX + sPosition.iX;
	attackPos.y = pKelvezu->pY + sPosition.iY;
	attackPos.z = pKelvezu->pZ + sPosition.iZ;

	curPos.x = pKelvezu->pX;
	curPos.y = pKelvezu->pY+130000;
	curPos.z = pKelvezu->pZ+50000;
	AssaParticle_TerrainFire(&curPos, &attackPos, 60);

	sPosition = GetMoveLocation(0, 0, 210 * fONE, pKelvezu->Angle.x, pKelvezu->Angle.y + ANGLE_180 + ANGLE_90 + ANGLE_45, 1);

	attackPos.x = pKelvezu->pX + sPosition.iX;
	attackPos.y = pKelvezu->pY + sPosition.iY;
	attackPos.z = pKelvezu->pZ + sPosition.iZ;

	curPos.x = pKelvezu->pX;
	curPos.y = pKelvezu->pY+130000;
	curPos.z = pKelvezu->pZ+50000;
	AssaParticle_TerrainFire(&curPos, &attackPos, 70);

}

// ÄÌº£Áê ¸¶¹ýÁø¹× ÀÔ¿¡¼­ ¿¬±â³ª´Â°Å
void ParkKelvezuJin(Unit *pKelvezu)
{
	if(GetAssaCodeEffect(pKelvezu, MONSTER_KELVEZU_CIRCLE) == FALSE)
	{
     	int i = GetAssaEffect();
		cAssaTraceCharMeshParticle *traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pKelvezu, "Bip01 Bae", "IceKelvezuBossJin1");
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->Posi.y = cAssaEffect[i]->Posi.y - 15000;
		cAssaEffect[i]->CODE = MONSTER_KELVEZU_CIRCLE;

		i = GetAssaEffect();
		traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pKelvezu, "BIP01 Mouse", "IceKelvezuBossMouseJin1");
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = MONSTER_KELVEZU_CIRCLE;

	}
}

// ÄÌº£Áê °ø°Ý½Ã ¹ßÅé¿¡¼­ °Ë±âÈ¿°ú
void ParkKelvezuFingerShow(Unit* pKelvezu, int nTime)
{
	if(pKelvezu)
	{
		int i = GetAssaEffect();
		cAssaMotionBlur *motionBlur = new cAssaMotionBlur;
		motionBlur->Start(pKelvezu, "Bip01 Hand", "Bip01 Fin03", nTime);
		motionBlur->Color.R = 200;
		motionBlur->Color.G = 100;
		motionBlur->Color.B = 200;
		motionBlur->Color.A = 100;
		cAssaEffect[i] = motionBlur;

		i = GetAssaEffect();
		motionBlur = new cAssaMotionBlur;
		motionBlur->Start(pKelvezu, "Bip01 Hand", "Bip01 Fin02", nTime);
		motionBlur->Color.R = 200;
		motionBlur->Color.G = 100;
		motionBlur->Color.B = 200;
		motionBlur->Color.A = 100;
		cAssaEffect[i] = motionBlur;

		i = GetAssaEffect();
		motionBlur = new cAssaMotionBlur;
		motionBlur->Start(pKelvezu, "Bip01 Hand", "Bip01 Fin01", nTime);
		motionBlur->Color.R = 200;
		motionBlur->Color.G = 100;
		motionBlur->Color.B = 200;
		motionBlur->Color.A = 100;
		cAssaEffect[i] = motionBlur;
	}
}

// ÄÌº£Áê °ø°Ý½Ã ³¯°³¿¡¼­ °Ë±âÈ¿°ú
void ParkKelvezuWingShow(Unit* pKelvezu, int nTime)
{
	if(pKelvezu)
	{
		int i = GetAssaEffect();
		cAssaMotionBlur *motionBlur = new cAssaMotionBlur;
		motionBlur->Start(pKelvezu, "Bip01 Rwing03", "Bip01 Rwing02", nTime);
		motionBlur->Color.R = 200;
		motionBlur->Color.G = 100;
		motionBlur->Color.B = 200;
		motionBlur->Color.A = 100;
		cAssaEffect[i] = motionBlur;

		i = GetAssaEffect();
		motionBlur = new cAssaMotionBlur;
		motionBlur->Start(pKelvezu, "Bip01 Rwing02", "Bip01 Rwing01", nTime);
		motionBlur->Color.R = 200;
		motionBlur->Color.G = 100;
		motionBlur->Color.B = 200;
		motionBlur->Color.A = 100;
		cAssaEffect[i] = motionBlur;

		i = GetAssaEffect();
		motionBlur = new cAssaMotionBlur;
		motionBlur->Start(pKelvezu, "Bip01 Lwing03", "Bip01 Lwing02", nTime);
		motionBlur->Color.R = 200;
		motionBlur->Color.G = 100;
		motionBlur->Color.B = 200;
		motionBlur->Color.A = 100;
		cAssaEffect[i] = motionBlur;

		i = GetAssaEffect();
		motionBlur = new cAssaMotionBlur;
		motionBlur->Start(pKelvezu, "Bip01 Lwing02", "Bip01 Lwing01", nTime);
		motionBlur->Color.R = 200;
		motionBlur->Color.G = 100;
		motionBlur->Color.B = 200;
		motionBlur->Color.A = 100;
		cAssaEffect[i] = motionBlur;
	}
}

// ÄÌº£Áê °ø°Ý½Ã ²¿¸®¿¡¼­ °Ë±âÈ¿°ú
void ParkKelvezuTaleShow(Unit* pKelvezu, int nTime)
{
	if(pKelvezu)
	{
		int i = GetAssaEffect();
		cAssaMotionBlur *motionBlur = new cAssaMotionBlur;
		motionBlur->Start(pKelvezu, "Bip01 Tale01", "Bip01 Tale02", nTime);
		motionBlur->Color.R = 200;
		motionBlur->Color.G = 100;
		motionBlur->Color.B = 200;
		motionBlur->Color.A = 100;
		cAssaEffect[i] = motionBlur;

		i = GetAssaEffect();
		motionBlur = new cAssaMotionBlur;
		motionBlur->Start(pKelvezu, "Bip01 Tale02", "Bip01 Tale03", nTime);
		motionBlur->Color.R = 200;
		motionBlur->Color.G = 100;
		motionBlur->Color.B = 200;
		motionBlur->Color.A = 100;
		cAssaEffect[i] = motionBlur;
	}
}

// ¿ùµåÄÅ ¸ó½ºÅÍ ÀÌÆåÆ®
void ParkAssaParticle_WorldCupMonsterAttack(Unit* pMonster, Unit *pChar)
{
	auto sPosition = GetMoveLocation(0, 0, 0, 0, pMonster->Angle.y, 0);
	POINT3D pCur, pDest;
	pCur.x = pMonster->pX + sPosition.iX;
	pCur.y = pMonster->pY + 3000;
	pCur.z = pMonster->pZ + sPosition.iZ;

	sPosition = GetMoveLocation(0, 30 * fONE, 0, 0, pChar->Angle.y, 0);
	pDest.x = pChar->pX + sPosition.iX;
	pDest.y = pChar->pY + sPosition.iY;
	pDest.z = pChar->pZ + sPosition.iZ;

	Assa = SetAssaEffect(0,"bball.ASE",0, &pCur,0);
	
	cAssaEffect[Assa]->Time = 0;
	cAssaEffect[Assa]->AniMaxCount = 60;
	cAssaEffect[Assa]->AniDelayTime = 4;
 	cAssaEffect[Assa]->MOVECODE = ASSA_ANGLE_ROTATE;
	cAssaEffect[Assa]->Angle.y = ANGLE_1;

	sPosition = GetRadian3D(pCur.x, pCur.y, pCur.z, pDest.x, pDest.y, pDest.z);

	cAssaEffect[Assa]->Angle.x = sPosition.iX;
	cAssaEffect[Assa]->Angle.y = sPosition.iY;
	cAssaEffect[Assa]->Angle.z = sPosition.iZ;
	
	cAssaEffect[Assa]->Angle.y = (-sPosition.iY + ANGLE_1)&ANGCLIP;
	cAssaEffect[Assa]->NotFadeIn = TRUE;
	cAssaEffect[Assa]->ARotateSpeed.z = 100;
	int i = GetAssaEffect();
	cASSAPARTSHOT *partShot = new cASSAPARTSHOT;
	partShot->Start(&pCur, &pDest, cAssaEffect[Assa], SKILL_TWIST_JAVELIN);
	cAssaEffect[i] = partShot;
}

void ParkWorldCupMonsterHit(Unit *pChar)	// ¿ùµåÄÅ ¸ó½ºÅÍ°¡ °ø°Ý½Ã Ä³¸¯ÅÍ ÇÇ°ÝÀÌÆåÆ®
{
	POINT3D pos;

	auto sPosition = GetMoveLocation(0, 0, 0, 0, pChar->Angle.y, 0);

	pos.x = pChar->pX + sPosition.iX;
	pos.y = pChar->pY + 7000;
	pos.z = pChar->pZ + sPosition.iZ;
	
 	g_NewParticleMgr.Start("MonsterHit2", pos);
}
//////////////////////////////  ¹ÚÃ¶È£  ////////////////////////////////////////
void ParkAssaParticle_MonsterIceChaosKara(Unit *pChar)
{
	if(GetAssaCodeEffect(pChar, ICE_MONSTER_CHAOSKARA_STAFF) == FALSE)
	{
     	int i = GetAssaEffect();
		cAssaTraceCharMeshParticle *traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pChar, "Bip01 ob", "ChaosKaraStaff");
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = ICE_MONSTER_CHAOSKARA_STAFF;

	}
}

void ParkAssaParticle_MonsterIceValentoBody(Unit *pValento)
{
	if(GetAssaCodeEffect(pValento, ICE_MONSTER_VALENTO_BODY) == FALSE)
	{
		int i = GetAssaEffect();
		cAssaTraceCharMeshParticle *traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pValento, "BIP01fire07", "IceValentoLEye");
		traceMeshParticle->SetScale(float(pValento->sCharacterData.sSize)/256.f);
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = ICE_MONSTER_VALENTO_BODY;
		
 		i = GetAssaEffect();
		traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pValento, "BIP01fire08", "IceValentoREye");
		traceMeshParticle->SetScale(float(pValento->sCharacterData.sSize)/256.f);
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = ICE_MONSTER_VALENTO_BODY;


		//¸öÅë
     	i = GetAssaEffect();
		traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pValento, "BIP01fire01", "IceValentoBody");
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = ICE_MONSTER_VALENTO_BODY;


		// ÆÈ²ÞÄ¡
		i = GetAssaEffect();
		traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pValento, "BIP01fire03", "IceValentoJoint");
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = ICE_MONSTER_VALENTO_BODY;

		i = GetAssaEffect();
		traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pValento, "BIP01fire04", "IceValentoJoint");
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = ICE_MONSTER_VALENTO_BODY;

		// ¹«¸­
		i = GetAssaEffect();
		traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pValento, "BIP01fire05", "IceValentoJoint");
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = ICE_MONSTER_VALENTO_BODY;

		i = GetAssaEffect();
		traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pValento, "BIP01fire06", "IceValentoJoint");
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = ICE_MONSTER_VALENTO_BODY;

	}
}

void ParkAssaParticle_MonsterTurtleCanonNormal(Unit *pTCanon, Unit* pTarget)
{
	auto sPosition = GetMoveLocation(0, 30 * fONE, 10 * fONE, 0, pTCanon->Angle.y, 0);
	StartEffectMonsterDest(pTCanon->pX + sPosition.iX, pTCanon->pY + sPosition.iY, pTCanon->pZ + sPosition.iZ, pTarget->pX, pTarget->pY + 24 * fONE, pTarget->pZ, MONSTER_TURTLECANON_SHOT);
}

struct tagFireCracker
{
	int nCracker;	// ÅÍÁö¶§ ÆÄÆí ÆÄÆ¼Å¬
	int nBome;		// Ç³¼± ÆÄÆ¼Å¬
};

tagFireCracker TableFireCracker[20] = { {0,0}, {0,1}, {0,2}, {0,3},
										{1,0}, {1,1}, {1,2}, {1,3},
										{2,0}, {2,1}, {2,2}, {2,3},
										{3,0}, {3,1}, {3,2}, {3,3},
										{4,0}, {4,1}, {4,2}, {4,3}
};


// ÆøÁ× ÀÌÆåÆ®
void ParkAssaParticle_FireCracker(Unit *pChar, int nFireCracker )
{
	if(GetAssaCodeEffect(pChar, EFFECT_FIRECRACKER) == FALSE)
	{
		int xpos, ypos, zpos;

		POINT3D BomePos;	// ÅÍÁö´Â À§Ä¡

		xpos = GetRandomPos(-20, 20)*fONE;
		ypos = GetRandomPos(-5, 5);
		zpos = GetRandomPos(-20, 20)*fONE;
		auto sPosition = GetMoveLocation(xpos, (ypos + 50)*fONE, zpos, 0, 0, 0);

		BomePos.x = pChar->pX + sPosition.iX;
		BomePos.y = pChar->pY + 100 * fONE + sPosition.iY;
		BomePos.z = pChar->pZ + sPosition.iZ;

		StartEffectMonsterDest(pChar->pX + sPosition.iX, pChar->pY + sPosition.iY, pChar->pZ + sPosition.iZ,
			BomePos.x, BomePos.y, BomePos.z, EFFECT_FIRE_CRACKER);


		switch (TableFireCracker[nFireCracker].nCracker)
		{
			case 0:
				g_NewParticleMgr.Start("FireCrackerAll", BomePos, 1.0f);
				break;

			case 1:
				g_NewParticleMgr.Start("FireCrackerHeart", BomePos, 1.0f);
				break;

			case 2:
				g_NewParticleMgr.Start("FireCrackerMoon", BomePos, 1.0f);
				break;

			case 3:
				g_NewParticleMgr.Start("FireCrackerStar", BomePos, 1.0f);
				break;

			case 4:
				g_NewParticleMgr.Start("FireCrackerNormal", BomePos, 1.0f);
				break;
		}

		switch(TableFireCracker[nFireCracker].nBome)
		{
			case 0:
				g_NewParticleMgr.Start("FireCrackerBombHeart", BomePos, 1.0f);
				break;
			case 1:
				g_NewParticleMgr.Start("FireCrackerBombMoon", BomePos, 1.0f);
				break;
			case 2:
				g_NewParticleMgr.Start("FireCrackerBombStar", BomePos, 1.0f);
				break;
			default:
				break;
		}
	}
}
void ParkAssaParticle_TurtleDragonHit(Unit *pCur, Unit *pDes)
{
	if (pCur && pDes)
	{
		auto sPosition = GetMoveLocation(0, 30 * fONE, 10 * fONE, 0, pCur->Angle.y, 0);
		StartEffectMonsterDest(pCur->pX + sPosition.iX, pCur->pY + sPosition.iY, pCur->pZ + sPosition.iZ, pDes->pX, pDes->pY + 24 * fONE, pDes->pZ, MONSTER_TURTLEDRAGON_SHOT1);
	}
}
void AssaParticle_MonsterIronChainGolem(Unit *pChar)
{
	if(GetAssaCodeEffect(pChar, IRON_MONSTER_CHAINGOLEM1) == FALSE)
	{
    	int i = GetAssaEffect();
		cAssaTraceCharMeshParticle *traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pChar, "Bip01 FX", "IronMonsterChainGolem1");
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = IRON_MONSTER_CHAINGOLEM1;

        i = GetAssaEffect();
		traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pChar, "Bip01 chain26", "IronMonsterChainGolem2", false);
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = IRON_MONSTER_CHAINGOLEM1;

	}
}

void AssaParticle_MonsterIronRunicGuardian(Unit *pChar, Unit *pDestChar)
{
	POINT3D curPos;
	POINT3D desPos;
    
 	curPos.x = pChar->pX;
	curPos.y = pChar->pY+40000;
	curPos.z = pChar->pZ;

	desPos.x = pDestChar->pX;
	desPos.y = pDestChar->pY+5000;
	desPos.z = pDestChar->pZ;

   	g_NewParticleMgr.Start("IronMonsterRunicGuardian", curPos);
	g_NewParticleMgr.Start("IronMonsterRunicGuardianLight1", curPos, 1.f);	
 	g_NewParticleMgr.Start("IronMonsterRunicGuardianLight2", desPos, 1.f);
	
 	//SetDynLight( desPos.x, desPos.y, desPos.z, 255, 255, 255, 255, 150, 2);

    Assa = SetAssaEffect(200,"spark04_01.bmp",0,&curPos,0);
	AssaGetAniFileMat(cAssaEffect[Assa]);
	cAssaEffect[Assa]->AniDelayTime = 3;
	cAssaEffect[Assa]->Face.r = 255;
	cAssaEffect[Assa]->Face.g = 255;
	cAssaEffect[Assa]->Face.b = 255;
	cAssaEffect[Assa]->Face.Transparency = 255;
	cAssaEffect[Assa]->Size.w = 8000;
	cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE;
	cAssaEffect[Assa]->Time = -70;
	
	cAssaEffect[Assa]->ScalePosi.x = desPos.x - curPos.x;
	cAssaEffect[Assa]->ScalePosi.y = desPos.y - curPos.y;
	cAssaEffect[Assa]->ScalePosi.z = desPos.z - curPos.z;

  	Assa = SetAssaEffect(200,"light2_01.bmp",0,&curPos,0);
	AssaGetAniFileMat(cAssaEffect[Assa]);
	cAssaEffect[Assa]->AniDelayTime = 3;
	cAssaEffect[Assa]->Face.r = 255;
	cAssaEffect[Assa]->Face.g = 255;
	cAssaEffect[Assa]->Face.b = 255;
	cAssaEffect[Assa]->Face.Transparency = 255;
	cAssaEffect[Assa]->Size.w = 8000;
	cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE; 
	cAssaEffect[Assa]->Time = -70;

	cAssaEffect[Assa]->ScalePosi.x = desPos.x - curPos.x;
	cAssaEffect[Assa]->ScalePosi.y = desPos.y - curPos.y;
	cAssaEffect[Assa]->ScalePosi.z = desPos.z - curPos.z;
}

void AssaParticle_MonsterIronMountainHit1(Unit *pChar)
{
	//Mountain
 	POINT3D pos;
	auto sPosition = GetMoveLocation(0, 0, 100 * fONE, 0, pChar->Angle.y, 0);
	pos.x = pChar->pX + sPosition.iX;
	pos.y = pChar->pY + 2000;
	pos.z = pChar->pZ + sPosition.iZ;
	
 	g_NewParticleMgr.Start("IronMonsterMountainHit1", pos);
}

void AssaParticle_MonsterIronTowerGolemHit1(Unit *pChar)
{
	POINT3D pos;
    pos.x = pChar->pX;
	pos.y = pChar->pY;
	pos.z = pChar->pZ;
	
	auto sPosition = GetMoveLocation(0, 0, -50 * fONE, pChar->Angle.x, pChar->Angle.y, 0);
	pos.x += sPosition.iX;
	pos.z += sPosition.iZ;
    
	Assa = SetAssaEffect(0,"m_StoneGolem.ASE",0,&pos,0, 1);
	cAssaEffect[Assa]->AniMaxCount = 30;
	cAssaEffect[Assa]->AniDelayTime = 2;
	cAssaEffect[Assa]->Angle.y = (-pChar->Angle.y+ANGLE_180)&ANGCLIP;
	cAssaEffect[Assa]->NotFadeIn = TRUE;
	
	pos.x = pos.x;
	pos.y = pos.y+1500;
	pos.z = pos.z;
	
	sPosition = GetMoveLocation(0, 0, 120 * fONE, pChar->Angle.x, pChar->Angle.y, 0);
	pos.x += sPosition.iX;
	pos.z += sPosition.iZ;
	g_NewParticleMgr.Start("StoneGolemHit1", pos);
}

void AssaParticle_MonsterIronTowerGolemSkill1(Unit *pChar)
{
	auto sPosition = GetMoveLocation(0, 0, 30 * fONE, 0, pChar->Angle.y, 0);
	
  	//int num = -1;
 	POINT3D pos;
	pos.x = pChar->pX + sPosition.iX;
	pos.y = pChar->pY + 3000;
	pos.z = pChar->pZ + sPosition.iZ;
	
	sPosition = GetMoveLocation(0, 0, 30 * fONE, 0, pChar->Angle.y, 0);

	//Å×½ºÆ®¿ë.
	D3DVECTOR  velocity;
	D3DVECTOR  gravity;
   	int i = GetAssaEffect();
	velocity.x = float((float)sPosition.iX / 8.f);
	velocity.y = 0.f;
	velocity.z = float((float)sPosition.iZ / 8.f);

  	gravity.x = 0.f;
 	gravity.y = 0.f;
	gravity.z = 0.f;
	
	AssaSkill3BombShotExplision *explision = new AssaSkill3BombShotExplision;
	explision->Start(&pos, &velocity, &gravity, "IronMonsterBombHit2");
	cAssaEffect[i] = explision;
	
	
	int num = g_NewParticleMgr.Start("MonsterIron1", pos);
	if(num != -1)
	{
		POINT3D angle;
		angle.x = 0;
		angle.y = pChar->Angle.y;
		angle.z = 0;
		g_NewParticleMgr.SetAngle(num, angle);
	}
}


void AssaParticle_MonsterAvelArcher(Unit *pChar, Unit *pDestChar)
{
	auto sPosition = GetMoveLocation(0, 60 * fONE, 20 * fONE, 0, pChar->Angle.y, 0);
	POINT3D curPos;
	POINT3D desPos;
	curPos.x = pChar->pX + sPosition.iX;
	curPos.y = pChar->pY + sPosition.iY;
	curPos.z = pChar->pZ + sPosition.iZ;
	
	desPos.x = pDestChar->pX;
	desPos.y = pDestChar->pY+24*fONE;
	desPos.z = pDestChar->pZ;
	
	StartEffectMonsterDest(curPos.x, curPos.y, curPos.z, desPos.x, desPos.y, desPos.z, MONSTER_SERQBUS_SHOT1);
}


void AssaParticle_MonsterAvelQueen(Unit *pChar, Unit *pDestChar)
{
	auto sPosition = GetMoveLocation(0, 60 * fONE, 20 * fONE, 0, pChar->Angle.y, 0);
	POINT3D curPos;
	POINT3D desPos;
	curPos.x = pChar->pX + sPosition.iX;
	curPos.y = pChar->pY + sPosition.iY;
	curPos.z = pChar->pZ + sPosition.iZ;
	
	desPos.x = pDestChar->pX;
	desPos.y = pDestChar->pY+24*fONE;
	desPos.z = pDestChar->pZ;
	
	StartEffectMonsterDest(curPos.x, curPos.y, curPos.z, desPos.x, desPos.y, desPos.z, MONSTER_SERQBUS_SHOT2);
}
void AssaParticle_MonsterDeadZoneDead(Unit *pChar)
{
	POINT3D curPos;
  	curPos.x = pChar->pX;
	curPos.y = pChar->pY + 15000;
	curPos.z = pChar->pZ;
	
	g_NewParticleMgr.Start("IronMonsterDeadZoneDead", curPos);
}
void AssaParticle_MonsterHyperDead(Unit *pChar)
{
	POINT3D curPos;
 	curPos.x = pChar->pX;
	curPos.y = pChar->pY + 10000;
	curPos.z = pChar->pZ;

	g_NewParticleMgr.Start("IronMonsterHyperDead", curPos);
}
void AssaParticle_MonsterIronHit1(POINT3D *pPosi)
{
	g_NewParticleMgr.Start("HulkHit1", *pPosi);
}

void AssaParticle_MonsterIronMountainSkill1(Unit *pChar)
{
	//Mountain
 	POINT3D pos;
	auto sPosition = GetMoveLocation(0, 0, 130 * fONE, 0, pChar->Angle.y - ANGLE_45 / 3, 0);
	pos.x = pChar->pX + sPosition.iX;
	pos.y = pChar->pY + 1000;
	pos.z = pChar->pZ + sPosition.iZ;
	
 	g_NewParticleMgr.Start("IronMonsterMountainHit1", pos);

	
	sPosition = GetMoveLocation(0, 0, 130 * fONE, 0, pChar->Angle.y + ANGLE_45 / 3, 0);
	pos.x = pChar->pX + sPosition.iX;
	pos.y = pChar->pY + 1000;
	pos.z = pChar->pZ + sPosition.iZ;
	
 	g_NewParticleMgr.Start("IronMonsterMountainHit1", pos);
}

void AssaParticle_MonsterRunicGuardianHand(Unit *pChar)
{
	if(GetAssaCodeEffect(pChar, IRON_MONSTER_RUNIC_GUARDIAN_HAND1) == FALSE)
	{
    	int i = GetAssaEffect();
		cAssaTraceCharMeshParticle *traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pChar, "Bip01 L Hand", "IronMonsterRunicGuardianHand");
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = IRON_MONSTER_RUNIC_GUARDIAN_HAND1;

        i = GetAssaEffect();
		traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pChar, "Bip01 R Hand", "IronMonsterRunicGuardianHand");
		cAssaEffect[i] = traceMeshParticle;
		cAssaEffect[i]->CODE = IRON_MONSTER_RUNIC_GUARDIAN_HAND1;
	}
}

void AssaParticle_MonsterRunicGuardianShot(Unit *pChar, Unit *pDestChar)
{
	POINT3D curPos;
	POINT3D desPos;
   	curPos.x = pChar->pX;
	curPos.y = pChar->pY+30*fONE;
	curPos.z = pChar->pZ;

	desPos.x = pDestChar->pX;
	desPos.y = pDestChar->pY+24*fONE;
	desPos.z = pDestChar->pZ;

	int i = GetAssaEffect();
	AssaRunicGuardianShot *runicGuardianShot = new AssaRunicGuardianShot;
	runicGuardianShot->Start(&curPos, &desPos);
	cAssaEffect[i] = runicGuardianShot;
}

void AssaParticle_MonsterRunicGuardianBossShot(Unit *pChar, int blendType)
{
	D3DVECTOR velocity;
	POINT3D curPos;
	curPos.x = pChar->pX;
	curPos.y = pChar->pY + 30000;
 	curPos.z = pChar->pZ;
	
	//g_NewParticleMgr.Start("IronMonsterRunicGuardianBossSkill1", curPos);

	POINT3D desPos;
 	desPos.x = pChar->pX;
	desPos.y = pChar->pY;
	desPos.z = pChar->pZ;
	
    for(int index = 0; index < 5; index++)
	{
		auto sPosition = GetMoveLocation(0, 12 * fONE, -5 * fONE, 0, index*(ANGLE_45 + ANGLE_45 / 2 + GetRandomPos(0, ANGLE_45)), 0);
		
		velocity.x = (float)sPosition.iX / 256.f;
		velocity.y = (float)sPosition.iY / 256.f;
		velocity.z = (float)sPosition.iZ / 256.f;
		
 		if(index == 0)
		{
			desPos.x = pChar->pX;
			desPos.y = pChar->pY;
			desPos.z = pChar->pZ;
		}
		else
		{
			desPos.x = pChar->pX + sPosition.iX * 8;
			desPos.y = pChar->pY;
			desPos.z = pChar->pZ + sPosition.iZ * 8;
		}

		int i = GetAssaEffect();
		AssaRunicGuardianBossShot *runicGuardianBossShot = new AssaRunicGuardianBossShot;
		runicGuardianBossShot->Start(&curPos, &desPos, &velocity, blendType);
		cAssaEffect[i] = runicGuardianBossShot;
		if(index == 0)
			runicGuardianBossShot->SetHitFlag(true);
	}
}

void AssaParticle_MonsterRunicGuardianBossLightShot(Unit **pCharList, int charCount)
{
	if(charCount > 1)
	{

 		for(int index = 0; index < charCount-1; index++)
		{
 			int i = GetAssaEffect();
 			AssaRunicGuardianLight *runicGuardianLight = new AssaRunicGuardianLight;
			//if(charCount < 2)
			//{
				runicGuardianLight->Start(pCharList[index],pCharList[index+1], 0, true, true);
			//}

			/*
			else
			{
				if(index == 0)
				{
					runicGuardianLight->Start(pCharList[index],pCharList[index+1], 0, true, false);
				}
				else if(index == (charCount - 2))
				{
					runicGuardianLight->Start(pCharList[index],pCharList[index+1], 0, false, true);
				}
				else
					runicGuardianLight->Start(pCharList[index],pCharList[index+1], 0, false, true);
			}
			*/

			cAssaEffect[i] = runicGuardianLight;
		}
	}
}


void AssaParticle_MonsterRunicGuardianBossWeapon(Unit *pChar)
{
  	if(GetAssaCodeEffect(pChar, IRON_MONSTER_RUNIC_GUARDIAN_HAND1) == FALSE)
	{
    	int i = GetAssaEffect();
		cAssaTraceCharMeshParticle *traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pChar, "Bip01 Effect", "IronMonsterRunicGuardianBossWeapon2");
        traceMeshParticle->SetScale(float(pChar->sCharacterData.sSize)/256.f);

		cAssaEffect[i] = traceMeshParticle;
 		cAssaEffect[i]->CODE = IRON_MONSTER_RUNIC_GUARDIAN_HAND1;

		i = GetAssaEffect();
		traceMeshParticle = new cAssaTraceCharMeshParticle;
		traceMeshParticle->Start(pChar, "Bip01 Pelvis", "IronMonsterRunicGuardianBossJin2");
		cAssaEffect[i] = traceMeshParticle;
		traceMeshParticle->SetScale(float(pChar->sCharacterData.sSize)/256.f);
		cAssaEffect[i]->CODE = IRON_MONSTER_RUNIC_GUARDIAN_HAND1;
	}
}


void AssaParticle_MonsterRunicGuardianBossHit(Unit *pCurChar, Unit *pDestChar, Unit **pCharList, int charCount)
{
	POINT3D curPos;
   	curPos.x = pCurChar->pX;
	curPos.y = pCurChar->pY+15000;
	curPos.z = pCurChar->pZ;

	D3DVECTOR velocity;
	memset(&velocity, 0, sizeof(velocity));

	int motionEvent = pCurChar->MotionEvent;
	int i  = 0;
	if(motionEvent == 1)
	{
 		i = GetAssaEffect(); 
		AssaRunicGuardianBossHit *guardianBossHit = new AssaRunicGuardianBossHit;
		
		velocity.x = 0.f;
		velocity.y = 0.f;
		velocity.z = 0.f;

		auto sPosition = GetMoveLocation(0, 0, 3 * fONE + rand() % (2 * fONE) - fONE, 0, pCurChar->Angle.y - ANGLE_45, 0);
		velocity.x += ((float)sPosition.iX*2.f / 256.f);
		velocity.z += ((float)sPosition.iZ*2.f / 256.f);
		if(charCount == 0)
			guardianBossHit->Start(&curPos, pDestChar, &velocity, 0);
		else
			guardianBossHit->Start(&curPos, pDestChar, &velocity, 0, pCharList, charCount);

		cAssaEffect[i] = guardianBossHit;
	}
	else
	{
		i = GetAssaEffect(); 
		AssaRunicGuardianBossHit *guardianBosHit = new AssaRunicGuardianBossHit;
	
		velocity.x = 0.f;
		velocity.y = 0.f;
		velocity.z = 0.f;

		auto sPosition = GetMoveLocation(0, 0, 3 * fONE + rand() % (2 * fONE) - fONE, 0, pCurChar->Angle.y + ANGLE_45, 0);
		velocity.x += ((float)sPosition.iX*2.f / 256.f);
		velocity.z += ((float)sPosition.iZ*2.f / 256.f);
		if(charCount == 0)
			guardianBosHit->Start(&curPos, pDestChar, &velocity, 0);
		else
		 	guardianBosHit->Start(&curPos, pDestChar, &velocity, 0, pCharList, charCount);

		cAssaEffect[i] = guardianBosHit;
	}
}

void AssaParticle_MonsterRunicGuardianBossSkillHit(POINT3D *pDest)
{
	D3DVECTOR vector;
    vector.x = float(pDest->x - lpCurPlayer->pX)/fONE;
	vector.y = float(pDest->y - lpCurPlayer->pY)/fONE;
	vector.z = float(pDest->z - lpCurPlayer->pZ)/fONE;
	
	float length;
 	length = (float)sqrt(vector.x*vector.x+vector.y*vector.y+vector.z*vector.z);
	if(length == 0)
		length = 1;

	g_NewParticleMgr.Start("IronMonsterRunicGuardianSkillHit1", *pDest);
	SetDynLight( pDest->x, pDest->y, pDest->z,-150, -150, -255, 255, 300, 4);
 	EffectWaveCamera(int((1000.f - length)/25.f), 1);

}

void AssaParticle_TerrainFireHit(POINT3D *pCur,int SkillCode)
{
    D3DVECTOR vector;
    vector.x = float(pCur->x - lpCurPlayer->pX)/fONE;
	vector.y = float(pCur->y - lpCurPlayer->pY)/fONE;
	vector.z = float(pCur->z - lpCurPlayer->pZ)/fONE;
	
	float length;
 	length = (float)sqrt(vector.x*vector.x+vector.y*vector.y+vector.z*vector.z);
	if(length == 0)
		length = 1;

    SetDynLight( pCur->x, pCur->y, pCur->z, 255, 200, 100, 255, 250, 2);
	switch(SkillCode)
	{
	case SKILL_PRESS_OF_DEITY:
		g_NewParticleMgr.Start("PressOfDeity1", *pCur);
		break;
	default:
		g_NewParticleMgr.Start("FireBigHit1", *pCur);
		break;
	}
    EffectWaveCamera(int((500.f - length)/15.f), 2);
}

void AssaParticle_MonsterRunicGrardianBossSkill(Unit *pChar)
{
    int i = GetAssaEffect();
	AssaRunicGuardianBossSkill *runicGuardianBossSkill = new AssaRunicGuardianBossSkill;
	runicGuardianBossSkill->Start(pChar,70+50);
	cAssaEffect[i] = runicGuardianBossSkill;
	
	POINT3D pos;
   	memcpy(&pos, &pChar->Posi, sizeof(POINT3D));
    pos.y += 26000;
	
	POINT3D curPos;
	POINT3D rand;

    for(int index = 0; index < 100; index++)
	{
        rand.x = GetRandomPos(-80, 80);
		rand.y = GetRandomPos(-80, 80);
		rand.z = GetRandomPos(-80, 80);
		
		double length = sqrt((float)rand.x*(float)rand.x+(float)rand.y*(float)rand.y+(float)rand.z*(float)rand.z);
		
		if(length == 0)
			length = 1;
	 	int range = GetRandomPos(19000, 20000);
 		curPos.x = int(((float)rand.x/length)*(float)range+(float)pos.x);
		curPos.y = int(((float)rand.y/length)*(float)range+(float)pos.y);
		curPos.z = int(((float)rand.z/length)*(float)range+(float)pos.z);
		
	 	Assa = SetAssaEffect( 50, "Shield1.bmp", 0, &curPos, 0, 0);
		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE;
		
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE;
		
 		cAssaEffect[Assa]->Face.r = 255;
		cAssaEffect[Assa]->Face.g = 150;
		cAssaEffect[Assa]->Face.b = 50;
		cAssaEffect[Assa]->Face.Transparency = 255;
 		cAssaEffect[Assa]->Time = -(index);
  	 	cAssaEffect[Assa]->MoveSpeed.x = -int(float(rand.x)/length*600.f);
		cAssaEffect[Assa]->MoveSpeed.y = -int(float(rand.y)/length*600.f);
		cAssaEffect[Assa]->MoveSpeed.z = -int(float(rand.z)/length*600.f);
		
  		cAssaEffect[Assa]->Size.w = 600+GetRandomPos(0,500);

		POINT3D inScale;
   		inScale.x = int((rand.x)/(float)length*14000.f);
		inScale.y = int((rand.y)/(float)length*14000.f);
		inScale.z = int((rand.z)/(float)length*14000.f);
		
		cAssaEffect[Assa]->ScalePosi.x = inScale.x;
		cAssaEffect[Assa]->ScalePosi.y = inScale.y;
		cAssaEffect[Assa]->ScalePosi.z = inScale.z;
	}
}
void AssaParticle_MonsterIronOmuHit1(Unit *pChar)
{
	POINT3D charPos;
	auto sPosition = GetMoveLocation(0, 0, 30 * fONE, 0, pChar->Angle.y, 0);

	charPos.x = pChar->pX + sPosition.iX;
	charPos.y = pChar->pY + 7000;
	charPos.z = pChar->pZ + sPosition.iZ;
	
	int num;
	num = g_NewParticleMgr.Start("IronMonsterOmuHit1", charPos);
	if(num != -1)
	{
		POINT3D angle;
  		angle.x = 0;
		angle.y = pChar->Angle.y;
		angle.z = 0;
		g_NewParticleMgr.SetAngle(num, angle);
	}
}
void AssaParticle_ShelltomShot(POINT3D *pPosi, POINT3D *pDest, int type)
{
   	int i = GetAssaEffect();
	AssaShelltomShot *shelltomShot = new AssaShelltomShot;
	shelltomShot->Start(pPosi, pDest, type);
	cAssaEffect[i] = shelltomShot;
}

void AssaParticle_BamShot(POINT3D *pPosi, POINT3D *pDest)
{
	int i = GetAssaEffect();
	AssaShelltomShot *shelltomShot = new AssaShelltomShot;
	shelltomShot->Start(pPosi, pDest,1);
	cAssaEffect[i] = shelltomShot;
}

void AssaParticle_MonsterExplision(POINT3D *pPosi)
{
	POINT3D pos;
 	memcpy(&pos, pPosi, sizeof(POINT3D));
	D3DVECTOR velocity;
 	D3DVECTOR gravity;
	
  	for(int index = 0; index < 3; index++)
  	{
		int i = GetAssaEffect(); 
		velocity.x = float(rand()%2400-1200);
		velocity.y = float(rand()%500+900);
		velocity.z = float(rand()%2400-1200);

  		gravity.x = 0;
 		gravity.y = float((rand()%500-670));
		gravity.z = 0;
		
		AssaSkill3BombShotExplision *explision = new AssaSkill3BombShotExplision;
		explision->Start(&pos, &velocity, &gravity, "IronMonsterBombHit2");
		cAssaEffect[i] = explision;
	}

	g_NewParticleMgr.Start("IronMonsterBombHit1", pos);
 	SetDynLight( pos.x, pos.y, pos.z, 255, 150, 50, 255, 250, 2);
}

void AssaParticle_TurtleDragonHit(POINT3D *pPosi)
{
	POINT3D pos;
	memcpy(&pos, pPosi, sizeof(POINT3D));
	D3DVECTOR velocity;
	D3DVECTOR gravity;

	for(int index = 0; index < 3; index++)
	{
		int i = GetAssaEffect(); 
		velocity.x = float(rand()%2400-1200);
		velocity.y = float(rand()%500+900);
		velocity.z = float(rand()%2400-1200);

		gravity.x = 0;
		gravity.y = float((rand()%500-670));
		gravity.z = 0;

		AssaSkill3BombShotExplision *explision = new AssaSkill3BombShotExplision;
		explision->Start(&pos, &velocity, &gravity, "TurtleDragonHit3");
		cAssaEffect[i] = explision;
	}
	g_NewParticleMgr.Start("TurtleDragonHit2", pos);
	SetDynLight( pos.x, pos.y, pos.z, 255, 150, 50, 255, 250, 2);
}
void AssaParticle_BoneHoundHit(Unit *pChar)
{
	if (pChar)
	{
		auto sPosition = GetMoveLocation(0, 0, 50 * fONE, 0, pChar->Angle.y, 0);

		POINT3D pos;
		pos.x = pChar->pX + sPosition.iX;
		pos.y = pChar->pY + 10000;
		pos.z = pChar->pZ + sPosition.iZ;

		sPosition = GetMoveLocation(0, 0, 30 * fONE, 0, pChar->Angle.y, 0);

		D3DVECTOR  velocity;
		D3DVECTOR  gravity;

		int i = GetAssaEffect(); 
		velocity.x = float((float)sPosition.iX / 8.f);
		velocity.y = 0.f;
		velocity.z = float((float)sPosition.iZ / 8.f);

		gravity.x = 0.f;
		gravity.y = 0.f;
		gravity.z = 0.f;

		AssaSkill3BombShotExplision *explision = new AssaSkill3BombShotExplision;
		explision->Start(&pos, &velocity, &gravity, "BonehoundHit4");
		cAssaEffect[i] = explision;

		int num = g_NewParticleMgr.Start("BonehoundSkill3", pos);

		if(num != -1)
		{
			POINT3D angle;
			angle.x = 0;
			angle.y = pChar->Angle.y;
			angle.z = 0;
			g_NewParticleMgr.SetAngle(num, angle);
		}
	}
}
void AssaParticle_TurtleDragonSkill(POINT3D *pPosi)
{
	POINT3D pos;
	memcpy(&pos, pPosi, sizeof(POINT3D));
	D3DVECTOR velocity;
	D3DVECTOR gravity;

	for(int index = 0; index < 3; index++)
	{
		int i = GetAssaEffect(); 
		velocity.x = float(rand()%2400-1200);
		velocity.y = float(rand()%500+900);
		velocity.z = float(rand()%2400-1200);

		gravity.x = 0;
		gravity.y = float((rand()%500-670));
		gravity.z = 0;

		AssaSkill3BombShotExplision *explision = new AssaSkill3BombShotExplision;
		explision->Start(&pos, &velocity, &gravity);
		cAssaEffect[i] = explision;
	}
	g_NewParticleMgr.Start("TurtleDragonSkill1", pos);
	SetDynLight( pos.x, pos.y, pos.z, 255, 150, 50, 255, 200, 2);
}

void AssaMonsterHitTest(Unit *pChar)
{
	//AssaParticle_MonsterIronFist(pChar);
	AssaParticle_MonsterIronMorgonHit(pChar);
}
 
void AssaParticle_TerrainShowStart()
{
	int i = GetAssaEffect();
	AssaNatureSnow *natureSnow = new AssaNatureSnow;
	
	natureSnow->Start();
	cAssaEffect[i] = natureSnow;
}

void AssaParticle_ShelltomWeaponHit(POINT3D *pPosi)
{
    g_NewParticleMgr.Start("ShellTomWeaponHit", *pPosi);
	SetDynLight( pPosi->x,pPosi->y+22*fONE,pPosi->z , 100, 0, 0, 0, 250, 3);
} 


void AssaParticle_ShelltomWeapon(Unit *pChar, int time, int code)
{
	bool bFlag = false;
	for(int i = 0; i < cASSAEFFECT_MAX; i++)
	{
		if(cAssaEffect[i])
		{
			if(cAssaEffect[i]->CODE == SHELLTOM_WEAPON)
			{
				if(cAssaEffect[i]->pChar == pChar)
				{
					bFlag = true;
   					cAssaEffect[i]->Time = 0;
					cAssaEffect[i]->Max_Time = time;
				}
			}
		}
	}
	

	if(bFlag == false)
	{
   		int i = GetAssaEffect();
 		AssaShelltomUpWeapon2 *shelltomWeapon = new AssaShelltomUpWeapon2;
  		shelltomWeapon->Start(pChar, time, code);
		cAssaEffect[i] = shelltomWeapon;
	}
}
//ÔÉÊ¯Ð§¹û
void AssaParticle_TerrainFire(POINT3D *pCur, POINT3D *pDest, int delay,int SkillCode)
{
	int i = GetAssaEffect();
	AssaSkyParticle *skyParticle = new AssaSkyParticle;
	skyParticle->Start(pCur, pDest,delay,SkillCode);
	cAssaEffect[i] = skyParticle;
}

void SkillPhoenixShotFlame(Unit *pChar, POINT3D *curPos)
{
	auto sPosition = GetMoveLocation(0, 0, 30 * fONE, 0, (ANGLE_45 + pChar->Angle.y)&ANGCLIP, 0);
	//Å×½ºÆ®¿ë.
	D3DVECTOR  velocity;
	D3DVECTOR  gravity;
	
 	int i = GetAssaEffect();
		
	POINT3D partPos;
	partPos.x = curPos->x + sPosition.iX;
	partPos.y = curPos->y;
	partPos.z = curPos->z + sPosition.iZ;
	
	sPosition = GetMoveLocation(0, 0, 30 * fONE, 0, (pChar->Angle.y)&ANGCLIP, 0);
	velocity.x = (float)(sPosition.iX) / 8.f;
	velocity.y = 0.f;
	velocity.z = (float)(sPosition.iZ) / 8.f;

  	gravity.x = 0.f;
 	gravity.y = 0.f;
	gravity.z = 0.f;
	
  	AssaSkill3BombShotExplision *explision = new AssaSkill3BombShotExplision;
	explision->Start(&partPos, &velocity, &gravity, "IronMonsterSadnessShot");
	cAssaEffect[i] = explision;
	
	sPosition = GetMoveLocation(0, 0, 30 * fONE, 0, -((ANGLE_45 + pChar->Angle.y)&ANGCLIP), 0);
	partPos.x = curPos->x + sPosition.iX;
	partPos.y = curPos->y;
	partPos.z = curPos->z + sPosition.iZ;

	i = GetAssaEffect();

	sPosition = GetMoveLocation(0, 0, 30 * fONE, 0, (pChar->Angle.y)&ANGCLIP, 0);
	velocity.x = (float)(sPosition.iX) / 8.f;
	velocity.y = 0.f;
	velocity.z = (float)(sPosition.iZ) / 8.f;

  	gravity.x = 0.f;
 	gravity.y = 0.f;
	gravity.z = 0.f;
	
	explision = new AssaSkill3BombShotExplision;
	explision->Start(&partPos, &velocity, &gravity, "IronMonsterSadnessShot");
	cAssaEffect[i] = explision;
}

BOOL GetAssaUseEffect(Unit *pChar, int code)
{
	return GetAssaCodeEffect(pChar, code);
}
bool GetAssaContinueSkill(int skillCode)
{
	for(int index = 0; index < SIN_MAX_SKILL_LIST; index++)
	{
		if(ContinueSkill[index].Flag)
		{
			if(ContinueSkill[index].CODE == skillCode)
				return true;
		}
	}
	
	return false;
}

// »úÐµ Åùö¨Ðý·ç¼¼ÄÜÐ§¹û
int ParkParticle_LandMinning_Skill(Unit *pChar)
{
	POINT3D pos;
	pos.x = pChar->pX;
	pos.y = pChar->pY;
	pos.z = pChar->pZ;
	StartEffectMonster(pos.x,pos.y,pos.z,EFFECT_LANDMINNING_SKILL);
	return TRUE;
}
void ParkParticle_DraxosSkill(Unit *pChar,int LiveCount)
{
	int i = GetAssaEffect();
	cAssaMotionBlur *motionBlur = new cAssaMotionBlur;
	motionBlur->Start(pChar, "Bip01 Wapon01", "Bip01 Wapon02",LiveCount);
	motionBlur->SetScale(1.5f);
	cAssaEffect[i] = motionBlur;
}
void AssaParticle_HyperSonic(Unit *pChar,int LiveCount)
{
	int SkillTime = LiveCount*70+2;

	if (AddAssaCodeEffectTime(pChar,SKILL_H_SONIC,SkillTime) == 0)
	{
		int i = GetAssaEffect();
		AssaSkillHyperSonic *Metalion = new AssaSkillHyperSonic;
		Metalion->Start(pChar,LiveCount);
		cAssaEffect[i] = Metalion;
	}
}
void AssaParticle_EnhenceStart(Unit *pChar)
{
	POINT3D charPos;
	charPos.x = pChar->pX;
	charPos.y = pChar->pY;
	charPos.z = pChar->pZ;
	g_NewParticleMgr.Start("Skill5_Meca_PowerEnhance_Start",charPos);
}
//Õ½Éñ×£¸£Ð§¹û
void AssaParticle_EnhenceEffect(Unit *pChar,int LiveCount)
{
	int SkillTime = LiveCount*70+2;

	if (AddAssaCodeEffectTime(pChar,SKILL_P_ENHENCE,SkillTime) == 0)
	{
		int i = GetAssaEffect();
		AssaSkill5Normal *motion = new AssaSkill5Normal;
		motion->Start(pChar,LiveCount,"Skill5_Mecanician_PowerEnhance1","Skill5_Mecanician_PowerEnhance2",SKILL_P_ENHENCE);
		cAssaEffect[i] = motion;
	}
}
//»ØÐýÖ®ÎèÐ§¹û
void AssaParticle_EvadEshot(Unit *pChar)
{
	int i = GetAssaEffect();
	POINT3D charPos;
	AssaSkill5Normal *motion = new AssaSkill5Normal;
	motion->Start(pChar,3,"Skill5_Acher_EvadeShot2","Skill5_Acher_EvadeShot3");
	cAssaEffect[i] = motion;

	auto sPosition = GetMoveLocation(0, 0, 0, 0, pChar->Angle.y, 0);
	charPos.x = pChar->pX + sPosition.iX;
	charPos.y = pChar->pY + 3000;
	charPos.z = pChar->pZ + sPosition.iZ;
	g_NewParticleMgr.Start("Skill5_Acher_Evade_ShotEffect",charPos);

	sPosition = GetMoveLocation(0, 0, fONE * 100, pChar->Angle.x, pChar->Angle.y, 0);
	charPos.x = pChar->pX + sPosition.iX;
	charPos.y = pChar->pY + fONE * 10;
	charPos.z = pChar->pZ + sPosition.iZ;
	g_NewParticleMgr.Start("Skill5_Acher_EvadeShot4",charPos,1.2f);
}
//Ðþ¹âÖ®Îè
void AssaParticle_S_Rope(POINT3D *curPos,POINT3D *desPos)
{
	int i = GetAssaEffect();

	AssaSkill3LightingJavelin *motion = new AssaSkill3LightingJavelin;
	motion->StartRope(curPos,desPos);
	cAssaEffect[i] = motion;
}
//ì«·çÖ®¼ý
void AssaParticle_Splash(POINT3D *pos)
{
	g_NewParticleMgr.Start("EvilMaple",*pos);
}
//º®±ùÖ®¼ý
void AssaParticle_CircleTrap(POINT3D *curPos,POINT3D *desPos,int Level)
{
	int i = GetAssaEffect();

	AssaSkillCircleTrap *motion = new AssaSkillCircleTrap;
	motion->Start(curPos,desPos,Level);
	cAssaEffect[i] = motion;
}
//µØÏ®ÆæÇ¹
void AssParticle_Spear(Unit *pChar)
{
	int i = GetAssaEffect();
	AssaSkill5Normal *motion = new AssaSkill5Normal;
	motion->Start(pChar,3,"Skill5_PikeMan_FinalSpear1","Skill5_PikeMan_FinalSpear2",SKILL_F_SPEAR);
	cAssaEffect[i] = motion;
}
//ÉýÁúÖØ»÷
void AssaParticle_Moon(Unit *pChar)
{
	int i = GetAssaEffect();
	AssaSkill5Normal *motion = new AssaSkill5Normal;
	motion->Start(pChar,3,"Skill5_Knight_CrescentMoon1","Skill5_Knight_CrescentMoon1",SKILL_C_MOON);
	cAssaEffect[i] = motion;
}
//ÍöÁéÖ®Öä
void AssaParticle_Benedic(Unit *pChar)
{
	int i = GetAssaEffect();
	AssaSkill5Normal *motion = new AssaSkill5Normal;
	motion->Start(pChar,3,"Skill5KnightHolyBenedicHand1","Skill5KnightHolyBenedicHand2",SKILL_H_BENEDIC);
	
	cAssaEffect[i] = motion;
}
//ÉýÁúÖØ»÷
void AssaParticle_Moon2(Unit *pChar)
{
	POINT3D pos;
	pos.x = pChar->pX;
	pos.y = pChar->pY + 5000;
	pos.z = pChar->pZ;

	int partID = g_NewParticleMgr.Start("Skill5_Knight_CrescentMoon2",pos);

	POINT3D angle;
	angle.x = rand()%ANGLE_45;
	angle.y = rand()%ANGLE_360;
	angle.z = rand()%ANGLE_45;

	g_NewParticleMgr.SetAngle(partID, angle);

	SetDynLight(pos.x,pos.y,pos.z,100,50,0,0,250,5);
}
// ÉÏµÛÖØ»÷
void AssaParticle_Blade(Unit *pChar)
{
	POINT3D pos;

	pos.x = pChar->pX;
	pos.y = pChar->pY + 5000;
	pos.z = pChar->pZ;

	g_NewParticleMgr.Start("Skill5_Knight_SaintBlade1",pos);
	g_NewParticleMgr.Start("Skill5_Knight_SaintBlade2",pos);
}
// ÍöÁéÖ®Öä
void AssaParticle_Benedic2(Unit *pChar)
{
	int i = GetAssaEffect();
	AssaSkillBenedic *motion = new AssaSkillBenedic;
	motion->Start(pChar);
	cAssaEffect[i] = motion;
}
//ÇáÎè·ÉÑï
void AssaParticle_Taltria(Unit *pChar)
{
	POINT3D charPos;
	charPos.x = pChar->pX;
	charPos.y = pChar->pY;
	charPos.z = pChar->pZ;
	g_NewParticleMgr.Start("Skill5_Atalanta_Talaria_StartEffect",charPos);
}
//ÇáÎè·ÉÑïÐ§¹û
void AssaParticle_TaltriaEffect(Unit *pChar,int LiveCount)
{
	int SkillTime = LiveCount*70+2;

	if (AddAssaCodeEffectTime(pChar,SKILL_TALARIA,SkillTime) == 0)
	{
		POINT3D pos;
		pos.x = pChar->pX;
		pos.y = pChar->pY;
		pos.z = pChar->pZ;

		g_NewParticleMgr.Start("Skill5_Atalanta_Talaria_EndEffect",pos);

		int i = GetAssaEffect();
		AssaSkillTalaria *motion = new AssaSkillTalaria;
		motion->Start(pChar,LiveCount);
		cAssaEffect[i] = motion;
	}
}
//ÐÇÓê±êÇ¹
void AssaParticle_G_Coup(Unit *pChar)
{
	POINT3D pos;
	auto sPosition = GetMoveLocation(0, 0, 0, 0, pChar->Angle.y, 0);
	pos.x = pChar->pX + sPosition.iX;
	pos.y = pChar->pY + 3000;
	pos.z = pChar->pZ + sPosition.iZ;

	g_NewParticleMgr.Start("Skill5_Atalanta_Galaxy_CoupEffect",pos);
}
void AssaParticle_G_Coup_Effect(POINT3D* pCur, POINT3D* pDest, int count)
{
	for(int index = 0; index < count; index++)
	{
		POINT3D worldPos;
		auto sPosition = GetMoveLocation(0, 5 * fONE, 0, 0, 0, ANGLE_360 / count * index);

		memcpy(&worldPos,pCur,sizeof(POINT3D));
		worldPos.x += sPosition.iX;
		worldPos.y += sPosition.iY + 120 * fONE;
		worldPos.z += sPosition.iZ;

		pDest->x += sPosition.iX;
		pDest->y += sPosition.iY;
		pDest->z += sPosition.iZ;

		int i = GetAssaEffect();
		AssaSkillCoupEffect *splitJavelin = new AssaSkillCoupEffect;
		splitJavelin->Start(&worldPos, pDest, index*10);
		cAssaEffect[i] = splitJavelin;
	}
}
//±¿±¿ÐÜÐ§¹û
void AssaParticle_SummonArcuda(Unit *pChar)
{
	POINT3D pos;
	pos.x = pChar->pX;
	pos.y = pChar->pY;
	pos.z = pChar->pZ;

	g_NewParticleMgr.Start("Skill5_Atalanta_SummonArcuda_Effect",pos);
}
//ÁÒÑæÍ»Ï®
void AssaParticle_S_Fear(POINT3D *pCur,POINT3D *pDest)
{
	int i = GetAssaEffect();
	cASSAPARTSHOT *motion = new cASSAPARTSHOT;
	motion->Start(pCur,pDest,SKILL_S_FEAR);
	cAssaEffect[i] = motion;
}
// ¼¼ÄÜ´úÂë
void AssaCodeSkillEffect(char *pFileName, Unit *pChar,int Time,int SkillCode)
{
	int SkillTime = (Time + 2) * 70;
	if (AddAssaCodeEffectTime(pChar,SkillCode,SkillTime) == 0)
	{
		int i = GetAssaEffect();
		AssaSkillNormal *motion = new AssaSkillNormal;
		motion->Start(pFileName,pChar,Time,SkillCode);
		cAssaEffect[i] = motion;
	}
}
///°µºÚÉÁµç
void AssaDarkWaveEffect(Unit *pCurChar, Unit *pDestChar,int SkillCode)
{
	POINT3D curPos;

	curPos.x = pCurChar->pX;
	curPos.y = pCurChar->pY+5000;
	curPos.z = pCurChar->pZ;

	D3DVECTOR velocity;

	ZeroMemory(&velocity,sizeof(velocity));
	int i  = 0;

	if (SkillCode == SKILL_DARK_BOLT)
	{
		i = GetAssaEffect();
		AssaDarkSkill *motion = new AssaDarkSkill;

		velocity.x = 0.f;
		velocity.y = 0.f;
		velocity.z = 0.f;

		auto sPosition = GetMoveLocation(0, 0, 3 * fONE + rand() % (2 * fONE) - fONE, 0, pCurChar->Angle.y, 0);
		velocity.x += ((float)sPosition.iX*2.f / 256.f);
		velocity.z += ((float)sPosition.iZ*2.f / 256.f);

		motion->Start(&curPos,pDestChar,&velocity, 0,"DarkBolt",NULL,SKILL_DARK_BOLT);

		cAssaEffect[i] = motion;
	}
	else if (SkillCode == SKILL_DARK_WAVE)
	{
		int motionEvent = pCurChar->MotionEvent;

		if (motionEvent == 1)
		{
			i = GetAssaEffect();

			AssaDarkSkill *motion = new AssaDarkSkill;

			velocity.x = 0.f;
			velocity.y = 0.f;
			velocity.z = 0.f;

			auto sPosition = GetMoveLocation(0, 0, 3 * fONE + rand() % (2 * fONE) - fONE, 0, pCurChar->Angle.y - ANGLE_45, 0);

			velocity.x += ((float)sPosition.iX*2.f / 256.f);
			velocity.z += ((float)sPosition.iZ*2.f / 256.f);

			motion->Start(&curPos,pDestChar,&velocity, 0,"DarkWave1","DarkWave2",SKILL_DARK_WAVE);

			cAssaEffect[i] = motion;
		}
		else
		{
			i = GetAssaEffect();

			AssaDarkSkill *motion = new AssaDarkSkill;

			velocity.x = 0.f;
			velocity.y = 0.f;
			velocity.z = 0.f;

			auto sPosition = GetMoveLocation(0, 0, 3 * fONE + rand() % (2 * fONE) - fONE, 0, pCurChar->Angle.y + ANGLE_45, 0);

			velocity.x += ((float)sPosition.iX*2.f / 256.f);
			velocity.z += ((float)sPosition.iZ*2.f / 256.f);

			motion->Start(&curPos,pDestChar,&velocity, 0,"DarkWave1","DarkWave2",SKILL_DARK_WAVE);

			cAssaEffect[i] = motion;
		}
	}
	else if (SkillCode == MONSTER_PIGON_NAJAN)
	{
		i = GetAssaEffect();
		AssaDarkSkill *motion = new AssaDarkSkill;

		velocity.x = 0.f;
		velocity.y = 0.f;
		velocity.z = 0.f;

		auto sPosition = GetMoveLocation(0, 0, 3 * fONE + rand() % (2 * fONE) - fONE, 0, pCurChar->Angle.y, 0);
		velocity.x += ((float)sPosition.iX*2.f / 256.f);
		velocity.z += ((float)sPosition.iZ*2.f / 256.f);

		motion->Start(&curPos,pDestChar,&velocity, 0,"MonsterNajanHit",NULL,SKILL_DARK_BOLT);

		cAssaEffect[i] = motion;
	}
}
//ÉñÖ®±ùÈÐ
void AssaP_IceEffect(Unit *pCurChar, Unit *pDestChar)
{
	POINT3D curPos;

	curPos.x = pCurChar->pX;
	curPos.y = pCurChar->pY;
	curPos.z = pCurChar->pZ;

	D3DVECTOR velocity;

	int i = 0;

	i = GetAssaEffect();

	AssaDarkSkill *motion = new AssaDarkSkill;

	velocity.x = 0.f;
	velocity.y = 0.f;
	velocity.z = 0.f;

	auto sPosition = GetMoveLocation(0, 0, 0, 0, pCurChar->Angle.y + ANGLE_90, 0);

	velocity.x += ((float)sPosition.iX * 65535.f / 256.f);
	velocity.z += ((float)sPosition.iZ * 65535.f / 256.f);

	motion->Start(&curPos,pDestChar,&velocity, 0,"Skill5PriestessPiercingIce1","Skill5PriestessPiercingIce2",SKILL_P_ICE);

	cAssaEffect[i] = motion;
}
//ÌìÅ®É¢»¨
void Assa_KrishnaEffect(Unit *pChar)
{
	POINT3D pos;

	auto sPosition = GetMoveLocation(0, 0, 0, 0, pChar->Angle.y, 0);

	pos.x = pChar->pX + sPosition.iX;
	pos.y = pChar->pY;
	pos.z = pChar->pZ + sPosition.iZ;

	g_NewParticleMgr.Start("S5_Pr_BlessingKrishna_Effect",pos);
}
void Assa_KrishnaEffect(Unit *pChar,int LiveCount)
{
	int i = GetAssaEffect();

	AssaSkillKrishna *motion = new AssaSkillKrishna;
	motion->Start(pChar,LiveCount);

	cAssaEffect[i] = motion;
}
//ÍöÁéÖ®Öä
void Assa_Benedic(Unit *pChar,int LiveCount)
{
	int i = GetAssaEffect();

	AssaSkillBenedicEffect *motion = new AssaSkillBenedicEffect;
	motion->Start(pChar,LiveCount);

	cAssaEffect[i] = motion;
}
//ÉñÊ¥Ï´Àñ
void AssaParticle_Ignis(Unit *pChar,int blendType,int Count)
{
	D3DVECTOR velocity;
	POINT3D curPos;
	curPos.x = pChar->pX;
	curPos.y = pChar->pY + 20000;
	curPos.z = pChar->pZ;

	POINT3D desPos;
	desPos.x = pChar->pX;
	desPos.y = pChar->pY;
	desPos.z = pChar->pZ;

	for(int index = 0; index < Count; index++)
	{
		auto sPosition = GetMoveLocation(0, 12 * fONE, -5 * fONE, 0, index*(ANGLE_45 + ANGLE_45 / 2 + GetRandomPos(0, ANGLE_45)), 0);

		velocity.x = (float)sPosition.iX / 256.f;
		velocity.y = (float)sPosition.iY / 256.f;
		velocity.z = (float)sPosition.iZ / 256.f;

		if(index == 0)
		{
			desPos.x = pChar->pX;
			desPos.y = pChar->pY;
			desPos.z = pChar->pZ;
		}
		else
		{
			desPos.x = pChar->pX + sPosition.iX * 8;
			desPos.y = pChar->pY;
			desPos.z = pChar->pZ + sPosition.iZ * 8;
		}

		int i = GetAssaEffect();
		AssaRunicGuardianBossShot *runicGuardianBossShot = new AssaRunicGuardianBossShot;
		runicGuardianBossShot->Start(&curPos, &desPos, &velocity, blendType);
		cAssaEffect[i] = runicGuardianBossShot;
		if(index == 0)
			runicGuardianBossShot->SetHitFlag(true);
	}
}
bool AddAssaCodeEffectTime(Unit *pChar, int code, int time)
{
	for(int i = 0; i < cASSAEFFECT_MAX; i++)
	{
		if (cAssaEffect[i])
		{
			if (cAssaEffect[i]->CODE == code)
			{
				if (cAssaEffect[i]->pChar == pChar)
				{
   					cAssaEffect[i]->Time		= 0;
					cAssaEffect[i]->Max_Time	= time;
					return true;
				}
			}
		}
	}
	return false;
}
int AddAssaCodeEffectTime(Unit *pChar,int Code)
{
	for(int i = 0; i < cASSAEFFECT_MAX; i++)
	{
		if (cAssaEffect[i])
		{
			if (cAssaEffect[i]->CODE == Code)
			{
				if (cAssaEffect[i]->pChar == pChar)
				{
					cAssaEffect[i]->Max_Time += 30;
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}
int StopAssaCodeEffect(Unit *pChar, int code, int setTime)
{
    for(int i = 0; i < cASSAEFFECT_MAX; i++)
	{
		if(cAssaEffect[i])
		{
			if(cAssaEffect[i]->CODE == code)
			{
				if(cAssaEffect[i]->pChar == pChar)
				{
   					if(setTime == 0)
					{
 			 			if(cAssaEffect[i]->Time < cAssaEffect[i]->Max_Time-70*4)
							cAssaEffect[i]->Time = cAssaEffect[i]->Max_Time-70*4;
					}
					else
					{
						if(cAssaEffect[i]->Time < cAssaEffect[i]->Max_Time-setTime)
							cAssaEffect[i]->Time = cAssaEffect[i]->Max_Time-setTime;
					}
				}
			}
		}
	}

	return true;
}
int GetAssaEffect()
{
	for(int i = 0; i < cASSAEFFECT_MAX; i++)
	{
		if(!cAssaEffect[i])
			return i;
	}
	return -1;
}
DWORD GetTableNum(int n)
{
	int total = 0;
	DWORD	dwData=0;

	for (int a = 0; a <= 19; a++)
	{
		for (int b = 0; b <= 19; b++)
		{
			for(int c = 0; c <= 19; c++)
			{
				for(int d = 0; d <= 19; d++)
				{
					if(total != n)
						total++;
					else
					{
						dwData = Park_VarEncode(a,b,c,d);
						return dwData;
					}
				}
			}
		}
	}
	return -1;
}
DWORD Park_VarEncode(int a, int b, int c, int d)
{
	DWORD dw_Code1,dw_Code2,dw_Code3,dw_Code4;
	DWORD dwData = 0;

	dw_Code1 = dw_Code2 = dw_Code3 = dw_Code4 = 0;

	dw_Code1 = (a | 0x00000000) << 24;
	dw_Code2 = (b | 0x00000000) << 16;
	dw_Code3 = (c | 0x00000000) << 8;
	dw_Code4 = (d | 0x00000000) ;
	
	dwData = dw_Code1 | dw_Code2 | dw_Code3 | dw_Code4;

	return dwData;
}
void Park_VarDecode(DWORD dwData, int &nData1, int &nData2, int &nData3, int &nData4)
{
	nData1 = (dwData >> 24) & 0xff;
	nData2 = (dwData >> 16) & 0x00ff;
	nData3 = (dwData >> 8) & 0x0000ff;
	nData4 = dwData & 0x000000ff;
}