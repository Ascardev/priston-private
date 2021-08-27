#pragma once

#define DEFAULT_ITEMS_PER_COLUMN	5

#define ITEMTIMER_WIDTH				38
#define ITEMTIMER_HEIGHT			38

#define POS_ITMTMRBASEX				10
#define POS_ITMTMRBASEY				165
#define TMR_SPACEX					40
#define TMR_SPACEY					40

namespace ITEMTIME
{
	class ItemTimer
	{
		friend class Window;
	public:
		ItemTimer(EItemTimerType eType, const char *pszTitle, const char *pszDescript);
		ItemTimer(ItemTimer *pItemTimer, DWORD dwTimeLeft, DWORD dwTimeTotal);
		virtual ~ItemTimer();

		void Clear();

		void Render();

		void Loop();
		void Tick();

		void OnMouseMove(class INPUTS::Mouse *pcMouse);

		void FreezeMap(int iMapID) { m_vFreezeMaps.push_back(iMapID); }
	private:
		EItemTimerType m_eType;

		int m_iFade = 0;
		int m_iColumn = 0;

		DWORD m_dwTimeLeft = 0;
		DWORD m_dwTimeTotal = 0;

		Rectangle2D m_sPosition;
		Rectangle2D m_sMoveTo;

		std::string m_strTitle = "";
		std::string m_strDescription = "";

		UI::LPIMAGE m_pcImage = nullptr;
		UI::LPIMAGE m_pcImageBackground = nullptr;

		BOOL m_bView = FALSE;
		BOOL m_bAlive = TRUE;
		BOOL m_bFreeze = FALSE;

		std::vector<int> m_vFreezeMaps;
	};

	class Window : public CBaseWindow
	{
	public:
		Window();
		Window(EWindow eID);
		virtual ~Window();

		void Init();
		void Shutdown();

		BOOL AddTimer(EItemTimerType eType, DWORD dwTimeLeft, DWORD dwTimeTotal);

		void Render();

		void Loop();
		void Tick();

		void OnMouseMove(class INPUTS::Mouse *pcMouse);
		BOOL OnMouseClick(class INPUTS::Mouse *pcMouse);

		void OnResolutionChanged();
	protected:
		void OnClickCancelOK(ItemTimer *pcTimer, UIEventArgs eArgs);
		void RemoveTimer(ItemTimer *pcTimer);
		ItemTimer *GetItemTimer(EItemTimerType eType);
		ItemTimer *GetPrefab(EItemTimerType eType);
		ItemTimer *AddTimer(ItemTimer *pcTimer);
		ItemTimer *GetHead();
	private:
		UI::LPIMAGE m_pcImageBox = nullptr;
		DX::LPFONT m_pcFont = nullptr;
		std::vector<ItemTimer *> m_pcaItemTimer;
		std::vector<ItemTimer *> m_pcaItemTimerPrefab;
	};
}