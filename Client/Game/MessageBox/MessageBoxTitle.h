#pragma once

#define MAX_MESSAGES			3
#define MAX_DURATION_TITLEBOX	10
#define MAX_DURATION_ANIM		600

//#define TITLEBOX				MESSAGEBOXTITLE->AddTextEx;

namespace MESSAGEBOX
{
	typedef class Title *LPTITLE;

	struct sTitle
	{
		BOOL bMoveToDown = TRUE;
		BOOL bCanHide = FALSE;
		Point2D sPosition;
		int iBasePositionY = 0;
		std::string strText;
		D3DXCOLOR d3dColor;
		short sDuration;
		float fTime = MAX_DURATION_ANIM;
		int iOpacity = 255;

		sTitle() = default;
		sTitle(Point2D sPos, std::string str, D3DXCOLOR color, short sDur) { sPosition.iX = 0; sPosition.iY = sPos.iY; strText = str; d3dColor = color; sDuration = sDur; }
	};
	class Title
	{
	public:
		Title();
		virtual ~Title();

		void Init();
		void Shutdown();
		void Clear();
		void AddTextEx(const char *pszFormat, ...);
		void Render();
		void RenderTextMiddle(const char *pszText);
		void Update(float fTime);
		void Tick();
	protected:
		void AddText(const char *pszText);
		void AddTitle(sTitle t);
	private:
		UI::LPIMAGE m_pImageLeft = NULL;
		UI::LPIMAGE m_pImageCenter = NULL;
		UI::LPIMAGE m_pImageRight = NULL;
		DX::LPFONT m_pFontHeigh = NULL;
		DX::LPFONT m_pFont = NULL;
		std::vector<sTitle> m_vTitles;
	};
}
