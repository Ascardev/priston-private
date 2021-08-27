#pragma once

enum EParticleEmitterType
{
	PARTICLEEMITTERTYPE_Follow,
	PARTICLEEMITTERTYPE_Free,
};

namespace PARTICLE
{
	class Particle;

	class Emitter
	{
		friend class Factory;

	public:
		Emitter(System *pcParticleSystem);
		Emitter(System *pcParticleSystem, Emitter &c);
		virtual ~Emitter();

		void Birth();
		BOOL Update(double fTime);
		void SetOwner(ENGINE::ObjectOwner *pNewOwner) { m_pOwner = pNewOwner->Clone(); }
		void SetName(std::string strName) { m_strName = strName; }
		void SetActive(BOOL b) { m_bActive = b; }
	protected:
		void Emit(double fUpdateTime);
	protected:
		BOOL m_bActive;
		std::string m_strName;
		System *m_pcParticleSystem;

		EParticleEmitterType m_eType;

		Particle::Point m_sPosition;
		Particle::Point m_sVelocity;

		Particle::Rotation m_sRotation;
		Particle::Rotation m_sAngularVelocity;

		Particle::Time m_sCurDelay;
		Particle::Time m_sMaxDelay;

		Particle::Time m_sCurLifeTime;
		Particle::Time m_sMaxLifeTime;

		Particle::Int m_sParticles;
		Particle::Dbl m_sInterval;

		ENGINE::ObjectOwner *m_pOwner;

		double m_fLastEmit;
	};
}