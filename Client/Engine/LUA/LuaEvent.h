#pragma once

namespace LUA
{
	class Event
	{
	public:
		Event(double f);
		Event(Event & c);

		virtual ~Event();

		virtual Event *Clone() = 0;
		virtual void Apply(Base *pcLua) = 0;
		double GetTime() { return m_fTime; }
	protected:
		double m_fTime;
	};
	class EventVelocity : public Event
	{
	public:
		EventVelocity(Base::Point v, double f);
		EventVelocity(EventVelocity & c);

		virtual ~EventVelocity();

		EventVelocity *Clone();
		void Apply(Base *pcLua);
	protected:
		Base::Point m_sVelocity;
	};
	class EventSize : public Event
	{
	public:
		EventSize(Base::Size s, double f);
		EventSize(EventSize & c);

		virtual ~EventSize();

		EventSize *Clone();
		void Apply(Base *pcLua);
	protected:
		Base::Size m_sSize;
	};
}