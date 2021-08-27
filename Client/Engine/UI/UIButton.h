#pragma once

namespace UI
{
	typedef std::shared_ptr<class Button> LPBUTTON;

	class Button : public Element
	{
	public:
		Button(Rectangle2D rRectangle);
		virtual ~Button();

		void Clear();

		void SetParentChild(BOOL b) {m_bParentChild = b;}
		BOOL IsParentChild() {return m_bParentChild;}

		BOOL IsHover() {return m_bHover;}

		void SetSelected(BOOL b) {m_bSelect = b; if (m_pGroup) m_pGroup->SetIndexObject(GetID());}
		BOOL IsSelected() {return m_bSelect;}

		void SetSelect(BOOL b) {m_bSelectType = b;}
		void SetAnimation(BOOL b) { m_bAnimate = b; }

		void SetEvent(int iEvent) { m_iEventID = iEvent; }

		void SetImage(class Image *pImage) {m_pImage = pImage;}
		void SetActiveImage(std::pair<class Image *,class Image *> pPair);
		void SetDisabledImage(class Image *pImage) { m_pImageDisable = pImage; }
		void SetAnimateImage(class Image *pImage) { m_pImageAnimate = pImage; }
		void SetGroup(std::shared_ptr<class Group> pGroup) { m_pGroup = pGroup; }
		void SetCanHold(BOOL b){m_bCanHold = b;}
		void SetMouseEvent(EMouseEvent e) { m_eMouseEvent = e; }
		void SetMenu(LPMENU p) { m_pMenu = p; }

		void Enable() { m_bDisable = FALSE; }
		void Disable() { m_bDisable = TRUE; }

		void Render(int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY);

		BOOL OnMouseClick(class INPUTS::Mouse *pcMouse,int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY);
		void OnMouseMove(class INPUTS::Mouse *pcMouse,int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY);
	protected:
		void Animate();
	private:
		class Image *m_pImage = NULL;
		class Image *m_pImageActive = NULL;
		class Image *m_pImageDisable = NULL;
		class Image *m_pImageAnimate = NULL;
		int m_iEventID = 0;
		BOOL m_bParentChild = TRUE;
		BOOL m_bHover = FALSE;
		BOOL m_bSelect = FALSE;
		BOOL m_bSelectType = FALSE;
		BOOL m_bCanHold = FALSE;
		BOOL m_bHolding = FALSE;
		BOOL m_bDisable = FALSE;

		BOOL m_bAnimate = FALSE;
		BOOL m_bAnimateFade = FALSE;
		Rectangle2D m_sAnimateBox;
		float m_fProgress = 1.0f;
		EMouseEvent m_eMouseEvent = ClickDownL;
		std::shared_ptr<class Group> m_pGroup = NULL;

		LPMENU m_pMenu = NULL;
	};
}