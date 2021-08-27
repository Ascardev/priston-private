#pragma once

#include "ParticleBase.h"

namespace PARTICLE
{
	class Modifier
	{
	public:
		Modifier(double f);
		Modifier(Modifier &c);

		virtual ~Modifier();
		virtual Modifier *Clone() = 0;

		virtual void Apply(Particle *pcParticle) = 0;
		virtual void Apply(Particle *pcParticle, Modifier *pcOther, int iDiffP) = 0;

		double GetTime() { return m_fTime; }
	protected:
		double m_fTime;
	};

	class ModifierSize : public Modifier
	{
	public:
		ModifierSize(Particle::Size s, double f);
		ModifierSize(ModifierSize &c);

		virtual ~ModifierSize();

		ModifierSize *Clone();

		void Apply(Particle *pcParticle);
		void Apply(Particle *pcParticle, Modifier *pcOther, int iDiffP);
	protected:
		Particle::Size m_sSize;
	};

	class ModifierColor : public Modifier
	{
	public:
		ModifierColor(Particle::Color c, double f);
		ModifierColor(ModifierColor &c);

		virtual ~ModifierColor();

		ModifierColor *Clone();

		void Apply(Particle *pcParticle);
		void Apply(Particle *pcParticle, Modifier *pcOther, int iDiffP);
	protected:
		Particle::Color m_sColor;
	};
}
