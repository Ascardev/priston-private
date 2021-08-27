#include "StdAfx.h"
#include "smwsock.h"

#include "character.h"
#include "playmain.h"
#include "effectsnd.h"
#include "fileread.h"
#include "netplay.h"
#include "makeshadow.h"
#include "particle.h"
#include "playsub.h"
#include "skillsub.h"
#include "damage.h"
#include "areaserver.h"

static sSKILL Skill_ScoutHawk;


//打开运行技能
int OpenPlaySkill(sSKILL *lpSkill)
{
	int flag;
	int cnt;
	short wpDamage[2];

	pUseSkill = lpSkill;

	flag = 0;

	if (GAMECHARACTER->IsStageVillage())
		return flag;

	if (sinCheckSkillUseOk(lpSkill) == FALSE)
		return flag;
	if (lpSkill->Point > 10)
		return flag;

	wpDamage[0] = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin;
	wpDamage[1] = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax;

	lpSkill->SkillTaget_CODE = 0;

	switch (lpSkill->Skill_Info.CODE)
	{
		//极光护盾
	case SKILL_EXTREME_SHIELD:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->BeginSkill(SKILL_PLAY_EXTREME_SHIELD, 0, 0, 0, 0, 0);
			lpCurPlayer->AttackSkil = SKILL_PLAY_EXTREME_SHIELD;
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 100;
			lpCurPlayer->MotionLoop = 1;
			flag++;
		}
		break;
		//灵光护体
	case SKILL_PHYSICAL_ABSORB:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_PHYSICAL_ABSORB;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
			SendProcessSKillToServer(SKILL_PLAY_PHYSICAL_ABSORB, lpSkill->Point, 0, 0);
			SkillPlaySound(SKILL_SOUND_PHYSICAL_ABSORB3, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, TRUE);
			flag++;
		}
		break;
		//毒之防御
	case SKILL_POISON_ATTRIBUTE:
		if (lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->BeginSkill(SKILL_PLAY_POISON_ATTRIBUTE, 0, 0, 0, 0, 0);
			flag++;
		}
		break;
		//改良专家
	case SKILL_MAXIMIZE:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_MAXIMIZE;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
			flag++;
		}
		break;
		//灵光飞扬
	case SKILL_AUTOMATION:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_AUTOMATION;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
			SkillPlaySound(SKILL_SOUND_SKILL_AUTOMATION3, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, TRUE);
			flag++;
		}
		break;
		//金属重甲
	case SKILL_METAL_ARMOR:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_METAL_ARMOR;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
			cnt = cSkill.GetSkillPoint(SKILL_PHYSICAL_ABSORB);
			SendProcessSKillToServer(SKILL_PLAY_METAL_ARMOR, lpSkill->Point, cnt, 0);
			flag++;
		}
		break;
		//防御电波
	case SKILL_SPARK_SHIELD:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_SPARK_SHIELD;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
			cnt = cSkill.GetSkillPoint(SKILL_SPARK);
			SendProcessSKillToServer(SKILL_PLAY_SPARK_SHIELD, lpSkill->Point, cnt, 0);
			flag++;
		}
		break;
		//威慑怒吼
	case SKILL_COMPULSION:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_COMPULSION;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 80;
			lpCurPlayer->MotionLoop = 1;
			dm_SelectRange(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, Compulsion_Area[lpSkill->Point - 1], FALSE);
			dm_SendRangeDamage(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, 0, 0, lpCurPlayer->AttackSkil);
			flag++;
		}
		break;
		//磁性球体
	case SKILL_MAGNETIC_SPHERE:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_MAGNETIC_SPHERE;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 80;
			lpCurPlayer->MotionLoop = 1;
			SendProcessSKillToServer(SKILL_PLAY_MAGNETIC_SPHERE, lpSkill->Point, 0, 0);
			flag++;
		}
		break;
		//终极机械
	case SKILL_METAL_GOLEM:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_METAL_GOLEM;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 80;
			lpCurPlayer->MotionLoop = 1;
			SendProcessSKillToServer(SKILL_PLAY_METAL_GOLEM, lpSkill->Point, 0, 0);
			flag++;
		}
		break;
		//霹雳旋风
	case SKILL_LANDMINNING:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_LANDMINNING;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
			flag++;
		}
		break;
		//快速打击
	case SKILL_H_SONIC:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && GetAssaUseEffect(lpCurPlayer, SKILL_VIRTUAL_LIFE) == FALSE && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_H_SONIC;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
			flag++;
		}
		break;
		//战神祝福
	case SKILL_P_ENHENCE:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_P_ENHENCE;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 60;
			lpCurPlayer->MotionLoop = 1;
			flag++;
		}
		break;
		//极地怒吼
	case SKILL_ROAR:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_ROAR;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 80;
			lpCurPlayer->MotionLoop = 1;
			flag++;
		}
		break;
		//会心一击
	case SKILL_CONCENTRATION:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_CONCENTRATION;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 80;
			lpCurPlayer->MotionLoop = 1;
			flag++;
		}
		break;
		//刺杀之斧
	case SKILL_SWIFT_AXE:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_SWIFT_AXE;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 80;
			lpCurPlayer->MotionLoop = 1;
			flag++;
		}
		break;
		//疯狂怒吼
	case SKILL_BERSERKER:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_BERSERKER;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 80;
			lpCurPlayer->MotionLoop = 1;
			SendProcessSKillToServer(SKILL_PLAY_BERSERKER, lpSkill->Point, 0, 0);
			flag++;
		}
		break;
		//众神之怒
	case SKILL_B_BERSERKER:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_B_BERSERKER;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);

			lpCurPlayer->AttackSkil = SKILL_PLAY_BERSERKER;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);

			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);

			lpCurPlayer->AttackSkil = SKILL_PLAY_B_BERSERKER;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);

			lpCurPlayer->MotionLoopSpeed = 80;
			lpCurPlayer->MotionLoop = 1;
			SendProcessSKillToServer(SKILL_PLAY_B_BERSERKER, lpSkill->Point, 0, 0);
			flag++;
		}
		break;
		//龙卷枪风
	case SKILL_PIKE_WIND:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_PIKEWIND;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(SKILL_PLAY_PIKEWIND, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 80;
			lpCurPlayer->MotionLoop = 1;
			dm_SelectRange(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, Pike_Wind_Push_Lenght[lpSkill->Point - 1], FALSE);
			dm_SendRangeDamage(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, 0, 0, lpCurPlayer->AttackSkil);
			flag++;
		}
		break;
		//大地之枪
	case SKILL_GROUND_PIKE:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_GROUND_PIKE;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 80;
			lpCurPlayer->MotionLoop = 1;
			dm_SelectRange(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, G_Pike_Range[lpSkill->Point - 1], FALSE);
			dm_SendRangeDamage(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, 0, 0, lpCurPlayer->AttackSkil);
			flag++;
		}
		break;
		//灵蛇标枪
	case SKILL_VENOM_SPEAR:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_VENOM_SPEAR;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 80;
			lpCurPlayer->MotionLoop = 1;
			flag++;
		}
		break;
		//隐暗之术
	case SKILL_VANISH:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_VANISH;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 80;
			lpCurPlayer->MotionLoop = 1;
			flag++;
		}
		break;
		//影隐之遁
	case SKILL_VAGUE:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_VAGUE;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 80;
			lpCurPlayer->MotionLoop = 1;
			SendProcessSKillToServer(SKILL_PLAY_VAGUE, lpSkill->Point, 0, 0);
			flag++;
		}
		break;
		//潜能激发
	case SKILL_AMPLIFIED:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_AMPLIFIED;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
			flag++;
		}
		break;
		//侦察之鹰
	case SKILL_SCOUT_HAWK:
		if (lpSkill->Point && lpCurPlayer->HoSkillCode != SKILL_SCOUT_HAWK && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_SCOUT_HAWK;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			memcpy(&Skill_ScoutHawk, lpSkill, sizeof(sSKILL));
			lpCurPlayer->HideWeapon = TRUE;
			flag++;
		}
		break;
		//灵魂之鹰
	case SKILL_FALCON:
		if (lpSkill->Point && lpCurPlayer->HoSkillCode != SKILL_FALCON && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_FALCON;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 80;
			lpCurPlayer->MotionLoop = 1;
			lpCurPlayer->HideWeapon = TRUE;
			SkillFalconPoint = (lpSkill->Point - 1) ^ lpCurPlayer->iID ^ ((DWORD)chrOtherPlayer);
			SendProcessSKillToServer(SKILL_PLAY_FALCON, lpSkill->Point, 0, 0);
		}
		break;
		//黄金猎鹰
	case SKILL_GOLDEN_FALCON:
		if (lpSkill->Point && lpCurPlayer->HoSkillCode != SKILL_GOLDEN_FALCON && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_GOLDEN_FALCON;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 80;
			lpCurPlayer->MotionLoop = 1;
			lpCurPlayer->HideWeapon = TRUE;
			SkillFalconPoint = (lpSkill->Point - 1) ^ lpCurPlayer->iID ^ ((DWORD)chrOtherPlayer);
			cnt = cSkill.GetSkillPoint(SKILL_FALCON);
			SendProcessSKillToServer(SKILL_PLAY_GOLDEN_FALCON, lpSkill->Point, cnt, 0);
		}
		break;
		//召唤雪狼
	case SKILL_RECALL_WOLVERIN:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_RECALL_WOLVERIN;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 80;
			lpCurPlayer->MotionLoop = 1;
			lpCurPlayer->HideWeapon = TRUE;
			flag++;
		}
		break;
		//自然之光
	case SKILL_FORCE_OF_NATURE:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_FORCE_OF_NATURE;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 80;
			lpCurPlayer->MotionLoop = 1;
			SendProcessSKillToServer(SKILL_PLAY_FORCE_OF_NATURE, lpSkill->Point, 0, 0);
			cSkill.ForeceOfNature(Force_Of_Nature_Time[lpSkill->Point - 1], lpSkill->Point);
			lpCurPlayer->dwForceOfNatureTime = dwPlayTime + Force_Of_Nature_Time[lpSkill->Point - 1] * 1000;
			flag++;
		}
		break;
		//圣光护体
	case SKILL_HOLY_BODY:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_HOLY_BODY;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
			SendProcessSKillToServer(SKILL_PLAY_HOLY_BODY, lpSkill->Point, 0, 0);
			SkillPlaySound(SKILL_SOUND_PHYSICAL_ABSORB3, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, TRUE);
			flag++;
		}
		break;
		//神力重击
	case SKILL_HOLY_VALOR:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_HOLY_VALOR;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
			flag++;
		}
		break;
		//天佑神铠
	case SKILL_DRASTIC_SPIRIT:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_DRASTIC_SPIRIT;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
			flag++;
		}
		break;
		//圣灵之吸
	case SKILL_DIVINE_INHALATION:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_DIVINE_INHALATION;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
			//SendProcessSKillToServer(SKILL_PLAY_DIVINE_INHALATION,lpSkill->Point,0,0);
			flag++;
		}
		break;
		//敬神之盾
	case SKILL_GODLY_SHIELD:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_GODLY_SHIELD;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 80;
			lpCurPlayer->MotionLoop = 1;
			//SendProcessSKillToServer(SKILL_PLAY_GODLY_SHIELD,lpSkill->Point,0,0);
			flag++;
		}
		break;
		//上帝祝福
	case SKILL_GOD_BLESS:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_GODS_BLESS;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 80;
			lpCurPlayer->MotionLoop = 1;
			SendProcessSKillToServer(SKILL_PLAY_GODS_BLESS, lpSkill->Point, 0, 0);
			flag++;
		}
		break;
		//追命劲风
	case SKILL_WINDY:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_WINDY;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			flag++;
		}
		break;
		//战栗咆哮
	case SKILL_TRIUMPH_OF_VALHALLA:
		if (lpSkill->Point && !lpCharSelPlayer && GetAssaUseEffect(lpCurPlayer, SKILL_TRIUMPH_OF_VALHALLA) == FALSE && !cSkill.SearchContiueSkill(SKILL_HALL_OF_VALHALLA) && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_TRIUMPH_OF_VALHALLA;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			SendProcessSKillToServer(SKILL_PLAY_TRIUMPH_OF_VALHALLA, lpSkill->Point, 0, lpCurPlayer->sCharacterData.iLevel);
			lpCurPlayer->chrAttackTarget = 0;
			cSkill.SetT_Of_Valhalla(lpSkill->Point, lpCurPlayer->sCharacterData.iLevel);
			flag++;
		}
		break;
		//瓦尔哈拉之光
	case SKILL_HALL_OF_VALHALLA:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && GetAssaUseEffect(lpCurPlayer, SKILL_TRIUMPH_OF_VALHALLA) == FALSE && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_HALL_OF_VALHALLA;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 80;
			lpCurPlayer->MotionLoop = 1;
			cnt = cSkill.GetSkillPoint(SKILL_TRIUMPH_OF_VALHALLA);
			SendProcessSKillToServer(SKILL_PLAY_HALL_OF_VALHALLA, lpSkill->Point, cnt, lpCurPlayer->sCharacterData.iLevel);
			cSkill.HellOfValhalla(Hall_Of_Valhalla_Time[lpSkill->Point - 1], lpSkill->Point, cnt, lpCurPlayer->sCharacterData.iLevel, 0);
			lpCurPlayer->dwHallOfValhallaTime = dwPlayTime + Hall_Of_Valhalla_Time[lpSkill->Point - 1] * 1000;
			lpCurPlayer->ClearSkillToPlay(SKILL_TRIUMPH_OF_VALHALLA);
			flag++;
		}
		break;
		//霜冻标枪
	case SKILL_FROST_JAVELIN:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_FROST_JAVELIN;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 80;
			lpCurPlayer->MotionLoop = 1;
			SendProcessSKillToServer(SKILL_PLAY_FROST_JAVELIN, lpSkill->Point, 0, 0);
			flag++;
		}
		break;
		//轻舞飞扬
	case SKILL_TALARIA:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_TALARIA;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
			flag++;
		}
		break;
		//笨笨熊
	case SKILL_S_ARCUDA:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_S_ARCUDA;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 80;
			lpCurPlayer->MotionLoop = 1;
			flag++;
		}
		break;
		//治愈之术
	case SKILL_HEALING:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && !lpCharSelPlayer && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_HEALING;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
			cnt = GetRandomPos(Healing_Heal[lpSkill->Point - 1][0] + wpDamage[0], Healing_Heal[lpSkill->Point - 1][1] + wpDamage[0]);
			sinSetLife(sinGetLife() + cnt);
			ResetEnergyGraph(0);
			flag++;
		}
		break;
		//神之雷电
	case SKILL_DIVINE_LIGHTNING:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_DIVINE_LIGHTNING;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 85;
			lpCurPlayer->MotionLoop = 1;
			flag++;
		}
		break;
		//神圣反射
	case SKILL_HOLY_REFLECTION:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_HOLY_REFLECTION;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			flag++;
		}
		break;
		//圣洁之光
	case SKILL_GRAND_HEALING:
		if (lpSkill->Point && PARTYHANDLE->GetPartyData().iMembersCount > 0 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_GREAT_HEALING;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;

			dm_SendTransDamage(lpCurPlayer, wpDamage[0], wpDamage[1], 0, 0, lpCurPlayer->AttackSkil, FALSE);
			flag++;
		}
		break;
		//回生之术
	case SKILL_RESURRECTION:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_RESURRECTION;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			flag++;
		}
		break;
		//圣光之咒
	case SKILL_EXTINCTION:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_EXTINCTION;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			dm_SelectRange(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 160, FALSE);
			dm_SendRangeDamage(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, 0, 0, lpCurPlayer->AttackSkil);
			flag++;
		}
		break;
		//神圣之光
	case SKILL_VIRTUAL_LIFE:
		if (lpSkill->Point && !lpCharSelPlayer && GetAssaUseEffect(lpCurPlayer, SKILL_VIRTUAL_LIFE) == FALSE && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_VIRTUAL_LIFE;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			SendProcessSKillToServer(SKILL_PLAY_VIRTUAL_LIFE, lpSkill->Point, 0, 0);
			cSkill.SetVirtualLife(Virtual_Life_Time[lpSkill->Point - 1], lpSkill->Point);
			lpCurPlayer->chrAttackTarget = 0;
			flag++;
		}
		break;
		//再生领域
	case SKILL_REGENERATION_FIELD:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_REGENERATION_FIELD;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 80;
			lpCurPlayer->MotionLoop = 1;
			cSkill.Regeneration_Field(Regeneration_Field_Time[lpSkill->Point - 1], lpSkill->Point, 0);
			flag++;
		}
		break;
		//神圣天使
	case SKILL_SUMMON_MUSPELL:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_SUMMON_MUSPELL;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 80;
			lpCurPlayer->MotionLoop = 1;
			SendProcessSKillToServer(SKILL_PLAY_SUMMON_MUSPELL, lpSkill->Point, 0, 0);
			flag++;
		}
		break;
		//仙女散花
	case SKILL_B_KRISHNA:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_B_KRISHNA;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 80;
			lpCurPlayer->MotionLoop = 1;
			SendProcessSKillToServer(SKILL_PLAY_B_KRISHNA, lpSkill->Point, 0, 0);
			flag++;
		}
		break;
		//魔力转化
	case SKILL_AGONY:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_AGONY;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
			ResetEnergyGraph(3);
			flag++;
		}
		break;
		//集合之术
	case SKILL_ZENITH:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_ZENITH;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
			SendResistanceToServer();
			flag++;
		}
		break;
		//元素之术
	case SKILL_ENCHANT_WEAPON:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && !lpCharSelPlayer && !lpCurPlayer->WeaponEffect && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->chrAttackTarget = 0;
			lpCurPlayer->AttackSkil = SKILL_PLAY_ENCHANT_WEAPON;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			cnt = rand() % 3;
			lpCurPlayer->AttackSkil |= (cnt << 12);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
			flag++;
		}
		break;
		//魔法守护
	case SKILL_ENERGY_SHIELD:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_ENERGY_SHIELD;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 80;
			lpCurPlayer->MotionLoop = 1;
			SendProcessSKillToServer(SKILL_PLAY_ENERGY_SHIELD, lpSkill->Point, 0, 0);
			flag++;
		}
		break;
		//地裂冲击
	case SKILL_DIASTROPHISM:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_DIASTROPHISM;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 120;
			lpCurPlayer->MotionLoop = 1;
			flag++;
		}
		break;
		//灵魂召唤
	case SKILL_SPIRIT_ELEMENTAL:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_SPIRIT_ELEMENTAL;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 80;
			lpCurPlayer->MotionLoop = 1;
			SendProcessSKillToServer(SKILL_PLAY_SPIRIT_ELEMENTAL, lpSkill->Point, 0, 0);
			flag++;
		}
		break;
		//元素之剑
	case SKILL_DANCING_SWORD:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_DANCING_SWORD;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			cnt = rand() % 2;
			lpCurPlayer->AttackSkil |= (cnt << 12);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 80;
			lpCurPlayer->MotionLoop = 1;
			SendProcessSKillToServer(SKILL_PLAY_DANCING_SWORD, lpSkill->Point, cnt, 0);
			flag++;
		}
		break;
		//伊夫列特
	case SKILL_FIRE_ELEMENTAL:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_FIRE_ELEMENTAL;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 80;
			lpCurPlayer->MotionLoop = 1;
			flag++;
		}
		break;
		//空间扭曲
	case SKILL_DISTORTION:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_DISTORTION;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 80;
			lpCurPlayer->MotionLoop = 1;
			dm_SelectRange(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, Distortion_Area[lpSkill->Point - 1], FALSE);
			dm_SendRangeDamage(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, 0, 0, lpCurPlayer->AttackSkil);
			flag++;
		}
		break;
		//神圣洗礼
	case SKILL_P_IGNIS:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_P_IGNIS;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->AttackSkil = SKILL_PLAY_DANCING_SWORD;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->AttackSkil = SKILL_PLAY_P_IGNIS;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->MotionLoopSpeed = 80;
			lpCurPlayer->MotionLoop = 1;
			flag++;
		}
		break;
		//圣光法阵
	case SKILL_T_ANIMA:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_T_ANIMA;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 80;
			lpCurPlayer->MotionLoop = 1;
			SendProcessSKillToServer(SKILL_PLAY_T_ANIMA, lpSkill->Point, 0, 0);
			flag++;
		}
		break;
		//敏捷之力
	case SKILL_ALAS:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_ALAS;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
			flag++;
		}
		break;
		//灵魂震撼
	case SKILL_SOUL_SHOCK:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_SOUL_SHOCK;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
			flag++;
		}
		break;
		//敏捷大师
	case SKILL_INPES:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_INPES;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
			flag++;
		}
		break;
		//致盲
	case SKILL_BLIND:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_BLIND;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
			flag++;
		}
		break;
		//瘟疫之刃
	case SKILL_POLLUTED:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_POLLUTE;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
			flag++;
		}
		break;
		//影子火焰
	case SKILL_SHADOW_BOMB:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_SHADOW_BOMB;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
			flag++;
		}
		break;
		//猎取
	case SKILL_CHASING_HUNT:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_CHASING_HUNT;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
			flag++;
		}
		break;
		//迈克尔
	case SKILL_ADVENT_MIGAL:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_ADVENT_MIGAL;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
			flag++;
		}
		break;
		//祈雨师
	case SKILL_RAIN_MAKER:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_RAINMAKER;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
			flag++;
		}
		break;
		//陆地灵魂
	case SKILL_LAND_OF_GHOST:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_LAND_OF_GHOST;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
			flag++;
		}
		break;
		//嗜血之夜
	case SKILL_RECALL_BLOODYKNIGHT:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_CRIMSON_KNIGHT;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
			flag++;
		}
		break;
		//米德兰达
	case SKILL_ADVENT_MIDRANDA:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_ADVENT_MIDRANDA;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
			flag++;
		}
		break;
		//旭日东升
	case SKILL_MOURNING_OF_PRAY:
		if (GetAssaContinueSkill(SKILL_ADVENT_MIGAL) || GetAssaContinueSkill(SKILL_ADVENT_MIDRANDA))
		{
			if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
			{
				lpCurPlayer->AttackSkil = SKILL_PLAY_MOURNING_PRAY;
				lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
				lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
				lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
				lpCurPlayer->MotionLoopSpeed = 70;
				lpCurPlayer->MotionLoop = 1;
				flag++;
			}
		}
		break;
		//咒术信仰
	case SKILL_CREED:
		if (lpSkill->Point && lpCurPlayer->psModelAnimation && lpCurPlayer->psModelAnimation->iType < 0x100 && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_CREED;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
			flag++;
		}
		break;
	}
	if (flag)
		CheckPlaySkill();

	return flag;
}


int	NormalAttackRange;
int	NormalAttackMode;
int	LastAttackRange;

//获取技能攻击范围
int GetSkillDistRange(sSKILL *lpSkill, int AttackRange, int AttackMode)
{
	int cnt;

	NormalAttackRange = AttackRange;
	NormalAttackMode = AttackMode;

	switch (lpSkill->CODE)
	{
		//机械榴弹
	case SKILL_MECHANIC_BOMB:
		if (lpSkill->Point)
		{
			cnt = Mechanic_Bomb_Attack_Range[lpSkill->Point - 1];
			return	(cnt * 3 * fONE);
		}
		break;
		//火花电场
	case SKILL_SPARK:
		if (lpSkill->Point)
			return	140 * fONE;
		break;
		//狂野冲击
	case SKILL_P_DASH:
		if (lpSkill->Point)
			return 210 * fONE;
		//枪之飓风
	case SKILL_TORNADO:
		if (lpSkill->Point)
		{
			cnt = Tornado_Range[lpSkill->Point - 1];
			if (AttackRange > cnt)
				break;
			LastAttackRange = cnt;
			return cnt;
		}
		break;
		//无限力枪
	case SKILL_EXPANSION:
		if (lpSkill->Point)
		{
			cnt = AttackRange + ((AttackRange - 50 * fONE) * Expansion_Size[lpSkill->Point - 1]) / 100;
			LastAttackRange = cnt;
			return cnt;
		}
		break;
		//惯穿之箭
	case SKILL_PERFORATION:
		if (lpSkill->Point)
			return	AttackRange + (Perforation_Attack_Range[lpSkill->Point - 1] * fONE);
		break;
		//玄光之舞
	case SKILL_S_ROPE:
		if (lpSkill->Point)
			return	AttackRange + (S_Rope_AddRange[lpSkill->Point - 1] * fONE);
		break;
		//魔神剑
	case SKILL_SWORD_BLAST:
		if (lpSkill->Point)
		{
			cnt = Sword_Blast_ShootingRange[lpSkill->Point - 1];
			if (AttackRange > cnt)
				break;
			LastAttackRange = cnt;
			return cnt;
		}
		break;
		//圣剡之光
	case SKILL_HOLY_INCANTATION:
		return	120 * fONE;
		//美杜莎盾
	case SKILL_SHIELD_STRIKE:
		return	110 * fONE;
		//战栗咆哮
	case SKILL_TRIUMPH_OF_VALHALLA:
		return	200 * fONE;
		//狂风爆裂
	case SKILL_VENGEANCE:
		if (lpSkill->Point)
		{
			cnt = AttackRange + Vengeance_Range[lpSkill->Point - 1] * fONE;
			LastAttackRange = cnt;
			return cnt;
		}
		break;
		//治愈之术
	case SKILL_HEALING:
		return	180 * fONE;
		//圣光电球
	case SKILL_HOLY_BOLT:
		return	170 * fONE;
		//光芒四射
	case SKILL_MULTISPARK:
		return	210 * fONE;
		//意念之术
	case SKILL_HOLY_MIND:
		return	160 * fONE;
		//神之雷电
	case SKILL_DIVINE_LIGHTNING:
		return 160 * fONE;
		//火影双重
	case SKILL_VIGOR_BALL:
		return	230 * fONE;
		//神圣之光
	case SKILL_VIRTUAL_LIFE:
		return 200 * fONE;
		// 神圣电波
	case SKILL_S_IMPACT:
		if (lpSkill->Point)
			return S_Impact_Range[lpSkill->Point - 1] * fONE;
		break;
		// 神之冰刃
	case SKILL_P_ICE:
		return 280 * fONE;
		break;
		//火箭之术
	case SKILL_FIRE_BOLT:
		if (lpSkill->Point)
			return	200 * fONE;
		break;
		//火球之术
	case SKILL_FIRE_BALL:
		if (lpSkill->Point)
			return	FireBall_Range[lpSkill->Point - 1] * fONE;
		break;
		//龙卷海风
	case SKILL_WATORNADO:
		if (lpSkill->Point)
			return Watornado_Range[lpSkill->Point - 1] * fONE;
		break;
		//元素之术
	case SKILL_ENCHANT_WEAPON:
		return	140 * fONE;
		//冥亡之光
	case SKILL_DEAD_RAY:
		if (lpSkill->Point)
			return	Dead_Ray_Range[lpSkill->Point - 1] * fONE;
		break;
		//流星火雨
	case SKILL_SILRAPHIM:
		if (lpSkill->Point)
			return AttackRange + Silraphim_Range[lpSkill->Point - 1] * fONE;
		break;
		//蛛网之术
	case SKILL_V_TENUS:
		if (lpSkill->Point)
			return AttackRange + V_Tenus_Range[lpSkill->Point - 1] * fONE;
		break;
	}

	return NULL;
}

int RetryPlayAttack(Unit *lpChar)
{
	return lpCurPlayer->PlayAttackFromPosi(lpChar->pX, lpChar->pY, lpChar->pZ, NormalAttackRange, NormalAttackMode);
}


//技能损伤生命
int PlaySkillSubLife(int Life)
{
	int sLife;

	CheckCharForm();
	sLife = sinGetLife();
	sLife -= Life;
	if (sLife <= 0) sLife = 1;
	sinSetLife(sLife);

	return sLife;
}


//使用技能
int PlaySkillAttack(sSKILL *lpSkill, Unit *lpChar)
{
	int cnt;
	int	temp;
	int x, y, z;
	smTRANS_COMMAND	smTransCommand;
	RECT	rect;
	short wpDamage[2];
	int	 skFlag;

	lpCurPlayer->AttackSkil = 0;

	if (!lpSkill)
		return FALSE;

	if (lpSkill->CODE == SKILL_HEALING || lpSkill->CODE == SKILL_ENCHANT_WEAPON || lpSkill->CODE == SKILL_VIRTUAL_LIFE || lpSkill->CODE == SKILL_TRIUMPH_OF_VALHALLA)
		skFlag = TRUE;
	else
		skFlag = FALSE;

	if (!PkMode && lpChar->sCharacterData.iType != CHARACTERTYPE_Monster && skFlag == FALSE)
		return FALSE;

	if (sinCheckSkillUseOk(lpSkill) == FALSE || lpSkill->Point > 10)
	{
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar))
			return FALSE;;
		return TRUE;
	}

	CheckPlaySkill();

	pUseSkill = lpSkill;

	wpDamage[0] = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMin;
	wpDamage[1] = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItem.sDamage.sMax;

	lpSkill->SkillTaget_CODE = lpChar->iID;

	switch (lpSkill->CODE)
	{
		//极光护盾
	case SKILL_EXTREME_SHIELD:
		return TRUE;
		//机械榴弹
	case SKILL_MECHANIC_BOMB:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_MECHANIC_BOMB;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->HideWeapon = TRUE;
		}
		return TRUE;
		//灵光护体
	case SKILL_PHYSICAL_ABSORB:
		return TRUE;
		//破碎巨击
	case SKILL_GREAT_SMASH:
		if (lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			RetryPlayAttack(lpChar);
			lpCurPlayer->AttackSkil = SKILL_PLAY_GREAT_SMASH;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 110;
			lpCurPlayer->MotionLoop = 1;
			if (lpSkill->Point)
			{
				temp = lpCurPlayer->sCharacterData.iAttackRating;
				lpCurPlayer->sCharacterData.iAttackRating += G_Smash_Attack_Rate[lpSkill->Point - 1];
				dm_SelectRange(lpChar->pX, lpChar->pY, lpChar->pZ, 70, TRUE);
				dm_SendRangeDamage(lpChar->pX, lpChar->pY, lpChar->pZ, lpChar, 0, 0, 0, 0, lpCurPlayer->AttackSkil);

				lpCurPlayer->sCharacterData.iAttackRating = temp;
			}
			return TRUE;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar))
			break;
		return TRUE;
		//改良专家
	case SKILL_MAXIMIZE:
		//灵光飞扬
	case SKILL_AUTOMATION:
		return TRUE;
		//火花电场
	case SKILL_SPARK:
		if (lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_SPARK;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->HideWeapon = TRUE;
		}
		return TRUE;
		//星光灭绝
	case SKILL_GRAND_SMASH:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			RetryPlayAttack(lpChar);
			lpCurPlayer->AttackSkil = SKILL_PLAY_GRAND_SMASH;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = GetAttackSpeedFrame(lpCurPlayer->sCharacterData.iAttackSpeed, 4);
			lpCurPlayer->MotionLoop = 1;
			if (lpSkill->Point)
			{
				temp = lpCurPlayer->sCharacterData.iAttackRating;
				lpCurPlayer->sCharacterData.iAttackRating += Grand_Smash_AttackRate[lpSkill->Point - 1];
				cnt = dm_SendTransDamage(lpChar, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
				if (!cnt)
					lpCurPlayer->AttackCritcal = -1;
				lpCurPlayer->sCharacterData.iAttackRating = temp;
			}
			return TRUE;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar))
			break;
		return TRUE;
		//雷霆冲击
	case SKILL_IMPULSION:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_IMPULSION;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			dm_SelectRange(lpChar->pX, lpChar->pY, lpChar->pZ, Impulsion_Range[lpSkill->Point - 1], TRUE, Impulsion_LightingNum[lpSkill->Point - 1]);
			dm_SendRangeDamage(lpChar->pX, lpChar->pY, lpChar->pZ, 0, 0, 0, 0, 0, lpCurPlayer->AttackSkil);
		}
		return TRUE;
		//威慑怒吼
	case SKILL_COMPULSION:
		//磁性球体
	case SKILL_MAGNETIC_SPHERE:
		//终极机械
	case SKILL_METAL_GOLEM:
		return TRUE;
		// 究极之刃
	case SKILL_R_SMASH:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_R_SMASH;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoop = 1;
			lpCurPlayer->MotionLoopSpeed = 70;
		}
		return TRUE;
		//绝地暴走
	case SKILL_RAVING:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			RetryPlayAttack(lpChar);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Attack);
			lpCurPlayer->AttackSkil = SKILL_PLAY_RAVING;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			if (lpSkill->Point)
			{
				lpCurPlayer->MotionLoop = Ravind_Speed[lpSkill->Point - 1];
				cnt = dm_SendTransDamage(lpChar, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
				if (!cnt)
					lpCurPlayer->AttackCritcal = -1;
				else
				{
					PlaySkillSubLife(((int)(Raving_UseLife[lpSkill->Point - 1] * 10)*lpCurPlayer->sCharacterData.sHP.sMax) / 1000);
					DamageExp(lpChar, cnt);
				}
			}
			else
				lpCurPlayer->MotionLoop = 1;
			lpCurPlayer->MotionLoopSpeed = 90 + (10 * lpCurPlayer->MotionLoop);
			if (lpCurPlayer->MotionLoopSpeed < 100)
				lpCurPlayer->MotionLoopSpeed = 100;
			lpCurPlayer->AttackAnger = 150;
			return TRUE;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar))
			break;
		return TRUE;
		//精准之击
	case SKILL_IMPACT:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			RetryPlayAttack(lpChar);
			lpCurPlayer->AttackSkil = SKILL_PLAY_IMPACT;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			if (lpSkill->Point)
			{
				temp = lpCurPlayer->sCharacterData.iAttackRating;
				lpCurPlayer->sCharacterData.iAttackRating += Impact_Attack_Rating[lpSkill->Point - 1];
				cnt = dm_SendTransDamage(lpChar, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
				lpCurPlayer->sCharacterData.iAttackRating = temp;
				if (!cnt)
					lpCurPlayer->AttackCritcal = -1;
				else
					DamageExp(lpChar, cnt);
			}
			return TRUE;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar))
			break;
		return TRUE;
		//威力冲击
	case SKILL_TRIPLE_IMPACT:
		if (lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			RetryPlayAttack(lpChar);
			lpCurPlayer->AttackSkil = SKILL_PLAY_TRIPLE_IMPACT;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			switch (T_Impact_Hit[lpSkill->Point - 1])
			{
			case 1:
				cnt = lpCurPlayer->AttackSkil;
				lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Attack);
				lpCurPlayer->AttackSkil = cnt;
				break;
			case 2:
				cnt = lpCurPlayer->AttackSkil;
				lpCurPlayer->AttackSkil = SKILL_PLAY_IMPACT;
				lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
				lpCurPlayer->AttackSkil = cnt;
				break;
			case 3:
				lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
				break;
			}
			if (lpSkill->Point)
			{
				cnt = dm_SendTransDamage(lpChar, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
				if (!cnt)
					lpCurPlayer->AttackCritcal = -1;
				else
					DamageExp(lpChar, cnt);
			}
			return TRUE;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar))
			break;
		return TRUE;
		//致命回旋
	case SKILL_BRUTAL_SWING:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			RetryPlayAttack(lpChar);
			lpCurPlayer->AttackSkil = SKILL_PLAY_BRUTAL_SWING;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			if (lpSkill->Point)
			{
				cnt = dm_SendTransDamage(lpChar, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
				if (!cnt)
					lpCurPlayer->AttackCritcal = -1;
				else
					DamageExp(lpChar, cnt);
			}
			return TRUE;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar))
			break;
		return TRUE;
		//极地怒吼
	case SKILL_ROAR:
		return TRUE;
		//战神之怒
	case SKILL_RAGE_OF_ZECRAM:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			RetryPlayAttack(lpChar);
			lpCurPlayer->AttackSkil = SKILL_PLAY_RAGEOF_ZECRAM;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			if (lpSkill->Point)
			{
				cnt = dm_SendTransDamage(lpChar, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);

				if (!cnt)
					lpCurPlayer->AttackCritcal = -1;
				else
					DamageExp(lpChar, cnt);
			}
			return TRUE;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar))
			break;
		return TRUE;
		//复仇连击
	case SKILL_AVANGING_CRASH:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			RetryPlayAttack(lpChar);
			lpCurPlayer->AttackSkil = SKILL_PLAY_AVANGING_CRASH;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			temp = lpCurPlayer->sCharacterData.iAttackRating;
			lpCurPlayer->sCharacterData.iAttackRating += (lpCurPlayer->sCharacterData.iAttackRating * A_Crash_AttackRate[lpSkill->Point - 1]) / 100;
			if (lpSkill->Point)
			{
				cnt = dm_SendTransDamage(lpChar, cSkill.GetSkillPoint(SKILL_BRUTAL_SWING), 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
				if (!cnt)
					lpCurPlayer->AttackCritcal = -1;
				else
					DamageExp(lpChar, cnt);
			}
			lpCurPlayer->sCharacterData.iAttackRating = temp;
			return TRUE;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar))
			break;
		return TRUE;
		//挫骨扬灰
	case SKILL_BONE_CRASH:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			RetryPlayAttack(lpChar);
			lpCurPlayer->AttackSkil = SKILL_PLAY_BONE_SMASH;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			if (lpSkill->Point)
			{
				cnt = dm_SendTransDamage(lpChar, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
				if (!cnt)
					lpCurPlayer->AttackCritcal = -1;
				else
					DamageExp(lpChar, cnt);
			}

			return TRUE;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar))
			break;
		return TRUE;
		//破坏之击
	case SKILL_DETORYER:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_DESTROYER;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			cnt = dm_SendTransDamage(lpChar, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
			if (!cnt)
				lpCurPlayer->AttackCritcal = -1;
			lpCurPlayer->MotionLoopSpeed = GetAttackSpeedFrame(lpCurPlayer->sCharacterData.iAttackSpeed, 1);
			lpCurPlayer->MotionLoop = 1;
		}
		return TRUE;
		//疯狂怒吼
	case SKILL_BERSERKER:
		return TRUE;
		//飓风袭击
	case SKILL_CYCLONE_STRIKE:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_CYCLONE_STRIKE;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			dm_SelectRange(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, Cyclone_Strike_Area[lpSkill->Point - 1], TRUE, Cyclone_Strike_AttackNum[lpSkill->Point - 1]);
			dm_AddRangeDamage(lpChar);
			dm_SendRangeDamage(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, lpChar, 0, 0, 0, 0, lpCurPlayer->AttackSkil);
		}
		return TRUE;
		//狂暴怒斩
	case SKILL_D_HIT:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_D_HIT;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = GetAttackSpeedFrame(lpCurPlayer->sCharacterData.iAttackSpeed, 1);
			lpCurPlayer->MotionLoop = 1;
		}
		return TRUE;
		//狂野冲击
	case SKILL_P_DASH:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_P_DASH;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
		}
		return TRUE;
		//回旋斩击
	case SKILL_M_BLOW:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_M_BLOW;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = GetAttackSpeedFrame(lpCurPlayer->sCharacterData.iAttackSpeed, 1);
			lpCurPlayer->MotionLoop = 1;
		}
		return TRUE;
		//龙卷枪风
	case SKILL_PIKE_WIND:
		return TRUE;
		//致命打击
	case SKILL_CRITICAL_HIT:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			RetryPlayAttack(lpChar);
			lpCurPlayer->AttackSkil = SKILL_PLAY_CRITICAL_HIT;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			cnt = lpCurPlayer->sCharacterData.iAttackSpeed - 6;
			if (cnt < 0)
				cnt = 0;
			if (cnt > 6)
				cnt = 6;
			cnt += 2;
			lpCurPlayer->MotionLoopSpeed = (80 * (fONE + 32 * cnt + 32)) >> FLOATNS;
			lpCurPlayer->MotionLoop = 2;
			break;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar))
			break;
		return TRUE;
		//霹雳一击
	case SKILL_JUMPING_CRASH:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			RetryPlayAttack(lpChar);
			lpCurPlayer->AttackSkil = SKILL_PLAY_JUMPING_CRASH;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			if (lpSkill->Point)
			{
				temp = lpCurPlayer->sCharacterData.iAttackRating;
				lpCurPlayer->sCharacterData.iAttackRating += (lpCurPlayer->sCharacterData.iAttackRating * Jumping_Crash_Attack_Rating[lpSkill->Point - 1]) / 100;
				cnt = dm_SendTransDamage(lpChar, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
				lpCurPlayer->sCharacterData.iAttackRating = temp;
				if (!cnt)
					lpCurPlayer->AttackCritcal = -1;
				else
					DamageExp(lpChar, cnt);
			}
			lpCurPlayer->MotionLoopSpeed = 80;
			lpCurPlayer->MotionLoop = 1;
			return TRUE;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar))
			break;
		return TRUE;
		//大地之枪
	case SKILL_GROUND_PIKE:
		return TRUE;
		//枪之飓风
	case SKILL_TORNADO:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_TORNADO;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			cnt = GetRandomPos(lpCurPlayer->sCharacterData.iMinDamage, lpCurPlayer->sCharacterData.iMaxDamage);
			cnt += (cnt*Tornado_Damage[lpSkill->Point - 1]) / 100;
			x = (lpCurPlayer->pX - lpChar->pX) >> FLOATNS;
			z = (lpCurPlayer->pZ - lpChar->pZ) >> FLOATNS;
			y = (int)sqrt((float)(x*x + z * z));
			y += 8;
			dm_SelectRange(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, y, FALSE);
			//范围攻击
			dm_SendRangeDamage(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, 0, 0, lpCurPlayer->AttackSkil);
		}
		return TRUE;
		//无限力枪
	case SKILL_EXPANSION:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			RetryPlayAttack(lpChar);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Attack);
			lpCurPlayer->AttackSkil = SKILL_PLAY_EXPANSION;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			rect.left = -30;
			rect.right = 30;
			rect.top = 0;
			rect.bottom = LastAttackRange >> FLOATNS;
			rect.bottom += 20;
			dm_SelectRangeBox(lpCurPlayer, &rect, FALSE);
			dm_SendRangeDamage(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, lpChar, 0, 0, 0, 0, lpCurPlayer->AttackSkil);
			return TRUE;
		}
		if (lpSkill == sinSkill.pLeftSkill)
		{
			if (RetryPlayAttack(lpChar))
				break;
			AttCancel = TRUE;
		}
		return TRUE;
		//链骑之枪
	case SKILL_CHAIN_LANCE:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			RetryPlayAttack(lpChar);
			lpCurPlayer->AttackSkil = SKILL_PLAY_CHAIN_LANCE;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = GetAttackSpeedFrame(lpCurPlayer->sCharacterData.iAttackSpeed);
			lpCurPlayer->MotionLoop = 1;
			if (lpSkill->Point)
			{
				cnt = dm_SendTransDamage(lpChar, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
				if (!cnt)
					lpCurPlayer->AttackCritcal = -1;
			}
			return TRUE;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar))
			break;
		return TRUE;
		//暗杀之眼
	case SKILL_ASSASSIN_EYE:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_ASSASSIN_EYE;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			dm_SendTransDamage(lpChar, 0, 0, 0, 0, lpCurPlayer->AttackSkil, FALSE);
		}
		return TRUE;
		//转换打击
	case SKILL_CHARGING_STRIKE:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_CHARGING_STRIKE;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			SkillChargingFlag = 1;
			lpCurPlayer->MotionLoopSpeed = 60 + (Charging_Strike_Time[lpSkill->Point - 1] * 2);
			lpCurPlayer->MotionLoop = 1;
			SkillPlaySound(SKILL_SOUND_SKILL_CHARGING, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
		}
		return TRUE;
		//影隐之遁
	case SKILL_VAGUE:
		return TRUE;
		//宇宙幻影
	case SKILL_SHADOW_MASTER:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_SHADOW_MASTER;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			cnt = dm_SendTransDamage(lpChar, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
			if (!cnt)
				lpCurPlayer->AttackCritcal = -1;
			lpCurPlayer->MotionLoopSpeed = GetAttackSpeedFrame(7);
			lpCurPlayer->MotionLoop = 1;
		}
		return TRUE;
		//回旋打击
	case SKILL_D_REAPER:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			RetryPlayAttack(lpChar);
			lpCurPlayer->AttackSkil = SKILL_PLAY_D_REAPER;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = GetAttackSpeedFrame(lpCurPlayer->sCharacterData.iAttackSpeed);
			lpCurPlayer->MotionLoop = 1;
		}
		return TRUE;
		//地袭奇枪
	case SKILL_F_SPEAR:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_F_SPEAR;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = GetAttackSpeedFrame(lpCurPlayer->sCharacterData.iAttackSpeed);
			lpCurPlayer->MotionLoop = 1;
		}
		return TRUE;
		//旋风之枪
	case SKILL_SS_ATTACK:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_SS_ATTACK;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = GetAttackSpeedFrame(lpCurPlayer->sCharacterData.iAttackSpeed);
			lpCurPlayer->MotionLoop = 1;
		}
		return TRUE;
		//侦察之鹰
	case SKILL_SCOUT_HAWK:
		return TRUE;
		//疾风之箭
	case SKILL_WIND_ARROW:
		if (lpCurPlayer->CheckShootingTest(lpChar) == FALSE)
		{
			lpCurPlayer->AttackCritcal = -1;
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Idle);
			return TRUE;
		}
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			RetryPlayAttack(lpChar);
			if (lpCurPlayer->CheckShootingTest(lpChar) == TRUE)
			{
				lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Attack);
				lpCurPlayer->AttackSkil = SKILL_PLAY_WIND_ARROW;
				lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
				lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
				cnt = dm_SendTransDamage(lpChar, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
				if (!cnt)
					lpCurPlayer->AttackCritcal = -1;
				else
					DamageExp(lpChar, cnt);
				lpCurPlayer->MotionLoopSpeed = GetAttackSpeedFrame(lpCurPlayer->sCharacterData.iAttackSpeed, Wind_Arrow_Speed[lpSkill->Point - 1]);

				lpCurPlayer->MotionLoop = 1;
			}
			return TRUE;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar)) break;
		return TRUE;
		//夺命之箭
	case SKILL_PERFECT_AIM:
		if (lpCurPlayer->CheckShootingTest(lpChar) == FALSE)
		{
			lpCurPlayer->AttackCritcal = -1;
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Idle);
			return TRUE;
		}
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			RetryPlayAttack(lpChar);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Attack);
			lpCurPlayer->AttackSkil = SKILL_PLAY_PERFECT_AIM;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			temp = lpCurPlayer->sCharacterData.iAttackRating;
			lpCurPlayer->sCharacterData.iAttackRating += (lpCurPlayer->sCharacterData.iAttackRating * Perfect_Aim_Attack_Rate[lpSkill->Point - 1]) / 100;
			cnt = dm_SendTransDamage(lpChar, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
			if (!cnt)
				lpCurPlayer->AttackCritcal = -1;
			else
				DamageExp(lpChar, cnt);
			lpCurPlayer->sCharacterData.iAttackRating = temp;
			return TRUE;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar)) break;
		return TRUE;
		//狂暴火箭
	case SKILL_ARROW_OF_RAGE:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_ARROWOF_RAGE;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 120;
			lpCurPlayer->MotionLoop = 1;
		}
		return TRUE;
		//灵魂之鹰
	case SKILL_FALCON:
		return TRUE;
		//雪崩之箭
	case SKILL_AVALANCHE:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			RetryPlayAttack(lpChar);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Attack);

			lpCurPlayer->AttackSkil = SKILL_PLAY_AVALANCHE;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->AttackCriticalCount = 0;
			cnt = dm_SendTransDamage(lpChar, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
			if (!cnt)
				lpCurPlayer->AttackCritcal = -1;
			if (lpCurPlayer->AttackCritcal > 0)
				lpCurPlayer->AttackCriticalCount++;
			lpCurPlayer->MotionLoopSpeed = GetAttackSpeedFrame(lpCurPlayer->sCharacterData.iAttackSpeed, Avalanche_Speed[lpSkill->Point - 1]);
			lpCurPlayer->MotionLoop = Avalanche_ArrowNum[lpSkill->Point - 1];
			return TRUE;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar)) break;
		return TRUE;
		//元素攻击
	case SKILL_ELEMENTAL_SHOT:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			RetryPlayAttack(lpChar);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Attack);

			lpCurPlayer->AttackSkil = SKILL_PLAY_ELEMENTAL_SHOT;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			cnt = rand() % 2;
			lpCurPlayer->AttackSkil |= (cnt << 12);

			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->AttackCriticalCount = 0;

			if (cnt == 0)
			{
				cnt = dm_SendTransDamage(lpChar, 0, 0, 0, 0, lpCurPlayer->AttackSkil, FALSE);
				if (!cnt)
					lpCurPlayer->AttackCritcal = -1;
			}
			else
			{
				dm_SelectRange(lpChar->pX, lpChar->pY, lpChar->pZ, 75, FALSE);
				dm_SendRangeDamage(lpChar->pX, lpChar->pY, lpChar->pZ, lpChar, 0, 0, 0, 0, lpCurPlayer->AttackSkil);
			}
			lpCurPlayer->MotionLoopSpeed = GetAttackSpeedFrame(lpCurPlayer->sCharacterData.iAttackSpeed, 3);
			lpCurPlayer->MotionLoop = 2;
			return TRUE;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar)) break;
		return TRUE;
		//爆裂之箭
	case SKILL_BOMB_SHOT:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			RetryPlayAttack(lpChar);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Attack);
			lpCurPlayer->AttackSkil = SKILL_PLAY_BOMB_SHOT;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->AttackCriticalCount = 0;
			dm_SelectRange(lpChar->pX, lpChar->pY, lpChar->pZ, BombShot_Area[lpSkill->Point - 1], FALSE);
			dm_SendRangeDamage(lpChar->pX, lpChar->pY, lpChar->pZ, lpChar, 0, 0, 0, 0, lpCurPlayer->AttackSkil);
			lpCurPlayer->MotionLoopSpeed = (GetAttackSpeedFrame(lpCurPlayer->sCharacterData.iAttackSpeed) * 80) / 100;
			lpCurPlayer->MotionLoop = 2;
			return TRUE;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar)) break;
		return TRUE;
		//惯穿之箭
	case SKILL_PERFORATION:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			RetryPlayAttack(lpChar);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Attack);
			lpCurPlayer->AttackSkil = SKILL_PLAY_PERFORATION;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->AttackCriticalCount = 0;
			rect.left = -40;
			rect.right = 40;
			rect.top = 0;
			rect.bottom = lpCurPlayer->sCharacterData.iAttackRange + Perforation_Attack_Range[lpSkill->Point - 1];
			rect.bottom += 20;
			rect.bottom += 20;
			dm_SelectRangeBox(lpCurPlayer, &rect, FALSE);
			dm_SendRangeDamage(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, 0, 0, lpCurPlayer->AttackSkil);
			lpCurPlayer->MotionLoopSpeed = GetAttackSpeedFrame(lpCurPlayer->sCharacterData.iAttackSpeed);
			lpCurPlayer->MotionLoop = 1;
			return TRUE;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar))
			break;
		return TRUE;
		//召唤雪狼
	case SKILL_RECALL_WOLVERIN:
		return TRUE;
		//绯凰绝炎
	case SKILL_PHOENIX_SHOT:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_PHOENIX_SHOT;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			SkillChargingFlag = 1;
			lpCurPlayer->MotionLoopSpeed = 60 + (Phoenix_Shot_Time[lpSkill->Point - 1] * 2);
			lpCurPlayer->MotionLoop = 1;
			SkillPlaySound(SKILL_SOUND_SKILL_CHARGING, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
		}
		return TRUE;
		//自然之光
	case SKILL_FORCE_OF_NATURE:
		return TRUE;
		//回旋之舞
	case SKILL_E_SHOT:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_E_SHOT;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = GetAttackSpeedFrame(lpCurPlayer->sCharacterData.iAttackSpeed);
			lpCurPlayer->MotionLoop = 1;
		}
		return TRUE;
		//玄光之舞
	case SKILL_S_ROPE:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_S_ROPE;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = GetAttackSpeedFrame(lpCurPlayer->sCharacterData.iAttackSpeed);
			lpCurPlayer->MotionLoop = 1;
		}
		return TRUE;
		//飓风之箭
	case SKILL_N_SPLASH:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_N_SPLASH;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 150;
			lpCurPlayer->MotionLoop = 1;
		}
		return TRUE;
		//寒冰之箭
	case SKILL_C_TRAP:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_C_TRAP;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = GetAttackSpeedFrame(lpCurPlayer->sCharacterData.iAttackSpeed);
			lpCurPlayer->MotionLoop = 1;
		}
		return TRUE;
		//魔神剑
	case SKILL_SWORD_BLAST:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			RetryPlayAttack(lpChar);
			lpCurPlayer->AttackSkil = SKILL_PLAY_SWORD_BLAST;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			rect.left = -40;
			rect.right = 40;
			rect.top = 0;
			rect.bottom = Sword_Blast_ShootingRange[lpSkill->Point - 1] + 50;
			dm_SelectRangeBox(lpCurPlayer, &rect, FALSE);
			//范围攻击
			dm_SendRangeDamage(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, lpChar, 0, 0, 0, 0, lpCurPlayer->AttackSkil);

			return TRUE;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar)) break;
		return TRUE;
		//双重爆击
	case SKILL_DOUBLE_CRASH:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			RetryPlayAttack(lpChar);
			lpCurPlayer->AttackSkil = SKILL_PLAY_DOUBLE_CRASH;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			if (lpSkill->Point)
			{
				cnt = dm_SendTransDamage(lpChar, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
				if (!cnt)
					lpCurPlayer->AttackCritcal = -1;
				else
					DamageExp(lpChar, cnt);
			}
			return TRUE;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar)) break;
		return TRUE;
		//狂躁挥舞
	case SKILL_BRANDISH:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			RetryPlayAttack(lpChar);
			lpCurPlayer->AttackSkil = SKILL_PLAY_BRANDISH;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			dm_SelectRange(lpChar->pX, lpChar->pY, lpChar->pZ, Brandish_Range[lpSkill->Point - 1], FALSE);
			dm_SendRangeDamage(lpChar->pX, lpChar->pY, lpChar->pZ, 0, 0, 0, 0, 0, lpCurPlayer->AttackSkil);
			return TRUE;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar)) break;
		return TRUE;
		//一雾银
	case SKILL_PIERCING:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			RetryPlayAttack(lpChar);
			lpCurPlayer->AttackSkil = SKILL_PLAY_PIERCING;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			temp = lpCurPlayer->sCharacterData.iAttackRating;
			rect.left = -40;
			rect.right = 40;
			rect.top = 0;
			rect.bottom = Piercing_Range[lpSkill->Point - 1] + 30;
			dm_SelectRangeBox(lpCurPlayer, &rect, TRUE);
			dm_SendRangeDamage(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, 0, 0, lpCurPlayer->AttackSkil);
			lpCurPlayer->sCharacterData.iAttackRating = temp;
			return TRUE;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar))
			break;
		return TRUE;
		//圣光护体
	case SKILL_HOLY_BODY:
		//天佑神铠
	case SKILL_DRASTIC_SPIRIT:
		//精剑之术
	case SKILL_HOLY_VALOR:
		//圣灵之吸
	case SKILL_DIVINE_INHALATION:
		return TRUE;
		//圣剡之光
	case SKILL_HOLY_INCANTATION:
		if (lpSkill->Point && lpChar->sCharacterData.iMonsterType == MONSTERTYPE_Undead && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			RetryPlayAttack(lpChar);
			lpCurPlayer->AttackSkil = SKILL_PLAY_HOLY_INCANTATION;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			return TRUE;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar)) break;
		return TRUE;
		//圣光十字
	case SKILL_GRAND_CROSS:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			RetryPlayAttack(lpChar);
			lpCurPlayer->AttackSkil = SKILL_PLAY_GRAND_CROSS;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = GetAttackSpeedFrame(lpCurPlayer->sCharacterData.iAttackSpeed, 1);
			lpCurPlayer->MotionLoop = 1;
			temp = lpCurPlayer->sCharacterData.iAttackRating;
			lpCurPlayer->sCharacterData.iAttackRating += (lpCurPlayer->sCharacterData.iAttackRating*Grand_Cross_AttackRate[lpSkill->Point - 1]) / 100;
			cnt = dm_SendTransDamage(lpChar, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
			if (!cnt)
				lpCurPlayer->AttackCritcal = -1;
			else
				DamageExp(lpChar, cnt);
			lpCurPlayer->sCharacterData.iAttackRating = temp;
			return TRUE;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar)) break;
		return TRUE;
		//真魔神剑
	case SKILL_SWORD_OF_JUSTICE:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_SWORD_OF_JUSTICE;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			rect.left = -70;
			rect.right = 70;
			rect.top = 0;
			rect.bottom = Sword_Of_Justice_Area[lpSkill->Point - 1];
			rect.bottom += 20;
			rect.bottom += 20;
			dm_SelectRangeBox(lpCurPlayer, &rect, TRUE);
			dm_AddRangeDamage(lpChar);
			dm_SendRangeDamage(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, 0, 0, lpCurPlayer->AttackSkil);
		}
		return TRUE;
		//敬神之盾
	case SKILL_GODLY_SHIELD:
		//上帝祝福
	case SKILL_GOD_BLESS:
		return TRUE;
		//刹剧荒舞
	case SKILL_DIVINE_PIERCING:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_DIVINE_PIERCING;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			if (Divine_Piercing_AttackNum[lpSkill->Point - 1] >= 7)
			{
				cnt = lpCurPlayer->AttackSkil;
				lpCurPlayer->AttackSkil = SKILL_PLAY_DIVINE_PIERCING3;
				lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
				lpCurPlayer->AttackSkil = cnt;
			}
			else if (Divine_Piercing_AttackNum[lpSkill->Point - 1] >= 5)
			{
				cnt = lpCurPlayer->AttackSkil;
				lpCurPlayer->AttackSkil = SKILL_PLAY_DIVINE_PIERCING2;
				lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
				lpCurPlayer->AttackSkil = cnt;
			}
			else
				lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			cnt = dm_SendTransDamage(lpChar, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
			if (!cnt)
				lpCurPlayer->AttackCritcal = -1;
			lpCurPlayer->MotionLoopSpeed = GetAttackSpeedFrame(7);
			lpCurPlayer->MotionLoop = 1;
		}
		return TRUE;
		//神力冲刺
	case SKILL_S_BREAKER:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_S_BREAKER;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 100;
			lpCurPlayer->MotionLoop = 1;
		}
		return TRUE;
		//升龙重击
	case SKILL_C_MOON:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_C_MOON;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 100;
			lpCurPlayer->MotionLoop = 1;
		}
		return TRUE;
		//上帝重击
	case SKILL_S_BLADE:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_S_BLADE;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 100;
			lpCurPlayer->MotionLoop = 1;
		}
		return TRUE;
	case SKILL_H_BENEDIC:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_H_BENEDIC;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
		}
		return TRUE;
		//美杜莎盾
	case SKILL_SHIELD_STRIKE:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			RetryPlayAttack(lpChar);
			lpCurPlayer->AttackSkil = SKILL_PLAY_SHIELD_STRIKE;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 90;
			lpCurPlayer->MotionLoop = 1;
			rect.left = -50;
			rect.right = 50;
			rect.top = 0;
			rect.bottom = 160;
			dm_SelectRangeBox(lpCurPlayer, &rect, FALSE);
			dm_SendRangeDamage(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, 0, 0, lpCurPlayer->AttackSkil);
			return TRUE;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar))
			break;
		return TRUE;
		//含沙射影
	case SKILL_FARINA:
		if (lpCurPlayer->CheckShootingTest(lpChar) == FALSE)
		{
			lpCurPlayer->AttackCritcal = -1;
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Idle);
			return TRUE;
		}
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			RetryPlayAttack(lpChar);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Attack);
			lpCurPlayer->AttackSkil = SKILL_PLAY_FARINA;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			temp = lpCurPlayer->sCharacterData.iAttackRating;
			lpCurPlayer->MotionLoopSpeed = GetAttackSpeedFrame(lpCurPlayer->sCharacterData.iAttackSpeed, Farina_Speed[lpSkill->Point - 1]);
			lpCurPlayer->MotionLoop = 1;
			lpCurPlayer->sCharacterData.iAttackRating += Farina_AttackRate[lpSkill->Point - 1] + lpCurPlayer->sCharacterData.iLevel;
			cnt = dm_SendTransDamage(lpChar, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
			if (!cnt)
				lpCurPlayer->AttackCritcal = -1;
			else
				DamageExp(lpChar, cnt);
			lpCurPlayer->sCharacterData.iAttackRating = temp;
			return TRUE;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar)) break;
		return TRUE;
		//精神之枪
	case SKILL_VIGOR_SPEAR:
		if (lpCurPlayer->CheckShootingTest(lpChar) == FALSE)
		{
			lpCurPlayer->AttackCritcal = -1;
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Idle);
			return TRUE;
		}
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			RetryPlayAttack(lpChar);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Attack);
			lpCurPlayer->AttackSkil = SKILL_PLAY_VIGOR_SPEAR;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			cnt = dm_SendTransDamage(lpChar, wpDamage[0], 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
			if (!cnt)
				lpCurPlayer->AttackCritcal = -1;
			else
				DamageExp(lpChar, cnt);
			return TRUE;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar)) break;
		return TRUE;
		//追命劲风
	case SKILL_WINDY:
		return TRUE;
		//螺旋飞标
	case SKILL_TWIST_JAVELIN:
		if (lpCurPlayer->CheckShootingTest(lpChar) == FALSE)
		{
			lpCurPlayer->AttackCritcal = -1;
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Idle);
			return TRUE;
		}
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			RetryPlayAttack(lpChar);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Attack);
			lpCurPlayer->AttackSkil = SKILL_PLAY_TWIST_JAVELIN;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			temp = lpCurPlayer->sCharacterData.iAttackRating;
			lpCurPlayer->sCharacterData.iAttackRating += (lpCurPlayer->sCharacterData.iAttackRating*Twist_Javelin_Attack_Rating[lpSkill->Point - 1]) / 100;
			cnt = dm_SendTransDamage(lpChar, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
			if (!cnt)
				lpCurPlayer->AttackCritcal = -1;
			else
				DamageExp(lpChar, cnt);
			lpCurPlayer->sCharacterData.iAttackRating = temp;
			return TRUE;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar)) break;
		return TRUE;
		//灵魂吞噬
	case SKILL_SOUL_SUCKER:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			RetryPlayAttack(lpChar);
			lpCurPlayer->AttackSkil = SKILL_PLAY_SOUL_SUCKER;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 90;
			lpCurPlayer->MotionLoop = 1;
			rect.left = -30;
			rect.right = 30;
			rect.top = 0;
			rect.bottom = 200;
			dm_SelectRangeBox(lpCurPlayer, &rect, FALSE);
			dm_SendRangeDamage(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, 0, 0, lpCurPlayer->AttackSkil);
			return TRUE;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar)) break;
		return TRUE;
		//火焰烈枪
	case SKILL_FIRE_JAVELIN:
		if (lpCurPlayer->CheckShootingTest(lpChar) == FALSE)
		{
			lpCurPlayer->AttackCritcal = -1;
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Idle);
			return TRUE;
		}
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			RetryPlayAttack(lpChar);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Attack);
			lpCurPlayer->AttackSkil = SKILL_PLAY_FIRE_JAVELIN;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			dm_SendTransDamage(lpChar, 0, 0, 0, 0, lpCurPlayer->AttackSkil, FALSE);
			return TRUE;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar)) break;
		return TRUE;
		//追风之枪
	case SKILL_SPLIT_JAVELIN:
		if (lpCurPlayer->CheckShootingTest(lpChar) == FALSE)
		{
			lpCurPlayer->AttackCritcal = -1;
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Idle);
			return TRUE;
		}
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			RetryPlayAttack(lpChar);
			lpCurPlayer->AttackSkil = SKILL_PLAY_SPLIT_JAVELIN;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);

			temp = lpCurPlayer->sCharacterData.iAttackRating;
			lpCurPlayer->sCharacterData.iAttackRating += Split_Javelin_AttackRate[lpSkill->Point - 1];
			z = Split_Javelin_AttackNum[lpSkill->Point - 1];
			x = 0;
			y = sinGetAccuracy(lpChar->sCharacterData.iLevel, lpChar->sCharacterData.iDefenseRating);
			for (cnt = 0; cnt < z; cnt++)
			{
				if ((rand() % 100) < y)
					x++;
			}
			if (x > 0)
				dm_SendTransDamage(lpChar, x, 0, 0, 0, lpCurPlayer->AttackSkil, FALSE);
			else
				lpCurPlayer->AttackCritcal = -1;
			lpCurPlayer->AttackSkil |= (x << 12);
			lpCurPlayer->sCharacterData.iAttackRating = temp;
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = GetAttackSpeedFrame(lpCurPlayer->sCharacterData.iAttackSpeed, 1);
			lpCurPlayer->MotionLoopSpeed -= (lpCurPlayer->MotionLoopSpeed * 20) / 100;
			lpCurPlayer->MotionLoop = 1;
			return TRUE;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar)) break;
		return TRUE;
		//战栗咆哮
	case SKILL_TRIUMPH_OF_VALHALLA:
		if (lpSkill->Point && lpChar->sCharacterData.iType == CHARACTERTYPE_Player && GetAssaUseEffect(lpChar, SKILL_TRIUMPH_OF_VALHALLA) == FALSE && GetAssaUseEffect(lpChar, SKILL_HALL_OF_VALHALLA) == FALSE && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			RetryPlayAttack(lpChar);
			lpCurPlayer->AttackSkil = SKILL_PLAY_TRIUMPH_OF_VALHALLA;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			return TRUE;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar)) break;
		return TRUE;
		//光猎之枪
	case SKILL_LIGHTNING_JAVELIN:
		if (lpCurPlayer->CheckShootingTest(lpChar) == FALSE)
		{
			lpCurPlayer->AttackCritcal = -1;
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Idle);
			return TRUE;
		}
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			RetryPlayAttack(lpChar);
			lpCurPlayer->AttackSkil = SKILL_PLAY_LIGHTNING_JAVELIN;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			dm_SelectRange(lpChar->pX, lpChar->pY, lpChar->pZ, 100, FALSE);
			dm_SendRangeDamage(lpChar->pX, lpChar->pY, lpChar->pZ, lpChar, 0, 0, 0, 0, lpCurPlayer->AttackSkil);
			return TRUE;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar)) break;
		return TRUE;
		//暴风狂标
	case SKILL_STORM_JAVELIN:
		if (lpCurPlayer->CheckShootingTest(lpChar) == FALSE)
		{
			lpCurPlayer->AttackCritcal = -1;
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Idle);
			return TRUE;
		}
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			RetryPlayAttack(lpChar);

			lpCurPlayer->AttackSkil = SKILL_PLAY_STORM_JAVELIN;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			rect.left = -30;
			rect.right = 30;
			rect.top = 0;
			rect.bottom = 300;
			rect.bottom += 20;
			rect.bottom += 20;
			dm_SelectRangeBox(lpCurPlayer, &rect, FALSE);
			dm_SendRangeDamage(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, 0, 0, lpCurPlayer->AttackSkil);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = GetAttackSpeedFrame(lpCurPlayer->sCharacterData.iAttackSpeed);
			lpCurPlayer->MotionLoop = 2;
			return TRUE;
		}

		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar))
			break;
		return TRUE;
		//瓦尔哈拉之光
	case SKILL_HALL_OF_VALHALLA:
		return TRUE;
		//十字怒击
	case SKILL_X_RAGE:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_X_RAGE;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			dm_SelectRange(lpChar->pX, lpChar->pY, lpChar->pZ, X_Rage_Area[lpSkill->Point - 1], FALSE);
			dm_SendRangeDamage(lpChar->pX, lpChar->pY, lpChar->pZ, 0, 0, 0, 0, 0, lpCurPlayer->AttackSkil);
		}
		return TRUE;
		//霜冻标枪
	case SKILL_FROST_JAVELIN:
		return TRUE;
		//狂风爆裂
	case SKILL_VENGEANCE:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_VENGEANCE;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = GetAttackSpeedFrame(6);
			lpCurPlayer->MotionLoop = 1;
			cnt = dm_SendTransDamage(lpChar, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
			if (!cnt)
				lpCurPlayer->AttackCritcal = -1;
		}
		return TRUE;
		//星雨标枪
	case SKILL_G_COUP:
		if (lpCurPlayer->CheckShootingTest(lpChar) == FALSE)
		{
			lpCurPlayer->AttackCritcal = -1;
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Idle);
			return TRUE;
		}
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			RetryPlayAttack(lpChar);

			lpCurPlayer->AttackSkil = SKILL_PLAY_G_COUP;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = GetAttackSpeedFrame(lpCurPlayer->sCharacterData.iAttackSpeed);
			lpCurPlayer->MotionLoop = 1;
		}
		return TRUE;
		//火焰突袭
	case SKILL_S_FEAR:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_S_FEAR;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = GetAttackSpeedFrame(8);
			lpCurPlayer->MotionLoop = 1;
		}
		return TRUE;
		//治愈之术
	case SKILL_HEALING:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_HEALING;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
			dm_SendTransDamage(lpChar, wpDamage[0], wpDamage[1], 0, 0, lpCurPlayer->AttackSkil, FALSE);
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar))
			break;
		return TRUE;
		//圣光电球
	case SKILL_HOLY_BOLT:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_HOLY_BOLT;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = GetAttackSpeedFrame(8);
			lpCurPlayer->MotionLoop = 1;
			cnt = dm_SendTransDamage(lpChar, wpDamage[0], wpDamage[1], 0, 0, lpCurPlayer->AttackSkil, FALSE);
			if (!cnt)
				lpCurPlayer->AttackCritcal = -1;
			else
				DamageExp(lpChar, cnt);
			return TRUE;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar))
			break;
		return TRUE;
		//光芒四射
	case SKILL_MULTISPARK:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			cnt = M_Spark_Num[lpSkill->Point - 1];
			cnt = GetRandomPos((cnt / 2) + 1, cnt);
			lpCurPlayer->AttackSkil = SKILL_PLAY_MULTI_SPARK;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->AttackSkil |= (cnt << 12);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = GetAttackSpeedFrame(8);
			lpCurPlayer->MotionLoop = 1;

			cnt = dm_SendTransDamage(lpChar, wpDamage[0], wpDamage[1], 0, 0, lpCurPlayer->AttackSkil, FALSE);
			if (cnt)
				DamageExp(lpChar, cnt);
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar))
			break;
		return TRUE;
		//意念之术
	case SKILL_HOLY_MIND:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_HOLY_MIND;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
			cnt = HolyMind_DecDamage[lpSkill->Point - 1];
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.code = smTRANSCODE_HOLYMIND;
			smTransCommand.WParam = HolyMind_DecDamage[lpSkill->Point - 1];
			smTransCommand.LParam = 15;
			smTransCommand.SParam = lpChar->iID;
			smTransCommand.EParam = lpCurPlayer->iID;

			SENDPACKETG(&smTransCommand);
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar))
			break;
		return TRUE;
		//神之雷电
	case SKILL_DIVINE_LIGHTNING:
		//神圣反射
	case SKILL_HOLY_REFLECTION:
		//圣洁之光
	case SKILL_GRAND_HEALING:
		return TRUE;
		//火影双重
	case SKILL_VIGOR_BALL:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_VIGOR_BALL;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = GetAttackSpeedFrame(7);
			lpCurPlayer->MotionLoop = 1;
			DamageExp(lpChar, 1);
			return TRUE;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar))
			break;
		return TRUE;
		//回生之术
	case SKILL_RESURRECTION:
		//圣光之咒
	case SKILL_EXTINCTION:
		return TRUE;
		//神圣之光
	case SKILL_VIRTUAL_LIFE:
		if (lpSkill->Point && lpChar->sCharacterData.iType == CHARACTERTYPE_Player && GetAssaUseEffect(lpChar, SKILL_VIRTUAL_LIFE) == FALSE && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_VIRTUAL_LIFE;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			SendProcessSKillToServer(SKILL_PLAY_VIRTUAL_LIFE, lpSkill->Point, lpChar->iID, 0);
			return TRUE;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar)) break;
		return TRUE;
		//冰霜噬月
	case SKILL_GLACIAL_SPIKE:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_GLACIAL_SPIKE;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
		}
		return TRUE;
		//再生领域
	case SKILL_REGENERATION_FIELD:
		return TRUE;
		//天雷之怒
	case SKILL_CHAIN_LIGHTNING:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_CHAIN_LIGHTNING;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
		}
		return TRUE;
		//神圣天使
	case SKILL_SUMMON_MUSPELL:
		return TRUE;
		//神圣电波
	case SKILL_S_IMPACT:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_S_IMPACT;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 150;
			lpCurPlayer->MotionLoop = 1;
		}
		return TRUE;
		//神圣冰刃
	case SKILL_P_ICE:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_P_ICE;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 150;
			lpCurPlayer->MotionLoop = 1;
		}
		return TRUE;
		//暴风雪
	case SKILL_S_PRMIEL:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_S_PRMIEL;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, 0, 0, 0, 0);
			lpCurPlayer->AttackSkil = SKILL_PLAY_DIVINE_LIGHTNING;
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->AttackSkil = SKILL_PLAY_S_PRMIEL;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
		}
		return TRUE;
		//魔力转化
	case SKILL_AGONY:
		return TRUE;
		//火箭之术
	case SKILL_FIRE_BOLT:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_FIRE_BOLT;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 100;
			lpCurPlayer->MotionLoop = 1;
			cnt = dm_SendTransDamage(lpChar, wpDamage[0], wpDamage[1], 0, 0, lpCurPlayer->AttackSkil, FALSE);
			if (cnt)
				DamageExp(lpChar, cnt);
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar))
			break;
		return TRUE;
		//集合之术
	case SKILL_ZENITH:
		return TRUE;
		//火球之术
	case SKILL_FIRE_BALL:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_FIRE_BALL;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 100;
			lpCurPlayer->MotionLoop = 1;
			dm_SelectRange(lpChar->pX, lpChar->pY, lpChar->pZ, FireBall_Area[lpSkill->Point - 1], FALSE);
			dm_SendRangeDamage(lpChar->pX, lpChar->pY, lpChar->pZ, lpChar, wpDamage[0], wpDamage[1], 0, 0, lpCurPlayer->AttackSkil);
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar)) break;
		return TRUE;
		//龙卷海风
	case SKILL_WATORNADO:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_COLUMN_OF_WATER;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 90;
			lpCurPlayer->MotionLoop = 1;
			dm_SelectRange(lpChar->pX, lpChar->pY, lpChar->pZ, Watornado_Area[lpSkill->Point - 1], FALSE);
			dm_SendRangeDamage(lpChar->pX, lpChar->pY, lpChar->pZ, lpChar, wpDamage[0], wpDamage[1], 0, 0, lpCurPlayer->AttackSkil);
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar)) break;
		return TRUE;
		//元素之术
	case SKILL_ENCHANT_WEAPON:
		if (lpSkill->Point && !lpChar->WeaponEffect && lpChar->dwExclusiveNum && lpChar->sCharacterData.iType == CHARACTERTYPE_Player && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_ENCHANT_WEAPON;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			cnt = rand() % 3;
			lpCurPlayer->AttackSkil |= (cnt << 12);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 90;
			lpCurPlayer->MotionLoop = 1;
			return TRUE;
		}
		lpCurPlayer->chrAttackTarget = 0;
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar))
			break;
		return TRUE;
		//冥亡之光
	case SKILL_DEAD_RAY:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_DEAD_RAY;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 100;
			lpCurPlayer->MotionLoop = 1;
			cnt = dm_SendTransDamage(lpChar, wpDamage[0], wpDamage[1], 0, 0, lpCurPlayer->AttackSkil, FALSE);
			if (cnt)
				DamageExp(lpChar, cnt);
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar))
			break;
		return TRUE;
		//魔法守护
	case SKILL_ENERGY_SHIELD:
		//地裂冲击
	case SKILL_DIASTROPHISM:
		//灵魂召唤
	case SKILL_SPIRIT_ELEMENTAL:
		//元素之剑
	case SKILL_DANCING_SWORD:
		return TRUE;
		//伊夫列特
	case SKILL_FIRE_ELEMENTAL:
		return TRUE;
		//火焰波动
	case SKILL_FLAME_WAVE:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_FLAME_WAVE;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			rect.left = -60;
			rect.right = 60;
			rect.top = 0;
			rect.bottom = 300;
			rect.bottom += 20;
			rect.bottom += 20;
			dm_SelectRangeBox(lpCurPlayer, &rect, FALSE);
			dm_SendRangeDamage(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, wpDamage[0], wpDamage[1], 0, 0, lpCurPlayer->AttackSkil);
		}
		return TRUE;
		//空间扭曲
	case SKILL_DISTORTION:
		return TRUE;
		//陨石召唤
	case SKILL_M_METEO:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_METEO;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
		}
		return TRUE;
		//流星火雨
	case SKILL_SILRAPHIM:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_SILRAPHIM;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
		}
		return TRUE;
		//缩小之术
	case SKILL_V_TENUS:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_V_TENUS;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
		}
		return TRUE;
		//神圣洗礼
	case SKILL_P_IGNIS:
		return TRUE;
		//刺击
	case SKILL_STRINGER:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_STRINGER;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
		}
		return TRUE;
		//闪击
	case SKILL_RUNNING_HIT:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_RUNNING_HIT;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
		}
		return TRUE;
		//弱点攻击
	case SKILL_WISP:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_WISP;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
		}
		return TRUE;
		//毒牙连击
	case SKILL_VENOM_THORN:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_VENOM_THORN;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
		}
		return TRUE;
		//敏捷之力
	case SKILL_ALAS:
		return TRUE;
		//灵魂震撼
	case SKILL_SOUL_SHOCK:
		return TRUE;
		//飞剑之舞
	case SKILL_SORE_SWORD:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_SORE_SWORD;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = GetAttackSpeedFrame(lpCurPlayer->sCharacterData.iAttackSpeed);
			lpCurPlayer->MotionLoop = 1;
		}
		return TRUE;
		//跳斩
	case SKILL_BEAT_UP:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_BEAT_UP;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
		}
		return TRUE;
		//敏捷大师
	case SKILL_INPES:
		return TRUE;
		//致盲
	case SKILL_BLIND:
		return TRUE;
		//冰冻之刃
	case SKILL_FROST_WIND:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_FROST_WIND;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
		}
		return TRUE;
		//影子闪击
	case SKILL_PASTING_SHADOW:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_PASTING_SHADOW;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
		}
		return TRUE;
		//地裂斩
	case SKILL_RISING_SHASH:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_RISING_SLASH;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
		}
		return TRUE;
		//猛龙摆尾
	case SKILL_VIOLENCE_STAB:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_VIOLENT_STUB;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
		}
		return TRUE;
		//风暴之刃
	case SKILL_STORM:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_SHADOW_STORM;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
		}
		return TRUE;
		//暗黑闪电
	case SKILL_DARK_BOLT:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_DARK_BOLT;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar))
			break;
		return TRUE;
		//暗黑波浪
	case SKILL_DARK_WAVE:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_DARK_WAVE;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar))
			break;
		return TRUE;
		//诅咒雷击
	case SKILL_CURSE_LAZY:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_INERTIA;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar))
			break;
		return TRUE;
		//精神咒术
	case SKILL_SPIRITUAL_FLARE:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_SPIRITUAL_FLARE;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar))
			break;
		return TRUE;
		//灵魂枷锁

	case SKILL_SPIRITUAL_MANACLE:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_SPIRITUAL_MANACLE;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar))
			break;
		return TRUE;
		//猎取
	case SKILL_CHASING_HUNT:
		return TRUE;
		//迈克尔
	case SKILL_ADVENT_MIGAL:
		return TRUE;
		//祈雨师
	case SKILL_RAIN_MAKER:
		return TRUE;
		//陆地灵魂
	case SKILL_LAND_OF_GHOST:
		return TRUE;
		//鬼魂重回
	case SKILL_HAUNT:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_HAUNT;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar))
			break;
		return TRUE;
		//抓破
	case SKILL_SCRATCH:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_SCRATCH;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar))
			break;
		return TRUE;
		//嗜血之夜
	case SKILL_RECALL_BLOODYKNIGHT:
		return TRUE;
		//审判
	case SKILL_JUDGEMENT:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_JUDGEMENT;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar))
			break;
		return TRUE;
		//米德兰达
	case SKILL_ADVENT_MIDRANDA:
		return TRUE;
		//旭日东升
	case SKILL_MOURNING_OF_PRAY:
		return TRUE;
		//咒术信仰
	case SKILL_CREED:
		return TRUE;
		//诅咒之力
	case SKILL_PRESS_OF_DEITY:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_PRESS_DEITY;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar))
			break;
		return TRUE;
		//死亡之爪
	case SKILL_CHOSTY_NAIL:
		if (lpSkill->Point && lpSkill->Skill_Info.FuncPointer() == TRUE)
		{
			lpCurPlayer->AttackSkil = SKILL_PLAY_PHANTOM_NAIL;
			lpCurPlayer->AttackSkil |= (lpSkill->Point << 8);
			lpCurPlayer->BeginSkill(lpCurPlayer->AttackSkil, 0, lpChar, 0, 0, 0);
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Skill);
			lpCurPlayer->MotionLoopSpeed = 70;
			lpCurPlayer->MotionLoop = 1;
		}
		if (lpSkill == sinSkill.pLeftSkill && RetryPlayAttack(lpChar))
			break;
		return TRUE;
	}
	if (lpCurPlayer->psModelAnimation->iType != ANIMATIONTYPE_Attack && lpCurPlayer->psModelAnimation->iType != ANIMATIONTYPE_Skill)
		RetryPlayAttack(lpChar);
	return FALSE;
}

//使用技能循环
int PlaySkillLoop(int SkillCode, Unit *lpChar)
{
	int point, param;
	int	cnt;
	int JobCode;
	int dwSkillCode;
	Unit	*chrAttackTarget;
	RECT	rect;

	point = (SkillCode >> 8) & 0xF;
	param = (SkillCode >> 12) & 0xF;
	JobCode = lpChar->sCharacterData.iClass;
	dwSkillCode = SkillCode & 0xFF;
	//绝地暴走
	if (JobCode == CHARACTERCLASS_Fighter && dwSkillCode == SKILL_PLAY_RAVING)
	{
		if (lpChar->chrAttackTarget && point)
		{
			if (!lpChar->chrAttackTarget->sCharacterData.sHP.sMin)
				lpChar->MotionLoop = 0;
			else
			{
				cnt = dm_SendTransDamage(lpChar->chrAttackTarget, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
				if (!cnt)
					lpChar->AttackCritcal = -1;
				else
				{
					lpChar->AttackCritcal = 0;
					PlaySkillSubLife(((int)(Raving_UseLife[point - 1] * 10)*lpChar->sCharacterData.sHP.sMax) / 1000);
					DamageExp(lpChar->chrAttackTarget, cnt);
				}
				lpChar->AttackAnger = 150;
				lpChar->Angle.y = GetRadian2D(lpChar->pX, lpChar->pZ, lpChar->chrAttackTarget->pX, lpChar->chrAttackTarget->pZ);
			}
		}
	}
	//雪崩之箭
	else if (JobCode == CHARACTERCLASS_Archer && dwSkillCode == SKILL_PLAY_AVALANCHE)
	{
		if (lpChar->chrAttackTarget && point)
		{
			if (!lpChar->chrAttackTarget->sCharacterData.sHP.sMin)
				lpChar->MotionLoop = 0;
			else
			{
				cnt = dm_SendTransDamage(lpChar->chrAttackTarget, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
				if (!cnt)
					lpChar->AttackCritcal = -1;
				else
				{
					lpChar->AttackCritcal = 0;
					DamageExp(lpChar->chrAttackTarget, cnt);
				}
				lpChar->Angle.y = GetRadian2D(lpChar->pX, lpChar->pZ, lpChar->chrAttackTarget->pX, lpChar->chrAttackTarget->pZ);
			}
		}
	}
	//元素攻击
	else if (JobCode == CHARACTERCLASS_Archer && dwSkillCode == SKILL_PLAY_ELEMENTAL_SHOT)
	{
		if (lpChar->chrAttackTarget && point)
		{
			if (!lpChar->chrAttackTarget->sCharacterData.sHP.sMin)
				lpChar->MotionLoop = 0;
			else
			{
				chrAttackTarget = lpChar->chrAttackTarget;
				if (param == 0)
				{
					cnt = dm_SendTransDamage(lpChar->chrAttackTarget, 0, 0, 0, 0, lpChar->AttackSkil, FALSE);
					if (!cnt)
						lpChar->AttackCritcal = -1;
					else
						lpChar->AttackCritcal = 0;
				}
				else
				{
					dm_SelectRange(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 75, FALSE);
					dm_SendRangeDamage(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, chrAttackTarget, 0, 0, 0, 0, lpChar->AttackSkil);
				}
			}
		}
	}
	//爆裂之箭
	else if (JobCode == CHARACTERCLASS_Archer && dwSkillCode == SKILL_PLAY_BOMB_SHOT)
	{
		if (lpChar->chrAttackTarget && point)
		{
			chrAttackTarget = lpChar->chrAttackTarget;
			dm_SelectRange(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, BombShot_Area[point - 1], FALSE);
			dm_SendRangeDamage(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, chrAttackTarget, 0, 0, 0, 0, lpChar->AttackSkil);
		}
	}
	//致命打击
	else if (JobCode == CHARACTERCLASS_Pikeman && dwSkillCode == SKILL_PLAY_CRITICAL_HIT)
	{
		if (lpChar->chrAttackTarget && point)
		{
			if (!lpChar->chrAttackTarget->sCharacterData.sHP.sMin)
				lpChar->MotionLoop = 0;
			else
			{
				cnt = dm_SendTransDamage(lpChar->chrAttackTarget, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
				if (!cnt)
					lpChar->AttackCritcal = -1;
				else
				{
					lpChar->AttackCritcal = 0;
					DamageExp(lpChar->chrAttackTarget, cnt);
				}
			}
		}
	}
	//暴风狂标
	else if (JobCode == CHARACTERCLASS_Atalanta && dwSkillCode == SKILL_PLAY_STORM_JAVELIN)
	{
		if (lpChar->chrAttackTarget && point)
		{
			chrAttackTarget = lpChar->chrAttackTarget;
			rect.left = -30;
			rect.right = 30;
			rect.top = 0;
			rect.bottom = 300;
			rect.bottom += 20;
			rect.bottom += 20;
			dm_SelectRangeBox(lpChar, &rect, FALSE);
			dm_SendRangeDamage(lpChar->pX, lpChar->pY, lpChar->pZ, 0, 0, 0, 0, 0, lpChar->AttackSkil);
		}
	}
	return TRUE;
}


//设置技能模型颜色
int SetSkillMotionBlurColor(int dwSkillCode, Unit *lpChar)
{
	int SkillCode = dwSkillCode & 0xFF;
	int JobCode = lpChar->sCharacterData.iClass;

	//绝地暴走
	if (JobCode == CHARACTERCLASS_Fighter && SkillCode == SKILL_PLAY_RAVING)
	{
		smRender.Color_R += 256;
		smRender.Color_G += -64;
		smRender.Color_B += -64;
		return TRUE;
	}
	//精准之击
	else if (JobCode == CHARACTERCLASS_Fighter && SkillCode == SKILL_PLAY_IMPACT)
	{
		smRender.Color_R += 256;
		smRender.Color_G += 256;
		smRender.Color_B += -64;
		return TRUE;
	}
	//威力冲击
	else if (JobCode == CHARACTERCLASS_Fighter && SkillCode == SKILL_PLAY_TRIPLE_IMPACT)
	{
		smRender.Color_R += 256;
		smRender.Color_G += -64;
		smRender.Color_B += 256;
		return TRUE;
	}
	//致命回旋
	else if (JobCode == CHARACTERCLASS_Fighter && SkillCode == SKILL_PLAY_BRUTAL_SWING)
	{
		smRender.Color_R += -64;
		smRender.Color_G += 256;
		smRender.Color_B += 128;
		return TRUE;
	}
	//致命打击
	else if (JobCode == CHARACTERCLASS_Pikeman && SkillCode == SKILL_PLAY_CRITICAL_HIT)
	{
		smRender.Color_R += 256;
		smRender.Color_G += -64;
		smRender.Color_B += 256;
		return TRUE;
	}
	//链骑之枪
	else if (JobCode == CHARACTERCLASS_Pikeman && SkillCode == SKILL_PLAY_CHAIN_LANCE)
	{
		smRender.Color_R += 256;
		smRender.Color_G -= 64;
		smRender.Color_B -= 64;
	}
	return FALSE;
}


//获取技能攻击侦察之鹰
int GetSkillPower(Unit *lpChar, Unit *lpChar2, int dx, int dy, int dz)
{
	int x, y, z, dist;

	switch (lpChar->HoSkillCode)
	{
	case SKILL_SCOUT_HAWK:
		if (Skill_ScoutHawk.Point)
		{
			x = (lpChar->HoSkillPos.x - lpChar2->pX) >> FLOATNS;
			y = (lpChar->HoSkillPos.y - lpChar2->pY) >> FLOATNS;
			z = (lpChar->HoSkillPos.z - lpChar2->pZ) >> FLOATNS;
			dist = x * x + y * y + z * z;

			if (dist < (512 * 512))
				return Scout_Hawk_Attack_Rate[Skill_ScoutHawk.Point - 1];
		}
		break;
	}
	return NULL;
}

//胶懦 嚼垫 捞棋飘
int	LearnSkillEffect(Unit *lpChar)
{
	if (lpChar)
	{
		StartSkill(lpChar->pX, lpChar->pY, lpChar->pZ, 0, 0, 0, SKILL_UP1);
		SkillPlaySound(SKILL_SOUND_LEARN, lpChar->pX, lpChar->pY, lpChar->pZ);
	}
	else
	{
		StartSkill(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, SKILL_UP1);
		SkillPlaySound(SKILL_SOUND_LEARN, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
	}

	return TRUE;
}

int LastSkillMastery = (-10000 * SIN_MAX_USE_SKILL) ^ ((DWORD)LearnSkillEffect);

//检测技能运行
int CheckPlaySkill()
{
	int cnt;
	int point;
	int OverPoint;
	int SkillCount = 0;
	int	LastSkillCount;
	int SkillError = 0;
	int	SubMastery;
	smTRANS_COMMAND	smTransCommand;

	point = sinSkill.SkillPoint;

	for (cnt = 1; cnt < 13; cnt++)
	{
		point += sinSkill.UseSkill[cnt].Point;
		SkillCount += sinSkill.UseSkill[cnt].UseSkillCount;
		if (sinSkill.UseSkill[cnt].Point > 10)
			point += 16384;
	}

	LastSkillCount = LastSkillMastery ^ ((DWORD)LearnSkillEffect);
	LastSkillCount = -LastSkillCount;

	SubMastery = SkillCount - LastSkillCount;
	if ((SubMastery) > 300)
	{
		if (cInvenTory.InvenItem[SelectInvenItemIndex - 1].sItem.sItemID.ToInt() == (sinBI1 | sin39) ||
			cInvenTory.InvenItem[SelectInvenItemIndex - 1].sItem.sItemID.ToInt() == (sinBI1 | sin40) ||
			cInvenTory.InvenItem[SelectInvenItemIndex - 1].sItem.sItemID.ToInt() == (sinBI1 | sin41))
			SkillError = 0;
		else
			SkillError = 2;

		smTransCommand.LParam = SubMastery;
	}

	LastSkillMastery = (-SkillCount) ^ ((DWORD)LearnSkillEffect);

	if (lpCurPlayer->sCharacterData.iLevel >= 10)
	{
		OverPoint = ((lpCurPlayer->sCharacterData.iLevel - 8) / 2) + 1;
		OverPoint += GetSkillPoint_LevelQuest(lpCurPlayer->sCharacterData.iLevel, sinQuest_levelLog);

		if (OverPoint < point)
		{
			SkillError = 1;
			smTransCommand.LParam = point;
		}
	}
	else
	{
		if (point > 0)
		{
			SkillError = 1;
			smTransCommand.LParam = point;
		}
	}
	if (SkillError)
	{
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.code = smTRANSCODE_WARNING_SKILL;
		smTransCommand.WParam = SkillError;
		smTransCommand.SParam = lpCurPlayer->sCharacterData.iLevel;
		smTransCommand.EParam = 0;
		smTransCommand.EParam = dm_GetCommandChkSum(&smTransCommand, lpCurPlayer->iID);

		SENDPACKETL(&smTransCommand);
	}
	return TRUE;
}
void MasterSkill()
{
	int TempTalent = 0;
	int Temp = 0;
	if (cShop.haBuyMoneyCheck(sinMasterSkill_Money[pMasterSkill->Skill_Info.SkillNum] + (sinMasterSkill_PlusMoney[pMasterSkill->Skill_Info.SkillNum] * (pMasterSkill->Point))))
	{
		CheckCharForm();
		SendPaymentMoneyToServer((sinMasterSkill_Money[pMasterSkill->Skill_Info.SkillNum] + (sinMasterSkill_PlusMoney[pMasterSkill->Skill_Info.SkillNum] * (pMasterSkill->Point))) +
			((sinMasterSkill_Money[pMasterSkill->Skill_Info.SkillNum] + (sinMasterSkill_PlusMoney[pMasterSkill->Skill_Info.SkillNum] * (pMasterSkill->Point)))*cSinSiege.GetTaxRate()) / 100, 1);

		sinMinusMoney(sinMasterSkill_Money[pMasterSkill->Skill_Info.SkillNum] + (sinMasterSkill_PlusMoney[pMasterSkill->Skill_Info.SkillNum] * (pMasterSkill->Point)), 1);
		cSkill.CheckSkillPointForm(pMasterSkill);
		pMasterSkill->Point++;
		cSkill.ReformSkillPointForm(pMasterSkill);

		//学习4转技能
		if (Skill4ButtonIndex > 13)
			sinSkill.SkillPoint4--;
		// 学习1-3技能
		if (Skill4ButtonIndex <= 13)
			sinSkill.SkillPoint--;

		ReformCharForm();
		SendSaveMoney();
		sinPlaySound(SIN_SOUND_COIN);
		switch (pMasterSkill->CODE)
		{
		case SKILL_POISON_ATTRIBUTE:
			cInvenTory.SetItemToChar();
			break;
		case SKILL_MELEE_MASTERY:
			cInvenTory.SetItemToChar();
			break;
		case SKILL_FIRE_ATTRIBUTE:
			cInvenTory.SetItemToChar();
			break;
		case SKILL_ICE_ATTRIBUTE:
			cInvenTory.SetItemToChar();
			break;
			//强力之箭
		case SKILL_SHOOTING_MASTERY:
			cInvenTory.SetItemToChar();
			break;
		case SKILL_WEAPONE_DEFENCE_MASTERY:
			cInvenTory.SetItemToChar();
			break;
		case SKILL_DIONS_EYE:
			cInvenTory.SetItemToChar();
			break;
		case SKILL_PHYSICAL_TRANING:
			cInvenTory.SetItemToChar();
			break;
		case SKILL_FIRE_JAVELIN:
			cInvenTory.SetItemToChar();
			break;
		case SKILL_MEDITATION:
			cInvenTory.SetItemToChar();
			break;
		case SKILL_MENTAL_MASTERY:
			cInvenTory.SetItemToChar();
			break;
		case SKILL_THROWING_MASTERY:
			cInvenTory.SetItemToChar();
			break;
		case SKILL_MECHANIC_WEAPON:
			cInvenTory.SetItemToChar();
			break;
		case SKILL_CRITICAL_MASTERY:
			cInvenTory.SetItemToChar();
			break;
		case SKILL_SWORD_MASTERY:
			cInvenTory.SetItemToChar();
			break;
		case SKILL_BOOST_HEALTH:
			cInvenTory.SetItemToChar();
			break;
		case SKILL_EVASION_MASTERY:
			cInvenTory.SetItemToChar();
			break;
			//强化攻击
		case SKILL_SWORDMASTERY:
			cInvenTory.SetItemToChar();
			break;
			//攻击大师
		case SKILL_ATTACK_MASTERY:
			cInvenTory.SetItemToChar();
			break;
			//致命艺术
		case SKILL_FATAL_MASTERY:
			cInvenTory.SetItemToChar();
			break;
			//内心平和
		case SKILL_INNER_PEACE:
			cInvenTory.SetItemToChar();
			break;
		};
		cInvenTory.CheckDamage();
		LearnSkillEffect(0);
		TempTalent = (int)(sinChar->iTalent / 3);
		if (TempTalent > 50)TempTalent = 50;
		Temp = 10000 - (TempTalent * 100);

		if (Temp >= pMasterSkill->UseSkillCount)
			pMasterSkill->UseSkillCount /= 2;
		else
			pMasterSkill->UseSkillCount = Temp / 2;
		SaveGameData();
	}
	else
		cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_MONEY);
}