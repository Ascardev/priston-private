#define SIN2_ATTACK_RATE		0
#define SIN2_DAMAGE				1
#define SIN2_DEFENSE			2
#define SIN2_ABSORB				3
#define SIN2_SPEED				4
#define SIN2_LIFE				5
#define SIN2_MANA				6
#define SIN2_STAMINA			7

#define USE_SKILL_MASTERY_COUNT	100


int RequireStateCheck(int Mana);
int ContinueSkillUse(sSKILL *pSkill,int Time);
void CheckContinueSkill();
void SwitchSkill(sSKILL *pSkill);

//////////////// »úÐµ
int F_Extreme_Shield();
int F_Mechanic_Bomb();
int F_Physical_Absorption();
int F_Poison_Attribute();

int F_Great_Smash();
int F_Maximize();
int F_Automation();
int F_Spark();

int F_Metal_Armor();
int F_Grand_Smash();
int F_M_W_Mastery();
int F_Spark_Shield();

int F_Impulsion();
int F_Compulsion();
int F_Magnetic_Sphere();
int F_Metal_Golem();

int F_landminning();
int F_H_Sonic();
int F_R_Smash();
int F_P_Enhence();

//////////////// ÎäÊ¿
int F_Melee_Mastery();
int F_Fire_Attribute();
int F_Raving();
int F_Impact();

int F_Triple_Impact();
int F_Brutal_Swing();
int F_Roar();
int F_RageOfZecram();

int F_Concentration();
int F_Avanging_Crash();
int F_Swift_Axe();
int F_Bone_Crash();

int F_Destoryer();
int F_Berserker();
int F_Cyclone_Strike();
int F_Boost_Health();

int F_D_Hit();
int F_P_Dash();
int F_M_Blow();
int F_B_Berserker();

//////////////// Ç¹±ø
int F_Pike_Wind();
int F_Ice_Attribute();
int F_Critical_Hit();
int F_Jumping_Crash();

int F_Ground_Pike();
int F_Tornado_Pike();
int F_Weapone_Defence_Mastery();
int F_Expansion();

int F_Venom_Spear();
int F_Vanish();
int F_Critical_Mastery();
int F_Chain_Lance();

int F_Assassin_Eye();
int F_Charging_Strike();
int F_Vague();
int F_Shadow_Master();

int F_D_Reaper();
int F_F_Spear();
int F_Amplified();
int F_SS_Attack();

//////////////// ¹­ÊÖ
int F_Scout_Hawk();
int F_Shooting_Mastery();
int F_Wind_Arrow();
int F_Perfect_Aim();

int F_Dions_Eye();
int F_Falcon();
int F_Arrow_of_Rage();
int F_Avalanche();

int F_E_Shot();
int F_G_Falcon();
int F_B_Shot();
int F_Perforation();

int F_Recall_Wolverin();
int F_Evasion_Mastery(); 
int F_Phoenix_Shot();
int F_Force_Of_Nature();

int F_S_Shot();
int F_S_Rope();
int F_N_Splash();
int F_C_Trap();

// ´Ì¿Í
int F_Stringer();
int F_Running();
int F_Sword_Mastery();
int F_Wisp();
int F_Verom_Thorn();
int F_Ales();
int F_Soul_Shock();
int F_Blade_Mastery();
int F_Finishing_Blow();
int F_Gust_Shash();
int F_Inpes();
int F_Deception();
int F_Frost_Wind();
int F_Fatal_Mastery();
int F_Pollute();
int F_Shadow();
int F_Shadow_Bomb();
int F_Rising_Shash();
int F_Violent_Stub();
int F_Shadow_Storm();

extern int E_Shield_BlockRate[10];
extern int E_Shield_UseTime[10];
extern int E_Shield_UseMana[10];

extern int Mechanic_Bomb_Damage[10][2];
extern int Mechanic_Bomb_Attack_Range[10];
extern int Mechanic_Bomb_UseMana[10];

extern int P_Absorb[10];
extern int P_Absorb_UseTime[10];
extern int P_Absor_bUseMana[10];

extern int PlusPoison[10];

extern int G_Smash_Attack_Rate[10];
extern int G_Smash_Attack_Rage[10];
extern int G_Smash_UseMana[10];

extern int Maximize_Damage[10];
extern int Maximize_Weapon_Speed[10];
extern int Maximize_Time[10]; 
extern int Maximize_UseMana[10];

extern int Automation_Damage[10];
extern int Automation_Speed[10];
extern int Automation_Time[10];
extern int Automation_UseMana[10];

extern int Spark_Damage[10][2];
extern int Spark_Area[10];
extern int Spark_UseMana[10];

extern int Metal_Armor_Defense[10];
extern int Metal_Armor_Time[10];
extern int Metal_Armor_UseMana[10];

extern int Grand_Smash_AttackRate[10];
extern int Grand_Smash_Damage[10];
extern int Grand_Smash_UseMana[10];

extern int M_Weapon_Mastey[10];

extern int Spark_Shield_Damage[10];
extern int Spark_Shield_Defense[10];
extern int Spark_Shield_Time[10];
extern int Spark_Shield_UseMana[10];

extern int Impulsion_LightingDamage[10];
extern int Impulsion_Range[10];
extern int Impulsion_LightingNum[10];
extern int Impulsion_UseMana[10];

extern int Compulsion_AddAbsorb[10];
extern int Compulsion_Area[10];
extern int Compulsion_Time[10];
extern int Compulsion_UseMana[10];

extern int Magnetic_Sphere_AddDamage[10][2];
extern int Magnetic_Sphere_Area[10];
extern int Magnetic_Sphere_AttackDelay[10];
extern int Magnetic_Sphere_Time[10];
extern int Magnetic_Sphere_UseMana[10];

//¸ÞÅ» °ñ·½
extern int Metal_Golem_Damage[10][2];      //°ø°Ý·Â
extern int Metal_Golem_Hit[10];			   //¸íÁß·Â
extern int Metal_Golem_Defense[10];		   //¹æ¾î·Â
extern int Metal_Golem_Life[10];           //»ý¸í·Â
extern int Metal_Golem_UseMana[10];

//Åùö¨Ðý·ç
extern int Landminning_AddDamage[10];
extern int Landminning_Area[10];
extern int Landminning_Num[10];
extern int Landminning_UseMana[10];

//¿ìËÙ´ò»÷
extern int H_Sonic_Speed[10];
extern int H_Sonic_Time[10];
extern int H_Sonic_UseMana[10];

//¾¿¼«Ö®ÈÐ
extern int R_Smash_AddDamage[10];
extern int R_Smash_UseMana[10];

//Õ½Éñ×£¸£
extern int P_Enhence_AddDamage[10][2];
extern int P_Enhence_Defanse[10];
extern int P_Enhence_Time[10];
extern int P_Enhence_UseMana[10];

////////////////////////////ÎäÊ¿¼¼ÄÜ
//¹Ð¸® ¸¶½ºÅÍ¸® 
extern int Melee_Mastery_DamagePercent[10];

//ÆÄÀÌ¾î ¾îÆ®¸®ºäÆ® 
extern int PlusFire[10];

//·¹ÀÌºù 
extern int Raving_Damage[10];
extern int Ravind_Speed[10];
extern float Raving_UseLife[10];
extern int Raving_UseMana[10];

//ÀÓÆåÆ® 
extern int Impact_Attack_Rating[10];
extern int Impact_Damage[10];
extern int Impact_UseMana[10];

//Æ®¸®ÇÃ ÀÓÆåÆ®
extern int T_Impact_Damage[10];
extern int T_Impact_Hit[10];
extern int T_Impact_UseMana[10];

//ºÎ¸£Å» ½ºÀ® 
extern int B_Swing_Damage[10];
extern int B_Swing_Critical[10];
extern int B_Swing_UseMana[10];

//·Î¾î
extern int Roar_Range[10];
extern int Roar_Time[10];
extern int Roar_UseMana[10];

//·¹ÀÌÁö ¿Àºê Á¦Å©¶÷ 
extern int R_Zecram_Damage[10];
extern int R_Zecram_Area[10];
extern int R_Zecram_UseMana[10];

//ÄÁ¼¾Æ®·¹ÀÌ¼Ç
extern int Concentration_AttackRate[10];
extern int Concentration_Time[10];
extern int Concentration_UseMana[10];

//¾îº¥Â¡ Å©·¡½¬
extern int A_Crash_Damage[10];
extern int A_Crash_AttackRate[10];
extern int A_Crash_UseMana[10];

//½ºÀ§ÇÁÆ® ¿¢½º
extern int Swift_Axe_Speed[10];
extern int Swift_Axe_Time[10];
extern int Swift_Axe_UseMana[10];

//º» Å©·¡½¬
extern int B_Crash_Damage[10];
extern int B_Crash_DemonDamage[10];
extern int B_Crash_UseMana[10];

//µð½ºÅä¸®¾î
extern int Destoryer_DamagePercent[10];   //°ø°Ý·Â °¡Áß
extern int Destoryer_AddCritical[10];	   //Å©¸®Æ¼ÄÃ Ãß°¡
extern int Destoryer_UseMana[10];

//¹ö¼­Ä¿
extern int Berserker_AddAttack[10];        //Ãß°¡ °ø°Ý·Â
extern int Berserker_SubAbsorb[10];        //Èí¼ö·Â °¨¼ÒÄ¡
extern int Berserker_Time[10];             //À¯Áö½Ã°£
extern int Berserker_UseMana[10];

//½ÎÀÌÅ¬·Ð ½ºÆ®¶óÀÌÅ©
extern int Cyclone_Strike_DamagePercent[10];      //°ø°Ý·Â °¡Áß
extern int Cyclone_Strike_AttackNum[10];		  //ÃÖ´ë Å¸°Ý¼ö
extern int Cyclone_Strike_Area[10];               //°ø°Ý ¹ü
extern int Cyclone_Strike_UseMana[10];

//º×Æ® Çï½º
extern int Boost_Health_Life[10];//»ý¸í·Â ¿µ±¸Àû Ãß°¡

//¿ñ±©Å­Õ¶
extern int D_Hit_AddDamage[10];
extern int D_Hit_UseMana[10];

//¿ñÒ°³å»÷
extern int P_Dash_AddDamage[10];
extern int P_Dash_Area[10];
extern int P_Dash_Time[10];
extern int P_Dash_UseMana[10];

//»ØÐýÕ¶»÷
extern int M_Blow_AddDamage[10];
extern int M_Blow_AttackNum[10];
extern int M_Blow_Area[10];
extern int M_Blow_UseMana[10];

//ÖÚÉñÖ®Å­
extern int B_Berserker_AddDamage[10];
extern int B_Berserker_Time[10];
extern int B_Berserker_UseMana[10];


///////////////////////////Ç¹±ø¼¼ÄÜ
//ÆÄÀÌÅ© À©µå 
extern int Pike_Wind_Damage[10][2];
extern int Pike_Wind_Push_Lenght[10];
extern int Pike_Wind_Throw_Height[10];
extern int Pike_Wind_UseMana[10];

//¾ÆÀÌ½º ¾îÆ®¸®ºäÆ® 
extern int PlusIce[10];

//Å©¸®Æ¼ÄÃ Èý 
extern int Critical_Hit_Critical[10];
extern int Critical_Hit_UseMana[10];

//Á¡ÇÎ Å©·¡½¬ 
extern int Jumping_Crash_UseMana[10];
extern int Jumping_Crash_Attack_Rating[10];
extern int Jumping_Crash_Damage[10];

//±×¶ó¿îµå ½ºÆÄÀÌÅ© 
extern int G_Pike_Damage[10][2];
extern int G_Pike_Range[10];
extern int G_Pike_UseMana[10];
extern int G_Pike_Time[10];

//Åä³×ÀÌµµ 
extern int Tornado_Damage[10];
extern int Tornado_Stun[10];
extern int Tornado_Range[10];
extern int Tornado_UseMana[10];

//¿þÆù µðÆæ½º ¸¶½ºÅÍ¸® 
extern int W_D_Mastery_Block[10];

//ÆÄ 
extern int Expansion_Size[10];
extern int Expansion_UseMana[10];
extern int Expansion_Damage[10];

//º£³ð ½ºÇÇ¾î
extern int VenomSpear_Damage[10];
extern int VenomSpear_Num[10];
extern int VenomSpear_Time[10];
extern int VenomSpear_Range[10];
extern int VenomSpear_UseMana[10];

extern float Vanish_Speed[10];
extern int Vanish_Damage[10];
extern int Vanish_Range[10];
extern int Vanish_Time[10];
extern int Vanish_UseMana[10];

extern int Critical_Mastery_Critical[10];

extern int Chain_Lance_Damage[10];
extern int Chain_Lance_UseMana[10];

extern int Assassin_Eye_AddCritical[10];
extern int Assassin_Eye_M_SubCritical[10];
extern int Assassin_Eye_Time[10];
extern int Assassin_Eye_UseMana[10];

extern int Charging_Strike_DamagePercent[10];
extern int Charging_Strike_CharingDamagePercent[10];
extern int Charging_Strike_Time[10];
extern int Charging_Strike_UseMana[10];

extern int Vague_EvasionPercent[10];
extern int Vague_Time[10];
extern int Vague_UseMana[10];

extern int Shadow_Master_DamagePercent[10];
extern int Shadow_Master_AddHit[10];
extern int Shadow_Master_ShadowNum[10];
extern int Shadow_Master_UseMana[10];

//»ØÐý´ò»÷
extern int D_Reaper_AddDamage[10];
extern int D_Reaper_UseMana[10];
//µØÇ¹ÆæÏ®
extern int F_Spear_AddDamage[10];
extern int F_Spear_Area[10];
extern int F_Spear_Num[10];
extern int F_Spear_UseMana[10];
//Ç±ÄÜ¼¤·¢
extern int Amplified_SubAbs[10];
extern int Amplified_AddHit[10];
extern int Amplified_MinAddDamage[10];
extern int Amplified_Time[10];
extern int Amplified_UseMana[10];
//Ðý·çÖ®Ç¹
extern int SS_Attack_AddDamage[10];
extern int SS_Attack_UseMana[10];


/////////////////////////////¹­ÊÖ¼¼ÄÜ
//½ºÄ«¿ìÆ® È£Å© 
extern int Scout_Hawk_Attack_Rate[10];
extern int Scout_Hawk_UseTime[10];
extern int Scout_Hawk_UseMana[10];
//½´ÆÃ ¸¶½ºÅÍ¸® 
extern int S_Mastery_DamagePercent[10];
//À©µå ¿¡·Î¿ì 
extern int Wind_Arrow_Speed[10];
extern int Wind_Arrow_Damage[10];
extern int Wind_Arrow_UseMana[10];
//ÆÛÆÑÆ® ¿¡ÀÓ 
extern int Perfect_Aim_Attack_Rate[10];
extern int Perfect_Aim_Damage[10];
extern int Perfect_Aim_Damage_LV[10];
extern int Perfect_Aim_UseMana[10];

//µð¿Â½º ¾ÆÀÌ 
extern int D_Eye_Attack_Rate[10];
//ÆÈÄÜ 
extern int Falcon_Damage[10][2];
extern int Falcon_Time[10];
extern int Falcon_UseMana[10];
//¿¡·Î¿ì ¿Àºê ·¹ÀÌÁö 
extern int A_Rage_ArrowNum[10];
extern int A_Rage_Damage[10];
extern int A_Rage_Area[10];
extern int A_Rage_UseMana[10];
//¿¡º§¶õÃ¼ 
extern int Avalanche_Speed[10];
extern int Avalanche_Damage[10];
extern int Avalanche_ArrowNum[10];
extern int Avalanche_UseMana[10];

//¿¤·¹¸àÅ» ¼¦
extern int Elemental_Shot_Ice[10][2];
extern int Elemental_Shot_Fire[10][2];
extern int Elemental_Shot_Lightning[10][2];
extern int Elemental_Shot_UseMana[10];
//°ñµç ÆÓÄÁ
extern int   Golden_Falcon_Damage[10];
extern float Golden_Falcon_LifeRegen[10];
extern int   Golden_Falcon_Time[10];
extern int   Golden_Falcon_UseMana[10];
//¹ü ¼¦
extern int BombShot_Damage[10];
extern int BombShot_DemonDamage[10];
extern int BombShot_AddDamage[10][2];
extern int BombShot_Area[10];
extern int BombShot_UseMana[10];
//ÆÛÆ÷·¹ÀÌ¼Ç
extern int Perforation_Damage[10];
extern int Perforation_Critical[10];
extern int Perforation_UseMana[10];
extern int Perforation_Attack_Range[10];

extern int Recall_Wolverin_Damage[10][2];
extern int Recall_Wolverin_Hit[10];
extern int Recall_Wolverin_Defense[10];
extern int Recall_Wolverin_Life[10];
extern int Recall_Wolverin_UseMana[10];

extern int Evasion_Mastery_AddPercent[10];

extern int   Phoenix_Shot_DamagePercent[10];
extern int   Phoenix_Shot_Time[10];
extern int   Phoenix_Shot_UseMana[10];

extern int Force_Of_Nature_AddDamage[10];
extern int Force_Of_Nature_AddHit[10];
extern int Force_Of_Nature_FalconAddDamage[10];
extern int Force_Of_Nature_Time[10];
extern int Force_Of_Nature_UseMana[10];
//»ØÐýÖ®Îè
extern int E_Shot_Damge[10];
extern int E_Shot_Range[10];
extern int E_Shot_UseMana[10];
//Ðþ¹âÖ®¼ý
extern int S_Rope_Damge[10];
extern int S_Rope_AddRange[10];
extern int S_Rope_UseMana[10];
//ì«·çÖ®¼ý
extern int N_Splash_Damge[10];
extern int N_Splash_Range[10];
extern int N_Splash_UseMana[10];
//¸´³ð¼ýÓê
extern int C_Trap_Dmage[10];
extern int C_Trap_Area[10];
extern int C_Trap_UseMana[10];



//½ºÅ³ ½Àµæ½Ã »ç¿ëµÇ´Â µ· 
extern int sinMasterSkill_Money[SKILL_POINT_COLUM_MAX];
extern int sinMasterSkill_PlusMoney[SKILL_POINT_COLUM_MAX];


// ½ºÅ³ ½Àµæ½Ã ÄÃ·¯ »öÀ» ¹Ù²Û´Ù 
extern int SkillTextColor[10];

//¿ä±¸Ä¡¸¦ ÃæÁ·¸øÇßÀ»°æ¿ì¿¡´Â È¿°ú¸¦ ÁØ´Ù 
extern int NotUseSkillElement[3];	//¿ä±¸Ä¡ ÃæÁ· ÇÃ·º 
extern int sinMasteryIncreaIndex[SKILL_POINT_COLUM_MAX];


//°ø¼ºÀü Å¬·£½ºÅ³ 
extern int C_Skill_HpPoint[10];      //hp »ó½Â
extern int C_Skill_AttPercent[10];   //°ø°Ý·Â »ó½Â
extern int C_Skill_EvaPercent[10];      //È¸ÇÇÀ² »ó½Â


//´Ì¿Í

//´Ì»÷
extern int Stinger_Damage[10];
extern int Stinger_UseMana[10];

//ÉÁ»÷
extern int Running_Hit_Damage[10];
extern int Running_Hit_UseMana[10];

//Ç¿»¯¹¥»÷
extern int Sword_Mastery_Damage[10];

//Èõµã¹¥»÷
extern int Wisp_Damage[10];
extern int Wisp_Range[10];
extern int Wisp_Time[10];
extern int Wisp_UseMana[10];

//¶¾ÑÀÁ¬»÷
extern int Venom_Thorn_Damage[10];
extern int Venom_Thorn_Ratio[10];
extern int Verom_Thorn_Time[10];
extern int Verom_Thorn_UseMana[10];

//Ãô½ÝÖ®Á¦
extern int Alas_Eavsion[10];
extern int Alas_Area[10];
extern int Alas_Time[10];
extern int Ales_UseMana[10];

//Áé»êÕðº³
extern int Soul_Shock_Area[10];
extern int Soul_Shock_Time[10];
extern int Soul_Shock_UseMana[10];

//¹¥»÷´óÊ¦
extern int Blade_Mastery_Attack[10];
extern int Blade_Mastery_Evasion[10];

//·É½£Ö®Îè
extern int Finishing_Blow_Damage[10];
extern int Finishing_Blow_UseMana[10];

//ÌøÕ¶
extern int Gust_Slash_Damage[10];
extern int Gust_Slash_Area[10];
extern int Gust_Shash_UseMana[10];

//Ãô½Ý´óÊ¦
extern int Inpes_Atk_Speed[10];
extern int Inpes_Time[10];
extern int Inpes_UseMana[10];

//ÖÂÃ¤
extern int Deception_Damage[10];
extern int Deception_Visibility[10];
extern int Deception_Time[10];
extern int Deception_UseMana[10];

//±ù¶³Ö®ÈÐ
extern int Frost_Wind_Damage[10];
extern int Frost_Wind_UseMana[10];

//ÖÂÃüÒÕÊõ
extern int Fatal_Mastery_Critical[10];

//ÎÁÒßÖ®ÈÐ
extern int Pollute_Damage[10];
extern int Pollute_Area[10];
extern int Pollute_Ratio[10];
extern int Pollute_Time[10];
extern int Pollute_UseMana[10];

//Ó°×ÓÉÁ»÷
extern int Shadow_Damage[10];
extern int Shadow_UseMana[10];

//Ó°×Ó»ðÑæ
extern int Shadow_Bomb_Damage[10];
extern int Shadow_Bomb_Area[10];
extern int Shadow_Bomb_Ratio[10];
extern int Shadow_Bomb_Time[10];
extern int Shadow_Bomb_UseMana[10];

//µØÁÑÕ¶
extern int Rising_Slash_Damage[10];
extern int Rising_Shash_UseMana[10];

//ÃÍÁú°ÚÎ²
extern int Violent_Stub_Damage[10];
extern int Violent_Stub_UseMana[10];

//·ç±©Ö®ÈÐ
extern int Shadow_Storm_Damage[10];
extern int Shadow_Storm_Area[10];
extern int Shadow_Storm_Range[10];
extern int Shadow_Storm_PushRange[10];
extern int Shadow_Storm_UseMana[10];
