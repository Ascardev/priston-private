#pragma once

enum ELuaModifierGroupType
{
	LUAMODIFIERGROUPTYPE_Size = 0,
	LUAMODIFIERGROUPTYPE_Color = 1,
};

namespace LUA
{
	class ModifierGroup
	{
	public:
		ModifierGroup(ELuaModifierGroupType eType);
		ModifierGroup(ModifierGroup &c);

		virtual ~ModifierGroup();

		void Apply(Base *pcLua);
		void AddModifier(Modifier *pcModifier) { m_vModifiers.push_back(pcModifier); }

		ELuaModifierGroupType GetType() { return m_eType; }
	protected:
		ELuaModifierGroupType m_eType;
		std::vector<Modifier*> m_vModifiers;

		Modifier *m_pcLast1;
		Modifier *m_pcLast2;

		int m_iLastDiffP;
	};
}