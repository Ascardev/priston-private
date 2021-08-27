#pragma once

namespace PARTICLE
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

		Factory *GetParticleFactory() { return m_pcParticleFactory; }

		UINT Add(System *pcParticleSystem, double fOverTime = 0.0f);
		void AddScript(Script *pcParticleScript, double fOverTime = 0.0f);

		void Pause(UINT uID);
		void Continue(UINT uID);

		void Kill(UINT uParticleID);
		void Kill(UINT uParticleID, UINT uOwnerID);
		void KillAll();

		UINT NumberOfActiveParticleSystems() { return m_vParticleSystems.size(); }

	protected:
		Factory *m_pcParticleFactory;
		smMATERIAL_GROUP *m_pcTextureManager;

		std::vector<System *> m_vParticleSystems;
	private:
		LPCMUTEX m_pcMutex;
	};
}
