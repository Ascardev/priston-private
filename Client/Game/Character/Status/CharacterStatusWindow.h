#pragma once

namespace CHARACTER
{
	namespace STATUS
	{
		class Window : public CBaseWindow
		{
			enum EElementsID
			{
				//Windows
				WINDOWID_Box,
				//Image
				IMAGEBOXID_Character,

				IMAGEBOXID_Organic,
				IMAGEBOXID_Posion,
				IMAGEBOXID_Fire,
				IMAGEBOXID_Lightning,
				IMAGEBOXID_Frost,

				//LIST
				LISTID_WindowBox,

				//Text
				TEXTID_Name,
				TEXTID_Title,
				TEXTID_Clan,
				TEXTID_Level,

				TEXTID_HP,
				TEXTID_MP,
				TEXTID_SP,

				TEXTID_StatsPoint,

				TEXTID_Str,
				TEXTID_Spi,
				TEXTID_Tal,
				TEXTID_Agi,
				TEXTID_Vit,

				TEXTID_AttackPower,
				TEXTID_AttackRating,
				TEXTID_Defense,
				TEXTID_Absorption,
				TEXTID_MoveSpeed,
				TEXTID_Critical,
				TEXTID_Block,
				TEXTID_Evade,

				TEXTID_Organic,
				TEXTID_Posion,
				TEXTID_Fire,
				TEXTID_Lightning,
				TEXTID_Frost,

				//Check
				CHECKBOXID_FastAdd,

				//Button
				BUTTONID_Str,
				BUTTONID_Spi,
				BUTTONID_Tal,
				BUTTONID_Agi,
				BUTTONID_Vit,

				TOOLID_Tip,
			};
		public:
			Window();
			Window(EWindow eID);
			virtual ~Window();

			void Init();
			void Shutdown();

			void Render();
			void Update(float fTime);

			void Tick();

			void Show();

			void OnMouseMove(INPUTS::LPMOUSE pcMouse);
			BOOL OnMouseClick(INPUTS::LPMOUSE pcMouse);
			BOOL OnMouseScroll(INPUTS::LPMOUSE pcMouse);
		protected:
			void BuidWindow();
			void Load();
			void OnClose(UIEventArgs eArgs);
			void OnUpdateStatus(int iID);
			void OnImageBoxMouseMove(int iID);
		private:
			UI::LPWINDOW m_pWindow;
		};
	}
}
#pragma once
