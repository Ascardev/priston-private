#include "StdAfx.h"
#include "Timer.h"

namespace BASE
{
	Time::Time(double fTick) : Node()
	{
		m_pEvent	= NULL;
		m_fTick		= fTick;
		m_fOffs		= 0.0f;
		m_iTicks	= 0;
		m_iMaxTicks	= INFINITE;
	}
	Time::Time(double fTick,LPEVENT pEvent) : Node()
	{
		m_pEvent	= pEvent;
		m_fTick		= fTick;
		m_fOffs		= 0.0f;
		m_iTicks	= 0;
		m_iMaxTicks	= INFINITE;
	}
	Time::Time(const Time &c) : Node(c)
	{
		m_pEvent	= c.m_pEvent ? new Event(*c.m_pEvent) : NULL;
		m_fTick		= c.m_fTick;
		m_fOffs		= 0.0f;
		m_iTicks	= 0;
		m_iMaxTicks	= c.m_iMaxTicks;
	}
	Time::~Time()
	{
		DELET(m_pEvent);
	}
	BOOL Time::Update(double fTime)
	{
		if ((m_iMaxTicks != INFINITE) && (m_iTicks >= m_iMaxTicks))
			return TRUE;

		m_fOffs += fTime;

		if (m_fOffs >= m_fTick)
		{
			do 
			{
				if (Fire())
					return TRUE;

				m_fOffs -= m_fTick;

			} while (m_fOffs >= m_fTick);
		}

		return FALSE;
	}
	BOOL Time::Fire()
	{
		if (m_pEvent)
			m_pEvent->Fire();

		m_iTicks ++;

		if ((m_iMaxTicks != INFINITE) && (m_iTicks >= m_iMaxTicks))
			return TRUE;

		return FALSE;
	}
}