#pragma once

namespace PARTICLE
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

		std::vector<System *> & GetParticleSystems() { return m_vParticleSystems; }

		void Add(System *pcReadyParticleSystem);
		void Clear();

		void SetOwner(ENGINE::ObjectOwner *pNewOwner);
		void SetID(UINT uID);
		void RemoveParticleSystem(std::string strParticleSystem);
	private:
		std::string m_strFilePath;

		std::string m_strScript;
		std::string m_strAuthor;

		System *m_pcParticleSystem;

		std::vector<System *> m_vParticleSystems;
	};
}
