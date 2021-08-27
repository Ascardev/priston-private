#include "StdAfx.h"
#include "smwsock.h"

#include "character.h"
#include "srcsound\\dxwav.h"
#include "particle.h"
#include "fileread.h"
#include "playmain.h"
#include "drawsub.h"
#include "netplay.h"

#include "effectsnd.h"
#include "playsub.h"
#include "skillsub.h"
#include "damage.h"
#include "areaserver.h"


TRANS_SKIL_ATTACKDATA2	*lpTransSkill_AttackData = 0;
Unit	*lpSelected_Char[SKIL_ATTACK_CHAR_MAX];
int	dmSelected_CharCnt;
int	dmUseAccuracy;
DWORD	dmAttackCount = 0;

//¹üÀ§ °ø°Ý Ã½Å©¼¶
DWORD	dm_GetRangeDamgeChkSum( TRANS_SKIL_ATTACKDATA2 *lpTransSkilAttackData2 )
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

//¹üÀ§ °ø°Ý Ã½Å©¼¶
DWORD	dm_GetDamgeChkSum( TRANS_ATTACKDATA2 *lpTransAttackData2 )
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

//ÄÚ¸Çµå Ã½Å©¼¶
DWORD	dm_GetCommandChkSum( smTRANS_COMMAND *lpTransCommand , DWORD dwObjectSerial )
{
	DWORD	dwChkSum;

	dwChkSum = lpTransCommand->code&0x037C70FF;
	dwChkSum += dwObjectSerial<<5;
	dwChkSum ^= lpTransCommand->WParam ^ lpTransCommand->SParam;
	dwChkSum ^= lpTransCommand->code<<2;
	dwChkSum ^= lpTransCommand->LParam ^ lpTransCommand->EParam;
	dwChkSum ^= 0x009821CC;

	return dwChkSum;
}

//S2C °ø°Ý Ã½Å©¼¶
DWORD	dm_GetDamgeChkSum_S2V( TRANS_ATTACKDATA *lpTransAttackData )
{
	DWORD	dwChkSum;

	dwChkSum = lpTransAttackData->code;
	dwChkSum += lpTransAttackData->x^lpTransAttackData->y^lpTransAttackData->z;
	dwChkSum ^= lpTransAttackData->AttackState+lpTransAttackData->AttackSize;
	dwChkSum ^= lpTransAttackData->Power<<5;
	dwChkSum ^= lpTransAttackData->dwChkSum;
	dwChkSum ^= ((DWORD *)lpTransAttackData->sRating)[0];
	dwChkSum ^= 0x80516809;

	return dwChkSum;
}

//»ðÊôÐÔÉËº¦ HPÏÔÊ¾
int dm_OpenFireAttack(Unit *lpChar,DWORD SkillCode)
{
	lpChar->dwLastRecvAttackTime = dwPlayTime;

	if (lpChar->sCharacterData.iType == CHARACTERTYPE_Monster && lpChar->sCharacterData.sHP.sMin > 0)
	{
		lpChar->EnableStateBar = TRUE;
		return TRUE;
	}
	return FALSE;
}

//»ðÊôÐÔ·¶Î§ÉËº¦
int dm_OpenFireAttackRange(DWORD dwSkillCode)
{
	DWORD SkillCode;
	int cnt;
	int OpenCount=0;
	Unit *lpChar;

	SkillCode = dwSkillCode&0xFF;

	if (lpCurPlayer->sCharacterData.iClass == CHARACTERCLASS_Fighter && SkillCode == SKILL_PLAY_ROAR)
		return FALSE;

	for(cnt=0;cnt<dmSelected_CharCnt;cnt++)
	{
		lpChar = lpSelected_Char[cnt];
		if (lpChar)
		{
			lpChar->dwLastRecvAttackTime = dwPlayTime;
			if (lpChar->sCharacterData.iType == CHARACTERTYPE_Monster && lpChar->sCharacterData.sHP.sMax && lpChar->sCharacterData.sHP.sMin == lpChar->sCharacterData.sHP.sMax)
			{
				lpChar->EnableStateBar = TRUE;
				OpenCount++;
				AddAttMonsterCode(lpChar->sCharacterData.iStatPoints);
			}
		}
	}
	return OpenCount;
}


//»ó´ë Ä³¸¯ÅÍ¿¡ °ø°Ý °¡ÇÔ 
int dm_SendTransDamage(Unit *lpChar , int PowParam1, int PowParam2, int AttackState, int Resistance, DWORD dwSkillCode , int UseAccuracy)
{
	TRANS_ATTACKDATA2	TransAttackData;
	int dmg;
	int rnd;

	if ((abs((int)(dwPlayTime-dwLastMouseMoveTime))>1024*60*3 || abs((int)(dwPlayTime-dwLastCharMoveTime))>1024*60*3 || abs((int)(dwFuncChkTime-dwPlayTime))>14*60*1024 ) || RestartPlayCount!=0)
		return FALSE;

	dmAttackCount++;

	ZeroMemory( &TransAttackData , sizeof(TRANS_ATTACKDATA2) );

	if ( UseAccuracy )
	{
		int	temp , accuracy , pow;

		switch( lpChar->sCharacterData.iType )
		{
			case CHARACTERTYPE_Monster:
				
				dwBattleTime = dwPlayTime;

				temp = lpCurPlayer->sCharacterData.iAttackRange;
				
				if ( lpCurPlayer->HoSkillCode )
				{
					switch( lpCurPlayer->HoSkillCode )
					{
						case SKILL_SCOUT_HAWK:
							pow = GetSkillPower(lpCurPlayer, lpChar, 0, 0, 0);
							if ( pow ) 
								lpCurPlayer->sCharacterData.iAttackRange += (lpCurPlayer->sCharacterData.iAttackRating*pow)/100;
							break;				
					}
				}

				accuracy = sinGetAccuracy( lpChar->sCharacterData.iLevel, lpChar->sCharacterData.iDefenseRating);
				lpCurPlayer->sCharacterData.iAttackRange = temp;

				rnd = rand()%100;

				if ( rnd>accuracy )
					return FALSE;
				break;

			case CHARACTERTYPE_NPC:
				if ( MouseItem.bValid)
					return FALSE;

				AttackState = Resistance;
				Resistance = 0;
				break;
		}
	}

	AddAttMonsterCode( lpChar->sCharacterData.iStatPoints);

	TransAttackData.code = smTRANSCODE_ATTACK_DAMAGE;
	TransAttackData.size = sizeof(TRANS_ATTACKDATA2);

	TransAttackData.x = lpChar->pX;
	TransAttackData.y = lpChar->pY;
	TransAttackData.z = lpChar->pZ;

	TransAttackData.Power[0] = lpCurPlayer->sCharacterData.iMinDamage;
	TransAttackData.Power[1] = lpCurPlayer->sCharacterData.iMaxDamage;

	if ( PowParam1 || PowParam2 )
	{
		TransAttackData.Power2[0] = PowParam1;
		TransAttackData.Power2[1] = PowParam2;
	}
	else 
	{
		if ( !dwSkillCode )
		{
			TransAttackData.Power2[0] = TransAttackData.Power[0]-cInvenTory.InvenItem[ sInven[0].ItemIndex-1 ].sItem.sDamage.sMin;
			TransAttackData.Power2[1] = TransAttackData.Power[1]-cInvenTory.InvenItem[ sInven[0].ItemIndex-1 ].sItem.sDamage.sMax;
		}
	}

	if ( ((lpCurPlayer->dwActionItemCode^sinWM1)&sinITEM_MASK2)!=0 )
		TransAttackData.Critical[0] = lpCurPlayer->sCharacterData.iCritical;

	switch( lpCurPlayer->sCharacterData.iClass)
	{
		case CHARACTERCLASS_Priestess:
		case CHARACTERCLASS_Magician:
		case CHARACTERCLASS_Shaman:
			TransAttackData.Critical[1] = lpCurPlayer->sCharacterData.iSpirit;
			break;

		case CHARACTERCLASS_Mechanician:
		case CHARACTERCLASS_Fighter:
		case CHARACTERCLASS_Pikeman:
		case CHARACTERCLASS_Knight:
		case CHARACTERCLASS_Assassin:
			TransAttackData.Critical[1] = lpCurPlayer->sCharacterData.iStrength;
			break;

		case CHARACTERCLASS_Archer:
		case CHARACTERCLASS_Atalanta:
			TransAttackData.Critical[1] = lpCurPlayer->sCharacterData.iAgility;
			break;
	}

	TransAttackData.AttackState = AttackState;
	TransAttackData.AttackSize  = 48*fONE;

	TransAttackData.MotionCount[0] = lpCurPlayer->MotionEvent;
	TransAttackData.AttackCount = dmAttackCount;
	TransAttackData.dwTime = dwPlayTime;
	TransAttackData.SkillCode = dwSkillCode;

	TransAttackData.dwWeaponCode = lpCurPlayer->dwActionItemCode;

	if ( lpCurPlayer->iLoadedMapIndex>=0 && lpChar->sCharacterData.iType == CHARACTERTYPE_Monster)
		TransAttackData.Area[0] = STAGE_MAP[ lpCurPlayer->iLoadedMapIndex ]->iMapID;
	else
		TransAttackData.Area[0] = -1;

	TransAttackData.dwDestObjectSerial = lpCurPlayer->iID;
	TransAttackData.dwTarObjectSerial = lpChar->iID;
	lpChar->TryAttackCount++;

	TransAttackData.dwChkSum = dm_GetDamgeChkSum(&TransAttackData);

	CheckMaxDamage();

	if (SOCKETG)
	{
		dmg = GetRandomPos( TransAttackData.Power[0] , TransAttackData.Power[1] );

		SENDPACKETG(&TransAttackData);

		dm_OpenFireAttack(lpChar, dwSkillCode);
		return dmg;
	}

	return NULL;
}
int dm_OpenTransRangeDamage()
{
	if ( !lpTransSkill_AttackData ) lpTransSkill_AttackData = new TRANS_SKIL_ATTACKDATA2;

	ZeroMemory( lpTransSkill_AttackData , sizeof(TRANS_SKIL_ATTACKDATA2) );
	dmSelected_CharCnt = 0;

	if ( lpTransSkill_AttackData ) 
		return TRUE;

	return FALSE;
}

int dm_SendTransRangeDamage()
{
	if ( RestartPlayCount!=0 || !lpTransSkill_AttackData)
		return FALSE;

	CheckMaxDamage();

	if (SOCKETG && lpTransSkill_AttackData->TargetCount>0)
	{
		SENDPACKETG(lpTransSkill_AttackData);

		dm_OpenFireAttackRange(lpTransSkill_AttackData->SkillCode);
	}
	ZeroMemory(lpTransSkill_AttackData,sizeof(TRANS_SKIL_ATTACKDATA2));

	DELET(lpTransSkill_AttackData);
	return TRUE;
}

// ¹¥»÷·¶Î§
int dm_SelectRange(int x,int y,int z,int range,int UseAttackRating,int SelCount)
{
	int cnt;
	int	dRange;
	int dx,dy,dz,dist;
	Unit	*lpChar;
	int Attack;
	int accuracy;
	int ChkCount = 0;

	dm_OpenTransRangeDamage();
	dmSelected_CharCnt = 0;
	dmUseAccuracy = UseAttackRating;

	dRange = range*range;

	for(cnt=0;cnt< MAX_UNITS;cnt++)
	{
		if (lpTransSkill_AttackData->TargetCount >= SKIL_ATTACK_CHAR_MAX - 4) 
			break;
		if (chrOtherPlayer[cnt].bActive && chrOtherPlayer[cnt].sCharacterData.iType == CHARACTERTYPE_Monster && chrOtherPlayer[cnt].sCharacterData.iMonsterType !=MONSTERTYPE_Friendly && chrOtherPlayer[cnt].sCharacterData.sHP.sMin >0)
		{
			lpChar = &chrOtherPlayer[cnt];

			dx = (x-lpChar->pX)>>FLOATNS;
			dy = (y-lpChar->pY)>>FLOATNS;
			dz = (z-lpChar->pZ)>>FLOATNS;
			dist = dx*dx+dy*dy+dz*dz;

			if (dist<dRange && abs(dy)<65)
			{
				if (!SelCount || SelCount>ChkCount)
				{
					Attack = TRUE;

					if (UseAttackRating)
					{
						accuracy = sinGetAccuracy( chrOtherPlayer[cnt].sCharacterData.iLevel, chrOtherPlayer[cnt].sCharacterData.iDefenseRating);

						if ((rand()%100)>accuracy) 
							Attack = FALSE;
					}

					if (Attack)
					{	
						lpTransSkill_AttackData->dwTarObjectSerial[lpTransSkill_AttackData->TargetCount++] = chrOtherPlayer[cnt].iID;
						lpSelected_Char[dmSelected_CharCnt++] = &chrOtherPlayer[cnt];
					}
				}

				ChkCount++;
			}
		}
	}

	return dmSelected_CharCnt;
}
int dm_SelectRange( int x, int y, int z , int range , int UseAttackRating )
{
	return dm_SelectRange( x,y,z, range, UseAttackRating , 0 );
}
int dm_SelectRangeBox(Unit *lpCurChar , RECT *lpRect , int UseAttackRating )
{
	int cnt;
	int dx,dy,dz;
	int Attack,accuracy;
	Unit	*lpChar;

	dm_OpenTransRangeDamage();
	dmSelected_CharCnt = 0;
	dmUseAccuracy = UseAttackRating;

	for( cnt=0;cnt< MAX_UNITS;cnt++)
	{
		if (lpTransSkill_AttackData->TargetCount >= SKIL_ATTACK_CHAR_MAX-4)
			break;
		if (chrOtherPlayer[cnt].bActive && chrOtherPlayer[cnt].sCharacterData.iType == CHARACTERTYPE_Monster && chrOtherPlayer[cnt].sCharacterData.sHP.sMin >0 && chrOtherPlayer[cnt].sCharacterData.iMonsterType != MONSTERTYPE_Friendly)
		{
			lpChar = &chrOtherPlayer[cnt];

			dx = (lpChar->pX-lpCurChar->pX)>>FLOATNS;
			dy = (lpChar->pY-lpCurChar->pY)>>FLOATNS;
			dz = (lpChar->pZ-lpCurChar->pZ)>>FLOATNS;

			auto sPosition = GetMoveLocation(dx,dy,dz,0,(-lpCurChar->Angle.y)&ANGCLIP,0);

			if (sPosition.iX > lpRect->left && sPosition.iX < lpRect->right && sPosition.iZ > lpRect->top && sPosition.iZ < lpRect->bottom && abs(dy)<256)
			{
				Attack = TRUE;

				if (UseAttackRating)
				{
					accuracy = sinGetAccuracy(chrOtherPlayer[cnt].sCharacterData.iLevel, chrOtherPlayer[cnt].sCharacterData.iDefenseRating);
					if ((rand()%100)>accuracy) 
						Attack = FALSE;
				}

				if (Attack)
				{
					lpTransSkill_AttackData->dwTarObjectSerial[lpTransSkill_AttackData->TargetCount++] = chrOtherPlayer[cnt].iID;
					lpSelected_Char[dmSelected_CharCnt++] = &chrOtherPlayer[cnt];
				}
			}
		}
	}

	return dmSelected_CharCnt;
}
int dm_SelectDamageCount(Unit *lpCurChar , int SelCount , int Size )
{
	int cnt;
	int dx,dy,dz,dist;
	int cCount;
	Unit	*lpChar;
	int dSize;

	dm_OpenTransRangeDamage();
	dmSelected_CharCnt = 0;
	dmUseAccuracy = 0;

	if (lpCurChar!=lpCurPlayer)
		return FALSE;

	dSize = Size*Size;

	for(cnt=0;cnt< MAX_UNITS;cnt++)
	{
		if (lpTransSkill_AttackData->TargetCount>=SKIL_ATTACK_CHAR_MAX-4)
			break;

		cCount = (DivineLightning_FindCount+cnt)&OTHER_PLAYER_MASK;

		if (chrOtherPlayer[cCount].bActive && chrOtherPlayer[cCount].iID && lpCurChar!=&chrOtherPlayer[cCount] && chrOtherPlayer[cCount].sCharacterData.iType == CHARACTERTYPE_Monster && chrOtherPlayer[cCount].sCharacterData.iMonsterType != MONSTERTYPE_Friendly && chrOtherPlayer[cCount].sCharacterData.sHP.sMin >0)
		{
			lpChar = &chrOtherPlayer[cCount];

			dx = (lpChar->pX-lpCurChar->pX)>>FLOATNS;
			dy = (lpChar->pY-lpCurChar->pY)>>FLOATNS;
			dz = (lpChar->pZ-lpCurChar->pZ)>>FLOATNS;

			dist = dx*dx+dy*dy+dz*dz;

			if (dist<dSize && abs(dy)<65)
			{
				lpTransSkill_AttackData->dwTarObjectSerial[lpTransSkill_AttackData->TargetCount++] = lpChar->iID;

				lpSelected_Char[dmSelected_CharCnt] = lpChar;
				dwSkill_DivineLightning_Target[dmSelected_CharCnt] = lpChar->iID;
				dmSelected_CharCnt++;

				if (dmSelected_CharCnt>=SelCount)
				{
					DivineLightning_FindCount = cCount;
					break;
				}
			}
		}
	}
	DivineLightning_Target_Count = dmSelected_CharCnt;

	return dmSelected_CharCnt;
}

//¹üÀ§Çü °ø°Ý ¹üÀ§ ¼±Á¤ (Ã¼ÀÎ¶óÀÌÆ®´×)
int dm_SelectDamageCount(Unit *lpCurChar , Unit *lpTragetChar, int SelCount , int Size )
{
	int cnt;
	int dx,dy,dz,dist;
	int cCount;
	Unit	*lpChar;
	int dSize;

	dm_OpenTransRangeDamage();
	dmSelected_CharCnt = 0;
	dmUseAccuracy = 0;

	if (lpCurChar!=lpCurPlayer)
		return FALSE;

	dSize = Size*Size;

	lpSelected_Char[dmSelected_CharCnt] = lpTragetChar;
	dwSkill_DivineLightning_Target[dmSelected_CharCnt] = lpTragetChar->iID;
	lpTransSkill_AttackData->dwTarObjectSerial[lpTransSkill_AttackData->TargetCount++] = lpTragetChar->iID;
	dmSelected_CharCnt++;

	for(cnt=0;cnt< MAX_UNITS;cnt++)
	{
		if (lpTransSkill_AttackData->TargetCount>=SKIL_ATTACK_CHAR_MAX-4)
			break;

		cCount = (DivineLightning_FindCount+cnt)&OTHER_PLAYER_MASK;

		if (chrOtherPlayer[cCount].bActive && chrOtherPlayer[cCount].iID && lpTragetChar!=&chrOtherPlayer[cCount] && chrOtherPlayer[cCount].sCharacterData.iType == CHARACTERTYPE_Monster && chrOtherPlayer[cCount].sCharacterData.iMonsterType != MONSTERTYPE_Friendly && chrOtherPlayer[cCount].sCharacterData.sHP.sMin >0)
		{
			lpChar = &chrOtherPlayer[cCount];

			dx = (lpChar->pX-lpTragetChar->pX)>>FLOATNS;
			dy = (lpChar->pY-lpTragetChar->pY)>>FLOATNS;
			dz = (lpChar->pZ-lpTragetChar->pZ)>>FLOATNS;

			dist = dx*dx+dy*dy+dz*dz;

			if (dist<dSize && abs(dy)<70)
			{
				lpTransSkill_AttackData->dwTarObjectSerial[lpTransSkill_AttackData->TargetCount++] = lpChar->iID;

				lpSelected_Char[dmSelected_CharCnt] = &chrOtherPlayer[cCount];
				dwSkill_DivineLightning_Target[dmSelected_CharCnt] = lpChar->iID;
				dmSelected_CharCnt++;

				if (dmSelected_CharCnt>=SelCount)
				{
					DivineLightning_FindCount = cCount;
					break;
				}
			}
		}
	}
	DivineLightning_Target_Count = dmSelected_CharCnt;

	return dmSelected_CharCnt;
}


//¹üÀ§Çü °ø°Ý ¹üÀ§ ¼±Á¤ (Ã¼ÀÎ¶óÀÌÆ®´×)
int dm_SelectDamageChainCount(Unit *lpCurChar , Unit *lpTragetChar, int SelCount , int Size )
{
	int cnt,cnt2,cnt3;
	int dx,dy,dz,dist;
	int cCount;
	Unit	*lpChar;
	Unit	*lpLinkChar;
	int dSize;
	int minDist;
	Unit *lpMinChar;

	dm_OpenTransRangeDamage();
	dmSelected_CharCnt = 0;
	dmUseAccuracy = 0;

	dSize = Size*Size;

	lpSelected_Char[dmSelected_CharCnt] = lpTragetChar;
	dwSkill_DivineLightning_Target[dmSelected_CharCnt] = lpTragetChar->iID;
	lpTransSkill_AttackData->dwTarObjectSerial[lpTransSkill_AttackData->TargetCount++] = lpTragetChar->iID;
	dmSelected_CharCnt++;

	lpLinkChar = lpTragetChar;

	for(cnt2=1;cnt2<SelCount;cnt2++) 
	{
		minDist = dSize;
		lpMinChar = 0;

		if (lpTransSkill_AttackData->TargetCount>=SKIL_ATTACK_CHAR_MAX-4)
			break;

		for(cnt=0;cnt< MAX_UNITS;cnt++)
		{
			cCount = cnt;

			if (chrOtherPlayer[cCount].bActive && chrOtherPlayer[cCount].iID && lpLinkChar!=&chrOtherPlayer[cCount] && chrOtherPlayer[cCount].sCharacterData.iType == CHARACTERTYPE_Monster && chrOtherPlayer[cCount].sCharacterData.iMonsterType != MONSTERTYPE_Friendly && chrOtherPlayer[cCount].sCharacterData.sHP.sMin >0 && lpCurChar!=&chrOtherPlayer[cCount])
			{
				lpChar = &chrOtherPlayer[cCount];

				for(cnt3=0;cnt3<dmSelected_CharCnt;cnt3++) 
				{
					if ( lpSelected_Char[cnt3]==lpChar ) 
					{ 
						lpChar = 0;
						break;
					}
				}

				if (lpChar) 
				{
					dx = (lpChar->pX-lpLinkChar->pX)>>FLOATNS;
					dy = (lpChar->pY-lpLinkChar->pY)>>FLOATNS;
					dz = (lpChar->pZ-lpLinkChar->pZ)>>FLOATNS;

					dist = dx*dx+dz*dz;

					if (dist<minDist && abs(dy)<70)
					{
						lpMinChar = lpChar;
						minDist = dist;
					}
				}
			}
		}
		if (lpMinChar) 
		{
			lpTransSkill_AttackData->dwTarObjectSerial[lpTransSkill_AttackData->TargetCount++] = lpMinChar->iID;

			lpSelected_Char[dmSelected_CharCnt] = lpMinChar;
			dwSkill_DivineLightning_Target[dmSelected_CharCnt] = lpMinChar->iID;
			dmSelected_CharCnt++;

			lpLinkChar = lpMinChar;
		}
	}

	DivineLightning_Target_Count = dmSelected_CharCnt;

	return dmSelected_CharCnt;
}


int dm_AddRangeDamage(Unit *lpChar)
{
	int cnt;

	if (lpTransSkill_AttackData->TargetCount>=SKIL_ATTACK_CHAR_MAX - 4 || !lpChar) 
		return FALSE;

	for(cnt=0;cnt<lpTransSkill_AttackData->TargetCount;cnt++) 
	{
		if (lpTransSkill_AttackData->dwTarObjectSerial[cnt]==lpChar->iID)
			return dmSelected_CharCnt;
	}

	lpTransSkill_AttackData->dwTarObjectSerial[lpTransSkill_AttackData->TargetCount++] = lpChar->iID;
	lpSelected_Char[dmSelected_CharCnt++] = lpChar;

	return dmSelected_CharCnt;
}

//·¢ËÍ·¶Î§¹¥»÷ÉËº¦
int dm_SendRangeDamage(int x, int y, int z, Unit *lpMainTraget ,int PowParam1, int PowParam2, int AttackState , int Registance ,DWORD dwSkillCode)
{
	int cnt;

	if (!lpTransSkill_AttackData)
		return FALSE;
	if (!lpTransSkill_AttackData->TargetCount && !lpMainTraget) 
		return FALSE;

	dmAttackCount++;

	lpTransSkill_AttackData->code = smTRANSCODE_RANGE_DAMAGE;
	lpTransSkill_AttackData->size = (sizeof(TRANS_SKIL_ATTACKDATA2)-sizeof(DWORD)*SKIL_ATTACK_CHAR_MAX);
	lpTransSkill_AttackData->size += sizeof(DWORD)*lpTransSkill_AttackData->TargetCount+16;

	lpTransSkill_AttackData->x = x;
	lpTransSkill_AttackData->y = y;
	lpTransSkill_AttackData->z = z;
	lpTransSkill_AttackData->AttackCount = dmAttackCount;
	lpTransSkill_AttackData->dwTime = dwPlayTime;
	lpTransSkill_AttackData->AttackState = AttackState;
	if ( lpMainTraget )
	{
		if ( dmUseAccuracy )
		{
			for(cnt=0;cnt<lpTransSkill_AttackData->TargetCount;cnt++)
			{
				if (lpTransSkill_AttackData->dwTarObjectSerial[cnt]==lpMainTraget->iID)
				{
					lpTransSkill_AttackData->dwMainTargetObject = lpMainTraget->iID;
					break;
				}
			}
		}
		else
			lpTransSkill_AttackData->dwMainTargetObject = lpMainTraget->iID;

		lpMainTraget->TryAttackCount++;
	}
	lpTransSkill_AttackData->SkillCode			= dwSkillCode;
	lpTransSkill_AttackData->Critical[0]		= lpCurPlayer->sCharacterData.iCritical;
	lpTransSkill_AttackData->dwDestObjectSerial = lpCurPlayer->iID;
	lpTransSkill_AttackData->Power[0]			= lpCurPlayer->sCharacterData.iMinDamage;
	lpTransSkill_AttackData->Power[1]			= lpCurPlayer->sCharacterData.iMaxDamage;
	lpTransSkill_AttackData->Power2[0]			= PowParam1;
	lpTransSkill_AttackData->Power2[1]			= PowParam2;

	switch( lpCurPlayer->sCharacterData.iClass)
	{
		case CHARACTERCLASS_Priestess:
		case CHARACTERCLASS_Magician:
		case CHARACTERCLASS_Shaman:
			lpTransSkill_AttackData->Critical[1] = lpCurPlayer->sCharacterData.iSpirit;
			break;

		case CHARACTERCLASS_Mechanician:
		case CHARACTERCLASS_Fighter:
		case CHARACTERCLASS_Pikeman:
		case CHARACTERCLASS_Knight:
		case CHARACTERCLASS_Assassin:
			lpTransSkill_AttackData->Critical[1] = lpCurPlayer->sCharacterData.iStrength;
			break;

		case CHARACTERCLASS_Archer:
		case CHARACTERCLASS_Atalanta:
			lpTransSkill_AttackData->Critical[1] = lpCurPlayer->sCharacterData.iAgility;
			break;
	}

	lpTransSkill_AttackData->AttackSize = 240;

	lpTransSkill_AttackData->dwWeaponCode = lpCurPlayer->dwActionItemCode;

	if ( lpCurPlayer->iLoadedMapIndex>=0 )
		lpTransSkill_AttackData->Area[0] = STAGE_MAP[ lpCurPlayer->iLoadedMapIndex ]->iMapID;

	lpTransSkill_AttackData->dwChkSum = dm_GetRangeDamgeChkSum(lpTransSkill_AttackData);

	return dm_SendTransRangeDamage();
}

WORD	wLimitDamage[8] = { 0,0,0,0, 0,0,0,0 };

//µ¥¹ÌÁö ¾ÏÈ£È­ ¸ðµâ ¼ö½Å
int RecvDamagePacketModule( TRANS_FUNC_MEMORY *lpTransFuncModule )
{
	ZeroMemory( wLimitDamage , sizeof(WORD)*8 );

	return TRUE;
}

//µ¥¹ÌÁö ¾ÏÈ£È­ ¸ðµâ ¼ö½Å
int RecvDamagePacketModule2( TRANS_FUNC_MEMORY *lpTransFuncModule )
{
	return TRUE;
}

//ÆÐÅ¶ µ¿Àû ¾ÏÈ£È­ ¸ðµâ ¼ö½Å
int RecvDynPacketModule( TRANS_FUNC_MEMORY *lpTransFuncModule )
{
	char *lpBuff;

	if ( !fnEncodePacket )
		lpBuff = new char[lpTransFuncModule->size];
	else
		lpBuff = (char *)fnEncodePacket;

	memcpy( lpBuff , lpTransFuncModule->szData , lpTransFuncModule->Param[0] );
	fnEncodePacket = (LPFN_EncodePacket)(lpBuff+lpTransFuncModule->Param[1]);
	fnDecodePacket = (LPFN_DecodePacket)(lpBuff+lpTransFuncModule->Param[2]);

	return TRUE;
}


int CheckMaxDamage()
{
	if ( (wLimitDamage[3]^wLimitDamage[5])==0 && lpCurPlayer->sCharacterData.iClass>0 )
		cInvenTory.CheckDamage();

	return TRUE;
}

int SetMaxDamage(CharacterData *lpCharInfo )
{
	WORD	wDamage[8];
	WORD	wSum;

	wDamage[0] = wLimitDamage[0] ^ wLimitDamage[5];
	wDamage[1] = wLimitDamage[1] ^ wLimitDamage[5];
	wDamage[2] = wLimitDamage[2] ^ wLimitDamage[5];
	wDamage[3] = wLimitDamage[3] ^ wLimitDamage[5];
	wDamage[4] = wLimitDamage[4] ^ wLimitDamage[5];

	wSum = wDamage[0]*3+wDamage[1]*5+wDamage[2]*7+wDamage[3]*9;

	if ( wSum!=wDamage[4] || lpCurPlayer->sCharacterData.iClass==0 ) return FALSE;

	lpCharInfo->iMinDamage = wDamage[0];
	lpCharInfo->iMaxDamage = wDamage[1];
	lpCharInfo->iCritical = wDamage[2];

	return TRUE;
}

int	SendMaxDamageToServer( WORD MinDamage , WORD MaxDamage , WORD Critical )
{
	WORD	wTime = (WORD)dwPlayTime;

	WORD	wDamage[8];
	WORD	wSum;
	smTRANS_COMMAND	smTransCommand;

	wDamage[0] = wLimitDamage[0] ^ wLimitDamage[5];
	wDamage[1] = wLimitDamage[1] ^ wLimitDamage[5];
	wDamage[2] = wLimitDamage[2] ^ wLimitDamage[5];
	wDamage[3] = wLimitDamage[3] ^ wLimitDamage[5];
	wDamage[4] = wLimitDamage[4] ^ wLimitDamage[5];

	wSum = wDamage[0]*3+wDamage[1]*5+wDamage[2]*7+wDamage[3]*9;
	if (wSum!=wDamage[4] || lpCurPlayer->sCharacterData.iClass==0)
		return FALSE;
	if (wDamage[0]<MinDamage || wDamage[1]<MaxDamage || wDamage[2]<Critical || wDamage[3]==0)
	{
		smTransCommand.code = smTRANSCODE_LIMIT_DAMAGE;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = 0;
		smTransCommand.LParam = MinDamage;
		smTransCommand.SParam = MaxDamage;
		smTransCommand.EParam = Critical;
		smTransCommand.WParam = dm_GetCommandChkSum(&smTransCommand , lpCurPlayer->iID);

		SENDPACKETG(&smTransCommand);

		wLimitDamage[3] = wDamage[3] + 1;

		wLimitDamage[0] = MinDamage;
		wLimitDamage[1] = MaxDamage;
		wLimitDamage[2] = Critical;
		wLimitDamage[4] = wLimitDamage[0]*3+wLimitDamage[1]*5+wLimitDamage[2]*7+wLimitDamage[3]*9;
		wLimitDamage[5] = wTime;

		wLimitDamage[0] ^= wLimitDamage[5];
		wLimitDamage[1] ^= wLimitDamage[5];
		wLimitDamage[2] ^= wLimitDamage[5];
		wLimitDamage[3] ^= wLimitDamage[5];
		wLimitDamage[4] ^= wLimitDamage[5];
	}

	return TRUE;
}

DWORD dwSpeedProtectCode = 0;
DWORD dwSkillProtectCode = 0;

DWORD GetSpeedProtectCode(Unit *lpChar )
{
	DWORD	dwCode;

	dwCode = lpChar->iFrame;
	dwCode += lpChar->FrameStep<<2;
	dwCode += lpChar->MoveSpeed<<5;
	dwCode += lpChar->AttackSpeed<<7;
	dwCode = ( dwCode&0xFFFFEFFF );

	if ( (dwSpeedProtectCode&0x1000)==0 ) return dwCode;

	return NULL;
}

DWORD GetSkillProtectCode(Unit *lpChar )
{
	DWORD	dwCode;

	dwCode = lpChar->AttackSkil;
	dwCode += lpChar->iFrame <<4;
	dwCode = ( dwCode&0xFFFFEFFF );

	if ( (dwSkillProtectCode&0x1000)==0 ) return dwCode;

	return NULL;
}


//¼Óµµ º¯¼ö Lock
int	LockSpeedProtect(Unit *lpChar )
{
	DWORD	dwCode;

	dwCode = GetSpeedProtectCode( lpChar );
	if ( dwCode )
		dwSpeedProtectCode = dwCode;

	dwCode = GetSkillProtectCode( lpChar );
	if ( dwCode )
		dwSkillProtectCode = dwCode;


	return TRUE;
}

//¼Óµµ º¯¼ö UnLock
int UnlockSpeedProtect(Unit *lpChar )
{
	DWORD dwCode;

	smTRANS_COMMAND	smTransCommand;
	ZeroMemory( &smTransCommand , sizeof(smTRANS_COMMAND) );


	dwCode = GetSpeedProtectCode( lpChar );

	if ( dwCode==NULL ) {
		dwSpeedProtectCode++;
		return TRUE;
	}

	if ( dwSpeedProtectCode!=dwCode ) {
		//½ºÇÇµå ÄÚµå ¿À·ù
		smTransCommand.code = TRUE;
		smTransCommand.WParam = 100;
		smTransCommand.LParam = lpChar->FrameStep;
		smTransCommand.SParam = 0;

		dwSpeedProtectCode|=0x1000;
	}

	dwCode = GetSkillProtectCode( lpChar );

	if ( dwCode==NULL ) {
		dwSkillProtectCode++;
		return TRUE;
	}

	if ( dwSkillProtectCode!=dwCode )
	{
		smTransCommand.code = TRUE;
		smTransCommand.WParam = 101;
		smTransCommand.LParam = lpChar->AttackSkil;
		smTransCommand.SParam = 0;

		dwSkillProtectCode|=0x1000;
	}

	if ( smTransCommand.code==TRUE ) 
	{
		smTransCommand.code = smTRANSCODE_WARNING_CLIENT;
		smTransCommand.EParam = 0;
		smTransCommand.EParam = dm_GetCommandChkSum( &smTransCommand , lpCurPlayer->iID);
		smTransCommand.size = sizeof(smTRANS_COMMAND);

		SENDPACKETL(&smTransCommand);
	}

	return TRUE;
}