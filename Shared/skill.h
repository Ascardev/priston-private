#pragma once

#define MAX_SKILL_POINT_COLUM	20
#define SKILLCONTAINER_LENGTH	0x1FF4
#define MAX_SKILLS				228
#define MAX_MASTERY				1000

// Mesh T1
const int iaMechT11AddedBlockRtg[10] = { 4,5,6,7,8,9,10,11,13,15 };
const int iaMechT11Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const MinMax saMeshT12Damage[10] = { {5,10},{10,20},{15,30},{20,40},{25,50},{30,60},{35,70},{40,80},{45,90},{50,100} };
const int iaMeshT12Area[10] = { 64,68,72,76,80,84,88,92,96,100 };

const int iaMeshT13AddedPoisonResistance[10] = { 5,10,15,20,25,30,35,40,45,50 };

const int iaMeshT14AddedAbsorbRtg[10] = { 4,6,12,14,20,22,28,30,36,38 };
const int iaMeshT14Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };
//T2
const MinMax saMechT21ExtraMaxDmg[10] = { {8,68},{16,76},{24,84},{32,92},{40,100},{48,108},{56,116},{64,124},{72,132},{80,140} };
const int iaMechT21AddedAtkPow[10] = { 8,16,24,32,40,48,56,64,72,80 };
const int iaMechT21AddedAtkRtg[10] = { 60,70,80,90,100,120,140,160,180,200 };
const int iaMechT21Area[10] = { 70,70,70,70,70,70,70,70,70,70 };

const int iaMeshT22MaxDmgBoost[10] = { 7,14,21,28,35,42,49,56,63,70 };
const int iaMeshT22Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaMechT23DmgBoost[10] = { 20,40,60,80,100,120,140,160,180,200 };
const int iaMechT23AddedAtkSpd[10] = { 3,3,3,4,4,4,5,5,5,6 };
const int iaMeshT23Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaMeshT24DamageBoost[10] = { 15,20,25,30,35,40,45,50,55,60 };
const int iaMeshT24Area[10] = { 85,90,95,100,105,110,115,120,125,130 };
//T3
const int iaMeshT31ArmorDefenseRtgBoost[10] = { 8,16,24,32,40,48,56,64,72,80 };
const int iaMeshT31Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaMeshT32DmgBoost[10] = { 25,31,37,43,49,55,61,67,73,79 };
const int iaMeshT32AtkRtgBoost[10] = { 8,16,24,32,40,48,56,64,72,80 };

const int iaMeshT33WeaponDmgBoost[10] = { 4,8,12,16,20,24,28,32,36,40 };

const int iaMeshT34ReflectDmg[10] = { 30,42,54,66,78,90,102,114,126,138 };
const int iaMeshT34AddedDefenseRtg[10] = { 24,48,72,96,120,144,168,192,216,240 };
const int iaMeshT34Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };
//T4
const int iaMeshT41DamgeBoost[10] = { 60,65,70,75,80,85,90,95,100,105 };
const int iaMeshT41Area[10] = { 130,135,140,145,150,155,160,165,170,175 };
const int iaMeshT41NumberofSparks[10] = { 16,17,18,19,20,21,22,23,24,25 };

const int iaMeshT42ExtraAbsorb[10] = { 3,6,9,13,17,21,26,31,36,42 };
const int iaMeshT42Range[10] = { 150,160,170,180,190,200,210,220,230,240 };
const int iaMeshT42Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const MinMax saMeshT43SphereDmg[10] = { {120,140},{140,180},{160,220},{180,260},{200,300},{220,340},{240,380},{260,420},{280,460},{400,500} };
const int iaMeshT43AttackInterval[10] = { 4,4,4,3,3,3,2,2,2,1 };
const int iaMeshT43AttackRange[10] = { 60,70,80,90,100,110,120,130,140,150 };
const int iaMeshT43Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const MinMax saMetalGolemAtkDmg[10] = { {160,160},{180,180},{200,200},{220,220},{240,240},{260,260},{280,280},{300,300},{320,320},{340,340} };
const int iaMetalGolemAttackRating[10] = { 1000,1100,1200,1300,1400,1500,1600,1700,1800,1900 };
const int iaMetalGolemHP[10] = { 14000,16000,1800,20000,22000,24000,26000,28000,30000,32000 };
const int iaMetalGolemDefense[10] = { 1000,1200,1400,1600,1800,2000,2200,2400,2600,2800 };
const int iaMetalGolemDuration[10] = { 300,300,300,300,300,300,300,300,300,300 };
//T5
const int iaMechT51DMGBoost[10] = { 70,80,90,100,110,120,130,140,150,160 };
const int iaMechT51AttackRange[10] = { 80,90,100,110,120,130,140,150,160,170 };
const int iaMechT51MaxHit[10] = { 6,7,8,9,10,11,12,13,14,15 };

const int iaMechT52ATKSpeedBoost[10] = { 3,6,9,11,13,15,16,17,18,19 };
const int iaMechT52Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaMechT53DMGBoost[10] = { 15,30,45,60,75,90,105,120,135,150 };

const MinMax saMechT54DMGBoost[10] = { {4,4},{8,8},{12,12},{16,16},{20,20},{24,24},{28,28},{32,32},{36,36},{40,40} };
const int iaMechT54Defanse[10] = { 220,240,260,280,300,320,340,360,380,400 };
const int iaMechT54Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

//Fighter
//T1
const int iaFighterT11WeaponAttackPower[10] = { 6,10,14,18,21,24,26,28,30,32 };

const int iaFighterT12AddedFireResistance[10] = { 9,17,24,30,35,39,42,44,45,46 };

const int iaFighterT13DamageBoost[10] = { 13,16,19,22,25,28,31,34,37,40 };
const int iaFighterT13NumberHit[10] = { 2,2,2,3,3,3,4,4,4,4 };
const float faFighterT13HPReduction[10] = { 1.0f,1.2f,1.6f,1.8f,2.2f,2.5f,2.7f,3.0f,3.4f,3.7f };

const int iaFighterT14AddedAtkRtg[10] = { 20,40,60,80,100,120,140,160,180,200 };
const int iaFighterT14DamageBoost[10] = { 20,25,29,33,37,41,45,49,52,55 };
//T2
const int iaFighterT21DamageBoost[10] = { 10,15,20,25,30,35,40,45,50,55 };
const int iaFighterT21NumberHit[10] = { 1,1,2,2,2,3,3,3,3,3 };

const int iaFighterT22DamageBoost[10] = { 10,16,22,28,34,40,45,50,55,60 };
const int iaFighterT22CriticalBoost[10] = { 3,7,10,13,16,19,21,24,27,30 };

const int iaFighterT23Area[10] = { 50,60,70,80,90,100,108,116,124,130 };
const int iaFighterT23Duration[10] = { 6,7,8,9,10,11,12,13,14,15 };

const int iaFighterT24DamageBoost[10] = { 14,28,42,56,70,84,98,112,126,140 };
const int iaFighterT24Area[10] = { 120,120,120,120,120,120,120,120,120,120 };
//T3
const int iaFighterT31AddedAtkRtg[10] = { 16,32,48,64,80,96,112,128,144,160 };
const int iaFighterT31Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaFighterT32AtkRtgBoost[10] = { 5,10,15,20,25,30,35,40,45,50 };
const int iaFighterT32DmgBoost[10] = { 60,65,70,75,80,85,90,95,100,105 };

const int iaFighterT33AtkSpeedBoost[10] = { 1,2,3,4,5,7,9,10,12,14 };
const int iaFighterT33Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaFighterT34DemonsDmgBoost[10] = { 60,65,70,75,80,85,90,95,100,105 };
const int iaFighterT34DmgBoost[10] = { 50,55,60,65,70,75,80,85,90,95 };
//T4
const int iaFighterT41DamageBoost[10] = { 25,40,55,70,85,100,115,130,145,160 };
const int iaFighterT41AddCritical[10] = { 10,12,14,16,18,20,22,24,26,28 };

const int iaFighterT42AddedAtkPower[10] = { 60,60,90,90,120,120,150,150,180,180 };
const int iaFighterT42AbsorptionPenalty[10] = { -5,-5,-5,-5,-10,-10,-10,-10,-10,-15 };
const int iaFighterT42Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaFighterT43DamageBoost[10] = { 15,20,25,30,35,40,45,50,55,60 };
const int iaFighterT43MaxHits[10] = { 6,7,8,9,10,11,12,13,14,15 };
const int iaFighterT43Range[10] = { 100,105,110,115,120,125,130,140,145 };

const int iaFighterT44HPInc[10] = { 10,20,30,40,50,60,70,80,90,100 };
//T5
const int iaFighterT51DamageBoost[10] = { 15,30,45,60,75,90,105,120,135,150 };

const int iaFighterT52DMGBoost[10] = { 15,30,45,60,75,90,105,120,135,150 };
const int iaFighterT52Area[10] = { 50,55,60,65,70,80,85,90,100 };

const int iaFighterT53DamageBoost[10] = { 15,25,35,45,55,65,75,85,95,105 };
const int iaFighterT53HitsBoost[10] = { 6,7,8,9,10,11,12,13,14,15 };
const int iaFighterT53ATKArea[10] = { 120,130,140,150,160,170,180,190,200,210 };

const int iaFighterT54AddCritical[10] = { 10,11,12,13,14,15,16,17,18,19 };
const int iaFighterT54Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

//Pikeman
//T1
const MinMax saPikemanT11AttackPower[10] = { {15,25},{20,30},{25,35},{30,40},{35,45},{40,50},{45,55},{50,60},{55,65},{60,70} };
const int iaPikemanT11PushBackRange[10] = { 70,80,90,100,110,120,130,140,150,160 };

const int iaPikemanT12FrostResistanceInc[10] = { 4,6,8,10,12,14,16,18,20,22 };
const int iaPikemanT13AddCriticalDamage[10] = { 2,4,6,8,10,11,12,13,14,15 };

const int iaPikemanT14WPAttackRatingBoost[10] = { 7,14,21,28,35,42,49,56,63,70 };
const int iaPikemanT14DamageBoost[10] = { 10,20,30,40,50,60,70,80,90,100 };
//T2
const int iaPikemanT21FreezeDuration[10] = { 3,4,5,6,7,8,9,10,11,12 };
const MinMax saPikemanT21FreezeAttack[10] = { {30,40},{35,45},{40,50},{45,55},{50,60},{55,65},{60,70},{65,75},{70,80},{75,85} };
const int iaPikemanT21FreezeAttackRange[10] = { 70,73,76,79,82,85,88,91,94,97 };

const int iaPikemanT22DamageBoost[10] = { 25,30,35,40,45,50,55,60,65,70 };
const int iaPikemanT22Range[10] = { 44,48,52,56,60,64,68,72,76,80 };

const int iaPikemanT23WeaponCurrentBlockBoost[10] = { 52,54,56,58,60,62,64,66,68,70 };

const int iaPikemanT24AddSize[10] = { 10,20,30,40,50,60,70,80,90,100 };
const int iaPikemanT24DamageBoost[10] = { 5,10,15,20,25,30,35,40,45,50 };
//T3
const int iaPikemanT31DamageBoost[10] = { 10,20,30,40,50,60,70,80,90,100 };
const int iaPikemanT31NumberSpears[10] = { 3,3,3,4,4,4,5,5,5,6 };
const int iaPikemanT31Duration[10] = { 5,5,5,5,6,6,6,6,7,7 };
const int iaPikemanT31Range[10] = { 90,94,98,102,106,110,114,118,122,126 };

const int iaPikemanT32AfterDamage[10] = { 28,32,36,40,44,48,52,56,60,65 };
const int iaPikemanT32SightDec[10] = { 35,40,45,50,55,60,65,70,75,80 };
const int iaPikemanT32Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaPikemanT33WPCriticalRatingBoost[10] = { 16,18,20,22,24,26,28,30,32,34 };
const int iaPikemanT34DamageBoost[10] = { 65,70,75,80,85,90,95,100,105,110 };
//T4
const int iaPikemanT41AddCriticalDamage[10] = { 4,8,12,16,20,24,28,32,36,40 };
const int iaPikemanT41TargetCriticalDec[10] = { 4,5,6,7,8,9,10,11,12,13 };
const int iaPikemanT41Duration[10] = { 12,13,14,15,16,17,18,19,20,21 };

const int iaPikemanT42DamageBoost[10] = { 20,25,30,35,40,45,50,55,60,65 };
const int iaPikemanT42ChargedDamgeBoost[10] = { 45,60,75,90,105,120,135,150,165,180 };
const int iaPikemanT42RaiseSpeed[10] = { 6,8,10,16,20,24,28,32,36,40 };

const int iaPikemanT43AddEvasion[10] = { 11,12,13,14,15,16,17,18,19,20 };
const int iaPikemanT43Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaPikemanT44DamageBoost[10] = { 40,50,60,70,80,90,100,110,120,130 };
const int iaPikemanT44NumberHits[10] = { 3,3,4,4,5,5,6,6,7,7 };
//T5
const int iaPikemanT51DamageBoost[10] = { 20,40,60,80,100,120,140,160,180,200 };

const int iaPikemanT52DamageBoost[10] = { 15,20,25,30,35,40,45,50,55,60 };
const int iaPikemanT52HitNumber[10] = { 5,5,5,5,6,6,6,6,7,8 };
const int iaPikemanT52ATKArea[10] = { 120,130,140,150,160,170,180,190,200,210 };

const int iaPikemanT53DecAbsorption[10] = { -5,-7,-9,-11,-13,-15,-17,-19,-21,-23 };
const int iaPikemanT53AddAccuracy[10] = { 30,35,40,45,50,55,60,65,70,75 };
const int iaPikemanT53MinAddDamage[10] = { 5,10,15,20,25,30,35,40,45,50 };
const int iaPikemanT53Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaPikemanT54DMGBoost[10] = { 10,30,50,70,90,110,130,150,170,190 };

//Archer
//T1
const int iaArcherT11AddAttackRating[10] = { 10,20,30,40,50,60,70,80,90,100 };
const int iaArcherT11HawkRotation[10] = { 5,6,7,8,9,10,11,12,13,14 };

const int iaArcherT12AddAttackPower[10] = { 12,16,20,24,28,32,36,40,44,48 };

const int iaArcherT13AddAttackSpeed[10] = { 2,2,2,3,3,3,4,4,4,5 };
const int iaArcherT13DamageBoost[10] = { 15,24,32,39,45,50,54,57,59,60 };

const int iaArcherT14AddAttackRating[10] = { 12,14,16,18,20,22,24,26,28,30 };
const int iaArcherT14DamageBoost[10] = { 20,22,24,26,28,30,32,34,36,38 };
//T2
const int iaArcherT21AddAttackRating[10] = { 10,20,30,40,50,60,70,80,90,100 };

const int iaArcherT22StaticDamge[10] = { 16,20,24,28,32,36,40,44,48,52 };
const int iaArcherT22FormulaDamage[10] = { 14,18,22,26,30,34,38,42,46,50 };
const int iaArcherT22Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaArcherT23DamageBoost[10] = { 23,24,26,28,30,32,34,36,38,40 };
const int iaArcherT23Area[10] = { 55,59,63,67,70,73,76,79,82,85 };

const int iaArcherT24AddAttackSpeed[10] = { 1,1,1,2,2,2,3,3,3,4 };
const int iaArcherT24DamageBoost[10] = { 30,35,40,45,50,55,60,65,70,75 };
const int iaArcherT24NumberArrow[10] = { 3,3,3,4,4,4,5,5,5,6 };
//T3
const int iaArcherT31FireDamageStatic[10] = { 20,25,30,35,40,45,50,55,60,65 };
const int iaArcherT31FireDamageCalculated[10] = { 10,20,30,40,50,60,70,80,90,100 };
const int iaArcherT31LightningDamageStatic[10] = { 20,25,30,35,40,45,50,55,60,65 };
const int iaArcherT31LightningDamageCalculated[10] = { 10,20,30,40,50,60,70,80,90,100 };

const int iaArcherT32FalconDamage[10] = { 150,160,165,170,175,180,185,190,195,200 };
const float faArcherT32HPRegen[10] = { 6.0f,7.0f,8.0f,9.0f,10.0f,11.0f,12.0f,13.0f,14.0f,15.0f };
const int iaArcherT32Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaArcherT33DamageBoost[10] = { 4,8,12,16,20,24,28,32,36,40 };
const int iaArcherT33DamageBoostDemon[10] = { 46,52,58,64,70,76,82,88,94,100 };
const int iaArcherT33Area[10] = { 100,100,100,100,100,100,100,100,100,100 };

const int iaArcherT34IncShotRange[10] = { 30,34,38,42,46,50,54,58,62,66 };
const int iaArcherT34DamageBoost[10] = { 7,14,21,28,35,42,49,56,63,70 };

//T4
const MinMax saWolverineAtkDmg[10] = { {120,120},{140,140},{180,180},{200,200},{220,220},{240,240},{260,260},{280,280},{300,300} };
const int iaWolverineAttackRating[10] = { 1000,1100,1200,1300,1400,1500,1600,1700,1800,1900 };
const int iaWolverineHP[10] = { 8000,10000,12000,14000,16000,18000,20000,22000,24000,26000 };
const int iaWolverineDefense[10] = { 2000,2200,2400,2600,2800,3000,3200,3400,3600,3800 };
const int iaWolverineDuration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaArcherT42IncEvasion[10] = { 7,9,11,13,15,17,19,21,23,25 };

const int iaArcherT43ShotRangeInc[10] = { 10,15,20,25,30,35,40,45,50,55 };
const int iaArcherT43DamageBoost[10] = { 45,60,75,90,105,120,135,150,165,180 };
const float faArcherT43ChargeRaiseSpeed[10] = { 9.0f,18.0f,27.0f,36.0f,45.0f,54.0f,63.0f,72.0f,81.0f,90.0f };

const int iaArcherT44AddAttackPower[10] = { 10,20,30,40,50,60,70,80,90,100 };
const int iaArcherT44AddAttackRating[10] = { 20,30,40,50,60,70,80,90,100,110 };
const int iaArcherT44Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };
//T5
const int iaArcherT51DamageBoost[10] = { 70,75,80,85,90,95,100,105,110,115 };
const int iaArcherT51AttackRange[10] = { 140,140,140,140,140,140,140,140,140,140 };

const int iaArcherT52DamageBoost[10] = { 75,80,85,90,95,100,105,110,115,120 };
const int iaArcherT52Rating[10] = { 20,25,30,35,40,45,50,55,60,65 };

const int iaArcherT53DamageBoost[10] = { 70,75,80,85,90,95,100,105,110,115 };
const int iaArcherT53AttackArea[10] = { 95,100,105,110,115,120,125,130,135,140 };

const int iaArcherT54DamageBoost[10] = { 80,85,90,95,100,105,110,115,120,125 };
const int iaArcherT54AttackArea[10] = { 95,100,105,110,115,120,125,130,135,140 };

//Knight
//T1
const int iaKnightT11StaticDamage[10] = { 20,24,28,32,36,40,44,48,52,56 };
const int iaKnightT11DamageBoost[10] = { 2,4,6,8,10,12,14,16,18,20 };
const int iaKnightT11Area[10] = { 60,60,60,60,60,60,60,60,60,60 };

const int iaKnightT12DamageBoostToUndead[10] = { 3,6,9,12,15,18,21,24,27,30 };
const int iaKnightT12Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaKnightT13SPBoost[10] = { 4,8,12,16,20,24,28,32,36,40 };

const int iaKnightT14DemageBoost[10] = { 10,14,18,24,30,36,42,48,54,60 };
const int iaKnightT14AddCritical[10] = { 2,3,3,4,4,4,5,5,5,6 };

//T2
const int iaKnightT21PartyArea[10] = { 350,350,350,350,350,350,350,350,350,350 };
const int iaKnightT21DamageBoostToUndead[10] = { 5,10,15,20,25,30,35,40,45,50 };
const int iaKnightT21Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaKnightT22Area[10] = { 73,76,79,82,85,88,91,94,97,100 };
const int iaKnightT22DamageBoost[10] = { 30,35,40,45,50,55,60,65,70,75 };

const int iaKnightT23DamageBoost[10] = { 22,24,26,28,30,32,34,36,38,40 };
const int iaKnightT23Area[10] = { 40,50,60,70,80,90,100,110,120,130 };
const int iaKnightT23PierceRange[10] = { 110,110,110,110,110,110,110,110,110,110 };

const int iaKnightT24DefenseBoost[10] = { 3,6,9,12,15,18,21,24,27,30 };
const int iaKnightT24Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

//T3
const int iaKnightT31BaseAttackPowerInc[10] = { 11,14,17,20,23,26,29,32,35,38 };

const int iaKnightT32AddBlockRating[10] = { 2,2,3,3,4,4,5,5,6,6 };
const int iaKnightT32ToHPConversion[10] = { 9,18,27,36,45,54,63,72,81,90 };
const int iaKnightT32Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaKnightT33SuccessRate[10] = { 24,32,40,48,56,64,72,80,88,96 };
const int iaKnightT33IncUndeadHP[10] = { 100,120,140,160,180,200,220,240,260,280 };
const int iaKnightT33Duration[10] = { 90,110,130,150,170,190,210,230,250,270 };

const int iaKnightT34AttackRatingBoost[10] = { 5,10,15,20,25,30,35,40,45,50 };
const int iaKnightT34DamageBoost[10] = { 65,70,75,80,85,90,95,100,105,110 };
const int iaKnightT34UnDeadDMGBoost[10] = { 5,10,15,20,25,30,35,40,45,50 };

//T4
const int iaKnightT41DamageBoost[10] = { 50,58,66,74,82,90,98,106,114,122 };
const int iaKnightT41Area[10] = { 80,90,100,110,120,130,140,150,160,170 };

const int iaKnightT42ShieldAbsorptionBoost[10] = { 40,46,52,58,64,70,76,82,96,100 };
const int iaKnightT42Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaKnightT43AddAttackPower[10] = { 11,12,13,14,15,16,17,18,19,20 };
const int iaKnightT43Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaKnightT44AddCritical[10] = { 3,3,3,4,4,4,5,5,5,6 };
const int iaKnightT44DamageBoost[10] = { 65,75,85,95,105,115,125,135,145,155 };
const int iaKnightT44NumberHits[10] = { 3,3,3,3,5,5,5,5,7,7 };

//T5
const int iaKnightT51DamageBoost[10] = { 40,58,76,94,112,130,148,166,184,202 };
const int iaKnightT51AttackRating[10] = { 40,45,50,55,60,65,70,75,80,85 };

const int iaKnightT52DamageBoost[10] = { 170,180,190,200,210,220,230,240,250,260 };
const int iaKnightT52AttackArea[10] = { 70,75,81,88,96,104,113,122,131,140 };

const int iaKnightT53DamageBoost[10] = { 50,70,90,110,130,150,170,190,210,230 };
const int iaKnightT53UndeadDamage[10] = { 5,10,15,20,25,30,35,40,45,50 };

const int iaKnightT54DeathRate[10] = { 5,8,11,14,17,20,23,26,29,32 };
const int iaKnightT54Duration[10] = { 120,110,100,90,80,70,60,50,40,30 };

//Atalanta
//T1
const MinMax saAtaT11AttackPower[10] = { {20,30},{30,40},{40,50},{50,60},{60,70},{70,80},{80,90},{90,100},{100,110},{110,120} };

const int iaAtaT12DamageBoost[10] = { 14,16,18,20,22,24,26,28,30,32 };
const int iaAtaT12AddAttackSpeed[10] = { 1,1,1,1,2,2,2,2,2,2 };
const int iaAtaT12AddAttackRating[10] = { 30,40,50,60,70,80,90,100 };

const int iaAtaT13AddAttackPower[10] = { 14,16,18,20,22,24,26,28,30,32 };

const int iaAtaT14DamageBoost[10] = { 16,20,24,28,32,35,40,45,50,55 };

//T2
const int iaAtaT21AttackRatingBoost[10] = { 30,35,40,45,50,55,60,65,75,80 };
const int iaAtaT21AddRange[10] = { 30,30,30,30,30,30,30,30,30,30 };
const int iaAtaT21Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaAtaT22DamageBoost[10] = { 14,18,22,24,26,28,30,32,34,36 };
const int iaAtaT22AttackRatingBoost[10] = { 10,10,11,11,12,12,13,13,14,15 };

const int iaAtaT23LifeAbsorption[10] = { 12,14,18,20,22,24,26,28,30 };

const int iaAtaT24DamageBoost[10] = { 20,28,32,36,40,55,60,65,70,75 };

//T3
const int iaAtaT31NumberHits[10] = { 3,3,3,3,3,3,3,3,3,3 };
const int iaAtaT31DamageBoost[10] = { 25,35,45,55,65,75,85,95,105,115 };
const int iaAtaT31AttackRatingBoost[10] = { 1,2,3,4,5,7,9,11,13,15 };

const int iaAtaT32MaxAttackPower[10] = { 7,14,21,28,35,42,49,56,63,70 };
const int iaAtaT32Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaAtaT33DamageBoost[10] = { 20,28,32,36,40,55,60,65,70,75 };

const int iaAtaT34DamageBoost[10] = { 20,24,28,30,32,34,35,36,37,38 };

//T4
const int iaAtaT41AddEvasion[10] = { 6,7,8,9,10,11,12,13,14,15 };
const int iaAtaT41Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaAtaT42DamageBoost[10] = { 46,52,58,64,70,76,82,88,94,100 };
const int iaAtaT42Area[10] = { 100,105,110,115,120,125,130,140,145 };

const MinMax saAtaT43AddAttack[10] = { {20,20},{22,22},{24,24},{26,26},{28,28},{30,30},{32,32},{34,34},{36,36},{38,38} };
const int iaAtaT43TargetRunningSpeedReduction[10] = { 7,8,9,10,11,12,13,14,15,16 };
const int iaAtaT43FreezeTime[10] = { 5,5,6,6,7,7,8,8,9,9 };
const int iaAtaT43Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaAtaT44DamageBoost[10] = { 55,60,65,70,75,80,85,90,95,100 };
const int iaAtaT44AddRange[10] = { 10,15,20,25,30,35,40,45,50,55 };

//T5
const int iaAtaT51MovementSpeed[10] = { 1,1,1,2,2,2,3,3,3,4 };
const int iaAtaT51Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaAtaT52DamegeBoost[10] = { 20,30,40,50,60,70,80,90,100,110 };
const int iaAtaT52DamegeHit[10] = { 2,2,4,4,6,6,8,8,10,10 };

const MinMax saSummonTigerAttackPower[10] = { {180,205},{190,215},{200,225},{210,235},{220,245},{230,255},{240,265},{250,275},{260,285},{270,295} };
const int iaSummonTigerAttackRating[10] = { 200,400,600,800,1000,1200,1400,1600,1800,2000 };
const int iaSummonTigerHP[10] = { 3000,6000,9000,12000,15000,18000,21000,24000,27000,30000 };
const int iaSummonTigerDuration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaAtaT54DamegeBoost[10] = { 30,40,50,60,70,80,90,100,110,120 };
const int iaAtaT54AddCritcal[10] = { 6,8,10,12,14,16,18,20,22,24 };

//Priestess
//T1
const int iaPrsT11HPRestored[10] = { 10,14,18,22,26,30,34,38,42,46 };

const int iaPrsT12DamageBoost[10] = { 37,39,41,43,45,47,49,51,53,55 };

const int iaPrsT13AttackPowerDamage[10] = { 8,10,12,8,10,12,10,12,10,12 };
const MinMax saPrsT13NumberofSparks[10] = { {3,4},{3,4},{3,4},{3,5},{3,5},{3,5},{4,6},{4,6},{4,7},{4,7} };

const int iaPrsT14ReduceDamage[10] = { 10,13,16,19,22,25,28,30,32,34 };
const int iaPrsT14Duration[10] = { 15,15,15,15,15,15,15,15,15,15 };

//T2
const int iaPrsT21AddMPRegeneration[10] = { 1,2,3,4,5,6,8,11,15,20 };

const int iaPrsT22Range[10] = { 180,180,180,180,180,180,180,180,180,180 };
const int iaPrsT22DamageBoost[10] = { 32,34,36,38,40,42,44,46,48,50 };
const int iaPrsT22NumberofBolts[10] = { 3,3,3,4,4,4,5,5,5,6 };

const int iaPrsT23ReflectDmg[10] = { 15,30,45,60,75,90,105,120,135,150 };
const int iaPrsT23Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };;

const int iaPrsT24HPRestored[10] = { 20,24,28,32,36,40,44,48,52,56 };
const int iaPrsT24Range[10] = { 300,310,320,330,340,350,360,370,380,390 };

//T3
const int iaPrsT31DamageBoost[10] = { 48,51,54,57,60,63,66,69,72,75 };

const int iaPrsT32Chance[10] = { 40,47,54,61,67,73,79,84,89,94 };

const int iaPrsT33SuccessRate[10] = { 60,64,68,72,76,80,84,92,96 };
const int iaPrsT33HPReduction[10] = { 26,28,30,32,34,36,38,40,42,44 };

const int iaPrsT34HPBoost[10] = { 3,6,9,12,15,18,21,24,27,30 };
const int iaPrsT34Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

//T4
const int iaPrsT41DmgBoost[10] = { 85,90,95,100,105,110,115,120,125,130 };
const int iaPrsT41FreezeChance[10] = { 35,40,45,50,55,60,65,70,75,80 };
const int iaPrsT41Duration[10] = { 2,2,4,4,6,6,8,8,10,10 };
const int iaPrsT41Range[10] = { 150,155,160,165,170,175,180,185,190,195 };

const int iaPrsT42HPRecovery[10] = { 20,40,60,80,100,120,140,160,180,200 };
const int iaPrsT42MPRecovery[10] = { 30,60,90,120,150,180,210,240,270,300 };
const int iaPrsT42Duration[10] = { 10,20,30,40,50,60,70,80,90,100 };
const int iaPrsT42Area[10] = { 250,260,270,280,290,300,310,320,330,340 };

const int iaPrsT43DmgBoost[10] = { 55,60,65,70,75,80,85,90,95,100 };
const int iaPrsT43NumberofBolts[10] = { 7,9,11,13,15,17,19,21,23,25 };
const int iaPrsT43Range[10] = { 110,120,130,140,150,160,170,180,190,200 };

const MinMax saPrsT44Damage[10] = { {35,60},{45,70},{55,80},{65,90},{75,100},{85,110},{95,120},{105,130},{115,140},{125,150} };
const int iaPrsT44Evasion[10] = { 6,7,8,9,10,11,12,13,14,15 };
const int iaPrsT44AbsorbsUndeadDmg[10] = { 5,10,15,20,25,30,35,40,45,50 };
const int iaPrsT44AttackInterval[10] = { 4,4,4,3,3,3,2,2,2,1 };
const int iaPrsT44Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

//T5
const int iaPrsT51DmgBoost[10] = { 2,4,6,8,10,12,14,16,18,20 };
const int iaPrsT51AttackRange[10] = { 170,175,180,185,190,195,200,205,210,215 };

const int iaPrsT52DmgBoost[10] = { 60,64,68,72,76,80,84,88,92,96 };
const int iaPrsT52FrozenDuration[10] = { 6,7,8,9,10,11,12,13,14,15 };

const int iaPrsT53DmgBoost[10] = { 66,70,74,78,82,86,90,94,98,102 };
const int iaPrsT53ofMeteorites[10] = { 1,1,1,2,2,3,4,5,6,7 };
const int iaPrsT53DmgArea[10] = { 62,64,66,68,70,72,74,76,78,80 };
const float faPrsT53FrozenDuration[10] = { 0.5f,1.0f,1.5f,2.0f,2.5f,3.0f,3.5f,4.0f,4.5f,5.0f };
const int iaPrsT53Area[10] = { 141,142,143,144,145,146,147,148,149,150 };

const int iaPrsT54Evasionrate[10] = { 10,15,20,25,30,35,40,45,50,55 };
const int iaPrsT54AddedAbsorb[10] = { 2,2,2,5,5,5,8,8,8,10 };
const int iaPrsT54Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

//Magician
//T1
const int iaMagT11HPtaken[10] = { 65,60,55,50,45,40,35,30,25,20 };
const int iaMagT11MPrecovery[10] = { 10,20,30,40,50,60,70,80,90,100 };

const int iaMagT12DamageBoost[10] = { 7,14,21,28,35,42,49,56,63,70 };
const int iaMagT12AttackRange[10] = { 150,155,160,165,170,175,180,185,190,195 };

const int iaMagT13Resistance[10] = { 5,10,15,20,25,30,35,40,45,50 };
const int iaMagT13Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaMagT14DmgBoost[10] = { 20,22,24,26,28,30,32,34,36,38 };
const int iaMagT14Range[10] = { 163,166,169,172,175,178,181,184,187,190 };
const int iaMagT14Area[10] = { 70,72,74,76,78,80,82,84,86,88 };

//T2
const int iaMagT21MPBoost[10] = { 4,8,12,16,20,24,28,32,36,40 };

const int iaMagT22DmgBoost[10] = { 23,46,69,92,115,138,161,184,207,230 };
const int iaMagT22AtkRange[10] = { 170,174,178,182,186,190,194,198,202,206 };
const int iaMagT22Area[10] = { 66,70,74,78,82,86,90,94,98,102 };
const int iaMagT22Lifetime[10] = { 3,4,5,6,7,8,9,10,11,12 };

const MinMax saMagT23FireDmg[10] = { {1,2},{2,3},{3,4},{4,5},{5,6},{6,7},{7,8},{8,9},{9,10},{10,11} };
const MinMax saMagT23LightningDmg[10] = { {2,3},{3,4},{4,5},{5,6},{6,7},{7,8},{8,9},{9,10},{10,11},{11,12} };
const MinMax saMagT23IceDmg[10] = { {0,1},{1,2},{2,3},{3,4},{4,5},{5,6},{6,7},{7,8},{8,9},{9,10} };
const int iaMagT23Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaMagT24DmgBoost[10] = { 48,51,54,57,60,63,66,69,72,75 };
const int iaMagT24AtkRange[10] = { 19,21,23,25,27,29,30,31,32,33 };
const int iaMagT24Range[10] = { 185,190,195,200,205,210,215,220,225,230 };

//T3
const int iaMagT31MPReduction[10] = { 8,10,12,14,16,18,20,22,24,26 };
const int iaMagT31Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaMagT32DmgBoost[10] = { 20,24,28,32,36,40,44,48,52,56 };
const int iaMagT32Area[10] = { 100,105,110,115,120,125,130,135,140,145 };

const int iaMagT33DmgBoost[10] = { 20,26,32,38,44,50,56,62,68,74 };
const float faMagT33MPRegen[10] = { 0.2f,0.4f,0.6f,0.8f,1.0f,1.2f,1.4f,1.6f,1.8f,2.0f };
const int iaMagT33Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaMagT34FireDmgBoost[10] = { 25,30,35,40,45,50,55,60,65,70 };
const int iaMagT34IceDmgBoost[10] = { 20,25,30,35,40,45,50,55,60,65 };
const int iaMagT34AtkInterval[10] = { 4,4,4,4,4,4,4,4,4,4 };
const int iaMagT34Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

//T4
const MinMax saMagT41AttackPower[10] = { {180,205},{190,215},{200,225},{210,235},{220,245},{230,255},{240,265},{250,275},{260,285},{270,295} };
const int iaMagT41AttackRating[10] = { 200,400,600,800,1000,1200,1400,1800,2000 };
const int iaMagT41HP[10] = { 3000,6000,9000,12000,15000,18000,21000,24000,27000,30000 };
const int iaMagT41Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaMagT42DmgBoost[10] = { 20,40,60,80,100,120,140,160,180,200 };
const int iaMagT42AtkRange[10] = { 130,140,150,160,170,180,190,200,210,220 };

const int iaMagT43Speed[10] = { -4,-6,-8,-10,-12,-14,-16,-18,-20,-22 };
const int iaMagT43Area[10] = { 120,125,130,135,140,145,150,155,160,165 };
const int iaMagT43Duration[10] = { 2,3,4,5,8,9,11,12,14,15 };

const int iaMagT44DmgBoost[10] = { 30,35,40,45,50,55,60,65,70,75 };
const int iaMagT44Area[10] = { 100,105,110,115,120,125,130,135,140,145 };

//T5
const int iaMagT51DmgBoost[10] = { 30,35,40,45,50,55,60,65,70,75 };
const int iaMagT51Area[10] = { 110,120,130,140,150,160,170,180,190,200 };

const int iaMagT52ReduceSpeed[10] = { 10,12,14,18,20,22,24,26,28,30 };
const int iaMagT52Area[10] = { 110,120,130,140,150,160,170,180,190,200 };
const int iaMagT52Duration[10] = { 10,12,14,18,20,22,24,26,28,30 };

const int iaMagT53DmgBoost[10] = { 35,39,43,47,51,55,59,63,67,71 };
const int iaMagT53Area[10] = { 120,125,130,135,140,145,150,155,160,165 };
const int iaMagT53Numbers[10] = { 3,3,3,4,5,6,7,8,9,10 };

const int iaMagT54MPBoost[10] = { 20,30,40,50,60,70,80,90,100,110 };
const int iaMagT54Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

//Assassin

//T1
const int iaAssaT11DmgBoost[10] = { 10,20,30,40,50,60,70,80,90,100 };

const int iaAssaT12DmgBoost[10] = { 56,62,68,74,80,86,92,98,104,110 };

const int iaAssaT13AddedAtkPwr[10] = { 5,7,9,11,14,17,20,23,27,31 };

const int iaAssaT14AtkPowReduction[10] = { -6,-8,-10,-12,-14,-16,-18,-20,-22,-24 };
const int iaAssaT14Range[10] = { 73,76,79,82,85,88,91,94,97,100 };
const int iaAssaT14Duration[10] = { 10,10,10,12,12,12,14,14,14,16 };

//T2
const int iaAssaT21DmgBoost[10] = { 12,24,36,48,60,72,84,96,108,120 };
const int iaAssaT21PoisonChance[10] = { 55,60,65,70,75,80,85,90,95,100 };
const int iaAssaT21PoisonDuration[10] = { 6,6,7,7,8,8,9,10,11,12 };

const int iaAssaT22Evasion[10] = { 2,3,4,5,6,7,8,9,10,12 };
const int iaAssaT22Area[10] = { 200,220,240,260,280,300,320,340,360,380 };
const int iaAssaT22Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaAssaT23Area[10] = { 70,75,80,85,90,95,100,105,110,115 };
const int iaAssaT23StunTime[10] = { 2,3,4,5,6,7,8,9,10,12 };

const int iaAssaT24AtkPwr[10] = { 8,14,20,26,32,38,44,50,56,62 };
const int iaAssaT24Evasion[10] = { 3,6,9,12,15,18,21,24,27,30 };

//T3
const int iaAssaT31DmgBoost[10] = { 74,78,82,86,90,94,98,102,106,110 };
const int iaAssaT31AtkRange[10] = { 18,20,22,24,25,26,27,28,29,30 };

const int iaAssaT32DmgBoost[10] = { 55,60,65,70,75,80,85,90,95,100 };
const int iaAssaT32Area[10] = { 80,80,80,80,80,80,80,80,80,80 };

const int iaAssaT33AtkSpd[10] = { 16,17,18,19,20,21,22,23,24,25 };
const int iaAssaT33Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaAssaT34AfterDmg[10] = { 13,14,15,16,17,18,19,20,21,22 };
const int iaAssaT34MoveSpeed[10] = { 11,12,13,14,15,16,16,17,17,18 };
const int iaAssaT34AtkRtgBoost[10] = { 10,20,30,40,50,60,70,80,90,100 };
const int iaAssaT34Visibility[10] = { -70,-74,-78,-82,-85,-88,-90,-92,-94,-95 };
const int iaAssaT34Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

//T4
const int iaAssaT41DmgBoost[10] = { 80,84,88,92,96,100,108,112,116 };
const int iaAssaT41FreezeChance[10] = { 25,30,35,40,45,50,55,60,65,70 };
const int iaAssaT41FreezeDuration[10] = { 3,4,5,5,6,6,7,8,9,10 };

const int iaAssaT42Critical[10] = { 3,4,5,6,7,8,9,10,11,12 };

const int iaAssaT43Area[10] = { 90,95,100,110,115,120,125,130,135,140 };
const int iaAssaT43DmgBoost[10] = { 73,80,87,94,101,108,115,122,129,136 };
const int iaAssaT43PoisonChance[10] = { 15,17,19,21,23,25,27,29,31,33 };
const int iaAssaT43PoisonDuration[10] = { 5,5,6,6,7,7,8,10,11,12 };

const int iaAssaT44DmgBoost[10] = { 52,57,62,67,72,77,82,87,92,97 };

//T5
const int iaAssaT51DmgBoost[10] = { 79,86,93,100,107,114,121,128,135,142 };
const int iaAssaT51Area[10] = { 90,95,100,105,110,115,120,125,130,135 };
const int iaAssaT51BurnChance[10] = { 4,8,12,16,20,24,28,32,36,40 };
const int iaAssaT51BurnDuration[10] = { 1,2,3,4,5,6,7,8,9,10 };

const int iaAssaT52DmgBoost[10] = { 150,155,160,165,170,175,180,185,190,195 };
const int iaAssaT52Area[10] = { 80,83,86,89,92,95,97,101,104,107 };

const int iaAssaT53DmgBoost[10] = { 95,100,105,110,115,120,125,130,135,140 };
const int iaAssaT53Critical[10] = { 6,75,8,9,10,11,12,13,14,15 };

const int iaAssaT54DmgBoost[10] = { 60,64,68,72,76,80,84,88,92,96 };
const int iaAssaT54AreaDmgBoost[10] = { 76,78,80,82,84,86,88,90,92,94 };
const int iaAssaT54Range[10] = { 53,56,59,62,65,68,71,74,77,80 };
const int iaAssaT54Area[10] = { 86,90,94,98,102,106,110,114,118,122 };
const int iaAssaT54PushRange[10] = { 85,90,95,100,105,110,115,120,125,130 };

//Shaman

//T1
const int iaShamanT11DmgBoost[10] = { 123,126,129,132,135,138,141,144,147,150 };

const int iaShamanT12DmgBoost[10] = { 114,118,122,126,130,134,138,142,146,150 };
const int iaShamanT12ExtraRange[10] = { 35,45,55,65,75,85,95,105,115,125 };

const int iaShamanT13SpeedReduction[10] = { -16,-18,-20,-22,-24,-26,-28,-30,-32,-34 };
const int iaShamanT13AtkPowReduction[10] = { -11,-12,-13,-14,-15,-16,-17,-18,-19,-20 };
const int iaShamanT13Range[10] = { 163,166,169,172,175,178,181,184,187,190 };
const int iaShamanT13Duration[10] = { 15,15,15,15,15,15,15,15,15,15 };

const int iaShamanT14MPBoost[10] = { 4,7,10,13,16,19,22,25,28,31 };

//T2
const int iaShamanT21DmgBoost[10] = { 75,80,90,95,100,105,110,115,120 };
const int iaShamanT21Range[10] = { 175,180,185,190,195,200,205,210,215,220 };
const int iaShamanT21Area[10] = { 82,84,86,88,90,92,94,96,98,100 };

const int iaShamanT22StunChance[10] = { 25,30,35,40,45,50,55,60,65,70 };
const int iaShamanT22StunDuration[10] = { 3,4,5,5,6,6,7,8,9,10 };

const int iaShamanT23LureSight[10] = { 600,660,720,780,840,900,960,1020,1080,1140 };
const int iaShamanT23Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaShamanT24AtkPower[10] = { 30,33,36,39,42,45,48,51,54,57 };
const int iaShamanT24Area[10] = { 220,220,220,220,220,220,220,220,220,220 };
const int iaShamanT24Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

//T3
const int iaShamanT31AddedAbsorb[10] = { 4,6,8,10,12,14,16,18,20,22 };
const int iaShamanT31AtkRating[10] = { 17,19,21,23,25,27,29,31,33,35 };
const int iaShamanT31Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaShamanT32DmgBoost[10] = { 65,75,85,95,105,115,125,135,145,155 };
const int iaShamanT32Area[10] = { 100,105,110,115,120,125,130,135,140,145 };

const int iaShamanT33DmgBoost[10] = { 130,135,140,145,150,155,160,165,170,175 };
const int iaShamanT33HPAbsorbed[10] = { 10,13,16,19,22,25,28,31,34,37 };

const int iaShamanT34DmgBoost[10] = { 130,140,150,160,170,180,190,200,210,220 };
const int iaShamanT34AtkRtgBoost[10] = { 5,10,15,20,25,30,35,40,45,50 };

const MinMax saShamanT41AttackPower[10] = { {180,205},{190,215},{200,225},{210,235},{220,245},{230,255},{240,275},{250,275},{260,285},{270,295} };
const int iaShamanT41AttackRating[10] = { 200,400,600,800,1000,1200,1400,1600,1800,2000 };
const int iaShamanT41PetHP[10] = { 2000,4000,6000,8000,10000,12000,14000,18000,20000 };
const int iaShamanT41DefenseRating[10] = { 1000,2000,3000,4000,5000,6000,7000,8000,9000,10000 };
const int iaShamanT41Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaShamanT42DmgBoost[10] = { 230,240,250,260,270,280,290,300,310,320 };

const int iaShamanT43AttackSpeed[10] = { 2,4,6,8,10,11,12,13,14,15 };
const int iaShamanT43Area[10] = { 220,220,220,220,220,220,220,220,220,220 };
const int iaShamanT43Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaShamanT44DmgBoost[10] = { 250,255,260,265,270,280,285,290,295 };
const int iaShamanT44Area[10] = { 110,115,120,125,130,135,140,145,150,155 };
const int iaShamanT44PushRange[10] = { 85,90,95,100,105,110,115,120,125,130 };

//T5
const int iaShamanT51MPBoost[10] = { 22,24,26,28,30,32,34,36,38,40 };
const int iaShamanT51SPBoost[10] = { 12,14,16,18,20,22,24,26,28,30 };

const int iaShamanT52DmgBoost[10] = { 130,140,150,160,170,180,190,200,210,220 };
const int iaShamanT52ImpactArea[10] = { 130,135,140,150,155,160,165,170,175 };
const int iaShamanT52Attacks[10] = { 1,2,3,4,5,6,7,8,9,10 };
const float faShamanT52AttackInterval[10] = { 0.0f,7.5f,5.0f,3.75f,3.0f,2.5f,2.15f,1.85f,1.67f,1.5f };
const int iaShamanT52AttackRange[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaShamanT53DmgBoost[10] = { 100,110,120,130,140,150,160,170,180,190 };
const int iaShamanT53Area[10] = { 100,105,110,115,120,125,130,135,140,145 };

const int iaShamanT54AddedHP[10] = { 110,120,130,140,150,160,170,180,190,200 };

enum ESkillType : unsigned int
{
	SKILLTYPE_Undefined			= 0,

	SKILLTYPE_Right				= 0x01000000,
	SKILLTYPE_Left				= 0x02000000,
	SKILLTYPE_All				= 0x03000000,
	SKILLTYPE_Passive			= 0x04000000,
};

enum ESkillID : unsigned int
{
	SKILLID_DefaultAttack			= 0x11111111,

	//Fighter
	SKILLID_MeleeMastery			= 0x02010001,
	SKILLID_FireAttribute			= 0x02010002,
	SKILLID_Raving					= 0x02010003,
	SKILLID_Impact					= 0x02010004,

	SKILLID_TripleImpact			= 0x02020001,
	SKILLID_BrutalSwing				= 0x02020002,
	SKILLID_Roar					= 0x02020003,
	SKILLID_RageofZecram			= 0x02020004,

	SKILLID_Concentration			= 0x02040001,
	SKILLID_AvengingCrash			= 0x02040002,
	SKILLID_SwiftAxe				= 0x02040003,
	SKILLID_BoneCrash				= 0x02040004,

	SKILLID_Destroyer				= 0x02080001,
	SKILLID_Berserker				= 0x02080002,
	SKILLID_CycloneStrike			= 0x02080003,
	SKILLID_BoostHealth				= 0x02080004,

	SKILLID_SurvivalInstinct		= 0x02100001,
	SKILLID_SeismicImpact			= 0x02100002,
	SKILLID_RuthlessofZecram		= 0x02100003,
	SKILLID_Whirlwind				= 0x02100004,

	//Mechanician
	SKILLID_ExtremeShield			= 0x01010001,
	SKILLID_MechanicBomb			= 0x01010002,
	SKILLID_PoisonAttribute			= 0x01010003,
	SKILLID_PhysicalAbsorb			= 0x01010004,

	SKILLID_GreatSmash				= 0x01020001,
	SKILLID_Maximize				= 0x01020002,
	SKILLID_Automation				= 0x01020003,
	SKILLID_Spark					= 0x01020004,
	
	SKILLID_MetalArmor				= 0x01040001,
	SKILLID_GrandSmash				= 0x01040002,
	SKILLID_MechanicWeaponMastery	= 0x01040003,
	SKILLID_SparkShield				= 0x01040004,
	
	SKILLID_Impulsion				= 0x01080001,
	SKILLID_Compulsion				= 0x01080002,
	SKILLID_MagneticSphere			= 0x01080003,
	SKILLID_MetalGolem				= 0x01080004,

	SKILLID_Rupture					= 0x01100001,
	SKILLID_ParasitShot				= 0x01100002,
	SKILLID_HardeningShield			= 0x01100003, //究极之刃
	SKILLID_MagneticDischarge		= 0x01100004,

	//Archer
	SKILLID_ScoutHawk				= 0x04010001,
	SKILLID_ShootingMastery			= 0x04010002,
	SKILLID_WindArrow				= 0x04010003,
	SKILLID_PerfectAim				= 0x04010004,
										 
	SKILLID_DionsEye				= 0x04020001,
	SKILLID_Falcon					= 0x04020002,
	SKILLID_ArrowofRage				= 0x04020003,
	SKILLID_Avalanche				= 0x04020004,
										 
	SKILLID_ElementalShot			= 0x04040001,
	SKILLID_GoldenFalcon			= 0x04040002,
	SKILLID_BombShot				= 0x04040003,
	SKILLID_Perforation				= 0x04040004,
										 
	SKILLID_RecallWolverine			= 0x04080001,
	SKILLID_EvasionMastery			= 0x04080002,
	SKILLID_PhoenixShot				= 0x04080003,
	SKILLID_ForceofNature			= 0x04080004,

	SKILLID_LethalSight				= 0x04100001,
	SKILLID_FierceWind				= 0x04100002,
	SKILLID_EntalingRoots			= 0x04100003,
	SKILLID_Bombardment				= 0x04100004,

	//Pikeman
	SKILLID_PikeWind				= 0x03010001,
	SKILLID_IceAttribute			= 0x03010002,
	SKILLID_CriticalHit				= 0x03010003,
	SKILLID_JumpingCrash			= 0x03010004,

	SKILLID_GroundPike				= 0x03020001,
	SKILLID_Tornado					= 0x03020002,
	SKILLID_WeaponDefenseMastery	= 0x03020003,
	SKILLID_Expansion				= 0x03020004,
	
	SKILLID_VenomSpear				= 0x03040001,
	SKILLID_Vanish					= 0x03040002,
	SKILLID_CriticalMastery			= 0x03040003,
	SKILLID_ChainLance				= 0x03040004,

	SKILLID_AssassinsEye			= 0x03080001,
	SKILLID_ChargingStrike			= 0x03080002,
	SKILLID_Vague					= 0x03080003,
	SKILLID_ShadowMaster			= 0x03080004,

	SKILLID_RingofSpears			= 0x03100001,
	SKILLID_Focus					= 0x03100002,
	SKILLID_DeathMaster				= 0x03100003,
	SKILLID_Twister					= 0x03100004,

	//Atalanta
	SKILLID_ShieldStrike			= 0x06010001,
	SKILLID_Farina					= 0x06010002,
	SKILLID_ThrowingMaster			= 0x06010003,
	SKILLID_BiggerSpear				= 0x06010004,
										 
	SKILLID_Windy					= 0x06020001,
	SKILLID_TwistJavelin			= 0x06020002,
	SKILLID_SoulSucker				= 0x06020003,
	SKILLID_FireJavelin				= 0x06020004,
										 
	SKILLID_SplitJavelin			= 0x06040001,
	SKILLID_TriumphofJavelin		= 0x06040002,
	SKILLID_LightningJavelin		= 0x06040003,
	SKILLID_StormJavelin			= 0x06040004,
										 
	SKILLID_HallofValhalla			= 0x06080001,
	SKILLID_ExtremeRage				= 0x06080002,
	SKILLID_FrostJavelin			= 0x06080003,
	SKILLID_Vengeance				= 0x06080004,

	SKILLID_PlagueJavelin			= 0x06100001,
	SKILLID_GoldenApple				= 0x06100002,
	SKILLID_SummonTiger				= 0x06100003,
	SKILLID_ComboJavelin			= 0x06100004,

	//Knight
	SKILLID_SwordBlast				= 0x05010001,
	SKILLID_HolyBody				= 0x05010002,
	SKILLID_PhysicalTraining		= 0x05010003,
	SKILLID_DoubleCrash				= 0x05010004,

	SKILLID_HolyValor				= 0x05020001,
	SKILLID_Brandish				= 0x05020002,
	SKILLID_Piercing				= 0x05020003,
	SKILLID_DrasticSpirit			= 0x05020004,
	
	SKILLID_SwordMastery			= 0x05040001,
	SKILLID_DivineShield			= 0x05040002,
	SKILLID_HolyIncantation			= 0x05040003,
	SKILLID_GrandCross				= 0x05040004,

	SKILLID_SwordofJustice			= 0x05080001,
	SKILLID_GodlyShield				= 0x05080002,
	SKILLID_GodsBlessing			= 0x05080003,
	SKILLID_DivinePiercing			= 0x05080004,

	SKILLID_HolyConviction			= 0x05100001,
	SKILLID_DivineInquisiton		= 0x05100002,
	SKILLID_GloriousShield			= 0x05100003,
	SKILLID_DivineCross				= 0x05100004,

	//Magician
	SKILLID_Agony					= 0x08010001,
	SKILLID_FireBolt				= 0x08010002,
	SKILLID_Zenith					= 0x08010003,
	SKILLID_FireBall				= 0x08010004,

	SKILLID_MetalMastery			= 0x08020001,
	SKILLID_Watornado				= 0x08020002,
	SKILLID_EnchantWeapon			= 0x08020003,
	SKILLID_DeathRay				= 0x08020004,
	
	SKILLID_EnergyShield			= 0x08040001,
	SKILLID_Diastrophism			= 0x08040002,
	SKILLID_SpiritElemental			= 0x08040003,
	SKILLID_DancingSword			= 0x08040004,

	SKILLID_FireElemental			= 0x08080001,
	SKILLID_FlameWave				= 0x08080002,
	SKILLID_Distortion				= 0x08080003,
	SKILLID_Meteorite				= 0x08080004,

	SKILLID_WizardTrance			= 0x08100001,
	SKILLID_StoneSkin				= 0x08100002,
	SKILLID_RedRay					= 0x08100003,
	SKILLID_Cataclysm				= 0x08100004,

	//Priestess
	SKILLID_Healing					= 0x07010001,
	SKILLID_HolyBolt				= 0x07010002,
	SKILLID_MultiSpark				= 0x07010003,
	SKILLID_HolyMind				= 0x07010004,

	SKILLID_Meditation				= 0x07020001,
	SKILLID_DivineLightning			= 0x07020002,
	SKILLID_HolyReflection			= 0x07020003,
	SKILLID_GrandHealing			= 0x07020004,

	SKILLID_VigorBall				= 0x07040001,
	SKILLID_Ressurection			= 0x07040002,
	SKILLID_Extinction				= 0x07040003,
	SKILLID_VirtualLife				= 0x07040004,

	SKILLID_GlacialSpike			= 0x07080001,
	SKILLID_RegenerationField		= 0x07080002,
	SKILLID_ChainLightning			= 0x07080003,
	SKILLID_SummonMuspell			= 0x07080004,

	SKILLID_IceElemental			= 0x07100001,
	SKILLID_LightningSurge			= 0x07100002,
	SKILLID_HeavenlyLight			= 0x07100003,
	SKILLID_Consecration			= 0x07100004,

	//Assassin
	SKILLID_Stinger					= 0x10010001,
	SKILLID_RunningHit				= 0x10010002,
	SKILLID_DualWieldMastery		= 0x10010003,
	SKILLID_Wisp					= 0x10010004,

	SKILLID_VenomThorn				= 0x10020001,
	SKILLID_Alas					= 0x10020002,
	SKILLID_SoulShock				= 0x10020003,
	SKILLID_AttackMastery			= 0x10020004,

	SKILLID_SoreBlade				= 0x10040001,
	SKILLID_GustSlash				= 0x10040002,
	SKILLID_Inpes					= 0x10040003,
	SKILLID_Blind					= 0x10040004,

	SKILLID_FrostWind				= 0x10080001,
	SKILLID_FatalMastery			= 0x10080002,
	SKILLID_Polluted				= 0x10080003,
	SKILLID_NinjaShadow				= 0x10080004,

	SKILLID_ShadowBlink				= 0x10100001,
	SKILLID_RisingSlash				= 0x10100002,
	SKILLID_ViolentStub				= 0x10100003,
	SKILLID_ShadowStorm				= 0x10100004,

	//Shaman
	SKILLID_DarkBolt				= 0x50010001,
	SKILLID_DarkWave				= 0x50010002,
	SKILLID_Inertia					= 0x50010003,
	SKILLID_InnerPeace				= 0x50010004,

	SKILLID_SpiritualFlare			= 0x50020001,
	SKILLID_SpiritualManacle		= 0x50020002,
	SKILLID_ChasingHunt				= 0x50020003,
	SKILLID_AdventMigal				= 0x50020004,
	
	SKILLID_Rainmaker				= 0x50040001,
	SKILLID_PhantomCall				= 0x50040002,
	SKILLID_Haunt					= 0x50040003,
	SKILLID_Scratch					= 0x50040004,

	SKILLID_RecallHestian			= 0x50080001,
	SKILLID_Judgement				= 0x50080002,
	SKILLID_AdventMidranda			= 0x50080003,
	SKILLID_MourningPray			= 0x50080004,

	SKILLID_Creed					= 0x50100001,
	SKILLID_PressDeity				= 0x50100002,
	SKILLID_PhantomNail				= 0x50100003,
	SKILLID_OccultLife				= 0x50100004,

	//Stones
	SKILLID_FighterStone			= 0x09040001,
	SKILLID_MechanicianStone		= 0x09040002,
	SKILLID_PikemanStone			= 0x09040003,
	SKILLID_ArcherStone				= 0x09040004,
	SKILLID_KnightStone				= 0x09040005,
	SKILLID_AtalantaStone			= 0x09040006,
	SKILLID_PriestessStone			= 0x09040007,
	SKILLID_MagicianStone			= 0x09040008,
	SKILLID_ShamanStone				= 0x09040009,
	SKILLID_AssassinStone			= 0x0904000A,

	//Timers
	SKILLID_AvertScroll				= 0x09080003,
	SKILLID_AbsorptionOfGlory		= 0x09010004,
	SKILLID_PowerSiege				= 0x09010005,
	SKILLID_EvasionAdaption			= 0x09010006,
	SKILLID_Force					= 0x09010001,
	SKILLID_QUEST1					= 0x09010002,
	SKILLID_QUEST2					= 0x09010003,
	SKILLID_QUEST3					= 0x09010010,
	SKILLID_QUEST4					= 0x09010020,
	SKILLID_QUESTNew				= 0x096A0003,
	SKILLID_QUESTNewTime			= 0x096B0003,
	SKILLID_Atanasia				= 0x09020001,
	SKILLID_DeadlyEdge				= 0x09020002,
	SKILLID_AvailofEvasion			= 0x09020003,
	SKILLID_DefianceStoneA			= 0x09020004,
	SKILLID_DefianceStoneB			= 0x09020005,
	SKILLID_DefianceStoneC			= 0x09020006,
	SKILLID_MightStone				= 0x09040010,
	SKILLID_EternalLife				= 0x09080001,
	SKILLID_FatalEdge				= 0x09080002,
	SKILLID_Rivera					= 0x09080004,

	SKILLID_BellatraGold			= 0x096A0061,
	SKILLID_BellatraSilver			= 0x096A0062,
	SKILLID_BellatraBronze			= 0x096A0063,
};

enum ESkillPlayID
{
	SKILLPLAYID_Undefined		= 0x00,

	//Tier1
	SKILLPLAYID_T11				= 0x1A,
	SKILLPLAYID_T12				= 0x1B,
	SKILLPLAYID_T13				= 0x1C,
	SKILLPLAYID_T14				= 0x1D,

	//Tier2
	SKILLPLAYID_T21				= 0x2A,
	SKILLPLAYID_T22				= 0x2B,
	SKILLPLAYID_T23				= 0x2C,
	SKILLPLAYID_T24				= 0x2D,

	//Tier3
	SKILLPLAYID_T31				= 0x3A,
	SKILLPLAYID_T32				= 0x3B,
	SKILLPLAYID_T33				= 0x3C,
	SKILLPLAYID_T34				= 0x3D,

	//Tier4
	SKILLPLAYID_T41				= 0x4A,
	SKILLPLAYID_T42				= 0x4B,
	SKILLPLAYID_T43				= 0x4C,
	SKILLPLAYID_T44				= 0x4D,

	//Tier5
	SKILLPLAYID_T51				= 0x5A,		//90
	SKILLPLAYID_T52				= 0x5B,		//91
	SKILLPLAYID_T53				= 0x5C,		//92
	SKILLPLAYID_T54				= 0x5D,		//93
};

struct RecordSkill
{
	BYTE bSkillPoint[MAX_SKILL_POINT_COLUM];
	WORD wSkillMastery[MAX_SKILL_POINT_COLUM];
	WORD wShortKey[MAX_SKILL_POINT_COLUM];
	WORD wSelectSkill[2];
};

struct SkillBase
{
	char				szName[64];
	char				szDescription[150];
	int					iSkillLevelRequired;
	int					iaSkillUseStamina[2];		// 0 = stamina value static, 1 = increase value each level skill
	int					iaSkillMastery[2];
	int					iaSkillElements[3];
	EItemType			eSkillItemAllowed[10];
	int					(* dwFunctionPointer)();
	ESkillID			eSkillID;
	ESkillType			eSkillType;
	int					* dwUseManaPointer;
	int					iSkillIndex;
};

struct Skill
{
	char				szName[32];
	DWORD				iID;
	char				szFileName[32];
	char				szIconName[32];
	int					bActive;
	BOOL				bCanUse;
	int					iLevel;
	int					ShortKey;
	int					MousePosi;
	int					Position;
	int					iUseTime;
	int					iCheckTime;
	int					GageLength;
	int					GageLength2;
	int					Mastery;
	int					UseSKillIncreCount;
	int					UseSkillCount;
	int					UseSkillMastery;
	int					UseSkillMasteryGage;
	int					UseSkillFlag;
	int					PlusState[5];
	int					Time[2];
	int					PartyFlag;
	int					ElementIndex;
	int					MatIcon;
	DWORD				dwPlayTime;
	int					uID;
	int					iSkillCodeIndex;
	int					IconAlpha;
	int					IconPosiX;
	int					IconTime;
	int					IconFlag;
	DWORD				dwSkillTarget;
	int					SummonFlag;

	SkillBase			sSkillInfo;
};

struct SkillBox
{
	RECT				BoxRect;
	RECT				GageRect;
};

struct UseSkill
{
	Skill			saUseSkill[21];
	SkillBox		saSkillBox[21];
	Skill			* pLeftSkill;
	Skill			* pRightSkill;
	int				iSkillPoint;
	int				iSkillPointTier4;
};

struct PacketRestoreHP : Packet
{
	int hpboost;
	int SKILLLVL;
	int pRange;
	int IDPlayer;
};

struct PacketSkillStatus : Packet
{
	int			iID;

	//Archer T5
	short		sLethalSightLevel;
	short		sLethalSightTimeLeft;
	short		sFierceWindLevel;
	short		sFierceWindTimeLeft;

	//Knight T5
	short		sHolyConvictionLevel;
	short		sHolyConvictionTimeLeft;

	//Mage T5
	short		sWizardTranceLevel;
	short		sWizardTranceTimeLeft;
};

struct PacketSkillStatusContainer : Packet
{
	int			iAmount;

	BYTE		baBuffer[SKILLCONTAINER_LENGTH];
};

static BOOL IsActiveSkill(ESkillID eSkillID)
{
	switch (eSkillID)
	{
		//Fighter
	case SKILLID_Raving:
	case SKILLID_Impact:
	case SKILLID_TripleImpact:
	case SKILLID_BrutalSwing:
	case SKILLID_RageofZecram:
	case SKILLID_AvengingCrash:
	case SKILLID_BoneCrash:
	case SKILLID_Destroyer:
	case SKILLID_CycloneStrike:
	case SKILLID_SurvivalInstinct:
	case SKILLID_SeismicImpact:
	case SKILLID_RuthlessofZecram:

		//Mechanician
	case SKILLID_MechanicBomb:
	case SKILLID_GreatSmash:
	case SKILLID_Spark:
	case SKILLID_GrandSmash:
	case SKILLID_Impulsion:
	case SKILLID_Rupture:
	case SKILLID_HardeningShield:

		//Archer
	case SKILLID_WindArrow:
	case SKILLID_PerfectAim:
	case SKILLID_ArrowofRage:
	case SKILLID_Avalanche:
	case SKILLID_ElementalShot:
	case SKILLID_BombShot:
	case SKILLID_Perforation:
	case SKILLID_PhoenixShot:
	case SKILLID_LethalSight:
	case SKILLID_FierceWind:
	case SKILLID_EntalingRoots:
	case SKILLID_Bombardment:

		//Pikeman 
	case SKILLID_PikeWind:
	case SKILLID_CriticalHit:
	case SKILLID_JumpingCrash:
	case SKILLID_Tornado:
	case SKILLID_Expansion:
	case SKILLID_ChainLance:
	case SKILLID_ChargingStrike:
	case SKILLID_ShadowMaster:
	case SKILLID_RingofSpears:
	case SKILLID_Focus:
	case SKILLID_Twister:

		//Atalanta 
	case SKILLID_BiggerSpear:
	case SKILLID_TwistJavelin:
	case SKILLID_FireJavelin:
	case SKILLID_SplitJavelin:
	case SKILLID_LightningJavelin:
	case SKILLID_StormJavelin:
	case SKILLID_ExtremeRage:
	case SKILLID_Vengeance:
	case SKILLID_GoldenApple:
	case SKILLID_ComboJavelin:

		//Knight 
	case SKILLID_SwordBlast:
	case SKILLID_DoubleCrash:
	case SKILLID_Brandish:
	case SKILLID_Piercing:
	case SKILLID_GrandCross:
	case SKILLID_SwordofJustice:
	case SKILLID_DivinePiercing:
	case SKILLID_HolyConviction:
	case SKILLID_DivineInquisiton:
	case SKILLID_GloriousShield:

		//Magician 
	case SKILLID_Agony:
	case SKILLID_FireBolt:
	case SKILLID_FireBall:
	case SKILLID_Watornado:
	case SKILLID_DeathRay:
	case SKILLID_Diastrophism:
	case SKILLID_FlameWave:
	case SKILLID_Meteorite:
	case SKILLID_WizardTrance:
	case SKILLID_StoneSkin:
	case SKILLID_RedRay:

		//Priestess 
	case SKILLID_Healing:
	case SKILLID_HolyBolt:
	case SKILLID_MultiSpark:
	case SKILLID_DivineLightning:
	case SKILLID_GrandHealing:
	case SKILLID_VigorBall:
	case SKILLID_Ressurection:
	case SKILLID_GlacialSpike:
	case SKILLID_ChainLightning:
	case SKILLID_LightningSurge:
	case SKILLID_HeavenlyLight:

		//Assassin 
	case SKILLID_Stinger:
	case SKILLID_RunningHit:
	case SKILLID_VenomThorn:
	case SKILLID_SoreBlade:
	case SKILLID_GustSlash:
	case SKILLID_FrostWind:
	case SKILLID_NinjaShadow:
	case SKILLID_ShadowBlink:

		//Shaman 
	case SKILLID_DarkBolt:
	case SKILLID_DarkWave:
	case SKILLID_SpiritualFlare:
	case SKILLID_PhantomCall:
	case SKILLID_Scratch:
	case SKILLID_Judgement:
	case SKILLID_MourningPray:
	case SKILLID_PressDeity:
	case SKILLID_PhantomNail:
		return TRUE;
	}

	return FALSE;
}

//被动技能
static BOOL IsPassiveSkill(ESkillID eSkillID)
{
	switch (eSkillID)
	{
		//Fighter
	case SKILLID_MeleeMastery:
	case SKILLID_FireAttribute:
	case SKILLID_BoostHealth:

		//Mechanician
	case SKILLID_PoisonAttribute:
	case SKILLID_MechanicWeaponMastery:

		//Archer
	case SKILLID_ShootingMastery:
	case SKILLID_DionsEye:
	case SKILLID_EvasionMastery:

		//Pikeman 
	case SKILLID_IceAttribute:
	case SKILLID_WeaponDefenseMastery:
	case SKILLID_CriticalMastery:

		//Atalanta 
	case SKILLID_ThrowingMaster:

		//Knight 
	case SKILLID_PhysicalTraining:
	case SKILLID_SwordMastery:

		//Magician 
	case SKILLID_MetalMastery:

		//Priestess 
	case SKILLID_Meditation:

		//Assassin 
	case SKILLID_DualWieldMastery:
	case SKILLID_AttackMastery:
	case SKILLID_FatalMastery:

		//Shaman 
	case SKILLID_InnerPeace:
	case SKILLID_OccultLife:
		return TRUE;
	}

	return FALSE;
}
// 主动BUFF技能
static BOOL IsDebuffSkill(ESkillID eSkillID)
{
	switch (eSkillID)
	{
		//Fighter
	case SKILLID_Roar:

		//Mechanician
		//Archer

		//Pikeman 
	case SKILLID_GroundPike:
	case SKILLID_VenomSpear:
	case SKILLID_AssassinsEye:

		//Atalanta 
	case SKILLID_ShieldStrike:
	case SKILLID_SoulSucker:
	case SKILLID_Distortion:

		//Knight
	case SKILLID_DivineCross:

		//Priestess 
	case SKILLID_HolyMind:
	case SKILLID_Extinction:

		//Assassin 
	case SKILLID_Wisp:
	case SKILLID_SoulShock:
	case SKILLID_Polluted:

		//Shaman 
	case SKILLID_Inertia:
	case SKILLID_SpiritualManacle:
	case SKILLID_Haunt:
		return TRUE;
	}

	return FALSE;
}
// BUFF技能
static BOOL IsBuffSkill(ESkillID eSkillID)
{
	switch (eSkillID)
	{
		//Fighter
	case SKILLID_Concentration:
	case SKILLID_SwiftAxe:
	case SKILLID_Berserker:
	case SKILLID_Whirlwind:

		//Mechanician
	case SKILLID_ExtremeShield:
	case SKILLID_PhysicalAbsorb:
	case SKILLID_Maximize:
	case SKILLID_Automation:
	case SKILLID_MetalArmor:
	case SKILLID_SparkShield:
	case SKILLID_Compulsion:
	case SKILLID_MagneticSphere:
	case SKILLID_ParasitShot:
	case SKILLID_MagneticDischarge:

		//Archer
	case SKILLID_ScoutHawk:
	case SKILLID_Falcon:
	case SKILLID_GoldenFalcon:
	case SKILLID_ForceofNature:

		//Pikeman 
	case SKILLID_Vanish:
	case SKILLID_Vague:
	case SKILLID_DeathMaster:

		//Atalanta 
	case SKILLID_Farina:
	case SKILLID_Windy:
	case SKILLID_TriumphofJavelin:
	case SKILLID_HallofValhalla:
	case SKILLID_FrostJavelin:
	case SKILLID_PlagueJavelin:

		//Knight 
	case SKILLID_HolyBody:
	case SKILLID_HolyValor:
	case SKILLID_DrasticSpirit:
	case SKILLID_DivineShield:
	case SKILLID_HolyIncantation:
	case SKILLID_GodlyShield:
	case SKILLID_GodsBlessing:

		//Magician 
	case SKILLID_Zenith:
	case SKILLID_EnchantWeapon:
	case SKILLID_EnergyShield:
	case SKILLID_SpiritElemental:
	case SKILLID_DancingSword:
	case SKILLID_Cataclysm:

		//Priestess 
	case SKILLID_HolyReflection:
	case SKILLID_VirtualLife:
	case SKILLID_RegenerationField:
	case SKILLID_SummonMuspell:
	case SKILLID_Consecration:

		//Assassin 
	case SKILLID_Alas:
	case SKILLID_Inpes:
	case SKILLID_Blind:

		//Shaman 
	case SKILLID_ChasingHunt:
	case SKILLID_AdventMigal:
	case SKILLID_Rainmaker:
	case SKILLID_AdventMidranda:
	case SKILLID_Creed:
		return TRUE;
	}

	return FALSE;
}
// 召唤技能
static BOOL IsSummonSkill(ESkillID eSkillID)
{
	switch (eSkillID)
	{
		//Mechanician
	case SKILLID_MetalGolem:

		//Archer
	case SKILLID_RecallWolverine:

		//Atalanta
	case SKILLID_SummonTiger:

		//Priestess
	case SKILLID_IceElemental:

		//Magician
	case SKILLID_FireElemental:

		//Shaman
	case SKILLID_RecallHestian:
		return TRUE;
		break;
	}
	return FALSE;
}