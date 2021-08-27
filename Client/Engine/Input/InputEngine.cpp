#include "StdAfx.h"
#include "InputEngine.h"

namespace INPUTS
{
	Engine::Engine()
	{
		m_pcMouse = new Mouse;
		m_pcKeyboard = new KeyBoard;
	}
	Engine::~Engine()
	{
		DELET(m_pcMouse);
		DELET(m_pcKeyboard);
	}
}