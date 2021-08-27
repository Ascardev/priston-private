#pragma once


class CMiniMapHandle
{
public:
	CMiniMapHandle();
	virtual ~CMiniMapHandle();

	void Init();
	void Shutdown();

	void Render();

	void Update(float fTime);

	void OnMouseMove(class INPUTS::Mouse * pcMouse);
	BOOL OnMouseClick(class INPUTS::Mouse *pcMouse);

	BOOL IsOpen() { return m_bShow; }

	void Show() { m_bShow = TRUE; }
	void Hide() { m_bShow = FALSE; }

	void OnResolutionChanged();

	void LoadMiniMap(int iIndex, BaseMap * pcMap, smSTAGE3D * pcStage);

	//void OnChangeMap(int iMapID);

	void HandlePacket(PacketBossTimeUpdate * psPacket);
	void ProcessPacket(PacketBossTimeUpdate * psPacket);
protected:
	void RenderMap(Point3D sUserPosition);
	void RenderUser(Point3D sUserAngle);
	BOOL RenderNPC(Unit * pcUnit, Point3D sUserPosition, int iSize);
	BOOL RenderPlayer(Unit * pcUnit, Point3D sUserPosition, int iUserClanID, int iSize);
	BOOL RenderParty(Point3D sUserPosition, int iUserID, int iSize);
	Point2D GetMiniMapPostion() { return Point2D(m_sBox.iX, m_sBox.iY); }
	void SetMiniMapPostion(Point2D sPosition) { m_sBox.iX = sPosition.iX; m_sBox.iY = sPosition.iY; }
	void DrawMinimap(MiniMapData  * psMap, int iX, int iY, int iSize);
	MiniMapData * GetMiniMapData(int i) { return i == 0 ? &m_saMaps[0] : &m_saMaps[1]; }
	Point2D GetMinimapPositionFromCenter(Point3D sCenterPosition, Point3D sObjectPosition, int iWidthPoint, int iHeightPoint, int iSize);
	BOOL IsHave();
private:
	BOOL m_bInitialized = FALSE;
	BOOL m_bActive = FALSE;
	BOOL m_bShow = TRUE;

	UI::LPIMAGE	m_pcMaskBackground = NULL;
	UI::LPIMAGE	m_pcMaskBackgroundActive = NULL;
	UI::LPIMAGE	m_pcBorderImage = NULL;
	UI::LPIMAGE	m_pcMapImage = NULL;
	UI::LPIMAGE	m_pcUserPoint = NULL;
	UI::LPIMAGE	m_pcNPCPoint = NULL;
	UI::LPIMAGE	m_pcImageNextBoss = NULL;

	UI::LPIMAGE	m_pcImageEnemyIcon = NULL;
	UI::LPIMAGE	m_pcImageFriendlyIcon = NULL;
	UI::LPIMAGE	m_pcaImagesPartyMemberIcon[MAX_PARTY_MEMBERS];
	UI::LPIMAGE	m_pcImageRaidIcon = NULL;

	DX::LPEFFECT m_pEffectMask;
	DX::LPRENDERTARGET	m_pRenderTargetMask;

	BOOL m_bSelected;
	Point2D m_sPointMouse;

	Rectangle2D m_sBox;
	//Point2D m_saMinimaps[4];

	MiniMapData m_saMaps[2] = { 0 };

	DX::LPFONT m_pFont;
	int m_iMinimapSize = 138;

	BOOL m_bIsHoverUnit = FALSE;
	Rectangle2D m_sHoverUnitBox = Rectangle2D();
	std::string m_strHoverUnit;
	UI::Color m_cHoverColor = UI::Color();
	UI::LPTOOLTIP m_pTooltipUnit;

	BOOL m_bShowBossTime = FALSE;
	std::string m_strNextBossName;
	DWORD m_dwNextBossTime = 0;
	DWORD m_dwTickTime = 0;
};