#pragma once

namespace UI
{
	typedef std::shared_ptr<class Scroll> LPSCROLL;

	class Scroll : public Element
	{
	public:
		Scroll(class Rectangle2D rRectangle);
		virtual ~Scroll();

		void Clear();

		void SetMinMax(int iMin, int iMax) { m_fMinScroll = (float)iMin; m_fMaxScroll = (float)iMax; }

		void SetPercent(int iCur);
		int GetPercent();

		void SetParentChild(BOOL bParent) { m_bParentChild = bParent; }
		void SetVertical(BOOL bType) { m_bVertical = bType; }

		BOOL IsParentChild() { return m_bVertical; }

		void SetEvent(int iEventID) { m_iEventID = iEventID; }
		void SetImage(class Image *pImage) { m_pImage = pImage; }

		void SetScroller(class Image *pImage, int iWidth, int iHeight) { m_pImageScroll = pImage; m_iWidthScroll = iWidth; m_iHeightScroll = iHeight; }
		void SetImageBackground(class Image *pImage) { m_pImageBackground = pImage; }

		void SetGroup(std::shared_ptr<class Group> pGroup) { m_pGroup = pGroup; }
		void SetY(int iY) { m_pScroll->iY = iY; }

		//Render
		void Render(int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY);

		//Event Handles
		BOOL OnMouseClick(INPUTS::LPMOUSE pcMouse,int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY);
		BOOL OnMouseScroll(INPUTS::LPMOUSE pcMouse,int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY);
		void OnMouseMove(INPUTS::LPMOUSE pcMouse,int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY);
	private:
		Rectangle2D *m_pScroll;
		class Image *m_pImage = NULL;
		class Image *m_pImageScroll = NULL;
		class Image *m_pImageBackground = NULL;
		int m_iEventID = -1;
		int m_iWidthScroll = 0;
		int m_iHeightScroll = 0;
		int m_iCurrentPercent = 0;
		float m_fMinScroll = 0.0f;
		float m_fMaxScroll = 100.0f;
		BOOL m_bParentChild = TRUE;
		BOOL m_bVertical = TRUE;
		BOOL m_bScrollable = FALSE;
		LPGROUP m_pGroup = NULL;
	};
}