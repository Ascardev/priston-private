#include "StdAfx.h"

namespace PARTICLE
{
	Factory::Factory() : CLua()
	{
		m_pcMutex = new CMutex("Particle Factory");
		m_pcTextureManager = NULL;
		m_pcParticleScript = NULL;
	}
	Factory::~Factory()
	{
		//WRITEDBG( "~CParticleFactory()" );

		for (vector<Script*>::iterator it = m_vParticleScriptCache.begin(); it != m_vParticleScriptCache.end(); it++)
		{
			Script * pcCachedParticleScript = *it;

			DELET(pcCachedParticleScript);
		}
		m_vParticleScriptCache.clear();

		m_pcParticleScript = NULL;

		m_pcTextureManager = NULL;

		DELET(m_pcMutex);
	}
	void Factory::Init(class smMATERIAL_GROUP *pcTextureManager)
	{
		m_pcTextureManager = pcTextureManager;

		//Integer Handlers
		Register("Int", LuaInt);
		Register("RandomInt", LuaRandomInt);

		//Double Handlers
		Register("Dbl", LuaDbl);
		Register("RandomDbl", LuaRandomDbl);

		//Particle Script Handlers
		Register("Script", LuaScript);
		Register("Author", LuaAuthor);

		//Particle System Handlers
		Register("ParticleObject", LuaParticleObject);
		Register("ParticleObjectEnd", LuaParticleObjectEnd);

		Register("ParticleSystem", LuaParticleSystem);
		Register("ParticleSystemEnd", LuaParticleSystemEnd);

		Register("Name", LuaName);

		//Emitter Handlers
		Register("EmitType", LuaEmitType);

		Register("Position", LuaEmitPosition);
		Register("Velocity", LuaEmitVelocity);

		Register("EmitRotation", LuaEmitRotation);
		Register("EmitAngularVelocity", LuaEmitAngularVelocity);

		Register("EmitDelay", LuaEmitDelay);
		Register("EmitLifeTime", LuaEmitLifeTime);

		Register("EmitParticles", LuaEmitParticles);
		Register("EmitInterval", LuaEmitInterval);

		//Emitter Events Handlers

		//Particle Handlers
		Register("Type", LuaType);

		Register("Texture", LuaTexture);
		Register("Blend", LuaBlend);

		Register("RGBA", LuaRGBA);
		Register("Size", LuaSize);
		Register("SizeWH", LuaSizeWH);

		Register("Loop", LuaLoop);
		Register("LifeTime", LuaLifeTime);

		//Particle Events Handlers
		Register("EventVelocity", LuaEventVelocity);
		Register("EventSize", LuaEventSize);

		//Particle Modifiers Handlers
		Register("ModifierSize", LuaModifierSize);
		Register("ModifierRGBA", LuaModifierRGBA);
	}
	void Factory::Shutdown()
	{

	}
	Script *Factory::LoadScript(std::string strFilePath, int iScriptID, BOOL bUseCache)
	{
		m_pcMutex->Lock();

		Script * pcRet = NULL;

		m_pcParticleScript = bUseCache ? GetScriptFromCache(strFilePath) : NULL;

		if (m_pcParticleScript == NULL)
		{
			m_pcParticleScript = new Script(strFilePath);

			DoFile(strFilePath);

			AddScriptToCache(m_pcParticleScript);
		}

		pcRet = new Script(*m_pcParticleScript);

		m_pcMutex->UnLock();

		return pcRet;
	}
	void Factory::ClearCache()
	{
		for (vector<Script*>::iterator it = m_vParticleScriptCache.begin(); it != m_vParticleScriptCache.end(); it++)
		{
			Script * pcCachedParticleScript = *it;

			DELET(pcCachedParticleScript);
		}
		m_vParticleScriptCache.clear();
	}
	void Factory::AddScriptToCache(Script * pcParticleScriptToCache)
	{
		m_vParticleScriptCache.push_back(pcParticleScriptToCache);
	}
	Script * Factory::GetScriptFromCache(string strFilePath)
	{
		for (vector<Script*>::iterator it = m_vParticleScriptCache.begin(); it != m_vParticleScriptCache.end(); it++)
		{
			Script * pcCachedParticleScript = *it;

			if (pcCachedParticleScript->GetFilePath().compare(strFilePath) == 0)
				return pcCachedParticleScript;
		}

		return NULL;
	}
	Factory * Factory::GetThis(LuaState * pLuaState)
	{
		Factory * pThis = (Factory*)pLuaState->lua;

		return pThis;
	}
	int Factory::LuaInt(LuaState * pLuaState)
	{
		int iInt = ReadParamInteger(pLuaState, 1);

		Particle::Int * pcParticleInt = new Particle::Int(iInt);

		lua_pushinteger(pLuaState->get_ptr(), (int)pcParticleInt);

		return 1;
	}
	int Factory::LuaRandomInt(LuaState * pLuaState)
	{
		int iIntL = ReadParamInteger(pLuaState, 1);
		int iIntH = ReadParamInteger(pLuaState, 2);

		Particle::Int * pcParticleInt = new Particle::Int(iIntL, iIntH);

		lua_pushinteger(pLuaState->get_ptr(), (int)pcParticleInt);

		return 1;
	}
	int Factory::LuaDbl(LuaState * pLuaState)
	{
		double dDbl = ReadParamDouble(pLuaState, 1);

		Particle::Dbl * pcParticleDbl = new Particle::Dbl(dDbl);

		lua_pushinteger(pLuaState->get_ptr(), (int)pcParticleDbl);

		return 1;
	}
	int Factory::LuaRandomDbl(LuaState * pLuaState)
	{
		double dDblL = ReadParamDouble(pLuaState, 1);
		double dDblH = ReadParamDouble(pLuaState, 2);

		Particle::Dbl * pcParticleDbl = new Particle::Dbl(dDblL, dDblH);

		lua_pushinteger(pLuaState->get_ptr(), (int)pcParticleDbl);

		return 1;
	}
	int Factory::LuaScript(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcParticleScript = pThis->m_pcParticleScript;

		if (pcParticleScript)
		{
			std::string strScript = ReadParamString(pLuaState, 1);

			pcParticleScript->m_strScript = strScript;
		}

		return 0;
	}
	int Factory::LuaAuthor(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcParticleScript = pThis->m_pcParticleScript;

		if (pcParticleScript)
		{
			std::string strAuthor = ReadParamString(pLuaState, 1);

			pcParticleScript->m_strAuthor = strAuthor;
		}

		return 0;
	}
	int Factory::LuaParticleSystem(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcParticleScript = pThis->m_pcParticleScript;

		if (pcParticleScript)
		{
			std::string strParticleType = ReadParamString(pLuaState, 1);

			System * pcParticleSystem = new System();
			pcParticleSystem->m_pcParticle = new Particle();

			if (strParticleType.compare("Billboard") == 0)
			{
				//A Simple Billboard
				pcParticleSystem->m_pcParticle->m_eVisualType = PARTICLEVISUALTYPE_Billboard;
			}
			else if (strParticleType.compare("BillboardRotation") == 0)
			{
				//A Simple Billboard Rotation
				pcParticleSystem->m_pcParticle->m_eVisualType = PARTICLEVISUALTYPE_BillboardRotation;
			}
			else if (strParticleType.compare("BillboardHorizontal") == 0)
			{
				//A Horizontal Billboard
				pcParticleSystem->m_pcParticle->m_eVisualType = PARTICLEVISUALTYPE_BillboardHorizontal;
			}
			else if (strParticleType.compare("BillboardHorizontalRotation") == 0)
			{
				//A Horizontal Billboard with Rotation Attributes
				pcParticleSystem->m_pcParticle->m_eVisualType = PARTICLEVISUALTYPE_BillboardHorizontalRotation;
			}
			else if (strParticleType.compare("BillboardVertical") == 0)
			{
				//A Horizontal Billboard with Rotation Attributes
				pcParticleSystem->m_pcParticle->m_eVisualType = PARTICLEVISUALTYPE_BillboardVertical;
			}
			else if (strParticleType.compare("BillboardVerticalRotation") == 0)
			{
				//A Horizontal Billboard with Rotation Attributes
				pcParticleSystem->m_pcParticle->m_eVisualType = PARTICLEVISUALTYPE_BillboardVerticalRotation;
			}
			else
				ERRORBOX("ParticleSystem: Parameter 1 is not a valid Particle Type");

			pcParticleScript->m_pcParticleSystem = pcParticleSystem;
		}

		return 0;
	}
	int Factory::LuaParticleSystemEnd(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcParticleScript = pThis->m_pcParticleScript;

		if (pcParticleScript)
		{
			pcParticleScript->Add(pcParticleScript->m_pcParticleSystem);

			pcParticleScript->m_pcParticleSystem = NULL;
		}

		return 0;
	}
	int Factory::LuaParticleObject(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcParticleScript = pThis->m_pcParticleScript;
		System * pcParticleSystem = pcParticleScript->m_pcParticleSystem;
		Emitter * pcParticleEmitter = pcParticleSystem->m_pcParticleEmitter;

		if (pcParticleSystem && pcParticleEmitter)
		{
			if (pcParticleSystem->m_pcParticle)
				DELET(pcParticleSystem->m_pcParticle);

			pcParticleSystem->m_pcParticle = new Particle();

			pcParticleSystem->m_pcParticle->SetName(ReadParamString(pLuaState, 1));
		}

		return 0;
	}
	int Factory::LuaParticleObjectEnd(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcParticleScript = pThis->m_pcParticleScript;
		System * pcParticleSystem = pcParticleScript->m_pcParticleSystem;
		Emitter * pcParticleEmitter = pcParticleSystem->m_pcParticleEmitter;

		if (pcParticleSystem && pcParticleEmitter)
		{
			if (pcParticleSystem->m_pcParticle)
			{
				pcParticleSystem->Add(pcParticleSystem->m_pcParticle);

				DELET(pcParticleSystem->m_pcParticle);
			}

			pcParticleSystem->m_pcParticle = NULL;
		}

		return 0;
	}
	int Factory::LuaAddObject(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcParticleScript = pThis->m_pcParticleScript;
		System * pcParticleSystem = pcParticleScript->m_pcParticleSystem;
		Emitter * pcParticleEmitter = pcParticleSystem->m_pcParticleEmitter;

		if (pcParticleSystem && pcParticleEmitter)
		{
			std::string strName = ReadParamString(pLuaState, 1);
			std::string strNameType = ReadParamString(pLuaState, 2);

			for (std::vector<Particle*>::iterator it = pcParticleSystem->m_vActiveParticles.begin(); it != pcParticleSystem->m_vActiveParticles.end(); it++)
			{
				Particle * pcParticle = (*it);

				if (!pcParticle->IsActive())
				{
					if (pcParticle->GetName().compare(strName) == 0)
					{
						pcParticle->SetNameType(strNameType);

						pcParticle->SetActive(TRUE);
						break;
					}
				}
			}
		}

		return 0;
	}
	int Factory::LuaName(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcParticleScript = pThis->m_pcParticleScript;
		System * pcParticleSystem = pcParticleScript->m_pcParticleSystem;

		if (pcParticleSystem)
		{
			std::string strName = ReadParamString(pLuaState, 1);

			pcParticleSystem->m_strName = strName;
		}

		return 0;
	}
	int Factory::LuaEmitType(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcParticleScript = pThis->m_pcParticleScript;
		System * pcParticleSystem = pcParticleScript->m_pcParticleSystem;
		Emitter * pcParticleEmitter = pcParticleSystem->m_pcParticleEmitter;
		Particle * pcParticle = pcParticleSystem->m_pcParticle;

		if (pcParticleSystem && pcParticleEmitter && pcParticle)
		{
			std::string strEmitterType = ReadParamString(pLuaState, 1);

			if (strEmitterType.compare("Follow") == 0)
				pcParticleEmitter->m_eType = PARTICLEEMITTERTYPE_Follow;
			else if (strEmitterType.compare("Free") == 0)
				pcParticleEmitter->m_eType = PARTICLEEMITTERTYPE_Free;
			else
				ERRORBOX("EmitType: Parameter 1 is not a valid Emitter Type");
		}

		return 0;
	}
	int Factory::LuaEmitPosition(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcParticleScript = pThis->m_pcParticleScript;
		System * pcParticleSystem = pcParticleScript->m_pcParticleSystem;
		Emitter * pcParticleEmitter = pcParticleSystem->m_pcParticleEmitter;
		Particle * pcParticle = pcParticleSystem->m_pcParticle;

		if (pcParticleSystem && pcParticleEmitter && pcParticle)
		{
			Particle::Int * x = (Particle::Int*)ReadParamPointer(pLuaState, 1);
			Particle::Int * y = (Particle::Int*)ReadParamPointer(pLuaState, 2);
			Particle::Int * z = (Particle::Int*)ReadParamPointer(pLuaState, 3);

			pcParticleEmitter->m_sPosition.x = Particle::Int(((*x) << 8));
			pcParticleEmitter->m_sPosition.y = Particle::Int(((*y) << 8));
			pcParticleEmitter->m_sPosition.z = Particle::Int(((*z) << 8));

			DELET(x);
			DELET(y);
			DELET(z);
		}

		return 0;
	}
	int Factory::LuaEmitVelocity(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcParticleScript = pThis->m_pcParticleScript;
		System * pcParticleSystem = pcParticleScript->m_pcParticleSystem;
		Emitter * pcParticleEmitter = pcParticleSystem->m_pcParticleEmitter;
		Particle * pcParticle = pcParticleSystem->m_pcParticle;

		if (pcParticleSystem && pcParticleEmitter && pcParticle)
		{
			Particle::Int * x = (Particle::Int*)ReadParamPointer(pLuaState, 1);
			Particle::Int * y = (Particle::Int*)ReadParamPointer(pLuaState, 2);
			Particle::Int * z = (Particle::Int*)ReadParamPointer(pLuaState, 3);

			pcParticleEmitter->m_sVelocity.x = Particle::Int(((*x) << 8));
			pcParticleEmitter->m_sVelocity.y = Particle::Int(((*y) << 8));
			pcParticleEmitter->m_sVelocity.z = Particle::Int(((*z) << 8));

			DELET(x);
			DELET(y);
			DELET(z);
		}

		return 0;
	}
	int Factory::LuaEmitRotation(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcParticleScript = pThis->m_pcParticleScript;
		System * pcParticleSystem = pcParticleScript->m_pcParticleSystem;
		Emitter * pcParticleEmitter = pcParticleSystem->m_pcParticleEmitter;
		Particle * pcParticle = pcParticleSystem->m_pcParticle;

		if (pcParticleSystem && pcParticleEmitter && pcParticle)
		{
			Particle::Dbl * p = (Particle::Dbl*)ReadParamPointer(pLuaState, 1);
			Particle::Dbl * y = (Particle::Dbl*)ReadParamPointer(pLuaState, 2);
			Particle::Dbl * r = (Particle::Dbl*)ReadParamPointer(pLuaState, 3);

			pcParticleEmitter->m_sRotation.p = *p;
			pcParticleEmitter->m_sRotation.y = *y;
			pcParticleEmitter->m_sRotation.r = *r;

			DELET(r);
			DELET(y);
			DELET(p);
		}

		return 0;
	}
	int Factory::LuaEmitAngularVelocity(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcParticleScript = pThis->m_pcParticleScript;
		System * pcParticleSystem = pcParticleScript->m_pcParticleSystem;
		Emitter * pcParticleEmitter = pcParticleSystem->m_pcParticleEmitter;
		Particle * pcParticle = pcParticleSystem->m_pcParticle;

		if (pcParticleSystem && pcParticleEmitter && pcParticle)
		{
			Particle::Dbl * p = (Particle::Dbl*)ReadParamPointer(pLuaState, 1);
			Particle::Dbl * y = (Particle::Dbl*)ReadParamPointer(pLuaState, 2);
			Particle::Dbl * r = (Particle::Dbl*)ReadParamPointer(pLuaState, 3);

			pcParticleEmitter->m_sAngularVelocity.p = *p;
			pcParticleEmitter->m_sAngularVelocity.y = *y;
			pcParticleEmitter->m_sAngularVelocity.r = *r;

			DELET(r);
			DELET(y);
			DELET(p);
		}

		return 0;
	}
	int Factory::LuaEmitDelay(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcParticleScript = pThis->m_pcParticleScript;
		System * pcParticleSystem = pcParticleScript->m_pcParticleSystem;
		Emitter * pcParticleEmitter = pcParticleSystem->m_pcParticleEmitter;
		Particle * pcParticle = pcParticleSystem->m_pcParticle;

		if (pcParticleSystem && pcParticleEmitter && pcParticle)
		{
			Particle::Dbl * d = (Particle::Dbl*)ReadParamPointer(pLuaState, 1);

			pcParticleEmitter->m_sMaxDelay.t = Particle::Dbl(((*d) * 1000.0f));

			DELET(d);
		}

		return 0;
	}
	int Factory::LuaEmitLifeTime(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcParticleScript = pThis->m_pcParticleScript;
		System * pcParticleSystem = pcParticleScript->m_pcParticleSystem;
		Emitter * pcParticleEmitter = pcParticleSystem->m_pcParticleEmitter;
		Particle * pcParticle = pcParticleSystem->m_pcParticle;

		if (pcParticleSystem && pcParticleEmitter && pcParticle)
		{
			Particle::Dbl * d = (Particle::Dbl*)ReadParamPointer(pLuaState, 1);

			pcParticleEmitter->m_sMaxLifeTime.t = Particle::Dbl(((*d) * 1000.0f));

			DELET(d);
		}

		return 0;
	}
	int Factory::LuaEmitParticles(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcParticleScript = pThis->m_pcParticleScript;
		System * pcParticleSystem = pcParticleScript->m_pcParticleSystem;
		Emitter * pcParticleEmitter = pcParticleSystem->m_pcParticleEmitter;
		Particle * pcParticle = pcParticleSystem->m_pcParticle;

		if (pcParticleSystem && pcParticleEmitter && pcParticle)
		{
			Particle::Int * p = (Particle::Int*)ReadParamPointer(pLuaState, 1);

			pcParticleEmitter->m_sParticles = Particle::Int(*p);

			DELET(p);
		}

		return 0;
	}
	int Factory::LuaEmitInterval(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcParticleScript = pThis->m_pcParticleScript;
		System * pcParticleSystem = pcParticleScript->m_pcParticleSystem;
		Emitter * pcParticleEmitter = pcParticleSystem->m_pcParticleEmitter;
		Particle * pcParticle = pcParticleSystem->m_pcParticle;

		if (pcParticleSystem && pcParticleEmitter && pcParticle)
		{
			Particle::Dbl * d = (Particle::Dbl*)ReadParamPointer(pLuaState, 1);

			pcParticleEmitter->m_sInterval = Particle::Dbl(((*d) * 1000.0f));

			DELET(d);
		}

		return 0;
	}
	int Factory::LuaType(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcParticleScript = pThis->m_pcParticleScript;
		System * pcParticleSystem = pcParticleScript->m_pcParticleSystem;
		Emitter * pcParticleEmitter = pcParticleSystem->m_pcParticleEmitter;
		Particle * pcParticle = pcParticleSystem->m_pcParticle;

		if (pcParticleSystem && pcParticleEmitter && pcParticle)
		{
			std::string strEmitterType = ReadParamString(pLuaState, 1);

			if (strEmitterType.compare("Follow") == 0)
				pcParticle->m_eType = PARTICLETYPE_Follow;
			else if (strEmitterType.compare("Free") == 0)
				pcParticle->m_eType = PARTICLETYPE_Free;
			else
				ERRORBOX("Type: Parameter 1 is not a valid Particle Type");
		}

		return 0;
	}
	int Factory::LuaTexture(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcParticleScript = pThis->m_pcParticleScript;
		System * pcParticleSystem = pcParticleScript->m_pcParticleSystem;
		Emitter * pcParticleEmitter = pcParticleSystem->m_pcParticleEmitter;
		Particle * pcParticle = pcParticleSystem->m_pcParticle;

		if (pcParticleSystem && pcParticleEmitter && pcParticle)
		{
			std::string strFilePath = ReadParamString(pLuaState, 1);

			//pcParticle->m_uTextureID = pThis->m_pcTextureManager->LoadTexture(strFilePath);
		}

		return 0;
	}
	int Factory::LuaBlend(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcParticleScript = pThis->m_pcParticleScript;
		System * pcParticleSystem = pcParticleScript->m_pcParticleSystem;
		Emitter * pcParticleEmitter = pcParticleSystem->m_pcParticleEmitter;
		Particle * pcParticle = pcParticleSystem->m_pcParticle;

		if (pcParticleSystem && pcParticleEmitter && pcParticle)
		{
			std::string strBlendMode = ReadParamString(pLuaState, 1);

			EBlendType e = BLENDTYPE_None;

			if (strBlendMode.compare("Lamp") == 0)
			{
				//?
				e = BLENDTYPE_Lamp;
			}
			else if (strBlendMode.compare("Alpha") == 0)
			{
				//?
				e = BLENDTYPE_Alpha;
			}
			else if (strBlendMode.compare("Inverse Shadow") == 0)
			{
				//?
				e = BLENDTYPE_InvShadow;
			}
			else if (strBlendMode.compare("Shadow") == 0)
			{
				//?
				e = BLENDTYPE_Shadow;
			}
			else if (strBlendMode.compare("Color") == 0)
			{
				//?
				e = BLENDTYPE_Color;
			}
			else if (strBlendMode.compare("Add Color") == 0)
			{
				//?
				e = BLENDTYPE_AddColor;
			}
			else
			{
				ERRORBOX("Blend: Parameter 1 is not a valid Particle Blend Mode");

				//Default to Lamp Blend Mode
				e = BLENDTYPE_Lamp;
			}

			pcParticle->m_eSourceBlendMode = e;
		}

		return 0;
	}
	int Factory::LuaRGBA(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcParticleScript = pThis->m_pcParticleScript;
		System * pcParticleSystem = pcParticleScript->m_pcParticleSystem;
		Emitter * pcParticleEmitter = pcParticleSystem->m_pcParticleEmitter;
		Particle * pcParticle = pcParticleSystem->m_pcParticle;

		if (pcParticleSystem && pcParticleEmitter && pcParticle)
		{
			Particle::Int * r = (Particle::Int*)ReadParamPointer(pLuaState, 1);
			Particle::Int * g = (Particle::Int*)ReadParamPointer(pLuaState, 2);
			Particle::Int * b = (Particle::Int*)ReadParamPointer(pLuaState, 3);
			Particle::Int * a = (Particle::Int*)ReadParamPointer(pLuaState, 4);

			pcParticle->m_sColor.a = Particle::Int(*a);
			pcParticle->m_sColor.r = Particle::Int(*r);
			pcParticle->m_sColor.g = Particle::Int(*g);
			pcParticle->m_sColor.b = Particle::Int(*b);

			DELET(r);
			DELET(g);
			DELET(b);
			DELET(a);
		}

		return 0;
	}
	int Factory::LuaSize(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcParticleScript = pThis->m_pcParticleScript;
		System * pcParticleSystem = pcParticleScript->m_pcParticleSystem;
		Emitter * pcParticleEmitter = pcParticleSystem->m_pcParticleEmitter;
		Particle * pcParticle = pcParticleSystem->m_pcParticle;

		if (pcParticleSystem && pcParticleEmitter && pcParticle)
		{
			Particle::Int * size = (Particle::Int*)ReadParamPointer(pLuaState, 1);

			pcParticle->m_sSize.s = Particle::Int(((*size) << 8));

			DELET(size);
		}

		return 0;
	}
	int Factory::LuaSizeWH(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcParticleScript = pThis->m_pcParticleScript;
		System * pcParticleSystem = pcParticleScript->m_pcParticleSystem;
		Emitter * pcParticleEmitter = pcParticleSystem->m_pcParticleEmitter;
		Particle * pcParticle = pcParticleSystem->m_pcParticle;

		if (pcParticleSystem && pcParticleEmitter && pcParticle)
		{
			Particle::Int * w = (Particle::Int*)ReadParamPointer(pLuaState, 1);
			Particle::Int * h = (Particle::Int*)ReadParamPointer(pLuaState, 2);

			pcParticle->m_sSize.bWH = TRUE;
			pcParticle->m_sSize.w = Particle::Int(((*w) << 8));
			pcParticle->m_sSize.h = Particle::Int(((*h) << 8));

			DELET(w);
			DELET(h);
		}

		return 0;
	}
	int Factory::LuaLoop(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcParticleScript = pThis->m_pcParticleScript;
		System * pcParticleSystem = pcParticleScript->m_pcParticleSystem;
		Emitter * pcParticleEmitter = pcParticleSystem->m_pcParticleEmitter;
		Particle * pcParticle = pcParticleSystem->m_pcParticle;

		if (pcParticleSystem && pcParticleEmitter && pcParticle)
		{
			Particle::Dbl * b = (Particle::Dbl*)ReadParamPointer(pLuaState, 1);
			Particle::Dbl * e = (Particle::Dbl*)ReadParamPointer(pLuaState, 2);

			b->Birth();
			e->Birth();

			pcParticle->m_bLoop = TRUE;
			pcParticle->m_fLoopAt = b->value * 1000.0f;
			pcParticle->m_fLoopTime = e->value * 1000.0f;

			DELET(e);
			DELET(b);
		}

		return 0;
	}
	int Factory::LuaLifeTime(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcParticleScript = pThis->m_pcParticleScript;
		System * pcParticleSystem = pcParticleScript->m_pcParticleSystem;
		Emitter * pcParticleEmitter = pcParticleSystem->m_pcParticleEmitter;
		Particle * pcParticle = pcParticleSystem->m_pcParticle;

		if (pcParticleSystem && pcParticleEmitter && pcParticle)
		{
			Particle::Dbl * d = (Particle::Dbl*)ReadParamPointer(pLuaState, 1);

			pcParticle->m_sMaxLifeTime.t = Particle::Dbl(((*d) * 1000.0f));

			DELET(d);
		}

		return 0;
	}
	int Factory::LuaEventVelocity(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcParticleScript = pThis->m_pcParticleScript;
		System * pcParticleSystem = pcParticleScript->m_pcParticleSystem;
		Emitter * pcParticleEmitter = pcParticleSystem->m_pcParticleEmitter;
		Particle * pcParticle = pcParticleSystem->m_pcParticle;

		if (pcParticleSystem && pcParticleEmitter && pcParticle)
		{
			Particle::Dbl * d = (Particle::Dbl*)ReadParamPointer(pLuaState, 1);
			Particle::Int * x = (Particle::Int*)ReadParamPointer(pLuaState, 2);
			Particle::Int * y = (Particle::Int*)ReadParamPointer(pLuaState, 3);
			Particle::Int * z = (Particle::Int*)ReadParamPointer(pLuaState, 4);

			d->Birth();

			Particle::Point sVelocity;
			sVelocity.x = Particle::Int(((*x) << 8));
			sVelocity.y = Particle::Int(((*y) << 8));
			sVelocity.z = Particle::Int(((*z) << 8));

			pcParticle->m_vParticleEvents.push_back(new EventVelocity(sVelocity, d->value * 1000.0f));

			DELET(z);
			DELET(y);
			DELET(x);
			DELET(d);
		}

		return 0;
	}
	int Factory::LuaEventSize(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcParticleScript = pThis->m_pcParticleScript;
		System * pcParticleSystem = pcParticleScript->m_pcParticleSystem;
		Emitter * pcParticleEmitter = pcParticleSystem->m_pcParticleEmitter;
		Particle * pcParticle = pcParticleSystem->m_pcParticle;

		if (pcParticleSystem && pcParticleEmitter && pcParticle)
		{
			Particle::Dbl * d = (Particle::Dbl*)ReadParamPointer(pLuaState, 1);
			Particle::Int * i = (Particle::Int*)ReadParamPointer(pLuaState, 2);

			d->Birth();

			Particle::Size sSize;
			sSize.s = Particle::Int(((*i) << 8));

			pcParticle->m_vParticleEvents.push_back(new EventSize(sSize, d->value * 1000.0f));

			DELET(i);
			DELET(d);
		}

		return 0;
	}
	int Factory::LuaModifierSize(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcParticleScript = pThis->m_pcParticleScript;
		System * pcParticleSystem = pcParticleScript->m_pcParticleSystem;
		Emitter * pcParticleEmitter = pcParticleSystem->m_pcParticleEmitter;
		Particle * pcParticle = pcParticleSystem->m_pcParticle;

		if (pcParticleSystem && pcParticleEmitter && pcParticle)
		{
			Particle::Dbl * d = (Particle::Dbl*)ReadParamPointer(pLuaState, 1);
			Particle::Int * s = (Particle::Int*)ReadParamPointer(pLuaState, 2);

			d->Birth();

			Particle::Size sSize;
			sSize.s = Particle::Int(((*s) << 8));

			ModifierGroup * pcGroup = pcParticle->GetParticleModifierGroup(PARTICLEMODIFIERGROUPTYPE_Size);

			if (pcGroup == NULL)
			{
				pcGroup = new ModifierGroup(PARTICLEMODIFIERGROUPTYPE_Size);

				pcParticle->AddParticleModifierGroup(pcGroup);
			}

			pcGroup->AddModifier(new ModifierSize(sSize, d->value * 1000.0f));

			DELET(s);
			DELET(d);
		}

		return 0;
	}
	int Factory::LuaModifierRGBA(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcParticleScript = pThis->m_pcParticleScript;
		System * pcParticleSystem = pcParticleScript->m_pcParticleSystem;
		Emitter * pcParticleEmitter = pcParticleSystem->m_pcParticleEmitter;
		Particle * pcParticle = pcParticleSystem->m_pcParticle;

		if (pcParticleSystem && pcParticleEmitter && pcParticle)
		{
			Particle::Dbl * d = (Particle::Dbl*)ReadParamPointer(pLuaState, 1);
			Particle::Int * r = (Particle::Int*)ReadParamPointer(pLuaState, 2);
			Particle::Int * g = (Particle::Int*)ReadParamPointer(pLuaState, 3);
			Particle::Int * b = (Particle::Int*)ReadParamPointer(pLuaState, 4);
			Particle::Int * a = (Particle::Int*)ReadParamPointer(pLuaState, 5);

			d->Birth();

			Particle::Color sColor;
			sColor.r = *r;
			sColor.g = *g;
			sColor.b = *b;
			sColor.a = *a;

			ModifierGroup * pcGroup = pcParticle->GetParticleModifierGroup(PARTICLEMODIFIERGROUPTYPE_Color);

			if (pcGroup == NULL)
			{
				pcGroup = new ModifierGroup(PARTICLEMODIFIERGROUPTYPE_Color);

				pcParticle->AddParticleModifierGroup(pcGroup);
			}

			pcGroup->AddModifier(new ModifierColor(sColor, d->value * 1000.0f));

			DELET(a);
			DELET(b);
			DELET(g);
			DELET(r);
			DELET(d);
		}

		return 0;
	}
}