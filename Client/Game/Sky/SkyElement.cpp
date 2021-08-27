#include "StdAfx.h"

namespace SKY
{
	/*Element::Element()
	{

	}
	Element::Element(std::string strFileName, BOOL bFadeDelay, Color4D sColor) : m_bFadeDelay(bFadeDelay),m_sColor(sColor)
	{
		m_pcMesh = smASE_Read((char *)strFileName.c_str());

		if (m_pcMesh)
		{
			m_pcMesh->ZeroNormals();
			m_pcMesh->SetClipStates(SMCLIP_NEARZ | SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM, FALSE);
			m_pcMesh->ReadTextures();
		}
	}
	Element::~Element()
	{
		DELET(m_pcMesh);
	}
	void Element::Render(Point3D sCameraPosition, Point3D sCameraAngle)
	{
		if (m_pcMesh)
		{
			GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

			cpRender->SetCameraPosition(sCameraPosition, sCameraAngle);

			m_pcMesh->TmAnimation(0, Point3D(), NULL);
			m_pcMesh->SetPosition(Point3D(), Point3D());
			m_pcMesh->RenderD3D(Point3D(0, sCameraPosition.iY / 8, 0), sCameraAngle);

			GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		}
	}*/
}