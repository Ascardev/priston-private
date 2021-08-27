#pragma once

namespace BASE
{
	typedef class Time *LPTIME;

	class Time : public Node
	{
	public:
		Time(double fTick);
		Time(double fTick,LPEVENT pEvent);
		Time(const Time &c);
		virtual ~Time();

		BOOL Update(double fTime);
		void SetEvent(LPEVENT pEvent) {m_pEvent = pEvent;}
	protected:
		BOOL Fire();
	protected:
		LPEVENT m_pEvent;
		double m_fTick;
		double m_fOffs;

		int m_iTicks;
		int m_iMaxTicks;
	};
}