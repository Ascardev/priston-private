#include "StdAfx.h"
#include "LuaFactory.h"

namespace LUA
{
	Factory::Factory() : CLua()
	{
		m_pcMutex = new CMutex("Lua Factory");
		m_pcTextureManager = NULL;
		m_pcLuaScript = NULL;
	}
	Factory::~Factory()
	{
		//WRITEDBG( "~CLuaFactory()" );

		for (vector<Script*>::iterator it = m_vLuaScriptCache.begin(); it != m_vLuaScriptCache.end(); it++)
		{
			Script * pcCachedLuaScript = *it;

			DELET(pcCachedLuaScript);
		}
		m_vLuaScriptCache.clear();

		m_pcLuaScript = NULL;

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

		//Lua Script Handlers
		Register("Script", LuaScript);
		Register("Author", LuaAuthor);

		//Lua System Handlers
		Register("Object", LuaObject);
		Register("ObjectEnd", LuaObjectEnd);

		Register("System", LuaSystem);
		Register("SystemEnd", LuaSystemEnd);

		Register("Name", LuaName);

		//Emitter Handlers
		Register("EmitType", LuaEmitType);

		Register("Position", LuaEmitPosition);
		Register("Velocity", LuaEmitVelocity);

		Register("EmitRotation", LuaEmitRotation);
		Register("EmitAngularVelocity", LuaEmitAngularVelocity);

		Register("EmitDelay", LuaEmitDelay);
		Register("EmitLifeTime", LuaEmitLifeTime);

		Register("EmitLuas", LuaEmitLuas);
		Register("EmitInterval", LuaEmitInterval);

		//Emitter Events Handlers

		//Lua Handlers
		Register("Type", LuaType);

		Register("Texture", LuaTexture);
		Register("Blend", LuaBlend);

		Register("RGBA", LuaRGBA);
		Register("Size", LuaSize);
		Register("SizeWH", LuaSizeWH);

		Register("Loop", LuaLoop);
		Register("LifeTime", LuaLifeTime);

		//Lua Events Handlers
		Register("EventVelocity", LuaEventVelocity);
		Register("EventSize", LuaEventSize);

		//Lua Modifiers Handlers
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

		m_pcLuaScript = bUseCache ? GetScriptFromCache(strFilePath) : NULL;

		if (m_pcLuaScript == NULL)
		{
			m_pcLuaScript = new Script(strFilePath);

			DoFile(strFilePath);

			AddScriptToCache(m_pcLuaScript);
		}

		pcRet = new Script(*m_pcLuaScript);

		m_pcMutex->UnLock();

		return pcRet;
	}
	void Factory::ClearCache()
	{
		for (vector<Script*>::iterator it = m_vLuaScriptCache.begin(); it != m_vLuaScriptCache.end(); it++)
		{
			Script * pcCachedLuaScript = *it;

			DELET(pcCachedLuaScript);
		}
		m_vLuaScriptCache.clear();
	}
	void Factory::AddScriptToCache(Script * pcLuaScriptToCache)
	{
		m_vLuaScriptCache.push_back(pcLuaScriptToCache);
	}
	Script * Factory::GetScriptFromCache(string strFilePath)
	{
		for (vector<Script*>::iterator it = m_vLuaScriptCache.begin(); it != m_vLuaScriptCache.end(); it++)
		{
			Script * pcCachedLuaScript = *it;

			if (pcCachedLuaScript->GetFilePath().compare(strFilePath) == 0)
				return pcCachedLuaScript;
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

		Base::Int * pcLuaInt = new Base::Int(iInt);

		lua_pushinteger(pLuaState->get_ptr(), (int)pcLuaInt);

		return 1;
	}
	int Factory::LuaRandomInt(LuaState * pLuaState)
	{
		int iIntL = ReadParamInteger(pLuaState, 1);
		int iIntH = ReadParamInteger(pLuaState, 2);

		Base::Int * pcLuaInt = new Base::Int(iIntL, iIntH);

		lua_pushinteger(pLuaState->get_ptr(), (int)pcLuaInt);

		return 1;
	}
	int Factory::LuaDbl(LuaState * pLuaState)
	{
		double dDbl = ReadParamDouble(pLuaState, 1);

		Base::Dbl * pcLuaDbl = new Base::Dbl(dDbl);

		lua_pushinteger(pLuaState->get_ptr(), (int)pcLuaDbl);

		return 1;
	}
	int Factory::LuaRandomDbl(LuaState * pLuaState)
	{
		double dDblL = ReadParamDouble(pLuaState, 1);
		double dDblH = ReadParamDouble(pLuaState, 2);

		Base::Dbl * pcLuaDbl = new Base::Dbl(dDblL, dDblH);

		lua_pushinteger(pLuaState->get_ptr(), (int)pcLuaDbl);

		return 1;
	}
	int Factory::LuaScript(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcLuaScript = pThis->m_pcLuaScript;

		if (pcLuaScript)
		{
			std::string strScript = ReadParamString(pLuaState, 1);

			pcLuaScript->m_strScript = strScript;
		}

		return 0;
	}
	int Factory::LuaAuthor(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcLuaScript = pThis->m_pcLuaScript;

		if (pcLuaScript)
		{
			std::string strAuthor = ReadParamString(pLuaState, 1);

			pcLuaScript->m_strAuthor = strAuthor;
		}

		return 0;
	}
	int Factory::LuaSystem(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcLuaScript = pThis->m_pcLuaScript;

		if (pcLuaScript)
		{
			std::string strLuaType = ReadParamString(pLuaState, 1);

			System * pcLuaSystem = new System();
			pcLuaSystem->m_pcLua = new Base();

			if (strLuaType.compare("Billboard") == 0)
			{
				//A Simple Billboard
				pcLuaSystem->m_pcLua->m_eVisualType = LUAVISUALTYPE_Billboard;
			}
			else if (strLuaType.compare("BillboardRotation") == 0)
			{
				//A Simple Billboard Rotation
				pcLuaSystem->m_pcLua->m_eVisualType = LUAVISUALTYPE_BillboardRotation;
			}
			else if (strLuaType.compare("BillboardHorizontal") == 0)
			{
				//A Horizontal Billboard
				pcLuaSystem->m_pcLua->m_eVisualType = LUAVISUALTYPE_BillboardHorizontal;
			}
			else if (strLuaType.compare("BillboardHorizontalRotation") == 0)
			{
				//A Horizontal Billboard with Rotation Attributes
				pcLuaSystem->m_pcLua->m_eVisualType = LUAVISUALTYPE_BillboardHorizontalRotation;
			}
			else if (strLuaType.compare("BillboardVertical") == 0)
			{
				//A Horizontal Billboard with Rotation Attributes
				pcLuaSystem->m_pcLua->m_eVisualType = LUAVISUALTYPE_BillboardVertical;
			}
			else if (strLuaType.compare("BillboardVerticalRotation") == 0)
			{
				//A Horizontal Billboard with Rotation Attributes
				pcLuaSystem->m_pcLua->m_eVisualType = LUAVISUALTYPE_BillboardVerticalRotation;
			}
			else
				ERRORBOX("LuaSystem: Parameter 1 is not a valid Lua Type");

			pcLuaScript->m_pcLuaSystem = pcLuaSystem;
		}

		return 0;
	}
	int Factory::LuaSystemEnd(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcLuaScript = pThis->m_pcLuaScript;

		if (pcLuaScript)
		{
			pcLuaScript->Add(pcLuaScript->m_pcLuaSystem);

			pcLuaScript->m_pcLuaSystem = NULL;
		}

		return 0;
	}
	int Factory::LuaObject(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcLuaScript = pThis->m_pcLuaScript;
		System * pcLuaSystem = pcLuaScript->m_pcLuaSystem;
		Emitter * pcLuaEmitter = pcLuaSystem->m_pcLuaEmitter;

		if (pcLuaSystem && pcLuaEmitter)
		{
			if (pcLuaSystem->m_pcLua)
				DELET(pcLuaSystem->m_pcLua);

			pcLuaSystem->m_pcLua = new Base();

			pcLuaSystem->m_pcLua->SetName(ReadParamString(pLuaState, 1));
		}

		return 0;
	}
	int Factory::LuaObjectEnd(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcLuaScript = pThis->m_pcLuaScript;
		System * pcLuaSystem = pcLuaScript->m_pcLuaSystem;
		Emitter * pcLuaEmitter = pcLuaSystem->m_pcLuaEmitter;

		if (pcLuaSystem && pcLuaEmitter)
		{
			if (pcLuaSystem->m_pcLua)
			{
				pcLuaSystem->Add(pcLuaSystem->m_pcLua);

				DELET(pcLuaSystem->m_pcLua);
			}

			pcLuaSystem->m_pcLua = NULL;
		}

		return 0;
	}
	int Factory::LuaAddObject(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcLuaScript = pThis->m_pcLuaScript;
		System * pcLuaSystem = pcLuaScript->m_pcLuaSystem;
		Emitter * pcLuaEmitter = pcLuaSystem->m_pcLuaEmitter;

		if (pcLuaSystem && pcLuaEmitter)
		{
			std::string strName = ReadParamString(pLuaState, 1);
			std::string strNameType = ReadParamString(pLuaState, 2);

			for (std::vector<Base*>::iterator it = pcLuaSystem->m_vActiveLuas.begin(); it != pcLuaSystem->m_vActiveLuas.end(); it++)
			{
				Base * pcLua = (*it);

				if (!pcLua->IsActive())
				{
					if (pcLua->GetName().compare(strName) == 0)
					{
						pcLua->SetNameType(strNameType);

						pcLua->SetActive(TRUE);
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
		Script * pcLuaScript = pThis->m_pcLuaScript;
		System * pcLuaSystem = pcLuaScript->m_pcLuaSystem;

		if (pcLuaSystem)
		{
			std::string strName = ReadParamString(pLuaState, 1);

			pcLuaSystem->m_strName = strName;
		}

		return 0;
	}
	int Factory::LuaEmitType(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcLuaScript = pThis->m_pcLuaScript;
		System * pcLuaSystem = pcLuaScript->m_pcLuaSystem;
		Emitter * pcLuaEmitter = pcLuaSystem->m_pcLuaEmitter;
		Base * pcLua = pcLuaSystem->m_pcLua;

		if (pcLuaSystem && pcLuaEmitter && pcLua)
		{
			std::string strEmitterType = ReadParamString(pLuaState, 1);

			if (strEmitterType.compare("Follow") == 0)
				pcLuaEmitter->m_eType = LUAEMITTERTYPE_Follow;
			else if (strEmitterType.compare("Free") == 0)
				pcLuaEmitter->m_eType = LUAEMITTERTYPE_Free;
			else
				ERRORBOX("EmitType: Parameter 1 is not a valid Emitter Type");
		}

		return 0;
	}
	int Factory::LuaEmitPosition(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcLuaScript = pThis->m_pcLuaScript;
		System * pcLuaSystem = pcLuaScript->m_pcLuaSystem;
		Emitter * pcLuaEmitter = pcLuaSystem->m_pcLuaEmitter;
		Base * pcLua = pcLuaSystem->m_pcLua;

		if (pcLuaSystem && pcLuaEmitter && pcLua)
		{
			Base::Int * x = (Base::Int*)ReadParamPointer(pLuaState, 1);
			Base::Int * y = (Base::Int*)ReadParamPointer(pLuaState, 2);
			Base::Int * z = (Base::Int*)ReadParamPointer(pLuaState, 3);

			pcLuaEmitter->m_sPosition.x = Base::Int(((*x) << 8));
			pcLuaEmitter->m_sPosition.y = Base::Int(((*y) << 8));
			pcLuaEmitter->m_sPosition.z = Base::Int(((*z) << 8));

			DELET(x);
			DELET(y);
			DELET(z);
		}

		return 0;
	}
	int Factory::LuaEmitVelocity(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcLuaScript = pThis->m_pcLuaScript;
		System * pcLuaSystem = pcLuaScript->m_pcLuaSystem;
		Emitter * pcLuaEmitter = pcLuaSystem->m_pcLuaEmitter;
		Base * pcLua = pcLuaSystem->m_pcLua;

		if (pcLuaSystem && pcLuaEmitter && pcLua)
		{
			Base::Int * x = (Base::Int*)ReadParamPointer(pLuaState, 1);
			Base::Int * y = (Base::Int*)ReadParamPointer(pLuaState, 2);
			Base::Int * z = (Base::Int*)ReadParamPointer(pLuaState, 3);

			pcLuaEmitter->m_sVelocity.x = Base::Int(((*x) << 8));
			pcLuaEmitter->m_sVelocity.y = Base::Int(((*y) << 8));
			pcLuaEmitter->m_sVelocity.z = Base::Int(((*z) << 8));

			DELET(x);
			DELET(y);
			DELET(z);
		}

		return 0;
	}
	int Factory::LuaEmitRotation(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcLuaScript = pThis->m_pcLuaScript;
		System * pcLuaSystem = pcLuaScript->m_pcLuaSystem;
		Emitter * pcLuaEmitter = pcLuaSystem->m_pcLuaEmitter;
		Base * pcLua = pcLuaSystem->m_pcLua;

		if (pcLuaSystem && pcLuaEmitter && pcLua)
		{
			Base::Dbl * p = (Base::Dbl*)ReadParamPointer(pLuaState, 1);
			Base::Dbl * y = (Base::Dbl*)ReadParamPointer(pLuaState, 2);
			Base::Dbl * r = (Base::Dbl*)ReadParamPointer(pLuaState, 3);

			pcLuaEmitter->m_sRotation.p = *p;
			pcLuaEmitter->m_sRotation.y = *y;
			pcLuaEmitter->m_sRotation.r = *r;

			DELET(r);
			DELET(y);
			DELET(p);
		}

		return 0;
	}
	int Factory::LuaEmitAngularVelocity(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcLuaScript = pThis->m_pcLuaScript;
		System * pcLuaSystem = pcLuaScript->m_pcLuaSystem;
		Emitter * pcLuaEmitter = pcLuaSystem->m_pcLuaEmitter;
		Base * pcLua = pcLuaSystem->m_pcLua;

		if (pcLuaSystem && pcLuaEmitter && pcLua)
		{
			Base::Dbl * p = (Base::Dbl*)ReadParamPointer(pLuaState, 1);
			Base::Dbl * y = (Base::Dbl*)ReadParamPointer(pLuaState, 2);
			Base::Dbl * r = (Base::Dbl*)ReadParamPointer(pLuaState, 3);

			pcLuaEmitter->m_sAngularVelocity.p = *p;
			pcLuaEmitter->m_sAngularVelocity.y = *y;
			pcLuaEmitter->m_sAngularVelocity.r = *r;

			DELET(r);
			DELET(y);
			DELET(p);
		}

		return 0;
	}
	int Factory::LuaEmitDelay(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcLuaScript = pThis->m_pcLuaScript;
		System * pcLuaSystem = pcLuaScript->m_pcLuaSystem;
		Emitter * pcLuaEmitter = pcLuaSystem->m_pcLuaEmitter;
		Base * pcLua = pcLuaSystem->m_pcLua;

		if (pcLuaSystem && pcLuaEmitter && pcLua)
		{
			Base::Dbl * d = (Base::Dbl*)ReadParamPointer(pLuaState, 1);

			pcLuaEmitter->m_sMaxDelay.t = Base::Dbl(((*d) * 1000.0f));

			DELET(d);
		}

		return 0;
	}
	int Factory::LuaEmitLifeTime(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcLuaScript = pThis->m_pcLuaScript;
		System * pcLuaSystem = pcLuaScript->m_pcLuaSystem;
		Emitter * pcLuaEmitter = pcLuaSystem->m_pcLuaEmitter;
		Base * pcLua = pcLuaSystem->m_pcLua;

		if (pcLuaSystem && pcLuaEmitter && pcLua)
		{
			Base::Dbl * d = (Base::Dbl*)ReadParamPointer(pLuaState, 1);

			pcLuaEmitter->m_sMaxLifeTime.t = Base::Dbl(((*d) * 1000.0f));

			DELET(d);
		}

		return 0;
	}
	int Factory::LuaEmitLuas(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcLuaScript = pThis->m_pcLuaScript;
		System * pcLuaSystem = pcLuaScript->m_pcLuaSystem;
		Emitter * pcLuaEmitter = pcLuaSystem->m_pcLuaEmitter;
		Base * pcLua = pcLuaSystem->m_pcLua;

		if (pcLuaSystem && pcLuaEmitter && pcLua)
		{
			Base::Int * p = (Base::Int*)ReadParamPointer(pLuaState, 1);

			pcLuaEmitter->m_sLuas = Base::Int(*p);

			DELET(p);
		}

		return 0;
	}
	int Factory::LuaEmitInterval(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcLuaScript = pThis->m_pcLuaScript;
		System * pcLuaSystem = pcLuaScript->m_pcLuaSystem;
		Emitter * pcLuaEmitter = pcLuaSystem->m_pcLuaEmitter;
		Base * pcLua = pcLuaSystem->m_pcLua;

		if (pcLuaSystem && pcLuaEmitter && pcLua)
		{
			Base::Dbl * d = (Base::Dbl*)ReadParamPointer(pLuaState, 1);

			pcLuaEmitter->m_sInterval = Base::Dbl(((*d) * 1000.0f));

			DELET(d);
		}

		return 0;
	}
	int Factory::LuaType(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcLuaScript = pThis->m_pcLuaScript;
		System * pcLuaSystem = pcLuaScript->m_pcLuaSystem;
		Emitter * pcLuaEmitter = pcLuaSystem->m_pcLuaEmitter;
		Base * pcLua = pcLuaSystem->m_pcLua;

		if (pcLuaSystem && pcLuaEmitter && pcLua)
		{
			std::string strEmitterType = ReadParamString(pLuaState, 1);

			if (strEmitterType.compare("Follow") == 0)
				pcLua->m_eType = LUATYPE_Follow;
			else if (strEmitterType.compare("Free") == 0)
				pcLua->m_eType = LUATYPE_Free;
			else
				ERRORBOX("Type: Parameter 1 is not a valid Lua Type");
		}

		return 0;
	}
	int Factory::LuaTexture(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcLuaScript = pThis->m_pcLuaScript;
		System * pcLuaSystem = pcLuaScript->m_pcLuaSystem;
		Emitter * pcLuaEmitter = pcLuaSystem->m_pcLuaEmitter;
		Base * pcLua = pcLuaSystem->m_pcLua;

		if (pcLuaSystem && pcLuaEmitter && pcLua)
		{
			std::string strFilePath = ReadParamString(pLuaState, 1);

			pcLua->m_uTextureID = pThis->m_pcTextureManager->LoadTexture(strFilePath);
		}

		return 0;
	}
	int Factory::LuaBlend(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcLuaScript = pThis->m_pcLuaScript;
		System * pcLuaSystem = pcLuaScript->m_pcLuaSystem;
		Emitter * pcLuaEmitter = pcLuaSystem->m_pcLuaEmitter;
		Base * pcLua = pcLuaSystem->m_pcLua;

		if (pcLuaSystem && pcLuaEmitter && pcLua)
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
				ERRORBOX("Blend: Parameter 1 is not a valid Lua Blend Mode");

				//Default to Lamp Blend Mode
				e = BLENDTYPE_Lamp;
			}

			pcLua->m_eSourceBlendMode = e;
		}

		return 0;
	}
	int Factory::LuaRGBA(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcLuaScript = pThis->m_pcLuaScript;
		System * pcLuaSystem = pcLuaScript->m_pcLuaSystem;
		Emitter * pcLuaEmitter = pcLuaSystem->m_pcLuaEmitter;
		Base * pcLua = pcLuaSystem->m_pcLua;

		if (pcLuaSystem && pcLuaEmitter && pcLua)
		{
			Base::Int * r = (Base::Int*)ReadParamPointer(pLuaState, 1);
			Base::Int * g = (Base::Int*)ReadParamPointer(pLuaState, 2);
			Base::Int * b = (Base::Int*)ReadParamPointer(pLuaState, 3);
			Base::Int * a = (Base::Int*)ReadParamPointer(pLuaState, 4);

			pcLua->m_sColor.a = Base::Int(*a);
			pcLua->m_sColor.r = Base::Int(*r);
			pcLua->m_sColor.g = Base::Int(*g);
			pcLua->m_sColor.b = Base::Int(*b);

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
		Script * pcLuaScript = pThis->m_pcLuaScript;
		System * pcLuaSystem = pcLuaScript->m_pcLuaSystem;
		Emitter * pcLuaEmitter = pcLuaSystem->m_pcLuaEmitter;
		Base * pcLua = pcLuaSystem->m_pcLua;

		if (pcLuaSystem && pcLuaEmitter && pcLua)
		{
			Base::Int * size = (Base::Int*)ReadParamPointer(pLuaState, 1);

			pcLua->m_sSize.s = Base::Int(((*size) << 8));

			DELET(size);
		}

		return 0;
	}
	int Factory::LuaSizeWH(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcLuaScript = pThis->m_pcLuaScript;
		System * pcLuaSystem = pcLuaScript->m_pcLuaSystem;
		Emitter * pcLuaEmitter = pcLuaSystem->m_pcLuaEmitter;
		Base * pcLua = pcLuaSystem->m_pcLua;

		if (pcLuaSystem && pcLuaEmitter && pcLua)
		{
			Base::Int * w = (Base::Int*)ReadParamPointer(pLuaState, 1);
			Base::Int * h = (Base::Int*)ReadParamPointer(pLuaState, 2);

			pcLua->m_sSize.bWH = TRUE;
			pcLua->m_sSize.w = Base::Int(((*w) << 8));
			pcLua->m_sSize.h = Base::Int(((*h) << 8));

			DELET(w);
			DELET(h);
		}

		return 0;
	}
	int Factory::LuaLoop(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcLuaScript = pThis->m_pcLuaScript;
		System * pcLuaSystem = pcLuaScript->m_pcLuaSystem;
		Emitter * pcLuaEmitter = pcLuaSystem->m_pcLuaEmitter;
		Base * pcLua = pcLuaSystem->m_pcLua;

		if (pcLuaSystem && pcLuaEmitter && pcLua)
		{
			Base::Dbl * b = (Base::Dbl*)ReadParamPointer(pLuaState, 1);
			Base::Dbl * e = (Base::Dbl*)ReadParamPointer(pLuaState, 2);

			b->Birth();
			e->Birth();

			pcLua->m_bLoop = TRUE;
			pcLua->m_fLoopAt = b->value * 1000.0f;
			pcLua->m_fLoopTime = e->value * 1000.0f;

			DELET(e);
			DELET(b);
		}

		return 0;
	}
	int Factory::LuaLifeTime(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcLuaScript = pThis->m_pcLuaScript;
		System * pcLuaSystem = pcLuaScript->m_pcLuaSystem;
		Emitter * pcLuaEmitter = pcLuaSystem->m_pcLuaEmitter;
		Base * pcLua = pcLuaSystem->m_pcLua;

		if (pcLuaSystem && pcLuaEmitter && pcLua)
		{
			Base::Dbl * d = (Base::Dbl*)ReadParamPointer(pLuaState, 1);

			pcLua->m_sMaxLifeTime.t = Base::Dbl(((*d) * 1000.0f));

			DELET(d);
		}

		return 0;
	}
	int Factory::LuaEventVelocity(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcLuaScript = pThis->m_pcLuaScript;
		System * pcLuaSystem = pcLuaScript->m_pcLuaSystem;
		Emitter * pcLuaEmitter = pcLuaSystem->m_pcLuaEmitter;
		Base * pcLua = pcLuaSystem->m_pcLua;

		if (pcLuaSystem && pcLuaEmitter && pcLua)
		{
			Base::Dbl * d = (Base::Dbl*)ReadParamPointer(pLuaState, 1);
			Base::Int * x = (Base::Int*)ReadParamPointer(pLuaState, 2);
			Base::Int * y = (Base::Int*)ReadParamPointer(pLuaState, 3);
			Base::Int * z = (Base::Int*)ReadParamPointer(pLuaState, 4);

			d->Birth();

			Base::Point sVelocity;
			sVelocity.x = Base::Int(((*x) << 8));
			sVelocity.y = Base::Int(((*y) << 8));
			sVelocity.z = Base::Int(((*z) << 8));

			pcLua->m_vLuaEvents.push_back(new EventVelocity(sVelocity, d->value * 1000.0f));

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
		Script * pcLuaScript = pThis->m_pcLuaScript;
		System * pcLuaSystem = pcLuaScript->m_pcLuaSystem;
		Emitter * pcLuaEmitter = pcLuaSystem->m_pcLuaEmitter;
		Base * pcLua = pcLuaSystem->m_pcLua;

		if (pcLuaSystem && pcLuaEmitter && pcLua)
		{
			Base::Dbl * d = (Base::Dbl*)ReadParamPointer(pLuaState, 1);
			Base::Int * i = (Base::Int*)ReadParamPointer(pLuaState, 2);

			d->Birth();

			Base::Size sSize;
			sSize.s = Base::Int(((*i) << 8));

			pcLua->m_vLuaEvents.push_back(new EventSize(sSize, d->value * 1000.0f));

			DELET(i);
			DELET(d);
		}

		return 0;
	}
	int Factory::LuaModifierSize(LuaState * pLuaState)
	{
		Factory * pThis = GetThis(pLuaState);
		Script * pcLuaScript = pThis->m_pcLuaScript;
		System * pcLuaSystem = pcLuaScript->m_pcLuaSystem;
		Emitter * pcLuaEmitter = pcLuaSystem->m_pcLuaEmitter;
		Base * pcLua = pcLuaSystem->m_pcLua;

		if (pcLuaSystem && pcLuaEmitter && pcLua)
		{
			Base::Dbl * d = (Base::Dbl*)ReadParamPointer(pLuaState, 1);
			Base::Int * s = (Base::Int*)ReadParamPointer(pLuaState, 2);

			d->Birth();

			Base::Size sSize;
			sSize.s = Base::Int(((*s) << 8));

			ModifierGroup * pcGroup = pcLua->GetLuaModifierGroup(LUAMODIFIERGROUPTYPE_Size);

			if (pcGroup == NULL)
			{
				pcGroup = new ModifierGroup(LUAMODIFIERGROUPTYPE_Size);

				pcLua->AddLuaModifierGroup(pcGroup);
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
		Script * pcLuaScript = pThis->m_pcLuaScript;
		System * pcLuaSystem = pcLuaScript->m_pcLuaSystem;
		Emitter * pcLuaEmitter = pcLuaSystem->m_pcLuaEmitter;
		Base * pcLua = pcLuaSystem->m_pcLua;

		if (pcLuaSystem && pcLuaEmitter && pcLua)
		{
			Base::Dbl * d = (Base::Dbl*)ReadParamPointer(pLuaState, 1);
			Base::Int * r = (Base::Int*)ReadParamPointer(pLuaState, 2);
			Base::Int * g = (Base::Int*)ReadParamPointer(pLuaState, 3);
			Base::Int * b = (Base::Int*)ReadParamPointer(pLuaState, 4);
			Base::Int * a = (Base::Int*)ReadParamPointer(pLuaState, 5);

			d->Birth();

			Base::Color sColor;
			sColor.r = *r;
			sColor.g = *g;
			sColor.b = *b;
			sColor.a = *a;

			ModifierGroup * pcGroup = pcLua->GetLuaModifierGroup(LUAMODIFIERGROUPTYPE_Color);

			if (pcGroup == NULL)
			{
				pcGroup = new ModifierGroup(LUAMODIFIERGROUPTYPE_Color);

				pcLua->AddLuaModifierGroup(pcGroup);
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