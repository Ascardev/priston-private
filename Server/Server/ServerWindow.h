#pragma once

#define WINDOW		(static_cast<CServerWindow *>(pcApplication->GetWindow()))
#define GSERVER		(WINDOW->GetServer())
#define GHANDLE		(WINDOW->GetHandle())

class CServerWindow : public CWindow
{
public:
	CServerWindow();
	virtual ~CServerWindow();

	UINT Init();
	void Shutdown();

	BOOL Run();

	CServer *GetServer() { return m_pcServer; }
	CServerHandle *GetHandle() { return m_pcHandle; }

	void Render();
protected:
	LRESULT WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

	void Update(double fTime);
private:
	CServer * m_pcServer = nullptr;
	CServerHandle * m_pcHandle = nullptr;
};