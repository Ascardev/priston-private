#pragma once

class smPAT3D;

namespace SKY
{
	class Element
	{
	public:
		Element();
		Element(std::string strFileName, BOOL bFadeDelay, Color4D sColor);
		virtual ~Element();

		void Render(Point3D sCameraPosition, Point3D sCameraAngle);

		BOOL IsFadeDelay() { return m_bFadeDelay; }
		Color4D GetColor() { return m_sColor; }
	private:
		BOOL m_bFadeDelay = FALSE;
		Color4D m_sColor;
		smPAT3D *m_pcMesh = NULL;
	};
}
