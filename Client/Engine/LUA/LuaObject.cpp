#include "StdAfx.h"
#include "LuaObject.h"

namespace LUA
{
	Object::Object()
	{

	}
	Object::~Object()
	{

	}
	void Object::AddObject(Base *pcLuaEmitter)
	{
		m_vLuas.push_back(pcLuaEmitter);
	}
}