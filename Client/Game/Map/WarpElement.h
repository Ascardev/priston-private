#pragma once

namespace MAP
{
	namespace WARP
	{
		class ElementOut
		{
			friend class Handle;

		public:
			ElementOut();
			ElementOut(EMapID eID, int iX, int iZ, int iY);
			virtual ~ElementOut();
		private:
			Point3D m_sPosition;
			EMapID m_eID = MAPID_Invalid;
		};
		class ElementIn
		{
			friend class Handle;

		public:
			ElementIn();
			ElementIn(EMapID eID, int iX, int iZ, int iY, int iWidth, int iHeight, int iType);
			virtual ~ElementIn();

			void AddElement(EMapID eID, int iX, int iZ, int iY);

			ElementOut *GetElement();

			BOOL IsInto(Point3D sPosition);
		private:
			Point3D m_sPosition;
			EMapID m_eID = MAPID_Invalid;
			int m_iWidth = 0;
			int m_iHeight = 0;
			int m_iType = 0;
			std::vector<ElementOut> m_vElement;
		};
	}
}