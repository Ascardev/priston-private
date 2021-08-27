#pragma once

namespace MAP
{
	namespace BORDER
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
		protected:
			void AddElement(EMapID eOneID, EMapID eTwoID, int iX, int iZ, int iY = 0);
			Element *GetElement(Point3D sPosition);
		private:
			std::vector<Element *> m_vpElement;
		};
	}
}