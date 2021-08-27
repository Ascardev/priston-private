#pragma once

namespace PARTICLE
{
	class Object
	{
	public:
		Object();
		virtual ~Object();

		void AddObject(Particle *pcParticleEmitter);
	private:
		std::vector<Particle*> m_vParticles;
	};
}