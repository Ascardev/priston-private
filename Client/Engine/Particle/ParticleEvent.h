#pragma once

namespace PARTICLE
{
	class Event
	{
	public:
		Event(double f);
		Event(Event & c);

		virtual ~Event();

		virtual Event *Clone() = 0;
		virtual void Apply(Particle *pcParticle) = 0;
		double GetTime() { return m_fTime; }
	protected:
		double m_fTime;
	};
	class EventVelocity : public Event
	{
	public:
		EventVelocity(Particle::Point v, double f);
		EventVelocity(EventVelocity & c);

		virtual ~EventVelocity();

		EventVelocity *Clone();
		void Apply(Particle *pcParticle);
	protected:
		Particle::Point m_sVelocity;
	};
	class EventSize : public Event
	{
	public:
		EventSize(Particle::Size s, double f);
		EventSize(EventSize & c);

		virtual ~EventSize();

		EventSize *Clone();
		void Apply(Particle *pcParticle);
	protected:
		Particle::Size m_sSize;
	};
}