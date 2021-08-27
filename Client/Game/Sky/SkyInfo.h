#pragma once

namespace SKY
{
	/*enum ESKYANIMATION
	{
		ESKYANIMATION_None,
		ESKYANIMATION_FadeIn,
		ESKYANIMATION_FadeOut,
	};
	enum ESKYTYPE
	{
		ESKYTYPE_None,
		ESKYTYPE_Flash,
		ESKYTYPE_Snow,
	};

	class Info
	{
		struct Blink
		{
			int iTime = 200;
			int iCount = 0;
			Color4D sColor = Color4D(65, 65, 65, 65);
			BOOL bActive = FALSE;
			BOOL bHave = FALSE;
		};
	public:
		Info();
		virtual ~Info();

		void Render(Point3D sCameraPosition, Point3D sCameraAngle);

		void Tick(int iTime);

		ESKYANIMATION GetAnimation() { return m_eAnimation; }

		void Fade(ESKYANIMATION eAnimation, MinMax sAlpha) { m_eAnimation = eAnimation; m_sAlpha = sAlpha; }

		void SetType(ESKYTYPE eType) { m_eType = eType; }

		void AddElement(std::string strFileName, BOOL bFadeDelay, Color4D sColor)
		{
			m_pvElement.push_back(new Element(strFileName, bFadeDelay, sColor));
		}
	protected:
		void Animation();
	private:
		Blink m_sBlink;
		MinMax m_sAlpha;

		ESKYTYPE m_eType = ESKYTYPE_None;
		ESKYANIMATION m_eAnimation = ESKYANIMATION_None;
		std::vector<Element *> m_pvElement;
	};*/
}