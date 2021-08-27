#pragma once

namespace UI
{
	typedef std::shared_ptr<class ImageBox> LPIMAGEBOX;

	class ImageBox : public Element
	{
	public:
		ImageBox(class Rectangle2D rRectangle);
		virtual ~ImageBox();

		void Clear();
		void SetImage(Image *pImage);
		void SetActiveImage(std::pair<class Image *,class Image *> pPair);
		void SetGroup(std::shared_ptr<Group> pGroup);
		void SetColor(DWORD dwColor) { m_dwColor = dwColor; }

		void SetSourceBox(Rectangle2D sBox) { m_sSourceBox = sBox; }
		void SetTexture(LPDIRECT3DTEXTURE9 ps) {m_pTexture = ps;}
		void SetScale(float f) {m_fScale = f;}
		void SetEvent(int iEvent) { m_iEvent_MoveID = iEvent; }

		void SetLeft(int i) { m_iLeft = i; }
		void SetTop(int i) { m_iTop = i; }

		Image *GetImage() {return m_pImage;}
		Image *GetImageActive1() {return m_pImageActive1;}
		Image *GetImageActive2() {return m_pImageActive2;}

		BOOL IsHover() { return m_bHover; }

		void Swap();
		void Swap(BOOL bActiveImage);

		void Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
		void OnMouseMove(INPUTS::LPMOUSE pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
	private:
		class Image *m_pImage = NULL;
		class Image *m_pImageActive1 = NULL;
		class Image *m_pImageActive2 = NULL;

		int m_iEvent_MoveID = 0;
		float m_fScale = 1.0f;
		DWORD m_dwColor = -1;
		LPDIRECT3DTEXTURE9 m_pTexture = NULL;

		int m_iLeft = 0;
		int m_iTop = 0;

		std::shared_ptr<class Group> m_pGroup = NULL;

		Rectangle2D m_sSourceBox;

		BOOL m_bHover = FALSE;
	};
}