#pragma once

namespace MAP
{
	typedef class Window *LPWINDOW;

	class Window
	{
	public:
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
		};
		Window();
		virtual ~Window();

		void Init();
		void Shutdown();

		void Open() { m_pcWindow->Show(); }
		void Close();

		void Update() {};

		void Render();

		BOOL OnMouseClick(INPUTS::LPMOUSE pcMouse);
		void OnMouseMove(INPUTS::LPMOUSE pcMouse);
	protected:
		void BuildWindow();
		void BuildInfo();
		void BuildMap();
		void OnButtonMouseMoveIn(int iID);
		void OnButtonMouseMoveOut();
	private:
		UI::LPWINDOW m_pcWindow = NULL;
	};
}