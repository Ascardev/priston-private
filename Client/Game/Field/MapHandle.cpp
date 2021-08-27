#include "StdAfx.h"
#include "MapHandle.h"

namespace MAP
{
	Handles::Handles()
	{
		m_pcModel = new Model;
		m_pcTitle = new Title;
	}
	Handles::~Handles()
	{
		DELET(m_pcModel);
		DELET(m_pcTitle);
	}
	void Handles::Init()
	{
		INIT(m_pcModel);
		INIT(m_pcTitle);
	}
	void Handles::Shutdown()
	{
		SHUTDOWN(m_pcModel);
		SHUTDOWN(m_pcTitle);
	}
	void Handles::Update()
	{
		m_pcModel->Update();
		m_pcTitle->Update();
	}
	void Handles::Render()
	{
		
	}
	BOOL Handles::OnMouseClick(INPUTS::LPMOUSE pcMouse)
	{
		if (m_pcTitle->OnMouseClick(pcMouse)) return TRUE;
		
		return FALSE;
	}
	void Handles::OnMouseMove(INPUTS::LPMOUSE pcMouse)
	{
		m_pcTitle->OnMouseMove(pcMouse);
	}
}