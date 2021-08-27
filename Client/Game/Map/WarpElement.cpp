#include "StdAfx.h"
#include "WarpElement.h"

namespace MAP
{
	namespace WARP
	{
		ElementOut::ElementOut()
		{

		}
		ElementOut::ElementOut(EMapID eID, int iX, int iZ, int iY) : m_eID(eID), m_sPosition(Point3D(iX, iY, iZ))
		{
			
		}
		ElementOut::~ElementOut()
		{

		}

		ElementIn::ElementIn()
		{

		}
		ElementIn::ElementIn(EMapID eID, int iX, int iZ, int iY, int iWidth, int iHeight, int iType) : m_eID(eID), m_sPosition(Point3D(iX, iY, iZ)), m_iWidth(iWidth), m_iHeight(iHeight), m_iType(iType)
		{

		}
		ElementIn::~ElementIn()
		{

		}
		void ElementIn::AddElement(EMapID eID, int iX, int iZ, int iY)
		{
			m_vElement.push_back(ElementOut(eID, iX << 8, iZ << 8, iY << 8));
		}
		ElementOut *ElementIn::GetElement()
		{
			return m_vElement.size() ? &m_vElement[rand() % m_vElement.size()] : nullptr;
		}
		BOOL ElementIn::IsInto(Point3D sPosition)
		{
			int iDist, iX, iY, iZ;

			sPosition.GetPTDistanceXZY(&sPosition, iDist, iX, iY, iZ);

			return (iX < 1024 && iZ < 1024 && iDist < m_iWidth * m_iWidth && iY < m_iHeight) ? TRUE : FALSE;
		}
	}
}