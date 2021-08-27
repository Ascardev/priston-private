#pragma once

// Mesh T1
const int iaMechT11ShieldBlockBoost[10] = { 11,12,13,14,15,16,17,18,19,20 };
const int iaMechT11Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaMeshT12StaticDamage[10] = { 10,14,18,22,26,30,34,38,42,46 };
const int iaMeshT12AddAttackPower[10] = { 5,10,20,30,40,50,60,70,80,90 };
const int iaMeshT12Area[10] = { 70,70,70,70,70,70,70,70,70,70 };

const int iaMeshT13AbsorptionBoost[10] = { 5,10,15,20,25,26,27,28,29,30 };
const int iaMeshT13Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaMeshT14PoisonInc[10] = { 9,17,24,30,35,39,42,44,45,46 };
//T2
const int iaMechT21CalculatedDamage[10] = { 20,25,30,35,40,45,50,55,60,65 };
const int iaMechT21Area[10] = { 70,70,70,70,70,70,70,70,70,70 };

const int iaMeshT22AddAttackPower[10] = { 6,7,8,9,10,11,12,13,14,15 };
const int iaMeshT22AddAttackRating[10] = { 1,2,3,4,5,6,7,8,9,10 };
const int iaMeshT22Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaMechT23DamageBoost[10] = { 2,4,6,8,10,12,14,16,18,20 };
const int iaMechT23AtkSpeed[10] = { 4,4,4,4,5,5,5,5,6,6 };
const float faMechT23MPDrain[10] = { 7.0f,8.0f,9.0f,10.0f,11.0f,12.0f,13.0f,14.0f,15.0f,16.0f };
const float faMechT23SPDrain[10] = { 5.0f,6.0f,7.0f,8.0f,9.0f,10.0f,11.0f,12.0f,13.0f,14.0f };
const int iaMeshT23Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaMeshT24DamageBoost[10] = { 28,30,32,34,36,38,40,42,44,46 };
const int iaMeshT24Area[10] = { 100,105,110,115,120,125,130,135,140,145 };
//T3
const int iaMeshT31ArmorDefenseRatingBoost[10] = { 6,9,12,15,18,21,24,27,30,35 };
const int iaMeshT31Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaMeshT32AttackRatingBoost[10] = { 5,10,15,20,25,30,35,40,45,50 };
const int iaMeshT32DamageBoost[10] = { 55,60,70,75,80,85,90,95,100 };

const int iaMeshT33BaseAttackPowerInc[10] = { 5,9,13,17,21,25,29,33,37,41 };

const int iaMeshT34SparkDamage[10] = { 32,34,36,38,40,42,44,46,48,50 };
const int iaMeshT34AddDefenceRating[10] = { 20,30,40,50,60,70,80,90,100,120 };
const int iaMeshT34Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };
//T4
const int iaMeshT41DamgeBoost[10] = { 40,42,44,46,48,50,52,54,56,58 };
const int iaMeshT41Area[10] = { 100,105,110,115,120,125,130,135,140,145 };
const int iaMeshT41Hits[10] = { 6,7,8,9,10,11,12,13,14,15 };

const int iaMeshT42IncAbsorption[10] = { 3,6,9,12,15,18,21,24,27,30 };
const int iaMeshT42BoostAbsorption[10] = { 1,1,1,2,2,3,3,4,4,5 };
const int iaMeshT42RangeInc[10] = { 130,135,140,145,150,155,160,165,170,175 };
const int iaMeshT42Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaMeshT43SpheresDamage[10] = { 2,4,6,8,10,12,14,16,18,20 };
const int iaMeshT43SpheresAttackRange[10] = { 300,300,300,300,300,300,300,300,300,300 };
const int iaMeshT43SpheresAttackDelay[10] = { 6,6,6,5,5,5,4,4,4,3 };
const int iaMeshT43Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const MinMax saMetalGolemAtkDmg[10] = { {160,160},{180,180},{200,200},{220,220},{240,240},{260,260},{280,280},{300,300},{320,320},{340,340} };
const int iaMetalGolemAttackRating[10] = { 1000,1100,1200,1300,1400,1500,1600,1700,1800,1900 };
const int iaMetalGolemHP[10] = { 14000,16000,1800,20000,22000,24000,26000,28000,30000,32000 };
const int iaMetalGolemDefense[10] = { 1000,1200,1400,1600,1800,2000,2200,2400,2600,2800 };
const int iaMetalGolemDuration[10] = { 300,300,300,300,300,300,300,300,300,300 };
//T5
const int iaMechT51DMGBoost[10] = { 70,80,90,100,110,120,130,140,150,160 };

const int iaMechT52DMGBoost[10] = {};
const int iaMechT52PoisonTimeDuration[10] = {};

const int iaMechT53DMGReduction[10] = {};
const int iaMechT53WPAtkRateRed[10] = {};

const int iaMechT54DMGBoost[10] = {};

//Fighter
//T1
const int iaFighterT11WeaponAttackPower[10] = { 6,10,14,18,21,24,26,28,30,32 };

const int iaFighterT12FireResistanceInc[10] = { 9,17,24,30,35,39,42,44,45,46 };

const int iaFighterT13DamageBoost[10] = { 13,16,19,22,25,28,31,34,37,40 };
const int iaFighterT13NumberHit[10] = { 2,2,2,3,3,3,4,4,4,4 };
const float faFighterT13HPDecrease[10] = { 1.0f,1.2f,1.6f,1.8f,2.2f,2.5f,2.7f,3.0f,3.4f,3.7f };

const int iaFighterT14AddAttackRating[10] = { 20,40,60,80,100,120,140,160,180,200 };
const int iaFighterT14DamageBoost[10] = { 20,25,29,33,37,41,45,49,52,55 };
//T2
const int iaFighterT21DamageBoost[10] = { 35,40,25,30,35,25,30,35,40,45 };
const int iaFighterT21NumberHit[10] = { 1,1,2,2,2,3,3,3,3,3 };

const int iaFighterT22DamageBoost[10] = { 10,16,22,28,34,40,45,50,55,60 };
const int iaFighterT22AddCritical[10] = { 3,7,10,13,16,19,21,24,27,30 };

const int iaFighterT23Area[10] = { 50,60,70,80,90,100,108,116,124,130 };
const int iaFighterT23Duration[10] = { 6,7,8,9,10,11,12,13,14,15 };

const int iaFighterT24DamageBoost[10] = { 2,4,6,8,10,12,14,16,18,20 };
const int iaFighterT24Area[10] = { 100,100,100,100,100,100,100,100,100,100 };
//T3
const int iaFighterT31AddAttackRating[10] = { 6,7,8,9,10,11,12,13,14,15 };
const int iaFighterT31Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaFighterT32AddAttackRating[10] = { 10,20,30,40,50,60,70,80,90,100 };
const int iaFighterT32DamageBoost[10] = { 55,60,65,70,75,80,85,90,95,100 };

const int iaFighterT33AttackSpeedBoost[10] = { 3,4,5,6,7,8,9,10,11,12 };
const int iaFighterT33Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaFighterT34DamageBoost[10] = { 20,25,30,35,40,45,50,55,60,65 };
const int iaFighterT34DamageBoostDemons[10] = { 90,95,100,105,110,115,120,125,130,135 };
//T4
const int iaFighterT41DamageBoost[10] = { 45,60,75,90,105,120,135,150,165,180 };
const int iaFighterT41AddCritical[10] = { 10,12,14,16,18,20,22,24,26,28 };

const int iaFighterT42AddBaseAttackPower[10] = { 6,7,8,9,10,11,12,13,14,15 };
const int iaFighterT42DecAbsorption[10] = { 6,7,8,9,10,11,12,13,14,15 };
const int iaFighterT42Duration[10] = { 300,300,300,300,300,300,300,300,300,300 };

const int iaFighterT43DamageBoost[10] = { 15,20,25,30,35,40,45,50,55,60 };
const int iaFighterT43MaxHits[10] = { 6,7,8,9,10,11,12,13,14,15 };
const int iaFighterT43Range[10] = { 100,105,110,115,120,125,130,140,145 };

const int iaFighterT44HPInc[10] = { 10,20,30,40,50,60,70,80,90,100 };
//T5
const float faFighterT51AddHPRegen[10] = { 2.0f,4.0f,6.0f,8.0f,10.0f,12.0f,14.0f,16.0f,18.0f,20.0f };
const int iaFighterT51AddHPPotionBoost[10] = { 4,8,12,16,20,24,28,32,36,40 };
const int iaFighterT51BoostHealthBoost[10] = { 13,16,19,22,25,28,31,34,37,40 };

const int iaFighterT52DMGBoost[10] = { 50,60,70,80,90,100,120,140,160,180 };
const int iaFighterT52Area[10] = { 50,55,60,65,70,80,85,90,100 };

const int faFighterT53HPDec[10] = {};
const int iaFighterT53HitsBoost[10] = {};
const int iaFighterT53DMGBoost[10] = {};
const int iaFighterT54DMGBoost[10] = {};
const int iaFighterT54Duration[10] = {};
const int iaFighterT54MPDrain[10] = {};
const int iaFighterT54SPDrain[10] = {};

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
const int iaPikemanT51Duration[10] = { 8,9,10,11,12,13,14,15,16,17 };

const int iaPikemanT52DamageBoost[10] = { 60,70,80,90,100,110,120,130,140,150 };
const double faPikemanT52Cooldown[10] = { 30.04,30.04,30.04,30.04,30.04,30.04,30.04,30.04,30.04,30.04 };

const int iaPikemanT53DMGBoost[10] = {};
const int iaPikemanT53ATKRate[10] = {};

const int iaPikemanT54DMGBoost[10] = {};

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
const int iaArcherT51RangeAdd[10] = { 10,15,20,25,30,35,40,45,50,55 };
const int iaArcherT51CritRate[10] = { 3,4,5,6,7,8,9,10,27,30 };
const int iaArcherT51DMGBoost[10] = {};
const int iaArcherT52DMGBoost[10] = {};
const int iaArcherT52CDMGBoost[10] = {};
const int iaArcherT53Duration[10] = {};
const int iaArcherT54DMGBoost[10] = {};
const int iaArcherT54Duration[10] = {};
const int iaArcherT54MPDrain[10] = {};
const int iaArcherT54SPDrain[10] = {};

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
const int iaKnightT51DMGBoost[10] = {};
const int iaKnightT52DMGBoost[10] = {};
const int iaKnightT52Area[10] = {};
const int iaKnightT52UndeadDMG[10] = {};
const int iaKnightT53DefBoost[10] = {};
const int iaKnightT54DMGBoost[10] = {};

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
const MinMax saSummonTigerAttackPower[10] = {};
const int iaSummonTigerAttackRating[10] = {};
const int iaSummonTigerHP[10] = {};
const int iaSummonTigerDuration[10] = {};
const int iaAtaT52Speed[10] = {};
const int iaAtaT52Evade[10] = {};
const int iaAtaT53DMGBoost[10] = {};
const int iaAtaT53Targets[10] = {};
const int iaAtaT53PoisonDuration[10] = {};

//Priestess
//T1
const int iaPrsT11FormulaBasedLifeRecovery[10] = { 20,28,36,44,52,60,76,84,92 };
const int iaPrsT1134AttackPowerBasedLifeRecovery[10] = {};

const int iaPrsT12FormulaBasedDamage[10] = {};
const int iaPrsT12DamageBoost[10] = {};

const int iaPrsT13FormulaBasedDamageperHit[10] = {};
const int iaPrsT13AttackPowerBasedDamageperHit[10] = {};
const MinMax saPrsT13NumberofSparks[10] = {};

const int iaPrsT14TargetReduceDamage[10] = {};
const int iaPrsT14Duration[10] = {};

//T2
const int iaPrsT21AddMPPotionBoostRecovery[10] = {};
const int iaPrsT21AddMPRegeneration[10] = {};

const int iaPrsT22AttackRange[10] = {};
const int iaPrsT22DamageBoost[10] = {};
const int iaPrsT22NumberofBolts[10] = {};

const int iaPrsT23MonsterDamageReflected[10] = {};
const int iaPrsT23Duration[10] = {};

const int iaPrsT24FormulaBasedLifeRecovery[10] = {};
const int iaPrsT24AttackPowerBasedLifeRecovery[10] = {};

//T3
const int iaPrsT31AttackRatingBoost[10] = {};
const int iaPrsT31DamageBoost[10] = {};

const int iaPrsT32AttainableSuccessRate[10] = {};
const int iaPrsT32MaxPlayersResurrected[10] = {};

const int iaPrsT33AttainableSuccessRate[10] = {};
const int iaPrsT33MonsterHealthReduction[10] = {};

const int iaPrsT34IncreaseLife[10] = {};
const int iaPrsT34Duration[10] = {};

//T4

const MinMax saPrsT41AttackPower[10] = {};
const int iaPrsT41AttackRange[10] = {};
const int iaPrsT41Duration[10] = {};

const int iaPrsT42AddHPRegen[10] = {};
const int iaPrsT42AddMPRegen[10] = {};
const int iaPrsT42Duration[10] = {};
const int iaPrsT42Range[10] = {};

const int iaPrsT43DamageBoost[10] = {};
const int iaPrsT43NumberofBolts[10] = {};
const int iaPrsT43Range[10] = {};

const int iaPrsT44Damage[10] = {};
const MinMax saPrsT44AttackPower[10] = {};
const int iaPrsT44LifeReduction[10] = {};
const int iaPrsT44AttackDelay[10] = {};
const int iaPrsT44AddUndeadAbsorption[10] = {};
const int iaPrsT44AddEvasion[10] = {};
const int iaPrsT44Duration[10] = {};

enum ESkillType
{
	SKILLTYPE_Undefined = 0,

	SKILLTYPE_Right = 0x01000000,
	SKILLTYPE_Left = 0x02000000,
	SKILLTYPE_All = 0x03000000,
	SKILLTYPE_Passive = 0x04000000,
};
enum ESkillID
{
	SKILLID_DefaultAttack		= 0x11111111,

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
	SKILLID_PhysicalAbsorb			= 0x01010003,
	SKILLID_PoisonAttribute			= 0x01010004,

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
	SKILLID_HardeningShield			= 0x01100003,
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

	SKILLID_SummonTiger				= 0x06100001,
	SKILLID_GoldenApple				= 0x06100002,
	SKILLID_PlagueJavelin			= 0x06100003,
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

namespace SKILL
{
	struct SkillBase
	{
		std::string strName;
		std::string strDescription;
		int iSkillLevelRequired;
		int iaSkillUseStamina[2];
		int iaSkillMastery[2];
		int iaSkillElements[3];
		EItemType eSkillItemAllowed[8];
		DWORD dwFunctionPointer;
		ESkillID eSkillID;
		ESkillType eSkillType;
		DWORD dwUseManaPointer;
		int iSkillIndex;
	};
	class SkillData
	{
	public:
		BOOL IsActiveSkill();
		BOOL IsPassiveSkill();
		BOOL IsDebuffSkill();
		BOOL IsBuffSkill();
		BOOL IsSummonSkill();
	public:
		std::string strName;
		ESkillID eID;
		std::string strFileName;
		std::string strIconName;
		BOOL bActive;
		BOOL bCanUse;
		int iLevel;
		int iShortKey;
		int iMousePosition;
		int iPosition;
		int iUseTime;
		int iCheckTime;
		int iGageLength1;
		int iGageLength2;
		int iMastery;
		int iUseSkillIncreCount;
		int iUseSkillCount;
		int iUseSkillMastery;
		int iUseSkillMasteryGage;
		int iUseSkillFlag;
		int iPlusState[5];
		int iTime[2];
		int iPartyFlag;
		int iElementIndex;
		int iMatIcon;
		int iIconAlpha;
		int iIconPosition;
		int iIconTime;
		int iIconFlag;

		DWORD dwSkillTarget;
		int iSummonFlag;

		SkillBase sSkillInfo;
	};
}
