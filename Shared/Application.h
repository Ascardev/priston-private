#pragma once

class CWindow;

class CApplication
{
public:
	CApplication(CWindow * pcWindow);
	virtual ~CApplication();

	BOOL Init(HINSTANCE hInstance);
	void Shutdown();
	BOOL Run();

	UINT GetInitCode() {return m_iInitCode;}
	CINFO::LPSYSTEM GetSystem() {return m_pcSystem;}
	CINFO::LPPROCESSEX GetProcess() {return m_pcProcess;}
	CWindow * GetWindow() {return m_pcWindow;}
private:
	int m_iInitCode;
	CINFO::LPSYSTEM m_pcSystem;
	CINFO::LPPROCESSEX m_pcProcess;
	CWindow * m_pcWindow;
};