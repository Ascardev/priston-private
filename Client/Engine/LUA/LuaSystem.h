#pragma once

namespace LUA
{
	class System
	{
		friend class Factory;
		friend class Emitter;
	public:
		System();
		System(Base *pcLua);
		System(System & c);

		virtual ~System();

		void Birth();
		BOOL Update(double fTime);
		void Render(class smMATERIAL_GROUP *pcTextureManager);
		void Pause() { m_bPaused = TRUE; }
		void Continue() { m_bPaused = FALSE; }
		void Kill(BOOL bForce);
		std::string GetName() { return m_strName; }
		UINT GetOwnerID();
		void SetOwner(ENGINE::ObjectOwner *pNewOwner);
		void SetID(UINT uID) { m_uID = uID; }
		UINT  GetID() { return m_uID; }
		Emitter *GetLuaEmitter() { return m_pcLuaEmitter; }
		Base *GetLua() { return m_pcLua; }
	private:
		void Add(Base *pcParticle);
		UINT ParticlesAlive() { return m_vActiveLuas.size(); }
	private:
		std::string m_strName;
		Emitter *m_pcLuaEmitter;
		Object *m_pcLuaObject;
		Base *m_pcLua;
		std::vector<Base*> m_vActiveLuas;
		ENGINE::ObjectOwner *m_pOwner;
		BOOL m_bKill;
		BOOL m_bPaused;
		UINT m_uID;
	};
}