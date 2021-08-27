#pragma once

namespace UI
{
	class ComboBox : public Element
	{
	public:
		ComboBox(Rectangle2D rRectangle);
		virtual ~ComboBox();

		void Clear();

		LPTEXT MakeOption(const std::string &strText,const Rectangle2D &rBox,BOOL bBold,const DWORD dwColor);
		void AddOption(LPTEXT p);
		void AddOption(LPTEXT p,int iID);

		void Render(int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY);

		void SetHoverColor(DWORD dwColor){m_dwHoverColor = dwColor;}
		void SetBackgroundImage(std::pair<class Image *,class Image *> pPair);
		void SetBackgroundSelectImage(class Image *pImage) {m_pBackgroundActiveTopImage = pImage;}
		void SetBackgroundActiveImage(std::pair<class Image *,class Image *> pPair);
		void SetChangeEvent(int iEvent){m_iEventID = iEvent;}

		int GetSelectID(){return m_iSelectID;}

		std::string GetTextOption(int iIDObject);

		BOOL OnMouseClick(class INPUTS::Mouse *pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
		void OnMouseMove(class INPUTS::Mouse *pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
	private:
		class Image *m_pBackgroundImage = NULL;
		class Image *m_pBackgroundActiveImage = NULL;
		class Image *m_pBackgroundActiveTopImage = NULL;
		class Image *m_pBackgroundActiveMiddleImage = NULL;
		class Image *m_pBackgroundActiveBottomImage = NULL;

		BOOL m_bShowMenu = FALSE;
		BOOL m_bHover = FALSE;

		std::vector<LPTEXT> m_vTextOptions;

		LPTEXT m_pTextValue;

		DWORD m_dwHoverColor = -1;

		int m_iEventID = 0;
		int m_iHeightMenu = 0;
		int m_iSelectID = -1;

		Rectangle2D m_rOptionPosition;
	};
}