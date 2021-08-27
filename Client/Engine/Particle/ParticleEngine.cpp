#include "StdAfx.h"
#include "ParticleEngine.h"

namespace PARTICLE
{
	Engine::Engine()
	{
		m_pcMutex = new CMutex("Particle Engine");

		m_pcParticleFactory = new Factory();

		m_pcTextureManager = new smMATERIAL_GROUP(1000);
	}
	Engine::~Engine()
	{
		//WRITEDBG( "~CParticleEngine()" );

		DELET(m_pcTextureManager);

		DELET(m_pcParticleFactory);

		DELET(m_pcMutex);
	}
	void Engine::Init()
	{
		INITP(m_pcParticleFactory, m_pcTextureManager);
	}
	void Engine::Shutdown()
	{
		for (vector<System*>::iterator it = m_vParticleSystems.begin(); it != m_vParticleSystems.end(); it++)
		{
			System * pcParticleSystem = *it;

			DELET(pcParticleSystem);
		}
		m_vParticleSystems.clear();

		SHUTDOWN(m_pcParticleFactory);
	}
	void Engine::Update(double fTime)
	{
		for (vector<System*>::iterator it = m_vParticleSystems.begin(); it != m_vParticleSystems.end(); )
		{
			System * pcParticleSystem = *it;

			if (pcParticleSystem->Update(fTime))
			{
				DELET(pcParticleSystem);

				it = m_vParticleSystems.erase(it);
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

		//cpRender->SetMaterialGroup(m_pcTextureManager);
		//cpRender->SetCameraPosition(sCameraPosition, sCameraAngle);

		//Loop through each Particle System and render each Particle
		for (int i = 0, j = m_vParticleSystems.size(); i < j; i++)
			m_vParticleSystems[i]->Render(m_pcTextureManager);

		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_DITHERENABLE, dw1);
		GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_SPECULARENABLE, dw2);
	}
	void Engine::Render2D()
	{
		//Only for Particle Debug
		//pcParticleDebug->Render();
	}
	UINT Engine::Add(System * pcParticleSystem, double fOverTime)
	{
		m_pcMutex->Lock();

		pcParticleSystem->Birth();

		if (fOverTime > 0.0f)
		{
			if (pcParticleSystem->Update(fOverTime))
			{
				DELET(pcParticleSystem);

				m_pcMutex->UnLock();

				return -1;
			}
		}

		UINT iID = m_vParticleSystems.size();

		m_vParticleSystems.push_back(pcParticleSystem);

		m_pcMutex->UnLock();

		return iID;
	}
	void Engine::AddScript(Script * pcParticleScript, double fOverTime)
	{
		m_pcMutex->Lock();

		for (vector<System*>::iterator it = pcParticleScript->m_vParticleSystems.begin(); it != pcParticleScript->m_vParticleSystems.end(); it++)
		{
			System * pcParticleSystem = *it;

			UINT iID = Add(pcParticleSystem, fOverTime);
		}

		pcParticleScript->Clear();

		DELET(pcParticleScript);

		m_pcMutex->UnLock();
	}
	void Engine::Pause(UINT iID)
	{
		if ((iID >= 0) && (iID < m_vParticleSystems.size()))
		{
			System * pcParticleSystem = m_vParticleSystems[iID];

			pcParticleSystem->Pause();
		}
	}

	void Engine::Continue(UINT iID)
	{
		if ((iID >= 0) && (iID < m_vParticleSystems.size()))
		{
			System * pcParticleSystem = m_vParticleSystems[iID];

			pcParticleSystem->Continue();
		}
	}

	void Engine::Kill(UINT uParticleID)
	{
		for (vector<System*>::iterator it = m_vParticleSystems.begin(); it != m_vParticleSystems.end(); it++)
		{
			System * pcParticleSystem = *it;

			if (pcParticleSystem->GetID() == uParticleID)
			{
				//Let Particle System Die
				pcParticleSystem->Kill(TRUE);
			}
		}
	}

	void Engine::Kill(UINT uParticleID, UINT uOwnerID)
	{
		for (vector<System*>::iterator it = m_vParticleSystems.begin(); it != m_vParticleSystems.end(); it++)
		{
			System * pcParticleSystem = *it;

			if ((pcParticleSystem->GetID() == uParticleID) && (pcParticleSystem->GetOwnerID() == uOwnerID))
			{
				//Let Particle System Die
				pcParticleSystem->Kill(FALSE);
			}
		}
	}

	void Engine::KillAll()
	{
		for (vector<System*>::iterator it = m_vParticleSystems.begin(); it != m_vParticleSystems.end(); it++)
		{
			System * pcParticleSystem = *it;

			DELET(pcParticleSystem);
		}
		m_vParticleSystems.clear();
	}
}