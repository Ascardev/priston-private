#pragma once

namespace MAP
{
	typedef class Model *LPMODEL;

	class Model
	{
	public:
		Model();
		virtual ~Model();

		void Init();
		void Shutdown();

		void Update();

		void Load();
		void LoadMap(LPBASEMAP pcMap1, LPBASEMAP pcMap2 = nullptr);
		void Render(Point3D sPosition, Point3D sAngle);
		int GetHeight(Point3D sPosition);
		LPBASEMAP GetMap(EMapID eID) { return (eID != MAPID_Invalid) ? m_vpBaseMap[eID] : nullptr; }
		std::vector<LPBASEMAP> GetMap() { return m_vpBaseMap; }
		LPBASEMAP GetActiveMap(int i) { return (i == 1) ? m_pcMap[1] : m_pcMap[0]; }
		Point2D TeleportToCastle();
	protected:
		LPBASEMAP AddMap(LPBASEMAP pcMap) { m_vpBaseMap.push_back(pcMap); return pcMap; }
	private:
		std::vector<LPBASEMAP> m_vpBaseMap;
		LPBASEMAP m_pcMap[2] = { 0 };
	};
}