#pragma once

namespace LUA
{
	class Engine
	{
	public:
		Engine();
		virtual ~Engine();

		void Init();
		void Shutdown();
		void Update(double fTime);
		void Render3D(Point3D sCameraPostion, Point3D sCameraAngle);
		void Render2D();

		Factory *GetLuaFactory() { return m_pcLuaFactory; }

		UINT Add(System *pcLuaSystem, double fOverTime = 0.0f);
		void AddScript(Script *pcLuaScript, double fOverTime = 0.0f);

		void Pause(UINT uID);
		void Continue(UINT uID);

		void Kill(UINT uLuaID);
		void Kill(UINT uLuaID, UINT uOwnerID);
		void KillAll();

		UINT NumberOfActiveLuaSystems() { return m_vLuaSystems.size(); }

	protected:
		Factory *m_pcLuaFactory;
		smMATERIAL_GROUP *m_pcTextureManager;

		std::vector<System *> m_vLuaSystems;
	private:
		LPCMUTEX m_pcMutex;
	};
}
