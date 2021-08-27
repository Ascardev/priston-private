#pragma once

class smMATERIAL_GROUP;

namespace LUA
{
	class Script;

	class Factory : public CLua
	{
	public:
		Factory();
		virtual ~Factory();

		void Init(class smMATERIAL_GROUP *pcTextureManager);
		void Shutdown();

		Script *LoadScript(std::string strFilePath, int iScriptID = 0, BOOL bUseCache = TRUE);

		void ClearCache();
	protected:
		void AddScriptToCache(Script *pcLuaScriptToCache);
		Script *GetScriptFromCache(std::string strFilePath);

		static Factory *GetThis(LuaState *pLuaState);

		//Integer Handlers
		static int LuaInt(LuaState *pLuaState);
		static int LuaRandomInt(LuaState *pLuaState);

		//Double Handlers
		static int LuaDbl(LuaState *pLuaState);
		static int LuaRandomDbl(LuaState *pLuaState);

		//Particle Script Handlers
		static int LuaScript(LuaState *pLuaState);
		static int LuaAuthor(LuaState *pLuaState);

		//Particle System Handlers
		static int LuaSystem(LuaState *pLuaState);
		static int LuaSystemEnd(LuaState *pLuaState);

		//Particle Object Handlers
		static int LuaObject(LuaState *pLuaState);
		static int LuaObjectEnd(LuaState *pLuaState);

		static int LuaAddObject(LuaState *pLuaState);

		static int LuaName(LuaState *pLuaState);

		//Emitter Handlers
		static int LuaEmitType(LuaState *pLuaState);

		static int LuaEmitPosition(LuaState *pLuaState);
		static int LuaEmitVelocity(LuaState *pLuaState);

		static int LuaEmitRotation(LuaState *pLuaState);
		static int LuaEmitAngularVelocity(LuaState *pLuaState);

		static int LuaEmitDelay(LuaState *pLuaState);
		static int LuaEmitLifeTime(LuaState *pLuaState);

		static int LuaEmitLuas(LuaState *pLuaState);
		static int LuaEmitInterval(LuaState *pLuaState);

		//Particle Handlers
		static int LuaType(LuaState *pLuaState);
		static int LuaTexture(LuaState *pLuaState);
		static int LuaBlend(LuaState *pLuaState);

		static int LuaRGBA(LuaState *pLuaState);
		static int LuaSize(LuaState *pLuaState);
		static int LuaSizeWH(LuaState *pLuaState);

		static int LuaLoop(LuaState *pLuaState);
		static int LuaLifeTime(LuaState *pLuaState);

		//Particle Events Handlers
		static int LuaEventVelocity(LuaState *pLuaState);
		static int LuaEventSize(LuaState *pLuaState);

		//Particle Modifiers Handlers
		static int LuaModifierSize(LuaState *pLuaState);
		static int LuaModifierRGBA(LuaState *pLuaState);
	protected:
		smMATERIAL_GROUP *m_pcTextureManager;

		std::vector<Script *> m_vLuaScriptCache;

		Script *m_pcLuaScript;
	private:
		LPCMUTEX m_pcMutex;
	};
}