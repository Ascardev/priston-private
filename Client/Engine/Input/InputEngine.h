#pragma once

namespace INPUTS
{
	class Engine
	{
	public:
		Engine();
		virtual ~Engine();
		Mouse *GetMouse() { return m_pcMouse; }
		KeyBoard *GetKeyBoard() { return m_pcKeyboard; }
	private:
		Mouse *m_pcMouse = nullptr;
		KeyBoard *m_pcKeyboard = nullptr;
	};
}
