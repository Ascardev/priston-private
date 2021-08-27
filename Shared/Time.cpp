#include "StdAfx.h"
#include "Time.h"

namespace CINFO
{
	Time::Time()
	{
		LARGE_INTEGER liFrequency;
		QueryPerformanceFrequency(&liFrequency);

		m_dFrequency = (double)liFrequency.QuadPart;

		m_bMultiCore = FALSE;

		m_liLastTick.QuadPart = 0;
	}
	double Time::Update()
	{
		LARGE_INTEGER liNewTick;

		QueryPerformanceCounter(&liNewTick);

		if (!m_liLastTick.QuadPart)
			QueryPerformanceCounter(&m_liLastTick);

		double dUpdate = (((double)(liNewTick.QuadPart - m_liLastTick.QuadPart)) * 1000.0f) / m_dFrequency;

		m_liLastTick = liNewTick;

		return dUpdate;
	}
}