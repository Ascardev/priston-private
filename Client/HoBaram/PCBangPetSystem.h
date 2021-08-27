//---------------------------------------------------------------------------------- 
//  FIleName : LowLevelPet.h
//                     
//	Class Name:	LowLevelPet
//
//  Desc:   �ʺ� ����� �� ����
//		
//----------------------------------------------------------------------------------


#ifndef _PC_BANG_Pet_H_
#define _PC_BANG_Pet_H_

#include "..\\smwsock.h"
#include "..\\character.h"

#define PCBANG_PET_BURSTP	0
#define PCBANG_PET_BURSTS	1
#define PCBANG_PET_BURSTL	2
#define PCBANG_PET_BURSTD	3

//------------------------------------------------------------------------
// Name : PcBangPet
// Desc : PcBangPet �⺻ �Ӽ��� ������ �ִ� ��ü
// Date : 2004.4.19		Author : HongHoDong�ҽ� ���� ��öȣ		Version : 1.0
//------------------------------------------------------------------------
class HoPCBangPet
{
public:
	enum Type
	{
		BurstP,
		BurstS,
		BurstL,
		BurstD,
		IllusionP,
		IllusionS,
		IllusionL,
		IllusionD,
	};

	enum PCBang_FsmState
	{
		Spawn,						//Pet ����
		Idle,						//Pet ���� ��ȭ���
		SkillPre,                   //Pet Skill ������ ��ų���� ��ġ�� ���� ���
		Skill,                      //Pet Skill ���� ���
		Vanish,                     //Pet ������� ���
		None						//Pet �ƹ��͵� ���ϴ� ���	
	};

	enum PCBang_FsmStateEvent
	{
		EVENT_INIT,
		EVENT_UPDATE,
		EVENT_EXIT
	};

	HoPCBangPet();
	~HoPCBangPet();
	
	void	FsmEventProcess(PCBang_FsmStateEvent eStateEvent);
	void	OnEvent(PCBang_FsmStateEvent eEvent, PCBang_FsmState eFsmState);
	
	void		SetFsmState(HoPCBangPet::PCBang_FsmState eFsmState);
	void		SetFsmAttackState(Unit *pAttackChar);
	void        SetFsmHealState(Unit *pHealChar);

	PCBang_FsmState    GetFsmState();
	Unit     *GetAttachChar();
	BOOL	PetNearMonster(Unit *lpNearMonster );

	void    SetSpawn(Unit *pAttachChar, HoPCBangPet::Type type, smPAT3D *meshRes, smPAT3D *boneRes);
	void    SetIdle(Unit *pAttachChar, HoPCBangPet::Type type, smPAT3D *meshRes, smPAT3D *boneRes, Unit *pAttackChar);

	bool	Main();
	bool	Draw(int x, int y, int z, int angleX, int angleY, int angleZ);
	
	HoPCBangPet::Type	GetType();

private:
	Type		m_Type;
	smPAT3D		*m_PetMeshRes;
	smPAT3D     *m_PetBoneRes;
	Unit		*m_TargetChar;
	Unit      *m_AttackChar;
	int			m_iCurrentFrame;

	Unit      *m_AttackCharTarget;

	PCBang_FsmState            m_eCurrentFsmState;
	PCBang_FsmState			m_eNextFsmState;
	bool				m_bFsmChangeFlag;
	bool				m_bMyCharacterFlag;

	//�����µ鸶�� �ӽ������� ���� ������
	POINT3D				m_CurrentPos;
	POINT3D				m_TargetPos;
	POINT3D				m_AttackPos;
	bool				m_bSkillFlag;
	int					m_iParticleID;
	smOBJ3D				*ObjBip;
	bool				m_bAttackTiming;
	//int					m_iHealCount;
	bool				m_bPetAttacking;
};



//------------------------------------------------------------------------
// Name : HoLowLevelPetManager
// Desc : Pet�� �����ϴ� Ŭ����
// Date : 2004.4.19		Author : HongHoDong		Version : 1.0
//------------------------------------------------------------------------
const int MAX_PCBANG_PET = 100;
class HoPCBangPetManager
{
public:
	HoPCBangPetManager();
	~HoPCBangPetManager();
	
private:
	HoPCBangPet	PcBangPetList[MAX_PCBANG_PET];
	smPAT3D			*m_BoneBurstP;
	smPAT3D			*m_BoneBurstS;
	smPAT3D			*m_BoneBurstL;
	smPAT3D			*m_BoneBurstD;
	
	smPAT3D			*m_MeshBurstP;
	smPAT3D			*m_MeshBurstS;
	smPAT3D			*m_MeshBurstL;
	smPAT3D			*m_MeshBurstD;
/*
	enum Type
	{
		BurstP,
		BurstS,
		BurstL,
		BurstD,
		IllusionP,
		IllusionS,
		IllusionL,
		IllusionD,
	}*/

private:
	HoPCBangPet *GetEmptyPet(Unit *pAttachChar);
	HoPCBangPet *GetEmptyIdlePet(Unit *pAttachChar, int petType, Unit *pAttackChar);
public:
	bool	Create();
	bool    Destroy();

	bool    AddPet(Unit *pAttachChar, HoPCBangPet::Type petType);
	bool	AddIdlePet(Unit *pAttachChar, int petType, Unit *pAttackChar);

	void    DeletePet(Unit *pAttachChar);

	bool	Main();
	bool    Draw(int x, int y, int z, int angleX, int angleY, int angleZ);
};


//------------------------------------------------------------------------
// Name : �ܺο��� PetManager�� �������� C Interface �Լ���
// Desc : �ܺο��� PetManager�� �����ϱ� ���� �⺻ �Լ��� �����Ѵ�.
// Date : 2004.4.19		Author : HongHoDong		Version : 1.0
//------------------------------------------------------------------------
extern bool g_PCBang_CreatePetSystem();
extern bool g_PCBang_MainPetSystem();
extern bool g_PCBang_DrawPetSystem(int x, int y, int z, int ax, int ay, int az);
extern bool g_PCBang_DestroyPetSystem();
extern bool g_HoPCBangAddPet(Unit *pAttachChar, HoPCBangPet::Type petType);
extern bool g_HoPCBangAddIdlePet(Unit *pAttachChar, int petType, Unit *pAttackChar = NULL);

extern void g_HoPCBangDeletePet(Unit *pAttachChar);

extern POINT3D HoHoPCBangPetRenderPoint;
extern DWORD  g_HoPCBangPetAttackSerial;

#endif