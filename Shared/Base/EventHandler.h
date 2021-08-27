#pragma once

namespace BASE
{
	struct EventHandler
	{
		EventHandler(LPVOID _pOnEventHandler);
		EventHandler(const EventHandler &c);
		virtual ~EventHandler(){}

		virtual void Fire();
	protected:
		LPVOID pOnEventHandler;
	};
	struct EventHandler1 : EventHandler
	{
	public:
		EventHandler1(LPVOID _pOnEventHandler,LPVOID _pPointer1);
		EventHandler1(const EventHandler1 &c);
		virtual ~EventHandler1() {}

		virtual void Fire();
	protected:
		LPVOID pPointer1;
	};
	struct EventHandler2 : EventHandler1
	{
	public:
		EventHandler2(LPVOID _pOnEventHandler,LPVOID _pPointer1,LPVOID _pPointer2);
		EventHandler2(const EventHandler2 &c);
		virtual ~EventHandler2() {}

		virtual void Fire();
	protected:
		LPVOID pPointer2;
	};
}