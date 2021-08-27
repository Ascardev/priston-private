#pragma once

#include "LuaBase.h"

namespace LUA
{
	class Modifier
	{
	public:
		Modifier(double f);
		Modifier(Modifier &c);

		virtual ~Modifier();
		virtual Modifier *Clone() = 0;

		virtual void Apply(Base *pcLua) = 0;
		virtual void Apply(Base *pcLua, Modifier *pcOther, int iDiffP) = 0;

		double GetTime() { return m_fTime; }
	protected:
		double m_fTime;
	};

	class ModifierSize : public Modifier
	{
	public:
		ModifierSize(Base::Size s, double f);
		ModifierSize(ModifierSize &c);

		virtual ~ModifierSize();

		ModifierSize *Clone();

		void Apply(Base *pcLua);
		void Apply(Base *pcLua, Modifier *pcOther, int iDiffP);
	protected:
		Base::Size m_sSize;
	};

	class ModifierColor : public Modifier
	{
	public:
		ModifierColor(Base::Color c, double f);
		ModifierColor(ModifierColor &c);

		virtual ~ModifierColor();

		ModifierColor *Clone();

		void Apply(Base *pcLua);
		void Apply(Base *pcLua, Modifier *pcOther, int iDiffP);
	protected:
		Base::Color m_sColor;
	};
}
