#pragma once

#define GAME_WORLDTIME	800

namespace CINFO
{
	typedef class Time *LPTIME;

	class Time
	{
	public:
		Time();
		virtual ~Time(){}

		double Update();

		void SetMultiCore(BOOL b) {m_bMultiCore = b;}
	protected:
		double m_dFrequency;
		BOOL m_bMultiCore;
		LARGE_INTEGER m_liLastTick;
	};
}

static int GetGMTime(time_t t)
{
	struct tm sLocalTime;
	struct tm sGMTime;

	localtime_s(&sLocalTime, &t);
	gmtime_s(&sGMTime, &t);

	int iTime = sLocalTime.tm_hour - sGMTime.tm_hour;

	if (iTime < -12)
		iTime += 24;
	else if (iTime > 12)
		iTime -= 24;

	return iTime;
}