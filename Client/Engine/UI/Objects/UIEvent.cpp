#include "StdAfx.h"
#include "UIEvent.h"

std::vector<std::pair<std::function<void(UIEventArgs const&)>,int>> vEventsHandler;

int iEventHandlerIDS = 0;

struct CompareSecondEventHandler
{
	CompareSecondEventHandler(int val) : _valo( val ) {}

	bool operator()(const std::pair<std::function<void(UIEventArgs const&)>, int>& elem) const
	{
		return _valo == elem.second;
	}

private:
	int _valo;
};

namespace UI
{
	Event::Event()
	{

	}
	Event::~Event()
	{

	}
	int Event::Build(std::function<void(UIEventArgs const &)> const & f)
	{
		iEventHandlerIDS++;

		vEventsHandler.push_back(std::make_pair(f,iEventHandlerIDS));

		return iEventHandlerIDS;
	}

	void Event::Invoke(int iHandle)
	{
		auto it = std::find_if(vEventsHandler.begin(),vEventsHandler.end(),CompareSecondEventHandler(iHandle));

		UIEventArgs Event;

		if (it != vEventsHandler.end())
			it->first(Event);
	}
}