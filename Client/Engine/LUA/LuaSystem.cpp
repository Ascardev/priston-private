#include "StdAfx.h"
#include "LuaSystem.h"

namespace LUA
{
	System::System()
	{
		m_strName = "";
		m_pcLuaEmitter = new Emitter(this);
		m_pcLua = NULL;

		m_pOwner = NULL;

		m_bKill = FALSE;

		m_bPaused = FALSE;

		m_uID = 0xFFFFFFFF;
	}
	System::System(Base *pcLua)
	{
		m_strName = "";

		m_pcLuaEmitter = new Emitter(this);
		m_pcLua = pcLua;

		m_pOwner = NULL;

		m_bKill = FALSE;

		m_bPaused = FALSE;

		m_uID = 0xFFFFFFFF;
	}
	System::System(System & c)
	{
		m_strName = c.m_strName;

		m_pcLuaEmitter = new Emitter(this, *c.m_pcLuaEmitter);
		m_pcLua = (c.m_pcLua ? c.m_pcLua->Clone() : NULL);

		m_pOwner = (c.m_pOwner ? c.m_pOwner->Clone() : NULL);

		m_bKill = c.m_bKill;

		m_bPaused = c.m_bPaused;

		m_uID = c.m_uID;
	}
	System::~System()
	{
		for (vector<Base*>::iterator it = m_vActiveLuas.begin(); it != m_vActiveLuas.end(); it++)
		{
			Base * pcActiveLua = *it;

			DELET(pcActiveLua);
		}
		m_vActiveLuas.clear();

		DELET(m_pcLua);
		DELET(m_pcLuaEmitter);
	}
	void System::Birth()
	{
		m_pcLuaEmitter->Birth();
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
		for (vector<Base*>::iterator it = m_vActiveLuas.begin(); it != m_vActiveLuas.end(); )
		{
			Base * pcActiveLua = *it;

			if (pcActiveLua->Update(fTime))
			{
				DELET(pcActiveLua);

				it = m_vActiveLuas.erase(it);
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
			bRet = m_pcLuaEmitter->Update(fTime);
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
		cpRender->InitStageMesh();

		//Loop through each Active Particle and Render it
		for (int i = 0, j = m_vActiveLuas.size(); i < j; i++)
		{
			Base * pcActiveLua = m_vActiveLuas[i];

			//Set the Source Blend Mode of the Texture
			smMATERIAL * pTextureWrapper = pcTextureManager->GetTexture(pcActiveLua->m_uTextureID);
			pTextureWrapper->InUse = TRUE;
			pTextureWrapper->TwoSide = TRUE;
			pTextureWrapper->BlendType = pcActiveLua->m_eSourceBlendMode;

			//RENDERER->SetTextureManager(pcTextureManager);
			cpRender->SetMaterialGroup(pcTextureManager);

			//Render the Particle
			pcActiveLua->Render();

			//Depracated for now pTextureWrapper->bInUse = FALSE;
		}

		//Prepare to finalize Rendering
		cpRender->RendFace(SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM, FALSE);
	}
	void System::Kill(BOOL bForce)
	{
		m_bKill = TRUE;

		if (bForce)
		{
			for (vector<Base*>::iterator it = m_vActiveLuas.begin(); it != m_vActiveLuas.end(); it++)
			{
				Base * pcActiveLua = *it;

				DELET(pcActiveLua);
			}
			m_vActiveLuas.clear();
		}
		else
		{
			for (vector<Base*>::iterator it = m_vActiveLuas.begin(); it != m_vActiveLuas.end(); it++)
			{
				Base * pcActiveLua = *it;

				pcActiveLua->m_bLoop = FALSE;
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

		m_pcLuaEmitter->SetOwner(pNewOwner);
		m_pcLua->SetOwner(pNewOwner);
	}

	void System::Add(Base * pcLua)
	{
		m_vActiveLuas.push_back(pcLua);
	}
}