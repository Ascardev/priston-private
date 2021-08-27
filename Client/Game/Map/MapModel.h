#pragma once

namespace MAP
{
	class Model : public Info
	{
	public:
		Model();
		Model(EMapID eID, const char *pszName);
		virtual ~Model();

		void Load();
		void Render(Point3D sPosition, Point3D sAngle);
		void Update();
	private:
		smSTAGE3D *m_pTerrain = nullptr;
		int m_iMode = 0;
	};
}
