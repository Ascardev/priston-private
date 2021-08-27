#include "StdAfx.h"
#include "Application.h"

CApplication::CApplication(CWindow *pcWindow)
{
	m_pcWindow	= pcWindow;
	m_pcProcess	= new CINFO::ProcessEx;
	m_pcSystem	= new CINFO::System;
}
CApplication::~CApplication()
{
	DELET(m_pcProcess);
	DELET(m_pcSystem);
	DELET(m_pcWindow);
}
BOOL CApplication::Init(HINSTANCE hInstance)
{
	m_pcProcess->SetInstanceHandle(hInstance);
	m_pcWindow->SetApplication(this);
	m_iInitCode = m_pcWindow->Init();

	if (m_iInitCode == 1)
		return TRUE;

	return FALSE;
}
void CApplication::Shutdown()
{
	m_pcWindow->Shutdown();
}
BOOL CApplication::Run()
{
	return m_pcWindow->Run();
}