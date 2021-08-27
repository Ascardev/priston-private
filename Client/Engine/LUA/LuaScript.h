#pragma once

namespace LUA
{
	class Script
	{
		friend class Engine;
		friend class Factory;
	public:
		Script(std::string strFilePath);
		Script(Script & c);
		virtual ~Script();

		std::string GetFilePath() { return m_strFilePath; }

		std::string GetScript() { return m_strScript; }
		std::string GetAuthor() { return m_strAuthor; }

		std::vector<System *> & GetLuaSystems() { return m_vLuaSystems; }

		void Add(System *pcReadyParticleSystem);
		void Clear();

		void SetOwner(ENGINE::ObjectOwner *pNewOwner);
		void SetID(UINT uID);
		void RemoveLuaSystem(std::string strLuaSystem);
	private:
		std::string m_strFilePath;

		std::string m_strScript;
		std::string m_strAuthor;

		System *m_pcLuaSystem;

		std::vector<System *> m_vLuaSystems;
	};
}
