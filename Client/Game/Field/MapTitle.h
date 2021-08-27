#pragma once

class smCHAR;

namespace MAP
{
	typedef class Title *LPTITLE;

	class Title
	{
	public:
		Title();
		virtual ~Title();

		void Init();
		void Shutdown();

		void Update() {};

		void Render();

		BOOL IsActive() { return m_bActive; }

		void Open() { m_bFlag ? 0 : m_bFlag = TRUE; }
		void Close() { m_bFlag ? m_bFlag = FALSE : 0; }

		BOOL OnMouseClick(INPUTS::LPMOUSE pcMouse);
		void OnMouseMove(INPUTS::LPMOUSE pcMouse);
	protected:
		void RenderMap(Point3D sUserPosition);
		void RenderUser(Point3D sUserAngle);
		BOOL RenderNPC(smCHAR *pcChar, Point3D sUserPosition, int iSize);
		BOOL RenderPlayer(smCHAR *pcChar, Point3D sUserPosition, int iUserClanID, int iSize);
		void RenderParty(Point3D sUserPosition, int iUserID, int iSize);
		Point2D GetMinimapPositionFromCenter(Point3D sCenterPosition, Point3D sObjectPosition, int iWidthPoint, int iHeightPoint, int iSize);
		Point2D GetMiniMapPostion() { return Point2D(m_sBox.iX, m_sBox.iY); }
		void SetMiniMapPostion(Point2D sPosition) { m_sBox.iX = sPosition.iX; m_sBox.iY = sPosition.iY; }
		BOOL IsHave();
	private:
		UI::LPIMAGE m_pcMaskBackground = NULL;
		UI::LPIMAGE m_pcMaskBackgroundActive = NULL;
		UI::LPIMAGE m_pcBorderImage = NULL;
		UI::LPIMAGE m_pcUserPoint = NULL;
		UI::LPIMAGE m_pcNPCPoint = NULL;
		UI::LPIMAGE m_pcImageRaidIcon = NULL;
		UI::LPIMAGE m_pcImageEnemyIcon = NULL;
		UI::LPIMAGE m_pcImageFriendlyIcon = NULL;
		UI::LPIMAGE m_pcImageNextBoss = NULL;
		UI::LPIMAGE m_pcaImagesPartyMemberIcon[6] = { 0 };
		UI::LPTOOLTIP m_pcToolTip = NULL;
		DX::LPEFFECT m_pEffectMask = NULL;
		DX::LPRENDERTARGET m_pRenderTargetMask = NULL;
		DX::LPFONT m_pFont = NULL;
		UI::Color m_cHoverColor = UI::Color();
		BOOL m_bIsHover = FALSE;
		BOOL m_bActive = FALSE;
		BOOL m_bSelected = FALSE;
		BOOL m_bFlag = FALSE;
		Point2D	m_sPointMouse;
		Rectangle2D m_sBox;
		Rectangle2D	m_sHoverUnitBox = Rectangle2D();
		std::string m_strHoverUnit;

	};
}
