#include "StdAfx.h"
#include "LuaModifierGroup.h"

namespace LUA
{
	ModifierGroup::ModifierGroup(ELuaModifierGroupType eType) : m_eType(eType)
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
			Modifier * pcLuaModifier = *it;

			m_vModifiers.push_back(pcLuaModifier->Clone());
		}
	}
	ModifierGroup::~ModifierGroup()
	{
		for (vector<Modifier*>::iterator it = m_vModifiers.begin(); it != m_vModifiers.end(); it++)
		{
			Modifier * pcLuaModifier = *it;

			DELET(pcLuaModifier);
		}
		m_vModifiers.clear();
	}
	void ModifierGroup::Apply(Base * pcLua)
	{
		double fCurLifeTime = pcLua->m_sCurLifeTime.t.value;

		Modifier * pcMod1 = m_pcLast1, *pcMod2 = m_pcLast2;

		if ((pcMod1 == NULL) || (pcMod2 == NULL) || !((fCurLifeTime >= pcMod1->GetTime()) && (fCurLifeTime < pcMod2->GetTime())))
		{
			for (vector<Modifier*>::iterator it = m_vModifiers.begin(); it != m_vModifiers.end(); it++)
			{
				Modifier * pcLuaModifier = *it;

				if (fCurLifeTime >= pcLuaModifier->GetTime())
				{
					pcMod1 = pcLuaModifier;
				}
				else
				{
					pcMod2 = pcLuaModifier;
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
				pcMod1->Apply(pcLua, pcMod2, iDiffP);

				m_iLastDiffP = iDiffP;
			}
		}
		else if (pcMod1)
		{
			//All Modifiers passed..
			if (m_pcLast1 != pcMod1)
			{
				//Apply Final Modifications
				pcMod1->Apply(pcLua);
			}
		}

		m_pcLast1 = pcMod1;
		m_pcLast2 = pcMod2;
	}
}