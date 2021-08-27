#include "StdAfx.h"
#include "skillsub.h"


static sSKILL Skill_ScoutHawk;

//获取技能攻击侦察之鹰
int GetSkillPower(Unit *lpChar, Unit *lpChar2, int dx, int dy, int dz)
{
	int x, y, z, dist;

	switch (lpChar->iPetID)
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