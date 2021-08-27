#include "StdAfx.h"
#include "BorderElement.h"

namespace MAP
{
	namespace BORDER
	{
		Element::Element()
		{

		}
		Element::Element(EMapID eOneID, EMapID eTwoID, int iX, int iZ, int iY) : m_eOneID(eOneID), m_eTwoID(eTwoID), m_sPosition(Point3D(iX, iY, iZ))
		{

		}
		Element::~Element()
		{

		}
		BOOL Element::IsInto(Point3D sPosition)
		{
			int iDist, iX, iY, iZ;

			sPosition.GetPTDistanceXZY(&sPosition, iDist, iX, iY, iZ);

			return (iDist < DIST_TRANSLEVEL_CONNECT && iX < 64 * 256 && iZ < 64 * 256) ? TRUE : FALSE;
		}
	}
}