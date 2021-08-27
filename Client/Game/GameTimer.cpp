#include "StdAfx.h"
#include "GameTimer.h"

CGameTime::CGameTime() : CINFO::Time()
{
	m_pcList = NULL;
}
CGameTime::~CGameTime()
{
	RELEASE(m_pcList);
}
void CGameTime::Init()
{

}
void CGameTime::Shutdown()
{
	CList<BASE::LPTIME> *item = m_pcList;

	while (item)
	{
		CList<BASE::LPTIME> *next = item->next;

		DELET(item->obj);

		item = next;
	}
}
void CGameTime::Update(double fTime)
{
	CList<BASE::LPTIME> *item = m_pcList;

	while (item != NULL)
	{
		CList<BASE::LPTIME> *next = item->next;

		BASE::LPTIME timer = item->obj;

		if (timer != NULL)
		{
			if (timer->Update(fTime))
			{
				DELET(timer);
				DELET(item);
			}
		}
		else
			DELET(item);

		item = next;
	}
}
void CGameTime::Add(BASE::LPTIME pTimer)
{
	if (m_pcList == NULL)
		m_pcList = new CList<BASE::LPTIME>(pTimer);
	else
		m_pcList->Add(pTimer);
}