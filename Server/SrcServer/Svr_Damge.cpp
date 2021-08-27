#include "StdAfx.h"
#include "..\\character.h"
#include "..\\fileread.h"
#include "..\\playmain.h"
#include "..\\effectsnd.h"

#include "..\\record.h"
#include "..\\playsub.h"

#include "onserver.h"
#include "svr_Damage.h"

#define	PK_POWER_DIVIDE	5
#define	PK_SCORE_DIVIDE	10

extern int CastleBattleZone_LineZ;


WORD	rsDefaultDamage[10][2] =
{
	{	7,	14	},
	{	17,	40	},
	{	25,	50	},
	{	45,	74	},
	{	50,	80	},
	{	55,	86	},
	{	60,	90	},
	{	65,	100	},
	{	70,	110	},
	{	70,	110	}
};

#define PET_TERRY	0
#define PET_NEPSYS  1
#define PET_IO      2
#define PET_MUTE    3

#define PCBANG_PET_BURSTP	0
#define PCBANG_PET_BURSTS	1
#define PCBANG_PET_BURSTL	2
#define PCBANG_PET_BURSTD	3

int	dm_Critical_Temp;
int dm_SkillCode_Temp;

int GetCritical(User *lpPlayInfo, Unit *lpChar, int Critical_Hit);
int GetCritical2(User *lpPlayInfo, User *lpPlayInfo2, int Critical_Hit);

int	rsRecordCharDamage(User *lpPlayInfo, Unit *lpChar, int Damage);

int	rsRecord_PKDamage(User *lpPlayInfo, User *lpPlayInfo2, int Damage);

int rsSendAttackUser(User *lpPlayInfo, User *lpPlayInfo2, int Power, int AttackState, short sParam1 = 0, short sParam2 = 0);

#define	DISP_DAMAGE

#ifdef DISP_DAMAGE
static char szDispDamage[128];
static char szDispDamage2[128];	//ÇØ¿Ü

//µ¥¹ÌÁö Á¤º¸ Ãâ·Â
int rsDisplayDamgeToClient(User *lpPlayInfo, char *szDmgMsg)
{
	TRANS_CHATMESSAGE	TransChatMessage;

	if (lpPlayInfo->iGameLevel <= GAMELEVEL_Two) return FALSE;

	lstrcpy(TransChatMessage.szMessage, szDmgMsg);
	TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
	TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
	TransChatMessage.dwIP = 0;
	TransChatMessage.dwObjectSerial = 0;

	SENDPACKET(lpPlayInfo, &TransChatMessage);

	return TRUE;
}
#endif

//S2C °ø°Ý Ã½Å©¼¶
DWORD	dm_GetDamgeChkSum_S2V(TRANS_ATTACKDATA *lpTransAttackData)
{
	DWORD	dwChkSum;

	dwChkSum = lpTransAttackData->code;
	dwChkSum += lpTransAttackData->x^lpTransAttackData->y^lpTransAttackData->z;
	dwChkSum ^= lpTransAttackData->AttackState + lpTransAttackData->AttackSize;
	dwChkSum ^= lpTransAttackData->Power << 5;
	dwChkSum ^= lpTransAttackData->dwChkSum;
	dwChkSum ^= ((DWORD *)lpTransAttackData->sRating)[0];
	dwChkSum ^= 0x80516809;

	return dwChkSum;
}
DWORD	dm_GetCommandChkSum(smTRANS_COMMAND *lpTransCommand, DWORD dwObjectSerial)
{
	DWORD	dwChkSum;

	dwChkSum = lpTransCommand->code & 0x037C70FF;
	dwChkSum += dwObjectSerial << 5;
	dwChkSum ^= lpTransCommand->WParam ^ lpTransCommand->SParam;
	dwChkSum ^= lpTransCommand->code << 2;
	dwChkSum ^= lpTransCommand->LParam ^ lpTransCommand->EParam;
	dwChkSum ^= 0x009821CC;

	return dwChkSum;
}
DWORD	dm_GetRangeDamgeChkSum(TRANS_SKIL_ATTACKDATA2 *lpTransSkilAttackData2)
{
	DWORD	dwChkSum;

	dwChkSum = lpTransSkilAttackData2->code;
	dwChkSum += lpTransSkilAttackData2->x^lpTransSkilAttackData2->y^lpTransSkilAttackData2->z;
	dwChkSum += lpTransSkilAttackData2->AttackCount^lpTransSkilAttackData2->dwTime;
	dwChkSum ^= ((DWORD *)lpTransSkilAttackData2->Power)[0];
	dwChkSum ^= ((DWORD *)lpTransSkilAttackData2->Power2)[0];
	dwChkSum ^= ((DWORD *)lpTransSkilAttackData2->Critical)[0];
	dwChkSum ^= ((DWORD *)lpTransSkilAttackData2->MotionCount)[0];
	dwChkSum += lpTransSkilAttackData2->SkillCode;
	dwChkSum ^= 0x65028086;

	return dwChkSum;
}
DWORD	dm_GetDamgeChkSum(TRANS_ATTACKDATA2 *lpTransAttackData2)
{
	DWORD	dwChkSum;

	dwChkSum = lpTransAttackData2->code;
	dwChkSum += lpTransAttackData2->x^lpTransAttackData2->y^lpTransAttackData2->z;
	dwChkSum += lpTransAttackData2->AttackCount^lpTransAttackData2->dwTime;
	dwChkSum ^= ((DWORD *)lpTransAttackData2->Power)[0];
	dwChkSum ^= ((DWORD *)lpTransAttackData2->Power2)[0];
	dwChkSum ^= ((DWORD *)lpTransAttackData2->Critical)[0];
	dwChkSum ^= ((DWORD *)lpTransAttackData2->MotionCount)[0];
	dwChkSum += lpTransAttackData2->SkillCode;
	dwChkSum ^= 0x68098051;

	return dwChkSum;
}
int rsRecvAttackData_Old(User *lpPlayInfo, TRANS_ATTACKDATA *lpTransAttackData, Unit *lpTargetChar, int Type)
{
#ifdef	_W_SERVER
	DWORD	dwTime;
	TRANS_CHATMESSAGE TransChatMessage;
	Unit	*lpChar;
	smTRANS_COMMAND	smTransCommand;
	int		x, y, z;
	int		cnt, len;
	int		ang, ang2;
	int		regs;
	User	*lpPlayInfo2;

	int	Dmg1, Dmg2, Dmg3, Dmg4;
	int rs;

	int PowerType = FALSE;

	Dmg1 = 0;
	Dmg2 = 0;
	Dmg3 = 0;
	Dmg4 = 0;

	dwTime = SERVER_GAMETIME;

	lpPlayInfo->Recv_AttackCount++;
	lpPlayInfo->Recv_AttackDamage += lpTransAttackData->Power;

	if (lpPlayInfo->BadPlayer == TRUE)
		return FALSE;
	if (lpPlayInfo->bCloak && lpPlayInfo->iGameLevel < GAMELEVEL_Four)
		return FALSE;

	if (lpTargetChar)
		lpChar = lpTargetChar;
	else
		lpChar = SERVERUNIT->GetUnit(lpTransAttackData->dwTarObjectSerial);

	if (!lpChar || lpChar->sCharacterData.iType != CHARACTERTYPE_NPC)
		lpPlayInfo->AttackCount++;

	if ((SERVER_GAMETIME - lpPlayInfo->dwAttackTime) > 5000)
	{
		lpPlayInfo->dwAttackTime = SERVER_GAMETIME;
		if (lpPlayInfo->AttackCount >= 40)
		{
			smTransCommand.WParam = 1823;
			smTransCommand.SParam = lpPlayInfo->AttackCount;
			smTransCommand.LParam = lpPlayInfo->AttackCount;

			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.code = smTRANSCODE_SET_BLACKLIST;
			rsSendDataServer(lpPlayInfo, &smTransCommand);
			if (lpPlayInfo->AttackCount >= 80)
				lpPlayInfo->BadPlayer = TRUE;

			return FALSE;
		}
		lpPlayInfo->AttackCount = 0;
	}
	if (!Type && lpTransAttackData->dwChkSum != (DWORD)(lpTransAttackData->Power * 2002 + (lpTransAttackData->x*lpTransAttackData->y*lpTransAttackData->z)))
	{
		smTransCommand.WParam = 1820;
		smTransCommand.SParam = lpTransAttackData->Power;
		smTransCommand.LParam = lpTransAttackData->Power;

		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.code = smTRANSCODE_SET_BLACKLIST;
		rsSendDataServer(lpPlayInfo, &smTransCommand);

		lpPlayInfo->BadPlayer = TRUE;
		return FALSE;
	}

	if (lpChar && lpChar->dwExclusiveNum == rsHARDCORE_EVENT_FLAG)
	{
		if (lpPlayInfo->dwExclusiveNum != rsHARDCORE_EVENT_FLAG)
			return FALSE;
	}
	if (lpChar)
	{
		lpChar->dwLastActiveTime = SERVER_GAMETIME;

		x = (lpPlayInfo->sPosition.iX - lpChar->pX) >> FLOATNS;
		y = (lpPlayInfo->sPosition.iY - lpChar->pY) >> FLOATNS;
		z = (lpPlayInfo->sPosition.iZ - lpChar->pZ) >> FLOATNS;
		if (abs(y) > 100 || (x*x + z * z) > (800 * 800))
			return FALSE;
		x = (lpPlayInfo->sPosition.iX - lpTransAttackData->x) >> FLOATNS;
		y = (lpPlayInfo->sPosition.iY - lpTransAttackData->y) >> FLOATNS;
		z = (lpPlayInfo->sPosition.iZ - lpTransAttackData->z) >> FLOATNS;

		if (lpChar->psModelAnimation && lpChar->psModelAnimation->iType != ANIMATIONTYPE_Die && lpChar->psModelAnimation->iType != ANIMATIONTYPE_Special)
		{
			Dmg1 = lpTransAttackData->Power;

			if (lpChar->sCharacterData.iType != CHARACTERTYPE_None)
			{
				if (lpPlayInfo->BadPlayer == 2 || lpPlayInfo->BadPlayer == 4)
				{
					cnt = lpPlayInfo->sCharacterData.iLevel / 10;
					if (cnt < 1 || cnt>8)
						cnt = 1;

					cnt = GetRandomPos(rsDefaultDamage[cnt][0], rsDefaultDamage[cnt][1]);
					if (cnt < lpTransAttackData->Power)
						lpTransAttackData->Power = cnt;
				}
				lpPlayInfo->pcLastAttack = lpChar;
				lpPlayInfo->lLastAttackID = lpChar->iID;

				lpChar->iStunTimeLeft = 0;

				if (lpPlayInfo->dwSkill_EnchantWeapon_Time)
				{
					if (lpPlayInfo->dwSkill_EnchantWeapon_Time > SERVER_GAMETIME)
					{
						if (((lpTransAttackData->AttackState >> 16) & 0xF) == 0)
						{
							len = lpPlayInfo->dwSkill_EnchantWeapon_Param & 0xFF;

							switch (lpPlayInfo->dwSkill_EnchantWeapon_Param >> 8)
							{
							case 0:
								lpTransAttackData->Power += GetRandomPos(Enchant_Weapon_Damage_Ice[len - 1][0], Enchant_Weapon_Damage_Ice[len - 1][1]);
								lpTransAttackData->AttackState |= (sITEMINFO_ICE + 1) << 16;
								lpTransAttackData->AttackState |= (Enchant_Weapon_Damage_Ice[len - 1][1]) << (16 + 4);
								break;
							case 1:
								lpTransAttackData->Power += GetRandomPos(Enchant_Weapon_Damage_Lightning[len - 1][0], Enchant_Weapon_Damage_Lightning[len - 1][1]);
								lpTransAttackData->AttackState |= (sITEMINFO_LIGHTING + 1) << 16;
								lpTransAttackData->AttackState |= (Enchant_Weapon_Damage_Lightning[len - 1][1]) << (16 + 4);
								break;
							case 2:
								lpTransAttackData->Power += GetRandomPos(Enchant_Weapon_Damage_Fire[len - 1][0], Enchant_Weapon_Damage_Fire[len - 1][1]);
								lpTransAttackData->AttackState |= (sITEMINFO_FIRE + 1) << 16;
								lpTransAttackData->AttackState |= (Enchant_Weapon_Damage_Fire[len - 1][1]) << (16 + 4);
								break;
							}
						}
					}
					else
					{
						lpPlayInfo->dwSkill_EnchantWeapon_Time = 0;
						lpPlayInfo->dwSkill_EnchantWeapon_Param = 0;
					}
				}
				regs = (lpTransAttackData->AttackState >> 16) & 0xF;

				if (regs && regs < sITEMINFO_NONE)
				{
					cnt = lpTransAttackData->AttackState >> (16 + 4);
					if (!cnt)
						cnt = lpTransAttackData->Power;

					len = lpChar->sCharacterData.sElementalDef[regs - 1];
					if (len)
					{
						if (len >= 100)
							len = 100;
						if (len <= -100)
							len = -100;
						lpTransAttackData->Power -= ((cnt*len) / 100);

						if (lpTransAttackData->Power < 0)
							lpTransAttackData->Power = 0;
					}
					switch (regs - 1)
					{
					case sITEMINFO_ICE:
						if (lpPlayInfo->dwSkill_EnchantWeapon_Time > SERVER_GAMETIME && (lpPlayInfo->dwSkill_EnchantWeapon_Param >> 8) == 0)
						{
							lpChar->PlaySlowCount = 16 * 3;
							lpChar->PlaySlowCount -= (lpChar->PlaySlowCount*len) / 100;
							lpChar->PlaySlowSpeed = 230 - 10 * (lpPlayInfo->dwSkill_EnchantWeapon_Param & 0xFF);
							lpChar->iDistortion = 0;
							break;
						}
						if (lpPlayInfo->dwSkill_DancingSword_Time > SERVER_GAMETIME && (lpPlayInfo->dwSkill_DancingSword_Param & 0xFF) == 0)
						{
							lpChar->PlaySlowCount = 16 * 5;
							lpChar->PlaySlowCount -= (lpChar->PlaySlowCount*len) / 100;
							lpChar->PlaySlowSpeed = 230 - 10 * (lpPlayInfo->dwSkill_DancingSword_Param >> 16);
							lpChar->iDistortion = 0;
							break;
						}
						if (dm_SkillCode_Temp == SKILL_PLAY_ELEMENT_ATTACK)
						{
							lpChar->PlaySlowCount = 16 * 10;
							lpChar->PlaySlowCount -= (lpChar->PlaySlowCount*len) / 100;
							lpChar->PlaySlowSpeed = 180;
							lpChar->iDistortion = 0;
							break;
						}
						if (dm_SkillCode_Temp == SKILL_PLAY_PET_ATTACK)
						{
							lpChar->PlaySlowCount = 16 * 10;
							lpChar->PlaySlowCount -= (lpChar->PlaySlowCount*len) / 100;
							lpChar->PlaySlowSpeed = 180;
							lpChar->iDistortion = 0;
							break;
						}
						if (lpPlayInfo->sCharacterData.iClass == CHARACTERCLASS_Priestess && (dm_SkillCode_Temp & 0xFF) == SKILL_PLAY_P_ICE)
						{
							lpChar->PlaySlowCount = ((dm_SkillCode_Temp >> 8) & 0xFF) * 16;
							lpChar->PlaySlowCount -= (lpChar->PlaySlowCount*len) / 100;
							lpChar->PlaySlowSpeed = 100;
							lpChar->iDistortion = 0;
						}
						if (lpPlayInfo->dwSkill_FrostJavelin_Time > SERVER_GAMETIME)
						{
							lpChar->PlaySlowCount = 16 * Frost_Javelin_IceTime[lpPlayInfo->dwSkill_FrostJavelin_Param];
							lpChar->PlaySlowCount -= (lpChar->PlaySlowCount*len) / 100;
							lpChar->PlaySlowSpeed = 240 - (240 * Frost_Javelin_SpeedSubPercent[lpPlayInfo->dwSkill_FrostJavelin_Param]) / 100;
							lpChar->iDistortion = 0;
							break;
						}
						break;
					case sITEMINFO_POISON:
						lpChar->PlayPoison[1] = 5 * 17;
						lpChar->PlayPoison[0] = 20;
						break;
					}
				}

				if (regs == sITEMINFO_STUN)
				{
					cnt = lpTransAttackData->AttackState >> 24;

					if (cnt > 0)
					{
						rs = lpChar->sCharacterData.sElementalDef[sITEMINFO_BIONIC];

						if (rs < 0)
							rs = 0;
						if (rs >= 100)
							rs = 100;
						rs = 100 - rs;

						if (rand() % 100 < cnt)
						{
							lpChar->iStunTimeLeft = lpTransAttackData->Power << 4;
							lpChar->iStunTimeLeft = (lpChar->iStunTimeLeft * rs) / 100;
						}
					}
					lpTransAttackData->Power = 0;
				}
				if (regs == sITEMINFO_SPEED)
				{
					cnt = lpTransAttackData->Power * 17; //¼õËÙÊ±¼ä
					rs = 240 - (lpTransAttackData->AttackState >> 24) * 240 / 100; //¼õËÙËÙÂÊ

					lpChar->PlaySlowCount = cnt;
					lpChar->PlaySlowSpeed = rs;
					lpChar->iDistortion = cnt;

					lpTransAttackData->Power = 0;
				}
				if (regs == sITEMINFO_MOVESPEED)
				{
					cnt = lpTransAttackData->Power * 17; //ËõÐ¡Ê±¼ä

					rs = 240 - (lpTransAttackData->AttackState >> 24) * 240 / 100; //¼õËÙËÙÂÊ

					lpChar->PlaySlowCount = cnt;
					lpChar->PlaySlowSpeed = rs;
					lpChar->PlayWeb = cnt;

					lpTransAttackData->Power = 0;
				}

				cnt = (lpTransAttackData->Power * lpChar->sCharacterData.iAbsorbRating) / 100;
				cnt = lpTransAttackData->Power - cnt;

				Dmg2 = lpTransAttackData->Power;
				Dmg3 = cnt;
				Dmg4 = cnt;

				if ((lpChar->sCharacterData.sHP.sMax / 4) < cnt && lpChar->sCharacterData.iLevel > lpPlayInfo->sCharacterData.iLevel)
					cnt = GetRandomPos(lpChar->sCharacterData.sHP.sMax / 8, lpChar->sCharacterData.sHP.sMax / 4);

				if (cnt > 0)
				{
					if (lpChar->sCharacterData.sHP.sMin == lpChar->sCharacterData.sHP.sMax)
					{
						if (!lpChar->pcLastAttacker)
						{
							lpChar->pcLastAttacker = lpPlayInfo;
							lpChar->iDamageLastAttacker = 0;
							lpChar->dwExpAttackTime = dwTime;
						}
					}
					if (lpChar->pcLastAttacker)
					{
						if (lpChar->pcLastAttacker == lpPlayInfo)
						{
							lpChar->iDamageLastAttacker += cnt;
							lpChar->dwExpAttackTime = dwTime;
						}
						else
						{
							if ((dwTime - lpChar->dwExpAttackTime) > 15000)
								lpChar->pcLastAttacker = 0;
						}
					}
					if (lpPlayInfo->dwSkill_HolyValor_Time)
					{
						if (lpPlayInfo->dwSkill_HolyValor_Time > SERVER_GAMETIME)
						{
							if (lpChar->sCharacterData.iMonsterType == MONSTERTYPE_Undead)
								cnt += (cnt*lpPlayInfo->dwSkill_HolyValor_Param) / 100;
						}
						else
						{
							lpPlayInfo->dwSkill_HolyValor_Time = 0;
							lpPlayInfo->dwSkill_HolyValor_Param = 0;
						}
					}
					if (lpPlayInfo->dwSkill_Advent_Migal_Time)
					{
						if (lpPlayInfo->dwSkill_Advent_Migal_Time > SERVER_GAMETIME)
							cnt += lpPlayInfo->dwSkill_Advent_Migal_Param;
						else
						{
							lpPlayInfo->dwSkill_Advent_Migal_Time = 0;
							lpPlayInfo->dwSkill_Advent_Migal_Param = 0;
						}
					}

					Dmg4 = cnt;

					lpChar->sCharacterData.sHP.sMin -= cnt;

					if (lpChar->psaDamageUsersData || lpChar->psaSiegeWarDataList)
						rsRecordCharDamage(lpPlayInfo, lpChar, cnt);

					if (lpChar->sCharacterData.iLevel > 14)
						cnt = (cnt * 5) / lpChar->sCharacterData.sHP.sMax;
					else
						cnt = (cnt * 10) / lpChar->sCharacterData.sHP.sMax;

					if (lpChar->sCharacterData.sHP.sMin > 0 && (cnt >= 1 || (lpTransAttackData->AttackState & 0xFFFF) > 1) && (rand() % 100) < lpChar->sUnitInfo.DamageStunPers)
					{
						ang2 = GetRadian2D(lpChar->pX, lpChar->pZ, lpPlayInfo->sPosition.iX, lpPlayInfo->sPosition.iZ);
						ang = (ang2 + ANGLE_180) & ANGCLIP;
						lpChar->Angle.y = ang;
						lpChar->MoveAngle(10);
						lpChar->Angle.y = ang2;

						if (lpChar->sCharacterData.sHP.sMin &&
							lpChar->psModelAnimation->iType != ANIMATIONTYPE_Flinch &&
							lpChar->psModelAnimation->iType != ANIMATIONTYPE_Potion &&
							lpChar->psModelAnimation->iType != ANIMATIONTYPE_Special &&
							lpChar->psModelAnimation->iType != ANIMATIONTYPE_Skill)
						{
							lpChar->SetMotionFromCode(ANIMATIONTYPE_Flinch);
							PowerType = TRUE;
						}
					}
				}
				lpPlayInfo->dwLastAttackTime = dwTime;
				if (dm_SkillCode_Temp != SKILL_PLAY_ELEMENT_ATTACK && regs != sITEMINFO_STUN && regs != sITEMINFO_SPEED && regs != sITEMINFO_MOVESPEED)
					SERVERMAP->OnSendDebugDamageUnit(lpChar, Dmg4, DAMAGEINFO_Normal);
			}
			else
			{
				//µã»÷NPC
				if (abs((int)(lpPlayInfo->dwLastAttackTime - dwTime)) > 1500)
				{
					lpPlayInfo->dwLastAttackTime = dwTime;

					if (lpChar->sUnitInfo.iQuestTypeID && lpChar->sUnitInfo.iQuestTypeID == (lpTransAttackData->AttackState >> 16))
					{
						if (rsProcessQuest(lpPlayInfo, lpChar, lpTransAttackData->AttackState >> 16, lpTransAttackData->AttackState & 0xFFFF) == TRUE)
							return TRUE;
					}
					if (lpChar->szMessage[0] && (!lpChar->sUnitInfo.iBellatraTypeNPC || lpChar->sUnitInfo.iBellatraTypeNPC == 5))
					{
						if (lpChar->sUnitInfo.iNumMessage > 1)
						{
							TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
							TransChatMessage.dwIP = 0;
							TransChatMessage.dwObjectSerial = lpChar->iID;
							lstrcpy(TransChatMessage.szMessage, lpChar->sUnitInfo.pszaMessage[rand() % lpChar->sUnitInfo.iNumMessage]);
							TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);

							SENDPACKET(lpPlayInfo, &TransChatMessage);
						}
						else
						{
							TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
							TransChatMessage.size = 32 + lstrlen(lpChar->szMessage);
							TransChatMessage.dwIP = 0;
							TransChatMessage.dwObjectSerial = lpChar->iID;
							lstrcpy(TransChatMessage.szMessage, lpChar->szMessage);

							SENDPACKET(lpPlayInfo, &TransChatMessage);
						}
					}
					if (lpChar->sUnitInfo.iWeaponShopCounter || lpChar->sUnitInfo.iDefenseShopCounter || lpChar->sUnitInfo.iMiscShopCounter)
						SendShopItemList(lpPlayInfo, lpChar);

					if (lpChar->sUnitInfo.iSkillMaster)
					{
						if (lpPlayInfo->iGameLevel != GAMELEVEL_None)
							SendSkillMenu(lpPlayInfo, lpChar, 2);
						else
							SendSkillMenu(lpPlayInfo, lpChar, lpChar->sUnitInfo.iSkillMasterRank);
					}
					if (lpChar->sUnitInfo.iWarehouse)
						SendOpenWareHouse(lpPlayInfo);
					if (lpChar->sUnitInfo.iMixMaster)
						SendOpenMixItem(lpPlayInfo, lpChar->sUnitInfo.iMixMaster);
					if (lpChar->sUnitInfo.iSmelting == NPCEVENTCODE_CoinShop)
						SENDPACKETBLANK(lpPlayInfo, PKTHDR_OpenCoinShop);
					if (lpChar->sUnitInfo.iItemBox)
						SENDPACKETBLANK(lpPlayInfo, PKTHDR_DistrbutorNPC);
					//if (lpChar->sUnitInfo.iSmelting)
						//SendOpenSmelting(lpPlayInfo);
					if (lpChar->sUnitInfo.Manufacture)
						SendOpenManufacture(lpPlayInfo);
					//if (lpChar->sUnitInfo.CollectMoney)
						//SendOpenCollectMoney(lpsmSock);
					if (lpChar->sUnitInfo.iEventGirl)
						SendOpenEventGift(lpPlayInfo);
					if (lpChar->sUnitInfo.iWarpgate)
					{
						smTransCommand.size = sizeof(smTRANS_COMMAND);
						smTransCommand.code = smTRANSCODE_WING_NPC;
						smTransCommand.WParam = lpChar->sUnitInfo.iWarpgate;
						smTransCommand.LParam = 0;
						smTransCommand.SParam = 0;
						SENDPACKET(lpPlayInfo, &smTransCommand);
					}

					if (lpChar->sUnitInfo.iTeleport)
					{
						int temp = 0;
						if (lpChar->sUnitInfo.iTeleport == 3)
							temp = -1;
						smTransCommand.size = sizeof(smTRANS_COMMAND);
						smTransCommand.code = smTRANSCODE_WING_NPC;
						smTransCommand.WParam = temp;
						smTransCommand.LParam = lpChar->sUnitInfo.iTeleport;
						smTransCommand.SParam = 0;

						SENDPACKET(lpPlayInfo, &smTransCommand);
					}
					if (lpChar->sUnitInfo.StarPointNpc && lpPlayInfo->sCharacterData.iLevel >= lpChar->sUnitInfo.StarPointNpc)
					{
						smTransCommand.size = sizeof(smTRANS_COMMAND);
						smTransCommand.code = smTRANSCODE_OPEN_STARPOINT;
						smTransCommand.WParam = 0;
						smTransCommand.LParam = 0;
						smTransCommand.SParam = 0;
						
						SENDPACKET(lpPlayInfo, &smTransCommand);
					}

					if (lpChar->sUnitInfo.GiveMoneyNpc)
					{
						smTransCommand.size = sizeof(smTRANS_COMMAND);
						smTransCommand.code = smTRANSCODE_OPEN_GIVEMONEY;
						smTransCommand.WParam = 0;
						smTransCommand.LParam = 0;
						smTransCommand.SParam = 0;

						SENDPACKET(lpPlayInfo, &smTransCommand);
					}
					if (lpChar->sUnitInfo.iBellatraTypeNPC)
					{
						if (lpChar->sUnitInfo.iBellatraTypeNPC == 5)
						{
							smTransCommand.size = sizeof(smTRANS_COMMAND);
							smTransCommand.code = smTRANSCODE_OPEN_COLLECT;
							smTransCommand.WParam = 5;
							smTransCommand.LParam = 0;
							smTransCommand.SParam = 0;

							SENDPACKET(lpPlayInfo, &smTransCommand);
						}
						else
							SendOpenEvent(lpChar, lpPlayInfo, lpChar->sUnitInfo.iBellatraTypeNPC);

						if (lpChar->psModelAnimation->iType < 0x100)
							lpChar->SetMotionFromCode(ANIMATIONTYPE_Attack);
					}
					if (lpChar->sUnitInfo.iAgeMaster)
						SendOpenAgingItem(lpPlayInfo);
					if (lpChar->sUnitInfo.ItemSocket)
						SendOpenSocketItem(lpPlayInfo);
					if (lpChar->sUnitInfo.iClanController)
						SendOpenClanMenu(lpPlayInfo);
					if (lpChar->sUnitInfo.iCastleController)
						SERVERBLESSCASTLE->ProcessPacket(lpPlayInfo);
					if (lpChar->sUnitInfo.PollingNpc)
					{
						smTransCommand.size = sizeof(smTRANS_COMMAND);
						smTransCommand.code = smTRANSCODE_PUBLIC_POLLING;
						smTransCommand.WParam = lpChar->sUnitInfo.PollingNpc;
						smTransCommand.LParam = 0;
						smTransCommand.SParam = 0;
						smTransCommand.EParam = 0;
						rsSendDataServer(lpPlayInfo, &smTransCommand);
					}
					if (lpChar->sUnitInfo.szMediaPlayNPC_Title && lpChar->sUnitInfo.szMediaPlayNPC_Path)
					{
						lstrcpy(TransChatMessage.szMessage, lpChar->sUnitInfo.szMediaPlayNPC_Path);
						len = lstrlen(TransChatMessage.szMessage);
						lstrcpy(TransChatMessage.szMessage + len + 1, lpChar->sUnitInfo.szMediaPlayNPC_Title);
						TransChatMessage.code = smTRANSCODE_MEDIA_NPC;
						TransChatMessage.size = 34 + len + lstrlen(lpChar->sUnitInfo.szMediaPlayNPC_Title);
						TransChatMessage.dwIP = 0;
						TransChatMessage.dwObjectSerial = lpChar->iID;

						SENDPACKET(lpPlayInfo, &TransChatMessage);
					}
					if (lpChar->sUnitInfo.MixtureReset)
						SendOpenMixtureItemReset(lpPlayInfo);
					if (lpChar->sUnitInfo.Element)
						SendOpenElementItem(lpPlayInfo);
					if (lpChar->pcOwner == lpPlayInfo && lpChar->sUnitInfo.Caravan)
						SendOpenCaravanItem(lpPlayInfo, lpChar->sUnitInfo.Caravan);
				}
			}
			if (lpChar->sCharacterData.sHP.sMin <= 0)
			{
				lpChar->SetMotionFromCode(ANIMATIONTYPE_Die);

				lpChar->pcKillerData = lpPlayInfo;
			}
		}
	}
	else
	{
		lpPlayInfo2 = SERVERUSER->GetUser(lpTransAttackData->dwTarObjectSerial);
		if (lpPlayInfo2)
		{
			if (lpPlayInfo->sCharacterData.iType != lpPlayInfo2->sCharacterData.iType)
			{
				if (lpPlayInfo->iGameLevel != GAMELEVEL_None || (lpPlayInfo->sCharacterData.iLevel > LIMIT_PK_LEVEL && lpPlayInfo2->sCharacterData.iLevel > LIMIT_PK_LEVEL))
					rsSendAttackUser(lpPlayInfo, lpPlayInfo2, lpTransAttackData->Power / PK_POWER_DIVIDE, 0x80);
			}
		}
	}
#endif		
	return TRUE;

}

//¹¥»÷·¶Î§ÓÃ»§Êý¾Ý¼ì²â
int rsRecvRangeAttackData_Old(User *lpPlayInfo, TRANS_SKIL_ATTACKDATA *lpTransSkilAttackData, int Type)
{
	smTRANS_COMMAND		smTransCommand;

	lpPlayInfo->Recv_AttackCount++;
	lpPlayInfo->Recv_AttackDamage += lpTransSkilAttackData->Power;

	if (lpPlayInfo->bCloak && lpPlayInfo->iGameLevel < GAMELEVEL_Four)
		return FALSE;

	RecvRangeAttack(lpPlayInfo, lpTransSkilAttackData);

	if (lpTransSkilAttackData->Power >= 1000)
	{
		smTransCommand.WParam = 1830;
		smTransCommand.SParam = lpTransSkilAttackData->Power;
		smTransCommand.LParam = smTransCommand.SParam;
		RecordHackLogFile(lpPlayInfo, &smTransCommand);

		//DisconnectUser(lpPlayInfo->lpsmSock);
	}
	return TRUE;
}

//¹¥»÷·¶Î§ÓÃ»§Êý¾Ý¼ì²â
int rsRecvRangeAttackUserData_Old(User *lpPlayInfo, TRANS_SKIL_ATTACKDATA *lpTransSkilAttackData)
{
	smTRANS_COMMAND	smTransCommand;

	lpPlayInfo->Recv_AttackCount++;
	lpPlayInfo->Recv_AttackDamage += lpTransSkilAttackData->Power;

	if (lpPlayInfo->bCloak && lpPlayInfo->iGameLevel < GAMELEVEL_Four) return FALSE;

	RecvRangeAttackUser(lpPlayInfo, lpTransSkilAttackData);

	if (lpTransSkilAttackData->Power >= 1000)
	{
		smTransCommand.WParam = 1830;
		smTransCommand.SParam = lpTransSkilAttackData->Power;
		smTransCommand.LParam = smTransCommand.SParam;
		RecordHackLogFile(lpPlayInfo, &smTransCommand);
		//DisconnectUser(lpPlayInfo->lpsmSock);
	}

	return TRUE;
}

//¼ì²â¹¥»÷·¶Î§
int	rsCheckAttackRange(int dx, int dy, int dz, Unit *lpChar, int dAttackSize)
{
	int x, y, z;

	x = (dx - lpChar->pX) >> FLOATNS;
	y = (dy - lpChar->pY) >> FLOATNS;
	z = (dz - lpChar->pZ) >> FLOATNS;

	if (abs(y) > 100 || (x*x + z * z) > dAttackSize)
		return FALSE;

	return TRUE;
}
//¼ì²â¹¥»÷·¶Î§
int	rsCheckAttackRange(int dx, int dy, int dz, User *lpPlayInfo)
{
	int x, y, z;

	x = (dx - lpPlayInfo->sPosition.iX) >> FLOATNS;
	y = (dy - lpPlayInfo->sPosition.iY) >> FLOATNS;
	z = (dz - lpPlayInfo->sPosition.iZ) >> FLOATNS;

	if (abs(y) > 100 || (x*x + z * z) > (300 * 300))
		return FALSE;

	return TRUE;
}


// ·¢ËÍ¹¥»÷ÓÃ»§
int rsSendAttackUser(User *lpPlayInfo, User *lpPlayInfo2, int Power, int AttackState, short sParam1, short sParam2)
{
	TRANS_ATTACKDATA TransAttackData;
	smTRANS_COMMAND	smTransCommand;
	int	temp;

	if (SERVERMAP->IsPVPMap(lpPlayInfo->iMapID) == FALSE)
		return FALSE;

	if (lpPlayInfo->iMapID == MAPID_BlessCastle && lpPlayInfo->sPosition.iZ < CastleBattleZone_LineZ)
		return FALSE;

	TransAttackData.code = smTRANSCODE_ATTACKDATA;
	TransAttackData.size = sizeof(TRANS_ATTACKDATA);

	TransAttackData.x = lpPlayInfo2->sPosition.iX;
	TransAttackData.y = lpPlayInfo2->sPosition.iY;
	TransAttackData.z = lpPlayInfo2->sPosition.iZ;

	TransAttackData.AttackState = AttackState;
	TransAttackData.AttackSize = 32 * fONE;
	TransAttackData.Power = Power;

	if (lpPlayInfo->dwSiegeItem_Scroll_Time && lpPlayInfo->dwSiegeItem_Scroll_Time < SERVER_GAMETIME)
	{
		lpPlayInfo->dwSiegeItem_Scroll_Code = 0;
		lpPlayInfo->dwSiegeItem_Scroll_Time = 0;
	}
	if (lpPlayInfo->dwSiegeItem_Stone1_Time && lpPlayInfo->dwSiegeItem_Stone1_Time < SERVER_GAMETIME)
	{
		lpPlayInfo->dwSiegeItem_Stone1_Code = 0;
		lpPlayInfo->dwSiegeItem_Stone1_Time = 0;
	}
	if (lpPlayInfo->dwSiegeItem_Stone2_Time && lpPlayInfo->dwSiegeItem_Stone2_Time < SERVER_GAMETIME)
	{
		lpPlayInfo->dwSiegeItem_Stone2_Code = 0;
		lpPlayInfo->dwSiegeItem_Stone2_Time = 0;
	}
	if (lpPlayInfo2->dwSiegeItem_Scroll_Time && lpPlayInfo2->dwSiegeItem_Scroll_Time < SERVER_GAMETIME)
	{
		lpPlayInfo2->dwSiegeItem_Scroll_Code = 0;
		lpPlayInfo2->dwSiegeItem_Scroll_Time = 0;
	}
	if (lpPlayInfo2->dwSiegeItem_Stone1_Time && lpPlayInfo2->dwSiegeItem_Stone1_Time < SERVER_GAMETIME)
	{
		lpPlayInfo2->dwSiegeItem_Stone1_Code = 0;
		lpPlayInfo2->dwSiegeItem_Stone1_Time = 0;
	}
	if (lpPlayInfo->dwSiegeItem_Stone2_Time && lpPlayInfo->dwSiegeItem_Stone2_Time < SERVER_GAMETIME)
	{
		lpPlayInfo->dwSiegeItem_Stone2_Code = 0;
		lpPlayInfo->dwSiegeItem_Stone2_Time = 0;
	}

	if (lpPlayInfo2->dwSiegeItem_Scroll_Code == (sinBC1 | sin01))
	{
		if (lpPlayInfo2->iMapID == MAPID_BlessCastle)
			return FALSE;
	}
	if (lpPlayInfo2->dwSiegeItem_Scroll_Code == (sinBI1 | sin05))
		return FALSE;

	if (lpPlayInfo2->dwSiegeItem_Scroll_Code == (sinBC1 | sin03))
	{
		if (lpPlayInfo2->iMapID == MAPID_BlessCastle)
		{
			if ((rand() % 100) < (int)lpPlayInfo2->dwSiegeItem_Scroll_Param)
			{
				smTransCommand.code = smTRANSCODE_SUCCESS_EVATION;
				smTransCommand.size = sizeof(smTRANS_COMMAND);
				smTransCommand.WParam = 0;
				smTransCommand.LParam = lpPlayInfo2->dwSiegeItem_Scroll_Code;
				smTransCommand.SParam = lpPlayInfo->iID;
				smTransCommand.EParam = 0;

				SENDPACKET(lpPlayInfo2, &smTransCommand);
				return FALSE;
			}
		}
	}
	if (lpPlayInfo2->dwSiegeItem_Scroll_Code == (sinBI1 | sin07))
	{
		if ((rand() % 100) < (int)lpPlayInfo2->dwSiegeItem_Scroll_Param)
		{
			smTransCommand.code = smTRANSCODE_SUCCESS_EVATION;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.WParam = 0;
			smTransCommand.LParam = lpPlayInfo2->dwSiegeItem_Scroll_Code;
			smTransCommand.SParam = lpPlayInfo->iID;
			smTransCommand.EParam = 0;

			SENDPACKET(lpPlayInfo2, &smTransCommand);
			return FALSE;
		}
	}

	if (lpPlayInfo->dwSiegeItem_Stone2_Code && lpPlayInfo2->sCharacterData.iClass == lpPlayInfo->dwSiegeItem_Stone2_Code)
		TransAttackData.Power += (TransAttackData.Power*lpPlayInfo->dwSiegeItem_Stone2_Param) / 100;

	if (lpPlayInfo2->dwSkill_PhysicalAbsorb_Time)
	{
		if (lpPlayInfo2->dwSkill_PhysicalAbsorb_Time > SERVER_GAMETIME)
		{
			TransAttackData.Power -= lpPlayInfo2->dwSkill_PhysicalAbsorb_Param;
			if (TransAttackData.Power < 0) return FALSE;
		}
		else
		{
			lpPlayInfo2->dwSkill_PhysicalAbsorb_Time = 0;
			lpPlayInfo2->dwSkill_PhysicalAbsorb_Param = 0;
		}
	}
	if (lpPlayInfo2->dwSkill_ExtreamShield_Time)
	{
		if (lpPlayInfo2->dwSkill_ExtreamShield_Time > SERVER_GAMETIME)
			TransAttackData.AttackState |= (lpPlayInfo2->dwSkill_ExtreamShield_Param << 16);
		else
		{
			lpPlayInfo2->dwSkill_ExtreamShield_Time = 0;
			lpPlayInfo2->dwSkill_ExtreamShield_Param = 0;
		}
	}
	if (lpPlayInfo2->dwSkill_MetalArmor_Time)
	{
		if (lpPlayInfo2->dwSkill_MetalArmor_Time > SERVER_GAMETIME)
		{
			TransAttackData.Power -= lpPlayInfo2->dwSkill_MetalArmor_Param;
			if (TransAttackData.Power < 0)
				return FALSE;
		}
		else
		{
			lpPlayInfo2->dwSkill_MetalArmor_Time = 0;
			lpPlayInfo2->dwSkill_MetalArmor_Param = 0;
		}
	}
	if (lpPlayInfo2->dwSkill_VirtualLife_Time)
	{
		if (lpPlayInfo2->dwSkill_VirtualLife_Time > SERVER_GAMETIME)
		{
			TransAttackData.Power -= (TransAttackData.Power*lpPlayInfo2->dwSkill_VirtualLife_Param) / 100;
			if (TransAttackData.Power < 0) return FALSE;
		}
		else
		{
			lpPlayInfo2->dwSkill_VirtualLife_Time = 0;
			lpPlayInfo2->dwSkill_VirtualLife_Param = 0;
		}
	}

	if (lpPlayInfo2->dwSkill_EnergyShield_Time)
	{
		if (lpPlayInfo2->dwSkill_EnergyShield_Time > SERVER_GAMETIME)
		{
			temp = (TransAttackData.Power*lpPlayInfo2->dwSkill_EnergyShield_Param) / 100;
			TransAttackData.Power -= temp;
			TransAttackData.AttackState |= (temp << 16);
			if (TransAttackData.Power < 0) return FALSE;
		}
		else
		{
			lpPlayInfo2->dwSkill_EnergyShield_Time = 0;
			lpPlayInfo2->dwSkill_EnergyShield_Param = 0;
		}
	}
	if (lpPlayInfo2->dwSkill_Compulsion_Time)
	{
		if (lpPlayInfo2->dwSkill_Compulsion_Time > SERVER_GAMETIME)
		{
			TransAttackData.Power -= lpPlayInfo2->dwSkill_Compulsion_Param;
			if (TransAttackData.Power < 0)
				return FALSE;
		}
		else
		{
			lpPlayInfo2->dwSkill_Compulsion_Time = 0;
			lpPlayInfo2->dwSkill_Compulsion_Param = 0;
		}
	}
	// ·è¿ñÅ­ºð
	if (lpPlayInfo2->dwSkill_Berserker_Time)
	{
		if (lpPlayInfo2->dwSkill_Berserker_Time > SERVER_GAMETIME)
		{
			TransAttackData.Power -= Berserker_SubAbsorb[lpPlayInfo2->dwSkill_Berserker_Param];
			if (TransAttackData.Power < 0)
				return FALSE;
		}
		else
		{
			lpPlayInfo2->dwSkill_Berserker_Time = 0;
			lpPlayInfo2->dwSkill_Berserker_Param = 0;
		}
	}
	if (lpPlayInfo2->dwSkill_Vague_Time)
	{
		if (lpPlayInfo2->dwSkill_Vague_Time > SERVER_GAMETIME)
		{
			if ((rand() % 100) < Vague_EvasionPercent[lpPlayInfo2->dwSkill_Vague_Param])
			{
				smTransCommand.code = smTRANSCODE_SUCCESS_EVATION;
				smTransCommand.size = sizeof(smTRANS_COMMAND);
				smTransCommand.WParam = 0;
				smTransCommand.LParam = SKILL_PLAY_VAGUE;
				smTransCommand.SParam = lpPlayInfo->iID;
				smTransCommand.EParam = CHARACTERCLASS_Pikeman;

				SENDPACKET(lpPlayInfo2, &smTransCommand);
				return FALSE;
			}
		}
		else
		{
			lpPlayInfo2->dwSkill_Vague_Time = 0;
			lpPlayInfo2->dwSkill_Vague_Param = 0;
		}
	}
	// Ç±ÄÜ¼¤·¢
	if (lpPlayInfo2->dwSkill_Amplified_Time)
	{
		if (lpPlayInfo2->dwSkill_Amplified_Time > SERVER_GAMETIME)
		{
			TransAttackData.Power -= Amplified_SubAbs[lpPlayInfo2->dwSkill_Amplified_Param];
			if (TransAttackData.Power < 0)
				return FALSE;
		}
		else
		{
			lpPlayInfo2->dwSkill_Amplified_Time = 0;
			lpPlayInfo2->dwSkill_Amplified_Param = 0;
		}
	}
	if (lpPlayInfo2->dwSkill_GodlyShied_Time)
	{
		if (lpPlayInfo2->dwSkill_GodlyShied_Time > SERVER_GAMETIME)
		{
			TransAttackData.Power -= (TransAttackData.Power*Godly_Shield_AbsorbPercent[lpPlayInfo2->dwSkill_GodlyShied_Param]) / 100;
			if (TransAttackData.Power < 0)
				return FALSE;
		}
		else
		{
			lpPlayInfo2->dwSkill_GodlyShied_Time = 0;
			lpPlayInfo2->dwSkill_GodlyShied_Param = 0;
		}
	}
	if (lpPlayInfo2->dwSkill_HallOfValhalla_Time)
	{
		if (lpPlayInfo2->dwSkill_HallOfValhalla_Time > SERVER_GAMETIME)
		{
			if ((rand() % 100) < (int)lpPlayInfo2->wSkill_HallOfValhalla_Param[0])
			{
				smTransCommand.code = smTRANSCODE_SUCCESS_EVATION;
				smTransCommand.size = sizeof(smTRANS_COMMAND);
				smTransCommand.WParam = 0;
				smTransCommand.LParam = SKILL_PLAY_HALL_OF_VALHALLA;
				smTransCommand.SParam = lpPlayInfo->iID;
				smTransCommand.EParam = CHARACTERCLASS_Atalanta;

				SENDPACKET(lpPlayInfo2, &smTransCommand);
				return FALSE;
			}
		}
		else
			lpPlayInfo2->dwSkill_HallOfValhalla_Time = 0;
	}
	if (lpPlayInfo2->dwSkill_SummonMuspell_Time)
	{
		if (lpPlayInfo2->dwSkill_SummonMuspell_Time > SERVER_GAMETIME)
		{
			if ((rand() % 100) < Summon_Muspell_BlockPercent[lpPlayInfo2->dwSkill_SummonMuspell_Param])
			{
				smTransCommand.code = smTRANSCODE_SUCCESS_EVATION;
				smTransCommand.size = sizeof(smTRANS_COMMAND);
				smTransCommand.WParam = 0;
				smTransCommand.LParam = SKILL_PLAY_SUMMON_MUSPELL;
				smTransCommand.SParam = lpPlayInfo->iID;
				smTransCommand.EParam = CHARACTERCLASS_Priestess;

				SENDPACKET(lpPlayInfo2, &smTransCommand);
				return FALSE;
			}
		}
		else
		{
			lpPlayInfo2->dwSkill_SummonMuspell_Time = 0;
			lpPlayInfo2->dwSkill_SummonMuspell_Param = 0;
		}
	}
	// ÌìÅ®É¢»¨
	if (lpPlayInfo2->dwSkill_Krishna_Time)
	{
		if (lpPlayInfo2->dwSkill_Krishna_Time > SERVER_GAMETIME)
		{
			if (lpPlayInfo2->dwSkill_Krishna_Time > SERVER_GAMETIME)
			{
				if ((rand() % 100) < Summon_Muspell_BlockPercent[lpPlayInfo2->dwSkill_SummonMuspell_Param])
				{
					smTransCommand.code = smTRANSCODE_SUCCESS_EVATION;
					smTransCommand.size = sizeof(smTRANS_COMMAND);
					smTransCommand.WParam = 0;
					smTransCommand.LParam = SKILL_PLAY_B_KRISHNA;
					smTransCommand.SParam = lpPlayInfo->iID;
					smTransCommand.EParam = CHARACTERCLASS_Priestess;

					SENDPACKET(lpPlayInfo2, &smTransCommand);
					return FALSE;
				}
				TransAttackData.Power -= B_Krishna_Abs[lpPlayInfo2->dwSkill_Krishna_Param];
				if (TransAttackData.Power < 0)
					return FALSE;
			}
			else
			{
				lpPlayInfo2->dwSkill_Krishna_Time = 0;
				lpPlayInfo2->dwSkill_Krishna_Param = 0;
			}
		}
	}
	//ÆíÓêÊ¦ÎüÊÕÐ§¹û
	if (lpPlayInfo2->dwSkill_Rainmaker_Time)
	{
		if (lpPlayInfo2->dwSkill_Rainmaker_Time > SERVER_GAMETIME)
		{
			TransAttackData.Power -= (TransAttackData.Power*Rainmaker_Abs[lpPlayInfo2->dwSkill_Rainmaker_Param]) / 100;
			if (TransAttackData.Power < 0)
				return FALSE;
		}
		else
		{
			lpPlayInfo2->dwSkill_Rainmaker_Param = 0;
			lpPlayInfo2->dwSkill_Rainmaker_Time = 0;
		}
	}

	TransAttackData.sRating[0] = sParam1;
	TransAttackData.sRating[1] = sParam2;

	TransAttackData.dwDestObjectSerial = lpPlayInfo->iID;
	TransAttackData.dwTarObjectSerial = lpPlayInfo2->iID;
	TransAttackData.dwChkSum = TransAttackData.Power * 2002 + (TransAttackData.x * TransAttackData.y * TransAttackData.z);

	if (lpPlayInfo2)
	{
		lpPlayInfo2->Send_AttackCount++;
		lpPlayInfo2->Send_AttackDamage += TransAttackData.Power;

		rsRecord_PKDamage(lpPlayInfo, lpPlayInfo2, TransAttackData.Power);

		TransAttackData.dwDamageChkSum = dm_GetDamgeChkSum_S2V(&TransAttackData);

		SENDPACKET(lpPlayInfo2, &TransAttackData);
	}

	return TRUE;
}

// ·¶Î§¹¥»÷ÓÃ»§
int RecvRangeAttack_User(User *lpPlayInfo, TRANS_SKIL_ATTACKDATA *lpTransSkilAttackData, int AreaNum, int PlaySkillCode)
{
	int cnt, cnt2, pow;
	int	rs, time;
	int	dDist;
	int	SkillCode, SkillPoint;
	int SlowSpeed;

	SkillCode = PlaySkillCode & 0xFF;
	SkillPoint = PlaySkillCode >> 8;
	int JobCode = lpPlayInfo->sCharacterData.iClass;

	if (SkillPoint)
	{
		SkillPoint--;
		if (SkillPoint < 0 || SkillPoint >= 10)
			SkillPoint = 0;
	}
	Map *lpStgArea = SERVERMAP->GetMap((EMapID)AreaNum);

	if (!lpStgArea)
		return FALSE;

	if (lpPlayInfo->bCloak && lpPlayInfo->iGameLevel < GAMELEVEL_Four)
		return FALSE;

	if (rsCheckAttackRange(lpTransSkilAttackData->x, lpTransSkilAttackData->y, lpTransSkilAttackData->z, lpPlayInfo) == FALSE)
		return FALSE;

	dDist = lpTransSkilAttackData->AttackSize + 60;
	dDist *= dDist;

	switch (lpTransSkilAttackData->AttackState)
	{
	case 0:
	case 100:
	case 101:
	case 103:
	case 104:
	case 105:
	case 106:
		for (cnt2 = 0; cnt2 < PLAYERS_MAX; cnt2++)
		{
			User * u = USERSDATA + cnt2;

			if (u && u->sCharacterData.iType != CHARACTERTYPE_None)
			{
				for (cnt = 0; cnt < lpTransSkilAttackData->TargetCount; cnt++)
				{
					if (u->iID == lpTransSkilAttackData->dwTarObjectSerial[cnt])
					{
						pow = lpTransSkilAttackData->Power;
						// »ðÊôÐÔÉËº¦
						if (lpTransSkilAttackData->AttackState == 100)
						{
							rs = u->sCharacterData.sElementalDef[sITEMINFO_FIRE];
							if (JobCode == CHARACTERCLASS_Magician)
							{
								if (SkillCode == SKILL_PLAY_METEO || SKILL_PLAY_FLAME_WAVE)
									rs /= 2;
							}
							if (rs)
							{
								if (rs >= 100)
									rs = 100;
								if (rs <= -100)
									rs = -100;
								pow -= ((pow*rs) / 100);
							}
						}
						// À×ÊôÐÔÉËº¦
						if (lpTransSkilAttackData->AttackState == 101)
						{
							rs = u->sCharacterData.sElementalDef[sITEMINFO_BIONIC];
							if (rs)
							{
								if (rs >= 100)
									rs = 100;
								if (rs <= -100)
									rs = -100;
								pow -= ((pow*rs) / 100);
							}
						}
						// À×ÊôÐÔÉËº¦
						if (lpTransSkilAttackData->AttackState == 105)
						{
							rs = u->sCharacterData.sElementalDef[sITEMINFO_LIGHTING];
							if (rs)
							{
								if (rs >= 100)
									rs = 100;
								if (rs <= -100)
									rs = -100;
								pow -= ((pow*rs) / 100);
							}
						}
						// ±ùÊôÐÔÉËº¦
						if (lpTransSkilAttackData->AttackState == 104)
						{
							rs = u->sCharacterData.sElementalDef[sITEMINFO_ICE];
							if (rs)
							{
								if (rs >= 100)
									rs = 100;
								if (rs <= -100)
									rs = -100;
								pow -= ((pow*rs) / 100);
							}
						}
						// ¶¾ÊôÐÔÉËº¦
						if (lpTransSkilAttackData->AttackState == 106)
						{
							rs = u->sCharacterData.sElementalDef[sITEMINFO_POISON];
							if (rs)
							{
								if (rs >= 100)
									rs = 100;
								if (rs <= -100)
									rs = -100;
								pow -= ((pow*rs) / 100);
							}
						}
						// ²»ËÀÏµÉËº¦
						if (lpTransSkilAttackData->AttackState == 103)
						{
							rs = u->sCharacterData.sElementalDef[sITEMINFO_LIGHTING] / 10;
							if (rs)
							{
								if (rs >= 100)
									rs = 100;
								if (rs <= -100)
									rs = -100;
								pow -= ((pow*rs) / 100);
							}
						}
						switch (JobCode)
						{
							// ÎäÊ¿
						case CHARACTERCLASS_Fighter:
							switch (SkillCode)
							{
								//ì«·çÏ®»÷
							case SKILL_PLAY_CYCLONE_STRIKE:
								if ((rand() % 100) < GetCritical2(lpPlayInfo, u, dm_Critical_Temp))
									pow = (pow * 170) / 100;
								if (pow > 0)
									rsSendAttackUser(lpPlayInfo, u, pow / PK_POWER_DIVIDE, 0x80);
								break;
								//»ØÐýÕ¶»÷
							case SKILL_PLAY_M_BLOW:
								if ((rand() % 100) < GetCritical2(lpPlayInfo, u, dm_Critical_Temp))
									pow = (pow * 170) / 100;
								if (pow > 0)
									rsSendAttackUser(lpPlayInfo, u, pow / PK_POWER_DIVIDE, 0x80);
								break;
							}
							break;
							// »úÐµ
						case CHARACTERCLASS_Mechanician:
							switch (SkillCode)
							{
								//»úÐµÁñµ¯
							case SKILL_PLAY_MECHANIC_BOMB:
								if (pow > 0)
									rsSendAttackUser(lpPlayInfo, u, pow / PK_POWER_DIVIDE, 0x80);
								break;
								//»ð»¨µç³¡
							case SKILL_PLAY_SPARK:
								if (pow > 0)
									rsSendAttackUser(lpPlayInfo, u, pow / PK_POWER_DIVIDE, 0x80);
								break;
								//À×öª³å»÷
							case SKILL_PLAY_IMPULSION:
								if (pow > 0)
									rsSendAttackUser(lpPlayInfo, u, pow / PK_POWER_DIVIDE, 0x80);
								break;
							}
							break;
							// ¹­ÊÖ
						case CHARACTERCLASS_Archer:
							switch (SkillCode)
							{
								//¹ß´©Ö®¼ý
							case SKILL_PLAY_PERFORATION:
								if ((rand() % 100) < GetCritical2(lpPlayInfo, u, dm_Critical_Temp))
									pow = (pow * 170) / 100;
								if (pow > 0)
									rsSendAttackUser(lpPlayInfo, u, pow / PK_POWER_DIVIDE, 0x80);
								break;
								//±¬ÁÑÖ®¼ý
							case SKILL_PLAY_BOMB_SHOT:
								if (pow > 0)
									rsSendAttackUser(lpPlayInfo, u, pow / PK_POWER_DIVIDE, 0x80);
								break;
							}
							break;
							// Ç¹±ø
						case CHARACTERCLASS_Pikeman:
							switch (SkillCode)
							{
								//ÎÞÏÞÁ¦Ç¹
							case SKILL_PLAY_EXPANSION:
								if (pow > 0)
									rsSendAttackUser(lpPlayInfo, u, pow / PK_POWER_DIVIDE, 0x80);
								break;
								//ÁéÉß±êÇ¹
							case SKILL_PLAY_VENOM_SPEAR:
								if (pow > 0)
									rsSendAttackUser(lpPlayInfo, u, pow / PK_POWER_DIVIDE, 0x80, -SKILL_PLAY_VENOM_SPEAR, VenomSpear_Time[SkillPoint]);
								break;
							}
							break;
							// Ä§Ç¹
						case CHARACTERCLASS_Atalanta:
							switch (SkillCode)
							{
								//¹âÁÔÖ®Ç¹
							case SKILL_PLAY_LIGHTNING_JAVELIN:
								if (pow > 0)
									rsSendAttackUser(lpPlayInfo, u, pow / PK_POWER_DIVIDE, 0x80);
								break;
							}
							break;
							// ÓÎÏÀ
						case CHARACTERCLASS_Knight:
							switch (SkillCode)
							{
								//Ä§Éñ½£
							case SKILL_PLAY_SWORD_BLAST:
								if (pow > 0)
									rsSendAttackUser(lpPlayInfo, u, pow / PK_POWER_DIVIDE, 0x80);
								break;
								//Ò»ÎíÒø
							case SKILL_PLAY_PIERCING:
								if (pow > 0)
									rsSendAttackUser(lpPlayInfo, u, pow / PK_POWER_DIVIDE, 0x80);
								break;
							}
							break;
							// ·¨Ê¦
						case CHARACTERCLASS_Magician:
							switch (SkillCode)
							{
								//µØÁÑ³å»÷
							case SKILL_PLAY_DIASTROPHISM:
								if (pow > 0)
									rsSendAttackUser(lpPlayInfo, u, pow / PK_POWER_DIVIDE, 0x80);
								break;
							}
							break;
							// ¼ÀË¾
						case CHARACTERCLASS_Priestess:
							switch (SkillCode)
							{
								//ÌìÀ×Ö®Å­
							case SKILL_PLAY_CHAIN_LIGHTNING:
								if (pow > 0)
									rsSendAttackUser(lpPlayInfo, u, pow / PK_POWER_DIVIDE, 0x80);
								break;
							}
							break;
							// ´Ì¿Í
						case CHARACTERCLASS_Assassin:
							switch (SkillCode)
							{
								// ÎÁÒßÖ®ÈÐ
							case SKILL_PLAY_POLLUTE:
								if (pow > 0)
									rsSendAttackUser(lpPlayInfo, u, pow / PK_POWER_DIVIDE, 0x80, -SKILL_PLAY_POLLUTE, Pollute_Time[SkillPoint]);
								break;
								//Ó°×Ó»ðÑæ
							case SKILL_PLAY_SHADOW_BOMB:
								if (pow > 0)
									rsSendAttackUser(lpPlayInfo, u, pow / PK_POWER_DIVIDE, 0x80, -SKILL_PLAY_SHADOW_BOMB, Shadow_Bomb_Time[SkillPoint]);
								break;
							}
							break;
						}
					}
				}
			}
		}
		//¼«µØÅ­ºð
	case 2:
		//ÃÀ¶ÅÉ¯¶Ü
	case 5:
		// Áé»êÕðº³
	case 9:
		for (cnt2 = 0; cnt2 < PLAYERS_MAX; cnt2++)
		{
			User * u = USERSDATA + cnt2;
			if (u && u->sCharacterData.iType != CHARACTERTYPE_None)
			{
				for (cnt = 0; cnt < lpTransSkilAttackData->TargetCount; cnt++)
				{
					if (u->iID == lpTransSkilAttackData->dwTarObjectSerial[cnt])
					{
						rs = u->sCharacterData.sElementalDef[sITEMINFO_BIONIC];
						if (rs < 0)
							rs = 0;
						if (rs >= 100)
							rs = 100;
						rs = 100 - rs;

						switch (lpTransSkilAttackData->AttackState)
						{
						case 2:
							rsSendAttackUser(lpPlayInfo, u, 1, 0x80, -SKILL_PLAY_ROAR, lpTransSkilAttackData->Power*rs / 100);
							break;
						case 5:
							rsSendAttackUser(lpPlayInfo, u, lpTransSkilAttackData->Power / PK_POWER_DIVIDE, 0x80, -SKILL_PLAY_SHIELD_STRIKE, (10 * rs) / 100);
							break;
						case 9:
							rsSendAttackUser(lpPlayInfo, u, 1, 0x80, -SKILL_PLAY_SOUL_SHOCK, lpTransSkilAttackData->Power*rs / 100);
							break;
						}
					}
				}
			}
		}
		break;
		//±ùËªÊÉÔÂ
	case 3:
		switch (JobCode)
		{
		case CHARACTERCLASS_Pikeman:
			switch (SkillCode)
			{
				//´óµØÖ®Ç¹
			case SKILL_PLAY_GROUND_PIKE:
				time = 175;
				SlowSpeed = 0;
				cnt2 = lpTransSkilAttackData->AttackSize >> FLOATNS;
				for (cnt = 0; cnt < 10; cnt++)
				{
					if (G_Pike_Range[cnt] == cnt2)
					{
						time = G_Pike_Time[cnt] * 17;
						break;
					}
				}
				break;
				//µØÏ®ÆæÇ¹
			case SKILL_PLAY_F_SPEAR:
				time = 11 * 17;
				SlowSpeed = 200;
				break;
			}
			break;
			//¹­ÊÖ
		case CHARACTERCLASS_Archer:
			switch (SkillCode)
			{
				//º®±ùÖ®¼ý
			case SKILL_PLAY_C_TRAP:
				time = (SkillPoint + 1) * 2 * 17;
				SlowSpeed = 120;
				break;
			}
			break;
		case CHARACTERCLASS_Priestess:
			switch (SkillCode)
			{
				//±ù·çÊÉÔÂ
			case SKILL_PLAY_GLACIAL_SPIKE:
				time = 8 * 17;
				SlowSpeed = 200;
				break;
				//±©·çÑ©
			case SKILL_PLAY_S_PRMIEL:
				time = (SkillPoint + 1) * 2 * 17;
				SlowSpeed = 200;
				break;
			}
			break;
		}
		for (cnt2 = 0; cnt2 < PLAYERS_MAX; cnt2++)
		{
			User * u = USERSDATA + cnt2;

			if (u && u->sCharacterData.iType != CHARACTERTYPE_None)
			{
				for (cnt = 0; cnt < lpTransSkilAttackData->TargetCount; cnt++)
				{
					if (u->iID == lpTransSkilAttackData->dwTarObjectSerial[cnt])
					{
						pow = lpTransSkilAttackData->Power;
						rs = u->sCharacterData.sElementalDef[sITEMINFO_ICE];
						if (rs)
						{
							if (rs >= 100)
								rs = 100;
							if (rs <= -100)
								rs = -100;
							pow -= ((pow*rs) / 100);
						}
						if (pow > 0)
							rsSendAttackUser(lpPlayInfo, u, pow / PK_POWER_DIVIDE, 0x80, -SkillCode, time);
						break;
					}
				}
			}
		}
		break;
		//¿Õ¼äÅ¤Çú
	case 7:
	case 10:
		if (lpTransSkilAttackData->AttackState == 7)
			time = Distortion_Time[SkillPoint];
		else if (lpTransSkilAttackData->AttackState == 10)
			time = Inertia_Time[SkillPoint];

		for (cnt2 = 0; cnt2 < PLAYERS_MAX; cnt2++)
		{
			User * u = USERSDATA + cnt2;

			if (u && u->sCharacterData.iType != CHARACTERTYPE_None)
			{
				for (cnt = 0; cnt < lpTransSkilAttackData->TargetCount; cnt++)
				{
					if (u->iID == lpTransSkilAttackData->dwTarObjectSerial[cnt])
					{
						rsSendAttackUser(lpPlayInfo, u, 1, 0x80, -SkillCode, time);
						break;
					}
				}
			}
		}
		break;
	}
	return TRUE;
}
//·¶Î§¹¥»÷¹ÖÎï
int RecvRangeAttack(User *lpPlayInfo, TRANS_SKIL_ATTACKDATA *lpTransSkilAttackData, int AreaNum, int PlaySkillCode)
{
	Unit *lpChar;
	int cnt, cnt2, pow;
	int ang, ang2;
	int x, y, z, dist;
	int	rs, time;
	int life, TotalLife;
	int	StunFlag;
	smTRANS_COMMAND	smTransCommand;
	int	dDist;
	int	SkillCode, SkillPoint;
	int	StnPers;
	int	Dmg1, Dmg2, Dmg3, Dmg4;
	int SlowSpeed;

	TRANS_PARTY_SKILL TransPartySkill;

	SkillCode = PlaySkillCode & 0xFF;
	SkillPoint = PlaySkillCode >> 8;

	int JobCode = lpPlayInfo->sCharacterData.iClass;

	if (SkillPoint)
	{
		SkillPoint--;
		if (SkillPoint < 0 || SkillPoint >= 10)
			SkillPoint = 0;
	}

	Map *lpStgArea = SERVERMAP->GetMap((EMapID)AreaNum);

	if (!lpStgArea)
		return FALSE;

	if (lpPlayInfo->bCloak && lpPlayInfo->iGameLevel < GAMELEVEL_Four)
		return FALSE;

	if (rsCheckAttackRange(lpTransSkilAttackData->x, lpTransSkilAttackData->y, lpTransSkilAttackData->z, lpPlayInfo) == FALSE)
		return FALSE;

	dDist = lpTransSkilAttackData->AttackSize + 60;
	dDist *= dDist;

	switch (lpTransSkilAttackData->AttackState)
	{
	case 0:
	case 100:
	case 101:
	case 103:
	case 104:
	case 105:
	case 106:
		for (cnt2 = 0; cnt2 < MAX_ALIVEMONSTERS; cnt2++)
		{
			lpChar = lpStgArea->pcaUnitData[cnt2];
			if (lpChar && lpChar->bActive && lpChar->sCharacterData.iType != CHARACTERTYPE_None && lpChar->psModelAnimation->iType != ANIMATIONTYPE_Die)
			{
				for (cnt = 0; cnt < lpTransSkilAttackData->TargetCount; cnt++)
				{
					if (lpChar->iID == lpTransSkilAttackData->dwTarObjectSerial[cnt])
					{
						if (!lpPlayInfo->pcLastAttack)
							lpPlayInfo->pcLastAttack = lpChar;

						if (lpChar->sCharacterData.iMonsterType == MONSTERTYPE_Friendly && lpChar->iPetID && lpChar->pcOwner == lpPlayInfo)
							continue;
						if (rsCheckAttackRange(lpTransSkilAttackData->x, lpTransSkilAttackData->y, lpTransSkilAttackData->z, lpChar, dDist) == FALSE)
							break;

						pow = lpTransSkilAttackData->Power;
						StunFlag = TRUE;

						Dmg1 = pow;
						// »ðÊôÐÔÉËº¦
						if (lpTransSkilAttackData->AttackState == 100)
						{
							rs = lpChar->sCharacterData.sElementalDef[sITEMINFO_FIRE];
							if (lpPlayInfo->sCharacterData.iClass == CHARACTERCLASS_Magician)
							{
								if (SkillCode == SKILL_PLAY_METEO || SKILL_PLAY_FLAME_WAVE)
									rs /= 2;
							}
							if (rs)
							{
								if (rs >= 100)
									rs = 100;
								if (rs <= -100)
									rs = -100;
								pow -= ((pow*rs) / 100);
							}
						}
						if (lpTransSkilAttackData->AttackState == 101)
						{
							rs = lpChar->sCharacterData.sElementalDef[sITEMINFO_BIONIC];
							if (rs)
							{
								if (rs >= 100)
									rs = 100;
								if (rs <= -100)
									rs = -100;
								pow -= ((pow*rs) / 100);
							}
						}
						if (lpTransSkilAttackData->AttackState == 105)
						{
							rs = lpChar->sCharacterData.sElementalDef[sITEMINFO_LIGHTING];
							if (rs)
							{
								if (rs >= 100)
									rs = 100;
								if (rs <= -100)
									rs = -100;
								pow -= ((pow*rs) / 100);
							}
							StunFlag = FALSE;
						}
						if (lpTransSkilAttackData->AttackState == 104)
						{
							rs = lpChar->sCharacterData.sElementalDef[sITEMINFO_ICE];
							if (rs)
							{
								if (rs >= 100)
									rs = 100;
								if (rs <= -100)
									rs = -100;
								pow -= ((pow*rs) / 100);
							}
						}
						if (lpTransSkilAttackData->AttackState == 106)
						{
							rs = lpChar->sCharacterData.sElementalDef[sITEMINFO_POISON];
							if (rs)
							{
								if (rs >= 100)
									rs = 100;
								if (rs <= -100)
									rs = -100;
								pow -= ((pow*rs) / 100);
							}
						}
						StnPers = rand() % 100;

						Dmg2 = pow;

						if (lpTransSkilAttackData->AttackState == 103)
						{
							if (lpChar->sCharacterData.iMonsterType == MONSTERTYPE_Undead)
								pow += pow / 2;
							rs = lpChar->sCharacterData.sElementalDef[sITEMINFO_LIGHTING] / 10;
							if (rs)
							{
								if (rs >= 100)
									rs = 100;
								if (rs <= -100)
									rs = -100;
								pow -= ((pow*rs) / 100);
							}
						}
						switch (JobCode)
						{
							// ÎäÊ¿
						case CHARACTERCLASS_Fighter:
							switch (SkillCode)
							{
								//ì«·çÏ®»÷
							case SKILL_PLAY_CYCLONE_STRIKE:
								if ((rand() % 100) < GetCritical(lpPlayInfo, lpChar, dm_Critical_Temp))
									pow = (pow * 170) / 100;
								break;
								//»ØÐýÕ¶»÷
							case SKILL_PLAY_M_BLOW:
								if ((rand() % 100) < GetCritical(lpPlayInfo, lpChar, dm_Critical_Temp))
									pow = (pow * 170) / 100;
								break;
							}
							break;
							// »úÐµ
						case CHARACTERCLASS_Mechanician:
							switch (SkillCode)
							{
								//»úÐµÁñµ¯
							case SKILL_PLAY_MECHANIC_BOMB:
								if (lpChar->sCharacterData.iMonsterType == MONSTERTYPE_Mutant || lpChar->sCharacterData.iMonsterType == MONSTERTYPE_Mechanic)
									pow += pow / 2;
								break;
								//»ð»¨µç³¡
							case SKILL_PLAY_SPARK:
								if (lpChar->sCharacterData.iMonsterType == MONSTERTYPE_Mechanic)
									pow += pow / 2;
								break;
								//À×öª³å»÷
							case SKILL_PLAY_IMPULSION:
								if (lpChar->sCharacterData.iMonsterType == MONSTERTYPE_Mechanic)
									pow += (pow * 30) / 100;
								break;
							}
							break;
							// ¹­ÊÖ
						case CHARACTERCLASS_Archer:
							switch (SkillCode)
							{
								//¹ß´©Ö®¼ý
							case SKILL_PLAY_PERFORATION:
								if ((rand() % 100) < GetCritical(lpPlayInfo, lpChar, dm_Critical_Temp))
									pow = (pow * 170) / 100;
								break;
								//±¬ÁÑÖ®¼ý
							case SKILL_PLAY_BOMB_SHOT:
								if (lpChar->sCharacterData.iMonsterType == MONSTERTYPE_Demon)
									pow += (pow*BombShot_DemonDamage[SkillPoint]) / 100;
								break;
							}
							break;
							// Ç¹±ø
						case CHARACTERCLASS_Pikeman:
							switch (SkillCode)
							{
								//ÎÞÏÞÁ¦Ç¹
							case SKILL_PLAY_EXPANSION:
								if (lpChar->sCharacterData.iMonsterType == MONSTERTYPE_Mutant)
									pow += (pow * 30) / 100;
								break;
								//ÁéÉß±êÇ¹
							case SKILL_PLAY_VENOM_SPEAR:
								lpChar->PlayPoison[1] = VenomSpear_Time[SkillPoint] * 17;
								lpChar->PlayPoison[0] = 20;
								break;
							}
							break;
							// Ä§Ç¹
						case CHARACTERCLASS_Atalanta:
							switch (SkillCode)
							{
								//¹âÁÔÖ®Ç¹
							case SKILL_PLAY_LIGHTNING_JAVELIN:
								if (lpChar->sCharacterData.iMonsterType == MONSTERTYPE_Undead)
									pow += pow / 2;
								break;
							}
							break;
							// ÓÎÏÀ
						case CHARACTERCLASS_Knight:
							switch (SkillCode)
							{
								//Ä§Éñ½£
							case SKILL_PLAY_SWORD_BLAST:
								if (lpChar->sCharacterData.iMonsterType == MONSTERTYPE_Normal || lpChar->sCharacterData.iMonsterType == MONSTERTYPE_Mutant)
									pow += (pow * 30) / 100;
								break;
								//Ò»ÎíÒø
							case SKILL_PLAY_PIERCING:
								if (lpChar->sCharacterData.iMonsterType == MONSTERTYPE_Mutant)
									pow += (pow * 30) / 100;
								break;
							}
							break;
							// ·¨Ê¦
						case CHARACTERCLASS_Magician:
							switch (SkillCode)
							{
								//µØÁÑ³å»÷
							case SKILL_PLAY_DIASTROPHISM:
								if (lpChar->sCharacterData.sGlow != MONSTER_CLASS_BOSS)
									StnPers = 0;
								if (lpChar->sCharacterData.iMonsterEffectID == snCHAR_SOUND_DEATHKNIGHT ||
									lpChar->sCharacterData.iMonsterEffectID == snCHAR_SOUND_BABEL ||
									lpChar->sCharacterData.iMonsterEffectID == snCHAR_SOUND_KELVEZU ||
									lpChar->sCharacterData.iMonsterEffectID == snCHAR_SOUND_MOKOVA)
									StnPers = 100;
								break;
							}
							break;
							// ¼ÀË¾
						case CHARACTERCLASS_Priestess:
							switch (SkillCode)
							{
								//ÌìÀ×Ö®Å­
							case SKILL_PLAY_CHAIN_LIGHTNING:
								if (lpChar->sCharacterData.sGlow != MONSTER_CLASS_BOSS &&
									lpChar->sCharacterData.sElementalDef[sITEMINFO_LIGHTING] <= 20)
									StnPers = 0;
								break;
							}
							break;
							// ´Ì¿Í
						case CHARACTERCLASS_Assassin:
							switch (SkillCode)
							{
								// ÎÁÒßÖ®ÈÐ
							case SKILL_PLAY_POLLUTE:
								if (rand() % 100 < Pollute_Ratio[SkillPoint])
								{
									lpChar->PlayPoison[1] = Pollute_Time[SkillPoint] * 17;
									lpChar->PlayPoison[0] = 20;
								}
								break;
								//Ó°×Ó»ðÑæ
							case SKILL_PLAY_SHADOW_BOMB:
								if (rand() % 100 < Shadow_Bomb_Ratio[SkillPoint])
								{
									lpChar->PlayFire[1] = Shadow_Bomb_Time[SkillPoint] * 17;
									lpChar->PlayFire[0] = 30;
								}
								break;
							}
							break;
						}
						lpChar->iStunTimeLeft = 0;

						Dmg3 = pow;

						pow -= (pow * lpChar->sCharacterData.iAbsorbRating) / 100;

						Dmg4 = pow;

						if (pow > 0)
						{
							lpChar->sCharacterData.sHP.sMin -= pow;

							int PowerType = FALSE;
							int Element = 0;

							if (lpChar->psaDamageUsersData || lpChar->psaSiegeWarDataList)
								rsRecordCharDamage(lpPlayInfo, lpChar, pow);

							if (StunFlag && lpChar->sCharacterData.sHP.sMin && StnPers < lpChar->sUnitInfo.DamageStunPers)
							{
								if (lpChar->sCharacterData.sHP.sMin && lpChar->psModelAnimation->iType != ANIMATIONTYPE_Flinch && lpChar->psModelAnimation->iType != ANIMATIONTYPE_Potion)
								{
									ang2 = GetRadian2D(lpChar->pX, lpChar->pZ, lpPlayInfo->sPosition.iX, lpPlayInfo->sPosition.iZ);
									ang = (ang2 + ANGLE_180) & ANGCLIP;
									lpChar->Angle.y = ang;
									lpChar->MoveAngle(10);
									lpChar->Angle.y = ang2;

									if (((lpChar->sCharacterData.sHP.sMax << 2) / 100) < lpTransSkilAttackData->Power || StnPers == 0)
									{
										lpChar->SetMotionFromCode(ANIMATIONTYPE_Flinch);
										PowerType = TRUE;
									}
								}
							}

							switch (lpTransSkilAttackData->AttackState)
							{
								// »ðÊôÐÔ
							case 100:
								Element = sITEMINFO_FIRE;
								break;
							case 101:
							case 103:
							case 105:
								Element = sITEMINFO_LIGHTING;
								break;
							case 104:
								Element = sITEMINFO_ICE;
								break;
							case 106:
								Element = sITEMINFO_POISON;
								break;
							}

							SERVERMAP->OnSendDebugDamageUnit(lpChar, Dmg4, (Element == sITEMINFO_ICE) ? DAMAGEINFO_Ice : DAMAGEINFO_Normal);
						}

						if (lpChar->sCharacterData.sHP.sMin <= 0)
						{
							lpChar->SetMotionFromCode(ANIMATIONTYPE_Die);
							lpChar->pcKillerData = lpPlayInfo;
						}
						break;
					}
				}
			}
		}
		break;
		//Áú¾íÇ¹·ç
	case 1:
		//·ç±©Ö®ÈÐ
	case 203:
	case SKILL_P_DASH:
	case SKILL_R_SMASH:
		for (cnt2 = 0; cnt2 < MAX_ALIVEMONSTERS; cnt2++)
		{
			lpChar = lpStgArea->pcaUnitData[cnt2];
			if (lpChar && lpChar->bActive && lpChar->sCharacterData.iType != CHARACTERTYPE_None && lpChar->psModelAnimation->iType != ANIMATIONTYPE_Die)
			{
				for (cnt = 0; cnt < lpTransSkilAttackData->TargetCount; cnt++)
				{
					if (lpChar->iID == lpTransSkilAttackData->dwTarObjectSerial[cnt])
					{
						if (rsCheckAttackRange(lpTransSkilAttackData->x, lpTransSkilAttackData->y, lpTransSkilAttackData->z, lpChar, dDist) == FALSE)
							break;

						x = (lpPlayInfo->sPosition.iX - lpChar->pX) >> FLOATNS;
						y = (lpPlayInfo->sPosition.iY - lpChar->pY) >> FLOATNS;
						z = (lpPlayInfo->sPosition.iZ - lpChar->pZ) >> FLOATNS;
						if (abs(y) > 100 || (x*x + z * z) > (800 * 800))
							break;

						dist = (int)sqrt((float)(x*x + z * z));
						if (lpTransSkilAttackData->AttackState == SKILL_P_DASH)
							dist = 180 - dist;
						else
							dist = lpTransSkilAttackData->AttackSize - dist;

						int PowerType = FALSE;

						if (lpChar->sCharacterData.iMonsterEffectID != snCHAR_SOUND_DEATHKNIGHT &&
							lpChar->sCharacterData.iMonsterEffectID != snCHAR_SOUND_BABEL &&
							lpChar->sCharacterData.iMonsterEffectID != snCHAR_SOUND_KELVEZU &&
							lpChar->sCharacterData.iMonsterEffectID != snCHAR_SOUND_MOKOVA)
						{
							if (lpChar->sCharacterData.sHP.sMin)
							{
								ang2 = GetRadian2D(lpChar->pX, lpChar->pZ, lpPlayInfo->sPosition.iX, lpPlayInfo->sPosition.iZ);
								ang = (ang2 + ANGLE_180) & ANGCLIP;
								lpChar->Angle.y = ang;
								lpChar->OverLapPosi2 = FALSE;
								lpChar->MoveAngle(dist);
								lpChar->Angle.y = ang2;

								PowerType = TRUE;

								if (lpChar->sCharacterData.sHP.sMin && lpChar->psModelAnimation->iType != ANIMATIONTYPE_Flinch && lpChar->psModelAnimation->iType != ANIMATIONTYPE_Potion)
								{
									if (((lpChar->sCharacterData.sHP.sMax << 2) / 100) < lpTransSkilAttackData->Power)
										lpChar->SetMotionFromCode(ANIMATIONTYPE_Flinch);
								}
								lpChar->pcFocusTarget = 0;
								lpChar->dwNextMotionCode = ANIMATIONTYPE_Idle;
							}
						}
						pow = (lpTransSkilAttackData->Power * lpChar->sCharacterData.iAbsorbRating) / 100;
						pow = lpTransSkilAttackData->Power - pow;

						lpChar->iStunTimeLeft = 0;

						if (pow > 0)
						{
							lpChar->sCharacterData.sHP.sMin -= pow;

							SERVERMAP->OnSendDebugDamageUnit(lpChar, pow, DAMAGEINFO_Normal);
						}

						if (lpChar->sCharacterData.sHP.sMin <= 0)
						{
							lpChar->SetMotionFromCode(ANIMATIONTYPE_Die);
							lpChar->pcKillerData = lpPlayInfo;
						}

						break;
					}
				}
			}
		}
		break;
		//¼«µØÅ­ºð
	case 2:
		//ÃÀ¶ÅÉ¯¶Ü
	case 5:
		//Áé»êÕðº³
	case 9:
		//ÍþÉåÅ­ºð
	case 201:
		//ÁÔÈ¡
	case 202:
		for (cnt2 = 0; cnt2 < MAX_ALIVEMONSTERS; cnt2++)
		{
			lpChar = lpStgArea->pcaUnitData[cnt2];
			if (lpChar && lpChar->bActive && lpChar->sCharacterData.iType != CHARACTERTYPE_None && lpChar->psModelAnimation->iType != ANIMATIONTYPE_Die)
			{
				for (cnt = 0; cnt < lpTransSkilAttackData->TargetCount; cnt++)
				{
					if (lpChar->iID == lpTransSkilAttackData->dwTarObjectSerial[cnt])
					{
						if (rsCheckAttackRange(lpTransSkilAttackData->x, lpTransSkilAttackData->y, lpTransSkilAttackData->z, lpChar, dDist) == FALSE)
							break;
						rs = lpChar->sCharacterData.sElementalDef[sITEMINFO_BIONIC];
						if (rs < 0)
							rs = 0;
						if (rs >= 100)
							rs = 100;
						rs = 100 - rs;

						switch (lpTransSkilAttackData->AttackState)
						{
							//¼«µØÅ­ºð
						case 2:
							//Áé»êÕðº³
						case 9:
							lpChar->iStunTimeLeft = lpTransSkilAttackData->Power << 4;
							lpChar->iStunTimeLeft = (lpChar->iStunTimeLeft * rs) / 100;
							break;
							//ÃÀ¶ÅÉ¯¶Ü
						case 5:
							pow = (lpTransSkilAttackData->Power * lpChar->sCharacterData.iAbsorbRating) / 100;
							pow = lpTransSkilAttackData->Power - pow;
							if (pow > 0)
							{
								lpChar->sCharacterData.sHP.sMin -= pow;
								if (lpChar->psaDamageUsersData || lpChar->psaSiegeWarDataList)
									rsRecordCharDamage(lpPlayInfo, lpChar, pow);
							}
							lpChar->iStunTimeLeft = 16 * 10;
							lpChar->iStunTimeLeft = (lpChar->iStunTimeLeft * rs) / 100;
							break;
							//ÍþÉåÅ­ºð
						case 201:
							if (lpChar->sCharacterData.iMonsterEffectID != snCHAR_SOUND_DEATHKNIGHT && lpChar->sCharacterData.iMonsterEffectID != snCHAR_SOUND_BABEL && lpChar->sCharacterData.iMonsterEffectID != snCHAR_SOUND_KELVEZU && lpChar->sCharacterData.iMonsterEffectID != snCHAR_SOUND_MOKOVA)
							{
								lpChar->pcFocusTarget = 0;
								lpChar->pcAttackTarget = 0;
								lpChar->pcHookedTarget = lpPlayInfo;
								lpChar->dwHookedTargetEndTime = SERVER_GAMETIME + Compulsion_Time[SkillPoint] * 1000;
							}
							break;
							//ÁÔÈ¡
						case 202:
							if (lpChar->sCharacterData.iMonsterEffectID != snCHAR_SOUND_DEATHKNIGHT && lpChar->sCharacterData.iMonsterEffectID != snCHAR_SOUND_BABEL && lpChar->sCharacterData.iMonsterEffectID != snCHAR_SOUND_KELVEZU && lpChar->sCharacterData.iMonsterEffectID != snCHAR_SOUND_MOKOVA)
							{
								lpChar->pcFocusTarget = 0;
								lpChar->pcAttackTarget = 0;
								lpChar->pcHookedTarget = lpPlayInfo;
								lpChar->dwHookedTargetEndTime = SERVER_GAMETIME + Chasing_Hunt_Time[SkillPoint] * 1000;
							}
							break;

						}
						if (lpChar->sCharacterData.sHP.sMin && lpChar->sCharacterData.iMonsterEffectID != snCHAR_SOUND_BABEL && lpChar->sCharacterData.iMonsterEffectID != snCHAR_SOUND_DEATHKNIGHT && lpChar->sCharacterData.iMonsterEffectID != snCHAR_SOUND_KELVEZU && lpChar->sCharacterData.iMonsterEffectID != snCHAR_SOUND_MOKOVA)
						{
							ang2 = GetRadian2D(lpChar->pX, lpChar->pZ, lpPlayInfo->sPosition.iX, lpPlayInfo->sPosition.iZ);
							ang = (ang2 + ANGLE_180) & ANGCLIP;
							lpChar->Angle.y = ang;
							lpChar->MoveAngle(10);
							lpChar->Angle.y = ang2;
							if (lpChar->sCharacterData.sHP.sMin && lpChar->psModelAnimation->iType != ANIMATIONTYPE_Flinch && lpChar->psModelAnimation->iType != ANIMATIONTYPE_Potion)
								lpChar->SetMotionFromCode(ANIMATIONTYPE_Flinch);
						}
						if (lpChar->sCharacterData.sHP.sMin <= 0)
						{
							lpChar->SetMotionFromCode(ANIMATIONTYPE_Die);
							lpChar->pcKillerData = lpPlayInfo;
						}
						break;
					}
				}
			}
		}
		break;
		// ÎüÒý¹ÖÎï
	case 11:
		for (cnt2 = 0; cnt2 < MAX_ALIVEMONSTERS; cnt2++)
		{
			lpChar = lpStgArea->pcaUnitData[cnt2];
			if (lpChar && lpChar->bActive && lpChar->sCharacterData.iType != CHARACTERTYPE_None && lpChar->psModelAnimation->iType != ANIMATIONTYPE_Die)
			{
				for (cnt = 0; cnt < lpTransSkilAttackData->TargetCount; cnt++)
				{
					if (lpChar->iID == lpTransSkilAttackData->dwTarObjectSerial[cnt])
					{
						if (rsCheckAttackRange(lpTransSkilAttackData->x, lpTransSkilAttackData->y, lpTransSkilAttackData->z, lpChar, dDist) == FALSE)
							break;

						x = (lpPlayInfo->sPosition.iX - lpChar->pX) >> FLOATNS;
						y = (lpPlayInfo->sPosition.iY - lpChar->pY) >> FLOATNS;
						z = (lpPlayInfo->sPosition.iZ - lpChar->pZ) >> FLOATNS;
						if (abs(y) > 100 || (x*x + z * z) > (800 * 800))
							break;

						dist = (int)sqrt((float)(x*x + z * z));

						dist = lpTransSkilAttackData->AttackSize + dist;

						int PowerType = FALSE;

						if (lpChar->sCharacterData.iMonsterEffectID != snCHAR_SOUND_DEATHKNIGHT &&
							lpChar->sCharacterData.iMonsterEffectID != snCHAR_SOUND_BABEL &&
							lpChar->sCharacterData.iMonsterEffectID != snCHAR_SOUND_KELVEZU &&
							lpChar->sCharacterData.iMonsterEffectID != snCHAR_SOUND_MOKOVA)
						{
							if (lpChar->sCharacterData.sHP.sMin)
							{
								ang2 = GetRadian2D(lpChar->pX, lpChar->pZ, lpPlayInfo->sPosition.iX, lpPlayInfo->sPosition.iZ);
								ang = (ang2 - ANGLE_180) & ANGCLIP;
								lpChar->Angle.y = ang;
								lpChar->OverLapPosi2 = FALSE;
								lpChar->MoveAngle(dist);
								lpChar->Angle.y = ang2;

								PowerType = TRUE;

								if (lpChar->sCharacterData.sHP.sMin &&
									lpChar->psModelAnimation->iType != ANIMATIONTYPE_Flinch &&
									lpChar->psModelAnimation->iType != ANIMATIONTYPE_Potion)
								{
									if (((lpChar->sCharacterData.sHP.sMax << 2) / 100) < lpTransSkilAttackData->Power)
										lpChar->SetMotionFromCode(ANIMATIONTYPE_Flinch);
								}
								lpChar->pcFocusTarget = 0;
								lpChar->dwNextMotionCode = ANIMATIONTYPE_Idle;
							}
						}
						pow = (lpTransSkilAttackData->Power * lpChar->sCharacterData.iAbsorbRating) / 100;
						pow = lpTransSkilAttackData->Power - pow;

						lpChar->iStunTimeLeft = 0;

						if (pow > 0)
						{
							lpChar->sCharacterData.sHP.sMin -= pow;

							SERVERMAP->OnSendDebugDamageUnit(lpChar, pow, DAMAGEINFO_Normal);
						}

						if (lpChar->sCharacterData.sHP.sMin <= 0)
						{
							lpChar->SetMotionFromCode(ANIMATIONTYPE_Die);
							lpChar->pcKillerData = lpPlayInfo;
						}

						break;
					}
				}
			}
		}
		break;
		//±ùËªÊÉÔÂ
	case 3:
		switch (JobCode)
		{
		case CHARACTERCLASS_Pikeman:
			switch (SkillCode)
			{
				//´óµØÖ®Ç¹
			case SKILL_PLAY_GROUND_PIKE:
				time = 175;
				SlowSpeed = 0;
				cnt2 = lpTransSkilAttackData->AttackSize >> FLOATNS;
				for (cnt = 0; cnt < 10; cnt++)
				{
					if (G_Pike_Range[cnt] == cnt2)
					{
						time = G_Pike_Time[cnt] * 17;
						break;
					}
				}
				break;
				//µØÏ®ÆæÇ¹
			case SKILL_PLAY_F_SPEAR:
				time = 11 * 17;
				SlowSpeed = 200;
				break;
			}
			break;
			//¹­ÊÖ
		case CHARACTERCLASS_Archer:
			switch (SkillCode)
			{
				//º®±ùÖ®¼ý
			case SKILL_PLAY_C_TRAP:
				time = (SkillPoint + 1) * 2 * 17;
				SlowSpeed = 120;
				break;
			}
			break;
		case CHARACTERCLASS_Priestess:
			switch (SkillCode)
			{
				//±ù·çÊÉÔÂ
			case SKILL_PLAY_GLACIAL_SPIKE:
				time = 8 * 17;
				SlowSpeed = 200;
				break;
				//±©·çÑ©
			case SKILL_PLAY_S_PRMIEL:
				time = (SkillPoint + 1) * 2 * 17;
				SlowSpeed = 200;
				break;
			}
			break;
		}
		for (cnt2 = 0; cnt2 < MAX_ALIVEMONSTERS; cnt2++)
		{
			lpChar = lpStgArea->pcaUnitData[cnt2];
			if (lpChar && lpChar->bActive && lpChar->sCharacterData.iType != CHARACTERTYPE_None && lpChar->psModelAnimation->iType != ANIMATIONTYPE_Die)
			{
				for (cnt = 0; cnt < lpTransSkilAttackData->TargetCount; cnt++)
				{
					if (lpChar->iID == lpTransSkilAttackData->dwTarObjectSerial[cnt])
					{
						if (rsCheckAttackRange(lpTransSkilAttackData->x, lpTransSkilAttackData->y, lpTransSkilAttackData->z, lpChar, dDist) == FALSE) break;

						pow = lpTransSkilAttackData->Power;
						Dmg1 = pow;
						rs = lpChar->sCharacterData.sElementalDef[sITEMINFO_ICE];
						if (rs)
						{
							if (rs >= 100)
								rs = 100;
							if (rs <= -100)
								rs = -100;
							pow -= ((pow*rs) / 100);
						}
						Dmg2 = pow;
						pow -= (pow * lpChar->sCharacterData.iAbsorbRating) / 100;
						Dmg3 = pow;

						lpChar->PlaySlowCount = time;
						lpChar->PlaySlowSpeed = SlowSpeed;

						lpChar->iStunTimeLeft = 0;
						lpChar->iDistortion = 0;

						if (rs)
						{
							if (rs < 0)
								rs = 0;

							lpChar->PlaySlowCount -= (rs*time) / 100;

							if (lpChar->PlaySlowCount < 0)
								lpChar->PlaySlowCount = 0;
						}
						if (pow > 0)
						{
							lpChar->sCharacterData.sHP.sMin -= pow;
							if (lpChar->psaDamageUsersData || lpChar->psaSiegeWarDataList)
								rsRecordCharDamage(lpPlayInfo, lpChar, pow);

							if (lpChar->sCharacterData.sHP.sMin)
							{
								ang2 = GetRadian2D(lpChar->pX, lpChar->pZ, lpPlayInfo->sPosition.iX, lpPlayInfo->sPosition.iZ);
								ang = (ang2 + ANGLE_180) & ANGCLIP;
								lpChar->Angle.y = ang;
								lpChar->MoveAngle(10);
								lpChar->Angle.y = ang2;

								if (lpChar->sCharacterData.sHP.sMin && lpChar->psModelAnimation->iType != ANIMATIONTYPE_Flinch && lpChar->psModelAnimation->iType != ANIMATIONTYPE_Potion)
								{
									if (((lpChar->sCharacterData.sHP.sMax << 2) / 100) < lpTransSkilAttackData->Power)
										lpChar->SetMotionFromCode(ANIMATIONTYPE_Flinch);
								}

								SERVERMAP->OnSendDebugDamageUnit(lpChar, pow, DAMAGEINFO_Ice);
							}
						}
						if (lpChar->sCharacterData.sHP.sMin <= 0)
						{
							lpChar->SetMotionFromCode(ANIMATIONTYPE_Die);
							lpChar->pcKillerData = lpPlayInfo;
						}
						break;
					}
				}
			}
		}
		break;
	case 4:
		if (lpTransSkilAttackData->Power < 1 || lpTransSkilAttackData->Power>10)
			break;

		TotalLife = 0;

		for (cnt2 = 0; cnt2 < MAX_ALIVEMONSTERS; cnt2++)
		{
			lpChar = lpStgArea->pcaUnitData[cnt2];
			if (lpChar && lpChar->bActive && lpChar->sCharacterData.iType != CHARACTERTYPE_None && lpChar->psModelAnimation->iType != ANIMATIONTYPE_Die)
			{
				for (cnt = 0; cnt < lpTransSkilAttackData->TargetCount; cnt++)
				{
					if (lpChar->iID == lpTransSkilAttackData->dwTarObjectSerial[cnt] && ((lpChar->sCharacterData.sHP.sMax * 50) / 100) < lpChar->sCharacterData.sHP.sMin && lpChar->sCharacterData.iMonsterType != MONSTERTYPE_Undead)
					{
						if (rsCheckAttackRange(lpTransSkilAttackData->x, lpTransSkilAttackData->y, lpTransSkilAttackData->z, lpChar, dDist) == FALSE) break;

						pow = Soul_Sucker_Absorb[lpTransSkilAttackData->Power - 1];

						rs = lpChar->sCharacterData.sElementalDef[sITEMINFO_BIONIC];
						if (rs)
						{
							if (rs >= 100)
								rs = 100;
							if (rs <= -100)
								rs = -100;
							pow -= ((pow*rs) / 100);
						}
						lpChar->iStunTimeLeft = 0;

						if (pow > 0)
						{
							life = (lpChar->sCharacterData.sHP.sMax * pow) / 100;
							lpChar->sCharacterData.sHP.sMin -= life;

							if (lpChar->psaDamageUsersData || lpChar->psaSiegeWarDataList)
								rsRecordCharDamage(lpPlayInfo, lpChar, life);
							if (lpChar->sCharacterData.sHP.sMin < 0) life += lpChar->sCharacterData.sHP.sMin;

							TotalLife += life;

							if (lpChar->sCharacterData.sHP.sMin && (rand() % 100) < lpChar->sUnitInfo.DamageStunPers)
							{
								ang2 = GetRadian2D(lpChar->pX, lpChar->pZ, lpPlayInfo->sPosition.iX, lpPlayInfo->sPosition.iZ);
								ang = (ang2 + ANGLE_180) & ANGCLIP;
								lpChar->Angle.y = ang;
								lpChar->MoveAngle(10);
								lpChar->Angle.y = ang2;
								if (lpChar->sCharacterData.sHP.sMin && lpChar->psModelAnimation->iType != ANIMATIONTYPE_Flinch && lpChar->psModelAnimation->iType != ANIMATIONTYPE_Potion)
									lpChar->SetMotionFromCode(ANIMATIONTYPE_Flinch);
							}

							SERVERMAP->OnSendDebugDamageUnit(lpChar, life, DAMAGEINFO_Normal);
						}
						if (lpChar->sCharacterData.sHP.sMin <= 0)
						{
							lpChar->SetMotionFromCode(ANIMATIONTYPE_Die);
							lpChar->pcKillerData = lpPlayInfo;
						}
						break;
					}
				}
			}
		}
		if (TotalLife > 0)
		{
			smTransCommand.code = smTRANSCODE_VIRTURAL_POTION;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.WParam = TotalLife;
			smTransCommand.LParam = 0;
			smTransCommand.SParam = 0;
			smTransCommand.EParam = 0;

			SENDPACKET(lpPlayInfo, &smTransCommand);
		}
		break;
		//Ê¥¹âÖ®Öä
	case 6:
		if (lpTransSkilAttackData->Power < 1 || lpTransSkilAttackData->Power>10) break;
		TotalLife = 0;

		ZeroMemory(&TransPartySkill, sizeof(TRANS_PARTY_SKILL));

		for (cnt2 = 0; cnt2 < MAX_ALIVEMONSTERS; cnt2++)
		{
			lpChar = lpStgArea->pcaUnitData[cnt2];
			if (lpChar && lpChar->bActive && lpChar->sCharacterData.iType != CHARACTERTYPE_None && lpChar->psModelAnimation->iType != ANIMATIONTYPE_Die)
			{
				for (cnt = 0; cnt < lpTransSkilAttackData->TargetCount; cnt++)
				{
					if (lpChar->iID == lpTransSkilAttackData->dwTarObjectSerial[cnt] && lpChar->sCharacterData.iMonsterType == MONSTERTYPE_Undead)
					{
						if (rsCheckAttackRange(lpTransSkilAttackData->x, lpTransSkilAttackData->y, lpTransSkilAttackData->z, lpChar, dDist) == FALSE) break;

						pow = Extinction_Percent[lpTransSkilAttackData->Power - 1];
						pow += lpPlayInfo->sCharacterData.iLevel / 5;

						rs = lpChar->sCharacterData.sElementalDef[sITEMINFO_BIONIC];
						if (rs)
						{
							if (rs >= 100)
								rs = 100;
							if (rs <= -100)
								rs = -100;
							pow -= ((pow*rs) / 100);
						}

						lpChar->iStunTimeLeft = 0;

						if ((rand() % 100) < pow)
						{
							if (TransPartySkill.PartyCount < 8)
								TransPartySkill.dwPartyUser[TransPartySkill.PartyCount++] = lpChar->iID;

							life = (lpChar->sCharacterData.sHP.sMin * Extinction_Amount[lpTransSkilAttackData->Power - 1]) / 100;

							lpChar->sCharacterData.sHP.sMin -= life;

							if (lpChar->psaDamageUsersData || lpChar->psaSiegeWarDataList)
								rsRecordCharDamage(lpPlayInfo, lpChar, life);
							if (lpChar->sCharacterData.sHP.sMin < 0)
								life += lpChar->sCharacterData.sHP.sMin;
							TotalLife += life;

							if (lpChar->sCharacterData.sHP.sMin && (rand() % 100) < lpChar->sUnitInfo.DamageStunPers)
							{
								ang2 = GetRadian2D(lpChar->pX, lpChar->pZ, lpPlayInfo->sPosition.iX, lpPlayInfo->sPosition.iZ);
								ang = (ang2 + ANGLE_180) & ANGCLIP;
								lpChar->Angle.y = ang;
								lpChar->MoveAngle(10);
								lpChar->Angle.y = ang2;

								if (lpChar->sCharacterData.sHP.sMin && lpChar->psModelAnimation->iType != ANIMATIONTYPE_Flinch && lpChar->psModelAnimation->iType != ANIMATIONTYPE_Potion)
									lpChar->SetMotionFromCode(ANIMATIONTYPE_Flinch);
							}

							SERVERMAP->OnSendDebugDamageUnit(lpChar, life, DAMAGEINFO_Normal);
						}
						if (lpChar->sCharacterData.sHP.sMin <= 0)
						{
							lpChar->SetMotionFromCode(ANIMATIONTYPE_Die);
							lpChar->pcKillerData = lpPlayInfo;
						}
						break;
					}
				}
			}
		}
		if (TransPartySkill.PartyCount > 0 && lpPlayInfo)
		{
			TransPartySkill.code = smTRANSCODE_PARTY_SKILL;
			TransPartySkill.size = sizeof(TRANS_PARTY_SKILL);
			TransPartySkill.dwSkillCode = SKILL_PLAY_EXTINCTION;
			TransPartySkill.eParam = lpPlayInfo->sCharacterData.iClass;
			rsSendCommandUser2(lpPlayInfo, (smTRANS_COMMAND *)&TransPartySkill);
		}
		break;
		//¿Õ¼äÅ¤Çú
		//×çÖäÀ×»÷
	case 10:
	case 7:
		if (lpTransSkilAttackData->AttackState == 7)
		{
			time = Distortion_Time[SkillPoint] * 17;
			rs = 240 - (240 * Distortion_SpeedSubPercent[SkillPoint]) / 100;
		}
		else if (lpTransSkilAttackData->AttackState == 10)
		{
			time = Inertia_Time[SkillPoint] * 17;
			rs = 240 - (240 * abs(Inertia_Speed[SkillPoint])) / 100;
		}
		for (cnt2 = 0; cnt2 < MAX_ALIVEMONSTERS; cnt2++)
		{
			lpChar = lpStgArea->pcaUnitData[cnt2];
			if (lpChar && lpChar->bActive && lpChar->sCharacterData.iType != CHARACTERTYPE_None && lpChar->psModelAnimation->iType != ANIMATIONTYPE_Die)
			{
				for (cnt = 0; cnt < lpTransSkilAttackData->TargetCount; cnt++)
				{
					if (lpChar->iID == lpTransSkilAttackData->dwTarObjectSerial[cnt])
					{
						if (rsCheckAttackRange(lpTransSkilAttackData->x, lpTransSkilAttackData->y, lpTransSkilAttackData->z, lpChar, dDist) == FALSE)
							break;
						lpChar->PlaySlowCount = time;
						lpChar->PlaySlowSpeed = rs;
						lpChar->iDistortion = time;
						lpChar->iStunTimeLeft = 0;

						if (lpChar->sCharacterData.sHP.sMin)
						{
							ang2 = GetRadian2D(lpChar->pX, lpChar->pZ, lpPlayInfo->sPosition.iX, lpPlayInfo->sPosition.iZ);
							ang = (ang2 + ANGLE_180) & ANGCLIP;
							lpChar->Angle.y = ang;
							lpChar->MoveAngle(10);
							lpChar->Angle.y = ang2;

							if (lpChar->sCharacterData.sHP.sMin && lpChar->psModelAnimation->iType != ANIMATIONTYPE_Flinch && lpChar->psModelAnimation->iType != ANIMATIONTYPE_Potion)
							{
								if (((lpChar->sCharacterData.sHP.sMax << 2) / 100) < lpTransSkilAttackData->Power)
									lpChar->SetMotionFromCode(ANIMATIONTYPE_Flinch);
							}
						}

						if (lpChar->sCharacterData.sHP.sMin <= 0)
						{
							lpChar->SetMotionFromCode(ANIMATIONTYPE_Die);
							lpChar->pcKillerData = lpPlayInfo;
						}
						break;
					}
				}
			}
		}
		break;
	}
	return TRUE;
}

int RecvRangeAttack(User *lpPlayInfo, TRANS_SKIL_ATTACKDATA *lpTransSkilAttackData)
{
	return TRUE;
}


//·¶Î§¹¥»÷ÓÃ»§
int RecvRangeAttackUser(User *lpPlayInfo, TRANS_SKIL_ATTACKDATA *lpTransSkilAttackData)
{
	int cnt, cnt2;
	TRANS_ATTACKDATA	TransAttackData;

	if (SERVERMAP->IsPVPMap(lpPlayInfo->iMapID) == FALSE)
		return FALSE;

	if ((lpTransSkilAttackData->AttackState & 0xFFFF) == 2)
		return FALSE;

	for (cnt2 = 0; cnt2 < PLAYERS_MAX; cnt2++)
	{
		User * u = USERSDATA + cnt2;

		if (u && u->iID)
		{
			for (cnt = 0; cnt < lpTransSkilAttackData->TargetCount; cnt++)
			{
				if (u->iID == lpTransSkilAttackData->dwTarObjectSerial[cnt] && u->sCharacterData.iLevel > LIMIT_PK_LEVEL)
				{
					TransAttackData.code = smTRANSCODE_ATTACKDATA;
					TransAttackData.size = sizeof(TRANS_ATTACKDATA);

					TransAttackData.x = u->sPosition.iX;
					TransAttackData.y = u->sPosition.iY;
					TransAttackData.z = u->sPosition.iZ;

					TransAttackData.AttackState = 1;
					TransAttackData.AttackSize = 32 * fONE;
					TransAttackData.Power = lpTransSkilAttackData->Power;

					TransAttackData.dwDestObjectSerial = lpPlayInfo->iID;
					TransAttackData.dwTarObjectSerial = u->iID;
					TransAttackData.dwChkSum = TransAttackData.Power * 2002 + (TransAttackData.x * TransAttackData.y * TransAttackData.z);

					u->Send_AttackCount++;
					u->Send_AttackDamage += lpTransSkilAttackData->Power;

					SENDPACKET(u, &TransAttackData);

					break;
				}
			}
		}
	}

	return TRUE;
}


//¼ì²â¼¼ÄÜÊÇ·ñÄÜ¹»Ê¹ÓÃ
int rsCheckSkillLevel(User *lpPlayInfo, DWORD dwSkillCode)
{
	DWORD dwCode = dwSkillCode & 0xFF;
	DWORD dwJob = (dwSkillCode >> 4) & 0xF;
	int lv = lpPlayInfo->sCharacterData.iLevel;
	int job = lpPlayInfo->sCharacterData.iClass;

	if ((job == CHARACTERCLASS_Pikeman && dwCode == SKILL_PLAY_PIKEWIND) || (job == CHARACTERCLASS_Magician && dwCode == SKILL_PLAY_ENCHANT_WEAPON))
		return TRUE;

	if (dwJob == 5 && lv < 80)
		return FALSE;
	else if (dwJob == 4 && lv < 60)
		return FALSE;
	else if (dwJob == 3 && lv < 40)
		return FALSE;
	else if (dwJob == 2 && lv < 20)
		return FALSE;
	else if (dwJob == 1 && lv < 10)
		return FALSE;
	return TRUE;
}

//ÉèÖÃ¼¼ÄÜ¹¥»÷
int rsSetSkillAttack(User *lpPlayInfo, Unit *lpChar, TRANS_ATTACKDATA *lpTransAttackData, TRANS_ATTACKDATA2 *lpTransAttackData2)
{
	DWORD	dwSkillCode;
	int		Point;
	int		Param;
	int		pow, pow1, pow2;
	int		power[2];
	int		cnt;
	smTRANS_COMMAND	smTransCommand;

	dwSkillCode = lpTransAttackData2->SkillCode & 0xFF;
	Point = ((lpTransAttackData2->SkillCode >> 8) & 0xF) - 1;
	Param = (lpTransAttackData2->SkillCode >> 12) & 0xF;
	int JobCode = lpPlayInfo->sCharacterData.iClass;

	if (Point < 0 || Point >= 10)
		return FALSE;

	dm_SkillCode_Temp = dwSkillCode;

	if (rsCheckSkillLevel(lpPlayInfo, dwSkillCode) == FALSE)
	{
		if (lpPlayInfo->WarningCount < 5)
		{
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.code = smTRANSCODE_SET_BLACKLIST;
			smTransCommand.WParam = 8850;
			smTransCommand.LParam = lpPlayInfo->sCharacterData.iLevel;
			smTransCommand.SParam = dwSkillCode;
			smTransCommand.EParam = Point;
			rsSendDataServer(lpPlayInfo, &smTransCommand);
			lpPlayInfo->WarningCount++;
		}
		return FALSE;
	}
	switch (dwSkillCode)
	{
		// ÊôÐÔ¹¥»÷Ð§¹û
	case SKILL_PLAY_ELEMENT_ATTACK:
		switch (Point)
		{
		case ELEMENT_FIRE:
			lpTransAttackData->AttackState |= (sITEMINFO_FIRE + 1) << 16;
			break;
		case ELEMENT_ICE:
			lpTransAttackData->AttackState |= (sITEMINFO_ICE + 1) << 16;
			break;
		case ELEMENT_THUNDER:
			lpTransAttackData->AttackState |= (sITEMINFO_LIGHTING + 1) << 16;
			break;
		}
		lpTransAttackData2->Critical[0] = 0;
		lpTransAttackData->Power = 2;
		return TRUE;
		break;
		// ·ï»Ë
	case SKILL_PLAY_PET_ATTACK:
		pow1 = 0;
		pow2 = 0;
		switch (Point)
		{
		case PET_TERRY:
			pow1 = lpPlayInfo->sCharacterData.iLevel / 2;
			pow2 = (lpPlayInfo->sCharacterData.iLevel * 95) / 100;
			lpTransAttackData->AttackState |= (sITEMINFO_FIRE + 1) << 16;
			break;
		case PET_NEPSYS:
			pow1 = lpPlayInfo->sCharacterData.iLevel / 2;
			pow2 = (lpPlayInfo->sCharacterData.iLevel * 95) / 100;
			lpTransAttackData->AttackState |= (sITEMINFO_ICE + 1) << 16;
			break;
		case PET_IO:
			pow1 = (lpPlayInfo->sCharacterData.iLevel * 80) / 100 + 1;
			pow2 = lpPlayInfo->sCharacterData.iLevel + (lpPlayInfo->sCharacterData.iLevel * 80) / 100 + 2;
			break;
		case PET_MUTE:
			pow1 = (lpPlayInfo->sCharacterData.iLevel) / 2;
			pow2 = lpPlayInfo->sCharacterData.iLevel + (lpPlayInfo->sCharacterData.iLevel * 95) / 100;
			break;
		}

		lpTransAttackData->Power = GetRandomPos(pow1, pow2);
		lpTransAttackData2->Critical[0] = 0;
		return TRUE;
		break;
		// ·ï»Ë
	case SKILL_PLAY_PET_ATTACK2:
		if (!lpPlayInfo->dwTime_PrimeItem_PhenixPet || (SERVER_GAMETIME - lpPlayInfo->dwPCBang_Pet_AttackTime) < 1000) return FALSE;

		lpPlayInfo->dwPCBang_Pet_AttackTime = SERVER_GAMETIME;

		pow1 = 0;
		pow2 = 0;

		switch (Point)
		{
		case PCBANG_PET_BURSTP:
		case PCBANG_PET_BURSTS:
		case PCBANG_PET_BURSTL:
		case PCBANG_PET_BURSTD:
			pow1 = lpPlayInfo->sCharacterData.iLevel / 2 + 1;
			pow2 = lpPlayInfo->sCharacterData.iLevel + lpPlayInfo->sCharacterData.iLevel / 2 + 1;
			break;
		}
		lpTransAttackData->Power = GetRandomPos(pow1, pow2);
		lpTransAttackData2->Critical[0] = 0;
		return TRUE;
		break;
	}
	switch (JobCode)
	{
	case CHARACTERCLASS_Fighter:
		switch (dwSkillCode)
		{
			//¾øµØ±©×ß
		case SKILL_PLAY_RAVING:
			lpTransAttackData->Power += (lpTransAttackData->Power*Raving_Damage[Point]) / 100;
			lpTransAttackData->AttackState = (lpTransAttackData->AttackState & 0xFFFF0000) + 2;
			return TRUE;
			//¾«×¼Ö®»÷
		case SKILL_PLAY_IMPACT:
			lpTransAttackData->Power += (lpTransAttackData->Power*Impact_Damage[Point]) / 100;
			lpTransAttackData->AttackState = (lpTransAttackData->AttackState & 0xFFFF0000) + 2;
			return TRUE;
			//ÍþÁ¦³å»÷
		case SKILL_PLAY_TRIPLE_IMPACT:
			lpTransAttackData->Power += (lpTransAttackData->Power*T_Impact_Damage[Point]) / 100;
			if (lpTransAttackData2->MotionCount[0] == 2)
			{
				lpTransAttackData->AttackState = (lpTransAttackData->AttackState & 0xFFFF0000) + 2;
				lpTransAttackData2->Critical[0] = 0;
			}
			return TRUE;
			//ÖÂÃü»ØÐý
		case SKILL_PLAY_BRUTAL_SWING:
			lpTransAttackData->Power += (lpTransAttackData->Power*B_Swing_Damage[Point]) / 100;
			lpTransAttackData2->Critical[0] += (lpTransAttackData2->Critical[0] * B_Swing_Critical[Point]) / 100;
			if (lpChar && lpChar->sCharacterData.iMonsterType == MONSTERTYPE_Demon)
				lpTransAttackData->Power += (lpTransAttackData->Power * 40) / 100;
			return TRUE;
			//Õ½ÉñÖ®Å­
		case SKILL_PLAY_RAGEOF_ZECRAM:
			lpTransAttackData->Power += (lpTransAttackData->Power*R_Zecram_Damage[Point]) / 100;
			lpTransAttackData->AttackState |= (sITEMINFO_FIRE + 1) << 16;
			return TRUE;
			//¸´³ðÁ¬»÷
		case SKILL_PLAY_AVANGING_CRASH:
			lpTransAttackData->Power += (lpTransAttackData->Power*A_Crash_Damage[Point]) / 100;
			if (lpTransAttackData2->Power2[0] > 0 && lpTransAttackData2->Power2[0] <= 10)
				lpTransAttackData2->Critical[0] += B_Swing_Critical[lpTransAttackData2->Power2[0]] / 2;
			return TRUE;
			//´ì¹ÇÑï»Ò
		case SKILL_PLAY_BONE_SMASH:
			lpTransAttackData->Power += (lpTransAttackData->Power*B_Crash_Damage[Point]) / 100;
			if (lpChar && lpChar->sCharacterData.iMonsterType == MONSTERTYPE_Demon)
				lpTransAttackData->Power += (lpTransAttackData->Power*B_Crash_DemonDamage[Point]) / 100;
			return TRUE;
			//ÆÆ»µÖ®»÷
		case SKILL_PLAY_DESTROYER:
			lpTransAttackData->AttackState = (lpTransAttackData->AttackState & 0xFFFF0000) + 2;
			lpTransAttackData->Power += (lpTransAttackData->Power*Destoryer_DamagePercent[Point]) / 100;
			lpTransAttackData2->Critical[0] += Destoryer_AddCritical[Point];
			if (lpChar && lpChar->sCharacterData.iMonsterType == MONSTERTYPE_Demon)
				lpTransAttackData->Power += (lpTransAttackData->Power * 30) / 100;
			return TRUE;
			//¿ñ±©Å­Õ¶
		case SKILL_PLAY_D_HIT:
			lpTransAttackData->AttackState = (lpTransAttackData->AttackState & 0xFFFF0000) + 2;
			lpTransAttackData->Power += (lpTransAttackData->Power*D_Hit_AddDamage[Point]) / 100;
			return TRUE;
			//¿ñÒ°³å»÷
		case SKILL_PLAY_P_DASH:
			lpTransAttackData->AttackState = (lpTransAttackData->AttackState & 0xFFFF0000) + 2;
			lpTransAttackData->Power += (lpTransAttackData->Power*P_Dash_AddDamage[Point]) / 100;
			return TRUE;
		}
		break;
	case CHARACTERCLASS_Mechanician:
		switch (dwSkillCode)
		{
			//·ÀÓùµç²¨
		case SKILL_PLAY_SPARK_SHIELD:
			if (!lpChar || !lpPlayInfo->dwSkill_SparkShield_Time || lpPlayInfo->dwSkill_SparkShield_Time < SERVER_GAMETIME)
			{
				lpPlayInfo->dwSkill_SparkShield_Time = 0;
				return FALSE;
			}
			pow1 = lpPlayInfo->dwSkill_SparkShield_Param >> 16;
			pow2 = lpPlayInfo->dwSkill_SparkShield_Param & 0xFFFF;
			pow = GetRandomPos(pow1, pow2);
			if (lpChar && lpChar->sCharacterData.iMonsterType == MONSTERTYPE_Mechanic)
				pow += (pow * 50) / 100;
			lpTransAttackData->AttackState |= (sITEMINFO_LIGHTING + 1) << 16;
			lpTransAttackData->Power = pow;
			lpTransAttackData2->Critical[0] = 0;
			smTransCommand.code = smTRANSCODE_PROCESS_SKILL;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.WParam = SKILL_PLAY_SPARK_SHIELD;
			smTransCommand.LParam = lpPlayInfo->iID;
			smTransCommand.SParam = lpChar->iID;
			smTransCommand.EParam = CHARACTERCLASS_Mechanician;
			rsSendCommandUser2(lpPlayInfo, &smTransCommand);
			return TRUE;
			//ÐÇ¹âÃð¾ø
		case SKILL_PLAY_GRAND_SMASH:
			lpTransAttackData->Power += (lpTransAttackData->Power*Grand_Smash_Damage[Point]) / 100;
			return TRUE;
			//À×öª³å»÷
		case SKILL_PLAY_IMPULSION:
			lpTransAttackData->Power = Impulsion_LightingDamage[Point];

			if (lpChar && lpChar->sCharacterData.iMonsterType == MONSTERTYPE_Mechanic)
				lpTransAttackData->Power += (lpTransAttackData->Power * 30) / 100;

			lpTransAttackData2->Critical[0] = 0;
			return TRUE;
			//´ÅÐÔÇòÌå
		case SKILL_PLAY_MAGNETIC_SPHERE:
			if (!lpPlayInfo->dwSkill_MagneticSphere_Time || lpPlayInfo->dwSkill_MagneticSphere_Time < SERVER_GAMETIME)
			{
				lpPlayInfo->dwSkill_MagneticSphere_Time = 0;
				return FALSE;
			}
			pow1 = Magnetic_Sphere_AddDamage[lpPlayInfo->dwSkill_MagneticSphere_Param][0];
			pow2 = Magnetic_Sphere_AddDamage[lpPlayInfo->dwSkill_MagneticSphere_Param][1];

			lpTransAttackData->Power = GetRandomPos(pow1, pow2);
			lpTransAttackData2->Critical[0] = 0;
			lpTransAttackData->AttackState |= (sITEMINFO_LIGHTING + 1) << 16;

			if (lpChar && lpChar->sCharacterData.iMonsterType == MONSTERTYPE_Mechanic)
				lpTransAttackData->Power += (lpTransAttackData->Power * 30) / 100;
			return TRUE;
			//¾¿¼«Ö®ÈÐ
		case SKILL_PLAY_R_SMASH:
			lpTransAttackData->Power += (lpTransAttackData->Power * R_Smash_AddDamage[Point]) / 100;
			return TRUE;
		}
		break;
	case CHARACTERCLASS_Archer:
		switch (dwSkillCode)
		{
			//¼²·çÖ®¼ý
		case SKILL_PLAY_WIND_ARROW:
			lpTransAttackData->Power += (lpTransAttackData->Power*Wind_Arrow_Damage[Point]) / 100;
			if (lpChar && lpChar->sCharacterData.iMonsterType == MONSTERTYPE_Normal)
				lpTransAttackData->Power += (lpTransAttackData->Power * 30) / 100;
			return TRUE;
			//¶áÃüÖ®¼ý
		case SKILL_PLAY_PERFECT_AIM:
			lpTransAttackData->Power += Perfect_Aim_Damage[Point];
			lpTransAttackData->Power += lpPlayInfo->sCharacterData.iLevel / Perfect_Aim_Damage_LV[Point];
			if (lpChar && lpChar->sCharacterData.iMonsterType == MONSTERTYPE_Demon)
				lpTransAttackData->Power += (lpTransAttackData->Power * 30) / 100;
			return TRUE;
			//Ñ©±ÀÖ®¼ý
		case SKILL_PLAY_AVALANCHE:
			lpTransAttackData->Power += (lpTransAttackData->Power*Avalanche_Damage[Point]) / 100;
			lpTransAttackData2->Critical[0] >>= 1;
			return TRUE;
			//Áé»êÖ®Ó¥
		case SKILL_PLAY_FALCON:
			if (!lpPlayInfo->dwSKill_Falcon_Time || lpPlayInfo->dwSKill_Falcon_Time < SERVER_GAMETIME)
			{
				lpPlayInfo->dwSKill_Falcon_Time = 0;
				return FALSE;
			}
			lpTransAttackData->Power = GetRandomPos(lpPlayInfo->dwSKill_Falcon_Damage[0], lpPlayInfo->dwSKill_Falcon_Damage[1]);
			lpTransAttackData2->Critical[0] = 0;

			if (lpPlayInfo->dwSkill_ForceOfNature_Time)
			{
				if (lpPlayInfo->dwSkill_ForceOfNature_Time < SERVER_GAMETIME)
					lpPlayInfo->dwSkill_ForceOfNature_Time = 0;
				else
					lpTransAttackData->Power += lpPlayInfo->wSkill_ForceOfNature_Param[1];
			}
			return TRUE;
			//ÔªËØ¹¥»÷
		case SKILL_PLAY_ELEMENTAL_SHOT:
			//»ðÊôÐÔ¹¥»÷
			if (Param == 0)
			{
				lpTransAttackData2->Critical[0] = 0;
				pow = GetRandomPos(Elemental_Shot_Fire[Point][0], Elemental_Shot_Fire[Point][1]);
				lpTransAttackData->Power += pow;
				lpTransAttackData->AttackState |= (sITEMINFO_FIRE + 1) << 16;
				lpTransAttackData->AttackState |= pow << (16 + 4);
			}
			return TRUE;
			//ç³»Ë¾øÑ×
		case SKILL_PLAY_PHOENIX_SHOT:
			lpTransAttackData->Power += (lpTransAttackData->Power*Phoenix_Shot_DamagePercent[Point]) / 100;
			return TRUE;
			//»ØÐýÖ®Îè
		case SKILL_PLAY_E_SHOT:
			lpTransAttackData->Power += (lpTransAttackData->Power*E_Shot_Damge[Point]) / 100;
			lpTransAttackData->AttackState |= (sITEMINFO_BIONIC + 1) << 16;
			return TRUE;
			//Ðþ¹âÖ®Îè
		case SKILL_PLAY_S_ROPE:
			lpTransAttackData->Power += (lpTransAttackData->Power*S_Rope_Damge[Point]) / 100;
			lpTransAttackData->AttackState |= (sITEMINFO_LIGHTING + 1) << 16;
			return TRUE;
		}
		break;
	case CHARACTERCLASS_Pikeman:
		switch (dwSkillCode)
		{
			//ÖÂÃü´ò»÷
		case SKILL_PLAY_CRITICAL_HIT:
			lpTransAttackData2->Critical[0] += Critical_Hit_Critical[Point];
			return TRUE;
			//Åùö¨Ò»»÷
		case SKILL_PLAY_JUMPING_CRASH:
			lpTransAttackData->AttackState = (lpTransAttackData->AttackState & 0xFFFF0000) + 2;
			lpTransAttackData->Power += (lpTransAttackData->Power*Jumping_Crash_Damage[Point]) / 100;
			if (lpChar && lpChar->sCharacterData.iMonsterType == MONSTERTYPE_Demon)
				lpTransAttackData->Power += (lpTransAttackData->Power * 30) / 100;
			return TRUE;
			//Á´ÆïÖ®Ç¹
		case SKILL_PLAY_CHAIN_LANCE:
			lpTransAttackData->Power += (lpTransAttackData->Power*Chain_Lance_Damage[Point]) / 100;
			return TRUE;
			//°µÉ±Ö®ÑÛ
		case SKILL_PLAY_ASSASSIN_EYE:
			lpPlayInfo->dwSkill_AssassinEye_Time = SERVER_GAMETIME + Assassin_Eye_Time[Point] * 1000;
			lpPlayInfo->dwSkill_AssassinEye_Param = Point;

			if (lpChar)
			{
				lpChar->dwAssassinEyeTime = lpPlayInfo->dwSkill_AssassinEye_Time;
				lpChar->AssassinEyeParam = Assassin_Eye_M_SubCritical[Point];
			}
			return FALSE;
			//×ª»»´ò»÷
		case SKILL_PLAY_CHARGING_STRIKE:
			if (!lpTransAttackData2->Power2[0])
				lpTransAttackData->Power += (lpTransAttackData->Power*Charging_Strike_CharingDamagePercent[Point]) / 100;
			else
				lpTransAttackData->Power += (lpTransAttackData->Power*Charging_Strike_DamagePercent[Point]) / 100;
			return TRUE;
			//ÓîÖæ»ÃÓ°
		case SKILL_PLAY_SHADOW_MASTER:
			lpTransAttackData->Power += (lpTransAttackData->Power*Shadow_Master_DamagePercent[Point]) / 100;
			return TRUE;
			//»ØÐý´ò»÷
		case SKILL_PLAY_D_REAPER:
			lpTransAttackData->Power += (lpTransAttackData->Power*D_Reaper_AddDamage[Point]) / 100;
			return TRUE;
			//Ðý·çÖ®Ç¹
		case SKILL_PLAY_SS_ATTACK:
			lpTransAttackData->Power += (lpTransAttackData->Power*SS_Attack_AddDamage[Point]) / 100;
			return TRUE;
		}
		break;
	case CHARACTERCLASS_Atalanta:
		switch (dwSkillCode)
		{
			//º¬É³ÉäÓ°
		case SKILL_PLAY_FARINA:
			return TRUE;
			//¾«ÉñÖ®Ç¹
		case SKILL_PLAY_VIGOR_SPEAR:
			lpTransAttackData->Power += GetRandomPos(V_Spear_Damage[Point][0], V_Spear_Damage[Point][1]);
			lpTransAttackData->Power += lpPlayInfo->sCharacterData.iLevel / 2;
			return TRUE;
			//ÂÝÐý·É±ê
		case SKILL_PLAY_TWIST_JAVELIN:
			lpTransAttackData->Power += (lpTransAttackData->Power*Twist_Javelin_Damage[Point]) / 100;
			if (lpChar && lpChar->sCharacterData.iMonsterType == MONSTERTYPE_Demon)
				lpTransAttackData->Power += (lpTransAttackData->Power * 30) / 100;
			return TRUE;
			//»ðÑæÁÒÇ¹
		case SKILL_PLAY_FIRE_JAVELIN:
			pow = GetRandomPos(Fire_Javelin_Damage[Point][0], Fire_Javelin_Damage[Point][1]);
			if (lpChar && lpChar->sCharacterData.iMonsterType == MONSTERTYPE_Mutant)
				pow += (pow * 50) / 100;
			lpTransAttackData->AttackState |= (sITEMINFO_FIRE + 1) << 16;
			lpTransAttackData->AttackState |= pow << (16 + 4);
			lpTransAttackData->Power += pow;
			lpTransAttackData->Power += lpPlayInfo->sCharacterData.iLevel / 3;
			return TRUE;
			//×··çÖ®Ç¹
		case SKILL_PLAY_SPLIT_JAVELIN:
			if (lpTransAttackData2->Power2[0] > Split_Javelin_AttackNum[Point])
				return FALSE;

			lpTransAttackData->Power = 0;

			for (cnt = 0; cnt < lpTransAttackData2->Power2[0]; cnt++)
			{
				pow = GetRandomPos(lpTransAttackData2->Power[0], lpTransAttackData2->Power[1]);
				pow += (pow*Split_Javelin_Damage[Point]) / 100;
				lpTransAttackData->Power += pow;
			}
			lpTransAttackData2->Critical[0] = 0;
			return TRUE;
			//¿ñ·ç±¬ÁÑ
		case SKILL_PLAY_VENGEANCE:
			lpTransAttackData->Power += (lpTransAttackData->Power*Vengeance_DamagePercent[Point]) / 100;
			return TRUE;
			//ÐÇÓê±êÇ¹
		case SKILL_PLAY_G_COUP:
		{
			int attack = 0;
			for (cnt = 0; cnt < G_Coup_Hit[Point]; cnt++)
				attack += (lpTransAttackData->Power*G_Coup_Damage[Point]) / 100;


			lpTransAttackData->Power = attack;

			lpTransAttackData2->Critical[0] = 0;
			return TRUE;
		}
		//ÁÒÑæÍ»Ï®
		case SKILL_PLAY_S_FEAR:
			lpTransAttackData->Power += (lpTransAttackData->Power*S_Fear_Damage[Point]) / 100;
			lpTransAttackData2->Critical[0] += (lpTransAttackData2->Critical[0] * S_Fear_AddCritical[Point]) / 100;
			return TRUE;
		}
		break;
	case CHARACTERCLASS_Knight:
		switch (dwSkillCode)
		{
			//Ë«ÖØ±¬»÷
		case SKILL_PLAY_DOUBLE_CRASH:
			lpTransAttackData->Power += (lpTransAttackData->Power*D_Crash_Damage[Point]) / 100;
			lpTransAttackData2->Critical[0] += D_Crash_Critical[Point];
			return TRUE;
			//Ê¥ØßÖ®¹â
		case SKILL_PLAY_HOLY_INCANTATION:
			if (lpChar && lpChar->sCharacterData.iMonsterType == MONSTERTYPE_Undead)
			{
				pow = lpChar->sCharacterData.sElementalDef[sITEMINFO_BIONIC];
				if (pow < 0)
					pow = 0;
				if (pow > 100)
					pow = 100;
				pow = 100 - pow;

				pow = (H_Incantation_Success[Point] * pow) / 100;
				if ((rand() % 100) < pow)
				{
					lpChar->pcOwner = lpPlayInfo;
					lpChar->sUnitInfo.dwHashCharacterName = 0;
					lpChar->sCharacterData.bUpdateInfo[0]++;
					lpChar->PlayHolyIncantation[0] = (short)lpChar->sCharacterData.iMonsterType;
					lpChar->PlayHolyIncantation[1] = H_Incantation_Time[Point] * 17;
					lpChar->sCharacterData.sHP.sMin = lpChar->sCharacterData.sHP.sMax = (lpChar->sCharacterData.sHP.sMin * H_Incantation_AddLife[Point]) / 100;
					lpChar->sCharacterData.iOwnerID = lpPlayInfo->iID;
					lpChar->sCharacterData.iMonsterType = MONSTERTYPE_Friendly;
					lstrcpy(lpChar->sCharacterData.Pet.szOwnerName, lpPlayInfo->sCharacterData.szName);
					lpChar->pcAttackTarget = 0;
					lpChar->pcFocusTarget = 0;

					SERVERUNIT->ProcessPacketEffectHolyIncAntation(lpPlayInfo, lpChar->iID, H_Incantation_Time[Point]);
				}
			}
			return FALSE;
			//Ê¥¹âÊ®×Ö
		case SKILL_PLAY_GRAND_CROSS:
			lpTransAttackData->Power += (lpTransAttackData->Power*Grand_Cross_Damage[Point]) / 100;
			if (lpChar && lpChar->sCharacterData.iMonsterType == MONSTERTYPE_Undead)
				lpTransAttackData->Power += (lpTransAttackData->Power*Grand_Cross_UndeadDamage[Point]) / 100;
			return TRUE;
			//É²¾ç»ÄÎè
		case SKILL_PLAY_DIVINE_PIERCING:
			lpTransAttackData->Power += (lpTransAttackData->Power*Divine_Piercing_DamagePercent[Point]) / 100;
			return TRUE;
			//ÉñÁ¦³å´Ì
		case SKILL_PLAY_S_BREAKER:
			lpTransAttackData->Power += (lpTransAttackData->Power*S_Breaker_Damage[Point]) / 100;
			return TRUE;
			//ÉÏµÛÖØ»÷
		case SKILL_PLAY_S_BLADE:
			lpTransAttackData->Power += (lpTransAttackData->Power*S_Blade_Damage[Point]) / 100;
			if (lpChar && lpChar->sCharacterData.iMonsterType == MONSTERTYPE_Undead)
				lpTransAttackData->Power += (lpTransAttackData->Power*S_Blade_UndeadDamage[Point]) / 100;
			return TRUE;
		}
		break;
	case CHARACTERCLASS_Magician:
		switch (dwSkillCode)
		{
			//»ð¼ýÖ®Êõ
		case SKILL_PLAY_FIRE_BOLT:
			power[0] = FireBolt_Damage[Point][0];
			power[1] = FireBolt_Damage[Point][1];
			if (lpPlayInfo->dwSkill_SpiritElemental_Time)
			{
				if (lpPlayInfo->dwSkill_SpiritElemental_Time > SERVER_GAMETIME)
				{
					power[0] += (power[0] * lpPlayInfo->dwSkill_SpiritElemental_Param) / 100;
					power[1] += (power[1] * lpPlayInfo->dwSkill_SpiritElemental_Param) / 100;
				}
				else
				{
					lpPlayInfo->dwSkill_SpiritElemental_Time = 0;
					lpPlayInfo->dwSkill_SpiritElemental_Param = 0;
				}
			}
			if (lpPlayInfo->dwSkill_T_Anima_Time)
			{
				if (lpPlayInfo->dwSkill_T_Anima_Time > SERVER_GAMETIME)
				{
					power[0] += (power[0] * lpPlayInfo->dwSkill_T_Anima_Param) / 100;
					power[1] += (power[1] * lpPlayInfo->dwSkill_T_Anima_Param) / 100;
				}
				else
				{
					lpPlayInfo->dwSkill_T_Anima_Time = 0;
					lpPlayInfo->dwSkill_T_Anima_Param = 0;
				}
			}
			power[0] += lpTransAttackData2->Power2[0] * 4;
			power[1] += lpTransAttackData2->Power2[1] * 4;

			pow = GetRandomPos(power[0], power[1]);
			lpTransAttackData->Power = pow;
			lpTransAttackData->AttackState |= (sITEMINFO_FIRE + 1) << 16;
			lpTransAttackData2->Critical[0] = 0;
			return TRUE;
			//Ú¤ÍöÖ®¹â
		case SKILL_PLAY_DEAD_RAY:
			pow1 = Dead_Ray_Damage[Point][0];
			pow2 = Dead_Ray_Damage[Point][1];
			if (lpPlayInfo->dwSkill_SpiritElemental_Time)
			{
				if (lpPlayInfo->dwSkill_SpiritElemental_Time > SERVER_GAMETIME)
				{
					pow1 += (pow1*lpPlayInfo->dwSkill_SpiritElemental_Param) / 100;
					pow2 += (pow2*lpPlayInfo->dwSkill_SpiritElemental_Param) / 100;
				}
				else
				{
					lpPlayInfo->dwSkill_SpiritElemental_Time = 0;
					lpPlayInfo->dwSkill_SpiritElemental_Param = 0;
				}
			}
			if (lpPlayInfo->dwSkill_T_Anima_Time)
			{
				if (lpPlayInfo->dwSkill_T_Anima_Time > SERVER_GAMETIME)
				{
					pow1 += (pow1*lpPlayInfo->dwSkill_T_Anima_Param) / 100;
					pow2 += (pow2*lpPlayInfo->dwSkill_T_Anima_Param) / 100;
				}
				else
				{
					lpPlayInfo->dwSkill_T_Anima_Time = 0;
					lpPlayInfo->dwSkill_T_Anima_Param = 0;
				}
			}
			pow1 += lpTransAttackData2->Power2[0] * 4;
			pow2 += lpTransAttackData2->Power2[1] * 4;

			pow1 += lpTransAttackData2->Critical[1] / 2;
			pow2 += lpTransAttackData2->Critical[1];

			lpTransAttackData->Power = GetRandomPos(pow1, pow2);

			lpTransAttackData->AttackState |= (sITEMINFO_NONE) << 16;
			lpTransAttackData2->Critical[0] = 0;
			return TRUE;
			//ÔªËØÖ®½£
		case SKILL_PLAY_DANCING_SWORD:
			if (!lpPlayInfo->dwSkill_DancingSword_Time || lpPlayInfo->dwSkill_DancingSword_Time < SERVER_GAMETIME)
			{
				lpPlayInfo->dwSkill_DancingSword_Time = 0;
				lpPlayInfo->dwSkill_DancingSword_Param = 0;
				return FALSE;
			}
			pow1 = lpPlayInfo->dwSkill_DancingSword_Param >> 16;
			if (lpPlayInfo->dwSkill_DancingSword_DelayTime)
			{
				if (lpPlayInfo->dwSkill_DancingSword_DelayTime > (lpTransAttackData2->dwTime + 1000))
					return FALSE;
			}
			lpPlayInfo->dwSkill_DancingSword_DelayTime = lpTransAttackData2->dwTime + Dancing_Sword_AttackDelay[pow1] * 900;

			if (lpTransAttackData2->Power[0] < lpTransAttackData2->Power2[0] || lpTransAttackData2->Power[1] < lpTransAttackData2->Power2[1])
				return FALSE;
			// ±ù½£
			if ((lpPlayInfo->dwSkill_DancingSword_Param & 0xFF) == 0)
			{
				lpTransAttackData->Power = GetRandomPos(Dancing_Sword_IceDamage[pow1][0] + lpTransAttackData2->Power2[0], Dancing_Sword_IceDamage[pow1][1] + lpTransAttackData2->Power2[1]);
				lpTransAttackData2->Critical[0] = 0;
				lpTransAttackData->AttackState |= (sITEMINFO_ICE + 1) << 16;
			}
			// »ð½£
			else
			{
				lpTransAttackData->Power = GetRandomPos(Dancing_Sword_FireDamage[pow1][0] + lpTransAttackData2->Power2[0], Dancing_Sword_FireDamage[pow1][1] + lpTransAttackData2->Power2[1]);
				lpTransAttackData2->Critical[0] = 0;
				lpTransAttackData->AttackState |= (sITEMINFO_FIRE + 1) << 16;
			}
			return TRUE;
			//Á÷ÐÇ»ðÓê
		case SKILL_PLAY_SILRAPHIM:
			pow1 = Silraphim_Damage[Point][0];
			pow2 = Silraphim_Damage[Point][1];

			if (lpPlayInfo->dwSkill_SpiritElemental_Time)
			{
				if (lpPlayInfo->dwSkill_SpiritElemental_Time > SERVER_GAMETIME)
				{
					pow1 += (pow1*lpPlayInfo->dwSkill_SpiritElemental_Param) / 100;
					pow2 += (pow2*lpPlayInfo->dwSkill_SpiritElemental_Param) / 100;
				}
				else
				{
					lpPlayInfo->dwSkill_SpiritElemental_Time = 0;
					lpPlayInfo->dwSkill_SpiritElemental_Param = 0;
				}
			}
			if (lpPlayInfo->dwSkill_T_Anima_Time)
			{
				if (lpPlayInfo->dwSkill_T_Anima_Time > SERVER_GAMETIME)
				{
					pow1 += (pow1*lpPlayInfo->dwSkill_T_Anima_Param) / 100;
					pow2 += (pow2*lpPlayInfo->dwSkill_T_Anima_Param) / 100;
				}
				else
				{
					lpPlayInfo->dwSkill_T_Anima_Time = 0;
					lpPlayInfo->dwSkill_T_Anima_Param = 0;
				}
			}
			pow1 += lpTransAttackData2->Power2[0] * 2;
			pow2 += lpTransAttackData2->Power2[1] * 2;

			pow1 += lpTransAttackData2->Critical[1] / 2;
			pow2 += lpTransAttackData2->Critical[1];

			lpTransAttackData->Power = GetRandomPos(pow1, pow2);

			lpTransAttackData->AttackState |= (sITEMINFO_NONE) << 16;
			lpTransAttackData2->Critical[0] = 0;
			return TRUE;
			//ËõÐ¡Ö®Êõ
		case SKILL_PLAY_V_TENUS:
			lpTransAttackData->AttackState = (sITEMINFO_MOVESPEED << 16) | (V_Tenus_SubSpeed[Point] << 24);
			lpTransAttackData->Power = V_Tenus_Time[Point];
			lpTransAttackData->PowerType = SKILL_PLAY_V_TENUS;
			return TRUE;
		}
		break;
	case CHARACTERCLASS_Priestess:
		switch (dwSkillCode)
		{
			//ÖÎÓúÖ®Êõ
		case SKILL_PLAY_HEALING:
			if (lpPlayInfo->sLimitDamage[0] < lpTransAttackData2->Power2[0] || lpPlayInfo->sLimitDamage[1] < lpTransAttackData2->Power2[1])
				return FALSE;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.code = smTRANSCODE_HEALING;
			smTransCommand.WParam = GetRandomPos(Healing_Heal[Point][0] + lpTransAttackData2->Power2[0], Healing_Heal[Point][1] + lpTransAttackData2->Power2[1]);
			smTransCommand.LParam = 0;
			smTransCommand.SParam = lpTransAttackData2->dwTarObjectSerial;
			smTransCommand.EParam = lpPlayInfo->iID;
			rsPlayHealing(&smTransCommand);
			return FALSE;
			//Ê¥¹âµçÇò
		case SKILL_PLAY_HOLY_BOLT:
			power[0] = HolyBolt_Damage[Point][0];
			power[1] = HolyBolt_Damage[Point][1];
			power[0] += lpTransAttackData2->Power2[0] * 4;
			power[1] += lpTransAttackData2->Power2[1] * 4;

			pow = GetRandomPos(power[0], power[1]);
			if (lpChar && lpChar->sCharacterData.iMonsterType == MONSTERTYPE_Undead)
				pow <<= 1;
			lpTransAttackData->Power = pow;
			lpTransAttackData2->Critical[0] = 0;
			return TRUE;
			//¹âÃ¢ËÄÉä
		case SKILL_PLAY_MULTI_SPARK:
			pow1 = M_Spark_Damage[Point][0] + lpTransAttackData2->Power2[0] * 2;
			pow2 = M_Spark_Damage[Point][1] + lpTransAttackData2->Power2[1] * 2;
			pow = GetRandomPos(pow1, pow2);
			pow *= Param;
			lpTransAttackData->Power = pow;
			lpTransAttackData2->Critical[0] = 0;
			return TRUE;
			//Ê¥½àÖ®¹â
		case SKILL_PLAY_GREAT_HEALING:
		{
			PacketRestoreHP phpr;

			phpr.iLength = sizeof(phpr);
			phpr.iHeader = smTRANSCODE_GRAND_HEALING;
			phpr.hpboost = GetRandomPos(Grand_Healing[Point][0] + lpTransAttackData2->Power2[0] * 2, Grand_Healing[Point][1] + lpTransAttackData2->Power2[1] * 2);;
			phpr.SKILLLVL = Point + 1;
			phpr.pRange = Grand_Healing_Range[Point];
			phpr.IDPlayer = lpPlayInfo->iID;

			PRIESTESSSKILL->RestoreHPPacketParty(lpPlayInfo, &phpr);

			return FALSE;
		}
			
			//»ðÓ°Ë«ÖØ
		case SKILL_PLAY_VIGOR_BALL:
			if (lpTransAttackData2->Power[0] > lpTransAttackData2->Power2[0] && lpTransAttackData2->Power[1] > lpTransAttackData2->Power2[1])
			{
				pow1 = Vigor_Ball_Damage[Point][0] + lpTransAttackData2->Power2[0] * 2 + lpTransAttackData2->Critical[1] * 2;
				pow2 = Vigor_Ball_Damage[Point][1] + lpTransAttackData2->Power2[1] * 2 + lpTransAttackData2->Critical[1] * 2;

				lpTransAttackData->Power = GetRandomPos(pow1, pow2);
				lpTransAttackData2->Critical[0] = 0;
				return TRUE;
			}
			return FALSE;
			//ÉñÊ¥ÌìÊ¹
		case SKILL_PLAY_SUMMON_MUSPELL:
			if (!lpPlayInfo->dwSkill_SummonMuspell_Time || lpPlayInfo->dwSkill_SummonMuspell_Time < SERVER_GAMETIME)
			{
				lpPlayInfo->dwSkill_SummonMuspell_Time = 0;
				return FALSE;
			}
			pow1 = Summon_Muspell_Damage[lpPlayInfo->dwSkill_SummonMuspell_Param][0];
			pow2 = Summon_Muspell_Damage[lpPlayInfo->dwSkill_SummonMuspell_Param][1];

			lpTransAttackData->Power = GetRandomPos(pow1, pow2);
			lpTransAttackData2->Critical[0] = 0;
			return TRUE;
			//ÉñÊ¥µç²¨
		case SKILL_PLAY_S_IMPACT:
			power[0] = S_Impact_Damage[Point][0];
			power[1] = S_Impact_Damage[Point][1];
			power[0] += lpTransAttackData2->Power2[0] * 2;
			power[1] += lpTransAttackData2->Power2[1] * 2;
			power[0] += lpTransAttackData2->Critical[1] / 2;
			power[1] += lpTransAttackData2->Critical[1];

			lpTransAttackData->Power = GetRandomPos(power[0], power[1]);
			lpTransAttackData2->Critical[0] = 0;
			return TRUE;
			// ÉñÖ®±ùÈÐ
		case SKILL_PLAY_P_ICE:
			lpTransAttackData->AttackState |= (sITEMINFO_ICE + 1) << 16;
			power[0] = P_Ice_Damge[Point][0];
			power[1] = P_Ice_Damge[Point][1];
			power[0] += lpTransAttackData2->Power2[0] * 2;
			power[1] += lpTransAttackData2->Power2[1] * 2;
			power[0] += lpTransAttackData2->Critical[1] / 2;
			power[1] += lpTransAttackData2->Critical[1];
			lpTransAttackData->Power = GetRandomPos(power[0], power[1]);
			lpTransAttackData2->Critical[0] = 0;
			dm_SkillCode_Temp |= P_Ice_Frozen[Point] << 8;
			return TRUE;
		}
		break;
		//´Ì¿Í
	case CHARACTERCLASS_Assassin:
		switch (dwSkillCode)
		{
			//´Ì»÷
		case SKILL_PLAY_STRINGER:
			lpTransAttackData->AttackState |= (sITEMINFO_POISON + 1) << 16;
			lpTransAttackData->Power += (lpTransAttackData->Power*Stinger_Damage[Point]) / 100;
			lpTransAttackData->PowerType = SKILL_PLAY_STRINGER;
			return TRUE;
			//ÉÁ»÷
		case SKILL_PLAY_RUNNING_HIT:
			lpTransAttackData->Power += (lpTransAttackData->Power*Running_Hit_Damage[Point]) / 100;
			return TRUE;
			//Èõµã¹¥»÷
		case SKILL_PLAY_WISP:
			lpTransAttackData->AttackSize = Wisp_Range[Point];
			lpTransAttackData->AttackState = (sITEMINFO_SPEED << 16) | (Wisp_Damage[Point] << 24);
			lpTransAttackData->Power = Wisp_Time[Point];
			lpTransAttackData->PowerType = SKILL_PLAY_WISP;
			return TRUE;
			//¶¾ÑÀÁ¬»÷
		case SKILL_PLAY_VENOM_THORN:
			lpTransAttackData->AttackState |= (sITEMINFO_POISON + 1) << 16;
			lpTransAttackData->Power += (lpTransAttackData->Power*Venom_Thorn_Damage[Point]) / 100;
			lpTransAttackData->PowerType = SKILL_PLAY_VENOM_THORN;
			return TRUE;
			//·É½£Ö®Îè
		case SKILL_PLAY_SORE_SWORD:
			lpTransAttackData->Power += (lpTransAttackData->Power*Finishing_Blow_Damage[Point]) / 100;
			return TRUE;
			//ÌøÕ¶
		case SKILL_PLAY_BEAT_UP:
			lpTransAttackData->Power += (lpTransAttackData->Power*Gust_Slash_Damage[Point]) / 100;
			return TRUE;
			//±ù¶³Ö®ÈÐ
		case SKILL_PLAY_FROST_WIND:
			lpTransAttackData->Power += (lpTransAttackData->Power*Frost_Wind_Damage[Point]) / 100;
			return TRUE;
			//Ó°×ÓÉÁ»÷
		case SKILL_PLAY_PASTING_SHADOW:
			lpTransAttackData->Power += (lpTransAttackData->Power*Shadow_Damage[Point]) / 100;
			return TRUE;
			//µØÁÑÕ¶
		case SKILL_PLAY_RISING_SLASH:
			lpTransAttackData->Power += (lpTransAttackData->Power*Rising_Slash_Damage[Point]) / 100;
			return TRUE;
			//ÃÍÁú°ÚÎ²
		case SKILL_PLAY_VIOLENT_STUB:
			lpTransAttackData->Power += (lpTransAttackData->Power*Violent_Stub_Damage[Point]) / 100;
			return TRUE;
		}
		break;
		// ÈøÂú
	case CHARACTERCLASS_Shaman:
		switch (dwSkillCode)
		{
			//°µºÚÉÁµç
		case SKILL_PLAY_DARK_BOLT:
			lpTransAttackData->Power += (lpTransAttackData->Power*Dark_Bolt_Damage[Point]) / 100;
			return TRUE;
			//°µºÚ²¨ÀË
		case SKILL_PLAY_DARK_WAVE:
			lpTransAttackData->Power += (lpTransAttackData->Power*Dark_Wave_Damage[Point]) / 100;
			return TRUE;
			//Áé»ê¼ÏËø
		case SKILL_PLAY_SPIRITUAL_MANACLE:
			lpTransAttackData->AttackState = (sITEMINFO_STUN << 16) | (Spiritual_Manacle_Ratio[Point] << 24);
			lpTransAttackData->Power = Spiritual_Manacle_Time[Point];
			lpTransAttackData->PowerType = SKILL_PLAY_SPIRITUAL_MANACLE;
			return TRUE;
			//×¥ÆÆ
		case SKILL_PLAY_SCRATCH:
			lpTransAttackData->Power += (lpTransAttackData->Power*Scratch_Damage[Point]) / 100;
			return TRUE;
			//ÉóÅÐ
		case SKILL_PLAY_JUDGEMENT:
			lpTransAttackData->Power += (lpTransAttackData->Power*Judgement_Damage[Point]) / 100;
			return TRUE;
		}
		break;
	}
	return FALSE;
}

//ÉèÖÃ¼¼ÄÜ¼ÓÇ¿
int rsSetSkillPlus(User *lpPlayInfo, Unit *lpChar, TRANS_ATTACKDATA *lpTransAttackData, TRANS_ATTACKDATA2 *lpTransAttackData2)
{
	int pow;
	DWORD dwWeaponCode;
	smTRANS_COMMAND	smTransCommand;
	DWORD 	dwSkillCode = lpTransAttackData2->SkillCode & 0xFF;

	DWORD	dwAttSkillCode = 0;

	if (lpPlayInfo->iGameLevel == GAMELEVEL_None)
		dwAttSkillCode = lpTransAttackData2->SkillCode;

	if (lpPlayInfo->dwSkill_Maximize_Time && !dwAttSkillCode)
	{
		if (lpPlayInfo->dwSkill_Maximize_Time < SERVER_GAMETIME)
		{
			lpPlayInfo->dwSkill_Maximize_Time = 0;
			lpPlayInfo->dwSkill_Maximize_Param = 0;
			return TRUE;
		}
		pow = lpTransAttackData2->Power[1] - lpTransAttackData2->Power2[1];
		if (pow >= 0 && pow < lpTransAttackData2->Power[1])
		{
			lpTransAttackData2->Power[1] += (pow * lpPlayInfo->dwSkill_Maximize_Param) / 100;
			lpTransAttackData->Power = GetRandomPos(lpTransAttackData2->Power[0], lpTransAttackData2->Power[1]);
		}
	}
	if (lpPlayInfo->dwSkill_AutoMation_Time && !dwAttSkillCode)
	{
		if (lpPlayInfo->dwSkill_AutoMation_Time < SERVER_GAMETIME)
		{
			lpPlayInfo->dwSkill_AutoMation_Time = 0;
			lpPlayInfo->dwSkill_AutoMation_Param = 0;
			return TRUE;
		}
		dwWeaponCode = lpTransAttackData2->dwWeaponCode&sinITEM_MASK2;
		if (dwWeaponCode == sinWS1 || dwWeaponCode == sinWT1)
		{
			pow = lpTransAttackData2->Power[1] - lpTransAttackData2->Power2[1];
			if (pow >= 0 && pow < lpTransAttackData2->Power[1])
				lpTransAttackData2->Power[1] += (pow * lpPlayInfo->dwSkill_AutoMation_Param) / 100;

			pow = lpTransAttackData2->Power[0] - lpTransAttackData2->Power2[0];
			if (pow >= 0 && pow < lpTransAttackData2->Power[0])
				lpTransAttackData2->Power[0] += (pow * lpPlayInfo->dwSkill_AutoMation_Param) / 100;

			lpTransAttackData->Power = GetRandomPos(lpTransAttackData2->Power[0], lpTransAttackData2->Power[1]);
		}
	}
	if (lpPlayInfo->dwSkill_TriumphOfValhalla_Time && !dwAttSkillCode)
	{
		if (lpPlayInfo->dwSkill_TriumphOfValhalla_Time < SERVER_GAMETIME)
		{
			lpPlayInfo->dwSkill_TriumphOfValhalla_Time = 0;
			lpPlayInfo->dwSkill_TriumphOfValhalla_Param = 0;
			return TRUE;
		}
		pow = GetRandomPos(lpTransAttackData2->Power[0], lpTransAttackData2->Power[1] + (short)lpPlayInfo->dwSkill_TriumphOfValhalla_Param);
		lpTransAttackData->Power = pow;
	}

	if (lpPlayInfo->dwSkill_HallOfValhalla_Time && !dwAttSkillCode)
	{
		if (lpPlayInfo->dwSkill_HallOfValhalla_Time < SERVER_GAMETIME)
		{
			lpPlayInfo->dwSkill_HallOfValhalla_Time = 0;
			return TRUE;
		}
		pow = GetRandomPos(lpTransAttackData2->Power[0], lpTransAttackData2->Power[1] + (short)lpPlayInfo->wSkill_HallOfValhalla_Param[1]);
		lpTransAttackData->Power = pow;
	}

	if (lpPlayInfo->dwVanishEndTime)
	{
		if (lpPlayInfo->dwVanishEndTime < SERVER_GAMETIME)
		{
			lpPlayInfo->dwVanishEndTime = 0;
			lpPlayInfo->saVanishParam[0] = 0;
			lpPlayInfo->saVanishParam[1] = 0;
			return TRUE;
		}
		lpTransAttackData->Power += (lpTransAttackData->Power * (int)lpPlayInfo->saVanishParam[1]) / 100;

		lpPlayInfo->dwVanishEndTime = 0;
		lpPlayInfo->saVanishParam[0] = 0;
		lpPlayInfo->saVanishParam[1] = 0;

		smTransCommand.code = smTRANSCODE_PROCESS_SKILL;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = SKILL_PLAY_VANISH;
		smTransCommand.LParam = 0;
		smTransCommand.SParam = 0;
		smTransCommand.EParam = CHARACTERCLASS_Pikeman;

		SENDPACKET(lpPlayInfo, &smTransCommand);
	}
	if (lpPlayInfo->dwSkill_Blind_Time)
	{
		if (lpPlayInfo->dwSkill_Blind_Time < SERVER_GAMETIME)
		{
			lpPlayInfo->dwSkill_Blind_Time = 0;
			lpPlayInfo->dwSkill_Blind_Param = 0;
			return TRUE;
		}
		lpTransAttackData->Power += lpTransAttackData->Power * Deception_Damage[lpPlayInfo->dwSkill_Blind_Param] / 100;

		lpPlayInfo->dwSkill_Blind_Param = 0;
		lpPlayInfo->dwSkill_Blind_Time = 0;

		smTransCommand.code = smTRANSCODE_PROCESS_SKILL;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = SKILL_PLAY_BLIND;
		smTransCommand.LParam = 0;
		smTransCommand.SParam = 0;
		smTransCommand.EParam = CHARACTERCLASS_Assassin;

		SENDPACKET(lpPlayInfo, &smTransCommand);
	}
	//·è¿ñÅ­ºð
	if (lpPlayInfo->dwSkill_Berserker_Time)
	{
		if (lpPlayInfo->dwSkill_Berserker_Time < SERVER_GAMETIME)
		{
			lpPlayInfo->dwSkill_Berserker_Time = 0;
			lpPlayInfo->dwSkill_Berserker_Param = 0;
			return TRUE;
		}
		lpTransAttackData->Power += Berserker_AddAttack[lpPlayInfo->dwSkill_Berserker_Param];
	}
	//Õ½Éñ×£¸£
	if (lpPlayInfo->dwSkill_P_Enhence_Time)
	{
		if (lpPlayInfo->dwSkill_P_Enhence_Time < SERVER_GAMETIME)
		{
			lpPlayInfo->dwSkill_P_Enhence_Time = 0;
			lpPlayInfo->dwSkill_P_Enhence_Param = 0;
			return TRUE;
		}
		lpTransAttackData->Power += lpTransAttackData->Power * lpPlayInfo->dwSkill_P_Enhence_Param / 100;
	}
	// Ç±ÄÜ¼¤·¢
	if (lpPlayInfo->dwSkill_Amplified_Time)
	{
		if (lpPlayInfo->dwSkill_Amplified_Time < SERVER_GAMETIME)
		{
			lpPlayInfo->dwSkill_Amplified_Time = 0;
			lpPlayInfo->dwSkill_Amplified_Param = 0;
			return TRUE;
		}
		pow = GetRandomPos((lpTransAttackData2->Power[0] + (lpTransAttackData2->Power[0] * (short)Amplified_MinAddDamage[lpPlayInfo->dwSkill_Amplified_Param] / 100)), lpTransAttackData2->Power[1]);
		lpTransAttackData->Power = pow;
	}
	// ×ÔÈ»Ö®¹â
	if (lpPlayInfo->dwSkill_ForceOfNature_Time)
	{
		if (lpPlayInfo->dwSkill_ForceOfNature_Time < SERVER_GAMETIME)
		{
			lpPlayInfo->dwSkill_ForceOfNature_Time = 0;
			return TRUE;
		}
		if (lpPlayInfo->sCharacterData.iClass == CHARACTERCLASS_Archer && dwSkillCode != SKILL_PLAY_FALCON)
			lpTransAttackData->Power += lpPlayInfo->wSkill_ForceOfNature_Param[0];
	}
	// ÉÏµÛ×£¸£
	if (lpPlayInfo->dwSkill_GodsBless_Time)
	{
		if (lpPlayInfo->dwSkill_GodsBless_Time < SERVER_GAMETIME)
		{
			lpPlayInfo->dwSkill_GodsBless_Time = 0;
			lpPlayInfo->dwSkill_GodsBless_Param = 0;
			return TRUE;
		}
		lpTransAttackData->Power += lpPlayInfo->dwSkill_GodsBless_Param;
	}
	if (lpPlayInfo->dwSkill_FrostJavelin_Time && !dwAttSkillCode)
	{
		if (lpPlayInfo->dwSkill_FrostJavelin_Time < SERVER_GAMETIME)
		{
			lpPlayInfo->dwSkill_FrostJavelin_Time = 0;
			lpPlayInfo->dwSkill_FrostJavelin_Param = 0;
			return TRUE;
		}

		dwWeaponCode = lpTransAttackData2->dwWeaponCode&sinITEM_MASK2;
		if (dwWeaponCode == sinWT1)
		{
			pow = GetRandomPos(Frost_Javelin_IceAddDamage[lpPlayInfo->dwSkill_FrostJavelin_Param][0], Frost_Javelin_IceAddDamage[lpPlayInfo->dwSkill_FrostJavelin_Param][1]);

			lpTransAttackData->AttackState |= (sITEMINFO_ICE + 1) << 16;
			lpTransAttackData->AttackState |= pow << (16 + 4);
			lpTransAttackData->Power += pow;
		}
	}
	if (lpPlayInfo->dwBlessSkill_Code == SKILL_PLAY_BLESS_DAMAGE)
	{
		if (lpPlayInfo->dwBlessSkill_Time > SERVER_GAMETIME)
			lpTransAttackData->Power += (lpTransAttackData->Power*lpPlayInfo->dwBlessSkill_Param) / 100;
		else
		{
			lpPlayInfo->dwBlessSkill_Code = 0;
			lpPlayInfo->dwBlessSkill_Time = 0;
			return TRUE;
		}
	}
	if (lpPlayInfo->dwSiegeItem_Scroll_Time)
	{
		if (lpPlayInfo->dwSiegeItem_Scroll_Time < SERVER_GAMETIME)
		{
			lpPlayInfo->dwSiegeItem_Scroll_Code = 0;
			lpPlayInfo->dwSiegeItem_Scroll_Time = 0;
		}
		else
		{
			switch (lpPlayInfo->dwSiegeItem_Scroll_Code)
			{
			case (sinBI1 | sin05):
				lpTransAttackData->Power /= lpPlayInfo->dwSiegeItem_Scroll_Param;
				break;
			case (sinBI1 | sin06):
				lpTransAttackData2->Critical[0] += (short)lpPlayInfo->dwSiegeItem_Scroll_Param;
				break;
			}
			if (lpPlayInfo->iMapID == MAPID_BlessCastle)
			{
				switch (lpPlayInfo->dwSiegeItem_Scroll_Code)
				{
				case (sinBC1 | sin01):
					lpTransAttackData->Power /= lpPlayInfo->dwSiegeItem_Scroll_Param;
					break;
				case (sinBC1 | sin02):
					lpTransAttackData2->Critical[0] += (short)lpPlayInfo->dwSiegeItem_Scroll_Param;
					break;
				}
			}
		}
	}
	return TRUE;
}


//»ñÈ¡¹¥»÷±ØÉ±ÓÐ°µÉ±Ö®ÑÛ
int GetCritical(User *lpPlayInfo, Unit *lpChar, int Critical_Hit)
{
	int Result;

	Result = Critical_Hit + (((lpPlayInfo->sCharacterData.iLevel - lpChar->sCharacterData.iLevel) * 25) / 100);

	if (lpChar->dwAssassinEyeTime && Critical_Hit > 0)
	{
		if (lpChar->dwAssassinEyeTime > SERVER_GAMETIME)
			Result -= lpChar->AssassinEyeParam;
		else
		{
			lpChar->dwAssassinEyeTime = 0;
			lpChar->AssassinEyeParam = 0;
		}
	}
	if (Result > 70)
		Result = 70;

	return Result;
}

//»ñÈ¡¹¥»÷±ØÉ± 
int GetCritical2(User *lpPlayInfo, User *lpPlayInfo2, int Critical_Hit)
{
	int Result;

	Result = Critical_Hit + (((lpPlayInfo->sCharacterData.iLevel - lpPlayInfo2->sCharacterData.iLevel) * 25) / 100);
	if (Result > 70)
		Result = 70;

	return Result;
}

// Ìí¼ÓÁ¦Á¿Ê¯Í·¹¥»÷
int AddForceOrbPower(User *lpPlayInfo, Unit *lpChar, TRANS_ATTACKDATA	*lpTransAttackData, DWORD dwSkillCode, int MinDamage, int MaxDamage)
{
	int damage = 0;
	int	damage2;
	int JobCode;
	int SkillCode;

	if ((lpPlayInfo->dwForceOrb_Code&sinITEM_MASK2) != sinFO1)
		return FALSE;
	if (!lpPlayInfo->iForceOrbTime)
		return FALSE;
	if (lpPlayInfo->iForceOrbTime < SERVER_GAMETIME)
	{
		lpPlayInfo->iForceOrbTime = 0;
		lpPlayInfo->dwForceOrb_Code = 0;
		lpPlayInfo->dwForceOrb_Damage = 0;
		return FALSE;
	}

	JobCode = lpPlayInfo->sCharacterData.iClass;

	SkillCode = dwSkillCode & 0xFF;

	//·ÀÓùµç²¨
	if (JobCode == CHARACTERCLASS_Mechanician && SkillCode == SKILL_PLAY_SPARK_SHIELD)
		return FALSE;
	//Áé»êÖ®Ó¥
	else if (JobCode == CHARACTERCLASS_Archer && SkillCode == SKILL_PLAY_FALCON)
		return FALSE;
	//»Æ½ðÁÔÓ¥
	else if (JobCode == CHARACTERCLASS_Archer && SkillCode == SKILL_PLAY_GOLDEN_FALCON)
		return FALSE;
	//ÎÞÏÞÁ¦Ç¹
	else if (JobCode == CHARACTERCLASS_Pikeman && SkillCode == SKILL_PLAY_EXPANSION)
		return FALSE;
	//Áé»êÍÌÊÉ
	else if (JobCode == CHARACTERCLASS_Atalanta && SkillCode == SKILL_PLAY_SOUL_SUCKER)
		return FALSE;
	//ÔªËØÖ®½£
	else if (JobCode == CHARACTERCLASS_Magician && SkillCode == SKILL_PLAY_DANCING_SWORD)
		return FALSE;
	//ÖëÍøÖ®Êõ
	else if (JobCode == CHARACTERCLASS_Magician && SkillCode == SKILL_PLAY_V_TENUS)
		return FALSE;
	//ÉñÊ¥ÌìÊ¹
	else if (JobCode == CHARACTERCLASS_Priestess && SkillCode == SKILL_PLAY_SUMMON_MUSPELL)
		return FALSE;
	//Èõµã¹¥»÷
	else if (JobCode == CHARACTERCLASS_Assassin && SkillCode == SKILL_PLAY_WISP)
		return FALSE;
	else if (JobCode == CHARACTERCLASS_Shaman && SkillCode == SKILL_PLAY_SPIRITUAL_MANACLE)
		return FALSE;
	//·ÉÁú
	else if (SkillCode == SKILL_PLAY_PET_ATTACK)
		return FALSE;
	//·ï»Ë
	else if (SkillCode == SKILL_PLAY_PET_ATTACK2)
		return FALSE;

	damage = lpPlayInfo->dwForceOrb_Damage;

	damage2 = (MaxDamage + MinDamage) / 2;
	damage += (damage2 * 10) / 100;

	lpTransAttackData->Power += damage;

	if (lpPlayInfo->iGameLevel > GAMELEVEL_Two)
	{
		if (lpChar)
		{
			wsprintf(szDispDamage, ">%s Attack ( ForceOrb + %d ) (%d)", lpChar->sCharacterData.szName, damage, lpTransAttackData->Power);
			rsDisplayDamgeToClient(lpPlayInfo, szDispDamage);
		}
		else
		{
			wsprintf(szDispDamage, "> Attack ( ForceOrb + %d ) (%d)", damage, lpTransAttackData->Power);
			rsDisplayDamgeToClient(lpPlayInfo, szDispDamage);
		}
	}
	return TRUE;
}

// Ôö¼Ó·¶Î§Á¦Á¿Ê¯Í·¹¥»÷
int AddRangeForceOrbPower(User *lpPlayInfo, Unit *lpChar, TRANS_SKIL_ATTACKDATA *lpTransSkillAttackData, DWORD dwSkillCode, int MinDamage, int MaxDamage)
{
	int damage = 0;
	int	damage2;
	int JobCode;
	int SkillCode;

	if ((lpPlayInfo->dwForceOrb_Code&sinITEM_MASK2) != sinFO1)
		return FALSE;
	if (!lpPlayInfo->iForceOrbTime)
		return FALSE;
	if (lpPlayInfo->iForceOrbTime < SERVER_GAMETIME)
	{
		lpPlayInfo->iForceOrbTime = 0;
		lpPlayInfo->dwForceOrb_Code = 0;
		lpPlayInfo->dwForceOrb_Damage = 0;
		return FALSE;
	}
	JobCode = lpPlayInfo->sCharacterData.iClass;
	SkillCode = dwSkillCode & 0xFF;

	//·ÀÓùµç²¨
	if (JobCode == CHARACTERCLASS_Mechanician && SkillCode == SKILL_PLAY_SPARK_SHIELD)
		return FALSE;
	//Áé»êÖ®Ó¥
	else if (JobCode == CHARACTERCLASS_Archer && SkillCode == SKILL_PLAY_FALCON)
		return FALSE;
	//»Æ½ðÁÔÓ¥
	else if (JobCode == CHARACTERCLASS_Archer && SkillCode == SKILL_PLAY_GOLDEN_FALCON)
		return FALSE;
	//ÎÞÏÞÁ¦Ç¹
	else if (JobCode == CHARACTERCLASS_Pikeman && SkillCode == SKILL_PLAY_EXPANSION)
		return FALSE;
	//Áé»êÍÌÊÉ
	else if (JobCode == CHARACTERCLASS_Atalanta && SkillCode == SKILL_PLAY_SOUL_SUCKER)
		return FALSE;
	//ÔªËØÖ®½£
	else if (JobCode == CHARACTERCLASS_Magician && SkillCode == SKILL_PLAY_DANCING_SWORD)
		return FALSE;
	//ÉñÊ¥ÌìÊ¹
	else if (JobCode == CHARACTERCLASS_Priestess && SkillCode == SKILL_PLAY_SUMMON_MUSPELL)
		return FALSE;
	//·ÉÁú
	else if (SkillCode == SKILL_PLAY_PET_ATTACK)
		return FALSE;
	//·ï»Ë
	else if (SkillCode == SKILL_PLAY_PET_ATTACK2)
		return FALSE;

	damage = lpPlayInfo->dwForceOrb_Damage;
	damage2 = (MaxDamage + MinDamage) / 2;
	damage += (damage2 * 10) / 100;

	lpTransSkillAttackData->Power += damage;

	if (lpPlayInfo->iGameLevel > GAMELEVEL_Two)
	{
		if (lpChar)
		{
			wsprintf(szDispDamage, ">%s Attack ( ForceOrb + %d ) (%d)", lpChar->sCharacterData.szName, damage, lpTransSkillAttackData->Power);
			rsDisplayDamgeToClient(lpPlayInfo, szDispDamage);
		}
		else
		{
			wsprintf(szDispDamage, "> Attack ( ForceOrb + %d ) (%d)", damage, lpTransSkillAttackData->Power);
			rsDisplayDamgeToClient(lpPlayInfo, szDispDamage);
		}
	}
	return TRUE;
}

// ·¢ËÍ¹¥»÷Êý¾Ýµ½ÓÃ»§(PVP)
int rsSendAttackDataToUser(User *lpPlayInfo, User *lpPlayInfo2, TRANS_ATTACKDATA *lpTransAttackData)
{
#ifdef _W_SERVER
	int regs, cnt, len;
	int  Param1, Param2;

	if (SERVERMAP->IsPVPMap(lpPlayInfo->iMapID) == FALSE)
		return FALSE;

	if (lpPlayInfo->iGameLevel > GAMELEVEL_Two)
	{
		wsprintf(szDispDamage, ">%s Damaged ( %d -> %d )", lpPlayInfo2->sCharacterData.szName, lpTransAttackData->Power, lpTransAttackData->Power / PK_POWER_DIVIDE);
		rsDisplayDamgeToClient(lpPlayInfo, szDispDamage);
	}

	Param1 = 0;
	Param2 = 0;

	regs = (lpTransAttackData->AttackState >> 16) & 0xF;
	if (regs && regs < sITEMINFO_NONE)
	{
		cnt = lpTransAttackData->AttackState >> (16 + 4);
		if (!cnt)
			cnt = lpTransAttackData->Power;

		len = lpPlayInfo2->sCharacterData.sElementalDef[regs - 1];
		if (len)
		{
			if (len >= 100)
				len = 100;
			if (len <= -100)
				len = -100;

			lpTransAttackData->Power -= ((cnt*len) / 100);
			if (lpTransAttackData->Power < 0)
				lpTransAttackData->Power = 0;
		}
		switch (regs - 1)
		{
		case sITEMINFO_ICE:
			if (lpPlayInfo->dwSkill_EnchantWeapon_Time > SERVER_GAMETIME && (lpPlayInfo->dwSkill_EnchantWeapon_Param >> 8) == 0)
			{
				Param1 = -SKILL_PLAY_ENCHANT_WEAPON;
				Param2 = 230 - 10 * (lpPlayInfo->dwSkill_EnchantWeapon_Param & 0xFF);
				break;
			}
			if (lpPlayInfo->dwSkill_DancingSword_Time > SERVER_GAMETIME && (lpPlayInfo->dwSkill_DancingSword_Param & 0xFF) == 0)
			{
				Param1 = -SKILL_PLAY_DANCING_SWORD;
				Param2 = 230 - 10 * (lpPlayInfo->dwSkill_DancingSword_Param >> 16);
				break;
			}
			if (lpPlayInfo->dwSkill_FrostJavelin_Time > SERVER_GAMETIME)
			{
				Param1 = -SKILL_PLAY_FROST_JAVELIN;
				Param2 = 240 - (240 * Frost_Javelin_SpeedSubPercent[lpPlayInfo->dwSkill_FrostJavelin_Param]) / 100;
				break;
			}
			break;
		case sITEMINFO_POISON:
			Param1 = -lpTransAttackData->PowerType;
			Param2 = 5;
			break;
		}
	}
	if (regs == sITEMINFO_STUN)
	{
		cnt = lpTransAttackData->AttackState >> 24;
		if (cnt > 0)
		{
			len = lpPlayInfo2->sCharacterData.sElementalDef[sITEMINFO_BIONIC];

			if (len < 0)
				len = 0;
			if (len >= 100)
				len = 100;
			len = 100 - len;

			if (rand() % 100 < cnt)
			{
				Param1 = -lpTransAttackData->PowerType;
				Param2 = lpTransAttackData->Power*len / 100;
			}
		}
	}
	if (regs == sITEMINFO_SPEED)
	{
		Param1 = -lpTransAttackData->PowerType;
		Param2 = lpTransAttackData->Power;
	}
	if (regs == sITEMINFO_MOVESPEED)
	{
		Param1 = -lpTransAttackData->PowerType;
		Param2 = lpTransAttackData->Power;
	}
	return rsSendAttackUser(lpPlayInfo, lpPlayInfo2, lpTransAttackData->Power / PK_POWER_DIVIDE, 0x80, Param1, Param2);
#endif
	return TRUE;
}

//µ¥Ìå¹¥»÷Êý¾Ý
int rsRecvAttackData(User *lpPlayInfo, TRANS_ATTACKDATA2 *lpTransAttackData)
{
	TRANS_ATTACKDATA	TransAttackData;
	Unit				*lpChar;
	smTRANS_COMMAND_EX	smTransCommand;
	User *lpPlayInfo2;
	short				sDefAttack[2];
	int					pow;
	DWORD				dwCode;
	int					JobCode;

	if (lpTransAttackData->dwChkSum != dm_GetDamgeChkSum(lpTransAttackData))
	{
		smTransCommand.code = smTRANSCODE_SET_BLACKLIST;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = 8500;
		smTransCommand.LParam = 1;
		smTransCommand.SParam = 0;
		smTransCommand.EParam = 0;
		rsRecordDamageError(lpPlayInfo, (smTRANS_COMMAND *)&smTransCommand);
		return FALSE;
	}
	dwCode = lpTransAttackData->SkillCode & 0xFF;
	JobCode = lpPlayInfo->sCharacterData.iClass;
	if (JobCode == CHARACTERCLASS_Archer && dwCode != SKILL_PLAY_FALCON)
	{
		if (lpTransAttackData->AttackCount <= lpPlayInfo->DamagePacketCount || lpTransAttackData->dwTime <= lpPlayInfo->dwDamagePacketTime)
			return FALSE;

		lpPlayInfo->DamagePacketCount = lpTransAttackData->AttackCount;
		lpPlayInfo->dwDamagePacketTime = lpTransAttackData->dwTime;
	}
	else if (JobCode == CHARACTERCLASS_Mechanician && dwCode != SKILL_PLAY_MAGNETIC_SPHERE)
	{
		if (lpTransAttackData->AttackCount <= lpPlayInfo->DamagePacketCount || lpTransAttackData->dwTime <= lpPlayInfo->dwDamagePacketTime)
			return FALSE;

		lpPlayInfo->DamagePacketCount = lpTransAttackData->AttackCount;
		lpPlayInfo->dwDamagePacketTime = lpTransAttackData->dwTime;
	}
	else if (JobCode == CHARACTERCLASS_Pikeman && dwCode != SKILL_PLAY_CHARGING_STRIKE)
	{
		if (lpTransAttackData->AttackCount <= lpPlayInfo->DamagePacketCount || lpTransAttackData->dwTime <= lpPlayInfo->dwDamagePacketTime)
			return FALSE;

		lpPlayInfo->DamagePacketCount = lpTransAttackData->AttackCount;
		lpPlayInfo->dwDamagePacketTime = lpTransAttackData->dwTime;
	}
	else if (JobCode == CHARACTERCLASS_Pikeman && dwCode != SKILL_PLAY_SHADOW_MASTER)
	{
		if (lpTransAttackData->AttackCount <= lpPlayInfo->DamagePacketCount || lpTransAttackData->dwTime <= lpPlayInfo->dwDamagePacketTime)
			return FALSE;

		lpPlayInfo->DamagePacketCount = lpTransAttackData->AttackCount;
		lpPlayInfo->dwDamagePacketTime = lpTransAttackData->dwTime;
	}
	else if (JobCode == CHARACTERCLASS_Knight && dwCode != SKILL_PLAY_DIVINE_PIERCING)
	{
		if (lpTransAttackData->AttackCount <= lpPlayInfo->DamagePacketCount || lpTransAttackData->dwTime <= lpPlayInfo->dwDamagePacketTime)
			return FALSE;

		lpPlayInfo->DamagePacketCount = lpTransAttackData->AttackCount;
		lpPlayInfo->dwDamagePacketTime = lpTransAttackData->dwTime;
	}

	if (lpTransAttackData->Power[0] > lpPlayInfo->sLimitDamage[0] || lpTransAttackData->Power[1] > lpPlayInfo->sLimitDamage[1] || lpTransAttackData->Critical[0] > lpPlayInfo->sLimitCritical[0])
	{
		smTransCommand.code = smTRANSCODE_SET_BLACKLIST;
		smTransCommand.size = sizeof(smTRANS_COMMAND_EX);
		smTransCommand.WParam = 8510;
		smTransCommand.WxParam = 1;

		smTransCommand.LParam = lpTransAttackData->Power[0];
		smTransCommand.SParam = lpTransAttackData->Power[1];
		smTransCommand.EParam = lpTransAttackData->Critical[0];

		smTransCommand.LxParam = lpPlayInfo->sLimitDamage[0];
		smTransCommand.SxParam = lpPlayInfo->sLimitDamage[1];
		smTransCommand.ExParam = lpPlayInfo->sLimitCritical[0];

		rsRecordDamageError(lpPlayInfo, (smTRANS_COMMAND *)&smTransCommand);

		lpTransAttackData->Power[0] = lpPlayInfo->sLimitDamage[0];
		lpTransAttackData->Power[1] = lpPlayInfo->sLimitDamage[1];
		lpTransAttackData->Critical[0] = lpPlayInfo->sLimitCritical[0];
	}

	TransAttackData.x = lpTransAttackData->x;
	TransAttackData.y = lpTransAttackData->y;
	TransAttackData.z = lpTransAttackData->z;

	TransAttackData.AttackSize = lpTransAttackData->AttackSize;
	TransAttackData.dwTarObjectSerial = lpTransAttackData->dwTarObjectSerial;
	TransAttackData.dwDestObjectSerial = lpTransAttackData->dwDestObjectSerial;

	sDefAttack[0] = lpTransAttackData->Power[0];
	sDefAttack[1] = lpTransAttackData->Power[1];

	TransAttackData.Power = GetRandomPos(sDefAttack[0], sDefAttack[1]);
	TransAttackData.AttackState = lpTransAttackData->AttackState;
	TransAttackData.PowerType = 0;

	dm_SkillCode_Temp = 0;

	lpChar = SERVERUNIT->GetUnit(lpTransAttackData->dwTarObjectSerial,(EMapID)lpTransAttackData->Area[0]);

	if (lpTransAttackData->SkillCode)
	{
		if (rsSetSkillAttack(lpPlayInfo, lpChar, &TransAttackData, lpTransAttackData) == FALSE)
			return FALSE;
	}

	if (rsSetSkillPlus(lpPlayInfo, lpChar, &TransAttackData, lpTransAttackData) == FALSE)
		return FALSE;

	if (!lpTransAttackData->SkillCode)
	{
		if (rsServerConfig.Event_Child)
		{
			if (lpPlayInfo->sCharacterData.iShadowSize > 0x1000 && lpPlayInfo->sCharacterData.iShadowSize <= 0x1002)
				TransAttackData.Power += (TransAttackData.Power * 15) / 100;
		}
	}
	if (lpPlayInfo->dwCurse_Attack_Time)
	{
		if (lpPlayInfo->dwCurse_Attack_Time > SERVER_GAMETIME)
			TransAttackData.Power -= (TransAttackData.Power*lpPlayInfo->dwCurse_Attack_Param) / 100;
		else
			lpPlayInfo->dwCurse_Attack_Time = 0;
	}
	if (lpPlayInfo->dwTime_PrimeItem_HelpPet > (DWORD)SERVER_LOCATIME && lpPlayInfo->sCharacterData.GravityScroolCheck[1] == 2)
		TransAttackData.Power += (TransAttackData.Power * 10) / 100;

	// PVEÄ£Ê½
	if (lpChar)
	{
		// Ìí¼ÓÁ¦Á¿Ê¯Í·µÄÉËº¦
		AddForceOrbPower(lpPlayInfo, lpChar, &TransAttackData, lpTransAttackData->SkillCode, sDefAttack[0], sDefAttack[1]);

		if (lpTransAttackData->Critical[0])
		{
			if ((rand() % 100) < GetCritical(lpPlayInfo, lpChar, lpTransAttackData->Critical[0]))
			{
				TransAttackData.AttackState = (TransAttackData.AttackState & 0xFFFF0000) + 2;
				pow = TransAttackData.Power;
				TransAttackData.Power = (pow * 170) / 100;						//±ØÉ±¹¥»÷Ôö

				//±ØÉ±Ö®ÑÛ
				if (lpPlayInfo->dwSkill_AssassinEye_Time)
				{
					if (lpPlayInfo->dwSkill_AssassinEye_Time > SERVER_GAMETIME)
						TransAttackData.Power = (pow*(170 + Assassin_Eye_AddCritical[lpPlayInfo->dwSkill_AssassinEye_Param])) / 100;
					else
					{
						lpPlayInfo->dwSkill_AssassinEye_Time = 0;
						lpPlayInfo->dwSkill_AssassinEye_Param = 0;
					}
				}
				//ÖÚÉñÖ®Å­
				if (lpPlayInfo->dwSkill_B_Berserker_Time)
				{
					if (lpPlayInfo->dwSkill_B_Berserker_Time > SERVER_GAMETIME)
						TransAttackData.Power = (pow*(170 + B_Berserker_AddDamage[lpPlayInfo->dwSkill_AssassinEye_Param])) / 100;	//¹¥»÷±ØÉ±
					else
					{
						lpPlayInfo->dwSkill_B_Berserker_Time = 0;
						lpPlayInfo->dwSkill_B_Berserker_Param = 0;
					}
				}

				smTransCommand.code = smTRANSCODE_ATTACK_RESULT;
				smTransCommand.size = sizeof(smTRANS_COMMAND);
				smTransCommand.WParam = 1;
				smTransCommand.LParam = 0;
				smTransCommand.SParam = 0;
				smTransCommand.EParam = 0;

				SENDPACKET(lpPlayInfo, &smTransCommand);
			}
		}
		rsRecvAttackData_Old(lpPlayInfo, &TransAttackData, lpChar, TRUE);

		if (lpChar->dwIgnoreOthersTime == 0 && (lpChar->sCharacterData.iMonsterEffectID == snCHAR_SOUND_DEATHKNIGHT || lpChar->sCharacterData.iMonsterEffectID == snCHAR_SOUND_BABEL || lpChar->sCharacterData.iMonsterEffectID == snCHAR_SOUND_CASTLE_CRYSTAL_R || lpChar->sCharacterData.iMonsterEffectID == snCHAR_SOUND_CASTLE_CRYSTAL_G || lpChar->sCharacterData.iMonsterEffectID == snCHAR_SOUND_CASTLE_CRYSTAL_B))
		{
			int dist, x, y, z;

			x = (lpPlayInfo->sPosition.iX - lpChar->pX) >> FLOATNS;
			y = (lpPlayInfo->sPosition.iY - lpChar->pY) >> FLOATNS;
			z = (lpPlayInfo->sPosition.iZ - lpChar->pZ) >> FLOATNS;
			dist = x * x + y * y + z * z;

			if (dist <= (lpChar->sCharacterData.iAttackRange * lpChar->sCharacterData.iAttackRange))
			{
				lpChar->pcFocusTarget = lpPlayInfo;
				lpChar->dwIgnoreOthersTime = SERVER_GAMETIME + 4000;
			}
		}
	}
	//PVPÄ£Ê½
	else
	{
		lpPlayInfo2 = SERVERUSER->GetUser(lpTransAttackData->dwTarObjectSerial);
		if (lpPlayInfo2)
		{
			AddForceOrbPower(lpPlayInfo, 0, &TransAttackData, lpTransAttackData->SkillCode, sDefAttack[0], sDefAttack[1]);

			if (lpTransAttackData->Critical[0])
			{
				if ((rand() % 100) < GetCritical2(lpPlayInfo, lpPlayInfo2, lpTransAttackData->Critical[0]))
				{
					TransAttackData.AttackState = (TransAttackData.AttackState & 0xFFFF0000) + 2;
					pow = TransAttackData.Power;
					TransAttackData.Power = (pow * 170) / 100;

					//°µÉ±Ö®ÑÛ
					if (lpPlayInfo->dwSkill_AssassinEye_Time)
					{
						if (lpPlayInfo->dwSkill_AssassinEye_Time > SERVER_GAMETIME)
							TransAttackData.Power = (pow*(170 + Assassin_Eye_AddCritical[lpPlayInfo->dwSkill_AssassinEye_Param])) / 100;	//¹¥»÷±ØÉ±
						else
						{
							lpPlayInfo->dwSkill_AssassinEye_Time = 0;
							lpPlayInfo->dwSkill_AssassinEye_Param = 0;
						}
					}
					//ÖÚÉñÖ®Å­
					if (lpPlayInfo->dwSkill_B_Berserker_Time)
					{
						if (lpPlayInfo->dwSkill_B_Berserker_Time > SERVER_GAMETIME)
							TransAttackData.Power = (pow*(170 + B_Berserker_AddDamage[lpPlayInfo->dwSkill_AssassinEye_Param])) / 100;	//¹¥»÷±ØÉ±
						else
						{
							lpPlayInfo->dwSkill_B_Berserker_Time = 0;
							lpPlayInfo->dwSkill_B_Berserker_Param = 0;
						}
					}

					smTransCommand.code = smTRANSCODE_ATTACK_RESULT;
					smTransCommand.size = sizeof(smTRANS_COMMAND);
					smTransCommand.WParam = 1;
					smTransCommand.LParam = 0;
					smTransCommand.SParam = 0;
					smTransCommand.EParam = 0;

					SENDPACKET(lpPlayInfo, &smTransCommand);
				}
			}
			rsSendAttackDataToUser(lpPlayInfo, lpPlayInfo2, &TransAttackData);
		}
	}
	if (lpPlayInfo->iGameLevel != GAMELEVEL_None)
	{
		smTransCommand.code = smTRANSCODE_DISP_DAMAGE;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = TransAttackData.Power;
		smTransCommand.LParam = 0;
		smTransCommand.SParam = 0;
		smTransCommand.EParam = 0;

		SENDPACKET(lpPlayInfo, &smTransCommand);
	}

	return TRUE;
}


// ÉèÖÃ·¶Î§¹¥»÷
int rsSetSkillRangeAttack(User *lpPlayInfo, Unit *lpChar, TRANS_ATTACKDATA *lpTransAttackData, TRANS_SKIL_ATTACKDATA *lpTransSkillAttackData, TRANS_SKIL_ATTACKDATA2 *lpTransRangeAttack)
{
	DWORD	dwSkillCode;
	int		Point;
	int		Param;
	int		pow, pow1, pow2;
	int		cnt;
	smTRANS_COMMAND	smTransCommand;

	dwSkillCode = lpTransRangeAttack->SkillCode & 0xFF;
	Point = ((lpTransRangeAttack->SkillCode >> 8) & 0xF) - 1;
	Param = (lpTransRangeAttack->SkillCode >> 12) & 0xF;
	int JobCode = lpPlayInfo->sCharacterData.iClass;

	if (Point < 0 || Point >= 10)
		return FALSE;

	dm_SkillCode_Temp = dwSkillCode;

	if (lpPlayInfo->dwVanishEndTime)
	{
		if (lpPlayInfo->dwVanishEndTime < SERVER_GAMETIME)
		{
			lpPlayInfo->dwVanishEndTime = 0;
			lpPlayInfo->saVanishParam[0] = 0;
			lpPlayInfo->saVanishParam[1] = 0;
			return TRUE;
		}

		lpPlayInfo->dwVanishEndTime = 0;
		lpPlayInfo->saVanishParam[0] = 0;
		lpPlayInfo->saVanishParam[1] = 0;

		smTransCommand.code = smTRANSCODE_PROCESS_SKILL;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = SKILL_PLAY_VANISH;
		smTransCommand.LParam = 0;
		smTransCommand.SParam = 0;
		smTransCommand.EParam = CHARACTERCLASS_Pikeman;

		SENDPACKET(lpPlayInfo, &smTransCommand);
	}

	if (lpPlayInfo->dwSkill_Blind_Time)
	{
		if (lpPlayInfo->dwSkill_Blind_Time < SERVER_GAMETIME)
		{
			lpPlayInfo->dwSkill_Blind_Time = 0;
			lpPlayInfo->dwSkill_Blind_Param = 0;
			return TRUE;
		}

		lpPlayInfo->dwSkill_Blind_Param = 0;
		lpPlayInfo->dwSkill_Blind_Time = 0;

		smTransCommand.code = smTRANSCODE_PROCESS_SKILL;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = SKILL_PLAY_BLIND;
		smTransCommand.LParam = 0;
		smTransCommand.SParam = 0;
		smTransCommand.EParam = CHARACTERCLASS_Assassin;

		SENDPACKET(lpPlayInfo, &smTransCommand);
	}

	if (rsCheckSkillLevel(lpPlayInfo, dwSkillCode) == FALSE)
	{
		if (lpPlayInfo->WarningCount < 5)
		{
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.code = smTRANSCODE_SET_BLACKLIST;
			smTransCommand.WParam = 8850;
			smTransCommand.LParam = lpPlayInfo->sCharacterData.iLevel;
			smTransCommand.SParam = dwSkillCode;
			smTransCommand.EParam = Point;
			rsSendDataServer(lpPlayInfo, &smTransCommand);
			lpPlayInfo->WarningCount++;
		}
		return FALSE;
	}
	switch (dwSkillCode)
	{
	case SKILL_PLAY_MOURNING_PRAY2:
		lpTransSkillAttackData->AttackSize = Mourning_Pray_Area[Point];
		pow = GetRandomPos(lpTransRangeAttack->Power[0], lpTransRangeAttack->Power[1]);
		pow += (pow * Mourning_Pray_Damage[Point]) / 100;
		lpTransSkillAttackData->Power = pow;
		lpTransSkillAttackData->AttackState = 0;
		return TRUE;
	}
	switch (JobCode)
	{
	case CHARACTERCLASS_Fighter:
		switch (dwSkillCode)
		{
			//¼«µØÅ­ºð
		case SKILL_PLAY_ROAR:
			lpTransSkillAttackData->AttackSize = Roar_Range[Point];
			lpTransSkillAttackData->Power = Roar_Time[Point];
			lpTransSkillAttackData->AttackState = 2;
			return TRUE;
			//Õ½ÉñÖ®Å­
		case SKILL_PLAY_RAGEOF_ZECRAM:
			lpTransSkillAttackData->AttackSize = R_Zecram_Area[Point];
			pow = GetRandomPos(lpTransRangeAttack->Power[0], lpTransRangeAttack->Power[1]);
			pow += (pow*R_Zecram_Damage[Point]) / 100;
			pow >>= 1;
			lpTransSkillAttackData->Power = pow;
			lpTransSkillAttackData->AttackState = 100;
			lpTransAttackData->AttackState |= (sITEMINFO_FIRE + 1) << 16; // »ðÊôÐÔ
			return TRUE;
			//ì«·çÏ®»÷
		case SKILL_PLAY_CYCLONE_STRIKE:
			if (lpTransSkillAttackData->TargetCount > Cyclone_Strike_AttackNum[Point] + 1)
				return FALSE;
			lpTransAttackData->Power = GetRandomPos(lpTransRangeAttack->Power[0], lpTransRangeAttack->Power[1]);
			lpTransAttackData->Power += (lpTransAttackData->Power*Cyclone_Strike_DamagePercent[Point]) / 100;
			lpTransSkillAttackData->AttackSize = Cyclone_Strike_Area[Point];
			lpTransSkillAttackData->Power = lpTransAttackData->Power;
			lpTransSkillAttackData->AttackState = 0;
			dm_Critical_Temp = lpTransRangeAttack->Critical[0];
			return TRUE;
			//¿ñÒ°³å»÷
		case SKILL_PLAY_P_DASH:
			lpTransSkillAttackData->AttackSize = P_Dash_Area[Point];
			pow = GetRandomPos(lpTransRangeAttack->Power[0], lpTransRangeAttack->Power[1]);
			pow += (pow*P_Dash_AddDamage[Point]) / 100;
			pow >>= 1;
			lpTransSkillAttackData->Power = pow;
			lpTransSkillAttackData->AttackState = SKILL_P_DASH;
			return TRUE;
			//»ØÐýÕ¶»÷
		case SKILL_PLAY_M_BLOW:
			if (lpTransSkillAttackData->TargetCount > M_Blow_AttackNum[Point])
				return FALSE;
			pow = GetRandomPos(lpTransRangeAttack->Power[0], lpTransRangeAttack->Power[1]);
			pow += (pow*M_Blow_AddDamage[Point]) / 100;

			lpTransSkillAttackData->Power = pow;
			lpTransSkillAttackData->AttackState = 0;
			lpTransSkillAttackData->AttackSize = M_Blow_Area[Point];
			dm_Critical_Temp = lpTransRangeAttack->Critical[0];
			return TRUE;
		}
		break;
	case CHARACTERCLASS_Mechanician:
		switch (dwSkillCode)
		{
			//»úÐµÁñµ¯
		case SKILL_PLAY_MECHANIC_BOMB:
			lpTransSkillAttackData->AttackSize = Mechanic_Bomb_Attack_Range[Point];
			lpTransSkillAttackData->Power = GetRandomPos(Mechanic_Bomb_Damage[Point][0], Mechanic_Bomb_Damage[Point][1]);
			lpTransAttackData->Power = lpTransSkillAttackData->Power >> 1;
			lpTransSkillAttackData->Power >>= 1;
			lpTransSkillAttackData->AttackState = 0;
			return TRUE;
			//ÆÆËé¾Þ»÷
		case SKILL_PLAY_GREAT_SMASH:
			lpTransSkillAttackData->AttackSize = 70;
			pow = GetRandomPos(lpTransRangeAttack->Power[0], lpTransRangeAttack->Power[1] + (lpTransRangeAttack->Critical[1] / 5));
			pow += G_Smash_Attack_Rage[Point];
			pow >>= 1;
			lpTransSkillAttackData->Power = pow;
			lpTransAttackData->Power = pow;
			lpTransSkillAttackData->AttackState = 0;
			return TRUE;
			//»ð»¨µç³¡
		case SKILL_PLAY_SPARK:
			lpTransSkillAttackData->AttackSize = Spark_Area[Point];
			lpTransSkillAttackData->Power = GetRandomPos(Spark_Damage[Point][0], (Spark_Damage[Point][1] + lpPlayInfo->sCharacterData.iLevel * 4));
			lpTransSkillAttackData->AttackState = 101;
			return TRUE;
			//À×öª³å»÷
		case SKILL_PLAY_IMPULSION:
			lpTransSkillAttackData->AttackSize = Impulsion_Range[Point];
			lpTransSkillAttackData->Power = Impulsion_LightingDamage[Point];
			lpTransSkillAttackData->AttackState = 101;
			return TRUE;
			//ÍþÉåÅ­ºð
		case SKILL_PLAY_COMPULSION:
			lpTransSkillAttackData->AttackState = 201;
			lpTransSkillAttackData->AttackSize = Compulsion_Area[Point];
			lpPlayInfo->dwSkill_Compulsion_Time = SERVER_GAMETIME + Compulsion_Time[Point] * 1000;
			lpPlayInfo->dwSkill_Compulsion_Param = Compulsion_AddAbsorb[Point];
			return TRUE;
			//Åùö¨Ðý·ç
		case SKILL_PLAY_LANDMINNING:
			lpTransSkillAttackData->AttackSize = Landminning_Area[Point];
			lpTransSkillAttackData->AttackState = 0;
			pow = GetRandomPos(lpTransRangeAttack->Power[0], lpTransRangeAttack->Power[1]);
			pow += (pow*Landminning_AddDamage[Point]) / 100;
			lpTransSkillAttackData->Power = pow;
			return TRUE;
			//¾¿¼«Ö®ÈÐ
		case SKILL_PLAY_R_SMASH:
			switch (lpTransSkillAttackData->AttackState)
			{
			case 3:
				lpTransSkillAttackData->AttackSize = 60;
				pow = GetRandomPos(lpTransRangeAttack->Power[0], lpTransRangeAttack->Power[1]);
				pow += (pow*R_Smash_AddDamage[Point]) / 100;
				lpTransSkillAttackData->AttackState = SKILL_R_SMASH;
				lpTransSkillAttackData->Power = pow;
				break;
			case 4:
				lpTransSkillAttackData->AttackSize = 100;
				pow = GetRandomPos(lpTransRangeAttack->Power[0], lpTransRangeAttack->Power[1]);
				pow += (pow*Landminning_AddDamage[Point]) / 100;
				lpTransSkillAttackData->AttackState = 0;
				lpTransSkillAttackData->Power = pow / 2;
				break;
			}
			return TRUE;
		}
		break;
	case CHARACTERCLASS_Archer:
		switch (dwSkillCode)
		{
			//¿ñ±©»ð¼ý
		case SKILL_PLAY_ARROWOF_RAGE:
			lpTransSkillAttackData->AttackSize = A_Rage_Area[Point];
			pow = GetRandomPos(lpTransRangeAttack->Power[0], lpTransRangeAttack->Power[1]);
			if (Point > 4)
				pow += (lpPlayInfo->sCharacterData.iLevel * A_Rage_Damage[Point]);
			else
				pow += (lpPlayInfo->sCharacterData.iLevel / A_Rage_Damage[Point]);
			lpTransSkillAttackData->Power = pow;
			lpTransSkillAttackData->AttackState = 0;
			return TRUE;
			//ÔªËØ¹¥»÷
		case SKILL_PLAY_ELEMENTAL_SHOT:
			if (Param != 1) return FALSE;
			lpTransSkillAttackData->AttackSize = 75;
			pow = GetRandomPos(lpTransRangeAttack->Power[0], lpTransRangeAttack->Power[1]);
			lpTransAttackData->Power = pow;
			lpTransSkillAttackData->Power = GetRandomPos(Elemental_Shot_Lightning[Point][0], Elemental_Shot_Lightning[Point][1]);
			lpTransSkillAttackData->AttackState = 105;
			lpTransAttackData->AttackState |= (sITEMINFO_LIGHTING + 1) << 16;
			return TRUE;
			//±¬ÁÑÖ®¼ý
		case SKILL_PLAY_BOMB_SHOT:
			if (lpChar)
			{
				pow = GetRandomPos(lpTransRangeAttack->Power[0], lpTransRangeAttack->Power[1]);
				pow += (pow*BombShot_Damage[Point]) / 100;
				if (lpChar->sCharacterData.iMonsterType == MONSTERTYPE_Demon)
					pow += (pow*BombShot_DemonDamage[Point]) / 100;
				lpTransAttackData->Power = pow;
			}
			lpTransSkillAttackData->Power = GetRandomPos(BombShot_AddDamage[Point][0], BombShot_AddDamage[Point][1]);
			lpTransSkillAttackData->AttackState = 100;
			lpTransAttackData->AttackState = 0;
			return TRUE;
			//¹ß´©Ö®¼ý
		case SKILL_PLAY_PERFORATION:
			lpTransSkillAttackData->AttackSize = 340 + Perforation_Attack_Range[Point];
			pow = GetRandomPos(lpTransRangeAttack->Power[0], lpTransRangeAttack->Power[1]);
			pow += (pow*Perforation_Damage[Point]) / 100;
			lpTransSkillAttackData->Power = pow;
			lpTransSkillAttackData->AttackState = 0;
			dm_Critical_Temp = lpTransRangeAttack->Critical[0];
			return TRUE;
			//ç³»Ë¾øÑ×
		case SKILL_PLAY_PHOENIX_SHOT:
			lpTransSkillAttackData->Power = GetRandomPos(lpTransRangeAttack->Power[0], lpTransRangeAttack->Power[1]);
			lpTransSkillAttackData->Power += (lpTransSkillAttackData->Power*Phoenix_Shot_DamagePercent[Point]) / 100;
			lpTransSkillAttackData->AttackState = 0;
			return TRUE;
			//»ØÐýÖ®Îè
		case SKILL_PLAY_E_SHOT:
			pow = GetRandomPos(lpTransRangeAttack->Power[0], lpTransRangeAttack->Power[1]);
			pow += (pow*E_Shot_Damge[Point]) / 100;
			pow >>= 1;
			lpTransSkillAttackData->Power = pow;
			lpTransSkillAttackData->AttackState = 101;
			lpTransSkillAttackData->AttackSize = 140;
			return TRUE;
			//Ðþ¹âÖ®Îè
		case SKILL_PLAY_S_ROPE:
			pow = GetRandomPos(lpTransRangeAttack->Power[0], lpTransRangeAttack->Power[1]);
			pow += (pow*S_Rope_Damge[Point]) / 100;
			pow >>= 1;
			lpTransSkillAttackData->Power = pow;
			lpTransSkillAttackData->AttackState = 105;
			lpTransSkillAttackData->AttackSize = 80;
			return TRUE;
			//ì«·çÖ®¼ý
		case SKILL_PLAY_N_SPLASH:
			lpTransSkillAttackData->AttackSize = 140 + N_Splash_Range[Point];
			lpTransSkillAttackData->Power = GetRandomPos(lpTransRangeAttack->Power[0], lpTransRangeAttack->Power[1]);
			lpTransSkillAttackData->Power += (lpTransSkillAttackData->Power*N_Splash_Damge[Point]) / 100;
			lpTransSkillAttackData->AttackState = 11;
			return TRUE;
			//º®±ùÖ®¼ý
		case SKILL_PLAY_C_TRAP:
			lpTransSkillAttackData->AttackSize = C_Trap_Area[Point];
			lpTransSkillAttackData->Power = GetRandomPos(lpTransRangeAttack->Power[0], lpTransRangeAttack->Power[1]);
			lpTransSkillAttackData->Power += (lpTransSkillAttackData->Power*C_Trap_Dmage[Point]) / 100;
			lpTransSkillAttackData->AttackState = 3;
			return TRUE;
		}
		break;
	case CHARACTERCLASS_Pikeman:
		switch (dwSkillCode)
		{
			//Áú¾íÇ¹·ç
		case SKILL_PLAY_PIKEWIND:
			lpTransSkillAttackData->AttackSize = Pike_Wind_Push_Lenght[Point];
			lpTransSkillAttackData->Power = GetRandomPos(Pike_Wind_Damage[Point][0], Pike_Wind_Damage[Point][1]);
			lpTransSkillAttackData->AttackState = 1;
			return TRUE;
			//´óµØÖ®Ç¹
		case SKILL_PLAY_GROUND_PIKE:
			lpTransSkillAttackData->AttackSize = G_Pike_Range[Point];
			lpTransSkillAttackData->Power = GetRandomPos(G_Pike_Damage[Point][0], G_Pike_Damage[Point][1]);
			lpTransSkillAttackData->AttackState = 3;
			return TRUE;
			//Ç¹Ö®ì«·ç
		case SKILL_PLAY_TORNADO:
			pow = GetRandomPos(lpTransRangeAttack->Power[0], lpTransRangeAttack->Power[1]);
			pow += (pow*Tornado_Damage[Point]) / 100;
			lpTransSkillAttackData->Power = pow;
			lpTransSkillAttackData->AttackState = 0;
			return TRUE;
			//ÎÞÏÞÁ¦Ç¹
		case SKILL_PLAY_EXPANSION:
			lpTransSkillAttackData->AttackSize = 180;
			pow = GetRandomPos(lpTransRangeAttack->Power[0], lpTransRangeAttack->Power[1]);
			pow += (pow*Expansion_Damage[Point]) / 100;
			pow += (pow*(5 * (Point + 1))) / 100;
			lpTransSkillAttackData->Power = pow;
			lpTransSkillAttackData->AttackState = 0;
			if (lpChar)
			{
				for (cnt = 0; cnt < lpTransRangeAttack->TargetCount; cnt++)
				{
					if (lpTransRangeAttack->dwTarObjectSerial[cnt] == lpChar->iID)
					{
						lpTransAttackData->Power = 0;
						break;
					}
				}
			}
			return TRUE;
			//ÁéÉß±êÇ¹
		case SKILL_PLAY_VENOM_SPEAR:
			lpTransSkillAttackData->AttackSize = VenomSpear_Range[Point];
			pow = GetRandomPos(lpTransRangeAttack->Power[0], lpTransRangeAttack->Power[1]);
			pow += (pow * VenomSpear_Damage[Point]) / 100;
			lpTransSkillAttackData->Power = pow;
			lpTransSkillAttackData->AttackState = 106;
			lpTransAttackData->AttackState |= (sITEMINFO_POISON + 1) << 16;
			return TRUE;
			//µØÏ®ÆæÇ¹
		case SKILL_PLAY_F_SPEAR:
			lpTransSkillAttackData->AttackSize = F_Spear_Area[Point];
			pow = GetRandomPos(lpTransRangeAttack->Power[0], lpTransRangeAttack->Power[1]);
			pow += (pow * F_Spear_AddDamage[Point]) / 100;
			lpTransSkillAttackData->Power = pow;
			lpTransSkillAttackData->AttackState = 3;
			lpTransAttackData->AttackState |= (sITEMINFO_ICE + 1) << 16;
			return TRUE;
			//Ðý·çÖ®Ç¹
		case SKILL_PLAY_SS_ATTACK:
			lpTransSkillAttackData->AttackSize = 100;
			pow = GetRandomPos(lpTransRangeAttack->Power[0], lpTransRangeAttack->Power[1]);
			pow += (pow * SS_Attack_AddDamage[Point]) / 100;
			pow >>= 1;
			lpTransSkillAttackData->Power = pow;
			lpTransSkillAttackData->AttackState = 0;
			return TRUE;
		}
		break;
	case CHARACTERCLASS_Atalanta:
		switch (dwSkillCode)
		{
			//ÃÀ¶ÅÉ¯¶Ü
		case SKILL_PLAY_SHIELD_STRIKE:
			lpTransSkillAttackData->Power = GetRandomPos(S_Strike_Damage[Point][0], S_Strike_Damage[Point][1] + (lpPlayInfo->sCharacterData.iLevel / 5));
			lpTransSkillAttackData->AttackState = 5;
			return TRUE;
			//Áé»êÍÌÊÉ
		case SKILL_PLAY_SOUL_SUCKER:
			lpTransSkillAttackData->Power = Point;
			lpTransSkillAttackData->AttackState = 4;
			return TRUE;
			//¹âÁÔÖ®Ç¹
		case SKILL_PLAY_LIGHTNING_JAVELIN:
			lpTransSkillAttackData->AttackSize = 100;
			pow = GetRandomPos(Lightning_Javelin_Damage[Point][0], Lightning_Javelin_Damage[Point][1] + (lpPlayInfo->sCharacterData.iLevel / 3));
			lpTransSkillAttackData->Power = pow;
			lpTransSkillAttackData->AttackState = 101;
			lpTransAttackData->Power = GetRandomPos(lpTransRangeAttack->Power[0], lpTransRangeAttack->Power[1] + (lpPlayInfo->sCharacterData.iLevel / 3));
			lpTransAttackData->AttackState = 0;
			if (lpChar)
			{
				if (lpChar->sCharacterData.iMonsterType == MONSTERTYPE_Undead)
					lpTransAttackData->Power += lpTransAttackData->Power / 2;
				if (lpTransRangeAttack->Critical[0])
				{
					if ((rand() % 100) < GetCritical(lpPlayInfo, lpChar, lpTransRangeAttack->Critical[0]))
						lpTransAttackData->Power = (lpTransAttackData->Power * 170) / 100;
				}
			}
			return TRUE;
			//±©·ç¿ñ±ê
		case SKILL_PLAY_STORM_JAVELIN:
			lpTransSkillAttackData->AttackSize = 340;
			pow = GetRandomPos(lpTransRangeAttack->Power[0], lpTransRangeAttack->Power[1]);
			pow += (pow*Storm_Javelin_Damage[Point]) / 100;
			lpTransSkillAttackData->Power = pow;
			lpTransSkillAttackData->AttackState = 0;
			return TRUE;
			//Ê®×ÖÅ­»÷
		case SKILL_PLAY_X_RAGE:
			lpTransSkillAttackData->Power = GetRandomPos(lpTransRangeAttack->Power[0], lpTransRangeAttack->Power[1]);
			lpTransSkillAttackData->Power += (lpTransSkillAttackData->Power*X_Rage_DamagePercent[Point]) / 100;
			lpTransSkillAttackData->AttackSize = X_Rage_Area[Point];
			lpTransSkillAttackData->AttackState = 0;
			return TRUE;
		}
		break;
	case CHARACTERCLASS_Knight:
		switch (dwSkillCode)
		{
			//Ä§Éñ½£
		case SKILL_PLAY_SWORD_BLAST:
			pow = GetRandomPos(Sword_Blast_Damage[Point][0], Sword_Blast_Damage[Point][1] + (lpPlayInfo->sCharacterData.iLevel * 4));
			lpTransSkillAttackData->Power = pow;
			lpTransSkillAttackData->AttackState = 0;
			return TRUE;
			//¿ñÔê»ÓÎè
		case SKILL_PLAY_BRANDISH:
			lpTransSkillAttackData->AttackSize = Brandish_Range[Point];
			pow = GetRandomPos(lpTransRangeAttack->Power[0], lpTransRangeAttack->Power[1]);
			pow += (pow*Brandish_Damage[Point]) / 100;
			lpTransSkillAttackData->Power = pow;
			lpTransSkillAttackData->AttackState = 0;
			return TRUE;
			//Ò»ÎíÒø
		case SKILL_PLAY_PIERCING:
			pow = GetRandomPos(lpTransRangeAttack->Power[0], lpTransRangeAttack->Power[1]);
			pow += (pow*Piercing_Damage[Point]) / 100;
			lpTransSkillAttackData->Power = pow;
			lpTransSkillAttackData->AttackState = 0;
			return TRUE;
			//ÕæÄ§Éñ½£
		case SKILL_PLAY_SWORD_OF_JUSTICE:
			lpTransSkillAttackData->Power = GetRandomPos(lpTransRangeAttack->Power[0], lpTransRangeAttack->Power[1]);
			lpTransSkillAttackData->Power += (lpTransSkillAttackData->Power*Sword_Of_Justice_DamagePercent[Point]) / 100;
			lpTransSkillAttackData->AttackSize = Sword_Of_Justice_Area[Point];
			lpTransSkillAttackData->AttackState = 0;
			return TRUE;
			//ÉýÁúÖØ»÷
		case SKILL_PLAY_C_MOON:
			lpTransSkillAttackData->Power = GetRandomPos(lpTransRangeAttack->Power[0], lpTransRangeAttack->Power[1]);
			lpTransSkillAttackData->Power += (lpTransSkillAttackData->Power*C_Moon_Damage[Point]) / 100;
			lpTransSkillAttackData->AttackSize = C_Moon_Area[Point];
			lpTransSkillAttackData->AttackState = 0;
			return TRUE;
		}
		break;
	case CHARACTERCLASS_Magician:
		switch (dwSkillCode)
		{
			//»ðÇòÖ®Êõ
		case SKILL_PLAY_FIRE_BALL:
			lpTransSkillAttackData->AttackSize = FireBall_Area[Point];

			pow1 = FireBall_Damage[Point][0];
			pow2 = FireBall_Damage[Point][1];

			if (lpPlayInfo->dwSkill_SpiritElemental_Time)
			{
				if (lpPlayInfo->dwSkill_SpiritElemental_Time > SERVER_GAMETIME)
				{
					pow1 += (pow1 * lpPlayInfo->dwSkill_SpiritElemental_Param) / 100;
					pow2 += (pow2 * lpPlayInfo->dwSkill_SpiritElemental_Param) / 100;
				}
				else
				{
					lpPlayInfo->dwSkill_SpiritElemental_Time = 0;
					lpPlayInfo->dwSkill_SpiritElemental_Param = 0;
				}
			}
			if (lpPlayInfo->dwSkill_T_Anima_Time)
			{
				if (lpPlayInfo->dwSkill_T_Anima_Time > SERVER_GAMETIME)
				{
					pow1 += (pow1 * lpPlayInfo->dwSkill_T_Anima_Param) / 100;
					pow2 += (pow2 * lpPlayInfo->dwSkill_T_Anima_Param) / 100;
				}
				else
				{
					lpPlayInfo->dwSkill_T_Anima_Time = 0;
					lpPlayInfo->dwSkill_T_Anima_Param = 0;
				}
			}

			pow1 += lpTransRangeAttack->Power2[0] / 8;
			pow2 += lpTransRangeAttack->Power2[1] / 4;

			pow = GetRandomPos(pow1, pow2);

			lpTransSkillAttackData->Power = (pow * 70) / 100;
			lpTransAttackData->Power = pow;

			lpTransSkillAttackData->AttackState = 100;
			lpTransAttackData->AttackState |= (sITEMINFO_FIRE + 1) << 16;
			return TRUE;
			//Áú¾íº£·ç
		case SKILL_PLAY_COLUMN_OF_WATER:
			lpTransSkillAttackData->AttackSize = Watornado_Area[Point];

			pow1 = Watornado_Damage[Point][0];
			pow2 = Watornado_Damage[Point][1];

			if (lpPlayInfo->dwSkill_SpiritElemental_Time)
			{
				if (lpPlayInfo->dwSkill_SpiritElemental_Time > SERVER_GAMETIME)
				{
					pow1 += (pow1*lpPlayInfo->dwSkill_SpiritElemental_Param) / 100;
					pow2 += (pow2*lpPlayInfo->dwSkill_SpiritElemental_Param) / 100;
				}
				else
				{
					lpPlayInfo->dwSkill_SpiritElemental_Time = 0;
					lpPlayInfo->dwSkill_SpiritElemental_Param = 0;
				}
			}
			if (lpPlayInfo->dwSkill_T_Anima_Time)
			{
				if (lpPlayInfo->dwSkill_T_Anima_Time > SERVER_GAMETIME)
				{
					pow1 += (pow1*lpPlayInfo->dwSkill_T_Anima_Param) / 100;
					pow2 += (pow2*lpPlayInfo->dwSkill_T_Anima_Param) / 100;
				}
				else
				{
					lpPlayInfo->dwSkill_T_Anima_Time = 0;
					lpPlayInfo->dwSkill_T_Anima_Param = 0;
				}
			}

			pow1 += lpTransRangeAttack->Power2[0];
			pow2 += lpTransRangeAttack->Power2[1];

			pow1 += lpTransRangeAttack->Critical[1] / 2;
			pow2 += lpTransRangeAttack->Critical[1];

			pow = GetRandomPos(pow1, pow2);

			lpTransSkillAttackData->Power = (pow * 70) / 100;
			lpTransAttackData->Power = pow;
			lpTransSkillAttackData->AttackState = 104;
			lpTransAttackData->AttackState |= (sITEMINFO_NONE) << 16;
			return TRUE;
			//µØÁÑ³å»÷
		case SKILL_PLAY_DIASTROPHISM:
			if (lpTransRangeAttack->Power[0] < lpTransRangeAttack->Power2[0] || lpTransRangeAttack->Power[1] < lpTransRangeAttack->Power2[1])
				return FALSE;

			lpTransSkillAttackData->AttackSize = Diastrophism_Area[Point];

			pow1 = Diastrophism_Damage[Point][0];
			pow2 = Diastrophism_Damage[Point][1];

			if (lpPlayInfo->dwSkill_SpiritElemental_Time)
			{
				if (lpPlayInfo->dwSkill_SpiritElemental_Time > SERVER_GAMETIME)
				{
					pow1 += (pow1*lpPlayInfo->dwSkill_SpiritElemental_Param) / 100;
					pow2 += (pow2*lpPlayInfo->dwSkill_SpiritElemental_Param) / 100;
				}
				else
				{
					lpPlayInfo->dwSkill_SpiritElemental_Time = 0;
					lpPlayInfo->dwSkill_SpiritElemental_Param = 0;
				}
			}
			if (lpPlayInfo->dwSkill_T_Anima_Time)
			{
				if (lpPlayInfo->dwSkill_T_Anima_Time > SERVER_GAMETIME)
				{
					pow1 += (pow1*lpPlayInfo->dwSkill_T_Anima_Param) / 100;
					pow2 += (pow2*lpPlayInfo->dwSkill_T_Anima_Param) / 100;
				}
				else
				{
					lpPlayInfo->dwSkill_T_Anima_Time = 0;
					lpPlayInfo->dwSkill_T_Anima_Param = 0;
				}
			}
			pow = GetRandomPos(pow1 + lpTransRangeAttack->Power2[0] * 2 + lpTransRangeAttack->Critical[1] / 2, pow2 + lpTransRangeAttack->Power2[1] * 2 + lpTransRangeAttack->Critical[1]);

			lpTransSkillAttackData->Power = pow;
			lpTransSkillAttackData->AttackState = 0;
			return TRUE;
			//»ðÑæ²¨¶¯
		case SKILL_PLAY_FLAME_WAVE:
			pow1 = Flame_Wave_FireDamage[Point][0];
			pow2 = Flame_Wave_FireDamage[Point][1];

			if (lpPlayInfo->dwSkill_SpiritElemental_Time)
			{
				if (lpPlayInfo->dwSkill_SpiritElemental_Time > SERVER_GAMETIME)
				{
					pow1 += (pow1 * lpPlayInfo->dwSkill_SpiritElemental_Param) / 100;
					pow2 += (pow2 * lpPlayInfo->dwSkill_SpiritElemental_Param) / 100;
				}
				else
				{
					lpPlayInfo->dwSkill_SpiritElemental_Time = 0;
					lpPlayInfo->dwSkill_SpiritElemental_Param = 0;
				}
			}
			if (lpPlayInfo->dwSkill_T_Anima_Time)
			{
				if (lpPlayInfo->dwSkill_T_Anima_Time > SERVER_GAMETIME)
				{
					pow1 += (pow1*lpPlayInfo->dwSkill_T_Anima_Param) / 100;
					pow2 += (pow2*lpPlayInfo->dwSkill_T_Anima_Param) / 100;
				}
				else
				{
					lpPlayInfo->dwSkill_T_Anima_Time = 0;
					lpPlayInfo->dwSkill_T_Anima_Param = 0;
				}
			}
			pow1 += lpTransRangeAttack->Power2[0] * 2;
			pow2 += lpTransRangeAttack->Power2[1] * 2;

			pow1 += lpTransRangeAttack->Critical[1] / 2;
			pow2 += lpTransRangeAttack->Critical[1];

			pow = GetRandomPos(pow1, pow2);
			lpTransSkillAttackData->Power = pow;

			lpTransSkillAttackData->AttackState = 100;
			return TRUE;
			//¿Õ¼äÅ¤Çú
		case SKILL_PLAY_DISTORTION:
			lpTransSkillAttackData->AttackState = 7;
			return TRUE;
			//ÔÉÊ¯ÕÙ»½
		case SKILL_PLAY_METEO:
			lpTransSkillAttackData->AttackSize = Meteo_Area[Point];

			pow1 = Meteo_Damage[Point][0];
			pow2 = Meteo_Damage[Point][1];

			if (lpPlayInfo->dwSkill_SpiritElemental_Time)
			{
				if (lpPlayInfo->dwSkill_SpiritElemental_Time > SERVER_GAMETIME)
				{
					pow1 += (pow1 * lpPlayInfo->dwSkill_SpiritElemental_Param) / 100;
					pow2 += (pow2 * lpPlayInfo->dwSkill_SpiritElemental_Param) / 100;
				}
				else
				{
					lpPlayInfo->dwSkill_SpiritElemental_Time = 0;
					lpPlayInfo->dwSkill_SpiritElemental_Param = 0;
				}
			}
			if (lpPlayInfo->dwSkill_T_Anima_Time)
			{
				if (lpPlayInfo->dwSkill_T_Anima_Time > SERVER_GAMETIME)
				{
					pow1 += (pow1*lpPlayInfo->dwSkill_T_Anima_Param) / 100;
					pow2 += (pow2*lpPlayInfo->dwSkill_T_Anima_Param) / 100;
				}
				else
				{
					lpPlayInfo->dwSkill_T_Anima_Time = 0;
					lpPlayInfo->dwSkill_T_Anima_Param = 0;
				}
			}
			pow1 += lpTransRangeAttack->Power2[0] * 2;
			pow2 += lpTransRangeAttack->Power2[1] * 2;

			pow1 += lpTransRangeAttack->Critical[1] / 2;
			pow2 += lpTransRangeAttack->Critical[1];

			pow = GetRandomPos(pow1, pow2);
			lpTransSkillAttackData->Power = pow;

			lpTransSkillAttackData->AttackState = 100;
			return TRUE;
			//Á÷ÐÇ»ðÓê
		case SKILL_PLAY_SILRAPHIM:
			lpTransSkillAttackData->AttackSize = 60;

			pow1 = Silraphim_Damage[Point][0];
			pow2 = Silraphim_Damage[Point][1];

			if (lpPlayInfo->dwSkill_SpiritElemental_Time)
			{
				if (lpPlayInfo->dwSkill_SpiritElemental_Time > SERVER_GAMETIME)
				{
					pow1 += (pow1 * lpPlayInfo->dwSkill_SpiritElemental_Param) / 100;
					pow2 += (pow2 * lpPlayInfo->dwSkill_SpiritElemental_Param) / 100;
				}
				else
				{
					lpPlayInfo->dwSkill_SpiritElemental_Time = 0;
					lpPlayInfo->dwSkill_SpiritElemental_Param = 0;
				}
			}
			if (lpPlayInfo->dwSkill_T_Anima_Time)
			{
				if (lpPlayInfo->dwSkill_T_Anima_Time > SERVER_GAMETIME)
				{
					pow1 += (pow1*lpPlayInfo->dwSkill_T_Anima_Param) / 100;
					pow2 += (pow2*lpPlayInfo->dwSkill_T_Anima_Param) / 100;
				}
				else
				{
					lpPlayInfo->dwSkill_T_Anima_Time = 0;
					lpPlayInfo->dwSkill_T_Anima_Param = 0;
				}
			}
			pow1 += lpTransRangeAttack->Power2[0] * 2;
			pow2 += lpTransRangeAttack->Power2[1] * 2;

			pow1 += lpTransRangeAttack->Critical[1] / 2;
			pow2 += lpTransRangeAttack->Critical[1];

			pow = GetRandomPos(pow1, pow2);
			lpTransSkillAttackData->Power = pow >> 1;

			lpTransSkillAttackData->AttackState = 0;

			return TRUE;
			//ÉñÊ¥Ï´Àñ
		case SKILL_PLAY_P_IGNIS:
			lpTransSkillAttackData->AttackSize = P_Ignis_Area[Point];

			pow1 = P_Ignis_Dmage[Point][0];
			pow2 = P_Ignis_Dmage[Point][1];

			if (lpPlayInfo->dwSkill_SpiritElemental_Time)
			{
				if (lpPlayInfo->dwSkill_SpiritElemental_Time > SERVER_GAMETIME)
				{
					pow1 += (pow1 * lpPlayInfo->dwSkill_SpiritElemental_Param) / 100;
					pow2 += (pow2 * lpPlayInfo->dwSkill_SpiritElemental_Param) / 100;
				}
				else
				{
					lpPlayInfo->dwSkill_SpiritElemental_Time = 0;
					lpPlayInfo->dwSkill_SpiritElemental_Param = 0;
				}
			}
			if (lpPlayInfo->dwSkill_T_Anima_Time)
			{
				if (lpPlayInfo->dwSkill_T_Anima_Time > SERVER_GAMETIME)
				{
					pow1 += (pow1*lpPlayInfo->dwSkill_T_Anima_Param) / 100;
					pow2 += (pow2*lpPlayInfo->dwSkill_T_Anima_Param) / 100;
				}
				else
				{
					lpPlayInfo->dwSkill_T_Anima_Time = 0;
					lpPlayInfo->dwSkill_T_Anima_Param = 0;
				}
			}
			pow1 += lpTransRangeAttack->Power2[0] * 2;
			pow2 += lpTransRangeAttack->Power2[1] * 2;

			pow1 += lpTransRangeAttack->Critical[1] / 2;
			pow2 += lpTransRangeAttack->Critical[1];

			pow = GetRandomPos(pow1, pow2);
			lpTransSkillAttackData->Power = pow;

			lpTransSkillAttackData->AttackState = 0;
			return TRUE;
		}
		break;
	case CHARACTERCLASS_Priestess:
		switch (dwSkillCode)
		{
			//ÉñÖ®À×µç
		case SKILL_PLAY_DIVINE_LIGHTNING:
			if (lpTransSkillAttackData->TargetCount > Divine_Lightning_Num[Point])
				return FALSE;
			pow1 = Divine_Lightning_Damage[Point][0] + lpTransRangeAttack->Power2[0] * 2 + lpTransRangeAttack->Critical[1] / 2;
			pow2 = Divine_Lightning_Damage[Point][1] + lpTransRangeAttack->Power2[1] * 2 + lpTransRangeAttack->Critical[1];
			lpTransSkillAttackData->Power = GetRandomPos(pow1, pow2);
			lpTransSkillAttackData->AttackState = 103;
			return TRUE;
			//Ê¥¹âÖ®Öä
		case SKILL_PLAY_EXTINCTION:
			lpTransSkillAttackData->Power = Point + 1;
			lpTransSkillAttackData->AttackState = 6;
			return TRUE;
			//±ùËªÊÉÔÂ
		case SKILL_PLAY_GLACIAL_SPIKE:
			pow1 = Glacial_Spike_Damage[Point][0] + lpTransRangeAttack->Power2[0] * 2 + lpTransRangeAttack->Critical[1] / 2;
			pow2 = Glacial_Spike_Damage[Point][1] + lpTransRangeAttack->Power2[0] * 2 + lpTransRangeAttack->Critical[1] / 2;

			lpTransSkillAttackData->Power = GetRandomPos(pow1, pow2);
			lpTransSkillAttackData->AttackState = 3;
			return TRUE;
			//ÌìÀ×Ö®Å­
		case SKILL_PLAY_CHAIN_LIGHTNING:
			if (lpTransSkillAttackData->TargetCount > Chain_Lightning_Num[Point])
				return FALSE;
			lpTransSkillAttackData->AttackSize = Chain_Lightning_Range[Point] * Chain_Lightning_Num[Point];
			pow1 = Chain_Lightning_Damage[Point][0] + lpTransRangeAttack->Power2[0] * 2 + lpTransRangeAttack->Critical[1] / 2;
			pow2 = Chain_Lightning_Damage[Point][1] + lpTransRangeAttack->Power2[1] * 2 + lpTransRangeAttack->Critical[1];
			lpTransSkillAttackData->Power = GetRandomPos(pow1, pow2);
			lpTransSkillAttackData->AttackState = 101;
			return TRUE;
			//ÉñÊ¥µç²¨
		case SKILL_PLAY_S_IMPACT:
			lpTransSkillAttackData->AttackSize = 60;
			pow1 = S_Impact_Damage[Point][0] + lpTransRangeAttack->Power2[0] * 2 + lpTransRangeAttack->Critical[1] / 2;
			pow2 = S_Impact_Damage[Point][1] + lpTransRangeAttack->Power2[1] * 2 + lpTransRangeAttack->Critical[1];
			lpTransSkillAttackData->Power = (GetRandomPos(pow1, pow2) >> 1);
			lpTransSkillAttackData->AttackState = 101;
			return TRUE;
			//±©·çÑ©
		case SKILL_PLAY_S_PRMIEL:
			lpTransSkillAttackData->AttackSize = S_Ramiel_Area[Point];
			pow1 = S_Ramiel_Damage[Point][0] + lpTransRangeAttack->Power2[0] * 2 + lpTransRangeAttack->Critical[1] / 2;
			pow2 = S_Ramiel_Damage[Point][1] + lpTransRangeAttack->Power2[1] * 2 + lpTransRangeAttack->Critical[1];
			lpTransSkillAttackData->Power = GetRandomPos(pow1, pow2);
			lpTransSkillAttackData->AttackState = 3;
			return TRUE;
		}
		break;
		//´Ì¿Í
	case CHARACTERCLASS_Assassin:
		switch (dwSkillCode)
		{
			//Áé»êÕðº³
		case SKILL_PLAY_SOUL_SHOCK:
			lpTransSkillAttackData->AttackSize = Soul_Shock_Area[Point];
			lpTransSkillAttackData->Power = Soul_Shock_Time[Point];
			lpTransSkillAttackData->AttackState = 9;
			return TRUE;
			//ÎÁÒßÖ®ÈÐ
		case SKILL_PLAY_POLLUTE:
			lpTransSkillAttackData->AttackSize = Pollute_Area[Point];
			pow = GetRandomPos(lpTransRangeAttack->Power[0], lpTransRangeAttack->Power[1]);
			pow += (pow * Pollute_Damage[Point]) / 100;
			lpTransSkillAttackData->Power = pow;

			lpTransSkillAttackData->AttackState = 106;
			lpTransAttackData->AttackState |= (sITEMINFO_POISON + 1) << 16;
			return TRUE;
			//Ó°×Ó»ðÑæ
		case SKILL_PLAY_SHADOW_BOMB:
			lpTransSkillAttackData->AttackSize = Pollute_Area[Point];
			pow = GetRandomPos(lpTransRangeAttack->Power[0], lpTransRangeAttack->Power[1]);
			pow += (pow * Shadow_Bomb_Damage[Point]) / 100;
			lpTransSkillAttackData->Power = pow;

			lpTransSkillAttackData->AttackState = 100;
			lpTransAttackData->AttackState |= (sITEMINFO_FIRE + 1) << 16;
			return TRUE;
			//·ç±©Ö®ÈÐ
		case SKILL_PLAY_SHADOW_STORM:
			lpTransSkillAttackData->AttackSize = Shadow_Storm_Area[Point];
			pow = GetRandomPos(lpTransRangeAttack->Power[0], lpTransRangeAttack->Power[1]);
			pow += (pow * Shadow_Storm_Damage[Point]) / 100;
			lpTransSkillAttackData->Power = pow;
			lpTransSkillAttackData->AttackState = 203;
			return TRUE;
		}
		break;
		//ÈøÂú
	case CHARACTERCLASS_Shaman:
		switch (dwSkillCode)
		{
			//×çÖäÀ×»÷
		case SKILL_PLAY_INERTIA:
			lpTransSkillAttackData->AttackState = 10;
			return TRUE;
			//¾«ÉñÖäÊõ
		case SKILL_PLAY_SPIRITUAL_FLARE:
			lpTransSkillAttackData->AttackSize = Spiritual_Flare_Area[Point];
			pow = GetRandomPos(lpTransRangeAttack->Power[0], lpTransRangeAttack->Power[1]);
			pow += (pow * Spiritual_Flare_Damage[Point]) / 100;
			lpTransSkillAttackData->Power = pow;
			lpTransSkillAttackData->AttackState = 0;
			return TRUE;
			//ÁÔÈ¡
		case SKILL_PLAY_CHASING_HUNT:
			lpTransSkillAttackData->AttackSize = Chasing_Hunt_Sight[Point];
			lpTransSkillAttackData->AttackState = 202;
			return TRUE;
			//Â½µØÁé»ê
		case SKILL_PLAY_LAND_OF_GHOST:
			lpTransSkillAttackData->AttackSize = Phantom_Call_Area[Point];
			pow = GetRandomPos(lpTransRangeAttack->Power[0], lpTransRangeAttack->Power[1]);
			pow += (pow * Phantom_Call_Damage[Point]) / 100;
			lpTransSkillAttackData->Power = pow;
			lpTransSkillAttackData->AttackState = 0;
			return TRUE;
			//×çÖäÖ®Á¦
		case SKILL_PLAY_PRESS_DEITY:
			lpTransSkillAttackData->AttackSize = Press_Deity_Area[Point];
			pow = GetRandomPos(lpTransRangeAttack->Power[0], lpTransRangeAttack->Power[1]);
			pow += (pow * Press_Deity_Damage[Point]) / 100;
			lpTransSkillAttackData->Power = pow;
			lpTransSkillAttackData->AttackState = 0;
			return TRUE;
			//ÐñÈÕ¶«Éý
		case SKILL_PLAY_MOURNING_PRAY:
			lpTransSkillAttackData->AttackSize = Mourning_Pray_Area[Point];
			pow = GetRandomPos(lpTransRangeAttack->Power[0], lpTransRangeAttack->Power[1]);
			pow += (pow * Mourning_Pray_Damage[Point]) / 100;
			lpTransSkillAttackData->Power = pow;
			lpTransSkillAttackData->AttackState = 0;
			return TRUE;
			//ËÀÍöÖ®×¦
		case SKILL_PLAY_PHANTOM_NAIL:
			lpTransSkillAttackData->AttackSize = Phantom_Nail_Area[Point];
			pow = GetRandomPos(lpTransRangeAttack->Power[0], lpTransRangeAttack->Power[1]);
			pow += (pow * Phantom_Nail_Damage[Point]) / 100;
			lpTransSkillAttackData->Power = pow;
			lpTransSkillAttackData->AttackState = 0;
			return TRUE;
		}
		break;
	}
	return FALSE;
}

//·¶Î§¹¥»÷Êý¾Ý
int rsRecvRangeAttackData(User *lpPlayInfo, TRANS_SKIL_ATTACKDATA2 *lpTransRangeAttackData)
{
#ifdef _W_SERVER
	TRANS_ATTACKDATA		TransAttackData;
	TRANS_SKIL_ATTACKDATA	TransSkillAttackData;
	Unit					*lpChar;
	smTRANS_COMMAND_EX	smTransCommand;

	if (lpTransRangeAttackData->dwChkSum != dm_GetRangeDamgeChkSum(lpTransRangeAttackData))
	{
		smTransCommand.code = smTRANSCODE_SET_BLACKLIST;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = 8500;
		smTransCommand.LParam = 2;
		smTransCommand.SParam = 0;
		smTransCommand.EParam = 0;

		rsRecordDamageError(lpPlayInfo, (smTRANS_COMMAND *)&smTransCommand);
		return FALSE;
	}
	if (lpPlayInfo->sCharacterData.iClass == CHARACTERCLASS_Magician && (lpTransRangeAttackData->SkillCode & 0xFF) != SKILL_PLAY_ENCHANT_WEAPON)
	{
		if (lpTransRangeAttackData->AttackCount <= lpPlayInfo->DamagePacketCount || lpTransRangeAttackData->dwTime <= lpPlayInfo->dwDamagePacketTime)
			return FALSE;

		lpPlayInfo->DamagePacketCount = lpTransRangeAttackData->AttackCount;
		lpPlayInfo->dwDamagePacketTime = lpTransRangeAttackData->dwTime;
	}

	if (lpTransRangeAttackData->Power[0] > lpPlayInfo->sLimitDamage[0] || lpTransRangeAttackData->Power[1] > lpPlayInfo->sLimitDamage[1] || lpTransRangeAttackData->Critical[0] > lpPlayInfo->sLimitCritical[0])
	{
		smTransCommand.code = smTRANSCODE_SET_BLACKLIST;
		smTransCommand.size = sizeof(smTRANS_COMMAND_EX);
		smTransCommand.WParam = 8510;
		smTransCommand.WxParam = 1;

		smTransCommand.LParam = lpTransRangeAttackData->Power[0];
		smTransCommand.SParam = lpTransRangeAttackData->Power[1];
		smTransCommand.EParam = lpTransRangeAttackData->Critical[0];

		smTransCommand.LxParam = lpPlayInfo->sLimitDamage[0];
		smTransCommand.SxParam = lpPlayInfo->sLimitDamage[1];
		smTransCommand.ExParam = lpPlayInfo->sLimitCritical[0];

		rsRecordDamageError(lpPlayInfo, (smTRANS_COMMAND *)&smTransCommand);

		lpTransRangeAttackData->Power[0] = lpPlayInfo->sLimitDamage[0];
		lpTransRangeAttackData->Power[1] = lpPlayInfo->sLimitDamage[1];
		lpTransRangeAttackData->Critical[0] = lpPlayInfo->sLimitCritical[0];
	}

	TransAttackData.Power = 0;
	TransSkillAttackData.Power = 0;
	dm_SkillCode_Temp = 0;

	lpChar = SERVERUNIT->GetUnit(lpTransRangeAttackData->dwMainTargetObject, (EMapID)lpTransRangeAttackData->Area[0]);

	if (lpTransRangeAttackData->dwMainTargetObject)
	{
		TransAttackData.AttackState = 0;
		TransAttackData.AttackSize = 64 * 64;
		TransAttackData.dwDestObjectSerial = lpTransRangeAttackData->dwDestObjectSerial;
		TransAttackData.x = lpTransRangeAttackData->x;
		TransAttackData.y = lpTransRangeAttackData->y;
		TransAttackData.z = lpTransRangeAttackData->z;
	}

	TransSkillAttackData.AttackSize = lpTransRangeAttackData->AttackSize;
	TransSkillAttackData.dwDestObjectSerial = lpTransRangeAttackData->dwDestObjectSerial;
	TransSkillAttackData.x = lpTransRangeAttackData->x;
	TransSkillAttackData.y = lpTransRangeAttackData->y;
	TransSkillAttackData.z = lpTransRangeAttackData->z;
	TransSkillAttackData.AttackSize = 200;

	if (lpTransRangeAttackData->TargetCount > 0 && lpTransRangeAttackData->TargetCount < SKIL_ATTACK_CHAR_MAX)
	{
		memcpy(TransSkillAttackData.dwTarObjectSerial, lpTransRangeAttackData->dwTarObjectSerial, sizeof(DWORD)*lpTransRangeAttackData->TargetCount);
		TransSkillAttackData.TargetCount = lpTransRangeAttackData->TargetCount;
	}
	else
		TransSkillAttackData.TargetCount = 0;

	if (rsSetSkillRangeAttack(lpPlayInfo, lpChar, &TransAttackData, &TransSkillAttackData, lpTransRangeAttackData) == FALSE)
		return FALSE;

	//if (rsSetSkillPlus(lpPlayInfo,lpChar,&TransAttackData,lpTransRangeAttackData)==FALSE)
		//return FALSE;

	AddRangeForceOrbPower(lpPlayInfo, lpChar, &TransSkillAttackData, lpTransRangeAttackData->SkillCode, lpTransRangeAttackData->Power[0], lpTransRangeAttackData->Power[1]);

	int Total = TransSkillAttackData.TargetCount;
	int AvgPow;

	if (lpChar)
		Total += 1;
	if (Total)
		AvgPow = (TransAttackData.Power + TransSkillAttackData.Power*TransSkillAttackData.TargetCount) / Total;
	else
		AvgPow = 0;

	if (lpChar && TransAttackData.Power)
		rsRecvAttackData_Old(lpPlayInfo, &TransAttackData, lpChar, TRUE);

	if (TransSkillAttackData.TargetCount > 0)
	{
		RecvRangeAttack(lpPlayInfo, &TransSkillAttackData, lpTransRangeAttackData->Area[0], lpTransRangeAttackData->SkillCode);

		if (SERVERMAP->IsPVPMap(lpPlayInfo->iMapID))
		{
			RecvRangeAttack_User(lpPlayInfo, &TransSkillAttackData, lpTransRangeAttackData->Area[0], lpTransRangeAttackData->SkillCode);
		}
	}
	if (lpPlayInfo->iGameLevel != GAMELEVEL_None)
	{
		smTRANS_COMMAND	smTransCommand;

		smTransCommand.code = smTRANSCODE_DISP_DAMAGE;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = TransSkillAttackData.Power + TransAttackData.Power;
		smTransCommand.LParam = 0;
		smTransCommand.SParam = 0;
		smTransCommand.EParam = 0;

		SENDPACKET(lpPlayInfo, &smTransCommand);
	}
#endif
	return TRUE;
}

#ifdef _W_SERVER

#define	DM_ENCODE_PACKET_SIZE	0x60
#define	DM_ENCODE_PACKET_KEY1	0x13
#define	DM_ENCODE_PACKET_KEY2	0x1F

#define	DM_DECODE_PACKET_SIZE	0x70
#define	DM_DECODE_PACKET_KEY1	0x13
#define	DM_DECODE_PACKET_KEY2	0x1F

#define	PACKET_SAFE_CODE		704
#define	PACKET_SAFE_SHIFT1		2
#define	PACKET_SAFE_SHIFT2		3



#else

#endif

int rsRecordDamageError(User *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{

	if (lpPlayInfo->WarningCount < 20)
	{
		rsSendDataServer(lpPlayInfo, lpTransCommand);
		lpPlayInfo->WarningCount++;
	}
	return TRUE;
}
int	rsRecordCharDamage(User *lpPlayInfo, Unit *lpChar, int Damage)
{
	int cnt;
	int EmptyNum = -1;
	DWORD	dwClanCode;

	if (lpChar->psaSiegeWarDataList)
	{
		if (lpPlayInfo->iClanID && lpPlayInfo->iMapID == MAPID_BlessCastle)
		{
			lpPlayInfo->sBlessCastle_Damage[0] += Damage;

			for (cnt = 0; cnt < ATTACK_DAMAGE_LIST_MAX; cnt++)
			{
				if (lpChar->psaSiegeWarDataList[cnt].iID)
				{
					dwClanCode = GetClanCodeByID(lpChar->psaSiegeWarDataList[cnt].iID);
					if (dwClanCode == lpPlayInfo->iClanID)
					{
						lpChar->psaSiegeWarDataList[cnt].iDamage += Damage;
						lpChar->psaSiegeWarDataList[cnt].iCounter++;
						return TRUE;
					}
				}
				if (EmptyNum < 0 && lpChar->psaSiegeWarDataList[cnt].iID == 0)
					EmptyNum = cnt;
			}
			if (EmptyNum >= 0)
			{
				lpChar->psaSiegeWarDataList[EmptyNum].iID = lpPlayInfo->sCharacterData.iClanID;
				lpChar->psaSiegeWarDataList[EmptyNum].iDamage = Damage;
				lpChar->psaSiegeWarDataList[EmptyNum].iCounter++;

				return TRUE;
			}
		}
		return TRUE;
	}

	if (!lpChar->psaDamageUsersData)
		return FALSE;

	if (lpChar->sCharacterData.iMonsterEffectID == snCHAR_SOUND_CASTLE_TOWER_B)
	{
		if (lpPlayInfo->iClanID && lpPlayInfo->iMapID == MAPID_BlessCastle)
		{
			lpPlayInfo->sBlessCastle_Damage[0] += Damage;

			for (cnt = 0; cnt < ATTACK_DAMAGE_LIST_MAX; cnt++)
			{
				if (lpChar->psaDamageUsersData[cnt].iID)
				{
					dwClanCode = GetClanCodeByID(lpChar->psaDamageUsersData[cnt].iID);
					if (dwClanCode == lpPlayInfo->iClanID)
					{
						lpChar->psaDamageUsersData[cnt].iDamage += Damage;
						lpChar->psaDamageUsersData[cnt].iCounter++;
						return TRUE;
					}
				}
				if (EmptyNum < 0 && lpChar->psaDamageUsersData[cnt].iID == 0)
					EmptyNum = cnt;

			}
			if (EmptyNum >= 0)
			{
				lpChar->psaDamageUsersData[EmptyNum].iID = lpPlayInfo->sCharacterData.iClanID;
				lpChar->psaDamageUsersData[EmptyNum].iDamage = Damage;
				lpChar->psaDamageUsersData[EmptyNum].iCounter++;

				return TRUE;
			}
		}
	}
	else
	{
		for (cnt = 0; cnt < ATTACK_DAMAGE_LIST_MAX; cnt++)
		{
			if (lpChar->psaDamageUsersData[cnt].iID == lpPlayInfo->iID)
			{
				lpChar->psaDamageUsersData[cnt].iDamage += Damage;
				lpChar->psaDamageUsersData[cnt].iCounter++;
				return TRUE;
			}
			if (EmptyNum < 0 && lpChar->psaDamageUsersData[cnt].iID == 0)
				EmptyNum = cnt;
		}

		if (EmptyNum >= 0)
		{
			lpChar->psaDamageUsersData[EmptyNum].iID = lpPlayInfo->iID;
			lpChar->psaDamageUsersData[EmptyNum].iDamage = Damage;
			lpChar->psaDamageUsersData[EmptyNum].iCounter++;

			return TRUE;
		}
	}

	return FALSE;
}
int	rsRecord_PKDamage(User *lpPlayInfo, User *lpPlayInfo2, int Damage)
{
	int cnt;
	AttackDamageData *lpAttackDamageList = 0;
	DWORD dwClanCode;
	int EmptyNum = -1;

	BlessCastleStatusData * psBC = SERVERBLESSCASTLE->GetBlessCastleStatusData();

	if (!lpPlayInfo2->iClanID || lpPlayInfo2->iClanID == lpPlayInfo->iClanID)
	{
		if (lpPlayInfo2->iClanID != psBC->iClanID && lpPlayInfo->iClanID != psBC->iClanID)
			return FALSE;
	}
	if (psBC->psaDamageData)
		lpAttackDamageList = psBC->psaDamageData;
	else if (psBC->pcUnitDataTower)
	{
		if (psBC->pcUnitDataTower->bActive &&
			psBC->pcUnitDataTower->sCharacterData.iMonsterEffectID == snCHAR_SOUND_CASTLE_TOWER_B &&
			psBC->pcUnitDataTower->sCharacterData.sHP.sMin > 0)

			lpAttackDamageList = psBC->pcUnitDataTower->psaDamageUsersData;
	}

	if (!lpAttackDamageList)
		return FALSE;

	Damage -= lpPlayInfo->sCharacterData.iAbsorbRating;
	Damage /= PK_SCORE_DIVIDE;
	if (Damage <= 0)
		Damage = 1;

	lpPlayInfo->sBlessCastle_Damage[0] += Damage;

	if (lpPlayInfo->iClanID && lpPlayInfo->iMapID == MAPID_BlessCastle)
	{
		for (cnt = 0; cnt < ATTACK_DAMAGE_LIST_MAX; cnt++)
		{
			if (lpAttackDamageList[cnt].iID)
			{
				dwClanCode = GetClanCodeByID(lpAttackDamageList[cnt].iID);
				if (dwClanCode == lpPlayInfo->iClanID)
				{
					lpAttackDamageList[cnt].iDamage += Damage;
					lpAttackDamageList[cnt].iCounter++;
					return TRUE;
				}
			}
			if (EmptyNum < 0 && lpAttackDamageList[cnt].iID == 0)
				EmptyNum = cnt;
		}
		if (EmptyNum >= 0)
		{
			lpAttackDamageList[EmptyNum].iID = lpPlayInfo->sCharacterData.iClanID;
			lpAttackDamageList[EmptyNum].iDamage = Damage;
			lpAttackDamageList[EmptyNum].iCounter++;

			return TRUE;
		}
	}

	return TRUE;
}