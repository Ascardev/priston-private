#include "StdAfx.h"
#include "ParticleSystem.h"

namespace PARTICLE
{
	System::System()
	{
		m_strName = "";
		m_pcParticleEmitter = new Emitter(this);
		m_pcParticle = NULL;

		m_pOwner = NULL;

		m_bKill = FALSE;

		m_bPaused = FALSE;

		m_uID = 0xFFFFFFFF;
	}
	System::System(Particle *pcParticle)
	{
		m_strName = "";

		m_pcParticleEmitter = new Emitter(this);
		m_pcParticle = pcParticle;

		m_pOwner = NULL;

		m_bKill = FALSE;

		m_bPaused = FALSE;

		m_uID = 0xFFFFFFFF;
	}
	System::System(System & c)
	{
		m_strName = c.m_strName;

		m_pcParticleEmitter = new Emitter(this, *c.m_pcParticleEmitter);
		m_pcParticle = (c.m_pcParticle ? c.m_pcParticle->Clone() : NULL);

		m_pOwner = (c.m_pOwner ? c.m_pOwner->Clone() : NULL);

		m_bKill = c.m_bKill;

		m_bPaused = c.m_bPaused;

		m_uID = c.m_uID;
	}
	System::~System()
	{
		for (vector<Particle*>::iterator it = m_vActiveParticles.begin(); it != m_vActiveParticles.end(); it++)
		{
			Particle * pcActiveParticle = *it;

			DELET(pcActiveParticle);
		}
		m_vActiveParticles.clear();

		DELET(m_pcParticle);
		DELET(m_pcParticleEmitter);
	}
	void System::Birth()
	{
		m_pcParticleEmitter->Birth();
	}
	BOOL System::Update(double fTime)
	{
		if (m_bPaused)
			return FALSE;

		if (m_pOwner)
		{
			if (m_pOwner->Lost(TICKCOUNT))
			{
				//Owner is Lost, force System end
				Kill(TRUE);
			}
			else
			{
				//Check if an ending Condition has met
				//TODO
			}
		}

		//Update Alive Particles
		for (vector<Particle*>::iterator it = m_vActiveParticles.begin(); it != m_vActiveParticles.end(); )
		{
			Particle * pcActiveParticle = *it;

			if (pcActiveParticle->Update(fTime))
			{
				DELET(pcActiveParticle);

				it = m_vActiveParticles.erase(it);
			}
			else
				it++;
		}

		//Emit Vitality
		BOOL bRet = m_bKill;

		//System Ending?
		if (bRet == FALSE)
		{
			//Emit New Particles
			bRet = m_pcParticleEmitter->Update(fTime);
		}

		//Is the Emitter done or is System ending?
		if (bRet)
		{
			if (ParticlesAlive() > 0)
			{
				//Let's not delete this Particle System yet if there's active particles
				return FALSE;
			}
		}

		return bRet;
	}
	void System::Render(smMATERIAL_GROUP *pcTextureManager)
	{
		//Prepare for Rendering
		//cpRender->InitStageMesh();

		//Loop through each Active Particle and Render it
		for (int i = 0, j = m_vActiveParticles.size(); i < j; i++)
		{
			Particle * pcActiveParticle = m_vActiveParticles[i];

			//Set the Source Blend Mode of the Texture
			//smMATERIAL * pTextureWrapper = pcTextureManager->GetTexture(pcActiveParticle->m_uTextureID);
			//pTextureWrapper->InUse = TRUE;
			//pTextureWrapper->TwoSide = TRUE;
			//pTextureWrapper->BlendType = pcActiveParticle->m_eSourceBlendMode;

			//RENDERER->SetTextureManager(pcTextureManager);
			//cpRender->SetMaterialGroup(pcTextureManager);

			//Render the Particle
			pcActiveParticle->Render();

			//Depracated for now pTextureWrapper->bInUse = FALSE;
		}

		//Prepare to finalize Rendering
		//cpRender->RendFace(SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM, FALSE);
	}
	void System::Kill(BOOL bForce)
	{
		m_bKill = TRUE;

		if (bForce)
		{
			for (vector<Particle*>::iterator it = m_vActiveParticles.begin(); it != m_vActiveParticles.end(); it++)
			{
				Particle * pcActiveParticle = *it;

				DELET(pcActiveParticle);
			}
			m_vActiveParticles.clear();
		}
		else
		{
			for (vector<Particle*>::iterator it = m_vActiveParticles.begin(); it != m_vActiveParticles.end(); it++)
			{
				Particle * pcActiveParticle = *it;

				pcActiveParticle->m_bLoop = FALSE;
			}
		}
	}
	UINT System::GetOwnerID()
	{
		if (m_pOwner)
		{
			if (m_pOwner->GetType() == ENGINE::OBJECTOWNERTYPE_Unit)
			{
				//Return Unit ID
				return ((ENGINE::ObjectOwnerUnit*)m_pOwner)->GetUnitID();
			}
		}

		return 0xFFFFFFFF;
	}

	void System::SetOwner(ENGINE::ObjectOwner * pNewOwner)
	{
		m_pOwner = pNewOwner->Clone();

		m_pcParticleEmitter->SetOwner(pNewOwner);
		m_pcParticle->SetOwner(pNewOwner);
	}

	void System::Add(Particle * pcParticle)
	{
		m_vActiveParticles.push_back(pcParticle);
	}
}