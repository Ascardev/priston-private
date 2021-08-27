#pragma once

enum EParticleModifierGroupType
{
	PARTICLEMODIFIERGROUPTYPE_Size = 0,
	PARTICLEMODIFIERGROUPTYPE_Color = 1,
};

namespace PARTICLE
{
	class ModifierGroup
	{
	public:
		ModifierGroup(EParticleModifierGroupType eType);
		ModifierGroup(ModifierGroup &c);

		virtual ~ModifierGroup();

		void Apply(Particle *pcParticle);
		void AddModifier(Modifier *pcModifier) { m_vModifiers.push_back(pcModifier); }

		EParticleModifierGroupType GetType() { return m_eType; }
	protected:
		EParticleModifierGroupType m_eType;
		std::vector<Modifier*> m_vModifiers;

		Modifier *m_pcLast1;
		Modifier *m_pcLast2;

		int m_iLastDiffP;
	};
}