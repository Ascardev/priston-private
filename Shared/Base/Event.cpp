#include "StdAfx.h"
#include "Event.h"

namespace BASE
{
	Event::Event(const Event &c) : Node(c)
	{
		for (std::vector<EventHandler *>::const_iterator it = c.m_vEventHandlers.begin(); it != c.m_vEventHandlers.end(); it ++)
		{
			auto *pEventHandler = *it;

			m_vEventHandlers.push_back(new EventHandler(*pEventHandler));
		}
	}
	Event::~Event()
	{
		for (std::vector<EventHandler *>::iterator it = m_vEventHandlers.begin(); it != m_vEventHandlers.end(); it ++)
		{
			auto *pEventHandler = *it;

			DELET(pEventHandler);
		}
	}
	void Event::AddEventHandler(EventHandler *pEventHandler)
	{
		m_vEventHandlers.push_back(pEventHandler);
	}
	void Event::Fire()
	{
		for (std::vector<EventHandler *>::iterator it = m_vEventHandlers.begin(); it != m_vEventHandlers.end(); it ++)
		{
			auto *c = *it;

			c->Fire();
		}
	}

	Event *EVENTFACTROY::BuildEvent(void *pOnEventHandler)
	{
		auto *pEvent = new Event;

		pEvent->AddEventHandler(new EventHandler(pOnEventHandler));

		return pEvent;
	}
	Event *EVENTFACTROY::BuildEvent(void *pOnEventHandler,void *pPointer1)
	{
		auto *pEvent = new Event;

		pEvent->AddEventHandler(new EventHandler1(pOnEventHandler,pPointer1));

		return pEvent;
	}
	Event *EVENTFACTROY::BuildEvent(void *pOnEventHandler,void *pPointer1,void *pPointer2)
	{
		auto *pEvent = new Event;

		pEvent->AddEventHandler(new EventHandler2(pOnEventHandler,pPointer1,pPointer2));

		return pEvent;
	}
}