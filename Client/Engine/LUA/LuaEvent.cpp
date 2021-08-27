#include "StdAfx.h"
#include "LuaEvent.h"

namespace LUA
{
	Event::Event(double f) : m_fTime(f)
	{

	}
	Event::Event(Event & c)
	{
		m_fTime = c.m_fTime;
	}
	Event::~Event()
	{

	}
	EventVelocity::EventVelocity(Base::Point v, double f) : m_sVelocity(v), Event(f)
	{

	}
	EventVelocity::EventVelocity(EventVelocity & c) : Event(c)
	{
		m_sVelocity = c.m_sVelocity;
	}
	EventVelocity::~EventVelocity()
	{

	}
	EventVelocity *EventVelocity::Clone()
	{
		EventVelocity *pcClone = new EventVelocity(*this);

		return pcClone;
	}
	void EventVelocity::Apply(Base *pcLua)
	{
		m_sVelocity.Birth();

		pcLua->SetVelocity(m_sVelocity);
	}

	EventSize::EventSize(Base::Size s, double f) : m_sSize(s), Event(f)
	{

	}
	EventSize::EventSize(EventSize & c) : Event(c)
	{
		m_sSize = c.m_sSize;
	}
	EventSize::~EventSize()
	{

	}
	EventSize *EventSize::Clone()
	{
		EventSize *pcClone = new EventSize(*this);

		return pcClone;
	}
	void EventSize::Apply(Base *pcLua)
	{
		m_sSize.Birth();

		pcLua->SetSize(m_sSize);
	}
}