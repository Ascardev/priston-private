#include "StdAfx.h"
#include "ParticleScript.h"

namespace PARTICLE
{
	Script::Script(string strFilePath)
	{
		m_strFilePath = strFilePath;

		m_strScript = "";
		m_strAuthor = "";

		m_pcParticleSystem = NULL;
	}
	Script::Script(Script & c)
	{
		m_strFilePath = c.m_strFilePath;

		m_strScript = c.m_strScript;
		m_strAuthor = c.m_strAuthor;

		m_pcParticleSystem = NULL;

		for (vector<System*>::iterator it = c.m_vParticleSystems.begin(); it != c.m_vParticleSystems.end(); it++)
		{
			System * pcReadyParticleSystem = *it;

			m_vParticleSystems.push_back(new System(*pcReadyParticleSystem));
		}
	}
	Script::~Script()
	{
		//WRITEDBG( "~CParticleScript()" );

		for (vector<System*>::iterator it = m_vParticleSystems.begin(); it != m_vParticleSystems.end(); it++)
		{
			System * pcReadyParticleSystem = *it;

			DELET(pcReadyParticleSystem);
		}
		m_vParticleSystems.clear();

		DELET(m_pcParticleSystem);
	}
	void Script::Add(System * pcReadyParticleSystem)
	{
		m_vParticleSystems.push_back(pcReadyParticleSystem);
	}
	void Script::Clear()
	{
		m_vParticleSystems.clear();
	}
	void Script::SetOwner(ENGINE::ObjectOwner * pNewOwner)
	{
		for (vector<System*>::iterator it = m_vParticleSystems.begin(); it != m_vParticleSystems.end(); it++)
		{
			System * pcReadyParticleSystem = *it;

			pcReadyParticleSystem->SetOwner(pNewOwner);
		}

		DELET(pNewOwner);
	}
	void Script::SetID(UINT uID)
	{
		for (vector<System*>::iterator it = m_vParticleSystems.begin(); it != m_vParticleSystems.end(); it++)
		{
			System * pcReadyParticleSystem = *it;

			pcReadyParticleSystem->SetID(uID);
		}
	}
	void Script::RemoveParticleSystem(string strParticleSystem)
	{
		for (vector<System*>::iterator it = m_vParticleSystems.begin(); it != m_vParticleSystems.end(); )
		{
			System * pcReadyParticleSystem = *it;

			if (strParticleSystem.compare(pcReadyParticleSystem->GetName()) == 0)
			{
				DELET(pcReadyParticleSystem);

				it = m_vParticleSystems.erase(it);
			}
			else
				it++;
		}
	}
}