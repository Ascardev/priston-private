/*----------------------------------------------------------------------------*
*	ÆÄÀÏ¸í :  Morayion.h	
*	ÇÏ´ÂÀÏ :  ¸ğ¶óÀÌ¿ÂÀÇ ½ºÅ³ Çì´õ
*	ÀÛ¼ºÀÏ :  ÃÖÁ¾¾÷µ¥ÀÌÆ® 9¿ù
*	Àû¼ºÀÚ :  ¹Ú»ó¿­ 
*-----------------------------------------------------------------------------*/	
#define MAX_CONTINUE_SKILL		10

//////////////// °øÅëÀû¿ëºÎºĞ
int sinCheckSkillUseOk(sSKILL *lpSkill);
int sinUseManaStamina(sSKILL *lpSkill);
int sinContinueSkillSet(sSKILL *lpSkill,int Flag = 0);
int sinCheckContinueSkill();
int sinSwitchSkill(sSKILL *pSkill);

//ÓÎÏÀ
int F_Sword_Blast();
int F_HolyBody();	
int F_Physical_Traning();
int F_Double_Crash();	

int F_Holy_Valor();
int F_Brandish();
int F_Piercing();
int F_Drastic_Spirit();

int F_S_Mastery();
int F_D_Inhalation();
int F_Holy_Incantation();
int F_Grand_Cross();

int F_Divine_Piercing();
int F_Godly_Shield();
int F_God_Bless();
int F_Sword_Of_Justice();

int F_S_Breaker();
int F_C_Moon();
int F_S_Blade();
int F_H_Benedic();

//Ä§Ç¹ÊÖ
int F_S_Strike();
int F_Farina();
int F_D_Mastery();
int F_V_Spear();

int F_Windy();
int F_Twist_Javelin();
int F_Soul_Sucker();
int F_Fire_Javelin();

int F_Split_Javelin();
int F_T_Of_Valhalla();
int F_Lightning_Javelin();
int F_Storm_Javelin();

int F_Hall_Of_Valhalla();
int F_X_Rage();
int F_Frost_Javelin();
int F_Vengeance();

int F_Talaria();
int F_G_Coup();
int F_S_Arcuda();
int F_S_Fear();

//¼ÀË¾
int F_Healing();
int F_HolyBolt();
int F_M_Spark();
int F_HolyMind();

int F_Meditation();
int F_Divine_Lightning();
int F_Holy_Reflection();
int F_Grand_Healing();

int F_Vigor_Ball();
int F_Resurrection();
int F_Extinction();
int F_Virtual_Life();

int F_Glacial_Spike();
int F_Regeneration_Field();
int F_Chain_Lightning();
int F_Summon_Muspell();

int F_S_Impact();
int F_P_Ice();
int F_S_Ramiel();
int F_B_Krishna();

//Ä§·¨Ê¦
int F_Agony();
int F_FireBolt();
int F_Zenith();
int F_ZenithFromServer(int Time);
int F_FireBall();

int F_Mental_Mastery();
int F_Watornado();
int F_Enchant_Weapon();
int F_Dead_Ray();

int F_Energy_Shield();
int F_Diastrophism();
int F_Spirit_Elemental();
int F_D_Sword();

int F_Fire_Elemental();
int F_Flame_Wave();
int F_Distortion();
int F_Meteo();

int F_Silraphim();
int F_V_Tenus();
int F_P_Ignis();
int F_T_Anima();

//ÈøÂú
int F_Dark_Bolt();
int F_Dark_Wave();
int F_Inertia();
int F_Inner_Peace();
int F_Spiritual_Flare();
int F_Spiritual_Manacle();
int F_Chasing_Hunt();
int F_Advent_Migal();
int F_Rainmaker();
int F_Phantom_Call();
int F_Haunt();
int F_Scratch();
int F_Crimson_Knight();
int F_Judgement();
int F_Advent_Midranda();
int F_Mourning_pray();
int F_Creed();
int F_Press();
int F_Phantom_Nail();
int F_Occult_Life();

/////////////// ³ªÀÌÆ®
//½º¿öµå ºí·¹½ºÆ®
extern int Sword_Blast_UseMana[10];
extern int Sword_Blast_Damage[10][2];
extern int Sword_Blast_ShootingRange[10];

//È¦¸® ¹Ùµğ
extern int HolyBody_UseMana[10];
extern int HolyBody_Absorb[10];
extern int HolyBody_Time[10];

//ÇÇÁöÄÃ Æ®·¹ÀÌ´×
extern int P_Traning_Stamina[10];

//´õºí Å©·¡½¬
extern int D_Crash_UseMana[10];
extern int D_Crash_Damage[10];
extern int D_Crash_Critical[10];

//È¦¸® º§·¯ 
extern int Holy_Valor_Damage[10];
extern int Holy_Valor_Time[10];
extern int Holy_Valor_Mana[10];

//ºê·»µğ½¬
extern int Brandish_Range[10];
extern int Brandish_Damage[10];
extern int Brandish_Mana[10];

//ÇÇ¾î½Ì
extern int Piercing_Damage[10];
extern int Piercing_Range[10];
extern int Piercing_Mana[10];

//µå·¹½ºÆ½ ½ºÇÇ¸´
extern int Drastic_Spirit_Defense[10];
extern int Drastic_Spirit_Time[10];
extern int Drastic_Spirit_Mana[10];

//½º¿öµå ¸¶½ºÅÍ¸®
//extern int Flame_Brandish_Damage[10][2];
//extern int Flame_Brandish_UseMana[10];
extern int Sword_Mastery_DamagePercent[10];

//µğ¹ÙÀÎ ÀÎÈ¦·¹ÀÌ¼Ç
extern int D_Inhalation_Life[10];
extern int D_Inhalation_Block[10];
extern int D_Inhalation_Time[10];
extern int D_Inhalation_UseMana[10];

//È¦¸® ÀÎÄËÅ×ÀÌ¼Ç
extern int H_Incantation_Success[10];
extern int H_Incantation_AddLife[10];
extern int H_Incantation_Time[10];
extern int H_Incantation_UseMana[10];

//±×·£µå Å©·Î½º
extern int Grand_Cross_Damage[10];
extern int Grand_Cross_AttackRate[10];
extern int Grand_Cross_UndeadDamage[10];
extern int Grand_Cross_UseMana[10];

//4Â÷ ½ºÅ³
//µğ¹ÙÀÎ ÇÇ¾î½Ì
extern int  Divine_Piercing_DamagePercent[10];
extern int  Divine_Piercing_AddHit[10];
extern int	Divine_Piercing_AttackNum[10];
extern int  Divine_Piercing_UseMana[10];

//°«µé ½¯µå
extern int Godly_Shield_AbsorbPercent[10];
extern int Godly_Shield_Time[10];
extern int Godly_Shield_UseMana[10];

//°« ºí·¹½º
extern int God_Bless_AddDamage[10];
extern int God_Bless_Time[10];
extern int God_Bless_UseMana[10];

//½º¿öµå ¿Àºê Àú½ºÆ½½º
extern int Sword_Of_Justice_DamagePercent[10];
extern int Sword_Of_Justice_Area[10];
extern int Sword_Of_Justice_UseMana[10];


/////////// ¾ÆÆ²¶õÅ¸
//½¯µå ½ºÆ®¶óÀÌÅ©
extern int S_Strike_UseMana[10];
extern int S_Strike_Damage[10][2];
//extern int S_Strike_Stun[10]; ÇöÁ¦ ¹Ì»ç¿ë

//ÆÄ¸®³ª
extern int Farina_UseMana[10];
extern int Farina_Speed[10];
extern int Farina_AttackRate[10];

//µå·ÎÀ®¸¶½ºÅÍ¸®
extern int T_Mastery_Damage[10];

//ºñ°Å ½ºÇÇ¾î
extern int V_Spear_UseMana[10];
extern int V_Spear_Damage[10][2];

//À©µğ
extern int Windy_Attack_Rating[10];
extern int Windy_Time[10];      
extern int Windy_Mana[10];     

//Æ®À§½ºÆ® Àçºí¸°
extern int Twist_Javelin_Damage[10];
extern int Twist_Javelin_Attack_Rating[10];
extern int Twist_Javelin_Mana[10];      

//¼Ò¿ï ½âÄ¿
extern int Soul_Sucker_Absorb[10];  
extern int Soul_Sucker_Mana[10];    

//ÆÄÀÌ¾î Àçºí¸°
extern int Fire_Javelin_Damage[10][2];
extern int Fire_Javelin_Mana[10];

//½ºÇÃ¸´ Àçºí¸°
extern int Split_Javelin_AttackNum[10];
extern int Split_Javelin_Damage[10];
extern int Split_Javelin_AttackRate[10];
extern int Split_Javelin_UseMana[10];

//Æ®¶óÀÌ¾öÇÁ ¿Àºê ¹ßÇÒ¶ó
extern int T_Of_Valhalla_Damage[10];
extern int T_Of_Valhalla_Time[10];
extern int T_Of_Valhalla_UseMana[10];

//¶óÀÌÆ®´× ÀÚº§¸°
extern int Lightning_Javelin_Damage[10][2];
extern int Lightning_Javelin_UseMana[10];

//½ºÅè ÀÚº§¸°
extern int Storm_Javelin_Damage[10];
extern int Storm_Javelin_UseMana[10];

//4Â÷ ½ºÅ³
//Çï¿Àºê ¹ßÇÒ¶ó
extern int Hall_Of_Valhalla_AddEvation[10];  //Ãß°¡ È¸ÇÇ·Â »ó½Â
extern int Hall_Of_Valhalla_Time[10];        //À¯Áö½Ã°£
extern int Hall_Of_Valhalla_UseMana[10];

//¿¢½º ¶óÁö
extern int X_Rage_DamagePercent[10];   //°ø°İ·Â °¡Áß
extern int X_Rage_Area[10];            //°ø°İ ¹üÀ§
extern int X_Rage_UseMana[10];

//ÇÁ·Î½ºÆ® Àçºí¸°
extern int Frost_Javelin_IceAddDamage[10][2];
extern int Frost_Javelin_SpeedSubPercent[10];
extern int Frost_Javelin_IceTime[10];
extern int Frost_Javelin_Time[10];
extern int Frost_Javelin_UseMana[10];


//º¥Ã¾½º
extern int Vengeance_DamagePercent[10];
extern int Vengeance_AddCritical[10];
extern int Vengeance_Range[10];
extern int Vengeance_UseMana[10];

// ÇáÎè·ÉÑï
extern int Talaria_MoveSpeed[10];
extern int Talaria_Time[10];
extern int Talaria_UseMana[10];
// ĞÇÓê±êÇ¹
extern int G_Coup_Damage[10];
extern int G_Coup_Hit[10];
extern int G_Coup_UseMana[10];
// ±¿±¿ĞÜ
extern int S_Arcuda_Damage[10][2];
extern int S_Arcuda_AtkRating[10];
extern int S_Arcuda_PetHp[10];
extern int S_Arcuda_Defanse[10];
extern int S_Arcuda_UseMana[10];
// ÁÒÑæÍ»Ï®
extern int S_Fear_Damage[10];
extern int S_Fear_AddCritical[10];
extern int S_Fear_UseMana[10];


////////////ÇÁ¸®½ºÆ¼½º
//Èú¸µ
extern int Healing_UseMana[10];
extern int Healing_Heal[10][2];

//È¦¸® º¼Æ®
extern int HolyBolt_UseMana[10];
extern int HolyBolt_Damage[10][2];

//¸ÖÆ¼½ºÆÄÅ©
extern int M_Spark_UseMana[10];
extern int M_Spark_Damage[10][2];
extern int M_Spark_Num[10];


//È¦¸® ¸¶ÀÎµå
extern int HolyMind_UseMana[10];
extern int HolyMind_DecDamage[10];
extern int HolyMind_Time[10];

//¸ŞµğÅ×ÀÌ¼Ç
extern float Meditation_Regen[10];

//µğ¹ÙÀÎ ¶óÀÌÆ®´×
extern int Divine_Lightning_Damage[10][2];
extern int Divine_Lightning_Num[10];
extern int Divine_Lightning_Mana[10];

//È¦¸® ¸®ÇÃ·º¼Ç
extern int Holy_Reflection_Return_Damage[10];
extern int Holy_Reflection_Time[10];
extern int Holy_Reflection_Mana[10];

//±×·£µå Èú¸µ
extern int Grand_Healing[10][2];
extern int Grand_Healing_Range[10];
extern int Grand_Healing_Mana[10];

//ºñ°Å º¼
extern int Vigor_Ball_Damage[10][2];
extern int Vigor_Ball_UseMana[10];

//¸®Á®·º¼Ç
extern int Resurrection_Percent[10];
extern int Resurrection_Exp[10];
extern int Resurrection_UseMana[10];

//ÀÍ½ºÆÃ¼Ç
extern int Extinction_Percent[10];
extern int Extinction_Amount[10];
extern int Extinction_UseMana[10];

//¹öÃß¾ó ¶óÀÌÇÁ
extern int Virtual_Life_Percent[10];
extern int Virtual_Life_Time[10];
extern int Virtual_Life_UseMana[10];

//4Â÷ ½ºÅ³
//±Û·¡ÀÌ¼Å ½ºÆ®¶óÀÌÅ©
extern int Glacial_Spike_Damage[10][2];       //°ø°İ·Â
extern int Glacial_Spike_Area[10];            //°ø°İ ¹üÀ§      
extern int Glacial_Spike_UseMana[10]; 

//¸®Á¦³Ê·¹ÀÌ¼Ç ÇÊµå
extern float Regeneration_Field_LifeRegen[10];   //Ã¼·Â Àç»ı·Â Ãß°¡
extern float Regeneration_Field_ManaRegen[10];   //±â·Â Àç»ı·Â Ãß°¡
extern int   Regeneration_Field_Time[10];        //Áö¼Ó½Ã°£
extern int   Regeneration_Field_Area[10];        //À¯È¿¹üÀ§
extern int   Regeneration_Field_UseMana[10];

//Ã¼ÀÎ¶óÀÌÆ®´×
extern int Chain_Lightning_Damage[10][2];           //°ø°İ·Â
extern int Chain_Lightning_Num[10];                 //¿¬°á °¹¼ö
extern int Chain_Lightning_Range[10];               //¿¬°á °Å¸®
extern int Chain_Lightning_UseMana[10];

//¼­¸ó ¹Â½ºÆç
extern int Summon_Muspell_Damage[10][2];
extern int Summon_Muspell_Attack_Delay[10];			// °ø°İµô·¹ÀÌ
extern int Summon_Muspell_UndeadAbsorbPercent[10];  //¾ğµ¥µåÀÇ °ø°İ·Â Èí¼öÄ¡
extern int Summon_Muspell_BlockPercent[10];         //À¯Àú ºí·ÏÀ²
extern int Summon_Muspell_Time[10];					//À¯Áö½Ã°£
extern int Summon_Muspell_UseMana[10];   

/////////////¸ŞÁö¼Ç
//¾î°í´Ï
extern int Agony_UseMana[10];
extern int Agony_ConvLife[10];

//ÆÄÀÌ¾î º¼Æ®
extern int FireBolt_UseMana[10];
extern int FireBolt_Damage[10][2];

//Á¦´Ï¾²
extern int Zenith_UseMana[10];
extern int Zenith_Element[10];
extern int Zenith_Time[10];


//ÆÄÀÌ¾î º¼
extern int FireBall_UseMana[10];
extern int FireBall_Damage[10][2];
extern int FireBall_Range[10];
extern int FireBall_Area[10];

//¿¡³ÊÁö ½©ÅÍ
extern int Mental_Mastery_Mana[10];
//extern int Energy_Shelter_Down_Damage[10];
//extern int Energy_Shelter_Time[10];
//extern int Energy_Shelter_Mana[10];

//¿öÅä³×ÀÌÅä
extern int Watornado_Damage[10][2];
extern int Watornado_Range[10];
extern int Watornado_Mana[10];
extern int Watornado_Area[10];

//ÀÎÇî½º ¿şÆù
extern int Enchant_Weapon_Damage_Ice[10][2];
extern int Enchant_Weapon_Damage_Fire[10][2];
extern int Enchant_Weapon_Damage_Lightning[10][2];
extern int Enchant_Weapon_Time[10];
extern int Enchant_Weapon_Mana[10];

//µ¥µå ·¹ÀÌ
extern int Dead_Ray_Damage[10][2];
extern int Dead_Ray_Range[10];
extern int Dead_Ray_Mana[10];

//¿¡³ÊÁö ½¯µå
extern int Energy_Shield_DecDamage[10];
extern int Energy_Shield_Time[10];
extern int Energy_Shield_UseMana[10];

//´ÙÀÌ¿¡ ½ºÆ®·¯ÇÇÁò
extern int Diastrophism_Damage[10][2];
extern int Diastrophism_Area[10];
extern int Diastrophism_UseMana[10];

//½ºÇÇ¸´ ¿¤·¹¸àÅ»
extern float Spirit_Elemental_RegenMana[10];
extern int Spirit_Elemental_Damage[10];
extern int Spirit_Elemental_Time[10];
extern int Spirit_Elemental_UseMana[10];

//´í½Ì ½º¿öµå
extern int Dancing_Sword_IceDamage[10][2];
extern int Dancing_Sword_FireDamage[10][2];
extern int Dancing_Sword_AttackDelay[10];
extern int Dancing_Sword_Time[10];
extern int Dancing_Sword_UseMana[10];

//**4Â÷ ½ºÅ³

//ÆÄÀÌ¾î ¿¤·¹¸àÅ» 
extern int Fire_Elemental_Damage[10][2];  //¿¤·¹¸àÅ¸ °ø°İ·Â
extern int Fire_Elemental_Hit[10];        //¸íÁß·Â
extern int Fire_Elemental_Life[10];       //»ı¸í·Â
extern int Fire_Elemental_UseMana[10];

//ÇÃ·¹ÀÓ ¿şÀÌºê
extern int Flame_Wave_FireDamage[10][2];	  //ºÒ °ø°İ·Â
extern int Flame_Wave_Area[10];			      //°ø°İ ¹üÀ§
extern int Flame_Wave_UseMana[10];

//µğ½ºÆ®·Ï¼Ç
extern int Distortion_SpeedSubPercent[10];    //¼Óµµ ÀúÇÏ 
extern int Distortion_DamageSubPercent[10];   //°ø°İ·Â ÀúÇÏ
extern int Distortion_Area[10];     
extern int Distortion_Time[10];
extern int Distortion_UseMana[10];   

//ÕÙ»½ÔÉÊ¯
extern int Meteo_Damage[10][2];
extern int Meteo_Area[10];
extern int Meteo_UseMana[10];

// Á÷ĞÇ»ğÓê
extern int Silraphim_Damage[10][2];
extern int Silraphim_Range[10];
extern int Silraphim_UseMana[10];
//ËõĞ¡Ö®Êõ
extern int V_Tenus_SubSpeed[10];
extern int V_Tenus_Time[10];
extern int V_Tenus_Range[10];
extern int V_Tenus_UseMana[10];
// ÉñÊ¥Ï´Àñ
extern int P_Ignis_Dmage[10][2];
extern int P_Ignis_Area[10];
extern int P_Ignis_Hit[10];
extern int P_Ignis_UseMana[10];
//ÉñÊ¥·¨Õó
extern int T_Anima_Dmage[10];
extern int T_Anima_Time[10];
extern int T_Anima_UseMana[10];

//ÉñÁ¦³å´Ì
extern int S_Breaker_Damage[10];
extern int S_Breaker_AddHit[10];
extern int S_Breaker_UseMana[10];
//ÉıÁúÖØ»÷
extern int C_Moon_Damage[10];
extern int C_Moon_Area[10];
extern int C_Moon_UseMana[10];
//ÉÏµÛÖØ»÷
extern int S_Blade_Damage[10];
extern int S_Blade_UndeadDamage[10];
extern int S_Blade_UseMana[10];
//ÍöÁéÖ®Öä
extern int H_Benedic_Hit[10];
extern int H_Benedic_Time[10];
extern int H_Benedic_UseMana[10];


// ÇáÎè·ÉÑï
extern int Talaria_Time[10];
extern int Talaria_UseMana[10];
// ĞÇÓê±êÇ¹
extern int G_Coup_UseMana[10];
// ±¿±¿ĞÜ
extern int S_Arcuda_UseMana[10];
// ÁÒÑæÍ»Ï®
extern int S_Fear_UseMana[10];


// ÉñÊ¥µç²¨
extern int S_Impact_Damage[10][2];
extern int S_Impact_Range[10];
extern int S_Impact_UseMana[10];
// ÉñÖ®±ùÈĞ
extern int P_Ice_Damge[10][2];
extern int P_Ice_Frozen[10];
extern int P_Ice_UseMana[10];
// ±©·çÑ©
extern int S_Ramiel_Damage[10][2];
extern int S_Ramiel_Area[10];
extern int S_Ramiel_Num[10];
extern int S_Ramiel_UseMana[10];
// ÌìÅ®É¢»¨
extern int B_Krishna_Evasion[10];
extern int B_Krishna_Abs[10];
extern int B_Krishna_Time[10];
extern int B_Krishna_UseMana[10];


// Á÷ĞÇ»ğÓê
extern int Silraphim_UseMana[10];
// ËõĞ¡Ö®Êõ
extern int V_Tenus_UseMana[10];
// ÉñÊ¥Ï´Àñ
extern int P_Ignis_UseMana[10];
// ÉñÊ¥·¨Õó
extern int T_Anima_Time[10];
extern int T_Anima_UseMana[10];

//°µºÚÉÁµç
extern int Dark_Bolt_Damage[10];
extern int Dark_Bolt_UseMana[10];

//°µºÚ²¨ÀË
extern int Dark_Wave_Damage[10];
extern int Dark_Wave_UseMana[10];

//×çÖäÀ×»÷
extern int Inertia_Speed[10];
extern int Inertia_Atk[10];
extern int Inertia_Area[10];
extern int Inertia_Time[10];
extern int Inertia_UseMana[10];

//ÄÚĞÄÆ½ºÍ
extern int Inner_Peace_AddMana[10];

//¾«ÉñÖäÊõ
extern int Spiritual_Flare_Damage[10];
extern int Spiritual_Flare_Rnage[10];
extern int Spiritual_Flare_Area[10];
extern int Spiritual_Flare_UseMana[10];

//Áé»ê¼ÏËø
extern int Spiritual_Manacle_Ratio[10];
extern int Spiritual_Manacle_Time[10];
extern int Spiritual_Manacle_UseMana[10];

//ÁÔÈ¡
extern int Chasing_Hunt_Sight[10];
extern int Chasing_Hunt_Time[10];
extern int Chasing_Hunt_UseMana[10];

//Âõ¿Ë¶û
extern int Advent_Migal_Atk[10];
extern int Advent_Migal_Time[10];
extern int Advent_Migal_UseMana[10];

//ÆíÓêÊ¦
extern int Rainmaker_Abs[10];
extern int Rainmaker_AtkRating[10];
extern int Rainmaker_Time[10];
extern int Rainmaker_UseMana[10];

//Â½µØÁé»ê
extern int Phantom_Call_Damage[10];
extern int Phantom_Call_Area[10];
extern int Phantom_Call_UseMana[10];

//¹í»êÖØ»Ø
extern int Haunt_Damage[10];
extern int Haunt_Abs[10];
extern int Haunt_UseMana[10];

//×¥ÆÆ
extern int Scratch_Damage[10];
extern int Scratch_UseMana[10];

//ÊÈÑªÖ®Ò¹
extern int Crimson_Knight_Atk[10][2];
extern int Crimson_Knight_AtkRating[10];
extern int Crimson_Knight_PetHp[10];
extern int Crimson_Knight_Defanse[10];
extern int Crimson_Knight_UseMana[10];

//ÉóÅĞ
extern int Judgement_Damage[10];
extern int Judgement_UseMana[10];

//Ã×µÂÀ¼´ï
extern int Advent_Midranda_Speed[10];
extern int Advent_Midranda_Area[10];
extern int Advent_Midranda_Time[10];
extern int Advent_Midranda_UseMana[10];

//ĞñÈÕ¶«Éı
extern int Mourning_Pray_Damage[10];
extern int Mourning_Pray_Area[10];
extern int Mourning_Pray_UseMana[10];

//ÖäÊõĞÅÑö
extern int Creed_AddMP[10];
extern int Creed_AddSP[10];
extern int Creed_Time[10];
extern int Creed_UseMana[10];

//×çÖäÖ®Á¦
extern int Press_Deity_Damage[10];
extern int Press_Deity_Area[10];
extern int Press_UseMana[10];

//ËÀÍöÖ®×¦
extern int Phantom_Nail_Damage[10];
extern int Phantom_Nail_Area[10];
extern int Phantom_Nail_UseMana[10];

//¸ß¼¶ÔÙÉı
extern int Occult_Lift_HP[10];
