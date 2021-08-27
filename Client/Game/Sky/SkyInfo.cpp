#include "StdAfx.h"
#include "SkyInfo.h"

namespace SKY
{
	/*Info::Info()
	{

	}
	Info::~Info()
	{
		for (auto &v : m_pvElement)
		{
			DELET(v);
		}

		m_pvElement.clear();
	}
	void Info::Render(Point3D sCameraPosition, Point3D sCameraAngle)
	{
		for (size_t t = 0; t < m_pvElement.size(); t++)
		{
			auto pcElement = m_pvElement[t];

			if (pcElement)
			{
				auto sBackColor = cpRender->GetColor();

				auto sColor = (m_sBlink.bActive && m_sBlink.bHave && t == 0) ? pcElement->GetColor() + m_sBlink.sColor : pcElement->GetColor();

				if (!pcElement->IsFadeDelay())
					cpRender->m_sColor = m_sAlpha.sMin == 100 ? sColor - Color4D() : Color4D(sColor.iR, sColor.iG, sColor.iB, int((float)sColor.iA * ((float)m_sAlpha.sMin / 100.f))) - Color4D();
				else
					cpRender->m_sColor = m_sAlpha.sMax == 100 ? sColor - Color4D() : Color4D(sColor.iR, sColor.iG, sColor.iB, int((float)sColor.iA * ((float)m_sAlpha.sMax / 100.f))) - Color4D();

				pcElement->Render(sCameraPosition, sCameraAngle);

				cpRender->m_sColor = sBackColor;
			}
		}
	}
	void Info::Tick(int iTime)
	{
		if (m_eAnimation == ESKYANIMATION_FadeIn)
		{
			if (m_sAlpha.sMin < 100 && (iTime % 6) == 0)
				m_sAlpha.sMin++;

			if (m_sAlpha.sMax < 100)
				m_sAlpha.sMax++;

			if (m_sAlpha.sMax >= 100)
				m_eAnimation = ESKYANIMATION_None;
		}
		else if (m_eAnimation == ESKYANIMATION_FadeOut)
		{
			if (m_sAlpha.sMin > 0 && (iTime % 4) == 0)
				m_sAlpha.sMin--;

			if (m_sAlpha.sMin < 20 && m_sAlpha.sMax > 0 && (iTime % 2) == 0)
				m_sAlpha.sMax--;

			if (m_sAlpha.sMin <= 0 && m_sAlpha.sMax <= 0)
			{
				m_sAlpha.sMin = -1;
				m_sAlpha.sMax = -1;

				m_eAnimation = ESKYANIMATION_None;
			}
		}
		else
		{
			if (m_eType == ESKYTYPE_Flash)
				Animation();
		}
	}
	// ´òÉÁÐ§¹û
	void Info::Animation()
	{
		m_sBlink.iTime--;

		if (m_sBlink.iTime < 0)
			m_sBlink.iTime = 200;

		if ((m_sBlink.iTime % 100) == 0 && !m_sBlink.bActive)
		{
			m_sBlink.bActive = TRUE;
			m_sBlink.iCount = 0;
			m_sBlink.sColor = Color4D(90, 90, 90, 90);
		}
		if (m_sBlink.bActive && (m_sBlink.iTime % 5) == 0)
		{
			m_sBlink.bHave = !m_sBlink.bHave;
			m_sBlink.iCount++;
			m_sBlink.sColor -= Color4D(5, 5, 5, 5);

			if (m_sBlink.iCount >= 7)
			{
				m_sBlink.bActive = FALSE;
				m_sBlink.bHave = FALSE;
				m_sBlink.iCount = 0;
			}
		}
	}*/
}