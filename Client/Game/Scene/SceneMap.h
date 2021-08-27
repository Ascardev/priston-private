#pragma once

namespace SCENE
{
	class Map
	{
	public:
		Map();
		virtual ~Map();

		void Init();
		void Shutdown();
	protected:
		void Load();
		MapInfo *AddMap(MapInfo *pcMap) { m_vpMap.push_back(pcMap); return pcMap; }
	private:
		std::vector<MapInfo *> m_vpMap;
	};
}
