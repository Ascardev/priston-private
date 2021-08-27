#include "StdAfx.h"
#include "ParticleModifier.h"

namespace PARTICLE
{
	Modifier::Modifier(double f) : m_fTime(f)
	{

	}
	Modifier::Modifier(Modifier &c) : m_fTime(c.m_fTime)
	{

	}
	Modifier::~Modifier()
	{

	}
	
	ModifierSize::ModifierSize(Particle::Size s, double f) : m_sSize(s), Modifier(f)
	{
		m_sSize.Birth();
	}
	ModifierSize::ModifierSize(ModifierSize &c) : Modifier(c)
	{
		m_sSize = c.m_sSize;

		m_sSize.Birth();
	}
	ModifierSize::~ModifierSize()
	{

	}
	ModifierSize *ModifierSize::Clone()
	{
		ModifierSize *pcClone = new ModifierSize(*this);

		return pcClone;
	}
	void ModifierSize::Apply(Particle *pcParticle)
	{
		pcParticle->SetSize(m_sSize);
	}
	void ModifierSize::Apply(Particle *pcParticle, Modifier *pcOther, int iDiffP)
	{
		ModifierSize *pcOtherSize = (ModifierSize *)pcOther;
		Particle::Size *psSize = &pcOtherSize->m_sSize;

		if (iDiffP <= 0)
		{
			pcParticle->SetSize(m_sSize);
			return;
		}
		if (iDiffP >= 100)
		{
			pcParticle->SetSize(*psSize);
			return;
		}

		int s;

		if (m_sSize.s.value != psSize->s.value)
			s = m_sSize.s.value + (((pcOtherSize->m_sSize.s.value - m_sSize.s.value) * iDiffP) / 100);
		else
			s = m_sSize.s.value;

		Particle::Size sNewSize;

		sNewSize.s = s;

		pcParticle->SetSize(sNewSize);
	}

	ModifierColor::ModifierColor(Particle::Color c, double f) : m_sColor(c), Modifier(f)
	{
		m_sColor.Birth();
	}
	ModifierColor::ModifierColor(ModifierColor &c) : Modifier(c)
	{
		m_sColor = c.m_sColor;

		m_sColor.Birth();
	}
	ModifierColor::~ModifierColor()
	{

	}
	ModifierColor *ModifierColor::Clone()
	{
		ModifierColor *pcClone = new ModifierColor(*this);

		return pcClone;
	}
	void ModifierColor::Apply(Particle *pcParticle)
	{
		pcParticle->SetColor(m_sColor);
	}
	void ModifierColor::Apply(Particle *pcParticle, Modifier *pcOther, int iDiffP)
	{
		ModifierColor * pcOtherColor = (ModifierColor*)pcOther;
		Particle::Color * psColor = &pcOtherColor->m_sColor;

		if (iDiffP <= 0)
		{
			pcParticle->SetColor(m_sColor);
			return;
		}

		if (iDiffP >= 100)
		{
			pcParticle->SetColor(*psColor);
			return;
		}

		int r, g, b, a;

		if (m_sColor.r.value != psColor->r.value)
			r = m_sColor.r.value + (((pcOtherColor->m_sColor.r.value - m_sColor.r.value) * iDiffP) / 100);
		else
			r = m_sColor.r.value;

		if (m_sColor.g.value != psColor->g.value)
			g = m_sColor.g.value + (((pcOtherColor->m_sColor.g.value - m_sColor.g.value) * iDiffP) / 100);
		else
			g = m_sColor.g.value;

		if (m_sColor.b.value != psColor->b.value)
			b = m_sColor.b.value + (((pcOtherColor->m_sColor.b.value - m_sColor.b.value) * iDiffP) / 100);
		else
			b = m_sColor.b.value;

		if (m_sColor.a.value != psColor->a.value)
			a = m_sColor.a.value + (((pcOtherColor->m_sColor.a.value - m_sColor.a.value) * iDiffP) / 100);
		else
			a = m_sColor.a.value;

		Particle::Color sNewColor;
		sNewColor.r = r;
		sNewColor.g = g;
		sNewColor.b = b;
		sNewColor.a = a;

		pcParticle->SetColor(sNewColor);
	}
}