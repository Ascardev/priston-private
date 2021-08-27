#pragma once

namespace MAP
{
	struct MapWarpPosition
	{
		EMapID eID = MAPID_Invalid;
		int iX = 0;
		int iY = 0;
		std::string str;

		MapWarpPosition() : eID(MAPID_Invalid), iX(0), iY(0)
		{
			str = "Resources\\UI\\Warp\\Text\\Default.txt";
		}
		MapWarpPosition(EMapID eID, int iX, int iY, std::string str)
		{
			this->eID = eID;
			this->iX = iX;
			this->iY = iY;
			this->str = str;
		}
	};

	typedef class Warp *LPWARP;

	class Warp
	{
	public:
		Warp();
		virtual ~Warp();

		void Init();
		void Shutdown();

		void Open();
		void Close();

		void Update();

		void Render();

		BOOL OnMouseClick(INPUTS::LPMOUSE pcMouse);
		void OnMouseMove(INPUTS::LPMOUSE pcMouse);

		enum
		{
			TEXTWINDOWID,
		};

	protected:
		void BuildWindow();
		void OnClickClose(UIEventArgs e);
		void OnTeleport();
		void Animation();
		void LoadTextFromFile();
		Point2D GetWarpPosition() { return Point2D(m_sBox.iX, m_sBox.iY); }
		void SetWarpPostion(Point2D sPosition) { m_sBox.iX = sPosition.iX; m_sBox.iY = sPosition.iY; }
	private:
		Rectangle2D m_sBox;
		Rectangle2D m_sAniBox;
		Point2D m_sPointMouse;
		UI::LPWINDOW m_pcWindow = NULL;
		UI::LPIMAGE m_pcImage = NULL;
		UI::LPIMAGE m_pcIcon = NULL;
		UI::LPIMAGE m_pcSelect = NULL;
		UI::LPBUTTON m_pcClose = NULL;
		std::vector<MapWarpPosition> m_vPosition;
		MapWarpPosition m_sPosition;
		BOOL m_bActive = FALSE;
		BOOL m_bHover = FALSE;
		BOOL m_bSelected = FALSE;
		BOOL m_bAnimation = FALSE;
		float m_fProcess = 1.0f;
		EMapID m_eID = EMapID(-2);
	};
}
