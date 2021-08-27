#pragma once

namespace PARTICLE
{
	class System
	{
		friend class Factory;
		friend class Emitter;
	public:
		System();
		System(Particle *pcParticle);
		System(System & c);

		virtual ~System();

		void Birth();
		BOOL Update(double fTime);
		void Render(class smMATERIAL_GROUP *pcTextureManager);
		void Pause() { m_bPaused = TRUE; }
		void Continue() { m_bPaused = FALSE; }
		void Kill(BOOL bForce);
		std::string GetName() { return m_strName; }
		UINT GetOwnerID();
		void SetOwner(ENGINE::ObjectOwner *pNewOwner);
		void SetID(UINT uID) { m_uID = uID; }
		UINT  GetID() { return m_uID; }
		Emitter *GetParticleEmitter() { return m_pcParticleEmitter; }
		Particle *GetParticle() { return m_pcParticle; }
	private:
		void Add(Particle *pcParticle);
		UINT ParticlesAlive() { return m_vActiveParticles.size(); }
	private:
		std::string m_strName;
		Emitter *m_pcParticleEmitter;
		Object *m_pcParticleObject;
		Particle *m_pcParticle;
		std::vector<Particle*> m_vActiveParticles;
		ENGINE::ObjectOwner *m_pOwner;
		BOOL m_bKill;
		BOOL m_bPaused;
		UINT m_uID;
	};
}