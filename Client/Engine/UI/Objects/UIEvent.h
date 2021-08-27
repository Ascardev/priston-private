#pragma once

struct UIEventArgs {};

enum EEventStatue
{
	EVENT_Click,
	EVENT_MoveIn,
	EVENT_MoveOut,
};

namespace UI
{
	class Event : public Element
	{
	public:
		Event();
		virtual ~Event();

		void SetEventID(int iID) {m_iEventID = iID;}
		static int Build(std::function<void(UIEventArgs const &)> const & f);
		static void Invoke(int iHandle);

		//Events Handlers
		void OnClick(EButton eButton){}
	private:
		int m_iEventID = 0;
	};
}