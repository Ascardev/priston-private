#include "StdAfx.h"	
#include "..\\HoBaram\\HoNewParticleLinkHeader.h" //»õ·Î¿î È£¹Ù¶÷


/*----------------------------------------------------------------------------*
*							Key Down
*-----------------------------------------------------------------------------*/
int TestNum = 0;
int sinAssaSkillEffectKeyDown()
{
	POINT3D Posi = { lpCurPlayer->pX,lpCurPlayer->pY,lpCurPlayer->pZ };

	if (sinGetKeyClick('0'))
		sinEffect_StartMagic(&Posi, CHARACTERCLASS_Magician, TRUE);
	return TRUE;
}

/*----------------------------------------------------------------------------*
*							Process
*-----------------------------------------------------------------------------*/
int sinAssaSkillEffectProcess(cASSAEFFECT *pEffect)
{
	switch (pEffect->CODE)
	{
	case SKILL_PIERCING:
		if (pEffect->Time == 1)
			pEffect->Obj = pEffect->pChar->AnimPattern->GetObjectFromName("Bip weapon01");

		AssaSearchObjPos(pEffect->pChar, pEffect->Obj, &pEffect->CenterPosi);
		if (pEffect->ActionIndex[3] == 1)
		{
			if (pEffect->GatherSpeed > 1)
			{
				pEffect->GatherSpeed -= pEffect->Time / 4;
				if (pEffect->GatherSpeed < 1)
					pEffect->GatherSpeed = 1;
			}

			pEffect->TempPosi.x = pEffect->CenterPosi.x - pEffect->Posi.x;
			pEffect->TempPosi.y = pEffect->CenterPosi.y - pEffect->Posi.y;
			pEffect->TempPosi.z = pEffect->CenterPosi.z - pEffect->Posi.z;

			pEffect->Posi.x += pEffect->TempPosi.x / pEffect->GatherSpeed;
			pEffect->Posi.y += pEffect->TempPosi.y / pEffect->GatherSpeed;
			pEffect->Posi.z += pEffect->TempPosi.z / pEffect->GatherSpeed;
		}

		if (pEffect->Bone)
		{
			if ((pEffect->Time == 1))
			{

			}
			if ((pEffect->Time % 3) == 0)
			{
				AssaParticle_RisingParticleContinue(&pEffect->CenterPosi, "star05B_02.bmp", 500, 128, GetRandomPos(20, 80));
				AssaParticle_After_Image(&pEffect->CenterPosi, "star01B_04.bmp", 16, 0);
			}
			if (pEffect->Time == 40)
			{

			}
		}
		break;
	case SKILL_WINDY:
		AssaSearchWeaponPos(pEffect->pChar, &pEffect->CenterPosi, 0);
		if (pEffect->ActionIndex[3] == 1)
		{
			if (pEffect->GatherSpeed > 1)
			{
				pEffect->GatherSpeed -= pEffect->Time / 4;
				if (pEffect->GatherSpeed < 1)
					pEffect->GatherSpeed = 1;
			}
			pEffect->TempPosi.x = pEffect->CenterPosi.x - pEffect->Posi.x;
			pEffect->TempPosi.y = pEffect->CenterPosi.y - pEffect->Posi.y;
			pEffect->TempPosi.z = pEffect->CenterPosi.z - pEffect->Posi.z;

			pEffect->Posi.x += pEffect->TempPosi.x / pEffect->GatherSpeed;
			pEffect->Posi.y += pEffect->TempPosi.y / pEffect->GatherSpeed;
			pEffect->Posi.z += pEffect->TempPosi.z / pEffect->GatherSpeed;
		}
		if (pEffect->Bone)
		{
			if (pEffect->Time == 10)
				sinSkillEffect_Windy_Gather(pEffect->pChar);
			if (pEffect->Time == 37)
				AssaParticle_Windy2(pEffect->pChar);
		}
		break;
	case SKILL_HOLY_REFLECTION:
		if (pEffect->Bone)
			AssaParticle_Holy_Reflection(pEffect);
		if (pEffect->ActionIndex[0] == 1)
		{
			pEffect->RDistance.z += pEffect->Time / 4;
			pEffect->Gravity -= 2;
			pEffect->Posi.y += pEffect->Gravity;
			pEffect->Angle.y += 10; pEffect->Angle.y &= ANGCLIP;
			pEffect->Angle.x += 10; pEffect->Angle.x &= ANGCLIP;
			pEffect->Angle.z += 10; pEffect->Angle.z &= ANGCLIP;
		}
		else if (pEffect->ActionIndex[1] == 1)
		{
			if (pEffect->Time < 10)
				pEffect->Size.w += 400;
			else
				pEffect->Size.w -= 400;
		}
		else if (pEffect->ActionIndex[1] == 2)
		{

		}
		else
		{
			pEffect->Gravity -= 2;
			pEffect->Posi.y += pEffect->Gravity;
		}
		break;
	case SKILL_GRAND_HEALING:
		pEffect->Angle.y = -((pEffect->RAngle) + ANGLE_270)&ANGCLIP;

		break;
	case SKILL_SOUL_SUCKER:
		if (pEffect->GatherSpeed > 1)
		{
			pEffect->GatherSpeed -= pEffect->Time / 4;
			if (pEffect->GatherSpeed < 1)
				pEffect->GatherSpeed = 1;
		}
		pEffect->TempPosi.x = pEffect->CenterPosi.x - pEffect->Posi.x;
		pEffect->TempPosi.y = pEffect->CenterPosi.y - pEffect->Posi.y;
		pEffect->TempPosi.z = pEffect->CenterPosi.z - pEffect->Posi.z;

		pEffect->Posi.x += pEffect->TempPosi.x / pEffect->GatherSpeed;
		pEffect->Posi.y += pEffect->TempPosi.y / pEffect->GatherSpeed;
		pEffect->Posi.z += pEffect->TempPosi.z / pEffect->GatherSpeed;

		break;
	case SKILL_HOLY_MIND:
		if ((pEffect->Time % 3) == 0)
			AssaParticle_HolyMind(&pEffect->Posi);
		break;
	}
	return TRUE;
}
/*----------------------------------------------------------------------------*
*						(Knight) Brandish
*-----------------------------------------------------------------------------*/
int sinSkillEffect_Brandish(Unit *pChar)
{

	for (int i = 0; i < 2; i++)
	{
		Assa = SetAssaEffect(0, "Brabdish.ASE", pChar, 0, 0);
		cAssaEffect[Assa]->AniMaxCount = 20;
		cAssaEffect[Assa]->AniDelayTime = 2;
		cAssaEffect[Assa]->StartPosi.x = 256 * 8 * 6;
		cAssaEffect[Assa]->Angle.y = ((pChar->Angle.y&ANGCLIP) + ANGLE_270)&ANGCLIP;
		AssaSetStartPosi(cAssaEffect[Assa]);
		cAssaEffect[Assa]->Angle.y = -((pChar->Angle.y&ANGCLIP))&ANGCLIP;
		AssaParticle_SpecialHit2(&cAssaEffect[Assa]->Posi, 0);
	}
	SetDynLight(cAssaEffect[Assa]->Posi.x, cAssaEffect[Assa]->Posi.y, cAssaEffect[Assa]->Posi.z, 255, 120, 0, 255, 200, 1);
	return TRUE;
}

/*----------------------------------------------------------------------------*
*						(Knight) Piercing
*-----------------------------------------------------------------------------*/
int sinSkillEffect_Piercing_Attack(Unit *pChar) //ÇÇ¾î½Ì °ø°Ý 
{
	Assa = SetAssaEffect(30, "Piercing.ASE", pChar, 0, 0);
	cAssaEffect[Assa]->NotFadeIn = 1;
	AssaParticle_Piercing(cAssaEffect[Assa]); //µÎ°³Âï¾îÁØ´Ù

	return TRUE;
}
int sinSkillEffect_Piercing(Unit *pChar)
{
	POINT3D TempPosi = { pChar->pX,pChar->pY,pChar->pZ };
	int TempIndex = 0, Temp4 = 0;

	AssaParticle_Char_Light2(pChar, ASSA_COLOR_CODE_BLUE, 70);

	SetDynLight(pChar->pX, pChar->pY, pChar->pZ, 0, 150, 255, 255, 130, 1);

	Assa = SetAssaEffect(60, "Bone", pChar, 0, 7000);
	cAssaEffect[Assa]->CODE = SKILL_PIERCING;

	for (int i = 0; i < 6; i++)
	{
		Assa = SetAssaEffect(200, "star05B_03.bmp", pChar, 0, pChar->PatHeight - 2500);
		cAssaEffect[Assa]->Size.w = 4000;
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE_RANDOM_ROTATE;
		cAssaEffect[Assa]->RAngleSpeed = 100;
		cAssaEffect[Assa]->MoveSpeed.z = 256 * 2;
		cAssaEffect[Assa]->Angle.x = GetRandomPos(0, 4096);
		cAssaEffect[Assa]->Angle.y = GetRandomPos(0, 4096);
		cAssaEffect[Assa]->CODE = SKILL_PIERCING;
	}
	return TRUE;
}

/*----------------------------------------------------------------------------*
*						(Knight) Drastic Spirit
*-----------------------------------------------------------------------------*/
int sinSkillEffect_DrasticSpirit(Unit *pChar)
{
	POINT3D TempPosi = { pChar->pX,pChar->pY - 2000,pChar->pZ };
	SetDynLight(pChar->pX, pChar->pY, pChar->pZ, 50, 50, 255, 255, 200, 1);

	Assa = SetAssaEffect(0, "DrasticSpirit.ASE", pChar, 0, 0);
	cAssaEffect[Assa]->AniMaxCount = 30;
	cAssaEffect[Assa]->AniDelayTime = 2;

	AssaParticle_RotateWide(&TempPosi, "star06B_04.bmp", 256, 400);
	AssaParticle_RisingParticle(&TempPosi, "star04B_01.bmp", 1000, 1, 1000, 3, 200);

	Assa = SetAssaEffect(0, "DrasticSpirit.ASE", pChar, 0, 0);
	cAssaEffect[Assa]->AniMaxCount = 30;
	cAssaEffect[Assa]->AniDelayTime = 2;

	Assa = SetAssaEffect(100, "helmet01.bmp", 0, &TempPosi, 15000);
	cAssaEffect[Assa]->Size.w = 6000;
	cAssaEffect[Assa]->ReSize.w = 100;
	cAssaEffect[Assa]->ReSize.h = cAssaEffect[Assa]->ReSize.w;
	cAssaEffect[Assa]->MOVECODE = ASSA_INCRESIZE;
	cAssaEffect[Assa]->Time = -70;
	cAssaEffect[Assa]->MOVECODE = ASSA_MOVE | ASSA_INCRESIZE;

	TempPosi.y += 15000;

	return TRUE;
}
//¿ñÒ°³å»÷
int sinSkillEffect_P_Dash(Unit *pChar)
{
	for (int i = 0; i < 2; i++)
	{
		Assa = SetAssaEffect(0, "PowerDash.ASE", pChar, 0, 0);
		cAssaEffect[Assa]->AniMaxCount = 20;
		cAssaEffect[Assa]->AniDelayTime = 2;
		cAssaEffect[Assa]->StartPosi.x = fONE * 4;
		cAssaEffect[Assa]->Angle.y = ((pChar->Angle.y&ANGCLIP) + ANGLE_270)&ANGCLIP;
		AssaSetStartPosi(cAssaEffect[Assa]);
		cAssaEffect[Assa]->Angle.y = -((pChar->Angle.y&ANGCLIP))&ANGCLIP;
		AssaParticle_SpecialHit2(&cAssaEffect[Assa]->Posi, 0);
	}
	SetDynLight(cAssaEffect[Assa]->Posi.x, cAssaEffect[Assa]->Posi.y, cAssaEffect[Assa]->Posi.z, 255, 120, 0, 255, 200, 1);
	return TRUE;
}
/*----------------------------------------------------------------------------*
*						(Wizard) Energy Shelter
*-----------------------------------------------------------------------------*/
int sinSkillEffect_Energy_Shelter(Unit *pChar)
{
	return TRUE;


}
/*----------------------------------------------------------------------------*
*						(Saintess) Great Healing
*-----------------------------------------------------------------------------*/
int sinSkillEffect_Great_Healing(Unit *pChar)
{
	int Temp = 1, Temp2 = 1, Temp4 = 1;
	SetDynLight(pChar->pX, pChar->pY, pChar->pZ, 255, 150, 100, 150, 180, 1);
	//³¯°³ 
	for (int i = 0; i < 2; i++) {
		Assa = SetAssaEffect(0, "GH.ASE", pChar, 0, 0);
		cAssaEffect[Assa]->AniMaxCount = 30;
		cAssaEffect[Assa]->AniDelayTime = 4;
		//cAssaEffect[Assa]->NotFadeIn = 1;
		cAssaEffect[Assa]->MOVECODE = ASSA_CHAR_POSI;
		cAssaEffect[Assa]->Time = i * -30;

	}

	for (int i = 0; i < 20; i++) {
		Assa = SetAssaEffect(200, "star04Y_01.bmp", pChar, 0, 7000);    //±âº»ÀûÀ¸·Î CharÀÏ°æ¿ì´Â AngleY¸¦ Àâ¾ÆÁÖ±â¶§¹®¿¡ ÃÊ±âÈ­ÇØÁØ´Ù
		//cAssaEffect[Assa]->Angle.y = GetRandomPos(0,2046); //Angle À» ÃÊ±âÈ­ÇØÁØ´Ù 
		cAssaEffect[Assa]->Angle.y = 0;
		cAssaEffect[Assa]->Size.w = 1000;
		AssaGetAniFileMat(cAssaEffect[Assa]);
		cAssaEffect[Assa]->AniCount = GetRandomPos(0, cAssaEffect[Assa]->AniMaxCount);
		cAssaEffect[Assa]->AniDelayTime = GetRandomPos(30, 45);
		cAssaEffect[Assa]->AniReverse = 1;
		cAssaEffect[Assa]->StartPosi.z = GetRandomPos(256 * 16, 256 * 32);
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE;
		if (Temp > 0)Temp = -1;
		else Temp = 1;
		cAssaEffect[Assa]->MoveSpeed.y = 10 * Temp;
		AssaSetStartPosi(cAssaEffect[Assa]);
	}

	for (int i = 0; i < 10; i++) {
		//È¸Àü ¶óÀÎ
		Assa = SetAssaEffect(120, "star06Y_04.bmp", pChar, 0, 0);
		cAssaEffect[Assa]->Size.w = 1000;
		cAssaEffect[Assa]->MoveSpeed.y = 300;
		AssaGetCirclePosi(cAssaEffect[Assa], 256 * 8, GetRandomPos(0, 4096));
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE | ASSA_ROTATE | ASSA_CHAR_POSI;
		if (Temp4 > 0)Temp4 = -1;
		else Temp4 = 1;
		cAssaEffect[Assa]->RAngleSpeed = 50 * Temp4;
		cAssaEffect[Assa]->Time = GetRandomPos(-5 * i, -i * 4);
		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_TRACE;
		cAssaEffect[Assa]->cAssaTrace->SetLength(30); //¿¬°á±æÀÌ¸¦ Àâ´Â´Ù
		cAssaEffect[Assa]->NotFadeIn = 1;
	}
	return TRUE;
}

int sinSkillEffect_Great_Healing_Party(Unit *pChar)
{
	POINT3D TempPosi = { pChar->pX,pChar->pY,pChar->pZ };
	int Temp = 1, Temp2 = 1, Temp3 = 1, Temp4 = 1;;

	SetDynLight(pChar->pX, pChar->pY, pChar->pZ, 255, 150, 100, 150, 100, 1);
	for (int i = 0; i < 4; i++) {
		///////¶óÀÎ  
		Assa = SetAssaEffect(120, "fire01_02.bmp", pChar, 0, 0);
		cAssaEffect[Assa]->Size.w = 600;
		cAssaEffect[Assa]->MoveSpeed.y = 300;
		AssaGetCirclePosi(cAssaEffect[Assa], 256 * 6, GetRandomPos(0, 4096));
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE | ASSA_ROTATE | ASSA_CHAR_POSI;
		if (Temp > 0)Temp = -1;
		else Temp = 1;
		cAssaEffect[Assa]->RAngleSpeed = 100 * Temp;
		cAssaEffect[Assa]->Time = GetRandomPos(-5 * i, -i * 4);
		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_TRACE;
		cAssaEffect[Assa]->cAssaTrace->SetLength(30); //¿¬°á±æÀÌ¸¦ Àâ´Â´Ù
		cAssaEffect[Assa]->NotFadeIn = 1;

		/////// ÆÄÆ¼Å¬  
		Assa = SetAssaEffect(120, "star01Y_01.bmp", pChar, 0, 0);
		cAssaEffect[Assa]->Size.w = 2000;
		cAssaEffect[Assa]->MoveSpeed.y = 200;
		AssaGetCirclePosi(cAssaEffect[Assa], 256 * 8, GetRandomPos(0, 4096));
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE | ASSA_ROTATE | ASSA_CHAR_POSI;
		if (Temp2 > 0)Temp2 = -1;
		else Temp2 = 1;
		cAssaEffect[Assa]->RAngleSpeed = 50 * Temp2;
		cAssaEffect[Assa]->Time = GetRandomPos(-5 * i, -i * 4);
		cAssaEffect[Assa]->cAssaTrace->SetLength(30); //¿¬°á±æÀÌ¸¦ Àâ´Â´Ù
		cAssaEffect[Assa]->NotFadeIn = 1;
		AssaGetAniFileMat(cAssaEffect[Assa]);
		cAssaEffect[Assa]->AniDelayTime = GetRandomPos(10, 15);
		cAssaEffect[Assa]->AniCount = GetRandomPos(0, cAssaEffect[Assa]->AniMaxCount);

		//¸Þ½¬ 
		Assa = SetAssaEffect(70, "GreatHealing.ASE", pChar, 0, 4000);
		cAssaEffect[Assa]->AniMaxCount = 32;
		cAssaEffect[Assa]->AniDelayTime = 4;
		AssaGetCirclePosi(cAssaEffect[Assa], 256 * 8, GetRandomPos(0, 4096));
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE | ASSA_ROTATE | ASSA_CHAR_POSI;
		cAssaEffect[Assa]->MoveSpeed.y = 200;
		if (Temp3 > 0)Temp3 = -1;
		else Temp3 = 1;
		cAssaEffect[Assa]->RAngleSpeed = 50 * Temp3;
		cAssaEffect[Assa]->CODE = SKILL_GRAND_HEALING;
		cAssaEffect[Assa]->Time = GetRandomPos(-5 * i, -i * 4);

		//È¸Àü 
		Assa = SetAssaEffect(120, "star06Y_04.bmp", pChar, 0, 0);
		cAssaEffect[Assa]->Size.w = 1000;
		//cAssaEffect[Assa]->MoveSpeed.y = 300;
		AssaGetCirclePosi(cAssaEffect[Assa], 256 * 7, GetRandomPos(0, 4096));
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE | ASSA_ROTATE | ASSA_CHAR_POSI;
		if (Temp4 > 0)Temp4 = -1;
		else Temp4 = 1;
		cAssaEffect[Assa]->RAngleSpeed = 50 * Temp4;
		cAssaEffect[Assa]->Time = GetRandomPos(-5 * i, -i * 4);
		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE;
		cAssaEffect[Assa]->ScalePosi.y = 15000;
		cAssaEffect[Assa]->NotFadeIn = 1;

		//¶ó¿îµå ¸µ 
		if (i < 2) {
			Assa = SetAssaEffect(140, "ground_ring.bmp", pChar, 0, 1200 - ((i + 1) * 300));
			cAssaEffect[Assa]->Size.w = 3000 * (i + 2);
			cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_WORLD;
			cAssaEffect[Assa]->MOVECODE = ASSA_ANGLE_ROTATE | ASSA_CHAR_POSI;
			cAssaEffect[Assa]->ARotateSpeed.y = 30;
		}
	}
	return TRUE;
}

/*----------------------------------------------------------------------------*
*						(Valkyrie) Soul Sucker
*-----------------------------------------------------------------------------*/
int sinSkillEffect_Soul_Sucker(Unit *pChar, Unit *DesChar)
{

	int Temp = 1, TempIndex = 0, Temp2 = 1, Temp3 = 1, Temp4 = 1;
	POINT3D Posi2;
	int TempTime = -10;
	if (!DesChar)return FALSE;
	SetDynLight(DesChar->pX, DesChar->pY, DesChar->pZ, 255, 180, 100, 150, 130, 1);
	//¿µÈ¥ÀÌ ºüÁ®³ª°¨

	Assa = SetAssaEffect(150, "etc01_01.bmp", DesChar, 0, DesChar->PatHeight + 1000);
	cAssaEffect[Assa]->Size.w = 5000;
	cAssaEffect[Assa]->Size.h = 10000;
	cAssaEffect[Assa]->AniDelayTime = 15;
	cAssaEffect[Assa]->MOVECODE = ASSA_MOVE;
	cAssaEffect[Assa]->MoveSpeed.y = 100;
	AssaGetAniFileMat(cAssaEffect[Assa]);
	cAssaEffect[Assa]->Time = TempTime;


	Posi2 = cAssaEffect[Assa]->Posi;
	Posi2.y -= 4000;

	//AssaTest_Shot(&cAssaEffect[Assa]->Posi);
	AssaParticle_SpecialHit(&Posi2, 0);
	for (int i = 0; i < 3; i++) {
		Assa = SetAssaEffect(80, "fire01_02.bmp", DesChar, 0, DesChar->PatHeight - 2500);
		cAssaEffect[Assa]->Size.w = 2000;
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE | ASSA_CHAR_POSI;
		if (i == 0) {
			cAssaEffect[Assa]->MoveSpeed.y = 500;
		}
		if (i == 1) {
			cAssaEffect[Assa]->MoveSpeed.x = 500;
			cAssaEffect[Assa]->MoveSpeed.z = 500;
		}
		if (i == 2) {
			cAssaEffect[Assa]->MoveSpeed.x = -500;
			cAssaEffect[Assa]->MoveSpeed.z = -500;
		}
		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_TRACE;
		cAssaEffect[Assa]->cAssaTrace->SetLength(10); //¿¬°á±æÀÌ¸¦ Àâ´Â´Ù
		cAssaEffect[Assa]->CenterPosi.x = pChar->pX;
		cAssaEffect[Assa]->CenterPosi.y = pChar->pY + pChar->PatHeight - 2500;
		cAssaEffect[Assa]->CenterPosi.z = pChar->pZ;
		cAssaEffect[Assa]->GatherSpeed = 80;
		cAssaEffect[Assa]->CODE = SKILL_SOUL_SUCKER;
		cAssaEffect[Assa]->NotFadeIn = 1;
		cAssaEffect[Assa]->Time = TempTime;
		TempIndex = Assa;

		//±¸½½... 
		Assa = SetAssaEffect(80, "star02Y_03.bmp", DesChar, 0, cAssaEffect[Assa]->AddHeight);
		cAssaEffect[Assa]->Size.w = 10000;
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE | ASSA_CHAR_POSI;
		cAssaEffect[Assa]->MoveSpeed.x = cAssaEffect[TempIndex]->MoveSpeed.x;
		cAssaEffect[Assa]->MoveSpeed.y = cAssaEffect[TempIndex]->MoveSpeed.y;
		cAssaEffect[Assa]->MoveSpeed.z = cAssaEffect[TempIndex]->MoveSpeed.z;
		cAssaEffect[Assa]->CenterPosi.x = cAssaEffect[TempIndex]->CenterPosi.x;
		cAssaEffect[Assa]->CenterPosi.y = cAssaEffect[TempIndex]->CenterPosi.y;
		cAssaEffect[Assa]->CenterPosi.z = cAssaEffect[TempIndex]->CenterPosi.z;
		cAssaEffect[Assa]->GatherSpeed = cAssaEffect[TempIndex]->GatherSpeed;
		cAssaEffect[Assa]->Time = TempTime;
		cAssaEffect[Assa]->CODE = SKILL_SOUL_SUCKER;//cAssaEffect[TempIndex]->CODE;
		//cAssaEffect[Assa]->NotFadeIn = 1;

		//¸öÀ»  °¨½Ñ´Ù 
		Assa = SetAssaEffect(60, "fire01_02.bmp", pChar, 0, pChar->PatHeight - 2500);
		cAssaEffect[Assa]->Size.w = 1000;
		cAssaEffect[Assa]->MoveSpeed.y = -300;
		AssaGetCirclePosi(cAssaEffect[Assa], 256 * 8, (i + 1) * 1200);
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE | ASSA_ROTATE | ASSA_CHAR_POSI;
		if (Temp3 > 0)Temp3 = -1;
		else Temp3 = 1;
		cAssaEffect[Assa]->RAngleSpeed = 50 * Temp3;
		cAssaEffect[Assa]->Time = GetRandomPos(-5 * i, -i * 4);
		cAssaEffect[Assa]->cAssaTrace->SetLength(30); //¿¬°á±æÀÌ¸¦ Àâ´Â´Ù
		cAssaEffect[Assa]->NotFadeIn = 1;
		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_TRACE;
		cAssaEffect[Assa]->Time = -30 + TempTime;

		//AssaParticle_Light(&cAssaEffect[Assa]->CenterPosi ,"light01-03.bmp", 5000,0,-30);
		//AssaParticle_Area_Particle(&cAssaEffect[Assa]->CenterPosi ,"star01Y_01.bmp", 16,-30); »ç¿ë¾ÈÇÔ
		///////////³¯Ä¡±â ÆÄÆ¼Å¬ 
		for (int j = 0; j < 3; j++) {
			Assa = SetAssaEffect(30, "star01Y_01.bmp", pChar, 0, pChar->PatHeight - 2500);
			cAssaEffect[Assa]->Size.w = 2000;
			cAssaEffect[Assa]->MoveSpeed.y = -200;
			AssaGetCirclePosi(cAssaEffect[Assa], 256 * 8, GetRandomPos(0, 4098));
			cAssaEffect[Assa]->MOVECODE = ASSA_MOVE | ASSA_ROTATE | ASSA_CHAR_POSI;
			if (Temp2 > 0)Temp2 = -1;
			else Temp2 = 1;
			cAssaEffect[Assa]->RAngleSpeed = 50 * Temp2;
			cAssaEffect[Assa]->Time = GetRandomPos(-5 * i, -i * 4);
			cAssaEffect[Assa]->NotFadeIn = 1;
			AssaGetAniFileMat(cAssaEffect[Assa]);
			cAssaEffect[Assa]->AniDelayTime = GetRandomPos(10, 15);
			cAssaEffect[Assa]->AniCount = GetRandomPos(0, cAssaEffect[Assa]->AniMaxCount);
			cAssaEffect[Assa]->Time = -30 + TempTime;

			////////¶óÀÎÀ¸·Î °¨½Ñ´Ù 
			//È¸Àü 
			Assa = SetAssaEffect(50, "star06Y_04.bmp", pChar, 0, 3000);
			cAssaEffect[Assa]->Size.w = 800;
			cAssaEffect[Assa]->MoveSpeed.y = -200;
			AssaGetCirclePosi(cAssaEffect[Assa], 256 * 7, GetRandomPos(0, 4096));
			cAssaEffect[Assa]->MOVECODE = ASSA_MOVE | ASSA_ROTATE | ASSA_CHAR_POSI;
			if (Temp4 > 0)Temp4 = -1;
			else Temp4 = 1;
			cAssaEffect[Assa]->RAngleSpeed = 50 * Temp4;
			cAssaEffect[Assa]->Time = GetRandomPos(-5 * i, -i * 4);
			cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE;
			cAssaEffect[Assa]->ScalePosi.y = 10000;
			cAssaEffect[Assa]->NotFadeIn = 1;
			cAssaEffect[Assa]->Time = -30 + TempTime;

		}
	}
	return TRUE;
}

/*----------------------------------------------------------------------------*
*						(Saintess) Holy Reflection
*-----------------------------------------------------------------------------*/
int sinSkillEffect_Holy_Reflection_Defense(Unit *pChar)
{
	int Temp = 1, Temp2 = 1;
	SetDynLight(pChar->pX, pChar->pY, pChar->pZ, 100, 50, 100, 150, 200, 1);
	Assa = SetAssaEffect(40, "HolyReflection-gu.ASE", pChar, 0, 0);
	cAssaEffect[Assa]->MOVECODE = ASSA_CHAR_POSI;
	//cAssaEffect[Assa]->Time = -10; //µ¿±â¸¦ ¸ÂÃß±âÀ§ÇØ Àá½Ã µô·¹ÀÌ¸¦ ÁØ´Ù 

	/*
	for(int i = 0 ; i < 3 ; i++){
		Assa = SetAssaEffect(120,"HolyReplection3.tga",pChar,0,3000);
		cAssaEffect[Assa]->Size.w = 600;
		cAssaEffect[Assa]->MoveSpeed.y = 200;
		AssaGetCirclePosi(cAssaEffect[Assa],256*12,GetRandomPos(0,4096));
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE | ASSA_ROTATE |ASSA_CHAR_POSI;
		if(Temp > 0 )Temp = -1;
		else Temp = 1;
		cAssaEffect[Assa]->RAngleSpeed = 50*Temp;
		//cAssaEffect[Assa]->Time = GetRandomPos(-5*i,-i*4);
		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_TRACE;
		cAssaEffect[Assa]->cAssaTrace->SetLength(30); //¿¬°á±æÀÌ¸¦ Àâ´Â´Ù
		cAssaEffect[Assa]->NotFadeIn = 1;
	}
	*/

	/*
	for(int i = 0 ; i < 30 ; i++){
		Assa = SetAssaEffect(100,"star01M_04.bmp",pChar,0,GetRandomPos(5000,10000));
		cAssaEffect[Assa]->Size.w = 500;
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE_SPREAD;
		cAssaEffect[Assa]->RAngle = rand()%4096;
		cAssaEffect[Assa]->RDistance.z = 64;
		cAssaEffect[Assa]->Gravity = 10;
		cAssaEffect[Assa]->MoveSpeed.y = 300;
		cAssaEffect[Assa]->NotFadeIn = 1;
	}
	*/

	for (int i = 0; i < 7; i++) {
		Assa = SetAssaEffect(100, "star01M_04.bmp", pChar, 0, 7000);    //±âº»ÀûÀ¸·Î CharÀÏ°æ¿ì´Â AngleY¸¦ Àâ¾ÆÁÖ±â¶§¹®¿¡ ÃÊ±âÈ­ÇØÁØ´Ù
		//cAssaEffect[Assa]->Angle.y = GetRandomPos(0,2046); //Angle À» ÃÊ±âÈ­ÇØÁØ´Ù 
		cAssaEffect[Assa]->Angle.y = 0;
		cAssaEffect[Assa]->Size.w = GetRandomPos(700, 1000);
		cAssaEffect[Assa]->StartPosi.z = GetRandomPos(256 * 15, 256 * 31);
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE;
		if (Temp > 0)Temp = -1;
		else Temp = 1;
		cAssaEffect[Assa]->MoveSpeed.y = 10 * Temp;
		AssaSetStartPosi(cAssaEffect[Assa]);
		//cAssaEffect[Assa]->Time = -10; //µ¿±â¸¦ ¸ÂÃß±âÀ§ÇØ Àá½Ã µô·¹ÀÌ¸¦ ÁØ´Ù 

	}


	return TRUE;
}

int sinSkillEffect_Holy_Reflection(Unit *pChar, int Time)
{
	SetDynLight(pChar->pX, pChar->pY, pChar->pZ, 100, 50, 100, 150, 200, 1);
	POINT3D TempPosi = { pChar->pX,pChar->pY,pChar->pZ };
	int Temp = 1, Temp2 = 1;

	Assa = SetAssaEffect(100, "Bone", pChar, 0, 14000);
	if (Assa < cASSAEFFECT_MAX)
		cAssaEffect[Assa]->CODE = SKILL_HOLY_REFLECTION;

	for (int i = 0; i < 2; i++)
	{
		Assa = SetAssaEffect(0, "2HolyReflection.ASE", pChar, 0, 14000);
		if (Assa < cASSAEFFECT_MAX)
		{
			cAssaEffect[Assa]->AniMaxCount = 30;
			cAssaEffect[Assa]->AniDelayTime = 4;
			cAssaEffect[Assa]->StartPosi.x = -256 * 10;
			cAssaEffect[Assa]->Angle.y = ((pChar->Angle.y&ANGCLIP) + ANGLE_270)&ANGCLIP;
			AssaSetStartPosi(cAssaEffect[Assa]);
			cAssaEffect[Assa]->Angle.y = (-(pChar->Angle.y&ANGCLIP) + ANGLE_180)&ANGCLIP;
			cAssaEffect[Assa]->ActionIndex[1] = 2;
			cAssaEffect[Assa]->CODE = SKILL_HOLY_REFLECTION;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		Assa = SetAssaEffect(70, "flare.tga", pChar, 0, 12500);
		if (Assa < cASSAEFFECT_MAX)
		{
			cAssaEffect[Assa]->Size.w = GetRandomPos(3000, 5000);
			cAssaEffect[Assa]->Size.h = GetRandomPos(200, 500);
			cAssaEffect[Assa]->FACEY = (i + 1)*(4096 / 6);
			cAssaEffect[Assa]->NotFadeIn = 1;
			cAssaEffect[Assa]->ActionIndex[1] = 1;
			cAssaEffect[Assa]->Face.r = 255;
			cAssaEffect[Assa]->Face.g = 150;
			cAssaEffect[Assa]->Face.b = 255;
			cAssaEffect[Assa]->CODE = SKILL_HOLY_REFLECTION;
			cAssaEffect[Assa]->Time = -90;
		}
	}
	for (int i = 0; i < 20; i++)
	{
		Assa = SetAssaEffect(100, "star05M_02.bmp", pChar, 0, 12500);
		if (Assa < cASSAEFFECT_MAX)
		{
			cAssaEffect[Assa]->Size.w = GetRandomPos(300, 500);
			cAssaEffect[Assa]->MOVECODE = ASSA_MOVE_ANGLE_SPEED;
			cAssaEffect[Assa]->MoveSpeed.z = GetRandomPos(20, 40);
			cAssaEffect[Assa]->Angle.y = 0;
			cAssaEffect[Assa]->Time = -90;
			cAssaEffect[Assa]->Gravity = 50;
			cAssaEffect[Assa]->CODE = SKILL_HOLY_REFLECTION;
		}
	}
	for (int i = 0; i < 50; i++)
	{
		Assa = SetAssaEffect(120, "flw.ase", pChar, 0, 12000);

		if (Assa < cASSAEFFECT_MAX)
		{
			cAssaEffect[Assa]->Size.w = GetRandomPos(700, 1500);
			AssaGetCirclePosi(cAssaEffect[Assa], GetRandomPos(256 * 4, 256 * 5), GetRandomPos(0, 4096));
			cAssaEffect[Assa]->MOVECODE = ASSA_MOVE | ASSA_ROTATE | ASSA_CHAR_POSI;
			if (Temp2 > 0)
				Temp2 = -1;
			else
				Temp2 = 1;
			cAssaEffect[Assa]->RAngleSpeed = GetRandomPos(20, 30)*Temp2;
			cAssaEffect[Assa]->Time = GetRandomPos(-50, 0) - 90;
			cAssaEffect[Assa]->Gravity = GetRandomPos(30, 50);
			cAssaEffect[Assa]->ActionIndex[0] = 1;
			cAssaEffect[Assa]->CODE = SKILL_HOLY_REFLECTION;
			cAssaEffect[Assa]->Angle.x = GetRandomPos(0, 4096);
			cAssaEffect[Assa]->Angle.y = GetRandomPos(0, 4096);
			cAssaEffect[Assa]->Angle.z = GetRandomPos(0, 4096);
			cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_WORLD;
		}
	}
	for (int i = 0; i < 2; i++)
	{
		Assa = SetAssaEffect(700, "mn.ASE", pChar, 0, 7000);
		if (Assa < cASSAEFFECT_MAX)
		{
			cAssaEffect[Assa]->MOVECODE = ASSA_ANGLE_ROTATE | ASSA_CHAR_POSI;
			cAssaEffect[Assa]->ARotateSpeed.y = 10;
			cAssaEffect[Assa]->Time = -90;
			cAssaEffect[Assa]->Max_Time = Time * 70;
			cAssaEffect[Assa]->ActionIndex[1] = 2;
			cAssaEffect[Assa]->CODE = SKILL_HOLY_REFLECTION;
			return TRUE;
		}
	}

	return TRUE;
}
int sinSkillEffect_Holy_ReflectionEffect(Unit *pChar, int Time)
{
	if (AddAssaCodeEffectTime(pChar, SKILL_HOLY_REFLECTION) == 0)
	{
		for (int i = 0; i < 2; i++)
		{
			Assa = SetAssaEffect(700, "mn.ASE", pChar, 0, 7000);
			if (Assa < cASSAEFFECT_MAX)
			{
				cAssaEffect[Assa]->MOVECODE = ASSA_ANGLE_ROTATE | ASSA_CHAR_POSI;
				cAssaEffect[Assa]->ARotateSpeed.y = 10;
				cAssaEffect[Assa]->Time = -90;
				cAssaEffect[Assa]->Max_Time = Time * 70;
				cAssaEffect[Assa]->ActionIndex[1] = 2;
				cAssaEffect[Assa]->CODE = SKILL_HOLY_REFLECTION;
				return TRUE;
			}
		}
	}
	return FALSE;
}
/*----------------------------------------------------------------------------*
*						(Valkyrie) sinSkillEffect_Twist_Javelin
*-----------------------------------------------------------------------------*/
int sinSkillEffect_Twist_Javelin(Unit *pChar, Unit *DesChar)
{
	Assa = SetAssaEffect(0, "TwistJavelin.ASE", pChar, 0, 7000);
	cAssaEffect[Assa]->AniMaxCount = 60;
	cAssaEffect[Assa]->AniDelayTime = 1;

	return TRUE;
}

/*----------------------------------------------------------------------------*
*						(Valkyrie) Windy
*-----------------------------------------------------------------------------*/
int sinSkillEffect_Windy(Unit *pChar)
{
	SetDynLight(pChar->pX, pChar->pY, pChar->pZ, 255, 180, 100, 150, 180, 1);
	Assa = SetAssaEffect(75, "Bone", pChar, 0, 7000);
	cAssaEffect[Assa]->CODE = SKILL_WINDY;
	AssaParticle_Char_Light2(pChar, ASSA_COLOR_CODE_YELLOW, 200);
	return TRUE;
}
int sinSkillEffect_Windy_Gather(Unit *pChar)
{
	int TempIndex, Temp4 = 1;
	//¼Õ¿¡ ±â°¡¸ðÀÎ´Ù À¸¶óÂ÷Â÷ 
	for (int i = 0; i < 3; i++) {
		Assa = SetAssaEffect(100, "fire11_02.bmp", pChar, 0, pChar->PatHeight - 2500);
		cAssaEffect[Assa]->Size.w = 1500;
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE | ASSA_CHAR_POSI;
		//cAssaEffect[Assa]->MoveSpeed.y = 500; 
		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_TRACE;
		cAssaEffect[Assa]->cAssaTrace->SetLength(10); //¿¬°á±æÀÌ¸¦ Àâ´Â´Ù

		cAssaEffect[Assa]->StartPosi.x = 256 * 8 * 4;
		cAssaEffect[Assa]->Angle.y = ((pChar->Angle.y&ANGCLIP) + ANGLE_270)&ANGCLIP;
		AssaSetStartPosi(cAssaEffect[Assa]);
		cAssaEffect[Assa]->Angle.y = 0;
		//cAssaEffect[Assa]->Angle.y =  -((pChar->Angle.y&ANGCLIP))&ANGCLIP;

		//AssaSearchWeaponPos(cAssaEffect[Assa]->pChar,&cAssaEffect[Assa]->CenterPosi,0);
		cAssaEffect[Assa]->CenterPosi.x = cAssaEffect[Assa]->Posi.x;
		cAssaEffect[Assa]->CenterPosi.y = cAssaEffect[Assa]->Posi.y + cAssaEffect[Assa]->pChar->PatHeight;
		cAssaEffect[Assa]->CenterPosi.z = cAssaEffect[Assa]->Posi.z;
		cAssaEffect[Assa]->GatherSpeed = 80;
		cAssaEffect[Assa]->CODE = SKILL_WINDY;
		cAssaEffect[Assa]->NotFadeIn = 1;
		cAssaEffect[Assa]->ActionIndex[3] = 1;

		AssaGetCirclePosi(cAssaEffect[Assa], 256 * 64, (i + 1)*(4096 / 3));
		TempIndex = Assa;

		//Assa = SetAssaEffect(80,"star05B_03.bmp",pChar,0,cAssaEffect[Assa]->AddHeight);                   
		Assa = SetAssaEffect(100, "star01Y_04.bmp", pChar, 0, cAssaEffect[Assa]->AddHeight);
		cAssaEffect[Assa]->Size.w = 4000;
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE | ASSA_CHAR_POSI;
		cAssaEffect[Assa]->MoveSpeed.x = cAssaEffect[TempIndex]->MoveSpeed.x;
		cAssaEffect[Assa]->MoveSpeed.y = cAssaEffect[TempIndex]->MoveSpeed.y;
		cAssaEffect[Assa]->MoveSpeed.z = cAssaEffect[TempIndex]->MoveSpeed.z;
		cAssaEffect[Assa]->CenterPosi.x = cAssaEffect[TempIndex]->CenterPosi.x;
		cAssaEffect[Assa]->CenterPosi.y = cAssaEffect[TempIndex]->CenterPosi.y;
		cAssaEffect[Assa]->CenterPosi.z = cAssaEffect[TempIndex]->CenterPosi.z;
		cAssaEffect[Assa]->GatherSpeed = cAssaEffect[TempIndex]->GatherSpeed;
		AssaGetCirclePosi(cAssaEffect[Assa], cAssaEffect[TempIndex]->RDistance.z, cAssaEffect[TempIndex]->RAngle);
		cAssaEffect[Assa]->ActionIndex[3] = 1;
		cAssaEffect[Assa]->CODE = SKILL_WINDY;//cAssaEffect[TempIndex]->CODE;
		cAssaEffect[Assa]->Posi.x = cAssaEffect[TempIndex]->Posi.x;
		cAssaEffect[Assa]->Posi.y = cAssaEffect[TempIndex]->Posi.y;
		cAssaEffect[Assa]->Posi.z = cAssaEffect[TempIndex]->Posi.z;


		for (int j = 0; j < 10; j++)
			AssaParticle_RisingParticleContinue(&cAssaEffect[Assa]->Posi, "star05G_02.bmp", 700, 200, GetRandomPos(40, 100));

	}
	/*
	for(int i = 0 ; i < 30 ; i++){
		Assa = SetAssaEffect(170,"star06G_04.bmp",pChar,0,-10000);
		cAssaEffect[Assa]->Size.w = 600;
		cAssaEffect[Assa]->MoveSpeed.y = 300;
		AssaGetCirclePosi(cAssaEffect[Assa],256*7,i*256);
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE | ASSA_ROTATE |ASSA_CHAR_POSI;
		if(Temp4 > 0 )Temp4 = -1;
		else Temp4 = 1;
		cAssaEffect[Assa]->RAngleSpeed = 25*Temp4;
		cAssaEffect[Assa]->Time = GetRandomPos(0,100);
		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE;
		cAssaEffect[Assa]->ScalePosi.y = 10000*2;
		//cAssaEffect[Assa]->NotFadeIn = 1;

	}
	*/

	return TRUE;
}
/*----------------------------------------------------------------------------*
*						 Holy Mind
*-----------------------------------------------------------------------------*/
int sinSkillEffect_HolyMind(Unit *pChar, int Time)
{
	Assa = SetAssaEffect(Time * 70, "bone", pChar, 0, pChar->PatHeight + 2000);
	cAssaEffect[Assa]->CODE = SKILL_HOLY_MIND;
	cAssaEffect[Assa]->MOVECODE = ASSA_CHAR_POSI;

	Assa = SetAssaEffect(Time * 70, "Holy_m2.bmp", pChar, 0, pChar->PatHeight + 2000);
	cAssaEffect[Assa]->Size.w = 5000;
	cAssaEffect[Assa]->MaxAlphaAmount = 100;
	cAssaEffect[Assa]->NotFadeIn = 1;
	cAssaEffect[Assa]->MOVECODE = ASSA_CHAR_POSI;

	return TRUE;
}
//ÉñÁ¦³å´Ì
int sinSkillEffect_Breaker(Unit *curChar, Unit *desChar)
{
	POINT3D pos;
	int TempIndex;

	pos.x = curChar->pX;
	pos.y = curChar->pY;
	pos.z = curChar->pZ;

	AssaParticle_Char_Light2(curChar, ASSA_COLOR_CODE_BLUE, 70);

	SetDynLight(pos.x, pos.y, pos.z, 0, 150, 255, 255, 130, 1);

	Assa = SetAssaEffect(60, "Bone", curChar, 0, 7000);
	cAssaEffect[Assa]->CODE = SKILL_S_BREAKER;

	for (int i = 0; i < 4; i++)
	{
		Assa = SetAssaEffect(80, "fire11_08.bmp", curChar, 0, curChar->PatHeight + 10000);
		cAssaEffect[Assa]->Size.w = 1500;
		cAssaEffect[Assa]->MOVECODE = ASSA_CHAR_POSI | ASSA_MOVE;
		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_TRACE;
		cAssaEffect[Assa]->cAssaTrace->SetLength(10);
		cAssaEffect[Assa]->CenterPosi.x = pos.x;
		cAssaEffect[Assa]->CenterPosi.y = pos.y + 10000 + cAssaEffect[Assa]->AddHeight;
		cAssaEffect[Assa]->CenterPosi.z = pos.z;
		cAssaEffect[Assa]->GatherSpeed = 80;
		cAssaEffect[Assa]->CODE = SKILL_S_BREAKER;
		cAssaEffect[Assa]->NotFadeIn = 1;
		cAssaEffect[Assa]->ActionIndex[3] = 1;
		AssaGetCirclePosi(cAssaEffect[Assa], 256 * 64, (i + 1)*(4096 / 3));

		TempIndex = Assa;

		Assa = SetAssaEffect(80, "star05B_03.bmp", curChar, 0, cAssaEffect[Assa]->AddHeight);
		cAssaEffect[Assa]->Size.w = 4000;
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE | ASSA_CHAR_POSI;
		cAssaEffect[Assa]->MoveSpeed.x = cAssaEffect[TempIndex]->MoveSpeed.x;
		cAssaEffect[Assa]->MoveSpeed.y = cAssaEffect[TempIndex]->MoveSpeed.y;
		cAssaEffect[Assa]->MoveSpeed.z = cAssaEffect[TempIndex]->MoveSpeed.z;

		cAssaEffect[Assa]->CenterPosi.x = cAssaEffect[TempIndex]->CenterPosi.x;
		cAssaEffect[Assa]->CenterPosi.y = cAssaEffect[TempIndex]->CenterPosi.y;
		cAssaEffect[Assa]->CenterPosi.z = cAssaEffect[TempIndex]->CenterPosi.z;

		cAssaEffect[Assa]->GatherSpeed = cAssaEffect[TempIndex]->GatherSpeed;

		AssaGetCirclePosi(cAssaEffect[Assa], cAssaEffect[TempIndex]->RDistance.z, cAssaEffect[TempIndex]->RAngle);
		cAssaEffect[Assa]->ActionIndex[3] = 1;
		cAssaEffect[Assa]->CODE = SKILL_S_BREAKER;

		for (int j = 0; j < 10; j++)
			AssaParticle_RisingParticleContinue(&cAssaEffect[Assa]->Posi, "star05B_02.bmp", 500, 128, GetRandomPos(20, 80));
	}
	for (int i = 0; i < 6; i++)
	{
		Assa = SetAssaEffect(200, "star05B_03.bmp", curChar, 0, curChar->PatHeight - 2500);
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE_RANDOM_ROTATE;
		cAssaEffect[Assa]->RAngleSpeed = 100;
		cAssaEffect[Assa]->MoveSpeed.z = fONE * 2;
		cAssaEffect[Assa]->Angle.x = GetRandomPos(0, 4096);
		cAssaEffect[Assa]->Angle.y = GetRandomPos(0, 4096);
		cAssaEffect[Assa]->CODE = SKILL_S_BREAKER;
	}

	pos.x = desChar->pX;
	pos.y = desChar->pY;
	pos.z = desChar->pZ;

	AssaParticle_RisingParticle(&pos, "star04B_01.bmp", 1000, 1, 1500, 3, 300);
	AssaParticle_RisingLine(&pos, "star04B_01.bmp", 300, 1, 1000, 3, 300);
	AssaParticle_RisingRotateLine(&pos, "star04B_01.bmp", 1, 500, 1, 200);

	Assa = SetAssaEffect(0, "NT23-Piecing.ASE", desChar, 0, 3000);

	cAssaEffect[Assa]->AniMaxCount = 20;
	cAssaEffect[Assa]->AniDelayTime = 2;
	cAssaEffect[Assa]->Time = -70;

	TempIndex = Assa;

	Assa = SetAssaEffect(30, "star03B_07.bmp", curChar, 0, 10000);

	cAssaEffect[Assa]->MOVECODE = ASSA_MOVE_ANGLE_SPEED;
	cAssaEffect[Assa]->Size.w = 4000;
	cAssaEffect[Assa]->MoveSpeed.z = 6 * fONE;
	cAssaEffect[Assa]->Angle.y = (-cAssaEffect[TempIndex]->Angle.y + ANGLE_180) & 0xFFF;
	cAssaEffect[Assa]->Time = cAssaEffect[TempIndex]->Time;
	cAssaEffect[Assa]->CODE = SKILL_PIERCING;
	cAssaEffect[Assa]->StartPosi.z = 8 * fONE;
	AssaSetStartPosi(cAssaEffect[Assa]);

	return TRUE;
}
//ÉñÁ¦³å´Ì
int sinSkillEffect_Breaker2(Unit *pChar)
{
	int TempIndex;

	AssaParticle_Char_Light2(pChar, ASSA_COLOR_CODE_BLUE, 70);
	SetDynLight(pChar->pX, pChar->pY, pChar->pZ, 0, 150, 255, 255, 130, 1);

	Assa = SetAssaEffect(60, "Bone", pChar, 0, 7000);

	cAssaEffect[Assa]->CODE = SKILL_S_BREAKER;

	for (int i = 0; i < 6; i++)
	{
		Assa = SetAssaEffect(80, "star05B_03.bmp", pChar, 0, pChar->PatHeight + 2500);
		cAssaEffect[Assa]->Size.w = 4000;
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE_RANDOM_ROTATE;
		cAssaEffect[Assa]->RAngleSpeed = 100;
		cAssaEffect[Assa]->MoveSpeed.z = fONE * 2;
		cAssaEffect[Assa]->Angle.x = GetRandomPos(0, 4096);
		cAssaEffect[Assa]->Angle.y = GetRandomPos(0, 4096);
		cAssaEffect[Assa]->CODE = SKILL_S_BREAKER;
	}
	for (int i = 0; i < 4; i++)
	{
		Assa = SetAssaEffect(80, "fire11_08.bmp", pChar, 0, pChar->PatHeight);
		cAssaEffect[Assa]->Size.w = 1500;
		cAssaEffect[Assa]->MOVECODE = ASSA_CHAR_POSI | ASSA_MOVE;
		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_TRACE;
		cAssaEffect[Assa]->cAssaTrace->SetLength(10);
		cAssaEffect[Assa]->CenterPosi.x = pChar->pX;
		cAssaEffect[Assa]->CenterPosi.y = pChar->pY + 10000 + cAssaEffect[Assa]->AddHeight;
		cAssaEffect[Assa]->CenterPosi.z = pChar->pZ;
		cAssaEffect[Assa]->GatherSpeed = 80;
		cAssaEffect[Assa]->CODE = SKILL_S_BREAKER;
		cAssaEffect[Assa]->NotFadeIn = 1;
		cAssaEffect[Assa]->ActionIndex[3] = 1;
		AssaGetCirclePosi(cAssaEffect[Assa], 256 * 64, (i + 1)*(4096 / 3));

		TempIndex = Assa;

		Assa = SetAssaEffect(80, "star01B_04.bmp", pChar, 0, cAssaEffect[Assa]->AddHeight);

		cAssaEffect[Assa]->Size.w = 4000;
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE | ASSA_CHAR_POSI;

		cAssaEffect[Assa]->MoveSpeed.x = cAssaEffect[TempIndex]->MoveSpeed.x;
		cAssaEffect[Assa]->MoveSpeed.y = cAssaEffect[TempIndex]->MoveSpeed.y;
		cAssaEffect[Assa]->MoveSpeed.z = cAssaEffect[TempIndex]->MoveSpeed.z;

		cAssaEffect[Assa]->CenterPosi.x = cAssaEffect[TempIndex]->CenterPosi.x;
		cAssaEffect[Assa]->CenterPosi.y = cAssaEffect[TempIndex]->CenterPosi.y;
		cAssaEffect[Assa]->CenterPosi.z = cAssaEffect[TempIndex]->CenterPosi.z;

		cAssaEffect[Assa]->GatherSpeed = cAssaEffect[TempIndex]->GatherSpeed;

		AssaGetCirclePosi(cAssaEffect[Assa], cAssaEffect[TempIndex]->RDistance.z, cAssaEffect[TempIndex]->RAngle);
		cAssaEffect[Assa]->ActionIndex[3] = 1;
		cAssaEffect[Assa]->CODE = SKILL_S_BREAKER;

		for (int j = 0; j < 10; j++)
			AssaParticle_RisingParticleContinue(&cAssaEffect[Assa]->Posi, "star05B_02.bmp", 500, 128, GetRandomPos(20, 80));
	}
	return TRUE;
}
//ÉýÁúÖØ»÷
int sinSkillEffect_Moon(Unit *pChar)
{
	for (int i = 0; i < 2; i++)
	{
		Assa = SetAssaEffect(0, "CresentMoon.ASE", pChar, 0, 0);
		cAssaEffect[Assa]->AniMaxCount = 20;
		cAssaEffect[Assa]->AniDelayTime = 2;
		//cAssaEffect[Assa]->StartPosi.x	= 20 * fONE;
		cAssaEffect[Assa]->Angle.y = (-pChar->Angle.y + ANGLE_90) & 0xFFF;
		AssaSetStartPosi(cAssaEffect[Assa]);
		cAssaEffect[Assa]->Angle.y = (-pChar->Angle.y) & 0xFFF;
		AssaGetCirclePosi(cAssaEffect[Assa], 0, 0);
	}
	SetDynLight(cAssaEffect[Assa]->Posi.x, cAssaEffect[Assa]->Posi.y, cAssaEffect[Assa]->Posi.z, 255, 120, 0, 255, 200, 1);

	return TRUE;
}
//ÉÏµÛÖØ»÷
int sinSkillEffect_Blade(Unit *pChar)
{
	int TempIndex;

	for (int i = 0; i < 4; i++)
	{
		Assa = SetAssaEffect(100, "Bubble1.bmp", pChar, 0, pChar->PatHeight - 2500);
		cAssaEffect[Assa]->Size.w = 1500;
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE | ASSA_CHAR_POSI;
		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_TRACE;
		cAssaEffect[Assa]->cAssaTrace->SetLength(10);
		cAssaEffect[Assa]->StartPosi.x = 32 * fONE;
		cAssaEffect[Assa]->Angle.y = (-pChar->Angle.y + ANGLE_90) & 0xFFF;
		AssaSetStartPosi(cAssaEffect[Assa]);
		cAssaEffect[Assa]->Angle.y = 0;
		cAssaEffect[Assa]->CenterPosi.x = cAssaEffect[Assa]->Posi.x;
		cAssaEffect[Assa]->CenterPosi.y = cAssaEffect[Assa]->pChar->Posi.y + cAssaEffect[Assa]->Posi.y;
		cAssaEffect[Assa]->CenterPosi.z = cAssaEffect[Assa]->Posi.z;
		cAssaEffect[Assa]->GatherSpeed = 80;
		cAssaEffect[Assa]->CODE = SKILL_S_BLADE;
		cAssaEffect[Assa]->NotFadeIn = 1;
		cAssaEffect[Assa]->ActionIndex[3] = 1;
		AssaGetCirclePosi(cAssaEffect[Assa], fONE * 64, (i + 1)*(4096 / 3));

		TempIndex = Assa;

		Assa = SetAssaEffect(100, "devine_nature_cross.tga", pChar, 0, pChar->PatHeight);
		cAssaEffect[Assa]->Size.w = 5000;
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE | ASSA_CHAR_POSI;

		cAssaEffect[Assa]->MoveSpeed.x = cAssaEffect[TempIndex]->MoveSpeed.x;
		cAssaEffect[Assa]->MoveSpeed.y = cAssaEffect[TempIndex]->MoveSpeed.y;
		cAssaEffect[Assa]->MoveSpeed.z = cAssaEffect[TempIndex]->MoveSpeed.z;

		cAssaEffect[Assa]->CenterPosi.x = cAssaEffect[TempIndex]->CenterPosi.x;
		cAssaEffect[Assa]->CenterPosi.y = cAssaEffect[TempIndex]->CenterPosi.y;
		cAssaEffect[Assa]->CenterPosi.z = cAssaEffect[TempIndex]->CenterPosi.z;

		cAssaEffect[Assa]->GatherSpeed = cAssaEffect[TempIndex]->GatherSpeed;

		AssaGetCirclePosi(cAssaEffect[Assa], cAssaEffect[TempIndex]->RDistance.z, cAssaEffect[TempIndex]->RAngle);
		cAssaEffect[Assa]->ActionIndex[3] = 1;
		cAssaEffect[Assa]->CODE = SKILL_S_BLADE;

		cAssaEffect[Assa]->Posi.x = cAssaEffect[TempIndex]->Posi.x;
		cAssaEffect[Assa]->Posi.y = cAssaEffect[TempIndex]->Posi.y;
		cAssaEffect[Assa]->Posi.z = cAssaEffect[TempIndex]->Posi.z;

		for (int j = 0; j < 10; j++)
			AssaParticle_RisingParticleContinue(&cAssaEffect[Assa]->Posi, "star05G_02.bmp", 700, 200, GetRandomPos(40, 100));
	}
	return TRUE;
}
//ÉñÊ¥Ï´Àñ
int sinSkillEffect_Anima(Unit *pChar)
{
	int TempIndex;
	AssaParticle_Char_Light2(pChar, ASSA_COLOR_CODE_BLUE, 70);
	SetDynLight(pChar->pX, pChar->pY, pChar->pZ, 0, 150, 255, 255, 130, 1);

	Assa = SetAssaEffect(60, "Bone", pChar, 0, 7000);
	cAssaEffect[Assa]->CODE = SKILL_T_ANIMA;

	POINT3D pos;

	pos.x = pChar->pX;
	pos.y = pChar->pY;
	pos.z = pChar->pZ;

	AssaParticle_RisingBelt(&pos, "belt-02.ASE", 1, 100);
	AssaParticle_RisingRotateLine(&pos, "star04B_01.bmp", 1, 500, 1, 200);

	Assa = SetAssaEffect(0, "NT23-Piecing.ASE", pChar, 0, 3000);

	cAssaEffect[Assa]->AniMaxCount = 20;
	cAssaEffect[Assa]->AniDelayTime = 2;
	cAssaEffect[Assa]->Time = -70;

	TempIndex = Assa;

	Assa = SetAssaEffect(30, "star03B_07.bmp", pChar, 0, 10000);

	cAssaEffect[Assa]->MOVECODE = ASSA_MOVE_ANGLE_SPEED;
	cAssaEffect[Assa]->Size.w = 3000;
	cAssaEffect[Assa]->MoveSpeed.z = 6 * fONE;
	cAssaEffect[Assa]->Angle.y = (-cAssaEffect[TempIndex]->Angle.y + ANGLE_180) & 0xFFF;
	cAssaEffect[Assa]->Time = cAssaEffect[TempIndex]->Time;
	cAssaEffect[Assa]->CODE = SKILL_T_ANIMA;
	//cAssaEffect[Assa]->AddHeight	= 128 * fONE;

	AssaSetStartPosi(cAssaEffect[Assa]);

	return TRUE;
}