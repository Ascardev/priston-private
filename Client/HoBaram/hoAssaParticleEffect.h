#ifndef _HO_ASSA_PARTICLE_EFFECT_
#define _HO_ASSA_PARTICLE_EFFECT_




//ºñ¾î ÀÖ´Â ¹öÆÛ¸¦ ¸®ÅÏÇÏ´Â ÇÔ¼ö..(ÇÔ¼ö ¾È¿¡¼­ µ¿ÀûÀ¸·Î »ý¼º ÇÏ¸é sinÀÇ ÇÔ¼ö¸¦ °íÃÄ¾ß ÇÏ¹Ç·Î)
int GetAssaEffect();
int	StopAssaCodeEffect(Unit *pChar, int code, int setTime = 0);
bool AddAssaCodeEffectTime(Unit *pChar, int code, int time);
int AddAssaCodeEffectTime(Unit *pChar,int Code);

BOOL GetAssaUseEffect(Unit *pChar, int code);
bool GetAssaContinueSkill(int skillCode);
//¸ðÀÌ´Â ¶óÀÎ ÆÄÆ¼Å¬...
int AssaParticle_LineIn(POINT3D *pPosi , char *texName = NULL, int continueTime = 15, int speed = 0);
int AssaParticle_LineOut(POINT3D *pPosi , char *texName = NULL, int continueTime = 10, int speed = 0);
int AssaParticle_Star(POINT3D *pPosi);

//ÉñÁ¦ÖØ»÷
int AssaParticle_HolyValor_Jang(Unit *pChar);
int AssaParticle_HolyValor_JangEffect(Unit *pChar,int maxTime);
int AssaParticle_HolyValor_Member(Unit *pChar, int maxTime = 0);
int AssaParticle_HolyValorIsUse(Unit *pChar);

//ÌìÓÓÉñîø
int AssaParticle_DrasticSpirit_Jang(Unit *pChar);
int AssaParticle_DrasticSpirit_JangEffect(Unit *pChar,int maxTime);
int AssaParticle_DrasticSpirit_Member(Unit *pChar, int maxTime = 0);

//Valkyrie (Windy, TwistJavelin, FireJavelin)
int AssaParticle_Windy(Unit *pChar, int maxTime = 0);
int AssaParticle_TwistJavelinShot(POINT3D *pPosi, POINT3D *pDesti);
int AssaParticle_FireJavelin(POINT3D *pPosi, POINT3D *pDesti);
int AssaParticle_FireJavelin(Unit *pChar, POINT3D *pDesti);


int AssaParticle_DivineLighting(Unit *pChar);
int AssaParticle_Sprak(POINT3D *pPosi);

//Wizard (ColumnOfWater, EnchantWeapon, DeadLay)
int AssaParticle_ColumnOfWater(POINT3D *pPosi, POINT3D *pDesti, int level = 1);
int AssaParticle_ColumnOfWaterHit(POINT3D *pPosi);

int AssaParticle_EnchantWeaponIceJang(Unit *pChar, int maxTime = 0);
int AssaParticle_EnchantWeaponFireJang(Unit *pChar, int maxTime = 0);
int AssaParticle_EnchantWeaponLightJang(Unit *pChar, int maxTime = 0);


int AssaParticle_EnchantWeaponJinMember(Unit *pChar);
int AssaParticle_EnchantWeaponIceMember(Unit *pChar, int maxTime = 0);
int AssaParticle_EnchantWeaponFireMember(Unit *pChar, int maxTime = 0);
int AssaParticle_EnchantWeaponLightMember(Unit *pChar, int maxTime = 0);

int AssaParticle_LightShot(POINT3D *pPosi, POINT3D *pDesti);
int AssaParticle_FireShot(POINT3D *pPosi, POINT3D *pDesti);
int AssaParticle_IceShot(POINT3D *pPosi, POINT3D *pDesti);

int AssaParticle_LightHit1(POINT3D *pPosi);
int AssaParticle_IceHit1(POINT3D *pPosi);
int AssaParticle_FireHit1(POINT3D *pPosi);
int AssaParticle_FireHit2(POINT3D *pPosi);

int AssaParticle_BigFireHit1(POINT3D *pPosi);

int AssaParticle_DeadLay(POINT3D *pPosi, POINT3D *pDesti);
int AssaParticle_HolyMind_Attack(Unit *pChar, int liveCount);

//int AssaParticle_AgingBody(Unit *pChar);

int StartEffect_Serqbus_Skill1(Unit *pChar, int liveCount);
int StartEffect_Serqbus_Skill2(Unit *pChar, int liveCount);
int StartEffect_Serqbus_Skill3(Unit *pChar, int liveCount);

//Fury °ü·Ã ÀÌÆåÆ®
int AssaParticle_Fury_Eye(Unit *pChar);							//´«¿¡ ºÙ´Â ÀÌÆåÆ®
int AssaParticle_Fury_ShotFire(Unit *pChar, POINT3D *destPos);	//ºÒ½î±â..

int AssaParticle_Fury_RespawnMonster(POINT3D *pPosi);						//¸ó½ºÅÍµé ¼ÒÈ¯..
int AssaParticle_Fury_RespawnBody(Unit *pChar);                  //¸ó½ºÅÍ ¼ÕÈ¯½Ã Ç»¸®ÀÇ ÀÔ¿¡¼­ ³ª¿À´Â ÆÄÆ¼Å¬.
int AssaParticle_Fury_Skill1(Unit *pChar);						//¿µ¿ª °ø°Ý..

int AssaParticle_Fury_Skill1(POINT3D *pPosi, POINT3D *pAngle);      //¿µ¿ª °ø°Ý.. ¿¾³¯ ¹öÀüÀ» À§ÇØ¼­..

//Evil Maple°ü·Ã ÀÌÆåÆ®..
int AssaParticle_EvilMapleShot(Unit *pChar);

//Evil Plant°ü·Ã ÀÌÆåÆ®..
int AssaParticle_EvilPlantShot(Unit *pChar);

void AssaParticle_IceserpentHit(Unit *pChar);

void AssaParticle_IceserpentSkill(Unit *pChar);

//Thorn Crawler°ü·Ã ÀÌÆåÆ®..
int AssaParticle_ThornCrawlerShot(Unit *pChar, POINT3D *destPos);

//Stone Golem°ü·Ã ÀÌÆåÆ®..
int AssaParticle_StoneGolemShot(Unit *pChar);


//Heavy Goblin°ü·Ã ÀÌÆåÆ®..
int AssaParticle_HeavyGoblinHit1(Unit *pChar); //À§¿¡¼­ ³»·ÁÄ¡´Â µ¿ÀÛ
int AssaParticle_HeavyGoblinHit2(Unit *pChar); //¾ç»çÀÌµå¿¡¼­ Ä¡´Â µ¿ÀÛ

//Doom Gurad°ü·Ã ÀÌÆåÆ®..
int AssaParticle_DoomGuardHit1(Unit *pChar); //À§¿¡¼­ ³»·ÁÄ¡´Â µ¿ÀÛ
int AssaParticle_DoomGuardHit2(Unit *pChar); //¾ç»çÀÌµå Ä¡´Â µ¿ÀÛ

//Snail °ü·Ã ÀÌÆåÆ®..
int AssaParticle_SnailShot(Unit *pChar, POINT3D *destPos);

//Night Mare°ü·Ã ÀÌÆåÆ®..
int AssaParticle_NightMare(Unit *pChar);

//Ratoo ÀÌÆå½º
int AssaParticle_RatooHit1(Unit *pChar);

//Monster Ä¡±â
int AssaParticle_Hit1(POINT3D *destPos);


//Spider °Å¹Ì »¯¾î ³»±â
int AssaParticleSpiderSkill1(Unit *pChar);

void AssParticle_UnDeadManger(Unit *pChar,int nSkill);
//±¿±¿ÐÜ¼¼ÄÜ
void AssaParticle_Arcuda(Unit *pChar);
// ÉèÖÃÐ§¹û
void AssaParticle_Effect(char *szName, Unit *pChar,int Kind);
// ¾¿¼«Ö®ÈÐ
void AssaParticle_RollingSmashHit(int x,int y,int z);
void AssaParticle_RollingSmashDown(int x,int y,int z);


void AssaParticle_CastleRed(Unit *pChar);
void AssaParticle_CastleGreen(Unit *pChar);
void AssaParticle_CastleBlue(Unit *pChar);

//ClanMonster ÀÌÆåÆ®
int AssaParticleClanMonster(Unit *pChar);
int AssaParticleClanMonsterHit1(Unit *pChar);
int AssaParticleClanMonsterHit2(Unit *pChar);
int AssaParticle_Sprak1(POINT3D *pPosi);

// ¶ñÄ§²®¾ôÐ§¹û
int AssaParticleTulla(Unit *pChar);

void AssaParticle_BlueMountainHit(Unit *pChar);
void AssaParticle_BlueMountainSkill(Unit *pChar);
void AssaParticle_MorgoniaHit(Unit *pChar);
void AssaParticle_MorgoniaSkill(Unit *pChar);
void AssaParticle_BoneHoundSkill(Unit *pChar);
void AssaParticle_BoneHoundSkillHit(Unit *pChar);

// »áÐÄÒ»»÷
void AssaParticle_ConcentrationStart(Unit *pChar);
void AssaParticle_ConcentrationEffect(Unit *pChar,int liveCount,int SkillCode,int Light = TRUE);
//´ÌÉ±Ö®¸«
void AssaParticle_SwiftAxeStart(Unit *pChar);
void AssaParticle_SwiftAxeEffect(Unit *pChar,int liveCount,int SkillCode,int Light = TRUE);

void AssaParticle_AvangingCrash(Unit* pChar);
void AssaParticle_BoneSmash1(Unit* pChar);
void AssaParticle_BoneSmash2(Unit* pChar);

//3Â÷ ½ºÅ³ ÆÄÀÌÅ©
void AssaParticle_VeonmSpear(Unit *pDest);
void AssaParticle_VeonmSpearPike(Unit *pChar);
void AssaParticle_Vanish(Unit *pChar);
void AssaParticle_ChainLance(POINT3D *pPosi);


//3Â÷ ½ºÅ³ ¾ÆÃ³
void AssaParticle_ElementalShotFire(POINT3D* pCur, POINT3D* pDest);
void AssaParticle_ElementalShotLighting(POINT3D* pCur, POINT3D* pDest);
void AssaParticle_GoldenFalcon(Unit *pChar, int liveCount);
void AssaParticle_BombHit1(POINT3D *pPosi);
void AssaParticle_BombShot(POINT3D* pCur, POINT3D* pDest);
void AssaParticle_Perforation(POINT3D* pCur, POINT3D* Dest);
void AssaParticle_PerforationHit(Unit* monster, Unit* character, float delay = 0.f);


//3Â÷ ½ºÅ³ ¸ÞÄ«´Ï¼Ç
void AssaParticle_MetalArmorStart(Unit *pChar);
void AssaParticle_MetalArmorEffect(Unit *pChar, int liveCount);
void AssaParticle_GrandSmash(Unit *pChar);
void AssaParticle_SparkShieldStart(Unit* pChar);
void AssaParticle_SparkShieldEffect(Unit *pChar, int liveCount);
void AssaParticle_SparkShieldDefence(POINT3D *pPosi, POINT3D *pDesti);


//3Â÷ ½ºÅ³ ¸ÞÁö¼Ç
void AssaParticle_EnergyShield(Unit *pChar,int liveCount);
void AssaParticle_EnergyShieldDefence(Unit *pChar);
void AssaParticle_Diastrophism(Unit *pChar);
void AssaParticle_DiastrophismPart(Unit *pChar);
void AssaParticle_SpiritElemental(Unit *pChar, int liveCount);

void AssaParticle_DancingSwordFire(Unit *pChar,int liveCount, int level);
void AssaParticle_DancingSwordIce(Unit *pChar,int liveCount, int level);

//3Â÷ ½ºÅ³ ³ªÀÌÆ®
void AssaParticle_FlameBrandish(Unit *pChar);
void AssaParticle_FlameBrandishHit1(Unit *pChar);
void AssaParticle_HolyIncantationShot(Unit* pDestChar);
void AssaParticle_HolyIncantationPart(Unit* pDestChar, int liveCount);
void AssaParticle_HolyIncantationHand(Unit* pDestChar);

void AssaParticle_GrandCrossHorz(POINT3D* pPosi, int angleY);
void AssaParticle_GrandCrossVert(POINT3D* pPosi, int angleY);
void AssaParticle_DivineInhalationStart(Unit* pChar);
void AssaParticle_DivineInhalationPart(Unit* pChar, int liveCount);
void AssaParticle_DivineInhalationDefence(POINT3D *pDest);


//3Â÷ ¾ÆÅ»¶õÅ¸
void AssaParticle_SplitJavelin(POINT3D* pCur, POINT3D* pDest, int count = 2);
void AssaParticle_TriumphOfValhalla(Unit *pDestChar, int liveCount);
void AssaParticle_TriumphOfValhallaMember(Unit *pCurChar, Unit *pDestChar, int liveCount);
void AssaParticle_LightingJavelin(POINT3D* pCur, POINT3D* pDest);
void AssaParticle_StormJavelin(POINT3D* pCur, POINT3D* pDest);
void AssaParticle_StormJavelinHit(Unit* monster, Unit* character, float delay = 0.f);


//3Â÷ ½ºÅ³ ÇÁ¸®½ºÆ¼½º
void AssaParticle_VigorBall(Unit* pCurChar, Unit* pDestChar);
void AssaParticle_ResurrectionShot(Unit* pDestChar);
void AssaParticle_ResurrectionPart(Unit* pDestChar);
void AssaParticle_Extinction(Unit* pDestChar);
// ÉñÊ¥Ö®¹â
void AssaParticle_VirtualLifeStart(Unit *pDestChar);
void AssaParticle_VirtualLifeEffect(Unit* pDestChar, int liveCount);

//»ØÐý´ò»÷
void AssaParticle_Reaper(POINT3D *pos);
//µØÏ®ÆæÇ¹
void AssaParticle_Spear(Unit *pDest);

//Monster ÆÄÆ¼Å¬
void AssaParticle_MonsterPigonHand(Unit* pChar);

//ClassUp ÆÄÆ¼Å¬
void AssaParticle_ClassUpWeapon(Unit* pChar);
void AssaParticle_StopClassUpWeapon(Unit* pChar);
void AssaParticle_AgingBody(Unit* pChar, int num);

// ElementÐ§¹û
void AssaParticle_ElementWeapon(Unit *pChar,int Kind,int Hand = 0);
void AssaParticle_ElementHit(Unit *pChar,int Kind,POINT3D *pos);

void AssParticle_AdvEffect(Unit *pChar);


//Iron Monster ½ºÅ³
void AssaParticle_MonsterExplision(POINT3D *pPosi);
void AssaParticle_MonsterIronSadNessHit1(Unit *pChar);
void AssaParticle_MonsterIronSadNessSkill1(Unit *pChar);
void AssaParticle_MonsterIronHyperHit1(Unit *pChar, POINT3D *pDest);
void AssaParticle_MonsterIronHyperSkill1(Unit *pChar, POINT3D *pDest);

void AssaParticle_MonsterIronChainGolem(Unit *pChar);
void AssaParticle_MonsterIronRunicGuardian(Unit *pChar, Unit *pDestChar);
void AssaParticle_MonsterIronMountainHit1(Unit *pChar);
void AssaParticle_MonsterIronMountainSkill1(Unit *pChar);
void AssaParticle_MonsterIronTowerGolemHit1(Unit *pChar);
void AssaParticle_MonsterIronTowerGolemSkill1(Unit *pChar);
void AssaParticle_MonsterIronHit1(POINT3D *pPosi);

void AssaParticle_MonsterIronOmuHit1(Unit *pChar);
void AssaParticle_MonsterIronFist(Unit *pChar);
void AssaParticle_MonsterIronMorgonHit(Unit *pChar);
void AssaParticle_MonsterAvelArcher(Unit *pChar, Unit *pDestChar);
void AssaParticle_MonsterAvelQueen(Unit *pChar, Unit *pDestChar);
void AssaParticle_MonsterDeadZoneDead(Unit *pChar);
void AssaParticle_MonsterHyperDead(Unit *pChar);

void AssaParticle_MonsterRunicGuardianHand(Unit *pChar);
void AssaParticle_MonsterRunicGuardianShot(Unit *pChar, Unit *pDestChar);
void AssaParticle_MonsterRunicGuardianBossLightShot(Unit **pCharList, int charCount);

void AssaParticle_MonsterRunicGuardianBossShot(Unit *pChar, int blendType = SMMAT_BLEND_INVSHADOW);
void AssaParticle_MonsterRunicGrardianBossSkill(Unit *pChar);
void AssaParticle_MonsterRunicGuardianBossSkillHit(POINT3D *pDest);
void AssaParticle_MonsterRunicGuardianBossWeapon(Unit *pChar);
void AssaParticle_MonsterRunicGuardianBossHit(Unit *pCurChar, Unit *pDestChar, Unit **charList = 0, int charCount = 0);

void AssaParticle_ShelltomShot(POINT3D *pPosi, POINT3D *pDest, int type = 0);
void AssaParticle_BamShot(POINT3D *pPosi, POINT3D *pDest);

void AssaParticle_ShelltomWeapon(Unit *pChar, int time, int code);
void AssaParticle_ShelltomWeaponHit(POINT3D *pPosi);

//Terrain È¿°ú
void AssaParticle_TerrainShowStart();
void AssaParticle_TerrainFire(POINT3D *pCur, POINT3D *pDest, int delay = 0,int SkillCode = 0);
void AssaParticle_TerrainFireHit(POINT3D *pCur,int SkillCode);

void ParkAssaParticle_TurtleDragonHit(Unit *pCur, Unit *pDes);

void AssaMonsterHitTest(Unit *pChar);

void AssaParticle_TurtleDragonHit(POINT3D *pPosi);
void AssaParticle_TurtleDragonSkill(POINT3D *pPosi);
void AssaParticle_BoneHoundHit(Unit *pChar);

//4Â÷ ½ºÅ³
void SkillSaintGodlyShieldStart(Unit *pChar);
void SkillArchMageFlameWave(Unit *pChar);
void SkillCelestialChainLighting(Unit **pCharList, int charCount);
void SkillValhallaHallOfValhallaHandEffect(Unit *pChar, float time);
void SkillImpulsionLight(Unit *pChar, float time);
void SkillImpulsionLightHit(POINT3D *pos);
void SkillShadowMasterHit(POINT3D *pos);
void SkillPhoenixShotFlame(Unit *pChar, POINT3D *curPos);
void SkillGodBless(Unit *pChar);
void SkillParticle_FrostJavelin(Unit *pChar, float time);

void AssaMotionBlur(Unit *pChar, char *meshName1, char *meshName2, int timeCount);

//°£¿ËË¹¼¼ÄÜ
void ParkParticle_DraxosSkill(Unit *pChar,int LiveCount);
void AssaParticle_Draxos(Unit *pChar);

void AssParticle_Greedy(Unit *pChar);

void AssParticle_Midranda(Unit *pChar);

void AssParticle_Faugn(Unit *pChar);

void AssParticle_Yagditha(Unit *pChar);


// »úÐµ Åùö¨Ðý·ç¼¼ÄÜÐ§¹û
int ParkParticle_LandMinning_Skill(Unit *pChar);
// ¿ìËÙ´ò»÷
void AssaParticle_HyperSonic(Unit *pChar,int LiveCount);
//Õ½Éñ×£¸£Ð§¹û
void AssaParticle_EnhenceEffect(Unit *pChar,int LiveCount);
void AssaParticle_EnhenceStart(Unit *pChar);
//»ØÐýÖ®ÎèÐ§¹û
void AssaParticle_EvadEshot(Unit *pChar);
//Ðþ¹âÖ®Îè
void AssaParticle_S_Rope(POINT3D *curPos,POINT3D *desPos);
//ì«·çÖ®¼ý
void AssaParticle_Splash(POINT3D *pos);
//º®±ùÖ®¼ý
void AssaParticle_CircleTrap(POINT3D *curPos,POINT3D *desPos,int Level);
//µØÏ®ÆæÇ¹
void AssParticle_Spear(Unit *pChar);
//ÉýÁúÖØ»÷
void AssaParticle_Moon(Unit *pChar);
//ÍöÁéÖ®Öä
void AssaParticle_Benedic(Unit *pChar);
//ÉýÁúÖØ»÷
void AssaParticle_Moon2(Unit *pChar);
//ÉÏµÛÖØ»÷
void AssaParticle_Blade(Unit *pChar);
//ÍöÁéÖ®Öä
void AssaParticle_Benedic2(Unit *pChar);
void Assa_Benedic(Unit *pChar,int LiveCount);
//ÉñÊ¥Ï´Àñ
void AssaParticle_Ignis(Unit *pChar,int blendType,int Count);
//ÇáÎè·ÉÑï
void AssaParticle_Taltria(Unit *pChar);
void AssaParticle_TaltriaEffect(Unit *pChar,int LiveCount);
//ÐÇÓê±êÇ¹
void AssaParticle_G_Coup(Unit *pChar);
void AssaParticle_G_Coup_Effect(POINT3D* pCur, POINT3D* pDest, int count);
//±¿±¿ÐÜ
void AssaParticle_SummonArcuda(Unit *pChar);
//ÁÒÑæÍ»Ï®
void AssaParticle_S_Fear(POINT3D *pCur,POINT3D *pDest);
//ÉñÖ®±ùÈÐ
void AssaP_IceEffect(Unit *pCurChar, Unit *pDestChar);
//ÌìÅ®É¢»¨
void Assa_KrishnaEffect(Unit *pChar);
void Assa_KrishnaEffect(Unit *pChar,int LiveCount);

//¼¼ÄÜÐ§¹û
void AssaCodeSkillEffect(char *pFileName, Unit *pChar,int Time,int SkillCode);
//°µºÚÉÁµçÐ§¹û
void AssaDarkWaveEffect(Unit *pCurChar, Unit *pDestChar,int SkillCode);
//ÉóÅÐ
int ParkAssaParticle_Judgement(POINT3D *pPosi,POINT3D *pDesti);


// ¾ÆÀÌ½º ÇÊµå

//ColdEye ·¹ÀÌÀú ½î±â..
int ParkAssaParticle_ColdEye(POINT3D *pPosi, POINT3D *pDesti);
//ColdEye ½ºÅ³°ø°Ý
int ParkParticle_ColdEyeSkill(Unit *pChar);

int ParkParticle_RedEyeSkill(Unit *pChar);
// ±ùË®¾§Ð§¹û
int ParkAssaParticle_MisticSpinel(Unit *pChar);
// ¿óÉ½¾§Ê¯Ð§¹û
int ParkAssaParticle_SealCrasherl(Unit *pChar);
// ±ù¼×¶¾ÖëÐ§¹û
int ParkAssaParticle_Tarantulika(Unit *pChar);

int ParkAssaParticle_AcientDia(Unit *pChar);
// ÇÁ·Î½ºÆ® ¿¡ÀÌ¼ÇÆ® ÇÇ¾î½Ì
int ParksinSkillEffect_AcientPiercing(Unit *pChar);
int ParksinSkillEffect_AcientPiercingAtt(Unit *pChar);

// ¾ÆÀÌ½º °ñ·½ ÀÌÆåÆ®
int ParkAssaParticle_IceGolemShot(Unit *pChar);
// ÇÁ·ÎÁð ¹Ì½ºÆ®	±âº»°ø°Ý
int ParkAssaParticle_MistIceBolt(Unit* pCurChar, Unit* pDestChar);
// ÇÁ·ÎÁð ¹Ì½ºÆ®	½ºÅ³°ø°Ý
int ParkAssaParticle_MistIceBall(Unit* pCurChar, Unit* pDestChar);

// ¾ÆÀÌ½º °íºí¸°
int ParkAssaParticle_IceGoblinHit1(Unit *pChar);

int ParkAssaParticle_RedEye(POINT3D *pPosi,POINT3D *pDesti);

int ParkAssaParticle_Valento1(Unit* pValento);	// µ¥½º³ªÀÌÆ® ºê·£µð½¬
int ParkAssaParticle_Valento2_1(Unit* pValento);	// µ¥½º³ªÀÌÆ® ¹ö¼­Ä¿ (ÇÇ¾î½ÌÀÇ ±â ¸ðÀ¸±â)
int ParkAssaParticle_Valento2_2(Unit* pValento);	// ¹ö¼­Ä¿ ÈÄ¿¡ ±â¸¦ ¸ð¾Æ½ð´Ù.
int ParkAssaParticle_Valento3_1(Unit* pValento);	// µ¥½º³ªÀÌÆ® ³»·ÁÄ¡±â´Â (ParkAssaParticle_Valento1) È£Ãâ ÀÌÇÔ¼ö´Â ¿Ã·ÁÄ¡±â.
void ParkAssaParticle_MonsterIceValentoBody(Unit *pValento);	// µ¥½º³ªÀÌÆ® ¸öÅë¿¡ ºÙ´Â ÆÄÆ¼Å¬
void ParkValentSwordShow(Unit* pValento, int nTime);	// µ¥½º³ªÀÌÆ® °Ë±â

// ¶ñÄ§²®¾ôÐ§¹û
void ParksinSkillEffect_TullaPiercing(Unit* pChar);

int ParkAssaParticle_ChaosKara1(Unit* pChar);	// Ä«¿À½º Ä«¶ó ÀÏ¹Ý°ø°Ý
int ParkAssaParticle_ChaosKara2(Unit* pChar);	// Ä«¿À½º Ä«¶ó ¾ÆÀÌ½º ¹ÌÆ¼¾î
int ParkAssaParticle_ChaosKaraSkill_Monster(Unit* pMonster); // Ä«¿À½ºÄ«¶ó ¹ìÆÄÀÌ¾î¸¯ (¸ó½ºÅÍ ÀÚ½Å)
int ParkAssaParticle_ChaosKaraSkill_User(Unit* pUser);	// Ä«¿À½ºÄ«¶ó ¹ìÆÄÀÌ¾î¸¯ (À¯Àú)
void ParkAssaParticle_MonsterIceChaosKara(Unit *pChar);	// Ä«¿À½º Ä«¶ó ½ºÅÂÇÁ ÆÄÆ¼Å¬


///////////////// »õ·Î¿î ÇÊµå ////////////////
// ¹ÚÃ¶È£ //
void ParkAssaParticle_SpiderTrooperHit1(Unit *pChar);	// ½ºÆÄÀÌ´õ Æ®·çÆÛ µ¶°¡½º »Õ¾î³»±â

void ParkAssaParticle_StingRay(Unit *pChar);	//½ºÆÃ·¹ÀÌ µ¶°¡½º »Õ¾î³»±â..
int ParkDivineLight_Effect(Unit *lpChar );		//µð¹ÙÀÎ ¶óÀÌÆ®´× ½ºÅ³ ¿¬Ãâ ( ÀÌÆåÆ® ½ÇÇö )
int ParkAssaParticle_DivineLighting(Unit *pChar);	//µð¹ÙÀÎ ¶óÀÌÆ®´× ½ºÅ³ ¿¬Ãâ ( ÀÌÆåÆ® ½ÇÇö )
int ParkAssaParticle_Sprak1(POINT3D *pPosi);
int ParkAssaParticle_Posion(Unit *pChar, int liveCount);		// µ¶°É¸°°Å Ç¥Çö
void ParkAssaParticle_MummyShot(Unit *pChar, Unit *pDestChar);	// ¸Ó¹Ì·Îµå Åë»ó°ø°Ý
#define STINGRAY_POSION_TIME	5

void ParkBlizzardGiantSkillToTarget(Unit *pTarget);	//ºí¸®ÀÚµå ÀÚÀÌ¾ðÆ® ½ºÅ³ ÀÌÆåÆ®

void ParkDevilBirdAttackBlur(Unit* pDevilBird);	// µ¥ºí ¹öµå ÀÏ¹Ý °ø°Ý ½ÃÀÛ½Ã ºí·¯
void ParkDevilBirdAttackNormal(Unit *pTarget);	// µ¥ºí ¹öµå °ø°Ýµ¿ÀÛ 2¹ø Å¸°ÝÀÌÆåÆ®
void ParkDevilBirdSkillToTarget(Unit *pTarget);	// µ¥ºí ¹öµå ±â¼úµ¿ÀÛ Å¸°Ý ÀÌÆåÆ®

void ParkAssaParticle_MonsterTurtleCanonNormal(Unit *pTCanon, Unit* pTarget);	// ÅÍÆ²Ä³³í ÀÏ¹Ý °ø°Ý

void ParkAssaParticle_FireCracker(Unit *pChar, int nFireCracker);	// ÆøÁ×ÀÌÆåÆ®

// Ç«Á× ÅÍÆ®¸±½Ã 20°³ÀÇ 4Â÷¿ø¹è¿­ Áï 20 ^ 4 ÀÇ Å×ÀÌºíÀ» Á¤ÀÇÇÏ¿© ¸®ÅÏ½ÃÄÑÁØ´Ù.
// ¹øÈ£¸¸ ÀÔ·ÂÇÏ¸é ±× ¹øÈ£¿¡ ¸Â´Â ¹è¿­À» ªO¾Æ¼­ ÀÎÄÚµå ÇÏ¿© ¸®ÅÏ½ÃÄÑÁØ´Ù.
DWORD GetTableNum(int n);

// 4°³ÀÇ °ªÀ» ÀÎÄÚµåÇÑ´Ù.
DWORD Park_VarEncode(int a, int b, int c, int d);

// ÀÎÄÚµåµÈ °ªÀ» ´Ù½Ã µðÄÚµå ÇØÁØ´Ù.
void Park_VarDecode(DWORD dwData, int &nData1, int &nData2, int &nData3, int &nData4);

// ÄÌº£Áê ÀÌÆåÆ®
void ParkKelvezuHit(Unit *pChar);	// ÄÌº£Áê °ø°Ý½Ã Ä³¸¯ÅÍ ÇÇ°ÝÀÌÆåÆ®
void ParkKelvezuSkillHit(Unit *pChar);	// ÄÌº£Áê °ø°Ý½Ã Ä³¸¯ÅÍ ÇÇ°ÝÀÌÆåÆ®
void ParkKelvezuNormal1(Unit *pChar);
void ParkKelvezuNormal2(Unit *pKelvezu);
void ParkKelvezuSkill1(Unit *pKelvezu);
void ParkKelvezuSkill2(Unit *pKelvezu);
void ParkKelvezuJin(Unit *pKelvezu);	// ÄÌº£Áê ¸¶¹ýÁø¹× ÀÔ¿¡¼­ ¿¬±â³ª´Â°Å

// ÄÌº£Áê °ø°Ý½Ã ¹ßÅé¿¡¼­ °Ë±âÈ¿°ú
void ParkKelvezuFingerShow(Unit* pKelvezu, int nTime);

// ÄÌº£Áê °ø°Ý½Ã ³¯°³¿¡¼­ °Ë±âÈ¿°ú
void ParkKelvezuWingShow(Unit* pKelvezu, int nTime);

// ÄÌº£Áê °ø°Ý½Ã ²¿¸®¿¡¼­ °Ë±âÈ¿°ú
void ParkKelvezuTaleShow(Unit* pKelvezu, int nTime);

// ¿ùµåÄÅ ¸ó½ºÅÍ ÀÌÆåÆ®
void ParkAssaParticle_WorldCupMonsterAttack(Unit* pMonster, Unit *pChar);
// ¿ùµåÄÅ ¸ó½ºÅÍ°¡ °ø°Ý½Ã Ä³¸¯ÅÍ ÇÇ°ÝÀÌÆåÆ®
void ParkWorldCupMonsterHit(Unit *pChar);



// Dark Phalanx ±â¼ú µ¿ÀÛ ÀÌÆåÆ® (Ã¢À¸·Î Âî¸¦¶§ Ã¢ÀÌ ÆÄ°íµå´Â ´À³¦ÀÇ ÀÌÆåÆ® - ÇÇ¾î½ÌÀ¸·Î Ã³¸®)
void ParkAssaParticle_DarkPhalanx(Unit *pDarkPhalanx);

// ÆÄÀÌ¾î ¿ú ÀÏ¹Ý °ø°Ý ¹× ½ºÅ³°ø°Ý
void ParkAssaParticle_TerrainFireHit(POINT3D *pCur, int nType);
void ParkAssaParticle_TerrainFire(POINT3D *pCur, POINT3D *pDest, int delay = 0, int nType = 0);

void ParkAssaParticle_FireWorm(Unit* pTarget, BOOL bSkill = FALSE);
void ParkAssaParticle_IceWorm(Unit* pTarget, BOOL bSkill = FALSE);


// Å°¸Þ¶ó ÀÏ¹Ý°ø°Ý ( ¹ßÅé ºí·¯ )
void ParkAssaParticle_ChimeraNormal(Unit *pChimera);

// Å°¸Þ¶ó ½ºÅ³°ø°Ý (Çìµù - ¸Ó¸®¿¡ ÀÍ½ºÆ®¸²½Çµå)
void ParkAssaParticle_ChimeraSkill(Unit *pChar);

// Bloody Knight ½ºÅ³ °ø°Ý (·Î¾î)
void ParkAssaParticle_BloodySkill(Unit *pBloodKnight);

// Bloody Knight ½ºÅ³ °ø°Ý ÇÇ°Ý (½ºÅÏ)
void ParkAssaParticle_BloodySkillStun(Unit *pChar);

// Çï ÇÏ¿îµå ³ë¸»°ø°Ý (µÎ¹ßÀ» µé¾î ´ë»óÀ» ³»·ÁÂïÀ½)
void ParkAssaParticle_HellHoundNormal(Unit *pChar);

// Çï ÇÏ¿îµå ½ºÅ³°ø°Ý (ÀÔ¿¡¼­ ºÒ³ª°¨)
void ParkAssaParticle_HellHoundSkillAttack(Unit *pHellHound);

// Çï ÇÏ¿îµå ½ºÅ³°ø°ÝÀÇ ÇÇ°Ý½Ã (È­¿°¿¡ ÈÛ½ÎÀÎµíÇÑ ÀÌÆåÆ®)
void ParkAssaParticle_HellHoundSkillTaget(Unit *pChar);

// ´ÙÅ© °¡µå ±âº»°ø°Ý ÇÇ°Ý½Ã
void ParkAssaParticle_DarkGuardTaget(Unit *pChar);

// ´ÙÅ© °¡µå ½ºÅ³°ø°Ý
void ParkAssaParticle_DarkGuardSkill(Unit *pDarkGuard, Unit *pChar);

// ´ÙÅ© ¸ÞÀÌÁö ±âº»°ø°Ý
void ParkAssaParticle_DarkMageNormal(Unit *pDarkMage, Unit *pChar);

// ´ÙÅ© ¸ÞÀÌÁö ½ºÅ³°ø°Ý
void ParkAssaParticle_DarkMageSkill(Unit *pChar);

// ´ÙÅ© ¸ÞÀÌÁö Á×À»¶§
void ParkAssaParticle_DarkMageDead(Unit *pDarkMage);






#endif