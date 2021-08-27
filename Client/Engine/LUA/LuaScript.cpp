#include "StdAfx.h"
#include "LuaScript.h"

namespace LUA
{
	Script::Script(string strFilePath)
	{
		m_strFilePath = strFilePath;

		m_strScript = "";
		m_strAuthor = "";

		m_pcLuaSystem = NULL;
	}
	Script::Script(Script & c)
	{
		m_strFilePath = c.m_strFilePath;

		m_strScript = c.m_strScript;
		m_strAuthor = c.m_strAuthor;

		m_pcLuaSystem = NULL;

		for (vector<System*>::iterator it = c.m_vLuaSystems.begin(); it != c.m_vLuaSystems.end(); it++)
		{
			System * pcReadyLuaSystem = *it;

			m_vLuaSystems.push_back(new System(*pcReadyLuaSystem));
		}
	}
	Script::~Script()
	{
		//WRITEDBG( "~CParticleScript()" );

		for (vector<System*>::iterator it = m_vLuaSystems.begin(); it != m_vLuaSystems.end(); it++)
		{
			System * pcReadyLuaSystem = *it;

			DELET(pcReadyLuaSystem);
		}
		m_vLuaSystems.clear();

		DELET(m_pcLuaSystem);
	}
	void Script::Add(System * pcReadyLuaSystem)
	{
		m_vLuaSystems.push_back(pcReadyLuaSystem);
	}
	void Script::Clear()
	{
		m_vLuaSystems.clear();
	}
	void Script::SetOwner(ENGINE::ObjectOwner * pNewOwner)
	{
		for (vector<System*>::iterator it = m_vLuaSystems.begin(); it != m_vLuaSystems.end(); it++)
		{
			System * pcReadyLuaSystem = *it;

			pcReadyLuaSystem->SetOwner(pNewOwner);
		}

		DELET(pNewOwner);
	}
	void Script::SetID(UINT uID)
	{
		for (vector<System*>::iterator it = m_vLuaSystems.begin(); it != m_vLuaSystems.end(); it++)
		{
			System * pcReadyLuaSystem = *it;

			pcReadyLuaSystem->SetID(uID);
		}
	}
	void Script::RemoveLuaSystem(string strLuaSystem)
	{
		for (vector<System*>::iterator it = m_vLuaSystems.begin(); it != m_vLuaSystems.end(); )
		{
			System * pcReadyLuaSystem = *it;

			if (strLuaSystem.compare(pcReadyLuaSystem->GetName()) == 0)
			{
				DELET(pcReadyLuaSystem);

				it = m_vLuaSystems.erase(it);
			}
			else
				it++;
		}
	}
}