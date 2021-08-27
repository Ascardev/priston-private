#pragma once

namespace UI
{
	class Animation : public Element
	{
	public:
		Animation(Rectangle2D rRectangle);
		virtual ~Animation();

		void Clear();

		void SetImage(LPIMAGE pcImage) { m_pcImage = pcImage; }

		void Update();


	private:
		LPIMAGE m_pcImage = NULL;
		int 
	};
}
