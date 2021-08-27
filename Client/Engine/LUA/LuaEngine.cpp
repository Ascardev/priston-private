#include "StdAfx.h"
#include "LuaEngine.h"

namespace LUA
{
	Engine::Engine()
	{
		m_pcMutex = new CMutex("Lua Engine");

		m_pcLuaFactory = new Factory();

		m_pcTextureManager = new smMATERIAL_GROUP(1000);
	}
	Engine::~Engine()
	{
		//WRITEDBG( "~CParticleEngine()" );

		DELET(m_pcTextureManager);

		DELET(m_pcLuaFactory);

		DELET(m_pcMutex);
	}
	void Engine::Init()
	{
		INITP(m_pcLuaFactory, m_pcTextureManager);
	}
	void Engine::Shutdown()
	{
		for (vector<System*>::iterator it = m_vLuaSystems.begin(); it != m_vLuaSystems.end(); it++)
		{
			System * pcLuaSystem = *it;

			DELET(pcLuaSystem);
		}
		m_vLuaSystems.clear();

		SHUTDOWN(m_pcLuaFactory);
	}
	void Engine::Update(double fTime)
	{
		for (vector<System*>::iterator it = m_vLuaSystems.begin(); it != m_vLuaSystems.end(); )
		{
			System * pcLuaSystem = *it;

			if (pcLuaSystem->Update(fTime))
			{
				DELET(pcLuaSystem);

				it = m_vLuaSystems.erase(it);
			}
			else
				it++;
		}
	}
	void Engine::Render3D(Point3D sCameraPosition, Point3D sCameraAngle)
	{
		//Render States
		DWORD dw1 = 0, dw2 = 0;
		GRAPHICENGINE->GetDevice()->GetRenderState(D3DRS_DITHERENABLE, &dw1);
		GRAPHICENGINE->GetDevice()->GetRenderState(D3DRS_SPECULARENABLE, &dw2);

		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_DITHERENABLE, FALSE);
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_SPECULARENABLE, FALSE);
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

		cpRender->SetMaterialGroup(m_pcTextureManager);
		cpRender->SetCameraPosition(sCameraPosition, sCameraAngle);

		//Loop through each Particle System and render each Particle
		for (int i = 0, j = m_vLuaSystems.size(); i < j; i++)
			m_vLuaSystems[i]->Render(m_pcTextureManager);

		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_DITHERENABLE, dw1);
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_SPECULARENABLE, dw2);
	}
	void Engine::Render2D()
	{
		//Only for Particle Debug
		//pcParticleDebug->Render();
	}
	UINT Engine::Add(System * pcLuaSystem, double fOverTime)
	{
		m_pcMutex->Lock();

		pcLuaSystem->Birth();

		if (fOverTime > 0.0f)
		{
			if (pcLuaSystem->Update(fOverTime))
			{
				DELET(pcLuaSystem);

				m_pcMutex->UnLock();

				return -1;
			}
		}

		UINT iID = m_vLuaSystems.size();

		m_vLuaSystems.push_back(pcLuaSystem);

		m_pcMutex->UnLock();

		return iID;
	}
	void Engine::AddScript(Script * pcLuaScript, double fOverTime)
	{
		m_pcMutex->Lock();

		for (vector<System*>::iterator it = pcLuaScript->m_vLuaSystems.begin(); it != pcLuaScript->m_vLuaSystems.end(); it++)
		{
			System * pcLuaSystem = *it;

			UINT iID = Add(pcLuaSystem, fOverTime);
		}

		pcLuaScript->Clear();

		DELET(pcLuaScript);

		m_pcMutex->UnLock();
	}
	void Engine::Pause(UINT iID)
	{
		if ((iID >= 0) && (iID < m_vLuaSystems.size()))
		{
			System * pcLuaSystem = m_vLuaSystems[iID];

			pcLuaSystem->Pause();
		}
	}

	void Engine::Continue(UINT iID)
	{
		if ((iID >= 0) && (iID < m_vLuaSystems.size()))
		{
			System * pcLuaSystem = m_vLuaSystems[iID];

			pcLuaSystem->Continue();
		}
	}

	void Engine::Kill(UINT uLuaID)
	{
		for (vector<System*>::iterator it = m_vLuaSystems.begin(); it != m_vLuaSystems.end(); it++)
		{
			System * pcLuaSystem = *it;

			if (pcLuaSystem->GetID() == uLuaID)
			{
				//Let Particle System Die
				pcLuaSystem->Kill(TRUE);
			}
		}
	}

	void Engine::Kill(UINT uLuaID, UINT uOwnerID)
	{
		for (vector<System*>::iterator it = m_vLuaSystems.begin(); it != m_vLuaSystems.end(); it++)
		{
			System * pcLuaSystem = *it;

			if ((pcLuaSystem->GetID() == uLuaID) && (pcLuaSystem->GetOwnerID() == uOwnerID))
			{
				//Let Particle System Die
				pcLuaSystem->Kill(FALSE);
			}
		}
	}

	void Engine::KillAll()
	{
		for (vector<System*>::iterator it = m_vLuaSystems.begin(); it != m_vLuaSystems.end(); it++)
		{
			System * pcLuaSystem = *it;

			DELET(pcLuaSystem);
		}
		m_vLuaSystems.clear();
	}
}