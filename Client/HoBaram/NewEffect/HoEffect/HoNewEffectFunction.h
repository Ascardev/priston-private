#ifndef _HO_NEW_EFFECT_FUNCTION_H_
#define _HO_NEW_EFFECT_FUNCTION_H_

#include "..\\..\\..\\smwsock.h"
#include "..\\..\\..\\character.h"

void SkillMetalionImpulsionHit(Unit **pChar, int charCount);
void SkillMetalionCompulsion(Unit *pChar);
void SkillMetalionSphereStart(Unit *pChar);
void SkillMetalionSphereEffect(Unit *pChar, float time, float attackTime);
void SkillMetalionSphereDefence(POINT3D *curPos, POINT3D *desPos, bool flag = true);
void SkillMetalionGolem(Unit *pChar);
void SkillMetalionHyperSonic(Unit *pChar);

void SkillWarriorDestroyerBlade(Unit *pChar, float time);
void SkillWarriorDestroyerHit(POINT3D *pos);
void SkillWarriorBetserker(Unit *pChar, float time,int Effect = TRUE);
void SkillBloodyBerserker(Unit *pChar,float time,int Effect = TRUE);
void SkillWarriorCycloneStrikeBlade(Unit *pChar, float time,int Flag = 0);
void SkillFighterDownHit(Unit *pChar,int x,int y,int z);

void SkillLancelotAssassinEye(Unit *pChar, float time);
void SkillLancelotChargingStrike(Unit *pChar);
void SkillLancelotVague(Unit *pChar);

void SkillSagittarionPhoneixShot(Unit *pChar, POINT3D *curPos, POINT3D *desPos);
void SkillSagittarionForceOfNature1(Unit *pChar, float time); //�������� �����°�
void SkillSagittarionForceOfNature2(Unit *pChar, float time); //�����ȳ����� ���� ����Ʈ�� �����°�

void SkillSaintDivinePiercing(Unit *pChar);
void SkillSaintGodBless(Unit *pChar, float time);
void SkillSwordOfUstice(Unit *pChar);

void SkillValhallaHallOfValhalla1(Unit *pChar);
void SkillValhallaXRage(POINT3D *curPos, POINT3D *desPos);
void SkillFrostJavelin(POINT3D *curPos, POINT3D *desPos);
void SkillForstJavelinAttach(Unit *pChar, float time);
void SkillVengeance(POINT3D *curPos, POINT3D *desPos);

void SkillCelestialGlacialSpike(Unit *pChar);
void SkillCelestialRegnerationField(Unit *pChar, float time);
void SkillCelestialMusPel(Unit* pChar, float time, float attackTime,int Kind);
void CelestialChainLighting(Unit **pChar, int count);
void SkillArchMageMeteo(POINT3D *desPos,int SkillCode = 0);
//����ʯ
void SkillIceMeteorite(Unit *pChar,int Level);
void SkillArchMageFireElementalHand(Unit *pChar);
void SkillArchMageFireElementalShot(POINT3D *curPos, POINT3D *desPos);

BOOL GetAssaCodeEffect(Unit *pChar, int code);

// ��öȣ
void Valento_PowerUp(Unit *pChar);
void Valento_Justice(Unit *pChar);

void ParkIncubusSummonerSkill(Unit *pChar);
void DevilBird_Skill(Unit *pChar);
//���Ч��
void ParkWingEffect(Unit *pChar,int iCode);
#endif