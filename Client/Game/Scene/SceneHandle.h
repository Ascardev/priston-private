#pragma once

class smSTAGE3D;

namespace SCENE
{
	class Handle
	{
	public:
		Handle();
		virtual ~Handle();

		void Init();
		void Shutdown();

		void Render(Point3D sCameraPosition, Point3D sCameraAngle);
		void Update();

		void Load(std::string strFileName);
	private:
		smSTAGE3D *m_pcTerrain = NULL;
	};
}
