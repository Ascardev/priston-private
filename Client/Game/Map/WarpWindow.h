#pragma once

namespace MAP
{
	namespace WARP
	{
		class Window : public CBaseWindow
		{
			enum
			{
				WINDOWID_Info,
				WINDOWID_Map,

				LISTID_Main,

				TEXTWINDOWID,

				BUTTONID_RicartenTown,
				BUTTONID_PhillaiTown,
				BUTTONID_LandOfDusk,
				BUTTONID_BambooForest,
				BUTTONID_RuinenVillage,
				BUTTONID_NaviskoTown,
				BUTTONID_ForbiddenLand,
				BUTTONID_Eura,
				BUTTONID_LandOfChaos,
				BUTTONID_BlessCastle,
			};
		public:
			Window();
			Window(EWindow eID);
			virtual ~Window();

			void Init();
			void Shutdown();

			void Render();

			BOOL OnMouseClick(INPUTS::LPMOUSE pcMouse);
			void OnMouseMove(INPUTS::LPMOUSE pcMouse);

			void Show();
		protected:
			void BuildWindow();
			void BuildInfo();
			void BuildMap();
			void BuildText(UI::LPTEXTWINDOW pTextWindow);
			UI::LPBUTTON AddButton(int iID, int iX, int iY, EMapID eID);

			void OnButtonMouseMoveIn(int iID);
			void OnButtonMouseMoveOut();
			void OnButtonWarpGate(int iID);
			void OnButtonClose();
			void OnWarpGate(int iID);
			void WarpGate(EMapID eID);
		private:
			UI::LPWINDOW m_pWindow = NULL;
		};
	}
}
