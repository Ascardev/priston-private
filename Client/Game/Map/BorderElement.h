#pragma once

namespace MAP
{
	namespace BORDER
	{
		class Element
		{
			friend class Handle;

		public:
			Element();
			Element(EMapID eOneID, EMapID eTwoID, int iX, int iZ, int iY);
			virtual ~Element();

			BOOL IsInto(Point3D sPosition);
		private:
			EMapID m_eOneID;
			EMapID m_eTwoID;
			Point3D m_sPosition;
		};
	}
}