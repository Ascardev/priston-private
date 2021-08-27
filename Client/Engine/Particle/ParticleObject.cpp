#include "StdAfx.h"
#include "ParticleObject.h"

namespace PARTICLE
{
	Object::Object()
	{

	}
	Object::~Object()
	{

	}
	void Object::AddObject(Particle *pcParticleEmitter)
	{
		m_vParticles.push_back(pcParticleEmitter);
	}
}