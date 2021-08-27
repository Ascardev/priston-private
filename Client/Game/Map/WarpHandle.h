#pragma once

namespace MAP
{
	namespace WARP
	{
		class Handle : public CBaseHandle
		{
		public:
			Handle();
			Handle(EHandle eID);
			virtual ~Handle();

			void Init();
			void Shutdown();

			void Tick();

			void SetWarpGate(EMapID eID);
		protected:
			ElementIn *GetElement(EMapID eID, int iType);
			ElementIn *GetElement(Point3D sPosition);
			ElementIn *AddElement(EMapID eID, int iX, int iZ, int iY, int iWidth, int iHeight, int iType);
		private:
			EMapID m_eID = MAPID_Invalid;

			BOOL m_bHover = FALSE;

			std::vector<ElementIn *> m_vpElement;
		};
	}
}