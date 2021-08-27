#pragma once


typedef int EButton;

enum ETYPE
{
	TYPE_None,

	TYPE_Button,
	TYPE_Group,
	TYPE_Window,
	TYPE_Scroller,
	TYPE_Checkbox,
	TYPE_Text,
	TYPE_InputField,
	TYPE_ImageBox,
	TYPE_Tooltip,
};
namespace UI
{
	typedef std::shared_ptr<class Element> LPELEMENT;

	class Element
	{
	public:
		Element();
		Element(class Rectangle2D rRectangle);
		virtual ~Element();

		virtual void Clear() {}
		//Getters and Settings
		virtual int GetID() {return m_iID;}
		virtual void SetID(int iID) {m_iID = iID;}

		virtual int GetX() {return m_rRect.iX;}
		virtual int GetY() {return m_rRect.iY;}

		virtual void SetWidth(int i) {m_rRect.iWidth = i;}
		virtual int GetWidth() {return m_rRect.iWidth;}

		virtual void SetHeight(int i) {m_rRect.iHeight = i;}
		virtual int GetHeight() {return m_rRect.iHeight;}

		virtual void SetYAxis(int iY) {}
		virtual void SetPosition(int iX,int iY) {m_rRect.iX = iX; m_rRect.iY = iY;}

		virtual void SetType(ETYPE e) {m_eType = e;}
		virtual int GetType() {return m_eType;}

		virtual void SetBox(Rectangle2D sBox) {m_rRect = sBox;}
		virtual Rectangle2D GetBox() {return m_rRect;}

		virtual void Update(float fTime) {}

		//Render
		virtual void Render(int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY,int iSourceWidth,int iSourceHeight) {}
		virtual void Render(int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY);

		//Event Handles
		virtual BOOL OnMouseClick(INPUTS::LPMOUSE pcMouse,int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY) {return FALSE;}
		virtual void OnMouseMove(INPUTS::LPMOUSE pcMouse,int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY) {}
		virtual BOOL OnMouseScroll(INPUTS::LPMOUSE pcMouse,int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY) {return FALSE;}

		virtual BOOL OnKeyChar(INPUTS::LPKEYBOARD pcKeyboard) { return FALSE; }
		virtual BOOL OnKeyPress(INPUTS::LPKEYBOARD pcKeyboard) { return FALSE; }

		void Show() { m_bShow = TRUE; }
		void Hide() { m_bShow = FALSE; }
		BOOL IsOpen() { return m_bShow; }

		BOOL IsEnjoin() { return m_bEnjoin; }

		void OnEnjoin() { m_bEnjoin = TRUE; }
		void UnEnjoin() { m_bEnjoin = FALSE; }

		virtual BOOL IsParentChild() { return TRUE; }
	protected:
		int m_iID = -1;
		BOOL m_bShow = TRUE;
		BOOL m_bEnjoin = FALSE;
		BOOL m_bDebug = FALSE;
		Rectangle2D m_rRect;
		ETYPE m_eType = TYPE_None;
		std::vector<LPELEMENT> m_vElementChild;
	};
}