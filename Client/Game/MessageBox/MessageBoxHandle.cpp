#include "StdAfx.h"
#include "MessageBoxHandle.h"

namespace MESSAGEBOX
{
	Handle::Handle()
	{
		m_pcModel = new Model;
		m_pcTitle = new Title;
	}
	Handle::~Handle()
	{
		DELET(m_pcModel);
		DELET(m_pcTitle);
	}
	void Handle::Init()
	{
		INIT(m_pcModel);
		INIT(m_pcTitle);
	}
	void Handle::Shutdown()
	{
		//Clear();
		SHUTDOWN(m_pcModel);
		SHUTDOWN(m_pcTitle);
	}
	void Handle::Clear()
	{
		CLEARPTR(m_pcModel);
		CLEARPTR(m_pcTitle);
	}
	void Handle::Update(float fTime)
	{
		m_pcTitle->Update(fTime);
	}
	void Handle::Tick()
	{
		m_pcModel->Update();
		m_pcTitle->Tick();
	}
	void Handle::Render()
	{
		m_pcModel->Render();
		m_pcTitle->Render();
	}
	BOOL Handle::OnKeyPress(INPUTS::LPKEYBOARD pcKeyboard)
	{
		return m_pcModel->OnKeyPress(pcKeyboard);
	}
	void Handle::OnMouseMove(INPUTS::LPMOUSE pcMouse)
	{
		m_pcModel->OnMouseMove(pcMouse);
	}
	BOOL Handle::OnMouseClick(INPUTS::LPMOUSE pcMouse)
	{
		return m_pcModel->OnMouseClick(pcMouse);
	}
}