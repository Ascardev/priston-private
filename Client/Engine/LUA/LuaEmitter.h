#pragma once

enum ELuaEmitterType
{
	LUAEMITTERTYPE_Follow,
	LUAEMITTERTYPE_Free,
};

namespace LUA
{
	class Base;

	class Emitter
	{
		friend class Factory;

	public:
		Emitter(System *pcLuaSystem);
		Emitter(System *pcLuaSystem, Emitter &c);
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
		System *m_pcLuaSystem;

		ELuaEmitterType m_eType;

		Base::Point m_sPosition;
		Base::Point m_sVelocity;

		Base::Rotation m_sRotation;
		Base::Rotation m_sAngularVelocity;

		Base::Time m_sCurDelay;
		Base::Time m_sMaxDelay;

		Base::Time m_sCurLifeTime;
		Base::Time m_sMaxLifeTime;

		Base::Int m_sLuas;
		Base::Dbl m_sInterval;

		ENGINE::ObjectOwner *m_pOwner;

		double m_fLastEmit;
	};
}