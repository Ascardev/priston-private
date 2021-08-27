#ifndef _HO_ASSA_PARTICLE_EFFECT_
#define _HO_ASSA_PARTICLE_EFFECT_




//��� �ִ� ���۸� �����ϴ� �Լ�..(�Լ� �ȿ��� �������� ���� �ϸ� sin�� �Լ��� ���ľ� �ϹǷ�)
int GetAssaEffect();
int	StopAssaCodeEffect(Unit *pChar, int code, int setTime = 0);
bool AddAssaCodeEffectTime(Unit *pChar, int code, int time);
int AddAssaCodeEffectTime(Unit *pChar,int Code);

BOOL GetAssaUseEffect(Unit *pChar, int code);
bool GetAssaContinueSkill(int skillCode);
//���̴� ���� ��ƼŬ...
int AssaParticle_LineIn(POINT3D *pPosi , char *texName = NULL, int continueTime = 15, int speed = 0);
int AssaParticle_LineOut(POINT3D *pPosi , char *texName = NULL, int continueTime = 10, int speed = 0);
int AssaParticle_Star(POINT3D *pPosi);

//�����ػ�
int AssaParticle_HolyValor_Jang(Unit *pChar);
int AssaParticle_HolyValor_JangEffect(Unit *pChar,int maxTime);
int AssaParticle_HolyValor_Member(Unit *pChar, int maxTime = 0);
int AssaParticle_HolyValorIsUse(Unit *pChar);

//��������
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

//Fury ���� ����Ʈ
int AssaParticle_Fury_Eye(Unit *pChar);							//���� �ٴ� ����Ʈ
int AssaParticle_Fury_ShotFire(Unit *pChar, POINT3D *destPos);	//�ҽ��..

int AssaParticle_Fury_RespawnMonster(POINT3D *pPosi);						//���͵� ��ȯ..
int AssaParticle_Fury_RespawnBody(Unit *pChar);                  //���� ��ȯ�� ǻ���� �Կ��� ������ ��ƼŬ.
int AssaParticle_Fury_Skill1(Unit *pChar);						//���� ����..

int AssaParticle_Fury_Skill1(POINT3D *pPosi, POINT3D *pAngle);      //���� ����.. ���� ������ ���ؼ�..

//Evil Maple���� ����Ʈ..
int AssaParticle_EvilMapleShot(Unit *pChar);

//Evil Plant���� ����Ʈ..
int AssaParticle_EvilPlantShot(Unit *pChar);

void AssaParticle_IceserpentHit(Unit *pChar);

void AssaParticle_IceserpentSkill(Unit *pChar);

//Thorn Crawler���� ����Ʈ..
int AssaParticle_ThornCrawlerShot(Unit *pChar, POINT3D *destPos);

//Stone Golem���� ����Ʈ..
int AssaParticle_StoneGolemShot(Unit *pChar);


//Heavy Goblin���� ����Ʈ..
int AssaParticle_HeavyGoblinHit1(Unit *pChar); //������ ����ġ�� ����
int AssaParticle_HeavyGoblinHit2(Unit *pChar); //����̵忡�� ġ�� ����

//Doom Gurad���� ����Ʈ..
int AssaParticle_DoomGuardHit1(Unit *pChar); //������ ����ġ�� ����
int AssaParticle_DoomGuardHit2(Unit *pChar); //����̵� ġ�� ����

//Snail ���� ����Ʈ..
int AssaParticle_SnailShot(Unit *pChar, POINT3D *destPos);

//Night Mare���� ����Ʈ..
int AssaParticle_NightMare(Unit *pChar);

//Ratoo ���彺
int AssaParticle_RatooHit1(Unit *pChar);

//Monster ġ��
int AssaParticle_Hit1(POINT3D *destPos);


//Spider �Ź� ���� ����
int AssaParticleSpiderSkill1(Unit *pChar);

void AssParticle_UnDeadManger(Unit *pChar,int nSkill);
//�����ܼ���
void AssaParticle_Arcuda(Unit *pChar);
// ����Ч��
void AssaParticle_Effect(char *szName, Unit *pChar,int Kind);
// ����֮��
void AssaParticle_RollingSmashHit(int x,int y,int z);
void AssaParticle_RollingSmashDown(int x,int y,int z);


void AssaParticle_CastleRed(Unit *pChar);
void AssaParticle_CastleGreen(Unit *pChar);
void AssaParticle_CastleBlue(Unit *pChar);

//ClanMonster ����Ʈ
int AssaParticleClanMonster(Unit *pChar);
int AssaParticleClanMonsterHit1(Unit *pChar);
int AssaParticleClanMonsterHit2(Unit *pChar);
int AssaParticle_Sprak1(POINT3D *pPosi);

// ��ħ����Ч��
int AssaParticleTulla(Unit *pChar);

void AssaParticle_BlueMountainHit(Unit *pChar);
void AssaParticle_BlueMountainSkill(Unit *pChar);
void AssaParticle_MorgoniaHit(Unit *pChar);
void AssaParticle_MorgoniaSkill(Unit *pChar);
void AssaParticle_BoneHoundSkill(Unit *pChar);
void AssaParticle_BoneHoundSkillHit(Unit *pChar);

// ����һ��
void AssaParticle_ConcentrationStart(Unit *pChar);
void AssaParticle_ConcentrationEffect(Unit *pChar,int liveCount,int SkillCode,int Light = TRUE);
//��ɱ֮��
void AssaParticle_SwiftAxeStart(Unit *pChar);
void AssaParticle_SwiftAxeEffect(Unit *pChar,int liveCount,int SkillCode,int Light = TRUE);

void AssaParticle_AvangingCrash(Unit* pChar);
void AssaParticle_BoneSmash1(Unit* pChar);
void AssaParticle_BoneSmash2(Unit* pChar);

//3�� ��ų ����ũ
void AssaParticle_VeonmSpear(Unit *pDest);
void AssaParticle_VeonmSpearPike(Unit *pChar);
void AssaParticle_Vanish(Unit *pChar);
void AssaParticle_ChainLance(POINT3D *pPosi);


//3�� ��ų ��ó
void AssaParticle_ElementalShotFire(POINT3D* pCur, POINT3D* pDest);
void AssaParticle_ElementalShotLighting(POINT3D* pCur, POINT3D* pDest);
void AssaParticle_GoldenFalcon(Unit *pChar, int liveCount);
void AssaParticle_BombHit1(POINT3D *pPosi);
void AssaParticle_BombShot(POINT3D* pCur, POINT3D* pDest);
void AssaParticle_Perforation(POINT3D* pCur, POINT3D* Dest);
void AssaParticle_PerforationHit(Unit* monster, Unit* character, float delay = 0.f);


//3�� ��ų ��ī�ϼ�
void AssaParticle_MetalArmorStart(Unit *pChar);
void AssaParticle_MetalArmorEffect(Unit *pChar, int liveCount);
void AssaParticle_GrandSmash(Unit *pChar);
void AssaParticle_SparkShieldStart(Unit* pChar);
void AssaParticle_SparkShieldEffect(Unit *pChar, int liveCount);
void AssaParticle_SparkShieldDefence(POINT3D *pPosi, POINT3D *pDesti);


//3�� ��ų ������
void AssaParticle_EnergyShield(Unit *pChar,int liveCount);
void AssaParticle_EnergyShieldDefence(Unit *pChar);
void AssaParticle_Diastrophism(Unit *pChar);
void AssaParticle_DiastrophismPart(Unit *pChar);
void AssaParticle_SpiritElemental(Unit *pChar, int liveCount);

void AssaParticle_DancingSwordFire(Unit *pChar,int liveCount, int level);
void AssaParticle_DancingSwordIce(Unit *pChar,int liveCount, int level);

//3�� ��ų ����Ʈ
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


//3�� ��Ż��Ÿ
void AssaParticle_SplitJavelin(POINT3D* pCur, POINT3D* pDest, int count = 2);
void AssaParticle_TriumphOfValhalla(Unit *pDestChar, int liveCount);
void AssaParticle_TriumphOfValhallaMember(Unit *pCurChar, Unit *pDestChar, int liveCount);
void AssaParticle_LightingJavelin(POINT3D* pCur, POINT3D* pDest);
void AssaParticle_StormJavelin(POINT3D* pCur, POINT3D* pDest);
void AssaParticle_StormJavelinHit(Unit* monster, Unit* character, float delay = 0.f);


//3�� ��ų ������Ƽ��
void AssaParticle_VigorBall(Unit* pCurChar, Unit* pDestChar);
void AssaParticle_ResurrectionShot(Unit* pDestChar);
void AssaParticle_ResurrectionPart(Unit* pDestChar);
void AssaParticle_Extinction(Unit* pDestChar);
// ��ʥ֮��
void AssaParticle_VirtualLifeStart(Unit *pDestChar);
void AssaParticle_VirtualLifeEffect(Unit* pDestChar, int liveCount);

//�������
void AssaParticle_Reaper(POINT3D *pos);
//��Ϯ��ǹ
void AssaParticle_Spear(Unit *pDest);

//Monster ��ƼŬ
void AssaParticle_MonsterPigonHand(Unit* pChar);

//ClassUp ��ƼŬ
void AssaParticle_ClassUpWeapon(Unit* pChar);
void AssaParticle_StopClassUpWeapon(Unit* pChar);
void AssaParticle_AgingBody(Unit* pChar, int num);

// ElementЧ��
void AssaParticle_ElementWeapon(Unit *pChar,int Kind,int Hand = 0);
void AssaParticle_ElementHit(Unit *pChar,int Kind,POINT3D *pos);

void AssParticle_AdvEffect(Unit *pChar);


//Iron Monster ��ų
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

//Terrain ȿ��
void AssaParticle_TerrainShowStart();
void AssaParticle_TerrainFire(POINT3D *pCur, POINT3D *pDest, int delay = 0,int SkillCode = 0);
void AssaParticle_TerrainFireHit(POINT3D *pCur,int SkillCode);

void ParkAssaParticle_TurtleDragonHit(Unit *pCur, Unit *pDes);

void AssaMonsterHitTest(Unit *pChar);

void AssaParticle_TurtleDragonHit(POINT3D *pPosi);
void AssaParticle_TurtleDragonSkill(POINT3D *pPosi);
void AssaParticle_BoneHoundHit(Unit *pChar);

//4�� ��ų
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

//����˹����
void ParkParticle_DraxosSkill(Unit *pChar,int LiveCount);
void AssaParticle_Draxos(Unit *pChar);

void AssParticle_Greedy(Unit *pChar);

void AssParticle_Midranda(Unit *pChar);

void AssParticle_Faugn(Unit *pChar);

void AssParticle_Yagditha(Unit *pChar);


// ��е �������缼��Ч��
int ParkParticle_LandMinning_Skill(Unit *pChar);
// ���ٴ��
void AssaParticle_HyperSonic(Unit *pChar,int LiveCount);
//ս��ף��Ч��
void AssaParticle_EnhenceEffect(Unit *pChar,int LiveCount);
void AssaParticle_EnhenceStart(Unit *pChar);
//����֮��Ч��
void AssaParticle_EvadEshot(Unit *pChar);
//����֮��
void AssaParticle_S_Rope(POINT3D *curPos,POINT3D *desPos);
//쫷�֮��
void AssaParticle_Splash(POINT3D *pos);
//����֮��
void AssaParticle_CircleTrap(POINT3D *curPos,POINT3D *desPos,int Level);
//��Ϯ��ǹ
void AssParticle_Spear(Unit *pChar);
//�����ػ�
void AssaParticle_Moon(Unit *pChar);
//����֮��
void AssaParticle_Benedic(Unit *pChar);
//�����ػ�
void AssaParticle_Moon2(Unit *pChar);
//�ϵ��ػ�
void AssaParticle_Blade(Unit *pChar);
//����֮��
void AssaParticle_Benedic2(Unit *pChar);
void Assa_Benedic(Unit *pChar,int LiveCount);
//��ʥϴ��
void AssaParticle_Ignis(Unit *pChar,int blendType,int Count);
//�������
void AssaParticle_Taltria(Unit *pChar);
void AssaParticle_TaltriaEffect(Unit *pChar,int LiveCount);
//�����ǹ
void AssaParticle_G_Coup(Unit *pChar);
void AssaParticle_G_Coup_Effect(POINT3D* pCur, POINT3D* pDest, int count);
//������
void AssaParticle_SummonArcuda(Unit *pChar);
//����ͻϮ
void AssaParticle_S_Fear(POINT3D *pCur,POINT3D *pDest);
//��֮����
void AssaP_IceEffect(Unit *pCurChar, Unit *pDestChar);
//��Ůɢ��
void Assa_KrishnaEffect(Unit *pChar);
void Assa_KrishnaEffect(Unit *pChar,int LiveCount);

//����Ч��
void AssaCodeSkillEffect(char *pFileName, Unit *pChar,int Time,int SkillCode);
//��������Ч��
void AssaDarkWaveEffect(Unit *pCurChar, Unit *pDestChar,int SkillCode);
//����
int ParkAssaParticle_Judgement(POINT3D *pPosi,POINT3D *pDesti);


// ���̽� �ʵ�

//ColdEye ������ ���..
int ParkAssaParticle_ColdEye(POINT3D *pPosi, POINT3D *pDesti);
//ColdEye ��ų����
int ParkParticle_ColdEyeSkill(Unit *pChar);

int ParkParticle_RedEyeSkill(Unit *pChar);
// ��ˮ��Ч��
int ParkAssaParticle_MisticSpinel(Unit *pChar);
// ��ɽ��ʯЧ��
int ParkAssaParticle_SealCrasherl(Unit *pChar);
// ���׶���Ч��
int ParkAssaParticle_Tarantulika(Unit *pChar);

int ParkAssaParticle_AcientDia(Unit *pChar);
// ���ν�Ʈ ���̼�Ʈ �Ǿ��
int ParksinSkillEffect_AcientPiercing(Unit *pChar);
int ParksinSkillEffect_AcientPiercingAtt(Unit *pChar);

// ���̽� �� ����Ʈ
int ParkAssaParticle_IceGolemShot(Unit *pChar);
// ������ �̽�Ʈ	�⺻����
int ParkAssaParticle_MistIceBolt(Unit* pCurChar, Unit* pDestChar);
// ������ �̽�Ʈ	��ų����
int ParkAssaParticle_MistIceBall(Unit* pCurChar, Unit* pDestChar);

// ���̽� ���
int ParkAssaParticle_IceGoblinHit1(Unit *pChar);

int ParkAssaParticle_RedEye(POINT3D *pPosi,POINT3D *pDesti);

int ParkAssaParticle_Valento1(Unit* pValento);	// ��������Ʈ �귣��
int ParkAssaParticle_Valento2_1(Unit* pValento);	// ��������Ʈ ����Ŀ (�Ǿ���� �� ������)
int ParkAssaParticle_Valento2_2(Unit* pValento);	// ����Ŀ �Ŀ� �⸦ ��ƽ��.
int ParkAssaParticle_Valento3_1(Unit* pValento);	// ��������Ʈ ����ġ��� (ParkAssaParticle_Valento1) ȣ�� ���Լ��� �÷�ġ��.
void ParkAssaParticle_MonsterIceValentoBody(Unit *pValento);	// ��������Ʈ ���뿡 �ٴ� ��ƼŬ
void ParkValentSwordShow(Unit* pValento, int nTime);	// ��������Ʈ �˱�

// ��ħ����Ч��
void ParksinSkillEffect_TullaPiercing(Unit* pChar);

int ParkAssaParticle_ChaosKara1(Unit* pChar);	// ī���� ī�� �Ϲݰ���
int ParkAssaParticle_ChaosKara2(Unit* pChar);	// ī���� ī�� ���̽� ��Ƽ��
int ParkAssaParticle_ChaosKaraSkill_Monster(Unit* pMonster); // ī����ī�� �����̾ (���� �ڽ�)
int ParkAssaParticle_ChaosKaraSkill_User(Unit* pUser);	// ī����ī�� �����̾ (����)
void ParkAssaParticle_MonsterIceChaosKara(Unit *pChar);	// ī���� ī�� ������ ��ƼŬ


///////////////// ���ο� �ʵ� ////////////////
// ��öȣ //
void ParkAssaParticle_SpiderTrooperHit1(Unit *pChar);	// �����̴� Ʈ���� ������ �վ��

void ParkAssaParticle_StingRay(Unit *pChar);	//���÷��� ������ �վ��..
int ParkDivineLight_Effect(Unit *lpChar );		//����� ����Ʈ�� ��ų ���� ( ����Ʈ ���� )
int ParkAssaParticle_DivineLighting(Unit *pChar);	//����� ����Ʈ�� ��ų ���� ( ����Ʈ ���� )
int ParkAssaParticle_Sprak1(POINT3D *pPosi);
int ParkAssaParticle_Posion(Unit *pChar, int liveCount);		// ���ɸ��� ǥ��
void ParkAssaParticle_MummyShot(Unit *pChar, Unit *pDestChar);	// �ӹ̷ε� ������
#define STINGRAY_POSION_TIME	5

void ParkBlizzardGiantSkillToTarget(Unit *pTarget);	//���ڵ� ���̾�Ʈ ��ų ����Ʈ

void ParkDevilBirdAttackBlur(Unit* pDevilBird);	// ���� ���� �Ϲ� ���� ���۽� ��
void ParkDevilBirdAttackNormal(Unit *pTarget);	// ���� ���� ���ݵ��� 2�� Ÿ������Ʈ
void ParkDevilBirdSkillToTarget(Unit *pTarget);	// ���� ���� ������� Ÿ�� ����Ʈ

void ParkAssaParticle_MonsterTurtleCanonNormal(Unit *pTCanon, Unit* pTarget);	// ��Ʋĳ�� �Ϲ� ����

void ParkAssaParticle_FireCracker(Unit *pChar, int nFireCracker);	// ��������Ʈ

// ǫ�� ��Ʈ���� 20���� 4�����迭 �� 20 ^ 4 �� ���̺��� �����Ͽ� ���Ͻ����ش�.
// ��ȣ�� �Է��ϸ� �� ��ȣ�� �´� �迭�� �O�Ƽ� ���ڵ� �Ͽ� ���Ͻ����ش�.
DWORD GetTableNum(int n);

// 4���� ���� ���ڵ��Ѵ�.
DWORD Park_VarEncode(int a, int b, int c, int d);

// ���ڵ�� ���� �ٽ� ���ڵ� ���ش�.
void Park_VarDecode(DWORD dwData, int &nData1, int &nData2, int &nData3, int &nData4);

// �̺��� ����Ʈ
void ParkKelvezuHit(Unit *pChar);	// �̺��� ���ݽ� ĳ���� �ǰ�����Ʈ
void ParkKelvezuSkillHit(Unit *pChar);	// �̺��� ���ݽ� ĳ���� �ǰ�����Ʈ
void ParkKelvezuNormal1(Unit *pChar);
void ParkKelvezuNormal2(Unit *pKelvezu);
void ParkKelvezuSkill1(Unit *pKelvezu);
void ParkKelvezuSkill2(Unit *pKelvezu);
void ParkKelvezuJin(Unit *pKelvezu);	// �̺��� �������� �Կ��� ���⳪�°�

// �̺��� ���ݽ� ���鿡�� �˱�ȿ��
void ParkKelvezuFingerShow(Unit* pKelvezu, int nTime);

// �̺��� ���ݽ� �������� �˱�ȿ��
void ParkKelvezuWingShow(Unit* pKelvezu, int nTime);

// �̺��� ���ݽ� �������� �˱�ȿ��
void ParkKelvezuTaleShow(Unit* pKelvezu, int nTime);

// ������ ���� ����Ʈ
void ParkAssaParticle_WorldCupMonsterAttack(Unit* pMonster, Unit *pChar);
// ������ ���Ͱ� ���ݽ� ĳ���� �ǰ�����Ʈ
void ParkWorldCupMonsterHit(Unit *pChar);



// Dark Phalanx ��� ���� ����Ʈ (â���� ��� â�� �İ��� ������ ����Ʈ - �Ǿ������ ó��)
void ParkAssaParticle_DarkPhalanx(Unit *pDarkPhalanx);

// ���̾� �� �Ϲ� ���� �� ��ų����
void ParkAssaParticle_TerrainFireHit(POINT3D *pCur, int nType);
void ParkAssaParticle_TerrainFire(POINT3D *pCur, POINT3D *pDest, int delay = 0, int nType = 0);

void ParkAssaParticle_FireWorm(Unit* pTarget, BOOL bSkill = FALSE);
void ParkAssaParticle_IceWorm(Unit* pTarget, BOOL bSkill = FALSE);


// Ű�޶� �Ϲݰ��� ( ���� �� )
void ParkAssaParticle_ChimeraNormal(Unit *pChimera);

// Ű�޶� ��ų���� (��� - �Ӹ��� �ͽ�Ʈ���ǵ�)
void ParkAssaParticle_ChimeraSkill(Unit *pChar);

// Bloody Knight ��ų ���� (�ξ�)
void ParkAssaParticle_BloodySkill(Unit *pBloodKnight);

// Bloody Knight ��ų ���� �ǰ� (����)
void ParkAssaParticle_BloodySkillStun(Unit *pChar);

// �� �Ͽ�� �븻���� (�ι��� ��� ����� ��������)
void ParkAssaParticle_HellHoundNormal(Unit *pChar);

// �� �Ͽ�� ��ų���� (�Կ��� �ҳ���)
void ParkAssaParticle_HellHoundSkillAttack(Unit *pHellHound);

// �� �Ͽ�� ��ų������ �ǰݽ� (ȭ���� �۽��ε��� ����Ʈ)
void ParkAssaParticle_HellHoundSkillTaget(Unit *pChar);

// ��ũ ���� �⺻���� �ǰݽ�
void ParkAssaParticle_DarkGuardTaget(Unit *pChar);

// ��ũ ���� ��ų����
void ParkAssaParticle_DarkGuardSkill(Unit *pDarkGuard, Unit *pChar);

// ��ũ ������ �⺻����
void ParkAssaParticle_DarkMageNormal(Unit *pDarkMage, Unit *pChar);

// ��ũ ������ ��ų����
void ParkAssaParticle_DarkMageSkill(Unit *pChar);

// ��ũ ������ ������
void ParkAssaParticle_DarkMageDead(Unit *pDarkMage);






#endif