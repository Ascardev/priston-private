#pragma once

#define STAGE_MAP		(GAMEMAP->spStageMap)

class CGameMap
{
public:
	CGameMap();
	virtual ~CGameMap();

	void Init();
	void Shutdown();

	void Load();
	void LoadStage(BaseMap *psMapFirst, BaseMap *psMapSecond = nullptr);

	Point3D WarpMap(EMapID iID);
	Point3D WarpMap(EMapID iID, int iX, int iZ);
	Point3D WarpMap();
	Point3D WarpMap(EMapID iID, BOOL brnd);
	Point3D WarpCastle();

	void LoadWarpMap(EMapID iID);

	BOOL SetWarpGate(EMapID iID);
	void UpdateWarpGate();
	BOOL IsWarpGate() { return m_bWarpMap; }

	void Update();

	void SetStartPoint();

	void SetGameTime(DWORD dwTime);
	DWORD GetGameTime() { return m_dwTime; }
	DWORD GetGameHour() { return m_dwHour; }
	DWORD GetGameMin() { return m_dwMin; }

	void UpdateGameTime(DWORD dwTime);

	DWORD SystemTimeToGameTime(DWORD dwTime);
public:
	BaseMap * pcaBaseMap;
	BaseMap * spStageMap[2] = { 0 };
private:
	DWORD m_dwTime = 0;
	DWORD m_dwHour = 0;
	DWORD m_dwMin = 0;
	DWORD m_dwSec = 0;

	BaseMap * m_pcLastWarpMap = NULL;
	EMapID m_eWarpMapID = MAPID_Invalid;
	BOOL m_bWarpMap = FALSE;
	DWORD m_dwWarpDelay = 0;
};