#include "StdAfx.h"

int CheckMana;
int CheckStamina;
int CheckMastery;

int NotUseSkillElement[3] = { 0,0,0 };

int sinMasterSkill_Money[SKILL_POINT_COLUM_MAX] = { 500,1000,1500,2000,3000,5000,7000,9000,10000,12000,15000,20000,25000,30000,35000,40000,50000,60000,70000,80000 };
int sinMasterSkill_PlusMoney[SKILL_POINT_COLUM_MAX] = { 500,600,700,800,1000,1200,1400,1600,2000,2500,3000,4000,5000,6000,7000,8000,10000,12000,14000,16000 };


#define GROUP_MECHANICIAN		0x01000000
#define GROUP_FIGHTER			0x02000000
#define GROUP_PIKEMAN			0x03000000
#define	GROUP_ARCHER			0x04000000



int sinMasteryIncreaIndex[SKILL_POINT_COLUM_MAX] = { 5,5,5,5,7,7,7,7,9,9,9,9,14,15,16,17,18,19,20,21 };


int ContinueSkillCancelFlag = 0;


int SkillTextColor[10] = { 0,0,0,0,0,0,0,0,0,0 };


int CheckContinueSkillUse(sSKILL *pSkill)
{
	for (int i = 0; i < SIN_MAX_SKILL_LIST; i++)
	{
		if (ContinueSkill[i].Flag && ContinueSkill[i].CODE == pSkill->CODE)
			return FALSE;
	}
	return TRUE;
}

int ContinueSkillUse(sSKILL *pSkill, int Time)
{
	for (int i = 0; i < SIN_MAX_SKILL_LIST; i++)
	{
		if (!ContinueSkill[i].Flag)
		{
			memcpy(&ContinueSkill[i], pSkill, sizeof(sSKILL));
			ContinueSkill[i].PlayTime = Time * 1000 + dwPlayTime;
			ContinueSkill[i].Flag = 1;
			ContinueSkill[i].UseTime = Time;
			return i + 1;
		}
	}
	return FALSE;
}

DWORD sinSkillswitchCODE[10][10] =
{
	{SKILL_PHYSICAL_ABSORB,SKILL_MAXIMIZE,SKILL_AUTOMATION,SKILL_METAL_ARMOR,0},
	{SKILL_EXTREME_SHIELD,SKILL_SPARK_SHIELD,0},
	{SKILL_CONCENTRATION,SKILL_SWIFT_AXE,0},
	{SKILL_BERSERKER,SKILL_B_BERSERKER,0},
	{SKILL_FALCON,SKILL_GOLDEN_FALCON,SKILL_SCOUT_HAWK,0},
	{SKILL_DIVINE_INHALATION,SKILL_GODLY_SHIELD,0},
	{STONE_R_FIRECRYTAL,STONE_R_ICECRYTAL,STONE_R_LINGHTINGCRYTAL,0},
	{STONE_A_FIGHTER,STONE_A_MECHANICIAN,STONE_A_PIKEMAN,STONE_A_ARCHER,STONE_A_KNIGHT,STONE_A_ATALANTA,STONE_A_MAGICIAN,STONE_A_PRIESTESS,STONE_A_ASSASSIN,STONE_A_SAMAN},
	0
};
void SwitchSkill(sSKILL *pSkill)
{
	int CodeLine = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (sinSkillswitchCODE[i][j])
			{
				if (sinSkillswitchCODE[i][j] == pSkill->CODE)
				{
					CodeLine = i + 1;
					break;
				}
			}
		}
	}
	if (CodeLine)
	{
		for (int k = 0; k < SIN_MAX_SKILL_LIST; k++)
		{
			if (ContinueSkill[k].Flag)
			{
				for (int t = 0; t < SIN_MAX_SKILL_LIST; t++)
				{
					if (ContinueSkill[k].CODE == sinSkillswitchCODE[CodeLine - 1][t])
					{
						if (sinSkillswitchCODE[CodeLine - 1][t] == pSkill->CODE)
							continue;
						ContinueSkill[k].Flag = 0;
						ContinueSkill[k].UseTime = 0;
						ContinueSkill[k].CheckTime = 0;
						ContinueSkill[k].IconFlag = 0;
						ContinueSkill[k].IconPosiX = 0;
						ContinueSkill[k].IconTime = 0;
						ContinueSkill[k].IconAlpha = 0;
						ContinueSkill[k].MatIcon = 0;
						ContinueSkill[k].PlayTime = 0;
						cInvenTory.SetItemToChar();
						lpCurPlayer->ClearSkillToPlay(ContinueSkill[k].CODE);
						SendCancelSkillToServer(sinSkillswitchCODE[CodeLine - 1][t], ContinueSkill[k].Point, 0, 0);
						break;
					}
				}
			}
		}
	}
}
// 检测时间技能
void CheckContinueSkill()
{
	int Cancel = 0;
	for (int i = 0; i < SIN_MAX_SKILL_LIST; i++)
	{
		if (ContinueSkill[i].Flag)
		{
			if (sinGetLife() <= 0 && (ContinueSkill[i].CODE != SKILL_FORCE_ORB && ContinueSkill[i].CODE != SKILL_CRYSTAL_ORB && ContinueSkill[i].CODE != SKILL_METAL_GOLEM && ContinueSkill[i].CODE != SKILL_RECALL_WOLVERIN && ContinueSkill[i].CODE != SKILL_S_ARCUDA && ContinueSkill[i].CODE != SKILL_FIRE_ELEMENTAL && ContinueSkill[i].CODE != SKILL_RECALL_BLOODYKNIGHT && ContinueSkill[i].CODE != SKILL_WARNING_TIME && ContinueSkill[i].CODE != CHANGE_JOB3_QUEST && ContinueSkill[i].CODE != CHANGE_ELEMENTARY_QUEST && ContinueSkill[i].CODE != CLANSKILL_ATTACK && ContinueSkill[i].CODE != CLANSKILL_EVASION && ContinueSkill[i].CODE != CLANSKILL_ABSORB && ContinueSkill[i].CODE != SCROLL_P_CRITICAL && ContinueSkill[i].CODE != SCROLL_P_EVASION && ContinueSkill[i].CODE != BOOSTER_ITEM_LIFE && ContinueSkill[i].CODE != BOOSTER_ITEM_MANA && ContinueSkill[i].CODE != BOOSTER_ITEM_STAMINA))
			{
				ContinueSkill[i].CheckTime = ContinueSkill[i].UseTime * 70;
				lpCurPlayer->ClearSkillToPlay(ContinueSkill[i].CODE);
				Cancel++;
			}
			if (ContinueSkill[i].CODE != SKILL_WARNING_TIME && ContinueSkill[i].CODE != SKILL_FORCE_ORB && ContinueSkill[i].CODE != CHANGE_JOB3_QUEST && ContinueSkill[i].CODE != CHANGE_ELEMENTARY_QUEST && ContinueSkill[i].CODE != CLANSKILL_ATTACK && ContinueSkill[i].CODE != CLANSKILL_EVASION && ContinueSkill[i].CODE != CLANSKILL_ABSORB && ContinueSkill[i].CODE != SCROLL_P_CRITICAL && ContinueSkill[i].CODE != SCROLL_P_EVASION && ContinueSkill[i].CODE != BOOSTER_ITEM_LIFE && ContinueSkill[i].CODE != BOOSTER_ITEM_MANA && ContinueSkill[i].CODE != BOOSTER_ITEM_STAMINA)
			{
				if (lpCurPlayer->iLoadedMapIndex >= 0 &&
					STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapType == MAPTYPE_Town)
				{
					if (ContinueSkill[i].CODE == SKILL_VIRTUAL_LIFE)
						sinVirtualLifeTime = 0;
					ContinueSkill[i].CheckTime = ContinueSkill[i].UseTime * 70;
					lpCurPlayer->ClearSkillToPlay(ContinueSkill[i].CODE);
					Cancel++;
				}
			}
			ContinueSkill[i].CheckTime++;

			if (ContinueSkill[i].CODE == CLANSKILL_ABSORB || ContinueSkill[i].CODE == CLANSKILL_ATTACK || ContinueSkill[i].CODE == CLANSKILL_EVASION || ContinueSkill[i].CODE == CHANGE_ELEMENTARY_QUEST || (ContinueSkill[i].CODE == CHANGE_JOB3_QUEST))
				ContinueSkill[i].CheckTime--;

			if (ContinueSkill[i].CODE == CHANGE_ELEMENTARY_QUEST)
			{
				if (chaQuest.sHaQuestElementary[Quest_D].CODE == HAQUEST_CODE_ELEMENTARY_D)
					ContinueSkill[i].CheckTime++;
			}
			if (ContinueSkill[i].CODE == CHANGE_JOB3_QUEST)
			{
				if (Quest_Flag == SIN_QUEST_CODE_CHANGEJOB4)
					ContinueSkill[i].CheckTime++;
			}
			if ((ContinueSkill[i].UseTime * 70) < ContinueSkill[i].CheckTime)
			{
				if (ContinueSkill[i].CODE == CHANGE_JOB3_QUEST)
				{
					if (Quest_Flag == SIN_QUEST_CODE_CHANGEJOB4)
					{
						if (sinQuest_ChangeJob4.Monster[1])
							sinQuest_ChangeJob4.State--;
						sinQuest_ChangeJob4.Monster[0] = 0;
						sinQuest_ChangeJob4.Kind = 0;
						SetQuestBoard();
						cMessageBox.ShowMessage(MESSAGE_CHANGEJOB4_FAIL);
						sinPlaySound(SIN_SOUND_FAILD_MIXITEM);
					}
				}

				if (ContinueSkill[i].CODE == CHANGE_ELEMENTARY_QUEST)
				{
					if (chaQuest.sHaQuestElementary[Quest_D].CODE == HAQUEST_CODE_ELEMENTARY_D)
					{
						DeleteQuestItem(sinQT1 | sin15);
						chaQuest.sHaQuestElementary[Quest_D].State = 1;
					}
				}

				ContinueSkill[i].Flag = 0;
				ContinueSkill[i].UseTime = 0;
				ContinueSkill[i].CheckTime = 0;

				ContinueSkill[i].IconFlag = 0;
				ContinueSkill[i].IconPosiX = 0;
				ContinueSkill[i].IconTime = 0;
				ContinueSkill[i].IconAlpha = 0;
				ContinueSkill[i].MatIcon = 0;
				ContinueSkill[i].PlayTime = 0;

				cInvenTory.SetItemToChar();
				switch (ContinueSkill[i].CODE)
				{
					// 极光之盾
				case SKILL_EXTREME_SHIELD:
					ZeroMemory(&ContinueSkill[i], sizeof(sSKILL));
					cInvenTory.SetItemToChar();
					if (Cancel == 0)
						SendCancelSkillToServer(SKILL_PLAY_EXTREME_SHIELD, 0, 0, 0);
					break;
					// 灵光护体
				case SKILL_PHYSICAL_ABSORB:
					ZeroMemory(&ContinueSkill[i], sizeof(sSKILL));
					cInvenTory.SetItemToChar();
					SkillTextColor[SIN2_ABSORB] = SIN_TEXT_COLOR_WHITE;
					break;
					//灵光飞扬
				case SKILL_AUTOMATION:
					ContinueSkill[i].PlusState[0] = 0;
					cInvenTory.SetItemToChar();
					if (Cancel == 0)
						SendCancelSkillToServer(SKILL_PLAY_AUTOMATION, 0, 0, 0);
					break;
					//改良专家
				case SKILL_MAXIMIZE:
					ContinueSkill[i].PlusState[0] = 0;
					cInvenTory.SetItemToChar();
					break;
					//金属重甲
				case SKILL_METAL_ARMOR:
					ContinueSkill[i].PlusState[0] = 0;
					cInvenTory.SetItemToChar();
					SkillTextColor[SIN2_DEFENSE] = SIN_TEXT_COLOR_WHITE;
					break;
					//防御电波
				case SKILL_SPARK_SHIELD:
					ContinueSkill[i].PlusState[0] = 0;
					cInvenTory.SetItemToChar();
					SkillTextColor[SIN2_DEFENSE] = SIN_TEXT_COLOR_WHITE;
					break;
					//威慑怒吼
				case SKILL_COMPULSION:
					ContinueSkill[i].PlusState[0] = 0;
					cInvenTory.SetItemToChar();
					SkillTextColor[SIN2_DEFENSE] = SIN_TEXT_COLOR_WHITE;
					break;
					//会心一击
				case SKILL_CONCENTRATION:
					ContinueSkill[i].PlusState[0] = 0;
					cInvenTory.SetItemToChar();
					SkillTextColor[SIN2_ATTACK_RATE] = SIN_TEXT_COLOR_WHITE;
					break;
					//刺杀之斧
				case SKILL_SWIFT_AXE:
					ContinueSkill[i].PlusState[0] = 0;
					cInvenTory.SetItemToChar();
					break;
					//天佑神铠
				case SKILL_DRASTIC_SPIRIT:
					ContinueSkill[i].PlusState[0] = 0;
					cInvenTory.SetItemToChar();
					SkillTextColor[SIN2_DEFENSE] = SIN_TEXT_COLOR_WHITE;
					break;
					//圣灵之吸
				case SKILL_DIVINE_INHALATION:
					ContinueSkill[i].PlusState[0] = 0;
					cInvenTory.SetItemToChar();
					if (Cancel == 0)
						SendCancelSkillToServer(SKILL_PLAY_DIVINE_INHALATION, 0, 0, 0);
					break;
					//敬神之盾
				case SKILL_GODLY_SHIELD:
					if (Cancel == 0)
						SendCancelSkillToServer(SKILL_PLAY_GODLY_SHIELD, 0, 0, 0);
					//追命劲风
				case SKILL_WINDY:
					ContinueSkill[i].PlusState[0] = 0;
					cInvenTory.SetItemToChar();
					SkillTextColor[SIN2_ATTACK_RATE] = SIN_TEXT_COLOR_WHITE;
					break;
				case CLANSKILL_ABSORB:
					ContinueSkill[i].PlusState[0] = 0;
					cInvenTory.SetItemToChar();
					break;
				case CLANSKILL_ATTACK:
					ContinueSkill[i].PlusState[0] = 0;
					cInvenTory.SetItemToChar();
					break;
				}
				memset(&ContinueSkill[i], 0, sizeof(sSKILL));
			}
		}
	}
	if (Cancel)
		SendCancelSkillToServer(0, 0, 0, 0);
}
int RequireStateCheck(int Mana)
{
	if (pUseSkill)
	{
		CheckStamina = pUseSkill->Skill_Info.UseStamina[0] + (pUseSkill->Skill_Info.UseStamina[1] * (pUseSkill->Point - 1));

		if (chaPremiumitem.m_StaminaReducePotiontime > 0)
			CheckStamina = CheckStamina - (CheckStamina * chaPremiumitem.m_StaminaReducePotionValue / 100);
	}

	if ((sinGetMana() - Mana) >= 0 && (sinGetStamina() - CheckStamina) >= 0 && pUseSkill->UseSkillFlag)
		return TRUE;

	if ((sinGetMana() - Mana) < 0)
		NotUseSkillElement[0] = 1;
	else
		NotUseSkillElement[0] = 0;

	if ((sinGetStamina() - CheckStamina) < 0)
		NotUseSkillElement[1] = 1;
	else
		NotUseSkillElement[1] = 0;

	if (!pUseSkill->UseSkillFlag)
		NotUseSkillElement[2] = 1;
	else
		NotUseSkillElement[2] = 0;

	if ((sinGetMana() - Mana) >= 0 && (sinGetStamina() - CheckStamina) >= 0 && pUseSkill->UseSkillFlag)
		return TRUE;

	return FALSE;
}
int F_Extreme_Shield()
{
	int SkillIndex = 0;

	CheckMana = E_Shield_UseMana[pUseSkill->Point - 1];

	if (chaPremiumitem.m_ManaReducePotiontime > 0 && chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - ((CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100) + (CheckMana * 20 / 100));

	else if (chaPremiumitem.m_ManaReducePotiontime > 0)
		CheckMana = CheckMana - (CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100);

	else if (chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - (CheckMana * 20 / 100);

	if (!CheckContinueSkillUse(pUseSkill))
		return FALSE;
	if (RequireStateCheck(CheckMana))
	{
		if (pUseSkill->Skill_Info.UseWeaponCode[0] == (cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sBaseItemID.ToInt() & sinITEM_MASK2))
		{
			CheckCharForm();
			SwitchSkill(pUseSkill);
			SkillIndex = ContinueSkillUse(pUseSkill, E_Shield_UseTime[pUseSkill->Point - 1]);
			if (SkillIndex)
				ContinueSkill[SkillIndex - 1].PlusState[0] = E_Shield_BlockRate[pUseSkill->Point - 1];
			sinSetMana(sinGetMana() - CheckMana);
			sinSetStamina(sinGetStamina() - CheckStamina);
			cSkill.CheckSkillMasteryForm(pUseSkill);
			pUseSkill->Mastery = 0;
			cSkill.ReformSkillMasteryForm(pUseSkill);

			ReformCharForm();

			cInvenTory.SetItemToChar();
			pUseSkill->UseSKillIncreCount++;
			if (pUseSkill->UseSKillIncreCount >= sinMasteryIncreaIndex[pUseSkill->Skill_Info.SkillNum] + ((pUseSkill->Point - 1) / 3))
			{
				pUseSkill->UseSKillIncreCount = 0;
				pUseSkill->UseSkillCount += USE_SKILL_MASTERY_COUNT;
			}
			return TRUE;
		}
	}
	return FALSE;
}

int F_Mechanic_Bomb()
{
	CheckMana = Mechanic_Bomb_UseMana[pUseSkill->Point - 1];

	if (chaPremiumitem.m_ManaReducePotiontime > 0 && chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - ((CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100) + (CheckMana * 20 / 100));

	else if (chaPremiumitem.m_ManaReducePotiontime > 0)
		CheckMana = CheckMana - (CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100);

	else if (chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - (CheckMana * 20 / 100);

	if (RequireStateCheck(CheckMana))
	{
		CheckCharForm();
		sinSetMana(sinGetMana() - CheckMana);
		sinSetStamina(sinGetStamina() - CheckStamina);
		cSkill.CheckSkillMasteryForm(pUseSkill);
		pUseSkill->Mastery = 0;
		cSkill.ReformSkillMasteryForm(pUseSkill);

		ReformCharForm();
		pUseSkill->UseSKillIncreCount++;
		if (pUseSkill->UseSKillIncreCount >= sinMasteryIncreaIndex[pUseSkill->Skill_Info.SkillNum] + ((pUseSkill->Point - 1) / 3))
		{
			pUseSkill->UseSKillIncreCount = 0;
			pUseSkill->UseSkillCount += USE_SKILL_MASTERY_COUNT;
		}
		return TRUE;
	}
	return FALSE;
}

int F_Physical_Absorption()
{
	int SkillIndex = 0;

	CheckMana = P_Absor_bUseMana[pUseSkill->Point - 1];

	if (chaPremiumitem.m_ManaReducePotiontime > 0 && chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - ((CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100) + (CheckMana * 20 / 100));

	else if (chaPremiumitem.m_ManaReducePotiontime > 0)
		CheckMana = CheckMana - (CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100);

	else if (chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - (CheckMana * 20 / 100);

	if (!CheckContinueSkillUse(pUseSkill))return FALSE;

	if (RequireStateCheck(CheckMana))
	{
		SwitchSkill(pUseSkill);
		CheckCharForm();
		SkillIndex = ContinueSkillUse(pUseSkill, P_Absorb_UseTime[pUseSkill->Point - 1]);
		if (SkillIndex)
			ContinueSkill[SkillIndex - 1].PlusState[0] = P_Absorb[pUseSkill->Point - 1];

		sinSetMana(sinGetMana() - CheckMana);
		sinSetStamina(sinGetStamina() - CheckStamina);
		cSkill.CheckSkillMasteryForm(pUseSkill);
		pUseSkill->Mastery = 0;
		cSkill.ReformSkillMasteryForm(pUseSkill);

		ReformCharForm();

		cInvenTory.SetItemToChar();
		SkillTextColor[SIN2_ABSORB] = SIN_TEXT_COLOR_BLUE;
		pUseSkill->UseSKillIncreCount++;
		if (pUseSkill->UseSKillIncreCount >= sinMasteryIncreaIndex[pUseSkill->Skill_Info.SkillNum] + ((pUseSkill->Point - 1) / 3))
		{
			pUseSkill->UseSKillIncreCount = 0;
			pUseSkill->UseSkillCount += USE_SKILL_MASTERY_COUNT;
		}
		return TRUE;
	}
	return FALSE;
}
int F_Poison_Attribute()
{
	cInvenTory.SetItemToChar();

	return TRUE;
}

int F_Great_Smash()
{
	CheckMana = G_Smash_UseMana[pUseSkill->Point - 1];

	if (chaPremiumitem.m_ManaReducePotiontime > 0 && chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - ((CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100) + (CheckMana * 20 / 100));

	else if (chaPremiumitem.m_ManaReducePotiontime > 0)
		CheckMana = CheckMana - (CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100);

	else if (chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - (CheckMana * 20 / 100);

	if (RequireStateCheck(CheckMana))
	{
		for (int i = 0; i < 10; i++)
		{
			if (pUseSkill->Skill_Info.UseWeaponCode[i] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt() & sinITEM_MASK2))
			{
				CheckCharForm();
				sinSetMana(sinGetMana() - CheckMana);
				sinSetStamina(sinGetStamina() - CheckStamina);
				cSkill.CheckSkillMasteryForm(pUseSkill);
				pUseSkill->Mastery = 0;
				cSkill.ReformSkillMasteryForm(pUseSkill);

				ReformCharForm();
				pUseSkill->UseSKillIncreCount++;
				if (pUseSkill->UseSKillIncreCount >= sinMasteryIncreaIndex[pUseSkill->Skill_Info.SkillNum] + ((pUseSkill->Point - 1) / 3))
				{
					pUseSkill->UseSKillIncreCount = 0;
					pUseSkill->UseSkillCount += USE_SKILL_MASTERY_COUNT;
				}
				return TRUE;
			}
		}
	}
	return FALSE;
}
int F_Maximize()
{
	int SkillIndex = 0;
	CheckMana = Maximize_UseMana[pUseSkill->Point - 1];

	if (chaPremiumitem.m_ManaReducePotiontime > 0 && chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - ((CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100) + (CheckMana * 20 / 100));

	else if (chaPremiumitem.m_ManaReducePotiontime > 0)
		CheckMana = CheckMana - (CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100);

	else if (chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - (CheckMana * 20 / 100);

	if (!CheckContinueSkillUse(pUseSkill))
		return FALSE;
	if (RequireStateCheck(CheckMana))
	{
		SwitchSkill(pUseSkill);
		CheckCharForm();
		SkillIndex = ContinueSkillUse(pUseSkill, Maximize_Time[pUseSkill->Point - 1]);

		if (SkillIndex)
			ContinueSkill[SkillIndex - 1].PlusState[0] = Maximize_Damage[pUseSkill->Point - 1];

		sinSetMana(sinGetMana() - CheckMana);
		sinSetStamina(sinGetStamina() - CheckStamina);
		cSkill.CheckSkillMasteryForm(pUseSkill);
		pUseSkill->Mastery = 0;
		cSkill.ReformSkillMasteryForm(pUseSkill);

		ReformCharForm();

		cInvenTory.SetItemToChar();
		SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_YELLOW;
		pUseSkill->UseSKillIncreCount++;
		if (pUseSkill->UseSKillIncreCount >= sinMasteryIncreaIndex[pUseSkill->Skill_Info.SkillNum] + ((pUseSkill->Point - 1) / 3))
		{
			pUseSkill->UseSKillIncreCount = 0;
			pUseSkill->UseSkillCount += USE_SKILL_MASTERY_COUNT;
		}
		return TRUE;
	}
	return FALSE;
}

int F_Automation()
{
	int SkillIndex = 0;
	CheckMana = Automation_UseMana[pUseSkill->Point - 1];

	if (chaPremiumitem.m_ManaReducePotiontime > 0 && chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - ((CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100) + (CheckMana * 20 / 100));

	else if (chaPremiumitem.m_ManaReducePotiontime > 0)
		CheckMana = CheckMana - (CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100);

	else if (chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - (CheckMana * 20 / 100);

	if (!CheckContinueSkillUse(pUseSkill))
		return FALSE;
	if (RequireStateCheck(CheckMana))
	{
		for (int i = 0; i < 10; i++)
		{
			if (pUseSkill->Skill_Info.UseWeaponCode[i] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt() & sinITEM_MASK2))
			{
				SwitchSkill(pUseSkill);
				CheckCharForm();
				SkillIndex = ContinueSkillUse(pUseSkill, Automation_Time[pUseSkill->Point - 1]);
				if (SkillIndex)
					ContinueSkill[SkillIndex - 1].PlusState[0] = Automation_Speed[pUseSkill->Point - 1];

				sinSetMana(sinGetMana() - CheckMana);
				sinSetStamina(sinGetStamina() - CheckStamina);
				cSkill.CheckSkillMasteryForm(pUseSkill);
				pUseSkill->Mastery = 0;
				cSkill.ReformSkillMasteryForm(pUseSkill);

				ReformCharForm();

				cInvenTory.SetItemToChar();

				SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_YELLOW;
				pUseSkill->UseSKillIncreCount++;
				if (pUseSkill->UseSKillIncreCount >= sinMasteryIncreaIndex[pUseSkill->Skill_Info.SkillNum] + ((pUseSkill->Point - 1) / 3))
				{
					pUseSkill->UseSKillIncreCount = 0;
					pUseSkill->UseSkillCount += USE_SKILL_MASTERY_COUNT;

				}
				return TRUE;
			}
		}
	}
	return FALSE;
}


int F_Spark()
{
	CheckMana = Spark_UseMana[pUseSkill->Point - 1];

	if (chaPremiumitem.m_ManaReducePotiontime > 0 && chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - ((CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100) + (CheckMana * 20 / 100));

	else if (chaPremiumitem.m_ManaReducePotiontime > 0)
		CheckMana = CheckMana - (CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100);

	else if (chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - (CheckMana * 20 / 100);

	if (RequireStateCheck(CheckMana))
	{
		CheckCharForm();
		sinSetMana(sinGetMana() - CheckMana);
		sinSetStamina(sinGetStamina() - CheckStamina);
		cSkill.CheckSkillMasteryForm(pUseSkill);
		pUseSkill->Mastery = 0;
		cSkill.ReformSkillMasteryForm(pUseSkill);

		ReformCharForm();
		pUseSkill->UseSKillIncreCount++;
		if (pUseSkill->UseSKillIncreCount >= sinMasteryIncreaIndex[pUseSkill->Skill_Info.SkillNum] + ((pUseSkill->Point - 1) / 3))
		{
			pUseSkill->UseSKillIncreCount = 0;
			pUseSkill->UseSkillCount += USE_SKILL_MASTERY_COUNT;
		}
		return TRUE;
	}
	return FALSE;
}
int F_Melee_Mastery()
{
	cInvenTory.SetItemToChar();
	return TRUE;
}
int F_Fire_Attribute()
{
	cInvenTory.SetItemToChar();

	return TRUE;
}
int F_Raving()
{
	float CheckLife = 0;

	CheckMana = Raving_UseMana[pUseSkill->Point - 1];

	if (chaPremiumitem.m_ManaReducePotiontime > 0 && chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - ((CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100) + (CheckMana * 20 / 100));

	else if (chaPremiumitem.m_ManaReducePotiontime > 0)
		CheckMana = CheckMana - (CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100);

	else if (chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - (CheckMana * 20 / 100);

	CheckLife = (float)((Raving_UseLife[pUseSkill->Point - 1] / 10) / sinChar->sHP.sMax) * 100;

	if (RequireStateCheck(CheckMana))
	{
		if ((short)CheckLife <= sinGetLife())
		{
			for (int i = 0; i < 10; i++)
			{
				if (pUseSkill->Skill_Info.UseWeaponCode[i] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt() & sinITEM_MASK2))
				{
					CheckCharForm();
					sinSetMana(sinGetMana() - CheckMana);
					sinSetStamina(sinGetStamina() - CheckStamina);
					sinSetLife(sinGetLife() - (short)CheckLife);
					cSkill.CheckSkillMasteryForm(pUseSkill);
					pUseSkill->Mastery = 0;
					cSkill.ReformSkillMasteryForm(pUseSkill);
					ReformCharForm();
					pUseSkill->UseSKillIncreCount++;
					if (pUseSkill->UseSKillIncreCount >= sinMasteryIncreaIndex[pUseSkill->Skill_Info.SkillNum] + ((pUseSkill->Point - 1) / 3))
					{
						pUseSkill->UseSKillIncreCount = 0;
						pUseSkill->UseSkillCount += USE_SKILL_MASTERY_COUNT;
					}
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}
int F_Impact()
{
	CheckMana = Impact_UseMana[pUseSkill->Point - 1];

	if (chaPremiumitem.m_ManaReducePotiontime > 0 && chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - ((CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100) + (CheckMana * 20 / 100));

	else if (chaPremiumitem.m_ManaReducePotiontime > 0)
		CheckMana = CheckMana - (CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100);

	else if (chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - (CheckMana * 20 / 100);

	if (RequireStateCheck(CheckMana))
	{
		for (int i = 0; i < 10; i++)
		{
			if (pUseSkill->Skill_Info.UseWeaponCode[i] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt() & sinITEM_MASK2))
			{
				CheckCharForm();
				sinSetMana(sinGetMana() - CheckMana);
				sinSetStamina(sinGetStamina() - CheckStamina);
				cSkill.CheckSkillMasteryForm(pUseSkill);
				pUseSkill->Mastery = 0;
				cSkill.ReformSkillMasteryForm(pUseSkill);
				ReformCharForm();
				pUseSkill->UseSKillIncreCount++;
				if (pUseSkill->UseSKillIncreCount >= sinMasteryIncreaIndex[pUseSkill->Skill_Info.SkillNum] + ((pUseSkill->Point - 1) / 3))
				{
					pUseSkill->UseSKillIncreCount = 0;
					pUseSkill->UseSkillCount += USE_SKILL_MASTERY_COUNT;
				}
				return TRUE;
			}
		}
	}
	return FALSE;
}

int F_Triple_Impact()
{
	CheckMana = T_Impact_UseMana[pUseSkill->Point - 1];

	if (chaPremiumitem.m_ManaReducePotiontime > 0 && chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - ((CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100) + (CheckMana * 20 / 100));

	else if (chaPremiumitem.m_ManaReducePotiontime > 0)
		CheckMana = CheckMana - (CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100);

	else if (chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - (CheckMana * 20 / 100);

	if (RequireStateCheck(CheckMana))
	{
		for (int i = 0; i < 10; i++)
		{
			if (pUseSkill->Skill_Info.UseWeaponCode[i] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt() & sinITEM_MASK2))
			{
				CheckCharForm();
				sinSetMana(sinGetMana() - CheckMana);
				sinSetStamina(sinGetStamina() - CheckStamina);
				cSkill.CheckSkillMasteryForm(pUseSkill);
				pUseSkill->Mastery = 0;
				cSkill.ReformSkillMasteryForm(pUseSkill);
				ReformCharForm();
				pUseSkill->UseSKillIncreCount++;
				if (pUseSkill->UseSKillIncreCount >= sinMasteryIncreaIndex[pUseSkill->Skill_Info.SkillNum] + ((pUseSkill->Point - 1) / 3))
				{
					pUseSkill->UseSKillIncreCount = 0;
					pUseSkill->UseSkillCount += USE_SKILL_MASTERY_COUNT;
				}
				return TRUE;
			}
		}
	}
	return FALSE;
}

int F_Brutal_Swing()
{
	CheckMana = B_Swing_UseMana[pUseSkill->Point - 1];

	if (chaPremiumitem.m_ManaReducePotiontime > 0 && chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - ((CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100) + (CheckMana * 20 / 100));

	else if (chaPremiumitem.m_ManaReducePotiontime > 0)
		CheckMana = CheckMana - (CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100);

	else if (chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - (CheckMana * 20 / 100);

	if (RequireStateCheck(CheckMana))
	{
		for (int i = 0; i < 10; i++)
		{
			if (pUseSkill->Skill_Info.UseWeaponCode[i] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt() & sinITEM_MASK2))
			{
				CheckCharForm();
				sinSetMana(sinGetMana() - CheckMana);
				sinSetStamina(sinGetStamina() - CheckStamina);
				cSkill.CheckSkillMasteryForm(pUseSkill);
				pUseSkill->Mastery = 0;
				cSkill.ReformSkillMasteryForm(pUseSkill);
				ReformCharForm();
				pUseSkill->UseSKillIncreCount++;
				if (pUseSkill->UseSKillIncreCount >= sinMasteryIncreaIndex[pUseSkill->Skill_Info.SkillNum] + ((pUseSkill->Point - 1) / 3))
				{
					pUseSkill->UseSKillIncreCount = 0;
					pUseSkill->UseSkillCount += USE_SKILL_MASTERY_COUNT;
				}
				return TRUE;
			}
		}
	}
	return FALSE;
}

int F_Roar()
{
	CheckMana = Roar_UseMana[pUseSkill->Point - 1];

	if (chaPremiumitem.m_ManaReducePotiontime > 0 && chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - ((CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100) + (CheckMana * 20 / 100));

	else if (chaPremiumitem.m_ManaReducePotiontime > 0)
		CheckMana = CheckMana - (CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100);

	else if (chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - (CheckMana * 20 / 100);

	if (RequireStateCheck(CheckMana))
	{
		CheckCharForm();
		sinSetMana(sinGetMana() - CheckMana);
		sinSetStamina(sinGetStamina() - CheckStamina);
		cSkill.CheckSkillMasteryForm(pUseSkill);
		pUseSkill->Mastery = 0;
		cSkill.ReformSkillMasteryForm(pUseSkill);
		ReformCharForm();
		pUseSkill->UseSKillIncreCount++;
		if (pUseSkill->UseSKillIncreCount >= sinMasteryIncreaIndex[pUseSkill->Skill_Info.SkillNum] + ((pUseSkill->Point - 1) / 3))
		{
			pUseSkill->UseSKillIncreCount = 0;
			pUseSkill->UseSkillCount += USE_SKILL_MASTERY_COUNT;
		}
		return TRUE;

	}
	return FALSE;
}

int F_RageOfZecram()
{
	CheckMana = R_Zecram_UseMana[pUseSkill->Point - 1];

	if (chaPremiumitem.m_ManaReducePotiontime > 0 && chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - ((CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100) + (CheckMana * 20 / 100));

	else if (chaPremiumitem.m_ManaReducePotiontime > 0)
		CheckMana = CheckMana - (CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100);

	else if (chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - (CheckMana * 20 / 100);

	if (RequireStateCheck(CheckMana))
	{
		for (int i = 0; i < 10; i++)
		{
			if (pUseSkill->Skill_Info.UseWeaponCode[i] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt() & sinITEM_MASK2))
			{
				CheckCharForm();
				sinSetMana(sinGetMana() - CheckMana);
				sinSetStamina(sinGetStamina() - CheckStamina);
				cSkill.CheckSkillMasteryForm(pUseSkill);
				pUseSkill->Mastery = 0;
				cSkill.ReformSkillMasteryForm(pUseSkill);
				ReformCharForm();
				pUseSkill->UseSKillIncreCount++;
				if (pUseSkill->UseSKillIncreCount >= sinMasteryIncreaIndex[pUseSkill->Skill_Info.SkillNum] + ((pUseSkill->Point - 1) / 3))
				{
					pUseSkill->UseSKillIncreCount = 0;
					pUseSkill->UseSkillCount += USE_SKILL_MASTERY_COUNT;
				}
				return TRUE;
			}
		}
	}
	return FALSE;
}
int F_Pike_Wind()
{
	CheckMana = Pike_Wind_UseMana[pUseSkill->Point - 1];

	if (chaPremiumitem.m_ManaReducePotiontime > 0 && chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - ((CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100) + (CheckMana * 20 / 100));

	else if (chaPremiumitem.m_ManaReducePotiontime > 0)
		CheckMana = CheckMana - (CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100);

	else if (chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - (CheckMana * 20 / 100);

	if (RequireStateCheck(CheckMana))
	{
		if (pUseSkill->Skill_Info.UseWeaponCode[0] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt() & sinITEM_MASK2))
		{
			CheckCharForm();
			sinSetMana(sinGetMana() - CheckMana);
			sinSetStamina(sinGetStamina() - CheckStamina);
			cSkill.CheckSkillMasteryForm(pUseSkill);
			pUseSkill->Mastery = 0;
			cSkill.ReformSkillMasteryForm(pUseSkill);
			ReformCharForm();
			pUseSkill->UseSKillIncreCount++;
			if (pUseSkill->UseSKillIncreCount >= sinMasteryIncreaIndex[pUseSkill->Skill_Info.SkillNum] + ((pUseSkill->Point - 1) / 3))
			{
				pUseSkill->UseSKillIncreCount = 0;
				pUseSkill->UseSkillCount += USE_SKILL_MASTERY_COUNT;
			}
			return TRUE;
		}
	}
	return FALSE;
}
int F_Ice_Attribute()
{
	cInvenTory.SetItemToChar();

	return TRUE;
}
int F_Critical_Hit()
{
	CheckMana = Critical_Hit_UseMana[pUseSkill->Point - 1];

	if (chaPremiumitem.m_ManaReducePotiontime > 0 && chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - ((CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100) + (CheckMana * 20 / 100));

	else if (chaPremiumitem.m_ManaReducePotiontime > 0)
		CheckMana = CheckMana - (CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100);

	else if (chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - (CheckMana * 20 / 100);

	if (RequireStateCheck(CheckMana))
	{
		CheckCharForm();
		sinSetMana(sinGetMana() - CheckMana);
		sinSetStamina(sinGetStamina() - CheckStamina);
		cSkill.CheckSkillMasteryForm(pUseSkill);
		pUseSkill->Mastery = 0;
		cSkill.ReformSkillMasteryForm(pUseSkill);

		ReformCharForm();
		pUseSkill->UseSKillIncreCount++;
		if (pUseSkill->UseSKillIncreCount >= sinMasteryIncreaIndex[pUseSkill->Skill_Info.SkillNum] + ((pUseSkill->Point - 1) / 3))
		{
			pUseSkill->UseSKillIncreCount = 0;
			pUseSkill->UseSkillCount += USE_SKILL_MASTERY_COUNT;
		}
		return TRUE;
	}
	return FALSE;
}
int F_Jumping_Crash()
{
	CheckMana = Jumping_Crash_UseMana[pUseSkill->Point - 1];

	if (chaPremiumitem.m_ManaReducePotiontime > 0 && chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - ((CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100) + (CheckMana * 20 / 100));

	else if (chaPremiumitem.m_ManaReducePotiontime > 0)
		CheckMana = CheckMana - (CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100);

	else if (chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - (CheckMana * 20 / 100);

	if (RequireStateCheck(CheckMana))
	{
		for (int i = 0; i < 10; i++)
		{
			if (pUseSkill->Skill_Info.UseWeaponCode[i] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt() & sinITEM_MASK2))
			{
				CheckCharForm();
				sinSetMana(sinGetMana() - CheckMana);
				sinSetStamina(sinGetStamina() - CheckStamina);
				cSkill.CheckSkillMasteryForm(pUseSkill);
				pUseSkill->Mastery = 0;
				cSkill.ReformSkillMasteryForm(pUseSkill);

				ReformCharForm();
				pUseSkill->UseSKillIncreCount++;
				if (pUseSkill->UseSKillIncreCount >= sinMasteryIncreaIndex[pUseSkill->Skill_Info.SkillNum] + ((pUseSkill->Point - 1) / 3))
				{
					pUseSkill->UseSKillIncreCount = 0;
					pUseSkill->UseSkillCount += USE_SKILL_MASTERY_COUNT;
				}
				return TRUE;
			}
		}
	}
	return FALSE;

}

int F_Ground_Pike()
{
	CheckMana = G_Pike_UseMana[pUseSkill->Point - 1];

	if (chaPremiumitem.m_ManaReducePotiontime > 0 && chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - ((CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100) + (CheckMana * 20 / 100));

	else if (chaPremiumitem.m_ManaReducePotiontime > 0)
		CheckMana = CheckMana - (CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100);

	else if (chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - (CheckMana * 20 / 100);

	if (RequireStateCheck(CheckMana))
	{
		if (pUseSkill->Skill_Info.UseWeaponCode[0] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt() & sinITEM_MASK2))
		{
			CheckCharForm();
			sinSetMana(sinGetMana() - CheckMana);
			sinSetStamina(sinGetStamina() - CheckStamina);
			cSkill.CheckSkillMasteryForm(pUseSkill);
			pUseSkill->Mastery = 0;
			cSkill.ReformSkillMasteryForm(pUseSkill);

			ReformCharForm();
			pUseSkill->UseSKillIncreCount++;
			if (pUseSkill->UseSKillIncreCount >= sinMasteryIncreaIndex[pUseSkill->Skill_Info.SkillNum] + ((pUseSkill->Point - 1) / 3))
			{
				pUseSkill->UseSKillIncreCount = 0;
				pUseSkill->UseSkillCount += USE_SKILL_MASTERY_COUNT;
			}
			return TRUE;
		}
	}
	return FALSE;
}

int F_Tornado_Pike()
{
	CheckMana = Tornado_UseMana[pUseSkill->Point - 1];

	if (chaPremiumitem.m_ManaReducePotiontime > 0 && chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - ((CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100) + (CheckMana * 20 / 100));

	else if (chaPremiumitem.m_ManaReducePotiontime > 0)
		CheckMana = CheckMana - (CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100);

	else if (chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - (CheckMana * 20 / 100);

	if (RequireStateCheck(CheckMana))
	{
		if (pUseSkill->Skill_Info.UseWeaponCode[0] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt() & sinITEM_MASK2))
		{
			CheckCharForm();
			sinSetMana(sinGetMana() - CheckMana);
			sinSetStamina(sinGetStamina() - CheckStamina);
			cSkill.CheckSkillMasteryForm(pUseSkill);
			pUseSkill->Mastery = 0;
			cSkill.ReformSkillMasteryForm(pUseSkill);
			ReformCharForm();
			pUseSkill->UseSKillIncreCount++;
			if (pUseSkill->UseSKillIncreCount >= sinMasteryIncreaIndex[pUseSkill->Skill_Info.SkillNum] + ((pUseSkill->Point - 1) / 3))
			{
				pUseSkill->UseSKillIncreCount = 0;
				pUseSkill->UseSkillCount += USE_SKILL_MASTERY_COUNT;

			}
			return TRUE;
		}
	}
	return FALSE;
}

int F_Weapone_Defence_Mastery()
{
	cInvenTory.SetItemToChar();

	return TRUE;
}
int F_Expansion()
{
	CheckMana = Expansion_UseMana[pUseSkill->Point - 1];

	if (chaPremiumitem.m_ManaReducePotiontime > 0 && chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - ((CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100) + (CheckMana * 20 / 100));

	else if (chaPremiumitem.m_ManaReducePotiontime > 0)
		CheckMana = CheckMana - (CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100);

	else if (chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - (CheckMana * 20 / 100);

	if (RequireStateCheck(CheckMana))
	{
		for (int i = 0; i < 10; i++)
		{
			if (pUseSkill->Skill_Info.UseWeaponCode[i] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt() & sinITEM_MASK2))
			{
				CheckCharForm();
				sinSetMana(sinGetMana() - CheckMana);
				sinSetStamina(sinGetStamina() - CheckStamina);
				cSkill.CheckSkillMasteryForm(pUseSkill);
				pUseSkill->Mastery = 0;
				cSkill.ReformSkillMasteryForm(pUseSkill);

				ReformCharForm();
				pUseSkill->UseSKillIncreCount++;
				if (pUseSkill->UseSKillIncreCount >= sinMasteryIncreaIndex[pUseSkill->Skill_Info.SkillNum] + ((pUseSkill->Point - 1) / 3))
				{
					pUseSkill->UseSKillIncreCount = 0;
					pUseSkill->UseSkillCount += USE_SKILL_MASTERY_COUNT;

				}
				return TRUE;
			}
		}
	}
	return FALSE;

}
int F_Scout_Hawk()
{
	int SkillIndex = 0;

	CheckMana = Scout_Hawk_UseMana[pUseSkill->Point - 1];

	if (chaPremiumitem.m_ManaReducePotiontime > 0 && chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - ((CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100) + (CheckMana * 20 / 100));

	else if (chaPremiumitem.m_ManaReducePotiontime > 0)
		CheckMana = CheckMana - (CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100);

	else if (chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - (CheckMana * 20 / 100);

	if (RequireStateCheck(CheckMana))
	{
		CheckCharForm();
		pUseSkill->UseTime = int(float(Scout_Hawk_UseTime[pUseSkill->Point - 1]) * 2.5f);
		sinContinueSkillSet(pUseSkill);
		SwitchSkill(pUseSkill);
		sinSetMana(sinGetMana() - CheckMana);
		sinSetStamina(sinGetStamina() - CheckStamina);
		cSkill.CheckSkillMasteryForm(pUseSkill);
		pUseSkill->Mastery = 0;
		cSkill.ReformSkillMasteryForm(pUseSkill);

		ReformCharForm();
		pUseSkill->UseSKillIncreCount++;
		if (pUseSkill->UseSKillIncreCount >= sinMasteryIncreaIndex[pUseSkill->Skill_Info.SkillNum] + ((pUseSkill->Point - 1) / 3))
		{
			pUseSkill->UseSKillIncreCount = 0;
			pUseSkill->UseSkillCount += USE_SKILL_MASTERY_COUNT;
		}
		return TRUE;
	}
	return FALSE;

}
int F_Shooting_Mastery()
{
	cInvenTory.SetItemToChar();
	return TRUE;
}
int F_Wind_Arrow()
{
	CheckMana = Wind_Arrow_UseMana[pUseSkill->Point - 1];

	if (chaPremiumitem.m_ManaReducePotiontime > 0 && chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - ((CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100) + (CheckMana * 20 / 100));

	else if (chaPremiumitem.m_ManaReducePotiontime > 0)
		CheckMana = CheckMana - (CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100);

	else if (chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - (CheckMana * 20 / 100);

	if (RequireStateCheck(CheckMana))
	{
		if (pUseSkill->Skill_Info.UseWeaponCode[0] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt() & sinITEM_MASK2))
		{
			CheckCharForm();
			sinSetMana(sinGetMana() - CheckMana);
			sinSetStamina(sinGetStamina() - CheckStamina);
			cSkill.CheckSkillMasteryForm(pUseSkill);
			pUseSkill->Mastery = 0;
			cSkill.ReformSkillMasteryForm(pUseSkill);

			ReformCharForm();
			pUseSkill->UseSKillIncreCount++;
			if (pUseSkill->UseSKillIncreCount >= sinMasteryIncreaIndex[pUseSkill->Skill_Info.SkillNum] + ((pUseSkill->Point - 1) / 3))
			{
				pUseSkill->UseSKillIncreCount = 0;
				pUseSkill->UseSkillCount += USE_SKILL_MASTERY_COUNT;

			}
			return TRUE;
		}
	}
	return FALSE;
}
int F_Perfect_Aim()
{
	CheckMana = Perfect_Aim_UseMana[pUseSkill->Point - 1];

	if (chaPremiumitem.m_ManaReducePotiontime > 0 && chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - ((CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100) + (CheckMana * 20 / 100));

	else if (chaPremiumitem.m_ManaReducePotiontime > 0)
		CheckMana = CheckMana - (CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100);

	else if (chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - (CheckMana * 20 / 100);

	if (RequireStateCheck(CheckMana))
	{
		if (pUseSkill->Skill_Info.UseWeaponCode[0] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt() & sinITEM_MASK2))
		{
			CheckCharForm();
			sinSetMana(sinGetMana() - CheckMana);
			sinSetStamina(sinGetStamina() - CheckStamina);
			cSkill.CheckSkillMasteryForm(pUseSkill);
			pUseSkill->Mastery = 0;
			cSkill.ReformSkillMasteryForm(pUseSkill);

			ReformCharForm();
			pUseSkill->UseSKillIncreCount++;
			if (pUseSkill->UseSKillIncreCount >= sinMasteryIncreaIndex[pUseSkill->Skill_Info.SkillNum] + ((pUseSkill->Point - 1) / 3))
			{
				pUseSkill->UseSKillIncreCount = 0;
				pUseSkill->UseSkillCount += USE_SKILL_MASTERY_COUNT;
			}
			return TRUE;
		}
	}
	return FALSE;
}

int F_Dions_Eye()
{
	cInvenTory.SetItemToChar();
	return TRUE;
}

int F_Falcon()
{
	CheckMana = Falcon_UseMana[pUseSkill->Point - 1];

	if (chaPremiumitem.m_ManaReducePotiontime > 0 && chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - ((CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100) + (CheckMana * 20 / 100));

	else if (chaPremiumitem.m_ManaReducePotiontime > 0)
		CheckMana = CheckMana - (CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100);

	else if (chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - (CheckMana * 20 / 100);

	if (RequireStateCheck(CheckMana))
	{
		CheckCharForm();
		SwitchSkill(pUseSkill);
		sinSetMana(sinGetMana() - CheckMana);
		sinSetStamina(sinGetStamina() - CheckStamina);
		cSkill.CheckSkillMasteryForm(pUseSkill);
		pUseSkill->Mastery = 0;
		cSkill.ReformSkillMasteryForm(pUseSkill);

		pUseSkill->UseTime = Falcon_Time[pUseSkill->Point - 1];
		sinContinueSkillSet(pUseSkill);

		ReformCharForm();
		pUseSkill->UseSKillIncreCount++;
		if (pUseSkill->UseSKillIncreCount >= sinMasteryIncreaIndex[pUseSkill->Skill_Info.SkillNum] + ((pUseSkill->Point - 1) / 3))
		{
			pUseSkill->UseSKillIncreCount = 0;
			pUseSkill->UseSkillCount += USE_SKILL_MASTERY_COUNT;

		}
		return TRUE;

	}
	return FALSE;
}

int F_Arrow_of_Rage()
{
	CheckMana = A_Rage_UseMana[pUseSkill->Point - 1];

	if (chaPremiumitem.m_ManaReducePotiontime > 0 && chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - ((CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100) + (CheckMana * 20 / 100));

	else if (chaPremiumitem.m_ManaReducePotiontime > 0)
		CheckMana = CheckMana - (CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100);

	else if (chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - (CheckMana * 20 / 100);

	if (RequireStateCheck(CheckMana))
	{
		if (pUseSkill->Skill_Info.UseWeaponCode[0] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt() & sinITEM_MASK2))
		{
			CheckCharForm();
			sinSetMana(sinGetMana() - CheckMana);
			sinSetStamina(sinGetStamina() - CheckStamina);
			cSkill.CheckSkillMasteryForm(pUseSkill);
			pUseSkill->Mastery = 0;
			cSkill.ReformSkillMasteryForm(pUseSkill);

			ReformCharForm();
			pUseSkill->UseSKillIncreCount++;
			if (pUseSkill->UseSKillIncreCount >= sinMasteryIncreaIndex[pUseSkill->Skill_Info.SkillNum] + ((pUseSkill->Point - 1) / 3))
			{
				pUseSkill->UseSKillIncreCount = 0;
				pUseSkill->UseSkillCount += USE_SKILL_MASTERY_COUNT;
			}
			return TRUE;
		}
	}
	return FALSE;

}
int F_Avalanche()
{
	CheckMana = Avalanche_UseMana[pUseSkill->Point - 1];

	if (chaPremiumitem.m_ManaReducePotiontime > 0 && chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - ((CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100) + (CheckMana * 20 / 100));

	else if (chaPremiumitem.m_ManaReducePotiontime > 0)
		CheckMana = CheckMana - (CheckMana * chaPremiumitem.m_ManaReducePotionValue / 100);

	else if (chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		CheckMana = CheckMana - (CheckMana * 20 / 100);

	if (RequireStateCheck(CheckMana))
	{
		if (pUseSkill->Skill_Info.UseWeaponCode[0] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sBaseItemID.ToInt() & sinITEM_MASK2))
		{
			CheckCharForm();
			sinSetMana(sinGetMana() - CheckMana);
			sinSetStamina(sinGetStamina() - CheckStamina);
			cSkill.CheckSkillMasteryForm(pUseSkill);
			pUseSkill->Mastery = 0;
			cSkill.ReformSkillMasteryForm(pUseSkill);

			ReformCharForm();
			pUseSkill->UseSKillIncreCount++;
			if (pUseSkill->UseSKillIncreCount >= sinMasteryIncreaIndex[pUseSkill->Skill_Info.SkillNum] + ((pUseSkill->Point - 1) / 3))
			{
				pUseSkill->UseSKillIncreCount = 0;
				pUseSkill->UseSkillCount += USE_SKILL_MASTERY_COUNT;
			}
			return TRUE;
		}
	}
	return FALSE;
}
int F_Metal_Armor()
{
	pUseSkill->UseTime = Metal_Armor_Time[pUseSkill->Point - 1];
	sinContinueSkillSet(pUseSkill);
	sinUseManaStamina(pUseSkill);
	SwitchSkill(pUseSkill);
	cInvenTory.SetItemToChar();
	return TRUE;
}
int F_Grand_Smash()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
int F_M_W_Mastery()
{
	return TRUE;
}
int F_Spark_Shield()
{
	pUseSkill->UseTime = Spark_Shield_Time[pUseSkill->Point - 1];
	sinContinueSkillSet(pUseSkill);
	sinUseManaStamina(pUseSkill);
	SwitchSkill(pUseSkill);
	cInvenTory.SetItemToChar();
	return TRUE;
}
int F_Concentration()
{
	pUseSkill->UseTime = Concentration_Time[pUseSkill->Point - 1];
	sinContinueSkillSet(pUseSkill);
	sinUseManaStamina(pUseSkill);
	SwitchSkill(pUseSkill);
	cInvenTory.SetItemToChar();

	return TRUE;
}
int F_Avanging_Crash()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
int F_Swift_Axe()
{
	pUseSkill->UseTime = Swift_Axe_Time[pUseSkill->Point - 1];
	sinContinueSkillSet(pUseSkill);
	sinUseManaStamina(pUseSkill);
	SwitchSkill(pUseSkill);
	cInvenTory.SetItemToChar();

	return TRUE;
}
int F_Bone_Crash()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
int F_Venom_Spear()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
int F_Vanish()
{
	pUseSkill->UseTime = Vanish_Time[pUseSkill->Point - 1];
	sinContinueSkillSet(pUseSkill);
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
int F_Critical_Mastery()
{
	return TRUE;
}
int F_Chain_Lance()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
int F_E_Shot()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
int F_G_Falcon()
{
	pUseSkill->UseTime = Golden_Falcon_Time[pUseSkill->Point - 1];
	sinContinueSkillSet(pUseSkill);
	sinUseManaStamina(pUseSkill);
	SwitchSkill(pUseSkill);
	cInvenTory.SetItemToChar();
	return TRUE;
}
int F_B_Shot()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
int F_Perforation()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
int F_Impulsion()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
int F_Compulsion()
{
	pUseSkill->UseTime = Compulsion_Time[pUseSkill->Point - 1];
	sinContinueSkillSet(pUseSkill);
	sinUseManaStamina(pUseSkill);
	cInvenTory.SetItemToChar();
	return TRUE;
}
int F_Magnetic_Sphere()
{
	pUseSkill->UseTime = Magnetic_Sphere_Time[pUseSkill->Point - 1];
	sinContinueSkillSet(pUseSkill);
	sinUseManaStamina(pUseSkill);
	cInvenTory.SetItemToChar();
	return TRUE;
}
int F_Metal_Golem()
{
	pUseSkill->UseTime = 360;
	sinContinueSkillSet(pUseSkill);
	pUseSkill->SkillCodeIndex = TRUE;
	sinUseManaStamina(pUseSkill);
	cInvenTory.SetItemToChar();
	return TRUE;
}
int F_Destoryer()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
int F_Berserker()
{
	pUseSkill->UseTime = Berserker_Time[pUseSkill->Point - 1];
	sinContinueSkillSet(pUseSkill);
	SwitchSkill(pUseSkill);
	sinUseManaStamina(pUseSkill);
	cInvenTory.SetItemToChar();
	return TRUE;
}
int F_Cyclone_Strike()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
int F_Boost_Health()
{
	return TRUE;
}
int F_Assassin_Eye()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
int F_Charging_Strike()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
int F_Vague()
{
	pUseSkill->UseTime = Vague_Time[pUseSkill->Point - 1];
	sinContinueSkillSet(pUseSkill);
	sinUseManaStamina(pUseSkill);
	cInvenTory.SetItemToChar();
	return TRUE;
}
int F_Shadow_Master()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
//弓手
int F_Recall_Wolverin()
{
	pUseSkill->UseTime = 6 * 60;
	sinContinueSkillSet(pUseSkill);
	pUseSkill->SkillCodeIndex = TRUE;
	sinUseManaStamina(pUseSkill);
	cInvenTory.SetItemToChar();
	return TRUE;
}
int F_Evasion_Mastery()
{
	return TRUE;
}
int F_Phoenix_Shot()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
int F_Force_Of_Nature()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
// 机械
//霹雳旋风
int F_landminning()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
//快速打击
int F_H_Sonic()
{
	pUseSkill->UseTime = H_Sonic_Time[pUseSkill->Point - 1];
	sinContinueSkillSet(pUseSkill);
	sinUseManaStamina(pUseSkill);
	cInvenTory.SetItemToChar();
	return TRUE;
}
//究极之刃
int F_R_Smash()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
//战神祝福
int F_P_Enhence()
{
	pUseSkill->UseTime = P_Enhence_Time[pUseSkill->Point - 1];
	sinContinueSkillSet(pUseSkill);
	sinUseManaStamina(pUseSkill);
	cInvenTory.SetItemToChar();
	return TRUE;
}
// 武士
//狂暴怒斩
int F_D_Hit()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
//狂野冲击
int F_P_Dash()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
//回旋斩击
int F_M_Blow()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
//众神之怒
int F_B_Berserker()
{
	pUseSkill->UseTime = B_Berserker_Time[pUseSkill->Point - 1];
	sinContinueSkillSet(pUseSkill);
	SwitchSkill(pUseSkill);
	sinUseManaStamina(pUseSkill);
	cInvenTory.SetItemToChar();
	return TRUE;
}

// 枪兵
//回旋打击
int F_D_Reaper()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
//地枪奇袭
int F_F_Spear()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
//潜能激发
int F_Amplified()
{
	pUseSkill->UseTime = Amplified_Time[pUseSkill->Point - 1];
	sinContinueSkillSet(pUseSkill);
	sinUseManaStamina(pUseSkill);
	cInvenTory.SetItemToChar();
	return TRUE;
}
//旋风之枪
int F_SS_Attack()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
// 弓手

// 回旋之舞
int F_S_Shot()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
// 玄光之箭
int F_S_Rope()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
// 飓风之箭
int F_N_Splash()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
// 复仇箭雨
int F_C_Trap()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
// 刺客
//刺击
int F_Stringer()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
//闪击
int F_Running()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
//强化攻击
int F_Sword_Mastery()
{
	cInvenTory.SetItemToChar();
	return TRUE;
}
//弱点攻击
int F_Wisp()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
//毒牙连击
int F_Verom_Thorn()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
//敏捷之力
int F_Ales()
{
	pUseSkill->UseTime = Alas_Time[pUseSkill->Point - 1];
	sinContinueSkillSet(pUseSkill);
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
//灵魂震撼
int F_Soul_Shock()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
//攻击大师
int F_Blade_Mastery()
{
	cInvenTory.SetItemToChar();
	return TRUE;
}
//飞剑之舞
int F_Finishing_Blow()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
//跳斩
int F_Gust_Shash()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
//敏捷大师
int F_Inpes()
{
	pUseSkill->UseTime = Inpes_Time[pUseSkill->Point - 1];
	sinContinueSkillSet(pUseSkill);
	sinUseManaStamina(pUseSkill);
	cInvenTory.SetItemToChar();
	return TRUE;
}
//致盲
int F_Deception()
{
	pUseSkill->UseTime = Deception_Time[pUseSkill->Point - 1];
	sinContinueSkillSet(pUseSkill);
	sinUseManaStamina(pUseSkill);

	return TRUE;
}
//冰冻之刃
int F_Frost_Wind()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
//致命艺术
int F_Fatal_Mastery()
{
	cInvenTory.SetItemToChar();
	return TRUE;
};
//瘟疫之刃
int F_Pollute()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
//影子闪击
int F_Shadow()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
//影子火焰
int F_Shadow_Bomb()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
//地裂斩
int F_Rising_Shash()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
//猛龙摆尾
int F_Violent_Stub()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
//风暴之刃
int F_Shadow_Storm()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}