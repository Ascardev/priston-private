/*----------------------------------------------------------------------------*
*	���ϸ� :  sinPublicEffect.h	
*	�ϴ��� :  ���� ����Ʈ�� ���� ������ ����Ʈ 
*	�ۼ��� :  ����������Ʈ 2002�� 10��
*	������ :  �ڻ� 
*-----------------------------------------------------------------------------*/	

int sinPublicEffectTestKey(); //��ų �׽�Ʈ Key

/*----------------------------------------------------------------------------*
*							�ý���
*-----------------------------------------------------------------------------*/	
void sinInitPublicEffect();
void sinPublicEffectMove(cSINEFFECT2 *pEffect);	

/*----------------------------------------------------------------------------*
*							���� ����Ʈ 
*-----------------------------------------------------------------------------*/	
int sinEffect_WideLine(POINT3D *pPosi , int Mat , int Lenght , int Num);  //������ ����
int sinEffect_WideParticle_Bone(POINT3D *pPosi , int Mat , int Size , int Time , int Num , int Speed); 	//������ ��ƼŬ 
int sinEffect_WideParticle(POINT3D *pPosi , int Mat , int Size);
int sinEffect_BombParticle(POINT3D *pPosi , int Mat , int Size , int Num);
int sinEffect_Light5(POINT3D *pPosi , int Size );
int sinEffect_SpoutParticle(POINT3D *pPosi ,int Mat ,int Num , int Size , int Time , int Gravity );
int sinEffect_GatherLine(Unit *pChar  , int Mat ,int Time);
int sinEffect_GatherLine2(Unit *pChar  , int Mat );
int sinEffect_WideContinueLine(Unit *pChar , int Mat ,int Time,int Height);
int sinEffect_WideContinueLine2(POINT3D *pPosi , int Mat );
int sinEffect_GatherCircleParticle(POINT3D *pPosi ,int Mat );
int sinEffect_Hit2(POINT3D *pPosi ,int Mat );


/*----------------------------------------------------------------------------*
*							���� ����Ʈ
*-----------------------------------------------------------------------------*/	
int sinEffect_Sen(POINT3D *pPosi); //�� ����Ʈ 
int sinEffect_Sen_Particle(POINT3D *pPosi); 
int sinEffect_MutentTree_Smoke(POINT3D *pPosi); //����Ʈ Ʈ�� 
int sinEffect_MutentTree_Smoke_Particle(POINT3D *pPosi);
int sinEffect_MutentTree_Attack(Unit *pChar , Unit *desChar);
int sinEffect_MutentTree_Attack_Particle(POINT3D *pPosi);
int sinEffect_MutentTree_Attack_Particle2(POINT3D *pPosi);
int sinEffect_MutentTree_Hit_Particle(POINT3D *pPosi);
int sinEffect_MutentTree_Fire(POINT3D *pPosi);
int sinEffect_MutentTree_Fire_Particle(POINT3D *pPosi);
int sinEffect_Ratoo(Unit *pChar); //���� 
int sinEffect_Ratoo_Vigor(Unit *pChar); //���� �� 
int sinEffect_Ratoo_Vigor_Partilce(POINT3D *pPosi);

// ����֮��
int sinEffect_RollingSmash(Unit *pChar,int x,int y,int z);
// 쫷�֮��
int sinEffect_Splash(Unit *pChar);
// ��Ůɢ��
int sinEffect_Krishna(Unit *pChar,int LiveCount);
// ����֮��
int sinEffect_Benedic(Unit *pChar,int LiveCount);