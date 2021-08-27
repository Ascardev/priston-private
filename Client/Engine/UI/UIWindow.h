#pragma once

#include "UIElement.h"

namespace UI
{
	typedef std::shared_ptr<class Window> LPWINDOW;

	class Window : public Element
	{
	public:
		Window(Rectangle2D rRectangle);
		virtual ~Window();

		void Clear();

		int GetType() { return TYPE_Window; }
		void SetImage(class Image *pImage) { m_pImage = pImage; }
		void SetMoveBox(Rectangle2D s) { m_rRectSelectMove = s; }
		void SetCanMove(BOOL b) { m_bCanMove = b; }
		void SetScroll(LPSCROLL pScroll) { m_pScroll = pScroll; }
		void SetGroup(LPGROUP pGroup) { m_pGroup = pGroup; }
		void SetEvent(int iEvent) { m_iEventID = iEvent; }
		void SetEvent(int iEvent, EMouseEvent e) { m_iEventID = iEvent; m_eMouseEvent = e; }
		void SetHoverEvent(int iEvent) { m_iHoverEventID = iEvent; }
		void SetBox(Rectangle2D sBox);
		BOOL IsHover();
		void SetColorBackground(Color c) { m_cColorBackground = c; }
		void SetFocusWindow(BOOL b) { m_bFocusWindow = b; }
		BOOL GetFocusWindow() { return m_bFocusWindow; }
		void Update(float fTime);
		void Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY, int iSourceWidth = -1, int iSourceHeight = -1);
		BOOL OnMouseClick(class INPUTS::Mouse *pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
		BOOL OnMouseScroll(class INPUTS::Mouse *pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
		void OnMouseMove(class INPUTS::Mouse *pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
		BOOL OnKeyChar(class INPUTS::KeyBoard *pcKeyboard);
		BOOL OnKeyPress(class INPUTS::KeyBoard *pcKeyboard);
		void AddElement(LPELEMENT pElement);
		BOOL DelElement(LPELEMENT pElement);

		template <class F>
		inline std::shared_ptr<F> GetElement(int iIDObject)
		{
			for (auto &v : m_vElementChild)
			{
				if (v->GetID() == iIDObject)
				{
					return std::static_pointer_cast<F>(v);
				}
			}
			return NULL;
		};
	private:
		class Image *m_pImage = NULL;
		int m_iEventID = 0;
		int m_iHoverEventID = 0;
		Rectangle2D m_rRectSelectMove;
		Rectangle2D m_rRectViewPort;
		BOOL m_bCanMove = FALSE;
		BOOL m_bFocusWindow = TRUE;
		BOOL m_bIsHover = FALSE;
		BOOL m_bSelected = FALSE;
		LPSCROLL m_pScroll = NULL;
		LPGROUP m_pGroup = NULL;
		EMouseEvent m_eMouseEvent = ClickDownL;
		Color m_cColorBackground = 0;
		Point2D m_sPointMouse;
	};
}
