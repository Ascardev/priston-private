#include "StdAfx.h"
#include "ParticleModifierGroup.h"

namespace PARTICLE
{
	ModifierGroup::ModifierGroup(EParticleModifierGroupType eType) : m_eType(eType)
	{
		m_pcLast1 = NULL;
		m_pcLast2 = NULL;

		m_iLastDiffP = -1;
	}
	ModifierGroup::ModifierGroup(ModifierGroup &c)
	{
		m_eType = c.m_eType;

		m_pcLast1 = NULL;
		m_pcLast2 = NULL;
		m_iLastDiffP = -1;

		for (vector<Modifier*>::iterator it = c.m_vModifiers.begin(); it != c.m_vModifiers.end(); it++)
		{
			Modifier * pcParticleModifier = *it;

			m_vModifiers.push_back(pcParticleModifier->Clone());
		}
	}
	ModifierGroup::~ModifierGroup()
	{
		for (vector<Modifier*>::iterator it = m_vModifiers.begin(); it != m_vModifiers.end(); it++)
		{
			Modifier * pcParticleModifier = *it;

			DELET(pcParticleModifier);
		}
		m_vModifiers.clear();
	}
	void ModifierGroup::Apply(Particle * pcParticle)
	{
		double fCurLifeTime = pcParticle->m_sCurLifeTime.t.value;

		Modifier * pcMod1 = m_pcLast1, *pcMod2 = m_pcLast2;

		if ((pcMod1 == NULL) || (pcMod2 == NULL) || !((fCurLifeTime >= pcMod1->GetTime()) && (fCurLifeTime < pcMod2->GetTime())))
		{
			for (vector<Modifier*>::iterator it = m_vModifiers.begin(); it != m_vModifiers.end(); it++)
			{
				Modifier * pcParticleModifier = *it;

				if (fCurLifeTime >= pcParticleModifier->GetTime())
				{
					pcMod1 = pcParticleModifier;
				}
				else
				{
					pcMod2 = pcParticleModifier;
					break;
				}
			}
		}

		if (pcMod1 && pcMod2)
		{
			//Between two Modifiers
			double fClc = fCurLifeTime - pcMod1->GetTime();
			double fMax = pcMod2->GetTime() - pcMod1->GetTime();
			int iDiffP = (int)((100 * fClc) / fMax);

			if (iDiffP != m_iLastDiffP)
			{
				pcMod1->Apply(pcParticle, pcMod2, iDiffP);

				m_iLastDiffP = iDiffP;
			}
		}
		else if (pcMod1)
		{
			//All Modifiers passed..
			if (m_pcLast1 != pcMod1)
			{
				//Apply Final Modifications
				pcMod1->Apply(pcParticle);
			}
		}

		m_pcLast1 = pcMod1;
		m_pcLast2 = pcMod2;
	}
}