#pragma once

namespace LUA
{
	class Object
	{
	public:
		Object();
		virtual ~Object();

		void AddObject(Base *pcLuaEmitter);
	private:
		std::vector<Base*> m_vLuas;
	};
}