#pragma once

namespace UI
{
	enum EMENUTYPE
	{
		EMENUTYPE_None,

		EMENUTYPE_Vertical,
		EMENUTYPE_Horizontal,
	};
	enum EMENUPOSITION
	{
		EMENUPOSITION_None,

		EMENUPOSITION_Top,
		EMENUPOSITION_Bottom,
		EMENUPOSITION_Left,
		EMENUPOSITION_Right,
	};
	struct OPTION
	{
		LPTEXT pText;
		BOOL	bChild;
	};

	typedef std::shared_ptr<class Menu> LPMENU;

	class Menu : public Element
	{
	public:
		Menu();
		Menu(Rectangle2D sBox);
		virtual ~Menu();

		void Open();
		void Close();

		void Clear();

		void SetBackground(std::string strImageTop,std::string strImageMiddle,std::string strImageBottom,std::string strImageMain);

		LPTEXT MakeOption(const std::string &strText,const Rectangle2D &rBox,BOOL bBold,const DWORD dwColor,const DWORD dwHoverColor);
		void AddOption(LPTEXT p,BOOL bChild);
		void AddOption(LPTEXT p,BOOL bChild,int iID);

		void RemoveOption(int iID);

		void SetEvent(int iEvent){m_iEventID = iEvent;}
		void SetGroup(LPGROUP p) {m_pGroup = p;}

		int GetOptionID() {return m_iOptionID;}
		void SetOptionID(int iID) {m_iOptionID = iID;}

		EMENUPOSITION GetMenuPosition() {return m_ePosition;}
		void SetMenuPosition(EMENUPOSITION e) { m_ePosition = e; }

		EMouseEvent GetMouseEvent() {return m_eMouseEvent;}
		void SetMouseEvent(EMouseEvent e) {m_eMouseEvent = e;}

		void Animate();
		void Render(int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY);
		void Update(float fTime);

		BOOL OnMouseClick(class INPUTS::Mouse *pcMouse,int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY);
		void OnMouseMove(class INPUTS::Mouse *pcMouse,int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY);
	private:
		int m_iEventID = 0;
		int m_iOptionID = -1;
		int m_iHeightMenu = 0;

		class Image *m_pImageTop = NULL;
		class Image *m_pImageMiddle = NULL;
		class Image *m_pImageBottom = NULL;
		class Image *m_pImageMain = NULL;

		BOOL m_bAnimate = FALSE;
		BOOL m_bOpen = FALSE;
		BOOL m_bClose = FALSE;

		float m_fProgress = 0.0f;
		Point2D m_sAniatebox = Point2D();

		std::vector<OPTION> m_vOptions;

		LPGROUP m_pGroup = NULL;
		EMENUTYPE m_eType = EMENUTYPE_None;
		EMENUPOSITION m_ePosition = EMENUPOSITION_None;
		EMouseEvent m_eMouseEvent = ClickDownL;
	};
}