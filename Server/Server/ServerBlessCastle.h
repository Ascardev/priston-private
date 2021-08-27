#pragma once

#define MAX_GOLD_PERBOX						400000000
#define	MAX_SOLDIER_BLESSCASTLE				20

static const Point3D saBlessCastleTowerPosition[] =
{
	{ 34224 , -25857 , 646 },
	{ 34891 , -25857 , 646 },
	{ 33755 , -28297 , 686 },
	{ 35351 , -28297 , 686 },
	{ 34151 , -30313 , 754 },
	{ 34952 , -30313 , 754 },
	{ 0,0,0 }
};

static const Point3D saCastleSoulFountainPosition[2] = 
{ 
	{ 37040	, 0 , -30286 },
	{ 37158	, 0 , -30102 },
};

static const Point3D saCastleGuardPositionA[MAX_SOLDIER_BLESSCASTLE] =
{
	{ 33251, -27968, 688 },
	{ 33339, -27968, 688 },
	{ 33428, -27968, 688 },
	{ 33516, -27968, 688 },
	{ 33605, -27968, 688 },

	{ 33251, -28052, 688 },
	{ 33339, -28052, 688 },
	{ 33428, -28052, 688 },
	{ 33516, -28052, 688 },
	{ 33605, -28052, 688 },


	{ 35497, -27968, 688 },
	{ 35586, -27968, 688 },
	{ 35674, -27968, 688 },
	{ 35763, -27968, 688 },
	{ 35851, -27968, 688 },

	{ 35497, -28052, 688 },
	{ 35586, -28052, 688 },
	{ 35674, -28052, 688 },
	{ 35763, -28052, 688 },
	{ 35851, -28052, 688 }
};


static const Point3D saCastleGuardPositionB[MAX_SOLDIER_BLESSCASTLE] =
{
	{ 33590, -29534, 706 },
	{ 33679, -29534, 706 },
	{ 33767, -29534, 706 },
	{ 33856, -29534, 706 },
	{ 33945, -29534, 706 },

	{ 33590, -29618, 706 },
	{ 33679, -29618, 706 },
	{ 33767, -29618, 706 },
	{ 33856, -29618, 706 },
	{ 33945, -29618, 706 },


	{ 35159, -29534, 706 },
	{ 35248, -29534, 706 },
	{ 35336, -29534, 706 },
	{ 35425, -29534, 706 },
	{ 35513, -29534, 706 },

	{ 35159, -29618, 706 },
	{ 35248, -29618, 706 },
	{ 35336, -29618, 706 },
	{ 35425, -29618, 706 },
	{ 35513, -29618, 706 }
};


static const Point3D saCastleGuardPositionC[MAX_SOLDIER_BLESSCASTLE] =
{
	{ 33898, -30882, 754 },
	{ 33987, -30882, 754 },
	{ 34075, -30882, 754 },
	{ 34164, -30882, 754 },
	{ 34252, -30882, 754 },

	{ 33898, -30967, 754 },
	{ 33987, -30967, 754 },
	{ 34075, -30967, 754 },
	{ 34164, -30967, 754 },
	{ 34252, -30967, 754 },


	{ 34852, -30882, 754 },
	{ 34941, -30882, 754 },
	{ 35029, -30882, 754 },
	{ 35118, -30882, 754 },
	{ 35206, -30882, 754 },

	{ 34852, -30967, 754 },
	{ 34941, -30967, 754 },
	{ 35029, -30967, 754 },
	{ 35118, -30967, 754 },
	{ 35206, -30967, 754 }
};

static const Point3D sCastleValhallaPosition = { 34559, -31375, 800 };
static const Point3D sCastleDoorPosition = { 34552, -25545, 680 };

class CServerBlessCastle
{
public:
	CServerBlessCastle();
	virtual ~CServerBlessCastle();

	void Init();

	void Update();
	void UpdateBC();

	void OnTime();

	void Start();
	void End(BOOL bUnitsAlive);
	void End();
	void SetSiegeWarMode(ESiegeWarMode iNewMode);
	ESiegeWarMode GetSiegeWarMode() { return m_iBlessCastleMode; }
	void SendUserScore(User * pcUser);
	void NetSendBlessCastleStatus(struct NetConnection * psNetConnection = NULL);
	void NetRecvBlessCastleStatus(PacketNetBCStatus * psPacket);

	BlessCastleStatusData * GetBlessCastleStatusData() { return m_psBlessCastleStatusData; }

	void SQLReadBlessCastleStatus();

	void ResetUserScore();

	void SetBlessCastleOwnerClanID(DWORD iClanID);

	void HandlePacket(User * pcUser, PacketBlessCastleStatusSettingsData * psPacket);
	void HandlePacket(User * pcUser, PacketBlessCastleTex * psPacket);
	void HandlePacket(User * pcUser, PacketBlessCastleSkill * psPacket);

	void ProcessPacket(User * pcUser);
	void SendBlessCastleSkill(User * pcUser);
protected:
	void SQLUpdateUserScore(User * pcUser);
	void SQLWriteBlessCastleStatus();
	void UpdateIndividualScores(BOOL bReset = FALSE);
	void SendIndividualScore();
	BOOL CanShowScore();
	void KillBuffs();
	void HandleIndividualScore();
	void GetTop10ClanDamage(Unit * pcUnit, PacketBlessCastleTopData * psPacket);

	void MainFountain();
	int UpdateTower();
	void UpdatePhase(int iPhase);
	int GetBlessCastleSkillSum(User *pcUser, PacketBlessCastleSkill * psPacket);
private:
	BlessCastlePVPLeague  * m_psBlessCastlePVPLeague = nullptr;
	BlessCastleStatusData * m_psBlessCastleStatusData = nullptr;
	ESiegeWarMode m_iBlessCastleMode;
	DWORD m_dwTickUpdateUsersScore = 0;

	Unit * m_pcUnitDoor = nullptr;
	BOOL m_bCastleDoor = FALSE;
	BOOL m_bTowers = FALSE;
	BOOL m_bPhase3 = FALSE;
	BOOL m_bPhase4 = FALSE;
	WORD m_sLastDay = 0;
	WORD m_sLastHour = 0;
	WORD m_sLastMin = 0;
	BOOL m_bInit = FALSE;

	int m_iPhaseID = 0;
	int m_iOldPhaseID = 0;

	DWORD m_dwTickUpdate = 0;
};
