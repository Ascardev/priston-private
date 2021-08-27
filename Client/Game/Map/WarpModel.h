#pragma once

namespace MAP
{
	namespace WARP
	{
		struct Out
		{
			Point3D sPosition;
			EMapID eID = MAPID_Invalid;

			Out() {}
			Out(EMapID _eID, int iX, int iZ, int iY) :eID(_eID), sPosition(Point3D(iX, iY, iZ)) {}
		};
		struct In
		{
			In() {}
			In(EMapID _eID, int iX, int iZ, int iY, int _iWidth, int _iHeight, int _iType) : eID(_eID), sPosition(Point3D(iX, iY, iZ)), iWidth(_iWidth), iHeight(iHeight), iType(_iType) {}
			Point3D sPosition;
			EMapID eID = MAPID_Invalid;
			int iWidth = 0;
			int iHeight = 0;
			int iType = 0;
			std::vector<Out> vOut;

			void AddOut(EMapID _eID, int iX, int iZ, int iY) { vOut.push_back(Out(_eID, iX << 8, iZ << 8, iY << 8)); }
			Out *GetOut() { return vOut.size() ? &vOut[rand() % vOut.size()] : nullptr; }
			BOOL IsIn(Point3D sUsePosition)
			{
				int iDist, iX, iY, iZ;

				sPosition.GetPTDistanceXZY(&sUsePosition, iDist, iX, iY, iZ);

				return (iX < 1024 && iZ < 1024 && iDist < iWidth * iWidth && iY < iHeight) ? TRUE : FALSE;
			}
		};
		class Model
		{
		public:
			Model();
			virtual ~Model();

			void Init();
			void Shutdown();

			void Update();

			void SetWarpGate(EMapID eID) { m_eID = eID; }
		protected:
			In *GetIn(EMapID eID);
			In *AddIn(EMapID eID, int iX, int iZ, int iY, int iWidth, int iHeight, int iType);
		private:
			EMapID m_eID = MAPID_Invalid;
			std::vector<In *> m_vpIn;
		};
	}
}